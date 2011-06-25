#include "Framework.h"
#include "OGLContext.h"


using namespace std;

// Function prototypes
void logRedirect();
void logUnredirect();

// Variables
streambuf *ferrbuf, *errbackup, *foutbuf, *outbackup;
ofstream ferrstr, foutstr;
OGLContext *ogc;

int main()
{
    logRedirect();

    ogc = new OGLContext();

    if(ogc)
        ogc->Render();

    logUnredirect();
}

void logRedirect()
{
    ferrstr.open("errlog.txt");
    foutstr.open("log.txt");

    // backup rdbufs
    errbackup = cerr.rdbuf();
    outbackup = cout.rdbuf();

    ferrbuf = ferrstr.rdbuf();
    foutbuf = foutstr.rdbuf();
    cerr.rdbuf(ferrbuf);
    cout.rdbuf(foutbuf);
}

void logUnredirect()
{
    cerr.rdbuf(errbackup);
    cout.rdbuf(outbackup);

    ferrstr.close();
    foutstr.close();
}
