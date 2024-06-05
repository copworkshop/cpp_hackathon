from cffi import FFI

ffi = FFI()

# Specify the C interface to the PWInventory class
ffi.cdef("""
    typedef struct PWInventory PWInventory;
    PWInventory* PWInventory_new();
    void PWInventory_Load(PWInventory* p, const char* file);
    void PWInventory_Save(PWInventory* p, const char* file);
    void PWInventory_UpdateQuality(PWInventory* p);
    int PWInventory_Count(PWInventory* p);
    void PWInventory_delete(PWInventory* p);
""")

# Load the shared library
lib = ffi.dlopen('./libPWInventoryCWrapper.so')

# Now you can use the PWInventory class from Python
inventory = lib.PWInventory_new()
lib.PWInventory_Load(inventory, b'inventory.json')
lib.PWInventory_UpdateQuality(inventory)
lib.PWInventory_Save(inventory, b'inventory.json')

count = lib.PWInventory_Count(inventory)
lib.PWInventory_delete(inventory)