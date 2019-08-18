#include "logincontroller.h"
#include "cdatabase.h"

extern cDatabase data;
loginController::loginController()
{

}


void loginController::service(HttpRequest &request, HttpResponse &response)
{

    QByteArray path=request.getPath();
    qDebug("loginConroller: path=%s",path.data());

    response.write(data.login(request),true);
    //curl -d '{"login":"user","password":"user"}'  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/login?appid=FFF01
}
