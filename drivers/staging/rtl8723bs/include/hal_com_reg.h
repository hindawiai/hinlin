<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_COMMON_REG_H__
#घोषणा __HAL_COMMON_REG_H__


#घोषणा MAC_ADDR_LEN				6

#घोषणा HAL_NAV_UPPER_UNIT		128		/*  micro-second */

/*  8188E PKT_BUFF_ACCESS_CTRL value */
#घोषणा TXPKT_BUF_SELECT				0x69
#घोषणा RXPKT_BUF_SELECT				0xA5
#घोषणा DISABLE_TRXPKT_BUF_ACCESS		0x0

/*  */
/*  */
/*  */

/*  */
/*  */
/* 	0x0000h ~ 0x00FFh	System Configuration */
/*  */
/*  */
#घोषणा REG_SYS_ISO_CTRL				0x0000
#घोषणा REG_SYS_FUNC_EN				0x0002
#घोषणा REG_APS_FSMCO					0x0004
#घोषणा REG_SYS_CLKR					0x0008
#घोषणा REG_9346CR						0x000A
#घोषणा REG_SYS_EEPROM_CTRL			0x000A
#घोषणा REG_EE_VPD						0x000C
#घोषणा REG_AFE_MISC					0x0010
#घोषणा REG_SPS0_CTRL					0x0011
#घोषणा REG_SPS0_CTRL_6					0x0016
#घोषणा REG_POWER_OFF_IN_PROCESS		0x0017
#घोषणा REG_SPS_OCP_CFG				0x0018
#घोषणा REG_RSV_CTRL					0x001C
#घोषणा REG_RF_CTRL						0x001F
#घोषणा REG_LDOA15_CTRL				0x0020
#घोषणा REG_LDOV12D_CTRL				0x0021
#घोषणा REG_LDOHCI12_CTRL				0x0022
#घोषणा REG_LPLDO_CTRL					0x0023
#घोषणा REG_AFE_XTAL_CTRL				0x0024
#घोषणा REG_AFE_LDO_CTRL				0x0027 /*  1.5v क्रम 8188EE test chip, 1.4v क्रम MP chip */
#घोषणा REG_AFE_PLL_CTRL				0x0028
#घोषणा REG_MAC_PHY_CTRL				0x002c /* क्रम 92d, DMDP, SMSP, DMSP contrl */
#घोषणा REG_APE_PLL_CTRL_EXT			0x002c
#घोषणा REG_EFUSE_CTRL					0x0030
#घोषणा REG_EFUSE_TEST					0x0034
#घोषणा REG_PWR_DATA					0x0038
#घोषणा REG_CAL_TIMER					0x003C
#घोषणा REG_ACLK_MON					0x003E
#घोषणा REG_GPIO_MUXCFG				0x0040
#घोषणा REG_GPIO_IO_SEL					0x0042
#घोषणा REG_MAC_PINMUX_CFG			0x0043
#घोषणा REG_GPIO_PIN_CTRL				0x0044
#घोषणा REG_GPIO_INTM					0x0048
#घोषणा REG_LEDCFG0						0x004C
#घोषणा REG_LEDCFG1						0x004D
#घोषणा REG_LEDCFG2						0x004E
#घोषणा REG_LEDCFG3						0x004F
#घोषणा REG_FSIMR						0x0050
#घोषणा REG_FSISR						0x0054
#घोषणा REG_HSIMR						0x0058
#घोषणा REG_HSISR						0x005c
#घोषणा REG_GPIO_PIN_CTRL_2			0x0060 /*  RTL8723 WIFI/BT/GPS Multi-Function GPIO Pin Control. */
#घोषणा REG_GPIO_IO_SEL_2				0x0062 /*  RTL8723 WIFI/BT/GPS Multi-Function GPIO Select. */
#घोषणा REG_MULTI_FUNC_CTRL			0x0068 /*  RTL8723 WIFI/BT/GPS Multi-Function control source. */
#घोषणा REG_GSSR						0x006c
#घोषणा REG_AFE_XTAL_CTRL_EXT			0x0078 /* RTL8188E */
#घोषणा REG_XCK_OUT_CTRL				0x007c /* RTL8188E */
#घोषणा REG_MCUFWDL					0x0080
#घोषणा REG_WOL_EVENT					0x0081 /* RTL8188E */
#घोषणा REG_MCUTSTCFG					0x0084
#घोषणा REG_FDHM0						0x0088
#घोषणा REG_HOST_SUSP_CNT				0x00BC	/*  RTL8192C Host suspend counter on FPGA platक्रमm */
#घोषणा REG_SYSTEM_ON_CTRL			0x00CC	/*  For 8723AE Reset after S3 */
#घोषणा REG_EFUSE_ACCESS				0x00CF	/*  Efuse access protection क्रम RTL8723 */
#घोषणा REG_BIST_SCAN					0x00D0
#घोषणा REG_BIST_RPT					0x00D4
#घोषणा REG_BIST_ROM_RPT				0x00D8
#घोषणा REG_USB_SIE_INTF				0x00E0
#घोषणा REG_PCIE_MIO_INTF				0x00E4
#घोषणा REG_PCIE_MIO_INTD				0x00E8
#घोषणा REG_HPON_FSM					0x00EC
#घोषणा REG_SYS_CFG						0x00F0
#घोषणा REG_GPIO_OUTSTS				0x00F4	/*  For RTL8723 only. */
#घोषणा REG_TYPE_ID						0x00FC

/*  */
/*  2010/12/29 MH Add क्रम 92D */
/*  */
#घोषणा REG_MAC_PHY_CTRL_NORMAL		0x00f8


/*  */
/*  */
/* 	0x0100h ~ 0x01FFh	MACTOP General Configuration */
/*  */
/*  */
#घोषणा REG_CR							0x0100
#घोषणा REG_PBP							0x0104
#घोषणा REG_PKT_BUFF_ACCESS_CTRL		0x0106
#घोषणा REG_TRXDMA_CTRL				0x010C
#घोषणा REG_TRXFF_BNDY					0x0114
#घोषणा REG_TRXFF_STATUS				0x0118
#घोषणा REG_RXFF_PTR					0x011C
#घोषणा REG_HIMR						0x0120
#घोषणा REG_HISR						0x0124
#घोषणा REG_HIMRE						0x0128
#घोषणा REG_HISRE						0x012C
#घोषणा REG_CPWM						0x012F
#घोषणा REG_FWIMR						0x0130
#घोषणा REG_FWISR						0x0134
#घोषणा REG_FTIMR						0x0138
#घोषणा REG_FTISR						0x013C /* RTL8192C */
#घोषणा REG_PKTBUF_DBG_CTRL			0x0140
#घोषणा REG_RXPKTBUF_CTRL				(REG_PKTBUF_DBG_CTRL+2)
#घोषणा REG_PKTBUF_DBG_DATA_L			0x0144
#घोषणा REG_PKTBUF_DBG_DATA_H		0x0148

#घोषणा REG_TC0_CTRL					0x0150
#घोषणा REG_TC1_CTRL					0x0154
#घोषणा REG_TC2_CTRL					0x0158
#घोषणा REG_TC3_CTRL					0x015C
#घोषणा REG_TC4_CTRL					0x0160
#घोषणा REG_TCUNIT_BASE				0x0164
#घोषणा REG_MBIST_START				0x0174
#घोषणा REG_MBIST_DONE					0x0178
#घोषणा REG_MBIST_FAIL					0x017C
#घोषणा REG_32K_CTRL					0x0194 /* RTL8188E */
#घोषणा REG_C2HEVT_MSG_NORMAL		0x01A0
#घोषणा REG_C2HEVT_CLEAR				0x01AF
#घोषणा REG_MCUTST_1					0x01c0
#घोषणा REG_MCUTST_WOWLAN			0x01C7	/*  Defined after 8188E series. */
#घोषणा REG_FMETHR						0x01C8
#घोषणा REG_HMETFR						0x01CC
#घोषणा REG_HMEBOX_0					0x01D0
#घोषणा REG_HMEBOX_1					0x01D4
#घोषणा REG_HMEBOX_2					0x01D8
#घोषणा REG_HMEBOX_3					0x01DC
#घोषणा REG_LLT_INIT					0x01E0


/*  */
/*  */
/* 	0x0200h ~ 0x027Fh	TXDMA Configuration */
/*  */
/*  */
#घोषणा REG_RQPN						0x0200
#घोषणा REG_FIFOPAGE					0x0204
#घोषणा REG_TDECTRL						0x0208
#घोषणा REG_TXDMA_OFFSET_CHK			0x020C
#घोषणा REG_TXDMA_STATUS				0x0210
#घोषणा REG_RQPN_NPQ					0x0214
#घोषणा REG_AUTO_LLT					0x0224


/*  */
/*  */
/* 	0x0280h ~ 0x02FFh	RXDMA Configuration */
/*  */
/*  */
#घोषणा REG_RXDMA_AGG_PG_TH			0x0280
#घोषणा REG_RXPKT_NUM					0x0284
#घोषणा REG_RXDMA_STATUS				0x0288

/*  */
/*  */
/* 	0x0300h ~ 0x03FFh	PCIe */
/*  */
/*  */
#घोषणा REG_PCIE_CTRL_REG				0x0300
#घोषणा REG_INT_MIG						0x0304	/*  Interrupt Migration */
#घोषणा REG_BCNQ_DESA					0x0308	/*  TX Beacon Descriptor Address */
#घोषणा REG_HQ_DESA					0x0310	/*  TX High Queue Descriptor Address */
#घोषणा REG_MGQ_DESA					0x0318	/*  TX Manage Queue Descriptor Address */
#घोषणा REG_VOQ_DESA					0x0320	/*  TX VO Queue Descriptor Address */
#घोषणा REG_VIQ_DESA					0x0328	/*  TX VI Queue Descriptor Address */
#घोषणा REG_BEQ_DESA					0x0330	/*  TX BE Queue Descriptor Address */
#घोषणा REG_BKQ_DESA					0x0338	/*  TX BK Queue Descriptor Address */
#घोषणा REG_RX_DESA						0x0340	/*  RX Queue	Descriptor Address */
/* sherry added क्रम DBI Read/Write  20091126 */
#घोषणा REG_DBI_WDATA					0x0348	/*  Backकरोor REG क्रम Access Configuration */
#घोषणा REG_DBI_RDATA				0x034C	/* Backकरोor REG क्रम Access Configuration */
#घोषणा REG_DBI_CTRL					0x0350	/* Backकरोor REG क्रम Access Configuration */
#घोषणा REG_DBI_FLAG					0x0352	/* Backकरोor REG क्रम Access Configuration */
#घोषणा REG_MDIO						0x0354	/*  MDIO क्रम Access PCIE PHY */
#घोषणा REG_DBG_SEL						0x0360	/*  Debug Selection Register */
#घोषणा REG_PCIE_HRPWM					0x0361	/* PCIe RPWM */
#घोषणा REG_PCIE_HCPWM					0x0363	/* PCIe CPWM */
#घोषणा REG_WATCH_DOG					0x0368

/*  RTL8723 series ------------------------------- */
#घोषणा REG_PCIE_HISR_EN				0x0394	/* PCIE Local Interrupt Enable Register */
#घोषणा REG_PCIE_HISR					0x03A0
#घोषणा REG_PCIE_HISRE					0x03A4
#घोषणा REG_PCIE_HIMR					0x03A8
#घोषणा REG_PCIE_HIMRE					0x03AC

#घोषणा REG_USB_HIMR					0xFE38
#घोषणा REG_USB_HIMRE					0xFE3C
#घोषणा REG_USB_HISR					0xFE78
#घोषणा REG_USB_HISRE					0xFE7C


/*  */
/*  */
/* 	0x0400h ~ 0x047Fh	Protocol Configuration */
/*  */
/*  */
#घोषणा REG_VOQ_INFORMATION			0x0400
#घोषणा REG_VIQ_INFORMATION			0x0404
#घोषणा REG_BEQ_INFORMATION			0x0408
#घोषणा REG_BKQ_INFORMATION			0x040C
#घोषणा REG_MGQ_INFORMATION			0x0410
#घोषणा REG_HGQ_INFORMATION			0x0414
#घोषणा REG_BCNQ_INFORMATION			0x0418
#घोषणा REG_TXPKT_EMPTY				0x041A
#घोषणा REG_CPU_MGQ_INFORMATION		0x041C
#घोषणा REG_FWHW_TXQ_CTRL				0x0420
#घोषणा REG_HWSEQ_CTRL					0x0423
#घोषणा REG_BCNQ_BDNY					0x0424
#घोषणा REG_MGQ_BDNY					0x0425
#घोषणा REG_LIFETIME_CTRL				0x0426
#घोषणा REG_MULTI_BCNQ_OFFSET			0x0427
#घोषणा REG_SPEC_SIFS					0x0428
#घोषणा REG_RL							0x042A
#घोषणा REG_DARFRC						0x0430
#घोषणा REG_RARFRC						0x0438
#घोषणा REG_RRSR						0x0440
#घोषणा REG_ARFR0						0x0444
#घोषणा REG_ARFR1						0x0448
#घोषणा REG_ARFR2						0x044C
#घोषणा REG_ARFR3						0x0450
#घोषणा REG_BCNQ1_BDNY					0x0457

#घोषणा REG_AGGLEN_LMT					0x0458
#घोषणा REG_AMPDU_MIN_SPACE			0x045C
#घोषणा REG_WMAC_LBK_BF_HD			0x045D
#घोषणा REG_FAST_EDCA_CTRL				0x0460
#घोषणा REG_RD_RESP_PKT_TH				0x0463

#घोषणा REG_INIRTS_RATE_SEL				0x0480
#घोषणा REG_INIDATA_RATE_SEL			0x0484

#घोषणा REG_POWER_STAGE1				0x04B4
#घोषणा REG_POWER_STAGE2				0x04B8
#घोषणा REG_PKT_VO_VI_LIFE_TIME		0x04C0
#घोषणा REG_PKT_BE_BK_LIFE_TIME		0x04C2
#घोषणा REG_STBC_SETTING				0x04C4
#घोषणा REG_QUEUE_CTRL					0x04C6
#घोषणा REG_SINGLE_AMPDU_CTRL			0x04c7
#घोषणा REG_PROT_MODE_CTRL			0x04C8
#घोषणा REG_MAX_AGGR_NUM				0x04CA
#घोषणा REG_RTS_MAX_AGGR_NUM			0x04CB
#घोषणा REG_BAR_MODE_CTRL				0x04CC
#घोषणा REG_RA_TRY_RATE_AGG_LMT		0x04CF
#घोषणा REG_EARLY_MODE_CONTROL		0x04D0
#घोषणा REG_MACID_SLEEP				0x04D4
#घोषणा REG_NQOS_SEQ					0x04DC
#घोषणा REG_QOS_SEQ					0x04DE
#घोषणा REG_NEED_CPU_HANDLE			0x04E0
#घोषणा REG_PKT_LOSE_RPT				0x04E1
#घोषणा REG_PTCL_ERR_STATUS			0x04E2
#घोषणा REG_TX_RPT_CTRL					0x04EC
#घोषणा REG_TX_RPT_TIME					0x04F0	/*  2 byte */
#घोषणा REG_DUMMY						0x04FC

/*  */
/*  */
/* 	0x0500h ~ 0x05FFh	EDCA Configuration */
/*  */
/*  */
#घोषणा REG_EDCA_VO_PARAM				0x0500
#घोषणा REG_EDCA_VI_PARAM				0x0504
#घोषणा REG_EDCA_BE_PARAM				0x0508
#घोषणा REG_EDCA_BK_PARAM				0x050C
#घोषणा REG_BCNTCFG						0x0510
#घोषणा REG_PIFS							0x0512
#घोषणा REG_RDG_PIFS					0x0513
#घोषणा REG_SIFS_CTX					0x0514
#घोषणा REG_SIFS_TRX					0x0516
#घोषणा REG_TSFTR_SYN_OFFSET			0x0518
#घोषणा REG_AGGR_BREAK_TIME			0x051A
#घोषणा REG_SLOT						0x051B
#घोषणा REG_TX_PTCL_CTRL				0x0520
#घोषणा REG_TXPAUSE						0x0522
#घोषणा REG_DIS_TXREQ_CLR				0x0523
#घोषणा REG_RD_CTRL						0x0524
/*  */
/*  Format क्रम offset 540h-542h: */
/* 	[3:0]:   TBTT prohibit setup in unit of 32us. The समय क्रम HW getting beacon content beक्रमe TBTT. */
/* 	[7:4]:   Reserved. */
/* 	[19:8]:  TBTT prohibit hold in unit of 32us. The समय क्रम HW holding to send the beacon packet. */
/* 	[23:20]: Reserved */
/*  Description: */
/* 	              | */
/*      |<--Setup--|--Hold------------>| */
/* 	--------------|---------------------- */
/*                 | */
/*                TBTT */
/*  Note: We cannot update beacon content to HW or send any AC packets during the समय between Setup and Hold. */
/*  Described by Designer Tim and Bruce, 2011-01-14. */
/*  */
#घोषणा REG_TBTT_PROHIBIT				0x0540
#घोषणा REG_RD_NAV_NXT					0x0544
#घोषणा REG_NAV_PROT_LEN				0x0546
#घोषणा REG_BCN_CTRL					0x0550
#घोषणा REG_BCN_CTRL_1					0x0551
#घोषणा REG_MBID_NUM					0x0552
#घोषणा REG_DUAL_TSF_RST				0x0553
#घोषणा REG_BCN_INTERVAL				0x0554	/*  The same as REG_MBSSID_BCN_SPACE */
#घोषणा REG_DRVERLYINT					0x0558
#घोषणा REG_BCNDMATIM					0x0559
#घोषणा REG_ATIMWND					0x055A
#घोषणा REG_USTIME_TSF					0x055C
#घोषणा REG_BCN_MAX_ERR				0x055D
#घोषणा REG_RXTSF_OFFSET_CCK			0x055E
#घोषणा REG_RXTSF_OFFSET_OFDM			0x055F
#घोषणा REG_TSFTR						0x0560
#घोषणा REG_TSFTR1						0x0568	/*  HW Port 1 TSF Register */
#घोषणा REG_ATIMWND_1					0x0570
#घोषणा REG_P2P_CTWIN					0x0572 /*  1 Byte दीर्घ (in unit of TU) */
#घोषणा REG_PSTIMER						0x0580
#घोषणा REG_TIMER0						0x0584
#घोषणा REG_TIMER1						0x0588
#घोषणा REG_ACMHWCTRL					0x05C0
#घोषणा REG_NOA_DESC_SEL				0x05CF
#घोषणा REG_NOA_DESC_DURATION		0x05E0
#घोषणा REG_NOA_DESC_INTERVAL			0x05E4
#घोषणा REG_NOA_DESC_START			0x05E8
#घोषणा REG_NOA_DESC_COUNT			0x05EC

#घोषणा REG_DMC							0x05F0	/* Dual MAC Co-Existence Register */
#घोषणा REG_SCH_TX_CMD					0x05F8

#घोषणा REG_FW_RESET_TSF_CNT_1		0x05FC
#घोषणा REG_FW_RESET_TSF_CNT_0		0x05FD
#घोषणा REG_FW_BCN_DIS_CNT			0x05FE

/*  */
/*  */
/* 	0x0600h ~ 0x07FFh	WMAC Configuration */
/*  */
/*  */
#घोषणा REG_APSD_CTRL					0x0600
#घोषणा REG_BWOPMODE					0x0603
#घोषणा REG_TCR							0x0604
#घोषणा REG_RCR							0x0608
#घोषणा REG_RX_PKT_LIMIT				0x060C
#घोषणा REG_RX_DLK_TIME				0x060D
#घोषणा REG_RX_DRVINFO_SZ				0x060F

#घोषणा REG_MACID						0x0610
#घोषणा REG_BSSID						0x0618
#घोषणा REG_MAR							0x0620
#घोषणा REG_MBIDCAMCFG					0x0628

#घोषणा REG_PNO_STATUS					0x0631
#घोषणा REG_USTIME_EDCA				0x0638
#घोषणा REG_MAC_SPEC_SIFS				0x063A
/*  20100719 Joseph: Hardware रेजिस्टर definition change. (HW datasheet v54) */
#घोषणा REG_RESP_SIFS_CCK				0x063C	/*  [15:8]SIFS_R2T_OFDM, [7:0]SIFS_R2T_CCK */
#घोषणा REG_RESP_SIFS_OFDM                    0x063E	/*  [15:8]SIFS_T2T_OFDM, [7:0]SIFS_T2T_CCK */

#घोषणा REG_ACKTO						0x0640
#घोषणा REG_CTS2TO						0x0641
#घोषणा REG_EIFS							0x0642


/* RXERR_RPT */
#घोषणा RXERR_TYPE_OFDM_PPDU			0
#घोषणा RXERR_TYPE_OFDMfalse_ALARM	1
#घोषणा RXERR_TYPE_OFDM_MPDU_OK			2
#घोषणा RXERR_TYPE_OFDM_MPDU_FAIL	3
#घोषणा RXERR_TYPE_CCK_PPDU			4
#घोषणा RXERR_TYPE_CCKfalse_ALARM	5
#घोषणा RXERR_TYPE_CCK_MPDU_OK		6
#घोषणा RXERR_TYPE_CCK_MPDU_FAIL		7
#घोषणा RXERR_TYPE_HT_PPDU				8
#घोषणा RXERR_TYPE_HTfalse_ALARM	9
#घोषणा RXERR_TYPE_HT_MPDU_TOTAL		10
#घोषणा RXERR_TYPE_HT_MPDU_OK			11
#घोषणा RXERR_TYPE_HT_MPDU_FAIL			12
#घोषणा RXERR_TYPE_RX_FULL_DROP			15

#घोषणा RXERR_COUNTER_MASK			0xFFFFF
#घोषणा RXERR_RPT_RST					BIT(27)
#घोषणा _RXERR_RPT_SEL(type)			((type) << 28)

/*  */
/*  Note: */
/* 	The NAV upper value is very important to WiFi 11n 5.2.3 NAV test. The शेष value is */
/* 	always too small, but the WiFi TestPlan test by 25, 000 microseconds of NAV through sending */
/* 	CTS in the air. We must update this value greater than 25, 000 microseconds to pass the item. */
/* 	The offset of NAV_UPPER in 8192C Spec is incorrect, and the offset should be 0x0652. Commented */
/* 	by SD1 Scott. */
/*  By Bruce, 2011-07-18. */
/*  */
#घोषणा REG_NAV_UPPER					0x0652	/*  unit of 128 */

/* WMA, BA, CCX */
#घोषणा REG_NAV_CTRL					0x0650
#घोषणा REG_BACAMCMD					0x0654
#घोषणा REG_BACAMCONTENT				0x0658
#घोषणा REG_LBDLY						0x0660
#घोषणा REG_FWDLY						0x0661
#घोषणा REG_RXERR_RPT					0x0664
#घोषणा REG_WMAC_TRXPTCL_CTL			0x0668

/*  Security */
#घोषणा REG_CAMCMD						0x0670
#घोषणा REG_CAMWRITE					0x0674
#घोषणा REG_CAMREAD					0x0678
#घोषणा REG_CAMDBG						0x067C
#घोषणा REG_SECCFG						0x0680

/*  Power */
#घोषणा REG_WOW_CTRL					0x0690
#घोषणा REG_PS_RX_INFO					0x0692
#घोषणा REG_UAPSD_TID					0x0693
#घोषणा REG_WKFMCAM_CMD				0x0698
#घोषणा REG_WKFMCAM_NUM				REG_WKFMCAM_CMD
#घोषणा REG_WKFMCAM_RWD				0x069C
#घोषणा REG_RXFLTMAP0					0x06A0
#घोषणा REG_RXFLTMAP1					0x06A2
#घोषणा REG_RXFLTMAP2					0x06A4
#घोषणा REG_BCN_PSR_RPT				0x06A8
#घोषणा REG_BT_COEX_TABLE				0x06C0

/*  Hardware Port 2 */
#घोषणा REG_MACID1						0x0700
#घोषणा REG_BSSID1						0x0708


/*  */
/*  */
/* 	0xFE00h ~ 0xFE55h	USB Configuration */
/*  */
/*  */
#घोषणा REG_USB_INFO					0xFE17
#घोषणा REG_USB_SPECIAL_OPTION		0xFE55
#घोषणा REG_USB_DMA_AGG_TO			0xFE5B
#घोषणा REG_USB_AGG_TO					0xFE5C
#घोषणा REG_USB_AGG_TH					0xFE5D

#घोषणा REG_USB_HRPWM					0xFE58
#घोषणा REG_USB_HCPWM					0xFE57

/*  क्रम 92DU high_Queue low_Queue Normal_Queue select */
#घोषणा REG_USB_High_NORMAL_Queue_Select_MAC0	0xFE44
/* define REG_USB_LOW_Queue_Select_MAC0		0xFE45 */
#घोषणा REG_USB_High_NORMAL_Queue_Select_MAC1	0xFE47
/* define REG_USB_LOW_Queue_Select_MAC1		0xFE48 */

/*  For test chip */
#घोषणा REG_TEST_USB_TXQS				0xFE48
#घोषणा REG_TEST_SIE_VID				0xFE60		/*  0xFE60~0xFE61 */
#घोषणा REG_TEST_SIE_PID				0xFE62		/*  0xFE62~0xFE63 */
#घोषणा REG_TEST_SIE_OPTIONAL			0xFE64
#घोषणा REG_TEST_SIE_CHIRP_K			0xFE65
#घोषणा REG_TEST_SIE_PHY				0xFE66		/*  0xFE66~0xFE6B */
#घोषणा REG_TEST_SIE_MAC_ADDR			0xFE70		/*  0xFE70~0xFE75 */
#घोषणा REG_TEST_SIE_STRING			0xFE80		/*  0xFE80~0xFEB9 */


/*  For normal chip */
#घोषणा REG_NORMAL_SIE_VID				0xFE60		/*  0xFE60~0xFE61 */
#घोषणा REG_NORMAL_SIE_PID				0xFE62		/*  0xFE62~0xFE63 */
#घोषणा REG_NORMAL_SIE_OPTIONAL		0xFE64
#घोषणा REG_NORMAL_SIE_EP				0xFE65		/*  0xFE65~0xFE67 */
#घोषणा REG_NORMAL_SIE_PHY			0xFE68		/*  0xFE68~0xFE6B */
#घोषणा REG_NORMAL_SIE_OPTIONAL2		0xFE6C
#घोषणा REG_NORMAL_SIE_GPS_EP			0xFE6D		/*  0xFE6D, क्रम RTL8723 only. */
#घोषणा REG_NORMAL_SIE_MAC_ADDR		0xFE70		/*  0xFE70~0xFE75 */
#घोषणा REG_NORMAL_SIE_STRING			0xFE80		/*  0xFE80~0xFEDF */


/*  */
/*  */
/* 	Redअगरine 8192C रेजिस्टर definition क्रम compatibility */
/*  */
/*  */

/*  TODO: use these definition when using REG_xxx naming rule. */
/*  NOTE: DO NOT Remove these definition. Use later. */

#घोषणा EFUSE_CTRL				REG_EFUSE_CTRL		/*  E-Fuse Control. */
#घोषणा EFUSE_TEST				REG_EFUSE_TEST		/*  E-Fuse Test. */
#घोषणा MSR						(REG_CR + 2)		/*  Media Status रेजिस्टर */
/* define ISR						REG_HISR */

#घोषणा TSFR						REG_TSFTR			/*  Timing Sync Function Timer Register. */
#घोषणा TSFR1					REG_TSFTR1			/*  HW Port 1 TSF Register */

#घोषणा PBP						REG_PBP

/*  Redअगरine MACID रेजिस्टर, to compatible prior ICs. */
#घोषणा IDR0						REG_MACID			/*  MAC ID Register, Offset 0x0050-0x0053 */
#घोषणा IDR4						(REG_MACID + 4)		/*  MAC ID Register, Offset 0x0054-0x0055 */


/*  */
/*  9. Security Control Registers	(Offset:) */
/*  */
#घोषणा RWCAM					REG_CAMCMD		/* IN 8190 Data Sheet is called CAMcmd */
#घोषणा WCAMI					REG_CAMWRITE	/*  Software ग_लिखो CAM input content */
#घोषणा RCAMO					REG_CAMREAD		/*  Software पढ़ो/ग_लिखो CAM config */
#घोषणा CAMDBG					REG_CAMDBG
#घोषणा SECR						REG_SECCFG		/* Security Configuration Register */

/*  Unused रेजिस्टर */
#घोषणा UnusedRegister			0x1BF
#घोषणा DCAM					UnusedRegister
#घोषणा PSR						UnusedRegister
#घोषणा BBAddr					UnusedRegister
#घोषणा PhyDataR					UnusedRegister

/*  Min Spacing related settings. */
#घोषणा MAX_MSS_DENSITY_2T			0x13
#घोषणा MAX_MSS_DENSITY_1T			0x0A

/*  */
/*        8192C Cmd9346CR bits					(Offset 0xA, 16bit) */
/*  */
#घोषणा CmdEEPROM_En				BIT5	 /*  EEPROM enable when set 1 */
#घोषणा CmdEERPOMSEL				BIT4	/*  System EEPROM select, 0: boot from E-FUSE, 1: The EEPROM used is 9346 */
#घोषणा Cmd9346CR_9356SEL			BIT4

/*  */
/*        8192C GPIO MUX Configuration Register (offset 0x40, 4 byte) */
/*  */
#घोषणा GPIOSEL_GPIO				0
#घोषणा GPIOSEL_ENBT				BIT5

/*  */
/*        8192C GPIO PIN Control Register (offset 0x44, 4 byte) */
/*  */
#घोषणा GPIO_IN					REG_GPIO_PIN_CTRL		/*  GPIO pins input value */
#घोषणा GPIO_OUT				(REG_GPIO_PIN_CTRL+1)	/*  GPIO pins output value */
#घोषणा GPIO_IO_SEL				(REG_GPIO_PIN_CTRL+2)	/*  GPIO pins output enable when a bit is set to "1"; otherwise, input is configured. */
#घोषणा GPIO_MOD				(REG_GPIO_PIN_CTRL+3)

/*  */
/*        8811A GPIO PIN Control Register (offset 0x60, 4 byte) */
/*  */
#घोषणा GPIO_IN_8811A			REG_GPIO_PIN_CTRL_2		/*  GPIO pins input value */
#घोषणा GPIO_OUT_8811A			(REG_GPIO_PIN_CTRL_2+1)	/*  GPIO pins output value */
#घोषणा GPIO_IO_SEL_8811A		(REG_GPIO_PIN_CTRL_2+2)	/*  GPIO pins output enable when a bit is set to "1"; otherwise, input is configured. */
#घोषणा GPIO_MOD_8811A			(REG_GPIO_PIN_CTRL_2+3)

/*  */
/*        8723/8188E Host System Interrupt Mask Register (offset 0x58, 32 byte) */
/*  */
#घोषणा HSIMR_GPIO12_0_INT_EN			BIT0
#घोषणा HSIMR_SPS_OCP_INT_EN			BIT5
#घोषणा HSIMR_RON_INT_EN				BIT6
#घोषणा HSIMR_PDN_INT_EN				BIT7
#घोषणा HSIMR_GPIO9_INT_EN				BIT25

/*  */
/*        8723/8188E Host System Interrupt Status Register (offset 0x5C, 32 byte) */
/*  */
#घोषणा HSISR_GPIO12_0_INT				BIT0
#घोषणा HSISR_SPS_OCP_INT				BIT5
#घोषणा HSISR_RON_INT					BIT6
#घोषणा HSISR_PDNINT					BIT7
#घोषणा HSISR_GPIO9_INT					BIT25

/*  */
/*        8192C (MSR) Media Status Register	(Offset 0x4C, 8 bits) */
/*  */
/*
Network Type
00: No link
01: Link in ad hoc network
10: Link in infraकाष्ठाure network
11: AP mode
Default: 00b.
*/
#घोषणा MSR_NOLINK				0x00
#घोषणा MSR_ADHOC				0x01
#घोषणा MSR_INFRA				0x02
#घोषणा MSR_AP					0x03

/*  */
/*        USB INTR CONTENT */
/*  */
#घोषणा USB_C2H_CMDID_OFFSET					0
#घोषणा USB_C2H_SEQ_OFFSET					1
#घोषणा USB_C2H_EVENT_OFFSET					2
#घोषणा USB_INTR_CPWM_OFFSET					16
#घोषणा USB_INTR_CONTENT_C2H_OFFSET			0
#घोषणा USB_INTR_CONTENT_CPWM1_OFFSET		16
#घोषणा USB_INTR_CONTENT_CPWM2_OFFSET		20
#घोषणा USB_INTR_CONTENT_HISR_OFFSET			48
#घोषणा USB_INTR_CONTENT_HISRE_OFFSET		52
#घोषणा USB_INTR_CONTENT_LENGTH				56

/*  */
/*        Response Rate Set Register	(offset 0x440, 24bits) */
/*  */
#घोषणा RRSR_1M					BIT0
#घोषणा RRSR_2M					BIT1
#घोषणा RRSR_5_5M				BIT2
#घोषणा RRSR_11M				BIT3
#घोषणा RRSR_6M					BIT4
#घोषणा RRSR_9M					BIT5
#घोषणा RRSR_12M				BIT6
#घोषणा RRSR_18M				BIT7
#घोषणा RRSR_24M				BIT8
#घोषणा RRSR_36M				BIT9
#घोषणा RRSR_48M				BIT10
#घोषणा RRSR_54M				BIT11
#घोषणा RRSR_MCS0				BIT12
#घोषणा RRSR_MCS1				BIT13
#घोषणा RRSR_MCS2				BIT14
#घोषणा RRSR_MCS3				BIT15
#घोषणा RRSR_MCS4				BIT16
#घोषणा RRSR_MCS5				BIT17
#घोषणा RRSR_MCS6				BIT18
#घोषणा RRSR_MCS7				BIT19

#घोषणा RRSR_CCK_RATES (RRSR_11M|RRSR_5_5M|RRSR_2M|RRSR_1M)
#घोषणा RRSR_OFDM_RATES (RRSR_54M|RRSR_48M|RRSR_36M|RRSR_24M|RRSR_18M|RRSR_12M|RRSR_9M|RRSR_6M)

/*  WOL bit inक्रमmation */
#घोषणा HAL92C_WOL_PTK_UPDATE_EVENT		BIT0
#घोषणा HAL92C_WOL_GTK_UPDATE_EVENT		BIT1
#घोषणा HAL92C_WOL_DISASSOC_EVENT		BIT2
#घोषणा HAL92C_WOL_DEAUTH_EVENT			BIT3
#घोषणा HAL92C_WOL_FW_DISCONNECT_EVENT	BIT4

/*  */
/*        Rate Definition */
/*  */
/* CCK */
#घोषणा	RATR_1M					0x00000001
#घोषणा	RATR_2M					0x00000002
#घोषणा	RATR_55M					0x00000004
#घोषणा	RATR_11M					0x00000008
/* OFDM */
#घोषणा	RATR_6M					0x00000010
#घोषणा	RATR_9M					0x00000020
#घोषणा	RATR_12M					0x00000040
#घोषणा	RATR_18M					0x00000080
#घोषणा	RATR_24M					0x00000100
#घोषणा	RATR_36M					0x00000200
#घोषणा	RATR_48M					0x00000400
#घोषणा	RATR_54M					0x00000800
/* MCS 1 Spatial Stream */
#घोषणा	RATR_MCS0					0x00001000
#घोषणा	RATR_MCS1					0x00002000
#घोषणा	RATR_MCS2					0x00004000
#घोषणा	RATR_MCS3					0x00008000
#घोषणा	RATR_MCS4					0x00010000
#घोषणा	RATR_MCS5					0x00020000
#घोषणा	RATR_MCS6					0x00040000
#घोषणा	RATR_MCS7					0x00080000
/* MCS 2 Spatial Stream */
#घोषणा	RATR_MCS8					0x00100000
#घोषणा	RATR_MCS9					0x00200000
#घोषणा	RATR_MCS10					0x00400000
#घोषणा	RATR_MCS11					0x00800000
#घोषणा	RATR_MCS12					0x01000000
#घोषणा	RATR_MCS13					0x02000000
#घोषणा	RATR_MCS14					0x04000000
#घोषणा	RATR_MCS15					0x08000000

/* CCK */
#घोषणा RATE_1M					BIT(0)
#घोषणा RATE_2M					BIT(1)
#घोषणा RATE_5_5M				BIT(2)
#घोषणा RATE_11M				BIT(3)
/* OFDM */
#घोषणा RATE_6M					BIT(4)
#घोषणा RATE_9M					BIT(5)
#घोषणा RATE_12M				BIT(6)
#घोषणा RATE_18M				BIT(7)
#घोषणा RATE_24M				BIT(8)
#घोषणा RATE_36M				BIT(9)
#घोषणा RATE_48M				BIT(10)
#घोषणा RATE_54M				BIT(11)
/* MCS 1 Spatial Stream */
#घोषणा RATE_MCS0				BIT(12)
#घोषणा RATE_MCS1				BIT(13)
#घोषणा RATE_MCS2				BIT(14)
#घोषणा RATE_MCS3				BIT(15)
#घोषणा RATE_MCS4				BIT(16)
#घोषणा RATE_MCS5				BIT(17)
#घोषणा RATE_MCS6				BIT(18)
#घोषणा RATE_MCS7				BIT(19)
/* MCS 2 Spatial Stream */
#घोषणा RATE_MCS8				BIT(20)
#घोषणा RATE_MCS9				BIT(21)
#घोषणा RATE_MCS10				BIT(22)
#घोषणा RATE_MCS11				BIT(23)
#घोषणा RATE_MCS12				BIT(24)
#घोषणा RATE_MCS13				BIT(25)
#घोषणा RATE_MCS14				BIT(26)
#घोषणा RATE_MCS15				BIT(27)


/*  ALL CCK Rate */
#घोषणा RATE_BITMAP_ALL			0xFFFFF

/*  Only use CCK 1M rate क्रम ACK */
#घोषणा RATE_RRSR_CCK_ONLY_1M		0xFFFF1
#घोषणा RATE_RRSR_WITHOUT_CCK		0xFFFF0

/*  */
/*        BW_OPMODE bits				(Offset 0x603, 8bit) */
/*  */
#घोषणा BW_OPMODE_20MHZ			BIT2
#घोषणा BW_OPMODE_5G				BIT1

/*  */
/*        CAM Config Setting (offset 0x680, 1 byte) */
/*  */
#घोषणा CAM_VALID				BIT15
#घोषणा CAM_NOTVALID			0x0000
#घोषणा CAM_USEDK				BIT5

#घोषणा CAM_CONTENT_COUNT	8

#घोषणा CAM_NONE				0x0
#घोषणा CAM_WEP40				0x01
#घोषणा CAM_TKIP				0x02
#घोषणा CAM_AES					0x04
#घोषणा CAM_WEP104				0x05
#घोषणा CAM_SMS4				0x6

#घोषणा TOTAL_CAM_ENTRY		32
#घोषणा HALF_CAM_ENTRY			16

#घोषणा CAM_CONFIG_USEDK		true
#घोषणा CAM_CONFIG_NO_USEDK	false

#घोषणा CAM_WRITE				BIT16
#घोषणा CAM_READ				0x00000000
#घोषणा CAM_POLLINIG			BIT31

/*  */
/*  10. Power Save Control Registers */
/*  */
#घोषणा WOW_PMEN				BIT0 /*  Power management Enable. */
#घोषणा WOW_WOMEN				BIT1 /*  WoW function on or off. */
#घोषणा WOW_MAGIC				BIT2 /*  Magic packet */
#घोषणा WOW_UWF				BIT3 /*  Unicast Wakeup frame. */

/*  */
/*  12. Host Interrupt Status Registers */
/*  */
/*  */
/*       8190 IMR/ISR bits */
/*  */
#घोषणा IMR8190_DISABLED		0x0
#घोषणा IMR_DISABLED			0x0
/*  IMR DW0 Bit 0-31 */
#घोषणा IMR_BCNDMAINT6			BIT31		/*  Beacon DMA Interrupt 6 */
#घोषणा IMR_BCNDMAINT5			BIT30		/*  Beacon DMA Interrupt 5 */
#घोषणा IMR_BCNDMAINT4			BIT29		/*  Beacon DMA Interrupt 4 */
#घोषणा IMR_BCNDMAINT3			BIT28		/*  Beacon DMA Interrupt 3 */
#घोषणा IMR_BCNDMAINT2			BIT27		/*  Beacon DMA Interrupt 2 */
#घोषणा IMR_BCNDMAINT1			BIT26		/*  Beacon DMA Interrupt 1 */
#घोषणा IMR_BCNDOK8				BIT25		/*  Beacon Queue DMA OK Interrupt 8 */
#घोषणा IMR_BCNDOK7				BIT24		/*  Beacon Queue DMA OK Interrupt 7 */
#घोषणा IMR_BCNDOK6				BIT23		/*  Beacon Queue DMA OK Interrupt 6 */
#घोषणा IMR_BCNDOK5				BIT22		/*  Beacon Queue DMA OK Interrupt 5 */
#घोषणा IMR_BCNDOK4				BIT21		/*  Beacon Queue DMA OK Interrupt 4 */
#घोषणा IMR_BCNDOK3				BIT20		/*  Beacon Queue DMA OK Interrupt 3 */
#घोषणा IMR_BCNDOK2				BIT19		/*  Beacon Queue DMA OK Interrupt 2 */
#घोषणा IMR_BCNDOK1				BIT18		/*  Beacon Queue DMA OK Interrupt 1 */
#घोषणा IMR_TIMEOUT2			BIT17		/*  Timeout पूर्णांकerrupt 2 */
#घोषणा IMR_TIMEOUT1			BIT16		/*  Timeout पूर्णांकerrupt 1 */
#घोषणा IMR_TXFOVW				BIT15		/*  Transmit FIFO Overflow */
#घोषणा IMR_PSTIMEOUT			BIT14		/*  Power save समय out पूर्णांकerrupt */
#घोषणा IMR_BcnInt				BIT13		/*  Beacon DMA Interrupt 0 */
#घोषणा IMR_RXFOVW				BIT12		/*  Receive FIFO Overflow */
#घोषणा IMR_RDU					BIT11		/*  Receive Descriptor Unavailable */
#घोषणा IMR_ATIMEND				BIT10		/*  For 92C, ATIM Winकरोw End Interrupt. For 8723 and later ICs, it also means P2P CTWin End पूर्णांकerrupt. */
#घोषणा IMR_BDOK				BIT9		/*  Beacon Queue DMA OK Interrupt */
#घोषणा IMR_HIGHDOK				BIT8		/*  High Queue DMA OK Interrupt */
#घोषणा IMR_TBDOK				BIT7		/*  Transmit Beacon OK पूर्णांकerrupt */
#घोषणा IMR_MGNTDOK			BIT6		/*  Management Queue DMA OK Interrupt */
#घोषणा IMR_TBDER				BIT5		/*  For 92C, Transmit Beacon Error Interrupt */
#घोषणा IMR_BKDOK				BIT4		/*  AC_BK DMA OK Interrupt */
#घोषणा IMR_BEDOK				BIT3		/*  AC_BE DMA OK Interrupt */
#घोषणा IMR_VIDOK				BIT2		/*  AC_VI DMA OK Interrupt */
#घोषणा IMR_VODOK				BIT1		/*  AC_VO DMA Interrupt */
#घोषणा IMR_ROK					BIT0		/*  Receive DMA OK Interrupt */

/*  13. Host Interrupt Status Extension Register	 (Offset: 0x012C-012Eh) */
#घोषणा IMR_TSF_BIT32_TOGGLE	BIT15
#घोषणा IMR_BcnInt_E				BIT12
#घोषणा IMR_TXERR				BIT11
#घोषणा IMR_RXERR				BIT10
#घोषणा IMR_C2HCMD				BIT9
#घोषणा IMR_CPWM				BIT8
/* RSVD [2-7] */
#घोषणा IMR_OCPINT				BIT1
#घोषणा IMR_WLANOFF			BIT0

/*  */
/*  8723E series PCIE Host IMR/ISR bit */
/*  */
/*  IMR DW0 Bit 0-31 */
#घोषणा PHIMR_TIMEOUT2				BIT31
#घोषणा PHIMR_TIMEOUT1				BIT30
#घोषणा PHIMR_PSTIMEOUT			BIT29
#घोषणा PHIMR_GTINT4				BIT28
#घोषणा PHIMR_GTINT3				BIT27
#घोषणा PHIMR_TXBCNERR				BIT26
#घोषणा PHIMR_TXBCNOK				BIT25
#घोषणा PHIMR_TSF_BIT32_TOGGLE	BIT24
#घोषणा PHIMR_BCNDMAINT3			BIT23
#घोषणा PHIMR_BCNDMAINT2			BIT22
#घोषणा PHIMR_BCNDMAINT1			BIT21
#घोषणा PHIMR_BCNDMAINT0			BIT20
#घोषणा PHIMR_BCNDOK3				BIT19
#घोषणा PHIMR_BCNDOK2				BIT18
#घोषणा PHIMR_BCNDOK1				BIT17
#घोषणा PHIMR_BCNDOK0				BIT16
#घोषणा PHIMR_HSISR_IND_ON			BIT15
#घोषणा PHIMR_BCNDMAINT_E			BIT14
#घोषणा PHIMR_ATIMEND_E			BIT13
#घोषणा PHIMR_ATIM_CTW_END		BIT12
#घोषणा PHIMR_HISRE_IND			BIT11	/*  RO. HISRE Indicator (HISRE & HIMRE is true, this bit is set to 1) */
#घोषणा PHIMR_C2HCMD				BIT10
#घोषणा PHIMR_CPWM2				BIT9
#घोषणा PHIMR_CPWM					BIT8
#घोषणा PHIMR_HIGHDOK				BIT7		/*  High Queue DMA OK Interrupt */
#घोषणा PHIMR_MGNTDOK				BIT6		/*  Management Queue DMA OK Interrupt */
#घोषणा PHIMR_BKDOK					BIT5		/*  AC_BK DMA OK Interrupt */
#घोषणा PHIMR_BEDOK					BIT4		/*  AC_BE DMA OK Interrupt */
#घोषणा PHIMR_VIDOK					BIT3		/*  AC_VI DMA OK Interrupt */
#घोषणा PHIMR_VODOK				BIT2		/*  AC_VO DMA Interrupt */
#घोषणा PHIMR_RDU					BIT1		/*  Receive Descriptor Unavailable */
#घोषणा PHIMR_ROK					BIT0		/*  Receive DMA OK Interrupt */

/*  PCIE Host Interrupt Status Extension bit */
#घोषणा PHIMR_BCNDMAINT7			BIT23
#घोषणा PHIMR_BCNDMAINT6			BIT22
#घोषणा PHIMR_BCNDMAINT5			BIT21
#घोषणा PHIMR_BCNDMAINT4			BIT20
#घोषणा PHIMR_BCNDOK7				BIT19
#घोषणा PHIMR_BCNDOK6				BIT18
#घोषणा PHIMR_BCNDOK5				BIT17
#घोषणा PHIMR_BCNDOK4				BIT16
/*  bit12 15: RSVD */
#घोषणा PHIMR_TXERR					BIT11
#घोषणा PHIMR_RXERR					BIT10
#घोषणा PHIMR_TXFOVW				BIT9
#घोषणा PHIMR_RXFOVW				BIT8
/*  bit2-7: RSVD */
#घोषणा PHIMR_OCPINT				BIT1
/*  bit0: RSVD */

#घोषणा UHIMR_TIMEOUT2				BIT31
#घोषणा UHIMR_TIMEOUT1				BIT30
#घोषणा UHIMR_PSTIMEOUT			BIT29
#घोषणा UHIMR_GTINT4				BIT28
#घोषणा UHIMR_GTINT3				BIT27
#घोषणा UHIMR_TXBCNERR				BIT26
#घोषणा UHIMR_TXBCNOK				BIT25
#घोषणा UHIMR_TSF_BIT32_TOGGLE	BIT24
#घोषणा UHIMR_BCNDMAINT3			BIT23
#घोषणा UHIMR_BCNDMAINT2			BIT22
#घोषणा UHIMR_BCNDMAINT1			BIT21
#घोषणा UHIMR_BCNDMAINT0			BIT20
#घोषणा UHIMR_BCNDOK3				BIT19
#घोषणा UHIMR_BCNDOK2				BIT18
#घोषणा UHIMR_BCNDOK1				BIT17
#घोषणा UHIMR_BCNDOK0				BIT16
#घोषणा UHIMR_HSISR_IND			BIT15
#घोषणा UHIMR_BCNDMAINT_E			BIT14
/* RSVD	BIT13 */
#घोषणा UHIMR_CTW_END				BIT12
/* RSVD	BIT11 */
#घोषणा UHIMR_C2HCMD				BIT10
#घोषणा UHIMR_CPWM2				BIT9
#घोषणा UHIMR_CPWM					BIT8
#घोषणा UHIMR_HIGHDOK				BIT7		/*  High Queue DMA OK Interrupt */
#घोषणा UHIMR_MGNTDOK				BIT6		/*  Management Queue DMA OK Interrupt */
#घोषणा UHIMR_BKDOK				BIT5		/*  AC_BK DMA OK Interrupt */
#घोषणा UHIMR_BEDOK				BIT4		/*  AC_BE DMA OK Interrupt */
#घोषणा UHIMR_VIDOK					BIT3		/*  AC_VI DMA OK Interrupt */
#घोषणा UHIMR_VODOK				BIT2		/*  AC_VO DMA Interrupt */
#घोषणा UHIMR_RDU					BIT1		/*  Receive Descriptor Unavailable */
#घोषणा UHIMR_ROK					BIT0		/*  Receive DMA OK Interrupt */

/*  USB Host Interrupt Status Extension bit */
#घोषणा UHIMR_BCNDMAINT7			BIT23
#घोषणा UHIMR_BCNDMAINT6			BIT22
#घोषणा UHIMR_BCNDMAINT5			BIT21
#घोषणा UHIMR_BCNDMAINT4			BIT20
#घोषणा UHIMR_BCNDOK7				BIT19
#घोषणा UHIMR_BCNDOK6				BIT18
#घोषणा UHIMR_BCNDOK5				BIT17
#घोषणा UHIMR_BCNDOK4				BIT16
/*  bit14-15: RSVD */
#घोषणा UHIMR_ATIMEND_E			BIT13
#घोषणा UHIMR_ATIMEND				BIT12
#घोषणा UHIMR_TXERR					BIT11
#घोषणा UHIMR_RXERR					BIT10
#घोषणा UHIMR_TXFOVW				BIT9
#घोषणा UHIMR_RXFOVW				BIT8
/*  bit2-7: RSVD */
#घोषणा UHIMR_OCPINT				BIT1
/*  bit0: RSVD */


#घोषणा HAL_NIC_UNPLUG_ISR			0xFFFFFFFF	/*  The value when the NIC is unplugged क्रम PCI. */
#घोषणा HAL_NIC_UNPLUG_PCI_ISR		0xEAEAEAEA	/*  The value when the NIC is unplugged क्रम PCI in PCI पूर्णांकerrupt (page 3). */

/*  */
/*        8188 IMR/ISR bits */
/*  */
#घोषणा IMR_DISABLED_88E			0x0
/*  IMR DW0(0x0060-0063) Bit 0-31 */
#घोषणा IMR_TXCCK_88E				BIT30		/*  TXRPT पूर्णांकerrupt when CCX bit of the packet is set */
#घोषणा IMR_PSTIMEOUT_88E			BIT29		/*  Power Save Time Out Interrupt */
#घोषणा IMR_GTINT4_88E				BIT28		/*  When GTIMER4 expires, this bit is set to 1 */
#घोषणा IMR_GTINT3_88E				BIT27		/*  When GTIMER3 expires, this bit is set to 1 */
#घोषणा IMR_TBDER_88E				BIT26		/*  Transmit Beacon0 Error */
#घोषणा IMR_TBDOK_88E				BIT25		/*  Transmit Beacon0 OK */
#घोषणा IMR_TSF_BIT32_TOGGLE_88E	BIT24		/*  TSF Timer BIT32 toggle indication पूर्णांकerrupt */
#घोषणा IMR_BCNDMAINT0_88E		BIT20		/*  Beacon DMA Interrupt 0 */
#घोषणा IMR_BCNDERR0_88E			BIT16		/*  Beacon Queue DMA Error 0 */
#घोषणा IMR_HSISR_IND_ON_INT_88E	BIT15		/*  HSISR Indicator (HSIMR & HSISR is true, this bit is set to 1) */
#घोषणा IMR_BCNDMAINT_E_88E		BIT14		/*  Beacon DMA Interrupt Extension क्रम Win7 */
#घोषणा IMR_ATIMEND_88E			BIT12		/*  CTWidnow End or ATIM Winकरोw End */
#घोषणा IMR_HISR1_IND_INT_88E		BIT11		/*  HISR1 Indicator (HISR1 & HIMR1 is true, this bit is set to 1) */
#घोषणा IMR_C2HCMD_88E				BIT10		/*  CPU to Host Command INT Status, Write 1 clear */
#घोषणा IMR_CPWM2_88E				BIT9			/*  CPU घातer Mode exchange INT Status, Write 1 clear */
#घोषणा IMR_CPWM_88E				BIT8			/*  CPU घातer Mode exchange INT Status, Write 1 clear */
#घोषणा IMR_HIGHDOK_88E			BIT7			/*  High Queue DMA OK */
#घोषणा IMR_MGNTDOK_88E			BIT6			/*  Management Queue DMA OK */
#घोषणा IMR_BKDOK_88E				BIT5			/*  AC_BK DMA OK */
#घोषणा IMR_BEDOK_88E				BIT4			/*  AC_BE DMA OK */
#घोषणा IMR_VIDOK_88E				BIT3			/*  AC_VI DMA OK */
#घोषणा IMR_VODOK_88E				BIT2			/*  AC_VO DMA OK */
#घोषणा IMR_RDU_88E					BIT1			/*  Rx Descriptor Unavailable */
#घोषणा IMR_ROK_88E					BIT0			/*  Receive DMA OK */

/*  IMR DW1(0x00B4-00B7) Bit 0-31 */
#घोषणा IMR_BCNDMAINT7_88E		BIT27		/*  Beacon DMA Interrupt 7 */
#घोषणा IMR_BCNDMAINT6_88E		BIT26		/*  Beacon DMA Interrupt 6 */
#घोषणा IMR_BCNDMAINT5_88E		BIT25		/*  Beacon DMA Interrupt 5 */
#घोषणा IMR_BCNDMAINT4_88E		BIT24		/*  Beacon DMA Interrupt 4 */
#घोषणा IMR_BCNDMAINT3_88E		BIT23		/*  Beacon DMA Interrupt 3 */
#घोषणा IMR_BCNDMAINT2_88E		BIT22		/*  Beacon DMA Interrupt 2 */
#घोषणा IMR_BCNDMAINT1_88E		BIT21		/*  Beacon DMA Interrupt 1 */
#घोषणा IMR_BCNDOK7_88E			BIT20		/*  Beacon Queue DMA OK Interrupt 7 */
#घोषणा IMR_BCNDOK6_88E			BIT19		/*  Beacon Queue DMA OK Interrupt 6 */
#घोषणा IMR_BCNDOK5_88E			BIT18		/*  Beacon Queue DMA OK Interrupt 5 */
#घोषणा IMR_BCNDOK4_88E			BIT17		/*  Beacon Queue DMA OK Interrupt 4 */
#घोषणा IMR_BCNDOK3_88E			BIT16		/*  Beacon Queue DMA OK Interrupt 3 */
#घोषणा IMR_BCNDOK2_88E			BIT15		/*  Beacon Queue DMA OK Interrupt 2 */
#घोषणा IMR_BCNDOK1_88E			BIT14		/*  Beacon Queue DMA OK Interrupt 1 */
#घोषणा IMR_ATIMEND_E_88E			BIT13		/*  ATIM Winकरोw End Extension क्रम Win7 */
#घोषणा IMR_TXERR_88E				BIT11		/*  Tx Error Flag Interrupt Status, ग_लिखो 1 clear. */
#घोषणा IMR_RXERR_88E				BIT10		/*  Rx Error Flag INT Status, Write 1 clear */
#घोषणा IMR_TXFOVW_88E				BIT9			/*  Transmit FIFO Overflow */
#घोषणा IMR_RXFOVW_88E				BIT8			/*  Receive FIFO Overflow */

/*===================================================================
=====================================================================
Here the रेजिस्टर defines are क्रम 92C. When the define is as same with 92C,
we will use the 92C's define क्रम the consistency
So the following defines क्रम 92C is not entire!!!!!!
=====================================================================
=====================================================================*/
/*
Based on Datasheet V33---090401
Register Summary
Current IOREG MAP
0x0000h ~ 0x00FFh   System Configuration (256 Bytes)
0x0100h ~ 0x01FFh   MACTOP General Configuration (256 Bytes)
0x0200h ~ 0x027Fh   TXDMA Configuration (128 Bytes)
0x0280h ~ 0x02FFh   RXDMA Configuration (128 Bytes)
0x0300h ~ 0x03FFh   PCIE EMAC Reserved Region (256 Bytes)
0x0400h ~ 0x04FFh   Protocol Configuration (256 Bytes)
0x0500h ~ 0x05FFh   EDCA Configuration (256 Bytes)
0x0600h ~ 0x07FFh   WMAC Configuration (512 Bytes)
0x2000h ~ 0x3FFFh   8051 FW Download Region (8196 Bytes)
*/
	/*  */
	/* 		 8192C (TXPAUSE) transmission छोड़ो	(Offset 0x522, 8 bits) */
	/*  */
/*  Note: */
/* 	The  bits of stopping AC(VO/VI/BE/BK) queue in datasheet RTL8192S/RTL8192C are wrong, */
/* 	the correct arrangement is VO - Bit0, VI - Bit1, BE - Bit2, and BK - Bit3. */
/* 	8723 and 88E may be not correct either in the earlier version. Confirmed with DD Tim. */
/*  By Bruce, 2011-09-22. */
#घोषणा StopBecon		BIT6
#घोषणा StopHigh			BIT5
#घोषणा StopMgt			BIT4
#घोषणा StopBK			BIT3
#घोषणा StopBE			BIT2
#घोषणा StopVI			BIT1
#घोषणा StopVO			BIT0

/*  */
/*        8192C (RCR) Receive Configuration Register	(Offset 0x608, 32 bits) */
/*  */
#घोषणा RCR_APPFCS				BIT31	/*  WMAC append FCS after pauload */
#घोषणा RCR_APP_MIC				BIT30	/*  MACRX will retain the MIC at the bottom of the packet. */
#घोषणा RCR_APP_ICV				BIT29	/*  MACRX will retain the ICV at the bottom of the packet. */
#घोषणा RCR_APP_PHYST_RXFF		BIT28	/*  PHY Status is appended beक्रमe RX packet in RXFF */
#घोषणा RCR_APP_BA_SSN			BIT27	/*  SSN of previous TXBA is appended as after original RXDESC as the 4-th DW of RXDESC. */
#घोषणा RCR_NONQOS_VHT			BIT26	/*  Reserved */
#घोषणा RCR_RSVD_BIT25			BIT25	/*  Reserved */
#घोषणा RCR_ENMBID				BIT24	/*  Enable Multiple BssId. Only response ACK to the packets whose DID(A1) matching to the addresses in the MBSSID CAM Entries. */
#घोषणा RCR_LSIGEN				BIT23	/*  Enable LSIG TXOP Protection function. Search KEYCAM क्रम each rx packet to check अगर LSIGEN bit is set. */
#घोषणा RCR_MFBEN				BIT22	/*  Enable immediate MCS Feedback function. When Rx packet with MRQ = 1'b1, then search KEYCAM to find sender's MCS Feedback function and send response. */
#घोषणा RCR_RSVD_BIT21			BIT21	/*  Reserved */
#घोषणा RCR_RSVD_BIT20			BIT20	/*  Reserved */
#घोषणा RCR_RSVD_BIT19			BIT19	/*  Reserved */
#घोषणा RCR_TIM_PARSER_EN		BIT18	/*  RX Beacon TIM Parser. */
#घोषणा RCR_BM_DATA_EN			BIT17	/*  Broadcast data packet पूर्णांकerrupt enable. */
#घोषणा RCR_UC_DATA_EN			BIT16	/*  Unicast data packet पूर्णांकerrupt enable. */
#घोषणा RCR_RSVD_BIT15			BIT15	/*  Reserved */
#घोषणा RCR_HTC_LOC_CTRL		BIT14	/*  MFC<--HTC = 1 MFC-->HTC = 0 */
#घोषणा RCR_AMF					BIT13	/*  Accept management type frame */
#घोषणा RCR_ACF					BIT12	/*  Accept control type frame. Control frames BA, BAR, and PS-Poll (when in AP mode) are not controlled by this bit. They are controlled by ADF. */
#घोषणा RCR_ADF					BIT11	/*  Accept data type frame. This bit also regulates BA, BAR, and PS-Poll (AP mode only). */
#घोषणा RCR_RSVD_BIT10			BIT10	/*  Reserved */
#घोषणा RCR_AICV					BIT9		/*  Accept ICV error packet */
#घोषणा RCR_ACRC32				BIT8		/*  Accept CRC32 error packet */
#घोषणा RCR_CBSSID_BCN			BIT7		/*  Accept BSSID match packet (Rx beacon, probe rsp) */
#घोषणा RCR_CBSSID_DATA		BIT6		/*  Accept BSSID match packet (Data) */
#घोषणा RCR_CBSSID				RCR_CBSSID_DATA	/*  Accept BSSID match packet */
#घोषणा RCR_APWRMGT			BIT5		/*  Accept घातer management packet */
#घोषणा RCR_ADD3				BIT4		/*  Accept address 3 match packet */
#घोषणा RCR_AB					BIT3		/*  Accept broadcast packet */
#घोषणा RCR_AM					BIT2		/*  Accept multicast packet */
#घोषणा RCR_APM					BIT1		/*  Accept physical match packet */
#घोषणा RCR_AAP					BIT0		/*  Accept all unicast packet */


/*  */
/*  */
/* 	0x0000h ~ 0x00FFh	System Configuration */
/*  */
/*  */

/* 2 SYS_ISO_CTRL */
#घोषणा ISO_MD2PP				BIT(0)
#घोषणा ISO_UA2USB				BIT(1)
#घोषणा ISO_UD2CORE				BIT(2)
#घोषणा ISO_PA2PCIE				BIT(3)
#घोषणा ISO_PD2CORE				BIT(4)
#घोषणा ISO_IP2MAC				BIT(5)
#घोषणा ISO_DIOP					BIT(6)
#घोषणा ISO_DIOE					BIT(7)
#घोषणा ISO_EB2CORE				BIT(8)
#घोषणा ISO_DIOR					BIT(9)
#घोषणा PWC_EV12V				BIT(15)


/* 2 SYS_FUNC_EN */
#घोषणा FEN_BBRSTB				BIT(0)
#घोषणा FEN_BB_GLB_RSTn		BIT(1)
#घोषणा FEN_USBA				BIT(2)
#घोषणा FEN_UPLL				BIT(3)
#घोषणा FEN_USBD				BIT(4)
#घोषणा FEN_DIO_PCIE			BIT(5)
#घोषणा FEN_PCIEA				BIT(6)
#घोषणा FEN_PPLL					BIT(7)
#घोषणा FEN_PCIED				BIT(8)
#घोषणा FEN_DIOE				BIT(9)
#घोषणा FEN_CPUEN				BIT(10)
#घोषणा FEN_DCORE				BIT(11)
#घोषणा FEN_ELDR				BIT(12)
#घोषणा FEN_EN_25_1				BIT(13)
#घोषणा FEN_HWPDN				BIT(14)
#घोषणा FEN_MREGEN				BIT(15)

/* 2 APS_FSMCO */
#घोषणा PFM_LDALL				BIT(0)
#घोषणा PFM_ALDN				BIT(1)
#घोषणा PFM_LDKP				BIT(2)
#घोषणा PFM_WOWL				BIT(3)
#घोषणा EnPDN					BIT(4)
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

/* 2 SYS_CLKR */
#घोषणा ANAD16V_EN				BIT(0)
#घोषणा ANA8M					BIT(1)
#घोषणा MACSLP					BIT(4)
#घोषणा LOADER_CLK_EN			BIT(5)


/* 2 9346CR /REG_SYS_EEPROM_CTRL */
#घोषणा BOOT_FROM_EEPROM		BIT(4)
#घोषणा EEPROMSEL				BIT(4)
#घोषणा EEPROM_EN				BIT(5)


/* 2 RF_CTRL */
#घोषणा RF_EN					BIT(0)
#घोषणा RF_RSTB					BIT(1)
#घोषणा RF_SDMRSTB				BIT(2)


/* 2 LDOV12D_CTRL */
#घोषणा LDV12_EN				BIT(0)
#घोषणा LDV12_SDBY				BIT(1)
#घोषणा LPLDO_HSM				BIT(2)
#घोषणा LPLDO_LSM_DIS			BIT(3)
#घोषणा _LDV12_VADJ(x)			(((x) & 0xF) << 4)



/* 2 EFUSE_TEST (For RTL8723 partially) */
#घोषणा EF_TRPT					BIT(7)
#घोषणा EF_CELL_SEL				(BIT(8)|BIT(9)) /*  00: Wअगरi Efuse, 01: BT Efuse0, 10: BT Efuse1, 11: BT Efuse2 */
#घोषणा LDOE25_EN				BIT(31)
#घोषणा EFUSE_SEL(x)				(((x) & 0x3) << 8)
#घोषणा EFUSE_SEL_MASK			0x300
#घोषणा EFUSE_WIFI_SEL_0		0x0
#घोषणा EFUSE_BT_SEL_0			0x1
#घोषणा EFUSE_BT_SEL_1			0x2
#घोषणा EFUSE_BT_SEL_2			0x3


/* 2 8051FWDL */
/* 2 MCUFWDL */
#घोषणा MCUFWDL_EN				BIT(0)
#घोषणा MCUFWDL_RDY			BIT(1)
#घोषणा FWDL_ChkSum_rpt		BIT(2)
#घोषणा MACINI_RDY				BIT(3)
#घोषणा BBINI_RDY				BIT(4)
#घोषणा RFINI_RDY				BIT(5)
#घोषणा WINTINI_RDY				BIT(6)
#घोषणा RAM_DL_SEL				BIT(7)
#घोषणा ROM_DLEN				BIT(19)
#घोषणा CPRST					BIT(23)


/* 2 REG_SYS_CFG */
#घोषणा XCLK_VLD				BIT(0)
#घोषणा ACLK_VLD				BIT(1)
#घोषणा UCLK_VLD				BIT(2)
#घोषणा PCLK_VLD				BIT(3)
#घोषणा PCIRSTB					BIT(4)
#घोषणा V15_VLD					BIT(5)
#घोषणा SW_OFFLOAD_EN			BIT(7)
#घोषणा SIC_IDLE					BIT(8)
#घोषणा BD_MAC2					BIT(9)
#घोषणा BD_MAC1					BIT(10)
#घोषणा IC_MACPHY_MODE		BIT(11)
#घोषणा CHIP_VER				(BIT(12)|BIT(13)|BIT(14)|BIT(15))
#घोषणा BT_FUNC					BIT(16)
#घोषणा VENDOR_ID				BIT(19)
#घोषणा EXT_VENDOR_ID			(BIT(18)|BIT(19)) /* Currently only क्रम RTL8723B */
#घोषणा PAD_HWPD_IDN			BIT(22)
#घोषणा TRP_VAUX_EN				BIT(23)	/*  RTL ID */
#घोषणा TRP_BT_EN				BIT(24)
#घोषणा BD_PKG_SEL				BIT(25)
#घोषणा BD_HCI_SEL				BIT(26)
#घोषणा TYPE_ID					BIT(27)
#घोषणा RF_TYPE_ID				BIT(27)

#घोषणा RTL_ID					BIT(23) /*  TestChip ID, 1:Test(RLE); 0:MP(RL) */
#घोषणा SPS_SEL					BIT(24) /*  1:LDO regulator mode; 0:Switching regulator mode */


#घोषणा CHIP_VER_RTL_MASK		0xF000	/* Bit 12 ~ 15 */
#घोषणा CHIP_VER_RTL_SHIFT		12
#घोषणा EXT_VENDOR_ID_SHIFT	18

/* 2 REG_GPIO_OUTSTS (For RTL8723 only) */
#घोषणा EFS_HCI_SEL				(BIT(0)|BIT(1))
#घोषणा PAD_HCI_SEL				(BIT(2)|BIT(3))
#घोषणा HCI_SEL					(BIT(4)|BIT(5))
#घोषणा PKG_SEL_HCI				BIT(6)
#घोषणा FEN_GPS					BIT(7)
#घोषणा FEN_BT					BIT(8)
#घोषणा FEN_WL					BIT(9)
#घोषणा FEN_PCI					BIT(10)
#घोषणा FEN_USB					BIT(11)
#घोषणा BTRF_HWPDN_N			BIT(12)
#घोषणा WLRF_HWPDN_N			BIT(13)
#घोषणा PDN_BT_N				BIT(14)
#घोषणा PDN_GPS_N				BIT(15)
#घोषणा BT_CTL_HWPDN			BIT(16)
#घोषणा GPS_CTL_HWPDN			BIT(17)
#घोषणा PPHY_SUSB				BIT(20)
#घोषणा UPHY_SUSB				BIT(21)
#घोषणा PCI_SUSEN				BIT(22)
#घोषणा USB_SUSEN				BIT(23)
#घोषणा RF_RL_ID					(BIT(31)|BIT(30)|BIT(29)|BIT(28))


/*  */
/*  */
/* 	0x0100h ~ 0x01FFh	MACTOP General Configuration */
/*  */
/*  */

/* 2 Function Enable Registers */
/* 2 CR */
#घोषणा HCI_TXDMA_EN			BIT(0)
#घोषणा HCI_RXDMA_EN			BIT(1)
#घोषणा TXDMA_EN				BIT(2)
#घोषणा RXDMA_EN				BIT(3)
#घोषणा PROTOCOL_EN				BIT(4)
#घोषणा SCHEDULE_EN				BIT(5)
#घोषणा MACTXEN					BIT(6)
#घोषणा MACRXEN					BIT(7)
#घोषणा ENSWBCN					BIT(8)
#घोषणा ENSEC					BIT(9)
#घोषणा CALTMR_EN				BIT(10)	/*  32k CAL TMR enable */

/*  Network type */
#घोषणा _NETTYPE(x)				(((x) & 0x3) << 16)
#घोषणा MASK_NETTYPE			0x30000
#घोषणा NT_NO_LINK				0x0
#घोषणा NT_LINK_AD_HOC			0x1
#घोषणा NT_LINK_AP				0x2
#घोषणा NT_AS_AP				0x3

/* 2 PBP - Page Size Register */
#घोषणा GET_RX_PAGE_SIZE(value)			((value) & 0xF)
#घोषणा GET_TX_PAGE_SIZE(value)			(((value) & 0xF0) >> 4)
#घोषणा _PSRX_MASK				0xF
#घोषणा _PSTX_MASK				0xF0
#घोषणा _PSRX(x)				(x)
#घोषणा _PSTX(x)				((x) << 4)

#घोषणा PBP_64					0x0
#घोषणा PBP_128					0x1
#घोषणा PBP_256					0x2
#घोषणा PBP_512					0x3
#घोषणा PBP_1024				0x4


/* 2 TX/RXDMA */
#घोषणा RXDMA_ARBBW_EN		BIT(0)
#घोषणा RXSHFT_EN				BIT(1)
#घोषणा RXDMA_AGG_EN			BIT(2)
#घोषणा QS_VO_QUEUE			BIT(8)
#घोषणा QS_VI_QUEUE				BIT(9)
#घोषणा QS_BE_QUEUE			BIT(10)
#घोषणा QS_BK_QUEUE			BIT(11)
#घोषणा QS_MANAGER_QUEUE		BIT(12)
#घोषणा QS_HIGH_QUEUE			BIT(13)

#घोषणा HQSEL_VOQ				BIT(0)
#घोषणा HQSEL_VIQ				BIT(1)
#घोषणा HQSEL_BEQ				BIT(2)
#घोषणा HQSEL_BKQ				BIT(3)
#घोषणा HQSEL_MGTQ				BIT(4)
#घोषणा HQSEL_HIQ				BIT(5)

/*  For normal driver, 0x10C */
#घोषणा _TXDMA_CMQ_MAP(x)			(((x)&0x3) << 16)
#घोषणा _TXDMA_HIQ_MAP(x)			(((x)&0x3) << 14)
#घोषणा _TXDMA_MGQ_MAP(x)			(((x)&0x3) << 12)
#घोषणा _TXDMA_BKQ_MAP(x)			(((x)&0x3) << 10)
#घोषणा _TXDMA_BEQ_MAP(x)			(((x)&0x3) << 8)
#घोषणा _TXDMA_VIQ_MAP(x)			(((x)&0x3) << 6)
#घोषणा _TXDMA_VOQ_MAP(x)			(((x)&0x3) << 4)

#घोषणा QUEUE_EXTRA				0
#घोषणा QUEUE_LOW				1
#घोषणा QUEUE_NORMAL			2
#घोषणा QUEUE_HIGH				3


/* 2 TRXFF_BNDY */


/* 2 LLT_INIT */
#घोषणा _LLT_NO_ACTIVE				0x0
#घोषणा _LLT_WRITE_ACCESS			0x1
#घोषणा _LLT_READ_ACCESS			0x2

#घोषणा _LLT_INIT_DATA(x)			((x) & 0xFF)
#घोषणा _LLT_INIT_ADDR(x)			(((x) & 0xFF) << 8)
#घोषणा _LLT_OP(x)					(((x) & 0x3) << 30)
#घोषणा _LLT_OP_VALUE(x)			(((x) >> 30) & 0x3)


/*  */
/*  */
/* 	0x0200h ~ 0x027Fh	TXDMA Configuration */
/*  */
/*  */
/* 2 RQPN */
#घोषणा _HPQ(x)					((x) & 0xFF)
#घोषणा _LPQ(x)					(((x) & 0xFF) << 8)
#घोषणा _PUBQ(x)					(((x) & 0xFF) << 16)
#घोषणा _NPQ(x)					((x) & 0xFF)			/*  NOTE: in RQPN_NPQ रेजिस्टर */
#घोषणा _EPQ(x)					(((x) & 0xFF) << 16)	/*  NOTE: in RQPN_EPQ रेजिस्टर */


#घोषणा HPQ_PUBLIC_DIS			BIT(24)
#घोषणा LPQ_PUBLIC_DIS			BIT(25)
#घोषणा LD_RQPN					BIT(31)


/* 2 TDECTL */
#घोषणा BLK_DESC_NUM_SHIFT			4
#घोषणा BLK_DESC_NUM_MASK			0xF


/* 2 TXDMA_OFFSET_CHK */
#घोषणा DROP_DATA_EN				BIT(9)

/* 2 AUTO_LLT */
#घोषणा BIT_SHIFT_TXPKTNUM 24
#घोषणा BIT_MASK_TXPKTNUM 0xff
#घोषणा BIT_TXPKTNUM(x) (((x) & BIT_MASK_TXPKTNUM) << BIT_SHIFT_TXPKTNUM)

#घोषणा BIT_TDE_DBG_SEL BIT(23)
#घोषणा BIT_AUTO_INIT_LLT BIT(16)

#घोषणा BIT_SHIFT_Tx_OQT_मुक्त_space 8
#घोषणा BIT_MASK_Tx_OQT_मुक्त_space 0xff
#घोषणा BIT_Tx_OQT_मुक्त_space(x) (((x) & BIT_MASK_Tx_OQT_मुक्त_space) << BIT_SHIFT_Tx_OQT_मुक्त_space)


/*  */
/*  */
/* 	0x0280h ~ 0x028Bh	RX DMA Configuration */
/*  */
/*  */

/* 2 REG_RXDMA_CONTROL, 0x0286h */
/*  Write only. When this bit is set, RXDMA will decrease RX PKT counter by one. Beक्रमe */
/*  this bit is polled, FW shall update RXFF_RD_PTR first. This रेजिस्टर is ग_लिखो pulse and स्वतः clear. */
/* define RXPKT_RELEASE_POLL			BIT(0) */
/*  Read only. When RXMA finishes on-going DMA operation, RXMDA will report idle state in */
/*  this bit. FW can start releasing packets after RXDMA entering idle mode. */
/* define RXDMA_IDLE					BIT(1) */
/*  When this bit is set, RXDMA will enter this mode after on-going RXDMA packet to host */
/*  completed, and stop DMA packet to host. RXDMA will then report Default: 0; */
/* define RW_RELEASE_EN				BIT(2) */

/* 2 REG_RXPKT_NUM, 0x0284 */
#घोषणा		RXPKT_RELEASE_POLL	BIT(16)
#घोषणा	RXDMA_IDLE				BIT(17)
#घोषणा	RW_RELEASE_EN			BIT(18)

/*  */
/*  */
/* 	0x0400h ~ 0x047Fh	Protocol Configuration */
/*  */
/*  */
/* 2 FWHW_TXQ_CTRL */
#घोषणा EN_AMPDU_RTY_NEW			BIT(7)


/* 2 SPEC SIFS */
#घोषणा _SPEC_SIFS_CCK(x)			((x) & 0xFF)
#घोषणा _SPEC_SIFS_OFDM(x)			(((x) & 0xFF) << 8)

/* 2 RL */
#घोषणा	RETRY_LIMIT_SHORT_SHIFT			8
#घोषणा	RETRY_LIMIT_LONG_SHIFT			0

/*  */
/*  */
/* 	0x0500h ~ 0x05FFh	EDCA Configuration */
/*  */
/*  */

/* 2 EDCA setting */
#घोषणा AC_PARAM_TXOP_LIMIT_OFFSET		16
#घोषणा AC_PARAM_ECW_MAX_OFFSET			12
#घोषणा AC_PARAM_ECW_MIN_OFFSET			8
#घोषणा AC_PARAM_AIFS_OFFSET				0


#घोषणा _LRL(x)					((x) & 0x3F)
#घोषणा _SRL(x)					(((x) & 0x3F) << 8)


/* 2 BCN_CTRL */
#घोषणा EN_TXBCN_RPT			BIT(2)
#घोषणा EN_BCN_FUNCTION		BIT(3)
#घोषणा STOP_BCNQ				BIT(6)
#घोषणा DIS_RX_BSSID_FIT		BIT(6)

#घोषणा DIS_ATIM					BIT(0)
#घोषणा DIS_BCNQ_SUB			BIT(1)
#घोषणा DIS_TSF_UDT				BIT(4)

/*  The same function but dअगरferent bit field. */
#घोषणा DIS_TSF_UDT0_NORMAL_CHIP	BIT(4)
#घोषणा DIS_TSF_UDT0_TEST_CHIP	BIT(5)


/* 2 ACMHWCTRL */
#घोषणा AcmHw_HwEn				BIT(0)
#घोषणा AcmHw_BeqEn			BIT(1)
#घोषणा AcmHw_ViqEn				BIT(2)
#घोषणा AcmHw_VoqEn			BIT(3)
#घोषणा AcmHw_BeqStatus		BIT(4)
#घोषणा AcmHw_ViqStatus			BIT(5)
#घोषणा AcmHw_VoqStatus		BIT(6)

/* 2 REG_DUAL_TSF_RST (0x553) */
#घोषणा DUAL_TSF_RST_P2P		BIT(4)

/* 2  REG_NOA_DESC_SEL (0x5CF) */
#घोषणा NOA_DESC_SEL_0			0
#घोषणा NOA_DESC_SEL_1			BIT(4)

/*  */
/*  */
/* 	0x0600h ~ 0x07FFh	WMAC Configuration */
/*  */
/*  */

/* 2 APSD_CTRL */
#घोषणा APSDOFF					BIT(6)

/* 2 TCR */
#घोषणा TSFRST					BIT(0)
#घोषणा DIS_GCLK					BIT(1)
#घोषणा PAD_SEL					BIT(2)
#घोषणा PWR_ST					BIT(6)
#घोषणा PWRBIT_OW_EN			BIT(7)
#घोषणा ACRC						BIT(8)
#घोषणा CFENDFORM				BIT(9)
#घोषणा ICV						BIT(10)


/* 2 RCR */
#घोषणा AAP						BIT(0)
#घोषणा APM						BIT(1)
#घोषणा AM						BIT(2)
#घोषणा AB						BIT(3)
#घोषणा ADD3						BIT(4)
#घोषणा APWRMGT				BIT(5)
#घोषणा CBSSID					BIT(6)
#घोषणा CBSSID_DATA				BIT(6)
#घोषणा CBSSID_BCN				BIT(7)
#घोषणा ACRC32					BIT(8)
#घोषणा AICV						BIT(9)
#घोषणा ADF						BIT(11)
#घोषणा ACF						BIT(12)
#घोषणा AMF						BIT(13)
#घोषणा HTC_LOC_CTRL			BIT(14)
#घोषणा UC_DATA_EN				BIT(16)
#घोषणा BM_DATA_EN				BIT(17)
#घोषणा MFBEN					BIT(22)
#घोषणा LSIGEN					BIT(23)
#घोषणा EnMBID					BIT(24)
#घोषणा FORCEACK				BIT(26)
#घोषणा APP_BASSN				BIT(27)
#घोषणा APP_PHYSTS				BIT(28)
#घोषणा APP_ICV					BIT(29)
#घोषणा APP_MIC					BIT(30)
#घोषणा APP_FCS					BIT(31)


/* 2 SECCFG */
#घोषणा SCR_TxUseDK				BIT(0)			/* Force Tx Use Default Key */
#घोषणा SCR_RxUseDK				BIT(1)			/* Force Rx Use Default Key */
#घोषणा SCR_TxEncEnable			BIT(2)			/* Enable Tx Encryption */
#घोषणा SCR_RxDecEnable			BIT(3)			/* Enable Rx Decryption */
#घोषणा SCR_SKByA2				BIT(4)			/* Search kEY BY A2 */
#घोषणा SCR_NoSKMC				BIT(5)			/* No Key Search Multicast */
#घोषणा SCR_TXBCUSEDK			BIT(6)			/*  Force Tx Broadcast packets Use Default Key */
#घोषणा SCR_RXBCUSEDK			BIT(7)			/*  Force Rx Broadcast packets Use Default Key */
#घोषणा SCR_CHK_KEYID			BIT(8)

/*  */
/*  */
/* 	SDIO Bus Specअगरication */
/*  */
/*  */

/*  I/O bus करोमुख्य address mapping */
#घोषणा SDIO_LOCAL_BASE		0x10250000
#घोषणा WLAN_IOREG_BASE		0x10260000
#घोषणा FIRMWARE_FIFO_BASE	0x10270000
#घोषणा TX_HIQ_BASE				0x10310000
#घोषणा TX_MIQ_BASE				0x10320000
#घोषणा TX_LOQ_BASE				0x10330000
#घोषणा TX_EPQ_BASE				0x10350000
#घोषणा RX_RX0FF_BASE			0x10340000

/* SDIO host local रेजिस्टर space mapping. */
#घोषणा SDIO_LOCAL_MSK				0x0FFF
#घोषणा WLAN_IOREG_MSK			0x7FFF
#घोषणा WLAN_FIFO_MSK				0x1FFF	/*  Aggregation Length[12:0] */
#घोषणा WLAN_RX0FF_MSK				0x0003

#घोषणा SDIO_WITHOUT_REF_DEVICE_ID	0	/*  Without reference to the SDIO Device ID */
#घोषणा SDIO_LOCAL_DEVICE_ID			0	/*  0b[16], 000b[15:13] */
#घोषणा WLAN_TX_HIQ_DEVICE_ID			4	/*  0b[16], 100b[15:13] */
#घोषणा WLAN_TX_MIQ_DEVICE_ID		5	/*  0b[16], 101b[15:13] */
#घोषणा WLAN_TX_LOQ_DEVICE_ID		6	/*  0b[16], 110b[15:13] */
#घोषणा WLAN_TX_EXQ_DEVICE_ID		3	/*  0b[16], 011b[15:13] */
#घोषणा WLAN_RX0FF_DEVICE_ID			7	/*  0b[16], 111b[15:13] */
#घोषणा WLAN_IOREG_DEVICE_ID			8	/*  1b[16] */

/* SDIO Tx Free Page Index */
#घोषणा HI_QUEUE_IDX				0
#घोषणा MID_QUEUE_IDX				1
#घोषणा LOW_QUEUE_IDX				2
#घोषणा PUBLIC_QUEUE_IDX			3

#घोषणा SDIO_MAX_TX_QUEUE			3		/*  HIQ, MIQ and LOQ */
#घोषणा SDIO_MAX_RX_QUEUE			1

#घोषणा SDIO_REG_TX_CTRL			0x0000 /*  SDIO Tx Control */
#घोषणा SDIO_REG_HIMR				0x0014 /*  SDIO Host Interrupt Mask */
#घोषणा SDIO_REG_HISR				0x0018 /*  SDIO Host Interrupt Service Routine */
#घोषणा SDIO_REG_HCPWM			0x0019 /*  HCI Current Power Mode */
#घोषणा SDIO_REG_RX0_REQ_LEN		0x001C /*  RXDMA Request Length */
#घोषणा SDIO_REG_OQT_FREE_PG		0x001E /*  OQT Free Page */
#घोषणा SDIO_REG_FREE_TXPG			0x0020 /*  Free Tx Buffer Page */
#घोषणा SDIO_REG_HCPWM1			0x0024 /*  HCI Current Power Mode 1 */
#घोषणा SDIO_REG_HCPWM2			0x0026 /*  HCI Current Power Mode 2 */
#घोषणा SDIO_REG_FREE_TXPG_SEQ	0x0028 /*  Free Tx Page Sequence */
#घोषणा SDIO_REG_HTSFR_INFO		0x0030 /*  HTSF Inक्रमmaion */
#घोषणा SDIO_REG_HRPWM1			0x0080 /*  HCI Request Power Mode 1 */
#घोषणा SDIO_REG_HRPWM2			0x0082 /*  HCI Request Power Mode 2 */
#घोषणा SDIO_REG_HPS_CLKR			0x0084 /*  HCI Power Save Clock */
#घोषणा SDIO_REG_HSUS_CTRL			0x0086 /*  SDIO HCI Suspend Control */
#घोषणा SDIO_REG_HIMR_ON			0x0090 /* SDIO Host Extension Interrupt Mask Always */
#घोषणा SDIO_REG_HISR_ON			0x0091 /* SDIO Host Extension Interrupt Status Always */

#घोषणा SDIO_HIMR_DISABLED			0

/*  RTL8723/RTL8188E SDIO Host Interrupt Mask Register */
#घोषणा SDIO_HIMR_RX_REQUEST_MSK		BIT0
#घोषणा SDIO_HIMR_AVAL_MSK			BIT1
#घोषणा SDIO_HIMR_TXERR_MSK			BIT2
#घोषणा SDIO_HIMR_RXERR_MSK			BIT3
#घोषणा SDIO_HIMR_TXFOVW_MSK			BIT4
#घोषणा SDIO_HIMR_RXFOVW_MSK			BIT5
#घोषणा SDIO_HIMR_TXBCNOK_MSK			BIT6
#घोषणा SDIO_HIMR_TXBCNERR_MSK		BIT7
#घोषणा SDIO_HIMR_BCNERLY_INT_MSK		BIT16
#घोषणा SDIO_HIMR_C2HCMD_MSK			BIT17
#घोषणा SDIO_HIMR_CPWM1_MSK			BIT18
#घोषणा SDIO_HIMR_CPWM2_MSK			BIT19
#घोषणा SDIO_HIMR_HSISR_IND_MSK		BIT20
#घोषणा SDIO_HIMR_GTINT3_IND_MSK		BIT21
#घोषणा SDIO_HIMR_GTINT4_IND_MSK		BIT22
#घोषणा SDIO_HIMR_PSTIMEOUT_MSK		BIT23
#घोषणा SDIO_HIMR_OCPINT_MSK			BIT24
#घोषणा SDIO_HIMR_ATIMEND_MSK			BIT25
#घोषणा SDIO_HIMR_ATIMEND_E_MSK		BIT26
#घोषणा SDIO_HIMR_CTWEND_MSK			BIT27

/* RTL8188E SDIO Specअगरic */
#घोषणा SDIO_HIMR_MCU_ERR_MSK			BIT28
#घोषणा SDIO_HIMR_TSF_BIT32_TOGGLE_MSK		BIT29

/*  SDIO Host Interrupt Service Routine */
#घोषणा SDIO_HISR_RX_REQUEST			BIT0
#घोषणा SDIO_HISR_AVAL					BIT1
#घोषणा SDIO_HISR_TXERR					BIT2
#घोषणा SDIO_HISR_RXERR					BIT3
#घोषणा SDIO_HISR_TXFOVW				BIT4
#घोषणा SDIO_HISR_RXFOVW				BIT5
#घोषणा SDIO_HISR_TXBCNOK				BIT6
#घोषणा SDIO_HISR_TXBCNERR				BIT7
#घोषणा SDIO_HISR_BCNERLY_INT			BIT16
#घोषणा SDIO_HISR_C2HCMD				BIT17
#घोषणा SDIO_HISR_CPWM1				BIT18
#घोषणा SDIO_HISR_CPWM2				BIT19
#घोषणा SDIO_HISR_HSISR_IND			BIT20
#घोषणा SDIO_HISR_GTINT3_IND			BIT21
#घोषणा SDIO_HISR_GTINT4_IND			BIT22
#घोषणा SDIO_HISR_PSTIMEOUT			BIT23
#घोषणा SDIO_HISR_OCPINT				BIT24
#घोषणा SDIO_HISR_ATIMEND				BIT25
#घोषणा SDIO_HISR_ATIMEND_E			BIT26
#घोषणा SDIO_HISR_CTWEND				BIT27

/* RTL8188E SDIO Specअगरic */
#घोषणा SDIO_HISR_MCU_ERR				BIT28
#घोषणा SDIO_HISR_TSF_BIT32_TOGGLE	BIT29

#घोषणा MASK_SDIO_HISR_CLEAR		(SDIO_HISR_TXERR |\
									SDIO_HISR_RXERR |\
									SDIO_HISR_TXFOVW |\
									SDIO_HISR_RXFOVW |\
									SDIO_HISR_TXBCNOK |\
									SDIO_HISR_TXBCNERR |\
									SDIO_HISR_C2HCMD |\
									SDIO_HISR_CPWM1 |\
									SDIO_HISR_CPWM2 |\
									SDIO_HISR_HSISR_IND |\
									SDIO_HISR_GTINT3_IND |\
									SDIO_HISR_GTINT4_IND |\
									SDIO_HISR_PSTIMEOUT |\
									SDIO_HISR_OCPINT)

/*  SDIO HCI Suspend Control Register */
#घोषणा HCI_RESUME_PWR_RDY			BIT1
#घोषणा HCI_SUS_CTRL					BIT0

/*  SDIO Tx FIFO related */
#घोषणा SDIO_TX_FREE_PG_QUEUE			4	/*  The number of Tx FIFO मुक्त page */
#घोषणा SDIO_TX_FIFO_PAGE_SZ			128

#घोषणा MAX_TX_AGG_PACKET_NUMBER	0x8

/*  */
/*  */
/* 	0xFE00h ~ 0xFE55h	USB Configuration */
/*  */
/*  */

/* 2 USB Inक्रमmation (0xFE17) */
#घोषणा USB_IS_HIGH_SPEED			0
#घोषणा USB_IS_FULL_SPEED			1
#घोषणा USB_SPEED_MASK				BIT(5)

#घोषणा USB_NORMAL_SIE_EP_MASK	0xF
#घोषणा USB_NORMAL_SIE_EP_SHIFT	4

/* 2 Special Option */
#घोषणा USB_AGG_EN				BIT(3)

/*  0; Use पूर्णांकerrupt endpoपूर्णांक to upload पूर्णांकerrupt pkt */
/*  1; Use bulk endpoपूर्णांक to upload पूर्णांकerrupt pkt, */
#घोषणा INT_BULK_SEL			BIT(4)

/* 2REG_C2HEVT_CLEAR */
#घोषणा C2H_EVT_HOST_CLOSE		0x00	/*  Set by driver and notअगरy FW that the driver has पढ़ो the C2H command message */
#घोषणा C2H_EVT_FW_CLOSE		0xFF	/*  Set by FW indicating that FW had set the C2H command message and it's not yet पढ़ो by driver. */


/* 2REG_MULTI_FUNC_CTRL(For RTL8723 Only) */
#घोषणा WL_HWPDN_EN			BIT0	/*  Enable GPIO[9] as WiFi HW PDn source */
#घोषणा WL_HWPDN_SL			BIT1	/*  WiFi HW PDn polarity control */
#घोषणा WL_FUNC_EN				BIT2	/*  WiFi function enable */
#घोषणा WL_HWROF_EN			BIT3	/*  Enable GPIO[9] as WiFi RF HW PDn source */
#घोषणा BT_HWPDN_EN			BIT16	/*  Enable GPIO[11] as BT HW PDn source */
#घोषणा BT_HWPDN_SL			BIT17	/*  BT HW PDn polarity control */
#घोषणा BT_FUNC_EN				BIT18	/*  BT function enable */
#घोषणा BT_HWROF_EN			BIT19	/*  Enable GPIO[11] as BT/GPS RF HW PDn source */
#घोषणा GPS_HWPDN_EN			BIT20	/*  Enable GPIO[10] as GPS HW PDn source */
#घोषणा GPS_HWPDN_SL			BIT21	/*  GPS HW PDn polarity control */
#घोषणा GPS_FUNC_EN			BIT22	/*  GPS function enable */

/* 3 REG_LIFECTRL_CTRL */
#घोषणा HAL92C_EN_PKT_LIFE_TIME_BK		BIT3
#घोषणा HAL92C_EN_PKT_LIFE_TIME_BE		BIT2
#घोषणा HAL92C_EN_PKT_LIFE_TIME_VI		BIT1
#घोषणा HAL92C_EN_PKT_LIFE_TIME_VO		BIT0

#घोषणा HAL92C_MSDU_LIFE_TIME_UNIT		128	/*  in us, said by Tim. */

/* 2 8192D PartNo. */
#घोषणा PARTNO_92D_NIC							(BIT7|BIT6)
#घोषणा PARTNO_92D_NIC_REMARK				(BIT5|BIT4)
#घोषणा PARTNO_SINGLE_BAND_VS				BIT3
#घोषणा PARTNO_SINGLE_BAND_VS_REMARK		BIT1
#घोषणा PARTNO_CONCURRENT_BAND_VC			(BIT3|BIT2)
#घोषणा PARTNO_CONCURRENT_BAND_VC_REMARK	(BIT1|BIT0)

/*  */
/*  General definitions */
/*  */

#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER_8188E		176
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER_8812			255
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER_8723B		255
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER_8192C		255
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER_DUAL_MAC	127

#घोषणा POLLING_LLT_THRESHOLD				20
#घोषणा POLLING_READY_TIMEOUT_COUNT		1000


/*  GPIO BIT */
#घोषणा	HAL_8192C_HW_GPIO_WPS_BIT	BIT2
#घोषणा	HAL_8192EU_HW_GPIO_WPS_BIT	BIT7
#घोषणा	HAL_8188E_HW_GPIO_WPS_BIT	BIT7

#पूर्ण_अगर /* __HAL_COMMON_H__ */
