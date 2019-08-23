#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "httprequesthandler.h"
using namespace stefanfrings;


class requestController : public  HttpRequestHandler
{
        Q_OBJECT
        Q_DISABLE_COPY(requestController)
private:

public:
    requestController();

    // HttpRequestHandler interface
public:
    virtual void service(HttpRequest &request, HttpResponse &response) override;

};

#endif // LOGINCONTROLLER_H
