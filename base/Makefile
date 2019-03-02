OUT := libbase.so

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))
OBJS += external/jsoncpp/jsoncpp.o

CXXFLAGS += -c -Wall -Wextra -I.. -I../base/external -fvisibility=hidden -fPIC -std=c++0x
LDFLAGS += -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUT) $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -w -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OUT)
