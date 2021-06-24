<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PM करोमुख्यs क्रम CPUs via genpd - managed by cpuidle-psci.
 *
 * Copyright (C) 2019 Linaro Ltd.
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 *
 */

#घोषणा pr_fmt(fmt) "CPUidle PSCI: " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/psci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "cpuidle-psci.h"

काष्ठा psci_pd_provider अणु
	काष्ठा list_head link;
	काष्ठा device_node *node;
पूर्ण;

अटल LIST_HEAD(psci_pd_providers);
अटल bool psci_pd_allow_करोमुख्य_state;

अटल पूर्णांक psci_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *pd)
अणु
	काष्ठा genpd_घातer_state *state = &pd->states[pd->state_idx];
	u32 *pd_state;

	अगर (!state->data)
		वापस 0;

	अगर (!psci_pd_allow_करोमुख्य_state)
		वापस -EBUSY;

	/* OSI mode is enabled, set the corresponding करोमुख्य state. */
	pd_state = state->data;
	psci_set_करोमुख्य_state(*pd_state);

	वापस 0;
पूर्ण

अटल पूर्णांक psci_pd_parse_state_nodes(काष्ठा genpd_घातer_state *states,
				     पूर्णांक state_count)
अणु
	पूर्णांक i, ret;
	u32 psci_state, *psci_state_buf;

	क्रम (i = 0; i < state_count; i++) अणु
		ret = psci_dt_parse_state_node(to_of_node(states[i].fwnode),
					&psci_state);
		अगर (ret)
			जाओ मुक्त_state;

		psci_state_buf = kदो_स्मृति(माप(u32), GFP_KERNEL);
		अगर (!psci_state_buf) अणु
			ret = -ENOMEM;
			जाओ मुक्त_state;
		पूर्ण
		*psci_state_buf = psci_state;
		states[i].data = psci_state_buf;
	पूर्ण

	वापस 0;

मुक्त_state:
	i--;
	क्रम (; i >= 0; i--)
		kमुक्त(states[i].data);
	वापस ret;
पूर्ण

अटल पूर्णांक psci_pd_parse_states(काष्ठा device_node *np,
			काष्ठा genpd_घातer_state **states, पूर्णांक *state_count)
अणु
	पूर्णांक ret;

	/* Parse the करोमुख्य idle states. */
	ret = of_genpd_parse_idle_states(np, states, state_count);
	अगर (ret)
		वापस ret;

	/* Fill out the PSCI specअगरics क्रम each found state. */
	ret = psci_pd_parse_state_nodes(*states, *state_count);
	अगर (ret)
		kमुक्त(*states);

	वापस ret;
पूर्ण

अटल व्योम psci_pd_मुक्त_states(काष्ठा genpd_घातer_state *states,
				अचिन्हित पूर्णांक state_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < state_count; i++)
		kमुक्त(states[i].data);
	kमुक्त(states);
पूर्ण

अटल पूर्णांक psci_pd_init(काष्ठा device_node *np, bool use_osi)
अणु
	काष्ठा generic_pm_करोमुख्य *pd;
	काष्ठा psci_pd_provider *pd_provider;
	काष्ठा dev_घातer_governor *pd_gov;
	काष्ठा genpd_घातer_state *states = शून्य;
	पूर्णांक ret = -ENOMEM, state_count = 0;

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		जाओ out;

	pd_provider = kzalloc(माप(*pd_provider), GFP_KERNEL);
	अगर (!pd_provider)
		जाओ मुक्त_pd;

	pd->name = kaप्र_लिखो(GFP_KERNEL, "%pOF", np);
	अगर (!pd->name)
		जाओ मुक्त_pd_prov;

	/*
	 * Parse the करोमुख्य idle states and let genpd manage the state selection
	 * क्रम those being compatible with "domain-idle-state".
	 */
	ret = psci_pd_parse_states(np, &states, &state_count);
	अगर (ret)
		जाओ मुक्त_name;

	pd->मुक्त_states = psci_pd_मुक्त_states;
	pd->name = kbasename(pd->name);
	pd->states = states;
	pd->state_count = state_count;
	pd->flags |= GENPD_FLAG_IRQ_SAFE | GENPD_FLAG_CPU_DOMAIN;

	/* Allow घातer off when OSI has been successfully enabled. */
	अगर (use_osi)
		pd->घातer_off = psci_pd_घातer_off;
	अन्यथा
		pd->flags |= GENPD_FLAG_ALWAYS_ON;

	/* Use governor क्रम CPU PM करोमुख्यs अगर it has some states to manage. */
	pd_gov = state_count > 0 ? &pm_करोमुख्य_cpu_gov : शून्य;

	ret = pm_genpd_init(pd, pd_gov, false);
	अगर (ret) अणु
		psci_pd_मुक्त_states(states, state_count);
		जाओ मुक्त_name;
	पूर्ण

	ret = of_genpd_add_provider_simple(np, pd);
	अगर (ret)
		जाओ हटाओ_pd;

	pd_provider->node = of_node_get(np);
	list_add(&pd_provider->link, &psci_pd_providers);

	pr_debug("init PM domain %s\n", pd->name);
	वापस 0;

हटाओ_pd:
	pm_genpd_हटाओ(pd);
मुक्त_name:
	kमुक्त(pd->name);
मुक्त_pd_prov:
	kमुक्त(pd_provider);
मुक्त_pd:
	kमुक्त(pd);
out:
	pr_err("failed to init PM domain ret=%d %pOF\n", ret, np);
	वापस ret;
पूर्ण

अटल व्योम psci_pd_हटाओ(व्योम)
अणु
	काष्ठा psci_pd_provider *pd_provider, *it;
	काष्ठा generic_pm_करोमुख्य *genpd;

	list_क्रम_each_entry_safe(pd_provider, it, &psci_pd_providers, link) अणु
		of_genpd_del_provider(pd_provider->node);

		genpd = of_genpd_हटाओ_last(pd_provider->node);
		अगर (!IS_ERR(genpd))
			kमुक्त(genpd);

		of_node_put(pd_provider->node);
		list_del(&pd_provider->link);
		kमुक्त(pd_provider);
	पूर्ण
पूर्ण

अटल पूर्णांक psci_pd_init_topology(काष्ठा device_node *np)
अणु
	काष्ठा device_node *node;
	काष्ठा of_phandle_args child, parent;
	पूर्णांक ret;

	क्रम_each_child_of_node(np, node) अणु
		अगर (of_parse_phandle_with_args(node, "power-domains",
					"#power-domain-cells", 0, &parent))
			जारी;

		child.np = node;
		child.args_count = 0;
		ret = of_genpd_add_subकरोमुख्य(&parent, &child);
		of_node_put(parent.np);
		अगर (ret) अणु
			of_node_put(node);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool psci_pd_try_set_osi_mode(व्योम)
अणु
	पूर्णांक ret;

	अगर (!psci_has_osi_support())
		वापस false;

	ret = psci_set_osi_mode(true);
	अगर (ret) अणु
		pr_warn("failed to enable OSI mode: %d\n", ret);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम psci_cpuidle_करोमुख्य_sync_state(काष्ठा device *dev)
अणु
	/*
	 * All devices have now been attached/probed to the PM करोमुख्य topology,
	 * hence it's fine to allow करोमुख्य states to be picked.
	 */
	psci_pd_allow_करोमुख्य_state = true;
पूर्ण

अटल स्थिर काष्ठा of_device_id psci_of_match[] = अणु
	अणु .compatible = "arm,psci-1.0" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक psci_cpuidle_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *node;
	bool use_osi;
	पूर्णांक ret = 0, pd_count = 0;

	अगर (!np)
		वापस -ENODEV;

	/* If OSI mode is supported, let's try to enable it. */
	use_osi = psci_pd_try_set_osi_mode();

	/*
	 * Parse child nodes क्रम the "#power-domain-cells" property and
	 * initialize a genpd/genpd-of-provider pair when it's found.
	 */
	क्रम_each_child_of_node(np, node) अणु
		अगर (!of_find_property(node, "#power-domain-cells", शून्य))
			जारी;

		ret = psci_pd_init(node, use_osi);
		अगर (ret)
			जाओ put_node;

		pd_count++;
	पूर्ण

	/* Bail out अगर not using the hierarchical CPU topology. */
	अगर (!pd_count)
		जाओ no_pd;

	/* Link genpd masters/subकरोमुख्यs to model the CPU topology. */
	ret = psci_pd_init_topology(np);
	अगर (ret)
		जाओ हटाओ_pd;

	pr_info("Initialized CPU PM domain topology\n");
	वापस 0;

put_node:
	of_node_put(node);
हटाओ_pd:
	psci_pd_हटाओ();
	pr_err("failed to create CPU PM domains ret=%d\n", ret);
no_pd:
	अगर (use_osi)
		psci_set_osi_mode(false);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver psci_cpuidle_करोमुख्य_driver = अणु
	.probe  = psci_cpuidle_करोमुख्य_probe,
	.driver = अणु
		.name = "psci-cpuidle-domain",
		.of_match_table = psci_of_match,
		.sync_state = psci_cpuidle_करोमुख्य_sync_state,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init psci_idle_init_करोमुख्यs(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&psci_cpuidle_करोमुख्य_driver);
पूर्ण
subsys_initcall(psci_idle_init_करोमुख्यs);

काष्ठा device *psci_dt_attach_cpu(पूर्णांक cpu)
अणु
	काष्ठा device *dev;

	dev = dev_pm_करोमुख्य_attach_by_name(get_cpu_device(cpu), "psci");
	अगर (IS_ERR_OR_शून्य(dev))
		वापस dev;

	pm_runसमय_irq_safe(dev);
	अगर (cpu_online(cpu))
		pm_runसमय_get_sync(dev);

	dev_pm_syscore_device(dev, true);

	वापस dev;
पूर्ण

व्योम psci_dt_detach_cpu(काष्ठा device *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev))
		वापस;

	dev_pm_करोमुख्य_detach(dev, false);
पूर्ण
