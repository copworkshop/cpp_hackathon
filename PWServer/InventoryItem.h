#pragma once

/**
 * @class InventoryItem
 * @brief Represents an item in the inventory.
 */
class InventoryItem
{
public:
    /**
     * @brief Default constructor for InventoryItem.
     */
    InventoryItem() = default;

    /**
     * @brief Constructor for InventoryItem.
     * @param name The name of the item.
     * @param sellBy The number of days left to sell the item.
     * @param value The value of the item.
     */
    InventoryItem(std::string name, int sellBy, int value) :
        name(name), sellBy(sellBy), value(value) {}

    std::string name; /**< The name of the item. */
    int sellBy; /**< The number of days left to sell the item. */
    int value; /**< The value of the item. */
};