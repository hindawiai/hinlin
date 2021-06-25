<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_MP_H_
#घोषणा __RTL871X_MP_H_

#घोषणा MPT_NOOP			0
#घोषणा MPT_READ_MAC_1BYTE		1
#घोषणा MPT_READ_MAC_2BYTE		2
#घोषणा MPT_READ_MAC_4BYTE		3
#घोषणा MPT_WRITE_MAC_1BYTE		4
#घोषणा MPT_WRITE_MAC_2BYTE		5
#घोषणा MPT_WRITE_MAC_4BYTE		6
#घोषणा MPT_READ_BB_CCK			7
#घोषणा MPT_WRITE_BB_CCK		8
#घोषणा MPT_READ_BB_OFDM		9
#घोषणा MPT_WRITE_BB_OFDM		10
#घोषणा MPT_READ_RF			11
#घोषणा MPT_WRITE_RF			12
#घोषणा MPT_READ_EEPROM_1BYTE		13
#घोषणा MPT_WRITE_EEPROM_1BYTE		14
#घोषणा MPT_READ_EEPROM_2BYTE		15
#घोषणा MPT_WRITE_EEPROM_2BYTE		16
#घोषणा MPT_SET_CSTHRESHOLD		21
#घोषणा MPT_SET_INITGAIN		22
#घोषणा MPT_SWITCH_BAND			23
#घोषणा MPT_SWITCH_CHANNEL		24
#घोषणा MPT_SET_DATARATE		25
#घोषणा MPT_SWITCH_ANTENNA		26
#घोषणा MPT_SET_TX_POWER		27
#घोषणा MPT_SET_CONT_TX			28
#घोषणा MPT_SET_SINGLE_CARRIER		29
#घोषणा MPT_SET_CARRIER_SUPPRESSION	30
#घोषणा MPT_GET_RATE_TABLE		31
#घोषणा MPT_READ_TSSI			32
#घोषणा MPT_GET_THERMAL_METER		33
#घोषणा MAX_MP_XMITBUF_SZ	2048
#घोषणा NR_MP_XMITFRAME		8

काष्ठा mp_xmit_frame अणु
	काष्ठा list_head list;
	काष्ठा pkt_attrib attrib;
	_pkt *pkt;
	पूर्णांक frame_tag;
	काष्ठा _adapter *padapter;
	u8 *mem_addr;
	u16 sz[8];
	काष्ठा urb *pxmit_urb[8];
	u8 bpending[8];
	u8 last[8];
पूर्ण;

काष्ठा mp_wiparam अणु
	u32 bcompleted;
	u32 act_type;
	u32 io_offset;
	u32 io_value;
पूर्ण;

काष्ठा mp_priv अणु
	काष्ठा _adapter *papdater;
	/*OID cmd handler*/
	काष्ठा mp_wiparam workparam;
	u8 act_in_progress;
	/*Tx Section*/
	u8 TID;
	u32 tx_pktcount;
	/*Rx Section*/
	u32 rx_pktcount;
	u32 rx_crcerrpktcount;
	u32 rx_pktloss;
	काष्ठा recv_stat rxstat;
	/*RF/BB relative*/
	u32 curr_ch;
	u32 curr_rateidx;
	u8 curr_bandwidth;
	u8 curr_modem;
	u8 curr_txघातeridx;
	u32 curr_crystalcap;
	u16 antenna_tx;
	u16 antenna_rx;
	u8 curr_rfpath;
	u8 check_mp_pkt;
	uपूर्णांक ForcedDataRate;
	काष्ठा wlan_network mp_network;
	अचिन्हित अक्षर network_macaddr[6];
	/*Testing Flag*/
	u32 mode;/*0 क्रम normal type packet,
		  * 1 क्रम loopback packet (16bytes TXCMD)
		  */
	sपूर्णांक prev_fw_state;
	u8 *pallocated_mp_xmitframe_buf;
	u8 *pmp_xmtframe_buf;
	काष्ठा  __queue मुक्त_mp_xmitqueue;
	u32 मुक्त_mp_xmitframe_cnt;
पूर्ण;

काष्ठा IOCMD_STRUCT अणु
	u8	cmdclass;
	u16	value;
	u8	index;
पूर्ण;

काष्ठा rf_reg_param अणु
	u32 path;
	u32 offset;
	u32 value;
पूर्ण;

काष्ठा bb_reg_param अणु
	u32 offset;
	u32 value;
पूर्ण;

/* ======================================================================= */

#घोषणा LOWER	true
#घोषणा RAISE	false
#घोषणा IOCMD_CTRL_REG			0x10250370
#घोषणा IOCMD_DATA_REG			0x10250374
#घोषणा IOCMD_GET_THERMAL_METER		0xFD000028
#घोषणा IOCMD_CLASS_BB_RF		0xF0
#घोषणा IOCMD_BB_READ_IDX		0x00
#घोषणा IOCMD_BB_WRITE_IDX		0x01
#घोषणा IOCMD_RF_READ_IDX		0x02
#घोषणा IOCMD_RF_WRIT_IDX		0x03
#घोषणा BB_REG_BASE_ADDR		0x800
#घोषणा RF_PATH_A	0
#घोषणा RF_PATH_B	1
#घोषणा RF_PATH_C	2
#घोषणा RF_PATH_D	3
#घोषणा MAX_RF_PATH_NUMS	2
#घोषणा _2MAC_MODE_	0
#घोषणा _LOOPBOOK_MODE_	1

/* MP set क्रमce data rate base on the definition. */
क्रमागत अणु
	/* CCK rate. */
	MPT_RATE_1M,	/* 0 */
	MPT_RATE_2M,
	MPT_RATE_55M,
	MPT_RATE_11M,	/* 3 */

	/* OFDM rate. */
	MPT_RATE_6M,	/* 4 */
	MPT_RATE_9M,
	MPT_RATE_12M,
	MPT_RATE_18M,
	MPT_RATE_24M,
	MPT_RATE_36M,
	MPT_RATE_48M,
	MPT_RATE_54M,	/* 11 */

	/* HT rate. */
	MPT_RATE_MCS0,	/* 12 */
	MPT_RATE_MCS1,
	MPT_RATE_MCS2,
	MPT_RATE_MCS3,
	MPT_RATE_MCS4,
	MPT_RATE_MCS5,
	MPT_RATE_MCS6,
	MPT_RATE_MCS7,	/* 19 */
	MPT_RATE_MCS8,
	MPT_RATE_MCS9,
	MPT_RATE_MCS10,
	MPT_RATE_MCS11,
	MPT_RATE_MCS12,
	MPT_RATE_MCS13,
	MPT_RATE_MCS14,
	MPT_RATE_MCS15,	/* 27 */
	MPT_RATE_LAST
पूर्ण;

/* Represent Channel Width in HT Capabilities */
क्रमागत HT_CHANNEL_WIDTH अणु
	HT_CHANNEL_WIDTH_20 = 0,
	HT_CHANNEL_WIDTH_40 = 1,
पूर्ण;

#घोषणा MAX_TX_PWR_INDEX_N_MODE 64	/* 0x3F */

क्रमागत POWER_MODE अणु
	POWER_LOW = 0,
	POWER_NORMAL
पूर्ण;

#घोषणा RX_PKT_BROADCAST	1
#घोषणा RX_PKT_DEST_ADDR	2
#घोषणा RX_PKT_PHY_MATCH	3

#घोषणा RPTMaxCount 0x000FFFFF

/* parameter 1 : BitMask
 *	bit 0  : OFDM PPDU
 *	bit 1  : OFDM False Alarm
 *	bit 2  : OFDM MPDU OK
 *	bit 3  : OFDM MPDU Fail
 *	bit 4  : CCK PPDU
 *	bit 5  : CCK False Alarm
 *	bit 6  : CCK MPDU ok
 *	bit 7  : CCK MPDU fail
 *	bit 8  : HT PPDU counter
 *	bit 9  : HT false alarm
 *	bit 10 : HT MPDU total
 *	bit 11 : HT MPDU OK
 *	bit 12 : HT MPDU fail
 *	bit 15 : RX full drop
 */
क्रमागत RXPHY_BITMASK अणु
	OFDM_PPDU_BIT = 0,
	OFDM_MPDU_OK_BIT,
	OFDM_MPDU_FAIL_BIT,
	CCK_PPDU_BIT,
	CCK_MPDU_OK_BIT,
	CCK_MPDU_FAIL_BIT,
	HT_PPDU_BIT,
	HT_MPDU_BIT,
	HT_MPDU_OK_BIT,
	HT_MPDU_FAIL_BIT,
पूर्ण;

क्रमागत ENCRY_CTRL_STATE अणु
	HW_CONTROL,		/*hw encryption& decryption*/
	SW_CONTROL,		/*sw encryption& decryption*/
	HW_ENCRY_SW_DECRY,	/*hw encryption & sw decryption*/
	SW_ENCRY_HW_DECRY	/*sw encryption & hw decryption*/
पूर्ण;

/* Bandwidth Offset */
#घोषणा HAL_PRIME_CHNL_OFFSET_DONT_CARE	0
#घोषणा HAL_PRIME_CHNL_OFFSET_LOWER	1
#घोषणा HAL_PRIME_CHNL_OFFSET_UPPER	2
/*=======================================================================*/
व्योम mp871xinit(काष्ठा _adapter *padapter);
व्योम mp871xdeinit(काष्ठा _adapter *padapter);
u32 r8712_bb_reg_पढ़ो(काष्ठा _adapter *Adapter, u16 offset);
u8 r8712_bb_reg_ग_लिखो(काष्ठा _adapter *Adapter, u16 offset, u32 value);
u32 r8712_rf_reg_पढ़ो(काष्ठा _adapter *Adapter, u8 path, u8 offset);
u8 r8712_rf_reg_ग_लिखो(काष्ठा _adapter *Adapter, u8 path,
		      u8 offset, u32 value);
u32 r8712_get_bb_reg(काष्ठा _adapter *Adapter, u16 offset, u32 biपंचांगask);
u8 r8712_set_bb_reg(काष्ठा _adapter *Adapter, u16 offset,
		    u32 biपंचांगask, u32 value);
u32 r8712_get_rf_reg(काष्ठा _adapter *Adapter, u8 path, u8 offset,
		     u32 biपंचांगask);
u8 r8712_set_rf_reg(काष्ठा _adapter *Adapter, u8 path, u8 offset,
		    u32 biपंचांगask, u32 value);

व्योम r8712_SetChannel(काष्ठा _adapter *pAdapter);
व्योम r8712_SetTxPower(काष्ठा _adapter *pAdapte);
व्योम r8712_SetTxAGCOffset(काष्ठा _adapter *pAdapter, u32 ulTxAGCOffset);
व्योम r8712_SetDataRate(काष्ठा _adapter *pAdapter);
व्योम r8712_SwitchBandwidth(काष्ठा _adapter *pAdapter);
व्योम r8712_SwitchAntenna(काष्ठा _adapter *pAdapter);
व्योम r8712_GetThermalMeter(काष्ठा _adapter *pAdapter, u32 *value);
व्योम r8712_SetContinuousTx(काष्ठा _adapter *pAdapter, u8 bStart);
व्योम r8712_SetSingleCarrierTx(काष्ठा _adapter *pAdapter, u8 bStart);
व्योम r8712_SetSingleToneTx(काष्ठा _adapter *pAdapter, u8 bStart);
व्योम r8712_SetCarrierSuppressionTx(काष्ठा _adapter *pAdapter, u8 bStart);
व्योम r8712_ResetPhyRxPktCount(काष्ठा _adapter *pAdapter);
u32 r8712_GetPhyRxPktReceived(काष्ठा _adapter *pAdapter);
u32 r8712_GetPhyRxPktCRC32Error(काष्ठा _adapter *pAdapter);

#पूर्ण_अगर /*__RTL871X_MP_H_*/

