<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
 * RX/TX descriptor काष्ठाures
 */

/**
 * काष्ठा ath5k_hw_rx_ctl - Common hardware RX control descriptor
 * @rx_control_0: RX control word 0
 * @rx_control_1: RX control word 1
 */
काष्ठा ath5k_hw_rx_ctl अणु
	u32	rx_control_0;
	u32	rx_control_1;
पूर्ण __packed __aligned(4);

/* RX control word 1 fields/flags */
#घोषणा AR5K_DESC_RX_CTL1_BUF_LEN		0x00000fff /* data buffer length */
#घोषणा AR5K_DESC_RX_CTL1_INTREQ		0x00002000 /* RX पूर्णांकerrupt request */

/**
 * काष्ठा ath5k_hw_rx_status - Common hardware RX status descriptor
 * @rx_status_0: RX status word 0
 * @rx_status_1: RX status word 1
 *
 * 5210, 5211 and 5212 dअगरfer only in the fields and flags defined below
 */
काष्ठा ath5k_hw_rx_status अणु
	u32	rx_status_0;
	u32	rx_status_1;
पूर्ण __packed __aligned(4);

/* 5210/5211 */
/* RX status word 0 fields/flags */
#घोषणा AR5K_5210_RX_DESC_STATUS0_DATA_LEN		0x00000fff /* RX data length */
#घोषणा AR5K_5210_RX_DESC_STATUS0_MORE			0x00001000 /* more desc क्रम this frame */
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_ANT_5210	0x00004000 /* [5210] receive on ant 1 */
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_RATE		0x00078000 /* reception rate */
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_RATE_S	15
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_SIGNAL	0x07f80000 /* rssi */
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_SIGNAL_S	19
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_ANT_5211	0x38000000 /* [5211] receive antenna */
#घोषणा AR5K_5210_RX_DESC_STATUS0_RECEIVE_ANT_5211_S	27

/* RX status word 1 fields/flags */
#घोषणा AR5K_5210_RX_DESC_STATUS1_DONE			0x00000001 /* descriptor complete */
#घोषणा AR5K_5210_RX_DESC_STATUS1_FRAME_RECEIVE_OK	0x00000002 /* reception success */
#घोषणा AR5K_5210_RX_DESC_STATUS1_CRC_ERROR		0x00000004 /* CRC error */
#घोषणा AR5K_5210_RX_DESC_STATUS1_FIFO_OVERRUN_5210	0x00000008 /* [5210] FIFO overrun */
#घोषणा AR5K_5210_RX_DESC_STATUS1_DECRYPT_CRC_ERROR	0x00000010 /* decryption CRC failure */
#घोषणा AR5K_5210_RX_DESC_STATUS1_PHY_ERROR		0x000000e0 /* PHY error */
#घोषणा AR5K_5210_RX_DESC_STATUS1_PHY_ERROR_S		5
#घोषणा AR5K_5210_RX_DESC_STATUS1_KEY_INDEX_VALID	0x00000100 /* key index valid */
#घोषणा AR5K_5210_RX_DESC_STATUS1_KEY_INDEX		0x00007e00 /* decryption key index */
#घोषणा AR5K_5210_RX_DESC_STATUS1_KEY_INDEX_S		9
#घोषणा AR5K_5210_RX_DESC_STATUS1_RECEIVE_TIMESTAMP	0x0fff8000 /* 13 bit of TSF */
#घोषणा AR5K_5210_RX_DESC_STATUS1_RECEIVE_TIMESTAMP_S	15
#घोषणा AR5K_5210_RX_DESC_STATUS1_KEY_CACHE_MISS	0x10000000 /* key cache miss */

/* 5212 */
/* RX status word 0 fields/flags */
#घोषणा AR5K_5212_RX_DESC_STATUS0_DATA_LEN		0x00000fff /* RX data length */
#घोषणा AR5K_5212_RX_DESC_STATUS0_MORE			0x00001000 /* more desc क्रम this frame */
#घोषणा AR5K_5212_RX_DESC_STATUS0_DECOMP_CRC_ERROR	0x00002000 /* decompression CRC error */
#घोषणा AR5K_5212_RX_DESC_STATUS0_RECEIVE_RATE		0x000f8000 /* reception rate */
#घोषणा AR5K_5212_RX_DESC_STATUS0_RECEIVE_RATE_S	15
#घोषणा AR5K_5212_RX_DESC_STATUS0_RECEIVE_SIGNAL	0x0ff00000 /* rssi */
#घोषणा AR5K_5212_RX_DESC_STATUS0_RECEIVE_SIGNAL_S	20
#घोषणा AR5K_5212_RX_DESC_STATUS0_RECEIVE_ANTENNA	0xf0000000 /* receive antenna */
#घोषणा AR5K_5212_RX_DESC_STATUS0_RECEIVE_ANTENNA_S	28

/* RX status word 1 fields/flags */
#घोषणा AR5K_5212_RX_DESC_STATUS1_DONE			0x00000001 /* descriptor complete */
#घोषणा AR5K_5212_RX_DESC_STATUS1_FRAME_RECEIVE_OK	0x00000002 /* frame reception success */
#घोषणा AR5K_5212_RX_DESC_STATUS1_CRC_ERROR		0x00000004 /* CRC error */
#घोषणा AR5K_5212_RX_DESC_STATUS1_DECRYPT_CRC_ERROR	0x00000008 /* decryption CRC failure */
#घोषणा AR5K_5212_RX_DESC_STATUS1_PHY_ERROR		0x00000010 /* PHY error */
#घोषणा AR5K_5212_RX_DESC_STATUS1_MIC_ERROR		0x00000020 /* MIC decrypt error */
#घोषणा AR5K_5212_RX_DESC_STATUS1_KEY_INDEX_VALID	0x00000100 /* key index valid */
#घोषणा AR5K_5212_RX_DESC_STATUS1_KEY_INDEX		0x0000fe00 /* decryption key index */
#घोषणा AR5K_5212_RX_DESC_STATUS1_KEY_INDEX_S		9
#घोषणा AR5K_5212_RX_DESC_STATUS1_RECEIVE_TIMESTAMP	0x7fff0000 /* first 15bit of the TSF */
#घोषणा AR5K_5212_RX_DESC_STATUS1_RECEIVE_TIMESTAMP_S	16
#घोषणा AR5K_5212_RX_DESC_STATUS1_KEY_CACHE_MISS	0x80000000 /* key cache miss */
#घोषणा AR5K_5212_RX_DESC_STATUS1_PHY_ERROR_CODE	0x0000ff00 /* phy error code overlays key index and valid fields */
#घोषणा AR5K_5212_RX_DESC_STATUS1_PHY_ERROR_CODE_S	8

/**
 * क्रमागत ath5k_phy_error_code - PHY Error codes
 * @AR5K_RX_PHY_ERROR_UNDERRUN: Transmit underrun, [5210] No error
 * @AR5K_RX_PHY_ERROR_TIMING: Timing error
 * @AR5K_RX_PHY_ERROR_PARITY: Illegal parity
 * @AR5K_RX_PHY_ERROR_RATE: Illegal rate
 * @AR5K_RX_PHY_ERROR_LENGTH: Illegal length
 * @AR5K_RX_PHY_ERROR_RADAR: Radar detect, [5210] 64 QAM rate
 * @AR5K_RX_PHY_ERROR_SERVICE: Illegal service
 * @AR5K_RX_PHY_ERROR_TOR: Transmit override receive
 * @AR5K_RX_PHY_ERROR_OFDM_TIMING: OFDM Timing error [5212+]
 * @AR5K_RX_PHY_ERROR_OFDM_SIGNAL_PARITY: OFDM Signal parity error [5212+]
 * @AR5K_RX_PHY_ERROR_OFDM_RATE_ILLEGAL: OFDM Illegal rate [5212+]
 * @AR5K_RX_PHY_ERROR_OFDM_LENGTH_ILLEGAL: OFDM Illegal length [5212+]
 * @AR5K_RX_PHY_ERROR_OFDM_POWER_DROP: OFDM Power drop [5212+]
 * @AR5K_RX_PHY_ERROR_OFDM_SERVICE: OFDM Service (?) [5212+]
 * @AR5K_RX_PHY_ERROR_OFDM_RESTART: OFDM Restart (?) [5212+]
 * @AR5K_RX_PHY_ERROR_CCK_TIMING: CCK Timing error [5212+]
 * @AR5K_RX_PHY_ERROR_CCK_HEADER_CRC: Header CRC error [5212+]
 * @AR5K_RX_PHY_ERROR_CCK_RATE_ILLEGAL: Illegal rate [5212+]
 * @AR5K_RX_PHY_ERROR_CCK_SERVICE: CCK Service (?) [5212+]
 * @AR5K_RX_PHY_ERROR_CCK_RESTART: CCK Restart (?) [5212+]
 */
क्रमागत ath5k_phy_error_code अणु
	AR5K_RX_PHY_ERROR_UNDERRUN		= 0,
	AR5K_RX_PHY_ERROR_TIMING		= 1,
	AR5K_RX_PHY_ERROR_PARITY		= 2,
	AR5K_RX_PHY_ERROR_RATE			= 3,
	AR5K_RX_PHY_ERROR_LENGTH		= 4,
	AR5K_RX_PHY_ERROR_RADAR			= 5,
	AR5K_RX_PHY_ERROR_SERVICE		= 6,
	AR5K_RX_PHY_ERROR_TOR			= 7,
	AR5K_RX_PHY_ERROR_OFDM_TIMING		= 17,
	AR5K_RX_PHY_ERROR_OFDM_SIGNAL_PARITY	= 18,
	AR5K_RX_PHY_ERROR_OFDM_RATE_ILLEGAL	= 19,
	AR5K_RX_PHY_ERROR_OFDM_LENGTH_ILLEGAL	= 20,
	AR5K_RX_PHY_ERROR_OFDM_POWER_DROP	= 21,
	AR5K_RX_PHY_ERROR_OFDM_SERVICE		= 22,
	AR5K_RX_PHY_ERROR_OFDM_RESTART		= 23,
	AR5K_RX_PHY_ERROR_CCK_TIMING		= 25,
	AR5K_RX_PHY_ERROR_CCK_HEADER_CRC	= 26,
	AR5K_RX_PHY_ERROR_CCK_RATE_ILLEGAL	= 27,
	AR5K_RX_PHY_ERROR_CCK_SERVICE		= 30,
	AR5K_RX_PHY_ERROR_CCK_RESTART		= 31,
पूर्ण;

/**
 * काष्ठा ath5k_hw_2w_tx_ctl  - 5210/5211 hardware 2-word TX control descriptor
 * @tx_control_0: TX control word 0
 * @tx_control_1: TX control word 1
 */
काष्ठा ath5k_hw_2w_tx_ctl अणु
	u32	tx_control_0;
	u32	tx_control_1;
पूर्ण __packed __aligned(4);

/* TX control word 0 fields/flags */
#घोषणा AR5K_2W_TX_DESC_CTL0_FRAME_LEN		0x00000fff /* frame length */
#घोषणा AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210	0x0003f000 /* [5210] header length */
#घोषणा AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210_S	12
#घोषणा AR5K_2W_TX_DESC_CTL0_XMIT_RATE		0x003c0000 /* tx rate */
#घोषणा AR5K_2W_TX_DESC_CTL0_XMIT_RATE_S	18
#घोषणा AR5K_2W_TX_DESC_CTL0_RTSENA		0x00400000 /* RTS/CTS enable */
#घोषणा AR5K_2W_TX_DESC_CTL0_LONG_PACKET_5210	0x00800000 /* [5210] दीर्घ packet */
#घोषणा AR5K_2W_TX_DESC_CTL0_VEOL_5211		0x00800000 /* [5211] भव end-of-list */
#घोषणा AR5K_2W_TX_DESC_CTL0_CLRDMASK		0x01000000 /* clear destination mask */
#घोषणा AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT_5210	0x02000000 /* [5210] antenna selection */
#घोषणा AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT_5211	0x1e000000 /* [5211] antenna selection */
#घोषणा AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT			\
		(ah->ah_version == AR5K_AR5210 ?		\
		AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT_5210 :	\
		AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT_5211)
#घोषणा AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT_S	25
#घोषणा AR5K_2W_TX_DESC_CTL0_FRAME_TYPE_5210	0x1c000000 /* [5210] frame type */
#घोषणा AR5K_2W_TX_DESC_CTL0_FRAME_TYPE_5210_S	26
#घोषणा AR5K_2W_TX_DESC_CTL0_INTREQ		0x20000000 /* TX पूर्णांकerrupt request */
#घोषणा AR5K_2W_TX_DESC_CTL0_ENCRYPT_KEY_VALID	0x40000000 /* key is valid */

/* TX control word 1 fields/flags */
#घोषणा AR5K_2W_TX_DESC_CTL1_BUF_LEN		0x00000fff /* data buffer length */
#घोषणा AR5K_2W_TX_DESC_CTL1_MORE		0x00001000 /* more desc क्रम this frame */
#घोषणा AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX_5210	0x0007e000 /* [5210] key table index */
#घोषणा AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX_5211	0x000fe000 /* [5211] key table index */
#घोषणा AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX				\
			(ah->ah_version == AR5K_AR5210 ?		\
			AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX_5210 :		\
			AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX_5211)
#घोषणा AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX_S	13
#घोषणा AR5K_2W_TX_DESC_CTL1_FRAME_TYPE_5211	0x00700000 /* [5211] frame type */
#घोषणा AR5K_2W_TX_DESC_CTL1_FRAME_TYPE_5211_S	20
#घोषणा AR5K_2W_TX_DESC_CTL1_NOACK_5211		0x00800000 /* [5211] no ACK */
#घोषणा AR5K_2W_TX_DESC_CTL1_RTS_DURATION_5210	0xfff80000 /* [5210] lower 13 bit of duration */

/* Frame types */
#घोषणा AR5K_AR5210_TX_DESC_FRAME_TYPE_NORMAL	0
#घोषणा AR5K_AR5210_TX_DESC_FRAME_TYPE_ATIM	1
#घोषणा AR5K_AR5210_TX_DESC_FRAME_TYPE_PSPOLL	2
#घोषणा AR5K_AR5210_TX_DESC_FRAME_TYPE_NO_DELAY	3
#घोषणा AR5K_AR5211_TX_DESC_FRAME_TYPE_BEACON	3
#घोषणा AR5K_AR5210_TX_DESC_FRAME_TYPE_PIFS	4
#घोषणा AR5K_AR5211_TX_DESC_FRAME_TYPE_PRESP	4

/**
 * काष्ठा ath5k_hw_4w_tx_ctl - 5212 hardware 4-word TX control descriptor
 * @tx_control_0: TX control word 0
 * @tx_control_1: TX control word 1
 * @tx_control_2: TX control word 2
 * @tx_control_3: TX control word 3
 */
काष्ठा ath5k_hw_4w_tx_ctl अणु
	u32	tx_control_0;
	u32	tx_control_1;
	u32	tx_control_2;
	u32	tx_control_3;
पूर्ण __packed __aligned(4);

/* TX control word 0 fields/flags */
#घोषणा AR5K_4W_TX_DESC_CTL0_FRAME_LEN		0x00000fff /* frame length */
#घोषणा AR5K_4W_TX_DESC_CTL0_XMIT_POWER		0x003f0000 /* transmit घातer */
#घोषणा AR5K_4W_TX_DESC_CTL0_XMIT_POWER_S	16
#घोषणा AR5K_4W_TX_DESC_CTL0_RTSENA		0x00400000 /* RTS/CTS enable */
#घोषणा AR5K_4W_TX_DESC_CTL0_VEOL		0x00800000 /* भव end-of-list */
#घोषणा AR5K_4W_TX_DESC_CTL0_CLRDMASK		0x01000000 /* clear destination mask */
#घोषणा AR5K_4W_TX_DESC_CTL0_ANT_MODE_XMIT	0x1e000000 /* TX antenna selection */
#घोषणा AR5K_4W_TX_DESC_CTL0_ANT_MODE_XMIT_S	25
#घोषणा AR5K_4W_TX_DESC_CTL0_INTREQ		0x20000000 /* TX पूर्णांकerrupt request */
#घोषणा AR5K_4W_TX_DESC_CTL0_ENCRYPT_KEY_VALID	0x40000000 /* destination index valid */
#घोषणा AR5K_4W_TX_DESC_CTL0_CTSENA		0x80000000 /* precede frame with CTS */

/* TX control word 1 fields/flags */
#घोषणा AR5K_4W_TX_DESC_CTL1_BUF_LEN		0x00000fff /* data buffer length */
#घोषणा AR5K_4W_TX_DESC_CTL1_MORE		0x00001000 /* more desc क्रम this frame */
#घोषणा AR5K_4W_TX_DESC_CTL1_ENCRYPT_KEY_IDX	0x000fe000 /* destination table index */
#घोषणा AR5K_4W_TX_DESC_CTL1_ENCRYPT_KEY_IDX_S	13
#घोषणा AR5K_4W_TX_DESC_CTL1_FRAME_TYPE		0x00f00000 /* frame type */
#घोषणा AR5K_4W_TX_DESC_CTL1_FRAME_TYPE_S	20
#घोषणा AR5K_4W_TX_DESC_CTL1_NOACK		0x01000000 /* no ACK */
#घोषणा AR5K_4W_TX_DESC_CTL1_COMP_PROC		0x06000000 /* compression processing */
#घोषणा AR5K_4W_TX_DESC_CTL1_COMP_PROC_S	25
#घोषणा AR5K_4W_TX_DESC_CTL1_COMP_IV_LEN	0x18000000 /* length of frame IV */
#घोषणा AR5K_4W_TX_DESC_CTL1_COMP_IV_LEN_S	27
#घोषणा AR5K_4W_TX_DESC_CTL1_COMP_ICV_LEN	0x60000000 /* length of frame ICV */
#घोषणा AR5K_4W_TX_DESC_CTL1_COMP_ICV_LEN_S	29

/* TX control word 2 fields/flags */
#घोषणा AR5K_4W_TX_DESC_CTL2_RTS_DURATION	0x00007fff /* RTS/CTS duration */
#घोषणा AR5K_4W_TX_DESC_CTL2_DURATION_UPD_EN	0x00008000 /* frame duration update */
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES0	0x000f0000 /* series 0 max attempts */
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES0_S	16
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES1	0x00f00000 /* series 1 max attempts */
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES1_S	20
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES2	0x0f000000 /* series 2 max attempts */
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES2_S	24
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES3	0xf0000000 /* series 3 max attempts */
#घोषणा AR5K_4W_TX_DESC_CTL2_XMIT_TRIES3_S	28

/* TX control word 3 fields/flags */
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE0		0x0000001f /* series 0 tx rate */
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE1		0x000003e0 /* series 1 tx rate */
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE1_S	5
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE2		0x00007c00 /* series 2 tx rate */
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE2_S	10
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE3		0x000f8000 /* series 3 tx rate */
#घोषणा AR5K_4W_TX_DESC_CTL3_XMIT_RATE3_S	15
#घोषणा AR5K_4W_TX_DESC_CTL3_RTS_CTS_RATE	0x01f00000 /* RTS or CTS rate */
#घोषणा AR5K_4W_TX_DESC_CTL3_RTS_CTS_RATE_S	20

/**
 * काष्ठा ath5k_hw_tx_status - Common TX status descriptor
 * @tx_status_0: TX status word 0
 * @tx_status_1: TX status word 1
 */
काष्ठा ath5k_hw_tx_status अणु
	u32	tx_status_0;
	u32	tx_status_1;
पूर्ण __packed __aligned(4);

/* TX status word 0 fields/flags */
#घोषणा AR5K_DESC_TX_STATUS0_FRAME_XMIT_OK	0x00000001 /* TX success */
#घोषणा AR5K_DESC_TX_STATUS0_EXCESSIVE_RETRIES	0x00000002 /* excessive retries */
#घोषणा AR5K_DESC_TX_STATUS0_FIFO_UNDERRUN	0x00000004 /* FIFO underrun */
#घोषणा AR5K_DESC_TX_STATUS0_FILTERED		0x00000008 /* TX filter indication */
/* according to the HAL sources the spec has लघु/दीर्घ retry counts reversed.
 * we have it reversed to the HAL sources as well, क्रम 5210 and 5211.
 * For 5212 these fields are defined as RTS_FAIL_COUNT and DATA_FAIL_COUNT,
 * but used respectively as SHORT and LONG retry count in the code later. This
 * is consistent with the definitions here... TODO: check */
#घोषणा AR5K_DESC_TX_STATUS0_SHORT_RETRY_COUNT	0x000000f0 /* लघु retry count */
#घोषणा AR5K_DESC_TX_STATUS0_SHORT_RETRY_COUNT_S	4
#घोषणा AR5K_DESC_TX_STATUS0_LONG_RETRY_COUNT	0x00000f00 /* दीर्घ retry count */
#घोषणा AR5K_DESC_TX_STATUS0_LONG_RETRY_COUNT_S	8
#घोषणा AR5K_DESC_TX_STATUS0_VIRTCOLL_CT_5211	0x0000f000 /* [5211+] भव collision count */
#घोषणा AR5K_DESC_TX_STATUS0_VIRTCOLL_CT_5212_S	12
#घोषणा AR5K_DESC_TX_STATUS0_SEND_TIMESTAMP	0xffff0000 /* TX बारtamp */
#घोषणा AR5K_DESC_TX_STATUS0_SEND_TIMESTAMP_S	16

/* TX status word 1 fields/flags */
#घोषणा AR5K_DESC_TX_STATUS1_DONE		0x00000001 /* descriptor complete */
#घोषणा AR5K_DESC_TX_STATUS1_SEQ_NUM		0x00001ffe /* TX sequence number */
#घोषणा AR5K_DESC_TX_STATUS1_SEQ_NUM_S		1
#घोषणा AR5K_DESC_TX_STATUS1_ACK_SIG_STRENGTH	0x001fe000 /* संकेत strength of ACK */
#घोषणा AR5K_DESC_TX_STATUS1_ACK_SIG_STRENGTH_S	13
#घोषणा AR5K_DESC_TX_STATUS1_FINAL_TS_IX_5212	0x00600000 /* [5212] final TX attempt series ix */
#घोषणा AR5K_DESC_TX_STATUS1_FINAL_TS_IX_5212_S	21
#घोषणा AR5K_DESC_TX_STATUS1_COMP_SUCCESS_5212	0x00800000 /* [5212] compression status */
#घोषणा AR5K_DESC_TX_STATUS1_XMIT_ANTENNA_5212	0x01000000 /* [5212] transmit antenna */

/**
 * काष्ठा ath5k_hw_5210_tx_desc - 5210/5211 hardware TX descriptor
 * @tx_ctl: The &काष्ठा ath5k_hw_2w_tx_ctl
 * @tx_stat: The &काष्ठा ath5k_hw_tx_status
 */
काष्ठा ath5k_hw_5210_tx_desc अणु
	काष्ठा ath5k_hw_2w_tx_ctl	tx_ctl;
	काष्ठा ath5k_hw_tx_status	tx_stat;
पूर्ण __packed __aligned(4);

/**
 * काष्ठा ath5k_hw_5212_tx_desc - 5212 hardware TX descriptor
 * @tx_ctl: The &काष्ठा ath5k_hw_4w_tx_ctl
 * @tx_stat: The &काष्ठा ath5k_hw_tx_status
 */
काष्ठा ath5k_hw_5212_tx_desc अणु
	काष्ठा ath5k_hw_4w_tx_ctl	tx_ctl;
	काष्ठा ath5k_hw_tx_status	tx_stat;
पूर्ण __packed __aligned(4);

/**
 * काष्ठा ath5k_hw_all_rx_desc - Common hardware RX descriptor
 * @rx_ctl: The &काष्ठा ath5k_hw_rx_ctl
 * @rx_stat: The &काष्ठा ath5k_hw_rx_status
 */
काष्ठा ath5k_hw_all_rx_desc अणु
	काष्ठा ath5k_hw_rx_ctl		rx_ctl;
	काष्ठा ath5k_hw_rx_status	rx_stat;
पूर्ण __packed __aligned(4);

/**
 * काष्ठा ath5k_desc - Atheros hardware DMA descriptor
 * @ds_link: Physical address of the next descriptor
 * @ds_data: Physical address of data buffer (skb)
 * @ud: Union containing hw_5xxx_tx_desc काष्ठाs and hw_all_rx_desc
 *
 * This is पढ़ो and written to by the hardware
 */
काष्ठा ath5k_desc अणु
	u32	ds_link;
	u32	ds_data;

	जोड़ अणु
		काष्ठा ath5k_hw_5210_tx_desc	ds_tx5210;
		काष्ठा ath5k_hw_5212_tx_desc	ds_tx5212;
		काष्ठा ath5k_hw_all_rx_desc	ds_rx;
	पूर्ण ud;
पूर्ण __packed __aligned(4);

#घोषणा AR5K_RXDESC_INTREQ	0x0020

#घोषणा AR5K_TXDESC_CLRDMASK	0x0001
#घोषणा AR5K_TXDESC_NOACK	0x0002	/*[5211+]*/
#घोषणा AR5K_TXDESC_RTSENA	0x0004
#घोषणा AR5K_TXDESC_CTSENA	0x0008
#घोषणा AR5K_TXDESC_INTREQ	0x0010
#घोषणा AR5K_TXDESC_VEOL	0x0020	/*[5211+]*/
