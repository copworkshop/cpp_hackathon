#include "PWInventory.h"

extern "C" {
    PWInventory* PWInventory_new() { return new PWInventory(); }
    void PWInventory_Load(PWInventory* p, const char* file) { p->Load(file); }
    void PWInventory_Save(PWInventory* p, const char* file) { p->Save(file); }
    void PWInventory_UpdateQuality(PWInventory* p) { p->UpdateQuality(); }
    int PWInventory_Count(PWInventory* p) { return p->Count(); }
    void PWInventory_delete(PWInventory* p) { delete p; }
}