TARGETS = bitfield bandit bandit_with_gmock googlemock

BITFIELD_VERSION = ts_processor_extension
BANDIT_VERSION = v1.1.4
BANDIT_WITH_GMOCK_VERSION = v1.1.1
GOOGLEMOCK_VERSION = 1.7.0


.PHONY: all
all: ${TARGETS}

.PHONY: clean
clean:
	${RM} -r ${TARGETS}

.PHONY: rebuild
rebuild: clean all


bitfield:
	git clone https://github.com/mrk21/bitfield.git $@
	cd $@ && git checkout ${BITFIELD_VERSION}

googlemock:
	svn checkout http://googlemock.googlecode.com/svn/tags/release-${GOOGLEMOCK_VERSION} $@
	cd $@ && cmake . && make

bandit_with_gmock:
	git clone https://github.com/mrk21/bandit_with_gmock.git $@
	cd $@ && git checkout ${BANDIT_WITH_GMOCK_VERSION}

bandit:
	git clone https://github.com/joakimkarlsson/bandit.git $@
	cd $@ && git checkout ${BANDIT_VERSION}
