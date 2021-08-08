AM_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
AM_CFLAGS += -I$(top_srcdir)/src/

AM_LDFLAGS = -L$(top_builddir)/src/.libs -lgtkplt
AM_LDFLAGS += @GTK_LIBS@ -rdynamic -lm

check_PROGRAMS = gtk

gtk_SOURCES = gtk.c
gtk_CFLAGS = $(AM_CFLAGS)
gtk_LDFLAGS = $(AM_LDFLAGS)

dist_noinst_SCRIPTS = gtk.sh

TEST_EXTENSIONS = .sh
SH_LOG_COMPILER = $(SHELL)

TESTS = $(dist_noinst_SCRIPTS)
