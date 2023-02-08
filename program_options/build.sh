#!/bin/bash

rm -f test

g++ test.cpp -o test /usr/local/lib/libboost_log_setup.a /usr/local/lib/libboost_regex.a \
  /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
  /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread \
  /usr/local/lib/libboost_program_options.a
