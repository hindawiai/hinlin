<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * This file contains NUMA specअगरic variables and functions which can
 * be split away from DISCONTIGMEM and are used on NUMA machines with
 * contiguous memory.
 * 		2002/08/07 Erich Focht <efocht@ess.nec.de>
 * Populate cpu entries in sysfs क्रम non-numa प्रणालीs as well
 *  	Intel Corporation - Ashok Raj
 * 02/27/2006 Zhang, Yanmin
 *	Populate cpu cache entries in sysfs क्रम cpu cache info
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/node.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/cpu.h>

अटल काष्ठा ia64_cpu *sysfs_cpus;

व्योम arch_fix_phys_package_id(पूर्णांक num, u32 slot)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (cpu_data(num)->socket_id == -1)
		cpu_data(num)->socket_id = slot;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(arch_fix_phys_package_id);


#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक __ref arch_रेजिस्टर_cpu(पूर्णांक num)
अणु
	/*
	 * If CPEI can be re-targeted or अगर this is not
	 * CPEI target, then it is hotpluggable
	 */
	अगर (can_cpei_retarget() || !is_cpu_cpei_target(num))
		sysfs_cpus[num].cpu.hotpluggable = 1;
	map_cpu_to_node(num, node_cpuid[num].nid);
	वापस रेजिस्टर_cpu(&sysfs_cpus[num].cpu, num);
पूर्ण
EXPORT_SYMBOL(arch_रेजिस्टर_cpu);

व्योम __ref arch_unरेजिस्टर_cpu(पूर्णांक num)
अणु
	unरेजिस्टर_cpu(&sysfs_cpus[num].cpu);
	unmap_cpu_from_node(num, cpu_to_node(num));
पूर्ण
EXPORT_SYMBOL(arch_unरेजिस्टर_cpu);
#अन्यथा
अटल पूर्णांक __init arch_रेजिस्टर_cpu(पूर्णांक num)
अणु
	वापस रेजिस्टर_cpu(&sysfs_cpus[num].cpu, num);
पूर्ण
#पूर्ण_अगर /*CONFIG_HOTPLUG_CPU*/


अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i, err = 0;

#अगर_घोषित CONFIG_NUMA
	/*
	 * MCD - Do we want to रेजिस्टर all ONLINE nodes, or all POSSIBLE nodes?
	 */
	क्रम_each_online_node(i) अणु
		अगर ((err = रेजिस्टर_one_node(i)))
			जाओ out;
	पूर्ण
#पूर्ण_अगर

	sysfs_cpus = kसुस्मृति(NR_CPUS, माप(काष्ठा ia64_cpu), GFP_KERNEL);
	अगर (!sysfs_cpus)
		panic("kzalloc in topology_init failed - NR_CPUS too big?");

	क्रम_each_present_cpu(i) अणु
		अगर((err = arch_रेजिस्टर_cpu(i)))
			जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

subsys_initcall(topology_init);


/*
 * Export cpu cache inक्रमmation through sysfs
 */

/*
 *  A bunch of string array to get pretty prपूर्णांकing
 */
अटल स्थिर अक्षर *cache_types[] = अणु
	"",			/* not used */
	"Instruction",
	"Data",
	"Unified"	/* unअगरied */
पूर्ण;

अटल स्थिर अक्षर *cache_mattrib[]=अणु
	"WriteThrough",
	"WriteBack",
	"",		/* reserved */
	""		/* reserved */
पूर्ण;

काष्ठा cache_info अणु
	pal_cache_config_info_t	cci;
	cpumask_t shared_cpu_map;
	पूर्णांक level;
	पूर्णांक type;
	काष्ठा kobject kobj;
पूर्ण;

काष्ठा cpu_cache_info अणु
	काष्ठा cache_info *cache_leaves;
	पूर्णांक	num_cache_leaves;
	काष्ठा kobject kobj;
पूर्ण;

अटल काष्ठा cpu_cache_info	all_cpu_cache_info[NR_CPUS];
#घोषणा LEAF_KOBJECT_PTR(x,y)    (&all_cpu_cache_info[x].cache_leaves[y])

#अगर_घोषित CONFIG_SMP
अटल व्योम cache_shared_cpu_map_setup(अचिन्हित पूर्णांक cpu,
		काष्ठा cache_info * this_leaf)
अणु
	pal_cache_shared_info_t	csi;
	पूर्णांक num_shared, i = 0;
	अचिन्हित पूर्णांक j;

	अगर (cpu_data(cpu)->thपढ़ोs_per_core <= 1 &&
		cpu_data(cpu)->cores_per_socket <= 1) अणु
		cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
		वापस;
	पूर्ण

	अगर (ia64_pal_cache_shared_info(this_leaf->level,
					this_leaf->type,
					0,
					&csi) != PAL_STATUS_SUCCESS)
		वापस;

	num_shared = (पूर्णांक) csi.num_shared;
	करो अणु
		क्रम_each_possible_cpu(j)
			अगर (cpu_data(cpu)->socket_id == cpu_data(j)->socket_id
				&& cpu_data(j)->core_id == csi.log1_cid
				&& cpu_data(j)->thपढ़ो_id == csi.log1_tid)
				cpumask_set_cpu(j, &this_leaf->shared_cpu_map);

		i++;
	पूर्ण जबतक (i < num_shared &&
		ia64_pal_cache_shared_info(this_leaf->level,
				this_leaf->type,
				i,
				&csi) == PAL_STATUS_SUCCESS);
पूर्ण
#अन्यथा
अटल व्योम cache_shared_cpu_map_setup(अचिन्हित पूर्णांक cpu,
		काष्ठा cache_info * this_leaf)
अणु
	cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
	वापस;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार show_coherency_line_size(काष्ठा cache_info *this_leaf,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", 1 << this_leaf->cci.pcci_line_size);
पूर्ण

अटल sमाप_प्रकार show_ways_of_associativity(काष्ठा cache_info *this_leaf,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", this_leaf->cci.pcci_assoc);
पूर्ण

अटल sमाप_प्रकार show_attributes(काष्ठा cache_info *this_leaf, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf,
			"%s\n",
			cache_mattrib[this_leaf->cci.pcci_cache_attr]);
पूर्ण

अटल sमाप_प्रकार show_size(काष्ठा cache_info *this_leaf, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%uK\n", this_leaf->cci.pcci_cache_size / 1024);
पूर्ण

अटल sमाप_प्रकार show_number_of_sets(काष्ठा cache_info *this_leaf, अक्षर *buf)
अणु
	अचिन्हित number_of_sets = this_leaf->cci.pcci_cache_size;
	number_of_sets /= this_leaf->cci.pcci_assoc;
	number_of_sets /= 1 << this_leaf->cci.pcci_line_size;

	वापस प्र_लिखो(buf, "%u\n", number_of_sets);
पूर्ण

अटल sमाप_प्रकार show_shared_cpu_map(काष्ठा cache_info *this_leaf, अक्षर *buf)
अणु
	cpumask_t shared_cpu_map;

	cpumask_and(&shared_cpu_map,
				&this_leaf->shared_cpu_map, cpu_online_mask);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%*pb\n",
			 cpumask_pr_args(&shared_cpu_map));
पूर्ण

अटल sमाप_प्रकार show_type(काष्ठा cache_info *this_leaf, अक्षर *buf)
अणु
	पूर्णांक type = this_leaf->type + this_leaf->cci.pcci_unअगरied;
	वापस प्र_लिखो(buf, "%s\n", cache_types[type]);
पूर्ण

अटल sमाप_प्रकार show_level(काष्ठा cache_info *this_leaf, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", this_leaf->level);
पूर्ण

काष्ठा cache_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा cache_info *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा cache_info *, स्थिर अक्षर *, माप_प्रकार count);
पूर्ण;

#अगर_घोषित define_one_ro
	#अघोषित define_one_ro
#पूर्ण_अगर
#घोषणा define_one_ro(_name) \
	अटल काष्ठा cache_attr _name = \
__ATTR(_name, 0444, show_##_name, शून्य)

define_one_ro(level);
define_one_ro(type);
define_one_ro(coherency_line_size);
define_one_ro(ways_of_associativity);
define_one_ro(size);
define_one_ro(number_of_sets);
define_one_ro(shared_cpu_map);
define_one_ro(attributes);

अटल काष्ठा attribute * cache_शेष_attrs[] = अणु
	&type.attr,
	&level.attr,
	&coherency_line_size.attr,
	&ways_of_associativity.attr,
	&attributes.attr,
	&size.attr,
	&number_of_sets.attr,
	&shared_cpu_map.attr,
	शून्य
पूर्ण;

#घोषणा to_object(k) container_of(k, काष्ठा cache_info, kobj)
#घोषणा to_attr(a) container_of(a, काष्ठा cache_attr, attr)

अटल sमाप_प्रकार ia64_cache_show(काष्ठा kobject * kobj, काष्ठा attribute * attr, अक्षर * buf)
अणु
	काष्ठा cache_attr *fattr = to_attr(attr);
	काष्ठा cache_info *this_leaf = to_object(kobj);
	sमाप_प्रकार ret;

	ret = fattr->show ? fattr->show(this_leaf, buf) : 0;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops cache_sysfs_ops = अणु
	.show   = ia64_cache_show
पूर्ण;

अटल काष्ठा kobj_type cache_ktype = अणु
	.sysfs_ops	= &cache_sysfs_ops,
	.शेष_attrs	= cache_शेष_attrs,
पूर्ण;

अटल काष्ठा kobj_type cache_ktype_percpu_entry = अणु
	.sysfs_ops	= &cache_sysfs_ops,
पूर्ण;

अटल व्योम cpu_cache_sysfs_निकास(अचिन्हित पूर्णांक cpu)
अणु
	kमुक्त(all_cpu_cache_info[cpu].cache_leaves);
	all_cpu_cache_info[cpu].cache_leaves = शून्य;
	all_cpu_cache_info[cpu].num_cache_leaves = 0;
	स_रखो(&all_cpu_cache_info[cpu].kobj, 0, माप(काष्ठा kobject));
	वापस;
पूर्ण

अटल पूर्णांक cpu_cache_sysfs_init(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ i, levels, unique_caches;
	pal_cache_config_info_t cci;
	पूर्णांक j;
	दीर्घ status;
	काष्ठा cache_info *this_cache;
	पूर्णांक num_cache_leaves = 0;

	अगर ((status = ia64_pal_cache_summary(&levels, &unique_caches)) != 0) अणु
		prपूर्णांकk(KERN_ERR "ia64_pal_cache_summary=%ld\n", status);
		वापस -1;
	पूर्ण

	this_cache=kसुस्मृति(unique_caches, माप(काष्ठा cache_info),
			   GFP_KERNEL);
	अगर (this_cache == शून्य)
		वापस -ENOMEM;

	क्रम (i=0; i < levels; i++) अणु
		क्रम (j=2; j >0 ; j--) अणु
			अगर ((status=ia64_pal_cache_config_info(i,j, &cci)) !=
					PAL_STATUS_SUCCESS)
				जारी;

			this_cache[num_cache_leaves].cci = cci;
			this_cache[num_cache_leaves].level = i + 1;
			this_cache[num_cache_leaves].type = j;

			cache_shared_cpu_map_setup(cpu,
					&this_cache[num_cache_leaves]);
			num_cache_leaves ++;
		पूर्ण
	पूर्ण

	all_cpu_cache_info[cpu].cache_leaves = this_cache;
	all_cpu_cache_info[cpu].num_cache_leaves = num_cache_leaves;

	स_रखो(&all_cpu_cache_info[cpu].kobj, 0, माप(काष्ठा kobject));

	वापस 0;
पूर्ण

/* Add cache पूर्णांकerface क्रम CPU device */
अटल पूर्णांक cache_add_dev(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *sys_dev = get_cpu_device(cpu);
	अचिन्हित दीर्घ i, j;
	काष्ठा cache_info *this_object;
	पूर्णांक retval = 0;

	अगर (all_cpu_cache_info[cpu].kobj.parent)
		वापस 0;


	retval = cpu_cache_sysfs_init(cpu);
	अगर (unlikely(retval < 0))
		वापस retval;

	retval = kobject_init_and_add(&all_cpu_cache_info[cpu].kobj,
				      &cache_ktype_percpu_entry, &sys_dev->kobj,
				      "%s", "cache");
	अगर (unlikely(retval < 0)) अणु
		cpu_cache_sysfs_निकास(cpu);
		वापस retval;
	पूर्ण

	क्रम (i = 0; i < all_cpu_cache_info[cpu].num_cache_leaves; i++) अणु
		this_object = LEAF_KOBJECT_PTR(cpu,i);
		retval = kobject_init_and_add(&(this_object->kobj),
					      &cache_ktype,
					      &all_cpu_cache_info[cpu].kobj,
					      "index%1lu", i);
		अगर (unlikely(retval)) अणु
			क्रम (j = 0; j < i; j++) अणु
				kobject_put(&(LEAF_KOBJECT_PTR(cpu,j)->kobj));
			पूर्ण
			kobject_put(&all_cpu_cache_info[cpu].kobj);
			cpu_cache_sysfs_निकास(cpu);
			वापस retval;
		पूर्ण
		kobject_uevent(&(this_object->kobj), KOBJ_ADD);
	पूर्ण
	kobject_uevent(&all_cpu_cache_info[cpu].kobj, KOBJ_ADD);
	वापस retval;
पूर्ण

/* Remove cache पूर्णांकerface क्रम CPU device */
अटल पूर्णांक cache_हटाओ_dev(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < all_cpu_cache_info[cpu].num_cache_leaves; i++)
		kobject_put(&(LEAF_KOBJECT_PTR(cpu,i)->kobj));

	अगर (all_cpu_cache_info[cpu].kobj.parent) अणु
		kobject_put(&all_cpu_cache_info[cpu].kobj);
		स_रखो(&all_cpu_cache_info[cpu].kobj,
			0,
			माप(काष्ठा kobject));
	पूर्ण

	cpu_cache_sysfs_निकास(cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक __init cache_sysfs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "ia64/topology:online",
				cache_add_dev, cache_हटाओ_dev);
	WARN_ON(ret < 0);
	वापस 0;
पूर्ण
device_initcall(cache_sysfs_init);
