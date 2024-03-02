#include "ccsdspacket.hpp"

constexpr bool SWAP = true;
constexpr bool NOSWAP = false;
constexpr uint8_t CMD_MASK = 0x10;
constexpr uint8_t SEGFLG_MASK = 0xC0;
constexpr uint8_t SECHDR_MASK = 0x08;
constexpr uint16_t APPID_MASK = 0x03FF;
constexpr uint16_t SEQNO_MASK = 0x3FFF;

uint16_t packet_identification(
				const PktType pkttype,
				const SegFlag segflg,
				const bool secondaryheader,
				const uint16_t appid
		)
{
	uint16_t word = 0x1800;

        if (pkttype == PktType::tlm) word = word & 0x0800; // TlM pkt
	if (!secondaryheader) word = word & 0x1000; // No secondary header

	uint16_t apidbits = appid & APPID_MASK;
        word = word | apidbits;

	return word;
}

uint16_t seq_word(const SegFlag segflg, const uint16_t seqno)
{
	uint16_t seqnobits = seqno & SEQNO_MASK;

	uint16_t seqwrd;
	switch( segflg )
	{
	case firstsegment:
	    seqwrd = 0b01<<14;
	    break;
	case continuation:
	    seqwrd = 0b00<<14;
	    break;
	case lastseg:
	    seqwrd = 0b10<<14;
	    break;
	case unsegmented:
	    seqwrd = 0b11<<14;
	    break;
        default:
	    throw "Invalid Segment Flag\n";
	}
	seqwrd = seqwrd | seqnobits;
	return seqwrd;
}

void appendword2vector(const uint16_t word, std::vector<uint8_t>& vecdata)
{
	uint8_t byt;

	byt = word>>8;
	vecdata.push_back(byt);

	byt = word;
	vecdata.push_back(byt);
}

uint16_t word_frombytes(uint8_t byte0, uint8_t byte1, bool byteswap)
{
	int val;
        if (byteswap)
	    val = static_cast<int>(byte0)<<8 | static_cast<int>(byte1);
	else
	    val = static_cast<int>(byte1)<<8 | static_cast<int>(byte0);
	return val;
}


CcsdsPrimaryHeader::CcsdsPrimaryHeader(
				const PktType pkttype,
				const bool secondaryheader,
				const uint16_t appid,
				const uint16_t size,
				const SegFlag segflg,
				const uint16_t seqno=0
		)
{

	uint16_t word0 = packet_identification(pkttype, segflg, secondaryheader, appid);
	appendword2vector(word0, m_data);

	uint16_t word1 = seq_word(segflg, seqno);
	appendword2vector(word1, m_data);

	appendword2vector(size, m_data);
	
}

bool CcsdsPrimaryHeader::isCommand()
{
	std::cout << "isCmd" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr0: " << m_data[0] << std::endl; 
	bool cmdbit = (m_data[0] & CMD_MASK)>>4;
	return cmdbit;
}

bool CcsdsPrimaryHeader::isTelemetry()
{
	std::cout << "isTlm" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr0: " << m_data[0] << std::endl; 
	bool sechdrbit = (m_data[0] & SECHDR_MASK)>>3;
	return sechdrbit;
}

bool CcsdsPrimaryHeader::isSegmented()
{
	std::cout << "isSeg" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr1: " << std::hex << static_cast<int>(m_data[2]) << std::endl; 
	int segflg = (m_data[2] & SEGFLG_MASK)>>6;
	std::cout << "SegFlg: " << std::hex << segflg << std::endl; 
	if (segflg == 3) return false;
	return true;
}

bool CcsdsPrimaryHeader::isContinuation()
{
	std::cout << "isSeg" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr1: " << std::hex << static_cast<int>(m_data[2]) << std::endl; 
	int segflg = (m_data[2] & SEGFLG_MASK)>>6;
	std::cout << "SegFlg: " << std::hex << segflg << std::endl; 
	if (segflg == 0) return true;
	return false;
}

bool CcsdsPrimaryHeader::isLastSegment()
{
	std::cout << "isSeg" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr1: " << std::hex << static_cast<int>(m_data[2]) << std::endl; 
	int segflg = (m_data[2] & SEGFLG_MASK)>>6;
	std::cout << "SegFlg: " << std::hex << segflg << std::endl; 
	if (segflg == 2) return true;
	return false;
}

int CcsdsPrimaryHeader::get_appid()
{
	std::cout << "appid" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr2: " << std::hex << static_cast<int>(m_data[0]) << std::endl; 
	std::cout << "Hdr2: " << std::hex << static_cast<int>(m_data[1]) << std::endl; 
	int val = word_frombytes(m_data[0], m_data[1], SWAP);
	val = val & APPID_MASK;
	std::cout << "Appid: " << std::hex << val << std::endl; 
	return val;
}

int CcsdsPrimaryHeader::get_sequencenumber()
{
	std::cout << "seqno" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr2: " << std::hex << static_cast<int>(m_data[2]) << std::endl; 
	std::cout << "Hdr2: " << std::hex << static_cast<int>(m_data[3]) << std::endl; 
	int val = word_frombytes(m_data[2], m_data[3], SWAP);
	val = val & SEQNO_MASK;
	std::cout << "Seqno: " << std::hex << val << std::endl; 
	return val;
}

int CcsdsPrimaryHeader::get_size()
{
	std::cout << "size" << std::endl;
	if (m_data.size() < 6) return false;

	std::cout << "Hdr2: " << std::hex << static_cast<int>(m_data[4]) << std::endl; 
	std::cout << "Hdr2: " << std::hex << static_cast<int>(m_data[5]) << std::endl; 
	int val = word_frombytes(m_data[4], m_data[5], SWAP);
	std::cout << "Size: " << std::hex << val << std::endl; 
	return val;
}

CcsdsPacket::CcsdsPacket(
				const PktType pkttype,
				const bool secondaryheader,
				const uint16_t appid,
				const uint16_t size,
				const SegFlag segflg=unsegmented,
				const uint16_t seqno=0
		)
{
;
}
