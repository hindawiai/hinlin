<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित R8190P_DEF_H
#घोषणा R8190P_DEF_H

#समावेश <linux/types.h>

#घोषणा		MAX_SILENT_RESET_RX_SLOT_NUM	10

#घोषणा RX_MPDU_QUEUE				0

क्रमागत rtl819x_loopback अणु
	RTL819X_NO_LOOPBACK = 0,
	RTL819X_MAC_LOOPBACK = 1,
	RTL819X_DMA_LOOPBACK = 2,
	RTL819X_CCK_LOOPBACK = 3,
पूर्ण;

#घोषणा DESC90_RATE1M				0x00
#घोषणा DESC90_RATE2M				0x01
#घोषणा DESC90_RATE5_5M				0x02
#घोषणा DESC90_RATE11M				0x03
#घोषणा DESC90_RATE6M				0x04
#घोषणा DESC90_RATE9M				0x05
#घोषणा DESC90_RATE12M				0x06
#घोषणा DESC90_RATE18M				0x07
#घोषणा DESC90_RATE24M				0x08
#घोषणा DESC90_RATE36M				0x09
#घोषणा DESC90_RATE48M				0x0a
#घोषणा DESC90_RATE54M				0x0b
#घोषणा DESC90_RATEMCS0				0x00
#घोषणा DESC90_RATEMCS1				0x01
#घोषणा DESC90_RATEMCS2				0x02
#घोषणा DESC90_RATEMCS3				0x03
#घोषणा DESC90_RATEMCS4				0x04
#घोषणा DESC90_RATEMCS5				0x05
#घोषणा DESC90_RATEMCS6				0x06
#घोषणा DESC90_RATEMCS7				0x07
#घोषणा DESC90_RATEMCS8				0x08
#घोषणा DESC90_RATEMCS9				0x09
#घोषणा DESC90_RATEMCS10			0x0a
#घोषणा DESC90_RATEMCS11			0x0b
#घोषणा DESC90_RATEMCS12			0x0c
#घोषणा DESC90_RATEMCS13			0x0d
#घोषणा DESC90_RATEMCS14			0x0e
#घोषणा DESC90_RATEMCS15			0x0f
#घोषणा DESC90_RATEMCS32			0x20

#घोषणा SHORT_SLOT_TIME				9
#घोषणा NON_SHORT_SLOT_TIME		20

#घोषणा	RX_SMOOTH				20

#घोषणा QSLT_BK					0x1
#घोषणा QSLT_BE					0x0
#घोषणा QSLT_VI					0x4
#घोषणा QSLT_VO					0x6
#घोषणा	QSLT_BEACON			0x10
#घोषणा	QSLT_HIGH				0x11
#घोषणा	QSLT_MGNT				0x12
#घोषणा	QSLT_CMD				0x13

#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BK		0x007
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BE		0x0aa
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_VI		0x024
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_VO		0x007
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_MGNT		0x10
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BCN		0x4
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_PUB		0xd

#घोषणा APPLIED_RESERVED_QUEUE_IN_FW		0x80000000
#घोषणा RSVD_FW_QUEUE_PAGE_BK_SHIFT		0x00
#घोषणा RSVD_FW_QUEUE_PAGE_BE_SHIFT		0x08
#घोषणा RSVD_FW_QUEUE_PAGE_VI_SHIFT		0x10
#घोषणा RSVD_FW_QUEUE_PAGE_VO_SHIFT		0x18
#घोषणा RSVD_FW_QUEUE_PAGE_MGNT_SHIFT	0x10
#घोषणा RSVD_FW_QUEUE_PAGE_BCN_SHIFT		0x00
#घोषणा RSVD_FW_QUEUE_PAGE_PUB_SHIFT		0x08

#घोषणा HAL_PRIME_CHNL_OFFSET_DONT_CARE	0
#घोषणा HAL_PRIME_CHNL_OFFSET_LOWER		1
#घोषणा HAL_PRIME_CHNL_OFFSET_UPPER		2


क्रमागत version_8190_loopback अणु
	VERSION_8190_BD = 0x3,
	VERSION_8190_BE
पूर्ण;

#घोषणा IC_VersionCut_C	0x2
#घोषणा IC_VersionCut_D	0x3
#घोषणा IC_VersionCut_E	0x4

क्रमागत rf_optype अणु
	RF_OP_By_SW_3wire = 0,
	RF_OP_By_FW,
	RF_OP_MAX
पूर्ण;

काष्ठा bb_reg_definition अणु
	u32 rfपूर्णांकfs;
	u32 rfपूर्णांकfi;
	u32 rfपूर्णांकfo;
	u32 rfपूर्णांकfe;
	u32 rf3wireOffset;
	u32 rfLSSI_Select;
	u32 rfTxGainStage;
	u32 rfHSSIPara1;
	u32 rfHSSIPara2;
	u32 rfSwitchControl;
	u32 rfAGCControl1;
	u32 rfAGCControl2;
	u32 rfRxIQImbalance;
	u32 rfRxAFE;
	u32 rfTxIQImbalance;
	u32 rfTxAFE;
	u32 rfLSSIReadBack;
	u32 rfLSSIReadBackPi;
पूर्ण;

काष्ठा tx_fwinfo_8190pci अणु
	u8			TxRate:7;
	u8			CtsEnable:1;
	u8			RtsRate:7;
	u8			RtsEnable:1;
	u8			TxHT:1;
	u8			Short:1;
	u8			TxBandwidth:1;
	u8			TxSubCarrier:2;
	u8			STBC:2;
	u8			AllowAggregation:1;
	u8			RtsHT:1;
	u8			RtsShort:1;
	u8			RtsBandwidth:1;
	u8			RtsSubcarrier:2;
	u8			RtsSTBC:2;
	u8			EnableCPUDur:1;

	u32			RxMF:2;
	u32			RxAMD:3;
	u32			TxPerPktInfoFeedback:1;
	u32			Reserved1:2;
	u32			TxAGCOffset:4;
	u32			TxAGCSign:1;
	u32			RAW_TXD:1;
	u32			Retry_Limit:4;
	u32			Reserved2:1;
	u32			PacketID:13;


पूर्ण;

काष्ठा log_पूर्णांक_8190 अणु
	u32	nIMR_COMDOK;
	u32	nIMR_MGNTDOK;
	u32	nIMR_HIGH;
	u32	nIMR_VODOK;
	u32	nIMR_VIDOK;
	u32	nIMR_BEDOK;
	u32	nIMR_BKDOK;
	u32	nIMR_ROK;
	u32	nIMR_RCOK;
	u32	nIMR_TBDOK;
	u32	nIMR_BDOK;
	u32	nIMR_RXFOVW;
पूर्ण;

काष्ठा phy_ofdm_rx_status_rxsc_sgien_exपूर्णांकfflag अणु
	u8			reserved:4;
	u8			rxsc:2;
	u8			sgi_en:1;
	u8			ex_पूर्णांकf_flag:1;
पूर्ण;

काष्ठा phy_sts_ofdm_819xpci अणु
	u8	trsw_gain_X[4];
	u8	pwdb_all;
	u8	cfosho_X[4];
	u8	cfotail_X[4];
	u8	rxevm_X[2];
	u8	rxsnr_X[4];
	u8	pdsnr_X[2];
	u8	csi_current_X[2];
	u8	csi_target_X[2];
	u8	sigevm;
	u8	max_ex_pwr;
	u8	sgi_en;
	u8	rxsc_sgien_exflg;
पूर्ण;

काष्ठा phy_sts_cck_819xpci अणु
	u8	adc_pwdb_X[4];
	u8	sq_rpt;
	u8	cck_agc_rpt;
पूर्ण;


#घोषणा		PHY_RSSI_SLID_WIN_MAX				100
#घोषणा		PHY_Beacon_RSSI_SLID_WIN_MAX		10

काष्ठा tx_desc अणु
	u16	PktSize;
	u8	Offset;
	u8	Reserved1:3;
	u8	CmdInit:1;
	u8	LastSeg:1;
	u8	FirstSeg:1;
	u8	LINIP:1;
	u8	OWN:1;

	u8	TxFWInfoSize;
	u8	RATid:3;
	u8	DISFB:1;
	u8	USERATE:1;
	u8	MOREFRAG:1;
	u8	NoEnc:1;
	u8	PIFS:1;
	u8	QueueSelect:5;
	u8	NoACM:1;
	u8	Resv:2;
	u8	SecCAMID:5;
	u8	SecDescAssign:1;
	u8	SecType:2;

	u16	TxBufferSize;
	u8	PktId:7;
	u8	Resv1:1;
	u8	Reserved2;

	u32	TxBuffAddr;

	u32	NextDescAddress;

	u32	Reserved5;
	u32	Reserved6;
	u32	Reserved7;
पूर्ण;


काष्ठा tx_desc_cmd अणु
	u16	PktSize;
	u8	Reserved1;
	u8	CmdType:3;
	u8	CmdInit:1;
	u8	LastSeg:1;
	u8	FirstSeg:1;
	u8	LINIP:1;
	u8	OWN:1;

	u16	ElementReport;
	u16	Reserved2;

	u16	TxBufferSize;
	u16	Reserved3;

	u32	TxBuffAddr;
	u32	NextDescAddress;
	u32	Reserved4;
	u32	Reserved5;
	u32	Reserved6;
पूर्ण;

काष्ठा rx_desc अणु
	u16			Length:14;
	u16			CRC32:1;
	u16			ICV:1;
	u8			RxDrvInfoSize;
	u8			Shअगरt:2;
	u8			PHYStatus:1;
	u8			SWDec:1;
	u8			LastSeg:1;
	u8			FirstSeg:1;
	u8			EOR:1;
	u8			OWN:1;

	u32			Reserved2;

	u32			Reserved3;

	u32	BufferAddress;

पूर्ण;


काष्ठा rx_fwinfo अणु
	u16			Reserved1:12;
	u16			PartAggr:1;
	u16			FirstAGGR:1;
	u16			Reserved2:2;

	u8			RxRate:7;
	u8			RxHT:1;

	u8			BW:1;
	u8			SPLCP:1;
	u8			Reserved3:2;
	u8			PAM:1;
	u8			Mcast:1;
	u8			Bcast:1;
	u8			Reserved4:1;

	u32			TSFL;

पूर्ण;

#पूर्ण_अगर
