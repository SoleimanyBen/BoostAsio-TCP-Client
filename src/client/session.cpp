#include <iostream>
#include "session.h"
#include <boost/asio.hpp>


Session::Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint& ep) : socket_(io_context), ep_(ep) { }

boost::asio::ip::tcp::socket& Session::get_socket()
{
	return socket_;
}

void Session::start_session()
{
	boost::system::error_code ec;

	socket_.connect(ep_, ec);
	 
	if (ec)
		std::cout << "Error connecting to server: " << ec.message() << std::endl;

	if (!ec)
	{
		run();
		attempt_read();
	}
}

void Session::attempt_connect()
{
}

void Session::run()
{
	attempt_read();
}

void Session::attempt_read()
{
	auto self = shared_from_this();

	socket_.async_read_some(boost::asio::buffer(&buffer_data_, sizeof(buffer_data_)),
		[this, self](const boost::system::error_code & ec, std::size_t bytes_transferred)
		{
			if (!ec)
			{
				
				//buffer_data_[bytes_transferred] = '\0';
				std::cout << buffer_data_;

				run();
			}

			if (ec)
			{
				std::cout << ec.message() << std::endl;
			}
		});
}

void Session::wait_for_cin()
{
	std::string test;
	std::cin >> test;
}