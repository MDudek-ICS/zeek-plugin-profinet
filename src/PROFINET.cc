#include "PROFINET.h"
#include "events.bif.h"

using namespace analyzer::profinet;

PROFINET_Analyzer::PROFINET_Analyzer(Connection* c): analyzer::Analyzer("PROFINET", c) {
    interp = new binpac::PROFINET::PROFINET_Conn(this);
    }

PROFINET_Analyzer::~PROFINET_Analyzer() {
    delete interp;
    }

void PROFINET_Analyzer::Done() {
    Analyzer::Done();
    }

void PROFINET_Analyzer::DeliverPacket(int len, const u_char* data, bool orig, uint64 seq, const IP_Hdr* ip, int caplen) {
    Analyzer::DeliverPacket(len, data, orig, seq, ip, caplen);

    try {
        interp->NewData(orig, data, data + len);
        }
    catch(const binpac::Exception& e) {
        ProtocolViolation(fmt("Binpac exception: %s", e.c_msg()));
        }
    }

