BOOST_INCLUDE_DIR := /usr/local/include/boost

BOOST_LIBRARY_DIR := /usr/local/lib

BOOST_LIBRARYS := log log_setup thread date_time system filesystem exception program_options serialization signals serialization chrono unit_test_framework context

# 宏定义
DEFS = -D Boost_USE_STATIC_LIBS=ON -D Boost_USE_STATIC_RUNTIME=ON -D Boost_USE_MULTITHREADED=ON

# BOOST_LIB += ../lib/
BOOST_LIB_L := $(addprefix -L , $(BOOST_LIBRARY_DIR))

CFLAGS  := -I $(BOOST_INCLUDE_DIR) -I ../include $(DEFS) -std=gnu++11 -fPIC
LDFLAGS := -lrt -Wl,-Bstatic $(BOOST_LIBRARYS:%=-lboost_%) -Wl,-Bdynamic -Wl,--as-needed $(BOOST_LIB_L) -lstdc++ -pthread

all: test
test: test.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@
clean:
	-@rm -f test.o
	-@rm -f test
