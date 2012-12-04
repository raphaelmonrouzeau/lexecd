AUTOMAKE_OPTIONS = foreign
SUBDIRS = src doc examples man scripts

# what flags you want to pass to the C compiler & linker
CFLAGS = -Wall -W -std=c99 -O2
LDFLAGS =
#
# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = lxd_check
lxd_check_SOURCES = lxd_check/main.c
sbin_PROGRAMS = lexecd
