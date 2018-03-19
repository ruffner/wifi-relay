#ifndef RELAYSTATUSWIDGET_H
#define RELAYSTATUSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include "../../tcprelayobject.h"

class RelayStatusWidget : public QWidget
{
    Q_OBJECT

public:
    RelayStatusWidget(QWidget *parent = 0);
    ~RelayStatusWidget();

private:
    QLabel *statusLabel;
    QPushButton *relayToggleButton;
    TCPRelayObject *relay;

private slots:
    void onRelayError(QString err);
    void onRelayVerified(bool);
    void onRelayStateChanged(bool state);
};

#endif // RELAYSTATUSWIDGET_H
