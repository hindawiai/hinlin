<शैली गुरु>
/*
 * Shared Atheros AR9170 Header
 *
 * RX/TX meta descriptor क्रमmat
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009-2011 Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __CARL9170_SHARED_WLAN_H
#घोषणा __CARL9170_SHARED_WLAN_H

#समावेश "fwcmd.h"

#घोषणा	AR9170_RX_PHY_RATE_CCK_1M		0x0a
#घोषणा	AR9170_RX_PHY_RATE_CCK_2M		0x14
#घोषणा	AR9170_RX_PHY_RATE_CCK_5M		0x37
#घोषणा	AR9170_RX_PHY_RATE_CCK_11M		0x6e

#घोषणा	AR9170_ENC_ALG_NONE			0x0
#घोषणा	AR9170_ENC_ALG_WEP64			0x1
#घोषणा	AR9170_ENC_ALG_TKIP			0x2
#घोषणा	AR9170_ENC_ALG_AESCCMP			0x4
#घोषणा	AR9170_ENC_ALG_WEP128			0x5
#घोषणा	AR9170_ENC_ALG_WEP256			0x6
#घोषणा	AR9170_ENC_ALG_CENC			0x7

#घोषणा	AR9170_RX_ENC_SOFTWARE			0x8

#घोषणा	AR9170_RX_STATUS_MODULATION		0x03
#घोषणा	AR9170_RX_STATUS_MODULATION_S		0
#घोषणा	AR9170_RX_STATUS_MODULATION_CCK		0x00
#घोषणा	AR9170_RX_STATUS_MODULATION_OFDM	0x01
#घोषणा	AR9170_RX_STATUS_MODULATION_HT		0x02
#घोषणा	AR9170_RX_STATUS_MODULATION_DUPOFDM	0x03

/* depends on modulation */
#घोषणा	AR9170_RX_STATUS_SHORT_PREAMBLE		0x08
#घोषणा	AR9170_RX_STATUS_GREENFIELD		0x08

#घोषणा	AR9170_RX_STATUS_MPDU			0x30
#घोषणा	AR9170_RX_STATUS_MPDU_S			4
#घोषणा	AR9170_RX_STATUS_MPDU_SINGLE		0x00
#घोषणा	AR9170_RX_STATUS_MPDU_FIRST		0x20
#घोषणा	AR9170_RX_STATUS_MPDU_MIDDLE		0x30
#घोषणा	AR9170_RX_STATUS_MPDU_LAST		0x10

#घोषणा	AR9170_RX_STATUS_CONT_AGGR		0x40
#घोषणा	AR9170_RX_STATUS_TOTAL_ERROR		0x80

#घोषणा	AR9170_RX_ERROR_RXTO			0x01
#घोषणा	AR9170_RX_ERROR_OVERRUN			0x02
#घोषणा	AR9170_RX_ERROR_DECRYPT			0x04
#घोषणा	AR9170_RX_ERROR_FCS			0x08
#घोषणा	AR9170_RX_ERROR_WRONG_RA		0x10
#घोषणा	AR9170_RX_ERROR_PLCP			0x20
#घोषणा	AR9170_RX_ERROR_MMIC			0x40

/* these are either-or */
#घोषणा	AR9170_TX_MAC_PROT_RTS			0x0001
#घोषणा	AR9170_TX_MAC_PROT_CTS			0x0002
#घोषणा	AR9170_TX_MAC_PROT			0x0003

#घोषणा	AR9170_TX_MAC_NO_ACK			0x0004
/* अगर unset, MAC will only करो SIFS space beक्रमe frame */
#घोषणा	AR9170_TX_MAC_BACKOFF			0x0008
#घोषणा	AR9170_TX_MAC_BURST			0x0010
#घोषणा	AR9170_TX_MAC_AGGR			0x0020

/* encryption is a two-bit field */
#घोषणा	AR9170_TX_MAC_ENCR_NONE			0x0000
#घोषणा	AR9170_TX_MAC_ENCR_RC4			0x0040
#घोषणा	AR9170_TX_MAC_ENCR_CENC			0x0080
#घोषणा	AR9170_TX_MAC_ENCR_AES			0x00c0

#घोषणा	AR9170_TX_MAC_MMIC			0x0100
#घोषणा	AR9170_TX_MAC_HW_DURATION		0x0200
#घोषणा	AR9170_TX_MAC_QOS_S			10
#घोषणा	AR9170_TX_MAC_QOS			0x0c00
#घोषणा	AR9170_TX_MAC_DISABLE_TXOP		0x1000
#घोषणा	AR9170_TX_MAC_TXOP_RIFS			0x2000
#घोषणा	AR9170_TX_MAC_IMM_BA			0x4000

/* either-or */
#घोषणा	AR9170_TX_PHY_MOD_CCK			0x00000000
#घोषणा	AR9170_TX_PHY_MOD_OFDM			0x00000001
#घोषणा	AR9170_TX_PHY_MOD_HT			0x00000002

/* depends on modulation */
#घोषणा	AR9170_TX_PHY_SHORT_PREAMBLE		0x00000004
#घोषणा	AR9170_TX_PHY_GREENFIELD		0x00000004

#घोषणा	AR9170_TX_PHY_BW_S			3
#घोषणा	AR9170_TX_PHY_BW			(3 << AR9170_TX_PHY_BW_SHIFT)
#घोषणा	AR9170_TX_PHY_BW_20MHZ			0
#घोषणा	AR9170_TX_PHY_BW_40MHZ			2
#घोषणा	AR9170_TX_PHY_BW_40MHZ_DUP		3

#घोषणा	AR9170_TX_PHY_TX_HEAVY_CLIP_S		6
#घोषणा	AR9170_TX_PHY_TX_HEAVY_CLIP		(7 << \
						 AR9170_TX_PHY_TX_HEAVY_CLIP_S)

#घोषणा	AR9170_TX_PHY_TX_PWR_S			9
#घोषणा	AR9170_TX_PHY_TX_PWR			(0x3f << \
						 AR9170_TX_PHY_TX_PWR_S)

#घोषणा	AR9170_TX_PHY_TXCHAIN_S			15
#घोषणा	AR9170_TX_PHY_TXCHAIN			(7 << \
						 AR9170_TX_PHY_TXCHAIN_S)
#घोषणा	AR9170_TX_PHY_TXCHAIN_1			1
/* use क्रम cck, ofdm 6/9/12/18/24 and HT अगर capable */
#घोषणा	AR9170_TX_PHY_TXCHAIN_2			5

#घोषणा	AR9170_TX_PHY_MCS_S			18
#घोषणा	AR9170_TX_PHY_MCS			(0x7f << \
						 AR9170_TX_PHY_MCS_S)

#घोषणा	AR9170_TX_PHY_RATE_CCK_1M		0x0
#घोषणा	AR9170_TX_PHY_RATE_CCK_2M		0x1
#घोषणा	AR9170_TX_PHY_RATE_CCK_5M		0x2
#घोषणा	AR9170_TX_PHY_RATE_CCK_11M		0x3

/* same as AR9170_RX_PHY_RATE */
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_6M		0xb
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_9M		0xf
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_12M		0xa
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_18M		0xe
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_24M		0x9
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_36M		0xd
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_48M		0x8
#घोषणा	AR9170_TXRX_PHY_RATE_OFDM_54M		0xc

#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS0		0x0
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS1		0x1
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS2		0x2
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS3		0x3
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS4		0x4
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS5		0x5
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS6		0x6
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS7		0x7
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS8		0x8
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS9		0x9
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS10		0xa
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS11		0xb
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS12		0xc
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS13		0xd
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS14		0xe
#घोषणा	AR9170_TXRX_PHY_RATE_HT_MCS15		0xf

#घोषणा	AR9170_TX_PHY_SHORT_GI			0x80000000

#अगर_घोषित __CARL9170FW__
काष्ठा ar9170_tx_hw_mac_control अणु
	जोड़ अणु
		काष्ठा अणु
			/*
			 * Beware of compiler bugs in all gcc pre 4.4!
			 */

			u8 erp_prot:2;
			u8 no_ack:1;
			u8 backoff:1;
			u8 burst:1;
			u8 ampdu:1;

			u8 enc_mode:2;

			u8 hw_mmic:1;
			u8 hw_duration:1;

			u8 qos_queue:2;

			u8 disable_txop:1;
			u8 txop_rअगरs:1;

			u8 ba_end:1;
			u8 probe:1;
		पूर्ण __packed;

		__le16 set;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा ar9170_tx_hw_phy_control अणु
	जोड़ अणु
		काष्ठा अणु
			/*
			 * Beware of compiler bugs in all gcc pre 4.4!
			 */

			u8 modulation:2;
			u8 preamble:1;
			u8 bandwidth:2;
			u8:1;
			u8 heavy_clip:3;
			u8 tx_घातer:6;
			u8 chains:3;
			u8 mcs:7;
			u8:6;
			u8 लघु_gi:1;
		पूर्ण __packed;

		__le32 set;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा ar9170_tx_rate_info अणु
	u8 tries:3;
	u8 erp_prot:2;
	u8 ampdu:1;
	u8 मुक्त:2; /* मुक्त क्रम use (e.g.:RIFS/TXOP/AMPDU) */
पूर्ण __packed;

काष्ठा carl9170_tx_superdesc अणु
	__le16 len;
	u8 rix;
	u8 cnt;
	u8 cookie;
	u8 ampdu_density:3;
	u8 ampdu_factor:2;
	u8 ampdu_commit_density:1;
	u8 ampdu_commit_factor:1;
	u8 ampdu_unused_bit:1;
	u8 queue:2;
	u8 assign_seq:1;
	u8 vअगर_id:3;
	u8 fill_in_tsf:1;
	u8 cab:1;
	u8 padding2;
	काष्ठा ar9170_tx_rate_info ri[CARL9170_TX_MAX_RATES];
	काष्ठा ar9170_tx_hw_phy_control rr[CARL9170_TX_MAX_RETRY_RATES];
पूर्ण __packed;

काष्ठा ar9170_tx_hwdesc अणु
	__le16 length;
	काष्ठा ar9170_tx_hw_mac_control mac;
	काष्ठा ar9170_tx_hw_phy_control phy;
पूर्ण __packed;

काष्ठा ar9170_tx_frame अणु
	काष्ठा ar9170_tx_hwdesc hdr;

	जोड़ अणु
		काष्ठा ieee80211_hdr i3e;
		u8 payload[0];
	पूर्ण data;
पूर्ण __packed;

काष्ठा carl9170_tx_superframe अणु
	काष्ठा carl9170_tx_superdesc s;
	काष्ठा ar9170_tx_frame f;
पूर्ण __packed __aligned(4);

#पूर्ण_अगर /* __CARL9170FW__ */

काष्ठा _ar9170_tx_hwdesc अणु
	__le16 length;
	__le16 mac_control;
	__le32 phy_control;
पूर्ण __packed;

#घोषणा	CARL9170_TX_SUPER_AMPDU_DENSITY_S		0
#घोषणा	CARL9170_TX_SUPER_AMPDU_DENSITY			0x7
#घोषणा	CARL9170_TX_SUPER_AMPDU_FACTOR			0x18
#घोषणा	CARL9170_TX_SUPER_AMPDU_FACTOR_S		3
#घोषणा	CARL9170_TX_SUPER_AMPDU_COMMIT_DENSITY		0x20
#घोषणा	CARL9170_TX_SUPER_AMPDU_COMMIT_DENSITY_S	5
#घोषणा	CARL9170_TX_SUPER_AMPDU_COMMIT_FACTOR		0x40
#घोषणा	CARL9170_TX_SUPER_AMPDU_COMMIT_FACTOR_S		6

#घोषणा CARL9170_TX_SUPER_MISC_QUEUE			0x3
#घोषणा CARL9170_TX_SUPER_MISC_QUEUE_S			0
#घोषणा CARL9170_TX_SUPER_MISC_ASSIGN_SEQ		0x4
#घोषणा	CARL9170_TX_SUPER_MISC_VIF_ID			0x38
#घोषणा	CARL9170_TX_SUPER_MISC_VIF_ID_S			3
#घोषणा	CARL9170_TX_SUPER_MISC_FILL_IN_TSF		0x40
#घोषणा	CARL9170_TX_SUPER_MISC_CAB			0x80

#घोषणा CARL9170_TX_SUPER_RI_TRIES			0x7
#घोषणा CARL9170_TX_SUPER_RI_TRIES_S			0
#घोषणा CARL9170_TX_SUPER_RI_ERP_PROT			0x18
#घोषणा CARL9170_TX_SUPER_RI_ERP_PROT_S			3
#घोषणा CARL9170_TX_SUPER_RI_AMPDU			0x20
#घोषणा CARL9170_TX_SUPER_RI_AMPDU_S			5

काष्ठा _carl9170_tx_superdesc अणु
	__le16 len;
	u8 rix;
	u8 cnt;
	u8 cookie;
	u8 ampdu_settings;
	u8 misc;
	u8 padding;
	u8 ri[CARL9170_TX_MAX_RATES];
	__le32 rr[CARL9170_TX_MAX_RETRY_RATES];
पूर्ण __packed;

काष्ठा _carl9170_tx_superframe अणु
	काष्ठा _carl9170_tx_superdesc s;
	काष्ठा _ar9170_tx_hwdesc f;
	u8 frame_data[0];
पूर्ण __packed __aligned(4);

#घोषणा	CARL9170_TX_SUPERDESC_LEN		24
#घोषणा	AR9170_TX_HWDESC_LEN			8
#घोषणा	CARL9170_TX_SUPERFRAME_LEN		(CARL9170_TX_SUPERDESC_LEN + \
						 AR9170_TX_HWDESC_LEN)

काष्ठा ar9170_rx_head अणु
	u8 plcp[12];
पूर्ण __packed;

#घोषणा	AR9170_RX_HEAD_LEN			12

काष्ठा ar9170_rx_phystatus अणु
	जोड़ अणु
		काष्ठा अणु
			u8 rssi_ant0, rssi_ant1, rssi_ant2,
				rssi_ant0x, rssi_ant1x, rssi_ant2x,
				rssi_combined;
		पूर्ण __packed;
		u8 rssi[7];
	पूर्ण __packed;

	u8 evm_stream0[6], evm_stream1[6];
	u8 phy_err;
पूर्ण __packed;

#घोषणा	AR9170_RX_PHYSTATUS_LEN			20

काष्ठा ar9170_rx_macstatus अणु
	u8 SAidx, DAidx;
	u8 error;
	u8 status;
पूर्ण __packed;

#घोषणा	AR9170_RX_MACSTATUS_LEN			4

काष्ठा ar9170_rx_frame_single अणु
	काष्ठा ar9170_rx_head phy_head;
	काष्ठा ieee80211_hdr i3e __packed __aligned(2);
	काष्ठा ar9170_rx_phystatus phy_tail;
	काष्ठा ar9170_rx_macstatus macstatus;
पूर्ण;

काष्ठा ar9170_rx_frame_head अणु
	काष्ठा ar9170_rx_head phy_head;
	काष्ठा ieee80211_hdr i3e __packed __aligned(2);
	काष्ठा ar9170_rx_macstatus macstatus;
पूर्ण;

काष्ठा ar9170_rx_frame_middle अणु
	काष्ठा ieee80211_hdr i3e __packed __aligned(2);
	काष्ठा ar9170_rx_macstatus macstatus;
पूर्ण;

काष्ठा ar9170_rx_frame_tail अणु
	काष्ठा ieee80211_hdr i3e __packed __aligned(2);
	काष्ठा ar9170_rx_phystatus phy_tail;
	काष्ठा ar9170_rx_macstatus macstatus;
पूर्ण;

काष्ठा ar9170_rx_frame अणु
	जोड़ अणु
		काष्ठा ar9170_rx_frame_single single;
		काष्ठा ar9170_rx_frame_head head;
		काष्ठा ar9170_rx_frame_middle middle;
		काष्ठा ar9170_rx_frame_tail tail;
	पूर्ण;
पूर्ण;

अटल अंतरभूत u8 ar9170_get_decrypt_type(काष्ठा ar9170_rx_macstatus *t)
अणु
	वापस (t->SAidx & 0xc0) >> 4 |
	       (t->DAidx & 0xc0) >> 6;
पूर्ण

/*
 * This is an workaround क्रम several unकरोcumented bugs.
 * Don't mess with the QoS/AC <-> HW Queue map, if you don't
 * know what you are करोing.
 *
 * Known problems [hardware]:
 *  * The MAC करोes not aggregate frames on anything other
 *    than the first HW queue.
 *  * when an AMPDU is placed [in the first hw queue] and
 *    additional frames are alपढ़ोy queued on a dअगरferent
 *    hw queue, the MAC will ALWAYS मुक्तze.
 *
 * In a nutshell: The hardware can either करो QoS or
 * Aggregation but not both at the same समय. As a
 * result, this makes the device pretty much useless
 * क्रम any serious 802.11n setup.
 */
क्रमागत ar9170_txq अणु
	AR9170_TXQ_BK = 0,	/* TXQ0 */
	AR9170_TXQ_BE,		/* TXQ1	*/
	AR9170_TXQ_VI,		/* TXQ2	*/
	AR9170_TXQ_VO,		/* TXQ3 */

	__AR9170_NUM_TXQ,
पूर्ण;

#घोषणा	AR9170_TXQ_DEPTH			32

#पूर्ण_अगर /* __CARL9170_SHARED_WLAN_H */
