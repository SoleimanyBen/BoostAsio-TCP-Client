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
		// Attempt read needs to be in it's own thread because it is blocking
		std::thread thread1([this]() { this->attempt_read(); });

		// Call wait_for_cin to get input from user to send to server
		wait_for_cin();
	}
}

void Session::attempt_read()
{
	auto self = shared_from_this();

	std::cout << "Calling again" << std::endl;

	std::size_t bytes_read = socket_.read_some(boost::asio::buffer(buffer_data_));
	buffer_data_[bytes_read] = '\0';

	std::cout << buffer_data_;

	attempt_read();
}

void Session::run()
{
	std::cout << "Made it" << std::endl;
}

void Session::attempt_write(std::string message)
{
	output_buffer_.resize(message.size());

	for (int i = 0; i < message.size(); ++i)
	{
		output_buffer_[i] = message[i];
	}

	auto self = shared_from_this();

	socket_.async_write_some(boost::asio::buffer(output_buffer_),
		[this, self](const boost::system::error_code& ec, std::size_t bytes_transferred)
		{
			if (!ec)
			{
				std::cout << "Message sent successfully" << std::endl;
			}
		});

	wait_for_cin();
}

void Session::wait_for_cin()
{
	std::string test;
	std::cin >> test;

	attempt_write(test);
}