<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/of.h>

#समावेश <soc/tegra/common.h>

अटल स्थिर काष्ठा of_device_id tegra_machine_match[] = अणु
	अणु .compatible = "nvidia,tegra20", पूर्ण,
	अणु .compatible = "nvidia,tegra30", पूर्ण,
	अणु .compatible = "nvidia,tegra114", पूर्ण,
	अणु .compatible = "nvidia,tegra124", पूर्ण,
	अणु .compatible = "nvidia,tegra132", पूर्ण,
	अणु .compatible = "nvidia,tegra210", पूर्ण,
	अणु पूर्ण
पूर्ण;

bool soc_is_tegra(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *root;

	root = of_find_node_by_path("/");
	अगर (!root)
		वापस false;

	match = of_match_node(tegra_machine_match, root);
	of_node_put(root);

	वापस match != शून्य;
पूर्ण
