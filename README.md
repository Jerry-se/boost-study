# boost-study

Boost 学习笔记

## 编译 Boost {#compiling}

```shell
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0# apt install libboost-all-dev
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0#
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0# ./bootstrap.sh --help
`./bootstrap.sh' prepares Boost for building on a few kinds of systems.

Usage: ./bootstrap.sh [OPTION]...

Defaults for the options are specified in brackets.

Configuration:
  -h, --help                display this help and exit
  --with-bjam=BJAM          use existing Boost.Jam executable (bjam)
                            [automatically built]
  --with-toolset=TOOLSET    use specific Boost.Build toolset
                            [automatically detected]
  --show-libraries          show the set of libraries that require build
                            and installation steps (i.e., those libraries
                            that can be used with --with-libraries or
                            --without-libraries), then exit
  --with-libraries=list     build only a particular set of libraries,
                            describing using either a comma-separated list of
                            library names or "all"
                            [all]
  --without-libraries=list  build all libraries except the ones listed []
  --with-icu                enable Unicode/ICU support in Regex
                            [automatically detected]
  --without-icu             disable Unicode/ICU support in Regex
  --with-icu=DIR            specify the root of the ICU library installation
                            and enable Unicode/ICU support in Regex
                            [automatically detected]
  --with-python=PYTHON      specify the Python executable [python]
  --with-python-root=DIR    specify the root of the Python installation
                            [automatically detected]
  --with-python-version=X.Y specify the Python version as X.Y
                            [automatically detected]

Installation directories:
  --prefix=PREFIX           install Boost into the given PREFIX
                            [/usr/local]
  --exec-prefix=EPREFIX     install Boost binaries into the given EPREFIX
                            [PREFIX]

More precise control over installation directories:
  --libdir=DIR              install libraries here [EPREFIX/lib]
  --includedir=DIR          install headers here [PREFIX/include]

root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0#
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0# ./bootstrap.sh
Building Boost.Build engine with toolset gcc... tools/build/src/engine/bin.linuxx86_64/b2
Detecting Python version... 2.7
Detecting Python root... /usr
Unicode/ICU support for Boost.Regex?... /usr
Generating Boost.Build configuration in project-config.jam...

Bootstrapping is done. To build, run:

    ./b2

To adjust configuration, edit 'project-config.jam'.
Further information:

   - Command line help:
     ./b2 --help

   - Getting started guide:
     http://www.boost.org/more/getting_started/unix-variants.html

   - Boost.Build documentation:
     http://www.boost.org/build/doc/html/index.html

root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0# ./b2 --help
Boost.Build 2015.07-git

Project-specific help:

  Project has jamfile at Jamroot

Usage:

  b2 [options] [properties] [install|stage]

  Builds and installs Boost.

Targets and Related Options:

  install                 Install headers and compiled library files to the
  =======                 configured locations (below).

  --prefix=<PREFIX>       Install architecture independent files here.
                          Default; C:\Boost on Win32
                          Default; /usr/local on Unix. Linux, etc.

  --exec-prefix=<EPREFIX> Install architecture dependent files here.
                          Default; <PREFIX>

  --libdir=<DIR>          Install library files here.
                          Default; <EPREFIX>/lib

  --includedir=<HDRDIR>   Install header files here.
                          Default; <PREFIX>/include

  stage                   Build and install only compiled library files to the
  =====                   stage directory.

  --stagedir=<STAGEDIR>   Install library files here
                          Default; ./stage

Other Options:

  --build-type=<type>     Build the specified pre-defined set of variations of
                          the libraries. Note, that which variants get built
                          depends on what each library supports.

                              -- minimal -- (default) Builds a minimal set of
                              variants. On Windows, these are static
                              multithreaded libraries in debug and release
                              modes, using shared runtime. On Linux, these are
                              static and shared multithreaded libraries in
                              release mode.

                              -- complete -- Build all possible variations.

  --build-dir=DIR         Build in this location instead of building within
                          the distribution tree. Recommended!

  --show-libraries        Display the list of Boost libraries that require
                          build and installation steps, and then exit.

  --layout=<layout>       Determine whether to choose library names and header
                          locations such that multiple versions of Boost or
                          multiple compilers can be used on the same system.

                              -- versioned -- Names of boost binaries include
                              the Boost version number, name and version of
                              the compiler and encoded build properties. Boost
                              headers are installed in a subdirectory of
                              <HDRDIR> whose name contains the Boost version
                              number.

                              -- tagged -- Names of boost binaries include the
                              encoded build properties such as variant and
                              threading, but do not including compiler name
                              and version, or Boost version. This option is
                              useful if you build several variants of Boost,
                              using the same compiler.

                              -- system -- Binaries names do not include the
                              Boost version number or the name and version
                              number of the compiler. Boost headers are
                              installed directly into <HDRDIR>. This option is
                              intended for system integrators building
                              distribution packages.

                          The default value is 'versioned' on Windows, and
                          'system' on Unix.

  --buildid=ID            Add the specified ID to the name of built libraries.
                          The default is to not add anything.

  --python-buildid=ID     Add the specified ID to the name of built libraries
                          that depend on Python. The default is to not add
                          anything. This ID is added in addition to --buildid.

  --help                  This message.

  --with-<library>        Build and install the specified <library>. If this
                          option is used, only libraries specified using this
                          option will be built.

  --without-<library>     Do not build, stage, or install the specified
                          <library>. By default, all libraries are built.

Properties:

  toolset=toolset         Indicate the toolset to build with.

  variant=debug|release   Select the build variant

  link=static|shared      Whether to build static or shared libraries

  threading=single|multi  Whether to build single or multithreaded binaries

  runtime-link=static|shared
                          Whether to link to static or shared C and C++
                          runtime.


General command line usage:

    b2 [options] [properties] [targets]

  Options, properties and targets can be specified in any order.

Important Options:

  * --clean Remove targets instead of building
  * -a Rebuild everything
  * -n Don't execute the commands, only print them
  * -d+2 Show commands as they are executed
  * -d0 Suppress all informational messages
  * -q Stop at first error
  * --reconfigure Rerun all configuration checks
  * --debug-configuration Diagnose configuration
  * --debug-building Report which targets are built with what properties
  * --debug-generator Diagnose generator search/execution

Further Help:

  The following options can be used to obtain additional documentation.

  * --help-options Print more obscure command line options.
  * --help-internal Boost.Build implementation details.
  * --help-doc-options Implementation details doc formatting.

...found 1 target...
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0#
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0# ./b2
Performing configuration checks

    - 32-bit                   : no
    - 64-bit                   : yes
    - arm                      : no
    - mips1                    : no
    - power                    : no
    - sparc                    : no
    - x86                      : yes

Building the Boost C++ Libraries.


    - symlinks supported       : yes
    - C++11 mutex              : yes
    - lockfree boost::atomic_flag : yes
    - Boost.Config Feature Check: cxx11_auto_declarations : yes
    - Boost.Config Feature Check: cxx11_constexpr : yes
    - Boost.Config Feature Check: cxx11_defaulted_functions : yes
    - Boost.Config Feature Check: cxx11_final : yes
    - Boost.Config Feature Check: cxx11_hdr_mutex : yes
    - Boost.Config Feature Check: cxx11_hdr_regex : yes
    - Boost.Config Feature Check: cxx11_hdr_tuple : yes
    - Boost.Config Feature Check: cxx11_lambdas : yes
    - Boost.Config Feature Check: cxx11_noexcept : yes
    - Boost.Config Feature Check: cxx11_nullptr : yes
    - Boost.Config Feature Check: cxx11_rvalue_references : yes
    - Boost.Config Feature Check: cxx11_template_aliases : yes
    - Boost.Config Feature Check: cxx11_thread_local : yes
    - Boost.Config Feature Check: cxx11_variadic_templates : yes
    - has_icu builds           : yes
warning: Graph library does not contain MPI-based parallel components.
note: to enable them, add "using mpi ;" to your user-config.jam
    - zlib                     : yes
    - bzip2                    : no
    - lzma                     : no
    - iconv (libc)             : yes
    - icu                      : yes
    - native-atomic-int32-supported : yes
    - native-syslog-supported  : yes
    - pthread-supports-robust-mutexes : yes
    - compiler-supports-visibility : yes
    - compiler-supports-ssse3  : yes
    - compiler-supports-avx2   : yes
    - gcc visibility           : yes
    - long double support      : yes
warning: skipping optional Message Passing Interface (MPI) library.
note: to enable MPI support, add "using mpi ;" to user-config.jam.
note: to suppress this message, pass "--without-mpi" to bjam.
note: otherwise, you can safely ignore this message.
    - libbacktrace builds      : yes
    - addr2line builds         : yes
    - WinDbg builds            : no
    - WinDbgCached builds      : no
    - zlib                     : yes
    - bzip2                    : no
    - lzma                     : no

Component configuration:

    - atomic                   : building
    - chrono                   : building
    - container                : building
    - context                  : building
    - coroutine                : building
    - date_time                : building
    - exception                : building
    - fiber                    : building
    - filesystem               : building
    - graph                    : building
    - graph_parallel           : building
    - iostreams                : building
    - locale                   : building
    - log                      : building
    - math                     : building
    - mpi                      : building
    - program_options          : building
    - python                   : building
    - random                   : building
    - regex                    : building
    - serialization            : building
    - signals                  : building
    - stacktrace               : building
    - system                   : building
    - test                     : building
    - thread                   : building
    - timer                    : building
    - type_erasure             : building
    - wave                     : building

...patience...
...patience...
...patience...
...patience...
...patience...
...found 14325 targets...
...updating 1307 targets...
gcc.compile.c++ bin.v2/libs/atomic/build/gcc-gnu-7/release/threadapi-pthread/threading-multi/lockpool.o
gcc.link.dll bin.v2/libs/atomic/build/gcc-gnu-7/release/threadapi-pthread/threading-multi/libboost_atomic.so.1.66.0
common.copy stage/lib/libboost_atomic.so.1.66.0
ln-UNIX stage/lib/libboost_atomic.so
...
gcc.compile.c++ bin.v2/libs/wave/build/gcc-gnu-7/release/link-static/threadapi-pthread/threading-multi/wave_config_constant.o
gcc.compile.c++ bin.v2/libs/wave/build/gcc-gnu-7/release/link-static/threadapi-pthread/threading-multi/cpplexer/re2clex/aq.o
gcc.compile.c++ bin.v2/libs/wave/build/gcc-gnu-7/release/link-static/threadapi-pthread/threading-multi/cpplexer/re2clex/cpp_re.o
gcc.archive bin.v2/libs/wave/build/gcc-gnu-7/release/link-static/threadapi-pthread/threading-multi/libboost_wave.a
common.copy stage/lib/libboost_wave.a
...updated 1307 targets...


The Boost C++ Libraries were successfully built!

The following directory should be added to compiler include paths:

    /home/dbtu/code/boost_1_66_0

The following directory should be added to linker library paths:

    /home/dbtu/code/boost_1_66_0/stage/lib

root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0#
root@3958bc5ccab3:/home/dbtu/code/boost_1_66_0# ls ./stage/lib/
libboost_atomic.a             libboost_filesystem.so         libboost_math_c99l.a                 libboost_random.so.1.66.0                libboost_system.so
libboost_atomic.so            libboost_filesystem.so.1.66.0  libboost_math_c99l.so                libboost_regex.a                         libboost_system.so.1.66.0
libboost_atomic.so.1.66.0     libboost_graph.a               libboost_math_c99l.so.1.66.0         libboost_regex.so                        libboost_test_exec_monitor.a
libboost_chrono.a             libboost_graph.so              libboost_math_tr1.a                  libboost_regex.so.1.66.0                 libboost_thread.a
libboost_chrono.so            libboost_graph.so.1.66.0       libboost_math_tr1.so                 libboost_serialization.a                 libboost_thread.so
libboost_chrono.so.1.66.0     libboost_iostreams.a           libboost_math_tr1.so.1.66.0          libboost_serialization.so                libboost_thread.so.1.66.0
libboost_container.a          libboost_iostreams.so          libboost_math_tr1f.a                 libboost_serialization.so.1.66.0         libboost_timer.a
libboost_container.so         libboost_iostreams.so.1.66.0   libboost_math_tr1f.so                libboost_signals.a                       libboost_timer.so
libboost_container.so.1.66.0  libboost_locale.a              libboost_math_tr1f.so.1.66.0         libboost_signals.so                      libboost_timer.so.1.66.0
libboost_context.a            libboost_locale.so             libboost_math_tr1l.a                 libboost_signals.so.1.66.0               libboost_type_erasure.a
libboost_context.so           libboost_locale.so.1.66.0      libboost_math_tr1l.so                libboost_stacktrace_addr2line.a          libboost_type_erasure.so
libboost_context.so.1.66.0    libboost_log.a                 libboost_math_tr1l.so.1.66.0         libboost_stacktrace_addr2line.so         libboost_type_erasure.so.1.66.0
libboost_coroutine.a          libboost_log.so                libboost_prg_exec_monitor.a          libboost_stacktrace_addr2line.so.1.66.0  libboost_unit_test_framework.a
libboost_coroutine.so         libboost_log.so.1.66.0         libboost_prg_exec_monitor.so         libboost_stacktrace_backtrace.a          libboost_unit_test_framework.so
libboost_coroutine.so.1.66.0  libboost_log_setup.a           libboost_prg_exec_monitor.so.1.66.0  libboost_stacktrace_backtrace.so         libboost_unit_test_framework.so.1.66.0
libboost_date_time.a          libboost_log_setup.so          libboost_program_options.a           libboost_stacktrace_backtrace.so.1.66.0  libboost_wave.a
libboost_date_time.so         libboost_log_setup.so.1.66.0   libboost_program_options.so          libboost_stacktrace_basic.a              libboost_wave.so
libboost_date_time.so.1.66.0  libboost_math_c99.a            libboost_program_options.so.1.66.0   libboost_stacktrace_basic.so             libboost_wave.so.1.66.0
libboost_exception.a          libboost_math_c99.so           libboost_python.a                    libboost_stacktrace_basic.so.1.66.0      libboost_wserialization.a
libboost_fiber.a              libboost_math_c99.so.1.66.0    libboost_python.so                   libboost_stacktrace_noop.a               libboost_wserialization.so
libboost_fiber.so             libboost_math_c99f.a           libboost_python.so.1.66.0            libboost_stacktrace_noop.so              libboost_wserialization.so.1.66.0
libboost_fiber.so.1.66.0      libboost_math_c99f.so          libboost_random.a                    libboost_stacktrace_noop.so.1.66.0
libboost_filesystem.a         libboost_math_c99f.so.1.66.0   libboost_random.so                   libboost_system.a
```
