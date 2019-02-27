OUT := libbase.so

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))
OBJS += external/jsoncpp/jsoncpp.o

CXXFLAGS += -c -Wall -Wextra -I.. -fvisibility=hidden -fPIC -std=c++0x
LDFLAGS += -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUT) $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OUT)
