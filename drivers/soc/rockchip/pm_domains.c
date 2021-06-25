<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip Generic घातer करोमुख्य support.
 *
 * Copyright (c) 2015 ROCKCHIP, Co. Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <dt-bindings/घातer/px30-घातer.h>
#समावेश <dt-bindings/घातer/rk3036-घातer.h>
#समावेश <dt-bindings/घातer/rk3066-घातer.h>
#समावेश <dt-bindings/घातer/rk3128-घातer.h>
#समावेश <dt-bindings/घातer/rk3188-घातer.h>
#समावेश <dt-bindings/घातer/rk3228-घातer.h>
#समावेश <dt-bindings/घातer/rk3288-घातer.h>
#समावेश <dt-bindings/घातer/rk3328-घातer.h>
#समावेश <dt-bindings/घातer/rk3366-घातer.h>
#समावेश <dt-bindings/घातer/rk3368-घातer.h>
#समावेश <dt-bindings/घातer/rk3399-घातer.h>

काष्ठा rockchip_करोमुख्य_info अणु
	पूर्णांक pwr_mask;
	पूर्णांक status_mask;
	पूर्णांक req_mask;
	पूर्णांक idle_mask;
	पूर्णांक ack_mask;
	bool active_wakeup;
	पूर्णांक pwr_w_mask;
	पूर्णांक req_w_mask;
पूर्ण;

काष्ठा rockchip_pmu_info अणु
	u32 pwr_offset;
	u32 status_offset;
	u32 req_offset;
	u32 idle_offset;
	u32 ack_offset;

	u32 core_pwrcnt_offset;
	u32 gpu_pwrcnt_offset;

	अचिन्हित पूर्णांक core_घातer_transition_समय;
	अचिन्हित पूर्णांक gpu_घातer_transition_समय;

	पूर्णांक num_करोमुख्यs;
	स्थिर काष्ठा rockchip_करोमुख्य_info *करोमुख्य_info;
पूर्ण;

#घोषणा MAX_QOS_REGS_NUM	5
#घोषणा QOS_PRIORITY		0x08
#घोषणा QOS_MODE		0x0c
#घोषणा QOS_BANDWIDTH		0x10
#घोषणा QOS_SATURATION		0x14
#घोषणा QOS_EXTCONTROL		0x18

काष्ठा rockchip_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	स्थिर काष्ठा rockchip_करोमुख्य_info *info;
	काष्ठा rockchip_pmu *pmu;
	पूर्णांक num_qos;
	काष्ठा regmap **qos_regmap;
	u32 *qos_save_regs[MAX_QOS_REGS_NUM];
	पूर्णांक num_clks;
	काष्ठा clk_bulk_data *clks;
पूर्ण;

काष्ठा rockchip_pmu अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा rockchip_pmu_info *info;
	काष्ठा mutex mutex; /* mutex lock क्रम pmu */
	काष्ठा genpd_onecell_data genpd_data;
	काष्ठा generic_pm_करोमुख्य *करोमुख्यs[];
पूर्ण;

#घोषणा to_rockchip_pd(gpd) container_of(gpd, काष्ठा rockchip_pm_करोमुख्य, genpd)

#घोषणा DOMAIN(pwr, status, req, idle, ack, wakeup)	\
अणु							\
	.pwr_mask = (pwr),				\
	.status_mask = (status),			\
	.req_mask = (req),				\
	.idle_mask = (idle),				\
	.ack_mask = (ack),				\
	.active_wakeup = (wakeup),			\
पूर्ण

#घोषणा DOMAIN_M(pwr, status, req, idle, ack, wakeup)	\
अणु							\
	.pwr_w_mask = (pwr) << 16,			\
	.pwr_mask = (pwr),				\
	.status_mask = (status),			\
	.req_w_mask = (req) << 16,			\
	.req_mask = (req),				\
	.idle_mask = (idle),				\
	.ack_mask = (ack),				\
	.active_wakeup = wakeup,			\
पूर्ण

#घोषणा DOMAIN_RK3036(req, ack, idle, wakeup)		\
अणु							\
	.req_mask = (req),				\
	.req_w_mask = (req) << 16,			\
	.ack_mask = (ack),				\
	.idle_mask = (idle),				\
	.active_wakeup = wakeup,			\
पूर्ण

#घोषणा DOMAIN_PX30(pwr, status, req, wakeup)		\
	DOMAIN_M(pwr, status, req, (req) << 16, req, wakeup)

#घोषणा DOMAIN_RK3288(pwr, status, req, wakeup)		\
	DOMAIN(pwr, status, req, req, (req) << 16, wakeup)

#घोषणा DOMAIN_RK3328(pwr, status, req, wakeup)		\
	DOMAIN_M(pwr, pwr, req, (req) << 10, req, wakeup)

#घोषणा DOMAIN_RK3368(pwr, status, req, wakeup)		\
	DOMAIN(pwr, status, req, (req) << 16, req, wakeup)

#घोषणा DOMAIN_RK3399(pwr, status, req, wakeup)		\
	DOMAIN(pwr, status, req, req, req, wakeup)

अटल bool rockchip_pmu_करोमुख्य_is_idle(काष्ठा rockchip_pm_करोमुख्य *pd)
अणु
	काष्ठा rockchip_pmu *pmu = pd->pmu;
	स्थिर काष्ठा rockchip_करोमुख्य_info *pd_info = pd->info;
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(pmu->regmap, pmu->info->idle_offset, &val);
	वापस (val & pd_info->idle_mask) == pd_info->idle_mask;
पूर्ण

अटल अचिन्हित पूर्णांक rockchip_pmu_पढ़ो_ack(काष्ठा rockchip_pmu *pmu)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(pmu->regmap, pmu->info->ack_offset, &val);
	वापस val;
पूर्ण

अटल पूर्णांक rockchip_pmu_set_idle_request(काष्ठा rockchip_pm_करोमुख्य *pd,
					 bool idle)
अणु
	स्थिर काष्ठा rockchip_करोमुख्य_info *pd_info = pd->info;
	काष्ठा generic_pm_करोमुख्य *genpd = &pd->genpd;
	काष्ठा rockchip_pmu *pmu = pd->pmu;
	अचिन्हित पूर्णांक target_ack;
	अचिन्हित पूर्णांक val;
	bool is_idle;
	पूर्णांक ret;

	अगर (pd_info->req_mask == 0)
		वापस 0;
	अन्यथा अगर (pd_info->req_w_mask)
		regmap_ग_लिखो(pmu->regmap, pmu->info->req_offset,
			     idle ? (pd_info->req_mask | pd_info->req_w_mask) :
			     pd_info->req_w_mask);
	अन्यथा
		regmap_update_bits(pmu->regmap, pmu->info->req_offset,
				   pd_info->req_mask, idle ? -1U : 0);

	dsb(sy);

	/* Wait util idle_ack = 1 */
	target_ack = idle ? pd_info->ack_mask : 0;
	ret = पढ़ोx_poll_समयout_atomic(rockchip_pmu_पढ़ो_ack, pmu, val,
					(val & pd_info->ack_mask) == target_ack,
					0, 10000);
	अगर (ret) अणु
		dev_err(pmu->dev,
			"failed to get ack on domain '%s', val=0x%x\n",
			genpd->name, val);
		वापस ret;
	पूर्ण

	ret = पढ़ोx_poll_समयout_atomic(rockchip_pmu_करोमुख्य_is_idle, pd,
					is_idle, is_idle == idle, 0, 10000);
	अगर (ret) अणु
		dev_err(pmu->dev,
			"failed to set idle on domain '%s', val=%d\n",
			genpd->name, is_idle);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pmu_save_qos(काष्ठा rockchip_pm_करोमुख्य *pd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pd->num_qos; i++) अणु
		regmap_पढ़ो(pd->qos_regmap[i],
			    QOS_PRIORITY,
			    &pd->qos_save_regs[0][i]);
		regmap_पढ़ो(pd->qos_regmap[i],
			    QOS_MODE,
			    &pd->qos_save_regs[1][i]);
		regmap_पढ़ो(pd->qos_regmap[i],
			    QOS_BANDWIDTH,
			    &pd->qos_save_regs[2][i]);
		regmap_पढ़ो(pd->qos_regmap[i],
			    QOS_SATURATION,
			    &pd->qos_save_regs[3][i]);
		regmap_पढ़ो(pd->qos_regmap[i],
			    QOS_EXTCONTROL,
			    &pd->qos_save_regs[4][i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pmu_restore_qos(काष्ठा rockchip_pm_करोमुख्य *pd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pd->num_qos; i++) अणु
		regmap_ग_लिखो(pd->qos_regmap[i],
			     QOS_PRIORITY,
			     pd->qos_save_regs[0][i]);
		regmap_ग_लिखो(pd->qos_regmap[i],
			     QOS_MODE,
			     pd->qos_save_regs[1][i]);
		regmap_ग_लिखो(pd->qos_regmap[i],
			     QOS_BANDWIDTH,
			     pd->qos_save_regs[2][i]);
		regmap_ग_लिखो(pd->qos_regmap[i],
			     QOS_SATURATION,
			     pd->qos_save_regs[3][i]);
		regmap_ग_लिखो(pd->qos_regmap[i],
			     QOS_EXTCONTROL,
			     pd->qos_save_regs[4][i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rockchip_pmu_करोमुख्य_is_on(काष्ठा rockchip_pm_करोमुख्य *pd)
अणु
	काष्ठा rockchip_pmu *pmu = pd->pmu;
	अचिन्हित पूर्णांक val;

	/* check idle status क्रम idle-only करोमुख्यs */
	अगर (pd->info->status_mask == 0)
		वापस !rockchip_pmu_करोमुख्य_is_idle(pd);

	regmap_पढ़ो(pmu->regmap, pmu->info->status_offset, &val);

	/* 1'b0: power on, 1'b1: घातer off */
	वापस !(val & pd->info->status_mask);
पूर्ण

अटल व्योम rockchip_करो_pmu_set_घातer_करोमुख्य(काष्ठा rockchip_pm_करोमुख्य *pd,
					     bool on)
अणु
	काष्ठा rockchip_pmu *pmu = pd->pmu;
	काष्ठा generic_pm_करोमुख्य *genpd = &pd->genpd;
	bool is_on;

	अगर (pd->info->pwr_mask == 0)
		वापस;
	अन्यथा अगर (pd->info->pwr_w_mask)
		regmap_ग_लिखो(pmu->regmap, pmu->info->pwr_offset,
			     on ? pd->info->pwr_w_mask :
			     (pd->info->pwr_mask | pd->info->pwr_w_mask));
	अन्यथा
		regmap_update_bits(pmu->regmap, pmu->info->pwr_offset,
				   pd->info->pwr_mask, on ? 0 : -1U);

	dsb(sy);

	अगर (पढ़ोx_poll_समयout_atomic(rockchip_pmu_करोमुख्य_is_on, pd, is_on,
				      is_on == on, 0, 10000)) अणु
		dev_err(pmu->dev,
			"failed to set domain '%s', val=%d\n",
			genpd->name, is_on);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_pd_घातer(काष्ठा rockchip_pm_करोमुख्य *pd, bool घातer_on)
अणु
	काष्ठा rockchip_pmu *pmu = pd->pmu;
	पूर्णांक ret;

	mutex_lock(&pmu->mutex);

	अगर (rockchip_pmu_करोमुख्य_is_on(pd) != घातer_on) अणु
		ret = clk_bulk_enable(pd->num_clks, pd->clks);
		अगर (ret < 0) अणु
			dev_err(pmu->dev, "failed to enable clocks\n");
			mutex_unlock(&pmu->mutex);
			वापस ret;
		पूर्ण

		अगर (!घातer_on) अणु
			rockchip_pmu_save_qos(pd);

			/* अगर घातering करोwn, idle request to NIU first */
			rockchip_pmu_set_idle_request(pd, true);
		पूर्ण

		rockchip_करो_pmu_set_घातer_करोमुख्य(pd, घातer_on);

		अगर (घातer_on) अणु
			/* अगर घातering up, leave idle mode */
			rockchip_pmu_set_idle_request(pd, false);

			rockchip_pmu_restore_qos(pd);
		पूर्ण

		clk_bulk_disable(pd->num_clks, pd->clks);
	पूर्ण

	mutex_unlock(&pmu->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rockchip_pm_करोमुख्य *pd = to_rockchip_pd(करोमुख्य);

	वापस rockchip_pd_घातer(pd, true);
पूर्ण

अटल पूर्णांक rockchip_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rockchip_pm_करोमुख्य *pd = to_rockchip_pd(करोमुख्य);

	वापस rockchip_pd_घातer(pd, false);
पूर्ण

अटल पूर्णांक rockchip_pd_attach_dev(काष्ठा generic_pm_करोमुख्य *genpd,
				  काष्ठा device *dev)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;
	पूर्णांक error;

	dev_dbg(dev, "attaching to power domain '%s'\n", genpd->name);

	error = pm_clk_create(dev);
	अगर (error) अणु
		dev_err(dev, "pm_clk_create failed %d\n", error);
		वापस error;
	पूर्ण

	i = 0;
	जबतक ((clk = of_clk_get(dev->of_node, i++)) && !IS_ERR(clk)) अणु
		dev_dbg(dev, "adding clock '%pC' to list of PM clocks\n", clk);
		error = pm_clk_add_clk(dev, clk);
		अगर (error) अणु
			dev_err(dev, "pm_clk_add_clk failed %d\n", error);
			clk_put(clk);
			pm_clk_destroy(dev);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rockchip_pd_detach_dev(काष्ठा generic_pm_करोमुख्य *genpd,
				   काष्ठा device *dev)
अणु
	dev_dbg(dev, "detaching from power domain '%s'\n", genpd->name);

	pm_clk_destroy(dev);
पूर्ण

अटल पूर्णांक rockchip_pm_add_one_करोमुख्य(काष्ठा rockchip_pmu *pmu,
				      काष्ठा device_node *node)
अणु
	स्थिर काष्ठा rockchip_करोमुख्य_info *pd_info;
	काष्ठा rockchip_pm_करोमुख्य *pd;
	काष्ठा device_node *qos_node;
	पूर्णांक i, j;
	u32 id;
	पूर्णांक error;

	error = of_property_पढ़ो_u32(node, "reg", &id);
	अगर (error) अणु
		dev_err(pmu->dev,
			"%pOFn: failed to retrieve domain id (reg): %d\n",
			node, error);
		वापस -EINVAL;
	पूर्ण

	अगर (id >= pmu->info->num_करोमुख्यs) अणु
		dev_err(pmu->dev, "%pOFn: invalid domain id %d\n",
			node, id);
		वापस -EINVAL;
	पूर्ण

	pd_info = &pmu->info->करोमुख्य_info[id];
	अगर (!pd_info) अणु
		dev_err(pmu->dev, "%pOFn: undefined domain id %d\n",
			node, id);
		वापस -EINVAL;
	पूर्ण

	pd = devm_kzalloc(pmu->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pd->info = pd_info;
	pd->pmu = pmu;

	pd->num_clks = of_clk_get_parent_count(node);
	अगर (pd->num_clks > 0) अणु
		pd->clks = devm_kसुस्मृति(pmu->dev, pd->num_clks,
					माप(*pd->clks), GFP_KERNEL);
		अगर (!pd->clks)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		dev_dbg(pmu->dev, "%pOFn: doesn't have clocks: %d\n",
			node, pd->num_clks);
		pd->num_clks = 0;
	पूर्ण

	क्रम (i = 0; i < pd->num_clks; i++) अणु
		pd->clks[i].clk = of_clk_get(node, i);
		अगर (IS_ERR(pd->clks[i].clk)) अणु
			error = PTR_ERR(pd->clks[i].clk);
			dev_err(pmu->dev,
				"%pOFn: failed to get clk at index %d: %d\n",
				node, i, error);
			वापस error;
		पूर्ण
	पूर्ण

	error = clk_bulk_prepare(pd->num_clks, pd->clks);
	अगर (error)
		जाओ err_put_घड़ीs;

	pd->num_qos = of_count_phandle_with_args(node, "pm_qos",
						 शून्य);

	अगर (pd->num_qos > 0) अणु
		pd->qos_regmap = devm_kसुस्मृति(pmu->dev, pd->num_qos,
					      माप(*pd->qos_regmap),
					      GFP_KERNEL);
		अगर (!pd->qos_regmap) अणु
			error = -ENOMEM;
			जाओ err_unprepare_घड़ीs;
		पूर्ण

		क्रम (j = 0; j < MAX_QOS_REGS_NUM; j++) अणु
			pd->qos_save_regs[j] = devm_kसुस्मृति(pmu->dev,
							    pd->num_qos,
							    माप(u32),
							    GFP_KERNEL);
			अगर (!pd->qos_save_regs[j]) अणु
				error = -ENOMEM;
				जाओ err_unprepare_घड़ीs;
			पूर्ण
		पूर्ण

		क्रम (j = 0; j < pd->num_qos; j++) अणु
			qos_node = of_parse_phandle(node, "pm_qos", j);
			अगर (!qos_node) अणु
				error = -ENODEV;
				जाओ err_unprepare_घड़ीs;
			पूर्ण
			pd->qos_regmap[j] = syscon_node_to_regmap(qos_node);
			अगर (IS_ERR(pd->qos_regmap[j])) अणु
				error = -ENODEV;
				of_node_put(qos_node);
				जाओ err_unprepare_घड़ीs;
			पूर्ण
			of_node_put(qos_node);
		पूर्ण
	पूर्ण

	error = rockchip_pd_घातer(pd, true);
	अगर (error) अणु
		dev_err(pmu->dev,
			"failed to power on domain '%pOFn': %d\n",
			node, error);
		जाओ err_unprepare_घड़ीs;
	पूर्ण

	pd->genpd.name = node->name;
	pd->genpd.घातer_off = rockchip_pd_घातer_off;
	pd->genpd.घातer_on = rockchip_pd_घातer_on;
	pd->genpd.attach_dev = rockchip_pd_attach_dev;
	pd->genpd.detach_dev = rockchip_pd_detach_dev;
	pd->genpd.flags = GENPD_FLAG_PM_CLK;
	अगर (pd_info->active_wakeup)
		pd->genpd.flags |= GENPD_FLAG_ACTIVE_WAKEUP;
	pm_genpd_init(&pd->genpd, शून्य, false);

	pmu->genpd_data.करोमुख्यs[id] = &pd->genpd;
	वापस 0;

err_unprepare_घड़ीs:
	clk_bulk_unprepare(pd->num_clks, pd->clks);
err_put_घड़ीs:
	clk_bulk_put(pd->num_clks, pd->clks);
	वापस error;
पूर्ण

अटल व्योम rockchip_pm_हटाओ_one_करोमुख्य(काष्ठा rockchip_pm_करोमुख्य *pd)
अणु
	पूर्णांक ret;

	/*
	 * We're in the error cleanup alपढ़ोy, so we only complain,
	 * but won't emit another error on top of the original one.
	 */
	ret = pm_genpd_हटाओ(&pd->genpd);
	अगर (ret < 0)
		dev_err(pd->pmu->dev, "failed to remove domain '%s' : %d - state may be inconsistent\n",
			pd->genpd.name, ret);

	clk_bulk_unprepare(pd->num_clks, pd->clks);
	clk_bulk_put(pd->num_clks, pd->clks);

	/* protect the zeroing of pm->num_clks */
	mutex_lock(&pd->pmu->mutex);
	pd->num_clks = 0;
	mutex_unlock(&pd->pmu->mutex);

	/* devm will मुक्त our memory */
पूर्ण

अटल व्योम rockchip_pm_करोमुख्य_cleanup(काष्ठा rockchip_pmu *pmu)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा rockchip_pm_करोमुख्य *pd;
	पूर्णांक i;

	क्रम (i = 0; i < pmu->genpd_data.num_करोमुख्यs; i++) अणु
		genpd = pmu->genpd_data.करोमुख्यs[i];
		अगर (genpd) अणु
			pd = to_rockchip_pd(genpd);
			rockchip_pm_हटाओ_one_करोमुख्य(pd);
		पूर्ण
	पूर्ण

	/* devm will मुक्त our memory */
पूर्ण

अटल व्योम rockchip_configure_pd_cnt(काष्ठा rockchip_pmu *pmu,
				      u32 करोमुख्य_reg_offset,
				      अचिन्हित पूर्णांक count)
अणु
	/* First configure करोमुख्य घातer करोwn transition count ... */
	regmap_ग_लिखो(pmu->regmap, करोमुख्य_reg_offset, count);
	/* ... and then घातer up count. */
	regmap_ग_लिखो(pmu->regmap, करोमुख्य_reg_offset + 4, count);
पूर्ण

अटल पूर्णांक rockchip_pm_add_subकरोमुख्य(काष्ठा rockchip_pmu *pmu,
				     काष्ठा device_node *parent)
अणु
	काष्ठा device_node *np;
	काष्ठा generic_pm_करोमुख्य *child_करोमुख्य, *parent_करोमुख्य;
	पूर्णांक error;

	क्रम_each_child_of_node(parent, np) अणु
		u32 idx;

		error = of_property_पढ़ो_u32(parent, "reg", &idx);
		अगर (error) अणु
			dev_err(pmu->dev,
				"%pOFn: failed to retrieve domain id (reg): %d\n",
				parent, error);
			जाओ err_out;
		पूर्ण
		parent_करोमुख्य = pmu->genpd_data.करोमुख्यs[idx];

		error = rockchip_pm_add_one_करोमुख्य(pmu, np);
		अगर (error) अणु
			dev_err(pmu->dev, "failed to handle node %pOFn: %d\n",
				np, error);
			जाओ err_out;
		पूर्ण

		error = of_property_पढ़ो_u32(np, "reg", &idx);
		अगर (error) अणु
			dev_err(pmu->dev,
				"%pOFn: failed to retrieve domain id (reg): %d\n",
				np, error);
			जाओ err_out;
		पूर्ण
		child_करोमुख्य = pmu->genpd_data.करोमुख्यs[idx];

		error = pm_genpd_add_subकरोमुख्य(parent_करोमुख्य, child_करोमुख्य);
		अगर (error) अणु
			dev_err(pmu->dev, "%s failed to add subdomain %s: %d\n",
				parent_करोमुख्य->name, child_करोमुख्य->name, error);
			जाओ err_out;
		पूर्ण अन्यथा अणु
			dev_dbg(pmu->dev, "%s add subdomain: %s\n",
				parent_करोमुख्य->name, child_करोमुख्य->name);
		पूर्ण

		rockchip_pm_add_subकरोमुख्य(pmu, np);
	पूर्ण

	वापस 0;

err_out:
	of_node_put(np);
	वापस error;
पूर्ण

अटल पूर्णांक rockchip_pm_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *node;
	काष्ठा device *parent;
	काष्ठा rockchip_pmu *pmu;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा rockchip_pmu_info *pmu_info;
	पूर्णांक error;

	अगर (!np) अणु
		dev_err(dev, "device tree node not found\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data) अणु
		dev_err(dev, "missing pmu data\n");
		वापस -EINVAL;
	पूर्ण

	pmu_info = match->data;

	pmu = devm_kzalloc(dev,
			   काष्ठा_size(pmu, करोमुख्यs, pmu_info->num_करोमुख्यs),
			   GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;

	pmu->dev = &pdev->dev;
	mutex_init(&pmu->mutex);

	pmu->info = pmu_info;

	pmu->genpd_data.करोमुख्यs = pmu->करोमुख्यs;
	pmu->genpd_data.num_करोमुख्यs = pmu_info->num_करोमुख्यs;

	parent = dev->parent;
	अगर (!parent) अणु
		dev_err(dev, "no parent for syscon devices\n");
		वापस -ENODEV;
	पूर्ण

	pmu->regmap = syscon_node_to_regmap(parent->of_node);
	अगर (IS_ERR(pmu->regmap)) अणु
		dev_err(dev, "no regmap available\n");
		वापस PTR_ERR(pmu->regmap);
	पूर्ण

	/*
	 * Configure घातer up and करोwn transition delays क्रम CORE
	 * and GPU करोमुख्यs.
	 */
	अगर (pmu_info->core_घातer_transition_समय)
		rockchip_configure_pd_cnt(pmu, pmu_info->core_pwrcnt_offset,
					pmu_info->core_घातer_transition_समय);
	अगर (pmu_info->gpu_pwrcnt_offset)
		rockchip_configure_pd_cnt(pmu, pmu_info->gpu_pwrcnt_offset,
					pmu_info->gpu_घातer_transition_समय);

	error = -ENODEV;

	क्रम_each_available_child_of_node(np, node) अणु
		error = rockchip_pm_add_one_करोमुख्य(pmu, node);
		अगर (error) अणु
			dev_err(dev, "failed to handle node %pOFn: %d\n",
				node, error);
			of_node_put(node);
			जाओ err_out;
		पूर्ण

		error = rockchip_pm_add_subकरोमुख्य(pmu, node);
		अगर (error < 0) अणु
			dev_err(dev, "failed to handle subdomain node %pOFn: %d\n",
				node, error);
			of_node_put(node);
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (error) अणु
		dev_dbg(dev, "no power domains defined\n");
		जाओ err_out;
	पूर्ण

	error = of_genpd_add_provider_onecell(np, &pmu->genpd_data);
	अगर (error) अणु
		dev_err(dev, "failed to add provider: %d\n", error);
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	rockchip_pm_करोमुख्य_cleanup(pmu);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा rockchip_करोमुख्य_info px30_pm_करोमुख्यs[] = अणु
	[PX30_PD_USB]		= DOMAIN_PX30(BIT(5),  BIT(5),  BIT(10), false),
	[PX30_PD_SDCARD]	= DOMAIN_PX30(BIT(8),  BIT(8),  BIT(9),  false),
	[PX30_PD_GMAC]		= DOMAIN_PX30(BIT(10), BIT(10), BIT(6),  false),
	[PX30_PD_MMC_न_अंकD]	= DOMAIN_PX30(BIT(11), BIT(11), BIT(5),  false),
	[PX30_PD_VPU]		= DOMAIN_PX30(BIT(12), BIT(12), BIT(14), false),
	[PX30_PD_VO]		= DOMAIN_PX30(BIT(13), BIT(13), BIT(7),  false),
	[PX30_PD_VI]		= DOMAIN_PX30(BIT(14), BIT(14), BIT(8),  false),
	[PX30_PD_GPU]		= DOMAIN_PX30(BIT(15), BIT(15), BIT(2),  false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3036_pm_करोमुख्यs[] = अणु
	[RK3036_PD_MSCH]	= DOMAIN_RK3036(BIT(14), BIT(23), BIT(30), true),
	[RK3036_PD_CORE]	= DOMAIN_RK3036(BIT(13), BIT(17), BIT(24), false),
	[RK3036_PD_PERI]	= DOMAIN_RK3036(BIT(12), BIT(18), BIT(25), false),
	[RK3036_PD_VIO]		= DOMAIN_RK3036(BIT(11), BIT(19), BIT(26), false),
	[RK3036_PD_VPU]		= DOMAIN_RK3036(BIT(10), BIT(20), BIT(27), false),
	[RK3036_PD_GPU]		= DOMAIN_RK3036(BIT(9),  BIT(21), BIT(28), false),
	[RK3036_PD_SYS]		= DOMAIN_RK3036(BIT(8),  BIT(22), BIT(29), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3066_pm_करोमुख्यs[] = अणु
	[RK3066_PD_GPU]		= DOMAIN(BIT(9), BIT(9), BIT(3), BIT(24), BIT(29), false),
	[RK3066_PD_VIDEO]	= DOMAIN(BIT(8), BIT(8), BIT(4), BIT(23), BIT(28), false),
	[RK3066_PD_VIO]		= DOMAIN(BIT(7), BIT(7), BIT(5), BIT(22), BIT(27), false),
	[RK3066_PD_PERI]	= DOMAIN(BIT(6), BIT(6), BIT(2), BIT(25), BIT(30), false),
	[RK3066_PD_CPU]		= DOMAIN(0,      BIT(5), BIT(1), BIT(26), BIT(31), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3128_pm_करोमुख्यs[] = अणु
	[RK3128_PD_CORE]	= DOMAIN_RK3288(BIT(0), BIT(0), BIT(4), false),
	[RK3128_PD_MSCH]	= DOMAIN_RK3288(0,      0,      BIT(6), true),
	[RK3128_PD_VIO]		= DOMAIN_RK3288(BIT(3), BIT(3), BIT(2), false),
	[RK3128_PD_VIDEO]	= DOMAIN_RK3288(BIT(2), BIT(2), BIT(1), false),
	[RK3128_PD_GPU]		= DOMAIN_RK3288(BIT(1), BIT(1), BIT(3), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3188_pm_करोमुख्यs[] = अणु
	[RK3188_PD_GPU]		= DOMAIN(BIT(9), BIT(9), BIT(3), BIT(24), BIT(29), false),
	[RK3188_PD_VIDEO]	= DOMAIN(BIT(8), BIT(8), BIT(4), BIT(23), BIT(28), false),
	[RK3188_PD_VIO]		= DOMAIN(BIT(7), BIT(7), BIT(5), BIT(22), BIT(27), false),
	[RK3188_PD_PERI]	= DOMAIN(BIT(6), BIT(6), BIT(2), BIT(25), BIT(30), false),
	[RK3188_PD_CPU]		= DOMAIN(BIT(5), BIT(5), BIT(1), BIT(26), BIT(31), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3228_pm_करोमुख्यs[] = अणु
	[RK3228_PD_CORE]	= DOMAIN_RK3036(BIT(0),  BIT(0),  BIT(16), true),
	[RK3228_PD_MSCH]	= DOMAIN_RK3036(BIT(1),  BIT(1),  BIT(17), true),
	[RK3228_PD_BUS]		= DOMAIN_RK3036(BIT(2),  BIT(2),  BIT(18), true),
	[RK3228_PD_SYS]		= DOMAIN_RK3036(BIT(3),  BIT(3),  BIT(19), true),
	[RK3228_PD_VIO]		= DOMAIN_RK3036(BIT(4),  BIT(4),  BIT(20), false),
	[RK3228_PD_VOP]		= DOMAIN_RK3036(BIT(5),  BIT(5),  BIT(21), false),
	[RK3228_PD_VPU]		= DOMAIN_RK3036(BIT(6),  BIT(6),  BIT(22), false),
	[RK3228_PD_RKVDEC]	= DOMAIN_RK3036(BIT(7),  BIT(7),  BIT(23), false),
	[RK3228_PD_GPU]		= DOMAIN_RK3036(BIT(8),  BIT(8),  BIT(24), false),
	[RK3228_PD_PERI]	= DOMAIN_RK3036(BIT(9),  BIT(9),  BIT(25), true),
	[RK3228_PD_GMAC]	= DOMAIN_RK3036(BIT(10), BIT(10), BIT(26), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3288_pm_करोमुख्यs[] = अणु
	[RK3288_PD_VIO]		= DOMAIN_RK3288(BIT(7),  BIT(7),  BIT(4), false),
	[RK3288_PD_HEVC]	= DOMAIN_RK3288(BIT(14), BIT(10), BIT(9), false),
	[RK3288_PD_VIDEO]	= DOMAIN_RK3288(BIT(8),  BIT(8),  BIT(3), false),
	[RK3288_PD_GPU]		= DOMAIN_RK3288(BIT(9),  BIT(9),  BIT(2), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3328_pm_करोमुख्यs[] = अणु
	[RK3328_PD_CORE]	= DOMAIN_RK3328(0, BIT(0), BIT(0), false),
	[RK3328_PD_GPU]		= DOMAIN_RK3328(0, BIT(1), BIT(1), false),
	[RK3328_PD_BUS]		= DOMAIN_RK3328(0, BIT(2), BIT(2), true),
	[RK3328_PD_MSCH]	= DOMAIN_RK3328(0, BIT(3), BIT(3), true),
	[RK3328_PD_PERI]	= DOMAIN_RK3328(0, BIT(4), BIT(4), true),
	[RK3328_PD_VIDEO]	= DOMAIN_RK3328(0, BIT(5), BIT(5), false),
	[RK3328_PD_HEVC]	= DOMAIN_RK3328(0, BIT(6), BIT(6), false),
	[RK3328_PD_VIO]		= DOMAIN_RK3328(0, BIT(8), BIT(8), false),
	[RK3328_PD_VPU]		= DOMAIN_RK3328(0, BIT(9), BIT(9), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3366_pm_करोमुख्यs[] = अणु
	[RK3366_PD_PERI]	= DOMAIN_RK3368(BIT(10), BIT(10), BIT(6), true),
	[RK3366_PD_VIO]		= DOMAIN_RK3368(BIT(14), BIT(14), BIT(8), false),
	[RK3366_PD_VIDEO]	= DOMAIN_RK3368(BIT(13), BIT(13), BIT(7), false),
	[RK3366_PD_RKVDEC]	= DOMAIN_RK3368(BIT(11), BIT(11), BIT(7), false),
	[RK3366_PD_WIFIBT]	= DOMAIN_RK3368(BIT(8),  BIT(8),  BIT(9), false),
	[RK3366_PD_VPU]		= DOMAIN_RK3368(BIT(12), BIT(12), BIT(7), false),
	[RK3366_PD_GPU]		= DOMAIN_RK3368(BIT(15), BIT(15), BIT(2), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3368_pm_करोमुख्यs[] = अणु
	[RK3368_PD_PERI]	= DOMAIN_RK3368(BIT(13), BIT(12), BIT(6), true),
	[RK3368_PD_VIO]		= DOMAIN_RK3368(BIT(15), BIT(14), BIT(8), false),
	[RK3368_PD_VIDEO]	= DOMAIN_RK3368(BIT(14), BIT(13), BIT(7), false),
	[RK3368_PD_GPU_0]	= DOMAIN_RK3368(BIT(16), BIT(15), BIT(2), false),
	[RK3368_PD_GPU_1]	= DOMAIN_RK3368(BIT(17), BIT(16), BIT(2), false),
पूर्ण;

अटल स्थिर काष्ठा rockchip_करोमुख्य_info rk3399_pm_करोमुख्यs[] = अणु
	[RK3399_PD_TCPD0]	= DOMAIN_RK3399(BIT(8),  BIT(8),  0,	   false),
	[RK3399_PD_TCPD1]	= DOMAIN_RK3399(BIT(9),  BIT(9),  0,	   false),
	[RK3399_PD_CCI]		= DOMAIN_RK3399(BIT(10), BIT(10), 0,	   true),
	[RK3399_PD_CCI0]	= DOMAIN_RK3399(0,	 0,	  BIT(15), true),
	[RK3399_PD_CCI1]	= DOMAIN_RK3399(0,	 0,	  BIT(16), true),
	[RK3399_PD_PERILP]	= DOMAIN_RK3399(BIT(11), BIT(11), BIT(1),  true),
	[RK3399_PD_PERIHP]	= DOMAIN_RK3399(BIT(12), BIT(12), BIT(2),  true),
	[RK3399_PD_CENTER]	= DOMAIN_RK3399(BIT(13), BIT(13), BIT(14), true),
	[RK3399_PD_VIO]		= DOMAIN_RK3399(BIT(14), BIT(14), BIT(17), false),
	[RK3399_PD_GPU]		= DOMAIN_RK3399(BIT(15), BIT(15), BIT(0),  false),
	[RK3399_PD_VCODEC]	= DOMAIN_RK3399(BIT(16), BIT(16), BIT(3),  false),
	[RK3399_PD_VDU]		= DOMAIN_RK3399(BIT(17), BIT(17), BIT(4),  false),
	[RK3399_PD_RGA]		= DOMAIN_RK3399(BIT(18), BIT(18), BIT(5),  false),
	[RK3399_PD_IEP]		= DOMAIN_RK3399(BIT(19), BIT(19), BIT(6),  false),
	[RK3399_PD_VO]		= DOMAIN_RK3399(BIT(20), BIT(20), 0,	   false),
	[RK3399_PD_VOPB]	= DOMAIN_RK3399(0,	 0,	  BIT(7),  false),
	[RK3399_PD_VOPL]	= DOMAIN_RK3399(0, 	 0,	  BIT(8),  false),
	[RK3399_PD_ISP0]	= DOMAIN_RK3399(BIT(22), BIT(22), BIT(9),  false),
	[RK3399_PD_ISP1]	= DOMAIN_RK3399(BIT(23), BIT(23), BIT(10), false),
	[RK3399_PD_HDCP]	= DOMAIN_RK3399(BIT(24), BIT(24), BIT(11), false),
	[RK3399_PD_GMAC]	= DOMAIN_RK3399(BIT(25), BIT(25), BIT(23), true),
	[RK3399_PD_EMMC]	= DOMAIN_RK3399(BIT(26), BIT(26), BIT(24), true),
	[RK3399_PD_USB3]	= DOMAIN_RK3399(BIT(27), BIT(27), BIT(12), true),
	[RK3399_PD_EDP]		= DOMAIN_RK3399(BIT(28), BIT(28), BIT(22), false),
	[RK3399_PD_GIC]		= DOMAIN_RK3399(BIT(29), BIT(29), BIT(27), true),
	[RK3399_PD_SD]		= DOMAIN_RK3399(BIT(30), BIT(30), BIT(28), true),
	[RK3399_PD_SDIOAUDIO]	= DOMAIN_RK3399(BIT(31), BIT(31), BIT(29), true),
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info px30_pmu = अणु
	.pwr_offset = 0x18,
	.status_offset = 0x20,
	.req_offset = 0x64,
	.idle_offset = 0x6c,
	.ack_offset = 0x6c,

	.num_करोमुख्यs = ARRAY_SIZE(px30_pm_करोमुख्यs),
	.करोमुख्य_info = px30_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3036_pmu = अणु
	.req_offset = 0x148,
	.idle_offset = 0x14c,
	.ack_offset = 0x14c,

	.num_करोमुख्यs = ARRAY_SIZE(rk3036_pm_करोमुख्यs),
	.करोमुख्य_info = rk3036_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3066_pmu = अणु
	.pwr_offset = 0x08,
	.status_offset = 0x0c,
	.req_offset = 0x38, /* PMU_MISC_CON1 */
	.idle_offset = 0x0c,
	.ack_offset = 0x0c,

	.num_करोमुख्यs = ARRAY_SIZE(rk3066_pm_करोमुख्यs),
	.करोमुख्य_info = rk3066_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3128_pmu = अणु
	.pwr_offset = 0x04,
	.status_offset = 0x08,
	.req_offset = 0x0c,
	.idle_offset = 0x10,
	.ack_offset = 0x10,

	.num_करोमुख्यs = ARRAY_SIZE(rk3128_pm_करोमुख्यs),
	.करोमुख्य_info = rk3128_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3188_pmu = अणु
	.pwr_offset = 0x08,
	.status_offset = 0x0c,
	.req_offset = 0x38, /* PMU_MISC_CON1 */
	.idle_offset = 0x0c,
	.ack_offset = 0x0c,

	.num_करोमुख्यs = ARRAY_SIZE(rk3188_pm_करोमुख्यs),
	.करोमुख्य_info = rk3188_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3228_pmu = अणु
	.req_offset = 0x40c,
	.idle_offset = 0x488,
	.ack_offset = 0x488,

	.num_करोमुख्यs = ARRAY_SIZE(rk3228_pm_करोमुख्यs),
	.करोमुख्य_info = rk3228_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3288_pmu = अणु
	.pwr_offset = 0x08,
	.status_offset = 0x0c,
	.req_offset = 0x10,
	.idle_offset = 0x14,
	.ack_offset = 0x14,

	.core_pwrcnt_offset = 0x34,
	.gpu_pwrcnt_offset = 0x3c,

	.core_घातer_transition_समय = 24, /* 1us */
	.gpu_घातer_transition_समय = 24, /* 1us */

	.num_करोमुख्यs = ARRAY_SIZE(rk3288_pm_करोमुख्यs),
	.करोमुख्य_info = rk3288_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3328_pmu = अणु
	.req_offset = 0x414,
	.idle_offset = 0x484,
	.ack_offset = 0x484,

	.num_करोमुख्यs = ARRAY_SIZE(rk3328_pm_करोमुख्यs),
	.करोमुख्य_info = rk3328_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3366_pmu = अणु
	.pwr_offset = 0x0c,
	.status_offset = 0x10,
	.req_offset = 0x3c,
	.idle_offset = 0x40,
	.ack_offset = 0x40,

	.core_pwrcnt_offset = 0x48,
	.gpu_pwrcnt_offset = 0x50,

	.core_घातer_transition_समय = 24,
	.gpu_घातer_transition_समय = 24,

	.num_करोमुख्यs = ARRAY_SIZE(rk3366_pm_करोमुख्यs),
	.करोमुख्य_info = rk3366_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3368_pmu = अणु
	.pwr_offset = 0x0c,
	.status_offset = 0x10,
	.req_offset = 0x3c,
	.idle_offset = 0x40,
	.ack_offset = 0x40,

	.core_pwrcnt_offset = 0x48,
	.gpu_pwrcnt_offset = 0x50,

	.core_घातer_transition_समय = 24,
	.gpu_घातer_transition_समय = 24,

	.num_करोमुख्यs = ARRAY_SIZE(rk3368_pm_करोमुख्यs),
	.करोमुख्य_info = rk3368_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pmu_info rk3399_pmu = अणु
	.pwr_offset = 0x14,
	.status_offset = 0x18,
	.req_offset = 0x60,
	.idle_offset = 0x64,
	.ack_offset = 0x68,

	/* ARM Trusted Firmware manages घातer transition बार */

	.num_करोमुख्यs = ARRAY_SIZE(rk3399_pm_करोमुख्यs),
	.करोमुख्य_info = rk3399_pm_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pm_करोमुख्य_dt_match[] = अणु
	अणु
		.compatible = "rockchip,px30-power-controller",
		.data = (व्योम *)&px30_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3036-power-controller",
		.data = (व्योम *)&rk3036_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3066-power-controller",
		.data = (व्योम *)&rk3066_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3128-power-controller",
		.data = (व्योम *)&rk3128_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3188-power-controller",
		.data = (व्योम *)&rk3188_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3228-power-controller",
		.data = (व्योम *)&rk3228_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3288-power-controller",
		.data = (व्योम *)&rk3288_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3328-power-controller",
		.data = (व्योम *)&rk3328_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3366-power-controller",
		.data = (व्योम *)&rk3366_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3368-power-controller",
		.data = (व्योम *)&rk3368_pmu,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-power-controller",
		.data = (व्योम *)&rk3399_pmu,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rockchip_pm_करोमुख्य_driver = अणु
	.probe = rockchip_pm_करोमुख्य_probe,
	.driver = अणु
		.name   = "rockchip-pm-domain",
		.of_match_table = rockchip_pm_करोमुख्य_dt_match,
		/*
		 * We can't क्रमcibly eject devices क्रमm घातer करोमुख्य,
		 * so we can't really हटाओ घातer करोमुख्यs once they
		 * were added.
		 */
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rockchip_pm_करोमुख्य_drv_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rockchip_pm_करोमुख्य_driver);
पूर्ण
postcore_initcall(rockchip_pm_करोमुख्य_drv_रेजिस्टर);
