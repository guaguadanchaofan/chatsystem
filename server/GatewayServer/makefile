test:*.cc
	g++ -o $@ $^ -std=c++14 -g -lboost_filesystem -ljsoncpp  -lprotobuf `pkg-config --cflags --libs grpc++` -lhiredis
.PHONY:clean
clean:
	rm -r test