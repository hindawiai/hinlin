<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __REALTEK_92S_REG_H__
#घोषणा __REALTEK_92S_REG_H__

/* 1. System Configuration Registers  */
#घोषणा	REG_SYS_ISO_CTRL			0x0000
#घोषणा	REG_SYS_FUNC_EN				0x0002
#घोषणा	PMC_FSM					0x0004
#घोषणा	SYS_CLKR				0x0008
#घोषणा	EPROM_CMD				0x000A
#घोषणा	EE_VPD					0x000C
#घोषणा	AFE_MISC				0x0010
#घोषणा	SPS0_CTRL				0x0011
#घोषणा	SPS1_CTRL				0x0018
#घोषणा	RF_CTRL					0x001F
#घोषणा	LDOA15_CTRL				0x0020
#घोषणा	LDOV12D_CTRL				0x0021
#घोषणा	LDOHCI12_CTRL				0x0022
#घोषणा	LDO_USB_SDIO				0x0023
#घोषणा	LPLDO_CTRL				0x0024
#घोषणा	AFE_XTAL_CTRL				0x0026
#घोषणा	AFE_PLL_CTRL				0x0028
#घोषणा	REG_EFUSE_CTRL				0x0030
#घोषणा	REG_EFUSE_TEST				0x0034
#घोषणा	PWR_DATA				0x0038
#घोषणा	DBG_PORT				0x003A
#घोषणा	DPS_TIMER				0x003C
#घोषणा	RCLK_MON				0x003E

/* 2. Command Control Registers	  */
#घोषणा	CMDR					0x0040
#घोषणा	TXPAUSE					0x0042
#घोषणा	LBKMD_SEL				0x0043
#घोषणा	TCR					0x0044
#घोषणा	RCR					0x0048
#घोषणा	MSR					0x004C
#घोषणा	SYSF_CFG				0x004D
#घोषणा	RX_PKY_LIMIT				0x004E
#घोषणा	MBIDCTRL				0x004F

/* 3. MACID Setting Registers	 */
#घोषणा	MACIDR					0x0050
#घोषणा	MACIDR0					0x0050
#घोषणा	MACIDR4					0x0054
#घोषणा	BSSIDR					0x0058
#घोषणा	HWVID					0x005E
#घोषणा	MAR					0x0060
#घोषणा	MBIDCAMCONTENT				0x0068
#घोषणा	MBIDCAMCFG				0x0070
#घोषणा	BUILDTIME				0x0074
#घोषणा	BUILDUSER				0x0078

#घोषणा	IDR0					MACIDR0
#घोषणा	IDR4					MACIDR4

/* 4. Timing Control Registers	 */
#घोषणा	TSFR					0x0080
#घोषणा	SLOT_TIME				0x0089
#घोषणा	USTIME					0x008A
#घोषणा	SIFS_CCK				0x008C
#घोषणा	SIFS_OFDM				0x008E
#घोषणा	PIFS_TIME				0x0090
#घोषणा	ACK_TIMEOUT				0x0091
#घोषणा	EIFSTR					0x0092
#घोषणा	BCN_INTERVAL				0x0094
#घोषणा	ATIMWND					0x0096
#घोषणा	BCN_DRV_EARLY_INT			0x0098
#घोषणा	BCN_DMATIME				0x009A
#घोषणा	BCN_ERR_THRESH				0x009C
#घोषणा	MLT					0x009D
#घोषणा	RSVD_MAC_TUNE_US			0x009E

/* 5. FIFO Control Registers	  */
#घोषणा RQPN					0x00A0
#घोषणा	RQPN1					0x00A0
#घोषणा	RQPN2					0x00A1
#घोषणा	RQPN3					0x00A2
#घोषणा	RQPN4					0x00A3
#घोषणा	RQPN5					0x00A4
#घोषणा	RQPN6					0x00A5
#घोषणा	RQPN7					0x00A6
#घोषणा	RQPN8					0x00A7
#घोषणा	RQPN9					0x00A8
#घोषणा	RQPN10					0x00A9
#घोषणा	LD_RQPN					0x00AB
#घोषणा	RXFF_BNDY				0x00AC
#घोषणा	RXRPT_BNDY				0x00B0
#घोषणा	TXPKTBUF_PGBNDY				0x00B4
#घोषणा	PBP					0x00B5
#घोषणा	RXDRVINFO_SZ				0x00B6
#घोषणा	TXFF_STATUS				0x00B7
#घोषणा	RXFF_STATUS				0x00B8
#घोषणा	TXFF_EMPTY_TH				0x00B9
#घोषणा	SDIO_RX_BLKSZ				0x00BC
#घोषणा	RXDMA					0x00BD
#घोषणा	RXPKT_NUM				0x00BE
#घोषणा	C2HCMD_UDT_SIZE				0x00C0
#घोषणा	C2HCMD_UDT_ADDR				0x00C2
#घोषणा	FIFOPAGE1				0x00C4
#घोषणा	FIFOPAGE2				0x00C8
#घोषणा	FIFOPAGE3				0x00CC
#घोषणा	FIFOPAGE4				0x00D0
#घोषणा	FIFOPAGE5				0x00D4
#घोषणा	FW_RSVD_PG_CRTL				0x00D8
#घोषणा	RXDMA_AGG_PG_TH				0x00D9
#घोषणा	TXDESC_MSK				0x00DC
#घोषणा	TXRPTFF_RDPTR				0x00E0
#घोषणा	TXRPTFF_WTPTR				0x00E4
#घोषणा	C2HFF_RDPTR				0x00E8
#घोषणा	C2HFF_WTPTR				0x00EC
#घोषणा	RXFF0_RDPTR				0x00F0
#घोषणा	RXFF0_WTPTR				0x00F4
#घोषणा	RXFF1_RDPTR				0x00F8
#घोषणा	RXFF1_WTPTR				0x00FC
#घोषणा	RXRPT0_RDPTR				0x0100
#घोषणा	RXRPT0_WTPTR				0x0104
#घोषणा	RXRPT1_RDPTR				0x0108
#घोषणा	RXRPT1_WTPTR				0x010C
#घोषणा	RX0_UDT_SIZE				0x0110
#घोषणा	RX1PKTNUM				0x0114
#घोषणा	RXFILTERMAP				0x0116
#घोषणा	RXFILTERMAP_GP1				0x0118
#घोषणा	RXFILTERMAP_GP2				0x011A
#घोषणा	RXFILTERMAP_GP3				0x011C
#घोषणा	BCNQ_CTRL				0x0120
#घोषणा	MGTQ_CTRL				0x0124
#घोषणा	HIQ_CTRL				0x0128
#घोषणा	VOTID7_CTRL				0x012c
#घोषणा	VOTID6_CTRL				0x0130
#घोषणा	VITID5_CTRL				0x0134
#घोषणा	VITID4_CTRL				0x0138
#घोषणा	BETID3_CTRL				0x013c
#घोषणा	BETID0_CTRL				0x0140
#घोषणा	BKTID2_CTRL				0x0144
#घोषणा	BKTID1_CTRL				0x0148
#घोषणा	CMDQ_CTRL				0x014c
#घोषणा	TXPKT_NUM_CTRL				0x0150
#घोषणा	TXQ_PGADD				0x0152
#घोषणा	TXFF_PG_NUM				0x0154
#घोषणा	TRXDMA_STATUS				0x0156

/* 6. Adaptive Control Registers   */
#घोषणा	INIMCS_SEL				0x0160
#घोषणा	TX_RATE_REG				INIMCS_SEL
#घोषणा	INIRTSMCS_SEL				0x0180
#घोषणा	RRSR					0x0181
#घोषणा	ARFR0					0x0184
#घोषणा	ARFR1					0x0188
#घोषणा	ARFR2					0x018C
#घोषणा	ARFR3					0x0190
#घोषणा	ARFR4					0x0194
#घोषणा	ARFR5					0x0198
#घोषणा	ARFR6					0x019C
#घोषणा	ARFR7					0x01A0
#घोषणा	AGGLEN_LMT_H				0x01A7
#घोषणा	AGGLEN_LMT_L				0x01A8
#घोषणा	DARFRC					0x01B0
#घोषणा	RARFRC					0x01B8
#घोषणा	MCS_TXAGC				0x01C0
#घोषणा	CCK_TXAGC				0x01C8

/* 7. EDCA Setting Registers */
#घोषणा	EDCAPARA_VO				0x01D0
#घोषणा	EDCAPARA_VI				0x01D4
#घोषणा	EDCAPARA_BE				0x01D8
#घोषणा	EDCAPARA_BK				0x01DC
#घोषणा	BCNTCFG					0x01E0
#घोषणा	CWRR					0x01E2
#घोषणा	ACMAVG					0x01E4
#घोषणा	ACMHWCTRL				0x01E7
#घोषणा	VO_ADMTM				0x01E8
#घोषणा	VI_ADMTM				0x01EC
#घोषणा	BE_ADMTM				0x01F0
#घोषणा	RETRY_LIMIT				0x01F4
#घोषणा	SG_RATE					0x01F6

/* 8. WMAC, BA and CCX related Register. */
#घोषणा	NAV_CTRL				0x0200
#घोषणा	BW_OPMODE				0x0203
#घोषणा	BACAMCMD				0x0204
#घोषणा	BACAMCONTENT				0x0208

/* the 0x2xx रेजिस्टर WMAC definition */
#घोषणा	LBDLY					0x0210
#घोषणा	FWDLY					0x0211
#घोषणा	HWPC_RX_CTRL				0x0218
#घोषणा	MQIR					0x0220
#घोषणा	MAIR					0x0222
#घोषणा	MSIR					0x0224
#घोषणा	CLM_RESULT				0x0227
#घोषणा	NHM_RPI_CNT				0x0228
#घोषणा	RXERR_RPT				0x0230
#घोषणा	NAV_PROT_LEN				0x0234
#घोषणा	CFEND_TH				0x0236
#घोषणा	AMPDU_MIN_SPACE				0x0237
#घोषणा	TXOP_STALL_CTRL				0x0238

/* 9. Security Control Registers */
#घोषणा	REG_RWCAM				0x0240
#घोषणा	REG_WCAMI				0x0244
#घोषणा	REG_RCAMO				0x0248
#घोषणा	REG_CAMDBG				0x024C
#घोषणा	REG_SECR				0x0250

/* 10. Power Save Control Registers */
#घोषणा	WOW_CTRL				0x0260
#घोषणा	PSSTATUS				0x0261
#घोषणा	PSSWITCH				0x0262
#घोषणा	MIMOPS_WAIT_PERIOD			0x0263
#घोषणा	LPNAV_CTRL				0x0264
#घोषणा	WFM0					0x0270
#घोषणा	WFM1					0x0280
#घोषणा	WFM2					0x0290
#घोषणा	WFM3					0x02A0
#घोषणा	WFM4					0x02B0
#घोषणा	WFM5					0x02C0
#घोषणा	WFCRC					0x02D0
#घोषणा	FW_RPT_REG				0x02c4

/* 11. General Purpose Registers */
#घोषणा	PSTIME					0x02E0
#घोषणा	TIMER0					0x02E4
#घोषणा	TIMER1					0x02E8
#घोषणा	GPIO_IN_SE				0x02EC
#घोषणा	GPIO_IO_SEL				0x02EE
#घोषणा	MAC_PINMUX_CFG				0x02F1
#घोषणा	LEDCFG					0x02F2
#घोषणा	PHY_REG					0x02F3
#घोषणा	PHY_REG_DATA				0x02F4
#घोषणा	REG_EFUSE_CLK				0x02F8

/* 12. Host Interrupt Status Registers */
#घोषणा	INTA_MASK				0x0300
#घोषणा	ISR					0x0308

/* 13. Test mode and Debug Control Registers */
#घोषणा	DBG_PORT_SWITCH				0x003A
#घोषणा	BIST					0x0310
#घोषणा	DBS					0x0314
#घोषणा	CPUINST					0x0318
#घोषणा	CPUCAUSE				0x031C
#घोषणा	LBUS_ERR_ADDR				0x0320
#घोषणा	LBUS_ERR_CMD				0x0324
#घोषणा	LBUS_ERR_DATA_L				0x0328
#घोषणा	LBUS_ERR_DATA_H				0x032C
#घोषणा	LX_EXCEPTION_ADDR			0x0330
#घोषणा	WDG_CTRL				0x0334
#घोषणा	INTMTU					0x0338
#घोषणा	INTM					0x033A
#घोषणा	FDLOCKTURN0				0x033C
#घोषणा	FDLOCKTURN1				0x033D
#घोषणा	TRXPKTBUF_DBG_DATA			0x0340
#घोषणा	TRXPKTBUF_DBG_CTRL			0x0348
#घोषणा	DPLL					0x034A
#घोषणा	CBUS_ERR_ADDR				0x0350
#घोषणा	CBUS_ERR_CMD				0x0354
#घोषणा	CBUS_ERR_DATA_L				0x0358
#घोषणा	CBUS_ERR_DATA_H				0x035C
#घोषणा	USB_SIE_INTF_ADDR			0x0360
#घोषणा	USB_SIE_INTF_WD				0x0361
#घोषणा	USB_SIE_INTF_RD				0x0362
#घोषणा	USB_SIE_INTF_CTRL			0x0363
#घोषणा LBUS_MON_ADDR				0x0364
#घोषणा LBUS_ADDR_MASK				0x0368

/* Boundary is 0x37F */

/* 14. PCIE config रेजिस्टर */
#घोषणा	TP_POLL					0x0500
#घोषणा	PM_CTRL					0x0502
#घोषणा	PCIF					0x0503

#घोषणा	THPDA					0x0514
#घोषणा	TMDA					0x0518
#घोषणा	TCDA					0x051C
#घोषणा	HDA					0x0520
#घोषणा	TVODA					0x0524
#घोषणा	TVIDA					0x0528
#घोषणा	TBEDA					0x052C
#घोषणा	TBKDA					0x0530
#घोषणा	TBDA					0x0534
#घोषणा	RCDA					0x0538
#घोषणा	RDQDA					0x053C
#घोषणा	DBI_WDATA				0x0540
#घोषणा	DBI_RDATA				0x0544
#घोषणा	DBI_CTRL				0x0548
#घोषणा	MDIO_DATA				0x0550
#घोषणा	MDIO_CTRL				0x0554
#घोषणा	PCI_RPWM				0x0561
#घोषणा	PCI_CPWM				0x0563

/* Config रेजिस्टर	(Offset 0x800-) */
#घोषणा	PHY_CCA					0x803

/* Min Spacing related settings. */
#घोषणा	MAX_MSS_DENSITY_2T			0x13
#घोषणा	MAX_MSS_DENSITY_1T			0x0A

/* Rx DMA Control related settings */
#घोषणा	RXDMA_AGG_EN				BIT(7)

#घोषणा	RPWM					PCI_RPWM

/* Regsiter Bit and Content definition  */

#घोषणा	ISO_MD2PP				BIT(0)
#घोषणा	ISO_PA2PCIE				BIT(3)
#घोषणा	ISO_PLL2MD				BIT(4)
#घोषणा	ISO_PWC_DV2RP				BIT(11)
#घोषणा	ISO_PWC_RV2RP				BIT(12)


#घोषणा	FEN_MREGEN				BIT(15)
#घोषणा	FEN_DCORE				BIT(11)
#घोषणा	FEN_CPUEN				BIT(10)

#घोषणा	PAD_HWPD_IDN				BIT(22)

#घोषणा	SYS_CLKSEL_80M				BIT(0)
#घोषणा	SYS_PS_CLKSEL				BIT(1)
#घोषणा	SYS_CPU_CLKSEL				BIT(2)
#घोषणा	SYS_MAC_CLK_EN				BIT(11)
#घोषणा	SYS_SWHW_SEL				BIT(14)
#घोषणा	SYS_FWHW_SEL				BIT(15)

#घोषणा	CMDEEPROM_EN				BIT(5)
#घोषणा	CMDEERPOMSEL				BIT(4)
#घोषणा	CMD9346CR_9356SEL			BIT(4)

#घोषणा	AFE_MBEN				BIT(1)
#घोषणा	AFE_BGEN				BIT(0)

#घोषणा	SPS1_SWEN				BIT(1)
#घोषणा	SPS1_LDEN				BIT(0)

#घोषणा	RF_EN					BIT(0)
#घोषणा	RF_RSTB					BIT(1)
#घोषणा	RF_SDMRSTB				BIT(2)

#घोषणा	LDA15_EN				BIT(0)

#घोषणा	LDV12_EN				BIT(0)
#घोषणा	LDV12_SDBY				BIT(1)

#घोषणा	XTAL_GATE_AFE				BIT(10)

#घोषणा	APLL_EN					BIT(0)

#घोषणा	AFR_CARDBEN				BIT(0)
#घोषणा	AFR_CLKRUN_SEL				BIT(1)
#घोषणा	AFR_FUNCREGEN				BIT(2)

#घोषणा	APSDOFF_STATUS				BIT(15)
#घोषणा	APSDOFF					BIT(14)
#घोषणा	BBRSTN					BIT(13)
#घोषणा	BB_GLB_RSTN				BIT(12)
#घोषणा	SCHEDULE_EN				BIT(10)
#घोषणा	MACRXEN					BIT(9)
#घोषणा	MACTXEN					BIT(8)
#घोषणा	DDMA_EN					BIT(7)
#घोषणा	FW2HW_EN				BIT(6)
#घोषणा	RXDMA_EN				BIT(5)
#घोषणा	TXDMA_EN				BIT(4)
#घोषणा	HCI_RXDMA_EN				BIT(3)
#घोषणा	HCI_TXDMA_EN				BIT(2)

#घोषणा	STOPHCCA				BIT(6)
#घोषणा	STOPHIGH				BIT(5)
#घोषणा	STOPMGT					BIT(4)
#घोषणा	STOPVO					BIT(3)
#घोषणा	STOPVI					BIT(2)
#घोषणा	STOPBE					BIT(1)
#घोषणा	STOPBK					BIT(0)

#घोषणा	LBK_NORMAL				0x00
#घोषणा	LBK_MAC_LB				(BIT(0) | BIT(1) | BIT(3))
#घोषणा	LBK_MAC_DLB				(BIT(0) | BIT(1))
#घोषणा	LBK_DMA_LB				(BIT(0) | BIT(1) | BIT(2))

#घोषणा	TCP_OFDL_EN				BIT(25)
#घोषणा	HWPC_TX_EN				BIT(24)
#घोषणा	TXDMAPRE2FULL				BIT(23)
#घोषणा	DISCW					BIT(20)
#घोषणा	TCRICV					BIT(19)
#घोषणा	cfendक्रमm				BIT(17)
#घोषणा	TCRCRC					BIT(16)
#घोषणा	FAKE_IMEM_EN				BIT(15)
#घोषणा	TSFRST					BIT(9)
#घोषणा	TSFEN					BIT(8)
#घोषणा	FWALLRDY				(BIT(0) | BIT(1) | BIT(2) | \
						BIT(3) | BIT(4) | BIT(5) | \
						BIT(6) | BIT(7))
#घोषणा	FWRDY					BIT(7)
#घोषणा	BASECHG					BIT(6)
#घोषणा	IMEM					BIT(5)
#घोषणा	DMEM_CODE_DONE				BIT(4)
#घोषणा	EXT_IMEM_CHK_RPT			BIT(3)
#घोषणा	EXT_IMEM_CODE_DONE			BIT(2)
#घोषणा	IMEM_CHK_RPT				BIT(1)
#घोषणा	IMEM_CODE_DONE				BIT(0)
#घोषणा	EMEM_CODE_DONE				BIT(2)
#घोषणा	EMEM_CHK_RPT				BIT(3)
#घोषणा	IMEM_RDY				BIT(5)
#घोषणा	LOAD_FW_READY				(IMEM_CODE_DONE | \
						IMEM_CHK_RPT | \
						EMEM_CODE_DONE | \
						EMEM_CHK_RPT | \
						DMEM_CODE_DONE | \
						IMEM_RDY | \
						BASECHG | \
						FWRDY)
#घोषणा	TCR_TSFEN				BIT(8)
#घोषणा	TCR_TSFRST				BIT(9)
#घोषणा	TCR_FAKE_IMEM_EN			BIT(15)
#घोषणा	TCR_CRC					BIT(16)
#घोषणा	TCR_ICV					BIT(19)
#घोषणा	TCR_DISCW				BIT(20)
#घोषणा	TCR_HWPC_TX_EN				BIT(24)
#घोषणा	TCR_TCP_OFDL_EN				BIT(25)
#घोषणा	TXDMA_INIT_VALUE			(IMEM_CHK_RPT | \
						EXT_IMEM_CHK_RPT)

#घोषणा	RCR_APPFCS				BIT(31)
#घोषणा	RCR_DIS_ENC_2BYTE			BIT(30)
#घोषणा	RCR_DIS_AES_2BYTE			BIT(29)
#घोषणा	RCR_HTC_LOC_CTRL			BIT(28)
#घोषणा	RCR_ENMBID				BIT(27)
#घोषणा	RCR_RX_TCPOFDL_EN			BIT(26)
#घोषणा	RCR_APP_PHYST_RXFF			BIT(25)
#घोषणा	RCR_APP_PHYST_STAFF			BIT(24)
#घोषणा	RCR_CBSSID				BIT(23)
#घोषणा	RCR_APWRMGT				BIT(22)
#घोषणा	RCR_ADD3				BIT(21)
#घोषणा	RCR_AMF					BIT(20)
#घोषणा	RCR_ACF					BIT(19)
#घोषणा	RCR_ADF					BIT(18)
#घोषणा	RCR_APP_MIC				BIT(17)
#घोषणा	RCR_APP_ICV				BIT(16)
#घोषणा	RCR_RXFTH				BIT(13)
#घोषणा	RCR_AICV				BIT(12)
#घोषणा	RCR_RXDESC_LK_EN			BIT(11)
#घोषणा	RCR_APP_BA_SSN				BIT(6)
#घोषणा	RCR_ACRC32				BIT(5)
#घोषणा	RCR_RXSHFT_EN				BIT(4)
#घोषणा	RCR_AB					BIT(3)
#घोषणा	RCR_AM					BIT(2)
#घोषणा	RCR_APM					BIT(1)
#घोषणा	RCR_AAP					BIT(0)
#घोषणा	RCR_MXDMA_OFFSET			8
#घोषणा	RCR_FIFO_OFFSET				13


#घोषणा MSR_LINK_MASK				((1 << 0) | (1 << 1))
#घोषणा MSR_LINK_MANAGED			2
#घोषणा MSR_LINK_NONE				0
#घोषणा MSR_LINK_SHIFT				0
#घोषणा MSR_LINK_ADHOC				1
#घोषणा MSR_LINK_MASTER				3
#घोषणा	MSR_NOLINK				0x00
#घोषणा	MSR_ADHOC				0x01
#घोषणा	MSR_INFRA				0x02
#घोषणा	MSR_AP					0x03

#घोषणा	ENUART					BIT(7)
#घोषणा	ENJTAG					BIT(3)
#घोषणा	BTMODE					(BIT(2) | BIT(1))
#घोषणा	ENBT					BIT(0)

#घोषणा	ENMBID					BIT(7)
#घोषणा	BCNUM					(BIT(6) | BIT(5) | BIT(4))

#घोषणा	USTIME_EDCA				0xFF00
#घोषणा	USTIME_TSF				0x00FF

#घोषणा	SIFS_TRX				0xFF00
#घोषणा	SIFS_CTX				0x00FF

#घोषणा	ENSWBCN					BIT(15)
#घोषणा	DRVERLY_TU				0x0FF0
#घोषणा	DRVERLY_US				0x000F
#घोषणा	BCN_TCFG_CW_SHIFT			8
#घोषणा	BCN_TCFG_IFS				0

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

#घोषणा	RATE_ALL_CCK				(RATR_1M | RATR_2M | \
						RATR_55M | RATR_11M)
#घोषणा	RATE_ALL_OFDM_AG			(RATR_6M | RATR_9M | \
						RATR_12M | RATR_18M | \
						RATR_24M | RATR_36M | \
						RATR_48M | RATR_54M)
#घोषणा	RATE_ALL_OFDM_1SS			(RATR_MCS0 | RATR_MCS1 | \
						RATR_MCS2 | RATR_MCS3 | \
						RATR_MCS4 | RATR_MCS5 | \
						RATR_MCS6 | RATR_MCS7)
#घोषणा	RATE_ALL_OFDM_2SS			(RATR_MCS8 | RATR_MCS9 | \
						RATR_MCS10 | RATR_MCS11 | \
						RATR_MCS12 | RATR_MCS13 | \
						RATR_MCS14 | RATR_MCS15)

#घोषणा	AC_PARAM_TXOP_LIMIT_OFFSET		16
#घोषणा	AC_PARAM_ECW_MAX_OFFSET			12
#घोषणा	AC_PARAM_ECW_MIN_OFFSET			8
#घोषणा	AC_PARAM_AIFS_OFFSET			0

#घोषणा	ACMHW_HWEN				BIT(0)
#घोषणा	ACMHW_BEQEN				BIT(1)
#घोषणा	ACMHW_VIQEN				BIT(2)
#घोषणा	ACMHW_VOQEN				BIT(3)
#घोषणा	ACMHW_BEQSTATUS				BIT(4)
#घोषणा	ACMHW_VIQSTATUS				BIT(5)
#घोषणा	ACMHW_VOQSTATUS				BIT(6)

#घोषणा	RETRY_LIMIT_SHORT_SHIFT			8
#घोषणा	RETRY_LIMIT_LONG_SHIFT			0

#घोषणा	NAV_UPPER_EN				BIT(16)
#घोषणा	NAV_UPPER				0xFF00
#घोषणा	NAV_RTSRST				0xFF

#घोषणा	BW_OPMODE_20MHZ				BIT(2)
#घोषणा	BW_OPMODE_5G				BIT(1)
#घोषणा	BW_OPMODE_11J				BIT(0)

#घोषणा	RXERR_RPT_RST				BIT(27)
#घोषणा	RXERR_OFDM_PPDU				0
#घोषणा	RXERR_OFDM_FALSE_ALARM			1
#घोषणा	RXERR_OFDM_MPDU_OK			2
#घोषणा	RXERR_OFDM_MPDU_FAIL			3
#घोषणा	RXERR_CCK_PPDU				4
#घोषणा	RXERR_CCK_FALSE_ALARM			5
#घोषणा	RXERR_CCK_MPDU_OK			6
#घोषणा	RXERR_CCK_MPDU_FAIL			7
#घोषणा	RXERR_HT_PPDU				8
#घोषणा	RXERR_HT_FALSE_ALARM			9
#घोषणा	RXERR_HT_MPDU_TOTAL			10
#घोषणा	RXERR_HT_MPDU_OK			11
#घोषणा	RXERR_HT_MPDU_FAIL			12
#घोषणा	RXERR_RX_FULL_DROP			15

#घोषणा	SCR_TXUSEDK				BIT(0)
#घोषणा	SCR_RXUSEDK				BIT(1)
#घोषणा	SCR_TXENCENABLE				BIT(2)
#घोषणा	SCR_RXENCENABLE				BIT(3)
#घोषणा	SCR_SKBYA2				BIT(4)
#घोषणा	SCR_NOSKMC				BIT(5)

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

#घोषणा	WOW_PMEN				BIT(0)
#घोषणा	WOW_WOMEN				BIT(1)
#घोषणा	WOW_MAGIC				BIT(2)
#घोषणा	WOW_UWF					BIT(3)

#घोषणा	GPIOMUX_EN				BIT(3)
#घोषणा	GPIOSEL_GPIO				0
#घोषणा	GPIOSEL_PHYDBG				1
#घोषणा	GPIOSEL_BT				2
#घोषणा	GPIOSEL_WLANDBG				3
#घोषणा	GPIOSEL_GPIO_MASK			(~(BIT(0)|BIT(1)))

#घोषणा	HST_RDBUSY				BIT(0)
#घोषणा	CPU_WTBUSY				BIT(1)

#घोषणा	IMR8190_DISABLED			0x0
#घोषणा	IMR_CPUERR				BIT(5)
#घोषणा	IMR_ATIMEND				BIT(4)
#घोषणा	IMR_TBDOK				BIT(3)
#घोषणा	IMR_TBDER				BIT(2)
#घोषणा	IMR_BCNDMAINT8				BIT(1)
#घोषणा	IMR_BCNDMAINT7				BIT(0)
#घोषणा	IMR_BCNDMAINT6				BIT(31)
#घोषणा	IMR_BCNDMAINT5				BIT(30)
#घोषणा	IMR_BCNDMAINT4				BIT(29)
#घोषणा	IMR_BCNDMAINT3				BIT(28)
#घोषणा	IMR_BCNDMAINT2				BIT(27)
#घोषणा	IMR_BCNDMAINT1				BIT(26)
#घोषणा	IMR_BCNDOK8				BIT(25)
#घोषणा	IMR_BCNDOK7				BIT(24)
#घोषणा	IMR_BCNDOK6				BIT(23)
#घोषणा	IMR_BCNDOK5				BIT(22)
#घोषणा	IMR_BCNDOK4				BIT(21)
#घोषणा	IMR_BCNDOK3				BIT(20)
#घोषणा	IMR_BCNDOK2				BIT(19)
#घोषणा	IMR_BCNDOK1				BIT(18)
#घोषणा	IMR_TIMEOUT2				BIT(17)
#घोषणा	IMR_TIMEOUT1				BIT(16)
#घोषणा	IMR_TXFOVW				BIT(15)
#घोषणा	IMR_PSTIMEOUT				BIT(14)
#घोषणा	IMR_BCNINT				BIT(13)
#घोषणा	IMR_RXFOVW				BIT(12)
#घोषणा	IMR_RDU					BIT(11)
#घोषणा	IMR_RXCMDOK				BIT(10)
#घोषणा	IMR_BDOK				BIT(9)
#घोषणा	IMR_HIGHDOK				BIT(8)
#घोषणा	IMR_COMDOK				BIT(7)
#घोषणा	IMR_MGNTDOK				BIT(6)
#घोषणा	IMR_HCCADOK				BIT(5)
#घोषणा	IMR_BKDOK				BIT(4)
#घोषणा	IMR_BEDOK				BIT(3)
#घोषणा	IMR_VIDOK				BIT(2)
#घोषणा	IMR_VODOK				BIT(1)
#घोषणा	IMR_ROK					BIT(0)

#घोषणा	TPPOLL_BKQ				BIT(0)
#घोषणा	TPPOLL_BEQ				BIT(1)
#घोषणा	TPPOLL_VIQ				BIT(2)
#घोषणा	TPPOLL_VOQ				BIT(3)
#घोषणा	TPPOLL_BQ				BIT(4)
#घोषणा	TPPOLL_CQ				BIT(5)
#घोषणा	TPPOLL_MQ				BIT(6)
#घोषणा	TPPOLL_HQ				BIT(7)
#घोषणा	TPPOLL_HCCAQ				BIT(8)
#घोषणा	TPPOLL_STOPBK				BIT(9)
#घोषणा	TPPOLL_STOPBE				BIT(10)
#घोषणा	TPPOLL_STOPVI				BIT(11)
#घोषणा	TPPOLL_STOPVO				BIT(12)
#घोषणा	TPPOLL_STOPMGT				BIT(13)
#घोषणा	TPPOLL_STOPHIGH				BIT(14)
#घोषणा	TPPOLL_STOPHCCA				BIT(15)
#घोषणा	TPPOLL_SHIFT				8

#घोषणा	CCX_CMD_CLM_ENABLE			BIT(0)
#घोषणा	CCX_CMD_NHM_ENABLE			BIT(1)
#घोषणा	CCX_CMD_FUNCTION_ENABLE			BIT(8)
#घोषणा	CCX_CMD_IGNORE_CCA			BIT(9)
#घोषणा	CCX_CMD_IGNORE_TXON			BIT(10)
#घोषणा	CCX_CLM_RESULT_READY			BIT(16)
#घोषणा	CCX_NHM_RESULT_READY			BIT(16)
#घोषणा	CCX_CMD_RESET				0x0


#घोषणा	HWSET_MAX_SIZE_92S			128
#घोषणा EFUSE_MAX_SECTION			16
#घोषणा EFUSE_REAL_CONTENT_LEN			512
#घोषणा EFUSE_OOB_PROTECT_BYTES			15

#घोषणा RTL8190_EEPROM_ID			0x8129
#घोषणा EEPROM_HPON				0x02
#घोषणा EEPROM_CLK				0x06
#घोषणा EEPROM_TESTR				0x08

#घोषणा EEPROM_VID				0x0A
#घोषणा EEPROM_DID				0x0C
#घोषणा EEPROM_SVID				0x0E
#घोषणा EEPROM_SMID				0x10

#घोषणा EEPROM_MAC_ADDR				0x12
#घोषणा EEPROM_NODE_ADDRESS_BYTE_0		0x12

#घोषणा EEPROM_PWDIFF				0x54

#घोषणा EEPROM_TXPOWERBASE			0x50
#घोषणा	EEPROM_TX_PWR_INDEX_RANGE		28

#घोषणा EEPROM_TX_PWR_HT20_DIFF			0x62
#घोषणा DEFAULT_HT20_TXPWR_DIFF			2
#घोषणा EEPROM_TX_PWR_OFDM_DIFF			0x65

#घोषणा	EEPROM_TXPWRGROUP			0x67
#घोषणा EEPROM_REGULATORY			0x6D

#घोषणा TX_PWR_SAFETY_CHK			0x6D
#घोषणा EEPROM_TXPWINDEX_CCK_24G		0x5D
#घोषणा EEPROM_TXPWINDEX_OFDM_24G		0x6B
#घोषणा EEPROM_HT2T_CH1_A			0x6c
#घोषणा EEPROM_HT2T_CH7_A			0x6d
#घोषणा EEPROM_HT2T_CH13_A			0x6e
#घोषणा EEPROM_HT2T_CH1_B			0x6f
#घोषणा EEPROM_HT2T_CH7_B			0x70
#घोषणा EEPROM_HT2T_CH13_B			0x71

#घोषणा EEPROM_TSSI_A				0x74
#घोषणा EEPROM_TSSI_B				0x75

#घोषणा	EEPROM_RFIND_POWERDIFF			0x76
#घोषणा	EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF	0x3

#घोषणा EEPROM_THERMALMETER			0x77
#घोषणा	EEPROM_BLUETOOTH_COEXIST		0x78
#घोषणा	EEPROM_BLUETOOTH_TYPE			0x4f

#घोषणा	EEPROM_OPTIONAL				0x78
#घोषणा	EEPROM_WOWLAN				0x78

#घोषणा EEPROM_CRYSTALCAP			0x79
#घोषणा EEPROM_CHANNELPLAN			0x7B
#घोषणा EEPROM_VERSION				0x7C
#घोषणा	EEPROM_CUSTOMID				0x7A
#घोषणा EEPROM_BOARDTYPE			0x7E

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

#घोषणा	FW_DIG_DISABLE				0xfd00cc00
#घोषणा	FW_DIG_ENABLE				0xfd000000
#घोषणा	FW_DIG_HALT				0xfd000001
#घोषणा	FW_DIG_RESUME				0xfd000002
#घोषणा	FW_HIGH_PWR_DISABLE			0xfd000008
#घोषणा	FW_HIGH_PWR_ENABLE			0xfd000009
#घोषणा	FW_ADD_A2_ENTRY				0xfd000016
#घोषणा	FW_TXPWR_TRACK_ENABLE			0xfd000017
#घोषणा	FW_TXPWR_TRACK_DISABLE			0xfd000018
#घोषणा	FW_TXPWR_TRACK_THERMAL			0xfd000019
#घोषणा	FW_TXANT_SWITCH_ENABLE			0xfd000023
#घोषणा	FW_TXANT_SWITCH_DISABLE			0xfd000024
#घोषणा	FW_RA_INIT				0xfd000026
#घोषणा	FW_CTRL_DM_BY_DRIVER			0Xfd00002a
#घोषणा	FW_RA_IOT_BG_COMB			0xfd000030
#घोषणा	FW_RA_IOT_N_COMB			0xfd000031
#घोषणा	FW_RA_REFRESH				0xfd0000a0
#घोषणा	FW_RA_UPDATE_MASK			0xfd0000a2
#घोषणा	FW_RA_DISABLE				0xfd0000a4
#घोषणा	FW_RA_ACTIVE				0xfd0000a6
#घोषणा	FW_RA_DISABLE_RSSI_MASK			0xfd0000ac
#घोषणा	FW_RA_ENABLE_RSSI_MASK			0xfd0000ad
#घोषणा	FW_RA_RESET				0xfd0000af
#घोषणा	FW_DM_DISABLE				0xfd00aa00
#घोषणा	FW_IQK_ENABLE				0xf0000020
#घोषणा	FW_IQK_SUCCESS				0x0000dddd
#घोषणा	FW_IQK_FAIL				0x0000ffff
#घोषणा	FW_OP_FAILURE				0xffffffff
#घोषणा	FW_TX_FEEDBACK_NONE			0xfb000000
#घोषणा	FW_TX_FEEDBACK_DTM_ENABLE		(FW_TX_FEEDBACK_NONE | 0x1)
#घोषणा	FW_TX_FEEDBACK_CCX_ENABL		(FW_TX_FEEDBACK_NONE | 0x2)
#घोषणा	FW_BB_RESET_ENABLE			0xff00000d
#घोषणा	FW_BB_RESET_DISABLE			0xff00000e
#घोषणा	FW_CCA_CHK_ENABLE			0xff000011
#घोषणा	FW_CCK_RESET_CNT			0xff000013
#घोषणा	FW_LPS_ENTER				0xfe000010
#घोषणा	FW_LPS_LEAVE				0xfe000011
#घोषणा	FW_INसूचीECT_READ			0xf2000000
#घोषणा	FW_INसूचीECT_WRITE			0xf2000001
#घोषणा	FW_CHAN_SET				0xf3000001

#घोषणा RFPC					0x5F
#घोषणा RCR_9356SEL				BIT(6)
#घोषणा TCR_LRL_OFFSET				0
#घोषणा TCR_SRL_OFFSET				8
#घोषणा TCR_MXDMA_OFFSET			21
#घोषणा TCR_SAT					BIT(24)
#घोषणा RCR_MXDMA_OFFSET			8
#घोषणा RCR_FIFO_OFFSET				13
#घोषणा RCR_ONLYERLPKT				BIT(31)
#घोषणा CWR					0xDC
#घोषणा RETRYCTR				0xDE

#घोषणा CPU_GEN_SYSTEM_RESET			0x00000001

#घोषणा	CCX_COMMAND_REG				0x890
#घोषणा	CLM_PERIOD_REG				0x894
#घोषणा	NHM_PERIOD_REG				0x896

#घोषणा	NHM_THRESHOLD0				0x898
#घोषणा	NHM_THRESHOLD1				0x899
#घोषणा	NHM_THRESHOLD2				0x89A
#घोषणा	NHM_THRESHOLD3				0x89B
#घोषणा	NHM_THRESHOLD4				0x89C
#घोषणा	NHM_THRESHOLD5				0x89D
#घोषणा	NHM_THRESHOLD6				0x89E
#घोषणा	CLM_RESULT_REG				0x8D0
#घोषणा	NHM_RESULT_REG				0x8D4
#घोषणा	NHM_RPI_COUNTER0			0x8D8
#घोषणा	NHM_RPI_COUNTER1			0x8D9
#घोषणा	NHM_RPI_COUNTER2			0x8DA
#घोषणा	NHM_RPI_COUNTER3			0x8DB
#घोषणा	NHM_RPI_COUNTER4			0x8DC
#घोषणा	NHM_RPI_COUNTER5			0x8DD
#घोषणा	NHM_RPI_COUNTER6			0x8DE
#घोषणा	NHM_RPI_COUNTER7			0x8DF

#घोषणा	HAL_8192S_HW_GPIO_OFF_BIT		BIT(3)
#घोषणा	HAL_8192S_HW_GPIO_OFF_MASK		0xF7
#घोषणा	HAL_8192S_HW_GPIO_WPS_BIT		BIT(4)

#घोषणा	RPMAC_RESET				0x100
#घोषणा	RPMAC_TXSTART				0x104
#घोषणा	RPMAC_TXLEGACYSIG			0x108
#घोषणा	RPMAC_TXHTSIG1				0x10c
#घोषणा	RPMAC_TXHTSIG2				0x110
#घोषणा	RPMAC_PHYDEBUG				0x114
#घोषणा	RPMAC_TXPACKETNNM			0x118
#घोषणा	RPMAC_TXIDLE				0x11c
#घोषणा	RPMAC_TXMACHEADER0			0x120
#घोषणा	RPMAC_TXMACHEADER1			0x124
#घोषणा	RPMAC_TXMACHEADER2			0x128
#घोषणा	RPMAC_TXMACHEADER3			0x12c
#घोषणा	RPMAC_TXMACHEADER4			0x130
#घोषणा	RPMAC_TXMACHEADER5			0x134
#घोषणा	RPMAC_TXDATATYPE			0x138
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

#घोषणा	RF_BB_CMD_ADDR				0x02c0
#घोषणा	RF_BB_CMD_DATA				0x02c4

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
#घोषणा	RFPGA0_XC_HSSIPARAMETER1		0x830
#घोषणा	RFPGA0_XC_HSSIPARAMETER2		0x834
#घोषणा	RFPGA0_XD_HSSIPARAMETER1		0x838
#घोषणा	RFPGA0_XD_HSSIPARAMETER2		0x83c
#घोषणा	RFPGA0_XA_LSSIPARAMETER			0x840
#घोषणा	RFPGA0_XB_LSSIPARAMETER			0x844
#घोषणा	RFPGA0_XC_LSSIPARAMETER			0x848
#घोषणा	RFPGA0_XD_LSSIPARAMETER			0x84c

#घोषणा	RFPGA0_RFWAKEUP_PARAMETER		0x850
#घोषणा	RFPGA0_RFSLEEPUP_PARAMETER		0x854

#घोषणा	RFPGA0_XAB_SWITCHCONTROL		0x858
#घोषणा	RFPGA0_XCD_SWITCHCONTROL		0x85c

#घोषणा	RFPGA0_XA_RFINTERFACEOE			0x860
#घोषणा	RFPGA0_XB_RFINTERFACEOE			0x864
#घोषणा	RFPGA0_XC_RFINTERFACEOE			0x868
#घोषणा	RFPGA0_XD_RFINTERFACEOE			0x86c

#घोषणा	RFPGA0_XAB_RFINTERFACESW		0x870
#घोषणा	RFPGA0_XCD_RFINTERFACESW		0x874

#घोषणा	RFPGA0_XAB_RFPARAMETER			0x878
#घोषणा	RFPGA0_XCD_RFPARAMETER			0x87c

#घोषणा	RFPGA0_ANALOGPARAMETER1			0x880
#घोषणा	RFPGA0_ANALOGPARAMETER2			0x884
#घोषणा	RFPGA0_ANALOGPARAMETER3			0x888
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
#घोषणा	RFPGA1_RFMOD				0x900

#घोषणा	RFPGA1_TXBLOCK				0x904
#घोषणा	RFPGA1_DEBUGSELECT			0x908
#घोषणा	RFPGA1_TXINFO				0x90c

#घोषणा	RCCK0_SYSTEM				0xa00

#घोषणा	RCCK0_AFESETTING			0xa04
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
#घोषणा	ROFDM0_CFO_AND_DAGC			0xc44
#घोषणा	ROFDM0_CCADROP_THRESHOLD		0xc48
#घोषणा	ROFDM0_ECCA_THRESHOLD			0xc4c

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

#घोषणा	ROFDM0_RXHP_PARAMETER			0xce0
#घोषणा	ROFDM0_TXPSEUDO_NOISE_WGT		0xce4
#घोषणा	ROFDM0_FRAME_SYNC			0xcf0
#घोषणा	ROFDM0_DFSREPORT			0xcf4
#घोषणा	ROFDM0_TXCOEFF1				0xca4
#घोषणा	ROFDM0_TXCOEFF2				0xca8
#घोषणा	ROFDM0_TXCOEFF3				0xcac
#घोषणा	ROFDM0_TXCOEFF4				0xcb0
#घोषणा	ROFDM0_TXCOEFF5				0xcb4
#घोषणा	ROFDM0_TXCOEFF6				0xcb8


#घोषणा	ROFDM1_LSTF				0xd00
#घोषणा	ROFDM1_TRXPATHENABLE			0xd04

#घोषणा	ROFDM1_CFO				0xd08
#घोषणा	ROFDM1_CSI1				0xd10
#घोषणा	ROFDM1_SBD				0xd14
#घोषणा	ROFDM1_CSI2				0xd18
#घोषणा	ROFDM1_CFOTRACKING			0xd2c
#घोषणा	ROFDM1_TRXMESAURE1			0xd34
#घोषणा	ROFDM1_INTF_DET				0xd3c
#घोषणा	ROFDM1_PSEUDO_NOISESTATEAB		0xd50
#घोषणा	ROFDM1_PSEUDO_NOISESTATECD		0xd54
#घोषणा	ROFDM1_RX_PSEUDO_NOISE_WGT		0xd58

#घोषणा	ROFDM_PHYCOUNTER1			0xda0
#घोषणा	ROFDM_PHYCOUNTER2			0xda4
#घोषणा	ROFDM_PHYCOUNTER3			0xda8

#घोषणा	ROFDM_SHORT_CFOAB			0xdac
#घोषणा	ROFDM_SHORT_CFOCD			0xdb0
#घोषणा	ROFDM_LONG_CFOAB			0xdb4
#घोषणा	ROFDM_LONG_CFOCD			0xdb8
#घोषणा	ROFDM_TAIL_CFOAB			0xdbc
#घोषणा	ROFDM_TAIL_CFOCD			0xdc0
#घोषणा	ROFDM_PW_MEASURE1			0xdc4
#घोषणा	ROFDM_PW_MEASURE2			0xdc8
#घोषणा	ROFDM_BW_REPORT				0xdcc
#घोषणा	ROFDM_AGC_REPORT			0xdd0
#घोषणा	ROFDM_RXSNR				0xdd4
#घोषणा	ROFDM_RXEVMCSI				0xdd8
#घोषणा	ROFDM_SIG_REPORT			0xddc


#घोषणा	RTXAGC_RATE18_06			0xe00
#घोषणा	RTXAGC_RATE54_24			0xe04
#घोषणा	RTXAGC_CCK_MCS32			0xe08
#घोषणा	RTXAGC_MCS03_MCS00			0xe10
#घोषणा	RTXAGC_MCS07_MCS04			0xe14
#घोषणा	RTXAGC_MCS11_MCS08			0xe18
#घोषणा	RTXAGC_MCS15_MCS12			0xe1c


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
#घोषणा	RF_CHANNEL				0x18
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
#घोषणा	RF_T_METER				0x24
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

#घोषणा	BRFMOD					0x1
#घोषणा	BCCKEN					0x1000000
#घोषणा	BOFDMEN					0x2000000

#घोषणा	BXBTXAGC				0xf00
#घोषणा	BXCTXAGC				0xf000
#घोषणा	BXDTXAGC				0xf0000

#घोषणा	B3WIRE_DATALENGTH			0x800
#घोषणा	B3WIRE_ADDRESSLENGTH			0x400

#घोषणा	BRFSI_RFENV				0x10

#घोषणा	BLSSI_READADDRESS			0x7f800000
#घोषणा	BLSSI_READEDGE				0x80000000
#घोषणा	BLSSI_READBACK_DATA			0xfffff

#घोषणा	BADCLKPHASE				0x4000000

#घोषणा	BCCK_SIDEBAND				0x10

#घोषणा	BTX_AGCRATECCK				0x7f00

#पूर्ण_अगर
