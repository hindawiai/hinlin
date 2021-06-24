<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI SCI Generic Power Doमुख्य Driver
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
 *	J Keerthy <j-keerthy@ti.com>
 *	Dave Gerlach <d-gerlach@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>
#समावेश <dt-bindings/soc/ti,sci_pm_करोमुख्य.h>

/**
 * काष्ठा ti_sci_genpd_provider: holds common TI SCI genpd provider data
 * @ti_sci: handle to TI SCI protocol driver that provides ops to
 *	    communicate with प्रणाली control processor.
 * @dev: poपूर्णांकer to dev क्रम the driver क्रम devm allocs
 * @pd_list: list of all the घातer करोमुख्यs on the device
 * @data: onecell data क्रम genpd core
 */
काष्ठा ti_sci_genpd_provider अणु
	स्थिर काष्ठा ti_sci_handle *ti_sci;
	काष्ठा device *dev;
	काष्ठा list_head pd_list;
	काष्ठा genpd_onecell_data data;
पूर्ण;

/**
 * काष्ठा ti_sci_pm_करोमुख्य: TI specअगरic data needed क्रम घातer करोमुख्य
 * @idx: index of the device that identअगरies it with the प्रणाली
 *	 control processor.
 * @exclusive: Permissions क्रम exclusive request or shared request of the
 *	       device.
 * @pd: generic_pm_करोमुख्य क्रम use with the genpd framework
 * @node: link क्रम the genpd list
 * @parent: link to the parent TI SCI genpd provider
 */
काष्ठा ti_sci_pm_करोमुख्य अणु
	पूर्णांक idx;
	u8 exclusive;
	काष्ठा generic_pm_करोमुख्य pd;
	काष्ठा list_head node;
	काष्ठा ti_sci_genpd_provider *parent;
पूर्ण;

#घोषणा genpd_to_ti_sci_pd(gpd) container_of(gpd, काष्ठा ti_sci_pm_करोमुख्य, pd)

/*
 * ti_sci_pd_घातer_off(): genpd घातer करोwn hook
 * @करोमुख्य: poपूर्णांकer to the घातerकरोमुख्य to घातer off
 */
अटल पूर्णांक ti_sci_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा ti_sci_pm_करोमुख्य *pd = genpd_to_ti_sci_pd(करोमुख्य);
	स्थिर काष्ठा ti_sci_handle *ti_sci = pd->parent->ti_sci;

	वापस ti_sci->ops.dev_ops.put_device(ti_sci, pd->idx);
पूर्ण

/*
 * ti_sci_pd_घातer_on(): genpd घातer up hook
 * @करोमुख्य: poपूर्णांकer to the घातerकरोमुख्य to घातer on
 */
अटल पूर्णांक ti_sci_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा ti_sci_pm_करोमुख्य *pd = genpd_to_ti_sci_pd(करोमुख्य);
	स्थिर काष्ठा ti_sci_handle *ti_sci = pd->parent->ti_sci;

	अगर (pd->exclusive)
		वापस ti_sci->ops.dev_ops.get_device_exclusive(ti_sci,
								pd->idx);
	अन्यथा
		वापस ti_sci->ops.dev_ops.get_device(ti_sci, pd->idx);
पूर्ण

/*
 * ti_sci_pd_xlate(): translation service क्रम TI SCI genpds
 * @genpdspec: DT identअगरication data क्रम the genpd
 * @data: genpd core data क्रम all the घातerकरोमुख्यs on the device
 */
अटल काष्ठा generic_pm_करोमुख्य *ti_sci_pd_xlate(
					काष्ठा of_phandle_args *genpdspec,
					व्योम *data)
अणु
	काष्ठा genpd_onecell_data *genpd_data = data;
	अचिन्हित पूर्णांक idx = genpdspec->args[0];

	अगर (genpdspec->args_count != 1 && genpdspec->args_count != 2)
		वापस ERR_PTR(-EINVAL);

	अगर (idx >= genpd_data->num_करोमुख्यs) अणु
		pr_err("%s: invalid domain index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!genpd_data->करोमुख्यs[idx])
		वापस ERR_PTR(-ENOENT);

	genpd_to_ti_sci_pd(genpd_data->करोमुख्यs[idx])->exclusive =
		genpdspec->args[1];

	वापस genpd_data->करोमुख्यs[idx];
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_sci_pm_करोमुख्य_matches[] = अणु
	अणु .compatible = "ti,sci-pm-domain", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sci_pm_करोमुख्य_matches);

अटल पूर्णांक ti_sci_pm_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ti_sci_genpd_provider *pd_provider;
	काष्ठा ti_sci_pm_करोमुख्य *pd;
	काष्ठा device_node *np = शून्य;
	काष्ठा of_phandle_args args;
	पूर्णांक ret;
	u32 max_id = 0;
	पूर्णांक index;

	pd_provider = devm_kzalloc(dev, माप(*pd_provider), GFP_KERNEL);
	अगर (!pd_provider)
		वापस -ENOMEM;

	pd_provider->ti_sci = devm_ti_sci_get_handle(dev);
	अगर (IS_ERR(pd_provider->ti_sci))
		वापस PTR_ERR(pd_provider->ti_sci);

	pd_provider->dev = dev;

	INIT_LIST_HEAD(&pd_provider->pd_list);

	/* Find highest device ID used क्रम घातer करोमुख्यs */
	जबतक (1) अणु
		np = of_find_node_with_property(np, "power-domains");
		अगर (!np)
			अवरोध;

		index = 0;

		जबतक (1) अणु
			ret = of_parse_phandle_with_args(np, "power-domains",
							 "#power-domain-cells",
							 index, &args);
			अगर (ret)
				अवरोध;

			अगर (args.args_count >= 1 && args.np == dev->of_node) अणु
				अगर (args.args[0] > max_id)
					max_id = args.args[0];

				pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
				अगर (!pd)
					वापस -ENOMEM;

				pd->pd.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							     "pd:%d",
							     args.args[0]);
				अगर (!pd->pd.name)
					वापस -ENOMEM;

				pd->pd.घातer_off = ti_sci_pd_घातer_off;
				pd->pd.घातer_on = ti_sci_pd_घातer_on;
				pd->idx = args.args[0];
				pd->parent = pd_provider;

				pm_genpd_init(&pd->pd, शून्य, true);

				list_add(&pd->node, &pd_provider->pd_list);
			पूर्ण
			index++;
		पूर्ण
	पूर्ण

	pd_provider->data.करोमुख्यs =
		devm_kसुस्मृति(dev, max_id + 1,
			     माप(*pd_provider->data.करोमुख्यs),
			     GFP_KERNEL);

	pd_provider->data.num_करोमुख्यs = max_id + 1;
	pd_provider->data.xlate = ti_sci_pd_xlate;

	list_क्रम_each_entry(pd, &pd_provider->pd_list, node)
		pd_provider->data.करोमुख्यs[pd->idx] = &pd->pd;

	वापस of_genpd_add_provider_onecell(dev->of_node, &pd_provider->data);
पूर्ण

अटल काष्ठा platक्रमm_driver ti_sci_pm_करोमुख्यs_driver = अणु
	.probe = ti_sci_pm_करोमुख्य_probe,
	.driver = अणु
		.name = "ti_sci_pm_domains",
		.of_match_table = ti_sci_pm_करोमुख्य_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_sci_pm_करोमुख्यs_driver);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI System Control Interface (SCI) Power Domain driver");
MODULE_AUTHOR("Dave Gerlach");
