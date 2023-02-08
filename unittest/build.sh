#!/bin/bash

rm -f test
rm -f test_fixture
rm -f test_fixture2

g++ test_main.cpp -o test /usr/local/lib/libboost_system.a /usr/local/lib/libboost_filesystem.a \
  /usr/local/lib/libboost_thread.a -lpthread \
  /usr/local/lib/libboost_program_options.a /usr/local/lib/libboost_unit_test_framework.a

g++ test_fixture.cpp -o test_fixture /usr/local/lib/libboost_system.a /usr/local/lib/libboost_filesystem.a \
  /usr/local/lib/libboost_thread.a -lpthread \
  /usr/local/lib/libboost_program_options.a /usr/local/lib/libboost_unit_test_framework.a

g++ test_fixture2.cpp -o test_fixture2 /usr/local/lib/libboost_system.a /usr/local/lib/libboost_filesystem.a \
  /usr/local/lib/libboost_thread.a -lpthread \
  /usr/local/lib/libboost_program_options.a /usr/local/lib/libboost_unit_test_framework.a
