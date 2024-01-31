#include <iostream>

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(boost::asio::ip::tcp::socket& socket) {
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
        [&] (std::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "\n\nRead " <<length << " bytes\n\n";

                for (int i=0; i<length; i++) 
                    std::cout << vBuffer[i];

                GrabSomeData(socket);
            }
        }

    );
}


int main() {
    std::cout << "minseop" << std::endl;


    boost::system::error_code ec;

    boost::asio::io_context context;

    boost::asio::io_context::work idleWork(context);

    std::thread thrContext = std::thread([&]() { context.run(); });

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);

    boost::asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec) {
        std::cout << "Connected!" << std::endl;
    } else {
        std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
    }

    if (socket.is_open()) {

        GrabSomeData(socket);

        std::string sRequest = 
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);

        context.stop();
        if (thrContext.joinable()) thrContext.join();
        
    }

    return 0;
}