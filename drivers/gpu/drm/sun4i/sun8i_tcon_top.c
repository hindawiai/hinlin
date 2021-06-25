<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2018 Jernej Skrabec <jernej.skrabec@siol.net> */


#समावेश <linux/bitfield.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/घड़ी/sun8i-tcon-top.h>

#समावेश "sun8i_tcon_top.h"

काष्ठा sun8i_tcon_top_quirks अणु
	bool has_tcon_tv1;
	bool has_dsi;
पूर्ण;

अटल bool sun8i_tcon_top_node_is_tcon_top(काष्ठा device_node *node)
अणु
	वापस !!of_match_node(sun8i_tcon_top_of_table, node);
पूर्ण

पूर्णांक sun8i_tcon_top_set_hdmi_src(काष्ठा device *dev, पूर्णांक tcon)
अणु
	काष्ठा sun8i_tcon_top *tcon_top = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!sun8i_tcon_top_node_is_tcon_top(dev->of_node)) अणु
		dev_err(dev, "Device is not TCON TOP!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (tcon < 2 || tcon > 3) अणु
		dev_err(dev, "TCON index must be 2 or 3!\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&tcon_top->reg_lock, flags);

	val = पढ़ोl(tcon_top->regs + TCON_TOP_GATE_SRC_REG);
	val &= ~TCON_TOP_HDMI_SRC_MSK;
	val |= FIELD_PREP(TCON_TOP_HDMI_SRC_MSK, tcon - 1);
	ग_लिखोl(val, tcon_top->regs + TCON_TOP_GATE_SRC_REG);

	spin_unlock_irqrestore(&tcon_top->reg_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sun8i_tcon_top_set_hdmi_src);

पूर्णांक sun8i_tcon_top_de_config(काष्ठा device *dev, पूर्णांक mixer, पूर्णांक tcon)
अणु
	काष्ठा sun8i_tcon_top *tcon_top = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!sun8i_tcon_top_node_is_tcon_top(dev->of_node)) अणु
		dev_err(dev, "Device is not TCON TOP!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mixer > 1) अणु
		dev_err(dev, "Mixer index is too high!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (tcon > 3) अणु
		dev_err(dev, "TCON index is too high!\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&tcon_top->reg_lock, flags);

	reg = पढ़ोl(tcon_top->regs + TCON_TOP_PORT_SEL_REG);
	अगर (mixer == 0) अणु
		reg &= ~TCON_TOP_PORT_DE0_MSK;
		reg |= FIELD_PREP(TCON_TOP_PORT_DE0_MSK, tcon);
	पूर्ण अन्यथा अणु
		reg &= ~TCON_TOP_PORT_DE1_MSK;
		reg |= FIELD_PREP(TCON_TOP_PORT_DE1_MSK, tcon);
	पूर्ण
	ग_लिखोl(reg, tcon_top->regs + TCON_TOP_PORT_SEL_REG);

	spin_unlock_irqrestore(&tcon_top->reg_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sun8i_tcon_top_de_config);


अटल काष्ठा clk_hw *sun8i_tcon_top_रेजिस्टर_gate(काष्ठा device *dev,
						   स्थिर अक्षर *parent,
						   व्योम __iomem *regs,
						   spinlock_t *lock,
						   u8 bit, पूर्णांक name_index)
अणु
	स्थिर अक्षर *clk_name, *parent_name;
	पूर्णांक ret, index;

	index = of_property_match_string(dev->of_node, "clock-names", parent);
	अगर (index < 0)
		वापस ERR_PTR(index);

	parent_name = of_clk_get_parent_name(dev->of_node, index);

	ret = of_property_पढ़ो_string_index(dev->of_node,
					    "clock-output-names", name_index,
					    &clk_name);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस clk_hw_रेजिस्टर_gate(dev, clk_name, parent_name,
				    CLK_SET_RATE_PARENT,
				    regs + TCON_TOP_GATE_SRC_REG,
				    bit, 0, lock);
पूर्ण;

अटल पूर्णांक sun8i_tcon_top_bind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा sun8i_tcon_top *tcon_top;
	स्थिर काष्ठा sun8i_tcon_top_quirks *quirks;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret, i;

	quirks = of_device_get_match_data(&pdev->dev);

	tcon_top = devm_kzalloc(dev, माप(*tcon_top), GFP_KERNEL);
	अगर (!tcon_top)
		वापस -ENOMEM;

	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, hws, CLK_NUM),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;
	tcon_top->clk_data = clk_data;

	spin_lock_init(&tcon_top->reg_lock);

	tcon_top->rst = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(tcon_top->rst)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(tcon_top->rst);
	पूर्ण

	tcon_top->bus = devm_clk_get(dev, "bus");
	अगर (IS_ERR(tcon_top->bus)) अणु
		dev_err(dev, "Couldn't get the bus clock\n");
		वापस PTR_ERR(tcon_top->bus);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	tcon_top->regs = regs;
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	ret = reset_control_deनिश्चित(tcon_top->rst);
	अगर (ret) अणु
		dev_err(dev, "Could not deassert ctrl reset control\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(tcon_top->bus);
	अगर (ret) अणु
		dev_err(dev, "Could not enable bus clock\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	/*
	 * At least on H6, some रेजिस्टरs have some bits set by शेष
	 * which may cause issues. Clear them here.
	 */
	ग_लिखोl(0, regs + TCON_TOP_PORT_SEL_REG);
	ग_लिखोl(0, regs + TCON_TOP_GATE_SRC_REG);

	/*
	 * TCON TOP has two muxes, which select parent घड़ी क्रम each TCON TV
	 * channel घड़ी. Parent could be either TCON TV or TVE घड़ी. For now
	 * we leave this fixed to TCON TV, since TVE driver क्रम R40 is not yet
	 * implemented. Once it is, graph needs to be traversed to determine
	 * अगर TVE is active on each TCON TV. If it is, mux should be चयनed
	 * to TVE घड़ी parent.
	 */
	clk_data->hws[CLK_TCON_TOP_TV0] =
		sun8i_tcon_top_रेजिस्टर_gate(dev, "tcon-tv0", regs,
					     &tcon_top->reg_lock,
					     TCON_TOP_TCON_TV0_GATE, 0);

	अगर (quirks->has_tcon_tv1)
		clk_data->hws[CLK_TCON_TOP_TV1] =
			sun8i_tcon_top_रेजिस्टर_gate(dev, "tcon-tv1", regs,
						     &tcon_top->reg_lock,
						     TCON_TOP_TCON_TV1_GATE, 1);

	अगर (quirks->has_dsi)
		clk_data->hws[CLK_TCON_TOP_DSI] =
			sun8i_tcon_top_रेजिस्टर_gate(dev, "dsi", regs,
						     &tcon_top->reg_lock,
						     TCON_TOP_TCON_DSI_GATE, 2);

	क्रम (i = 0; i < CLK_NUM; i++)
		अगर (IS_ERR(clk_data->hws[i])) अणु
			ret = PTR_ERR(clk_data->hws[i]);
			जाओ err_unरेजिस्टर_gates;
		पूर्ण

	clk_data->num = CLK_NUM;

	ret = of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
				     clk_data);
	अगर (ret)
		जाओ err_unरेजिस्टर_gates;

	dev_set_drvdata(dev, tcon_top);

	वापस 0;

err_unरेजिस्टर_gates:
	क्रम (i = 0; i < CLK_NUM; i++)
		अगर (!IS_ERR_OR_शून्य(clk_data->hws[i]))
			clk_hw_unरेजिस्टर_gate(clk_data->hws[i]);
	clk_disable_unprepare(tcon_top->bus);
err_निश्चित_reset:
	reset_control_निश्चित(tcon_top->rst);

	वापस ret;
पूर्ण

अटल व्योम sun8i_tcon_top_unbind(काष्ठा device *dev, काष्ठा device *master,
				  व्योम *data)
अणु
	काष्ठा sun8i_tcon_top *tcon_top = dev_get_drvdata(dev);
	काष्ठा clk_hw_onecell_data *clk_data = tcon_top->clk_data;
	पूर्णांक i;

	of_clk_del_provider(dev->of_node);
	क्रम (i = 0; i < CLK_NUM; i++)
		अगर (clk_data->hws[i])
			clk_hw_unरेजिस्टर_gate(clk_data->hws[i]);

	clk_disable_unprepare(tcon_top->bus);
	reset_control_निश्चित(tcon_top->rst);
पूर्ण

अटल स्थिर काष्ठा component_ops sun8i_tcon_top_ops = अणु
	.bind	= sun8i_tcon_top_bind,
	.unbind	= sun8i_tcon_top_unbind,
पूर्ण;

अटल पूर्णांक sun8i_tcon_top_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun8i_tcon_top_ops);
पूर्ण

अटल पूर्णांक sun8i_tcon_top_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun8i_tcon_top_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun8i_tcon_top_quirks sun8i_r40_tcon_top_quirks = अणु
	.has_tcon_tv1	= true,
	.has_dsi	= true,
पूर्ण;

अटल स्थिर काष्ठा sun8i_tcon_top_quirks sun50i_h6_tcon_top_quirks = अणु
	/* Nothing special */
पूर्ण;

/* sun4i_drv uses this list to check अगर a device node is a TCON TOP */
स्थिर काष्ठा of_device_id sun8i_tcon_top_of_table[] = अणु
	अणु
		.compatible = "allwinner,sun8i-r40-tcon-top",
		.data = &sun8i_r40_tcon_top_quirks
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-tcon-top",
		.data = &sun50i_h6_tcon_top_quirks
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_tcon_top_of_table);
EXPORT_SYMBOL(sun8i_tcon_top_of_table);

अटल काष्ठा platक्रमm_driver sun8i_tcon_top_platक्रमm_driver = अणु
	.probe		= sun8i_tcon_top_probe,
	.हटाओ		= sun8i_tcon_top_हटाओ,
	.driver		= अणु
		.name		= "sun8i-tcon-top",
		.of_match_table	= sun8i_tcon_top_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun8i_tcon_top_platक्रमm_driver);

MODULE_AUTHOR("Jernej Skrabec <jernej.skrabec@siol.net>");
MODULE_DESCRIPTION("Allwinner R40 TCON TOP driver");
MODULE_LICENSE("GPL");
