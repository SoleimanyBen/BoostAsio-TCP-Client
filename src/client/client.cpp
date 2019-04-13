#include "client.h"

Client::Client(boost::asio::io_context& io_context, short port) : m_endpoint_(boost::asio::ip::address::from_string("127.0.0.1"), port), m_iocontext_(io_context) { }

void Client::do_connect()
{
	m_session_ = std::make_shared<Session>(m_iocontext_, m_endpoint_);



	m_session_->start_session();
}