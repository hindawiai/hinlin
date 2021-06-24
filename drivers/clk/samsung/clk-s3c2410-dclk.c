<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Common Clock Framework support क्रम s3c24xx बाह्यal घड़ी output.
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/clk-s3c2410.h>
#समावेश <linux/module.h>
#समावेश "clk.h"

#घोषणा MUX_DCLK0	0
#घोषणा MUX_DCLK1	1
#घोषणा DIV_DCLK0	2
#घोषणा DIV_DCLK1	3
#घोषणा GATE_DCLK0	4
#घोषणा GATE_DCLK1	5
#घोषणा MUX_CLKOUT0	6
#घोषणा MUX_CLKOUT1	7
#घोषणा DCLK_MAX_CLKS	(MUX_CLKOUT1 + 1)

क्रमागत supported_socs अणु
	S3C2410,
	S3C2412,
	S3C2440,
	S3C2443,
पूर्ण;

काष्ठा s3c24xx_dclk_drv_data अणु
	स्थिर अक्षर **clkout0_parent_names;
	पूर्णांक clkout0_num_parents;
	स्थिर अक्षर **clkout1_parent_names;
	पूर्णांक clkout1_num_parents;
	स्थिर अक्षर **mux_parent_names;
	पूर्णांक mux_num_parents;
पूर्ण;

/*
 * Clock क्रम output-parent selection in misccr
 */

काष्ठा s3c24xx_clkout अणु
	काष्ठा clk_hw		hw;
	u32			mask;
	u8			shअगरt;
	अचिन्हित पूर्णांक (*modअगरy_misccr)(अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक chg);
पूर्ण;

#घोषणा to_s3c24xx_clkout(_hw) container_of(_hw, काष्ठा s3c24xx_clkout, hw)

अटल u8 s3c24xx_clkout_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा s3c24xx_clkout *clkout = to_s3c24xx_clkout(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	u32 val;

	val = clkout->modअगरy_misccr(0, 0) >> clkout->shअगरt;
	val >>= clkout->shअगरt;
	val &= clkout->mask;

	अगर (val >= num_parents)
		वापस -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक s3c24xx_clkout_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा s3c24xx_clkout *clkout = to_s3c24xx_clkout(hw);

	clkout->modअगरy_misccr((clkout->mask << clkout->shअगरt),
			      (index << clkout->shअगरt));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops s3c24xx_clkout_ops = अणु
	.get_parent = s3c24xx_clkout_get_parent,
	.set_parent = s3c24xx_clkout_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_hw *s3c24xx_रेजिस्टर_clkout(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर **parent_names, u8 num_parents,
		u8 shअगरt, u32 mask)
अणु
	काष्ठा s3c2410_clk_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा s3c24xx_clkout *clkout;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!pdata)
		वापस ERR_PTR(-EINVAL);

	/* allocate the clkout */
	clkout = kzalloc(माप(*clkout), GFP_KERNEL);
	अगर (!clkout)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &s3c24xx_clkout_ops;
	init.flags = 0;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	clkout->shअगरt = shअगरt;
	clkout->mask = mask;
	clkout->hw.init = &init;
	clkout->modअगरy_misccr = pdata->modअगरy_misccr;

	ret = clk_hw_रेजिस्टर(dev, &clkout->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &clkout->hw;
पूर्ण

/*
 * dclk and clkout init
 */

काष्ठा s3c24xx_dclk अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा notअगरier_block dclk0_भाग_change_nb;
	काष्ठा notअगरier_block dclk1_भाग_change_nb;
	spinlock_t dclk_lock;
	अचिन्हित दीर्घ reg_save;
	/* clk_data must be the last entry in the काष्ठाure */
	काष्ठा clk_hw_onecell_data clk_data;
पूर्ण;

#घोषणा to_s3c24xx_dclk0(x) \
		container_of(x, काष्ठा s3c24xx_dclk, dclk0_भाग_change_nb)

#घोषणा to_s3c24xx_dclk1(x) \
		container_of(x, काष्ठा s3c24xx_dclk, dclk1_भाग_change_nb)

अटल स्थिर अक्षर *dclk_s3c2410_p[] = अणु "pclk", "uclk" पूर्ण;
अटल स्थिर अक्षर *clkout0_s3c2410_p[] = अणु "mpll", "upll", "fclk", "hclk", "pclk",
			     "gate_dclk0" पूर्ण;
अटल स्थिर अक्षर *clkout1_s3c2410_p[] = अणु "mpll", "upll", "fclk", "hclk", "pclk",
			     "gate_dclk1" पूर्ण;

अटल स्थिर अक्षर *clkout0_s3c2412_p[] = अणु "mpll", "upll", "rtc_clkout",
			     "hclk", "pclk", "gate_dclk0" पूर्ण;
अटल स्थिर अक्षर *clkout1_s3c2412_p[] = अणु "xti", "upll", "fclk", "hclk", "pclk",
			     "gate_dclk1" पूर्ण;

अटल स्थिर अक्षर *clkout0_s3c2440_p[] = अणु "xti", "upll", "fclk", "hclk", "pclk",
			     "gate_dclk0" पूर्ण;
अटल स्थिर अक्षर *clkout1_s3c2440_p[] = अणु "mpll", "upll", "rtc_clkout",
			     "hclk", "pclk", "gate_dclk1" पूर्ण;

अटल स्थिर अक्षर *dclk_s3c2443_p[] = अणु "pclk", "epll" पूर्ण;
अटल स्थिर अक्षर *clkout0_s3c2443_p[] = अणु "xti", "epll", "armclk", "hclk", "pclk",
			     "gate_dclk0" पूर्ण;
अटल स्थिर अक्षर *clkout1_s3c2443_p[] = अणु "dummy", "epll", "rtc_clkout",
			     "hclk", "pclk", "gate_dclk1" पूर्ण;

#घोषणा DCLKCON_DCLK_DIV_MASK		0xf
#घोषणा DCLKCON_DCLK0_DIV_SHIFT		4
#घोषणा DCLKCON_DCLK0_CMP_SHIFT		8
#घोषणा DCLKCON_DCLK1_DIV_SHIFT		20
#घोषणा DCLKCON_DCLK1_CMP_SHIFT		24

अटल व्योम s3c24xx_dclk_update_cmp(काष्ठा s3c24xx_dclk *s3c24xx_dclk,
				    पूर्णांक भाग_shअगरt, पूर्णांक cmp_shअगरt)
अणु
	अचिन्हित दीर्घ flags = 0;
	u32 dclk_con, भाग, cmp;

	spin_lock_irqsave(&s3c24xx_dclk->dclk_lock, flags);

	dclk_con = पढ़ोl_relaxed(s3c24xx_dclk->base);

	भाग = ((dclk_con >> भाग_shअगरt) & DCLKCON_DCLK_DIV_MASK) + 1;
	cmp = ((भाग + 1) / 2) - 1;

	dclk_con &= ~(DCLKCON_DCLK_DIV_MASK << cmp_shअगरt);
	dclk_con |= (cmp << cmp_shअगरt);

	ग_लिखोl_relaxed(dclk_con, s3c24xx_dclk->base);

	spin_unlock_irqrestore(&s3c24xx_dclk->dclk_lock, flags);
पूर्ण

अटल पूर्णांक s3c24xx_dclk0_भाग_notअगरy(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा s3c24xx_dclk *s3c24xx_dclk = to_s3c24xx_dclk0(nb);

	अगर (event == POST_RATE_CHANGE) अणु
		s3c24xx_dclk_update_cmp(s3c24xx_dclk,
			DCLKCON_DCLK0_DIV_SHIFT, DCLKCON_DCLK0_CMP_SHIFT);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक s3c24xx_dclk1_भाग_notअगरy(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा s3c24xx_dclk *s3c24xx_dclk = to_s3c24xx_dclk1(nb);

	अगर (event == POST_RATE_CHANGE) अणु
		s3c24xx_dclk_update_cmp(s3c24xx_dclk,
			DCLKCON_DCLK1_DIV_SHIFT, DCLKCON_DCLK1_CMP_SHIFT);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s3c24xx_dclk_suspend(काष्ठा device *dev)
अणु
	काष्ठा s3c24xx_dclk *s3c24xx_dclk = dev_get_drvdata(dev);

	s3c24xx_dclk->reg_save = पढ़ोl_relaxed(s3c24xx_dclk->base);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_dclk_resume(काष्ठा device *dev)
अणु
	काष्ठा s3c24xx_dclk *s3c24xx_dclk = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(s3c24xx_dclk->reg_save, s3c24xx_dclk->base);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(s3c24xx_dclk_pm_ops,
			 s3c24xx_dclk_suspend, s3c24xx_dclk_resume);

अटल पूर्णांक s3c24xx_dclk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c24xx_dclk *s3c24xx_dclk;
	काष्ठा s3c24xx_dclk_drv_data *dclk_variant;
	काष्ठा clk_hw **clk_table;
	पूर्णांक ret, i;

	s3c24xx_dclk = devm_kzalloc(&pdev->dev,
				    काष्ठा_size(s3c24xx_dclk, clk_data.hws,
						DCLK_MAX_CLKS),
				    GFP_KERNEL);
	अगर (!s3c24xx_dclk)
		वापस -ENOMEM;

	clk_table = s3c24xx_dclk->clk_data.hws;

	s3c24xx_dclk->dev = &pdev->dev;
	s3c24xx_dclk->clk_data.num = DCLK_MAX_CLKS;
	platक्रमm_set_drvdata(pdev, s3c24xx_dclk);
	spin_lock_init(&s3c24xx_dclk->dclk_lock);

	s3c24xx_dclk->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(s3c24xx_dclk->base))
		वापस PTR_ERR(s3c24xx_dclk->base);

	dclk_variant = (काष्ठा s3c24xx_dclk_drv_data *)
				platक्रमm_get_device_id(pdev)->driver_data;


	clk_table[MUX_DCLK0] = clk_hw_रेजिस्टर_mux(&pdev->dev, "mux_dclk0",
				dclk_variant->mux_parent_names,
				dclk_variant->mux_num_parents, 0,
				s3c24xx_dclk->base, 1, 1, 0,
				&s3c24xx_dclk->dclk_lock);
	clk_table[MUX_DCLK1] = clk_hw_रेजिस्टर_mux(&pdev->dev, "mux_dclk1",
				dclk_variant->mux_parent_names,
				dclk_variant->mux_num_parents, 0,
				s3c24xx_dclk->base, 17, 1, 0,
				&s3c24xx_dclk->dclk_lock);

	clk_table[DIV_DCLK0] = clk_hw_रेजिस्टर_भागider(&pdev->dev, "div_dclk0",
				"mux_dclk0", 0, s3c24xx_dclk->base,
				4, 4, 0, &s3c24xx_dclk->dclk_lock);
	clk_table[DIV_DCLK1] = clk_hw_रेजिस्टर_भागider(&pdev->dev, "div_dclk1",
				"mux_dclk1", 0, s3c24xx_dclk->base,
				20, 4, 0, &s3c24xx_dclk->dclk_lock);

	clk_table[GATE_DCLK0] = clk_hw_रेजिस्टर_gate(&pdev->dev, "gate_dclk0",
				"div_dclk0", CLK_SET_RATE_PARENT,
				s3c24xx_dclk->base, 0, 0,
				&s3c24xx_dclk->dclk_lock);
	clk_table[GATE_DCLK1] = clk_hw_रेजिस्टर_gate(&pdev->dev, "gate_dclk1",
				"div_dclk1", CLK_SET_RATE_PARENT,
				s3c24xx_dclk->base, 16, 0,
				&s3c24xx_dclk->dclk_lock);

	clk_table[MUX_CLKOUT0] = s3c24xx_रेजिस्टर_clkout(&pdev->dev,
				"clkout0", dclk_variant->clkout0_parent_names,
				dclk_variant->clkout0_num_parents, 4, 7);
	clk_table[MUX_CLKOUT1] = s3c24xx_रेजिस्टर_clkout(&pdev->dev,
				"clkout1", dclk_variant->clkout1_parent_names,
				dclk_variant->clkout1_num_parents, 8, 7);

	क्रम (i = 0; i < DCLK_MAX_CLKS; i++)
		अगर (IS_ERR(clk_table[i])) अणु
			dev_err(&pdev->dev, "clock %d failed to register\n", i);
			ret = PTR_ERR(clk_table[i]);
			जाओ err_clk_रेजिस्टर;
		पूर्ण

	ret = clk_hw_रेजिस्टर_clkdev(clk_table[MUX_DCLK0], "dclk0", शून्य);
	अगर (!ret)
		ret = clk_hw_रेजिस्टर_clkdev(clk_table[MUX_DCLK1], "dclk1",
					     शून्य);
	अगर (!ret)
		ret = clk_hw_रेजिस्टर_clkdev(clk_table[MUX_CLKOUT0],
					     "clkout0", शून्य);
	अगर (!ret)
		ret = clk_hw_रेजिस्टर_clkdev(clk_table[MUX_CLKOUT1],
					     "clkout1", शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register aliases, %d\n", ret);
		जाओ err_clk_रेजिस्टर;
	पूर्ण

	s3c24xx_dclk->dclk0_भाग_change_nb.notअगरier_call =
						s3c24xx_dclk0_भाग_notअगरy;

	s3c24xx_dclk->dclk1_भाग_change_nb.notअगरier_call =
						s3c24xx_dclk1_भाग_notअगरy;

	ret = clk_notअगरier_रेजिस्टर(clk_table[DIV_DCLK0]->clk,
				    &s3c24xx_dclk->dclk0_भाग_change_nb);
	अगर (ret)
		जाओ err_clk_रेजिस्टर;

	ret = clk_notअगरier_रेजिस्टर(clk_table[DIV_DCLK1]->clk,
				    &s3c24xx_dclk->dclk1_भाग_change_nb);
	अगर (ret)
		जाओ err_dclk_notअगरy;

	वापस 0;

err_dclk_notअगरy:
	clk_notअगरier_unरेजिस्टर(clk_table[DIV_DCLK0]->clk,
				&s3c24xx_dclk->dclk0_भाग_change_nb);
err_clk_रेजिस्टर:
	क्रम (i = 0; i < DCLK_MAX_CLKS; i++)
		अगर (clk_table[i] && !IS_ERR(clk_table[i]))
			clk_hw_unरेजिस्टर(clk_table[i]);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c24xx_dclk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c24xx_dclk *s3c24xx_dclk = platक्रमm_get_drvdata(pdev);
	काष्ठा clk_hw **clk_table = s3c24xx_dclk->clk_data.hws;
	पूर्णांक i;

	clk_notअगरier_unरेजिस्टर(clk_table[DIV_DCLK1]->clk,
				&s3c24xx_dclk->dclk1_भाग_change_nb);
	clk_notअगरier_unरेजिस्टर(clk_table[DIV_DCLK0]->clk,
				&s3c24xx_dclk->dclk0_भाग_change_nb);

	क्रम (i = 0; i < DCLK_MAX_CLKS; i++)
		clk_hw_unरेजिस्टर(clk_table[i]);

	वापस 0;
पूर्ण

अटल काष्ठा s3c24xx_dclk_drv_data dclk_variants[] = अणु
	[S3C2410] = अणु
		.clkout0_parent_names = clkout0_s3c2410_p,
		.clkout0_num_parents = ARRAY_SIZE(clkout0_s3c2410_p),
		.clkout1_parent_names = clkout1_s3c2410_p,
		.clkout1_num_parents = ARRAY_SIZE(clkout1_s3c2410_p),
		.mux_parent_names = dclk_s3c2410_p,
		.mux_num_parents = ARRAY_SIZE(dclk_s3c2410_p),
	पूर्ण,
	[S3C2412] = अणु
		.clkout0_parent_names = clkout0_s3c2412_p,
		.clkout0_num_parents = ARRAY_SIZE(clkout0_s3c2412_p),
		.clkout1_parent_names = clkout1_s3c2412_p,
		.clkout1_num_parents = ARRAY_SIZE(clkout1_s3c2412_p),
		.mux_parent_names = dclk_s3c2410_p,
		.mux_num_parents = ARRAY_SIZE(dclk_s3c2410_p),
	पूर्ण,
	[S3C2440] = अणु
		.clkout0_parent_names = clkout0_s3c2440_p,
		.clkout0_num_parents = ARRAY_SIZE(clkout0_s3c2440_p),
		.clkout1_parent_names = clkout1_s3c2440_p,
		.clkout1_num_parents = ARRAY_SIZE(clkout1_s3c2440_p),
		.mux_parent_names = dclk_s3c2410_p,
		.mux_num_parents = ARRAY_SIZE(dclk_s3c2410_p),
	पूर्ण,
	[S3C2443] = अणु
		.clkout0_parent_names = clkout0_s3c2443_p,
		.clkout0_num_parents = ARRAY_SIZE(clkout0_s3c2443_p),
		.clkout1_parent_names = clkout1_s3c2443_p,
		.clkout1_num_parents = ARRAY_SIZE(clkout1_s3c2443_p),
		.mux_parent_names = dclk_s3c2443_p,
		.mux_num_parents = ARRAY_SIZE(dclk_s3c2443_p),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c24xx_dclk_driver_ids[] = अणु
	अणु
		.name		= "s3c2410-dclk",
		.driver_data	= (kernel_uदीर्घ_t)&dclk_variants[S3C2410],
	पूर्ण, अणु
		.name		= "s3c2412-dclk",
		.driver_data	= (kernel_uदीर्घ_t)&dclk_variants[S3C2412],
	पूर्ण, अणु
		.name		= "s3c2440-dclk",
		.driver_data	= (kernel_uदीर्घ_t)&dclk_variants[S3C2440],
	पूर्ण, अणु
		.name		= "s3c2443-dclk",
		.driver_data	= (kernel_uदीर्घ_t)&dclk_variants[S3C2443],
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, s3c24xx_dclk_driver_ids);

अटल काष्ठा platक्रमm_driver s3c24xx_dclk_driver = अणु
	.driver = अणु
		.name			= "s3c24xx-dclk",
		.pm			= &s3c24xx_dclk_pm_ops,
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe = s3c24xx_dclk_probe,
	.हटाओ = s3c24xx_dclk_हटाओ,
	.id_table = s3c24xx_dclk_driver_ids,
पूर्ण;
module_platक्रमm_driver(s3c24xx_dclk_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("Driver for the S3C24XX external clock outputs");
