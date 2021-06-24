<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __WL1251_RX_H__
#घोषणा __WL1251_RX_H__

#समावेश <linux/bitops.h>

#समावेश "wl1251.h"

/*
 * RX PATH
 *
 * The Rx path uses a द्विगुन buffer and an rx_contro काष्ठाure, each located
 * at a fixed address in the device memory. The host keeps track of which
 * buffer is available and alternates between them on a per packet basis.
 * The size of each of the two buffers is large enough to hold the दीर्घest
 * 802.3 packet.
 * The RX path goes like that:
 * 1) The target generates an पूर्णांकerrupt each समय a new packet is received.
 *   There are 2 RX पूर्णांकerrupts, one क्रम each buffer.
 * 2) The host पढ़ोs the received packet from one of the द्विगुन buffers.
 * 3) The host triggers a target पूर्णांकerrupt.
 * 4) The target prepares the next RX packet.
 */

#घोषणा WL1251_RX_MAX_RSSI -30
#घोषणा WL1251_RX_MIN_RSSI -95

#घोषणा WL1251_RX_ALIGN_TO 4
#घोषणा WL1251_RX_ALIGN(len) (((len) + WL1251_RX_ALIGN_TO - 1) & \
			     ~(WL1251_RX_ALIGN_TO - 1))

#घोषणा SHORT_PREAMBLE_BIT   BIT(0)
#घोषणा OFDM_RATE_BIT        BIT(6)
#घोषणा PBCC_RATE_BIT        BIT(7)

#घोषणा PLCP_HEADER_LENGTH 8
#घोषणा RX_DESC_PACKETID_SHIFT 11
#घोषणा RX_MAX_PACKET_ID 3

#घोषणा RX_DESC_VALID_FCS         0x0001
#घोषणा RX_DESC_MATCH_RXADDR1     0x0002
#घोषणा RX_DESC_MCAST             0x0004
#घोषणा RX_DESC_STAINTIM          0x0008
#घोषणा RX_DESC_VIRTUAL_BM        0x0010
#घोषणा RX_DESC_BCAST             0x0020
#घोषणा RX_DESC_MATCH_SSID        0x0040
#घोषणा RX_DESC_MATCH_BSSID       0x0080
#घोषणा RX_DESC_ENCRYPTION_MASK   0x0300
#घोषणा RX_DESC_MEASURMENT        0x0400
#घोषणा RX_DESC_SEQNUM_MASK       0x1800
#घोषणा	RX_DESC_MIC_FAIL	  0x2000
#घोषणा	RX_DESC_DECRYPT_FAIL	  0x4000

काष्ठा wl1251_rx_descriptor अणु
	u32 बारtamp; /* In microseconds */
	u16 length; /* Paylod length, including headers */
	u16 flags;

	/*
	 * 0 - 802.11
	 * 1 - 802.3
	 * 2 - IP
	 * 3 - Raw Codec
	 */
	u8 type;

	/*
	 * Received Rate:
	 * 0x0A - 1MBPS
	 * 0x14 - 2MBPS
	 * 0x37 - 5_5MBPS
	 * 0x0B - 6MBPS
	 * 0x0F - 9MBPS
	 * 0x6E - 11MBPS
	 * 0x0A - 12MBPS
	 * 0x0E - 18MBPS
	 * 0xDC - 22MBPS
	 * 0x09 - 24MBPS
	 * 0x0D - 36MBPS
	 * 0x08 - 48MBPS
	 * 0x0C - 54MBPS
	 */
	u8 rate;

	u8 mod_pre; /* Modulation and preamble */
	u8 channel;

	/*
	 * 0 - 2.4 Ghz
	 * 1 - 5 Ghz
	 */
	u8 band;

	s8 rssi; /* in dB */
	u8 rcpi; /* in dB */
	u8 snr; /* in dB */
पूर्ण __packed;

व्योम wl1251_rx(काष्ठा wl1251 *wl);

#पूर्ण_अगर
