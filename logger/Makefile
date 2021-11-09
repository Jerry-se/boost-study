CXXFLAGS = -O2 -g -Wall -fmessage-length=0

MODULE=log

OBJS_DIR=../objs/$(MODULE)

SUB_OBJS_DIR_FOR_TEST=$(OBJS_DIR)/testcase

OBJS+= \
        $(OBJS_DIR)/test1.o \

INCLUDES=\
        -I../include \
        -I../3rd/gtest-1.6.0/include \
        -I../3rd

LIBS=\
        -L../lib \
        -L../3rd/gtest-1.6.0/lib -lgtest \
        -lssl \
        -lboost_log_setup \
        -lboost_log \
        -lboost_filesystem \
        -lboost_thread \
        -lboost_date_time \
        -lboost_system \
        -lrt

TARGET = $(OBJS_DIR)/log

.PHONY:all clean $(TARGET)

all: echomsg clean checkdir $(TARGET)
        echo "complete"

echomsg:
        echo $(OBJS)

$(TARGET):$(OBJS)
        $(CXX) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJS_DIR)/%.o:%.cpp
        $(CXX)  $(CXXFLAGS) -c -o $@ $^ $(INCLUDES)

checkdir:
        echo "!run checkdir"
        @if test ! -d $(SUB_OBJS_DIR_FOR_TEST) ; \
        then \
          mkdir -p $(SUB_OBJS_DIR_FOR_TEST) ; \
        fi

.PHONY:clean

clean:
        rm -f $(OBJS) $(TARGET)
