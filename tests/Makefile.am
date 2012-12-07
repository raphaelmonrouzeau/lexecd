TESTS = check_libjson

AM_CFLAGS = -Wall -W -std=c99 @CHECK_CFLAGS@
AM_LDFLAGS = $(top_builddir)/src/libjson/libjson.a @CHECK_LIBS@

check_PROGRAMS = check_libjson

check_libjson_SOURCES = check_libjson.c \
						check_libjson_till_eos.c \
						check_libjson_json_items_create.c \
						$(top_builddir)/src/libjson/till_eos.h \
						$(top_builddir)/src/libjson/json.h
