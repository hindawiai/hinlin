<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __INC_HAL8188EPHYREG_H__
#घोषणा __INC_HAL8188EPHYREG_H__
/*--------------------------Define Parameters-------------------------------*/
/*  */
/*  BB-PHY रेजिस्टर PMAC 0x100 PHY 0x800 - 0xEFF */
/*  1. PMAC duplicate रेजिस्टर due to connection: RF_Mode, TRxRN, NumOf L-STF */
/*  2. 0x800/0x900/0xA00/0xC00/0xD00/0xE00 */
/*  3. RF रेजिस्टर 0x00-2E */
/*  4. Bit Mask क्रम BB/RF रेजिस्टर */
/*  5. Other definition क्रम BB/RF R/W */
/*  */

/*  3. Page8(0x800) */
#घोषणा	rFPGA0_RFMOD		0x800	/* RF mode & CCK TxSC RF BW Setting */
#घोषणा	rFPGA0_TxGainStage	0x80c	/*  Set TX PWR init gain? */

#घोषणा	rFPGA0_XA_HSSIParameter1	0x820	/*  RF 3 wire रेजिस्टर */
#घोषणा	rFPGA0_XA_HSSIParameter2	0x824
#घोषणा	rFPGA0_XB_HSSIParameter1	0x828
#घोषणा	rFPGA0_XB_HSSIParameter2	0x82c

#घोषणा	rFPGA0_XA_LSSIParameter		0x840
#घोषणा	rFPGA0_XB_LSSIParameter		0x844

#घोषणा	rFPGA0_XAB_SwitchControl	0x858	/*  RF Channel चयन */
#घोषणा	rFPGA0_XCD_SwitchControl	0x85c

#घोषणा	rFPGA0_XA_RFInterfaceOE		0x860	/*  RF Channel चयन */
#घोषणा	rFPGA0_XB_RFInterfaceOE		0x864

#घोषणा	rFPGA0_XAB_RFInterfaceSW	0x870	/*  RF Iface Software Control */
#घोषणा	rFPGA0_XCD_RFInterfaceSW	0x874

#घोषणा	rFPGA0_XAB_RFParameter		0x878	/*  RF Parameter */

#घोषणा	rFPGA0_XA_LSSIReadBack		0x8a0	/*  Tranceiver LSSI Readback */
#घोषणा	rFPGA0_XB_LSSIReadBack		0x8a4

#घोषणा	TransceiverA_HSPI_Readback	0x8b8
#घोषणा	TransceiverB_HSPI_Readback	0x8bc
#घोषणा	rFPGA0_XAB_RFInterfaceRB	0x8e0

/*  4. Page9(0x900) */
/* RF mode & OFDM TxSC RF BW Setting?? */
#घोषणा	rFPGA1_RFMOD			0x900

/*  5. PageA(0xA00) */
/*  Set Control channel to upper or lower - required only क्रम 40MHz */
#घोषणा	rCCK0_System			0xa00

/*  */
/*  PageB(0xB00) */
/*  */
#घोषणा	rConfig_AntA			0xb68
#घोषणा	rConfig_AntB			0xb6c

/*  */
/*  6. PageC(0xC00) */
/*  */
#घोषणा	rOFDM0_TRxPathEnable		0xc04
#घोषणा	rOFDM0_TRMuxPar			0xc08

/* RxIQ DC offset, Rx digital filter, DC notch filter */
#घोषणा	rOFDM0_XARxAFE			0xc10
#घोषणा	rOFDM0_XARxIQImbalance		0xc14  /* RxIQ imbalance matrix */
#घोषणा	rOFDM0_XBRxAFE			0xc18
#घोषणा	rOFDM0_XBRxIQImbalance		0xc1c

#घोषणा	rOFDM0_RxDSP			0xc40  /* Rx Sync Path */
#घोषणा	rOFDM0_ECCAThreshold		0xc4c /*  energy CCA */

#घोषणा	rOFDM0_XAAGCCore1		0xc50	/*  DIG */
#घोषणा	rOFDM0_XAAGCCore2		0xc54
#घोषणा	rOFDM0_XBAGCCore1		0xc58
#घोषणा	rOFDM0_XBAGCCore2		0xc5c

#घोषणा	rOFDM0_AGCRSSITable		0xc78

#घोषणा	rOFDM0_XATxIQImbalance		0xc80	/*  TX PWR TRACK and DIG */
#घोषणा	rOFDM0_XATxAFE			0xc84
#घोषणा	rOFDM0_XBTxIQImbalance		0xc88
#घोषणा	rOFDM0_XBTxAFE			0xc8c
#घोषणा	rOFDM0_XCTxAFE			0xc94
#घोषणा	rOFDM0_XDTxAFE			0xc9c

#घोषणा	rOFDM0_RxIQExtAnta		0xca0

/*  */
/*  7. PageD(0xD00) */
/*  */
#घोषणा	rOFDM1_LSTF			0xd00

/*  */
/*  8. PageE(0xE00) */
/*  */
#घोषणा	rTxAGC_A_Rate18_06		0xe00
#घोषणा	rTxAGC_A_Rate54_24		0xe04
#घोषणा	rTxAGC_A_CCK1_Mcs32		0xe08
#घोषणा	rTxAGC_A_Mcs03_Mcs00		0xe10
#घोषणा	rTxAGC_A_Mcs07_Mcs04		0xe14
#घोषणा	rTxAGC_A_Mcs11_Mcs08		0xe18
#घोषणा	rTxAGC_A_Mcs15_Mcs12		0xe1c

#घोषणा	rTxAGC_B_Rate18_06		0x830
#घोषणा	rTxAGC_B_Rate54_24		0x834
#घोषणा	rTxAGC_B_CCK1_55_Mcs32		0x838
#घोषणा	rTxAGC_B_Mcs03_Mcs00		0x83c
#घोषणा	rTxAGC_B_Mcs07_Mcs04		0x848
#घोषणा	rTxAGC_B_Mcs11_Mcs08		0x84c
#घोषणा	rTxAGC_B_Mcs15_Mcs12		0x868
#घोषणा	rTxAGC_B_CCK11_A_CCK2_11	0x86c

#घोषणा	rFPGA0_IQK			0xe28
#घोषणा	rTx_IQK_Tone_A			0xe30
#घोषणा	rRx_IQK_Tone_A			0xe34
#घोषणा	rTx_IQK_PI_A			0xe38
#घोषणा	rRx_IQK_PI_A			0xe3c

#घोषणा	rTx_IQK				0xe40
#घोषणा	rRx_IQK				0xe44
#घोषणा	rIQK_AGC_Pts			0xe48
#घोषणा	rIQK_AGC_Rsp			0xe4c
#घोषणा	rIQK_AGC_Cont			0xe60

#घोषणा	rBlue_Tooth			0xe6c
#घोषणा	rRx_Wait_CCA			0xe70
#घोषणा	rTx_CCK_RFON			0xe74
#घोषणा	rTx_CCK_BBON			0xe78
#घोषणा	rTx_OFDM_RFON			0xe7c
#घोषणा	rTx_OFDM_BBON			0xe80
#घोषणा	rTx_To_Rx			0xe84
#घोषणा	rTx_To_Tx			0xe88
#घोषणा	rRx_CCK				0xe8c

#घोषणा	rTx_Power_Beक्रमe_IQK_A		0xe94
#घोषणा	rTx_Power_After_IQK_A		0xe9c

#घोषणा	rRx_Power_Beक्रमe_IQK_A_2	0xea4
#घोषणा	rRx_Power_After_IQK_A_2		0xeac

#घोषणा	rTx_Power_Beक्रमe_IQK_B		0xeb4
#घोषणा	rTx_Power_After_IQK_B		0xebc

#घोषणा	rRx_Power_Beक्रमe_IQK_B_2	0xec4
#घोषणा	rRx_Power_After_IQK_B_2		0xecc

#घोषणा	rRx_OFDM			0xed0
#घोषणा	rRx_Wait_RIFS			0xed4
#घोषणा	rRx_TO_Rx			0xed8
#घोषणा	rStandby			0xedc
#घोषणा	rSleep				0xee0
#घोषणा	rPMPD_ANAEN			0xeec

/*  */
/*  RL6052 Register definition */
/*  */
#घोषणा	RF_AC			0x00	/*  */
#घोषणा	RF_CHNLBW		0x18	/*  RF channel and BW चयन */
#घोषणा	RF_T_METER_88E		0x42	/*  */
#घोषणा	RF_RCK_OS		0x30	/*  RF TX PA control */
#घोषणा	RF_TXPA_G1		0x31	/*  RF TX PA control */
#घोषणा	RF_TXPA_G2		0x32	/*  RF TX PA control */
#घोषणा	RF_WE_LUT		0xEF

/*  */
/* Bit Mask */
/*  */

/*  2. Page8(0x800) */
#घोषणा	bRFMOD			0x1	/*  Reg 0x800 rFPGA0_RFMOD */
#घोषणा	bCCKEn			0x1000000
#घोषणा	bOFDMEn			0x2000000

#घोषणा	bLSSIReadAddress	0x7f800000   /*  T65 RF */
#घोषणा	bLSSIReadEdge		0x80000000   /* LSSI "Read" edge संकेत */
#घोषणा	bLSSIReadBackData	0xfffff		/*  T65 RF */

#घोषणा	bCCKSideBand		0x10	/*  Reg 0xa00 rCCK0_System 20/40 */

/*  */
/*  Other Definition */
/*  */

/* क्रम PutRegsetting & GetRegSetting BitMask */
#घोषणा	bMaskByte0		0xff	/*  Reg 0xc50 rOFDM0_XAAGCCore~0xC6f */
#घोषणा	bMaskByte1		0xff00
#घोषणा	bMaskByte3		0xff000000
#घोषणा	bMaskDWord		0xffffffff
#घोषणा	bMask12Bits		0xfff
#घोषणा	bMaskOFDM_D		0xffc00000

/* क्रम PutRFRegsetting & GetRFRegSetting BitMask */
#घोषणा	bRFRegOffsetMask	0xfffff

#पूर्ण_अगर
