lib_LTLIBRARIES = libgtkplt.la

include_HEADERS = gtkplt.h

libgtkplt_la_SOURCES = gtkplt_plot_widget.c \
		       plot.c \
		       axis.c \
		       plotarea.c \
		       legend.c \
		       graphs.c \
		       labels.c \
		       margins.c \
		       title.c \
		       text.c
libgtkplt_la_CFLAGS = @GTK_CFLAGS@
libgtkplt_la_CFLAGS += -g -Wall -Wextra -Wpedantic
libgtkplt_la_CXXFLAGS =
libgtkplt_la_FCFLAGS =
libgtkplt_la_LDFLAGS = @GTK_LIBS@ -rdynamic -lm
