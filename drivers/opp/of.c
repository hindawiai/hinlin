<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic OPP OF helpers
 *
 * Copyright (C) 2009-2010 Texas Instruments Incorporated.
 *	Nishanth Menon
 *	Romit Dasgupta
 *	Kevin Hilman
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/energy_model.h>

#समावेश "opp.h"

/*
 * Returns opp descriptor node क्रम a device node, caller must
 * करो of_node_put().
 */
अटल काष्ठा device_node *_opp_of_get_opp_desc_node(काष्ठा device_node *np,
						     पूर्णांक index)
अणु
	/* "operating-points-v2" can be an array क्रम घातer करोमुख्य providers */
	वापस of_parse_phandle(np, "operating-points-v2", index);
पूर्ण

/* Returns opp descriptor node क्रम a device, caller must करो of_node_put() */
काष्ठा device_node *dev_pm_opp_of_get_opp_desc_node(काष्ठा device *dev)
अणु
	वापस _opp_of_get_opp_desc_node(dev->of_node, 0);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_get_opp_desc_node);

काष्ठा opp_table *_managed_opp(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा opp_table *opp_table, *managed_table = शून्य;
	काष्ठा device_node *np;

	np = _opp_of_get_opp_desc_node(dev->of_node, index);
	अगर (!np)
		वापस शून्य;

	list_क्रम_each_entry(opp_table, &opp_tables, node) अणु
		अगर (opp_table->np == np) अणु
			/*
			 * Multiple devices can poपूर्णांक to the same OPP table and
			 * so will have same node-poपूर्णांकer, np.
			 *
			 * But the OPPs will be considered as shared only अगर the
			 * OPP table contains a "opp-shared" property.
			 */
			अगर (opp_table->shared_opp == OPP_TABLE_ACCESS_SHARED) अणु
				_get_opp_table_kref(opp_table);
				managed_table = opp_table;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(np);

	वापस managed_table;
पूर्ण

/* The caller must call dev_pm_opp_put() after the OPP is used */
अटल काष्ठा dev_pm_opp *_find_opp_of_np(काष्ठा opp_table *opp_table,
					  काष्ठा device_node *opp_np)
अणु
	काष्ठा dev_pm_opp *opp;

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
		अगर (opp->np == opp_np) अणु
			dev_pm_opp_get(opp);
			mutex_unlock(&opp_table->lock);
			वापस opp;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);

	वापस शून्य;
पूर्ण

अटल काष्ठा device_node *of_parse_required_opp(काष्ठा device_node *np,
						 पूर्णांक index)
अणु
	काष्ठा device_node *required_np;

	required_np = of_parse_phandle(np, "required-opps", index);
	अगर (unlikely(!required_np)) अणु
		pr_err("%s: Unable to parse required-opps: %pOF, index: %d\n",
		       __func__, np, index);
	पूर्ण

	वापस required_np;
पूर्ण

/* The caller must call dev_pm_opp_put_opp_table() after the table is used */
अटल काष्ठा opp_table *_find_table_of_opp_np(काष्ठा device_node *opp_np)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा device_node *opp_table_np;

	opp_table_np = of_get_parent(opp_np);
	अगर (!opp_table_np)
		जाओ err;

	/* It is safe to put the node now as all we need now is its address */
	of_node_put(opp_table_np);

	mutex_lock(&opp_table_lock);
	list_क्रम_each_entry(opp_table, &opp_tables, node) अणु
		अगर (opp_table_np == opp_table->np) अणु
			_get_opp_table_kref(opp_table);
			mutex_unlock(&opp_table_lock);
			वापस opp_table;
		पूर्ण
	पूर्ण
	mutex_unlock(&opp_table_lock);

err:
	वापस ERR_PTR(-ENODEV);
पूर्ण

/* Free resources previously acquired by _opp_table_alloc_required_tables() */
अटल व्योम _opp_table_मुक्त_required_tables(काष्ठा opp_table *opp_table)
अणु
	काष्ठा opp_table **required_opp_tables = opp_table->required_opp_tables;
	पूर्णांक i;

	अगर (!required_opp_tables)
		वापस;

	क्रम (i = 0; i < opp_table->required_opp_count; i++) अणु
		अगर (IS_ERR_OR_शून्य(required_opp_tables[i]))
			जारी;

		dev_pm_opp_put_opp_table(required_opp_tables[i]);
	पूर्ण

	kमुक्त(required_opp_tables);

	opp_table->required_opp_count = 0;
	opp_table->required_opp_tables = शून्य;
	list_del(&opp_table->lazy);
पूर्ण

/*
 * Populate all devices and opp tables which are part of "required-opps" list.
 * Checking only the first OPP node should be enough.
 */
अटल व्योम _opp_table_alloc_required_tables(काष्ठा opp_table *opp_table,
					     काष्ठा device *dev,
					     काष्ठा device_node *opp_np)
अणु
	काष्ठा opp_table **required_opp_tables;
	काष्ठा device_node *required_np, *np;
	bool lazy = false;
	पूर्णांक count, i;

	/* Traversing the first OPP node is all we need */
	np = of_get_next_available_child(opp_np, शून्य);
	अगर (!np) अणु
		dev_warn(dev, "Empty OPP table\n");

		वापस;
	पूर्ण

	count = of_count_phandle_with_args(np, "required-opps", शून्य);
	अगर (!count)
		जाओ put_np;

	required_opp_tables = kसुस्मृति(count, माप(*required_opp_tables),
				      GFP_KERNEL);
	अगर (!required_opp_tables)
		जाओ put_np;

	opp_table->required_opp_tables = required_opp_tables;
	opp_table->required_opp_count = count;

	क्रम (i = 0; i < count; i++) अणु
		required_np = of_parse_required_opp(np, i);
		अगर (!required_np)
			जाओ मुक्त_required_tables;

		required_opp_tables[i] = _find_table_of_opp_np(required_np);
		of_node_put(required_np);

		अगर (IS_ERR(required_opp_tables[i])) अणु
			lazy = true;
			जारी;
		पूर्ण

		/*
		 * We only support genpd's OPPs in the "required-opps" क्रम now,
		 * as we करोn't know how much about other हालs. Error out अगर the
		 * required OPP करोesn't beदीर्घ to a genpd.
		 */
		अगर (!required_opp_tables[i]->is_genpd) अणु
			dev_err(dev, "required-opp doesn't belong to genpd: %pOF\n",
				required_np);
			जाओ मुक्त_required_tables;
		पूर्ण
	पूर्ण

	/* Let's करो the linking later on */
	अगर (lazy)
		list_add(&opp_table->lazy, &lazy_opp_tables);

	जाओ put_np;

मुक्त_required_tables:
	_opp_table_मुक्त_required_tables(opp_table);
put_np:
	of_node_put(np);
पूर्ण

व्योम _of_init_opp_table(काष्ठा opp_table *opp_table, काष्ठा device *dev,
			पूर्णांक index)
अणु
	काष्ठा device_node *np, *opp_np;
	u32 val;

	/*
	 * Only required क्रम backward compatibility with v1 bindings, but isn't
	 * harmful क्रम other हालs. And so we करो it unconditionally.
	 */
	np = of_node_get(dev->of_node);
	अगर (!np)
		वापस;

	अगर (!of_property_पढ़ो_u32(np, "clock-latency", &val))
		opp_table->घड़ी_latency_ns_max = val;
	of_property_पढ़ो_u32(np, "voltage-tolerance",
			     &opp_table->voltage_tolerance_v1);

	अगर (of_find_property(np, "#power-domain-cells", शून्य))
		opp_table->is_genpd = true;

	/* Get OPP table node */
	opp_np = _opp_of_get_opp_desc_node(np, index);
	of_node_put(np);

	अगर (!opp_np)
		वापस;

	अगर (of_property_पढ़ो_bool(opp_np, "opp-shared"))
		opp_table->shared_opp = OPP_TABLE_ACCESS_SHARED;
	अन्यथा
		opp_table->shared_opp = OPP_TABLE_ACCESS_EXCLUSIVE;

	opp_table->np = opp_np;

	_opp_table_alloc_required_tables(opp_table, dev, opp_np);
	of_node_put(opp_np);
पूर्ण

व्योम _of_clear_opp_table(काष्ठा opp_table *opp_table)
अणु
	_opp_table_मुक्त_required_tables(opp_table);
पूर्ण

/*
 * Release all resources previously acquired with a call to
 * _of_opp_alloc_required_opps().
 */
व्योम _of_opp_मुक्त_required_opps(काष्ठा opp_table *opp_table,
				काष्ठा dev_pm_opp *opp)
अणु
	काष्ठा dev_pm_opp **required_opps = opp->required_opps;
	पूर्णांक i;

	अगर (!required_opps)
		वापस;

	क्रम (i = 0; i < opp_table->required_opp_count; i++) अणु
		अगर (!required_opps[i])
			जारी;

		/* Put the reference back */
		dev_pm_opp_put(required_opps[i]);
	पूर्ण

	opp->required_opps = शून्य;
	kमुक्त(required_opps);
पूर्ण

/* Populate all required OPPs which are part of "required-opps" list */
अटल पूर्णांक _of_opp_alloc_required_opps(काष्ठा opp_table *opp_table,
				       काष्ठा dev_pm_opp *opp)
अणु
	काष्ठा dev_pm_opp **required_opps;
	काष्ठा opp_table *required_table;
	काष्ठा device_node *np;
	पूर्णांक i, ret, count = opp_table->required_opp_count;

	अगर (!count)
		वापस 0;

	required_opps = kसुस्मृति(count, माप(*required_opps), GFP_KERNEL);
	अगर (!required_opps)
		वापस -ENOMEM;

	opp->required_opps = required_opps;

	क्रम (i = 0; i < count; i++) अणु
		required_table = opp_table->required_opp_tables[i];

		/* Required table not added yet, we will link later */
		अगर (IS_ERR_OR_शून्य(required_table))
			जारी;

		np = of_parse_required_opp(opp->np, i);
		अगर (unlikely(!np)) अणु
			ret = -ENODEV;
			जाओ मुक्त_required_opps;
		पूर्ण

		required_opps[i] = _find_opp_of_np(required_table, np);
		of_node_put(np);

		अगर (!required_opps[i]) अणु
			pr_err("%s: Unable to find required OPP node: %pOF (%d)\n",
			       __func__, opp->np, i);
			ret = -ENODEV;
			जाओ मुक्त_required_opps;
		पूर्ण
	पूर्ण

	वापस 0;

मुक्त_required_opps:
	_of_opp_मुक्त_required_opps(opp_table, opp);

	वापस ret;
पूर्ण

/* Link required OPPs क्रम an inभागidual OPP */
अटल पूर्णांक lazy_link_required_opps(काष्ठा opp_table *opp_table,
				   काष्ठा opp_table *new_table, पूर्णांक index)
अणु
	काष्ठा device_node *required_np;
	काष्ठा dev_pm_opp *opp;

	list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
		required_np = of_parse_required_opp(opp->np, index);
		अगर (unlikely(!required_np))
			वापस -ENODEV;

		opp->required_opps[index] = _find_opp_of_np(new_table, required_np);
		of_node_put(required_np);

		अगर (!opp->required_opps[index]) अणु
			pr_err("%s: Unable to find required OPP node: %pOF (%d)\n",
			       __func__, opp->np, index);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Link required OPPs क्रम all OPPs of the newly added OPP table */
अटल व्योम lazy_link_required_opp_table(काष्ठा opp_table *new_table)
अणु
	काष्ठा opp_table *opp_table, *temp, **required_opp_tables;
	काष्ठा device_node *required_np, *opp_np, *required_table_np;
	काष्ठा dev_pm_opp *opp;
	पूर्णांक i, ret;

	/*
	 * We only support genpd's OPPs in the "required-opps" क्रम now,
	 * as we करोn't know much about other हालs.
	 */
	अगर (!new_table->is_genpd)
		वापस;

	mutex_lock(&opp_table_lock);

	list_क्रम_each_entry_safe(opp_table, temp, &lazy_opp_tables, lazy) अणु
		bool lazy = false;

		/* opp_np can't be invalid here */
		opp_np = of_get_next_available_child(opp_table->np, शून्य);

		क्रम (i = 0; i < opp_table->required_opp_count; i++) अणु
			required_opp_tables = opp_table->required_opp_tables;

			/* Required opp-table is alपढ़ोy parsed */
			अगर (!IS_ERR(required_opp_tables[i]))
				जारी;

			/* required_np can't be invalid here */
			required_np = of_parse_required_opp(opp_np, i);
			required_table_np = of_get_parent(required_np);

			of_node_put(required_table_np);
			of_node_put(required_np);

			/*
			 * Newly added table isn't the required opp-table क्रम
			 * opp_table.
			 */
			अगर (required_table_np != new_table->np) अणु
				lazy = true;
				जारी;
			पूर्ण

			required_opp_tables[i] = new_table;
			_get_opp_table_kref(new_table);

			/* Link OPPs now */
			ret = lazy_link_required_opps(opp_table, new_table, i);
			अगर (ret) अणु
				/* The OPPs will be marked unusable */
				lazy = false;
				अवरोध;
			पूर्ण
		पूर्ण

		of_node_put(opp_np);

		/* All required opp-tables found, हटाओ from lazy list */
		अगर (!lazy) अणु
			list_del(&opp_table->lazy);
			INIT_LIST_HEAD(&opp_table->lazy);

			list_क्रम_each_entry(opp, &opp_table->opp_list, node)
				_required_opps_available(opp, opp_table->required_opp_count);
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table_lock);
पूर्ण

अटल पूर्णांक _bandwidth_supported(काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	काष्ठा device_node *np, *opp_np;
	काष्ठा property *prop;

	अगर (!opp_table) अणु
		np = of_node_get(dev->of_node);
		अगर (!np)
			वापस -ENODEV;

		opp_np = _opp_of_get_opp_desc_node(np, 0);
		of_node_put(np);
	पूर्ण अन्यथा अणु
		opp_np = of_node_get(opp_table->np);
	पूर्ण

	/* Lets not fail in हाल we are parsing opp-v1 bindings */
	अगर (!opp_np)
		वापस 0;

	/* Checking only first OPP is sufficient */
	np = of_get_next_available_child(opp_np, शून्य);
	अगर (!np) अणु
		dev_err(dev, "OPP table empty\n");
		वापस -EINVAL;
	पूर्ण
	of_node_put(opp_np);

	prop = of_find_property(np, "opp-peak-kBps", शून्य);
	of_node_put(np);

	अगर (!prop || !prop->length)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक dev_pm_opp_of_find_icc_paths(काष्ठा device *dev,
				 काष्ठा opp_table *opp_table)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret, i, count, num_paths;
	काष्ठा icc_path **paths;

	ret = _bandwidth_supported(dev, opp_table);
	अगर (ret == -EINVAL)
		वापस 0; /* Empty OPP table is a valid corner-हाल, let's not fail */
	अन्यथा अगर (ret <= 0)
		वापस ret;

	ret = 0;

	np = of_node_get(dev->of_node);
	अगर (!np)
		वापस 0;

	count = of_count_phandle_with_args(np, "interconnects",
					   "#interconnect-cells");
	of_node_put(np);
	अगर (count < 0)
		वापस 0;

	/* two phandles when #पूर्णांकerconnect-cells = <1> */
	अगर (count % 2) अणु
		dev_err(dev, "%s: Invalid interconnects values\n", __func__);
		वापस -EINVAL;
	पूर्ण

	num_paths = count / 2;
	paths = kसुस्मृति(num_paths, माप(*paths), GFP_KERNEL);
	अगर (!paths)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_paths; i++) अणु
		paths[i] = of_icc_get_by_index(dev, i);
		अगर (IS_ERR(paths[i])) अणु
			ret = PTR_ERR(paths[i]);
			अगर (ret != -EPROBE_DEFER) अणु
				dev_err(dev, "%s: Unable to get path%d: %d\n",
					__func__, i, ret);
			पूर्ण
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (opp_table) अणु
		opp_table->paths = paths;
		opp_table->path_count = num_paths;
		वापस 0;
	पूर्ण

err:
	जबतक (i--)
		icc_put(paths[i]);

	kमुक्त(paths);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_find_icc_paths);

अटल bool _opp_is_supported(काष्ठा device *dev, काष्ठा opp_table *opp_table,
			      काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक levels = opp_table->supported_hw_count;
	पूर्णांक count, versions, ret, i, j;
	u32 val;

	अगर (!opp_table->supported_hw) अणु
		/*
		 * In the हाल that no supported_hw has been set by the
		 * platक्रमm but there is an opp-supported-hw value set क्रम
		 * an OPP then the OPP should not be enabled as there is
		 * no way to see अगर the hardware supports it.
		 */
		अगर (of_find_property(np, "opp-supported-hw", शून्य))
			वापस false;
		अन्यथा
			वापस true;
	पूर्ण

	count = of_property_count_u32_elems(np, "opp-supported-hw");
	अगर (count <= 0 || count % levels) अणु
		dev_err(dev, "%s: Invalid opp-supported-hw property (%d)\n",
			__func__, count);
		वापस false;
	पूर्ण

	versions = count / levels;

	/* All levels in at least one of the versions should match */
	क्रम (i = 0; i < versions; i++) अणु
		bool supported = true;

		क्रम (j = 0; j < levels; j++) अणु
			ret = of_property_पढ़ो_u32_index(np, "opp-supported-hw",
							 i * levels + j, &val);
			अगर (ret) अणु
				dev_warn(dev, "%s: failed to read opp-supported-hw property at index %d: %d\n",
					 __func__, i * levels + j, ret);
				वापस false;
			पूर्ण

			/* Check अगर the level is supported */
			अगर (!(val & opp_table->supported_hw[j])) अणु
				supported = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (supported)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक opp_parse_supplies(काष्ठा dev_pm_opp *opp, काष्ठा device *dev,
			      काष्ठा opp_table *opp_table)
अणु
	u32 *microvolt, *microamp = शून्य;
	पूर्णांक supplies = opp_table->regulator_count, vcount, icount, ret, i, j;
	काष्ठा property *prop = शून्य;
	अक्षर name[NAME_MAX];

	/* Search क्रम "opp-microvolt-<name>" */
	अगर (opp_table->prop_name) अणु
		snम_लिखो(name, माप(name), "opp-microvolt-%s",
			 opp_table->prop_name);
		prop = of_find_property(opp->np, name, शून्य);
	पूर्ण

	अगर (!prop) अणु
		/* Search क्रम "opp-microvolt" */
		प्र_लिखो(name, "opp-microvolt");
		prop = of_find_property(opp->np, name, शून्य);

		/* Missing property isn't a problem, but an invalid entry is */
		अगर (!prop) अणु
			अगर (unlikely(supplies == -1)) अणु
				/* Initialize regulator_count */
				opp_table->regulator_count = 0;
				वापस 0;
			पूर्ण

			अगर (!supplies)
				वापस 0;

			dev_err(dev, "%s: opp-microvolt missing although OPP managing regulators\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (unlikely(supplies == -1)) अणु
		/* Initialize regulator_count */
		supplies = opp_table->regulator_count = 1;
	पूर्ण अन्यथा अगर (unlikely(!supplies)) अणु
		dev_err(dev, "%s: opp-microvolt wasn't expected\n", __func__);
		वापस -EINVAL;
	पूर्ण

	vcount = of_property_count_u32_elems(opp->np, name);
	अगर (vcount < 0) अणु
		dev_err(dev, "%s: Invalid %s property (%d)\n",
			__func__, name, vcount);
		वापस vcount;
	पूर्ण

	/* There can be one or three elements per supply */
	अगर (vcount != supplies && vcount != supplies * 3) अणु
		dev_err(dev, "%s: Invalid number of elements in %s property (%d) with supplies (%d)\n",
			__func__, name, vcount, supplies);
		वापस -EINVAL;
	पूर्ण

	microvolt = kदो_स्मृति_array(vcount, माप(*microvolt), GFP_KERNEL);
	अगर (!microvolt)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(opp->np, name, microvolt, vcount);
	अगर (ret) अणु
		dev_err(dev, "%s: error parsing %s: %d\n", __func__, name, ret);
		ret = -EINVAL;
		जाओ मुक्त_microvolt;
	पूर्ण

	/* Search क्रम "opp-microamp-<name>" */
	prop = शून्य;
	अगर (opp_table->prop_name) अणु
		snम_लिखो(name, माप(name), "opp-microamp-%s",
			 opp_table->prop_name);
		prop = of_find_property(opp->np, name, शून्य);
	पूर्ण

	अगर (!prop) अणु
		/* Search क्रम "opp-microamp" */
		प्र_लिखो(name, "opp-microamp");
		prop = of_find_property(opp->np, name, शून्य);
	पूर्ण

	अगर (prop) अणु
		icount = of_property_count_u32_elems(opp->np, name);
		अगर (icount < 0) अणु
			dev_err(dev, "%s: Invalid %s property (%d)\n", __func__,
				name, icount);
			ret = icount;
			जाओ मुक्त_microvolt;
		पूर्ण

		अगर (icount != supplies) अणु
			dev_err(dev, "%s: Invalid number of elements in %s property (%d) with supplies (%d)\n",
				__func__, name, icount, supplies);
			ret = -EINVAL;
			जाओ मुक्त_microvolt;
		पूर्ण

		microamp = kदो_स्मृति_array(icount, माप(*microamp), GFP_KERNEL);
		अगर (!microamp) अणु
			ret = -EINVAL;
			जाओ मुक्त_microvolt;
		पूर्ण

		ret = of_property_पढ़ो_u32_array(opp->np, name, microamp,
						 icount);
		अगर (ret) अणु
			dev_err(dev, "%s: error parsing %s: %d\n", __func__,
				name, ret);
			ret = -EINVAL;
			जाओ मुक्त_microamp;
		पूर्ण
	पूर्ण

	क्रम (i = 0, j = 0; i < supplies; i++) अणु
		opp->supplies[i].u_volt = microvolt[j++];

		अगर (vcount == supplies) अणु
			opp->supplies[i].u_volt_min = opp->supplies[i].u_volt;
			opp->supplies[i].u_volt_max = opp->supplies[i].u_volt;
		पूर्ण अन्यथा अणु
			opp->supplies[i].u_volt_min = microvolt[j++];
			opp->supplies[i].u_volt_max = microvolt[j++];
		पूर्ण

		अगर (microamp)
			opp->supplies[i].u_amp = microamp[i];
	पूर्ण

मुक्त_microamp:
	kमुक्त(microamp);
मुक्त_microvolt:
	kमुक्त(microvolt);

	वापस ret;
पूर्ण

/**
 * dev_pm_opp_of_हटाओ_table() - Free OPP table entries created from अटल DT
 *				  entries
 * @dev:	device poपूर्णांकer used to lookup OPP table.
 *
 * Free OPPs created using अटल entries present in DT.
 */
व्योम dev_pm_opp_of_हटाओ_table(काष्ठा device *dev)
अणु
	dev_pm_opp_हटाओ_table(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_हटाओ_table);

अटल पूर्णांक _पढ़ो_bw(काष्ठा dev_pm_opp *new_opp, काष्ठा opp_table *table,
		    काष्ठा device_node *np, bool peak)
अणु
	स्थिर अक्षर *name = peak ? "opp-peak-kBps" : "opp-avg-kBps";
	काष्ठा property *prop;
	पूर्णांक i, count, ret;
	u32 *bw;

	prop = of_find_property(np, name, शून्य);
	अगर (!prop)
		वापस -ENODEV;

	count = prop->length / माप(u32);
	अगर (table->path_count != count) अणु
		pr_err("%s: Mismatch between %s and paths (%d %d)\n",
				__func__, name, count, table->path_count);
		वापस -EINVAL;
	पूर्ण

	bw = kदो_स्मृति_array(count, माप(*bw), GFP_KERNEL);
	अगर (!bw)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(np, name, bw, count);
	अगर (ret) अणु
		pr_err("%s: Error parsing %s: %d\n", __func__, name, ret);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (peak)
			new_opp->bandwidth[i].peak = kBps_to_icc(bw[i]);
		अन्यथा
			new_opp->bandwidth[i].avg = kBps_to_icc(bw[i]);
	पूर्ण

out:
	kमुक्त(bw);
	वापस ret;
पूर्ण

अटल पूर्णांक _पढ़ो_opp_key(काष्ठा dev_pm_opp *new_opp, काष्ठा opp_table *table,
			 काष्ठा device_node *np, bool *rate_not_available)
अणु
	bool found = false;
	u64 rate;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u64(np, "opp-hz", &rate);
	अगर (!ret) अणु
		/*
		 * Rate is defined as an अचिन्हित दीर्घ in clk API, and so
		 * casting explicitly to its type. Must be fixed once rate is 64
		 * bit guaranteed in clk API.
		 */
		new_opp->rate = (अचिन्हित दीर्घ)rate;
		found = true;
	पूर्ण
	*rate_not_available = !!ret;

	/*
	 * Bandwidth consists of peak and average (optional) values:
	 * opp-peak-kBps = <path1_value path2_value>;
	 * opp-avg-kBps = <path1_value path2_value>;
	 */
	ret = _पढ़ो_bw(new_opp, table, np, true);
	अगर (!ret) अणु
		found = true;
		ret = _पढ़ो_bw(new_opp, table, np, false);
	पूर्ण

	/* The properties were found but we failed to parse them */
	अगर (ret && ret != -ENODEV)
		वापस ret;

	अगर (!of_property_पढ़ो_u32(np, "opp-level", &new_opp->level))
		found = true;

	अगर (found)
		वापस 0;

	वापस ret;
पूर्ण

/**
 * _opp_add_अटल_v2() - Allocate अटल OPPs (As per 'v2' DT bindings)
 * @opp_table:	OPP table
 * @dev:	device क्रम which we करो this operation
 * @np:		device node
 *
 * This function adds an opp definition to the opp table and वापसs status. The
 * opp can be controlled using dev_pm_opp_enable/disable functions and may be
 * हटाओd by dev_pm_opp_हटाओ.
 *
 * Return:
 * Valid OPP poपूर्णांकer:
 *		On success
 * शून्य:
 *		Duplicate OPPs (both freq and volt are same) and opp->available
 *		OR अगर the OPP is not supported by hardware.
 * ERR_PTR(-EEXIST):
 *		Freq are same and volt are dअगरferent OR
 *		Duplicate OPPs (both freq and volt are same) and !opp->available
 * ERR_PTR(-ENOMEM):
 *		Memory allocation failure
 * ERR_PTR(-EINVAL):
 *		Failed parsing the OPP node
 */
अटल काष्ठा dev_pm_opp *_opp_add_अटल_v2(काष्ठा opp_table *opp_table,
		काष्ठा device *dev, काष्ठा device_node *np)
अणु
	काष्ठा dev_pm_opp *new_opp;
	u32 val;
	पूर्णांक ret;
	bool rate_not_available = false;

	new_opp = _opp_allocate(opp_table);
	अगर (!new_opp)
		वापस ERR_PTR(-ENOMEM);

	ret = _पढ़ो_opp_key(new_opp, opp_table, np, &rate_not_available);
	अगर (ret < 0 && !opp_table->is_genpd) अणु
		dev_err(dev, "%s: opp key field not found\n", __func__);
		जाओ मुक्त_opp;
	पूर्ण

	/* Check अगर the OPP supports hardware's hierarchy of versions or not */
	अगर (!_opp_is_supported(dev, opp_table, np)) अणु
		dev_dbg(dev, "OPP not supported by hardware: %lu\n",
			new_opp->rate);
		जाओ मुक्त_opp;
	पूर्ण

	new_opp->turbo = of_property_पढ़ो_bool(np, "turbo-mode");

	new_opp->np = np;
	new_opp->dynamic = false;
	new_opp->available = true;

	ret = _of_opp_alloc_required_opps(opp_table, new_opp);
	अगर (ret)
		जाओ मुक्त_opp;

	अगर (!of_property_पढ़ो_u32(np, "clock-latency-ns", &val))
		new_opp->घड़ी_latency_ns = val;

	ret = opp_parse_supplies(new_opp, dev, opp_table);
	अगर (ret)
		जाओ मुक्त_required_opps;

	अगर (opp_table->is_genpd)
		new_opp->pstate = pm_genpd_opp_to_perक्रमmance_state(dev, new_opp);

	ret = _opp_add(dev, new_opp, opp_table, rate_not_available);
	अगर (ret) अणु
		/* Don't वापस error क्रम duplicate OPPs */
		अगर (ret == -EBUSY)
			ret = 0;
		जाओ मुक्त_required_opps;
	पूर्ण

	/* OPP to select on device suspend */
	अगर (of_property_पढ़ो_bool(np, "opp-suspend")) अणु
		अगर (opp_table->suspend_opp) अणु
			/* Pick the OPP with higher rate as suspend OPP */
			अगर (new_opp->rate > opp_table->suspend_opp->rate) अणु
				opp_table->suspend_opp->suspend = false;
				new_opp->suspend = true;
				opp_table->suspend_opp = new_opp;
			पूर्ण
		पूर्ण अन्यथा अणु
			new_opp->suspend = true;
			opp_table->suspend_opp = new_opp;
		पूर्ण
	पूर्ण

	अगर (new_opp->घड़ी_latency_ns > opp_table->घड़ी_latency_ns_max)
		opp_table->घड़ी_latency_ns_max = new_opp->घड़ी_latency_ns;

	pr_debug("%s: turbo:%d rate:%lu uv:%lu uvmin:%lu uvmax:%lu latency:%lu level:%u\n",
		 __func__, new_opp->turbo, new_opp->rate,
		 new_opp->supplies[0].u_volt, new_opp->supplies[0].u_volt_min,
		 new_opp->supplies[0].u_volt_max, new_opp->घड़ी_latency_ns,
		 new_opp->level);

	/*
	 * Notअगरy the changes in the availability of the operable
	 * frequency/voltage list.
	 */
	blocking_notअगरier_call_chain(&opp_table->head, OPP_EVENT_ADD, new_opp);
	वापस new_opp;

मुक्त_required_opps:
	_of_opp_मुक्त_required_opps(opp_table, new_opp);
मुक्त_opp:
	_opp_मुक्त(new_opp);

	वापस ERR_PTR(ret);
पूर्ण

/* Initializes OPP tables based on new bindings */
अटल पूर्णांक _of_add_opp_table_v2(काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret, count = 0;
	काष्ठा dev_pm_opp *opp;

	/* OPP table is alपढ़ोy initialized क्रम the device */
	mutex_lock(&opp_table->lock);
	अगर (opp_table->parsed_अटल_opps) अणु
		opp_table->parsed_अटल_opps++;
		mutex_unlock(&opp_table->lock);
		वापस 0;
	पूर्ण

	opp_table->parsed_अटल_opps = 1;
	mutex_unlock(&opp_table->lock);

	/* We have opp-table node now, iterate over it and add OPPs */
	क्रम_each_available_child_of_node(opp_table->np, np) अणु
		opp = _opp_add_अटल_v2(opp_table, dev, np);
		अगर (IS_ERR(opp)) अणु
			ret = PTR_ERR(opp);
			dev_err(dev, "%s: Failed to add OPP, %d\n", __func__,
				ret);
			of_node_put(np);
			जाओ हटाओ_अटल_opp;
		पूर्ण अन्यथा अगर (opp) अणु
			count++;
		पूर्ण
	पूर्ण

	/* There should be one of more OPP defined */
	अगर (WARN_ON(!count)) अणु
		ret = -ENOENT;
		जाओ हटाओ_अटल_opp;
	पूर्ण

	list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
		/* Any non-zero perक्रमmance state would enable the feature */
		अगर (opp->pstate) अणु
			opp_table->genpd_perक्रमmance_state = true;
			अवरोध;
		पूर्ण
	पूर्ण

	lazy_link_required_opp_table(opp_table);

	वापस 0;

हटाओ_अटल_opp:
	_opp_हटाओ_all_अटल(opp_table);

	वापस ret;
पूर्ण

/* Initializes OPP tables based on old-deprecated bindings */
अटल पूर्णांक _of_add_opp_table_v1(काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	स्थिर काष्ठा property *prop;
	स्थिर __be32 *val;
	पूर्णांक nr, ret = 0;

	mutex_lock(&opp_table->lock);
	अगर (opp_table->parsed_अटल_opps) अणु
		opp_table->parsed_अटल_opps++;
		mutex_unlock(&opp_table->lock);
		वापस 0;
	पूर्ण

	opp_table->parsed_अटल_opps = 1;
	mutex_unlock(&opp_table->lock);

	prop = of_find_property(dev->of_node, "operating-points", शून्य);
	अगर (!prop) अणु
		ret = -ENODEV;
		जाओ हटाओ_अटल_opp;
	पूर्ण
	अगर (!prop->value) अणु
		ret = -ENODATA;
		जाओ हटाओ_अटल_opp;
	पूर्ण

	/*
	 * Each OPP is a set of tuples consisting of frequency and
	 * voltage like <freq-kHz vol-uV>.
	 */
	nr = prop->length / माप(u32);
	अगर (nr % 2) अणु
		dev_err(dev, "%s: Invalid OPP table\n", __func__);
		ret = -EINVAL;
		जाओ हटाओ_अटल_opp;
	पूर्ण

	val = prop->value;
	जबतक (nr) अणु
		अचिन्हित दीर्घ freq = be32_to_cpup(val++) * 1000;
		अचिन्हित दीर्घ volt = be32_to_cpup(val++);

		ret = _opp_add_v1(opp_table, dev, freq, volt, false);
		अगर (ret) अणु
			dev_err(dev, "%s: Failed to add OPP %ld (%d)\n",
				__func__, freq, ret);
			जाओ हटाओ_अटल_opp;
		पूर्ण
		nr -= 2;
	पूर्ण

	वापस 0;

हटाओ_अटल_opp:
	_opp_हटाओ_all_अटल(opp_table);

	वापस ret;
पूर्ण

अटल पूर्णांक _of_add_table_indexed(काष्ठा device *dev, पूर्णांक index, bool अ_लोlk)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक ret, count;

	अगर (index) अणु
		/*
		 * If only one phandle is present, then the same OPP table
		 * applies क्रम all index requests.
		 */
		count = of_count_phandle_with_args(dev->of_node,
						   "operating-points-v2", शून्य);
		अगर (count == 1)
			index = 0;
	पूर्ण

	opp_table = _add_opp_table_indexed(dev, index, अ_लोlk);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	/*
	 * OPPs have two version of bindings now. Also try the old (v1)
	 * bindings क्रम backward compatibility with older dtbs.
	 */
	अगर (opp_table->np)
		ret = _of_add_opp_table_v2(dev, opp_table);
	अन्यथा
		ret = _of_add_opp_table_v1(dev, opp_table);

	अगर (ret)
		dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण

अटल व्योम devm_pm_opp_of_table_release(व्योम *data)
अणु
	dev_pm_opp_of_हटाओ_table(data);
पूर्ण

/**
 * devm_pm_opp_of_add_table() - Initialize opp table from device tree
 * @dev:	device poपूर्णांकer used to lookup OPP table.
 *
 * Register the initial OPP table with the OPP library क्रम given device.
 *
 * The opp_table काष्ठाure will be मुक्तd after the device is destroyed.
 *
 * Return:
 * 0		On success OR
 *		Duplicate OPPs (both freq and volt are same) and opp->available
 * -EEXIST	Freq are same and volt are dअगरferent OR
 *		Duplicate OPPs (both freq and volt are same) and !opp->available
 * -ENOMEM	Memory allocation failure
 * -ENODEV	when 'operating-points' property is not found or is invalid data
 *		in device node.
 * -ENODATA	when empty 'operating-points' property is found
 * -EINVAL	when invalid entries are found in opp-v2 table
 */
पूर्णांक devm_pm_opp_of_add_table(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = dev_pm_opp_of_add_table(dev);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, devm_pm_opp_of_table_release, dev);
पूर्ण
EXPORT_SYMBOL_GPL(devm_pm_opp_of_add_table);

/**
 * dev_pm_opp_of_add_table() - Initialize opp table from device tree
 * @dev:	device poपूर्णांकer used to lookup OPP table.
 *
 * Register the initial OPP table with the OPP library क्रम given device.
 *
 * Return:
 * 0		On success OR
 *		Duplicate OPPs (both freq and volt are same) and opp->available
 * -EEXIST	Freq are same and volt are dअगरferent OR
 *		Duplicate OPPs (both freq and volt are same) and !opp->available
 * -ENOMEM	Memory allocation failure
 * -ENODEV	when 'operating-points' property is not found or is invalid data
 *		in device node.
 * -ENODATA	when empty 'operating-points' property is found
 * -EINVAL	when invalid entries are found in opp-v2 table
 */
पूर्णांक dev_pm_opp_of_add_table(काष्ठा device *dev)
अणु
	वापस _of_add_table_indexed(dev, 0, true);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_add_table);

/**
 * dev_pm_opp_of_add_table_indexed() - Initialize indexed opp table from device tree
 * @dev:	device poपूर्णांकer used to lookup OPP table.
 * @index:	Index number.
 *
 * Register the initial OPP table with the OPP library क्रम given device only
 * using the "operating-points-v2" property.
 *
 * Return: Refer to dev_pm_opp_of_add_table() क्रम वापस values.
 */
पूर्णांक dev_pm_opp_of_add_table_indexed(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस _of_add_table_indexed(dev, index, true);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_add_table_indexed);

/**
 * dev_pm_opp_of_add_table_noclk() - Initialize indexed opp table from device
 *		tree without getting clk क्रम device.
 * @dev:	device poपूर्णांकer used to lookup OPP table.
 * @index:	Index number.
 *
 * Register the initial OPP table with the OPP library क्रम given device only
 * using the "operating-points-v2" property. Do not try to get the clk क्रम the
 * device.
 *
 * Return: Refer to dev_pm_opp_of_add_table() क्रम वापस values.
 */
पूर्णांक dev_pm_opp_of_add_table_noclk(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस _of_add_table_indexed(dev, index, false);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_add_table_noclk);

/* CPU device specअगरic helpers */

/**
 * dev_pm_opp_of_cpumask_हटाओ_table() - Removes OPP table क्रम @cpumask
 * @cpumask:	cpumask क्रम which OPP table needs to be हटाओd
 *
 * This हटाओs the OPP tables क्रम CPUs present in the @cpumask.
 * This should be used only to हटाओ अटल entries created from DT.
 */
व्योम dev_pm_opp_of_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask)
अणु
	_dev_pm_opp_cpumask_हटाओ_table(cpumask, -1);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_cpumask_हटाओ_table);

/**
 * dev_pm_opp_of_cpumask_add_table() - Adds OPP table क्रम @cpumask
 * @cpumask:	cpumask क्रम which OPP table needs to be added.
 *
 * This adds the OPP tables क्रम CPUs present in the @cpumask.
 */
पूर्णांक dev_pm_opp_of_cpumask_add_table(स्थिर काष्ठा cpumask *cpumask)
अणु
	काष्ठा device *cpu_dev;
	पूर्णांक cpu, ret;

	अगर (WARN_ON(cpumask_empty(cpumask)))
		वापस -ENODEV;

	क्रम_each_cpu(cpu, cpumask) अणु
		cpu_dev = get_cpu_device(cpu);
		अगर (!cpu_dev) अणु
			pr_err("%s: failed to get cpu%d device\n", __func__,
			       cpu);
			ret = -ENODEV;
			जाओ हटाओ_table;
		पूर्ण

		ret = dev_pm_opp_of_add_table(cpu_dev);
		अगर (ret) अणु
			/*
			 * OPP may get रेजिस्टरed dynamically, करोn't prपूर्णांक error
			 * message here.
			 */
			pr_debug("%s: couldn't find opp table for cpu:%d, %d\n",
				 __func__, cpu, ret);

			जाओ हटाओ_table;
		पूर्ण
	पूर्ण

	वापस 0;

हटाओ_table:
	/* Free all other OPPs */
	_dev_pm_opp_cpumask_हटाओ_table(cpumask, cpu);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_cpumask_add_table);

/*
 * Works only क्रम OPP v2 bindings.
 *
 * Returns -ENOENT अगर operating-poपूर्णांकs-v2 bindings aren't supported.
 */
/**
 * dev_pm_opp_of_get_sharing_cpus() - Get cpumask of CPUs sharing OPPs with
 *				      @cpu_dev using operating-poपूर्णांकs-v2
 *				      bindings.
 *
 * @cpu_dev:	CPU device क्रम which we करो this operation
 * @cpumask:	cpumask to update with inक्रमmation of sharing CPUs
 *
 * This updates the @cpumask with CPUs that are sharing OPPs with @cpu_dev.
 *
 * Returns -ENOENT अगर operating-poपूर्णांकs-v2 isn't present क्रम @cpu_dev.
 */
पूर्णांक dev_pm_opp_of_get_sharing_cpus(काष्ठा device *cpu_dev,
				   काष्ठा cpumask *cpumask)
अणु
	काष्ठा device_node *np, *पंचांगp_np, *cpu_np;
	पूर्णांक cpu, ret = 0;

	/* Get OPP descriptor node */
	np = dev_pm_opp_of_get_opp_desc_node(cpu_dev);
	अगर (!np) अणु
		dev_dbg(cpu_dev, "%s: Couldn't find opp node.\n", __func__);
		वापस -ENOENT;
	पूर्ण

	cpumask_set_cpu(cpu_dev->id, cpumask);

	/* OPPs are shared ? */
	अगर (!of_property_पढ़ो_bool(np, "opp-shared"))
		जाओ put_cpu_node;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == cpu_dev->id)
			जारी;

		cpu_np = of_cpu_device_node_get(cpu);
		अगर (!cpu_np) अणु
			dev_err(cpu_dev, "%s: failed to get cpu%d node\n",
				__func__, cpu);
			ret = -ENOENT;
			जाओ put_cpu_node;
		पूर्ण

		/* Get OPP descriptor node */
		पंचांगp_np = _opp_of_get_opp_desc_node(cpu_np, 0);
		of_node_put(cpu_np);
		अगर (!पंचांगp_np) अणु
			pr_err("%pOF: Couldn't find opp node\n", cpu_np);
			ret = -ENOENT;
			जाओ put_cpu_node;
		पूर्ण

		/* CPUs are sharing opp node */
		अगर (np == पंचांगp_np)
			cpumask_set_cpu(cpu, cpumask);

		of_node_put(पंचांगp_np);
	पूर्ण

put_cpu_node:
	of_node_put(np);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_get_sharing_cpus);

/**
 * of_get_required_opp_perक्रमmance_state() - Search क्रम required OPP and वापस its perक्रमmance state.
 * @np: Node that contains the "required-opps" property.
 * @index: Index of the phandle to parse.
 *
 * Returns the perक्रमmance state of the OPP poपूर्णांकed out by the "required-opps"
 * property at @index in @np.
 *
 * Return: Zero or positive perक्रमmance state on success, otherwise negative
 * value on errors.
 */
पूर्णांक of_get_required_opp_perक्रमmance_state(काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा dev_pm_opp *opp;
	काष्ठा device_node *required_np;
	काष्ठा opp_table *opp_table;
	पूर्णांक pstate = -EINVAL;

	required_np = of_parse_required_opp(np, index);
	अगर (!required_np)
		वापस -EINVAL;

	opp_table = _find_table_of_opp_np(required_np);
	अगर (IS_ERR(opp_table)) अणु
		pr_err("%s: Failed to find required OPP table %pOF: %ld\n",
		       __func__, np, PTR_ERR(opp_table));
		जाओ put_required_np;
	पूर्ण

	opp = _find_opp_of_np(opp_table, required_np);
	अगर (opp) अणु
		pstate = opp->pstate;
		dev_pm_opp_put(opp);
	पूर्ण

	dev_pm_opp_put_opp_table(opp_table);

put_required_np:
	of_node_put(required_np);

	वापस pstate;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_required_opp_perक्रमmance_state);

/**
 * dev_pm_opp_get_of_node() - Gets the DT node corresponding to an opp
 * @opp:	opp क्रम which DT node has to be वापसed क्रम
 *
 * Return: DT node corresponding to the opp, अन्यथा 0 on success.
 *
 * The caller needs to put the node with of_node_put() after using it.
 */
काष्ठा device_node *dev_pm_opp_get_of_node(काष्ठा dev_pm_opp *opp)
अणु
	अगर (IS_ERR_OR_शून्य(opp)) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस शून्य;
	पूर्ण

	वापस of_node_get(opp->np);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_of_node);

/*
 * Callback function provided to the Energy Model framework upon registration.
 * This computes the घातer estimated by @dev at @kHz अगर it is the frequency
 * of an existing OPP, or at the frequency of the first OPP above @kHz otherwise
 * (see dev_pm_opp_find_freq_उच्चमान()). This function updates @kHz to the उच्चमानed
 * frequency and @mW to the associated घातer. The घातer is estimated as
 * P = C * V^2 * f with C being the device's capacitance and V and f
 * respectively the voltage and frequency of the OPP.
 *
 * Returns -EINVAL अगर the घातer calculation failed because of missing
 * parameters, 0 otherwise.
 */
अटल पूर्णांक __maybe_unused _get_घातer(अचिन्हित दीर्घ *mW, अचिन्हित दीर्घ *kHz,
				     काष्ठा device *dev)
अणु
	काष्ठा dev_pm_opp *opp;
	काष्ठा device_node *np;
	अचिन्हित दीर्घ mV, Hz;
	u32 cap;
	u64 पंचांगp;
	पूर्णांक ret;

	np = of_node_get(dev->of_node);
	अगर (!np)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32(np, "dynamic-power-coefficient", &cap);
	of_node_put(np);
	अगर (ret)
		वापस -EINVAL;

	Hz = *kHz * 1000;
	opp = dev_pm_opp_find_freq_उच्चमान(dev, &Hz);
	अगर (IS_ERR(opp))
		वापस -EINVAL;

	mV = dev_pm_opp_get_voltage(opp) / 1000;
	dev_pm_opp_put(opp);
	अगर (!mV)
		वापस -EINVAL;

	पंचांगp = (u64)cap * mV * mV * (Hz / 1000000);
	करो_भाग(पंचांगp, 1000000000);

	*mW = (अचिन्हित दीर्घ)पंचांगp;
	*kHz = Hz / 1000;

	वापस 0;
पूर्ण

/**
 * dev_pm_opp_of_रेजिस्टर_em() - Attempt to रेजिस्टर an Energy Model
 * @dev		: Device क्रम which an Energy Model has to be रेजिस्टरed
 * @cpus	: CPUs क्रम which an Energy Model has to be रेजिस्टरed. For
 *		other type of devices it should be set to शून्य.
 *
 * This checks whether the "dynamic-power-coefficient" devicetree property has
 * been specअगरied, and tries to रेजिस्टर an Energy Model with it अगर it has.
 * Having this property means the voltages are known क्रम OPPs and the EM
 * might be calculated.
 */
पूर्णांक dev_pm_opp_of_रेजिस्टर_em(काष्ठा device *dev, काष्ठा cpumask *cpus)
अणु
	काष्ठा em_data_callback em_cb = EM_DATA_CB(_get_घातer);
	काष्ठा device_node *np;
	पूर्णांक ret, nr_opp;
	u32 cap;

	अगर (IS_ERR_OR_शून्य(dev)) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	nr_opp = dev_pm_opp_get_opp_count(dev);
	अगर (nr_opp <= 0) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	np = of_node_get(dev->of_node);
	अगर (!np) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	/*
	 * Register an EM only अगर the 'dynamic-power-coefficient' property is
	 * set in devicetree. It is assumed the voltage values are known अगर that
	 * property is set since it is useless otherwise. If voltages are not
	 * known, just let the EM registration fail with an error to alert the
	 * user about the inconsistent configuration.
	 */
	ret = of_property_पढ़ो_u32(np, "dynamic-power-coefficient", &cap);
	of_node_put(np);
	अगर (ret || !cap) अणु
		dev_dbg(dev, "Couldn't find proper 'dynamic-power-coefficient' in DT\n");
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	ret = em_dev_रेजिस्टर_perf_करोमुख्य(dev, nr_opp, &em_cb, cpus, true);
	अगर (ret)
		जाओ failed;

	वापस 0;

failed:
	dev_dbg(dev, "Couldn't register Energy Model %d\n", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_of_रेजिस्टर_em);
