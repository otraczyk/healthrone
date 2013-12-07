import random
import json
import time

import cffi

from twisted.internet import reactor, protocol, task
from twisted.internet.serialport import SerialPort

#class Echo(protocol.Protocol):
#    def dataReceived(self, data):
#        self.transport.write(data)

#class EchoFactory(protocol.Factory):
#    def buildProtocol(self, addr):
#        print addr
#        return Echo()

from twisted.internet.serialport import SerialPort

globalData= {
#    't':None,
#    'a':None,
#    'b':None,
    'txt':None
}

class USBclient(protocol.Protocol):
    def connectionMade(self):
        global serServ
        serServ = self
        self.buf=""
        print 'Arduino device: ', serServ, ' is connected.'

#    def cmdReceived(self, cmd):
#        serServ.transport.write(cmd)
#        pass

    def dataReceived(self,data):
        lineData,self.buf=(self.buf+data).split('\n',1)
        globalData['txt']=repr(data)

class ControlerStream(protocol.Protocol):
    def connectionMade(self):
        self.factory.clientConnectionMade(self)
    def connectionLost(self, reason):
        self.factory.clientConnectionLost(self)
    def dataReceived(self, data):
        self.transport.write(data)

class ControlerStreamFactory(protocol.Factory):
    protocol = ControlerStream
    def __init__(self):
        self.count=0
        self.clients = []
        self.lc = task.LoopingCall(self.announce)
        self.lc.start(0.1)

    def announce(self):
        self.count+=1
        obj={'value':random.random(),'id':self.count,'time':time.time()}
        obj.update(globalData)
        data=json.dumps(obj)+"\n"
        for client in self.clients:
            client.transport.write(data)

    def clientConnectionMade(self, client):
        self.clients.append(client)

    def clientConnectionLost(self, client):
        self.clients.remove(client)

#reactor.listenTCP(1234, EchoFactory())

reactor.listenTCP(1236, ControlerStreamFactory())
SerialPort(USBclient(), '/dev/ttyACM0', reactor, baudrate='9600')
reactor.run()
