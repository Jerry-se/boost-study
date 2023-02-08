#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

int main(int argc, char* argv[]) {
  // in C/C++ syntax
  time_t tt_ = time(nullptr);
  struct tm tm_ = {};
  localtime_r(&tt_, &tm_);
  char buf_[256] = {0};
  strftime(buf_, sizeof(char) * 256, "%Y-%m-%d %H:%M:%S %Z", &tm_);
  std::cout << buf_ << std::endl;

  // boost style
  boost::posix_time::ptime  now = boost::posix_time::second_clock::local_time();
  boost::posix_time::ptime  utc = boost::posix_time::second_clock::universal_time();

  boost::posix_time::time_duration tz_offset = (now - utc);

  std::stringstream   ss;
  boost::local_time::local_time_facet* output_facet = new boost::local_time::local_time_facet();
  ss.imbue(std::locale(std::locale::classic(), output_facet));

  output_facet->format("%H:%M:%S");
  ss.str("");
  ss << tz_offset;

  std::cout << ss.str() << std::endl;

  boost::local_time::time_zone_ptr    zone(new boost::local_time::posix_time_zone(ss.str().c_str()));
  boost::local_time::local_date_time  ldt = boost::local_time::local_microsec_clock::local_time(zone);
  // boost::local_time::local_time_facet* output_facet = new boost::local_time::local_time_facet();
  // ss.imbue(std::locale(std::locale::classic(), output_facet));
  output_facet->format("%Y-%m-%d %H:%M:%S.%f %Q");
  ss.str("");
  ss << ldt;
  std::cout << ss.str() << std::endl; // "2004-02-29 12:34:56.000789-05:00"

  time_t ctime = 1638241435;
  boost::posix_time::ptime pctime = boost::posix_time::from_time_t(ctime);
  boost::local_time::local_date_time  ldt2(pctime, zone);
  ss.str("");
  ss << ldt2;
  std::cout << ss.str() << std::endl;

  delete output_facet;
  return 0;
}
