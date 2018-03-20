#include "tcprelayobject.h"

TCPRelayObject::TCPRelayObject(QObject *parent, bool autoConnect) : QObject(parent), manager(NULL), relayState(-1), pending(false), commandVerified(false), deviceVerified(false), pendingCommand(-1)
{
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));

    if( autoConnect ){
        QNetworkConfiguration cfg;
        QNetworkConfigurationManager ncm;
        auto nc = ncm.allConfigurations();
        for (auto &x : nc)
        {
            if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
            {
                if (x.name() == "ESPap")
                    cfg = x;
            }
        }
        auto session = new QNetworkSession(cfg, this);
        session->open();
    }

    verify();
}

TCPRelayObject::~TCPRelayObject()
{
    delete manager;
}


void TCPRelayObject::verify()
{
    if( !pending ){
        request.setUrl(QUrl(QString("http://192.168.4.1/id")));
        manager->get(request);
        pending = true;
        pendingCommand = COMMAND_ID;
        commandVerified = false;
        deviceVerified = false;
    }
}
void TCPRelayObject::onSetRelayState(bool state)
{
    if( !pending ){
        request.setUrl(QUrl(QString("http://192.168.4.1/") + QString(state ? "on" : "off") ));
        manager->get(request);
        pending = true;
        commandVerified = false;
        pendingCommand = (state ? COMMAND_ON : COMMAND_OFF);
    }
}

void TCPRelayObject::onSetRelayOn()
{
    onSetRelayState(true);
}

void TCPRelayObject::onSetRelayOff()
{
    onSetRelayState(false);
}

void TCPRelayObject::managerFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        emit emitRelayError(reply->errorString());
        return;
    }

    QString answer = reply->readAll();

    switch( pendingCommand ){
    case COMMAND_ID:
        if( answer.compare(RESPONSE_ID)==0 ){
            deviceVerified = true;
            commandVerified = true;
            emit emitDeviceVerified(true);
        } else {
            emit emitDeviceVerified(false);
        }
        break;

    case COMMAND_ON:
        if( answer.compare(RESPONSE_ON)==0 ){
            commandVerified = true;
            relayState = 1;
            emit emitRelayState(relayState);
        }
        break;
    case COMMAND_OFF:
        if( answer.compare(RESPONSE_OFF)==0 ){
            commandVerified = true;
            relayState = 0;
            emit emitRelayState(relayState);
        }
        break;
    default:
        emit emitRelayError(QString("pending vs recieved mismatch"));
    }

    pending = false;
}
