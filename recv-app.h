/*
 * I'm really cool.
 */

#ifndef RECV_APP_H
#define RECV_APP_H

#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"

namespace ns3
{

class Application;

class RecvApp : public Application
{
  public:
    RecvApp();
    ~RecvApp() override;

    /**
     * Register this type.
     * \return The TypeId.
     */
    //static TypeId GetTypeId();

    /**
     * Setup the socket.
     * \param socket The socket.
     * \param address The destination address.
     * \param packetSize The packet size to transmit.
     * \param nPackets The number of packets to transmit.
     * \param dataRate the data rate to use.
     */
    void Setup(Ptr<Socket> socket,
               Address sourceAddress, Address sinkAddress);

    void recvPacket();
    void ScheduleRecv();

  private:
    void StartApplication() override;
    void StopApplication() override;

    /// Schedule a new transmission.
    void Receive();

    Ptr<Socket> m_socket;   //!< The transmission socket.
    Address m_sinkAddress;         //!< The destination address.
    Address m_sourceAddress;
    bool m_running;
    /*uint32_t m_packetSize;  //!< The packet size.
    uint32_t m_nPackets;    //!< The number of packets to send.
    DataRate m_dataRate;    //!< The data rate to use.
    EventId m_sendEvent;    //!< Send event.
    bool m_running;         //!< True if the application is running.
    uint32_t m_packetsSent; //!< The number of packets sent.*/
};

} // namespace ns3

#endif /* TUTORIAL_APP_H */
