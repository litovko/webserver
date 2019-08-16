/**
  @file
  @author Stefan Frings
*/

#include "requesthandler.h"
#include "filelogger.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "controllers/logincontroller.h"


/** Logger class */
extern Logger* logger;

RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent)
{}

void RequestHandler::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    QJsonObject recordObject;
    recordObject["FirstName"] = "John";
    recordObject["LastName"] = "Doe";
    recordObject["Age"]= 43;
    recordObject["Sex"] = "Male";

    QJsonObject addressObject;
    addressObject.insert("Street", "Downing Street 10");
    addressObject.insert("City", "London");
    addressObject.insert("Country", "Great Britain");
    recordObject.insert("Address", addressObject);

    QJsonArray phoneNumbersArray;
    phoneNumbersArray.push_back("+44 1234567");
    phoneNumbersArray.push_back("+44 2345678");
    recordObject.insert("Phone Numbers", phoneNumbersArray);

    QJsonDocument doc(recordObject);
    qDebug() << doc.toJson();
    qDebug("Conroller: path=%s",path.data());

    // Set a response header
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");

    // Return a simple HTML document
    //response.write(doc.toJson(),true);
    if (path=="/api/v1/login") {
        loginController().service(request,response);
    }
    qDebug("Conroller: finished request");
    qDebug()<<"=== info begin ===";
    qDebug()<<"Hdr map : "<<request.getHeaderMap();
    qDebug()<<"Path    : "<<request.getPath();
    qDebug()<<"Method  : "<<request.getMethod();
    qDebug()<<"Raw path: "<<request.getRawPath();
    qDebug()<<"Par map : "<<request.getParameterMap();
    qDebug()<<"Body    : "<<request.getBody();
    qDebug()<<"=== info  end  ===";

    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
}
