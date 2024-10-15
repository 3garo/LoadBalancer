#include "LoadBalancer.h"
#include <iostream>

/**
 * @brief Main function to simulate the load balancer.
 * 
 * This program takes the number of servers and the duration of the simulation as user input
 * and runs the load balancer for the specified time.
 * 
 * @return int Returns 0 on successful execution.
 */
int main() {
    int numServers;  ///< Number of web servers for the load balancer.
    int duration;    ///< Duration of the load balancer simulation in seconds.

    // Get user input for the number of servers and simulation duration
    std::cout << "Enter the number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter the duration for the load balancer (in seconds): ";
    std::cin >> duration;
    
    // Initialize and start the load balancer simulation
    LoadBalancer loadBalancer(numServers);
    loadBalancer.startSimulation(duration);

    return 0;
}
