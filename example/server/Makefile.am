lib_LTLIBRARIES = libestserverwrap.la
libestserverwrap_la_SOURCES = estserverwrap.c ossl_srv.c ../util/utils.c ../util/simple_server.c
AM_CFLAGS = -I$(SSL_CFLAGS) -I../.. -I$(SAFEC_CFLAGS)/include
libestserverwrap_la_LDFLAGS = -release $(PACKAGE_VERSION) -L../../src/est/.libs $(DL) $(PTHREAD) -lest -lssl -lcrypto
library_include_HEADERS = estserverwrap.h
library_includedir = ./


bin_PROGRAMS = estserver
estclient_includedir=$(includedir)/est
estserver_SOURCES = estserver.c
AM_CFLAGS = -I../.. -I$(srcdir)/../../src/est -I$(SSL_CFLAGS) -g
estserver_LDADD = libestserverwrap.la
if FREEBSD 
DL=
else
DL=-ldl
endif

if DISABLE_PTHREAD
PTHREAD=
else
PTHREAD=-lpthread
endif

estserver_LDFLAGS = -L../../src/est/.libs $(DL) $(PTHREAD) -lest -lssl -lcrypto 

EXTRA_DIST = ossl_srv.h apps.h createCA.sh ext.cnf ESTcommon.sh runserver.sh estExampleCA.cnf extExampleCA.cnf

