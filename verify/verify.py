# required directory structure
# TR - test root
# TR/sols/ab123456.zip -> your solution in a zip file
# TR/data/paper.txt -> input file
# TR/ref-results/paper-1.txt -> expected output
# TR/verify/verify.py -> this script
# TR/lib/blimit-paper.cpp -> sample blimit implementation that will be compiled with your code
#
# this script must be run from TR/verify directory, thus:
# cd TR/verify
# python verify.py

import logging
import os
import subprocess
import signal
import shutil
import zipfile
import itertools

log = logging.getLogger("verifyprograms")


class Alarm(Exception):
    pass


def alarm_handler(signum, frame):
    raise Alarm


def gen_header(files, threads, b_types):
    all_head = "login,tot_err"
    for (thread_c, file, b_type) in itertools.product(threads, files, b_types):
        all_head += ",%s-%d-%d" % (file, thread_c, b_type)
    return all_head


def get_run_number(filebase="results"):
    run_number = 1
    while os.path.isfile(filebase+"-run"+str(run_number)+".csv"):
        run_number += 1
    return run_number


def read_adorates(filename):
    log.debug("file: %s", filename)
    adorates = []
    try:
        with open(filename) as file:
            for line in file:
                adorates.append(int(line))
        return adorates
    except IOError as err:
        log.error(err)
        return None
    except ValueError as err:
        log.error(err)
        return None

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    run_number = get_run_number('../logs/results')
    log.info("run number %d", run_number)
    try:
        os.mkdir('../logs/')
    except FileExistsError:
        pass
    fh = logging.FileHandler('../logs/verifyprograms-run'+str(run_number)+'.log')
    formatter = logging.Formatter('%(asctime)s : %(message)s')
    fh.setFormatter(formatter)
    log.addHandler(fh)
    sink = open('/dev/null', 'w')
    tests = ['paper']
    threads = [1, 2, ]
    blimit = 1
    timelimit = 5
    # --------------------------------------------------
    # TODO: put your studentid here
    students = ['ab123456']
    # --------------------------------------------------
    basedir = os.getcwd()
    zipdir = "../sols/"
    testdir = "../tests-"+str(run_number)+"/"
    os.makedirs(testdir)
    with open('../logs/results-run'+str(run_number)+'.csv', 'a') as results_stat:
        results_stat.write(gen_header(tests, threads, range(blimit+1)))
        for solution in students:
            results_stat.flush()
            results_stat.write("\n"+solution+",")
            error_count = 0
            os.chdir(basedir)
            log.info("solution: %s" % solution)

            if not os.path.exists(zipdir + solution + ".zip"):
                log.error("zip file missing")
                continue

            shutil.copy(zipdir + solution + ".zip", testdir)
            os.mkdir(testdir + solution)
            zip = zipfile.ZipFile(testdir + solution + ".zip")
            try:
                zip.extractall(testdir + solution)
            except zipfile.BadZipFile:
                log.error("zip file misformatted")
                continue

            shutil.copy(basedir + "/../lib/blimit-paper.cpp", testdir+solution+"/blimit.cpp")
            os.mkdir(testdir+solution+"/build")
            os.chdir(testdir+solution+"/build")

            retcode = subprocess.call(("cmake", "-DCMAKE_BUILD_TYPE=Release", ".."), stdout=sink, stderr=sink)
            if retcode != 0:
                log.error("cmake non-0 retcode")
                continue
            retcode = subprocess.call("make", stdout=sink, stderr=sink)
            if retcode != 0:
                log.error("make non-0 retcode")
                continue
            test_counter = 0
            res_line = ""
            with open('errors.txt', 'w') as error_file:
                for (thread_num, test_file) in itertools.product(threads, tests):
                    ref_result = read_adorates("../../../ref-results/res-"+test_file+"-"+str(blimit)+".txt")
                    params = ["./adorate", str(thread_num), "../../../data/"+test_file+".txt", str(blimit)]
                    compact_command = " ".join(params)
                    compact_params = "_".join((str(thread_num), test_file, str(blimit)))
                    log.info("dir: "+solution+" params: " + compact_params)
                    test_counter += 1
                    signal.signal(signal.SIGALRM, alarm_handler)
                    signal.alarm(timelimit)
                    child = None
                    with open("stdout_"+compact_params+".txt", 'w') as stdoutfile:
                        try:
                            child = subprocess.Popen(params, stdout=stdoutfile, stderr=sink)
                            outcode = child.wait()
                            signal.alarm(0)
                            log.info("subprocess finished")
                            if outcode != 0:
                                log.error("non-0 exit code")
                                res_line += "non0, "*len(ref_result)
                                error_count += len(ref_result)
                                error_file.write(compact_command+"\n")
                                continue
                        except FileNotFoundError:
                            log.error("exec not found")
                            res_line += "notfound, "*len(ref_result)
                            error_count += len(ref_result)
                            error_file.write(compact_command+"\n")
                            continue
                        except Alarm:
                            log.info("timeout!")
                            if child is not None:
                                log.info("killing the child")
                                child.kill()
                                log.info("child killed")
                            error_count += len(ref_result)
                            res_line += "time, "*len(ref_result)
                            error_file.write(compact_command+"\n")
                            continue

                    prog_result = read_adorates("stdout_"+compact_params+".txt")
                    if prog_result == None:
                        log.info("error while reading output")
                        res_line += "out, "*len(ref_result)
                        error_count += len(ref_result)
                        error_file.write(compact_command+"\n")
                        continue
                    for (ref, prog) in itertools.zip_longest(ref_result, prog_result, fillvalue=-1):
                        if ref != prog:
                            log.info("error in the result: expected %d seen %d", ref, prog)
                            res_line += "res, "
                            error_file.write(compact_command+"\n")
                            error_count += 1
                        else:
                            res_line += "OK, "

            log.info("solution %s errors %d" % (solution, error_count))
            results_stat.write(str(error_count)+","+res_line)
        results_stat.write("\n")


