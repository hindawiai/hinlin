<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * driver/base/topology.c - Populate sysfs with cpu topology inक्रमmation
 *
 * Written by: Zhang Yanmin, Intel Corporation
 *
 * Copyright (C) 2006, Intel Corp.
 *
 * All rights reserved.
 */
#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/topology.h>

#घोषणा define_id_show_func(name)					\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	वापस sysfs_emit(buf, "%d\n", topology_##name(dev->id));	\
पूर्ण

#घोषणा define_siblings_show_map(name, mask)				\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	वापस cpumap_prपूर्णांक_to_pagebuf(false, buf, topology_##mask(dev->id));\
पूर्ण

#घोषणा define_siblings_show_list(name, mask)				\
अटल sमाप_प्रकार name##_list_show(काष्ठा device *dev,			\
				काष्ठा device_attribute *attr,		\
				अक्षर *buf)				\
अणु									\
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, topology_##mask(dev->id));\
पूर्ण

#घोषणा define_siblings_show_func(name, mask)	\
	define_siblings_show_map(name, mask);	\
	define_siblings_show_list(name, mask)

define_id_show_func(physical_package_id);
अटल DEVICE_ATTR_RO(physical_package_id);

define_id_show_func(die_id);
अटल DEVICE_ATTR_RO(die_id);

define_id_show_func(core_id);
अटल DEVICE_ATTR_RO(core_id);

define_siblings_show_func(thपढ़ो_siblings, sibling_cpumask);
अटल DEVICE_ATTR_RO(thपढ़ो_siblings);
अटल DEVICE_ATTR_RO(thपढ़ो_siblings_list);

define_siblings_show_func(core_cpus, sibling_cpumask);
अटल DEVICE_ATTR_RO(core_cpus);
अटल DEVICE_ATTR_RO(core_cpus_list);

define_siblings_show_func(core_siblings, core_cpumask);
अटल DEVICE_ATTR_RO(core_siblings);
अटल DEVICE_ATTR_RO(core_siblings_list);

define_siblings_show_func(die_cpus, die_cpumask);
अटल DEVICE_ATTR_RO(die_cpus);
अटल DEVICE_ATTR_RO(die_cpus_list);

define_siblings_show_func(package_cpus, core_cpumask);
अटल DEVICE_ATTR_RO(package_cpus);
अटल DEVICE_ATTR_RO(package_cpus_list);

#अगर_घोषित CONFIG_SCHED_BOOK
define_id_show_func(book_id);
अटल DEVICE_ATTR_RO(book_id);
define_siblings_show_func(book_siblings, book_cpumask);
अटल DEVICE_ATTR_RO(book_siblings);
अटल DEVICE_ATTR_RO(book_siblings_list);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_DRAWER
define_id_show_func(drawer_id);
अटल DEVICE_ATTR_RO(drawer_id);
define_siblings_show_func(drawer_siblings, drawer_cpumask);
अटल DEVICE_ATTR_RO(drawer_siblings);
अटल DEVICE_ATTR_RO(drawer_siblings_list);
#पूर्ण_अगर

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&dev_attr_physical_package_id.attr,
	&dev_attr_die_id.attr,
	&dev_attr_core_id.attr,
	&dev_attr_thपढ़ो_siblings.attr,
	&dev_attr_thपढ़ो_siblings_list.attr,
	&dev_attr_core_cpus.attr,
	&dev_attr_core_cpus_list.attr,
	&dev_attr_core_siblings.attr,
	&dev_attr_core_siblings_list.attr,
	&dev_attr_die_cpus.attr,
	&dev_attr_die_cpus_list.attr,
	&dev_attr_package_cpus.attr,
	&dev_attr_package_cpus_list.attr,
#अगर_घोषित CONFIG_SCHED_BOOK
	&dev_attr_book_id.attr,
	&dev_attr_book_siblings.attr,
	&dev_attr_book_siblings_list.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_DRAWER
	&dev_attr_drawer_id.attr,
	&dev_attr_drawer_siblings.attr,
	&dev_attr_drawer_siblings_list.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group topology_attr_group = अणु
	.attrs = शेष_attrs,
	.name = "topology"
पूर्ण;

/* Add/Remove cpu_topology पूर्णांकerface क्रम CPU device */
अटल पूर्णांक topology_add_dev(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	वापस sysfs_create_group(&dev->kobj, &topology_attr_group);
पूर्ण

अटल पूर्णांक topology_हटाओ_dev(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	sysfs_हटाओ_group(&dev->kobj, &topology_attr_group);
	वापस 0;
पूर्ण

अटल पूर्णांक __init topology_sysfs_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_TOPOLOGY_PREPARE,
				 "base/topology:prepare", topology_add_dev,
				 topology_हटाओ_dev);
पूर्ण

device_initcall(topology_sysfs_init);
