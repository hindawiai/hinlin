<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr320 pinmux
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
#समावेश "pinctrl-spear3xx.h"

#घोषणा DRIVER_NAME "spear320-pinmux"

/* addresses */
#घोषणा PMX_CONFIG_REG			0x0C
#घोषणा MODE_CONFIG_REG			0x10
#घोषणा MODE_EXT_CONFIG_REG		0x18

/* modes */
#घोषणा AUTO_NET_SMII_MODE	(1 << 0)
#घोषणा AUTO_NET_MII_MODE	(1 << 1)
#घोषणा AUTO_EXP_MODE		(1 << 2)
#घोषणा SMALL_PRINTERS_MODE	(1 << 3)
#घोषणा EXTENDED_MODE		(1 << 4)

अटल काष्ठा spear_pmx_mode pmx_mode_स्वतः_net_smii = अणु
	.name = "Automation Networking SMII mode",
	.mode = AUTO_NET_SMII_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x00000007,
	.val = 0x0,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_स्वतः_net_mii = अणु
	.name = "Automation Networking MII mode",
	.mode = AUTO_NET_MII_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x00000007,
	.val = 0x1,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_स्वतः_exp = अणु
	.name = "Automation Expanded mode",
	.mode = AUTO_EXP_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x00000007,
	.val = 0x2,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_small_prपूर्णांकers = अणु
	.name = "Small Printers mode",
	.mode = SMALL_PRINTERS_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x00000007,
	.val = 0x3,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_extended = अणु
	.name = "extended mode",
	.mode = EXTENDED_MODE,
	.reg = MODE_EXT_CONFIG_REG,
	.mask = 0x00000001,
	.val = 0x1,
पूर्ण;

अटल काष्ठा spear_pmx_mode *spear320_pmx_modes[] = अणु
	&pmx_mode_स्वतः_net_smii,
	&pmx_mode_स्वतः_net_mii,
	&pmx_mode_स्वतः_exp,
	&pmx_mode_small_prपूर्णांकers,
	&pmx_mode_extended,
पूर्ण;

/* Extended mode रेजिस्टरs and their offsets */
#घोषणा EXT_CTRL_REG				0x0018
	#घोषणा MII_MDIO_MASK			(1 << 4)
	#घोषणा MII_MDIO_10_11_VAL		0
	#घोषणा MII_MDIO_81_VAL			(1 << 4)
	#घोषणा EMI_FSMC_DYNAMIC_MUX_MASK	(1 << 5)
	#घोषणा MAC_MODE_MII			0
	#घोषणा MAC_MODE_RMII			1
	#घोषणा MAC_MODE_SMII			2
	#घोषणा MAC_MODE_SS_SMII		3
	#घोषणा MAC_MODE_MASK			0x3
	#घोषणा MAC1_MODE_SHIFT			16
	#घोषणा MAC2_MODE_SHIFT			18

#घोषणा IP_SEL_PAD_0_9_REG			0x00A4
	#घोषणा PMX_PL_0_1_MASK			(0x3F << 0)
	#घोषणा PMX_UART2_PL_0_1_VAL		0x0
	#घोषणा PMX_I2C2_PL_0_1_VAL		(0x4 | (0x4 << 3))

	#घोषणा PMX_PL_2_3_MASK			(0x3F << 6)
	#घोषणा PMX_I2C2_PL_2_3_VAL		0x0
	#घोषणा PMX_UART6_PL_2_3_VAL		((0x1 << 6) | (0x1 << 9))
	#घोषणा PMX_UART1_ENH_PL_2_3_VAL	((0x4 << 6) | (0x4 << 9))

	#घोषणा PMX_PL_4_5_MASK			(0x3F << 12)
	#घोषणा PMX_UART5_PL_4_5_VAL		((0x1 << 12) | (0x1 << 15))
	#घोषणा PMX_UART1_ENH_PL_4_5_VAL	((0x4 << 12) | (0x4 << 15))
	#घोषणा PMX_PL_5_MASK			(0x7 << 15)
	#घोषणा PMX_TOUCH_Y_PL_5_VAL		0x0

	#घोषणा PMX_PL_6_7_MASK			(0x3F << 18)
	#घोषणा PMX_PL_6_MASK			(0x7 << 18)
	#घोषणा PMX_PL_7_MASK			(0x7 << 21)
	#घोषणा PMX_UART4_PL_6_7_VAL		((0x1 << 18) | (0x1 << 21))
	#घोषणा PMX_PWM_3_PL_6_VAL		(0x2 << 18)
	#घोषणा PMX_PWM_2_PL_7_VAL		(0x2 << 21)
	#घोषणा PMX_UART1_ENH_PL_6_7_VAL	((0x4 << 18) | (0x4 << 21))

	#घोषणा PMX_PL_8_9_MASK			(0x3F << 24)
	#घोषणा PMX_UART3_PL_8_9_VAL		((0x1 << 24) | (0x1 << 27))
	#घोषणा PMX_PWM_0_1_PL_8_9_VAL		((0x2 << 24) | (0x2 << 27))
	#घोषणा PMX_I2C1_PL_8_9_VAL		((0x4 << 24) | (0x4 << 27))

#घोषणा IP_SEL_PAD_10_19_REG			0x00A8
	#घोषणा PMX_PL_10_11_MASK		(0x3F << 0)
	#घोषणा PMX_SMII_PL_10_11_VAL		0
	#घोषणा PMX_RMII_PL_10_11_VAL		((0x4 << 0) | (0x4 << 3))

	#घोषणा PMX_PL_12_MASK			(0x7 << 6)
	#घोषणा PMX_PWM3_PL_12_VAL		0
	#घोषणा PMX_SDHCI_CD_PL_12_VAL		(0x4 << 6)

	#घोषणा PMX_PL_13_14_MASK		(0x3F << 9)
	#घोषणा PMX_PL_13_MASK			(0x7 << 9)
	#घोषणा PMX_PL_14_MASK			(0x7 << 12)
	#घोषणा PMX_SSP2_PL_13_14_15_16_VAL	0
	#घोषणा PMX_UART4_PL_13_14_VAL		((0x1 << 9) | (0x1 << 12))
	#घोषणा PMX_RMII_PL_13_14_VAL		((0x4 << 9) | (0x4 << 12))
	#घोषणा PMX_PWM2_PL_13_VAL		(0x2 << 9)
	#घोषणा PMX_PWM1_PL_14_VAL		(0x2 << 12)

	#घोषणा PMX_PL_15_MASK			(0x7 << 15)
	#घोषणा PMX_PWM0_PL_15_VAL		(0x2 << 15)
	#घोषणा PMX_PL_15_16_MASK		(0x3F << 15)
	#घोषणा PMX_UART3_PL_15_16_VAL		((0x1 << 15) | (0x1 << 18))
	#घोषणा PMX_RMII_PL_15_16_VAL		((0x4 << 15) | (0x4 << 18))

	#घोषणा PMX_PL_17_18_MASK		(0x3F << 21)
	#घोषणा PMX_SSP1_PL_17_18_19_20_VAL	0
	#घोषणा PMX_RMII_PL_17_18_VAL		((0x4 << 21) | (0x4 << 24))

	#घोषणा PMX_PL_19_MASK			(0x7 << 27)
	#घोषणा PMX_I2C2_PL_19_VAL		(0x1 << 27)
	#घोषणा PMX_RMII_PL_19_VAL		(0x4 << 27)

#घोषणा IP_SEL_PAD_20_29_REG			0x00AC
	#घोषणा PMX_PL_20_MASK			(0x7 << 0)
	#घोषणा PMX_I2C2_PL_20_VAL		(0x1 << 0)
	#घोषणा PMX_RMII_PL_20_VAL		(0x4 << 0)

	#घोषणा PMX_PL_21_TO_27_MASK		(0x1FFFFF << 3)
	#घोषणा PMX_SMII_PL_21_TO_27_VAL	0
	#घोषणा PMX_RMII_PL_21_TO_27_VAL	((0x4 << 3) | (0x4 << 6) | (0x4 << 9) | (0x4 << 12) | (0x4 << 15) | (0x4 << 18) | (0x4 << 21))

	#घोषणा PMX_PL_28_29_MASK		(0x3F << 24)
	#घोषणा PMX_PL_28_MASK			(0x7 << 24)
	#घोषणा PMX_PL_29_MASK			(0x7 << 27)
	#घोषणा PMX_UART1_PL_28_29_VAL		0
	#घोषणा PMX_PWM_3_PL_28_VAL		(0x4 << 24)
	#घोषणा PMX_PWM_2_PL_29_VAL		(0x4 << 27)

#घोषणा IP_SEL_PAD_30_39_REG			0x00B0
	#घोषणा PMX_PL_30_31_MASK		(0x3F << 0)
	#घोषणा PMX_CAN1_PL_30_31_VAL		(0)
	#घोषणा PMX_PL_30_MASK			(0x7 << 0)
	#घोषणा PMX_PL_31_MASK			(0x7 << 3)
	#घोषणा PMX_PWM1_EXT_PL_30_VAL		(0x4 << 0)
	#घोषणा PMX_PWM0_EXT_PL_31_VAL		(0x4 << 3)
	#घोषणा PMX_UART1_ENH_PL_31_VAL		(0x3 << 3)

	#घोषणा PMX_PL_32_33_MASK		(0x3F << 6)
	#घोषणा PMX_CAN0_PL_32_33_VAL		0
	#घोषणा PMX_UART1_ENH_PL_32_33_VAL	((0x3 << 6) | (0x3 << 9))
	#घोषणा PMX_SSP2_PL_32_33_VAL		((0x4 << 6) | (0x4 << 9))

	#घोषणा PMX_PL_34_MASK			(0x7 << 12)
	#घोषणा PMX_PWM2_PL_34_VAL		0
	#घोषणा PMX_UART1_ENH_PL_34_VAL		(0x2 << 12)
	#घोषणा PMX_SSP2_PL_34_VAL		(0x4 << 12)

	#घोषणा PMX_PL_35_MASK			(0x7 << 15)
	#घोषणा PMX_I2S_REF_CLK_PL_35_VAL	0
	#घोषणा PMX_UART1_ENH_PL_35_VAL		(0x2 << 15)
	#घोषणा PMX_SSP2_PL_35_VAL		(0x4 << 15)

	#घोषणा PMX_PL_36_MASK			(0x7 << 18)
	#घोषणा PMX_TOUCH_X_PL_36_VAL		0
	#घोषणा PMX_UART1_ENH_PL_36_VAL		(0x2 << 18)
	#घोषणा PMX_SSP1_PL_36_VAL		(0x4 << 18)

	#घोषणा PMX_PL_37_38_MASK		(0x3F << 21)
	#घोषणा PMX_PWM0_1_PL_37_38_VAL		0
	#घोषणा PMX_UART5_PL_37_38_VAL		((0x2 << 21) | (0x2 << 24))
	#घोषणा PMX_SSP1_PL_37_38_VAL		((0x4 << 21) | (0x4 << 24))

	#घोषणा PMX_PL_39_MASK			(0x7 << 27)
	#घोषणा PMX_I2S_PL_39_VAL		0
	#घोषणा PMX_UART4_PL_39_VAL		(0x2 << 27)
	#घोषणा PMX_SSP1_PL_39_VAL		(0x4 << 27)

#घोषणा IP_SEL_PAD_40_49_REG			0x00B4
	#घोषणा PMX_PL_40_MASK			(0x7 << 0)
	#घोषणा PMX_I2S_PL_40_VAL		0
	#घोषणा PMX_UART4_PL_40_VAL		(0x2 << 0)
	#घोषणा PMX_PWM3_PL_40_VAL		(0x4 << 0)

	#घोषणा PMX_PL_41_42_MASK		(0x3F << 3)
	#घोषणा PMX_PL_41_MASK			(0x7 << 3)
	#घोषणा PMX_PL_42_MASK			(0x7 << 6)
	#घोषणा PMX_I2S_PL_41_42_VAL		0
	#घोषणा PMX_UART3_PL_41_42_VAL		((0x2 << 3) | (0x2 << 6))
	#घोषणा PMX_PWM2_PL_41_VAL		(0x4 << 3)
	#घोषणा PMX_PWM1_PL_42_VAL		(0x4 << 6)

	#घोषणा PMX_PL_43_MASK			(0x7 << 9)
	#घोषणा PMX_SDHCI_PL_43_VAL		0
	#घोषणा PMX_UART1_ENH_PL_43_VAL		(0x2 << 9)
	#घोषणा PMX_PWM0_PL_43_VAL		(0x4 << 9)

	#घोषणा PMX_PL_44_45_MASK		(0x3F << 12)
	#घोषणा PMX_SDHCI_PL_44_45_VAL	0
	#घोषणा PMX_UART1_ENH_PL_44_45_VAL	((0x2 << 12) | (0x2 << 15))
	#घोषणा PMX_SSP2_PL_44_45_VAL		((0x4 << 12) | (0x4 << 15))

	#घोषणा PMX_PL_46_47_MASK		(0x3F << 18)
	#घोषणा PMX_SDHCI_PL_46_47_VAL	0
	#घोषणा PMX_FSMC_EMI_PL_46_47_VAL	((0x2 << 18) | (0x2 << 21))
	#घोषणा PMX_SSP2_PL_46_47_VAL		((0x4 << 18) | (0x4 << 21))

	#घोषणा PMX_PL_48_49_MASK		(0x3F << 24)
	#घोषणा PMX_SDHCI_PL_48_49_VAL	0
	#घोषणा PMX_FSMC_EMI_PL_48_49_VAL	((0x2 << 24) | (0x2 << 27))
	#घोषणा PMX_SSP1_PL_48_49_VAL		((0x4 << 24) | (0x4 << 27))

#घोषणा IP_SEL_PAD_50_59_REG			0x00B8
	#घोषणा PMX_PL_50_51_MASK		(0x3F << 0)
	#घोषणा PMX_EMI_PL_50_51_VAL		((0x2 << 0) | (0x2 << 3))
	#घोषणा PMX_SSP1_PL_50_51_VAL		((0x4 << 0) | (0x4 << 3))
	#घोषणा PMX_PL_50_MASK			(0x7 << 0)
	#घोषणा PMX_PL_51_MASK			(0x7 << 3)
	#घोषणा PMX_SDHCI_PL_50_VAL		0
	#घोषणा PMX_SDHCI_CD_PL_51_VAL		0

	#घोषणा PMX_PL_52_53_MASK		(0x3F << 6)
	#घोषणा PMX_FSMC_PL_52_53_VAL		0
	#घोषणा PMX_EMI_PL_52_53_VAL		((0x2 << 6) | (0x2 << 9))
	#घोषणा PMX_UART3_PL_52_53_VAL		((0x4 << 6) | (0x4 << 9))

	#घोषणा PMX_PL_54_55_56_MASK		(0x1FF << 12)
	#घोषणा PMX_FSMC_EMI_PL_54_55_56_VAL	((0x2 << 12) | (0x2 << 15) | (0x2 << 18))

	#घोषणा PMX_PL_57_MASK			(0x7 << 21)
	#घोषणा PMX_FSMC_PL_57_VAL		0
	#घोषणा PMX_PWM3_PL_57_VAL		(0x4 << 21)

	#घोषणा PMX_PL_58_59_MASK		(0x3F << 24)
	#घोषणा PMX_PL_58_MASK			(0x7 << 24)
	#घोषणा PMX_PL_59_MASK			(0x7 << 27)
	#घोषणा PMX_FSMC_EMI_PL_58_59_VAL	((0x2 << 24) | (0x2 << 27))
	#घोषणा PMX_PWM2_PL_58_VAL		(0x4 << 24)
	#घोषणा PMX_PWM1_PL_59_VAL		(0x4 << 27)

#घोषणा IP_SEL_PAD_60_69_REG			0x00BC
	#घोषणा PMX_PL_60_MASK			(0x7 << 0)
	#घोषणा PMX_FSMC_PL_60_VAL		0
	#घोषणा PMX_PWM0_PL_60_VAL		(0x4 << 0)

	#घोषणा PMX_PL_61_TO_64_MASK		(0xFFF << 3)
	#घोषणा PMX_FSMC_PL_61_TO_64_VAL	((0x2 << 3) | (0x2 << 6) | (0x2 << 9) | (0x2 << 12))
	#घोषणा PMX_SSP2_PL_61_TO_64_VAL	((0x4 << 3) | (0x4 << 6) | (0x4 << 9) | (0x4 << 12))

	#घोषणा PMX_PL_65_TO_68_MASK		(0xFFF << 15)
	#घोषणा PMX_FSMC_PL_65_TO_68_VAL	((0x2 << 15) | (0x2 << 18) | (0x2 << 21) | (0x2 << 24))
	#घोषणा PMX_SSP1_PL_65_TO_68_VAL	((0x4 << 15) | (0x4 << 18) | (0x4 << 21) | (0x4 << 24))

	#घोषणा PMX_PL_69_MASK			(0x7 << 27)
	#घोषणा PMX_CLCD_PL_69_VAL		(0)
	#घोषणा PMX_EMI_PL_69_VAL		(0x2 << 27)
	#घोषणा PMX_SPP_PL_69_VAL		(0x3 << 27)
	#घोषणा PMX_UART5_PL_69_VAL		(0x4 << 27)

#घोषणा IP_SEL_PAD_70_79_REG			0x00C0
	#घोषणा PMX_PL_70_MASK			(0x7 << 0)
	#घोषणा PMX_CLCD_PL_70_VAL		(0)
	#घोषणा PMX_FSMC_EMI_PL_70_VAL		(0x2 << 0)
	#घोषणा PMX_SPP_PL_70_VAL		(0x3 << 0)
	#घोषणा PMX_UART5_PL_70_VAL		(0x4 << 0)

	#घोषणा PMX_PL_71_72_MASK		(0x3F << 3)
	#घोषणा PMX_CLCD_PL_71_72_VAL		(0)
	#घोषणा PMX_FSMC_EMI_PL_71_72_VAL	((0x2 << 3) | (0x2 << 6))
	#घोषणा PMX_SPP_PL_71_72_VAL		((0x3 << 3) | (0x3 << 6))
	#घोषणा PMX_UART4_PL_71_72_VAL		((0x4 << 3) | (0x4 << 6))

	#घोषणा PMX_PL_73_MASK			(0x7 << 9)
	#घोषणा PMX_CLCD_PL_73_VAL		(0)
	#घोषणा PMX_FSMC_EMI_PL_73_VAL		(0x2 << 9)
	#घोषणा PMX_SPP_PL_73_VAL		(0x3 << 9)
	#घोषणा PMX_UART3_PL_73_VAL		(0x4 << 9)

	#घोषणा PMX_PL_74_MASK			(0x7 << 12)
	#घोषणा PMX_CLCD_PL_74_VAL		(0)
	#घोषणा PMX_EMI_PL_74_VAL		(0x2 << 12)
	#घोषणा PMX_SPP_PL_74_VAL		(0x3 << 12)
	#घोषणा PMX_UART3_PL_74_VAL		(0x4 << 12)

	#घोषणा PMX_PL_75_76_MASK		(0x3F << 15)
	#घोषणा PMX_CLCD_PL_75_76_VAL		(0)
	#घोषणा PMX_EMI_PL_75_76_VAL		((0x2 << 15) | (0x2 << 18))
	#घोषणा PMX_SPP_PL_75_76_VAL		((0x3 << 15) | (0x3 << 18))
	#घोषणा PMX_I2C2_PL_75_76_VAL		((0x4 << 15) | (0x4 << 18))

	#घोषणा PMX_PL_77_78_79_MASK		(0x1FF << 21)
	#घोषणा PMX_CLCD_PL_77_78_79_VAL	(0)
	#घोषणा PMX_EMI_PL_77_78_79_VAL		((0x2 << 21) | (0x2 << 24) | (0x2 << 27))
	#घोषणा PMX_SPP_PL_77_78_79_VAL		((0x3 << 21) | (0x3 << 24) | (0x3 << 27))
	#घोषणा PMX_RS485_PL_77_78_79_VAL	((0x4 << 21) | (0x4 << 24) | (0x4 << 27))

#घोषणा IP_SEL_PAD_80_89_REG			0x00C4
	#घोषणा PMX_PL_80_TO_85_MASK		(0x3FFFF << 0)
	#घोषणा PMX_CLCD_PL_80_TO_85_VAL	0
	#घोषणा PMX_MII2_PL_80_TO_85_VAL	((0x1 << 0) | (0x1 << 3) | (0x1 << 6) | (0x1 << 9) | (0x1 << 12) | (0x1 << 15))
	#घोषणा PMX_EMI_PL_80_TO_85_VAL		((0x2 << 0) | (0x2 << 3) | (0x2 << 6) | (0x2 << 9) | (0x2 << 12) | (0x2 << 15))
	#घोषणा PMX_SPP_PL_80_TO_85_VAL		((0x3 << 0) | (0x3 << 3) | (0x3 << 6) | (0x3 << 9) | (0x3 << 12) | (0x3 << 15))
	#घोषणा PMX_UART1_ENH_PL_80_TO_85_VAL	((0x4 << 0) | (0x4 << 3) | (0x4 << 6) | (0x4 << 9) | (0x4 << 12) | (0x4 << 15))

	#घोषणा PMX_PL_86_87_MASK		(0x3F << 18)
	#घोषणा PMX_PL_86_MASK			(0x7 << 18)
	#घोषणा PMX_PL_87_MASK			(0x7 << 21)
	#घोषणा PMX_CLCD_PL_86_87_VAL		0
	#घोषणा PMX_MII2_PL_86_87_VAL		((0x1 << 18) | (0x1 << 21))
	#घोषणा PMX_EMI_PL_86_87_VAL		((0x2 << 18) | (0x2 << 21))
	#घोषणा PMX_PWM3_PL_86_VAL		(0x4 << 18)
	#घोषणा PMX_PWM2_PL_87_VAL		(0x4 << 21)

	#घोषणा PMX_PL_88_89_MASK		(0x3F << 24)
	#घोषणा PMX_CLCD_PL_88_89_VAL		0
	#घोषणा PMX_MII2_PL_88_89_VAL		((0x1 << 24) | (0x1 << 27))
	#घोषणा PMX_EMI_PL_88_89_VAL		((0x2 << 24) | (0x2 << 27))
	#घोषणा PMX_UART6_PL_88_89_VAL		((0x3 << 24) | (0x3 << 27))
	#घोषणा PMX_PWM0_1_PL_88_89_VAL		((0x4 << 24) | (0x4 << 27))

#घोषणा IP_SEL_PAD_90_99_REG			0x00C8
	#घोषणा PMX_PL_90_91_MASK		(0x3F << 0)
	#घोषणा PMX_CLCD_PL_90_91_VAL		0
	#घोषणा PMX_MII2_PL_90_91_VAL		((0x1 << 0) | (0x1 << 3))
	#घोषणा PMX_EMI1_PL_90_91_VAL		((0x2 << 0) | (0x2 << 3))
	#घोषणा PMX_UART5_PL_90_91_VAL		((0x3 << 0) | (0x3 << 3))
	#घोषणा PMX_SSP2_PL_90_91_VAL		((0x4 << 0) | (0x4 << 3))

	#घोषणा PMX_PL_92_93_MASK		(0x3F << 6)
	#घोषणा PMX_CLCD_PL_92_93_VAL		0
	#घोषणा PMX_MII2_PL_92_93_VAL		((0x1 << 6) | (0x1 << 9))
	#घोषणा PMX_EMI1_PL_92_93_VAL		((0x2 << 6) | (0x2 << 9))
	#घोषणा PMX_UART4_PL_92_93_VAL		((0x3 << 6) | (0x3 << 9))
	#घोषणा PMX_SSP2_PL_92_93_VAL		((0x4 << 6) | (0x4 << 9))

	#घोषणा PMX_PL_94_95_MASK		(0x3F << 12)
	#घोषणा PMX_CLCD_PL_94_95_VAL		0
	#घोषणा PMX_MII2_PL_94_95_VAL		((0x1 << 12) | (0x1 << 15))
	#घोषणा PMX_EMI1_PL_94_95_VAL		((0x2 << 12) | (0x2 << 15))
	#घोषणा PMX_UART3_PL_94_95_VAL		((0x3 << 12) | (0x3 << 15))
	#घोषणा PMX_SSP1_PL_94_95_VAL		((0x4 << 12) | (0x4 << 15))

	#घोषणा PMX_PL_96_97_MASK		(0x3F << 18)
	#घोषणा PMX_CLCD_PL_96_97_VAL		0
	#घोषणा PMX_MII2_PL_96_97_VAL		((0x1 << 18) | (0x1 << 21))
	#घोषणा PMX_EMI1_PL_96_97_VAL		((0x2 << 18) | (0x2 << 21))
	#घोषणा PMX_I2C2_PL_96_97_VAL		((0x3 << 18) | (0x3 << 21))
	#घोषणा PMX_SSP1_PL_96_97_VAL		((0x4 << 18) | (0x4 << 21))

	#घोषणा PMX_PL_98_MASK			(0x7 << 24)
	#घोषणा PMX_CLCD_PL_98_VAL		0
	#घोषणा PMX_I2C1_PL_98_VAL		(0x2 << 24)
	#घोषणा PMX_UART3_PL_98_VAL		(0x4 << 24)

	#घोषणा PMX_PL_99_MASK			(0x7 << 27)
	#घोषणा PMX_SDHCI_PL_99_VAL		0
	#घोषणा PMX_I2C1_PL_99_VAL		(0x2 << 27)
	#घोषणा PMX_UART3_PL_99_VAL		(0x4 << 27)

#घोषणा IP_SEL_MIX_PAD_REG			0x00CC
	#घोषणा PMX_PL_100_101_MASK		(0x3F << 0)
	#घोषणा PMX_SDHCI_PL_100_101_VAL	0
	#घोषणा PMX_UART4_PL_100_101_VAL	((0x4 << 0) | (0x4 << 3))

	#घोषणा PMX_SSP1_PORT_SEL_MASK		(0x7 << 8)
	#घोषणा PMX_SSP1_PORT_94_TO_97_VAL	0
	#घोषणा PMX_SSP1_PORT_65_TO_68_VAL	(0x1 << 8)
	#घोषणा PMX_SSP1_PORT_48_TO_51_VAL	(0x2 << 8)
	#घोषणा PMX_SSP1_PORT_36_TO_39_VAL	(0x3 << 8)
	#घोषणा PMX_SSP1_PORT_17_TO_20_VAL	(0x4 << 8)

	#घोषणा PMX_SSP2_PORT_SEL_MASK		(0x7 << 11)
	#घोषणा PMX_SSP2_PORT_90_TO_93_VAL	0
	#घोषणा PMX_SSP2_PORT_61_TO_64_VAL	(0x1 << 11)
	#घोषणा PMX_SSP2_PORT_44_TO_47_VAL	(0x2 << 11)
	#घोषणा PMX_SSP2_PORT_32_TO_35_VAL	(0x3 << 11)
	#घोषणा PMX_SSP2_PORT_13_TO_16_VAL	(0x4 << 11)

	#घोषणा PMX_UART1_ENH_PORT_SEL_MASK		(0x3 << 14)
	#घोषणा PMX_UART1_ENH_PORT_81_TO_85_VAL		0
	#घोषणा PMX_UART1_ENH_PORT_44_45_34_36_VAL	(0x1 << 14)
	#घोषणा PMX_UART1_ENH_PORT_32_TO_34_36_VAL	(0x2 << 14)
	#घोषणा PMX_UART1_ENH_PORT_3_TO_5_7_VAL		(0x3 << 14)

	#घोषणा PMX_UART3_PORT_SEL_MASK		(0x7 << 16)
	#घोषणा PMX_UART3_PORT_94_VAL		0
	#घोषणा PMX_UART3_PORT_73_VAL		(0x1 << 16)
	#घोषणा PMX_UART3_PORT_52_VAL		(0x2 << 16)
	#घोषणा PMX_UART3_PORT_41_VAL		(0x3 << 16)
	#घोषणा PMX_UART3_PORT_15_VAL		(0x4 << 16)
	#घोषणा PMX_UART3_PORT_8_VAL		(0x5 << 16)
	#घोषणा PMX_UART3_PORT_99_VAL		(0x6 << 16)

	#घोषणा PMX_UART4_PORT_SEL_MASK		(0x7 << 19)
	#घोषणा PMX_UART4_PORT_92_VAL		0
	#घोषणा PMX_UART4_PORT_71_VAL		(0x1 << 19)
	#घोषणा PMX_UART4_PORT_39_VAL		(0x2 << 19)
	#घोषणा PMX_UART4_PORT_13_VAL		(0x3 << 19)
	#घोषणा PMX_UART4_PORT_6_VAL		(0x4 << 19)
	#घोषणा PMX_UART4_PORT_101_VAL		(0x5 << 19)

	#घोषणा PMX_UART5_PORT_SEL_MASK		(0x3 << 22)
	#घोषणा PMX_UART5_PORT_90_VAL		0
	#घोषणा PMX_UART5_PORT_69_VAL		(0x1 << 22)
	#घोषणा PMX_UART5_PORT_37_VAL		(0x2 << 22)
	#घोषणा PMX_UART5_PORT_4_VAL		(0x3 << 22)

	#घोषणा PMX_UART6_PORT_SEL_MASK		(0x1 << 24)
	#घोषणा PMX_UART6_PORT_88_VAL		0
	#घोषणा PMX_UART6_PORT_2_VAL		(0x1 << 24)

	#घोषणा PMX_I2C1_PORT_SEL_MASK		(0x1 << 25)
	#घोषणा PMX_I2C1_PORT_8_9_VAL		0
	#घोषणा PMX_I2C1_PORT_98_99_VAL		(0x1 << 25)

	#घोषणा PMX_I2C2_PORT_SEL_MASK		(0x3 << 26)
	#घोषणा PMX_I2C2_PORT_96_97_VAL		0
	#घोषणा PMX_I2C2_PORT_75_76_VAL		(0x1 << 26)
	#घोषणा PMX_I2C2_PORT_19_20_VAL		(0x2 << 26)
	#घोषणा PMX_I2C2_PORT_2_3_VAL		(0x3 << 26)
	#घोषणा PMX_I2C2_PORT_0_1_VAL		(0x4 << 26)

	#घोषणा PMX_SDHCI_CD_PORT_SEL_MASK	(0x1 << 29)
	#घोषणा PMX_SDHCI_CD_PORT_12_VAL	0
	#घोषणा PMX_SDHCI_CD_PORT_51_VAL	(0x1 << 29)

/* Pad multiplexing क्रम CLCD device */
अटल स्थिर अचिन्हित clcd_pins[] = अणु 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
	79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
	97 पूर्ण;
अटल काष्ठा spear_muxreg clcd_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_69_MASK,
		.val = PMX_CLCD_PL_69_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_70_MASK | PMX_PL_71_72_MASK | PMX_PL_73_MASK |
			PMX_PL_74_MASK | PMX_PL_75_76_MASK |
			PMX_PL_77_78_79_MASK,
		.val = PMX_CLCD_PL_70_VAL | PMX_CLCD_PL_71_72_VAL |
			PMX_CLCD_PL_73_VAL | PMX_CLCD_PL_74_VAL |
			PMX_CLCD_PL_75_76_VAL | PMX_CLCD_PL_77_78_79_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_80_TO_85_MASK | PMX_PL_86_87_MASK |
			PMX_PL_88_89_MASK,
		.val = PMX_CLCD_PL_80_TO_85_VAL | PMX_CLCD_PL_86_87_VAL |
			PMX_CLCD_PL_88_89_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_90_91_MASK | PMX_PL_92_93_MASK |
			PMX_PL_94_95_MASK | PMX_PL_96_97_MASK | PMX_PL_98_MASK,
		.val = PMX_CLCD_PL_90_91_VAL | PMX_CLCD_PL_92_93_VAL |
			PMX_CLCD_PL_94_95_VAL | PMX_CLCD_PL_96_97_VAL |
			PMX_CLCD_PL_98_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux clcd_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
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

अटल स्थिर अक्षर *स्थिर clcd_grps[] = अणु "clcd_grp" पूर्ण;
अटल काष्ठा spear_function clcd_function = अणु
	.name = "clcd",
	.groups = clcd_grps,
	.ngroups = ARRAY_SIZE(clcd_grps),
पूर्ण;

/* Pad multiplexing क्रम EMI (Parallel NOR flash) device */
अटल स्थिर अचिन्हित emi_pins[] = अणु 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92,
	93, 94, 95, 96, 97 पूर्ण;
अटल काष्ठा spear_muxreg emi_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg emi_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_46_47_MASK | PMX_PL_48_49_MASK,
		.val = PMX_FSMC_EMI_PL_46_47_VAL | PMX_FSMC_EMI_PL_48_49_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_50_51_MASK | PMX_PL_52_53_MASK |
			PMX_PL_54_55_56_MASK | PMX_PL_58_59_MASK,
		.val = PMX_EMI_PL_50_51_VAL | PMX_EMI_PL_52_53_VAL |
			PMX_FSMC_EMI_PL_54_55_56_VAL |
			PMX_FSMC_EMI_PL_58_59_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_69_MASK,
		.val = PMX_EMI_PL_69_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_70_MASK | PMX_PL_71_72_MASK | PMX_PL_73_MASK |
			PMX_PL_74_MASK | PMX_PL_75_76_MASK |
			PMX_PL_77_78_79_MASK,
		.val = PMX_FSMC_EMI_PL_70_VAL | PMX_FSMC_EMI_PL_71_72_VAL |
			PMX_FSMC_EMI_PL_73_VAL | PMX_EMI_PL_74_VAL |
			PMX_EMI_PL_75_76_VAL | PMX_EMI_PL_77_78_79_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_80_TO_85_MASK | PMX_PL_86_87_MASK |
			PMX_PL_88_89_MASK,
		.val = PMX_EMI_PL_80_TO_85_VAL | PMX_EMI_PL_86_87_VAL |
			PMX_EMI_PL_88_89_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_90_91_MASK | PMX_PL_92_93_MASK |
			PMX_PL_94_95_MASK | PMX_PL_96_97_MASK,
		.val = PMX_EMI1_PL_90_91_VAL | PMX_EMI1_PL_92_93_VAL |
			PMX_EMI1_PL_94_95_VAL | PMX_EMI1_PL_96_97_VAL,
	पूर्ण, अणु
		.reg = EXT_CTRL_REG,
		.mask = EMI_FSMC_DYNAMIC_MUX_MASK,
		.val = EMI_FSMC_DYNAMIC_MUX_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux emi_modemux[] = अणु
	अणु
		.modes = AUTO_EXP_MODE | EXTENDED_MODE,
		.muxregs = emi_muxreg,
		.nmuxregs = ARRAY_SIZE(emi_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = emi_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(emi_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup emi_pingroup = अणु
	.name = "emi_grp",
	.pins = emi_pins,
	.npins = ARRAY_SIZE(emi_pins),
	.modemuxs = emi_modemux,
	.nmodemuxs = ARRAY_SIZE(emi_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर emi_grps[] = अणु "emi_grp" पूर्ण;
अटल काष्ठा spear_function emi_function = अणु
	.name = "emi",
	.groups = emi_grps,
	.ngroups = ARRAY_SIZE(emi_grps),
पूर्ण;

/* Pad multiplexing क्रम FSMC (न_अंकD flash) device */
अटल स्थिर अचिन्हित fsmc_8bit_pins[] = अणु 52, 53, 54, 55, 56, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 68 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_8bit_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_52_53_MASK | PMX_PL_54_55_56_MASK |
			PMX_PL_57_MASK | PMX_PL_58_59_MASK,
		.val = PMX_FSMC_PL_52_53_VAL | PMX_FSMC_EMI_PL_54_55_56_VAL |
			PMX_FSMC_PL_57_VAL | PMX_FSMC_EMI_PL_58_59_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_60_MASK | PMX_PL_61_TO_64_MASK |
			PMX_PL_65_TO_68_MASK,
		.val = PMX_FSMC_PL_60_VAL | PMX_FSMC_PL_61_TO_64_VAL |
			PMX_FSMC_PL_65_TO_68_VAL,
	पूर्ण, अणु
		.reg = EXT_CTRL_REG,
		.mask = EMI_FSMC_DYNAMIC_MUX_MASK,
		.val = EMI_FSMC_DYNAMIC_MUX_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux fsmc_8bit_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
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

अटल स्थिर अचिन्हित fsmc_16bit_pins[] = अणु 46, 47, 48, 49, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 71, 72, 73 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_16bit_स्वतःexp_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg fsmc_16bit_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_46_47_MASK | PMX_PL_48_49_MASK,
		.val = PMX_FSMC_EMI_PL_46_47_VAL | PMX_FSMC_EMI_PL_48_49_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_70_MASK | PMX_PL_71_72_MASK | PMX_PL_73_MASK,
		.val = PMX_FSMC_EMI_PL_70_VAL | PMX_FSMC_EMI_PL_71_72_VAL |
			PMX_FSMC_EMI_PL_73_VAL,
	पूर्ण
पूर्ण;

अटल काष्ठा spear_modemux fsmc_16bit_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = fsmc_8bit_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_8bit_muxreg),
	पूर्ण, अणु
		.modes = AUTO_EXP_MODE | EXTENDED_MODE,
		.muxregs = fsmc_16bit_स्वतःexp_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_16bit_स्वतःexp_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
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

अटल स्थिर अक्षर *स्थिर fsmc_grps[] = अणु "fsmc_8bit_grp", "fsmc_16bit_grp" पूर्ण;
अटल काष्ठा spear_function fsmc_function = अणु
	.name = "fsmc",
	.groups = fsmc_grps,
	.ngroups = ARRAY_SIZE(fsmc_grps),
पूर्ण;

/* Pad multiplexing क्रम SPP device */
अटल स्थिर अचिन्हित spp_pins[] = अणु 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83, 84, 85 पूर्ण;
अटल काष्ठा spear_muxreg spp_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_69_MASK,
		.val = PMX_SPP_PL_69_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_70_MASK | PMX_PL_71_72_MASK | PMX_PL_73_MASK |
			PMX_PL_74_MASK | PMX_PL_75_76_MASK |
			PMX_PL_77_78_79_MASK,
		.val = PMX_SPP_PL_70_VAL | PMX_SPP_PL_71_72_VAL |
			PMX_SPP_PL_73_VAL | PMX_SPP_PL_74_VAL |
			PMX_SPP_PL_75_76_VAL | PMX_SPP_PL_77_78_79_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_80_TO_85_MASK,
		.val = PMX_SPP_PL_80_TO_85_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux spp_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = spp_muxreg,
		.nmuxregs = ARRAY_SIZE(spp_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup spp_pingroup = अणु
	.name = "spp_grp",
	.pins = spp_pins,
	.npins = ARRAY_SIZE(spp_pins),
	.modemuxs = spp_modemux,
	.nmodemuxs = ARRAY_SIZE(spp_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर spp_grps[] = अणु "spp_grp" पूर्ण;
अटल काष्ठा spear_function spp_function = अणु
	.name = "spp",
	.groups = spp_grps,
	.ngroups = ARRAY_SIZE(spp_grps),
पूर्ण;

/* Pad multiplexing क्रम SDHCI device */
अटल स्थिर अचिन्हित sdhci_led_pins[] = अणु 34 पूर्ण;
अटल काष्ठा spear_muxreg sdhci_led_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg sdhci_led_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_34_MASK,
		.val = PMX_PWM2_PL_34_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sdhci_led_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxregs = sdhci_led_muxreg,
		.nmuxregs = ARRAY_SIZE(sdhci_led_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = sdhci_led_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(sdhci_led_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sdhci_led_pingroup = अणु
	.name = "sdhci_led_grp",
	.pins = sdhci_led_pins,
	.npins = ARRAY_SIZE(sdhci_led_pins),
	.modemuxs = sdhci_led_modemux,
	.nmodemuxs = ARRAY_SIZE(sdhci_led_modemux),
पूर्ण;

अटल स्थिर अचिन्हित sdhci_cd_12_pins[] = अणु 12, 43, 44, 45, 46, 47, 48, 49,
	50पूर्ण;
अटल स्थिर अचिन्हित sdhci_cd_51_pins[] = अणु 43, 44, 45, 46, 47, 48, 49, 50, 51
पूर्ण;
अटल काष्ठा spear_muxreg sdhci_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg sdhci_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_43_MASK | PMX_PL_44_45_MASK | PMX_PL_46_47_MASK |
			PMX_PL_48_49_MASK,
		.val = PMX_SDHCI_PL_43_VAL | PMX_SDHCI_PL_44_45_VAL |
			PMX_SDHCI_PL_46_47_VAL | PMX_SDHCI_PL_48_49_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_50_MASK,
		.val = PMX_SDHCI_PL_50_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_99_MASK,
		.val = PMX_SDHCI_PL_99_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_PL_100_101_MASK,
		.val = PMX_SDHCI_PL_100_101_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg sdhci_cd_12_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_12_MASK,
		.val = PMX_SDHCI_CD_PL_12_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SDHCI_CD_PORT_SEL_MASK,
		.val = PMX_SDHCI_CD_PORT_12_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg sdhci_cd_51_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_51_MASK,
		.val = PMX_SDHCI_CD_PL_51_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SDHCI_CD_PORT_SEL_MASK,
		.val = PMX_SDHCI_CD_PORT_51_VAL,
	पूर्ण,
पूर्ण;

#घोषणा pmx_sdhci_common_modemux					\
	अणु								\
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE |	\
			SMALL_PRINTERS_MODE | EXTENDED_MODE,		\
		.muxregs = sdhci_muxreg,				\
		.nmuxregs = ARRAY_SIZE(sdhci_muxreg),			\
	पूर्ण, अणु								\
		.modes = EXTENDED_MODE,					\
		.muxregs = sdhci_ext_muxreg,				\
		.nmuxregs = ARRAY_SIZE(sdhci_ext_muxreg),		\
	पूर्ण

अटल काष्ठा spear_modemux sdhci_modemux[][3] = अणु
	अणु
		/* select pin 12 क्रम cd */
		pmx_sdhci_common_modemux,
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = sdhci_cd_12_muxreg,
			.nmuxregs = ARRAY_SIZE(sdhci_cd_12_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* select pin 51 क्रम cd */
		pmx_sdhci_common_modemux,
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = sdhci_cd_51_muxreg,
			.nmuxregs = ARRAY_SIZE(sdhci_cd_51_muxreg),
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा spear_pingroup sdhci_pingroup[] = अणु
	अणु
		.name = "sdhci_cd_12_grp",
		.pins = sdhci_cd_12_pins,
		.npins = ARRAY_SIZE(sdhci_cd_12_pins),
		.modemuxs = sdhci_modemux[0],
		.nmodemuxs = ARRAY_SIZE(sdhci_modemux[0]),
	पूर्ण, अणु
		.name = "sdhci_cd_51_grp",
		.pins = sdhci_cd_51_pins,
		.npins = ARRAY_SIZE(sdhci_cd_51_pins),
		.modemuxs = sdhci_modemux[1],
		.nmodemuxs = ARRAY_SIZE(sdhci_modemux[1]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर sdhci_grps[] = अणु "sdhci_cd_12_grp", "sdhci_cd_51_grp",
	"sdhci_led_grp" पूर्ण;

अटल काष्ठा spear_function sdhci_function = अणु
	.name = "sdhci",
	.groups = sdhci_grps,
	.ngroups = ARRAY_SIZE(sdhci_grps),
पूर्ण;

/* Pad multiplexing क्रम I2S device */
अटल स्थिर अचिन्हित i2s_pins[] = अणु 35, 39, 40, 41, 42 पूर्ण;
अटल काष्ठा spear_muxreg i2s_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg i2s_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_35_MASK | PMX_PL_39_MASK,
		.val = PMX_I2S_REF_CLK_PL_35_VAL | PMX_I2S_PL_39_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_40_MASK | PMX_PL_41_42_MASK,
		.val = PMX_I2S_PL_40_VAL | PMX_I2S_PL_41_42_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2s_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxregs = i2s_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = i2s_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2s_pingroup = अणु
	.name = "i2s_grp",
	.pins = i2s_pins,
	.npins = ARRAY_SIZE(i2s_pins),
	.modemuxs = i2s_modemux,
	.nmodemuxs = ARRAY_SIZE(i2s_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2s_grps[] = अणु "i2s_grp" पूर्ण;
अटल काष्ठा spear_function i2s_function = अणु
	.name = "i2s",
	.groups = i2s_grps,
	.ngroups = ARRAY_SIZE(i2s_grps),
पूर्ण;

/* Pad multiplexing क्रम UART1 device */
अटल स्थिर अचिन्हित uart1_pins[] = अणु 28, 29 पूर्ण;
अटल काष्ठा spear_muxreg uart1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN0_MASK | PMX_GPIO_PIN1_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart1_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_28_29_MASK,
		.val = PMX_UART1_PL_28_29_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| SMALL_PRINTERS_MODE | EXTENDED_MODE,
		.muxregs = uart1_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = uart1_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_ext_muxreg),
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

/* Pad multiplexing क्रम UART1 Modem device */
अटल स्थिर अचिन्हित uart1_modem_2_to_7_pins[] = अणु 2, 3, 4, 5, 6, 7 पूर्ण;
अटल स्थिर अचिन्हित uart1_modem_31_to_36_pins[] = अणु 31, 32, 33, 34, 35, 36 पूर्ण;
अटल स्थिर अचिन्हित uart1_modem_34_to_45_pins[] = अणु 34, 35, 36, 43, 44, 45 पूर्ण;
अटल स्थिर अचिन्हित uart1_modem_80_to_85_pins[] = अणु 80, 81, 82, 83, 84, 85 पूर्ण;

अटल काष्ठा spear_muxreg uart1_modem_ext_2_to_7_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MASK | PMX_I2C_MASK | PMX_SSP_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_2_3_MASK | PMX_PL_6_7_MASK,
		.val = PMX_UART1_ENH_PL_2_3_VAL | PMX_UART1_ENH_PL_4_5_VAL |
			PMX_UART1_ENH_PL_6_7_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART1_ENH_PORT_SEL_MASK,
		.val = PMX_UART1_ENH_PORT_3_TO_5_7_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart1_modem_31_to_36_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN3_MASK | PMX_GPIO_PIN4_MASK |
			PMX_GPIO_PIN5_MASK | PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart1_modem_ext_31_to_36_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_31_MASK | PMX_PL_32_33_MASK | PMX_PL_34_MASK |
			PMX_PL_35_MASK | PMX_PL_36_MASK,
		.val = PMX_UART1_ENH_PL_31_VAL | PMX_UART1_ENH_PL_32_33_VAL |
			PMX_UART1_ENH_PL_34_VAL | PMX_UART1_ENH_PL_35_VAL |
			PMX_UART1_ENH_PL_36_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART1_ENH_PORT_SEL_MASK,
		.val = PMX_UART1_ENH_PORT_32_TO_34_36_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart1_modem_34_to_45_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK |
			PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart1_modem_ext_34_to_45_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_34_MASK | PMX_PL_35_MASK | PMX_PL_36_MASK,
		.val = PMX_UART1_ENH_PL_34_VAL | PMX_UART1_ENH_PL_35_VAL |
			PMX_UART1_ENH_PL_36_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_43_MASK | PMX_PL_44_45_MASK,
		.val = PMX_UART1_ENH_PL_43_VAL | PMX_UART1_ENH_PL_44_45_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART1_ENH_PORT_SEL_MASK,
		.val = PMX_UART1_ENH_PORT_44_45_34_36_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart1_modem_ext_80_to_85_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_80_TO_85_MASK,
		.val = PMX_UART1_ENH_PL_80_TO_85_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_43_MASK | PMX_PL_44_45_MASK,
		.val = PMX_UART1_ENH_PL_43_VAL | PMX_UART1_ENH_PL_44_45_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART1_ENH_PORT_SEL_MASK,
		.val = PMX_UART1_ENH_PORT_81_TO_85_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modem_2_to_7_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = uart1_modem_ext_2_to_7_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_modem_ext_2_to_7_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modem_31_to_36_modemux[] = अणु
	अणु
		.modes = SMALL_PRINTERS_MODE | EXTENDED_MODE,
		.muxregs = uart1_modem_31_to_36_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_modem_31_to_36_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = uart1_modem_ext_31_to_36_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_modem_ext_31_to_36_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modem_34_to_45_modemux[] = अणु
	अणु
		.modes = AUTO_EXP_MODE | EXTENDED_MODE,
		.muxregs = uart1_modem_34_to_45_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_modem_34_to_45_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = uart1_modem_ext_34_to_45_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_modem_ext_34_to_45_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modem_80_to_85_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = uart1_modem_ext_80_to_85_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_modem_ext_80_to_85_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart1_modem_pingroup[] = अणु
	अणु
		.name = "uart1_modem_2_to_7_grp",
		.pins = uart1_modem_2_to_7_pins,
		.npins = ARRAY_SIZE(uart1_modem_2_to_7_pins),
		.modemuxs = uart1_modem_2_to_7_modemux,
		.nmodemuxs = ARRAY_SIZE(uart1_modem_2_to_7_modemux),
	पूर्ण, अणु
		.name = "uart1_modem_31_to_36_grp",
		.pins = uart1_modem_31_to_36_pins,
		.npins = ARRAY_SIZE(uart1_modem_31_to_36_pins),
		.modemuxs = uart1_modem_31_to_36_modemux,
		.nmodemuxs = ARRAY_SIZE(uart1_modem_31_to_36_modemux),
	पूर्ण, अणु
		.name = "uart1_modem_34_to_45_grp",
		.pins = uart1_modem_34_to_45_pins,
		.npins = ARRAY_SIZE(uart1_modem_34_to_45_pins),
		.modemuxs = uart1_modem_34_to_45_modemux,
		.nmodemuxs = ARRAY_SIZE(uart1_modem_34_to_45_modemux),
	पूर्ण, अणु
		.name = "uart1_modem_80_to_85_grp",
		.pins = uart1_modem_80_to_85_pins,
		.npins = ARRAY_SIZE(uart1_modem_80_to_85_pins),
		.modemuxs = uart1_modem_80_to_85_modemux,
		.nmodemuxs = ARRAY_SIZE(uart1_modem_80_to_85_modemux),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart1_modem_grps[] = अणु "uart1_modem_2_to_7_grp",
	"uart1_modem_31_to_36_grp", "uart1_modem_34_to_45_grp",
	"uart1_modem_80_to_85_grp" पूर्ण;
अटल काष्ठा spear_function uart1_modem_function = अणु
	.name = "uart1_modem",
	.groups = uart1_modem_grps,
	.ngroups = ARRAY_SIZE(uart1_modem_grps),
पूर्ण;

/* Pad multiplexing क्रम UART2 device */
अटल स्थिर अचिन्हित uart2_pins[] = अणु 0, 1 पूर्ण;
अटल काष्ठा spear_muxreg uart2_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_FIRDA_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart2_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_0_1_MASK,
		.val = PMX_UART2_PL_0_1_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart2_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| SMALL_PRINTERS_MODE | EXTENDED_MODE,
		.muxregs = uart2_muxreg,
		.nmuxregs = ARRAY_SIZE(uart2_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = uart2_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(uart2_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart2_pingroup = अणु
	.name = "uart2_grp",
	.pins = uart2_pins,
	.npins = ARRAY_SIZE(uart2_pins),
	.modemuxs = uart2_modemux,
	.nmodemuxs = ARRAY_SIZE(uart2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart2_grps[] = अणु "uart2_grp" पूर्ण;
अटल काष्ठा spear_function uart2_function = अणु
	.name = "uart2",
	.groups = uart2_grps,
	.ngroups = ARRAY_SIZE(uart2_grps),
पूर्ण;

/* Pad multiplexing क्रम uart3 device */
अटल स्थिर अचिन्हित uart3_pins[][2] = अणु अणु 8, 9 पूर्ण, अणु 15, 16 पूर्ण, अणु 41, 42 पूर्ण,
	अणु 52, 53 पूर्ण, अणु 73, 74 पूर्ण, अणु 94, 95 पूर्ण, अणु 98, 99 पूर्ण पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_8_9_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_8_9_MASK,
		.val = PMX_UART3_PL_8_9_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_8_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_15_16_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_15_16_MASK,
		.val = PMX_UART3_PL_15_16_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_15_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_41_42_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_41_42_MASK,
		.val = PMX_UART3_PL_41_42_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_41_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_52_53_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_52_53_MASK,
		.val = PMX_UART3_PL_52_53_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_52_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_73_74_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_73_MASK | PMX_PL_74_MASK,
		.val = PMX_UART3_PL_73_VAL | PMX_UART3_PL_74_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_73_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_94_95_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_94_95_MASK,
		.val = PMX_UART3_PL_94_95_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_94_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart3_ext_98_99_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_98_MASK | PMX_PL_99_MASK,
		.val = PMX_UART3_PL_98_VAL | PMX_UART3_PL_99_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART3_PORT_SEL_MASK,
		.val = PMX_UART3_PORT_99_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart3_modemux[][1] = अणु
	अणु
		/* Select संकेतs on pins 8_9 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_8_9_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_8_9_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 15_16 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_15_16_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_15_16_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 41_42 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_41_42_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_41_42_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 52_53 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_52_53_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_52_53_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 73_74 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_73_74_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_73_74_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 94_95 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_94_95_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_94_95_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 98_99 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart3_ext_98_99_muxreg,
			.nmuxregs = ARRAY_SIZE(uart3_ext_98_99_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart3_pingroup[] = अणु
	अणु
		.name = "uart3_8_9_grp",
		.pins = uart3_pins[0],
		.npins = ARRAY_SIZE(uart3_pins[0]),
		.modemuxs = uart3_modemux[0],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[0]),
	पूर्ण, अणु
		.name = "uart3_15_16_grp",
		.pins = uart3_pins[1],
		.npins = ARRAY_SIZE(uart3_pins[1]),
		.modemuxs = uart3_modemux[1],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[1]),
	पूर्ण, अणु
		.name = "uart3_41_42_grp",
		.pins = uart3_pins[2],
		.npins = ARRAY_SIZE(uart3_pins[2]),
		.modemuxs = uart3_modemux[2],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[2]),
	पूर्ण, अणु
		.name = "uart3_52_53_grp",
		.pins = uart3_pins[3],
		.npins = ARRAY_SIZE(uart3_pins[3]),
		.modemuxs = uart3_modemux[3],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[3]),
	पूर्ण, अणु
		.name = "uart3_73_74_grp",
		.pins = uart3_pins[4],
		.npins = ARRAY_SIZE(uart3_pins[4]),
		.modemuxs = uart3_modemux[4],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[4]),
	पूर्ण, अणु
		.name = "uart3_94_95_grp",
		.pins = uart3_pins[5],
		.npins = ARRAY_SIZE(uart3_pins[5]),
		.modemuxs = uart3_modemux[5],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[5]),
	पूर्ण, अणु
		.name = "uart3_98_99_grp",
		.pins = uart3_pins[6],
		.npins = ARRAY_SIZE(uart3_pins[6]),
		.modemuxs = uart3_modemux[6],
		.nmodemuxs = ARRAY_SIZE(uart3_modemux[6]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart3_grps[] = अणु "uart3_8_9_grp", "uart3_15_16_grp",
	"uart3_41_42_grp", "uart3_52_53_grp", "uart3_73_74_grp",
	"uart3_94_95_grp", "uart3_98_99_grp" पूर्ण;

अटल काष्ठा spear_function uart3_function = अणु
	.name = "uart3",
	.groups = uart3_grps,
	.ngroups = ARRAY_SIZE(uart3_grps),
पूर्ण;

/* Pad multiplexing क्रम uart4 device */
अटल स्थिर अचिन्हित uart4_pins[][2] = अणु अणु 6, 7 पूर्ण, अणु 13, 14 पूर्ण, अणु 39, 40 पूर्ण,
	अणु 71, 72 पूर्ण, अणु 92, 93 पूर्ण, अणु 100, 101 पूर्ण पूर्ण;

अटल काष्ठा spear_muxreg uart4_ext_6_7_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_6_7_MASK,
		.val = PMX_UART4_PL_6_7_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART4_PORT_SEL_MASK,
		.val = PMX_UART4_PORT_6_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart4_ext_13_14_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_13_14_MASK,
		.val = PMX_UART4_PL_13_14_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART4_PORT_SEL_MASK,
		.val = PMX_UART4_PORT_13_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart4_ext_39_40_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_39_MASK,
		.val = PMX_UART4_PL_39_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_40_MASK,
		.val = PMX_UART4_PL_40_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART4_PORT_SEL_MASK,
		.val = PMX_UART4_PORT_39_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart4_ext_71_72_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_71_72_MASK,
		.val = PMX_UART4_PL_71_72_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART4_PORT_SEL_MASK,
		.val = PMX_UART4_PORT_71_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart4_ext_92_93_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_92_93_MASK,
		.val = PMX_UART4_PL_92_93_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART4_PORT_SEL_MASK,
		.val = PMX_UART4_PORT_92_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart4_ext_100_101_muxreg[] = अणु
	अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_PL_100_101_MASK |
			PMX_UART4_PORT_SEL_MASK,
		.val = PMX_UART4_PL_100_101_VAL |
			PMX_UART4_PORT_101_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart4_modemux[][1] = अणु
	अणु
		/* Select संकेतs on pins 6_7 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart4_ext_6_7_muxreg,
			.nmuxregs = ARRAY_SIZE(uart4_ext_6_7_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 13_14 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart4_ext_13_14_muxreg,
			.nmuxregs = ARRAY_SIZE(uart4_ext_13_14_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 39_40 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart4_ext_39_40_muxreg,
			.nmuxregs = ARRAY_SIZE(uart4_ext_39_40_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 71_72 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart4_ext_71_72_muxreg,
			.nmuxregs = ARRAY_SIZE(uart4_ext_71_72_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 92_93 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart4_ext_92_93_muxreg,
			.nmuxregs = ARRAY_SIZE(uart4_ext_92_93_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 100_101_ */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart4_ext_100_101_muxreg,
			.nmuxregs = ARRAY_SIZE(uart4_ext_100_101_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart4_pingroup[] = अणु
	अणु
		.name = "uart4_6_7_grp",
		.pins = uart4_pins[0],
		.npins = ARRAY_SIZE(uart4_pins[0]),
		.modemuxs = uart4_modemux[0],
		.nmodemuxs = ARRAY_SIZE(uart4_modemux[0]),
	पूर्ण, अणु
		.name = "uart4_13_14_grp",
		.pins = uart4_pins[1],
		.npins = ARRAY_SIZE(uart4_pins[1]),
		.modemuxs = uart4_modemux[1],
		.nmodemuxs = ARRAY_SIZE(uart4_modemux[1]),
	पूर्ण, अणु
		.name = "uart4_39_40_grp",
		.pins = uart4_pins[2],
		.npins = ARRAY_SIZE(uart4_pins[2]),
		.modemuxs = uart4_modemux[2],
		.nmodemuxs = ARRAY_SIZE(uart4_modemux[2]),
	पूर्ण, अणु
		.name = "uart4_71_72_grp",
		.pins = uart4_pins[3],
		.npins = ARRAY_SIZE(uart4_pins[3]),
		.modemuxs = uart4_modemux[3],
		.nmodemuxs = ARRAY_SIZE(uart4_modemux[3]),
	पूर्ण, अणु
		.name = "uart4_92_93_grp",
		.pins = uart4_pins[4],
		.npins = ARRAY_SIZE(uart4_pins[4]),
		.modemuxs = uart4_modemux[4],
		.nmodemuxs = ARRAY_SIZE(uart4_modemux[4]),
	पूर्ण, अणु
		.name = "uart4_100_101_grp",
		.pins = uart4_pins[5],
		.npins = ARRAY_SIZE(uart4_pins[5]),
		.modemuxs = uart4_modemux[5],
		.nmodemuxs = ARRAY_SIZE(uart4_modemux[5]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart4_grps[] = अणु "uart4_6_7_grp", "uart4_13_14_grp",
	"uart4_39_40_grp", "uart4_71_72_grp", "uart4_92_93_grp",
	"uart4_100_101_grp" पूर्ण;

अटल काष्ठा spear_function uart4_function = अणु
	.name = "uart4",
	.groups = uart4_grps,
	.ngroups = ARRAY_SIZE(uart4_grps),
पूर्ण;

/* Pad multiplexing क्रम uart5 device */
अटल स्थिर अचिन्हित uart5_pins[][2] = अणु अणु 4, 5 पूर्ण, अणु 37, 38 पूर्ण, अणु 69, 70 पूर्ण,
	अणु 90, 91 पूर्ण पूर्ण;

अटल काष्ठा spear_muxreg uart5_ext_4_5_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_I2C_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_4_5_MASK,
		.val = PMX_UART5_PL_4_5_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART5_PORT_SEL_MASK,
		.val = PMX_UART5_PORT_4_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart5_ext_37_38_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_37_38_MASK,
		.val = PMX_UART5_PL_37_38_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART5_PORT_SEL_MASK,
		.val = PMX_UART5_PORT_37_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart5_ext_69_70_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_69_MASK,
		.val = PMX_UART5_PL_69_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_70_MASK,
		.val = PMX_UART5_PL_70_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART5_PORT_SEL_MASK,
		.val = PMX_UART5_PORT_69_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart5_ext_90_91_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_90_91_MASK,
		.val = PMX_UART5_PL_90_91_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART5_PORT_SEL_MASK,
		.val = PMX_UART5_PORT_90_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart5_modemux[][1] = अणु
	अणु
		/* Select संकेतs on pins 4_5 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart5_ext_4_5_muxreg,
			.nmuxregs = ARRAY_SIZE(uart5_ext_4_5_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 37_38 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart5_ext_37_38_muxreg,
			.nmuxregs = ARRAY_SIZE(uart5_ext_37_38_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 69_70 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart5_ext_69_70_muxreg,
			.nmuxregs = ARRAY_SIZE(uart5_ext_69_70_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 90_91 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart5_ext_90_91_muxreg,
			.nmuxregs = ARRAY_SIZE(uart5_ext_90_91_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart5_pingroup[] = अणु
	अणु
		.name = "uart5_4_5_grp",
		.pins = uart5_pins[0],
		.npins = ARRAY_SIZE(uart5_pins[0]),
		.modemuxs = uart5_modemux[0],
		.nmodemuxs = ARRAY_SIZE(uart5_modemux[0]),
	पूर्ण, अणु
		.name = "uart5_37_38_grp",
		.pins = uart5_pins[1],
		.npins = ARRAY_SIZE(uart5_pins[1]),
		.modemuxs = uart5_modemux[1],
		.nmodemuxs = ARRAY_SIZE(uart5_modemux[1]),
	पूर्ण, अणु
		.name = "uart5_69_70_grp",
		.pins = uart5_pins[2],
		.npins = ARRAY_SIZE(uart5_pins[2]),
		.modemuxs = uart5_modemux[2],
		.nmodemuxs = ARRAY_SIZE(uart5_modemux[2]),
	पूर्ण, अणु
		.name = "uart5_90_91_grp",
		.pins = uart5_pins[3],
		.npins = ARRAY_SIZE(uart5_pins[3]),
		.modemuxs = uart5_modemux[3],
		.nmodemuxs = ARRAY_SIZE(uart5_modemux[3]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart5_grps[] = अणु "uart5_4_5_grp", "uart5_37_38_grp",
	"uart5_69_70_grp", "uart5_90_91_grp" पूर्ण;
अटल काष्ठा spear_function uart5_function = अणु
	.name = "uart5",
	.groups = uart5_grps,
	.ngroups = ARRAY_SIZE(uart5_grps),
पूर्ण;

/* Pad multiplexing क्रम uart6 device */
अटल स्थिर अचिन्हित uart6_pins[][2] = अणु अणु 2, 3 पूर्ण, अणु 88, 89 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg uart6_ext_2_3_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_2_3_MASK,
		.val = PMX_UART6_PL_2_3_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART6_PORT_SEL_MASK,
		.val = PMX_UART6_PORT_2_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg uart6_ext_88_89_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_88_89_MASK,
		.val = PMX_UART6_PL_88_89_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_UART6_PORT_SEL_MASK,
		.val = PMX_UART6_PORT_88_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart6_modemux[][1] = अणु
	अणु
		/* Select संकेतs on pins 2_3 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart6_ext_2_3_muxreg,
			.nmuxregs = ARRAY_SIZE(uart6_ext_2_3_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 88_89 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = uart6_ext_88_89_muxreg,
			.nmuxregs = ARRAY_SIZE(uart6_ext_88_89_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart6_pingroup[] = अणु
	अणु
		.name = "uart6_2_3_grp",
		.pins = uart6_pins[0],
		.npins = ARRAY_SIZE(uart6_pins[0]),
		.modemuxs = uart6_modemux[0],
		.nmodemuxs = ARRAY_SIZE(uart6_modemux[0]),
	पूर्ण, अणु
		.name = "uart6_88_89_grp",
		.pins = uart6_pins[1],
		.npins = ARRAY_SIZE(uart6_pins[1]),
		.modemuxs = uart6_modemux[1],
		.nmodemuxs = ARRAY_SIZE(uart6_modemux[1]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart6_grps[] = अणु "uart6_2_3_grp", "uart6_88_89_grp" पूर्ण;
अटल काष्ठा spear_function uart6_function = अणु
	.name = "uart6",
	.groups = uart6_grps,
	.ngroups = ARRAY_SIZE(uart6_grps),
पूर्ण;

/* UART - RS485 pmx */
अटल स्थिर अचिन्हित rs485_pins[] = अणु 77, 78, 79 पूर्ण;
अटल काष्ठा spear_muxreg rs485_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_77_78_79_MASK,
		.val = PMX_RS485_PL_77_78_79_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux rs485_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = rs485_muxreg,
		.nmuxregs = ARRAY_SIZE(rs485_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup rs485_pingroup = अणु
	.name = "rs485_grp",
	.pins = rs485_pins,
	.npins = ARRAY_SIZE(rs485_pins),
	.modemuxs = rs485_modemux,
	.nmodemuxs = ARRAY_SIZE(rs485_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर rs485_grps[] = अणु "rs485_grp" पूर्ण;
अटल काष्ठा spear_function rs485_function = अणु
	.name = "rs485",
	.groups = rs485_grps,
	.ngroups = ARRAY_SIZE(rs485_grps),
पूर्ण;

/* Pad multiplexing क्रम Touchscreen device */
अटल स्थिर अचिन्हित touchscreen_pins[] = अणु 5, 36 पूर्ण;
अटल काष्ठा spear_muxreg touchscreen_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_I2C_MASK | PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg touchscreen_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_5_MASK,
		.val = PMX_TOUCH_Y_PL_5_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_36_MASK,
		.val = PMX_TOUCH_X_PL_36_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux touchscreen_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | EXTENDED_MODE,
		.muxregs = touchscreen_muxreg,
		.nmuxregs = ARRAY_SIZE(touchscreen_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = touchscreen_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(touchscreen_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup touchscreen_pingroup = अणु
	.name = "touchscreen_grp",
	.pins = touchscreen_pins,
	.npins = ARRAY_SIZE(touchscreen_pins),
	.modemuxs = touchscreen_modemux,
	.nmodemuxs = ARRAY_SIZE(touchscreen_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर touchscreen_grps[] = अणु "touchscreen_grp" पूर्ण;
अटल काष्ठा spear_function touchscreen_function = अणु
	.name = "touchscreen",
	.groups = touchscreen_grps,
	.ngroups = ARRAY_SIZE(touchscreen_grps),
पूर्ण;

/* Pad multiplexing क्रम CAN device */
अटल स्थिर अचिन्हित can0_pins[] = अणु 32, 33 पूर्ण;
अटल काष्ठा spear_muxreg can0_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN4_MASK | PMX_GPIO_PIN5_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg can0_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_32_33_MASK,
		.val = PMX_CAN0_PL_32_33_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux can0_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| EXTENDED_MODE,
		.muxregs = can0_muxreg,
		.nmuxregs = ARRAY_SIZE(can0_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = can0_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(can0_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup can0_pingroup = अणु
	.name = "can0_grp",
	.pins = can0_pins,
	.npins = ARRAY_SIZE(can0_pins),
	.modemuxs = can0_modemux,
	.nmodemuxs = ARRAY_SIZE(can0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर can0_grps[] = अणु "can0_grp" पूर्ण;
अटल काष्ठा spear_function can0_function = अणु
	.name = "can0",
	.groups = can0_grps,
	.ngroups = ARRAY_SIZE(can0_grps),
पूर्ण;

अटल स्थिर अचिन्हित can1_pins[] = अणु 30, 31 पूर्ण;
अटल काष्ठा spear_muxreg can1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg can1_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_30_31_MASK,
		.val = PMX_CAN1_PL_30_31_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux can1_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| EXTENDED_MODE,
		.muxregs = can1_muxreg,
		.nmuxregs = ARRAY_SIZE(can1_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = can1_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(can1_ext_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup can1_pingroup = अणु
	.name = "can1_grp",
	.pins = can1_pins,
	.npins = ARRAY_SIZE(can1_pins),
	.modemuxs = can1_modemux,
	.nmodemuxs = ARRAY_SIZE(can1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर can1_grps[] = अणु "can1_grp" पूर्ण;
अटल काष्ठा spear_function can1_function = अणु
	.name = "can1",
	.groups = can1_grps,
	.ngroups = ARRAY_SIZE(can1_grps),
पूर्ण;

/* Pad multiplexing क्रम PWM0_1 device */
अटल स्थिर अचिन्हित pwm0_1_pins[][2] = अणु अणु 37, 38 पूर्ण, अणु 14, 15 पूर्ण, अणु 8, 9 पूर्ण,
	अणु 30, 31 पूर्ण, अणु 42, 43 पूर्ण, अणु 59, 60 पूर्ण, अणु 88, 89 पूर्ण पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_8_9_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_8_9_MASK,
		.val = PMX_PWM_0_1_PL_8_9_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_स्वतःexpsmallpri_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_14_15_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_14_MASK | PMX_PL_15_MASK,
		.val = PMX_PWM1_PL_14_VAL | PMX_PWM0_PL_15_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_30_31_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_30_MASK | PMX_PL_31_MASK,
		.val = PMX_PWM1_EXT_PL_30_VAL | PMX_PWM0_EXT_PL_31_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_net_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_37_38_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_37_38_MASK,
		.val = PMX_PWM0_1_PL_37_38_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_42_43_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK | PMX_TIMER_0_1_MASK ,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_42_MASK | PMX_PL_43_MASK,
		.val = PMX_PWM1_PL_42_VAL |
			PMX_PWM0_PL_43_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_59_60_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_59_MASK,
		.val = PMX_PWM1_PL_59_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_60_MASK,
		.val = PMX_PWM0_PL_60_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm0_1_pin_88_89_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_88_89_MASK,
		.val = PMX_PWM0_1_PL_88_89_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_8_9_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_8_9_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_8_9_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_14_15_modemux[] = अणु
	अणु
		.modes = AUTO_EXP_MODE | SMALL_PRINTERS_MODE | EXTENDED_MODE,
		.muxregs = pwm0_1_स्वतःexpsmallpri_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_स्वतःexpsmallpri_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_14_15_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_14_15_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_30_31_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_30_31_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_30_31_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_37_38_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxregs = pwm0_1_net_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_net_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_37_38_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_37_38_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_42_43_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_42_43_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_42_43_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_59_60_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_59_60_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_59_60_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm0_1_pin_88_89_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm0_1_pin_88_89_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm0_1_pin_88_89_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm0_1_pingroup[] = अणु
	अणु
		.name = "pwm0_1_pin_8_9_grp",
		.pins = pwm0_1_pins[0],
		.npins = ARRAY_SIZE(pwm0_1_pins[0]),
		.modemuxs = pwm0_1_pin_8_9_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_8_9_modemux),
	पूर्ण, अणु
		.name = "pwm0_1_pin_14_15_grp",
		.pins = pwm0_1_pins[1],
		.npins = ARRAY_SIZE(pwm0_1_pins[1]),
		.modemuxs = pwm0_1_pin_14_15_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_14_15_modemux),
	पूर्ण, अणु
		.name = "pwm0_1_pin_30_31_grp",
		.pins = pwm0_1_pins[2],
		.npins = ARRAY_SIZE(pwm0_1_pins[2]),
		.modemuxs = pwm0_1_pin_30_31_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_30_31_modemux),
	पूर्ण, अणु
		.name = "pwm0_1_pin_37_38_grp",
		.pins = pwm0_1_pins[3],
		.npins = ARRAY_SIZE(pwm0_1_pins[3]),
		.modemuxs = pwm0_1_pin_37_38_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_37_38_modemux),
	पूर्ण, अणु
		.name = "pwm0_1_pin_42_43_grp",
		.pins = pwm0_1_pins[4],
		.npins = ARRAY_SIZE(pwm0_1_pins[4]),
		.modemuxs = pwm0_1_pin_42_43_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_42_43_modemux),
	पूर्ण, अणु
		.name = "pwm0_1_pin_59_60_grp",
		.pins = pwm0_1_pins[5],
		.npins = ARRAY_SIZE(pwm0_1_pins[5]),
		.modemuxs = pwm0_1_pin_59_60_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_59_60_modemux),
	पूर्ण, अणु
		.name = "pwm0_1_pin_88_89_grp",
		.pins = pwm0_1_pins[6],
		.npins = ARRAY_SIZE(pwm0_1_pins[6]),
		.modemuxs = pwm0_1_pin_88_89_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm0_1_pin_88_89_modemux),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर pwm0_1_grps[] = अणु "pwm0_1_pin_8_9_grp",
	"pwm0_1_pin_14_15_grp", "pwm0_1_pin_30_31_grp", "pwm0_1_pin_37_38_grp",
	"pwm0_1_pin_42_43_grp", "pwm0_1_pin_59_60_grp", "pwm0_1_pin_88_89_grp"
पूर्ण;

अटल काष्ठा spear_function pwm0_1_function = अणु
	.name = "pwm0_1",
	.groups = pwm0_1_grps,
	.ngroups = ARRAY_SIZE(pwm0_1_grps),
पूर्ण;

/* Pad multiplexing क्रम PWM2 device */
अटल स्थिर अचिन्हित pwm2_pins[][1] = अणु अणु 7 पूर्ण, अणु 13 पूर्ण, अणु 29 पूर्ण, अणु 34 पूर्ण, अणु 41 पूर्ण,
	अणु 58 पूर्ण, अणु 87 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg pwm2_net_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_7_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_7_MASK,
		.val = PMX_PWM_2_PL_7_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_स्वतःexpsmallpri_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_13_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_13_MASK,
		.val = PMX_PWM2_PL_13_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_29_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN1_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_29_MASK,
		.val = PMX_PWM_2_PL_29_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_34_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = MODE_CONFIG_REG,
		.mask = PMX_PWM_MASK,
		.val = PMX_PWM_MASK,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_34_MASK,
		.val = PMX_PWM2_PL_34_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_41_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_41_MASK,
		.val = PMX_PWM2_PL_41_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_58_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_58_MASK,
		.val = PMX_PWM2_PL_58_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm2_pin_87_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_87_MASK,
		.val = PMX_PWM2_PL_87_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm2_pin_7_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxregs = pwm2_net_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_net_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_7_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_7_muxreg),
	पूर्ण,
पूर्ण;
अटल काष्ठा spear_modemux pwm2_pin_13_modemux[] = अणु
	अणु
		.modes = AUTO_EXP_MODE | SMALL_PRINTERS_MODE | EXTENDED_MODE,
		.muxregs = pwm2_स्वतःexpsmallpri_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_स्वतःexpsmallpri_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_13_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_13_muxreg),
	पूर्ण,
पूर्ण;
अटल काष्ठा spear_modemux pwm2_pin_29_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_29_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_29_muxreg),
	पूर्ण,
पूर्ण;
अटल काष्ठा spear_modemux pwm2_pin_34_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_34_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_34_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm2_pin_41_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_41_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_41_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm2_pin_58_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_58_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_58_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm2_pin_87_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm2_pin_87_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm2_pin_87_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm2_pingroup[] = अणु
	अणु
		.name = "pwm2_pin_7_grp",
		.pins = pwm2_pins[0],
		.npins = ARRAY_SIZE(pwm2_pins[0]),
		.modemuxs = pwm2_pin_7_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_7_modemux),
	पूर्ण, अणु
		.name = "pwm2_pin_13_grp",
		.pins = pwm2_pins[1],
		.npins = ARRAY_SIZE(pwm2_pins[1]),
		.modemuxs = pwm2_pin_13_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_13_modemux),
	पूर्ण, अणु
		.name = "pwm2_pin_29_grp",
		.pins = pwm2_pins[2],
		.npins = ARRAY_SIZE(pwm2_pins[2]),
		.modemuxs = pwm2_pin_29_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_29_modemux),
	पूर्ण, अणु
		.name = "pwm2_pin_34_grp",
		.pins = pwm2_pins[3],
		.npins = ARRAY_SIZE(pwm2_pins[3]),
		.modemuxs = pwm2_pin_34_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_34_modemux),
	पूर्ण, अणु
		.name = "pwm2_pin_41_grp",
		.pins = pwm2_pins[4],
		.npins = ARRAY_SIZE(pwm2_pins[4]),
		.modemuxs = pwm2_pin_41_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_41_modemux),
	पूर्ण, अणु
		.name = "pwm2_pin_58_grp",
		.pins = pwm2_pins[5],
		.npins = ARRAY_SIZE(pwm2_pins[5]),
		.modemuxs = pwm2_pin_58_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_58_modemux),
	पूर्ण, अणु
		.name = "pwm2_pin_87_grp",
		.pins = pwm2_pins[6],
		.npins = ARRAY_SIZE(pwm2_pins[6]),
		.modemuxs = pwm2_pin_87_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm2_pin_87_modemux),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर pwm2_grps[] = अणु "pwm2_pin_7_grp", "pwm2_pin_13_grp",
	"pwm2_pin_29_grp", "pwm2_pin_34_grp", "pwm2_pin_41_grp",
	"pwm2_pin_58_grp", "pwm2_pin_87_grp" पूर्ण;
अटल काष्ठा spear_function pwm2_function = अणु
	.name = "pwm2",
	.groups = pwm2_grps,
	.ngroups = ARRAY_SIZE(pwm2_grps),
पूर्ण;

/* Pad multiplexing क्रम PWM3 device */
अटल स्थिर अचिन्हित pwm3_pins[][1] = अणु अणु 6 पूर्ण, अणु 12 पूर्ण, अणु 28 पूर्ण, अणु 40 पूर्ण, अणु 57 पूर्ण,
	अणु 86 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg pwm3_pin_6_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_6_MASK,
		.val = PMX_PWM_3_PL_6_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm3_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm3_pin_12_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_12_MASK,
		.val = PMX_PWM3_PL_12_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm3_pin_28_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_28_MASK,
		.val = PMX_PWM_3_PL_28_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm3_pin_40_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_40_MASK,
		.val = PMX_PWM3_PL_40_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm3_pin_57_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_57_MASK,
		.val = PMX_PWM3_PL_57_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg pwm3_pin_86_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_86_MASK,
		.val = PMX_PWM3_PL_86_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_pin_6_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm3_pin_6_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_pin_6_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_pin_12_modemux[] = अणु
	अणु
		.modes = AUTO_EXP_MODE | SMALL_PRINTERS_MODE |
			AUTO_NET_SMII_MODE | EXTENDED_MODE,
		.muxregs = pwm3_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm3_pin_12_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_pin_12_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_pin_28_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm3_pin_28_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_pin_28_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_pin_40_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm3_pin_40_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_pin_40_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_pin_57_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm3_pin_57_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_pin_57_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux pwm3_pin_86_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = pwm3_pin_86_muxreg,
		.nmuxregs = ARRAY_SIZE(pwm3_pin_86_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup pwm3_pingroup[] = अणु
	अणु
		.name = "pwm3_pin_6_grp",
		.pins = pwm3_pins[0],
		.npins = ARRAY_SIZE(pwm3_pins[0]),
		.modemuxs = pwm3_pin_6_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm3_pin_6_modemux),
	पूर्ण, अणु
		.name = "pwm3_pin_12_grp",
		.pins = pwm3_pins[1],
		.npins = ARRAY_SIZE(pwm3_pins[1]),
		.modemuxs = pwm3_pin_12_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm3_pin_12_modemux),
	पूर्ण, अणु
		.name = "pwm3_pin_28_grp",
		.pins = pwm3_pins[2],
		.npins = ARRAY_SIZE(pwm3_pins[2]),
		.modemuxs = pwm3_pin_28_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm3_pin_28_modemux),
	पूर्ण, अणु
		.name = "pwm3_pin_40_grp",
		.pins = pwm3_pins[3],
		.npins = ARRAY_SIZE(pwm3_pins[3]),
		.modemuxs = pwm3_pin_40_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm3_pin_40_modemux),
	पूर्ण, अणु
		.name = "pwm3_pin_57_grp",
		.pins = pwm3_pins[4],
		.npins = ARRAY_SIZE(pwm3_pins[4]),
		.modemuxs = pwm3_pin_57_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm3_pin_57_modemux),
	पूर्ण, अणु
		.name = "pwm3_pin_86_grp",
		.pins = pwm3_pins[5],
		.npins = ARRAY_SIZE(pwm3_pins[5]),
		.modemuxs = pwm3_pin_86_modemux,
		.nmodemuxs = ARRAY_SIZE(pwm3_pin_86_modemux),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर pwm3_grps[] = अणु "pwm3_pin_6_grp", "pwm3_pin_12_grp",
	"pwm3_pin_28_grp", "pwm3_pin_40_grp", "pwm3_pin_57_grp",
	"pwm3_pin_86_grp" पूर्ण;
अटल काष्ठा spear_function pwm3_function = अणु
	.name = "pwm3",
	.groups = pwm3_grps,
	.ngroups = ARRAY_SIZE(pwm3_grps),
पूर्ण;

/* Pad multiplexing क्रम SSP1 device */
अटल स्थिर अचिन्हित ssp1_pins[][2] = अणु अणु 17, 20 पूर्ण, अणु 36, 39 पूर्ण, अणु 48, 51 पूर्ण,
	अणु 65, 68 पूर्ण, अणु 94, 97 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg ssp1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp1_ext_17_20_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_17_18_MASK | PMX_PL_19_MASK,
		.val = PMX_SSP1_PL_17_18_19_20_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_20_MASK,
		.val = PMX_SSP1_PL_17_18_19_20_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP1_PORT_SEL_MASK,
		.val = PMX_SSP1_PORT_17_TO_20_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp1_ext_36_39_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK | PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_36_MASK | PMX_PL_37_38_MASK | PMX_PL_39_MASK,
		.val = PMX_SSP1_PL_36_VAL | PMX_SSP1_PL_37_38_VAL |
			PMX_SSP1_PL_39_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP1_PORT_SEL_MASK,
		.val = PMX_SSP1_PORT_36_TO_39_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp1_ext_48_51_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_48_49_MASK,
		.val = PMX_SSP1_PL_48_49_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_50_59_REG,
		.mask = PMX_PL_50_51_MASK,
		.val = PMX_SSP1_PL_50_51_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP1_PORT_SEL_MASK,
		.val = PMX_SSP1_PORT_48_TO_51_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp1_ext_65_68_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_65_TO_68_MASK,
		.val = PMX_SSP1_PL_65_TO_68_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP1_PORT_SEL_MASK,
		.val = PMX_SSP1_PORT_65_TO_68_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp1_ext_94_97_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_94_95_MASK | PMX_PL_96_97_MASK,
		.val = PMX_SSP1_PL_94_95_VAL | PMX_SSP1_PL_96_97_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP1_PORT_SEL_MASK,
		.val = PMX_SSP1_PORT_94_TO_97_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp1_17_20_modemux[] = अणु
	अणु
		.modes = SMALL_PRINTERS_MODE | AUTO_NET_SMII_MODE |
			EXTENDED_MODE,
		.muxregs = ssp1_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp1_ext_17_20_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_ext_17_20_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp1_36_39_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp1_ext_36_39_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_ext_36_39_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp1_48_51_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp1_ext_48_51_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_ext_48_51_muxreg),
	पूर्ण,
पूर्ण;
अटल काष्ठा spear_modemux ssp1_65_68_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp1_ext_65_68_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_ext_65_68_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp1_94_97_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp1_ext_94_97_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp1_ext_94_97_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp1_pingroup[] = अणु
	अणु
		.name = "ssp1_17_20_grp",
		.pins = ssp1_pins[0],
		.npins = ARRAY_SIZE(ssp1_pins[0]),
		.modemuxs = ssp1_17_20_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp1_17_20_modemux),
	पूर्ण, अणु
		.name = "ssp1_36_39_grp",
		.pins = ssp1_pins[1],
		.npins = ARRAY_SIZE(ssp1_pins[1]),
		.modemuxs = ssp1_36_39_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp1_36_39_modemux),
	पूर्ण, अणु
		.name = "ssp1_48_51_grp",
		.pins = ssp1_pins[2],
		.npins = ARRAY_SIZE(ssp1_pins[2]),
		.modemuxs = ssp1_48_51_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp1_48_51_modemux),
	पूर्ण, अणु
		.name = "ssp1_65_68_grp",
		.pins = ssp1_pins[3],
		.npins = ARRAY_SIZE(ssp1_pins[3]),
		.modemuxs = ssp1_65_68_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp1_65_68_modemux),
	पूर्ण, अणु
		.name = "ssp1_94_97_grp",
		.pins = ssp1_pins[4],
		.npins = ARRAY_SIZE(ssp1_pins[4]),
		.modemuxs = ssp1_94_97_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp1_94_97_modemux),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp1_grps[] = अणु "ssp1_17_20_grp", "ssp1_36_39_grp",
	"ssp1_48_51_grp", "ssp1_65_68_grp", "ssp1_94_97_grp"
पूर्ण;
अटल काष्ठा spear_function ssp1_function = अणु
	.name = "ssp1",
	.groups = ssp1_grps,
	.ngroups = ARRAY_SIZE(ssp1_grps),
पूर्ण;

/* Pad multiplexing क्रम SSP2 device */
अटल स्थिर अचिन्हित ssp2_pins[][2] = अणु अणु 13, 16 पूर्ण, अणु 32, 35 पूर्ण, अणु 44, 47 पूर्ण,
	अणु 61, 64 पूर्ण, अणु 90, 93 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg ssp2_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp2_ext_13_16_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_13_14_MASK | PMX_PL_15_16_MASK,
		.val = PMX_SSP2_PL_13_14_15_16_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP2_PORT_SEL_MASK,
		.val = PMX_SSP2_PORT_13_TO_16_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp2_ext_32_35_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK | PMX_GPIO_PIN4_MASK |
			PMX_GPIO_PIN5_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_30_39_REG,
		.mask = PMX_PL_32_33_MASK | PMX_PL_34_MASK | PMX_PL_35_MASK,
		.val = PMX_SSP2_PL_32_33_VAL | PMX_SSP2_PL_34_VAL |
			PMX_SSP2_PL_35_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP2_PORT_SEL_MASK,
		.val = PMX_SSP2_PORT_32_TO_35_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp2_ext_44_47_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_40_49_REG,
		.mask = PMX_PL_44_45_MASK | PMX_PL_46_47_MASK,
		.val = PMX_SSP2_PL_44_45_VAL | PMX_SSP2_PL_46_47_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP2_PORT_SEL_MASK,
		.val = PMX_SSP2_PORT_44_TO_47_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp2_ext_61_64_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_60_69_REG,
		.mask = PMX_PL_61_TO_64_MASK,
		.val = PMX_SSP2_PL_61_TO_64_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP2_PORT_SEL_MASK,
		.val = PMX_SSP2_PORT_61_TO_64_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg ssp2_ext_90_93_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_90_91_MASK | PMX_PL_92_93_MASK,
		.val = PMX_SSP2_PL_90_91_VAL | PMX_SSP2_PL_92_93_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_SSP2_PORT_SEL_MASK,
		.val = PMX_SSP2_PORT_90_TO_93_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp2_13_16_modemux[] = अणु
	अणु
		.modes = AUTO_NET_SMII_MODE | EXTENDED_MODE,
		.muxregs = ssp2_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp2_muxreg),
	पूर्ण, अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp2_ext_13_16_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp2_ext_13_16_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp2_32_35_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp2_ext_32_35_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp2_ext_32_35_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp2_44_47_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp2_ext_44_47_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp2_ext_44_47_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp2_61_64_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp2_ext_61_64_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp2_ext_61_64_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp2_90_93_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = ssp2_ext_90_93_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp2_ext_90_93_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup ssp2_pingroup[] = अणु
	अणु
		.name = "ssp2_13_16_grp",
		.pins = ssp2_pins[0],
		.npins = ARRAY_SIZE(ssp2_pins[0]),
		.modemuxs = ssp2_13_16_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp2_13_16_modemux),
	पूर्ण, अणु
		.name = "ssp2_32_35_grp",
		.pins = ssp2_pins[1],
		.npins = ARRAY_SIZE(ssp2_pins[1]),
		.modemuxs = ssp2_32_35_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp2_32_35_modemux),
	पूर्ण, अणु
		.name = "ssp2_44_47_grp",
		.pins = ssp2_pins[2],
		.npins = ARRAY_SIZE(ssp2_pins[2]),
		.modemuxs = ssp2_44_47_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp2_44_47_modemux),
	पूर्ण, अणु
		.name = "ssp2_61_64_grp",
		.pins = ssp2_pins[3],
		.npins = ARRAY_SIZE(ssp2_pins[3]),
		.modemuxs = ssp2_61_64_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp2_61_64_modemux),
	पूर्ण, अणु
		.name = "ssp2_90_93_grp",
		.pins = ssp2_pins[4],
		.npins = ARRAY_SIZE(ssp2_pins[4]),
		.modemuxs = ssp2_90_93_modemux,
		.nmodemuxs = ARRAY_SIZE(ssp2_90_93_modemux),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp2_grps[] = अणु "ssp2_13_16_grp", "ssp2_32_35_grp",
	"ssp2_44_47_grp", "ssp2_61_64_grp", "ssp2_90_93_grp" पूर्ण;
अटल काष्ठा spear_function ssp2_function = अणु
	.name = "ssp2",
	.groups = ssp2_grps,
	.ngroups = ARRAY_SIZE(ssp2_grps),
पूर्ण;

/* Pad multiplexing क्रम cadence mii2 as mii device */
अटल स्थिर अचिन्हित mii2_pins[] = अणु 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97 पूर्ण;
अटल काष्ठा spear_muxreg mii2_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_80_89_REG,
		.mask = PMX_PL_80_TO_85_MASK | PMX_PL_86_87_MASK |
			PMX_PL_88_89_MASK,
		.val = PMX_MII2_PL_80_TO_85_VAL | PMX_MII2_PL_86_87_VAL |
			PMX_MII2_PL_88_89_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_90_91_MASK | PMX_PL_92_93_MASK |
			PMX_PL_94_95_MASK | PMX_PL_96_97_MASK,
		.val = PMX_MII2_PL_90_91_VAL | PMX_MII2_PL_92_93_VAL |
			PMX_MII2_PL_94_95_VAL | PMX_MII2_PL_96_97_VAL,
	पूर्ण, अणु
		.reg = EXT_CTRL_REG,
		.mask = (MAC_MODE_MASK << MAC2_MODE_SHIFT) |
			(MAC_MODE_MASK << MAC1_MODE_SHIFT) |
			MII_MDIO_MASK,
		.val = (MAC_MODE_MII << MAC2_MODE_SHIFT) |
			(MAC_MODE_MII << MAC1_MODE_SHIFT) |
			MII_MDIO_81_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux mii2_modemux[] = अणु
	अणु
		.modes = EXTENDED_MODE,
		.muxregs = mii2_muxreg,
		.nmuxregs = ARRAY_SIZE(mii2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup mii2_pingroup = अणु
	.name = "mii2_grp",
	.pins = mii2_pins,
	.npins = ARRAY_SIZE(mii2_pins),
	.modemuxs = mii2_modemux,
	.nmodemuxs = ARRAY_SIZE(mii2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर mii2_grps[] = अणु "mii2_grp" पूर्ण;
अटल काष्ठा spear_function mii2_function = अणु
	.name = "mii2",
	.groups = mii2_grps,
	.ngroups = ARRAY_SIZE(mii2_grps),
पूर्ण;

/* Pad multiplexing क्रम cadence mii 1_2 as smii or rmii device */
अटल स्थिर अचिन्हित rmii0_1_pins[] = अणु 10, 11, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27 पूर्ण;
अटल स्थिर अचिन्हित smii0_1_pins[] = अणु 10, 11, 21, 22, 23, 24, 25, 26, 27 पूर्ण;
अटल काष्ठा spear_muxreg mii0_1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg smii0_1_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_10_11_MASK,
		.val = PMX_SMII_PL_10_11_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_21_TO_27_MASK,
		.val = PMX_SMII_PL_21_TO_27_VAL,
	पूर्ण, अणु
		.reg = EXT_CTRL_REG,
		.mask = (MAC_MODE_MASK << MAC2_MODE_SHIFT) |
			(MAC_MODE_MASK << MAC1_MODE_SHIFT) |
			MII_MDIO_MASK,
		.val = (MAC_MODE_SMII << MAC2_MODE_SHIFT)
			| (MAC_MODE_SMII << MAC1_MODE_SHIFT)
			| MII_MDIO_10_11_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg rmii0_1_ext_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_10_11_MASK | PMX_PL_13_14_MASK |
			PMX_PL_15_16_MASK | PMX_PL_17_18_MASK | PMX_PL_19_MASK,
		.val = PMX_RMII_PL_10_11_VAL | PMX_RMII_PL_13_14_VAL |
			PMX_RMII_PL_15_16_VAL | PMX_RMII_PL_17_18_VAL |
			PMX_RMII_PL_19_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_20_MASK | PMX_PL_21_TO_27_MASK,
		.val = PMX_RMII_PL_20_VAL | PMX_RMII_PL_21_TO_27_VAL,
	पूर्ण, अणु
		.reg = EXT_CTRL_REG,
		.mask = (MAC_MODE_MASK << MAC2_MODE_SHIFT) |
			(MAC_MODE_MASK << MAC1_MODE_SHIFT) |
			MII_MDIO_MASK,
		.val = (MAC_MODE_RMII << MAC2_MODE_SHIFT)
			| (MAC_MODE_RMII << MAC1_MODE_SHIFT)
			| MII_MDIO_10_11_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux mii0_1_modemux[][2] = अणु
	अणु
		/* configure as smii */
		अणु
			.modes = AUTO_NET_SMII_MODE | AUTO_EXP_MODE |
				SMALL_PRINTERS_MODE | EXTENDED_MODE,
			.muxregs = mii0_1_muxreg,
			.nmuxregs = ARRAY_SIZE(mii0_1_muxreg),
		पूर्ण, अणु
			.modes = EXTENDED_MODE,
			.muxregs = smii0_1_ext_muxreg,
			.nmuxregs = ARRAY_SIZE(smii0_1_ext_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* configure as rmii */
		अणु
			.modes = AUTO_NET_SMII_MODE | AUTO_EXP_MODE |
				SMALL_PRINTERS_MODE | EXTENDED_MODE,
			.muxregs = mii0_1_muxreg,
			.nmuxregs = ARRAY_SIZE(mii0_1_muxreg),
		पूर्ण, अणु
			.modes = EXTENDED_MODE,
			.muxregs = rmii0_1_ext_muxreg,
			.nmuxregs = ARRAY_SIZE(rmii0_1_ext_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup mii0_1_pingroup[] = अणु
	अणु
		.name = "smii0_1_grp",
		.pins = smii0_1_pins,
		.npins = ARRAY_SIZE(smii0_1_pins),
		.modemuxs = mii0_1_modemux[0],
		.nmodemuxs = ARRAY_SIZE(mii0_1_modemux[0]),
	पूर्ण, अणु
		.name = "rmii0_1_grp",
		.pins = rmii0_1_pins,
		.npins = ARRAY_SIZE(rmii0_1_pins),
		.modemuxs = mii0_1_modemux[1],
		.nmodemuxs = ARRAY_SIZE(mii0_1_modemux[1]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर mii0_1_grps[] = अणु "smii0_1_grp", "rmii0_1_grp" पूर्ण;
अटल काष्ठा spear_function mii0_1_function = अणु
	.name = "mii0_1",
	.groups = mii0_1_grps,
	.ngroups = ARRAY_SIZE(mii0_1_grps),
पूर्ण;

/* Pad multiplexing क्रम i2c1 device */
अटल स्थिर अचिन्हित i2c1_pins[][2] = अणु अणु 8, 9 पूर्ण, अणु 98, 99 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg i2c1_ext_8_9_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_8_9_MASK,
		.val = PMX_I2C1_PL_8_9_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C1_PORT_SEL_MASK,
		.val = PMX_I2C1_PORT_8_9_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg i2c1_ext_98_99_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_98_MASK | PMX_PL_99_MASK,
		.val = PMX_I2C1_PL_98_VAL | PMX_I2C1_PL_99_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C1_PORT_SEL_MASK,
		.val = PMX_I2C1_PORT_98_99_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c1_modemux[][1] = अणु
	अणु
		/* Select संकेतs on pins 8-9 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c1_ext_8_9_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c1_ext_8_9_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 98-99 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c1_ext_98_99_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c1_ext_98_99_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c1_pingroup[] = अणु
	अणु
		.name = "i2c1_8_9_grp",
		.pins = i2c1_pins[0],
		.npins = ARRAY_SIZE(i2c1_pins[0]),
		.modemuxs = i2c1_modemux[0],
		.nmodemuxs = ARRAY_SIZE(i2c1_modemux[0]),
	पूर्ण, अणु
		.name = "i2c1_98_99_grp",
		.pins = i2c1_pins[1],
		.npins = ARRAY_SIZE(i2c1_pins[1]),
		.modemuxs = i2c1_modemux[1],
		.nmodemuxs = ARRAY_SIZE(i2c1_modemux[1]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c1_grps[] = अणु "i2c1_8_9_grp", "i2c1_98_99_grp" पूर्ण;
अटल काष्ठा spear_function i2c1_function = अणु
	.name = "i2c1",
	.groups = i2c1_grps,
	.ngroups = ARRAY_SIZE(i2c1_grps),
पूर्ण;

/* Pad multiplexing क्रम i2c2 device */
अटल स्थिर अचिन्हित i2c2_pins[][2] = अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण, अणु 19, 20 पूर्ण,
	अणु 75, 76 पूर्ण, अणु 96, 97 पूर्ण पूर्ण;
अटल काष्ठा spear_muxreg i2c2_ext_0_1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_FIRDA_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_0_1_MASK,
		.val = PMX_I2C2_PL_0_1_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C2_PORT_SEL_MASK,
		.val = PMX_I2C2_PORT_0_1_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg i2c2_ext_2_3_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_0_9_REG,
		.mask = PMX_PL_2_3_MASK,
		.val = PMX_I2C2_PL_2_3_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C2_PORT_SEL_MASK,
		.val = PMX_I2C2_PORT_2_3_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg i2c2_ext_19_20_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_10_19_REG,
		.mask = PMX_PL_19_MASK,
		.val = PMX_I2C2_PL_19_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_PAD_20_29_REG,
		.mask = PMX_PL_20_MASK,
		.val = PMX_I2C2_PL_20_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C2_PORT_SEL_MASK,
		.val = PMX_I2C2_PORT_19_20_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg i2c2_ext_75_76_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_70_79_REG,
		.mask = PMX_PL_75_76_MASK,
		.val = PMX_I2C2_PL_75_76_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C2_PORT_SEL_MASK,
		.val = PMX_I2C2_PORT_75_76_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_muxreg i2c2_ext_96_97_muxreg[] = अणु
	अणु
		.reg = IP_SEL_PAD_90_99_REG,
		.mask = PMX_PL_96_97_MASK,
		.val = PMX_I2C2_PL_96_97_VAL,
	पूर्ण, अणु
		.reg = IP_SEL_MIX_PAD_REG,
		.mask = PMX_I2C2_PORT_SEL_MASK,
		.val = PMX_I2C2_PORT_96_97_VAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c2_modemux[][1] = अणु
	अणु
		/* Select संकेतs on pins 0_1 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c2_ext_0_1_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c2_ext_0_1_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 2_3 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c2_ext_2_3_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c2_ext_2_3_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 19_20 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c2_ext_19_20_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c2_ext_19_20_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 75_76 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c2_ext_75_76_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c2_ext_75_76_muxreg),
		पूर्ण,
	पूर्ण, अणु
		/* Select संकेतs on pins 96_97 */
		अणु
			.modes = EXTENDED_MODE,
			.muxregs = i2c2_ext_96_97_muxreg,
			.nmuxregs = ARRAY_SIZE(i2c2_ext_96_97_muxreg),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c2_pingroup[] = अणु
	अणु
		.name = "i2c2_0_1_grp",
		.pins = i2c2_pins[0],
		.npins = ARRAY_SIZE(i2c2_pins[0]),
		.modemuxs = i2c2_modemux[0],
		.nmodemuxs = ARRAY_SIZE(i2c2_modemux[0]),
	पूर्ण, अणु
		.name = "i2c2_2_3_grp",
		.pins = i2c2_pins[1],
		.npins = ARRAY_SIZE(i2c2_pins[1]),
		.modemuxs = i2c2_modemux[1],
		.nmodemuxs = ARRAY_SIZE(i2c2_modemux[1]),
	पूर्ण, अणु
		.name = "i2c2_19_20_grp",
		.pins = i2c2_pins[2],
		.npins = ARRAY_SIZE(i2c2_pins[2]),
		.modemuxs = i2c2_modemux[2],
		.nmodemuxs = ARRAY_SIZE(i2c2_modemux[2]),
	पूर्ण, अणु
		.name = "i2c2_75_76_grp",
		.pins = i2c2_pins[3],
		.npins = ARRAY_SIZE(i2c2_pins[3]),
		.modemuxs = i2c2_modemux[3],
		.nmodemuxs = ARRAY_SIZE(i2c2_modemux[3]),
	पूर्ण, अणु
		.name = "i2c2_96_97_grp",
		.pins = i2c2_pins[4],
		.npins = ARRAY_SIZE(i2c2_pins[4]),
		.modemuxs = i2c2_modemux[4],
		.nmodemuxs = ARRAY_SIZE(i2c2_modemux[4]),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c2_grps[] = अणु "i2c2_0_1_grp", "i2c2_2_3_grp",
	"i2c2_19_20_grp", "i2c2_75_76_grp", "i2c2_96_97_grp" पूर्ण;
अटल काष्ठा spear_function i2c2_function = अणु
	.name = "i2c2",
	.groups = i2c2_grps,
	.ngroups = ARRAY_SIZE(i2c2_grps),
पूर्ण;

/* pingroups */
अटल काष्ठा spear_pingroup *spear320_pingroups[] = अणु
	SPEAR3XX_COMMON_PINGROUPS,
	&clcd_pingroup,
	&emi_pingroup,
	&fsmc_8bit_pingroup,
	&fsmc_16bit_pingroup,
	&spp_pingroup,
	&sdhci_led_pingroup,
	&sdhci_pingroup[0],
	&sdhci_pingroup[1],
	&i2s_pingroup,
	&uart1_pingroup,
	&uart1_modem_pingroup[0],
	&uart1_modem_pingroup[1],
	&uart1_modem_pingroup[2],
	&uart1_modem_pingroup[3],
	&uart2_pingroup,
	&uart3_pingroup[0],
	&uart3_pingroup[1],
	&uart3_pingroup[2],
	&uart3_pingroup[3],
	&uart3_pingroup[4],
	&uart3_pingroup[5],
	&uart3_pingroup[6],
	&uart4_pingroup[0],
	&uart4_pingroup[1],
	&uart4_pingroup[2],
	&uart4_pingroup[3],
	&uart4_pingroup[4],
	&uart4_pingroup[5],
	&uart5_pingroup[0],
	&uart5_pingroup[1],
	&uart5_pingroup[2],
	&uart5_pingroup[3],
	&uart6_pingroup[0],
	&uart6_pingroup[1],
	&rs485_pingroup,
	&touchscreen_pingroup,
	&can0_pingroup,
	&can1_pingroup,
	&pwm0_1_pingroup[0],
	&pwm0_1_pingroup[1],
	&pwm0_1_pingroup[2],
	&pwm0_1_pingroup[3],
	&pwm0_1_pingroup[4],
	&pwm0_1_pingroup[5],
	&pwm0_1_pingroup[6],
	&pwm2_pingroup[0],
	&pwm2_pingroup[1],
	&pwm2_pingroup[2],
	&pwm2_pingroup[3],
	&pwm2_pingroup[4],
	&pwm2_pingroup[5],
	&pwm2_pingroup[6],
	&pwm3_pingroup[0],
	&pwm3_pingroup[1],
	&pwm3_pingroup[2],
	&pwm3_pingroup[3],
	&pwm3_pingroup[4],
	&pwm3_pingroup[5],
	&ssp1_pingroup[0],
	&ssp1_pingroup[1],
	&ssp1_pingroup[2],
	&ssp1_pingroup[3],
	&ssp1_pingroup[4],
	&ssp2_pingroup[0],
	&ssp2_pingroup[1],
	&ssp2_pingroup[2],
	&ssp2_pingroup[3],
	&ssp2_pingroup[4],
	&mii2_pingroup,
	&mii0_1_pingroup[0],
	&mii0_1_pingroup[1],
	&i2c1_pingroup[0],
	&i2c1_pingroup[1],
	&i2c2_pingroup[0],
	&i2c2_pingroup[1],
	&i2c2_pingroup[2],
	&i2c2_pingroup[3],
	&i2c2_pingroup[4],
पूर्ण;

/* functions */
अटल काष्ठा spear_function *spear320_functions[] = अणु
	SPEAR3XX_COMMON_FUNCTIONS,
	&clcd_function,
	&emi_function,
	&fsmc_function,
	&spp_function,
	&sdhci_function,
	&i2s_function,
	&uart1_function,
	&uart1_modem_function,
	&uart2_function,
	&uart3_function,
	&uart4_function,
	&uart5_function,
	&uart6_function,
	&rs485_function,
	&touchscreen_function,
	&can0_function,
	&can1_function,
	&pwm0_1_function,
	&pwm2_function,
	&pwm3_function,
	&ssp1_function,
	&ssp2_function,
	&mii2_function,
	&mii0_1_function,
	&i2c1_function,
	&i2c2_function,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spear320_pinctrl_of_match[] = अणु
	अणु
		.compatible = "st,spear320-pinmux",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक spear320_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	spear3xx_machdata.groups = spear320_pingroups;
	spear3xx_machdata.ngroups = ARRAY_SIZE(spear320_pingroups);
	spear3xx_machdata.functions = spear320_functions;
	spear3xx_machdata.nfunctions = ARRAY_SIZE(spear320_functions);

	spear3xx_machdata.modes_supported = true;
	spear3xx_machdata.pmx_modes = spear320_pmx_modes;
	spear3xx_machdata.npmx_modes = ARRAY_SIZE(spear320_pmx_modes);

	pmx_init_addr(&spear3xx_machdata, PMX_CONFIG_REG);
	pmx_init_gpio_pingroup_addr(spear3xx_machdata.gpio_pingroups,
			spear3xx_machdata.ngpio_pingroups, PMX_CONFIG_REG);

	वापस spear_pinctrl_probe(pdev, &spear3xx_machdata);
पूर्ण

अटल काष्ठा platक्रमm_driver spear320_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = spear320_pinctrl_of_match,
	पूर्ण,
	.probe = spear320_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init spear320_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spear320_pinctrl_driver);
पूर्ण
arch_initcall(spear320_pinctrl_init);
