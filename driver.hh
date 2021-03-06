#ifndef __DRIVER_HH__
#define __DRIVER_HH__

#include <string>
#include <map>
#include "parser.hh"

#define YY_DECL \
    yy::parser::symbol_type yylex(driver &drv)

YY_DECL;

extern void start_parser();
extern void end_parser();

class driver
{
    public:
        driver()
            :trace_parsing(false), trace_scanning(false), emit_obj( false )
        {}

        std::string result;
        int parse(const std::string &f)
        {
            file = f;
            location.initialize (&file);
            scan_begin ();
            yy::parser parse (*this);
            parse.set_debug_level (trace_parsing);
            start_parser();
            int res = parse ();
            if( emit_obj )
                end_parser();
            scan_end ();
            return res;
        }

        std::string file;
        bool trace_parsing;

        void scan_begin();
        void scan_end();
        bool trace_scanning;
        bool emit_obj;

        yy::location location;

};

#endif
