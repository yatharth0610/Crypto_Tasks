#include <bits/stdc++.h>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "main.grpc.pb.h"

using messenger::Num;
using messenger::Array;
using grpc::Status;
using namespace std;

class server_task final : public messenger::Messenger::Service {
    public:
        Status squareNum(grpc::ServerContext* context, grpc::ServerReaderWriter<Num, Num>* stream) override {
            Num in, out;
            stream->Read(&in);
            out.set_num(in.num()*in.num());
            stream->Write(out);
            return Status::OK;
        }

        Status sendNums(grpc::ServerContext* context, const Array* arr, ::google::protobuf::Empty* res) override {
            std::cout << "Received Numbers are :\n";
            for (int n : arr->arr()) {
                std::cout << n << std::endl;
            }

            return Status::OK; 
        } 
};

int main() {
    std::string server_address("0.0.0.0:50051");
    server_task service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address,  grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server Listening on " << server_address << std::endl;
    server->Wait();

    return 0;
}