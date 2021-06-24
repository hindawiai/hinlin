<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr1340 pinmux
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

#घोषणा DRIVER_NAME "spear1340-pinmux"

/* pins */
अटल स्थिर काष्ठा pinctrl_pin_desc spear1340_pins[] = अणु
	SPEAR_PIN_0_TO_101,
	SPEAR_PIN_102_TO_245,
	PINCTRL_PIN(246, "PLGPIO246"),
	PINCTRL_PIN(247, "PLGPIO247"),
	PINCTRL_PIN(248, "PLGPIO248"),
	PINCTRL_PIN(249, "PLGPIO249"),
	PINCTRL_PIN(250, "PLGPIO250"),
	PINCTRL_PIN(251, "PLGPIO251"),
पूर्ण;

/* In SPEAr1340 there are two levels of pad muxing */
/* - pads as gpio OR peripherals */
#घोषणा PAD_FUNCTION_EN_1			0x668
#घोषणा PAD_FUNCTION_EN_2			0x66C
#घोषणा PAD_FUNCTION_EN_3			0x670
#घोषणा PAD_FUNCTION_EN_4			0x674
#घोषणा PAD_FUNCTION_EN_5			0x690
#घोषणा PAD_FUNCTION_EN_6			0x694
#घोषणा PAD_FUNCTION_EN_7			0x698
#घोषणा PAD_FUNCTION_EN_8			0x69C

/* - If peripherals, then primary OR alternate peripheral */
#घोषणा PAD_SHARED_IP_EN_1			0x6A0
#घोषणा PAD_SHARED_IP_EN_2			0x6A4

/*
 * Macro's क्रम first level of pmx - pads as gpio OR peripherals. There are 8
 * रेजिस्टरs with 32 bits each क्रम handling gpio pads, रेजिस्टर 8 has only 26
 * relevant bits.
 */
/* macro's for making pads as gpio's */
#घोषणा PADS_AS_GPIO_REG0_MASK			0xFFFFFFFE
#घोषणा PADS_AS_GPIO_REGS_MASK			0xFFFFFFFF
#घोषणा PADS_AS_GPIO_REG7_MASK			0x07FFFFFF

/* macro's क्रम making pads as peripherals */
#घोषणा FSMC_16_BIT_AND_KBD_ROW_COL_REG0_MASK	0x00000FFE
#घोषणा UART0_ENH_AND_GPT_REG0_MASK		0x0003F000
#घोषणा PWM1_AND_KBD_COL5_REG0_MASK		0x00040000
#घोषणा I2C1_REG0_MASK				0x01080000
#घोषणा SPDIF_IN_REG0_MASK			0x00100000
#घोषणा PWM2_AND_GPT0_TMR0_CPT_REG0_MASK	0x00400000
#घोषणा PWM3_AND_GPT0_TMR1_CLK_REG0_MASK	0x00800000
#घोषणा PWM0_AND_SSP0_CS1_REG0_MASK		0x02000000
#घोषणा VIP_AND_CAM3_REG0_MASK			0xFC200000
#घोषणा VIP_AND_CAM3_REG1_MASK			0x0000000F
#घोषणा VIP_REG1_MASK				0x00001EF0
#घोषणा VIP_AND_CAM2_REG1_MASK			0x007FE100
#घोषणा VIP_AND_CAM1_REG1_MASK			0xFF800000
#घोषणा VIP_AND_CAM1_REG2_MASK			0x00000003
#घोषणा VIP_AND_CAM0_REG2_MASK			0x00001FFC
#घोषणा SMI_REG2_MASK				0x0021E000
#घोषणा SSP0_REG2_MASK				0x001E0000
#घोषणा TS_AND_SSP0_CS2_REG2_MASK		0x00400000
#घोषणा UART0_REG2_MASK				0x01800000
#घोषणा UART1_REG2_MASK				0x06000000
#घोषणा I2S_IN_REG2_MASK			0xF8000000
#घोषणा DEVS_GRP_AND_MIPHY_DBG_REG3_MASK	0x000001FE
#घोषणा I2S_OUT_REG3_MASK			0x000001EF
#घोषणा I2S_IN_REG3_MASK			0x00000010
#घोषणा GMAC_REG3_MASK				0xFFFFFE00
#घोषणा GMAC_REG4_MASK				0x0000001F
#घोषणा DEVS_GRP_AND_MIPHY_DBG_REG4_MASK	0x7FFFFF20
#घोषणा SSP0_CS3_REG4_MASK			0x00000020
#घोषणा I2C0_REG4_MASK				0x000000C0
#घोषणा CEC0_REG4_MASK				0x00000100
#घोषणा CEC1_REG4_MASK				0x00000200
#घोषणा SPDIF_OUT_REG4_MASK			0x00000400
#घोषणा CLCD_REG4_MASK				0x7FFFF800
#घोषणा CLCD_AND_ARM_TRACE_REG4_MASK		0x80000000
#घोषणा CLCD_AND_ARM_TRACE_REG5_MASK		0xFFFFFFFF
#घोषणा CLCD_AND_ARM_TRACE_REG6_MASK		0x00000001
#घोषणा FSMC_PNOR_AND_MCIF_REG6_MASK		0x073FFFFE
#घोषणा MCIF_REG6_MASK				0xF8C00000
#घोषणा MCIF_REG7_MASK				0x000043FF
#घोषणा FSMC_8BIT_REG7_MASK			0x07FFBC00

/* other रेजिस्टरs */
#घोषणा PERIP_CFG				0x42C
	/* PERIP_CFG रेजिस्टर masks */
	#घोषणा SSP_CS_CTL_HW			0
	#घोषणा SSP_CS_CTL_SW			1
	#घोषणा SSP_CS_CTL_MASK			1
	#घोषणा SSP_CS_CTL_SHIFT		21
	#घोषणा SSP_CS_VAL_MASK			1
	#घोषणा SSP_CS_VAL_SHIFT		20
	#घोषणा SSP_CS_SEL_CS0			0
	#घोषणा SSP_CS_SEL_CS1			1
	#घोषणा SSP_CS_SEL_CS2			2
	#घोषणा SSP_CS_SEL_MASK			3
	#घोषणा SSP_CS_SEL_SHIFT		18

	#घोषणा I2S_CHNL_2_0			(0)
	#घोषणा I2S_CHNL_3_1			(1)
	#घोषणा I2S_CHNL_5_1			(2)
	#घोषणा I2S_CHNL_7_1			(3)
	#घोषणा I2S_CHNL_PLAY_SHIFT		(4)
	#घोषणा I2S_CHNL_PLAY_MASK		(3 << 4)
	#घोषणा I2S_CHNL_REC_SHIFT		(6)
	#घोषणा I2S_CHNL_REC_MASK		(3 << 6)

	#घोषणा SPDIF_OUT_ENB_MASK		(1 << 2)
	#घोषणा SPDIF_OUT_ENB_SHIFT		2

	#घोषणा MCIF_SEL_SD			1
	#घोषणा MCIF_SEL_CF			2
	#घोषणा MCIF_SEL_XD			3
	#घोषणा MCIF_SEL_MASK			3
	#घोषणा MCIF_SEL_SHIFT			0

#घोषणा GMAC_CLK_CFG				0x248
	#घोषणा GMAC_PHY_IF_GMII_VAL		(0 << 3)
	#घोषणा GMAC_PHY_IF_RGMII_VAL		(1 << 3)
	#घोषणा GMAC_PHY_IF_SGMII_VAL		(2 << 3)
	#घोषणा GMAC_PHY_IF_RMII_VAL		(4 << 3)
	#घोषणा GMAC_PHY_IF_SEL_MASK		(7 << 3)
	#घोषणा GMAC_PHY_INPUT_ENB_VAL		0
	#घोषणा GMAC_PHY_SYNT_ENB_VAL		1
	#घोषणा GMAC_PHY_CLK_MASK		1
	#घोषणा GMAC_PHY_CLK_SHIFT		2
	#घोषणा GMAC_PHY_125M_PAD_VAL		0
	#घोषणा GMAC_PHY_PLL2_VAL		1
	#घोषणा GMAC_PHY_OSC3_VAL		2
	#घोषणा GMAC_PHY_INPUT_CLK_MASK		3
	#घोषणा GMAC_PHY_INPUT_CLK_SHIFT	0

#घोषणा PCIE_SATA_CFG				0x424
	/* PCIE CFG MASks */
	#घोषणा PCIE_CFG_DEVICE_PRESENT		(1 << 11)
	#घोषणा PCIE_CFG_POWERUP_RESET		(1 << 10)
	#घोषणा PCIE_CFG_CORE_CLK_EN		(1 << 9)
	#घोषणा PCIE_CFG_AUX_CLK_EN		(1 << 8)
	#घोषणा SATA_CFG_TX_CLK_EN		(1 << 4)
	#घोषणा SATA_CFG_RX_CLK_EN		(1 << 3)
	#घोषणा SATA_CFG_POWERUP_RESET		(1 << 2)
	#घोषणा SATA_CFG_PM_CLK_EN		(1 << 1)
	#घोषणा PCIE_SATA_SEL_PCIE		(0)
	#घोषणा PCIE_SATA_SEL_SATA		(1)
	#घोषणा SATA_PCIE_CFG_MASK		0xF1F
	#घोषणा PCIE_CFG_VAL	(PCIE_SATA_SEL_PCIE | PCIE_CFG_AUX_CLK_EN | \
				PCIE_CFG_CORE_CLK_EN | PCIE_CFG_POWERUP_RESET |\
				PCIE_CFG_DEVICE_PRESENT)
	#घोषणा SATA_CFG_VAL	(PCIE_SATA_SEL_SATA | SATA_CFG_PM_CLK_EN | \
				SATA_CFG_POWERUP_RESET | SATA_CFG_RX_CLK_EN | \
				SATA_CFG_TX_CLK_EN)

/* Macro's क्रम second level of pmx - pads as primary OR alternate peripheral */
/* Write 0 to enable FSMC_16_BIT */
#घोषणा KBD_ROW_COL_MASK			(1 << 0)

/* Write 0 to enable UART0_ENH */
#घोषणा GPT_MASK				(1 << 1) /* Only clk & cpt */

/* Write 0 to enable PWM1 */
#घोषणा KBD_COL5_MASK				(1 << 2)

/* Write 0 to enable PWM2 */
#घोषणा GPT0_TMR0_CPT_MASK			(1 << 3) /* Only clk & cpt */

/* Write 0 to enable PWM3 */
#घोषणा GPT0_TMR1_CLK_MASK			(1 << 4) /* Only clk & cpt */

/* Write 0 to enable PWM0 */
#घोषणा SSP0_CS1_MASK				(1 << 5)

/* Write 0 to enable VIP */
#घोषणा CAM3_MASK				(1 << 6)

/* Write 0 to enable VIP */
#घोषणा CAM2_MASK				(1 << 7)

/* Write 0 to enable VIP */
#घोषणा CAM1_MASK				(1 << 8)

/* Write 0 to enable VIP */
#घोषणा CAM0_MASK				(1 << 9)

/* Write 0 to enable TS */
#घोषणा SSP0_CS2_MASK				(1 << 10)

/* Write 0 to enable FSMC PNOR */
#घोषणा MCIF_MASK				(1 << 11)

/* Write 0 to enable CLCD */
#घोषणा ARM_TRACE_MASK				(1 << 12)

/* Write 0 to enable I2S, SSP0_CS2, CEC0, 1, SPDIF out, CLCD */
#घोषणा MIPHY_DBG_MASK				(1 << 13)

/*
 * Pad multiplexing क्रम making all pads as gpio's. This is करोne to override the
 * values passed from bootloader and start from scratch.
 */
अटल स्थिर अचिन्हित pads_as_gpio_pins[] = अणु 12, 88, 89, 251 पूर्ण;
अटल काष्ठा spear_muxreg pads_as_gpio_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PADS_AS_GPIO_REG0_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = PADS_AS_GPIO_REGS_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = PADS_AS_GPIO_REGS_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_4,
		.mask = PADS_AS_GPIO_REGS_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = PADS_AS_GPIO_REGS_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_6,
		.mask = PADS_AS_GPIO_REGS_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_7,
		.mask = PADS_AS_GPIO_REGS_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_8,
		.mask = PADS_AS_GPIO_REG7_MASK,
		.val = 0x0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pads_as_gpio_modemux[] = अणु
	अणु
		.muxregs = pads_as_gpio_muxreg,
		.nmuxregs = ARRAY_SIZE(pads_as_gpio_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pads_as_gpio_pingroup = अणु
	.name = "pads_as_gpio_grp",
	.pins = pads_as_gpio_pins,
	.npins = ARRAY_SIZE(pads_as_gpio_pins),
	.modemuxs = pads_as_gpio_modemux,
	.nmodemuxs = ARRAY_SIZE(pads_as_gpio_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर pads_as_gpio_grps[] = अणु "pads_as_gpio_grp" पूर्ण;
अटल काष्ठा spear_function pads_as_gpio_function = अणु
	.name = "pads_as_gpio",
	.groups = pads_as_gpio_grps,
	.ngroups = ARRAY_SIZE(pads_as_gpio_grps),
पूर्ण;

/* Pad multiplexing क्रम fsmc_8bit device */
अटल स्थिर अचिन्हित fsmc_8bit_pins[] = अणु 233, 234, 235, 236, 238, 239, 240,
	241, 242, 243, 244, 245, 246, 247, 248, 249 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_8bit_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_8,
		.mask = FSMC_8BIT_REG7_MASK,
		.val = FSMC_8BIT_REG7_MASK,
	पूर्ण
पूर्ण;

अटल काष्ठा spear_modemux fsmc_8bit_modemux[] = अणु
	अणु
		.muxregs = fsmc_8bit_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_8bit_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup fsmc_8bit_pingroup = अणु
	.name = "fsmc_8bit_grp",
	.pins = fsmc_8bit_pins,
	.npins = ARRAY_SIZE(fsmc_8bit_pins),
	.modemuxs = fsmc_8bit_modemux,
	.nmodemuxs = ARRAY_SIZE(fsmc_8bit_modemux),
पूर्ण;

/* Pad multiplexing क्रम fsmc_16bit device */
अटल स्थिर अचिन्हित fsmc_16bit_pins[] = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_16bit_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = KBD_ROW_COL_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = FSMC_16_BIT_AND_KBD_ROW_COL_REG0_MASK,
		.val = FSMC_16_BIT_AND_KBD_ROW_COL_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux fsmc_16bit_modemux[] = अणु
	अणु
		.muxregs = fsmc_16bit_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_16bit_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup fsmc_16bit_pingroup = अणु
	.name = "fsmc_16bit_grp",
	.pins = fsmc_16bit_pins,
	.npins = ARRAY_SIZE(fsmc_16bit_pins),
	.modemuxs = fsmc_16bit_modemux,
	.nmodemuxs = ARRAY_SIZE(fsmc_16bit_modemux),
पूर्ण;

/* pad multiplexing क्रम fsmc_pnor device */
अटल स्थिर अचिन्हित fsmc_pnor_pins[] = अणु 192, 193, 194, 195, 196, 197, 198,
	199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212,
	215, 216, 217 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_pnor_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = MCIF_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_7,
		.mask = FSMC_PNOR_AND_MCIF_REG6_MASK,
		.val = FSMC_PNOR_AND_MCIF_REG6_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux fsmc_pnor_modemux[] = अणु
	अणु
		.muxregs = fsmc_pnor_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_pnor_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup fsmc_pnor_pingroup = अणु
	.name = "fsmc_pnor_grp",
	.pins = fsmc_pnor_pins,
	.npins = ARRAY_SIZE(fsmc_pnor_pins),
	.modemuxs = fsmc_pnor_modemux,
	.nmodemuxs = ARRAY_SIZE(fsmc_pnor_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर fsmc_grps[] = अणु "fsmc_8bit_grp", "fsmc_16bit_grp",
	"fsmc_pnor_grp" पूर्ण;
अटल काष्ठा spear_function fsmc_function = अणु
	.name = "fsmc",
	.groups = fsmc_grps,
	.ngroups = ARRAY_SIZE(fsmc_grps),
पूर्ण;

/* pad multiplexing क्रम keyboard rows-cols device */
अटल स्थिर अचिन्हित keyboard_row_col_pins[] = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10 पूर्ण;
अटल काष्ठा spear_muxreg keyboard_row_col_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = KBD_ROW_COL_MASK,
		.val = KBD_ROW_COL_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = FSMC_16_BIT_AND_KBD_ROW_COL_REG0_MASK,
		.val = FSMC_16_BIT_AND_KBD_ROW_COL_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux keyboard_row_col_modemux[] = अणु
	अणु
		.muxregs = keyboard_row_col_muxreg,
		.nmuxregs = ARRAY_SIZE(keyboard_row_col_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup keyboard_row_col_pingroup = अणु
	.name = "keyboard_row_col_grp",
	.pins = keyboard_row_col_pins,
	.npins = ARRAY_SIZE(keyboard_row_col_pins),
	.modemuxs = keyboard_row_col_modemux,
	.nmodemuxs = ARRAY_SIZE(keyboard_row_col_modemux),
पूर्ण;

/* pad multiplexing क्रम keyboard col5 device */
अटल स्थिर अचिन्हित keyboard_col5_pins[] = अणु 17 पूर्ण;
अटल काष्ठा spear_muxreg keyboard_col5_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = KBD_COL5_MASK,
		.val = KBD_COL5_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PWM1_AND_KBD_COL5_REG0_MASK,
		.val = PWM1_AND_KBD_COL5_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux keyboard_col5_modemux[] = अणु
	अणु
		.muxregs = keyboard_col5_muxreg,
		.nmuxregs = ARRAY_SIZE(keyboard_col5_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup keyboard_col5_pingroup = अणु
	.name = "keyboard_col5_grp",
	.pins = keyboard_col5_pins,
	.npins = ARRAY_SIZE(keyboard_col5_pins),
	.modemuxs = keyboard_col5_modemux,
	.nmodemuxs = ARRAY_SIZE(keyboard_col5_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर keyboard_grps[] = अणु "keyboard_row_col_grp",
	"keyboard_col5_grp" पूर्ण;
अटल काष्ठा spear_function keyboard_function = अणु
	.name = "keyboard",
	.groups = keyboard_grps,
	.ngroups = ARRAY_SIZE(keyboard_grps),
पूर्ण;

/* pad multiplexing क्रम spdअगर_in device */
अटल स्थिर अचिन्हित spdअगर_in_pins[] = अणु 19 पूर्ण;
अटल काष्ठा spear_muxreg spdअगर_in_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = SPDIF_IN_REG0_MASK,
		.val = SPDIF_IN_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux spdअगर_in_modemux[] = अणु
	अणु
		.muxregs = spdअगर_in_muxreg,
		.nmuxregs = ARRAY_SIZE(spdअगर_in_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup spdअगर_in_pingroup = अणु
	.name = "spdif_in_grp",
	.pins = spdअगर_in_pins,
	.npins = ARRAY_SIZE(spdअगर_in_pins),
	.modemuxs = spdअगर_in_modemux,
	.nmodemuxs = ARRAY_SIZE(spdअगर_in_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर spdअगर_in_grps[] = अणु "spdif_in_grp" पूर्ण;
अटल काष्ठा spear_function spdअगर_in_function = अणु
	.name = "spdif_in",
	.groups = spdअगर_in_grps,
	.ngroups = ARRAY_SIZE(spdअगर_in_grps),
पूर्ण;

/* pad multiplexing क्रम spdअगर_out device */
अटल स्थिर अचिन्हित spdअगर_out_pins[] = अणु 137 पूर्ण;
अटल काष्ठा spear_muxreg spdअगर_out_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = SPDIF_OUT_REG4_MASK,
		.val = SPDIF_OUT_REG4_MASK,
	पूर्ण, अणु
		.reg = PERIP_CFG,
		.mask = SPDIF_OUT_ENB_MASK,
		.val = SPDIF_OUT_ENB_MASK,
	पूर्ण
पूर्ण;

अटल काष्ठा spear_modemux spdअगर_out_modemux[] = अणु
	अणु
		.muxregs = spdअगर_out_muxreg,
		.nmuxregs = ARRAY_SIZE(spdअगर_out_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup spdअगर_out_pingroup = अणु
	.name = "spdif_out_grp",
	.pins = spdअगर_out_pins,
	.npins = ARRAY_SIZE(spdअगर_out_pins),
	.modemuxs = spdअगर_out_modemux,
	.nmodemuxs = ARRAY_SIZE(spdअगर_out_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर spdअगर_out_grps[] = अणु "spdif_out_grp" पूर्ण;
अटल काष्ठा spear_function spdअगर_out_function = अणु
	.name = "spdif_out",
	.groups = spdअगर_out_grps,
	.ngroups = ARRAY_SIZE(spdअगर_out_grps),
पूर्ण;

/* pad multiplexing क्रम gpt_0_1 device */
अटल स्थिर अचिन्हित gpt_0_1_pins[] = अणु 11, 12, 13, 14, 15, 16, 21, 22 पूर्ण;
अटल काष्ठा spear_muxreg gpt_0_1_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = GPT_MASK | GPT0_TMR0_CPT_MASK | GPT0_TMR1_CLK_MASK,
		.val = GPT_MASK | GPT0_TMR0_CPT_MASK | GPT0_TMR1_CLK_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = UART0_ENH_AND_GPT_REG0_MASK |
			PWM2_AND_GPT0_TMR0_CPT_REG0_MASK |
			PWM3_AND_GPT0_TMR1_CLK_REG0_MASK,
		.val = UART0_ENH_AND_GPT_REG0_MASK |
			PWM2_AND_GPT0_TMR0_CPT_REG0_MASK |
			PWM3_AND_GPT0_TMR1_CLK_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpt_0_1_modemux[] = अणु
	अणु
		.muxregs = gpt_0_1_muxreg,
		.nmuxregs = ARRAY_SIZE(gpt_0_1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpt_0_1_pingroup = अणु
	.name = "gpt_0_1_grp",
	.pins = gpt_0_1_pins,
	.npins = ARRAY_SIZE(gpt_0_1_pins),
	.modemuxs = gpt_0_1_modemux,
	.nmodemuxs = ARRAY_SIZE(gpt_0_1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpt_0_1_grps[] = अणु "gpt_0_1_grp" पूर्ण;
अटल काष्ठा spear_function gpt_0_1_function = अणु
	.name = "gpt_0_1",
	.groups = gpt_0_1_grps,
	.ngroups = ARRAY_SIZE(gpt_0_1_grps),
पूर्ण;

/* pad multiplexing क्रम pwm0 device */
अटल स्थिर अचिन्हित pwm0_pins[] = अणु 24 पूर्ण;
अटल काष्ठा spear_muxreg pwm0_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = SSP0_CS1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PWM0_AND_SSP0_CS1_REG0_MASK,
		.val = PWM0_AND_SSP0_CS1_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_modemux[] = अणु
	अणु
		.muxregs = pwm0_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm0_pingroup = अणु
	.name = "pwm0_grp",
	.pins = pwm0_pins,
	.npins = ARRAY_SIZE(pwm0_pins),
	.modemuxs = pwm0_modemux,
	.nmodemuxs = ARRAY_SIZE(pwm0_modemux),
पूर्ण;

/* pad multiplexing क्रम pwm1 device */
अटल स्थिर अचिन्हित pwm1_pins[] = अणु 17 पूर्ण;
अटल काष्ठा spear_muxreg pwm1_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = KBD_COL5_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PWM1_AND_KBD_COL5_REG0_MASK,
		.val = PWM1_AND_KBD_COL5_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm1_modemux[] = अणु
	अणु
		.muxregs = pwm1_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm1_pingroup = अणु
	.name = "pwm1_grp",
	.pins = pwm1_pins,
	.npins = ARRAY_SIZE(pwm1_pins),
	.modemuxs = pwm1_modemux,
	.nmodemuxs = ARRAY_SIZE(pwm1_modemux),
पूर्ण;

/* pad multiplexing क्रम pwm2 device */
अटल स्थिर अचिन्हित pwm2_pins[] = अणु 21 पूर्ण;
अटल काष्ठा spear_muxreg pwm2_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = GPT0_TMR0_CPT_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PWM2_AND_GPT0_TMR0_CPT_REG0_MASK,
		.val = PWM2_AND_GPT0_TMR0_CPT_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm2_modemux[] = अणु
	अणु
		.muxregs = pwm2_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm2_pingroup = अणु
	.name = "pwm2_grp",
	.pins = pwm2_pins,
	.npins = ARRAY_SIZE(pwm2_pins),
	.modemuxs = pwm2_modemux,
	.nmodemuxs = ARRAY_SIZE(pwm2_modemux),
पूर्ण;

/* pad multiplexing क्रम pwm3 device */
अटल स्थिर अचिन्हित pwm3_pins[] = अणु 22 पूर्ण;
अटल काष्ठा spear_muxreg pwm3_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = GPT0_TMR1_CLK_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PWM3_AND_GPT0_TMR1_CLK_REG0_MASK,
		.val = PWM3_AND_GPT0_TMR1_CLK_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_modemux[] = अणु
	अणु
		.muxregs = pwm3_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm3_pingroup = अणु
	.name = "pwm3_grp",
	.pins = pwm3_pins,
	.npins = ARRAY_SIZE(pwm3_pins),
	.modemuxs = pwm3_modemux,
	.nmodemuxs = ARRAY_SIZE(pwm3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर pwm_grps[] = अणु "pwm0_grp", "pwm1_grp", "pwm2_grp",
	"pwm3_grp" पूर्ण;
अटल काष्ठा spear_function pwm_function = अणु
	.name = "pwm",
	.groups = pwm_grps,
	.ngroups = ARRAY_SIZE(pwm_grps),
पूर्ण;

/* pad multiplexing क्रम vip_mux device */
अटल स्थिर अचिन्हित vip_mux_pins[] = अणु 35, 36, 37, 38, 40, 41, 42, 43 पूर्ण;
अटल काष्ठा spear_muxreg vip_mux_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_REG1_MASK,
		.val = VIP_REG1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux vip_mux_modemux[] = अणु
	अणु
		.muxregs = vip_mux_muxreg,
		.nmuxregs = ARRAY_SIZE(vip_mux_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup vip_mux_pingroup = अणु
	.name = "vip_mux_grp",
	.pins = vip_mux_pins,
	.npins = ARRAY_SIZE(vip_mux_pins),
	.modemuxs = vip_mux_modemux,
	.nmodemuxs = ARRAY_SIZE(vip_mux_modemux),
पूर्ण;

/* pad multiplexing क्रम vip_mux_cam0 (disables cam0) device */
अटल स्थिर अचिन्हित vip_mux_cam0_pins[] = अणु 65, 66, 67, 68, 69, 70, 71, 72,
	73, 74, 75 पूर्ण;
अटल काष्ठा spear_muxreg vip_mux_cam0_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = VIP_AND_CAM0_REG2_MASK,
		.val = VIP_AND_CAM0_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux vip_mux_cam0_modemux[] = अणु
	अणु
		.muxregs = vip_mux_cam0_muxreg,
		.nmuxregs = ARRAY_SIZE(vip_mux_cam0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup vip_mux_cam0_pingroup = अणु
	.name = "vip_mux_cam0_grp",
	.pins = vip_mux_cam0_pins,
	.npins = ARRAY_SIZE(vip_mux_cam0_pins),
	.modemuxs = vip_mux_cam0_modemux,
	.nmodemuxs = ARRAY_SIZE(vip_mux_cam0_modemux),
पूर्ण;

/* pad multiplexing क्रम vip_mux_cam1 (disables cam1) device */
अटल स्थिर अचिन्हित vip_mux_cam1_pins[] = अणु 54, 55, 56, 57, 58, 59, 60, 61,
	62, 63, 64 पूर्ण;
अटल काष्ठा spear_muxreg vip_mux_cam1_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_AND_CAM1_REG1_MASK,
		.val = VIP_AND_CAM1_REG1_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = VIP_AND_CAM1_REG2_MASK,
		.val = VIP_AND_CAM1_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux vip_mux_cam1_modemux[] = अणु
	अणु
		.muxregs = vip_mux_cam1_muxreg,
		.nmuxregs = ARRAY_SIZE(vip_mux_cam1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup vip_mux_cam1_pingroup = अणु
	.name = "vip_mux_cam1_grp",
	.pins = vip_mux_cam1_pins,
	.npins = ARRAY_SIZE(vip_mux_cam1_pins),
	.modemuxs = vip_mux_cam1_modemux,
	.nmodemuxs = ARRAY_SIZE(vip_mux_cam1_modemux),
पूर्ण;

/* pad multiplexing क्रम vip_mux_cam2 (disables cam2) device */
अटल स्थिर अचिन्हित vip_mux_cam2_pins[] = अणु 39, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53 पूर्ण;
अटल काष्ठा spear_muxreg vip_mux_cam2_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM2_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_AND_CAM2_REG1_MASK,
		.val = VIP_AND_CAM2_REG1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux vip_mux_cam2_modemux[] = अणु
	अणु
		.muxregs = vip_mux_cam2_muxreg,
		.nmuxregs = ARRAY_SIZE(vip_mux_cam2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup vip_mux_cam2_pingroup = अणु
	.name = "vip_mux_cam2_grp",
	.pins = vip_mux_cam2_pins,
	.npins = ARRAY_SIZE(vip_mux_cam2_pins),
	.modemuxs = vip_mux_cam2_modemux,
	.nmodemuxs = ARRAY_SIZE(vip_mux_cam2_modemux),
पूर्ण;

/* pad multiplexing क्रम vip_mux_cam3 (disables cam3) device */
अटल स्थिर अचिन्हित vip_mux_cam3_pins[] = अणु 20, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34 पूर्ण;
अटल काष्ठा spear_muxreg vip_mux_cam3_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM3_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = VIP_AND_CAM3_REG0_MASK,
		.val = VIP_AND_CAM3_REG0_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_AND_CAM3_REG1_MASK,
		.val = VIP_AND_CAM3_REG1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux vip_mux_cam3_modemux[] = अणु
	अणु
		.muxregs = vip_mux_cam3_muxreg,
		.nmuxregs = ARRAY_SIZE(vip_mux_cam3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup vip_mux_cam3_pingroup = अणु
	.name = "vip_mux_cam3_grp",
	.pins = vip_mux_cam3_pins,
	.npins = ARRAY_SIZE(vip_mux_cam3_pins),
	.modemuxs = vip_mux_cam3_modemux,
	.nmodemuxs = ARRAY_SIZE(vip_mux_cam3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर vip_grps[] = अणु "vip_mux_grp", "vip_mux_cam0_grp" ,
	"vip_mux_cam1_grp" , "vip_mux_cam2_grp", "vip_mux_cam3_grp" पूर्ण;
अटल काष्ठा spear_function vip_function = अणु
	.name = "vip",
	.groups = vip_grps,
	.ngroups = ARRAY_SIZE(vip_grps),
पूर्ण;

/* pad multiplexing क्रम cam0 device */
अटल स्थिर अचिन्हित cam0_pins[] = अणु 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75
पूर्ण;
अटल काष्ठा spear_muxreg cam0_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM0_MASK,
		.val = CAM0_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = VIP_AND_CAM0_REG2_MASK,
		.val = VIP_AND_CAM0_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cam0_modemux[] = अणु
	अणु
		.muxregs = cam0_muxreg,
		.nmuxregs = ARRAY_SIZE(cam0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cam0_pingroup = अणु
	.name = "cam0_grp",
	.pins = cam0_pins,
	.npins = ARRAY_SIZE(cam0_pins),
	.modemuxs = cam0_modemux,
	.nmodemuxs = ARRAY_SIZE(cam0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cam0_grps[] = अणु "cam0_grp" पूर्ण;
अटल काष्ठा spear_function cam0_function = अणु
	.name = "cam0",
	.groups = cam0_grps,
	.ngroups = ARRAY_SIZE(cam0_grps),
पूर्ण;

/* pad multiplexing क्रम cam1 device */
अटल स्थिर अचिन्हित cam1_pins[] = अणु 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64
पूर्ण;
अटल काष्ठा spear_muxreg cam1_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM1_MASK,
		.val = CAM1_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_AND_CAM1_REG1_MASK,
		.val = VIP_AND_CAM1_REG1_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = VIP_AND_CAM1_REG2_MASK,
		.val = VIP_AND_CAM1_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cam1_modemux[] = अणु
	अणु
		.muxregs = cam1_muxreg,
		.nmuxregs = ARRAY_SIZE(cam1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cam1_pingroup = अणु
	.name = "cam1_grp",
	.pins = cam1_pins,
	.npins = ARRAY_SIZE(cam1_pins),
	.modemuxs = cam1_modemux,
	.nmodemuxs = ARRAY_SIZE(cam1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cam1_grps[] = अणु "cam1_grp" पूर्ण;
अटल काष्ठा spear_function cam1_function = अणु
	.name = "cam1",
	.groups = cam1_grps,
	.ngroups = ARRAY_SIZE(cam1_grps),
पूर्ण;

/* pad multiplexing क्रम cam2 device */
अटल स्थिर अचिन्हित cam2_pins[] = अणु 39, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53
पूर्ण;
अटल काष्ठा spear_muxreg cam2_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM2_MASK,
		.val = CAM2_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_AND_CAM2_REG1_MASK,
		.val = VIP_AND_CAM2_REG1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cam2_modemux[] = अणु
	अणु
		.muxregs = cam2_muxreg,
		.nmuxregs = ARRAY_SIZE(cam2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cam2_pingroup = अणु
	.name = "cam2_grp",
	.pins = cam2_pins,
	.npins = ARRAY_SIZE(cam2_pins),
	.modemuxs = cam2_modemux,
	.nmodemuxs = ARRAY_SIZE(cam2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cam2_grps[] = अणु "cam2_grp" पूर्ण;
अटल काष्ठा spear_function cam2_function = अणु
	.name = "cam2",
	.groups = cam2_grps,
	.ngroups = ARRAY_SIZE(cam2_grps),
पूर्ण;

/* pad multiplexing क्रम cam3 device */
अटल स्थिर अचिन्हित cam3_pins[] = अणु 20, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34
पूर्ण;
अटल काष्ठा spear_muxreg cam3_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = CAM3_MASK,
		.val = CAM3_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = VIP_AND_CAM3_REG0_MASK,
		.val = VIP_AND_CAM3_REG0_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_2,
		.mask = VIP_AND_CAM3_REG1_MASK,
		.val = VIP_AND_CAM3_REG1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cam3_modemux[] = अणु
	अणु
		.muxregs = cam3_muxreg,
		.nmuxregs = ARRAY_SIZE(cam3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cam3_pingroup = अणु
	.name = "cam3_grp",
	.pins = cam3_pins,
	.npins = ARRAY_SIZE(cam3_pins),
	.modemuxs = cam3_modemux,
	.nmodemuxs = ARRAY_SIZE(cam3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cam3_grps[] = अणु "cam3_grp" पूर्ण;
अटल काष्ठा spear_function cam3_function = अणु
	.name = "cam3",
	.groups = cam3_grps,
	.ngroups = ARRAY_SIZE(cam3_grps),
पूर्ण;

/* pad multiplexing क्रम smi device */
अटल स्थिर अचिन्हित smi_pins[] = अणु 76, 77, 78, 79, 84 पूर्ण;
अटल काष्ठा spear_muxreg smi_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = SMI_REG2_MASK,
		.val = SMI_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux smi_modemux[] = अणु
	अणु
		.muxregs = smi_muxreg,
		.nmuxregs = ARRAY_SIZE(smi_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup smi_pingroup = अणु
	.name = "smi_grp",
	.pins = smi_pins,
	.npins = ARRAY_SIZE(smi_pins),
	.modemuxs = smi_modemux,
	.nmodemuxs = ARRAY_SIZE(smi_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर smi_grps[] = अणु "smi_grp" पूर्ण;
अटल काष्ठा spear_function smi_function = अणु
	.name = "smi",
	.groups = smi_grps,
	.ngroups = ARRAY_SIZE(smi_grps),
पूर्ण;

/* pad multiplexing क्रम ssp0 device */
अटल स्थिर अचिन्हित ssp0_pins[] = अणु 80, 81, 82, 83 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = SSP0_REG2_MASK,
		.val = SSP0_REG2_MASK,
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

/* pad multiplexing क्रम ssp0_cs1 device */
अटल स्थिर अचिन्हित ssp0_cs1_pins[] = अणु 24 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_cs1_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = SSP0_CS1_MASK,
		.val = SSP0_CS1_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = PWM0_AND_SSP0_CS1_REG0_MASK,
		.val = PWM0_AND_SSP0_CS1_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp0_cs1_modemux[] = अणु
	अणु
		.muxregs = ssp0_cs1_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp0_cs1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp0_cs1_pingroup = अणु
	.name = "ssp0_cs1_grp",
	.pins = ssp0_cs1_pins,
	.npins = ARRAY_SIZE(ssp0_cs1_pins),
	.modemuxs = ssp0_cs1_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp0_cs1_modemux),
पूर्ण;

/* pad multiplexing क्रम ssp0_cs2 device */
अटल स्थिर अचिन्हित ssp0_cs2_pins[] = अणु 85 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_cs2_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = SSP0_CS2_MASK,
		.val = SSP0_CS2_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = TS_AND_SSP0_CS2_REG2_MASK,
		.val = TS_AND_SSP0_CS2_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp0_cs2_modemux[] = अणु
	अणु
		.muxregs = ssp0_cs2_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp0_cs2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp0_cs2_pingroup = अणु
	.name = "ssp0_cs2_grp",
	.pins = ssp0_cs2_pins,
	.npins = ARRAY_SIZE(ssp0_cs2_pins),
	.modemuxs = ssp0_cs2_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp0_cs2_modemux),
पूर्ण;

/* pad multiplexing क्रम ssp0_cs3 device */
अटल स्थिर अचिन्हित ssp0_cs3_pins[] = अणु 132 पूर्ण;
अटल काष्ठा spear_muxreg ssp0_cs3_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = SSP0_CS3_REG4_MASK,
		.val = SSP0_CS3_REG4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp0_cs3_modemux[] = अणु
	अणु
		.muxregs = ssp0_cs3_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp0_cs3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp0_cs3_pingroup = अणु
	.name = "ssp0_cs3_grp",
	.pins = ssp0_cs3_pins,
	.npins = ARRAY_SIZE(ssp0_cs3_pins),
	.modemuxs = ssp0_cs3_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp0_cs3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp0_grps[] = अणु "ssp0_grp", "ssp0_cs1_grp",
	"ssp0_cs2_grp", "ssp0_cs3_grp" पूर्ण;
अटल काष्ठा spear_function ssp0_function = अणु
	.name = "ssp0",
	.groups = ssp0_grps,
	.ngroups = ARRAY_SIZE(ssp0_grps),
पूर्ण;

/* pad multiplexing क्रम uart0 device */
अटल स्थिर अचिन्हित uart0_pins[] = अणु 86, 87 पूर्ण;
अटल काष्ठा spear_muxreg uart0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = UART0_REG2_MASK,
		.val = UART0_REG2_MASK,
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

/* pad multiplexing क्रम uart0_enh device */
अटल स्थिर अचिन्हित uart0_enh_pins[] = अणु 11, 12, 13, 14, 15, 16 पूर्ण;
अटल काष्ठा spear_muxreg uart0_enh_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = GPT_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = UART0_ENH_AND_GPT_REG0_MASK,
		.val = UART0_ENH_AND_GPT_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart0_enh_modemux[] = अणु
	अणु
		.muxregs = uart0_enh_muxreg,
		.nmuxregs = ARRAY_SIZE(uart0_enh_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart0_enh_pingroup = अणु
	.name = "uart0_enh_grp",
	.pins = uart0_enh_pins,
	.npins = ARRAY_SIZE(uart0_enh_pins),
	.modemuxs = uart0_enh_modemux,
	.nmodemuxs = ARRAY_SIZE(uart0_enh_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart0_grps[] = अणु "uart0_grp", "uart0_enh_grp" पूर्ण;
अटल काष्ठा spear_function uart0_function = अणु
	.name = "uart0",
	.groups = uart0_grps,
	.ngroups = ARRAY_SIZE(uart0_grps),
पूर्ण;

/* pad multiplexing क्रम uart1 device */
अटल स्थिर अचिन्हित uart1_pins[] = अणु 88, 89 पूर्ण;
अटल काष्ठा spear_muxreg uart1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = UART1_REG2_MASK,
		.val = UART1_REG2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modemux[] = अणु
	अणु
		.muxregs = uart1_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart1_pingroup = अणु
	.name = "uart1_grp",
	.pins = uart1_pins,
	.npins = ARRAY_SIZE(uart1_pins),
	.modemuxs = uart1_modemux,
	.nmodemuxs = ARRAY_SIZE(uart1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart1_grps[] = अणु "uart1_grp" पूर्ण;
अटल काष्ठा spear_function uart1_function = अणु
	.name = "uart1",
	.groups = uart1_grps,
	.ngroups = ARRAY_SIZE(uart1_grps),
पूर्ण;

/* pad multiplexing क्रम i2s_in device */
अटल स्थिर अचिन्हित i2s_in_pins[] = अणु 90, 91, 92, 93, 94, 99 पूर्ण;
अटल काष्ठा spear_muxreg i2s_in_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_3,
		.mask = I2S_IN_REG2_MASK,
		.val = I2S_IN_REG2_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_4,
		.mask = I2S_IN_REG3_MASK,
		.val = I2S_IN_REG3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2s_in_modemux[] = अणु
	अणु
		.muxregs = i2s_in_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s_in_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2s_in_pingroup = अणु
	.name = "i2s_in_grp",
	.pins = i2s_in_pins,
	.npins = ARRAY_SIZE(i2s_in_pins),
	.modemuxs = i2s_in_modemux,
	.nmodemuxs = ARRAY_SIZE(i2s_in_modemux),
पूर्ण;

/* pad multiplexing क्रम i2s_out device */
अटल स्थिर अचिन्हित i2s_out_pins[] = अणु 95, 96, 97, 98, 100, 101, 102, 103 पूर्ण;
अटल काष्ठा spear_muxreg i2s_out_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_4,
		.mask = I2S_OUT_REG3_MASK,
		.val = I2S_OUT_REG3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2s_out_modemux[] = अणु
	अणु
		.muxregs = i2s_out_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s_out_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2s_out_pingroup = अणु
	.name = "i2s_out_grp",
	.pins = i2s_out_pins,
	.npins = ARRAY_SIZE(i2s_out_pins),
	.modemuxs = i2s_out_modemux,
	.nmodemuxs = ARRAY_SIZE(i2s_out_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2s_grps[] = अणु "i2s_in_grp", "i2s_out_grp" पूर्ण;
अटल काष्ठा spear_function i2s_function = अणु
	.name = "i2s",
	.groups = i2s_grps,
	.ngroups = ARRAY_SIZE(i2s_grps),
पूर्ण;

/* pad multiplexing क्रम gmac device */
अटल स्थिर अचिन्हित gmac_pins[] = अणु 104, 105, 106, 107, 108, 109, 110, 111,
	112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125,
	126, 127, 128, 129, 130, 131 पूर्ण;
#घोषणा GMAC_MUXREG				\
	अणु					\
		.reg = PAD_FUNCTION_EN_4,	\
		.mask = GMAC_REG3_MASK,		\
		.val = GMAC_REG3_MASK,		\
	पूर्ण, अणु					\
		.reg = PAD_FUNCTION_EN_5,	\
		.mask = GMAC_REG4_MASK,		\
		.val = GMAC_REG4_MASK,		\
	पूर्ण

/* pad multiplexing क्रम gmii device */
अटल काष्ठा spear_muxreg gmii_muxreg[] = अणु
	GMAC_MUXREG,
	अणु
		.reg = GMAC_CLK_CFG,
		.mask = GMAC_PHY_IF_SEL_MASK,
		.val = GMAC_PHY_IF_GMII_VAL,
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
	.pins = gmac_pins,
	.npins = ARRAY_SIZE(gmac_pins),
	.modemuxs = gmii_modemux,
	.nmodemuxs = ARRAY_SIZE(gmii_modemux),
पूर्ण;

/* pad multiplexing क्रम rgmii device */
अटल काष्ठा spear_muxreg rgmii_muxreg[] = अणु
	GMAC_MUXREG,
	अणु
		.reg = GMAC_CLK_CFG,
		.mask = GMAC_PHY_IF_SEL_MASK,
		.val = GMAC_PHY_IF_RGMII_VAL,
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
	.pins = gmac_pins,
	.npins = ARRAY_SIZE(gmac_pins),
	.modemuxs = rgmii_modemux,
	.nmodemuxs = ARRAY_SIZE(rgmii_modemux),
पूर्ण;

/* pad multiplexing क्रम rmii device */
अटल काष्ठा spear_muxreg rmii_muxreg[] = अणु
	GMAC_MUXREG,
	अणु
		.reg = GMAC_CLK_CFG,
		.mask = GMAC_PHY_IF_SEL_MASK,
		.val = GMAC_PHY_IF_RMII_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux rmii_modemux[] = अणु
	अणु
		.muxregs = rmii_muxreg,
		.nmuxregs = ARRAY_SIZE(rmii_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup rmii_pingroup = अणु
	.name = "rmii_grp",
	.pins = gmac_pins,
	.npins = ARRAY_SIZE(gmac_pins),
	.modemuxs = rmii_modemux,
	.nmodemuxs = ARRAY_SIZE(rmii_modemux),
पूर्ण;

/* pad multiplexing क्रम sgmii device */
अटल काष्ठा spear_muxreg sgmii_muxreg[] = अणु
	GMAC_MUXREG,
	अणु
		.reg = GMAC_CLK_CFG,
		.mask = GMAC_PHY_IF_SEL_MASK,
		.val = GMAC_PHY_IF_SGMII_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sgmii_modemux[] = अणु
	अणु
		.muxregs = sgmii_muxreg,
		.nmuxregs = ARRAY_SIZE(sgmii_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sgmii_pingroup = अणु
	.name = "sgmii_grp",
	.pins = gmac_pins,
	.npins = ARRAY_SIZE(gmac_pins),
	.modemuxs = sgmii_modemux,
	.nmodemuxs = ARRAY_SIZE(sgmii_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gmac_grps[] = अणु "gmii_grp", "rgmii_grp", "rmii_grp",
	"sgmii_grp" पूर्ण;
अटल काष्ठा spear_function gmac_function = अणु
	.name = "gmac",
	.groups = gmac_grps,
	.ngroups = ARRAY_SIZE(gmac_grps),
पूर्ण;

/* pad multiplexing क्रम i2c0 device */
अटल स्थिर अचिन्हित i2c0_pins[] = अणु 133, 134 पूर्ण;
अटल काष्ठा spear_muxreg i2c0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = I2C0_REG4_MASK,
		.val = I2C0_REG4_MASK,
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

/* pad multiplexing क्रम i2c1 device */
अटल स्थिर अचिन्हित i2c1_pins[] = अणु 18, 23 पूर्ण;
अटल काष्ठा spear_muxreg i2c1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_1,
		.mask = I2C1_REG0_MASK,
		.val = I2C1_REG0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c1_modemux[] = अणु
	अणु
		.muxregs = i2c1_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c1_pingroup = अणु
	.name = "i2c1_grp",
	.pins = i2c1_pins,
	.npins = ARRAY_SIZE(i2c1_pins),
	.modemuxs = i2c1_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c1_grps[] = अणु "i2c1_grp" पूर्ण;
अटल काष्ठा spear_function i2c1_function = अणु
	.name = "i2c1",
	.groups = i2c1_grps,
	.ngroups = ARRAY_SIZE(i2c1_grps),
पूर्ण;

/* pad multiplexing क्रम cec0 device */
अटल स्थिर अचिन्हित cec0_pins[] = अणु 135 पूर्ण;
अटल काष्ठा spear_muxreg cec0_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = CEC0_REG4_MASK,
		.val = CEC0_REG4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cec0_modemux[] = अणु
	अणु
		.muxregs = cec0_muxreg,
		.nmuxregs = ARRAY_SIZE(cec0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cec0_pingroup = अणु
	.name = "cec0_grp",
	.pins = cec0_pins,
	.npins = ARRAY_SIZE(cec0_pins),
	.modemuxs = cec0_modemux,
	.nmodemuxs = ARRAY_SIZE(cec0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cec0_grps[] = अणु "cec0_grp" पूर्ण;
अटल काष्ठा spear_function cec0_function = अणु
	.name = "cec0",
	.groups = cec0_grps,
	.ngroups = ARRAY_SIZE(cec0_grps),
पूर्ण;

/* pad multiplexing क्रम cec1 device */
अटल स्थिर अचिन्हित cec1_pins[] = अणु 136 पूर्ण;
अटल काष्ठा spear_muxreg cec1_muxreg[] = अणु
	अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = CEC1_REG4_MASK,
		.val = CEC1_REG4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux cec1_modemux[] = अणु
	अणु
		.muxregs = cec1_muxreg,
		.nmuxregs = ARRAY_SIZE(cec1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup cec1_pingroup = अणु
	.name = "cec1_grp",
	.pins = cec1_pins,
	.npins = ARRAY_SIZE(cec1_pins),
	.modemuxs = cec1_modemux,
	.nmodemuxs = ARRAY_SIZE(cec1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cec1_grps[] = अणु "cec1_grp" पूर्ण;
अटल काष्ठा spear_function cec1_function = अणु
	.name = "cec1",
	.groups = cec1_grps,
	.ngroups = ARRAY_SIZE(cec1_grps),
पूर्ण;

/* pad multiplexing क्रम mcअगर devices */
अटल स्थिर अचिन्हित mcअगर_pins[] = अणु 193, 194, 195, 196, 197, 198, 199, 200,
	201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214,
	215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
	229, 230, 231, 232, 237 पूर्ण;
#घोषणा MCIF_MUXREG							\
	अणु								\
		.reg = PAD_SHARED_IP_EN_1,				\
		.mask = MCIF_MASK,					\
		.val = MCIF_MASK,					\
	पूर्ण, अणु								\
		.reg = PAD_FUNCTION_EN_7,				\
		.mask = FSMC_PNOR_AND_MCIF_REG6_MASK | MCIF_REG6_MASK,	\
		.val = FSMC_PNOR_AND_MCIF_REG6_MASK | MCIF_REG6_MASK,	\
	पूर्ण, अणु								\
		.reg = PAD_FUNCTION_EN_8,				\
		.mask = MCIF_REG7_MASK,					\
		.val = MCIF_REG7_MASK,					\
	पूर्ण

/* Pad multiplexing क्रम sdhci device */
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

/* Pad multiplexing क्रम cf device */
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

/* Pad multiplexing क्रम xd device */
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

/* pad multiplexing क्रम clcd device */
अटल स्थिर अचिन्हित clcd_pins[] = अणु 138, 139, 140, 141, 142, 143, 144, 145,
	146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173,
	174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187,
	188, 189, 190, 191 पूर्ण;
अटल काष्ठा spear_muxreg clcd_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = ARM_TRACE_MASK | MIPHY_DBG_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = CLCD_REG4_MASK | CLCD_AND_ARM_TRACE_REG4_MASK,
		.val = CLCD_REG4_MASK | CLCD_AND_ARM_TRACE_REG4_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_6,
		.mask = CLCD_AND_ARM_TRACE_REG5_MASK,
		.val = CLCD_AND_ARM_TRACE_REG5_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_7,
		.mask = CLCD_AND_ARM_TRACE_REG6_MASK,
		.val = CLCD_AND_ARM_TRACE_REG6_MASK,
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

/* Disable cld runसमय to save panel damage */
अटल काष्ठा spear_muxreg clcd_sleep_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = ARM_TRACE_MASK | MIPHY_DBG_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = CLCD_REG4_MASK | CLCD_AND_ARM_TRACE_REG4_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_6,
		.mask = CLCD_AND_ARM_TRACE_REG5_MASK,
		.val = 0x0,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_7,
		.mask = CLCD_AND_ARM_TRACE_REG6_MASK,
		.val = 0x0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux clcd_sleep_modemux[] = अणु
	अणु
		.muxregs = clcd_sleep_muxreg,
		.nmuxregs = ARRAY_SIZE(clcd_sleep_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup clcd_sleep_pingroup = अणु
	.name = "clcd_sleep_grp",
	.pins = clcd_pins,
	.npins = ARRAY_SIZE(clcd_pins),
	.modemuxs = clcd_sleep_modemux,
	.nmodemuxs = ARRAY_SIZE(clcd_sleep_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर clcd_grps[] = अणु "clcd_grp", "clcd_sleep_grp" पूर्ण;
अटल काष्ठा spear_function clcd_function = अणु
	.name = "clcd",
	.groups = clcd_grps,
	.ngroups = ARRAY_SIZE(clcd_grps),
पूर्ण;

/* pad multiplexing क्रम arm_trace device */
अटल स्थिर अचिन्हित arm_trace_pins[] = अणु 158, 159, 160, 161, 162, 163, 164,
	165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178,
	179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
	193, 194, 195, 196, 197, 198, 199, 200 पूर्ण;
अटल काष्ठा spear_muxreg arm_trace_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = ARM_TRACE_MASK,
		.val = ARM_TRACE_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = CLCD_AND_ARM_TRACE_REG4_MASK,
		.val = CLCD_AND_ARM_TRACE_REG4_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_6,
		.mask = CLCD_AND_ARM_TRACE_REG5_MASK,
		.val = CLCD_AND_ARM_TRACE_REG5_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_7,
		.mask = CLCD_AND_ARM_TRACE_REG6_MASK,
		.val = CLCD_AND_ARM_TRACE_REG6_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux arm_trace_modemux[] = अणु
	अणु
		.muxregs = arm_trace_muxreg,
		.nmuxregs = ARRAY_SIZE(arm_trace_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup arm_trace_pingroup = अणु
	.name = "arm_trace_grp",
	.pins = arm_trace_pins,
	.npins = ARRAY_SIZE(arm_trace_pins),
	.modemuxs = arm_trace_modemux,
	.nmodemuxs = ARRAY_SIZE(arm_trace_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर arm_trace_grps[] = अणु "arm_trace_grp" पूर्ण;
अटल काष्ठा spear_function arm_trace_function = अणु
	.name = "arm_trace",
	.groups = arm_trace_grps,
	.ngroups = ARRAY_SIZE(arm_trace_grps),
पूर्ण;

/* pad multiplexing क्रम miphy_dbg device */
अटल स्थिर अचिन्हित miphy_dbg_pins[] = अणु 96, 97, 98, 99, 100, 101, 102, 103,
	132, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
	148, 149, 150, 151, 152, 153, 154, 155, 156, 157 पूर्ण;
अटल काष्ठा spear_muxreg miphy_dbg_muxreg[] = अणु
	अणु
		.reg = PAD_SHARED_IP_EN_1,
		.mask = MIPHY_DBG_MASK,
		.val = MIPHY_DBG_MASK,
	पूर्ण, अणु
		.reg = PAD_FUNCTION_EN_5,
		.mask = DEVS_GRP_AND_MIPHY_DBG_REG4_MASK,
		.val = DEVS_GRP_AND_MIPHY_DBG_REG4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux miphy_dbg_modemux[] = अणु
	अणु
		.muxregs = miphy_dbg_muxreg,
		.nmuxregs = ARRAY_SIZE(miphy_dbg_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup miphy_dbg_pingroup = अणु
	.name = "miphy_dbg_grp",
	.pins = miphy_dbg_pins,
	.npins = ARRAY_SIZE(miphy_dbg_pins),
	.modemuxs = miphy_dbg_modemux,
	.nmodemuxs = ARRAY_SIZE(miphy_dbg_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर miphy_dbg_grps[] = अणु "miphy_dbg_grp" पूर्ण;
अटल काष्ठा spear_function miphy_dbg_function = अणु
	.name = "miphy_dbg",
	.groups = miphy_dbg_grps,
	.ngroups = ARRAY_SIZE(miphy_dbg_grps),
पूर्ण;

/* pad multiplexing क्रम pcie device */
अटल स्थिर अचिन्हित pcie_pins[] = अणु 250 पूर्ण;
अटल काष्ठा spear_muxreg pcie_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = SATA_PCIE_CFG_MASK,
		.val = PCIE_CFG_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pcie_modemux[] = अणु
	अणु
		.muxregs = pcie_muxreg,
		.nmuxregs = ARRAY_SIZE(pcie_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pcie_pingroup = अणु
	.name = "pcie_grp",
	.pins = pcie_pins,
	.npins = ARRAY_SIZE(pcie_pins),
	.modemuxs = pcie_modemux,
	.nmodemuxs = ARRAY_SIZE(pcie_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर pcie_grps[] = अणु "pcie_grp" पूर्ण;
अटल काष्ठा spear_function pcie_function = अणु
	.name = "pcie",
	.groups = pcie_grps,
	.ngroups = ARRAY_SIZE(pcie_grps),
पूर्ण;

/* pad multiplexing क्रम sata device */
अटल स्थिर अचिन्हित sata_pins[] = अणु 250 पूर्ण;
अटल काष्ठा spear_muxreg sata_muxreg[] = अणु
	अणु
		.reg = PCIE_SATA_CFG,
		.mask = SATA_PCIE_CFG_MASK,
		.val = SATA_CFG_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sata_modemux[] = अणु
	अणु
		.muxregs = sata_muxreg,
		.nmuxregs = ARRAY_SIZE(sata_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sata_pingroup = अणु
	.name = "sata_grp",
	.pins = sata_pins,
	.npins = ARRAY_SIZE(sata_pins),
	.modemuxs = sata_modemux,
	.nmodemuxs = ARRAY_SIZE(sata_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर sata_grps[] = अणु "sata_grp" पूर्ण;
अटल काष्ठा spear_function sata_function = अणु
	.name = "sata",
	.groups = sata_grps,
	.ngroups = ARRAY_SIZE(sata_grps),
पूर्ण;

/* pingroups */
अटल काष्ठा spear_pingroup *spear1340_pingroups[] = अणु
	&pads_as_gpio_pingroup,
	&fsmc_8bit_pingroup,
	&fsmc_16bit_pingroup,
	&fsmc_pnor_pingroup,
	&keyboard_row_col_pingroup,
	&keyboard_col5_pingroup,
	&spdअगर_in_pingroup,
	&spdअगर_out_pingroup,
	&gpt_0_1_pingroup,
	&pwm0_pingroup,
	&pwm1_pingroup,
	&pwm2_pingroup,
	&pwm3_pingroup,
	&vip_mux_pingroup,
	&vip_mux_cam0_pingroup,
	&vip_mux_cam1_pingroup,
	&vip_mux_cam2_pingroup,
	&vip_mux_cam3_pingroup,
	&cam0_pingroup,
	&cam1_pingroup,
	&cam2_pingroup,
	&cam3_pingroup,
	&smi_pingroup,
	&ssp0_pingroup,
	&ssp0_cs1_pingroup,
	&ssp0_cs2_pingroup,
	&ssp0_cs3_pingroup,
	&uart0_pingroup,
	&uart0_enh_pingroup,
	&uart1_pingroup,
	&i2s_in_pingroup,
	&i2s_out_pingroup,
	&gmii_pingroup,
	&rgmii_pingroup,
	&rmii_pingroup,
	&sgmii_pingroup,
	&i2c0_pingroup,
	&i2c1_pingroup,
	&cec0_pingroup,
	&cec1_pingroup,
	&sdhci_pingroup,
	&cf_pingroup,
	&xd_pingroup,
	&clcd_sleep_pingroup,
	&clcd_pingroup,
	&arm_trace_pingroup,
	&miphy_dbg_pingroup,
	&pcie_pingroup,
	&sata_pingroup,
पूर्ण;

/* functions */
अटल काष्ठा spear_function *spear1340_functions[] = अणु
	&pads_as_gpio_function,
	&fsmc_function,
	&keyboard_function,
	&spdअगर_in_function,
	&spdअगर_out_function,
	&gpt_0_1_function,
	&pwm_function,
	&vip_function,
	&cam0_function,
	&cam1_function,
	&cam2_function,
	&cam3_function,
	&smi_function,
	&ssp0_function,
	&uart0_function,
	&uart1_function,
	&i2s_function,
	&gmac_function,
	&i2c0_function,
	&i2c1_function,
	&cec0_function,
	&cec1_function,
	&sdhci_function,
	&cf_function,
	&xd_function,
	&clcd_function,
	&arm_trace_function,
	&miphy_dbg_function,
	&pcie_function,
	&sata_function,
पूर्ण;

अटल व्योम gpio_request_endisable(काष्ठा spear_pmx *pmx, पूर्णांक pin,
		bool enable)
अणु
	अचिन्हित पूर्णांक regoffset, regindex, bitoffset;
	अचिन्हित पूर्णांक val;

	/* pin++ as gpio configuration starts from 2nd bit of base रेजिस्टर */
	pin++;

	regindex = pin / 32;
	bitoffset = pin % 32;

	अगर (regindex <= 3)
		regoffset = PAD_FUNCTION_EN_1 + regindex * माप(पूर्णांक *);
	अन्यथा
		regoffset = PAD_FUNCTION_EN_5 + (regindex - 4) * माप(पूर्णांक *);

	val = pmx_पढ़ोl(pmx, regoffset);
	अगर (enable)
		val &= ~(0x1 << bitoffset);
	अन्यथा
		val |= 0x1 << bitoffset;

	pmx_ग_लिखोl(pmx, val, regoffset);
पूर्ण

अटल काष्ठा spear_pinctrl_machdata spear1340_machdata = अणु
	.pins = spear1340_pins,
	.npins = ARRAY_SIZE(spear1340_pins),
	.groups = spear1340_pingroups,
	.ngroups = ARRAY_SIZE(spear1340_pingroups),
	.functions = spear1340_functions,
	.nfunctions = ARRAY_SIZE(spear1340_functions),
	.gpio_request_endisable = gpio_request_endisable,
	.modes_supported = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spear1340_pinctrl_of_match[] = अणु
	अणु
		.compatible = "st,spear1340-pinmux",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक spear1340_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस spear_pinctrl_probe(pdev, &spear1340_machdata);
पूर्ण

अटल काष्ठा platक्रमm_driver spear1340_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = spear1340_pinctrl_of_match,
	पूर्ण,
	.probe = spear1340_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init spear1340_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spear1340_pinctrl_driver);
पूर्ण
arch_initcall(spear1340_pinctrl_init);
