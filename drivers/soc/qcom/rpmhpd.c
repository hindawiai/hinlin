<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, The Linux Foundation. All rights reserved.*/

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <soc/qcom/cmd-db.h>
#समावेश <soc/qcom/rpmh.h>
#समावेश <dt-bindings/घातer/qcom-rpmpd.h>

#घोषणा करोमुख्य_to_rpmhpd(करोमुख्य) container_of(करोमुख्य, काष्ठा rpmhpd, pd)

#घोषणा RPMH_ARC_MAX_LEVELS	16

/**
 * काष्ठा rpmhpd - top level RPMh घातer करोमुख्य resource data काष्ठाure
 * @dev:		rpmh घातer करोमुख्य controller device
 * @pd:			generic_pm_करोमुख्य corrresponding to the घातer करोमुख्य
 * @parent:		generic_pm_करोमुख्य corrresponding to the parent's घातer करोमुख्य
 * @peer:		A peer घातer करोमुख्य in हाल Active only Voting is
 *			supported
 * @active_only:	True अगर it represents an Active only peer
 * @corner:		current corner
 * @active_corner:	current active corner
 * @level:		An array of level (vlvl) to corner (hlvl) mappings
 *			derived from cmd-db
 * @level_count:	Number of levels supported by the घातer करोमुख्य. max
 *			being 16 (0 - 15)
 * @enabled:		true अगर the घातer करोमुख्य is enabled
 * @res_name:		Resource name used क्रम cmd-db lookup
 * @addr:		Resource address as looped up using resource name from
 *			cmd-db
 */
काष्ठा rpmhpd अणु
	काष्ठा device	*dev;
	काष्ठा generic_pm_करोमुख्य pd;
	काष्ठा generic_pm_करोमुख्य *parent;
	काष्ठा rpmhpd	*peer;
	स्थिर bool	active_only;
	अचिन्हित पूर्णांक	corner;
	अचिन्हित पूर्णांक	active_corner;
	u32		level[RPMH_ARC_MAX_LEVELS];
	माप_प्रकार		level_count;
	bool		enabled;
	स्थिर अक्षर	*res_name;
	u32		addr;
पूर्ण;

काष्ठा rpmhpd_desc अणु
	काष्ठा rpmhpd **rpmhpds;
	माप_प्रकार num_pds;
पूर्ण;

अटल DEFINE_MUTEX(rpmhpd_lock);

/* SDM845 RPMH घातerकरोमुख्यs */

अटल काष्ठा rpmhpd sdm845_ebi = अणु
	.pd = अणु .name = "ebi", पूर्ण,
	.res_name = "ebi.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_lmx = अणु
	.pd = अणु .name = "lmx", पूर्ण,
	.res_name = "lmx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_lcx = अणु
	.pd = अणु .name = "lcx", पूर्ण,
	.res_name = "lcx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_gfx = अणु
	.pd = अणु .name = "gfx", पूर्ण,
	.res_name = "gfx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_mss = अणु
	.pd = अणु .name = "mss", पूर्ण,
	.res_name = "mss.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_mx_ao;
अटल काष्ठा rpmhpd sdm845_mx = अणु
	.pd = अणु .name = "mx", पूर्ण,
	.peer = &sdm845_mx_ao,
	.res_name = "mx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_mx_ao = अणु
	.pd = अणु .name = "mx_ao", पूर्ण,
	.active_only = true,
	.peer = &sdm845_mx,
	.res_name = "mx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_cx_ao;
अटल काष्ठा rpmhpd sdm845_cx = अणु
	.pd = अणु .name = "cx", पूर्ण,
	.peer = &sdm845_cx_ao,
	.parent = &sdm845_mx.pd,
	.res_name = "cx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sdm845_cx_ao = अणु
	.pd = अणु .name = "cx_ao", पूर्ण,
	.active_only = true,
	.peer = &sdm845_cx,
	.parent = &sdm845_mx_ao.pd,
	.res_name = "cx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd *sdm845_rpmhpds[] = अणु
	[SDM845_EBI] = &sdm845_ebi,
	[SDM845_MX] = &sdm845_mx,
	[SDM845_MX_AO] = &sdm845_mx_ao,
	[SDM845_CX] = &sdm845_cx,
	[SDM845_CX_AO] = &sdm845_cx_ao,
	[SDM845_LMX] = &sdm845_lmx,
	[SDM845_LCX] = &sdm845_lcx,
	[SDM845_GFX] = &sdm845_gfx,
	[SDM845_MSS] = &sdm845_mss,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sdm845_desc = अणु
	.rpmhpds = sdm845_rpmhpds,
	.num_pds = ARRAY_SIZE(sdm845_rpmhpds),
पूर्ण;

/* SDX55 RPMH घातerकरोमुख्यs */
अटल काष्ठा rpmhpd *sdx55_rpmhpds[] = अणु
	[SDX55_MSS] = &sdm845_mss,
	[SDX55_MX] = &sdm845_mx,
	[SDX55_CX] = &sdm845_cx,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sdx55_desc = अणु
	.rpmhpds = sdx55_rpmhpds,
	.num_pds = ARRAY_SIZE(sdx55_rpmhpds),
पूर्ण;

/* SM8150 RPMH घातerकरोमुख्यs */

अटल काष्ठा rpmhpd sm8150_mmcx_ao;
अटल काष्ठा rpmhpd sm8150_mmcx = अणु
	.pd = अणु .name = "mmcx", पूर्ण,
	.peer = &sm8150_mmcx_ao,
	.res_name = "mmcx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sm8150_mmcx_ao = अणु
	.pd = अणु .name = "mmcx_ao", पूर्ण,
	.active_only = true,
	.peer = &sm8150_mmcx,
	.res_name = "mmcx.lvl",
पूर्ण;

अटल काष्ठा rpmhpd *sm8150_rpmhpds[] = अणु
	[SM8150_MSS] = &sdm845_mss,
	[SM8150_EBI] = &sdm845_ebi,
	[SM8150_LMX] = &sdm845_lmx,
	[SM8150_LCX] = &sdm845_lcx,
	[SM8150_GFX] = &sdm845_gfx,
	[SM8150_MX] = &sdm845_mx,
	[SM8150_MX_AO] = &sdm845_mx_ao,
	[SM8150_CX] = &sdm845_cx,
	[SM8150_CX_AO] = &sdm845_cx_ao,
	[SM8150_MMCX] = &sm8150_mmcx,
	[SM8150_MMCX_AO] = &sm8150_mmcx_ao,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sm8150_desc = अणु
	.rpmhpds = sm8150_rpmhpds,
	.num_pds = ARRAY_SIZE(sm8150_rpmhpds),
पूर्ण;

अटल काष्ठा rpmhpd *sm8250_rpmhpds[] = अणु
	[SM8250_CX] = &sdm845_cx,
	[SM8250_CX_AO] = &sdm845_cx_ao,
	[SM8250_EBI] = &sdm845_ebi,
	[SM8250_GFX] = &sdm845_gfx,
	[SM8250_LCX] = &sdm845_lcx,
	[SM8250_LMX] = &sdm845_lmx,
	[SM8250_MMCX] = &sm8150_mmcx,
	[SM8250_MMCX_AO] = &sm8150_mmcx_ao,
	[SM8250_MX] = &sdm845_mx,
	[SM8250_MX_AO] = &sdm845_mx_ao,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sm8250_desc = अणु
	.rpmhpds = sm8250_rpmhpds,
	.num_pds = ARRAY_SIZE(sm8250_rpmhpds),
पूर्ण;

/* SM8350 Power करोमुख्यs */
अटल काष्ठा rpmhpd sm8350_mxc_ao;
अटल काष्ठा rpmhpd sm8350_mxc = अणु
	.pd = अणु .name = "mxc", पूर्ण,
	.peer = &sm8150_mmcx_ao,
	.res_name = "mxc.lvl",
पूर्ण;

अटल काष्ठा rpmhpd sm8350_mxc_ao = अणु
	.pd = अणु .name = "mxc_ao", पूर्ण,
	.active_only = true,
	.peer = &sm8350_mxc,
	.res_name = "mxc.lvl",
पूर्ण;

अटल काष्ठा rpmhpd *sm8350_rpmhpds[] = अणु
	[SM8350_CX] = &sdm845_cx,
	[SM8350_CX_AO] = &sdm845_cx_ao,
	[SM8350_EBI] = &sdm845_ebi,
	[SM8350_GFX] = &sdm845_gfx,
	[SM8350_LCX] = &sdm845_lcx,
	[SM8350_LMX] = &sdm845_lmx,
	[SM8350_MMCX] = &sm8150_mmcx,
	[SM8350_MMCX_AO] = &sm8150_mmcx_ao,
	[SM8350_MX] = &sdm845_mx,
	[SM8350_MX_AO] = &sdm845_mx_ao,
	[SM8350_MXC] = &sm8350_mxc,
	[SM8350_MXC_AO] = &sm8350_mxc_ao,
	[SM8350_MSS] = &sdm845_mss,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sm8350_desc = अणु
	.rpmhpds = sm8350_rpmhpds,
	.num_pds = ARRAY_SIZE(sm8350_rpmhpds),
पूर्ण;

/* SC7180 RPMH घातerकरोमुख्यs */
अटल काष्ठा rpmhpd *sc7180_rpmhpds[] = अणु
	[SC7180_CX] = &sdm845_cx,
	[SC7180_CX_AO] = &sdm845_cx_ao,
	[SC7180_GFX] = &sdm845_gfx,
	[SC7180_MX] = &sdm845_mx,
	[SC7180_MX_AO] = &sdm845_mx_ao,
	[SC7180_LMX] = &sdm845_lmx,
	[SC7180_LCX] = &sdm845_lcx,
	[SC7180_MSS] = &sdm845_mss,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sc7180_desc = अणु
	.rpmhpds = sc7180_rpmhpds,
	.num_pds = ARRAY_SIZE(sc7180_rpmhpds),
पूर्ण;

/* SC7280 RPMH घातerकरोमुख्यs */
अटल काष्ठा rpmhpd *sc7280_rpmhpds[] = अणु
	[SC7280_CX] = &sdm845_cx,
	[SC7280_CX_AO] = &sdm845_cx_ao,
	[SC7280_EBI] = &sdm845_ebi,
	[SC7280_GFX] = &sdm845_gfx,
	[SC7280_MX] = &sdm845_mx,
	[SC7280_MX_AO] = &sdm845_mx_ao,
	[SC7280_LMX] = &sdm845_lmx,
	[SC7280_LCX] = &sdm845_lcx,
	[SC7280_MSS] = &sdm845_mss,
पूर्ण;

अटल स्थिर काष्ठा rpmhpd_desc sc7280_desc = अणु
	.rpmhpds = sc7280_rpmhpds,
	.num_pds = ARRAY_SIZE(sc7280_rpmhpds),
पूर्ण;

अटल स्थिर काष्ठा of_device_id rpmhpd_match_table[] = अणु
	अणु .compatible = "qcom,sc7180-rpmhpd", .data = &sc7180_desc पूर्ण,
	अणु .compatible = "qcom,sc7280-rpmhpd", .data = &sc7280_desc पूर्ण,
	अणु .compatible = "qcom,sdm845-rpmhpd", .data = &sdm845_desc पूर्ण,
	अणु .compatible = "qcom,sdx55-rpmhpd", .data = &sdx55_descपूर्ण,
	अणु .compatible = "qcom,sm8150-rpmhpd", .data = &sm8150_desc पूर्ण,
	अणु .compatible = "qcom,sm8250-rpmhpd", .data = &sm8250_desc पूर्ण,
	अणु .compatible = "qcom,sm8350-rpmhpd", .data = &sm8350_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpmhpd_match_table);

अटल पूर्णांक rpmhpd_send_corner(काष्ठा rpmhpd *pd, पूर्णांक state,
			      अचिन्हित पूर्णांक corner, bool sync)
अणु
	काष्ठा tcs_cmd cmd = अणु
		.addr = pd->addr,
		.data = corner,
	पूर्ण;

	/*
	 * Wait क्रम an ack only when we are increasing the
	 * perf state of the घातer करोमुख्य
	 */
	अगर (sync)
		वापस rpmh_ग_लिखो(pd->dev, state, &cmd, 1);
	अन्यथा
		वापस rpmh_ग_लिखो_async(pd->dev, state, &cmd, 1);
पूर्ण

अटल व्योम to_active_sleep(काष्ठा rpmhpd *pd, अचिन्हित पूर्णांक corner,
			    अचिन्हित पूर्णांक *active, अचिन्हित पूर्णांक *sleep)
अणु
	*active = corner;

	अगर (pd->active_only)
		*sleep = 0;
	अन्यथा
		*sleep = *active;
पूर्ण

/*
 * This function is used to aggregate the votes across the active only
 * resources and its peers. The aggregated votes are sent to RPMh as
 * ACTIVE_ONLY votes (which take effect immediately), as WAKE_ONLY votes
 * (applied by RPMh on प्रणाली wakeup) and as SLEEP votes (applied by RPMh
 * on प्रणाली sleep).
 * We send ACTIVE_ONLY votes क्रम resources without any peers. For others,
 * which have an active only peer, all 3 votes are sent.
 */
अटल पूर्णांक rpmhpd_aggregate_corner(काष्ठा rpmhpd *pd, अचिन्हित पूर्णांक corner)
अणु
	पूर्णांक ret;
	काष्ठा rpmhpd *peer = pd->peer;
	अचिन्हित पूर्णांक active_corner, sleep_corner;
	अचिन्हित पूर्णांक this_active_corner = 0, this_sleep_corner = 0;
	अचिन्हित पूर्णांक peer_active_corner = 0, peer_sleep_corner = 0;

	to_active_sleep(pd, corner, &this_active_corner, &this_sleep_corner);

	अगर (peer && peer->enabled)
		to_active_sleep(peer, peer->corner, &peer_active_corner,
				&peer_sleep_corner);

	active_corner = max(this_active_corner, peer_active_corner);

	ret = rpmhpd_send_corner(pd, RPMH_ACTIVE_ONLY_STATE, active_corner,
				 active_corner > pd->active_corner);
	अगर (ret)
		वापस ret;

	pd->active_corner = active_corner;

	अगर (peer) अणु
		peer->active_corner = active_corner;

		ret = rpmhpd_send_corner(pd, RPMH_WAKE_ONLY_STATE,
					 active_corner, false);
		अगर (ret)
			वापस ret;

		sleep_corner = max(this_sleep_corner, peer_sleep_corner);

		वापस rpmhpd_send_corner(pd, RPMH_SLEEP_STATE, sleep_corner,
					  false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rpmhpd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rpmhpd *pd = करोमुख्य_to_rpmhpd(करोमुख्य);
	पूर्णांक ret = 0;

	mutex_lock(&rpmhpd_lock);

	अगर (pd->corner)
		ret = rpmhpd_aggregate_corner(pd, pd->corner);

	अगर (!ret)
		pd->enabled = true;

	mutex_unlock(&rpmhpd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpmhpd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rpmhpd *pd = करोमुख्य_to_rpmhpd(करोमुख्य);
	पूर्णांक ret = 0;

	mutex_lock(&rpmhpd_lock);

	ret = rpmhpd_aggregate_corner(pd, pd->level[0]);

	अगर (!ret)
		pd->enabled = false;

	mutex_unlock(&rpmhpd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpmhpd_set_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक level)
अणु
	काष्ठा rpmhpd *pd = करोमुख्य_to_rpmhpd(करोमुख्य);
	पूर्णांक ret = 0, i;

	mutex_lock(&rpmhpd_lock);

	क्रम (i = 0; i < pd->level_count; i++)
		अगर (level <= pd->level[i])
			अवरोध;

	/*
	 * If the level requested is more than that supported by the
	 * max corner, just set it to max anyway.
	 */
	अगर (i == pd->level_count)
		i--;

	अगर (pd->enabled) अणु
		ret = rpmhpd_aggregate_corner(pd, i);
		अगर (ret)
			जाओ out;
	पूर्ण

	pd->corner = i;
out:
	mutex_unlock(&rpmhpd_lock);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक rpmhpd_get_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *genpd,
						 काष्ठा dev_pm_opp *opp)
अणु
	वापस dev_pm_opp_get_level(opp);
पूर्ण

अटल पूर्णांक rpmhpd_update_level_mapping(काष्ठा rpmhpd *rpmhpd)
अणु
	पूर्णांक i;
	स्थिर u16 *buf;

	buf = cmd_db_पढ़ो_aux_data(rpmhpd->res_name, &rpmhpd->level_count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	/* 2 bytes used क्रम each command DB aux data entry */
	rpmhpd->level_count >>= 1;

	अगर (rpmhpd->level_count > RPMH_ARC_MAX_LEVELS)
		वापस -EINVAL;

	क्रम (i = 0; i < rpmhpd->level_count; i++) अणु
		rpmhpd->level[i] = buf[i];

		/*
		 * The AUX data may be zero padded.  These 0 valued entries at
		 * the end of the map must be ignored.
		 */
		अगर (i > 0 && rpmhpd->level[i] == 0) अणु
			rpmhpd->level_count = i;
			अवरोध;
		पूर्ण
		pr_debug("%s: ARC hlvl=%2d --> vlvl=%4u\n", rpmhpd->res_name, i,
			 rpmhpd->level[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rpmhpd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;
	माप_प्रकार num_pds;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा genpd_onecell_data *data;
	काष्ठा rpmhpd **rpmhpds;
	स्थिर काष्ठा rpmhpd_desc *desc;

	desc = of_device_get_match_data(dev);
	अगर (!desc)
		वापस -EINVAL;

	rpmhpds = desc->rpmhpds;
	num_pds = desc->num_pds;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->करोमुख्यs = devm_kसुस्मृति(dev, num_pds, माप(*data->करोमुख्यs),
				     GFP_KERNEL);
	अगर (!data->करोमुख्यs)
		वापस -ENOMEM;

	data->num_करोमुख्यs = num_pds;

	क्रम (i = 0; i < num_pds; i++) अणु
		अगर (!rpmhpds[i]) अणु
			dev_warn(dev, "rpmhpds[%d] is empty\n", i);
			जारी;
		पूर्ण

		rpmhpds[i]->dev = dev;
		rpmhpds[i]->addr = cmd_db_पढ़ो_addr(rpmhpds[i]->res_name);
		अगर (!rpmhpds[i]->addr) अणु
			dev_err(dev, "Could not find RPMh address for resource %s\n",
				rpmhpds[i]->res_name);
			वापस -ENODEV;
		पूर्ण

		ret = cmd_db_पढ़ो_slave_id(rpmhpds[i]->res_name);
		अगर (ret != CMD_DB_HW_ARC) अणु
			dev_err(dev, "RPMh slave ID mismatch\n");
			वापस -EINVAL;
		पूर्ण

		ret = rpmhpd_update_level_mapping(rpmhpds[i]);
		अगर (ret)
			वापस ret;

		rpmhpds[i]->pd.घातer_off = rpmhpd_घातer_off;
		rpmhpds[i]->pd.घातer_on = rpmhpd_घातer_on;
		rpmhpds[i]->pd.set_perक्रमmance_state = rpmhpd_set_perक्रमmance_state;
		rpmhpds[i]->pd.opp_to_perक्रमmance_state = rpmhpd_get_perक्रमmance_state;
		pm_genpd_init(&rpmhpds[i]->pd, शून्य, true);

		data->करोमुख्यs[i] = &rpmhpds[i]->pd;
	पूर्ण

	/* Add subकरोमुख्यs */
	क्रम (i = 0; i < num_pds; i++) अणु
		अगर (!rpmhpds[i])
			जारी;
		अगर (rpmhpds[i]->parent)
			pm_genpd_add_subकरोमुख्य(rpmhpds[i]->parent,
					       &rpmhpds[i]->pd);
	पूर्ण

	वापस of_genpd_add_provider_onecell(pdev->dev.of_node, data);
पूर्ण

अटल काष्ठा platक्रमm_driver rpmhpd_driver = अणु
	.driver = अणु
		.name = "qcom-rpmhpd",
		.of_match_table = rpmhpd_match_table,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = rpmhpd_probe,
पूर्ण;

अटल पूर्णांक __init rpmhpd_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rpmhpd_driver);
पूर्ण
core_initcall(rpmhpd_init);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. RPMh Power Domain Driver");
MODULE_LICENSE("GPL v2");
