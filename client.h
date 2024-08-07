// Created by mypzuk on 3/15/24.
#include <iostream>
#include <string>
#include <SFML/Network.hpp>

class account{
    std::string name;
    std::string password;
};

class client_s{
public:
    sf::TcpSocket* socet;
    int status;
    int id;
    account ac;
};

void get_client(client_s cl){
    std::cout<< "client id: " << cl.id << ", status: "<< cl.status << std::endl;
}
