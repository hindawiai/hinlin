<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ZynqMP Generic PM करोमुख्य support
 *
 *  Copyright (C) 2015-2019 Xilinx, Inc.
 *
 *  Davorin Mista <davorin.mista@aggios.com>
 *  Jolly Shah <jollys@xilinx.com>
 *  Rajan Vaja <rajan.vaja@xilinx.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>

#समावेश <linux/firmware/xlnx-zynqmp.h>

#घोषणा ZYNQMP_NUM_DOMAINS		(100)
/* Flag stating अगर PM nodes mapped to the PM करोमुख्य has been requested */
#घोषणा ZYNQMP_PM_DOMAIN_REQUESTED	BIT(0)

अटल पूर्णांक min_capability;

/**
 * काष्ठा zynqmp_pm_करोमुख्य - Wrapper around काष्ठा generic_pm_करोमुख्य
 * @gpd:		Generic घातer करोमुख्य
 * @node_id:		PM node ID corresponding to device inside PM करोमुख्य
 * @flags:		ZynqMP PM करोमुख्य flags
 */
काष्ठा zynqmp_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य gpd;
	u32 node_id;
	u8 flags;
पूर्ण;

/**
 * zynqmp_gpd_is_active_wakeup_path() - Check अगर device is in wakeup source
 *					path
 * @dev:	Device to check क्रम wakeup source path
 * @not_used:	Data member (not required)
 *
 * This function is checks device's child hierarchy and checks अगर any device is
 * set as wakeup source.
 *
 * Return: 1 अगर device is in wakeup source path अन्यथा 0
 */
अटल पूर्णांक zynqmp_gpd_is_active_wakeup_path(काष्ठा device *dev, व्योम *not_used)
अणु
	पूर्णांक may_wakeup;

	may_wakeup = device_may_wakeup(dev);
	अगर (may_wakeup)
		वापस may_wakeup;

	वापस device_क्रम_each_child(dev, शून्य,
			zynqmp_gpd_is_active_wakeup_path);
पूर्ण

/**
 * zynqmp_gpd_घातer_on() - Power on PM करोमुख्य
 * @करोमुख्य:	Generic PM करोमुख्य
 *
 * This function is called beक्रमe devices inside a PM करोमुख्य are resumed, to
 * घातer on PM करोमुख्य.
 *
 * Return: 0 on success, error code otherwise
 */
अटल पूर्णांक zynqmp_gpd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret;
	काष्ठा zynqmp_pm_करोमुख्य *pd;

	pd = container_of(करोमुख्य, काष्ठा zynqmp_pm_करोमुख्य, gpd);
	ret = zynqmp_pm_set_requirement(pd->node_id,
					ZYNQMP_PM_CAPABILITY_ACCESS,
					ZYNQMP_PM_MAX_QOS,
					ZYNQMP_PM_REQUEST_ACK_BLOCKING);
	अगर (ret) अणु
		pr_err("%s() %s set requirement for node %d failed: %d\n",
		       __func__, करोमुख्य->name, pd->node_id, ret);
		वापस ret;
	पूर्ण

	pr_debug("%s() Powered on %s domain\n", __func__, करोमुख्य->name);
	वापस 0;
पूर्ण

/**
 * zynqmp_gpd_घातer_off() - Power off PM करोमुख्य
 * @करोमुख्य:	Generic PM करोमुख्य
 *
 * This function is called after devices inside a PM करोमुख्य are suspended, to
 * घातer off PM करोमुख्य.
 *
 * Return: 0 on success, error code otherwise
 */
अटल पूर्णांक zynqmp_gpd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret;
	काष्ठा pm_करोमुख्य_data *pdd, *पंचांगp;
	काष्ठा zynqmp_pm_करोमुख्य *pd;
	u32 capabilities = min_capability;
	bool may_wakeup;

	pd = container_of(करोमुख्य, काष्ठा zynqmp_pm_करोमुख्य, gpd);

	/* If करोमुख्य is alपढ़ोy released there is nothing to be करोne */
	अगर (!(pd->flags & ZYNQMP_PM_DOMAIN_REQUESTED)) अणु
		pr_debug("%s() %s domain is already released\n",
			 __func__, करोमुख्य->name);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry_safe(pdd, पंचांगp, &करोमुख्य->dev_list, list_node) अणु
		/* If device is in wakeup path, set capability to WAKEUP */
		may_wakeup = zynqmp_gpd_is_active_wakeup_path(pdd->dev, शून्य);
		अगर (may_wakeup) अणु
			dev_dbg(pdd->dev, "device is in wakeup path in %s\n",
				करोमुख्य->name);
			capabilities = ZYNQMP_PM_CAPABILITY_WAKEUP;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = zynqmp_pm_set_requirement(pd->node_id, capabilities, 0,
					ZYNQMP_PM_REQUEST_ACK_NO);
	/**
	 * If घातering करोwn of any node inside this करोमुख्य fails,
	 * report and वापस the error
	 */
	अगर (ret) अणु
		pr_err("%s() %s set requirement for node %d failed: %d\n",
		       __func__, करोमुख्य->name, pd->node_id, ret);
		वापस ret;
	पूर्ण

	pr_debug("%s() Powered off %s domain\n", __func__, करोमुख्य->name);
	वापस 0;
पूर्ण

/**
 * zynqmp_gpd_attach_dev() - Attach device to the PM करोमुख्य
 * @करोमुख्य:	Generic PM करोमुख्य
 * @dev:	Device to attach
 *
 * Return: 0 on success, error code otherwise
 */
अटल पूर्णांक zynqmp_gpd_attach_dev(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा zynqmp_pm_करोमुख्य *pd;

	pd = container_of(करोमुख्य, काष्ठा zynqmp_pm_करोमुख्य, gpd);

	/* If this is not the first device to attach there is nothing to करो */
	अगर (करोमुख्य->device_count)
		वापस 0;

	ret = zynqmp_pm_request_node(pd->node_id, 0, 0,
				     ZYNQMP_PM_REQUEST_ACK_BLOCKING);
	/* If requesting a node fails prपूर्णांक and वापस the error */
	अगर (ret) अणु
		pr_err("%s() %s request failed for node %d: %d\n",
		       __func__, करोमुख्य->name, pd->node_id, ret);
		वापस ret;
	पूर्ण

	pd->flags |= ZYNQMP_PM_DOMAIN_REQUESTED;

	pr_debug("%s() %s attached to %s domain\n", __func__,
		 dev_name(dev), करोमुख्य->name);
	वापस 0;
पूर्ण

/**
 * zynqmp_gpd_detach_dev() - Detach device from the PM करोमुख्य
 * @करोमुख्य:	Generic PM करोमुख्य
 * @dev:	Device to detach
 */
अटल व्योम zynqmp_gpd_detach_dev(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा zynqmp_pm_करोमुख्य *pd;

	pd = container_of(करोमुख्य, काष्ठा zynqmp_pm_करोमुख्य, gpd);

	/* If this is not the last device to detach there is nothing to करो */
	अगर (करोमुख्य->device_count)
		वापस;

	ret = zynqmp_pm_release_node(pd->node_id);
	/* If releasing a node fails prपूर्णांक the error and वापस */
	अगर (ret) अणु
		pr_err("%s() %s release failed for node %d: %d\n",
		       __func__, करोमुख्य->name, pd->node_id, ret);
		वापस;
	पूर्ण

	pd->flags &= ~ZYNQMP_PM_DOMAIN_REQUESTED;

	pr_debug("%s() %s detached from %s domain\n", __func__,
		 dev_name(dev), करोमुख्य->name);
पूर्ण

अटल काष्ठा generic_pm_करोमुख्य *zynqmp_gpd_xlate
				(काष्ठा of_phandle_args *genpdspec, व्योम *data)
अणु
	काष्ठा genpd_onecell_data *genpd_data = data;
	अचिन्हित पूर्णांक i, idx = genpdspec->args[0];
	काष्ठा zynqmp_pm_करोमुख्य *pd;

	pd = container_of(genpd_data->करोमुख्यs[0], काष्ठा zynqmp_pm_करोमुख्य, gpd);

	अगर (genpdspec->args_count != 1)
		वापस ERR_PTR(-EINVAL);

	/* Check क्रम existing pm करोमुख्यs */
	क्रम (i = 0; i < ZYNQMP_NUM_DOMAINS; i++) अणु
		अगर (pd[i].node_id == idx)
			जाओ करोne;
	पूर्ण

	/**
	 * Add index in empty node_id of घातer करोमुख्य list as no existing
	 * घातer करोमुख्य found क्रम current index.
	 */
	क्रम (i = 0; i < ZYNQMP_NUM_DOMAINS; i++) अणु
		अगर (pd[i].node_id == 0) अणु
			pd[i].node_id = idx;
			अवरोध;
		पूर्ण
	पूर्ण

करोne:
	अगर (!genpd_data->करोमुख्यs[i] || i == ZYNQMP_NUM_DOMAINS)
		वापस ERR_PTR(-ENOENT);

	वापस genpd_data->करोमुख्यs[i];
पूर्ण

अटल पूर्णांक zynqmp_gpd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा genpd_onecell_data *zynqmp_pd_data;
	काष्ठा generic_pm_करोमुख्य **करोमुख्यs;
	काष्ठा zynqmp_pm_करोमुख्य *pd;
	काष्ठा device *dev = &pdev->dev;

	pd = devm_kसुस्मृति(dev, ZYNQMP_NUM_DOMAINS, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	zynqmp_pd_data = devm_kzalloc(dev, माप(*zynqmp_pd_data), GFP_KERNEL);
	अगर (!zynqmp_pd_data)
		वापस -ENOMEM;

	zynqmp_pd_data->xlate = zynqmp_gpd_xlate;

	करोमुख्यs = devm_kसुस्मृति(dev, ZYNQMP_NUM_DOMAINS, माप(*करोमुख्यs),
			       GFP_KERNEL);
	अगर (!करोमुख्यs)
		वापस -ENOMEM;

	अगर (!of_device_is_compatible(dev->parent->of_node,
				     "xlnx,zynqmp-firmware"))
		min_capability = ZYNQMP_PM_CAPABILITY_UNUSABLE;

	क्रम (i = 0; i < ZYNQMP_NUM_DOMAINS; i++, pd++) अणु
		pd->node_id = 0;
		pd->gpd.name = kaप्र_लिखो(GFP_KERNEL, "domain%d", i);
		pd->gpd.घातer_off = zynqmp_gpd_घातer_off;
		pd->gpd.घातer_on = zynqmp_gpd_घातer_on;
		pd->gpd.attach_dev = zynqmp_gpd_attach_dev;
		pd->gpd.detach_dev = zynqmp_gpd_detach_dev;

		करोमुख्यs[i] = &pd->gpd;

		/* Mark all PM करोमुख्यs as initially घातered off */
		pm_genpd_init(&pd->gpd, शून्य, true);
	पूर्ण

	zynqmp_pd_data->करोमुख्यs = करोमुख्यs;
	zynqmp_pd_data->num_करोमुख्यs = ZYNQMP_NUM_DOMAINS;
	of_genpd_add_provider_onecell(dev->parent->of_node, zynqmp_pd_data);

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_gpd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_genpd_del_provider(pdev->dev.parent->of_node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver zynqmp_घातer_करोमुख्य_driver = अणु
	.driver	= अणु
		.name = "zynqmp_power_controller",
	पूर्ण,
	.probe = zynqmp_gpd_probe,
	.हटाओ = zynqmp_gpd_हटाओ,
पूर्ण;
module_platक्रमm_driver(zynqmp_घातer_करोमुख्य_driver);

MODULE_ALIAS("platform:zynqmp_power_controller");
