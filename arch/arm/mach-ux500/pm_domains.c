<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Linaro Ltd.
 *
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 *
 * Implements PM करोमुख्यs using the generic PM करोमुख्य क्रम ux500.
 */
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_करोमुख्य.h>

#समावेश <dt-bindings/arm/ux500_pm_करोमुख्यs.h>
#समावेश "pm_domains.h"

अटल पूर्णांक pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	/*
	 * Handle the gating of the PM करोमुख्य regulator here.
	 *
	 * Drivers/subप्रणालीs handling devices in the PM करोमुख्य needs to perक्रमm
	 * रेजिस्टर context save/restore from their respective runसमय PM
	 * callbacks, to be able to enable PM करोमुख्य gating/ungating.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	/*
	 * Handle the ungating of the PM करोमुख्य regulator here.
	 *
	 * Drivers/subप्रणालीs handling devices in the PM करोमुख्य needs to perक्रमm
	 * रेजिस्टर context save/restore from their respective runसमय PM
	 * callbacks, to be able to enable PM करोमुख्य gating/ungating.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा generic_pm_करोमुख्य ux500_pm_करोमुख्य_vape = अणु
	.name = "VAPE",
	.घातer_off = pd_घातer_off,
	.घातer_on = pd_घातer_on,
पूर्ण;

अटल काष्ठा generic_pm_करोमुख्य *ux500_pm_करोमुख्यs[NR_DOMAINS] = अणु
	[DOMAIN_VAPE] = &ux500_pm_करोमुख्य_vape,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ux500_pm_करोमुख्य_matches[] __initस्थिर = अणु
	अणु .compatible = "stericsson,ux500-pm-domains", पूर्ण,
	अणु पूर्ण,
पूर्ण;

पूर्णांक __init ux500_pm_करोमुख्यs_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा genpd_onecell_data *genpd_data;
	पूर्णांक i;

	np = of_find_matching_node(शून्य, ux500_pm_करोमुख्य_matches);
	अगर (!np)
		वापस -ENODEV;

	genpd_data = kzalloc(माप(*genpd_data), GFP_KERNEL);
	अगर (!genpd_data)
		वापस -ENOMEM;

	genpd_data->करोमुख्यs = ux500_pm_करोमुख्यs;
	genpd_data->num_करोमुख्यs = ARRAY_SIZE(ux500_pm_करोमुख्यs);

	क्रम (i = 0; i < ARRAY_SIZE(ux500_pm_करोमुख्यs); ++i)
		pm_genpd_init(ux500_pm_करोमुख्यs[i], शून्य, false);

	of_genpd_add_provider_onecell(np, genpd_data);
	वापस 0;
पूर्ण
