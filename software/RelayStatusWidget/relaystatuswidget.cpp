#include "relaystatuswidget.h"

RelayStatusWidget::RelayStatusWidget(QWidget *parent)
    : QWidget(parent)
{
    relay = new TCPRelayObject();

    statusLabel = new QLabel("relay disconnected");

    this->setLayout(new QVBoxLayout());
    relayToggleButton = new QPushButton("TOGGLE RELAY");
    relayToggleButton->setCheckable(true);

    this->layout()->addWidget(relayToggleButton);
    this->layout()->addWidget(statusLabel);


    connect(relayToggleButton, SIGNAL(clicked(bool)), relay, SLOT(onSetRelayState(bool)));
    connect(relay, SIGNAL(emitDeviceVerified(bool)), this, SLOT(onRelayVerified(bool)));
    connect(relay, SIGNAL(emitRelayState(bool)), this, SLOT(onRelayStateChanged(bool)));
    connect(relay, SIGNAL(emitRelayError(QString)), this, SLOT(onRelayError(QString)));
}

RelayStatusWidget::~RelayStatusWidget()
{

}

void RelayStatusWidget::onRelayError(QString err)
{
    statusLabel->setText(err);
}

void RelayStatusWidget::onRelayVerified(bool con)
{
    statusLabel->setText(QString("RELAY ") + QString(con ? "IS " : "IS NOT ") + QString("CONNECTED"));
}

void RelayStatusWidget::onRelayStateChanged(bool newState)
{
    statusLabel->setText(QString("RELAY IS ") + QString(newState ? "ON" : "OFF"));
}
