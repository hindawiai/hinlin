<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER platक्रमm energy management driver
 * Copyright (C) 2010 IBM Corporation
 *
 * This pseries platक्रमm device driver provides access to
 * platक्रमm energy management capabilities.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/prom.h>


#घोषणा MODULE_VERS "1.0"
#घोषणा MODULE_NAME "pseries_energy"

/* Driver flags */

अटल पूर्णांक sysfs_entries;

/* Helper routines */

/* Helper Routines to convert between drc_index to cpu numbers */

अटल u32 cpu_to_drc_index(पूर्णांक cpu)
अणु
	काष्ठा device_node *dn = शून्य;
	काष्ठा property *info;
	पूर्णांक thपढ़ो_index;
	पूर्णांक rc = 1;
	u32 ret = 0;

	dn = of_find_node_by_path("/cpus");
	अगर (dn == शून्य)
		जाओ err;

	/* Convert logical cpu number to core number */
	thपढ़ो_index = cpu_core_index_of_thपढ़ो(cpu);

	info = of_find_property(dn, "ibm,drc-info", शून्य);
	अगर (info) अणु
		काष्ठा of_drc_info drc;
		पूर्णांक j;
		u32 num_set_entries;
		स्थिर __be32 *value;

		value = of_prop_next_u32(info, शून्य, &num_set_entries);
		अगर (!value)
			जाओ err_of_node_put;
		अन्यथा
			value++;

		क्रम (j = 0; j < num_set_entries; j++) अणु

			of_पढ़ो_drc_info_cell(&info, &value, &drc);
			अगर (म_भेदन(drc.drc_type, "CPU", 3))
				जाओ err;

			अगर (thपढ़ो_index < drc.last_drc_index)
				अवरोध;
		पूर्ण

		ret = drc.drc_index_start + (thपढ़ो_index * drc.sequential_inc);
	पूर्ण अन्यथा अणु
		u32 nr_drc_indexes, thपढ़ो_drc_index;

		/*
		 * The first element of ibm,drc-indexes array is the
		 * number of drc_indexes वापसed in the list.  Hence
		 * thपढ़ो_index+1 will get the drc_index corresponding
		 * to core number thपढ़ो_index.
		 */
		rc = of_property_पढ़ो_u32_index(dn, "ibm,drc-indexes",
						0, &nr_drc_indexes);
		अगर (rc)
			जाओ err_of_node_put;

		WARN_ON_ONCE(thपढ़ो_index > nr_drc_indexes);
		rc = of_property_पढ़ो_u32_index(dn, "ibm,drc-indexes",
						thपढ़ो_index + 1,
						&thपढ़ो_drc_index);
		अगर (rc)
			जाओ err_of_node_put;

		ret = thपढ़ो_drc_index;
	पूर्ण

	rc = 0;

err_of_node_put:
	of_node_put(dn);
err:
	अगर (rc)
		prपूर्णांकk(KERN_WARNING "cpu_to_drc_index(%d) failed", cpu);
	वापस ret;
पूर्ण

अटल पूर्णांक drc_index_to_cpu(u32 drc_index)
अणु
	काष्ठा device_node *dn = शून्य;
	काष्ठा property *info;
	स्थिर पूर्णांक *indexes;
	पूर्णांक thपढ़ो_index = 0, cpu = 0;
	पूर्णांक rc = 1;

	dn = of_find_node_by_path("/cpus");
	अगर (dn == शून्य)
		जाओ err;
	info = of_find_property(dn, "ibm,drc-info", शून्य);
	अगर (info) अणु
		काष्ठा of_drc_info drc;
		पूर्णांक j;
		u32 num_set_entries;
		स्थिर __be32 *value;

		value = of_prop_next_u32(info, शून्य, &num_set_entries);
		अगर (!value)
			जाओ err_of_node_put;
		अन्यथा
			value++;

		क्रम (j = 0; j < num_set_entries; j++) अणु

			of_पढ़ो_drc_info_cell(&info, &value, &drc);
			अगर (म_भेदन(drc.drc_type, "CPU", 3))
				जाओ err;

			अगर (drc_index > drc.last_drc_index) अणु
				cpu += drc.num_sequential_elems;
				जारी;
			पूर्ण
			cpu += ((drc_index - drc.drc_index_start) /
				drc.sequential_inc);

			thपढ़ो_index = cpu_first_thपढ़ो_of_core(cpu);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ पूर्णांक i;

		indexes = of_get_property(dn, "ibm,drc-indexes", शून्य);
		अगर (indexes == शून्य)
			जाओ err_of_node_put;
		/*
		 * First element in the array is the number of drc_indexes
		 * वापसed.  Search through the list to find the matching
		 * drc_index and get the core number
		 */
		क्रम (i = 0; i < indexes[0]; i++) अणु
			अगर (indexes[i + 1] == drc_index)
				अवरोध;
		पूर्ण
		/* Convert core number to logical cpu number */
		thपढ़ो_index = cpu_first_thपढ़ो_of_core(i);
		rc = 0;
	पूर्ण

err_of_node_put:
	of_node_put(dn);
err:
	अगर (rc)
		prपूर्णांकk(KERN_WARNING "drc_index_to_cpu(%d) failed", drc_index);
	वापस thपढ़ो_index;
पूर्ण

/*
 * pseries hypervisor call H_BEST_ENERGY provides hपूर्णांकs to OS on
 * preferred logical cpus to activate or deactivate क्रम optimized
 * energy consumption.
 */

#घोषणा FLAGS_MODE1	0x004E200000080E01UL
#घोषणा FLAGS_MODE2	0x004E200000080401UL
#घोषणा FLAGS_ACTIVATE  0x100

अटल sमाप_प्रकार get_best_energy_list(अक्षर *page, पूर्णांक activate)
अणु
	पूर्णांक rc, cnt, i, cpu;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];
	अचिन्हित दीर्घ flags = 0;
	u32 *buf_page;
	अक्षर *s = page;

	buf_page = (u32 *) get_zeroed_page(GFP_KERNEL);
	अगर (!buf_page)
		वापस -ENOMEM;

	flags = FLAGS_MODE1;
	अगर (activate)
		flags |= FLAGS_ACTIVATE;

	rc = plpar_hcall9(H_BEST_ENERGY, retbuf, flags, 0, __pa(buf_page),
				0, 0, 0, 0, 0, 0);
	अगर (rc != H_SUCCESS) अणु
		मुक्त_page((अचिन्हित दीर्घ) buf_page);
		वापस -EINVAL;
	पूर्ण

	cnt = retbuf[0];
	क्रम (i = 0; i < cnt; i++) अणु
		cpu = drc_index_to_cpu(buf_page[2*i+1]);
		अगर ((cpu_online(cpu) && !activate) ||
		    (!cpu_online(cpu) && activate))
			s += प्र_लिखो(s, "%d,", cpu);
	पूर्ण
	अगर (s > page) अणु /* Something to show */
		s--; /* Suppress last comma */
		s += प्र_लिखो(s, "\n");
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ) buf_page);
	वापस s-page;
पूर्ण

अटल sमाप_प्रकार get_best_energy_data(काष्ठा device *dev,
					अक्षर *page, पूर्णांक activate)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];
	अचिन्हित दीर्घ flags = 0;

	flags = FLAGS_MODE2;
	अगर (activate)
		flags |= FLAGS_ACTIVATE;

	rc = plpar_hcall9(H_BEST_ENERGY, retbuf, flags,
				cpu_to_drc_index(dev->id),
				0, 0, 0, 0, 0, 0, 0);

	अगर (rc != H_SUCCESS)
		वापस -EINVAL;

	वापस प्र_लिखो(page, "%lu\n", retbuf[1] >> 32);
पूर्ण

/* Wrapper functions */

अटल sमाप_प्रकार cpu_activate_hपूर्णांक_list_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *page)
अणु
	वापस get_best_energy_list(page, 1);
पूर्ण

अटल sमाप_प्रकार cpu_deactivate_hपूर्णांक_list_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *page)
अणु
	वापस get_best_energy_list(page, 0);
पूर्ण

अटल sमाप_प्रकार percpu_activate_hपूर्णांक_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *page)
अणु
	वापस get_best_energy_data(dev, page, 1);
पूर्ण

अटल sमाप_प्रकार percpu_deactivate_hपूर्णांक_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *page)
अणु
	वापस get_best_energy_data(dev, page, 0);
पूर्ण

/*
 * Create sysfs पूर्णांकerface:
 * /sys/devices/प्रणाली/cpu/pseries_activate_hपूर्णांक_list
 * /sys/devices/प्रणाली/cpu/pseries_deactivate_hपूर्णांक_list
 *	Comma separated list of cpus to activate or deactivate
 * /sys/devices/प्रणाली/cpu/cpuN/pseries_activate_hपूर्णांक
 * /sys/devices/प्रणाली/cpu/cpuN/pseries_deactivate_hपूर्णांक
 *	Per-cpu value of the hपूर्णांक
 */

अटल काष्ठा device_attribute attr_cpu_activate_hपूर्णांक_list =
		__ATTR(pseries_activate_hपूर्णांक_list, 0444,
		cpu_activate_hपूर्णांक_list_show, शून्य);

अटल काष्ठा device_attribute attr_cpu_deactivate_hपूर्णांक_list =
		__ATTR(pseries_deactivate_hपूर्णांक_list, 0444,
		cpu_deactivate_hपूर्णांक_list_show, शून्य);

अटल काष्ठा device_attribute attr_percpu_activate_hपूर्णांक =
		__ATTR(pseries_activate_hपूर्णांक, 0444,
		percpu_activate_hपूर्णांक_show, शून्य);

अटल काष्ठा device_attribute attr_percpu_deactivate_hपूर्णांक =
		__ATTR(pseries_deactivate_hपूर्णांक, 0444,
		percpu_deactivate_hपूर्णांक_show, शून्य);

अटल पूर्णांक __init pseries_energy_init(व्योम)
अणु
	पूर्णांक cpu, err;
	काष्ठा device *cpu_dev;

	अगर (!firmware_has_feature(FW_FEATURE_BEST_ENERGY))
		वापस 0; /* H_BEST_ENERGY hcall not supported */

	/* Create the sysfs files */
	err = device_create_file(cpu_subsys.dev_root,
				&attr_cpu_activate_hपूर्णांक_list);
	अगर (!err)
		err = device_create_file(cpu_subsys.dev_root,
				&attr_cpu_deactivate_hपूर्णांक_list);

	अगर (err)
		वापस err;
	क्रम_each_possible_cpu(cpu) अणु
		cpu_dev = get_cpu_device(cpu);
		err = device_create_file(cpu_dev,
				&attr_percpu_activate_hपूर्णांक);
		अगर (err)
			अवरोध;
		err = device_create_file(cpu_dev,
				&attr_percpu_deactivate_hपूर्णांक);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	sysfs_entries = 1; /* Removed entries on cleanup */
	वापस 0;

पूर्ण

अटल व्योम __निकास pseries_energy_cleanup(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा device *cpu_dev;

	अगर (!sysfs_entries)
		वापस;

	/* Remove the sysfs files */
	device_हटाओ_file(cpu_subsys.dev_root, &attr_cpu_activate_hपूर्णांक_list);
	device_हटाओ_file(cpu_subsys.dev_root, &attr_cpu_deactivate_hपूर्णांक_list);

	क्रम_each_possible_cpu(cpu) अणु
		cpu_dev = get_cpu_device(cpu);
		sysfs_हटाओ_file(&cpu_dev->kobj,
				&attr_percpu_activate_hपूर्णांक.attr);
		sysfs_हटाओ_file(&cpu_dev->kobj,
				&attr_percpu_deactivate_hपूर्णांक.attr);
	पूर्ण
पूर्ण

module_init(pseries_energy_init);
module_निकास(pseries_energy_cleanup);
MODULE_DESCRIPTION("Driver for pSeries platform energy management");
MODULE_AUTHOR("Vaidyanathan Srinivasan");
MODULE_LICENSE("GPL");
