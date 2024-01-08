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
#include <boost/program_options.hpp>
#include <config.h>
#include <cstddef>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <option.h>
#include <string>
#include <version.h>

using namespace boost::program_options;
using namespace std;

/**
 * @brief 解析输入的命令行
 *
 * @param argc 输入参数个数
 * @param argv 输入参数内容
 * @return option_result 执行结果
 */
option_result option_main(int argc, char* argv[], option_value &value)
{
	try {
		variables_map		variables_map;
		options_description description("Usage: AntlrExpr [options] text...");
		description.add_options()
					("help,h", 		"Display this information.")
					("version,v", 	"Display compiler version information.")
					("file,f", 		"Use file as input.")
					("text,t", 		"Use string as input")
					("pipe,p", 		"Use pipe as input")
					("debug,d", 	"Run as debug mode");

		store(parse_command_line(argc, argv, description), variables_map);
		notify(variables_map);

		if (1 == argc) {
			std::cout << description << "\n";
			return OPTION_FAILURE;
		}

		if (variables_map.count("help")) {
			std::cout << description << "\n";
			return OPTION_SUCCESS;
		}

		if (variables_map.count("version")) {
			std::cout << "AntlrExpr " << AntlrExpr_VERSION << " " << AntlrExpr_BUILD
					  << "\n"
						 "Copyright (C) 2024 MengDemao mengdemao19951021@163.com \n"
						 "This is free software; see the source for copying conditions.  There is NO\n"
						 "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
					  << std::endl;
			return OPTION_SUCCESS;
		}

		if (variables_map.count("file")) {
			std::cout << "file" << variables_map["file"].as<std::string>() << std::endl;
			return OPTION_SUCCESS;
		}

		if (variables_map.count("text")) {
			std::cout << "text" << variables_map["text"].as<std::string>() << std::endl;
			value.input_string = variables_map["text"].as<std::string>();
			return OPTION_SUCCESS;
		}

		if (variables_map.count("pipe")) {
			std::cout << "pipe" << variables_map["pipe"].as<std::string>() << std::endl;
			return OPTION_SUCCESS;
		}

		if (variables_map.count("debug")) {
			std::cout << "debug" << variables_map["debug"].as<std::string>() << std::endl;
			return OPTION_SUCCESS;
		}
	}
	catch (std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
		return OPTION_FAILURE;
	}
	catch (...) {
		std::cerr << "Exception of unknown type!\n";
		return OPTION_FAILURE;
	}

	return OPTION_NONEUSE;
}
