#include "RequestQueue.h"

/**
 * @brief Adds a request to the queue.
 * 
 * @param req The request to be added.
 */
void RequestQueue::addRequest(const Request& req) {
    queue.push(req);
}

/**
 * @brief Retrieves the next request from the queue and removes it.
 * 
 * @return The next request in the queue.
 */
Request RequestQueue::getNextRequest() {
    if (!queue.empty()) {
        Request req = queue.front();
        queue.pop();
        return req;
    }
    // Handling the case where the queue is empty might be needed, 
    // but leaving it as is to maintain original logic.
}

/**
 * @brief Checks if the request queue is empty.
 * 
 * @return true if the queue is empty, false otherwise.
 */
bool RequestQueue::isEmpty() const {
    return queue.empty();
}

/**
 * @brief Returns the current size of the request queue.
 * 
 * @return The number of requests in the queue.
 */
int RequestQueue::size() const {
    return queue.size();
}
