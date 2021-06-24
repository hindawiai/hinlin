<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (C) 2019 Jason Yan <yanaijie@huawei.com>

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/memblock.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/crash_core.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/kdump.h>
#समावेश <mm/mmu_decl.h>
#समावेश <generated/compile.h>
#समावेश <generated/utsrelease.h>

काष्ठा regions अणु
	अचिन्हित दीर्घ pa_start;
	अचिन्हित दीर्घ pa_end;
	अचिन्हित दीर्घ kernel_size;
	अचिन्हित दीर्घ dtb_start;
	अचिन्हित दीर्घ dtb_end;
	अचिन्हित दीर्घ initrd_start;
	अचिन्हित दीर्घ initrd_end;
	अचिन्हित दीर्घ crash_start;
	अचिन्हित दीर्घ crash_end;
	पूर्णांक reserved_mem;
	पूर्णांक reserved_mem_addr_cells;
	पूर्णांक reserved_mem_size_cells;
पूर्ण;

/* Simplअगरied build-specअगरic string क्रम starting entropy. */
अटल स्थिर अक्षर build_str[] = UTS_RELEASE " (" LINUX_COMPILE_BY "@"
		LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION;

काष्ठा regions __initdata regions;

अटल __init व्योम kaslr_get_cmdline(व्योम *fdt)
अणु
	पूर्णांक node = fdt_path_offset(fdt, "/chosen");

	early_init_dt_scan_chosen(node, "chosen", 1, boot_command_line);
पूर्ण

अटल अचिन्हित दीर्घ __init rotate_xor(अचिन्हित दीर्घ hash, स्थिर व्योम *area,
				       माप_प्रकार size)
अणु
	माप_प्रकार i;
	स्थिर अचिन्हित दीर्घ *ptr = area;

	क्रम (i = 0; i < size / माप(hash); i++) अणु
		/* Rotate by odd number of bits and XOR. */
		hash = (hash << ((माप(hash) * 8) - 7)) | (hash >> 7);
		hash ^= ptr[i];
	पूर्ण

	वापस hash;
पूर्ण

/* Attempt to create a simple starting entropy. This can make it defferent क्रम
 * every build but it is still not enough. Stronger entropy should
 * be added to make it change क्रम every boot.
 */
अटल अचिन्हित दीर्घ __init get_boot_seed(व्योम *fdt)
अणु
	अचिन्हित दीर्घ hash = 0;

	hash = rotate_xor(hash, build_str, माप(build_str));
	hash = rotate_xor(hash, fdt, fdt_totalsize(fdt));

	वापस hash;
पूर्ण

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

अटल __init bool regions_overlap(u32 s1, u32 e1, u32 s2, u32 e2)
अणु
	वापस e1 >= s2 && e2 >= s1;
पूर्ण

अटल __init bool overlaps_reserved_region(स्थिर व्योम *fdt, u32 start,
					    u32 end)
अणु
	पूर्णांक subnode, len, i;
	u64 base, size;

	/* check क्रम overlap with /memreserve/ entries */
	क्रम (i = 0; i < fdt_num_mem_rsv(fdt); i++) अणु
		अगर (fdt_get_mem_rsv(fdt, i, &base, &size) < 0)
			जारी;
		अगर (regions_overlap(start, end, base, base + size))
			वापस true;
	पूर्ण

	अगर (regions.reserved_mem < 0)
		वापस false;

	/* check क्रम overlap with अटल reservations in /reserved-memory */
	क्रम (subnode = fdt_first_subnode(fdt, regions.reserved_mem);
	     subnode >= 0;
	     subnode = fdt_next_subnode(fdt, subnode)) अणु
		स्थिर fdt32_t *reg;
		u64 rsv_end;

		len = 0;
		reg = fdt_getprop(fdt, subnode, "reg", &len);
		जबतक (len >= (regions.reserved_mem_addr_cells +
			       regions.reserved_mem_size_cells)) अणु
			base = fdt32_to_cpu(reg[0]);
			अगर (regions.reserved_mem_addr_cells == 2)
				base = (base << 32) | fdt32_to_cpu(reg[1]);

			reg += regions.reserved_mem_addr_cells;
			len -= 4 * regions.reserved_mem_addr_cells;

			size = fdt32_to_cpu(reg[0]);
			अगर (regions.reserved_mem_size_cells == 2)
				size = (size << 32) | fdt32_to_cpu(reg[1]);

			reg += regions.reserved_mem_size_cells;
			len -= 4 * regions.reserved_mem_size_cells;

			अगर (base >= regions.pa_end)
				जारी;

			rsv_end = min(base + size, (u64)U32_MAX);

			अगर (regions_overlap(start, end, base, rsv_end))
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल __init bool overlaps_region(स्थिर व्योम *fdt, u32 start,
				   u32 end)
अणु
	अगर (regions_overlap(start, end, __pa(_stext), __pa(_end)))
		वापस true;

	अगर (regions_overlap(start, end, regions.dtb_start,
			    regions.dtb_end))
		वापस true;

	अगर (regions_overlap(start, end, regions.initrd_start,
			    regions.initrd_end))
		वापस true;

	अगर (regions_overlap(start, end, regions.crash_start,
			    regions.crash_end))
		वापस true;

	वापस overlaps_reserved_region(fdt, start, end);
पूर्ण

अटल व्योम __init get_crash_kernel(व्योम *fdt, अचिन्हित दीर्घ size)
अणु
#अगर_घोषित CONFIG_CRASH_CORE
	अचिन्हित दीर्घ दीर्घ crash_size, crash_base;
	पूर्णांक ret;

	ret = parse_crashkernel(boot_command_line, size, &crash_size,
				&crash_base);
	अगर (ret != 0 || crash_size == 0)
		वापस;
	अगर (crash_base == 0)
		crash_base = KDUMP_KERNELBASE;

	regions.crash_start = (अचिन्हित दीर्घ)crash_base;
	regions.crash_end = (अचिन्हित दीर्घ)(crash_base + crash_size);

	pr_debug("crash_base=0x%llx crash_size=0x%llx\n", crash_base, crash_size);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init get_initrd_range(व्योम *fdt)
अणु
	u64 start, end;
	पूर्णांक node, len;
	स्थिर __be32 *prop;

	node = fdt_path_offset(fdt, "/chosen");
	अगर (node < 0)
		वापस;

	prop = fdt_getprop(fdt, node, "linux,initrd-start", &len);
	अगर (!prop)
		वापस;
	start = of_पढ़ो_number(prop, len / 4);

	prop = fdt_getprop(fdt, node, "linux,initrd-end", &len);
	अगर (!prop)
		वापस;
	end = of_पढ़ो_number(prop, len / 4);

	regions.initrd_start = (अचिन्हित दीर्घ)start;
	regions.initrd_end = (अचिन्हित दीर्घ)end;

	pr_debug("initrd_start=0x%llx  initrd_end=0x%llx\n", start, end);
पूर्ण

अटल __init अचिन्हित दीर्घ get_usable_address(स्थिर व्योम *fdt,
					       अचिन्हित दीर्घ start,
					       अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ pa;
	अचिन्हित दीर्घ pa_end;

	क्रम (pa = offset; (दीर्घ)pa > (दीर्घ)start; pa -= SZ_16K) अणु
		pa_end = pa + regions.kernel_size;
		अगर (overlaps_region(fdt, pa, pa_end))
			जारी;

		वापस pa;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init व्योम get_cell_sizes(स्थिर व्योम *fdt, पूर्णांक node, पूर्णांक *addr_cells,
				  पूर्णांक *size_cells)
अणु
	स्थिर पूर्णांक *prop;
	पूर्णांक len;

	/*
	 * Retrieve the #address-cells and #size-cells properties
	 * from the 'node', or use the शेष अगर not provided.
	 */
	*addr_cells = *size_cells = 1;

	prop = fdt_getprop(fdt, node, "#address-cells", &len);
	अगर (len == 4)
		*addr_cells = fdt32_to_cpu(*prop);
	prop = fdt_getprop(fdt, node, "#size-cells", &len);
	अगर (len == 4)
		*size_cells = fdt32_to_cpu(*prop);
पूर्ण

अटल अचिन्हित दीर्घ __init kaslr_legal_offset(व्योम *dt_ptr, अचिन्हित दीर्घ index,
					       अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ koffset = 0;
	अचिन्हित दीर्घ start;

	जबतक ((दीर्घ)index >= 0) अणु
		offset = memstart_addr + index * SZ_64M + offset;
		start = memstart_addr + index * SZ_64M;
		koffset = get_usable_address(dt_ptr, start, offset);
		अगर (koffset)
			अवरोध;
		index--;
	पूर्ण

	अगर (koffset != 0)
		koffset -= memstart_addr;

	वापस koffset;
पूर्ण

अटल अंतरभूत __init bool kaslr_disabled(व्योम)
अणु
	वापस म_माला(boot_command_line, "nokaslr") != शून्य;
पूर्ण

अटल अचिन्हित दीर्घ __init kaslr_choose_location(व्योम *dt_ptr, phys_addr_t size,
						  अचिन्हित दीर्घ kernel_sz)
अणु
	अचिन्हित दीर्घ offset, अक्रमom;
	अचिन्हित दीर्घ ram, linear_sz;
	u64 seed;
	अचिन्हित दीर्घ index;

	kaslr_get_cmdline(dt_ptr);
	अगर (kaslr_disabled())
		वापस 0;

	अक्रमom = get_boot_seed(dt_ptr);

	seed = get_tb() << 32;
	seed ^= get_tb();
	अक्रमom = rotate_xor(अक्रमom, &seed, माप(seed));

	/*
	 * Retrieve (and wipe) the seed from the FDT
	 */
	seed = get_kaslr_seed(dt_ptr);
	अगर (seed)
		अक्रमom = rotate_xor(अक्रमom, &seed, माप(seed));
	अन्यथा
		pr_warn("KASLR: No safe seed for randomizing the kernel base.\n");

	ram = min_t(phys_addr_t, __max_low_memory, size);
	ram = map_mem_in_cams(ram, CONFIG_LOWMEM_CAM_NUM, true);
	linear_sz = min_t(अचिन्हित दीर्घ, ram, SZ_512M);

	/* If the linear size is smaller than 64M, करो not अक्रमmize */
	अगर (linear_sz < SZ_64M)
		वापस 0;

	/* check क्रम a reserved-memory node and record its cell sizes */
	regions.reserved_mem = fdt_path_offset(dt_ptr, "/reserved-memory");
	अगर (regions.reserved_mem >= 0)
		get_cell_sizes(dt_ptr, regions.reserved_mem,
			       &regions.reserved_mem_addr_cells,
			       &regions.reserved_mem_size_cells);

	regions.pa_start = memstart_addr;
	regions.pa_end = memstart_addr + linear_sz;
	regions.dtb_start = __pa(dt_ptr);
	regions.dtb_end = __pa(dt_ptr) + fdt_totalsize(dt_ptr);
	regions.kernel_size = kernel_sz;

	get_initrd_range(dt_ptr);
	get_crash_kernel(dt_ptr, ram);

	/*
	 * Decide which 64M we want to start
	 * Only use the low 8 bits of the अक्रमom seed
	 */
	index = अक्रमom & 0xFF;
	index %= linear_sz / SZ_64M;

	/* Decide offset inside 64M */
	offset = अक्रमom % (SZ_64M - kernel_sz);
	offset = round_करोwn(offset, SZ_16K);

	वापस kaslr_legal_offset(dt_ptr, index, offset);
पूर्ण

/*
 * To see अगर we need to relocate the kernel to a अक्रमom offset
 * व्योम *dt_ptr - address of the device tree
 * phys_addr_t size - size of the first memory block
 */
notrace व्योम __init kaslr_early_init(व्योम *dt_ptr, phys_addr_t size)
अणु
	अचिन्हित दीर्घ tlb_virt;
	phys_addr_t tlb_phys;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ kernel_sz;

	kernel_sz = (अचिन्हित दीर्घ)_end - (अचिन्हित दीर्घ)_stext;

	offset = kaslr_choose_location(dt_ptr, size, kernel_sz);
	अगर (offset == 0)
		वापस;

	kernstart_virt_addr += offset;
	kernstart_addr += offset;

	is_second_reloc = 1;

	अगर (offset >= SZ_64M) अणु
		tlb_virt = round_करोwn(kernstart_virt_addr, SZ_64M);
		tlb_phys = round_करोwn(kernstart_addr, SZ_64M);

		/* Create kernel map to relocate in */
		create_kaslr_tlb_entry(1, tlb_virt, tlb_phys);
	पूर्ण

	/* Copy the kernel to it's new location and run */
	स_नकल((व्योम *)kernstart_virt_addr, (व्योम *)_stext, kernel_sz);
	flush_icache_range(kernstart_virt_addr, kernstart_virt_addr + kernel_sz);

	reloc_kernel_entry(dt_ptr, kernstart_virt_addr);
पूर्ण

व्योम __init kaslr_late_init(व्योम)
अणु
	/* If अक्रमomized, clear the original kernel */
	अगर (kernstart_virt_addr != KERNELBASE) अणु
		अचिन्हित दीर्घ kernel_sz;

		kernel_sz = (अचिन्हित दीर्घ)_end - kernstart_virt_addr;
		memzero_explicit((व्योम *)KERNELBASE, kernel_sz);
	पूर्ण
पूर्ण
