<शैली गुरु>
/*
 * Synopsys HSDK SDP Generic PLL घड़ी driver
 *
 * Copyright (C) 2017 Synopsys
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा CGU_PLL_CTRL	0x000 /* ARC PLL control रेजिस्टर */
#घोषणा CGU_PLL_STATUS	0x004 /* ARC PLL status रेजिस्टर */
#घोषणा CGU_PLL_FMEAS	0x008 /* ARC PLL frequency measurement रेजिस्टर */
#घोषणा CGU_PLL_MON	0x00C /* ARC PLL monitor रेजिस्टर */

#घोषणा CGU_PLL_CTRL_ODIV_SHIFT		2
#घोषणा CGU_PLL_CTRL_IDIV_SHIFT		4
#घोषणा CGU_PLL_CTRL_FBDIV_SHIFT	9
#घोषणा CGU_PLL_CTRL_BAND_SHIFT		20

#घोषणा CGU_PLL_CTRL_ODIV_MASK		GENMASK(3, CGU_PLL_CTRL_ODIV_SHIFT)
#घोषणा CGU_PLL_CTRL_IDIV_MASK		GENMASK(8, CGU_PLL_CTRL_IDIV_SHIFT)
#घोषणा CGU_PLL_CTRL_FBDIV_MASK		GENMASK(15, CGU_PLL_CTRL_FBDIV_SHIFT)

#घोषणा CGU_PLL_CTRL_PD			BIT(0)
#घोषणा CGU_PLL_CTRL_BYPASS		BIT(1)

#घोषणा CGU_PLL_STATUS_LOCK		BIT(0)
#घोषणा CGU_PLL_STATUS_ERR		BIT(1)

#घोषणा HSDK_PLL_MAX_LOCK_TIME		100 /* 100 us */

#घोषणा CGU_PLL_SOURCE_MAX		1

#घोषणा CORE_IF_CLK_THRESHOLD_HZ	500000000
#घोषणा CREG_CORE_IF_CLK_DIV_1		0x0
#घोषणा CREG_CORE_IF_CLK_DIV_2		0x1

काष्ठा hsdk_pll_cfg अणु
	u32 rate;
	u32 iभाग;
	u32 fbभाग;
	u32 oभाग;
	u32 band;
	u32 bypass;
पूर्ण;

अटल स्थिर काष्ठा hsdk_pll_cfg asdt_pll_cfg[] = अणु
	अणु 100000000,  0, 11, 3, 0, 0 पूर्ण,
	अणु 133000000,  0, 15, 3, 0, 0 पूर्ण,
	अणु 200000000,  1, 47, 3, 0, 0 पूर्ण,
	अणु 233000000,  1, 27, 2, 0, 0 पूर्ण,
	अणु 300000000,  1, 35, 2, 0, 0 पूर्ण,
	अणु 333000000,  1, 39, 2, 0, 0 पूर्ण,
	अणु 400000000,  1, 47, 2, 0, 0 पूर्ण,
	अणु 500000000,  0, 14, 1, 0, 0 पूर्ण,
	अणु 600000000,  0, 17, 1, 0, 0 पूर्ण,
	अणु 700000000,  0, 20, 1, 0, 0 पूर्ण,
	अणु 800000000,  0, 23, 1, 0, 0 पूर्ण,
	अणु 900000000,  1, 26, 0, 0, 0 पूर्ण,
	अणु 1000000000, 1, 29, 0, 0, 0 पूर्ण,
	अणु 1100000000, 1, 32, 0, 0, 0 पूर्ण,
	अणु 1200000000, 1, 35, 0, 0, 0 पूर्ण,
	अणु 1300000000, 1, 38, 0, 0, 0 पूर्ण,
	अणु 1400000000, 1, 41, 0, 0, 0 पूर्ण,
	अणु 1500000000, 1, 44, 0, 0, 0 पूर्ण,
	अणु 1600000000, 1, 47, 0, 0, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hsdk_pll_cfg hdmi_pll_cfg[] = अणु
	अणु 27000000,   0, 0,  0, 0, 1 पूर्ण,
	अणु 148500000,  0, 21, 3, 0, 0 पूर्ण,
	अणु 297000000,  0, 21, 2, 0, 0 पूर्ण,
	अणु 540000000,  0, 19, 1, 0, 0 पूर्ण,
	अणु 594000000,  0, 21, 1, 0, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा hsdk_pll_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *regs;
	व्योम __iomem *spec_regs;
	स्थिर काष्ठा hsdk_pll_devdata *pll_devdata;
	काष्ठा device *dev;
पूर्ण;

काष्ठा hsdk_pll_devdata अणु
	स्थिर काष्ठा hsdk_pll_cfg *pll_cfg;
	पूर्णांक (*update_rate)(काष्ठा hsdk_pll_clk *clk, अचिन्हित दीर्घ rate,
			   स्थिर काष्ठा hsdk_pll_cfg *cfg);
पूर्ण;

अटल पूर्णांक hsdk_pll_core_update_rate(काष्ठा hsdk_pll_clk *, अचिन्हित दीर्घ,
				     स्थिर काष्ठा hsdk_pll_cfg *);
अटल पूर्णांक hsdk_pll_comm_update_rate(काष्ठा hsdk_pll_clk *, अचिन्हित दीर्घ,
				     स्थिर काष्ठा hsdk_pll_cfg *);

अटल स्थिर काष्ठा hsdk_pll_devdata core_pll_devdata = अणु
	.pll_cfg = asdt_pll_cfg,
	.update_rate = hsdk_pll_core_update_rate,
पूर्ण;

अटल स्थिर काष्ठा hsdk_pll_devdata sdt_pll_devdata = अणु
	.pll_cfg = asdt_pll_cfg,
	.update_rate = hsdk_pll_comm_update_rate,
पूर्ण;

अटल स्थिर काष्ठा hsdk_pll_devdata hdmi_pll_devdata = अणु
	.pll_cfg = hdmi_pll_cfg,
	.update_rate = hsdk_pll_comm_update_rate,
पूर्ण;

अटल अंतरभूत व्योम hsdk_pll_ग_लिखो(काष्ठा hsdk_pll_clk *clk, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, clk->regs + reg);
पूर्ण

अटल अंतरभूत u32 hsdk_pll_पढ़ो(काष्ठा hsdk_pll_clk *clk, u32 reg)
अणु
	वापस ioपढ़ो32(clk->regs + reg);
पूर्ण

अटल अंतरभूत व्योम hsdk_pll_set_cfg(काष्ठा hsdk_pll_clk *clk,
				    स्थिर काष्ठा hsdk_pll_cfg *cfg)
अणु
	u32 val = 0;

	अगर (cfg->bypass) अणु
		val = hsdk_pll_पढ़ो(clk, CGU_PLL_CTRL);
		val |= CGU_PLL_CTRL_BYPASS;
	पूर्ण अन्यथा अणु
		/* Powerकरोwn and Bypass bits should be cleared */
		val |= cfg->iभाग << CGU_PLL_CTRL_IDIV_SHIFT;
		val |= cfg->fbभाग << CGU_PLL_CTRL_FBDIV_SHIFT;
		val |= cfg->oभाग << CGU_PLL_CTRL_ODIV_SHIFT;
		val |= cfg->band << CGU_PLL_CTRL_BAND_SHIFT;
	पूर्ण

	dev_dbg(clk->dev, "write configuration: %#x\n", val);

	hsdk_pll_ग_लिखो(clk, CGU_PLL_CTRL, val);
पूर्ण

अटल अंतरभूत bool hsdk_pll_is_locked(काष्ठा hsdk_pll_clk *clk)
अणु
	वापस !!(hsdk_pll_पढ़ो(clk, CGU_PLL_STATUS) & CGU_PLL_STATUS_LOCK);
पूर्ण

अटल अंतरभूत bool hsdk_pll_is_err(काष्ठा hsdk_pll_clk *clk)
अणु
	वापस !!(hsdk_pll_पढ़ो(clk, CGU_PLL_STATUS) & CGU_PLL_STATUS_ERR);
पूर्ण

अटल अंतरभूत काष्ठा hsdk_pll_clk *to_hsdk_pll_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा hsdk_pll_clk, hw);
पूर्ण

अटल अचिन्हित दीर्घ hsdk_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	u32 val;
	u64 rate;
	u32 iभाग, fbभाग, oभाग;
	काष्ठा hsdk_pll_clk *clk = to_hsdk_pll_clk(hw);

	val = hsdk_pll_पढ़ो(clk, CGU_PLL_CTRL);

	dev_dbg(clk->dev, "current configuration: %#x\n", val);

	/* Check अगर PLL is bypassed */
	अगर (val & CGU_PLL_CTRL_BYPASS)
		वापस parent_rate;

	/* Check अगर PLL is disabled */
	अगर (val & CGU_PLL_CTRL_PD)
		वापस 0;

	/* input भागider = reg.iभाग + 1 */
	iभाग = 1 + ((val & CGU_PLL_CTRL_IDIV_MASK) >> CGU_PLL_CTRL_IDIV_SHIFT);
	/* fb भागider = 2*(reg.fbभाग + 1) */
	fbभाग = 2 * (1 + ((val & CGU_PLL_CTRL_FBDIV_MASK) >> CGU_PLL_CTRL_FBDIV_SHIFT));
	/* output भागider = 2^(reg.oभाग) */
	oभाग = 1 << ((val & CGU_PLL_CTRL_ODIV_MASK) >> CGU_PLL_CTRL_ODIV_SHIFT);

	rate = (u64)parent_rate * fbभाग;
	करो_भाग(rate, iभाग * oभाग);

	वापस rate;
पूर्ण

अटल दीर्घ hsdk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ best_rate;
	काष्ठा hsdk_pll_clk *clk = to_hsdk_pll_clk(hw);
	स्थिर काष्ठा hsdk_pll_cfg *pll_cfg = clk->pll_devdata->pll_cfg;

	अगर (pll_cfg[0].rate == 0)
		वापस -EINVAL;

	best_rate = pll_cfg[0].rate;

	क्रम (i = 1; pll_cfg[i].rate != 0; i++) अणु
		अगर (असल(rate - pll_cfg[i].rate) < असल(rate - best_rate))
			best_rate = pll_cfg[i].rate;
	पूर्ण

	dev_dbg(clk->dev, "chosen best rate: %lu\n", best_rate);

	वापस best_rate;
पूर्ण

अटल पूर्णांक hsdk_pll_comm_update_rate(काष्ठा hsdk_pll_clk *clk,
				     अचिन्हित दीर्घ rate,
				     स्थिर काष्ठा hsdk_pll_cfg *cfg)
अणु
	hsdk_pll_set_cfg(clk, cfg);

	/*
	 * Wait until CGU relocks and check error status.
	 * If after समयout CGU is unlocked yet वापस error.
	 */
	udelay(HSDK_PLL_MAX_LOCK_TIME);
	अगर (!hsdk_pll_is_locked(clk))
		वापस -ETIMEDOUT;

	अगर (hsdk_pll_is_err(clk))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hsdk_pll_core_update_rate(काष्ठा hsdk_pll_clk *clk,
				     अचिन्हित दीर्घ rate,
				     स्थिर काष्ठा hsdk_pll_cfg *cfg)
अणु
	/*
	 * When core घड़ी exceeds 500MHz, the भागider क्रम the पूर्णांकerface
	 * घड़ी must be programmed to भाग-by-2.
	 */
	अगर (rate > CORE_IF_CLK_THRESHOLD_HZ)
		ioग_लिखो32(CREG_CORE_IF_CLK_DIV_2, clk->spec_regs);

	hsdk_pll_set_cfg(clk, cfg);

	/*
	 * Wait until CGU relocks and check error status.
	 * If after समयout CGU is unlocked yet वापस error.
	 */
	udelay(HSDK_PLL_MAX_LOCK_TIME);
	अगर (!hsdk_pll_is_locked(clk))
		वापस -ETIMEDOUT;

	अगर (hsdk_pll_is_err(clk))
		वापस -EINVAL;

	/*
	 * Program भागider to भाग-by-1 अगर we succesfuly set core घड़ी below
	 * 500MHz threshold.
	 */
	अगर (rate <= CORE_IF_CLK_THRESHOLD_HZ)
		ioग_लिखो32(CREG_CORE_IF_CLK_DIV_1, clk->spec_regs);

	वापस 0;
पूर्ण

अटल पूर्णांक hsdk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक i;
	काष्ठा hsdk_pll_clk *clk = to_hsdk_pll_clk(hw);
	स्थिर काष्ठा hsdk_pll_cfg *pll_cfg = clk->pll_devdata->pll_cfg;

	क्रम (i = 0; pll_cfg[i].rate != 0; i++) अणु
		अगर (pll_cfg[i].rate == rate) अणु
			वापस clk->pll_devdata->update_rate(clk, rate,
							     &pll_cfg[i]);
		पूर्ण
	पूर्ण

	dev_err(clk->dev, "invalid rate=%ld, parent_rate=%ld\n", rate,
			parent_rate);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops hsdk_pll_ops = अणु
	.recalc_rate = hsdk_pll_recalc_rate,
	.round_rate = hsdk_pll_round_rate,
	.set_rate = hsdk_pll_set_rate,
पूर्ण;

अटल पूर्णांक hsdk_pll_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *mem;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा hsdk_pll_clk *pll_clk;
	काष्ठा clk_init_data init = अणु पूर्ण;
	काष्ठा device *dev = &pdev->dev;

	pll_clk = devm_kzalloc(dev, माप(*pll_clk), GFP_KERNEL);
	अगर (!pll_clk)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pll_clk->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(pll_clk->regs))
		वापस PTR_ERR(pll_clk->regs);

	init.name = dev->of_node->name;
	init.ops = &hsdk_pll_ops;
	parent_name = of_clk_get_parent_name(dev->of_node, 0);
	init.parent_names = &parent_name;
	num_parents = of_clk_get_parent_count(dev->of_node);
	अगर (num_parents == 0 || num_parents > CGU_PLL_SOURCE_MAX) अणु
		dev_err(dev, "wrong clock parents number: %u\n", num_parents);
		वापस -EINVAL;
	पूर्ण
	init.num_parents = num_parents;

	pll_clk->hw.init = &init;
	pll_clk->dev = dev;
	pll_clk->pll_devdata = of_device_get_match_data(dev);

	अगर (!pll_clk->pll_devdata) अणु
		dev_err(dev, "No OF match data provided\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_clk_hw_रेजिस्टर(dev, &pll_clk->hw);
	अगर (ret) अणु
		dev_err(dev, "failed to register %s clock\n", init.name);
		वापस ret;
	पूर्ण

	वापस of_clk_add_hw_provider(dev->of_node, of_clk_hw_simple_get,
			&pll_clk->hw);
पूर्ण

अटल पूर्णांक hsdk_pll_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल व्योम __init of_hsdk_pll_clk_setup(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा hsdk_pll_clk *pll_clk;
	काष्ठा clk_init_data init = अणु पूर्ण;

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (!pll_clk)
		वापस;

	pll_clk->regs = of_iomap(node, 0);
	अगर (!pll_clk->regs) अणु
		pr_err("failed to map pll registers\n");
		जाओ err_मुक्त_pll_clk;
	पूर्ण

	pll_clk->spec_regs = of_iomap(node, 1);
	अगर (!pll_clk->spec_regs) अणु
		pr_err("failed to map pll registers\n");
		जाओ err_unmap_comm_regs;
	पूर्ण

	init.name = node->name;
	init.ops = &hsdk_pll_ops;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	num_parents = of_clk_get_parent_count(node);
	अगर (num_parents > CGU_PLL_SOURCE_MAX) अणु
		pr_err("too much clock parents: %u\n", num_parents);
		जाओ err_unmap_spec_regs;
	पूर्ण
	init.num_parents = num_parents;

	pll_clk->hw.init = &init;
	pll_clk->pll_devdata = &core_pll_devdata;

	ret = clk_hw_रेजिस्टर(शून्य, &pll_clk->hw);
	अगर (ret) अणु
		pr_err("failed to register %pOFn clock\n", node);
		जाओ err_unmap_spec_regs;
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, &pll_clk->hw);
	अगर (ret) अणु
		pr_err("failed to add hw provider for %pOFn clock\n", node);
		जाओ err_unmap_spec_regs;
	पूर्ण

	वापस;

err_unmap_spec_regs:
	iounmap(pll_clk->spec_regs);
err_unmap_comm_regs:
	iounmap(pll_clk->regs);
err_मुक्त_pll_clk:
	kमुक्त(pll_clk);
पूर्ण

/* Core PLL needed early क्रम ARC cpus समयrs */
CLK_OF_DECLARE(hsdk_pll_घड़ी, "snps,hsdk-core-pll-clock",
of_hsdk_pll_clk_setup);

अटल स्थिर काष्ठा of_device_id hsdk_pll_clk_id[] = अणु
	अणु .compatible = "snps,hsdk-gp-pll-clock", .data = &sdt_pll_devdataपूर्ण,
	अणु .compatible = "snps,hsdk-hdmi-pll-clock", .data = &hdmi_pll_devdataपूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver hsdk_pll_clk_driver = अणु
	.driver = अणु
		.name = "hsdk-gp-pll-clock",
		.of_match_table = hsdk_pll_clk_id,
	पूर्ण,
	.probe = hsdk_pll_clk_probe,
	.हटाओ = hsdk_pll_clk_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(hsdk_pll_clk_driver);
