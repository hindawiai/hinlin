<शैली गुरु>
/*
 * Utils functions to implement the pincontrol driver.
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "pinctrl-utils.h"

पूर्णांक pinctrl_utils_reserve_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, अचिन्हित reserve)
अणु
	अचिन्हित old_num = *reserved_maps;
	अचिन्हित new_num = *num_maps + reserve;
	काष्ठा pinctrl_map *new_map;

	अगर (old_num >= new_num)
		वापस 0;

	new_map = kपुनः_स्मृति_array(*map, new_num, माप(*new_map), GFP_KERNEL);
	अगर (!new_map) अणु
		dev_err(pctldev->dev, "krealloc(map) failed\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(new_map + old_num, 0, (new_num - old_num) * माप(*new_map));

	*map = new_map;
	*reserved_maps = new_num;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_utils_reserve_map);

पूर्णांक pinctrl_utils_add_map_mux(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		स्थिर अक्षर *function)
अणु
	अगर (WARN_ON(*num_maps == *reserved_maps))
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = group;
	(*map)[*num_maps].data.mux.function = function;
	(*num_maps)++;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_utils_add_map_mux);

पूर्णांक pinctrl_utils_add_map_configs(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		अचिन्हित दीर्घ *configs, अचिन्हित num_configs,
		क्रमागत pinctrl_map_type type)
अणु
	अचिन्हित दीर्घ *dup_configs;

	अगर (WARN_ON(*num_maps == *reserved_maps))
		वापस -ENOSPC;

	dup_configs = kmemdup(configs, num_configs * माप(*dup_configs),
			      GFP_KERNEL);
	अगर (!dup_configs)
		वापस -ENOMEM;

	(*map)[*num_maps].type = type;
	(*map)[*num_maps].data.configs.group_or_pin = group;
	(*map)[*num_maps].data.configs.configs = dup_configs;
	(*map)[*num_maps].data.configs.num_configs = num_configs;
	(*num_maps)++;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_utils_add_map_configs);

पूर्णांक pinctrl_utils_add_config(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित दीर्घ **configs, अचिन्हित *num_configs,
		अचिन्हित दीर्घ config)
अणु
	अचिन्हित old_num = *num_configs;
	अचिन्हित new_num = old_num + 1;
	अचिन्हित दीर्घ *new_configs;

	new_configs = kपुनः_स्मृति(*configs, माप(*new_configs) * new_num,
			       GFP_KERNEL);
	अगर (!new_configs) अणु
		dev_err(pctldev->dev, "krealloc(configs) failed\n");
		वापस -ENOMEM;
	पूर्ण

	new_configs[old_num] = config;

	*configs = new_configs;
	*num_configs = new_num;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_utils_add_config);

व्योम pinctrl_utils_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
	      काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_maps; i++) अणु
		चयन (map[i].type) अणु
		हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		हाल PIN_MAP_TYPE_CONFIGS_PIN:
			kमुक्त(map[i].data.configs.configs);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(map);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_utils_मुक्त_map);
