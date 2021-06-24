<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*****************************************************************************
 *Copyright(c) 2009,  RealTEK Technology Inc. All Right Reserved.
 *
 * Module:	__INC_HAL8723BREG_H
 *
 *
 * Note:	1. Define Mac रेजिस्टर address and corresponding bit mask map
 *
 *
 * Export:	Constants, macro, functions(API), global variables(None).
 *
 * Abbrev:
 *
 * History:
 *	Data		Who		Remark
 *
 *****************************************************************************/
#अगर_अघोषित __INC_HAL8723BREG_H
#घोषणा __INC_HAL8723BREG_H

/*  */
/*  */
/*  */

/*  */
/*  */
/*	0x0000h ~ 0x00FFh	System Configuration */
/*  */
/*  */
#घोषणा REG_SYS_ISO_CTRL_8723B			0x0000	/*  2 Byte */
#घोषणा REG_SYS_FUNC_EN_8723B			0x0002	/*  2 Byte */
#घोषणा REG_APS_FSMCO_8723B			0x0004	/*  4 Byte */
#घोषणा REG_SYS_CLKR_8723B			0x0008	/*  2 Byte */
#घोषणा REG_9346CR_8723B			0x000A	/*  2 Byte */
#घोषणा REG_EE_VPD_8723B			0x000C	/*  2 Byte */
#घोषणा REG_AFE_MISC_8723B			0x0010	/*  1 Byte */
#घोषणा REG_SPS0_CTRL_8723B			0x0011	/*  7 Byte */
#घोषणा REG_SPS_OCP_CFG_8723B			0x0018	/*  4 Byte */
#घोषणा REG_RSV_CTRL_8723B			0x001C	/*  3 Byte */
#घोषणा REG_RF_CTRL_8723B			0x001F	/*  1 Byte */
#घोषणा REG_LPLDO_CTRL_8723B			0x0023	/*  1 Byte */
#घोषणा REG_AFE_XTAL_CTRL_8723B			0x0024	/*  4 Byte */
#घोषणा REG_AFE_PLL_CTRL_8723B			0x0028	/*  4 Byte */
#घोषणा REG_MAC_PLL_CTRL_EXT_8723B		0x002c	/*  4 Byte */
#घोषणा REG_EFUSE_CTRL_8723B			0x0030
#घोषणा REG_EFUSE_TEST_8723B			0x0034
#घोषणा REG_PWR_DATA_8723B			0x0038
#घोषणा REG_CAL_TIMER_8723B			0x003C
#घोषणा REG_ACLK_MON_8723B			0x003E
#घोषणा REG_GPIO_MUXCFG_8723B			0x0040
#घोषणा REG_GPIO_IO_SEL_8723B			0x0042
#घोषणा REG_MAC_PINMUX_CFG_8723B		0x0043
#घोषणा REG_GPIO_PIN_CTRL_8723B			0x0044
#घोषणा REG_GPIO_INTM_8723B			0x0048
#घोषणा REG_LEDCFG0_8723B			0x004C
#घोषणा REG_LEDCFG1_8723B			0x004D
#घोषणा REG_LEDCFG2_8723B			0x004E
#घोषणा REG_LEDCFG3_8723B			0x004F
#घोषणा REG_FSIMR_8723B				0x0050
#घोषणा REG_FSISR_8723B				0x0054
#घोषणा REG_HSIMR_8723B				0x0058
#घोषणा REG_HSISR_8723B				0x005c
#घोषणा REG_GPIO_EXT_CTRL			0x0060
#घोषणा REG_MULTI_FUNC_CTRL_8723B		0x0068
#घोषणा REG_GPIO_STATUS_8723B			0x006C
#घोषणा REG_SDIO_CTRL_8723B			0x0070
#घोषणा REG_OPT_CTRL_8723B			0x0074
#घोषणा REG_AFE_XTAL_CTRL_EXT_8723B		0x0078
#घोषणा REG_MCUFWDL_8723B			0x0080
#घोषणा REG_BT_PATCH_STATUS_8723B		0x0088
#घोषणा REG_HIMR0_8723B				0x00B0
#घोषणा REG_HISR0_8723B				0x00B4
#घोषणा REG_HIMR1_8723B				0x00B8
#घोषणा REG_HISR1_8723B				0x00BC
#घोषणा REG_PMC_DBG_CTRL2_8723B			0x00CC
#घोषणा	REG_EFUSE_BURN_GNT_8723B		0x00CF
#घोषणा REG_HPON_FSM_8723B			0x00EC
#घोषणा REG_SYS_CFG_8723B			0x00F0
#घोषणा REG_SYS_CFG1_8723B			0x00FC
#घोषणा REG_ROM_VERSION				0x00FD

/*  */
/*  */
/*	0x0100h ~ 0x01FFh	MACTOP General Configuration */
/*  */
/*  */
#घोषणा REG_CR_8723B				0x0100
#घोषणा REG_PBP_8723B				0x0104
#घोषणा REG_PKT_BUFF_ACCESS_CTRL_8723B		0x0106
#घोषणा REG_TRXDMA_CTRL_8723B			0x010C
#घोषणा REG_TRXFF_BNDY_8723B			0x0114
#घोषणा REG_TRXFF_STATUS_8723B			0x0118
#घोषणा REG_RXFF_PTR_8723B			0x011C
#घोषणा REG_CPWM_8723B				0x012F
#घोषणा REG_FWIMR_8723B				0x0130
#घोषणा REG_FWISR_8723B				0x0134
#घोषणा REG_FTIMR_8723B				0x0138
#घोषणा REG_PKTBUF_DBG_CTRL_8723B		0x0140
#घोषणा REG_RXPKTBUF_CTRL_8723B			0x0142
#घोषणा REG_PKTBUF_DBG_DATA_L_8723B		0x0144
#घोषणा REG_PKTBUF_DBG_DATA_H_8723B		0x0148

#घोषणा REG_TC0_CTRL_8723B			0x0150
#घोषणा REG_TC1_CTRL_8723B			0x0154
#घोषणा REG_TC2_CTRL_8723B			0x0158
#घोषणा REG_TC3_CTRL_8723B			0x015C
#घोषणा REG_TC4_CTRL_8723B			0x0160
#घोषणा REG_TCUNIT_BASE_8723B			0x0164
#घोषणा REG_RSVD3_8723B				0x0168
#घोषणा REG_C2HEVT_MSG_NORMAL_8723B		0x01A0
#घोषणा REG_C2HEVT_CMD_SEQ_88XX			0x01A1
#घोषणा REG_C2HEVT_CMD_CONTENT_88XX		0x01A2
#घोषणा REG_C2HEVT_CMD_LEN_88XX			0x01AE
#घोषणा REG_C2HEVT_CLEAR_8723B			0x01AF
#घोषणा REG_MCUTST_1_8723B			0x01C0
#घोषणा REG_MCUTST_WOWLAN_8723B			0x01C7
#घोषणा REG_FMETHR_8723B			0x01C8
#घोषणा REG_HMETFR_8723B			0x01CC
#घोषणा REG_HMEBOX_0_8723B			0x01D0
#घोषणा REG_HMEBOX_1_8723B			0x01D4
#घोषणा REG_HMEBOX_2_8723B			0x01D8
#घोषणा REG_HMEBOX_3_8723B			0x01DC
#घोषणा REG_LLT_INIT_8723B			0x01E0
#घोषणा REG_HMEBOX_EXT0_8723B			0x01F0
#घोषणा REG_HMEBOX_EXT1_8723B			0x01F4
#घोषणा REG_HMEBOX_EXT2_8723B			0x01F8
#घोषणा REG_HMEBOX_EXT3_8723B			0x01FC

/*  */
/*  */
/*	0x0200h ~ 0x027Fh	TXDMA Configuration */
/*  */
/*  */
#घोषणा REG_RQPN_8723B				0x0200
#घोषणा REG_FIFOPAGE_8723B			0x0204
#घोषणा REG_DWBCN0_CTRL_8723B			REG_TDECTRL
#घोषणा REG_TXDMA_OFFSET_CHK_8723B		0x020C
#घोषणा REG_TXDMA_STATUS_8723B			0x0210
#घोषणा REG_RQPN_NPQ_8723B			0x0214
#घोषणा REG_DWBCN1_CTRL_8723B			0x0228

/*  */
/*  */
/*	0x0280h ~ 0x02FFh	RXDMA Configuration */
/*  */
/*  */
#घोषणा REG_RXDMA_AGG_PG_TH_8723B		0x0280
#घोषणा REG_FW_UPD_RDPTR_8723B			0x0284 /*  FW shall update this रेजिस्टर beक्रमe FW ग_लिखो RXPKT_RELEASE_POLL to 1 */
#घोषणा REG_RXDMA_CONTROL_8723B			0x0286 /*  Control the RX DMA. */
#घोषणा REG_RXPKT_NUM_8723B			0x0287 /*  The number of packets in RXPKTBUF. */
#घोषणा REG_RXDMA_STATUS_8723B			0x0288
#घोषणा REG_RXDMA_PRO_8723B			0x0290
#घोषणा REG_EARLY_MODE_CONTROL_8723B		0x02BC
#घोषणा REG_RSVD5_8723B				0x02F0
#घोषणा REG_RSVD6_8723B				0x02F4

/*  */
/*  */
/*	0x0300h ~ 0x03FFh	PCIe */
/*  */
/*  */
#घोषणा	REG_PCIE_CTRL_REG_8723B			0x0300
#घोषणा	REG_INT_MIG_8723B			0x0304	/*  Interrupt Migration */
#घोषणा	REG_BCNQ_DESA_8723B			0x0308	/*  TX Beacon Descriptor Address */
#घोषणा	REG_HQ_DESA_8723B			0x0310	/*  TX High Queue Descriptor Address */
#घोषणा	REG_MGQ_DESA_8723B			0x0318	/*  TX Manage Queue Descriptor Address */
#घोषणा	REG_VOQ_DESA_8723B			0x0320	/*  TX VO Queue Descriptor Address */
#घोषणा	REG_VIQ_DESA_8723B			0x0328	/*  TX VI Queue Descriptor Address */
#घोषणा	REG_BEQ_DESA_8723B			0x0330	/*  TX BE Queue Descriptor Address */
#घोषणा	REG_BKQ_DESA_8723B			0x0338	/*  TX BK Queue Descriptor Address */
#घोषणा	REG_RX_DESA_8723B			0x0340	/*  RX Queue	Descriptor Address */
#घोषणा	REG_DBI_WDATA_8723B			0x0348	/*  DBI Write Data */
#घोषणा	REG_DBI_RDATA_8723B			0x034C	/*  DBI Read Data */
#घोषणा	REG_DBI_ADDR_8723B			0x0350	/*  DBI Address */
#घोषणा	REG_DBI_FLAG_8723B			0x0352	/*  DBI Read/Write Flag */
#घोषणा	REG_MDIO_WDATA_8723B			0x0354	/*  MDIO क्रम Write PCIE PHY */
#घोषणा	REG_MDIO_RDATA_8723B			0x0356	/*  MDIO क्रम Reads PCIE PHY */
#घोषणा	REG_MDIO_CTL_8723B			0x0358	/*  MDIO क्रम Control */
#घोषणा	REG_DBG_SEL_8723B			0x0360	/*  Debug Selection Register */
#घोषणा	REG_PCIE_HRPWM_8723B			0x0361	/* PCIe RPWM */
#घोषणा	REG_PCIE_HCPWM_8723B			0x0363	/* PCIe CPWM */
#घोषणा	REG_PCIE_MULTIFET_CTRL_8723B		0x036A	/* PCIE Multi-Fethc Control */

/*  spec version 11 */
/*  */
/*  */
/*	0x0400h ~ 0x047Fh	Protocol Configuration */
/*  */
/*  */
#घोषणा REG_VOQ_INFORMATION_8723B		0x0400
#घोषणा REG_VIQ_INFORMATION_8723B		0x0404
#घोषणा REG_BEQ_INFORMATION_8723B		0x0408
#घोषणा REG_BKQ_INFORMATION_8723B		0x040C
#घोषणा REG_MGQ_INFORMATION_8723B		0x0410
#घोषणा REG_HGQ_INFORMATION_8723B		0x0414
#घोषणा REG_BCNQ_INFORMATION_8723B		0x0418
#घोषणा REG_TXPKT_EMPTY_8723B			0x041A

#घोषणा REG_FWHW_TXQ_CTRL_8723B			0x0420
#घोषणा REG_HWSEQ_CTRL_8723B			0x0423
#घोषणा REG_TXPKTBUF_BCNQ_BDNY_8723B		0x0424
#घोषणा REG_TXPKTBUF_MGQ_BDNY_8723B		0x0425
#घोषणा REG_LIFECTRL_CTRL_8723B			0x0426
#घोषणा REG_MULTI_BCNQ_OFFSET_8723B		0x0427
#घोषणा REG_SPEC_SIFS_8723B			0x0428
#घोषणा REG_RL_8723B				0x042A
#घोषणा REG_TXBF_CTRL_8723B			0x042C
#घोषणा REG_DARFRC_8723B			0x0430
#घोषणा REG_RARFRC_8723B			0x0438
#घोषणा REG_RRSR_8723B				0x0440
#घोषणा REG_ARFR0_8723B				0x0444
#घोषणा REG_ARFR1_8723B				0x044C
#घोषणा REG_CCK_CHECK_8723B			0x0454
#घोषणा REG_AMPDU_MAX_TIME_8723B		0x0456
#घोषणा REG_TXPKTBUF_BCNQ_BDNY1_8723B		0x0457

#घोषणा REG_AMPDU_MAX_LENGTH_8723B		0x0458
#घोषणा REG_TXPKTBUF_WMAC_LBK_BF_HD_8723B	0x045D
#घोषणा REG_NDPA_OPT_CTRL_8723B			0x045F
#घोषणा REG_FAST_EDCA_CTRL_8723B		0x0460
#घोषणा REG_RD_RESP_PKT_TH_8723B		0x0463
#घोषणा REG_DATA_SC_8723B			0x0483
#घोषणा REG_TXRPT_START_OFFSET			0x04AC
#घोषणा REG_POWER_STAGE1_8723B			0x04B4
#घोषणा REG_POWER_STAGE2_8723B			0x04B8
#घोषणा REG_AMPDU_BURST_MODE_8723B		0x04BC
#घोषणा REG_PKT_VO_VI_LIFE_TIME_8723B		0x04C0
#घोषणा REG_PKT_BE_BK_LIFE_TIME_8723B		0x04C2
#घोषणा REG_STBC_SETTING_8723B			0x04C4
#घोषणा REG_HT_SINGLE_AMPDU_8723B		0x04C7
#घोषणा REG_PROT_MODE_CTRL_8723B		0x04C8
#घोषणा REG_MAX_AGGR_NUM_8723B			0x04CA
#घोषणा REG_RTS_MAX_AGGR_NUM_8723B		0x04CB
#घोषणा REG_BAR_MODE_CTRL_8723B			0x04CC
#घोषणा REG_RA_TRY_RATE_AGG_LMT_8723B		0x04CF
#घोषणा REG_MACID_PKT_DROP0_8723B		0x04D0
#घोषणा REG_MACID_PKT_SLEEP_8723B		0x04D4

/*  */
/*  */
/*	0x0500h ~ 0x05FFh	EDCA Configuration */
/*  */
/*  */
#घोषणा REG_EDCA_VO_PARAM_8723B			0x0500
#घोषणा REG_EDCA_VI_PARAM_8723B			0x0504
#घोषणा REG_EDCA_BE_PARAM_8723B			0x0508
#घोषणा REG_EDCA_BK_PARAM_8723B			0x050C
#घोषणा REG_BCNTCFG_8723B			0x0510
#घोषणा REG_PIFS_8723B				0x0512
#घोषणा REG_RDG_PIFS_8723B			0x0513
#घोषणा REG_SIFS_CTX_8723B			0x0514
#घोषणा REG_SIFS_TRX_8723B			0x0516
#घोषणा REG_AGGR_BREAK_TIME_8723B		0x051A
#घोषणा REG_SLOT_8723B				0x051B
#घोषणा REG_TX_PTCL_CTRL_8723B			0x0520
#घोषणा REG_TXPAUSE_8723B			0x0522
#घोषणा REG_DIS_TXREQ_CLR_8723B			0x0523
#घोषणा REG_RD_CTRL_8723B			0x0524
/*  */
/*  Format क्रम offset 540h-542h: */
/*	[3:0]:	TBTT prohibit setup in unit of 32us. The समय क्रम HW getting beacon content beक्रमe TBTT. */
/*	[7:4]:	Reserved. */
/*	[19:8]:	TBTT prohibit hold in unit of 32us. The समय क्रम HW holding to send the beacon packet. */
/*	[23:20]: Reserved */
/*  Description: */
/* 	              | */
/*      |<--Setup--|--Hold------------>| */
/* 	--------------|---------------------- */
/*                 | */
/*                TBTT */
/*  Note: We cannot update beacon content to HW or send any AC packets during the समय between Setup and Hold. */
/*  Described by Designer Tim and Bruce, 2011-01-14. */
/*  */
#घोषणा REG_TBTT_PROHIBIT_8723B			0x0540
#घोषणा REG_RD_NAV_NXT_8723B			0x0544
#घोषणा REG_NAV_PROT_LEN_8723B			0x0546
#घोषणा REG_BCN_CTRL_8723B			0x0550
#घोषणा REG_BCN_CTRL_1_8723B			0x0551
#घोषणा REG_MBID_NUM_8723B			0x0552
#घोषणा REG_DUAL_TSF_RST_8723B			0x0553
#घोषणा REG_BCN_INTERVAL_8723B			0x0554
#घोषणा REG_DRVERLYINT_8723B			0x0558
#घोषणा REG_BCNDMATIM_8723B			0x0559
#घोषणा REG_ATIMWND_8723B			0x055A
#घोषणा REG_USTIME_TSF_8723B			0x055C
#घोषणा REG_BCN_MAX_ERR_8723B			0x055D
#घोषणा REG_RXTSF_OFFSET_CCK_8723B		0x055E
#घोषणा REG_RXTSF_OFFSET_OFDM_8723B		0x055F
#घोषणा REG_TSFTR_8723B				0x0560
#घोषणा REG_CTWND_8723B				0x0572
#घोषणा REG_SECONDARY_CCA_CTRL_8723B		0x0577
#घोषणा REG_PSTIMER_8723B			0x0580
#घोषणा REG_TIMER0_8723B			0x0584
#घोषणा REG_TIMER1_8723B			0x0588
#घोषणा REG_ACMHWCTRL_8723B			0x05C0
#घोषणा REG_SCH_TXCMD_8723B			0x05F8

/*	0x0600h ~ 0x07FFh	WMAC Configuration */
#घोषणा REG_MAC_CR_8723B			0x0600
#घोषणा REG_TCR_8723B				0x0604
#घोषणा REG_RCR_8723B				0x0608
#घोषणा REG_RX_PKT_LIMIT_8723B			0x060C
#घोषणा REG_RX_DLK_TIME_8723B			0x060D
#घोषणा REG_RX_DRVINFO_SZ_8723B			0x060F

#घोषणा REG_MACID_8723B				0x0610
#घोषणा REG_BSSID_8723B				0x0618
#घोषणा REG_MAR_8723B				0x0620
#घोषणा REG_MBIDCAMCFG_8723B			0x0628

#घोषणा REG_USTIME_EDCA_8723B			0x0638
#घोषणा REG_MAC_SPEC_SIFS_8723B			0x063A
#घोषणा REG_RESP_SIFP_CCK_8723B			0x063C
#घोषणा REG_RESP_SIFS_OFDM_8723B		0x063E
#घोषणा REG_ACKTO_8723B				0x0640
#घोषणा REG_CTS2TO_8723B			0x0641
#घोषणा REG_EIFS_8723B				0x0642

#घोषणा REG_NAV_UPPER_8723B			0x0652	/*  unit of 128 */
#घोषणा REG_TRXPTCL_CTL_8723B			0x0668

/*  Security */
#घोषणा REG_CAMCMD_8723B			0x0670
#घोषणा REG_CAMWRITE_8723B			0x0674
#घोषणा REG_CAMREAD_8723B			0x0678
#घोषणा REG_CAMDBG_8723B			0x067C
#घोषणा REG_SECCFG_8723B			0x0680

/*  Power */
#घोषणा REG_WOW_CTRL_8723B			0x0690
#घोषणा REG_PS_RX_INFO_8723B			0x0692
#घोषणा REG_UAPSD_TID_8723B			0x0693
#घोषणा REG_WKFMCAM_CMD_8723B			0x0698
#घोषणा REG_WKFMCAM_NUM_8723B			0x0698
#घोषणा REG_WKFMCAM_RWD_8723B			0x069C
#घोषणा REG_RXFLTMAP0_8723B			0x06A0
#घोषणा REG_RXFLTMAP1_8723B			0x06A2
#घोषणा REG_RXFLTMAP2_8723B			0x06A4
#घोषणा REG_BCN_PSR_RPT_8723B			0x06A8
#घोषणा REG_BT_COEX_TABLE_8723B			0x06C0
#घोषणा REG_BFMER0_INFO_8723B			0x06E4
#घोषणा REG_BFMER1_INFO_8723B			0x06EC
#घोषणा REG_CSI_RPT_PARAM_BW20_8723B		0x06F4
#घोषणा REG_CSI_RPT_PARAM_BW40_8723B		0x06F8
#घोषणा REG_CSI_RPT_PARAM_BW80_8723B		0x06FC

/*  Hardware Port 2 */
#घोषणा REG_MACID1_8723B			0x0700
#घोषणा REG_BSSID1_8723B			0x0708
#घोषणा REG_BFMEE_SEL_8723B			0x0714
#घोषणा REG_SND_PTCL_CTRL_8723B			0x0718

/*	Redअगरine 8192C रेजिस्टर definition क्रम compatibility */

/*  TODO: use these definition when using REG_xxx naming rule. */
/*  NOTE: DO NOT Remove these definition. Use later. */
#घोषणा	EFUSE_CTRL_8723B	REG_EFUSE_CTRL_8723B	/*  E-Fuse Control. */
#घोषणा	EFUSE_TEST_8723B	REG_EFUSE_TEST_8723B	/*  E-Fuse Test. */
#घोषणा	MSR_8723B		(REG_CR_8723B + 2)	/*  Media Status रेजिस्टर */
#घोषणा	ISR_8723B		REG_HISR0_8723B
#घोषणा	TSFR_8723B		REG_TSFTR_8723B		/*  Timing Sync Function Timer Register. */

#घोषणा PBP_8723B		REG_PBP_8723B

/*  Redअगरine MACID रेजिस्टर, to compatible prior ICs. */
#घोषणा	IDR0_8723B		REG_MACID_8723B		/*  MAC ID Register, Offset 0x0050-0x0053 */
#घोषणा	IDR4_8723B		(REG_MACID_8723B + 4)	/*  MAC ID Register, Offset 0x0054-0x0055 */

/*  9. Security Control Registers	(Offset:) */
#घोषणा	RWCAM_8723B		REG_CAMCMD_8723B	/* IN 8190 Data Sheet is called CAMcmd */
#घोषणा	WCAMI_8723B		REG_CAMWRITE_8723B	/*  Software ग_लिखो CAM input content */
#घोषणा	RCAMO_8723B		REG_CAMREAD_8723B	/*  Software पढ़ो/ग_लिखो CAM config */
#घोषणा	CAMDBG_8723B		REG_CAMDBG_8723B
#घोषणा	SECR_8723B		REG_SECCFG_8723B	/* Security Configuration Register */

/*        8195 IMR/ISR bits		(offset 0xB0,  8bits) */
#घोषणा	IMR_DISABLED_8723B		0
/*  IMR DW0(0x00B0-00B3) Bit 0-31 */
#घोषणा	IMR_TIMER2_8723B		BIT31	/*  Timeout पूर्णांकerrupt 2 */
#घोषणा	IMR_TIMER1_8723B		BIT30	/*  Timeout पूर्णांकerrupt 1 */
#घोषणा	IMR_PSTIMEOUT_8723B		BIT29	/*  Power Save Time Out Interrupt */
#घोषणा	IMR_GTINT4_8723B		BIT28	/*  When GTIMER4 expires, this bit is set to 1 */
#घोषणा	IMR_GTINT3_8723B		BIT27	/*  When GTIMER3 expires, this bit is set to 1 */
#घोषणा	IMR_TXBCN0ERR_8723B		BIT26	/*  Transmit Beacon0 Error */
#घोषणा	IMR_TXBCN0OK_8723B		BIT25	/*  Transmit Beacon0 OK */
#घोषणा	IMR_TSF_BIT32_TOGGLE_8723B	BIT24	/*  TSF Timer BIT32 toggle indication पूर्णांकerrupt */
#घोषणा	IMR_BCNDMAINT0_8723B		BIT20	/*  Beacon DMA Interrupt 0 */
#घोषणा	IMR_BCNDERR0_8723B		BIT16	/*  Beacon Queue DMA OK0 */
#घोषणा	IMR_HSISR_IND_ON_INT_8723B	BIT15	/*  HSISR Indicator (HSIMR & HSISR is true, this bit is set to 1) */
#घोषणा	IMR_BCNDMAINT_E_8723B		BIT14	/*  Beacon DMA Interrupt Extension क्रम Win7 */
#घोषणा	IMR_ATIMEND_8723B		BIT12	/*  CTWidnow End or ATIM Winकरोw End */
#घोषणा	IMR_C2HCMD_8723B		BIT10	/*  CPU to Host Command INT Status, Write 1 clear */
#घोषणा	IMR_CPWM2_8723B			BIT9	/*  CPU घातer Mode exchange INT Status, Write 1 clear */
#घोषणा	IMR_CPWM_8723B			BIT8	/*  CPU घातer Mode exchange INT Status, Write 1 clear */
#घोषणा	IMR_HIGHDOK_8723B		BIT7	/*  High Queue DMA OK */
#घोषणा	IMR_MGNTDOK_8723B		BIT6	/*  Management Queue DMA OK */
#घोषणा	IMR_BKDOK_8723B			BIT5	/*  AC_BK DMA OK */
#घोषणा	IMR_BEDOK_8723B			BIT4	/*  AC_BE DMA OK */
#घोषणा	IMR_VIDOK_8723B			BIT3	/*  AC_VI DMA OK */
#घोषणा	IMR_VODOK_8723B			BIT2	/*  AC_VO DMA OK */
#घोषणा	IMR_RDU_8723B			BIT1	/*  Rx Descriptor Unavailable */
#घोषणा	IMR_ROK_8723B			BIT0	/*  Receive DMA OK */

/*  IMR DW1(0x00B4-00B7) Bit 0-31 */
#घोषणा	IMR_BCNDMAINT7_8723B		BIT27	/*  Beacon DMA Interrupt 7 */
#घोषणा	IMR_BCNDMAINT6_8723B		BIT26	/*  Beacon DMA Interrupt 6 */
#घोषणा	IMR_BCNDMAINT5_8723B		BIT25	/*  Beacon DMA Interrupt 5 */
#घोषणा	IMR_BCNDMAINT4_8723B		BIT24	/*  Beacon DMA Interrupt 4 */
#घोषणा	IMR_BCNDMAINT3_8723B		BIT23	/*  Beacon DMA Interrupt 3 */
#घोषणा	IMR_BCNDMAINT2_8723B		BIT22	/*  Beacon DMA Interrupt 2 */
#घोषणा	IMR_BCNDMAINT1_8723B		BIT21	/*  Beacon DMA Interrupt 1 */
#घोषणा	IMR_BCNDOK7_8723B		BIT20	/*  Beacon Queue DMA OK Interrupt 7 */
#घोषणा	IMR_BCNDOK6_8723B		BIT19	/*  Beacon Queue DMA OK Interrupt 6 */
#घोषणा	IMR_BCNDOK5_8723B		BIT18	/*  Beacon Queue DMA OK Interrupt 5 */
#घोषणा	IMR_BCNDOK4_8723B		BIT17	/*  Beacon Queue DMA OK Interrupt 4 */
#घोषणा	IMR_BCNDOK3_8723B		BIT16	/*  Beacon Queue DMA OK Interrupt 3 */
#घोषणा	IMR_BCNDOK2_8723B		BIT15	/*  Beacon Queue DMA OK Interrupt 2 */
#घोषणा	IMR_BCNDOK1_8723B		BIT14	/*  Beacon Queue DMA OK Interrupt 1 */
#घोषणा	IMR_ATIMEND_E_8723B		BIT13	/*  ATIM Winकरोw End Extension क्रम Win7 */
#घोषणा	IMR_TXERR_8723B			BIT11	/*  Tx Error Flag Interrupt Status, ग_लिखो 1 clear. */
#घोषणा	IMR_RXERR_8723B			BIT10	/*  Rx Error Flag INT Status, Write 1 clear */
#घोषणा	IMR_TXFOVW_8723B		BIT9	/*  Transmit FIFO Overflow */
#घोषणा	IMR_RXFOVW_8723B		BIT8	/*  Receive FIFO Overflow */

/* 2 ACMHWCTRL 0x05C0 */
#घोषणा	ACMHW_HWEN_8723B		BIT(0)
#घोषणा	ACMHW_VOQEN_8723B		BIT(1)
#घोषणा	ACMHW_VIQEN_8723B		BIT(2)
#घोषणा	ACMHW_BEQEN_8723B		BIT(3)
#घोषणा	ACMHW_VOQSTATUS_8723B		BIT(5)
#घोषणा	ACMHW_VIQSTATUS_8723B		BIT(6)
#घोषणा	ACMHW_BEQSTATUS_8723B		BIT(7)

/*        8195 (RCR) Receive Configuration Register	(Offset 0x608, 32 bits) */
#घोषणा	RCR_TCPOFLD_EN			BIT25	/*  Enable TCP checksum offload */

#पूर्ण_अगर /*  #अगर_अघोषित __INC_HAL8723BREG_H */
