#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

/**
 * @brief The RequestQueue class handles a queue of requests.
 */
class RequestQueue {
private:
    std::queue<Request> queue; ///< A queue to hold incoming requests.

public:
    /**
     * @brief Adds a request to the queue.
     * 
     * @param req The request to be added.
     */
    void addRequest(const Request& req);

    /**
     * @brief Retrieves the next request from the queue and removes it.
     * 
     * @return The next request in the queue.
     */
    Request getNextRequest();

    /**
     * @brief Checks if the request queue is empty.
     * 
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Returns the number of requests in the queue.
     * 
     * @return The size of the queue.
     */
    int size() const;
};

#endif // REQUESTQUEUE_H
