#ifndef INCLUDE_CCSDSPACKET
#define INCLUDE_CCSDSPACKET

#include <vector>
#include <iostream>
#include "util.hpp"

enum PktType {cmd, tlm};

enum SegFlag {firstsegment, continuation, lastseg, unsegmented};


class CcsdsPrimaryHeader
{
	public:
		CcsdsPrimaryHeader(std::vector<uint8_t> hdrdata) :m_data(hdrdata) {};
		CcsdsPrimaryHeader(
				const PktType pkttype,
				const bool secondaryheader,
				const uint16_t appid,
				const uint16_t size,
				const SegFlag segflg,
				const uint16_t seqno
				);

		bool isCommand();
		bool isTelemetry();
		bool isSegmented();
		bool isContinuation();
		bool isLastSegment();

		int get_appid();
		int get_sequencenumber();
		int get_size();


	private:
		std::vector<uint8_t> m_data;
};


class CcsdsPacket
{
	public:
		CcsdsPacket(
				const PktType pkttype,
				const bool secondaryheader,
				const uint16_t appid,
				const uint16_t size,
				const SegFlag segflg,
				const uint16_t seqno
			   );

	private:
		std::vector<uint8_t> m_data;
};

#endif
