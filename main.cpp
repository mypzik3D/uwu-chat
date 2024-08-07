#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "client.h"

short int port = 4000;

int main(){
    sf::TcpListener listener;
    std::vector<client_s*> clients;

    listener.setBlocking(false);
    if (listener.listen(port) != sf::Socket::Done){
        std::cout << "Error < please restart programm." << std::endl;
        return 1;
    }

    std::cout << "Server is started!" << std::endl;

    while (true){
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) == sf::Socket::Done){
            client->setBlocking(false);
            client_s* cl;
            cl->socet = client;
            cl->socet->setBlocking(false);
            cl->id = clients.size()+1;
            clients.push_back(cl);
            get_client(*clients.back());
        }

	for(int i = 0;i < clients.size();i++) {
            sf::Packet pac;

            int command = 0;
            int data;
            std::string text;

            if (clients.at(i)->socet->receive(pac) == sf::Socket::Done)
                pac >> command >> data >> text;

            if (command != 0) {
                sf::Packet packet;
                packet.clear();

                if (command == 2) {
                    std::cout << clients.at(i)->id << " get id" << std::endl;
                    packet << command << i + 1 << text;
                    clients.at(i)->socet->send(packet);
                }
            }
        }
    }
    for(int i = 0; i < clients.size(); i++){
        delete clients.at(i);
    }
    return 0;
}
