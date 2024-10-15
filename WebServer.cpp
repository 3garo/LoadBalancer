#include "WebServer.h"

/**
 * @brief Constructs a WebServer with a given ID.
 * 
 * @param id The unique identifier for the server.
 */
WebServer::WebServer(int id) : id(id), available(true) {}

/**
 * @brief Processes a request and logs the details of the request.
 * 
 * @param req The request to be processed.
 * @param logFile The log file where the server activity is recorded.
 */
void WebServer::processRequest(const Request& req, std::ofstream &logFile) {
    available = false; // Mark server as busy
    logFile << "WebServer " << id << " is processing request ID: " << req.id 
            << ", IP in: " << req.ipIn 
            << ", IP out: " << req.ipOut 
            << ", time: " << req.time 
            << ", job type: " << req.jobType << std::endl;
    available = true; // Mark server as available again
}

/**
 * @brief Checks if the server is available to process a request.
 * 
 * @return true if the server is available, false otherwise.
 */
bool WebServer::isAvailable() const {
    return available;
}
