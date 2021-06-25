<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Atom platक्रमm घड़ीs driver क्रम BayTrail and CherryTrail SoCs
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Irina Tirdea <irina.tirdea@पूर्णांकel.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/x86/clk-pmc-atom.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा PLT_CLK_NAME_BASE	"pmc_plt_clk"

#घोषणा PMC_CLK_CTL_OFFSET		0x60
#घोषणा PMC_CLK_CTL_SIZE		4
#घोषणा PMC_CLK_NUM			6
#घोषणा PMC_CLK_CTL_GATED_ON_D3		0x0
#घोषणा PMC_CLK_CTL_FORCE_ON		0x1
#घोषणा PMC_CLK_CTL_FORCE_OFF		0x2
#घोषणा PMC_CLK_CTL_RESERVED		0x3
#घोषणा PMC_MASK_CLK_CTL		GENMASK(1, 0)
#घोषणा PMC_MASK_CLK_FREQ		BIT(2)
#घोषणा PMC_CLK_FREQ_XTAL		(0 << 2)	/* 25 MHz */
#घोषणा PMC_CLK_FREQ_PLL		(1 << 2)	/* 19.2 MHz */

काष्ठा clk_plt_fixed अणु
	काष्ठा clk_hw *clk;
	काष्ठा clk_lookup *lookup;
पूर्ण;

काष्ठा clk_plt अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	काष्ठा clk_lookup *lookup;
	/* protect access to PMC रेजिस्टरs */
	spinlock_t lock;
पूर्ण;

#घोषणा to_clk_plt(_hw) container_of(_hw, काष्ठा clk_plt, hw)

काष्ठा clk_plt_data अणु
	काष्ठा clk_plt_fixed **parents;
	u8 nparents;
	काष्ठा clk_plt *clks[PMC_CLK_NUM];
	काष्ठा clk_lookup *mclk_lookup;
	काष्ठा clk_lookup *ether_clk_lookup;
पूर्ण;

/* Return an index in parent table */
अटल अंतरभूत पूर्णांक plt_reg_to_parent(पूर्णांक reg)
अणु
	चयन (reg & PMC_MASK_CLK_FREQ) अणु
	शेष:
	हाल PMC_CLK_FREQ_XTAL:
		वापस 0;
	हाल PMC_CLK_FREQ_PLL:
		वापस 1;
	पूर्ण
पूर्ण

/* Return clk index of parent */
अटल अंतरभूत पूर्णांक plt_parent_to_reg(पूर्णांक index)
अणु
	चयन (index) अणु
	शेष:
	हाल 0:
		वापस PMC_CLK_FREQ_XTAL;
	हाल 1:
		वापस PMC_CLK_FREQ_PLL;
	पूर्ण
पूर्ण

/* Abstract status in simpler enabled/disabled value */
अटल अंतरभूत पूर्णांक plt_reg_to_enabled(पूर्णांक reg)
अणु
	चयन (reg & PMC_MASK_CLK_CTL) अणु
	हाल PMC_CLK_CTL_GATED_ON_D3:
	हाल PMC_CLK_CTL_FORCE_ON:
		वापस 1;	/* enabled */
	हाल PMC_CLK_CTL_FORCE_OFF:
	हाल PMC_CLK_CTL_RESERVED:
	शेष:
		वापस 0;	/* disabled */
	पूर्ण
पूर्ण

अटल व्योम plt_clk_reg_update(काष्ठा clk_plt *clk, u32 mask, u32 val)
अणु
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&clk->lock, flags);

	पंचांगp = पढ़ोl(clk->reg);
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	ग_लिखोl(पंचांगp, clk->reg);

	spin_unlock_irqrestore(&clk->lock, flags);
पूर्ण

अटल पूर्णांक plt_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_plt *clk = to_clk_plt(hw);

	plt_clk_reg_update(clk, PMC_MASK_CLK_FREQ, plt_parent_to_reg(index));

	वापस 0;
पूर्ण

अटल u8 plt_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plt *clk = to_clk_plt(hw);
	u32 value;

	value = पढ़ोl(clk->reg);

	वापस plt_reg_to_parent(value);
पूर्ण

अटल पूर्णांक plt_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plt *clk = to_clk_plt(hw);

	plt_clk_reg_update(clk, PMC_MASK_CLK_CTL, PMC_CLK_CTL_FORCE_ON);

	वापस 0;
पूर्ण

अटल व्योम plt_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plt *clk = to_clk_plt(hw);

	plt_clk_reg_update(clk, PMC_MASK_CLK_CTL, PMC_CLK_CTL_FORCE_OFF);
पूर्ण

अटल पूर्णांक plt_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plt *clk = to_clk_plt(hw);
	u32 value;

	value = पढ़ोl(clk->reg);

	वापस plt_reg_to_enabled(value);
पूर्ण

अटल स्थिर काष्ठा clk_ops plt_clk_ops = अणु
	.enable = plt_clk_enable,
	.disable = plt_clk_disable,
	.is_enabled = plt_clk_is_enabled,
	.get_parent = plt_clk_get_parent,
	.set_parent = plt_clk_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_plt *plt_clk_रेजिस्टर(काष्ठा platक्रमm_device *pdev, पूर्णांक id,
					स्थिर काष्ठा pmc_clk_data *pmc_data,
					स्थिर अक्षर **parent_names,
					पूर्णांक num_parents)
अणु
	काष्ठा clk_plt *pclk;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pclk = devm_kzalloc(&pdev->dev, माप(*pclk), GFP_KERNEL);
	अगर (!pclk)
		वापस ERR_PTR(-ENOMEM);

	init.name =  kaप्र_लिखो(GFP_KERNEL, "%s_%d", PLT_CLK_NAME_BASE, id);
	init.ops = &plt_clk_ops;
	init.flags = 0;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	pclk->hw.init = &init;
	pclk->reg = pmc_data->base + PMC_CLK_CTL_OFFSET + id * PMC_CLK_CTL_SIZE;
	spin_lock_init(&pclk->lock);

	/*
	 * On some प्रणालीs, the pmc_plt_घड़ीs alपढ़ोy enabled by the
	 * firmware are being marked as critical to aव्योम them being
	 * gated by the घड़ी framework.
	 */
	अगर (pmc_data->critical && plt_clk_is_enabled(&pclk->hw))
		init.flags |= CLK_IS_CRITICAL;

	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &pclk->hw);
	अगर (ret) अणु
		pclk = ERR_PTR(ret);
		जाओ err_मुक्त_init;
	पूर्ण

	pclk->lookup = clkdev_hw_create(&pclk->hw, init.name, शून्य);
	अगर (!pclk->lookup) अणु
		pclk = ERR_PTR(-ENOMEM);
		जाओ err_मुक्त_init;
	पूर्ण

err_मुक्त_init:
	kमुक्त(init.name);
	वापस pclk;
पूर्ण

अटल व्योम plt_clk_unरेजिस्टर(काष्ठा clk_plt *pclk)
अणु
	clkdev_drop(pclk->lookup);
पूर्ण

अटल काष्ठा clk_plt_fixed *plt_clk_रेजिस्टर_fixed_rate(काष्ठा platक्रमm_device *pdev,
						 स्थिर अक्षर *name,
						 स्थिर अक्षर *parent_name,
						 अचिन्हित दीर्घ fixed_rate)
अणु
	काष्ठा clk_plt_fixed *pclk;

	pclk = devm_kzalloc(&pdev->dev, माप(*pclk), GFP_KERNEL);
	अगर (!pclk)
		वापस ERR_PTR(-ENOMEM);

	pclk->clk = clk_hw_रेजिस्टर_fixed_rate(&pdev->dev, name, parent_name,
					       0, fixed_rate);
	अगर (IS_ERR(pclk->clk))
		वापस ERR_CAST(pclk->clk);

	pclk->lookup = clkdev_hw_create(pclk->clk, name, शून्य);
	अगर (!pclk->lookup) अणु
		clk_hw_unरेजिस्टर_fixed_rate(pclk->clk);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस pclk;
पूर्ण

अटल व्योम plt_clk_unरेजिस्टर_fixed_rate(काष्ठा clk_plt_fixed *pclk)
अणु
	clkdev_drop(pclk->lookup);
	clk_hw_unरेजिस्टर_fixed_rate(pclk->clk);
पूर्ण

अटल व्योम plt_clk_unरेजिस्टर_fixed_rate_loop(काष्ठा clk_plt_data *data,
					       अचिन्हित पूर्णांक i)
अणु
	जबतक (i--)
		plt_clk_unरेजिस्टर_fixed_rate(data->parents[i]);
पूर्ण

अटल व्योम plt_clk_मुक्त_parent_names_loop(स्थिर अक्षर **parent_names,
					   अचिन्हित पूर्णांक i)
अणु
	जबतक (i--)
		kमुक्त_स्थिर(parent_names[i]);
	kमुक्त(parent_names);
पूर्ण

अटल व्योम plt_clk_unरेजिस्टर_loop(काष्ठा clk_plt_data *data,
				    अचिन्हित पूर्णांक i)
अणु
	जबतक (i--)
		plt_clk_unरेजिस्टर(data->clks[i]);
पूर्ण

अटल स्थिर अक्षर **plt_clk_रेजिस्टर_parents(काष्ठा platक्रमm_device *pdev,
					     काष्ठा clk_plt_data *data,
					     स्थिर काष्ठा pmc_clk *clks)
अणु
	स्थिर अक्षर **parent_names;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	पूर्णांक nparents = 0;

	data->nparents = 0;
	जबतक (clks[nparents].name)
		nparents++;

	data->parents = devm_kसुस्मृति(&pdev->dev, nparents,
				     माप(*data->parents), GFP_KERNEL);
	अगर (!data->parents)
		वापस ERR_PTR(-ENOMEM);

	parent_names = kसुस्मृति(nparents, माप(*parent_names),
			       GFP_KERNEL);
	अगर (!parent_names)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < nparents; i++) अणु
		data->parents[i] =
			plt_clk_रेजिस्टर_fixed_rate(pdev, clks[i].name,
						    clks[i].parent_name,
						    clks[i].freq);
		अगर (IS_ERR(data->parents[i])) अणु
			err = PTR_ERR(data->parents[i]);
			जाओ err_unreg;
		पूर्ण
		parent_names[i] = kstrdup_स्थिर(clks[i].name, GFP_KERNEL);
	पूर्ण

	data->nparents = nparents;
	वापस parent_names;

err_unreg:
	plt_clk_unरेजिस्टर_fixed_rate_loop(data, i);
	plt_clk_मुक्त_parent_names_loop(parent_names, i);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम plt_clk_unरेजिस्टर_parents(काष्ठा clk_plt_data *data)
अणु
	plt_clk_unरेजिस्टर_fixed_rate_loop(data, data->nparents);
पूर्ण

अटल पूर्णांक plt_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा pmc_clk_data *pmc_data;
	स्थिर अक्षर **parent_names;
	काष्ठा clk_plt_data *data;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	pmc_data = dev_get_platdata(&pdev->dev);
	अगर (!pmc_data || !pmc_data->clks)
		वापस -EINVAL;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	parent_names = plt_clk_रेजिस्टर_parents(pdev, data, pmc_data->clks);
	अगर (IS_ERR(parent_names))
		वापस PTR_ERR(parent_names);

	क्रम (i = 0; i < PMC_CLK_NUM; i++) अणु
		data->clks[i] = plt_clk_रेजिस्टर(pdev, i, pmc_data,
						 parent_names, data->nparents);
		अगर (IS_ERR(data->clks[i])) अणु
			err = PTR_ERR(data->clks[i]);
			जाओ err_unreg_clk_plt;
		पूर्ण
	पूर्ण
	data->mclk_lookup = clkdev_hw_create(&data->clks[3]->hw, "mclk", शून्य);
	अगर (!data->mclk_lookup) अणु
		err = -ENOMEM;
		जाओ err_unreg_clk_plt;
	पूर्ण

	data->ether_clk_lookup = clkdev_hw_create(&data->clks[4]->hw,
						  "ether_clk", शून्य);
	अगर (!data->ether_clk_lookup) अणु
		err = -ENOMEM;
		जाओ err_drop_mclk;
	पूर्ण

	plt_clk_मुक्त_parent_names_loop(parent_names, data->nparents);

	platक्रमm_set_drvdata(pdev, data);
	वापस 0;

err_drop_mclk:
	clkdev_drop(data->mclk_lookup);
err_unreg_clk_plt:
	plt_clk_unरेजिस्टर_loop(data, i);
	plt_clk_unरेजिस्टर_parents(data);
	plt_clk_मुक्त_parent_names_loop(parent_names, data->nparents);
	वापस err;
पूर्ण

अटल पूर्णांक plt_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_plt_data *data;

	data = platक्रमm_get_drvdata(pdev);

	clkdev_drop(data->ether_clk_lookup);
	clkdev_drop(data->mclk_lookup);
	plt_clk_unरेजिस्टर_loop(data, PMC_CLK_NUM);
	plt_clk_unरेजिस्टर_parents(data);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver plt_clk_driver = अणु
	.driver = अणु
		.name = "clk-pmc-atom",
	पूर्ण,
	.probe = plt_clk_probe,
	.हटाओ = plt_clk_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(plt_clk_driver);
