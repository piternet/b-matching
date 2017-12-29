#!/bin/bash

#TODO: put your student id here
STUDENTID=ab123456

zip $STUDENTID.zip CMakeLists.txt adorate-42.cpp blimit.hpp blimit.cpp  
mv $STUDENTID.zip ../sols/
