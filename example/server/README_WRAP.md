# EST Server Wrapper

The EST server wrapper was built to facilitate easer server control during unit testing of a Java client library.

## Building
### On Linux 
Building on Linux has not been tried, but it a very standard C project and it should build out of the box.

### On Windows
Not tried.

### On OSX
Apple has moved away from using OpenSSL so the OpenSSL libraries that are available from Apple are old. You will need to install a newer
version of OpenSSL. A newer version can be installed via 'Homebrew', so if you have Homebrew installed you can do the following:

```
 brew update
 brew install openssl
```

Next you will need to run 
```
./configure --with-ssl-dir= <ssl install director>

#eg

./configure --with-ssl-dir=./configure --with-ssl-dir=/usr/local/Cellar/openssl/1.0.2k

#At the time of writing 1.0.2k was the OpenSSL version available.
```

Go ahead and make and install libest, this will build all the libraries.

The next thing you will need to do is make the newer openssl libraries available on your system. It was found that the loader would find the older versions shipped with OS before it would find the newer versions. This was resolved by linking:

```
    /usr/lib/libcrypto.dylib -> /usr/local/Cellar/openssl/1.0.2k/lib/libcrypto.1.0.0.dylib
    /usr/lib/libssl.dylib -> /usr/local/Cellar/openssl/1.0.2k/lib/libssl.1.0.0.dylib
```

To do this required a reboot into recovery mode to disable the system integrity checking otherwise even as root you will be unable to make the links.

See: http://www.imore.com/el-capitan-system-integrity-protection-helps-keep-malware-away



## Using the wrapper from Java

The wrapper does not use JNI but it is very easy to call from Java using JNA https://github.com/java-native-access/jna

The first thing you need to do is create the following classes:

```java
public interface CLibrary
        extends Library
    {
        int start_server(EstServerConfig config);

        void stop_server();
    }

    public class EstServerConfig
        extends Structure
    {
        public String srp;
        public boolean enforceCsr;
        public String httpAuthToken;
        public int manualEnroll;
        public boolean useDigestAuth;
        public boolean useBasicAuth;
        public boolean writeCSRToFile;
        public boolean disableHTTPAuth;
        public boolean disableHTTPWhenTLSSucceeds;
        public boolean verbose;
        public boolean enableCRLChecks;
        public boolean enableCheckPOPtoTLSUID;
        public boolean useIPV6;
        public int sleepDelay;
        public int tcpPort;
        public String serverCertPemFile;
        public String serverKeyPemFile;
        public String realm;
        public boolean fipsMode;
        public String estCSRAttr;
        public String estCACERTSResp;
        public String estTRUSTEDCerts;
        public String openSSLConfigFile; // Content of file not path to file


        protected List<String> getFieldOrder()
        {
            return Arrays.asList("srp",
                "enforceCsr",
                "httpAuthToken",
                "manualEnroll",
                "useDigestAuth",
                "useBasicAuth",
                "writeCSRToFile",
                "disableHTTPAuth",
                "disableHTTPWhenTLSSucceeds",
                "verbose",
                "enableCRLChecks",
                "enableCheckPOPtoTLSUID",
                "useIPV6",
                "sleepDelay",
                "tcpPort",
                "serverCertPemFile",
                "serverKeyPemFile",
                "realm",
                "fipsMode",
                "estCSRAttr",
                "estCACERTSResp",
                "estTRUSTEDCerts",
                "openSSLConfigFile"
            );
        }
    }

```

Then using JNH:

```java

final CLibrary server = (CLibrary)Native.loadLibrary("estserverwrap", CLibrary.class);

EstServerConfig config = new EstServerConfig();
// set configuration as desired.

Thread t = new Thread(new Runnable(){
        server.start_server(config); // This blocks..
    });

t.setPriority(Thread.MIN_PRIORITY);
t.start();

// At this point it is advisable to wait until the socket has been opened the server.
// Exercise the server.
server.stop_server();
```

NB: Running more than one instance at the same time has not be tested.


