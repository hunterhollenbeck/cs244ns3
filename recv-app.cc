#include "recv-app.h"
#include "ns3/applications-module.h"
#include "ns3/address-utils.h"
#include "ns3/address.h"
#include "ns3/boolean.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/ipv4-packet-info-tag.h"
#include "ns3/ipv6-packet-info-tag.h"
#include "ns3/log.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/socket.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/udp-socket.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("RecvApp");

RecvApp::RecvApp(){
    m_socket = nullptr;
}
RecvApp::~RecvApp(){
    m_socket = nullptr;
}

void RecvApp::Setup(Ptr<Socket> socket, Address sourceAddress, Address sinkAddress){
    m_socket = socket;
    m_sourceAddress = sourceAddress;
    m_sinkAddress = sinkAddress;

}

void RecvApp::StartApplication(){
    m_running = true;
    m_socket->Bind(m_sinkAddress);
    m_socket->Connect(m_sourceAddress);
    m_socket->Listen();
    recvPacket();
}

void RecvApp::StopApplication(){
    m_running = false;
    if (m_socket)
    {
        m_socket->Close();
    }
}

void RecvApp::recvPacket(){
    //while(m_running){
    //Ptr<Packet> packet;
    //while((packet = m_socket->Recv())){};
    m_socket->Recv();
    NS_LOG_DEBUG("attempting to receive");
    //}
    if(m_running){
        ScheduleRecv();
    }
}

void RecvApp::ScheduleRecv(){
    if(m_running){
        Simulator::Schedule(Seconds(.0001), &RecvApp::recvPacket, this);
    }
}
