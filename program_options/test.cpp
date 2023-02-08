#include <iostream>
#include <string>

#include <boost/program_options.hpp>

namespace bpo = boost::program_options;

int main(int argc, char* argv[]) {
  bpo::options_description opts("test command options");
  opts.add_options()
    ("help,h", "test options help")
    ("name,n", bpo::value<std::string>(), "param name")
    ("age", bpo::value<int>(), "param age");
  bpo::variables_map vm;
  try {
    bpo::store(bpo::parse_command_line(argc, argv, opts), vm);
    bpo::notify(vm);

    std::cout << "param count " << vm.size() << std::endl;
    if (vm.count("name") > 0) {
      std::cout << "input name=" << vm["name"].as<std::string>() << std::endl;
    }
    if (vm.count("age") > 0) {
      std::cout << "input age=" << vm["age"].as<int>() << std::endl;
    }
    if (vm.count("help") > 0) {
      std::cout << opts;
    }
  }
  catch (const std::exception &e) {
    std::cout << "invalid command option " << e.what() << std::endl;
    std::cout << opts;
    return -1;
  }
  return 0;
}
