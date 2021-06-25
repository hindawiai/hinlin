<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 - 2017 Jes Sorensen <Jes.Sorensen@gmail.com>
 *
 * Register definitions taken from original Realtek rtl8723au driver
 */

/* 0x0000 ~ 0x00FF	System Configuration */
#घोषणा REG_SYS_ISO_CTRL		0x0000
#घोषणा  SYS_ISO_MD2PP			BIT(0)
#घोषणा  SYS_ISO_ANALOG_IPS		BIT(5)
#घोषणा  SYS_ISO_DIOR			BIT(9)
#घोषणा  SYS_ISO_PWC_EV25V		BIT(14)
#घोषणा  SYS_ISO_PWC_EV12V		BIT(15)

#घोषणा REG_SYS_FUNC			0x0002
#घोषणा  SYS_FUNC_BBRSTB		BIT(0)
#घोषणा  SYS_FUNC_BB_GLB_RSTN		BIT(1)
#घोषणा  SYS_FUNC_USBA			BIT(2)
#घोषणा  SYS_FUNC_UPLL			BIT(3)
#घोषणा  SYS_FUNC_USBD			BIT(4)
#घोषणा  SYS_FUNC_DIO_PCIE		BIT(5)
#घोषणा  SYS_FUNC_PCIEA			BIT(6)
#घोषणा  SYS_FUNC_PPLL			BIT(7)
#घोषणा  SYS_FUNC_PCIED			BIT(8)
#घोषणा  SYS_FUNC_DIOE			BIT(9)
#घोषणा  SYS_FUNC_CPU_ENABLE		BIT(10)
#घोषणा  SYS_FUNC_DCORE			BIT(11)
#घोषणा  SYS_FUNC_ELDR			BIT(12)
#घोषणा  SYS_FUNC_DIO_RF		BIT(13)
#घोषणा  SYS_FUNC_HWPDN			BIT(14)
#घोषणा  SYS_FUNC_MREGEN		BIT(15)

#घोषणा REG_APS_FSMCO			0x0004
#घोषणा  APS_FSMCO_PFM_ALDN		BIT(1)
#घोषणा  APS_FSMCO_PFM_WOWL		BIT(3)
#घोषणा  APS_FSMCO_ENABLE_POWERDOWN	BIT(4)
#घोषणा  APS_FSMCO_MAC_ENABLE		BIT(8)
#घोषणा  APS_FSMCO_MAC_OFF		BIT(9)
#घोषणा  APS_FSMCO_SW_LPS		BIT(10)
#घोषणा  APS_FSMCO_HW_SUSPEND		BIT(11)
#घोषणा  APS_FSMCO_PCIE			BIT(12)
#घोषणा  APS_FSMCO_HW_POWERDOWN		BIT(15)
#घोषणा  APS_FSMCO_WLON_RESET		BIT(16)

#घोषणा REG_SYS_CLKR			0x0008
#घोषणा  SYS_CLK_ANAD16V_ENABLE		BIT(0)
#घोषणा  SYS_CLK_ANA8M			BIT(1)
#घोषणा  SYS_CLK_MACSLP			BIT(4)
#घोषणा  SYS_CLK_LOADER_ENABLE		BIT(5)
#घोषणा  SYS_CLK_80M_SSC_DISABLE	BIT(7)
#घोषणा  SYS_CLK_80M_SSC_ENABLE_HO	BIT(8)
#घोषणा  SYS_CLK_PHY_SSC_RSTB		BIT(9)
#घोषणा  SYS_CLK_SEC_CLK_ENABLE		BIT(10)
#घोषणा  SYS_CLK_MAC_CLK_ENABLE		BIT(11)
#घोषणा  SYS_CLK_ENABLE			BIT(12)
#घोषणा  SYS_CLK_RING_CLK_ENABLE	BIT(13)

#घोषणा REG_9346CR			0x000a
#घोषणा  EEPROM_BOOT			BIT(4)
#घोषणा  EEPROM_ENABLE			BIT(5)

#घोषणा REG_EE_VPD			0x000c
#घोषणा REG_AFE_MISC			0x0010
#घोषणा  AFE_MISC_WL_XTAL_CTRL		BIT(6)

#घोषणा REG_SPS0_CTRL			0x0011
#घोषणा REG_SPS_OCP_CFG			0x0018
#घोषणा REG_8192E_LDOV12_CTRL		0x0014
#घोषणा REG_RSV_CTRL			0x001c

#घोषणा REG_RF_CTRL			0x001f
#घोषणा  RF_ENABLE			BIT(0)
#घोषणा  RF_RSTB			BIT(1)
#घोषणा  RF_SDMRSTB			BIT(2)

#घोषणा REG_LDOA15_CTRL			0x0020
#घोषणा  LDOA15_ENABLE			BIT(0)
#घोषणा  LDOA15_STANDBY			BIT(1)
#घोषणा  LDOA15_OBUF			BIT(2)
#घोषणा  LDOA15_REG_VOS			BIT(3)
#घोषणा  LDOA15_VOADJ_SHIFT		4

#घोषणा REG_LDOV12D_CTRL		0x0021
#घोषणा  LDOV12D_ENABLE			BIT(0)
#घोषणा  LDOV12D_STANDBY		BIT(1)
#घोषणा  LDOV12D_VADJ_SHIFT		4

#घोषणा REG_LDOHCI12_CTRL		0x0022

#घोषणा REG_LPLDO_CTRL			0x0023
#घोषणा  LPLDO_HSM			BIT(2)
#घोषणा  LPLDO_LSM_DIS			BIT(3)

#घोषणा REG_AFE_XTAL_CTRL		0x0024
#घोषणा  AFE_XTAL_ENABLE		BIT(0)
#घोषणा  AFE_XTAL_B_SELECT		BIT(1)
#घोषणा  AFE_XTAL_GATE_USB		BIT(8)
#घोषणा  AFE_XTAL_GATE_AFE		BIT(11)
#घोषणा  AFE_XTAL_RF_GATE		BIT(14)
#घोषणा  AFE_XTAL_GATE_DIG		BIT(17)
#घोषणा  AFE_XTAL_BT_GATE		BIT(20)

/*
 * 0x0028 is also known as REG_AFE_CTRL2 on 8723bu/8192eu
 */
#घोषणा REG_AFE_PLL_CTRL		0x0028
#घोषणा  AFE_PLL_ENABLE			BIT(0)
#घोषणा  AFE_PLL_320_ENABLE		BIT(1)
#घोषणा  APE_PLL_FREF_SELECT		BIT(2)
#घोषणा  AFE_PLL_EDGE_SELECT		BIT(3)
#घोषणा  AFE_PLL_WDOGB			BIT(4)
#घोषणा  AFE_PLL_LPF_ENABLE		BIT(5)

#घोषणा REG_MAC_PHY_CTRL		0x002c

#घोषणा REG_EFUSE_CTRL			0x0030
#घोषणा REG_EFUSE_TEST			0x0034
#घोषणा  EFUSE_TRPT			BIT(7)
	/*  00: Wअगरi Efuse, 01: BT Efuse0, 10: BT Efuse1, 11: BT Efuse2 */
#घोषणा  EFUSE_CELL_SEL			(BIT(8) | BIT(9))
#घोषणा  EFUSE_LDOE25_ENABLE		BIT(31)
#घोषणा  EFUSE_SELECT_MASK		0x0300
#घोषणा  EFUSE_WIFI_SELECT		0x0000
#घोषणा  EFUSE_BT0_SELECT		0x0100
#घोषणा  EFUSE_BT1_SELECT		0x0200
#घोषणा  EFUSE_BT2_SELECT		0x0300

#घोषणा  EFUSE_ACCESS_ENABLE		0x69	/* RTL8723 only */
#घोषणा  EFUSE_ACCESS_DISABLE		0x00	/* RTL8723 only */

#घोषणा REG_PWR_DATA			0x0038
#घोषणा  PWR_DATA_EEPRPAD_RFE_CTRL_EN	BIT(11)

#घोषणा REG_CAL_TIMER			0x003c
#घोषणा REG_ACLK_MON			0x003e
#घोषणा REG_GPIO_MUXCFG			0x0040
#घोषणा REG_GPIO_IO_SEL			0x0042
#घोषणा REG_MAC_PINMUX_CFG		0x0043
#घोषणा REG_GPIO_PIN_CTRL		0x0044
#घोषणा REG_GPIO_INTM			0x0048
#घोषणा  GPIO_INTM_EDGE_TRIG_IRQ	BIT(9)

#घोषणा REG_LEDCFG0			0x004c
#घोषणा  LEDCFG0_DPDT_SELECT		BIT(23)
#घोषणा REG_LEDCFG1			0x004d
#घोषणा REG_LEDCFG2			0x004e
#घोषणा  LEDCFG2_DPDT_SELECT		BIT(7)
#घोषणा REG_LEDCFG3			0x004f
#घोषणा REG_LEDCFG			REG_LEDCFG2
#घोषणा REG_FSIMR			0x0050
#घोषणा REG_FSISR			0x0054
#घोषणा REG_HSIMR			0x0058
#घोषणा REG_HSISR			0x005c
/*  RTL8723 WIFI/BT/GPS Multi-Function GPIO Pin Control. */
#घोषणा REG_GPIO_PIN_CTRL_2		0x0060
/*  RTL8723 WIFI/BT/GPS Multi-Function GPIO Select. */
#घोषणा REG_GPIO_IO_SEL_2		0x0062
#घोषणा  GPIO_IO_SEL_2_GPIO09_INPUT	BIT(1)
#घोषणा  GPIO_IO_SEL_2_GPIO09_IRQ	BIT(9)

/*  RTL8723B */
#घोषणा REG_PAD_CTRL1			0x0064
#घोषणा  PAD_CTRL1_SW_DPDT_SEL_DATA	BIT(0)

/*  RTL8723 only WIFI/BT/GPS Multi-Function control source. */
#घोषणा REG_MULTI_FUNC_CTRL		0x0068

#घोषणा  MULTI_FN_WIFI_HW_PWRDOWN_EN	BIT(0)	/* Enable GPIO[9] as WiFi HW
						   घातerकरोwn source */
#घोषणा  MULTI_FN_WIFI_HW_PWRDOWN_SL	BIT(1)	/* WiFi HW घातerकरोwn polarity
						   control */
#घोषणा  MULTI_WIFI_FUNC_EN		BIT(2)	/* WiFi function enable */

#घोषणा  MULTI_WIFI_HW_ROF_EN		BIT(3)	/* Enable GPIO[9] as WiFi RF HW
						   घातerकरोwn source */
#घोषणा  MULTI_BT_HW_PWRDOWN_EN		BIT(16)	/* Enable GPIO[11] as BT HW
						   घातerकरोwn source */
#घोषणा  MULTI_BT_HW_PWRDOWN_SL		BIT(17)	/* BT HW घातerकरोwn polarity
						   control */
#घोषणा  MULTI_BT_FUNC_EN		BIT(18)	/* BT function enable */
#घोषणा  MULTI_BT_HW_ROF_EN		BIT(19)	/* Enable GPIO[11] as BT/GPS
						   RF HW घातerकरोwn source */
#घोषणा  MULTI_GPS_HW_PWRDOWN_EN	BIT(20)	/* Enable GPIO[10] as GPS HW
						   घातerकरोwn source */
#घोषणा  MULTI_GPS_HW_PWRDOWN_SL	BIT(21)	/* GPS HW घातerकरोwn polarity
						   control */
#घोषणा  MULTI_GPS_FUNC_EN		BIT(22)	/* GPS function enable */

#घोषणा REG_AFE_CTRL4			0x0078	/* 8192eu/8723bu */
#घोषणा REG_LDO_SW_CTRL			0x007c	/* 8192eu */

#घोषणा REG_MCU_FW_DL			0x0080
#घोषणा  MCU_FW_DL_ENABLE		BIT(0)
#घोषणा  MCU_FW_DL_READY		BIT(1)
#घोषणा  MCU_FW_DL_CSUM_REPORT		BIT(2)
#घोषणा  MCU_MAC_INIT_READY		BIT(3)
#घोषणा  MCU_BB_INIT_READY		BIT(4)
#घोषणा  MCU_RF_INIT_READY		BIT(5)
#घोषणा  MCU_WINT_INIT_READY		BIT(6)
#घोषणा  MCU_FW_RAM_SEL			BIT(7)	/* 1: RAM, 0:ROM */
#घोषणा  MCU_CP_RESET			BIT(23)

#घोषणा REG_HMBOX_EXT_0			0x0088
#घोषणा REG_HMBOX_EXT_1			0x008a
#घोषणा REG_HMBOX_EXT_2			0x008c
#घोषणा REG_HMBOX_EXT_3			0x008e

/* Interrupt रेजिस्टरs क्रम 8192e/8723bu/8812 */
#घोषणा REG_HIMR0			0x00b0
#घोषणा	 IMR0_TXCCK			BIT(30)	/* TXRPT पूर्णांकerrupt when CCX bit
						   of the packet is set */
#घोषणा	 IMR0_PSTIMEOUT			BIT(29)	/* Power Save Time Out Int */
#घोषणा	 IMR0_GTINT4			BIT(28)	/* Set when GTIMER4 expires */
#घोषणा	 IMR0_GTINT3			BIT(27)	/* Set when GTIMER3 expires */
#घोषणा	 IMR0_TBDER			BIT(26)	/* Transmit Beacon0 Error */
#घोषणा	 IMR0_TBDOK			BIT(25)	/* Transmit Beacon0 OK */
#घोषणा	 IMR0_TSF_BIT32_TOGGLE		BIT(24)	/* TSF Timer BIT32 toggle
						   indication पूर्णांकerrupt */
#घोषणा	 IMR0_BCNDMAINT0		BIT(20)	/* Beacon DMA Interrupt 0 */
#घोषणा	 IMR0_BCNDERR0			BIT(16)	/* Beacon Queue DMA Error 0 */
#घोषणा	 IMR0_HSISR_IND_ON_INT		BIT(15)	/* HSISR Indicator (HSIMR &
						   HSISR is true) */
#घोषणा	 IMR0_BCNDMAINT_E		BIT(14)	/* Beacon DMA Interrupt
						   Extension क्रम Win7 */
#घोषणा	 IMR0_ATIMEND			BIT(12)	/* CTWidnow End or
						   ATIM Winकरोw End */
#घोषणा	 IMR0_HISR1_IND_INT		BIT(11)	/* HISR1 Indicator
						   (HISR1 & HIMR1 is true) */
#घोषणा	 IMR0_C2HCMD			BIT(10)	/* CPU to Host Command INT
						   Status, Write 1 to clear */
#घोषणा	 IMR0_CPWM2			BIT(9)	/* CPU घातer Mode exchange INT
						   Status, Write 1 to clear */
#घोषणा	 IMR0_CPWM			BIT(8)	/* CPU घातer Mode exchange INT
						   Status, Write 1 to clear */
#घोषणा	 IMR0_HIGHDOK			BIT(7)	/* High Queue DMA OK */
#घोषणा	 IMR0_MGNTDOK			BIT(6)	/* Management Queue DMA OK */
#घोषणा	 IMR0_BKDOK			BIT(5)	/* AC_BK DMA OK */
#घोषणा	 IMR0_BEDOK			BIT(4)	/* AC_BE DMA OK */
#घोषणा	 IMR0_VIDOK			BIT(3)	/* AC_VI DMA OK */
#घोषणा	 IMR0_VODOK			BIT(2)	/* AC_VO DMA OK */
#घोषणा	 IMR0_RDU			BIT(1)	/* Rx Descriptor Unavailable */
#घोषणा	 IMR0_ROK			BIT(0)	/* Receive DMA OK */
#घोषणा REG_HISR0			0x00b4
#घोषणा REG_HIMR1			0x00b8
#घोषणा	 IMR1_BCNDMAINT7		BIT(27)	/* Beacon DMA Interrupt 7 */
#घोषणा	 IMR1_BCNDMAINT6		BIT(26)	/* Beacon DMA Interrupt 6 */
#घोषणा	 IMR1_BCNDMAINT5		BIT(25)	/* Beacon DMA Interrupt 5 */
#घोषणा	 IMR1_BCNDMAINT4		BIT(24)	/* Beacon DMA Interrupt 4 */
#घोषणा	 IMR1_BCNDMAINT3		BIT(23)	/* Beacon DMA Interrupt 3 */
#घोषणा	 IMR1_BCNDMAINT2		BIT(22)	/* Beacon DMA Interrupt 2 */
#घोषणा	 IMR1_BCNDMAINT1		BIT(21)	/* Beacon DMA Interrupt 1 */
#घोषणा	 IMR1_BCNDERR7			BIT(20)	/* Beacon Queue DMA Err Int 7 */
#घोषणा	 IMR1_BCNDERR6			BIT(19)	/* Beacon Queue DMA Err Int 6 */
#घोषणा	 IMR1_BCNDERR5			BIT(18)	/* Beacon Queue DMA Err Int 5 */
#घोषणा	 IMR1_BCNDERR4			BIT(17)	/* Beacon Queue DMA Err Int 4 */
#घोषणा	 IMR1_BCNDERR3			BIT(16)	/* Beacon Queue DMA Err Int 3 */
#घोषणा	 IMR1_BCNDERR2			BIT(15)	/* Beacon Queue DMA Err Int 2 */
#घोषणा	 IMR1_BCNDERR1			BIT(14)	/* Beacon Queue DMA Err Int 1 */
#घोषणा	 IMR1_ATIMEND_E			BIT(13)	/* ATIM Winकरोw End Extension
						   क्रम Win7 */
#घोषणा	 IMR1_TXERR			BIT(11)	/* Tx Error Flag Int Status,
						   ग_लिखो 1 to clear */
#घोषणा	 IMR1_RXERR			BIT(10)	/* Rx Error Flag Int Status,
						   ग_लिखो 1 to clear */
#घोषणा	 IMR1_TXFOVW			BIT(9)	/* Transmit FIFO Overflow */
#घोषणा	 IMR1_RXFOVW			BIT(8)	/* Receive FIFO Overflow */
#घोषणा REG_HISR1			0x00bc

/*  Host suspend counter on FPGA platक्रमm */
#घोषणा REG_HOST_SUSP_CNT		0x00bc
/*  Efuse access protection क्रम RTL8723 */
#घोषणा REG_EFUSE_ACCESS		0x00cf
#घोषणा REG_BIST_SCAN			0x00d0
#घोषणा REG_BIST_RPT			0x00d4
#घोषणा REG_BIST_ROM_RPT		0x00d8
#घोषणा REG_USB_SIE_INTF		0x00e0
#घोषणा REG_PCIE_MIO_INTF		0x00e4
#घोषणा REG_PCIE_MIO_INTD		0x00e8
#घोषणा REG_HPON_FSM			0x00ec
#घोषणा  HPON_FSM_BONDING_MASK		(BIT(22) | BIT(23))
#घोषणा  HPON_FSM_BONDING_1T2R		BIT(22)
#घोषणा REG_SYS_CFG			0x00f0
#घोषणा  SYS_CFG_XCLK_VLD		BIT(0)
#घोषणा  SYS_CFG_ACLK_VLD		BIT(1)
#घोषणा  SYS_CFG_UCLK_VLD		BIT(2)
#घोषणा  SYS_CFG_PCLK_VLD		BIT(3)
#घोषणा  SYS_CFG_PCIRSTB		BIT(4)
#घोषणा  SYS_CFG_V15_VLD		BIT(5)
#घोषणा  SYS_CFG_TRP_B15V_EN		BIT(7)
#घोषणा  SYS_CFG_SW_OFFLOAD_EN		BIT(7)	/* For chips with IOL support */
#घोषणा  SYS_CFG_SIC_IDLE		BIT(8)
#घोषणा  SYS_CFG_BD_MAC2		BIT(9)
#घोषणा  SYS_CFG_BD_MAC1		BIT(10)
#घोषणा  SYS_CFG_IC_MACPHY_MODE		BIT(11)
#घोषणा  SYS_CFG_CHIP_VER		(BIT(12) | BIT(13) | BIT(14) | BIT(15))
#घोषणा  SYS_CFG_BT_FUNC		BIT(16)
#घोषणा  SYS_CFG_VENDOR_ID		BIT(19)
#घोषणा  SYS_CFG_VENDOR_EXT_MASK	(BIT(18) | BIT(19))
#घोषणा   SYS_CFG_VENDOR_ID_TSMC	0
#घोषणा   SYS_CFG_VENDOR_ID_SMIC	BIT(18)
#घोषणा   SYS_CFG_VENDOR_ID_UMC		BIT(19)
#घोषणा  SYS_CFG_PAD_HWPD_IDN		BIT(22)
#घोषणा  SYS_CFG_TRP_VAUX_EN		BIT(23)
#घोषणा  SYS_CFG_TRP_BT_EN		BIT(24)
#घोषणा  SYS_CFG_SPS_LDO_SEL		BIT(24)	/* 8192eu */
#घोषणा  SYS_CFG_BD_PKG_SEL		BIT(25)
#घोषणा  SYS_CFG_BD_HCI_SEL		BIT(26)
#घोषणा  SYS_CFG_TYPE_ID		BIT(27)
#घोषणा  SYS_CFG_RTL_ID			BIT(23) /*  TestChip ID,
						    1:Test(RLE); 0:MP(RL) */
#घोषणा  SYS_CFG_SPS_SEL		BIT(24) /*  1:LDO regulator mode;
						    0:Switching regulator mode*/
#घोषणा  SYS_CFG_CHIP_VERSION_MASK	0xf000	/* Bit 12 - 15 */
#घोषणा  SYS_CFG_CHIP_VERSION_SHIFT	12

#घोषणा REG_GPIO_OUTSTS			0x00f4	/*  For RTL8723 only. */
#घोषणा  GPIO_EFS_HCI_SEL		(BIT(0) | BIT(1))
#घोषणा  GPIO_PAD_HCI_SEL		(BIT(2) | BIT(3))
#घोषणा  GPIO_HCI_SEL			(BIT(4) | BIT(5))
#घोषणा  GPIO_PKG_SEL_HCI		BIT(6)
#घोषणा  GPIO_FEN_GPS			BIT(7)
#घोषणा  GPIO_FEN_BT			BIT(8)
#घोषणा  GPIO_FEN_WL			BIT(9)
#घोषणा  GPIO_FEN_PCI			BIT(10)
#घोषणा  GPIO_FEN_USB			BIT(11)
#घोषणा  GPIO_BTRF_HWPDN_N		BIT(12)
#घोषणा  GPIO_WLRF_HWPDN_N		BIT(13)
#घोषणा  GPIO_PDN_BT_N			BIT(14)
#घोषणा  GPIO_PDN_GPS_N			BIT(15)
#घोषणा  GPIO_BT_CTL_HWPDN		BIT(16)
#घोषणा  GPIO_GPS_CTL_HWPDN		BIT(17)
#घोषणा  GPIO_PPHY_SUSB			BIT(20)
#घोषणा  GPIO_UPHY_SUSB			BIT(21)
#घोषणा  GPIO_PCI_SUSEN			BIT(22)
#घोषणा  GPIO_USB_SUSEN			BIT(23)
#घोषणा  GPIO_RF_RL_ID			(BIT(31) | BIT(30) | BIT(29) | BIT(28))

#घोषणा REG_SYS_CFG2			0x00fc	/* 8192eu */

/* 0x0100 ~ 0x01FF	MACTOP General Configuration */
#घोषणा REG_CR				0x0100
#घोषणा  CR_HCI_TXDMA_ENABLE		BIT(0)
#घोषणा  CR_HCI_RXDMA_ENABLE		BIT(1)
#घोषणा  CR_TXDMA_ENABLE		BIT(2)
#घोषणा  CR_RXDMA_ENABLE		BIT(3)
#घोषणा  CR_PROTOCOL_ENABLE		BIT(4)
#घोषणा  CR_SCHEDULE_ENABLE		BIT(5)
#घोषणा  CR_MAC_TX_ENABLE		BIT(6)
#घोषणा  CR_MAC_RX_ENABLE		BIT(7)
#घोषणा  CR_SW_BEACON_ENABLE		BIT(8)
#घोषणा  CR_SECURITY_ENABLE		BIT(9)
#घोषणा  CR_CALTIMER_ENABLE		BIT(10)

/* Media Status Register */
#घोषणा REG_MSR				0x0102
#घोषणा  MSR_LINKTYPE_MASK		0x3
#घोषणा  MSR_LINKTYPE_NONE		0x0
#घोषणा  MSR_LINKTYPE_ADHOC		0x1
#घोषणा  MSR_LINKTYPE_STATION		0x2
#घोषणा  MSR_LINKTYPE_AP		0x3

#घोषणा REG_PBP				0x0104
#घोषणा  PBP_PAGE_SIZE_RX_SHIFT		0
#घोषणा  PBP_PAGE_SIZE_TX_SHIFT		4
#घोषणा  PBP_PAGE_SIZE_64		0x0
#घोषणा  PBP_PAGE_SIZE_128		0x1
#घोषणा  PBP_PAGE_SIZE_256		0x2
#घोषणा  PBP_PAGE_SIZE_512		0x3
#घोषणा  PBP_PAGE_SIZE_1024		0x4

#घोषणा REG_TRXDMA_CTRL			0x010c
#घोषणा  TRXDMA_CTRL_RXDMA_AGG_EN	BIT(2)
#घोषणा  TRXDMA_CTRL_VOQ_SHIFT		4
#घोषणा  TRXDMA_CTRL_VIQ_SHIFT		6
#घोषणा  TRXDMA_CTRL_BEQ_SHIFT		8
#घोषणा  TRXDMA_CTRL_BKQ_SHIFT		10
#घोषणा  TRXDMA_CTRL_MGQ_SHIFT		12
#घोषणा  TRXDMA_CTRL_HIQ_SHIFT		14
#घोषणा  TRXDMA_QUEUE_LOW		1
#घोषणा  TRXDMA_QUEUE_NORMAL		2
#घोषणा  TRXDMA_QUEUE_HIGH		3

#घोषणा REG_TRXFF_BNDY			0x0114
#घोषणा REG_TRXFF_STATUS		0x0118
#घोषणा REG_RXFF_PTR			0x011c
#घोषणा REG_HIMR			0x0120
#घोषणा REG_HISR			0x0124
#घोषणा REG_HIMRE			0x0128
#घोषणा REG_HISRE			0x012c
#घोषणा REG_CPWM			0x012f
#घोषणा REG_FWIMR			0x0130
#घोषणा REG_FWISR			0x0134
#घोषणा REG_PKTBUF_DBG_CTRL		0x0140
#घोषणा REG_PKTBUF_DBG_DATA_L		0x0144
#घोषणा REG_PKTBUF_DBG_DATA_H		0x0148

#घोषणा REG_TC0_CTRL			0x0150
#घोषणा REG_TC1_CTRL			0x0154
#घोषणा REG_TC2_CTRL			0x0158
#घोषणा REG_TC3_CTRL			0x015c
#घोषणा REG_TC4_CTRL			0x0160
#घोषणा REG_TCUNIT_BASE			0x0164
#घोषणा REG_MBIST_START			0x0174
#घोषणा REG_MBIST_DONE			0x0178
#घोषणा REG_MBIST_FAIL			0x017c
#घोषणा REG_C2HEVT_MSG_NORMAL		0x01a0
/* 8192EU/8723BU/8812 */
#घोषणा REG_C2HEVT_CMD_ID_8723B		0x01ae
#घोषणा REG_C2HEVT_CLEAR		0x01af
#घोषणा REG_C2HEVT_MSG_TEST		0x01b8
#घोषणा REG_MCUTST_1			0x01c0
#घोषणा REG_FMTHR			0x01c8
#घोषणा REG_HMTFR			0x01cc
#घोषणा REG_HMBOX_0			0x01d0
#घोषणा REG_HMBOX_1			0x01d4
#घोषणा REG_HMBOX_2			0x01d8
#घोषणा REG_HMBOX_3			0x01dc

#घोषणा REG_LLT_INIT			0x01e0
#घोषणा  LLT_OP_INACTIVE		0x0
#घोषणा  LLT_OP_WRITE			(0x1 << 30)
#घोषणा  LLT_OP_READ			(0x2 << 30)
#घोषणा  LLT_OP_MASK			(0x3 << 30)

#घोषणा REG_BB_ACCEESS_CTRL		0x01e8
#घोषणा REG_BB_ACCESS_DATA		0x01ec

#घोषणा REG_HMBOX_EXT0_8723B		0x01f0
#घोषणा REG_HMBOX_EXT1_8723B		0x01f4
#घोषणा REG_HMBOX_EXT2_8723B		0x01f8
#घोषणा REG_HMBOX_EXT3_8723B		0x01fc

/* 0x0200 ~ 0x027F	TXDMA Configuration */
#घोषणा REG_RQPN			0x0200
#घोषणा  RQPN_HI_PQ_SHIFT		0
#घोषणा  RQPN_LO_PQ_SHIFT		8
#घोषणा  RQPN_PUB_PQ_SHIFT		16
#घोषणा  RQPN_LOAD			BIT(31)

#घोषणा REG_FIFOPAGE			0x0204
#घोषणा REG_TDECTRL			0x0208
#घोषणा REG_TXDMA_OFFSET_CHK		0x020c
#घोषणा  TXDMA_OFFSET_DROP_DATA_EN	BIT(9)
#घोषणा REG_TXDMA_STATUS		0x0210
#घोषणा REG_RQPN_NPQ			0x0214
#घोषणा  RQPN_NPQ_SHIFT			0
#घोषणा  RQPN_EPQ_SHIFT			16

#घोषणा REG_AUTO_LLT			0x0224
#घोषणा  AUTO_LLT_INIT_LLT		BIT(16)

#घोषणा REG_DWBCN1_CTRL_8723B		0x0228

/* 0x0280 ~ 0x02FF	RXDMA Configuration */
#घोषणा REG_RXDMA_AGG_PG_TH		0x0280	/* 0-7 : USB DMA size bits
						   8-14: USB DMA समयout
						   15  : Aggregation enable
						         Only seems to be used
							 on 8723bu/8192eu */
#घोषणा  RXDMA_USB_AGG_ENABLE		BIT(31)
#घोषणा REG_RXPKT_NUM			0x0284
#घोषणा  RXPKT_NUM_RXDMA_IDLE		BIT(17)
#घोषणा  RXPKT_NUM_RW_RELEASE_EN	BIT(18)
#घोषणा REG_RXDMA_STATUS		0x0288

/* Presumably only found on newer chips such as 8723bu */
#घोषणा REG_RX_DMA_CTRL_8723B		0x0286
#घोषणा REG_RXDMA_PRO_8723B		0x0290

#घोषणा REG_RF_BB_CMD_ADDR		0x02c0
#घोषणा REG_RF_BB_CMD_DATA		0x02c4

/*  spec version 11 */
/* 0x0400 ~ 0x047F	Protocol Configuration */
/* 8192c, 8192d */
#घोषणा REG_VOQ_INFO			0x0400
#घोषणा REG_VIQ_INFO			0x0404
#घोषणा REG_BEQ_INFO			0x0408
#घोषणा REG_BKQ_INFO			0x040c
/* 8188e, 8723a, 8812a, 8821a, 8192e, 8723b */
#घोषणा REG_Q0_INFO			0x400
#घोषणा REG_Q1_INFO			0x404
#घोषणा REG_Q2_INFO			0x408
#घोषणा REG_Q3_INFO			0x40c

#घोषणा REG_MGQ_INFO			0x0410
#घोषणा REG_HGQ_INFO			0x0414
#घोषणा REG_BCNQ_INFO			0x0418

#घोषणा REG_CPU_MGQ_INFORMATION		0x041c
#घोषणा REG_FWHW_TXQ_CTRL		0x0420
#घोषणा  FWHW_TXQ_CTRL_AMPDU_RETRY	BIT(7)
#घोषणा  FWHW_TXQ_CTRL_XMIT_MGMT_ACK	BIT(12)

#घोषणा REG_HWSEQ_CTRL			0x0423
#घोषणा REG_TXPKTBUF_BCNQ_BDNY		0x0424
#घोषणा REG_TXPKTBUF_MGQ_BDNY		0x0425
#घोषणा REG_LIFETIME_EN			0x0426
#घोषणा REG_MULTI_BCNQ_OFFSET		0x0427

#घोषणा REG_SPEC_SIFS			0x0428
#घोषणा  SPEC_SIFS_CCK_MASK		0x00ff
#घोषणा  SPEC_SIFS_CCK_SHIFT		0
#घोषणा  SPEC_SIFS_OFDM_MASK		0xff00
#घोषणा  SPEC_SIFS_OFDM_SHIFT		8

#घोषणा REG_RETRY_LIMIT			0x042a
#घोषणा  RETRY_LIMIT_LONG_SHIFT		0
#घोषणा  RETRY_LIMIT_LONG_MASK		0x003f
#घोषणा  RETRY_LIMIT_SHORT_SHIFT	8
#घोषणा  RETRY_LIMIT_SHORT_MASK		0x3f00

#घोषणा REG_DARFRC			0x0430
#घोषणा REG_RARFRC			0x0438
#घोषणा REG_RESPONSE_RATE_SET		0x0440
#घोषणा  RESPONSE_RATE_BITMAP_ALL	0xfffff
#घोषणा  RESPONSE_RATE_RRSR_CCK_ONLY_1M	0xffff1
#घोषणा  RSR_1M				BIT(0)
#घोषणा  RSR_2M				BIT(1)
#घोषणा  RSR_5_5M			BIT(2)
#घोषणा  RSR_11M			BIT(3)
#घोषणा  RSR_6M				BIT(4)
#घोषणा  RSR_9M				BIT(5)
#घोषणा  RSR_12M			BIT(6)
#घोषणा  RSR_18M			BIT(7)
#घोषणा  RSR_24M			BIT(8)
#घोषणा  RSR_36M			BIT(9)
#घोषणा  RSR_48M			BIT(10)
#घोषणा  RSR_54M			BIT(11)
#घोषणा  RSR_MCS0			BIT(12)
#घोषणा  RSR_MCS1			BIT(13)
#घोषणा  RSR_MCS2			BIT(14)
#घोषणा  RSR_MCS3			BIT(15)
#घोषणा  RSR_MCS4			BIT(16)
#घोषणा  RSR_MCS5			BIT(17)
#घोषणा  RSR_MCS6			BIT(18)
#घोषणा  RSR_MCS7			BIT(19)
#घोषणा  RSR_RSC_LOWER_SUB_CHANNEL	BIT(21)	/* 0x200000 */
#घोषणा  RSR_RSC_UPPER_SUB_CHANNEL	BIT(22)	/* 0x400000 */
#घोषणा  RSR_RSC_BANDWIDTH_40M		(RSR_RSC_UPPER_SUB_CHANNEL | \
					 RSR_RSC_LOWER_SUB_CHANNEL)
#घोषणा  RSR_ACK_SHORT_PREAMBLE		BIT(23)

#घोषणा REG_ARFR0			0x0444
#घोषणा REG_ARFR1			0x0448
#घोषणा REG_ARFR2			0x044c
#घोषणा REG_ARFR3			0x0450
#घोषणा REG_AMPDU_MAX_TIME_8723B	0x0456
#घोषणा REG_AGGLEN_LMT			0x0458
#घोषणा REG_AMPDU_MIN_SPACE		0x045c
#घोषणा REG_TXPKTBUF_WMAC_LBK_BF_HD	0x045d
#घोषणा REG_FAST_EDCA_CTRL		0x0460
#घोषणा REG_RD_RESP_PKT_TH		0x0463
#घोषणा REG_INIRTS_RATE_SEL		0x0480
/* 8723bu */
#घोषणा REG_DATA_SUBCHANNEL		0x0483
/* 8723au */
#घोषणा REG_INIDATA_RATE_SEL		0x0484
/* MACID_SLEEP_1/3 क्रम 8723b, 8192e, 8812a, 8821a */
#घोषणा REG_MACID_SLEEP_3_8732B		0x0484
#घोषणा REG_MACID_SLEEP_1_8732B		0x0488

#घोषणा REG_POWER_STATUS		0x04a4
#घोषणा REG_POWER_STAGE1		0x04b4
#घोषणा REG_POWER_STAGE2		0x04b8
#घोषणा REG_AMPDU_BURST_MODE_8723B	0x04bc
#घोषणा REG_PKT_VO_VI_LIFE_TIME		0x04c0
#घोषणा REG_PKT_BE_BK_LIFE_TIME		0x04c2
#घोषणा REG_STBC_SETTING		0x04c4
#घोषणा REG_QUEUE_CTRL			0x04c6
#घोषणा REG_HT_SINGLE_AMPDU_8723B	0x04c7
#घोषणा REG_PROT_MODE_CTRL		0x04c8
#घोषणा REG_MAX_AGGR_NUM		0x04ca
#घोषणा REG_RTS_MAX_AGGR_NUM		0x04cb
#घोषणा REG_BAR_MODE_CTRL		0x04cc
#घोषणा REG_RA_TRY_RATE_AGG_LMT		0x04cf
/* MACID_DROP क्रम 8723a */
#घोषणा REG_MACID_DROP_8732A		0x04d0
/* EARLY_MODE_CONTROL 8188e */
#घोषणा REG_EARLY_MODE_CONTROL_8188E	0x04d0
/* MACID_SLEEP_2 क्रम 8723b, 8192e, 8812a, 8821a */
#घोषणा REG_MACID_SLEEP_2_8732B		0x04d0
#घोषणा REG_MACID_SLEEP			0x04d4
#घोषणा REG_NQOS_SEQ			0x04dc
#घोषणा REG_QOS_SEQ			0x04de
#घोषणा REG_NEED_CPU_HANDLE		0x04e0
#घोषणा REG_PKT_LOSE_RPT		0x04e1
#घोषणा REG_PTCL_ERR_STATUS		0x04e2
#घोषणा REG_TX_REPORT_CTRL		0x04ec
#घोषणा  TX_REPORT_CTRL_TIMER_ENABLE	BIT(1)

#घोषणा REG_TX_REPORT_TIME		0x04f0
#घोषणा REG_DUMMY			0x04fc

/* 0x0500 ~ 0x05FF	EDCA Configuration */
#घोषणा REG_EDCA_VO_PARAM		0x0500
#घोषणा REG_EDCA_VI_PARAM		0x0504
#घोषणा REG_EDCA_BE_PARAM		0x0508
#घोषणा REG_EDCA_BK_PARAM		0x050c
#घोषणा  EDCA_PARAM_ECW_MIN_SHIFT	8
#घोषणा  EDCA_PARAM_ECW_MAX_SHIFT	12
#घोषणा  EDCA_PARAM_TXOP_SHIFT		16
#घोषणा REG_BEACON_TCFG			0x0510
#घोषणा REG_PIFS			0x0512
#घोषणा REG_RDG_PIFS			0x0513
#घोषणा REG_SIFS_CCK			0x0514
#घोषणा REG_SIFS_OFDM			0x0516
#घोषणा REG_TSFTR_SYN_OFFSET		0x0518
#घोषणा REG_AGGR_BREAK_TIME		0x051a
#घोषणा REG_SLOT			0x051b
#घोषणा REG_TX_PTCL_CTRL		0x0520
#घोषणा REG_TXPAUSE			0x0522
#घोषणा REG_DIS_TXREQ_CLR		0x0523
#घोषणा REG_RD_CTRL			0x0524
#घोषणा REG_TBTT_PROHIBIT		0x0540
#घोषणा REG_RD_NAV_NXT			0x0544
#घोषणा REG_NAV_PROT_LEN		0x0546

#घोषणा REG_BEACON_CTRL			0x0550
#घोषणा REG_BEACON_CTRL_1		0x0551
#घोषणा  BEACON_ATIM			BIT(0)
#घोषणा  BEACON_CTRL_MBSSID		BIT(1)
#घोषणा  BEACON_CTRL_TX_BEACON_RPT	BIT(2)
#घोषणा  BEACON_FUNCTION_ENABLE		BIT(3)
#घोषणा  BEACON_DISABLE_TSF_UPDATE	BIT(4)

#घोषणा REG_MBID_NUM			0x0552
#घोषणा REG_DUAL_TSF_RST		0x0553
#घोषणा  DUAL_TSF_RESET_TSF0		BIT(0)
#घोषणा  DUAL_TSF_RESET_TSF1		BIT(1)
#घोषणा  DUAL_TSF_RESET_P2P		BIT(4)
#घोषणा  DUAL_TSF_TX_OK			BIT(5)

/*  The same as REG_MBSSID_BCN_SPACE */
#घोषणा REG_BCN_INTERVAL		0x0554
#घोषणा REG_MBSSID_BCN_SPACE		0x0554

#घोषणा REG_DRIVER_EARLY_INT		0x0558
#घोषणा  DRIVER_EARLY_INT_TIME		5

#घोषणा REG_BEACON_DMA_TIME		0x0559
#घोषणा  BEACON_DMA_ATIME_INT_TIME	2

#घोषणा REG_ATIMWND			0x055a
#घोषणा REG_USTIME_TSF_8723B		0x055c
#घोषणा REG_BCN_MAX_ERR			0x055d
#घोषणा REG_RXTSF_OFFSET_CCK		0x055e
#घोषणा REG_RXTSF_OFFSET_OFDM		0x055f
#घोषणा REG_TSFTR			0x0560
#घोषणा REG_TSFTR1			0x0568
#घोषणा REG_INIT_TSFTR			0x0564
#घोषणा REG_ATIMWND_1			0x0570
#घोषणा REG_PSTIMER			0x0580
#घोषणा REG_TIMER0			0x0584
#घोषणा REG_TIMER1			0x0588
#घोषणा REG_ACM_HW_CTRL			0x05c0
#घोषणा  ACM_HW_CTRL_BK			BIT(0)
#घोषणा  ACM_HW_CTRL_BE			BIT(1)
#घोषणा  ACM_HW_CTRL_VI			BIT(2)
#घोषणा  ACM_HW_CTRL_VO			BIT(3)
#घोषणा REG_ACM_RST_CTRL		0x05c1
#घोषणा REG_ACMAVG			0x05c2
#घोषणा REG_VO_ADMTIME			0x05c4
#घोषणा REG_VI_ADMTIME			0x05c6
#घोषणा REG_BE_ADMTIME			0x05c8
#घोषणा REG_EDCA_RANDOM_GEN		0x05cc
#घोषणा REG_SCH_TXCMD			0x05d0

/* define REG_FW_TSF_SYNC_CNT		0x04a0 */
#घोषणा REG_SCH_TX_CMD			0x05f8
#घोषणा REG_FW_RESET_TSF_CNT_1		0x05fc
#घोषणा REG_FW_RESET_TSF_CNT_0		0x05fd
#घोषणा REG_FW_BCN_DIS_CNT		0x05fe

/* 0x0600 ~ 0x07FF  WMAC Configuration */
#घोषणा REG_APSD_CTRL			0x0600
#घोषणा  APSD_CTRL_OFF			BIT(6)
#घोषणा  APSD_CTRL_OFF_STATUS		BIT(7)
#घोषणा REG_BW_OPMODE			0x0603
#घोषणा  BW_OPMODE_20MHZ		BIT(2)
#घोषणा  BW_OPMODE_5G			BIT(1)
#घोषणा  BW_OPMODE_11J			BIT(0)

#घोषणा REG_TCR				0x0604

/* Receive Configuration Register */
#घोषणा REG_RCR				0x0608
#घोषणा  RCR_ACCEPT_AP			BIT(0)  /* Accept all unicast packet */
#घोषणा  RCR_ACCEPT_PHYS_MATCH		BIT(1)  /* Accept phys match packet */
#घोषणा  RCR_ACCEPT_MCAST		BIT(2)
#घोषणा  RCR_ACCEPT_BCAST		BIT(3)
#घोषणा  RCR_ACCEPT_ADDR3		BIT(4)  /* Accept address 3 match
						 packet */
#घोषणा  RCR_ACCEPT_PM			BIT(5)  /* Accept घातer management
						 packet */
#घोषणा  RCR_CHECK_BSSID_MATCH		BIT(6)  /* Accept BSSID match packet */
#घोषणा  RCR_CHECK_BSSID_BEACON		BIT(7)  /* Accept BSSID match packet
						 (Rx beacon, probe rsp) */
#घोषणा  RCR_ACCEPT_CRC32		BIT(8)  /* Accept CRC32 error packet */
#घोषणा  RCR_ACCEPT_ICV			BIT(9)  /* Accept ICV error packet */
#घोषणा  RCR_ACCEPT_DATA_FRAME		BIT(11) /* Accept all data pkt or use
						   REG_RXFLTMAP2 */
#घोषणा  RCR_ACCEPT_CTRL_FRAME		BIT(12) /* Accept all control pkt or use
						   REG_RXFLTMAP1 */
#घोषणा  RCR_ACCEPT_MGMT_FRAME		BIT(13) /* Accept all mgmt pkt or use
						   REG_RXFLTMAP0 */
#घोषणा  RCR_HTC_LOC_CTRL		BIT(14) /* MFC<--HTC=1 MFC-->HTC=0 */
#घोषणा  RCR_UC_DATA_PKT_INT_ENABLE	BIT(16) /* Enable unicast data packet
						   पूर्णांकerrupt */
#घोषणा  RCR_BM_DATA_PKT_INT_ENABLE	BIT(17) /* Enable broadcast data packet
						   पूर्णांकerrupt */
#घोषणा  RCR_TIM_PARSER_ENABLE		BIT(18) /* Enable RX beacon TIM parser*/
#घोषणा  RCR_MFBEN			BIT(22)
#घोषणा  RCR_LSIG_ENABLE		BIT(23) /* Enable LSIG TXOP Protection
						   function. Search KEYCAM क्रम
						   each rx packet to check अगर
						   LSIGEN bit is set. */
#घोषणा  RCR_MULTI_BSSID_ENABLE		BIT(24) /* Enable Multiple BssId */
#घोषणा  RCR_FORCE_ACK			BIT(26)
#घोषणा  RCR_ACCEPT_BA_SSN		BIT(27) /* Accept BA SSN */
#घोषणा  RCR_APPEND_PHYSTAT		BIT(28)
#घोषणा  RCR_APPEND_ICV			BIT(29)
#घोषणा  RCR_APPEND_MIC			BIT(30)
#घोषणा  RCR_APPEND_FCS			BIT(31) /* WMAC append FCS after */

#घोषणा REG_RX_PKT_LIMIT		0x060c
#घोषणा REG_RX_DLK_TIME			0x060d
#घोषणा REG_RX_DRVINFO_SZ		0x060f

#घोषणा REG_MACID			0x0610
#घोषणा REG_BSSID			0x0618
#घोषणा REG_MAR				0x0620
#घोषणा REG_MBIDCAMCFG			0x0628

#घोषणा REG_USTIME_EDCA			0x0638
#घोषणा REG_MAC_SPEC_SIFS		0x063a

/*  20100719 Joseph: Hardware रेजिस्टर definition change. (HW datasheet v54) */
	/*  [15:8]SIFS_R2T_OFDM, [7:0]SIFS_R2T_CCK */
#घोषणा REG_R2T_SIFS			0x063c
	/*  [15:8]SIFS_T2T_OFDM, [7:0]SIFS_T2T_CCK */
#घोषणा REG_T2T_SIFS			0x063e
#घोषणा REG_ACKTO			0x0640
#घोषणा REG_CTS2TO			0x0641
#घोषणा REG_EIFS			0x0642

/* WMA, BA, CCX */
#घोषणा REG_NAV_CTRL			0x0650
/* In units of 128us */
#घोषणा REG_NAV_UPPER			0x0652
#घोषणा  NAV_UPPER_UNIT			128

#घोषणा REG_BACAMCMD			0x0654
#घोषणा REG_BACAMCONTENT		0x0658
#घोषणा REG_LBDLY			0x0660
#घोषणा REG_FWDLY			0x0661
#घोषणा REG_RXERR_RPT			0x0664
#घोषणा REG_WMAC_TRXPTCL_CTL		0x0668
#घोषणा  WMAC_TRXPTCL_CTL_BW_MASK	(BIT(7) | BIT(8))
#घोषणा  WMAC_TRXPTCL_CTL_BW_20		0
#घोषणा  WMAC_TRXPTCL_CTL_BW_40		BIT(7)
#घोषणा  WMAC_TRXPTCL_CTL_BW_80		BIT(8)

/*  Security */
#घोषणा REG_CAM_CMD			0x0670
#घोषणा  CAM_CMD_POLLING		BIT(31)
#घोषणा  CAM_CMD_WRITE			BIT(16)
#घोषणा  CAM_CMD_KEY_SHIFT		3
#घोषणा REG_CAM_WRITE			0x0674
#घोषणा  CAM_WRITE_VALID		BIT(15)
#घोषणा REG_CAM_READ			0x0678
#घोषणा REG_CAM_DEBUG			0x067c
#घोषणा REG_SECURITY_CFG		0x0680
#घोषणा  SEC_CFG_TX_USE_DEFKEY		BIT(0)
#घोषणा  SEC_CFG_RX_USE_DEFKEY		BIT(1)
#घोषणा  SEC_CFG_TX_SEC_ENABLE		BIT(2)
#घोषणा  SEC_CFG_RX_SEC_ENABLE		BIT(3)
#घोषणा  SEC_CFG_SKBYA2			BIT(4)
#घोषणा  SEC_CFG_NO_SKMC		BIT(5)
#घोषणा  SEC_CFG_TXBC_USE_DEFKEY	BIT(6)
#घोषणा  SEC_CFG_RXBC_USE_DEFKEY	BIT(7)

/*  Power */
#घोषणा REG_WOW_CTRL			0x0690
#घोषणा REG_PSSTATUS			0x0691
#घोषणा REG_PS_RX_INFO			0x0692
#घोषणा REG_LPNAV_CTRL			0x0694
#घोषणा REG_WKFMCAM_CMD			0x0698
#घोषणा REG_WKFMCAM_RWD			0x069c

/*
 * RX Filters: each bit corresponds to the numerical value of the subtype.
 * If it is set the subtype frame type is passed. The filter is only used when
 * the RCR_ACCEPT_DATA_FRAME, RCR_ACCEPT_CTRL_FRAME, RCR_ACCEPT_MGMT_FRAME bit
 * in the RCR are low.
 *
 * Example: Beacon subtype is binary 1000 which is decimal 8 so we have to set
 * bit 8 (0x100) in REG_RXFLTMAP0 to enable reception.
 */
#घोषणा REG_RXFLTMAP0			0x06a0	/* Management frames */
#घोषणा REG_RXFLTMAP1			0x06a2	/* Control frames */
#घोषणा REG_RXFLTMAP2			0x06a4	/* Data frames */

#घोषणा REG_BCN_PSR_RPT			0x06a8
#घोषणा REG_CALB32K_CTRL		0x06ac
#घोषणा REG_PKT_MON_CTRL		0x06b4
#घोषणा REG_BT_COEX_TABLE1		0x06c0
#घोषणा REG_BT_COEX_TABLE2		0x06c4
#घोषणा REG_BT_COEX_TABLE3		0x06c8
#घोषणा REG_BT_COEX_TABLE4		0x06cc
#घोषणा REG_WMAC_RESP_TXINFO		0x06d8

#घोषणा REG_MACID1			0x0700
#घोषणा REG_BSSID1			0x0708

/*
 * This seems to be 8723bu specअगरic
 */
#घोषणा REG_BT_CONTROL_8723BU		0x0764
#घोषणा  BT_CONTROL_BT_GRANT		BIT(12)

#घोषणा REG_WLAN_ACT_CONTROL_8723B	0x076e

#घोषणा REG_FPGA0_RF_MODE		0x0800
#घोषणा  FPGA_RF_MODE			BIT(0)
#घोषणा  FPGA_RF_MODE_JAPAN		BIT(1)
#घोषणा  FPGA_RF_MODE_CCK		BIT(24)
#घोषणा  FPGA_RF_MODE_OFDM		BIT(25)

#घोषणा REG_FPGA0_TX_INFO		0x0804
#घोषणा  FPGA0_TX_INFO_OFDM_PATH_A	BIT(0)
#घोषणा  FPGA0_TX_INFO_OFDM_PATH_B	BIT(1)
#घोषणा  FPGA0_TX_INFO_OFDM_PATH_C	BIT(2)
#घोषणा  FPGA0_TX_INFO_OFDM_PATH_D	BIT(3)
#घोषणा REG_FPGA0_PSD_FUNC		0x0808
#घोषणा REG_FPGA0_TX_GAIN		0x080c
#घोषणा REG_FPGA0_RF_TIMING1		0x0810
#घोषणा REG_FPGA0_RF_TIMING2		0x0814
#घोषणा REG_FPGA0_POWER_SAVE		0x0818
#घोषणा  FPGA0_PS_LOWER_CHANNEL		BIT(26)
#घोषणा  FPGA0_PS_UPPER_CHANNEL		BIT(27)

#घोषणा REG_FPGA0_XA_HSSI_PARM1		0x0820	/* RF 3 wire रेजिस्टर */
#घोषणा  FPGA0_HSSI_PARM1_PI		BIT(8)
#घोषणा REG_FPGA0_XA_HSSI_PARM2		0x0824
#घोषणा REG_FPGA0_XB_HSSI_PARM1		0x0828
#घोषणा REG_FPGA0_XB_HSSI_PARM2		0x082c
#घोषणा  FPGA0_HSSI_3WIRE_DATA_LEN	0x800
#घोषणा  FPGA0_HSSI_3WIRE_ADDR_LEN	0x400
#घोषणा  FPGA0_HSSI_PARM2_ADDR_SHIFT	23
#घोषणा  FPGA0_HSSI_PARM2_ADDR_MASK	0x7f800000	/* 0xff << 23 */
#घोषणा  FPGA0_HSSI_PARM2_CCK_HIGH_PWR	BIT(9)
#घोषणा  FPGA0_HSSI_PARM2_EDGE_READ	BIT(31)

#घोषणा REG_TX_AGC_B_RATE18_06		0x0830
#घोषणा REG_TX_AGC_B_RATE54_24		0x0834
#घोषणा REG_TX_AGC_B_CCK1_55_MCS32	0x0838
#घोषणा REG_TX_AGC_B_MCS03_MCS00	0x083c

#घोषणा REG_FPGA0_XA_LSSI_PARM		0x0840
#घोषणा REG_FPGA0_XB_LSSI_PARM		0x0844
#घोषणा  FPGA0_LSSI_PARM_ADDR_SHIFT	20
#घोषणा  FPGA0_LSSI_PARM_ADDR_MASK	0x0ff00000
#घोषणा  FPGA0_LSSI_PARM_DATA_MASK	0x000fffff

#घोषणा REG_TX_AGC_B_MCS07_MCS04	0x0848
#घोषणा REG_TX_AGC_B_MCS11_MCS08	0x084c

#घोषणा REG_FPGA0_XCD_SWITCH_CTRL	0x085c

#घोषणा REG_FPGA0_XA_RF_INT_OE		0x0860	/* RF Channel चयन */
#घोषणा REG_FPGA0_XB_RF_INT_OE		0x0864
#घोषणा  FPGA0_INT_OE_ANTENNA_AB_OPEN	0x000
#घोषणा  FPGA0_INT_OE_ANTENNA_A		BIT(8)
#घोषणा  FPGA0_INT_OE_ANTENNA_B		BIT(9)
#घोषणा  FPGA0_INT_OE_ANTENNA_MASK	(FPGA0_INT_OE_ANTENNA_A | \
					 FPGA0_INT_OE_ANTENNA_B)

#घोषणा REG_TX_AGC_B_MCS15_MCS12	0x0868
#घोषणा REG_TX_AGC_B_CCK11_A_CCK2_11	0x086c

#घोषणा REG_FPGA0_XAB_RF_SW_CTRL	0x0870
#घोषणा REG_FPGA0_XA_RF_SW_CTRL		0x0870	/* 16 bit */
#घोषणा REG_FPGA0_XB_RF_SW_CTRL		0x0872	/* 16 bit */
#घोषणा REG_FPGA0_XCD_RF_SW_CTRL	0x0874
#घोषणा REG_FPGA0_XC_RF_SW_CTRL		0x0874	/* 16 bit */
#घोषणा REG_FPGA0_XD_RF_SW_CTRL		0x0876	/* 16 bit */
#घोषणा  FPGA0_RF_3WIRE_DATA		BIT(0)
#घोषणा  FPGA0_RF_3WIRE_CLOC		BIT(1)
#घोषणा  FPGA0_RF_3WIRE_LOAD		BIT(2)
#घोषणा  FPGA0_RF_3WIRE_RW		BIT(3)
#घोषणा  FPGA0_RF_3WIRE_MASK		0xf
#घोषणा  FPGA0_RF_RFENV			BIT(4)
#घोषणा  FPGA0_RF_TRSW			BIT(5)	/* Useless now */
#घोषणा  FPGA0_RF_TRSWB			BIT(6)
#घोषणा  FPGA0_RF_ANTSW			BIT(8)
#घोषणा  FPGA0_RF_ANTSWB		BIT(9)
#घोषणा  FPGA0_RF_PAPE			BIT(10)
#घोषणा  FPGA0_RF_PAPE5G		BIT(11)
#घोषणा  FPGA0_RF_BD_CTRL_SHIFT		16

#घोषणा REG_FPGA0_XAB_RF_PARM		0x0878	/* Antenna select path in ODM */
#घोषणा REG_FPGA0_XA_RF_PARM		0x0878	/* 16 bit */
#घोषणा REG_FPGA0_XB_RF_PARM		0x087a	/* 16 bit */
#घोषणा REG_FPGA0_XCD_RF_PARM		0x087c
#घोषणा REG_FPGA0_XC_RF_PARM		0x087c	/* 16 bit */
#घोषणा REG_FPGA0_XD_RF_PARM		0x087e	/* 16 bit */
#घोषणा  FPGA0_RF_PARM_RFA_ENABLE	BIT(1)
#घोषणा  FPGA0_RF_PARM_RFB_ENABLE	BIT(17)
#घोषणा  FPGA0_RF_PARM_CLK_GATE		BIT(31)

#घोषणा REG_FPGA0_ANALOG1		0x0880
#घोषणा REG_FPGA0_ANALOG2		0x0884
#घोषणा  FPGA0_ANALOG2_20MHZ		BIT(10)
#घोषणा REG_FPGA0_ANALOG3		0x0888
#घोषणा REG_FPGA0_ANALOG4		0x088c

#घोषणा REG_NHM_TH9_TH10_8723B		0x0890
#घोषणा REG_NHM_TIMER_8723B		0x0894
#घोषणा REG_NHM_TH3_TO_TH0_8723B	0x0898
#घोषणा REG_NHM_TH7_TO_TH4_8723B	0x089c

#घोषणा REG_FPGA0_XA_LSSI_READBACK	0x08a0	/* Tranceiver LSSI Readback */
#घोषणा REG_FPGA0_XB_LSSI_READBACK	0x08a4
#घोषणा REG_HSPI_XA_READBACK		0x08b8	/* Transceiver A HSPI पढ़ो */
#घोषणा REG_HSPI_XB_READBACK		0x08bc	/* Transceiver B HSPI पढ़ो */

#घोषणा REG_FPGA1_RF_MODE		0x0900

#घोषणा REG_FPGA1_TX_INFO		0x090c
#घोषणा REG_DPDT_CTRL			0x092c	/* 8723BU */
#घोषणा REG_RFE_CTRL_ANTA_SRC		0x0930	/* 8723BU */
#घोषणा REG_RFE_PATH_SELECT		0x0940	/* 8723BU */
#घोषणा REG_RFE_BUFFER			0x0944	/* 8723BU */
#घोषणा REG_S0S1_PATH_SWITCH		0x0948	/* 8723BU */

#घोषणा REG_CCK0_SYSTEM			0x0a00
#घोषणा  CCK0_SIDEBAND			BIT(4)

#घोषणा REG_CCK0_AFE_SETTING		0x0a04
#घोषणा  CCK0_AFE_RX_MASK		0x0f000000
#घोषणा  CCK0_AFE_RX_ANT_AB		BIT(24)
#घोषणा  CCK0_AFE_RX_ANT_A		0
#घोषणा  CCK0_AFE_RX_ANT_B		(BIT(24) | BIT(26))

#घोषणा REG_CONFIG_ANT_A		0x0b68
#घोषणा REG_CONFIG_ANT_B		0x0b6c

#घोषणा REG_OFDM0_TRX_PATH_ENABLE	0x0c04
#घोषणा OFDM_RF_PATH_RX_MASK		0x0f
#घोषणा OFDM_RF_PATH_RX_A		BIT(0)
#घोषणा OFDM_RF_PATH_RX_B		BIT(1)
#घोषणा OFDM_RF_PATH_RX_C		BIT(2)
#घोषणा OFDM_RF_PATH_RX_D		BIT(3)
#घोषणा OFDM_RF_PATH_TX_MASK		0xf0
#घोषणा OFDM_RF_PATH_TX_A		BIT(4)
#घोषणा OFDM_RF_PATH_TX_B		BIT(5)
#घोषणा OFDM_RF_PATH_TX_C		BIT(6)
#घोषणा OFDM_RF_PATH_TX_D		BIT(7)

#घोषणा REG_OFDM0_TR_MUX_PAR		0x0c08

#घोषणा REG_OFDM0_FA_RSTC		0x0c0c

#घोषणा REG_OFDM0_XA_RX_IQ_IMBALANCE	0x0c14
#घोषणा REG_OFDM0_XB_RX_IQ_IMBALANCE	0x0c1c

#घोषणा REG_OFDM0_ENERGY_CCA_THRES	0x0c4c

#घोषणा REG_OFDM0_RX_D_SYNC_PATH	0x0c40
#घोषणा  OFDM0_SYNC_PATH_NOTCH_FILTER	BIT(1)

#घोषणा REG_OFDM0_XA_AGC_CORE1		0x0c50
#घोषणा REG_OFDM0_XA_AGC_CORE2		0x0c54
#घोषणा REG_OFDM0_XB_AGC_CORE1		0x0c58
#घोषणा REG_OFDM0_XB_AGC_CORE2		0x0c5c
#घोषणा REG_OFDM0_XC_AGC_CORE1		0x0c60
#घोषणा REG_OFDM0_XC_AGC_CORE2		0x0c64
#घोषणा REG_OFDM0_XD_AGC_CORE1		0x0c68
#घोषणा REG_OFDM0_XD_AGC_CORE2		0x0c6c
#घोषणा  OFDM0_X_AGC_CORE1_IGI_MASK	0x0000007F

#घोषणा REG_OFDM0_AGC_PARM1		0x0c70

#घोषणा REG_OFDM0_AGCR_SSI_TABLE	0x0c78

#घोषणा REG_OFDM0_XA_TX_IQ_IMBALANCE	0x0c80
#घोषणा REG_OFDM0_XB_TX_IQ_IMBALANCE	0x0c88
#घोषणा REG_OFDM0_XC_TX_IQ_IMBALANCE	0x0c90
#घोषणा REG_OFDM0_XD_TX_IQ_IMBALANCE	0x0c98

#घोषणा REG_OFDM0_XC_TX_AFE		0x0c94
#घोषणा REG_OFDM0_XD_TX_AFE		0x0c9c

#घोषणा REG_OFDM0_RX_IQ_EXT_ANTA	0x0ca0

/* 8723bu */
#घोषणा REG_OFDM0_TX_PSDO_NOISE_WEIGHT	0x0ce4

#घोषणा REG_OFDM1_LSTF			0x0d00
#घोषणा  OFDM_LSTF_PRIME_CH_LOW		BIT(10)
#घोषणा  OFDM_LSTF_PRIME_CH_HIGH	BIT(11)
#घोषणा  OFDM_LSTF_PRIME_CH_MASK	(OFDM_LSTF_PRIME_CH_LOW | \
					 OFDM_LSTF_PRIME_CH_HIGH)
#घोषणा  OFDM_LSTF_CONTINUE_TX		BIT(28)
#घोषणा  OFDM_LSTF_SINGLE_CARRIER	BIT(29)
#घोषणा  OFDM_LSTF_SINGLE_TONE		BIT(30)
#घोषणा  OFDM_LSTF_MASK			0x70000000

#घोषणा REG_OFDM1_TRX_PATH_ENABLE	0x0d04

#घोषणा REG_TX_AGC_A_RATE18_06		0x0e00
#घोषणा REG_TX_AGC_A_RATE54_24		0x0e04
#घोषणा REG_TX_AGC_A_CCK1_MCS32		0x0e08
#घोषणा REG_TX_AGC_A_MCS03_MCS00	0x0e10
#घोषणा REG_TX_AGC_A_MCS07_MCS04	0x0e14
#घोषणा REG_TX_AGC_A_MCS11_MCS08	0x0e18
#घोषणा REG_TX_AGC_A_MCS15_MCS12	0x0e1c

#घोषणा REG_FPGA0_IQK			0x0e28

#घोषणा REG_TX_IQK_TONE_A		0x0e30
#घोषणा REG_RX_IQK_TONE_A		0x0e34
#घोषणा REG_TX_IQK_PI_A			0x0e38
#घोषणा REG_RX_IQK_PI_A			0x0e3c

#घोषणा REG_TX_IQK			0x0e40
#घोषणा REG_RX_IQK			0x0e44
#घोषणा REG_IQK_AGC_PTS			0x0e48
#घोषणा REG_IQK_AGC_RSP			0x0e4c
#घोषणा REG_TX_IQK_TONE_B		0x0e50
#घोषणा REG_RX_IQK_TONE_B		0x0e54
#घोषणा REG_TX_IQK_PI_B			0x0e58
#घोषणा REG_RX_IQK_PI_B			0x0e5c
#घोषणा REG_IQK_AGC_CONT		0x0e60

#घोषणा REG_BLUETOOTH			0x0e6c
#घोषणा REG_RX_WAIT_CCA			0x0e70
#घोषणा REG_TX_CCK_RFON			0x0e74
#घोषणा REG_TX_CCK_BBON			0x0e78
#घोषणा REG_TX_OFDM_RFON		0x0e7c
#घोषणा REG_TX_OFDM_BBON		0x0e80
#घोषणा REG_TX_TO_RX			0x0e84
#घोषणा REG_TX_TO_TX			0x0e88
#घोषणा REG_RX_CCK			0x0e8c

#घोषणा REG_TX_POWER_BEFORE_IQK_A	0x0e94
#घोषणा REG_TX_POWER_AFTER_IQK_A	0x0e9c

#घोषणा REG_RX_POWER_BEFORE_IQK_A	0x0ea0
#घोषणा REG_RX_POWER_BEFORE_IQK_A_2	0x0ea4
#घोषणा REG_RX_POWER_AFTER_IQK_A	0x0ea8
#घोषणा REG_RX_POWER_AFTER_IQK_A_2	0x0eac

#घोषणा REG_TX_POWER_BEFORE_IQK_B	0x0eb4
#घोषणा REG_TX_POWER_AFTER_IQK_B	0x0ebc

#घोषणा REG_RX_POWER_BEFORE_IQK_B	0x0ec0
#घोषणा REG_RX_POWER_BEFORE_IQK_B_2	0x0ec4
#घोषणा REG_RX_POWER_AFTER_IQK_B	0x0ec8
#घोषणा REG_RX_POWER_AFTER_IQK_B_2	0x0ecc

#घोषणा REG_RX_OFDM			0x0ed0
#घोषणा REG_RX_WAIT_RIFS		0x0ed4
#घोषणा REG_RX_TO_RX			0x0ed8
#घोषणा REG_STANDBY			0x0edc
#घोषणा REG_SLEEP			0x0ee0
#घोषणा REG_PMPD_ANAEN			0x0eec

#घोषणा REG_FW_START_ADDRESS		0x1000

#घोषणा REG_USB_INFO			0xfe17
#घोषणा REG_USB_HIMR			0xfe38
#घोषणा  USB_HIMR_TIMEOUT2		BIT(31)
#घोषणा  USB_HIMR_TIMEOUT1		BIT(30)
#घोषणा  USB_HIMR_PSTIMEOUT		BIT(29)
#घोषणा  USB_HIMR_GTINT4		BIT(28)
#घोषणा  USB_HIMR_GTINT3		BIT(27)
#घोषणा  USB_HIMR_TXBCNERR		BIT(26)
#घोषणा  USB_HIMR_TXBCNOK		BIT(25)
#घोषणा  USB_HIMR_TSF_BIT32_TOGGLE	BIT(24)
#घोषणा  USB_HIMR_BCNDMAINT3		BIT(23)
#घोषणा  USB_HIMR_BCNDMAINT2		BIT(22)
#घोषणा  USB_HIMR_BCNDMAINT1		BIT(21)
#घोषणा  USB_HIMR_BCNDMAINT0		BIT(20)
#घोषणा  USB_HIMR_BCNDOK3		BIT(19)
#घोषणा  USB_HIMR_BCNDOK2		BIT(18)
#घोषणा  USB_HIMR_BCNDOK1		BIT(17)
#घोषणा  USB_HIMR_BCNDOK0		BIT(16)
#घोषणा  USB_HIMR_HSISR_IND		BIT(15)
#घोषणा  USB_HIMR_BCNDMAINT_E		BIT(14)
/* RSVD	BIT(13) */
#घोषणा  USB_HIMR_CTW_END		BIT(12)
/* RSVD	BIT(11) */
#घोषणा  USB_HIMR_C2HCMD		BIT(10)
#घोषणा  USB_HIMR_CPWM2			BIT(9)
#घोषणा  USB_HIMR_CPWM			BIT(8)
#घोषणा  USB_HIMR_HIGHDOK		BIT(7)	/*  High Queue DMA OK
						    Interrupt */
#घोषणा  USB_HIMR_MGNTDOK		BIT(6)	/*  Management Queue DMA OK
						    Interrupt */
#घोषणा  USB_HIMR_BKDOK			BIT(5)	/*  AC_BK DMA OK Interrupt */
#घोषणा  USB_HIMR_BEDOK			BIT(4)	/*  AC_BE DMA OK Interrupt */
#घोषणा  USB_HIMR_VIDOK			BIT(3)	/*  AC_VI DMA OK Interrupt */
#घोषणा  USB_HIMR_VODOK			BIT(2)	/*  AC_VO DMA Interrupt */
#घोषणा  USB_HIMR_RDU			BIT(1)	/*  Receive Descriptor
						    Unavailable */
#घोषणा  USB_HIMR_ROK			BIT(0)	/*  Receive DMA OK Interrupt */

#घोषणा REG_USB_SPECIAL_OPTION		0xfe55
#घोषणा  USB_SPEC_USB_AGG_ENABLE	BIT(3)	/* Enable USB aggregation */
#घोषणा  USB_SPEC_INT_BULK_SELECT	BIT(4)	/* Use पूर्णांकerrupt endpoपूर्णांक to
						   deliver पूर्णांकerrupt packet.
						   0: Use पूर्णांक, 1: use bulk */
#घोषणा REG_USB_HRPWM			0xfe58
#घोषणा REG_USB_DMA_AGG_TO		0xfe5b
#घोषणा REG_USB_AGG_TIMEOUT		0xfe5c
#घोषणा REG_USB_AGG_THRESH		0xfe5d

#घोषणा REG_NORMAL_SIE_VID		0xfe60	/* 0xfe60 - 0xfe61 */
#घोषणा REG_NORMAL_SIE_PID		0xfe62	/* 0xfe62 - 0xfe63 */
#घोषणा REG_NORMAL_SIE_OPTIONAL		0xfe64
#घोषणा REG_NORMAL_SIE_EP		0xfe65	/* 0xfe65 - 0xfe67 */
#घोषणा REG_NORMAL_SIE_EP_TX		0xfe66
#घोषणा  NORMAL_SIE_EP_TX_HIGH_MASK	0x000f
#घोषणा  NORMAL_SIE_EP_TX_NORMAL_MASK	0x00f0
#घोषणा  NORMAL_SIE_EP_TX_LOW_MASK	0x0f00

#घोषणा REG_NORMAL_SIE_PHY		0xfe68	/* 0xfe68 - 0xfe6b */
#घोषणा REG_NORMAL_SIE_OPTIONAL2	0xfe6c
#घोषणा REG_NORMAL_SIE_GPS_EP		0xfe6d	/* RTL8723 only */
#घोषणा REG_NORMAL_SIE_MAC_ADDR		0xfe70	/* 0xfe70 - 0xfe75 */
#घोषणा REG_NORMAL_SIE_STRING		0xfe80	/* 0xfe80 - 0xfedf */

/* RF6052 रेजिस्टरs */
#घोषणा RF6052_REG_AC			0x00
#घोषणा RF6052_REG_IQADJ_G1		0x01
#घोषणा RF6052_REG_IQADJ_G2		0x02
#घोषणा RF6052_REG_BS_PA_APSET_G1_G4	0x03
#घोषणा RF6052_REG_BS_PA_APSET_G5_G8	0x04
#घोषणा RF6052_REG_POW_TRSW		0x05
#घोषणा RF6052_REG_GAIN_RX		0x06
#घोषणा RF6052_REG_GAIN_TX		0x07
#घोषणा RF6052_REG_TXM_IDAC		0x08
#घोषणा RF6052_REG_IPA_G		0x09
#घोषणा RF6052_REG_TXBIAS_G		0x0a
#घोषणा RF6052_REG_TXPA_AG		0x0b
#घोषणा RF6052_REG_IPA_A		0x0c
#घोषणा RF6052_REG_TXBIAS_A		0x0d
#घोषणा RF6052_REG_BS_PA_APSET_G9_G11	0x0e
#घोषणा RF6052_REG_BS_IQGEN		0x0f
#घोषणा RF6052_REG_MODE1		0x10
#घोषणा RF6052_REG_MODE2		0x11
#घोषणा RF6052_REG_RX_AGC_HP		0x12
#घोषणा RF6052_REG_TX_AGC		0x13
#घोषणा RF6052_REG_BIAS			0x14
#घोषणा RF6052_REG_IPA			0x15
#घोषणा RF6052_REG_TXBIAS		0x16
#घोषणा RF6052_REG_POW_ABILITY		0x17
#घोषणा RF6052_REG_MODE_AG		0x18	/* RF channel and BW चयन */
#घोषणा  MODE_AG_CHANNEL_MASK		0x3ff
#घोषणा  MODE_AG_CHANNEL_20MHZ		BIT(10)
#घोषणा  MODE_AG_BW_MASK		(BIT(10) | BIT(11))
#घोषणा  MODE_AG_BW_20MHZ_8723B		(BIT(10) | BIT(11))
#घोषणा  MODE_AG_BW_40MHZ_8723B		BIT(10)
#घोषणा  MODE_AG_BW_80MHZ_8723B		0

#घोषणा RF6052_REG_TOP			0x19
#घोषणा RF6052_REG_RX_G1		0x1a
#घोषणा RF6052_REG_RX_G2		0x1b
#घोषणा RF6052_REG_RX_BB2		0x1c
#घोषणा RF6052_REG_RX_BB1		0x1d
#घोषणा RF6052_REG_RCK1			0x1e
#घोषणा RF6052_REG_RCK2			0x1f
#घोषणा RF6052_REG_TX_G1		0x20
#घोषणा RF6052_REG_TX_G2		0x21
#घोषणा RF6052_REG_TX_G3		0x22
#घोषणा RF6052_REG_TX_BB1		0x23
#घोषणा RF6052_REG_T_METER		0x24
#घोषणा RF6052_REG_SYN_G1		0x25	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G2		0x26	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G3		0x27	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G4		0x28	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G5		0x29	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G6		0x2a	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G7		0x2b	/* RF TX Power control */
#घोषणा RF6052_REG_SYN_G8		0x2c	/* RF TX Power control */

#घोषणा RF6052_REG_RCK_OS		0x30	/* RF TX PA control */

#घोषणा RF6052_REG_TXPA_G1		0x31	/* RF TX PA control */
#घोषणा RF6052_REG_TXPA_G2		0x32	/* RF TX PA control */
#घोषणा RF6052_REG_TXPA_G3		0x33	/* RF TX PA control */

/*
 * NextGen regs: 8723BU
 */
#घोषणा RF6052_REG_T_METER_8723B	0x42
#घोषणा RF6052_REG_UNKNOWN_43		0x43
#घोषणा RF6052_REG_UNKNOWN_55		0x55
#घोषणा RF6052_REG_UNKNOWN_56		0x56
#घोषणा RF6052_REG_S0S1			0xb0
#घोषणा RF6052_REG_UNKNOWN_DF		0xdf
#घोषणा RF6052_REG_UNKNOWN_ED		0xed
#घोषणा RF6052_REG_WE_LUT		0xef
