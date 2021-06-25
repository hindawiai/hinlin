<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Procedures क्रम creating, accessing and पूर्णांकerpreting the device tree.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 * 
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com 
 */

#अघोषित DEBUG

#समावेश <मानकतर्क.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/initrd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/kexec.h>
#समावेश <linux/irq.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/kdump.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/घातernv.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/epapr_hcalls.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/dt_cpu_ftrs.h>
#समावेश <यंत्र/drस्मृति.स>
#समावेश <यंत्र/ultravisor.h>

#समावेश <mm/mmu_decl.h>

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) prपूर्णांकk(KERN_ERR fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

पूर्णांक *chip_id_lookup_table;

#अगर_घोषित CONFIG_PPC64
पूर्णांक __initdata iommu_is_off;
पूर्णांक __initdata iommu_क्रमce_on;
अचिन्हित दीर्घ tce_alloc_start, tce_alloc_end;
u64 ppc64_rma_size;
#पूर्ण_अगर
अटल phys_addr_t first_memblock_size;
अटल पूर्णांक __initdata boot_cpu_count;

अटल पूर्णांक __init early_parse_mem(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;

	memory_limit = PAGE_ALIGN(memparse(p, &p));
	DBG("memory limit = 0x%llx\n", memory_limit);

	वापस 0;
पूर्ण
early_param("mem", early_parse_mem);

/*
 * overlaps_initrd - check क्रम overlap with page aligned extension of
 * initrd.
 */
अटल अंतरभूत पूर्णांक overlaps_initrd(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (!initrd_start)
		वापस 0;

	वापस	(start + size) > ALIGN_DOWN(initrd_start, PAGE_SIZE) &&
			start <= ALIGN(initrd_end, PAGE_SIZE);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * move_device_tree - move tree to an unused area, अगर needed.
 *
 * The device tree may be allocated beyond our memory limit, or inside the
 * crash kernel region क्रम kdump, or within the page aligned range of initrd.
 * If so, move it out of the way.
 */
अटल व्योम __init move_device_tree(व्योम)
अणु
	अचिन्हित दीर्घ start, size;
	व्योम *p;

	DBG("-> move_device_tree\n");

	start = __pa(initial_boot_params);
	size = fdt_totalsize(initial_boot_params);

	अगर ((memory_limit && (start + size) > PHYSICAL_START + memory_limit) ||
	    !memblock_is_memory(start + size - 1) ||
	    overlaps_crashkernel(start, size) || overlaps_initrd(start, size)) अणु
		p = memblock_alloc_raw(size, PAGE_SIZE);
		अगर (!p)
			panic("Failed to allocate %lu bytes to move device tree\n",
			      size);
		स_नकल(p, initial_boot_params, size);
		initial_boot_params = p;
		DBG("Moved device tree to 0x%px\n", p);
	पूर्ण

	DBG("<- move_device_tree\n");
पूर्ण

/*
 * ibm,pa-features is a per-cpu property that contains a string of
 * attribute descriptors, each of which has a 2 byte header plus up
 * to 254 bytes worth of processor attribute bits.  First header
 * byte specअगरies the number of bytes following the header.
 * Second header byte is an "attribute-specifier" type, of which
 * zero is the only currently-defined value.
 * Implementation:  Pass in the byte and bit offset क्रम the feature
 * that we are पूर्णांकerested in.  The function will वापस -1 अगर the
 * pa-features property is missing, or a 1/0 to indicate अगर the feature
 * is supported/not supported.  Note that the bit numbers are
 * big-endian to match the definition in PAPR.
 */
अटल काष्ठा ibm_pa_feature अणु
	अचिन्हित दीर्घ	cpu_features;	/* CPU_FTR_xxx bit */
	अचिन्हित दीर्घ	mmu_features;	/* MMU_FTR_xxx bit */
	अचिन्हित पूर्णांक	cpu_user_ftrs;	/* PPC_FEATURE_xxx bit */
	अचिन्हित पूर्णांक	cpu_user_ftrs2;	/* PPC_FEATURE2_xxx bit */
	अचिन्हित अक्षर	pabyte;		/* byte number in ibm,pa-features */
	अचिन्हित अक्षर	pabit;		/* bit number (big-endian) */
	अचिन्हित अक्षर	invert;		/* अगर 1, pa bit set => clear feature */
पूर्ण ibm_pa_features[] __initdata = अणु
	अणु .pabyte = 0,  .pabit = 0, .cpu_user_ftrs = PPC_FEATURE_HAS_MMU पूर्ण,
	अणु .pabyte = 0,  .pabit = 1, .cpu_user_ftrs = PPC_FEATURE_HAS_FPU पूर्ण,
	अणु .pabyte = 0,  .pabit = 3, .cpu_features  = CPU_FTR_CTRL पूर्ण,
	अणु .pabyte = 0,  .pabit = 6, .cpu_features  = CPU_FTR_NOEXECUTE पूर्ण,
	अणु .pabyte = 1,  .pabit = 2, .mmu_features  = MMU_FTR_CI_LARGE_PAGE पूर्ण,
#अगर_घोषित CONFIG_PPC_RADIX_MMU
	अणु .pabyte = 40, .pabit = 0, .mmu_features  = MMU_FTR_TYPE_RADIX | MMU_FTR_GTSE पूर्ण,
#पूर्ण_अगर
	अणु .pabyte = 5,  .pabit = 0, .cpu_features  = CPU_FTR_REAL_LE,
				    .cpu_user_ftrs = PPC_FEATURE_TRUE_LE पूर्ण,
	/*
	 * If the kernel करोesn't support TM (ie CONFIG_PPC_TRANSACTIONAL_MEM=n),
	 * we करोn't want to turn on TM here, so we use the *_COMP versions
	 * which are 0 अगर the kernel करोesn't support TM.
	 */
	अणु .pabyte = 22, .pabit = 0, .cpu_features = CPU_FTR_TM_COMP,
	  .cpu_user_ftrs2 = PPC_FEATURE2_HTM_COMP | PPC_FEATURE2_HTM_NOSC_COMP पूर्ण,

	अणु .pabyte = 64, .pabit = 0, .cpu_features = CPU_FTR_DAWR1 पूर्ण,
पूर्ण;

अटल व्योम __init scan_features(अचिन्हित दीर्घ node, स्थिर अचिन्हित अक्षर *ftrs,
				 अचिन्हित दीर्घ tablelen,
				 काष्ठा ibm_pa_feature *fp,
				 अचिन्हित दीर्घ ft_size)
अणु
	अचिन्हित दीर्घ i, len, bit;

	/* find descriptor with type == 0 */
	क्रम (;;) अणु
		अगर (tablelen < 3)
			वापस;
		len = 2 + ftrs[0];
		अगर (tablelen < len)
			वापस;		/* descriptor 0 not found */
		अगर (ftrs[1] == 0)
			अवरोध;
		tablelen -= len;
		ftrs += len;
	पूर्ण

	/* loop over bits we know about */
	क्रम (i = 0; i < ft_size; ++i, ++fp) अणु
		अगर (fp->pabyte >= ftrs[0])
			जारी;
		bit = (ftrs[2 + fp->pabyte] >> (7 - fp->pabit)) & 1;
		अगर (bit ^ fp->invert) अणु
			cur_cpu_spec->cpu_features |= fp->cpu_features;
			cur_cpu_spec->cpu_user_features |= fp->cpu_user_ftrs;
			cur_cpu_spec->cpu_user_features2 |= fp->cpu_user_ftrs2;
			cur_cpu_spec->mmu_features |= fp->mmu_features;
		पूर्ण अन्यथा अणु
			cur_cpu_spec->cpu_features &= ~fp->cpu_features;
			cur_cpu_spec->cpu_user_features &= ~fp->cpu_user_ftrs;
			cur_cpu_spec->cpu_user_features2 &= ~fp->cpu_user_ftrs2;
			cur_cpu_spec->mmu_features &= ~fp->mmu_features;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init check_cpu_pa_features(अचिन्हित दीर्घ node)
अणु
	स्थिर अचिन्हित अक्षर *pa_ftrs;
	पूर्णांक tablelen;

	pa_ftrs = of_get_flat_dt_prop(node, "ibm,pa-features", &tablelen);
	अगर (pa_ftrs == शून्य)
		वापस;

	scan_features(node, pa_ftrs, tablelen,
		      ibm_pa_features, ARRAY_SIZE(ibm_pa_features));
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल व्योम __init init_mmu_slb_size(अचिन्हित दीर्घ node)
अणु
	स्थिर __be32 *slb_size_ptr;

	slb_size_ptr = of_get_flat_dt_prop(node, "slb-size", शून्य) ? :
			of_get_flat_dt_prop(node, "ibm,slb-size", शून्य);

	अगर (slb_size_ptr)
		mmu_slb_size = be32_to_cpup(slb_size_ptr);
पूर्ण
#अन्यथा
#घोषणा init_mmu_slb_size(node) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल काष्ठा feature_property अणु
	स्थिर अक्षर *name;
	u32 min_value;
	अचिन्हित दीर्घ cpu_feature;
	अचिन्हित दीर्घ cpu_user_ftr;
पूर्ण feature_properties[] __initdata = अणु
#अगर_घोषित CONFIG_ALTIVEC
	अणु"altivec", 0, CPU_FTR_ALTIVEC, PPC_FEATURE_HAS_ALTIVECपूर्ण,
	अणु"ibm,vmx", 1, CPU_FTR_ALTIVEC, PPC_FEATURE_HAS_ALTIVECपूर्ण,
#पूर्ण_अगर /* CONFIG_ALTIVEC */
#अगर_घोषित CONFIG_VSX
	/* Yes, this _really_ is ibm,vmx == 2 to enable VSX */
	अणु"ibm,vmx", 2, CPU_FTR_VSX, PPC_FEATURE_HAS_VSXपूर्ण,
#पूर्ण_अगर /* CONFIG_VSX */
#अगर_घोषित CONFIG_PPC64
	अणु"ibm,dfp", 1, 0, PPC_FEATURE_HAS_DFPपूर्ण,
	अणु"ibm,purr", 1, CPU_FTR_PURR, 0पूर्ण,
	अणु"ibm,spurr", 1, CPU_FTR_SPURR, 0पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC64 */
पूर्ण;

#अगर defined(CONFIG_44x) && defined(CONFIG_PPC_FPU)
अटल __init व्योम identical_pvr_fixup(अचिन्हित दीर्घ node)
अणु
	अचिन्हित पूर्णांक pvr;
	स्थिर अक्षर *model = of_get_flat_dt_prop(node, "model", शून्य);

	/*
	 * Since 440GR(x)/440EP(x) processors have the same pvr,
	 * we check the node path and set bit 28 in the cur_cpu_spec
	 * pvr क्रम EP(x) processor version. This bit is always 0 in
	 * the "real" pvr. Then we call identअगरy_cpu again with
	 * the new logical pvr to enable FPU support.
	 */
	अगर (model && म_माला(model, "440EP")) अणु
		pvr = cur_cpu_spec->pvr_value | 0x8;
		identअगरy_cpu(0, pvr);
		DBG("Using logical pvr %x for %s\n", pvr, model);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा identical_pvr_fixup(node) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल व्योम __init check_cpu_feature_properties(अचिन्हित दीर्घ node)
अणु
	पूर्णांक i;
	काष्ठा feature_property *fp = feature_properties;
	स्थिर __be32 *prop;

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(feature_properties); ++i, ++fp) अणु
		prop = of_get_flat_dt_prop(node, fp->name, शून्य);
		अगर (prop && be32_to_cpup(prop) >= fp->min_value) अणु
			cur_cpu_spec->cpu_features |= fp->cpu_feature;
			cur_cpu_spec->cpu_user_features |= fp->cpu_user_ftr;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init early_init_dt_scan_cpus(अचिन्हित दीर्घ node,
					  स्थिर अक्षर *uname, पूर्णांक depth,
					  व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *prop;
	स्थिर __be32 *पूर्णांकserv;
	पूर्णांक i, nthपढ़ोs;
	पूर्णांक len;
	पूर्णांक found = -1;
	पूर्णांक found_thपढ़ो = 0;

	/* We are scanning "cpu" nodes only */
	अगर (type == शून्य || म_भेद(type, "cpu") != 0)
		वापस 0;

	/* Get physical cpuid */
	पूर्णांकserv = of_get_flat_dt_prop(node, "ibm,ppc-interrupt-server#s", &len);
	अगर (!पूर्णांकserv)
		पूर्णांकserv = of_get_flat_dt_prop(node, "reg", &len);

	nthपढ़ोs = len / माप(पूर्णांक);

	/*
	 * Now see अगर any of these thपढ़ोs match our boot cpu.
	 * NOTE: This must match the parsing करोne in smp_setup_cpu_maps.
	 */
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		अगर (be32_to_cpu(पूर्णांकserv[i]) ==
			fdt_boot_cpuid_phys(initial_boot_params)) अणु
			found = boot_cpu_count;
			found_thपढ़ो = i;
		पूर्ण
#अगर_घोषित CONFIG_SMP
		/* logical cpu id is always 0 on UP kernels */
		boot_cpu_count++;
#पूर्ण_अगर
	पूर्ण

	/* Not the boot CPU */
	अगर (found < 0)
		वापस 0;

	DBG("boot cpu: logical %d physical %d\n", found,
	    be32_to_cpu(पूर्णांकserv[found_thपढ़ो]));
	boot_cpuid = found;

	/*
	 * PAPR defines "logical" PVR values क्रम cpus that
	 * meet various levels of the architecture:
	 * 0x0f000001	Architecture version 2.04
	 * 0x0f000002	Architecture version 2.05
	 * If the cpu-version property in the cpu node contains
	 * such a value, we call identअगरy_cpu again with the
	 * logical PVR value in order to use the cpu feature
	 * bits appropriate क्रम the architecture level.
	 *
	 * A POWER6 partition in "POWER6 architected" mode
	 * uses the 0x0f000002 PVR value; in POWER5+ mode
	 * it uses 0x0f000001.
	 *
	 * If we're using device tree CPU feature discovery then we don't
	 * support the cpu-version property, and it's the responsibility of the
	 * firmware/hypervisor to provide the correct feature set क्रम the
	 * architecture level via the ibm,घातerpc-cpu-features binding.
	 */
	अगर (!dt_cpu_ftrs_in_use()) अणु
		prop = of_get_flat_dt_prop(node, "cpu-version", शून्य);
		अगर (prop && (be32_to_cpup(prop) & 0xff000000) == 0x0f000000)
			identअगरy_cpu(0, be32_to_cpup(prop));

		check_cpu_feature_properties(node);
		check_cpu_pa_features(node);
	पूर्ण

	identical_pvr_fixup(node);
	init_mmu_slb_size(node);

#अगर_घोषित CONFIG_PPC64
	अगर (nthपढ़ोs == 1)
		cur_cpu_spec->cpu_features &= ~CPU_FTR_SMT;
	अन्यथा अगर (!dt_cpu_ftrs_in_use())
		cur_cpu_spec->cpu_features |= CPU_FTR_SMT;
	allocate_paca(boot_cpuid);
#पूर्ण_अगर
	set_hard_smp_processor_id(found, be32_to_cpu(पूर्णांकserv[found_thपढ़ो]));

	वापस 0;
पूर्ण

अटल पूर्णांक __init early_init_dt_scan_chosen_ppc(अचिन्हित दीर्घ node,
						स्थिर अक्षर *uname,
						पूर्णांक depth, व्योम *data)
अणु
	स्थिर अचिन्हित दीर्घ *lprop; /* All these set by kernel, so no need to convert endian */

	/* Use common scan routine to determine अगर this is the chosen node */
	अगर (early_init_dt_scan_chosen(node, uname, depth, data) == 0)
		वापस 0;

#अगर_घोषित CONFIG_PPC64
	/* check अगर iommu is क्रमced on or off */
	अगर (of_get_flat_dt_prop(node, "linux,iommu-off", शून्य) != शून्य)
		iommu_is_off = 1;
	अगर (of_get_flat_dt_prop(node, "linux,iommu-force-on", शून्य) != शून्य)
		iommu_क्रमce_on = 1;
#पूर्ण_अगर

	/* mem=x on the command line is the preferred mechanism */
	lprop = of_get_flat_dt_prop(node, "linux,memory-limit", शून्य);
	अगर (lprop)
		memory_limit = *lprop;

#अगर_घोषित CONFIG_PPC64
	lprop = of_get_flat_dt_prop(node, "linux,tce-alloc-start", शून्य);
	अगर (lprop)
		tce_alloc_start = *lprop;
	lprop = of_get_flat_dt_prop(node, "linux,tce-alloc-end", शून्य);
	अगर (lprop)
		tce_alloc_end = *lprop;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_CORE
	lprop = of_get_flat_dt_prop(node, "linux,crashkernel-base", शून्य);
	अगर (lprop)
		crashk_res.start = *lprop;

	lprop = of_get_flat_dt_prop(node, "linux,crashkernel-size", शून्य);
	अगर (lprop)
		crashk_res.end = crashk_res.start + *lprop - 1;
#पूर्ण_अगर

	/* अवरोध now */
	वापस 1;
पूर्ण

/*
 * Compare the range against max mem limit and update
 * size अगर it cross the limit.
 */

#अगर_घोषित CONFIG_SPARSEMEM
अटल bool validate_mem_limit(u64 base, u64 *size)
अणु
	u64 max_mem = 1UL << (MAX_PHYSMEM_BITS);

	अगर (base >= max_mem)
		वापस false;
	अगर ((base + *size) > max_mem)
		*size = max_mem - base;
	वापस true;
पूर्ण
#अन्यथा
अटल bool validate_mem_limit(u64 base, u64 *size)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PSERIES
/*
 * Interpret the ibm dynamic reconfiguration memory LMBs.
 * This contains a list of memory blocks aदीर्घ with NUMA affinity
 * inक्रमmation.
 */
अटल पूर्णांक  __init early_init_drmem_lmb(काष्ठा drmem_lmb *lmb,
					स्थिर __be32 **usm,
					व्योम *data)
अणु
	u64 base, size;
	पूर्णांक is_kexec_kdump = 0, rngs;

	base = lmb->base_addr;
	size = drmem_lmb_size();
	rngs = 1;

	/*
	 * Skip this block अगर the reserved bit is set in flags
	 * or अगर the block is not asचिन्हित to this partition.
	 */
	अगर ((lmb->flags & DRCONF_MEM_RESERVED) ||
	    !(lmb->flags & DRCONF_MEM_ASSIGNED))
		वापस 0;

	अगर (*usm)
		is_kexec_kdump = 1;

	अगर (is_kexec_kdump) अणु
		/*
		 * For each memblock in ibm,dynamic-memory, a
		 * corresponding entry in linux,drconf-usable-memory
		 * property contains a counter 'p' followed by 'p'
		 * (base, size) duple. Now पढ़ो the counter from
		 * linux,drconf-usable-memory property
		 */
		rngs = dt_mem_next_cell(dt_root_size_cells, usm);
		अगर (!rngs) /* there are no (base, size) duple */
			वापस 0;
	पूर्ण

	करो अणु
		अगर (is_kexec_kdump) अणु
			base = dt_mem_next_cell(dt_root_addr_cells, usm);
			size = dt_mem_next_cell(dt_root_size_cells, usm);
		पूर्ण

		अगर (iommu_is_off) अणु
			अगर (base >= 0x80000000ul)
				जारी;
			अगर ((base + size) > 0x80000000ul)
				size = 0x80000000ul - base;
		पूर्ण

		अगर (!validate_mem_limit(base, &size))
			जारी;

		DBG("Adding: %llx -> %llx\n", base, size);
		memblock_add(base, size);

		अगर (lmb->flags & DRCONF_MEM_HOTREMOVABLE)
			memblock_mark_hotplug(base, size);
	पूर्ण जबतक (--rngs);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

अटल पूर्णांक __init early_init_dt_scan_memory_ppc(अचिन्हित दीर्घ node,
						स्थिर अक्षर *uname,
						पूर्णांक depth, व्योम *data)
अणु
#अगर_घोषित CONFIG_PPC_PSERIES
	अगर (depth == 1 &&
	    म_भेद(uname, "ibm,dynamic-reconfiguration-memory") == 0) अणु
		walk_drmem_lmbs_early(node, शून्य, early_init_drmem_lmb);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	
	वापस early_init_dt_scan_memory(node, uname, depth, data);
पूर्ण

/*
 * For a relocatable kernel, we need to get the memstart_addr first,
 * then use it to calculate the भव kernel start address. This has
 * to happen at a very early stage (beक्रमe machine_init). In this हाल,
 * we just want to get the memstart_address and would not like to mess the
 * memblock at this stage. So पूर्णांकroduce a variable to skip the memblock_add()
 * क्रम this reason.
 */
#अगर_घोषित CONFIG_RELOCATABLE
अटल पूर्णांक add_mem_to_memblock = 1;
#अन्यथा
#घोषणा add_mem_to_memblock 1
#पूर्ण_अगर

व्योम __init early_init_dt_add_memory_arch(u64 base, u64 size)
अणु
#अगर_घोषित CONFIG_PPC64
	अगर (iommu_is_off) अणु
		अगर (base >= 0x80000000ul)
			वापस;
		अगर ((base + size) > 0x80000000ul)
			size = 0x80000000ul - base;
	पूर्ण
#पूर्ण_अगर
	/* Keep track of the beginning of memory -and- the size of
	 * the very first block in the device-tree as it represents
	 * the RMA on ppc64 server
	 */
	अगर (base < memstart_addr) अणु
		memstart_addr = base;
		first_memblock_size = size;
	पूर्ण

	/* Add the chunk to the MEMBLOCK list */
	अगर (add_mem_to_memblock) अणु
		अगर (validate_mem_limit(base, &size))
			memblock_add(base, size);
	पूर्ण
पूर्ण

अटल व्योम __init early_reserve_mem_dt(व्योम)
अणु
	अचिन्हित दीर्घ i, dt_root;
	पूर्णांक len;
	स्थिर __be32 *prop;

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	dt_root = of_get_flat_dt_root();

	prop = of_get_flat_dt_prop(dt_root, "reserved-ranges", &len);

	अगर (!prop)
		वापस;

	DBG("Found new-style reserved-ranges\n");

	/* Each reserved range is an (address,size) pair, 2 cells each,
	 * totalling 4 cells per range. */
	क्रम (i = 0; i < len / (माप(*prop) * 4); i++) अणु
		u64 base, size;

		base = of_पढ़ो_number(prop + (i * 4) + 0, 2);
		size = of_पढ़ो_number(prop + (i * 4) + 2, 2);

		अगर (size) अणु
			DBG("reserving: %llx -> %llx\n", base, size);
			memblock_reserve(base, size);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init early_reserve_mem(व्योम)
अणु
	__be64 *reserve_map;

	reserve_map = (__be64 *)(((अचिन्हित दीर्घ)initial_boot_params) +
			fdt_off_mem_rsvmap(initial_boot_params));

	/* Look क्रम the new "reserved-regions" property in the DT */
	early_reserve_mem_dt();

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	/* Then reserve the initrd, अगर any */
	अगर (initrd_start && (initrd_end > initrd_start)) अणु
		memblock_reserve(ALIGN_DOWN(__pa(initrd_start), PAGE_SIZE),
			ALIGN(initrd_end, PAGE_SIZE) -
			ALIGN_DOWN(initrd_start, PAGE_SIZE));
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

#अगर_घोषित CONFIG_PPC32
	/* 
	 * Handle the हाल where we might be booting from an old kexec
	 * image that setup the mem_rsvmap as pairs of 32-bit values
	 */
	अगर (be64_to_cpup(reserve_map) > 0xffffffffull) अणु
		u32 base_32, size_32;
		__be32 *reserve_map_32 = (__be32 *)reserve_map;

		DBG("Found old 32-bit reserve map\n");

		जबतक (1) अणु
			base_32 = be32_to_cpup(reserve_map_32++);
			size_32 = be32_to_cpup(reserve_map_32++);
			अगर (size_32 == 0)
				अवरोध;
			DBG("reserving: %x -> %x\n", base_32, size_32);
			memblock_reserve(base_32, size_32);
		पूर्ण
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल bool पंचांग_disabled __initdata;

अटल पूर्णांक __init parse_ppc_पंचांग(अक्षर *str)
अणु
	bool res;

	अगर (kstrtobool(str, &res))
		वापस -EINVAL;

	पंचांग_disabled = !res;

	वापस 0;
पूर्ण
early_param("ppc_tm", parse_ppc_पंचांग);

अटल व्योम __init पंचांग_init(व्योम)
अणु
	अगर (पंचांग_disabled) अणु
		pr_info("Disabling hardware transactional memory (HTM)\n");
		cur_cpu_spec->cpu_user_features2 &=
			~(PPC_FEATURE2_HTM_NOSC | PPC_FEATURE2_HTM);
		cur_cpu_spec->cpu_features &= ~CPU_FTR_TM;
		वापस;
	पूर्ण

	pnv_पंचांग_init();
पूर्ण
#अन्यथा
अटल व्योम पंचांग_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

#अगर_घोषित CONFIG_PPC64
अटल व्योम __init save_fscr_to_task(व्योम)
अणु
	/*
	 * Ensure the init_task (pid 0, aka swapper) uses the value of FSCR we
	 * have configured via the device tree features or via __init_FSCR().
	 * That value will then be propagated to pid 1 (init) and all future
	 * processes.
	 */
	अगर (early_cpu_has_feature(CPU_FTR_ARCH_207S))
		init_task.thपढ़ो.fscr = mfspr(SPRN_FSCR);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम save_fscr_to_task(व्योम) अणुपूर्ण
#पूर्ण_अगर


व्योम __init early_init_devtree(व्योम *params)
अणु
	phys_addr_t limit;

	DBG(" -> early_init_devtree(%px)\n", params);

	/* Too early to BUG_ON(), करो it by hand */
	अगर (!early_init_dt_verअगरy(params))
		panic("BUG: Failed verifying flat device tree, bad version?");

#अगर_घोषित CONFIG_PPC_RTAS
	/* Some machines might need RTAS info क्रम debugging, grab it now. */
	of_scan_flat_dt(early_init_dt_scan_rtas, शून्य);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
	/* Some machines might need OPAL info क्रम debugging, grab it now. */
	of_scan_flat_dt(early_init_dt_scan_opal, शून्य);

	/* Scan tree क्रम ultravisor feature */
	of_scan_flat_dt(early_init_dt_scan_ultravisor, शून्य);
#पूर्ण_अगर

#अगर defined(CONFIG_FA_DUMP) || defined(CONFIG_PRESERVE_FA_DUMP)
	/* scan tree to see अगर dump is active during last boot */
	of_scan_flat_dt(early_init_dt_scan_fw_dump, शून्य);
#पूर्ण_अगर

	/* Retrieve various inक्रमmations from the /chosen node of the
	 * device-tree, including the platक्रमm type, initrd location and
	 * size, TCE reserve, and more ...
	 */
	of_scan_flat_dt(early_init_dt_scan_chosen_ppc, boot_command_line);

	/* Scan memory nodes and rebuild MEMBLOCKs */
	of_scan_flat_dt(early_init_dt_scan_root, शून्य);
	of_scan_flat_dt(early_init_dt_scan_memory_ppc, शून्य);

	parse_early_param();

	/* make sure we've parsed cmdline क्रम mem= beक्रमe this */
	अगर (memory_limit)
		first_memblock_size = min_t(u64, first_memblock_size, memory_limit);
	setup_initial_memory_limit(memstart_addr, first_memblock_size);
	/* Reserve MEMBLOCK regions used by kernel, initrd, dt, etc... */
	memblock_reserve(PHYSICAL_START, __pa(klimit) - PHYSICAL_START);
	/* If relocatable, reserve first 32k क्रम पूर्णांकerrupt vectors etc. */
	अगर (PHYSICAL_START > MEMORY_START)
		memblock_reserve(MEMORY_START, 0x8000);
	reserve_kdump_trampoline();
#अगर defined(CONFIG_FA_DUMP) || defined(CONFIG_PRESERVE_FA_DUMP)
	/*
	 * If we fail to reserve memory क्रम firmware-assisted dump then
	 * fallback to kexec based kdump.
	 */
	अगर (fadump_reserve_mem() == 0)
#पूर्ण_अगर
		reserve_crashkernel();
	early_reserve_mem();

	/* Ensure that total memory size is page-aligned. */
	limit = ALIGN(memory_limit ?: memblock_phys_mem_size(), PAGE_SIZE);
	memblock_enक्रमce_memory_limit(limit);

#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_PPC_4K_PAGES)
	अगर (!early_radix_enabled())
		memblock_cap_memory_range(0, 1UL << (H_MAX_PHYSMEM_BITS));
#पूर्ण_अगर

	memblock_allow_resize();
	memblock_dump_all();

	DBG("Phys. mem: %llx\n", (अचिन्हित दीर्घ दीर्घ)memblock_phys_mem_size());

	/* We may need to relocate the flat tree, करो it now.
	 * FIXME .. and the initrd too? */
	move_device_tree();

	allocate_paca_ptrs();

	DBG("Scanning CPUs ...\n");

	dt_cpu_ftrs_scan();

	/* Retrieve CPU related inक्रमmations from the flat tree
	 * (altivec support, boot CPU ID, ...)
	 */
	of_scan_flat_dt(early_init_dt_scan_cpus, शून्य);
	अगर (boot_cpuid < 0) अणु
		prपूर्णांकk("Failed to identify boot CPU !\n");
		BUG();
	पूर्ण

	save_fscr_to_task();

#अगर defined(CONFIG_SMP) && defined(CONFIG_PPC64)
	/* We'll later रुको क्रम secondaries to check in; there are
	 * NCPUS-1 non-boot CPUs  :-)
	 */
	spinning_secondaries = boot_cpu_count - 1;
#पूर्ण_अगर

	mmu_early_init_devtree();

#अगर_घोषित CONFIG_PPC_POWERNV
	/* Scan and build the list of machine check recoverable ranges */
	of_scan_flat_dt(early_init_dt_scan_recoverable_ranges, शून्य);
#पूर्ण_अगर
	epapr_paravirt_early_init();

	/* Now try to figure out अगर we are running on LPAR and so on */
	pseries_probe_fw_features();

	/*
	 * Initialize pkey features and शेष AMR/IAMR values
	 */
	pkey_early_init_devtree();

#अगर_घोषित CONFIG_PPC_PS3
	/* Identअगरy PS3 firmware */
	अगर (of_flat_dt_is_compatible(of_get_flat_dt_root(), "sony,ps3"))
		घातerpc_firmware_features |= FW_FEATURE_PS3_POSSIBLE;
#पूर्ण_अगर

	पंचांग_init();

	DBG(" <- early_init_devtree()\n");
पूर्ण

#अगर_घोषित CONFIG_RELOCATABLE
/*
 * This function run beक्रमe early_init_devtree, so we have to init
 * initial_boot_params.
 */
व्योम __init early_get_first_memblock_info(व्योम *params, phys_addr_t *size)
अणु
	/* Setup flat device-tree poपूर्णांकer */
	initial_boot_params = params;

	/*
	 * Scan the memory nodes and set add_mem_to_memblock to 0 to aव्योम
	 * mess the memblock.
	 */
	add_mem_to_memblock = 0;
	of_scan_flat_dt(early_init_dt_scan_root, शून्य);
	of_scan_flat_dt(early_init_dt_scan_memory_ppc, शून्य);
	add_mem_to_memblock = 1;

	अगर (size)
		*size = first_memblock_size;
पूर्ण
#पूर्ण_अगर

/*******
 *
 * New implementation of the OF "find" APIs, वापस a refcounted
 * object, call of_node_put() when करोne.  The device tree and list
 * are रक्षित by a rw_lock.
 *
 * Note that property management will need some locking as well,
 * this isn't dealt with yet.
 *
 *******/

/**
 * of_get_ibm_chip_id - Returns the IBM "chip-id" of a device
 * @np: device node of the device
 *
 * This looks क्रम a property "ibm,chip-id" in the node or any
 * of its parents and वापसs its content, or -1 अगर it cannot
 * be found.
 */
पूर्णांक of_get_ibm_chip_id(काष्ठा device_node *np)
अणु
	of_node_get(np);
	जबतक (np) अणु
		u32 chip_id;

		/*
		 * Skiboot may produce memory nodes that contain more than one
		 * cell in chip-id, we only पढ़ो the first one here.
		 */
		अगर (!of_property_पढ़ो_u32(np, "ibm,chip-id", &chip_id)) अणु
			of_node_put(np);
			वापस chip_id;
		पूर्ण

		np = of_get_next_parent(np);
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(of_get_ibm_chip_id);

/**
 * cpu_to_chip_id - Return the cpus chip-id
 * @cpu: The logical cpu number.
 *
 * Return the value of the ibm,chip-id property corresponding to the given
 * logical cpu number. If the chip-id can not be found, वापसs -1.
 */
पूर्णांक cpu_to_chip_id(पूर्णांक cpu)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret = -1, idx;

	idx = cpu / thपढ़ोs_per_core;
	अगर (chip_id_lookup_table && chip_id_lookup_table[idx] != -1)
		वापस chip_id_lookup_table[idx];

	np = of_get_cpu_node(cpu, शून्य);
	अगर (np) अणु
		ret = of_get_ibm_chip_id(np);
		of_node_put(np);

		अगर (chip_id_lookup_table)
			chip_id_lookup_table[idx] = ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cpu_to_chip_id);

bool arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id)
अणु
#अगर_घोषित CONFIG_SMP
	/*
	 * Early firmware scanning must use this rather than
	 * get_hard_smp_processor_id because we करोn't have pacas allocated
	 * until memory topology is discovered.
	 */
	अगर (cpu_to_phys_id != शून्य)
		वापस (पूर्णांक)phys_id == cpu_to_phys_id[cpu];
#पूर्ण_अगर

	वापस (पूर्णांक)phys_id == get_hard_smp_processor_id(cpu);
पूर्ण
