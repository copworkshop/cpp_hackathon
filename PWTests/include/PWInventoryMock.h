#include <gmock/gmock.h>
#include <PWInventory.h>

class PWInventoryMock : public IPWInventory {
public:
    MOCK_METHOD(void, UpdateQuality, (), (override));
    MOCK_METHOD(void, Load, (const std::string& file), (override));
    MOCK_METHOD(void, Save, (const std::string& file), (override));
    MOCK_METHOD(InventoryItem&, operator[], (int index), (override));
    MOCK_METHOD(int, Count, (), (const, override));
};