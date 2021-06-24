<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2011
 *    Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "cpu"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/workqueue.h>
#समावेश <linux/memblock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/node.h>
#समावेश <यंत्र/sysinfo.h>

#घोषणा PTF_HORIZONTAL	(0UL)
#घोषणा PTF_VERTICAL	(1UL)
#घोषणा PTF_CHECK	(2UL)

क्रमागत अणु
	TOPOLOGY_MODE_HW,
	TOPOLOGY_MODE_SINGLE,
	TOPOLOGY_MODE_PACKAGE,
	TOPOLOGY_MODE_UNINITIALIZED
पूर्ण;

काष्ठा mask_info अणु
	काष्ठा mask_info *next;
	अचिन्हित अक्षर id;
	cpumask_t mask;
पूर्ण;

अटल पूर्णांक topology_mode = TOPOLOGY_MODE_UNINITIALIZED;
अटल व्योम set_topology_समयr(व्योम);
अटल व्योम topology_work_fn(काष्ठा work_काष्ठा *work);
अटल काष्ठा sysinfo_15_1_x *tl_info;

अटल DECLARE_WORK(topology_work, topology_work_fn);

/*
 * Socket/Book linked lists and cpu_topology updates are
 * रक्षित by "sched_domains_mutex".
 */
अटल काष्ठा mask_info socket_info;
अटल काष्ठा mask_info book_info;
अटल काष्ठा mask_info drawer_info;

काष्ठा cpu_topology_s390 cpu_topology[NR_CPUS];
EXPORT_SYMBOL_GPL(cpu_topology);

अटल व्योम cpu_group_map(cpumask_t *dst, काष्ठा mask_info *info, अचिन्हित पूर्णांक cpu)
अणु
	अटल cpumask_t mask;

	cpumask_copy(&mask, cpumask_of(cpu));
	चयन (topology_mode) अणु
	हाल TOPOLOGY_MODE_HW:
		जबतक (info) अणु
			अगर (cpumask_test_cpu(cpu, &info->mask)) अणु
				cpumask_copy(&mask, &info->mask);
				अवरोध;
			पूर्ण
			info = info->next;
		पूर्ण
		अवरोध;
	हाल TOPOLOGY_MODE_PACKAGE:
		cpumask_copy(&mask, cpu_present_mask);
		अवरोध;
	शेष:
		fallthrough;
	हाल TOPOLOGY_MODE_SINGLE:
		cpumask_copy(&mask, cpumask_of(cpu));
		अवरोध;
	पूर्ण
	cpumask_and(&mask, &mask, cpu_online_mask);
	cpumask_copy(dst, &mask);
पूर्ण

अटल व्योम cpu_thपढ़ो_map(cpumask_t *dst, अचिन्हित पूर्णांक cpu)
अणु
	अटल cpumask_t mask;
	पूर्णांक i;

	cpumask_copy(&mask, cpumask_of(cpu));
	अगर (topology_mode != TOPOLOGY_MODE_HW)
		जाओ out;
	cpu -= cpu % (smp_cpu_mtid + 1);
	क्रम (i = 0; i <= smp_cpu_mtid; i++)
		अगर (cpu_present(cpu + i))
			cpumask_set_cpu(cpu + i, &mask);
	cpumask_and(&mask, &mask, cpu_online_mask);
out:
	cpumask_copy(dst, &mask);
पूर्ण

#घोषणा TOPOLOGY_CORE_BITS	64

अटल व्योम add_cpus_to_mask(काष्ठा topology_core *tl_core,
			     काष्ठा mask_info *drawer,
			     काष्ठा mask_info *book,
			     काष्ठा mask_info *socket)
अणु
	काष्ठा cpu_topology_s390 *topo;
	अचिन्हित पूर्णांक core;

	क्रम_each_set_bit(core, &tl_core->mask, TOPOLOGY_CORE_BITS) अणु
		अचिन्हित पूर्णांक rcore;
		पूर्णांक lcpu, i;

		rcore = TOPOLOGY_CORE_BITS - 1 - core + tl_core->origin;
		lcpu = smp_find_processor_id(rcore << smp_cpu_mt_shअगरt);
		अगर (lcpu < 0)
			जारी;
		क्रम (i = 0; i <= smp_cpu_mtid; i++) अणु
			topo = &cpu_topology[lcpu + i];
			topo->drawer_id = drawer->id;
			topo->book_id = book->id;
			topo->socket_id = socket->id;
			topo->core_id = rcore;
			topo->thपढ़ो_id = lcpu + i;
			topo->dedicated = tl_core->d;
			cpumask_set_cpu(lcpu + i, &drawer->mask);
			cpumask_set_cpu(lcpu + i, &book->mask);
			cpumask_set_cpu(lcpu + i, &socket->mask);
			smp_cpu_set_polarization(lcpu + i, tl_core->pp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clear_masks(व्योम)
अणु
	काष्ठा mask_info *info;

	info = &socket_info;
	जबतक (info) अणु
		cpumask_clear(&info->mask);
		info = info->next;
	पूर्ण
	info = &book_info;
	जबतक (info) अणु
		cpumask_clear(&info->mask);
		info = info->next;
	पूर्ण
	info = &drawer_info;
	जबतक (info) अणु
		cpumask_clear(&info->mask);
		info = info->next;
	पूर्ण
पूर्ण

अटल जोड़ topology_entry *next_tle(जोड़ topology_entry *tle)
अणु
	अगर (!tle->nl)
		वापस (जोड़ topology_entry *)((काष्ठा topology_core *)tle + 1);
	वापस (जोड़ topology_entry *)((काष्ठा topology_container *)tle + 1);
पूर्ण

अटल व्योम tl_to_masks(काष्ठा sysinfo_15_1_x *info)
अणु
	काष्ठा mask_info *socket = &socket_info;
	काष्ठा mask_info *book = &book_info;
	काष्ठा mask_info *drawer = &drawer_info;
	जोड़ topology_entry *tle, *end;

	clear_masks();
	tle = info->tle;
	end = (जोड़ topology_entry *)((अचिन्हित दीर्घ)info + info->length);
	जबतक (tle < end) अणु
		चयन (tle->nl) अणु
		हाल 3:
			drawer = drawer->next;
			drawer->id = tle->container.id;
			अवरोध;
		हाल 2:
			book = book->next;
			book->id = tle->container.id;
			अवरोध;
		हाल 1:
			socket = socket->next;
			socket->id = tle->container.id;
			अवरोध;
		हाल 0:
			add_cpus_to_mask(&tle->cpu, drawer, book, socket);
			अवरोध;
		शेष:
			clear_masks();
			वापस;
		पूर्ण
		tle = next_tle(tle);
	पूर्ण
पूर्ण

अटल व्योम topology_update_polarization_simple(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		smp_cpu_set_polarization(cpu, POLARIZATION_HRZ);
पूर्ण

अटल पूर्णांक ptf(अचिन्हित दीर्घ fc)
अणु
	पूर्णांक rc;

	यंत्र अस्थिर(
		"	.insn	rre,0xb9a20000,%1,%1\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (rc)
		: "d" (fc)  : "cc");
	वापस rc;
पूर्ण

पूर्णांक topology_set_cpu_management(पूर्णांक fc)
अणु
	पूर्णांक cpu, rc;

	अगर (!MACHINE_HAS_TOPOLOGY)
		वापस -EOPNOTSUPP;
	अगर (fc)
		rc = ptf(PTF_VERTICAL);
	अन्यथा
		rc = ptf(PTF_HORIZONTAL);
	अगर (rc)
		वापस -EBUSY;
	क्रम_each_possible_cpu(cpu)
		smp_cpu_set_polarization(cpu, POLARIZATION_UNKNOWN);
	वापस rc;
पूर्ण

व्योम update_cpu_masks(व्योम)
अणु
	काष्ठा cpu_topology_s390 *topo, *topo_package, *topo_sibling;
	पूर्णांक cpu, sibling, pkg_first, smt_first, id;

	क्रम_each_possible_cpu(cpu) अणु
		topo = &cpu_topology[cpu];
		cpu_thपढ़ो_map(&topo->thपढ़ो_mask, cpu);
		cpu_group_map(&topo->core_mask, &socket_info, cpu);
		cpu_group_map(&topo->book_mask, &book_info, cpu);
		cpu_group_map(&topo->drawer_mask, &drawer_info, cpu);
		topo->booted_cores = 0;
		अगर (topology_mode != TOPOLOGY_MODE_HW) अणु
			id = topology_mode == TOPOLOGY_MODE_PACKAGE ? 0 : cpu;
			topo->thपढ़ो_id = cpu;
			topo->core_id = cpu;
			topo->socket_id = id;
			topo->book_id = id;
			topo->drawer_id = id;
		पूर्ण
	पूर्ण
	क्रम_each_online_cpu(cpu) अणु
		topo = &cpu_topology[cpu];
		pkg_first = cpumask_first(&topo->core_mask);
		topo_package = &cpu_topology[pkg_first];
		अगर (cpu == pkg_first) अणु
			क्रम_each_cpu(sibling, &topo->core_mask) अणु
				topo_sibling = &cpu_topology[sibling];
				smt_first = cpumask_first(&topo_sibling->thपढ़ो_mask);
				अगर (sibling == smt_first)
					topo_package->booted_cores++;
			पूर्ण
		पूर्ण अन्यथा अणु
			topo->booted_cores = topo_package->booted_cores;
		पूर्ण
	पूर्ण
पूर्ण

व्योम store_topology(काष्ठा sysinfo_15_1_x *info)
अणु
	stsi(info, 15, 1, topology_mnest_limit());
पूर्ण

अटल व्योम __arch_update_dedicated_flag(व्योम *arg)
अणु
	अगर (topology_cpu_dedicated(smp_processor_id()))
		set_cpu_flag(CIF_DEDICATED_CPU);
	अन्यथा
		clear_cpu_flag(CIF_DEDICATED_CPU);
पूर्ण

अटल पूर्णांक __arch_update_cpu_topology(व्योम)
अणु
	काष्ठा sysinfo_15_1_x *info = tl_info;
	पूर्णांक rc = 0;

	mutex_lock(&smp_cpu_state_mutex);
	अगर (MACHINE_HAS_TOPOLOGY) अणु
		rc = 1;
		store_topology(info);
		tl_to_masks(info);
	पूर्ण
	update_cpu_masks();
	अगर (!MACHINE_HAS_TOPOLOGY)
		topology_update_polarization_simple();
	mutex_unlock(&smp_cpu_state_mutex);
	वापस rc;
पूर्ण

पूर्णांक arch_update_cpu_topology(व्योम)
अणु
	काष्ठा device *dev;
	पूर्णांक cpu, rc;

	rc = __arch_update_cpu_topology();
	on_each_cpu(__arch_update_dedicated_flag, शून्य, 0);
	क्रम_each_online_cpu(cpu) अणु
		dev = get_cpu_device(cpu);
		अगर (dev)
			kobject_uevent(&dev->kobj, KOBJ_CHANGE);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम topology_work_fn(काष्ठा work_काष्ठा *work)
अणु
	rebuild_sched_करोमुख्यs();
पूर्ण

व्योम topology_schedule_update(व्योम)
अणु
	schedule_work(&topology_work);
पूर्ण

अटल व्योम topology_flush_work(व्योम)
अणु
	flush_work(&topology_work);
पूर्ण

अटल व्योम topology_समयr_fn(काष्ठा समयr_list *unused)
अणु
	अगर (ptf(PTF_CHECK))
		topology_schedule_update();
	set_topology_समयr();
पूर्ण

अटल काष्ठा समयr_list topology_समयr;

अटल atomic_t topology_poll = ATOMIC_INIT(0);

अटल व्योम set_topology_समयr(व्योम)
अणु
	अगर (atomic_add_unless(&topology_poll, -1, 0))
		mod_समयr(&topology_समयr, jअगरfies + msecs_to_jअगरfies(100));
	अन्यथा
		mod_समयr(&topology_समयr, jअगरfies + msecs_to_jअगरfies(60 * MSEC_PER_SEC));
पूर्ण

व्योम topology_expect_change(व्योम)
अणु
	अगर (!MACHINE_HAS_TOPOLOGY)
		वापस;
	/* This is racy, but it करोesn't matter since it is just a heuristic.
	 * Worst हाल is that we poll in a higher frequency क्रम a bit दीर्घer.
	 */
	अगर (atomic_पढ़ो(&topology_poll) > 60)
		वापस;
	atomic_add(60, &topology_poll);
	set_topology_समयr();
पूर्ण

अटल पूर्णांक cpu_management;

अटल sमाप_प्रकार dispatching_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार count;

	mutex_lock(&smp_cpu_state_mutex);
	count = प्र_लिखो(buf, "%d\n", cpu_management);
	mutex_unlock(&smp_cpu_state_mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार dispatching_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	पूर्णांक val, rc;
	अक्षर delim;

	अगर (माला_पूछो(buf, "%d %c", &val, &delim) != 1)
		वापस -EINVAL;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;
	rc = 0;
	get_online_cpus();
	mutex_lock(&smp_cpu_state_mutex);
	अगर (cpu_management == val)
		जाओ out;
	rc = topology_set_cpu_management(val);
	अगर (rc)
		जाओ out;
	cpu_management = val;
	topology_expect_change();
out:
	mutex_unlock(&smp_cpu_state_mutex);
	put_online_cpus();
	वापस rc ? rc : count;
पूर्ण
अटल DEVICE_ATTR_RW(dispatching);

अटल sमाप_प्रकार cpu_polarization_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक cpu = dev->id;
	sमाप_प्रकार count;

	mutex_lock(&smp_cpu_state_mutex);
	चयन (smp_cpu_get_polarization(cpu)) अणु
	हाल POLARIZATION_HRZ:
		count = प्र_लिखो(buf, "horizontal\n");
		अवरोध;
	हाल POLARIZATION_VL:
		count = प्र_लिखो(buf, "vertical:low\n");
		अवरोध;
	हाल POLARIZATION_VM:
		count = प्र_लिखो(buf, "vertical:medium\n");
		अवरोध;
	हाल POLARIZATION_VH:
		count = प्र_लिखो(buf, "vertical:high\n");
		अवरोध;
	शेष:
		count = प्र_लिखो(buf, "unknown\n");
		अवरोध;
	पूर्ण
	mutex_unlock(&smp_cpu_state_mutex);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(polarization, 0444, cpu_polarization_show, शून्य);

अटल काष्ठा attribute *topology_cpu_attrs[] = अणु
	&dev_attr_polarization.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group topology_cpu_attr_group = अणु
	.attrs = topology_cpu_attrs,
पूर्ण;

अटल sमाप_प्रकार cpu_dedicated_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक cpu = dev->id;
	sमाप_प्रकार count;

	mutex_lock(&smp_cpu_state_mutex);
	count = प्र_लिखो(buf, "%d\n", topology_cpu_dedicated(cpu));
	mutex_unlock(&smp_cpu_state_mutex);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(dedicated, 0444, cpu_dedicated_show, शून्य);

अटल काष्ठा attribute *topology_extra_cpu_attrs[] = अणु
	&dev_attr_dedicated.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group topology_extra_cpu_attr_group = अणु
	.attrs = topology_extra_cpu_attrs,
पूर्ण;

पूर्णांक topology_cpu_init(काष्ठा cpu *cpu)
अणु
	पूर्णांक rc;

	rc = sysfs_create_group(&cpu->dev.kobj, &topology_cpu_attr_group);
	अगर (rc || !MACHINE_HAS_TOPOLOGY)
		वापस rc;
	rc = sysfs_create_group(&cpu->dev.kobj, &topology_extra_cpu_attr_group);
	अगर (rc)
		sysfs_हटाओ_group(&cpu->dev.kobj, &topology_cpu_attr_group);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा cpumask *cpu_thपढ़ो_mask(पूर्णांक cpu)
अणु
	वापस &cpu_topology[cpu].thपढ़ो_mask;
पूर्ण


स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	वापस &cpu_topology[cpu].core_mask;
पूर्ण

अटल स्थिर काष्ठा cpumask *cpu_book_mask(पूर्णांक cpu)
अणु
	वापस &cpu_topology[cpu].book_mask;
पूर्ण

अटल स्थिर काष्ठा cpumask *cpu_drawer_mask(पूर्णांक cpu)
अणु
	वापस &cpu_topology[cpu].drawer_mask;
पूर्ण

अटल काष्ठा sched_करोमुख्य_topology_level s390_topology[] = अणु
	अणु cpu_thपढ़ो_mask, cpu_smt_flags, SD_INIT_NAME(SMT) पूर्ण,
	अणु cpu_coregroup_mask, cpu_core_flags, SD_INIT_NAME(MC) पूर्ण,
	अणु cpu_book_mask, SD_INIT_NAME(BOOK) पूर्ण,
	अणु cpu_drawer_mask, SD_INIT_NAME(DRAWER) पूर्ण,
	अणु cpu_cpu_mask, SD_INIT_NAME(DIE) पूर्ण,
	अणु शून्य, पूर्ण,
पूर्ण;

अटल व्योम __init alloc_masks(काष्ठा sysinfo_15_1_x *info,
			       काष्ठा mask_info *mask, पूर्णांक offset)
अणु
	पूर्णांक i, nr_masks;

	nr_masks = info->mag[TOPOLOGY_NR_MAG - offset];
	क्रम (i = 0; i < info->mnest - offset; i++)
		nr_masks *= info->mag[TOPOLOGY_NR_MAG - offset - 1 - i];
	nr_masks = max(nr_masks, 1);
	क्रम (i = 0; i < nr_masks; i++) अणु
		mask->next = memblock_alloc(माप(*mask->next), 8);
		अगर (!mask->next)
			panic("%s: Failed to allocate %zu bytes align=0x%x\n",
			      __func__, माप(*mask->next), 8);
		mask = mask->next;
	पूर्ण
पूर्ण

व्योम __init topology_init_early(व्योम)
अणु
	काष्ठा sysinfo_15_1_x *info;

	set_sched_topology(s390_topology);
	अगर (topology_mode == TOPOLOGY_MODE_UNINITIALIZED) अणु
		अगर (MACHINE_HAS_TOPOLOGY)
			topology_mode = TOPOLOGY_MODE_HW;
		अन्यथा
			topology_mode = TOPOLOGY_MODE_SINGLE;
	पूर्ण
	अगर (!MACHINE_HAS_TOPOLOGY)
		जाओ out;
	tl_info = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!tl_info)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);
	info = tl_info;
	store_topology(info);
	pr_info("The CPU configuration topology of the machine is: %d %d %d %d %d %d / %d\n",
		info->mag[0], info->mag[1], info->mag[2], info->mag[3],
		info->mag[4], info->mag[5], info->mnest);
	alloc_masks(info, &socket_info, 1);
	alloc_masks(info, &book_info, 2);
	alloc_masks(info, &drawer_info, 3);
out:
	__arch_update_cpu_topology();
	__arch_update_dedicated_flag(शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक topology_get_mode(पूर्णांक enabled)
अणु
	अगर (!enabled)
		वापस TOPOLOGY_MODE_SINGLE;
	वापस MACHINE_HAS_TOPOLOGY ? TOPOLOGY_MODE_HW : TOPOLOGY_MODE_PACKAGE;
पूर्ण

अटल अंतरभूत पूर्णांक topology_is_enabled(व्योम)
अणु
	वापस topology_mode != TOPOLOGY_MODE_SINGLE;
पूर्ण

अटल पूर्णांक __init topology_setup(अक्षर *str)
अणु
	bool enabled;
	पूर्णांक rc;

	rc = kstrtobool(str, &enabled);
	अगर (rc)
		वापस rc;
	topology_mode = topology_get_mode(enabled);
	वापस 0;
पूर्ण
early_param("topology", topology_setup);

अटल पूर्णांक topology_ctl_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक enabled = topology_is_enabled();
	पूर्णांक new_mode;
	पूर्णांक rc;
	काष्ठा ctl_table ctl_entry = अणु
		.procname	= ctl->procname,
		.data		= &enabled,
		.maxlen		= माप(पूर्णांक),
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण;

	rc = proc_करोuपूर्णांकvec_minmax(&ctl_entry, ग_लिखो, buffer, lenp, ppos);
	अगर (rc < 0 || !ग_लिखो)
		वापस rc;

	mutex_lock(&smp_cpu_state_mutex);
	new_mode = topology_get_mode(enabled);
	अगर (topology_mode != new_mode) अणु
		topology_mode = new_mode;
		topology_schedule_update();
	पूर्ण
	mutex_unlock(&smp_cpu_state_mutex);
	topology_flush_work();

	वापस rc;
पूर्ण

अटल काष्ठा ctl_table topology_ctl_table[] = अणु
	अणु
		.procname	= "topology",
		.mode		= 0644,
		.proc_handler	= topology_ctl_handler,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table topology_dir_table[] = अणु
	अणु
		.procname	= "s390",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= topology_ctl_table,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init topology_init(व्योम)
अणु
	समयr_setup(&topology_समयr, topology_समयr_fn, TIMER_DEFERRABLE);
	अगर (MACHINE_HAS_TOPOLOGY)
		set_topology_समयr();
	अन्यथा
		topology_update_polarization_simple();
	रेजिस्टर_sysctl_table(topology_dir_table);
	वापस device_create_file(cpu_subsys.dev_root, &dev_attr_dispatching);
पूर्ण
device_initcall(topology_init);
