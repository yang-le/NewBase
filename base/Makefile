OUT := libbase.so

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

CXXFLAGS += -c -Wall -I../external -I.. -fvisibility=hidden -fPIC -std=c++11
LDFLAGS += -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUT) $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OUT)
