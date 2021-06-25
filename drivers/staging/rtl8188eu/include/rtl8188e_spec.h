<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 *******************************************************************************/
#अगर_अघोषित __RTL8188E_SPEC_H__
#घोषणा __RTL8188E_SPEC_H__

/*        8192C Register offset definition */

#घोषणा		HAL_PS_TIMER_INT_DELAY	50	/*   50 microseconds */
#घोषणा		HAL_92C_NAV_UPPER_UNIT	128	/*  micro-second */

#घोषणा MAC_ADDR_LEN			6
/*  8188E PKT_BUFF_ACCESS_CTRL value */
#घोषणा TXPKT_BUF_SELECT		0x69
#घोषणा RXPKT_BUF_SELECT		0xA5
#घोषणा DISABLE_TRXPKT_BUF_ACCESS	0x0

/*	0x0000h ~ 0x00FFh	System Configuration */
#घोषणा REG_SYS_ISO_CTRL		0x0000
#घोषणा REG_SYS_FUNC_EN			0x0002
#घोषणा REG_APS_FSMCO			0x0004
#घोषणा REG_SYS_CLKR			0x0008
#घोषणा REG_9346CR			0x000A
#घोषणा REG_EE_VPD			0x000C
#घोषणा REG_AFE_MISC			0x0010
#घोषणा REG_SPS0_CTRL			0x0011
#घोषणा REG_SPS_OCP_CFG			0x0018
#घोषणा REG_RSV_CTRL			0x001C
#घोषणा REG_RF_CTRL			0x001F
#घोषणा REG_LDOA15_CTRL			0x0020
#घोषणा REG_LDOV12D_CTRL		0x0021
#घोषणा REG_LDOHCI12_CTRL		0x0022
#घोषणा REG_LPLDO_CTRL			0x0023
#घोषणा REG_AFE_XTAL_CTRL		0x0024
#घोषणा REG_AFE_PLL_CTRL		0x0028
#घोषणा REG_APE_PLL_CTRL_EXT		0x002c
#घोषणा REG_EFUSE_CTRL			0x0030
#घोषणा REG_EFUSE_TEST			0x0034
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
#घोषणा REG_HSIMR			0x0058
#घोषणा REG_HSISR			0x005c
#घोषणा REG_GPIO_PIN_CTRL_2		0x0060 /*  RTL8723 WIFI/BT/GPS
						* Multi-Function GPIO Pin Control.
						*/
#घोषणा REG_GPIO_IO_SEL_2		0x0062 /*  RTL8723 WIFI/BT/GPS
						* Multi-Function GPIO Select.
						*/
#घोषणा REG_BB_PAD_CTRL			0x0064
#घोषणा REG_MULTI_FUNC_CTRL		0x0068 /*  RTL8723 WIFI/BT/GPS
						* Multi-Function control source.
						*/
#घोषणा REG_GPIO_OUTPUT			0x006c
#घोषणा REG_AFE_XTAL_CTRL_EXT		0x0078 /* RTL8188E */
#घोषणा REG_XCK_OUT_CTRL		0x007c /* RTL8188E */
#घोषणा REG_MCUFWDL			0x0080
#घोषणा REG_WOL_EVENT			0x0081 /* RTL8188E */
#घोषणा REG_MCUTSTCFG			0x0084
#घोषणा REG_HMEBOX_E0			0x0088
#घोषणा REG_HMEBOX_E1			0x008A
#घोषणा REG_HMEBOX_E2			0x008C
#घोषणा REG_HMEBOX_E3			0x008E
#घोषणा REG_HMEBOX_EXT_0		0x01F0
#घोषणा REG_HMEBOX_EXT_1		0x01F4
#घोषणा REG_HMEBOX_EXT_2		0x01F8
#घोषणा REG_HMEBOX_EXT_3		0x01FC
#घोषणा REG_HIMR_88E			0x00B0
#घोषणा REG_HISR_88E			0x00B4
#घोषणा REG_HIMRE_88E			0x00B8
#घोषणा REG_HISRE_88E			0x00BC
#घोषणा REG_EFUSE_ACCESS		0x00CF	/*  Efuse access protection
						 * क्रम RTL8723
						 */
#घोषणा REG_BIST_SCAN			0x00D0
#घोषणा REG_BIST_RPT			0x00D4
#घोषणा REG_BIST_ROM_RPT		0x00D8
#घोषणा REG_USB_SIE_INTF		0x00E0
#घोषणा REG_PCIE_MIO_INTF		0x00E4
#घोषणा REG_PCIE_MIO_INTD		0x00E8
#घोषणा REG_HPON_FSM			0x00EC
#घोषणा REG_SYS_CFG			0x00F0
#घोषणा REG_GPIO_OUTSTS			0x00F4	/*  For RTL8723 only. */
#घोषणा REG_TYPE_ID			0x00FC

#घोषणा REG_MAC_PHY_CTRL_NORMAL		0x00f8

/*	0x0100h ~ 0x01FFh	MACTOP General Configuration */
#घोषणा REG_CR				0x0100
#घोषणा REG_PBP				0x0104
#घोषणा REG_PKT_BUFF_ACCESS_CTRL	0x0106
#घोषणा REG_TRXDMA_CTRL			0x010C
#घोषणा REG_TRXFF_BNDY			0x0114
#घोषणा REG_TRXFF_STATUS		0x0118
#घोषणा REG_RXFF_PTR			0x011C
/* define REG_HIMR			0x0120 */
/* define REG_HISR			0x0124 */
#घोषणा REG_HIMRE			0x0128
#घोषणा REG_HISRE			0x012C
#घोषणा REG_CPWM			0x012F
#घोषणा REG_FWIMR			0x0130
#घोषणा REG_FTIMR			0x0138
#घोषणा REG_FWISR			0x0134
#घोषणा REG_PKTBUF_DBG_CTRL		0x0140
#घोषणा REG_PKTBUF_DBG_ADDR		(REG_PKTBUF_DBG_CTRL)
#घोषणा REG_RXPKTBUF_DBG		(REG_PKTBUF_DBG_CTRL + 2)
#घोषणा REG_TXPKTBUF_DBG		(REG_PKTBUF_DBG_CTRL + 3)
#घोषणा REG_RXPKTBUF_CTRL		(REG_PKTBUF_DBG_CTRL + 2)
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
#घोषणा REG_32K_CTRL			0x0194 /* RTL8188E */
#घोषणा REG_C2HEVT_MSG_NORMAL		0x01A0
#घोषणा REG_C2HEVT_CLEAR		0x01AF
#घोषणा REG_MCUTST_1			0x01c0
#घोषणा REG_FMETHR			0x01C8
#घोषणा REG_HMETFR			0x01CC
#घोषणा REG_HMEBOX_0			0x01D0
#घोषणा REG_HMEBOX_1			0x01D4
#घोषणा REG_HMEBOX_2			0x01D8
#घोषणा REG_HMEBOX_3			0x01DC

#घोषणा REG_LLT_INIT			0x01E0

/*	0x0200h ~ 0x027Fh	TXDMA Configuration */
#घोषणा REG_RQPN			0x0200
#घोषणा REG_FIFOPAGE			0x0204
#घोषणा REG_TDECTRL			0x0208
#घोषणा REG_TXDMA_OFFSET_CHK		0x020C
#घोषणा REG_TXDMA_STATUS		0x0210
#घोषणा REG_RQPN_NPQ			0x0214

/*	0x0280h ~ 0x02FFh	RXDMA Configuration */
#घोषणा		REG_RXDMA_AGG_PG_TH	0x0280
#घोषणा	REG_RXPKT_NUM			0x0284
#घोषणा		REG_RXDMA_STATUS	0x0288

/*	0x0300h ~ 0x03FFh	PCIe */
#घोषणा	REG_PCIE_CTRL_REG		0x0300
#घोषणा	REG_INT_MIG			0x0304	/*  Interrupt Migration */
#घोषणा	REG_BCNQ_DESA			0x0308	/*  TX Beacon Descr Address */
#घोषणा	REG_HQ_DESA			0x0310	/*  TX High Queue Descr Addr */
#घोषणा	REG_MGQ_DESA			0x0318	/*  TX Manage Queue Descr Addr*/
#घोषणा	REG_VOQ_DESA			0x0320	/*  TX VO Queue Descr Addr */
#घोषणा	REG_VIQ_DESA			0x0328	/*  TX VI Queue Descr Addr */
#घोषणा	REG_BEQ_DESA			0x0330	/*  TX BE Queue Descr Addr */
#घोषणा	REG_BKQ_DESA			0x0338	/*  TX BK Queue Descr Addr */
#घोषणा	REG_RX_DESA			0x0340	/*  RX Queue Descr Addr */
#घोषणा	REG_MDIO			0x0354	/*  MDIO क्रम Access PCIE PHY */
#घोषणा	REG_DBG_SEL			0x0360	/*  Debug Selection Register */
#घोषणा	REG_PCIE_HRPWM			0x0361	/* PCIe RPWM */
#घोषणा	REG_PCIE_HCPWM			0x0363	/* PCIe CPWM */
#घोषणा	REG_WATCH_DOG			0x0368

/*  RTL8723 series ------------------------------ */
#घोषणा	REG_PCIE_HISR			0x03A0

/*  spec version 11 */
/*	0x0400h ~ 0x047Fh	Protocol Configuration */
#घोषणा REG_VOQ_INFORMATION		0x0400
#घोषणा REG_VIQ_INFORMATION		0x0404
#घोषणा REG_BEQ_INFORMATION		0x0408
#घोषणा REG_BKQ_INFORMATION		0x040C
#घोषणा REG_MGQ_INFORMATION		0x0410
#घोषणा REG_HGQ_INFORMATION		0x0414
#घोषणा REG_BCNQ_INFORMATION		0x0418
#घोषणा REG_TXPKT_EMPTY			0x041A

#घोषणा REG_CPU_MGQ_INFORMATION		0x041C
#घोषणा REG_FWHW_TXQ_CTRL		0x0420
#घोषणा REG_HWSEQ_CTRL			0x0423
#घोषणा REG_TXPKTBUF_BCNQ_BDNY		0x0424
#घोषणा REG_TXPKTBUF_MGQ_BDNY		0x0425
#घोषणा REG_LIFETIME_EN			0x0426
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
/* define REG_INIDATA_RATE_SEL		0x0484 */
#घोषणा REG_POWER_STATUS		0x04A4
#घोषणा REG_POWER_STAGE1		0x04B4
#घोषणा REG_POWER_STAGE2		0x04B8
#घोषणा REG_PKT_VO_VI_LIFE_TIME		0x04C0
#घोषणा REG_PKT_BE_BK_LIFE_TIME		0x04C2
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
#घोषणा REG_TX_RPT_CTRL			0x04EC
#घोषणा REG_TX_RPT_TIME			0x04F0	/*  2 byte */
#घोषणा REG_DUMMY			0x04FC

/*	0x0500h ~ 0x05FFh	EDCA Configuration */
#घोषणा REG_EDCA_VO_PARAM		0x0500
#घोषणा REG_EDCA_VI_PARAM		0x0504
#घोषणा REG_EDCA_BE_PARAM		0x0508
#घोषणा REG_EDCA_BK_PARAM		0x050C
#घोषणा REG_BCNTCFG			0x0510
#घोषणा REG_PIFS			0x0512
#घोषणा REG_RDG_PIFS			0x0513
#घोषणा REG_SIFS_CTX			0x0514
#घोषणा REG_SIFS_TRX			0x0516
#घोषणा REG_TSFTR_SYN_OFFSET		0x0518
#घोषणा REG_AGGR_BREAK_TIME		0x051A
#घोषणा REG_SLOT			0x051B
#घोषणा REG_TX_PTCL_CTRL		0x0520
#घोषणा REG_TXPAUSE			0x0522
#घोषणा REG_DIS_TXREQ_CLR		0x0523
#घोषणा REG_RD_CTRL			0x0524
/*  Format क्रम offset 540h-542h:
 *	[3:0]:   TBTT prohibit setup in unit of 32us. The समय क्रम HW getting
 *		 beacon content beक्रमe TBTT.
 *
 *	[7:4]:   Reserved.
 *	[19:8]:  TBTT prohibit hold in unit of 32us. The समय क्रम HW holding
 *		 to send the beacon packet.
 *
 *	[23:20]: Reserved
 *  Description:
 *	              |
 *      |<--Setup--|--Hold------------>|
 *	--------------|----------------------
 *                 |
 *                TBTT
 *  Note: We cannot update beacon content to HW or send any AC packets during
 *	  the समय between Setup and Hold.
 */
#घोषणा REG_TBTT_PROHIBIT		0x0540
#घोषणा REG_RD_NAV_NXT			0x0544
#घोषणा REG_NAV_PROT_LEN		0x0546
#घोषणा REG_BCN_CTRL			0x0550
#घोषणा REG_BCN_CTRL_1			0x0551
#घोषणा REG_MBID_NUM			0x0552
#घोषणा REG_DUAL_TSF_RST		0x0553
#घोषणा REG_BCN_INTERVAL		0x0554
#घोषणा REG_DRVERLYINT			0x0558
#घोषणा REG_BCNDMATIM			0x0559
#घोषणा REG_ATIMWND			0x055A
#घोषणा REG_BCN_MAX_ERR			0x055D
#घोषणा REG_RXTSF_OFFSET_CCK		0x055E
#घोषणा REG_RXTSF_OFFSET_OFDM		0x055F
#घोषणा REG_TSFTR			0x0560
#घोषणा REG_TSFTR1			0x0568
#घोषणा REG_ATIMWND_1			0x0570
#घोषणा REG_PSTIMER			0x0580
#घोषणा REG_TIMER0			0x0584
#घोषणा REG_TIMER1			0x0588
#घोषणा REG_ACMHWCTRL			0x05C0

/* define REG_FW_TSF_SYNC_CNT		0x04A0 */
#घोषणा REG_FW_RESET_TSF_CNT_1		0x05FC
#घोषणा REG_FW_RESET_TSF_CNT_0		0x05FD
#घोषणा REG_FW_BCN_DIS_CNT		0x05FE

/*	0x0600h ~ 0x07FFh	WMAC Configuration */
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

/*  20100719 Joseph: Hardware रेजिस्टर definition change. (HW datasheet v54) */
/*  [15:8]SIFS_R2T_OFDM, [7:0]SIFS_R2T_CCK */
#घोषणा REG_R2T_SIFS			0x063C
/*  [15:8]SIFS_T2T_OFDM, [7:0]SIFS_T2T_CCK */
#घोषणा REG_T2T_SIFS			0x063E
#घोषणा REG_ACKTO			0x0640
#घोषणा REG_CTS2TO			0x0641
#घोषणा REG_EIFS			0x0642

/* RXERR_RPT */
#घोषणा RXERR_TYPE_OFDM_PPDU		0
#घोषणा RXERR_TYPE_OFDM_false_ALARM	1
#घोषणा RXERR_TYPE_OFDM_MPDU_OK		2
#घोषणा RXERR_TYPE_OFDM_MPDU_FAIL	3
#घोषणा RXERR_TYPE_CCK_PPDU		4
#घोषणा RXERR_TYPE_CCK_false_ALARM	5
#घोषणा RXERR_TYPE_CCK_MPDU_OK		6
#घोषणा RXERR_TYPE_CCK_MPDU_FAIL	7
#घोषणा RXERR_TYPE_HT_PPDU		8
#घोषणा RXERR_TYPE_HT_false_ALARM	9
#घोषणा RXERR_TYPE_HT_MPDU_TOTAL	10
#घोषणा RXERR_TYPE_HT_MPDU_OK		11
#घोषणा RXERR_TYPE_HT_MPDU_FAIL		12
#घोषणा RXERR_TYPE_RX_FULL_DROP		15

#घोषणा RXERR_COUNTER_MASK		0xFFFFF
#घोषणा RXERR_RPT_RST			BIT(27)
#घोषणा _RXERR_RPT_SEL(type)		((type) << 28)

/*  Note:
 *	The NAV upper value is very important to WiFi 11n 5.2.3 NAV test.
 *	The शेष value is always too small, but the WiFi TestPlan test
 *	by 25,000 microseconds of NAV through sending CTS in the air.
 *	We must update this value greater than 25,000 microseconds to pass
 *	the item. The offset of NAV_UPPER in 8192C Spec is incorrect, and
 *	the offset should be 0x0652.
 */
#घोषणा REG_NAV_UPPER			0x0652	/*  unit of 128 */

/* WMA, BA, CCX */
/* define REG_NAV_CTRL			0x0650 */
#घोषणा REG_BACAMCMD			0x0654
#घोषणा REG_BACAMCONTENT		0x0658
#घोषणा REG_LBDLY			0x0660
#घोषणा REG_FWDLY			0x0661
#घोषणा REG_RXERR_RPT			0x0664
#घोषणा REG_WMAC_TRXPTCL_CTL		0x0668

/*  Security */
#घोषणा REG_CAMCMD			0x0670
#घोषणा REG_CAMWRITE			0x0674
#घोषणा REG_CAMREAD			0x0678
#घोषणा REG_CAMDBG			0x067C
#घोषणा REG_SECCFG			0x0680

/*  Power */
#घोषणा REG_WOW_CTRL			0x0690
#घोषणा REG_PS_RX_INFO			0x0692
#घोषणा REG_UAPSD_TID			0x0693
#घोषणा REG_WKFMCAM_CMD			0x0698
#घोषणा REG_WKFMCAM_NUM_88E		0x698
#घोषणा REG_RXFLTMAP0			0x06A0
#घोषणा REG_RXFLTMAP1			0x06A2
#घोषणा REG_RXFLTMAP2			0x06A4
#घोषणा REG_BCN_PSR_RPT			0x06A8
#घोषणा REG_BT_COEX_TABLE		0x06C0

/*  Hardware Port 2 */
#घोषणा REG_MACID1			0x0700
#घोषणा REG_BSSID1			0x0708

/*	0xFE00h ~ 0xFE55h	USB Configuration */
#घोषणा REG_USB_INFO			0xFE17
#घोषणा REG_USB_SPECIAL_OPTION		0xFE55
#घोषणा REG_USB_DMA_AGG_TO		0xFE5B
#घोषणा REG_USB_AGG_TO			0xFE5C
#घोषणा REG_USB_AGG_TH			0xFE5D

/*  For normal chip */
#घोषणा REG_NORMAL_SIE_VID		0xFE60		/*  0xFE60~0xFE61 */
#घोषणा REG_NORMAL_SIE_PID		0xFE62		/*  0xFE62~0xFE63 */
#घोषणा REG_NORMAL_SIE_OPTIONAL		0xFE64
#घोषणा REG_NORMAL_SIE_EP		0xFE65		/*  0xFE65~0xFE67 */
#घोषणा REG_NORMAL_SIE_PHY		0xFE68		/*  0xFE68~0xFE6B */
#घोषणा REG_NORMAL_SIE_OPTIONAL2	0xFE6C
#घोषणा REG_NORMAL_SIE_GPS_EP		0xFE6D	/*  0xFE6D, क्रम RTL8723 only. */
#घोषणा REG_NORMAL_SIE_MAC_ADDR		0xFE70		/*  0xFE70~0xFE75 */
#घोषणा REG_NORMAL_SIE_STRING		0xFE80		/*  0xFE80~0xFEDF */

/*  TODO: use these definition when using REG_xxx naming rule. */
/*  NOTE: DO NOT Remove these definition. Use later. */

#घोषणा	EFUSE_CTRL			REG_EFUSE_CTRL	/*  E-Fuse Control. */
#घोषणा	EFUSE_TEST			REG_EFUSE_TEST	/*  E-Fuse Test. */
#घोषणा	MSR				(REG_CR + 2)	/*  Media Status reg */
#घोषणा	ISR				REG_HISR_88E
/*  Timing Sync Function Timer Register. */
#घोषणा	TSFR				REG_TSFTR

#घोषणा		PBP			REG_PBP

/*  Redअगरine MACID रेजिस्टर, to compatible prior ICs. */
/*  MAC ID Register, Offset 0x0050-0x0053 */
#घोषणा	IDR0				REG_MACID
/*  MAC ID Register, Offset 0x0054-0x0055 */
#घोषणा	IDR4				(REG_MACID + 4)

/*  9. Security Control Registers	(Offset: ) */
/* IN 8190 Data Sheet is called CAMcmd */
#घोषणा	RWCAM				REG_CAMCMD
/*  Software ग_लिखो CAM input content */
#घोषणा	WCAMI				REG_CAMWRITE
/*  Software पढ़ो/ग_लिखो CAM config */
#घोषणा	RCAMO				REG_CAMREAD
#घोषणा	CAMDBG				REG_CAMDBG
/* Security Configuration Register */
#घोषणा	SECR				REG_SECCFG

/*  Unused रेजिस्टर */
#घोषणा	UnusedRegister			0x1BF
#घोषणा	DCAM				UnusedRegister
#घोषणा	PSR				UnusedRegister
#घोषणा	BBAddr				UnusedRegister
#घोषणा	PhyDataR			UnusedRegister

/*  Min Spacing related settings. */
#घोषणा	MAX_MSS_DENSITY_2T		0x13
#घोषणा	MAX_MSS_DENSITY_1T		0x0A

/*  EEPROM enable when set 1 */
#घोषणा	CmdEEPROM_En			BIT(5)
/*  System EEPROM select, 0: boot from E-FUSE, 1: The EEPROM used is 9346 */
#घोषणा	CmdEERPOMSEL			BIT(4)
#घोषणा	Cmd9346CR_9356SEL		BIT(4)

/*        8192C GPIO MUX Configuration Register (offset 0x40, 4 byte) */
#घोषणा	GPIOSEL_GPIO			0
#घोषणा	GPIOSEL_ENBT			BIT(5)

/*        8192C GPIO PIN Control Register (offset 0x44, 4 byte) */
/*  GPIO pins input value */
#घोषणा	GPIO_IN				REG_GPIO_PIN_CTRL
/*  GPIO pins output value */
#घोषणा	GPIO_OUT			(REG_GPIO_PIN_CTRL + 1)
/*  GPIO pins output enable when a bit is set to "1"; otherwise,
 *  input is configured.
 */
#घोषणा	GPIO_IO_SEL			(REG_GPIO_PIN_CTRL + 2)
#घोषणा	GPIO_MOD			(REG_GPIO_PIN_CTRL + 3)

/* 8723/8188E Host System Interrupt Mask Register (offset 0x58, 32 byte) */
#घोषणा	HSIMR_GPIO12_0_INT_EN		BIT(0)
#घोषणा	HSIMR_SPS_OCP_INT_EN		BIT(5)
#घोषणा	HSIMR_RON_INT_EN		BIT(6)
#घोषणा	HSIMR_PDN_INT_EN		BIT(7)
#घोषणा	HSIMR_GPIO9_INT_EN		BIT(25)

/* 8723/8188E Host System Interrupt Status Register (offset 0x5C, 32 byte) */
#घोषणा	HSISR_GPIO12_0_INT		BIT(0)
#घोषणा	HSISR_SPS_OCP_INT		BIT(5)
#घोषणा	HSISR_RON_INT_EN		BIT(6)
#घोषणा	HSISR_PDNINT			BIT(7)
#घोषणा	HSISR_GPIO9_INT			BIT(25)

/*   8192C (MSR) Media Status Register	(Offset 0x4C, 8 bits) */
/*
 * Network Type
 * 00: No link
 * 01: Link in ad hoc network
 * 10: Link in infraकाष्ठाure network
 * 11: AP mode
 * Default: 00b.
 */
#घोषणा	MSR_NOLINK			0x00
#घोषणा	MSR_ADHOC			0x01
#घोषणा	MSR_INFRA			0x02
#घोषणा	MSR_AP				0x03

/*   88EU (MSR) Media Status Register	(Offset 0x4C, 8 bits) */
#घोषणा	USB_INTR_CONTENT_C2H_OFFSET	0
#घोषणा	USB_INTR_CONTENT_CPWM1_OFFSET	16
#घोषणा	USB_INTR_CONTENT_CPWM2_OFFSET	20
#घोषणा	USB_INTR_CONTENT_HISR_OFFSET	48
#घोषणा	USB_INTR_CONTENT_HISRE_OFFSET	52

/*  88E Driver Initialization Offload REG_FDHM0(Offset 0x88, 8 bits) */
/* IOL config क्रम REG_FDHM0(Reg0x88) */
#घोषणा CMD_INIT_LLT			BIT(0)
#घोषणा CMD_READ_EFUSE_MAP		BIT(1)
#घोषणा CMD_EFUSE_PATCH			BIT(2)
#घोषणा CMD_IOCONFIG			BIT(3)
#घोषणा CMD_INIT_LLT_ERR		BIT(4)
#घोषणा CMD_READ_EFUSE_MAP_ERR		BIT(5)
#घोषणा CMD_EFUSE_PATCH_ERR		BIT(6)
#घोषणा CMD_IOCONFIG_ERR		BIT(7)

/*  6. Adaptive Control Registers  (Offset: 0x0160 - 0x01CF) */
/*  8192C Response Rate Set Register	(offset 0x181, 24bits) */
#घोषणा	RRSR_1M				BIT(0)
#घोषणा	RRSR_2M				BIT(1)
#घोषणा	RRSR_5_5M			BIT(2)
#घोषणा	RRSR_11M			BIT(3)
#घोषणा	RRSR_6M				BIT(4)
#घोषणा	RRSR_9M				BIT(5)
#घोषणा	RRSR_12M			BIT(6)
#घोषणा	RRSR_18M			BIT(7)
#घोषणा	RRSR_24M			BIT(8)
#घोषणा	RRSR_36M			BIT(9)
#घोषणा	RRSR_48M			BIT(10)
#घोषणा	RRSR_54M			BIT(11)
#घोषणा	RRSR_MCS0			BIT(12)
#घोषणा	RRSR_MCS1			BIT(13)
#घोषणा	RRSR_MCS2			BIT(14)
#घोषणा	RRSR_MCS3			BIT(15)
#घोषणा	RRSR_MCS4			BIT(16)
#घोषणा	RRSR_MCS5			BIT(17)
#घोषणा	RRSR_MCS6			BIT(18)
#घोषणा	RRSR_MCS7			BIT(19)

/*  8192C Response Rate Set Register	(offset 0x1BF, 8bits) */
/*  WOL bit inक्रमmation */
#घोषणा	HAL92C_WOL_PTK_UPDATE_EVENT	BIT(0)
#घोषणा	HAL92C_WOL_GTK_UPDATE_EVENT	BIT(1)

/*        8192C BW_OPMODE bits		(Offset 0x203, 8bit) */
#घोषणा	BW_OPMODE_20MHZ			BIT(2)
#घोषणा	BW_OPMODE_5G			BIT(1)

/*        8192C CAM Config Setting (offset 0x250, 1 byte) */
#घोषणा	CAM_VALID			BIT(15)
#घोषणा	CAM_NOTVALID			0x0000
#घोषणा	CAM_USEDK			BIT(5)

#घोषणा	CAM_CONTENT_COUNT		8

#घोषणा	CAM_NONE			0x0
#घोषणा	CAM_WEP40			0x01
#घोषणा	CAM_TKIP			0x02
#घोषणा	CAM_AES				0x04
#घोषणा	CAM_WEP104			0x05
#घोषणा	CAM_SMS4			0x6

#घोषणा	TOTAL_CAM_ENTRY			32
#घोषणा	HALF_CAM_ENTRY			16

#घोषणा	CAM_CONFIG_USEDK		true
#घोषणा	CAM_CONFIG_NO_USEDK		false

#घोषणा	CAM_WRITE			BIT(16)
#घोषणा	CAM_READ			0x00000000
#घोषणा	CAM_POLLINIG			BIT(31)

#घोषणा	SCR_UseDK			0x01
#घोषणा	SCR_TxSecEnable			0x02
#घोषणा	SCR_RxSecEnable			0x04

/*  10. Power Save Control Registers	 (Offset: 0x0260 - 0x02DF) */
#घोषणा	WOW_PMEN			BIT(0) /*  Power management Enable. */
#घोषणा	WOW_WOMEN			BIT(1) /*  WoW function on or off. */
#घोषणा	WOW_MAGIC			BIT(2) /*  Magic packet */
#घोषणा	WOW_UWF				BIT(3) /*  Unicast Wakeup frame. */

/*  12. Host Interrupt Status Registers	 (Offset: 0x0300 - 0x030F) */
/*        8188 IMR/ISR bits */
#घोषणा	IMR_DISABLED_88E		0x0
/*  IMR DW0(0x0060-0063) Bit 0-31 */
#घोषणा	IMR_TXCCK_88E			BIT(30)	/*  TXRPT पूर्णांकerrupt when CCX bit of the packet is set */
#घोषणा	IMR_PSTIMEOUT_88E		BIT(29)	/*  Power Save Time Out Interrupt */
#घोषणा	IMR_GTINT4_88E			BIT(28)	/*  When GTIMER4 expires, this bit is set to 1 */
#घोषणा	IMR_GTINT3_88E			BIT(27)	/*  When GTIMER3 expires, this bit is set to 1 */
#घोषणा	IMR_TBDER_88E			BIT(26)	/*  Transmit Beacon0 Error */
#घोषणा	IMR_TBDOK_88E			BIT(25)	/*  Transmit Beacon0 OK */
#घोषणा	IMR_TSF_BIT32_TOGGLE_88E	BIT(24)	/*  TSF Timer BIT32 toggle indication पूर्णांकerrupt */
#घोषणा	IMR_BCNDMAINT0_88E		BIT(20)	/*  Beacon DMA Interrupt 0 */
#घोषणा	IMR_BCNDERR0_88E		BIT(16)	/*  Beacon Queue DMA Error 0 */
#घोषणा	IMR_HSISR_IND_ON_INT_88E	BIT(15)	/*  HSISR Indicator (HSIMR & HSISR is true, this bit is set to 1) */
#घोषणा	IMR_BCNDMAINT_E_88E		BIT(14)	/*  Beacon DMA Interrupt Extension क्रम Win7 */
#घोषणा	IMR_ATIMEND_88E			BIT(12)	/*  CTWidnow End or ATIM Winकरोw End */
#घोषणा	IMR_HISR1_IND_INT_88E		BIT(11)	/*  HISR1 Indicator (HISR1 & HIMR1 is true, this bit is set to 1) */
#घोषणा	IMR_C2HCMD_88E			BIT(10)	/*  CPU to Host Command INT Status, Write 1 clear */
#घोषणा	IMR_CPWM2_88E			BIT(9)	/*  CPU घातer Mode exchange INT Status, Write 1 clear */
#घोषणा	IMR_CPWM_88E			BIT(8)	/*  CPU घातer Mode exchange INT Status, Write 1 clear */
#घोषणा	IMR_HIGHDOK_88E			BIT(7)	/*  High Queue DMA OK */
#घोषणा	IMR_MGNTDOK_88E			BIT(6)	/*  Management Queue DMA OK */
#घोषणा	IMR_BKDOK_88E			BIT(5)	/*  AC_BK DMA OK */
#घोषणा	IMR_BEDOK_88E			BIT(4)	/*  AC_BE DMA OK */
#घोषणा	IMR_VIDOK_88E			BIT(3)	/*  AC_VI DMA OK */
#घोषणा	IMR_VODOK_88E			BIT(2)	/*  AC_VO DMA OK */
#घोषणा	IMR_RDU_88E			BIT(1)	/*  Rx Descriptor Unavailable */
#घोषणा	IMR_ROK_88E			BIT(0)	/*  Receive DMA OK */

/*  IMR DW1(0x00B4-00B7) Bit 0-31 */
#घोषणा	IMR_BCNDMAINT7_88E		BIT(27)	/*  Beacon DMA Interrupt 7 */
#घोषणा	IMR_BCNDMAINT6_88E		BIT(26)	/*  Beacon DMA Interrupt 6 */
#घोषणा	IMR_BCNDMAINT5_88E		BIT(25)	/*  Beacon DMA Interrupt 5 */
#घोषणा	IMR_BCNDMAINT4_88E		BIT(24)	/*  Beacon DMA Interrupt 4 */
#घोषणा	IMR_BCNDMAINT3_88E		BIT(23)	/*  Beacon DMA Interrupt 3 */
#घोषणा	IMR_BCNDMAINT2_88E		BIT(22)	/*  Beacon DMA Interrupt 2 */
#घोषणा	IMR_BCNDMAINT1_88E		BIT(21)	/*  Beacon DMA Interrupt 1 */
#घोषणा	IMR_BCNDERR7_88E		BIT(20)	/*  Beacon DMA Error Int 7 */
#घोषणा	IMR_BCNDERR6_88E		BIT(19)	/*  Beacon DMA Error Int 6 */
#घोषणा	IMR_BCNDERR5_88E		BIT(18)	/*  Beacon DMA Error Int 5 */
#घोषणा	IMR_BCNDERR4_88E		BIT(17)	/*  Beacon DMA Error Int 4 */
#घोषणा	IMR_BCNDERR3_88E		BIT(16)	/*  Beacon DMA Error Int 3 */
#घोषणा	IMR_BCNDERR2_88E		BIT(15)	/*  Beacon DMA Error Int 2 */
#घोषणा	IMR_BCNDERR1_88E		BIT(14)	/*  Beacon DMA Error Int 1 */
#घोषणा	IMR_ATIMEND_E_88E		BIT(13)	/*  ATIM Winकरोw End Ext क्रम Win7 */
#घोषणा	IMR_TXERR_88E			BIT(11)	/*  Tx Err Flag Int Status, ग_लिखो 1 clear. */
#घोषणा	IMR_RXERR_88E			BIT(10)	/*  Rx Err Flag INT Status, Write 1 clear */
#घोषणा	IMR_TXFOVW_88E			BIT(9)	/*  Transmit FIFO Overflow */
#घोषणा	IMR_RXFOVW_88E			BIT(8)	/*  Receive FIFO Overflow */

#घोषणा	HAL_NIC_UNPLUG_ISR		0xFFFFFFFF	/*  The value when the NIC is unplugged क्रम PCI. */

/*  8192C EFUSE */
#घोषणा		HWSET_MAX_SIZE			256
#घोषणा		HWSET_MAX_SIZE_88E		512

/*===================================================================
=====================================================================
Here the रेजिस्टर defines are क्रम 92C. When the define is as same with 92C,
we will use the 92C's define क्रम the consistency
So the following defines क्रम 92C is not entire!!!!!!
=====================================================================
=====================================================================*/
/*
 * Based on Datasheet V33---090401
 * Register Summary
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
/*		 8192C (TXPAUSE) transmission छोड़ो (Offset 0x522, 8 bits) */
/*  Note:
 *	The bits of stopping AC(VO/VI/BE/BK) queue in datasheet
 *	RTL8192S/RTL8192C are wrong,
 *	the correct arragement is VO - Bit0, VI - Bit1, BE - Bit2,
 *	and BK - Bit3.
 *	8723 and 88E may be not correct either in the earlier version.
 */
#घोषणा		StopBecon			BIT(6)
#घोषणा		StopHigh			BIT(5)
#घोषणा		StopMgt				BIT(4)
#घोषणा		StopBK				BIT(3)
#घोषणा		StopBE				BIT(2)
#घोषणा		StopVI				BIT(1)
#घोषणा		StopVO				BIT(0)

/*        8192C (RCR) Receive Configuration Register(Offset 0x608, 32 bits) */
#घोषणा	RCR_APPFCS		BIT(31)	/* WMAC append FCS after payload */
#घोषणा	RCR_APP_MIC		BIT(30)
#घोषणा	RCR_APP_PHYSTS		BIT(28)
#घोषणा	RCR_APP_ICV		BIT(29)
#घोषणा	RCR_APP_PHYST_RXFF	BIT(28)
#घोषणा	RCR_APP_BA_SSN		BIT(27)	/* Accept BA SSN */
#घोषणा	RCR_ENMBID		BIT(24)	/* Enable Multiple BssId. */
#घोषणा	RCR_LSIGEN		BIT(23)
#घोषणा	RCR_MFBEN		BIT(22)
#घोषणा	RCR_HTC_LOC_CTRL	BIT(14)   /* MFC<--HTC=1 MFC-->HTC=0 */
#घोषणा	RCR_AMF			BIT(13)	/* Accept management type frame */
#घोषणा	RCR_ACF			BIT(12)	/* Accept control type frame */
#घोषणा	RCR_ADF			BIT(11)	/* Accept data type frame */
#घोषणा	RCR_AICV		BIT(9)	/* Accept ICV error packet */
#घोषणा	RCR_ACRC32		BIT(8)	/* Accept CRC32 error packet */
#घोषणा	RCR_CBSSID_BCN		BIT(7)	/* Accept BSSID match packet
					 * (Rx beacon, probe rsp)
					 */
#घोषणा	RCR_CBSSID_DATA		BIT(6)	/* Accept BSSID match (Data)*/
#घोषणा	RCR_CBSSID		RCR_CBSSID_DATA	/* Accept BSSID match */
#घोषणा	RCR_APWRMGT		BIT(5)	/* Accept घातer management pkt*/
#घोषणा	RCR_ADD3		BIT(4)	/* Accept address 3 match pkt */
#घोषणा	RCR_AB			BIT(3)	/* Accept broadcast packet */
#घोषणा	RCR_AM			BIT(2)	/* Accept multicast packet */
#घोषणा	RCR_APM			BIT(1)	/* Accept physical match pkt */
#घोषणा	RCR_AAP			BIT(0)	/* Accept all unicast packet */
#घोषणा	RCR_MXDMA_OFFSET	8
#घोषणा	RCR_FIFO_OFFSET		13

/*	0xFE00h ~ 0xFE55h	USB Configuration */
#घोषणा REG_USB_INFO			0xFE17
#घोषणा REG_USB_SPECIAL_OPTION		0xFE55
#घोषणा REG_USB_DMA_AGG_TO		0xFE5B
#घोषणा REG_USB_AGG_TO			0xFE5C
#घोषणा REG_USB_AGG_TH			0xFE5D

#घोषणा REG_USB_HRPWM			0xFE58
#घोषणा REG_USB_HCPWM			0xFE57
/*        8192C Register Bit and Content definition */
/*	0x0000h ~ 0x00FFh	System Configuration */

/* 2 SYS_ISO_CTRL */
#घोषणा ISO_MD2PP			BIT(0)
#घोषणा ISO_UA2USB			BIT(1)
#घोषणा ISO_UD2CORE			BIT(2)
#घोषणा ISO_PA2PCIE			BIT(3)
#घोषणा ISO_PD2CORE			BIT(4)
#घोषणा ISO_IP2MAC			BIT(5)
#घोषणा ISO_DIOP			BIT(6)
#घोषणा ISO_DIOE			BIT(7)
#घोषणा ISO_EB2CORE			BIT(8)
#घोषणा ISO_DIOR			BIT(9)
#घोषणा PWC_EV12V			BIT(15)

/* 2 SYS_FUNC_EN */
#घोषणा FEN_BBRSTB			BIT(0)
#घोषणा FEN_BB_GLB_RSTn			BIT(1)
#घोषणा FEN_USBA			BIT(2)
#घोषणा FEN_UPLL			BIT(3)
#घोषणा FEN_USBD			BIT(4)
#घोषणा FEN_DIO_PCIE			BIT(5)
#घोषणा FEN_PCIEA			BIT(6)
#घोषणा FEN_PPLL			BIT(7)
#घोषणा FEN_PCIED			BIT(8)
#घोषणा FEN_DIOE			BIT(9)
#घोषणा FEN_CPUEN			BIT(10)
#घोषणा FEN_DCORE			BIT(11)
#घोषणा FEN_ELDR			BIT(12)
#घोषणा FEN_DIO_RF			BIT(13)
#घोषणा FEN_HWPDN			BIT(14)
#घोषणा FEN_MREGEN			BIT(15)

/* 2 APS_FSMCO */
#घोषणा PFM_LDALL			BIT(0)
#घोषणा PFM_ALDN			BIT(1)
#घोषणा PFM_LDKP			BIT(2)
#घोषणा PFM_WOWL			BIT(3)
#घोषणा EnPDN				BIT(4)
#घोषणा PDN_PL				BIT(5)
#घोषणा APFM_ONMAC			BIT(8)
#घोषणा APFM_OFF			BIT(9)
#घोषणा APFM_RSM			BIT(10)
#घोषणा AFSM_HSUS			BIT(11)
#घोषणा AFSM_PCIE			BIT(12)
#घोषणा APDM_MAC			BIT(13)
#घोषणा APDM_HOST			BIT(14)
#घोषणा APDM_HPDN			BIT(15)
#घोषणा RDY_MACON			BIT(16)
#घोषणा SUS_HOST			BIT(17)
#घोषणा ROP_ALD				BIT(20)
#घोषणा ROP_PWR				BIT(21)
#घोषणा ROP_SPS				BIT(22)
#घोषणा SOP_MRST			BIT(25)
#घोषणा SOP_FUSE			BIT(26)
#घोषणा SOP_ABG				BIT(27)
#घोषणा SOP_AMB				BIT(28)
#घोषणा SOP_RCK				BIT(29)
#घोषणा SOP_A8M				BIT(30)
#घोषणा XOP_BTCK			BIT(31)

/* 2 SYS_CLKR */
#घोषणा ANAD16V_EN			BIT(0)
#घोषणा ANA8M				BIT(1)
#घोषणा MACSLP				BIT(4)
#घोषणा LOADER_CLK_EN			BIT(5)

/* 2 9346CR */

#घोषणा		BOOT_FROM_EEPROM	BIT(4)
#घोषणा		EEPROM_EN		BIT(5)

/* 2 SPS0_CTRL */

/* 2 SPS_OCP_CFG */

/* 2 RF_CTRL */
#घोषणा RF_EN				BIT(0)
#घोषणा RF_RSTB				BIT(1)
#घोषणा RF_SDMRSTB			BIT(2)

/* 2 LDOV12D_CTRL */
#घोषणा LDV12_EN			BIT(0)
#घोषणा LDV12_SDBY			BIT(1)
#घोषणा LPLDO_HSM			BIT(2)
#घोषणा LPLDO_LSM_DIS			BIT(3)
#घोषणा _LDV12_VADJ(x)			(((x) & 0xF) << 4)

/* 2EFUSE_CTRL */
#घोषणा ALD_EN				BIT(18)
#घोषणा EF_PD				BIT(19)
#घोषणा EF_FLAG				BIT(31)

/* 2 EFUSE_TEST (For RTL8723 partially) */
#घोषणा EF_TRPT				BIT(7)
/*  00: Wअगरi Efuse, 01: BT Efuse0, 10: BT Efuse1, 11: BT Efuse2 */
#घोषणा EF_CELL_SEL			(BIT(8) | BIT(9))
#घोषणा LDOE25_EN			BIT(31)
#घोषणा EFUSE_SEL(x)			(((x) & 0x3) << 8)
#घोषणा EFUSE_SEL_MASK			0x300
#घोषणा EFUSE_WIFI_SEL_0		0x0
#घोषणा EFUSE_BT_SEL_0			0x1
#घोषणा EFUSE_BT_SEL_1			0x2
#घोषणा EFUSE_BT_SEL_2			0x3

#घोषणा EFUSE_ACCESS_ON			0x69	/*  For RTL8723 only. */
#घोषणा EFUSE_ACCESS_OFF		0x00	/*  For RTL8723 only. */

/* 2 8051FWDL */
/* 2 MCUFWDL */
#घोषणा MCUFWDL_EN			BIT(0)
#घोषणा MCUFWDL_RDY			BIT(1)
#घोषणा FWDL_CHKSUM_RPT			BIT(2)
#घोषणा MACINI_RDY			BIT(3)
#घोषणा BBINI_RDY			BIT(4)
#घोषणा RFINI_RDY			BIT(5)
#घोषणा WINTINI_RDY			BIT(6)
#घोषणा RAM_DL_SEL			BIT(7) /*  1:RAM, 0:ROM */
#घोषणा ROM_DLEN			BIT(19)
#घोषणा CPRST				BIT(23)

/* 2 REG_SYS_CFG */
#घोषणा XCLK_VLD			BIT(0)
#घोषणा ACLK_VLD			BIT(1)
#घोषणा UCLK_VLD			BIT(2)
#घोषणा PCLK_VLD			BIT(3)
#घोषणा PCIRSTB				BIT(4)
#घोषणा V15_VLD				BIT(5)
#घोषणा SW_OFFLOAD_EN			BIT(7)
#घोषणा SIC_IDLE			BIT(8)
#घोषणा BD_MAC2				BIT(9)
#घोषणा BD_MAC1				BIT(10)
#घोषणा IC_MACPHY_MODE			BIT(11)
#घोषणा CHIP_VER			(BIT(12) | BIT(13) | BIT(14) | BIT(15))
#घोषणा BT_FUNC				BIT(16)
#घोषणा VENDOR_ID			BIT(19)
#घोषणा PAD_HWPD_IDN			BIT(22)
#घोषणा TRP_VAUX_EN			BIT(23)	/*  RTL ID */
#घोषणा TRP_BT_EN			BIT(24)
#घोषणा BD_PKG_SEL			BIT(25)
#घोषणा BD_HCI_SEL			BIT(26)
#घोषणा TYPE_ID				BIT(27)

#घोषणा CHIP_VER_RTL_MASK		0xF000	/* Bit 12 ~ 15 */
#घोषणा CHIP_VER_RTL_SHIFT		12

/* 2REG_GPIO_OUTSTS (For RTL8723 only) */
#घोषणा	EFS_HCI_SEL			(BIT(0) | BIT(1))
#घोषणा	PAD_HCI_SEL			(BIT(2) | BIT(3))
#घोषणा	HCI_SEL				(BIT(4) | BIT(5))
#घोषणा	PKG_SEL_HCI			BIT(6)
#घोषणा	FEN_GPS				BIT(7)
#घोषणा	FEN_BT				BIT(8)
#घोषणा	FEN_WL				BIT(9)
#घोषणा	FEN_PCI				BIT(10)
#घोषणा	FEN_USB				BIT(11)
#घोषणा	BTRF_HWPDN_N			BIT(12)
#घोषणा	WLRF_HWPDN_N			BIT(13)
#घोषणा	PDN_BT_N			BIT(14)
#घोषणा	PDN_GPS_N			BIT(15)
#घोषणा	BT_CTL_HWPDN			BIT(16)
#घोषणा	GPS_CTL_HWPDN			BIT(17)
#घोषणा	PPHY_SUSB			BIT(20)
#घोषणा	UPHY_SUSB			BIT(21)
#घोषणा	PCI_SUSEN			BIT(22)
#घोषणा	USB_SUSEN			BIT(23)
#घोषणा	RF_RL_ID			(BIT(31) | BIT(30) | BIT(29) | BIT(28))

/* 2SYS_CFG */
#घोषणा RTL_ID				BIT(23)	/*  TestChip ID, 1:Test(RLE); 0:MP(RL) */

/*	0x0100h ~ 0x01FFh	MACTOP General Configuration */

/* 2 Function Enable Registers */
/* 2 CR */

#घोषणा HCI_TXDMA_EN			BIT(0)
#घोषणा HCI_RXDMA_EN			BIT(1)
#घोषणा TXDMA_EN			BIT(2)
#घोषणा RXDMA_EN			BIT(3)
#घोषणा PROTOCOL_EN			BIT(4)
#घोषणा SCHEDULE_EN			BIT(5)
#घोषणा MACTXEN				BIT(6)
#घोषणा MACRXEN				BIT(7)
#घोषणा ENSWBCN				BIT(8)
#घोषणा ENSEC				BIT(9)
#घोषणा CALTMR_EN			BIT(10)	/*  32k CAL TMR enable */

/*  Network type */
#घोषणा _NETTYPE(x)			(((x) & 0x3) << 16)
#घोषणा MASK_NETTYPE			0x30000
#घोषणा NT_NO_LINK			0x0
#घोषणा NT_LINK_AD_HOC			0x1
#घोषणा NT_LINK_AP			0x2
#घोषणा NT_AS_AP			0x3

/* 2 PBP - Page Size Register */
#घोषणा GET_RX_PAGE_SIZE(value)		((value) & 0xF)
#घोषणा GET_TX_PAGE_SIZE(value)		(((value) & 0xF0) >> 4)
#घोषणा _PSRX_MASK			0xF
#घोषणा _PSTX_MASK			0xF0
#घोषणा _PSRX(x)			(x)
#घोषणा _PSTX(x)			((x) << 4)

#घोषणा PBP_64				0x0
#घोषणा PBP_128				0x1
#घोषणा PBP_256				0x2
#घोषणा PBP_512				0x3
#घोषणा PBP_1024			0x4

/* 2 TX/RXDMA */
#घोषणा RXDMA_ARBBW_EN			BIT(0)
#घोषणा RXSHFT_EN			BIT(1)
#घोषणा RXDMA_AGG_EN			BIT(2)
#घोषणा QS_VO_QUEUE			BIT(8)
#घोषणा QS_VI_QUEUE			BIT(9)
#घोषणा QS_BE_QUEUE			BIT(10)
#घोषणा QS_BK_QUEUE			BIT(11)
#घोषणा QS_MANAGER_QUEUE		BIT(12)
#घोषणा QS_HIGH_QUEUE			BIT(13)

#घोषणा HQSEL_VOQ			BIT(0)
#घोषणा HQSEL_VIQ			BIT(1)
#घोषणा HQSEL_BEQ			BIT(2)
#घोषणा HQSEL_BKQ			BIT(3)
#घोषणा HQSEL_MGTQ			BIT(4)
#घोषणा HQSEL_HIQ			BIT(5)

/*  For normal driver, 0x10C */
#घोषणा _TXDMA_HIQ_MAP(x)		(((x) & 0x3) << 14)
#घोषणा _TXDMA_MGQ_MAP(x)		(((x) & 0x3) << 12)
#घोषणा _TXDMA_BKQ_MAP(x)		(((x) & 0x3) << 10)
#घोषणा _TXDMA_BEQ_MAP(x)		(((x) & 0x3) << 8)
#घोषणा _TXDMA_VIQ_MAP(x)		(((x) & 0x3) << 6)
#घोषणा _TXDMA_VOQ_MAP(x)		(((x) & 0x3) << 4)

#घोषणा QUEUE_LOW			1
#घोषणा QUEUE_NORMAL			2
#घोषणा QUEUE_HIGH			3

/* 2 TRXFF_BNDY */

/* 2 LLT_INIT */
#घोषणा _LLT_NO_ACTIVE			0x0
#घोषणा _LLT_WRITE_ACCESS		0x1
#घोषणा _LLT_READ_ACCESS		0x2

#घोषणा _LLT_INIT_DATA(x)		((x) & 0xFF)
#घोषणा _LLT_INIT_ADDR(x)		(((x) & 0xFF) << 8)
#घोषणा _LLT_OP(x)			(((x) & 0x3) << 30)
#घोषणा _LLT_OP_VALUE(x)		(((x) >> 30) & 0x3)

/*	0x0200h ~ 0x027Fh	TXDMA Configuration */
/* 2RQPN */
#घोषणा _HPQ(x)				((x) & 0xFF)
#घोषणा _LPQ(x)				(((x) & 0xFF) << 8)
#घोषणा _PUBQ(x)			(((x) & 0xFF) << 16)
/*  NOTE: in RQPN_NPQ रेजिस्टर */
#घोषणा _NPQ(x)				((x) & 0xFF)

#घोषणा HPQ_PUBLIC_DIS			BIT(24)
#घोषणा LPQ_PUBLIC_DIS			BIT(25)
#घोषणा LD_RQPN				BIT(31)

/* 2TDECTRL */
#घोषणा BCN_VALID			BIT(16)
#घोषणा BCN_HEAD(x)			(((x) & 0xFF) << 8)
#घोषणा	BCN_HEAD_MASK			0xFF00

/* 2 TDECTL */
#घोषणा BLK_DESC_NUM_SHIFT		4
#घोषणा BLK_DESC_NUM_MASK		0xF

/* 2 TXDMA_OFFSET_CHK */
#घोषणा DROP_DATA_EN			BIT(9)

/*	0x0280h ~ 0x028Bh	RX DMA Configuration */

/*     REG_RXDMA_CONTROL, 0x0286h */

/* 2 REG_RXPKT_NUM, 0x0284 */
#घोषणा		RXPKT_RELEASE_POLL	BIT(16)
#घोषणा	RXDMA_IDLE			BIT(17)
#घोषणा	RW_RELEASE_EN			BIT(18)

/*	0x0400h ~ 0x047Fh	Protocol Configuration */
/* 2 FWHW_TXQ_CTRL */
#घोषणा EN_AMPDU_RTY_NEW		BIT(7)

/* 2 SPEC SIFS */
#घोषणा _SPEC_SIFS_CCK(x)		((x) & 0xFF)
#घोषणा _SPEC_SIFS_OFDM(x)		(((x) & 0xFF) << 8)

/* 2 RL */
#घोषणा	RETRY_LIMIT_SHORT_SHIFT		8
#घोषणा	RETRY_LIMIT_LONG_SHIFT		0

/*	0x0500h ~ 0x05FFh	EDCA Configuration */

/* 2 EDCA setting */
#घोषणा AC_PARAM_TXOP_LIMIT_OFFSET	16
#घोषणा AC_PARAM_ECW_MAX_OFFSET		12
#घोषणा AC_PARAM_ECW_MIN_OFFSET		8
#घोषणा AC_PARAM_AIFS_OFFSET		0

#घोषणा _LRL(x)			((x) & 0x3F)
#घोषणा _SRL(x)			(((x) & 0x3F) << 8)

/* 2 BCN_CTRL */
#घोषणा EN_MBSSID		BIT(1)
#घोषणा EN_TXBCN_RPT		BIT(2)
#घोषणा EN_BCN_FUNCTION		BIT(3)
#घोषणा DIS_TSF_UPDATE		BIT(3)

/*  The same function but dअगरferent bit field. */
#घोषणा DIS_TSF_UDT0_NORMAL_CHIP	BIT(4)
#घोषणा DIS_TSF_UDT0_TEST_CHIP	BIT(5)
#घोषणा STOP_BCNQ		BIT(6)

/* 2 ACMHWCTRL */
#घोषणा	AcmHw_HwEn		BIT(0)
#घोषणा	AcmHw_BeqEn		BIT(1)
#घोषणा	AcmHw_ViqEn		BIT(2)
#घोषणा	AcmHw_VoqEn		BIT(3)
#घोषणा	AcmHw_BeqStatus		BIT(4)
#घोषणा	AcmHw_ViqStatus		BIT(5)
#घोषणा	AcmHw_VoqStatus		BIT(6)

/*	0x0600h ~ 0x07FFh	WMAC Configuration */
/* 2APSD_CTRL */
#घोषणा APSDOFF			BIT(6)
#घोषणा APSDOFF_STATUS		BIT(7)

#घोषणा RATE_BITMAP_ALL		0xFFFFF

/*  Only use CCK 1M rate क्रम ACK */
#घोषणा RATE_RRSR_CCK_ONLY_1M	0xFFFF1

/* 2 TCR */
#घोषणा TSFRST			BIT(0)
#घोषणा DIS_GCLK		BIT(1)
#घोषणा PAD_SEL			BIT(2)
#घोषणा PWR_ST			BIT(6)
#घोषणा PWRBIT_OW_EN		BIT(7)
#घोषणा ACRC			BIT(8)
#घोषणा CFENDFORM		BIT(9)
#घोषणा ICV			BIT(10)

/* 2 RCR */
#घोषणा AAP			BIT(0)
#घोषणा APM			BIT(1)
#घोषणा AM			BIT(2)
#घोषणा AB			BIT(3)
#घोषणा ADD3			BIT(4)
#घोषणा APWRMGT			BIT(5)
#घोषणा CBSSID			BIT(6)
#घोषणा CBSSID_DATA		BIT(6)
#घोषणा CBSSID_BCN		BIT(7)
#घोषणा ACRC32			BIT(8)
#घोषणा AICV			BIT(9)
#घोषणा ADF			BIT(11)
#घोषणा ACF			BIT(12)
#घोषणा AMF			BIT(13)
#घोषणा HTC_LOC_CTRL		BIT(14)
#घोषणा UC_DATA_EN		BIT(16)
#घोषणा BM_DATA_EN		BIT(17)
#घोषणा MFBEN			BIT(22)
#घोषणा LSIGEN			BIT(23)
#घोषणा EnMBID			BIT(24)
#घोषणा APP_BASSN		BIT(27)
#घोषणा APP_PHYSTS		BIT(28)
#घोषणा APP_ICV			BIT(29)
#घोषणा APP_MIC			BIT(30)
#घोषणा APP_FCS			BIT(31)

/* 2 SECCFG */
#घोषणा	SCR_TxUseDK		BIT(0)	/* Force Tx Use Default Key */
#घोषणा	SCR_RxUseDK		BIT(1)	/* Force Rx Use Default Key */
#घोषणा	SCR_TxEncEnable		BIT(2)	/* Enable Tx Encryption */
#घोषणा	SCR_RxDecEnable		BIT(3)	/* Enable Rx Decryption */
#घोषणा	SCR_SKByA2		BIT(4)	/* Search kEY BY A2 */
#घोषणा	SCR_NoSKMC		BIT(5)	/* No Key Search Multicast */
#घोषणा SCR_TXBCUSEDK		BIT(6)	/* Force Tx Bcast pkt Use Default Key */
#घोषणा SCR_RXBCUSEDK		BIT(7)	/* Force Rx Bcast pkt Use Default Key */

/*	RTL8188E SDIO Configuration */

/*  I/O bus करोमुख्य address mapping */
#घोषणा SDIO_LOCAL_BASE			0x10250000
#घोषणा WLAN_IOREG_BASE			0x10260000
#घोषणा FIRMWARE_FIFO_BASE		0x10270000
#घोषणा TX_HIQ_BASE			0x10310000
#घोषणा TX_MIQ_BASE			0x10320000
#घोषणा TX_LOQ_BASE			0x10330000
#घोषणा RX_RX0FF_BASE			0x10340000

/*  SDIO host local रेजिस्टर space mapping. */
#घोषणा SDIO_LOCAL_MSK			0x0FFF
#घोषणा WLAN_IOREG_MSK			0x7FFF
#घोषणा WLAN_FIFO_MSK			0x1FFF	/*  Aggregation Length[12:0] */
#घोषणा WLAN_RX0FF_MSK			0x0003

/*  Without ref to the SDIO Device ID */
#घोषणा SDIO_WITHOUT_REF_DEVICE_ID	0
#घोषणा SDIO_LOCAL_DEVICE_ID		0	/*  0b[16], 000b[15:13] */
#घोषणा WLAN_TX_HIQ_DEVICE_ID		4	/*  0b[16], 100b[15:13] */
#घोषणा WLAN_TX_MIQ_DEVICE_ID		5	/*  0b[16], 101b[15:13] */
#घोषणा WLAN_TX_LOQ_DEVICE_ID		6	/*  0b[16], 110b[15:13] */
#घोषणा WLAN_RX0FF_DEVICE_ID		7	/*  0b[16], 111b[15:13] */
#घोषणा WLAN_IOREG_DEVICE_ID		8	/*  1b[16] */

/*  SDIO Tx Free Page Index */
#घोषणा HI_QUEUE_IDX			0
#घोषणा MID_QUEUE_IDX			1
#घोषणा LOW_QUEUE_IDX			2
#घोषणा PUBLIC_QUEUE_IDX		3

#घोषणा SDIO_MAX_TX_QUEUE		3	/*  HIQ, MIQ and LOQ */
#घोषणा SDIO_MAX_RX_QUEUE		1

/*  SDIO Tx Control */
#घोषणा SDIO_REG_TX_CTRL		0x0000
/*  SDIO Host Interrupt Mask */
#घोषणा SDIO_REG_HIMR			0x0014
/*  SDIO Host Interrupt Service Routine */
#घोषणा SDIO_REG_HISR			0x0018
/*  HCI Current Power Mode */
#घोषणा SDIO_REG_HCPWM			0x0019
/*  RXDMA Request Length */
#घोषणा SDIO_REG_RX0_REQ_LEN		0x001C
/*  Free Tx Buffer Page */
#घोषणा SDIO_REG_FREE_TXPG		0x0020
/*  HCI Current Power Mode 1 */
#घोषणा SDIO_REG_HCPWM1			0x0024
/*  HCI Current Power Mode 2 */
#घोषणा SDIO_REG_HCPWM2			0x0026
/*  HTSF Inक्रमmaion */
#घोषणा SDIO_REG_HTSFR_INFO		0x0030
/*  HCI Request Power Mode 1 */
#घोषणा SDIO_REG_HRPWM1			0x0080
/*  HCI Request Power Mode 2 */
#घोषणा SDIO_REG_HRPWM2			0x0082
/*  HCI Power Save Clock */
#घोषणा SDIO_REG_HPS_CLKR		0x0084
/*  SDIO HCI Suspend Control */
#घोषणा SDIO_REG_HSUS_CTRL		0x0086
/*  SDIO Host Extension Interrupt Mask Always */
#घोषणा SDIO_REG_HIMR_ON		0x0090
/*  SDIO Host Extension Interrupt Status Always */
#घोषणा SDIO_REG_HISR_ON		0x0091

#घोषणा SDIO_HIMR_DISABLED			0

/*  RTL8188E SDIO Host Interrupt Mask Register */
#घोषणा SDIO_HIMR_RX_REQUEST_MSK		BIT(0)
#घोषणा SDIO_HIMR_AVAL_MSK			BIT(1)
#घोषणा SDIO_HIMR_TXERR_MSK			BIT(2)
#घोषणा SDIO_HIMR_RXERR_MSK			BIT(3)
#घोषणा SDIO_HIMR_TXFOVW_MSK			BIT(4)
#घोषणा SDIO_HIMR_RXFOVW_MSK			BIT(5)
#घोषणा SDIO_HIMR_TXBCNOK_MSK			BIT(6)
#घोषणा SDIO_HIMR_TXBCNERR_MSK			BIT(7)
#घोषणा SDIO_HIMR_BCNERLY_INT_MSK		BIT(16)
#घोषणा SDIO_HIMR_C2HCMD_MSK			BIT(17)
#घोषणा SDIO_HIMR_CPWM1_MSK			BIT(18)
#घोषणा SDIO_HIMR_CPWM2_MSK			BIT(19)
#घोषणा SDIO_HIMR_HSISR_IND_MSK			BIT(20)
#घोषणा SDIO_HIMR_GTINT3_IND_MSK		BIT(21)
#घोषणा SDIO_HIMR_GTINT4_IND_MSK		BIT(22)
#घोषणा SDIO_HIMR_PSTIMEOUT_MSK			BIT(23)
#घोषणा SDIO_HIMR_OCPINT_MSK			BIT(24)
#घोषणा SDIO_HIMR_ATIMEND_MSK			BIT(25)
#घोषणा SDIO_HIMR_ATIMEND_E_MSK			BIT(26)
#घोषणा SDIO_HIMR_CTWEND_MSK			BIT(27)

/* RTL8188E SDIO Specअगरic */
#घोषणा	SDIO_HIMR_MCU_ERR_MSK			BIT(28)
#घोषणा	SDIO_HIMR_TSF_BIT32_TOGGLE_MSK		BIT(29)

/*  SDIO Host Interrupt Service Routine */
#घोषणा SDIO_HISR_RX_REQUEST			BIT(0)
#घोषणा SDIO_HISR_AVAL				BIT(1)
#घोषणा SDIO_HISR_TXERR				BIT(2)
#घोषणा SDIO_HISR_RXERR				BIT(3)
#घोषणा SDIO_HISR_TXFOVW			BIT(4)
#घोषणा SDIO_HISR_RXFOVW			BIT(5)
#घोषणा SDIO_HISR_TXBCNOK			BIT(6)
#घोषणा SDIO_HISR_TXBCNERR			BIT(7)
#घोषणा SDIO_HISR_BCNERLY_INT			BIT(16)
#घोषणा SDIO_HISR_C2HCMD			BIT(17)
#घोषणा SDIO_HISR_CPWM1				BIT(18)
#घोषणा SDIO_HISR_CPWM2				BIT(19)
#घोषणा SDIO_HISR_HSISR_IND			BIT(20)
#घोषणा SDIO_HISR_GTINT3_IND			BIT(21)
#घोषणा SDIO_HISR_GTINT4_IND			BIT(22)
#घोषणा SDIO_HISR_PSTIME			BIT(23)
#घोषणा SDIO_HISR_OCPINT			BIT(24)
#घोषणा SDIO_HISR_ATIMEND			BIT(25)
#घोषणा SDIO_HISR_ATIMEND_E			BIT(26)
#घोषणा SDIO_HISR_CTWEND			BIT(27)

/* RTL8188E SDIO Specअगरic */
#घोषणा	SDIO_HISR_MCU_ERR			BIT(28)
#घोषणा	SDIO_HISR_TSF_BIT32_TOGGLE		BIT(29)

#घोषणा MASK_SDIO_HISR_CLEAR				\
	(SDIO_HISR_TXERR | SDIO_HISR_RXERR | SDIO_HISR_TXFOVW |\
	 SDIO_HISR_RXFOVW | SDIO_HISR_TXBCNOK | SDIO_HISR_TXBCNERR |\
	 SDIO_HISR_C2HCMD | SDIO_HISR_CPWM1 | SDIO_HISR_CPWM2 |\
	 SDIO_HISR_HSISR_IND | SDIO_HISR_GTINT3_IND | SDIO_HISR_GTINT4_IND |\
	 SDIO_HISR_PSTIMEOUT | SDIO_HISR_OCPINT)

/*  SDIO HCI Suspend Control Register */
#घोषणा HCI_RESUME_PWR_RDY		BIT(1)
#घोषणा HCI_SUS_CTRL			BIT(0)

/*  SDIO Tx FIFO related */
/*  The number of Tx FIFO मुक्त page */
#घोषणा SDIO_TX_FREE_PG_QUEUE			4
#घोषणा SDIO_TX_FIFO_PAGE_SZ			128

/*	0xFE00h ~ 0xFE55h	USB Configuration */

/* 2 USB Inक्रमmation (0xFE17) */
#घोषणा USB_IS_HIGH_SPEED			0
#घोषणा USB_IS_FULL_SPEED			1
#घोषणा USB_SPEED_MASK				BIT(5)

#घोषणा USB_NORMAL_SIE_EP_MASK			0xF
#घोषणा USB_NORMAL_SIE_EP_SHIFT			4

/* 2 Special Option */
#घोषणा USB_AGG_EN				BIT(3)

/*  0; Use पूर्णांकerrupt endpoपूर्णांक to upload पूर्णांकerrupt pkt */
/*  1; Use bulk endpoपूर्णांक to upload पूर्णांकerrupt pkt, */
#घोषणा INT_BULK_SEL				BIT(4)

/* 2REG_C2HEVT_CLEAR */
/*  Set by driver and notअगरy FW that the driver has पढ़ो
 *  the C2H command message
 */
#घोषणा	C2H_EVT_HOST_CLOSE	0x00
/*  Set by FW indicating that FW had set the C2H command
 *  message and it's not yet पढ़ो by driver.
 */
#घोषणा C2H_EVT_FW_CLOSE	0xFF

/* 2REG_MULTI_FUNC_CTRL(For RTL8723 Only) */
/*  Enable GPIO[9] as WiFi HW PDn source */
#घोषणा	WL_HWPDN_EN				BIT(0)
/*  WiFi HW PDn polarity control */
#घोषणा	WL_HWPDN_SL				BIT(1)
/*  WiFi function enable */
#घोषणा	WL_FUNC_EN				BIT(2)
/*  Enable GPIO[9] as WiFi RF HW PDn source */
#घोषणा	WL_HWROF_EN				BIT(3)
/*  Enable GPIO[11] as BT HW PDn source */
#घोषणा	BT_HWPDN_EN				BIT(16)
/*  BT HW PDn polarity control */
#घोषणा	BT_HWPDN_SL				BIT(17)
/*  BT function enable */
#घोषणा	BT_FUNC_EN				BIT(18)
/*  Enable GPIO[11] as BT/GPS RF HW PDn source */
#घोषणा	BT_HWROF_EN				BIT(19)
/*  Enable GPIO[10] as GPS HW PDn source */
#घोषणा	GPS_HWPDN_EN				BIT(20)
/*  GPS HW PDn polarity control */
#घोषणा	GPS_HWPDN_SL				BIT(21)
/*  GPS function enable */
#घोषणा	GPS_FUNC_EN				BIT(22)

/* 3 REG_LIFECTRL_CTRL */
#घोषणा	HAL92C_EN_PKT_LIFE_TIME_BK		BIT(3)
#घोषणा	HAL92C_EN_PKT_LIFE_TIME_BE		BIT(2)
#घोषणा	HAL92C_EN_PKT_LIFE_TIME_VI		BIT(1)
#घोषणा	HAL92C_EN_PKT_LIFE_TIME_VO		BIT(0)

#घोषणा	HAL92C_MSDU_LIFE_TIME_UNIT		128	/*  in us */

/*  General definitions */
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER		176 /*  22k 22528 bytes */

#घोषणा POLLING_LLT_THRESHOLD			20
#घोषणा POLLING_READY_TIMEOUT_COUNT		1000
/*  GPIO BIT */
#घोषणा	HAL_8192C_HW_GPIO_WPS_BIT		BIT(2)

/*	8192C EEPROM/EFUSE share रेजिस्टर definition. */

/*	EEPROM/Efuse PG Offset क्रम 88EE/88EU/88ES */
#घोषणा	EEPROM_TX_PWR_INX_88E			0x10

#घोषणा	EEPROM_ChannelPlan_88E			0xB8
#घोषणा	EEPROM_XTAL_88E				0xB9
#घोषणा	EEPROM_THERMAL_METER_88E		0xBA
#घोषणा	EEPROM_IQK_LCK_88E			0xBB

#घोषणा	EEPROM_RF_BOARD_OPTION_88E		0xC1
#घोषणा	EEPROM_RF_FEATURE_OPTION_88E		0xC2
#घोषणा	EEPROM_RF_BT_SETTING_88E		0xC3
#घोषणा	EEPROM_VERSION_88E			0xC4
#घोषणा	EEPROM_CUSTOMERID_88E			0xC5
#घोषणा	EEPROM_RF_ANTENNA_OPT_88E		0xC9

/*  RTL88EE */
#घोषणा	EEPROM_MAC_ADDR_88EE			0xD0
#घोषणा	EEPROM_VID_88EE				0xD6
#घोषणा	EEPROM_DID_88EE				0xD8
#घोषणा	EEPROM_SVID_88EE			0xDA
#घोषणा	EEPROM_SMID_88EE			0xDC

/* RTL88EU */
#घोषणा	EEPROM_MAC_ADDR_88EU			0xD7
#घोषणा	EEPROM_VID_88EU				0xD0
#घोषणा	EEPROM_PID_88EU				0xD2
#घोषणा EEPROM_USB_OPTIONAL_FUNCTION0		0xD4

/*  RTL88ES */
#घोषणा	EEPROM_MAC_ADDR_88ES			0x11A

/*		EEPROM/Efuse Value Type */
#घोषणा EETYPE_TX_PWR				0x0

/*  Default Value क्रम EEPROM or EFUSE!!! */
#घोषणा EEPROM_Default_TSSI			0x0
#घोषणा EEPROM_Default_TxPowerDअगरf		0x0
#घोषणा EEPROM_Default_CrystalCap		0x5
/*  Default: 2X2, RTL8192CE(QFPN68) */
#घोषणा EEPROM_Default_BoardType		0x02
#घोषणा EEPROM_Default_TxPower			0x1010
#घोषणा EEPROM_Default_HT2T_TxPwr		0x10

#घोषणा EEPROM_Default_LegacyHTTxPowerDअगरf	0x3
#घोषणा EEPROM_Default_ThermalMeter		0x12

#घोषणा EEPROM_Default_AntTxPowerDअगरf		0x0
#घोषणा EEPROM_Default_TxPwDअगरf_CrystalCap	0x5
#घोषणा EEPROM_Default_TxPowerLevel		0x2A

#घोषणा EEPROM_Default_HT40_2SDअगरf		0x0
/*  HT20<->40 शेष Tx Power Index Dअगरference */
#घोषणा EEPROM_Default_HT20_Dअगरf		2
#घोषणा EEPROM_Default_LegacyHTTxPowerDअगरf	0x3
#घोषणा EEPROM_Default_HT40_PwrMaxOffset	0
#घोषणा EEPROM_Default_HT20_PwrMaxOffset	0

#घोषणा EEPROM_Default_CrystalCap_88E		0x20
#घोषणा	EEPROM_Default_ThermalMeter_88E		0x18

/* New EFUSE शेष value */
#घोषणा		EEPROM_DEFAULT_24G_INDEX	0x2D
#घोषणा		EEPROM_DEFAULT_24G_HT20_DIFF	0X02
#घोषणा		EEPROM_DEFAULT_24G_OFDM_DIFF	0X04

#घोषणा		EEPROM_DEFAULT_5G_INDEX		0X2A
#घोषणा		EEPROM_DEFAULT_5G_HT20_DIFF	0X00
#घोषणा		EEPROM_DEFAULT_5G_OFDM_DIFF	0X04

#घोषणा		EEPROM_DEFAULT_DIFF		0XFE
#घोषणा	EEPROM_DEFAULT_CHANNEL_PLAN		0x7F
#घोषणा	EEPROM_DEFAULT_BOARD_OPTION		0x00
#घोषणा	EEPROM_DEFAULT_FEATURE_OPTION		0x00
#घोषणा	EEPROM_DEFAULT_BT_OPTION		0x10

/*  For debug */
#घोषणा EEPROM_Default_PID			0x1234
#घोषणा EEPROM_Default_VID			0x5678
#घोषणा EEPROM_Default_CustomerID		0xAB
#घोषणा	EEPROM_Default_CustomerID_8188E		0x00
#घोषणा EEPROM_Default_SubCustomerID		0xCD
#घोषणा EEPROM_Default_Version			0

#घोषणा EEPROM_CHANNEL_PLAN_FCC			0x0
#घोषणा EEPROM_CHANNEL_PLAN_IC			0x1
#घोषणा EEPROM_CHANNEL_PLAN_ETSI		0x2
#घोषणा EEPROM_CHANNEL_PLAN_SPA			0x3
#घोषणा EEPROM_CHANNEL_PLAN_FRANCE		0x4
#घोषणा EEPROM_CHANNEL_PLAN_MKK			0x5
#घोषणा EEPROM_CHANNEL_PLAN_MKK1		0x6
#घोषणा EEPROM_CHANNEL_PLAN_ISRAEL		0x7
#घोषणा EEPROM_CHANNEL_PLAN_TELEC		0x8
#घोषणा EEPROM_CHANNEL_PLAN_GLOBAL_DOMA		0x9
#घोषणा EEPROM_CHANNEL_PLAN_WORLD_WIDE_13	0xA
#घोषणा EEPROM_CHANNEL_PLAN_NCC			0xB
#घोषणा EEPROM_USB_OPTIONAL1			0xE
#घोषणा EEPROM_CHANNEL_PLAN_BY_HW_MASK		0x80

#घोषणा EEPROM_CID_DEFAULT		0x0
#घोषणा EEPROM_CID_TOSHIBA		0x4
#घोषणा EEPROM_CID_CCX			0x10 /*  CCX test. */
#घोषणा EEPROM_CID_QMI			0x0D
#घोषणा EEPROM_CID_WHQL			0xFE
#घोषणा	RTL_EEPROM_ID			0x8129

#पूर्ण_अगर /* __RTL8188E_SPEC_H__ */
