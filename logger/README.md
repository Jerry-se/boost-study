# boost log
## 是否是单线程
宏BOOST_LOG_NO_THREADS可以禁用多线程支持

## 动态链接
需要定义宏BOOST_LOG_DYN_LINK或者BOOST_ALL_DYN_LINK

## 静态链接
需要libboost_log_setup.a 需要在libboost_log.a前面

## 关于sink
sink决定日志信息输出到什么地方。没有添加sink，boost log将使用console作为默认的sink。如果主动调用了add_file_log函数，表示自己添加了sink,默认的sink就不在有效，被file sink取代。要设置sink, 需要将其添加到core中。

## test code
1. test1: add_file_log.
2. test2: format filter add_common_attributes.
3. test3: boost log 多模块多文件.
4. text_multifile_backend: 一个backend输出多个日志文件, [Text multi-file backend](https://www.boost.org/doc/libs/1_55_0/libs/log/doc/html/log/detailed/sink_backends.html#log.detailed.sink_backends.text_multifile) example.
5. text_multifile_backend2: 分离不同线程生成的日志, [multiple_files](https://www.boost.org/doc/libs/1_55_0/libs/log/example/multiple_files/main.cpp) example.

## 参考资料
1. [boost.log要点笔记](https://www.cnblogs.com/liaocheng/p/4222885.html)
2. [boost log使用心得](https://blog.csdn.net/Max_Cong/article/details/83176559)
3. [boost log库使用 十二 架构研究和主要使用总结](https://blog.csdn.net/qq_43682438/article/details/87876879)
