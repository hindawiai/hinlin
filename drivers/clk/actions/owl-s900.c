<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL S900 SoC घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

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

#समावेश <dt-bindings/घड़ी/actions,s900-cmu.h>
#समावेश <dt-bindings/reset/actions,s900-reset.h>

#घोषणा CMU_COREPLL		(0x0000)
#घोषणा CMU_DEVPLL		(0x0004)
#घोषणा CMU_DDRPLL		(0x0008)
#घोषणा CMU_न_अंकDPLL		(0x000C)
#घोषणा CMU_DISPLAYPLL		(0x0010)
#घोषणा CMU_AUDIOPLL		(0x0014)
#घोषणा CMU_TVOUTPLL		(0x0018)
#घोषणा CMU_BUSCLK		(0x001C)
#घोषणा CMU_SENSORCLK		(0x0020)
#घोषणा CMU_LCDCLK		(0x0024)
#घोषणा CMU_DSICLK		(0x0028)
#घोषणा CMU_CSICLK		(0x002C)
#घोषणा CMU_DECLK		(0x0030)
#घोषणा CMU_BISPCLK		(0x0034)
#घोषणा CMU_IMXCLK		(0x0038)
#घोषणा CMU_HDECLK		(0x003C)
#घोषणा CMU_VDECLK		(0x0040)
#घोषणा CMU_VCECLK		(0x0044)
#घोषणा CMU_न_अंकDCCLK		(0x004C)
#घोषणा CMU_SD0CLK		(0x0050)
#घोषणा CMU_SD1CLK		(0x0054)
#घोषणा CMU_SD2CLK		(0x0058)
#घोषणा CMU_UART0CLK		(0x005C)
#घोषणा CMU_UART1CLK		(0x0060)
#घोषणा CMU_UART2CLK		(0x0064)
#घोषणा CMU_PWM0CLK		(0x0070)
#घोषणा CMU_PWM1CLK		(0x0074)
#घोषणा CMU_PWM2CLK		(0x0078)
#घोषणा CMU_PWM3CLK		(0x007C)
#घोषणा CMU_USBPLL		(0x0080)
#घोषणा CMU_ASSISTPLL		(0x0084)
#घोषणा CMU_EDPCLK		(0x0088)
#घोषणा CMU_GPU3DCLK		(0x0090)
#घोषणा CMU_CORECTL		(0x009C)
#घोषणा CMU_DEVCLKEN0		(0x00A0)
#घोषणा CMU_DEVCLKEN1		(0x00A4)
#घोषणा CMU_DEVRST0		(0x00A8)
#घोषणा CMU_DEVRST1		(0x00AC)
#घोषणा CMU_UART3CLK		(0x00B0)
#घोषणा CMU_UART4CLK		(0x00B4)
#घोषणा CMU_UART5CLK		(0x00B8)
#घोषणा CMU_UART6CLK		(0x00BC)
#घोषणा CMU_TLSCLK		(0x00C0)
#घोषणा CMU_SD3CLK		(0x00C4)
#घोषणा CMU_PWM4CLK		(0x00C8)
#घोषणा CMU_PWM5CLK		(0x00CC)

अटल काष्ठा clk_pll_table clk_audio_pll_table[] = अणु
	अणु 0, 45158400 पूर्ण, अणु 1, 49152000 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll_table clk_edp_pll_table[] = अणु
	अणु 0, 810000000 पूर्ण, अणु 1, 135000000 पूर्ण, अणु 2, 270000000 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

/* pll घड़ीs */
अटल OWL_PLL_NO_PARENT(core_pll_clk, "core_pll_clk", CMU_COREPLL, 24000000, 9, 0, 8, 5, 107, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(dev_pll_clk, "dev_pll_clk", CMU_DEVPLL, 6000000, 8, 0, 8, 20, 180, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(ddr_pll_clk, "ddr_pll_clk", CMU_DDRPLL, 24000000, 8, 0, 8, 5, 45, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(nand_pll_clk, "nand_pll_clk", CMU_न_अंकDPLL, 6000000, 8, 0, 8, 4, 100, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(display_pll_clk, "display_pll_clk", CMU_DISPLAYPLL, 6000000, 8, 0, 8, 20, 180, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(assist_pll_clk, "assist_pll_clk", CMU_ASSISTPLL, 500000000, 0, 0, 0, 0, 0, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(audio_pll_clk, "audio_pll_clk", CMU_AUDIOPLL, 0, 4, 0, 1, 0, 0, clk_audio_pll_table, CLK_IGNORE_UNUSED);
अटल OWL_PLL(edp_pll_clk, "edp_pll_clk", "edp24M_clk", CMU_EDPCLK, 0, 9, 0, 2, 0, 0, clk_edp_pll_table, CLK_IGNORE_UNUSED);

अटल स्थिर अक्षर *cpu_clk_mux_p[] = अणु "losc", "hosc", "core_pll_clk", पूर्ण;
अटल स्थिर अक्षर *dev_clk_p[] = अणु "hosc", "dev_pll_clk", पूर्ण;
अटल स्थिर अक्षर *noc_clk_mux_p[] = अणु "dev_clk", "assist_pll_clk", पूर्ण;
अटल स्थिर अक्षर *dmm_clk_mux_p[] = अणु "dev_clk", "nand_pll_clk", "assist_pll_clk", "ddr_clk_src", पूर्ण;
अटल स्थिर अक्षर *bisp_clk_mux_p[] = अणु "assist_pll_clk", "dev_clk", पूर्ण;
अटल स्थिर अक्षर *csi_clk_mux_p[] = अणु "display_pll_clk", "dev_clk", पूर्ण;
अटल स्थिर अक्षर *de_clk_mux_p[] = अणु "assist_pll_clk", "dev_clk", पूर्ण;
अटल स्थिर अक्षर *gpu_clk_mux_p[] = अणु "dev_clk", "display_pll_clk", "ddr_clk_src", पूर्ण;
अटल स्थिर अक्षर *hde_clk_mux_p[] = अणु "dev_clk", "display_pll_clk", "ddr_clk_src", पूर्ण;
अटल स्थिर अक्षर *imx_clk_mux_p[] = अणु "assist_pll_clk", "dev_clk", पूर्ण;
अटल स्थिर अक्षर *lcd_clk_mux_p[] = अणु "display_pll_clk", "nand_pll_clk", पूर्ण;
अटल स्थिर अक्षर *nand_clk_mux_p[] = अणु "dev_clk", "nand_pll_clk", पूर्ण;
अटल स्थिर अक्षर *sd_clk_mux_p[] = अणु "dev_clk", "nand_pll_clk", पूर्ण;
अटल स्थिर अक्षर *sensor_clk_mux_p[] = अणु "hosc", "bisp_clk", पूर्ण;
अटल स्थिर अक्षर *uart_clk_mux_p[] = अणु "hosc", "dev_pll_clk", पूर्ण;
अटल स्थिर अक्षर *vce_clk_mux_p[] = अणु "dev_clk", "display_pll_clk", "assist_pll_clk", "ddr_clk_src", पूर्ण;
अटल स्थिर अक्षर *i2s_clk_mux_p[] = अणु "audio_pll_clk", पूर्ण;
अटल स्थिर अक्षर *edp_clk_mux_p[] = अणु "assist_pll_clk", "display_pll_clk", पूर्ण;

/* mux घड़ीs */
अटल OWL_MUX(cpu_clk, "cpu_clk", cpu_clk_mux_p, CMU_BUSCLK, 0, 2, CLK_SET_RATE_PARENT);
अटल OWL_MUX(dev_clk, "dev_clk", dev_clk_p, CMU_DEVPLL, 12, 1, CLK_SET_RATE_PARENT);
अटल OWL_MUX(noc_clk_mux, "noc_clk_mux", noc_clk_mux_p, CMU_BUSCLK, 7, 1, CLK_SET_RATE_PARENT);

अटल काष्ठा clk_भाग_प्रकारable nand_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 6 पूर्ण,
	अणु 4, 8 पूर्ण, अणु 5, 10 पूर्ण, अणु 6, 12 पूर्ण, अणु 7, 14 पूर्ण,
	अणु 8, 16 पूर्ण, अणु 9, 18 पूर्ण, अणु 10, 20 पूर्ण, अणु 11, 22 पूर्ण,
	अणु 12, 24 पूर्ण, अणु 13, 26 पूर्ण, अणु 14, 28 पूर्ण, अणु 15, 30 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable apb_भाग_प्रकारable[] = अणु
	अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable eth_mac_भाग_प्रकारable[] = अणु
	अणु 0, 2 पूर्ण, अणु 1, 4 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable rmii_ref_भाग_प्रकारable[] = अणु
	अणु 0, 4 पूर्ण,	  अणु 1, 10 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable usb3_mac_भाग_प्रकारable[] = अणु
	अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 0, 8 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable i2s_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 6 पूर्ण, अणु 5, 8 पूर्ण, अणु 6, 12 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 8, 24 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable hdmia_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 6 पूर्ण, अणु 5, 8 पूर्ण, अणु 6, 12 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 8, 24 पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

/* भागider घड़ीs */
अटल OWL_DIVIDER(noc_clk_भाग, "noc_clk_div", "noc_clk", CMU_BUSCLK, 19, 1, शून्य, 0, 0);
अटल OWL_DIVIDER(ahb_clk, "ahb_clk", "noc_clk_div", CMU_BUSCLK, 4, 1, शून्य, 0, 0);
अटल OWL_DIVIDER(apb_clk, "apb_clk", "ahb_clk", CMU_BUSCLK, 8, 2, apb_भाग_प्रकारable, 0, 0);
अटल OWL_DIVIDER(usb3_mac_clk, "usb3_mac_clk", "assist_pll_clk", CMU_ASSISTPLL, 12, 2, usb3_mac_भाग_प्रकारable, 0, 0);
अटल OWL_DIVIDER(rmii_ref_clk, "rmii_ref_clk", "assist_pll_clk", CMU_ASSISTPLL, 8, 1, rmii_ref_भाग_प्रकारable, 0, 0);

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

	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table dmm_factor_table[] = अणु
	अणु 0, 1, 1 पूर्ण, अणु 1, 2, 3 पूर्ण, अणु 2, 1, 2 पूर्ण, अणु 3, 1, 3 पूर्ण,
	अणु 4, 1, 4 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table noc_factor_table[] = अणु
	अणु 0, 1, 1 पूर्ण,   अणु 1, 2, 3 पूर्ण, अणु 2, 1, 2 पूर्ण, अणु 3, 1, 3 पूर्ण, अणु 4, 1, 4 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table bisp_factor_table[] = अणु
	अणु 0, 1, 1 पूर्ण, अणु 1, 2, 3 पूर्ण, अणु 2, 1, 2 पूर्ण, अणु 3, 2, 5 पूर्ण,
	अणु 4, 1, 3 पूर्ण, अणु 5, 1, 4 पूर्ण, अणु 6, 1, 6 पूर्ण, अणु 7, 1, 8 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;

/* factor घड़ीs */
अटल OWL_FACTOR(noc_clk, "noc_clk", "noc_clk_mux", CMU_BUSCLK, 16, 3, noc_factor_table, 0, 0);
अटल OWL_FACTOR(de_clk1, "de_clk1", "de_clk", CMU_DECLK, 0, 3, bisp_factor_table, 0, 0);
अटल OWL_FACTOR(de_clk2, "de_clk2", "de_clk", CMU_DECLK, 4, 3, bisp_factor_table, 0, 0);
अटल OWL_FACTOR(de_clk3, "de_clk3", "de_clk", CMU_DECLK, 8, 3, bisp_factor_table, 0, 0);

/* gate घड़ीs */
अटल OWL_GATE(gpio_clk, "gpio_clk", "apb_clk", CMU_DEVCLKEN0, 18, 0, 0);
अटल OWL_GATE_NO_PARENT(gpu_clk, "gpu_clk", CMU_DEVCLKEN0, 30, 0, 0);
अटल OWL_GATE(dmac_clk, "dmac_clk", "noc_clk_div", CMU_DEVCLKEN0, 1, 0, 0);
अटल OWL_GATE(समयr_clk, "timer_clk", "hosc", CMU_DEVCLKEN1, 27, 0, 0);
अटल OWL_GATE_NO_PARENT(dsi_clk, "dsi_clk", CMU_DEVCLKEN0, 12, 0, 0);
अटल OWL_GATE(ddr0_clk, "ddr0_clk", "ddr_pll_clk", CMU_DEVCLKEN0, 31, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(ddr1_clk, "ddr1_clk", "ddr_pll_clk", CMU_DEVCLKEN0, 29, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE_NO_PARENT(usb3_480mpll0_clk, "usb3_480mpll0_clk", CMU_USBPLL, 3, 0, 0);
अटल OWL_GATE_NO_PARENT(usb3_480mphy0_clk, "usb3_480mphy0_clk", CMU_USBPLL, 2, 0, 0);
अटल OWL_GATE_NO_PARENT(usb3_5gphy_clk, "usb3_5gphy_clk", CMU_USBPLL, 1, 0, 0);
अटल OWL_GATE_NO_PARENT(usb3_cce_clk, "usb3_cce_clk", CMU_USBPLL, 0, 0, 0);
अटल OWL_GATE(edp24M_clk, "edp24M_clk", "diff24M", CMU_EDPCLK, 8, 0, 0);
अटल OWL_GATE(edp_link_clk, "edp_link_clk", "edp_pll_clk", CMU_DEVCLKEN0, 10, 0, 0);
अटल OWL_GATE_NO_PARENT(usbh0_pllen_clk, "usbh0_pllen_clk", CMU_USBPLL, 12, 0, 0);
अटल OWL_GATE_NO_PARENT(usbh0_phy_clk, "usbh0_phy_clk", CMU_USBPLL, 10, 0, 0);
अटल OWL_GATE_NO_PARENT(usbh0_cce_clk, "usbh0_cce_clk", CMU_USBPLL, 8, 0, 0);
अटल OWL_GATE_NO_PARENT(usbh1_pllen_clk, "usbh1_pllen_clk", CMU_USBPLL, 13, 0, 0);
अटल OWL_GATE_NO_PARENT(usbh1_phy_clk, "usbh1_phy_clk", CMU_USBPLL, 11, 0, 0);
अटल OWL_GATE_NO_PARENT(usbh1_cce_clk, "usbh1_cce_clk", CMU_USBPLL, 9, 0, 0);
अटल OWL_GATE(spi0_clk, "spi0_clk", "ahb_clk", CMU_DEVCLKEN1, 10, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(spi1_clk, "spi1_clk", "ahb_clk", CMU_DEVCLKEN1, 11, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(spi2_clk, "spi2_clk", "ahb_clk", CMU_DEVCLKEN1, 12, 0, CLK_IGNORE_UNUSED);
अटल OWL_GATE(spi3_clk, "spi3_clk", "ahb_clk", CMU_DEVCLKEN1, 13, 0, CLK_IGNORE_UNUSED);

/* composite घड़ीs */
अटल OWL_COMP_FACTOR(bisp_clk, "bisp_clk", bisp_clk_mux_p,
			OWL_MUX_HW(CMU_BISPCLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 14, 0),
			OWL_FACTOR_HW(CMU_BISPCLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_DIV(csi0_clk, "csi0_clk", csi_clk_mux_p,
			OWL_MUX_HW(CMU_CSICLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 13, 0),
			OWL_DIVIDER_HW(CMU_CSICLK, 0, 4, 0, शून्य),
			0);

अटल OWL_COMP_DIV(csi1_clk, "csi1_clk", csi_clk_mux_p,
			OWL_MUX_HW(CMU_CSICLK, 20, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 15, 0),
			OWL_DIVIDER_HW(CMU_CSICLK, 16, 4, 0, शून्य),
			0);

अटल OWL_COMP_PASS(de_clk, "de_clk", de_clk_mux_p,
			OWL_MUX_HW(CMU_DECLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 8, 0),
			0);

अटल OWL_COMP_FACTOR(dmm_clk, "dmm_clk", dmm_clk_mux_p,
			OWL_MUX_HW(CMU_BUSCLK, 10, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 19, 0),
			OWL_FACTOR_HW(CMU_BUSCLK, 12, 3, 0, dmm_factor_table),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_FACTOR(edp_clk, "edp_clk", edp_clk_mux_p,
			OWL_MUX_HW(CMU_EDPCLK, 19, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 10, 0),
			OWL_FACTOR_HW(CMU_EDPCLK, 16, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_DIV_FIXED(eth_mac_clk, "eth_mac_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 22, 0),
			OWL_DIVIDER_HW(CMU_ASSISTPLL, 10, 1, 0, eth_mac_भाग_प्रकारable),
			0);

अटल OWL_COMP_FACTOR(gpu_core_clk, "gpu_core_clk", gpu_clk_mux_p,
			OWL_MUX_HW(CMU_GPU3DCLK, 4, 2),
			OWL_GATE_HW(CMU_GPU3DCLK, 15, 0),
			OWL_FACTOR_HW(CMU_GPU3DCLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(gpu_mem_clk, "gpu_mem_clk", gpu_clk_mux_p,
			OWL_MUX_HW(CMU_GPU3DCLK, 20, 2),
			OWL_GATE_HW(CMU_GPU3DCLK, 14, 0),
			OWL_FACTOR_HW(CMU_GPU3DCLK, 16, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(gpu_sys_clk, "gpu_sys_clk", gpu_clk_mux_p,
			OWL_MUX_HW(CMU_GPU3DCLK, 28, 2),
			OWL_GATE_HW(CMU_GPU3DCLK, 13, 0),
			OWL_FACTOR_HW(CMU_GPU3DCLK, 24, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(hde_clk, "hde_clk", hde_clk_mux_p,
			OWL_MUX_HW(CMU_HDECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 27, 0),
			OWL_FACTOR_HW(CMU_HDECLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_DIV(hdmia_clk, "hdmia_clk", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 22, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 24, 4, 0, hdmia_भाग_प्रकारable),
			0);

अटल OWL_COMP_FIXED_FACTOR(i2c0_clk, "i2c0_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 14, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c1_clk, "i2c1_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 15, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c2_clk, "i2c2_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 30, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c3_clk, "i2c3_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 31, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c4_clk, "i2c4_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN0, 17, 0),
			1, 5, 0);

अटल OWL_COMP_FIXED_FACTOR(i2c5_clk, "i2c5_clk", "assist_pll_clk",
			OWL_GATE_HW(CMU_DEVCLKEN1, 1, 0),
			1, 5, 0);

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

अटल OWL_COMP_FACTOR(imx_clk, "imx_clk", imx_clk_mux_p,
			OWL_MUX_HW(CMU_IMXCLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 17, 0),
			OWL_FACTOR_HW(CMU_IMXCLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_DIV(lcd_clk, "lcd_clk", lcd_clk_mux_p,
			OWL_MUX_HW(CMU_LCDCLK, 12, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 9, 0),
			OWL_DIVIDER_HW(CMU_LCDCLK, 0, 5, 0, शून्य),
			0);

अटल OWL_COMP_DIV(nand0_clk, "nand0_clk", nand_clk_mux_p,
			OWL_MUX_HW(CMU_न_अंकDCCLK, 8, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 4, 0),
			OWL_DIVIDER_HW(CMU_न_अंकDCCLK, 0, 4, 0, nand_भाग_प्रकारable),
			CLK_SET_RATE_PARENT);

अटल OWL_COMP_DIV(nand1_clk, "nand1_clk", nand_clk_mux_p,
			OWL_MUX_HW(CMU_न_अंकDCCLK, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 11, 0),
			OWL_DIVIDER_HW(CMU_न_अंकDCCLK, 16, 4, 0, nand_भाग_प्रकारable),
			CLK_SET_RATE_PARENT);

अटल OWL_COMP_DIV_FIXED(pwm0_clk, "pwm0_clk", "hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 23, 0),
			OWL_DIVIDER_HW(CMU_PWM0CLK, 0, 6, 0, शून्य),
			0);

अटल OWL_COMP_DIV_FIXED(pwm1_clk, "pwm1_clk", "hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 24, 0),
			OWL_DIVIDER_HW(CMU_PWM1CLK, 0, 6, 0, शून्य),
			0);
/*
 * pwm2 may be क्रम backlight, करो not gate it
 * even it is "unused", because it may be
 * enabled at boot stage, and in kernel, driver
 * has no effective method to know the real status,
 * so, the best way is keeping it as what it was.
 */
अटल OWL_COMP_DIV_FIXED(pwm2_clk, "pwm2_clk", "hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 25, 0),
			OWL_DIVIDER_HW(CMU_PWM2CLK, 0, 6, 0, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV_FIXED(pwm3_clk, "pwm3_clk", "hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 26, 0),
			OWL_DIVIDER_HW(CMU_PWM3CLK, 0, 6, 0, शून्य),
			0);

अटल OWL_COMP_DIV_FIXED(pwm4_clk, "pwm4_clk", "hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 4, 0),
			OWL_DIVIDER_HW(CMU_PWM4CLK, 0, 6, 0, शून्य),
			0);

अटल OWL_COMP_DIV_FIXED(pwm5_clk, "pwm5_clk", "hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 5, 0),
			OWL_DIVIDER_HW(CMU_PWM5CLK, 0, 6, 0, शून्य),
			0);

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

अटल OWL_COMP_FACTOR(sd3_clk, "sd3_clk", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD3CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 16, 0),
			OWL_FACTOR_HW(CMU_SD3CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_DIV(sensor_clk, "sensor_clk", sensor_clk_mux_p,
			OWL_MUX_HW(CMU_SENSORCLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 14, 0),
			OWL_DIVIDER_HW(CMU_SENSORCLK, 0, 4, 0, शून्य),
			0);

अटल OWL_COMP_DIV_FIXED(speed_sensor_clk, "speed_sensor_clk",
			"hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 0, 0),
			OWL_DIVIDER_HW(CMU_TLSCLK, 0, 4, CLK_DIVIDER_POWER_OF_TWO, शून्य),
			0);

अटल OWL_COMP_DIV_FIXED(thermal_sensor_clk, "thermal_sensor_clk",
			"hosc",
			OWL_GATE_HW(CMU_DEVCLKEN1, 2, 0),
			OWL_DIVIDER_HW(CMU_TLSCLK, 8, 4, CLK_DIVIDER_POWER_OF_TWO, शून्य),
			0);

अटल OWL_COMP_DIV(uart0_clk, "uart0_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART0CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 6, 0),
			OWL_DIVIDER_HW(CMU_UART0CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart1_clk, "uart1_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART1CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 7, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 1, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart2_clk, "uart2_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART2CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 8, 0),
			OWL_DIVIDER_HW(CMU_UART2CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart3_clk, "uart3_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART3CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 19, 0),
			OWL_DIVIDER_HW(CMU_UART3CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart4_clk, "uart4_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART4CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 20, 0),
			OWL_DIVIDER_HW(CMU_UART4CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart5_clk, "uart5_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART5CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 21, 0),
			OWL_DIVIDER_HW(CMU_UART5CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(uart6_clk, "uart6_clk", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART6CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 18, 0),
			OWL_DIVIDER_HW(CMU_UART6CLK, 0, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_FACTOR(vce_clk, "vce_clk", vce_clk_mux_p,
			OWL_MUX_HW(CMU_VCECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 26, 0),
			OWL_FACTOR_HW(CMU_VCECLK, 0, 3, 0, bisp_factor_table),
			0);

अटल OWL_COMP_FACTOR(vde_clk, "vde_clk", hde_clk_mux_p,
			OWL_MUX_HW(CMU_VDECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 25, 0),
			OWL_FACTOR_HW(CMU_VDECLK, 0, 3, 0, bisp_factor_table),
			0);

अटल काष्ठा owl_clk_common *s900_clks[] = अणु
	&core_pll_clk.common,
	&dev_pll_clk.common,
	&ddr_pll_clk.common,
	&nand_pll_clk.common,
	&display_pll_clk.common,
	&assist_pll_clk.common,
	&audio_pll_clk.common,
	&edp_pll_clk.common,
	&cpu_clk.common,
	&dev_clk.common,
	&noc_clk_mux.common,
	&noc_clk_भाग.common,
	&ahb_clk.common,
	&apb_clk.common,
	&usb3_mac_clk.common,
	&rmii_ref_clk.common,
	&noc_clk.common,
	&de_clk1.common,
	&de_clk2.common,
	&de_clk3.common,
	&gpio_clk.common,
	&gpu_clk.common,
	&dmac_clk.common,
	&समयr_clk.common,
	&dsi_clk.common,
	&ddr0_clk.common,
	&ddr1_clk.common,
	&usb3_480mpll0_clk.common,
	&usb3_480mphy0_clk.common,
	&usb3_5gphy_clk.common,
	&usb3_cce_clk.common,
	&edp24M_clk.common,
	&edp_link_clk.common,
	&usbh0_pllen_clk.common,
	&usbh0_phy_clk.common,
	&usbh0_cce_clk.common,
	&usbh1_pllen_clk.common,
	&usbh1_phy_clk.common,
	&usbh1_cce_clk.common,
	&i2c0_clk.common,
	&i2c1_clk.common,
	&i2c2_clk.common,
	&i2c3_clk.common,
	&i2c4_clk.common,
	&i2c5_clk.common,
	&spi0_clk.common,
	&spi1_clk.common,
	&spi2_clk.common,
	&spi3_clk.common,
	&bisp_clk.common,
	&csi0_clk.common,
	&csi1_clk.common,
	&de_clk.common,
	&dmm_clk.common,
	&edp_clk.common,
	&eth_mac_clk.common,
	&gpu_core_clk.common,
	&gpu_mem_clk.common,
	&gpu_sys_clk.common,
	&hde_clk.common,
	&hdmia_clk.common,
	&i2srx_clk.common,
	&i2stx_clk.common,
	&imx_clk.common,
	&lcd_clk.common,
	&nand0_clk.common,
	&nand1_clk.common,
	&pwm0_clk.common,
	&pwm1_clk.common,
	&pwm2_clk.common,
	&pwm3_clk.common,
	&pwm4_clk.common,
	&pwm5_clk.common,
	&sd0_clk.common,
	&sd1_clk.common,
	&sd2_clk.common,
	&sd3_clk.common,
	&sensor_clk.common,
	&speed_sensor_clk.common,
	&thermal_sensor_clk.common,
	&uart0_clk.common,
	&uart1_clk.common,
	&uart2_clk.common,
	&uart3_clk.common,
	&uart4_clk.common,
	&uart5_clk.common,
	&uart6_clk.common,
	&vce_clk.common,
	&vde_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data s900_hw_clks = अणु
	.hws	= अणु
		[CLK_CORE_PLL]		= &core_pll_clk.common.hw,
		[CLK_DEV_PLL]		= &dev_pll_clk.common.hw,
		[CLK_DDR_PLL]		= &ddr_pll_clk.common.hw,
		[CLK_न_अंकD_PLL]		= &nand_pll_clk.common.hw,
		[CLK_DISPLAY_PLL]	= &display_pll_clk.common.hw,
		[CLK_ASSIST_PLL]	= &assist_pll_clk.common.hw,
		[CLK_AUDIO_PLL]		= &audio_pll_clk.common.hw,
		[CLK_EDP_PLL]		= &edp_pll_clk.common.hw,
		[CLK_CPU]		= &cpu_clk.common.hw,
		[CLK_DEV]		= &dev_clk.common.hw,
		[CLK_NOC_MUX]		= &noc_clk_mux.common.hw,
		[CLK_NOC_DIV]		= &noc_clk_भाग.common.hw,
		[CLK_AHB]		= &ahb_clk.common.hw,
		[CLK_APB]		= &apb_clk.common.hw,
		[CLK_USB3_MAC]		= &usb3_mac_clk.common.hw,
		[CLK_RMII_REF]		= &rmii_ref_clk.common.hw,
		[CLK_NOC]		= &noc_clk.common.hw,
		[CLK_DE1]		= &de_clk1.common.hw,
		[CLK_DE2]		= &de_clk2.common.hw,
		[CLK_DE3]		= &de_clk3.common.hw,
		[CLK_GPIO]		= &gpio_clk.common.hw,
		[CLK_GPU]		= &gpu_clk.common.hw,
		[CLK_DMAC]		= &dmac_clk.common.hw,
		[CLK_TIMER]		= &समयr_clk.common.hw,
		[CLK_DSI]		= &dsi_clk.common.hw,
		[CLK_DDR0]		= &ddr0_clk.common.hw,
		[CLK_DDR1]		= &ddr1_clk.common.hw,
		[CLK_USB3_480MPLL0]	= &usb3_480mpll0_clk.common.hw,
		[CLK_USB3_480MPHY0]	= &usb3_480mphy0_clk.common.hw,
		[CLK_USB3_5GPHY]	= &usb3_5gphy_clk.common.hw,
		[CLK_USB3_CCE]		= &usb3_cce_clk.common.hw,
		[CLK_24M_EDP]		= &edp24M_clk.common.hw,
		[CLK_EDP_LINK]		= &edp_link_clk.common.hw,
		[CLK_USB2H0_PLLEN]	= &usbh0_pllen_clk.common.hw,
		[CLK_USB2H0_PHY]	= &usbh0_phy_clk.common.hw,
		[CLK_USB2H0_CCE]	= &usbh0_cce_clk.common.hw,
		[CLK_USB2H1_PLLEN]	= &usbh1_pllen_clk.common.hw,
		[CLK_USB2H1_PHY]	= &usbh1_phy_clk.common.hw,
		[CLK_USB2H1_CCE]	= &usbh1_cce_clk.common.hw,
		[CLK_I2C0]		= &i2c0_clk.common.hw,
		[CLK_I2C1]		= &i2c1_clk.common.hw,
		[CLK_I2C2]		= &i2c2_clk.common.hw,
		[CLK_I2C3]		= &i2c3_clk.common.hw,
		[CLK_I2C4]		= &i2c4_clk.common.hw,
		[CLK_I2C5]		= &i2c5_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_SPI1]		= &spi1_clk.common.hw,
		[CLK_SPI2]		= &spi2_clk.common.hw,
		[CLK_SPI3]		= &spi3_clk.common.hw,
		[CLK_BISP]		= &bisp_clk.common.hw,
		[CLK_CSI0]		= &csi0_clk.common.hw,
		[CLK_CSI1]		= &csi1_clk.common.hw,
		[CLK_DE0]		= &de_clk.common.hw,
		[CLK_DMM]		= &dmm_clk.common.hw,
		[CLK_EDP]		= &edp_clk.common.hw,
		[CLK_ETH_MAC]		= &eth_mac_clk.common.hw,
		[CLK_GPU_CORE]		= &gpu_core_clk.common.hw,
		[CLK_GPU_MEM]		= &gpu_mem_clk.common.hw,
		[CLK_GPU_SYS]		= &gpu_sys_clk.common.hw,
		[CLK_HDE]		= &hde_clk.common.hw,
		[CLK_HDMI_AUDIO]	= &hdmia_clk.common.hw,
		[CLK_I2SRX]		= &i2srx_clk.common.hw,
		[CLK_I2STX]		= &i2stx_clk.common.hw,
		[CLK_IMX]		= &imx_clk.common.hw,
		[CLK_LCD]		= &lcd_clk.common.hw,
		[CLK_न_अंकD0]		= &nand0_clk.common.hw,
		[CLK_न_अंकD1]		= &nand1_clk.common.hw,
		[CLK_PWM0]		= &pwm0_clk.common.hw,
		[CLK_PWM1]		= &pwm1_clk.common.hw,
		[CLK_PWM2]		= &pwm2_clk.common.hw,
		[CLK_PWM3]		= &pwm3_clk.common.hw,
		[CLK_PWM4]		= &pwm4_clk.common.hw,
		[CLK_PWM5]		= &pwm5_clk.common.hw,
		[CLK_SD0]		= &sd0_clk.common.hw,
		[CLK_SD1]		= &sd1_clk.common.hw,
		[CLK_SD2]		= &sd2_clk.common.hw,
		[CLK_SD3]		= &sd3_clk.common.hw,
		[CLK_SENSOR]		= &sensor_clk.common.hw,
		[CLK_SPEED_SENSOR]	= &speed_sensor_clk.common.hw,
		[CLK_THERMAL_SENSOR]	= &thermal_sensor_clk.common.hw,
		[CLK_UART0]		= &uart0_clk.common.hw,
		[CLK_UART1]		= &uart1_clk.common.hw,
		[CLK_UART2]		= &uart2_clk.common.hw,
		[CLK_UART3]		= &uart3_clk.common.hw,
		[CLK_UART4]		= &uart4_clk.common.hw,
		[CLK_UART5]		= &uart5_clk.common.hw,
		[CLK_UART6]		= &uart6_clk.common.hw,
		[CLK_VCE]		= &vce_clk.common.hw,
		[CLK_VDE]		= &vde_clk.common.hw,
	पूर्ण,
	.num	= CLK_NR_CLKS,
पूर्ण;

अटल स्थिर काष्ठा owl_reset_map s900_resets[] = अणु
	[RESET_DMAC]		= अणु CMU_DEVRST0, BIT(0) पूर्ण,
	[RESET_SRAMI]		= अणु CMU_DEVRST0, BIT(1) पूर्ण,
	[RESET_DDR_CTL_PHY]	= अणु CMU_DEVRST0, BIT(2) पूर्ण,
	[RESET_न_अंकDC0]		= अणु CMU_DEVRST0, BIT(3) पूर्ण,
	[RESET_SD0]		= अणु CMU_DEVRST0, BIT(4) पूर्ण,
	[RESET_SD1]		= अणु CMU_DEVRST0, BIT(5) पूर्ण,
	[RESET_PCM1]		= अणु CMU_DEVRST0, BIT(6) पूर्ण,
	[RESET_DE]		= अणु CMU_DEVRST0, BIT(7) पूर्ण,
	[RESET_LVDS]		= अणु CMU_DEVRST0, BIT(8) पूर्ण,
	[RESET_SD2]		= अणु CMU_DEVRST0, BIT(9) पूर्ण,
	[RESET_DSI]		= अणु CMU_DEVRST0, BIT(10) पूर्ण,
	[RESET_CSI0]		= अणु CMU_DEVRST0, BIT(11) पूर्ण,
	[RESET_BISP_AXI]	= अणु CMU_DEVRST0, BIT(12) पूर्ण,
	[RESET_CSI1]		= अणु CMU_DEVRST0, BIT(13) पूर्ण,
	[RESET_GPIO]		= अणु CMU_DEVRST0, BIT(15) पूर्ण,
	[RESET_EDP]		= अणु CMU_DEVRST0, BIT(16) पूर्ण,
	[RESET_AUDIO]		= अणु CMU_DEVRST0, BIT(17) पूर्ण,
	[RESET_PCM0]		= अणु CMU_DEVRST0, BIT(18) पूर्ण,
	[RESET_HDE]		= अणु CMU_DEVRST0, BIT(21) पूर्ण,
	[RESET_GPU3D_PA]	= अणु CMU_DEVRST0, BIT(22) पूर्ण,
	[RESET_IMX]		= अणु CMU_DEVRST0, BIT(23) पूर्ण,
	[RESET_SE]		= अणु CMU_DEVRST0, BIT(24) पूर्ण,
	[RESET_न_अंकDC1]		= अणु CMU_DEVRST0, BIT(25) पूर्ण,
	[RESET_SD3]		= अणु CMU_DEVRST0, BIT(26) पूर्ण,
	[RESET_GIC]		= अणु CMU_DEVRST0, BIT(27) पूर्ण,
	[RESET_GPU3D_PB]	= अणु CMU_DEVRST0, BIT(28) पूर्ण,
	[RESET_DDR_CTL_PHY_AXI]	= अणु CMU_DEVRST0, BIT(29) पूर्ण,
	[RESET_CMU_DDR]		= अणु CMU_DEVRST0, BIT(30) पूर्ण,
	[RESET_DMM]		= अणु CMU_DEVRST0, BIT(31) पूर्ण,
	[RESET_USB2HUB]		= अणु CMU_DEVRST1, BIT(0) पूर्ण,
	[RESET_USB2HSIC]	= अणु CMU_DEVRST1, BIT(1) पूर्ण,
	[RESET_HDMI]		= अणु CMU_DEVRST1, BIT(2) पूर्ण,
	[RESET_HDCP2TX]		= अणु CMU_DEVRST1, BIT(3) पूर्ण,
	[RESET_UART6]		= अणु CMU_DEVRST1, BIT(4) पूर्ण,
	[RESET_UART0]		= अणु CMU_DEVRST1, BIT(5) पूर्ण,
	[RESET_UART1]		= अणु CMU_DEVRST1, BIT(6) पूर्ण,
	[RESET_UART2]		= अणु CMU_DEVRST1, BIT(7) पूर्ण,
	[RESET_SPI0]		= अणु CMU_DEVRST1, BIT(8) पूर्ण,
	[RESET_SPI1]		= अणु CMU_DEVRST1, BIT(9) पूर्ण,
	[RESET_SPI2]		= अणु CMU_DEVRST1, BIT(10) पूर्ण,
	[RESET_SPI3]		= अणु CMU_DEVRST1, BIT(11) पूर्ण,
	[RESET_I2C0]		= अणु CMU_DEVRST1, BIT(12) पूर्ण,
	[RESET_I2C1]		= अणु CMU_DEVRST1, BIT(13) पूर्ण,
	[RESET_USB3]		= अणु CMU_DEVRST1, BIT(14) पूर्ण,
	[RESET_UART3]		= अणु CMU_DEVRST1, BIT(15) पूर्ण,
	[RESET_UART4]		= अणु CMU_DEVRST1, BIT(16) पूर्ण,
	[RESET_UART5]		= अणु CMU_DEVRST1, BIT(17) पूर्ण,
	[RESET_I2C2]		= अणु CMU_DEVRST1, BIT(18) पूर्ण,
	[RESET_I2C3]		= अणु CMU_DEVRST1, BIT(19) पूर्ण,
	[RESET_ETHERNET]	= अणु CMU_DEVRST1, BIT(20) पूर्ण,
	[RESET_CHIPID]		= अणु CMU_DEVRST1, BIT(21) पूर्ण,
	[RESET_I2C4]		= अणु CMU_DEVRST1, BIT(22) पूर्ण,
	[RESET_I2C5]		= अणु CMU_DEVRST1, BIT(23) पूर्ण,
	[RESET_CPU_SCNT]	= अणु CMU_DEVRST1, BIT(30) पूर्ण
पूर्ण;

अटल काष्ठा owl_clk_desc s900_clk_desc = अणु
	.clks	    = s900_clks,
	.num_clks   = ARRAY_SIZE(s900_clks),

	.hw_clks    = &s900_hw_clks,

	.resets     = s900_resets,
	.num_resets = ARRAY_SIZE(s900_resets),
पूर्ण;

अटल पूर्णांक s900_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_clk_desc *desc;
	काष्ठा owl_reset *reset;
	पूर्णांक ret;

	desc = &s900_clk_desc;
	owl_clk_regmap_init(pdev, desc);

	/*
	 * FIXME: Reset controller registration should be moved to
	 * common code, once all SoCs of Owl family supports it.
	 */
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

अटल स्थिर काष्ठा of_device_id s900_clk_of_match[] = अणु
	अणु .compatible = "actions,s900-cmu", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver s900_clk_driver = अणु
	.probe = s900_clk_probe,
	.driver = अणु
		.name = "s900-cmu",
		.of_match_table = s900_clk_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init s900_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s900_clk_driver);
पूर्ण
core_initcall(s900_clk_init);
