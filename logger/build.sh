#!/bin/bash

rm -f test1
rm -f test2
rm -f test3
rm -f test4
rm -f test5

# dynamic link
# g++ -DBOOST_LOG_DYN_LINK test1.cpp -o test1 -lboost_system -lboost_log -lboost_thread -lpthread
# static link
g++ test1.cpp -o test1 /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
 /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread
# g++ test1.cpp -o test1 -lboost_log_setup -lboost_log -lboost_system -lboost_thread -lboost_filesystem -lpthread

g++ test2.cpp -o test2 /usr/local/lib/libboost_log_setup.a \
 /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
 /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread

g++ test3.cpp -o test3 /usr/local/lib/libboost_log_setup.a \
 /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
 /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread

g++ text_multifile_backend.cpp -o test4 /usr/local/lib/libboost_log_setup.a \
 /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
 /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread

g++ text_multifile_backend2.cpp -o test5 /usr/local/lib/libboost_log_setup.a \
 /usr/local/lib/libboost_log.a /usr/local/lib/libboost_system.a \
 /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_filesystem.a -lpthread
