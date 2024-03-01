#include <iostream>
#include <queue>
#include "olc_net.h"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};



class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
public:
	void PingServer()	
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerPing;

		// Caution with this...
		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();		

		msg << timeNow;
		Send(msg);
	}

	void MessageAll()
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::MessageAll;		
		Send(msg);
	}

	void TextMessageAll(std::string s)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::MessageAll;
		msg << s;
		Send(msg);
	}
};


int main()
{
	CustomClient c;
	// c.Connect("127.0.0.1", 60000);
	c.Connect("58.230.65.39", 80);

	bool key[3] = { false, false, false };
	bool old_key[3] = { false, false, false };

	bool bQuit = false;

	std::queue<std::string> q;

	std::string s;
	std::thread m_threadContext;

	try {
		m_threadContext = std::thread([&]() {
			while(1) {
				std::cin >> s;
				q.push(s);	
			}
		});
	} catch(std::exception& e) {
		std::cerr << "thread error: " << e.what() << '\n';
	}


	while (!bQuit)
	{
		// if (GetForegroundWindow() == GetConsoleWindow())
		// {
		// 	key[0] = GetAsyncKeyState('1') & 0x8000;
		// 	key[1] = GetAsyncKeyState('2') & 0x8000;
		// 	key[2] = GetAsyncKeyState('3') & 0x8000;
		// }

		// if (key[0] && !old_key[0]) c.PingServer();
		// if (key[1] && !old_key[1]) c.MessageAll();
		// if (key[2] && !old_key[2]) bQuit = true;

		if (q.size() > 0) {
			if (q.front() == "ping")
				c.PingServer();
			if (q.front() == "a")
				c.MessageAll();
			// c.TextMessageAll(q.front());
			q.pop();
		}

		for (int i = 0; i < 3; i++) old_key[i] = key[i];

		if (c.IsConnected())
		{
			if (!c.InComing().empty())
			{


				auto msg = c.InComing().pop_front().msg;

				switch (msg.header.id)
				{
				case CustomMsgTypes::ServerAccept:
				{
					// Server has responded to a ping request				
					std::cout << "Server Accepted Connection\n";
				}
				break;


				case CustomMsgTypes::ServerPing:
				{
					// Server has responded to a ping request
					std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
					std::chrono::system_clock::time_point timeThen;
					msg >> timeThen;
					std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
				}
				break;

				case CustomMsgTypes::ServerMessage:
				{
					// Server has responded to a ping request	
					uint32_t clientID;
					msg >> clientID;
					// std::string s;
					// msg >> s;
					std::cout << "Hello from [" << clientID << "]\n";
				}
				break;
				}
			}
		}
		else
		{
			std::cout << "Server Down\n";
			bQuit = true;
		}

	}
	if (m_threadContext.joinable()) m_threadContext.join();

	return 0;
}