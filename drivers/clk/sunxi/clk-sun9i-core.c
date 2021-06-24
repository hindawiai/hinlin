<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/log2.h>

#समावेश "clk-factors.h"


/*
 * sun9i_a80_get_pll4_factors() - calculates n, p, m factors क्रम PLL4
 * PLL4 rate is calculated as follows
 * rate = (parent_rate * n >> p) / (m + 1);
 * parent_rate is always 24MHz
 *
 * p and m are named भाग1 and भाग2 in Allwinner's SDK
 */

अटल व्योम sun9i_a80_get_pll4_factors(काष्ठा factors_request *req)
अणु
	पूर्णांक n;
	पूर्णांक m = 1;
	पूर्णांक p = 1;

	/* Normalize value to a 6 MHz multiple (24 MHz / 4) */
	n = DIV_ROUND_UP(req->rate, 6000000);

	/* If n is too large चयन to steps of 12 MHz */
	अगर (n > 255) अणु
		m = 0;
		n = (n + 1) / 2;
	पूर्ण

	/* If n is still too large चयन to steps of 24 MHz */
	अगर (n > 255) अणु
		p = 0;
		n = (n + 1) / 2;
	पूर्ण

	/* n must be between 12 and 255 */
	अगर (n > 255)
		n = 255;
	अन्यथा अगर (n < 12)
		n = 12;

	req->rate = ((24000000 * n) >> p) / (m + 1);
	req->n = n;
	req->m = m;
	req->p = p;
पूर्ण

अटल स्थिर काष्ठा clk_factors_config sun9i_a80_pll4_config = अणु
	.mshअगरt = 18,
	.mwidth = 1,
	.nshअगरt = 8,
	.nwidth = 8,
	.pshअगरt = 16,
	.pwidth = 1,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun9i_a80_pll4_data __initस्थिर = अणु
	.enable = 31,
	.table = &sun9i_a80_pll4_config,
	.getter = sun9i_a80_get_pll4_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun9i_a80_pll4_lock);

अटल व्योम __init sun9i_a80_pll4_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for a80-pll4-clk: %pOFn\n",
		       node);
		वापस;
	पूर्ण

	sunxi_factors_रेजिस्टर(node, &sun9i_a80_pll4_data,
			       &sun9i_a80_pll4_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_pll4, "allwinner,sun9i-a80-pll4-clk", sun9i_a80_pll4_setup);


/*
 * sun9i_a80_get_gt_factors() - calculates m factor क्रम GT
 * GT rate is calculated as follows
 * rate = parent_rate / (m + 1);
 */

अटल व्योम sun9i_a80_get_gt_factors(काष्ठा factors_request *req)
अणु
	u32 भाग;

	अगर (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* maximum भागider is 4 */
	अगर (भाग > 4)
		भाग = 4;

	req->rate = req->parent_rate / भाग;
	req->m = भाग;
पूर्ण

अटल स्थिर काष्ठा clk_factors_config sun9i_a80_gt_config = अणु
	.mshअगरt = 0,
	.mwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun9i_a80_gt_data __initस्थिर = अणु
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun9i_a80_gt_config,
	.getter = sun9i_a80_get_gt_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun9i_a80_gt_lock);

अटल व्योम __init sun9i_a80_gt_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for a80-gt-clk: %pOFn\n",
		       node);
		वापस;
	पूर्ण

	/* The GT bus घड़ी needs to be always enabled */
	sunxi_factors_रेजिस्टर_critical(node, &sun9i_a80_gt_data,
					&sun9i_a80_gt_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_gt, "allwinner,sun9i-a80-gt-clk", sun9i_a80_gt_setup);


/*
 * sun9i_a80_get_ahb_factors() - calculates p factor क्रम AHB0/1/2
 * AHB rate is calculated as follows
 * rate = parent_rate >> p;
 */

अटल व्योम sun9i_a80_get_ahb_factors(काष्ठा factors_request *req)
अणु
	u32 _p;

	अगर (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	_p = order_base_2(DIV_ROUND_UP(req->parent_rate, req->rate));

	/* maximum p is 3 */
	अगर (_p > 3)
		_p = 3;

	req->rate = req->parent_rate >> _p;
	req->p = _p;
पूर्ण

अटल स्थिर काष्ठा clk_factors_config sun9i_a80_ahb_config = अणु
	.pshअगरt = 0,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun9i_a80_ahb_data __initस्थिर = अणु
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun9i_a80_ahb_config,
	.getter = sun9i_a80_get_ahb_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun9i_a80_ahb_lock);

अटल व्योम __init sun9i_a80_ahb_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for a80-ahb-clk: %pOFn\n",
		       node);
		वापस;
	पूर्ण

	sunxi_factors_रेजिस्टर(node, &sun9i_a80_ahb_data,
			       &sun9i_a80_ahb_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_ahb, "allwinner,sun9i-a80-ahb-clk", sun9i_a80_ahb_setup);


अटल स्थिर काष्ठा factors_data sun9i_a80_apb0_data __initस्थिर = अणु
	.mux = 24,
	.muxmask = BIT(0),
	.table = &sun9i_a80_ahb_config,
	.getter = sun9i_a80_get_ahb_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun9i_a80_apb0_lock);

अटल व्योम __init sun9i_a80_apb0_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for a80-apb0-clk: %pOFn\n",
		       node);
		वापस;
	पूर्ण

	sunxi_factors_रेजिस्टर(node, &sun9i_a80_apb0_data,
			       &sun9i_a80_apb0_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_apb0, "allwinner,sun9i-a80-apb0-clk", sun9i_a80_apb0_setup);


/*
 * sun9i_a80_get_apb1_factors() - calculates m, p factors क्रम APB1
 * APB1 rate is calculated as follows
 * rate = (parent_rate >> p) / (m + 1);
 */

अटल व्योम sun9i_a80_get_apb1_factors(काष्ठा factors_request *req)
अणु
	u32 भाग;

	अगर (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* Highest possible भागider is 256 (p = 3, m = 31) */
	अगर (भाग > 256)
		भाग = 256;

	req->p = order_base_2(भाग);
	req->m = (req->parent_rate >> req->p) - 1;
	req->rate = (req->parent_rate >> req->p) / (req->m + 1);
पूर्ण

अटल स्थिर काष्ठा clk_factors_config sun9i_a80_apb1_config = अणु
	.mshअगरt = 0,
	.mwidth = 5,
	.pshअगरt = 16,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun9i_a80_apb1_data __initस्थिर = अणु
	.mux = 24,
	.muxmask = BIT(0),
	.table = &sun9i_a80_apb1_config,
	.getter = sun9i_a80_get_apb1_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun9i_a80_apb1_lock);

अटल व्योम __init sun9i_a80_apb1_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for a80-apb1-clk: %pOFn\n",
		       node);
		वापस;
	पूर्ण

	sunxi_factors_रेजिस्टर(node, &sun9i_a80_apb1_data,
			       &sun9i_a80_apb1_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_apb1, "allwinner,sun9i-a80-apb1-clk", sun9i_a80_apb1_setup);
