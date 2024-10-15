#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @brief Structure representing a Request.
 * 
 * A request contains an ID, incoming and outgoing IP addresses, 
 * processing time, and the type of job (processing or streaming).
 */
struct Request {
    int id;              ///< Request ID.
    std::string ipIn;    ///< Incoming IP address.
    std::string ipOut;   ///< Outgoing IP address.
    int time;            ///< Time required to process the request.
    char jobType;        ///< Job type: 'P' for processing, 'S' for streaming.

    /**
     * @brief Constructor for the Request struct.
     * 
     * @param id Unique identifier for the request.
     * @param ipIn Incoming IP address.
     * @param ipOut Outgoing IP address.
     * @param time Time required for the request to be processed.
     * @param jobType Type of job ('P' for processing, 'S' for streaming).
     */
    Request(int id, const std::string& ipIn, const std::string& ipOut, int time, char jobType)
        : id(id), ipIn(ipIn), ipOut(ipOut), time(time), jobType(jobType) {}
};

#endif
