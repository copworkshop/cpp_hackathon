/**
 * @file PWMessageTypes.h
 * @brief This file contains the declaration of message types and response status.
 */

#pragma once

#include <nlohmann/json.hpp>

/**
 * @enum PWMessageTypes
 * @brief Enum for different types of messages.
 */
enum PWMessageTypes
{
	EchoRequest = 0, /**< Echo request message type */
	EchoResponse, /**< Echo response message type */
	GetInvRequest, /**< Get inventory request message type */
	GetInventoryRequest, /**< Another type of get inventory request message type */
	GetInventoryResponse, /**< Get inventory response message type */
};

/**
 * @enum PWResponseStatus
 * @brief Enum for response status.
 */
enum PWResponseStatus
{
	Failure = -1, /**< Failure status */
	Success, /**< Success status */
};

/**
 * @class PWSerializableMessage
 * @brief Abstract class for serializable messages.
 *
 * This class provides an interface for serializing and deserializing messages to/from JSON format.
 */
class PWSerializableMessage
{
public:

	/**
	 * @brief Convert the object to JSON format.
	 * @param j JSON object to hold the serialized data.
	 */
	virtual void ToJson(nlohmann::json& j) const = 0;

	/**
	 * @brief Populate the object from JSON format.
	 * @param j JSON object that contains the data.
	 */
	virtual void FromJson(const nlohmann::json& j) = 0;
};