<शैली गुरु>
/*
 * Shared Atheros AR9170 Header
 *
 * Firmware command पूर्णांकerface definitions
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

#अगर_अघोषित __CARL9170_SHARED_FWCMD_H
#घोषणा __CARL9170_SHARED_FWCMD_H

#घोषणा	CARL9170_MAX_CMD_LEN		64
#घोषणा	CARL9170_MAX_CMD_PAYLOAD_LEN	60

#घोषणा CARL9170FW_API_MIN_VER		1
#घोषणा CARL9170FW_API_MAX_VER		1

क्रमागत carl9170_cmd_oids अणु
	CARL9170_CMD_RREG		= 0x00,
	CARL9170_CMD_WREG		= 0x01,
	CARL9170_CMD_ECHO		= 0x02,
	CARL9170_CMD_SWRST		= 0x03,
	CARL9170_CMD_REBOOT		= 0x04,
	CARL9170_CMD_BCN_CTRL		= 0x05,
	CARL9170_CMD_READ_TSF		= 0x06,
	CARL9170_CMD_RX_FILTER		= 0x07,
	CARL9170_CMD_WOL		= 0x08,
	CARL9170_CMD_TALLY		= 0x09,
	CARL9170_CMD_WREGB		= 0x0a,

	/* CAM */
	CARL9170_CMD_EKEY		= 0x10,
	CARL9170_CMD_DKEY		= 0x11,

	/* RF / PHY */
	CARL9170_CMD_FREQUENCY		= 0x20,
	CARL9170_CMD_RF_INIT		= 0x21,
	CARL9170_CMD_SYNTH		= 0x22,
	CARL9170_CMD_FREQ_START		= 0x23,
	CARL9170_CMD_PSM		= 0x24,

	/* Asychronous command flag */
	CARL9170_CMD_ASYNC_FLAG		= 0x40,
	CARL9170_CMD_WREG_ASYNC		= (CARL9170_CMD_WREG |
					   CARL9170_CMD_ASYNC_FLAG),
	CARL9170_CMD_REBOOT_ASYNC	= (CARL9170_CMD_REBOOT |
					   CARL9170_CMD_ASYNC_FLAG),
	CARL9170_CMD_BCN_CTRL_ASYNC	= (CARL9170_CMD_BCN_CTRL |
					   CARL9170_CMD_ASYNC_FLAG),
	CARL9170_CMD_PSM_ASYNC		= (CARL9170_CMD_PSM |
					   CARL9170_CMD_ASYNC_FLAG),

	/* responses and traps */
	CARL9170_RSP_FLAG		= 0xc0,
	CARL9170_RSP_PRETBTT		= 0xc0,
	CARL9170_RSP_TXCOMP		= 0xc1,
	CARL9170_RSP_BEACON_CONFIG	= 0xc2,
	CARL9170_RSP_ATIM		= 0xc3,
	CARL9170_RSP_WATCHDOG		= 0xc6,
	CARL9170_RSP_TEXT		= 0xca,
	CARL9170_RSP_HEXDUMP		= 0xcc,
	CARL9170_RSP_RADAR		= 0xcd,
	CARL9170_RSP_GPIO		= 0xce,
	CARL9170_RSP_BOOT		= 0xcf,
पूर्ण;

काष्ठा carl9170_set_key_cmd अणु
	__le16		user;
	__le16		keyId;
	__le16		type;
	u8		macAddr[6];
	u32		key[4];
पूर्ण __packed __aligned(4);
#घोषणा CARL9170_SET_KEY_CMD_SIZE		28

काष्ठा carl9170_disable_key_cmd अणु
	__le16		user;
	__le16		padding;
पूर्ण __packed __aligned(4);
#घोषणा CARL9170_DISABLE_KEY_CMD_SIZE		4

काष्ठा carl9170_u32_list अणु
	u32	vals[0];
पूर्ण __packed;

काष्ठा carl9170_reg_list अणु
	__le32		regs[0];
पूर्ण __packed;

काष्ठा carl9170_ग_लिखो_reg अणु
	काष्ठा अणु
		__le32		addr;
		__le32		val;
	पूर्ण regs[0] __packed;
पूर्ण __packed;

काष्ठा carl9170_ग_लिखो_reg_byte अणु
	__le32	addr;
	__le32  count;
	u8	val[];
पूर्ण __packed;

#घोषणा	CARL9170FW_PHY_HT_ENABLE		0x4
#घोषणा	CARL9170FW_PHY_HT_DYN2040		0x8
#घोषणा	CARL9170FW_PHY_HT_EXT_CHAN_OFF		0x3
#घोषणा	CARL9170FW_PHY_HT_EXT_CHAN_OFF_S	2

काष्ठा carl9170_rf_init अणु
	__le32		freq;
	u8		ht_settings;
	u8		padding2[3];
	__le32		delta_slope_coeff_exp;
	__le32		delta_slope_coeff_man;
	__le32		delta_slope_coeff_exp_shgi;
	__le32		delta_slope_coeff_man_shgi;
	__le32		finiteLoopCount;
पूर्ण __packed;
#घोषणा CARL9170_RF_INIT_SIZE		28

काष्ठा carl9170_rf_init_result अणु
	__le32		ret;		/* AR9170_PHY_REG_AGC_CONTROL */
पूर्ण __packed;
#घोषणा	CARL9170_RF_INIT_RESULT_SIZE	4

#घोषणा	CARL9170_PSM_SLEEP		0x1000
#घोषणा	CARL9170_PSM_SOFTWARE		0
#घोषणा	CARL9170_PSM_WAKE		0 /* पूर्णांकernally used. */
#घोषणा	CARL9170_PSM_COUNTER		0xfff
#घोषणा	CARL9170_PSM_COUNTER_S		0

काष्ठा carl9170_psm अणु
	__le32		state;
पूर्ण __packed;
#घोषणा CARL9170_PSM_SIZE		4

/*
 * Note: If a bit in rx_filter is set, then it
 * means that the particular frames which matches
 * the condition are FILTERED/REMOVED/DISCARDED!
 * (This is can be a bit confusing, especially
 * because someone people think it's the exact
 * opposite way, so watch out!)
 */
काष्ठा carl9170_rx_filter_cmd अणु
	__le32		rx_filter;
पूर्ण __packed;
#घोषणा CARL9170_RX_FILTER_CMD_SIZE	4

#घोषणा CARL9170_RX_FILTER_BAD		0x01
#घोषणा CARL9170_RX_FILTER_OTHER_RA	0x02
#घोषणा CARL9170_RX_FILTER_DECRY_FAIL	0x04
#घोषणा CARL9170_RX_FILTER_CTL_OTHER	0x08
#घोषणा CARL9170_RX_FILTER_CTL_PSPOLL	0x10
#घोषणा CARL9170_RX_FILTER_CTL_BACKR	0x20
#घोषणा CARL9170_RX_FILTER_MGMT		0x40
#घोषणा CARL9170_RX_FILTER_DATA		0x80
#घोषणा CARL9170_RX_FILTER_EVERYTHING	(~0)

काष्ठा carl9170_bcn_ctrl_cmd अणु
	__le32		vअगर_id;
	__le32		mode;
	__le32		bcn_addr;
	__le32		bcn_len;
पूर्ण __packed;
#घोषणा CARL9170_BCN_CTRL_CMD_SIZE	16

#घोषणा CARL9170_BCN_CTRL_DRAIN	0
#घोषणा CARL9170_BCN_CTRL_CAB_TRIGGER	1

काष्ठा carl9170_wol_cmd अणु
	__le32		flags;
	u8		mac[6];
	u8		bssid[6];
	__le32		null_पूर्णांकerval;
	__le32		मुक्त_क्रम_use2;
	__le32		mask;
	u8		pattern[32];
पूर्ण __packed;

#घोषणा CARL9170_WOL_CMD_SIZE		60

#घोषणा CARL9170_WOL_DISCONNECT		1
#घोषणा CARL9170_WOL_MAGIC_PKT		2

काष्ठा carl9170_cmd_head अणु
	जोड़ अणु
		काष्ठा अणु
			u8	len;
			u8	cmd;
			u8	seq;
			u8	ext;
		पूर्ण __packed;

		u32 hdr_data;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा carl9170_cmd अणु
	काष्ठा carl9170_cmd_head hdr;
	जोड़ अणु
		काष्ठा carl9170_set_key_cmd	setkey;
		काष्ठा carl9170_disable_key_cmd	disablekey;
		काष्ठा carl9170_u32_list	echo;
		काष्ठा carl9170_reg_list	rreg;
		काष्ठा carl9170_ग_लिखो_reg	wreg;
		काष्ठा carl9170_ग_लिखो_reg_byte	wregb;
		काष्ठा carl9170_rf_init		rf_init;
		काष्ठा carl9170_psm		psm;
		काष्ठा carl9170_wol_cmd		wol;
		काष्ठा carl9170_bcn_ctrl_cmd	bcn_ctrl;
		काष्ठा carl9170_rx_filter_cmd	rx_filter;
		u8 data[CARL9170_MAX_CMD_PAYLOAD_LEN];
	पूर्ण __packed __aligned(4);
पूर्ण __packed __aligned(4);

#घोषणा	CARL9170_TX_STATUS_QUEUE	3
#घोषणा	CARL9170_TX_STATUS_QUEUE_S	0
#घोषणा	CARL9170_TX_STATUS_RIX_S	2
#घोषणा	CARL9170_TX_STATUS_RIX		(3 << CARL9170_TX_STATUS_RIX_S)
#घोषणा	CARL9170_TX_STATUS_TRIES_S	4
#घोषणा	CARL9170_TX_STATUS_TRIES	(7 << CARL9170_TX_STATUS_TRIES_S)
#घोषणा	CARL9170_TX_STATUS_SUCCESS	0x80

#अगर_घोषित __CARL9170FW__
/*
 * NOTE:
 * Both काष्ठाs [carl9170_tx_status and _carl9170_tx_status]
 * need to be "bit for bit" in sync.
 */
काष्ठा carl9170_tx_status अणु
	/*
	 * Beware of compiler bugs in all gcc pre 4.4!
	 */

	u8 cookie;
	u8 queue:2;
	u8 rix:2;
	u8 tries:3;
	u8 success:1;
पूर्ण __packed;
#पूर्ण_अगर /* __CARL9170FW__ */

काष्ठा _carl9170_tx_status अणु
	/*
	 * This version should be immune to all alignment bugs.
	 */

	u8 cookie;
	u8 info;
पूर्ण __packed;
#घोषणा CARL9170_TX_STATUS_SIZE		2

#घोषणा	CARL9170_RSP_TX_STATUS_NUM	(CARL9170_MAX_CMD_PAYLOAD_LEN /	\
					 माप(काष्ठा _carl9170_tx_status))

#घोषणा	CARL9170_TX_MAX_RATE_TRIES	7

#घोषणा	CARL9170_TX_MAX_RATES		4
#घोषणा	CARL9170_TX_MAX_RETRY_RATES	(CARL9170_TX_MAX_RATES - 1)
#घोषणा	CARL9170_ERR_MAGIC		"ERR:"
#घोषणा	CARL9170_BUG_MAGIC		"BUG:"

काष्ठा carl9170_gpio अणु
	__le32 gpio;
पूर्ण __packed;
#घोषणा CARL9170_GPIO_SIZE		4

काष्ठा carl9170_tsf_rsp अणु
	जोड़ अणु
		__le32 tsf[2];
		__le64 tsf_64;
	पूर्ण __packed;
पूर्ण __packed;
#घोषणा CARL9170_TSF_RSP_SIZE		8

काष्ठा carl9170_tally_rsp अणु
	__le32 active;
	__le32 cca;
	__le32 tx_समय;
	__le32 rx_total;
	__le32 rx_overrun;
	__le32 tick;
पूर्ण __packed;

काष्ठा carl9170_rsp अणु
	काष्ठा carl9170_cmd_head hdr;

	जोड़ अणु
		काष्ठा carl9170_rf_init_result	rf_init_res;
		काष्ठा carl9170_u32_list	rreg_res;
		काष्ठा carl9170_u32_list	echo;
#अगर_घोषित __CARL9170FW__
		काष्ठा carl9170_tx_status	tx_status[0];
#पूर्ण_अगर /* __CARL9170FW__ */
		काष्ठा _carl9170_tx_status	_tx_status[0];
		काष्ठा carl9170_gpio		gpio;
		काष्ठा carl9170_tsf_rsp		tsf;
		काष्ठा carl9170_psm		psm;
		काष्ठा carl9170_tally_rsp	tally;
		u8 data[CARL9170_MAX_CMD_PAYLOAD_LEN];
	पूर्ण __packed;
पूर्ण __packed __aligned(4);

#पूर्ण_अगर /* __CARL9170_SHARED_FWCMD_H */
