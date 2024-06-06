/**
 * @file InventoryItem.h
 * @brief This file contains the InventoryItem class.
 */

#pragma once

/**
 * @class InventoryItem
 * @brief This class represents an item in an inventory.
 */
class InventoryItem
{
public:
	/**
	 * @brief Default constructor for InventoryItem.
	 */
	InventoryItem() = default;

	/**
	 * @brief Name of the inventory item.
	 */
	std::string name;

	/**
	 * @brief The sell-by date of the inventory item.
	 */
	int sellBy;

	/**
	 * @brief The value of the inventory item.
	 */
	int value;

	/**
	 * @brief Constructor for InventoryItem that initializes name, sellBy, and value.
	 * @param name The name of the inventory item.
	 * @param sellBy The sell-by date of the inventory item.
	 * @param value The value of the inventory item.
	 */
	InventoryItem(std::string name, int sellBy, int value) : name(name), sellBy(sellBy), value(value) {}
};