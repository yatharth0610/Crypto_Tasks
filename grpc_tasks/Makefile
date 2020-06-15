HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/home/yatharth/Documents/crypto_tasks/lib `pkg-config --libs protobuf grpc++`\
           -isystem /home/yatharth/Documents/crypto_tasks/include\
					 -pthread\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/home/yatharth/Documents/crypto_tasks/lib `pkg-config --libs protobuf grpc++`\
            -isystem /home/yatharth/Documents/crypto_tasks/include\
           -pthread\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
PROTOC = /home/yatharth/Documents/crypto_tasks/bin/protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = .

vpath %.proto $(PROTOS_PATH)

all: main.pb.cc main.grpc.pb.cc main.pb.o main.grpc.pb.o main_client main_server

main_client: main.pb.o main.grpc.pb.o main_client.o
	$(CXX) $^ $(LDFLAGS) -o $@

main_server: main.pb.o main.grpc.pb.o main_server.o
	$(CXX) $^ $(LDFLAGS) -o $@

%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h main_client main_server