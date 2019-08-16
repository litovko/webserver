#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "httprequesthandler.h"
using namespace stefanfrings;


class loginController : public  HttpRequestHandler
{
        Q_OBJECT
        Q_DISABLE_COPY(loginController)

public:
    loginController();

    // HttpRequestHandler interface
public:
    virtual void service(HttpRequest &request, HttpResponse &response) override;
};

#endif // LOGINCONTROLLER_H
