<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Collabora Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/soc/mediatek/infracfg.h>

#समावेश "mt8167-pm-domains.h"
#समावेश "mt8173-pm-domains.h"
#समावेश "mt8183-pm-domains.h"
#समावेश "mt8192-pm-domains.h"

#घोषणा MTK_POLL_DELAY_US		10
#घोषणा MTK_POLL_TIMEOUT		USEC_PER_SEC

#घोषणा PWR_RST_B_BIT			BIT(0)
#घोषणा PWR_ISO_BIT			BIT(1)
#घोषणा PWR_ON_BIT			BIT(2)
#घोषणा PWR_ON_2ND_BIT			BIT(3)
#घोषणा PWR_CLK_DIS_BIT			BIT(4)
#घोषणा PWR_SRAM_CLKISO_BIT		BIT(5)
#घोषणा PWR_SRAM_ISOINT_B_BIT		BIT(6)

काष्ठा scpsys_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	स्थिर काष्ठा scpsys_करोमुख्य_data *data;
	काष्ठा scpsys *scpsys;
	पूर्णांक num_clks;
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_subsys_clks;
	काष्ठा clk_bulk_data *subsys_clks;
	काष्ठा regmap *infracfg;
	काष्ठा regmap *smi;
	काष्ठा regulator *supply;
पूर्ण;

काष्ठा scpsys अणु
	काष्ठा device *dev;
	काष्ठा regmap *base;
	स्थिर काष्ठा scpsys_soc_data *soc_data;
	काष्ठा genpd_onecell_data pd_data;
	काष्ठा generic_pm_करोमुख्य *करोमुख्यs[];
पूर्ण;

#घोषणा to_scpsys_करोमुख्य(gpd) container_of(gpd, काष्ठा scpsys_करोमुख्य, genpd)

अटल bool scpsys_करोमुख्य_is_on(काष्ठा scpsys_करोमुख्य *pd)
अणु
	काष्ठा scpsys *scpsys = pd->scpsys;
	u32 status, status2;

	regmap_पढ़ो(scpsys->base, scpsys->soc_data->pwr_sta_offs, &status);
	status &= pd->data->sta_mask;

	regmap_पढ़ो(scpsys->base, scpsys->soc_data->pwr_sta2nd_offs, &status2);
	status2 &= pd->data->sta_mask;

	/* A करोमुख्य is on when both status bits are set. */
	वापस status && status2;
पूर्ण

अटल पूर्णांक scpsys_sram_enable(काष्ठा scpsys_करोमुख्य *pd)
अणु
	u32 pdn_ack = pd->data->sram_pdn_ack_bits;
	काष्ठा scpsys *scpsys = pd->scpsys;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	regmap_clear_bits(scpsys->base, pd->data->ctl_offs, pd->data->sram_pdn_bits);

	/* Either रुको until SRAM_PDN_ACK all 1 or 0 */
	ret = regmap_पढ़ो_poll_समयout(scpsys->base, pd->data->ctl_offs, पंचांगp,
				       (पंचांगp & pdn_ack) == 0, MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
	अगर (ret < 0)
		वापस ret;

	अगर (MTK_SCPD_CAPS(pd, MTK_SCPD_SRAM_ISO)) अणु
		regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_SRAM_ISOINT_B_BIT);
		udelay(1);
		regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_SRAM_CLKISO_BIT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scpsys_sram_disable(काष्ठा scpsys_करोमुख्य *pd)
अणु
	u32 pdn_ack = pd->data->sram_pdn_ack_bits;
	काष्ठा scpsys *scpsys = pd->scpsys;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (MTK_SCPD_CAPS(pd, MTK_SCPD_SRAM_ISO)) अणु
		regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_SRAM_CLKISO_BIT);
		udelay(1);
		regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_SRAM_ISOINT_B_BIT);
	पूर्ण

	regmap_set_bits(scpsys->base, pd->data->ctl_offs, pd->data->sram_pdn_bits);

	/* Either रुको until SRAM_PDN_ACK all 1 or 0 */
	वापस regmap_पढ़ो_poll_समयout(scpsys->base, pd->data->ctl_offs, पंचांगp,
					(पंचांगp & pdn_ack) == pdn_ack, MTK_POLL_DELAY_US,
					MTK_POLL_TIMEOUT);
पूर्ण

अटल पूर्णांक _scpsys_bus_protect_enable(स्थिर काष्ठा scpsys_bus_prot_data *bpd, काष्ठा regmap *regmap)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < SPM_MAX_BUS_PROT_DATA; i++) अणु
		u32 val, mask = bpd[i].bus_prot_mask;

		अगर (!mask)
			अवरोध;

		अगर (bpd[i].bus_prot_reg_update)
			regmap_set_bits(regmap, bpd[i].bus_prot_set, mask);
		अन्यथा
			regmap_ग_लिखो(regmap, bpd[i].bus_prot_set, mask);

		ret = regmap_पढ़ो_poll_समयout(regmap, bpd[i].bus_prot_sta,
					       val, (val & mask) == mask,
					       MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scpsys_bus_protect_enable(काष्ठा scpsys_करोमुख्य *pd)
अणु
	पूर्णांक ret;

	ret = _scpsys_bus_protect_enable(pd->data->bp_infracfg, pd->infracfg);
	अगर (ret)
		वापस ret;

	वापस _scpsys_bus_protect_enable(pd->data->bp_smi, pd->smi);
पूर्ण

अटल पूर्णांक _scpsys_bus_protect_disable(स्थिर काष्ठा scpsys_bus_prot_data *bpd,
				       काष्ठा regmap *regmap)
अणु
	पूर्णांक i, ret;

	क्रम (i = SPM_MAX_BUS_PROT_DATA - 1; i >= 0; i--) अणु
		u32 val, mask = bpd[i].bus_prot_mask;

		अगर (!mask)
			जारी;

		अगर (bpd[i].bus_prot_reg_update)
			regmap_clear_bits(regmap, bpd[i].bus_prot_clr, mask);
		अन्यथा
			regmap_ग_लिखो(regmap, bpd[i].bus_prot_clr, mask);

		अगर (bpd[i].ignore_clr_ack)
			जारी;

		ret = regmap_पढ़ो_poll_समयout(regmap, bpd[i].bus_prot_sta,
					       val, !(val & mask),
					       MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scpsys_bus_protect_disable(काष्ठा scpsys_करोमुख्य *pd)
अणु
	पूर्णांक ret;

	ret = _scpsys_bus_protect_disable(pd->data->bp_smi, pd->smi);
	अगर (ret)
		वापस ret;

	वापस _scpsys_bus_protect_disable(pd->data->bp_infracfg, pd->infracfg);
पूर्ण

अटल पूर्णांक scpsys_regulator_enable(काष्ठा regulator *supply)
अणु
	वापस supply ? regulator_enable(supply) : 0;
पूर्ण

अटल पूर्णांक scpsys_regulator_disable(काष्ठा regulator *supply)
अणु
	वापस supply ? regulator_disable(supply) : 0;
पूर्ण

अटल पूर्णांक scpsys_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा scpsys_करोमुख्य *pd = container_of(genpd, काष्ठा scpsys_करोमुख्य, genpd);
	काष्ठा scpsys *scpsys = pd->scpsys;
	bool पंचांगp;
	पूर्णांक ret;

	ret = scpsys_regulator_enable(pd->supply);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_enable(pd->num_clks, pd->clks);
	अगर (ret)
		जाओ err_reg;

	/* subsys घातer on */
	regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_ON_BIT);
	regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_ON_2ND_BIT);

	/* रुको until PWR_ACK = 1 */
	ret = पढ़ोx_poll_समयout(scpsys_करोमुख्य_is_on, pd, पंचांगp, पंचांगp, MTK_POLL_DELAY_US,
				 MTK_POLL_TIMEOUT);
	अगर (ret < 0)
		जाओ err_pwr_ack;

	regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_CLK_DIS_BIT);
	regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_ISO_BIT);
	regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_RST_B_BIT);

	ret = clk_bulk_enable(pd->num_subsys_clks, pd->subsys_clks);
	अगर (ret)
		जाओ err_pwr_ack;

	ret = scpsys_sram_enable(pd);
	अगर (ret < 0)
		जाओ err_disable_subsys_clks;

	ret = scpsys_bus_protect_disable(pd);
	अगर (ret < 0)
		जाओ err_disable_sram;

	वापस 0;

err_disable_sram:
	scpsys_sram_disable(pd);
err_disable_subsys_clks:
	clk_bulk_disable(pd->num_subsys_clks, pd->subsys_clks);
err_pwr_ack:
	clk_bulk_disable(pd->num_clks, pd->clks);
err_reg:
	scpsys_regulator_disable(pd->supply);
	वापस ret;
पूर्ण

अटल पूर्णांक scpsys_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा scpsys_करोमुख्य *pd = container_of(genpd, काष्ठा scpsys_करोमुख्य, genpd);
	काष्ठा scpsys *scpsys = pd->scpsys;
	bool पंचांगp;
	पूर्णांक ret;

	ret = scpsys_bus_protect_enable(pd);
	अगर (ret < 0)
		वापस ret;

	ret = scpsys_sram_disable(pd);
	अगर (ret < 0)
		वापस ret;

	clk_bulk_disable(pd->num_subsys_clks, pd->subsys_clks);

	/* subsys घातer off */
	regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_RST_B_BIT);
	regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_ISO_BIT);
	regmap_set_bits(scpsys->base, pd->data->ctl_offs, PWR_CLK_DIS_BIT);
	regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_ON_2ND_BIT);
	regmap_clear_bits(scpsys->base, pd->data->ctl_offs, PWR_ON_BIT);

	/* रुको until PWR_ACK = 0 */
	ret = पढ़ोx_poll_समयout(scpsys_करोमुख्य_is_on, pd, पंचांगp, !पंचांगp, MTK_POLL_DELAY_US,
				 MTK_POLL_TIMEOUT);
	अगर (ret < 0)
		वापस ret;

	clk_bulk_disable(pd->num_clks, pd->clks);

	scpsys_regulator_disable(pd->supply);

	वापस 0;
पूर्ण

अटल काष्ठा
generic_pm_करोमुख्य *scpsys_add_one_करोमुख्य(काष्ठा scpsys *scpsys, काष्ठा device_node *node)
अणु
	स्थिर काष्ठा scpsys_करोमुख्य_data *करोमुख्य_data;
	काष्ठा scpsys_करोमुख्य *pd;
	काष्ठा device_node *root_node = scpsys->dev->of_node;
	काष्ठा property *prop;
	स्थिर अक्षर *clk_name;
	पूर्णांक i, ret, num_clks;
	काष्ठा clk *clk;
	पूर्णांक clk_ind = 0;
	u32 id;

	ret = of_property_पढ़ो_u32(node, "reg", &id);
	अगर (ret) अणु
		dev_err(scpsys->dev, "%pOF: failed to retrieve domain id from reg: %d\n",
			node, ret);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (id >= scpsys->soc_data->num_करोमुख्यs) अणु
		dev_err(scpsys->dev, "%pOF: invalid domain id %d\n", node, id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	करोमुख्य_data = &scpsys->soc_data->करोमुख्यs_data[id];
	अगर (करोमुख्य_data->sta_mask == 0) अणु
		dev_err(scpsys->dev, "%pOF: undefined domain id %d\n", node, id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pd = devm_kzalloc(scpsys->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);

	pd->data = करोमुख्य_data;
	pd->scpsys = scpsys;

	अगर (MTK_SCPD_CAPS(pd, MTK_SCPD_DOMAIN_SUPPLY)) अणु
		/*
		 * Find regulator in current घातer करोमुख्य node.
		 * devm_regulator_get() finds regulator in a node and its child
		 * node, so set of_node to current घातer करोमुख्य node then change
		 * back to original node after regulator is found क्रम current
		 * घातer करोमुख्य node.
		 */
		scpsys->dev->of_node = node;
		pd->supply = devm_regulator_get(scpsys->dev, "domain");
		scpsys->dev->of_node = root_node;
		अगर (IS_ERR(pd->supply)) अणु
			dev_err_probe(scpsys->dev, PTR_ERR(pd->supply),
				      "%pOF: failed to get power supply.\n",
				      node);
			वापस ERR_CAST(pd->supply);
		पूर्ण
	पूर्ण

	pd->infracfg = syscon_regmap_lookup_by_phandle_optional(node, "mediatek,infracfg");
	अगर (IS_ERR(pd->infracfg))
		वापस ERR_CAST(pd->infracfg);

	pd->smi = syscon_regmap_lookup_by_phandle_optional(node, "mediatek,smi");
	अगर (IS_ERR(pd->smi))
		वापस ERR_CAST(pd->smi);

	num_clks = of_clk_get_parent_count(node);
	अगर (num_clks > 0) अणु
		/* Calculate number of subsys_clks */
		of_property_क्रम_each_string(node, "clock-names", prop, clk_name) अणु
			अक्षर *subsys;

			subsys = म_अक्षर(clk_name, '-');
			अगर (subsys)
				pd->num_subsys_clks++;
			अन्यथा
				pd->num_clks++;
		पूर्ण

		pd->clks = devm_kसुस्मृति(scpsys->dev, pd->num_clks, माप(*pd->clks), GFP_KERNEL);
		अगर (!pd->clks)
			वापस ERR_PTR(-ENOMEM);

		pd->subsys_clks = devm_kसुस्मृति(scpsys->dev, pd->num_subsys_clks,
					       माप(*pd->subsys_clks), GFP_KERNEL);
		अगर (!pd->subsys_clks)
			वापस ERR_PTR(-ENOMEM);

	पूर्ण

	क्रम (i = 0; i < pd->num_clks; i++) अणु
		clk = of_clk_get(node, i);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			dev_err_probe(scpsys->dev, ret,
				      "%pOF: failed to get clk at index %d: %d\n", node, i, ret);
			जाओ err_put_घड़ीs;
		पूर्ण

		pd->clks[clk_ind++].clk = clk;
	पूर्ण

	क्रम (i = 0; i < pd->num_subsys_clks; i++) अणु
		clk = of_clk_get(node, i + clk_ind);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			dev_err_probe(scpsys->dev, ret,
				      "%pOF: failed to get clk at index %d: %d\n", node,
				      i + clk_ind, ret);
			जाओ err_put_subsys_घड़ीs;
		पूर्ण

		pd->subsys_clks[i].clk = clk;
	पूर्ण

	ret = clk_bulk_prepare(pd->num_clks, pd->clks);
	अगर (ret)
		जाओ err_put_subsys_घड़ीs;

	ret = clk_bulk_prepare(pd->num_subsys_clks, pd->subsys_clks);
	अगर (ret)
		जाओ err_unprepare_घड़ीs;

	/*
	 * Initially turn on all करोमुख्यs to make the करोमुख्यs usable
	 * with !CONFIG_PM and to get the hardware in sync with the
	 * software.  The unused करोमुख्यs will be चयनed off during
	 * late_init समय.
	 */
	अगर (MTK_SCPD_CAPS(pd, MTK_SCPD_KEEP_DEFAULT_OFF)) अणु
		अगर (scpsys_करोमुख्य_is_on(pd))
			dev_warn(scpsys->dev,
				 "%pOF: A default off power domain has been ON\n", node);
	पूर्ण अन्यथा अणु
		ret = scpsys_घातer_on(&pd->genpd);
		अगर (ret < 0) अणु
			dev_err(scpsys->dev, "%pOF: failed to power on domain: %d\n", node, ret);
			जाओ err_unprepare_घड़ीs;
		पूर्ण
	पूर्ण

	अगर (scpsys->करोमुख्यs[id]) अणु
		ret = -EINVAL;
		dev_err(scpsys->dev,
			"power domain with id %d already exists, check your device-tree\n", id);
		जाओ err_unprepare_subsys_घड़ीs;
	पूर्ण

	अगर (!pd->data->name)
		pd->genpd.name = node->name;
	अन्यथा
		pd->genpd.name = pd->data->name;

	pd->genpd.घातer_off = scpsys_घातer_off;
	pd->genpd.घातer_on = scpsys_घातer_on;

	अगर (MTK_SCPD_CAPS(pd, MTK_SCPD_KEEP_DEFAULT_OFF))
		pm_genpd_init(&pd->genpd, शून्य, true);
	अन्यथा
		pm_genpd_init(&pd->genpd, शून्य, false);

	scpsys->करोमुख्यs[id] = &pd->genpd;

	वापस scpsys->pd_data.करोमुख्यs[id];

err_unprepare_subsys_घड़ीs:
	clk_bulk_unprepare(pd->num_subsys_clks, pd->subsys_clks);
err_unprepare_घड़ीs:
	clk_bulk_unprepare(pd->num_clks, pd->clks);
err_put_subsys_घड़ीs:
	clk_bulk_put(pd->num_subsys_clks, pd->subsys_clks);
err_put_घड़ीs:
	clk_bulk_put(pd->num_clks, pd->clks);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक scpsys_add_subकरोमुख्य(काष्ठा scpsys *scpsys, काष्ठा device_node *parent)
अणु
	काष्ठा generic_pm_करोमुख्य *child_pd, *parent_pd;
	काष्ठा device_node *child;
	पूर्णांक ret;

	क्रम_each_child_of_node(parent, child) अणु
		u32 id;

		ret = of_property_पढ़ो_u32(parent, "reg", &id);
		अगर (ret) अणु
			dev_err(scpsys->dev, "%pOF: failed to get parent domain id\n", child);
			जाओ err_put_node;
		पूर्ण

		अगर (!scpsys->pd_data.करोमुख्यs[id]) अणु
			ret = -EINVAL;
			dev_err(scpsys->dev, "power domain with id %d does not exist\n", id);
			जाओ err_put_node;
		पूर्ण

		parent_pd = scpsys->pd_data.करोमुख्यs[id];

		child_pd = scpsys_add_one_करोमुख्य(scpsys, child);
		अगर (IS_ERR(child_pd)) अणु
			ret = PTR_ERR(child_pd);
			dev_err_probe(scpsys->dev, ret, "%pOF: failed to get child domain id\n",
				      child);
			जाओ err_put_node;
		पूर्ण

		ret = pm_genpd_add_subकरोमुख्य(parent_pd, child_pd);
		अगर (ret) अणु
			dev_err(scpsys->dev, "failed to add %s subdomain to parent %s\n",
				child_pd->name, parent_pd->name);
			जाओ err_put_node;
		पूर्ण अन्यथा अणु
			dev_dbg(scpsys->dev, "%s add subdomain: %s\n", parent_pd->name,
				child_pd->name);
		पूर्ण

		/* recursive call to add all subकरोमुख्यs */
		ret = scpsys_add_subकरोमुख्य(scpsys, child);
		अगर (ret)
			जाओ err_put_node;
	पूर्ण

	वापस 0;

err_put_node:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल व्योम scpsys_हटाओ_one_करोमुख्य(काष्ठा scpsys_करोमुख्य *pd)
अणु
	पूर्णांक ret;

	अगर (scpsys_करोमुख्य_is_on(pd))
		scpsys_घातer_off(&pd->genpd);

	/*
	 * We're in the error cleanup alपढ़ोy, so we only complain,
	 * but won't emit another error on top of the original one.
	 */
	ret = pm_genpd_हटाओ(&pd->genpd);
	अगर (ret < 0)
		dev_err(pd->scpsys->dev,
			"failed to remove domain '%s' : %d - state may be inconsistent\n",
			pd->genpd.name, ret);

	clk_bulk_unprepare(pd->num_clks, pd->clks);
	clk_bulk_put(pd->num_clks, pd->clks);

	clk_bulk_unprepare(pd->num_subsys_clks, pd->subsys_clks);
	clk_bulk_put(pd->num_subsys_clks, pd->subsys_clks);
पूर्ण

अटल व्योम scpsys_करोमुख्य_cleanup(काष्ठा scpsys *scpsys)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा scpsys_करोमुख्य *pd;
	पूर्णांक i;

	क्रम (i = scpsys->pd_data.num_करोमुख्यs - 1; i >= 0; i--) अणु
		genpd = scpsys->pd_data.करोमुख्यs[i];
		अगर (genpd) अणु
			pd = to_scpsys_करोमुख्य(genpd);
			scpsys_हटाओ_one_करोमुख्य(pd);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id scpsys_of_match[] = अणु
	अणु
		.compatible = "mediatek,mt8167-power-controller",
		.data = &mt8167_scpsys_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8173-power-controller",
		.data = &mt8173_scpsys_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183-power-controller",
		.data = &mt8183_scpsys_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8192-power-controller",
		.data = &mt8192_scpsys_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक scpsys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा scpsys_soc_data *soc;
	काष्ठा device_node *node;
	काष्ठा device *parent;
	काष्ठा scpsys *scpsys;
	पूर्णांक ret;

	soc = of_device_get_match_data(&pdev->dev);
	अगर (!soc) अणु
		dev_err(&pdev->dev, "no power controller data\n");
		वापस -EINVAL;
	पूर्ण

	scpsys = devm_kzalloc(dev, काष्ठा_size(scpsys, करोमुख्यs, soc->num_करोमुख्यs), GFP_KERNEL);
	अगर (!scpsys)
		वापस -ENOMEM;

	scpsys->dev = dev;
	scpsys->soc_data = soc;

	scpsys->pd_data.करोमुख्यs = scpsys->करोमुख्यs;
	scpsys->pd_data.num_करोमुख्यs = soc->num_करोमुख्यs;

	parent = dev->parent;
	अगर (!parent) अणु
		dev_err(dev, "no parent for syscon devices\n");
		वापस -ENODEV;
	पूर्ण

	scpsys->base = syscon_node_to_regmap(parent->of_node);
	अगर (IS_ERR(scpsys->base)) अणु
		dev_err(dev, "no regmap available\n");
		वापस PTR_ERR(scpsys->base);
	पूर्ण

	ret = -ENODEV;
	क्रम_each_available_child_of_node(np, node) अणु
		काष्ठा generic_pm_करोमुख्य *करोमुख्य;

		करोमुख्य = scpsys_add_one_करोमुख्य(scpsys, node);
		अगर (IS_ERR(करोमुख्य)) अणु
			ret = PTR_ERR(करोमुख्य);
			of_node_put(node);
			जाओ err_cleanup_करोमुख्यs;
		पूर्ण

		ret = scpsys_add_subकरोमुख्य(scpsys, node);
		अगर (ret) अणु
			of_node_put(node);
			जाओ err_cleanup_करोमुख्यs;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_dbg(dev, "no power domains present\n");
		वापस ret;
	पूर्ण

	ret = of_genpd_add_provider_onecell(np, &scpsys->pd_data);
	अगर (ret) अणु
		dev_err(dev, "failed to add provider: %d\n", ret);
		जाओ err_cleanup_करोमुख्यs;
	पूर्ण

	वापस 0;

err_cleanup_करोमुख्यs:
	scpsys_करोमुख्य_cleanup(scpsys);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver scpsys_pm_करोमुख्य_driver = अणु
	.probe = scpsys_probe,
	.driver = अणु
		.name = "mtk-power-controller",
		.suppress_bind_attrs = true,
		.of_match_table = scpsys_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(scpsys_pm_करोमुख्य_driver);
