<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BRCMPHY_H
#घोषणा _LINUX_BRCMPHY_H

#समावेश <linux/phy.h>

/* All Broadcom Ethernet चयनes have a pseuकरो-PHY at address 30 which is used
 * to configure the चयन पूर्णांकernal रेजिस्टरs via MDIO accesses.
 */
#घोषणा BRCM_PSEUDO_PHY_ADDR           30

#घोषणा PHY_ID_BCM50610			0x0143bd60
#घोषणा PHY_ID_BCM50610M		0x0143bd70
#घोषणा PHY_ID_BCM5241			0x0143bc30
#घोषणा PHY_ID_BCMAC131			0x0143bc70
#घोषणा PHY_ID_BCM5481			0x0143bca0
#घोषणा PHY_ID_BCM5395			0x0143bcf0
#घोषणा PHY_ID_BCM53125			0x03625f20
#घोषणा PHY_ID_BCM54810			0x03625d00
#घोषणा PHY_ID_BCM54811			0x03625cc0
#घोषणा PHY_ID_BCM5482			0x0143bcb0
#घोषणा PHY_ID_BCM5411			0x00206070
#घोषणा PHY_ID_BCM5421			0x002060e0
#घोषणा PHY_ID_BCM54210E		0x600d84a0
#घोषणा PHY_ID_BCM5464			0x002060b0
#घोषणा PHY_ID_BCM5461			0x002060c0
#घोषणा PHY_ID_BCM54612E		0x03625e60
#घोषणा PHY_ID_BCM54616S		0x03625d10
#घोषणा PHY_ID_BCM54140			0xae025009
#घोषणा PHY_ID_BCM57780			0x03625d90
#घोषणा PHY_ID_BCM89610			0x03625cd0

#घोषणा PHY_ID_BCM72113			0x35905310
#घोषणा PHY_ID_BCM72116			0x35905350
#घोषणा PHY_ID_BCM7250			0xae025280
#घोषणा PHY_ID_BCM7255			0xae025120
#घोषणा PHY_ID_BCM7260			0xae025190
#घोषणा PHY_ID_BCM7268			0xae025090
#घोषणा PHY_ID_BCM7271			0xae0253b0
#घोषणा PHY_ID_BCM7278			0xae0251a0
#घोषणा PHY_ID_BCM7364			0xae025260
#घोषणा PHY_ID_BCM7366			0x600d8490
#घोषणा PHY_ID_BCM7346			0x600d8650
#घोषणा PHY_ID_BCM7362			0x600d84b0
#घोषणा PHY_ID_BCM7425			0x600d86b0
#घोषणा PHY_ID_BCM7429			0x600d8730
#घोषणा PHY_ID_BCM7435			0x600d8750
#घोषणा PHY_ID_BCM74371			0xae0252e0
#घोषणा PHY_ID_BCM7439			0x600d8480
#घोषणा PHY_ID_BCM7439_2		0xae025080
#घोषणा PHY_ID_BCM7445			0x600d8510

#घोषणा PHY_ID_BCM_CYGNUS		0xae025200
#घोषणा PHY_ID_BCM_OMEGA		0xae025100

#घोषणा PHY_BCM_OUI_MASK		0xfffffc00
#घोषणा PHY_BCM_OUI_1			0x00206000
#घोषणा PHY_BCM_OUI_2			0x0143bc00
#घोषणा PHY_BCM_OUI_3			0x03625c00
#घोषणा PHY_BCM_OUI_4			0x600d8400
#घोषणा PHY_BCM_OUI_5			0x03625e00
#घोषणा PHY_BCM_OUI_6			0xae025000

#घोषणा PHY_BRCM_AUTO_PWRDWN_ENABLE	0x00000001
#घोषणा PHY_BRCM_RX_REFCLK_UNUSED	0x00000002
#घोषणा PHY_BRCM_CLEAR_RGMII_MODE	0x00000004
#घोषणा PHY_BRCM_DIS_TXCRXC_NOENRGY	0x00000008
#घोषणा PHY_BRCM_EN_MASTER_MODE		0x00000010

/* Broadcom BCM7xxx specअगरic workarounds */
#घोषणा PHY_BRCM_7XXX_REV(x)		(((x) >> 8) & 0xff)
#घोषणा PHY_BRCM_7XXX_PATCH(x)		((x) & 0xff)
#घोषणा PHY_BCM_FLAGS_VALID		0x80000000

/* Broadcom BCM54XX रेजिस्टर definitions, common to most Broadcom PHYs */
#घोषणा MII_BCM54XX_ECR		0x10	/* BCM54xx extended control रेजिस्टर */
#घोषणा MII_BCM54XX_ECR_IM	0x1000	/* Interrupt mask */
#घोषणा MII_BCM54XX_ECR_IF	0x0800	/* Interrupt क्रमce */
#घोषणा MII_BCM54XX_ECR_FIFOE	0x0001	/* FIFO elasticity */

#घोषणा MII_BCM54XX_ESR		0x11	/* BCM54xx extended status रेजिस्टर */
#घोषणा MII_BCM54XX_ESR_IS	0x1000	/* Interrupt status */

#घोषणा MII_BCM54XX_EXP_DATA	0x15	/* Expansion रेजिस्टर data */
#घोषणा MII_BCM54XX_EXP_SEL	0x17	/* Expansion रेजिस्टर select */
#घोषणा MII_BCM54XX_EXP_SEL_SSD	0x0e00	/* Secondary SerDes select */
#घोषणा MII_BCM54XX_EXP_SEL_ER	0x0f00	/* Expansion रेजिस्टर select */
#घोषणा MII_BCM54XX_EXP_SEL_ETC	0x0d00	/* Expansion रेजिस्टर spare + 2k mem */

#घोषणा MII_BCM54XX_AUX_CTL	0x18	/* Auxiliary control रेजिस्टर */
#घोषणा MII_BCM54XX_ISR		0x1a	/* BCM54xx पूर्णांकerrupt status रेजिस्टर */
#घोषणा MII_BCM54XX_IMR		0x1b	/* BCM54xx पूर्णांकerrupt mask रेजिस्टर */
#घोषणा MII_BCM54XX_INT_CRCERR	0x0001	/* CRC error */
#घोषणा MII_BCM54XX_INT_LINK	0x0002	/* Link status changed */
#घोषणा MII_BCM54XX_INT_SPEED	0x0004	/* Link speed change */
#घोषणा MII_BCM54XX_INT_DUPLEX	0x0008	/* Duplex mode changed */
#घोषणा MII_BCM54XX_INT_LRS	0x0010	/* Local receiver status changed */
#घोषणा MII_BCM54XX_INT_RRS	0x0020	/* Remote receiver status changed */
#घोषणा MII_BCM54XX_INT_SSERR	0x0040	/* Scrambler synchronization error */
#घोषणा MII_BCM54XX_INT_UHCD	0x0080	/* Unsupported HCD negotiated */
#घोषणा MII_BCM54XX_INT_NHCD	0x0100	/* No HCD */
#घोषणा MII_BCM54XX_INT_NHCDL	0x0200	/* No HCD link */
#घोषणा MII_BCM54XX_INT_ANPR	0x0400	/* Auto-negotiation page received */
#घोषणा MII_BCM54XX_INT_LC	0x0800	/* All counters below 128 */
#घोषणा MII_BCM54XX_INT_HC	0x1000	/* Counter above 32768 */
#घोषणा MII_BCM54XX_INT_MDIX	0x2000	/* MDIX status change */
#घोषणा MII_BCM54XX_INT_PSERR	0x4000	/* Pair swap error */

#घोषणा MII_BCM54XX_SHD		0x1c	/* 0x1c shaकरोw रेजिस्टरs */
#घोषणा MII_BCM54XX_SHD_WRITE	0x8000
#घोषणा MII_BCM54XX_SHD_VAL(x)	((x & 0x1f) << 10)
#घोषणा MII_BCM54XX_SHD_DATA(x)	((x & 0x3ff) << 0)

#घोषणा MII_BCM54XX_RDB_ADDR	0x1e
#घोषणा MII_BCM54XX_RDB_DATA	0x1f

/* legacy access control via rdb/expansion रेजिस्टर */
#घोषणा BCM54XX_RDB_REG0087		0x0087
#घोषणा BCM54XX_EXP_REG7E		(MII_BCM54XX_EXP_SEL_ER + 0x7E)
#घोषणा BCM54XX_ACCESS_MODE_LEGACY_EN	BIT(15)

/*
 * AUXILIARY CONTROL SHADOW ACCESS REGISTERS.  (PHY REG 0x18)
 */
#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL	0x00
#घोषणा MII_BCM54XX_AUXCTL_ACTL_TX_6DB		0x0400
#घोषणा MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA	0x0800
#घोषणा MII_BCM54XX_AUXCTL_ACTL_EXT_PKT_LEN	0x4000

#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_MISC			0x07
#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_MISC_WIRESPEED_EN	0x0010
#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_EN	0x0080
#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN	0x0100
#घोषणा MII_BCM54XX_AUXCTL_MISC_FORCE_AMDIX		0x0200
#घोषणा MII_BCM54XX_AUXCTL_MISC_WREN			0x8000

#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_READ_SHIFT	12
#घोषणा MII_BCM54XX_AUXCTL_SHDWSEL_MASK	0x0007

/*
 * Broadcom LED source encodings.  These are used in BCM5461, BCM5481,
 * BCM5482, and possibly some others.
 */
#घोषणा BCM_LED_SRC_LINKSPD1	0x0
#घोषणा BCM_LED_SRC_LINKSPD2	0x1
#घोषणा BCM_LED_SRC_XMITLED	0x2
#घोषणा BCM_LED_SRC_ACTIVITYLED	0x3
#घोषणा BCM_LED_SRC_FDXLED	0x4
#घोषणा BCM_LED_SRC_SLAVE	0x5
#घोषणा BCM_LED_SRC_INTR	0x6
#घोषणा BCM_LED_SRC_QUALITY	0x7
#घोषणा BCM_LED_SRC_RCVLED	0x8
#घोषणा BCM_LED_SRC_WIRESPEED	0x9
#घोषणा BCM_LED_SRC_MULTICOLOR1	0xa
#घोषणा BCM_LED_SRC_OPENSHORT	0xb
#घोषणा BCM_LED_SRC_OFF		0xe	/* Tied high */
#घोषणा BCM_LED_SRC_ON		0xf	/* Tied low */

/*
 * Broadcom Multicolor LED configurations (expansion रेजिस्टर 4)
 */
#घोषणा BCM_EXP_MULTICOLOR		(MII_BCM54XX_EXP_SEL_ER + 0x04)
#घोषणा BCM_LED_MULTICOLOR_IN_PHASE	BIT(8)
#घोषणा BCM_LED_MULTICOLOR_LINK_ACT	0x0
#घोषणा BCM_LED_MULTICOLOR_SPEED	0x1
#घोषणा BCM_LED_MULTICOLOR_ACT_FLASH	0x2
#घोषणा BCM_LED_MULTICOLOR_FDX		0x3
#घोषणा BCM_LED_MULTICOLOR_OFF		0x4
#घोषणा BCM_LED_MULTICOLOR_ON		0x5
#घोषणा BCM_LED_MULTICOLOR_ALT		0x6
#घोषणा BCM_LED_MULTICOLOR_FLASH	0x7
#घोषणा BCM_LED_MULTICOLOR_LINK		0x8
#घोषणा BCM_LED_MULTICOLOR_ACT		0x9
#घोषणा BCM_LED_MULTICOLOR_PROGRAM	0xa

/*
 * BCM5482: Shaकरोw रेजिस्टरs
 * Shaकरोw values go पूर्णांकo bits [14:10] of रेजिस्टर 0x1c to select a shaकरोw
 * रेजिस्टर to access.
 */

/* 00100: Reserved control रेजिस्टर 2 */
#घोषणा BCM54XX_SHD_SCR2		0x04
#घोषणा  BCM54XX_SHD_SCR2_WSPD_RTRY_DIS	0x100
#घोषणा  BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_SHIFT	2
#घोषणा  BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_OFFSET	2
#घोषणा  BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_MASK	0x7

/* 00101: Spare Control Register 3 */
#घोषणा BCM54XX_SHD_SCR3		0x05
#घोषणा  BCM54XX_SHD_SCR3_DEF_CLK125	0x0001
#घोषणा  BCM54XX_SHD_SCR3_DLLAPD_DIS	0x0002
#घोषणा  BCM54XX_SHD_SCR3_TRDDAPD	0x0004
#घोषणा  BCM54XX_SHD_SCR3_RXCTXC_DIS	0x0100

/* 01010: Auto Power-Down */
#घोषणा BCM54XX_SHD_APD			0x0a
#घोषणा  BCM_APD_CLR_MASK		0xFE9F /* clear bits 5, 6 & 8 */
#घोषणा  BCM54XX_SHD_APD_EN		0x0020
#घोषणा  BCM_NO_ANEG_APD_EN		0x0060 /* bits 5 & 6 */
#घोषणा  BCM_APD_SINGLELP_EN	0x0100 /* Bit 8 */

#घोषणा BCM5482_SHD_LEDS1	0x0d	/* 01101: LED Selector 1 */
					/* LED3 / ~LINKSPD[2] selector */
#घोषणा BCM5482_SHD_LEDS1_LED3(src)	((src & 0xf) << 4)
					/* LED1 / ~LINKSPD[1] selector */
#घोषणा BCM5482_SHD_LEDS1_LED1(src)	((src & 0xf) << 0)
#घोषणा BCM54XX_SHD_RGMII_MODE	0x0b	/* 01011: RGMII Mode Selector */
#घोषणा BCM5482_SHD_SSD		0x14	/* 10100: Secondary SerDes control */
#घोषणा BCM5482_SHD_SSD_LEDM	0x0008	/* SSD LED Mode enable */
#घोषणा BCM5482_SHD_SSD_EN	0x0001	/* SSD enable */

/* 10011: SerDes 100-FX Control Register */
#घोषणा BCM54616S_SHD_100FX_CTRL	0x13
#घोषणा	BCM54616S_100FX_MODE		BIT(0)	/* 100-FX SerDes Enable */

/* 11111: Mode Control Register */
#घोषणा BCM54XX_SHD_MODE		0x1f
#घोषणा BCM54XX_SHD_INTF_SEL_MASK	GENMASK(2, 1)	/* INTERF_SEL[1:0] */
#घोषणा BCM54XX_SHD_INTF_SEL_RGMII	0x02
#घोषणा BCM54XX_SHD_INTF_SEL_SGMII	0x04
#घोषणा BCM54XX_SHD_INTF_SEL_GBIC	0x06
#घोषणा BCM54XX_SHD_MODE_1000BX		BIT(0)	/* Enable 1000-X रेजिस्टरs */

/*
 * EXPANSION SHADOW ACCESS REGISTERS.  (PHY REG 0x15, 0x16, and 0x17)
 */
#घोषणा MII_BCM54XX_EXP_AADJ1CH0		0x001f
#घोषणा  MII_BCM54XX_EXP_AADJ1CH0_SWP_ABCD_OEN	0x0200
#घोषणा  MII_BCM54XX_EXP_AADJ1CH0_SWSEL_THPF	0x0100
#घोषणा MII_BCM54XX_EXP_AADJ1CH3		0x601f
#घोषणा  MII_BCM54XX_EXP_AADJ1CH3_ADCCKADJ	0x0002
#घोषणा MII_BCM54XX_EXP_EXP08			0x0F08
#घोषणा  MII_BCM54XX_EXP_EXP08_RJCT_2MHZ	0x0001
#घोषणा  MII_BCM54XX_EXP_EXP08_EARLY_DAC_WAKE	0x0200
#घोषणा MII_BCM54XX_EXP_EXP75			0x0f75
#घोषणा  MII_BCM54XX_EXP_EXP75_VDACCTRL		0x003c
#घोषणा  MII_BCM54XX_EXP_EXP75_CM_OSC		0x0001
#घोषणा MII_BCM54XX_EXP_EXP96			0x0f96
#घोषणा  MII_BCM54XX_EXP_EXP96_MYST		0x0010
#घोषणा MII_BCM54XX_EXP_EXP97			0x0f97
#घोषणा  MII_BCM54XX_EXP_EXP97_MYST		0x0c0c

/*
 * BCM5482: Secondary SerDes रेजिस्टरs
 */
#घोषणा BCM5482_SSD_1000BX_CTL		0x00	/* 1000BASE-X Control */
#घोषणा BCM5482_SSD_1000BX_CTL_PWRDOWN	0x0800	/* Power-करोwn SSD */
#घोषणा BCM5482_SSD_SGMII_SLAVE		0x15	/* SGMII Slave Register */
#घोषणा BCM5482_SSD_SGMII_SLAVE_EN	0x0002	/* Slave mode enable */
#घोषणा BCM5482_SSD_SGMII_SLAVE_AD	0x0001	/* Slave स्वतः-detection */

/* BCM54810 Registers */
#घोषणा BCM54810_EXP_BROADREACH_LRE_MISC_CTL	(MII_BCM54XX_EXP_SEL_ER + 0x90)
#घोषणा BCM54810_EXP_BROADREACH_LRE_MISC_CTL_EN	(1 << 0)
#घोषणा BCM54810_SHD_CLK_CTL			0x3
#घोषणा BCM54810_SHD_CLK_CTL_GTXCLK_EN		(1 << 9)

/* BCM54612E Registers */
#घोषणा BCM54612E_EXP_SPARE0		(MII_BCM54XX_EXP_SEL_ETC + 0x34)
#घोषणा BCM54612E_LED4_CLK125OUT_EN	(1 << 1)

/*****************************************************************************/
/* Fast Ethernet Transceiver definitions. */
/*****************************************************************************/

#घोषणा MII_BRCM_FET_INTREG		0x1a	/* Interrupt रेजिस्टर */
#घोषणा MII_BRCM_FET_IR_MASK		0x0100	/* Mask all पूर्णांकerrupts */
#घोषणा MII_BRCM_FET_IR_LINK_EN		0x0200	/* Link status change enable */
#घोषणा MII_BRCM_FET_IR_SPEED_EN	0x0400	/* Link speed change enable */
#घोषणा MII_BRCM_FET_IR_DUPLEX_EN	0x0800	/* Duplex mode change enable */
#घोषणा MII_BRCM_FET_IR_ENABLE		0x4000	/* Interrupt enable */

#घोषणा MII_BRCM_FET_BRCMTEST		0x1f	/* Brcm test रेजिस्टर */
#घोषणा MII_BRCM_FET_BT_SRE		0x0080	/* Shaकरोw रेजिस्टर enable */


/*** Shaकरोw रेजिस्टर definitions ***/

#घोषणा MII_BRCM_FET_SHDW_MISCCTRL	0x10	/* Shaकरोw misc ctrl */
#घोषणा MII_BRCM_FET_SHDW_MC_FAME	0x4000	/* Force Auto MDIX enable */

#घोषणा MII_BRCM_FET_SHDW_AUXMODE4	0x1a	/* Auxiliary mode 4 */
#घोषणा MII_BRCM_FET_SHDW_AM4_LED_MASK	0x0003
#घोषणा MII_BRCM_FET_SHDW_AM4_LED_MODE1 0x0001

#घोषणा MII_BRCM_FET_SHDW_AUXSTAT2	0x1b	/* Auxiliary status 2 */
#घोषणा MII_BRCM_FET_SHDW_AS2_APDE	0x0020	/* Auto घातer करोwn enable */

#घोषणा BRCM_CL45VEN_EEE_CONTROL	0x803d
#घोषणा LPI_FEATURE_EN			0x8000
#घोषणा LPI_FEATURE_EN_DIG1000X		0x4000

/* Core रेजिस्टर definitions*/
#घोषणा MII_BRCM_CORE_BASE12	0x12
#घोषणा MII_BRCM_CORE_BASE13	0x13
#घोषणा MII_BRCM_CORE_BASE14	0x14
#घोषणा MII_BRCM_CORE_BASE1E	0x1E
#घोषणा MII_BRCM_CORE_EXPB0	0xB0
#घोषणा MII_BRCM_CORE_EXPB1	0xB1

/* Enhanced Cable Diagnostics */
#घोषणा BCM54XX_RDB_ECD_CTRL			0x2a0
#घोषणा BCM54XX_EXP_ECD_CTRL			(MII_BCM54XX_EXP_SEL_ER + 0xc0)

#घोषणा BCM54XX_ECD_CTRL_CABLE_TYPE_CAT3	1	/* CAT3 or worse */
#घोषणा BCM54XX_ECD_CTRL_CABLE_TYPE_CAT5	0	/* CAT5 or better */
#घोषणा BCM54XX_ECD_CTRL_CABLE_TYPE_MASK	BIT(0)	/* cable type */
#घोषणा BCM54XX_ECD_CTRL_INVALID		BIT(3)	/* invalid result */
#घोषणा BCM54XX_ECD_CTRL_UNIT_CM		0	/* cenसमयters */
#घोषणा BCM54XX_ECD_CTRL_UNIT_M			1	/* meters */
#घोषणा BCM54XX_ECD_CTRL_UNIT_MASK		BIT(10)	/* cable length unit */
#घोषणा BCM54XX_ECD_CTRL_IN_PROGRESS		BIT(11)	/* test in progress */
#घोषणा BCM54XX_ECD_CTRL_BREAK_LINK		BIT(12)	/* unconnect link
							 * during test
							 */
#घोषणा BCM54XX_ECD_CTRL_CROSS_SHORT_DIS	BIT(13)	/* disable पूर्णांकer-pair
							 * लघु check
							 */
#घोषणा BCM54XX_ECD_CTRL_RUN			BIT(15)	/* run immediate */

#घोषणा BCM54XX_RDB_ECD_FAULT_TYPE		0x2a1
#घोषणा BCM54XX_EXP_ECD_FAULT_TYPE		(MII_BCM54XX_EXP_SEL_ER + 0xc1)
#घोषणा BCM54XX_ECD_FAULT_TYPE_INVALID		0x0
#घोषणा BCM54XX_ECD_FAULT_TYPE_OK		0x1
#घोषणा BCM54XX_ECD_FAULT_TYPE_OPEN		0x2
#घोषणा BCM54XX_ECD_FAULT_TYPE_SAME_SHORT	0x3 /* लघु same pair */
#घोषणा BCM54XX_ECD_FAULT_TYPE_CROSS_SHORT	0x4 /* लघु dअगरferent pairs */
#घोषणा BCM54XX_ECD_FAULT_TYPE_BUSY		0x9
#घोषणा BCM54XX_ECD_FAULT_TYPE_PAIR_D_MASK	GENMASK(3, 0)
#घोषणा BCM54XX_ECD_FAULT_TYPE_PAIR_C_MASK	GENMASK(7, 4)
#घोषणा BCM54XX_ECD_FAULT_TYPE_PAIR_B_MASK	GENMASK(11, 8)
#घोषणा BCM54XX_ECD_FAULT_TYPE_PAIR_A_MASK	GENMASK(15, 12)
#घोषणा BCM54XX_ECD_PAIR_A_LENGTH_RESULTS	0x2a2
#घोषणा BCM54XX_ECD_PAIR_B_LENGTH_RESULTS	0x2a3
#घोषणा BCM54XX_ECD_PAIR_C_LENGTH_RESULTS	0x2a4
#घोषणा BCM54XX_ECD_PAIR_D_LENGTH_RESULTS	0x2a5

#घोषणा BCM54XX_RDB_ECD_PAIR_A_LENGTH_RESULTS	0x2a2
#घोषणा BCM54XX_EXP_ECD_PAIR_A_LENGTH_RESULTS	(MII_BCM54XX_EXP_SEL_ER + 0xc2)
#घोषणा BCM54XX_RDB_ECD_PAIR_B_LENGTH_RESULTS	0x2a3
#घोषणा BCM54XX_EXP_ECD_PAIR_B_LENGTH_RESULTS	(MII_BCM54XX_EXP_SEL_ER + 0xc3)
#घोषणा BCM54XX_RDB_ECD_PAIR_C_LENGTH_RESULTS	0x2a4
#घोषणा BCM54XX_EXP_ECD_PAIR_C_LENGTH_RESULTS	(MII_BCM54XX_EXP_SEL_ER + 0xc4)
#घोषणा BCM54XX_RDB_ECD_PAIR_D_LENGTH_RESULTS	0x2a5
#घोषणा BCM54XX_EXP_ECD_PAIR_D_LENGTH_RESULTS	(MII_BCM54XX_EXP_SEL_ER + 0xc5)
#घोषणा BCM54XX_ECD_LENGTH_RESULTS_INVALID	0xffff

#पूर्ण_अगर /* _LINUX_BRCMPHY_H */
