<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Marvell Armada 37xx SoC Time Base Generator घड़ीs
 *
 * Copyright (C) 2016 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा NUM_TBG	    4

#घोषणा TBG_CTRL0		0x4
#घोषणा TBG_CTRL1		0x8
#घोषणा TBG_CTRL7		0x20
#घोषणा TBG_CTRL8		0x30

#घोषणा TBG_DIV_MASK		0x1FF

#घोषणा TBG_A_REFDIV		0
#घोषणा TBG_B_REFDIV		16

#घोषणा TBG_A_FBDIV		2
#घोषणा TBG_B_FBDIV		18

#घोषणा TBG_A_VCODIV_SE		0
#घोषणा TBG_B_VCODIV_SE		16

#घोषणा TBG_A_VCODIV_DIFF	1
#घोषणा TBG_B_VCODIV_DIFF	17

काष्ठा tbg_def अणु
	अक्षर *name;
	u32 refभाग_offset;
	u32 fbभाग_offset;
	u32 vcoभाग_reg;
	u32 vcoभाग_offset;
पूर्ण;

अटल स्थिर काष्ठा tbg_def tbg[NUM_TBG] = अणु
	अणु"TBG-A-P", TBG_A_REFDIV, TBG_A_FBDIV, TBG_CTRL8, TBG_A_VCODIV_DIFFपूर्ण,
	अणु"TBG-B-P", TBG_B_REFDIV, TBG_B_FBDIV, TBG_CTRL8, TBG_B_VCODIV_DIFFपूर्ण,
	अणु"TBG-A-S", TBG_A_REFDIV, TBG_A_FBDIV, TBG_CTRL1, TBG_A_VCODIV_SEपूर्ण,
	अणु"TBG-B-S", TBG_B_REFDIV, TBG_B_FBDIV, TBG_CTRL1, TBG_B_VCODIV_SEपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक tbg_get_mult(व्योम __iomem *reg, स्थिर काष्ठा tbg_def *ptbg)
अणु
	u32 val;

	val = पढ़ोl(reg + TBG_CTRL0);

	वापस ((val >> ptbg->fbभाग_offset) & TBG_DIV_MASK) << 2;
पूर्ण

अटल अचिन्हित पूर्णांक tbg_get_भाग(व्योम __iomem *reg, स्थिर काष्ठा tbg_def *ptbg)
अणु
	u32 val;
	अचिन्हित पूर्णांक भाग;

	val = पढ़ोl(reg + TBG_CTRL7);

	भाग = (val >> ptbg->refभाग_offset) & TBG_DIV_MASK;
	अगर (भाग == 0)
		भाग = 1;
	val = पढ़ोl(reg + ptbg->vcoभाग_reg);

	भाग *= 1 << ((val >>  ptbg->vcoभाग_offset) & TBG_DIV_MASK);

	वापस भाग;
पूर्ण


अटल पूर्णांक armada_3700_tbg_घड़ी_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clk_hw_onecell_data *hw_tbg_data;
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *parent_name;
	काष्ठा resource *res;
	काष्ठा clk *parent;
	व्योम __iomem *reg;
	पूर्णांक i, ret;

	hw_tbg_data = devm_kzalloc(&pdev->dev,
				   काष्ठा_size(hw_tbg_data, hws, NUM_TBG),
				   GFP_KERNEL);
	अगर (!hw_tbg_data)
		वापस -ENOMEM;
	hw_tbg_data->num = NUM_TBG;
	platक्रमm_set_drvdata(pdev, hw_tbg_data);

	parent = clk_get(dev, शून्य);
	अगर (IS_ERR(parent)) अणु
		dev_err(dev, "Could get the clock parent\n");
		वापस -EINVAL;
	पूर्ण
	parent_name = __clk_get_name(parent);
	clk_put(parent);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	क्रम (i = 0; i < NUM_TBG; i++) अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक mult, भाग;

		name = tbg[i].name;
		mult = tbg_get_mult(reg, &tbg[i]);
		भाग = tbg_get_भाग(reg, &tbg[i]);
		hw_tbg_data->hws[i] = clk_hw_रेजिस्टर_fixed_factor(शून्य, name,
						parent_name, 0, mult, भाग);
		अगर (IS_ERR(hw_tbg_data->hws[i]))
			dev_err(dev, "Can't register TBG clock %s\n", name);
	पूर्ण

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, hw_tbg_data);

	वापस ret;
पूर्ण

अटल पूर्णांक armada_3700_tbg_घड़ी_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा clk_hw_onecell_data *hw_tbg_data = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);
	क्रम (i = 0; i < hw_tbg_data->num; i++)
		clk_hw_unरेजिस्टर_fixed_factor(hw_tbg_data->hws[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id armada_3700_tbg_घड़ी_of_match[] = अणु
	अणु .compatible = "marvell,armada-3700-tbg-clock", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver armada_3700_tbg_घड़ी_driver = अणु
	.probe = armada_3700_tbg_घड़ी_probe,
	.हटाओ = armada_3700_tbg_घड़ी_हटाओ,
	.driver		= अणु
		.name	= "marvell-armada-3700-tbg-clock",
		.of_match_table = armada_3700_tbg_घड़ी_of_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(armada_3700_tbg_घड़ी_driver);
