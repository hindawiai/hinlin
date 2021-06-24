<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi S700 घड़ी driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Author: Pathiban Nallathambi <pn@denx.de>
 * Author: Saravanan Sekar <sravanhome@gmail.com>
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

#समावेश <dt-bindings/घड़ी/actions,s700-cmu.h>
#समावेश <dt-bindings/reset/actions,s700-reset.h>

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
#घोषणा CMU_DSIPLLCLK		(0x0028)
#घोषणा CMU_CSICLK		(0x002C)
#घोषणा CMU_DECLK		(0x0030)
#घोषणा CMU_SICLK		(0x0034)
#घोषणा CMU_BUSCLK1		(0x0038)
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
#घोषणा CMU_UART3CLK		(0x0068)
#घोषणा CMU_UART4CLK		(0x006C)
#घोषणा CMU_UART5CLK		(0x0070)
#घोषणा CMU_UART6CLK		(0x0074)
#घोषणा CMU_PWM0CLK		(0x0078)
#घोषणा CMU_PWM1CLK		(0x007C)
#घोषणा CMU_PWM2CLK		(0x0080)
#घोषणा CMU_PWM3CLK		(0x0084)
#घोषणा CMU_PWM4CLK		(0x0088)
#घोषणा CMU_PWM5CLK		(0x008C)
#घोषणा CMU_GPU3DCLK		(0x0090)
#घोषणा CMU_CORECTL		(0x009C)
#घोषणा CMU_DEVCLKEN0		(0x00A0)
#घोषणा CMU_DEVCLKEN1		(0x00A4)
#घोषणा CMU_DEVRST0		(0x00A8)
#घोषणा CMU_DEVRST1		(0x00AC)
#घोषणा CMU_USBPLL		(0x00B0)
#घोषणा CMU_ETHERNETPLL		(0x00B4)
#घोषणा CMU_CVBSPLL		(0x00B8)
#घोषणा CMU_SSTSCLK		(0x00C0)

अटल काष्ठा clk_pll_table clk_audio_pll_table[] = अणु
	अणु0, 45158400पूर्ण, अणु1, 49152000पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll_table clk_cvbs_pll_table[] = अणु
	अणु27, 29 * 12000000पूर्ण, अणु28, 30 * 12000000पूर्ण, अणु29, 31 * 12000000पूर्ण,
	अणु30, 32 * 12000000पूर्ण, अणु31, 33 * 12000000पूर्ण, अणु32, 34 * 12000000पूर्ण,
	अणु33, 35 * 12000000पूर्ण, अणु34, 36 * 12000000पूर्ण, अणु35, 37 * 12000000पूर्ण,
	अणु36, 38 * 12000000पूर्ण, अणु37, 39 * 12000000पूर्ण, अणु38, 40 * 12000000पूर्ण,
	अणु39, 41 * 12000000पूर्ण, अणु40, 42 * 12000000पूर्ण, अणु41, 43 * 12000000पूर्ण,
	अणु42, 44 * 12000000पूर्ण, अणु43, 45 * 12000000पूर्ण, अणु0, 0पूर्ण,
पूर्ण;

/* pll घड़ीs */
अटल OWL_PLL_NO_PARENT(clk_core_pll,   "core_pll", CMU_COREPLL, 12000000, 9, 0, 8,  4, 174, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_dev_pll,    "dev_pll", CMU_DEVPLL,  6000000, 8, 0, 8, 8, 126, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_ddr_pll,    "ddr_pll", CMU_DDRPLL, 6000000, 8, 0, 8,  2,  180, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_nand_pll,   "nand_pll", CMU_न_अंकDPLL,  6000000, 8, 0, 8,  2, 86, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_display_pll, "display_pll", CMU_DISPLAYPLL, 6000000, 8, 0, 8, 2, 140, शून्य, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_cvbs_pll, "cvbs_pll", CMU_CVBSPLL, 0, 8, 0, 8, 27, 43, clk_cvbs_pll_table, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_audio_pll,  "audio_pll", CMU_AUDIOPLL, 0, 4, 0, 1, 0, 0, clk_audio_pll_table, CLK_IGNORE_UNUSED);
अटल OWL_PLL_NO_PARENT(clk_ethernet_pll, "ethernet_pll", CMU_ETHERNETPLL, 500000000, 0, 0, 0, 0, 0, शून्य, CLK_IGNORE_UNUSED);

अटल स्थिर अक्षर *cpu_clk_mux_p[] = अणु"losc", "hosc", "core_pll", "noc1_clk_div"पूर्ण;
अटल स्थिर अक्षर *dev_clk_p[] = अणु "hosc", "dev_pll"पूर्ण;
अटल स्थिर अक्षर *noc_clk_mux_p[] = अणु "dev_clk", "display_pll", "nand_pll", "ddr_pll", "cvbs_pll"पूर्ण;

अटल स्थिर अक्षर *csi_clk_mux_p[] = अणु "display_pll", "dev_clk"पूर्ण;
अटल स्थिर अक्षर *de_clk_mux_p[] = अणु "display_pll", "dev_clk"पूर्ण;
अटल स्थिर अक्षर *hde_clk_mux_p[] = अणु "dev_clk", "display_pll", "nand_pll", "ddr_pll"पूर्ण;
अटल स्थिर अक्षर *nand_clk_mux_p[] = अणु "nand_pll", "display_pll", "dev_clk", "ddr_pll"पूर्ण;
अटल स्थिर अक्षर *sd_clk_mux_p[] = अणु "dev_clk", "nand_pll", पूर्ण;
अटल स्थिर अक्षर *uart_clk_mux_p[] = अणु "hosc", "dev_pll"पूर्ण;
अटल स्थिर अक्षर *pwm_clk_mux_p[] = अणु "losc", "hosc"पूर्ण;
अटल स्थिर अक्षर *gpu_clk_mux_p[] = अणु "dev_clk", "display_pll", "nand_pll", "ddr_clk", "cvbs_pll"पूर्ण;
अटल स्थिर अक्षर *lcd_clk_mux_p[] = अणु "display_pll", "dev_clk" पूर्ण;
अटल स्थिर अक्षर *i2s_clk_mux_p[] = अणु "audio_pll" पूर्ण;
अटल स्थिर अक्षर *sensor_clk_mux_p[] = अणु "hosc", "si"पूर्ण;

/* mux घड़ीs */
अटल OWL_MUX(clk_cpu, "cpu_clk", cpu_clk_mux_p,  CMU_BUSCLK, 0, 2, CLK_SET_RATE_PARENT);
अटल OWL_MUX(clk_dev, "dev_clk", dev_clk_p, CMU_DEVPLL, 12, 1, CLK_SET_RATE_PARENT);
अटल OWL_MUX(clk_noc0_clk_mux, "noc0_clk_mux", noc_clk_mux_p, CMU_BUSCLK, 4, 3, CLK_SET_RATE_PARENT);
अटल OWL_MUX(clk_noc1_clk_mux, "noc1_clk_mux", noc_clk_mux_p, CMU_BUSCLK1, 4, 3, CLK_SET_RATE_PARENT);
अटल OWL_MUX(clk_hp_clk_mux, "hp_clk_mux", noc_clk_mux_p, CMU_BUSCLK1, 8, 3, CLK_SET_RATE_PARENT);

अटल काष्ठा clk_factor_table sd_factor_table[] = अणु
	/* bit0 ~ 4 */
	अणु0, 1, 1पूर्ण, अणु1, 1, 2पूर्ण, अणु2, 1, 3पूर्ण, अणु3, 1, 4पूर्ण,
	अणु4, 1, 5पूर्ण, अणु5, 1, 6पूर्ण, अणु6, 1, 7पूर्ण, अणु7, 1, 8पूर्ण,
	अणु8, 1, 9पूर्ण, अणु9, 1, 10पूर्ण, अणु10, 1, 11पूर्ण, अणु11, 1, 12पूर्ण,
	अणु12, 1, 13पूर्ण, अणु13, 1, 14पूर्ण, अणु14, 1, 15पूर्ण, अणु15, 1, 16पूर्ण,
	अणु16, 1, 17पूर्ण, अणु17, 1, 18पूर्ण, अणु18, 1, 19पूर्ण, अणु19, 1, 20पूर्ण,
	अणु20, 1, 21पूर्ण, अणु21, 1, 22पूर्ण, अणु22, 1, 23पूर्ण, अणु23, 1, 24पूर्ण,
	अणु24, 1, 25पूर्ण, अणु25, 1, 26पूर्ण,

	/* bit8: /128 */
	अणु256, 1, 1 * 128पूर्ण, अणु257, 1, 2 * 128पूर्ण, अणु258, 1, 3 * 128पूर्ण, अणु259, 1, 4 * 128पूर्ण,
	अणु260, 1, 5 * 128पूर्ण, अणु261, 1, 6 * 128पूर्ण, अणु262, 1, 7 * 128पूर्ण, अणु263, 1, 8 * 128पूर्ण,
	अणु264, 1, 9 * 128पूर्ण, अणु265, 1, 10 * 128पूर्ण, अणु266, 1, 11 * 128पूर्ण, अणु267, 1, 12 * 128पूर्ण,
	अणु268, 1, 13 * 128पूर्ण, अणु269, 1, 14 * 128पूर्ण, अणु270, 1, 15 * 128पूर्ण, अणु271, 1, 16 * 128पूर्ण,
	अणु272, 1, 17 * 128पूर्ण, अणु273, 1, 18 * 128पूर्ण, अणु274, 1, 19 * 128पूर्ण, अणु275, 1, 20 * 128पूर्ण,
	अणु276, 1, 21 * 128पूर्ण, अणु277, 1, 22 * 128पूर्ण, अणु278, 1, 23 * 128पूर्ण, अणु279, 1, 24 * 128पूर्ण,
	अणु280, 1, 25 * 128पूर्ण, अणु281, 1, 26 * 128पूर्ण,

	अणु0, 0पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table lcd_factor_table[] = अणु
	/* bit0 ~ 3 */
	अणु0, 1, 1पूर्ण, अणु1, 1, 2पूर्ण, अणु2, 1, 3पूर्ण, अणु3, 1, 4पूर्ण,
	अणु4, 1, 5पूर्ण, अणु5, 1, 6पूर्ण, अणु6, 1, 7पूर्ण, अणु7, 1, 8पूर्ण,
	अणु8, 1, 9पूर्ण, अणु9, 1, 10पूर्ण, अणु10, 1, 11पूर्ण, अणु11, 1, 12पूर्ण,

	/* bit8: /7 */
	अणु256, 1, 1 * 7पूर्ण, अणु257, 1, 2 * 7पूर्ण, अणु258, 1, 3 * 7पूर्ण, अणु259, 1, 4 * 7पूर्ण,
	अणु260, 1, 5 * 7पूर्ण, अणु261, 1, 6 * 7पूर्ण, अणु262, 1, 7 * 7पूर्ण, अणु263, 1, 8 * 7पूर्ण,
	अणु264, 1, 9 * 7पूर्ण, अणु265, 1, 10 * 7पूर्ण, अणु266, 1, 11 * 7पूर्ण, अणु267, 1, 12 * 7पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable hdmia_भाग_प्रकारable[] = अणु
	अणु0, 1पूर्ण,   अणु1, 2पूर्ण,   अणु2, 3पूर्ण,   अणु3, 4पूर्ण,
	अणु4, 6पूर्ण,   अणु5, 8पूर्ण,   अणु6, 12पूर्ण,  अणु7, 16पूर्ण,
	अणु8, 24पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable rmii_भाग_प्रकारable[] = अणु
	अणु0, 4पूर्ण,   अणु1, 10पूर्ण,
पूर्ण;

/* भागider घड़ीs */
अटल OWL_DIVIDER(clk_noc0, "noc0_clk", "noc0_clk_mux", CMU_BUSCLK, 16, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_noc1, "noc1_clk", "noc1_clk_mux", CMU_BUSCLK1, 16, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_noc1_clk_भाग, "noc1_clk_div", "noc1_clk", CMU_BUSCLK1, 20, 1, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_hp_clk_भाग, "hp_clk_div", "hp_clk_mux", CMU_BUSCLK1, 12, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_ahb, "ahb_clk", "hp_clk_div", CMU_BUSCLK1, 2, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_apb, "apb_clk", "ahb_clk", CMU_BUSCLK1, 14, 2, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_sensor0, "sensor0", "sensor_src", CMU_SENSORCLK, 0, 4, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_sensor1, "sensor1", "sensor_src", CMU_SENSORCLK, 8, 4, शून्य, 0, 0);
अटल OWL_DIVIDER(clk_rmii_ref, "rmii_ref", "ethernet_pll", CMU_ETHERNETPLL, 2, 1, rmii_भाग_प्रकारable, 0, 0);

अटल काष्ठा clk_factor_table de_factor_table[] = अणु
	अणु0, 1, 1पूर्ण, अणु1, 2, 3पूर्ण, अणु2, 1, 2पूर्ण, अणु3, 2, 5पूर्ण,
	अणु4, 1, 3पूर्ण, अणु5, 1, 4पूर्ण, अणु6, 1, 6पूर्ण, अणु7, 1, 8पूर्ण,
	अणु8, 1, 12पूर्ण, अणु0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा clk_factor_table hde_factor_table[] = अणु
	अणु0, 1, 1पूर्ण, अणु1, 2, 3पूर्ण, अणु2, 1, 2पूर्ण, अणु3, 2, 5पूर्ण,
	अणु4, 1, 3पूर्ण, अणु5, 1, 4पूर्ण, अणु6, 1, 6पूर्ण, अणु7, 1, 8पूर्ण,
	अणु0, 0, 0पूर्ण,
पूर्ण;

/* gate घड़ीs */
अटल OWL_GATE(clk_gpio, "gpio", "apb_clk", CMU_DEVCLKEN1, 25, 0, 0);
अटल OWL_GATE(clk_dmac, "dmac", "hp_clk_div", CMU_DEVCLKEN0, 17, 0, 0);
अटल OWL_GATE(clk_समयr, "timer", "hosc", CMU_DEVCLKEN1, 22, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_dsi, "dsi_clk", CMU_DEVCLKEN0, 2, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_tvout, "tvout_clk", CMU_DEVCLKEN0, 3, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_hdmi_dev, "hdmi_dev", CMU_DEVCLKEN0, 5, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb3_480mpll0, "usb3_480mpll0", CMU_USBPLL, 3, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb3_480mphy0, "usb3_480mphy0", CMU_USBPLL, 2, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb3_5gphy, "usb3_5gphy", CMU_USBPLL, 1, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb3_cce, "usb3_cce", CMU_DEVCLKEN0, 25, 0, 0);
अटल OWL_GATE(clk_i2c0, "i2c0", "hosc", CMU_DEVCLKEN1, 0, 0, 0);
अटल OWL_GATE(clk_i2c1, "i2c1", "hosc", CMU_DEVCLKEN1, 1, 0, 0);
अटल OWL_GATE(clk_i2c2, "i2c2", "hosc", CMU_DEVCLKEN1, 2, 0, 0);
अटल OWL_GATE(clk_i2c3, "i2c3", "hosc", CMU_DEVCLKEN1, 3, 0, 0);
अटल OWL_GATE(clk_spi0, "spi0", "ahb_clk", CMU_DEVCLKEN1, 4, 0, 0);
अटल OWL_GATE(clk_spi1, "spi1", "ahb_clk", CMU_DEVCLKEN1, 5, 0, 0);
अटल OWL_GATE(clk_spi2, "spi2", "ahb_clk", CMU_DEVCLKEN1, 6, 0, 0);
अटल OWL_GATE(clk_spi3, "spi3", "ahb_clk", CMU_DEVCLKEN1, 7, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb2h0_pllen, "usbh0_pllen", CMU_USBPLL, 12, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb2h0_phy, "usbh0_phy", CMU_USBPLL, 10, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb2h0_cce, "usbh0_cce", CMU_DEVCLKEN0, 26, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb2h1_pllen, "usbh1_pllen", CMU_USBPLL, 13, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb2h1_phy, "usbh1_phy", CMU_USBPLL, 11, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_usb2h1_cce, "usbh1_cce", CMU_DEVCLKEN0, 27, 0, 0);
अटल OWL_GATE_NO_PARENT(clk_irc_चयन, "irc_switch", CMU_DEVCLKEN1, 15, 0, 0);

/* composite घड़ीs */

अटल OWL_COMP_DIV(clk_csi, "csi", csi_clk_mux_p,
			OWL_MUX_HW(CMU_CSICLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 13, 0),
			OWL_DIVIDER_HW(CMU_CSICLK, 0, 4, 0, शून्य),
			0);

अटल OWL_COMP_DIV(clk_si, "si", csi_clk_mux_p,
			OWL_MUX_HW(CMU_SICLK, 4, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 14,  0),
			OWL_DIVIDER_HW(CMU_SICLK, 0, 4, 0, शून्य),
			0);

अटल OWL_COMP_FACTOR(clk_de, "de", de_clk_mux_p,
			OWL_MUX_HW(CMU_DECLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 0,  0),
			OWL_FACTOR_HW(CMU_DECLK, 0, 3, 0, de_factor_table),
			0);

अटल OWL_COMP_FACTOR(clk_hde, "hde", hde_clk_mux_p,
			OWL_MUX_HW(CMU_HDECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 9, 0),
			OWL_FACTOR_HW(CMU_HDECLK, 0, 3, 0, hde_factor_table),
			0);

अटल OWL_COMP_FACTOR(clk_vde, "vde", hde_clk_mux_p,
			OWL_MUX_HW(CMU_VDECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 10,  0),
			OWL_FACTOR_HW(CMU_VDECLK, 0, 3, 0, hde_factor_table),
			0);

अटल OWL_COMP_FACTOR(clk_vce, "vce", hde_clk_mux_p,
			OWL_MUX_HW(CMU_VCECLK, 4, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 11, 0),
			OWL_FACTOR_HW(CMU_VCECLK, 0, 3, 0, hde_factor_table),
			0);

अटल OWL_COMP_DIV(clk_nand, "nand", nand_clk_mux_p,
			OWL_MUX_HW(CMU_न_अंकDCCLK, 8, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 21, 0),
			OWL_DIVIDER_HW(CMU_न_अंकDCCLK, 0, 3, 0, शून्य),
			CLK_SET_RATE_PARENT);

अटल OWL_COMP_FACTOR(clk_sd0, "sd0", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD0CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 22, 0),
			OWL_FACTOR_HW(CMU_SD0CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_FACTOR(clk_sd1, "sd1", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD1CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 23, 0),
			OWL_FACTOR_HW(CMU_SD1CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_FACTOR(clk_sd2, "sd2", sd_clk_mux_p,
			OWL_MUX_HW(CMU_SD2CLK, 9, 1),
			OWL_GATE_HW(CMU_DEVCLKEN0, 24, 0),
			OWL_FACTOR_HW(CMU_SD2CLK, 0, 9, 0, sd_factor_table),
			0);

अटल OWL_COMP_DIV(clk_uart0, "uart0", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART0CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 8, 0),
			OWL_DIVIDER_HW(CMU_UART0CLK, 0, 9, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_uart1, "uart1", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART1CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 9, 0),
			OWL_DIVIDER_HW(CMU_UART1CLK, 0, 9, CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_uart2, "uart2", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART2CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 10, 0),
			OWL_DIVIDER_HW(CMU_UART2CLK, 0, 9,  CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_uart3, "uart3", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART3CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 11, 0),
			OWL_DIVIDER_HW(CMU_UART3CLK, 0, 9,  CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_uart4, "uart4", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART4CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 12, 0),
			OWL_DIVIDER_HW(CMU_UART4CLK, 0, 9,  CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_uart5, "uart5", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART5CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 13, 0),
			OWL_DIVIDER_HW(CMU_UART5CLK, 0, 9,  CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_uart6, "uart6", uart_clk_mux_p,
			OWL_MUX_HW(CMU_UART6CLK, 16, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 14, 0),
			OWL_DIVIDER_HW(CMU_UART6CLK, 0, 9,  CLK_DIVIDER_ROUND_CLOSEST, शून्य),
			0);

अटल OWL_COMP_DIV(clk_pwm0, "pwm0", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM0CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 16, 0),
			OWL_DIVIDER_HW(CMU_PWM0CLK, 0, 10, 0, शून्य),
			CLK_IGNORE_UNUSED);

अटल OWL_COMP_DIV(clk_pwm1, "pwm1", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM1CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 17, 0),
			OWL_DIVIDER_HW(CMU_PWM1CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(clk_pwm2, "pwm2", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM2CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 18, 0),
			OWL_DIVIDER_HW(CMU_PWM2CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(clk_pwm3, "pwm3", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM3CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 19, 0),
			OWL_DIVIDER_HW(CMU_PWM3CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(clk_pwm4, "pwm4", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM4CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 20, 0),
			OWL_DIVIDER_HW(CMU_PWM4CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_DIV(clk_pwm5, "pwm5", pwm_clk_mux_p,
			OWL_MUX_HW(CMU_PWM5CLK, 12, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 21, 0),
			OWL_DIVIDER_HW(CMU_PWM5CLK, 0, 10, 0, शून्य),
			0);

अटल OWL_COMP_FACTOR(clk_gpu3d, "gpu3d", gpu_clk_mux_p,
			OWL_MUX_HW(CMU_GPU3DCLK, 4, 3),
			OWL_GATE_HW(CMU_DEVCLKEN0, 8, 0),
			OWL_FACTOR_HW(CMU_GPU3DCLK, 0, 3, 0, hde_factor_table),
			0);

अटल OWL_COMP_FACTOR(clk_lcd, "lcd", lcd_clk_mux_p,
			OWL_MUX_HW(CMU_LCDCLK, 12, 2),
			OWL_GATE_HW(CMU_DEVCLKEN0, 1, 0),
			OWL_FACTOR_HW(CMU_LCDCLK, 0, 9, 0, lcd_factor_table),
			0);

अटल OWL_COMP_DIV(clk_hdmi_audio, "hdmia", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1), /*CMU_AUDIOPLL 24,1 unused*/
			OWL_GATE_HW(CMU_DEVCLKEN1, 28, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 24, 4, 0, hdmia_भाग_प्रकारable),
			0);

अटल OWL_COMP_DIV(clk_i2srx, "i2srx", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 27, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 20, 4, 0, hdmia_भाग_प्रकारable),
			0);

अटल OWL_COMP_DIV(clk_i2stx, "i2stx", i2s_clk_mux_p,
			OWL_MUX_HW(CMU_AUDIOPLL, 24, 1),
			OWL_GATE_HW(CMU_DEVCLKEN1, 26, 0),
			OWL_DIVIDER_HW(CMU_AUDIOPLL, 16, 4, 0, hdmia_भाग_प्रकारable),
			0);

/* क्रम bluetooth pcm communication */
अटल OWL_COMP_FIXED_FACTOR(clk_pcm1, "pcm1", "audio_pll",
			OWL_GATE_HW(CMU_DEVCLKEN1, 31, 0),
			1, 2, 0);

अटल OWL_COMP_DIV(clk_sensor_src, "sensor_src", sensor_clk_mux_p,
			OWL_MUX_HW(CMU_SENSORCLK, 4, 1),
			अणु0पूर्ण,
			OWL_DIVIDER_HW(CMU_SENSORCLK, 5, 2, 0, शून्य),
			0);

अटल OWL_COMP_FIXED_FACTOR(clk_ethernet, "ethernet", "ethernet_pll",
			OWL_GATE_HW(CMU_DEVCLKEN1, 23, 0),
			1, 20, 0);

अटल OWL_COMP_DIV_FIXED(clk_thermal_sensor, "thermal_sensor", "hosc",
				OWL_GATE_HW(CMU_DEVCLKEN0, 31, 0),
				OWL_DIVIDER_HW(CMU_SSTSCLK, 20, 10, 0, शून्य),
				0);

अटल काष्ठा owl_clk_common *s700_clks[] = अणु
	&clk_core_pll.common,
	&clk_dev_pll.common,
	&clk_ddr_pll.common,
	&clk_nand_pll.common,
	&clk_display_pll.common,
	&clk_cvbs_pll .common,
	&clk_audio_pll.common,
	&clk_ethernet_pll.common,
	&clk_cpu.common,
	&clk_dev.common,
	&clk_ahb.common,
	&clk_apb.common,
	&clk_dmac.common,
	&clk_noc0_clk_mux.common,
	&clk_noc1_clk_mux.common,
	&clk_hp_clk_mux.common,
	&clk_hp_clk_भाग.common,
	&clk_noc1_clk_भाग.common,
	&clk_noc0.common,
	&clk_noc1.common,
	&clk_sensor_src.common,
	&clk_gpio.common,
	&clk_समयr.common,
	&clk_dsi.common,
	&clk_csi.common,
	&clk_si.common,
	&clk_de.common,
	&clk_hde.common,
	&clk_vde.common,
	&clk_vce.common,
	&clk_nand.common,
	&clk_sd0.common,
	&clk_sd1.common,
	&clk_sd2.common,
	&clk_uart0.common,
	&clk_uart1.common,
	&clk_uart2.common,
	&clk_uart3.common,
	&clk_uart4.common,
	&clk_uart5.common,
	&clk_uart6.common,
	&clk_pwm0.common,
	&clk_pwm1.common,
	&clk_pwm2.common,
	&clk_pwm3.common,
	&clk_pwm4.common,
	&clk_pwm5.common,
	&clk_gpu3d.common,
	&clk_i2c0.common,
	&clk_i2c1.common,
	&clk_i2c2.common,
	&clk_i2c3.common,
	&clk_spi0.common,
	&clk_spi1.common,
	&clk_spi2.common,
	&clk_spi3.common,
	&clk_usb3_480mpll0.common,
	&clk_usb3_480mphy0.common,
	&clk_usb3_5gphy.common,
	&clk_usb3_cce.common,
	&clk_lcd.common,
	&clk_hdmi_audio.common,
	&clk_i2srx.common,
	&clk_i2stx.common,
	&clk_sensor0.common,
	&clk_sensor1.common,
	&clk_hdmi_dev.common,
	&clk_ethernet.common,
	&clk_rmii_ref.common,
	&clk_usb2h0_pllen.common,
	&clk_usb2h0_phy.common,
	&clk_usb2h0_cce.common,
	&clk_usb2h1_pllen.common,
	&clk_usb2h1_phy.common,
	&clk_usb2h1_cce.common,
	&clk_tvout.common,
	&clk_thermal_sensor.common,
	&clk_irc_चयन.common,
	&clk_pcm1.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data s700_hw_clks = अणु
	.hws    = अणु
			[CLK_CORE_PLL]				= &clk_core_pll.common.hw,
			[CLK_DEV_PLL]				= &clk_dev_pll.common.hw,
			[CLK_DDR_PLL]				= &clk_ddr_pll.common.hw,
			[CLK_न_अंकD_PLL]				= &clk_nand_pll.common.hw,
			[CLK_DISPLAY_PLL]			= &clk_display_pll.common.hw,
			[CLK_CVBS_PLL]				= &clk_cvbs_pll .common.hw,
			[CLK_AUDIO_PLL]				= &clk_audio_pll.common.hw,
			[CLK_ETHERNET_PLL]			= &clk_ethernet_pll.common.hw,
			[CLK_CPU]				= &clk_cpu.common.hw,
			[CLK_DEV]				= &clk_dev.common.hw,
			[CLK_AHB]				= &clk_ahb.common.hw,
			[CLK_APB]				= &clk_apb.common.hw,
			[CLK_DMAC]				= &clk_dmac.common.hw,
			[CLK_NOC0_CLK_MUX]			= &clk_noc0_clk_mux.common.hw,
			[CLK_NOC1_CLK_MUX]			= &clk_noc1_clk_mux.common.hw,
			[CLK_HP_CLK_MUX]			= &clk_hp_clk_mux.common.hw,
			[CLK_HP_CLK_DIV]			= &clk_hp_clk_भाग.common.hw,
			[CLK_NOC1_CLK_DIV]			= &clk_noc1_clk_भाग.common.hw,
			[CLK_NOC0]				= &clk_noc0.common.hw,
			[CLK_NOC1]				= &clk_noc1.common.hw,
			[CLK_SENOR_SRC]				= &clk_sensor_src.common.hw,
			[CLK_GPIO]				= &clk_gpio.common.hw,
			[CLK_TIMER]				= &clk_समयr.common.hw,
			[CLK_DSI]				= &clk_dsi.common.hw,
			[CLK_CSI]				= &clk_csi.common.hw,
			[CLK_SI]				= &clk_si.common.hw,
			[CLK_DE]				= &clk_de.common.hw,
			[CLK_HDE]				= &clk_hde.common.hw,
			[CLK_VDE]				= &clk_vde.common.hw,
			[CLK_VCE]				= &clk_vce.common.hw,
			[CLK_न_अंकD]				= &clk_nand.common.hw,
			[CLK_SD0]				= &clk_sd0.common.hw,
			[CLK_SD1]				= &clk_sd1.common.hw,
			[CLK_SD2]				= &clk_sd2.common.hw,
			[CLK_UART0]				= &clk_uart0.common.hw,
			[CLK_UART1]				= &clk_uart1.common.hw,
			[CLK_UART2]				= &clk_uart2.common.hw,
			[CLK_UART3]				= &clk_uart3.common.hw,
			[CLK_UART4]				= &clk_uart4.common.hw,
			[CLK_UART5]				= &clk_uart5.common.hw,
			[CLK_UART6]				= &clk_uart6.common.hw,
			[CLK_PWM0]				= &clk_pwm0.common.hw,
			[CLK_PWM1]				= &clk_pwm1.common.hw,
			[CLK_PWM2]				= &clk_pwm2.common.hw,
			[CLK_PWM3]				= &clk_pwm3.common.hw,
			[CLK_PWM4]				= &clk_pwm4.common.hw,
			[CLK_PWM5]				= &clk_pwm5.common.hw,
			[CLK_GPU3D]				= &clk_gpu3d.common.hw,
			[CLK_I2C0]				= &clk_i2c0.common.hw,
			[CLK_I2C1]				= &clk_i2c1.common.hw,
			[CLK_I2C2]				= &clk_i2c2.common.hw,
			[CLK_I2C3]				= &clk_i2c3.common.hw,
			[CLK_SPI0]				= &clk_spi0.common.hw,
			[CLK_SPI1]				= &clk_spi1.common.hw,
			[CLK_SPI2]				= &clk_spi2.common.hw,
			[CLK_SPI3]				= &clk_spi3.common.hw,
			[CLK_USB3_480MPLL0]			= &clk_usb3_480mpll0.common.hw,
			[CLK_USB3_480MPHY0]			= &clk_usb3_480mphy0.common.hw,
			[CLK_USB3_5GPHY]			= &clk_usb3_5gphy.common.hw,
			[CLK_USB3_CCE]				= &clk_usb3_cce.common.hw,
			[CLK_LCD]				= &clk_lcd.common.hw,
			[CLK_HDMI_AUDIO]			= &clk_hdmi_audio.common.hw,
			[CLK_I2SRX]				= &clk_i2srx.common.hw,
			[CLK_I2STX]				= &clk_i2stx.common.hw,
			[CLK_SENSOR0]				= &clk_sensor0.common.hw,
			[CLK_SENSOR1]				= &clk_sensor1.common.hw,
			[CLK_HDMI_DEV]				= &clk_hdmi_dev.common.hw,
			[CLK_ETHERNET]				= &clk_ethernet.common.hw,
			[CLK_RMII_REF]				= &clk_rmii_ref.common.hw,
			[CLK_USB2H0_PLLEN]			= &clk_usb2h0_pllen.common.hw,
			[CLK_USB2H0_PHY]			= &clk_usb2h0_phy.common.hw,
			[CLK_USB2H0_CCE]			= &clk_usb2h0_cce.common.hw,
			[CLK_USB2H1_PLLEN]			= &clk_usb2h1_pllen.common.hw,
			[CLK_USB2H1_PHY]			= &clk_usb2h1_phy.common.hw,
			[CLK_USB2H1_CCE]			= &clk_usb2h1_cce.common.hw,
			[CLK_TVOUT]				= &clk_tvout.common.hw,
			[CLK_THERMAL_SENSOR]			= &clk_thermal_sensor.common.hw,
			[CLK_IRC_SWITCH]			= &clk_irc_चयन.common.hw,
			[CLK_PCM1]				= &clk_pcm1.common.hw,
		पूर्ण,
		.num    = CLK_NR_CLKS,
पूर्ण;

अटल स्थिर काष्ठा owl_reset_map s700_resets[] = अणु
	[RESET_DE]	= अणु CMU_DEVRST0, BIT(0) पूर्ण,
	[RESET_LCD0]	= अणु CMU_DEVRST0, BIT(1) पूर्ण,
	[RESET_DSI]	= अणु CMU_DEVRST0, BIT(2) पूर्ण,
	[RESET_CSI]	= अणु CMU_DEVRST0, BIT(13) पूर्ण,
	[RESET_SI]	= अणु CMU_DEVRST0, BIT(14) पूर्ण,
	[RESET_I2C0]	= अणु CMU_DEVRST1, BIT(0) पूर्ण,
	[RESET_I2C1]	= अणु CMU_DEVRST1, BIT(1) पूर्ण,
	[RESET_I2C2]	= अणु CMU_DEVRST1, BIT(2) पूर्ण,
	[RESET_I2C3]	= अणु CMU_DEVRST1, BIT(3) पूर्ण,
	[RESET_SPI0]	= अणु CMU_DEVRST1, BIT(4) पूर्ण,
	[RESET_SPI1]	= अणु CMU_DEVRST1, BIT(5) पूर्ण,
	[RESET_SPI2]	= अणु CMU_DEVRST1, BIT(6) पूर्ण,
	[RESET_SPI3]	= अणु CMU_DEVRST1, BIT(7) पूर्ण,
	[RESET_UART0]	= अणु CMU_DEVRST1, BIT(8) पूर्ण,
	[RESET_UART1]	= अणु CMU_DEVRST1, BIT(9) पूर्ण,
	[RESET_UART2]	= अणु CMU_DEVRST1, BIT(10) पूर्ण,
	[RESET_UART3]	= अणु CMU_DEVRST1, BIT(11) पूर्ण,
	[RESET_UART4]	= अणु CMU_DEVRST1, BIT(12) पूर्ण,
	[RESET_UART5]	= अणु CMU_DEVRST1, BIT(13) पूर्ण,
	[RESET_UART6]	= अणु CMU_DEVRST1, BIT(14) पूर्ण,
	[RESET_KEY]	= अणु CMU_DEVRST1, BIT(24) पूर्ण,
	[RESET_GPIO]	= अणु CMU_DEVRST1, BIT(25) पूर्ण,
	[RESET_AUDIO]	= अणु CMU_DEVRST1, BIT(29) पूर्ण,
पूर्ण;

अटल काष्ठा owl_clk_desc s700_clk_desc = अणु
	.clks       = s700_clks,
	.num_clks   = ARRAY_SIZE(s700_clks),

	.hw_clks    = &s700_hw_clks,

	.resets     = s700_resets,
	.num_resets = ARRAY_SIZE(s700_resets),
पूर्ण;

अटल पूर्णांक s700_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_clk_desc *desc;
	काष्ठा owl_reset *reset;
	पूर्णांक ret;

	desc = &s700_clk_desc;
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

अटल स्थिर काष्ठा of_device_id s700_clk_of_match[] = अणु
	अणु .compatible = "actions,s700-cmu", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver s700_clk_driver = अणु
	.probe = s700_clk_probe,
	.driver = अणु
		.name = "s700-cmu",
		.of_match_table = s700_clk_of_match
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init s700_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s700_clk_driver);
पूर्ण
core_initcall(s700_clk_init);
