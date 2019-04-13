#include "client/client.h"
#include <boost/asio.hpp>

int main()
{
	boost::asio::io_context io_context;

	std::shared_ptr<Client> client = std::make_shared<Client>(io_context, 6299);

	client->do_connect();

	io_context.run();
}