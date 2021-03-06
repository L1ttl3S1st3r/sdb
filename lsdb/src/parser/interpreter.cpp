#include "interpreter.h"
#include <iostream>

std::list<std::shared_ptr<sdb::Any>> sdb::Interpreter::interpreterStack;
bool sdb::Interpreter::continueWork = true;

extern FILE* yyin;

sdb::Interpreter::Interpreter()
{

}

void sdb::Interpreter::work()
{
    std::cout << "welcome sdb command line!!!" << std::endl;
    std::cout << "ver. 1.0 beta" << std::endl;
    std::cout << "enter a SQL statement or \"exit;\" to quit" << std::endl;

    ::yyin = stdin;

    while(continueWork)
    {
        // parse input
        yyparse();

        // show stack content
//        std::cout << "stack:" << std::endl;

//        for (auto& name : interpreterStack)
//        {
//            std::cout << name->toString() << std::endl;
//        }

        try {
        std::cout << "interpreting..." << std::endl;

        if (!interpreterStack.empty())
        {
            // interpret it
            auto ptr = std::dynamic_pointer_cast<sdb::Operation>(interpreterStack.back());
            interpreterStack.pop_back();
            ptr->apply();

            interpreterStack.clear();
        }
        }
        catch (std::exception ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }
}
