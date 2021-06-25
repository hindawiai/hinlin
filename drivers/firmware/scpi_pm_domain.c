<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCPI Generic घातer करोमुख्य support.
 *
 * Copyright (C) 2016 ARM Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/scpi_protocol.h>

काष्ठा scpi_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा scpi_ops *ops;
	u32 करोमुख्य;
	अक्षर name[30];
पूर्ण;

/*
 * These device घातer state values are not well-defined in the specअगरication.
 * In हाल, dअगरferent implementations use dअगरferent values, we can make these
 * specअगरic to compatibles rather than getting these values from device tree.
 */
क्रमागत scpi_घातer_करोमुख्य_state अणु
	SCPI_PD_STATE_ON = 0,
	SCPI_PD_STATE_OFF = 3,
पूर्ण;

#घोषणा to_scpi_pd(gpd) container_of(gpd, काष्ठा scpi_pm_करोमुख्य, genpd)

अटल पूर्णांक scpi_pd_घातer(काष्ठा scpi_pm_करोमुख्य *pd, bool घातer_on)
अणु
	पूर्णांक ret;
	क्रमागत scpi_घातer_करोमुख्य_state state;

	अगर (घातer_on)
		state = SCPI_PD_STATE_ON;
	अन्यथा
		state = SCPI_PD_STATE_OFF;

	ret = pd->ops->device_set_घातer_state(pd->करोमुख्य, state);
	अगर (ret)
		वापस ret;

	वापस !(state == pd->ops->device_get_घातer_state(pd->करोमुख्य));
पूर्ण

अटल पूर्णांक scpi_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा scpi_pm_करोमुख्य *pd = to_scpi_pd(करोमुख्य);

	वापस scpi_pd_घातer(pd, true);
पूर्ण

अटल पूर्णांक scpi_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा scpi_pm_करोमुख्य *pd = to_scpi_pd(करोमुख्य);

	वापस scpi_pd_घातer(pd, false);
पूर्ण

अटल पूर्णांक scpi_pm_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा scpi_pm_करोमुख्य *scpi_pd;
	काष्ठा genpd_onecell_data *scpi_pd_data;
	काष्ठा generic_pm_करोमुख्य **करोमुख्यs;
	काष्ठा scpi_ops *scpi_ops;
	पूर्णांक ret, num_करोमुख्यs, i;

	scpi_ops = get_scpi_ops();
	अगर (!scpi_ops)
		वापस -EPROBE_DEFER;

	अगर (!np) अणु
		dev_err(dev, "device tree node not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!scpi_ops->device_set_घातer_state ||
	    !scpi_ops->device_get_घातer_state) अणु
		dev_err(dev, "power domains not supported in the firmware\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "num-domains", &num_करोमुख्यs);
	अगर (ret) अणु
		dev_err(dev, "number of domains not found\n");
		वापस -EINVAL;
	पूर्ण

	scpi_pd = devm_kसुस्मृति(dev, num_करोमुख्यs, माप(*scpi_pd), GFP_KERNEL);
	अगर (!scpi_pd)
		वापस -ENOMEM;

	scpi_pd_data = devm_kzalloc(dev, माप(*scpi_pd_data), GFP_KERNEL);
	अगर (!scpi_pd_data)
		वापस -ENOMEM;

	करोमुख्यs = devm_kसुस्मृति(dev, num_करोमुख्यs, माप(*करोमुख्यs), GFP_KERNEL);
	अगर (!करोमुख्यs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_करोमुख्यs; i++, scpi_pd++) अणु
		करोमुख्यs[i] = &scpi_pd->genpd;

		scpi_pd->करोमुख्य = i;
		scpi_pd->ops = scpi_ops;
		प्र_लिखो(scpi_pd->name, "%pOFn.%d", np, i);
		scpi_pd->genpd.name = scpi_pd->name;
		scpi_pd->genpd.घातer_off = scpi_pd_घातer_off;
		scpi_pd->genpd.घातer_on = scpi_pd_घातer_on;

		/*
		 * Treat all घातer करोमुख्यs as off at boot.
		 *
		 * The SCP firmware itself may have चयनed on some करोमुख्यs,
		 * but क्रम reference counting purpose, keep it this way.
		 */
		pm_genpd_init(&scpi_pd->genpd, शून्य, true);
	पूर्ण

	scpi_pd_data->करोमुख्यs = करोमुख्यs;
	scpi_pd_data->num_करोमुख्यs = num_करोमुख्यs;

	of_genpd_add_provider_onecell(np, scpi_pd_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id scpi_घातer_करोमुख्य_ids[] = अणु
	अणु .compatible = "arm,scpi-power-domains", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, scpi_घातer_करोमुख्य_ids);

अटल काष्ठा platक्रमm_driver scpi_घातer_करोमुख्य_driver = अणु
	.driver	= अणु
		.name = "scpi_power_domain",
		.of_match_table = scpi_घातer_करोमुख्य_ids,
	पूर्ण,
	.probe = scpi_pm_करोमुख्य_probe,
पूर्ण;
module_platक्रमm_driver(scpi_घातer_करोमुख्य_driver);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCPI power domain driver");
MODULE_LICENSE("GPL v2");
