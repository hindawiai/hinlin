<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/microcode_पूर्णांकel.h>
#समावेश <यंत्र/hwcap2.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/cmdline.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/resctrl.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/thermal.h>

#अगर_घोषित CONFIG_X86_64
#समावेश <linux/topology.h>
#पूर्ण_अगर

#समावेश "cpu.h"

#अगर_घोषित CONFIG_X86_LOCAL_APIC
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/apic.h>
#पूर्ण_अगर

क्रमागत split_lock_detect_state अणु
	sld_off = 0,
	sld_warn,
	sld_fatal,
पूर्ण;

/*
 * Default to sld_off because most प्रणालीs करो not support split lock detection.
 * sld_state_setup() will चयन this to sld_warn on प्रणालीs that support
 * split lock/bus lock detect, unless there is a command line override.
 */
अटल क्रमागत split_lock_detect_state sld_state __ro_after_init = sld_off;
अटल u64 msr_test_ctrl_cache __ro_after_init;

/*
 * With a name like MSR_TEST_CTL it should go without saying, but करोn't touch
 * MSR_TEST_CTL unless the CPU is one of the whitelisted models.  Writing it
 * on CPUs that करो not support SLD can cause fireworks, even when writing '0'.
 */
अटल bool cpu_model_supports_sld __ro_after_init;

/*
 * Processors which have self-snooping capability can handle conflicting
 * memory type across CPUs by snooping its own cache. However, there exists
 * CPU models in which having conflicting memory types still leads to
 * unpredictable behavior, machine check errors, or hangs. Clear this
 * feature to prevent its use on machines with known erratas.
 */
अटल व्योम check_memory_type_self_snoop_errata(काष्ठा cpuinfo_x86 *c)
अणु
	चयन (c->x86_model) अणु
	हाल INTEL_FAM6_CORE_YONAH:
	हाल INTEL_FAM6_CORE2_MEROM:
	हाल INTEL_FAM6_CORE2_MEROM_L:
	हाल INTEL_FAM6_CORE2_PENRYN:
	हाल INTEL_FAM6_CORE2_DUNNINGTON:
	हाल INTEL_FAM6_NEHALEM:
	हाल INTEL_FAM6_NEHALEM_G:
	हाल INTEL_FAM6_NEHALEM_EP:
	हाल INTEL_FAM6_NEHALEM_EX:
	हाल INTEL_FAM6_WESTMERE:
	हाल INTEL_FAM6_WESTMERE_EP:
	हाल INTEL_FAM6_SANDYBRIDGE:
		setup_clear_cpu_cap(X86_FEATURE_SELFSNOOP);
	पूर्ण
पूर्ण

अटल bool ring3mरुको_disabled __पढ़ो_mostly;

अटल पूर्णांक __init ring3mरुको_disable(अक्षर *__unused)
अणु
	ring3mरुको_disabled = true;
	वापस 0;
पूर्ण
__setup("ring3mwait=disable", ring3mरुको_disable);

अटल व्योम probe_xeon_phi_r3mरुको(काष्ठा cpuinfo_x86 *c)
अणु
	/*
	 * Ring 3 MONITOR/MWAIT feature cannot be detected without
	 * cpu model and family comparison.
	 */
	अगर (c->x86 != 6)
		वापस;
	चयन (c->x86_model) अणु
	हाल INTEL_FAM6_XEON_PHI_KNL:
	हाल INTEL_FAM6_XEON_PHI_KNM:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (ring3mरुको_disabled)
		वापस;

	set_cpu_cap(c, X86_FEATURE_RING3MWAIT);
	this_cpu_or(msr_misc_features_shaकरोw,
		    1UL << MSR_MISC_FEATURES_ENABLES_RING3MWAIT_BIT);

	अगर (c == &boot_cpu_data)
		ELF_HWCAP2 |= HWCAP2_RING3MWAIT;
पूर्ण

/*
 * Early microcode releases क्रम the Spectre v2 mitigation were broken.
 * Inक्रमmation taken from;
 * - https://newsroom.पूर्णांकel.com/wp-content/uploads/sites/11/2018/03/microcode-update-guidance.pdf
 * - https://kb.vmware.com/s/article/52345
 * - Microcode revisions observed in the wild
 * - Release note from 20180108 microcode release
 */
काष्ठा sku_microcode अणु
	u8 model;
	u8 stepping;
	u32 microcode;
पूर्ण;
अटल स्थिर काष्ठा sku_microcode spectre_bad_microcodes[] = अणु
	अणु INTEL_FAM6_KABYLAKE,		0x0B,	0x80 पूर्ण,
	अणु INTEL_FAM6_KABYLAKE,		0x0A,	0x80 पूर्ण,
	अणु INTEL_FAM6_KABYLAKE,		0x09,	0x80 पूर्ण,
	अणु INTEL_FAM6_KABYLAKE_L,	0x0A,	0x80 पूर्ण,
	अणु INTEL_FAM6_KABYLAKE_L,	0x09,	0x80 पूर्ण,
	अणु INTEL_FAM6_SKYLAKE_X,		0x03,	0x0100013e पूर्ण,
	अणु INTEL_FAM6_SKYLAKE_X,		0x04,	0x0200003c पूर्ण,
	अणु INTEL_FAM6_BROADWELL,		0x04,	0x28 पूर्ण,
	अणु INTEL_FAM6_BROADWELL_G,	0x01,	0x1b पूर्ण,
	अणु INTEL_FAM6_BROADWELL_D,	0x02,	0x14 पूर्ण,
	अणु INTEL_FAM6_BROADWELL_D,	0x03,	0x07000011 पूर्ण,
	अणु INTEL_FAM6_BROADWELL_X,	0x01,	0x0b000025 पूर्ण,
	अणु INTEL_FAM6_HASWELL_L,		0x01,	0x21 पूर्ण,
	अणु INTEL_FAM6_HASWELL_G,		0x01,	0x18 पूर्ण,
	अणु INTEL_FAM6_HASWELL,		0x03,	0x23 पूर्ण,
	अणु INTEL_FAM6_HASWELL_X,		0x02,	0x3b पूर्ण,
	अणु INTEL_FAM6_HASWELL_X,		0x04,	0x10 पूर्ण,
	अणु INTEL_FAM6_IVYBRIDGE_X,	0x04,	0x42a पूर्ण,
	/* Observed in the wild */
	अणु INTEL_FAM6_SANDYBRIDGE_X,	0x06,	0x61b पूर्ण,
	अणु INTEL_FAM6_SANDYBRIDGE_X,	0x07,	0x712 पूर्ण,
पूर्ण;

अटल bool bad_spectre_microcode(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांक i;

	/*
	 * We know that the hypervisor lie to us on the microcode version so
	 * we may as well hope that it is running the correct version.
	 */
	अगर (cpu_has(c, X86_FEATURE_HYPERVISOR))
		वापस false;

	अगर (c->x86 != 6)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(spectre_bad_microcodes); i++) अणु
		अगर (c->x86_model == spectre_bad_microcodes[i].model &&
		    c->x86_stepping == spectre_bad_microcodes[i].stepping)
			वापस (c->microcode <= spectre_bad_microcodes[i].microcode);
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम early_init_पूर्णांकel(काष्ठा cpuinfo_x86 *c)
अणु
	u64 misc_enable;

	/* Unmask CPUID levels अगर masked: */
	अगर (c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xd)) अणु
		अगर (msr_clear_bit(MSR_IA32_MISC_ENABLE,
				  MSR_IA32_MISC_ENABLE_LIMIT_CPUID_BIT) > 0) अणु
			c->cpuid_level = cpuid_eax(0);
			get_cpu_cap(c);
		पूर्ण
	पूर्ण

	अगर ((c->x86 == 0xf && c->x86_model >= 0x03) ||
		(c->x86 == 0x6 && c->x86_model >= 0x0e))
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);

	अगर (c->x86 >= 6 && !cpu_has(c, X86_FEATURE_IA64))
		c->microcode = पूर्णांकel_get_microcode_revision();

	/* Now अगर any of them are set, check the blacklist and clear the lot */
	अगर ((cpu_has(c, X86_FEATURE_SPEC_CTRL) ||
	     cpu_has(c, X86_FEATURE_INTEL_STIBP) ||
	     cpu_has(c, X86_FEATURE_IBRS) || cpu_has(c, X86_FEATURE_IBPB) ||
	     cpu_has(c, X86_FEATURE_STIBP)) && bad_spectre_microcode(c)) अणु
		pr_warn("Intel Spectre v2 broken microcode detected; disabling Speculation Control\n");
		setup_clear_cpu_cap(X86_FEATURE_IBRS);
		setup_clear_cpu_cap(X86_FEATURE_IBPB);
		setup_clear_cpu_cap(X86_FEATURE_STIBP);
		setup_clear_cpu_cap(X86_FEATURE_SPEC_CTRL);
		setup_clear_cpu_cap(X86_FEATURE_MSR_SPEC_CTRL);
		setup_clear_cpu_cap(X86_FEATURE_INTEL_STIBP);
		setup_clear_cpu_cap(X86_FEATURE_SSBD);
		setup_clear_cpu_cap(X86_FEATURE_SPEC_CTRL_SSBD);
	पूर्ण

	/*
	 * Atom erratum AAE44/AAF40/AAG38/AAH41:
	 *
	 * A race condition between speculative fetches and invalidating
	 * a large page.  This is worked around in microcode, but we
	 * need the microcode to have alपढ़ोy been loaded... so अगर it is
	 * not, recommend a BIOS update and disable large pages.
	 */
	अगर (c->x86 == 6 && c->x86_model == 0x1c && c->x86_stepping <= 2 &&
	    c->microcode < 0x20e) अणु
		pr_warn("Atom PSE erratum detected, BIOS microcode update recommended\n");
		clear_cpu_cap(c, X86_FEATURE_PSE);
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSENTER32);
#अन्यथा
	/* Netburst reports 64 bytes clflush size, but करोes IO in 128 bytes */
	अगर (c->x86 == 15 && c->x86_cache_alignment == 64)
		c->x86_cache_alignment = 128;
#पूर्ण_अगर

	/* CPUID workaround क्रम 0F33/0F34 CPU */
	अगर (c->x86 == 0xF && c->x86_model == 0x3
	    && (c->x86_stepping == 0x3 || c->x86_stepping == 0x4))
		c->x86_phys_bits = 36;

	/*
	 * c->x86_घातer is 8000_0007 edx. Bit 8 is TSC runs at स्थिरant rate
	 * with P/T states and करोes not stop in deep C-states.
	 *
	 * It is also reliable across cores and sockets. (but not across
	 * cabinets - we turn it off in that हाल explicitly.)
	 */
	अगर (c->x86_घातer & (1 << 8)) अणु
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	पूर्ण

	/* Penwell and Cloverview have the TSC which करोesn't sleep on S3 */
	अगर (c->x86 == 6) अणु
		चयन (c->x86_model) अणु
		हाल INTEL_FAM6_ATOM_SALTWELL_MID:
		हाल INTEL_FAM6_ATOM_SALTWELL_TABLET:
		हाल INTEL_FAM6_ATOM_SILVERMONT_MID:
		हाल INTEL_FAM6_ATOM_AIRMONT_NP:
			set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC_S3);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * There is a known erratum on Pentium III and Core Solo
	 * and Core Duo CPUs.
	 * " Page with PAT set to WC जबतक associated MTRR is UC
	 *   may consolidate to UC "
	 * Because of this erratum, it is better to stick with
	 * setting WC in MTRR rather than using PAT on these CPUs.
	 *
	 * Enable PAT WC only on P4, Core 2 or later CPUs.
	 */
	अगर (c->x86 == 6 && c->x86_model < 15)
		clear_cpu_cap(c, X86_FEATURE_PAT);

	/*
	 * If fast string is not enabled in IA32_MISC_ENABLE क्रम any reason,
	 * clear the fast string and enhanced fast string CPU capabilities.
	 */
	अगर (c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xd)) अणु
		rdmsrl(MSR_IA32_MISC_ENABLE, misc_enable);
		अगर (!(misc_enable & MSR_IA32_MISC_ENABLE_FAST_STRING)) अणु
			pr_info("Disabled fast string operations\n");
			setup_clear_cpu_cap(X86_FEATURE_REP_GOOD);
			setup_clear_cpu_cap(X86_FEATURE_ERMS);
		पूर्ण
	पूर्ण

	/*
	 * Intel Quark Core DevMan_001.pdf section 6.4.11
	 * "The operating प्रणाली also is required to invalidate (i.e., flush)
	 *  the TLB when any changes are made to any of the page table entries.
	 *  The operating प्रणाली must reload CR3 to cause the TLB to be flushed"
	 *
	 * As a result, boot_cpu_has(X86_FEATURE_PGE) in arch/x86/include/यंत्र/tlbflush.h
	 * should be false so that __flush_tlb_all() causes CR3 instead of CR4.PGE
	 * to be modअगरied.
	 */
	अगर (c->x86 == 5 && c->x86_model == 9) अणु
		pr_info("Disabling PGE capability bit\n");
		setup_clear_cpu_cap(X86_FEATURE_PGE);
	पूर्ण

	अगर (c->cpuid_level >= 0x00000001) अणु
		u32 eax, ebx, ecx, edx;

		cpuid(0x00000001, &eax, &ebx, &ecx, &edx);
		/*
		 * If HTT (EDX[28]) is set EBX[16:23] contain the number of
		 * apicids which are reserved per package. Store the resulting
		 * shअगरt value क्रम the package management code.
		 */
		अगर (edx & (1U << 28))
			c->x86_coreid_bits = get_count_order((ebx >> 16) & 0xff);
	पूर्ण

	check_memory_type_self_snoop_errata(c);

	/*
	 * Get the number of SMT siblings early from the extended topology
	 * leaf, अगर available. Otherwise try the legacy SMT detection.
	 */
	अगर (detect_extended_topology_early(c) < 0)
		detect_ht_early(c);
पूर्ण

अटल व्योम bsp_init_पूर्णांकel(काष्ठा cpuinfo_x86 *c)
अणु
	resctrl_cpu_detect(c);
पूर्ण

#अगर_घोषित CONFIG_X86_32
/*
 *	Early probe support logic क्रम ppro memory erratum #50
 *
 *	This is called beक्रमe we करो cpu ident work
 */

पूर्णांक ppro_with_ram_bug(व्योम)
अणु
	/* Uses data from early_cpu_detect now */
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL &&
	    boot_cpu_data.x86 == 6 &&
	    boot_cpu_data.x86_model == 1 &&
	    boot_cpu_data.x86_stepping < 8) अणु
		pr_info("Pentium Pro with Errata#50 detected. Taking evasive action.\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_smp_check(काष्ठा cpuinfo_x86 *c)
अणु
	/* calling is from identअगरy_secondary_cpu() ? */
	अगर (!c->cpu_index)
		वापस;

	/*
	 * Mask B, Pentium, but not Pentium MMX
	 */
	अगर (c->x86 == 5 &&
	    c->x86_stepping >= 1 && c->x86_stepping <= 4 &&
	    c->x86_model <= 3) अणु
		/*
		 * Remember we have B step Pentia with bugs
		 */
		WARN_ONCE(1, "WARNING: SMP operation may be unreliable"
				    "with B stepping processors.\n");
	पूर्ण
पूर्ण

अटल पूर्णांक क्रमcepae;
अटल पूर्णांक __init क्रमcepae_setup(अक्षर *__unused)
अणु
	क्रमcepae = 1;
	वापस 1;
पूर्ण
__setup("forcepae", क्रमcepae_setup);

अटल व्योम पूर्णांकel_workarounds(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_F00F_BUG
	/*
	 * All models of Pentium and Pentium with MMX technology CPUs
	 * have the F0 0F bug, which lets nonprivileged users lock up the
	 * प्रणाली. Announce that the fault handler will be checking क्रम it.
	 * The Quark is also family 5, but करोes not have the same bug.
	 */
	clear_cpu_bug(c, X86_BUG_F00F);
	अगर (c->x86 == 5 && c->x86_model < 9) अणु
		अटल पूर्णांक f00f_workaround_enabled;

		set_cpu_bug(c, X86_BUG_F00F);
		अगर (!f00f_workaround_enabled) अणु
			pr_notice("Intel Pentium with F0 0F bug - workaround enabled.\n");
			f00f_workaround_enabled = 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * SEP CPUID bug: Pentium Pro reports SEP but करोesn't have it until
	 * model 3 mask 3
	 */
	अगर ((c->x86<<8 | c->x86_model<<4 | c->x86_stepping) < 0x633)
		clear_cpu_cap(c, X86_FEATURE_SEP);

	/*
	 * PAE CPUID issue: many Pentium M report no PAE but may have a
	 * functionally usable PAE implementation.
	 * Forcefully enable PAE अगर kernel parameter "forcepae" is present.
	 */
	अगर (क्रमcepae) अणु
		pr_warn("PAE forced!\n");
		set_cpu_cap(c, X86_FEATURE_PAE);
		add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_NOW_UNRELIABLE);
	पूर्ण

	/*
	 * P4 Xeon erratum 037 workaround.
	 * Hardware prefetcher may cause stale data to be loaded पूर्णांकo the cache.
	 */
	अगर ((c->x86 == 15) && (c->x86_model == 1) && (c->x86_stepping == 1)) अणु
		अगर (msr_set_bit(MSR_IA32_MISC_ENABLE,
				MSR_IA32_MISC_ENABLE_PREFETCH_DISABLE_BIT) > 0) अणु
			pr_info("CPU: C0 stepping P4 Xeon detected.\n");
			pr_info("CPU: Disabling hardware prefetching (Erratum 037)\n");
		पूर्ण
	पूर्ण

	/*
	 * See अगर we have a good local APIC by checking क्रम buggy Pentia,
	 * i.e. all B steppings and the C2 stepping of P54C when using their
	 * पूर्णांकegrated APIC (see 11AP erratum in "Pentium Processor
	 * Specअगरication Update").
	 */
	अगर (boot_cpu_has(X86_FEATURE_APIC) && (c->x86<<8 | c->x86_model<<4) == 0x520 &&
	    (c->x86_stepping < 0x6 || c->x86_stepping == 0xb))
		set_cpu_bug(c, X86_BUG_11AP);


#अगर_घोषित CONFIG_X86_INTEL_USERCOPY
	/*
	 * Set up the preferred alignment क्रम movsl bulk memory moves
	 */
	चयन (c->x86) अणु
	हाल 4:		/* 486: untested */
		अवरोध;
	हाल 5:		/* Old Pentia: untested */
		अवरोध;
	हाल 6:		/* PII/PIII only like movsl with 8-byte alignment */
		movsl_mask.mask = 7;
		अवरोध;
	हाल 15:	/* P4 is OK करोwn to 8-byte alignment */
		movsl_mask.mask = 7;
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	पूर्णांकel_smp_check(c);
पूर्ण
#अन्यथा
अटल व्योम पूर्णांकel_workarounds(काष्ठा cpuinfo_x86 *c)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम srat_detect_node(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_NUMA
	अचिन्हित node;
	पूर्णांक cpu = smp_processor_id();

	/* Don't करो the funky fallback heuristics the AMD version employs
	   क्रम now. */
	node = numa_cpu_node(cpu);
	अगर (node == NUMA_NO_NODE || !node_online(node)) अणु
		/* reuse the value from init_cpu_to_node() */
		node = cpu_to_node(cpu);
	पूर्ण
	numa_set_node(cpu, node);
#पूर्ण_अगर
पूर्ण

#घोषणा MSR_IA32_TME_ACTIVATE		0x982

/* Helpers to access TME_ACTIVATE MSR */
#घोषणा TME_ACTIVATE_LOCKED(x)		(x & 0x1)
#घोषणा TME_ACTIVATE_ENABLED(x)		(x & 0x2)

#घोषणा TME_ACTIVATE_POLICY(x)		((x >> 4) & 0xf)	/* Bits 7:4 */
#घोषणा TME_ACTIVATE_POLICY_AES_XTS_128	0

#घोषणा TME_ACTIVATE_KEYID_BITS(x)	((x >> 32) & 0xf)	/* Bits 35:32 */

#घोषणा TME_ACTIVATE_CRYPTO_ALGS(x)	((x >> 48) & 0xffff)	/* Bits 63:48 */
#घोषणा TME_ACTIVATE_CRYPTO_AES_XTS_128	1

/* Values क्रम mkपंचांगe_status (SW only स्थिरruct) */
#घोषणा MKTME_ENABLED			0
#घोषणा MKTME_DISABLED			1
#घोषणा MKTME_UNINITIALIZED		2
अटल पूर्णांक mkपंचांगe_status = MKTME_UNINITIALIZED;

अटल व्योम detect_पंचांगe(काष्ठा cpuinfo_x86 *c)
अणु
	u64 पंचांगe_activate, पंचांगe_policy, पंचांगe_crypto_algs;
	पूर्णांक keyid_bits = 0, nr_keyids = 0;
	अटल u64 पंचांगe_activate_cpu0 = 0;

	rdmsrl(MSR_IA32_TME_ACTIVATE, पंचांगe_activate);

	अगर (mkपंचांगe_status != MKTME_UNINITIALIZED) अणु
		अगर (पंचांगe_activate != पंचांगe_activate_cpu0) अणु
			/* Broken BIOS? */
			pr_err_once("x86/tme: configuration is inconsistent between CPUs\n");
			pr_err_once("x86/tme: MKTME is not usable\n");
			mkपंचांगe_status = MKTME_DISABLED;

			/* Proceed. We may need to exclude bits from x86_phys_bits. */
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगe_activate_cpu0 = पंचांगe_activate;
	पूर्ण

	अगर (!TME_ACTIVATE_LOCKED(पंचांगe_activate) || !TME_ACTIVATE_ENABLED(पंचांगe_activate)) अणु
		pr_info_once("x86/tme: not enabled by BIOS\n");
		mkपंचांगe_status = MKTME_DISABLED;
		वापस;
	पूर्ण

	अगर (mkपंचांगe_status != MKTME_UNINITIALIZED)
		जाओ detect_keyid_bits;

	pr_info("x86/tme: enabled by BIOS\n");

	पंचांगe_policy = TME_ACTIVATE_POLICY(पंचांगe_activate);
	अगर (पंचांगe_policy != TME_ACTIVATE_POLICY_AES_XTS_128)
		pr_warn("x86/tme: Unknown policy is active: %#llx\n", पंचांगe_policy);

	पंचांगe_crypto_algs = TME_ACTIVATE_CRYPTO_ALGS(पंचांगe_activate);
	अगर (!(पंचांगe_crypto_algs & TME_ACTIVATE_CRYPTO_AES_XTS_128)) अणु
		pr_err("x86/mktme: No known encryption algorithm is supported: %#llx\n",
				पंचांगe_crypto_algs);
		mkपंचांगe_status = MKTME_DISABLED;
	पूर्ण
detect_keyid_bits:
	keyid_bits = TME_ACTIVATE_KEYID_BITS(पंचांगe_activate);
	nr_keyids = (1UL << keyid_bits) - 1;
	अगर (nr_keyids) अणु
		pr_info_once("x86/mktme: enabled by BIOS\n");
		pr_info_once("x86/mktme: %d KeyIDs available\n", nr_keyids);
	पूर्ण अन्यथा अणु
		pr_info_once("x86/mktme: disabled by BIOS\n");
	पूर्ण

	अगर (mkपंचांगe_status == MKTME_UNINITIALIZED) अणु
		/* MKTME is usable */
		mkपंचांगe_status = MKTME_ENABLED;
	पूर्ण

	/*
	 * KeyID bits effectively lower the number of physical address
	 * bits.  Update cpuinfo_x86::x86_phys_bits accordingly.
	 */
	c->x86_phys_bits -= keyid_bits;
पूर्ण

अटल व्योम init_cpuid_fault(काष्ठा cpuinfo_x86 *c)
अणु
	u64 msr;

	अगर (!rdmsrl_safe(MSR_PLATFORM_INFO, &msr)) अणु
		अगर (msr & MSR_PLATFORM_INFO_CPUID_FAULT)
			set_cpu_cap(c, X86_FEATURE_CPUID_FAULT);
	पूर्ण
पूर्ण

अटल व्योम init_पूर्णांकel_misc_features(काष्ठा cpuinfo_x86 *c)
अणु
	u64 msr;

	अगर (rdmsrl_safe(MSR_MISC_FEATURES_ENABLES, &msr))
		वापस;

	/* Clear all MISC features */
	this_cpu_ग_लिखो(msr_misc_features_shaकरोw, 0);

	/* Check features and update capabilities and shaकरोw control bits */
	init_cpuid_fault(c);
	probe_xeon_phi_r3mरुको(c);

	msr = this_cpu_पढ़ो(msr_misc_features_shaकरोw);
	wrmsrl(MSR_MISC_FEATURES_ENABLES, msr);
पूर्ण

अटल व्योम split_lock_init(व्योम);
अटल व्योम bus_lock_init(व्योम);

अटल व्योम init_पूर्णांकel(काष्ठा cpuinfo_x86 *c)
अणु
	early_init_पूर्णांकel(c);

	पूर्णांकel_workarounds(c);

	/*
	 * Detect the extended topology inक्रमmation अगर available. This
	 * will reinitialise the initial_apicid which will be used
	 * in init_पूर्णांकel_cacheinfo()
	 */
	detect_extended_topology(c);

	अगर (!cpu_has(c, X86_FEATURE_XTOPOLOGY)) अणु
		/*
		 * let's use the legacy cpuid vector 0x1 and 0x4 क्रम topology
		 * detection.
		 */
		detect_num_cpu_cores(c);
#अगर_घोषित CONFIG_X86_32
		detect_ht(c);
#पूर्ण_अगर
	पूर्ण

	init_पूर्णांकel_cacheinfo(c);

	अगर (c->cpuid_level > 9) अणु
		अचिन्हित eax = cpuid_eax(10);
		/* Check क्रम version and the number of counters */
		अगर ((eax & 0xff) && (((eax>>8) & 0xff) > 1))
			set_cpu_cap(c, X86_FEATURE_ARCH_PERFMON);
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_XMM2))
		set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);

	अगर (boot_cpu_has(X86_FEATURE_DS)) अणु
		अचिन्हित पूर्णांक l1, l2;

		rdmsr(MSR_IA32_MISC_ENABLE, l1, l2);
		अगर (!(l1 & (1<<11)))
			set_cpu_cap(c, X86_FEATURE_BTS);
		अगर (!(l1 & (1<<12)))
			set_cpu_cap(c, X86_FEATURE_PEBS);
	पूर्ण

	अगर (c->x86 == 6 && boot_cpu_has(X86_FEATURE_CLFLUSH) &&
	    (c->x86_model == 29 || c->x86_model == 46 || c->x86_model == 47))
		set_cpu_bug(c, X86_BUG_CLFLUSH_MONITOR);

	अगर (c->x86 == 6 && boot_cpu_has(X86_FEATURE_MWAIT) &&
		((c->x86_model == INTEL_FAM6_ATOM_GOLDMONT)))
		set_cpu_bug(c, X86_BUG_MONITOR);

#अगर_घोषित CONFIG_X86_64
	अगर (c->x86 == 15)
		c->x86_cache_alignment = c->x86_clflush_size * 2;
	अगर (c->x86 == 6)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);
#अन्यथा
	/*
	 * Names क्रम the Pentium II/Celeron processors
	 * detectable only by also checking the cache size.
	 * Dixon is NOT a Celeron.
	 */
	अगर (c->x86 == 6) अणु
		अचिन्हित पूर्णांक l2 = c->x86_cache_size;
		अक्षर *p = शून्य;

		चयन (c->x86_model) अणु
		हाल 5:
			अगर (l2 == 0)
				p = "Celeron (Covington)";
			अन्यथा अगर (l2 == 256)
				p = "Mobile Pentium II (Dixon)";
			अवरोध;

		हाल 6:
			अगर (l2 == 128)
				p = "Celeron (Mendocino)";
			अन्यथा अगर (c->x86_stepping == 0 || c->x86_stepping == 5)
				p = "Celeron-A";
			अवरोध;

		हाल 8:
			अगर (l2 == 128)
				p = "Celeron (Coppermine)";
			अवरोध;
		पूर्ण

		अगर (p)
			म_नकल(c->x86_model_id, p);
	पूर्ण

	अगर (c->x86 == 15)
		set_cpu_cap(c, X86_FEATURE_P4);
	अगर (c->x86 == 6)
		set_cpu_cap(c, X86_FEATURE_P3);
#पूर्ण_अगर

	/* Work around errata */
	srat_detect_node(c);

	init_ia32_feat_ctl(c);

	अगर (cpu_has(c, X86_FEATURE_TME))
		detect_पंचांगe(c);

	init_पूर्णांकel_misc_features(c);

	अगर (tsx_ctrl_state == TSX_CTRL_ENABLE)
		tsx_enable();
	अगर (tsx_ctrl_state == TSX_CTRL_DISABLE)
		tsx_disable();

	split_lock_init();
	bus_lock_init();

	पूर्णांकel_init_thermal(c);
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल अचिन्हित पूर्णांक पूर्णांकel_size_cache(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक size)
अणु
	/*
	 * Intel PIII Tualatin. This comes in two flavours.
	 * One has 256kb of cache, the other 512. We have no way
	 * to determine which, so we use a bootसमय override
	 * क्रम the 512kb model, and assume 256 otherwise.
	 */
	अगर ((c->x86 == 6) && (c->x86_model == 11) && (size == 0))
		size = 256;

	/*
	 * Intel Quark SoC X1000 contains a 4-way set associative
	 * 16K cache with a 16 byte cache line and 256 lines per tag
	 */
	अगर ((c->x86 == 5) && (c->x86_model == 9))
		size = 16;
	वापस size;
पूर्ण
#पूर्ण_अगर

#घोषणा TLB_INST_4K	0x01
#घोषणा TLB_INST_4M	0x02
#घोषणा TLB_INST_2M_4M	0x03

#घोषणा TLB_INST_ALL	0x05
#घोषणा TLB_INST_1G	0x06

#घोषणा TLB_DATA_4K	0x11
#घोषणा TLB_DATA_4M	0x12
#घोषणा TLB_DATA_2M_4M	0x13
#घोषणा TLB_DATA_4K_4M	0x14

#घोषणा TLB_DATA_1G	0x16

#घोषणा TLB_DATA0_4K	0x21
#घोषणा TLB_DATA0_4M	0x22
#घोषणा TLB_DATA0_2M_4M	0x23

#घोषणा STLB_4K		0x41
#घोषणा STLB_4K_2M	0x42

अटल स्थिर काष्ठा _tlb_table पूर्णांकel_tlb_table[] = अणु
	अणु 0x01, TLB_INST_4K,		32,	" TLB_INST 4 KByte pages, 4-way set associative" पूर्ण,
	अणु 0x02, TLB_INST_4M,		2,	" TLB_INST 4 MByte pages, full associative" पूर्ण,
	अणु 0x03, TLB_DATA_4K,		64,	" TLB_DATA 4 KByte pages, 4-way set associative" पूर्ण,
	अणु 0x04, TLB_DATA_4M,		8,	" TLB_DATA 4 MByte pages, 4-way set associative" पूर्ण,
	अणु 0x05, TLB_DATA_4M,		32,	" TLB_DATA 4 MByte pages, 4-way set associative" पूर्ण,
	अणु 0x0b, TLB_INST_4M,		4,	" TLB_INST 4 MByte pages, 4-way set associative" पूर्ण,
	अणु 0x4f, TLB_INST_4K,		32,	" TLB_INST 4 KByte pages" पूर्ण,
	अणु 0x50, TLB_INST_ALL,		64,	" TLB_INST 4 KByte and 2-MByte or 4-MByte pages" पूर्ण,
	अणु 0x51, TLB_INST_ALL,		128,	" TLB_INST 4 KByte and 2-MByte or 4-MByte pages" पूर्ण,
	अणु 0x52, TLB_INST_ALL,		256,	" TLB_INST 4 KByte and 2-MByte or 4-MByte pages" पूर्ण,
	अणु 0x55, TLB_INST_2M_4M,		7,	" TLB_INST 2-MByte or 4-MByte pages, fully associative" पूर्ण,
	अणु 0x56, TLB_DATA0_4M,		16,	" TLB_DATA0 4 MByte pages, 4-way set associative" पूर्ण,
	अणु 0x57, TLB_DATA0_4K,		16,	" TLB_DATA0 4 KByte pages, 4-way associative" पूर्ण,
	अणु 0x59, TLB_DATA0_4K,		16,	" TLB_DATA0 4 KByte pages, fully associative" पूर्ण,
	अणु 0x5a, TLB_DATA0_2M_4M,	32,	" TLB_DATA0 2-MByte or 4 MByte pages, 4-way set associative" पूर्ण,
	अणु 0x5b, TLB_DATA_4K_4M,		64,	" TLB_DATA 4 KByte and 4 MByte pages" पूर्ण,
	अणु 0x5c, TLB_DATA_4K_4M,		128,	" TLB_DATA 4 KByte and 4 MByte pages" पूर्ण,
	अणु 0x5d, TLB_DATA_4K_4M,		256,	" TLB_DATA 4 KByte and 4 MByte pages" पूर्ण,
	अणु 0x61, TLB_INST_4K,		48,	" TLB_INST 4 KByte pages, full associative" पूर्ण,
	अणु 0x63, TLB_DATA_1G,		4,	" TLB_DATA 1 GByte pages, 4-way set associative" पूर्ण,
	अणु 0x6b, TLB_DATA_4K,		256,	" TLB_DATA 4 KByte pages, 8-way associative" पूर्ण,
	अणु 0x6c, TLB_DATA_2M_4M,		128,	" TLB_DATA 2 MByte or 4 MByte pages, 8-way associative" पूर्ण,
	अणु 0x6d, TLB_DATA_1G,		16,	" TLB_DATA 1 GByte pages, fully associative" पूर्ण,
	अणु 0x76, TLB_INST_2M_4M,		8,	" TLB_INST 2-MByte or 4-MByte pages, fully associative" पूर्ण,
	अणु 0xb0, TLB_INST_4K,		128,	" TLB_INST 4 KByte pages, 4-way set associative" पूर्ण,
	अणु 0xb1, TLB_INST_2M_4M,		4,	" TLB_INST 2M pages, 4-way, 8 entries or 4M pages, 4-way entries" पूर्ण,
	अणु 0xb2, TLB_INST_4K,		64,	" TLB_INST 4KByte pages, 4-way set associative" पूर्ण,
	अणु 0xb3, TLB_DATA_4K,		128,	" TLB_DATA 4 KByte pages, 4-way set associative" पूर्ण,
	अणु 0xb4, TLB_DATA_4K,		256,	" TLB_DATA 4 KByte pages, 4-way associative" पूर्ण,
	अणु 0xb5, TLB_INST_4K,		64,	" TLB_INST 4 KByte pages, 8-way set associative" पूर्ण,
	अणु 0xb6, TLB_INST_4K,		128,	" TLB_INST 4 KByte pages, 8-way set associative" पूर्ण,
	अणु 0xba, TLB_DATA_4K,		64,	" TLB_DATA 4 KByte pages, 4-way associative" पूर्ण,
	अणु 0xc0, TLB_DATA_4K_4M,		8,	" TLB_DATA 4 KByte and 4 MByte pages, 4-way associative" पूर्ण,
	अणु 0xc1, STLB_4K_2M,		1024,	" STLB 4 KByte and 2 MByte pages, 8-way associative" पूर्ण,
	अणु 0xc2, TLB_DATA_2M_4M,		16,	" TLB_DATA 2 MByte/4MByte pages, 4-way associative" पूर्ण,
	अणु 0xca, STLB_4K,		512,	" STLB 4 KByte pages, 4-way associative" पूर्ण,
	अणु 0x00, 0, 0 पूर्ण
पूर्ण;

अटल व्योम पूर्णांकel_tlb_lookup(स्थिर अचिन्हित अक्षर desc)
अणु
	अचिन्हित अक्षर k;
	अगर (desc == 0)
		वापस;

	/* look up this descriptor in the table */
	क्रम (k = 0; पूर्णांकel_tlb_table[k].descriptor != desc &&
	     पूर्णांकel_tlb_table[k].descriptor != 0; k++)
		;

	अगर (पूर्णांकel_tlb_table[k].tlb_type == 0)
		वापस;

	चयन (पूर्णांकel_tlb_table[k].tlb_type) अणु
	हाल STLB_4K:
		अगर (tlb_lli_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lld_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल STLB_4K_2M:
		अगर (tlb_lli_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lld_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lli_2m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_2m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lld_2m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_2m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lli_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lld_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_INST_ALL:
		अगर (tlb_lli_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lli_2m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_2m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lli_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_INST_4K:
		अगर (tlb_lli_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_INST_4M:
		अगर (tlb_lli_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_INST_2M_4M:
		अगर (tlb_lli_2m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_2m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lli_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lli_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_DATA_4K:
	हाल TLB_DATA0_4K:
		अगर (tlb_lld_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_DATA_4M:
	हाल TLB_DATA0_4M:
		अगर (tlb_lld_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_DATA_2M_4M:
	हाल TLB_DATA0_2M_4M:
		अगर (tlb_lld_2m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_2m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lld_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_DATA_4K_4M:
		अगर (tlb_lld_4k[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4k[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अगर (tlb_lld_4m[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_4m[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	हाल TLB_DATA_1G:
		अगर (tlb_lld_1g[ENTRIES] < पूर्णांकel_tlb_table[k].entries)
			tlb_lld_1g[ENTRIES] = पूर्णांकel_tlb_table[k].entries;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_detect_tlb(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांक i, j, n;
	अचिन्हित पूर्णांक regs[4];
	अचिन्हित अक्षर *desc = (अचिन्हित अक्षर *)regs;

	अगर (c->cpuid_level < 2)
		वापस;

	/* Number of बार to iterate */
	n = cpuid_eax(2) & 0xFF;

	क्रम (i = 0 ; i < n ; i++) अणु
		cpuid(2, &regs[0], &regs[1], &regs[2], &regs[3]);

		/* If bit 31 is set, this is an unknown क्रमmat */
		क्रम (j = 0 ; j < 3 ; j++)
			अगर (regs[j] & (1 << 31))
				regs[j] = 0;

		/* Byte 0 is level count, not a descriptor */
		क्रम (j = 1 ; j < 16 ; j++)
			पूर्णांकel_tlb_lookup(desc[j]);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cpu_dev पूर्णांकel_cpu_dev = अणु
	.c_venकरोr	= "Intel",
	.c_ident	= अणु "GenuineIntel" पूर्ण,
#अगर_घोषित CONFIG_X86_32
	.legacy_models = अणु
		अणु .family = 4, .model_names =
		  अणु
			  [0] = "486 DX-25/33",
			  [1] = "486 DX-50",
			  [2] = "486 SX",
			  [3] = "486 DX/2",
			  [4] = "486 SL",
			  [5] = "486 SX/2",
			  [7] = "486 DX/2-WB",
			  [8] = "486 DX/4",
			  [9] = "486 DX/4-WB"
		  पूर्ण
		पूर्ण,
		अणु .family = 5, .model_names =
		  अणु
			  [0] = "Pentium 60/66 A-step",
			  [1] = "Pentium 60/66",
			  [2] = "Pentium 75 - 200",
			  [3] = "OverDrive PODP5V83",
			  [4] = "Pentium MMX",
			  [7] = "Mobile Pentium 75 - 200",
			  [8] = "Mobile Pentium MMX",
			  [9] = "Quark SoC X1000",
		  पूर्ण
		पूर्ण,
		अणु .family = 6, .model_names =
		  अणु
			  [0] = "Pentium Pro A-step",
			  [1] = "Pentium Pro",
			  [3] = "Pentium II (Klamath)",
			  [4] = "Pentium II (Deschutes)",
			  [5] = "Pentium II (Deschutes)",
			  [6] = "Mobile Pentium II",
			  [7] = "Pentium III (Katmai)",
			  [8] = "Pentium III (Coppermine)",
			  [10] = "Pentium III (Cascades)",
			  [11] = "Pentium III (Tualatin)",
		  पूर्ण
		पूर्ण,
		अणु .family = 15, .model_names =
		  अणु
			  [0] = "Pentium 4 (Unknown)",
			  [1] = "Pentium 4 (Willamette)",
			  [2] = "Pentium 4 (Northwood)",
			  [4] = "Pentium 4 (Foster)",
			  [5] = "Pentium 4 (Foster)",
		  पूर्ण
		पूर्ण,
	पूर्ण,
	.legacy_cache_size = पूर्णांकel_size_cache,
#पूर्ण_अगर
	.c_detect_tlb	= पूर्णांकel_detect_tlb,
	.c_early_init   = early_init_पूर्णांकel,
	.c_bsp_init	= bsp_init_पूर्णांकel,
	.c_init		= init_पूर्णांकel,
	.c_x86_venकरोr	= X86_VENDOR_INTEL,
पूर्ण;

cpu_dev_रेजिस्टर(पूर्णांकel_cpu_dev);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "x86/split lock detection: " fmt

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर			*option;
	क्रमागत split_lock_detect_state	state;
पूर्ण sld_options[] __initस्थिर = अणु
	अणु "off",	sld_off   पूर्ण,
	अणु "warn",	sld_warn  पूर्ण,
	अणु "fatal",	sld_fatal पूर्ण,
पूर्ण;

अटल अंतरभूत bool match_option(स्थिर अक्षर *arg, पूर्णांक arglen, स्थिर अक्षर *opt)
अणु
	पूर्णांक len = म_माप(opt);

	वापस len == arglen && !म_भेदन(arg, opt, len);
पूर्ण

अटल bool split_lock_verअगरy_msr(bool on)
अणु
	u64 ctrl, पंचांगp;

	अगर (rdmsrl_safe(MSR_TEST_CTRL, &ctrl))
		वापस false;
	अगर (on)
		ctrl |= MSR_TEST_CTRL_SPLIT_LOCK_DETECT;
	अन्यथा
		ctrl &= ~MSR_TEST_CTRL_SPLIT_LOCK_DETECT;
	अगर (wrmsrl_safe(MSR_TEST_CTRL, ctrl))
		वापस false;
	rdmsrl(MSR_TEST_CTRL, पंचांगp);
	वापस ctrl == पंचांगp;
पूर्ण

अटल व्योम __init sld_state_setup(व्योम)
अणु
	क्रमागत split_lock_detect_state state = sld_warn;
	अक्षर arg[20];
	पूर्णांक i, ret;

	अगर (!boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT) &&
	    !boot_cpu_has(X86_FEATURE_BUS_LOCK_DETECT))
		वापस;

	ret = cmdline_find_option(boot_command_line, "split_lock_detect",
				  arg, माप(arg));
	अगर (ret >= 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sld_options); i++) अणु
			अगर (match_option(arg, ret, sld_options[i].option)) अणु
				state = sld_options[i].state;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	sld_state = state;
पूर्ण

अटल व्योम __init __split_lock_setup(व्योम)
अणु
	अगर (!split_lock_verअगरy_msr(false)) अणु
		pr_info("MSR access failed: Disabled\n");
		वापस;
	पूर्ण

	rdmsrl(MSR_TEST_CTRL, msr_test_ctrl_cache);

	अगर (!split_lock_verअगरy_msr(true)) अणु
		pr_info("MSR access failed: Disabled\n");
		वापस;
	पूर्ण

	/* Restore the MSR to its cached value. */
	wrmsrl(MSR_TEST_CTRL, msr_test_ctrl_cache);

	setup_क्रमce_cpu_cap(X86_FEATURE_SPLIT_LOCK_DETECT);
पूर्ण

/*
 * MSR_TEST_CTRL is per core, but we treat it like a per CPU MSR. Locking
 * is not implemented as one thपढ़ो could unकरो the setting of the other
 * thपढ़ो immediately after dropping the lock anyway.
 */
अटल व्योम sld_update_msr(bool on)
अणु
	u64 test_ctrl_val = msr_test_ctrl_cache;

	अगर (on)
		test_ctrl_val |= MSR_TEST_CTRL_SPLIT_LOCK_DETECT;

	wrmsrl(MSR_TEST_CTRL, test_ctrl_val);
पूर्ण

अटल व्योम split_lock_init(व्योम)
अणु
	अगर (cpu_model_supports_sld)
		split_lock_verअगरy_msr(sld_state != sld_off);
पूर्ण

अटल व्योम split_lock_warn(अचिन्हित दीर्घ ip)
अणु
	pr_warn_ratelimited("#AC: %s/%d took a split_lock trap at address: 0x%lx\n",
			    current->comm, current->pid, ip);

	/*
	 * Disable the split lock detection क्रम this task so it can make
	 * progress and set TIF_SLD so the detection is re-enabled via
	 * चयन_to_sld() when the task is scheduled out.
	 */
	sld_update_msr(false);
	set_tsk_thपढ़ो_flag(current, TIF_SLD);
पूर्ण

bool handle_guest_split_lock(अचिन्हित दीर्घ ip)
अणु
	अगर (sld_state == sld_warn) अणु
		split_lock_warn(ip);
		वापस true;
	पूर्ण

	pr_warn_once("#AC: %s/%d %s split_lock trap at address: 0x%lx\n",
		     current->comm, current->pid,
		     sld_state == sld_fatal ? "fatal" : "bogus", ip);

	current->thपढ़ो.error_code = 0;
	current->thपढ़ो.trap_nr = X86_TRAP_AC;
	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, शून्य);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(handle_guest_split_lock);

अटल व्योम bus_lock_init(व्योम)
अणु
	u64 val;

	/*
	 * Warn and fatal are handled by #AC क्रम split lock अगर #AC क्रम
	 * split lock is supported.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_BUS_LOCK_DETECT) ||
	    (boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT) &&
	    (sld_state == sld_warn || sld_state == sld_fatal)) ||
	    sld_state == sld_off)
		वापस;

	/*
	 * Enable #DB क्रम bus lock. All bus locks are handled in #DB except
	 * split locks are handled in #AC in the fatal हाल.
	 */
	rdmsrl(MSR_IA32_DEBUGCTLMSR, val);
	val |= DEBUGCTLMSR_BUS_LOCK_DETECT;
	wrmsrl(MSR_IA32_DEBUGCTLMSR, val);
पूर्ण

bool handle_user_split_lock(काष्ठा pt_regs *regs, दीर्घ error_code)
अणु
	अगर ((regs->flags & X86_EFLAGS_AC) || sld_state == sld_fatal)
		वापस false;
	split_lock_warn(regs->ip);
	वापस true;
पूर्ण

व्योम handle_bus_lock(काष्ठा pt_regs *regs)
अणु
	चयन (sld_state) अणु
	हाल sld_off:
		अवरोध;
	हाल sld_warn:
		pr_warn_ratelimited("#DB: %s/%d took a bus_lock trap at address: 0x%lx\n",
				    current->comm, current->pid, regs->ip);
		अवरोध;
	हाल sld_fatal:
		क्रमce_sig_fault(SIGBUS, BUS_ADRALN, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This function is called only when चयनing between tasks with
 * dअगरferent split-lock detection modes. It sets the MSR क्रम the
 * mode of the new task. This is right most of the समय, but since
 * the MSR is shared by hyperthपढ़ोs on a physical core there can
 * be glitches when the two thपढ़ोs need dअगरferent modes.
 */
व्योम चयन_to_sld(अचिन्हित दीर्घ tअगरn)
अणु
	sld_update_msr(!(tअगरn & _TIF_SLD));
पूर्ण

/*
 * Bits in the IA32_CORE_CAPABILITIES are not architectural, so they should
 * only be trusted अगर it is confirmed that a CPU model implements a
 * specअगरic feature at a particular bit position.
 *
 * The possible driver data field values:
 *
 * - 0: CPU models that are known to have the per-core split-lock detection
 *	feature even though they करो not क्रमागतerate IA32_CORE_CAPABILITIES.
 *
 * - 1: CPU models which may क्रमागतerate IA32_CORE_CAPABILITIES and अगर so use
 *      bit 5 to क्रमागतerate the per-core split-lock detection feature.
 */
अटल स्थिर काष्ठा x86_cpu_id split_lock_cpu_ids[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_X,		0),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		0),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_D,		0),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT,	1),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_D,	1),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_L,	1),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE_L,		1),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE,		1),
	X86_MATCH_INTEL_FAM6_MODEL(SAPPHIRERAPIDS_X,	1),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE,		1),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE_L,		1),
	अणुपूर्ण
पूर्ण;

अटल व्योम __init split_lock_setup(काष्ठा cpuinfo_x86 *c)
अणु
	स्थिर काष्ठा x86_cpu_id *m;
	u64 ia32_core_caps;

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस;

	m = x86_match_cpu(split_lock_cpu_ids);
	अगर (!m)
		वापस;

	चयन (m->driver_data) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		अगर (!cpu_has(c, X86_FEATURE_CORE_CAPABILITIES))
			वापस;
		rdmsrl(MSR_IA32_CORE_CAPS, ia32_core_caps);
		अगर (!(ia32_core_caps & MSR_IA32_CORE_CAPS_SPLIT_LOCK_DETECT))
			वापस;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	cpu_model_supports_sld = true;
	__split_lock_setup();
पूर्ण

अटल व्योम sld_state_show(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_BUS_LOCK_DETECT) &&
	    !boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT))
		वापस;

	चयन (sld_state) अणु
	हाल sld_off:
		pr_info("disabled\n");
		अवरोध;
	हाल sld_warn:
		अगर (boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT))
			pr_info("#AC: crashing the kernel on kernel split_locks and warning on user-space split_locks\n");
		अन्यथा अगर (boot_cpu_has(X86_FEATURE_BUS_LOCK_DETECT))
			pr_info("#DB: warning on user-space bus_locks\n");
		अवरोध;
	हाल sld_fatal:
		अगर (boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT)) अणु
			pr_info("#AC: crashing the kernel on kernel split_locks and sending SIGBUS on user-space split_locks\n");
		पूर्ण अन्यथा अगर (boot_cpu_has(X86_FEATURE_BUS_LOCK_DETECT)) अणु
			pr_info("#DB: sending SIGBUS on user-space bus_locks%s\n",
				boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT) ?
				" from non-WB" : "");
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

व्योम __init sld_setup(काष्ठा cpuinfo_x86 *c)
अणु
	split_lock_setup(c);
	sld_state_setup();
	sld_state_show();
पूर्ण

#घोषणा X86_HYBRID_CPU_TYPE_ID_SHIFT	24

/**
 * get_this_hybrid_cpu_type() - Get the type of this hybrid CPU
 *
 * Returns the CPU type [31:24] (i.e., Atom or Core) of a CPU in
 * a hybrid processor. If the processor is not hybrid, वापसs 0.
 */
u8 get_this_hybrid_cpu_type(व्योम)
अणु
	अगर (!cpu_feature_enabled(X86_FEATURE_HYBRID_CPU))
		वापस 0;

	वापस cpuid_eax(0x0000001a) >> X86_HYBRID_CPU_TYPE_ID_SHIFT;
पूर्ण
