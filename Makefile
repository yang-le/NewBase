SRCS := $(wildcard base/*.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

CXXFLAGS := -c -Iexternal -I. -fvisibility=hidden -fPIC -std=c++11
LDFLAGS := -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o libbase.so $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) libbase.so
