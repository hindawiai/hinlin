<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*****************************************************************************
 *	Copyright(c) 2008,  RealTEK Technology Inc. All Right Reserved.
 *
 * Module:	__INC_HAL8192SPHYREG_H
 *
 *
 * Note:	1. Define PMAC/BB रेजिस्टर map
 *			2. Define RF रेजिस्टर map
 *			3. PMAC/BB रेजिस्टर bit mask.
 *			4. RF reg bit mask.
 *			5. Other BB/RF relative definition.
 *
 *
 * Export:	Constants, macro, functions(API), global variables(None).
 *
 * Abbrev:
 *
 * History:
 *	Data			Who		Remark
 *	08/07/2007	MHC		1. Porting from 9x series PHYCFG.h.
 *						2. Reorganize code architecture.
 *	09/25/2008	MH		1. Add RL6052 रेजिस्टर definition
 *
 *****************************************************************************/
#अगर_अघोषित __RTL871X_MP_PHY_REGDEF_H
#घोषणा __RTL871X_MP_PHY_REGDEF_H


/*--------------------------Define Parameters-------------------------------*/

/*============================================================
 *       8192S Register offset definition
 *============================================================
 *
 *
 * BB-PHY रेजिस्टर PMAC 0x100 PHY 0x800 - 0xEFF
 * 1. PMAC duplicate रेजिस्टर due to connection: RF_Mode, TRxRN, NumOf L-STF
 * 2. 0x800/0x900/0xA00/0xC00/0xD00/0xE00
 * 3. RF रेजिस्टर 0x00-2E
 * 4. Bit Mask क्रम BB/RF रेजिस्टर
 * 5. Other definition क्रम BB/RF R/W
 *
 * 1. PMAC duplicate रेजिस्टर due to connection: RF_Mode, TRxRN, NumOf L-STF
 * 1. Page1(0x100)
 */
#घोषणा	rPMAC_Reset			0x100
#घोषणा	rPMAC_TxStart			0x104
#घोषणा	rPMAC_TxLegacySIG		0x108
#घोषणा	rPMAC_TxHTSIG1			0x10c
#घोषणा	rPMAC_TxHTSIG2			0x110
#घोषणा	rPMAC_PHYDebug			0x114
#घोषणा	rPMAC_TxPacketNum		0x118
#घोषणा	rPMAC_TxIdle			0x11c
#घोषणा	rPMAC_TxMACHeader0		0x120
#घोषणा	rPMAC_TxMACHeader1		0x124
#घोषणा	rPMAC_TxMACHeader2		0x128
#घोषणा	rPMAC_TxMACHeader3		0x12c
#घोषणा	rPMAC_TxMACHeader4		0x130
#घोषणा	rPMAC_TxMACHeader5		0x134
#घोषणा	rPMAC_TxDataType		0x138
#घोषणा	rPMAC_TxRanकरोmSeed		0x13c
#घोषणा	rPMAC_CCKPLCPPreamble		0x140
#घोषणा	rPMAC_CCKPLCPHeader		0x144
#घोषणा	rPMAC_CCKCRC16			0x148
#घोषणा	rPMAC_OFDMRxCRC32OK		0x170
#घोषणा	rPMAC_OFDMRxCRC32Er		0x174
#घोषणा	rPMAC_OFDMRxParityEr		0x178
#घोषणा	rPMAC_OFDMRxCRC8Er		0x17c
#घोषणा	rPMAC_CCKCRxRC16Er		0x180
#घोषणा	rPMAC_CCKCRxRC32Er		0x184
#घोषणा	rPMAC_CCKCRxRC32OK		0x188
#घोषणा	rPMAC_TxStatus			0x18c

/*
 * 2. Page2(0x200)
 *
 * The following two definition are only used क्रम USB पूर्णांकerface.
 *#घोषणा RF_BB_CMD_ADDR	0x02c0	// RF/BB पढ़ो/ग_लिखो command address.
 *#घोषणा RF_BB_CMD_DATA	0x02c4	// RF/BB पढ़ो/ग_लिखो command data.
 *
 *
 * 3. Page8(0x800)
 */
#घोषणा	rFPGA0_RFMOD			0x800	/*RF mode & CCK TxSC RF
						 * BW Setting??
						 */
#घोषणा	rFPGA0_TxInfo			0x804	/* Status report?? */
#घोषणा	rFPGA0_PSDFunction		0x808
#घोषणा	rFPGA0_TxGainStage		0x80c	/* Set TX PWR init gain? */
#घोषणा	rFPGA0_RFTiming1		0x810	/* Useless now */
#घोषणा	rFPGA0_RFTiming2		0x814
#घोषणा	rFPGA0_XA_HSSIParameter1	0x820	/* RF 3 wire रेजिस्टर */
#घोषणा	rFPGA0_XA_HSSIParameter2	0x824
#घोषणा	rFPGA0_XB_HSSIParameter1	0x828
#घोषणा	rFPGA0_XB_HSSIParameter2	0x82c
#घोषणा	rFPGA0_XC_HSSIParameter1	0x830
#घोषणा	rFPGA0_XC_HSSIParameter2	0x834
#घोषणा	rFPGA0_XD_HSSIParameter1	0x838
#घोषणा	rFPGA0_XD_HSSIParameter2	0x83c
#घोषणा	rFPGA0_XA_LSSIParameter		0x840
#घोषणा	rFPGA0_XB_LSSIParameter		0x844
#घोषणा	rFPGA0_XC_LSSIParameter		0x848
#घोषणा	rFPGA0_XD_LSSIParameter		0x84c

#घोषणा	rFPGA0_RFWakeUpParameter	0x850	/* Useless now */
#घोषणा	rFPGA0_RFSleepUpParameter	0x854

#घोषणा	rFPGA0_XAB_SwitchControl	0x858	/* RF Channel चयन */
#घोषणा	rFPGA0_XCD_SwitchControl	0x85c

#घोषणा	rFPGA0_XA_RFInterfaceOE		0x860	/* RF Channel चयन */
#घोषणा	rFPGA0_XB_RFInterfaceOE		0x864
#घोषणा	rFPGA0_XC_RFInterfaceOE		0x868
#घोषणा	rFPGA0_XD_RFInterfaceOE		0x86c
#घोषणा	rFPGA0_XAB_RFInterfaceSW	0x870	/* RF Interface Software Ctrl */
#घोषणा	rFPGA0_XCD_RFInterfaceSW	0x874

#घोषणा	rFPGA0_XAB_RFParameter		0x878	/* RF Parameter */
#घोषणा	rFPGA0_XCD_RFParameter		0x87c

#घोषणा	rFPGA0_AnalogParameter1		0x880	/* Crystal cap setting
						 * RF-R/W protection
						 * क्रम parameter4??
						 */
#घोषणा	rFPGA0_AnalogParameter2		0x884
#घोषणा	rFPGA0_AnalogParameter3		0x888	/* Useless now */
#घोषणा	rFPGA0_AnalogParameter4		0x88c

#घोषणा	rFPGA0_XA_LSSIReadBack		0x8a0	/* Tranceiver LSSI Readback */
#घोषणा	rFPGA0_XB_LSSIReadBack		0x8a4
#घोषणा	rFPGA0_XC_LSSIReadBack		0x8a8
#घोषणा	rFPGA0_XD_LSSIReadBack		0x8ac

#घोषणा	rFPGA0_PSDReport		0x8b4	/* Useless now */
#घोषणा	rFPGA0_XAB_RFInterfaceRB	0x8e0	/* Useless now */
#घोषणा	rFPGA0_XCD_RFInterfaceRB	0x8e4	/* Useless now */

/*
 * 4. Page9(0x900)
 */
#घोषणा	rFPGA1_RFMOD			0x900	/* RF mode & OFDM TxSC */

#घोषणा	rFPGA1_TxBlock			0x904	/* Useless now */
#घोषणा	rFPGA1_DebugSelect		0x908	/* Useless now */
#घोषणा	rFPGA1_TxInfo			0x90c	/* Useless now */

/*
 * 5. PageA(0xA00)
 *
 * Set Control channel to upper or lower.
 * These settings are required only क्रम 40MHz
 */
#घोषणा	rCCK0_System			0xa00

#घोषणा	rCCK0_AFESetting		0xa04	/* Disable init gain now */
#घोषणा	rCCK0_CCA			0xa08	/* Disable init gain now */

#घोषणा	rCCK0_RxAGC1			0xa0c
/* AGC शेष value, saturation level
 * Antenna Diversity, RX AGC, LNA Threshold, RX LNA Threshold useless now.
 * Not the same as 90 series
 */
#घोषणा	rCCK0_RxAGC2			0xa10	/* AGC & DAGC */

#घोषणा	rCCK0_RxHP			0xa14

#घोषणा	rCCK0_DSPParameter1		0xa18	/* Timing recovery & Channel
						 * estimation threshold
						 */
#घोषणा	rCCK0_DSPParameter2		0xa1c	/* SQ threshold */

#घोषणा	rCCK0_TxFilter1			0xa20
#घोषणा	rCCK0_TxFilter2			0xa24
#घोषणा	rCCK0_DebugPort			0xa28	/* debug port and Tx filter3 */
#घोषणा	rCCK0_FalseAlarmReport		0xa2c	/* 0xa2d useless now 0xa30-a4f
						 * channel report
						 */
#घोषणा	rCCK0_TRSSIReport		0xa50
#घोषणा	rCCK0_RxReport			0xa54   /* 0xa57 */
#घोषणा	rCCK0_FACounterLower		0xa5c   /* 0xa5b */
#घोषणा	rCCK0_FACounterUpper		0xa58   /* 0xa5c */

/*
 * 6. PageC(0xC00)
 */
#घोषणा	rOFDM0_LSTF			0xc00
#घोषणा	rOFDM0_TRxPathEnable		0xc04
#घोषणा	rOFDM0_TRMuxPar			0xc08
#घोषणा	rOFDM0_TRSWIsolation		0xc0c

/*RxIQ DC offset, Rx digital filter, DC notch filter */
#घोषणा	rOFDM0_XARxAFE			0xc10
#घोषणा	rOFDM0_XARxIQImbalance		0xc14  /* RxIQ imbalance matrix */
#घोषणा	rOFDM0_XBRxAFE			0xc18
#घोषणा	rOFDM0_XBRxIQImbalance		0xc1c
#घोषणा	rOFDM0_XCRxAFE			0xc20
#घोषणा	rOFDM0_XCRxIQImbalance		0xc24
#घोषणा	rOFDM0_XDRxAFE			0xc28
#घोषणा	rOFDM0_XDRxIQImbalance		0xc2c

#घोषणा	rOFDM0_RxDetector1		0xc30  /* PD,BW & SBD DM tune
						* init gain
						*/
#घोषणा	rOFDM0_RxDetector2		0xc34  /* SBD & Fame Sync. */
#घोषणा	rOFDM0_RxDetector3		0xc38  /* Frame Sync. */
#घोषणा	rOFDM0_RxDetector4		0xc3c  /* PD, SBD, Frame Sync &
						* Short-GI
						*/

#घोषणा	rOFDM0_RxDSP			0xc40  /* Rx Sync Path */
#घोषणा	rOFDM0_CFOandDAGC		0xc44  /* CFO & DAGC */
#घोषणा	rOFDM0_CCADropThreshold		0xc48 /* CCA Drop threshold */
#घोषणा	rOFDM0_ECCAThreshold		0xc4c /* energy CCA */

#घोषणा	rOFDM0_XAAGCCore1		0xc50	/* DIG */
#घोषणा	rOFDM0_XAAGCCore2		0xc54
#घोषणा	rOFDM0_XBAGCCore1		0xc58
#घोषणा	rOFDM0_XBAGCCore2		0xc5c
#घोषणा	rOFDM0_XCAGCCore1		0xc60
#घोषणा	rOFDM0_XCAGCCore2		0xc64
#घोषणा	rOFDM0_XDAGCCore1		0xc68
#घोषणा	rOFDM0_XDAGCCore2		0xc6c
#घोषणा	rOFDM0_AGCParameter1		0xc70
#घोषणा	rOFDM0_AGCParameter2		0xc74
#घोषणा	rOFDM0_AGCRSSITable		0xc78
#घोषणा	rOFDM0_HTSTFAGC			0xc7c

#घोषणा	rOFDM0_XATxIQImbalance		0xc80	/* TX PWR TRACK and DIG */
#घोषणा	rOFDM0_XATxAFE			0xc84
#घोषणा	rOFDM0_XBTxIQImbalance		0xc88
#घोषणा	rOFDM0_XBTxAFE			0xc8c
#घोषणा	rOFDM0_XCTxIQImbalance		0xc90
#घोषणा	rOFDM0_XCTxAFE			0xc94
#घोषणा	rOFDM0_XDTxIQImbalance		0xc98
#घोषणा	rOFDM0_XDTxAFE			0xc9c

#घोषणा	rOFDM0_RxHPParameter		0xce0
#घोषणा	rOFDM0_TxPseuकरोNoiseWgt		0xce4
#घोषणा	rOFDM0_FrameSync		0xcf0
#घोषणा	rOFDM0_DFSReport		0xcf4
#घोषणा	rOFDM0_TxCoeff1			0xca4
#घोषणा	rOFDM0_TxCoeff2			0xca8
#घोषणा	rOFDM0_TxCoeff3			0xcac
#घोषणा	rOFDM0_TxCoeff4			0xcb0
#घोषणा	rOFDM0_TxCoeff5			0xcb4
#घोषणा	rOFDM0_TxCoeff6			0xcb8

/*
 * 7. PageD(0xD00)
 */
#घोषणा	rOFDM1_LSTF			0xd00
#घोषणा	rOFDM1_TRxPathEnable		0xd04

#घोषणा	rOFDM1_CFO			0xd08	/* No setting now */
#घोषणा	rOFDM1_CSI1			0xd10
#घोषणा	rOFDM1_SBD			0xd14
#घोषणा	rOFDM1_CSI2			0xd18
#घोषणा	rOFDM1_CFOTracking		0xd2c
#घोषणा	rOFDM1_TRxMesaure1		0xd34
#घोषणा	rOFDM1_IntfDet			0xd3c
#घोषणा	rOFDM1_PseuकरोNoiseStateAB	0xd50
#घोषणा	rOFDM1_PseuकरोNoiseStateCD	0xd54
#घोषणा	rOFDM1_RxPseuकरोNoiseWgt		0xd58

#घोषणा	rOFDM_PHYCounter1		0xda0  /* cca, parity fail */
#घोषणा	rOFDM_PHYCounter2		0xda4  /* rate illegal, crc8 fail */
#घोषणा	rOFDM_PHYCounter3		0xda8  /* MCS not support */
#घोषणा	rOFDM_ShortCFOAB		0xdac  /* No setting now */
#घोषणा	rOFDM_ShortCFOCD		0xdb0
#घोषणा	rOFDM_LongCFOAB			0xdb4
#घोषणा	rOFDM_LongCFOCD			0xdb8
#घोषणा	rOFDM_TailCFOAB			0xdbc
#घोषणा	rOFDM_TailCFOCD			0xdc0
#घोषणा	rOFDM_PWMeasure1		0xdc4
#घोषणा	rOFDM_PWMeasure2		0xdc8
#घोषणा	rOFDM_BWReport			0xdcc
#घोषणा	rOFDM_AGCReport			0xdd0
#घोषणा	rOFDM_RxSNR			0xdd4
#घोषणा	rOFDM_RxEVMCSI			0xdd8
#घोषणा	rOFDM_SIGReport			0xddc

/*
 * 8. PageE(0xE00)
 */
#घोषणा	rTxAGC_Rate18_06		0xe00
#घोषणा	rTxAGC_Rate54_24		0xe04
#घोषणा	rTxAGC_CCK_Mcs32		0xe08
#घोषणा	rTxAGC_Mcs03_Mcs00		0xe10
#घोषणा	rTxAGC_Mcs07_Mcs04		0xe14
#घोषणा	rTxAGC_Mcs11_Mcs08		0xe18
#घोषणा	rTxAGC_Mcs15_Mcs12		0xe1c

/* Analog- control in RX_WAIT_CCA : REG: EE0
 * [Analog- Power & Control Register]
 */
#घोषणा		rRx_Wait_CCCA		0xe70
#घोषणा	rAnapar_Ctrl_BB			0xee0

/*
 * 7. RF Register 0x00-0x2E (RF 8256)
 *    RF-0222D 0x00-3F
 *
 * Zebra1
 */
#घोषणा	rZebra1_HSSIEnable		0x0	/* Useless now */
#घोषणा	rZebra1_TRxEnable1		0x1
#घोषणा	rZebra1_TRxEnable2		0x2
#घोषणा	rZebra1_AGC			0x4
#घोषणा	rZebra1_ChargePump		0x5
#घोषणा	rZebra1_Channel			0x7	/* RF channel चयन */
#घोषणा	rZebra1_TxGain			0x8	/* Useless now */
#घोषणा	rZebra1_TxLPF			0x9
#घोषणा	rZebra1_RxLPF			0xb
#घोषणा	rZebra1_RxHPFCorner		0xc

/* Zebra4 */
#घोषणा	rGlobalCtrl			0	/* Useless now */
#घोषणा	rRTL8256_TxLPF			19
#घोषणा	rRTL8256_RxLPF			11

/* RTL8258 */
#घोषणा	rRTL8258_TxLPF			0x11	/* Useless now */
#घोषणा	rRTL8258_RxLPF			0x13
#घोषणा	rRTL8258_RSSILPF		0xa

/* RL6052 Register definition */
#घोषणा	RF_AC				0x00
#घोषणा	RF_IQADJ_G1			0x01
#घोषणा	RF_IQADJ_G2			0x02
#घोषणा	RF_POW_TRSW			0x05

#घोषणा	RF_GAIN_RX			0x06
#घोषणा	RF_GAIN_TX			0x07

#घोषणा	RF_TXM_IDAC			0x08
#घोषणा	RF_BS_IQGEN			0x0F

#घोषणा	RF_MODE1			0x10
#घोषणा	RF_MODE2			0x11

#घोषणा	RF_RX_AGC_HP			0x12
#घोषणा	RF_TX_AGC			0x13
#घोषणा	RF_BIAS				0x14
#घोषणा	RF_IPA				0x15
#घोषणा	RF_POW_ABILITY			0x17
#घोषणा	RF_MODE_AG			0x18
#घोषणा	rRfChannel			0x18	/* RF channel and BW चयन */
#घोषणा	RF_CHNLBW			0x18	/* RF channel and BW चयन */
#घोषणा	RF_TOP				0x19
#घोषणा	RF_RX_G1			0x1A
#घोषणा	RF_RX_G2			0x1B
#घोषणा	RF_RX_BB2			0x1C
#घोषणा	RF_RX_BB1			0x1D

#घोषणा	RF_RCK1				0x1E
#घोषणा	RF_RCK2				0x1F

#घोषणा	RF_TX_G1			0x20
#घोषणा	RF_TX_G2			0x21
#घोषणा	RF_TX_G3			0x22

#घोषणा	RF_TX_BB1			0x23
#घोषणा	RF_T_METER			0x24

#घोषणा	RF_SYN_G1			0x25	/* RF TX Power control */
#घोषणा	RF_SYN_G2			0x26	/* RF TX Power control */
#घोषणा	RF_SYN_G3			0x27	/* RF TX Power control */
#घोषणा	RF_SYN_G4			0x28	/* RF TX Power control */
#घोषणा	RF_SYN_G5			0x29	/* RF TX Power control */
#घोषणा	RF_SYN_G6			0x2A	/* RF TX Power control */
#घोषणा	RF_SYN_G7			0x2B	/* RF TX Power control */
#घोषणा	RF_SYN_G8			0x2C	/* RF TX Power control */

#घोषणा	RF_RCK_OS			0x30	/* RF TX PA control */

#घोषणा	RF_TXPA_G1			0x31	/* RF TX PA control */
#घोषणा	RF_TXPA_G2			0x32	/* RF TX PA control */
#घोषणा	RF_TXPA_G3			0x33	/* RF TX PA control */

/*
 * Bit Mask
 *
 * 1. Page1(0x100)
 */
#घोषणा	bBBResetB			0x100	/* Useless now? */
#घोषणा	bGlobalResetB			0x200
#घोषणा	bOFDMTxStart			0x4
#घोषणा	bCCKTxStart			0x8
#घोषणा	bCRC32Debug			0x100
#घोषणा	bPMACLoopback			0x10
#घोषणा	bTxLSIG				0xffffff
#घोषणा	bOFDMTxRate			0xf
#घोषणा	bOFDMTxReserved			0x10
#घोषणा	bOFDMTxLength			0x1ffe0
#घोषणा	bOFDMTxParity			0x20000
#घोषणा	bTxHTSIG1			0xffffff
#घोषणा	bTxHTMCSRate			0x7f
#घोषणा	bTxHTBW				0x80
#घोषणा	bTxHTLength			0xffff00
#घोषणा	bTxHTSIG2			0xffffff
#घोषणा	bTxHTSmoothing			0x1
#घोषणा	bTxHTSounding			0x2
#घोषणा	bTxHTReserved			0x4
#घोषणा	bTxHTAggreation			0x8
#घोषणा	bTxHTSTBC			0x30
#घोषणा	bTxHTAdvanceCoding		0x40
#घोषणा	bTxHTShortGI			0x80
#घोषणा	bTxHTNumberHT_LTF		0x300
#घोषणा	bTxHTCRC8			0x3fc00
#घोषणा	bCounterReset			0x10000
#घोषणा	bNumOfOFDMTx			0xffff
#घोषणा	bNumOfCCKTx			0xffff0000
#घोषणा	bTxIdleInterval			0xffff
#घोषणा	bOFDMService			0xffff0000
#घोषणा	bTxMACHeader			0xffffffff
#घोषणा	bTxDataInit			0xff
#घोषणा	bTxHTMode			0x100
#घोषणा	bTxDataType			0x30000
#घोषणा	bTxRanकरोmSeed			0xffffffff
#घोषणा	bCCKTxPreamble			0x1
#घोषणा	bCCKTxSFD			0xffff0000
#घोषणा	bCCKTxSIG			0xff
#घोषणा	bCCKTxService			0xff00
#घोषणा	bCCKLengthExt			0x8000
#घोषणा	bCCKTxLength			0xffff0000
#घोषणा	bCCKTxCRC16			0xffff
#घोषणा	bCCKTxStatus			0x1
#घोषणा	bOFDMTxStatus			0x2
#घोषणा IS_BB_REG_OFFSET_92S(_Offset)	((_Offset >= 0x800) && \
					(_Offset <= 0xfff))

/* 2. Page8(0x800) */
#घोषणा	bRFMOD			0x1	/* Reg 0x800 rFPGA0_RFMOD */
#घोषणा	bJapanMode		0x2
#घोषणा	bCCKTxSC		0x30
#घोषणा	bCCKEn			0x1000000
#घोषणा	bOFDMEn			0x2000000

#घोषणा	bOFDMRxADCPhase         0x10000	/* Useless now */
#घोषणा	bOFDMTxDACPhase         0x40000
#घोषणा	bXATxAGC                0x3f
#घोषणा	bXBTxAGC                0xf00	/* Reg 80c rFPGA0_TxGainStage */
#घोषणा	bXCTxAGC                0xf000
#घोषणा	bXDTxAGC                0xf0000

#घोषणा	bPAStart		0xf0000000	/* Useless now */
#घोषणा	bTRStart		0x00f00000
#घोषणा	bRFStart		0x0000f000
#घोषणा	bBBStart		0x000000f0
#घोषणा	bBBCCKStart		0x0000000f
#घोषणा	bPAEnd			0xf          /* Reg0x814 */
#घोषणा	bTREnd			0x0f000000
#घोषणा	bRFEnd			0x000f0000
#घोषणा	bCCAMask		0x000000f0   /* T2R */
#घोषणा	bR2RCCAMask		0x00000f00
#घोषणा	bHSSI_R2TDelay		0xf8000000
#घोषणा	bHSSI_T2RDelay		0xf80000
#घोषणा	bContTxHSSI		0x400     /* change gain at जारी Tx */
#घोषणा	bIGFromCCK		0x200
#घोषणा	bAGCAddress		0x3f
#घोषणा	bRxHPTx			0x7000
#घोषणा	bRxHPT2R		0x38000
#घोषणा	bRxHPCCKIni		0xc0000
#घोषणा	bAGCTxCode		0xc00000
#घोषणा	bAGCRxCode		0x300000
#घोषणा	b3WireDataLength	0x800	/* Reg 0x820~84f rFPGA0_XA_HSSIParm1 */
#घोषणा	b3WireAddressLength	0x400
#घोषणा	b3WireRFPowerDown	0x1	/* Useless now */
#घोषणा	b5GPAPEPolarity		0x40000000
#घोषणा	b2GPAPEPolarity		0x80000000
#घोषणा	bRFSW_TxDefaultAnt	0x3
#घोषणा	bRFSW_TxOptionAnt	0x30
#घोषणा	bRFSW_RxDefaultAnt	0x300
#घोषणा	bRFSW_RxOptionAnt	0x3000
#घोषणा	bRFSI_3WireData		0x1
#घोषणा	bRFSI_3WireClock	0x2
#घोषणा	bRFSI_3WireLoad		0x4
#घोषणा	bRFSI_3WireRW		0x8
#घोषणा	bRFSI_3Wire		0xf
#घोषणा	bRFSI_RFENV		0x10	/* Reg 0x870 rFPGA0_XAB_RFInterfaceSW */
#घोषणा	bRFSI_TRSW		0x20	/* Useless now */
#घोषणा	bRFSI_TRSWB		0x40
#घोषणा	bRFSI_ANTSW		0x100
#घोषणा	bRFSI_ANTSWB		0x200
#घोषणा	bRFSI_PAPE		0x400
#घोषणा	bRFSI_PAPE5G		0x800
#घोषणा	bBandSelect		0x1
#घोषणा	bHTSIG2_GI		0x80
#घोषणा	bHTSIG2_Smoothing	0x01
#घोषणा	bHTSIG2_Sounding	0x02
#घोषणा	bHTSIG2_Aggreaton	0x08
#घोषणा	bHTSIG2_STBC		0x30
#घोषणा	bHTSIG2_AdvCoding	0x40
#घोषणा	bHTSIG2_NumOfHTLTF	0x300
#घोषणा	bHTSIG2_CRC8		0x3fc
#घोषणा	bHTSIG1_MCS		0x7f
#घोषणा	bHTSIG1_BandWidth	0x80
#घोषणा	bHTSIG1_HTLength	0xffff
#घोषणा	bLSIG_Rate		0xf
#घोषणा	bLSIG_Reserved		0x10
#घोषणा	bLSIG_Length		0x1fffe
#घोषणा	bLSIG_Parity		0x20
#घोषणा	bCCKRxPhase		0x4
#घोषणा	bLSSIReadAddress	0x7f800000   /* T65 RF */
#घोषणा	bLSSIReadEdge		0x80000000   /* LSSI "Read" edge संकेत */
#घोषणा	bLSSIReadBackData	0xfffff		/* T65 RF */
#घोषणा	bLSSIReadOKFlag		0x1000	/* Useless now */
#घोषणा	bCCKSampleRate		0x8       /*0: 44MHz, 1:88MHz*/
#घोषणा	bRegulator0Standby	0x1
#घोषणा	bRegulatorPLLStandby	0x2
#घोषणा	bRegulator1Standby	0x4
#घोषणा	bPLLPowerUp		0x8
#घोषणा	bDPLLPowerUp		0x10
#घोषणा	bDA10PowerUp		0x20
#घोषणा	bAD7PowerUp		0x200
#घोषणा	bDA6PowerUp		0x2000
#घोषणा	bXtalPowerUp		0x4000
#घोषणा	b40MDClkPowerUP		0x8000
#घोषणा	bDA6DebugMode		0x20000
#घोषणा	bDA6Swing		0x380000

/* Reg 0x880 rFPGA0_AnalogParameter1 20/40 CCK support चयन 40/80 BB MHZ */
#घोषणा	bADClkPhase		0x4000000

#घोषणा	b80MClkDelay		0x18000000	/* Useless */
#घोषणा	bAFEWatchDogEnable	0x20000000

/* Reg 0x884 rFPGA0_AnalogParameter2 Crystal cap */
#घोषणा	bXtalCap01		0xc0000000
#घोषणा	bXtalCap23		0x3
#घोषणा	bXtalCap92x		0x0f000000
#घोषणा bXtalCap		0x0f000000
#घोषणा	bIntDअगरClkEnable	0x400	/* Useless */
#घोषणा	bExtSigClkEnable	0x800
#घोषणा	bBandgapMbiasPowerUp	0x10000
#घोषणा	bAD11SHGain		0xc0000
#घोषणा	bAD11InputRange		0x700000
#घोषणा	bAD11OPCurrent		0x3800000
#घोषणा	bIPathLoopback		0x4000000
#घोषणा	bQPathLoopback		0x8000000
#घोषणा	bAFELoopback		0x10000000
#घोषणा	bDA10Swing		0x7e0
#घोषणा	bDA10Reverse		0x800
#घोषणा	bDAClkSource		0x1000
#घोषणा	bAD7InputRange		0x6000
#घोषणा	bAD7Gain		0x38000
#घोषणा	bAD7OutputCMMode	0x40000
#घोषणा	bAD7InputCMMode		0x380000
#घोषणा	bAD7Current		0xc00000
#घोषणा	bRegulatorAdjust	0x7000000
#घोषणा	bAD11PowerUpAtTx	0x1
#घोषणा	bDA10PSAtTx		0x10
#घोषणा	bAD11PowerUpAtRx	0x100
#घोषणा	bDA10PSAtRx		0x1000
#घोषणा	bCCKRxAGCFormat		0x200
#घोषणा	bPSDFFTSamplepPoपूर्णांक	0xc000
#घोषणा	bPSDAverageNum		0x3000
#घोषणा	bIQPathControl		0xc00
#घोषणा	bPSDFreq		0x3ff
#घोषणा	bPSDAntennaPath		0x30
#घोषणा	bPSDIQSwitch		0x40
#घोषणा	bPSDRxTrigger		0x400000
#घोषणा	bPSDTxTrigger		0x80000000
#घोषणा	bPSDSineToneScale	0x7f000000
#घोषणा	bPSDReport		0xffff

/* 3. Page9(0x900) */
#घोषणा	bOFDMTxSC		0x30000000	/* Useless */
#घोषणा	bCCKTxOn		0x1
#घोषणा	bOFDMTxOn		0x2
#घोषणा	bDebugPage		0xfff  /* reset debug page and HWord, LWord */
#घोषणा	bDebugItem		0xff   /* reset debug page and LWord */
#घोषणा	bAntL			0x10
#घोषणा	bAntNonHT		0x100
#घोषणा	bAntHT1			0x1000
#घोषणा	bAntHT2			0x10000
#घोषणा	bAntHT1S1		0x100000
#घोषणा	bAntNonHTS1		0x1000000

/* 4. PageA(0xA00) */
#घोषणा	bCCKBBMode		0x3	/* Useless */
#घोषणा	bCCKTxPowerSaving	0x80
#घोषणा	bCCKRxPowerSaving	0x40

#घोषणा	bCCKSideBand		0x10	/* Reg 0xa00 rCCK0_System 20/40 चयन*/
#घोषणा	bCCKScramble		0x8	/* Useless */
#घोषणा	bCCKAntDiversity	0x8000
#घोषणा	bCCKCarrierRecovery	0x4000
#घोषणा	bCCKTxRate		0x3000
#घोषणा	bCCKDCCancel		0x0800
#घोषणा	bCCKISICancel		0x0400
#घोषणा	bCCKMatchFilter		0x0200
#घोषणा	bCCKEqualizer		0x0100
#घोषणा	bCCKPreambleDetect	0x800000
#घोषणा	bCCKFastFalseCCA	0x400000
#घोषणा	bCCKChEstStart		0x300000
#घोषणा	bCCKCCACount		0x080000
#घोषणा	bCCKcs_lim		0x070000
#घोषणा	bCCKBistMode		0x80000000
#घोषणा	bCCKCCAMask		0x40000000
#घोषणा	bCCKTxDACPhase		0x4
#घोषणा	bCCKRxADCPhase		0x20000000   /* r_rx_clk */
#घोषणा	bCCKr_cp_mode0		0x0100
#घोषणा	bCCKTxDCOffset		0xf0
#घोषणा	bCCKRxDCOffset		0xf
#घोषणा	bCCKCCAMode		0xc000
#घोषणा	bCCKFalseCS_lim		0x3f00
#घोषणा	bCCKCS_ratio		0xc00000
#घोषणा	bCCKCorgBit_sel		0x300000
#घोषणा	bCCKPD_lim		0x0f0000
#घोषणा	bCCKNewCCA		0x80000000
#घोषणा	bCCKRxHPofIG		0x8000
#घोषणा	bCCKRxIG		0x7f00
#घोषणा	bCCKLNAPolarity		0x800000
#घोषणा	bCCKRx1stGain		0x7f0000
#घोषणा	bCCKRFExtend		0x20000000 /* CCK Rx initial gain polarity */
#घोषणा	bCCKRxAGCSatLevel	0x1f000000
#घोषणा	bCCKRxAGCSatCount       0xe0
#घोषणा	bCCKRxRFSettle          0x1f       /* AGCsamp_dly */
#घोषणा	bCCKFixedRxAGC          0x8000
#घोषणा	bCCKAntennaPolarity     0x2000
#घोषणा	bCCKTxFilterType        0x0c00
#घोषणा	bCCKRxAGCReportType	0x0300
#घोषणा	bCCKRxDAGCEn            0x80000000
#घोषणा	bCCKRxDAGCPeriod        0x20000000
#घोषणा	bCCKRxDAGCSatLevel	0x1f000000
#घोषणा	bCCKTimingRecovery      0x800000
#घोषणा	bCCKTxC0                0x3f0000
#घोषणा	bCCKTxC1                0x3f000000
#घोषणा	bCCKTxC2                0x3f
#घोषणा	bCCKTxC3                0x3f00
#घोषणा	bCCKTxC4                0x3f0000
#घोषणा	bCCKTxC5		0x3f000000
#घोषणा	bCCKTxC6		0x3f
#घोषणा	bCCKTxC7		0x3f00
#घोषणा	bCCKDebugPort		0xff0000
#घोषणा	bCCKDACDebug		0x0f000000
#घोषणा	bCCKFalseAlarmEnable	0x8000
#घोषणा	bCCKFalseAlarmRead	0x4000
#घोषणा	bCCKTRSSI		0x7f
#घोषणा	bCCKRxAGCReport		0xfe
#घोषणा	bCCKRxReport_AntSel	0x80000000
#घोषणा	bCCKRxReport_MFOff	0x40000000
#घोषणा	bCCKRxRxReport_SQLoss	0x20000000
#घोषणा	bCCKRxReport_Pktloss	0x10000000
#घोषणा	bCCKRxReport_Lockedbit	0x08000000
#घोषणा	bCCKRxReport_RateError	0x04000000
#घोषणा	bCCKRxReport_RxRate	0x03000000
#घोषणा	bCCKRxFACounterLower	0xff
#घोषणा	bCCKRxFACounterUpper	0xff000000
#घोषणा	bCCKRxHPAGCStart	0xe000
#घोषणा	bCCKRxHPAGCFinal	0x1c00
#घोषणा	bCCKRxFalseAlarmEnable	0x8000
#घोषणा	bCCKFACounterFreeze	0x4000
#घोषणा	bCCKTxPathSel		0x10000000
#घोषणा	bCCKDefaultRxPath	0xc000000
#घोषणा	bCCKOptionRxPath	0x3000000

/* 5. PageC(0xC00) */
#घोषणा	bNumOfSTF		0x3	/* Useless */
#घोषणा	bShअगरt_L                0xc0
#घोषणा	bGI_TH			0xc
#घोषणा	bRxPathA		0x1
#घोषणा	bRxPathB		0x2
#घोषणा	bRxPathC		0x4
#घोषणा	bRxPathD		0x8
#घोषणा	bTxPathA		0x1
#घोषणा	bTxPathB		0x2
#घोषणा	bTxPathC		0x4
#घोषणा	bTxPathD		0x8
#घोषणा	bTRSSIFreq		0x200
#घोषणा	bADCBackoff		0x3000
#घोषणा	bDFIRBackoff		0xc000
#घोषणा	bTRSSILatchPhase	0x10000
#घोषणा	bRxIDCOffset		0xff
#घोषणा	bRxQDCOffset		0xff00
#घोषणा	bRxDFIRMode		0x1800000
#घोषणा	bRxDCNFType		0xe000000
#घोषणा	bRXIQImb_A		0x3ff
#घोषणा	bRXIQImb_B		0xfc00
#घोषणा	bRXIQImb_C		0x3f0000
#घोषणा	bRXIQImb_D		0xffc00000
#घोषणा	bDC_dc_Notch		0x60000
#घोषणा	bRxNBINotch		0x1f000000
#घोषणा	bPD_TH			0xf
#घोषणा	bPD_TH_Opt2		0xc000
#घोषणा	bPWED_TH		0x700
#घोषणा	bIfMF_Win_L		0x800
#घोषणा	bPD_Option		0x1000
#घोषणा	bMF_Win_L		0xe000
#घोषणा	bBW_Search_L		0x30000
#घोषणा	bwin_enh_L		0xc0000
#घोषणा	bBW_TH			0x700000
#घोषणा	bED_TH2			0x3800000
#घोषणा	bBW_option		0x4000000
#घोषणा	bRatio_TH		0x18000000
#घोषणा	bWinकरोw_L		0xe0000000
#घोषणा	bSBD_Option		0x1
#घोषणा	bFrame_TH		0x1c
#घोषणा	bFS_Option		0x60
#घोषणा	bDC_Slope_check		0x80
#घोषणा	bFGuard_Counter_DC_L	0xe00
#घोषणा	bFrame_Weight_Short	0x7000
#घोषणा	bSub_Tune		0xe00000
#घोषणा	bFrame_DC_Length	0xe000000
#घोषणा	bSBD_start_offset	0x30000000
#घोषणा	bFrame_TH_2		0x7
#घोषणा	bFrame_GI2_TH		0x38
#घोषणा	bGI2_Sync_en		0x40
#घोषणा	bSarch_Short_Early	0x300
#घोषणा	bSarch_Short_Late	0xc00
#घोषणा	bSarch_GI2_Late		0x70000
#घोषणा	bCFOAntSum		0x1
#घोषणा	bCFOAcc			0x2
#घोषणा	bCFOStartOffset		0xc
#घोषणा	bCFOLookBack		0x70
#घोषणा	bCFOSumWeight		0x80
#घोषणा	bDAGCEnable		0x10000
#घोषणा	bTXIQImb_A		0x3ff
#घोषणा	bTXIQImb_B		0xfc00
#घोषणा	bTXIQImb_C		0x3f0000
#घोषणा	bTXIQImb_D		0xffc00000
#घोषणा	bTxIDCOffset		0xff
#घोषणा	bTxQDCOffset		0xff00
#घोषणा	bTxDFIRMode		0x10000
#घोषणा	bTxPesuकरोNoiseOn	0x4000000
#घोषणा	bTxPesuकरोNoise_A	0xff
#घोषणा	bTxPesuकरोNoise_B	0xff00
#घोषणा	bTxPesuकरोNoise_C	0xff0000
#घोषणा	bTxPesuकरोNoise_D	0xff000000
#घोषणा	bCCADropOption		0x20000
#घोषणा	bCCADropThres		0xfff00000
#घोषणा	bEDCCA_H		0xf
#घोषणा	bEDCCA_L		0xf0
#घोषणा	bLambda_ED              0x300
#घोषणा	bRxInitialGain          0x7f
#घोषणा	bRxAntDivEn             0x80
#घोषणा	bRxAGCAddressForLNA     0x7f00
#घोषणा	bRxHighPowerFlow        0x8000
#घोषणा	bRxAGCFreezeThres       0xc0000
#घोषणा	bRxFreezeStep_AGC1      0x300000
#घोषणा	bRxFreezeStep_AGC2      0xc00000
#घोषणा	bRxFreezeStep_AGC3      0x3000000
#घोषणा	bRxFreezeStep_AGC0      0xc000000
#घोषणा	bRxRssi_Cmp_En          0x10000000
#घोषणा	bRxQuickAGCEn           0x20000000
#घोषणा	bRxAGCFreezeThresMode   0x40000000
#घोषणा	bRxOverFlowCheckType    0x80000000
#घोषणा	bRxAGCShअगरt             0x7f
#घोषणा	bTRSW_Tri_Only          0x80
#घोषणा	bPowerThres             0x300
#घोषणा	bRxAGCEn                0x1
#घोषणा	bRxAGCTogetherEn        0x2
#घोषणा	bRxAGCMin               0x4
#घोषणा	bRxHP_Ini               0x7
#घोषणा	bRxHP_TRLNA             0x70
#घोषणा	bRxHP_RSSI              0x700
#घोषणा	bRxHP_BBP1              0x7000
#घोषणा	bRxHP_BBP2              0x70000
#घोषणा	bRxHP_BBP3              0x700000
#घोषणा	bRSSI_H                 0x7f0000     /* the threshold क्रम high घातer */
#घोषणा	bRSSI_Gen               0x7f000000   /* the threshold क्रम ant भागers */
#घोषणा	bRxSettle_TRSW          0x7
#घोषणा	bRxSettle_LNA           0x38
#घोषणा	bRxSettle_RSSI          0x1c0
#घोषणा	bRxSettle_BBP           0xe00
#घोषणा	bRxSettle_RxHP          0x7000
#घोषणा	bRxSettle_AntSW_RSSI    0x38000
#घोषणा	bRxSettle_AntSW         0xc0000
#घोषणा	bRxProcessTime_DAGC     0x300000
#घोषणा	bRxSettle_HSSI          0x400000
#घोषणा	bRxProcessTime_BBPPW    0x800000
#घोषणा	bRxAntennaPowerShअगरt    0x3000000
#घोषणा	bRSSITableSelect        0xc000000
#घोषणा	bRxHP_Final             0x7000000
#घोषणा	bRxHTSettle_BBP         0x7
#घोषणा	bRxHTSettle_HSSI        0x8
#घोषणा	bRxHTSettle_RxHP        0x70
#घोषणा	bRxHTSettle_BBPPW       0x80
#घोषणा	bRxHTSettle_Idle        0x300
#घोषणा	bRxHTSettle_Reserved    0x1c00
#घोषणा	bRxHTRxHPEn             0x8000
#घोषणा	bRxHTAGCFreezeThres     0x30000
#घोषणा	bRxHTAGCTogetherEn      0x40000
#घोषणा	bRxHTAGCMin             0x80000
#घोषणा	bRxHTAGCEn              0x100000
#घोषणा	bRxHTDAGCEn             0x200000
#घोषणा	bRxHTRxHP_BBP           0x1c00000
#घोषणा	bRxHTRxHP_Final         0xe0000000
#घोषणा	bRxPWRatioTH            0x3
#घोषणा	bRxPWRatioEn            0x4
#घोषणा	bRxMFHold               0x3800
#घोषणा	bRxPD_Delay_TH1         0x38
#घोषणा	bRxPD_Delay_TH2         0x1c0
#घोषणा	bRxPD_DC_COUNT_MAX      0x600
#घोषणा	bRxPD_Delay_TH          0x8000
#घोषणा	bRxProcess_Delay        0xf0000
#घोषणा	bRxSearchrange_GI2_Early 0x700000
#घोषणा	bRxFrame_Guard_Counter_L 0x3800000
#घोषणा	bRxSGI_Guard_L          0xc000000
#घोषणा	bRxSGI_Search_L         0x30000000
#घोषणा	bRxSGI_TH               0xc0000000
#घोषणा	bDFSCnt0                0xff
#घोषणा	bDFSCnt1                0xff00
#घोषणा	bDFSFlag                0xf0000
#घोषणा	bMFWeightSum            0x300000
#घोषणा	bMinIdxTH               0x7f000000
#घोषणा	bDAFormat               0x40000
#घोषणा	bTxChEmuEnable          0x01000000
#घोषणा	bTRSWIsolation_A        0x7f
#घोषणा	bTRSWIsolation_B        0x7f00
#घोषणा	bTRSWIsolation_C        0x7f0000
#घोषणा	bTRSWIsolation_D        0x7f000000
#घोषणा	bExtLNAGain             0x7c00

/* 6. PageE(0xE00) */
#घोषणा	bSTBCEn                 0x4	/* Useless */
#घोषणा	bAntennaMapping         0x10
#घोषणा	bNss                    0x20
#घोषणा	bCFOAntSumD             0x200
#घोषणा	bPHYCounterReset        0x8000000
#घोषणा	bCFOReportGet           0x4000000
#घोषणा	bOFDMContinueTx         0x10000000
#घोषणा	bOFDMSingleCarrier      0x20000000
#घोषणा	bOFDMSingleTone         0x40000000
#घोषणा	bHTDetect               0x100
#घोषणा	bCFOEn                  0x10000
#घोषणा	bCFOValue               0xfff00000
#घोषणा	bSigTone_Re             0x3f
#घोषणा	bSigTone_Im             0x7f00
#घोषणा	bCounter_CCA            0xffff
#घोषणा	bCounter_ParityFail     0xffff0000
#घोषणा	bCounter_RateIllegal    0xffff
#घोषणा	bCounter_CRC8Fail       0xffff0000
#घोषणा	bCounter_MCSNoSupport   0xffff
#घोषणा	bCounter_FastSync       0xffff
#घोषणा	bShortCFO               0xfff
#घोषणा	bShortCFOTLength        12   /* total */
#घोषणा	bShortCFOFLength        11   /* fraction */
#घोषणा	bLongCFO                0x7ff
#घोषणा	bLongCFOTLength         11
#घोषणा	bLongCFOFLength         11
#घोषणा	bTailCFO                0x1fff
#घोषणा	bTailCFOTLength         13
#घोषणा	bTailCFOFLength         12
#घोषणा	bmax_en_pwdB            0xffff
#घोषणा	bCC_घातer_dB            0xffff0000
#घोषणा	bnoise_pwdB             0xffff
#घोषणा	bPowerMeasTLength       10
#घोषणा	bPowerMeasFLength       3
#घोषणा	bRx_HT_BW               0x1
#घोषणा	bRxSC                   0x6
#घोषणा	bRx_HT                  0x8
#घोषणा	bNB_पूर्णांकf_det_on         0x1
#घोषणा	bIntf_win_len_cfg       0x30
#घोषणा	bNB_Intf_TH_cfg         0x1c0
#घोषणा	bRFGain                 0x3f
#घोषणा	bTableSel               0x40
#घोषणा	bTRSW                   0x80
#घोषणा	bRxSNR_A                0xff
#घोषणा	bRxSNR_B                0xff00
#घोषणा	bRxSNR_C                0xff0000
#घोषणा	bRxSNR_D                0xff000000
#घोषणा	bSNREVMTLength          8
#घोषणा	bSNREVMFLength          1
#घोषणा	bCSI1st                 0xff
#घोषणा	bCSI2nd                 0xff00
#घोषणा	bRxEVM1st               0xff0000
#घोषणा	bRxEVM2nd               0xff000000
#घोषणा	bSIGEVM                 0xff
#घोषणा	bPWDB                   0xff00
#घोषणा	bSGIEN                  0x10000

#घोषणा	bSFactorQAM1            0xf	/* Useless */
#घोषणा	bSFactorQAM2            0xf0
#घोषणा	bSFactorQAM3            0xf00
#घोषणा	bSFactorQAM4            0xf000
#घोषणा	bSFactorQAM5            0xf0000
#घोषणा	bSFactorQAM6            0xf0000
#घोषणा	bSFactorQAM7            0xf00000
#घोषणा	bSFactorQAM8            0xf000000
#घोषणा	bSFactorQAM9            0xf0000000
#घोषणा	bCSIScheme              0x100000

#घोषणा	bNoiseLvlTopSet         0x3	/* Useless */
#घोषणा	bChSmooth               0x4
#घोषणा	bChSmoothCfg1           0x38
#घोषणा	bChSmoothCfg2           0x1c0
#घोषणा	bChSmoothCfg3           0xe00
#घोषणा	bChSmoothCfg4           0x7000
#घोषणा	bMRCMode                0x800000
#घोषणा	bTHEVMCfg               0x7000000

#घोषणा	bLoopFitType            0x1	/* Useless */
#घोषणा	bUpdCFO                 0x40
#घोषणा	bUpdCFOOffData          0x80
#घोषणा	bAdvUpdCFO              0x100
#घोषणा	bAdvTimeCtrl            0x800
#घोषणा	bUpdClko                0x1000
#घोषणा	bFC                     0x6000
#घोषणा	bTrackingMode           0x8000
#घोषणा	bPhCmpEnable            0x10000
#घोषणा	bUpdClkoLTF             0x20000
#घोषणा	bComChCFO               0x40000
#घोषणा	bCSIEstiMode            0x80000
#घोषणा	bAdvUpdEqz              0x100000
#घोषणा	bUChCfg                 0x7000000
#घोषणा	bUpdEqz			0x8000000

#घोषणा	bTxAGCRate18_06		0x7f7f7f7f	/* Useless */
#घोषणा	bTxAGCRate54_24		0x7f7f7f7f
#घोषणा	bTxAGCRateMCS32		0x7f
#घोषणा	bTxAGCRateCCK		0x7f00
#घोषणा	bTxAGCRateMCS3_MCS0	0x7f7f7f7f
#घोषणा	bTxAGCRateMCS7_MCS4	0x7f7f7f7f
#घोषणा	bTxAGCRateMCS11_MCS8	0x7f7f7f7f
#घोषणा	bTxAGCRateMCS15_MCS12	0x7f7f7f7f

/* Rx Pseduo noise */
#घोषणा	bRxPesuकरोNoiseOn         0x20000000	/* Useless */
#घोषणा	bRxPesuकरोNoise_A         0xff
#घोषणा	bRxPesuकरोNoise_B         0xff00
#घोषणा	bRxPesuकरोNoise_C         0xff0000
#घोषणा	bRxPesuकरोNoise_D         0xff000000
#घोषणा	bPesuकरोNoiseState_A      0xffff
#घोषणा	bPesuकरोNoiseState_B      0xffff0000
#घोषणा	bPesuकरोNoiseState_C      0xffff
#घोषणा	bPesuकरोNoiseState_D      0xffff0000

/* 7. RF Register
 * Zebra1
 */
#घोषणा	bZebra1_HSSIEnable        0x8		/* Useless */
#घोषणा	bZebra1_TRxControl        0xc00
#घोषणा	bZebra1_TRxGainSetting    0x07f
#घोषणा	bZebra1_RxCorner          0xc00
#घोषणा	bZebra1_TxChargePump      0x38
#घोषणा	bZebra1_RxChargePump      0x7
#घोषणा	bZebra1_ChannelNum        0xf80
#घोषणा	bZebra1_TxLPFBW           0x400
#घोषणा	bZebra1_RxLPFBW           0x600

/*Zebra4 */
#घोषणा	bRTL8256RegModeCtrl1      0x100	/* Useless */
#घोषणा	bRTL8256RegModeCtrl0      0x40
#घोषणा	bRTL8256_TxLPFBW          0x18
#घोषणा	bRTL8256_RxLPFBW          0x600

/* RTL8258 */
#घोषणा	bRTL8258_TxLPFBW          0xc	/* Useless */
#घोषणा	bRTL8258_RxLPFBW          0xc00
#घोषणा	bRTL8258_RSSILPFBW        0xc0

/*
 * Other Definition
 */

/* byte endable क्रम sb_ग_लिखो */
#घोषणा	bByte0                    0x1	/* Useless */
#घोषणा	bByte1                    0x2
#घोषणा	bByte2                    0x4
#घोषणा	bByte3                    0x8
#घोषणा	bWord0                    0x3
#घोषणा	bWord1                    0xc
#घोषणा	bDWord                    0xf

/* क्रम PutRegsetting & GetRegSetting BitMask */
#घोषणा	bMaskByte0                0xff	/* Reg 0xc50 rOFDM0_XAAGCCore~0xC6f */
#घोषणा	bMaskByte1                0xff00
#घोषणा	bMaskByte2                0xff0000
#घोषणा	bMaskByte3                0xff000000
#घोषणा	bMaskHWord                0xffff0000
#घोषणा	bMaskLWord                0x0000ffff
#घोषणा	bMaskDWord                0xffffffff

/* क्रम PutRFRegsetting & GetRFRegSetting BitMask */
#घोषणा	bRFRegOffsetMask	0xfffff
#घोषणा	bEnable                   0x1	/* Useless */
#घोषणा	bDisable                  0x0

#घोषणा	LeftAntenna               0x0	/* Useless */
#घोषणा	RightAntenna              0x1

#घोषणा	tCheckTxStatus            500   /* 500ms Useless */
#घोषणा	tUpdateRxCounter          100   /* 100ms */

#घोषणा	rateCCK     0	/* Useless */
#घोषणा	rateOFDM    1
#घोषणा	rateHT      2

/* define Register-End */
#घोषणा	bPMAC_End       0x1ff	/* Useless */
#घोषणा	bFPGAPHY0_End   0x8ff
#घोषणा	bFPGAPHY1_End   0x9ff
#घोषणा	bCCKPHY0_End    0xaff
#घोषणा	bOFDMPHY0_End   0xcff
#घोषणा	bOFDMPHY1_End   0xdff

#घोषणा	bPMACControl	0x0	/* Useless */
#घोषणा	bWMACControl	0x1
#घोषणा	bWNICControl	0x2

#घोषणा	ANTENNA_A	0x1	/* Useless */
#घोषणा	ANTENNA_B	0x2
#घोषणा	ANTENNA_AB	0x3	/* ANTENNA_A |ANTENNA_B */

#घोषणा	ANTENNA_C	0x4
#घोषणा	ANTENNA_D	0x8


/* accept all physical address */
#घोषणा RCR_AAP		BIT(0)
#घोषणा RCR_APM		BIT(1)		/* accept physical match */
#घोषणा RCR_AM		BIT(2)		/* accept multicast */
#घोषणा RCR_AB		BIT(3)		/* accept broadcast */
#घोषणा RCR_ACRC32	BIT(5)		/* accept error packet */
#घोषणा RCR_9356SEL	BIT(6)
#घोषणा RCR_AICV	BIT(12)		/* Accept ICV error packet */
#घोषणा RCR_RXFTH0	(BIT(13)|BIT(14)|BIT(15))	/* Rx FIFO threshold */
#घोषणा RCR_ADF		BIT(18)		/* Accept Data(frame type) frame */
#घोषणा RCR_ACF		BIT(19)		/* Accept control frame */
#घोषणा RCR_AMF		BIT(20)		/* Accept management frame */
#घोषणा RCR_ADD3	BIT(21)
#घोषणा RCR_APWRMGT	BIT(22)		/* Accept घातer management packet */
#घोषणा RCR_CBSSID	BIT(23)		/* Accept BSSID match packet */
#घोषणा RCR_ENMARP	BIT(28)		/* enable mac स्वतः reset phy */
#घोषणा RCR_EnCS1	BIT(29)		/* enable carrier sense method 1 */
#घोषणा RCR_EnCS2	BIT(30)		/* enable carrier sense method 2 */
/* Rx Early mode is perक्रमmed क्रम packet size greater than 1536 */
#घोषणा RCR_OnlyErlPkt	BIT(31)

/*--------------------------Define Parameters-------------------------------*/


#पूर्ण_अगर	/*__INC_HAL8192SPHYREG_H */

