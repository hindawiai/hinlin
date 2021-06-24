<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PRU-ICSS platक्रमm driver क्रम various TI SoCs
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * Author(s):
 *	Suman Anna <s-anna@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pruss_driver.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/**
 * काष्ठा pruss_निजी_data - PRUSS driver निजी data
 * @has_no_sharedram: flag to indicate the असलence of PRUSS Shared Data RAM
 * @has_core_mux_घड़ी: flag to indicate the presence of PRUSS core घड़ी
 */
काष्ठा pruss_निजी_data अणु
	bool has_no_sharedram;
	bool has_core_mux_घड़ी;
पूर्ण;

अटल व्योम pruss_of_मुक्त_clk_provider(व्योम *data)
अणु
	काष्ठा device_node *clk_mux_np = data;

	of_clk_del_provider(clk_mux_np);
	of_node_put(clk_mux_np);
पूर्ण

अटल पूर्णांक pruss_clk_mux_setup(काष्ठा pruss *pruss, काष्ठा clk *clk_mux,
			       अक्षर *mux_name, काष्ठा device_node *clks_np)
अणु
	काष्ठा device_node *clk_mux_np;
	काष्ठा device *dev = pruss->dev;
	अक्षर *clk_mux_name;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर **parent_names;
	व्योम __iomem *reg;
	u32 reg_offset;
	पूर्णांक ret;

	clk_mux_np = of_get_child_by_name(clks_np, mux_name);
	अगर (!clk_mux_np) अणु
		dev_err(dev, "%pOF is missing its '%s' node\n", clks_np,
			mux_name);
		वापस -ENODEV;
	पूर्ण

	num_parents = of_clk_get_parent_count(clk_mux_np);
	अगर (num_parents < 1) अणु
		dev_err(dev, "mux-clock %pOF must have parents\n", clk_mux_np);
		ret = -EINVAL;
		जाओ put_clk_mux_np;
	पूर्ण

	parent_names = devm_kसुस्मृति(dev, माप(*parent_names), num_parents,
				    GFP_KERNEL);
	अगर (!parent_names) अणु
		ret = -ENOMEM;
		जाओ put_clk_mux_np;
	पूर्ण

	of_clk_parent_fill(clk_mux_np, parent_names, num_parents);

	clk_mux_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s.%pOFn",
				      dev_name(dev), clk_mux_np);
	अगर (!clk_mux_name) अणु
		ret = -ENOMEM;
		जाओ put_clk_mux_np;
	पूर्ण

	ret = of_property_पढ़ो_u32(clk_mux_np, "reg", &reg_offset);
	अगर (ret)
		जाओ put_clk_mux_np;

	reg = pruss->cfg_base + reg_offset;

	clk_mux = clk_रेजिस्टर_mux(शून्य, clk_mux_name, parent_names,
				   num_parents, 0, reg, 0, 1, 0, शून्य);
	अगर (IS_ERR(clk_mux)) अणु
		ret = PTR_ERR(clk_mux);
		जाओ put_clk_mux_np;
	पूर्ण

	ret = devm_add_action_or_reset(dev, (व्योम(*)(व्योम *))clk_unरेजिस्टर_mux,
				       clk_mux);
	अगर (ret) अणु
		dev_err(dev, "failed to add clkmux unregister action %d", ret);
		जाओ put_clk_mux_np;
	पूर्ण

	ret = of_clk_add_provider(clk_mux_np, of_clk_src_simple_get, clk_mux);
	अगर (ret)
		जाओ put_clk_mux_np;

	ret = devm_add_action_or_reset(dev, pruss_of_मुक्त_clk_provider,
				       clk_mux_np);
	अगर (ret) अणु
		dev_err(dev, "failed to add clkmux free action %d", ret);
		जाओ put_clk_mux_np;
	पूर्ण

	वापस 0;

put_clk_mux_np:
	of_node_put(clk_mux_np);
	वापस ret;
पूर्ण

अटल पूर्णांक pruss_clk_init(काष्ठा pruss *pruss, काष्ठा device_node *cfg_node)
अणु
	स्थिर काष्ठा pruss_निजी_data *data;
	काष्ठा device_node *clks_np;
	काष्ठा device *dev = pruss->dev;
	पूर्णांक ret = 0;

	data = of_device_get_match_data(dev);

	clks_np = of_get_child_by_name(cfg_node, "clocks");
	अगर (!clks_np) अणु
		dev_err(dev, "%pOF is missing its 'clocks' node\n", clks_np);
		वापस -ENODEV;
	पूर्ण

	अगर (data && data->has_core_mux_घड़ी) अणु
		ret = pruss_clk_mux_setup(pruss, pruss->core_clk_mux,
					  "coreclk-mux", clks_np);
		अगर (ret) अणु
			dev_err(dev, "failed to setup coreclk-mux\n");
			जाओ put_clks_node;
		पूर्ण
	पूर्ण

	ret = pruss_clk_mux_setup(pruss, pruss->iep_clk_mux, "iepclk-mux",
				  clks_np);
	अगर (ret) अणु
		dev_err(dev, "failed to setup iepclk-mux\n");
		जाओ put_clks_node;
	पूर्ण

put_clks_node:
	of_node_put(clks_np);

	वापस ret;
पूर्ण

अटल काष्ठा regmap_config regmap_conf = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक pruss_cfg_of_init(काष्ठा device *dev, काष्ठा pruss *pruss)
अणु
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device_node *child;
	काष्ठा resource res;
	पूर्णांक ret;

	child = of_get_child_by_name(np, "cfg");
	अगर (!child) अणु
		dev_err(dev, "%pOF is missing its 'cfg' node\n", child);
		वापस -ENODEV;
	पूर्ण

	अगर (of_address_to_resource(child, 0, &res)) अणु
		ret = -ENOMEM;
		जाओ node_put;
	पूर्ण

	pruss->cfg_base = devm_ioremap(dev, res.start, resource_size(&res));
	अगर (!pruss->cfg_base) अणु
		ret = -ENOMEM;
		जाओ node_put;
	पूर्ण

	regmap_conf.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn@%llx", child,
				     (u64)res.start);
	regmap_conf.max_रेजिस्टर = resource_size(&res) - 4;

	pruss->cfg_regmap = devm_regmap_init_mmio(dev, pruss->cfg_base,
						  &regmap_conf);
	kमुक्त(regmap_conf.name);
	अगर (IS_ERR(pruss->cfg_regmap)) अणु
		dev_err(dev, "regmap_init_mmio failed for cfg, ret = %ld\n",
			PTR_ERR(pruss->cfg_regmap));
		ret = PTR_ERR(pruss->cfg_regmap);
		जाओ node_put;
	पूर्ण

	ret = pruss_clk_init(pruss, child);
	अगर (ret)
		dev_err(dev, "pruss_clk_init failed, ret = %d\n", ret);

node_put:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक pruss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device_node *child;
	काष्ठा pruss *pruss;
	काष्ठा resource res;
	पूर्णांक ret, i, index;
	स्थिर काष्ठा pruss_निजी_data *data;
	स्थिर अक्षर *mem_names[PRUSS_MEM_MAX] = अणु "dram0", "dram1", "shrdram2" पूर्ण;

	data = of_device_get_match_data(&pdev->dev);

	ret = dma_set_coherent_mask(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "failed to set the DMA coherent mask");
		वापस ret;
	पूर्ण

	pruss = devm_kzalloc(dev, माप(*pruss), GFP_KERNEL);
	अगर (!pruss)
		वापस -ENOMEM;

	pruss->dev = dev;

	child = of_get_child_by_name(np, "memories");
	अगर (!child) अणु
		dev_err(dev, "%pOF is missing its 'memories' node\n", child);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < PRUSS_MEM_MAX; i++) अणु
		/*
		 * On AM437x one of two PRUSS units करोn't contain Shared RAM,
		 * skip it
		 */
		अगर (data && data->has_no_sharedram && i == PRUSS_MEM_SHRD_RAM2)
			जारी;

		index = of_property_match_string(child, "reg-names",
						 mem_names[i]);
		अगर (index < 0) अणु
			of_node_put(child);
			वापस index;
		पूर्ण

		अगर (of_address_to_resource(child, index, &res)) अणु
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		pruss->mem_regions[i].va = devm_ioremap(dev, res.start,
							resource_size(&res));
		अगर (!pruss->mem_regions[i].va) अणु
			dev_err(dev, "failed to parse and map memory resource %d %s\n",
				i, mem_names[i]);
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण
		pruss->mem_regions[i].pa = res.start;
		pruss->mem_regions[i].size = resource_size(&res);

		dev_dbg(dev, "memory %8s: pa %pa size 0x%zx va %pK\n",
			mem_names[i], &pruss->mem_regions[i].pa,
			pruss->mem_regions[i].size, pruss->mem_regions[i].va);
	पूर्ण
	of_node_put(child);

	platक्रमm_set_drvdata(pdev, pruss);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "couldn't enable module\n");
		pm_runसमय_put_noidle(dev);
		जाओ rpm_disable;
	पूर्ण

	ret = pruss_cfg_of_init(dev, pruss);
	अगर (ret < 0)
		जाओ rpm_put;

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register child devices\n");
		जाओ rpm_put;
	पूर्ण

	वापस 0;

rpm_put:
	pm_runसमय_put_sync(dev);
rpm_disable:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक pruss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	devm_of_platक्रमm_depopulate(dev);

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

/* instance-specअगरic driver निजी data */
अटल स्थिर काष्ठा pruss_निजी_data am437x_pruss1_data = अणु
	.has_no_sharedram = false,
पूर्ण;

अटल स्थिर काष्ठा pruss_निजी_data am437x_pruss0_data = अणु
	.has_no_sharedram = true,
पूर्ण;

अटल स्थिर काष्ठा pruss_निजी_data am65x_j721e_pruss_data = अणु
	.has_core_mux_घड़ी = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pruss_of_match[] = अणु
	अणु .compatible = "ti,am3356-pruss" पूर्ण,
	अणु .compatible = "ti,am4376-pruss0", .data = &am437x_pruss0_data, पूर्ण,
	अणु .compatible = "ti,am4376-pruss1", .data = &am437x_pruss1_data, पूर्ण,
	अणु .compatible = "ti,am5728-pruss" पूर्ण,
	अणु .compatible = "ti,k2g-pruss" पूर्ण,
	अणु .compatible = "ti,am654-icssg", .data = &am65x_j721e_pruss_data, पूर्ण,
	अणु .compatible = "ti,j721e-icssg", .data = &am65x_j721e_pruss_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pruss_of_match);

अटल काष्ठा platक्रमm_driver pruss_driver = अणु
	.driver = अणु
		.name = "pruss",
		.of_match_table = pruss_of_match,
	पूर्ण,
	.probe  = pruss_probe,
	.हटाओ = pruss_हटाओ,
पूर्ण;
module_platक्रमm_driver(pruss_driver);

MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
MODULE_DESCRIPTION("PRU-ICSS Subsystem Driver");
MODULE_LICENSE("GPL v2");
