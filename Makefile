SUBDIRS := base main node1 node2

all: subdirs

clean: subdirs

debug: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do CXXFLAGS='-Werror -Og -g' $(MAKE) -C $$dir; \
	done

subdirs: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do CXXFLAGS='-Werror -Ofast' LDFLAGS='-s' $(MAKE) -C $$dir $(MAKECMDGOALS); \
	done

cpplint:
	cpplint --quiet --recursive $(SUBDIRS)
