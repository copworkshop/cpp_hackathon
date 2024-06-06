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

class PWInventory final  : public IPWInventory {

public:
	PWInventory(const std::vector<InventoryItem>& storage) : items(storage) {}
	PWInventory() = default;
	PWInventory(const PWInventory&) = delete;
	PWInventory& operator=(const PWInventory &) = delete;

	void Load(const std::string& file) override;
	void Save(const std::string& file) override;
	void UpdateQuality() override;
	InventoryItem& operator[](int index) override;
	int Count() const override;

protected:
	std::vector<InventoryItem> items;
};
