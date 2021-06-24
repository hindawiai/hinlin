<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 *
 * Common Clock Framework support क्रम all Exynos4 SoCs.
*/

#समावेश <dt-bindings/घड़ी/exynos4.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "clk.h"
#समावेश "clk-cpu.h"

/* Exynos4 घड़ी controller रेजिस्टर offsets */
#घोषणा SRC_LEFTBUS		0x4200
#घोषणा DIV_LEFTBUS		0x4500
#घोषणा GATE_IP_LEFTBUS		0x4800
#घोषणा E4X12_GATE_IP_IMAGE	0x4930
#घोषणा CLKOUT_CMU_LEFTBUS	0x4a00
#घोषणा SRC_RIGHTBUS		0x8200
#घोषणा DIV_RIGHTBUS		0x8500
#घोषणा GATE_IP_RIGHTBUS	0x8800
#घोषणा E4X12_GATE_IP_PERIR	0x8960
#घोषणा CLKOUT_CMU_RIGHTBUS	0x8a00
#घोषणा EPLL_LOCK		0xc010
#घोषणा VPLL_LOCK		0xc020
#घोषणा EPLL_CON0		0xc110
#घोषणा EPLL_CON1		0xc114
#घोषणा EPLL_CON2		0xc118
#घोषणा VPLL_CON0		0xc120
#घोषणा VPLL_CON1		0xc124
#घोषणा VPLL_CON2		0xc128
#घोषणा SRC_TOP0		0xc210
#घोषणा SRC_TOP1		0xc214
#घोषणा SRC_CAM			0xc220
#घोषणा SRC_TV			0xc224
#घोषणा SRC_MFC			0xc228
#घोषणा SRC_G3D			0xc22c
#घोषणा E4210_SRC_IMAGE		0xc230
#घोषणा SRC_LCD0		0xc234
#घोषणा E4210_SRC_LCD1		0xc238
#घोषणा E4X12_SRC_ISP		0xc238
#घोषणा SRC_MAUDIO		0xc23c
#घोषणा SRC_FSYS		0xc240
#घोषणा SRC_PERIL0		0xc250
#घोषणा SRC_PERIL1		0xc254
#घोषणा E4X12_SRC_CAM1		0xc258
#घोषणा SRC_MASK_TOP		0xc310
#घोषणा SRC_MASK_CAM		0xc320
#घोषणा SRC_MASK_TV		0xc324
#घोषणा SRC_MASK_LCD0		0xc334
#घोषणा E4210_SRC_MASK_LCD1	0xc338
#घोषणा E4X12_SRC_MASK_ISP	0xc338
#घोषणा SRC_MASK_MAUDIO		0xc33c
#घोषणा SRC_MASK_FSYS		0xc340
#घोषणा SRC_MASK_PERIL0		0xc350
#घोषणा SRC_MASK_PERIL1		0xc354
#घोषणा DIV_TOP			0xc510
#घोषणा DIV_CAM			0xc520
#घोषणा DIV_TV			0xc524
#घोषणा DIV_MFC			0xc528
#घोषणा DIV_G3D			0xc52c
#घोषणा DIV_IMAGE		0xc530
#घोषणा DIV_LCD0		0xc534
#घोषणा E4210_DIV_LCD1		0xc538
#घोषणा E4X12_DIV_ISP		0xc538
#घोषणा DIV_MAUDIO		0xc53c
#घोषणा DIV_FSYS0		0xc540
#घोषणा DIV_FSYS1		0xc544
#घोषणा DIV_FSYS2		0xc548
#घोषणा DIV_FSYS3		0xc54c
#घोषणा DIV_PERIL0		0xc550
#घोषणा DIV_PERIL1		0xc554
#घोषणा DIV_PERIL2		0xc558
#घोषणा DIV_PERIL3		0xc55c
#घोषणा DIV_PERIL4		0xc560
#घोषणा DIV_PERIL5		0xc564
#घोषणा E4X12_DIV_CAM1		0xc568
#घोषणा E4X12_GATE_BUS_FSYS1	0xc744
#घोषणा GATE_SCLK_CAM		0xc820
#घोषणा GATE_IP_CAM		0xc920
#घोषणा GATE_IP_TV		0xc924
#घोषणा GATE_IP_MFC		0xc928
#घोषणा GATE_IP_G3D		0xc92c
#घोषणा E4210_GATE_IP_IMAGE	0xc930
#घोषणा GATE_IP_LCD0		0xc934
#घोषणा E4210_GATE_IP_LCD1	0xc938
#घोषणा E4X12_GATE_IP_ISP	0xc938
#घोषणा E4X12_GATE_IP_MAUDIO	0xc93c
#घोषणा GATE_IP_FSYS		0xc940
#घोषणा GATE_IP_GPS		0xc94c
#घोषणा GATE_IP_PERIL		0xc950
#घोषणा E4210_GATE_IP_PERIR	0xc960
#घोषणा GATE_BLOCK		0xc970
#घोषणा CLKOUT_CMU_TOP		0xca00
#घोषणा E4X12_MPLL_LOCK		0x10008
#घोषणा E4X12_MPLL_CON0		0x10108
#घोषणा SRC_DMC			0x10200
#घोषणा SRC_MASK_DMC		0x10300
#घोषणा DIV_DMC0		0x10500
#घोषणा DIV_DMC1		0x10504
#घोषणा GATE_IP_DMC		0x10900
#घोषणा CLKOUT_CMU_DMC		0x10a00
#घोषणा APLL_LOCK		0x14000
#घोषणा E4210_MPLL_LOCK		0x14008
#घोषणा APLL_CON0		0x14100
#घोषणा E4210_MPLL_CON0		0x14108
#घोषणा SRC_CPU			0x14200
#घोषणा DIV_CPU0		0x14500
#घोषणा DIV_CPU1		0x14504
#घोषणा GATE_SCLK_CPU		0x14800
#घोषणा GATE_IP_CPU		0x14900
#घोषणा CLKOUT_CMU_CPU		0x14a00
#घोषणा PWR_CTRL1		0x15020
#घोषणा E4X12_PWR_CTRL2		0x15024

/* Below definitions are used क्रम PWR_CTRL settings */
#घोषणा PWR_CTRL1_CORE2_DOWN_RATIO(x)		(((x) & 0x7) << 28)
#घोषणा PWR_CTRL1_CORE1_DOWN_RATIO(x)		(((x) & 0x7) << 16)
#घोषणा PWR_CTRL1_DIV2_DOWN_EN			(1 << 9)
#घोषणा PWR_CTRL1_DIV1_DOWN_EN			(1 << 8)
#घोषणा PWR_CTRL1_USE_CORE3_WFE			(1 << 7)
#घोषणा PWR_CTRL1_USE_CORE2_WFE			(1 << 6)
#घोषणा PWR_CTRL1_USE_CORE1_WFE			(1 << 5)
#घोषणा PWR_CTRL1_USE_CORE0_WFE			(1 << 4)
#घोषणा PWR_CTRL1_USE_CORE3_WFI			(1 << 3)
#घोषणा PWR_CTRL1_USE_CORE2_WFI			(1 << 2)
#घोषणा PWR_CTRL1_USE_CORE1_WFI			(1 << 1)
#घोषणा PWR_CTRL1_USE_CORE0_WFI			(1 << 0)

/* the exynos4 soc type */
क्रमागत exynos4_soc अणु
	EXYNOS4210,
	EXYNOS4X12,
पूर्ण;

/* list of PLLs to be रेजिस्टरed */
क्रमागत exynos4_plls अणु
	apll, mpll, epll, vpll,
	nr_plls			/* number of PLLs */
पूर्ण;

अटल व्योम __iomem *reg_base;
अटल क्रमागत exynos4_soc exynos4_soc;

/*
 * list of controller रेजिस्टरs to be saved and restored during a
 * suspend/resume cycle.
 */
अटल स्थिर अचिन्हित दीर्घ exynos4210_clk_save[] __initस्थिर = अणु
	E4210_SRC_IMAGE,
	E4210_SRC_LCD1,
	E4210_SRC_MASK_LCD1,
	E4210_DIV_LCD1,
	E4210_GATE_IP_IMAGE,
	E4210_GATE_IP_LCD1,
	E4210_GATE_IP_PERIR,
	E4210_MPLL_CON0,
	PWR_CTRL1,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ exynos4x12_clk_save[] __initस्थिर = अणु
	E4X12_GATE_IP_IMAGE,
	E4X12_GATE_IP_PERIR,
	E4X12_SRC_CAM1,
	E4X12_DIV_ISP,
	E4X12_DIV_CAM1,
	E4X12_MPLL_CON0,
	PWR_CTRL1,
	E4X12_PWR_CTRL2,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ exynos4_clk_regs[] __initस्थिर = अणु
	EPLL_LOCK,
	VPLL_LOCK,
	EPLL_CON0,
	EPLL_CON1,
	EPLL_CON2,
	VPLL_CON0,
	VPLL_CON1,
	VPLL_CON2,
	SRC_LEFTBUS,
	DIV_LEFTBUS,
	GATE_IP_LEFTBUS,
	SRC_RIGHTBUS,
	DIV_RIGHTBUS,
	GATE_IP_RIGHTBUS,
	SRC_TOP0,
	SRC_TOP1,
	SRC_CAM,
	SRC_TV,
	SRC_MFC,
	SRC_G3D,
	SRC_LCD0,
	SRC_MAUDIO,
	SRC_FSYS,
	SRC_PERIL0,
	SRC_PERIL1,
	SRC_MASK_TOP,
	SRC_MASK_CAM,
	SRC_MASK_TV,
	SRC_MASK_LCD0,
	SRC_MASK_MAUDIO,
	SRC_MASK_FSYS,
	SRC_MASK_PERIL0,
	SRC_MASK_PERIL1,
	DIV_TOP,
	DIV_CAM,
	DIV_TV,
	DIV_MFC,
	DIV_G3D,
	DIV_IMAGE,
	DIV_LCD0,
	DIV_MAUDIO,
	DIV_FSYS0,
	DIV_FSYS1,
	DIV_FSYS2,
	DIV_FSYS3,
	DIV_PERIL0,
	DIV_PERIL1,
	DIV_PERIL2,
	DIV_PERIL3,
	DIV_PERIL4,
	DIV_PERIL5,
	GATE_SCLK_CAM,
	GATE_IP_CAM,
	GATE_IP_TV,
	GATE_IP_MFC,
	GATE_IP_G3D,
	GATE_IP_LCD0,
	GATE_IP_FSYS,
	GATE_IP_GPS,
	GATE_IP_PERIL,
	GATE_BLOCK,
	SRC_MASK_DMC,
	SRC_DMC,
	DIV_DMC0,
	DIV_DMC1,
	GATE_IP_DMC,
	APLL_CON0,
	SRC_CPU,
	DIV_CPU0,
	DIV_CPU1,
	GATE_SCLK_CPU,
	GATE_IP_CPU,
	CLKOUT_CMU_LEFTBUS,
	CLKOUT_CMU_RIGHTBUS,
	CLKOUT_CMU_TOP,
	CLKOUT_CMU_DMC,
	CLKOUT_CMU_CPU,
पूर्ण;

अटल स्थिर काष्ठा samsung_clk_reg_dump src_mask_suspend[] = अणु
	अणु .offset = VPLL_CON0,			.value = 0x80600302, पूर्ण,
	अणु .offset = EPLL_CON0,			.value = 0x806F0302, पूर्ण,
	अणु .offset = SRC_MASK_TOP,		.value = 0x00000001, पूर्ण,
	अणु .offset = SRC_MASK_CAM,		.value = 0x11111111, पूर्ण,
	अणु .offset = SRC_MASK_TV,		.value = 0x00000111, पूर्ण,
	अणु .offset = SRC_MASK_LCD0,		.value = 0x00001111, पूर्ण,
	अणु .offset = SRC_MASK_MAUDIO,		.value = 0x00000001, पूर्ण,
	अणु .offset = SRC_MASK_FSYS,		.value = 0x01011111, पूर्ण,
	अणु .offset = SRC_MASK_PERIL0,		.value = 0x01111111, पूर्ण,
	अणु .offset = SRC_MASK_PERIL1,		.value = 0x01110111, पूर्ण,
	अणु .offset = SRC_MASK_DMC,		.value = 0x00010000, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_clk_reg_dump src_mask_suspend_e4210[] = अणु
	अणु .offset = E4210_SRC_MASK_LCD1,	.value = 0x00001111, पूर्ण,
पूर्ण;

/* list of all parent घड़ी list */
PNAME(mout_apll_p)	= अणु "fin_pll", "fout_apll", पूर्ण;
PNAME(mout_mpll_p)	= अणु "fin_pll", "fout_mpll", पूर्ण;
PNAME(mout_epll_p)	= अणु "fin_pll", "fout_epll", पूर्ण;
PNAME(mout_vpllsrc_p)	= अणु "fin_pll", "sclk_hdmi24m", पूर्ण;
PNAME(mout_vpll_p)	= अणु "fin_pll", "fout_vpll", पूर्ण;
PNAME(sclk_evpll_p)	= अणु "sclk_epll", "sclk_vpll", पूर्ण;
PNAME(mout_mfc_p)	= अणु "mout_mfc0", "mout_mfc1", पूर्ण;
PNAME(mout_g3d_p)	= अणु "mout_g3d0", "mout_g3d1", पूर्ण;
PNAME(mout_g2d_p)	= अणु "mout_g2d0", "mout_g2d1", पूर्ण;
PNAME(mout_hdmi_p)	= अणु "sclk_pixel", "sclk_hdmiphy", पूर्ण;
PNAME(mout_jpeg_p)	= अणु "mout_jpeg0", "mout_jpeg1", पूर्ण;
PNAME(mout_spdअगर_p)	= अणु "sclk_audio0", "sclk_audio1", "sclk_audio2",
				"spdif_extclk", पूर्ण;
PNAME(mout_onenand_p)  = अणु"aclk133", "aclk160", पूर्ण;
PNAME(mout_onenand1_p) = अणु"mout_onenand", "sclk_vpll", पूर्ण;

/* Exynos 4210-specअगरic parent groups */
PNAME(sclk_vpll_p4210)	= अणु "mout_vpllsrc", "fout_vpll", पूर्ण;
PNAME(mout_core_p4210)	= अणु "mout_apll", "sclk_mpll", पूर्ण;
PNAME(sclk_ampll_p4210)	= अणु "sclk_mpll", "sclk_apll", पूर्ण;
PNAME(group1_p4210)	= अणु "xxti", "xusbxti", "sclk_hdmi24m",
				"sclk_usbphy0", "none",	"sclk_hdmiphy",
				"sclk_mpll", "sclk_epll", "sclk_vpll", पूर्ण;
PNAME(mout_audio0_p4210) = अणु "cdclk0", "none", "sclk_hdmi24m",
				"sclk_usbphy0", "xxti", "xusbxti", "sclk_mpll",
				"sclk_epll", "sclk_vpll" पूर्ण;
PNAME(mout_audio1_p4210) = अणु "cdclk1", "none", "sclk_hdmi24m",
				"sclk_usbphy0", "xxti", "xusbxti", "sclk_mpll",
				"sclk_epll", "sclk_vpll", पूर्ण;
PNAME(mout_audio2_p4210) = अणु "cdclk2", "none", "sclk_hdmi24m",
				"sclk_usbphy0", "xxti", "xusbxti", "sclk_mpll",
				"sclk_epll", "sclk_vpll", पूर्ण;
PNAME(mout_mixer_p4210)	= अणु "sclk_dac", "sclk_hdmi", पूर्ण;
PNAME(mout_dac_p4210)	= अणु "sclk_vpll", "sclk_hdmiphy", पूर्ण;
PNAME(mout_pwi_p4210) = अणु "xxti", "xusbxti", "sclk_hdmi24m", "sclk_usbphy0",
				"sclk_usbphy1", "sclk_hdmiphy", "none",
				"sclk_epll", "sclk_vpll" पूर्ण;
PNAME(clkout_left_p4210) = अणु "sclk_mpll_div_2", "sclk_apll_div_2",
				"div_gdl", "div_gpl" पूर्ण;
PNAME(clkout_right_p4210) = अणु "sclk_mpll_div_2", "sclk_apll_div_2",
				"div_gdr", "div_gpr" पूर्ण;
PNAME(clkout_top_p4210) = अणु "fout_epll", "fout_vpll", "sclk_hdmi24m",
				"sclk_usbphy0", "sclk_usbphy1", "sclk_hdmiphy",
				"cdclk0", "cdclk1", "cdclk2", "spdif_extclk",
				"aclk160", "aclk133", "aclk200", "aclk100",
				"sclk_mfc", "sclk_g3d", "sclk_g2d",
				"cam_a_pclk", "cam_b_pclk", "s_rxbyteclkhs0_2l",
				"s_rxbyteclkhs0_4l" पूर्ण;
PNAME(clkout_dmc_p4210) = अणु "div_dmcd", "div_dmcp", "div_acp_pclk", "div_dmc",
				"div_dphy", "none", "div_pwi" पूर्ण;
PNAME(clkout_cpu_p4210) = अणु "fout_apll_div_2", "none", "fout_mpll_div_2",
				"none", "arm_clk_div_2", "div_corem0",
				"div_corem1", "div_corem0", "div_atb",
				"div_periph", "div_pclk_dbg", "div_hpm" पूर्ण;

/* Exynos 4x12-specअगरic parent groups */
PNAME(mout_mpll_user_p4x12) = अणु "fin_pll", "sclk_mpll", पूर्ण;
PNAME(mout_core_p4x12)	= अणु "mout_apll", "mout_mpll_user_c", पूर्ण;
PNAME(mout_gdl_p4x12)	= अणु "mout_mpll_user_l", "sclk_apll", पूर्ण;
PNAME(mout_gdr_p4x12)	= अणु "mout_mpll_user_r", "sclk_apll", पूर्ण;
PNAME(sclk_ampll_p4x12)	= अणु "mout_mpll_user_t", "sclk_apll", पूर्ण;
PNAME(group1_p4x12)	= अणु "xxti", "xusbxti", "sclk_hdmi24m", "sclk_usbphy0",
				"none",	"sclk_hdmiphy", "mout_mpll_user_t",
				"sclk_epll", "sclk_vpll", पूर्ण;
PNAME(mout_audio0_p4x12) = अणु "cdclk0", "none", "sclk_hdmi24m",
				"sclk_usbphy0", "xxti", "xusbxti",
				"mout_mpll_user_t", "sclk_epll", "sclk_vpll" पूर्ण;
PNAME(mout_audio1_p4x12) = अणु "cdclk1", "none", "sclk_hdmi24m",
				"sclk_usbphy0", "xxti", "xusbxti",
				"mout_mpll_user_t", "sclk_epll", "sclk_vpll", पूर्ण;
PNAME(mout_audio2_p4x12) = अणु "cdclk2", "none", "sclk_hdmi24m",
				"sclk_usbphy0", "xxti", "xusbxti",
				"mout_mpll_user_t", "sclk_epll", "sclk_vpll", पूर्ण;
PNAME(aclk_p4412)	= अणु "mout_mpll_user_t", "sclk_apll", पूर्ण;
PNAME(mout_user_aclk400_mcuisp_p4x12) = अणु"fin_pll", "div_aclk400_mcuisp", पूर्ण;
PNAME(mout_user_aclk200_p4x12) = अणु"fin_pll", "div_aclk200", पूर्ण;
PNAME(mout_user_aclk266_gps_p4x12) = अणु"fin_pll", "div_aclk266_gps", पूर्ण;
PNAME(mout_pwi_p4x12) = अणु "xxti", "xusbxti", "sclk_hdmi24m", "sclk_usbphy0",
				"none", "sclk_hdmiphy", "sclk_mpll",
				"sclk_epll", "sclk_vpll" पूर्ण;
PNAME(clkout_left_p4x12) = अणु "sclk_mpll_user_l_div_2", "sclk_apll_div_2",
				"div_gdl", "div_gpl" पूर्ण;
PNAME(clkout_right_p4x12) = अणु "sclk_mpll_user_r_div_2", "sclk_apll_div_2",
				"div_gdr", "div_gpr" पूर्ण;
PNAME(clkout_top_p4x12) = अणु "fout_epll", "fout_vpll", "sclk_hdmi24m",
				"sclk_usbphy0", "none", "sclk_hdmiphy",
				"cdclk0", "cdclk1", "cdclk2", "spdif_extclk",
				"aclk160", "aclk133", "aclk200", "aclk100",
				"sclk_mfc", "sclk_g3d", "aclk400_mcuisp",
				"cam_a_pclk", "cam_b_pclk", "s_rxbyteclkhs0_2l",
				"s_rxbyteclkhs0_4l", "rx_half_byte_clk_csis0",
				"rx_half_byte_clk_csis1", "div_jpeg",
				"sclk_pwm_isp", "sclk_spi0_isp",
				"sclk_spi1_isp", "sclk_uart_isp",
				"sclk_mipihsi", "sclk_hdmi", "sclk_fimd0",
				"sclk_pcm0" पूर्ण;
PNAME(clkout_dmc_p4x12) = अणु "div_dmcd", "div_dmcp", "aclk_acp", "div_acp_pclk",
				"div_dmc", "div_dphy", "fout_mpll_div_2",
				"div_pwi", "none", "div_c2c", "div_c2c_aclk" पूर्ण;
PNAME(clkout_cpu_p4x12) = अणु "fout_apll_div_2", "none", "none", "none",
				"arm_clk_div_2", "div_corem0", "div_corem1",
				"div_cores", "div_atb", "div_periph",
				"div_pclk_dbg", "div_hpm" पूर्ण;

/* fixed rate घड़ीs generated outside the soc */
अटल काष्ठा samsung_fixed_rate_घड़ी exynos4_fixed_rate_ext_clks[] __initdata = अणु
	FRATE(CLK_XXTI, "xxti", शून्य, 0, 0),
	FRATE(CLK_XUSBXTI, "xusbxti", शून्य, 0, 0),
पूर्ण;

/* fixed rate घड़ीs generated inside the soc */
अटल स्थिर काष्ठा samsung_fixed_rate_घड़ी exynos4_fixed_rate_clks[] __initस्थिर = अणु
	FRATE(0, "sclk_hdmi24m", शून्य, 0, 24000000),
	FRATE(CLK_SCLK_HDMIPHY, "sclk_hdmiphy", "hdmi", 0, 27000000),
	FRATE(0, "sclk_usbphy0", शून्य, 0, 48000000),
पूर्ण;

अटल स्थिर काष्ठा samsung_fixed_rate_घड़ी exynos4210_fixed_rate_clks[] __initस्थिर = अणु
	FRATE(0, "sclk_usbphy1", शून्य, 0, 48000000),
पूर्ण;

अटल स्थिर काष्ठा samsung_fixed_factor_घड़ी exynos4_fixed_factor_clks[] __initस्थिर = अणु
	FFACTOR(0, "sclk_apll_div_2", "sclk_apll", 1, 2, 0),
	FFACTOR(0, "fout_mpll_div_2", "fout_mpll", 1, 2, 0),
	FFACTOR(0, "fout_apll_div_2", "fout_apll", 1, 2, 0),
	FFACTOR(0, "arm_clk_div_2", "div_core2", 1, 2, 0),
पूर्ण;

अटल स्थिर काष्ठा samsung_fixed_factor_घड़ी exynos4210_fixed_factor_clks[] __initस्थिर = अणु
	FFACTOR(0, "sclk_mpll_div_2", "sclk_mpll", 1, 2, 0),
पूर्ण;

अटल स्थिर काष्ठा samsung_fixed_factor_घड़ी exynos4x12_fixed_factor_clks[] __initस्थिर = अणु
	FFACTOR(0, "sclk_mpll_user_l_div_2", "mout_mpll_user_l", 1, 2, 0),
	FFACTOR(0, "sclk_mpll_user_r_div_2", "mout_mpll_user_r", 1, 2, 0),
	FFACTOR(0, "sclk_mpll_user_t_div_2", "mout_mpll_user_t", 1, 2, 0),
	FFACTOR(0, "sclk_mpll_user_c_div_2", "mout_mpll_user_c", 1, 2, 0),
पूर्ण;

/* list of mux घड़ीs supported in all exynos4 soc's */
अटल स्थिर काष्ठा samsung_mux_घड़ी exynos4_mux_clks[] __initस्थिर = अणु
	MUX_F(CLK_MOUT_APLL, "mout_apll", mout_apll_p, SRC_CPU, 0, 1,
			CLK_SET_RATE_PARENT | CLK_RECALC_NEW_RATES, 0),
	MUX(CLK_MOUT_HDMI, "mout_hdmi", mout_hdmi_p, SRC_TV, 0, 1),
	MUX(0, "mout_mfc1", sclk_evpll_p, SRC_MFC, 4, 1),
	MUX(0, "mout_mfc", mout_mfc_p, SRC_MFC, 8, 1),
	MUX_F(CLK_MOUT_G3D1, "mout_g3d1", sclk_evpll_p, SRC_G3D, 4, 1,
			CLK_SET_RATE_PARENT, 0),
	MUX_F(CLK_MOUT_G3D, "mout_g3d", mout_g3d_p, SRC_G3D, 8, 1,
			CLK_SET_RATE_PARENT, 0),
	MUX(0, "mout_spdif", mout_spdअगर_p, SRC_PERIL1, 8, 2),
	MUX(0, "mout_onenand1", mout_onenand1_p, SRC_TOP0, 0, 1),
	MUX(CLK_SCLK_EPLL, "sclk_epll", mout_epll_p, SRC_TOP0, 4, 1),
	MUX(0, "mout_onenand", mout_onenand_p, SRC_TOP0, 28, 1),

	MUX(0, "mout_dmc_bus", sclk_ampll_p4210, SRC_DMC, 4, 1),
	MUX(0, "mout_dphy", sclk_ampll_p4210, SRC_DMC, 8, 1),
पूर्ण;

/* list of mux घड़ीs supported in exynos4210 soc */
अटल स्थिर काष्ठा samsung_mux_घड़ी exynos4210_mux_early[] __initस्थिर = अणु
	MUX(0, "mout_vpllsrc", mout_vpllsrc_p, SRC_TOP1, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा samsung_mux_घड़ी exynos4210_mux_clks[] __initस्थिर = अणु
	MUX(0, "mout_gdl", sclk_ampll_p4210, SRC_LEFTBUS, 0, 1),
	MUX(0, "mout_clkout_leftbus", clkout_left_p4210,
			CLKOUT_CMU_LEFTBUS, 0, 5),

	MUX(0, "mout_gdr", sclk_ampll_p4210, SRC_RIGHTBUS, 0, 1),
	MUX(0, "mout_clkout_rightbus", clkout_right_p4210,
			CLKOUT_CMU_RIGHTBUS, 0, 5),

	MUX(0, "mout_aclk200", sclk_ampll_p4210, SRC_TOP0, 12, 1),
	MUX(0, "mout_aclk100", sclk_ampll_p4210, SRC_TOP0, 16, 1),
	MUX(0, "mout_aclk160", sclk_ampll_p4210, SRC_TOP0, 20, 1),
	MUX(0, "mout_aclk133", sclk_ampll_p4210, SRC_TOP0, 24, 1),
	MUX(CLK_MOUT_MIXER, "mout_mixer", mout_mixer_p4210, SRC_TV, 4, 1),
	MUX(0, "mout_dac", mout_dac_p4210, SRC_TV, 8, 1),
	MUX(0, "mout_g2d0", sclk_ampll_p4210, E4210_SRC_IMAGE, 0, 1),
	MUX(0, "mout_g2d1", sclk_evpll_p, E4210_SRC_IMAGE, 4, 1),
	MUX(0, "mout_g2d", mout_g2d_p, E4210_SRC_IMAGE, 8, 1),
	MUX(0, "mout_fimd1", group1_p4210, E4210_SRC_LCD1, 0, 4),
	MUX(0, "mout_mipi1", group1_p4210, E4210_SRC_LCD1, 12, 4),
	MUX(CLK_SCLK_MPLL, "sclk_mpll", mout_mpll_p, SRC_CPU, 8, 1),
	MUX(CLK_MOUT_CORE, "mout_core", mout_core_p4210, SRC_CPU, 16, 1),
	MUX(0, "mout_hpm", mout_core_p4210, SRC_CPU, 20, 1),
	MUX(CLK_SCLK_VPLL, "sclk_vpll", sclk_vpll_p4210, SRC_TOP0, 8, 1),
	MUX(CLK_MOUT_FIMC0, "mout_fimc0", group1_p4210, SRC_CAM, 0, 4),
	MUX(CLK_MOUT_FIMC1, "mout_fimc1", group1_p4210, SRC_CAM, 4, 4),
	MUX(CLK_MOUT_FIMC2, "mout_fimc2", group1_p4210, SRC_CAM, 8, 4),
	MUX(CLK_MOUT_FIMC3, "mout_fimc3", group1_p4210, SRC_CAM, 12, 4),
	MUX(CLK_MOUT_CAM0, "mout_cam0", group1_p4210, SRC_CAM, 16, 4),
	MUX(CLK_MOUT_CAM1, "mout_cam1", group1_p4210, SRC_CAM, 20, 4),
	MUX(CLK_MOUT_CSIS0, "mout_csis0", group1_p4210, SRC_CAM, 24, 4),
	MUX(CLK_MOUT_CSIS1, "mout_csis1", group1_p4210, SRC_CAM, 28, 4),
	MUX(0, "mout_mfc0", sclk_ampll_p4210, SRC_MFC, 0, 1),
	MUX_F(CLK_MOUT_G3D0, "mout_g3d0", sclk_ampll_p4210, SRC_G3D, 0, 1,
			CLK_SET_RATE_PARENT, 0),
	MUX(0, "mout_fimd0", group1_p4210, SRC_LCD0, 0, 4),
	MUX(0, "mout_mipi0", group1_p4210, SRC_LCD0, 12, 4),
	MUX(0, "mout_audio0", mout_audio0_p4210, SRC_MAUDIO, 0, 4),
	MUX(0, "mout_mmc0", group1_p4210, SRC_FSYS, 0, 4),
	MUX(0, "mout_mmc1", group1_p4210, SRC_FSYS, 4, 4),
	MUX(0, "mout_mmc2", group1_p4210, SRC_FSYS, 8, 4),
	MUX(0, "mout_mmc3", group1_p4210, SRC_FSYS, 12, 4),
	MUX(0, "mout_mmc4", group1_p4210, SRC_FSYS, 16, 4),
	MUX(0, "mout_sata", sclk_ampll_p4210, SRC_FSYS, 24, 1),
	MUX(0, "mout_uart0", group1_p4210, SRC_PERIL0, 0, 4),
	MUX(0, "mout_uart1", group1_p4210, SRC_PERIL0, 4, 4),
	MUX(0, "mout_uart2", group1_p4210, SRC_PERIL0, 8, 4),
	MUX(0, "mout_uart3", group1_p4210, SRC_PERIL0, 12, 4),
	MUX(0, "mout_uart4", group1_p4210, SRC_PERIL0, 16, 4),
	MUX(0, "mout_audio1", mout_audio1_p4210, SRC_PERIL1, 0, 4),
	MUX(0, "mout_audio2", mout_audio2_p4210, SRC_PERIL1, 4, 4),
	MUX(0, "mout_spi0", group1_p4210, SRC_PERIL1, 16, 4),
	MUX(0, "mout_spi1", group1_p4210, SRC_PERIL1, 20, 4),
	MUX(0, "mout_spi2", group1_p4210, SRC_PERIL1, 24, 4),
	MUX(0, "mout_clkout_top", clkout_top_p4210, CLKOUT_CMU_TOP, 0, 5),

	MUX(0, "mout_pwi", mout_pwi_p4210, SRC_DMC, 16, 4),
	MUX(0, "mout_clkout_dmc", clkout_dmc_p4210, CLKOUT_CMU_DMC, 0, 5),

	MUX(0, "mout_clkout_cpu", clkout_cpu_p4210, CLKOUT_CMU_CPU, 0, 5),
पूर्ण;

/* list of mux घड़ीs supported in exynos4x12 soc */
अटल स्थिर काष्ठा samsung_mux_घड़ी exynos4x12_mux_clks[] __initस्थिर = अणु
	MUX(0, "mout_mpll_user_l", mout_mpll_p, SRC_LEFTBUS, 4, 1),
	MUX(0, "mout_gdl", mout_gdl_p4x12, SRC_LEFTBUS, 0, 1),
	MUX(0, "mout_clkout_leftbus", clkout_left_p4x12,
			CLKOUT_CMU_LEFTBUS, 0, 5),

	MUX(0, "mout_mpll_user_r", mout_mpll_p, SRC_RIGHTBUS, 4, 1),
	MUX(0, "mout_gdr", mout_gdr_p4x12, SRC_RIGHTBUS, 0, 1),
	MUX(0, "mout_clkout_rightbus", clkout_right_p4x12,
			CLKOUT_CMU_RIGHTBUS, 0, 5),

	MUX(CLK_MOUT_MPLL_USER_C, "mout_mpll_user_c", mout_mpll_user_p4x12,
			SRC_CPU, 24, 1),
	MUX(0, "mout_clkout_cpu", clkout_cpu_p4x12, CLKOUT_CMU_CPU, 0, 5),

	MUX(0, "mout_aclk266_gps", aclk_p4412, SRC_TOP1, 4, 1),
	MUX(0, "mout_aclk400_mcuisp", aclk_p4412, SRC_TOP1, 8, 1),
	MUX(CLK_MOUT_MPLL_USER_T, "mout_mpll_user_t", mout_mpll_user_p4x12,
			SRC_TOP1, 12, 1),
	MUX(0, "mout_user_aclk266_gps", mout_user_aclk266_gps_p4x12,
			SRC_TOP1, 16, 1),
	MUX(CLK_ACLK200, "aclk200", mout_user_aclk200_p4x12, SRC_TOP1, 20, 1),
	MUX(CLK_ACLK400_MCUISP, "aclk400_mcuisp",
		mout_user_aclk400_mcuisp_p4x12, SRC_TOP1, 24, 1),
	MUX(0, "mout_aclk200", aclk_p4412, SRC_TOP0, 12, 1),
	MUX(0, "mout_aclk100", aclk_p4412, SRC_TOP0, 16, 1),
	MUX(0, "mout_aclk160", aclk_p4412, SRC_TOP0, 20, 1),
	MUX(0, "mout_aclk133", aclk_p4412, SRC_TOP0, 24, 1),
	MUX(0, "mout_mdnie0", group1_p4x12, SRC_LCD0, 4, 4),
	MUX(0, "mout_mdnie_pwm0", group1_p4x12, SRC_LCD0, 8, 4),
	MUX(0, "mout_sata", sclk_ampll_p4x12, SRC_FSYS, 24, 1),
	MUX(0, "mout_jpeg0", sclk_ampll_p4x12, E4X12_SRC_CAM1, 0, 1),
	MUX(0, "mout_jpeg1", sclk_evpll_p, E4X12_SRC_CAM1, 4, 1),
	MUX(0, "mout_jpeg", mout_jpeg_p, E4X12_SRC_CAM1, 8, 1),
	MUX(CLK_SCLK_MPLL, "sclk_mpll", mout_mpll_p, SRC_DMC, 12, 1),
	MUX(CLK_SCLK_VPLL, "sclk_vpll", mout_vpll_p, SRC_TOP0, 8, 1),
	MUX(CLK_MOUT_CORE, "mout_core", mout_core_p4x12, SRC_CPU, 16, 1),
	MUX(0, "mout_hpm", mout_core_p4x12, SRC_CPU, 20, 1),
	MUX(CLK_MOUT_FIMC0, "mout_fimc0", group1_p4x12, SRC_CAM, 0, 4),
	MUX(CLK_MOUT_FIMC1, "mout_fimc1", group1_p4x12, SRC_CAM, 4, 4),
	MUX(CLK_MOUT_FIMC2, "mout_fimc2", group1_p4x12, SRC_CAM, 8, 4),
	MUX(CLK_MOUT_FIMC3, "mout_fimc3", group1_p4x12, SRC_CAM, 12, 4),
	MUX(CLK_MOUT_CAM0, "mout_cam0", group1_p4x12, SRC_CAM, 16, 4),
	MUX(CLK_MOUT_CAM1, "mout_cam1", group1_p4x12, SRC_CAM, 20, 4),
	MUX(CLK_MOUT_CSIS0, "mout_csis0", group1_p4x12, SRC_CAM, 24, 4),
	MUX(CLK_MOUT_CSIS1, "mout_csis1", group1_p4x12, SRC_CAM, 28, 4),
	MUX(0, "mout_mfc0", sclk_ampll_p4x12, SRC_MFC, 0, 1),
	MUX_F(CLK_MOUT_G3D0, "mout_g3d0", sclk_ampll_p4x12, SRC_G3D, 0, 1,
			CLK_SET_RATE_PARENT, 0),
	MUX(0, "mout_fimd0", group1_p4x12, SRC_LCD0, 0, 4),
	MUX(0, "mout_mipi0", group1_p4x12, SRC_LCD0, 12, 4),
	MUX(0, "mout_audio0", mout_audio0_p4x12, SRC_MAUDIO, 0, 4),
	MUX(0, "mout_mmc0", group1_p4x12, SRC_FSYS, 0, 4),
	MUX(0, "mout_mmc1", group1_p4x12, SRC_FSYS, 4, 4),
	MUX(0, "mout_mmc2", group1_p4x12, SRC_FSYS, 8, 4),
	MUX(0, "mout_mmc3", group1_p4x12, SRC_FSYS, 12, 4),
	MUX(0, "mout_mmc4", group1_p4x12, SRC_FSYS, 16, 4),
	MUX(0, "mout_mipihsi", aclk_p4412, SRC_FSYS, 24, 1),
	MUX(0, "mout_uart0", group1_p4x12, SRC_PERIL0, 0, 4),
	MUX(0, "mout_uart1", group1_p4x12, SRC_PERIL0, 4, 4),
	MUX(0, "mout_uart2", group1_p4x12, SRC_PERIL0, 8, 4),
	MUX(0, "mout_uart3", group1_p4x12, SRC_PERIL0, 12, 4),
	MUX(0, "mout_uart4", group1_p4x12, SRC_PERIL0, 16, 4),
	MUX(0, "mout_audio1", mout_audio1_p4x12, SRC_PERIL1, 0, 4),
	MUX(0, "mout_audio2", mout_audio2_p4x12, SRC_PERIL1, 4, 4),
	MUX(0, "mout_spi0", group1_p4x12, SRC_PERIL1, 16, 4),
	MUX(0, "mout_spi1", group1_p4x12, SRC_PERIL1, 20, 4),
	MUX(0, "mout_spi2", group1_p4x12, SRC_PERIL1, 24, 4),
	MUX(0, "mout_pwm_isp", group1_p4x12, E4X12_SRC_ISP, 0, 4),
	MUX(0, "mout_spi0_isp", group1_p4x12, E4X12_SRC_ISP, 4, 4),
	MUX(0, "mout_spi1_isp", group1_p4x12, E4X12_SRC_ISP, 8, 4),
	MUX(0, "mout_uart_isp", group1_p4x12, E4X12_SRC_ISP, 12, 4),
	MUX(0, "mout_clkout_top", clkout_top_p4x12, CLKOUT_CMU_TOP, 0, 5),

	MUX(0, "mout_c2c", sclk_ampll_p4210, SRC_DMC, 0, 1),
	MUX(0, "mout_pwi", mout_pwi_p4x12, SRC_DMC, 16, 4),
	MUX(0, "mout_g2d0", sclk_ampll_p4210, SRC_DMC, 20, 1),
	MUX(0, "mout_g2d1", sclk_evpll_p, SRC_DMC, 24, 1),
	MUX(0, "mout_g2d", mout_g2d_p, SRC_DMC, 28, 1),
	MUX(0, "mout_clkout_dmc", clkout_dmc_p4x12, CLKOUT_CMU_DMC, 0, 5),
पूर्ण;

/* list of भागider घड़ीs supported in all exynos4 soc's */
अटल स्थिर काष्ठा samsung_भाग_घड़ी exynos4_भाग_clks[] __initस्थिर = अणु
	DIV(CLK_DIV_GDL, "div_gdl", "mout_gdl", DIV_LEFTBUS, 0, 3),
	DIV(0, "div_gpl", "div_gdl", DIV_LEFTBUS, 4, 3),
	DIV(0, "div_clkout_leftbus", "mout_clkout_leftbus",
			CLKOUT_CMU_LEFTBUS, 8, 6),

	DIV(CLK_DIV_GDR, "div_gdr", "mout_gdr", DIV_RIGHTBUS, 0, 3),
	DIV(0, "div_gpr", "div_gdr", DIV_RIGHTBUS, 4, 3),
	DIV(0, "div_clkout_rightbus", "mout_clkout_rightbus",
			CLKOUT_CMU_RIGHTBUS, 8, 6),

	DIV(0, "div_core", "mout_core", DIV_CPU0, 0, 3),
	DIV(0, "div_corem0", "div_core2", DIV_CPU0, 4, 3),
	DIV(0, "div_corem1", "div_core2", DIV_CPU0, 8, 3),
	DIV(0, "div_periph", "div_core2", DIV_CPU0, 12, 3),
	DIV(0, "div_atb", "mout_core", DIV_CPU0, 16, 3),
	DIV(0, "div_pclk_dbg", "div_atb", DIV_CPU0, 20, 3),
	DIV(0, "div_core2", "div_core", DIV_CPU0, 28, 3),
	DIV(0, "div_copy", "mout_hpm", DIV_CPU1, 0, 3),
	DIV(0, "div_hpm", "div_copy", DIV_CPU1, 4, 3),
	DIV(0, "div_clkout_cpu", "mout_clkout_cpu", CLKOUT_CMU_CPU, 8, 6),

	DIV(0, "div_fimc0", "mout_fimc0", DIV_CAM, 0, 4),
	DIV(0, "div_fimc1", "mout_fimc1", DIV_CAM, 4, 4),
	DIV(0, "div_fimc2", "mout_fimc2", DIV_CAM, 8, 4),
	DIV(0, "div_fimc3", "mout_fimc3", DIV_CAM, 12, 4),
	DIV(0, "div_cam0", "mout_cam0", DIV_CAM, 16, 4),
	DIV(0, "div_cam1", "mout_cam1", DIV_CAM, 20, 4),
	DIV(0, "div_csis0", "mout_csis0", DIV_CAM, 24, 4),
	DIV(0, "div_csis1", "mout_csis1", DIV_CAM, 28, 4),
	DIV(CLK_SCLK_MFC, "sclk_mfc", "mout_mfc", DIV_MFC, 0, 4),
	DIV(CLK_SCLK_G3D, "sclk_g3d", "mout_g3d", DIV_G3D, 0, 4),
	DIV(0, "div_fimd0", "mout_fimd0", DIV_LCD0, 0, 4),
	DIV(0, "div_mipi0", "mout_mipi0", DIV_LCD0, 16, 4),
	DIV(0, "div_audio0", "mout_audio0", DIV_MAUDIO, 0, 4),
	DIV(CLK_SCLK_PCM0, "sclk_pcm0", "sclk_audio0", DIV_MAUDIO, 4, 8),
	DIV(0, "div_mmc0", "mout_mmc0", DIV_FSYS1, 0, 4),
	DIV(0, "div_mmc1", "mout_mmc1", DIV_FSYS1, 16, 4),
	DIV(0, "div_mmc2", "mout_mmc2", DIV_FSYS2, 0, 4),
	DIV(0, "div_mmc3", "mout_mmc3", DIV_FSYS2, 16, 4),
	DIV(CLK_SCLK_PIXEL, "sclk_pixel", "sclk_vpll", DIV_TV, 0, 4),
	DIV(CLK_ACLK100, "aclk100", "mout_aclk100", DIV_TOP, 4, 4),
	DIV(CLK_ACLK160, "aclk160", "mout_aclk160", DIV_TOP, 8, 3),
	DIV(CLK_ACLK133, "aclk133", "mout_aclk133", DIV_TOP, 12, 3),
	DIV(0, "div_onenand", "mout_onenand1", DIV_TOP, 16, 3),
	DIV(CLK_SCLK_SLIMBUS, "sclk_slimbus", "sclk_epll", DIV_PERIL3, 4, 4),
	DIV(CLK_SCLK_PCM1, "sclk_pcm1", "sclk_audio1", DIV_PERIL4, 4, 8),
	DIV(CLK_SCLK_PCM2, "sclk_pcm2", "sclk_audio2", DIV_PERIL4, 20, 8),
	DIV(CLK_SCLK_I2S1, "sclk_i2s1", "sclk_audio1", DIV_PERIL5, 0, 6),
	DIV(CLK_SCLK_I2S2, "sclk_i2s2", "sclk_audio2", DIV_PERIL5, 8, 6),
	DIV(0, "div_mmc4", "mout_mmc4", DIV_FSYS3, 0, 4),
	DIV_F(0, "div_mmc_pre4", "div_mmc4", DIV_FSYS3, 8, 8,
			CLK_SET_RATE_PARENT, 0),
	DIV(0, "div_uart0", "mout_uart0", DIV_PERIL0, 0, 4),
	DIV(0, "div_uart1", "mout_uart1", DIV_PERIL0, 4, 4),
	DIV(0, "div_uart2", "mout_uart2", DIV_PERIL0, 8, 4),
	DIV(0, "div_uart3", "mout_uart3", DIV_PERIL0, 12, 4),
	DIV(0, "div_uart4", "mout_uart4", DIV_PERIL0, 16, 4),
	DIV(0, "div_spi0", "mout_spi0", DIV_PERIL1, 0, 4),
	DIV(0, "div_spi_pre0", "div_spi0", DIV_PERIL1, 8, 8),
	DIV(0, "div_spi1", "mout_spi1", DIV_PERIL1, 16, 4),
	DIV(0, "div_spi_pre1", "div_spi1", DIV_PERIL1, 24, 8),
	DIV(0, "div_spi2", "mout_spi2", DIV_PERIL2, 0, 4),
	DIV(0, "div_spi_pre2", "div_spi2", DIV_PERIL2, 8, 8),
	DIV(0, "div_audio1", "mout_audio1", DIV_PERIL4, 0, 4),
	DIV(0, "div_audio2", "mout_audio2", DIV_PERIL4, 16, 4),
	DIV(CLK_SCLK_APLL, "sclk_apll", "mout_apll", DIV_CPU0, 24, 3),
	DIV_F(0, "div_mipi_pre0", "div_mipi0", DIV_LCD0, 20, 4,
			CLK_SET_RATE_PARENT, 0),
	DIV_F(0, "div_mmc_pre0", "div_mmc0", DIV_FSYS1, 8, 8,
			CLK_SET_RATE_PARENT, 0),
	DIV_F(0, "div_mmc_pre1", "div_mmc1", DIV_FSYS1, 24, 8,
			CLK_SET_RATE_PARENT, 0),
	DIV_F(0, "div_mmc_pre2", "div_mmc2", DIV_FSYS2, 8, 8,
			CLK_SET_RATE_PARENT, 0),
	DIV_F(0, "div_mmc_pre3", "div_mmc3", DIV_FSYS2, 24, 8,
			CLK_SET_RATE_PARENT, 0),
	DIV(0, "div_clkout_top", "mout_clkout_top", CLKOUT_CMU_TOP, 8, 6),

	DIV(CLK_DIV_ACP, "div_acp", "mout_dmc_bus", DIV_DMC0, 0, 3),
	DIV(0, "div_acp_pclk", "div_acp", DIV_DMC0, 4, 3),
	DIV(0, "div_dphy", "mout_dphy", DIV_DMC0, 8, 3),
	DIV(CLK_DIV_DMC, "div_dmc", "mout_dmc_bus", DIV_DMC0, 12, 3),
	DIV(0, "div_dmcd", "div_dmc", DIV_DMC0, 16, 3),
	DIV(0, "div_dmcp", "div_dmcd", DIV_DMC0, 20, 3),
	DIV(0, "div_pwi", "mout_pwi", DIV_DMC1, 8, 4),
	DIV(0, "div_clkout_dmc", "mout_clkout_dmc", CLKOUT_CMU_DMC, 8, 6),
पूर्ण;

/* list of भागider घड़ीs supported in exynos4210 soc */
अटल स्थिर काष्ठा samsung_भाग_घड़ी exynos4210_भाग_clks[] __initस्थिर = अणु
	DIV(CLK_ACLK200, "aclk200", "mout_aclk200", DIV_TOP, 0, 3),
	DIV(CLK_SCLK_FIMG2D, "sclk_fimg2d", "mout_g2d", DIV_IMAGE, 0, 4),
	DIV(0, "div_fimd1", "mout_fimd1", E4210_DIV_LCD1, 0, 4),
	DIV(0, "div_mipi1", "mout_mipi1", E4210_DIV_LCD1, 16, 4),
	DIV(0, "div_sata", "mout_sata", DIV_FSYS0, 20, 4),
	DIV_F(0, "div_mipi_pre1", "div_mipi1", E4210_DIV_LCD1, 20, 4,
			CLK_SET_RATE_PARENT, 0),
पूर्ण;

/* list of भागider घड़ीs supported in exynos4x12 soc */
अटल स्थिर काष्ठा samsung_भाग_घड़ी exynos4x12_भाग_clks[] __initस्थिर = अणु
	DIV(0, "div_mdnie0", "mout_mdnie0", DIV_LCD0, 4, 4),
	DIV(0, "div_mdnie_pwm0", "mout_mdnie_pwm0", DIV_LCD0, 8, 4),
	DIV(0, "div_mdnie_pwm_pre0", "div_mdnie_pwm0", DIV_LCD0, 12, 4),
	DIV(0, "div_mipihsi", "mout_mipihsi", DIV_FSYS0, 20, 4),
	DIV(0, "div_jpeg", "mout_jpeg", E4X12_DIV_CAM1, 0, 4),
	DIV(CLK_DIV_ACLK200, "div_aclk200", "mout_aclk200", DIV_TOP, 0, 3),
	DIV(0, "div_aclk266_gps", "mout_aclk266_gps", DIV_TOP, 20, 3),
	DIV(CLK_DIV_ACLK400_MCUISP, "div_aclk400_mcuisp", "mout_aclk400_mcuisp",
						DIV_TOP, 24, 3),
	DIV(0, "div_pwm_isp", "mout_pwm_isp", E4X12_DIV_ISP, 0, 4),
	DIV(0, "div_spi0_isp", "mout_spi0_isp", E4X12_DIV_ISP, 4, 4),
	DIV(0, "div_spi0_isp_pre", "div_spi0_isp", E4X12_DIV_ISP, 8, 8),
	DIV(0, "div_spi1_isp", "mout_spi1_isp", E4X12_DIV_ISP, 16, 4),
	DIV(0, "div_spi1_isp_pre", "div_spi1_isp", E4X12_DIV_ISP, 20, 8),
	DIV(0, "div_uart_isp", "mout_uart_isp", E4X12_DIV_ISP, 28, 4),
	DIV(CLK_SCLK_FIMG2D, "sclk_fimg2d", "mout_g2d", DIV_DMC1, 0, 4),
	DIV(CLK_DIV_C2C, "div_c2c", "mout_c2c", DIV_DMC1, 4, 3),
	DIV(0, "div_c2c_aclk", "div_c2c", DIV_DMC1, 12, 3),
पूर्ण;

/* list of gate घड़ीs supported in all exynos4 soc's */
अटल स्थिर काष्ठा samsung_gate_घड़ी exynos4_gate_clks[] __initस्थिर = अणु
	GATE(CLK_PPMULEFT, "ppmuleft", "aclk200", GATE_IP_LEFTBUS, 1, 0, 0),
	GATE(CLK_PPMURIGHT, "ppmuright", "aclk200", GATE_IP_RIGHTBUS, 1, 0, 0),
	GATE(CLK_SCLK_HDMI, "sclk_hdmi", "mout_hdmi", SRC_MASK_TV, 0, 0, 0),
	GATE(CLK_SCLK_SPDIF, "sclk_spdif", "mout_spdif", SRC_MASK_PERIL1, 8, 0,
		0),
	GATE(CLK_JPEG, "jpeg", "aclk160", GATE_IP_CAM, 6, 0, 0),
	GATE(CLK_MIE0, "mie0", "aclk160", GATE_IP_LCD0, 1, 0, 0),
	GATE(CLK_DSIM0, "dsim0", "aclk160", GATE_IP_LCD0, 3, 0, 0),
	GATE(CLK_FIMD1, "fimd1", "aclk160", E4210_GATE_IP_LCD1, 0, 0, 0),
	GATE(CLK_MIE1, "mie1", "aclk160", E4210_GATE_IP_LCD1, 1, 0, 0),
	GATE(CLK_DSIM1, "dsim1", "aclk160", E4210_GATE_IP_LCD1, 3, 0, 0),
	GATE(CLK_SMMU_FIMD1, "smmu_fimd1", "aclk160", E4210_GATE_IP_LCD1, 4, 0,
		0),
	GATE(CLK_TSI, "tsi", "aclk133", GATE_IP_FSYS, 4, 0, 0),
	GATE(CLK_SROMC, "sromc", "aclk133", GATE_IP_FSYS, 11, 0, 0),
	GATE(CLK_G3D, "g3d", "aclk200", GATE_IP_G3D, 0, 0, 0),
	GATE(CLK_PPMUG3D, "ppmug3d", "aclk200", GATE_IP_G3D, 1, 0, 0),
	GATE(CLK_USB_DEVICE, "usb_device", "aclk133", GATE_IP_FSYS, 13, 0, 0),
	GATE(CLK_ONEन_अंकD, "onenand", "aclk133", GATE_IP_FSYS, 15, 0, 0),
	GATE(CLK_NFCON, "nfcon", "aclk133", GATE_IP_FSYS, 16, 0, 0),
	GATE(CLK_GPS, "gps", "aclk133", GATE_IP_GPS, 0, 0, 0),
	GATE(CLK_SMMU_GPS, "smmu_gps", "aclk133", GATE_IP_GPS, 1, 0, 0),
	GATE(CLK_PPMUGPS, "ppmugps", "aclk200", GATE_IP_GPS, 2, 0, 0),
	GATE(CLK_SLIMBUS, "slimbus", "aclk100", GATE_IP_PERIL, 25, 0, 0),
	GATE(CLK_SCLK_CAM0, "sclk_cam0", "div_cam0", GATE_SCLK_CAM, 4,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_CAM1, "sclk_cam1", "div_cam1", GATE_SCLK_CAM, 5,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MIPI0, "sclk_mipi0", "div_mipi_pre0",
			SRC_MASK_LCD0, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_AUDIO0, "sclk_audio0", "div_audio0", SRC_MASK_MAUDIO, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_AUDIO1, "sclk_audio1", "div_audio1", SRC_MASK_PERIL1, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_VP, "vp", "aclk160", GATE_IP_TV, 0, 0, 0),
	GATE(CLK_MIXER, "mixer", "aclk160", GATE_IP_TV, 1, 0, 0),
	GATE(CLK_HDMI, "hdmi", "aclk160", GATE_IP_TV, 3, 0, 0),
	GATE(CLK_PWM, "pwm", "aclk100", GATE_IP_PERIL, 24, 0, 0),
	GATE(CLK_SDMMC4, "sdmmc4", "aclk133", GATE_IP_FSYS, 9, 0, 0),
	GATE(CLK_USB_HOST, "usb_host", "aclk133", GATE_IP_FSYS, 12, 0, 0),
	GATE(CLK_SCLK_FIMC0, "sclk_fimc0", "div_fimc0", SRC_MASK_CAM, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_FIMC1, "sclk_fimc1", "div_fimc1", SRC_MASK_CAM, 4,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_FIMC2, "sclk_fimc2", "div_fimc2", SRC_MASK_CAM, 8,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_FIMC3, "sclk_fimc3", "div_fimc3", SRC_MASK_CAM, 12,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_CSIS0, "sclk_csis0", "div_csis0", SRC_MASK_CAM, 24,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_CSIS1, "sclk_csis1", "div_csis1", SRC_MASK_CAM, 28,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_FIMD0, "sclk_fimd0", "div_fimd0", SRC_MASK_LCD0, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC0, "sclk_mmc0", "div_mmc_pre0", SRC_MASK_FSYS, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC1, "sclk_mmc1", "div_mmc_pre1", SRC_MASK_FSYS, 4,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC2, "sclk_mmc2", "div_mmc_pre2", SRC_MASK_FSYS, 8,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC3, "sclk_mmc3", "div_mmc_pre3", SRC_MASK_FSYS, 12,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC4, "sclk_mmc4", "div_mmc_pre4", SRC_MASK_FSYS, 16,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART0, "uclk0", "div_uart0", SRC_MASK_PERIL0, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART1, "uclk1", "div_uart1", SRC_MASK_PERIL0, 4,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART2, "uclk2", "div_uart2", SRC_MASK_PERIL0, 8,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART3, "uclk3", "div_uart3", SRC_MASK_PERIL0, 12,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART4, "uclk4", "div_uart4", SRC_MASK_PERIL0, 16,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_AUDIO2, "sclk_audio2", "div_audio2", SRC_MASK_PERIL1, 4,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SPI0, "sclk_spi0", "div_spi_pre0", SRC_MASK_PERIL1, 16,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SPI1, "sclk_spi1", "div_spi_pre1", SRC_MASK_PERIL1, 20,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SPI2, "sclk_spi2", "div_spi_pre2", SRC_MASK_PERIL1, 24,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_FIMC0, "fimc0", "aclk160", GATE_IP_CAM, 0,
			0, 0),
	GATE(CLK_FIMC1, "fimc1", "aclk160", GATE_IP_CAM, 1,
			0, 0),
	GATE(CLK_FIMC2, "fimc2", "aclk160", GATE_IP_CAM, 2,
			0, 0),
	GATE(CLK_FIMC3, "fimc3", "aclk160", GATE_IP_CAM, 3,
			0, 0),
	GATE(CLK_CSIS0, "csis0", "aclk160", GATE_IP_CAM, 4,
			0, 0),
	GATE(CLK_CSIS1, "csis1", "aclk160", GATE_IP_CAM, 5,
			0, 0),
	GATE(CLK_SMMU_FIMC0, "smmu_fimc0", "aclk160", GATE_IP_CAM, 7,
			0, 0),
	GATE(CLK_SMMU_FIMC1, "smmu_fimc1", "aclk160", GATE_IP_CAM, 8,
			0, 0),
	GATE(CLK_SMMU_FIMC2, "smmu_fimc2", "aclk160", GATE_IP_CAM, 9,
			0, 0),
	GATE(CLK_SMMU_FIMC3, "smmu_fimc3", "aclk160", GATE_IP_CAM, 10,
			0, 0),
	GATE(CLK_SMMU_JPEG, "smmu_jpeg", "aclk160", GATE_IP_CAM, 11,
			0, 0),
	GATE(CLK_PPMUCAMIF, "ppmucamif", "aclk160", GATE_IP_CAM, 16, 0, 0),
	GATE(CLK_PIXELASYNCM0, "pxl_async0", "aclk160", GATE_IP_CAM, 17, 0, 0),
	GATE(CLK_PIXELASYNCM1, "pxl_async1", "aclk160", GATE_IP_CAM, 18, 0, 0),
	GATE(CLK_SMMU_TV, "smmu_tv", "aclk160", GATE_IP_TV, 4,
			0, 0),
	GATE(CLK_PPMUTV, "ppmutv", "aclk160", GATE_IP_TV, 5, 0, 0),
	GATE(CLK_MFC, "mfc", "aclk100", GATE_IP_MFC, 0, 0, 0),
	GATE(CLK_SMMU_MFCL, "smmu_mfcl", "aclk100", GATE_IP_MFC, 1,
			0, 0),
	GATE(CLK_SMMU_MFCR, "smmu_mfcr", "aclk100", GATE_IP_MFC, 2,
			0, 0),
	GATE(CLK_PPMUMFC_L, "ppmumfc_l", "aclk100", GATE_IP_MFC, 3, 0, 0),
	GATE(CLK_PPMUMFC_R, "ppmumfc_r", "aclk100", GATE_IP_MFC, 4, 0, 0),
	GATE(CLK_FIMD0, "fimd0", "aclk160", GATE_IP_LCD0, 0,
			0, 0),
	GATE(CLK_SMMU_FIMD0, "smmu_fimd0", "aclk160", GATE_IP_LCD0, 4,
			0, 0),
	GATE(CLK_PPMULCD0, "ppmulcd0", "aclk160", GATE_IP_LCD0, 5, 0, 0),
	GATE(CLK_PDMA0, "pdma0", "aclk133", GATE_IP_FSYS, 0,
			0, 0),
	GATE(CLK_PDMA1, "pdma1", "aclk133", GATE_IP_FSYS, 1,
			0, 0),
	GATE(CLK_SDMMC0, "sdmmc0", "aclk133", GATE_IP_FSYS, 5,
			0, 0),
	GATE(CLK_SDMMC1, "sdmmc1", "aclk133", GATE_IP_FSYS, 6,
			0, 0),
	GATE(CLK_SDMMC2, "sdmmc2", "aclk133", GATE_IP_FSYS, 7,
			0, 0),
	GATE(CLK_SDMMC3, "sdmmc3", "aclk133", GATE_IP_FSYS, 8,
			0, 0),
	GATE(CLK_PPMUखाता, "ppmufile", "aclk133", GATE_IP_FSYS, 17, 0, 0),
	GATE(CLK_UART0, "uart0", "aclk100", GATE_IP_PERIL, 0,
			0, 0),
	GATE(CLK_UART1, "uart1", "aclk100", GATE_IP_PERIL, 1,
			0, 0),
	GATE(CLK_UART2, "uart2", "aclk100", GATE_IP_PERIL, 2,
			0, 0),
	GATE(CLK_UART3, "uart3", "aclk100", GATE_IP_PERIL, 3,
			0, 0),
	GATE(CLK_UART4, "uart4", "aclk100", GATE_IP_PERIL, 4,
			0, 0),
	GATE(CLK_I2C0, "i2c0", "aclk100", GATE_IP_PERIL, 6,
			0, 0),
	GATE(CLK_I2C1, "i2c1", "aclk100", GATE_IP_PERIL, 7,
			0, 0),
	GATE(CLK_I2C2, "i2c2", "aclk100", GATE_IP_PERIL, 8,
			0, 0),
	GATE(CLK_I2C3, "i2c3", "aclk100", GATE_IP_PERIL, 9,
			0, 0),
	GATE(CLK_I2C4, "i2c4", "aclk100", GATE_IP_PERIL, 10,
			0, 0),
	GATE(CLK_I2C5, "i2c5", "aclk100", GATE_IP_PERIL, 11,
			0, 0),
	GATE(CLK_I2C6, "i2c6", "aclk100", GATE_IP_PERIL, 12,
			0, 0),
	GATE(CLK_I2C7, "i2c7", "aclk100", GATE_IP_PERIL, 13,
			0, 0),
	GATE(CLK_I2C_HDMI, "i2c-hdmi", "aclk100", GATE_IP_PERIL, 14,
			0, 0),
	GATE(CLK_SPI0, "spi0", "aclk100", GATE_IP_PERIL, 16,
			0, 0),
	GATE(CLK_SPI1, "spi1", "aclk100", GATE_IP_PERIL, 17,
			0, 0),
	GATE(CLK_SPI2, "spi2", "aclk100", GATE_IP_PERIL, 18,
			0, 0),
	GATE(CLK_I2S1, "i2s1", "aclk100", GATE_IP_PERIL, 20,
			0, 0),
	GATE(CLK_I2S2, "i2s2", "aclk100", GATE_IP_PERIL, 21,
			0, 0),
	GATE(CLK_PCM1, "pcm1", "aclk100", GATE_IP_PERIL, 22,
			0, 0),
	GATE(CLK_PCM2, "pcm2", "aclk100", GATE_IP_PERIL, 23,
			0, 0),
	GATE(CLK_SPDIF, "spdif", "aclk100", GATE_IP_PERIL, 26,
			0, 0),
	GATE(CLK_AC97, "ac97", "aclk100", GATE_IP_PERIL, 27,
			0, 0),
	GATE(CLK_SSS, "sss", "aclk133", GATE_IP_DMC, 4, 0, 0),
	GATE(CLK_PPMUDMC0, "ppmudmc0", "aclk133", GATE_IP_DMC, 8, 0, 0),
	GATE(CLK_PPMUDMC1, "ppmudmc1", "aclk133", GATE_IP_DMC, 9, 0, 0),
	GATE(CLK_PPMUCPU, "ppmucpu", "aclk133", GATE_IP_DMC, 10, 0, 0),
	GATE(CLK_PPMUACP, "ppmuacp", "aclk133", GATE_IP_DMC, 16, 0, 0),

	GATE(CLK_OUT_LEFTBUS, "clkout_leftbus", "div_clkout_leftbus",
			CLKOUT_CMU_LEFTBUS, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_OUT_RIGHTBUS, "clkout_rightbus", "div_clkout_rightbus",
			CLKOUT_CMU_RIGHTBUS, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_OUT_TOP, "clkout_top", "div_clkout_top",
			CLKOUT_CMU_TOP, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_OUT_DMC, "clkout_dmc", "div_clkout_dmc",
			CLKOUT_CMU_DMC, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_OUT_CPU, "clkout_cpu", "div_clkout_cpu",
			CLKOUT_CMU_CPU, 16, CLK_SET_RATE_PARENT, 0),
पूर्ण;

/* list of gate घड़ीs supported in exynos4210 soc */
अटल स्थिर काष्ठा samsung_gate_घड़ी exynos4210_gate_clks[] __initस्थिर = अणु
	GATE(CLK_TVENC, "tvenc", "aclk160", GATE_IP_TV, 2, 0, 0),
	GATE(CLK_G2D, "g2d", "aclk200", E4210_GATE_IP_IMAGE, 0, 0, 0),
	GATE(CLK_ROTATOR, "rotator", "aclk200", E4210_GATE_IP_IMAGE, 1, 0, 0),
	GATE(CLK_MDMA, "mdma", "aclk200", E4210_GATE_IP_IMAGE, 2, 0, 0),
	GATE(CLK_SMMU_G2D, "smmu_g2d", "aclk200", E4210_GATE_IP_IMAGE, 3, 0, 0),
	GATE(CLK_SMMU_MDMA, "smmu_mdma", "aclk200", E4210_GATE_IP_IMAGE, 5, 0,
		0),
	GATE(CLK_PPMUIMAGE, "ppmuimage", "aclk200", E4210_GATE_IP_IMAGE, 9, 0,
		0),
	GATE(CLK_PPMULCD1, "ppmulcd1", "aclk160", E4210_GATE_IP_LCD1, 5, 0, 0),
	GATE(CLK_PCIE_PHY, "pcie_phy", "aclk133", GATE_IP_FSYS, 2, 0, 0),
	GATE(CLK_SATA_PHY, "sata_phy", "aclk133", GATE_IP_FSYS, 3, 0, 0),
	GATE(CLK_SATA, "sata", "aclk133", GATE_IP_FSYS, 10, 0, 0),
	GATE(CLK_PCIE, "pcie", "aclk133", GATE_IP_FSYS, 14, 0, 0),
	GATE(CLK_SMMU_PCIE, "smmu_pcie", "aclk133", GATE_IP_FSYS, 18, 0, 0),
	GATE(CLK_MODEMIF, "modemif", "aclk100", GATE_IP_PERIL, 28, 0, 0),
	GATE(CLK_CHIPID, "chipid", "aclk100", E4210_GATE_IP_PERIR, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SYSREG, "sysreg", "aclk100", E4210_GATE_IP_PERIR, 0,
			CLK_IGNORE_UNUSED, 0),
	GATE(CLK_HDMI_CEC, "hdmi_cec", "aclk100", E4210_GATE_IP_PERIR, 11, 0,
		0),
	GATE(CLK_SMMU_ROTATOR, "smmu_rotator", "aclk200",
			E4210_GATE_IP_IMAGE, 4, 0, 0),
	GATE(CLK_SCLK_MIPI1, "sclk_mipi1", "div_mipi_pre1",
			E4210_SRC_MASK_LCD1, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SATA, "sclk_sata", "div_sata",
			SRC_MASK_FSYS, 24, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MIXER, "sclk_mixer", "mout_mixer", SRC_MASK_TV, 4, 0, 0),
	GATE(CLK_SCLK_DAC, "sclk_dac", "mout_dac", SRC_MASK_TV, 8, 0, 0),
	GATE(CLK_TSADC, "tsadc", "aclk100", GATE_IP_PERIL, 15,
			0, 0),
	GATE(CLK_MCT, "mct", "aclk100", E4210_GATE_IP_PERIR, 13,
			0, 0),
	GATE(CLK_WDT, "watchdog", "aclk100", E4210_GATE_IP_PERIR, 14,
			0, 0),
	GATE(CLK_RTC, "rtc", "aclk100", E4210_GATE_IP_PERIR, 15,
			0, 0),
	GATE(CLK_KEYIF, "keyif", "aclk100", E4210_GATE_IP_PERIR, 16,
			0, 0),
	GATE(CLK_SCLK_FIMD1, "sclk_fimd1", "div_fimd1", E4210_SRC_MASK_LCD1, 0,
			CLK_SET_RATE_PARENT, 0),
	GATE(CLK_TMU_APBIF, "tmu_apbif", "aclk100", E4210_GATE_IP_PERIR, 17, 0,
		0),
पूर्ण;

/* list of gate घड़ीs supported in exynos4x12 soc */
अटल स्थिर काष्ठा samsung_gate_घड़ी exynos4x12_gate_clks[] __initस्थिर = अणु
	GATE(CLK_ASYNC_G3D, "async_g3d", "aclk200", GATE_IP_LEFTBUS, 6, 0, 0),
	GATE(CLK_AUDSS, "audss", "sclk_epll", E4X12_GATE_IP_MAUDIO, 0, 0, 0),
	GATE(CLK_MDNIE0, "mdnie0", "aclk160", GATE_IP_LCD0, 2, 0, 0),
	GATE(CLK_ROTATOR, "rotator", "aclk200", E4X12_GATE_IP_IMAGE, 1, 0, 0),
	GATE(CLK_MDMA, "mdma", "aclk200", E4X12_GATE_IP_IMAGE, 2, 0, 0),
	GATE(CLK_SMMU_MDMA, "smmu_mdma", "aclk200", E4X12_GATE_IP_IMAGE, 5, 0,
		0),
	GATE(CLK_PPMUIMAGE, "ppmuimage", "aclk200", E4X12_GATE_IP_IMAGE, 9, 0,
		0),
	GATE(CLK_TSADC, "tsadc", "aclk133", E4X12_GATE_BUS_FSYS1, 16, 0, 0),
	GATE(CLK_MIPI_HSI, "mipi_hsi", "aclk133", GATE_IP_FSYS, 10, 0, 0),
	GATE(CLK_CHIPID, "chipid", "aclk100", E4X12_GATE_IP_PERIR, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SYSREG, "sysreg", "aclk100", E4X12_GATE_IP_PERIR, 1,
			CLK_IGNORE_UNUSED, 0),
	GATE(CLK_HDMI_CEC, "hdmi_cec", "aclk100", E4X12_GATE_IP_PERIR, 11, 0,
		0),
	GATE(CLK_SCLK_MDNIE0, "sclk_mdnie0", "div_mdnie0",
			SRC_MASK_LCD0, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MDNIE_PWM0, "sclk_mdnie_pwm0", "div_mdnie_pwm_pre0",
			SRC_MASK_LCD0, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MIPIHSI, "sclk_mipihsi", "div_mipihsi",
			SRC_MASK_FSYS, 24, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SMMU_ROTATOR, "smmu_rotator", "aclk200",
			E4X12_GATE_IP_IMAGE, 4, 0, 0),
	GATE(CLK_MCT, "mct", "aclk100", E4X12_GATE_IP_PERIR, 13,
			0, 0),
	GATE(CLK_RTC, "rtc", "aclk100", E4X12_GATE_IP_PERIR, 15,
			0, 0),
	GATE(CLK_KEYIF, "keyif", "aclk100", E4X12_GATE_IP_PERIR, 16, 0, 0),
	GATE(CLK_PWM_ISP_SCLK, "pwm_isp_sclk", "div_pwm_isp",
			E4X12_GATE_IP_ISP, 0, 0, 0),
	GATE(CLK_SPI0_ISP_SCLK, "spi0_isp_sclk", "div_spi0_isp_pre",
			E4X12_GATE_IP_ISP, 1, 0, 0),
	GATE(CLK_SPI1_ISP_SCLK, "spi1_isp_sclk", "div_spi1_isp_pre",
			E4X12_GATE_IP_ISP, 2, 0, 0),
	GATE(CLK_UART_ISP_SCLK, "uart_isp_sclk", "div_uart_isp",
			E4X12_GATE_IP_ISP, 3, 0, 0),
	GATE(CLK_WDT, "watchdog", "aclk100", E4X12_GATE_IP_PERIR, 14, 0, 0),
	GATE(CLK_PCM0, "pcm0", "aclk100", E4X12_GATE_IP_MAUDIO, 2,
			0, 0),
	GATE(CLK_I2S0, "i2s0", "aclk100", E4X12_GATE_IP_MAUDIO, 3,
			0, 0),
	GATE(CLK_G2D, "g2d", "aclk200", GATE_IP_DMC, 23, 0, 0),
	GATE(CLK_SMMU_G2D, "smmu_g2d", "aclk200", GATE_IP_DMC, 24, 0, 0),
	GATE(CLK_TMU_APBIF, "tmu_apbif", "aclk100", E4X12_GATE_IP_PERIR, 17, 0,
		0),
पूर्ण;

/*
 * The parent of the fin_pll घड़ी is selected by the XOM[0] bit. This bit
 * resides in chipid रेजिस्टर space, outside of the घड़ी controller memory
 * mapped space. So to determine the parent of fin_pll घड़ी, the chipid
 * controller is first remapped and the value of XOM[0] bit is पढ़ो to
 * determine the parent घड़ी.
 */
अटल अचिन्हित दीर्घ __init exynos4_get_xom(व्योम)
अणु
	अचिन्हित दीर्घ xom = 0;
	व्योम __iomem *chipid_base;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "samsung,exynos4210-chipid");
	अगर (np) अणु
		chipid_base = of_iomap(np, 0);

		अगर (chipid_base)
			xom = पढ़ोl(chipid_base + 8);

		iounmap(chipid_base);
		of_node_put(np);
	पूर्ण

	वापस xom;
पूर्ण

अटल व्योम __init exynos4_clk_रेजिस्टर_finpll(काष्ठा samsung_clk_provider *ctx)
अणु
	काष्ठा samsung_fixed_rate_घड़ी fclk;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ finpll_f = 24000000;
	अक्षर *parent_name;
	अचिन्हित पूर्णांक xom = exynos4_get_xom();

	parent_name = xom & 1 ? "xusbxti" : "xxti";
	clk = clk_get(शून्य, parent_name);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to lookup parent clock %s, assuming "
			"fin_pll clock frequency is 24MHz\n", __func__,
			parent_name);
	पूर्ण अन्यथा अणु
		finpll_f = clk_get_rate(clk);
	पूर्ण

	fclk.id = CLK_FIN_PLL;
	fclk.name = "fin_pll";
	fclk.parent_name = शून्य;
	fclk.flags = 0;
	fclk.fixed_rate = finpll_f;
	samsung_clk_रेजिस्टर_fixed_rate(ctx, &fclk, 1);

पूर्ण

अटल स्थिर काष्ठा of_device_id ext_clk_match[] __initस्थिर = अणु
	अणु .compatible = "samsung,clock-xxti", .data = (व्योम *)0, पूर्ण,
	अणु .compatible = "samsung,clock-xusbxti", .data = (व्योम *)1, पूर्ण,
	अणुपूर्ण,
पूर्ण;

/* PLLs PMS values */
अटल स्थिर काष्ठा samsung_pll_rate_table exynos4210_apll_rates[] __initस्थिर = अणु
	PLL_4508_RATE(24 * MHZ, 1200000000, 150,  3, 1, 28),
	PLL_4508_RATE(24 * MHZ, 1000000000, 250,  6, 1, 28),
	PLL_4508_RATE(24 * MHZ,  800000000, 200,  6, 1, 28),
	PLL_4508_RATE(24 * MHZ,  666857142, 389, 14, 1, 13),
	PLL_4508_RATE(24 * MHZ,  600000000, 100,  4, 1, 13),
	PLL_4508_RATE(24 * MHZ,  533000000, 533, 24, 1,  5),
	PLL_4508_RATE(24 * MHZ,  500000000, 250,  6, 2, 28),
	PLL_4508_RATE(24 * MHZ,  400000000, 200,  6, 2, 28),
	PLL_4508_RATE(24 * MHZ,  200000000, 200,  6, 3, 28),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table exynos4210_epll_rates[] __initस्थिर = अणु
	PLL_4600_RATE(24 * MHZ, 192000000, 48, 3, 1,     0, 0),
	PLL_4600_RATE(24 * MHZ, 180633605, 45, 3, 1, 10381, 0),
	PLL_4600_RATE(24 * MHZ, 180000000, 45, 3, 1,     0, 0),
	PLL_4600_RATE(24 * MHZ,  73727996, 73, 3, 3, 47710, 1),
	PLL_4600_RATE(24 * MHZ,  67737602, 90, 4, 3, 20762, 1),
	PLL_4600_RATE(24 * MHZ,  49151992, 49, 3, 3,  9961, 0),
	PLL_4600_RATE(24 * MHZ,  45158401, 45, 3, 3, 10381, 0),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table exynos4210_vpll_rates[] __initस्थिर = अणु
	PLL_4650_RATE(24 * MHZ, 360000000, 44, 3, 0, 1024, 0, 14, 0),
	PLL_4650_RATE(24 * MHZ, 324000000, 53, 2, 1, 1024, 1,  1, 1),
	PLL_4650_RATE(24 * MHZ, 259617187, 63, 3, 1, 1950, 0, 20, 1),
	PLL_4650_RATE(24 * MHZ, 110000000, 53, 3, 2, 2048, 0, 17, 0),
	PLL_4650_RATE(24 * MHZ,  55360351, 53, 3, 3, 2417, 0, 17, 0),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table exynos4x12_apll_rates[] __initस्थिर = अणु
	PLL_35XX_RATE(24 * MHZ, 1704000000, 213, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 1600000000, 200, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 1500000000, 250, 4, 0),
	PLL_35XX_RATE(24 * MHZ, 1400000000, 175, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 1300000000, 325, 6, 0),
	PLL_35XX_RATE(24 * MHZ, 1200000000, 200, 4, 0),
	PLL_35XX_RATE(24 * MHZ, 1100000000, 275, 6, 0),
	PLL_35XX_RATE(24 * MHZ, 1000000000, 125, 3, 0),
	PLL_35XX_RATE(24 * MHZ,  900000000, 150, 4, 0),
	PLL_35XX_RATE(24 * MHZ,  800000000, 100, 3, 0),
	PLL_35XX_RATE(24 * MHZ,  700000000, 175, 3, 1),
	PLL_35XX_RATE(24 * MHZ,  600000000, 200, 4, 1),
	PLL_35XX_RATE(24 * MHZ,  500000000, 125, 3, 1),
	PLL_35XX_RATE(24 * MHZ,  400000000, 100, 3, 1),
	PLL_35XX_RATE(24 * MHZ,  300000000, 200, 4, 2),
	PLL_35XX_RATE(24 * MHZ,  200000000, 100, 3, 2),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table exynos4x12_epll_rates[] __initस्थिर = अणु
	PLL_36XX_RATE(24 * MHZ, 196608001, 197, 3, 3, -25690),
	PLL_36XX_RATE(24 * MHZ, 192000000, 48, 3, 1,     0),
	PLL_36XX_RATE(24 * MHZ, 180633605, 45, 3, 1, 10381),
	PLL_36XX_RATE(24 * MHZ, 180000000, 45, 3, 1,     0),
	PLL_36XX_RATE(24 * MHZ,  73727996, 73, 3, 3, 47710),
	PLL_36XX_RATE(24 * MHZ,  67737602, 90, 4, 3, 20762),
	PLL_36XX_RATE(24 * MHZ,  49151992, 49, 3, 3,  9961),
	PLL_36XX_RATE(24 * MHZ,  45158401, 45, 3, 3, 10381),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table exynos4x12_vpll_rates[] __initस्थिर = अणु
	PLL_36XX_RATE(24 * MHZ, 533000000, 133, 3, 1, 16384),
	PLL_36XX_RATE(24 * MHZ, 440000000, 110, 3, 1,     0),
	PLL_36XX_RATE(24 * MHZ, 350000000, 175, 3, 2,     0),
	PLL_36XX_RATE(24 * MHZ, 266000000, 133, 3, 2,     0),
	PLL_36XX_RATE(24 * MHZ, 160000000, 160, 3, 3,     0),
	PLL_36XX_RATE(24 * MHZ, 106031250,  53, 3, 2,  1024),
	PLL_36XX_RATE(24 * MHZ,  53015625,  53, 3, 3,  1024),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा samsung_pll_घड़ी exynos4210_plls[nr_plls] __initdata = अणु
	[apll] = PLL(pll_4508, CLK_FOUT_APLL, "fout_apll", "fin_pll",
		APLL_LOCK, APLL_CON0, शून्य),
	[mpll] = PLL(pll_4508, CLK_FOUT_MPLL, "fout_mpll", "fin_pll",
		E4210_MPLL_LOCK, E4210_MPLL_CON0, शून्य),
	[epll] = PLL(pll_4600, CLK_FOUT_EPLL, "fout_epll", "fin_pll",
		EPLL_LOCK, EPLL_CON0, शून्य),
	[vpll] = PLL(pll_4650c, CLK_FOUT_VPLL, "fout_vpll", "mout_vpllsrc",
		VPLL_LOCK, VPLL_CON0, शून्य),
पूर्ण;

अटल काष्ठा samsung_pll_घड़ी exynos4x12_plls[nr_plls] __initdata = अणु
	[apll] = PLL(pll_35xx, CLK_FOUT_APLL, "fout_apll", "fin_pll",
			APLL_LOCK, APLL_CON0, शून्य),
	[mpll] = PLL(pll_35xx, CLK_FOUT_MPLL, "fout_mpll", "fin_pll",
			E4X12_MPLL_LOCK, E4X12_MPLL_CON0, शून्य),
	[epll] = PLL(pll_36xx, CLK_FOUT_EPLL, "fout_epll", "fin_pll",
			EPLL_LOCK, EPLL_CON0, शून्य),
	[vpll] = PLL(pll_36xx, CLK_FOUT_VPLL, "fout_vpll", "fin_pll",
			VPLL_LOCK, VPLL_CON0, शून्य),
पूर्ण;

अटल व्योम __init exynos4x12_core_करोwn_घड़ी(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/*
	 * Enable arm घड़ी करोwn (in idle) and set arm भागider
	 * ratios in WFI/WFE state.
	 */
	पंचांगp = (PWR_CTRL1_CORE2_DOWN_RATIO(7) | PWR_CTRL1_CORE1_DOWN_RATIO(7) |
		PWR_CTRL1_DIV2_DOWN_EN | PWR_CTRL1_DIV1_DOWN_EN |
		PWR_CTRL1_USE_CORE1_WFE | PWR_CTRL1_USE_CORE0_WFE |
		PWR_CTRL1_USE_CORE1_WFI | PWR_CTRL1_USE_CORE0_WFI);
	/* On Exynos4412 enable it also on core 2 and 3 */
	अगर (num_possible_cpus() == 4)
		पंचांगp |= PWR_CTRL1_USE_CORE3_WFE | PWR_CTRL1_USE_CORE2_WFE |
		       PWR_CTRL1_USE_CORE3_WFI | PWR_CTRL1_USE_CORE2_WFI;
	ग_लिखोl_relaxed(पंचांगp, reg_base + PWR_CTRL1);

	/*
	 * Disable the घड़ी up feature in हाल it was enabled by bootloader.
	 */
	ग_लिखोl_relaxed(0x0, reg_base + E4X12_PWR_CTRL2);
पूर्ण

#घोषणा E4210_CPU_DIV0(apll, pclk_dbg, atb, periph, corem1, corem0)	\
		(((apll) << 24) | ((pclk_dbg) << 20) | ((atb) << 16) |	\
		((periph) << 12) | ((corem1) << 8) | ((corem0) <<  4))
#घोषणा E4210_CPU_DIV1(hpm, copy)					\
		(((hpm) << 4) | ((copy) << 0))

अटल स्थिर काष्ठा exynos_cpuclk_cfg_data e4210_armclk_d[] __initस्थिर = अणु
	अणु 1200000, E4210_CPU_DIV0(7, 1, 4, 3, 7, 3), E4210_CPU_DIV1(0, 5), पूर्ण,
	अणु 1000000, E4210_CPU_DIV0(7, 1, 4, 3, 7, 3), E4210_CPU_DIV1(0, 4), पूर्ण,
	अणु  800000, E4210_CPU_DIV0(7, 1, 3, 3, 7, 3), E4210_CPU_DIV1(0, 3), पूर्ण,
	अणु  500000, E4210_CPU_DIV0(7, 1, 3, 3, 7, 3), E4210_CPU_DIV1(0, 3), पूर्ण,
	अणु  400000, E4210_CPU_DIV0(7, 1, 3, 3, 7, 3), E4210_CPU_DIV1(0, 3), पूर्ण,
	अणु  200000, E4210_CPU_DIV0(0, 1, 1, 1, 3, 1), E4210_CPU_DIV1(0, 3), पूर्ण,
	अणु  0 पूर्ण,
पूर्ण;

#घोषणा E4412_CPU_DIV1(cores, hpm, copy)				\
		(((cores) << 8) | ((hpm) << 4) | ((copy) << 0))

अटल स्थिर काष्ठा exynos_cpuclk_cfg_data e4412_armclk_d[] __initस्थिर = अणु
	अणु 1704000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(7, 0, 7), पूर्ण,
	अणु 1600000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(7, 0, 6), पूर्ण,
	अणु 1500000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(7, 0, 6), पूर्ण,
	अणु 1400000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(6, 0, 6), पूर्ण,
	अणु 1300000, E4210_CPU_DIV0(2, 1, 5, 0, 7, 3), E4412_CPU_DIV1(6, 0, 5), पूर्ण,
	अणु 1200000, E4210_CPU_DIV0(2, 1, 5, 0, 7, 3), E4412_CPU_DIV1(5, 0, 5), पूर्ण,
	अणु 1100000, E4210_CPU_DIV0(2, 1, 4, 0, 6, 3), E4412_CPU_DIV1(5, 0, 4), पूर्ण,
	अणु 1000000, E4210_CPU_DIV0(1, 1, 4, 0, 5, 2), E4412_CPU_DIV1(4, 0, 4), पूर्ण,
	अणु  900000, E4210_CPU_DIV0(1, 1, 3, 0, 5, 2), E4412_CPU_DIV1(4, 0, 3), पूर्ण,
	अणु  800000, E4210_CPU_DIV0(1, 1, 3, 0, 5, 2), E4412_CPU_DIV1(3, 0, 3), पूर्ण,
	अणु  700000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(3, 0, 3), पूर्ण,
	अणु  600000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(2, 0, 3), पूर्ण,
	अणु  500000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(2, 0, 3), पूर्ण,
	अणु  400000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(1, 0, 3), पूर्ण,
	अणु  300000, E4210_CPU_DIV0(1, 1, 2, 0, 4, 2), E4412_CPU_DIV1(1, 0, 3), पूर्ण,
	अणु  200000, E4210_CPU_DIV0(1, 1, 1, 0, 3, 1), E4412_CPU_DIV1(0, 0, 3), पूर्ण,
	अणु  0 पूर्ण,
पूर्ण;

/* रेजिस्टर exynos4 घड़ीs */
अटल व्योम __init exynos4_clk_init(काष्ठा device_node *np,
				    क्रमागत exynos4_soc soc)
अणु
	काष्ठा samsung_clk_provider *ctx;
	काष्ठा clk_hw **hws;

	exynos4_soc = soc;

	reg_base = of_iomap(np, 0);
	अगर (!reg_base)
		panic("%s: failed to map registers\n", __func__);

	ctx = samsung_clk_init(np, reg_base, CLK_NR_CLKS);
	hws = ctx->clk_data.hws;

	samsung_clk_of_रेजिस्टर_fixed_ext(ctx, exynos4_fixed_rate_ext_clks,
			ARRAY_SIZE(exynos4_fixed_rate_ext_clks),
			ext_clk_match);

	exynos4_clk_रेजिस्टर_finpll(ctx);

	अगर (exynos4_soc == EXYNOS4210) अणु
		samsung_clk_रेजिस्टर_mux(ctx, exynos4210_mux_early,
					ARRAY_SIZE(exynos4210_mux_early));

		अगर (_get_rate("fin_pll") == 24000000) अणु
			exynos4210_plls[apll].rate_table =
							exynos4210_apll_rates;
			exynos4210_plls[epll].rate_table =
							exynos4210_epll_rates;
		पूर्ण

		अगर (_get_rate("mout_vpllsrc") == 24000000)
			exynos4210_plls[vpll].rate_table =
							exynos4210_vpll_rates;

		samsung_clk_रेजिस्टर_pll(ctx, exynos4210_plls,
					ARRAY_SIZE(exynos4210_plls), reg_base);
	पूर्ण अन्यथा अणु
		अगर (_get_rate("fin_pll") == 24000000) अणु
			exynos4x12_plls[apll].rate_table =
							exynos4x12_apll_rates;
			exynos4x12_plls[epll].rate_table =
							exynos4x12_epll_rates;
			exynos4x12_plls[vpll].rate_table =
							exynos4x12_vpll_rates;
		पूर्ण

		samsung_clk_रेजिस्टर_pll(ctx, exynos4x12_plls,
					ARRAY_SIZE(exynos4x12_plls), reg_base);
	पूर्ण

	samsung_clk_रेजिस्टर_fixed_rate(ctx, exynos4_fixed_rate_clks,
			ARRAY_SIZE(exynos4_fixed_rate_clks));
	samsung_clk_रेजिस्टर_mux(ctx, exynos4_mux_clks,
			ARRAY_SIZE(exynos4_mux_clks));
	samsung_clk_रेजिस्टर_भाग(ctx, exynos4_भाग_clks,
			ARRAY_SIZE(exynos4_भाग_clks));
	samsung_clk_रेजिस्टर_gate(ctx, exynos4_gate_clks,
			ARRAY_SIZE(exynos4_gate_clks));
	samsung_clk_रेजिस्टर_fixed_factor(ctx, exynos4_fixed_factor_clks,
			ARRAY_SIZE(exynos4_fixed_factor_clks));

	अगर (exynos4_soc == EXYNOS4210) अणु
		samsung_clk_रेजिस्टर_fixed_rate(ctx, exynos4210_fixed_rate_clks,
			ARRAY_SIZE(exynos4210_fixed_rate_clks));
		samsung_clk_रेजिस्टर_mux(ctx, exynos4210_mux_clks,
			ARRAY_SIZE(exynos4210_mux_clks));
		samsung_clk_रेजिस्टर_भाग(ctx, exynos4210_भाग_clks,
			ARRAY_SIZE(exynos4210_भाग_clks));
		samsung_clk_रेजिस्टर_gate(ctx, exynos4210_gate_clks,
			ARRAY_SIZE(exynos4210_gate_clks));
		samsung_clk_रेजिस्टर_fixed_factor(ctx,
			exynos4210_fixed_factor_clks,
			ARRAY_SIZE(exynos4210_fixed_factor_clks));
		exynos_रेजिस्टर_cpu_घड़ी(ctx, CLK_ARM_CLK, "armclk",
			hws[CLK_MOUT_APLL], hws[CLK_SCLK_MPLL], 0x14200,
			e4210_armclk_d, ARRAY_SIZE(e4210_armclk_d),
			CLK_CPU_NEEDS_DEBUG_ALT_DIV | CLK_CPU_HAS_DIV1);
	पूर्ण अन्यथा अणु
		samsung_clk_रेजिस्टर_mux(ctx, exynos4x12_mux_clks,
			ARRAY_SIZE(exynos4x12_mux_clks));
		samsung_clk_रेजिस्टर_भाग(ctx, exynos4x12_भाग_clks,
			ARRAY_SIZE(exynos4x12_भाग_clks));
		samsung_clk_रेजिस्टर_gate(ctx, exynos4x12_gate_clks,
			ARRAY_SIZE(exynos4x12_gate_clks));
		samsung_clk_रेजिस्टर_fixed_factor(ctx,
			exynos4x12_fixed_factor_clks,
			ARRAY_SIZE(exynos4x12_fixed_factor_clks));

		exynos_रेजिस्टर_cpu_घड़ी(ctx, CLK_ARM_CLK, "armclk",
			hws[CLK_MOUT_APLL], hws[CLK_MOUT_MPLL_USER_C], 0x14200,
			e4412_armclk_d, ARRAY_SIZE(e4412_armclk_d),
			CLK_CPU_NEEDS_DEBUG_ALT_DIV | CLK_CPU_HAS_DIV1);
	पूर्ण

	अगर (soc == EXYNOS4X12)
		exynos4x12_core_करोwn_घड़ी();

	samsung_clk_extended_sleep_init(reg_base,
			exynos4_clk_regs, ARRAY_SIZE(exynos4_clk_regs),
			src_mask_suspend, ARRAY_SIZE(src_mask_suspend));
	अगर (exynos4_soc == EXYNOS4210)
		samsung_clk_extended_sleep_init(reg_base,
		    exynos4210_clk_save, ARRAY_SIZE(exynos4210_clk_save),
		    src_mask_suspend_e4210, ARRAY_SIZE(src_mask_suspend_e4210));
	अन्यथा
		samsung_clk_sleep_init(reg_base, exynos4x12_clk_save,
				       ARRAY_SIZE(exynos4x12_clk_save));

	samsung_clk_of_add_provider(np, ctx);

	pr_info("%s clocks: sclk_apll = %ld, sclk_mpll = %ld\n"
		"\tsclk_epll = %ld, sclk_vpll = %ld, arm_clk = %ld\n",
		exynos4_soc == EXYNOS4210 ? "Exynos4210" : "Exynos4x12",
		_get_rate("sclk_apll"),	_get_rate("sclk_mpll"),
		_get_rate("sclk_epll"), _get_rate("sclk_vpll"),
		_get_rate("div_core2"));
पूर्ण


अटल व्योम __init exynos4210_clk_init(काष्ठा device_node *np)
अणु
	exynos4_clk_init(np, EXYNOS4210);
पूर्ण
CLK_OF_DECLARE(exynos4210_clk, "samsung,exynos4210-clock", exynos4210_clk_init);

अटल व्योम __init exynos4412_clk_init(काष्ठा device_node *np)
अणु
	exynos4_clk_init(np, EXYNOS4X12);
पूर्ण
CLK_OF_DECLARE(exynos4412_clk, "samsung,exynos4412-clock", exynos4412_clk_init);
