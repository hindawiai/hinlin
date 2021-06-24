<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Emilio Lथकpez
 *
 * Emilio Lथकpez <emilio@elopez.com.ar>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/log2.h>

#समावेश "clk-factors.h"

अटल DEFINE_SPINLOCK(clk_lock);

/* Maximum number of parents our घड़ीs have */
#घोषणा SUNXI_MAX_PARENTS	5

/*
 * sun4i_get_pll1_factors() - calculates n, k, m, p factors क्रम PLL1
 * PLL1 rate is calculated as follows
 * rate = (parent_rate * n * (k + 1) >> p) / (m + 1);
 * parent_rate is always 24Mhz
 */

अटल व्योम sun4i_get_pll1_factors(काष्ठा factors_request *req)
अणु
	u8 भाग;

	/* Normalize value to a 6M multiple */
	भाग = req->rate / 6000000;
	req->rate = 6000000 * भाग;

	/* m is always zero क्रम pll1 */
	req->m = 0;

	/* k is 1 only on these हालs */
	अगर (req->rate >= 768000000 || req->rate == 42000000 ||
			req->rate == 54000000)
		req->k = 1;
	अन्यथा
		req->k = 0;

	/* p will be 3 क्रम भागs under 10 */
	अगर (भाग < 10)
		req->p = 3;

	/* p will be 2 क्रम भागs between 10 - 20 and odd भागs under 32 */
	अन्यथा अगर (भाग < 20 || (भाग < 32 && (भाग & 1)))
		req->p = 2;

	/* p will be 1 क्रम even भागs under 32, भागs under 40 and odd pairs
	 * of भागs between 40-62 */
	अन्यथा अगर (भाग < 40 || (भाग < 64 && (भाग & 2)))
		req->p = 1;

	/* any other entries have p = 0 */
	अन्यथा
		req->p = 0;

	/* calculate a suitable n based on k and p */
	भाग <<= req->p;
	भाग /= (req->k + 1);
	req->n = भाग / 4;
पूर्ण

/*
 * sun6i_a31_get_pll1_factors() - calculates n, k and m factors क्रम PLL1
 * PLL1 rate is calculated as follows
 * rate = parent_rate * (n + 1) * (k + 1) / (m + 1);
 * parent_rate should always be 24MHz
 */
अटल व्योम sun6i_a31_get_pll1_factors(काष्ठा factors_request *req)
अणु
	/*
	 * We can operate only on MHz, this will make our lअगरe easier
	 * later.
	 */
	u32 freq_mhz = req->rate / 1000000;
	u32 parent_freq_mhz = req->parent_rate / 1000000;

	/*
	 * Round करोwn the frequency to the बंदst multiple of either
	 * 6 or 16
	 */
	u32 round_freq_6 = roundकरोwn(freq_mhz, 6);
	u32 round_freq_16 = round_करोwn(freq_mhz, 16);

	अगर (round_freq_6 > round_freq_16)
		freq_mhz = round_freq_6;
	अन्यथा
		freq_mhz = round_freq_16;

	req->rate = freq_mhz * 1000000;

	/* If the frequency is a multiple of 32 MHz, k is always 3 */
	अगर (!(freq_mhz % 32))
		req->k = 3;
	/* If the frequency is a multiple of 9 MHz, k is always 2 */
	अन्यथा अगर (!(freq_mhz % 9))
		req->k = 2;
	/* If the frequency is a multiple of 8 MHz, k is always 1 */
	अन्यथा अगर (!(freq_mhz % 8))
		req->k = 1;
	/* Otherwise, we करोn't use the k factor */
	अन्यथा
		req->k = 0;

	/*
	 * If the frequency is a multiple of 2 but not a multiple of
	 * 3, m is 3. This is the first समय we use 6 here, yet we
	 * will use it on several other places.
	 * We use this number because it's the lowest frequency we can
	 * generate (with n = 0, k = 0, m = 3), so every other frequency
	 * somehow relates to this frequency.
	 */
	अगर ((freq_mhz % 6) == 2 || (freq_mhz % 6) == 4)
		req->m = 2;
	/*
	 * If the frequency is a multiple of 6MHz, but the factor is
	 * odd, m will be 3
	 */
	अन्यथा अगर ((freq_mhz / 6) & 1)
		req->m = 3;
	/* Otherwise, we end up with m = 1 */
	अन्यथा
		req->m = 1;

	/* Calculate n thanks to the above factors we alपढ़ोy got */
	req->n = freq_mhz * (req->m + 1) / ((req->k + 1) * parent_freq_mhz)
		 - 1;

	/*
	 * If n end up being outbound, and that we can still decrease
	 * m, करो it.
	 */
	अगर ((req->n + 1) > 31 && (req->m + 1) > 1) अणु
		req->n = (req->n + 1) / 2 - 1;
		req->m = (req->m + 1) / 2 - 1;
	पूर्ण
पूर्ण

/*
 * sun8i_a23_get_pll1_factors() - calculates n, k, m, p factors क्रम PLL1
 * PLL1 rate is calculated as follows
 * rate = (parent_rate * (n + 1) * (k + 1) >> p) / (m + 1);
 * parent_rate is always 24Mhz
 */

अटल व्योम sun8i_a23_get_pll1_factors(काष्ठा factors_request *req)
अणु
	u8 भाग;

	/* Normalize value to a 6M multiple */
	भाग = req->rate / 6000000;
	req->rate = 6000000 * भाग;

	/* m is always zero क्रम pll1 */
	req->m = 0;

	/* k is 1 only on these हालs */
	अगर (req->rate >= 768000000 || req->rate == 42000000 ||
			req->rate == 54000000)
		req->k = 1;
	अन्यथा
		req->k = 0;

	/* p will be 2 क्रम भागs under 20 and odd भागs under 32 */
	अगर (भाग < 20 || (भाग < 32 && (भाग & 1)))
		req->p = 2;

	/* p will be 1 क्रम even भागs under 32, भागs under 40 and odd pairs
	 * of भागs between 40-62 */
	अन्यथा अगर (भाग < 40 || (भाग < 64 && (भाग & 2)))
		req->p = 1;

	/* any other entries have p = 0 */
	अन्यथा
		req->p = 0;

	/* calculate a suitable n based on k and p */
	भाग <<= req->p;
	भाग /= (req->k + 1);
	req->n = भाग / 4 - 1;
पूर्ण

/*
 * sun4i_get_pll5_factors() - calculates n, k factors क्रम PLL5
 * PLL5 rate is calculated as follows
 * rate = parent_rate * n * (k + 1)
 * parent_rate is always 24Mhz
 */

अटल व्योम sun4i_get_pll5_factors(काष्ठा factors_request *req)
अणु
	u8 भाग;

	/* Normalize value to a parent_rate multiple (24M) */
	भाग = req->rate / req->parent_rate;
	req->rate = req->parent_rate * भाग;

	अगर (भाग < 31)
		req->k = 0;
	अन्यथा अगर (भाग / 2 < 31)
		req->k = 1;
	अन्यथा अगर (भाग / 3 < 31)
		req->k = 2;
	अन्यथा
		req->k = 3;

	req->n = DIV_ROUND_UP(भाग, (req->k + 1));
पूर्ण

/*
 * sun6i_a31_get_pll6_factors() - calculates n, k factors क्रम A31 PLL6x2
 * PLL6x2 rate is calculated as follows
 * rate = parent_rate * (n + 1) * (k + 1)
 * parent_rate is always 24Mhz
 */

अटल व्योम sun6i_a31_get_pll6_factors(काष्ठा factors_request *req)
अणु
	u8 भाग;

	/* Normalize value to a parent_rate multiple (24M) */
	भाग = req->rate / req->parent_rate;
	req->rate = req->parent_rate * भाग;

	req->k = भाग / 32;
	अगर (req->k > 3)
		req->k = 3;

	req->n = DIV_ROUND_UP(भाग, (req->k + 1)) - 1;
पूर्ण

/*
 * sun5i_a13_get_ahb_factors() - calculates m, p factors क्रम AHB
 * AHB rate is calculated as follows
 * rate = parent_rate >> p
 */

अटल व्योम sun5i_a13_get_ahb_factors(काष्ठा factors_request *req)
अणु
	u32 भाग;

	/* भागide only */
	अगर (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	/*
	 * user manual says valid speed is 8k ~ 276M, but tests show it
	 * can work at speeds up to 300M, just after reparenting to pll6
	 */
	अगर (req->rate < 8000)
		req->rate = 8000;
	अगर (req->rate > 300000000)
		req->rate = 300000000;

	भाग = order_base_2(DIV_ROUND_UP(req->parent_rate, req->rate));

	/* p = 0 ~ 3 */
	अगर (भाग > 3)
		भाग = 3;

	req->rate = req->parent_rate >> भाग;

	req->p = भाग;
पूर्ण

#घोषणा SUN6I_AHB1_PARENT_PLL6	3

/*
 * sun6i_a31_get_ahb_factors() - calculates m, p factors क्रम AHB
 * AHB rate is calculated as follows
 * rate = parent_rate >> p
 *
 * अगर parent is pll6, then
 * parent_rate = pll6 rate / (m + 1)
 */

अटल व्योम sun6i_get_ahb1_factors(काष्ठा factors_request *req)
अणु
	u8 भाग, calcp, calcm = 1;

	/*
	 * घड़ी can only भागide, so we will never be able to achieve
	 * frequencies higher than the parent frequency
	 */
	अगर (req->parent_rate && req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* calculate pre-भागider अगर parent is pll6 */
	अगर (req->parent_index == SUN6I_AHB1_PARENT_PLL6) अणु
		अगर (भाग < 4)
			calcp = 0;
		अन्यथा अगर (भाग / 2 < 4)
			calcp = 1;
		अन्यथा अगर (भाग / 4 < 4)
			calcp = 2;
		अन्यथा
			calcp = 3;

		calcm = DIV_ROUND_UP(भाग, 1 << calcp);
	पूर्ण अन्यथा अणु
		calcp = __roundup_घात_of_two(भाग);
		calcp = calcp > 3 ? 3 : calcp;
	पूर्ण

	req->rate = (req->parent_rate / calcm) >> calcp;
	req->p = calcp;
	req->m = calcm - 1;
पूर्ण

/*
 * sun6i_ahb1_recalc() - calculates AHB घड़ी rate from m, p factors and
 *			 parent index
 */
अटल व्योम sun6i_ahb1_recalc(काष्ठा factors_request *req)
अणु
	req->rate = req->parent_rate;

	/* apply pre-भागider first अगर parent is pll6 */
	अगर (req->parent_index == SUN6I_AHB1_PARENT_PLL6)
		req->rate /= req->m + 1;

	/* clk भागider */
	req->rate >>= req->p;
पूर्ण

/*
 * sun4i_get_apb1_factors() - calculates m, p factors क्रम APB1
 * APB1 rate is calculated as follows
 * rate = (parent_rate >> p) / (m + 1);
 */

अटल व्योम sun4i_get_apb1_factors(काष्ठा factors_request *req)
अणु
	u8 calcm, calcp;
	पूर्णांक भाग;

	अगर (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* Invalid rate! */
	अगर (भाग > 32)
		वापस;

	अगर (भाग <= 4)
		calcp = 0;
	अन्यथा अगर (भाग <= 8)
		calcp = 1;
	अन्यथा अगर (भाग <= 16)
		calcp = 2;
	अन्यथा
		calcp = 3;

	calcm = (भाग >> calcp) - 1;

	req->rate = (req->parent_rate >> calcp) / (calcm + 1);
	req->m = calcm;
	req->p = calcp;
पूर्ण




/*
 * sun7i_a20_get_out_factors() - calculates m, p factors क्रम CLK_OUT_A/B
 * CLK_OUT rate is calculated as follows
 * rate = (parent_rate >> p) / (m + 1);
 */

अटल व्योम sun7i_a20_get_out_factors(काष्ठा factors_request *req)
अणु
	u8 भाग, calcm, calcp;

	/* These घड़ीs can only भागide, so we will never be able to achieve
	 * frequencies higher than the parent frequency */
	अगर (req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	अगर (भाग < 32)
		calcp = 0;
	अन्यथा अगर (भाग / 2 < 32)
		calcp = 1;
	अन्यथा अगर (भाग / 4 < 32)
		calcp = 2;
	अन्यथा
		calcp = 3;

	calcm = DIV_ROUND_UP(भाग, 1 << calcp);

	req->rate = (req->parent_rate >> calcp) / calcm;
	req->m = calcm - 1;
	req->p = calcp;
पूर्ण

/*
 * sunxi_factors_clk_setup() - Setup function क्रम factor घड़ीs
 */

अटल स्थिर काष्ठा clk_factors_config sun4i_pll1_config = अणु
	.nshअगरt = 8,
	.nwidth = 5,
	.kshअगरt = 4,
	.kwidth = 2,
	.mshअगरt = 0,
	.mwidth = 2,
	.pshअगरt = 16,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun6i_a31_pll1_config = अणु
	.nshअगरt	= 8,
	.nwidth = 5,
	.kshअगरt = 4,
	.kwidth = 2,
	.mshअगरt = 0,
	.mwidth = 2,
	.n_start = 1,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun8i_a23_pll1_config = अणु
	.nshअगरt = 8,
	.nwidth = 5,
	.kshअगरt = 4,
	.kwidth = 2,
	.mshअगरt = 0,
	.mwidth = 2,
	.pshअगरt = 16,
	.pwidth = 2,
	.n_start = 1,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun4i_pll5_config = अणु
	.nshअगरt = 8,
	.nwidth = 5,
	.kshअगरt = 4,
	.kwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun6i_a31_pll6_config = अणु
	.nshअगरt	= 8,
	.nwidth = 5,
	.kshअगरt = 4,
	.kwidth = 2,
	.n_start = 1,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun5i_a13_ahb_config = अणु
	.pshअगरt = 4,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun6i_ahb1_config = अणु
	.mshअगरt = 6,
	.mwidth = 2,
	.pshअगरt = 4,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा clk_factors_config sun4i_apb1_config = अणु
	.mshअगरt = 0,
	.mwidth = 5,
	.pshअगरt = 16,
	.pwidth = 2,
पूर्ण;

/* user manual says "n" but it's really "p" */
अटल स्थिर काष्ठा clk_factors_config sun7i_a20_out_config = अणु
	.mshअगरt = 8,
	.mwidth = 5,
	.pshअगरt = 20,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun4i_pll1_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun4i_pll1_config,
	.getter = sun4i_get_pll1_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun6i_a31_pll1_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun6i_a31_pll1_config,
	.getter = sun6i_a31_get_pll1_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun8i_a23_pll1_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun8i_a23_pll1_config,
	.getter = sun8i_a23_get_pll1_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun7i_a20_pll4_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun4i_pll5_config,
	.getter = sun4i_get_pll5_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun4i_pll5_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun4i_pll5_config,
	.getter = sun4i_get_pll5_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun6i_a31_pll6_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun6i_a31_pll6_config,
	.getter = sun6i_a31_get_pll6_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun5i_a13_ahb_data __initस्थिर = अणु
	.mux = 6,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun5i_a13_ahb_config,
	.getter = sun5i_a13_get_ahb_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun6i_ahb1_data __initस्थिर = अणु
	.mux = 12,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun6i_ahb1_config,
	.getter = sun6i_get_ahb1_factors,
	.recalc = sun6i_ahb1_recalc,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun4i_apb1_data __initस्थिर = अणु
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun4i_apb1_config,
	.getter = sun4i_get_apb1_factors,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun7i_a20_out_data __initस्थिर = अणु
	.enable = 31,
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun7i_a20_out_config,
	.getter = sun7i_a20_get_out_factors,
पूर्ण;

अटल काष्ठा clk * __init sunxi_factors_clk_setup(काष्ठा device_node *node,
						   स्थिर काष्ठा factors_data *data)
अणु
	व्योम __iomem *reg;

	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("Could not get registers for factors-clk: %pOFn\n",
		       node);
		वापस शून्य;
	पूर्ण

	वापस sunxi_factors_रेजिस्टर(node, data, &clk_lock, reg);
पूर्ण

अटल व्योम __init sun4i_pll1_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun4i_pll1_data);
पूर्ण
CLK_OF_DECLARE(sun4i_pll1, "allwinner,sun4i-a10-pll1-clk",
	       sun4i_pll1_clk_setup);

अटल व्योम __init sun6i_pll1_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun6i_a31_pll1_data);
पूर्ण
CLK_OF_DECLARE(sun6i_pll1, "allwinner,sun6i-a31-pll1-clk",
	       sun6i_pll1_clk_setup);

अटल व्योम __init sun8i_pll1_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun8i_a23_pll1_data);
पूर्ण
CLK_OF_DECLARE(sun8i_pll1, "allwinner,sun8i-a23-pll1-clk",
	       sun8i_pll1_clk_setup);

अटल व्योम __init sun7i_pll4_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun7i_a20_pll4_data);
पूर्ण
CLK_OF_DECLARE(sun7i_pll4, "allwinner,sun7i-a20-pll4-clk",
	       sun7i_pll4_clk_setup);

अटल व्योम __init sun5i_ahb_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun5i_a13_ahb_data);
पूर्ण
CLK_OF_DECLARE(sun5i_ahb, "allwinner,sun5i-a13-ahb-clk",
	       sun5i_ahb_clk_setup);

अटल व्योम __init sun6i_ahb1_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun6i_ahb1_data);
पूर्ण
CLK_OF_DECLARE(sun6i_a31_ahb1, "allwinner,sun6i-a31-ahb1-clk",
	       sun6i_ahb1_clk_setup);

अटल व्योम __init sun4i_apb1_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun4i_apb1_data);
पूर्ण
CLK_OF_DECLARE(sun4i_apb1, "allwinner,sun4i-a10-apb1-clk",
	       sun4i_apb1_clk_setup);

अटल व्योम __init sun7i_out_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun7i_a20_out_data);
पूर्ण
CLK_OF_DECLARE(sun7i_out, "allwinner,sun7i-a20-out-clk",
	       sun7i_out_clk_setup);


/*
 * sunxi_mux_clk_setup() - Setup function क्रम muxes
 */

#घोषणा SUNXI_MUX_GATE_WIDTH	2

काष्ठा mux_data अणु
	u8 shअगरt;
पूर्ण;

अटल स्थिर काष्ठा mux_data sun4i_cpu_mux_data __initस्थिर = अणु
	.shअगरt = 16,
पूर्ण;

अटल स्थिर काष्ठा mux_data sun6i_a31_ahb1_mux_data __initस्थिर = अणु
	.shअगरt = 12,
पूर्ण;

अटल स्थिर काष्ठा mux_data sun8i_h3_ahb2_mux_data __initस्थिर = अणु
	.shअगरt = 0,
पूर्ण;

अटल काष्ठा clk * __init sunxi_mux_clk_setup(काष्ठा device_node *node,
					       स्थिर काष्ठा mux_data *data,
					       अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parents[SUNXI_MAX_PARENTS];
	व्योम __iomem *reg;
	पूर्णांक i;

	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("Could not map registers for mux-clk: %pOF\n", node);
		वापस शून्य;
	पूर्ण

	i = of_clk_parent_fill(node, parents, SUNXI_MAX_PARENTS);
	अगर (of_property_पढ़ो_string(node, "clock-output-names", &clk_name)) अणु
		pr_err("%s: could not read clock-output-names from \"%pOF\"\n",
		       __func__, node);
		जाओ out_unmap;
	पूर्ण

	clk = clk_रेजिस्टर_mux(शून्य, clk_name, parents, i,
			       CLK_SET_RATE_PARENT | flags, reg,
			       data->shअगरt, SUNXI_MUX_GATE_WIDTH,
			       0, &clk_lock);

	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to register mux clock %s: %ld\n", __func__,
		       clk_name, PTR_ERR(clk));
		जाओ out_unmap;
	पूर्ण

	अगर (of_clk_add_provider(node, of_clk_src_simple_get, clk)) अणु
		pr_err("%s: failed to add clock provider for %s\n",
		       __func__, clk_name);
		clk_unरेजिस्टर_भागider(clk);
		जाओ out_unmap;
	पूर्ण

	वापस clk;
out_unmap:
	iounmap(reg);
	वापस शून्य;
पूर्ण

अटल व्योम __init sun4i_cpu_clk_setup(काष्ठा device_node *node)
अणु
	/* Protect CPU घड़ी */
	sunxi_mux_clk_setup(node, &sun4i_cpu_mux_data, CLK_IS_CRITICAL);
पूर्ण
CLK_OF_DECLARE(sun4i_cpu, "allwinner,sun4i-a10-cpu-clk",
	       sun4i_cpu_clk_setup);

अटल व्योम __init sun6i_ahb1_mux_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_mux_clk_setup(node, &sun6i_a31_ahb1_mux_data, 0);
पूर्ण
CLK_OF_DECLARE(sun6i_ahb1_mux, "allwinner,sun6i-a31-ahb1-mux-clk",
	       sun6i_ahb1_mux_clk_setup);

अटल व्योम __init sun8i_ahb2_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_mux_clk_setup(node, &sun8i_h3_ahb2_mux_data, 0);
पूर्ण
CLK_OF_DECLARE(sun8i_ahb2, "allwinner,sun8i-h3-ahb2-clk",
	       sun8i_ahb2_clk_setup);


/*
 * sunxi_भागider_clk_setup() - Setup function क्रम simple भागider घड़ीs
 */

काष्ठा भाग_data अणु
	u8	shअगरt;
	u8	घात;
	u8	width;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
पूर्ण;

अटल स्थिर काष्ठा भाग_data sun4i_axi_data __initस्थिर = अणु
	.shअगरt	= 0,
	.घात	= 0,
	.width	= 2,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable sun8i_a23_axi_table[] __initस्थिर = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 3 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 4, .भाग = 4 पूर्ण,
	अणु .val = 5, .भाग = 4 पूर्ण,
	अणु .val = 6, .भाग = 4 पूर्ण,
	अणु .val = 7, .भाग = 4 पूर्ण,
	अणु पूर्ण /* sentinel */
पूर्ण;

अटल स्थिर काष्ठा भाग_data sun8i_a23_axi_data __initस्थिर = अणु
	.width	= 3,
	.table	= sun8i_a23_axi_table,
पूर्ण;

अटल स्थिर काष्ठा भाग_data sun4i_ahb_data __initस्थिर = अणु
	.shअगरt	= 4,
	.घात	= 1,
	.width	= 2,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable sun4i_apb0_table[] __initस्थिर = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 4 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु पूर्ण /* sentinel */
पूर्ण;

अटल स्थिर काष्ठा भाग_data sun4i_apb0_data __initस्थिर = अणु
	.shअगरt	= 8,
	.घात	= 1,
	.width	= 2,
	.table	= sun4i_apb0_table,
पूर्ण;

अटल व्योम __init sunxi_भागider_clk_setup(काष्ठा device_node *node,
					   स्थिर काष्ठा भाग_data *data)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *clk_parent;
	व्योम __iomem *reg;

	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("Could not map registers for mux-clk: %pOF\n", node);
		वापस;
	पूर्ण

	clk_parent = of_clk_get_parent_name(node, 0);

	अगर (of_property_पढ़ो_string(node, "clock-output-names", &clk_name)) अणु
		pr_err("%s: could not read clock-output-names from \"%pOF\"\n",
		       __func__, node);
		जाओ out_unmap;
	पूर्ण

	clk = clk_रेजिस्टर_भागider_table(शून्य, clk_name, clk_parent, 0,
					 reg, data->shअगरt, data->width,
					 data->घात ? CLK_DIVIDER_POWER_OF_TWO : 0,
					 data->table, &clk_lock);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to register divider clock %s: %ld\n",
		       __func__, clk_name, PTR_ERR(clk));
		जाओ out_unmap;
	पूर्ण

	अगर (of_clk_add_provider(node, of_clk_src_simple_get, clk)) अणु
		pr_err("%s: failed to add clock provider for %s\n",
		       __func__, clk_name);
		जाओ out_unरेजिस्टर;
	पूर्ण

	अगर (clk_रेजिस्टर_clkdev(clk, clk_name, शून्य)) अणु
		of_clk_del_provider(node);
		जाओ out_unरेजिस्टर;
	पूर्ण

	वापस;
out_unरेजिस्टर:
	clk_unरेजिस्टर_भागider(clk);

out_unmap:
	iounmap(reg);
पूर्ण

अटल व्योम __init sun4i_ahb_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागider_clk_setup(node, &sun4i_ahb_data);
पूर्ण
CLK_OF_DECLARE(sun4i_ahb, "allwinner,sun4i-a10-ahb-clk",
	       sun4i_ahb_clk_setup);

अटल व्योम __init sun4i_apb0_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागider_clk_setup(node, &sun4i_apb0_data);
पूर्ण
CLK_OF_DECLARE(sun4i_apb0, "allwinner,sun4i-a10-apb0-clk",
	       sun4i_apb0_clk_setup);

अटल व्योम __init sun4i_axi_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागider_clk_setup(node, &sun4i_axi_data);
पूर्ण
CLK_OF_DECLARE(sun4i_axi, "allwinner,sun4i-a10-axi-clk",
	       sun4i_axi_clk_setup);

अटल व्योम __init sun8i_axi_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागider_clk_setup(node, &sun8i_a23_axi_data);
पूर्ण
CLK_OF_DECLARE(sun8i_axi, "allwinner,sun8i-a23-axi-clk",
	       sun8i_axi_clk_setup);



/*
 * sunxi_gates_clk_setup() - Setup function क्रम leaf gates on घड़ीs
 */

#घोषणा SUNXI_GATES_MAX_SIZE	64

काष्ठा gates_data अणु
	DECLARE_BITMAP(mask, SUNXI_GATES_MAX_SIZE);
पूर्ण;

/*
 * sunxi_भागs_clk_setup() helper data
 */

#घोषणा SUNXI_DIVS_MAX_QTY	4
#घोषणा SUNXI_DIVISOR_WIDTH	2

काष्ठा भागs_data अणु
	स्थिर काष्ठा factors_data *factors; /* data क्रम the factor घड़ी */
	पूर्णांक nभागs; /* number of outमाला_दो */
	/*
	 * List of outमाला_दो. Refer to the diagram क्रम sunxi_भागs_clk_setup():
	 * self or base factor घड़ी refers to the output from the pll
	 * itself. The reमुख्यing refer to fixed or configurable भागider
	 * outमाला_दो.
	 */
	काष्ठा अणु
		u8 self; /* is it the base factor घड़ी? (only one) */
		u8 fixed; /* is it a fixed भागisor? अगर not... */
		काष्ठा clk_भाग_प्रकारable *table; /* is it a table based भागisor? */
		u8 shअगरt; /* otherwise it's a normal भागisor with this shअगरt */
		u8 घात;   /* is it घातer-of-two based? */
		u8 gate;  /* is it independently gateable? */
		bool critical;
	पूर्ण भाग[SUNXI_DIVS_MAX_QTY];
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable pll6_sata_tbl[] = अणु
	अणु .val = 0, .भाग = 6, पूर्ण,
	अणु .val = 1, .भाग = 12, पूर्ण,
	अणु .val = 2, .भाग = 18, पूर्ण,
	अणु .val = 3, .भाग = 24, पूर्ण,
	अणु पूर्ण /* sentinel */
पूर्ण;

अटल स्थिर काष्ठा भागs_data pll5_भागs_data __initस्थिर = अणु
	.factors = &sun4i_pll5_data,
	.nभागs = 2,
	.भाग = अणु
		/* Protect PLL5_DDR */
		अणु .shअगरt = 0, .घात = 0, .critical = true पूर्ण, /* M, DDR */
		अणु .shअगरt = 16, .घात = 1, पूर्ण, /* P, other */
		/* No output क्रम the base factor घड़ी */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा भागs_data pll6_भागs_data __initस्थिर = अणु
	.factors = &sun4i_pll5_data,
	.nभागs = 4,
	.भाग = अणु
		अणु .shअगरt = 0, .table = pll6_sata_tbl, .gate = 14 पूर्ण, /* M, SATA */
		अणु .fixed = 2 पूर्ण, /* P, other */
		अणु .self = 1 पूर्ण, /* base factor घड़ी, 2x */
		अणु .fixed = 4 पूर्ण, /* pll6 / 4, used as ahb input */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा भागs_data sun6i_a31_pll6_भागs_data __initस्थिर = अणु
	.factors = &sun6i_a31_pll6_data,
	.nभागs = 2,
	.भाग = अणु
		अणु .fixed = 2 पूर्ण, /* normal output */
		अणु .self = 1 पूर्ण, /* base factor घड़ी, 2x */
	पूर्ण
पूर्ण;

/*
 * sunxi_भागs_clk_setup() - Setup function क्रम leaf भागisors on घड़ीs
 *
 * These घड़ीs look something like this
 *            ________________________
 *           |         ___भागisor 1---|----> to consumer
 * parent >--|  pll___/___भागisor 2---|----> to consumer
 *           |        \_______________|____> to consumer
 *           |________________________|
 */

अटल काष्ठा clk ** __init sunxi_भागs_clk_setup(काष्ठा device_node *node,
						 स्थिर काष्ठा भागs_data *data)
अणु
	काष्ठा clk_onecell_data *clk_data;
	स्थिर अक्षर *parent;
	स्थिर अक्षर *clk_name;
	काष्ठा clk **clks, *pclk;
	काष्ठा clk_hw *gate_hw, *rate_hw;
	स्थिर काष्ठा clk_ops *rate_ops;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_fixed_factor *fix_factor;
	काष्ठा clk_भागider *भागider;
	काष्ठा factors_data factors = *data->factors;
	अक्षर *derived_name = शून्य;
	व्योम __iomem *reg;
	पूर्णांक nभागs = SUNXI_DIVS_MAX_QTY, i = 0;
	पूर्णांक flags, clkflags;

	/* अगर number of children known, use it */
	अगर (data->nभागs)
		nभागs = data->nभागs;

	/* Try to find a name क्रम base factor घड़ी */
	क्रम (i = 0; i < nभागs; i++) अणु
		अगर (data->भाग[i].self) अणु
			of_property_पढ़ो_string_index(node, "clock-output-names",
						      i, &factors.name);
			अवरोध;
		पूर्ण
	पूर्ण
	/* If we करोn't have a .self clk use the first output-name up to '_' */
	अगर (factors.name == शून्य) अणु
		अक्षर *endp;

		of_property_पढ़ो_string_index(node, "clock-output-names",
						      0, &clk_name);
		endp = म_अक्षर(clk_name, '_');
		अगर (endp) अणु
			derived_name = kstrndup(clk_name, endp - clk_name,
						GFP_KERNEL);
			अगर (!derived_name)
				वापस शून्य;
			factors.name = derived_name;
		पूर्ण अन्यथा अणु
			factors.name = clk_name;
		पूर्ण
	पूर्ण

	/* Set up factor घड़ी that we will be भागiding */
	pclk = sunxi_factors_clk_setup(node, &factors);
	अगर (!pclk)
		वापस शून्य;

	parent = __clk_get_name(pclk);
	kमुक्त(derived_name);

	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("Could not map registers for divs-clk: %pOF\n", node);
		वापस शून्य;
	पूर्ण

	clk_data = kदो_स्मृति(माप(काष्ठा clk_onecell_data), GFP_KERNEL);
	अगर (!clk_data)
		जाओ out_unmap;

	clks = kसुस्मृति(nभागs, माप(*clks), GFP_KERNEL);
	अगर (!clks)
		जाओ मुक्त_clkdata;

	clk_data->clks = clks;

	/* It's not a good idea to have स्वतःmatic reparenting changing
	 * our RAM घड़ी! */
	clkflags = !म_भेद("pll5", parent) ? 0 : CLK_SET_RATE_PARENT;

	क्रम (i = 0; i < nभागs; i++) अणु
		अगर (of_property_पढ़ो_string_index(node, "clock-output-names",
						  i, &clk_name) != 0)
			अवरोध;

		/* If this is the base factor घड़ी, only update clks */
		अगर (data->भाग[i].self) अणु
			clk_data->clks[i] = pclk;
			जारी;
		पूर्ण

		gate_hw = शून्य;
		rate_hw = शून्य;
		rate_ops = शून्य;

		/* If this leaf घड़ी can be gated, create a gate */
		अगर (data->भाग[i].gate) अणु
			gate = kzalloc(माप(*gate), GFP_KERNEL);
			अगर (!gate)
				जाओ मुक्त_clks;

			gate->reg = reg;
			gate->bit_idx = data->भाग[i].gate;
			gate->lock = &clk_lock;

			gate_hw = &gate->hw;
		पूर्ण

		/* Leaves can be fixed or configurable भागisors */
		अगर (data->भाग[i].fixed) अणु
			fix_factor = kzalloc(माप(*fix_factor), GFP_KERNEL);
			अगर (!fix_factor)
				जाओ मुक्त_gate;

			fix_factor->mult = 1;
			fix_factor->भाग = data->भाग[i].fixed;

			rate_hw = &fix_factor->hw;
			rate_ops = &clk_fixed_factor_ops;
		पूर्ण अन्यथा अणु
			भागider = kzalloc(माप(*भागider), GFP_KERNEL);
			अगर (!भागider)
				जाओ मुक्त_gate;

			flags = data->भाग[i].घात ? CLK_DIVIDER_POWER_OF_TWO : 0;

			भागider->reg = reg;
			भागider->shअगरt = data->भाग[i].shअगरt;
			भागider->width = SUNXI_DIVISOR_WIDTH;
			भागider->flags = flags;
			भागider->lock = &clk_lock;
			भागider->table = data->भाग[i].table;

			rate_hw = &भागider->hw;
			rate_ops = &clk_भागider_ops;
		पूर्ण

		/* Wrap the (potential) gate and the भागisor on a composite
		 * घड़ी to unअगरy them */
		clks[i] = clk_रेजिस्टर_composite(शून्य, clk_name, &parent, 1,
						 शून्य, शून्य,
						 rate_hw, rate_ops,
						 gate_hw, &clk_gate_ops,
						 clkflags |
						 (data->भाग[i].critical ?
							CLK_IS_CRITICAL : 0));

		WARN_ON(IS_ERR(clk_data->clks[i]));
	पूर्ण

	/* Adjust to the real max */
	clk_data->clk_num = i;

	अगर (of_clk_add_provider(node, of_clk_src_onecell_get, clk_data)) अणु
		pr_err("%s: failed to add clock provider for %s\n",
		       __func__, clk_name);
		जाओ मुक्त_gate;
	पूर्ण

	वापस clks;
मुक्त_gate:
	kमुक्त(gate);
मुक्त_clks:
	kमुक्त(clks);
मुक्त_clkdata:
	kमुक्त(clk_data);
out_unmap:
	iounmap(reg);
	वापस शून्य;
पूर्ण

अटल व्योम __init sun4i_pll5_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागs_clk_setup(node, &pll5_भागs_data);
पूर्ण
CLK_OF_DECLARE(sun4i_pll5, "allwinner,sun4i-a10-pll5-clk",
	       sun4i_pll5_clk_setup);

अटल व्योम __init sun4i_pll6_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागs_clk_setup(node, &pll6_भागs_data);
पूर्ण
CLK_OF_DECLARE(sun4i_pll6, "allwinner,sun4i-a10-pll6-clk",
	       sun4i_pll6_clk_setup);

अटल व्योम __init sun6i_pll6_clk_setup(काष्ठा device_node *node)
अणु
	sunxi_भागs_clk_setup(node, &sun6i_a31_pll6_भागs_data);
पूर्ण
CLK_OF_DECLARE(sun6i_pll6, "allwinner,sun6i-a31-pll6-clk",
	       sun6i_pll6_clk_setup);

/*
 * sun6i display
 *
 * rate = parent_rate / (m + 1);
 */
अटल व्योम sun6i_display_factors(काष्ठा factors_request *req)
अणु
	u8 m;

	अगर (req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	m = DIV_ROUND_UP(req->parent_rate, req->rate);

	req->rate = req->parent_rate / m;
	req->m = m - 1;
पूर्ण

अटल स्थिर काष्ठा clk_factors_config sun6i_display_config = अणु
	.mshअगरt = 0,
	.mwidth = 4,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun6i_display_data __initस्थिर = अणु
	.enable = 31,
	.mux = 24,
	.muxmask = BIT(2) | BIT(1) | BIT(0),
	.table = &sun6i_display_config,
	.getter = sun6i_display_factors,
पूर्ण;

अटल व्योम __init sun6i_display_setup(काष्ठा device_node *node)
अणु
	sunxi_factors_clk_setup(node, &sun6i_display_data);
पूर्ण
CLK_OF_DECLARE(sun6i_display, "allwinner,sun6i-a31-display-clk",
	       sun6i_display_setup);
