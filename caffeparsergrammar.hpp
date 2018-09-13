#define BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/qi_eol.hpp>

#include <iostream>
#include <string>

#include "caffeparserfunctors.hpp"

using namespace boost::spirit;
using namespace boost::phoenix;
using boost::phoenix::ref;

template<typename Lexer>
struct my_tokens : lex::lexer<Lexer>
{
    my_tokens()
    {
        simple_identifier       = "[\"]*[a-zA-Z_][a-zA-Z_]*[\"]*\n";
        unsigned_number         = "[0-9][0-9]*";
        colon_                  = "[:]";
        semicolon_              = "[;]";
        name_                   = "name";
		input_					= "input";
        input_dim_              = "input_dim";
        output_dim_             = "output_dim";
        line                    = "[\\n]";
    
        this->self  = 
                     simple_identifier
                    | unsigned_number
                    | left_brace
                    | right_brace
                    | colon_
                    | semicolon_
                    | name_
					| input_
                    | input_dim_
                    | output_dim_
                    ;

        this->self("WS") =  lex::token_def<>("[ \\t\\n]+") 
                            ;
    }
    lex::token_def<std::string> simple_identifier;
    
    lex::token_def<std::string> name_,
								input_,
                                input_dim_,
                                output_dim_
                                ;
    
    lex::token_def<int> unsigned_number;

    lex::token_def<std::string> 
                     left_brace, 
                     right_brace, 
                     colon_,
                     semicolon_,
                     line
                     ;
};

template<typename Iterator, typename Lexer>
struct my_grammar : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{

    template <typename TokenDef>
    my_grammar(TokenDef const& tok) : my_grammar::base_type(start)
    {
        name_      	= tok.name_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        input_      = tok.input_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        input_dim_ 	= tok.input_dim_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        output_dim_ = tok.output_dim_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        
        statement = name_
					| input_
                    | input_dim_
                    | output_dim_
                    ;
        start = +statement;
    }
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > start, statement;
    
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > name_,
													 input_,
                                                     input_dim_,
                                                     output_dim_
                                                     ;
};

