#include <iostream>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>

int main(int argc, char*argv[]) {
  std::string name="ModuleTwo";
  int max = -1;
  boost::filesystem::path id;
  if (id.empty())
    std::cout << "filepath is empty" << std::endl;
  boost::filesystem::path path("logs");
  boost::filesystem::directory_iterator enditer;
  for (boost::filesystem::directory_iterator iter(path); iter != enditer; iter++) {
    std::cout << iter->path().string() << std::endl;
    if (iter->path().string().find(name) != std::string::npos) {
      size_t pos1 = iter->path().string().find("_");
      size_t pos2 = iter->path().string().find(".");
      std::string nums = iter->path().string().substr(pos1+1, pos2 - pos1 - 1);
      std::cout << nums << std::endl;
      std::cout << atoi(nums.c_str()) << std::endl;
      if (atoi(nums.c_str()) > max) {
        id = iter->path();
        max = atoi(nums.c_str());
      }
    }
  }
  std::cout << "filepath(" << id.string() << ")" << std::endl;

  if (!id.empty()) {
    std::ifstream file(id.c_str(), std::ios::in);
    if (file.is_open()) {
      file.seekg(0, std::ios::beg);
      // for (int i = 0; i < 2; i++) {
      //   std::string line;
      //   getline(file, line);
      //   std::cout << line << std::endl;
      // }

      //back N line
      int linecount = 30;
      file.seekg(-2, std::ios::end);
      for (int i = 0; i < linecount; i++) {
        while (file.peek() != file.widen('\n'))
        {
          if (file.tellg() == 0) break;
          file.seekg(-1, std::ios::cur);
          // std::cout << "seekg ret=" << file.eof() << std::endl;
        }
        if (file.tellg() == 0) break;
        file.seekg(-1, std::ios::cur);
      }
      if (file.tellg() != 0)
        file.seekg(2, std::ios::cur);
      std::string  line;
      while (getline(file, line))
      {
        // std::cout << "eof=" << file.eof() << std::endl;
        std::cout << line << std::endl;
      }
      std::cout << "eof=" << file.eof() << std::endl;
    }
    file.close();
  }
  return 0;
}
