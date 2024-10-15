CXX = g++
CXXFLAGS = -std=c++11 -pthread
OBJ = main.o LoadBalancer.o WebServer.o Request.o RequestQueue.o

all: load_balancer

load_balancer: $(OBJ)
	$(CXX) $(CXXFLAGS) -o load_balancer $(OBJ)

main.o: main.cpp LoadBalancer.h
	$(CXX) $(CXXFLAGS) -c main.cpp

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h WebServer.h RequestQueue.h
	$(CXX) $(CXXFLAGS) -c LoadBalancer.cpp

WebServer.o: WebServer.cpp WebServer.h
	$(CXX) $(CXXFLAGS) -c WebServer.cpp

Request.o: Request.cpp Request.h
	$(CXX) $(CXXFLAGS) -c Request.cpp

RequestQueue.o: RequestQueue.cpp RequestQueue.h
	$(CXX) $(CXXFLAGS) -c RequestQueue.cpp

clean:
	rm -f load_balancer $(OBJ)
