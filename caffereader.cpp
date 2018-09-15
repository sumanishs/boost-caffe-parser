/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

#include "caffereader.hpp"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

#include <iostream>
#include <fstream>
#include <string>

using namespace boost::spirit;

bool 
CaffeReader::Read(std::string& filename){

    typedef std::string::iterator   base_iterator_type;
    typedef lex::lexertl::token<base_iterator_type, boost::mpl::vector<unsigned int, std::string> > token_type;
    //typedef lex::lexertl::token<base_iterator_type> token_type;
    typedef lex::lexertl::lexer<token_type>  lexer_type;
    typedef my_tokens<lexer_type>   my_tokens_lex;
    typedef my_tokens_lex::iterator_type    token_iterator;
    typedef my_grammar<token_iterator, my_tokens_lex::lexer_def>      my_grammar_t;
    //typedef my_grammar<token_iterator>      my_grammar_t;

    my_tokens_lex   tokens;
    my_grammar_t    mygrammar(tokens);    


    std::ifstream inFile;
    inFile.open(filename.c_str());
    if(inFile.fail()){
        std::cout << "Cannot open file to read...." << std::endl;
        return false;
    }

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str(strStream.str());
    //str.pop_back();
    std::cout << "File content:" << str << "!" << std::endl;
	inFile.close();
	
	std::string::iterator itr = str.begin();
	token_iterator  tkstart = tokens.begin(itr, str.end());
	token_iterator  tkend = tokens.end();
    std::cout << "Parsing:" << str << std::endl;
	bool r = qi::phrase_parse(tkstart, tkend, mygrammar, qi::in_state("WS")[tokens.self]);
	if(r && tkstart == tkend)
	{
	  std::cout << "Parsing succeeded....." << std::endl;
	}    
	else
	{
	  std::string rest(tkstart, tkend);
	  std::cout << "Parsing failed....." << std::endl;
	  std::cout << "Stopped at:" << rest << std::endl;
	  return false;	
	}
    std::cout << "Bye Bye ..... :-)" << std::endl;
    return true;


}
