<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Owen Chen <owen.chen@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"
#समावेश "clk-mux.h"

#समावेश <dt-bindings/घड़ी/mt6765-clk.h>

/*fmeter भाग select 4*/
#घोषणा _DIV4_ 1

अटल DEFINE_SPINLOCK(mt6765_clk_lock);

/* Total 12 subsys */
अटल व्योम __iomem *cksys_base;
अटल व्योम __iomem *apmixed_base;

/* CKSYS */
#घोषणा CLK_SCP_CFG_0		(cksys_base + 0x200)
#घोषणा CLK_SCP_CFG_1		(cksys_base + 0x204)

/* CG */
#घोषणा AP_PLL_CON3		(apmixed_base + 0x0C)
#घोषणा PLLON_CON0		(apmixed_base + 0x44)
#घोषणा PLLON_CON1		(apmixed_base + 0x48)

/* clk cfg update */
#घोषणा CLK_CFG_0		0x40
#घोषणा CLK_CFG_0_SET		0x44
#घोषणा CLK_CFG_0_CLR		0x48
#घोषणा CLK_CFG_1		0x50
#घोषणा CLK_CFG_1_SET		0x54
#घोषणा CLK_CFG_1_CLR		0x58
#घोषणा CLK_CFG_2		0x60
#घोषणा CLK_CFG_2_SET		0x64
#घोषणा CLK_CFG_2_CLR		0x68
#घोषणा CLK_CFG_3		0x70
#घोषणा CLK_CFG_3_SET		0x74
#घोषणा CLK_CFG_3_CLR		0x78
#घोषणा CLK_CFG_4		0x80
#घोषणा CLK_CFG_4_SET		0x84
#घोषणा CLK_CFG_4_CLR		0x88
#घोषणा CLK_CFG_5		0x90
#घोषणा CLK_CFG_5_SET		0x94
#घोषणा CLK_CFG_5_CLR		0x98
#घोषणा CLK_CFG_6		0xa0
#घोषणा CLK_CFG_6_SET		0xa4
#घोषणा CLK_CFG_6_CLR		0xa8
#घोषणा CLK_CFG_7		0xb0
#घोषणा CLK_CFG_7_SET		0xb4
#घोषणा CLK_CFG_7_CLR		0xb8
#घोषणा CLK_CFG_8		0xc0
#घोषणा CLK_CFG_8_SET		0xc4
#घोषणा CLK_CFG_8_CLR		0xc8
#घोषणा CLK_CFG_9		0xd0
#घोषणा CLK_CFG_9_SET		0xd4
#घोषणा CLK_CFG_9_CLR		0xd8
#घोषणा CLK_CFG_10		0xe0
#घोषणा CLK_CFG_10_SET		0xe4
#घोषणा CLK_CFG_10_CLR		0xe8
#घोषणा CLK_CFG_UPDATE		0x004

अटल स्थिर काष्ठा mtk_fixed_clk fixed_clks[] = अणु
	FIXED_CLK(CLK_TOP_F_FRTC, "f_frtc_ck", "clk32k", 32768),
	FIXED_CLK(CLK_TOP_CLK26M, "clk_26m_ck", "clk26m", 26000000),
	FIXED_CLK(CLK_TOP_DMPLL, "dmpll_ck", शून्य, 466000000),
पूर्ण;

अटल स्थिर काष्ठा mtk_fixed_factor top_भागs[] = अणु
	FACTOR(CLK_TOP_SYSPLL, "syspll_ck", "mainpll", 1, 1),
	FACTOR(CLK_TOP_SYSPLL_D2, "syspll_d2", "mainpll", 1, 2),
	FACTOR(CLK_TOP_SYSPLL1_D2, "syspll1_d2", "syspll_d2", 1, 2),
	FACTOR(CLK_TOP_SYSPLL1_D4, "syspll1_d4", "syspll_d2", 1, 4),
	FACTOR(CLK_TOP_SYSPLL1_D8, "syspll1_d8", "syspll_d2", 1, 8),
	FACTOR(CLK_TOP_SYSPLL1_D16, "syspll1_d16", "syspll_d2", 1, 16),
	FACTOR(CLK_TOP_SYSPLL_D3, "syspll_d3", "mainpll", 1, 3),
	FACTOR(CLK_TOP_SYSPLL2_D2, "syspll2_d2", "syspll_d3", 1, 2),
	FACTOR(CLK_TOP_SYSPLL2_D4, "syspll2_d4", "syspll_d3", 1, 4),
	FACTOR(CLK_TOP_SYSPLL2_D8, "syspll2_d8", "syspll_d3", 1, 8),
	FACTOR(CLK_TOP_SYSPLL_D5, "syspll_d5", "mainpll", 1, 5),
	FACTOR(CLK_TOP_SYSPLL3_D2, "syspll3_d2", "syspll_d5", 1, 2),
	FACTOR(CLK_TOP_SYSPLL3_D4, "syspll3_d4", "syspll_d5", 1, 4),
	FACTOR(CLK_TOP_SYSPLL_D7, "syspll_d7", "mainpll", 1, 7),
	FACTOR(CLK_TOP_SYSPLL4_D2, "syspll4_d2", "syspll_d7", 1, 2),
	FACTOR(CLK_TOP_SYSPLL4_D4, "syspll4_d4", "syspll_d7", 1, 4),
	FACTOR(CLK_TOP_UNIVPLL, "univpll", "univ2pll", 1, 2),
	FACTOR(CLK_TOP_USB20_192M, "usb20_192m_ck", "univpll", 2, 13),
	FACTOR(CLK_TOP_USB20_192M_D4, "usb20_192m_d4", "usb20_192m_ck", 1, 4),
	FACTOR(CLK_TOP_USB20_192M_D8, "usb20_192m_d8", "usb20_192m_ck", 1, 8),
	FACTOR(CLK_TOP_USB20_192M_D16,
	       "usb20_192m_d16", "usb20_192m_ck", 1, 16),
	FACTOR(CLK_TOP_USB20_192M_D32,
	       "usb20_192m_d32", "usb20_192m_ck", 1, 32),
	FACTOR(CLK_TOP_UNIVPLL_D2, "univpll_d2", "univpll", 1, 2),
	FACTOR(CLK_TOP_UNIVPLL1_D2, "univpll1_d2", "univpll_d2", 1, 2),
	FACTOR(CLK_TOP_UNIVPLL1_D4, "univpll1_d4", "univpll_d2", 1, 4),
	FACTOR(CLK_TOP_UNIVPLL_D3, "univpll_d3", "univpll", 1, 3),
	FACTOR(CLK_TOP_UNIVPLL2_D2, "univpll2_d2", "univpll_d3", 1, 2),
	FACTOR(CLK_TOP_UNIVPLL2_D4, "univpll2_d4", "univpll_d3", 1, 4),
	FACTOR(CLK_TOP_UNIVPLL2_D8, "univpll2_d8", "univpll_d3", 1, 8),
	FACTOR(CLK_TOP_UNIVPLL2_D32, "univpll2_d32", "univpll_d3", 1, 32),
	FACTOR(CLK_TOP_UNIVPLL_D5, "univpll_d5", "univpll", 1, 5),
	FACTOR(CLK_TOP_UNIVPLL3_D2, "univpll3_d2", "univpll_d5", 1, 2),
	FACTOR(CLK_TOP_UNIVPLL3_D4, "univpll3_d4", "univpll_d5", 1, 4),
	FACTOR(CLK_TOP_MMPLL, "mmpll_ck", "mmpll", 1, 1),
	FACTOR(CLK_TOP_MMPLL_D2, "mmpll_d2", "mmpll_ck", 1, 2),
	FACTOR(CLK_TOP_MPLL, "mpll_ck", "mpll", 1, 1),
	FACTOR(CLK_TOP_DA_MPLL_104M_DIV, "mpll_104m_div", "mpll_ck", 1, 2),
	FACTOR(CLK_TOP_DA_MPLL_52M_DIV, "mpll_52m_div", "mpll_ck", 1, 4),
	FACTOR(CLK_TOP_MFGPLL, "mfgpll_ck", "mfgpll", 1, 1),
	FACTOR(CLK_TOP_MSDCPLL, "msdcpll_ck", "msdcpll", 1, 1),
	FACTOR(CLK_TOP_MSDCPLL_D2, "msdcpll_d2", "msdcpll_ck", 1, 2),
	FACTOR(CLK_TOP_APLL1, "apll1_ck", "apll1", 1, 1),
	FACTOR(CLK_TOP_APLL1_D2, "apll1_d2", "apll1_ck", 1, 2),
	FACTOR(CLK_TOP_APLL1_D4, "apll1_d4", "apll1_ck", 1, 4),
	FACTOR(CLK_TOP_APLL1_D8, "apll1_d8", "apll1_ck", 1, 8),
	FACTOR(CLK_TOP_ULPOSC1, "ulposc1_ck", "ulposc1", 1, 1),
	FACTOR(CLK_TOP_ULPOSC1_D2, "ulposc1_d2", "ulposc1_ck", 1, 2),
	FACTOR(CLK_TOP_ULPOSC1_D4, "ulposc1_d4", "ulposc1_ck", 1, 4),
	FACTOR(CLK_TOP_ULPOSC1_D8, "ulposc1_d8", "ulposc1_ck", 1, 8),
	FACTOR(CLK_TOP_ULPOSC1_D16, "ulposc1_d16", "ulposc1_ck", 1, 16),
	FACTOR(CLK_TOP_ULPOSC1_D32, "ulposc1_d32", "ulposc1_ck", 1, 32),
	FACTOR(CLK_TOP_F_F26M, "f_f26m_ck", "clk_26m_ck", 1, 1),
	FACTOR(CLK_TOP_AXI, "axi_ck", "axi_sel", 1, 1),
	FACTOR(CLK_TOP_MM, "mm_ck", "mm_sel", 1, 1),
	FACTOR(CLK_TOP_SCP, "scp_ck", "scp_sel", 1, 1),
	FACTOR(CLK_TOP_MFG, "mfg_ck", "mfg_sel", 1, 1),
	FACTOR(CLK_TOP_F_FUART, "f_fuart_ck", "uart_sel", 1, 1),
	FACTOR(CLK_TOP_SPI, "spi_ck", "spi_sel", 1, 1),
	FACTOR(CLK_TOP_MSDC50_0, "msdc50_0_ck", "msdc50_0_sel", 1, 1),
	FACTOR(CLK_TOP_MSDC30_1, "msdc30_1_ck", "msdc30_1_sel", 1, 1),
	FACTOR(CLK_TOP_AUDIO, "audio_ck", "audio_sel", 1, 1),
	FACTOR(CLK_TOP_AUD_1, "aud_1_ck", "aud_1_sel", 1, 1),
	FACTOR(CLK_TOP_AUD_ENGEN1, "aud_engen1_ck", "aud_engen1_sel", 1, 1),
	FACTOR(CLK_TOP_F_FDISP_PWM, "f_fdisp_pwm_ck", "disp_pwm_sel", 1, 1),
	FACTOR(CLK_TOP_SSPM, "sspm_ck", "sspm_sel", 1, 1),
	FACTOR(CLK_TOP_DXCC, "dxcc_ck", "dxcc_sel", 1, 1),
	FACTOR(CLK_TOP_I2C, "i2c_ck", "i2c_sel", 1, 1),
	FACTOR(CLK_TOP_F_FPWM, "f_fpwm_ck", "pwm_sel", 1, 1),
	FACTOR(CLK_TOP_F_FSENINF, "f_fseninf_ck", "seninf_sel", 1, 1),
	FACTOR(CLK_TOP_AES_FDE, "aes_fde_ck", "aes_fde_sel", 1, 1),
	FACTOR(CLK_TOP_F_BIST2FPC, "f_bist2fpc_ck", "univpll2_d2", 1, 1),
	FACTOR(CLK_TOP_ARMPLL_DIVIDER_PLL0, "arm_div_pll0", "syspll_d2", 1, 1),
	FACTOR(CLK_TOP_ARMPLL_DIVIDER_PLL1, "arm_div_pll1", "syspll_ck", 1, 1),
	FACTOR(CLK_TOP_ARMPLL_DIVIDER_PLL2, "arm_div_pll2", "univpll_d2", 1, 1),
	FACTOR(CLK_TOP_DA_USB20_48M_DIV,
	       "usb20_48m_div", "usb20_192m_d4", 1, 1),
	FACTOR(CLK_TOP_DA_UNIV_48M_DIV, "univ_48m_div", "usb20_192m_d4", 1, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर axi_parents[] = अणु
	"clk26m",
	"syspll_d7",
	"syspll1_d4",
	"syspll3_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mem_parents[] = अणु
	"clk26m",
	"dmpll_ck",
	"apll1_ck"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mm_parents[] = अणु
	"clk26m",
	"mmpll_ck",
	"syspll1_d2",
	"syspll_d5",
	"syspll1_d4",
	"univpll_d5",
	"univpll1_d2",
	"mmpll_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर scp_parents[] = अणु
	"clk26m",
	"syspll4_d2",
	"univpll2_d2",
	"syspll1_d2",
	"univpll1_d2",
	"syspll_d3",
	"univpll_d3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mfg_parents[] = अणु
	"clk26m",
	"mfgpll_ck",
	"syspll_d3",
	"univpll_d3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर atb_parents[] = अणु
	"clk26m",
	"syspll1_d4",
	"syspll1_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर camtg_parents[] = अणु
	"clk26m",
	"usb20_192m_d8",
	"univpll2_d8",
	"usb20_192m_d4",
	"univpll2_d32",
	"usb20_192m_d16",
	"usb20_192m_d32"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_parents[] = अणु
	"clk26m",
	"univpll2_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_parents[] = अणु
	"clk26m",
	"syspll3_d2",
	"syspll4_d2",
	"syspll2_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर msdc5hclk_parents[] = अणु
	"clk26m",
	"syspll1_d2",
	"univpll1_d4",
	"syspll2_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर msdc50_0_parents[] = अणु
	"clk26m",
	"msdcpll_ck",
	"syspll2_d2",
	"syspll4_d2",
	"univpll1_d2",
	"syspll1_d2",
	"univpll_d5",
	"univpll1_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर msdc30_1_parents[] = अणु
	"clk26m",
	"msdcpll_d2",
	"univpll2_d2",
	"syspll2_d2",
	"syspll1_d4",
	"univpll1_d4",
	"usb20_192m_d4",
	"syspll2_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_parents[] = अणु
	"clk26m",
	"syspll3_d4",
	"syspll4_d4",
	"syspll1_d16"
पूर्ण;

अटल स्थिर अक्षर * स्थिर aud_पूर्णांकbus_parents[] = अणु
	"clk26m",
	"syspll1_d4",
	"syspll4_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर aud_1_parents[] = अणु
	"clk26m",
	"apll1_ck"
पूर्ण;

अटल स्थिर अक्षर * स्थिर aud_engen1_parents[] = अणु
	"clk26m",
	"apll1_d2",
	"apll1_d4",
	"apll1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर disp_pwm_parents[] = अणु
	"clk26m",
	"univpll2_d4",
	"ulposc1_d2",
	"ulposc1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sspm_parents[] = अणु
	"clk26m",
	"syspll1_d2",
	"syspll_d3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर dxcc_parents[] = अणु
	"clk26m",
	"syspll1_d2",
	"syspll1_d4",
	"syspll1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_top_parents[] = अणु
	"clk26m",
	"univpll3_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spm_parents[] = अणु
	"clk26m",
	"syspll1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_parents[] = अणु
	"clk26m",
	"univpll3_d4",
	"univpll3_d2",
	"syspll1_d8",
	"syspll2_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_parents[] = अणु
	"clk26m",
	"univpll3_d4",
	"syspll1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर seninf_parents[] = अणु
	"clk26m",
	"univpll1_d4",
	"univpll1_d2",
	"univpll2_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर aes_fde_parents[] = अणु
	"clk26m",
	"msdcpll_ck",
	"univpll_d3",
	"univpll2_d2",
	"univpll1_d2",
	"syspll1_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ulposc_parents[] = अणु
	"clk26m",
	"ulposc1_d4",
	"ulposc1_d8",
	"ulposc1_d16",
	"ulposc1_d32"
पूर्ण;

अटल स्थिर अक्षर * स्थिर camपंचांग_parents[] = अणु
	"clk26m",
	"univpll1_d4",
	"univpll1_d2",
	"univpll2_d2"
पूर्ण;

#घोषणा INVALID_UPDATE_REG 0xFFFFFFFF
#घोषणा INVALID_UPDATE_SHIFT -1
#घोषणा INVALID_MUX_GATE -1

अटल स्थिर काष्ठा mtk_mux top_muxes[] = अणु
	/* CLK_CFG_0 */
	MUX_GATE_CLR_SET_UPD_FLAGS(CLK_TOP_AXI_SEL, "axi_sel", axi_parents,
			      CLK_CFG_0, CLK_CFG_0_SET, CLK_CFG_0_CLR,
			      0, 2, 7, CLK_CFG_UPDATE, 0, CLK_IS_CRITICAL),
	MUX_GATE_CLR_SET_UPD_FLAGS(CLK_TOP_MEM_SEL, "mem_sel", mem_parents,
			      CLK_CFG_0, CLK_CFG_0_SET, CLK_CFG_0_CLR,
			      8, 2, 15, CLK_CFG_UPDATE, 1, CLK_IS_CRITICAL),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_MM_SEL, "mm_sel", mm_parents, CLK_CFG_0,
			CLK_CFG_0_SET, CLK_CFG_0_CLR, 16, 3, 23,
			CLK_CFG_UPDATE, 2),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_SCP_SEL, "scp_sel", scp_parents, CLK_CFG_0,
			CLK_CFG_0_SET, CLK_CFG_0_CLR, 24, 3, 31,
			CLK_CFG_UPDATE, 3),
	/* CLK_CFG_1 */
	MUX_GATE_CLR_SET_UPD(CLK_TOP_MFG_SEL, "mfg_sel", mfg_parents, CLK_CFG_1,
			CLK_CFG_1_SET, CLK_CFG_1_CLR, 0, 2, 7,
			CLK_CFG_UPDATE, 4),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_ATB_SEL, "atb_sel", atb_parents, CLK_CFG_1,
			CLK_CFG_1_SET, CLK_CFG_1_CLR, 8, 2, 15,
			CLK_CFG_UPDATE, 5),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_CAMTG_SEL, "camtg_sel",
			camtg_parents, CLK_CFG_1, CLK_CFG_1_SET,
			CLK_CFG_1_CLR, 16, 3, 23, CLK_CFG_UPDATE, 6),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_CAMTG1_SEL, "camtg1_sel", camtg_parents,
			CLK_CFG_1, CLK_CFG_1_SET, CLK_CFG_1_CLR,
			24, 3, 31, CLK_CFG_UPDATE, 7),
	/* CLK_CFG_2 */
	MUX_GATE_CLR_SET_UPD(CLK_TOP_CAMTG2_SEL, "camtg2_sel",
			camtg_parents, CLK_CFG_2, CLK_CFG_2_SET,
			CLK_CFG_2_CLR, 0, 3, 7, CLK_CFG_UPDATE, 8),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_CAMTG3_SEL, "camtg3_sel", camtg_parents,
			CLK_CFG_2, CLK_CFG_2_SET, CLK_CFG_2_CLR,
			8, 3, 15, CLK_CFG_UPDATE, 9),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_UART_SEL, "uart_sel", uart_parents,
			CLK_CFG_2, CLK_CFG_2_SET, CLK_CFG_2_CLR, 16, 1, 23,
			CLK_CFG_UPDATE, 10),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_SPI_SEL, "spi_sel", spi_parents, CLK_CFG_2,
			CLK_CFG_2_SET, CLK_CFG_2_CLR, 24, 2, 31,
			CLK_CFG_UPDATE, 11),
	/* CLK_CFG_3 */
	MUX_GATE_CLR_SET_UPD(CLK_TOP_MSDC50_0_HCLK_SEL, "msdc5hclk",
			msdc5hclk_parents, CLK_CFG_3, CLK_CFG_3_SET,
			CLK_CFG_3_CLR, 0, 2, 7, CLK_CFG_UPDATE, 12),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_MSDC50_0_SEL, "msdc50_0_sel",
			msdc50_0_parents, CLK_CFG_3, CLK_CFG_3_SET,
			CLK_CFG_3_CLR, 8, 3, 15, CLK_CFG_UPDATE, 13),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_MSDC30_1_SEL, "msdc30_1_sel",
			msdc30_1_parents, CLK_CFG_3, CLK_CFG_3_SET,
			CLK_CFG_3_CLR, 16, 3, 23, CLK_CFG_UPDATE, 14),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_AUDIO_SEL, "audio_sel", audio_parents,
			CLK_CFG_3, CLK_CFG_3_SET, CLK_CFG_3_CLR,
			24, 2, 31, CLK_CFG_UPDATE, 15),
	/* CLK_CFG_4 */
	MUX_GATE_CLR_SET_UPD(CLK_TOP_AUD_INTBUS_SEL, "aud_intbus_sel",
			aud_पूर्णांकbus_parents, CLK_CFG_4, CLK_CFG_4_SET,
			CLK_CFG_4_CLR, 0, 2, 7, CLK_CFG_UPDATE, 16),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_AUD_1_SEL, "aud_1_sel", aud_1_parents,
			CLK_CFG_4, CLK_CFG_4_SET, CLK_CFG_4_CLR,
			8, 1, 15, CLK_CFG_UPDATE, 17),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_AUD_ENGEN1_SEL, "aud_engen1_sel",
			aud_engen1_parents, CLK_CFG_4, CLK_CFG_4_SET,
			CLK_CFG_4_CLR, 16, 2, 23, CLK_CFG_UPDATE, 18),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_DISP_PWM_SEL, "disp_pwm_sel",
			disp_pwm_parents, CLK_CFG_4, CLK_CFG_4_SET,
			CLK_CFG_4_CLR, 24, 2, 31, CLK_CFG_UPDATE, 19),
	/* CLK_CFG_5 */
	MUX_GATE_CLR_SET_UPD(CLK_TOP_SSPM_SEL, "sspm_sel", sspm_parents,
			CLK_CFG_5, CLK_CFG_5_SET, CLK_CFG_5_CLR, 0, 2, 7,
			CLK_CFG_UPDATE, 20),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_DXCC_SEL, "dxcc_sel", dxcc_parents,
			CLK_CFG_5, CLK_CFG_5_SET, CLK_CFG_5_CLR, 8, 2, 15,
			CLK_CFG_UPDATE, 21),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_USB_TOP_SEL, "usb_top_sel",
			usb_top_parents, CLK_CFG_5, CLK_CFG_5_SET,
			CLK_CFG_5_CLR, 16, 1, 23, CLK_CFG_UPDATE, 22),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_SPM_SEL, "spm_sel", spm_parents, CLK_CFG_5,
			CLK_CFG_5_SET, CLK_CFG_5_CLR, 24, 1, 31,
			CLK_CFG_UPDATE, 23),
	/* CLK_CFG_6 */
	MUX_GATE_CLR_SET_UPD(CLK_TOP_I2C_SEL, "i2c_sel", i2c_parents, CLK_CFG_6,
			CLK_CFG_6_SET, CLK_CFG_6_CLR, 0, 3, 7, CLK_CFG_UPDATE,
			24),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_PWM_SEL, "pwm_sel", pwm_parents, CLK_CFG_6,
			CLK_CFG_6_SET, CLK_CFG_6_CLR, 8, 2, 15, CLK_CFG_UPDATE,
			25),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_SENINF_SEL, "seninf_sel", seninf_parents,
			CLK_CFG_6, CLK_CFG_6_SET, CLK_CFG_6_CLR, 16, 2, 23,
			CLK_CFG_UPDATE, 26),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_AES_FDE_SEL, "aes_fde_sel",
			aes_fde_parents, CLK_CFG_6, CLK_CFG_6_SET,
			CLK_CFG_6_CLR, 24, 3, 31, CLK_CFG_UPDATE, 27),
	/* CLK_CFG_7 */
	MUX_GATE_CLR_SET_UPD_FLAGS(CLK_TOP_PWRAP_ULPOSC_SEL, "ulposc_sel",
			      ulposc_parents, CLK_CFG_7, CLK_CFG_7_SET,
			      CLK_CFG_7_CLR, 0, 3, 7, CLK_CFG_UPDATE, 28,
			      CLK_IS_CRITICAL),
	MUX_GATE_CLR_SET_UPD(CLK_TOP_CAMTM_SEL, "camtm_sel", camपंचांग_parents,
			CLK_CFG_7, CLK_CFG_7_SET, CLK_CFG_7_CLR, 8, 2, 15,
			CLK_CFG_UPDATE, 29),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs top0_cg_regs = अणु
	.set_ofs = 0x0,
	.clr_ofs = 0x0,
	.sta_ofs = 0x0,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs top1_cg_regs = अणु
	.set_ofs = 0x104,
	.clr_ofs = 0x104,
	.sta_ofs = 0x104,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs top2_cg_regs = अणु
	.set_ofs = 0x320,
	.clr_ofs = 0x320,
	.sta_ofs = 0x320,
पूर्ण;

#घोषणा GATE_TOP0(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &top0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

#घोषणा GATE_TOP1(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &top1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

#घोषणा GATE_TOP2(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &top2_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate top_clks[] = अणु
	/* TOP0 */
	GATE_TOP0(CLK_TOP_MD_32K, "md_32k", "f_frtc_ck", 8),
	GATE_TOP0(CLK_TOP_MD_26M, "md_26m", "f_f26m_ck", 9),
	GATE_TOP0(CLK_TOP_MD2_32K, "md2_32k", "f_frtc_ck", 10),
	GATE_TOP0(CLK_TOP_MD2_26M, "md2_26m", "f_f26m_ck", 11),
	/* TOP1 */
	GATE_TOP1(CLK_TOP_ARMPLL_DIVIDER_PLL0_EN,
		  "arm_div_pll0_en", "arm_div_pll0", 3),
	GATE_TOP1(CLK_TOP_ARMPLL_DIVIDER_PLL1_EN,
		  "arm_div_pll1_en", "arm_div_pll1", 4),
	GATE_TOP1(CLK_TOP_ARMPLL_DIVIDER_PLL2_EN,
		  "arm_div_pll2_en", "arm_div_pll2", 5),
	GATE_TOP1(CLK_TOP_FMEM_OCC_DRC_EN, "drc_en", "univpll2_d2", 6),
	GATE_TOP1(CLK_TOP_USB20_48M_EN, "usb20_48m_en", "usb20_48m_div", 8),
	GATE_TOP1(CLK_TOP_UNIVPLL_48M_EN, "univpll_48m_en", "univ_48m_div", 9),
	GATE_TOP1(CLK_TOP_F_UFS_MP_SAP_CFG_EN, "ufs_sap", "f_f26m_ck", 12),
	GATE_TOP1(CLK_TOP_F_BIST2FPC_EN, "bist2fpc", "f_bist2fpc_ck", 16),
	/* TOP2 */
	GATE_TOP2(CLK_TOP_APLL12_DIV0, "apll12_div0", "aud_1_ck", 2),
	GATE_TOP2(CLK_TOP_APLL12_DIV1, "apll12_div1", "aud_1_ck", 3),
	GATE_TOP2(CLK_TOP_APLL12_DIV2, "apll12_div2", "aud_1_ck", 4),
	GATE_TOP2(CLK_TOP_APLL12_DIV3, "apll12_div3", "aud_1_ck", 5),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs अगरr2_cg_regs = अणु
	.set_ofs = 0x80,
	.clr_ofs = 0x84,
	.sta_ofs = 0x90,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs अगरr3_cg_regs = अणु
	.set_ofs = 0x88,
	.clr_ofs = 0x8c,
	.sta_ofs = 0x94,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs अगरr4_cg_regs = अणु
	.set_ofs = 0xa4,
	.clr_ofs = 0xa8,
	.sta_ofs = 0xac,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs अगरr5_cg_regs = अणु
	.set_ofs = 0xc0,
	.clr_ofs = 0xc4,
	.sta_ofs = 0xc8,
पूर्ण;

#घोषणा GATE_IFR2(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &अगरr2_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_IFR3(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &अगरr3_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_IFR4(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &अगरr4_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_IFR5(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &अगरr5_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate अगरr_clks[] = अणु
	/* INFRA_TOPAXI */
	/* INFRA PERI */
	/* INFRA mode 0 */
	GATE_IFR2(CLK_IFR_ICUSB, "ifr_icusb", "axi_ck", 8),
	GATE_IFR2(CLK_IFR_GCE, "ifr_gce", "axi_ck", 9),
	GATE_IFR2(CLK_IFR_THERM, "ifr_therm", "axi_ck", 10),
	GATE_IFR2(CLK_IFR_I2C_AP, "ifr_i2c_ap", "i2c_ck", 11),
	GATE_IFR2(CLK_IFR_I2C_CCU, "ifr_i2c_ccu", "i2c_ck", 12),
	GATE_IFR2(CLK_IFR_I2C_SSPM, "ifr_i2c_sspm", "i2c_ck", 13),
	GATE_IFR2(CLK_IFR_I2C_RSV, "ifr_i2c_rsv", "i2c_ck", 14),
	GATE_IFR2(CLK_IFR_PWM_HCLK, "ifr_pwm_hclk", "axi_ck", 15),
	GATE_IFR2(CLK_IFR_PWM1, "ifr_pwm1", "f_fpwm_ck", 16),
	GATE_IFR2(CLK_IFR_PWM2, "ifr_pwm2", "f_fpwm_ck", 17),
	GATE_IFR2(CLK_IFR_PWM3, "ifr_pwm3", "f_fpwm_ck", 18),
	GATE_IFR2(CLK_IFR_PWM4, "ifr_pwm4", "f_fpwm_ck", 19),
	GATE_IFR2(CLK_IFR_PWM5, "ifr_pwm5", "f_fpwm_ck", 20),
	GATE_IFR2(CLK_IFR_PWM, "ifr_pwm", "f_fpwm_ck", 21),
	GATE_IFR2(CLK_IFR_UART0, "ifr_uart0", "f_fuart_ck", 22),
	GATE_IFR2(CLK_IFR_UART1, "ifr_uart1", "f_fuart_ck", 23),
	GATE_IFR2(CLK_IFR_GCE_26M, "ifr_gce_26m", "f_f26m_ck", 27),
	GATE_IFR2(CLK_IFR_CQ_DMA_FPC, "ifr_dma", "axi_ck", 28),
	GATE_IFR2(CLK_IFR_BTIF, "ifr_btif", "axi_ck", 31),
	/* INFRA mode 1 */
	GATE_IFR3(CLK_IFR_SPI0, "ifr_spi0", "spi_ck", 1),
	GATE_IFR3(CLK_IFR_MSDC0, "ifr_msdc0", "msdc5hclk", 2),
	GATE_IFR3(CLK_IFR_MSDC1, "ifr_msdc1", "axi_ck", 4),
	GATE_IFR3(CLK_IFR_TRNG, "ifr_trng", "axi_ck", 9),
	GATE_IFR3(CLK_IFR_AUXADC, "ifr_auxadc", "f_f26m_ck", 10),
	GATE_IFR3(CLK_IFR_CCIF1_AP, "ifr_ccif1_ap", "axi_ck", 12),
	GATE_IFR3(CLK_IFR_CCIF1_MD, "ifr_ccif1_md", "axi_ck", 13),
	GATE_IFR3(CLK_IFR_AUXADC_MD, "ifr_auxadc_md", "f_f26m_ck", 14),
	GATE_IFR3(CLK_IFR_AP_DMA, "ifr_ap_dma", "axi_ck", 18),
	GATE_IFR3(CLK_IFR_DEVICE_APC, "ifr_dapc", "axi_ck", 20),
	GATE_IFR3(CLK_IFR_CCIF_AP, "ifr_ccif_ap", "axi_ck", 23),
	GATE_IFR3(CLK_IFR_AUDIO, "ifr_audio", "axi_ck", 25),
	GATE_IFR3(CLK_IFR_CCIF_MD, "ifr_ccif_md", "axi_ck", 26),
	/* INFRA mode 2 */
	GATE_IFR4(CLK_IFR_RG_PWM_FBCLK6, "ifr_pwmfb", "f_f26m_ck", 0),
	GATE_IFR4(CLK_IFR_DISP_PWM, "ifr_disp_pwm", "f_fdisp_pwm_ck", 2),
	GATE_IFR4(CLK_IFR_CLDMA_BCLK, "ifr_cldmabclk", "axi_ck", 3),
	GATE_IFR4(CLK_IFR_AUDIO_26M_BCLK, "ifr_audio26m", "f_f26m_ck", 4),
	GATE_IFR4(CLK_IFR_SPI1, "ifr_spi1", "spi_ck", 6),
	GATE_IFR4(CLK_IFR_I2C4, "ifr_i2c4", "i2c_ck", 7),
	GATE_IFR4(CLK_IFR_SPI2, "ifr_spi2", "spi_ck", 9),
	GATE_IFR4(CLK_IFR_SPI3, "ifr_spi3", "spi_ck", 10),
	GATE_IFR4(CLK_IFR_I2C5, "ifr_i2c5", "i2c_ck", 18),
	GATE_IFR4(CLK_IFR_I2C5_ARBITER, "ifr_i2c5a", "i2c_ck", 19),
	GATE_IFR4(CLK_IFR_I2C5_IMM, "ifr_i2c5_imm", "i2c_ck", 20),
	GATE_IFR4(CLK_IFR_I2C1_ARBITER, "ifr_i2c1a", "i2c_ck", 21),
	GATE_IFR4(CLK_IFR_I2C1_IMM, "ifr_i2c1_imm", "i2c_ck", 22),
	GATE_IFR4(CLK_IFR_I2C2_ARBITER, "ifr_i2c2a", "i2c_ck", 23),
	GATE_IFR4(CLK_IFR_I2C2_IMM, "ifr_i2c2_imm", "i2c_ck", 24),
	GATE_IFR4(CLK_IFR_SPI4, "ifr_spi4", "spi_ck", 25),
	GATE_IFR4(CLK_IFR_SPI5, "ifr_spi5", "spi_ck", 26),
	GATE_IFR4(CLK_IFR_CQ_DMA, "ifr_cq_dma", "axi_ck", 27),
	GATE_IFR4(CLK_IFR_FAES_FDE, "ifr_faes_fde_ck", "aes_fde_ck", 29),
	/* INFRA mode 3 */
	GATE_IFR5(CLK_IFR_MSDC0_SELF, "ifr_msdc0sf", "msdc50_0_ck", 0),
	GATE_IFR5(CLK_IFR_MSDC1_SELF, "ifr_msdc1sf", "msdc50_0_ck", 1),
	GATE_IFR5(CLK_IFR_I2C6, "ifr_i2c6", "i2c_ck", 6),
	GATE_IFR5(CLK_IFR_AP_MSDC0, "ifr_ap_msdc0", "msdc50_0_ck", 7),
	GATE_IFR5(CLK_IFR_MD_MSDC0, "ifr_md_msdc0", "msdc50_0_ck", 8),
	GATE_IFR5(CLK_IFR_MSDC0_SRC, "ifr_msdc0_clk", "msdc50_0_ck", 9),
	GATE_IFR5(CLK_IFR_MSDC1_SRC, "ifr_msdc1_clk", "msdc30_1_ck", 10),
	GATE_IFR5(CLK_IFR_MCU_PM_BCLK, "ifr_mcu_pm_bclk", "axi_ck", 17),
	GATE_IFR5(CLK_IFR_CCIF2_AP, "ifr_ccif2_ap", "axi_ck", 18),
	GATE_IFR5(CLK_IFR_CCIF2_MD, "ifr_ccif2_md", "axi_ck", 19),
	GATE_IFR5(CLK_IFR_CCIF3_AP, "ifr_ccif3_ap", "axi_ck", 20),
	GATE_IFR5(CLK_IFR_CCIF3_MD, "ifr_ccif3_md", "axi_ck", 21),
पूर्ण;

/* additional CCF control क्रम mipi26M race condition(disp/camera) */
अटल स्थिर काष्ठा mtk_gate_regs apmixed_cg_regs = अणु
	.set_ofs = 0x14,
	.clr_ofs = 0x14,
	.sta_ofs = 0x14,
पूर्ण;

#घोषणा GATE_APMIXED(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &apmixed_cg_regs,		\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,		\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate apmixed_clks[] = अणु
	/* AUDIO0 */
	GATE_APMIXED(CLK_APMIXED_SSUSB26M, "apmixed_ssusb26m", "f_f26m_ck",
		     4),
	GATE_APMIXED(CLK_APMIXED_APPLL26M, "apmixed_appll26m", "f_f26m_ck",
		     5),
	GATE_APMIXED(CLK_APMIXED_MIPIC0_26M, "apmixed_mipic026m", "f_f26m_ck",
		     6),
	GATE_APMIXED(CLK_APMIXED_MDPLLGP26M, "apmixed_mdpll26m", "f_f26m_ck",
		     7),
	GATE_APMIXED(CLK_APMIXED_MMSYS_F26M, "apmixed_mmsys26m", "f_f26m_ck",
		     8),
	GATE_APMIXED(CLK_APMIXED_UFS26M, "apmixed_ufs26m", "f_f26m_ck",
		     9),
	GATE_APMIXED(CLK_APMIXED_MIPIC1_26M, "apmixed_mipic126m", "f_f26m_ck",
		     11),
	GATE_APMIXED(CLK_APMIXED_MEMPLL26M, "apmixed_mempll26m", "f_f26m_ck",
		     13),
	GATE_APMIXED(CLK_APMIXED_CLKSQ_LVPLL_26M, "apmixed_lvpll26m",
		     "f_f26m_ck", 14),
	GATE_APMIXED(CLK_APMIXED_MIPID0_26M, "apmixed_mipid026m", "f_f26m_ck",
		     16),
पूर्ण;

#घोषणा MT6765_PLL_FMAX		(3800UL * MHZ)
#घोषणा MT6765_PLL_FMIN		(1500UL * MHZ)

#घोषणा CON0_MT6765_RST_BAR	BIT(23)

#घोषणा PLL_INFO_शून्य		(0xFF)

#घोषणा PLL_B(_id, _name, _reg, _pwr_reg, _en_mask, _flags, _pcwbits,	\
		_pcwibits, _pd_reg, _pd_shअगरt, _tuner_reg, _tuner_en_reg,\
		_tuner_en_bit, _pcw_reg, _pcw_shअगरt, _भाग_प्रकारable) अणु\
		.id = _id,						\
		.name = _name,						\
		.reg = _reg,						\
		.pwr_reg = _pwr_reg,					\
		.en_mask = _en_mask,					\
		.flags = _flags,					\
		.rst_bar_mask = CON0_MT6765_RST_BAR,			\
		.fmax = MT6765_PLL_FMAX,				\
		.fmin = MT6765_PLL_FMIN,				\
		.pcwbits = _pcwbits,					\
		.pcwibits = _pcwibits,					\
		.pd_reg = _pd_reg,					\
		.pd_shअगरt = _pd_shअगरt,					\
		.tuner_reg = _tuner_reg,				\
		.tuner_en_reg = _tuner_en_reg,				\
		.tuner_en_bit = _tuner_en_bit,				\
		.pcw_reg = _pcw_reg,					\
		.pcw_shअगरt = _pcw_shअगरt,				\
		.भाग_प्रकारable = _भाग_प्रकारable,				\
	पूर्ण

#घोषणा PLL(_id, _name, _reg, _pwr_reg, _en_mask, _flags, _pcwbits,	\
			_pcwibits, _pd_reg, _pd_shअगरt, _tuner_reg,	\
			_tuner_en_reg, _tuner_en_bit, _pcw_reg,	\
			_pcw_shअगरt)	\
		PLL_B(_id, _name, _reg, _pwr_reg, _en_mask, _flags,	\
			_pcwbits, _pcwibits, _pd_reg, _pd_shअगरt,	\
			_tuner_reg, _tuner_en_reg, _tuner_en_bit,	\
			_pcw_reg, _pcw_shअगरt, शून्य)	\

अटल स्थिर काष्ठा mtk_pll_data plls[] = अणु
	PLL(CLK_APMIXED_ARMPLL_L, "armpll_l", 0x021C, 0x0228, BIT(0),
	    PLL_AO, 22, 8, 0x0220, 24, 0, 0, 0, 0x0220, 0),
	PLL(CLK_APMIXED_ARMPLL, "armpll", 0x020C, 0x0218, BIT(0),
	    PLL_AO, 22, 8, 0x0210, 24, 0, 0, 0, 0x0210, 0),
	PLL(CLK_APMIXED_CCIPLL, "ccipll", 0x022C, 0x0238, BIT(0),
	    PLL_AO, 22, 8, 0x0230, 24, 0, 0, 0, 0x0230, 0),
	PLL(CLK_APMIXED_MAINPLL, "mainpll", 0x023C, 0x0248, BIT(0),
	    (HAVE_RST_BAR | PLL_AO), 22, 8, 0x0240, 24, 0, 0, 0, 0x0240,
	    0),
	PLL(CLK_APMIXED_MFGPLL, "mfgpll", 0x024C, 0x0258, BIT(0),
	    0, 22, 8, 0x0250, 24, 0, 0, 0, 0x0250, 0),
	PLL(CLK_APMIXED_MMPLL, "mmpll", 0x025C, 0x0268, BIT(0),
	    0, 22, 8, 0x0260, 24, 0, 0, 0, 0x0260, 0),
	PLL(CLK_APMIXED_UNIV2PLL, "univ2pll", 0x026C, 0x0278, BIT(0),
	    HAVE_RST_BAR, 22, 8, 0x0270, 24, 0, 0, 0, 0x0270, 0),
	PLL(CLK_APMIXED_MSDCPLL, "msdcpll", 0x027C, 0x0288, BIT(0),
	    0, 22, 8, 0x0280, 24, 0, 0, 0, 0x0280, 0),
	PLL(CLK_APMIXED_APLL1, "apll1", 0x028C, 0x029C, BIT(0),
	    0, 32, 8, 0x0290, 24, 0x0040, 0x000C, 0, 0x0294, 0),
	PLL(CLK_APMIXED_MPLL, "mpll", 0x02A0, 0x02AC, BIT(0),
	    PLL_AO, 22, 8, 0x02A4, 24, 0, 0, 0, 0x02A4, 0),
पूर्ण;

अटल पूर्णांक clk_mt6765_apmixed_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;
	व्योम __iomem *base;
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		pr_err("%s(): ioremap failed\n", __func__);
		वापस PTR_ERR(base);
	पूर्ण

	clk_data = mtk_alloc_clk_data(CLK_APMIXED_NR_CLK);

	mtk_clk_रेजिस्टर_plls(node, plls, ARRAY_SIZE(plls), clk_data);

	mtk_clk_रेजिस्टर_gates(node, apmixed_clks,
			       ARRAY_SIZE(apmixed_clks), clk_data);
	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
		       __func__, r);

	apmixed_base = base;
	/* MPLL, CCIPLL, MAINPLL set HW mode, TDCLKSQ, CLKSQ1 */
	ग_लिखोl(पढ़ोl(AP_PLL_CON3) & 0xFFFFFFE1, AP_PLL_CON3);
	ग_लिखोl(पढ़ोl(PLLON_CON0) & 0x01041041, PLLON_CON0);
	ग_लिखोl(पढ़ोl(PLLON_CON1) & 0x01041041, PLLON_CON1);

	वापस r;
पूर्ण

अटल पूर्णांक clk_mt6765_top_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;
	व्योम __iomem *base;
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		pr_err("%s(): ioremap failed\n", __func__);
		वापस PTR_ERR(base);
	पूर्ण

	clk_data = mtk_alloc_clk_data(CLK_TOP_NR_CLK);

	mtk_clk_रेजिस्टर_fixed_clks(fixed_clks, ARRAY_SIZE(fixed_clks),
				    clk_data);
	mtk_clk_रेजिस्टर_factors(top_भागs, ARRAY_SIZE(top_भागs),
				 clk_data);
	mtk_clk_रेजिस्टर_muxes(top_muxes, ARRAY_SIZE(top_muxes), node,
			       &mt6765_clk_lock, clk_data);
	mtk_clk_रेजिस्टर_gates(node, top_clks, ARRAY_SIZE(top_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
		       __func__, r);

	cksys_base = base;
	/* [4]:no need */
	ग_लिखोl(पढ़ोl(CLK_SCP_CFG_0) | 0x3EF, CLK_SCP_CFG_0);
	/*[1,2,3,8]: no need*/
	ग_लिखोl(पढ़ोl(CLK_SCP_CFG_1) | 0x1, CLK_SCP_CFG_1);

	वापस r;
पूर्ण

अटल पूर्णांक clk_mt6765_अगरr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;
	व्योम __iomem *base;
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		pr_err("%s(): ioremap failed\n", __func__);
		वापस PTR_ERR(base);
	पूर्ण

	clk_data = mtk_alloc_clk_data(CLK_IFR_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, अगरr_clks, ARRAY_SIZE(अगरr_clks),
			       clk_data);
	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
		       __func__, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6765[] = अणु
	अणु
		.compatible = "mediatek,mt6765-apmixedsys",
		.data = clk_mt6765_apmixed_probe,
	पूर्ण, अणु
		.compatible = "mediatek,mt6765-topckgen",
		.data = clk_mt6765_top_probe,
	पूर्ण, अणु
		.compatible = "mediatek,mt6765-infracfg",
		.data = clk_mt6765_अगरr_probe,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6765_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*clk_probe)(काष्ठा platक्रमm_device *d);
	पूर्णांक r;

	clk_probe = of_device_get_match_data(&pdev->dev);
	अगर (!clk_probe)
		वापस -EINVAL;

	r = clk_probe(pdev);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6765_drv = अणु
	.probe = clk_mt6765_probe,
	.driver = अणु
		.name = "clk-mt6765",
		.of_match_table = of_match_clk_mt6765,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init clk_mt6765_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&clk_mt6765_drv);
पूर्ण

arch_initcall(clk_mt6765_init);
