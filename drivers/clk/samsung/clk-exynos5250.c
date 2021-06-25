<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 *
 * Common Clock Framework support क्रम Exynos5250 SoC.
*/

#समावेश <dt-bindings/घड़ी/exynos5250.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "clk.h"
#समावेश "clk-cpu.h"
#समावेश "clk-exynos5-subcmu.h"

#घोषणा APLL_LOCK		0x0
#घोषणा APLL_CON0		0x100
#घोषणा SRC_CPU			0x200
#घोषणा DIV_CPU0		0x500
#घोषणा PWR_CTRL1		0x1020
#घोषणा PWR_CTRL2		0x1024
#घोषणा MPLL_LOCK		0x4000
#घोषणा MPLL_CON0		0x4100
#घोषणा SRC_CORE1		0x4204
#घोषणा GATE_IP_ACP		0x8800
#घोषणा GATE_IP_ISP0		0xc800
#घोषणा GATE_IP_ISP1		0xc804
#घोषणा CPLL_LOCK		0x10020
#घोषणा EPLL_LOCK		0x10030
#घोषणा VPLL_LOCK		0x10040
#घोषणा GPLL_LOCK		0x10050
#घोषणा CPLL_CON0		0x10120
#घोषणा EPLL_CON0		0x10130
#घोषणा VPLL_CON0		0x10140
#घोषणा GPLL_CON0		0x10150
#घोषणा SRC_TOP0		0x10210
#घोषणा SRC_TOP1		0x10214
#घोषणा SRC_TOP2		0x10218
#घोषणा SRC_TOP3		0x1021c
#घोषणा SRC_GSCL		0x10220
#घोषणा SRC_DISP1_0		0x1022c
#घोषणा SRC_MAU			0x10240
#घोषणा SRC_FSYS		0x10244
#घोषणा SRC_GEN			0x10248
#घोषणा SRC_PERIC0		0x10250
#घोषणा SRC_PERIC1		0x10254
#घोषणा SRC_MASK_GSCL		0x10320
#घोषणा SRC_MASK_DISP1_0	0x1032c
#घोषणा SRC_MASK_MAU		0x10334
#घोषणा SRC_MASK_FSYS		0x10340
#घोषणा SRC_MASK_GEN		0x10344
#घोषणा SRC_MASK_PERIC0		0x10350
#घोषणा SRC_MASK_PERIC1		0x10354
#घोषणा DIV_TOP0		0x10510
#घोषणा DIV_TOP1		0x10514
#घोषणा DIV_GSCL		0x10520
#घोषणा DIV_DISP1_0		0x1052c
#घोषणा DIV_GEN			0x1053c
#घोषणा DIV_MAU			0x10544
#घोषणा DIV_FSYS0		0x10548
#घोषणा DIV_FSYS1		0x1054c
#घोषणा DIV_FSYS2		0x10550
#घोषणा DIV_PERIC0		0x10558
#घोषणा DIV_PERIC1		0x1055c
#घोषणा DIV_PERIC2		0x10560
#घोषणा DIV_PERIC3		0x10564
#घोषणा DIV_PERIC4		0x10568
#घोषणा DIV_PERIC5		0x1056c
#घोषणा GATE_IP_GSCL		0x10920
#घोषणा GATE_IP_DISP1		0x10928
#घोषणा GATE_IP_MFC		0x1092c
#घोषणा GATE_IP_G3D		0x10930
#घोषणा GATE_IP_GEN		0x10934
#घोषणा GATE_IP_FSYS		0x10944
#घोषणा GATE_IP_PERIC		0x10950
#घोषणा GATE_IP_PERIS		0x10960
#घोषणा BPLL_LOCK		0x20010
#घोषणा BPLL_CON0		0x20110
#घोषणा SRC_CDREX		0x20200
#घोषणा PLL_DIV2_SEL		0x20a24

/*Below definitions are used क्रम PWR_CTRL settings*/
#घोषणा PWR_CTRL1_CORE2_DOWN_RATIO		(7 << 28)
#घोषणा PWR_CTRL1_CORE1_DOWN_RATIO		(7 << 16)
#घोषणा PWR_CTRL1_DIV2_DOWN_EN			(1 << 9)
#घोषणा PWR_CTRL1_DIV1_DOWN_EN			(1 << 8)
#घोषणा PWR_CTRL1_USE_CORE1_WFE			(1 << 5)
#घोषणा PWR_CTRL1_USE_CORE0_WFE			(1 << 4)
#घोषणा PWR_CTRL1_USE_CORE1_WFI			(1 << 1)
#घोषणा PWR_CTRL1_USE_CORE0_WFI			(1 << 0)

#घोषणा PWR_CTRL2_DIV2_UP_EN			(1 << 25)
#घोषणा PWR_CTRL2_DIV1_UP_EN			(1 << 24)
#घोषणा PWR_CTRL2_DUR_STANDBY2_VAL		(1 << 16)
#घोषणा PWR_CTRL2_DUR_STANDBY1_VAL		(1 << 8)
#घोषणा PWR_CTRL2_CORE2_UP_RATIO		(1 << 4)
#घोषणा PWR_CTRL2_CORE1_UP_RATIO		(1 << 0)

/* list of PLLs to be रेजिस्टरed */
क्रमागत exynos5250_plls अणु
	apll, mpll, cpll, epll, vpll, gpll, bpll,
	nr_plls			/* number of PLLs */
पूर्ण;

अटल व्योम __iomem *reg_base;

/*
 * list of controller रेजिस्टरs to be saved and restored during a
 * suspend/resume cycle.
 */
अटल स्थिर अचिन्हित दीर्घ exynos5250_clk_regs[] __initस्थिर = अणु
	SRC_CPU,
	DIV_CPU0,
	PWR_CTRL1,
	PWR_CTRL2,
	SRC_CORE1,
	SRC_TOP0,
	SRC_TOP1,
	SRC_TOP2,
	SRC_TOP3,
	SRC_GSCL,
	SRC_DISP1_0,
	SRC_MAU,
	SRC_FSYS,
	SRC_GEN,
	SRC_PERIC0,
	SRC_PERIC1,
	SRC_MASK_GSCL,
	SRC_MASK_DISP1_0,
	SRC_MASK_MAU,
	SRC_MASK_FSYS,
	SRC_MASK_GEN,
	SRC_MASK_PERIC0,
	SRC_MASK_PERIC1,
	DIV_TOP0,
	DIV_TOP1,
	DIV_GSCL,
	DIV_DISP1_0,
	DIV_GEN,
	DIV_MAU,
	DIV_FSYS0,
	DIV_FSYS1,
	DIV_FSYS2,
	DIV_PERIC0,
	DIV_PERIC1,
	DIV_PERIC2,
	DIV_PERIC3,
	DIV_PERIC4,
	DIV_PERIC5,
	GATE_IP_GSCL,
	GATE_IP_MFC,
	GATE_IP_G3D,
	GATE_IP_GEN,
	GATE_IP_FSYS,
	GATE_IP_PERIC,
	GATE_IP_PERIS,
	SRC_CDREX,
	PLL_DIV2_SEL,
	GATE_IP_DISP1,
	GATE_IP_ACP,
	GATE_IP_ISP0,
	GATE_IP_ISP1,
पूर्ण;

/* list of all parent घड़ी list */
PNAME(mout_apll_p)	= अणु "fin_pll", "fout_apll", पूर्ण;
PNAME(mout_cpu_p)	= अणु "mout_apll", "mout_mpll", पूर्ण;
PNAME(mout_mpll_fout_p)	= अणु "fout_mplldiv2", "fout_mpll" पूर्ण;
PNAME(mout_mpll_p)	= अणु "fin_pll", "mout_mpll_fout" पूर्ण;
PNAME(mout_bpll_fout_p)	= अणु "fout_bplldiv2", "fout_bpll" पूर्ण;
PNAME(mout_bpll_p)	= अणु "fin_pll", "mout_bpll_fout" पूर्ण;
PNAME(mout_vpllsrc_p)	= अणु "fin_pll", "sclk_hdmi27m" पूर्ण;
PNAME(mout_vpll_p)	= अणु "mout_vpllsrc", "fout_vpll" पूर्ण;
PNAME(mout_cpll_p)	= अणु "fin_pll", "fout_cpll" पूर्ण;
PNAME(mout_epll_p)	= अणु "fin_pll", "fout_epll" पूर्ण;
PNAME(mout_gpll_p)	= अणु "fin_pll", "fout_gpll" पूर्ण;
PNAME(mout_mpll_user_p)	= अणु "fin_pll", "mout_mpll" पूर्ण;
PNAME(mout_bpll_user_p)	= अणु "fin_pll", "mout_bpll" पूर्ण;
PNAME(mout_aclk166_p)	= अणु "mout_cpll", "mout_mpll_user" पूर्ण;
PNAME(mout_aclk200_p)	= अणु "mout_mpll_user", "mout_bpll_user" पूर्ण;
PNAME(mout_aclk300_p)	= अणु "mout_aclk300_disp1_mid",
			    "mout_aclk300_disp1_mid1" पूर्ण;
PNAME(mout_aclk400_p)	= अणु "mout_aclk400_g3d_mid", "mout_gpll" पूर्ण;
PNAME(mout_aclk200_sub_p) = अणु "fin_pll", "div_aclk200" पूर्ण;
PNAME(mout_aclk266_sub_p) = अणु "fin_pll", "div_aclk266" पूर्ण;
PNAME(mout_aclk300_sub_p) = अणु "fin_pll", "div_aclk300_disp" पूर्ण;
PNAME(mout_aclk300_disp1_mid1_p) = अणु "mout_vpll", "mout_cpll" पूर्ण;
PNAME(mout_aclk333_sub_p) = अणु "fin_pll", "div_aclk333" पूर्ण;
PNAME(mout_aclk400_isp_sub_p) = अणु "fin_pll", "div_aclk400_isp" पूर्ण;
PNAME(mout_hdmi_p)	= अणु "div_hdmi_pixel", "sclk_hdmiphy" पूर्ण;
PNAME(mout_usb3_p)	= अणु "mout_mpll_user", "mout_cpll" पूर्ण;
PNAME(mout_group1_p)	= अणु "fin_pll", "fin_pll", "sclk_hdmi27m",
				"sclk_dptxphy", "sclk_uhostphy", "sclk_hdmiphy",
				"mout_mpll_user", "mout_epll", "mout_vpll",
				"mout_cpll", "none", "none",
				"none", "none", "none",
				"none" पूर्ण;
PNAME(mout_audio0_p)	= अणु "cdclk0", "fin_pll", "sclk_hdmi27m", "sclk_dptxphy",
				"sclk_uhostphy", "fin_pll",
				"mout_mpll_user", "mout_epll", "mout_vpll",
				"mout_cpll", "none", "none",
				"none", "none", "none",
				"none" पूर्ण;
PNAME(mout_audio1_p)	= अणु "cdclk1", "fin_pll", "sclk_hdmi27m", "sclk_dptxphy",
				"sclk_uhostphy", "fin_pll",
				"mout_mpll_user", "mout_epll", "mout_vpll",
				"mout_cpll", "none", "none",
				"none", "none", "none",
				"none" पूर्ण;
PNAME(mout_audio2_p)	= अणु "cdclk2", "fin_pll", "sclk_hdmi27m", "sclk_dptxphy",
				"sclk_uhostphy", "fin_pll",
				"mout_mpll_user", "mout_epll", "mout_vpll",
				"mout_cpll", "none", "none",
				"none", "none", "none",
				"none" पूर्ण;
PNAME(mout_spdअगर_p)	= अणु "sclk_audio0", "sclk_audio1", "sclk_audio2",
				"spdif_extclk" पूर्ण;

/* fixed rate घड़ीs generated outside the soc */
अटल काष्ठा samsung_fixed_rate_घड़ी exynos5250_fixed_rate_ext_clks[] __initdata = अणु
	FRATE(CLK_FIN_PLL, "fin_pll", शून्य, 0, 0),
पूर्ण;

/* fixed rate घड़ीs generated inside the soc */
अटल स्थिर काष्ठा samsung_fixed_rate_घड़ी exynos5250_fixed_rate_clks[] __initस्थिर = अणु
	FRATE(CLK_SCLK_HDMIPHY, "sclk_hdmiphy", शून्य, 0, 24000000),
	FRATE(0, "sclk_hdmi27m", शून्य, 0, 27000000),
	FRATE(0, "sclk_dptxphy", शून्य, 0, 24000000),
	FRATE(0, "sclk_uhostphy", शून्य, 0, 48000000),
पूर्ण;

अटल स्थिर काष्ठा samsung_fixed_factor_घड़ी exynos5250_fixed_factor_clks[] __initस्थिर = अणु
	FFACTOR(0, "fout_mplldiv2", "fout_mpll", 1, 2, 0),
	FFACTOR(0, "fout_bplldiv2", "fout_bpll", 1, 2, 0),
पूर्ण;

अटल स्थिर काष्ठा samsung_mux_घड़ी exynos5250_pll_pmux_clks[] __initस्थिर = अणु
	MUX(0, "mout_vpllsrc", mout_vpllsrc_p, SRC_TOP2, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा samsung_mux_घड़ी exynos5250_mux_clks[] __initस्थिर = अणु
	/*
	 * NOTE: Following table is sorted by (घड़ी करोमुख्य, रेजिस्टर address,
	 * bitfield shअगरt) triplet in ascending order. When adding new entries,
	 * please make sure that the order is kept, to aव्योम merge conflicts
	 * and make further work with defined data easier.
	 */

	/*
	 * CMU_CPU
	 */
	MUX_F(CLK_MOUT_APLL, "mout_apll", mout_apll_p, SRC_CPU, 0, 1,
					CLK_SET_RATE_PARENT, 0),
	MUX(0, "mout_cpu", mout_cpu_p, SRC_CPU, 16, 1),

	/*
	 * CMU_CORE
	 */
	MUX(CLK_MOUT_MPLL, "mout_mpll", mout_mpll_p, SRC_CORE1, 8, 1),

	/*
	 * CMU_TOP
	 */
	MUX(0, "mout_aclk166", mout_aclk166_p, SRC_TOP0, 8, 1),
	MUX(0, "mout_aclk200", mout_aclk200_p, SRC_TOP0, 12, 1),
	MUX(0, "mout_aclk300_disp1_mid", mout_aclk200_p, SRC_TOP0, 14, 1),
	MUX(0, "mout_aclk300", mout_aclk300_p, SRC_TOP0, 15, 1),
	MUX(0, "mout_aclk333", mout_aclk166_p, SRC_TOP0, 16, 1),
	MUX(0, "mout_aclk400_g3d_mid", mout_aclk200_p, SRC_TOP0, 20, 1),

	MUX(0, "mout_aclk300_disp1_mid1", mout_aclk300_disp1_mid1_p, SRC_TOP1,
		8, 1),
	MUX(0, "mout_aclk400_isp", mout_aclk200_p, SRC_TOP1, 24, 1),
	MUX(0, "mout_aclk400_g3d", mout_aclk400_p, SRC_TOP1, 28, 1),

	MUX(0, "mout_cpll", mout_cpll_p, SRC_TOP2, 8, 1),
	MUX(0, "mout_epll", mout_epll_p, SRC_TOP2, 12, 1),
	MUX(0, "mout_vpll", mout_vpll_p, SRC_TOP2, 16, 1),
	MUX(0, "mout_mpll_user", mout_mpll_user_p, SRC_TOP2, 20, 1),
	MUX(0, "mout_bpll_user", mout_bpll_user_p, SRC_TOP2, 24, 1),
	MUX(CLK_MOUT_GPLL, "mout_gpll", mout_gpll_p, SRC_TOP2, 28, 1),

	MUX(CLK_MOUT_ACLK200_DISP1_SUB, "mout_aclk200_disp1_sub",
		mout_aclk200_sub_p, SRC_TOP3, 4, 1),
	MUX(CLK_MOUT_ACLK300_DISP1_SUB, "mout_aclk300_disp1_sub",
		mout_aclk300_sub_p, SRC_TOP3, 6, 1),
	MUX(0, "mout_aclk266_gscl_sub", mout_aclk266_sub_p, SRC_TOP3, 8, 1),
	MUX(0, "mout_aclk_266_isp_sub", mout_aclk266_sub_p, SRC_TOP3, 16, 1),
	MUX(0, "mout_aclk_400_isp_sub", mout_aclk400_isp_sub_p,
			SRC_TOP3, 20, 1),
	MUX(0, "mout_aclk333_sub", mout_aclk333_sub_p, SRC_TOP3, 24, 1),

	MUX(0, "mout_cam_bayer", mout_group1_p, SRC_GSCL, 12, 4),
	MUX(0, "mout_cam0", mout_group1_p, SRC_GSCL, 16, 4),
	MUX(0, "mout_cam1", mout_group1_p, SRC_GSCL, 20, 4),
	MUX(0, "mout_gscl_wa", mout_group1_p, SRC_GSCL, 24, 4),
	MUX(0, "mout_gscl_wb", mout_group1_p, SRC_GSCL, 28, 4),

	MUX(0, "mout_fimd1", mout_group1_p, SRC_DISP1_0, 0, 4),
	MUX(0, "mout_mipi1", mout_group1_p, SRC_DISP1_0, 12, 4),
	MUX(0, "mout_dp", mout_group1_p, SRC_DISP1_0, 16, 4),
	MUX(CLK_MOUT_HDMI, "mout_hdmi", mout_hdmi_p, SRC_DISP1_0, 20, 1),

	MUX(0, "mout_audio0", mout_audio0_p, SRC_MAU, 0, 4),

	MUX(0, "mout_mmc0", mout_group1_p, SRC_FSYS, 0, 4),
	MUX(0, "mout_mmc1", mout_group1_p, SRC_FSYS, 4, 4),
	MUX(0, "mout_mmc2", mout_group1_p, SRC_FSYS, 8, 4),
	MUX(0, "mout_mmc3", mout_group1_p, SRC_FSYS, 12, 4),
	MUX(0, "mout_sata", mout_aclk200_p, SRC_FSYS, 24, 1),
	MUX(0, "mout_usb3", mout_usb3_p, SRC_FSYS, 28, 1),

	MUX(0, "mout_jpeg", mout_group1_p, SRC_GEN, 0, 4),

	MUX(0, "mout_uart0", mout_group1_p, SRC_PERIC0, 0, 4),
	MUX(0, "mout_uart1", mout_group1_p, SRC_PERIC0, 4, 4),
	MUX(0, "mout_uart2", mout_group1_p, SRC_PERIC0, 8, 4),
	MUX(0, "mout_uart3", mout_group1_p, SRC_PERIC0, 12, 4),
	MUX(0, "mout_pwm", mout_group1_p, SRC_PERIC0, 24, 4),

	MUX(0, "mout_audio1", mout_audio1_p, SRC_PERIC1, 0, 4),
	MUX(0, "mout_audio2", mout_audio2_p, SRC_PERIC1, 4, 4),
	MUX(0, "mout_spdif", mout_spdअगर_p, SRC_PERIC1, 8, 2),
	MUX(0, "mout_spi0", mout_group1_p, SRC_PERIC1, 16, 4),
	MUX(0, "mout_spi1", mout_group1_p, SRC_PERIC1, 20, 4),
	MUX(0, "mout_spi2", mout_group1_p, SRC_PERIC1, 24, 4),

	/*
	 * CMU_CDREX
	 */
	MUX(0, "mout_bpll", mout_bpll_p, SRC_CDREX, 0, 1),

	MUX(0, "mout_mpll_fout", mout_mpll_fout_p, PLL_DIV2_SEL, 4, 1),
	MUX(0, "mout_bpll_fout", mout_bpll_fout_p, PLL_DIV2_SEL, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा samsung_भाग_घड़ी exynos5250_भाग_clks[] __initस्थिर = अणु
	/*
	 * NOTE: Following table is sorted by (घड़ी करोमुख्य, रेजिस्टर address,
	 * bitfield shअगरt) triplet in ascending order. When adding new entries,
	 * please make sure that the order is kept, to aव्योम merge conflicts
	 * and make further work with defined data easier.
	 */

	/*
	 * CMU_CPU
	 */
	DIV(0, "div_arm", "mout_cpu", DIV_CPU0, 0, 3),
	DIV(0, "div_apll", "mout_apll", DIV_CPU0, 24, 3),
	DIV(0, "div_arm2", "div_arm", DIV_CPU0, 28, 3),

	/*
	 * CMU_TOP
	 */
	DIV(0, "div_aclk66", "div_aclk66_pre", DIV_TOP0, 0, 3),
	DIV(0, "div_aclk166", "mout_aclk166", DIV_TOP0, 8, 3),
	DIV(0, "div_aclk200", "mout_aclk200", DIV_TOP0, 12, 3),
	DIV(0, "div_aclk266", "mout_mpll_user", DIV_TOP0, 16, 3),
	DIV(0, "div_aclk333", "mout_aclk333", DIV_TOP0, 20, 3),
	DIV(0, "div_aclk400_g3d", "mout_aclk400_g3d", DIV_TOP0,
							24, 3),
	DIV(0, "div_aclk300_disp", "mout_aclk300", DIV_TOP0, 28, 3),

	DIV(0, "div_aclk400_isp", "mout_aclk400_isp", DIV_TOP1, 20, 3),
	DIV(0, "div_aclk66_pre", "mout_mpll_user", DIV_TOP1, 24, 3),

	DIV(0, "div_cam_bayer", "mout_cam_bayer", DIV_GSCL, 12, 4),
	DIV(0, "div_cam0", "mout_cam0", DIV_GSCL, 16, 4),
	DIV(0, "div_cam1", "mout_cam1", DIV_GSCL, 20, 4),
	DIV(0, "div_gscl_wa", "mout_gscl_wa", DIV_GSCL, 24, 4),
	DIV(0, "div_gscl_wb", "mout_gscl_wb", DIV_GSCL, 28, 4),

	DIV(0, "div_fimd1", "mout_fimd1", DIV_DISP1_0, 0, 4),
	DIV(0, "div_mipi1", "mout_mipi1", DIV_DISP1_0, 16, 4),
	DIV_F(0, "div_mipi1_pre", "div_mipi1",
			DIV_DISP1_0, 20, 4, CLK_SET_RATE_PARENT, 0),
	DIV(0, "div_dp", "mout_dp", DIV_DISP1_0, 24, 4),
	DIV(CLK_SCLK_PIXEL, "div_hdmi_pixel", "mout_vpll", DIV_DISP1_0, 28, 4),

	DIV(0, "div_jpeg", "mout_jpeg", DIV_GEN, 4, 4),

	DIV(0, "div_audio0", "mout_audio0", DIV_MAU, 0, 4),
	DIV(CLK_DIV_PCM0, "div_pcm0", "sclk_audio0", DIV_MAU, 4, 8),

	DIV(0, "div_sata", "mout_sata", DIV_FSYS0, 20, 4),
	DIV(0, "div_usb3", "mout_usb3", DIV_FSYS0, 24, 4),

	DIV(0, "div_mmc0", "mout_mmc0", DIV_FSYS1, 0, 4),
	DIV_F(0, "div_mmc_pre0", "div_mmc0",
			DIV_FSYS1, 8, 8, CLK_SET_RATE_PARENT, 0),
	DIV(0, "div_mmc1", "mout_mmc1", DIV_FSYS1, 16, 4),
	DIV_F(0, "div_mmc_pre1", "div_mmc1",
			DIV_FSYS1, 24, 8, CLK_SET_RATE_PARENT, 0),

	DIV(0, "div_mmc2", "mout_mmc2", DIV_FSYS2, 0, 4),
	DIV_F(0, "div_mmc_pre2", "div_mmc2",
			DIV_FSYS2, 8, 8, CLK_SET_RATE_PARENT, 0),
	DIV(0, "div_mmc3", "mout_mmc3", DIV_FSYS2, 16, 4),
	DIV_F(0, "div_mmc_pre3", "div_mmc3",
			DIV_FSYS2, 24, 8, CLK_SET_RATE_PARENT, 0),

	DIV(0, "div_uart0", "mout_uart0", DIV_PERIC0, 0, 4),
	DIV(0, "div_uart1", "mout_uart1", DIV_PERIC0, 4, 4),
	DIV(0, "div_uart2", "mout_uart2", DIV_PERIC0, 8, 4),
	DIV(0, "div_uart3", "mout_uart3", DIV_PERIC0, 12, 4),

	DIV(0, "div_spi0", "mout_spi0", DIV_PERIC1, 0, 4),
	DIV_F(0, "div_spi_pre0", "div_spi0",
			DIV_PERIC1, 8, 8, CLK_SET_RATE_PARENT, 0),
	DIV(0, "div_spi1", "mout_spi1", DIV_PERIC1, 16, 4),
	DIV_F(0, "div_spi_pre1", "div_spi1",
			DIV_PERIC1, 24, 8, CLK_SET_RATE_PARENT, 0),

	DIV(0, "div_spi2", "mout_spi2", DIV_PERIC2, 0, 4),
	DIV_F(0, "div_spi_pre2", "div_spi2",
			DIV_PERIC2, 8, 8, CLK_SET_RATE_PARENT, 0),

	DIV(0, "div_pwm", "mout_pwm", DIV_PERIC3, 0, 4),

	DIV(0, "div_audio1", "mout_audio1", DIV_PERIC4, 0, 4),
	DIV(0, "div_pcm1", "sclk_audio1", DIV_PERIC4, 4, 8),
	DIV(0, "div_audio2", "mout_audio2", DIV_PERIC4, 16, 4),
	DIV(0, "div_pcm2", "sclk_audio2", DIV_PERIC4, 20, 8),

	DIV(CLK_DIV_I2S1, "div_i2s1", "sclk_audio1", DIV_PERIC5, 0, 6),
	DIV(CLK_DIV_I2S2, "div_i2s2", "sclk_audio2", DIV_PERIC5, 8, 6),
पूर्ण;

अटल स्थिर काष्ठा samsung_gate_घड़ी exynos5250_gate_clks[] __initस्थिर = अणु
	/*
	 * NOTE: Following table is sorted by (घड़ी करोमुख्य, रेजिस्टर address,
	 * bitfield shअगरt) triplet in ascending order. When adding new entries,
	 * please make sure that the order is kept, to aव्योम merge conflicts
	 * and make further work with defined data easier.
	 */

	/*
	 * CMU_ACP
	 */
	GATE(CLK_MDMA0, "mdma0", "div_aclk266", GATE_IP_ACP, 1, 0, 0),
	GATE(CLK_SSS, "sss", "div_aclk266", GATE_IP_ACP, 2, 0, 0),
	GATE(CLK_G2D, "g2d", "div_aclk200", GATE_IP_ACP, 3, 0, 0),
	GATE(CLK_SMMU_MDMA0, "smmu_mdma0", "div_aclk266", GATE_IP_ACP, 5, 0, 0),

	/*
	 * CMU_TOP
	 */
	GATE(CLK_SCLK_CAM_BAYER, "sclk_cam_bayer", "div_cam_bayer",
			SRC_MASK_GSCL, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_CAM0, "sclk_cam0", "div_cam0",
			SRC_MASK_GSCL, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_CAM1, "sclk_cam1", "div_cam1",
			SRC_MASK_GSCL, 20, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_GSCL_WA, "sclk_gscl_wa", "div_gscl_wa",
			SRC_MASK_GSCL, 24, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_GSCL_WB, "sclk_gscl_wb", "div_gscl_wb",
			SRC_MASK_GSCL, 28, CLK_SET_RATE_PARENT, 0),

	GATE(CLK_SCLK_FIMD1, "sclk_fimd1", "div_fimd1",
			SRC_MASK_DISP1_0, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MIPI1, "sclk_mipi1", "div_mipi1",
			SRC_MASK_DISP1_0, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_DP, "sclk_dp", "div_dp",
			SRC_MASK_DISP1_0, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_HDMI, "sclk_hdmi", "mout_hdmi",
			SRC_MASK_DISP1_0, 20, 0, 0),

	GATE(CLK_SCLK_AUDIO0, "sclk_audio0", "div_audio0",
			SRC_MASK_MAU, 0, CLK_SET_RATE_PARENT, 0),

	GATE(CLK_SCLK_MMC0, "sclk_mmc0", "div_mmc_pre0",
			SRC_MASK_FSYS, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC1, "sclk_mmc1", "div_mmc_pre1",
			SRC_MASK_FSYS, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC2, "sclk_mmc2", "div_mmc_pre2",
			SRC_MASK_FSYS, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_MMC3, "sclk_mmc3", "div_mmc_pre3",
			SRC_MASK_FSYS, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SATA, "sclk_sata", "div_sata",
			SRC_MASK_FSYS, 24, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_USB3, "sclk_usb3", "div_usb3",
			SRC_MASK_FSYS, 28, CLK_SET_RATE_PARENT, 0),

	GATE(CLK_SCLK_JPEG, "sclk_jpeg", "div_jpeg",
			SRC_MASK_GEN, 0, CLK_SET_RATE_PARENT, 0),

	GATE(CLK_SCLK_UART0, "sclk_uart0", "div_uart0",
			SRC_MASK_PERIC0, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART1, "sclk_uart1", "div_uart1",
			SRC_MASK_PERIC0, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART2, "sclk_uart2", "div_uart2",
			SRC_MASK_PERIC0, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_UART3, "sclk_uart3", "div_uart3",
			SRC_MASK_PERIC0, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_PWM, "sclk_pwm", "div_pwm",
			SRC_MASK_PERIC0, 24, CLK_SET_RATE_PARENT, 0),

	GATE(CLK_SCLK_AUDIO1, "sclk_audio1", "div_audio1",
			SRC_MASK_PERIC1, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_AUDIO2, "sclk_audio2", "div_audio2",
			SRC_MASK_PERIC1, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SPDIF, "sclk_spdif", "mout_spdif",
			SRC_MASK_PERIC1, 4, 0, 0),
	GATE(CLK_SCLK_SPI0, "sclk_spi0", "div_spi_pre0",
			SRC_MASK_PERIC1, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SPI1, "sclk_spi1", "div_spi_pre1",
			SRC_MASK_PERIC1, 20, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_SPI2, "sclk_spi2", "div_spi_pre2",
			SRC_MASK_PERIC1, 24, CLK_SET_RATE_PARENT, 0),

	GATE(CLK_GSCL0, "gscl0", "mout_aclk266_gscl_sub", GATE_IP_GSCL, 0, 0,
		0),
	GATE(CLK_GSCL1, "gscl1", "mout_aclk266_gscl_sub", GATE_IP_GSCL, 1, 0,
		0),
	GATE(CLK_GSCL2, "gscl2", "mout_aclk266_gscl_sub", GATE_IP_GSCL, 2, 0,
		0),
	GATE(CLK_GSCL3, "gscl3", "mout_aclk266_gscl_sub", GATE_IP_GSCL, 3, 0,
		0),
	GATE(CLK_CAMIF_TOP, "camif_top", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 4, 0, 0),
	GATE(CLK_GSCL_WA, "gscl_wa", "div_gscl_wa", GATE_IP_GSCL, 5, 0, 0),
	GATE(CLK_GSCL_WB, "gscl_wb", "div_gscl_wb", GATE_IP_GSCL, 6, 0, 0),
	GATE(CLK_SMMU_GSCL0, "smmu_gscl0", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 7, 0, 0),
	GATE(CLK_SMMU_GSCL1, "smmu_gscl1", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 8, 0, 0),
	GATE(CLK_SMMU_GSCL2, "smmu_gscl2", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 9, 0, 0),
	GATE(CLK_SMMU_GSCL3, "smmu_gscl3", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 10, 0, 0),
	GATE(CLK_SMMU_FIMC_LITE0, "smmu_fimc_lite0", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 11, 0, 0),
	GATE(CLK_SMMU_FIMC_LITE1, "smmu_fimc_lite1", "mout_aclk266_gscl_sub",
			GATE_IP_GSCL, 12, 0, 0),


	GATE(CLK_MFC, "mfc", "mout_aclk333_sub", GATE_IP_MFC, 0, 0, 0),
	GATE(CLK_SMMU_MFCR, "smmu_mfcr", "mout_aclk333_sub", GATE_IP_MFC, 1, 0,
		0),
	GATE(CLK_SMMU_MFCL, "smmu_mfcl", "mout_aclk333_sub", GATE_IP_MFC, 2, 0,
		0),
	GATE(CLK_G3D, "g3d", "div_aclk400_g3d", GATE_IP_G3D, 0,
					CLK_SET_RATE_PARENT, 0),
	GATE(CLK_ROTATOR, "rotator", "div_aclk266", GATE_IP_GEN, 1, 0, 0),
	GATE(CLK_JPEG, "jpeg", "div_aclk166", GATE_IP_GEN, 2, 0, 0),
	GATE(CLK_MDMA1, "mdma1", "div_aclk266", GATE_IP_GEN, 4, 0, 0),
	GATE(CLK_SMMU_ROTATOR, "smmu_rotator", "div_aclk266", GATE_IP_GEN, 6, 0,
		0),
	GATE(CLK_SMMU_JPEG, "smmu_jpeg", "div_aclk166", GATE_IP_GEN, 7, 0, 0),
	GATE(CLK_SMMU_MDMA1, "smmu_mdma1", "div_aclk266", GATE_IP_GEN, 9, 0, 0),

	GATE(CLK_PDMA0, "pdma0", "div_aclk200", GATE_IP_FSYS, 1, 0, 0),
	GATE(CLK_PDMA1, "pdma1", "div_aclk200", GATE_IP_FSYS, 2, 0, 0),
	GATE(CLK_SATA, "sata", "div_aclk200", GATE_IP_FSYS, 6, 0, 0),
	GATE(CLK_USBOTG, "usbotg", "div_aclk200", GATE_IP_FSYS, 7, 0, 0),
	GATE(CLK_MIPI_HSI, "mipi_hsi", "div_aclk200", GATE_IP_FSYS, 8, 0, 0),
	GATE(CLK_SDMMC0, "sdmmc0", "div_aclk200", GATE_IP_FSYS, 12, 0, 0),
	GATE(CLK_SDMMC1, "sdmmc1", "div_aclk200", GATE_IP_FSYS, 13, 0, 0),
	GATE(CLK_SDMMC2, "sdmmc2", "div_aclk200", GATE_IP_FSYS, 14, 0, 0),
	GATE(CLK_SDMMC3, "sdmmc3", "div_aclk200", GATE_IP_FSYS, 15, 0, 0),
	GATE(CLK_SROMC, "sromc", "div_aclk200", GATE_IP_FSYS, 17, 0, 0),
	GATE(CLK_USB2, "usb2", "div_aclk200", GATE_IP_FSYS, 18, 0, 0),
	GATE(CLK_USB3, "usb3", "div_aclk200", GATE_IP_FSYS, 19, 0, 0),
	GATE(CLK_SATA_PHYCTRL, "sata_phyctrl", "div_aclk200",
			GATE_IP_FSYS, 24, 0, 0),
	GATE(CLK_SATA_PHYI2C, "sata_phyi2c", "div_aclk200", GATE_IP_FSYS, 25, 0,
		0),

	GATE(CLK_UART0, "uart0", "div_aclk66", GATE_IP_PERIC, 0, 0, 0),
	GATE(CLK_UART1, "uart1", "div_aclk66", GATE_IP_PERIC, 1, 0, 0),
	GATE(CLK_UART2, "uart2", "div_aclk66", GATE_IP_PERIC, 2, 0, 0),
	GATE(CLK_UART3, "uart3", "div_aclk66", GATE_IP_PERIC, 3, 0, 0),
	GATE(CLK_UART4, "uart4", "div_aclk66", GATE_IP_PERIC, 4, 0, 0),
	GATE(CLK_I2C0, "i2c0", "div_aclk66", GATE_IP_PERIC, 6, 0, 0),
	GATE(CLK_I2C1, "i2c1", "div_aclk66", GATE_IP_PERIC, 7, 0, 0),
	GATE(CLK_I2C2, "i2c2", "div_aclk66", GATE_IP_PERIC, 8, 0, 0),
	GATE(CLK_I2C3, "i2c3", "div_aclk66", GATE_IP_PERIC, 9, 0, 0),
	GATE(CLK_I2C4, "i2c4", "div_aclk66", GATE_IP_PERIC, 10, 0, 0),
	GATE(CLK_I2C5, "i2c5", "div_aclk66", GATE_IP_PERIC, 11, 0, 0),
	GATE(CLK_I2C6, "i2c6", "div_aclk66", GATE_IP_PERIC, 12, 0, 0),
	GATE(CLK_I2C7, "i2c7", "div_aclk66", GATE_IP_PERIC, 13, 0, 0),
	GATE(CLK_I2C_HDMI, "i2c_hdmi", "div_aclk66", GATE_IP_PERIC, 14, 0, 0),
	GATE(CLK_ADC, "adc", "div_aclk66", GATE_IP_PERIC, 15, 0, 0),
	GATE(CLK_SPI0, "spi0", "div_aclk66", GATE_IP_PERIC, 16, 0, 0),
	GATE(CLK_SPI1, "spi1", "div_aclk66", GATE_IP_PERIC, 17, 0, 0),
	GATE(CLK_SPI2, "spi2", "div_aclk66", GATE_IP_PERIC, 18, 0, 0),
	GATE(CLK_I2S1, "i2s1", "div_aclk66", GATE_IP_PERIC, 20, 0, 0),
	GATE(CLK_I2S2, "i2s2", "div_aclk66", GATE_IP_PERIC, 21, 0, 0),
	GATE(CLK_PCM1, "pcm1", "div_aclk66", GATE_IP_PERIC, 22, 0, 0),
	GATE(CLK_PCM2, "pcm2", "div_aclk66", GATE_IP_PERIC, 23, 0, 0),
	GATE(CLK_PWM, "pwm", "div_aclk66", GATE_IP_PERIC, 24, 0, 0),
	GATE(CLK_SPDIF, "spdif", "div_aclk66", GATE_IP_PERIC, 26, 0, 0),
	GATE(CLK_AC97, "ac97", "div_aclk66", GATE_IP_PERIC, 27, 0, 0),
	GATE(CLK_HSI2C0, "hsi2c0", "div_aclk66", GATE_IP_PERIC, 28, 0, 0),
	GATE(CLK_HSI2C1, "hsi2c1", "div_aclk66", GATE_IP_PERIC, 29, 0, 0),
	GATE(CLK_HSI2C2, "hsi2c2", "div_aclk66", GATE_IP_PERIC, 30, 0, 0),
	GATE(CLK_HSI2C3, "hsi2c3", "div_aclk66", GATE_IP_PERIC, 31, 0, 0),

	GATE(CLK_CHIPID, "chipid", "div_aclk66", GATE_IP_PERIS, 0, 0, 0),
	GATE(CLK_SYSREG, "sysreg", "div_aclk66",
			GATE_IP_PERIS, 1, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_PMU, "pmu", "div_aclk66", GATE_IP_PERIS, 2, CLK_IGNORE_UNUSED,
		0),
	GATE(CLK_CMU_TOP, "cmu_top", "div_aclk66",
			GATE_IP_PERIS, 3, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_CMU_CORE, "cmu_core", "div_aclk66",
			GATE_IP_PERIS, 4, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_CMU_MEM, "cmu_mem", "div_aclk66",
			GATE_IP_PERIS, 5, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_TZPC0, "tzpc0", "div_aclk66", GATE_IP_PERIS, 6, 0, 0),
	GATE(CLK_TZPC1, "tzpc1", "div_aclk66", GATE_IP_PERIS, 7, 0, 0),
	GATE(CLK_TZPC2, "tzpc2", "div_aclk66", GATE_IP_PERIS, 8, 0, 0),
	GATE(CLK_TZPC3, "tzpc3", "div_aclk66", GATE_IP_PERIS, 9, 0, 0),
	GATE(CLK_TZPC4, "tzpc4", "div_aclk66", GATE_IP_PERIS, 10, 0, 0),
	GATE(CLK_TZPC5, "tzpc5", "div_aclk66", GATE_IP_PERIS, 11, 0, 0),
	GATE(CLK_TZPC6, "tzpc6", "div_aclk66", GATE_IP_PERIS, 12, 0, 0),
	GATE(CLK_TZPC7, "tzpc7", "div_aclk66", GATE_IP_PERIS, 13, 0, 0),
	GATE(CLK_TZPC8, "tzpc8", "div_aclk66", GATE_IP_PERIS, 14, 0, 0),
	GATE(CLK_TZPC9, "tzpc9", "div_aclk66", GATE_IP_PERIS, 15, 0, 0),
	GATE(CLK_HDMI_CEC, "hdmi_cec", "div_aclk66", GATE_IP_PERIS, 16, 0, 0),
	GATE(CLK_MCT, "mct", "div_aclk66", GATE_IP_PERIS, 18, 0, 0),
	GATE(CLK_WDT, "wdt", "div_aclk66", GATE_IP_PERIS, 19, 0, 0),
	GATE(CLK_RTC, "rtc", "div_aclk66", GATE_IP_PERIS, 20, 0, 0),
	GATE(CLK_TMU, "tmu", "div_aclk66", GATE_IP_PERIS, 21, 0, 0),
	GATE(CLK_SMMU_2D, "smmu_2d", "div_aclk200", GATE_IP_ACP, 7, 0, 0),
	GATE(CLK_SMMU_FIMC_ISP, "smmu_fimc_isp", "mout_aclk_266_isp_sub",
			GATE_IP_ISP0, 8, 0, 0),
	GATE(CLK_SMMU_FIMC_DRC, "smmu_fimc_drc", "mout_aclk_266_isp_sub",
			GATE_IP_ISP0, 9, 0, 0),
	GATE(CLK_SMMU_FIMC_FD, "smmu_fimc_fd", "mout_aclk_266_isp_sub",
			GATE_IP_ISP0, 10, 0, 0),
	GATE(CLK_SMMU_FIMC_SCC, "smmu_fimc_scc", "mout_aclk_266_isp_sub",
			GATE_IP_ISP0, 11, 0, 0),
	GATE(CLK_SMMU_FIMC_SCP, "smmu_fimc_scp", "mout_aclk_266_isp_sub",
			GATE_IP_ISP0, 12, 0, 0),
	GATE(CLK_SMMU_FIMC_MCU, "smmu_fimc_mcu", "mout_aclk_400_isp_sub",
			GATE_IP_ISP0, 13, 0, 0),
	GATE(CLK_SMMU_FIMC_ODC, "smmu_fimc_odc", "mout_aclk_266_isp_sub",
			GATE_IP_ISP1, 4, 0, 0),
	GATE(CLK_SMMU_FIMC_DIS0, "smmu_fimc_dis0", "mout_aclk_266_isp_sub",
			GATE_IP_ISP1, 5, 0, 0),
	GATE(CLK_SMMU_FIMC_DIS1, "smmu_fimc_dis1", "mout_aclk_266_isp_sub",
			GATE_IP_ISP1, 6, 0, 0),
	GATE(CLK_SMMU_FIMC_3DNR, "smmu_fimc_3dnr", "mout_aclk_266_isp_sub",
			GATE_IP_ISP1, 7, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा samsung_gate_घड़ी exynos5250_disp_gate_clks[] __initस्थिर = अणु
	GATE(CLK_FIMD1, "fimd1", "mout_aclk200_disp1_sub", GATE_IP_DISP1, 0, 0,
		0),
	GATE(CLK_MIE1, "mie1", "mout_aclk200_disp1_sub", GATE_IP_DISP1, 1, 0,
		0),
	GATE(CLK_DSIM0, "dsim0", "mout_aclk200_disp1_sub", GATE_IP_DISP1, 3, 0,
		0),
	GATE(CLK_DP, "dp", "mout_aclk200_disp1_sub", GATE_IP_DISP1, 4, 0, 0),
	GATE(CLK_MIXER, "mixer", "mout_aclk200_disp1_sub", GATE_IP_DISP1, 5, 0,
		0),
	GATE(CLK_HDMI, "hdmi", "mout_aclk200_disp1_sub", GATE_IP_DISP1, 6, 0,
		0),
	GATE(CLK_SMMU_TV, "smmu_tv", "mout_aclk200_disp1_sub",
			GATE_IP_DISP1, 9, 0, 0),
	GATE(CLK_SMMU_FIMD1, "smmu_fimd1", "mout_aclk200_disp1_sub",
			GATE_IP_DISP1, 8, 0, 0),
पूर्ण;

अटल काष्ठा exynos5_subcmu_reg_dump exynos5250_disp_suspend_regs[] = अणु
	अणु GATE_IP_DISP1, 0xffffffff, 0xffffffff पूर्ण, /* DISP1 gates */
	अणु SRC_TOP3, 0, BIT(4) पूर्ण,	/* MUX mout_aclk200_disp1_sub */
	अणु SRC_TOP3, 0, BIT(6) पूर्ण,	/* MUX mout_aclk300_disp1_sub */
पूर्ण;

अटल स्थिर काष्ठा exynos5_subcmu_info exynos5250_disp_subcmu = अणु
	.gate_clks	= exynos5250_disp_gate_clks,
	.nr_gate_clks	= ARRAY_SIZE(exynos5250_disp_gate_clks),
	.suspend_regs	= exynos5250_disp_suspend_regs,
	.nr_suspend_regs = ARRAY_SIZE(exynos5250_disp_suspend_regs),
	.pd_name	= "DISP1",
पूर्ण;

अटल स्थिर काष्ठा exynos5_subcmu_info *exynos5250_subcmus[] = अणु
	&exynos5250_disp_subcmu,
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table vpll_24mhz_tbl[] __initस्थिर = अणु
	/* sorted in descending order */
	/* PLL_36XX_RATE(rate, m, p, s, k) */
	PLL_36XX_RATE(24 * MHZ, 266000000, 266, 3, 3, 0),
	/* Not in UM, but need क्रम eDP on snow */
	PLL_36XX_RATE(24 * MHZ, 70500000, 94, 2, 4, 0),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table epll_24mhz_tbl[] __initस्थिर = अणु
	/* sorted in descending order */
	/* PLL_36XX_RATE(rate, m, p, s, k) */
	PLL_36XX_RATE(24 * MHZ, 192000000, 64, 2, 2, 0),
	PLL_36XX_RATE(24 * MHZ, 180633605, 90, 3, 2, 20762),
	PLL_36XX_RATE(24 * MHZ, 180000000, 90, 3, 2, 0),
	PLL_36XX_RATE(24 * MHZ, 73728000, 98, 2, 4, 19923),
	PLL_36XX_RATE(24 * MHZ, 67737602, 90, 2, 4, 20762),
	PLL_36XX_RATE(24 * MHZ, 49152000, 98, 3, 4, 19923),
	PLL_36XX_RATE(24 * MHZ, 45158401, 90, 3, 4, 20762),
	PLL_36XX_RATE(24 * MHZ, 32768001, 131, 3, 5, 4719),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pll_rate_table apll_24mhz_tbl[] __initस्थिर = अणु
	/* sorted in descending order */
	/* PLL_35XX_RATE(fin, rate, m, p, s) */
	PLL_35XX_RATE(24 * MHZ, 1700000000, 425, 6, 0),
	PLL_35XX_RATE(24 * MHZ, 1600000000, 200, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 1500000000, 250, 4, 0),
	PLL_35XX_RATE(24 * MHZ, 1400000000, 175, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 1300000000, 325, 6, 0),
	PLL_35XX_RATE(24 * MHZ, 1200000000, 200, 4, 0),
	PLL_35XX_RATE(24 * MHZ, 1100000000, 275, 6, 0),
	PLL_35XX_RATE(24 * MHZ, 1000000000, 125, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 900000000, 150, 4, 0),
	PLL_35XX_RATE(24 * MHZ, 800000000, 100, 3, 0),
	PLL_35XX_RATE(24 * MHZ, 700000000, 175, 3, 1),
	PLL_35XX_RATE(24 * MHZ, 600000000, 200, 4, 1),
	PLL_35XX_RATE(24 * MHZ, 500000000, 125, 3, 1),
	PLL_35XX_RATE(24 * MHZ, 400000000, 100, 3, 1),
	PLL_35XX_RATE(24 * MHZ, 300000000, 200, 4, 2),
	PLL_35XX_RATE(24 * MHZ, 200000000, 100, 3, 2),
पूर्ण;

अटल काष्ठा samsung_pll_घड़ी exynos5250_plls[nr_plls] __initdata = अणु
	[apll] = PLL(pll_35xx, CLK_FOUT_APLL, "fout_apll", "fin_pll", APLL_LOCK,
		APLL_CON0, शून्य),
	[mpll] = PLL(pll_35xx, CLK_FOUT_MPLL, "fout_mpll", "fin_pll", MPLL_LOCK,
		MPLL_CON0, शून्य),
	[bpll] = PLL(pll_35xx, CLK_FOUT_BPLL, "fout_bpll", "fin_pll", BPLL_LOCK,
		BPLL_CON0, शून्य),
	[gpll] = PLL(pll_35xx, CLK_FOUT_GPLL, "fout_gpll", "fin_pll", GPLL_LOCK,
		GPLL_CON0, शून्य),
	[cpll] = PLL(pll_35xx, CLK_FOUT_CPLL, "fout_cpll", "fin_pll", CPLL_LOCK,
		CPLL_CON0, शून्य),
	[epll] = PLL(pll_36xx, CLK_FOUT_EPLL, "fout_epll", "fin_pll", EPLL_LOCK,
		EPLL_CON0, शून्य),
	[vpll] = PLL(pll_36xx, CLK_FOUT_VPLL, "fout_vpll", "mout_vpllsrc",
		VPLL_LOCK, VPLL_CON0, शून्य),
पूर्ण;

#घोषणा E5250_CPU_DIV0(apll, pclk_dbg, atb, periph, acp, cpud)		\
		((((apll) << 24) | ((pclk_dbg) << 20) | ((atb) << 16) |	\
		 ((periph) << 12) | ((acp) << 8) | ((cpud) << 4)))
#घोषणा E5250_CPU_DIV1(hpm, copy)					\
		(((hpm) << 4) | (copy))

अटल स्थिर काष्ठा exynos_cpuclk_cfg_data exynos5250_armclk_d[] __initस्थिर = अणु
	अणु 1700000, E5250_CPU_DIV0(5, 3, 7, 7, 7, 3), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1600000, E5250_CPU_DIV0(4, 1, 7, 7, 7, 3), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1500000, E5250_CPU_DIV0(4, 1, 7, 7, 7, 2), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1400000, E5250_CPU_DIV0(4, 1, 6, 7, 7, 2), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1300000, E5250_CPU_DIV0(3, 1, 6, 7, 7, 2), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1200000, E5250_CPU_DIV0(3, 1, 5, 7, 7, 2), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1100000, E5250_CPU_DIV0(3, 1, 5, 7, 7, 3), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु 1000000, E5250_CPU_DIV0(2, 1, 4, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  900000, E5250_CPU_DIV0(2, 1, 4, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  800000, E5250_CPU_DIV0(2, 1, 4, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  700000, E5250_CPU_DIV0(1, 1, 3, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  600000, E5250_CPU_DIV0(1, 1, 3, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  500000, E5250_CPU_DIV0(1, 1, 2, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  400000, E5250_CPU_DIV0(1, 1, 2, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  300000, E5250_CPU_DIV0(1, 1, 1, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  200000, E5250_CPU_DIV0(1, 1, 1, 7, 7, 1), E5250_CPU_DIV1(2, 0), पूर्ण,
	अणु  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ext_clk_match[] __initस्थिर = अणु
	अणु .compatible = "samsung,clock-xxti", .data = (व्योम *)0, पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* रेजिस्टर exynox5250 घड़ीs */
अटल व्योम __init exynos5250_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा samsung_clk_provider *ctx;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा clk_hw **hws;

	अगर (np) अणु
		reg_base = of_iomap(np, 0);
		अगर (!reg_base)
			panic("%s: failed to map registers\n", __func__);
	पूर्ण अन्यथा अणु
		panic("%s: unable to determine soc\n", __func__);
	पूर्ण

	ctx = samsung_clk_init(np, reg_base, CLK_NR_CLKS);
	hws = ctx->clk_data.hws;

	samsung_clk_of_रेजिस्टर_fixed_ext(ctx, exynos5250_fixed_rate_ext_clks,
			ARRAY_SIZE(exynos5250_fixed_rate_ext_clks),
			ext_clk_match);
	samsung_clk_रेजिस्टर_mux(ctx, exynos5250_pll_pmux_clks,
				ARRAY_SIZE(exynos5250_pll_pmux_clks));

	अगर (_get_rate("fin_pll") == 24 * MHZ) अणु
		exynos5250_plls[epll].rate_table = epll_24mhz_tbl;
		exynos5250_plls[apll].rate_table = apll_24mhz_tbl;
	पूर्ण

	अगर (_get_rate("mout_vpllsrc") == 24 * MHZ)
		exynos5250_plls[vpll].rate_table =  vpll_24mhz_tbl;

	samsung_clk_रेजिस्टर_pll(ctx, exynos5250_plls,
			ARRAY_SIZE(exynos5250_plls),
			reg_base);
	samsung_clk_रेजिस्टर_fixed_rate(ctx, exynos5250_fixed_rate_clks,
			ARRAY_SIZE(exynos5250_fixed_rate_clks));
	samsung_clk_रेजिस्टर_fixed_factor(ctx, exynos5250_fixed_factor_clks,
			ARRAY_SIZE(exynos5250_fixed_factor_clks));
	samsung_clk_रेजिस्टर_mux(ctx, exynos5250_mux_clks,
			ARRAY_SIZE(exynos5250_mux_clks));
	samsung_clk_रेजिस्टर_भाग(ctx, exynos5250_भाग_clks,
			ARRAY_SIZE(exynos5250_भाग_clks));
	samsung_clk_रेजिस्टर_gate(ctx, exynos5250_gate_clks,
			ARRAY_SIZE(exynos5250_gate_clks));
	exynos_रेजिस्टर_cpu_घड़ी(ctx, CLK_ARM_CLK, "armclk",
			hws[CLK_MOUT_APLL], hws[CLK_MOUT_MPLL], 0x200,
			exynos5250_armclk_d, ARRAY_SIZE(exynos5250_armclk_d),
			CLK_CPU_HAS_DIV1);

	/*
	 * Enable arm घड़ी करोwn (in idle) and set arm भागider
	 * ratios in WFI/WFE state.
	 */
	पंचांगp = (PWR_CTRL1_CORE2_DOWN_RATIO | PWR_CTRL1_CORE1_DOWN_RATIO |
		PWR_CTRL1_DIV2_DOWN_EN | PWR_CTRL1_DIV1_DOWN_EN |
		PWR_CTRL1_USE_CORE1_WFE | PWR_CTRL1_USE_CORE0_WFE |
		PWR_CTRL1_USE_CORE1_WFI | PWR_CTRL1_USE_CORE0_WFI);
	__raw_ग_लिखोl(पंचांगp, reg_base + PWR_CTRL1);

	/*
	 * Enable arm घड़ी up (on निकासing idle). Set arm भागider
	 * ratios when not in idle aदीर्घ with the standby duration
	 * ratios.
	 */
	पंचांगp = (PWR_CTRL2_DIV2_UP_EN | PWR_CTRL2_DIV1_UP_EN |
		PWR_CTRL2_DUR_STANDBY2_VAL | PWR_CTRL2_DUR_STANDBY1_VAL |
		PWR_CTRL2_CORE2_UP_RATIO | PWR_CTRL2_CORE1_UP_RATIO);
	__raw_ग_लिखोl(पंचांगp, reg_base + PWR_CTRL2);

	samsung_clk_sleep_init(reg_base, exynos5250_clk_regs,
			       ARRAY_SIZE(exynos5250_clk_regs));
	exynos5_subcmus_init(ctx, ARRAY_SIZE(exynos5250_subcmus),
			     exynos5250_subcmus);

	samsung_clk_of_add_provider(np, ctx);

	pr_info("Exynos5250: clock setup completed, armclk=%ld\n",
			_get_rate("div_arm2"));
पूर्ण
CLK_OF_DECLARE_DRIVER(exynos5250_clk, "samsung,exynos5250-clock", exynos5250_clk_init);
