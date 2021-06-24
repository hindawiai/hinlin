<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright IBM Corp. 2008
 *  Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "cpu"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/stop_machine.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/smp.h>

काष्ठा cpu_info अणु
	अचिन्हित पूर्णांक cpu_mhz_dynamic;
	अचिन्हित पूर्णांक cpu_mhz_अटल;
	काष्ठा cpuid cpu_id;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu_info, cpu_info);
अटल DEFINE_PER_CPU(पूर्णांक, cpu_relax_retry);

अटल bool machine_has_cpu_mhz;

व्योम __init cpu_detect_mhz_feature(व्योम)
अणु
	अगर (test_facility(34) && __ecag(ECAG_CPU_ATTRIBUTE, 0) != -1UL)
		machine_has_cpu_mhz = true;
पूर्ण

अटल व्योम update_cpu_mhz(व्योम *arg)
अणु
	अचिन्हित दीर्घ mhz;
	काष्ठा cpu_info *c;

	mhz = __ecag(ECAG_CPU_ATTRIBUTE, 0);
	c = this_cpu_ptr(&cpu_info);
	c->cpu_mhz_dynamic = mhz >> 32;
	c->cpu_mhz_अटल = mhz & 0xffffffff;
पूर्ण

व्योम s390_update_cpu_mhz(व्योम)
अणु
	s390_adjust_jअगरfies();
	अगर (machine_has_cpu_mhz)
		on_each_cpu(update_cpu_mhz, शून्य, 0);
पूर्ण

व्योम notrace stop_machine_yield(स्थिर काष्ठा cpumask *cpumask)
अणु
	पूर्णांक cpu, this_cpu;

	this_cpu = smp_processor_id();
	अगर (__this_cpu_inc_वापस(cpu_relax_retry) >= spin_retry) अणु
		__this_cpu_ग_लिखो(cpu_relax_retry, 0);
		cpu = cpumask_next_wrap(this_cpu, cpumask, this_cpu, false);
		अगर (cpu >= nr_cpu_ids)
			वापस;
		अगर (arch_vcpu_is_preempted(cpu))
			smp_yield_cpu(cpu);
	पूर्ण
पूर्ण

/*
 * cpu_init - initializes state that is per-CPU.
 */
व्योम cpu_init(व्योम)
अणु
	काष्ठा cpuid *id = this_cpu_ptr(&cpu_info.cpu_id);

	get_cpu_id(id);
	अगर (machine_has_cpu_mhz)
		update_cpu_mhz(शून्य);
	mmgrab(&init_mm);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);
	enter_lazy_tlb(&init_mm, current);
पूर्ण

/*
 * cpu_have_feature - Test CPU features on module initialization
 */
पूर्णांक cpu_have_feature(अचिन्हित पूर्णांक num)
अणु
	वापस elf_hwcap & (1UL << num);
पूर्ण
EXPORT_SYMBOL(cpu_have_feature);

अटल व्योम show_facilities(काष्ठा seq_file *m)
अणु
	अचिन्हित पूर्णांक bit;
	दीर्घ *facilities;

	facilities = (दीर्घ *)&S390_lowcore.stfle_fac_list;
	seq_माला_दो(m, "facilities      :");
	क्रम_each_set_bit_inv(bit, facilities, MAX_FACILITY_BIT)
		seq_म_लिखो(m, " %d", bit);
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम show_cpu_summary(काष्ठा seq_file *m, व्योम *v)
अणु
	अटल स्थिर अक्षर *hwcap_str[] = अणु
		"esan3", "zarch", "stfle", "msa", "ldisp", "eimm", "dfp",
		"edat", "etf3eh", "highgprs", "te", "vx", "vxd", "vxe", "gs",
		"vxe2", "vxp", "sort", "dflt"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर पूर्णांक_hwcap_str[] = अणु
		"sie"
	पूर्ण;
	पूर्णांक i, cpu;

	seq_म_लिखो(m, "vendor_id       : IBM/S390\n"
		   "# processors    : %i\n"
		   "bogomips per cpu: %lu.%02lu\n",
		   num_online_cpus(), loops_per_jअगरfy/(500000/HZ),
		   (loops_per_jअगरfy/(5000/HZ))%100);
	seq_म_लिखो(m, "max thread id   : %d\n", smp_cpu_mtid);
	seq_माला_दो(m, "features\t: ");
	क्रम (i = 0; i < ARRAY_SIZE(hwcap_str); i++)
		अगर (hwcap_str[i] && (elf_hwcap & (1UL << i)))
			seq_म_लिखो(m, "%s ", hwcap_str[i]);
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांक_hwcap_str); i++)
		अगर (पूर्णांक_hwcap_str[i] && (पूर्णांक_hwcap & (1UL << i)))
			seq_म_लिखो(m, "%s ", पूर्णांक_hwcap_str[i]);
	seq_माला_दो(m, "\n");
	show_facilities(m);
	show_cacheinfo(m);
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा cpuid *id = &per_cpu(cpu_info.cpu_id, cpu);

		seq_म_लिखो(m, "processor %d: "
			   "version = %02X,  "
			   "identification = %06X,  "
			   "machine = %04X\n",
			   cpu, id->version, id->ident, id->machine);
	पूर्ण
पूर्ण

अटल व्योम show_cpu_topology(काष्ठा seq_file *m, अचिन्हित दीर्घ n)
अणु
#अगर_घोषित CONFIG_SCHED_TOPOLOGY
	seq_म_लिखो(m, "physical id     : %d\n", topology_physical_package_id(n));
	seq_म_लिखो(m, "core id         : %d\n", topology_core_id(n));
	seq_म_लिखो(m, "book id         : %d\n", topology_book_id(n));
	seq_म_लिखो(m, "drawer id       : %d\n", topology_drawer_id(n));
	seq_म_लिखो(m, "dedicated       : %d\n", topology_cpu_dedicated(n));
	seq_म_लिखो(m, "address         : %d\n", smp_cpu_get_cpu_address(n));
	seq_म_लिखो(m, "siblings        : %d\n", cpumask_weight(topology_core_cpumask(n)));
	seq_म_लिखो(m, "cpu cores       : %d\n", topology_booted_cores(n));
#पूर्ण_अगर /* CONFIG_SCHED_TOPOLOGY */
पूर्ण

अटल व्योम show_cpu_ids(काष्ठा seq_file *m, अचिन्हित दीर्घ n)
अणु
	काष्ठा cpuid *id = &per_cpu(cpu_info.cpu_id, n);

	seq_म_लिखो(m, "version         : %02X\n", id->version);
	seq_म_लिखो(m, "identification  : %06X\n", id->ident);
	seq_म_लिखो(m, "machine         : %04X\n", id->machine);
पूर्ण

अटल व्योम show_cpu_mhz(काष्ठा seq_file *m, अचिन्हित दीर्घ n)
अणु
	काष्ठा cpu_info *c = per_cpu_ptr(&cpu_info, n);

	अगर (!machine_has_cpu_mhz)
		वापस;
	seq_म_लिखो(m, "cpu MHz dynamic : %d\n", c->cpu_mhz_dynamic);
	seq_म_लिखो(m, "cpu MHz static  : %d\n", c->cpu_mhz_अटल);
पूर्ण

/*
 * show_cpuinfo - Get inक्रमmation on one CPU क्रम use by procfs.
 */
अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ n = (अचिन्हित दीर्घ) v - 1;
	अचिन्हित दीर्घ first = cpumask_first(cpu_online_mask);

	अगर (n == first)
		show_cpu_summary(m, v);
	seq_म_लिखो(m, "\ncpu number      : %ld\n", n);
	show_cpu_topology(m, n);
	show_cpu_ids(m, n);
	show_cpu_mhz(m, n);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *c_update(loff_t *pos)
अणु
	अगर (*pos)
		*pos = cpumask_next(*pos - 1, cpu_online_mask);
	अन्यथा
		*pos = cpumask_first(cpu_online_mask);
	वापस *pos < nr_cpu_ids ? (व्योम *)*pos + 1 : शून्य;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	get_online_cpus();
	वापस c_update(pos);
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_update(pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	put_online_cpus();
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;

पूर्णांक s390_isolate_bp(व्योम)
अणु
	अगर (!test_facility(82))
		वापस -EOPNOTSUPP;
	set_thपढ़ो_flag(TIF_ISOLATE_BP);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(s390_isolate_bp);

पूर्णांक s390_isolate_bp_guest(व्योम)
अणु
	अगर (!test_facility(82))
		वापस -EOPNOTSUPP;
	set_thपढ़ो_flag(TIF_ISOLATE_BP_GUEST);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(s390_isolate_bp_guest);
