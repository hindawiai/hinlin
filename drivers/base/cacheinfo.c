<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cacheinfo support - processor cache inक्रमmation via sysfs
 *
 * Based on arch/x86/kernel/cpu/पूर्णांकel_cacheinfo.c
 * Author: Sudeep Holla <sudeep.holla@arm.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cacheinfo.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/sysfs.h>

/* poपूर्णांकer to per cpu cacheinfo */
अटल DEFINE_PER_CPU(काष्ठा cpu_cacheinfo, ci_cpu_cacheinfo);
#घोषणा ci_cacheinfo(cpu)	(&per_cpu(ci_cpu_cacheinfo, cpu))
#घोषणा cache_leaves(cpu)	(ci_cacheinfo(cpu)->num_leaves)
#घोषणा per_cpu_cacheinfo(cpu)	(ci_cacheinfo(cpu)->info_list)

काष्ठा cpu_cacheinfo *get_cpu_cacheinfo(अचिन्हित पूर्णांक cpu)
अणु
	वापस ci_cacheinfo(cpu);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल अंतरभूत bool cache_leaves_are_shared(काष्ठा cacheinfo *this_leaf,
					   काष्ठा cacheinfo *sib_leaf)
अणु
	वापस sib_leaf->fw_token == this_leaf->fw_token;
पूर्ण

/* OF properties to query क्रम a given cache type */
काष्ठा cache_type_info अणु
	स्थिर अक्षर *size_prop;
	स्थिर अक्षर *line_size_props[2];
	स्थिर अक्षर *nr_sets_prop;
पूर्ण;

अटल स्थिर काष्ठा cache_type_info cache_type_info[] = अणु
	अणु
		.size_prop       = "cache-size",
		.line_size_props = अणु "cache-line-size",
				     "cache-block-size", पूर्ण,
		.nr_sets_prop    = "cache-sets",
	पूर्ण, अणु
		.size_prop       = "i-cache-size",
		.line_size_props = अणु "i-cache-line-size",
				     "i-cache-block-size", पूर्ण,
		.nr_sets_prop    = "i-cache-sets",
	पूर्ण, अणु
		.size_prop       = "d-cache-size",
		.line_size_props = अणु "d-cache-line-size",
				     "d-cache-block-size", पूर्ण,
		.nr_sets_prop    = "d-cache-sets",
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक get_cacheinfo_idx(क्रमागत cache_type type)
अणु
	अगर (type == CACHE_TYPE_UNIFIED)
		वापस 0;
	वापस type;
पूर्ण

अटल व्योम cache_size(काष्ठा cacheinfo *this_leaf, काष्ठा device_node *np)
अणु
	स्थिर अक्षर *propname;
	पूर्णांक ct_idx;

	ct_idx = get_cacheinfo_idx(this_leaf->type);
	propname = cache_type_info[ct_idx].size_prop;

	of_property_पढ़ो_u32(np, propname, &this_leaf->size);
पूर्ण

/* not cache_line_size() because that's a macro in include/linux/cache.h */
अटल व्योम cache_get_line_size(काष्ठा cacheinfo *this_leaf,
				काष्ठा device_node *np)
अणु
	पूर्णांक i, lim, ct_idx;

	ct_idx = get_cacheinfo_idx(this_leaf->type);
	lim = ARRAY_SIZE(cache_type_info[ct_idx].line_size_props);

	क्रम (i = 0; i < lim; i++) अणु
		पूर्णांक ret;
		u32 line_size;
		स्थिर अक्षर *propname;

		propname = cache_type_info[ct_idx].line_size_props[i];
		ret = of_property_पढ़ो_u32(np, propname, &line_size);
		अगर (!ret) अणु
			this_leaf->coherency_line_size = line_size;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cache_nr_sets(काष्ठा cacheinfo *this_leaf, काष्ठा device_node *np)
अणु
	स्थिर अक्षर *propname;
	पूर्णांक ct_idx;

	ct_idx = get_cacheinfo_idx(this_leaf->type);
	propname = cache_type_info[ct_idx].nr_sets_prop;

	of_property_पढ़ो_u32(np, propname, &this_leaf->number_of_sets);
पूर्ण

अटल व्योम cache_associativity(काष्ठा cacheinfo *this_leaf)
अणु
	अचिन्हित पूर्णांक line_size = this_leaf->coherency_line_size;
	अचिन्हित पूर्णांक nr_sets = this_leaf->number_of_sets;
	अचिन्हित पूर्णांक size = this_leaf->size;

	/*
	 * If the cache is fully associative, there is no need to
	 * check the other properties.
	 */
	अगर (!(nr_sets == 1) && (nr_sets > 0 && size > 0 && line_size > 0))
		this_leaf->ways_of_associativity = (size / nr_sets) / line_size;
पूर्ण

अटल bool cache_node_is_unअगरied(काष्ठा cacheinfo *this_leaf,
				  काष्ठा device_node *np)
अणु
	वापस of_property_पढ़ो_bool(np, "cache-unified");
पूर्ण

अटल व्योम cache_of_set_props(काष्ठा cacheinfo *this_leaf,
			       काष्ठा device_node *np)
अणु
	/*
	 * init_cache_level must setup the cache level correctly
	 * overriding the architecturally specअगरied levels, so
	 * अगर type is NONE at this stage, it should be unअगरied
	 */
	अगर (this_leaf->type == CACHE_TYPE_NOCACHE &&
	    cache_node_is_unअगरied(this_leaf, np))
		this_leaf->type = CACHE_TYPE_UNIFIED;
	cache_size(this_leaf, np);
	cache_get_line_size(this_leaf, np);
	cache_nr_sets(this_leaf, np);
	cache_associativity(this_leaf);
पूर्ण

अटल पूर्णांक cache_setup_of_node(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device_node *np;
	काष्ठा cacheinfo *this_leaf;
	काष्ठा device *cpu_dev = get_cpu_device(cpu);
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	अचिन्हित पूर्णांक index = 0;

	/* skip अगर fw_token is alपढ़ोy populated */
	अगर (this_cpu_ci->info_list->fw_token) अणु
		वापस 0;
	पूर्ण

	अगर (!cpu_dev) अणु
		pr_err("No cpu device for CPU %d\n", cpu);
		वापस -ENODEV;
	पूर्ण
	np = cpu_dev->of_node;
	अगर (!np) अणु
		pr_err("Failed to find cpu%d device node\n", cpu);
		वापस -ENOENT;
	पूर्ण

	जबतक (index < cache_leaves(cpu)) अणु
		this_leaf = this_cpu_ci->info_list + index;
		अगर (this_leaf->level != 1)
			np = of_find_next_cache_node(np);
		अन्यथा
			np = of_node_get(np);/* cpu node itself */
		अगर (!np)
			अवरोध;
		cache_of_set_props(this_leaf, np);
		this_leaf->fw_token = np;
		index++;
	पूर्ण

	अगर (index != cache_leaves(cpu)) /* not all OF nodes populated */
		वापस -ENOENT;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cache_setup_of_node(अचिन्हित पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत bool cache_leaves_are_shared(काष्ठा cacheinfo *this_leaf,
					   काष्ठा cacheinfo *sib_leaf)
अणु
	/*
	 * For non-DT/ACPI प्रणालीs, assume unique level 1 caches, प्रणाली-wide
	 * shared caches क्रम all other levels. This will be used only अगर
	 * arch specअगरic code has not populated shared_cpu_map
	 */
	वापस !(this_leaf->level == 1);
पूर्ण
#पूर्ण_अगर

पूर्णांक __weak cache_setup_acpi(अचिन्हित पूर्णांक cpu)
अणु
	वापस -ENOTSUPP;
पूर्ण

अचिन्हित पूर्णांक coherency_max_size;

अटल पूर्णांक cache_shared_cpu_map_setup(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf, *sib_leaf;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret = 0;

	अगर (this_cpu_ci->cpu_map_populated)
		वापस 0;

	अगर (of_have_populated_dt())
		ret = cache_setup_of_node(cpu);
	अन्यथा अगर (!acpi_disabled)
		ret = cache_setup_acpi(cpu);

	अगर (ret)
		वापस ret;

	क्रम (index = 0; index < cache_leaves(cpu); index++) अणु
		अचिन्हित पूर्णांक i;

		this_leaf = this_cpu_ci->info_list + index;
		/* skip अगर shared_cpu_map is alपढ़ोy populated */
		अगर (!cpumask_empty(&this_leaf->shared_cpu_map))
			जारी;

		cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
		क्रम_each_online_cpu(i) अणु
			काष्ठा cpu_cacheinfo *sib_cpu_ci = get_cpu_cacheinfo(i);

			अगर (i == cpu || !sib_cpu_ci->info_list)
				जारी;/* skip अगर itself or no cacheinfo */
			sib_leaf = sib_cpu_ci->info_list + index;
			अगर (cache_leaves_are_shared(this_leaf, sib_leaf)) अणु
				cpumask_set_cpu(cpu, &sib_leaf->shared_cpu_map);
				cpumask_set_cpu(i, &this_leaf->shared_cpu_map);
			पूर्ण
		पूर्ण
		/* record the maximum cache line size */
		अगर (this_leaf->coherency_line_size > coherency_max_size)
			coherency_max_size = this_leaf->coherency_line_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cache_shared_cpu_map_हटाओ(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf, *sib_leaf;
	अचिन्हित पूर्णांक sibling, index;

	क्रम (index = 0; index < cache_leaves(cpu); index++) अणु
		this_leaf = this_cpu_ci->info_list + index;
		क्रम_each_cpu(sibling, &this_leaf->shared_cpu_map) अणु
			काष्ठा cpu_cacheinfo *sib_cpu_ci;

			अगर (sibling == cpu) /* skip itself */
				जारी;

			sib_cpu_ci = get_cpu_cacheinfo(sibling);
			अगर (!sib_cpu_ci->info_list)
				जारी;

			sib_leaf = sib_cpu_ci->info_list + index;
			cpumask_clear_cpu(cpu, &sib_leaf->shared_cpu_map);
			cpumask_clear_cpu(sibling, &this_leaf->shared_cpu_map);
		पूर्ण
		अगर (of_have_populated_dt())
			of_node_put(this_leaf->fw_token);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_cache_attributes(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!per_cpu_cacheinfo(cpu))
		वापस;

	cache_shared_cpu_map_हटाओ(cpu);

	kमुक्त(per_cpu_cacheinfo(cpu));
	per_cpu_cacheinfo(cpu) = शून्य;
पूर्ण

पूर्णांक __weak init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	वापस -ENOENT;
पूर्ण

पूर्णांक __weak populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक detect_cache_attributes(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret;

	अगर (init_cache_level(cpu) || !cache_leaves(cpu))
		वापस -ENOENT;

	per_cpu_cacheinfo(cpu) = kसुस्मृति(cache_leaves(cpu),
					 माप(काष्ठा cacheinfo), GFP_KERNEL);
	अगर (per_cpu_cacheinfo(cpu) == शून्य)
		वापस -ENOMEM;

	/*
	 * populate_cache_leaves() may completely setup the cache leaves and
	 * shared_cpu_map or it may leave it partially setup.
	 */
	ret = populate_cache_leaves(cpu);
	अगर (ret)
		जाओ मुक्त_ci;
	/*
	 * For प्रणालीs using DT क्रम cache hierarchy, fw_token
	 * and shared_cpu_map will be set up here only अगर they are
	 * not populated alपढ़ोy
	 */
	ret = cache_shared_cpu_map_setup(cpu);
	अगर (ret) अणु
		pr_warn("Unable to detect cache hierarchy for CPU %d\n", cpu);
		जाओ मुक्त_ci;
	पूर्ण

	वापस 0;

मुक्त_ci:
	मुक्त_cache_attributes(cpu);
	वापस ret;
पूर्ण

/* poपूर्णांकer to cpuX/cache device */
अटल DEFINE_PER_CPU(काष्ठा device *, ci_cache_dev);
#घोषणा per_cpu_cache_dev(cpu)	(per_cpu(ci_cache_dev, cpu))

अटल cpumask_t cache_dev_map;

/* poपूर्णांकer to array of devices क्रम cpuX/cache/indexY */
अटल DEFINE_PER_CPU(काष्ठा device **, ci_index_dev);
#घोषणा per_cpu_index_dev(cpu)	(per_cpu(ci_index_dev, cpu))
#घोषणा per_cache_index_dev(cpu, idx)	((per_cpu_index_dev(cpu))[idx])

#घोषणा show_one(file_name, object)				\
अटल sमाप_प्रकार file_name##_show(काष्ठा device *dev,		\
		काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु								\
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);	\
	वापस sysfs_emit(buf, "%u\n", this_leaf->object);	\
पूर्ण

show_one(id, id);
show_one(level, level);
show_one(coherency_line_size, coherency_line_size);
show_one(number_of_sets, number_of_sets);
show_one(physical_line_partition, physical_line_partition);
show_one(ways_of_associativity, ways_of_associativity);

अटल sमाप_प्रकार size_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%uK\n", this_leaf->size >> 10);
पूर्ण

अटल sमाप_प्रकार shared_cpu_map_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	स्थिर काष्ठा cpumask *mask = &this_leaf->shared_cpu_map;

	वापस sysfs_emit(buf, "%*pb\n", nr_cpu_ids, mask);
पूर्ण

अटल sमाप_प्रकार shared_cpu_list_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	स्थिर काष्ठा cpumask *mask = &this_leaf->shared_cpu_map;

	वापस sysfs_emit(buf, "%*pbl\n", nr_cpu_ids, mask);
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	स्थिर अक्षर *output;

	चयन (this_leaf->type) अणु
	हाल CACHE_TYPE_DATA:
		output = "Data";
		अवरोध;
	हाल CACHE_TYPE_INST:
		output = "Instruction";
		अवरोध;
	हाल CACHE_TYPE_UNIFIED:
		output = "Unified";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल sमाप_प्रकार allocation_policy_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ci_attr = this_leaf->attributes;
	स्थिर अक्षर *output;

	अगर ((ci_attr & CACHE_READ_ALLOCATE) && (ci_attr & CACHE_WRITE_ALLOCATE))
		output = "ReadWriteAllocate";
	अन्यथा अगर (ci_attr & CACHE_READ_ALLOCATE)
		output = "ReadAllocate";
	अन्यथा अगर (ci_attr & CACHE_WRITE_ALLOCATE)
		output = "WriteAllocate";
	अन्यथा
		वापस 0;

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_policy_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ci_attr = this_leaf->attributes;
	पूर्णांक n = 0;

	अगर (ci_attr & CACHE_WRITE_THROUGH)
		n = sysfs_emit(buf, "WriteThrough\n");
	अन्यथा अगर (ci_attr & CACHE_WRITE_BACK)
		n = sysfs_emit(buf, "WriteBack\n");
	वापस n;
पूर्ण

अटल DEVICE_ATTR_RO(id);
अटल DEVICE_ATTR_RO(level);
अटल DEVICE_ATTR_RO(type);
अटल DEVICE_ATTR_RO(coherency_line_size);
अटल DEVICE_ATTR_RO(ways_of_associativity);
अटल DEVICE_ATTR_RO(number_of_sets);
अटल DEVICE_ATTR_RO(size);
अटल DEVICE_ATTR_RO(allocation_policy);
अटल DEVICE_ATTR_RO(ग_लिखो_policy);
अटल DEVICE_ATTR_RO(shared_cpu_map);
अटल DEVICE_ATTR_RO(shared_cpu_list);
अटल DEVICE_ATTR_RO(physical_line_partition);

अटल काष्ठा attribute *cache_शेष_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_type.attr,
	&dev_attr_level.attr,
	&dev_attr_shared_cpu_map.attr,
	&dev_attr_shared_cpu_list.attr,
	&dev_attr_coherency_line_size.attr,
	&dev_attr_ways_of_associativity.attr,
	&dev_attr_number_of_sets.attr,
	&dev_attr_size.attr,
	&dev_attr_allocation_policy.attr,
	&dev_attr_ग_लिखो_policy.attr,
	&dev_attr_physical_line_partition.attr,
	शून्य
पूर्ण;

अटल umode_t
cache_शेष_attrs_is_visible(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr, पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	स्थिर काष्ठा cpumask *mask = &this_leaf->shared_cpu_map;
	umode_t mode = attr->mode;

	अगर ((attr == &dev_attr_id.attr) && (this_leaf->attributes & CACHE_ID))
		वापस mode;
	अगर ((attr == &dev_attr_type.attr) && this_leaf->type)
		वापस mode;
	अगर ((attr == &dev_attr_level.attr) && this_leaf->level)
		वापस mode;
	अगर ((attr == &dev_attr_shared_cpu_map.attr) && !cpumask_empty(mask))
		वापस mode;
	अगर ((attr == &dev_attr_shared_cpu_list.attr) && !cpumask_empty(mask))
		वापस mode;
	अगर ((attr == &dev_attr_coherency_line_size.attr) &&
	    this_leaf->coherency_line_size)
		वापस mode;
	अगर ((attr == &dev_attr_ways_of_associativity.attr) &&
	    this_leaf->size) /* allow 0 = full associativity */
		वापस mode;
	अगर ((attr == &dev_attr_number_of_sets.attr) &&
	    this_leaf->number_of_sets)
		वापस mode;
	अगर ((attr == &dev_attr_size.attr) && this_leaf->size)
		वापस mode;
	अगर ((attr == &dev_attr_ग_लिखो_policy.attr) &&
	    (this_leaf->attributes & CACHE_WRITE_POLICY_MASK))
		वापस mode;
	अगर ((attr == &dev_attr_allocation_policy.attr) &&
	    (this_leaf->attributes & CACHE_ALLOCATE_POLICY_MASK))
		वापस mode;
	अगर ((attr == &dev_attr_physical_line_partition.attr) &&
	    this_leaf->physical_line_partition)
		वापस mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group cache_शेष_group = अणु
	.attrs = cache_शेष_attrs,
	.is_visible = cache_शेष_attrs_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cache_शेष_groups[] = अणु
	&cache_शेष_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cache_निजी_groups[] = अणु
	&cache_शेष_group,
	शून्य, /* Place holder क्रम निजी group */
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group *
__weak cache_get_priv_group(काष्ठा cacheinfo *this_leaf)
अणु
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा attribute_group **
cache_get_attribute_groups(काष्ठा cacheinfo *this_leaf)
अणु
	स्थिर काष्ठा attribute_group *priv_group =
			cache_get_priv_group(this_leaf);

	अगर (!priv_group)
		वापस cache_शेष_groups;

	अगर (!cache_निजी_groups[1])
		cache_निजी_groups[1] = priv_group;

	वापस cache_निजी_groups;
पूर्ण

/* Add/Remove cache पूर्णांकerface क्रम CPU device */
अटल व्योम cpu_cache_sysfs_निकास(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;
	काष्ठा device *ci_dev;

	अगर (per_cpu_index_dev(cpu)) अणु
		क्रम (i = 0; i < cache_leaves(cpu); i++) अणु
			ci_dev = per_cache_index_dev(cpu, i);
			अगर (!ci_dev)
				जारी;
			device_unरेजिस्टर(ci_dev);
		पूर्ण
		kमुक्त(per_cpu_index_dev(cpu));
		per_cpu_index_dev(cpu) = शून्य;
	पूर्ण
	device_unरेजिस्टर(per_cpu_cache_dev(cpu));
	per_cpu_cache_dev(cpu) = शून्य;
पूर्ण

अटल पूर्णांक cpu_cache_sysfs_init(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	अगर (per_cpu_cacheinfo(cpu) == शून्य)
		वापस -ENOENT;

	per_cpu_cache_dev(cpu) = cpu_device_create(dev, शून्य, शून्य, "cache");
	अगर (IS_ERR(per_cpu_cache_dev(cpu)))
		वापस PTR_ERR(per_cpu_cache_dev(cpu));

	/* Allocate all required memory */
	per_cpu_index_dev(cpu) = kसुस्मृति(cache_leaves(cpu),
					 माप(काष्ठा device *), GFP_KERNEL);
	अगर (unlikely(per_cpu_index_dev(cpu) == शून्य))
		जाओ err_out;

	वापस 0;

err_out:
	cpu_cache_sysfs_निकास(cpu);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cache_add_dev(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;
	काष्ठा device *ci_dev, *parent;
	काष्ठा cacheinfo *this_leaf;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	स्थिर काष्ठा attribute_group **cache_groups;

	rc = cpu_cache_sysfs_init(cpu);
	अगर (unlikely(rc < 0))
		वापस rc;

	parent = per_cpu_cache_dev(cpu);
	क्रम (i = 0; i < cache_leaves(cpu); i++) अणु
		this_leaf = this_cpu_ci->info_list + i;
		अगर (this_leaf->disable_sysfs)
			जारी;
		अगर (this_leaf->type == CACHE_TYPE_NOCACHE)
			अवरोध;
		cache_groups = cache_get_attribute_groups(this_leaf);
		ci_dev = cpu_device_create(parent, this_leaf, cache_groups,
					   "index%1u", i);
		अगर (IS_ERR(ci_dev)) अणु
			rc = PTR_ERR(ci_dev);
			जाओ err;
		पूर्ण
		per_cache_index_dev(cpu, i) = ci_dev;
	पूर्ण
	cpumask_set_cpu(cpu, &cache_dev_map);

	वापस 0;
err:
	cpu_cache_sysfs_निकास(cpu);
	वापस rc;
पूर्ण

अटल पूर्णांक cacheinfo_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc = detect_cache_attributes(cpu);

	अगर (rc)
		वापस rc;
	rc = cache_add_dev(cpu);
	अगर (rc)
		मुक्त_cache_attributes(cpu);
	वापस rc;
पूर्ण

अटल पूर्णांक cacheinfo_cpu_pre_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_test_and_clear_cpu(cpu, &cache_dev_map))
		cpu_cache_sysfs_निकास(cpu);

	मुक्त_cache_attributes(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक __init cacheinfo_sysfs_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_BASE_CACHEINFO_ONLINE,
				 "base/cacheinfo:online",
				 cacheinfo_cpu_online, cacheinfo_cpu_pre_करोwn);
पूर्ण
device_initcall(cacheinfo_sysfs_init);
