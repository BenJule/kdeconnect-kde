/**
 * Copyright 2013 Albert Vaca <albertvaka@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOCKETLINEREADER_H
#define SOCKETLINEREADER_H

#include <QObject>
#include <QQueue>
#include <QSslSocket>
#include <QHostAddress>

#include <kdeconnectcore_export.h>

/*
 * Encapsulates a QTcpSocket and implements the same methods of its API that are
 * used by LanDeviceLink, but readyRead is emitted only when a newline is found.
 */
class KDECONNECTCORE_EXPORT SocketLineReader
    : public QObject
{
    Q_OBJECT

public:
    explicit SocketLineReader(QSslSocket* socket, QObject* parent = nullptr);

    QByteArray readLine() { return mPackages.dequeue(); }
    qint64 write(const QByteArray& data) { return mSocket->write(data); }
    QHostAddress peerAddress() const { return mSocket->peerAddress(); }
    QSslCertificate peerCertificate() const { return mSocket->peerCertificate(); }
    qint64 bytesAvailable() const { return mPackages.size(); }

    QSslSocket* mSocket;
    
Q_SIGNALS:
    void readyRead();

private Q_SLOTS:
    void dataReceived();

private:
    QByteArray lastChunk;
    QQueue<QByteArray> mPackages;

};

#endif
