/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

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
using boost::spirit::qi::eoi;

template<typename Lexer>
struct my_tokens : lex::lexer<Lexer>
{
    my_tokens()
    {
        simple_identifier       = "[\"]*[a-zA-Z_][a-zA-Z_0-9.\\\-]*[\"]*\n";
        unsigned_number         = "[0-9][0-9]*";
        double_number           = "[0-9]*[.][0-9][0-9]*";
        colon_                  = "[:]";
        semicolon_              = "[;]";
        left_brace_             = "[\\{]";
        right_brace_            = "[\\}]";              
        name_                   = "name";
		input_					= "input";
        input_dim_              = "input_dim";
        output_dim_             = "output_dim";
        bottom_                 = "bottom";
        top_                    = "top";
        lr_mult_                = "lr_mult";
        num_output_             = "num_output";
        kernel_size_            = "kernel_size";
        stride_                 = "stride";
        pad_                    = "pad";
        type_                   = "type";
        pool_                   = "pool";
        param_                  = "param";
        weight_filler_          = "weight_filler";
        bias_filler_            = "bias_filler";
        layer_                  = "layer";
        convolution_param_      = "convolution_param";
        pooling_param_          = "pooling_param";
        inner_product_param_    = "inner_product_param";
        dim_                    = "dim";
        input_shape_            = "input_shape";
        decay_mult_             = "decay_mult";
        alpha_                  = "alpha";
        beta_                   = "beta";
        lrn_param_              = "lrn_param";
        local_size_             = "local_size";
        group_                  = "group";
        dropout_ratio_          = "dropout_ratio";
        dropout_param_          = "dropout_param";
        source_                 = "source";
        mean_file_              = "mean_file";
        backend_                = "backend";
        batch_size_             = "batch_size";
        crop_size_              = "crop_size";
        mirror_                 = "mirror";
        phase_                  = "phase";
        channels_               = "channels";
        height_                 = "height";
        width_                  = "width";
        data_param_             = "data_param";
        transform_param_        = "transform_param";
        memory_data_param_      = "memory_data_param";
        include_                = "include";
        mean_                   = "mean";
        std_                    = "std";
        value_                  = "value";
        line                    = "[\\n]";
    
        this->self  += 
                      simple_identifier | double_number 
                    | unsigned_number | left_brace_ | right_brace_ | colon_
                    | semicolon_ | name_ | input_ | input_dim_ | output_dim_
                    | bottom_ | top_ | lr_mult_ | num_output_ | kernel_size_
                    | stride_ | pad_ | type_ | pool_ | param_ | weight_filler_
                    | bias_filler_ | layer_ | convolution_param_ | pooling_param_
                    | inner_product_param_
                    ;

        this->self +=
                      dim_ | input_shape_ | decay_mult_ | alpha_ | beta_ | lrn_param_
                    | local_size_ | group_ | dropout_ratio_ | dropout_param_ | source_ 
                    | mean_file_ | backend_ | batch_size_ | crop_size_ | mirror_ | phase_
                    | channels_ | height_ | width_ | memory_data_param_ | include_ | mean_
                    | std_ | value_ | data_param_ | transform_param_
                    ;

        this->self("WS") =  lex::token_def<>("\\/\\/[^\\n]*")           // Single line C like comment 
                            | "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"     // Multi-line C like comment 
                            | lex::token_def<>("[ \\t\\n]+") 
                            ;
    }
    
    lex::token_def<std::string> name_, input_, input_dim_, output_dim_, bottom_, top_, lr_mult_,
                                num_output_, kernel_size_, stride_, pad_, type_, pool_, param_,
                                weight_filler_, bias_filler_, layer_, convolution_param_, pooling_param_,
                                inner_product_param_ ;

    lex::token_def<std::string> dim_, input_shape_, decay_mult_, local_size_, alpha_, beta_, lrn_param_,
                                group_, dropout_ratio_, dropout_param_, source_, mean_file_, backend_, batch_size_,
                                crop_size_, mirror_, phase_, channels_, height_, width_, memory_data_param_,
                                include_, mean_, std_, value_, data_param_, transform_param_
                                ;
    
    lex::token_def<int> unsigned_number 
                        ;
    lex::token_def<double> double_number
                           ; 

    lex::token_def<std::string> left_brace_, right_brace_, colon_, semicolon_, line
                                ;
    lex::token_def<std::string> simple_identifier;
};

template<typename Iterator, typename Lexer>
struct my_grammar : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{

    template <typename TokenDef>
    my_grammar(TokenDef const& tok) : my_grammar::base_type(start)
    {
        name_      	    = tok.name_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        input_          = tok.input_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        input_dim_ 	    = tok.input_dim_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        output_dim_     = tok.output_dim_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        bottom_         = tok.bottom_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        top_            = tok.top_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        lr_mult_        = tok.lr_mult_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        num_output_     = tok.num_output_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        kernel_size_    = tok.kernel_size_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        stride_         = tok.stride_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        pad_            = tok.pad_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        type_           = tok.type_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        pool_           = tok.pool_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()] ;
        
        weight_filler_statements_ = type_
                                   | mean_
                                   | std_
                                   ;        

        weight_filler_  = tok.weight_filler_ [PrintStr()] 
                          >> tok.left_brace_ 
                          >> +weight_filler_statements_
                          >> tok.right_brace_
                          ;

        bias_filler_statements_ = type_
                                 | value_
                                 ;

        bias_filler_    = tok.bias_filler_  [PrintStr()] 
                          >> tok.left_brace_ 
                          >> +bias_filler_statements_ 
                          >> tok.right_brace_;
        
        dim_            = tok.dim_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        decay_mult_     = tok.decay_mult_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        local_size_     = tok.local_size_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        alpha_          = tok.alpha_ [PrintStr()] >> tok.colon_ >> tok.double_number [PrintDouble()];
        beta_           = tok.beta_ [PrintStr()] >> tok.colon_ >> tok.double_number [PrintDouble()];
        group_          = tok.group_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintDouble()];
        dropout_ratio_  = tok.dropout_ratio_ [PrintStr()] >> tok.colon_ >> tok.double_number [PrintDouble()];

        param_statements_   = lr_mult_
                             | decay_mult_
                             ;

        param_          = tok.param_ [PrintStr()] 
                          >> tok.left_brace_ 
                          >> +param_statements_
                          >> tok.right_brace_;

        input_shape_    = tok.input_shape_ [PrintStr()]
                          >> tok.left_brace_
                          >> +dim_
                          >> tok.right_brace_
                          ;

        convolution_param_statements_ = num_output_
                                        | kernel_size_
                                        | stride_
                                        | pad_
                                        | weight_filler_
                                        | bias_filler_
                                        | group_
                                        ; 
        
        convolution_param_  = tok.convolution_param_ [PrintStr()]
                              >> tok.left_brace_
                              >> +convolution_param_statements_
                              >> tok.right_brace_
                              ;
        
        pooling_param_statements_   = pool_
                                      | kernel_size_
                                      | stride_
                                      ;  

        pooling_param_      = tok.pooling_param_ [PrintStr()]
                              >> tok.left_brace_
                              >> +pooling_param_statements_
                              >> tok.right_brace_
                              ; 

        inner_product_param_statements_ = num_output_
                                          | weight_filler_
                                          | bias_filler_
                                          ;      

        inner_product_param_ = tok.inner_product_param_ [PrintStr()]
                               >> tok.left_brace_
                               >> +inner_product_param_statements_
                               >> tok.right_brace_
                               ;   
        
        lrn_param_statements_   = local_size_ 
                                | alpha_
                                | beta_
                                ;

        lrn_param_          = tok.lrn_param_ [PrintStr()]
                              >> tok.left_brace_
                              >> +lrn_param_statements_
                              >> tok.right_brace_
                              ;

        dropout_param_statements_ = dropout_ratio_
                                    ;        


        dropout_param_      = tok.dropout_param_ [PrintStr()]
                              >> tok.left_brace_
                              >> +dropout_param_statements_
                              >> tok.right_brace_
                              ;  

        layer_statements_   =   name_
                                | type_
                                | bottom_
                                | top_
                                | param_
                                | convolution_param_
                                | pooling_param_
                                | inner_product_param_
                                | lrn_param_
                                | dropout_param_
                                | data_param_
                                | transform_param_
                                | memory_data_param_
                                | include_
                                ;        

        layer_          = tok.layer_ [PrintStr()] 
                          >> tok.left_brace_
                          >> +layer_statements_
                          >> tok.right_brace_
                          ;

        source_     = tok.source_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()];
        mean_file_  = tok.mean_file_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()];
        backend_    = tok.backend_ [PrintStr()] >> tok.colon_ >> tok.simple_identifier [PrintStr()];
        batch_size_ = tok.batch_size_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        crop_size_  = tok.crop_size_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        mirror_     = tok.mirror_   [PrintStr()]  >> tok.colon_ >> tok.simple_identifier [PrintStr()];
        phase_      = tok.phase_    [PrintStr()]  >> tok.colon_ >> tok.simple_identifier [PrintStr()];
        channels_   = tok.channels_ [PrintStr()]  >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        height_     = tok.height_   [PrintStr()]  >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        width_      = tok.width_    [PrintStr()]  >> tok.colon_ >> tok.unsigned_number [PrintInt()];

        memory_data_param_statements_ = batch_size_
                                        | channels_
                                        | height_
                                        | width_
                                        ;

        memory_data_param_ = tok.memory_data_param_ [PrintStr()]
                             >> tok.left_brace_
                             >> +memory_data_param_statements_
                             >> tok.right_brace_
                             ;

        include_statements_ = phase_
                              ;

        include_    = tok.include_ [PrintStr()] >> tok.colon_
                      >> tok.left_brace_
                      >> +include_statements_
                      >> tok.right_brace_
                      ;

        data_param_statements_ = source_
                                | backend_
                                | batch_size_
                                ;

        data_param_ = tok.data_param_
                      >> tok.left_brace_
                      >> +data_param_statements_
                      >> tok.right_brace_
                      ;

        transform_param_statements_ = crop_size_
                                     | mirror_
                                     | mean_file_
                                     ;

        transform_param_    = tok.transform_param_
                              >> tok.left_brace_
                              >> +transform_param_statements_
                              >> tok.right_brace_
                              ;
        
        mean_   = tok.mean_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];
        std_    = tok.std_ [PrintStr()] >> tok.colon_ >> tok.double_number [PrintDouble()];
        value_  = tok.value_ [PrintStr()] >> tok.colon_ >> tok.unsigned_number [PrintInt()];

        statement = name_
					| input_
                    | input_dim_
                    | output_dim_
                    | bottom_
                    | top_
                    | lr_mult_
                    | num_output_
                    | kernel_size_
                    | stride_
                    | pad_
                    | type_
                    | pool_
                    | alpha_
                    | beta_
                    | local_size_
                    | param_
                    | weight_filler_
                    | bias_filler_  
                    | input_shape_
                    | source_
                    | mean_file_        
                    | backend_
                    | batch_size_
                    | crop_size_
                    | mirror_
                    | phase_
                    | channels_
                    | height_
                    | width_
                    | data_param_
                    | transform_param_
                    | memory_data_param_
                    | include_
                    | dim_
                    | mean_
                    | std_
                    | value_
                    | layer_
                    ;

        start = +statement
                //>> eoi
                ;
    }
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > start, statement;
    
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > name_, input_, input_dim_, output_dim_, bottom_, top_,
                                                     lr_mult_, num_output_, kernel_size_, stride_, pad_, type_,
                                                     pool_, param_, param_statements_, weight_filler_, bias_filler_, 
                                                     layer_, layer_statements_, convolution_param_, convolution_param_statements_, 
                                                     pooling_param_, pooling_param_statements_, inner_product_param_, 
                                                     inner_product_param_statements_, weight_filler_statements_, 
                                                     bias_filler_statements_
                                                     ;
    
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > dim_, input_shape_, input_shape_statements_, decay_mult_, alpha_, beta_,
                                                     local_size_, lrn_param_, lrn_param_statements_, group_, dropout_ratio_,
                                                     dropout_param_, dropout_param_statements_, source_, mean_file_, backend_,
                                                     batch_size_, crop_size_, mirror_, phase_, channels_, height_, width_,
                                                     memory_data_param_, memory_data_param_statements_, include_, include_statements_
                                                     ;

    qi::rule<Iterator, qi::in_state_skipper<Lexer> > mean_, std_, value_, data_param_, data_param_statements_, transform_param_, 
                                                     transform_param_statements_
                                                     ;
};

