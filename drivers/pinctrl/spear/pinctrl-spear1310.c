<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr1310 pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "pinctrl-spear.h"

#घोषणा DRIVER_NAME "spear1310-pinmux"

/* pins */
अटल स्थिर काष्ठा pinctrl_pin_desc spear1310_pins[] = अणु
	SPEAR_PIN_0_TO_101,
	SPEAR_PIN_102_TO_245,
पूर्ण;

/* रेजिस्टरs */
#घोषणा PERIP_CFG					0x3B0
	#घोषणा MCIF_SEL_SHIFT				5
	#घोषणा MCIF_SEL_SD				(0x1 << MCIF_SEL_SHIFT)
	#घोषणा MCIF_SEL_CF				(0x2 << MCIF_SEL_SHIFT)
	#घोषणा MCIF_SEL_XD				(0x3 << MCIF_SEL_SHIFT)
	#घोषणा MCIF_SEL_MASK				(0x3 << MCIF_SEL_SHIFT)

#घोषणा PCIE_SATA_CFG					0x3A4
	#घोषणा PCIE_SATA2_SEL_PCIE			(0 << 31)
	#घोषणा PCIE_SATA1_SEL_PCIE			(0 << 30)
	#घोषणा PCIE_SATA0_SEL_PCIE			(0 << 29)
	#घोषणा PCIE_SATA2_SEL_SATA			(1 << 31)
	#घोषणा PCIE_SATA1_SEL_SATA			(1 << 30)
	#घोषणा PCIE_SATA0_SEL_SATA			(1 << 29)
	#घोषणा SATA2_CFG_TX_CLK_EN			(1 << 27)
	#घोषणा SATA2_CFG_RX_CLK_EN			(1 << 26)
	#घोषणा SATA2_CFG_POWERUP_RESET			(1 << 25)
	#घोषणा SATA2_CFG_PM_CLK_EN			(1 << 24)
	#घोषणा SATA1_CFG_TX_CLK_EN			(1 << 23)
	#घोषणा SATA1_CFG_RX_CLK_EN			(1 << 22)
	#घोषणा SATA1_CFG_POWERUP_RESET			(1 << 21)
	#घोषणा SATA1_CFG_PM_CLK_EN			(1 << 20)
	#घोषणा SATA0_CFG_TX_CLK_EN			(1 << 19)
	#घोषणा SATA0_CFG_RX_CLK_EN			(1 << 18)
	#घोषणा SATA0_CFG_POWERUP_RESET			(1 << 17)
	#घोषणा SATA0_CFG_PM_CLK_EN			(1 << 16)
	#घोषणा PCIE2_CFG_DEVICE_PRESENT		(1 << 11)
	#घोषणा PCIE2_CFG_POWERUP_RESET			(1 << 10)
	#घोषणा PCIE2_CFG_CORE_CLK_EN			(1 << 9)
	#घोषणा PCIE2_CFG_AUX_CLK_EN			(1 << 8)
	#घोषणा PCIE1_CFG_DEVICE_PRESENT		(1 << 7)
	#घोषणा PCIE1_CFG_POWERUP_RESET			(1 << 6)
	#घोषणा PCIE1_CFG_CORE_CLK_EN			(1 << 5)
	#घोषणा PCIE1_CFG_AUX_CLK_EN			(1 << 4)
	#घोषणा PCIE0_CFG_DEVICE_PRESENT		(1 << 3)
	#घोषणा PCIE0_CFG_POWERUP_RESET			(1 << 2)
	#घोषणा PCIE0_CFG_CORE_CLK_EN			(1 << 1)
	#घोषणा PCIE0_CFG_AUX_CLK_EN			(1 << 0)

#घोषणा PAD_FUNCTION_EN_0				0x650
	#घोषणा PMX_UART0_MASK				(1 << 1)
	#घोषणा PMX_I2C0_MASK				(1 << 2)
	#घोषणा PMX_I2S0_MASK				(1 << 3)
	#घोषणा PMX_SSP0_MASK				(1 << 4)
	#घोषणा PMX_CLCD1_MASK				(1 << 5)
	#घोषणा PMX_EGPIO00_MASK			(1 << 6)
	#घोषणा PMX_EGPIO01_MASK			(1 << 7)
	#घोषणा PMX_EGPIO02_MASK			(1 << 8)
	#घोषणा PMX_EGPIO03_MASK			(1 << 9)
	#घोषणा PMX_EGPIO04_MASK			(1 << 10)
	#घोषणा PMX_EGPIO05_MASK			(1 << 11)
	#घोषणा PMX_EGPIO06_MASK			(1 << 12)
	#घोषणा PMX_EGPIO07_MASK			(1 << 13)
	#घोषणा PMX_EGPIO08_MASK			(1 << 14)
	#घोषणा PMX_EGPIO09_MASK			(1 << 15)
	#घोषणा PMX_SMI_MASK				(1 << 16)
	#घोषणा PMX_न_अंकD8_MASK				(1 << 17)
	#घोषणा PMX_GMIICLK_MASK			(1 << 18)
	#घोषणा PMX_GMIICOL_CRS_XFERER_MIITXCLK_MASK	(1 << 19)
	#घोषणा PMX_RXCLK_RDV_TXEN_D03_MASK		(1 << 20)
	#घोषणा PMX_GMIID47_MASK			(1 << 21)
	#घोषणा PMX_MDC_MDIO_MASK			(1 << 22)
	#घोषणा PMX_MCI_DATA8_15_MASK			(1 << 23)
	#घोषणा PMX_NFAD23_MASK				(1 << 24)
	#घोषणा PMX_NFAD24_MASK				(1 << 25)
	#घोषणा PMX_NFAD25_MASK				(1 << 26)
	#घोषणा PMX_NFCE3_MASK				(1 << 27)
	#घोषणा PMX_NFWPRT3_MASK			(1 << 28)
	#घोषणा PMX_NFRSTPWDWN0_MASK			(1 << 29)
	#घोषणा PMX_NFRSTPWDWN1_MASK			(1 << 30)
	#घोषणा PMX_NFRSTPWDWN2_MASK			(1 << 31)

#घोषणा PAD_FUNCTION_EN_1				0x654
	#घोषणा PMX_NFRSTPWDWN3_MASK			(1 << 0)
	#घोषणा PMX_SMINCS2_MASK			(1 << 1)
	#घोषणा PMX_SMINCS3_MASK			(1 << 2)
	#घोषणा PMX_CLCD2_MASK				(1 << 3)
	#घोषणा PMX_KBD_ROWCOL68_MASK			(1 << 4)
	#घोषणा PMX_EGPIO10_MASK			(1 << 5)
	#घोषणा PMX_EGPIO11_MASK			(1 << 6)
	#घोषणा PMX_EGPIO12_MASK			(1 << 7)
	#घोषणा PMX_EGPIO13_MASK			(1 << 8)
	#घोषणा PMX_EGPIO14_MASK			(1 << 9)
	#घोषणा PMX_EGPIO15_MASK			(1 << 10)
	#घोषणा PMX_UART0_MODEM_MASK			(1 << 11)
	#घोषणा PMX_GPT0_TMR0_MASK			(1 << 12)
	#घोषणा PMX_GPT0_TMR1_MASK			(1 << 13)
	#घोषणा PMX_GPT1_TMR0_MASK			(1 << 14)
	#घोषणा PMX_GPT1_TMR1_MASK			(1 << 15)
	#घोषणा PMX_I2S1_MASK				(1 << 16)
	#घोषणा PMX_KBD_ROWCOL25_MASK			(1 << 17)
	#घोषणा PMX_NFIO8_15_MASK			(1 << 18)
	#घोषणा PMX_KBD_COL1_MASK			(1 << 19)
	#घोषणा PMX_NFCE1_MASK				(1 << 20)
	#घोषणा PMX_KBD_COL0_MASK			(1 << 21)
	#घोषणा PMX_NFCE2_MASK				(1 << 22)
	#घोषणा PMX_KBD_ROW1_MASK			(1 << 23)
	#घोषणा PMX_NFWPRT1_MASK			(1 << 24)
	#घोषणा PMX_KBD_ROW0_MASK			(1 << 25)
	#घोषणा PMX_NFWPRT2_MASK			(1 << 26)
	#घोषणा PMX_MCIDATA0_MASK			(1 << 27)
	#घोषणा PMX_MCIDATA1_MASK			(1 << 28)
	#घोषणा PMX_MCIDATA2_MASK			(1 << 29)
	#घोषणा PMX_MCIDATA3_MASK			(1 << 30)
	#घोषणा PMX_MCIDATA4_MASK			(1 << 31)

#घोषणा PAD_FUNCTION_EN_2				0x658
	#घोषणा PMX_MCIDATA5_MASK			(1 << 0)
	#घोषणा PMX_MCIDATA6_MASK			(1 << 1)
	#घोषणा PMX_MCIDATA7_MASK			(1 << 2)
	#घोषणा PMX_MCIDATA1SD_MASK			(1 << 3)
	#घोषणा PMX_MCIDATA2SD_MASK			(1 << 4)
	#घोषणा PMX_MCIDATA3SD_MASK			(1 << 5)
	#घोषणा PMX_MCIADDR0ALE_MASK			(1 << 6)
	#घोषणा PMX_MCIADDR1CLECLK_MASK			(1 << 7)
	#घोषणा PMX_MCIADDR2_MASK			(1 << 8)
	#घोषणा PMX_MCICECF_MASK			(1 << 9)
	#घोषणा PMX_MCICEXD_MASK			(1 << 10)
	#घोषणा PMX_MCICESDMMC_MASK			(1 << 11)
	#घोषणा PMX_MCICDCF1_MASK			(1 << 12)
	#घोषणा PMX_MCICDCF2_MASK			(1 << 13)
	#घोषणा PMX_MCICDXD_MASK			(1 << 14)
	#घोषणा PMX_MCICDSDMMC_MASK			(1 << 15)
	#घोषणा PMX_MCIDATAसूची_MASK			(1 << 16)
	#घोषणा PMX_MCIDMARQWP_MASK			(1 << 17)
	#घोषणा PMX_MCIIORDRE_MASK			(1 << 18)
	#घोषणा PMX_MCIIOWRWE_MASK			(1 << 19)
	#घोषणा PMX_MCIRESETCF_MASK			(1 << 20)
	#घोषणा PMX_MCICS0CE_MASK			(1 << 21)
	#घोषणा PMX_MCICFINTR_MASK			(1 << 22)
	#घोषणा PMX_MCIIORDY_MASK			(1 << 23)
	#घोषणा PMX_MCICS1_MASK				(1 << 24)
	#घोषणा PMX_MCIDMAACK_MASK			(1 << 25)
	#घोषणा PMX_MCISDCMD_MASK			(1 << 26)
	#घोषणा PMX_MCILEDS_MASK			(1 << 27)
	#घोषणा PMX_TOUCH_XY_MASK			(1 << 28)
	#घोषणा PMX_SSP0_CS0_MASK			(1 << 29)
	#घोषणा PMX_SSP0_CS1_2_MASK			(1 << 30)

#घोषणा PAD_सूचीECTION_SEL_0				0x65C
#घोषणा PAD_सूचीECTION_SEL_1				0x660
#घोषणा PAD_सूचीECTION_SEL_2				0x664

/* combined macros */
#घोषणा PMX_GMII_MASK		(PMX_GMIICLK_MASK |			\
				PMX_GMIICOL_CRS_XFERER_MIITXCLK_MASK |	\
				PMX_RXCLK_RDV_TXEN_D03_MASK |		\
				PMX_GMIID47_MASK | PMX_MDC_MDIO_MASK)

#घोषणा PMX_EGPIO_0_GRP_MASK	(PMX_EGPIO00_MASK | PMX_EGPIO01_MASK |	\
				PMX_EGPIO02_MASK |			\
				PMX_EGPIO03_MASK | PMX_EGPIO04_MASK |	\
				PMX_EGPIO05_MASK | PMX_EGPIO06_MASK |	\
				PMX_EGPIO07_MASK | PMX_EGPIO08_MASK |	\
				PMX_EGPIO09_MASK)
#घोषणा PMX_EGPIO_1_GRP_MASK	(PMX_EGPIO10_MASK | PMX_EGPIO11_MASK |	\
				PMX_EGPIO12_MASK | PMX_EGPIO13_MASK |	\
				PMX_EGPIO14_MASK | PMX_EGPIO15_MASK)

#घोषणा PMX_KEYBOARD_6X6_MASK	(PMX_KBD_ROW0_MASK | PMX_KBD_ROW1_MASK | \
				PMX_KBD_ROWCOL25_MASK | PMX_KBD_COL0_MASK | \
				PMX_KBD_COL1_MASK)

#घोषणा PMX_न_अंकD8BIT_0_MASK	(PMX_न_अंकD8_MASK | PMX_NFAD23_MASK |	\
				PMX_NFAD24_MASK | PMX_NFAD25_MASK |	\
				PMX_NFWPRT3_MASK | PMX_NFRSTPWDWN0_MASK | \
				PMX_NFRSTPWDWN1_MASK | PMX_NFRSTPWDWN2_MASK | \
				PMX_NFCE3_MASK)
#घोषणा PMX_न_अंकD8BIT_1_MASK	PMX_NFRSTPWDWN3_MASK

#घोषणा PMX_न_अंकD16BIT_1_MASK	(PMX_KBD_ROWCOL25_MASK | PMX_NFIO8_15_MASK)
#घोषणा PMX_न_अंकD_4CHIPS_MASK	(PMX_NFCE1_MASK | PMX_NFCE2_MASK |	\
				PMX_NFWPRT1_MASK | PMX_NFWPRT2_MASK |	\
				PMX_KBD_ROW0_MASK | PMX_KBD_ROW1_MASK |	\
				PMX_KBD_COL0_MASK | PMX_KBD_COL1_MASK)

#घोषणा PMX_MCIFALL_1_MASK	0xF8000000
#घोषणा PMX_MCIFALL_2_MASK	0x0FFFFFFF

#घोषणा PMX_PCI_REG1_MASK	(PMX_SMINCS2_MASK | PMX_SMINCS3_MASK |	\
				PMX_CLCD2_MASK | PMX_KBD_ROWCOL68_MASK | \
				PMX_EGPIO_1_GRP_MASK | PMX_GPT0_TMR0_MASK | \
				PMX_GPT0_TMR1_MASK | PMX_GPT1_TMR0_MASK | \
				PMX_GPT1_TMR1_MASK | PMX_I2S1_MASK |	\
				PMX_NFCE2_MASK)
#घोषणा PMX_PCI_REG2_MASK	(PMX_TOUCH_XY_MASK | PMX_SSP0_CS0_MASK | \
				PMX_SSP0_CS1_2_MASK)

#घोषणा PMX_SMII_0_1_2_MASK	(PMX_CLCD2_MASK | PMX_KBD_ROWCOL68_MASK)
#घोषणा PMX_RGMII_REG0_MASK	(PMX_MCI_DATA8_15_MASK |		\
				PMX_GMIICOL_CRS_XFERER_MIITXCLK_MASK |	\
				PMX_GMIID47_MASK)
#घोषणा PMX_RGMII_REG1_MASK	(PMX_KBD_ROWCOL68_MASK | PMX_EGPIO_1_GRP_MASK |\
				PMX_KBD_ROW1_MASK | PMX_NFWPRT1_MASK |	\
				PMX_KBD_ROW0_MASK | PMX_NFWPRT2_MASK)
#घोषणा PMX_RGMII_REG2_MASK	(PMX_TOUCH_XY_MASK | PMX_SSP0_CS0_MASK | \
				PMX_SSP0_CS1_2_MASK)

#घोषणा PCIE_CFG_VAL(x)		(PCIE_SATA##x##_SEL_PCIE |	\
				PCIE##x##_CFG_AUX_CLK_EN |	\
				PCIE##x##_CFG_CORE_CLK_EN |	\
				PCIE##x##_CFG_POWERUP_RESET |	\
				PCIE##x##_CFG_DEVICE_PRESENT)
#घोषणा SATA_CFG_VAL(x)		(PCIE_SATA##x##_SEL_SATA |	\
				SATA##x##_CFG_PM_CLK_EN |	\
				SATA##x##_CFG_POWERUP_RESET |	\
				SATA##x##_CFG_RX_CLK_EN |	\
				SATA##x##_CFG_TX_CLK_EN)

/* Pad multiplexing क्रम i2c0 device */
अटल स्थिर अचिन्हित i2c0_pins[] = अणु 102, 103 पूर्ण;
अटल काष्ठा spear_muxreg i2c0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2C0_MASK,
		.val = PMX_I2C0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_I2C0_MASK,
		.val = PMX_I2C0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c0_modemux[] = अणु
	अणु
		.muxregs = i2c0_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c0_pingroup = अणु
	.name = "i2c0_grp",
	.pins = i2c0_pins,
	.npins = ARRAY_SIZE(i2c0_pins),
	.modemuxs = i2c0_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c0_grps[] = अणु "i2c0_grp" पूर्ण;
अटल काष्ठा spear_function i2c0_function = अणु
	.name = "i2c0",
	.groups = i2c0_grps,
	.ngroups = ARRAY_SIZE(i2c0_grps),
पूर्ण;

/* Pad multiplexing क्रम ssp0 device */
अटल स्थिर अचिन्हित ssp0_pins[] = अणु 109, 110, 111, 112 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_SSP0_MASK,
		.val = PMX_SSP0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_SSP0_MASK,
		.val = PMX_SSP0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp0_modemux[] = अणु
	अणु
		.muxregs = ssp0_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp0_pingroup = अणु
	.name = "ssp0_grp",
	.pins = ssp0_pins,
	.npins = ARRAY_SIZE(ssp0_pins),
	.modemuxs = ssp0_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp0_modemux),
पूर्ण;

/* Pad multiplexing क्रम ssp0_cs0 device */
अटल स्थिर अचिन्हित ssp0_cs0_pins[] = अणु 96 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_cs0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_SSP0_CS0_MASK,
		.val = PMX_SSP0_CS0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_SSP0_CS0_MASK,
		.val = PMX_SSP0_CS0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp0_cs0_modemux[] = अणु
	अणु
		.muxregs = ssp0_cs0_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp0_cs0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp0_cs0_pingroup = अणु
	.name = "ssp0_cs0_grp",
	.pins = ssp0_cs0_pins,
	.npins = ARRAY_SIZE(ssp0_cs0_pins),
	.modemuxs = ssp0_cs0_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp0_cs0_modemux),
पूर्ण;

/* ssp0_cs1_2 device */
अटल स्थिर अचिन्हित ssp0_cs1_2_pins[] = अणु 94, 95 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_cs1_2_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_SSP0_CS1_2_MASK,
		.val = PMX_SSP0_CS1_2_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_SSP0_CS1_2_MASK,
		.val = PMX_SSP0_CS1_2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp0_cs1_2_modemux[] = अणु
	अणु
		.muxregs = ssp0_cs1_2_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp0_cs1_2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp0_cs1_2_pingroup = अणु
	.name = "ssp0_cs1_2_grp",
	.pins = ssp0_cs1_2_pins,
	.npins = ARRAY_SIZE(ssp0_cs1_2_pins),
	.modemuxs = ssp0_cs1_2_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp0_cs1_2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp0_grps[] = अणु "ssp0_grp", "ssp0_cs0_grp",
	"ssp0_cs1_2_grp" पूर्ण;
अटल काष्ठा spear_function ssp0_function = अणु
	.name = "ssp0",
	.groups = ssp0_grps,
	.ngroups = ARRAY_SIZE(ssp0_grps),
पूर्ण;

/* Pad multiplexing क्रम i2s0 device */
अटल स्थिर अचिन्हित i2s0_pins[] = अणु 104, 105, 106, 107, 108 पूर्ण;
अटल काष्ठा spear_muxreg i2s0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2S0_MASK,
		.val = PMX_I2S0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_I2S0_MASK,
		.val = PMX_I2S0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2s0_modemux[] = अणु
	अणु
		.muxregs = i2s0_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2s0_pingroup = अणु
	.name = "i2s0_grp",
	.pins = i2s0_pins,
	.npins = ARRAY_SIZE(i2s0_pins),
	.modemuxs = i2s0_modemux,
	.nmodemuxs = ARRAY_SIZE(i2s0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2s0_grps[] = अणु "i2s0_grp" पूर्ण;
अटल काष्ठा spear_function i2s0_function = अणु
	.name = "i2s0",
	.groups = i2s0_grps,
	.ngroups = ARRAY_SIZE(i2s0_grps),
पूर्ण;

/* Pad multiplexing क्रम i2s1 device */
अटल स्थिर अचिन्हित i2s1_pins[] = अणु 0, 1, 2, 3 पूर्ण;
अटल काष्ठा spear_muxreg i2s1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_I2S1_MASK,
		.val = PMX_I2S1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_I2S1_MASK,
		.val = PMX_I2S1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2s1_modemux[] = अणु
	अणु
		.muxregs = i2s1_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2s1_pingroup = अणु
	.name = "i2s1_grp",
	.pins = i2s1_pins,
	.npins = ARRAY_SIZE(i2s1_pins),
	.modemuxs = i2s1_modemux,
	.nmodemuxs = ARRAY_SIZE(i2s1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2s1_grps[] = अणु "i2s1_grp" पूर्ण;
अटल काष्ठा spear_function i2s1_function = अणु
	.name = "i2s1",
	.groups = i2s1_grps,
	.ngroups = ARRAY_SIZE(i2s1_grps),
पूर्ण;

/* Pad multiplexing क्रम clcd device */
अटल स्थिर अचिन्हित clcd_pins[] = अणु 113, 114, 115, 116, 117, 118, 119, 120,
	121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
	135, 136, 137, 138, 139, 140, 141, 142 पूर्ण;
अटल काष्ठा spear_muxreg clcd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_CLCD1_MASK,
		.val = PMX_CLCD1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_CLCD1_MASK,
		.val = PMX_CLCD1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux clcd_modemux[] = अणु
	अणु
		.muxregs = clcd_muxreg,
		.nmuxregs = ARRAY_SIZE(clcd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup clcd_pingroup = अणु
	.name = "clcd_grp",
	.pins = clcd_pins,
	.npins = ARRAY_SIZE(clcd_pins),
	.modemuxs = clcd_modemux,
	.nmodemuxs = ARRAY_SIZE(clcd_modemux),
पूर्ण;

अटल स्थिर अचिन्हित clcd_high_res_pins[] = अणु 30, 31, 32, 33, 34, 35, 36, 37,
	38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53 पूर्ण;
अटल काष्ठा spear_muxreg clcd_high_res_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_CLCD2_MASK,
		.val = PMX_CLCD2_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_CLCD2_MASK,
		.val = PMX_CLCD2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux clcd_high_res_modemux[] = अणु
	अणु
		.muxregs = clcd_high_res_muxreg,
		.nmuxregs = ARRAY_SIZE(clcd_high_res_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup clcd_high_res_pingroup = अणु
	.name = "clcd_high_res_grp",
	.pins = clcd_high_res_pins,
	.npins = ARRAY_SIZE(clcd_high_res_pins),
	.modemuxs = clcd_high_res_modemux,
	.nmodemuxs = ARRAY_SIZE(clcd_high_res_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर clcd_grps[] = अणु "clcd_grp", "clcd_high_res_grp" पूर्ण;
अटल काष्ठा spear_function clcd_function = अणु
	.name = "clcd",
	.groups = clcd_grps,
	.ngroups = ARRAY_SIZE(clcd_grps),
पूर्ण;

अटल स्थिर अचिन्हित arm_gpio_pins[] = अणु 18, 19, 20, 21, 22, 23, 143, 144, 145,
	146, 147, 148, 149, 150, 151, 152 पूर्ण;
अटल काष्ठा spear_muxreg arm_gpio_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_EGPIO_0_GRP_MASK,
		.val = PMX_EGPIO_0_GRP_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_EGPIO_1_GRP_MASK,
		.val = PMX_EGPIO_1_GRP_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_EGPIO_0_GRP_MASK,
		.val = PMX_EGPIO_0_GRP_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_EGPIO_1_GRP_MASK,
		.val = PMX_EGPIO_1_GRP_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux arm_gpio_modemux[] = अणु
	अणु
		.muxregs = arm_gpio_muxreg,
		.nmuxregs = ARRAY_SIZE(arm_gpio_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup arm_gpio_pingroup = अणु
	.name = "arm_gpio_grp",
	.pins = arm_gpio_pins,
	.npins = ARRAY_SIZE(arm_gpio_pins),
	.modemuxs = arm_gpio_modemux,
	.nmodemuxs = ARRAY_SIZE(arm_gpio_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर arm_gpio_grps[] = अणु "arm_gpio_grp" पूर्ण;
अटल काष्ठा spear_function arm_gpio_function = अणु
	.name = "arm_gpio",
	.groups = arm_gpio_grps,
	.ngroups = ARRAY_SIZE(arm_gpio_grps),
पूर्ण;

/* Pad multiplexing क्रम smi 2 chips device */
अटल स्थिर अचिन्हित smi_2_chips_pins[] = अणु 153, 154, 155, 156, 157 पूर्ण;
अटल काष्ठा spear_muxreg smi_2_chips_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_SMI_MASK,
		.val = PMX_SMI_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_SMI_MASK,
		.val = PMX_SMI_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux smi_2_chips_modemux[] = अणु
	अणु
		.muxregs = smi_2_chips_muxreg,
		.nmuxregs = ARRAY_SIZE(smi_2_chips_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup smi_2_chips_pingroup = अणु
	.name = "smi_2_chips_grp",
	.pins = smi_2_chips_pins,
	.npins = ARRAY_SIZE(smi_2_chips_pins),
	.modemuxs = smi_2_chips_modemux,
	.nmodemuxs = ARRAY_SIZE(smi_2_chips_modemux),
पूर्ण;

अटल स्थिर अचिन्हित smi_4_chips_pins[] = अणु 54, 55 पूर्ण;
अटल काष्ठा spear_muxreg smi_4_chips_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_SMI_MASK,
		.val = PMX_SMI_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
		.val = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_SMI_MASK,
		.val = PMX_SMI_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
		.val = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux smi_4_chips_modemux[] = अणु
	अणु
		.muxregs = smi_4_chips_muxreg,
		.nmuxregs = ARRAY_SIZE(smi_4_chips_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup smi_4_chips_pingroup = अणु
	.name = "smi_4_chips_grp",
	.pins = smi_4_chips_pins,
	.npins = ARRAY_SIZE(smi_4_chips_pins),
	.modemuxs = smi_4_chips_modemux,
	.nmodemuxs = ARRAY_SIZE(smi_4_chips_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर smi_grps[] = अणु "smi_2_chips_grp", "smi_4_chips_grp" पूर्ण;
अटल काष्ठा spear_function smi_function = अणु
	.name = "smi",
	.groups = smi_grps,
	.ngroups = ARRAY_SIZE(smi_grps),
पूर्ण;

/* Pad multiplexing क्रम gmii device */
अटल स्थिर अचिन्हित gmii_pins[] = अणु 173, 174, 175, 176, 177, 178, 179, 180,
	181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
	195, 196, 197, 198, 199, 200 पूर्ण;
अटल काष्ठा spear_muxreg gmii_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_GMII_MASK,
		.val = PMX_GMII_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_GMII_MASK,
		.val = PMX_GMII_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gmii_modemux[] = अणु
	अणु
		.muxregs = gmii_muxreg,
		.nmuxregs = ARRAY_SIZE(gmii_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gmii_pingroup = अणु
	.name = "gmii_grp",
	.pins = gmii_pins,
	.npins = ARRAY_SIZE(gmii_pins),
	.modemuxs = gmii_modemux,
	.nmodemuxs = ARRAY_SIZE(gmii_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gmii_grps[] = अणु "gmii_grp" पूर्ण;
अटल काष्ठा spear_function gmii_function = अणु
	.name = "gmii",
	.groups = gmii_grps,
	.ngroups = ARRAY_SIZE(gmii_grps),
पूर्ण;

/* Pad multiplexing क्रम rgmii device */
अटल स्थिर अचिन्हित rgmii_pins[] = अणु 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
	28, 29, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 175,
	180, 181, 182, 183, 185, 188, 193, 194, 195, 196, 197, 198, 211, 212 पूर्ण;
अटल काष्ठा spear_muxreg rgmii_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_RGMII_REG0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_RGMII_REG1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_RGMII_REG2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_RGMII_REG0_MASK,
		.val = PMX_RGMII_REG0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_RGMII_REG1_MASK,
		.val = PMX_RGMII_REG1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_RGMII_REG2_MASK,
		.val = PMX_RGMII_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux rgmii_modemux[] = अणु
	अणु
		.muxregs = rgmii_muxreg,
		.nmuxregs = ARRAY_SIZE(rgmii_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup rgmii_pingroup = अणु
	.name = "rgmii_grp",
	.pins = rgmii_pins,
	.npins = ARRAY_SIZE(rgmii_pins),
	.modemuxs = rgmii_modemux,
	.nmodemuxs = ARRAY_SIZE(rgmii_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर rgmii_grps[] = अणु "rgmii_grp" पूर्ण;
अटल काष्ठा spear_function rgmii_function = अणु
	.name = "rgmii",
	.groups = rgmii_grps,
	.ngroups = ARRAY_SIZE(rgmii_grps),
पूर्ण;

/* Pad multiplexing क्रम smii_0_1_2 device */
अटल स्थिर अचिन्हित smii_0_1_2_pins[] = अणु 24, 25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54, 55 पूर्ण;
अटल काष्ठा spear_muxreg smii_0_1_2_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_SMII_0_1_2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_SMII_0_1_2_MASK,
		.val = PMX_SMII_0_1_2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux smii_0_1_2_modemux[] = अणु
	अणु
		.muxregs = smii_0_1_2_muxreg,
		.nmuxregs = ARRAY_SIZE(smii_0_1_2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup smii_0_1_2_pingroup = अणु
	.name = "smii_0_1_2_grp",
	.pins = smii_0_1_2_pins,
	.npins = ARRAY_SIZE(smii_0_1_2_pins),
	.modemuxs = smii_0_1_2_modemux,
	.nmodemuxs = ARRAY_SIZE(smii_0_1_2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर smii_0_1_2_grps[] = अणु "smii_0_1_2_grp" पूर्ण;
अटल काष्ठा spear_function smii_0_1_2_function = अणु
	.name = "smii_0_1_2",
	.groups = smii_0_1_2_grps,
	.ngroups = ARRAY_SIZE(smii_0_1_2_grps),
पूर्ण;

/* Pad multiplexing क्रम ras_mii_txclk device */
अटल स्थिर अचिन्हित ras_mii_txclk_pins[] = अणु 98, 99 पूर्ण;
अटल काष्ठा spear_muxreg ras_mii_txclk_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_NFCE2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_NFCE2_MASK,
		.val = PMX_NFCE2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ras_mii_txclk_modemux[] = अणु
	अणु
		.muxregs = ras_mii_txclk_muxreg,
		.nmuxregs = ARRAY_SIZE(ras_mii_txclk_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ras_mii_txclk_pingroup = अणु
	.name = "ras_mii_txclk_grp",
	.pins = ras_mii_txclk_pins,
	.npins = ARRAY_SIZE(ras_mii_txclk_pins),
	.modemuxs = ras_mii_txclk_modemux,
	.nmodemuxs = ARRAY_SIZE(ras_mii_txclk_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर ras_mii_txclk_grps[] = अणु "ras_mii_txclk_grp" पूर्ण;
अटल काष्ठा spear_function ras_mii_txclk_function = अणु
	.name = "ras_mii_txclk",
	.groups = ras_mii_txclk_grps,
	.ngroups = ARRAY_SIZE(ras_mii_txclk_grps),
पूर्ण;

/* Pad multiplexing क्रम nand 8bit device (cs0 only) */
अटल स्थिर अचिन्हित nand_8bit_pins[] = अणु 56, 57, 58, 59, 60, 61, 62, 63, 64,
	65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82,
	83, 84, 85, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
	170, 171, 172, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211,
	212 पूर्ण;
अटल काष्ठा spear_muxreg nand_8bit_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_न_अंकD8BIT_0_MASK,
		.val = PMX_न_अंकD8BIT_0_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_न_अंकD8BIT_1_MASK,
		.val = PMX_न_अंकD8BIT_1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_न_अंकD8BIT_0_MASK,
		.val = PMX_न_अंकD8BIT_0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_न_अंकD8BIT_1_MASK,
		.val = PMX_न_अंकD8BIT_1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux nand_8bit_modemux[] = अणु
	अणु
		.muxregs = nand_8bit_muxreg,
		.nmuxregs = ARRAY_SIZE(nand_8bit_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup nand_8bit_pingroup = अणु
	.name = "nand_8bit_grp",
	.pins = nand_8bit_pins,
	.npins = ARRAY_SIZE(nand_8bit_pins),
	.modemuxs = nand_8bit_modemux,
	.nmodemuxs = ARRAY_SIZE(nand_8bit_modemux),
पूर्ण;

/* Pad multiplexing क्रम nand 16bit device */
अटल स्थिर अचिन्हित nand_16bit_pins[] = अणु 201, 202, 203, 204, 207, 208, 209,
	210 पूर्ण;
अटल काष्ठा spear_muxreg nand_16bit_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_न_अंकD16BIT_1_MASK,
		.val = PMX_न_अंकD16BIT_1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_न_अंकD16BIT_1_MASK,
		.val = PMX_न_अंकD16BIT_1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux nand_16bit_modemux[] = अणु
	अणु
		.muxregs = nand_16bit_muxreg,
		.nmuxregs = ARRAY_SIZE(nand_16bit_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup nand_16bit_pingroup = अणु
	.name = "nand_16bit_grp",
	.pins = nand_16bit_pins,
	.npins = ARRAY_SIZE(nand_16bit_pins),
	.modemuxs = nand_16bit_modemux,
	.nmodemuxs = ARRAY_SIZE(nand_16bit_modemux),
पूर्ण;

/* Pad multiplexing क्रम nand 4 chips */
अटल स्थिर अचिन्हित nand_4_chips_pins[] = अणु 205, 206, 211, 212 पूर्ण;
अटल काष्ठा spear_muxreg nand_4_chips_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_न_अंकD_4CHIPS_MASK,
		.val = PMX_न_अंकD_4CHIPS_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_न_अंकD_4CHIPS_MASK,
		.val = PMX_न_अंकD_4CHIPS_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux nand_4_chips_modemux[] = अणु
	अणु
		.muxregs = nand_4_chips_muxreg,
		.nmuxregs = ARRAY_SIZE(nand_4_chips_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup nand_4_chips_pingroup = अणु
	.name = "nand_4_chips_grp",
	.pins = nand_4_chips_pins,
	.npins = ARRAY_SIZE(nand_4_chips_pins),
	.modemuxs = nand_4_chips_modemux,
	.nmodemuxs = ARRAY_SIZE(nand_4_chips_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर nand_grps[] = अणु "nand_8bit_grp", "nand_16bit_grp",
	"nand_4_chips_grp" पूर्ण;
अटल काष्ठा spear_function nand_function = अणु
	.name = "nand",
	.groups = nand_grps,
	.ngroups = ARRAY_SIZE(nand_grps),
पूर्ण;

/* Pad multiplexing क्रम keyboard_6x6 device */
अटल स्थिर अचिन्हित keyboard_6x6_pins[] = अणु 201, 202, 203, 204, 205, 206, 207,
	208, 209, 210, 211, 212 पूर्ण;
अटल काष्ठा spear_muxreg keyboard_6x6_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_KEYBOARD_6X6_MASK | PMX_NFIO8_15_MASK |
			PMX_NFCE1_MASK | PMX_NFCE2_MASK | PMX_NFWPRT1_MASK |
			PMX_NFWPRT2_MASK,
		.val = PMX_KEYBOARD_6X6_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux keyboard_6x6_modemux[] = अणु
	अणु
		.muxregs = keyboard_6x6_muxreg,
		.nmuxregs = ARRAY_SIZE(keyboard_6x6_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup keyboard_6x6_pingroup = अणु
	.name = "keyboard_6x6_grp",
	.pins = keyboard_6x6_pins,
	.npins = ARRAY_SIZE(keyboard_6x6_pins),
	.modemuxs = keyboard_6x6_modemux,
	.nmodemuxs = ARRAY_SIZE(keyboard_6x6_modemux),
पूर्ण;

/* Pad multiplexing क्रम keyboard_rowcol6_8 device */
अटल स्थिर अचिन्हित keyboard_rowcol6_8_pins[] = अणु 24, 25, 26, 27, 28, 29 पूर्ण;
अटल काष्ठा spear_muxreg keyboard_rowcol6_8_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_ROWCOL68_MASK,
		.val = PMX_KBD_ROWCOL68_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_KBD_ROWCOL68_MASK,
		.val = PMX_KBD_ROWCOL68_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux keyboard_rowcol6_8_modemux[] = अणु
	अणु
		.muxregs = keyboard_rowcol6_8_muxreg,
		.nmuxregs = ARRAY_SIZE(keyboard_rowcol6_8_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup keyboard_rowcol6_8_pingroup = अणु
	.name = "keyboard_rowcol6_8_grp",
	.pins = keyboard_rowcol6_8_pins,
	.npins = ARRAY_SIZE(keyboard_rowcol6_8_pins),
	.modemuxs = keyboard_rowcol6_8_modemux,
	.nmodemuxs = ARRAY_SIZE(keyboard_rowcol6_8_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर keyboard_grps[] = अणु "keyboard_6x6_grp",
	"keyboard_rowcol6_8_grp" पूर्ण;
अटल काष्ठा spear_function keyboard_function = अणु
	.name = "keyboard",
	.groups = keyboard_grps,
	.ngroups = ARRAY_SIZE(keyboard_grps),
पूर्ण;

/* Pad multiplexing क्रम uart0 device */
अटल स्थिर अचिन्हित uart0_pins[] = अणु 100, 101 पूर्ण;
अटल काष्ठा spear_muxreg uart0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_UART0_MASK,
		.val = PMX_UART0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_UART0_MASK,
		.val = PMX_UART0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart0_modemux[] = अणु
	अणु
		.muxregs = uart0_muxreg,
		.nmuxregs = ARRAY_SIZE(uart0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart0_pingroup = अणु
	.name = "uart0_grp",
	.pins = uart0_pins,
	.npins = ARRAY_SIZE(uart0_pins),
	.modemuxs = uart0_modemux,
	.nmodemuxs = ARRAY_SIZE(uart0_modemux),
पूर्ण;

/* Pad multiplexing क्रम uart0_modem device */
अटल स्थिर अचिन्हित uart0_modem_pins[] = अणु 12, 13, 14, 15, 16, 17 पूर्ण;
अटल काष्ठा spear_muxreg uart0_modem_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_UART0_MODEM_MASK,
		.val = PMX_UART0_MODEM_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_UART0_MODEM_MASK,
		.val = PMX_UART0_MODEM_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart0_modem_modemux[] = अणु
	अणु
		.muxregs = uart0_modem_muxreg,
		.nmuxregs = ARRAY_SIZE(uart0_modem_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart0_modem_pingroup = अणु
	.name = "uart0_modem_grp",
	.pins = uart0_modem_pins,
	.npins = ARRAY_SIZE(uart0_modem_pins),
	.modemuxs = uart0_modem_modemux,
	.nmodemuxs = ARRAY_SIZE(uart0_modem_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart0_grps[] = अणु "uart0_grp", "uart0_modem_grp" पूर्ण;
अटल काष्ठा spear_function uart0_function = अणु
	.name = "uart0",
	.groups = uart0_grps,
	.ngroups = ARRAY_SIZE(uart0_grps),
पूर्ण;

/* Pad multiplexing क्रम gpt0_पंचांगr0 device */
अटल स्थिर अचिन्हित gpt0_पंचांगr0_pins[] = अणु 10, 11 पूर्ण;
अटल काष्ठा spear_muxreg gpt0_पंचांगr0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT0_TMR0_MASK,
		.val = PMX_GPT0_TMR0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_GPT0_TMR0_MASK,
		.val = PMX_GPT0_TMR0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpt0_पंचांगr0_modemux[] = अणु
	अणु
		.muxregs = gpt0_पंचांगr0_muxreg,
		.nmuxregs = ARRAY_SIZE(gpt0_पंचांगr0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpt0_पंचांगr0_pingroup = अणु
	.name = "gpt0_tmr0_grp",
	.pins = gpt0_पंचांगr0_pins,
	.npins = ARRAY_SIZE(gpt0_पंचांगr0_pins),
	.modemuxs = gpt0_पंचांगr0_modemux,
	.nmodemuxs = ARRAY_SIZE(gpt0_पंचांगr0_modemux),
पूर्ण;

/* Pad multiplexing क्रम gpt0_पंचांगr1 device */
अटल स्थिर अचिन्हित gpt0_पंचांगr1_pins[] = अणु 8, 9 पूर्ण;
अटल काष्ठा spear_muxreg gpt0_पंचांगr1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT0_TMR1_MASK,
		.val = PMX_GPT0_TMR1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_GPT0_TMR1_MASK,
		.val = PMX_GPT0_TMR1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpt0_पंचांगr1_modemux[] = अणु
	अणु
		.muxregs = gpt0_पंचांगr1_muxreg,
		.nmuxregs = ARRAY_SIZE(gpt0_पंचांगr1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpt0_पंचांगr1_pingroup = अणु
	.name = "gpt0_tmr1_grp",
	.pins = gpt0_पंचांगr1_pins,
	.npins = ARRAY_SIZE(gpt0_पंचांगr1_pins),
	.modemuxs = gpt0_पंचांगr1_modemux,
	.nmodemuxs = ARRAY_SIZE(gpt0_पंचांगr1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpt0_grps[] = अणु "gpt0_tmr0_grp", "gpt0_tmr1_grp" पूर्ण;
अटल काष्ठा spear_function gpt0_function = अणु
	.name = "gpt0",
	.groups = gpt0_grps,
	.ngroups = ARRAY_SIZE(gpt0_grps),
पूर्ण;

/* Pad multiplexing क्रम gpt1_पंचांगr0 device */
अटल स्थिर अचिन्हित gpt1_पंचांगr0_pins[] = अणु 6, 7 पूर्ण;
अटल काष्ठा spear_muxreg gpt1_पंचांगr0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT1_TMR0_MASK,
		.val = PMX_GPT1_TMR0_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_GPT1_TMR0_MASK,
		.val = PMX_GPT1_TMR0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpt1_पंचांगr0_modemux[] = अणु
	अणु
		.muxregs = gpt1_पंचांगr0_muxreg,
		.nmuxregs = ARRAY_SIZE(gpt1_पंचांगr0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpt1_पंचांगr0_pingroup = अणु
	.name = "gpt1_tmr0_grp",
	.pins = gpt1_पंचांगr0_pins,
	.npins = ARRAY_SIZE(gpt1_पंचांगr0_pins),
	.modemuxs = gpt1_पंचांगr0_modemux,
	.nmodemuxs = ARRAY_SIZE(gpt1_पंचांगr0_modemux),
पूर्ण;

/* Pad multiplexing क्रम gpt1_पंचांगr1 device */
अटल स्थिर अचिन्हित gpt1_पंचांगr1_pins[] = अणु 4, 5 पूर्ण;
अटल काष्ठा spear_muxreg gpt1_पंचांगr1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT1_TMR1_MASK,
		.val = PMX_GPT1_TMR1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_GPT1_TMR1_MASK,
		.val = PMX_GPT1_TMR1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpt1_पंचांगr1_modemux[] = अणु
	अणु
		.muxregs = gpt1_पंचांगr1_muxreg,
		.nmuxregs = ARRAY_SIZE(gpt1_पंचांगr1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpt1_पंचांगr1_pingroup = अणु
	.name = "gpt1_tmr1_grp",
	.pins = gpt1_पंचांगr1_pins,
	.npins = ARRAY_SIZE(gpt1_पंचांगr1_pins),
	.modemuxs = gpt1_पंचांगr1_modemux,
	.nmodemuxs = ARRAY_SIZE(gpt1_पंचांगr1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpt1_grps[] = अणु "gpt1_tmr1_grp", "gpt1_tmr0_grp" पूर्ण;
अटल काष्ठा spear_function gpt1_function = अणु
	.name = "gpt1",
	.groups = gpt1_grps,
	.ngroups = ARRAY_SIZE(gpt1_grps),
पूर्ण;

/* Pad multiplexing क्रम mcअगर device */
अटल स्थिर अचिन्हित mcअगर_pins[] = अणु 86, 87, 88, 89, 90, 91, 92, 93, 213, 214,
	215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
	229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
	243, 244, 245 पूर्ण;
#घोषणा MCIF_MUXREG						\
	अणु							\
		.reg = PAD_FUNCTION_EN_0,			\
		.mask = PMX_MCI_DATA8_15_MASK,			\
		.val = PMX_MCI_DATA8_15_MASK,			\
	पूर्ण, अणु							\
		.reg = PAD_FUNCTION_EN_1,			\
		.mask = PMX_MCIFALL_1_MASK | PMX_NFWPRT1_MASK |	\
			PMX_NFWPRT2_MASK,			\
		.val = PMX_MCIFALL_1_MASK,			\
	पूर्ण, अणु							\
		.reg = PAD_FUNCTION_EN_2,			\
		.mask = PMX_MCIFALL_2_MASK,			\
		.val = PMX_MCIFALL_2_MASK,			\
	पूर्ण, अणु							\
		.reg = PAD_सूचीECTION_SEL_0,			\
		.mask = PMX_MCI_DATA8_15_MASK,			\
		.val = PMX_MCI_DATA8_15_MASK,			\
	पूर्ण, अणु							\
		.reg = PAD_सूचीECTION_SEL_1,			\
		.mask = PMX_MCIFALL_1_MASK | PMX_NFWPRT1_MASK |	\
			PMX_NFWPRT2_MASK,			\
		.val = PMX_MCIFALL_1_MASK | PMX_NFWPRT1_MASK |  \
			PMX_NFWPRT2_MASK,			\
	पूर्ण, अणु							\
		.reg = PAD_सूचीECTION_SEL_2,			\
		.mask = PMX_MCIFALL_2_MASK,			\
		.val = PMX_MCIFALL_2_MASK,			\
	पूर्ण

/* sdhci device */
अटल काष्ठा spear_muxreg sdhci_muxreg[] = अणु
	MCIF_MUXREG,
	अणु
		.reg = PERIP_CFG,
		.mask = MCIF_SEL_MASK,
		.val = MCIF_SEL_SD,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sdhci_modemux[] = अणु
	अणु
		.muxregs = sdhci_muxreg,
		.nmuxregs = ARRAY_SIZE(sdhci_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sdhci_pingroup = अणु
	.name = "sdhci_grp",
	.pins = mcअगर_pins,
	.npins = ARRAY_SIZE(mcअगर_pins),
	.modemuxs = sdhci_modemux,
	.nmodemuxs = ARRAY_SIZE(sdhci_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर sdhci_grps[] = अणु "sdhci_grp" पूर्ण;
अटल काष्ठा spear_function sdhci_function = अणु
	.name = "sdhci",
	.groups = sdhci_grps,
	.ngroups = ARRAY_SIZE(sdhci_grps),
पूर्ण;

/* cf device */
अटल काष्ठा spear_muxreg cf_muxreg[] = अणु
	MCIF_MUXREG,
	अणु
		.reg = PERIP_CFG,
		.mask = MCIF_SEL_MASK,
		.val = MCIF_SEL_CF,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cf_modemux[] = अणु
	अणु
		.muxregs = cf_muxreg,
		.nmuxregs = ARRAY_SIZE(cf_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cf_pingroup = अणु
	.name = "cf_grp",
	.pins = mcअगर_pins,
	.npins = ARRAY_SIZE(mcअगर_pins),
	.modemuxs = cf_modemux,
	.nmodemuxs = ARRAY_SIZE(cf_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cf_grps[] = अणु "cf_grp" पूर्ण;
अटल काष्ठा spear_function cf_function = अणु
	.name = "cf",
	.groups = cf_grps,
	.ngroups = ARRAY_SIZE(cf_grps),
पूर्ण;

/* xd device */
अटल काष्ठा spear_muxreg xd_muxreg[] = अणु
	MCIF_MUXREG,
	अणु
		.reg = PERIP_CFG,
		.mask = MCIF_SEL_MASK,
		.val = MCIF_SEL_XD,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux xd_modemux[] = अणु
	अणु
		.muxregs = xd_muxreg,
		.nmuxregs = ARRAY_SIZE(xd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup xd_pingroup = अणु
	.name = "xd_grp",
	.pins = mcअगर_pins,
	.npins = ARRAY_SIZE(mcअगर_pins),
	.modemuxs = xd_modemux,
	.nmodemuxs = ARRAY_SIZE(xd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर xd_grps[] = अणु "xd_grp" पूर्ण;
अटल काष्ठा spear_function xd_function = अणु
	.name = "xd",
	.groups = xd_grps,
	.ngroups = ARRAY_SIZE(xd_grps),
पूर्ण;

/* Pad multiplexing क्रम touch_xy device */
अटल स्थिर अचिन्हित touch_xy_pins[] = अणु 97 पूर्ण;
अटल काष्ठा spear_muxreg touch_xy_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_TOUCH_XY_MASK,
		.val = PMX_TOUCH_XY_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_TOUCH_XY_MASK,
		.val = PMX_TOUCH_XY_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux touch_xy_modemux[] = अणु
	अणु
		.muxregs = touch_xy_muxreg,
		.nmuxregs = ARRAY_SIZE(touch_xy_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup touch_xy_pingroup = अणु
	.name = "touch_xy_grp",
	.pins = touch_xy_pins,
	.npins = ARRAY_SIZE(touch_xy_pins),
	.modemuxs = touch_xy_modemux,
	.nmodemuxs = ARRAY_SIZE(touch_xy_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर touch_xy_grps[] = अणु "touch_xy_grp" पूर्ण;
अटल काष्ठा spear_function touch_xy_function = अणु
	.name = "touchscreen",
	.groups = touch_xy_grps,
	.ngroups = ARRAY_SIZE(touch_xy_grps),
पूर्ण;

/* Pad multiplexing क्रम uart1 device */
/* Muxed with I2C */
अटल स्थिर अचिन्हित uart1_dis_i2c_pins[] = अणु 102, 103 पूर्ण;
अटल काष्ठा spear_muxreg uart1_dis_i2c_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2C0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_I2C0_MASK,
		.val = PMX_I2C0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_dis_i2c_modemux[] = अणु
	अणु
		.muxregs = uart1_dis_i2c_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_dis_i2c_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart_1_dis_i2c_pingroup = अणु
	.name = "uart1_disable_i2c_grp",
	.pins = uart1_dis_i2c_pins,
	.npins = ARRAY_SIZE(uart1_dis_i2c_pins),
	.modemuxs = uart1_dis_i2c_modemux,
	.nmodemuxs = ARRAY_SIZE(uart1_dis_i2c_modemux),
पूर्ण;

/* Muxed with SD/MMC */
अटल स्थिर अचिन्हित uart1_dis_sd_pins[] = अणु 214, 215 पूर्ण;
अटल काष्ठा spear_muxreg uart1_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_MCIDATA1_MASK |
			PMX_MCIDATA2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_MCIDATA1_MASK |
			PMX_MCIDATA2_MASK,
		.val = PMX_MCIDATA1_MASK |
			PMX_MCIDATA2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_dis_sd_modemux[] = अणु
	अणु
		.muxregs = uart1_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart_1_dis_sd_pingroup = अणु
	.name = "uart1_disable_sd_grp",
	.pins = uart1_dis_sd_pins,
	.npins = ARRAY_SIZE(uart1_dis_sd_pins),
	.modemuxs = uart1_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(uart1_dis_sd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart1_grps[] = अणु "uart1_disable_i2c_grp",
	"uart1_disable_sd_grp" पूर्ण;
अटल काष्ठा spear_function uart1_function = अणु
	.name = "uart1",
	.groups = uart1_grps,
	.ngroups = ARRAY_SIZE(uart1_grps),
पूर्ण;

/* Pad multiplexing क्रम uart2_3 device */
अटल स्थिर अचिन्हित uart2_3_pins[] = अणु 104, 105, 106, 107 पूर्ण;
अटल काष्ठा spear_muxreg uart2_3_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2S0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_I2S0_MASK,
		.val = PMX_I2S0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart2_3_modemux[] = अणु
	अणु
		.muxregs = uart2_3_muxreg,
		.nmuxregs = ARRAY_SIZE(uart2_3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart_2_3_pingroup = अणु
	.name = "uart2_3_grp",
	.pins = uart2_3_pins,
	.npins = ARRAY_SIZE(uart2_3_pins),
	.modemuxs = uart2_3_modemux,
	.nmodemuxs = ARRAY_SIZE(uart2_3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart2_3_grps[] = अणु "uart2_3_grp" पूर्ण;
अटल काष्ठा spear_function uart2_3_function = अणु
	.name = "uart2_3",
	.groups = uart2_3_grps,
	.ngroups = ARRAY_SIZE(uart2_3_grps),
पूर्ण;

/* Pad multiplexing क्रम uart4 device */
अटल स्थिर अचिन्हित uart4_pins[] = अणु 108, 113 पूर्ण;
अटल काष्ठा spear_muxreg uart4_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2S0_MASK | PMX_CLCD1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_I2S0_MASK | PMX_CLCD1_MASK,
		.val = PMX_I2S0_MASK | PMX_CLCD1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart4_modemux[] = अणु
	अणु
		.muxregs = uart4_muxreg,
		.nmuxregs = ARRAY_SIZE(uart4_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart_4_pingroup = अणु
	.name = "uart4_grp",
	.pins = uart4_pins,
	.npins = ARRAY_SIZE(uart4_pins),
	.modemuxs = uart4_modemux,
	.nmodemuxs = ARRAY_SIZE(uart4_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart4_grps[] = अणु "uart4_grp" पूर्ण;
अटल काष्ठा spear_function uart4_function = अणु
	.name = "uart4",
	.groups = uart4_grps,
	.ngroups = ARRAY_SIZE(uart4_grps),
पूर्ण;

/* Pad multiplexing क्रम uart5 device */
अटल स्थिर अचिन्हित uart5_pins[] = अणु 114, 115 पूर्ण;
अटल काष्ठा spear_muxreg uart5_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_CLCD1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_CLCD1_MASK,
		.val = PMX_CLCD1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart5_modemux[] = अणु
	अणु
		.muxregs = uart5_muxreg,
		.nmuxregs = ARRAY_SIZE(uart5_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart_5_pingroup = अणु
	.name = "uart5_grp",
	.pins = uart5_pins,
	.npins = ARRAY_SIZE(uart5_pins),
	.modemuxs = uart5_modemux,
	.nmodemuxs = ARRAY_SIZE(uart5_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart5_grps[] = अणु "uart5_grp" पूर्ण;
अटल काष्ठा spear_function uart5_function = अणु
	.name = "uart5",
	.groups = uart5_grps,
	.ngroups = ARRAY_SIZE(uart5_grps),
पूर्ण;

/* Pad multiplexing क्रम rs485_0_1_tdm_0_1 device */
अटल स्थिर अचिन्हित rs485_0_1_tdm_0_1_pins[] = अणु 116, 117, 118, 119, 120, 121,
	122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
	136, 137 पूर्ण;
अटल काष्ठा spear_muxreg rs485_0_1_tdm_0_1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_CLCD1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_CLCD1_MASK,
		.val = PMX_CLCD1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux rs485_0_1_tdm_0_1_modemux[] = अणु
	अणु
		.muxregs = rs485_0_1_tdm_0_1_muxreg,
		.nmuxregs = ARRAY_SIZE(rs485_0_1_tdm_0_1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup rs485_0_1_tdm_0_1_pingroup = अणु
	.name = "rs485_0_1_tdm_0_1_grp",
	.pins = rs485_0_1_tdm_0_1_pins,
	.npins = ARRAY_SIZE(rs485_0_1_tdm_0_1_pins),
	.modemuxs = rs485_0_1_tdm_0_1_modemux,
	.nmodemuxs = ARRAY_SIZE(rs485_0_1_tdm_0_1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर rs485_0_1_tdm_0_1_grps[] = अणु "rs485_0_1_tdm_0_1_grp" पूर्ण;
अटल काष्ठा spear_function rs485_0_1_tdm_0_1_function = अणु
	.name = "rs485_0_1_tdm_0_1",
	.groups = rs485_0_1_tdm_0_1_grps,
	.ngroups = ARRAY_SIZE(rs485_0_1_tdm_0_1_grps),
पूर्ण;

/* Pad multiplexing क्रम i2c_1_2 device */
अटल स्थिर अचिन्हित i2c_1_2_pins[] = अणु 138, 139, 140, 141 पूर्ण;
अटल काष्ठा spear_muxreg i2c_1_2_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_CLCD1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_CLCD1_MASK,
		.val = PMX_CLCD1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c_1_2_modemux[] = अणु
	अणु
		.muxregs = i2c_1_2_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c_1_2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c_1_2_pingroup = अणु
	.name = "i2c_1_2_grp",
	.pins = i2c_1_2_pins,
	.npins = ARRAY_SIZE(i2c_1_2_pins),
	.modemuxs = i2c_1_2_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c_1_2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c_1_2_grps[] = अणु "i2c_1_2_grp" पूर्ण;
अटल काष्ठा spear_function i2c_1_2_function = अणु
	.name = "i2c_1_2",
	.groups = i2c_1_2_grps,
	.ngroups = ARRAY_SIZE(i2c_1_2_grps),
पूर्ण;

/* Pad multiplexing क्रम i2c3_dis_smi_clcd device */
/* Muxed with SMI & CLCD */
अटल स्थिर अचिन्हित i2c3_dis_smi_clcd_pins[] = अणु 142, 153 पूर्ण;
अटल काष्ठा spear_muxreg i2c3_dis_smi_clcd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_CLCD1_MASK | PMX_SMI_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_CLCD1_MASK | PMX_SMI_MASK,
		.val = PMX_CLCD1_MASK | PMX_SMI_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c3_dis_smi_clcd_modemux[] = अणु
	अणु
		.muxregs = i2c3_dis_smi_clcd_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c3_dis_smi_clcd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c3_dis_smi_clcd_pingroup = अणु
	.name = "i2c3_dis_smi_clcd_grp",
	.pins = i2c3_dis_smi_clcd_pins,
	.npins = ARRAY_SIZE(i2c3_dis_smi_clcd_pins),
	.modemuxs = i2c3_dis_smi_clcd_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c3_dis_smi_clcd_modemux),
पूर्ण;

/* Pad multiplexing क्रम i2c3_dis_sd_i2s0 device */
/* Muxed with SD/MMC & I2S1 */
अटल स्थिर अचिन्हित i2c3_dis_sd_i2s0_pins[] = अणु 0, 216 पूर्ण;
अटल काष्ठा spear_muxreg i2c3_dis_sd_i2s0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_I2S1_MASK | PMX_MCIDATA3_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_I2S1_MASK | PMX_MCIDATA3_MASK,
		.val = PMX_I2S1_MASK | PMX_MCIDATA3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c3_dis_sd_i2s0_modemux[] = अणु
	अणु
		.muxregs = i2c3_dis_sd_i2s0_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c3_dis_sd_i2s0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c3_dis_sd_i2s0_pingroup = अणु
	.name = "i2c3_dis_sd_i2s0_grp",
	.pins = i2c3_dis_sd_i2s0_pins,
	.npins = ARRAY_SIZE(i2c3_dis_sd_i2s0_pins),
	.modemuxs = i2c3_dis_sd_i2s0_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c3_dis_sd_i2s0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c3_grps[] = अणु "i2c3_dis_smi_clcd_grp",
	"i2c3_dis_sd_i2s0_grp" पूर्ण;
अटल काष्ठा spear_function i2c3_unction = अणु
	.name = "i2c3_i2s1",
	.groups = i2c3_grps,
	.ngroups = ARRAY_SIZE(i2c3_grps),
पूर्ण;

/* Pad multiplexing क्रम i2c_4_5_dis_smi device */
/* Muxed with SMI */
अटल स्थिर अचिन्हित i2c_4_5_dis_smi_pins[] = अणु 154, 155, 156, 157 पूर्ण;
अटल काष्ठा spear_muxreg i2c_4_5_dis_smi_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_SMI_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_SMI_MASK,
		.val = PMX_SMI_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c_4_5_dis_smi_modemux[] = अणु
	अणु
		.muxregs = i2c_4_5_dis_smi_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c_4_5_dis_smi_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c_4_5_dis_smi_pingroup = अणु
	.name = "i2c_4_5_dis_smi_grp",
	.pins = i2c_4_5_dis_smi_pins,
	.npins = ARRAY_SIZE(i2c_4_5_dis_smi_pins),
	.modemuxs = i2c_4_5_dis_smi_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c_4_5_dis_smi_modemux),
पूर्ण;

/* Pad multiplexing क्रम i2c4_dis_sd device */
/* Muxed with SD/MMC */
अटल स्थिर अचिन्हित i2c4_dis_sd_pins[] = अणु 217, 218 पूर्ण;
अटल काष्ठा spear_muxreg i2c4_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_MCIDATA4_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIDATA5_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_MCIDATA4_MASK,
		.val = PMX_MCIDATA4_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCIDATA5_MASK,
		.val = PMX_MCIDATA5_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c4_dis_sd_modemux[] = अणु
	अणु
		.muxregs = i2c4_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c4_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c4_dis_sd_pingroup = अणु
	.name = "i2c4_dis_sd_grp",
	.pins = i2c4_dis_sd_pins,
	.npins = ARRAY_SIZE(i2c4_dis_sd_pins),
	.modemuxs = i2c4_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c4_dis_sd_modemux),
पूर्ण;

/* Pad multiplexing क्रम i2c5_dis_sd device */
/* Muxed with SD/MMC */
अटल स्थिर अचिन्हित i2c5_dis_sd_pins[] = अणु 219, 220 पूर्ण;
अटल काष्ठा spear_muxreg i2c5_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIDATA6_MASK |
			PMX_MCIDATA7_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCIDATA6_MASK |
			PMX_MCIDATA7_MASK,
		.val = PMX_MCIDATA6_MASK |
			PMX_MCIDATA7_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c5_dis_sd_modemux[] = अणु
	अणु
		.muxregs = i2c5_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c5_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c5_dis_sd_pingroup = अणु
	.name = "i2c5_dis_sd_grp",
	.pins = i2c5_dis_sd_pins,
	.npins = ARRAY_SIZE(i2c5_dis_sd_pins),
	.modemuxs = i2c5_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c5_dis_sd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c_4_5_grps[] = अणु "i2c5_dis_sd_grp",
	"i2c4_dis_sd_grp", "i2c_4_5_dis_smi_grp" पूर्ण;
अटल काष्ठा spear_function i2c_4_5_function = अणु
	.name = "i2c_4_5",
	.groups = i2c_4_5_grps,
	.ngroups = ARRAY_SIZE(i2c_4_5_grps),
पूर्ण;

/* Pad multiplexing क्रम i2c_6_7_dis_kbd device */
/* Muxed with KBD */
अटल स्थिर अचिन्हित i2c_6_7_dis_kbd_pins[] = अणु 207, 208, 209, 210 पूर्ण;
अटल काष्ठा spear_muxreg i2c_6_7_dis_kbd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_ROWCOL25_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_KBD_ROWCOL25_MASK,
		.val = PMX_KBD_ROWCOL25_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c_6_7_dis_kbd_modemux[] = अणु
	अणु
		.muxregs = i2c_6_7_dis_kbd_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c_6_7_dis_kbd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c_6_7_dis_kbd_pingroup = अणु
	.name = "i2c_6_7_dis_kbd_grp",
	.pins = i2c_6_7_dis_kbd_pins,
	.npins = ARRAY_SIZE(i2c_6_7_dis_kbd_pins),
	.modemuxs = i2c_6_7_dis_kbd_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c_6_7_dis_kbd_modemux),
पूर्ण;

/* Pad multiplexing क्रम i2c6_dis_sd device */
/* Muxed with SD/MMC */
अटल स्थिर अचिन्हित i2c6_dis_sd_pins[] = अणु 236, 237 पूर्ण;
अटल काष्ठा spear_muxreg i2c6_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIIORDRE_MASK |
			PMX_MCIIOWRWE_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCIIORDRE_MASK |
			PMX_MCIIOWRWE_MASK,
		.val = PMX_MCIIORDRE_MASK |
			PMX_MCIIOWRWE_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c6_dis_sd_modemux[] = अणु
	अणु
		.muxregs = i2c6_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c6_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c6_dis_sd_pingroup = अणु
	.name = "i2c6_dis_sd_grp",
	.pins = i2c6_dis_sd_pins,
	.npins = ARRAY_SIZE(i2c6_dis_sd_pins),
	.modemuxs = i2c6_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c6_dis_sd_modemux),
पूर्ण;

/* Pad multiplexing क्रम i2c7_dis_sd device */
अटल स्थिर अचिन्हित i2c7_dis_sd_pins[] = अणु 238, 239 पूर्ण;
अटल काष्ठा spear_muxreg i2c7_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIRESETCF_MASK |
			PMX_MCICS0CE_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCIRESETCF_MASK |
			PMX_MCICS0CE_MASK,
		.val = PMX_MCIRESETCF_MASK |
			PMX_MCICS0CE_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c7_dis_sd_modemux[] = अणु
	अणु
		.muxregs = i2c7_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c7_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c7_dis_sd_pingroup = अणु
	.name = "i2c7_dis_sd_grp",
	.pins = i2c7_dis_sd_pins,
	.npins = ARRAY_SIZE(i2c7_dis_sd_pins),
	.modemuxs = i2c7_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c7_dis_sd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c_6_7_grps[] = अणु "i2c6_dis_sd_grp",
	"i2c7_dis_sd_grp", "i2c_6_7_dis_kbd_grp" पूर्ण;
अटल काष्ठा spear_function i2c_6_7_function = अणु
	.name = "i2c_6_7",
	.groups = i2c_6_7_grps,
	.ngroups = ARRAY_SIZE(i2c_6_7_grps),
पूर्ण;

/* Pad multiplexing क्रम can0_dis_nor device */
/* Muxed with NOR */
अटल स्थिर अचिन्हित can0_dis_nor_pins[] = अणु 56, 57 पूर्ण;
अटल काष्ठा spear_muxreg can0_dis_nor_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_NFRSTPWDWN2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_NFRSTPWDWN3_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_NFRSTPWDWN2_MASK,
		.val = PMX_NFRSTPWDWN2_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_NFRSTPWDWN3_MASK,
		.val = PMX_NFRSTPWDWN3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux can0_dis_nor_modemux[] = अणु
	अणु
		.muxregs = can0_dis_nor_muxreg,
		.nmuxregs = ARRAY_SIZE(can0_dis_nor_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup can0_dis_nor_pingroup = अणु
	.name = "can0_dis_nor_grp",
	.pins = can0_dis_nor_pins,
	.npins = ARRAY_SIZE(can0_dis_nor_pins),
	.modemuxs = can0_dis_nor_modemux,
	.nmodemuxs = ARRAY_SIZE(can0_dis_nor_modemux),
पूर्ण;

/* Pad multiplexing क्रम can0_dis_sd device */
/* Muxed with SD/MMC */
अटल स्थिर अचिन्हित can0_dis_sd_pins[] = अणु 240, 241 पूर्ण;
अटल काष्ठा spear_muxreg can0_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCICFINTR_MASK | PMX_MCIIORDY_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCICFINTR_MASK | PMX_MCIIORDY_MASK,
		.val = PMX_MCICFINTR_MASK | PMX_MCIIORDY_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux can0_dis_sd_modemux[] = अणु
	अणु
		.muxregs = can0_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(can0_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup can0_dis_sd_pingroup = अणु
	.name = "can0_dis_sd_grp",
	.pins = can0_dis_sd_pins,
	.npins = ARRAY_SIZE(can0_dis_sd_pins),
	.modemuxs = can0_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(can0_dis_sd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर can0_grps[] = अणु "can0_dis_nor_grp", "can0_dis_sd_grp"
पूर्ण;
अटल काष्ठा spear_function can0_function = अणु
	.name = "can0",
	.groups = can0_grps,
	.ngroups = ARRAY_SIZE(can0_grps),
पूर्ण;

/* Pad multiplexing क्रम can1_dis_sd device */
/* Muxed with SD/MMC */
अटल स्थिर अचिन्हित can1_dis_sd_pins[] = अणु 242, 243 पूर्ण;
अटल काष्ठा spear_muxreg can1_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCICS1_MASK | PMX_MCIDMAACK_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCICS1_MASK | PMX_MCIDMAACK_MASK,
		.val = PMX_MCICS1_MASK | PMX_MCIDMAACK_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux can1_dis_sd_modemux[] = अणु
	अणु
		.muxregs = can1_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(can1_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup can1_dis_sd_pingroup = अणु
	.name = "can1_dis_sd_grp",
	.pins = can1_dis_sd_pins,
	.npins = ARRAY_SIZE(can1_dis_sd_pins),
	.modemuxs = can1_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(can1_dis_sd_modemux),
पूर्ण;

/* Pad multiplexing क्रम can1_dis_kbd device */
/* Muxed with KBD */
अटल स्थिर अचिन्हित can1_dis_kbd_pins[] = अणु 201, 202 पूर्ण;
अटल काष्ठा spear_muxreg can1_dis_kbd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_ROWCOL25_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_KBD_ROWCOL25_MASK,
		.val = PMX_KBD_ROWCOL25_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux can1_dis_kbd_modemux[] = अणु
	अणु
		.muxregs = can1_dis_kbd_muxreg,
		.nmuxregs = ARRAY_SIZE(can1_dis_kbd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup can1_dis_kbd_pingroup = अणु
	.name = "can1_dis_kbd_grp",
	.pins = can1_dis_kbd_pins,
	.npins = ARRAY_SIZE(can1_dis_kbd_pins),
	.modemuxs = can1_dis_kbd_modemux,
	.nmodemuxs = ARRAY_SIZE(can1_dis_kbd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर can1_grps[] = अणु "can1_dis_sd_grp", "can1_dis_kbd_grp"
पूर्ण;
अटल काष्ठा spear_function can1_function = अणु
	.name = "can1",
	.groups = can1_grps,
	.ngroups = ARRAY_SIZE(can1_grps),
पूर्ण;

/* Pad multiplexing क्रम (ras-ip) pci device */
अटल स्थिर अचिन्हित pci_pins[] = अणु 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18,
	19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
	37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
	55, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 पूर्ण;

अटल काष्ठा spear_muxreg pci_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_0,
		.mask = PMX_MCI_DATA8_15_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_PCI_REG1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_PCI_REG2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_0,
		.mask = PMX_MCI_DATA8_15_MASK,
		.val = PMX_MCI_DATA8_15_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_PCI_REG1_MASK,
		.val = PMX_PCI_REG1_MASK,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_PCI_REG2_MASK,
		.val = PMX_PCI_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pci_modemux[] = अणु
	अणु
		.muxregs = pci_muxreg,
		.nmuxregs = ARRAY_SIZE(pci_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pci_pingroup = अणु
	.name = "pci_grp",
	.pins = pci_pins,
	.npins = ARRAY_SIZE(pci_pins),
	.modemuxs = pci_modemux,
	.nmodemuxs = ARRAY_SIZE(pci_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर pci_grps[] = अणु "pci_grp" पूर्ण;
अटल काष्ठा spear_function pci_function = अणु
	.name = "pci",
	.groups = pci_grps,
	.ngroups = ARRAY_SIZE(pci_grps),
पूर्ण;

/* pad multiplexing क्रम (fix-part) pcie0 device */
अटल काष्ठा spear_muxreg pcie0_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = PCIE_CFG_VAL(0),
		.val = PCIE_CFG_VAL(0),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pcie0_modemux[] = अणु
	अणु
		.muxregs = pcie0_muxreg,
		.nmuxregs = ARRAY_SIZE(pcie0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pcie0_pingroup = अणु
	.name = "pcie0_grp",
	.modemuxs = pcie0_modemux,
	.nmodemuxs = ARRAY_SIZE(pcie0_modemux),
पूर्ण;

/* pad multiplexing क्रम (fix-part) pcie1 device */
अटल काष्ठा spear_muxreg pcie1_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = PCIE_CFG_VAL(1),
		.val = PCIE_CFG_VAL(1),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pcie1_modemux[] = अणु
	अणु
		.muxregs = pcie1_muxreg,
		.nmuxregs = ARRAY_SIZE(pcie1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pcie1_pingroup = अणु
	.name = "pcie1_grp",
	.modemuxs = pcie1_modemux,
	.nmodemuxs = ARRAY_SIZE(pcie1_modemux),
पूर्ण;

/* pad multiplexing क्रम (fix-part) pcie2 device */
अटल काष्ठा spear_muxreg pcie2_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = PCIE_CFG_VAL(2),
		.val = PCIE_CFG_VAL(2),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pcie2_modemux[] = अणु
	अणु
		.muxregs = pcie2_muxreg,
		.nmuxregs = ARRAY_SIZE(pcie2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pcie2_pingroup = अणु
	.name = "pcie2_grp",
	.modemuxs = pcie2_modemux,
	.nmodemuxs = ARRAY_SIZE(pcie2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर pcie_grps[] = अणु "pcie0_grp", "pcie1_grp", "pcie2_grp"
पूर्ण;
अटल काष्ठा spear_function pcie_function = अणु
	.name = "pci_express",
	.groups = pcie_grps,
	.ngroups = ARRAY_SIZE(pcie_grps),
पूर्ण;

/* pad multiplexing क्रम sata0 device */
अटल काष्ठा spear_muxreg sata0_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = SATA_CFG_VAL(0),
		.val = SATA_CFG_VAL(0),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sata0_modemux[] = अणु
	अणु
		.muxregs = sata0_muxreg,
		.nmuxregs = ARRAY_SIZE(sata0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sata0_pingroup = अणु
	.name = "sata0_grp",
	.modemuxs = sata0_modemux,
	.nmodemuxs = ARRAY_SIZE(sata0_modemux),
पूर्ण;

/* pad multiplexing क्रम sata1 device */
अटल काष्ठा spear_muxreg sata1_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = SATA_CFG_VAL(1),
		.val = SATA_CFG_VAL(1),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sata1_modemux[] = अणु
	अणु
		.muxregs = sata1_muxreg,
		.nmuxregs = ARRAY_SIZE(sata1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sata1_pingroup = अणु
	.name = "sata1_grp",
	.modemuxs = sata1_modemux,
	.nmodemuxs = ARRAY_SIZE(sata1_modemux),
पूर्ण;

/* pad multiplexing क्रम sata2 device */
अटल काष्ठा spear_muxreg sata2_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = SATA_CFG_VAL(2),
		.val = SATA_CFG_VAL(2),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sata2_modemux[] = अणु
	अणु
		.muxregs = sata2_muxreg,
		.nmuxregs = ARRAY_SIZE(sata2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sata2_pingroup = अणु
	.name = "sata2_grp",
	.modemuxs = sata2_modemux,
	.nmodemuxs = ARRAY_SIZE(sata2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर sata_grps[] = अणु "sata0_grp", "sata1_grp", "sata2_grp"
पूर्ण;
अटल काष्ठा spear_function sata_function = अणु
	.name = "sata",
	.groups = sata_grps,
	.ngroups = ARRAY_SIZE(sata_grps),
पूर्ण;

/* Pad multiplexing क्रम ssp1_dis_kbd device */
अटल स्थिर अचिन्हित ssp1_dis_kbd_pins[] = अणु 203, 204, 205, 206 पूर्ण;
अटल काष्ठा spear_muxreg ssp1_dis_kbd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_ROWCOL25_MASK | PMX_KBD_COL1_MASK |
			PMX_KBD_COL0_MASK | PMX_NFIO8_15_MASK | PMX_NFCE1_MASK |
			PMX_NFCE2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_1,
		.mask = PMX_KBD_ROWCOL25_MASK | PMX_KBD_COL1_MASK |
			PMX_KBD_COL0_MASK | PMX_NFIO8_15_MASK | PMX_NFCE1_MASK |
			PMX_NFCE2_MASK,
		.val = PMX_KBD_ROWCOL25_MASK | PMX_KBD_COL1_MASK |
			PMX_KBD_COL0_MASK | PMX_NFIO8_15_MASK | PMX_NFCE1_MASK |
			PMX_NFCE2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp1_dis_kbd_modemux[] = अणु
	अणु
		.muxregs = ssp1_dis_kbd_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_dis_kbd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp1_dis_kbd_pingroup = अणु
	.name = "ssp1_dis_kbd_grp",
	.pins = ssp1_dis_kbd_pins,
	.npins = ARRAY_SIZE(ssp1_dis_kbd_pins),
	.modemuxs = ssp1_dis_kbd_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp1_dis_kbd_modemux),
पूर्ण;

/* Pad multiplexing क्रम ssp1_dis_sd device */
अटल स्थिर अचिन्हित ssp1_dis_sd_pins[] = अणु 224, 226, 227, 228 पूर्ण;
अटल काष्ठा spear_muxreg ssp1_dis_sd_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIADDR0ALE_MASK | PMX_MCIADDR2_MASK |
			PMX_MCICECF_MASK | PMX_MCICEXD_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCIADDR0ALE_MASK | PMX_MCIADDR2_MASK |
			PMX_MCICECF_MASK | PMX_MCICEXD_MASK,
		.val = PMX_MCIADDR0ALE_MASK | PMX_MCIADDR2_MASK |
			PMX_MCICECF_MASK | PMX_MCICEXD_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp1_dis_sd_modemux[] = अणु
	अणु
		.muxregs = ssp1_dis_sd_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_dis_sd_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp1_dis_sd_pingroup = अणु
	.name = "ssp1_dis_sd_grp",
	.pins = ssp1_dis_sd_pins,
	.npins = ARRAY_SIZE(ssp1_dis_sd_pins),
	.modemuxs = ssp1_dis_sd_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp1_dis_sd_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp1_grps[] = अणु "ssp1_dis_kbd_grp",
	"ssp1_dis_sd_grp" पूर्ण;
अटल काष्ठा spear_function ssp1_function = अणु
	.name = "ssp1",
	.groups = ssp1_grps,
	.ngroups = ARRAY_SIZE(ssp1_grps),
पूर्ण;

/* Pad multiplexing क्रम gpt64 device */
अटल स्थिर अचिन्हित gpt64_pins[] = अणु 230, 231, 232, 245 पूर्ण;
अटल काष्ठा spear_muxreg gpt64_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCICDCF1_MASK | PMX_MCICDCF2_MASK | PMX_MCICDXD_MASK
			| PMX_MCILEDS_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_सूचीECTION_SEL_2,
		.mask = PMX_MCICDCF1_MASK | PMX_MCICDCF2_MASK | PMX_MCICDXD_MASK
			| PMX_MCILEDS_MASK,
		.val = PMX_MCICDCF1_MASK | PMX_MCICDCF2_MASK | PMX_MCICDXD_MASK
			| PMX_MCILEDS_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpt64_modemux[] = अणु
	अणु
		.muxregs = gpt64_muxreg,
		.nmuxregs = ARRAY_SIZE(gpt64_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpt64_pingroup = अणु
	.name = "gpt64_grp",
	.pins = gpt64_pins,
	.npins = ARRAY_SIZE(gpt64_pins),
	.modemuxs = gpt64_modemux,
	.nmodemuxs = ARRAY_SIZE(gpt64_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpt64_grps[] = अणु "gpt64_grp" पूर्ण;
अटल काष्ठा spear_function gpt64_function = अणु
	.name = "gpt64",
	.groups = gpt64_grps,
	.ngroups = ARRAY_SIZE(gpt64_grps),
पूर्ण;

/* pingroups */
अटल काष्ठा spear_pingroup *spear1310_pingroups[] = अणु
	&i2c0_pingroup,
	&ssp0_pingroup,
	&i2s0_pingroup,
	&i2s1_pingroup,
	&clcd_pingroup,
	&clcd_high_res_pingroup,
	&arm_gpio_pingroup,
	&smi_2_chips_pingroup,
	&smi_4_chips_pingroup,
	&gmii_pingroup,
	&rgmii_pingroup,
	&smii_0_1_2_pingroup,
	&ras_mii_txclk_pingroup,
	&nand_8bit_pingroup,
	&nand_16bit_pingroup,
	&nand_4_chips_pingroup,
	&keyboard_6x6_pingroup,
	&keyboard_rowcol6_8_pingroup,
	&uart0_pingroup,
	&uart0_modem_pingroup,
	&gpt0_पंचांगr0_pingroup,
	&gpt0_पंचांगr1_pingroup,
	&gpt1_पंचांगr0_pingroup,
	&gpt1_पंचांगr1_pingroup,
	&sdhci_pingroup,
	&cf_pingroup,
	&xd_pingroup,
	&touch_xy_pingroup,
	&ssp0_cs0_pingroup,
	&ssp0_cs1_2_pingroup,
	&uart_1_dis_i2c_pingroup,
	&uart_1_dis_sd_pingroup,
	&uart_2_3_pingroup,
	&uart_4_pingroup,
	&uart_5_pingroup,
	&rs485_0_1_tdm_0_1_pingroup,
	&i2c_1_2_pingroup,
	&i2c3_dis_smi_clcd_pingroup,
	&i2c3_dis_sd_i2s0_pingroup,
	&i2c_4_5_dis_smi_pingroup,
	&i2c4_dis_sd_pingroup,
	&i2c5_dis_sd_pingroup,
	&i2c_6_7_dis_kbd_pingroup,
	&i2c6_dis_sd_pingroup,
	&i2c7_dis_sd_pingroup,
	&can0_dis_nor_pingroup,
	&can0_dis_sd_pingroup,
	&can1_dis_sd_pingroup,
	&can1_dis_kbd_pingroup,
	&pci_pingroup,
	&pcie0_pingroup,
	&pcie1_pingroup,
	&pcie2_pingroup,
	&sata0_pingroup,
	&sata1_pingroup,
	&sata2_pingroup,
	&ssp1_dis_kbd_pingroup,
	&ssp1_dis_sd_pingroup,
	&gpt64_pingroup,
पूर्ण;

/* functions */
अटल काष्ठा spear_function *spear1310_functions[] = अणु
	&i2c0_function,
	&ssp0_function,
	&i2s0_function,
	&i2s1_function,
	&clcd_function,
	&arm_gpio_function,
	&smi_function,
	&gmii_function,
	&rgmii_function,
	&smii_0_1_2_function,
	&ras_mii_txclk_function,
	&nand_function,
	&keyboard_function,
	&uart0_function,
	&gpt0_function,
	&gpt1_function,
	&sdhci_function,
	&cf_function,
	&xd_function,
	&touch_xy_function,
	&uart1_function,
	&uart2_3_function,
	&uart4_function,
	&uart5_function,
	&rs485_0_1_tdm_0_1_function,
	&i2c_1_2_function,
	&i2c3_unction,
	&i2c_4_5_function,
	&i2c_6_7_function,
	&can0_function,
	&can1_function,
	&pci_function,
	&pcie_function,
	&sata_function,
	&ssp1_function,
	&gpt64_function,
पूर्ण;

अटल स्थिर अचिन्हित pin18[] = अणु 18, पूर्ण;
अटल स्थिर अचिन्हित pin19[] = अणु 19, पूर्ण;
अटल स्थिर अचिन्हित pin20[] = अणु 20, पूर्ण;
अटल स्थिर अचिन्हित pin21[] = अणु 21, पूर्ण;
अटल स्थिर अचिन्हित pin22[] = अणु 22, पूर्ण;
अटल स्थिर अचिन्हित pin23[] = अणु 23, पूर्ण;
अटल स्थिर अचिन्हित pin54[] = अणु 54, पूर्ण;
अटल स्थिर अचिन्हित pin55[] = अणु 55, पूर्ण;
अटल स्थिर अचिन्हित pin56[] = अणु 56, पूर्ण;
अटल स्थिर अचिन्हित pin57[] = अणु 57, पूर्ण;
अटल स्थिर अचिन्हित pin58[] = अणु 58, पूर्ण;
अटल स्थिर अचिन्हित pin59[] = अणु 59, पूर्ण;
अटल स्थिर अचिन्हित pin60[] = अणु 60, पूर्ण;
अटल स्थिर अचिन्हित pin61[] = अणु 61, पूर्ण;
अटल स्थिर अचिन्हित pin62[] = अणु 62, पूर्ण;
अटल स्थिर अचिन्हित pin63[] = अणु 63, पूर्ण;
अटल स्थिर अचिन्हित pin143[] = अणु 143, पूर्ण;
अटल स्थिर अचिन्हित pin144[] = अणु 144, पूर्ण;
अटल स्थिर अचिन्हित pin145[] = अणु 145, पूर्ण;
अटल स्थिर अचिन्हित pin146[] = अणु 146, पूर्ण;
अटल स्थिर अचिन्हित pin147[] = अणु 147, पूर्ण;
अटल स्थिर अचिन्हित pin148[] = अणु 148, पूर्ण;
अटल स्थिर अचिन्हित pin149[] = अणु 149, पूर्ण;
अटल स्थिर अचिन्हित pin150[] = अणु 150, पूर्ण;
अटल स्थिर अचिन्हित pin151[] = अणु 151, पूर्ण;
अटल स्थिर अचिन्हित pin152[] = अणु 152, पूर्ण;
अटल स्थिर अचिन्हित pin205[] = अणु 205, पूर्ण;
अटल स्थिर अचिन्हित pin206[] = अणु 206, पूर्ण;
अटल स्थिर अचिन्हित pin211[] = अणु 211, पूर्ण;
अटल स्थिर अचिन्हित pin212[] = अणु 212, पूर्ण;
अटल स्थिर अचिन्हित pin213[] = अणु 213, पूर्ण;
अटल स्थिर अचिन्हित pin214[] = अणु 214, पूर्ण;
अटल स्थिर अचिन्हित pin215[] = अणु 215, पूर्ण;
अटल स्थिर अचिन्हित pin216[] = अणु 216, पूर्ण;
अटल स्थिर अचिन्हित pin217[] = अणु 217, पूर्ण;
अटल स्थिर अचिन्हित pin218[] = अणु 218, पूर्ण;
अटल स्थिर अचिन्हित pin219[] = अणु 219, पूर्ण;
अटल स्थिर अचिन्हित pin220[] = अणु 220, पूर्ण;
अटल स्थिर अचिन्हित pin221[] = अणु 221, पूर्ण;
अटल स्थिर अचिन्हित pin222[] = अणु 222, पूर्ण;
अटल स्थिर अचिन्हित pin223[] = अणु 223, पूर्ण;
अटल स्थिर अचिन्हित pin224[] = अणु 224, पूर्ण;
अटल स्थिर अचिन्हित pin225[] = अणु 225, पूर्ण;
अटल स्थिर अचिन्हित pin226[] = अणु 226, पूर्ण;
अटल स्थिर अचिन्हित pin227[] = अणु 227, पूर्ण;
अटल स्थिर अचिन्हित pin228[] = अणु 228, पूर्ण;
अटल स्थिर अचिन्हित pin229[] = अणु 229, पूर्ण;
अटल स्थिर अचिन्हित pin230[] = अणु 230, पूर्ण;
अटल स्थिर अचिन्हित pin231[] = अणु 231, पूर्ण;
अटल स्थिर अचिन्हित pin232[] = अणु 232, पूर्ण;
अटल स्थिर अचिन्हित pin233[] = अणु 233, पूर्ण;
अटल स्थिर अचिन्हित pin234[] = अणु 234, पूर्ण;
अटल स्थिर अचिन्हित pin235[] = अणु 235, पूर्ण;
अटल स्थिर अचिन्हित pin236[] = अणु 236, पूर्ण;
अटल स्थिर अचिन्हित pin237[] = अणु 237, पूर्ण;
अटल स्थिर अचिन्हित pin238[] = अणु 238, पूर्ण;
अटल स्थिर अचिन्हित pin239[] = अणु 239, पूर्ण;
अटल स्थिर अचिन्हित pin240[] = अणु 240, पूर्ण;
अटल स्थिर अचिन्हित pin241[] = अणु 241, पूर्ण;
अटल स्थिर अचिन्हित pin242[] = अणु 242, पूर्ण;
अटल स्थिर अचिन्हित pin243[] = अणु 243, पूर्ण;
अटल स्थिर अचिन्हित pin244[] = अणु 244, पूर्ण;
अटल स्थिर अचिन्हित pin245[] = अणु 245, पूर्ण;

अटल स्थिर अचिन्हित pin_grp0[] = अणु 173, 174, पूर्ण;
अटल स्थिर अचिन्हित pin_grp1[] = अणु 175, 185, 188, 197, 198, पूर्ण;
अटल स्थिर अचिन्हित pin_grp2[] = अणु 176, 177, 178, 179, 184, 186, 187, 189,
	190, 191, 192, पूर्ण;
अटल स्थिर अचिन्हित pin_grp3[] = अणु 180, 181, 182, 183, 193, 194, 195, 196, पूर्ण;
अटल स्थिर अचिन्हित pin_grp4[] = अणु 199, 200, पूर्ण;
अटल स्थिर अचिन्हित pin_grp5[] = अणु 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, पूर्ण;
अटल स्थिर अचिन्हित pin_grp6[] = अणु 86, 87, 88, 89, 90, 91, 92, 93, पूर्ण;
अटल स्थिर अचिन्हित pin_grp7[] = अणु 98, 99, पूर्ण;
अटल स्थिर अचिन्हित pin_grp8[] = अणु 158, 159, 160, 161, 162, 163, 164, 165,
	166, 167, 168, 169, 170, 171, 172, पूर्ण;

/* Define muxreg arrays */
DEFINE_2_MUXREG(i2c0_pins, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_I2C0_MASK, 0, 1);
DEFINE_2_MUXREG(ssp0_pins, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_SSP0_MASK, 0, 1);
DEFINE_2_MUXREG(ssp0_cs0_pins, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_SSP0_CS0_MASK, 0, 1);
DEFINE_2_MUXREG(ssp0_cs1_2_pins, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_SSP0_CS1_2_MASK, 0, 1);
DEFINE_2_MUXREG(i2s0_pins, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_I2S0_MASK, 0, 1);
DEFINE_2_MUXREG(i2s1_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_I2S1_MASK, 0, 1);
DEFINE_2_MUXREG(clcd_pins, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_CLCD1_MASK, 0, 1);
DEFINE_2_MUXREG(clcd_high_res_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_CLCD2_MASK, 0, 1);
DEFINE_2_MUXREG(pin18, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO15_MASK, 0, 1);
DEFINE_2_MUXREG(pin19, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO14_MASK, 0, 1);
DEFINE_2_MUXREG(pin20, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO13_MASK, 0, 1);
DEFINE_2_MUXREG(pin21, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO12_MASK, 0, 1);
DEFINE_2_MUXREG(pin22, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO11_MASK, 0, 1);
DEFINE_2_MUXREG(pin23, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO10_MASK, 0, 1);
DEFINE_2_MUXREG(pin143, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO00_MASK, 0, 1);
DEFINE_2_MUXREG(pin144, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO01_MASK, 0, 1);
DEFINE_2_MUXREG(pin145, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO02_MASK, 0, 1);
DEFINE_2_MUXREG(pin146, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO03_MASK, 0, 1);
DEFINE_2_MUXREG(pin147, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO04_MASK, 0, 1);
DEFINE_2_MUXREG(pin148, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO05_MASK, 0, 1);
DEFINE_2_MUXREG(pin149, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO06_MASK, 0, 1);
DEFINE_2_MUXREG(pin150, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO07_MASK, 0, 1);
DEFINE_2_MUXREG(pin151, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO08_MASK, 0, 1);
DEFINE_2_MUXREG(pin152, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_EGPIO09_MASK, 0, 1);
DEFINE_2_MUXREG(smi_2_chips_pins, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_SMI_MASK, 0, 1);
DEFINE_2_MUXREG(pin54, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_SMINCS3_MASK, 0, 1);
DEFINE_2_MUXREG(pin55, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_SMINCS2_MASK, 0, 1);
DEFINE_2_MUXREG(pin56, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_NFRSTPWDWN3_MASK, 0, 1);
DEFINE_2_MUXREG(pin57, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFRSTPWDWN2_MASK, 0, 1);
DEFINE_2_MUXREG(pin58, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFRSTPWDWN1_MASK, 0, 1);
DEFINE_2_MUXREG(pin59, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFRSTPWDWN0_MASK, 0, 1);
DEFINE_2_MUXREG(pin60, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFWPRT3_MASK, 0, 1);
DEFINE_2_MUXREG(pin61, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFCE3_MASK, 0, 1);
DEFINE_2_MUXREG(pin62, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFAD25_MASK, 0, 1);
DEFINE_2_MUXREG(pin63, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFAD24_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp0, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_GMIICLK_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp1, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_GMIICOL_CRS_XFERER_MIITXCLK_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp2, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_RXCLK_RDV_TXEN_D03_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp3, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_GMIID47_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp4, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_MDC_MDIO_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp5, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_NFAD23_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp6, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_MCI_DATA8_15_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp7, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_NFCE2_MASK, 0, 1);
DEFINE_2_MUXREG(pin_grp8, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_न_अंकD8_MASK, 0, 1);
DEFINE_2_MUXREG(nand_16bit_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_न_अंकD16BIT_1_MASK, 0, 1);
DEFINE_2_MUXREG(pin205, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_KBD_COL1_MASK | PMX_NFCE1_MASK, 0, 1);
DEFINE_2_MUXREG(pin206, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_KBD_COL0_MASK | PMX_NFCE2_MASK, 0, 1);
DEFINE_2_MUXREG(pin211, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_KBD_ROW1_MASK | PMX_NFWPRT1_MASK, 0, 1);
DEFINE_2_MUXREG(pin212, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_KBD_ROW0_MASK | PMX_NFWPRT2_MASK, 0, 1);
DEFINE_2_MUXREG(pin213, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_MCIDATA0_MASK, 0, 1);
DEFINE_2_MUXREG(pin214, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_MCIDATA1_MASK, 0, 1);
DEFINE_2_MUXREG(pin215, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_MCIDATA2_MASK, 0, 1);
DEFINE_2_MUXREG(pin216, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_MCIDATA3_MASK, 0, 1);
DEFINE_2_MUXREG(pin217, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_MCIDATA4_MASK, 0, 1);
DEFINE_2_MUXREG(pin218, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATA5_MASK, 0, 1);
DEFINE_2_MUXREG(pin219, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATA6_MASK, 0, 1);
DEFINE_2_MUXREG(pin220, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATA7_MASK, 0, 1);
DEFINE_2_MUXREG(pin221, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATA1SD_MASK, 0, 1);
DEFINE_2_MUXREG(pin222, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATA2SD_MASK, 0, 1);
DEFINE_2_MUXREG(pin223, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATA3SD_MASK, 0, 1);
DEFINE_2_MUXREG(pin224, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIADDR0ALE_MASK, 0, 1);
DEFINE_2_MUXREG(pin225, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIADDR1CLECLK_MASK, 0, 1);
DEFINE_2_MUXREG(pin226, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIADDR2_MASK, 0, 1);
DEFINE_2_MUXREG(pin227, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICECF_MASK, 0, 1);
DEFINE_2_MUXREG(pin228, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICEXD_MASK, 0, 1);
DEFINE_2_MUXREG(pin229, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICESDMMC_MASK, 0, 1);
DEFINE_2_MUXREG(pin230, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICDCF1_MASK, 0, 1);
DEFINE_2_MUXREG(pin231, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICDCF2_MASK, 0, 1);
DEFINE_2_MUXREG(pin232, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICDXD_MASK, 0, 1);
DEFINE_2_MUXREG(pin233, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICDSDMMC_MASK, 0, 1);
DEFINE_2_MUXREG(pin234, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDATAसूची_MASK, 0, 1);
DEFINE_2_MUXREG(pin235, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDMARQWP_MASK, 0, 1);
DEFINE_2_MUXREG(pin236, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIIORDRE_MASK, 0, 1);
DEFINE_2_MUXREG(pin237, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIIOWRWE_MASK, 0, 1);
DEFINE_2_MUXREG(pin238, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIRESETCF_MASK, 0, 1);
DEFINE_2_MUXREG(pin239, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICS0CE_MASK, 0, 1);
DEFINE_2_MUXREG(pin240, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICFINTR_MASK, 0, 1);
DEFINE_2_MUXREG(pin241, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIIORDY_MASK, 0, 1);
DEFINE_2_MUXREG(pin242, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCICS1_MASK, 0, 1);
DEFINE_2_MUXREG(pin243, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCIDMAACK_MASK, 0, 1);
DEFINE_2_MUXREG(pin244, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCISDCMD_MASK, 0, 1);
DEFINE_2_MUXREG(pin245, PAD_FUNCTION_EN_2, PAD_सूचीECTION_SEL_2, PMX_MCILEDS_MASK, 0, 1);
DEFINE_2_MUXREG(keyboard_rowcol6_8_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_KBD_ROWCOL68_MASK, 0, 1);
DEFINE_2_MUXREG(uart0_pins, PAD_FUNCTION_EN_0, PAD_सूचीECTION_SEL_0, PMX_UART0_MASK, 0, 1);
DEFINE_2_MUXREG(uart0_modem_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_UART0_MODEM_MASK, 0, 1);
DEFINE_2_MUXREG(gpt0_पंचांगr0_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_GPT0_TMR0_MASK, 0, 1);
DEFINE_2_MUXREG(gpt0_पंचांगr1_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_GPT0_TMR1_MASK, 0, 1);
DEFINE_2_MUXREG(gpt1_पंचांगr0_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_GPT1_TMR0_MASK, 0, 1);
DEFINE_2_MUXREG(gpt1_पंचांगr1_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_GPT1_TMR1_MASK, 0, 1);
DEFINE_2_MUXREG(touch_xy_pins, PAD_FUNCTION_EN_1, PAD_सूचीECTION_SEL_1, PMX_TOUCH_XY_MASK, 0, 1);

अटल काष्ठा spear_gpio_pingroup spear1310_gpio_pingroup[] = अणु
	GPIO_PINGROUP(i2c0_pins),
	GPIO_PINGROUP(ssp0_pins),
	GPIO_PINGROUP(ssp0_cs0_pins),
	GPIO_PINGROUP(ssp0_cs1_2_pins),
	GPIO_PINGROUP(i2s0_pins),
	GPIO_PINGROUP(i2s1_pins),
	GPIO_PINGROUP(clcd_pins),
	GPIO_PINGROUP(clcd_high_res_pins),
	GPIO_PINGROUP(pin18),
	GPIO_PINGROUP(pin19),
	GPIO_PINGROUP(pin20),
	GPIO_PINGROUP(pin21),
	GPIO_PINGROUP(pin22),
	GPIO_PINGROUP(pin23),
	GPIO_PINGROUP(pin143),
	GPIO_PINGROUP(pin144),
	GPIO_PINGROUP(pin145),
	GPIO_PINGROUP(pin146),
	GPIO_PINGROUP(pin147),
	GPIO_PINGROUP(pin148),
	GPIO_PINGROUP(pin149),
	GPIO_PINGROUP(pin150),
	GPIO_PINGROUP(pin151),
	GPIO_PINGROUP(pin152),
	GPIO_PINGROUP(smi_2_chips_pins),
	GPIO_PINGROUP(pin54),
	GPIO_PINGROUP(pin55),
	GPIO_PINGROUP(pin56),
	GPIO_PINGROUP(pin57),
	GPIO_PINGROUP(pin58),
	GPIO_PINGROUP(pin59),
	GPIO_PINGROUP(pin60),
	GPIO_PINGROUP(pin61),
	GPIO_PINGROUP(pin62),
	GPIO_PINGROUP(pin63),
	GPIO_PINGROUP(pin_grp0),
	GPIO_PINGROUP(pin_grp1),
	GPIO_PINGROUP(pin_grp2),
	GPIO_PINGROUP(pin_grp3),
	GPIO_PINGROUP(pin_grp4),
	GPIO_PINGROUP(pin_grp5),
	GPIO_PINGROUP(pin_grp6),
	GPIO_PINGROUP(pin_grp7),
	GPIO_PINGROUP(pin_grp8),
	GPIO_PINGROUP(nand_16bit_pins),
	GPIO_PINGROUP(pin205),
	GPIO_PINGROUP(pin206),
	GPIO_PINGROUP(pin211),
	GPIO_PINGROUP(pin212),
	GPIO_PINGROUP(pin213),
	GPIO_PINGROUP(pin214),
	GPIO_PINGROUP(pin215),
	GPIO_PINGROUP(pin216),
	GPIO_PINGROUP(pin217),
	GPIO_PINGROUP(pin218),
	GPIO_PINGROUP(pin219),
	GPIO_PINGROUP(pin220),
	GPIO_PINGROUP(pin221),
	GPIO_PINGROUP(pin222),
	GPIO_PINGROUP(pin223),
	GPIO_PINGROUP(pin224),
	GPIO_PINGROUP(pin225),
	GPIO_PINGROUP(pin226),
	GPIO_PINGROUP(pin227),
	GPIO_PINGROUP(pin228),
	GPIO_PINGROUP(pin229),
	GPIO_PINGROUP(pin230),
	GPIO_PINGROUP(pin231),
	GPIO_PINGROUP(pin232),
	GPIO_PINGROUP(pin233),
	GPIO_PINGROUP(pin234),
	GPIO_PINGROUP(pin235),
	GPIO_PINGROUP(pin236),
	GPIO_PINGROUP(pin237),
	GPIO_PINGROUP(pin238),
	GPIO_PINGROUP(pin239),
	GPIO_PINGROUP(pin240),
	GPIO_PINGROUP(pin241),
	GPIO_PINGROUP(pin242),
	GPIO_PINGROUP(pin243),
	GPIO_PINGROUP(pin244),
	GPIO_PINGROUP(pin245),
	GPIO_PINGROUP(keyboard_rowcol6_8_pins),
	GPIO_PINGROUP(uart0_pins),
	GPIO_PINGROUP(uart0_modem_pins),
	GPIO_PINGROUP(gpt0_पंचांगr0_pins),
	GPIO_PINGROUP(gpt0_पंचांगr1_pins),
	GPIO_PINGROUP(gpt1_पंचांगr0_pins),
	GPIO_PINGROUP(gpt1_पंचांगr1_pins),
	GPIO_PINGROUP(touch_xy_pins),
पूर्ण;

अटल काष्ठा spear_pinctrl_machdata spear1310_machdata = अणु
	.pins = spear1310_pins,
	.npins = ARRAY_SIZE(spear1310_pins),
	.groups = spear1310_pingroups,
	.ngroups = ARRAY_SIZE(spear1310_pingroups),
	.functions = spear1310_functions,
	.nfunctions = ARRAY_SIZE(spear1310_functions),
	.gpio_pingroups = spear1310_gpio_pingroup,
	.ngpio_pingroups = ARRAY_SIZE(spear1310_gpio_pingroup),
	.modes_supported = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spear1310_pinctrl_of_match[] = अणु
	अणु
		.compatible = "st,spear1310-pinmux",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक spear1310_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस spear_pinctrl_probe(pdev, &spear1310_machdata);
पूर्ण

अटल काष्ठा platक्रमm_driver spear1310_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = spear1310_pinctrl_of_match,
	पूर्ण,
	.probe = spear1310_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init spear1310_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spear1310_pinctrl_driver);
पूर्ण
arch_initcall(spear1310_pinctrl_init);
