CXX=g++
TESTEXE=server_surfer_test
BUILDARGS= -g -std=c++14
OBS=server_surfer.o curl_helper.o parse_helper.o execute.o

all : $(EXE) $(TESTEXE)

server_surfer.o : src/server_surfer.cpp
	$(CXX) $(BUILDARGS) -c -o server_surfer.o src/server_surfer.cpp

curl_helper.o : src/curl_helper.cpp
	$(CXX) $(BUILDARGS) -c -o curl_helper.o src/curl_helper.cpp

parse_helper.o : src/parse_helper.cpp
	$(CXX) $(BUILDARGS) -c -o parse_helper.o src/parse_helper.cpp

execute.o : src/execute.cpp
	$(CXX) $(BUILDARGS) -c -o execute.o src/execute.cpp


server_surfer_test : test/server_surfer_test.cpp test/catch.hpp server_surfer.o curl_helper.o parse_helper.o execute.o
	$(CXX) $(BUILDARGS) -o server_surfer_test test/server_surfer_test.cpp test/catch.hpp curl_helper.o parse_helper.o execute.o -lcurl

clean :
	rm $(TESTEXE) $(OBS)

