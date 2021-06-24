<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* cpu_feature_enabled() cannot be used this early */
#घोषणा USE_EARLY_PGTABLE_L5

#समावेश <linux/memblock.h>
#समावेश <linux/linkage.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/smt.h>
#समावेश <linux/init.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cmdline.h>
#समावेश <यंत्र/stackprotector.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/द्विगुनfault.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/vsyscall.h>
#समावेश <linux/topology.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/hwcap2.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/microcode.h>
#समावेश <यंत्र/microcode_पूर्णांकel.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/uv/uv.h>

#समावेश "cpu.h"

u32 elf_hwcap2 __पढ़ो_mostly;

/* all of these masks are initialized in setup_cpu_local_masks() */
cpumask_var_t cpu_initialized_mask;
cpumask_var_t cpu_callout_mask;
cpumask_var_t cpu_callin_mask;

/* representing cpus क्रम which sibling maps can be computed */
cpumask_var_t cpu_sibling_setup_mask;

/* Number of siblings per CPU package */
पूर्णांक smp_num_siblings = 1;
EXPORT_SYMBOL(smp_num_siblings);

/* Last level cache ID of each logical CPU */
DEFINE_PER_CPU_READ_MOSTLY(u16, cpu_llc_id) = BAD_APICID;

/* correctly size the local cpu masks */
व्योम __init setup_cpu_local_masks(व्योम)
अणु
	alloc_booपंचांगem_cpumask_var(&cpu_initialized_mask);
	alloc_booपंचांगem_cpumask_var(&cpu_callin_mask);
	alloc_booपंचांगem_cpumask_var(&cpu_callout_mask);
	alloc_booपंचांगem_cpumask_var(&cpu_sibling_setup_mask);
पूर्ण

अटल व्योम शेष_init(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_64
	cpu_detect_cache_sizes(c);
#अन्यथा
	/* Not much we can करो here... */
	/* Check अगर at least it has cpuid */
	अगर (c->cpuid_level == -1) अणु
		/* No cpuid. It must be an ancient CPU */
		अगर (c->x86 == 4)
			म_नकल(c->x86_model_id, "486");
		अन्यथा अगर (c->x86 == 3)
			म_नकल(c->x86_model_id, "386");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा cpu_dev शेष_cpu = अणु
	.c_init		= शेष_init,
	.c_venकरोr	= "Unknown",
	.c_x86_venकरोr	= X86_VENDOR_UNKNOWN,
पूर्ण;

अटल स्थिर काष्ठा cpu_dev *this_cpu = &शेष_cpu;

DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा gdt_page, gdt_page) = अणु .gdt = अणु
#अगर_घोषित CONFIG_X86_64
	/*
	 * We need valid kernel segments क्रम data and code in दीर्घ mode too
	 * IRET will check the segment types  kkeil 2000/10/28
	 * Also sysret mandates a special GDT layout
	 *
	 * TLS descriptors are currently at a dअगरferent place compared to i386.
	 * Hopefully nobody expects them at a fixed place (Wine?)
	 */
	[GDT_ENTRY_KERNEL32_CS]		= GDT_ENTRY_INIT(0xc09b, 0, 0xfffff),
	[GDT_ENTRY_KERNEL_CS]		= GDT_ENTRY_INIT(0xa09b, 0, 0xfffff),
	[GDT_ENTRY_KERNEL_DS]		= GDT_ENTRY_INIT(0xc093, 0, 0xfffff),
	[GDT_ENTRY_DEFAULT_USER32_CS]	= GDT_ENTRY_INIT(0xc0fb, 0, 0xfffff),
	[GDT_ENTRY_DEFAULT_USER_DS]	= GDT_ENTRY_INIT(0xc0f3, 0, 0xfffff),
	[GDT_ENTRY_DEFAULT_USER_CS]	= GDT_ENTRY_INIT(0xa0fb, 0, 0xfffff),
#अन्यथा
	[GDT_ENTRY_KERNEL_CS]		= GDT_ENTRY_INIT(0xc09a, 0, 0xfffff),
	[GDT_ENTRY_KERNEL_DS]		= GDT_ENTRY_INIT(0xc092, 0, 0xfffff),
	[GDT_ENTRY_DEFAULT_USER_CS]	= GDT_ENTRY_INIT(0xc0fa, 0, 0xfffff),
	[GDT_ENTRY_DEFAULT_USER_DS]	= GDT_ENTRY_INIT(0xc0f2, 0, 0xfffff),
	/*
	 * Segments used क्रम calling PnP BIOS have byte granularity.
	 * They code segments and data segments have fixed 64k limits,
	 * the transfer segment sizes are set at run समय.
	 */
	/* 32-bit code */
	[GDT_ENTRY_PNPBIOS_CS32]	= GDT_ENTRY_INIT(0x409a, 0, 0xffff),
	/* 16-bit code */
	[GDT_ENTRY_PNPBIOS_CS16]	= GDT_ENTRY_INIT(0x009a, 0, 0xffff),
	/* 16-bit data */
	[GDT_ENTRY_PNPBIOS_DS]		= GDT_ENTRY_INIT(0x0092, 0, 0xffff),
	/* 16-bit data */
	[GDT_ENTRY_PNPBIOS_TS1]		= GDT_ENTRY_INIT(0x0092, 0, 0),
	/* 16-bit data */
	[GDT_ENTRY_PNPBIOS_TS2]		= GDT_ENTRY_INIT(0x0092, 0, 0),
	/*
	 * The APM segments have byte granularity and their bases
	 * are set at run समय.  All have 64k limits.
	 */
	/* 32-bit code */
	[GDT_ENTRY_APMBIOS_BASE]	= GDT_ENTRY_INIT(0x409a, 0, 0xffff),
	/* 16-bit code */
	[GDT_ENTRY_APMBIOS_BASE+1]	= GDT_ENTRY_INIT(0x009a, 0, 0xffff),
	/* data */
	[GDT_ENTRY_APMBIOS_BASE+2]	= GDT_ENTRY_INIT(0x4092, 0, 0xffff),

	[GDT_ENTRY_ESPFIX_SS]		= GDT_ENTRY_INIT(0xc092, 0, 0xfffff),
	[GDT_ENTRY_PERCPU]		= GDT_ENTRY_INIT(0xc092, 0, 0xfffff),
#पूर्ण_अगर
पूर्ण पूर्ण;
EXPORT_PER_CPU_SYMBOL_GPL(gdt_page);

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक __init x86_nopcid_setup(अक्षर *s)
अणु
	/* nopcid करोesn't accept parameters */
	अगर (s)
		वापस -EINVAL;

	/* करो not emit a message अगर the feature is not present */
	अगर (!boot_cpu_has(X86_FEATURE_PCID))
		वापस 0;

	setup_clear_cpu_cap(X86_FEATURE_PCID);
	pr_info("nopcid: PCID feature disabled\n");
	वापस 0;
पूर्ण
early_param("nopcid", x86_nopcid_setup);
#पूर्ण_अगर

अटल पूर्णांक __init x86_noinvpcid_setup(अक्षर *s)
अणु
	/* noinvpcid करोesn't accept parameters */
	अगर (s)
		वापस -EINVAL;

	/* करो not emit a message अगर the feature is not present */
	अगर (!boot_cpu_has(X86_FEATURE_INVPCID))
		वापस 0;

	setup_clear_cpu_cap(X86_FEATURE_INVPCID);
	pr_info("noinvpcid: INVPCID feature disabled\n");
	वापस 0;
पूर्ण
early_param("noinvpcid", x86_noinvpcid_setup);

#अगर_घोषित CONFIG_X86_32
अटल पूर्णांक cachesize_override = -1;
अटल पूर्णांक disable_x86_serial_nr = 1;

अटल पूर्णांक __init cachesize_setup(अक्षर *str)
अणु
	get_option(&str, &cachesize_override);
	वापस 1;
पूर्ण
__setup("cachesize=", cachesize_setup);

अटल पूर्णांक __init x86_sep_setup(अक्षर *s)
अणु
	setup_clear_cpu_cap(X86_FEATURE_SEP);
	वापस 1;
पूर्ण
__setup("nosep", x86_sep_setup);

/* Standard macro to see अगर a specअगरic flag is changeable */
अटल अंतरभूत पूर्णांक flag_is_changeable_p(u32 flag)
अणु
	u32 f1, f2;

	/*
	 * Cyrix and IDT cpus allow disabling of CPUID
	 * so the code below may वापस dअगरferent results
	 * when it is executed beक्रमe and after enabling
	 * the CPUID. Add "volatile" to not allow gcc to
	 * optimize the subsequent calls to this function.
	 */
	यंत्र अस्थिर ("pushfl		\n\t"
		      "pushfl		\n\t"
		      "popl %0		\n\t"
		      "movl %0, %1	\n\t"
		      "xorl %2, %0	\n\t"
		      "pushl %0		\n\t"
		      "popfl		\n\t"
		      "pushfl		\n\t"
		      "popl %0		\n\t"
		      "popfl		\n\t"

		      : "=&r" (f1), "=&r" (f2)
		      : "ir" (flag));

	वापस ((f1^f2) & flag) != 0;
पूर्ण

/* Probe क्रम the CPUID inकाष्ठाion */
पूर्णांक have_cpuid_p(व्योम)
अणु
	वापस flag_is_changeable_p(X86_EFLAGS_ID);
पूर्ण

अटल व्योम squash_the_stupid_serial_number(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित दीर्घ lo, hi;

	अगर (!cpu_has(c, X86_FEATURE_PN) || !disable_x86_serial_nr)
		वापस;

	/* Disable processor serial number: */

	rdmsr(MSR_IA32_BBL_CR_CTL, lo, hi);
	lo |= 0x200000;
	wrmsr(MSR_IA32_BBL_CR_CTL, lo, hi);

	pr_notice("CPU serial number disabled.\n");
	clear_cpu_cap(c, X86_FEATURE_PN);

	/* Disabling the serial number may affect the cpuid level */
	c->cpuid_level = cpuid_eax(0);
पूर्ण

अटल पूर्णांक __init x86_serial_nr_setup(अक्षर *s)
अणु
	disable_x86_serial_nr = 0;
	वापस 1;
पूर्ण
__setup("serialnumber", x86_serial_nr_setup);
#अन्यथा
अटल अंतरभूत पूर्णांक flag_is_changeable_p(u32 flag)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत व्योम squash_the_stupid_serial_number(काष्ठा cpuinfo_x86 *c)
अणु
पूर्ण
#पूर्ण_अगर

अटल __init पूर्णांक setup_disable_smep(अक्षर *arg)
अणु
	setup_clear_cpu_cap(X86_FEATURE_SMEP);
	वापस 1;
पूर्ण
__setup("nosmep", setup_disable_smep);

अटल __always_अंतरभूत व्योम setup_smep(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (cpu_has(c, X86_FEATURE_SMEP))
		cr4_set_bits(X86_CR4_SMEP);
पूर्ण

अटल __init पूर्णांक setup_disable_smap(अक्षर *arg)
अणु
	setup_clear_cpu_cap(X86_FEATURE_SMAP);
	वापस 1;
पूर्ण
__setup("nosmap", setup_disable_smap);

अटल __always_अंतरभूत व्योम setup_smap(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित दीर्घ eflags = native_save_fl();

	/* This should have been cleared दीर्घ ago */
	BUG_ON(eflags & X86_EFLAGS_AC);

	अगर (cpu_has(c, X86_FEATURE_SMAP)) अणु
#अगर_घोषित CONFIG_X86_SMAP
		cr4_set_bits(X86_CR4_SMAP);
#अन्यथा
		cr4_clear_bits(X86_CR4_SMAP);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम setup_umip(काष्ठा cpuinfo_x86 *c)
अणु
	/* Check the boot processor, plus build option क्रम UMIP. */
	अगर (!cpu_feature_enabled(X86_FEATURE_UMIP))
		जाओ out;

	/* Check the current processor's cpuid bits. */
	अगर (!cpu_has(c, X86_FEATURE_UMIP))
		जाओ out;

	cr4_set_bits(X86_CR4_UMIP);

	pr_info_once("x86/cpu: User Mode Instruction Prevention (UMIP) activated\n");

	वापस;

out:
	/*
	 * Make sure UMIP is disabled in हाल it was enabled in a
	 * previous boot (e.g., via kexec).
	 */
	cr4_clear_bits(X86_CR4_UMIP);
पूर्ण

/* These bits should not change their value after CPU init is finished. */
अटल स्थिर अचिन्हित दीर्घ cr4_pinned_mask =
	X86_CR4_SMEP | X86_CR4_SMAP | X86_CR4_UMIP | X86_CR4_FSGSBASE;
अटल DEFINE_STATIC_KEY_FALSE_RO(cr_pinning);
अटल अचिन्हित दीर्घ cr4_pinned_bits __ro_after_init;

व्योम native_ग_लिखो_cr0(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ bits_missing = 0;

set_रेजिस्टर:
	यंत्र अस्थिर("mov %0,%%cr0": "+r" (val) : : "memory");

	अगर (अटल_branch_likely(&cr_pinning)) अणु
		अगर (unlikely((val & X86_CR0_WP) != X86_CR0_WP)) अणु
			bits_missing = X86_CR0_WP;
			val |= bits_missing;
			जाओ set_रेजिस्टर;
		पूर्ण
		/* Warn after we've set the missing bits. */
		WARN_ONCE(bits_missing, "CR0 WP bit went missing!?\n");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(native_ग_लिखो_cr0);

व्योम native_ग_लिखो_cr4(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ bits_changed = 0;

set_रेजिस्टर:
	यंत्र अस्थिर("mov %0,%%cr4": "+r" (val) : : "memory");

	अगर (अटल_branch_likely(&cr_pinning)) अणु
		अगर (unlikely((val & cr4_pinned_mask) != cr4_pinned_bits)) अणु
			bits_changed = (val & cr4_pinned_mask) ^ cr4_pinned_bits;
			val = (val & ~cr4_pinned_mask) | cr4_pinned_bits;
			जाओ set_रेजिस्टर;
		पूर्ण
		/* Warn after we've corrected the changed bits. */
		WARN_ONCE(bits_changed, "pinned CR4 bits changed: 0x%lx!?\n",
			  bits_changed);
	पूर्ण
पूर्ण
#अगर IS_MODULE(CONFIG_LKDTM)
EXPORT_SYMBOL_GPL(native_ग_लिखो_cr4);
#पूर्ण_अगर

व्योम cr4_update_irqsoff(अचिन्हित दीर्घ set, अचिन्हित दीर्घ clear)
अणु
	अचिन्हित दीर्घ newval, cr4 = this_cpu_पढ़ो(cpu_tlbstate.cr4);

	lockdep_निश्चित_irqs_disabled();

	newval = (cr4 & ~clear) | set;
	अगर (newval != cr4) अणु
		this_cpu_ग_लिखो(cpu_tlbstate.cr4, newval);
		__ग_लिखो_cr4(newval);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cr4_update_irqsoff);

/* Read the CR4 shaकरोw. */
अचिन्हित दीर्घ cr4_पढ़ो_shaकरोw(व्योम)
अणु
	वापस this_cpu_पढ़ो(cpu_tlbstate.cr4);
पूर्ण
EXPORT_SYMBOL_GPL(cr4_पढ़ो_shaकरोw);

व्योम cr4_init(व्योम)
अणु
	अचिन्हित दीर्घ cr4 = __पढ़ो_cr4();

	अगर (boot_cpu_has(X86_FEATURE_PCID))
		cr4 |= X86_CR4_PCIDE;
	अगर (अटल_branch_likely(&cr_pinning))
		cr4 = (cr4 & ~cr4_pinned_mask) | cr4_pinned_bits;

	__ग_लिखो_cr4(cr4);

	/* Initialize cr4 shaकरोw क्रम this CPU. */
	this_cpu_ग_लिखो(cpu_tlbstate.cr4, cr4);
पूर्ण

/*
 * Once CPU feature detection is finished (and boot params have been
 * parsed), record any of the sensitive CR bits that are set, and
 * enable CR pinning.
 */
अटल व्योम __init setup_cr_pinning(व्योम)
अणु
	cr4_pinned_bits = this_cpu_पढ़ो(cpu_tlbstate.cr4) & cr4_pinned_mask;
	अटल_key_enable(&cr_pinning.key);
पूर्ण

अटल __init पूर्णांक x86_nofsgsbase_setup(अक्षर *arg)
अणु
	/* Require an exact match without trailing अक्षरacters. */
	अगर (म_माप(arg))
		वापस 0;

	/* Do not emit a message अगर the feature is not present. */
	अगर (!boot_cpu_has(X86_FEATURE_FSGSBASE))
		वापस 1;

	setup_clear_cpu_cap(X86_FEATURE_FSGSBASE);
	pr_info("FSGSBASE disabled via kernel command line\n");
	वापस 1;
पूर्ण
__setup("nofsgsbase", x86_nofsgsbase_setup);

/*
 * Protection Keys are not available in 32-bit mode.
 */
अटल bool pku_disabled;

अटल __always_अंतरभूत व्योम setup_pku(काष्ठा cpuinfo_x86 *c)
अणु
	काष्ठा pkru_state *pk;

	/* check the boot processor, plus compile options क्रम PKU: */
	अगर (!cpu_feature_enabled(X86_FEATURE_PKU))
		वापस;
	/* checks the actual processor's cpuid bits: */
	अगर (!cpu_has(c, X86_FEATURE_PKU))
		वापस;
	अगर (pku_disabled)
		वापस;

	cr4_set_bits(X86_CR4_PKE);
	pk = get_xsave_addr(&init_fpstate.xsave, XFEATURE_PKRU);
	अगर (pk)
		pk->pkru = init_pkru_value;
	/*
	 * Setting X86_CR4_PKE will cause the X86_FEATURE_OSPKE
	 * cpuid bit to be set.  We need to ensure that we
	 * update that bit in this CPU's "cpu_info".
	 */
	set_cpu_cap(c, X86_FEATURE_OSPKE);
पूर्ण

#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
अटल __init पूर्णांक setup_disable_pku(अक्षर *arg)
अणु
	/*
	 * Do not clear the X86_FEATURE_PKU bit.  All of the
	 * runसमय checks are against OSPKE so clearing the
	 * bit करोes nothing.
	 *
	 * This way, we will see "pku" in cpuinfo, but not
	 * "ospke", which is exactly what we want.  It shows
	 * that the CPU has PKU, but the OS has not enabled it.
	 * This happens to be exactly how a प्रणाली would look
	 * अगर we disabled the config option.
	 */
	pr_info("x86: 'nopku' specified, disabling Memory Protection Keys\n");
	pku_disabled = true;
	वापस 1;
पूर्ण
__setup("nopku", setup_disable_pku);
#पूर्ण_अगर /* CONFIG_X86_64 */

/*
 * Some CPU features depend on higher CPUID levels, which may not always
 * be available due to CPUID level capping or broken भवization
 * software.  Add those features to this table to स्वतः-disable them.
 */
काष्ठा cpuid_dependent_feature अणु
	u32 feature;
	u32 level;
पूर्ण;

अटल स्थिर काष्ठा cpuid_dependent_feature
cpuid_dependent_features[] = अणु
	अणु X86_FEATURE_MWAIT,		0x00000005 पूर्ण,
	अणु X86_FEATURE_DCA,		0x00000009 पूर्ण,
	अणु X86_FEATURE_XSAVE,		0x0000000d पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

अटल व्योम filter_cpuid_features(काष्ठा cpuinfo_x86 *c, bool warn)
अणु
	स्थिर काष्ठा cpuid_dependent_feature *df;

	क्रम (df = cpuid_dependent_features; df->feature; df++) अणु

		अगर (!cpu_has(c, df->feature))
			जारी;
		/*
		 * Note: cpuid_level is set to -1 अगर unavailable, but
		 * extended_extended_level is set to 0 अगर unavailable
		 * and the legitimate extended levels are all negative
		 * when चिन्हित; hence the weird messing around with
		 * signs here...
		 */
		अगर (!((s32)df->level < 0 ?
		     (u32)df->level > (u32)c->extended_cpuid_level :
		     (s32)df->level > (s32)c->cpuid_level))
			जारी;

		clear_cpu_cap(c, df->feature);
		अगर (!warn)
			जारी;

		pr_warn("CPU: CPU feature " X86_CAP_FMT " disabled, no CPUID level 0x%x\n",
			x86_cap_flag(df->feature), df->level);
	पूर्ण
पूर्ण

/*
 * Naming convention should be: <Name> [(<Codename>)]
 * This table only is used unless init_<venकरोr>() below करोesn't set it;
 * in particular, अगर CPUID levels 0x80000002..4 are supported, this
 * isn't used
 */

/* Look up CPU names by table lookup. */
अटल स्थिर अक्षर *table_lookup_model(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
	स्थिर काष्ठा legacy_cpu_model_info *info;

	अगर (c->x86_model >= 16)
		वापस शून्य;	/* Range check */

	अगर (!this_cpu)
		वापस शून्य;

	info = this_cpu->legacy_models;

	जबतक (info->family) अणु
		अगर (info->family == c->x86)
			वापस info->model_names[c->x86_model];
		info++;
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;		/* Not found */
पूर्ण

/* Aligned to अचिन्हित दीर्घ to aव्योम split lock in atomic biपंचांगap ops */
__u32 cpu_caps_cleared[NCAPINTS + NBUGINTS] __aligned(माप(अचिन्हित दीर्घ));
__u32 cpu_caps_set[NCAPINTS + NBUGINTS] __aligned(माप(अचिन्हित दीर्घ));

व्योम load_percpu_segment(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_X86_32
	loadsegment(fs, __KERNEL_PERCPU);
#अन्यथा
	__loadsegment_simple(gs, 0);
	wrmsrl(MSR_GS_BASE, cpu_kernelmode_gs_base(cpu));
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_X86_32
/* The 32-bit entry code needs to find cpu_entry_area. */
DEFINE_PER_CPU(काष्ठा cpu_entry_area *, cpu_entry_area);
#पूर्ण_अगर

/* Load the original GDT from the per-cpu काष्ठाure */
व्योम load_direct_gdt(पूर्णांक cpu)
अणु
	काष्ठा desc_ptr gdt_descr;

	gdt_descr.address = (दीर्घ)get_cpu_gdt_rw(cpu);
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);
पूर्ण
EXPORT_SYMBOL_GPL(load_direct_gdt);

/* Load a fixmap remapping of the per-cpu GDT */
व्योम load_fixmap_gdt(पूर्णांक cpu)
अणु
	काष्ठा desc_ptr gdt_descr;

	gdt_descr.address = (दीर्घ)get_cpu_gdt_ro(cpu);
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);
पूर्ण
EXPORT_SYMBOL_GPL(load_fixmap_gdt);

/*
 * Current gdt poपूर्णांकs %fs at the "master" per-cpu area: after this,
 * it's on the real one.
 */
व्योम चयन_to_new_gdt(पूर्णांक cpu)
अणु
	/* Load the original GDT */
	load_direct_gdt(cpu);
	/* Reload the per-cpu base */
	load_percpu_segment(cpu);
पूर्ण

अटल स्थिर काष्ठा cpu_dev *cpu_devs[X86_VENDOR_NUM] = अणुपूर्ण;

अटल व्योम get_model_name(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक *v;
	अक्षर *p, *q, *s;

	अगर (c->extended_cpuid_level < 0x80000004)
		वापस;

	v = (अचिन्हित पूर्णांक *)c->x86_model_id;
	cpuid(0x80000002, &v[0], &v[1], &v[2], &v[3]);
	cpuid(0x80000003, &v[4], &v[5], &v[6], &v[7]);
	cpuid(0x80000004, &v[8], &v[9], &v[10], &v[11]);
	c->x86_model_id[48] = 0;

	/* Trim whitespace */
	p = q = s = &c->x86_model_id[0];

	जबतक (*p == ' ')
		p++;

	जबतक (*p) अणु
		/* Note the last non-whitespace index */
		अगर (!है_खाली(*p))
			s = q;

		*q++ = *p++;
	पूर्ण

	*(s + 1) = '\0';
पूर्ण

व्योम detect_num_cpu_cores(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	c->x86_max_cores = 1;
	अगर (!IS_ENABLED(CONFIG_SMP) || c->cpuid_level < 4)
		वापस;

	cpuid_count(4, 0, &eax, &ebx, &ecx, &edx);
	अगर (eax & 0x1f)
		c->x86_max_cores = (eax >> 26) + 1;
पूर्ण

व्योम cpu_detect_cache_sizes(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक n, dummy, ebx, ecx, edx, l2size;

	n = c->extended_cpuid_level;

	अगर (n >= 0x80000005) अणु
		cpuid(0x80000005, &dummy, &ebx, &ecx, &edx);
		c->x86_cache_size = (ecx>>24) + (edx>>24);
#अगर_घोषित CONFIG_X86_64
		/* On K8 L1 TLB is inclusive, so करोn't count it */
		c->x86_tlbsize = 0;
#पूर्ण_अगर
	पूर्ण

	अगर (n < 0x80000006)	/* Some chips just has a large L1. */
		वापस;

	cpuid(0x80000006, &dummy, &ebx, &ecx, &edx);
	l2size = ecx >> 16;

#अगर_घोषित CONFIG_X86_64
	c->x86_tlbsize += ((ebx >> 16) & 0xfff) + (ebx & 0xfff);
#अन्यथा
	/* करो processor-specअगरic cache resizing */
	अगर (this_cpu->legacy_cache_size)
		l2size = this_cpu->legacy_cache_size(c, l2size);

	/* Allow user to override all this अगर necessary. */
	अगर (cachesize_override != -1)
		l2size = cachesize_override;

	अगर (l2size == 0)
		वापस;		/* Again, no L2 cache is possible */
#पूर्ण_अगर

	c->x86_cache_size = l2size;
पूर्ण

u16 __पढ़ो_mostly tlb_lli_4k[NR_INFO];
u16 __पढ़ो_mostly tlb_lli_2m[NR_INFO];
u16 __पढ़ो_mostly tlb_lli_4m[NR_INFO];
u16 __पढ़ो_mostly tlb_lld_4k[NR_INFO];
u16 __पढ़ो_mostly tlb_lld_2m[NR_INFO];
u16 __पढ़ो_mostly tlb_lld_4m[NR_INFO];
u16 __पढ़ो_mostly tlb_lld_1g[NR_INFO];

अटल व्योम cpu_detect_tlb(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (this_cpu->c_detect_tlb)
		this_cpu->c_detect_tlb(c);

	pr_info("Last level iTLB entries: 4KB %d, 2MB %d, 4MB %d\n",
		tlb_lli_4k[ENTRIES], tlb_lli_2m[ENTRIES],
		tlb_lli_4m[ENTRIES]);

	pr_info("Last level dTLB entries: 4KB %d, 2MB %d, 4MB %d, 1GB %d\n",
		tlb_lld_4k[ENTRIES], tlb_lld_2m[ENTRIES],
		tlb_lld_4m[ENTRIES], tlb_lld_1g[ENTRIES]);
पूर्ण

पूर्णांक detect_ht_early(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	u32 eax, ebx, ecx, edx;

	अगर (!cpu_has(c, X86_FEATURE_HT))
		वापस -1;

	अगर (cpu_has(c, X86_FEATURE_CMP_LEGACY))
		वापस -1;

	अगर (cpu_has(c, X86_FEATURE_XTOPOLOGY))
		वापस -1;

	cpuid(1, &eax, &ebx, &ecx, &edx);

	smp_num_siblings = (ebx & 0xff0000) >> 16;
	अगर (smp_num_siblings == 1)
		pr_info_once("CPU0: Hyper-Threading is disabled\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम detect_ht(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	पूर्णांक index_msb, core_bits;

	अगर (detect_ht_early(c) < 0)
		वापस;

	index_msb = get_count_order(smp_num_siblings);
	c->phys_proc_id = apic->phys_pkg_id(c->initial_apicid, index_msb);

	smp_num_siblings = smp_num_siblings / c->x86_max_cores;

	index_msb = get_count_order(smp_num_siblings);

	core_bits = get_count_order(c->x86_max_cores);

	c->cpu_core_id = apic->phys_pkg_id(c->initial_apicid, index_msb) &
				       ((1 << core_bits) - 1);
#पूर्ण_अगर
पूर्ण

अटल व्योम get_cpu_venकरोr(काष्ठा cpuinfo_x86 *c)
अणु
	अक्षर *v = c->x86_venकरोr_id;
	पूर्णांक i;

	क्रम (i = 0; i < X86_VENDOR_NUM; i++) अणु
		अगर (!cpu_devs[i])
			अवरोध;

		अगर (!म_भेद(v, cpu_devs[i]->c_ident[0]) ||
		    (cpu_devs[i]->c_ident[1] &&
		     !म_भेद(v, cpu_devs[i]->c_ident[1]))) अणु

			this_cpu = cpu_devs[i];
			c->x86_venकरोr = this_cpu->c_x86_venकरोr;
			वापस;
		पूर्ण
	पूर्ण

	pr_err_once("CPU: vendor_id '%s' unknown, using generic init.\n" \
		    "CPU: Your system may be unstable.\n", v);

	c->x86_venकरोr = X86_VENDOR_UNKNOWN;
	this_cpu = &शेष_cpu;
पूर्ण

व्योम cpu_detect(काष्ठा cpuinfo_x86 *c)
अणु
	/* Get venकरोr name */
	cpuid(0x00000000, (अचिन्हित पूर्णांक *)&c->cpuid_level,
	      (अचिन्हित पूर्णांक *)&c->x86_venकरोr_id[0],
	      (अचिन्हित पूर्णांक *)&c->x86_venकरोr_id[8],
	      (अचिन्हित पूर्णांक *)&c->x86_venकरोr_id[4]);

	c->x86 = 4;
	/* Intel-defined flags: level 0x00000001 */
	अगर (c->cpuid_level >= 0x00000001) अणु
		u32 junk, tfms, cap0, misc;

		cpuid(0x00000001, &tfms, &misc, &junk, &cap0);
		c->x86		= x86_family(tfms);
		c->x86_model	= x86_model(tfms);
		c->x86_stepping	= x86_stepping(tfms);

		अगर (cap0 & (1<<19)) अणु
			c->x86_clflush_size = ((misc >> 8) & 0xff) * 8;
			c->x86_cache_alignment = c->x86_clflush_size;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम apply_क्रमced_caps(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NCAPINTS + NBUGINTS; i++) अणु
		c->x86_capability[i] &= ~cpu_caps_cleared[i];
		c->x86_capability[i] |= cpu_caps_set[i];
	पूर्ण
पूर्ण

अटल व्योम init_speculation_control(काष्ठा cpuinfo_x86 *c)
अणु
	/*
	 * The Intel SPEC_CTRL CPUID bit implies IBRS and IBPB support,
	 * and they also have a dअगरferent bit क्रम STIBP support. Also,
	 * a hypervisor might have set the inभागidual AMD bits even on
	 * Intel CPUs, क्रम finer-grained selection of what's available.
	 */
	अगर (cpu_has(c, X86_FEATURE_SPEC_CTRL)) अणु
		set_cpu_cap(c, X86_FEATURE_IBRS);
		set_cpu_cap(c, X86_FEATURE_IBPB);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_INTEL_STIBP))
		set_cpu_cap(c, X86_FEATURE_STIBP);

	अगर (cpu_has(c, X86_FEATURE_SPEC_CTRL_SSBD) ||
	    cpu_has(c, X86_FEATURE_VIRT_SSBD))
		set_cpu_cap(c, X86_FEATURE_SSBD);

	अगर (cpu_has(c, X86_FEATURE_AMD_IBRS)) अणु
		set_cpu_cap(c, X86_FEATURE_IBRS);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_AMD_IBPB))
		set_cpu_cap(c, X86_FEATURE_IBPB);

	अगर (cpu_has(c, X86_FEATURE_AMD_STIBP)) अणु
		set_cpu_cap(c, X86_FEATURE_STIBP);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_AMD_SSBD)) अणु
		set_cpu_cap(c, X86_FEATURE_SSBD);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
		clear_cpu_cap(c, X86_FEATURE_VIRT_SSBD);
	पूर्ण
पूर्ण

व्योम get_cpu_cap(काष्ठा cpuinfo_x86 *c)
अणु
	u32 eax, ebx, ecx, edx;

	/* Intel-defined flags: level 0x00000001 */
	अगर (c->cpuid_level >= 0x00000001) अणु
		cpuid(0x00000001, &eax, &ebx, &ecx, &edx);

		c->x86_capability[CPUID_1_ECX] = ecx;
		c->x86_capability[CPUID_1_EDX] = edx;
	पूर्ण

	/* Thermal and Power Management Leaf: level 0x00000006 (eax) */
	अगर (c->cpuid_level >= 0x00000006)
		c->x86_capability[CPUID_6_EAX] = cpuid_eax(0x00000006);

	/* Additional Intel-defined flags: level 0x00000007 */
	अगर (c->cpuid_level >= 0x00000007) अणु
		cpuid_count(0x00000007, 0, &eax, &ebx, &ecx, &edx);
		c->x86_capability[CPUID_7_0_EBX] = ebx;
		c->x86_capability[CPUID_7_ECX] = ecx;
		c->x86_capability[CPUID_7_EDX] = edx;

		/* Check valid sub-leaf index beक्रमe accessing it */
		अगर (eax >= 1) अणु
			cpuid_count(0x00000007, 1, &eax, &ebx, &ecx, &edx);
			c->x86_capability[CPUID_7_1_EAX] = eax;
		पूर्ण
	पूर्ण

	/* Extended state features: level 0x0000000d */
	अगर (c->cpuid_level >= 0x0000000d) अणु
		cpuid_count(0x0000000d, 1, &eax, &ebx, &ecx, &edx);

		c->x86_capability[CPUID_D_1_EAX] = eax;
	पूर्ण

	/* AMD-defined flags: level 0x80000001 */
	eax = cpuid_eax(0x80000000);
	c->extended_cpuid_level = eax;

	अगर ((eax & 0xffff0000) == 0x80000000) अणु
		अगर (eax >= 0x80000001) अणु
			cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

			c->x86_capability[CPUID_8000_0001_ECX] = ecx;
			c->x86_capability[CPUID_8000_0001_EDX] = edx;
		पूर्ण
	पूर्ण

	अगर (c->extended_cpuid_level >= 0x80000007) अणु
		cpuid(0x80000007, &eax, &ebx, &ecx, &edx);

		c->x86_capability[CPUID_8000_0007_EBX] = ebx;
		c->x86_घातer = edx;
	पूर्ण

	अगर (c->extended_cpuid_level >= 0x80000008) अणु
		cpuid(0x80000008, &eax, &ebx, &ecx, &edx);
		c->x86_capability[CPUID_8000_0008_EBX] = ebx;
	पूर्ण

	अगर (c->extended_cpuid_level >= 0x8000000a)
		c->x86_capability[CPUID_8000_000A_EDX] = cpuid_edx(0x8000000a);

	अगर (c->extended_cpuid_level >= 0x8000001f)
		c->x86_capability[CPUID_8000_001F_EAX] = cpuid_eax(0x8000001f);

	init_scattered_cpuid_features(c);
	init_speculation_control(c);

	/*
	 * Clear/Set all flags overridden by options, after probe.
	 * This needs to happen each समय we re-probe, which may happen
	 * several बार during CPU initialization.
	 */
	apply_क्रमced_caps(c);
पूर्ण

व्योम get_cpu_address_sizes(काष्ठा cpuinfo_x86 *c)
अणु
	u32 eax, ebx, ecx, edx;

	अगर (c->extended_cpuid_level >= 0x80000008) अणु
		cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

		c->x86_virt_bits = (eax >> 8) & 0xff;
		c->x86_phys_bits = eax & 0xff;
	पूर्ण
#अगर_घोषित CONFIG_X86_32
	अन्यथा अगर (cpu_has(c, X86_FEATURE_PAE) || cpu_has(c, X86_FEATURE_PSE36))
		c->x86_phys_bits = 36;
#पूर्ण_अगर
	c->x86_cache_bits = c->x86_phys_bits;
पूर्ण

अटल व्योम identअगरy_cpu_without_cpuid(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
	पूर्णांक i;

	/*
	 * First of all, decide अगर this is a 486 or higher
	 * It's a 486 अगर we can modअगरy the AC flag
	 */
	अगर (flag_is_changeable_p(X86_EFLAGS_AC))
		c->x86 = 4;
	अन्यथा
		c->x86 = 3;

	क्रम (i = 0; i < X86_VENDOR_NUM; i++)
		अगर (cpu_devs[i] && cpu_devs[i]->c_identअगरy) अणु
			c->x86_venकरोr_id[0] = 0;
			cpu_devs[i]->c_identअगरy(c);
			अगर (c->x86_venकरोr_id[0]) अणु
				get_cpu_venकरोr(c);
				अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
पूर्ण

#घोषणा NO_SPECULATION		BIT(0)
#घोषणा NO_MELTDOWN		BIT(1)
#घोषणा NO_SSB			BIT(2)
#घोषणा NO_L1TF			BIT(3)
#घोषणा NO_MDS			BIT(4)
#घोषणा MSBDS_ONLY		BIT(5)
#घोषणा NO_SWAPGS		BIT(6)
#घोषणा NO_ITLB_MULTIHIT	BIT(7)
#घोषणा NO_SPECTRE_V2		BIT(8)

#घोषणा VULNWL(venकरोr, family, model, whitelist)	\
	X86_MATCH_VENDOR_FAM_MODEL(venकरोr, family, model, whitelist)

#घोषणा VULNWL_INTEL(model, whitelist)		\
	VULNWL(INTEL, 6, INTEL_FAM6_##model, whitelist)

#घोषणा VULNWL_AMD(family, whitelist)		\
	VULNWL(AMD, family, X86_MODEL_ANY, whitelist)

#घोषणा VULNWL_HYGON(family, whitelist)		\
	VULNWL(HYGON, family, X86_MODEL_ANY, whitelist)

अटल स्थिर __initस्थिर काष्ठा x86_cpu_id cpu_vuln_whitelist[] = अणु
	VULNWL(ANY,	4, X86_MODEL_ANY,	NO_SPECULATION),
	VULNWL(CENTAUR,	5, X86_MODEL_ANY,	NO_SPECULATION),
	VULNWL(INTEL,	5, X86_MODEL_ANY,	NO_SPECULATION),
	VULNWL(NSC,	5, X86_MODEL_ANY,	NO_SPECULATION),

	/* Intel Family 6 */
	VULNWL_INTEL(ATOM_SALTWELL,		NO_SPECULATION | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_SALTWELL_TABLET,	NO_SPECULATION | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_SALTWELL_MID,		NO_SPECULATION | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_BONNELL,		NO_SPECULATION | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_BONNELL_MID,		NO_SPECULATION | NO_ITLB_MULTIHIT),

	VULNWL_INTEL(ATOM_SILVERMONT,		NO_SSB | NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_SILVERMONT_D,		NO_SSB | NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_SILVERMONT_MID,	NO_SSB | NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_AIRMONT,		NO_SSB | NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(XEON_PHI_KNL,		NO_SSB | NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(XEON_PHI_KNM,		NO_SSB | NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),

	VULNWL_INTEL(CORE_YONAH,		NO_SSB),

	VULNWL_INTEL(ATOM_AIRMONT_MID,		NO_L1TF | MSBDS_ONLY | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_AIRMONT_NP,		NO_L1TF | NO_SWAPGS | NO_ITLB_MULTIHIT),

	VULNWL_INTEL(ATOM_GOLDMONT,		NO_MDS | NO_L1TF | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_GOLDMONT_D,		NO_MDS | NO_L1TF | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_INTEL(ATOM_GOLDMONT_PLUS,	NO_MDS | NO_L1TF | NO_SWAPGS | NO_ITLB_MULTIHIT),

	/*
	 * Technically, swapgs isn't serializing on AMD (despite it previously
	 * being करोcumented as such in the APM).  But according to AMD, %gs is
	 * updated non-speculatively, and the issuing of %gs-relative memory
	 * opeअक्रमs will be blocked until the %gs update completes, which is
	 * good enough क्रम our purposes.
	 */

	VULNWL_INTEL(ATOM_TREMONT_D,		NO_ITLB_MULTIHIT),

	/* AMD Family 0xf - 0x12 */
	VULNWL_AMD(0x0f,	NO_MELTDOWN | NO_SSB | NO_L1TF | NO_MDS | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_AMD(0x10,	NO_MELTDOWN | NO_SSB | NO_L1TF | NO_MDS | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_AMD(0x11,	NO_MELTDOWN | NO_SSB | NO_L1TF | NO_MDS | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_AMD(0x12,	NO_MELTDOWN | NO_SSB | NO_L1TF | NO_MDS | NO_SWAPGS | NO_ITLB_MULTIHIT),

	/* FAMILY_ANY must be last, otherwise 0x0f - 0x12 matches won't work */
	VULNWL_AMD(X86_FAMILY_ANY,	NO_MELTDOWN | NO_L1TF | NO_MDS | NO_SWAPGS | NO_ITLB_MULTIHIT),
	VULNWL_HYGON(X86_FAMILY_ANY,	NO_MELTDOWN | NO_L1TF | NO_MDS | NO_SWAPGS | NO_ITLB_MULTIHIT),

	/* Zhaoxin Family 7 */
	VULNWL(CENTAUR,	7, X86_MODEL_ANY,	NO_SPECTRE_V2 | NO_SWAPGS),
	VULNWL(ZHAOXIN,	7, X86_MODEL_ANY,	NO_SPECTRE_V2 | NO_SWAPGS),
	अणुपूर्ण
पूर्ण;

#घोषणा VULNBL_INTEL_STEPPINGS(model, steppings, issues)		   \
	X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE(INTEL, 6,		   \
					    INTEL_FAM6_##model, steppings, \
					    X86_FEATURE_ANY, issues)

#घोषणा SRBDS		BIT(0)

अटल स्थिर काष्ठा x86_cpu_id cpu_vuln_blacklist[] __initस्थिर = अणु
	VULNBL_INTEL_STEPPINGS(IVYBRIDGE,	X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(HASWELL,		X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(HASWELL_L,	X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(HASWELL_G,	X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(BROADWELL_G,	X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(BROADWELL,	X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(SKYLAKE_L,	X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(SKYLAKE,		X86_STEPPING_ANY,		SRBDS),
	VULNBL_INTEL_STEPPINGS(KABYLAKE_L,	X86_STEPPINGS(0x0, 0xC),	SRBDS),
	VULNBL_INTEL_STEPPINGS(KABYLAKE,	X86_STEPPINGS(0x0, 0xD),	SRBDS),
	अणुपूर्ण
पूर्ण;

अटल bool __init cpu_matches(स्थिर काष्ठा x86_cpu_id *table, अचिन्हित दीर्घ which)
अणु
	स्थिर काष्ठा x86_cpu_id *m = x86_match_cpu(table);

	वापस m && !!(m->driver_data & which);
पूर्ण

u64 x86_पढ़ो_arch_cap_msr(व्योम)
अणु
	u64 ia32_cap = 0;

	अगर (boot_cpu_has(X86_FEATURE_ARCH_CAPABILITIES))
		rdmsrl(MSR_IA32_ARCH_CAPABILITIES, ia32_cap);

	वापस ia32_cap;
पूर्ण

अटल व्योम __init cpu_set_bug_bits(काष्ठा cpuinfo_x86 *c)
अणु
	u64 ia32_cap = x86_पढ़ो_arch_cap_msr();

	/* Set ITLB_MULTIHIT bug अगर cpu is not in the whitelist and not mitigated */
	अगर (!cpu_matches(cpu_vuln_whitelist, NO_ITLB_MULTIHIT) &&
	    !(ia32_cap & ARCH_CAP_PSCHANGE_MC_NO))
		setup_क्रमce_cpu_bug(X86_BUG_ITLB_MULTIHIT);

	अगर (cpu_matches(cpu_vuln_whitelist, NO_SPECULATION))
		वापस;

	setup_क्रमce_cpu_bug(X86_BUG_SPECTRE_V1);

	अगर (!cpu_matches(cpu_vuln_whitelist, NO_SPECTRE_V2))
		setup_क्रमce_cpu_bug(X86_BUG_SPECTRE_V2);

	अगर (!cpu_matches(cpu_vuln_whitelist, NO_SSB) &&
	    !(ia32_cap & ARCH_CAP_SSB_NO) &&
	   !cpu_has(c, X86_FEATURE_AMD_SSB_NO))
		setup_क्रमce_cpu_bug(X86_BUG_SPEC_STORE_BYPASS);

	अगर (ia32_cap & ARCH_CAP_IBRS_ALL)
		setup_क्रमce_cpu_cap(X86_FEATURE_IBRS_ENHANCED);

	अगर (!cpu_matches(cpu_vuln_whitelist, NO_MDS) &&
	    !(ia32_cap & ARCH_CAP_MDS_NO)) अणु
		setup_क्रमce_cpu_bug(X86_BUG_MDS);
		अगर (cpu_matches(cpu_vuln_whitelist, MSBDS_ONLY))
			setup_क्रमce_cpu_bug(X86_BUG_MSBDS_ONLY);
	पूर्ण

	अगर (!cpu_matches(cpu_vuln_whitelist, NO_SWAPGS))
		setup_क्रमce_cpu_bug(X86_BUG_SWAPGS);

	/*
	 * When the CPU is not mitigated क्रम TAA (TAA_NO=0) set TAA bug when:
	 *	- TSX is supported or
	 *	- TSX_CTRL is present
	 *
	 * TSX_CTRL check is needed क्रम हालs when TSX could be disabled beक्रमe
	 * the kernel boot e.g. kexec.
	 * TSX_CTRL check alone is not sufficient क्रम हालs when the microcode
	 * update is not present or running as guest that करोn't get TSX_CTRL.
	 */
	अगर (!(ia32_cap & ARCH_CAP_TAA_NO) &&
	    (cpu_has(c, X86_FEATURE_RTM) ||
	     (ia32_cap & ARCH_CAP_TSX_CTRL_MSR)))
		setup_क्रमce_cpu_bug(X86_BUG_TAA);

	/*
	 * SRBDS affects CPUs which support RDRAND or RDSEED and are listed
	 * in the vulnerability blacklist.
	 */
	अगर ((cpu_has(c, X86_FEATURE_RDRAND) ||
	     cpu_has(c, X86_FEATURE_RDSEED)) &&
	    cpu_matches(cpu_vuln_blacklist, SRBDS))
		    setup_क्रमce_cpu_bug(X86_BUG_SRBDS);

	अगर (cpu_matches(cpu_vuln_whitelist, NO_MELTDOWN))
		वापस;

	/* Rogue Data Cache Load? No! */
	अगर (ia32_cap & ARCH_CAP_RDCL_NO)
		वापस;

	setup_क्रमce_cpu_bug(X86_BUG_CPU_MELTDOWN);

	अगर (cpu_matches(cpu_vuln_whitelist, NO_L1TF))
		वापस;

	setup_क्रमce_cpu_bug(X86_BUG_L1TF);
पूर्ण

/*
 * The NOPL inकाष्ठाion is supposed to exist on all CPUs of family >= 6;
 * unक्रमtunately, that's not true in practice because of early VIA
 * chips and (more importantly) broken भवizers that are not easy
 * to detect. In the latter हाल it करोesn't even *fail* reliably, so
 * probing क्रम it करोesn't even work. Disable it completely on 32-bit
 * unless we can find a reliable way to detect all the broken हालs.
 * Enable it explicitly on 64-bit क्रम non-स्थिरant inमाला_दो of cpu_has().
 */
अटल व्योम detect_nopl(व्योम)
अणु
#अगर_घोषित CONFIG_X86_32
	setup_clear_cpu_cap(X86_FEATURE_NOPL);
#अन्यथा
	setup_क्रमce_cpu_cap(X86_FEATURE_NOPL);
#पूर्ण_अगर
पूर्ण

/*
 * We parse cpu parameters early because fpu__init_प्रणाली() is executed
 * beक्रमe parse_early_param().
 */
अटल व्योम __init cpu_parse_early_param(व्योम)
अणु
	अक्षर arg[128];
	अक्षर *argptr = arg;
	पूर्णांक arglen, res, bit;

#अगर_घोषित CONFIG_X86_32
	अगर (cmdline_find_option_bool(boot_command_line, "no387"))
#अगर_घोषित CONFIG_MATH_EMULATION
		setup_clear_cpu_cap(X86_FEATURE_FPU);
#अन्यथा
		pr_err("Option 'no387' required CONFIG_MATH_EMULATION enabled.\n");
#पूर्ण_अगर

	अगर (cmdline_find_option_bool(boot_command_line, "nofxsr"))
		setup_clear_cpu_cap(X86_FEATURE_FXSR);
#पूर्ण_अगर

	अगर (cmdline_find_option_bool(boot_command_line, "noxsave"))
		setup_clear_cpu_cap(X86_FEATURE_XSAVE);

	अगर (cmdline_find_option_bool(boot_command_line, "noxsaveopt"))
		setup_clear_cpu_cap(X86_FEATURE_XSAVEOPT);

	अगर (cmdline_find_option_bool(boot_command_line, "noxsaves"))
		setup_clear_cpu_cap(X86_FEATURE_XSAVES);

	arglen = cmdline_find_option(boot_command_line, "clearcpuid", arg, माप(arg));
	अगर (arglen <= 0)
		वापस;

	pr_info("Clearing CPUID bits:");
	करो अणु
		res = get_option(&argptr, &bit);
		अगर (res == 0 || res == 3)
			अवरोध;

		/* If the argument was too दीर्घ, the last bit may be cut off */
		अगर (res == 1 && arglen >= माप(arg))
			अवरोध;

		अगर (bit >= 0 && bit < NCAPINTS * 32) अणु
			pr_cont(" " X86_CAP_FMT, x86_cap_flag(bit));
			setup_clear_cpu_cap(bit);
		पूर्ण
	पूर्ण जबतक (res == 2);
	pr_cont("\n");
पूर्ण

/*
 * Do minimum CPU detection early.
 * Fields really needed: venकरोr, cpuid_level, family, model, mask,
 * cache alignment.
 * The others are not touched to aव्योम unwanted side effects.
 *
 * WARNING: this function is only called on the boot CPU.  Don't add code
 * here that is supposed to run on all CPUs.
 */
अटल व्योम __init early_identअगरy_cpu(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_64
	c->x86_clflush_size = 64;
	c->x86_phys_bits = 36;
	c->x86_virt_bits = 48;
#अन्यथा
	c->x86_clflush_size = 32;
	c->x86_phys_bits = 32;
	c->x86_virt_bits = 32;
#पूर्ण_अगर
	c->x86_cache_alignment = c->x86_clflush_size;

	स_रखो(&c->x86_capability, 0, माप(c->x86_capability));
	c->extended_cpuid_level = 0;

	अगर (!have_cpuid_p())
		identअगरy_cpu_without_cpuid(c);

	/* cyrix could have cpuid enabled via c_identअगरy()*/
	अगर (have_cpuid_p()) अणु
		cpu_detect(c);
		get_cpu_venकरोr(c);
		get_cpu_cap(c);
		get_cpu_address_sizes(c);
		setup_क्रमce_cpu_cap(X86_FEATURE_CPUID);
		cpu_parse_early_param();

		अगर (this_cpu->c_early_init)
			this_cpu->c_early_init(c);

		c->cpu_index = 0;
		filter_cpuid_features(c, false);

		अगर (this_cpu->c_bsp_init)
			this_cpu->c_bsp_init(c);
	पूर्ण अन्यथा अणु
		setup_clear_cpu_cap(X86_FEATURE_CPUID);
	पूर्ण

	setup_क्रमce_cpu_cap(X86_FEATURE_ALWAYS);

	cpu_set_bug_bits(c);

	sld_setup(c);

	fpu__init_प्रणाली(c);

#अगर_घोषित CONFIG_X86_32
	/*
	 * Regardless of whether PCID is क्रमागतerated, the SDM says
	 * that it can't be enabled in 32-bit mode.
	 */
	setup_clear_cpu_cap(X86_FEATURE_PCID);
#पूर्ण_अगर

	/*
	 * Later in the boot process pgtable_l5_enabled() relies on
	 * cpu_feature_enabled(X86_FEATURE_LA57). If 5-level paging is not
	 * enabled by this poपूर्णांक we need to clear the feature bit to aव्योम
	 * false-positives at the later stage.
	 *
	 * pgtable_l5_enabled() can be false here क्रम several reasons:
	 *  - 5-level paging is disabled compile-समय;
	 *  - it's 32-bit kernel;
	 *  - machine करोesn't support 5-level paging;
	 *  - user specअगरied 'no5lvl' in kernel command line.
	 */
	अगर (!pgtable_l5_enabled())
		setup_clear_cpu_cap(X86_FEATURE_LA57);

	detect_nopl();
पूर्ण

व्योम __init early_cpu_init(व्योम)
अणु
	स्थिर काष्ठा cpu_dev *स्थिर *cdev;
	पूर्णांक count = 0;

#अगर_घोषित CONFIG_PROCESSOR_SELECT
	pr_info("KERNEL supported cpus:\n");
#पूर्ण_अगर

	क्रम (cdev = __x86_cpu_dev_start; cdev < __x86_cpu_dev_end; cdev++) अणु
		स्थिर काष्ठा cpu_dev *cpudev = *cdev;

		अगर (count >= X86_VENDOR_NUM)
			अवरोध;
		cpu_devs[count] = cpudev;
		count++;

#अगर_घोषित CONFIG_PROCESSOR_SELECT
		अणु
			अचिन्हित पूर्णांक j;

			क्रम (j = 0; j < 2; j++) अणु
				अगर (!cpudev->c_ident[j])
					जारी;
				pr_info("  %s %s\n", cpudev->c_venकरोr,
					cpudev->c_ident[j]);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	early_identअगरy_cpu(&boot_cpu_data);
पूर्ण

अटल व्योम detect_null_seg_behavior(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_64
	/*
	 * Empirically, writing zero to a segment selector on AMD करोes
	 * not clear the base, whereas writing zero to a segment
	 * selector on Intel करोes clear the base.  Intel's behavior
	 * allows slightly faster context चयनes in the common हाल
	 * where GS is unused by the prev and next thपढ़ोs.
	 *
	 * Since neither venकरोr करोcuments this anywhere that I can see,
	 * detect it directly instead of hard-coding the choice by
	 * venकरोr.
	 *
	 * I've designated AMD's behavior as the "bug" because it's
	 * counterपूर्णांकuitive and less मित्रly.
	 */

	अचिन्हित दीर्घ old_base, पंचांगp;
	rdmsrl(MSR_FS_BASE, old_base);
	wrmsrl(MSR_FS_BASE, 1);
	loadsegment(fs, 0);
	rdmsrl(MSR_FS_BASE, पंचांगp);
	अगर (पंचांगp != 0)
		set_cpu_bug(c, X86_BUG_शून्य_SEG);
	wrmsrl(MSR_FS_BASE, old_base);
#पूर्ण_अगर
पूर्ण

अटल व्योम generic_identअगरy(काष्ठा cpuinfo_x86 *c)
अणु
	c->extended_cpuid_level = 0;

	अगर (!have_cpuid_p())
		identअगरy_cpu_without_cpuid(c);

	/* cyrix could have cpuid enabled via c_identअगरy()*/
	अगर (!have_cpuid_p())
		वापस;

	cpu_detect(c);

	get_cpu_venकरोr(c);

	get_cpu_cap(c);

	get_cpu_address_sizes(c);

	अगर (c->cpuid_level >= 0x00000001) अणु
		c->initial_apicid = (cpuid_ebx(1) >> 24) & 0xFF;
#अगर_घोषित CONFIG_X86_32
# अगरdef CONFIG_SMP
		c->apicid = apic->phys_pkg_id(c->initial_apicid, 0);
# अन्यथा
		c->apicid = c->initial_apicid;
# endअगर
#पूर्ण_अगर
		c->phys_proc_id = c->initial_apicid;
	पूर्ण

	get_model_name(c); /* Default name */

	detect_null_seg_behavior(c);

	/*
	 * ESPFIX is a strange bug.  All real CPUs have it.  Paravirt
	 * प्रणालीs that run Linux at CPL > 0 may or may not have the
	 * issue, but, even अगर they have the issue, there's असलolutely
	 * nothing we can करो about it because we can't use the real IRET
	 * inकाष्ठाion.
	 *
	 * NB: For the समय being, only 32-bit kernels support
	 * X86_BUG_ESPFIX as such.  64-bit kernels directly choose
	 * whether to apply espfix using paravirt hooks.  If any
	 * non-paravirt प्रणाली ever shows up that करोes *not* have the
	 * ESPFIX issue, we can change this.
	 */
#अगर_घोषित CONFIG_X86_32
	set_cpu_bug(c, X86_BUG_ESPFIX);
#पूर्ण_अगर
पूर्ण

/*
 * Validate that ACPI/mptables have the same inक्रमmation about the
 * effective APIC id and update the package map.
 */
अटल व्योम validate_apic_and_package_id(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक apicid, cpu = smp_processor_id();

	apicid = apic->cpu_present_to_apicid(cpu);

	अगर (apicid != c->apicid) अणु
		pr_err(FW_BUG "CPU%u: APIC id mismatch. Firmware: %x APIC: %x\n",
		       cpu, apicid, c->initial_apicid);
	पूर्ण
	BUG_ON(topology_update_package_map(c->phys_proc_id, cpu));
	BUG_ON(topology_update_die_map(c->cpu_die_id, cpu));
#अन्यथा
	c->logical_proc_id = 0;
#पूर्ण_अगर
पूर्ण

/*
 * This करोes the hard work of actually picking apart the CPU stuff...
 */
अटल व्योम identअगरy_cpu(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांक i;

	c->loops_per_jअगरfy = loops_per_jअगरfy;
	c->x86_cache_size = 0;
	c->x86_venकरोr = X86_VENDOR_UNKNOWN;
	c->x86_model = c->x86_stepping = 0;	/* So far unknown... */
	c->x86_venकरोr_id[0] = '\0'; /* Unset */
	c->x86_model_id[0] = '\0';  /* Unset */
	c->x86_max_cores = 1;
	c->x86_coreid_bits = 0;
	c->cu_id = 0xff;
#अगर_घोषित CONFIG_X86_64
	c->x86_clflush_size = 64;
	c->x86_phys_bits = 36;
	c->x86_virt_bits = 48;
#अन्यथा
	c->cpuid_level = -1;	/* CPUID not detected */
	c->x86_clflush_size = 32;
	c->x86_phys_bits = 32;
	c->x86_virt_bits = 32;
#पूर्ण_अगर
	c->x86_cache_alignment = c->x86_clflush_size;
	स_रखो(&c->x86_capability, 0, माप(c->x86_capability));
#अगर_घोषित CONFIG_X86_VMX_FEATURE_NAMES
	स_रखो(&c->vmx_capability, 0, माप(c->vmx_capability));
#पूर्ण_अगर

	generic_identअगरy(c);

	अगर (this_cpu->c_identअगरy)
		this_cpu->c_identअगरy(c);

	/* Clear/Set all flags overridden by options, after probe */
	apply_क्रमced_caps(c);

#अगर_घोषित CONFIG_X86_64
	c->apicid = apic->phys_pkg_id(c->initial_apicid, 0);
#पूर्ण_अगर

	/*
	 * Venकरोr-specअगरic initialization.  In this section we
	 * canonicalize the feature flags, meaning अगर there are
	 * features a certain CPU supports which CPUID करोesn't
	 * tell us, CPUID claiming incorrect flags, or other bugs,
	 * we handle them here.
	 *
	 * At the end of this section, c->x86_capability better
	 * indicate the features this CPU genuinely supports!
	 */
	अगर (this_cpu->c_init)
		this_cpu->c_init(c);

	/* Disable the PN अगर appropriate */
	squash_the_stupid_serial_number(c);

	/* Set up SMEP/SMAP/UMIP */
	setup_smep(c);
	setup_smap(c);
	setup_umip(c);

	/* Enable FSGSBASE inकाष्ठाions अगर available. */
	अगर (cpu_has(c, X86_FEATURE_FSGSBASE)) अणु
		cr4_set_bits(X86_CR4_FSGSBASE);
		elf_hwcap2 |= HWCAP2_FSGSBASE;
	पूर्ण

	/*
	 * The venकरोr-specअगरic functions might have changed features.
	 * Now we करो "generic changes."
	 */

	/* Filter out anything that depends on CPUID levels we करोn't have */
	filter_cpuid_features(c, true);

	/* If the model name is still unset, करो table lookup. */
	अगर (!c->x86_model_id[0]) अणु
		स्थिर अक्षर *p;
		p = table_lookup_model(c);
		अगर (p)
			म_नकल(c->x86_model_id, p);
		अन्यथा
			/* Last resort... */
			प्र_लिखो(c->x86_model_id, "%02x/%02x",
				c->x86, c->x86_model);
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	detect_ht(c);
#पूर्ण_अगर

	x86_init_rdअक्रम(c);
	setup_pku(c);

	/*
	 * Clear/Set all flags overridden by options, need करो it
	 * beक्रमe following smp all cpus cap AND.
	 */
	apply_क्रमced_caps(c);

	/*
	 * On SMP, boot_cpu_data holds the common feature set between
	 * all CPUs; so make sure that we indicate which features are
	 * common between the CPUs.  The first समय this routine माला_लो
	 * executed, c == &boot_cpu_data.
	 */
	अगर (c != &boot_cpu_data) अणु
		/* AND the alपढ़ोy accumulated flags with these */
		क्रम (i = 0; i < NCAPINTS; i++)
			boot_cpu_data.x86_capability[i] &= c->x86_capability[i];

		/* OR, i.e. replicate the bug flags */
		क्रम (i = NCAPINTS; i < NCAPINTS + NBUGINTS; i++)
			c->x86_capability[i] |= boot_cpu_data.x86_capability[i];
	पूर्ण

	/* Init Machine Check Exception अगर available. */
	mcheck_cpu_init(c);

	select_idle_routine(c);

#अगर_घोषित CONFIG_NUMA
	numa_add_cpu(smp_processor_id());
#पूर्ण_अगर
पूर्ण

/*
 * Set up the CPU state needed to execute SYSENTER/SYSEXIT inकाष्ठाions
 * on 32-bit kernels:
 */
#अगर_घोषित CONFIG_X86_32
व्योम enable_sep_cpu(व्योम)
अणु
	काष्ठा tss_काष्ठा *tss;
	पूर्णांक cpu;

	अगर (!boot_cpu_has(X86_FEATURE_SEP))
		वापस;

	cpu = get_cpu();
	tss = &per_cpu(cpu_tss_rw, cpu);

	/*
	 * We cache MSR_IA32_SYSENTER_CS's value in the TSS's ss1 field --
	 * see the big comment in काष्ठा x86_hw_tss's definition.
	 */

	tss->x86_tss.ss1 = __KERNEL_CS;
	wrmsr(MSR_IA32_SYSENTER_CS, tss->x86_tss.ss1, 0);
	wrmsr(MSR_IA32_SYSENTER_ESP, (अचिन्हित दीर्घ)(cpu_entry_stack(cpu) + 1), 0);
	wrmsr(MSR_IA32_SYSENTER_EIP, (अचिन्हित दीर्घ)entry_SYSENTER_32, 0);

	put_cpu();
पूर्ण
#पूर्ण_अगर

व्योम __init identअगरy_boot_cpu(व्योम)
अणु
	identअगरy_cpu(&boot_cpu_data);
#अगर_घोषित CONFIG_X86_32
	sysenter_setup();
	enable_sep_cpu();
#पूर्ण_अगर
	cpu_detect_tlb(&boot_cpu_data);
	setup_cr_pinning();

	tsx_init();
पूर्ण

व्योम identअगरy_secondary_cpu(काष्ठा cpuinfo_x86 *c)
अणु
	BUG_ON(c == &boot_cpu_data);
	identअगरy_cpu(c);
#अगर_घोषित CONFIG_X86_32
	enable_sep_cpu();
#पूर्ण_अगर
	mtrr_ap_init();
	validate_apic_and_package_id(c);
	x86_spec_ctrl_setup_ap();
	update_srbds_msr();
पूर्ण

अटल __init पूर्णांक setup_noclflush(अक्षर *arg)
अणु
	setup_clear_cpu_cap(X86_FEATURE_CLFLUSH);
	setup_clear_cpu_cap(X86_FEATURE_CLFLUSHOPT);
	वापस 1;
पूर्ण
__setup("noclflush", setup_noclflush);

व्योम prपूर्णांक_cpu_info(काष्ठा cpuinfo_x86 *c)
अणु
	स्थिर अक्षर *venकरोr = शून्य;

	अगर (c->x86_venकरोr < X86_VENDOR_NUM) अणु
		venकरोr = this_cpu->c_venकरोr;
	पूर्ण अन्यथा अणु
		अगर (c->cpuid_level >= 0)
			venकरोr = c->x86_venकरोr_id;
	पूर्ण

	अगर (venकरोr && !म_माला(c->x86_model_id, venकरोr))
		pr_cont("%s ", venकरोr);

	अगर (c->x86_model_id[0])
		pr_cont("%s", c->x86_model_id);
	अन्यथा
		pr_cont("%d86", c->x86);

	pr_cont(" (family: 0x%x, model: 0x%x", c->x86, c->x86_model);

	अगर (c->x86_stepping || c->cpuid_level >= 0)
		pr_cont(", stepping: 0x%x)\n", c->x86_stepping);
	अन्यथा
		pr_cont(")\n");
पूर्ण

/*
 * clearcpuid= was alपढ़ोy parsed in fpu__init_parse_early_param.
 * But we need to keep a dummy __setup around otherwise it would
 * show up as an environment variable क्रम init.
 */
अटल __init पूर्णांक setup_clearcpuid(अक्षर *arg)
अणु
	वापस 1;
पूर्ण
__setup("clearcpuid=", setup_clearcpuid);

#अगर_घोषित CONFIG_X86_64
DEFINE_PER_CPU_FIRST(काष्ठा fixed_percpu_data,
		     fixed_percpu_data) __aligned(PAGE_SIZE) __visible;
EXPORT_PER_CPU_SYMBOL_GPL(fixed_percpu_data);

/*
 * The following percpu variables are hot.  Align current_task to
 * cacheline size such that they fall in the same cacheline.
 */
DEFINE_PER_CPU(काष्ठा task_काष्ठा *, current_task) ____cacheline_aligned =
	&init_task;
EXPORT_PER_CPU_SYMBOL(current_task);

DEFINE_PER_CPU(व्योम *, hardirq_stack_ptr);
DEFINE_PER_CPU(bool, hardirq_stack_inuse);

DEFINE_PER_CPU(पूर्णांक, __preempt_count) = INIT_PREEMPT_COUNT;
EXPORT_PER_CPU_SYMBOL(__preempt_count);

DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_current_top_of_stack) = TOP_OF_INIT_STACK;

/* May not be marked __init: used by software suspend */
व्योम syscall_init(व्योम)
अणु
	wrmsr(MSR_STAR, 0, (__USER32_CS << 16) | __KERNEL_CS);
	wrmsrl(MSR_LSTAR, (अचिन्हित दीर्घ)entry_SYSCALL_64);

#अगर_घोषित CONFIG_IA32_EMULATION
	wrmsrl(MSR_CSTAR, (अचिन्हित दीर्घ)entry_SYSCALL_compat);
	/*
	 * This only works on Intel CPUs.
	 * On AMD CPUs these MSRs are 32-bit, CPU truncates MSR_IA32_SYSENTER_EIP.
	 * This करोes not cause SYSENTER to jump to the wrong location, because
	 * AMD करोesn't allow SYSENTER in दीर्घ mode (either 32- or 64-bit).
	 */
	wrmsrl_safe(MSR_IA32_SYSENTER_CS, (u64)__KERNEL_CS);
	wrmsrl_safe(MSR_IA32_SYSENTER_ESP,
		    (अचिन्हित दीर्घ)(cpu_entry_stack(smp_processor_id()) + 1));
	wrmsrl_safe(MSR_IA32_SYSENTER_EIP, (u64)entry_SYSENTER_compat);
#अन्यथा
	wrmsrl(MSR_CSTAR, (अचिन्हित दीर्घ)ignore_sysret);
	wrmsrl_safe(MSR_IA32_SYSENTER_CS, (u64)GDT_ENTRY_INVALID_SEG);
	wrmsrl_safe(MSR_IA32_SYSENTER_ESP, 0ULL);
	wrmsrl_safe(MSR_IA32_SYSENTER_EIP, 0ULL);
#पूर्ण_अगर

	/* Flags to clear on syscall */
	wrmsrl(MSR_SYSCALL_MASK,
	       X86_EFLAGS_TF|X86_EFLAGS_DF|X86_EFLAGS_IF|
	       X86_EFLAGS_IOPL|X86_EFLAGS_AC|X86_EFLAGS_NT);
पूर्ण

#अन्यथा	/* CONFIG_X86_64 */

DEFINE_PER_CPU(काष्ठा task_काष्ठा *, current_task) = &init_task;
EXPORT_PER_CPU_SYMBOL(current_task);
DEFINE_PER_CPU(पूर्णांक, __preempt_count) = INIT_PREEMPT_COUNT;
EXPORT_PER_CPU_SYMBOL(__preempt_count);

/*
 * On x86_32, vm86 modअगरies tss.sp0, so sp0 isn't a reliable way to find
 * the top of the kernel stack.  Use an extra percpu variable to track the
 * top of the kernel stack directly.
 */
DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_current_top_of_stack) =
	(अचिन्हित दीर्घ)&init_thपढ़ो_जोड़ + THREAD_SIZE;
EXPORT_PER_CPU_SYMBOL(cpu_current_top_of_stack);

#अगर_घोषित CONFIG_STACKPROTECTOR
DEFINE_PER_CPU(अचिन्हित दीर्घ, __stack_chk_guard);
EXPORT_PER_CPU_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

#पूर्ण_अगर	/* CONFIG_X86_64 */

/*
 * Clear all 6 debug रेजिस्टरs:
 */
अटल व्योम clear_all_debug_regs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		/* Ignore db4, db5 */
		अगर ((i == 4) || (i == 5))
			जारी;

		set_debugreg(0, i);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KGDB
/*
 * Restore debug regs अगर using kgdbरुको and you have a kernel debugger
 * connection established.
 */
अटल व्योम dbg_restore_debug_regs(व्योम)
अणु
	अगर (unlikely(kgdb_connected && arch_kgdb_ops.correct_hw_अवरोध))
		arch_kgdb_ops.correct_hw_अवरोध();
पूर्ण
#अन्यथा /* ! CONFIG_KGDB */
#घोषणा dbg_restore_debug_regs()
#पूर्ण_अगर /* ! CONFIG_KGDB */

अटल व्योम रुको_क्रम_master_cpu(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	/*
	 * रुको क्रम ACK from master CPU beक्रमe continuing
	 * with AP initialization
	 */
	WARN_ON(cpumask_test_and_set_cpu(cpu, cpu_initialized_mask));
	जबतक (!cpumask_test_cpu(cpu, cpu_callout_mask))
		cpu_relax();
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल अंतरभूत व्योम setup_अ_लोpu(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ cpudata = vdso_encode_cpunode(cpu, early_cpu_to_node(cpu));
	काष्ठा desc_काष्ठा d = अणु पूर्ण;

	अगर (boot_cpu_has(X86_FEATURE_RDTSCP) || boot_cpu_has(X86_FEATURE_RDPID))
		wrmsr(MSR_TSC_AUX, cpudata, 0);

	/* Store CPU and node number in limit. */
	d.limit0 = cpudata;
	d.limit1 = cpudata >> 16;

	d.type = 5;		/* RO data, expand करोwn, accessed */
	d.dpl = 3;		/* Visible to user code */
	d.s = 1;		/* Not a प्रणाली segment */
	d.p = 1;		/* Present */
	d.d = 1;		/* 32-bit */

	ग_लिखो_gdt_entry(get_cpu_gdt_rw(cpu), GDT_ENTRY_CPUNODE, &d, DESCTYPE_S);
पूर्ण

अटल अंतरभूत व्योम ucode_cpu_init(पूर्णांक cpu)
अणु
	अगर (cpu)
		load_ucode_ap();
पूर्ण

अटल अंतरभूत व्योम tss_setup_ist(काष्ठा tss_काष्ठा *tss)
अणु
	/* Set up the per-CPU TSS IST stacks */
	tss->x86_tss.ist[IST_INDEX_DF] = __this_cpu_ist_top_va(DF);
	tss->x86_tss.ist[IST_INDEX_NMI] = __this_cpu_ist_top_va(NMI);
	tss->x86_tss.ist[IST_INDEX_DB] = __this_cpu_ist_top_va(DB);
	tss->x86_tss.ist[IST_INDEX_MCE] = __this_cpu_ist_top_va(MCE);
	/* Only mapped when SEV-ES is active */
	tss->x86_tss.ist[IST_INDEX_VC] = __this_cpu_ist_top_va(VC);
पूर्ण

#अन्यथा /* CONFIG_X86_64 */

अटल अंतरभूत व्योम setup_अ_लोpu(पूर्णांक cpu) अणु पूर्ण

अटल अंतरभूत व्योम ucode_cpu_init(पूर्णांक cpu)
अणु
	show_ucode_info_early();
पूर्ण

अटल अंतरभूत व्योम tss_setup_ist(काष्ठा tss_काष्ठा *tss) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_X86_64 */

अटल अंतरभूत व्योम tss_setup_io_biपंचांगap(काष्ठा tss_काष्ठा *tss)
अणु
	tss->x86_tss.io_biपंचांगap_base = IO_BITMAP_OFFSET_INVALID;

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
	tss->io_biपंचांगap.prev_max = 0;
	tss->io_biपंचांगap.prev_sequence = 0;
	स_रखो(tss->io_biपंचांगap.biपंचांगap, 0xff, माप(tss->io_biपंचांगap.biपंचांगap));
	/*
	 * Invalidate the extra array entry past the end of the all
	 * permission biपंचांगap as required by the hardware.
	 */
	tss->io_biपंचांगap.mapall[IO_BITMAP_LONGS] = ~0UL;
#पूर्ण_अगर
पूर्ण

/*
 * Setup everything needed to handle exceptions from the IDT, including the IST
 * exceptions which use paranoid_entry().
 */
व्योम cpu_init_exception_handling(व्योम)
अणु
	काष्ठा tss_काष्ठा *tss = this_cpu_ptr(&cpu_tss_rw);
	पूर्णांक cpu = raw_smp_processor_id();

	/* paranoid_entry() माला_लो the CPU number from the GDT */
	setup_अ_लोpu(cpu);

	/* IST vectors need TSS to be set up. */
	tss_setup_ist(tss);
	tss_setup_io_biपंचांगap(tss);
	set_tss_desc(cpu, &get_cpu_entry_area(cpu)->tss.x86_tss);

	load_TR_desc();

	/* Finally load the IDT */
	load_current_idt();
पूर्ण

/*
 * cpu_init() initializes state that is per-CPU. Some data is alपढ़ोy
 * initialized (naturally) in the bootstrap process, such as the GDT
 * and IDT. We reload them nevertheless, this function acts as a
 * 'CPU state barrier', nothing should get across.
 */
व्योम cpu_init(व्योम)
अणु
	काष्ठा tss_काष्ठा *tss = this_cpu_ptr(&cpu_tss_rw);
	काष्ठा task_काष्ठा *cur = current;
	पूर्णांक cpu = raw_smp_processor_id();

	रुको_क्रम_master_cpu(cpu);

	ucode_cpu_init(cpu);

#अगर_घोषित CONFIG_NUMA
	अगर (this_cpu_पढ़ो(numa_node) == 0 &&
	    early_cpu_to_node(cpu) != NUMA_NO_NODE)
		set_numa_node(early_cpu_to_node(cpu));
#पूर्ण_अगर
	setup_अ_लोpu(cpu);

	pr_debug("Initializing CPU#%d\n", cpu);

	अगर (IS_ENABLED(CONFIG_X86_64) || cpu_feature_enabled(X86_FEATURE_VME) ||
	    boot_cpu_has(X86_FEATURE_TSC) || boot_cpu_has(X86_FEATURE_DE))
		cr4_clear_bits(X86_CR4_VME|X86_CR4_PVI|X86_CR4_TSD|X86_CR4_DE);

	/*
	 * Initialize the per-CPU GDT with the boot GDT,
	 * and set up the GDT descriptor:
	 */
	चयन_to_new_gdt(cpu);
	load_current_idt();

	अगर (IS_ENABLED(CONFIG_X86_64)) अणु
		loadsegment(fs, 0);
		स_रखो(cur->thपढ़ो.tls_array, 0, GDT_ENTRY_TLS_ENTRIES * 8);
		syscall_init();

		wrmsrl(MSR_FS_BASE, 0);
		wrmsrl(MSR_KERNEL_GS_BASE, 0);
		barrier();

		x2apic_setup();
	पूर्ण

	mmgrab(&init_mm);
	cur->active_mm = &init_mm;
	BUG_ON(cur->mm);
	initialize_tlbstate_and_flush();
	enter_lazy_tlb(&init_mm, cur);

	/* Initialize the TSS. */
	tss_setup_ist(tss);
	tss_setup_io_biपंचांगap(tss);
	set_tss_desc(cpu, &get_cpu_entry_area(cpu)->tss.x86_tss);

	load_TR_desc();
	/*
	 * sp0 poपूर्णांकs to the entry trampoline stack regardless of what task
	 * is running.
	 */
	load_sp0((अचिन्हित दीर्घ)(cpu_entry_stack(cpu) + 1));

	load_mm_ldt(&init_mm);

	clear_all_debug_regs();
	dbg_restore_debug_regs();

	द्विगुनfault_init_cpu_tss();

	fpu__init_cpu();

	अगर (is_uv_प्रणाली())
		uv_cpu_init();

	load_fixmap_gdt(cpu);
पूर्ण

/*
 * The microcode loader calls this upon late microcode load to recheck features,
 * only when microcode has been updated. Caller holds microcode_mutex and CPU
 * hotplug lock.
 */
व्योम microcode_check(व्योम)
अणु
	काष्ठा cpuinfo_x86 info;

	perf_check_microcode();

	/* Reload CPUID max function as it might've changed. */
	info.cpuid_level = cpuid_eax(0);

	/*
	 * Copy all capability leafs to pick up the synthetic ones so that
	 * स_भेद() below करोesn't fail on that. The ones coming from CPUID will
	 * get overwritten in get_cpu_cap().
	 */
	स_नकल(&info.x86_capability, &boot_cpu_data.x86_capability, माप(info.x86_capability));

	get_cpu_cap(&info);

	अगर (!स_भेद(&info.x86_capability, &boot_cpu_data.x86_capability, माप(info.x86_capability)))
		वापस;

	pr_warn("x86/CPU: CPU features have changed after loading microcode, but might not take effect.\n");
	pr_warn("x86/CPU: Please consider either early loading through initrd/built-in or a potential BIOS update.\n");
पूर्ण

/*
 * Invoked from core CPU hotplug code after hotplug operations
 */
व्योम arch_smt_update(व्योम)
अणु
	/* Handle the speculative execution misfeatures */
	cpu_bugs_smt_update();
	/* Check whether IPI broadcasting can be enabled */
	apic_smt_update();
पूर्ण
