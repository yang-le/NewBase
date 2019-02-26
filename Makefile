SUBDIRS := base main node1 node2

all: subdirs

clean: subdirs

debug: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do CXXFLAGS='-D_GLIBCXX_USE_NANOSLEEP -Werror -Og -g' $(MAKE) -C $$dir; \
	done

subdirs: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do CXXFLAGS='-D_GLIBCXX_USE_NANOSLEEP -Werror -Ofast' LDFLAGS='-s' $(MAKE) -C $$dir $(MAKECMDGOALS); \
	done

cpplint:
	cpplint --recursive $(SUBDIRS)
