OUT := libbase.so

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

CXXFLAGS += -c -Wall -Wextra -I.. -I../base/external -fvisibility=hidden -fPIC -std=c++0x
LDFLAGS += -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUT) $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OUT)
