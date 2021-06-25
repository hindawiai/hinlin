<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Routines to identअगरy caches on Intel CPU.
 *
 *	Changes:
 *	Venkatesh Pallipadi	: Adding cache identअगरication through cpuid(4)
 *	Ashok Raj <ashok.raj@पूर्णांकel.com>: Work with CPU hotplug infraकाष्ठाure.
 *	Andi Kleen / Andreas Herrmann	: CPUID4 emulation on AMD.
 */

#समावेश <linux/slab.h>
#समावेश <linux/cacheinfo.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/capability.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cacheinfo.h>
#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/smp.h>

#समावेश "cpu.h"

#घोषणा LVL_1_INST	1
#घोषणा LVL_1_DATA	2
#घोषणा LVL_2		3
#घोषणा LVL_3		4
#घोषणा LVL_TRACE	5

काष्ठा _cache_table अणु
	अचिन्हित अक्षर descriptor;
	अक्षर cache_type;
	लघु size;
पूर्ण;

#घोषणा MB(x)	((x) * 1024)

/* All the cache descriptor types we care about (no TLB or
   trace cache entries) */

अटल स्थिर काष्ठा _cache_table cache_table[] =
अणु
	अणु 0x06, LVL_1_INST, 8 पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x08, LVL_1_INST, 16 पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x09, LVL_1_INST, 32 पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0x0a, LVL_1_DATA, 8 पूर्ण,	/* 2 way set assoc, 32 byte line size */
	अणु 0x0c, LVL_1_DATA, 16 पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x0d, LVL_1_DATA, 16 पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0x0e, LVL_1_DATA, 24 पूर्ण,	/* 6-way set assoc, 64 byte line size */
	अणु 0x21, LVL_2,      256 पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0x22, LVL_3,      512 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x23, LVL_3,      MB(1) पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x25, LVL_3,      MB(2) पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x29, LVL_3,      MB(4) पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x2c, LVL_1_DATA, 32 पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0x30, LVL_1_INST, 32 पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0x39, LVL_2,      128 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x3a, LVL_2,      192 पूर्ण,	/* 6-way set assoc, sectored cache, 64 byte line size */
	अणु 0x3b, LVL_2,      128 पूर्ण,	/* 2-way set assoc, sectored cache, 64 byte line size */
	अणु 0x3c, LVL_2,      256 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x3d, LVL_2,      384 पूर्ण,	/* 6-way set assoc, sectored cache, 64 byte line size */
	अणु 0x3e, LVL_2,      512 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x3f, LVL_2,      256 पूर्ण,	/* 2-way set assoc, 64 byte line size */
	अणु 0x41, LVL_2,      128 पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x42, LVL_2,      256 पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x43, LVL_2,      512 पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x44, LVL_2,      MB(1) पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x45, LVL_2,      MB(2) पूर्ण,	/* 4-way set assoc, 32 byte line size */
	अणु 0x46, LVL_3,      MB(4) पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0x47, LVL_3,      MB(8) पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0x48, LVL_2,      MB(3) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0x49, LVL_3,      MB(4) पूर्ण,	/* 16-way set assoc, 64 byte line size */
	अणु 0x4a, LVL_3,      MB(6) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0x4b, LVL_3,      MB(8) पूर्ण,	/* 16-way set assoc, 64 byte line size */
	अणु 0x4c, LVL_3,      MB(12) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0x4d, LVL_3,      MB(16) पूर्ण,	/* 16-way set assoc, 64 byte line size */
	अणु 0x4e, LVL_2,      MB(6) पूर्ण,	/* 24-way set assoc, 64 byte line size */
	अणु 0x60, LVL_1_DATA, 16 पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x66, LVL_1_DATA, 8 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x67, LVL_1_DATA, 16 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x68, LVL_1_DATA, 32 पूर्ण,	/* 4-way set assoc, sectored cache, 64 byte line size */
	अणु 0x70, LVL_TRACE,  12 पूर्ण,	/* 8-way set assoc */
	अणु 0x71, LVL_TRACE,  16 पूर्ण,	/* 8-way set assoc */
	अणु 0x72, LVL_TRACE,  32 पूर्ण,	/* 8-way set assoc */
	अणु 0x73, LVL_TRACE,  64 पूर्ण,	/* 8-way set assoc */
	अणु 0x78, LVL_2,      MB(1) पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0x79, LVL_2,      128 पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x7a, LVL_2,      256 पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x7b, LVL_2,      512 पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x7c, LVL_2,      MB(1) पूर्ण,	/* 8-way set assoc, sectored cache, 64 byte line size */
	अणु 0x7d, LVL_2,      MB(2) पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0x7f, LVL_2,      512 पूर्ण,	/* 2-way set assoc, 64 byte line size */
	अणु 0x80, LVL_2,      512 पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0x82, LVL_2,      256 पूर्ण,	/* 8-way set assoc, 32 byte line size */
	अणु 0x83, LVL_2,      512 पूर्ण,	/* 8-way set assoc, 32 byte line size */
	अणु 0x84, LVL_2,      MB(1) पूर्ण,	/* 8-way set assoc, 32 byte line size */
	अणु 0x85, LVL_2,      MB(2) पूर्ण,	/* 8-way set assoc, 32 byte line size */
	अणु 0x86, LVL_2,      512 पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0x87, LVL_2,      MB(1) पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0xd0, LVL_3,      512 पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0xd1, LVL_3,      MB(1) पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0xd2, LVL_3,      MB(2) पूर्ण,	/* 4-way set assoc, 64 byte line size */
	अणु 0xd6, LVL_3,      MB(1) पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0xd7, LVL_3,      MB(2) पूर्ण,	/* 8-way set assoc, 64 byte line size */
	अणु 0xd8, LVL_3,      MB(4) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0xdc, LVL_3,      MB(2) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0xdd, LVL_3,      MB(4) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0xde, LVL_3,      MB(8) पूर्ण,	/* 12-way set assoc, 64 byte line size */
	अणु 0xe2, LVL_3,      MB(2) पूर्ण,	/* 16-way set assoc, 64 byte line size */
	अणु 0xe3, LVL_3,      MB(4) पूर्ण,	/* 16-way set assoc, 64 byte line size */
	अणु 0xe4, LVL_3,      MB(8) पूर्ण,	/* 16-way set assoc, 64 byte line size */
	अणु 0xea, LVL_3,      MB(12) पूर्ण,	/* 24-way set assoc, 64 byte line size */
	अणु 0xeb, LVL_3,      MB(18) पूर्ण,	/* 24-way set assoc, 64 byte line size */
	अणु 0xec, LVL_3,      MB(24) पूर्ण,	/* 24-way set assoc, 64 byte line size */
	अणु 0x00, 0, 0पूर्ण
पूर्ण;


क्रमागत _cache_type अणु
	CTYPE_शून्य = 0,
	CTYPE_DATA = 1,
	CTYPE_INST = 2,
	CTYPE_UNIFIED = 3
पूर्ण;

जोड़ _cpuid4_leaf_eax अणु
	काष्ठा अणु
		क्रमागत _cache_type	type:5;
		अचिन्हित पूर्णांक		level:3;
		अचिन्हित पूर्णांक		is_self_initializing:1;
		अचिन्हित पूर्णांक		is_fully_associative:1;
		अचिन्हित पूर्णांक		reserved:4;
		अचिन्हित पूर्णांक		num_thपढ़ोs_sharing:12;
		अचिन्हित पूर्णांक		num_cores_on_die:6;
	पूर्ण split;
	u32 full;
पूर्ण;

जोड़ _cpuid4_leaf_ebx अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक		coherency_line_size:12;
		अचिन्हित पूर्णांक		physical_line_partition:10;
		अचिन्हित पूर्णांक		ways_of_associativity:10;
	पूर्ण split;
	u32 full;
पूर्ण;

जोड़ _cpuid4_leaf_ecx अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक		number_of_sets:32;
	पूर्ण split;
	u32 full;
पूर्ण;

काष्ठा _cpuid4_info_regs अणु
	जोड़ _cpuid4_leaf_eax eax;
	जोड़ _cpuid4_leaf_ebx ebx;
	जोड़ _cpuid4_leaf_ecx ecx;
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ size;
	काष्ठा amd_northbridge *nb;
पूर्ण;

अटल अचिन्हित लघु num_cache_leaves;

/* AMD करोesn't have CPUID4. Emulate it here to report the same
   inक्रमmation to the user.  This makes some assumptions about the machine:
   L2 not shared, no SMT etc. that is currently true on AMD CPUs.

   In theory the TLBs could be reported as fake type (they are in "dummy").
   Maybe later */
जोड़ l1_cache अणु
	काष्ठा अणु
		अचिन्हित line_size:8;
		अचिन्हित lines_per_tag:8;
		अचिन्हित assoc:8;
		अचिन्हित size_in_kb:8;
	पूर्ण;
	अचिन्हित val;
पूर्ण;

जोड़ l2_cache अणु
	काष्ठा अणु
		अचिन्हित line_size:8;
		अचिन्हित lines_per_tag:4;
		अचिन्हित assoc:4;
		अचिन्हित size_in_kb:16;
	पूर्ण;
	अचिन्हित val;
पूर्ण;

जोड़ l3_cache अणु
	काष्ठा अणु
		अचिन्हित line_size:8;
		अचिन्हित lines_per_tag:4;
		अचिन्हित assoc:4;
		अचिन्हित res:2;
		अचिन्हित size_encoded:14;
	पूर्ण;
	अचिन्हित val;
पूर्ण;

अटल स्थिर अचिन्हित लघु assocs[] = अणु
	[1] = 1,
	[2] = 2,
	[4] = 4,
	[6] = 8,
	[8] = 16,
	[0xa] = 32,
	[0xb] = 48,
	[0xc] = 64,
	[0xd] = 96,
	[0xe] = 128,
	[0xf] = 0xffff /* fully associative - no way to show this currently */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर levels[] = अणु 1, 1, 2, 3 पूर्ण;
अटल स्थिर अचिन्हित अक्षर types[] = अणु 1, 2, 3, 3 पूर्ण;

अटल स्थिर क्रमागत cache_type cache_type_map[] = अणु
	[CTYPE_शून्य] = CACHE_TYPE_NOCACHE,
	[CTYPE_DATA] = CACHE_TYPE_DATA,
	[CTYPE_INST] = CACHE_TYPE_INST,
	[CTYPE_UNIFIED] = CACHE_TYPE_UNIFIED,
पूर्ण;

अटल व्योम
amd_cpuid4(पूर्णांक leaf, जोड़ _cpuid4_leaf_eax *eax,
		     जोड़ _cpuid4_leaf_ebx *ebx,
		     जोड़ _cpuid4_leaf_ecx *ecx)
अणु
	अचिन्हित dummy;
	अचिन्हित line_size, lines_per_tag, assoc, size_in_kb;
	जोड़ l1_cache l1i, l1d;
	जोड़ l2_cache l2;
	जोड़ l3_cache l3;
	जोड़ l1_cache *l1 = &l1d;

	eax->full = 0;
	ebx->full = 0;
	ecx->full = 0;

	cpuid(0x80000005, &dummy, &dummy, &l1d.val, &l1i.val);
	cpuid(0x80000006, &dummy, &dummy, &l2.val, &l3.val);

	चयन (leaf) अणु
	हाल 1:
		l1 = &l1i;
		fallthrough;
	हाल 0:
		अगर (!l1->val)
			वापस;
		assoc = assocs[l1->assoc];
		line_size = l1->line_size;
		lines_per_tag = l1->lines_per_tag;
		size_in_kb = l1->size_in_kb;
		अवरोध;
	हाल 2:
		अगर (!l2.val)
			वापस;
		assoc = assocs[l2.assoc];
		line_size = l2.line_size;
		lines_per_tag = l2.lines_per_tag;
		/* cpu_data has errata corrections क्रम K7 applied */
		size_in_kb = __this_cpu_पढ़ो(cpu_info.x86_cache_size);
		अवरोध;
	हाल 3:
		अगर (!l3.val)
			वापस;
		assoc = assocs[l3.assoc];
		line_size = l3.line_size;
		lines_per_tag = l3.lines_per_tag;
		size_in_kb = l3.size_encoded * 512;
		अगर (boot_cpu_has(X86_FEATURE_AMD_DCM)) अणु
			size_in_kb = size_in_kb >> 1;
			assoc = assoc >> 1;
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	eax->split.is_self_initializing = 1;
	eax->split.type = types[leaf];
	eax->split.level = levels[leaf];
	eax->split.num_thपढ़ोs_sharing = 0;
	eax->split.num_cores_on_die = __this_cpu_पढ़ो(cpu_info.x86_max_cores) - 1;


	अगर (assoc == 0xffff)
		eax->split.is_fully_associative = 1;
	ebx->split.coherency_line_size = line_size - 1;
	ebx->split.ways_of_associativity = assoc - 1;
	ebx->split.physical_line_partition = lines_per_tag - 1;
	ecx->split.number_of_sets = (size_in_kb * 1024) / line_size /
		(ebx->split.ways_of_associativity + 1) - 1;
पूर्ण

#अगर defined(CONFIG_AMD_NB) && defined(CONFIG_SYSFS)

/*
 * L3 cache descriptors
 */
अटल व्योम amd_calc_l3_indices(काष्ठा amd_northbridge *nb)
अणु
	काष्ठा amd_l3_cache *l3 = &nb->l3_cache;
	अचिन्हित पूर्णांक sc0, sc1, sc2, sc3;
	u32 val = 0;

	pci_पढ़ो_config_dword(nb->misc, 0x1C4, &val);

	/* calculate subcache sizes */
	l3->subcaches[0] = sc0 = !(val & BIT(0));
	l3->subcaches[1] = sc1 = !(val & BIT(4));

	अगर (boot_cpu_data.x86 == 0x15) अणु
		l3->subcaches[0] = sc0 += !(val & BIT(1));
		l3->subcaches[1] = sc1 += !(val & BIT(5));
	पूर्ण

	l3->subcaches[2] = sc2 = !(val & BIT(8))  + !(val & BIT(9));
	l3->subcaches[3] = sc3 = !(val & BIT(12)) + !(val & BIT(13));

	l3->indices = (max(max3(sc0, sc1, sc2), sc3) << 10) - 1;
पूर्ण

/*
 * check whether a slot used क्रम disabling an L3 index is occupied.
 * @l3: L3 cache descriptor
 * @slot: slot number (0..1)
 *
 * @वापसs: the disabled index अगर used or negative value अगर slot मुक्त.
 */
अटल पूर्णांक amd_get_l3_disable_slot(काष्ठा amd_northbridge *nb, अचिन्हित slot)
अणु
	अचिन्हित पूर्णांक reg = 0;

	pci_पढ़ो_config_dword(nb->misc, 0x1BC + slot * 4, &reg);

	/* check whether this slot is activated alपढ़ोy */
	अगर (reg & (3UL << 30))
		वापस reg & 0xfff;

	वापस -1;
पूर्ण

अटल sमाप_प्रकार show_cache_disable(काष्ठा cacheinfo *this_leaf, अक्षर *buf,
				  अचिन्हित पूर्णांक slot)
अणु
	पूर्णांक index;
	काष्ठा amd_northbridge *nb = this_leaf->priv;

	index = amd_get_l3_disable_slot(nb, slot);
	अगर (index >= 0)
		वापस प्र_लिखो(buf, "%d\n", index);

	वापस प्र_लिखो(buf, "FREE\n");
पूर्ण

#घोषणा SHOW_CACHE_DISABLE(slot)					\
अटल sमाप_प्रकार								\
cache_disable_##slot##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);		\
	वापस show_cache_disable(this_leaf, buf, slot);		\
पूर्ण
SHOW_CACHE_DISABLE(0)
SHOW_CACHE_DISABLE(1)

अटल व्योम amd_l3_disable_index(काष्ठा amd_northbridge *nb, पूर्णांक cpu,
				 अचिन्हित slot, अचिन्हित दीर्घ idx)
अणु
	पूर्णांक i;

	idx |= BIT(30);

	/*
	 *  disable index in all 4 subcaches
	 */
	क्रम (i = 0; i < 4; i++) अणु
		u32 reg = idx | (i << 20);

		अगर (!nb->l3_cache.subcaches[i])
			जारी;

		pci_ग_लिखो_config_dword(nb->misc, 0x1BC + slot * 4, reg);

		/*
		 * We need to WBINVD on a core on the node containing the L3
		 * cache which indices we disable thereक्रमe a simple wbinvd()
		 * is not sufficient.
		 */
		wbinvd_on_cpu(cpu);

		reg |= BIT(31);
		pci_ग_लिखो_config_dword(nb->misc, 0x1BC + slot * 4, reg);
	पूर्ण
पूर्ण

/*
 * disable a L3 cache index by using a disable-slot
 *
 * @l3:    L3 cache descriptor
 * @cpu:   A CPU on the node containing the L3 cache
 * @slot:  slot number (0..1)
 * @index: index to disable
 *
 * @वापस: 0 on success, error status on failure
 */
अटल पूर्णांक amd_set_l3_disable_slot(काष्ठा amd_northbridge *nb, पूर्णांक cpu,
			    अचिन्हित slot, अचिन्हित दीर्घ index)
अणु
	पूर्णांक ret = 0;

	/*  check अगर @slot is alपढ़ोy used or the index is alपढ़ोy disabled */
	ret = amd_get_l3_disable_slot(nb, slot);
	अगर (ret >= 0)
		वापस -EEXIST;

	अगर (index > nb->l3_cache.indices)
		वापस -EINVAL;

	/* check whether the other slot has disabled the same index alपढ़ोy */
	अगर (index == amd_get_l3_disable_slot(nb, !slot))
		वापस -EEXIST;

	amd_l3_disable_index(nb, cpu, slot, index);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_cache_disable(काष्ठा cacheinfo *this_leaf,
				   स्थिर अक्षर *buf, माप_प्रकार count,
				   अचिन्हित पूर्णांक slot)
अणु
	अचिन्हित दीर्घ val = 0;
	पूर्णांक cpu, err = 0;
	काष्ठा amd_northbridge *nb = this_leaf->priv;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	cpu = cpumask_first(&this_leaf->shared_cpu_map);

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	err = amd_set_l3_disable_slot(nb, cpu, slot, val);
	अगर (err) अणु
		अगर (err == -EEXIST)
			pr_warn("L3 slot %d in use/index already disabled!\n",
				   slot);
		वापस err;
	पूर्ण
	वापस count;
पूर्ण

#घोषणा STORE_CACHE_DISABLE(slot)					\
अटल sमाप_प्रकार								\
cache_disable_##slot##_store(काष्ठा device *dev,			\
			     काष्ठा device_attribute *attr,		\
			     स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);		\
	वापस store_cache_disable(this_leaf, buf, count, slot);	\
पूर्ण
STORE_CACHE_DISABLE(0)
STORE_CACHE_DISABLE(1)

अटल sमाप_प्रकार subcaches_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	पूर्णांक cpu = cpumask_first(&this_leaf->shared_cpu_map);

	वापस प्र_लिखो(buf, "%x\n", amd_get_subcaches(cpu));
पूर्ण

अटल sमाप_प्रकार subcaches_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	पूर्णांक cpu = cpumask_first(&this_leaf->shared_cpu_map);
	अचिन्हित दीर्घ val;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (kम_से_अदीर्घ(buf, 16, &val) < 0)
		वापस -EINVAL;

	अगर (amd_set_subcaches(cpu, val))
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(cache_disable_0);
अटल DEVICE_ATTR_RW(cache_disable_1);
अटल DEVICE_ATTR_RW(subcaches);

अटल umode_t
cache_निजी_attrs_is_visible(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr, पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा cacheinfo *this_leaf = dev_get_drvdata(dev);
	umode_t mode = attr->mode;

	अगर (!this_leaf->priv)
		वापस 0;

	अगर ((attr == &dev_attr_subcaches.attr) &&
	    amd_nb_has_feature(AMD_NB_L3_PARTITIONING))
		वापस mode;

	अगर ((attr == &dev_attr_cache_disable_0.attr ||
	     attr == &dev_attr_cache_disable_1.attr) &&
	    amd_nb_has_feature(AMD_NB_L3_INDEX_DISABLE))
		वापस mode;

	वापस 0;
पूर्ण

अटल काष्ठा attribute_group cache_निजी_group = अणु
	.is_visible = cache_निजी_attrs_is_visible,
पूर्ण;

अटल व्योम init_amd_l3_attrs(व्योम)
अणु
	पूर्णांक n = 1;
	अटल काष्ठा attribute **amd_l3_attrs;

	अगर (amd_l3_attrs) /* alपढ़ोy initialized */
		वापस;

	अगर (amd_nb_has_feature(AMD_NB_L3_INDEX_DISABLE))
		n += 2;
	अगर (amd_nb_has_feature(AMD_NB_L3_PARTITIONING))
		n += 1;

	amd_l3_attrs = kसुस्मृति(n, माप(*amd_l3_attrs), GFP_KERNEL);
	अगर (!amd_l3_attrs)
		वापस;

	n = 0;
	अगर (amd_nb_has_feature(AMD_NB_L3_INDEX_DISABLE)) अणु
		amd_l3_attrs[n++] = &dev_attr_cache_disable_0.attr;
		amd_l3_attrs[n++] = &dev_attr_cache_disable_1.attr;
	पूर्ण
	अगर (amd_nb_has_feature(AMD_NB_L3_PARTITIONING))
		amd_l3_attrs[n++] = &dev_attr_subcaches.attr;

	cache_निजी_group.attrs = amd_l3_attrs;
पूर्ण

स्थिर काष्ठा attribute_group *
cache_get_priv_group(काष्ठा cacheinfo *this_leaf)
अणु
	काष्ठा amd_northbridge *nb = this_leaf->priv;

	अगर (this_leaf->level < 3 || !nb)
		वापस शून्य;

	अगर (nb && nb->l3_cache.indices)
		init_amd_l3_attrs();

	वापस &cache_निजी_group;
पूर्ण

अटल व्योम amd_init_l3_cache(काष्ठा _cpuid4_info_regs *this_leaf, पूर्णांक index)
अणु
	पूर्णांक node;

	/* only क्रम L3, and not in भवized environments */
	अगर (index < 3)
		वापस;

	node = topology_die_id(smp_processor_id());
	this_leaf->nb = node_to_amd_nb(node);
	अगर (this_leaf->nb && !this_leaf->nb->l3_cache.indices)
		amd_calc_l3_indices(this_leaf->nb);
पूर्ण
#अन्यथा
#घोषणा amd_init_l3_cache(x, y)
#पूर्ण_अगर  /* CONFIG_AMD_NB && CONFIG_SYSFS */

अटल पूर्णांक
cpuid4_cache_lookup_regs(पूर्णांक index, काष्ठा _cpuid4_info_regs *this_leaf)
अणु
	जोड़ _cpuid4_leaf_eax	eax;
	जोड़ _cpuid4_leaf_ebx	ebx;
	जोड़ _cpuid4_leaf_ecx	ecx;
	अचिन्हित		edx;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD) अणु
		अगर (boot_cpu_has(X86_FEATURE_TOPOEXT))
			cpuid_count(0x8000001d, index, &eax.full,
				    &ebx.full, &ecx.full, &edx);
		अन्यथा
			amd_cpuid4(index, &eax, &ebx, &ecx);
		amd_init_l3_cache(this_leaf, index);
	पूर्ण अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON) अणु
		cpuid_count(0x8000001d, index, &eax.full,
			    &ebx.full, &ecx.full, &edx);
		amd_init_l3_cache(this_leaf, index);
	पूर्ण अन्यथा अणु
		cpuid_count(4, index, &eax.full, &ebx.full, &ecx.full, &edx);
	पूर्ण

	अगर (eax.split.type == CTYPE_शून्य)
		वापस -EIO; /* better error ? */

	this_leaf->eax = eax;
	this_leaf->ebx = ebx;
	this_leaf->ecx = ecx;
	this_leaf->size = (ecx.split.number_of_sets          + 1) *
			  (ebx.split.coherency_line_size     + 1) *
			  (ebx.split.physical_line_partition + 1) *
			  (ebx.split.ways_of_associativity   + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक find_num_cache_leaves(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक		eax, ebx, ecx, edx, op;
	जोड़ _cpuid4_leaf_eax	cache_eax;
	पूर्णांक 			i = -1;

	अगर (c->x86_venकरोr == X86_VENDOR_AMD ||
	    c->x86_venकरोr == X86_VENDOR_HYGON)
		op = 0x8000001d;
	अन्यथा
		op = 4;

	करो अणु
		++i;
		/* Do cpuid(op) loop to find out num_cache_leaves */
		cpuid_count(op, i, &eax, &ebx, &ecx, &edx);
		cache_eax.full = eax;
	पूर्ण जबतक (cache_eax.split.type != CTYPE_शून्य);
	वापस i;
पूर्ण

व्योम cacheinfo_amd_init_llc_id(काष्ठा cpuinfo_x86 *c, पूर्णांक cpu)
अणु
	/*
	 * We may have multiple LLCs अगर L3 caches exist, so check अगर we
	 * have an L3 cache by looking at the L3 cache CPUID leaf.
	 */
	अगर (!cpuid_edx(0x80000006))
		वापस;

	अगर (c->x86 < 0x17) अणु
		/* LLC is at the node level. */
		per_cpu(cpu_llc_id, cpu) = c->cpu_die_id;
	पूर्ण अन्यथा अगर (c->x86 == 0x17 && c->x86_model <= 0x1F) अणु
		/*
		 * LLC is at the core complex level.
		 * Core complex ID is ApicId[3] क्रम these processors.
		 */
		per_cpu(cpu_llc_id, cpu) = c->apicid >> 3;
	पूर्ण अन्यथा अणु
		/*
		 * LLC ID is calculated from the number of thपढ़ोs sharing the
		 * cache.
		 * */
		u32 eax, ebx, ecx, edx, num_sharing_cache = 0;
		u32 llc_index = find_num_cache_leaves(c) - 1;

		cpuid_count(0x8000001d, llc_index, &eax, &ebx, &ecx, &edx);
		अगर (eax)
			num_sharing_cache = ((eax >> 14) & 0xfff) + 1;

		अगर (num_sharing_cache) अणु
			पूर्णांक bits = get_count_order(num_sharing_cache);

			per_cpu(cpu_llc_id, cpu) = c->apicid >> bits;
		पूर्ण
	पूर्ण
पूर्ण

व्योम cacheinfo_hygon_init_llc_id(काष्ठा cpuinfo_x86 *c, पूर्णांक cpu)
अणु
	/*
	 * We may have multiple LLCs अगर L3 caches exist, so check अगर we
	 * have an L3 cache by looking at the L3 cache CPUID leaf.
	 */
	अगर (!cpuid_edx(0x80000006))
		वापस;

	/*
	 * LLC is at the core complex level.
	 * Core complex ID is ApicId[3] क्रम these processors.
	 */
	per_cpu(cpu_llc_id, cpu) = c->apicid >> 3;
पूर्ण

व्योम init_amd_cacheinfo(काष्ठा cpuinfo_x86 *c)
अणु

	अगर (boot_cpu_has(X86_FEATURE_TOPOEXT)) अणु
		num_cache_leaves = find_num_cache_leaves(c);
	पूर्ण अन्यथा अगर (c->extended_cpuid_level >= 0x80000006) अणु
		अगर (cpuid_edx(0x80000006) & 0xf000)
			num_cache_leaves = 4;
		अन्यथा
			num_cache_leaves = 3;
	पूर्ण
पूर्ण

व्योम init_hygon_cacheinfo(काष्ठा cpuinfo_x86 *c)
अणु
	num_cache_leaves = find_num_cache_leaves(c);
पूर्ण

व्योम init_पूर्णांकel_cacheinfo(काष्ठा cpuinfo_x86 *c)
अणु
	/* Cache sizes */
	अचिन्हित पूर्णांक trace = 0, l1i = 0, l1d = 0, l2 = 0, l3 = 0;
	अचिन्हित पूर्णांक new_l1d = 0, new_l1i = 0; /* Cache sizes from cpuid(4) */
	अचिन्हित पूर्णांक new_l2 = 0, new_l3 = 0, i; /* Cache sizes from cpuid(4) */
	अचिन्हित पूर्णांक l2_id = 0, l3_id = 0, num_thपढ़ोs_sharing, index_msb;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक cpu = c->cpu_index;
#पूर्ण_अगर

	अगर (c->cpuid_level > 3) अणु
		अटल पूर्णांक is_initialized;

		अगर (is_initialized == 0) अणु
			/* Init num_cache_leaves from boot CPU */
			num_cache_leaves = find_num_cache_leaves(c);
			is_initialized++;
		पूर्ण

		/*
		 * Whenever possible use cpuid(4), deterministic cache
		 * parameters cpuid leaf to find the cache details
		 */
		क्रम (i = 0; i < num_cache_leaves; i++) अणु
			काष्ठा _cpuid4_info_regs this_leaf = अणुपूर्ण;
			पूर्णांक retval;

			retval = cpuid4_cache_lookup_regs(i, &this_leaf);
			अगर (retval < 0)
				जारी;

			चयन (this_leaf.eax.split.level) अणु
			हाल 1:
				अगर (this_leaf.eax.split.type == CTYPE_DATA)
					new_l1d = this_leaf.size/1024;
				अन्यथा अगर (this_leaf.eax.split.type == CTYPE_INST)
					new_l1i = this_leaf.size/1024;
				अवरोध;
			हाल 2:
				new_l2 = this_leaf.size/1024;
				num_thपढ़ोs_sharing = 1 + this_leaf.eax.split.num_thपढ़ोs_sharing;
				index_msb = get_count_order(num_thपढ़ोs_sharing);
				l2_id = c->apicid & ~((1 << index_msb) - 1);
				अवरोध;
			हाल 3:
				new_l3 = this_leaf.size/1024;
				num_thपढ़ोs_sharing = 1 + this_leaf.eax.split.num_thपढ़ोs_sharing;
				index_msb = get_count_order(num_thपढ़ोs_sharing);
				l3_id = c->apicid & ~((1 << index_msb) - 1);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Don't use cpuid2 अगर cpuid4 is supported. For P4, we use cpuid2 क्रम
	 * trace cache
	 */
	अगर ((num_cache_leaves == 0 || c->x86 == 15) && c->cpuid_level > 1) अणु
		/* supports eax=2  call */
		पूर्णांक j, n;
		अचिन्हित पूर्णांक regs[4];
		अचिन्हित अक्षर *dp = (अचिन्हित अक्षर *)regs;
		पूर्णांक only_trace = 0;

		अगर (num_cache_leaves != 0 && c->x86 == 15)
			only_trace = 1;

		/* Number of बार to iterate */
		n = cpuid_eax(2) & 0xFF;

		क्रम (i = 0 ; i < n ; i++) अणु
			cpuid(2, &regs[0], &regs[1], &regs[2], &regs[3]);

			/* If bit 31 is set, this is an unknown क्रमmat */
			क्रम (j = 0 ; j < 3 ; j++)
				अगर (regs[j] & (1 << 31))
					regs[j] = 0;

			/* Byte 0 is level count, not a descriptor */
			क्रम (j = 1 ; j < 16 ; j++) अणु
				अचिन्हित अक्षर des = dp[j];
				अचिन्हित अक्षर k = 0;

				/* look up this descriptor in the table */
				जबतक (cache_table[k].descriptor != 0) अणु
					अगर (cache_table[k].descriptor == des) अणु
						अगर (only_trace && cache_table[k].cache_type != LVL_TRACE)
							अवरोध;
						चयन (cache_table[k].cache_type) अणु
						हाल LVL_1_INST:
							l1i += cache_table[k].size;
							अवरोध;
						हाल LVL_1_DATA:
							l1d += cache_table[k].size;
							अवरोध;
						हाल LVL_2:
							l2 += cache_table[k].size;
							अवरोध;
						हाल LVL_3:
							l3 += cache_table[k].size;
							अवरोध;
						हाल LVL_TRACE:
							trace += cache_table[k].size;
							अवरोध;
						पूर्ण

						अवरोध;
					पूर्ण

					k++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (new_l1d)
		l1d = new_l1d;

	अगर (new_l1i)
		l1i = new_l1i;

	अगर (new_l2) अणु
		l2 = new_l2;
#अगर_घोषित CONFIG_SMP
		per_cpu(cpu_llc_id, cpu) = l2_id;
#पूर्ण_अगर
	पूर्ण

	अगर (new_l3) अणु
		l3 = new_l3;
#अगर_घोषित CONFIG_SMP
		per_cpu(cpu_llc_id, cpu) = l3_id;
#पूर्ण_अगर
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/*
	 * If cpu_llc_id is not yet set, this means cpuid_level < 4 which in
	 * turns means that the only possibility is SMT (as indicated in
	 * cpuid1). Since cpuid2 करोesn't specअगरy shared caches, and we know
	 * that SMT shares all caches, we can unconditionally set cpu_llc_id to
	 * c->phys_proc_id.
	 */
	अगर (per_cpu(cpu_llc_id, cpu) == BAD_APICID)
		per_cpu(cpu_llc_id, cpu) = c->phys_proc_id;
#पूर्ण_अगर

	c->x86_cache_size = l3 ? l3 : (l2 ? l2 : (l1i+l1d));

	अगर (!l2)
		cpu_detect_cache_sizes(c);
पूर्ण

अटल पूर्णांक __cache_amd_cpumap_setup(अचिन्हित पूर्णांक cpu, पूर्णांक index,
				    काष्ठा _cpuid4_info_regs *base)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci;
	काष्ठा cacheinfo *this_leaf;
	पूर्णांक i, sibling;

	/*
	 * For L3, always use the pre-calculated cpu_llc_shared_mask
	 * to derive shared_cpu_map.
	 */
	अगर (index == 3) अणु
		क्रम_each_cpu(i, cpu_llc_shared_mask(cpu)) अणु
			this_cpu_ci = get_cpu_cacheinfo(i);
			अगर (!this_cpu_ci->info_list)
				जारी;
			this_leaf = this_cpu_ci->info_list + index;
			क्रम_each_cpu(sibling, cpu_llc_shared_mask(cpu)) अणु
				अगर (!cpu_online(sibling))
					जारी;
				cpumask_set_cpu(sibling,
						&this_leaf->shared_cpu_map);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (boot_cpu_has(X86_FEATURE_TOPOEXT)) अणु
		अचिन्हित पूर्णांक apicid, nshared, first, last;

		nshared = base->eax.split.num_thपढ़ोs_sharing + 1;
		apicid = cpu_data(cpu).apicid;
		first = apicid - (apicid % nshared);
		last = first + nshared - 1;

		क्रम_each_online_cpu(i) अणु
			this_cpu_ci = get_cpu_cacheinfo(i);
			अगर (!this_cpu_ci->info_list)
				जारी;

			apicid = cpu_data(i).apicid;
			अगर ((apicid < first) || (apicid > last))
				जारी;

			this_leaf = this_cpu_ci->info_list + index;

			क्रम_each_online_cpu(sibling) अणु
				apicid = cpu_data(sibling).apicid;
				अगर ((apicid < first) || (apicid > last))
					जारी;
				cpumask_set_cpu(sibling,
						&this_leaf->shared_cpu_map);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम __cache_cpumap_setup(अचिन्हित पूर्णांक cpu, पूर्णांक index,
				 काष्ठा _cpuid4_info_regs *base)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf, *sibling_leaf;
	अचिन्हित दीर्घ num_thपढ़ोs_sharing;
	पूर्णांक index_msb, i;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	अगर (c->x86_venकरोr == X86_VENDOR_AMD ||
	    c->x86_venकरोr == X86_VENDOR_HYGON) अणु
		अगर (__cache_amd_cpumap_setup(cpu, index, base))
			वापस;
	पूर्ण

	this_leaf = this_cpu_ci->info_list + index;
	num_thपढ़ोs_sharing = 1 + base->eax.split.num_thपढ़ोs_sharing;

	cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
	अगर (num_thपढ़ोs_sharing == 1)
		वापस;

	index_msb = get_count_order(num_thपढ़ोs_sharing);

	क्रम_each_online_cpu(i)
		अगर (cpu_data(i).apicid >> index_msb == c->apicid >> index_msb) अणु
			काष्ठा cpu_cacheinfo *sib_cpu_ci = get_cpu_cacheinfo(i);

			अगर (i == cpu || !sib_cpu_ci->info_list)
				जारी;/* skip अगर itself or no cacheinfo */
			sibling_leaf = sib_cpu_ci->info_list + index;
			cpumask_set_cpu(i, &this_leaf->shared_cpu_map);
			cpumask_set_cpu(cpu, &sibling_leaf->shared_cpu_map);
		पूर्ण
पूर्ण

अटल व्योम ci_leaf_init(काष्ठा cacheinfo *this_leaf,
			 काष्ठा _cpuid4_info_regs *base)
अणु
	this_leaf->id = base->id;
	this_leaf->attributes = CACHE_ID;
	this_leaf->level = base->eax.split.level;
	this_leaf->type = cache_type_map[base->eax.split.type];
	this_leaf->coherency_line_size =
				base->ebx.split.coherency_line_size + 1;
	this_leaf->ways_of_associativity =
				base->ebx.split.ways_of_associativity + 1;
	this_leaf->size = base->size;
	this_leaf->number_of_sets = base->ecx.split.number_of_sets + 1;
	this_leaf->physical_line_partition =
				base->ebx.split.physical_line_partition + 1;
	this_leaf->priv = base->nb;
पूर्ण

अटल पूर्णांक __init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	अगर (!num_cache_leaves)
		वापस -ENOENT;
	अगर (!this_cpu_ci)
		वापस -EINVAL;
	this_cpu_ci->num_levels = 3;
	this_cpu_ci->num_leaves = num_cache_leaves;
	वापस 0;
पूर्ण

/*
 * The max shared thपढ़ोs number comes from CPUID.4:EAX[25-14] with input
 * ECX as cache index. Then right shअगरt apicid by the number's order to get
 * cache id क्रम this cache node.
 */
अटल व्योम get_cache_id(पूर्णांक cpu, काष्ठा _cpuid4_info_regs *id4_regs)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	अचिन्हित दीर्घ num_thपढ़ोs_sharing;
	पूर्णांक index_msb;

	num_thपढ़ोs_sharing = 1 + id4_regs->eax.split.num_thपढ़ोs_sharing;
	index_msb = get_count_order(num_thपढ़ोs_sharing);
	id4_regs->id = c->apicid >> index_msb;
पूर्ण

अटल पूर्णांक __populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक idx, ret;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf = this_cpu_ci->info_list;
	काष्ठा _cpuid4_info_regs id4_regs = अणुपूर्ण;

	क्रम (idx = 0; idx < this_cpu_ci->num_leaves; idx++) अणु
		ret = cpuid4_cache_lookup_regs(idx, &id4_regs);
		अगर (ret)
			वापस ret;
		get_cache_id(cpu, &id4_regs);
		ci_leaf_init(this_leaf++, &id4_regs);
		__cache_cpumap_setup(cpu, idx, &id4_regs);
	पूर्ण
	this_cpu_ci->cpu_map_populated = true;

	वापस 0;
पूर्ण

DEFINE_SMP_CALL_CACHE_FUNCTION(init_cache_level)
DEFINE_SMP_CALL_CACHE_FUNCTION(populate_cache_leaves)
