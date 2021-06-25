<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL8723BE_REG_H__
#घोषणा __RTL8723BE_REG_H__

#घोषणा TXPKT_BUF_SELECT			0x69
#घोषणा RXPKT_BUF_SELECT			0xA5
#घोषणा DISABLE_TRXPKT_BUF_ACCESS		0x0

#घोषणा REG_SYS_ISO_CTRL			0x0000
#घोषणा REG_SYS_FUNC_EN				0x0002
#घोषणा REG_APS_FSMCO				0x0004
#घोषणा REG_SYS_CLKR				0x0008
#घोषणा REG_9346CR				0x000A
#घोषणा REG_EE_VPD				0x000C
#घोषणा REG_AFE_MISC				0x0010
#घोषणा REG_SPS0_CTRL				0x0011
#घोषणा REG_SPS_OCP_CFG				0x0018
#घोषणा REG_RSV_CTRL				0x001C
#घोषणा REG_RF_CTRL				0x001F
#घोषणा REG_LDOA15_CTRL				0x0020
#घोषणा REG_LDOV12D_CTRL			0x0021
#घोषणा REG_LDOHCI12_CTRL			0x0022
#घोषणा REG_LPLDO_CTRL				0x0023
#घोषणा REG_AFE_XTAL_CTRL			0x0024
/* 1.5v क्रम 8188EE test chip, 1.4v क्रम MP chip */
#घोषणा REG_AFE_LDO_CTRL			0x0027
#घोषणा REG_AFE_PLL_CTRL			0x0028
#घोषणा REG_MAC_PHY_CTRL			0x002c
#घोषणा REG_EFUSE_CTRL				0x0030
#घोषणा REG_EFUSE_TEST				0x0034
#घोषणा REG_PWR_DATA				0x0038
#घोषणा REG_CAL_TIMER				0x003C
#घोषणा REG_ACLK_MON				0x003E
#घोषणा REG_GPIO_MUXCFG				0x0040
#घोषणा REG_GPIO_IO_SEL				0x0042
#घोषणा REG_MAC_PINMUX_CFG			0x0043
#घोषणा REG_GPIO_PIN_CTRL			0x0044
#घोषणा REG_GPIO_INTM				0x0048
#घोषणा REG_LEDCFG0				0x004C
#घोषणा REG_LEDCFG1				0x004D
#घोषणा REG_LEDCFG2				0x004E
#घोषणा REG_LEDCFG3				0x004F
#घोषणा REG_FSIMR				0x0050
#घोषणा REG_FSISR				0x0054
#घोषणा REG_HSIMR				0x0058
#घोषणा REG_HSISR				0x005c
#घोषणा REG_GPIO_PIN_CTRL_2			0x0060
#घोषणा REG_GPIO_IO_SEL_2			0x0062
#घोषणा REG_MULTI_FUNC_CTRL			0x0068
#घोषणा REG_GPIO_OUTPUT				0x006c
#घोषणा REG_AFE_XTAL_CTRL_EXT			0x0078
#घोषणा REG_XCK_OUT_CTRL			0x007c
#घोषणा REG_MCUFWDL				0x0080
#घोषणा REG_WOL_EVENT				0x0081
#घोषणा REG_MCUTSTCFG				0x0084

#घोषणा REG_HIMR				0x00B0
#घोषणा REG_HISR				0x00B4
#घोषणा REG_HIMRE				0x00B8
#घोषणा REG_HISRE				0x00BC
#घोषणा REG_PMC_DBG_CTRL2			0x00CC

#घोषणा REG_EFUSE_ACCESS			0x00CF

#घोषणा REG_BIST_SCAN				0x00D0
#घोषणा REG_BIST_RPT				0x00D4
#घोषणा REG_BIST_ROM_RPT			0x00D8
#घोषणा REG_USB_SIE_INTF			0x00E0
#घोषणा REG_PCIE_MIO_INTF			0x00E4
#घोषणा REG_PCIE_MIO_INTD			0x00E8
#घोषणा REG_HPON_FSM				0x00EC
#घोषणा REG_SYS_CFG				0x00F0
#घोषणा REG_GPIO_OUTSTS				0x00F4
#घोषणा REG_MAC_PHY_CTRL_NORMAL			0x00F8
#घोषणा REG_SYS_CFG1				0x00FC
#घोषणा REG_ROM_VERSION				0x00FD

#घोषणा REG_CR					0x0100
#घोषणा REG_PBP					0x0104
#घोषणा REG_PKT_BUFF_ACCESS_CTRL		0x0106
#घोषणा REG_TRXDMA_CTRL				0x010C
#घोषणा REG_TRXFF_BNDY				0x0114
#घोषणा REG_TRXFF_STATUS			0x0118
#घोषणा REG_RXFF_PTR				0x011C

#घोषणा REG_CPWM				0x012F
#घोषणा REG_FWIMR				0x0130
#घोषणा REG_FWISR				0x0134
#घोषणा REG_PKTBUF_DBG_CTRL			0x0140
#घोषणा REG_PKTBUF_DBG_DATA_L			0x0144
#घोषणा REG_PKTBUF_DBG_DATA_H			0x0148
#घोषणा REG_RXPKTBUF_CTRL			(REG_PKTBUF_DBG_CTRL + 2)

#घोषणा REG_TC0_CTRL				0x0150
#घोषणा REG_TC1_CTRL				0x0154
#घोषणा REG_TC2_CTRL				0x0158
#घोषणा REG_TC3_CTRL				0x015C
#घोषणा REG_TC4_CTRL				0x0160
#घोषणा REG_TCUNIT_BASE				0x0164
#घोषणा REG_MBIST_START				0x0174
#घोषणा REG_MBIST_DONE				0x0178
#घोषणा REG_MBIST_FAIL				0x017C
#घोषणा REG_32K_CTRL				0x0194
#घोषणा REG_C2HEVT_MSG_NORMAL			0x01A0
#घोषणा REG_C2HEVT_CLEAR			0x01AF
#घोषणा REG_C2HEVT_MSG_TEST			0x01B8
#घोषणा REG_MCUTST_1				0x01c0
#घोषणा REG_FMETHR				0x01C8
#घोषणा REG_HMETFR				0x01CC
#घोषणा REG_HMEBOX_0				0x01D0
#घोषणा REG_HMEBOX_1				0x01D4
#घोषणा REG_HMEBOX_2				0x01D8
#घोषणा REG_HMEBOX_3				0x01DC

#घोषणा REG_LLT_INIT				0x01E0
#घोषणा REG_BB_ACCEESS_CTRL			0x01E8
#घोषणा REG_BB_ACCESS_DATA			0x01EC

#घोषणा REG_HMEBOX_EXT_0			0x01F0
#घोषणा REG_HMEBOX_EXT_1			0x01F4
#घोषणा REG_HMEBOX_EXT_2			0x01F8
#घोषणा REG_HMEBOX_EXT_3			0x01FC

#घोषणा REG_RQPN				0x0200
#घोषणा REG_FIFOPAGE				0x0204
#घोषणा REG_TDECTRL				0x0208
#घोषणा REG_TXDMA_OFFSET_CHK			0x020C
#घोषणा REG_TXDMA_STATUS			0x0210
#घोषणा REG_RQPN_NPQ				0x0214

#घोषणा REG_RXDMA_AGG_PG_TH			0x0280
/* FW shall update this रेजिस्टर beक्रमe FW ग_लिखो RXPKT_RELEASE_POLL to 1 */
#घोषणा REG_FW_UPD_RDPTR			0x0284
/* Control the RX DMA.*/
#घोषणा REG_RXDMA_CONTROL			0x0286
/* The number of packets in RXPKTBUF.	*/
#घोषणा REG_RXPKT_NUM				0x0287

#घोषणा	REG_PCIE_CTRL_REG			0x0300
#घोषणा	REG_INT_MIG				0x0304
#घोषणा	REG_BCNQ_DESA				0x0308
#घोषणा	REG_HQ_DESA				0x0310
#घोषणा	REG_MGQ_DESA				0x0318
#घोषणा	REG_VOQ_DESA				0x0320
#घोषणा	REG_VIQ_DESA				0x0328
#घोषणा	REG_BEQ_DESA				0x0330
#घोषणा	REG_BKQ_DESA				0x0338
#घोषणा	REG_RX_DESA				0x0340

#घोषणा	REG_DBI_WDATA				0x0348
#घोषणा	REG_DBI_RDATA				0x034C
#घोषणा	REG_DBI_CTRL				0x0350
#घोषणा	REG_DBI_ADDR				0x0350
#घोषणा	REG_DBI_FLAG				0x0352
#घोषणा	REG_MDIO_WDATA				0x0354
#घोषणा	REG_MDIO_RDATA				0x0356
#घोषणा	REG_MDIO_CTL				0x0358
#घोषणा	REG_DBG_SEL				0x0360
#घोषणा	REG_PCIE_HRPWM				0x0361
#घोषणा	REG_PCIE_HCPWM				0x0363
#घोषणा	REG_UART_CTRL				0x0364
#घोषणा	REG_WATCH_DOG				0x0368
#घोषणा	REG_UART_TX_DESA			0x0370
#घोषणा	REG_UART_RX_DESA			0x0378

#घोषणा	REG_HDAQ_DESA_NODEF			0x0000
#घोषणा	REG_CMDQ_DESA_NODEF			0x0000

#घोषणा REG_VOQ_INFORMATION			0x0400
#घोषणा REG_VIQ_INFORMATION			0x0404
#घोषणा REG_BEQ_INFORMATION			0x0408
#घोषणा REG_BKQ_INFORMATION			0x040C
#घोषणा REG_MGQ_INFORMATION			0x0410
#घोषणा REG_HGQ_INFORMATION			0x0414
#घोषणा REG_BCNQ_INFORMATION			0x0418
#घोषणा REG_TXPKT_EMPTY				0x041A

#घोषणा REG_CPU_MGQ_INFORMATION			0x041C
#घोषणा REG_FWHW_TXQ_CTRL			0x0420
#घोषणा REG_HWSEQ_CTRL				0x0423
#घोषणा REG_TXPKTBUF_BCNQ_BDNY			0x0424
#घोषणा REG_TXPKTBUF_MGQ_BDNY			0x0425
#घोषणा REG_MULTI_BCNQ_EN			0x0426
#घोषणा REG_MULTI_BCNQ_OFFSET			0x0427
#घोषणा REG_SPEC_SIFS				0x0428
#घोषणा REG_RL					0x042A
#घोषणा REG_DARFRC				0x0430
#घोषणा REG_RARFRC				0x0438
#घोषणा REG_RRSR				0x0440
#घोषणा REG_ARFR0				0x0444
#घोषणा REG_ARFR1				0x044C
#घोषणा REG_AMPDU_MAX_TIME			0x0456
#घोषणा REG_AGGLEN_LMT				0x0458
#घोषणा REG_AMPDU_MIN_SPACE			0x045C
#घोषणा REG_TXPKTBUF_WMAC_LBK_BF_HD		0x045D
#घोषणा REG_FAST_EDCA_CTRL			0x0460
#घोषणा REG_RD_RESP_PKT_TH			0x0463
#घोषणा REG_INIRTS_RATE_SEL			0x0480
#घोषणा REG_INIDATA_RATE_SEL			0x0484
#घोषणा REG_POWER_STATUS			0x04A4
#घोषणा REG_POWER_STAGE1			0x04B4
#घोषणा REG_POWER_STAGE2			0x04B8
#घोषणा REG_PKT_LIFE_TIME			0x04C0
#घोषणा REG_STBC_SETTING			0x04C4
#घोषणा REG_HT_SINGLE_AMPDU			0x04C7

#घोषणा REG_PROT_MODE_CTRL			0x04C8
#घोषणा REG_MAX_AGGR_NUM			0x04CA
#घोषणा REG_BAR_MODE_CTRL			0x04CC
#घोषणा REG_RA_TRY_RATE_AGG_LMT			0x04CF
#घोषणा REG_EARLY_MODE_CONTROL			0x04D0
#घोषणा REG_NQOS_SEQ				0x04DC
#घोषणा REG_QOS_SEQ				0x04DE
#घोषणा REG_NEED_CPU_HANDLE			0x04E0
#घोषणा REG_PKT_LOSE_RPT			0x04E1
#घोषणा REG_PTCL_ERR_STATUS			0x04E2
#घोषणा REG_TX_RPT_CTRL				0x04EC
#घोषणा REG_TX_RPT_TIME				0x04F0
#घोषणा REG_DUMMY				0x04FC

#घोषणा REG_EDCA_VO_PARAM			0x0500
#घोषणा REG_EDCA_VI_PARAM			0x0504
#घोषणा REG_EDCA_BE_PARAM			0x0508
#घोषणा REG_EDCA_BK_PARAM			0x050C
#घोषणा REG_BCNTCFG				0x0510
#घोषणा REG_PIFS				0x0512
#घोषणा REG_RDG_PIFS				0x0513
#घोषणा REG_SIFS_CTX				0x0514
#घोषणा REG_SIFS_TRX				0x0516
#घोषणा REG_AGGR_BREAK_TIME			0x051A
#घोषणा REG_SLOT				0x051B
#घोषणा REG_TX_PTCL_CTRL			0x0520
#घोषणा REG_TXPAUSE				0x0522
#घोषणा REG_DIS_TXREQ_CLR			0x0523
#घोषणा REG_RD_CTRL				0x0524
#घोषणा REG_TBTT_PROHIBIT			0x0540
#घोषणा REG_RD_NAV_NXT				0x0544
#घोषणा REG_NAV_PROT_LEN			0x0546
#घोषणा REG_BCN_CTRL				0x0550
#घोषणा REG_MBID_NUM				0x0552
#घोषणा REG_DUAL_TSF_RST			0x0553
#घोषणा REG_BCN_INTERVAL			0x0554
#घोषणा REG_MBSSID_BCN_SPACE			0x0554
#घोषणा REG_DRVERLYINT				0x0558
#घोषणा REG_BCNDMATIM				0x0559
#घोषणा REG_ATIMWND				0x055A
#घोषणा REG_USTIME_TSF				0x055C
#घोषणा REG_BCN_MAX_ERR				0x055D
#घोषणा REG_RXTSF_OFFSET_CCK			0x055E
#घोषणा REG_RXTSF_OFFSET_OFDM			0x055F
#घोषणा REG_TSFTR				0x0560
#घोषणा REG_INIT_TSFTR				0x0564
#घोषणा REG_SECONDARY_CCA_CTRL			0x0577
#घोषणा REG_PSTIMER				0x0580
#घोषणा REG_TIMER0				0x0584
#घोषणा REG_TIMER1				0x0588
#घोषणा REG_ACMHWCTRL				0x05C0
#घोषणा REG_ACMRSTCTRL				0x05C1
#घोषणा REG_ACMAVG				0x05C2
#घोषणा REG_VO_ADMTIME				0x05C4
#घोषणा REG_VI_ADMTIME				0x05C6
#घोषणा REG_BE_ADMTIME				0x05C8
#घोषणा REG_EDCA_RANDOM_GEN			0x05CC
#घोषणा REG_SCH_TXCMD				0x05D0

#घोषणा REG_APSD_CTRL				0x0600
#घोषणा REG_BWOPMODE				0x0603
#घोषणा REG_TCR					0x0604
#घोषणा REG_RCR					0x0608
#घोषणा REG_RX_PKT_LIMIT			0x060C
#घोषणा REG_RX_DLK_TIME				0x060D
#घोषणा REG_RX_DRVINFO_SZ			0x060F

#घोषणा REG_MACID				0x0610
#घोषणा REG_BSSID				0x0618
#घोषणा REG_MAR					0x0620
#घोषणा REG_MBIDCAMCFG				0x0628

#घोषणा REG_USTIME_EDCA				0x0638
#घोषणा REG_MAC_SPEC_SIFS			0x063A
#घोषणा REG_RESP_SIFS_CCK			0x063C
#घोषणा REG_RESP_SIFS_OFDM			0x063E
#घोषणा REG_ACKTO				0x0640
#घोषणा REG_CTS2TO				0x0641
#घोषणा REG_EIFS				0x0642

#घोषणा REG_NAV_CTRL				0x0650
#घोषणा	REG_NAV_UPPER				0x0652
#घोषणा REG_BACAMCMD				0x0654
#घोषणा REG_BACAMCONTENT			0x0658
#घोषणा REG_LBDLY				0x0660
#घोषणा REG_FWDLY				0x0661
#घोषणा REG_RXERR_RPT				0x0664
#घोषणा REG_TRXPTCL_CTL				0x0668

#घोषणा REG_CAMCMD				0x0670
#घोषणा REG_CAMWRITE				0x0674
#घोषणा REG_CAMREAD				0x0678
#घोषणा REG_CAMDBG				0x067C
#घोषणा REG_SECCFG				0x0680

#घोषणा REG_WOW_CTRL				0x0690
#घोषणा REG_PSSTATUS				0x0691
#घोषणा REG_PS_RX_INFO				0x0692
#घोषणा REG_UAPSD_TID				0x0693
#घोषणा REG_LPNAV_CTRL				0x0694
#घोषणा REG_WKFMCAM_NUM				0x0698
#घोषणा REG_WKFMCAM_RWD				0x069C
#घोषणा REG_RXFLTMAP0				0x06A0
#घोषणा REG_RXFLTMAP1				0x06A2
#घोषणा REG_RXFLTMAP2				0x06A4
#घोषणा REG_BCN_PSR_RPT				0x06A8
#घोषणा REG_CALB32K_CTRL			0x06AC
#घोषणा REG_PKT_MON_CTRL			0x06B4
#घोषणा REG_BT_COEX_TABLE			0x06C0
#घोषणा REG_WMAC_RESP_TXINFO			0x06D8

#घोषणा REG_USB_INFO				0xFE17
#घोषणा REG_USB_SPECIAL_OPTION			0xFE55
#घोषणा REG_USB_DMA_AGG_TO			0xFE5B
#घोषणा REG_USB_AGG_TO				0xFE5C
#घोषणा REG_USB_AGG_TH				0xFE5D

#घोषणा REG_TEST_USB_TXQS			0xFE48
#घोषणा REG_TEST_SIE_VID			0xFE60
#घोषणा REG_TEST_SIE_PID			0xFE62
#घोषणा REG_TEST_SIE_OPTIONAL			0xFE64
#घोषणा REG_TEST_SIE_CHIRP_K			0xFE65
#घोषणा REG_TEST_SIE_PHY			0xFE66
#घोषणा REG_TEST_SIE_MAC_ADDR			0xFE70
#घोषणा REG_TEST_SIE_STRING			0xFE80

#घोषणा REG_NORMAL_SIE_VID			0xFE60
#घोषणा REG_NORMAL_SIE_PID			0xFE62
#घोषणा REG_NORMAL_SIE_OPTIONAL			0xFE64
#घोषणा REG_NORMAL_SIE_EP			0xFE65
#घोषणा REG_NORMAL_SIE_PHY			0xFE68
#घोषणा REG_NORMAL_SIE_MAC_ADDR			0xFE70
#घोषणा REG_NORMAL_SIE_STRING			0xFE80

#घोषणा	CR9346				REG_9346CR
#घोषणा	MSR				(REG_CR + 2)
#घोषणा	ISR				REG_HISR
#घोषणा	TSFR				REG_TSFTR

#घोषणा	MACIDR0				REG_MACID
#घोषणा	MACIDR4				(REG_MACID + 4)

#घोषणा PBP				REG_PBP

#घोषणा	IDR0				MACIDR0
#घोषणा	IDR4				MACIDR4

#घोषणा	UNUSED_REGISTER			0x1BF
#घोषणा	DCAM				UNUSED_REGISTER
#घोषणा	PSR				UNUSED_REGISTER
#घोषणा BBADDR				UNUSED_REGISTER
#घोषणा	PHYDATAR			UNUSED_REGISTER

#घोषणा	INVALID_BBRF_VALUE		0x12345678

#घोषणा	MAX_MSS_DENSITY_2T		0x13
#घोषणा	MAX_MSS_DENSITY_1T		0x0A

#घोषणा	CMDEEPROM_EN			BIT(5)
#घोषणा	CMDEEPROM_SEL			BIT(4)
#घोषणा	CMD9346CR_9356SEL		BIT(4)
#घोषणा	AUTOLOAD_EEPROM			(CMDEEPROM_EN | CMDEEPROM_SEL)
#घोषणा	AUTOLOAD_EFUSE			CMDEEPROM_EN

#घोषणा	GPIOSEL_GPIO			0
#घोषणा	GPIOSEL_ENBT			BIT(5)

#घोषणा	GPIO_IN				REG_GPIO_PIN_CTRL
#घोषणा	GPIO_OUT			(REG_GPIO_PIN_CTRL + 1)
#घोषणा	GPIO_IO_SEL			(REG_GPIO_PIN_CTRL + 2)
#घोषणा	GPIO_MOD			(REG_GPIO_PIN_CTRL + 3)

/* 8723/8188E Host System Interrupt Mask Register (offset 0x58, 32 byte) */
#घोषणा	HSIMR_GPIO12_0_INT_EN			BIT(0)
#घोषणा	HSIMR_SPS_OCP_INT_EN			BIT(5)
#घोषणा	HSIMR_RON_INT_EN			BIT(6)
#घोषणा	HSIMR_PDN_INT_EN			BIT(7)
#घोषणा	HSIMR_GPIO9_INT_EN			BIT(25)

/*  8723/8188E Host System Interrupt Status Register (offset 0x5C, 32 byte) */
#घोषणा	HSISR_GPIO12_0_INT			BIT(0)
#घोषणा	HSISR_SPS_OCP_INT			BIT(5)
#घोषणा	HSISR_RON_INT_EN			BIT(6)
#घोषणा	HSISR_PDNINT				BIT(7)
#घोषणा	HSISR_GPIO9_INT				BIT(25)

#घोषणा	MSR_NOLINK				0x00
#घोषणा	MSR_ADHOC				0x01
#घोषणा	MSR_INFRA				0x02
#घोषणा	MSR_AP					0x03

#घोषणा	RRSR_RSC_OFFSET				21
#घोषणा	RRSR_SHORT_OFFSET			23
#घोषणा	RRSR_RSC_BW_40M				0x600000
#घोषणा	RRSR_RSC_UPSUBCHNL			0x400000
#घोषणा	RRSR_RSC_LOWSUBCHNL			0x200000
#घोषणा	RRSR_SHORT				0x800000
#घोषणा	RRSR_1M					BIT(0)
#घोषणा	RRSR_2M					BIT(1)
#घोषणा	RRSR_5_5M				BIT(2)
#घोषणा	RRSR_11M				BIT(3)
#घोषणा	RRSR_6M					BIT(4)
#घोषणा	RRSR_9M					BIT(5)
#घोषणा	RRSR_12M				BIT(6)
#घोषणा	RRSR_18M				BIT(7)
#घोषणा	RRSR_24M				BIT(8)
#घोषणा	RRSR_36M				BIT(9)
#घोषणा	RRSR_48M				BIT(10)
#घोषणा	RRSR_54M				BIT(11)
#घोषणा	RRSR_MCS0				BIT(12)
#घोषणा	RRSR_MCS1				BIT(13)
#घोषणा	RRSR_MCS2				BIT(14)
#घोषणा	RRSR_MCS3				BIT(15)
#घोषणा	RRSR_MCS4				BIT(16)
#घोषणा	RRSR_MCS5				BIT(17)
#घोषणा	RRSR_MCS6				BIT(18)
#घोषणा	RRSR_MCS7				BIT(19)
#घोषणा	BRSR_ACKSHORTPMB			BIT(23)

#घोषणा	RATR_1M					0x00000001
#घोषणा	RATR_2M					0x00000002
#घोषणा	RATR_55M				0x00000004
#घोषणा	RATR_11M				0x00000008
#घोषणा	RATR_6M					0x00000010
#घोषणा	RATR_9M					0x00000020
#घोषणा	RATR_12M				0x00000040
#घोषणा	RATR_18M				0x00000080
#घोषणा	RATR_24M				0x00000100
#घोषणा	RATR_36M				0x00000200
#घोषणा	RATR_48M				0x00000400
#घोषणा	RATR_54M				0x00000800
#घोषणा	RATR_MCS0				0x00001000
#घोषणा	RATR_MCS1				0x00002000
#घोषणा	RATR_MCS2				0x00004000
#घोषणा	RATR_MCS3				0x00008000
#घोषणा	RATR_MCS4				0x00010000
#घोषणा	RATR_MCS5				0x00020000
#घोषणा	RATR_MCS6				0x00040000
#घोषणा	RATR_MCS7				0x00080000
#घोषणा	RATR_MCS8				0x00100000
#घोषणा	RATR_MCS9				0x00200000
#घोषणा	RATR_MCS10				0x00400000
#घोषणा	RATR_MCS11				0x00800000
#घोषणा	RATR_MCS12				0x01000000
#घोषणा	RATR_MCS13				0x02000000
#घोषणा	RATR_MCS14				0x04000000
#घोषणा	RATR_MCS15				0x08000000

#घोषणा RATE_1M					BIT(0)
#घोषणा RATE_2M					BIT(1)
#घोषणा RATE_5_5M				BIT(2)
#घोषणा RATE_11M				BIT(3)
#घोषणा RATE_6M					BIT(4)
#घोषणा RATE_9M					BIT(5)
#घोषणा RATE_12M				BIT(6)
#घोषणा RATE_18M				BIT(7)
#घोषणा RATE_24M				BIT(8)
#घोषणा RATE_36M				BIT(9)
#घोषणा RATE_48M				BIT(10)
#घोषणा RATE_54M				BIT(11)
#घोषणा RATE_MCS0				BIT(12)
#घोषणा RATE_MCS1				BIT(13)
#घोषणा RATE_MCS2				BIT(14)
#घोषणा RATE_MCS3				BIT(15)
#घोषणा RATE_MCS4				BIT(16)
#घोषणा RATE_MCS5				BIT(17)
#घोषणा RATE_MCS6				BIT(18)
#घोषणा RATE_MCS7				BIT(19)
#घोषणा RATE_MCS8				BIT(20)
#घोषणा RATE_MCS9				BIT(21)
#घोषणा RATE_MCS10				BIT(22)
#घोषणा RATE_MCS11				BIT(23)
#घोषणा RATE_MCS12				BIT(24)
#घोषणा RATE_MCS13				BIT(25)
#घोषणा RATE_MCS14				BIT(26)
#घोषणा RATE_MCS15				BIT(27)

#घोषणा	RATE_ALL_CCK		(RATR_1M | RATR_2M | RATR_55M | RATR_11M)
#घोषणा	RATE_ALL_OFDM_AG	(RATR_6M | RATR_9M | RATR_12M | RATR_18M |\
				 RATR_24M | RATR_36M | RATR_48M | RATR_54M)
#घोषणा	RATE_ALL_OFDM_1SS	(RATR_MCS0 | RATR_MCS1 | RATR_MCS2 |\
				 RATR_MCS3 | RATR_MCS4 | RATR_MCS5 |\
				 RATR_MCS6 | RATR_MCS7)
#घोषणा	RATE_ALL_OFDM_2SS	(RATR_MCS8 | RATR_MCS9 | RATR_MCS10 |\
				 RATR_MCS11 | RATR_MCS12 | RATR_MCS13 |\
				 RATR_MCS14 | RATR_MCS15)

#घोषणा	BW_OPMODE_20MHZ				BIT(2)
#घोषणा	BW_OPMODE_5G				BIT(1)
#घोषणा	BW_OPMODE_11J				BIT(0)

#घोषणा	CAM_VALID				BIT(15)
#घोषणा	CAM_NOTVALID				0x0000
#घोषणा	CAM_USEDK				BIT(5)

#घोषणा	CAM_NONE				0x0
#घोषणा	CAM_WEP40				0x01
#घोषणा	CAM_TKIP				0x02
#घोषणा	CAM_AES					0x04
#घोषणा	CAM_WEP104				0x05

#घोषणा	TOTAL_CAM_ENTRY				32
#घोषणा	HALF_CAM_ENTRY				16

#घोषणा	CAM_WRITE				BIT(16)
#घोषणा	CAM_READ				0x00000000
#घोषणा	CAM_POLLINIG				BIT(31)

#घोषणा	SCR_USEDK				0x01
#घोषणा	SCR_TXSEC_ENABLE			0x02
#घोषणा	SCR_RXSEC_ENABLE			0x04

#घोषणा	WOW_PMEN				BIT(0)
#घोषणा	WOW_WOMEN				BIT(1)
#घोषणा	WOW_MAGIC				BIT(2)
#घोषणा	WOW_UWF					BIT(3)

/*********************************************
*       8723BE IMR/ISR bits
*********************************************
*/
#घोषणा	IMR_DISABLED				0x0
/* IMR DW0(0x0060-0063) Bit 0-31 */
#घोषणा	IMR_TXCCK		BIT(30)	/* TXRPT पूर्णांकerrupt when
					 * CCX bit of the packet is set
					 */
#घोषणा	IMR_PSTIMEOUT		BIT(29)	/* Power Save Time Out Interrupt */
#घोषणा	IMR_GTINT4		BIT(28)	/* When GTIMER4 expires,
					 * this bit is set to 1
					 */
#घोषणा	IMR_GTINT3		BIT(27)	/* When GTIMER3 expires,
					 * this bit is set to 1
					 */
#घोषणा	IMR_TBDER		BIT(26)	/* Transmit Beacon0 Error */
#घोषणा	IMR_TBDOK		BIT(25)	/* Transmit Beacon0 OK */
#घोषणा	IMR_TSF_BIT32_TOGGLE	BIT(24)	/* TSF Timer BIT32 toggle
					 * indication पूर्णांकerrupt
					 */
#घोषणा	IMR_BCNDMAINT0		BIT(20)	/* Beacon DMA Interrupt 0 */
#घोषणा	IMR_BCNDOK0		BIT(16)	/* Beacon Queue DMA OK0 */
#घोषणा	IMR_HSISR_IND_ON_INT	BIT(15)	/* HSISR Indicator (HSIMR & HSISR is
					 * true, this bit is set to 1)
					 */
#घोषणा	IMR_BCNDMAINT_E		BIT(14)	/* Beacon DMA Interrupt
					 * Extension क्रम Win7
					 */
#घोषणा	IMR_ATIMEND		BIT(12)	/* CTWidnow End or ATIM Winकरोw End */
#घोषणा	IMR_HISR1_IND_INT	BIT(11)	/* HISR1 Indicator (HISR1 & HIMR1 is
					 * true, this bit is set to 1)
					 */
#घोषणा	IMR_C2HCMD		BIT(10)	/* CPU to Host Command INT Status,
					 * Write 1 clear
					 */
#घोषणा	IMR_CPWM2		BIT(9)	/* CPU घातer Mode exchange INT Status,
					 * Write 1 clear
					 */
#घोषणा	IMR_CPWM		BIT(8)	/* CPU घातer Mode exchange INT Status,
					 * Write 1 clear
					 */
#घोषणा	IMR_HIGHDOK		BIT(7)	/* High Queue DMA OK */
#घोषणा	IMR_MGNTDOK		BIT(6)	/* Management Queue DMA OK */
#घोषणा	IMR_BKDOK		BIT(5)	/* AC_BK DMA OK	*/
#घोषणा	IMR_BEDOK		BIT(4)	/* AC_BE DMA OK	*/
#घोषणा	IMR_VIDOK		BIT(3)	/* AC_VI DMA OK	*/
#घोषणा	IMR_VODOK		BIT(2)	/* AC_VO DMA OK	*/
#घोषणा	IMR_RDU			BIT(1)	/* Rx Descriptor Unavailable */
#घोषणा	IMR_ROK			BIT(0)	/* Receive DMA OK */

/* IMR DW1(0x00B4-00B7) Bit 0-31 */
#घोषणा	IMR_BCNDMAINT7		BIT(27)	/* Beacon DMA Interrupt 7 */
#घोषणा	IMR_BCNDMAINT6		BIT(26)	/* Beacon DMA Interrupt 6 */
#घोषणा	IMR_BCNDMAINT5		BIT(25)	/* Beacon DMA Interrupt 5 */
#घोषणा	IMR_BCNDMAINT4		BIT(24)	/* Beacon DMA Interrupt 4 */
#घोषणा	IMR_BCNDMAINT3		BIT(23)	/* Beacon DMA Interrupt 3 */
#घोषणा	IMR_BCNDMAINT2		BIT(22)	/* Beacon DMA Interrupt 2 */
#घोषणा	IMR_BCNDMAINT1		BIT(21)	/* Beacon DMA Interrupt 1 */
#घोषणा	IMR_BCNDOK7		BIT(20)	/* Beacon Queue DMA OK Interrup 7 */
#घोषणा	IMR_BCNDOK6		BIT(19)	/* Beacon Queue DMA OK Interrup 6 */
#घोषणा	IMR_BCNDOK5		BIT(18)	/* Beacon Queue DMA OK Interrup 5 */
#घोषणा	IMR_BCNDOK4		BIT(17)	/* Beacon Queue DMA OK Interrup 4 */
#घोषणा	IMR_BCNDOK3		BIT(16)	/* Beacon Queue DMA OK Interrup 3 */
#घोषणा	IMR_BCNDOK2		BIT(15)	/* Beacon Queue DMA OK Interrup 2 */
#घोषणा	IMR_BCNDOK1		BIT(14)	/* Beacon Queue DMA OK Interrup 1 */
#घोषणा	IMR_ATIMEND_E		BIT(13)	/* ATIM Winकरोw End Extension क्रम Win7 */
#घोषणा	IMR_TXERR		BIT(11)	/* Tx Error Flag Interrupt Status,
					 * ग_लिखो 1 clear.
					 */
#घोषणा	IMR_RXERR		BIT(10)	/* Rx Error Flag INT Status,
					 * Write 1 clear
					 */
#घोषणा	IMR_TXFOVW		BIT(9)	/* Transmit FIFO Overflow */
#घोषणा	IMR_RXFOVW		BIT(8)	/* Receive FIFO Overflow */

#घोषणा	HWSET_MAX_SIZE			512
#घोषणा EFUSE_MAX_SECTION		64
#घोषणा EFUSE_REAL_CONTENT_LEN		256
#घोषणा EFUSE_OOB_PROTECT_BYTES		18 /* PG data exclude header,
					    * dummy 7 bytes frome CP test
					    * and reserved 1byte.
					    */

#घोषणा	EEPROM_DEFAULT_TSSI			0x0
#घोषणा EEPROM_DEFAULT_TXPOWERDIFF		0x0
#घोषणा EEPROM_DEFAULT_CRYSTALCAP		0x5
#घोषणा EEPROM_DEFAULT_BOARDTYPE		0x02
#घोषणा EEPROM_DEFAULT_TXPOWER			0x1010
#घोषणा	EEPROM_DEFAULT_HT2T_TXPWR		0x10

#घोषणा	EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF	0x3
#घोषणा	EEPROM_DEFAULT_THERMALMETER		0x18
#घोषणा	EEPROM_DEFAULT_ANTTXPOWERDIFF		0x0
#घोषणा	EEPROM_DEFAULT_TXPWDIFF_CRYSTALCAP	0x5
#घोषणा	EEPROM_DEFAULT_TXPOWERLEVEL		0x22
#घोषणा	EEPROM_DEFAULT_HT40_2SDIFF		0x0
#घोषणा EEPROM_DEFAULT_HT20_DIFF		2
#घोषणा	EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF	0x3
#घोषणा EEPROM_DEFAULT_HT40_PWRMAXOFFSET	0
#घोषणा EEPROM_DEFAULT_HT20_PWRMAXOFFSET	0

#घोषणा RF_OPTION1				0x79
#घोषणा RF_OPTION2				0x7A
#घोषणा RF_OPTION3				0x7B
#घोषणा EEPROM_RF_BT_SETTING_8723B		0xC3

#घोषणा EEPROM_DEFAULT_PID			0x1234
#घोषणा EEPROM_DEFAULT_VID			0x5678
#घोषणा EEPROM_DEFAULT_CUSTOMERID		0xAB
#घोषणा EEPROM_DEFAULT_SUBCUSTOMERID		0xCD
#घोषणा EEPROM_DEFAULT_VERSION			0

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

#घोषणा	RTL8723BE_EEPROM_ID			0x8129

#घोषणा EEPROM_HPON				0x02
#घोषणा EEPROM_CLK				0x06
#घोषणा EEPROM_TESTR				0x08

#घोषणा EEPROM_TXPOWERCCK			0x10
#घोषणा	EEPROM_TXPOWERHT40_1S			0x16
#घोषणा EEPROM_TXPOWERHT20DIFF			0x1B
#घोषणा EEPROM_TXPOWER_OFDMDIFF			0x1B

#घोषणा	EEPROM_TX_PWR_INX			0x10

#घोषणा	EEPROM_CHANNELPLAN			0xB8
#घोषणा	EEPROM_XTAL_8723BE			0xB9
#घोषणा	EEPROM_THERMAL_METER_88E		0xBA
#घोषणा	EEPROM_IQK_LCK_88E			0xBB

#घोषणा	EEPROM_RF_BOARD_OPTION_88E		0xC1
#घोषणा	EEPROM_RF_FEATURE_OPTION_88E		0xC2
#घोषणा	EEPROM_RF_BT_SETTING_88E		0xC3
#घोषणा	EEPROM_VERSION				0xC4
#घोषणा	EEPROM_CUSTOMER_ID			0xC5
#घोषणा	EEPROM_RF_ANTENNA_OPT_88E		0xC9

#घोषणा	EEPROM_MAC_ADDR				0xD0
#घोषणा EEPROM_VID				0xD6
#घोषणा EEPROM_DID				0xD8
#घोषणा EEPROM_SVID				0xDA
#घोषणा EEPROM_SMID				0xDC

#घोषणा	STOPBECON				BIT(6)
#घोषणा	STOPHIGHT				BIT(5)
#घोषणा	STOPMGT					BIT(4)
#घोषणा	STOPVO					BIT(3)
#घोषणा	STOPVI					BIT(2)
#घोषणा	STOPBE					BIT(1)
#घोषणा	STOPBK					BIT(0)

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
#घोषणा	RCR_CBSSID				RCR_CBSSID_DATA
#घोषणा	RCR_APWRMGT				BIT(5)
#घोषणा	RCR_ADD3				BIT(4)
#घोषणा	RCR_AB					BIT(3)
#घोषणा	RCR_AM					BIT(2)
#घोषणा	RCR_APM					BIT(1)
#घोषणा	RCR_AAP					BIT(0)
#घोषणा	RCR_MXDMA_OFFSET			8
#घोषणा	RCR_FIFO_OFFSET				13

#घोषणा RSV_CTRL				0x001C
#घोषणा RD_CTRL					0x0524

#घोषणा REG_USB_INFO				0xFE17
#घोषणा REG_USB_SPECIAL_OPTION			0xFE55
#घोषणा REG_USB_DMA_AGG_TO			0xFE5B
#घोषणा REG_USB_AGG_TO				0xFE5C
#घोषणा REG_USB_AGG_TH				0xFE5D

#घोषणा REG_USB_VID				0xFE60
#घोषणा REG_USB_PID				0xFE62
#घोषणा REG_USB_OPTIONAL			0xFE64
#घोषणा REG_USB_CHIRP_K				0xFE65
#घोषणा REG_USB_PHY				0xFE66
#घोषणा REG_USB_MAC_ADDR			0xFE70
#घोषणा REG_USB_HRPWM				0xFE58
#घोषणा REG_USB_HCPWM				0xFE57

#घोषणा SW18_FPWM				BIT(3)

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

#घोषणा	BOOT_FROM_EEPROM			BIT(4)
#घोषणा	EEPROM_EN				BIT(5)

#घोषणा AFE_BGEN				BIT(0)
#घोषणा AFE_MBEN				BIT(1)
#घोषणा MAC_ID_EN				BIT(7)

#घोषणा WLOCK_ALL				BIT(0)
#घोषणा WLOCK_00				BIT(1)
#घोषणा WLOCK_04				BIT(2)
#घोषणा WLOCK_08				BIT(3)
#घोषणा WLOCK_40				BIT(4)
#घोषणा R_DIS_PRST_0				BIT(5)
#घोषणा R_DIS_PRST_1				BIT(6)
#घोषणा LOCK_ALL_EN				BIT(7)

#घोषणा RF_EN					BIT(0)
#घोषणा RF_RSTB					BIT(1)
#घोषणा RF_SDMRSTB				BIT(2)

#घोषणा LDA15_EN				BIT(0)
#घोषणा LDA15_STBY				BIT(1)
#घोषणा LDA15_OBUF				BIT(2)
#घोषणा LDA15_REG_VOS				BIT(3)
#घोषणा _LDA15_VOADJ(x)				(((x) & 0x7) << 4)

#घोषणा LDV12_EN				BIT(0)
#घोषणा LDV12_SDBY				BIT(1)
#घोषणा LPLDO_HSM				BIT(2)
#घोषणा LPLDO_LSM_DIS				BIT(3)
#घोषणा _LDV12_VADJ(x)				(((x) & 0xF) << 4)

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

#घोषणा ALD_EN					BIT(18)
#घोषणा EF_PD					BIT(19)
#घोषणा EF_FLAG					BIT(31)

#घोषणा EF_TRPT					BIT(7)
#घोषणा LDOE25_EN				BIT(31)

#घोषणा RSM_EN					BIT(0)
#घोषणा TIMER_EN				BIT(4)

#घोषणा TRSW0EN					BIT(2)
#घोषणा TRSW1EN					BIT(3)
#घोषणा EROM_EN					BIT(4)
#घोषणा ENBT					BIT(5)
#घोषणा ENUART					BIT(8)
#घोषणा UART_910				BIT(9)
#घोषणा ENPMAC					BIT(10)
#घोषणा SIC_SWRST				BIT(11)
#घोषणा ENSIC					BIT(12)
#घोषणा SIC_23					BIT(13)
#घोषणा ENHDP					BIT(14)
#घोषणा SIC_LBK					BIT(15)

#घोषणा LED0PL					BIT(4)
#घोषणा LED1PL					BIT(12)
#घोषणा LED0DIS					BIT(7)

#घोषणा MCUFWDL_EN				BIT(0)
#घोषणा MCUFWDL_RDY				BIT(1)
#घोषणा FWDL_CHKSUM_RPT				BIT(2)
#घोषणा MACINI_RDY				BIT(3)
#घोषणा BBINI_RDY				BIT(4)
#घोषणा RFINI_RDY				BIT(5)
#घोषणा WINTINI_RDY				BIT(6)
#घोषणा CPRST					BIT(23)

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
#घोषणा VENDOR_ID				BIT(19)
#घोषणा PAD_HWPD_IDN				BIT(22)
#घोषणा TRP_VAUX_EN				BIT(23)
#घोषणा TRP_BT_EN				BIT(24)
#घोषणा BD_PKG_SEL				BIT(25)
#घोषणा BD_HCI_SEL				BIT(26)
#घोषणा TYPE_ID					BIT(27)

#घोषणा CHIP_VER_RTL_MASK			0xF000
#घोषणा CHIP_VER_RTL_SHIFT			12

#घोषणा REG_LBMODE				(REG_CR + 3)

#घोषणा HCI_TXDMA_EN				BIT(0)
#घोषणा HCI_RXDMA_EN				BIT(1)
#घोषणा TXDMA_EN				BIT(2)
#घोषणा RXDMA_EN				BIT(3)
#घोषणा PROTOCOL_EN				BIT(4)
#घोषणा SCHEDULE_EN				BIT(5)
#घोषणा MACTXEN					BIT(6)
#घोषणा MACRXEN					BIT(7)
#घोषणा ENSWBCN					BIT(8)
#घोषणा ENSEC					BIT(9)

#घोषणा _NETTYPE(x)				(((x) & 0x3) << 16)
#घोषणा MASK_NETTYPE				0x30000
#घोषणा NT_NO_LINK				0x0
#घोषणा NT_LINK_AD_HOC				0x1
#घोषणा NT_LINK_AP				0x2
#घोषणा NT_AS_AP				0x3

#घोषणा _LBMODE(x)				(((x) & 0xF) << 24)
#घोषणा MASK_LBMODE				0xF000000
#घोषणा LOOPBACK_NORMAL				0x0
#घोषणा LOOPBACK_IMMEDIATELY			0xB
#घोषणा LOOPBACK_MAC_DELAY			0x3
#घोषणा LOOPBACK_PHY				0x1
#घोषणा LOOPBACK_DMA				0x7

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

#घोषणा RXDMA_ARBBW_EN				BIT(0)
#घोषणा RXSHFT_EN				BIT(1)
#घोषणा RXDMA_AGG_EN				BIT(2)
#घोषणा QS_VO_QUEUE				BIT(8)
#घोषणा QS_VI_QUEUE				BIT(9)
#घोषणा QS_BE_QUEUE				BIT(10)
#घोषणा QS_BK_QUEUE				BIT(11)
#घोषणा QS_MANAGER_QUEUE			BIT(12)
#घोषणा QS_HIGH_QUEUE				BIT(13)

#घोषणा HQSEL_VOQ				BIT(0)
#घोषणा HQSEL_VIQ				BIT(1)
#घोषणा HQSEL_BEQ				BIT(2)
#घोषणा HQSEL_BKQ				BIT(3)
#घोषणा HQSEL_MGTQ				BIT(4)
#घोषणा HQSEL_HIQ				BIT(5)

#घोषणा _TXDMA_HIQ_MAP(x)			(((x)&0x3) << 14)
#घोषणा _TXDMA_MGQ_MAP(x)			(((x)&0x3) << 12)
#घोषणा _TXDMA_BKQ_MAP(x)			(((x)&0x3) << 10)
#घोषणा _TXDMA_BEQ_MAP(x)			(((x)&0x3) << 8)
#घोषणा _TXDMA_VIQ_MAP(x)			(((x)&0x3) << 6)
#घोषणा _TXDMA_VOQ_MAP(x)			(((x)&0x3) << 4)

#घोषणा QUEUE_LOW				1
#घोषणा QUEUE_NORMAL				2
#घोषणा QUEUE_HIGH				3

#घोषणा _LLT_NO_ACTIVE				0x0
#घोषणा _LLT_WRITE_ACCESS			0x1
#घोषणा _LLT_READ_ACCESS			0x2

#घोषणा _LLT_INIT_DATA(x)			((x) & 0xFF)
#घोषणा _LLT_INIT_ADDR(x)			(((x) & 0xFF) << 8)
#घोषणा _LLT_OP(x)				(((x) & 0x3) << 30)
#घोषणा _LLT_OP_VALUE(x)			(((x) >> 30) & 0x3)

#घोषणा BB_WRITE_READ_MASK			(BIT(31) | BIT(30))
#घोषणा BB_WRITE_EN				BIT(30)
#घोषणा BB_READ_EN				BIT(31)

#घोषणा _HPQ(x)					((x) & 0xFF)
#घोषणा _LPQ(x)					(((x) & 0xFF) << 8)
#घोषणा _PUBQ(x)				(((x) & 0xFF) << 16)
#घोषणा _NPQ(x)					((x) & 0xFF)

#घोषणा HPQ_PUBLIC_DIS				BIT(24)
#घोषणा LPQ_PUBLIC_DIS				BIT(25)
#घोषणा LD_RQPN					BIT(31)

#घोषणा BCN_VALID				BIT(16)
#घोषणा BCN_HEAD(x)				(((x) & 0xFF) << 8)
#घोषणा	BCN_HEAD_MASK				0xFF00

#घोषणा BLK_DESC_NUM_SHIFT			4
#घोषणा BLK_DESC_NUM_MASK			0xF

#घोषणा DROP_DATA_EN				BIT(9)

#घोषणा EN_AMPDU_RTY_NEW			BIT(7)

#घोषणा _INIRTSMCS_SEL(x)			((x) & 0x3F)

#घोषणा _SPEC_SIFS_CCK(x)			((x) & 0xFF)
#घोषणा _SPEC_SIFS_OFDM(x)			(((x) & 0xFF) << 8)

#घोषणा RATE_REG_BITMAP_ALL			0xFFFFF

#घोषणा _RRSC_BITMAP(x)				((x) & 0xFFFFF)

#घोषणा _RRSR_RSC(x)				(((x) & 0x3) << 21)
#घोषणा RRSR_RSC_RESERVED			0x0
#घोषणा RRSR_RSC_UPPER_SUBCHANNEL		0x1
#घोषणा RRSR_RSC_LOWER_SUBCHANNEL		0x2
#घोषणा RRSR_RSC_DUPLICATE_MODE			0x3

#घोषणा USE_SHORT_G1				BIT(20)

#घोषणा _AGGLMT_MCS0(x)				((x) & 0xF)
#घोषणा _AGGLMT_MCS1(x)				(((x) & 0xF) << 4)
#घोषणा _AGGLMT_MCS2(x)				(((x) & 0xF) << 8)
#घोषणा _AGGLMT_MCS3(x)				(((x) & 0xF) << 12)
#घोषणा _AGGLMT_MCS4(x)				(((x) & 0xF) << 16)
#घोषणा _AGGLMT_MCS5(x)				(((x) & 0xF) << 20)
#घोषणा _AGGLMT_MCS6(x)				(((x) & 0xF) << 24)
#घोषणा _AGGLMT_MCS7(x)				(((x) & 0xF) << 28)

#घोषणा	RETRY_LIMIT_SHORT_SHIFT			8
#घोषणा	RETRY_LIMIT_LONG_SHIFT			0

#घोषणा _DARF_RC1(x)				((x) & 0x1F)
#घोषणा _DARF_RC2(x)				(((x) & 0x1F) << 8)
#घोषणा _DARF_RC3(x)				(((x) & 0x1F) << 16)
#घोषणा _DARF_RC4(x)				(((x) & 0x1F) << 24)
#घोषणा _DARF_RC5(x)				((x) & 0x1F)
#घोषणा _DARF_RC6(x)				(((x) & 0x1F) << 8)
#घोषणा _DARF_RC7(x)				(((x) & 0x1F) << 16)
#घोषणा _DARF_RC8(x)				(((x) & 0x1F) << 24)

#घोषणा _RARF_RC1(x)				((x) & 0x1F)
#घोषणा _RARF_RC2(x)				(((x) & 0x1F) << 8)
#घोषणा _RARF_RC3(x)				(((x) & 0x1F) << 16)
#घोषणा _RARF_RC4(x)				(((x) & 0x1F) << 24)
#घोषणा _RARF_RC5(x)				((x) & 0x1F)
#घोषणा _RARF_RC6(x)				(((x) & 0x1F) << 8)
#घोषणा _RARF_RC7(x)				(((x) & 0x1F) << 16)
#घोषणा _RARF_RC8(x)				(((x) & 0x1F) << 24)

#घोषणा AC_PARAM_TXOP_LIMIT_OFFSET		16
#घोषणा AC_PARAM_ECW_MAX_OFFSET			12
#घोषणा AC_PARAM_ECW_MIN_OFFSET			8
#घोषणा AC_PARAM_AIFS_OFFSET			0

#घोषणा _AIFS(x)				(x)
#घोषणा _ECW_MAX_MIN(x)				((x) << 8)
#घोषणा _TXOP_LIMIT(x)				((x) << 16)

#घोषणा _BCNIFS(x)				((x) & 0xFF)
#घोषणा _BCNECW(x)				((((x) & 0xF)) << 8)

#घोषणा _LRL(x)					((x) & 0x3F)
#घोषणा _SRL(x)					(((x) & 0x3F) << 8)

#घोषणा _SIFS_CCK_CTX(x)			((x) & 0xFF)
#घोषणा _SIFS_CCK_TRX(x)			(((x) & 0xFF) << 8)

#घोषणा _SIFS_OFDM_CTX(x)			((x) & 0xFF)
#घोषणा _SIFS_OFDM_TRX(x)			(((x) & 0xFF) << 8)

#घोषणा _TBTT_PROHIBIT_HOLD(x)			(((x) & 0xFF) << 8)

#घोषणा DIS_EDCA_CNT_DWN			BIT(11)

#घोषणा EN_MBSSID				BIT(1)
#घोषणा EN_TXBCN_RPT				BIT(2)
#घोषणा	EN_BCN_FUNCTION				BIT(3)

#घोषणा TSFTR_RST				BIT(0)
#घोषणा TSFTR1_RST				BIT(1)

#घोषणा STOP_BCNQ				BIT(6)

#घोषणा	DIS_TSF_UDT0_NORMAL_CHIP		BIT(4)
#घोषणा	DIS_TSF_UDT0_TEST_CHIP			BIT(5)

#घोषणा	ACMHW_HWEN				BIT(0)
#घोषणा	ACMHW_BEQEN				BIT(1)
#घोषणा	ACMHW_VIQEN				BIT(2)
#घोषणा	ACMHW_VOQEN				BIT(3)
#घोषणा	ACMHW_BEQSTATUS				BIT(4)
#घोषणा	ACMHW_VIQSTATUS				BIT(5)
#घोषणा	ACMHW_VOQSTATUS				BIT(6)

#घोषणा APSDOFF					BIT(6)
#घोषणा APSDOFF_STATUS				BIT(7)

#घोषणा BW_20MHZ				BIT(2)

#घोषणा RATE_BITMAP_ALL				0xFFFFF

#घोषणा RATE_RRSR_CCK_ONLY_1M			0xFFFF1

#घोषणा TSFRST					BIT(0)
#घोषणा DIS_GCLK				BIT(1)
#घोषणा PAD_SEL					BIT(2)
#घोषणा PWR_ST					BIT(6)
#घोषणा PWRBIT_OW_EN				BIT(7)
#घोषणा ACRC					BIT(8)
#घोषणा CFENDFORM				BIT(9)
#घोषणा ICV					BIT(10)

#घोषणा AAP					BIT(0)
#घोषणा APM					BIT(1)
#घोषणा AM					BIT(2)
#घोषणा AB					BIT(3)
#घोषणा ADD3					BIT(4)
#घोषणा APWRMGT					BIT(5)
#घोषणा CBSSID					BIT(6)
#घोषणा CBSSID_DATA				BIT(6)
#घोषणा CBSSID_BCN				BIT(7)
#घोषणा ACRC32					BIT(8)
#घोषणा AICV					BIT(9)
#घोषणा ADF					BIT(11)
#घोषणा ACF					BIT(12)
#घोषणा AMF					BIT(13)
#घोषणा HTC_LOC_CTRL				BIT(14)
#घोषणा UC_DATA_EN				BIT(16)
#घोषणा BM_DATA_EN				BIT(17)
#घोषणा MFBEN					BIT(22)
#घोषणा LSIGEN					BIT(23)
#घोषणा ENMBID					BIT(24)
#घोषणा APP_BASSN				BIT(27)
#घोषणा APP_PHYSTS				BIT(28)
#घोषणा APP_ICV					BIT(29)
#घोषणा APP_MIC					BIT(30)
#घोषणा APP_FCS					BIT(31)

#घोषणा _MIN_SPACE(x)				((x) & 0x7)
#घोषणा _SHORT_GI_PADDING(x)		(((x) & 0x1F) << 3)

#घोषणा RXERR_TYPE_OFDM_PPDU		0
#घोषणा RXERR_TYPE_OFDM_FALSE_ALARM	1
#घोषणा	RXERR_TYPE_OFDM_MPDU_OK		2
#घोषणा RXERR_TYPE_OFDM_MPDU_FAIL	3
#घोषणा RXERR_TYPE_CCK_PPDU		4
#घोषणा RXERR_TYPE_CCK_FALSE_ALARM	5
#घोषणा RXERR_TYPE_CCK_MPDU_OK		6
#घोषणा RXERR_TYPE_CCK_MPDU_FAIL	7
#घोषणा RXERR_TYPE_HT_PPDU		8
#घोषणा RXERR_TYPE_HT_FALSE_ALARM	9
#घोषणा RXERR_TYPE_HT_MPDU_TOTAL	10
#घोषणा RXERR_TYPE_HT_MPDU_OK		11
#घोषणा RXERR_TYPE_HT_MPDU_FAIL		12
#घोषणा RXERR_TYPE_RX_FULL_DROP		15

#घोषणा RXERR_COUNTER_MASK			0xFFFFF
#घोषणा RXERR_RPT_RST				BIT(27)
#घोषणा _RXERR_RPT_SEL(type)			((type) << 28)

#घोषणा	SCR_TXUSEDK				BIT(0)
#घोषणा	SCR_RXUSEDK				BIT(1)
#घोषणा	SCR_TXENCENABLE				BIT(2)
#घोषणा	SCR_RXDECENABLE				BIT(3)
#घोषणा	SCR_SKBYA2				BIT(4)
#घोषणा	SCR_NOSKMC				BIT(5)
#घोषणा SCR_TXBCUSEDK				BIT(6)
#घोषणा SCR_RXBCUSEDK				BIT(7)

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
#घोषणा BT_FUNC					BIT(16)
#घोषणा VENDOR_ID				BIT(19)
#घोषणा PAD_HWPD_IDN				BIT(22)
#घोषणा TRP_VAUX_EN				BIT(23)
#घोषणा TRP_BT_EN				BIT(24)
#घोषणा BD_PKG_SEL				BIT(25)
#घोषणा BD_HCI_SEL				BIT(26)
#घोषणा TYPE_ID					BIT(27)

#घोषणा USB_IS_HIGH_SPEED			0
#घोषणा USB_IS_FULL_SPEED			1
#घोषणा USB_SPEED_MASK				BIT(5)

#घोषणा USB_NORMAL_SIE_EP_MASK			0xF
#घोषणा USB_NORMAL_SIE_EP_SHIFT			4

#घोषणा USB_TEST_EP_MASK			0x30
#घोषणा USB_TEST_EP_SHIFT			4

#घोषणा USB_AGG_EN				BIT(3)

#घोषणा MAC_ADDR_LEN				6
#घोषणा LAST_ENTRY_OF_TX_PKT_BUFFER		175/*255    88e*/

#घोषणा POLLING_LLT_THRESHOLD			20
#घोषणा POLLING_READY_TIMEOUT_COUNT		3000

#घोषणा	MAX_MSS_DENSITY_2T			0x13
#घोषणा	MAX_MSS_DENSITY_1T			0x0A

#घोषणा EPROM_CMD_OPERATING_MODE_MASK	((1<<7)|(1<<6))
#घोषणा EPROM_CMD_CONFIG			0x3
#घोषणा EPROM_CMD_LOAD				1

#घोषणा	HWSET_MAX_SIZE_92S			HWSET_MAX_SIZE

#घोषणा	HAL_8192C_HW_GPIO_WPS_BIT		BIT(2)

#घोषणा	RPMAC_RESET				0x100
#घोषणा	RPMAC_TXSTART				0x104
#घोषणा	RPMAC_TXLEGACYSIG			0x108
#घोषणा	RPMAC_TXHTSIG1				0x10c
#घोषणा	RPMAC_TXHTSIG2				0x110
#घोषणा	RPMAC_PHYDEBUG				0x114
#घोषणा	RPMAC_TXPACKETNUM			0x118
#घोषणा	RPMAC_TXIDLE				0x11c
#घोषणा	RPMAC_TXMACHEADER0			0x120
#घोषणा	RPMAC_TXMACHEADER1			0x124
#घोषणा	RPMAC_TXMACHEADER2			0x128
#घोषणा	RPMAC_TXMACHEADER3			0x12c
#घोषणा	RPMAC_TXMACHEADER4			0x130
#घोषणा	RPMAC_TXMACHEADER5			0x134
#घोषणा	RPMAC_TXDADATYPE			0x138
#घोषणा	RPMAC_TXRANDOMSEED			0x13c
#घोषणा	RPMAC_CCKPLCPPREAMBLE			0x140
#घोषणा	RPMAC_CCKPLCPHEADER			0x144
#घोषणा	RPMAC_CCKCRC16				0x148
#घोषणा	RPMAC_OFDMRXCRC32OK			0x170
#घोषणा	RPMAC_OFDMRXCRC32ER			0x174
#घोषणा	RPMAC_OFDMRXPARITYER			0x178
#घोषणा	RPMAC_OFDMRXCRC8ER			0x17c
#घोषणा	RPMAC_CCKCRXRC16ER			0x180
#घोषणा	RPMAC_CCKCRXRC32ER			0x184
#घोषणा	RPMAC_CCKCRXRC32OK			0x188
#घोषणा	RPMAC_TXSTATUS				0x18c

#घोषणा	RFPGA0_RFMOD				0x800

#घोषणा	RFPGA0_TXINFO				0x804
#घोषणा	RFPGA0_PSDFUNCTION			0x808

#घोषणा	RFPGA0_TXGAINSTAGE			0x80c

#घोषणा	RFPGA0_RFTIMING1			0x810
#घोषणा	RFPGA0_RFTIMING2			0x814

#घोषणा	RFPGA0_XA_HSSIPARAMETER1	0x820
#घोषणा	RFPGA0_XA_HSSIPARAMETER2	0x824
#घोषणा	RFPGA0_XB_HSSIPARAMETER1	0x828
#घोषणा	RFPGA0_XB_HSSIPARAMETER2	0x82c

#घोषणा	RFPGA0_XA_LSSIPARAMETER		0x840
#घोषणा	RFPGA0_XB_LSSIPARAMETER		0x844

#घोषणा	RFPGA0_RFWAKEUPPARAMETER	0x850
#घोषणा	RFPGA0_RFSLEEPUPPARAMETER	0x854

#घोषणा	RFPGA0_XAB_SWITCHCONTROL	0x858
#घोषणा	RFPGA0_XCD_SWITCHCONTROL	0x85c

#घोषणा	RFPGA0_XA_RFINTERFACEOE		0x860
#घोषणा	RFPGA0_XB_RFINTERFACEOE		0x864

#घोषणा	RFPGA0_XAB_RFINTERFACESW	0x870
#घोषणा	RFPGA0_XCD_RFINTERFACESW	0x874

#घोषणा	RFPGA0_XAB_RFPARAMETER		0x878
#घोषणा	RFPGA0_XCD_RFPARAMETER		0x87c

#घोषणा	RFPGA0_ANALOGPARAMETER1		0x880
#घोषणा	RFPGA0_ANALOGPARAMETER2		0x884
#घोषणा	RFPGA0_ANALOGPARAMETER3		0x888
#घोषणा	RFPGA0_ANALOGPARAMETER4		0x88c

#घोषणा	RFPGA0_XA_LSSIREADBACK		0x8a0
#घोषणा	RFPGA0_XB_LSSIREADBACK		0x8a4
#घोषणा	RFPGA0_XC_LSSIREADBACK		0x8a8
#घोषणा	RFPGA0_XD_LSSIREADBACK		0x8ac

#घोषणा	RFPGA0_PSDREPORT		0x8b4
#घोषणा	TRANSCEIVEA_HSPI_READBACK	0x8b8
#घोषणा	TRANSCEIVEB_HSPI_READBACK	0x8bc
#घोषणा	REG_SC_CNT			0x8c4
#घोषणा	RFPGA0_XAB_RFINTERFACERB	0x8e0
#घोषणा	RFPGA0_XCD_RFINTERFACERB	0x8e4

#घोषणा	RFPGA1_RFMOD			0x900

#घोषणा	RFPGA1_TXBLOCK			0x904
#घोषणा	RFPGA1_DEBUGSELECT		0x908
#घोषणा	RFPGA1_TXINFO			0x90c

#घोषणा	RCCK0_SYSTEM			0xa00

#घोषणा	RCCK0_AFESETTING		0xa04
#घोषणा	RCCK0_CCA			0xa08

#घोषणा	RCCK0_RXAGC1			0xa0c
#घोषणा	RCCK0_RXAGC2			0xa10

#घोषणा	RCCK0_RXHP			0xa14

#घोषणा	RCCK0_DSPPARAMETER1		0xa18
#घोषणा	RCCK0_DSPPARAMETER2		0xa1c

#घोषणा	RCCK0_TXFILTER1			0xa20
#घोषणा	RCCK0_TXFILTER2			0xa24
#घोषणा	RCCK0_DEBUGPORT			0xa28
#घोषणा	RCCK0_FALSEALARMREPORT		0xa2c
#घोषणा	RCCK0_TRSSIREPORT		0xa50
#घोषणा	RCCK0_RXREPORT			0xa54
#घोषणा	RCCK0_FACOUNTERLOWER		0xa5c
#घोषणा	RCCK0_FACOUNTERUPPER		0xa58
#घोषणा	RCCK0_CCA_CNT			0xa60

/* PageB(0xB00) */
#घोषणा	RPDP_ANTA			0xb00
#घोषणा	RPDP_ANTA_4			0xb04
#घोषणा	RPDP_ANTA_8			0xb08
#घोषणा	RPDP_ANTA_C			0xb0c
#घोषणा	RPDP_ANTA_10			0xb10
#घोषणा	RPDP_ANTA_14			0xb14
#घोषणा	RPDP_ANTA_18			0xb18
#घोषणा	RPDP_ANTA_1C			0xb1c
#घोषणा	RPDP_ANTA_20			0xb20
#घोषणा	RPDP_ANTA_24			0xb24

#घोषणा	RCONFIG_PMPD_ANTA		0xb28
#घोषणा	RCONFIG_ram64x16		0xb2c

#घोषणा	RBNDA				0xb30
#घोषणा	RHSSIPAR			0xb34

#घोषणा	RCONFIG_ANTA			0xb68
#घोषणा	RCONFIG_ANTB			0xb6c

#घोषणा	RPDP_ANTB			0xb70
#घोषणा	RPDP_ANTB_4			0xb74
#घोषणा	RPDP_ANTB_8			0xb78
#घोषणा	RPDP_ANTB_C			0xb7c
#घोषणा	RPDP_ANTB_10			0xb80
#घोषणा	RPDP_ANTB_14			0xb84
#घोषणा	RPDP_ANTB_18			0xb88
#घोषणा	RPDP_ANTB_1C			0xb8c
#घोषणा	RPDP_ANTB_20			0xb90
#घोषणा	RPDP_ANTB_24			0xb94

#घोषणा	RCONFIG_PMPD_ANTB		0xb98

#घोषणा	RBNDB				0xba0

#घोषणा	RAPK				0xbd8
#घोषणा	RPM_RX0_ANTA			0xbdc
#घोषणा	RPM_RX1_ANTA			0xbe0
#घोषणा	RPM_RX2_ANTA			0xbe4
#घोषणा	RPM_RX3_ANTA			0xbe8
#घोषणा	RPM_RX0_ANTB			0xbec
#घोषणा	RPM_RX1_ANTB			0xbf0
#घोषणा	RPM_RX2_ANTB			0xbf4
#घोषणा	RPM_RX3_ANTB			0xbf8

/*Page C*/
#घोषणा	ROFDM0_LSTF			0xc00

#घोषणा	ROFDM0_TRXPATHENABLE		0xc04
#घोषणा	ROFDM0_TRMUXPAR			0xc08
#घोषणा	ROFDM0_TRSWISOLATION		0xc0c

#घोषणा	ROFDM0_XARXAFE			0xc10
#घोषणा	ROFDM0_XARXIQIMBALANCE		0xc14
#घोषणा	ROFDM0_XBRXAFE			0xc18
#घोषणा	ROFDM0_XBRXIQIMBALANCE		0xc1c
#घोषणा	ROFDM0_XCRXAFE			0xc20
#घोषणा	ROFDM0_XCRXIQIMBANLANCE		0xc24
#घोषणा	ROFDM0_XDRXAFE			0xc28
#घोषणा	ROFDM0_XDRXIQIMBALANCE		0xc2c

#घोषणा	ROFDM0_RXDETECTOR1		0xc30
#घोषणा	ROFDM0_RXDETECTOR2		0xc34
#घोषणा	ROFDM0_RXDETECTOR3		0xc38
#घोषणा	ROFDM0_RXDETECTOR4		0xc3c

#घोषणा	ROFDM0_RXDSP			0xc40
#घोषणा	ROFDM0_CFOANDDAGC		0xc44
#घोषणा	ROFDM0_CCADROPTHRESHOLD		0xc48
#घोषणा	ROFDM0_ECCATHRESHOLD		0xc4c

#घोषणा	ROFDM0_XAAGCCORE1		0xc50
#घोषणा	ROFDM0_XAAGCCORE2		0xc54
#घोषणा	ROFDM0_XBAGCCORE1		0xc58
#घोषणा	ROFDM0_XBAGCCORE2		0xc5c
#घोषणा	ROFDM0_XCAGCCORE1		0xc60
#घोषणा	ROFDM0_XCAGCCORE2		0xc64
#घोषणा	ROFDM0_XDAGCCORE1		0xc68
#घोषणा	ROFDM0_XDAGCCORE2		0xc6c

#घोषणा	ROFDM0_AGCPARAMETER1		0xc70
#घोषणा	ROFDM0_AGCPARAMETER2		0xc74
#घोषणा	ROFDM0_AGCRSSITABLE		0xc78
#घोषणा	ROFDM0_HTSTFAGC			0xc7c

#घोषणा	ROFDM0_XATXIQIMBALANCE		0xc80
#घोषणा	ROFDM0_XATXAFE			0xc84
#घोषणा	ROFDM0_XBTXIQIMBALANCE		0xc88
#घोषणा	ROFDM0_XBTXAFE			0xc8c
#घोषणा	ROFDM0_XCTXIQIMBALANCE		0xc90
#घोषणा	ROFDM0_XCTXAFE			0xc94
#घोषणा	ROFDM0_XDTXIQIMBALANCE		0xc98
#घोषणा	ROFDM0_XDTXAFE			0xc9c

#घोषणा ROFDM0_RXIQEXTANTA		0xca0
#घोषणा	ROFDM0_TXCOEFF1			0xca4
#घोषणा	ROFDM0_TXCOEFF2			0xca8
#घोषणा	ROFDM0_TXCOEFF3			0xcac
#घोषणा	ROFDM0_TXCOEFF4			0xcb0
#घोषणा	ROFDM0_TXCOEFF5			0xcb4
#घोषणा	ROFDM0_TXCOEFF6			0xcb8

#घोषणा	ROFDM0_RXHPPARAMETER		0xce0
#घोषणा	ROFDM0_TXPSEUDONOISEWGT		0xce4
#घोषणा	ROFDM0_FRAMESYNC		0xcf0
#घोषणा	ROFDM0_DFSREPORT		0xcf4

#घोषणा	ROFDM1_LSTF			0xd00
#घोषणा	ROFDM1_TRXPATHENABLE		0xd04

#घोषणा	ROFDM1_CF0			0xd08
#घोषणा	ROFDM1_CSI1			0xd10
#घोषणा	ROFDM1_SBD			0xd14
#घोषणा	ROFDM1_CSI2			0xd18
#घोषणा	ROFDM1_CFOTRACKING		0xd2c
#घोषणा	ROFDM1_TRXMESAURE1		0xd34
#घोषणा	ROFDM1_INTFDET			0xd3c
#घोषणा	ROFDM1_PSEUDONOISESTATEAB	0xd50
#घोषणा	ROFDM1_PSEUDONOISESTATECD	0xd54
#घोषणा	ROFDM1_RXPSEUDONOISEWGT		0xd58

#घोषणा	ROFDM_PHYCOUNTER1		0xda0
#घोषणा	ROFDM_PHYCOUNTER2		0xda4
#घोषणा	ROFDM_PHYCOUNTER3		0xda8

#घोषणा	ROFDM_SHORTCFOAB		0xdac
#घोषणा	ROFDM_SHORTCFOCD		0xdb0
#घोषणा	ROFDM_LONGCFOAB			0xdb4
#घोषणा	ROFDM_LONGCFOCD			0xdb8
#घोषणा	ROFDM_TAILCF0AB			0xdbc
#घोषणा	ROFDM_TAILCF0CD			0xdc0
#घोषणा	ROFDM_PWMEASURE1		0xdc4
#घोषणा	ROFDM_PWMEASURE2		0xdc8
#घोषणा	ROFDM_BWREPORT			0xdcc
#घोषणा	ROFDM_AGCREPORT			0xdd0
#घोषणा	ROFDM_RXSNR			0xdd4
#घोषणा	ROFDM_RXEVMCSI			0xdd8
#घोषणा	ROFDM_SIGREPORT			0xddc

#घोषणा	RTXAGC_A_RATE18_06		0xe00
#घोषणा	RTXAGC_A_RATE54_24		0xe04
#घोषणा	RTXAGC_A_CCK1_MCS32		0xe08
#घोषणा	RTXAGC_A_MCS03_MCS00		0xe10
#घोषणा	RTXAGC_A_MCS07_MCS04		0xe14
#घोषणा	RTXAGC_A_MCS11_MCS08		0xe18
#घोषणा	RTXAGC_A_MCS15_MCS12		0xe1c

#घोषणा	RTXAGC_B_RATE18_06		0x830
#घोषणा	RTXAGC_B_RATE54_24		0x834
#घोषणा	RTXAGC_B_CCK1_55_MCS32		0x838
#घोषणा	RTXAGC_B_MCS03_MCS00		0x83c
#घोषणा	RTXAGC_B_MCS07_MCS04		0x848
#घोषणा	RTXAGC_B_MCS11_MCS08		0x84c
#घोषणा	RTXAGC_B_MCS15_MCS12		0x868
#घोषणा	RTXAGC_B_CCK11_A_CCK2_11	0x86c

#घोषणा	RFPGA0_IQK			0xe28
#घोषणा	RTX_IQK_TONE_A			0xe30
#घोषणा	RRX_IQK_TONE_A			0xe34
#घोषणा	RTX_IQK_PI_A			0xe38
#घोषणा	RRX_IQK_PI_A			0xe3c

#घोषणा	RTX_IQK				0xe40
#घोषणा	RRX_IQK				0xe44
#घोषणा	RIQK_AGC_PTS			0xe48
#घोषणा	RIQK_AGC_RSP			0xe4c
#घोषणा	RTX_IQK_TONE_B			0xe50
#घोषणा	RRX_IQK_TONE_B			0xe54
#घोषणा	RTX_IQK_PI_B			0xe58
#घोषणा	RRX_IQK_PI_B			0xe5c
#घोषणा	RIQK_AGC_CONT			0xe60

#घोषणा	RBLUE_TOOTH			0xe6c
#घोषणा	RRX_WAIT_CCA			0xe70
#घोषणा	RTX_CCK_RFON			0xe74
#घोषणा	RTX_CCK_BBON			0xe78
#घोषणा	RTX_OFDM_RFON			0xe7c
#घोषणा	RTX_OFDM_BBON			0xe80
#घोषणा	RTX_TO_RX			0xe84
#घोषणा	RTX_TO_TX			0xe88
#घोषणा	RRX_CCK				0xe8c

#घोषणा	RTX_POWER_BEFORE_IQK_A		0xe94
#घोषणा	RTX_POWER_AFTER_IQK_A		0xe9c

#घोषणा	RRX_POWER_BEFORE_IQK_A		0xea0
#घोषणा	RRX_POWER_BEFORE_IQK_A_2	0xea4
#घोषणा	RRX_POWER_AFTER_IQK_A		0xea8
#घोषणा	RRX_POWER_AFTER_IQK_A_2		0xeac

#घोषणा	RTX_POWER_BEFORE_IQK_B		0xeb4
#घोषणा	RTX_POWER_AFTER_IQK_B		0xebc

#घोषणा	RRX_POWER_BEFORE_IQK_B		0xec0
#घोषणा	RRX_POWER_BEFORE_IQK_B_2	0xec4
#घोषणा	RRX_POWER_AFTER_IQK_B		0xec8
#घोषणा	RRX_POWER_AFTER_IQK_B_2		0xecc

#घोषणा	RRX_OFDM			0xed0
#घोषणा	RRX_WAIT_RIFS			0xed4
#घोषणा	RRX_TO_RX			0xed8
#घोषणा	RSTANDBY			0xedc
#घोषणा	RSLEEP				0xee0
#घोषणा	RPMPD_ANAEN			0xeec

#घोषणा	RZEBRA1_HSSIENABLE			0x0
#घोषणा	RZEBRA1_TRXENABLE1			0x1
#घोषणा	RZEBRA1_TRXENABLE2			0x2
#घोषणा	RZEBRA1_AGC				0x4
#घोषणा	RZEBRA1_CHARGEPUMP			0x5
#घोषणा	RZEBRA1_CHANNEL				0x7

#घोषणा	RZEBRA1_TXGAIN				0x8
#घोषणा	RZEBRA1_TXLPF				0x9
#घोषणा	RZEBRA1_RXLPF				0xb
#घोषणा	RZEBRA1_RXHPFCORNER			0xc

#घोषणा	RGLOBALCTRL				0
#घोषणा	RRTL8256_TXLPF				19
#घोषणा	RRTL8256_RXLPF				11
#घोषणा	RRTL8258_TXLPF				0x11
#घोषणा	RRTL8258_RXLPF				0x13
#घोषणा	RRTL8258_RSSILPF			0xa

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
#घोषणा	RRFCHANNEL				0x18
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

#घोषणा	RF_TX_BIAS_A				0x35
#घोषणा	RF_TX_BIAS_D				0x36
#घोषणा	RF_LOBF_9				0x38
#घोषणा	RF_RXRF_A3				0x3C
#घोषणा	RF_TRSW					0x3F

#घोषणा	RF_TXRF_A2				0x41
#घोषणा	RF_TXPA_G4				0x46
#घोषणा	RF_TXPA_A4				0x4B

#घोषणा	RF_WE_LUT				0xEF

#घोषणा	BBBRESETB				0x100
#घोषणा	BGLOBALRESETB				0x200
#घोषणा	BOFDMTXSTART				0x4
#घोषणा	BCCKTXSTART				0x8
#घोषणा	BCRC32DEBUG				0x100
#घोषणा	BPMACLOOPBACK				0x10
#घोषणा	BTXLSIG					0xffffff
#घोषणा	BOFDMTXRATE				0xf
#घोषणा	BOFDMTXRESERVED				0x10
#घोषणा	BOFDMTXLENGTH				0x1ffe0
#घोषणा	BOFDMTXPARITY				0x20000
#घोषणा	BTXHTSIG1				0xffffff
#घोषणा	BTXHTMCSRATE				0x7f
#घोषणा	BTXHTBW					0x80
#घोषणा	BTXHTLENGTH				0xffff00
#घोषणा	BTXHTSIG2				0xffffff
#घोषणा	BTXHTSMOOTHING				0x1
#घोषणा	BTXHTSOUNDING				0x2
#घोषणा	BTXHTRESERVED				0x4
#घोषणा	BTXHTAGGREATION				0x8
#घोषणा	BTXHTSTBC				0x30
#घोषणा	BTXHTADVANCECODING			0x40
#घोषणा	BTXHTSHORTGI				0x80
#घोषणा	BTXHTNUMBERHT_LTF			0x300
#घोषणा	BTXHTCRC8				0x3fc00
#घोषणा	BCOUNTERRESET				0x10000
#घोषणा	BNUMOFOFDMTX				0xffff
#घोषणा	BNUMOFCCKTX				0xffff0000
#घोषणा	BTXIDLEINTERVAL				0xffff
#घोषणा	BOFDMSERVICE				0xffff0000
#घोषणा	BTXMACHEADER				0xffffffff
#घोषणा	BTXDATAINIT				0xff
#घोषणा	BTXHTMODE				0x100
#घोषणा	BTXDATATYPE				0x30000
#घोषणा	BTXRANDOMSEED				0xffffffff
#घोषणा	BCCKTXPREAMBLE				0x1
#घोषणा	BCCKTXSFD				0xffff0000
#घोषणा	BCCKTXSIG				0xff
#घोषणा	BCCKTXSERVICE				0xff00
#घोषणा	BCCKLENGTHEXT				0x8000
#घोषणा	BCCKTXLENGHT				0xffff0000
#घोषणा	BCCKTXCRC16				0xffff
#घोषणा	BCCKTXSTATUS				0x1
#घोषणा	BOFDMTXSTATUS				0x2
#घोषणा IS_BB_REG_OFFSET_92S(_offset)	\
	((_offset >= 0x800) && (_offset <= 0xfff))

#घोषणा	BRFMOD					0x1
#घोषणा	BJAPANMODE				0x2
#घोषणा	BCCKTXSC				0x30
#घोषणा	BCCKEN					0x1000000
#घोषणा	BOFDMEN					0x2000000

#घोषणा	BOFDMRXADCPHASE			0x10000
#घोषणा	BOFDMTXDACPHASE			0x40000
#घोषणा	BXATXAGC			0x3f

#घोषणा	BXBTXAGC			0xf00
#घोषणा	BXCTXAGC			0xf000
#घोषणा	BXDTXAGC			0xf0000

#घोषणा	BPASTART			0xf0000000
#घोषणा	BTRSTART			0x00f00000
#घोषणा	BRFSTART			0x0000f000
#घोषणा	BBBSTART			0x000000f0
#घोषणा	BBBCCKSTART			0x0000000f
#घोषणा	BPAEND				0xf
#घोषणा	BTREND				0x0f000000
#घोषणा	BRFEND				0x000f0000
#घोषणा	BCCAMASK			0x000000f0
#घोषणा	BR2RCCAMASK			0x00000f00
#घोषणा	BHSSI_R2TDELAY			0xf8000000
#घोषणा	BHSSI_T2RDELAY			0xf80000
#घोषणा	BCONTXHSSI			0x400
#घोषणा	BIGFROMCCK			0x200
#घोषणा	BAGCADDRESS			0x3f
#घोषणा	BRXHPTX				0x7000
#घोषणा	BRXHP2RX			0x38000
#घोषणा	BRXHPCCKINI			0xc0000
#घोषणा	BAGCTXCODE			0xc00000
#घोषणा	BAGCRXCODE			0x300000

#घोषणा	B3WIREDATALENGTH		0x800
#घोषणा	B3WIREADDREAALENGTH		0x400

#घोषणा	B3WIRERFPOWERDOWN		0x1
#घोषणा	B5GPAPEPOLARITY			0x40000000
#घोषणा	B2GPAPEPOLARITY			0x80000000
#घोषणा	BRFSW_TXDEFAULTANT		0x3
#घोषणा	BRFSW_TXOPTIOन_अंकT		0x30
#घोषणा	BRFSW_RXDEFAULTANT		0x300
#घोषणा	BRFSW_RXOPTIOन_अंकT		0x3000
#घोषणा	BRFSI_3WIREDATA			0x1
#घोषणा	BRFSI_3WIRECLOCK		0x2
#घोषणा	BRFSI_3WIRELOAD			0x4
#घोषणा	BRFSI_3WIRERW			0x8
#घोषणा	BRFSI_3WIRE			0xf

#घोषणा	BRFSI_RFENV			0x10

#घोषणा	BRFSI_TRSW			0x20
#घोषणा	BRFSI_TRSWB			0x40
#घोषणा	BRFSI_ANTSW			0x100
#घोषणा	BRFSI_ANTSWB			0x200
#घोषणा	BRFSI_PAPE			0x400
#घोषणा	BRFSI_PAPE5G			0x800
#घोषणा	BBANDSELECT			0x1
#घोषणा	BHTSIG2_GI			0x80
#घोषणा	BHTSIG2_SMOOTHING		0x01
#घोषणा	BHTSIG2_SOUNDING		0x02
#घोषणा	BHTSIG2_AGGREATON		0x08
#घोषणा	BHTSIG2_STBC			0x30
#घोषणा	BHTSIG2_ADVCODING		0x40
#घोषणा	BHTSIG2_NUMOFHTLTF		0x300
#घोषणा	BHTSIG2_CRC8			0x3fc
#घोषणा	BHTSIG1_MCS			0x7f
#घोषणा	BHTSIG1_BANDWIDTH		0x80
#घोषणा	BHTSIG1_HTLENGTH		0xffff
#घोषणा	BLSIG_RATE			0xf
#घोषणा	BLSIG_RESERVED			0x10
#घोषणा	BLSIG_LENGTH			0x1fffe
#घोषणा	BLSIG_PARITY			0x20
#घोषणा	BCCKRXPHASE			0x4

#घोषणा	BLSSIREADADDRESS		0x7f800000
#घोषणा	BLSSIREADEDGE			0x80000000

#घोषणा	BLSSIREADBACKDATA		0xfffff

#घोषणा	BLSSIREADOKFLAG			0x1000
#घोषणा	BCCKSAMPLERATE			0x8
#घोषणा	BREGULATOR0STANDBY		0x1
#घोषणा	BREGULATORPLLSTANDBY		0x2
#घोषणा	BREGULATOR1STANDBY		0x4
#घोषणा	BPLLPOWERUP			0x8
#घोषणा	BDPLLPOWERUP			0x10
#घोषणा	BDA10POWERUP			0x20
#घोषणा	BAD7POWERUP			0x200
#घोषणा	BDA6POWERUP			0x2000
#घोषणा	BXTALPOWERUP			0x4000
#घोषणा	B40MDCLKPOWERUP			0x8000
#घोषणा	BDA6DEBUGMODE			0x20000
#घोषणा	BDA6SWING			0x380000

#घोषणा	BADCLKPHASE			0x4000000
#घोषणा	B80MCLKDELAY			0x18000000
#घोषणा	BAFEWATCHDOGENABLE		0x20000000

#घोषणा	BXTALCAP01			0xc0000000
#घोषणा	BXTALCAP23			0x3
#घोषणा	BXTALCAP92X			0x0f000000
#घोषणा BXTALCAP			0x0f000000

#घोषणा	BINTDIFCLKENABLE		0x400
#घोषणा	BEXTSIGCLKENABLE		0x800
#घोषणा	BBANDGAP_MBIAS_POWERUP		0x10000
#घोषणा	BAD11SH_GAIN			0xc0000
#घोषणा	BAD11NPUT_RANGE			0x700000
#घोषणा	BAD110P_CURRENT			0x3800000
#घोषणा	BLPATH_LOOPBACK			0x4000000
#घोषणा	BQPATH_LOOPBACK			0x8000000
#घोषणा	BAFE_LOOPBACK			0x10000000
#घोषणा	BDA10_SWING			0x7e0
#घोषणा	BDA10_REVERSE			0x800
#घोषणा	BDA_CLK_SOURCE			0x1000
#घोषणा	BDA7INPUT_RANGE			0x6000
#घोषणा	BDA7_GAIN			0x38000
#घोषणा	BDA7OUTPUT_CM_MODE		0x40000
#घोषणा	BDA7INPUT_CM_MODE		0x380000
#घोषणा	BDA7CURRENT			0xc00000
#घोषणा	BREGULATOR_ADJUST		0x7000000
#घोषणा	BAD11POWERUP_ATTX		0x1
#घोषणा	BDA10PS_ATTX			0x10
#घोषणा	BAD11POWERUP_ATRX		0x100
#घोषणा	BDA10PS_ATRX			0x1000
#घोषणा	BCCKRX_AGC_FORMAT		0x200
#घोषणा	BPSDFFT_SAMPLE_POINT		0xc000
#घोषणा	BPSD_AVERAGE_NUM		0x3000
#घोषणा	BIQPATH_CONTROL			0xc00
#घोषणा	BPSD_FREQ			0x3ff
#घोषणा	BPSD_ANTENNA_PATH		0x30
#घोषणा	BPSD_IQ_SWITCH			0x40
#घोषणा	BPSD_RX_TRIGGER			0x400000
#घोषणा	BPSD_TX_TRIGGER			0x80000000
#घोषणा	BPSD_SINE_TONE_SCALE		0x7f000000
#घोषणा	BPSD_REPORT			0xffff

#घोषणा	BOFDM_TXSC			0x30000000
#घोषणा	BCCK_TXON			0x1
#घोषणा	BOFDM_TXON			0x2
#घोषणा	BDEBUG_PAGE			0xfff
#घोषणा	BDEBUG_ITEM			0xff
#घोषणा	BANTL				0x10
#घोषणा	BANT_NONHT			0x100
#घोषणा	BANT_HT1			0x1000
#घोषणा	BANT_HT2			0x10000
#घोषणा	BANT_HT1S1			0x100000
#घोषणा	BANT_NONHTS1			0x1000000

#घोषणा	BCCK_BBMODE			0x3
#घोषणा	BCCK_TXPOWERSAVING		0x80
#घोषणा	BCCK_RXPOWERSAVING		0x40

#घोषणा	BCCK_SIDEBAND			0x10

#घोषणा	BCCK_SCRAMBLE			0x8
#घोषणा	BCCK_ANTDIVERSITY		0x8000
#घोषणा	BCCK_CARRIER_RECOVERY		0x4000
#घोषणा	BCCK_TXRATE			0x3000
#घोषणा	BCCK_DCCANCEL			0x0800
#घोषणा	BCCK_ISICANCEL			0x0400
#घोषणा	BCCK_MATCH_FILTER		0x0200
#घोषणा	BCCK_EQUALIZER			0x0100
#घोषणा	BCCK_PREAMBLE_DETECT		0x800000
#घोषणा	BCCK_FAST_FALSECCA		0x400000
#घोषणा	BCCK_CH_ESTSTART		0x300000
#घोषणा	BCCK_CCA_COUNT			0x080000
#घोषणा	BCCK_CS_LIM			0x070000
#घोषणा	BCCK_BIST_MODE			0x80000000
#घोषणा	BCCK_CCAMASK			0x40000000
#घोषणा	BCCK_TX_DAC_PHASE		0x4
#घोषणा	BCCK_RX_ADC_PHASE		0x20000000
#घोषणा	BCCKR_CP_MODE			0x0100
#घोषणा	BCCK_TXDC_OFFSET		0xf0
#घोषणा	BCCK_RXDC_OFFSET		0xf
#घोषणा	BCCK_CCA_MODE			0xc000
#घोषणा	BCCK_FALSECS_LIM		0x3f00
#घोषणा	BCCK_CS_RATIO			0xc00000
#घोषणा	BCCK_CORGBIT_SEL		0x300000
#घोषणा	BCCK_PD_LIM			0x0f0000
#घोषणा	BCCK_NEWCCA			0x80000000
#घोषणा	BCCK_RXHP_OF_IG			0x8000
#घोषणा	BCCK_RXIG			0x7f00
#घोषणा	BCCK_LNA_POLARITY		0x800000
#घोषणा	BCCK_RX1ST_BAIN			0x7f0000
#घोषणा	BCCK_RF_EXTEND			0x20000000
#घोषणा	BCCK_RXAGC_SATLEVEL		0x1f000000
#घोषणा	BCCK_RXAGC_SATCOUNT		0xe0
#घोषणा	BCCKRXRFSETTLE			0x1f
#घोषणा	BCCK_FIXED_RXAGC		0x8000
#घोषणा	BCCK_ANTENNA_POLARITY		0x2000
#घोषणा	BCCK_TXFILTER_TYPE		0x0c00
#घोषणा	BCCK_RXAGC_REPORTTYPE		0x0300
#घोषणा	BCCK_RXDAGC_EN			0x80000000
#घोषणा	BCCK_RXDAGC_PERIOD		0x20000000
#घोषणा	BCCK_RXDAGC_SATLEVEL		0x1f000000
#घोषणा	BCCK_TIMING_RECOVERY		0x800000
#घोषणा	BCCK_TXC0			0x3f0000
#घोषणा	BCCK_TXC1			0x3f000000
#घोषणा	BCCK_TXC2			0x3f
#घोषणा	BCCK_TXC3			0x3f00
#घोषणा	BCCK_TXC4			0x3f0000
#घोषणा	BCCK_TXC5			0x3f000000
#घोषणा	BCCK_TXC6			0x3f
#घोषणा	BCCK_TXC7			0x3f00
#घोषणा	BCCK_DEBUGPORT			0xff0000
#घोषणा	BCCK_DAC_DEBUG			0x0f000000
#घोषणा	BCCK_FALSEALARM_ENABLE		0x8000
#घोषणा	BCCK_FALSEALARM_READ		0x4000
#घोषणा	BCCK_TRSSI			0x7f
#घोषणा	BCCK_RXAGC_REPORT		0xfe
#घोषणा	BCCK_RXREPORT_ANTSEL		0x80000000
#घोषणा	BCCK_RXREPORT_MFOFF		0x40000000
#घोषणा	BCCK_RXREPORT_SQLOSS		0x20000000
#घोषणा	BCCK_RXREPORT_PKTLOSS		0x10000000
#घोषणा	BCCK_RXREPORT_LOCKEDBIT		0x08000000
#घोषणा	BCCK_RXREPORT_RATEERROR		0x04000000
#घोषणा	BCCK_RXREPORT_RXRATE		0x03000000
#घोषणा	BCCK_RXFA_COUNTER_LOWER		0xff
#घोषणा	BCCK_RXFA_COUNTER_UPPER		0xff000000
#घोषणा	BCCK_RXHPAGC_START		0xe000
#घोषणा	BCCK_RXHPAGC_FINAL		0x1c00
#घोषणा	BCCK_RXFALSEALARM_ENABLE	0x8000
#घोषणा	BCCK_FACOUNTER_FREEZE		0x4000
#घोषणा	BCCK_TXPATH_SEL			0x10000000
#घोषणा	BCCK_DEFAULT_RXPATH		0xc000000
#घोषणा	BCCK_OPTION_RXPATH		0x3000000

#घोषणा	BNUM_OFSTF			0x3
#घोषणा	BSHIFT_L			0xc0
#घोषणा	BGI_TH				0xc
#घोषणा	BRXPATH_A			0x1
#घोषणा	BRXPATH_B			0x2
#घोषणा	BRXPATH_C			0x4
#घोषणा	BRXPATH_D			0x8
#घोषणा	BTXPATH_A			0x1
#घोषणा	BTXPATH_B			0x2
#घोषणा	BTXPATH_C			0x4
#घोषणा	BTXPATH_D			0x8
#घोषणा	BTRSSI_FREQ			0x200
#घोषणा	BADC_BACKOFF			0x3000
#घोषणा	BDFIR_BACKOFF			0xc000
#घोषणा	BTRSSI_LATCH_PHASE		0x10000
#घोषणा	BRX_LDC_OFFSET			0xff
#घोषणा	BRX_QDC_OFFSET			0xff00
#घोषणा	BRX_DFIR_MODE			0x1800000
#घोषणा	BRX_DCNF_TYPE			0xe000000
#घोषणा	BRXIQIMB_A			0x3ff
#घोषणा	BRXIQIMB_B			0xfc00
#घोषणा	BRXIQIMB_C			0x3f0000
#घोषणा	BRXIQIMB_D			0xffc00000
#घोषणा	BDC_DC_NOTCH			0x60000
#घोषणा	BRXNB_NOTCH			0x1f000000
#घोषणा	BPD_TH				0xf
#घोषणा	BPD_TH_OPT2			0xc000
#घोषणा	BPWED_TH			0x700
#घोषणा	BIFMF_WIN_L			0x800
#घोषणा	BPD_OPTION			0x1000
#घोषणा	BMF_WIN_L			0xe000
#घोषणा	BBW_SEARCH_L			0x30000
#घोषणा	BWIN_ENH_L			0xc0000
#घोषणा	BBW_TH				0x700000
#घोषणा	BED_TH2				0x3800000
#घोषणा	BBW_OPTION			0x4000000
#घोषणा	BRADIO_TH			0x18000000
#घोषणा	BWINDOW_L			0xe0000000
#घोषणा	BSBD_OPTION			0x1
#घोषणा	BFRAME_TH			0x1c
#घोषणा	BFS_OPTION			0x60
#घोषणा	BDC_SLOPE_CHECK			0x80
#घोषणा	BFGUARD_COUNTER_DC_L		0xe00
#घोषणा	BFRAME_WEIGHT_SHORT		0x7000
#घोषणा	BSUB_TUNE			0xe00000
#घोषणा	BFRAME_DC_LENGTH		0xe000000
#घोषणा	BSBD_START_OFFSET		0x30000000
#घोषणा	BFRAME_TH_2			0x7
#घोषणा	BFRAME_GI2_TH			0x38
#घोषणा	BGI2_SYNC_EN			0x40
#घोषणा	BSARCH_SHORT_EARLY		0x300
#घोषणा	BSARCH_SHORT_LATE		0xc00
#घोषणा	BSARCH_GI2_LATE			0x70000
#घोषणा	BCFOANTSUM			0x1
#घोषणा	BCFOACC				0x2
#घोषणा	BCFOSTARTOFFSET			0xc
#घोषणा	BCFOLOOPBACK			0x70
#घोषणा	BCFOSUMWEIGHT			0x80
#घोषणा	BDAGCENABLE			0x10000
#घोषणा	BTXIQIMB_A			0x3ff
#घोषणा	BTXIQIMB_b			0xfc00
#घोषणा	BTXIQIMB_C			0x3f0000
#घोषणा	BTXIQIMB_D			0xffc00000
#घोषणा	BTXIDCOFFSET			0xff
#घोषणा	BTXIQDCOFFSET			0xff00
#घोषणा	BTXDFIRMODE			0x10000
#घोषणा	BTXPESUDO_NOISEON		0x4000000
#घोषणा	BTXPESUDO_NOISE_A		0xff
#घोषणा	BTXPESUDO_NOISE_B		0xff00
#घोषणा	BTXPESUDO_NOISE_C		0xff0000
#घोषणा	BTXPESUDO_NOISE_D		0xff000000
#घोषणा	BCCA_DROPOPTION			0x20000
#घोषणा	BCCA_DROPTHRES			0xfff00000
#घोषणा	BEDCCA_H			0xf
#घोषणा	BEDCCA_L			0xf0
#घोषणा	BLAMBDA_ED			0x300
#घोषणा	BRX_INITIALGAIN			0x7f
#घोषणा	BRX_ANTDIV_EN			0x80
#घोषणा	BRX_AGC_ADDRESS_FOR_LNA		0x7f00
#घोषणा	BRX_HIGHPOWER_FLOW		0x8000
#घोषणा	BRX_AGC_FREEZE_THRES		0xc0000
#घोषणा	BRX_FREEZESTEP_AGC1		0x300000
#घोषणा	BRX_FREEZESTEP_AGC2		0xc00000
#घोषणा	BRX_FREEZESTEP_AGC3		0x3000000
#घोषणा	BRX_FREEZESTEP_AGC0		0xc000000
#घोषणा	BRXRSSI_CMP_EN			0x10000000
#घोषणा	BRXQUICK_AGCEN			0x20000000
#घोषणा	BRXAGC_FREEZE_THRES_MODE	0x40000000
#घोषणा	BRX_OVERFLOW_CHECKTYPE		0x80000000
#घोषणा	BRX_AGCSHIFT			0x7f
#घोषणा	BTRSW_TRI_ONLY			0x80
#घोषणा	BPOWER_THRES			0x300
#घोषणा	BRXAGC_EN			0x1
#घोषणा	BRXAGC_TOGETHER_EN		0x2
#घोषणा	BRXAGC_MIN			0x4
#घोषणा	BRXHP_INI			0x7
#घोषणा	BRXHP_TRLNA			0x70
#घोषणा	BRXHP_RSSI			0x700
#घोषणा	BRXHP_BBP1			0x7000
#घोषणा	BRXHP_BBP2			0x70000
#घोषणा	BRXHP_BBP3			0x700000
#घोषणा	BRSSI_H				0x7f0000
#घोषणा	BRSSI_GEN			0x7f000000
#घोषणा	BRXSETTLE_TRSW			0x7
#घोषणा	BRXSETTLE_LNA			0x38
#घोषणा	BRXSETTLE_RSSI			0x1c0
#घोषणा	BRXSETTLE_BBP			0xe00
#घोषणा	BRXSETTLE_RXHP			0x7000
#घोषणा	BRXSETTLE_ANTSW_RSSI		0x38000
#घोषणा	BRXSETTLE_ANTSW			0xc0000
#घोषणा	BRXPROCESS_TIME_DAGC		0x300000
#घोषणा	BRXSETTLE_HSSI			0x400000
#घोषणा	BRXPROCESS_TIME_BBPPW		0x800000
#घोषणा	BRXANTENNA_POWER_SHIFT		0x3000000
#घोषणा	BRSSI_TABLE_SELECT		0xc000000
#घोषणा	BRXHP_FINAL			0x7000000
#घोषणा	BRXHPSETTLE_BBP			0x7
#घोषणा	BRXHTSETTLE_HSSI		0x8
#घोषणा	BRXHTSETTLE_RXHP		0x70
#घोषणा	BRXHTSETTLE_BBPPW		0x80
#घोषणा	BRXHTSETTLE_IDLE		0x300
#घोषणा	BRXHTSETTLE_RESERVED		0x1c00
#घोषणा	BRXHT_RXHP_EN			0x8000
#घोषणा	BRXAGC_FREEZE_THRES		0x30000
#घोषणा	BRXAGC_TOGETHEREN		0x40000
#घोषणा	BRXHTAGC_MIN			0x80000
#घोषणा	BRXHTAGC_EN			0x100000
#घोषणा	BRXHTDAGC_EN			0x200000
#घोषणा	BRXHT_RXHP_BBP			0x1c00000
#घोषणा	BRXHT_RXHP_FINAL		0xe0000000
#घोषणा	BRXPW_RADIO_TH			0x3
#घोषणा	BRXPW_RADIO_EN			0x4
#घोषणा	BRXMF_HOLD			0x3800
#घोषणा	BRXPD_DELAY_TH1			0x38
#घोषणा	BRXPD_DELAY_TH2			0x1c0
#घोषणा	BRXPD_DC_COUNT_MAX		0x600
#घोषणा	BRXPD_DELAY_TH			0x8000
#घोषणा	BRXPROCESS_DELAY		0xf0000
#घोषणा	BRXSEARCHRANGE_GI2_EARLY	0x700000
#घोषणा	BRXFRAME_FUARD_COUNTER_L	0x3800000
#घोषणा	BRXSGI_GUARD_L			0xc000000
#घोषणा	BRXSGI_SEARCH_L			0x30000000
#घोषणा	BRXSGI_TH			0xc0000000
#घोषणा	BDFSCNT0			0xff
#घोषणा	BDFSCNT1			0xff00
#घोषणा	BDFSFLAG			0xf0000
#घोषणा	BMF_WEIGHT_SUM			0x300000
#घोषणा	BMINIDX_TH			0x7f000000
#घोषणा	BDAFORMAT			0x40000
#घोषणा	BTXCH_EMU_ENABLE		0x01000000
#घोषणा	BTRSW_ISOLATION_A		0x7f
#घोषणा	BTRSW_ISOLATION_B		0x7f00
#घोषणा	BTRSW_ISOLATION_C		0x7f0000
#घोषणा	BTRSW_ISOLATION_D		0x7f000000
#घोषणा	BEXT_LNA_GAIN			0x7c00

#घोषणा	BSTBC_EN			0x4
#घोषणा	BANTENNA_MAPPING		0x10
#घोषणा	BNSS				0x20
#घोषणा	BCFO_ANTSUM_ID			0x200
#घोषणा	BPHY_COUNTER_RESET		0x8000000
#घोषणा	BCFO_REPORT_GET			0x4000000
#घोषणा	BOFDM_CONTINUE_TX		0x10000000
#घोषणा	BOFDM_SINGLE_CARRIER		0x20000000
#घोषणा	BOFDM_SINGLE_TONE		0x40000000
#घोषणा	BHT_DETECT			0x100
#घोषणा	BCFOEN				0x10000
#घोषणा	BCFOVALUE			0xfff00000
#घोषणा	BSIGTONE_RE			0x3f
#घोषणा	BSIGTONE_IM			0x7f00
#घोषणा	BCOUNTER_CCA			0xffff
#घोषणा	BCOUNTER_PARITYFAIL		0xffff0000
#घोषणा	BCOUNTER_RATEILLEGAL		0xffff
#घोषणा	BCOUNTER_CRC8FAIL		0xffff0000
#घोषणा	BCOUNTER_MCSNOSUPPORT		0xffff
#घोषणा	BCOUNTER_FASTSYNC		0xffff
#घोषणा	BSHORTCFO			0xfff
#घोषणा	BSHORTCFOT_LENGTH		12
#घोषणा	BSHORTCFOF_LENGTH		11
#घोषणा	BLONGCFO			0x7ff
#घोषणा	BLONGCFOT_LENGTH		11
#घोषणा	BLONGCFOF_LENGTH		11
#घोषणा	BTAILCFO			0x1fff
#घोषणा	BTAILCFOT_LENGTH		13
#घोषणा	BTAILCFOF_LENGTH		12
#घोषणा	BNOISE_EN_PWDB			0xffff
#घोषणा	BCC_POWER_DB			0xffff0000
#घोषणा	BMOISE_PWDB			0xffff
#घोषणा	BPOWERMEAST_LENGTH		10
#घोषणा	BPOWERMEASF_LENGTH		3
#घोषणा	BRX_HT_BW			0x1
#घोषणा	BRXSC				0x6
#घोषणा	BRX_HT				0x8
#घोषणा	BNB_INTF_DET_ON			0x1
#घोषणा	BINTF_WIN_LEN_CFG		0x30
#घोषणा	BNB_INTF_TH_CFG			0x1c0
#घोषणा	BRFGAIN				0x3f
#घोषणा	BTABLESEL			0x40
#घोषणा	BTRSW				0x80
#घोषणा	BRXSNR_A			0xff
#घोषणा	BRXSNR_B			0xff00
#घोषणा	BRXSNR_C			0xff0000
#घोषणा	BRXSNR_D			0xff000000
#घोषणा	BSNR_EVMT_LENGTH		8
#घोषणा	BSNR_EVMF_LENGTH		1
#घोषणा	BCSI1ST				0xff
#घोषणा	BCSI2ND				0xff00
#घोषणा	BRXEVM1ST			0xff0000
#घोषणा	BRXEVM2ND			0xff000000
#घोषणा	BSIGEVM				0xff
#घोषणा	BPWDB				0xff00
#घोषणा	BSGIEN				0x10000

#घोषणा	BSFACTOR_QMA1			0xf
#घोषणा	BSFACTOR_QMA2			0xf0
#घोषणा	BSFACTOR_QMA3			0xf00
#घोषणा	BSFACTOR_QMA4			0xf000
#घोषणा	BSFACTOR_QMA5			0xf0000
#घोषणा	BSFACTOR_QMA6			0xf0000
#घोषणा	BSFACTOR_QMA7			0xf00000
#घोषणा	BSFACTOR_QMA8			0xf000000
#घोषणा	BSFACTOR_QMA9			0xf0000000
#घोषणा	BCSI_SCHEME			0x100000

#घोषणा	BNOISE_LVL_TOP_SET		0x3
#घोषणा	BCHSMOOTH			0x4
#घोषणा	BCHSMOOTH_CFG1			0x38
#घोषणा	BCHSMOOTH_CFG2			0x1c0
#घोषणा	BCHSMOOTH_CFG3			0xe00
#घोषणा	BCHSMOOTH_CFG4			0x7000
#घोषणा	BMRCMODE			0x800000
#घोषणा	BTHEVMCFG			0x7000000

#घोषणा	BLOOP_FIT_TYPE			0x1
#घोषणा	BUPD_CFO			0x40
#घोषणा	BUPD_CFO_OFFDATA		0x80
#घोषणा	BADV_UPD_CFO			0x100
#घोषणा	BADV_TIME_CTRL			0x800
#घोषणा	BUPD_CLKO			0x1000
#घोषणा	BFC				0x6000
#घोषणा	BTRACKING_MODE			0x8000
#घोषणा	BPHCMP_ENABLE			0x10000
#घोषणा	BUPD_CLKO_LTF			0x20000
#घोषणा	BCOM_CH_CFO			0x40000
#घोषणा	BCSI_ESTI_MODE			0x80000
#घोषणा	BADV_UPD_EQZ			0x100000
#घोषणा	BUCHCFG				0x7000000
#घोषणा	BUPDEQZ				0x8000000

#घोषणा	BRX_PESUDO_NOISE_ON		0x20000000
#घोषणा	BRX_PESUDO_NOISE_A		0xff
#घोषणा	BRX_PESUDO_NOISE_B		0xff00
#घोषणा	BRX_PESUDO_NOISE_C		0xff0000
#घोषणा	BRX_PESUDO_NOISE_D		0xff000000
#घोषणा	BRX_PESUDO_NOISESTATE_A		0xffff
#घोषणा	BRX_PESUDO_NOISESTATE_B		0xffff0000
#घोषणा	BRX_PESUDO_NOISESTATE_C		0xffff
#घोषणा	BRX_PESUDO_NOISESTATE_D		0xffff0000

#घोषणा	BZEBRA1_HSSIENABLE		0x8
#घोषणा	BZEBRA1_TRXCONTROL		0xc00
#घोषणा	BZEBRA1_TRXGAINSETTING		0x07f
#घोषणा	BZEBRA1_RXCOUNTER		0xc00
#घोषणा	BZEBRA1_TXCHANGEPUMP		0x38
#घोषणा	BZEBRA1_RXCHANGEPUMP		0x7
#घोषणा	BZEBRA1_CHANNEL_NUM		0xf80
#घोषणा	BZEBRA1_TXLPFBW			0x400
#घोषणा	BZEBRA1_RXLPFBW			0x600

#घोषणा	BRTL8256REG_MODE_CTRL1		0x100
#घोषणा	BRTL8256REG_MODE_CTRL0		0x40
#घोषणा	BRTL8256REG_TXLPFBW		0x18
#घोषणा	BRTL8256REG_RXLPFBW		0x600

#घोषणा	BRTL8258_TXLPFBW		0xc
#घोषणा	BRTL8258_RXLPFBW		0xc00
#घोषणा	BRTL8258_RSSILPFBW		0xc0

#घोषणा	BBYTE0				0x1
#घोषणा	BBYTE1				0x2
#घोषणा	BBYTE2				0x4
#घोषणा	BBYTE3				0x8
#घोषणा	BWORD0				0x3
#घोषणा	BWORD1				0xc
#घोषणा	BWORD				0xf

#घोषणा	MASKBYTE0			0xff
#घोषणा	MASKBYTE1			0xff00
#घोषणा	MASKBYTE2			0xff0000
#घोषणा	MASKBYTE3			0xff000000
#घोषणा	MASKHWORD			0xffff0000
#घोषणा	MASKLWORD			0x0000ffff
#घोषणा	MASKDWORD			0xffffffff
#घोषणा	MASK12BITS			0xfff
#घोषणा	MASKH4BITS			0xf0000000
#घोषणा MASKOFDM_D			0xffc00000
#घोषणा	MASKCCK				0x3f3f3f3f

#घोषणा	MASK4BITS			0x0f
#घोषणा	MASK20BITS			0xfffff
#घोषणा RFREG_OFFSET_MASK		0xfffff

#घोषणा	BENABLE				0x1
#घोषणा	BDISABLE			0x0

#घोषणा	LEFT_ANTENNA			0x0
#घोषणा	RIGHT_ANTENNA			0x1

#घोषणा	TCHECK_TXSTATUS			500
#घोषणा	TUPDATE_RXCOUNTER		100

#घोषणा	REG_UN_used_रेजिस्टर		0x01bf

/* WOL bit inक्रमmation */
#घोषणा	HAL92C_WOL_PTK_UPDATE_EVENT	BIT(0)
#घोषणा	HAL92C_WOL_GTK_UPDATE_EVENT	BIT(1)
#घोषणा	HAL92C_WOL_DISASSOC_EVENT	BIT(2)
#घोषणा	HAL92C_WOL_DEAUTH_EVENT		BIT(3)
#घोषणा	HAL92C_WOL_FW_DISCONNECT_EVENT	BIT(4)

#घोषणा		WOL_REASON_PTK_UPDATE		BIT(0)
#घोषणा		WOL_REASON_GTK_UPDATE		BIT(1)
#घोषणा		WOL_REASON_DISASSOC		BIT(2)
#घोषणा		WOL_REASON_DEAUTH		BIT(3)
#घोषणा		WOL_REASON_FW_DISCONNECT	BIT(4)

/* 2 EFUSE_TEST (For RTL8723 partially) */
#घोषणा EFUSE_SEL(x)				(((x) & 0x3) << 8)
#घोषणा EFUSE_SEL_MASK				0x300
#घोषणा EFUSE_WIFI_SEL_0			0x0

#घोषणा	WL_HWPDN_EN	BIT(0)	/* Enable GPIO[9] as WiFi HW PDn source*/
#घोषणा	WL_HWPDN_SL	BIT(1)	/* WiFi HW PDn polarity control*/

#पूर्ण_अगर
