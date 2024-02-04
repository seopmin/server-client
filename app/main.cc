#include <iostream>

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);


// client가 요청 후 response를 받는 비동기 함수.
void GrabSomeData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if (!ec) {
                std::cout << "\n\nRead " << length << "bytes\n\n";

                for (int i=0; i<length; i++) 
                    std::cout << vBuffer[i];

                GrabSomeData(socket);
            }
        }
    );
}

int main()
{
    boost::system::error_code ec;

    // Create a "context" - essentially the platform specific interface
    boost::asio::io_context context;
    
    // Give some fake tasks to asio so the context doesnt finish 
    // (아래의 람다 함수가 끝나도 계속 실행되도록 함)
    boost::asio::io_context::work idleWork(context);

    // Start the context ( 응답을 받을 때 다른 스레드에서 비동기로 처리 따라서 socket에서 일어나는 I/O 서비스들이 메인 스레드가 아닌 다른 스레드에서 일어남 ex.socket.async_read_some())
    std::thread thrContext = std::thread([&]() { context.run(); });

    // Get the address of somewhere we wish to connect to
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("51.38.81.49", ec), 80);

    // Create a socket, the context will deliver the implementation
    boost::asio::ip::tcp::socket socket(context);

    // Tell socket to try and connect
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
    }

    context.stop();
    if (thrContext.joinable()) thrContext.join();


    return 0;
}