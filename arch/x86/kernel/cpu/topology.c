<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Check क्रम extended topology क्रमागतeration cpuid leaf 0xb and अगर it
 * exists, use it क्रम populating initial_apicid and cpu topology
 * detection.
 */

#समावेश <linux/cpu.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/processor.h>

#समावेश "cpu.h"

/* leaf 0xb SMT level */
#घोषणा SMT_LEVEL	0

/* extended topology sub-leaf types */
#घोषणा INVALID_TYPE	0
#घोषणा SMT_TYPE	1
#घोषणा CORE_TYPE	2
#घोषणा DIE_TYPE	5

#घोषणा LEAFB_SUBTYPE(ecx)		(((ecx) >> 8) & 0xff)
#घोषणा BITS_SHIFT_NEXT_LEVEL(eax)	((eax) & 0x1f)
#घोषणा LEVEL_MAX_SIBLINGS(ebx)		((ebx) & 0xffff)

अचिन्हित पूर्णांक __max_die_per_package __पढ़ो_mostly = 1;
EXPORT_SYMBOL(__max_die_per_package);

#अगर_घोषित CONFIG_SMP
/*
 * Check अगर given CPUID extended topology "leaf" is implemented
 */
अटल पूर्णांक check_extended_topology_leaf(पूर्णांक leaf)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	cpuid_count(leaf, SMT_LEVEL, &eax, &ebx, &ecx, &edx);

	अगर (ebx == 0 || (LEAFB_SUBTYPE(ecx) != SMT_TYPE))
		वापस -1;

	वापस 0;
पूर्ण
/*
 * Return best CPUID Extended Topology Leaf supported
 */
अटल पूर्णांक detect_extended_topology_leaf(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->cpuid_level >= 0x1f) अणु
		अगर (check_extended_topology_leaf(0x1f) == 0)
			वापस 0x1f;
	पूर्ण

	अगर (c->cpuid_level >= 0xb) अणु
		अगर (check_extended_topology_leaf(0xb) == 0)
			वापस 0xb;
	पूर्ण

	वापस -1;
पूर्ण
#पूर्ण_अगर

पूर्णांक detect_extended_topology_early(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	पूर्णांक leaf;

	leaf = detect_extended_topology_leaf(c);
	अगर (leaf < 0)
		वापस -1;

	set_cpu_cap(c, X86_FEATURE_XTOPOLOGY);

	cpuid_count(leaf, SMT_LEVEL, &eax, &ebx, &ecx, &edx);
	/*
	 * initial apic id, which also represents 32-bit extended x2apic id.
	 */
	c->initial_apicid = edx;
	smp_num_siblings = LEVEL_MAX_SIBLINGS(ebx);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Check क्रम extended topology क्रमागतeration cpuid leaf, and अगर it
 * exists, use it क्रम populating initial_apicid and cpu topology
 * detection.
 */
पूर्णांक detect_extended_topology(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक eax, ebx, ecx, edx, sub_index;
	अचिन्हित पूर्णांक ht_mask_width, core_plus_mask_width, die_plus_mask_width;
	अचिन्हित पूर्णांक core_select_mask, core_level_siblings;
	अचिन्हित पूर्णांक die_select_mask, die_level_siblings;
	bool die_level_present = false;
	पूर्णांक leaf;

	leaf = detect_extended_topology_leaf(c);
	अगर (leaf < 0)
		वापस -1;

	/*
	 * Populate HT related inक्रमmation from sub-leaf level 0.
	 */
	cpuid_count(leaf, SMT_LEVEL, &eax, &ebx, &ecx, &edx);
	c->initial_apicid = edx;
	core_level_siblings = smp_num_siblings = LEVEL_MAX_SIBLINGS(ebx);
	core_plus_mask_width = ht_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
	die_level_siblings = LEVEL_MAX_SIBLINGS(ebx);
	die_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);

	sub_index = 1;
	करो अणु
		cpuid_count(leaf, sub_index, &eax, &ebx, &ecx, &edx);

		/*
		 * Check क्रम the Core type in the implemented sub leaves.
		 */
		अगर (LEAFB_SUBTYPE(ecx) == CORE_TYPE) अणु
			core_level_siblings = LEVEL_MAX_SIBLINGS(ebx);
			core_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
			die_level_siblings = core_level_siblings;
			die_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
		पूर्ण
		अगर (LEAFB_SUBTYPE(ecx) == DIE_TYPE) अणु
			die_level_present = true;
			die_level_siblings = LEVEL_MAX_SIBLINGS(ebx);
			die_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
		पूर्ण

		sub_index++;
	पूर्ण जबतक (LEAFB_SUBTYPE(ecx) != INVALID_TYPE);

	core_select_mask = (~(-1 << core_plus_mask_width)) >> ht_mask_width;
	die_select_mask = (~(-1 << die_plus_mask_width)) >>
				core_plus_mask_width;

	c->cpu_core_id = apic->phys_pkg_id(c->initial_apicid,
				ht_mask_width) & core_select_mask;

	अगर (die_level_present) अणु
		c->cpu_die_id = apic->phys_pkg_id(c->initial_apicid,
					core_plus_mask_width) & die_select_mask;
	पूर्ण

	c->phys_proc_id = apic->phys_pkg_id(c->initial_apicid,
				die_plus_mask_width);
	/*
	 * Reinit the apicid, now that we have extended initial_apicid.
	 */
	c->apicid = apic->phys_pkg_id(c->initial_apicid, 0);

	c->x86_max_cores = (core_level_siblings / smp_num_siblings);
	__max_die_per_package = (die_level_siblings / core_level_siblings);
#पूर्ण_अगर
	वापस 0;
पूर्ण
