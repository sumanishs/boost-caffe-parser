#include <boost/spirit/include/qi.hpp>

using namespace boost::spirit;

struct PrintStr {
  void operator()(const std::string& str, qi::unused_type, qi::unused_type) const{
	std::string temp(str);
	if (!temp.empty() && temp[temp.length()-1] == '\n') {
	  temp.erase(temp.length()-1);
	} 
	std::cout << temp ;
  }
  PrintStr() {}
};

struct PrintInt {
    void operator()(const int& i, qi::unused_type, qi::unused_type) const{
        std::cout << i ;
    }
    PrintInt() {}
};

struct PrintDouble {
    void operator()(const double& d, qi::unused_type, qi::unused_type) const{
        std::cout << d ;
    }
    PrintDouble() {}
};

struct Printnl {
    void operator()(const std::string& str, qi::unused_type, qi::unused_type) const{
        std::cout << std::endl;
    }
    Printnl() {}
};
