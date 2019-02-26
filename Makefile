SUBDIRS := base main node1 node2

all: subdirs

clean: subdirs

debug: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do CXXFLAGS='-Werror -Og -g' $(MAKE) -C $$dir; \
	done

subdirs: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do CXXFLAGS='-Werror -Ofast' $(MAKE) -C $$dir $(MAKECMDGOALS); \
	done

cpplint:
	cpplint --recursive $(SUBDIRS)
