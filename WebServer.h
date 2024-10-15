#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "Request.h" // Include the Request header

/**
 * @class WebServer
 * @brief Represents a web server that processes requests.
 */
class WebServer {
private:
    int id; // Server ID
    bool available; // Indicates if the server is available

public:
    /**
     * @brief Constructs a WebServer with a given ID.
     * 
     * @param id The unique identifier for the server.
     */
    WebServer(int id);

    /**
     * @brief Processes a request and logs the details of the request.
     * 
     * @param req The request to be processed.
     * @param logFile The log file where the server activity is recorded.
     */
    void processRequest(const Request& req, std::ofstream &logFile);

    /**
     * @brief Checks if the server is available to process a request.
     * 
     * @return true if the server is available, false otherwise.
     */
    bool isAvailable() const; // Check if server is available
};

#endif
