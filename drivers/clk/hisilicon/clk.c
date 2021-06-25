<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon घड़ी driver
 *
 * Copyright (c) 2012-2013 Hisilicon Limited.
 * Copyright (c) 2012-2013 Linaro Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 *	   Xin Li <li.xin@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

अटल DEFINE_SPINLOCK(hisi_clk_lock);

काष्ठा hisi_घड़ी_data *hisi_clk_alloc(काष्ठा platक्रमm_device *pdev,
						पूर्णांक nr_clks)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	काष्ठा resource *res;
	काष्ठा clk **clk_table;

	clk_data = devm_kदो_स्मृति(&pdev->dev, माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस शून्य;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस शून्य;
	clk_data->base = devm_ioremap(&pdev->dev,
				res->start, resource_size(res));
	अगर (!clk_data->base)
		वापस शून्य;

	clk_table = devm_kदो_स्मृति_array(&pdev->dev, nr_clks,
				       माप(*clk_table),
				       GFP_KERNEL);
	अगर (!clk_table)
		वापस शून्य;

	clk_data->clk_data.clks = clk_table;
	clk_data->clk_data.clk_num = nr_clks;

	वापस clk_data;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_alloc);

काष्ठा hisi_घड़ी_data *hisi_clk_init(काष्ठा device_node *np,
					     पूर्णांक nr_clks)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	काष्ठा clk **clk_table;
	व्योम __iomem *base;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("%s: failed to map clock registers\n", __func__);
		जाओ err;
	पूर्ण

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		जाओ err;

	clk_data->base = base;
	clk_table = kसुस्मृति(nr_clks, माप(*clk_table), GFP_KERNEL);
	अगर (!clk_table)
		जाओ err_data;

	clk_data->clk_data.clks = clk_table;
	clk_data->clk_data.clk_num = nr_clks;
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data->clk_data);
	वापस clk_data;
err_data:
	kमुक्त(clk_data);
err:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_init);

पूर्णांक hisi_clk_रेजिस्टर_fixed_rate(स्थिर काष्ठा hisi_fixed_rate_घड़ी *clks,
					 पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = clk_रेजिस्टर_fixed_rate(शून्य, clks[i].name,
					      clks[i].parent_name,
					      clks[i].flags,
					      clks[i].fixed_rate);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err;
		पूर्ण
		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		clk_unरेजिस्टर_fixed_rate(data->clk_data.clks[clks[i].id]);

	वापस PTR_ERR(clk);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_fixed_rate);

पूर्णांक hisi_clk_रेजिस्टर_fixed_factor(स्थिर काष्ठा hisi_fixed_factor_घड़ी *clks,
					   पूर्णांक nums,
					   काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = clk_रेजिस्टर_fixed_factor(शून्य, clks[i].name,
						clks[i].parent_name,
						clks[i].flags, clks[i].mult,
						clks[i].भाग);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err;
		पूर्ण
		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		clk_unरेजिस्टर_fixed_factor(data->clk_data.clks[clks[i].id]);

	वापस PTR_ERR(clk);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_fixed_factor);

पूर्णांक hisi_clk_रेजिस्टर_mux(स्थिर काष्ठा hisi_mux_घड़ी *clks,
				  पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		u32 mask = BIT(clks[i].width) - 1;

		clk = clk_रेजिस्टर_mux_table(शून्य, clks[i].name,
					clks[i].parent_names,
					clks[i].num_parents, clks[i].flags,
					base + clks[i].offset, clks[i].shअगरt,
					mask, clks[i].mux_flags,
					clks[i].table, &hisi_clk_lock);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err;
		पूर्ण

		अगर (clks[i].alias)
			clk_रेजिस्टर_clkdev(clk, clks[i].alias, शून्य);

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		clk_unरेजिस्टर_mux(data->clk_data.clks[clks[i].id]);

	वापस PTR_ERR(clk);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_mux);

पूर्णांक hisi_clk_रेजिस्टर_phase(काष्ठा device *dev,
			    स्थिर काष्ठा hisi_phase_घड़ी *clks,
			    पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	व्योम __iomem *base = data->base;
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = clk_रेजिस्टर_hisi_phase(dev, &clks[i], base,
					      &hisi_clk_lock);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
			       clks[i].name);
			वापस PTR_ERR(clk);
		पूर्ण

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_phase);

पूर्णांक hisi_clk_रेजिस्टर_भागider(स्थिर काष्ठा hisi_भागider_घड़ी *clks,
				      पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = clk_रेजिस्टर_भागider_table(शून्य, clks[i].name,
						 clks[i].parent_name,
						 clks[i].flags,
						 base + clks[i].offset,
						 clks[i].shअगरt, clks[i].width,
						 clks[i].भाग_flags,
						 clks[i].table,
						 &hisi_clk_lock);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err;
		पूर्ण

		अगर (clks[i].alias)
			clk_रेजिस्टर_clkdev(clk, clks[i].alias, शून्य);

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		clk_unरेजिस्टर_भागider(data->clk_data.clks[clks[i].id]);

	वापस PTR_ERR(clk);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_भागider);

पूर्णांक hisi_clk_रेजिस्टर_gate(स्थिर काष्ठा hisi_gate_घड़ी *clks,
				       पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = clk_रेजिस्टर_gate(शून्य, clks[i].name,
						clks[i].parent_name,
						clks[i].flags,
						base + clks[i].offset,
						clks[i].bit_idx,
						clks[i].gate_flags,
						&hisi_clk_lock);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err;
		पूर्ण

		अगर (clks[i].alias)
			clk_रेजिस्टर_clkdev(clk, clks[i].alias, शून्य);

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		clk_unरेजिस्टर_gate(data->clk_data.clks[clks[i].id]);

	वापस PTR_ERR(clk);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_gate);

व्योम hisi_clk_रेजिस्टर_gate_sep(स्थिर काष्ठा hisi_gate_घड़ी *clks,
				       पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = hisi_रेजिस्टर_clkgate_sep(शून्य, clks[i].name,
						clks[i].parent_name,
						clks[i].flags,
						base + clks[i].offset,
						clks[i].bit_idx,
						clks[i].gate_flags,
						&hisi_clk_lock);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण

		अगर (clks[i].alias)
			clk_रेजिस्टर_clkdev(clk, clks[i].alias, शून्य);

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_clk_रेजिस्टर_gate_sep);

व्योम __init hi6220_clk_रेजिस्टर_भागider(स्थिर काष्ठा hi6220_भागider_घड़ी *clks,
					पूर्णांक nums, काष्ठा hisi_घड़ी_data *data)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		clk = hi6220_रेजिस्टर_clkभाग(शून्य, clks[i].name,
						clks[i].parent_name,
						clks[i].flags,
						base + clks[i].offset,
						clks[i].shअगरt,
						clks[i].width,
						clks[i].mask_bit,
						&hisi_clk_lock);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण

		अगर (clks[i].alias)
			clk_रेजिस्टर_clkdev(clk, clks[i].alias, शून्य);

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण
पूर्ण
