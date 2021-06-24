<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCMI Generic घातer करोमुख्य support.
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/scmi_protocol.h>

अटल स्थिर काष्ठा scmi_घातer_proto_ops *घातer_ops;

काष्ठा scmi_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	स्थिर काष्ठा scmi_protocol_handle *ph;
	स्थिर अक्षर *name;
	u32 करोमुख्य;
पूर्ण;

#घोषणा to_scmi_pd(gpd) container_of(gpd, काष्ठा scmi_pm_करोमुख्य, genpd)

अटल पूर्णांक scmi_pd_घातer(काष्ठा generic_pm_करोमुख्य *करोमुख्य, bool घातer_on)
अणु
	पूर्णांक ret;
	u32 state, ret_state;
	काष्ठा scmi_pm_करोमुख्य *pd = to_scmi_pd(करोमुख्य);

	अगर (घातer_on)
		state = SCMI_POWER_STATE_GENERIC_ON;
	अन्यथा
		state = SCMI_POWER_STATE_GENERIC_OFF;

	ret = घातer_ops->state_set(pd->ph, pd->करोमुख्य, state);
	अगर (!ret)
		ret = घातer_ops->state_get(pd->ph, pd->करोमुख्य, &ret_state);
	अगर (!ret && state != ret_state)
		वापस -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस scmi_pd_घातer(करोमुख्य, true);
पूर्ण

अटल पूर्णांक scmi_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस scmi_pd_घातer(करोमुख्य, false);
पूर्ण

अटल पूर्णांक scmi_pm_करोमुख्य_probe(काष्ठा scmi_device *sdev)
अणु
	पूर्णांक num_करोमुख्यs, i;
	काष्ठा device *dev = &sdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा scmi_pm_करोमुख्य *scmi_pd;
	काष्ठा genpd_onecell_data *scmi_pd_data;
	काष्ठा generic_pm_करोमुख्य **करोमुख्यs;
	स्थिर काष्ठा scmi_handle *handle = sdev->handle;
	काष्ठा scmi_protocol_handle *ph;

	अगर (!handle)
		वापस -ENODEV;

	घातer_ops = handle->devm_protocol_get(sdev, SCMI_PROTOCOL_POWER, &ph);
	अगर (IS_ERR(घातer_ops))
		वापस PTR_ERR(घातer_ops);

	num_करोमुख्यs = घातer_ops->num_करोमुख्यs_get(ph);
	अगर (num_करोमुख्यs < 0) अणु
		dev_err(dev, "number of domains not found\n");
		वापस num_करोमुख्यs;
	पूर्ण

	scmi_pd = devm_kसुस्मृति(dev, num_करोमुख्यs, माप(*scmi_pd), GFP_KERNEL);
	अगर (!scmi_pd)
		वापस -ENOMEM;

	scmi_pd_data = devm_kzalloc(dev, माप(*scmi_pd_data), GFP_KERNEL);
	अगर (!scmi_pd_data)
		वापस -ENOMEM;

	करोमुख्यs = devm_kसुस्मृति(dev, num_करोमुख्यs, माप(*करोमुख्यs), GFP_KERNEL);
	अगर (!करोमुख्यs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_करोमुख्यs; i++, scmi_pd++) अणु
		u32 state;

		अगर (घातer_ops->state_get(ph, i, &state)) अणु
			dev_warn(dev, "failed to get state for domain %d\n", i);
			जारी;
		पूर्ण

		scmi_pd->करोमुख्य = i;
		scmi_pd->ph = ph;
		scmi_pd->name = घातer_ops->name_get(ph, i);
		scmi_pd->genpd.name = scmi_pd->name;
		scmi_pd->genpd.घातer_off = scmi_pd_घातer_off;
		scmi_pd->genpd.घातer_on = scmi_pd_घातer_on;

		pm_genpd_init(&scmi_pd->genpd, शून्य,
			      state == SCMI_POWER_STATE_GENERIC_OFF);

		करोमुख्यs[i] = &scmi_pd->genpd;
	पूर्ण

	scmi_pd_data->करोमुख्यs = करोमुख्यs;
	scmi_pd_data->num_करोमुख्यs = num_करोमुख्यs;

	of_genpd_add_provider_onecell(np, scmi_pd_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_id_table[] = अणु
	अणु SCMI_PROTOCOL_POWER, "genpd" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(scmi, scmi_id_table);

अटल काष्ठा scmi_driver scmi_घातer_करोमुख्य_driver = अणु
	.name = "scmi-power-domain",
	.probe = scmi_pm_करोमुख्य_probe,
	.id_table = scmi_id_table,
पूर्ण;
module_scmi_driver(scmi_घातer_करोमुख्य_driver);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCMI power domain driver");
MODULE_LICENSE("GPL v2");
