<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/bitops.h>
#समावेश <linux/elf.h>
#समावेश <linux/mm.h>

#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/topology.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cacheinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/resctrl.h>

#अगर_घोषित CONFIG_X86_64
# include <यंत्र/mmconfig.h>
#पूर्ण_अगर

#समावेश "cpu.h"

अटल स्थिर पूर्णांक amd_erratum_383[];
अटल स्थिर पूर्णांक amd_erratum_400[];
अटल स्थिर पूर्णांक amd_erratum_1054[];
अटल bool cpu_has_amd_erratum(काष्ठा cpuinfo_x86 *cpu, स्थिर पूर्णांक *erratum);

/*
 * nodes_per_socket: Stores the number of nodes per socket.
 * Refer to Fam15h Models 00-0fh BKDG - CPUID Fn8000_001E_ECX
 * Node Identअगरiers[10:8]
 */
अटल u32 nodes_per_socket = 1;

अटल अंतरभूत पूर्णांक rdmsrl_amd_safe(अचिन्हित msr, अचिन्हित दीर्घ दीर्घ *p)
अणु
	u32 gprs[8] = अणु 0 पूर्ण;
	पूर्णांक err;

	WARN_ONCE((boot_cpu_data.x86 != 0xf),
		  "%s should only be used on K8!\n", __func__);

	gprs[1] = msr;
	gprs[7] = 0x9c5a203a;

	err = rdmsr_safe_regs(gprs);

	*p = gprs[0] | ((u64)gprs[2] << 32);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक wrmsrl_amd_safe(अचिन्हित msr, अचिन्हित दीर्घ दीर्घ val)
अणु
	u32 gprs[8] = अणु 0 पूर्ण;

	WARN_ONCE((boot_cpu_data.x86 != 0xf),
		  "%s should only be used on K8!\n", __func__);

	gprs[0] = (u32)val;
	gprs[1] = msr;
	gprs[2] = val >> 32;
	gprs[7] = 0x9c5a203a;

	वापस wrmsr_safe_regs(gprs);
पूर्ण

/*
 *	B step AMD K6 beक्रमe B 9730xxxx have hardware bugs that can cause
 *	misexecution of code under Linux. Owners of such processors should
 *	contact AMD क्रम precise details and a CPU swap.
 *
 *	See	http://www.multimania.com/poulot/k6bug.hपंचांगl
 *	and	section 2.6.2 of "AMD-K6 Processor Revision Guide - Model 6"
 *		(Publication # 21266  Issue Date: August 1998)
 *
 *	The following test is erm.. पूर्णांकeresting. AMD neglected to up
 *	the chip setting when fixing the bug but they also tweaked some
 *	perक्रमmance at the same समय..
 */

#अगर_घोषित CONFIG_X86_32
बाह्य __visible व्योम vide(व्योम);
__यंत्र__(".text\n"
	".globl vide\n"
	".type vide, @function\n"
	".align 4\n"
	"vide: ret\n");
#पूर्ण_अगर

अटल व्योम init_amd_k5(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
/*
 * General Systems BIOSen alias the cpu frequency रेजिस्टरs
 * of the Elan at 0x000df000. Unक्रमtunately, one of the Linux
 * drivers subsequently pokes it, and changes the CPU speed.
 * Workaround : Remove the unneeded alias.
 */
#घोषणा CBAR		(0xfffc) /* Configuration Base Address  (32-bit) */
#घोषणा CBAR_ENB	(0x80000000)
#घोषणा CBAR_KEY	(0X000000CB)
	अगर (c->x86_model == 9 || c->x86_model == 10) अणु
		अगर (inl(CBAR) & CBAR_ENB)
			outl(0 | CBAR_KEY, CBAR);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम init_amd_k6(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
	u32 l, h;
	पूर्णांक mbytes = get_num_physpages() >> (20-PAGE_SHIFT);

	अगर (c->x86_model < 6) अणु
		/* Based on AMD करोc 20734R - June 2000 */
		अगर (c->x86_model == 0) अणु
			clear_cpu_cap(c, X86_FEATURE_APIC);
			set_cpu_cap(c, X86_FEATURE_PGE);
		पूर्ण
		वापस;
	पूर्ण

	अगर (c->x86_model == 6 && c->x86_stepping == 1) अणु
		स्थिर पूर्णांक K6_BUG_LOOP = 1000000;
		पूर्णांक n;
		व्योम (*f_vide)(व्योम);
		u64 d, d2;

		pr_info("AMD K6 stepping B detected - ");

		/*
		 * It looks like AMD fixed the 2.6.2 bug and improved indirect
		 * calls at the same समय.
		 */

		n = K6_BUG_LOOP;
		f_vide = vide;
		OPTIMIZER_HIDE_VAR(f_vide);
		d = rdtsc();
		जबतक (n--)
			f_vide();
		d2 = rdtsc();
		d = d2-d;

		अगर (d > 20*K6_BUG_LOOP)
			pr_cont("system stability may be impaired when more than 32 MB are used.\n");
		अन्यथा
			pr_cont("probably OK (after B9730xxxx).\n");
	पूर्ण

	/* K6 with old style WHCR */
	अगर (c->x86_model < 8 ||
	   (c->x86_model == 8 && c->x86_stepping < 8)) अणु
		/* We can only ग_लिखो allocate on the low 508Mb */
		अगर (mbytes > 508)
			mbytes = 508;

		rdmsr(MSR_K6_WHCR, l, h);
		अगर ((l&0x0000FFFF) == 0) अणु
			अचिन्हित दीर्घ flags;
			l = (1<<0)|((mbytes/4)<<1);
			local_irq_save(flags);
			wbinvd();
			wrmsr(MSR_K6_WHCR, l, h);
			local_irq_restore(flags);
			pr_info("Enabling old style K6 write allocation for %d Mb\n",
				mbytes);
		पूर्ण
		वापस;
	पूर्ण

	अगर ((c->x86_model == 8 && c->x86_stepping > 7) ||
	     c->x86_model == 9 || c->x86_model == 13) अणु
		/* The more serious chips .. */

		अगर (mbytes > 4092)
			mbytes = 4092;

		rdmsr(MSR_K6_WHCR, l, h);
		अगर ((l&0xFFFF0000) == 0) अणु
			अचिन्हित दीर्घ flags;
			l = ((mbytes>>2)<<22)|(1<<16);
			local_irq_save(flags);
			wbinvd();
			wrmsr(MSR_K6_WHCR, l, h);
			local_irq_restore(flags);
			pr_info("Enabling new style K6 write allocation for %d Mb\n",
				mbytes);
		पूर्ण

		वापस;
	पूर्ण

	अगर (c->x86_model == 10) अणु
		/* AMD Geode LX is model 10 */
		/* placeholder क्रम any needed mods */
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम init_amd_k7(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
	u32 l, h;

	/*
	 * Bit 15 of Athlon specअगरic MSR 15, needs to be 0
	 * to enable SSE on Palomino/Morgan/Barton CPU's.
	 * If the BIOS didn't enable it alपढ़ोy, enable it here.
	 */
	अगर (c->x86_model >= 6 && c->x86_model <= 10) अणु
		अगर (!cpu_has(c, X86_FEATURE_XMM)) अणु
			pr_info("Enabling disabled K7/SSE Support.\n");
			msr_clear_bit(MSR_K7_HWCR, 15);
			set_cpu_cap(c, X86_FEATURE_XMM);
		पूर्ण
	पूर्ण

	/*
	 * It's been determined by AMD that Athlons since model 8 stepping 1
	 * are more robust with CLK_CTL set to 200xxxxx instead of 600xxxxx
	 * As per AMD technical note 27212 0.2
	 */
	अगर ((c->x86_model == 8 && c->x86_stepping >= 1) || (c->x86_model > 8)) अणु
		rdmsr(MSR_K7_CLK_CTL, l, h);
		अगर ((l & 0xfff00000) != 0x20000000) अणु
			pr_info("CPU: CLK_CTL MSR was %x. Reprogramming to %x\n",
				l, ((l & 0x000fffff)|0x20000000));
			wrmsr(MSR_K7_CLK_CTL, (l & 0x000fffff)|0x20000000, h);
		पूर्ण
	पूर्ण

	/* calling is from identअगरy_secondary_cpu() ? */
	अगर (!c->cpu_index)
		वापस;

	/*
	 * Certain Athlons might work (क्रम various values of 'work') in SMP
	 * but they are not certअगरied as MP capable.
	 */
	/* Athlon 660/661 is valid. */
	अगर ((c->x86_model == 6) && ((c->x86_stepping == 0) ||
	    (c->x86_stepping == 1)))
		वापस;

	/* Duron 670 is valid */
	अगर ((c->x86_model == 7) && (c->x86_stepping == 0))
		वापस;

	/*
	 * Athlon 662, Duron 671, and Athlon >model 7 have capability
	 * bit. It's worth noting that the A5 stepping (662) of some
	 * Athlon XP's have the MP bit set.
	 * See http://www.heise.de/newsticker/data/jow-18.10.01-000 क्रम
	 * more.
	 */
	अगर (((c->x86_model == 6) && (c->x86_stepping >= 2)) ||
	    ((c->x86_model == 7) && (c->x86_stepping >= 1)) ||
	     (c->x86_model > 7))
		अगर (cpu_has(c, X86_FEATURE_MP))
			वापस;

	/* If we get here, not a certअगरied SMP capable AMD प्रणाली. */

	/*
	 * Don't taपूर्णांक अगर we are running SMP kernel on a single non-MP
	 * approved Athlon
	 */
	WARN_ONCE(1, "WARNING: This combination of AMD"
		" processors is not suitable for SMP.\n");
	add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_NOW_UNRELIABLE);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NUMA
/*
 * To workaround broken NUMA config.  Read the comment in
 * srat_detect_node().
 */
अटल पूर्णांक nearby_node(पूर्णांक apicid)
अणु
	पूर्णांक i, node;

	क्रम (i = apicid - 1; i >= 0; i--) अणु
		node = __apicid_to_node[i];
		अगर (node != NUMA_NO_NODE && node_online(node))
			वापस node;
	पूर्ण
	क्रम (i = apicid + 1; i < MAX_LOCAL_APIC; i++) अणु
		node = __apicid_to_node[i];
		अगर (node != NUMA_NO_NODE && node_online(node))
			वापस node;
	पूर्ण
	वापस first_node(node_online_map); /* Shouldn't happen */
पूर्ण
#पूर्ण_अगर

/*
 * Fix up cpu_core_id क्रम pre-F17h प्रणालीs to be in the
 * [0 .. cores_per_node - 1] range. Not really needed but
 * kept so as not to अवरोध existing setups.
 */
अटल व्योम legacy_fixup_core_id(काष्ठा cpuinfo_x86 *c)
अणु
	u32 cus_per_node;

	अगर (c->x86 >= 0x17)
		वापस;

	cus_per_node = c->x86_max_cores / nodes_per_socket;
	c->cpu_core_id %= cus_per_node;
पूर्ण

/*
 * Fixup core topology inक्रमmation क्रम
 * (1) AMD multi-node processors
 *     Assumption: Number of cores in each पूर्णांकernal node is the same.
 * (2) AMD processors supporting compute units
 */
अटल व्योम amd_get_topology(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* get inक्रमmation required क्रम multi-node processors */
	अगर (boot_cpu_has(X86_FEATURE_TOPOEXT)) अणु
		पूर्णांक err;
		u32 eax, ebx, ecx, edx;

		cpuid(0x8000001e, &eax, &ebx, &ecx, &edx);

		c->cpu_die_id  = ecx & 0xff;

		अगर (c->x86 == 0x15)
			c->cu_id = ebx & 0xff;

		अगर (c->x86 >= 0x17) अणु
			c->cpu_core_id = ebx & 0xff;

			अगर (smp_num_siblings > 1)
				c->x86_max_cores /= smp_num_siblings;
		पूर्ण

		/*
		 * In हाल leaf B is available, use it to derive
		 * topology inक्रमmation.
		 */
		err = detect_extended_topology(c);
		अगर (!err)
			c->x86_coreid_bits = get_count_order(c->x86_max_cores);

		cacheinfo_amd_init_llc_id(c, cpu);

	पूर्ण अन्यथा अगर (cpu_has(c, X86_FEATURE_NODEID_MSR)) अणु
		u64 value;

		rdmsrl(MSR_FAM10H_NODE_ID, value);
		c->cpu_die_id = value & 7;

		per_cpu(cpu_llc_id, cpu) = c->cpu_die_id;
	पूर्ण अन्यथा
		वापस;

	अगर (nodes_per_socket > 1) अणु
		set_cpu_cap(c, X86_FEATURE_AMD_DCM);
		legacy_fixup_core_id(c);
	पूर्ण
पूर्ण

/*
 * On a AMD dual core setup the lower bits of the APIC id distinguish the cores.
 * Assumes number of cores is a घातer of two.
 */
अटल व्योम amd_detect_cmp(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित bits;
	पूर्णांक cpu = smp_processor_id();

	bits = c->x86_coreid_bits;
	/* Low order bits define the core id (index of core in socket) */
	c->cpu_core_id = c->initial_apicid & ((1 << bits)-1);
	/* Convert the initial APIC ID पूर्णांकo the socket ID */
	c->phys_proc_id = c->initial_apicid >> bits;
	/* use socket ID also क्रम last level cache */
	per_cpu(cpu_llc_id, cpu) = c->cpu_die_id = c->phys_proc_id;
पूर्ण

अटल व्योम amd_detect_ppin(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	अगर (!cpu_has(c, X86_FEATURE_AMD_PPIN))
		वापस;

	/* When PPIN is defined in CPUID, still need to check PPIN_CTL MSR */
	अगर (rdmsrl_safe(MSR_AMD_PPIN_CTL, &val))
		जाओ clear_ppin;

	/* PPIN is locked in disabled mode, clear feature bit */
	अगर ((val & 3UL) == 1UL)
		जाओ clear_ppin;

	/* If PPIN is disabled, try to enable it */
	अगर (!(val & 2UL)) अणु
		wrmsrl_safe(MSR_AMD_PPIN_CTL,  val | 2UL);
		rdmsrl_safe(MSR_AMD_PPIN_CTL, &val);
	पूर्ण

	/* If PPIN_EN bit is 1, वापस from here; otherwise fall through */
	अगर (val & 2UL)
		वापस;

clear_ppin:
	clear_cpu_cap(c, X86_FEATURE_AMD_PPIN);
पूर्ण

u32 amd_get_nodes_per_socket(व्योम)
अणु
	वापस nodes_per_socket;
पूर्ण
EXPORT_SYMBOL_GPL(amd_get_nodes_per_socket);

अटल व्योम srat_detect_node(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_NUMA
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक node;
	अचिन्हित apicid = c->apicid;

	node = numa_cpu_node(cpu);
	अगर (node == NUMA_NO_NODE)
		node = per_cpu(cpu_llc_id, cpu);

	/*
	 * On multi-fabric platक्रमm (e.g. Numascale NumaChip) a
	 * platक्रमm-specअगरic handler needs to be called to fixup some
	 * IDs of the CPU.
	 */
	अगर (x86_cpuinit.fixup_cpu_id)
		x86_cpuinit.fixup_cpu_id(c, node);

	अगर (!node_online(node)) अणु
		/*
		 * Two possibilities here:
		 *
		 * - The CPU is missing memory and no node was created.  In
		 *   that हाल try picking one from a nearby CPU.
		 *
		 * - The APIC IDs dअगरfer from the HyperTransport node IDs
		 *   which the K8 northbridge parsing fills in.  Assume
		 *   they are all increased by a स्थिरant offset, but in
		 *   the same order as the HT nodeids.  If that करोesn't
		 *   result in a usable node fall back to the path क्रम the
		 *   previous हाल.
		 *
		 * This workaround operates directly on the mapping between
		 * APIC ID and NUMA node, assuming certain relationship
		 * between APIC ID, HT node ID and NUMA topology.  As going
		 * through CPU mapping may alter the outcome, directly
		 * access __apicid_to_node[].
		 */
		पूर्णांक ht_nodeid = c->initial_apicid;

		अगर (__apicid_to_node[ht_nodeid] != NUMA_NO_NODE)
			node = __apicid_to_node[ht_nodeid];
		/* Pick a nearby node */
		अगर (!node_online(node))
			node = nearby_node(apicid);
	पूर्ण
	numa_set_node(cpu, node);
#पूर्ण_अगर
पूर्ण

अटल व्योम early_init_amd_mc(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित bits, ecx;

	/* Multi core CPU? */
	अगर (c->extended_cpuid_level < 0x80000008)
		वापस;

	ecx = cpuid_ecx(0x80000008);

	c->x86_max_cores = (ecx & 0xff) + 1;

	/* CPU telling us the core id bits shअगरt? */
	bits = (ecx >> 12) & 0xF;

	/* Otherwise recompute */
	अगर (bits == 0) अणु
		जबतक ((1 << bits) < c->x86_max_cores)
			bits++;
	पूर्ण

	c->x86_coreid_bits = bits;
#पूर्ण_अगर
पूर्ण

अटल व्योम bsp_init_amd(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (cpu_has(c, X86_FEATURE_CONSTANT_TSC)) अणु

		अगर (c->x86 > 0x10 ||
		    (c->x86 == 0x10 && c->x86_model >= 0x2)) अणु
			u64 val;

			rdmsrl(MSR_K7_HWCR, val);
			अगर (!(val & BIT(24)))
				pr_warn(FW_BUG "TSC doesn't count with P0 frequency!\n");
		पूर्ण
	पूर्ण

	अगर (c->x86 == 0x15) अणु
		अचिन्हित दीर्घ upperbit;
		u32 cpuid, assoc;

		cpuid	 = cpuid_edx(0x80000005);
		assoc	 = cpuid >> 16 & 0xff;
		upperbit = ((cpuid >> 24) << 10) / assoc;

		va_align.mask	  = (upperbit - 1) & PAGE_MASK;
		va_align.flags    = ALIGN_VA_32 | ALIGN_VA_64;

		/* A अक्रमom value per boot क्रम bit slice [12:upper_bit) */
		va_align.bits = get_अक्रमom_पूर्णांक() & va_align.mask;
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_MWAITX))
		use_mरुकोx_delay();

	अगर (boot_cpu_has(X86_FEATURE_TOPOEXT)) अणु
		u32 ecx;

		ecx = cpuid_ecx(0x8000001e);
		__max_die_per_package = nodes_per_socket = ((ecx >> 8) & 7) + 1;
	पूर्ण अन्यथा अगर (boot_cpu_has(X86_FEATURE_NODEID_MSR)) अणु
		u64 value;

		rdmsrl(MSR_FAM10H_NODE_ID, value);
		__max_die_per_package = nodes_per_socket = ((value >> 3) & 7) + 1;
	पूर्ण

	अगर (!boot_cpu_has(X86_FEATURE_AMD_SSBD) &&
	    !boot_cpu_has(X86_FEATURE_VIRT_SSBD) &&
	    c->x86 >= 0x15 && c->x86 <= 0x17) अणु
		अचिन्हित पूर्णांक bit;

		चयन (c->x86) अणु
		हाल 0x15: bit = 54; अवरोध;
		हाल 0x16: bit = 33; अवरोध;
		हाल 0x17: bit = 10; अवरोध;
		शेष: वापस;
		पूर्ण
		/*
		 * Try to cache the base value so further operations can
		 * aव्योम RMW. If that faults, करो not enable SSBD.
		 */
		अगर (!rdmsrl_safe(MSR_AMD64_LS_CFG, &x86_amd_ls_cfg_base)) अणु
			setup_क्रमce_cpu_cap(X86_FEATURE_LS_CFG_SSBD);
			setup_क्रमce_cpu_cap(X86_FEATURE_SSBD);
			x86_amd_ls_cfg_ssbd_mask = 1ULL << bit;
		पूर्ण
	पूर्ण

	resctrl_cpu_detect(c);
पूर्ण

अटल व्योम early_detect_mem_encrypt(काष्ठा cpuinfo_x86 *c)
अणु
	u64 msr;

	/*
	 * BIOS support is required क्रम SME and SEV.
	 *   For SME: If BIOS has enabled SME then adjust x86_phys_bits by
	 *	      the SME physical address space reduction value.
	 *	      If BIOS has not enabled SME then करोn't advertise the
	 *	      SME feature (set in scattered.c).
	 *   For SEV: If BIOS has not enabled SEV then करोn't advertise the
	 *            SEV and SEV_ES feature (set in scattered.c).
	 *
	 *   In all हालs, since support क्रम SME and SEV requires दीर्घ mode,
	 *   करोn't advertise the feature under CONFIG_X86_32.
	 */
	अगर (cpu_has(c, X86_FEATURE_SME) || cpu_has(c, X86_FEATURE_SEV)) अणु
		/* Check अगर memory encryption is enabled */
		rdmsrl(MSR_AMD64_SYSCFG, msr);
		अगर (!(msr & MSR_AMD64_SYSCFG_MEM_ENCRYPT))
			जाओ clear_all;

		/*
		 * Always adjust physical address bits. Even though this
		 * will be a value above 32-bits this is still करोne क्रम
		 * CONFIG_X86_32 so that accurate values are reported.
		 */
		c->x86_phys_bits -= (cpuid_ebx(0x8000001f) >> 6) & 0x3f;

		अगर (IS_ENABLED(CONFIG_X86_32))
			जाओ clear_all;

		rdmsrl(MSR_K7_HWCR, msr);
		अगर (!(msr & MSR_K7_HWCR_SMMLOCK))
			जाओ clear_sev;

		वापस;

clear_all:
		setup_clear_cpu_cap(X86_FEATURE_SME);
clear_sev:
		setup_clear_cpu_cap(X86_FEATURE_SEV);
		setup_clear_cpu_cap(X86_FEATURE_SEV_ES);
	पूर्ण
पूर्ण

अटल व्योम early_init_amd(काष्ठा cpuinfo_x86 *c)
अणु
	u64 value;
	u32 dummy;

	early_init_amd_mc(c);

	अगर (c->x86 >= 0xf)
		set_cpu_cap(c, X86_FEATURE_K8);

	rdmsr_safe(MSR_AMD64_PATCH_LEVEL, &c->microcode, &dummy);

	/*
	 * c->x86_घातer is 8000_0007 edx. Bit 8 is TSC runs at स्थिरant rate
	 * with P/T states and करोes not stop in deep C-states
	 */
	अगर (c->x86_घातer & (1 << 8)) अणु
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	पूर्ण

	/* Bit 12 of 8000_0007 edx is accumulated घातer mechanism. */
	अगर (c->x86_घातer & BIT(12))
		set_cpu_cap(c, X86_FEATURE_ACC_POWER);

#अगर_घोषित CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSCALL32);
#अन्यथा
	/*  Set MTRR capability flag अगर appropriate */
	अगर (c->x86 == 5)
		अगर (c->x86_model == 13 || c->x86_model == 9 ||
		    (c->x86_model == 8 && c->x86_stepping >= 8))
			set_cpu_cap(c, X86_FEATURE_K6_MTRR);
#पूर्ण_अगर
#अगर defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_PCI)
	/*
	 * ApicID can always be treated as an 8-bit value क्रम AMD APIC versions
	 * >= 0x10, but even old K8s came out of reset with version 0x10. So, we
	 * can safely set X86_FEATURE_EXTD_APICID unconditionally क्रम families
	 * after 16h.
	 */
	अगर (boot_cpu_has(X86_FEATURE_APIC)) अणु
		अगर (c->x86 > 0x16)
			set_cpu_cap(c, X86_FEATURE_EXTD_APICID);
		अन्यथा अगर (c->x86 >= 0xf) अणु
			/* check CPU config space क्रम extended APIC ID */
			अचिन्हित पूर्णांक val;

			val = पढ़ो_pci_config(0, 24, 0, 0x68);
			अगर ((val >> 17 & 0x3) == 0x3)
				set_cpu_cap(c, X86_FEATURE_EXTD_APICID);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * This is only needed to tell the kernel whether to use VMCALL
	 * and VMMCALL.  VMMCALL is never executed except under virt, so
	 * we can set it unconditionally.
	 */
	set_cpu_cap(c, X86_FEATURE_VMMCALL);

	/* F16h erratum 793, CVE-2013-6885 */
	अगर (c->x86 == 0x16 && c->x86_model <= 0xf)
		msr_set_bit(MSR_AMD64_LS_CFG, 15);

	/*
	 * Check whether the machine is affected by erratum 400. This is
	 * used to select the proper idle routine and to enable the check
	 * whether the machine is affected in arch_post_acpi_init(), which
	 * sets the X86_BUG_AMD_APIC_C1E bug depending on the MSR check.
	 */
	अगर (cpu_has_amd_erratum(c, amd_erratum_400))
		set_cpu_bug(c, X86_BUG_AMD_E400);

	early_detect_mem_encrypt(c);

	/* Re-enable TopologyExtensions अगर चयनed off by BIOS */
	अगर (c->x86 == 0x15 &&
	    (c->x86_model >= 0x10 && c->x86_model <= 0x6f) &&
	    !cpu_has(c, X86_FEATURE_TOPOEXT)) अणु

		अगर (msr_set_bit(0xc0011005, 54) > 0) अणु
			rdmsrl(0xc0011005, value);
			अगर (value & BIT_64(54)) अणु
				set_cpu_cap(c, X86_FEATURE_TOPOEXT);
				pr_info_once(FW_INFO "CPU: Re-enabling disabled Topology Extensions Support.\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_TOPOEXT))
		smp_num_siblings = ((cpuid_ebx(0x8000001e) >> 8) & 0xff) + 1;
पूर्ण

अटल व्योम init_amd_k8(काष्ठा cpuinfo_x86 *c)
अणु
	u32 level;
	u64 value;

	/* On C+ stepping K8 rep microcode works well क्रम copy/स_रखो */
	level = cpuid_eax(1);
	अगर ((level >= 0x0f48 && level < 0x0f50) || level >= 0x0f58)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);

	/*
	 * Some BIOSes incorrectly क्रमce this feature, but only K8 revision D
	 * (model = 0x14) and later actually support it.
	 * (AMD Erratum #110, करोcId: 25759).
	 */
	अगर (c->x86_model < 0x14 && cpu_has(c, X86_FEATURE_LAHF_LM)) अणु
		clear_cpu_cap(c, X86_FEATURE_LAHF_LM);
		अगर (!rdmsrl_amd_safe(0xc001100d, &value)) अणु
			value &= ~BIT_64(32);
			wrmsrl_amd_safe(0xc001100d, value);
		पूर्ण
	पूर्ण

	अगर (!c->x86_model_id[0])
		म_नकल(c->x86_model_id, "Hammer");

#अगर_घोषित CONFIG_SMP
	/*
	 * Disable TLB flush filter by setting HWCR.FFDIS on K8
	 * bit 6 of msr C001_0015
	 *
	 * Errata 63 क्रम SH-B3 steppings
	 * Errata 122 क्रम all steppings (F+ have it disabled by शेष)
	 */
	msr_set_bit(MSR_K7_HWCR, 6);
#पूर्ण_अगर
	set_cpu_bug(c, X86_BUG_SWAPGS_FENCE);
पूर्ण

अटल व्योम init_amd_gh(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_MMCONF_FAM10H
	/* करो this क्रम boot cpu */
	अगर (c == &boot_cpu_data)
		check_enable_amd_mmconf_dmi();

	fam10h_check_enable_mmcfg();
#पूर्ण_अगर

	/*
	 * Disable GART TLB Walk Errors on Fam10h. We करो this here because this
	 * is always needed when GART is enabled, even in a kernel which has no
	 * MCE support built in. BIOS should disable GartTlbWlk Errors alपढ़ोy.
	 * If it करोesn't, we करो it here as suggested by the BKDG.
	 *
	 * Fixes: https://bugzilla.kernel.org/show_bug.cgi?id=33012
	 */
	msr_set_bit(MSR_AMD64_MCx_MASK(4), 10);

	/*
	 * On family 10h BIOS may not have properly enabled WC+ support, causing
	 * it to be converted to CD memtype. This may result in perक्रमmance
	 * degradation क्रम certain nested-paging guests. Prevent this conversion
	 * by clearing bit 24 in MSR_AMD64_BU_CFG2.
	 *
	 * NOTE: we want to use the _safe accessors so as not to #GP kvm
	 * guests on older kvm hosts.
	 */
	msr_clear_bit(MSR_AMD64_BU_CFG2, 24);

	अगर (cpu_has_amd_erratum(c, amd_erratum_383))
		set_cpu_bug(c, X86_BUG_AMD_TLB_MMATCH);
पूर्ण

#घोषणा MSR_AMD64_DE_CFG	0xC0011029

अटल व्योम init_amd_ln(काष्ठा cpuinfo_x86 *c)
अणु
	/*
	 * Apply erratum 665 fix unconditionally so machines without a BIOS
	 * fix work.
	 */
	msr_set_bit(MSR_AMD64_DE_CFG, 31);
पूर्ण

अटल bool rdअक्रम_क्रमce;

अटल पूर्णांक __init rdअक्रम_cmdline(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (!म_भेद(str, "force"))
		rdअक्रम_क्रमce = true;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
early_param("rdrand", rdअक्रम_cmdline);

अटल व्योम clear_rdअक्रम_cpuid_bit(काष्ठा cpuinfo_x86 *c)
अणु
	/*
	 * Saving of the MSR used to hide the RDRAND support during
	 * suspend/resume is करोne by arch/x86/घातer/cpu.c, which is
	 * dependent on CONFIG_PM_SLEEP.
	 */
	अगर (!IS_ENABLED(CONFIG_PM_SLEEP))
		वापस;

	/*
	 * The nordअक्रम option can clear X86_FEATURE_RDRAND, so check क्रम
	 * RDRAND support using the CPUID function directly.
	 */
	अगर (!(cpuid_ecx(1) & BIT(30)) || rdअक्रम_क्रमce)
		वापस;

	msr_clear_bit(MSR_AMD64_CPUID_FN_1, 62);

	/*
	 * Verअगरy that the CPUID change has occurred in हाल the kernel is
	 * running भवized and the hypervisor करोesn't support the MSR.
	 */
	अगर (cpuid_ecx(1) & BIT(30)) अणु
		pr_info_once("BIOS may not properly restore RDRAND after suspend, but hypervisor does not support hiding RDRAND via CPUID.\n");
		वापस;
	पूर्ण

	clear_cpu_cap(c, X86_FEATURE_RDRAND);
	pr_info_once("BIOS may not properly restore RDRAND after suspend, hiding RDRAND via CPUID. Use rdrand=force to reenable.\n");
पूर्ण

अटल व्योम init_amd_jg(काष्ठा cpuinfo_x86 *c)
अणु
	/*
	 * Some BIOS implementations करो not restore proper RDRAND support
	 * across suspend and resume. Check on whether to hide the RDRAND
	 * inकाष्ठाion support via CPUID.
	 */
	clear_rdअक्रम_cpuid_bit(c);
पूर्ण

अटल व्योम init_amd_bd(काष्ठा cpuinfo_x86 *c)
अणु
	u64 value;

	/*
	 * The way access filter has a perक्रमmance penalty on some workloads.
	 * Disable it on the affected CPUs.
	 */
	अगर ((c->x86_model >= 0x02) && (c->x86_model < 0x20)) अणु
		अगर (!rdmsrl_safe(MSR_F15H_IC_CFG, &value) && !(value & 0x1E)) अणु
			value |= 0x1E;
			wrmsrl_safe(MSR_F15H_IC_CFG, value);
		पूर्ण
	पूर्ण

	/*
	 * Some BIOS implementations करो not restore proper RDRAND support
	 * across suspend and resume. Check on whether to hide the RDRAND
	 * inकाष्ठाion support via CPUID.
	 */
	clear_rdअक्रम_cpuid_bit(c);
पूर्ण

अटल व्योम init_amd_zn(काष्ठा cpuinfo_x86 *c)
अणु
	set_cpu_cap(c, X86_FEATURE_ZEN);

#अगर_घोषित CONFIG_NUMA
	node_reclaim_distance = 32;
#पूर्ण_अगर

	/*
	 * Fix erratum 1076: CPB feature bit not being set in CPUID.
	 * Always set it, except when running under a hypervisor.
	 */
	अगर (!cpu_has(c, X86_FEATURE_HYPERVISOR) && !cpu_has(c, X86_FEATURE_CPB))
		set_cpu_cap(c, X86_FEATURE_CPB);
पूर्ण

अटल व्योम init_amd(काष्ठा cpuinfo_x86 *c)
अणु
	early_init_amd(c);

	/*
	 * Bit 31 in normal CPUID used क्रम nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);

	अगर (c->x86 >= 0x10)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);

	/* get apicid instead of initial apic id from cpuid */
	c->apicid = hard_smp_processor_id();

	/* K6s reports MCEs but करोn't actually have all the MSRs */
	अगर (c->x86 < 6)
		clear_cpu_cap(c, X86_FEATURE_MCE);

	चयन (c->x86) अणु
	हाल 4:    init_amd_k5(c); अवरोध;
	हाल 5:    init_amd_k6(c); अवरोध;
	हाल 6:	   init_amd_k7(c); अवरोध;
	हाल 0xf:  init_amd_k8(c); अवरोध;
	हाल 0x10: init_amd_gh(c); अवरोध;
	हाल 0x12: init_amd_ln(c); अवरोध;
	हाल 0x15: init_amd_bd(c); अवरोध;
	हाल 0x16: init_amd_jg(c); अवरोध;
	हाल 0x17: fallthrough;
	हाल 0x19: init_amd_zn(c); अवरोध;
	पूर्ण

	/*
	 * Enable workaround क्रम FXSAVE leak on CPUs
	 * without a XSaveErPtr feature
	 */
	अगर ((c->x86 >= 6) && (!cpu_has(c, X86_FEATURE_XSAVEERPTR)))
		set_cpu_bug(c, X86_BUG_FXSAVE_LEAK);

	cpu_detect_cache_sizes(c);

	amd_detect_cmp(c);
	amd_get_topology(c);
	srat_detect_node(c);
	amd_detect_ppin(c);

	init_amd_cacheinfo(c);

	अगर (cpu_has(c, X86_FEATURE_XMM2)) अणु
		/*
		 * Use LFENCE क्रम execution serialization.  On families which
		 * करोn't have that MSR, LFENCE is alपढ़ोy serializing.
		 * msr_set_bit() uses the safe accessors, too, even अगर the MSR
		 * is not present.
		 */
		msr_set_bit(MSR_F10H_DECFG,
			    MSR_F10H_DECFG_LFENCE_SERIALIZE_BIT);

		/* A serializing LFENCE stops RDTSC speculation */
		set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);
	पूर्ण

	/*
	 * Family 0x12 and above processors have APIC समयr
	 * running in deep C states.
	 */
	अगर (c->x86 > 0x11)
		set_cpu_cap(c, X86_FEATURE_ARAT);

	/* 3DNow or LM implies PREFETCHW */
	अगर (!cpu_has(c, X86_FEATURE_3DNOWPREFETCH))
		अगर (cpu_has(c, X86_FEATURE_3DNOW) || cpu_has(c, X86_FEATURE_LM))
			set_cpu_cap(c, X86_FEATURE_3DNOWPREFETCH);

	/* AMD CPUs करोn't reset SS attributes on SYSRET, Xen करोes. */
	अगर (!cpu_has(c, X86_FEATURE_XENPV))
		set_cpu_bug(c, X86_BUG_SYSRET_SS_ATTRS);

	/*
	 * Turn on the Inकाष्ठाions Retired मुक्त counter on machines not
	 * susceptible to erratum #1054 "Inकाष्ठाions Retired Perक्रमmance
	 * Counter May Be Inaccurate".
	 */
	अगर (cpu_has(c, X86_FEATURE_IRPERF) &&
	    !cpu_has_amd_erratum(c, amd_erratum_1054))
		msr_set_bit(MSR_K7_HWCR, MSR_K7_HWCR_IRPERF_EN_BIT);
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल अचिन्हित पूर्णांक amd_size_cache(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक size)
अणु
	/* AMD errata T13 (order #21922) */
	अगर (c->x86 == 6) अणु
		/* Duron Rev A0 */
		अगर (c->x86_model == 3 && c->x86_stepping == 0)
			size = 64;
		/* Tbird rev A1/A2 */
		अगर (c->x86_model == 4 &&
			(c->x86_stepping == 0 || c->x86_stepping == 1))
			size = 256;
	पूर्ण
	वापस size;
पूर्ण
#पूर्ण_अगर

अटल व्योम cpu_detect_tlb_amd(काष्ठा cpuinfo_x86 *c)
अणु
	u32 ebx, eax, ecx, edx;
	u16 mask = 0xfff;

	अगर (c->x86 < 0xf)
		वापस;

	अगर (c->extended_cpuid_level < 0x80000006)
		वापस;

	cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	tlb_lld_4k[ENTRIES] = (ebx >> 16) & mask;
	tlb_lli_4k[ENTRIES] = ebx & mask;

	/*
	 * K8 करोesn't have 2M/4M entries in the L2 TLB so पढ़ो out the L1 TLB
	 * अक्षरacteristics from the CPUID function 0x80000005 instead.
	 */
	अगर (c->x86 == 0xf) अणु
		cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
		mask = 0xff;
	पूर्ण

	/* Handle DTLB 2M and 4M sizes, fall back to L1 अगर L2 is disabled */
	अगर (!((eax >> 16) & mask))
		tlb_lld_2m[ENTRIES] = (cpuid_eax(0x80000005) >> 16) & 0xff;
	अन्यथा
		tlb_lld_2m[ENTRIES] = (eax >> 16) & mask;

	/* a 4M entry uses two 2M entries */
	tlb_lld_4m[ENTRIES] = tlb_lld_2m[ENTRIES] >> 1;

	/* Handle ITLB 2M and 4M sizes, fall back to L1 अगर L2 is disabled */
	अगर (!(eax & mask)) अणु
		/* Erratum 658 */
		अगर (c->x86 == 0x15 && c->x86_model <= 0x1f) अणु
			tlb_lli_2m[ENTRIES] = 1024;
		पूर्ण अन्यथा अणु
			cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
			tlb_lli_2m[ENTRIES] = eax & 0xff;
		पूर्ण
	पूर्ण अन्यथा
		tlb_lli_2m[ENTRIES] = eax & mask;

	tlb_lli_4m[ENTRIES] = tlb_lli_2m[ENTRIES] >> 1;
पूर्ण

अटल स्थिर काष्ठा cpu_dev amd_cpu_dev = अणु
	.c_venकरोr	= "AMD",
	.c_ident	= अणु "AuthenticAMD" पूर्ण,
#अगर_घोषित CONFIG_X86_32
	.legacy_models = अणु
		अणु .family = 4, .model_names =
		  अणु
			  [3] = "486 DX/2",
			  [7] = "486 DX/2-WB",
			  [8] = "486 DX/4",
			  [9] = "486 DX/4-WB",
			  [14] = "Am5x86-WT",
			  [15] = "Am5x86-WB"
		  पूर्ण
		पूर्ण,
	पूर्ण,
	.legacy_cache_size = amd_size_cache,
#पूर्ण_अगर
	.c_early_init   = early_init_amd,
	.c_detect_tlb	= cpu_detect_tlb_amd,
	.c_bsp_init	= bsp_init_amd,
	.c_init		= init_amd,
	.c_x86_venकरोr	= X86_VENDOR_AMD,
पूर्ण;

cpu_dev_रेजिस्टर(amd_cpu_dev);

/*
 * AMD errata checking
 *
 * Errata are defined as arrays of पूर्णांकs using the AMD_LEGACY_ERRATUM() or
 * AMD_OSVW_ERRATUM() macros. The latter is पूर्णांकended क्रम newer errata that
 * have an OSVW id asचिन्हित, which it takes as first argument. Both take a
 * variable number of family-specअगरic model-stepping ranges created by
 * AMD_MODEL_RANGE().
 *
 * Example:
 *
 * स्थिर पूर्णांक amd_erratum_319[] =
 *	AMD_LEGACY_ERRATUM(AMD_MODEL_RANGE(0x10, 0x2, 0x1, 0x4, 0x2),
 *			   AMD_MODEL_RANGE(0x10, 0x8, 0x0, 0x8, 0x0),
 *			   AMD_MODEL_RANGE(0x10, 0x9, 0x0, 0x9, 0x0));
 */

#घोषणा AMD_LEGACY_ERRATUM(...)		अणु -1, __VA_ARGS__, 0 पूर्ण
#घोषणा AMD_OSVW_ERRATUM(osvw_id, ...)	अणु osvw_id, __VA_ARGS__, 0 पूर्ण
#घोषणा AMD_MODEL_RANGE(f, m_start, s_start, m_end, s_end) \
	((f << 24) | (m_start << 16) | (s_start << 12) | (m_end << 4) | (s_end))
#घोषणा AMD_MODEL_RANGE_FAMILY(range)	(((range) >> 24) & 0xff)
#घोषणा AMD_MODEL_RANGE_START(range)	(((range) >> 12) & 0xfff)
#घोषणा AMD_MODEL_RANGE_END(range)	((range) & 0xfff)

अटल स्थिर पूर्णांक amd_erratum_400[] =
	AMD_OSVW_ERRATUM(1, AMD_MODEL_RANGE(0xf, 0x41, 0x2, 0xff, 0xf),
			    AMD_MODEL_RANGE(0x10, 0x2, 0x1, 0xff, 0xf));

अटल स्थिर पूर्णांक amd_erratum_383[] =
	AMD_OSVW_ERRATUM(3, AMD_MODEL_RANGE(0x10, 0, 0, 0xff, 0xf));

/* #1054: Inकाष्ठाions Retired Perक्रमmance Counter May Be Inaccurate */
अटल स्थिर पूर्णांक amd_erratum_1054[] =
	AMD_LEGACY_ERRATUM(AMD_MODEL_RANGE(0x17, 0, 0, 0x2f, 0xf));

अटल bool cpu_has_amd_erratum(काष्ठा cpuinfo_x86 *cpu, स्थिर पूर्णांक *erratum)
अणु
	पूर्णांक osvw_id = *erratum++;
	u32 range;
	u32 ms;

	अगर (osvw_id >= 0 && osvw_id < 65536 &&
	    cpu_has(cpu, X86_FEATURE_OSVW)) अणु
		u64 osvw_len;

		rdmsrl(MSR_AMD64_OSVW_ID_LENGTH, osvw_len);
		अगर (osvw_id < osvw_len) अणु
			u64 osvw_bits;

			rdmsrl(MSR_AMD64_OSVW_STATUS + (osvw_id >> 6),
			    osvw_bits);
			वापस osvw_bits & (1ULL << (osvw_id & 0x3f));
		पूर्ण
	पूर्ण

	/* OSVW unavailable or ID unknown, match family-model-stepping range */
	ms = (cpu->x86_model << 4) | cpu->x86_stepping;
	जबतक ((range = *erratum++))
		अगर ((cpu->x86 == AMD_MODEL_RANGE_FAMILY(range)) &&
		    (ms >= AMD_MODEL_RANGE_START(range)) &&
		    (ms <= AMD_MODEL_RANGE_END(range)))
			वापस true;

	वापस false;
पूर्ण

व्योम set_dr_addr_mask(अचिन्हित दीर्घ mask, पूर्णांक dr)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_BPEXT))
		वापस;

	चयन (dr) अणु
	हाल 0:
		wrmsr(MSR_F16H_DR0_ADDR_MASK, mask, 0);
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
		wrmsr(MSR_F16H_DR1_ADDR_MASK - 1 + dr, mask, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u32 amd_get_highest_perf(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर (c->x86 == 0x17 && ((c->x86_model >= 0x30 && c->x86_model < 0x40) ||
			       (c->x86_model >= 0x70 && c->x86_model < 0x80)))
		वापस 166;

	अगर (c->x86 == 0x19 && ((c->x86_model >= 0x20 && c->x86_model < 0x30) ||
			       (c->x86_model >= 0x40 && c->x86_model < 0x70)))
		वापस 166;

	वापस 255;
पूर्ण
EXPORT_SYMBOL_GPL(amd_get_highest_perf);
