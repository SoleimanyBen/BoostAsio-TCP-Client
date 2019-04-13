#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session>
{
private:
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::endpoint& ep_;

	char buffer_data_[1024];

public:
	Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint& ep);

	boost::asio::ip::tcp::socket& get_socket();

	void start_session();

	void attempt_connect();
	void attempt_read();
	void wait_for_cin();
	void run();
};