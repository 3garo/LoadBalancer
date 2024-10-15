#include "LoadBalancer.h"
#include <fstream>
#include <sstream> // for generating random IPs

/**
 * @brief Generates a random IP address in the format XXX.XXX.XXX.XXX.
 * @return A randomly generated IP address as a string.
 */
std::string generateRandomIP() {
    std::stringstream ip;
    ip << rand() % 256 << "." << rand() % 256 << "." << rand() % 256 << "." << rand() % 256;
    return ip.str();
}

/**
 * @brief Constructs a LoadBalancer with an initial number of servers.
 * 
 * Initializes the number of servers, generates the initial request queue,
 * and opens the log file for logging events.
 * 
 * @param initialServers The number of servers to initialize.
 */
LoadBalancer::LoadBalancer(int initialServers) : initialServerCount(initialServers) {
    logFile.open("log.txt");
    for (int i = 0; i < initialServers; ++i) {
        servers.push_back(new WebServer(i)); // Dynamically allocate servers
    }
    generateInitialQueue(initialServers * 100); // Initial full queue
}

/**
 * @brief Destructor for LoadBalancer.
 * 
 * Deallocates dynamically allocated web servers and closes the log file.
 */
LoadBalancer::~LoadBalancer() {
    // Deallocate dynamically allocated web servers
    for (auto server : servers) {
        delete server;
    }
    logFile.close();
}

/**
 * @brief Generates an initial queue of requests.
 * 
 * This method generates a set number of requests, each with random IP addresses, 
 * processing time, and job type ('P' for processing or 'S' for streaming).
 * 
 * @param numRequests The number of initial requests to generate.
 */
void LoadBalancer::generateInitialQueue(int numRequests) {
    for (int i = 0; i < numRequests; ++i) {
        std::string ipIn = generateRandomIP();
        std::string ipOut = generateRandomIP();
        int time = rand() % 100; // Random time between 0 and 99
        char jobType = (rand() % 2 == 0) ? 'P' : 'S'; // Randomly choose between 'P' and 'S'

        Request req(i, ipIn, ipOut, time, jobType); // Use the new constructor
        requestQueue.addRequest(req);
    }
}

/**
 * @brief Adds new requests to the request queue.
 * 
 * Generates a specified number of new requests, each with random attributes.
 * Logs the details of each new request to the log file.
 * 
 * @param count The number of new requests to add to the queue.
 */
void LoadBalancer::addNewRequests(int count) {
    for (int i = 0; i < count; ++i) {
        std::string ipIn = generateRandomIP();
        std::string ipOut = generateRandomIP();
        int time = rand() % 100; // Random time between 0 and 99
        char jobType = (rand() % 2 == 0) ? 'P' : 'S'; // Randomly choose between 'P' and 'S'

        Request req(i, ipIn, ipOut, time, jobType); // Create a new request with all attributes
        requestQueue.addRequest(req);
        logFile << "Generated new request with ID: " << req.id 
                << ", IP in: " << req.ipIn 
                << ", IP out: " << req.ipOut 
                << ", time: " << req.time 
                << ", job type: " << req.jobType << std::endl;
    }
}

/**
 * @brief Starts the load balancing simulation.
 * 
 * Runs the simulation for a specified duration (in seconds), adjusting servers based on the
 * request load and generating new requests at random intervals. Logs queue size and server
 * status at the end of each cycle.
 * 
 * @param duration The number of seconds to run the simulation.
 */
void LoadBalancer::startSimulation(int duration) {
    int elapsed = 0;

    while (elapsed < duration) {
        // Process existing requests
        if (!requestQueue.isEmpty()) {
            for (auto& server : servers) {
                if (server->isAvailable() && !requestQueue.isEmpty()) {
                    Request req = requestQueue.getNextRequest();
                    server->processRequest(req, logFile);
                }
            }
        }

        // Adjust the number of servers based on request load
        adjustServers();

        // Randomly generate new requests at varying intervals
        int newRequestCount = rand() % 10 + 1; // Add between 1 to 10 new requests
        addNewRequests(newRequestCount); // Add new requests to the queue

        // Display queue size at the end of this cycle
        logFile << "Queue size at the end of cycle " << elapsed + 1 << ": " << requestQueue.size() << std::endl;

        logFile << "\n";
        elapsed++;
    }
}

/**
 * @brief Adjusts the number of servers based on the size of the request queue.
 * 
 * Adds or removes servers dynamically based on the number of requests in the queue.
 * Ensures that there is a minimum of one server and avoids over-provisioning.
 */
void LoadBalancer::adjustServers() {
    int activeRequests = requestQueue.size(); // Get the current number of requests in the queue

    // Determine the number of servers needed based on the queue size
    int requiredServers = (activeRequests / 10) + 1; // For example, add one server for every 10 requests

    // If the number of active requests is greater than the current number of servers, add servers
    if (activeRequests > servers.size() && requiredServers > servers.size()) {
        int newServers = requiredServers - servers.size(); // Calculate how many new servers to add
        for (int i = 0; i < newServers; ++i) {
            servers.push_back(new WebServer(servers.size())); // Dynamically allocate new servers
            logFile << "Added new WebServer " << (servers.size() - 1) << std::endl;
        }
    }
    // If there are too many servers compared to the requests, remove servers
    else if (activeRequests < servers.size() / 2) {
        int serversToRemove = servers.size() - (activeRequests / 10);
        
        // Ensure we do not go below the initial server count
        if (servers.size() - serversToRemove < initialServerCount) {
            serversToRemove = servers.size() - initialServerCount; // Adjust serversToRemove to maintain initialServerCount
        }

        for (int i = 0; i < serversToRemove && !servers.empty(); ++i) {
            delete servers.back(); // Deallocate the last server
            servers.pop_back(); // Remove from vector
            logFile << "Removed WebServer " << servers.size() << std::endl;
        }
    }
}
