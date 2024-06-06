#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <PWException.h>
#include "InventoryItem.h"

class IPWInventory
{
public:
	virtual void UpdateQuality() = 0;
	virtual void Load(const std::string& file) = 0;
	virtual void Save(const std::string& file) = 0;
	virtual InventoryItem& operator[](int index) = 0;
	virtual int Count() const = 0;
};

/**
 * @class PWInventory
 * @brief Represents an inventory of items in a game.
 * 
 * This class provides functionality to load and save the inventory from/to a file,
 * update the quality of items, access items by index, and count the number of items.
 */
class PWInventory final : public IPWInventory {

public:
    /**
     * @brief Constructs a PWInventory object with the given storage.
     * @param storage The vector of InventoryItem objects representing the initial storage.
     */
    PWInventory(const std::vector<InventoryItem>& storage) : items(storage) {}

    /**
     * @brief Default constructor for PWInventory.
     */
    PWInventory() = default;

    /**
     * @brief Deleted copy constructor for PWInventory.
     */
    PWInventory(const PWInventory&) = delete;

    /**
     * @brief Deleted copy assignment operator for PWInventory.
     */
    PWInventory& operator=(const PWInventory&) = delete;

    /**
     * @brief Loads the inventory from the specified file.
     * @param file The file path to load the inventory from.
     */
    void Load(const std::string& file) override;

    /**
     * @brief Saves the inventory to the specified file.
     * @param file The file path to save the inventory to.
     */
    void Save(const std::string& file) override;

    /**
     * @brief Updates the quality of all items in the inventory.
     */
    void UpdateQuality() override;

    /**
     * @brief Accesses the item at the specified index.
     * @param index The index of the item to access.
     * @return A reference to the InventoryItem at the specified index.
     */
    InventoryItem& operator[](int index) override;

    /**
     * @brief Counts the number of items in the inventory.
     * @return The number of items in the inventory.
     */
    int Count() const override;

protected:
    std::vector<InventoryItem> items; /**< The vector of InventoryItem objects representing the inventory storage. */
};
