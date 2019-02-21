SRCS := $(wildcard base/*.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

CXXFLAGS := -Iexternal -I. -fPIC -shared -std=gnu++11
LDFLAGS := -ldl -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o libbase.so $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) libbase.so
