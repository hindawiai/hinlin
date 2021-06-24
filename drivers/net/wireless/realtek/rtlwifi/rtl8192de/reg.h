<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92D_REG_H__
#घोषणा __RTL92D_REG_H__

/* ----------------------------------------------------- */
/* 0x0000h ~ 0x00FFh System Configuration */
/* ----------------------------------------------------- */
#घोषणा REG_SYS_ISO_CTRL		0x0000
#घोषणा REG_SYS_FUNC_EN			0x0002
#घोषणा REG_APS_FSMCO			0x0004
#घोषणा REG_SYS_CLKR			0x0008
#घोषणा REG_9346CR			0x000A
#घोषणा REG_EE_VPD			0x000C
#घोषणा REG_AFE_MISC			0x0010
#घोषणा REG_SPS0_CTRL			0x0011
#घोषणा REG_POWER_OFF_IN_PROCESS	0x0017
#घोषणा REG_SPS_OCP_CFG			0x0018
#घोषणा REG_RSV_CTRL			0x001C
#घोषणा REG_RF_CTRL			0x001F
#घोषणा REG_LDOA15_CTRL			0x0020
#घोषणा REG_LDOV12D_CTRL		0x0021
#घोषणा REG_LDOHCI12_CTRL		0x0022
#घोषणा REG_LPLDO_CTRL			0x0023
#घोषणा REG_AFE_XTAL_CTRL		0x0024
#घोषणा REG_AFE_PLL_CTRL		0x0028
/* क्रम 92d, DMDP,SMSP,DMSP contrl */
#घोषणा REG_MAC_PHY_CTRL		0x002c
#घोषणा REG_EFUSE_CTRL			0x0030
#घोषणा REG_EFUSE_TEST			0x0034
#घोषणा REG_PWR_DATA			0x0038
#घोषणा REG_CAL_TIMER			0x003C
#घोषणा REG_ACLK_MON			0x003E
#घोषणा REG_GPIO_MUXCFG			0x0040
#घोषणा REG_GPIO_IO_SEL			0x0042
#घोषणा REG_MAC_PINMUX_CFG		0x0043
#घोषणा REG_GPIO_PIN_CTRL		0x0044
#घोषणा REG_GPIO_INTM			0x0048
#घोषणा REG_LEDCFG0			0x004C
#घोषणा REG_LEDCFG1			0x004D
#घोषणा REG_LEDCFG2			0x004E
#घोषणा REG_LEDCFG3			0x004F
#घोषणा REG_FSIMR			0x0050
#घोषणा REG_FSISR			0x0054

#घोषणा REG_MCUFWDL			0x0080

#घोषणा REG_HMEBOX_EXT_0		0x0088
#घोषणा REG_HMEBOX_EXT_1		0x008A
#घोषणा REG_HMEBOX_EXT_2		0x008C
#घोषणा REG_HMEBOX_EXT_3		0x008E

#घोषणा REG_BIST_SCAN			0x00D0
#घोषणा REG_BIST_RPT			0x00D4
#घोषणा REG_BIST_ROM_RPT		0x00D8
#घोषणा REG_USB_SIE_INTF		0x00E0
#घोषणा REG_PCIE_MIO_INTF		0x00E4
#घोषणा REG_PCIE_MIO_INTD		0x00E8
#घोषणा REG_HPON_FSM			0x00EC
#घोषणा REG_SYS_CFG			0x00F0
#घोषणा REG_MAC_PHY_CTRL_NORMAL		0x00f8

#घोषणा  REG_MAC0			0x0081
#घोषणा  REG_MAC1			0x0053
#घोषणा  FW_MAC0_READY			0x18
#घोषणा  FW_MAC1_READY			0x1A
#घोषणा  MAC0_ON			BIT(7)
#घोषणा  MAC1_ON			BIT(0)
#घोषणा  MAC0_READY			BIT(0)
#घोषणा  MAC1_READY			BIT(0)

/* ----------------------------------------------------- */
/* 0x0100h ~ 0x01FFh	MACTOP General Configuration */
/* ----------------------------------------------------- */
#घोषणा REG_CR				0x0100
#घोषणा REG_PBP				0x0104
#घोषणा REG_TRXDMA_CTRL			0x010C
#घोषणा REG_TRXFF_BNDY			0x0114
#घोषणा REG_TRXFF_STATUS		0x0118
#घोषणा REG_RXFF_PTR			0x011C
#घोषणा REG_HIMR			0x0120
#घोषणा REG_HISR			0x0124
#घोषणा REG_HIMRE			0x0128
#घोषणा REG_HISRE			0x012C
#घोषणा REG_CPWM			0x012F
#घोषणा REG_FWIMR			0x0130
#घोषणा REG_FWISR			0x0134
#घोषणा REG_PKTBUF_DBG_CTRL		0x0140
#घोषणा REG_PKTBUF_DBG_DATA_L		0x0144
#घोषणा REG_PKTBUF_DBG_DATA_H		0x0148

#घोषणा REG_TC0_CTRL			0x0150
#घोषणा REG_TC1_CTRL			0x0154
#घोषणा REG_TC2_CTRL			0x0158
#घोषणा REG_TC3_CTRL			0x015C
#घोषणा REG_TC4_CTRL			0x0160
#घोषणा REG_TCUNIT_BASE			0x0164
#घोषणा REG_MBIST_START			0x0174
#घोषणा REG_MBIST_DONE			0x0178
#घोषणा REG_MBIST_FAIL			0x017C
#घोषणा REG_C2HEVT_MSG_NORMAL		0x01A0
#घोषणा REG_C2HEVT_MSG_TEST		0x01B8
#घोषणा REG_C2HEVT_CLEAR		0x01BF
#घोषणा REG_MCUTST_1			0x01c0
#घोषणा REG_FMETHR			0x01C8
#घोषणा REG_HMETFR			0x01CC
#घोषणा REG_HMEBOX_0			0x01D0
#घोषणा REG_HMEBOX_1			0x01D4
#घोषणा REG_HMEBOX_2			0x01D8
#घोषणा REG_HMEBOX_3			0x01DC

#घोषणा REG_LLT_INIT			0x01E0
#घोषणा REG_BB_ACCEESS_CTRL		0x01E8
#घोषणा REG_BB_ACCESS_DATA		0x01EC


/* ----------------------------------------------------- */
/*	0x0200h ~ 0x027Fh	TXDMA Configuration */
/* ----------------------------------------------------- */
#घोषणा REG_RQPN			0x0200
#घोषणा REG_FIFOPAGE			0x0204
#घोषणा REG_TDECTRL			0x0208
#घोषणा REG_TXDMA_OFFSET_CHK		0x020C
#घोषणा REG_TXDMA_STATUS		0x0210
#घोषणा REG_RQPN_NPQ			0x0214

/* ----------------------------------------------------- */
/*	0x0280h ~ 0x02FFh	RXDMA Configuration */
/* ----------------------------------------------------- */
#घोषणा REG_RXDMA_AGG_PG_TH		0x0280
#घोषणा REG_RXPKT_NUM			0x0284
#घोषणा REG_RXDMA_STATUS		0x0288

/* ----------------------------------------------------- */
/*	0x0300h ~ 0x03FFh	PCIe  */
/* ----------------------------------------------------- */
#घोषणा	REG_PCIE_CTRL_REG		0x0300
#घोषणा	REG_INT_MIG			0x0304
#घोषणा	REG_BCNQ_DESA			0x0308
#घोषणा	REG_HQ_DESA			0x0310
#घोषणा	REG_MGQ_DESA			0x0318
#घोषणा	REG_VOQ_DESA			0x0320
#घोषणा	REG_VIQ_DESA			0x0328
#घोषणा	REG_BEQ_DESA			0x0330
#घोषणा	REG_BKQ_DESA			0x0338
#घोषणा	REG_RX_DESA			0x0340
#घोषणा	REG_DBI				0x0348
#घोषणा	REG_DBI_WDATA			0x0348
#घोषणा REG_DBI_RDATA			0x034C
#घोषणा REG_DBI_CTRL			0x0350
#घोषणा REG_DBI_FLAG			0x0352
#घोषणा	REG_MDIO			0x0354
#घोषणा	REG_DBG_SEL			0x0360
#घोषणा	REG_PCIE_HRPWM			0x0361
#घोषणा	REG_PCIE_HCPWM			0x0363
#घोषणा	REG_UART_CTRL			0x0364
#घोषणा	REG_UART_TX_DESA		0x0370
#घोषणा	REG_UART_RX_DESA		0x0378

/* ----------------------------------------------------- */
/*	0x0400h ~ 0x047Fh	Protocol Configuration  */
/* ----------------------------------------------------- */
#घोषणा REG_VOQ_INFORMATION		0x0400
#घोषणा REG_VIQ_INFORMATION		0x0404
#घोषणा REG_BEQ_INFORMATION		0x0408
#घोषणा REG_BKQ_INFORMATION		0x040C
#घोषणा REG_MGQ_INFORMATION		0x0410
#घोषणा REG_HGQ_INFORMATION		0x0414
#घोषणा REG_BCNQ_INFORMATION		0x0418


#घोषणा REG_CPU_MGQ_INFORMATION		0x041C
#घोषणा REG_FWHW_TXQ_CTRL		0x0420
#घोषणा REG_HWSEQ_CTRL			0x0423
#घोषणा REG_TXPKTBUF_BCNQ_BDNY		0x0424
#घोषणा REG_TXPKTBUF_MGQ_BDNY		0x0425
#घोषणा REG_MULTI_BCNQ_EN		0x0426
#घोषणा REG_MULTI_BCNQ_OFFSET		0x0427
#घोषणा REG_SPEC_SIFS			0x0428
#घोषणा REG_RL				0x042A
#घोषणा REG_DARFRC			0x0430
#घोषणा REG_RARFRC			0x0438
#घोषणा REG_RRSR			0x0440
#घोषणा REG_ARFR0			0x0444
#घोषणा REG_ARFR1			0x0448
#घोषणा REG_ARFR2			0x044C
#घोषणा REG_ARFR3			0x0450
#घोषणा REG_AGGLEN_LMT			0x0458
#घोषणा REG_AMPDU_MIN_SPACE		0x045C
#घोषणा REG_TXPKTBUF_WMAC_LBK_BF_HD	0x045D
#घोषणा REG_FAST_EDCA_CTRL		0x0460
#घोषणा REG_RD_RESP_PKT_TH		0x0463
#घोषणा REG_INIRTS_RATE_SEL		0x0480
#घोषणा REG_INIDATA_RATE_SEL		0x0484
#घोषणा REG_POWER_STATUS		0x04A4
#घोषणा REG_POWER_STAGE1		0x04B4
#घोषणा REG_POWER_STAGE2		0x04B8
#घोषणा REG_PKT_LIFE_TIME		0x04C0
#घोषणा REG_STBC_SETTING		0x04C4
#घोषणा REG_PROT_MODE_CTRL		0x04C8
#घोषणा REG_MAX_AGGR_NUM		0x04CA
#घोषणा REG_RTS_MAX_AGGR_NUM		0x04CB
#घोषणा REG_BAR_MODE_CTRL		0x04CC
#घोषणा REG_RA_TRY_RATE_AGG_LMT		0x04CF
#घोषणा REG_EARLY_MODE_CONTROL		0x4D0
#घोषणा REG_NQOS_SEQ			0x04DC
#घोषणा REG_QOS_SEQ			0x04DE
#घोषणा REG_NEED_CPU_HANDLE		0x04E0
#घोषणा REG_PKT_LOSE_RPT		0x04E1
#घोषणा REG_PTCL_ERR_STATUS		0x04E2
#घोषणा REG_DUMMY			0x04FC

/* ----------------------------------------------------- */
/*	0x0500h ~ 0x05FFh	EDCA Configuration   */
/* ----------------------------------------------------- */
#घोषणा REG_EDCA_VO_PARAM		0x0500
#घोषणा REG_EDCA_VI_PARAM		0x0504
#घोषणा REG_EDCA_BE_PARAM		0x0508
#घोषणा REG_EDCA_BK_PARAM		0x050C
#घोषणा REG_BCNTCFG			0x0510
#घोषणा REG_PIFS			0x0512
#घोषणा REG_RDG_PIFS			0x0513
#घोषणा REG_SIFS_CTX			0x0514
#घोषणा REG_SIFS_TRX			0x0516
#घोषणा REG_AGGR_BREAK_TIME		0x051A
#घोषणा REG_SLOT			0x051B
#घोषणा REG_TX_PTCL_CTRL		0x0520
#घोषणा REG_TXPAUSE			0x0522
#घोषणा REG_DIS_TXREQ_CLR		0x0523
#घोषणा REG_RD_CTRL			0x0524
#घोषणा REG_TBTT_PROHIBIT		0x0540
#घोषणा REG_RD_NAV_NXT			0x0544
#घोषणा REG_NAV_PROT_LEN		0x0546
#घोषणा REG_BCN_CTRL			0x0550
#घोषणा REG_MBID_NUM			0x0552
#घोषणा REG_DUAL_TSF_RST		0x0553
#घोषणा REG_BCN_INTERVAL		0x0554
#घोषणा REG_MBSSID_BCN_SPACE		0x0554
#घोषणा REG_DRVERLYINT			0x0558
#घोषणा REG_BCNDMATIM			0x0559
#घोषणा REG_ATIMWND			0x055A
#घोषणा REG_USTIME_TSF			0x055C
#घोषणा REG_BCN_MAX_ERR			0x055D
#घोषणा REG_RXTSF_OFFSET_CCK		0x055E
#घोषणा REG_RXTSF_OFFSET_OFDM		0x055F
#घोषणा REG_TSFTR			0x0560
#घोषणा REG_INIT_TSFTR			0x0564
#घोषणा REG_PSTIMER			0x0580
#घोषणा REG_TIMER0			0x0584
#घोषणा REG_TIMER1			0x0588
#घोषणा REG_ACMHWCTRL			0x05C0
#घोषणा REG_ACMRSTCTRL			0x05C1
#घोषणा REG_ACMAVG			0x05C2
#घोषणा REG_VO_ADMTIME			0x05C4
#घोषणा REG_VI_ADMTIME			0x05C6
#घोषणा REG_BE_ADMTIME			0x05C8
#घोषणा REG_EDCA_RANDOM_GEN		0x05CC
#घोषणा REG_SCH_TXCMD			0x05D0

/* Dual MAC Co-Existence Register  */
#घोषणा REG_DMC				0x05F0

/* ----------------------------------------------------- */
/*	0x0600h ~ 0x07FFh	WMAC Configuration */
/* ----------------------------------------------------- */
#घोषणा REG_APSD_CTRL			0x0600
#घोषणा REG_BWOPMODE			0x0603
#घोषणा REG_TCR				0x0604
#घोषणा REG_RCR				0x0608
#घोषणा REG_RX_PKT_LIMIT		0x060C
#घोषणा REG_RX_DLK_TIME			0x060D
#घोषणा REG_RX_DRVINFO_SZ		0x060F

#घोषणा REG_MACID			0x0610
#घोषणा REG_BSSID			0x0618
#घोषणा REG_MAR				0x0620
#घोषणा REG_MBIDCAMCFG			0x0628

#घोषणा REG_USTIME_EDCA			0x0638
#घोषणा REG_MAC_SPEC_SIFS		0x063A
#घोषणा REG_RESP_SIFS_CCK		0x063C
#घोषणा REG_RESP_SIFS_OFDM		0x063E
#घोषणा REG_ACKTO			0x0640
#घोषणा REG_CTS2TO			0x0641
#घोषणा REG_EIFS			0x0642


/* WMA, BA, CCX */
#घोषणा REG_NAV_CTRL			0x0650
#घोषणा REG_BACAMCMD			0x0654
#घोषणा REG_BACAMCONTENT		0x0658
#घोषणा REG_LBDLY			0x0660
#घोषणा REG_FWDLY			0x0661
#घोषणा REG_RXERR_RPT			0x0664
#घोषणा REG_WMAC_TRXPTCL_CTL		0x0668


/* Security  */
#घोषणा REG_CAMCMD			0x0670
#घोषणा REG_CAMWRITE			0x0674
#घोषणा REG_CAMREAD			0x0678
#घोषणा REG_CAMDBG			0x067C
#घोषणा REG_SECCFG			0x0680

/* Power  */
#घोषणा REG_WOW_CTRL			0x0690
#घोषणा REG_PSSTATUS			0x0691
#घोषणा REG_PS_RX_INFO			0x0692
#घोषणा REG_LPNAV_CTRL			0x0694
#घोषणा REG_WKFMCAM_CMD			0x0698
#घोषणा REG_WKFMCAM_RWD			0x069C
#घोषणा REG_RXFLTMAP0			0x06A0
#घोषणा REG_RXFLTMAP1			0x06A2
#घोषणा REG_RXFLTMAP2			0x06A4
#घोषणा REG_BCN_PSR_RPT			0x06A8
#घोषणा REG_CALB32K_CTRL		0x06AC
#घोषणा REG_PKT_MON_CTRL		0x06B4
#घोषणा REG_BT_COEX_TABLE		0x06C0
#घोषणा REG_WMAC_RESP_TXINFO		0x06D8


/* ----------------------------------------------------- */
/*	Redअगरine 8192C रेजिस्टर definition क्रम compatibility */
/* ----------------------------------------------------- */
#घोषणा	CR9346				REG_9346CR
#घोषणा	MSR				(REG_CR + 2)
#घोषणा	ISR				REG_HISR
#घोषणा	TSFR				REG_TSFTR

#घोषणा	MACIDR0				REG_MACID
#घोषणा	MACIDR4				(REG_MACID + 4)

#घोषणा PBP				REG_PBP

#घोषणा	IDR0				MACIDR0
#घोषणा	IDR4				MACIDR4

/* ----------------------------------------------------- */
/* 8192C (MSR) Media Status Register(Offset 0x4C, 8 bits)*/
/* ----------------------------------------------------- */
#घोषणा	MSR_NOLINK			0x00
#घोषणा	MSR_ADHOC			0x01
#घोषणा	MSR_INFRA			0x02
#घोषणा	MSR_AP				0x03
#घोषणा	MSR_MASK			0x03

/* 6. Adaptive Control Registers  (Offset: 0x0160 - 0x01CF) */
/* ----------------------------------------------------- */
/* 8192C Response Rate Set Register(offset 0x181, 24bits)*/
/* ----------------------------------------------------- */
#घोषणा	RRSR_RSC_OFFSET			21
#घोषणा	RRSR_SHORT_OFFSET		23
#घोषणा	RRSR_RSC_BW_40M			0x600000
#घोषणा	RRSR_RSC_UPSUBCHNL		0x400000
#घोषणा	RRSR_RSC_LOWSUBCHNL		0x200000
#घोषणा	RRSR_SHORT			0x800000
#घोषणा	RRSR_1M				BIT0
#घोषणा	RRSR_2M				BIT1
#घोषणा	RRSR_5_5M			BIT2
#घोषणा	RRSR_11M			BIT3
#घोषणा	RRSR_6M				BIT4
#घोषणा	RRSR_9M				BIT5
#घोषणा	RRSR_12M			BIT6
#घोषणा	RRSR_18M			BIT7
#घोषणा	RRSR_24M			BIT8
#घोषणा	RRSR_36M			BIT9
#घोषणा	RRSR_48M			BIT10
#घोषणा	RRSR_54M			BIT11
#घोषणा	RRSR_MCS0			BIT12
#घोषणा	RRSR_MCS1			BIT13
#घोषणा	RRSR_MCS2			BIT14
#घोषणा	RRSR_MCS3			BIT15
#घोषणा	RRSR_MCS4			BIT16
#घोषणा	RRSR_MCS5			BIT17
#घोषणा	RRSR_MCS6			BIT18
#घोषणा	RRSR_MCS7			BIT19
#घोषणा	BRSR_ACKSHORTPMB		BIT23

/* ----------------------------------------------------- */
/*       8192C Rate Definition  */
/* ----------------------------------------------------- */
/* CCK */
#घोषणा	RATR_1M				0x00000001
#घोषणा	RATR_2M				0x00000002
#घोषणा	RATR_55M			0x00000004
#घोषणा	RATR_11M			0x00000008
/* OFDM */
#घोषणा	RATR_6M				0x00000010
#घोषणा	RATR_9M				0x00000020
#घोषणा	RATR_12M			0x00000040
#घोषणा	RATR_18M			0x00000080
#घोषणा	RATR_24M			0x00000100
#घोषणा	RATR_36M			0x00000200
#घोषणा	RATR_48M			0x00000400
#घोषणा	RATR_54M			0x00000800
/* MCS 1 Spatial Stream	*/
#घोषणा	RATR_MCS0			0x00001000
#घोषणा	RATR_MCS1			0x00002000
#घोषणा	RATR_MCS2			0x00004000
#घोषणा	RATR_MCS3			0x00008000
#घोषणा	RATR_MCS4			0x00010000
#घोषणा	RATR_MCS5			0x00020000
#घोषणा	RATR_MCS6			0x00040000
#घोषणा	RATR_MCS7			0x00080000
/* MCS 2 Spatial Stream */
#घोषणा	RATR_MCS8			0x00100000
#घोषणा	RATR_MCS9			0x00200000
#घोषणा	RATR_MCS10			0x00400000
#घोषणा	RATR_MCS11			0x00800000
#घोषणा	RATR_MCS12			0x01000000
#घोषणा	RATR_MCS13			0x02000000
#घोषणा	RATR_MCS14			0x04000000
#घोषणा	RATR_MCS15			0x08000000

/* CCK */
#घोषणा RATE_1M				BIT(0)
#घोषणा RATE_2M				BIT(1)
#घोषणा RATE_5_5M			BIT(2)
#घोषणा RATE_11M			BIT(3)
/* OFDM  */
#घोषणा RATE_6M				BIT(4)
#घोषणा RATE_9M				BIT(5)
#घोषणा RATE_12M			BIT(6)
#घोषणा RATE_18M			BIT(7)
#घोषणा RATE_24M			BIT(8)
#घोषणा RATE_36M			BIT(9)
#घोषणा RATE_48M			BIT(10)
#घोषणा RATE_54M			BIT(11)
/* MCS 1 Spatial Stream */
#घोषणा RATE_MCS0			BIT(12)
#घोषणा RATE_MCS1			BIT(13)
#घोषणा RATE_MCS2			BIT(14)
#घोषणा RATE_MCS3			BIT(15)
#घोषणा RATE_MCS4			BIT(16)
#घोषणा RATE_MCS5			BIT(17)
#घोषणा RATE_MCS6			BIT(18)
#घोषणा RATE_MCS7			BIT(19)
/* MCS 2 Spatial Stream */
#घोषणा RATE_MCS8			BIT(20)
#घोषणा RATE_MCS9			BIT(21)
#घोषणा RATE_MCS10			BIT(22)
#घोषणा RATE_MCS11			BIT(23)
#घोषणा RATE_MCS12			BIT(24)
#घोषणा RATE_MCS13			BIT(25)
#घोषणा RATE_MCS14			BIT(26)
#घोषणा RATE_MCS15			BIT(27)

/* ALL CCK Rate */
#घोषणा	RATE_ALL_CCK			(RATR_1M | RATR_2M | RATR_55M | \
					RATR_11M)
#घोषणा	RATE_ALL_OFDM_AG		(RATR_6M | RATR_9M | RATR_12M | \
					RATR_18M | RATR_24M | \
					RATR_36M | RATR_48M | RATR_54M)
#घोषणा	RATE_ALL_OFDM_1SS		(RATR_MCS0 | RATR_MCS1 | RATR_MCS2 | \
					RATR_MCS3 | RATR_MCS4 | RATR_MCS5 | \
					RATR_MCS6 | RATR_MCS7)
#घोषणा	RATE_ALL_OFDM_2SS		(RATR_MCS8 | RATR_MCS9 | RATR_MCS10 | \
					RATR_MCS11 | RATR_MCS12 | RATR_MCS13 | \
					RATR_MCS14 | RATR_MCS15)

/* ----------------------------------------------------- */
/*    8192C BW_OPMODE bits		(Offset 0x203, 8bit)     */
/* ----------------------------------------------------- */
#घोषणा	BW_OPMODE_20MHZ			BIT(2)
#घोषणा	BW_OPMODE_5G			BIT(1)
#घोषणा	BW_OPMODE_11J			BIT(0)


/* ----------------------------------------------------- */
/*     8192C CAM Config Setting (offset 0x250, 1 byte)   */
/* ----------------------------------------------------- */
#घोषणा	CAM_VALID			BIT(15)
#घोषणा	CAM_NOTVALID			0x0000
#घोषणा	CAM_USEDK			BIT(5)

#घोषणा	CAM_NONE			0x0
#घोषणा	CAM_WEP40			0x01
#घोषणा	CAM_TKIP			0x02
#घोषणा	CAM_AES				0x04
#घोषणा	CAM_WEP104			0x05
#घोषणा	CAM_SMS4			0x6


#घोषणा	TOTAL_CAM_ENTRY			32
#घोषणा	HALF_CAM_ENTRY			16

#घोषणा	CAM_WRITE			BIT(16)
#घोषणा	CAM_READ			0x00000000
#घोषणा	CAM_POLLINIG			BIT(31)

/* 10. Power Save Control Registers	 (Offset: 0x0260 - 0x02DF) */
#घोषणा	WOW_PMEN			BIT0 /* Power management Enable. */
#घोषणा	WOW_WOMEN			BIT1 /* WoW function on or off. */
#घोषणा	WOW_MAGIC			BIT2 /* Magic packet */
#घोषणा	WOW_UWF				BIT3 /* Unicast Wakeup frame. */

/* 12. Host Interrupt Status Registers	 (Offset: 0x0300 - 0x030F) */
/* ----------------------------------------------------- */
/*      8190 IMR/ISR bits	(offset 0xfd,  8bits) */
/* ----------------------------------------------------- */
#घोषणा	IMR8190_DISABLED		0x0
#घोषणा	IMR_BCNDMAINT6			BIT(31)
#घोषणा	IMR_BCNDMAINT5			BIT(30)
#घोषणा	IMR_BCNDMAINT4			BIT(29)
#घोषणा	IMR_BCNDMAINT3			BIT(28)
#घोषणा	IMR_BCNDMAINT2			BIT(27)
#घोषणा	IMR_BCNDMAINT1			BIT(26)
#घोषणा	IMR_BCNDOK8			BIT(25)
#घोषणा	IMR_BCNDOK7			BIT(24)
#घोषणा	IMR_BCNDOK6			BIT(23)
#घोषणा	IMR_BCNDOK5			BIT(22)
#घोषणा	IMR_BCNDOK4			BIT(21)
#घोषणा	IMR_BCNDOK3			BIT(20)
#घोषणा	IMR_BCNDOK2			BIT(19)
#घोषणा	IMR_BCNDOK1			BIT(18)
#घोषणा	IMR_TIMEOUT2			BIT(17)
#घोषणा	IMR_TIMEOUT1			BIT(16)
#घोषणा	IMR_TXFOVW			BIT(15)
#घोषणा	IMR_PSTIMEOUT			BIT(14)
#घोषणा	IMR_BCNINT			BIT(13)
#घोषणा	IMR_RXFOVW			BIT(12)
#घोषणा	IMR_RDU				BIT(11)
#घोषणा	IMR_ATIMEND			BIT(10)
#घोषणा	IMR_BDOK			BIT(9)
#घोषणा	IMR_HIGHDOK			BIT(8)
#घोषणा	IMR_TBDOK			BIT(7)
#घोषणा	IMR_MGNTDOK			BIT(6)
#घोषणा	IMR_TBDER			BIT(5)
#घोषणा	IMR_BKDOK			BIT(4)
#घोषणा	IMR_BEDOK			BIT(3)
#घोषणा	IMR_VIDOK			BIT(2)
#घोषणा	IMR_VODOK			BIT(1)
#घोषणा	IMR_ROK				BIT(0)

#घोषणा	IMR_TXERR			BIT(11)
#घोषणा	IMR_RXERR			BIT(10)
#घोषणा	IMR_C2HCMD			BIT(9)
#घोषणा	IMR_CPWM			BIT(8)
#घोषणा	IMR_OCPINT			BIT(1)
#घोषणा	IMR_WLANOFF			BIT(0)

/* ----------------------------------------------------- */
/* 8192C EFUSE */
/* ----------------------------------------------------- */
#घोषणा	HWSET_MAX_SIZE			256
#घोषणा EFUSE_MAX_SECTION		32
#घोषणा EFUSE_REAL_CONTENT_LEN		512

/* ----------------------------------------------------- */
/*     8192C EEPROM/EFUSE share रेजिस्टर definition. */
/* ----------------------------------------------------- */
#घोषणा	EEPROM_DEFAULT_TSSI			0x0
#घोषणा EEPROM_DEFAULT_CRYSTALCAP		0x0
#घोषणा	EEPROM_DEFAULT_THERMALMETER		0x12

#घोषणा	EEPROM_DEFAULT_TXPOWERLEVEL_2G		0x2C
#घोषणा	EEPROM_DEFAULT_TXPOWERLEVEL_5G		0x22

#घोषणा	EEPROM_DEFAULT_HT40_2SDIFF		0x0
/* HT20<->40 शेष Tx Power Index Dअगरference */
#घोषणा EEPROM_DEFAULT_HT20_DIFF		2
/* OFDM Tx Power index dअगरf */
#घोषणा	EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF	0x4
#घोषणा EEPROM_DEFAULT_HT40_PWRMAXOFFSET	0
#घोषणा EEPROM_DEFAULT_HT20_PWRMAXOFFSET	0

#घोषणा	EEPROM_CHANNEL_PLAN_FCC			0x0
#घोषणा	EEPROM_CHANNEL_PLAN_IC			0x1
#घोषणा	EEPROM_CHANNEL_PLAN_ETSI		0x2
#घोषणा	EEPROM_CHANNEL_PLAN_SPAIN		0x3
#घोषणा	EEPROM_CHANNEL_PLAN_FRANCE		0x4
#घोषणा	EEPROM_CHANNEL_PLAN_MKK			0x5
#घोषणा	EEPROM_CHANNEL_PLAN_MKK1		0x6
#घोषणा	EEPROM_CHANNEL_PLAN_ISRAEL		0x7
#घोषणा	EEPROM_CHANNEL_PLAN_TELEC		0x8
#घोषणा	EEPROM_CHANNEL_PLAN_GLOBAL_DOMAIN	0x9
#घोषणा	EEPROM_CHANNEL_PLAN_WORLD_WIDE_13	0xA
#घोषणा	EEPROM_CHANNEL_PLAN_NCC			0xB
#घोषणा	EEPROM_CHANNEL_PLAN_BY_HW_MASK		0x80

#घोषणा EEPROM_CID_DEFAULT			0x0
#घोषणा EEPROM_CID_TOSHIBA			0x4
#घोषणा	EEPROM_CID_CCX				0x10
#घोषणा	EEPROM_CID_QMI				0x0D
#घोषणा EEPROM_CID_WHQL				0xFE


#घोषणा	RTL8192_EEPROM_ID			0x8129
#घोषणा	EEPROM_WAPI_SUPPORT			0x78


#घोषणा RTL8190_EEPROM_ID		0x8129	/* 0-1 */
#घोषणा EEPROM_HPON			0x02 /* LDO settings.2-5 */
#घोषणा EEPROM_CLK			0x06 /* Clock settings.6-7 */
#घोषणा EEPROM_MAC_FUNCTION		0x08 /* SE Test mode.8 */

#घोषणा EEPROM_VID			0x28 /* SE Venकरोr ID.A-B */
#घोषणा EEPROM_DID			0x2A /* SE Device ID. C-D */
#घोषणा EEPROM_SVID			0x2C /* SE Venकरोr ID.E-F */
#घोषणा EEPROM_SMID			0x2E /* SE PCI Subप्रणाली ID. 10-11 */

#घोषणा EEPROM_MAC_ADDR			0x16 /* SEMAC Address. 12-17 */
#घोषणा EEPROM_MAC_ADDR_MAC0_92D	0x55
#घोषणा EEPROM_MAC_ADDR_MAC1_92D	0x5B

/* 2.4G band Tx घातer index setting */
#घोषणा EEPROM_CCK_TX_PWR_INX_2G	0x61
#घोषणा EEPROM_HT40_1S_TX_PWR_INX_2G	0x67
#घोषणा EEPROM_HT40_2S_TX_PWR_INX_DIFF_2G	0x6D
#घोषणा EEPROM_HT20_TX_PWR_INX_DIFF_2G		0x70
#घोषणा EEPROM_OFDM_TX_PWR_INX_DIFF_2G		0x73
#घोषणा EEPROM_HT40_MAX_PWR_OFFSET_2G		0x76
#घोषणा EEPROM_HT20_MAX_PWR_OFFSET_2G		0x79

/*5GL channel 32-64 */
#घोषणा EEPROM_HT40_1S_TX_PWR_INX_5GL		0x7C
#घोषणा EEPROM_HT40_2S_TX_PWR_INX_DIFF_5GL	0x82
#घोषणा EEPROM_HT20_TX_PWR_INX_DIFF_5GL		0x85
#घोषणा EEPROM_OFDM_TX_PWR_INX_DIFF_5GL		0x88
#घोषणा EEPROM_HT40_MAX_PWR_OFFSET_5GL		0x8B
#घोषणा EEPROM_HT20_MAX_PWR_OFFSET_5GL		0x8E

/* 5GM channel 100-140 */
#घोषणा EEPROM_HT40_1S_TX_PWR_INX_5GM		0x91
#घोषणा EEPROM_HT40_2S_TX_PWR_INX_DIFF_5GM	0x97
#घोषणा EEPROM_HT20_TX_PWR_INX_DIFF_5GM		0x9A
#घोषणा EEPROM_OFDM_TX_PWR_INX_DIFF_5GM		0x9D
#घोषणा EEPROM_HT40_MAX_PWR_OFFSET_5GM		0xA0
#घोषणा EEPROM_HT20_MAX_PWR_OFFSET_5GM		0xA3

/* 5GH channel 149-165 */
#घोषणा EEPROM_HT40_1S_TX_PWR_INX_5GH		0xA6
#घोषणा EEPROM_HT40_2S_TX_PWR_INX_DIFF_5GH	0xAC
#घोषणा EEPROM_HT20_TX_PWR_INX_DIFF_5GH		0xAF
#घोषणा EEPROM_OFDM_TX_PWR_INX_DIFF_5GH		0xB2
#घोषणा EEPROM_HT40_MAX_PWR_OFFSET_5GH		0xB5
#घोषणा EEPROM_HT20_MAX_PWR_OFFSET_5GH		0xB8

/* Map of supported channels. */
#घोषणा EEPROM_CHANNEL_PLAN			0xBB
#घोषणा EEPROM_IQK_DELTA			0xBC
#घोषणा EEPROM_LCK_DELTA			0xBC
#घोषणा EEPROM_XTAL_K				0xBD	/* [7:5] */
#घोषणा EEPROM_TSSI_A_5G			0xBE
#घोषणा EEPROM_TSSI_B_5G			0xBF
#घोषणा EEPROM_TSSI_AB_5G			0xC0
#घोषणा EEPROM_THERMAL_METER			0xC3	/* [4:0] */
#घोषणा EEPROM_RF_OPT1				0xC4
#घोषणा EEPROM_RF_OPT2				0xC5
#घोषणा EEPROM_RF_OPT3				0xC6
#घोषणा EEPROM_RF_OPT4				0xC7
#घोषणा EEPROM_RF_OPT5				0xC8
#घोषणा EEPROM_RF_OPT6				0xC9
#घोषणा EEPROM_VERSION				0xCA
#घोषणा EEPROM_CUSTOMER_ID			0xCB
#घोषणा EEPROM_RF_OPT7				0xCC

#घोषणा EEPROM_DEF_PART_NO			0x3FD    /* Byte */
#घोषणा EEPROME_CHIP_VERSION_L			0x3FF
#घोषणा EEPROME_CHIP_VERSION_H			0x3FE

/*
 * Current IOREG MAP
 * 0x0000h ~ 0x00FFh   System Configuration (256 Bytes)
 * 0x0100h ~ 0x01FFh   MACTOP General Configuration (256 Bytes)
 * 0x0200h ~ 0x027Fh   TXDMA Configuration (128 Bytes)
 * 0x0280h ~ 0x02FFh   RXDMA Configuration (128 Bytes)
 * 0x0300h ~ 0x03FFh   PCIE EMAC Reserved Region (256 Bytes)
 * 0x0400h ~ 0x04FFh   Protocol Configuration (256 Bytes)
 * 0x0500h ~ 0x05FFh   EDCA Configuration (256 Bytes)
 * 0x0600h ~ 0x07FFh   WMAC Configuration (512 Bytes)
 * 0x2000h ~ 0x3FFFh   8051 FW Download Region (8196 Bytes)
 */

/* ----------------------------------------------------- */
/* 8192C (RCR)	(Offset 0x608, 32 bits) */
/* ----------------------------------------------------- */
#घोषणा	RCR_APPFCS				BIT(31)
#घोषणा	RCR_APP_MIC				BIT(30)
#घोषणा	RCR_APP_ICV				BIT(29)
#घोषणा	RCR_APP_PHYST_RXFF			BIT(28)
#घोषणा	RCR_APP_BA_SSN				BIT(27)
#घोषणा	RCR_ENMBID				BIT(24)
#घोषणा	RCR_LSIGEN				BIT(23)
#घोषणा	RCR_MFBEN				BIT(22)
#घोषणा	RCR_HTC_LOC_CTRL			BIT(14)
#घोषणा	RCR_AMF					BIT(13)
#घोषणा	RCR_ACF					BIT(12)
#घोषणा	RCR_ADF					BIT(11)
#घोषणा	RCR_AICV				BIT(9)
#घोषणा	RCR_ACRC32				BIT(8)
#घोषणा	RCR_CBSSID_BCN				BIT(7)
#घोषणा	RCR_CBSSID_DATA				BIT(6)
#घोषणा	RCR_APWRMGT				BIT(5)
#घोषणा	RCR_ADD3				BIT(4)
#घोषणा	RCR_AB					BIT(3)
#घोषणा	RCR_AM					BIT(2)
#घोषणा	RCR_APM					BIT(1)
#घोषणा	RCR_AAP					BIT(0)
#घोषणा	RCR_MXDMA_OFFSET			8
#घोषणा	RCR_FIFO_OFFSET				13

/* ----------------------------------------------------- */
/*       8192C Regsiter Bit and Content definition	 */
/* ----------------------------------------------------- */
/* ----------------------------------------------------- */
/*	0x0000h ~ 0x00FFh	System Configuration */
/* ----------------------------------------------------- */

/* SPS0_CTRL */
#घोषणा SW18_FPWM				BIT(3)


/* SYS_ISO_CTRL */
#घोषणा ISO_MD2PP				BIT(0)
#घोषणा ISO_UA2USB				BIT(1)
#घोषणा ISO_UD2CORE				BIT(2)
#घोषणा ISO_PA2PCIE				BIT(3)
#घोषणा ISO_PD2CORE				BIT(4)
#घोषणा ISO_IP2MAC				BIT(5)
#घोषणा ISO_DIOP				BIT(6)
#घोषणा ISO_DIOE				BIT(7)
#घोषणा ISO_EB2CORE				BIT(8)
#घोषणा ISO_DIOR				BIT(9)

#घोषणा PWC_EV25V				BIT(14)
#घोषणा PWC_EV12V				BIT(15)


/* SYS_FUNC_EN */
#घोषणा FEN_BBRSTB				BIT(0)
#घोषणा FEN_BB_GLB_RSTN				BIT(1)
#घोषणा FEN_USBA				BIT(2)
#घोषणा FEN_UPLL				BIT(3)
#घोषणा FEN_USBD				BIT(4)
#घोषणा FEN_DIO_PCIE				BIT(5)
#घोषणा FEN_PCIEA				BIT(6)
#घोषणा FEN_PPLL				BIT(7)
#घोषणा FEN_PCIED				BIT(8)
#घोषणा FEN_DIOE				BIT(9)
#घोषणा FEN_CPUEN				BIT(10)
#घोषणा FEN_DCORE				BIT(11)
#घोषणा FEN_ELDR				BIT(12)
#घोषणा FEN_DIO_RF				BIT(13)
#घोषणा FEN_HWPDN				BIT(14)
#घोषणा FEN_MREGEN				BIT(15)

/* APS_FSMCO */
#घोषणा PFM_LDALL				BIT(0)
#घोषणा PFM_ALDN				BIT(1)
#घोषणा PFM_LDKP				BIT(2)
#घोषणा PFM_WOWL				BIT(3)
#घोषणा ENPDN					BIT(4)
#घोषणा PDN_PL					BIT(5)
#घोषणा APFM_ONMAC				BIT(8)
#घोषणा APFM_OFF				BIT(9)
#घोषणा APFM_RSM				BIT(10)
#घोषणा AFSM_HSUS				BIT(11)
#घोषणा AFSM_PCIE				BIT(12)
#घोषणा APDM_MAC				BIT(13)
#घोषणा APDM_HOST				BIT(14)
#घोषणा APDM_HPDN				BIT(15)
#घोषणा RDY_MACON				BIT(16)
#घोषणा SUS_HOST				BIT(17)
#घोषणा ROP_ALD					BIT(20)
#घोषणा ROP_PWR					BIT(21)
#घोषणा ROP_SPS					BIT(22)
#घोषणा SOP_MRST				BIT(25)
#घोषणा SOP_FUSE				BIT(26)
#घोषणा SOP_ABG					BIT(27)
#घोषणा SOP_AMB					BIT(28)
#घोषणा SOP_RCK					BIT(29)
#घोषणा SOP_A8M					BIT(30)
#घोषणा XOP_BTCK				BIT(31)

/* SYS_CLKR */
#घोषणा ANAD16V_EN				BIT(0)
#घोषणा ANA8M					BIT(1)
#घोषणा MACSLP					BIT(4)
#घोषणा LOADER_CLK_EN				BIT(5)
#घोषणा _80M_SSC_DIS				BIT(7)
#घोषणा _80M_SSC_EN_HO				BIT(8)
#घोषणा PHY_SSC_RSTB				BIT(9)
#घोषणा SEC_CLK_EN				BIT(10)
#घोषणा MAC_CLK_EN				BIT(11)
#घोषणा SYS_CLK_EN				BIT(12)
#घोषणा RING_CLK_EN				BIT(13)


/* 9346CR */
#घोषणा	BOOT_FROM_EEPROM			BIT(4)
#घोषणा	EEPROM_EN				BIT(5)

/* AFE_MISC */
#घोषणा AFE_BGEN				BIT(0)
#घोषणा AFE_MBEN				BIT(1)
#घोषणा MAC_ID_EN				BIT(7)

/* RSV_CTRL */
#घोषणा WLOCK_ALL				BIT(0)
#घोषणा WLOCK_00				BIT(1)
#घोषणा WLOCK_04				BIT(2)
#घोषणा WLOCK_08				BIT(3)
#घोषणा WLOCK_40				BIT(4)
#घोषणा R_DIS_PRST_0				BIT(5)
#घोषणा R_DIS_PRST_1				BIT(6)
#घोषणा LOCK_ALL_EN				BIT(7)

/* RF_CTRL */
#घोषणा RF_EN					BIT(0)
#घोषणा RF_RSTB					BIT(1)
#घोषणा RF_SDMRSTB				BIT(2)



/* LDOA15_CTRL */
#घोषणा LDA15_EN				BIT(0)
#घोषणा LDA15_STBY				BIT(1)
#घोषणा LDA15_OBUF				BIT(2)
#घोषणा LDA15_REG_VOS				BIT(3)
#घोषणा _LDA15_VOADJ(x)				(((x) & 0x7) << 4)



/* LDOV12D_CTRL */
#घोषणा LDV12_EN				BIT(0)
#घोषणा LDV12_SDBY				BIT(1)
#घोषणा LPLDO_HSM				BIT(2)
#घोषणा LPLDO_LSM_DIS				BIT(3)
#घोषणा _LDV12_VADJ(x)				(((x) & 0xF) << 4)


/* AFE_XTAL_CTRL */
#घोषणा XTAL_EN					BIT(0)
#घोषणा XTAL_BSEL				BIT(1)
#घोषणा _XTAL_BOSC(x)				(((x) & 0x3) << 2)
#घोषणा _XTAL_CADJ(x)				(((x) & 0xF) << 4)
#घोषणा XTAL_GATE_USB				BIT(8)
#घोषणा _XTAL_USB_DRV(x)			(((x) & 0x3) << 9)
#घोषणा XTAL_GATE_AFE				BIT(11)
#घोषणा _XTAL_AFE_DRV(x)			(((x) & 0x3) << 12)
#घोषणा XTAL_RF_GATE				BIT(14)
#घोषणा _XTAL_RF_DRV(x)				(((x) & 0x3) << 15)
#घोषणा XTAL_GATE_DIG				BIT(17)
#घोषणा _XTAL_DIG_DRV(x)			(((x) & 0x3) << 18)
#घोषणा XTAL_BT_GATE				BIT(20)
#घोषणा _XTAL_BT_DRV(x)				(((x) & 0x3) << 21)
#घोषणा _XTAL_GPIO(x)				(((x) & 0x7) << 23)


#घोषणा CKDLY_AFE				BIT(26)
#घोषणा CKDLY_USB				BIT(27)
#घोषणा CKDLY_DIG				BIT(28)
#घोषणा CKDLY_BT				BIT(29)


/* AFE_PLL_CTRL */
#घोषणा APLL_EN					BIT(0)
#घोषणा APLL_320_EN				BIT(1)
#घोषणा APLL_FREF_SEL				BIT(2)
#घोषणा APLL_EDGE_SEL				BIT(3)
#घोषणा APLL_WDOGB				BIT(4)
#घोषणा APLL_LPFEN				BIT(5)

#घोषणा APLL_REF_CLK_13MHZ			0x1
#घोषणा APLL_REF_CLK_19_2MHZ			0x2
#घोषणा APLL_REF_CLK_20MHZ			0x3
#घोषणा APLL_REF_CLK_25MHZ			0x4
#घोषणा APLL_REF_CLK_26MHZ			0x5
#घोषणा APLL_REF_CLK_38_4MHZ			0x6
#घोषणा APLL_REF_CLK_40MHZ			0x7

#घोषणा APLL_320EN				BIT(14)
#घोषणा APLL_80EN				BIT(15)
#घोषणा APLL_1MEN				BIT(24)


/* EFUSE_CTRL */
#घोषणा ALD_EN					BIT(18)
#घोषणा EF_PD					BIT(19)
#घोषणा EF_FLAG					BIT(31)

/* EFUSE_TEST  */
#घोषणा EF_TRPT					BIT(7)
#घोषणा LDOE25_EN				BIT(31)

/* MCUFWDL  */
#घोषणा MCUFWDL_EN				BIT(0)
#घोषणा MCUFWDL_RDY				BIT(1)
#घोषणा FWDL_CHKSUM_RPT				BIT(2)
#घोषणा MACINI_RDY				BIT(3)
#घोषणा BBINI_RDY				BIT(4)
#घोषणा RFINI_RDY				BIT(5)
#घोषणा WINTINI_RDY				BIT(6)
#घोषणा MAC1_WINTINI_RDY			BIT(11)
#घोषणा CPRST					BIT(23)

/*  REG_SYS_CFG */
#घोषणा XCLK_VLD				BIT(0)
#घोषणा ACLK_VLD				BIT(1)
#घोषणा UCLK_VLD				BIT(2)
#घोषणा PCLK_VLD				BIT(3)
#घोषणा PCIRSTB					BIT(4)
#घोषणा V15_VLD					BIT(5)
#घोषणा TRP_B15V_EN				BIT(7)
#घोषणा SIC_IDLE				BIT(8)
#घोषणा BD_MAC2					BIT(9)
#घोषणा BD_MAC1					BIT(10)
#घोषणा IC_MACPHY_MODE				BIT(11)
#घोषणा PAD_HWPD_IDN				BIT(22)
#घोषणा TRP_VAUX_EN				BIT(23)
#घोषणा TRP_BT_EN				BIT(24)
#घोषणा BD_PKG_SEL				BIT(25)
#घोषणा BD_HCI_SEL				BIT(26)
#घोषणा TYPE_ID					BIT(27)

/* LLT_INIT */
#घोषणा _LLT_NO_ACTIVE				0x0
#घोषणा _LLT_WRITE_ACCESS			0x1
#घोषणा _LLT_READ_ACCESS			0x2

#घोषणा _LLT_INIT_DATA(x)			((x) & 0xFF)
#घोषणा _LLT_INIT_ADDR(x)			(((x) & 0xFF) << 8)
#घोषणा _LLT_OP(x)				(((x) & 0x3) << 30)
#घोषणा _LLT_OP_VALUE(x)			(((x) >> 30) & 0x3)


/* ----------------------------------------------------- */
/*	0x0400h ~ 0x047Fh	Protocol Configuration	 */
/* ----------------------------------------------------- */
#घोषणा	RETRY_LIMIT_SHORT_SHIFT			8
#घोषणा	RETRY_LIMIT_LONG_SHIFT			0


/* ----------------------------------------------------- */
/*	0x0500h ~ 0x05FFh	EDCA Configuration */
/* ----------------------------------------------------- */
/* EDCA setting */
#घोषणा AC_PARAM_TXOP_LIMIT_OFFSET		16
#घोषणा AC_PARAM_ECW_MAX_OFFSET			12
#घोषणा AC_PARAM_ECW_MIN_OFFSET			8
#घोषणा AC_PARAM_AIFS_OFFSET			0

/* ACMHWCTRL */
#घोषणा	ACMHW_HWEN				BIT(0)
#घोषणा	ACMHW_BEQEN				BIT(1)
#घोषणा	ACMHW_VIQEN				BIT(2)
#घोषणा	ACMHW_VOQEN				BIT(3)

/* ----------------------------------------------------- */
/*	0x0600h ~ 0x07FFh	WMAC Configuration */
/* ----------------------------------------------------- */

/* TCR */
#घोषणा TSFRST					BIT(0)
#घोषणा DIS_GCLK				BIT(1)
#घोषणा PAD_SEL					BIT(2)
#घोषणा PWR_ST					BIT(6)
#घोषणा PWRBIT_OW_EN				BIT(7)
#घोषणा ACRC					BIT(8)
#घोषणा CFENDFORM				BIT(9)
#घोषणा ICV					BIT(10)

/* SECCFG */
#घोषणा	SCR_TXUSEDK				BIT(0)
#घोषणा	SCR_RXUSEDK				BIT(1)
#घोषणा	SCR_TXENCENABLE				BIT(2)
#घोषणा	SCR_RXENCENABLE				BIT(3)
#घोषणा	SCR_SKBYA2				BIT(4)
#घोषणा	SCR_NOSKMC				BIT(5)
#घोषणा SCR_TXBCUSEDK				BIT(6)
#घोषणा SCR_RXBCUSEDK				BIT(7)

/* General definitions */
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER		255
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER_DUAL_MAC	127

#घोषणा POLLING_LLT_THRESHOLD			20
#घोषणा POLLING_READY_TIMEOUT_COUNT		1000

/* Min Spacing related settings. */
#घोषणा	MAX_MSS_DENSITY_2T			0x13
#घोषणा	MAX_MSS_DENSITY_1T			0x0A


/* BB-PHY रेजिस्टर PMAC 0x100 PHY 0x800 - 0xEFF */
/* 1. PMAC duplicate रेजिस्टर due to connection: */
/*    RF_Mode, TRxRN, NumOf L-STF */
/* 2. 0x800/0x900/0xA00/0xC00/0xD00/0xE00 */
/* 3. RF रेजिस्टर 0x00-2E */
/* 4. Bit Mask क्रम BB/RF रेजिस्टर */
/* 5. Other defपूर्णांकion क्रम BB/RF R/W */

/* 3. Page8(0x800) */
#घोषणा	RFPGA0_RFMOD				0x800

#घोषणा	RFPGA0_TXINFO				0x804
#घोषणा	RFPGA0_PSDFUNCTION			0x808

#घोषणा	RFPGA0_TXGAINSTAGE			0x80c

#घोषणा	RFPGA0_RFTIMING1			0x810
#घोषणा	RFPGA0_RFTIMING2			0x814

#घोषणा	RFPGA0_XA_HSSIPARAMETER1		0x820
#घोषणा	RFPGA0_XA_HSSIPARAMETER2		0x824
#घोषणा	RFPGA0_XB_HSSIPARAMETER1		0x828
#घोषणा	RFPGA0_XB_HSSIPARAMETER2		0x82c

#घोषणा	RFPGA0_XA_LSSIPARAMETER			0x840
#घोषणा	RFPGA0_XB_LSSIPARAMETER			0x844

#घोषणा	RFPGA0_RFWAKEUPPARAMETER		0x850
#घोषणा	RFPGA0_RFSLEEPUPPARAMETER		0x854

#घोषणा	RFPGA0_XAB_SWITCHCONTROL		0x858
#घोषणा	RFPGA0_XCD_SWITCHCONTROL		0x85c

#घोषणा	RFPGA0_XA_RFINTERFACEOE			0x860
#घोषणा	RFPGA0_XB_RFINTERFACEOE			0x864

#घोषणा	RFPGA0_XAB_RFINTERFACESW		0x870
#घोषणा	RFPGA0_XCD_RFINTERFACESW		0x874

#घोषणा	RFPGA0_XAB_RFPARAMETER			0x878
#घोषणा	RFPGA0_XCD_RFPARAMETER			0x87c

#घोषणा	RFPGA0_ANALOGPARAMETER1			0x880
#घोषणा	RFPGA0_ANALOGPARAMETER2			0x884
#घोषणा	RFPGA0_ANALOGPARAMETER3			0x888
#घोषणा	RFPGA0_ADDALLOCKEN			0x888
#घोषणा	RFPGA0_ANALOGPARAMETER4			0x88c

#घोषणा	RFPGA0_XA_LSSIREADBACK			0x8a0
#घोषणा	RFPGA0_XB_LSSIREADBACK			0x8a4
#घोषणा	RFPGA0_XC_LSSIREADBACK			0x8a8
#घोषणा	RFPGA0_XD_LSSIREADBACK			0x8ac

#घोषणा	RFPGA0_PSDREPORT			0x8b4
#घोषणा	TRANSCEIVERA_HSPI_READBACK		0x8b8
#घोषणा	TRANSCEIVERB_HSPI_READBACK		0x8bc
#घोषणा	RFPGA0_XAB_RFINTERFACERB		0x8e0
#घोषणा	RFPGA0_XCD_RFINTERFACERB		0x8e4

/* 4. Page9(0x900) */
#घोषणा	RFPGA1_RFMOD				0x900

#घोषणा	RFPGA1_TXBLOCK				0x904
#घोषणा	RFPGA1_DEBUGSELECT			0x908
#घोषणा	RFPGA1_TXINFO				0x90c

/* 5. PageA(0xA00)  */
#घोषणा	RCCK0_SYSTEM				0xa00

#घोषणा	RCCK0_AFESSTTING			0xa04
#घोषणा	RCCK0_CCA				0xa08

#घोषणा	RCCK0_RXAGC1				0xa0c
#घोषणा	RCCK0_RXAGC2				0xa10

#घोषणा	RCCK0_RXHP				0xa14

#घोषणा	RCCK0_DSPPARAMETER1			0xa18
#घोषणा	RCCK0_DSPPARAMETER2			0xa1c

#घोषणा	RCCK0_TXFILTER1				0xa20
#घोषणा	RCCK0_TXFILTER2				0xa24
#घोषणा	RCCK0_DEBUGPORT				0xa28
#घोषणा	RCCK0_FALSEALARMREPORT			0xa2c
#घोषणा	RCCK0_TRSSIREPORT			0xa50
#घोषणा	RCCK0_RXREPORT				0xa54
#घोषणा	RCCK0_FACOUNTERLOWER			0xa5c
#घोषणा	RCCK0_FACOUNTERUPPER			0xa58

/* 6. PageC(0xC00) */
#घोषणा	ROFDM0_LSTF				0xc00

#घोषणा	ROFDM0_TRXPATHENABLE			0xc04
#घोषणा	ROFDM0_TRMUXPAR				0xc08
#घोषणा	ROFDM0_TRSWISOLATION			0xc0c

#घोषणा	ROFDM0_XARXAFE				0xc10
#घोषणा	ROFDM0_XARXIQIMBALANCE			0xc14
#घोषणा	ROFDM0_XBRXAFE				0xc18
#घोषणा	ROFDM0_XBRXIQIMBALANCE			0xc1c
#घोषणा	ROFDM0_XCRXAFE				0xc20
#घोषणा	ROFDM0_XCRXIQIMBALANCE			0xc24
#घोषणा	ROFDM0_XDRXAFE				0xc28
#घोषणा	ROFDM0_XDRXIQIMBALANCE			0xc2c

#घोषणा	ROFDM0_RXDETECTOR1			0xc30
#घोषणा	ROFDM0_RXDETECTOR2			0xc34
#घोषणा	ROFDM0_RXDETECTOR3			0xc38
#घोषणा	ROFDM0_RXDETECTOR4			0xc3c

#घोषणा	ROFDM0_RXDSP				0xc40
#घोषणा	ROFDM0_CFOANDDAGC			0xc44
#घोषणा	ROFDM0_CCADROPTHRESHOLD			0xc48
#घोषणा	ROFDM0_ECCATHRESHOLD			0xc4c

#घोषणा	ROFDM0_XAAGCCORE1			0xc50
#घोषणा	ROFDM0_XAAGCCORE2			0xc54
#घोषणा	ROFDM0_XBAGCCORE1			0xc58
#घोषणा	ROFDM0_XBAGCCORE2			0xc5c
#घोषणा	ROFDM0_XCAGCCORE1			0xc60
#घोषणा	ROFDM0_XCAGCCORE2			0xc64
#घोषणा	ROFDM0_XDAGCCORE1			0xc68
#घोषणा	ROFDM0_XDAGCCORE2			0xc6c

#घोषणा	ROFDM0_AGCPARAMETER1			0xc70
#घोषणा	ROFDM0_AGCPARAMETER2			0xc74
#घोषणा	ROFDM0_AGCRSSITABLE			0xc78
#घोषणा	ROFDM0_HTSTFAGC				0xc7c

#घोषणा	ROFDM0_XATXIQIMBALANCE			0xc80
#घोषणा	ROFDM0_XATXAFE				0xc84
#घोषणा	ROFDM0_XBTXIQIMBALANCE			0xc88
#घोषणा	ROFDM0_XBTXAFE				0xc8c
#घोषणा	ROFDM0_XCTXIQIMBALANCE			0xc90
#घोषणा	ROFDM0_XCTXAFE				0xc94
#घोषणा	ROFDM0_XDTXIQIMBALANCE			0xc98
#घोषणा	ROFDM0_XDTXAFE				0xc9c

#घोषणा	ROFDM0_RXHPPARAMETER			0xce0
#घोषणा	ROFDM0_TXPSEUDONOISEWGT			0xce4
#घोषणा	ROFDM0_FRAMESYNC			0xcf0
#घोषणा	ROFDM0_DFSREPORT			0xcf4
#घोषणा	ROFDM0_TXCOEFF1				0xca4
#घोषणा	ROFDM0_TXCOEFF2				0xca8
#घोषणा	ROFDM0_TXCOEFF3				0xcac
#घोषणा	ROFDM0_TXCOEFF4				0xcb0
#घोषणा	ROFDM0_TXCOEFF5				0xcb4
#घोषणा	ROFDM0_TXCOEFF6				0xcb8

/* 7. PageD(0xD00) */
#घोषणा	ROFDM1_LSTF				0xd00
#घोषणा	ROFDM1_TRXPATHENABLE			0xd04

#घोषणा	ROFDM1_CFO				0xd08
#घोषणा	ROFDM1_CSI1				0xd10
#घोषणा	ROFDM1_SBD				0xd14
#घोषणा	ROFDM1_CSI2				0xd18
#घोषणा	ROFDM1_CFOTRACKING			0xd2c
#घोषणा	ROFDM1_TRXMESAURE1			0xd34
#घोषणा	ROFDM1_INTFDET				0xd3c
#घोषणा	ROFDM1_PSEUDONOISESTATEAB		0xd50
#घोषणा	ROFDM1_PSEUDONOISESTATECD		0xd54
#घोषणा	ROFDM1_RXPSEUDONOISEWGT			0xd58

#घोषणा	ROFDM_PHYCOUNTER1			0xda0
#घोषणा	ROFDM_PHYCOUNTER2			0xda4
#घोषणा	ROFDM_PHYCOUNTER3			0xda8

#घोषणा	ROFDM_SHORTCFOAB			0xdac
#घोषणा	ROFDM_SHORTCFOCD			0xdb0
#घोषणा	ROFDM_LONGCFOAB				0xdb4
#घोषणा	ROFDM_LONGCFOCD				0xdb8
#घोषणा	ROFDM_TAILCFOAB				0xdbc
#घोषणा	ROFDM_TAILCFOCD				0xdc0
#घोषणा	ROFDM_PWMEASURE1			0xdc4
#घोषणा	ROFDM_PWMEASURE2			0xdc8
#घोषणा	ROFDM_BWREPORT				0xdcc
#घोषणा	ROFDM_AGCREPORT				0xdd0
#घोषणा	ROFDM_RXSNR				0xdd4
#घोषणा	ROFDM_RXEVMCSI				0xdd8
#घोषणा	ROFDM_SIGREPORT				0xddc

/* 8. PageE(0xE00) */
#घोषणा	RTXAGC_A_RATE18_06			0xe00
#घोषणा	RTXAGC_A_RATE54_24			0xe04
#घोषणा	RTXAGC_A_CCK1_MCS32			0xe08
#घोषणा	RTXAGC_A_MCS03_MCS00			0xe10
#घोषणा	RTXAGC_A_MCS07_MCS04			0xe14
#घोषणा	RTXAGC_A_MCS11_MCS08			0xe18
#घोषणा	RTXAGC_A_MCS15_MCS12			0xe1c

#घोषणा	RTXAGC_B_RATE18_06			0x830
#घोषणा	RTXAGC_B_RATE54_24			0x834
#घोषणा	RTXAGC_B_CCK1_55_MCS32			0x838
#घोषणा	RTXAGC_B_MCS03_MCS00			0x83c
#घोषणा	RTXAGC_B_MCS07_MCS04			0x848
#घोषणा	RTXAGC_B_MCS11_MCS08			0x84c
#घोषणा	RTXAGC_B_MCS15_MCS12			0x868
#घोषणा	RTXAGC_B_CCK11_A_CCK2_11		0x86c

/* RL6052 Register definition */
#घोषणा	RF_AC					0x00

#घोषणा	RF_IQADJ_G1				0x01
#घोषणा	RF_IQADJ_G2				0x02
#घोषणा	RF_POW_TRSW				0x05

#घोषणा	RF_GAIN_RX				0x06
#घोषणा	RF_GAIN_TX				0x07

#घोषणा	RF_TXM_IDAC				0x08
#घोषणा	RF_BS_IQGEN				0x0F

#घोषणा	RF_MODE1				0x10
#घोषणा	RF_MODE2				0x11

#घोषणा	RF_RX_AGC_HP				0x12
#घोषणा	RF_TX_AGC				0x13
#घोषणा	RF_BIAS					0x14
#घोषणा	RF_IPA					0x15
#घोषणा	RF_POW_ABILITY				0x17
#घोषणा	RF_MODE_AG				0x18
#घोषणा	rfchannel				0x18
#घोषणा	RF_CHNLBW				0x18
#घोषणा	RF_TOP					0x19

#घोषणा	RF_RX_G1				0x1A
#घोषणा	RF_RX_G2				0x1B

#घोषणा	RF_RX_BB2				0x1C
#घोषणा	RF_RX_BB1				0x1D

#घोषणा	RF_RCK1					0x1E
#घोषणा	RF_RCK2					0x1F

#घोषणा	RF_TX_G1				0x20
#घोषणा	RF_TX_G2				0x21
#घोषणा	RF_TX_G3				0x22

#घोषणा	RF_TX_BB1				0x23

#घोषणा	RF_T_METER				0x42

#घोषणा	RF_SYN_G1				0x25
#घोषणा	RF_SYN_G2				0x26
#घोषणा	RF_SYN_G3				0x27
#घोषणा	RF_SYN_G4				0x28
#घोषणा	RF_SYN_G5				0x29
#घोषणा	RF_SYN_G6				0x2A
#घोषणा	RF_SYN_G7				0x2B
#घोषणा	RF_SYN_G8				0x2C

#घोषणा	RF_RCK_OS				0x30

#घोषणा	RF_TXPA_G1				0x31
#घोषणा	RF_TXPA_G2				0x32
#घोषणा	RF_TXPA_G3				0x33

/* Bit Mask */

/* 2. Page8(0x800) */
#घोषणा	BRFMOD					0x1
#घोषणा	BCCKTXSC				0x30
#घोषणा	BCCKEN					0x1000000
#घोषणा	BOFDMEN					0x2000000

#घोषणा	B3WIREDATALENGTH			0x800
#घोषणा	B3WIREADDRESSLENGTH			0x400

#घोषणा	BRFSI_RFENV				0x10

#घोषणा	BLSSIREADADDRESS			0x7f800000
#घोषणा	BLSSIREADEDGE				0x80000000
#घोषणा	BLSSIREADBACKDATA			0xfffff
/* 4. PageA(0xA00) */
#घोषणा BCCKSIDEBAND				0x10

/* Other Definition */
#घोषणा	BBYTE0					0x1
#घोषणा	BBYTE1					0x2
#घोषणा	BBYTE2					0x4
#घोषणा	BBYTE3					0x8
#घोषणा	BWORD0					0x3
#घोषणा	BWORD1					0xc
#घोषणा	BDWORD					0xf

#पूर्ण_अगर
