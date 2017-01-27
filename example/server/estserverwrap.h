#ifndef HEADER_ESTSERVERWRAP_H 
#define HEADER_ESTSERVERWRAP_H 

// EstServerConfig holds the configuation
// for the server.
struct EstServerConfig {
	char *srp;
	int enforceCsr;
	char *httpAuthToken;
	int manualEnroll;
    int useDigestAuth;
    int useBasicAuth;
    int writeCSRToFile;
    int disableHTTPAuth;
    int disableHTTPWhenTLSSucceeds;
    int verbose;
    int enableCRLChecks;
    int enableCheckPOPtoTLSUID;
    int useIPV6;
    int sleepDelay;
    int tcpPort;
    char *serverCertPemFile;
    char *serverKeyPemFile;
    char *realm;
    int fipsMode;
    char *estCSRAttr;
    char *estCACERTSResp;
	char *estTRUSTEDCerts;   
	char *openSSLConfigFile; 
};

// Start Server will start the server and block until the
// stop_server is called.
int start_server (struct EstServerConfig *config);

// stop server causes the server to shutdown and release
// resources. It will block until shutdown is completed.
void stop_server();

#endif
