<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * Copyright (c) 2015 Rockchip Electronics Co. Ltd.
 * Author: Xing Zheng <zhengxing@rock-chips.com>
 *
 * based on
 *
 * samsung/clk.h
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 */

#अगर_अघोषित CLK_ROCKCHIP_CLK_H
#घोषणा CLK_ROCKCHIP_CLK_H

#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>

काष्ठा clk;

#घोषणा HIWORD_UPDATE(val, mask, shअगरt) \
		((val) << (shअगरt) | (mask) << ((shअगरt) + 16))

/* रेजिस्टर positions shared by PX30, RV1108, RK2928, RK3036, RK3066, RK3188 and RK3228 */
#घोषणा BOOST_PLL_H_CON(x)		((x) * 0x4)
#घोषणा BOOST_CLK_CON			0x0008
#घोषणा BOOST_BOOST_CON			0x000c
#घोषणा BOOST_SWITCH_CNT		0x0010
#घोषणा BOOST_HIGH_PERF_CNT0		0x0014
#घोषणा BOOST_HIGH_PERF_CNT1		0x0018
#घोषणा BOOST_STATIS_THRESHOLD		0x001c
#घोषणा BOOST_SHORT_SWITCH_CNT		0x0020
#घोषणा BOOST_SWITCH_THRESHOLD		0x0024
#घोषणा BOOST_FSM_STATUS		0x0028
#घोषणा BOOST_PLL_L_CON(x)		((x) * 0x4 + 0x2c)
#घोषणा BOOST_RECOVERY_MASK		0x1
#घोषणा BOOST_RECOVERY_SHIFT		1
#घोषणा BOOST_SW_CTRL_MASK		0x1
#घोषणा BOOST_SW_CTRL_SHIFT		2
#घोषणा BOOST_LOW_FREQ_EN_MASK		0x1
#घोषणा BOOST_LOW_FREQ_EN_SHIFT		3
#घोषणा BOOST_BUSY_STATE		BIT(8)

#घोषणा PX30_PLL_CON(x)			((x) * 0x4)
#घोषणा PX30_CLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा PX30_CLKGATE_CON(x)		((x) * 0x4 + 0x200)
#घोषणा PX30_GLB_SRST_FST		0xb8
#घोषणा PX30_GLB_SRST_SND		0xbc
#घोषणा PX30_SOFTRST_CON(x)		((x) * 0x4 + 0x300)
#घोषणा PX30_MODE_CON			0xa0
#घोषणा PX30_MISC_CON			0xa4
#घोषणा PX30_SDMMC_CON0			0x380
#घोषणा PX30_SDMMC_CON1			0x384
#घोषणा PX30_SDIO_CON0			0x388
#घोषणा PX30_SDIO_CON1			0x38c
#घोषणा PX30_EMMC_CON0			0x390
#घोषणा PX30_EMMC_CON1			0x394

#घोषणा PX30_PMU_PLL_CON(x)		((x) * 0x4)
#घोषणा PX30_PMU_CLKSEL_CON(x)		((x) * 0x4 + 0x40)
#घोषणा PX30_PMU_CLKGATE_CON(x)		((x) * 0x4 + 0x80)
#घोषणा PX30_PMU_MODE			0x0020

#घोषणा RV1108_PLL_CON(x)		((x) * 0x4)
#घोषणा RV1108_CLKSEL_CON(x)		((x) * 0x4 + 0x60)
#घोषणा RV1108_CLKGATE_CON(x)		((x) * 0x4 + 0x120)
#घोषणा RV1108_SOFTRST_CON(x)		((x) * 0x4 + 0x180)
#घोषणा RV1108_GLB_SRST_FST		0x1c0
#घोषणा RV1108_GLB_SRST_SND		0x1c4
#घोषणा RV1108_MISC_CON			0x1cc
#घोषणा RV1108_SDMMC_CON0		0x1d8
#घोषणा RV1108_SDMMC_CON1		0x1dc
#घोषणा RV1108_SDIO_CON0		0x1e0
#घोषणा RV1108_SDIO_CON1		0x1e4
#घोषणा RV1108_EMMC_CON0		0x1e8
#घोषणा RV1108_EMMC_CON1		0x1ec

#घोषणा RK2928_PLL_CON(x)		((x) * 0x4)
#घोषणा RK2928_MODE_CON		0x40
#घोषणा RK2928_CLKSEL_CON(x)	((x) * 0x4 + 0x44)
#घोषणा RK2928_CLKGATE_CON(x)	((x) * 0x4 + 0xd0)
#घोषणा RK2928_GLB_SRST_FST		0x100
#घोषणा RK2928_GLB_SRST_SND		0x104
#घोषणा RK2928_SOFTRST_CON(x)	((x) * 0x4 + 0x110)
#घोषणा RK2928_MISC_CON		0x134

#घोषणा RK3036_SDMMC_CON0		0x144
#घोषणा RK3036_SDMMC_CON1		0x148
#घोषणा RK3036_SDIO_CON0		0x14c
#घोषणा RK3036_SDIO_CON1		0x150
#घोषणा RK3036_EMMC_CON0		0x154
#घोषणा RK3036_EMMC_CON1		0x158

#घोषणा RK3228_GLB_SRST_FST		0x1f0
#घोषणा RK3228_GLB_SRST_SND		0x1f4
#घोषणा RK3228_SDMMC_CON0		0x1c0
#घोषणा RK3228_SDMMC_CON1		0x1c4
#घोषणा RK3228_SDIO_CON0		0x1c8
#घोषणा RK3228_SDIO_CON1		0x1cc
#घोषणा RK3228_EMMC_CON0		0x1d8
#घोषणा RK3228_EMMC_CON1		0x1dc

#घोषणा RK3288_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3288_MODE_CON			0x50
#घोषणा RK3288_CLKSEL_CON(x)		((x) * 0x4 + 0x60)
#घोषणा RK3288_CLKGATE_CON(x)		((x) * 0x4 + 0x160)
#घोषणा RK3288_GLB_SRST_FST		0x1b0
#घोषणा RK3288_GLB_SRST_SND		0x1b4
#घोषणा RK3288_SOFTRST_CON(x)		((x) * 0x4 + 0x1b8)
#घोषणा RK3288_MISC_CON			0x1e8
#घोषणा RK3288_SDMMC_CON0		0x200
#घोषणा RK3288_SDMMC_CON1		0x204
#घोषणा RK3288_SDIO0_CON0		0x208
#घोषणा RK3288_SDIO0_CON1		0x20c
#घोषणा RK3288_SDIO1_CON0		0x210
#घोषणा RK3288_SDIO1_CON1		0x214
#घोषणा RK3288_EMMC_CON0		0x218
#घोषणा RK3288_EMMC_CON1		0x21c

#घोषणा RK3308_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3308_CLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा RK3308_CLKGATE_CON(x)		((x) * 0x4 + 0x300)
#घोषणा RK3308_GLB_SRST_FST		0xb8
#घोषणा RK3308_SOFTRST_CON(x)		((x) * 0x4 + 0x400)
#घोषणा RK3308_MODE_CON			0xa0
#घोषणा RK3308_SDMMC_CON0		0x480
#घोषणा RK3308_SDMMC_CON1		0x484
#घोषणा RK3308_SDIO_CON0		0x488
#घोषणा RK3308_SDIO_CON1		0x48c
#घोषणा RK3308_EMMC_CON0		0x490
#घोषणा RK3308_EMMC_CON1		0x494

#घोषणा RK3328_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3328_CLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा RK3328_CLKGATE_CON(x)		((x) * 0x4 + 0x200)
#घोषणा RK3328_GRFCLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा RK3328_GLB_SRST_FST		0x9c
#घोषणा RK3328_GLB_SRST_SND		0x98
#घोषणा RK3328_SOFTRST_CON(x)		((x) * 0x4 + 0x300)
#घोषणा RK3328_MODE_CON			0x80
#घोषणा RK3328_MISC_CON			0x84
#घोषणा RK3328_SDMMC_CON0		0x380
#घोषणा RK3328_SDMMC_CON1		0x384
#घोषणा RK3328_SDIO_CON0		0x388
#घोषणा RK3328_SDIO_CON1		0x38c
#घोषणा RK3328_EMMC_CON0		0x390
#घोषणा RK3328_EMMC_CON1		0x394
#घोषणा RK3328_SDMMC_EXT_CON0		0x398
#घोषणा RK3328_SDMMC_EXT_CON1		0x39C

#घोषणा RK3368_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3368_CLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा RK3368_CLKGATE_CON(x)		((x) * 0x4 + 0x200)
#घोषणा RK3368_GLB_SRST_FST		0x280
#घोषणा RK3368_GLB_SRST_SND		0x284
#घोषणा RK3368_SOFTRST_CON(x)		((x) * 0x4 + 0x300)
#घोषणा RK3368_MISC_CON			0x380
#घोषणा RK3368_SDMMC_CON0		0x400
#घोषणा RK3368_SDMMC_CON1		0x404
#घोषणा RK3368_SDIO0_CON0		0x408
#घोषणा RK3368_SDIO0_CON1		0x40c
#घोषणा RK3368_SDIO1_CON0		0x410
#घोषणा RK3368_SDIO1_CON1		0x414
#घोषणा RK3368_EMMC_CON0		0x418
#घोषणा RK3368_EMMC_CON1		0x41c

#घोषणा RK3399_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3399_CLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा RK3399_CLKGATE_CON(x)		((x) * 0x4 + 0x300)
#घोषणा RK3399_SOFTRST_CON(x)		((x) * 0x4 + 0x400)
#घोषणा RK3399_GLB_SRST_FST		0x500
#घोषणा RK3399_GLB_SRST_SND		0x504
#घोषणा RK3399_GLB_CNT_TH		0x508
#घोषणा RK3399_MISC_CON			0x50c
#घोषणा RK3399_RST_CON			0x510
#घोषणा RK3399_RST_ST			0x514
#घोषणा RK3399_SDMMC_CON0		0x580
#घोषणा RK3399_SDMMC_CON1		0x584
#घोषणा RK3399_SDIO_CON0		0x588
#घोषणा RK3399_SDIO_CON1		0x58c

#घोषणा RK3399_PMU_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3399_PMU_CLKSEL_CON(x)	((x) * 0x4 + 0x80)
#घोषणा RK3399_PMU_CLKGATE_CON(x)	((x) * 0x4 + 0x100)
#घोषणा RK3399_PMU_SOFTRST_CON(x)	((x) * 0x4 + 0x110)

#घोषणा RK3568_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3568_MODE_CON0		0xc0
#घोषणा RK3568_MISC_CON0		0xc4
#घोषणा RK3568_MISC_CON1		0xc8
#घोषणा RK3568_MISC_CON2		0xcc
#घोषणा RK3568_GLB_CNT_TH		0xd0
#घोषणा RK3568_GLB_SRST_FST		0xd4
#घोषणा RK3568_GLB_SRST_SND		0xd8
#घोषणा RK3568_GLB_RST_CON		0xdc
#घोषणा RK3568_GLB_RST_ST		0xe0
#घोषणा RK3568_CLKSEL_CON(x)		((x) * 0x4 + 0x100)
#घोषणा RK3568_CLKGATE_CON(x)		((x) * 0x4 + 0x300)
#घोषणा RK3568_SOFTRST_CON(x)		((x) * 0x4 + 0x400)
#घोषणा RK3568_SDMMC0_CON0		0x580
#घोषणा RK3568_SDMMC0_CON1		0x584
#घोषणा RK3568_SDMMC1_CON0		0x588
#घोषणा RK3568_SDMMC1_CON1		0x58c
#घोषणा RK3568_SDMMC2_CON0		0x590
#घोषणा RK3568_SDMMC2_CON1		0x594
#घोषणा RK3568_EMMC_CON0		0x598
#घोषणा RK3568_EMMC_CON1		0x59c

#घोषणा RK3568_PMU_PLL_CON(x)		RK2928_PLL_CON(x)
#घोषणा RK3568_PMU_MODE_CON0		0x80
#घोषणा RK3568_PMU_CLKSEL_CON(x)	((x) * 0x4 + 0x100)
#घोषणा RK3568_PMU_CLKGATE_CON(x)	((x) * 0x4 + 0x180)
#घोषणा RK3568_PMU_SOFTRST_CON(x)	((x) * 0x4 + 0x200)

क्रमागत rockchip_pll_type अणु
	pll_rk3036,
	pll_rk3066,
	pll_rk3328,
	pll_rk3399,
पूर्ण;

#घोषणा RK3036_PLL_RATE(_rate, _refभाग, _fbभाग, _postभाग1,	\
			_postभाग2, _dsmpd, _frac)		\
अणु								\
	.rate	= _rate##U,					\
	.fbभाग = _fbभाग,					\
	.postभाग1 = _postभाग1,					\
	.refभाग = _refभाग,					\
	.postभाग2 = _postभाग2,					\
	.dsmpd = _dsmpd,					\
	.frac = _frac,						\
पूर्ण

#घोषणा RK3066_PLL_RATE(_rate, _nr, _nf, _no)	\
अणु						\
	.rate	= _rate##U,			\
	.nr = _nr,				\
	.nf = _nf,				\
	.no = _no,				\
	.nb = ((_nf) < 2) ? 1 : (_nf) >> 1,	\
पूर्ण

#घोषणा RK3066_PLL_RATE_NB(_rate, _nr, _nf, _no, _nb)		\
अणु								\
	.rate	= _rate##U,					\
	.nr = _nr,						\
	.nf = _nf,						\
	.no = _no,						\
	.nb = _nb,						\
पूर्ण

/**
 * काष्ठा rockchip_clk_provider - inक्रमmation about घड़ी provider
 * @reg_base: भव address क्रम the रेजिस्टर base.
 * @clk_data: holds घड़ी related data like clk* and number of घड़ीs.
 * @cru_node: device-node of the घड़ी-provider
 * @grf: regmap of the general-रेजिस्टर-files syscon
 * @lock: मुख्यtains exclusion between callbacks क्रम a given घड़ी-provider.
 */
काष्ठा rockchip_clk_provider अणु
	व्योम __iomem *reg_base;
	काष्ठा clk_onecell_data clk_data;
	काष्ठा device_node *cru_node;
	काष्ठा regmap *grf;
	spinlock_t lock;
पूर्ण;

काष्ठा rockchip_pll_rate_table अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक nr;
	अचिन्हित पूर्णांक nf;
	अचिन्हित पूर्णांक no;
	अचिन्हित पूर्णांक nb;
	/* क्रम RK3036/RK3399 */
	अचिन्हित पूर्णांक fbभाग;
	अचिन्हित पूर्णांक postभाग1;
	अचिन्हित पूर्णांक refभाग;
	अचिन्हित पूर्णांक postभाग2;
	अचिन्हित पूर्णांक dsmpd;
	अचिन्हित पूर्णांक frac;
पूर्ण;

/**
 * काष्ठा rockchip_pll_घड़ी - inक्रमmation about pll घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this pll घड़ी.
 * @parent_names: name of the parent घड़ी.
 * @num_parents: number of parents
 * @flags: optional flags क्रम basic घड़ी.
 * @con_offset: offset of the रेजिस्टर क्रम configuring the PLL.
 * @mode_offset: offset of the रेजिस्टर क्रम configuring the PLL-mode.
 * @mode_shअगरt: offset inside the mode-रेजिस्टर क्रम the mode of this pll.
 * @lock_shअगरt: offset inside the lock रेजिस्टर क्रम the lock status.
 * @type: Type of PLL to be रेजिस्टरed.
 * @pll_flags: hardware-specअगरic flags
 * @rate_table: Table of usable pll rates
 *
 * Flags:
 * ROCKCHIP_PLL_SYNC_RATE - check rate parameters to match against the
 *	rate_table parameters and ajust them अगर necessary.
 */
काष्ठा rockchip_pll_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*स्थिर *parent_names;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			con_offset;
	पूर्णांक			mode_offset;
	पूर्णांक			mode_shअगरt;
	पूर्णांक			lock_shअगरt;
	क्रमागत rockchip_pll_type	type;
	u8			pll_flags;
	काष्ठा rockchip_pll_rate_table *rate_table;
पूर्ण;

#घोषणा ROCKCHIP_PLL_SYNC_RATE		BIT(0)

#घोषणा PLL(_type, _id, _name, _pnames, _flags, _con, _mode, _mshअगरt,	\
		_lshअगरt, _pflags, _rtable)				\
	अणु								\
		.id		= _id,					\
		.type		= _type,				\
		.name		= _name,				\
		.parent_names	= _pnames,				\
		.num_parents	= ARRAY_SIZE(_pnames),			\
		.flags		= CLK_GET_RATE_NOCACHE | _flags,	\
		.con_offset	= _con,					\
		.mode_offset	= _mode,				\
		.mode_shअगरt	= _mshअगरt,				\
		.lock_shअगरt	= _lshअगरt,				\
		.pll_flags	= _pflags,				\
		.rate_table	= _rtable,				\
	पूर्ण

काष्ठा clk *rockchip_clk_रेजिस्टर_pll(काष्ठा rockchip_clk_provider *ctx,
		क्रमागत rockchip_pll_type pll_type,
		स्थिर अक्षर *name, स्थिर अक्षर *स्थिर *parent_names,
		u8 num_parents, पूर्णांक con_offset, पूर्णांक grf_lock_offset,
		पूर्णांक lock_shअगरt, पूर्णांक mode_offset, पूर्णांक mode_shअगरt,
		काष्ठा rockchip_pll_rate_table *rate_table,
		अचिन्हित दीर्घ flags, u8 clk_pll_flags);

काष्ठा rockchip_cpuclk_clksel अणु
	पूर्णांक reg;
	u32 val;
पूर्ण;

#घोषणा ROCKCHIP_CPUCLK_NUM_DIVIDERS	5
#घोषणा ROCKCHIP_CPUCLK_MAX_CORES	4
काष्ठा rockchip_cpuclk_rate_table अणु
	अचिन्हित दीर्घ prate;
	काष्ठा rockchip_cpuclk_clksel भागs[ROCKCHIP_CPUCLK_NUM_DIVIDERS];
पूर्ण;

/**
 * काष्ठा rockchip_cpuclk_reg_data - रेजिस्टर offsets and masks of the cpuघड़ी
 * @core_reg[]:	रेजिस्टर offset of the cores setting रेजिस्टर
 * @भाग_core_shअगरt[]:	cores भागider offset used to भागide the pll value
 * @भाग_core_mask[]:	cores भागider mask
 * @num_cores:	number of cpu cores
 * @mux_core_मुख्य:	mux value to select मुख्य parent of core
 * @mux_core_shअगरt:	offset of the core multiplexer
 * @mux_core_mask:	core multiplexer mask
 */
काष्ठा rockchip_cpuclk_reg_data अणु
	पूर्णांक	core_reg[ROCKCHIP_CPUCLK_MAX_CORES];
	u8	भाग_core_shअगरt[ROCKCHIP_CPUCLK_MAX_CORES];
	u32	भाग_core_mask[ROCKCHIP_CPUCLK_MAX_CORES];
	पूर्णांक	num_cores;
	u8	mux_core_alt;
	u8	mux_core_मुख्य;
	u8	mux_core_shअगरt;
	u32	mux_core_mask;
पूर्ण;

काष्ठा clk *rockchip_clk_रेजिस्टर_cpuclk(स्थिर अक्षर *name,
			स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
			स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data,
			स्थिर काष्ठा rockchip_cpuclk_rate_table *rates,
			पूर्णांक nrates, व्योम __iomem *reg_base, spinlock_t *lock);

काष्ठा clk *rockchip_clk_रेजिस्टर_mmc(स्थिर अक्षर *name,
				स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
				व्योम __iomem *reg, पूर्णांक shअगरt);

/*
 * DDRCLK flags, including method of setting the rate
 * ROCKCHIP_DDRCLK_SIP: use SIP call to bl31 to change ddrclk rate.
 */
#घोषणा ROCKCHIP_DDRCLK_SIP		BIT(0)

काष्ठा clk *rockchip_clk_रेजिस्टर_ddrclk(स्थिर अक्षर *name, पूर्णांक flags,
					 स्थिर अक्षर *स्थिर *parent_names,
					 u8 num_parents, पूर्णांक mux_offset,
					 पूर्णांक mux_shअगरt, पूर्णांक mux_width,
					 पूर्णांक भाग_shअगरt, पूर्णांक भाग_width,
					 पूर्णांक ddr_flags, व्योम __iomem *reg_base,
					 spinlock_t *lock);

#घोषणा ROCKCHIP_INVERTER_HIWORD_MASK	BIT(0)

काष्ठा clk *rockchip_clk_रेजिस्टर_inverter(स्थिर अक्षर *name,
				स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
				व्योम __iomem *reg, पूर्णांक shअगरt, पूर्णांक flags,
				spinlock_t *lock);

काष्ठा clk *rockchip_clk_रेजिस्टर_muxgrf(स्थिर अक्षर *name,
				स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
				पूर्णांक flags, काष्ठा regmap *grf, पूर्णांक reg,
				पूर्णांक shअगरt, पूर्णांक width, पूर्णांक mux_flags);

#घोषणा PNAME(x) अटल स्थिर अक्षर *स्थिर x[] __initस्थिर

क्रमागत rockchip_clk_branch_type अणु
	branch_composite,
	branch_mux,
	branch_muxgrf,
	branch_भागider,
	branch_fraction_भागider,
	branch_gate,
	branch_mmc,
	branch_inverter,
	branch_factor,
	branch_ddrclk,
	branch_half_भागider,
पूर्ण;

काष्ठा rockchip_clk_branch अणु
	अचिन्हित पूर्णांक			id;
	क्रमागत rockchip_clk_branch_type	branch_type;
	स्थिर अक्षर			*name;
	स्थिर अक्षर			*स्थिर *parent_names;
	u8				num_parents;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				muxभाग_offset;
	u8				mux_shअगरt;
	u8				mux_width;
	u8				mux_flags;
	पूर्णांक				भाग_offset;
	u8				भाग_shअगरt;
	u8				भाग_width;
	u8				भाग_flags;
	काष्ठा clk_भाग_प्रकारable		*भाग_प्रकारable;
	पूर्णांक				gate_offset;
	u8				gate_shअगरt;
	u8				gate_flags;
	काष्ठा rockchip_clk_branch	*child;
पूर्ण;

#घोषणा COMPOSITE(_id, cname, pnames, f, mo, ms, mw, mf, ds, dw,\
		  df, go, gs, gf)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_DIV_OFFSET(_id, cname, pnames, f, mo, ms, mw,	\
			     mf, करो, ds, dw, df, go, gs, gf)	\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.भाग_offset	= करो,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_NOMUX(_id, cname, pname, f, mo, ds, dw, df,	\
			go, gs, gf)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_NOMUX_DIVTBL(_id, cname, pname, f, mo, ds, dw,\
			       df, dt, go, gs, gf)		\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.भाग_प्रकारable	= dt,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_NODIV(_id, cname, pnames, f, mo, ms, mw, mf,	\
			go, gs, gf)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_NOGATE(_id, cname, pnames, f, mo, ms, mw, mf,	\
			 ds, dw, df)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= -1,				\
	पूर्ण

#घोषणा COMPOSITE_NOGATE_DIVTBL(_id, cname, pnames, f, mo, ms,	\
				mw, mf, ds, dw, df, dt)		\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_composite,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.भाग_प्रकारable	= dt,				\
		.gate_offset	= -1,				\
	पूर्ण

#घोषणा COMPOSITE_FRAC(_id, cname, pname, f, mo, df, go, gs, gf)\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_fraction_भागider,	\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.भाग_shअगरt	= 16,				\
		.भाग_width	= 16,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_FRACMUX(_id, cname, pname, f, mo, df, go, gs, gf, ch) \
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_fraction_भागider,	\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.भाग_shअगरt	= 16,				\
		.भाग_width	= 16,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
		.child		= ch,				\
	पूर्ण

#घोषणा COMPOSITE_FRACMUX_NOGATE(_id, cname, pname, f, mo, df, ch) \
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_fraction_भागider,	\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.भाग_shअगरt	= 16,				\
		.भाग_width	= 16,				\
		.भाग_flags	= df,				\
		.gate_offset	= -1,				\
		.child		= ch,				\
	पूर्ण

#घोषणा COMPOSITE_DDRCLK(_id, cname, pnames, f, mo, ms, mw,	\
			 ds, dw, df)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_ddrclk,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset  = mo,                           \
		.mux_shअगरt      = ms,                           \
		.mux_width      = mw,                           \
		.भाग_shअगरt      = ds,                           \
		.भाग_width      = dw,                           \
		.भाग_flags	= df,				\
		.gate_offset    = -1,                           \
	पूर्ण

#घोषणा MUX(_id, cname, pnames, f, o, s, w, mf)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_mux,			\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= o,				\
		.mux_shअगरt	= s,				\
		.mux_width	= w,				\
		.mux_flags	= mf,				\
		.gate_offset	= -1,				\
	पूर्ण

#घोषणा MUXGRF(_id, cname, pnames, f, o, s, w, mf)		\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_muxgrf,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= o,				\
		.mux_shअगरt	= s,				\
		.mux_width	= w,				\
		.mux_flags	= mf,				\
		.gate_offset	= -1,				\
	पूर्ण

#घोषणा DIV(_id, cname, pname, f, o, s, w, df)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_भागider,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= o,				\
		.भाग_shअगरt	= s,				\
		.भाग_width	= w,				\
		.भाग_flags	= df,				\
		.gate_offset	= -1,				\
	पूर्ण

#घोषणा DIVTBL(_id, cname, pname, f, o, s, w, df, dt)		\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_भागider,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= o,				\
		.भाग_shअगरt	= s,				\
		.भाग_width	= w,				\
		.भाग_flags	= df,				\
		.भाग_प्रकारable	= dt,				\
	पूर्ण

#घोषणा GATE(_id, cname, pname, f, o, b, gf)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_gate,			\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.gate_offset	= o,				\
		.gate_shअगरt	= b,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा MMC(_id, cname, pname, offset, shअगरt)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_mmc,			\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.muxभाग_offset	= offset,			\
		.भाग_shअगरt	= shअगरt,			\
	पूर्ण

#घोषणा INVERTER(_id, cname, pname, io, is, अगर)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_inverter,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.muxभाग_offset	= io,				\
		.भाग_shअगरt	= is,				\
		.भाग_flags	= अगर,				\
	पूर्ण

#घोषणा FACTOR(_id, cname, pname,  f, fm, fd)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_factor,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.भाग_shअगरt	= fm,				\
		.भाग_width	= fd,				\
	पूर्ण

#घोषणा FACTOR_GATE(_id, cname, pname,  f, fm, fd, go, gb, gf)	\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_factor,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.भाग_shअगरt	= fm,				\
		.भाग_width	= fd,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gb,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_HALFDIV(_id, cname, pnames, f, mo, ms, mw, mf, ds, dw,\
			  df, go, gs, gf)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_half_भागider,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा COMPOSITE_NOGATE_HALFDIV(_id, cname, pnames, f, mo, ms, mw, mf,	\
				 ds, dw, df)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_half_भागider,		\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.mux_shअगरt	= ms,				\
		.mux_width	= mw,				\
		.mux_flags	= mf,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= -1,				\
	पूर्ण

#घोषणा COMPOSITE_NOMUX_HALFDIV(_id, cname, pname, f, mo, ds, dw, df,	\
			go, gs, gf)				\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_half_भागider,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= mo,				\
		.भाग_shअगरt	= ds,				\
		.भाग_width	= dw,				\
		.भाग_flags	= df,				\
		.gate_offset	= go,				\
		.gate_shअगरt	= gs,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा DIV_HALF(_id, cname, pname, f, o, s, w, df)			\
	अणु							\
		.id		= _id,				\
		.branch_type	= branch_half_भागider,		\
		.name		= cname,			\
		.parent_names	= (स्थिर अक्षर *[])अणु pname पूर्ण,	\
		.num_parents	= 1,				\
		.flags		= f,				\
		.muxभाग_offset	= o,				\
		.भाग_shअगरt	= s,				\
		.भाग_width	= w,				\
		.भाग_flags	= df,				\
		.gate_offset	= -1,				\
	पूर्ण

/* SGRF घड़ीs are only accessible from secure mode, so not controllable */
#घोषणा SGRF_GATE(_id, cname, pname)				\
		FACTOR(_id, cname, pname, 0, 1, 1)

काष्ठा rockchip_clk_provider *rockchip_clk_init(काष्ठा device_node *np,
			व्योम __iomem *base, अचिन्हित दीर्घ nr_clks);
व्योम rockchip_clk_of_add_provider(काष्ठा device_node *np,
				काष्ठा rockchip_clk_provider *ctx);
व्योम rockchip_clk_add_lookup(काष्ठा rockchip_clk_provider *ctx,
			     काष्ठा clk *clk, अचिन्हित पूर्णांक id);
व्योम rockchip_clk_रेजिस्टर_branches(काष्ठा rockchip_clk_provider *ctx,
				    काष्ठा rockchip_clk_branch *list,
				    अचिन्हित पूर्णांक nr_clk);
व्योम rockchip_clk_रेजिस्टर_plls(काष्ठा rockchip_clk_provider *ctx,
				काष्ठा rockchip_pll_घड़ी *pll_list,
				अचिन्हित पूर्णांक nr_pll, पूर्णांक grf_lock_offset);
व्योम rockchip_clk_रेजिस्टर_armclk(काष्ठा rockchip_clk_provider *ctx,
			अचिन्हित पूर्णांक lookup_id, स्थिर अक्षर *name,
			स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
			स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data,
			स्थिर काष्ठा rockchip_cpuclk_rate_table *rates,
			पूर्णांक nrates);
व्योम rockchip_clk_protect_critical(स्थिर अक्षर *स्थिर घड़ीs[], पूर्णांक nघड़ीs);
व्योम rockchip_रेजिस्टर_restart_notअगरier(काष्ठा rockchip_clk_provider *ctx,
					अचिन्हित पूर्णांक reg, व्योम (*cb)(व्योम));

#घोषणा ROCKCHIP_SOFTRST_HIWORD_MASK	BIT(0)

काष्ठा clk *rockchip_clk_रेजिस्टर_halfभाग(स्थिर अक्षर *name,
					  स्थिर अक्षर *स्थिर *parent_names,
					  u8 num_parents, व्योम __iomem *base,
					  पूर्णांक muxभाग_offset, u8 mux_shअगरt,
					  u8 mux_width, u8 mux_flags,
					  u8 भाग_shअगरt, u8 भाग_width,
					  u8 भाग_flags, पूर्णांक gate_offset,
					  u8 gate_shअगरt, u8 gate_flags,
					  अचिन्हित दीर्घ flags,
					  spinlock_t *lock);

#अगर_घोषित CONFIG_RESET_CONTROLLER
व्योम rockchip_रेजिस्टर_softrst(काष्ठा device_node *np,
			       अचिन्हित पूर्णांक num_regs,
			       व्योम __iomem *base, u8 flags);
#अन्यथा
अटल अंतरभूत व्योम rockchip_रेजिस्टर_softrst(काष्ठा device_node *np,
			       अचिन्हित पूर्णांक num_regs,
			       व्योम __iomem *base, u8 flags)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
