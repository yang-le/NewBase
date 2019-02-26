SUBDIRS := base main node1 node2

all: subdirs

clean: subdirs

subdirs: $(SUBDIRS)
	for dir in $(SUBDIRS); \
	do $(MAKE) -C $$dir $(MAKECMDGOALS); \
	done

cpplint:
	cpplint --recursive $(SUBDIRS)
