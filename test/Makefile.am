AM_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
AM_CFLAGS += -I$(top_srcdir)/src/

AM_LDFLAGS = -L$(top_builddir)/src/.libs -lgtkcairoplot
AM_LDFLAGS += @GTK_LIBS@ -rdynamic -lm

check_PROGRAMS = test

test_SOURCES = test.c
test_CFLAGS = $(AM_CFLAGS)
test_LDFLAGS = $(AM_LDFLAGS)

dist_noinst_SCRIPTS = test.sh

TEST_EXTENSIONS = .sh
SH_LOG_COMPILER = $(SHELL)

TESTS = $(dist_noinst_SCRIPTS)
