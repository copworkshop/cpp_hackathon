import tornado.ioloop
import tornado.web
import json
from cffi import FFI

# PWInventory setup
ffi = FFI()
ffi.cdef("""
    typedef struct PWInventory PWInventory;
    PWInventory* PWInventory_new();
    void PWInventory_Load(PWInventory* p, const char* file);
    void PWInventory_Save(PWInventory* p, const char* file);
    void PWInventory_UpdateQuality(PWInventory* p);
    int PWInventory_Count(PWInventory* p);
    void PWInventory_delete(PWInventory* p);
""")
lib = ffi.dlopen('./libPWInventoryCWrapper.so')
inventory = lib.PWInventory_new()
lib.PWInventory_Load(inventory, b'inventory.json')

class StockHandler(tornado.web.RequestHandler):
    def get(self):
        count = lib.PWInventory_Count(inventory)
        self.write(json.dumps({"inventory": count}))

class UpdateHandler(tornado.web.RequestHandler):
    def post(self):
        lib.PWInventory_UpdateQuality(inventory)
        lib.PWInventory_Save(inventory, b'inventory.json')

        self.write("Inventory updated")

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Hello, world")

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        (r"/stock", StockHandler),
        (r"/update", UpdateHandler),

    ])

if __name__ == "__main__":
    app = make_app()
    app.listen(3000)
    tornado.ioloop.IOLoop.current().start()
