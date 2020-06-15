#include <bits/stdc++.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/security/credentials.h>

#include "main.grpc.pb.h"

using messenger::Num;
using messenger::Array;
using messenger::Messenger;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using namespace std;

class client_task {
    private : 
        unique_ptr<Messenger::Stub> stub_;
    public:
        client_task (shared_ptr<Channel> channel) : stub_(Messenger::NewStub(channel)) {
            ;
        }

    void squareNum () {
        ClientContext context;

        shared_ptr < ClientReaderWriter <Num, Num> > stream (
            stub_->squareNum(&context));

        thread writer([stream]() {
            Num in;
            srand(time(0));
            in.set_num((rand())%1000);
            cout << "The random number generated was: " << in.num() << endl;
            stream->Write(in);
        });

        Num out;
        stream->Read(&out);
        cout << "The square of the number obtained from server is: " << out.num() << endl;

        stream->WritesDone();
        writer.join();
        Status status = stream->Finish();
        if (!status.ok()) {
            cout << "Rpc Chat Failed" << endl;  
        } else {
            std::cout << "Chat completed Successfully" << endl;
        }
    }

    void sendNums() {
        ClientContext context;
        Array a;
        srand(time(0));
        for (int i = 0; i < 10; i++) {
            a.add_arr(rand()%100000);
        }
        ::google::protobuf::Empty* empty;

        Status status = stub_->sendNums(&context, a, empty);
    }
};

int main() {
    client_task task (
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
    );

    int choice;
    cout << "What task do want to perform\n 1. Squaring a random number\n 2. Send a stream of random numbers.\n Enter 1 or 2 -> ";
    cin >> choice;

    switch (choice) {
        case 1 : cout << "Sending a random number for squaring\n";
                task.squareNum();
                break;

        case 2 : cout << "Sending a stream of random numbersn\n";
                task.sendNums();    
    }
    return 0;
}