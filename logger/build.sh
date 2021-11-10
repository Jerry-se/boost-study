#!/bin/bash

# rm -f test[1-9]

# dynamic link
# g++ -DBOOST_LOG_DYN_LINK test1.cpp -o test1 -lboost_system -lboost_log -lboost_thread -lpthread
# static link
# g++ test1.cpp -o test1 /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
#  /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread
# g++ test1.cpp -o test1 -lboost_log_setup -lboost_log -lboost_system -lboost_thread -lboost_filesystem -lpthread

build() {
  if [ -f $2 ];then
    rm -f $2
  fi
  if [[ "$2" == *4* ]];then
    extern="/usr/local/lib/libboost_regex.a"
  fi
  if [ -f $1 ];then
    g++ $1 -o $2 /usr/local/lib/libboost_log_setup.a $extern \
      /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
      /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread
  else
    echo "$1 not exist"
  fi
}

if [ $# -lt 1 ];then
  echo "no param"
  for k in $( seq 1 7 )
  do
    echo "wait for building test$k"
    build test$k.cpp test$k
  done
  echo "wait for building test8"
  build text_multifile_backend.cpp test8
  echo "wait for building test9"
  build text_multifile_backend2.cpp test9
else
  if [[ $1 -eq 8 ]];then
    echo "wait for building test8"
    build text_multifile_backend.cpp test8
  elif [[ $1 -eq 9 ]];then
    echo "wait for building test9"
    build text_multifile_backend2.cpp test9
  elif [[ $1 -eq unittest ]];then
    echo "wait for building unittest"
    build unittest.cpp unittest
  else
    echo "wait for building test$1"
    build test$1.cpp test$1
  fi
fi
