#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "session.h"
#include <boost/asio.hpp>

class Client
{
private:
	boost::asio::ip::tcp::endpoint m_endpoint_;
	boost::asio::io_context& m_iocontext_;

	std::shared_ptr<Session> m_session_;

public:
	Client(boost::asio::io_context& io_context, short port);

	void do_connect();

};


#endif