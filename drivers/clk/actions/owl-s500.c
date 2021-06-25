<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi Owl S500 SoC घड़ी driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Copyright (c) 2018 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 *
 * Copyright (c) 2018 LSI-TEC - Caninos Loucos
 * Author: Edgar Bernardi Righi <edgar.righi@lsitec.org.br>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "owl-common.h"
#समावेश "owl-composite.h"
#समावेश "owl-divider.h"
#समावेश "owl-factor.h"
#समावेश "owl-fixed-factor.h"
#समावेश "owl-gate.h"
#समावेश "owl-mux.h"
#समावेश "owl-pll.h"
#समावेश "owl-reset.h"

#समावेश <dt-bindings/घड़ी/actions,s500-cmu.h>
#समावेश <dt-bindings/reset/actions,s500-reset.h>

#घोषणा CMU_COREPLL			(0x0000)
#घोषणा CMU_DEVPLL			(0x0004)
#घोषणा CMU_DDRPLL			(0x0008)
#घोषणा CMU_न_अंकDPLL			(0x000C)
#घोषणा CMU_DISPLAYPLL			(0x0010)
#घोषणा CMU_AUDIOPLL			(0x0014)
#घोषणा CMU_TVOUTPLL			(0x0018)
#घोषणा CMU_BUSCLK			(0x001C)
#घोषणा CMU_SENSORCLK			(0x0020)
#घोषणा CMU_LCDCLK			(0x0024)
#घोषणा CMU_DSICLK			(0x0028)
#घोषणा CMU_CSICLK			(0x002C)
#घोषणा CMU_DECLK			(0x0030)
#घोषणा CMU_BISPCLK			(0x0034)
#घोषणा CMU_BUSCLK1			(0x0038)
#घोषणा CMU_VDECLK			(0x0040)
#घोषणा CMU_VCECLK			(0x0044)
#घोषणा CMU_न_अंकDCCLK			(0x004C)
#घोषणा CMU_SD0CLK			(0x0050)
#घोषणा CMU_SD1CLK			(0x0054)
#घोषणा CMU_SD2CLK			(0x0058)
#घोषणा CMU_UART0CLK			(0x005C)
#घोषणा CMU_UART1CLK			(0x0060)
#घोषणा CMU_UART2CLK			(0x0064)
#घोषणा CMU_PWM4CLK			(0x0068)
#घोषणा CMU_PWM5CLK			(0x006C)
#घोषणा CMU_PWM0CLK			(0x0070)
#घोषणा CMU_PWM1CLK			(0x0074)
#घोषणा CMU_PWM2CLK			(0x0078)
#घोषणा CMU_PWM3CLK			(0x007C)
#घोषणा CMU_USBPLL			(0x0080)
#घोषणा CMU_ETHERNETPLL			(0x0084)
#घोषणा CMU_CVBSPLL			(0x0088)
#घोषणा CMU_LENSCLK			(0x008C)
#घोषणा CMU_GPU3DCLK			(0x0090)
#घोषणा CMU_CORECTL			(0x009C)
#घोषणा CMU_DEVCLKEN0			(0x00A0)
#घोषणा CMU_DEVCLKEN1			(0x00A4)
#घोषणा CMU_DEVRST0			(0x00A8)
#घोषणा CMU_DEVRST1			(0x00AC)
#घोषणा CMU_UART3CLK			(0x00B0)
#घोषणा CMU_UART4CLK			(0x00B4)
#घोषणा CMU_UART5CLK			(0x00B8)
#घोषणा CMU_UART6CLK			(0x00BC)
#घोषणा CMU_SSCLK			(0x00C0)
#घोषणा CMU_DIGITALDEBUG		(0x00D0)
#घोषणा CMU_ANALOGDEBUG			(0x00D4)
#घोषणा CMU_COREPLLDEBUG		(0x00D8)
#घोषणा CMU_DEVPLLDEBUG			(0x00DC)
#घोषणा CMU_DDRPLLDEBUG			(0x00E0)
#घोषणा CMU_न_अंकDPLLDEBUG		(0x00E4)
#घोषणा CMU_DISPLAYPLLDEBUG		(0x00E8)
#घोषणा CMU_TVOUTPLLDEBUG		(0x00EC)
#घोषणा CMU_DEEPCOLORPLLDEBUG		(0x00F4)
#घोषणा CMU_AUDIOPLL_ETHPLLDEBUG	(0x00F8)
#घोषणा CMU_CVBSPLLDEBUG		(0x00FC)

#घोषणा OWL_S500_COREPLL_DELAY		(150)
#घोषणा OWL_S500_DDRPLL_DELAY		(63)
#घोषणा OWL_S500_DEVPLL_DELAY		(28)
#घोषणा OWL_S500_न_अंकDPLL_DELAY		(44)
#घोषणा OWL_S500_DISPLAYPLL_DELAY	(57)
#घोषणा OWL_S500_ETHERNETPLL_DELAY	(25)
#घोषणा OWL_S500_AUDIOPLL_DELAY		(100)

अटल स्थिर काष्ठा clk_pll_table clk_audio_pll_table[] = अणु
	अणु 0, 45158400 पूर्ण, अणु 1, 49152000 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

/* pll घड़ीs */
अटल OWL_PLL_NO_PARENT_DELAY(ethernet_pll_clk, "ethernet_pll_clk", CMU_ETHERNETPLL, 500000000, 0, 0, 0, 0, 0, OWL_S500_ETHERNETPLL_DELAY, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT_DELAY(core_pll_clk, "core_pll_clk", CMU_COREPLL, 12000000, 9, 0, 8, 4, 134, OWL_S500_COREPLL_DELAY, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT_DELAY(ddr_pll_clk, "ddr_pll_clk", CMU_DDRPLL, 12000000, 8, 0, 8, 1, 67, OWL_S500_DDRPLL_DELAY, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT_DELAY(nand_pll_clk, "nand_pll_clk", CMU_न_अंकDPLL, 6000000, 8, 0, 7, 2, 86, OWL_S500_न_अंकDPLL_DELAY, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT_DELAY(display_pll_clk, "display_pll_clk", CMU_DISPLAYPLL, 6000000, 8, 0, 8, 2, 126, OWL_S500_DISPLAYPLL_DELAY, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT_DELAY(dev_pll_clk, "dev_pll_clk", CMU_DEVPLL, 6000000, 8, 0, 7, 8, 126, OWL_S500_DEVPLL_DELAY, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT_DELAY(audio_pll_clk, "audio_pll_clk", CMU_AUDIOPLL, 0, 4, 0, 1, 0, 0, OWL_S500_AUDIOPLL_DELAY, clk_audio_pll_table, CLK_IGNORE_UNUSED);

अटल स्थिर अक्षर * स्थिर dev_clk_mux_p[] = अणु "hosc", "dev_pll_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर bisp_clk_mux_p[] = अणु "display_pll_clk", "dev_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर sensor_clk_mux_p[] = अणु "hosc", "bisp_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर sd_clk_mux_p[] = अणु "dev_clk", "nand_pll_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm_clk_mux_p[] = अणु "losc", "hosc" पूर्ण;
अटल स्थिर अक्षर * स्थिर ahbpreभाग_clk_mux_p[] = अणु "dev_clk", "display_pll_clk", "nand_pll_clk", "ddr_pll_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart_clk_mux_p[] = अणु "hosc", "dev_pll_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर de_clk_mux_p[] = अणु "display_pll_clk", "dev_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s_clk_mux_p[] = अणु "audio_pll_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर hde_clk_mux_p[] = अणु "dev_clk", "display_pll_clk", "nand_pll_clk", "ddr_pll_clk" पूर्ण;
अटल स्थिर अक्षर * स्थिर nand_clk_mux_p[] = अणु "nand_pll_clk", "display_pll_clk", "dev_clk", "ddr_pll_clk" पूर्ण;

अटल काष्ठा clk_factor_table sd_factor_table[] = अणु
	/* bit0 ~ 4 */
	अणु 0, 1, 1 पूर्ण, अणु 1, 1, 2 पूर्ण, अणु 2, 1, 3 पूर्ण, अणु 3, 1, 4 पूर्ण,
	अणु 4, 1, 5 पूर्ण, अणु 5, 1, 6 पूर्ण, अणु 6, 1, 7 पूर्ण, अणु 7, 1, 8 पूर्ण,
	अणु 8, 1, 9 पूर्ण, अणु 9, 1, 10 पूर्ण, अणु 10, 1, 11 पूर्ण, अणु 11, 1, 12 पूर्ण,
	अणु 12, 1, 13 पूर्ण, अणु 13, 1, 14 पूर्ण, अणु 14, 1, 15 पूर्ण, अणु 15, 1, 16 पूर्ण,
	अणु 16, 1, 17 पूर्ण, अणु 17, 1, 18 पूर्ण, अणु 18, 1, 19 पूर्ण, अणु 19, 1, 20 पूर्ण,
	अणु 20, 1, 21 पूर्ण, अणु 21, 1, 22 पूर्ण, अणु 22, 1, 23 पूर्ण, अणु 23, 1, 24 पूर्ण,
	अणु 24, 1, 25 पूर्ण, अणु 25, 1, 26 पूर्ण, अणु 26, 1, 27 पूर्ण, अणु 27, 1, 28 पूर्ण,
	अणु 28, 1, 29 पूर्ण, अणु 29, 1, 30 पूर्ण, अणु 30, 1, 31 पूर्ण, अणु 31, 1, 32 पूर्ण,

	/* bit8: /128 */
	अणु 256, 1, 1 * 128 पूर्ण, अणु 257, 1, 2 * 128 पूर्ण, अणु 258, 1, 3 * 128 पूर्ण, अणु 259, 1, 4 * 128 पूर्ण,
	अणु 260, 1, 5 * 128 पूर्ण, अणु 261, 1, 6 * 128 पूर्ण, अणु 262, 1, 7 * 128 पूर्ण, अणु 263, 1, 8 * 128 पूर्ण,
	अणु 264, 1, 9 * 128 पूर्ण, अणु 265, 1, 10 * 128 पूर्ण, अणु 266, 1, 11 * 128 पूर्ण, अणु 267, 1, 12 * 128 पूर्ण,
	अणु 268, 1, 13 * 128 पूर्ण, अणु 269, 1, 14 * 128 पूर्ण, अणु 270, 1, 15 * 128 पूर्ण, अणु 271, 1, 16 * 128 पूर्ण,
	अणु 272, 1, 17 * 128 पूर्ण, अणु 273, 1, 18 * 128 पूर्ण, अणु 274, 1, 19 * 128 पूर्ण, अणु 275, 1, 20 * 128 पूर्ण,
	अणु 276, 1, 21 * 128 पूर्ण, अणु 277, 1, 22 * 128 पूर्ण, अणु 278, 1, 23 * 128 पूर्ण, अणु 279, 1, 24 * 128 पूर्ण,
	अणु 280, 1, 25 * 128 पूर्ण, अणु 281, 1, 26 * 128 पूर्ण, अणु 282, 1, 27 * 128 पूर्ण, अणु 283, 1, 28 * 128 पूर्ण,
	अणु 284, 1, 29 * 128 पूर्ण, अणु 285, 1, 30 * 128 पूर्ण, अणु 286, 1, 31 * 128 पूर्ण, अणु 287, 1, 32 * 128 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table bisp_factor_table[] = अणु
	अणु 0, 1, 1 पूर्ण, अणु 1, 1, 2 पूर्ण, अणु 2, 1, 3 पूर्ण, अणु 3, 1, 4 पूर्ण,
	अणु 4, 1, 5 पूर्ण, अणु 5, 1, 6 पूर्ण, अणु 6, 1, 7 पूर्ण, अणु 7, 1, 8 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table ahb_factor_table[] = अणु
	अणु 1, 1, 2 पूर्ण, अणु 2, 1, 3 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable rmii_ref_भाग_प्रकारable[] = अणु
	अणु 0, 4 पूर्ण, अणु 1, 10 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable i2s_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 6 पूर्ण, अणु 5, 8 पूर्ण, अणु 6, 12 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 8, 24 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable nand_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 6 पूर्ण,
	अणु 4, 8 पूर्ण, अणु 5, 10 पूर्ण, अणु 6, 12 पूर्ण, अणु 7, 14 पूर्ण,
	अणु 8, 16 पूर्ण, अणु 9, 18 पूर्ण, अणु 10, 20 पूर्ण, अणु 11, 22 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

/* mux घड़ी */
अटल OWL_MUX(dev_clk, "dev_clk", dev_clk_mux_p, CMU_DEVPLL, 12, 1, CLK_SET_RATE_PARENT);
अटल OWL_MUX(ahbpreभाग_clk, "ahbprediv_clk", ahbpreभाग_clk_mux_p, CMU_BUSCLK1, 8, 3, CLK_SET_RATE_PARENT);

/* gate घड़ीs */
अटल OWL_GATE(gpio_clk, "gpio_clk", "apb_clk", CMU_DEVCLKEN0, 18, 0, 0);
अटल OWL_GATE(dmac_clk, "dmac_clk", "h_clk", CMU_DEVCLKEN0, 1, 0, 0);
अटल OWL_GATE(spi0_clk, "spi0_clk", "ahb_clk", CMU_DEVCLKEN1, 10, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(spi1_clk, "spi1_clk", "ahb_clk", CMU_DEVCLKEN1, 11, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(spi2_clk, "spi2_clk", "ahb_clk", CMU_DEVCLKEN1, 12, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(spi3_clk, "spi3_clk", "ahb_clk", CMU_DEVCLKEN1, 13, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(समयr_clk, "timer_clk", "hosc", CMU_DEVCLKEN1, 27, 0, 0);
अटल OWL_GATE(hdmi_clk, "hdmi_clk", "hosc", CMU_DEVCLKEN1, 3, 0, 0);

/* भागider घड़ीs */
अटल OWL_DIVIDER(h_clk, "h_clk", "ahbprediv_clk", CMU_BUSCLK1, 12, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(apb_clk, "apb_clk", "ahb_clk", CMU_BUSCLK1, 14, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(rmii_ref_clk, "rmii_ref_clk", "ethernet_pll_clk", CMU_ETHERNETPLL, 1, 1, rmii_ref_भाग_प्रकारable, 0, 0);

/* factor घड़ीs */
अटल OWL_FACTOR(ahb_clk, "ahb_clk", "h_clk", CMU_BUSCLK1, 2, 2, ahb_factor_table, 0, 0);
अटल OWL_FACTOR(de1_clk, "de_clk1", "de_clk", CMU_DECLK, 0, 3, bisp_factor_table, 0, 0);
अटल OWL_FACTOR(de2_clk, "de_clk2", "de_clk", CMU_DECLK, 4, 3, bisp_factor_table, 0, 0);

/* composite घड़ीs */
अटल OWL_COMP_FACTOR(vce_clk, "vce_clk", hde_clk_mux_p,
			OWL_MUX_HW(CMU_VCECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 26, 0),
			OWL_FACTOR_HW(CMU_VCECLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(vde_clk, "vde_clk", hde_clk_mux_p,
			OWL_MUX_HW(CMU_VDECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 25, 0),
			OWL_FACTOR_HW(CMU_VDECLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(bisp_clk, "bisp_clk", bisp_clk_mux_p,
			OWL_MUX_HW(CMU_BISPCLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 14, 0),
			OWL_FACTOR_HW(CMU_BISPCLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(sensor0_clk, "sensor0_clk", sensor_clk_mux_p,
			OWL_MUX_HW(CMU_SENSORCLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 14, 0),
			OWL_FACTOR_HW(CMU_SENSORCLK, 0, 3, 0, bisp_factor_table),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_FACTOR(sensor1_clk, "sensor1_clk", sensor_clk_mux_p,
			OWL_MUX_HW(CMU_SENSORCLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 14, 0),
			OWL_FACTOR_HW(CMU_SENSORCLK, 8, 3, 0, bisp_factor_table),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_FACTOR(sd0_clk, "sd0_clk", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD0CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 5, 0),
			OWL_FACTOR_HW(CMU_SD0CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_FACTOR(sd1_clk, "sd1_clk", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD1CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 6, 0),
			OWL_FACTOR_HW(CMU_SD1CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_FACTOR(sd2_clk, "sd2_clk", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD2CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 7, 0),
			OWL_FACTOR_HW(CMU_SD2CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_DIV(pwm0_clk, "pwm0_clk", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM0CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 23, 0),
			OWL_DIVIDER_HW(CMU_PWM0CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(pwm1_clk, "pwm1_clk", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM1CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 24, 0),
			OWL_DIVIDER_HW(CMU_PWM1CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(pwm2_clk, "pwm2_clk", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM2CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 25, 0),
			OWL_DIVIDER_HW(CMU_PWM2CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(pwm3_clk, "pwm3_clk", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM3CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 26, 0),
			OWL_DIVIDER_HW(CMU_PWM3CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(pwm4_clk, "pwm4_clk", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM4CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 11, 0),
			OWL_DIVIDER_HW(CMU_PWM4CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(pwm5_clk, "pwm5_clk", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM5CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 0, 0),
			OWL_DIVIDER_HW(CMU_PWM5CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_PASS(de_clk, "de_clk", de_clk_mux_p,
			OWL_MUX_HW(CMU_DECLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 8, 0),
			0);

अटल OWL_COMP_FIXED_FACTOR(i2c0_clk, "i2c0_clk", "ethernet_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 14, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c1_clk, "i2c1_clk", "ethernet_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 15, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c2_clk, "i2c2_clk", "ethernet_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 30, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c3_clk, "i2c3_clk", "ethernet_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 31, 0),
			1, 5, 0);

अटल OWL_COMP_DIV(uart0_clk, "uart0_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART0CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 6, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart1_clk, "uart1_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART1CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 7, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart2_clk, "uart2_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART2CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 8, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart3_clk, "uart3_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART3CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 19, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart4_clk, "uart4_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART4CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 20, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart5_clk, "uart5_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART5CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 21, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart6_clk, "uart6_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART6CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 18, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(i2srx_clk, "i2srx_clk", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 21, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 20, 4, 0, i2s_भाग_प्रकारable),
			0);

अटल OWL_COMP_DIV(i2stx_clk, "i2stx_clk", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 20, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 16, 4, 0, i2s_भाग_प्रकारable),
			0);

अटल OWL_COMP_DIV(hdmia_clk, "hdmia_clk", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 22, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 24, 4, 0, i2s_भाग_प्रकारable),
			0);

अटल OWL_COMP_DIV(spdअगर_clk, "spdif_clk", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 23, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 28, 4, 0, i2s_भाग_प्रकारable),
			0);

अटल OWL_COMP_DIV(nand_clk, "nand_clk", nand_clk_mux_p,
			OWL_MUX_HW(CMU_न_अंकDCCLK, 8, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 4, 0),
			OWL_DIVIDER_HW(CMU_न_अंकDCCLK, 0, 3, 0, nand_भाग_प्रकारable),
			CLK_SET_RATE_PARENT);

अटल OWL_COMP_DIV(ecc_clk, "ecc_clk", nand_clk_mux_p,
			OWL_MUX_HW(CMU_न_अंकDCCLK, 8, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 4, 0),
			OWL_DIVIDER_HW(CMU_न_अंकDCCLK, 4, 3, 0, nand_भाग_प्रकारable),
			CLK_SET_RATE_PARENT);

अटल काष्ठा owl_clk_common *s500_clks[] = अणु
	&ethernet_pll_clk.common,
	&core_pll_clk.common,
	&ddr_pll_clk.common,
	&dev_pll_clk.common,
	&nand_pll_clk.common,
	&audio_pll_clk.common,
	&display_pll_clk.common,
	&dev_clk.common,
	&समयr_clk.common,
	&i2c0_clk.common,
	&i2c1_clk.common,
	&i2c2_clk.common,
	&i2c3_clk.common,
	&uart0_clk.common,
	&uart1_clk.common,
	&uart2_clk.common,
	&uart3_clk.common,
	&uart4_clk.common,
	&uart5_clk.common,
	&uart6_clk.common,
	&pwm0_clk.common,
	&pwm1_clk.common,
	&pwm2_clk.common,
	&pwm3_clk.common,
	&pwm4_clk.common,
	&pwm5_clk.common,
	&sensor0_clk.common,
	&sensor1_clk.common,
	&sd0_clk.common,
	&sd1_clk.common,
	&sd2_clk.common,
	&bisp_clk.common,
	&ahb_clk.common,
	&ahbpreभाग_clk.common,
	&h_clk.common,
	&spi0_clk.common,
	&spi1_clk.common,
	&spi2_clk.common,
	&spi3_clk.common,
	&rmii_ref_clk.common,
	&de_clk.common,
	&de1_clk.common,
	&de2_clk.common,
	&i2srx_clk.common,
	&i2stx_clk.common,
	&hdmia_clk.common,
	&hdmi_clk.common,
	&vce_clk.common,
	&vde_clk.common,
	&spdअगर_clk.common,
	&nand_clk.common,
	&ecc_clk.common,
	&apb_clk.common,
	&dmac_clk.common,
	&gpio_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data s500_hw_clks = अणु
	.hws = अणु
		[CLK_ETHERNET_PLL]	= &ethernet_pll_clk.common.hw,
		[CLK_CORE_PLL]		= &core_pll_clk.common.hw,
		[CLK_DDR_PLL]		= &ddr_pll_clk.common.hw,
		[CLK_न_अंकD_PLL]		= &nand_pll_clk.common.hw,
		[CLK_DISPLAY_PLL]	= &display_pll_clk.common.hw,
		[CLK_DEV_PLL]		= &dev_pll_clk.common.hw,
		[CLK_AUDIO_PLL]		= &audio_pll_clk.common.hw,
		[CLK_TIMER]		= &समयr_clk.common.hw,
		[CLK_DEV]		= &dev_clk.common.hw,
		[CLK_DE]		= &de_clk.common.hw,
		[CLK_DE1]		= &de1_clk.common.hw,
		[CLK_DE2]		= &de2_clk.common.hw,
		[CLK_I2C0]		= &i2c0_clk.common.hw,
		[CLK_I2C1]		= &i2c1_clk.common.hw,
		[CLK_I2C2]		= &i2c2_clk.common.hw,
		[CLK_I2C3]		= &i2c3_clk.common.hw,
		[CLK_I2SRX]		= &i2srx_clk.common.hw,
		[CLK_I2STX]		= &i2stx_clk.common.hw,
		[CLK_UART0]		= &uart0_clk.common.hw,
		[CLK_UART1]		= &uart1_clk.common.hw,
		[CLK_UART2]		= &uart2_clk.common.hw,
		[CLK_UART3]		= &uart3_clk.common.hw,
		[CLK_UART4]		= &uart4_clk.common.hw,
		[CLK_UART5]		= &uart5_clk.common.hw,
		[CLK_UART6]		= &uart6_clk.common.hw,
		[CLK_PWM0]		= &pwm0_clk.common.hw,
		[CLK_PWM1]		= &pwm1_clk.common.hw,
		[CLK_PWM2]		= &pwm2_clk.common.hw,
		[CLK_PWM3]		= &pwm3_clk.common.hw,
		[CLK_PWM4]		= &pwm4_clk.common.hw,
		[CLK_PWM5]		= &pwm5_clk.common.hw,
		[CLK_SENSOR0]		= &sensor0_clk.common.hw,
		[CLK_SENSOR1]		= &sensor1_clk.common.hw,
		[CLK_SD0]		= &sd0_clk.common.hw,
		[CLK_SD1]		= &sd1_clk.common.hw,
		[CLK_SD2]		= &sd2_clk.common.hw,
		[CLK_BISP]		= &bisp_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_SPI1]		= &spi1_clk.common.hw,
		[CLK_SPI2]		= &spi2_clk.common.hw,
		[CLK_SPI3]		= &spi3_clk.common.hw,
		[CLK_AHB]		= &ahb_clk.common.hw,
		[CLK_H]			= &h_clk.common.hw,
		[CLK_AHBPREDIV]		= &ahbpreभाग_clk.common.hw,
		[CLK_RMII_REF]		= &rmii_ref_clk.common.hw,
		[CLK_HDMI_AUDIO]	= &hdmia_clk.common.hw,
		[CLK_HDMI]		= &hdmi_clk.common.hw,
		[CLK_VDE]		= &vde_clk.common.hw,
		[CLK_VCE]		= &vce_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_न_अंकD]		= &nand_clk.common.hw,
		[CLK_ECC]		= &ecc_clk.common.hw,
		[CLK_APB]		= &apb_clk.common.hw,
		[CLK_DMAC]		= &dmac_clk.common.hw,
		[CLK_GPIO]		= &gpio_clk.common.hw,
	पूर्ण,
	.num = CLK_NR_CLKS,
पूर्ण;

अटल स्थिर काष्ठा owl_reset_map s500_resets[] = अणु
	[RESET_DMAC]	= अणु CMU_DEVRST0, BIT(0) पूर्ण,
	[RESET_NORIF]	= अणु CMU_DEVRST0, BIT(1) पूर्ण,
	[RESET_DDR]	= अणु CMU_DEVRST0, BIT(2) पूर्ण,
	[RESET_न_अंकDC]	= अणु CMU_DEVRST0, BIT(3) पूर्ण,
	[RESET_SD0]	= अणु CMU_DEVRST0, BIT(4) पूर्ण,
	[RESET_SD1]	= अणु CMU_DEVRST0, BIT(5) पूर्ण,
	[RESET_PCM1]	= अणु CMU_DEVRST0, BIT(6) पूर्ण,
	[RESET_DE]	= अणु CMU_DEVRST0, BIT(7) पूर्ण,
	[RESET_LCD]	= अणु CMU_DEVRST0, BIT(8) पूर्ण,
	[RESET_SD2]	= अणु CMU_DEVRST0, BIT(9) पूर्ण,
	[RESET_DSI]	= अणु CMU_DEVRST0, BIT(10) पूर्ण,
	[RESET_CSI]	= अणु CMU_DEVRST0, BIT(11) पूर्ण,
	[RESET_BISP]	= अणु CMU_DEVRST0, BIT(12) पूर्ण,
	[RESET_KEY]	= अणु CMU_DEVRST0, BIT(14) पूर्ण,
	[RESET_GPIO]	= अणु CMU_DEVRST0, BIT(15) पूर्ण,
	[RESET_AUDIO]	= अणु CMU_DEVRST0, BIT(17) पूर्ण,
	[RESET_PCM0]	= अणु CMU_DEVRST0, BIT(18) पूर्ण,
	[RESET_VDE]	= अणु CMU_DEVRST0, BIT(19) पूर्ण,
	[RESET_VCE]	= अणु CMU_DEVRST0, BIT(20) पूर्ण,
	[RESET_GPU3D]	= अणु CMU_DEVRST0, BIT(22) पूर्ण,
	[RESET_NIC301]	= अणु CMU_DEVRST0, BIT(23) पूर्ण,
	[RESET_LENS]	= अणु CMU_DEVRST0, BIT(26) पूर्ण,
	[RESET_PERIPHRESET] = अणु CMU_DEVRST0, BIT(27) पूर्ण,
	[RESET_USB2_0]	= अणु CMU_DEVRST1, BIT(0) पूर्ण,
	[RESET_TVOUT]	= अणु CMU_DEVRST1, BIT(1) पूर्ण,
	[RESET_HDMI]	= अणु CMU_DEVRST1, BIT(2) पूर्ण,
	[RESET_HDCP2TX]	= अणु CMU_DEVRST1, BIT(3) पूर्ण,
	[RESET_UART6]	= अणु CMU_DEVRST1, BIT(4) पूर्ण,
	[RESET_UART0]	= अणु CMU_DEVRST1, BIT(5) पूर्ण,
	[RESET_UART1]	= अणु CMU_DEVRST1, BIT(6) पूर्ण,
	[RESET_UART2]	= अणु CMU_DEVRST1, BIT(7) पूर्ण,
	[RESET_SPI0]	= अणु CMU_DEVRST1, BIT(8) पूर्ण,
	[RESET_SPI1]	= अणु CMU_DEVRST1, BIT(9) पूर्ण,
	[RESET_SPI2]	= अणु CMU_DEVRST1, BIT(10) पूर्ण,
	[RESET_SPI3]	= अणु CMU_DEVRST1, BIT(11) पूर्ण,
	[RESET_I2C0]	= अणु CMU_DEVRST1, BIT(12) पूर्ण,
	[RESET_I2C1]	= अणु CMU_DEVRST1, BIT(13) पूर्ण,
	[RESET_USB3]	= अणु CMU_DEVRST1, BIT(14) पूर्ण,
	[RESET_UART3]	= अणु CMU_DEVRST1, BIT(15) पूर्ण,
	[RESET_UART4]	= अणु CMU_DEVRST1, BIT(16) पूर्ण,
	[RESET_UART5]	= अणु CMU_DEVRST1, BIT(17) पूर्ण,
	[RESET_I2C2]	= अणु CMU_DEVRST1, BIT(18) पूर्ण,
	[RESET_I2C3]	= अणु CMU_DEVRST1, BIT(19) पूर्ण,
	[RESET_ETHERNET] = अणु CMU_DEVRST1, BIT(20) पूर्ण,
	[RESET_CHIPID]	= अणु CMU_DEVRST1, BIT(21) पूर्ण,
	[RESET_USB2_1]	= अणु CMU_DEVRST1, BIT(22) पूर्ण,
	[RESET_WD0RESET] = अणु CMU_DEVRST1, BIT(24) पूर्ण,
	[RESET_WD1RESET] = अणु CMU_DEVRST1, BIT(25) पूर्ण,
	[RESET_WD2RESET] = अणु CMU_DEVRST1, BIT(26) पूर्ण,
	[RESET_WD3RESET] = अणु CMU_DEVRST1, BIT(27) पूर्ण,
	[RESET_DBG0RESET] = अणु CMU_DEVRST1, BIT(28) पूर्ण,
	[RESET_DBG1RESET] = अणु CMU_DEVRST1, BIT(29) पूर्ण,
	[RESET_DBG2RESET] = अणु CMU_DEVRST1, BIT(30) पूर्ण,
	[RESET_DBG3RESET] = अणु CMU_DEVRST1, BIT(31) पूर्ण,
पूर्ण;

अटल काष्ठा owl_clk_desc s500_clk_desc = अणु
	.clks	    = s500_clks,
	.num_clks   = ARRAY_SIZE(s500_clks),

	.hw_clks    = &s500_hw_clks,

	.resets     = s500_resets,
	.num_resets = ARRAY_SIZE(s500_resets),
पूर्ण;

अटल पूर्णांक s500_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_clk_desc *desc;
	काष्ठा owl_reset *reset;
	पूर्णांक ret;

	desc = &s500_clk_desc;
	owl_clk_regmap_init(pdev, desc);

	reset = devm_kzalloc(&pdev->dev, माप(*reset), GFP_KERNEL);
	अगर (!reset)
		वापस -ENOMEM;

	reset->rcdev.of_node = pdev->dev.of_node;
	reset->rcdev.ops = &owl_reset_ops;
	reset->rcdev.nr_resets = desc->num_resets;
	reset->reset_map = desc->resets;
	reset->regmap = desc->regmap;

	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &reset->rcdev);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to register reset controller\n");

	वापस owl_clk_probe(&pdev->dev, desc->hw_clks);
पूर्ण

अटल स्थिर काष्ठा of_device_id s500_clk_of_match[] = अणु
	अणु .compatible = "actions,s500-cmu", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver s500_clk_driver = अणु
	.probe = s500_clk_probe,
	.driver = अणु
		.name = "s500-cmu",
		.of_match_table = s500_clk_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init s500_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s500_clk_driver);
पूर्ण
core_initcall(s500_clk_init);
