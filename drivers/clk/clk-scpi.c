<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System Control and Power Interface (SCPI) Protocol based घड़ी driver
 *
 * Copyright (C) 2015 ARM Ltd.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scpi_protocol.h>

काष्ठा scpi_clk अणु
	u32 id;
	काष्ठा clk_hw hw;
	काष्ठा scpi_dvfs_info *info;
	काष्ठा scpi_ops *scpi_ops;
पूर्ण;

#घोषणा to_scpi_clk(clk) container_of(clk, काष्ठा scpi_clk, hw)

अटल काष्ठा platक्रमm_device *cpufreq_dev;

अटल अचिन्हित दीर्घ scpi_clk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा scpi_clk *clk = to_scpi_clk(hw);

	वापस clk->scpi_ops->clk_get_val(clk->id);
पूर्ण

अटल दीर्घ scpi_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	/*
	 * We can't figure out what rate it will be, so just वापस the
	 * rate back to the caller. scpi_clk_recalc_rate() will be called
	 * after the rate is set and we'll know what rate the घड़ी is
	 * running at then.
	 */
	वापस rate;
पूर्ण

अटल पूर्णांक scpi_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा scpi_clk *clk = to_scpi_clk(hw);

	वापस clk->scpi_ops->clk_set_val(clk->id, rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops scpi_clk_ops = अणु
	.recalc_rate = scpi_clk_recalc_rate,
	.round_rate = scpi_clk_round_rate,
	.set_rate = scpi_clk_set_rate,
पूर्ण;

/* find बंदst match to given frequency in OPP table */
अटल दीर्घ __scpi_dvfs_round_rate(काष्ठा scpi_clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक idx;
	अचिन्हित दीर्घ fmin = 0, fmax = ~0, fपंचांगp;
	स्थिर काष्ठा scpi_opp *opp = clk->info->opps;

	क्रम (idx = 0; idx < clk->info->count; idx++, opp++) अणु
		fपंचांगp = opp->freq;
		अगर (fपंचांगp >= rate) अणु
			अगर (fपंचांगp <= fmax)
				fmax = fपंचांगp;
			अवरोध;
		पूर्ण अन्यथा अगर (fपंचांगp >= fmin) अणु
			fmin = fपंचांगp;
		पूर्ण
	पूर्ण
	वापस fmax != ~0 ? fmax : fmin;
पूर्ण

अटल अचिन्हित दीर्घ scpi_dvfs_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा scpi_clk *clk = to_scpi_clk(hw);
	पूर्णांक idx = clk->scpi_ops->dvfs_get_idx(clk->id);
	स्थिर काष्ठा scpi_opp *opp;

	अगर (idx < 0)
		वापस 0;

	opp = clk->info->opps + idx;
	वापस opp->freq;
पूर्ण

अटल दीर्घ scpi_dvfs_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा scpi_clk *clk = to_scpi_clk(hw);

	वापस __scpi_dvfs_round_rate(clk, rate);
पूर्ण

अटल पूर्णांक __scpi_find_dvfs_index(काष्ठा scpi_clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक idx, max_opp = clk->info->count;
	स्थिर काष्ठा scpi_opp *opp = clk->info->opps;

	क्रम (idx = 0; idx < max_opp; idx++, opp++)
		अगर (opp->freq == rate)
			वापस idx;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक scpi_dvfs_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा scpi_clk *clk = to_scpi_clk(hw);
	पूर्णांक ret = __scpi_find_dvfs_index(clk, rate);

	अगर (ret < 0)
		वापस ret;
	वापस clk->scpi_ops->dvfs_set_idx(clk->id, (u8)ret);
पूर्ण

अटल स्थिर काष्ठा clk_ops scpi_dvfs_ops = अणु
	.recalc_rate = scpi_dvfs_recalc_rate,
	.round_rate = scpi_dvfs_round_rate,
	.set_rate = scpi_dvfs_set_rate,
पूर्ण;

अटल स्थिर काष्ठा of_device_id scpi_clk_match[] __maybe_unused = अणु
	अणु .compatible = "arm,scpi-dvfs-clocks", .data = &scpi_dvfs_ops, पूर्ण,
	अणु .compatible = "arm,scpi-variable-clocks", .data = &scpi_clk_ops, पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
scpi_clk_ops_init(काष्ठा device *dev, स्थिर काष्ठा of_device_id *match,
		  काष्ठा scpi_clk *sclk, स्थिर अक्षर *name)
अणु
	काष्ठा clk_init_data init;
	अचिन्हित दीर्घ min = 0, max = 0;
	पूर्णांक ret;

	init.name = name;
	init.flags = 0;
	init.num_parents = 0;
	init.ops = match->data;
	sclk->hw.init = &init;
	sclk->scpi_ops = get_scpi_ops();

	अगर (init.ops == &scpi_dvfs_ops) अणु
		sclk->info = sclk->scpi_ops->dvfs_get_info(sclk->id);
		अगर (IS_ERR(sclk->info))
			वापस PTR_ERR(sclk->info);
	पूर्ण अन्यथा अगर (init.ops == &scpi_clk_ops) अणु
		अगर (sclk->scpi_ops->clk_get_range(sclk->id, &min, &max) || !max)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = devm_clk_hw_रेजिस्टर(dev, &sclk->hw);
	अगर (!ret && max)
		clk_hw_set_rate_range(&sclk->hw, min, max);
	वापस ret;
पूर्ण

काष्ठा scpi_clk_data अणु
	काष्ठा scpi_clk **clk;
	अचिन्हित पूर्णांक clk_num;
पूर्ण;

अटल काष्ठा clk_hw *
scpi_of_clk_src_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा scpi_clk *sclk;
	काष्ठा scpi_clk_data *clk_data = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0], count;

	क्रम (count = 0; count < clk_data->clk_num; count++) अणु
		sclk = clk_data->clk[count];
		अगर (idx == sclk->id)
			वापस &sclk->hw;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक scpi_clk_add(काष्ठा device *dev, काष्ठा device_node *np,
			स्थिर काष्ठा of_device_id *match)
अणु
	पूर्णांक idx, count, err;
	काष्ठा scpi_clk_data *clk_data;

	count = of_property_count_strings(np, "clock-output-names");
	अगर (count < 0) अणु
		dev_err(dev, "%pOFn: invalid clock output count\n", np);
		वापस -EINVAL;
	पूर्ण

	clk_data = devm_kदो_स्मृति(dev, माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->clk_num = count;
	clk_data->clk = devm_kसुस्मृति(dev, count, माप(*clk_data->clk),
				     GFP_KERNEL);
	अगर (!clk_data->clk)
		वापस -ENOMEM;

	क्रम (idx = 0; idx < count; idx++) अणु
		काष्ठा scpi_clk *sclk;
		स्थिर अक्षर *name;
		u32 val;

		sclk = devm_kzalloc(dev, माप(*sclk), GFP_KERNEL);
		अगर (!sclk)
			वापस -ENOMEM;

		अगर (of_property_पढ़ो_string_index(np, "clock-output-names",
						  idx, &name)) अणु
			dev_err(dev, "invalid clock name @ %pOFn\n", np);
			वापस -EINVAL;
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(np, "clock-indices",
					       idx, &val)) अणु
			dev_err(dev, "invalid clock index @ %pOFn\n", np);
			वापस -EINVAL;
		पूर्ण

		sclk->id = val;

		err = scpi_clk_ops_init(dev, match, sclk, name);
		अगर (err) अणु
			dev_err(dev, "failed to register clock '%s'\n", name);
			वापस err;
		पूर्ण

		dev_dbg(dev, "Registered clock '%s'\n", name);
		clk_data->clk[idx] = sclk;
	पूर्ण

	वापस of_clk_add_hw_provider(np, scpi_of_clk_src_get, clk_data);
पूर्ण

अटल पूर्णांक scpi_घड़ीs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child, *np = dev->of_node;

	अगर (cpufreq_dev) अणु
		platक्रमm_device_unरेजिस्टर(cpufreq_dev);
		cpufreq_dev = शून्य;
	पूर्ण

	क्रम_each_available_child_of_node(np, child)
		of_clk_del_provider(np);
	वापस 0;
पूर्ण

अटल पूर्णांक scpi_घड़ीs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child, *np = dev->of_node;
	स्थिर काष्ठा of_device_id *match;

	अगर (!get_scpi_ops())
		वापस -ENXIO;

	क्रम_each_available_child_of_node(np, child) अणु
		match = of_match_node(scpi_clk_match, child);
		अगर (!match)
			जारी;
		ret = scpi_clk_add(dev, child, match);
		अगर (ret) अणु
			scpi_घड़ीs_हटाओ(pdev);
			of_node_put(child);
			वापस ret;
		पूर्ण

		अगर (match->data != &scpi_dvfs_ops)
			जारी;
		/* Add the भव cpufreq device अगर it's DVFS घड़ी provider */
		cpufreq_dev = platक्रमm_device_रेजिस्टर_simple("scpi-cpufreq",
							      -1, शून्य, 0);
		अगर (IS_ERR(cpufreq_dev))
			pr_warn("unable to register cpufreq device");
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id scpi_घड़ीs_ids[] = अणु
	अणु .compatible = "arm,scpi-clocks", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, scpi_घड़ीs_ids);

अटल काष्ठा platक्रमm_driver scpi_घड़ीs_driver = अणु
	.driver	= अणु
		.name = "scpi_clocks",
		.of_match_table = scpi_घड़ीs_ids,
	पूर्ण,
	.probe = scpi_घड़ीs_probe,
	.हटाओ = scpi_घड़ीs_हटाओ,
पूर्ण;
module_platक्रमm_driver(scpi_घड़ीs_driver);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCPI clock driver");
MODULE_LICENSE("GPL v2");
