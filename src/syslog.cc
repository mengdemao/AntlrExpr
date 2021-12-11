#include <iostream>
#include <string>
#include <syslog.h>

using namespace std;

syslog::syslog(int addr, int port, int rank)
{
	this->addr = addr;

	if (!this->init) {
		this->port = port;
		this->rank = rank;
		this->init = this->connect();
	}
}

syslog::syslog(int rank)
{
	this->rank = rank;
}

syslog::syslog()
{
	// 测试初始化状态
	if (!this->init) {
		return;
	}

	this->addr = addr;
	this->port = port;
	this->rank = rank;

	this->init = this->connect();
}

syslog::~syslog()
{

}

bool syslog::connect()
{
	return true;
}

