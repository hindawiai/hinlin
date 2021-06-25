<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Marvell Armada AP CPU Clock Controller
 *
 * Copyright (C) 2018 Marvell
 *
 * Omri Itach <omrii@marvell.com>
 * Gregory Clement <gregory.clement@bootlin.com>
 */

#घोषणा pr_fmt(fmt) "ap-cpu-clk: " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश "armada_ap_cp_helper.h"

#घोषणा AP806_CPU_CLUSTER0		0
#घोषणा AP806_CPU_CLUSTER1		1
#घोषणा AP806_CPUS_PER_CLUSTER		2
#घोषणा APN806_CPU1_MASK		0x1

#घोषणा APN806_CLUSTER_NUM_OFFSET	8
#घोषणा APN806_CLUSTER_NUM_MASK		BIT(APN806_CLUSTER_NUM_OFFSET)

#घोषणा APN806_MAX_DIVIDER		32

/*
 * काष्ठा cpu_dfs_regs: CPU DFS रेजिस्टर mapping
 * @भागider_reg: full पूर्णांकeger ratio from PLL frequency to CPU घड़ी frequency
 * @क्रमce_reg: request to क्रमce new ratio regardless of relation to other घड़ीs
 * @ratio_reg: central request to चयन ratios
 */
काष्ठा cpu_dfs_regs अणु
	अचिन्हित पूर्णांक भागider_reg;
	अचिन्हित पूर्णांक क्रमce_reg;
	अचिन्हित पूर्णांक ratio_reg;
	अचिन्हित पूर्णांक ratio_state_reg;
	अचिन्हित पूर्णांक भागider_mask;
	अचिन्हित पूर्णांक cluster_offset;
	अचिन्हित पूर्णांक क्रमce_mask;
	पूर्णांक भागider_offset;
	पूर्णांक भागider_ratio;
	पूर्णांक ratio_offset;
	पूर्णांक ratio_state_offset;
	पूर्णांक ratio_state_cluster_offset;
पूर्ण;

/* AP806 CPU DFS रेजिस्टर mapping*/
#घोषणा AP806_CA72MP2_0_PLL_CR_0_REG_OFFSET		0x278
#घोषणा AP806_CA72MP2_0_PLL_CR_1_REG_OFFSET		0x280
#घोषणा AP806_CA72MP2_0_PLL_CR_2_REG_OFFSET		0x284
#घोषणा AP806_CA72MP2_0_PLL_SR_REG_OFFSET		0xC94

#घोषणा AP806_CA72MP2_0_PLL_CR_CLUSTER_OFFSET		0x14
#घोषणा AP806_PLL_CR_0_CPU_CLK_DIV_RATIO_OFFSET		0
#घोषणा AP806_PLL_CR_CPU_CLK_DIV_RATIO			0
#घोषणा AP806_PLL_CR_0_CPU_CLK_DIV_RATIO_MASK \
			(0x3f << AP806_PLL_CR_0_CPU_CLK_DIV_RATIO_OFFSET)
#घोषणा AP806_PLL_CR_0_CPU_CLK_RELOAD_FORCE_OFFSET	24
#घोषणा AP806_PLL_CR_0_CPU_CLK_RELOAD_FORCE_MASK \
			(0x1 << AP806_PLL_CR_0_CPU_CLK_RELOAD_FORCE_OFFSET)
#घोषणा AP806_PLL_CR_0_CPU_CLK_RELOAD_RATIO_OFFSET	16
#घोषणा AP806_CA72MP2_0_PLL_RATIO_STABLE_OFFSET	0
#घोषणा AP806_CA72MP2_0_PLL_RATIO_STATE			11

#घोषणा STATUS_POLL_PERIOD_US		1
#घोषणा STATUS_POLL_TIMEOUT_US		1000000

#घोषणा to_ap_cpu_clk(_hw) container_of(_hw, काष्ठा ap_cpu_clk, hw)

अटल स्थिर काष्ठा cpu_dfs_regs ap806_dfs_regs = अणु
	.भागider_reg = AP806_CA72MP2_0_PLL_CR_0_REG_OFFSET,
	.क्रमce_reg = AP806_CA72MP2_0_PLL_CR_1_REG_OFFSET,
	.ratio_reg = AP806_CA72MP2_0_PLL_CR_2_REG_OFFSET,
	.ratio_state_reg = AP806_CA72MP2_0_PLL_SR_REG_OFFSET,
	.भागider_mask = AP806_PLL_CR_0_CPU_CLK_DIV_RATIO_MASK,
	.cluster_offset = AP806_CA72MP2_0_PLL_CR_CLUSTER_OFFSET,
	.क्रमce_mask = AP806_PLL_CR_0_CPU_CLK_RELOAD_FORCE_MASK,
	.भागider_offset = AP806_PLL_CR_0_CPU_CLK_DIV_RATIO_OFFSET,
	.भागider_ratio = AP806_PLL_CR_CPU_CLK_DIV_RATIO,
	.ratio_offset = AP806_PLL_CR_0_CPU_CLK_RELOAD_RATIO_OFFSET,
	.ratio_state_offset = AP806_CA72MP2_0_PLL_RATIO_STABLE_OFFSET,
	.ratio_state_cluster_offset = AP806_CA72MP2_0_PLL_RATIO_STABLE_OFFSET,
पूर्ण;

/* AP807 CPU DFS रेजिस्टर mapping */
#घोषणा AP807_DEVICE_GENERAL_CONTROL_10_REG_OFFSET		0x278
#घोषणा AP807_DEVICE_GENERAL_CONTROL_11_REG_OFFSET		0x27c
#घोषणा AP807_DEVICE_GENERAL_STATUS_6_REG_OFFSET		0xc98
#घोषणा AP807_CA72MP2_0_PLL_CR_CLUSTER_OFFSET			0x8
#घोषणा AP807_PLL_CR_0_CPU_CLK_DIV_RATIO_OFFSET			18
#घोषणा AP807_PLL_CR_0_CPU_CLK_DIV_RATIO_MASK \
		(0x3f << AP807_PLL_CR_0_CPU_CLK_DIV_RATIO_OFFSET)
#घोषणा AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_OFFSET			12
#घोषणा AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_MASK \
		(0x3f << AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_OFFSET)
#घोषणा AP807_PLL_CR_CPU_CLK_DIV_RATIO				3
#घोषणा AP807_PLL_CR_0_CPU_CLK_RELOAD_FORCE_OFFSET		0
#घोषणा AP807_PLL_CR_0_CPU_CLK_RELOAD_FORCE_MASK \
		(0x3 << AP807_PLL_CR_0_CPU_CLK_RELOAD_FORCE_OFFSET)
#घोषणा AP807_PLL_CR_0_CPU_CLK_RELOAD_RATIO_OFFSET		6
#घोषणा	AP807_CA72MP2_0_PLL_CLKDIV_RATIO_STABLE_OFFSET		20
#घोषणा AP807_CA72MP2_0_PLL_CLKDIV_RATIO_STABLE_CLUSTER_OFFSET	3

अटल स्थिर काष्ठा cpu_dfs_regs ap807_dfs_regs = अणु
	.भागider_reg = AP807_DEVICE_GENERAL_CONTROL_10_REG_OFFSET,
	.क्रमce_reg = AP807_DEVICE_GENERAL_CONTROL_11_REG_OFFSET,
	.ratio_reg = AP807_DEVICE_GENERAL_CONTROL_11_REG_OFFSET,
	.ratio_state_reg = AP807_DEVICE_GENERAL_STATUS_6_REG_OFFSET,
	.भागider_mask = AP807_PLL_CR_0_CPU_CLK_DIV_RATIO_MASK,
	.cluster_offset = AP807_CA72MP2_0_PLL_CR_CLUSTER_OFFSET,
	.क्रमce_mask = AP807_PLL_CR_0_CPU_CLK_RELOAD_FORCE_MASK,
	.भागider_offset = AP807_PLL_CR_0_CPU_CLK_DIV_RATIO_OFFSET,
	.भागider_ratio = AP807_PLL_CR_CPU_CLK_DIV_RATIO,
	.ratio_offset = AP807_PLL_CR_0_CPU_CLK_RELOAD_RATIO_OFFSET,
	.ratio_state_offset = AP807_CA72MP2_0_PLL_CLKDIV_RATIO_STABLE_OFFSET,
	.ratio_state_cluster_offset =
		AP807_CA72MP2_0_PLL_CLKDIV_RATIO_STABLE_CLUSTER_OFFSET
पूर्ण;

/*
 * काष्ठा ap806_clk: CPU cluster घड़ी controller instance
 * @cluster: Cluster घड़ी controller index
 * @clk_name: Cluster घड़ी controller name
 * @dev : Cluster घड़ी device
 * @hw: HW specअगरic काष्ठाure of Cluster घड़ी controller
 * @pll_cr_base: CA72MP2 Register base (Device Sample at Reset रेजिस्टर)
 */
काष्ठा ap_cpu_clk अणु
	अचिन्हित पूर्णांक cluster;
	स्थिर अक्षर *clk_name;
	काष्ठा device *dev;
	काष्ठा clk_hw hw;
	काष्ठा regmap *pll_cr_base;
	स्थिर काष्ठा cpu_dfs_regs *pll_regs;
पूर्ण;

अटल अचिन्हित दीर्घ ap_cpu_clk_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ap_cpu_clk *clk = to_ap_cpu_clk(hw);
	अचिन्हित पूर्णांक cpu_clkभाग_reg;
	पूर्णांक cpu_clkभाग_ratio;

	cpu_clkभाग_reg = clk->pll_regs->भागider_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);
	regmap_पढ़ो(clk->pll_cr_base, cpu_clkभाग_reg, &cpu_clkभाग_ratio);
	cpu_clkभाग_ratio &= clk->pll_regs->भागider_mask;
	cpu_clkभाग_ratio >>= clk->pll_regs->भागider_offset;

	वापस parent_rate / cpu_clkभाग_ratio;
पूर्ण

अटल पूर्णांक ap_cpu_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ap_cpu_clk *clk = to_ap_cpu_clk(hw);
	पूर्णांक ret, reg, भागider = parent_rate / rate;
	अचिन्हित पूर्णांक cpu_clkभाग_reg, cpu_क्रमce_reg, cpu_ratio_reg, stable_bit;

	cpu_clkभाग_reg = clk->pll_regs->भागider_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);
	cpu_क्रमce_reg = clk->pll_regs->क्रमce_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);
	cpu_ratio_reg = clk->pll_regs->ratio_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);

	regmap_पढ़ो(clk->pll_cr_base, cpu_clkभाग_reg, &reg);
	reg &= ~(clk->pll_regs->भागider_mask);
	reg |= (भागider << clk->pll_regs->भागider_offset);

	/*
	 * AP807 CPU भागider has two channels with ratio 1:3 and भागider_ratio
	 * is 1. Otherwise, in the हाल of the AP806, भागider_ratio is 0.
	 */
	अगर (clk->pll_regs->भागider_ratio) अणु
		reg &= ~(AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_MASK);
		reg |= ((भागider * clk->pll_regs->भागider_ratio) <<
				AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_OFFSET);
	पूर्ण
	regmap_ग_लिखो(clk->pll_cr_base, cpu_clkभाग_reg, reg);


	regmap_update_bits(clk->pll_cr_base, cpu_क्रमce_reg,
			   clk->pll_regs->क्रमce_mask,
			   clk->pll_regs->क्रमce_mask);

	regmap_update_bits(clk->pll_cr_base, cpu_ratio_reg,
			   BIT(clk->pll_regs->ratio_offset),
			   BIT(clk->pll_regs->ratio_offset));

	stable_bit = BIT(clk->pll_regs->ratio_state_offset +
			 clk->cluster *
			 clk->pll_regs->ratio_state_cluster_offset);
	ret = regmap_पढ़ो_poll_समयout(clk->pll_cr_base,
				       clk->pll_regs->ratio_state_reg, reg,
				       reg & stable_bit, STATUS_POLL_PERIOD_US,
				       STATUS_POLL_TIMEOUT_US);
	अगर (ret)
		वापस ret;

	regmap_update_bits(clk->pll_cr_base, cpu_ratio_reg,
			   BIT(clk->pll_regs->ratio_offset), 0);

	वापस 0;
पूर्ण

अटल दीर्घ ap_cpu_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	पूर्णांक भागider = *parent_rate / rate;

	भागider = min(भागider, APN806_MAX_DIVIDER);

	वापस *parent_rate / भागider;
पूर्ण

अटल स्थिर काष्ठा clk_ops ap_cpu_clk_ops = अणु
	.recalc_rate	= ap_cpu_clk_recalc_rate,
	.round_rate	= ap_cpu_clk_round_rate,
	.set_rate	= ap_cpu_clk_set_rate,
पूर्ण;

अटल पूर्णांक ap_cpu_घड़ी_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, nclusters = 0, cluster_index = 0;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn, *np = dev->of_node;
	काष्ठा clk_hw_onecell_data *ap_cpu_data;
	काष्ठा ap_cpu_clk *ap_cpu_clk;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(regmap)) अणु
		pr_err("cannot get pll_cr_base regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/*
	 * AP806 has 4 cpus and DFS क्रम AP806 is controlled per
	 * cluster (2 CPUs per cluster), cpu0 and cpu1 are fixed to
	 * cluster0 जबतक cpu2 and cpu3 are fixed to cluster1 whether
	 * they are enabled or not.  Since cpu0 is the boot cpu, then
	 * cluster0 must exist.  If cpu2 or cpu3 is enabled, cluster1
	 * will exist and the cluster number is 2; otherwise the
	 * cluster number is 1.
	 */
	nclusters = 1;
	क्रम_each_of_cpu_node(dn) अणु
		पूर्णांक cpu, err;

		err = of_property_पढ़ो_u32(dn, "reg", &cpu);
		अगर (WARN_ON(err))
			वापस err;

		/* If cpu2 or cpu3 is enabled */
		अगर (cpu & APN806_CLUSTER_NUM_MASK) अणु
			nclusters = 2;
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * DFS क्रम AP806 is controlled per cluster (2 CPUs per cluster),
	 * so allocate काष्ठाs per cluster
	 */
	ap_cpu_clk = devm_kसुस्मृति(dev, nclusters, माप(*ap_cpu_clk),
				  GFP_KERNEL);
	अगर (!ap_cpu_clk)
		वापस -ENOMEM;

	ap_cpu_data = devm_kzalloc(dev, काष्ठा_size(ap_cpu_data, hws,
						    nclusters),
				GFP_KERNEL);
	अगर (!ap_cpu_data)
		वापस -ENOMEM;

	क्रम_each_of_cpu_node(dn) अणु
		अक्षर *clk_name = "cpu-cluster-0";
		काष्ठा clk_init_data init;
		स्थिर अक्षर *parent_name;
		काष्ठा clk *parent;
		पूर्णांक cpu, err;

		err = of_property_पढ़ो_u32(dn, "reg", &cpu);
		अगर (WARN_ON(err))
			वापस err;

		cluster_index = cpu & APN806_CLUSTER_NUM_MASK;
		cluster_index >>= APN806_CLUSTER_NUM_OFFSET;

		/* Initialize once क्रम one cluster */
		अगर (ap_cpu_data->hws[cluster_index])
			जारी;

		parent = of_clk_get(np, cluster_index);
		अगर (IS_ERR(parent)) अणु
			dev_err(dev, "Could not get the clock parent\n");
			वापस -EINVAL;
		पूर्ण
		parent_name =  __clk_get_name(parent);
		clk_name[12] += cluster_index;
		ap_cpu_clk[cluster_index].clk_name =
			ap_cp_unique_name(dev, np->parent, clk_name);
		ap_cpu_clk[cluster_index].cluster = cluster_index;
		ap_cpu_clk[cluster_index].pll_cr_base = regmap;
		ap_cpu_clk[cluster_index].hw.init = &init;
		ap_cpu_clk[cluster_index].dev = dev;
		ap_cpu_clk[cluster_index].pll_regs = of_device_get_match_data(&pdev->dev);

		init.name = ap_cpu_clk[cluster_index].clk_name;
		init.ops = &ap_cpu_clk_ops;
		init.num_parents = 1;
		init.parent_names = &parent_name;

		ret = devm_clk_hw_रेजिस्टर(dev, &ap_cpu_clk[cluster_index].hw);
		अगर (ret)
			वापस ret;
		ap_cpu_data->hws[cluster_index] = &ap_cpu_clk[cluster_index].hw;
	पूर्ण

	ap_cpu_data->num = cluster_index + 1;

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, ap_cpu_data);
	अगर (ret)
		dev_err(dev, "failed to register OF clock provider\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id ap_cpu_घड़ी_of_match[] = अणु
	अणु
		.compatible = "marvell,ap806-cpu-clock",
		.data = &ap806_dfs_regs,
	पूर्ण,
	अणु
		.compatible = "marvell,ap807-cpu-clock",
		.data = &ap807_dfs_regs,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ap_cpu_घड़ी_driver = अणु
	.probe = ap_cpu_घड़ी_probe,
	.driver		= अणु
		.name	= "marvell-ap-cpu-clock",
		.of_match_table = ap_cpu_घड़ी_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ap_cpu_घड़ी_driver);
