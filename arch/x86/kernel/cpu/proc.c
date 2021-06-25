<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/smp.h>
#समावेश <linux/समयx.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpufreq.h>

#समावेश "cpu.h"

#अगर_घोषित CONFIG_X86_VMX_FEATURE_NAMES
बाह्य स्थिर अक्षर * स्थिर x86_vmx_flags[NVMXINTS*32];
#पूर्ण_अगर

/*
 *	Get CPU inक्रमmation क्रम use by the procfs.
 */
अटल व्योम show_cpuinfo_core(काष्ठा seq_file *m, काष्ठा cpuinfo_x86 *c,
			      अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(m, "physical id\t: %d\n", c->phys_proc_id);
	seq_म_लिखो(m, "siblings\t: %d\n",
		   cpumask_weight(topology_core_cpumask(cpu)));
	seq_म_लिखो(m, "core id\t\t: %d\n", c->cpu_core_id);
	seq_म_लिखो(m, "cpu cores\t: %d\n", c->booted_cores);
	seq_म_लिखो(m, "apicid\t\t: %d\n", c->apicid);
	seq_म_लिखो(m, "initial apicid\t: %d\n", c->initial_apicid);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल व्योम show_cpuinfo_misc(काष्ठा seq_file *m, काष्ठा cpuinfo_x86 *c)
अणु
	seq_म_लिखो(m,
		   "fdiv_bug\t: %s\n"
		   "f00f_bug\t: %s\n"
		   "coma_bug\t: %s\n"
		   "fpu\t\t: %s\n"
		   "fpu_exception\t: %s\n"
		   "cpuid level\t: %d\n"
		   "wp\t\t: yes\n",
		   boot_cpu_has_bug(X86_BUG_FDIV) ? "yes" : "no",
		   boot_cpu_has_bug(X86_BUG_F00F) ? "yes" : "no",
		   boot_cpu_has_bug(X86_BUG_COMA) ? "yes" : "no",
		   boot_cpu_has(X86_FEATURE_FPU) ? "yes" : "no",
		   boot_cpu_has(X86_FEATURE_FPU) ? "yes" : "no",
		   c->cpuid_level);
पूर्ण
#अन्यथा
अटल व्योम show_cpuinfo_misc(काष्ठा seq_file *m, काष्ठा cpuinfo_x86 *c)
अणु
	seq_म_लिखो(m,
		   "fpu\t\t: yes\n"
		   "fpu_exception\t: yes\n"
		   "cpuid level\t: %d\n"
		   "wp\t\t: yes\n",
		   c->cpuid_level);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा cpuinfo_x86 *c = v;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक i;

	cpu = c->cpu_index;
	seq_म_लिखो(m, "processor\t: %u\n"
		   "vendor_id\t: %s\n"
		   "cpu family\t: %d\n"
		   "model\t\t: %u\n"
		   "model name\t: %s\n",
		   cpu,
		   c->x86_venकरोr_id[0] ? c->x86_venकरोr_id : "unknown",
		   c->x86,
		   c->x86_model,
		   c->x86_model_id[0] ? c->x86_model_id : "unknown");

	अगर (c->x86_stepping || c->cpuid_level >= 0)
		seq_म_लिखो(m, "stepping\t: %d\n", c->x86_stepping);
	अन्यथा
		seq_माला_दो(m, "stepping\t: unknown\n");
	अगर (c->microcode)
		seq_म_लिखो(m, "microcode\t: 0x%x\n", c->microcode);

	अगर (cpu_has(c, X86_FEATURE_TSC)) अणु
		अचिन्हित पूर्णांक freq = aperfmperf_get_khz(cpu);

		अगर (!freq)
			freq = cpufreq_quick_get(cpu);
		अगर (!freq)
			freq = cpu_khz;
		seq_म_लिखो(m, "cpu MHz\t\t: %u.%03u\n",
			   freq / 1000, (freq % 1000));
	पूर्ण

	/* Cache size */
	अगर (c->x86_cache_size)
		seq_म_लिखो(m, "cache size\t: %u KB\n", c->x86_cache_size);

	show_cpuinfo_core(m, c, cpu);
	show_cpuinfo_misc(m, c);

	seq_माला_दो(m, "flags\t\t:");
	क्रम (i = 0; i < 32*NCAPINTS; i++)
		अगर (cpu_has(c, i) && x86_cap_flags[i] != शून्य)
			seq_म_लिखो(m, " %s", x86_cap_flags[i]);

#अगर_घोषित CONFIG_X86_VMX_FEATURE_NAMES
	अगर (cpu_has(c, X86_FEATURE_VMX) && c->vmx_capability[0]) अणु
		seq_माला_दो(m, "\nvmx flags\t:");
		क्रम (i = 0; i < 32*NVMXINTS; i++) अणु
			अगर (test_bit(i, (अचिन्हित दीर्घ *)c->vmx_capability) &&
			    x86_vmx_flags[i] != शून्य)
				seq_म_लिखो(m, " %s", x86_vmx_flags[i]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	seq_माला_दो(m, "\nbugs\t\t:");
	क्रम (i = 0; i < 32*NBUGINTS; i++) अणु
		अचिन्हित पूर्णांक bug_bit = 32*NCAPINTS + i;

		अगर (cpu_has_bug(c, bug_bit) && x86_bug_flags[i])
			seq_म_लिखो(m, " %s", x86_bug_flags[i]);
	पूर्ण

	seq_म_लिखो(m, "\nbogomips\t: %lu.%02lu\n",
		   c->loops_per_jअगरfy/(500000/HZ),
		   (c->loops_per_jअगरfy/(5000/HZ)) % 100);

#अगर_घोषित CONFIG_X86_64
	अगर (c->x86_tlbsize > 0)
		seq_म_लिखो(m, "TLB size\t: %d 4K pages\n", c->x86_tlbsize);
#पूर्ण_अगर
	seq_म_लिखो(m, "clflush size\t: %u\n", c->x86_clflush_size);
	seq_म_लिखो(m, "cache_alignment\t: %d\n", c->x86_cache_alignment);
	seq_म_लिखो(m, "address sizes\t: %u bits physical, %u bits virtual\n",
		   c->x86_phys_bits, c->x86_virt_bits);

	seq_माला_दो(m, "power management:");
	क्रम (i = 0; i < 32; i++) अणु
		अगर (c->x86_घातer & (1 << i)) अणु
			अगर (i < ARRAY_SIZE(x86_घातer_flags) &&
			    x86_घातer_flags[i])
				seq_म_लिखो(m, "%s%s",
					   x86_घातer_flags[i][0] ? " " : "",
					   x86_घातer_flags[i]);
			अन्यथा
				seq_म_लिखो(m, " [%d]", i);
		पूर्ण
	पूर्ण

	seq_माला_दो(m, "\n\n");

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	*pos = cpumask_next(*pos - 1, cpu_online_mask);
	अगर ((*pos) < nr_cpu_ids)
		वापस &cpu_data(*pos);
	वापस शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;
