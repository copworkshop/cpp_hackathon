/**
 * @file PWInventory.h
 * @brief This file contains the IPWInventory interface and the PWInventory class.
 */

#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <PWException.h>
#include "InventoryItem.h"

/**
 * @interface IPWInventory
 * @brief This interface represents a PWInventory.
 */
class IPWInventory
{
public:
	/**
	 * @brief Updates the quality of the inventory.
	 */
	virtual void UpdateQuality() = 0;

	/**
	 * @brief Loads the inventory from a file.
	 * @param file The file to load the inventory from.
	 */
	virtual void Load(const std::string &file) = 0;

	/**
	 * @brief Saves the inventory to a file.
	 * @param file The file to save the inventory to.
	 */
	virtual void Save(const std::string &file) = 0;

	/**
	 * @brief Accesses an item in the inventory.
	 * @param index The index of the item to access.
	 * @return The item at the specified index.
	 */
	virtual InventoryItem &operator[](int index) = 0;

	/**
	 * @brief Gets the count of items in the inventory.
	 * @return The count of items in the inventory.
	 */
	virtual int Count() const = 0;
};

/**
 * @class PWInventory
 * @brief This class represents a PWInventory.
 */
class PWInventory final : public IPWInventory
{

public:
	/**
	 * @brief Constructs a PWInventory with the specified items.
	 * @param storage The items to initialize the inventory with.
	 */
	PWInventory(const std::vector<InventoryItem> &storage) : items(storage) {}

	/**
	 * @brief Default constructor for PWInventory.
	 */
	PWInventory() = default;

	/**
	 * @brief Copy constructor for PWInventory is deleted.
	 */
	PWInventory(const PWInventory &) = delete;

	/**
	 * @brief Copy assignment operator for PWInventory is deleted.
	 */
	PWInventory &operator=(const PWInventory &) = delete;

	/**
	 * @brief Loads the inventory from a file.
	 * @param file The file to load the inventory from.
	 */
	void Load(const std::string &file) override;

	/**
	 * @brief Saves the inventory to a file.
	 * @param file The file to save the inventory to.
	 */
	void Save(const std::string &file) override;

	/**
	 * @brief Updates the quality of the inventory.
	 */
	void UpdateQuality() override;

	/**
	 * @brief Accesses an item in the inventory.
	 * @param index The index of the item to access.
	 * @return The item at the specified index.
	 */
	InventoryItem &operator[](int index) override;

	/**
	 * @brief Gets the count of items in the inventory.
	 * @return The count of items in the inventory.
	 */
	int Count() const override;

protected:
	/**
	 * @brief The items in the inventory.
	 */
	std::vector<InventoryItem> items;
};