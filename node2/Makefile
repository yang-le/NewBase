OUT := libnode2.so

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

CXXFLAGS += -c -Wall -Wextra -I../external -I.. -fvisibility=hidden -fPIC -std=c++0x
LDFLAGS += -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUT) $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OUT)
