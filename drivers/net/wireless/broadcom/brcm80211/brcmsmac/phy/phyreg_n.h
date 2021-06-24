<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#घोषणा NPHY_TBL_ID_GAIN1		0
#घोषणा NPHY_TBL_ID_GAIN2		1
#घोषणा NPHY_TBL_ID_GAINBITS1		2
#घोषणा NPHY_TBL_ID_GAINBITS2		3
#घोषणा NPHY_TBL_ID_GAINLIMIT		4
#घोषणा NPHY_TBL_ID_WRSSIGainLimit	5
#घोषणा NPHY_TBL_ID_RFSEQ		7
#घोषणा NPHY_TBL_ID_AFECTRL		8
#घोषणा NPHY_TBL_ID_ANTSWCTRLLUT	9
#घोषणा NPHY_TBL_ID_IQLOCAL		15
#घोषणा NPHY_TBL_ID_NOISEVAR		16
#घोषणा NPHY_TBL_ID_SAMPLEPLAY		17
#घोषणा NPHY_TBL_ID_CORE1TXPWRCTL	26
#घोषणा NPHY_TBL_ID_CORE2TXPWRCTL	27
#घोषणा NPHY_TBL_ID_CMPMETRICDATAWEIGHTTBL	30

#घोषणा NPHY_TBL_ID_EPSILONTBL0   31
#घोषणा NPHY_TBL_ID_SCALARTBL0    32
#घोषणा NPHY_TBL_ID_EPSILONTBL1   33
#घोषणा NPHY_TBL_ID_SCALARTBL1    34

#घोषणा	NPHY_TO_BPHY_OFF	0xc00

#घोषणा NPHY_BandControl_currentBand			0x0001
#घोषणा RFCC_CHIP0_PU			0x0400
#घोषणा RFCC_POR_FORCE			0x0040
#घोषणा RFCC_OE_POR_FORCE		0x0080
#घोषणा NPHY_RfctrlIntc_override_OFF			0
#घोषणा NPHY_RfctrlIntc_override_TRSW			1
#घोषणा NPHY_RfctrlIntc_override_PA				2
#घोषणा NPHY_RfctrlIntc_override_EXT_LNA_PU		3
#घोषणा NPHY_RfctrlIntc_override_EXT_LNA_GAIN	4
#घोषणा RIFS_ENABLE			0x80
#घोषणा BPHY_BAND_SEL_UP20		0x10
#घोषणा NPHY_MLenable			0x02

#घोषणा NPHY_RfseqMode_CoreActv_override 0x0001
#घोषणा NPHY_RfseqMode_Trigger_override	0x0002
#घोषणा NPHY_RfseqCoreActv_TxRxChain0	(0x11)
#घोषणा NPHY_RfseqCoreActv_TxRxChain1	(0x22)

#घोषणा NPHY_RfseqTrigger_rx2tx		0x0001
#घोषणा NPHY_RfseqTrigger_tx2rx		0x0002
#घोषणा NPHY_RfseqTrigger_updategainh	0x0004
#घोषणा NPHY_RfseqTrigger_updategainl	0x0008
#घोषणा NPHY_RfseqTrigger_updategainu	0x0010
#घोषणा NPHY_RfseqTrigger_reset2rx	0x0020
#घोषणा NPHY_RfseqStatus_rx2tx		0x0001
#घोषणा NPHY_RfseqStatus_tx2rx		0x0002
#घोषणा NPHY_RfseqStatus_updategainh	0x0004
#घोषणा NPHY_RfseqStatus_updategainl	0x0008
#घोषणा NPHY_RfseqStatus_updategainu	0x0010
#घोषणा NPHY_RfseqStatus_reset2rx	0x0020
#घोषणा NPHY_ClassअगरierCtrl_cck_en	0x1
#घोषणा NPHY_ClassअगरierCtrl_ofdm_en	0x2
#घोषणा NPHY_ClassअगरierCtrl_रुकोed_en	0x4
#घोषणा NPHY_IQFlip_ADC1		0x0001
#घोषणा NPHY_IQFlip_ADC2		0x0010
#घोषणा NPHY_sampleCmd_STOP		0x0002

#घोषणा RX_GF_OR_MM			0x0004
#घोषणा RX_GF_MM_AUTO			0x0100

#घोषणा NPHY_iqloCalCmdGctl_IQLO_CAL_EN	0x8000

#घोषणा NPHY_IqestCmd_iqstart		0x1
#घोषणा NPHY_IqestCmd_iqMode		0x2

#घोषणा NPHY_TxPwrCtrlCmd_pwrIndex_init		0x40
#घोषणा NPHY_TxPwrCtrlCmd_pwrIndex_init_rev7	0x19

#घोषणा PRIM_SEL_UP20		0x8000

#घोषणा NPHY_RFSEQ_RX2TX		0x0
#घोषणा NPHY_RFSEQ_TX2RX		0x1
#घोषणा NPHY_RFSEQ_RESET2RX		0x2
#घोषणा NPHY_RFSEQ_UPDATEGAINH		0x3
#घोषणा NPHY_RFSEQ_UPDATEGAINL		0x4
#घोषणा NPHY_RFSEQ_UPDATEGAINU		0x5

#घोषणा NPHY_RFSEQ_CMD_NOP		0x0
#घोषणा NPHY_RFSEQ_CMD_RXG_FBW		0x1
#घोषणा NPHY_RFSEQ_CMD_TR_SWITCH	0x2
#घोषणा NPHY_RFSEQ_CMD_EXT_PA		0x3
#घोषणा NPHY_RFSEQ_CMD_RXPD_TXPD	0x4
#घोषणा NPHY_RFSEQ_CMD_TX_GAIN		0x5
#घोषणा NPHY_RFSEQ_CMD_RX_GAIN		0x6
#घोषणा NPHY_RFSEQ_CMD_SET_HPF_BW	0x7
#घोषणा NPHY_RFSEQ_CMD_CLR_HIQ_DIS	0x8
#घोषणा NPHY_RFSEQ_CMD_END		0xf

#घोषणा NPHY_REV3_RFSEQ_CMD_NOP		0x0
#घोषणा NPHY_REV3_RFSEQ_CMD_RXG_FBW	0x1
#घोषणा NPHY_REV3_RFSEQ_CMD_TR_SWITCH	0x2
#घोषणा NPHY_REV3_RFSEQ_CMD_INT_PA_PU	0x3
#घोषणा NPHY_REV3_RFSEQ_CMD_EXT_PA	0x4
#घोषणा NPHY_REV3_RFSEQ_CMD_RXPD_TXPD	0x5
#घोषणा NPHY_REV3_RFSEQ_CMD_TX_GAIN	0x6
#घोषणा NPHY_REV3_RFSEQ_CMD_RX_GAIN	0x7
#घोषणा NPHY_REV3_RFSEQ_CMD_CLR_HIQ_DIS	0x8
#घोषणा NPHY_REV3_RFSEQ_CMD_SET_HPF_H_HPC	0x9
#घोषणा NPHY_REV3_RFSEQ_CMD_SET_LPF_H_HPC	0xa
#घोषणा NPHY_REV3_RFSEQ_CMD_SET_HPF_M_HPC	0xb
#घोषणा NPHY_REV3_RFSEQ_CMD_SET_LPF_M_HPC	0xc
#घोषणा NPHY_REV3_RFSEQ_CMD_SET_HPF_L_HPC	0xd
#घोषणा NPHY_REV3_RFSEQ_CMD_SET_LPF_L_HPC	0xe
#घोषणा NPHY_REV3_RFSEQ_CMD_CLR_RXRX_BIAS	0xf
#घोषणा NPHY_REV3_RFSEQ_CMD_END		0x1f

#घोषणा NPHY_RSSI_SEL_W1		0x0
#घोषणा NPHY_RSSI_SEL_W2		0x1
#घोषणा NPHY_RSSI_SEL_NB		0x2
#घोषणा NPHY_RSSI_SEL_IQ		0x3
#घोषणा NPHY_RSSI_SEL_TSSI_2G		0x4
#घोषणा NPHY_RSSI_SEL_TSSI_5G		0x5
#घोषणा NPHY_RSSI_SEL_TBD		0x6

#घोषणा NPHY_RAIL_I			0x0
#घोषणा NPHY_RAIL_Q			0x1

#घोषणा NPHY_FORCESIG_DECODEGATEDCLKS	0x8

#घोषणा NPHY_REV7_RfctrlOverride_cmd_rxrf_pu 0x0
#घोषणा NPHY_REV7_RfctrlOverride_cmd_rx_pu   0x1
#घोषणा NPHY_REV7_RfctrlOverride_cmd_tx_pu   0x2
#घोषणा NPHY_REV7_RfctrlOverride_cmd_rxgain  0x3
#घोषणा NPHY_REV7_RfctrlOverride_cmd_txgain  0x4

#घोषणा NPHY_REV7_RXGAINCODE_RFMXGAIN_MASK 0x000ff
#घोषणा NPHY_REV7_RXGAINCODE_LPFGAIN_MASK  0x0ff00
#घोषणा NPHY_REV7_RXGAINCODE_DVGAGAIN_MASK 0xf0000

#घोषणा NPHY_REV7_TXGAINCODE_TGAIN_MASK     0x7fff
#घोषणा NPHY_REV7_TXGAINCODE_LPFGAIN_MASK   0x8000
#घोषणा NPHY_REV7_TXGAINCODE_BIQ0GAIN_SHIFT 14

#घोषणा NPHY_REV7_RFCTRLOVERRIDE_ID0 0x0
#घोषणा NPHY_REV7_RFCTRLOVERRIDE_ID1 0x1
#घोषणा NPHY_REV7_RFCTRLOVERRIDE_ID2 0x2

#घोषणा NPHY_IqestIqAccLo(core)  ((core == 0) ? 0x12c : 0x134)

#घोषणा NPHY_IqestIqAccHi(core)  ((core == 0) ? 0x12d : 0x135)

#घोषणा NPHY_IqestipwrAccLo(core)  ((core == 0) ? 0x12e : 0x136)

#घोषणा NPHY_IqestipwrAccHi(core)  ((core == 0) ? 0x12f : 0x137)

#घोषणा NPHY_IqestqpwrAccLo(core)  ((core == 0) ? 0x130 : 0x138)

#घोषणा NPHY_IqestqpwrAccHi(core)  ((core == 0) ? 0x131 : 0x139)
