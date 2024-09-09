test:*.cc
	g++ -o $@ $^ -std=c++14  -lprotobuf -lboost_filesystem -ljsoncpp -lgrpcpp -lgrpc
.PHONY:clean
clean:
	rm -r test