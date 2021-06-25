<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Emilio Lथकpez
 *
 * Emilio Lथकpez <emilio@elopez.com.ar>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "clk-factors.h"

/*
 * sun4i_a10_get_mod0_factors() - calculates m, n factors क्रम MOD0-style घड़ीs
 * MOD0 rate is calculated as follows
 * rate = (parent_rate >> p) / (m + 1);
 */

अटल व्योम sun4i_a10_get_mod0_factors(काष्ठा factors_request *req)
अणु
	u8 भाग, calcm, calcp;

	/* These घड़ीs can only भागide, so we will never be able to achieve
	 * frequencies higher than the parent frequency */
	अगर (req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	अगर (भाग < 16)
		calcp = 0;
	अन्यथा अगर (भाग / 2 < 16)
		calcp = 1;
	अन्यथा अगर (भाग / 4 < 16)
		calcp = 2;
	अन्यथा
		calcp = 3;

	calcm = DIV_ROUND_UP(भाग, 1 << calcp);

	req->rate = (req->parent_rate >> calcp) / calcm;
	req->m = calcm - 1;
	req->p = calcp;
पूर्ण

/* user manual says "n" but it's really "p" */
अटल स्थिर काष्ठा clk_factors_config sun4i_a10_mod0_config = अणु
	.mshअगरt = 0,
	.mwidth = 4,
	.pshअगरt = 16,
	.pwidth = 2,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun4i_a10_mod0_data = अणु
	.enable = 31,
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.table = &sun4i_a10_mod0_config,
	.getter = sun4i_a10_get_mod0_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun4i_a10_mod0_lock);

अटल व्योम __init sun4i_a10_mod0_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		/*
		 * This happens with mod0 clk nodes instantiated through
		 * mfd, as those करो not have their resources asचिन्हित at
		 * CLK_OF_DECLARE समय yet, so करो not prपूर्णांक an error.
		 */
		वापस;
	पूर्ण

	sunxi_factors_रेजिस्टर(node, &sun4i_a10_mod0_data,
			       &sun4i_a10_mod0_lock, reg);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun4i_a10_mod0, "allwinner,sun4i-a10-mod0-clk",
		      sun4i_a10_mod0_setup);

अटल पूर्णांक sun4i_a10_mod0_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *r;
	व्योम __iomem *reg;

	अगर (!np)
		वापस -ENODEV;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	sunxi_factors_रेजिस्टर(np, &sun4i_a10_mod0_data,
			       &sun4i_a10_mod0_lock, reg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_a10_mod0_clk_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-mod0-clk" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun4i_a10_mod0_clk_driver = अणु
	.driver = अणु
		.name = "sun4i-a10-mod0-clk",
		.of_match_table = sun4i_a10_mod0_clk_dt_ids,
	पूर्ण,
	.probe = sun4i_a10_mod0_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sun4i_a10_mod0_clk_driver);

अटल स्थिर काष्ठा factors_data sun9i_a80_mod0_data __initस्थिर = अणु
	.enable = 31,
	.mux = 24,
	.muxmask = BIT(3) | BIT(2) | BIT(1) | BIT(0),
	.table = &sun4i_a10_mod0_config,
	.getter = sun4i_a10_get_mod0_factors,
पूर्ण;

अटल व्योम __init sun9i_a80_mod0_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for mod0-clk: %pOFn\n",
		       node);
		वापस;
	पूर्ण

	sunxi_factors_रेजिस्टर(node, &sun9i_a80_mod0_data,
			       &sun4i_a10_mod0_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_mod0, "allwinner,sun9i-a80-mod0-clk", sun9i_a80_mod0_setup);

अटल DEFINE_SPINLOCK(sun5i_a13_mbus_lock);

अटल व्योम __init sun5i_a13_mbus_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;

	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("Could not get registers for a13-mbus-clk\n");
		वापस;
	पूर्ण

	/* The MBUS घड़ीs needs to be always enabled */
	sunxi_factors_रेजिस्टर_critical(node, &sun4i_a10_mod0_data,
					&sun5i_a13_mbus_lock, reg);
पूर्ण
CLK_OF_DECLARE(sun5i_a13_mbus, "allwinner,sun5i-a13-mbus-clk", sun5i_a13_mbus_setup);

काष्ठा mmc_phase अणु
	काष्ठा clk_hw		hw;
	u8			offset;
	व्योम __iomem		*reg;
	spinlock_t		*lock;
पूर्ण;

#घोषणा to_mmc_phase(_hw) container_of(_hw, काष्ठा mmc_phase, hw)

अटल पूर्णांक mmc_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk *mmc, *mmc_parent, *clk = hw->clk;
	काष्ठा mmc_phase *phase = to_mmc_phase(hw);
	अचिन्हित पूर्णांक mmc_rate, mmc_parent_rate;
	u16 step, mmc_भाग;
	u32 value;
	u8 delay;

	value = पढ़ोl(phase->reg);
	delay = (value >> phase->offset) & 0x3;

	अगर (!delay)
		वापस 180;

	/* Get the मुख्य MMC घड़ी */
	mmc = clk_get_parent(clk);
	अगर (!mmc)
		वापस -EINVAL;

	/* And its rate */
	mmc_rate = clk_get_rate(mmc);
	अगर (!mmc_rate)
		वापस -EINVAL;

	/* Now, get the MMC parent (most likely some PLL) */
	mmc_parent = clk_get_parent(mmc);
	अगर (!mmc_parent)
		वापस -EINVAL;

	/* And its rate */
	mmc_parent_rate = clk_get_rate(mmc_parent);
	अगर (!mmc_parent_rate)
		वापस -EINVAL;

	/* Get MMC घड़ी भागider */
	mmc_भाग = mmc_parent_rate / mmc_rate;

	step = DIV_ROUND_CLOSEST(360, mmc_भाग);
	वापस delay * step;
पूर्ण

अटल पूर्णांक mmc_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा clk *mmc, *mmc_parent, *clk = hw->clk;
	काष्ठा mmc_phase *phase = to_mmc_phase(hw);
	अचिन्हित पूर्णांक mmc_rate, mmc_parent_rate;
	अचिन्हित दीर्घ flags;
	u32 value;
	u8 delay;

	/* Get the मुख्य MMC घड़ी */
	mmc = clk_get_parent(clk);
	अगर (!mmc)
		वापस -EINVAL;

	/* And its rate */
	mmc_rate = clk_get_rate(mmc);
	अगर (!mmc_rate)
		वापस -EINVAL;

	/* Now, get the MMC parent (most likely some PLL) */
	mmc_parent = clk_get_parent(mmc);
	अगर (!mmc_parent)
		वापस -EINVAL;

	/* And its rate */
	mmc_parent_rate = clk_get_rate(mmc_parent);
	अगर (!mmc_parent_rate)
		वापस -EINVAL;

	अगर (degrees != 180) अणु
		u16 step, mmc_भाग;

		/* Get MMC घड़ी भागider */
		mmc_भाग = mmc_parent_rate / mmc_rate;

		/*
		 * We can only outphase the घड़ीs by multiple of the
		 * PLL's period.
		 *
		 * Since the MMC घड़ी in only a भागider, and the
		 * क्रमmula to get the outphasing in degrees is deg =
		 * 360 * delta / period
		 *
		 * If we simplअगरy this क्रमmula, we can see that the
		 * only thing that we're concerned about is the number
		 * of period we want to outphase our घड़ी from, and
		 * the भागider set by the MMC घड़ी.
		 */
		step = DIV_ROUND_CLOSEST(360, mmc_भाग);
		delay = DIV_ROUND_CLOSEST(degrees, step);
	पूर्ण अन्यथा अणु
		delay = 0;
	पूर्ण

	spin_lock_irqsave(phase->lock, flags);
	value = पढ़ोl(phase->reg);
	value &= ~GENMASK(phase->offset + 3, phase->offset);
	value |= delay << phase->offset;
	ग_लिखोl(value, phase->reg);
	spin_unlock_irqrestore(phase->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops mmc_clk_ops = अणु
	.get_phase	= mmc_get_phase,
	.set_phase	= mmc_set_phase,
पूर्ण;

/*
 * sunxi_mmc_setup - Common setup function क्रम mmc module घड़ीs
 *
 * The only dअगरference between module घड़ीs on dअगरferent platक्रमms is the
 * width of the mux रेजिस्टर bits and the valid values, which are passed in
 * through काष्ठा factors_data. The phase घड़ीs parts are identical.
 */
अटल व्योम __init sunxi_mmc_setup(काष्ठा device_node *node,
				   स्थिर काष्ठा factors_data *data,
				   spinlock_t *lock)
अणु
	काष्ठा clk_onecell_data *clk_data;
	स्थिर अक्षर *parent;
	व्योम __iomem *reg;
	पूर्णांक i;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Couldn't map the %pOFn clock registers\n", node);
		वापस;
	पूर्ण

	clk_data = kदो_स्मृति(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->clks = kसुस्मृति(3, माप(*clk_data->clks), GFP_KERNEL);
	अगर (!clk_data->clks)
		जाओ err_मुक्त_data;

	clk_data->clk_num = 3;
	clk_data->clks[0] = sunxi_factors_रेजिस्टर(node, data, lock, reg);
	अगर (!clk_data->clks[0])
		जाओ err_मुक्त_clks;

	parent = __clk_get_name(clk_data->clks[0]);

	क्रम (i = 1; i < 3; i++) अणु
		काष्ठा clk_init_data init = अणु
			.num_parents	= 1,
			.parent_names	= &parent,
			.ops		= &mmc_clk_ops,
		पूर्ण;
		काष्ठा mmc_phase *phase;

		phase = kदो_स्मृति(माप(*phase), GFP_KERNEL);
		अगर (!phase)
			जारी;

		phase->hw.init = &init;
		phase->reg = reg;
		phase->lock = lock;

		अगर (i == 1)
			phase->offset = 8;
		अन्यथा
			phase->offset = 20;

		अगर (of_property_पढ़ो_string_index(node, "clock-output-names",
						  i, &init.name))
			init.name = node->name;

		clk_data->clks[i] = clk_रेजिस्टर(शून्य, &phase->hw);
		अगर (IS_ERR(clk_data->clks[i])) अणु
			kमुक्त(phase);
			जारी;
		पूर्ण
	पूर्ण

	of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	वापस;

err_मुक्त_clks:
	kमुक्त(clk_data->clks);
err_मुक्त_data:
	kमुक्त(clk_data);
पूर्ण

अटल DEFINE_SPINLOCK(sun4i_a10_mmc_lock);

अटल व्योम __init sun4i_a10_mmc_setup(काष्ठा device_node *node)
अणु
	sunxi_mmc_setup(node, &sun4i_a10_mod0_data, &sun4i_a10_mmc_lock);
पूर्ण
CLK_OF_DECLARE(sun4i_a10_mmc, "allwinner,sun4i-a10-mmc-clk", sun4i_a10_mmc_setup);

अटल DEFINE_SPINLOCK(sun9i_a80_mmc_lock);

अटल व्योम __init sun9i_a80_mmc_setup(काष्ठा device_node *node)
अणु
	sunxi_mmc_setup(node, &sun9i_a80_mod0_data, &sun9i_a80_mmc_lock);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_mmc, "allwinner,sun9i-a80-mmc-clk", sun9i_a80_mmc_setup);
