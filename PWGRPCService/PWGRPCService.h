#ifndef PWGRPCSERVER_H
#define PWGRPCSERVER_H

#include <grpcpp/grpcpp.h>
#include "inventory.grpc.pb.h"

class InventoryServiceImpl final : public Inventory::Service {
    grpc::Status UpdateQuality(grpc::ServerContext* context, const UpdateQualityRequest* request, UpdateQualityResponse* response) override;
};

#endif // PWGRPCSERVER_H