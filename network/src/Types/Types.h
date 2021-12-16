#pragma once
#include <cstdint>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>


#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#include "../Connection/Connection.h"

#include "SFML/Graphics.hpp"
        enum class GameMsg : uint32_t {
            Server_GetStatus,
            Server_GetPing,

            Client_Accepted,
            Client_AssignID,
            Client_RegisterWithServer,
            Client_UnregisterWithServer,

            Game_AddPlayer,
            Game_RemovePlayer,
            Game_UpdatePlayer,
        };

        struct sPlayerDescription {
            uint32_t nUniqueID = 0;
            uint32_t nAvatarID = 0;

            uint32_t nHealth = 100;
            uint32_t nAmmo = 20;
            uint32_t nKills = 0;
            uint32_t nDeaths = 0;

            sf::Vector2f  vPos;
            sf::Vector2f vVel;
        };

        		template <typename T>
		struct message_header {
			T id {};
			uint32_t size = 0;
		};

		template <typename T>
		struct message {
			message_header<T> header {};
			std::vector<uint8_t> body;

			size_t size() const {
				return body.size();
			}

			friend std::ostream& operator << (std::ostream& os, const message<T>& msg) {
				os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
				return os;
			}


			template<typename DataType>
			friend message<T>& operator << (message<T>& msg, const DataType& data) {

				size_t i = msg.body.size();

				msg.body.resize(msg.body.size() + sizeof(DataType));

				std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

				msg.header.size = msg.size();

				return msg;
			}

			template<typename DataType>
			friend message<T>& operator >> (message<T>& msg, DataType& data) {

				size_t i = msg.body.size() - sizeof(DataType);

				std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

				msg.body.resize(i);

				msg.header.size = msg.size();

				return msg;
			}			
		};



		template <typename T>
		struct owned_message {
			std::shared_ptr<network::Connection<T>> remote = nullptr;
			message<T> msg;

			friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg) {
				os << msg.msg;
				return os;
			}
		};


