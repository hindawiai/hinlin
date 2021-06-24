<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hygon Processor Support क्रम Linux
 *
 * Copyright (C) 2018 Chengdu Haiguang IC Design Co., Ltd.
 *
 * Author: Pu Wen <puwen@hygon.cn>
 */
#समावेश <linux/पन.स>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/cacheinfo.h>
#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/delay.h>

#समावेश "cpu.h"

#घोषणा APICID_SOCKET_ID_BIT 6

/*
 * nodes_per_socket: Stores the number of nodes per socket.
 * Refer to CPUID Fn8000_001E_ECX Node Identअगरiers[10:8]
 */
अटल u32 nodes_per_socket = 1;

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

अटल व्योम hygon_get_topology_early(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (cpu_has(c, X86_FEATURE_TOPOEXT))
		smp_num_siblings = ((cpuid_ebx(0x8000001e) >> 8) & 0xff) + 1;
पूर्ण

/*
 * Fixup core topology inक्रमmation क्रम
 * (1) Hygon multi-node processors
 *     Assumption: Number of cores in each पूर्णांकernal node is the same.
 * (2) Hygon processors supporting compute units
 */
अटल व्योम hygon_get_topology(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* get inक्रमmation required क्रम multi-node processors */
	अगर (boot_cpu_has(X86_FEATURE_TOPOEXT)) अणु
		पूर्णांक err;
		u32 eax, ebx, ecx, edx;

		cpuid(0x8000001e, &eax, &ebx, &ecx, &edx);

		c->cpu_die_id  = ecx & 0xff;

		c->cpu_core_id = ebx & 0xff;

		अगर (smp_num_siblings > 1)
			c->x86_max_cores /= smp_num_siblings;

		/*
		 * In हाल leaf B is available, use it to derive
		 * topology inक्रमmation.
		 */
		err = detect_extended_topology(c);
		अगर (!err)
			c->x86_coreid_bits = get_count_order(c->x86_max_cores);

		/* Socket ID is ApicId[6] क्रम these processors. */
		c->phys_proc_id = c->apicid >> APICID_SOCKET_ID_BIT;

		cacheinfo_hygon_init_llc_id(c, cpu);
	पूर्ण अन्यथा अगर (cpu_has(c, X86_FEATURE_NODEID_MSR)) अणु
		u64 value;

		rdmsrl(MSR_FAM10H_NODE_ID, value);
		c->cpu_die_id = value & 7;

		per_cpu(cpu_llc_id, cpu) = c->cpu_die_id;
	पूर्ण अन्यथा
		वापस;

	अगर (nodes_per_socket > 1)
		set_cpu_cap(c, X86_FEATURE_AMD_DCM);
पूर्ण

/*
 * On Hygon setup the lower bits of the APIC id distinguish the cores.
 * Assumes number of cores is a घातer of two.
 */
अटल व्योम hygon_detect_cmp(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक bits;
	पूर्णांक cpu = smp_processor_id();

	bits = c->x86_coreid_bits;
	/* Low order bits define the core id (index of core in socket) */
	c->cpu_core_id = c->initial_apicid & ((1 << bits)-1);
	/* Convert the initial APIC ID पूर्णांकo the socket ID */
	c->phys_proc_id = c->initial_apicid >> bits;
	/* use socket ID also क्रम last level cache */
	per_cpu(cpu_llc_id, cpu) = c->cpu_die_id = c->phys_proc_id;
पूर्ण

अटल व्योम srat_detect_node(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_NUMA
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक node;
	अचिन्हित पूर्णांक apicid = c->apicid;

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
		 * - The APIC IDs dअगरfer from the HyperTransport node IDs.
		 *   Assume they are all increased by a स्थिरant offset, but
		 *   in the same order as the HT nodeids.  If that करोesn't
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

अटल व्योम early_init_hygon_mc(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक bits, ecx;

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

अटल व्योम bsp_init_hygon(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (cpu_has(c, X86_FEATURE_CONSTANT_TSC)) अणु
		u64 val;

		rdmsrl(MSR_K7_HWCR, val);
		अगर (!(val & BIT(24)))
			pr_warn(FW_BUG "TSC doesn't count with P0 frequency!\n");
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
	    !boot_cpu_has(X86_FEATURE_VIRT_SSBD)) अणु
		/*
		 * Try to cache the base value so further operations can
		 * aव्योम RMW. If that faults, करो not enable SSBD.
		 */
		अगर (!rdmsrl_safe(MSR_AMD64_LS_CFG, &x86_amd_ls_cfg_base)) अणु
			setup_क्रमce_cpu_cap(X86_FEATURE_LS_CFG_SSBD);
			setup_क्रमce_cpu_cap(X86_FEATURE_SSBD);
			x86_amd_ls_cfg_ssbd_mask = 1ULL << 10;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम early_init_hygon(काष्ठा cpuinfo_x86 *c)
अणु
	u32 dummy;

	early_init_hygon_mc(c);

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
#पूर्ण_अगर

#अगर defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_PCI)
	/*
	 * ApicID can always be treated as an 8-bit value क्रम Hygon APIC So, we
	 * can safely set X86_FEATURE_EXTD_APICID unconditionally.
	 */
	अगर (boot_cpu_has(X86_FEATURE_APIC))
		set_cpu_cap(c, X86_FEATURE_EXTD_APICID);
#पूर्ण_अगर

	/*
	 * This is only needed to tell the kernel whether to use VMCALL
	 * and VMMCALL.  VMMCALL is never executed except under virt, so
	 * we can set it unconditionally.
	 */
	set_cpu_cap(c, X86_FEATURE_VMMCALL);

	hygon_get_topology_early(c);
पूर्ण

अटल व्योम init_hygon(काष्ठा cpuinfo_x86 *c)
अणु
	early_init_hygon(c);

	/*
	 * Bit 31 in normal CPUID used क्रम nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);

	set_cpu_cap(c, X86_FEATURE_REP_GOOD);

	/* get apicid instead of initial apic id from cpuid */
	c->apicid = hard_smp_processor_id();

	set_cpu_cap(c, X86_FEATURE_ZEN);
	set_cpu_cap(c, X86_FEATURE_CPB);

	cpu_detect_cache_sizes(c);

	hygon_detect_cmp(c);
	hygon_get_topology(c);
	srat_detect_node(c);

	init_hygon_cacheinfo(c);

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
	 * Hygon processors have APIC समयr running in deep C states.
	 */
	set_cpu_cap(c, X86_FEATURE_ARAT);

	/* Hygon CPUs करोn't reset SS attributes on SYSRET, Xen करोes. */
	अगर (!cpu_has(c, X86_FEATURE_XENPV))
		set_cpu_bug(c, X86_BUG_SYSRET_SS_ATTRS);
पूर्ण

अटल व्योम cpu_detect_tlb_hygon(काष्ठा cpuinfo_x86 *c)
अणु
	u32 ebx, eax, ecx, edx;
	u16 mask = 0xfff;

	अगर (c->extended_cpuid_level < 0x80000006)
		वापस;

	cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	tlb_lld_4k[ENTRIES] = (ebx >> 16) & mask;
	tlb_lli_4k[ENTRIES] = ebx & mask;

	/* Handle DTLB 2M and 4M sizes, fall back to L1 अगर L2 is disabled */
	अगर (!((eax >> 16) & mask))
		tlb_lld_2m[ENTRIES] = (cpuid_eax(0x80000005) >> 16) & 0xff;
	अन्यथा
		tlb_lld_2m[ENTRIES] = (eax >> 16) & mask;

	/* a 4M entry uses two 2M entries */
	tlb_lld_4m[ENTRIES] = tlb_lld_2m[ENTRIES] >> 1;

	/* Handle ITLB 2M and 4M sizes, fall back to L1 अगर L2 is disabled */
	अगर (!(eax & mask)) अणु
		cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
		tlb_lli_2m[ENTRIES] = eax & 0xff;
	पूर्ण अन्यथा
		tlb_lli_2m[ENTRIES] = eax & mask;

	tlb_lli_4m[ENTRIES] = tlb_lli_2m[ENTRIES] >> 1;
पूर्ण

अटल स्थिर काष्ठा cpu_dev hygon_cpu_dev = अणु
	.c_venकरोr	= "Hygon",
	.c_ident	= अणु "HygonGenuine" पूर्ण,
	.c_early_init   = early_init_hygon,
	.c_detect_tlb	= cpu_detect_tlb_hygon,
	.c_bsp_init	= bsp_init_hygon,
	.c_init		= init_hygon,
	.c_x86_venकरोr	= X86_VENDOR_HYGON,
पूर्ण;

cpu_dev_रेजिस्टर(hygon_cpu_dev);
