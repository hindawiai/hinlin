<शैली गुरु>
/*
 * Synopsys AXS10X SDP Generic PLL घड़ी driver
 *
 * Copyright (C) 2017 Synopsys
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

/* PLL रेजिस्टरs addresses */
#घोषणा PLL_REG_IDIV	0x0
#घोषणा PLL_REG_FBDIV	0x4
#घोषणा PLL_REG_ODIV	0x8

/*
 * Bit fields of the PLL IDIV/FBDIV/ODIV रेजिस्टरs:
 *  ________________________________________________________________________
 * |31                15|    14    |   13   |  12  |11         6|5         0|
 * |-------RESRVED------|-NOUPDATE-|-BYPASS-|-EDGE-|--HIGHTIME--|--LOWTIME--|
 * |____________________|__________|________|______|____________|___________|
 *
 * Following macros determine the way of access to these रेजिस्टरs
 * They should be set up only using the macros.
 * reg should be an u32 variable.
 */

#घोषणा PLL_REG_GET_LOW(reg)			\
	(((reg) & (0x3F << 0)) >> 0)
#घोषणा PLL_REG_GET_HIGH(reg)			\
	(((reg) & (0x3F << 6)) >> 6)
#घोषणा PLL_REG_GET_EDGE(reg)			\
	(((reg) & (BIT(12))) ? 1 : 0)
#घोषणा PLL_REG_GET_BYPASS(reg)			\
	(((reg) & (BIT(13))) ? 1 : 0)
#घोषणा PLL_REG_GET_NOUPD(reg)			\
	(((reg) & (BIT(14))) ? 1 : 0)
#घोषणा PLL_REG_GET_PAD(reg)			\
	(((reg) & (0x1FFFF << 15)) >> 15)

#घोषणा PLL_REG_SET_LOW(reg, value)		\
	अणु reg |= (((value) & 0x3F) << 0); पूर्ण
#घोषणा PLL_REG_SET_HIGH(reg, value)		\
	अणु reg |= (((value) & 0x3F) << 6); पूर्ण
#घोषणा PLL_REG_SET_EDGE(reg, value)		\
	अणु reg |= (((value) & 0x01) << 12); पूर्ण
#घोषणा PLL_REG_SET_BYPASS(reg, value)		\
	अणु reg |= (((value) & 0x01) << 13); पूर्ण
#घोषणा PLL_REG_SET_NOUPD(reg, value)		\
	अणु reg |= (((value) & 0x01) << 14); पूर्ण
#घोषणा PLL_REG_SET_PAD(reg, value)		\
	अणु reg |= (((value) & 0x1FFFF) << 15); पूर्ण

#घोषणा PLL_LOCK	BIT(0)
#घोषणा PLL_ERROR	BIT(1)
#घोषणा PLL_MAX_LOCK_TIME 100 /* 100 us */

काष्ठा axs10x_pll_cfg अणु
	u32 rate;
	u32 iभाग;
	u32 fbभाग;
	u32 oभाग;
पूर्ण;

अटल स्थिर काष्ठा axs10x_pll_cfg arc_pll_cfg[] = अणु
	अणु 33333333,  1, 1,  1 पूर्ण,
	अणु 50000000,  1, 30, 20 पूर्ण,
	अणु 75000000,  2, 45, 10 पूर्ण,
	अणु 90000000,  2, 54, 10 पूर्ण,
	अणु 100000000, 1, 30, 10 पूर्ण,
	अणु 125000000, 2, 45, 6 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा axs10x_pll_cfg pgu_pll_cfg[] = अणु
	अणु 25200000, 1, 84, 90 पूर्ण,
	अणु 50000000, 1, 100, 54 पूर्ण,
	अणु 74250000, 1, 44, 16 पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा axs10x_pll_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	व्योम __iomem *lock;
	स्थिर काष्ठा axs10x_pll_cfg *pll_cfg;
	काष्ठा device *dev;
पूर्ण;

अटल अंतरभूत व्योम axs10x_pll_ग_लिखो(काष्ठा axs10x_pll_clk *clk, u32 reg,
				    u32 val)
अणु
	ioग_लिखो32(val, clk->base + reg);
पूर्ण

अटल अंतरभूत u32 axs10x_pll_पढ़ो(काष्ठा axs10x_pll_clk *clk, u32 reg)
अणु
	वापस ioपढ़ो32(clk->base + reg);
पूर्ण

अटल अंतरभूत काष्ठा axs10x_pll_clk *to_axs10x_pll_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा axs10x_pll_clk, hw);
पूर्ण

अटल अंतरभूत u32 axs10x_भाग_get_value(u32 reg)
अणु
	अगर (PLL_REG_GET_BYPASS(reg))
		वापस 1;

	वापस PLL_REG_GET_HIGH(reg) + PLL_REG_GET_LOW(reg);
पूर्ण

अटल अंतरभूत u32 axs10x_encode_भाग(अचिन्हित पूर्णांक id, पूर्णांक upd)
अणु
	u32 भाग = 0;

	PLL_REG_SET_LOW(भाग, (id % 2 == 0) ? id >> 1 : (id >> 1) + 1);
	PLL_REG_SET_HIGH(भाग, id >> 1);
	PLL_REG_SET_EDGE(भाग, id % 2);
	PLL_REG_SET_BYPASS(भाग, id == 1 ? 1 : 0);
	PLL_REG_SET_NOUPD(भाग, upd == 0 ? 1 : 0);

	वापस भाग;
पूर्ण

अटल अचिन्हित दीर्घ axs10x_pll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	u64 rate;
	u32 iभाग, fbभाग, oभाग;
	काष्ठा axs10x_pll_clk *clk = to_axs10x_pll_clk(hw);

	iभाग = axs10x_भाग_get_value(axs10x_pll_पढ़ो(clk, PLL_REG_IDIV));
	fbभाग = axs10x_भाग_get_value(axs10x_pll_पढ़ो(clk, PLL_REG_FBDIV));
	oभाग = axs10x_भाग_get_value(axs10x_pll_पढ़ो(clk, PLL_REG_ODIV));

	rate = (u64)parent_rate * fbभाग;
	करो_भाग(rate, iभाग * oभाग);

	वापस rate;
पूर्ण

अटल दीर्घ axs10x_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i;
	दीर्घ best_rate;
	काष्ठा axs10x_pll_clk *clk = to_axs10x_pll_clk(hw);
	स्थिर काष्ठा axs10x_pll_cfg *pll_cfg = clk->pll_cfg;

	अगर (pll_cfg[0].rate == 0)
		वापस -EINVAL;

	best_rate = pll_cfg[0].rate;

	क्रम (i = 1; pll_cfg[i].rate != 0; i++) अणु
		अगर (असल(rate - pll_cfg[i].rate) < असल(rate - best_rate))
			best_rate = pll_cfg[i].rate;
	पूर्ण

	वापस best_rate;
पूर्ण

अटल पूर्णांक axs10x_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक i;
	काष्ठा axs10x_pll_clk *clk = to_axs10x_pll_clk(hw);
	स्थिर काष्ठा axs10x_pll_cfg *pll_cfg = clk->pll_cfg;

	क्रम (i = 0; pll_cfg[i].rate != 0; i++) अणु
		अगर (pll_cfg[i].rate == rate) अणु
			axs10x_pll_ग_लिखो(clk, PLL_REG_IDIV,
					 axs10x_encode_भाग(pll_cfg[i].iभाग, 0));
			axs10x_pll_ग_लिखो(clk, PLL_REG_FBDIV,
					 axs10x_encode_भाग(pll_cfg[i].fbभाग, 0));
			axs10x_pll_ग_लिखो(clk, PLL_REG_ODIV,
					 axs10x_encode_भाग(pll_cfg[i].oभाग, 1));

			/*
			 * Wait until CGU relocks and check error status.
			 * If after समयout CGU is unlocked yet वापस error
			 */
			udelay(PLL_MAX_LOCK_TIME);
			अगर (!(ioपढ़ो32(clk->lock) & PLL_LOCK))
				वापस -ETIMEDOUT;

			अगर (ioपढ़ो32(clk->lock) & PLL_ERROR)
				वापस -EINVAL;

			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(clk->dev, "invalid rate=%ld, parent_rate=%ld\n", rate,
			parent_rate);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops axs10x_pll_ops = अणु
	.recalc_rate = axs10x_pll_recalc_rate,
	.round_rate = axs10x_pll_round_rate,
	.set_rate = axs10x_pll_set_rate,
पूर्ण;

अटल पूर्णांक axs10x_pll_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *parent_name;
	काष्ठा axs10x_pll_clk *pll_clk;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret;

	pll_clk = devm_kzalloc(dev, माप(*pll_clk), GFP_KERNEL);
	अगर (!pll_clk)
		वापस -ENOMEM;

	pll_clk->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pll_clk->base))
		वापस PTR_ERR(pll_clk->base);

	pll_clk->lock = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(pll_clk->lock))
		वापस PTR_ERR(pll_clk->lock);

	init.name = dev->of_node->name;
	init.ops = &axs10x_pll_ops;
	parent_name = of_clk_get_parent_name(dev->of_node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pll_clk->hw.init = &init;
	pll_clk->dev = dev;
	pll_clk->pll_cfg = of_device_get_match_data(dev);

	अगर (!pll_clk->pll_cfg) अणु
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

अटल पूर्णांक axs10x_pll_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल व्योम __init of_axs10x_pll_clk_setup(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *parent_name;
	काष्ठा axs10x_pll_clk *pll_clk;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret;

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (!pll_clk)
		वापस;

	pll_clk->base = of_iomap(node, 0);
	अगर (!pll_clk->base) अणु
		pr_err("failed to map pll div registers\n");
		जाओ err_मुक्त_pll_clk;
	पूर्ण

	pll_clk->lock = of_iomap(node, 1);
	अगर (!pll_clk->lock) अणु
		pr_err("failed to map pll lock register\n");
		जाओ err_unmap_base;
	पूर्ण

	init.name = node->name;
	init.ops = &axs10x_pll_ops;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	init.num_parents = parent_name ? 1 : 0;
	pll_clk->hw.init = &init;
	pll_clk->pll_cfg = arc_pll_cfg;

	ret = clk_hw_रेजिस्टर(शून्य, &pll_clk->hw);
	अगर (ret) अणु
		pr_err("failed to register %pOFn clock\n", node);
		जाओ err_unmap_lock;
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, &pll_clk->hw);
	अगर (ret) अणु
		pr_err("failed to add hw provider for %pOFn clock\n", node);
		जाओ err_unरेजिस्टर_clk;
	पूर्ण

	वापस;

err_unरेजिस्टर_clk:
	clk_hw_unरेजिस्टर(&pll_clk->hw);
err_unmap_lock:
	iounmap(pll_clk->lock);
err_unmap_base:
	iounmap(pll_clk->base);
err_मुक्त_pll_clk:
	kमुक्त(pll_clk);
पूर्ण
CLK_OF_DECLARE(axs10x_pll_घड़ी, "snps,axs10x-arc-pll-clock",
	       of_axs10x_pll_clk_setup);

अटल स्थिर काष्ठा of_device_id axs10x_pll_clk_id[] = अणु
	अणु .compatible = "snps,axs10x-pgu-pll-clock", .data = &pgu_pll_cfgपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axs10x_pll_clk_id);

अटल काष्ठा platक्रमm_driver axs10x_pll_clk_driver = अणु
	.driver = अणु
		.name = "axs10x-pll-clock",
		.of_match_table = axs10x_pll_clk_id,
	पूर्ण,
	.probe = axs10x_pll_clk_probe,
	.हटाओ = axs10x_pll_clk_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(axs10x_pll_clk_driver);

MODULE_AUTHOR("Vlad Zakharov <vzakhar@synopsys.com>");
MODULE_DESCRIPTION("Synopsys AXS10X SDP Generic PLL Clock Driver");
MODULE_LICENSE("GPL v2");
