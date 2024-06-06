#pragma once

#include <nlohmann/json.hpp>

enum PWMessageTypes
{
	EchoRequest = 0,
	EchoResponse,
	GetInvRequest,
	GetInventoryRequest,
	GetInventoryResponse,
};

enum PWResponseStatus
{
	Failure = -1,
	Success,
};

/**
 * @brief The base class for serializable messages.
 * 
 * This class provides an interface for serializing and deserializing messages to/from JSON format.
 * Any class that wants to be serializable should inherit from this class and implement the
 * `ToJson` and `FromJson` methods.
 */
class PWSerializableMessage
{
public:
	/**
	 * @brief Serializes the message to a JSON object.
	 * 
	 * This method should be implemented by derived classes to convert the message
	 * into a JSON object representation.
	 * 
	 * @param j The JSON object to store the serialized data.
	 */
	virtual void ToJson(nlohmann::json& j) const = 0;

	/**
	 * @brief Deserializes the message from a JSON object.
	 * 
	 * This method should be implemented by derived classes to populate the message
	 * from a JSON object representation.
	 * 
	 * @param j The JSON object containing the serialized data.
	 */
	virtual void FromJson(const nlohmann::json& j) = 0;
};