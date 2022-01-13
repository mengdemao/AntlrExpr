/**
 * @file option.cc
 * @author mengdemao (mengdemao@163.com)
 * @brief 解析输入的命令行
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <config.h>
#include <cstdlib>
#include <option.h>
#include <version.h>
#include <iostream>
#include <cstddef>
#include <boost/program_options.hpp>

using namespace boost::program_options;
using namespace std;

/**
 * @brief 解析输入的命令行
 *
 * @param argc 输入参数个数
 * @param argv 输入参数内容
 * @return option_result 执行结果
 */
option_result option_main(int argc, char* argv[])
{
	try {
		variables_map variables_map;
		options_description description("Usage: AntlrExpr [options] text...");
		description.add_options()
            ("help,h",    "Display this information.")
            ("version,v", "Display compiler version information.")
            ("file,f", "Open file as input.")
            ("text,t", "Use string as input");

        store(parse_command_line(argc, argv, description), variables_map);
        notify(variables_map);

        if (1 == argc)
        {
            std::cout << description << "\n";
            return OPTION_FAILURE;
        }

        if (variables_map.count("help")) {
            std::cout << description << "\n";
            return OPTION_SUCCESS;
        }
		
		if (variables_map.count("version")) {
            std::cout << "AntlrExpr " << AntlrExpr_VERSION << " " << AntlrExpr_BUILD << "\n"
			"Copyright (C) 2022 MengDemao mengdemao19951021@163.com \n"
			"This is free software; see the source for copying conditions.  There is NO\n"
			"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
			<< std::endl;
            return OPTION_SUCCESS;
        }
    }
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return OPTION_FAILURE;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
		return OPTION_FAILURE;
    }

	return OPTION_NONEUSE;
}
