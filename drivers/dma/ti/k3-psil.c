<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/sys_soc.h>

#समावेश "k3-psil-priv.h"

अटल DEFINE_MUTEX(ep_map_mutex);
अटल स्थिर काष्ठा psil_ep_map *soc_ep_map;

अटल स्थिर काष्ठा soc_device_attribute k3_soc_devices[] = अणु
	अणु .family = "AM65X", .data = &am654_ep_map पूर्ण,
	अणु .family = "J721E", .data = &j721e_ep_map पूर्ण,
	अणु .family = "J7200", .data = &j7200_ep_map पूर्ण,
	अणु .family = "AM64X", .data = &am64_ep_map पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा psil_endpoपूर्णांक_config *psil_get_ep_config(u32 thपढ़ो_id)
अणु
	पूर्णांक i;

	mutex_lock(&ep_map_mutex);
	अगर (!soc_ep_map) अणु
		स्थिर काष्ठा soc_device_attribute *soc;

		soc = soc_device_match(k3_soc_devices);
		अगर (soc) अणु
			soc_ep_map = soc->data;
		पूर्ण अन्यथा अणु
			pr_err("PSIL: No compatible machine found for map\n");
			mutex_unlock(&ep_map_mutex);
			वापस ERR_PTR(-ENOTSUPP);
		पूर्ण
		pr_debug("%s: Using map for %s\n", __func__, soc_ep_map->name);
	पूर्ण
	mutex_unlock(&ep_map_mutex);

	अगर (thपढ़ो_id & K3_PSIL_DST_THREAD_ID_OFFSET && soc_ep_map->dst) अणु
		/* check in destination thपढ़ो map */
		क्रम (i = 0; i < soc_ep_map->dst_count; i++) अणु
			अगर (soc_ep_map->dst[i].thपढ़ो_id == thपढ़ो_id)
				वापस &soc_ep_map->dst[i].ep_config;
		पूर्ण
	पूर्ण

	thपढ़ो_id &= ~K3_PSIL_DST_THREAD_ID_OFFSET;
	अगर (soc_ep_map->src) अणु
		क्रम (i = 0; i < soc_ep_map->src_count; i++) अणु
			अगर (soc_ep_map->src[i].thपढ़ो_id == thपढ़ो_id)
				वापस &soc_ep_map->src[i].ep_config;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL_GPL(psil_get_ep_config);

पूर्णांक psil_set_new_ep_config(काष्ठा device *dev, स्थिर अक्षर *name,
			   काष्ठा psil_endpoपूर्णांक_config *ep_config)
अणु
	काष्ठा psil_endpoपूर्णांक_config *dst_ep_config;
	काष्ठा of_phandle_args dma_spec;
	u32 thपढ़ो_id;
	पूर्णांक index;

	अगर (!dev || !dev->of_node)
		वापस -EINVAL;

	index = of_property_match_string(dev->of_node, "dma-names", name);
	अगर (index < 0)
		वापस index;

	अगर (of_parse_phandle_with_args(dev->of_node, "dmas", "#dma-cells",
				       index, &dma_spec))
		वापस -ENOENT;

	thपढ़ो_id = dma_spec.args[0];

	dst_ep_config = psil_get_ep_config(thपढ़ो_id);
	अगर (IS_ERR(dst_ep_config)) अणु
		pr_err("PSIL: thread ID 0x%04x not defined in map\n",
		       thपढ़ो_id);
		of_node_put(dma_spec.np);
		वापस PTR_ERR(dst_ep_config);
	पूर्ण

	स_नकल(dst_ep_config, ep_config, माप(*dst_ep_config));

	of_node_put(dma_spec.np);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(psil_set_new_ep_config);
