<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device tree पूर्णांकegration क्रम the pin control subप्रणाली
 *
 * Copyright (C) 2012 NVIDIA CORPORATION. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "devicetree.h"

/**
 * काष्ठा pinctrl_dt_map - mapping table chunk parsed from device tree
 * @node: list node क्रम काष्ठा pinctrl's @dt_maps field
 * @pctldev: the pin controller that allocated this काष्ठा, and will मुक्त it
 * @map: the mapping table entries
 * @num_maps: number of mapping table entries
 */
काष्ठा pinctrl_dt_map अणु
	काष्ठा list_head node;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_map *map;
	अचिन्हित num_maps;
पूर्ण;

अटल व्योम dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
		     काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_maps; ++i) अणु
		kमुक्त_स्थिर(map[i].dev_name);
		map[i].dev_name = शून्य;
	पूर्ण

	अगर (pctldev) अणु
		स्थिर काष्ठा pinctrl_ops *ops = pctldev->desc->pctlops;
		अगर (ops->dt_मुक्त_map)
			ops->dt_मुक्त_map(pctldev, map, num_maps);
	पूर्ण अन्यथा अणु
		/* There is no pctldev क्रम PIN_MAP_TYPE_DUMMY_STATE */
		kमुक्त(map);
	पूर्ण
पूर्ण

व्योम pinctrl_dt_मुक्त_maps(काष्ठा pinctrl *p)
अणु
	काष्ठा pinctrl_dt_map *dt_map, *n1;

	list_क्रम_each_entry_safe(dt_map, n1, &p->dt_maps, node) अणु
		pinctrl_unरेजिस्टर_mappings(dt_map->map);
		list_del(&dt_map->node);
		dt_मुक्त_map(dt_map->pctldev, dt_map->map,
			    dt_map->num_maps);
		kमुक्त(dt_map);
	पूर्ण

	of_node_put(p->dev->of_node);
पूर्ण

अटल पूर्णांक dt_remember_or_मुक्त_map(काष्ठा pinctrl *p, स्थिर अक्षर *statename,
				   काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	पूर्णांक i;
	काष्ठा pinctrl_dt_map *dt_map;

	/* Initialize common mapping table entry fields */
	क्रम (i = 0; i < num_maps; i++) अणु
		स्थिर अक्षर *devname;

		devname = kstrdup_स्थिर(dev_name(p->dev), GFP_KERNEL);
		अगर (!devname)
			जाओ err_मुक्त_map;

		map[i].dev_name = devname;
		map[i].name = statename;
		अगर (pctldev)
			map[i].ctrl_dev_name = dev_name(pctldev->dev);
	पूर्ण

	/* Remember the converted mapping table entries */
	dt_map = kzalloc(माप(*dt_map), GFP_KERNEL);
	अगर (!dt_map)
		जाओ err_मुक्त_map;

	dt_map->pctldev = pctldev;
	dt_map->map = map;
	dt_map->num_maps = num_maps;
	list_add_tail(&dt_map->node, &p->dt_maps);

	वापस pinctrl_रेजिस्टर_mappings(map, num_maps);

err_मुक्त_map:
	dt_मुक्त_map(pctldev, map, num_maps);
	वापस -ENOMEM;
पूर्ण

काष्ठा pinctrl_dev *of_pinctrl_get(काष्ठा device_node *np)
अणु
	वापस get_pinctrl_dev_from_of_node(np);
पूर्ण
EXPORT_SYMBOL_GPL(of_pinctrl_get);

अटल पूर्णांक dt_to_map_one_config(काष्ठा pinctrl *p,
				काष्ठा pinctrl_dev *hog_pctldev,
				स्थिर अक्षर *statename,
				काष्ठा device_node *np_config)
अणु
	काष्ठा pinctrl_dev *pctldev = शून्य;
	काष्ठा device_node *np_pctldev;
	स्थिर काष्ठा pinctrl_ops *ops;
	पूर्णांक ret;
	काष्ठा pinctrl_map *map;
	अचिन्हित num_maps;
	bool allow_शेष = false;

	/* Find the pin controller containing np_config */
	np_pctldev = of_node_get(np_config);
	क्रम (;;) अणु
		अगर (!allow_शेष)
			allow_शेष = of_property_पढ़ो_bool(np_pctldev,
							      "pinctrl-use-default");

		np_pctldev = of_get_next_parent(np_pctldev);
		अगर (!np_pctldev || of_node_is_root(np_pctldev)) अणु
			of_node_put(np_pctldev);
			ret = driver_deferred_probe_check_state(p->dev);
			/* keep deferring अगर modules are enabled */
			अगर (IS_ENABLED(CONFIG_MODULES) && !allow_शेष && ret < 0)
				ret = -EPROBE_DEFER;
			वापस ret;
		पूर्ण
		/* If we're creating a hog we can use the passed pctldev */
		अगर (hog_pctldev && (np_pctldev == p->dev->of_node)) अणु
			pctldev = hog_pctldev;
			अवरोध;
		पूर्ण
		pctldev = get_pinctrl_dev_from_of_node(np_pctldev);
		अगर (pctldev)
			अवरोध;
		/* Do not defer probing of hogs (circular loop) */
		अगर (np_pctldev == p->dev->of_node) अणु
			of_node_put(np_pctldev);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	of_node_put(np_pctldev);

	/*
	 * Call pinctrl driver to parse device tree node, and
	 * generate mapping table entries
	 */
	ops = pctldev->desc->pctlops;
	अगर (!ops->dt_node_to_map) अणु
		dev_err(p->dev, "pctldev %s doesn't support DT\n",
			dev_name(pctldev->dev));
		वापस -ENODEV;
	पूर्ण
	ret = ops->dt_node_to_map(pctldev, np_config, &map, &num_maps);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (num_maps == 0) अणु
		/*
		 * If we have no valid maps (maybe caused by empty pinctrl node
		 * or typing error) ther is no need remember this, so just
		 * वापस.
		 */
		dev_info(p->dev,
			 "there is not valid maps for state %s\n", statename);
		वापस 0;
	पूर्ण

	/* Stash the mapping table chunk away क्रम later use */
	वापस dt_remember_or_मुक्त_map(p, statename, pctldev, map, num_maps);
पूर्ण

अटल पूर्णांक dt_remember_dummy_state(काष्ठा pinctrl *p, स्थिर अक्षर *statename)
अणु
	काष्ठा pinctrl_map *map;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	/* There is no pctldev क्रम PIN_MAP_TYPE_DUMMY_STATE */
	map->type = PIN_MAP_TYPE_DUMMY_STATE;

	वापस dt_remember_or_मुक्त_map(p, statename, शून्य, map, 1);
पूर्ण

पूर्णांक pinctrl_dt_to_map(काष्ठा pinctrl *p, काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा device_node *np = p->dev->of_node;
	पूर्णांक state, ret;
	अक्षर *propname;
	काष्ठा property *prop;
	स्थिर अक्षर *statename;
	स्थिर __be32 *list;
	पूर्णांक size, config;
	phandle phandle;
	काष्ठा device_node *np_config;

	/* CONFIG_OF enabled, p->dev not instantiated from DT */
	अगर (!np) अणु
		अगर (of_have_populated_dt())
			dev_dbg(p->dev,
				"no of_node; not parsing pinctrl DT\n");
		वापस 0;
	पूर्ण

	/* We may store poपूर्णांकers to property names within the node */
	of_node_get(np);

	/* For each defined state ID */
	क्रम (state = 0; ; state++) अणु
		/* Retrieve the pinctrl-* property */
		propname = kaप्र_लिखो(GFP_KERNEL, "pinctrl-%d", state);
		prop = of_find_property(np, propname, &size);
		kमुक्त(propname);
		अगर (!prop) अणु
			अगर (state == 0) अणु
				of_node_put(np);
				वापस -ENODEV;
			पूर्ण
			अवरोध;
		पूर्ण
		list = prop->value;
		size /= माप(*list);

		/* Determine whether pinctrl-names property names the state */
		ret = of_property_पढ़ो_string_index(np, "pinctrl-names",
						    state, &statename);
		/*
		 * If not, statename is just the पूर्णांकeger state ID. But rather
		 * than dynamically allocate it and have to मुक्त it later,
		 * just poपूर्णांक part way पूर्णांकo the property name क्रम the string.
		 */
		अगर (ret < 0)
			statename = prop->name + म_माप("pinctrl-");

		/* For every referenced pin configuration node in it */
		क्रम (config = 0; config < size; config++) अणु
			phandle = be32_to_cpup(list++);

			/* Look up the pin configuration node */
			np_config = of_find_node_by_phandle(phandle);
			अगर (!np_config) अणु
				dev_err(p->dev,
					"prop %s index %i invalid phandle\n",
					prop->name, config);
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			/* Parse the node */
			ret = dt_to_map_one_config(p, pctldev, statename,
						   np_config);
			of_node_put(np_config);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		/* No entries in DT? Generate a dummy state table entry */
		अगर (!size) अणु
			ret = dt_remember_dummy_state(p, statename);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	pinctrl_dt_मुक्त_maps(p);
	वापस ret;
पूर्ण

/*
 * For pinctrl binding, typically #pinctrl-cells is क्रम the pin controller
 * device, so either parent or gअक्रमparent. See pinctrl-bindings.txt.
 */
अटल पूर्णांक pinctrl_find_cells_size(स्थिर काष्ठा device_node *np)
अणु
	स्थिर अक्षर *cells_name = "#pinctrl-cells";
	पूर्णांक cells_size, error;

	error = of_property_पढ़ो_u32(np->parent, cells_name, &cells_size);
	अगर (error) अणु
		error = of_property_पढ़ो_u32(np->parent->parent,
					     cells_name, &cells_size);
		अगर (error)
			वापस -ENOENT;
	पूर्ण

	वापस cells_size;
पूर्ण

/**
 * pinctrl_get_list_and_count - Gets the list and it's cell size and number
 * @np: poपूर्णांकer to device node with the property
 * @list_name: property that contains the list
 * @list: poपूर्णांकer क्रम the list found
 * @cells_size: poपूर्णांकer क्रम the cell size found
 * @nr_elements: poपूर्णांकer क्रम the number of elements found
 *
 * Typically np is a single pinctrl entry containing the list.
 */
अटल पूर्णांक pinctrl_get_list_and_count(स्थिर काष्ठा device_node *np,
				      स्थिर अक्षर *list_name,
				      स्थिर __be32 **list,
				      पूर्णांक *cells_size,
				      पूर्णांक *nr_elements)
अणु
	पूर्णांक size;

	*cells_size = 0;
	*nr_elements = 0;

	*list = of_get_property(np, list_name, &size);
	अगर (!*list)
		वापस -ENOENT;

	*cells_size = pinctrl_find_cells_size(np);
	अगर (*cells_size < 0)
		वापस -ENOENT;

	/* First element is always the index within the pinctrl device */
	*nr_elements = (size / माप(**list)) / (*cells_size + 1);

	वापस 0;
पूर्ण

/**
 * pinctrl_count_index_with_args - Count number of elements in a pinctrl entry
 * @np: poपूर्णांकer to device node with the property
 * @list_name: property that contains the list
 *
 * Counts the number of elements in a pinctrl array consisting of an index
 * within the controller and a number of u32 entries specअगरied क्रम each
 * entry. Note that device_node is always क्रम the parent pin controller device.
 */
पूर्णांक pinctrl_count_index_with_args(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *list_name)
अणु
	स्थिर __be32 *list;
	पूर्णांक size, nr_cells, error;

	error = pinctrl_get_list_and_count(np, list_name, &list,
					   &nr_cells, &size);
	अगर (error)
		वापस error;

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_count_index_with_args);

/**
 * pinctrl_copy_args - Populates of_phandle_args based on index
 * @np: poपूर्णांकer to device node with the property
 * @list: poपूर्णांकer to a list with the elements
 * @index: entry within the list of elements
 * @nr_cells: number of cells in the list
 * @nr_elem: number of elements क्रम each entry in the list
 * @out_args: वापसed values
 *
 * Populates the of_phandle_args based on the index in the list.
 */
अटल पूर्णांक pinctrl_copy_args(स्थिर काष्ठा device_node *np,
			     स्थिर __be32 *list,
			     पूर्णांक index, पूर्णांक nr_cells, पूर्णांक nr_elem,
			     काष्ठा of_phandle_args *out_args)
अणु
	पूर्णांक i;

	स_रखो(out_args, 0, माप(*out_args));
	out_args->np = (काष्ठा device_node *)np;
	out_args->args_count = nr_cells + 1;

	अगर (index >= nr_elem)
		वापस -EINVAL;

	list += index * (nr_cells + 1);

	क्रम (i = 0; i < nr_cells + 1; i++)
		out_args->args[i] = be32_to_cpup(list++);

	वापस 0;
पूर्ण

/**
 * pinctrl_parse_index_with_args - Find a node poपूर्णांकed by index in a list
 * @np: poपूर्णांकer to device node with the property
 * @list_name: property that contains the list
 * @index: index within the list
 * @out_args: entries in the list poपूर्णांकed by index
 *
 * Finds the selected element in a pinctrl array consisting of an index
 * within the controller and a number of u32 entries specअगरied क्रम each
 * entry. Note that device_node is always क्रम the parent pin controller device.
 */
पूर्णांक pinctrl_parse_index_with_args(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *list_name, पूर्णांक index,
				  काष्ठा of_phandle_args *out_args)
अणु
	स्थिर __be32 *list;
	पूर्णांक nr_elem, nr_cells, error;

	error = pinctrl_get_list_and_count(np, list_name, &list,
					   &nr_cells, &nr_elem);
	अगर (error || !nr_cells)
		वापस error;

	error = pinctrl_copy_args(np, list, index, nr_cells, nr_elem,
				  out_args);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_parse_index_with_args);
