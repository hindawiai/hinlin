<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __RX_H__
#घोषणा __RX_H__

#समावेश <linux/bitops.h>

#घोषणा WL1271_RX_MAX_RSSI -30
#घोषणा WL1271_RX_MIN_RSSI -95

#घोषणा RSSI_LEVEL_BITMASK	0x7F
#घोषणा ANT_DIVERSITY_BITMASK	BIT(7)

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

/*
 * RX Descriptor flags:
 *
 * Bits 0-1 - band
 * Bit  2   - STBC
 * Bit  3   - A-MPDU
 * Bit  4   - HT
 * Bits 5-7 - encryption
 */
#घोषणा WL1271_RX_DESC_BAND_MASK    0x03
#घोषणा WL1271_RX_DESC_ENCRYPT_MASK 0xE0

#घोषणा WL1271_RX_DESC_BAND_BG      0x00
#घोषणा WL1271_RX_DESC_BAND_J       0x01
#घोषणा WL1271_RX_DESC_BAND_A       0x02

#घोषणा WL1271_RX_DESC_STBC         BIT(2)
#घोषणा WL1271_RX_DESC_A_MPDU       BIT(3)
#घोषणा WL1271_RX_DESC_HT           BIT(4)

#घोषणा WL1271_RX_DESC_ENCRYPT_WEP  0x20
#घोषणा WL1271_RX_DESC_ENCRYPT_TKIP 0x40
#घोषणा WL1271_RX_DESC_ENCRYPT_AES  0x60
#घोषणा WL1271_RX_DESC_ENCRYPT_GEM  0x80

/*
 * RX Descriptor status
 *
 * Bits 0-2 - error code
 * Bits 3-5 - process_id tag (AP mode FW)
 * Bits 6-7 - reserved
 */
#घोषणा WL1271_RX_DESC_STATUS_MASK      0x07

#घोषणा WL1271_RX_DESC_SUCCESS          0x00
#घोषणा WL1271_RX_DESC_DECRYPT_FAIL     0x01
#घोषणा WL1271_RX_DESC_MIC_FAIL         0x02

#घोषणा RX_MEM_BLOCK_MASK            0xFF
#घोषणा RX_BUF_SIZE_MASK             0xFFF00
#घोषणा RX_BUF_SIZE_SHIFT_DIV        6
#घोषणा ALIGNED_RX_BUF_SIZE_MASK     0xFFFF00
#घोषणा ALIGNED_RX_BUF_SIZE_SHIFT    8

/* If set, the start of IP payload is not 4 bytes aligned */
#घोषणा RX_BUF_UNALIGNED_PAYLOAD     BIT(20)

/* If set, the buffer was padded by the FW to be 4 bytes aligned */
#घोषणा RX_BUF_PADDED_PAYLOAD        BIT(30)

/*
 * Account क्रम the padding inserted by the FW in हाल of RX_ALIGNMENT
 * or क्रम fixing alignment in हाल the packet wasn't aligned.
 */
#घोषणा RX_BUF_ALIGN                 2

/* Describes the alignment state of a Rx buffer */
क्रमागत wl_rx_buf_align अणु
	WLCORE_RX_BUF_ALIGNED,
	WLCORE_RX_BUF_UNALIGNED,
	WLCORE_RX_BUF_PADDED,
पूर्ण;

क्रमागत अणु
	WL12XX_RX_CLASS_UNKNOWN,
	WL12XX_RX_CLASS_MANAGEMENT,
	WL12XX_RX_CLASS_DATA,
	WL12XX_RX_CLASS_QOS_DATA,
	WL12XX_RX_CLASS_BCN_PRBRSP,
	WL12XX_RX_CLASS_EAPOL,
	WL12XX_RX_CLASS_BA_EVENT,
	WL12XX_RX_CLASS_AMSDU,
	WL12XX_RX_CLASS_LOGGER,
पूर्ण;

काष्ठा wl1271_rx_descriptor अणु
	__le16 length;
	u8  status;
	u8  flags;
	u8  rate;
	u8  channel;
	s8  rssi;
	u8  snr;
	__le32 बारtamp;
	u8  packet_class;
	u8  hlid;
	u8  pad_len;
	u8  reserved;
पूर्ण __packed;

पूर्णांक wlcore_rx(काष्ठा wl1271 *wl, काष्ठा wl_fw_status *status);
u8 wl1271_rate_to_idx(पूर्णांक rate, क्रमागत nl80211_band band);
पूर्णांक wl1271_rx_filter_enable(काष्ठा wl1271 *wl,
			    पूर्णांक index, bool enable,
			    काष्ठा wl12xx_rx_filter *filter);
पूर्णांक wl1271_rx_filter_clear_all(काष्ठा wl1271 *wl);

#पूर्ण_अगर
