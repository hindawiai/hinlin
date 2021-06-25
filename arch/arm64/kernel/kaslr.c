<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/cache.h>
#समावेश <linux/crc32.h>
#समावेश <linux/init.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/अक्रमom.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/kernel-pgtable.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>

क्रमागत kaslr_status अणु
	KASLR_ENABLED,
	KASLR_DISABLED_CMDLINE,
	KASLR_DISABLED_NO_SEED,
	KASLR_DISABLED_FDT_REMAP,
पूर्ण;

अटल क्रमागत kaslr_status __initdata kaslr_status;
u64 __ro_after_init module_alloc_base;
u16 __initdata memstart_offset_seed;

अटल __init u64 get_kaslr_seed(व्योम *fdt)
अणु
	पूर्णांक node, len;
	fdt64_t *prop;
	u64 ret;

	node = fdt_path_offset(fdt, "/chosen");
	अगर (node < 0)
		वापस 0;

	prop = fdt_getprop_w(fdt, node, "kaslr-seed", &len);
	अगर (!prop || len != माप(u64))
		वापस 0;

	ret = fdt64_to_cpu(*prop);
	*prop = 0;
	वापस ret;
पूर्ण

काष्ठा arm64_ftr_override kaslr_feature_override __initdata;

/*
 * This routine will be executed with the kernel mapped at its शेष भव
 * address, and अगर it वापसs successfully, the kernel will be remapped, and
 * start_kernel() will be executed from a अक्रमomized भव offset. The
 * relocation will result in all असलolute references (e.g., अटल variables
 * containing function poपूर्णांकers) to be reinitialized, and zero-initialized
 * .bss variables will be reset to 0.
 */
u64 __init kaslr_early_init(व्योम)
अणु
	व्योम *fdt;
	u64 seed, offset, mask, module_range;
	अचिन्हित दीर्घ raw;

	/*
	 * Set a reasonable शेष क्रम module_alloc_base in हाल
	 * we end up running with module अक्रमomization disabled.
	 */
	module_alloc_base = (u64)_etext - MODULES_VSIZE;
	__flush_dcache_area(&module_alloc_base, माप(module_alloc_base));

	/*
	 * Try to map the FDT early. If this fails, we simply bail,
	 * and proceed with KASLR disabled. We will make another
	 * attempt at mapping the FDT in setup_machine()
	 */
	fdt = get_early_fdt_ptr();
	अगर (!fdt) अणु
		kaslr_status = KASLR_DISABLED_FDT_REMAP;
		वापस 0;
	पूर्ण

	/*
	 * Retrieve (and wipe) the seed from the FDT
	 */
	seed = get_kaslr_seed(fdt);

	/*
	 * Check अगर 'nokaslr' appears on the command line, and
	 * वापस 0 अगर that is the हाल.
	 */
	अगर (kaslr_feature_override.val & kaslr_feature_override.mask & 0xf) अणु
		kaslr_status = KASLR_DISABLED_CMDLINE;
		वापस 0;
	पूर्ण

	/*
	 * Mix in any entropy obtainable architecturally अगर enabled
	 * and supported.
	 */

	अगर (arch_get_अक्रमom_seed_दीर्घ_early(&raw))
		seed ^= raw;

	अगर (!seed) अणु
		kaslr_status = KASLR_DISABLED_NO_SEED;
		वापस 0;
	पूर्ण

	/*
	 * OK, so we are proceeding with KASLR enabled. Calculate a suitable
	 * kernel image offset from the seed. Let's place the kernel in the
	 * middle half of the VMALLOC area (VA_BITS_MIN - 2), and stay clear of
	 * the lower and upper quarters to aव्योम colliding with other
	 * allocations.
	 * Even अगर we could अक्रमomize at page granularity क्रम 16k and 64k pages,
	 * let's always round to 2 MB so we don't पूर्णांकerfere with the ability to
	 * map using contiguous PTEs
	 */
	mask = ((1UL << (VA_BITS_MIN - 2)) - 1) & ~(SZ_2M - 1);
	offset = BIT(VA_BITS_MIN - 3) + (seed & mask);

	/* use the top 16 bits to अक्रमomize the linear region */
	memstart_offset_seed = seed >> 48;

	अगर (!IS_ENABLED(CONFIG_KASAN_VMALLOC) &&
	    (IS_ENABLED(CONFIG_KASAN_GENERIC) ||
	     IS_ENABLED(CONFIG_KASAN_SW_TAGS)))
		/*
		 * KASAN without KASAN_VMALLOC करोes not expect the module region
		 * to पूर्णांकersect the vदो_स्मृति region, since shaकरोw memory is
		 * allocated क्रम each module at load समय, whereas the vदो_स्मृति
		 * region is shaकरोwed by KASAN zero pages. So keep modules
		 * out of the vदो_स्मृति region अगर KASAN is enabled without
		 * KASAN_VMALLOC, and put the kernel well within 4 GB of the
		 * module region.
		 */
		वापस offset % SZ_2G;

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_MODULE_REGION_FULL)) अणु
		/*
		 * Ranकरोmize the module region over a 2 GB winकरोw covering the
		 * kernel. This reduces the risk of modules leaking inक्रमmation
		 * about the address of the kernel itself, but results in
		 * branches between modules and the core kernel that are
		 * resolved via PLTs. (Branches between modules will be
		 * resolved normally.)
		 */
		module_range = SZ_2G - (u64)(_end - _stext);
		module_alloc_base = max((u64)_end + offset - SZ_2G,
					(u64)MODULES_VADDR);
	पूर्ण अन्यथा अणु
		/*
		 * Ranकरोmize the module region by setting module_alloc_base to
		 * a PAGE_SIZE multiple in the range [_etext - MODULES_VSIZE,
		 * _stext) . This guarantees that the resulting region still
		 * covers [_stext, _etext], and that all relative branches can
		 * be resolved without veneers.
		 */
		module_range = MODULES_VSIZE - (u64)(_etext - _stext);
		module_alloc_base = (u64)_etext + offset - MODULES_VSIZE;
	पूर्ण

	/* use the lower 21 bits to अक्रमomize the base of the module region */
	module_alloc_base += (module_range * (seed & ((1 << 21) - 1))) >> 21;
	module_alloc_base &= PAGE_MASK;

	__flush_dcache_area(&module_alloc_base, माप(module_alloc_base));
	__flush_dcache_area(&memstart_offset_seed, माप(memstart_offset_seed));

	वापस offset;
पूर्ण

अटल पूर्णांक __init kaslr_init(व्योम)
अणु
	चयन (kaslr_status) अणु
	हाल KASLR_ENABLED:
		pr_info("KASLR enabled\n");
		अवरोध;
	हाल KASLR_DISABLED_CMDLINE:
		pr_info("KASLR disabled on command line\n");
		अवरोध;
	हाल KASLR_DISABLED_NO_SEED:
		pr_warn("KASLR disabled due to lack of seed\n");
		अवरोध;
	हाल KASLR_DISABLED_FDT_REMAP:
		pr_warn("KASLR disabled due to FDT remapping failure\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(kaslr_init)
