OUT := main

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

CXXFLAGS += -c -Wall -Wextra -I.. -std=c++0x
LDFLAGS += -L../base -lbase -ldl -pthread

all: $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(OUT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OUT)
