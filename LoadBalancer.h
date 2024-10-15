#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>

/**
 * @class LoadBalancer
 * @brief Manages a set of web servers and distributes requests among them.
 * 
 * The LoadBalancer class simulates a dynamic load balancing system by
 * managing the allocation and deallocation of web servers based on request load.
 * It can generate new requests at random intervals and adjust the number of servers accordingly.
 */
class LoadBalancer {
private:
    std::vector<WebServer*> servers;  ///< Dynamic collection of web servers.
    RequestQueue requestQueue;        ///< Queue for holding and processing requests.
    int totalTime;                    ///< Total time to run the load balancer in seconds.
    std::ofstream logFile;            ///< Log file to record the simulation events.
    int initialServerCount;           ///< Store the initial number of servers for baseline adjustments.

public:
    /**
     * @brief Constructor that initializes the load balancer with a specified number of servers.
     * @param initialServers The number of servers to start the load balancer with.
     */
    LoadBalancer(int initialServers);

    /**
     * @brief Destructor that cleans up dynamically allocated memory (web servers).
     */
    ~LoadBalancer();

    /**
     * @brief Generates an initial request queue with the given number of requests.
     * @param numRequests The number of initial requests to populate the request queue.
     */
    void generateInitialQueue(int numRequests);

    /**
     * @brief Starts the load balancer simulation for a given duration.
     * @param duration The duration for which the load balancer runs, in seconds.
     */
    void startSimulation(int duration);

    /**
     * @brief Adds new requests to the queue during runtime.
     * @param count The number of new requests to add to the request queue.
     */
    void addNewRequests(int count);

    /**
     * @brief Adjusts the number of web servers based on the current load (request queue size).
     */
    void adjustServers();
};

#endif // LOADBALANCER_H
