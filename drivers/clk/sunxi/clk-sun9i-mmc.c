<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Chen-Yu Tsai
 *
 * Chen-Yu Tsai	<wens@csie.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा SUN9I_MMC_WIDTH		4

#घोषणा SUN9I_MMC_GATE_BIT	16
#घोषणा SUN9I_MMC_RESET_BIT	18

काष्ठा sun9i_mmc_clk_data अणु
	spinlock_t			lock;
	व्योम __iomem			*membase;
	काष्ठा clk			*clk;
	काष्ठा reset_control		*reset;
	काष्ठा clk_onecell_data		clk_data;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल पूर्णांक sun9i_mmc_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा sun9i_mmc_clk_data *data = container_of(rcdev,
						       काष्ठा sun9i_mmc_clk_data,
						       rcdev);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = data->membase + SUN9I_MMC_WIDTH * id;
	u32 val;

	clk_prepare_enable(data->clk);
	spin_lock_irqsave(&data->lock, flags);

	val = पढ़ोl(reg);
	ग_लिखोl(val & ~BIT(SUN9I_MMC_RESET_BIT), reg);

	spin_unlock_irqrestore(&data->lock, flags);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sun9i_mmc_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा sun9i_mmc_clk_data *data = container_of(rcdev,
						       काष्ठा sun9i_mmc_clk_data,
						       rcdev);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = data->membase + SUN9I_MMC_WIDTH * id;
	u32 val;

	clk_prepare_enable(data->clk);
	spin_lock_irqsave(&data->lock, flags);

	val = पढ़ोl(reg);
	ग_लिखोl(val | BIT(SUN9I_MMC_RESET_BIT), reg);

	spin_unlock_irqrestore(&data->lock, flags);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sun9i_mmc_reset_reset(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	sun9i_mmc_reset_निश्चित(rcdev, id);
	udelay(10);
	sun9i_mmc_reset_deनिश्चित(rcdev, id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops sun9i_mmc_reset_ops = अणु
	.निश्चित		= sun9i_mmc_reset_निश्चित,
	.deनिश्चित	= sun9i_mmc_reset_deनिश्चित,
	.reset		= sun9i_mmc_reset_reset,
पूर्ण;

अटल पूर्णांक sun9i_a80_mmc_config_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sun9i_mmc_clk_data *data;
	काष्ठा clk_onecell_data *clk_data;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *clk_parent;
	काष्ठा resource *r;
	पूर्णांक count, i, ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_init(&data->lock);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	/* one घड़ी/reset pair per word */
	count = DIV_ROUND_UP((resource_size(r)), SUN9I_MMC_WIDTH);
	data->membase = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(data->membase))
		वापस PTR_ERR(data->membase);

	clk_data = &data->clk_data;
	clk_data->clk_num = count;
	clk_data->clks = devm_kसुस्मृति(&pdev->dev, count, माप(काष्ठा clk *),
				      GFP_KERNEL);
	अगर (!clk_data->clks)
		वापस -ENOMEM;

	data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(data->clk)) अणु
		dev_err(&pdev->dev, "Could not get clock\n");
		वापस PTR_ERR(data->clk);
	पूर्ण

	data->reset = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(data->reset)) अणु
		dev_err(&pdev->dev, "Could not get reset control\n");
		वापस PTR_ERR(data->reset);
	पूर्ण

	ret = reset_control_deनिश्चित(data->reset);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Reset deassert err %d\n", ret);
		वापस ret;
	पूर्ण

	clk_parent = __clk_get_name(data->clk);
	क्रम (i = 0; i < count; i++) अणु
		of_property_पढ़ो_string_index(np, "clock-output-names",
					      i, &clk_name);

		clk_data->clks[i] = clk_रेजिस्टर_gate(&pdev->dev, clk_name,
						      clk_parent, 0,
						      data->membase + SUN9I_MMC_WIDTH * i,
						      SUN9I_MMC_GATE_BIT, 0,
						      &data->lock);

		अगर (IS_ERR(clk_data->clks[i])) अणु
			ret = PTR_ERR(clk_data->clks[i]);
			जाओ err_clk_रेजिस्टर;
		पूर्ण
	पूर्ण

	ret = of_clk_add_provider(np, of_clk_src_onecell_get, clk_data);
	अगर (ret)
		जाओ err_clk_provider;

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = count;
	data->rcdev.ops = &sun9i_mmc_reset_ops;
	data->rcdev.of_node = pdev->dev.of_node;

	ret = reset_controller_रेजिस्टर(&data->rcdev);
	अगर (ret)
		जाओ err_rc_reg;

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;

err_rc_reg:
	of_clk_del_provider(np);

err_clk_provider:
	क्रम (i = 0; i < count; i++)
		clk_unरेजिस्टर(clk_data->clks[i]);

err_clk_रेजिस्टर:
	reset_control_निश्चित(data->reset);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun9i_a80_mmc_config_clk_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun9i-a80-mmc-config-clk" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun9i_a80_mmc_config_clk_driver = अणु
	.driver = अणु
		.name = "sun9i-a80-mmc-config-clk",
		.suppress_bind_attrs = true,
		.of_match_table = sun9i_a80_mmc_config_clk_dt_ids,
	पूर्ण,
	.probe = sun9i_a80_mmc_config_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sun9i_a80_mmc_config_clk_driver);
