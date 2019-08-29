#include "requestcontroller.h"
#include "cdatabase.h"

extern cDatabase data;


requestController::requestController()
{

}


void requestController::service(HttpRequest &request, HttpResponse &response)
{
    qDebug()<<"===service===";
    QString path=request.getPath();
    if (path=="/api/v1/login") {
       response.write(data.login(request),true);
    }
    if (path.indexOf("/api/v1/tasks")==0) {
       response.write(data.tasks(request,path),true);
    }
    if (path.indexOf("/api/v1/file")==0) {
       //response.write("{\"good\":\"well\"}");
        QByteArray fn="file"; //request.getParameterMap().begin().key()
        qDebug()<<"uploaded file:"<<request.getParameterMap().value(fn);
        QTemporaryFile* file=request.getUploadedFile(fn);
        if (file)
        {
            qDebug()<<"file link:"<<file->fileName();
            auto s="D:/tmp/"+(request.getParameterMap()).value(fn);
            qDebug()<<"file link:"<<file->fileName()<<"target file:"<<s;
            QFile::copy(file->fileName(), s);
            response.write("{\"filename\":\""+s+"\"}");
        }
        else
        {
            response.write("upload failed");
        }
    }
    //curl -d {\"pkey\":\"G&jK\",\"task\":\"1\",\"file\":\"/path/filename\"}  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/task?appid=FFF01 -k

    //curl -d '{"login":"user","password":"user"}'  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/login?appid=FFF01
}
