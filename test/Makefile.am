AM_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
AM_CFLAGS += -I$(top_srcdir)/src/

AM_LDFLAGS = -L$(top_builddir)/src/.libs -lgtkplt
AM_LDFLAGS += @GTK_LIBS@ -rdynamic -lm

check_PROGRAMS = gtk \
		 gtk_cairo \
		 gtkplt_widget \
		 plot_title \
		 axis_titles

gtk_SOURCES = gtk.c
gtk_CFLAGS = $(AM_CFLAGS)
gtk_LDFLAGS = $(AM_LDFLAGS)

gtk_cairo_SOURCES = gtk_cairo.c
gtk_cairo_CFLAGS = $(AM_CFLAGS)
gtk_cairo_LDFLAGS = $(AM_LDFLAGS)

gtkplt_widget_SOURCES = gtkplt_widget.c
gtkplt_widget_CFLAGS = $(AM_CFLAGS)
gtkplt_widget_LDFLAGS = $(AM_LDFLAGS)

plot_title_SOURCES = plot_title.c
plot_title_CFLAGS = $(AM_CFLAGS)
plot_title_LDFLAGS = $(AM_LDFLAGS)

axis_titles_SOURCES = axis_titles.c
axis_titles_CFLAGS = $(AM_CFLAGS)
axis_titles_LDFLAGS = $(AM_LDFLAGS)

dist_noinst_SCRIPTS = gtk.sh \
		      gtk_cairo.sh \
		      gtkplt_widget.sh \
		      plot_title.sh \
		      axis_titles.sh

TEST_EXTENSIONS = .sh
SH_LOG_COMPILER = $(SHELL)

TESTS = $(dist_noinst_SCRIPTS)
