<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SAMA7G5 PMC code.
 *
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * Author: Claudiu Beznea <claudiu.beznea@microchip.com>
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

#घोषणा SAMA7G5_INIT_TABLE(_table, _count)		\
	करो अणु						\
		u8 _i;					\
		क्रम (_i = 0; _i < (_count); _i++)	\
			(_table)[_i] = _i;		\
	पूर्ण जबतक (0)

#घोषणा SAMA7G5_FILL_TABLE(_to, _from, _count)		\
	करो अणु						\
		u8 _i;					\
		क्रम (_i = 0; _i < (_count); _i++) अणु	\
			(_to)[_i] = (_from)[_i];	\
		पूर्ण					\
	पूर्ण जबतक (0)

अटल DEFINE_SPINLOCK(pmc_pll_lock);
अटल DEFINE_SPINLOCK(pmc_mck0_lock);
अटल DEFINE_SPINLOCK(pmc_mckX_lock);

/**
 * PLL घड़ीs identअगरiers
 * @PLL_ID_CPU:		CPU PLL identअगरier
 * @PLL_ID_SYS:		System PLL identअगरier
 * @PLL_ID_DDR:		DDR PLL identअगरier
 * @PLL_ID_IMG:		Image subप्रणाली PLL identअगरier
 * @PLL_ID_BAUD:	Baud PLL identअगरier
 * @PLL_ID_AUDIO:	Audio PLL identअगरier
 * @PLL_ID_ETH:		Ethernet PLL identअगरier
 */
क्रमागत pll_ids अणु
	PLL_ID_CPU,
	PLL_ID_SYS,
	PLL_ID_DDR,
	PLL_ID_IMG,
	PLL_ID_BAUD,
	PLL_ID_AUDIO,
	PLL_ID_ETH,
	PLL_ID_MAX,
पूर्ण;

/**
 * PLL type identअगरiers
 * @PLL_TYPE_FRAC:	fractional PLL identअगरier
 * @PLL_TYPE_DIV:	भागider PLL identअगरier
 */
क्रमागत pll_type अणु
	PLL_TYPE_FRAC,
	PLL_TYPE_DIV,
पूर्ण;

/* Layout क्रम fractional PLLs. */
अटल स्थिर काष्ठा clk_pll_layout pll_layout_frac = अणु
	.mul_mask	= GENMASK(31, 24),
	.frac_mask	= GENMASK(21, 0),
	.mul_shअगरt	= 24,
	.frac_shअगरt	= 0,
पूर्ण;

/* Layout क्रम DIVPMC भागiders. */
अटल स्थिर काष्ठा clk_pll_layout pll_layout_भागpmc = अणु
	.भाग_mask	= GENMASK(7, 0),
	.enभाग_mask	= BIT(29),
	.भाग_shअगरt	= 0,
	.enभाग_shअगरt	= 29,
पूर्ण;

/* Layout क्रम DIVIO भागiders. */
अटल स्थिर काष्ठा clk_pll_layout pll_layout_भागio = अणु
	.भाग_mask	= GENMASK(19, 12),
	.enभाग_mask	= BIT(30),
	.भाग_shअगरt	= 12,
	.enभाग_shअगरt	= 30,
पूर्ण;

/*
 * CPU PLL output range.
 * Notice: The upper limit has been setup to 1000000002 due to hardware
 * block which cannot output exactly 1GHz.
 */
अटल स्थिर काष्ठा clk_range cpu_pll_outमाला_दो[] = अणु
	अणु .min = 2343750, .max = 1000000002 पूर्ण,
पूर्ण;

/* PLL output range. */
अटल स्थिर काष्ठा clk_range pll_outमाला_दो[] = अणु
	अणु .min = 2343750, .max = 1200000000 पूर्ण,
पूर्ण;

/* CPU PLL अक्षरacteristics. */
अटल स्थिर काष्ठा clk_pll_अक्षरacteristics cpu_pll_अक्षरacteristics = अणु
	.input = अणु .min = 12000000, .max = 50000000 पूर्ण,
	.num_output = ARRAY_SIZE(cpu_pll_outमाला_दो),
	.output = cpu_pll_outमाला_दो,
पूर्ण;

/* PLL अक्षरacteristics. */
अटल स्थिर काष्ठा clk_pll_अक्षरacteristics pll_अक्षरacteristics = अणु
	.input = अणु .min = 12000000, .max = 50000000 पूर्ण,
	.num_output = ARRAY_SIZE(pll_outमाला_दो),
	.output = pll_outमाला_दो,
पूर्ण;

/**
 * PLL घड़ीs description
 * @n:		घड़ी name
 * @p:		घड़ी parent
 * @l:		घड़ी layout
 * @c:		घड़ी अक्षरacteristics
 * @t:		घड़ी type
 * @f:		घड़ी flags
 * @eid:	export index in sama7g5->chws[] array
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *n;
	स्थिर अक्षर *p;
	स्थिर काष्ठा clk_pll_layout *l;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *c;
	अचिन्हित दीर्घ f;
	u8 t;
	u8 eid;
पूर्ण sama7g5_plls[][PLL_ID_MAX] = अणु
	[PLL_ID_CPU] = अणु
		अणु .n = "cpupll_fracck",
		  .p = "mainck",
		  .l = &pll_layout_frac,
		  .c = &cpu_pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		   /*
		    * This feeds cpupll_भागpmcck which feeds CPU. It should
		    * not be disabled.
		    */
		  .f = CLK_IS_CRITICAL, पूर्ण,

		अणु .n = "cpupll_divpmcck",
		  .p = "cpupll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &cpu_pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		   /* This feeds CPU. It should not be disabled. */
		  .f = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT,
		  .eid = PMC_CPUPLL, पूर्ण,
	पूर्ण,

	[PLL_ID_SYS] = अणु
		अणु .n = "syspll_fracck",
		  .p = "mainck",
		  .l = &pll_layout_frac,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		   /*
		    * This feeds syspll_भागpmcck which may feed critical parts
		    * of the प्रणालीs like समयrs. Thereक्रमe it should not be
		    * disabled.
		    */
		  .f = CLK_IS_CRITICAL | CLK_SET_RATE_GATE, पूर्ण,

		अणु .n = "syspll_divpmcck",
		  .p = "syspll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		   /*
		    * This may feed critical parts of the प्रणालीs like समयrs.
		    * Thereक्रमe it should not be disabled.
		    */
		  .f = CLK_IS_CRITICAL | CLK_SET_RATE_GATE,
		  .eid = PMC_SYSPLL, पूर्ण,
	पूर्ण,

	[PLL_ID_DDR] = अणु
		अणु .n = "ddrpll_fracck",
		  .p = "mainck",
		  .l = &pll_layout_frac,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		   /*
		    * This feeds ddrpll_भागpmcck which feeds DDR. It should not
		    * be disabled.
		    */
		  .f = CLK_IS_CRITICAL | CLK_SET_RATE_GATE, पूर्ण,

		अणु .n = "ddrpll_divpmcck",
		  .p = "ddrpll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		   /* This feeds DDR. It should not be disabled. */
		  .f = CLK_IS_CRITICAL | CLK_SET_RATE_GATE, पूर्ण,
	पूर्ण,

	[PLL_ID_IMG] = अणु
		अणु .n = "imgpll_fracck",
		  .p = "mainck",
		  .l = &pll_layout_frac,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		  .f = CLK_SET_RATE_GATE, पूर्ण,

		अणु .n = "imgpll_divpmcck",
		  .p = "imgpll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		  .f = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		       CLK_SET_RATE_PARENT, पूर्ण,
	पूर्ण,

	[PLL_ID_BAUD] = अणु
		अणु .n = "baudpll_fracck",
		  .p = "mainck",
		  .l = &pll_layout_frac,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		  .f = CLK_SET_RATE_GATE, पूर्ण,

		अणु .n = "baudpll_divpmcck",
		  .p = "baudpll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		  .f = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		       CLK_SET_RATE_PARENT, पूर्ण,
	पूर्ण,

	[PLL_ID_AUDIO] = अणु
		अणु .n = "audiopll_fracck",
		  .p = "main_xtal",
		  .l = &pll_layout_frac,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		  .f = CLK_SET_RATE_GATE, पूर्ण,

		अणु .n = "audiopll_divpmcck",
		  .p = "audiopll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		  .f = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		       CLK_SET_RATE_PARENT,
		  .eid = PMC_AUDIOPMCPLL, पूर्ण,

		अणु .n = "audiopll_diviock",
		  .p = "audiopll_fracck",
		  .l = &pll_layout_भागio,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		  .f = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		       CLK_SET_RATE_PARENT,
		  .eid = PMC_AUDIOIOPLL, पूर्ण,
	पूर्ण,

	[PLL_ID_ETH] = अणु
		अणु .n = "ethpll_fracck",
		  .p = "main_xtal",
		  .l = &pll_layout_frac,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_FRAC,
		  .f = CLK_SET_RATE_GATE, पूर्ण,

		अणु .n = "ethpll_divpmcck",
		  .p = "ethpll_fracck",
		  .l = &pll_layout_भागpmc,
		  .c = &pll_अक्षरacteristics,
		  .t = PLL_TYPE_DIV,
		  .f = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		       CLK_SET_RATE_PARENT, पूर्ण,
	पूर्ण,
पूर्ण;

/**
 * Master घड़ी (MCK[1..4]) description
 * @n:			घड़ी name
 * @ep:			extra parents names array
 * @ep_chg_chg_id:	index in parents array that specअगरies the changeable
 *			parent
 * @ep_count:		extra parents count
 * @ep_mux_table:	mux table क्रम extra parents
 * @id:			घड़ी id
 * @c:			true अगर घड़ी is critical and cannot be disabled
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *n;
	स्थिर अक्षर *ep[4];
	पूर्णांक ep_chg_id;
	u8 ep_count;
	u8 ep_mux_table[4];
	u8 id;
	u8 c;
पूर्ण sama7g5_mckx[] = अणु
	अणु .n = "mck1",
	  .id = 1,
	  .ep = अणु "syspll_divpmcck", पूर्ण,
	  .ep_mux_table = अणु 5, पूर्ण,
	  .ep_count = 1,
	  .ep_chg_id = पूर्णांक_न्यून,
	  .c = 1, पूर्ण,

	अणु .n = "mck2",
	  .id = 2,
	  .ep = अणु "ddrpll_divpmcck", पूर्ण,
	  .ep_mux_table = अणु 6, पूर्ण,
	  .ep_count = 1,
	  .ep_chg_id = पूर्णांक_न्यून,
	  .c = 1, पूर्ण,

	अणु .n = "mck3",
	  .id = 3,
	  .ep = अणु "syspll_divpmcck", "ddrpll_divpmcck", "imgpll_divpmcck", पूर्ण,
	  .ep_mux_table = अणु 5, 6, 7, पूर्ण,
	  .ep_count = 3,
	  .ep_chg_id = 5, पूर्ण,

	अणु .n = "mck4",
	  .id = 4,
	  .ep = अणु "syspll_divpmcck", पूर्ण,
	  .ep_mux_table = अणु 5, पूर्ण,
	  .ep_count = 1,
	  .ep_chg_id = पूर्णांक_न्यून,
	  .c = 1, पूर्ण,
पूर्ण;

/**
 * System घड़ी description
 * @n:	घड़ी name
 * @p:	घड़ी parent name
 * @id: घड़ी id
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *n;
	स्थिर अक्षर *p;
	u8 id;
पूर्ण sama7g5_प्रणालीck[] = अणु
	अणु .n = "pck0",		.p = "prog0", .id = 8, पूर्ण,
	अणु .n = "pck1",		.p = "prog1", .id = 9, पूर्ण,
	अणु .n = "pck2",		.p = "prog2", .id = 10, पूर्ण,
	अणु .n = "pck3",		.p = "prog3", .id = 11, पूर्ण,
	अणु .n = "pck4",		.p = "prog4", .id = 12, पूर्ण,
	अणु .n = "pck5",		.p = "prog5", .id = 13, पूर्ण,
	अणु .n = "pck6",		.p = "prog6", .id = 14, पूर्ण,
	अणु .n = "pck7",		.p = "prog7", .id = 15, पूर्ण,
पूर्ण;

/* Mux table क्रम programmable घड़ीs. */
अटल u32 sama7g5_prog_mux_table[] = अणु 0, 1, 2, 5, 6, 7, 8, 9, 10, पूर्ण;

/**
 * Peripheral घड़ी description
 * @n:		घड़ी name
 * @p:		घड़ी parent name
 * @r:		घड़ी range values
 * @id:		घड़ी id
 * @chgp:	index in parent array of the changeable parent
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *n;
	स्थिर अक्षर *p;
	काष्ठा clk_range r;
	u8 chgp;
	u8 id;
पूर्ण sama7g5_periphck[] = अणु
	अणु .n = "pioA_clk",	.p = "mck0", .id = 11, पूर्ण,
	अणु .n = "sfr_clk",	.p = "mck1", .id = 19, पूर्ण,
	अणु .n = "hsmc_clk",	.p = "mck1", .id = 21, पूर्ण,
	अणु .n = "xdmac0_clk",	.p = "mck1", .id = 22, पूर्ण,
	अणु .n = "xdmac1_clk",	.p = "mck1", .id = 23, पूर्ण,
	अणु .n = "xdmac2_clk",	.p = "mck1", .id = 24, पूर्ण,
	अणु .n = "acc_clk",	.p = "mck1", .id = 25, पूर्ण,
	अणु .n = "aes_clk",	.p = "mck1", .id = 27, पूर्ण,
	अणु .n = "tzaesbasc_clk",	.p = "mck1", .id = 28, पूर्ण,
	अणु .n = "asrc_clk",	.p = "mck1", .id = 30, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "cpkcc_clk",	.p = "mck0", .id = 32, पूर्ण,
	अणु .n = "csi_clk",	.p = "mck3", .id = 33, .r = अणु .max = 266000000, पूर्ण, .chgp = 1, पूर्ण,
	अणु .n = "csi2dc_clk",	.p = "mck3", .id = 34, .r = अणु .max = 266000000, पूर्ण, .chgp = 1, पूर्ण,
	अणु .n = "eic_clk",	.p = "mck1", .id = 37, पूर्ण,
	अणु .n = "flex0_clk",	.p = "mck1", .id = 38, पूर्ण,
	अणु .n = "flex1_clk",	.p = "mck1", .id = 39, पूर्ण,
	अणु .n = "flex2_clk",	.p = "mck1", .id = 40, पूर्ण,
	अणु .n = "flex3_clk",	.p = "mck1", .id = 41, पूर्ण,
	अणु .n = "flex4_clk",	.p = "mck1", .id = 42, पूर्ण,
	अणु .n = "flex5_clk",	.p = "mck1", .id = 43, पूर्ण,
	अणु .n = "flex6_clk",	.p = "mck1", .id = 44, पूर्ण,
	अणु .n = "flex7_clk",	.p = "mck1", .id = 45, पूर्ण,
	अणु .n = "flex8_clk",	.p = "mck1", .id = 46, पूर्ण,
	अणु .n = "flex9_clk",	.p = "mck1", .id = 47, पूर्ण,
	अणु .n = "flex10_clk",	.p = "mck1", .id = 48, पूर्ण,
	अणु .n = "flex11_clk",	.p = "mck1", .id = 49, पूर्ण,
	अणु .n = "gmac0_clk",	.p = "mck1", .id = 51, पूर्ण,
	अणु .n = "gmac1_clk",	.p = "mck1", .id = 52, पूर्ण,
	अणु .n = "icm_clk",	.p = "mck1", .id = 55, पूर्ण,
	अणु .n = "isc_clk",	.p = "mck3", .id = 56, .r = अणु .max = 266000000, पूर्ण, .chgp = 1, पूर्ण,
	अणु .n = "i2smcc0_clk",	.p = "mck1", .id = 57, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "i2smcc1_clk",	.p = "mck1", .id = 58, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "matrix_clk",	.p = "mck1", .id = 60, पूर्ण,
	अणु .n = "mcan0_clk",	.p = "mck1", .id = 61, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "mcan1_clk",	.p = "mck1", .id = 62, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "mcan2_clk",	.p = "mck1", .id = 63, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "mcan3_clk",	.p = "mck1", .id = 64, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "mcan4_clk",	.p = "mck1", .id = 65, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "mcan5_clk",	.p = "mck1", .id = 66, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "pdmc0_clk",	.p = "mck1", .id = 68, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "pdmc1_clk",	.p = "mck1", .id = 69, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "pit64b0_clk",	.p = "mck1", .id = 70, पूर्ण,
	अणु .n = "pit64b1_clk",	.p = "mck1", .id = 71, पूर्ण,
	अणु .n = "pit64b2_clk",	.p = "mck1", .id = 72, पूर्ण,
	अणु .n = "pit64b3_clk",	.p = "mck1", .id = 73, पूर्ण,
	अणु .n = "pit64b4_clk",	.p = "mck1", .id = 74, पूर्ण,
	अणु .n = "pit64b5_clk",	.p = "mck1", .id = 75, पूर्ण,
	अणु .n = "pwm_clk",	.p = "mck1", .id = 77, पूर्ण,
	अणु .n = "qspi0_clk",	.p = "mck1", .id = 78, पूर्ण,
	अणु .n = "qspi1_clk",	.p = "mck1", .id = 79, पूर्ण,
	अणु .n = "sdmmc0_clk",	.p = "mck1", .id = 80, पूर्ण,
	अणु .n = "sdmmc1_clk",	.p = "mck1", .id = 81, पूर्ण,
	अणु .n = "sdmmc2_clk",	.p = "mck1", .id = 82, पूर्ण,
	अणु .n = "sha_clk",	.p = "mck1", .id = 83, पूर्ण,
	अणु .n = "spdifrx_clk",	.p = "mck1", .id = 84, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "spdiftx_clk",	.p = "mck1", .id = 85, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "ssc0_clk",	.p = "mck1", .id = 86, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "ssc1_clk",	.p = "mck1", .id = 87, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcb0_ch0_clk",	.p = "mck1", .id = 88, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcb0_ch1_clk",	.p = "mck1", .id = 89, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcb0_ch2_clk",	.p = "mck1", .id = 90, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcb1_ch0_clk",	.p = "mck1", .id = 91, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcb1_ch1_clk",	.p = "mck1", .id = 92, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcb1_ch2_clk",	.p = "mck1", .id = 93, .r = अणु .max = 200000000, पूर्ण, पूर्ण,
	अणु .n = "tcpca_clk",	.p = "mck1", .id = 94, पूर्ण,
	अणु .n = "tcpcb_clk",	.p = "mck1", .id = 95, पूर्ण,
	अणु .n = "tdes_clk",	.p = "mck1", .id = 96, पूर्ण,
	अणु .n = "trng_clk",	.p = "mck1", .id = 97, पूर्ण,
	अणु .n = "udphsa_clk",	.p = "mck1", .id = 104, पूर्ण,
	अणु .n = "udphsb_clk",	.p = "mck1", .id = 105, पूर्ण,
	अणु .n = "uhphs_clk",	.p = "mck1", .id = 106, पूर्ण,
पूर्ण;

/**
 * Generic घड़ी description
 * @n:			घड़ी name
 * @pp:			PLL parents
 * @pp_mux_table:	PLL parents mux table
 * @r:			घड़ी output range
 * @pp_chg_id:		id in parent array of changeable PLL parent
 * @pp_count:		PLL parents count
 * @id:			घड़ी id
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *n;
	स्थिर अक्षर *pp[8];
	स्थिर अक्षर pp_mux_table[8];
	काष्ठा clk_range r;
	पूर्णांक pp_chg_id;
	u8 pp_count;
	u8 id;
पूर्ण sama7g5_gck[] = अणु
	अणु .n  = "adc_gclk",
	  .id = 26,
	  .r = अणु .max = 100000000, पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "audiopll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 9, पूर्ण,
	  .pp_count = 3,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "asrc_gclk",
	  .id = 30,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "audiopll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 9, पूर्ण,
	  .pp_count = 1,
	  .pp_chg_id = 3, पूर्ण,

	अणु .n  = "csi_gclk",
	  .id = 33,
	  .r = अणु .max = 27000000  पूर्ण,
	  .pp = अणु "ddrpll_divpmcck", "imgpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 6, 7, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex0_gclk",
	  .id = 38,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex1_gclk",
	  .id = 39,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex2_gclk",
	  .id = 40,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex3_gclk",
	  .id = 41,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex4_gclk",
	  .id = 42,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex5_gclk",
	  .id = 43,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex6_gclk",
	  .id = 44,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex7_gclk",
	  .id = 45,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex8_gclk",
	  .id = 46,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex9_gclk",
	  .id = 47,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex10_gclk",
	  .id = 48,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "flex11_gclk",
	  .id = 49,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "gmac0_gclk",
	  .id = 51,
	  .r = अणु .max = 125000000 पूर्ण,
	  .pp = अणु "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 10, पूर्ण,
	  .pp_count = 1,
	  .pp_chg_id = 3, पूर्ण,

	अणु .n  = "gmac1_gclk",
	  .id = 52,
	  .r = अणु .max = 50000000  पूर्ण,
	  .pp = अणु "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 10, पूर्ण,
	  .pp_count = 1,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "gmac0_tsu_gclk",
	  .id = 53,
	  .r = अणु .max = 300000000 पूर्ण,
	  .pp = अणु "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 9, 10, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "gmac1_tsu_gclk",
	  .id = 54,
	  .r = अणु .max = 300000000 पूर्ण,
	  .pp = अणु "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 9, 10, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "i2smcc0_gclk",
	  .id = 57,
	  .r = अणु .max = 100000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "audiopll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 9, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n  = "i2smcc1_gclk",
	  .id = 58,
	  .r = अणु .max = 100000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "audiopll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 9, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n  = "mcan0_gclk",
	  .id = 61,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "mcan1_gclk",
	  .id = 62,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "mcan2_gclk",
	  .id = 63,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "mcan3_gclk",
	  .id = 64,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "mcan4_gclk",
	  .id = 65,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "mcan5_gclk",
	  .id = 66,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pdmc0_gclk",
	  .id = 68,
	  .r = अणु .max = 50000000  पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pdmc1_gclk",
	  .id = 69,
	  .r = अणु .max = 50000000, पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pit64b0_gclk",
	  .id = 70,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pit64b1_gclk",
	  .id = 71,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pit64b2_gclk",
	  .id = 72,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pit64b3_gclk",
	  .id = 73,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pit64b4_gclk",
	  .id = 74,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "pit64b5_gclk",
	  .id = 75,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "qspi0_gclk",
	  .id = 78,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "qspi1_gclk",
	  .id = 79,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "sdmmc0_gclk",
	  .id = 80,
	  .r = अणु .max = 208000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n  = "sdmmc1_gclk",
	  .id = 81,
	  .r = अणु .max = 208000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n  = "sdmmc2_gclk",
	  .id = 82,
	  .r = अणु .max = 208000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "baudpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 8, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n  = "spdifrx_gclk",
	  .id = 84,
	  .r = अणु .max = 150000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "audiopll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 9, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n = "spdiftx_gclk",
	  .id = 85,
	  .r = अणु .max = 25000000  पूर्ण,
	  .pp = अणु "syspll_divpmcck", "audiopll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 9, पूर्ण,
	  .pp_count = 2,
	  .pp_chg_id = 4, पूर्ण,

	अणु .n  = "tcb0_ch0_gclk",
	  .id = 88,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "tcb1_ch0_gclk",
	  .id = 91,
	  .r = अणु .max = 200000000 पूर्ण,
	  .pp = अणु "syspll_divpmcck", "imgpll_divpmcck", "baudpll_divpmcck",
		  "audiopll_divpmcck", "ethpll_divpmcck", पूर्ण,
	  .pp_mux_table = अणु 5, 7, 8, 9, 10, पूर्ण,
	  .pp_count = 5,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "tcpca_gclk",
	  .id = 94,
	  .r = अणु .max = 32768, पूर्ण,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,

	अणु .n  = "tcpcb_gclk",
	  .id = 95,
	  .r = अणु .max = 32768, पूर्ण,
	  .pp_chg_id = पूर्णांक_न्यून, पूर्ण,
पूर्ण;

/* MCK0 अक्षरacteristics. */
अटल स्थिर काष्ठा clk_master_अक्षरacteristics mck0_अक्षरacteristics = अणु
	.output = अणु .min = 50000000, .max = 200000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 3, 5 पूर्ण,
	.have_भाग3_pres = 1,
पूर्ण;

/* MCK0 layout. */
अटल स्थिर काष्ठा clk_master_layout mck0_layout = अणु
	.mask = 0x773,
	.pres_shअगरt = 4,
	.offset = 0x28,
पूर्ण;

/* Programmable घड़ी layout. */
अटल स्थिर काष्ठा clk_programmable_layout programmable_layout = अणु
	.pres_mask = 0xff,
	.pres_shअगरt = 8,
	.css_mask = 0x1f,
	.have_slck_mck = 0,
	.is_pres_direct = 1,
पूर्ण;

/* Peripheral घड़ी layout. */
अटल स्थिर काष्ठा clk_pcr_layout sama7g5_pcr_layout = अणु
	.offset = 0x88,
	.cmd = BIT(31),
	.gckcss_mask = GENMASK(12, 8),
	.pid_mask = GENMASK(6, 0),
पूर्ण;

अटल व्योम __init sama7g5_pmc_setup(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *td_slck_name, *md_slck_name, *मुख्यxtal_name;
	काष्ठा pmc_data *sama7g5_pmc;
	स्थिर अक्षर *parent_names[10];
	व्योम **alloc_mem = शून्य;
	पूर्णांक alloc_mem_size = 0;
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *hw;
	bool bypass;
	पूर्णांक i, j;

	i = of_property_match_string(np, "clock-names", "td_slck");
	अगर (i < 0)
		वापस;

	td_slck_name = of_clk_get_parent_name(np, i);

	i = of_property_match_string(np, "clock-names", "md_slck");
	अगर (i < 0)
		वापस;

	md_slck_name = of_clk_get_parent_name(np, i);

	i = of_property_match_string(np, "clock-names", "main_xtal");
	अगर (i < 0)
		वापस;

	मुख्यxtal_name = of_clk_get_parent_name(np, i);

	regmap = device_node_to_regmap(np);
	अगर (IS_ERR(regmap))
		वापस;

	sama7g5_pmc = pmc_data_allocate(PMC_CPU + 1,
					nck(sama7g5_प्रणालीck),
					nck(sama7g5_periphck),
					nck(sama7g5_gck), 8);
	अगर (!sama7g5_pmc)
		वापस;

	alloc_mem = kदो_स्मृति(माप(व्योम *) *
			    (ARRAY_SIZE(sama7g5_mckx) + ARRAY_SIZE(sama7g5_gck)),
			    GFP_KERNEL);
	अगर (!alloc_mem)
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_मुख्य_rc_osc(regmap, "main_rc_osc", 12000000,
					   50000000);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");

	hw = at91_clk_रेजिस्टर_मुख्य_osc(regmap, "main_osc", मुख्यxtal_name,
					bypass);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = "main_rc_osc";
	parent_names[1] = "main_osc";
	hw = at91_clk_रेजिस्टर_sam9x5_मुख्य(regmap, "mainck", parent_names, 2);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama7g5_pmc->chws[PMC_MAIN] = hw;

	क्रम (i = 0; i < PLL_ID_MAX; i++) अणु
		क्रम (j = 0; j < 3; j++) अणु
			काष्ठा clk_hw *parent_hw;

			अगर (!sama7g5_plls[i][j].n)
				जारी;

			चयन (sama7g5_plls[i][j].t) अणु
			हाल PLL_TYPE_FRAC:
				अगर (!म_भेद(sama7g5_plls[i][j].p, "mainck"))
					parent_hw = sama7g5_pmc->chws[PMC_MAIN];
				अन्यथा
					parent_hw = __clk_get_hw(of_clk_get_by_name(np,
						sama7g5_plls[i][j].p));

				hw = sam9x60_clk_रेजिस्टर_frac_pll(regmap,
					&pmc_pll_lock, sama7g5_plls[i][j].n,
					sama7g5_plls[i][j].p, parent_hw, i,
					sama7g5_plls[i][j].c,
					sama7g5_plls[i][j].l,
					sama7g5_plls[i][j].f);
				अवरोध;

			हाल PLL_TYPE_DIV:
				hw = sam9x60_clk_रेजिस्टर_भाग_pll(regmap,
					&pmc_pll_lock, sama7g5_plls[i][j].n,
					sama7g5_plls[i][j].p, i,
					sama7g5_plls[i][j].c,
					sama7g5_plls[i][j].l,
					sama7g5_plls[i][j].f);
				अवरोध;

			शेष:
				जारी;
			पूर्ण

			अगर (IS_ERR(hw))
				जाओ err_मुक्त;

			अगर (sama7g5_plls[i][j].eid)
				sama7g5_pmc->chws[sama7g5_plls[i][j].eid] = hw;
		पूर्ण
	पूर्ण

	parent_names[0] = "cpupll_divpmcck";
	hw = at91_clk_रेजिस्टर_master_pres(regmap, "cpuck", 1, parent_names,
					   &mck0_layout, &mck0_अक्षरacteristics,
					   &pmc_mck0_lock,
					   CLK_SET_RATE_PARENT, 0);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama7g5_pmc->chws[PMC_CPU] = hw;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, "mck0", "cpuck",
					  &mck0_layout, &mck0_अक्षरacteristics,
					  &pmc_mck0_lock, 0);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama7g5_pmc->chws[PMC_MCK] = hw;

	parent_names[0] = md_slck_name;
	parent_names[1] = td_slck_name;
	parent_names[2] = "mainck";
	क्रम (i = 0; i < ARRAY_SIZE(sama7g5_mckx); i++) अणु
		u8 num_parents = 3 + sama7g5_mckx[i].ep_count;
		u32 *mux_table;

		mux_table = kदो_स्मृति_array(num_parents, माप(*mux_table),
					  GFP_KERNEL);
		अगर (!mux_table)
			जाओ err_मुक्त;

		SAMA7G5_INIT_TABLE(mux_table, 3);
		SAMA7G5_FILL_TABLE(&mux_table[3], sama7g5_mckx[i].ep_mux_table,
				   sama7g5_mckx[i].ep_count);
		SAMA7G5_FILL_TABLE(&parent_names[3], sama7g5_mckx[i].ep,
				   sama7g5_mckx[i].ep_count);

		hw = at91_clk_sama7g5_रेजिस्टर_master(regmap, sama7g5_mckx[i].n,
				   num_parents, parent_names, mux_table,
				   &pmc_mckX_lock, sama7g5_mckx[i].id,
				   sama7g5_mckx[i].c,
				   sama7g5_mckx[i].ep_chg_id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		alloc_mem[alloc_mem_size++] = mux_table;
	पूर्ण

	hw = at91_clk_sama7g5_रेजिस्टर_uपंचांगi(regmap, "utmick", "main_xtal");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama7g5_pmc->chws[PMC_UTMI] = hw;

	parent_names[0] = md_slck_name;
	parent_names[1] = td_slck_name;
	parent_names[2] = "mainck";
	parent_names[3] = "syspll_divpmcck";
	parent_names[4] = "ddrpll_divpmcck";
	parent_names[5] = "imgpll_divpmcck";
	parent_names[6] = "baudpll_divpmcck";
	parent_names[7] = "audiopll_divpmcck";
	parent_names[8] = "ethpll_divpmcck";
	क्रम (i = 0; i < 8; i++) अणु
		अक्षर name[6];

		snम_लिखो(name, माप(name), "prog%d", i);

		hw = at91_clk_रेजिस्टर_programmable(regmap, name, parent_names,
						    9, i,
						    &programmable_layout,
						    sama7g5_prog_mux_table);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama7g5_pmc->pchws[i] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sama7g5_प्रणालीck); i++) अणु
		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, sama7g5_प्रणालीck[i].n,
					      sama7g5_प्रणालीck[i].p,
					      sama7g5_प्रणालीck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama7g5_pmc->shws[sama7g5_प्रणालीck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sama7g5_periphck); i++) अणु
		hw = at91_clk_रेजिस्टर_sam9x5_peripheral(regmap, &pmc_pcr_lock,
						&sama7g5_pcr_layout,
						sama7g5_periphck[i].n,
						sama7g5_periphck[i].p,
						sama7g5_periphck[i].id,
						&sama7g5_periphck[i].r,
						sama7g5_periphck[i].chgp ? 0 :
						पूर्णांक_न्यून);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama7g5_pmc->phws[sama7g5_periphck[i].id] = hw;
	पूर्ण

	parent_names[0] = md_slck_name;
	parent_names[1] = td_slck_name;
	parent_names[2] = "mainck";
	क्रम (i = 0; i < ARRAY_SIZE(sama7g5_gck); i++) अणु
		u8 num_parents = 3 + sama7g5_gck[i].pp_count;
		u32 *mux_table;

		mux_table = kदो_स्मृति_array(num_parents, माप(*mux_table),
					  GFP_KERNEL);
		अगर (!mux_table)
			जाओ err_मुक्त;

		SAMA7G5_INIT_TABLE(mux_table, 3);
		SAMA7G5_FILL_TABLE(&mux_table[3], sama7g5_gck[i].pp_mux_table,
				   sama7g5_gck[i].pp_count);
		SAMA7G5_FILL_TABLE(&parent_names[3], sama7g5_gck[i].pp,
				   sama7g5_gck[i].pp_count);

		hw = at91_clk_रेजिस्टर_generated(regmap, &pmc_pcr_lock,
						 &sama7g5_pcr_layout,
						 sama7g5_gck[i].n,
						 parent_names, mux_table,
						 num_parents,
						 sama7g5_gck[i].id,
						 &sama7g5_gck[i].r,
						 sama7g5_gck[i].pp_chg_id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama7g5_pmc->ghws[sama7g5_gck[i].id] = hw;
		alloc_mem[alloc_mem_size++] = mux_table;
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_pmc_get, sama7g5_pmc);

	वापस;

err_मुक्त:
	अगर (alloc_mem) अणु
		क्रम (i = 0; i < alloc_mem_size; i++)
			kमुक्त(alloc_mem[i]);
		kमुक्त(alloc_mem);
	पूर्ण

	kमुक्त(sama7g5_pmc);
पूर्ण

/* Some clks are used क्रम a घड़ीsource */
CLK_OF_DECLARE(sama7g5_pmc, "microchip,sama7g5-pmc", sama7g5_pmc_setup);
