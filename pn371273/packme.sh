#!/bin/bash

#TODO: put your student id here
STUDENTID=pn371273

zip $STUDENTID.zip CMakeLists.txt adorate-seq.cpp blimit.hpp blimit.cpp  
mv $STUDENTID.zip ../sols/
