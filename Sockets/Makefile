

# Constants
CXX = gcc
CFLAGS = -Wall -g
OBJS = server.o client.o network_utils.o



# run make for both client and server
all: server client



# compile executables
server: server.o
	$(CXX) $(CFLAGS) -o server server.o

client: client.o
	$(CXX) $(CFLAGS) -o client client.o



# compile object files
server.o: server.cpp network_utils.cpp
	$(CXX) $(CXXFLAGS) -c server.cpp

client.o: client.cpp network_utils.cpp
	$(CXX) $(CXXFLAGS) -c client.cpp

network_utils.o: network_utils.cpp
	$(CXX) $(CXXFLAGS) -c network_utils.cpp


# clean object files
clean:
	rm -f $(OBJS)
