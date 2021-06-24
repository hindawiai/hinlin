<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/console.h>
#समावेश <linux/memblock.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/screen_info.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>

#अगर_घोषित CONFIG_DUMMY_CONSOLE
काष्ठा screen_info screen_info = अणु
	.orig_video_lines	= 30,
	.orig_video_cols	= 80,
	.orig_video_mode	= 0,
	.orig_video_ega_bx	= 0,
	.orig_video_isVGA	= 1,
	.orig_video_poपूर्णांकs	= 8
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init csky_memblock_init(व्योम)
अणु
	अचिन्हित दीर्घ lowmem_size = PFN_DOWN(LOWMEM_LIMIT - PHYS_OFFSET_OFFSET);
	अचिन्हित दीर्घ sseg_size = PFN_DOWN(SSEG_SIZE - PHYS_OFFSET_OFFSET);
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;
	चिन्हित दीर्घ size;

	memblock_reserve(__pa(_stext), _end - _stext);

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	memblock_dump_all();

	min_low_pfn = PFN_UP(memblock_start_of_DRAM());
	max_low_pfn = max_pfn = PFN_DOWN(memblock_end_of_DRAM());

	size = max_pfn - min_low_pfn;

	अगर (size >= lowmem_size) अणु
		max_low_pfn = min_low_pfn + lowmem_size;
#अगर_घोषित CONFIG_PAGE_OFFSET_80000000
		ग_लिखो_mmu_msa1(पढ़ो_mmu_msa0() + SSEG_SIZE);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (size > sseg_size) अणु
		max_low_pfn = min_low_pfn + sseg_size;
	पूर्ण

	max_zone_pfn[ZONE_NORMAL] = max_low_pfn;

	mmu_init(min_low_pfn, max_low_pfn);

#अगर_घोषित CONFIG_HIGHMEM
	max_zone_pfn[ZONE_HIGHMEM] = max_pfn;

	highstart_pfn = max_low_pfn;
	highend_pfn   = max_pfn;
#पूर्ण_अगर
	memblock_set_current_limit(PFN_PHYS(max_low_pfn));

	dma_contiguous_reserve(0);

	मुक्त_area_init(max_zone_pfn);
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	*cmdline_p = boot_command_line;

	console_verbose();

	pr_info("Phys. mem: %ldMB\n",
		(अचिन्हित दीर्घ) memblock_phys_mem_size()/1024/1024);

	init_mm.start_code = (अचिन्हित दीर्घ) _stext;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = (अचिन्हित दीर्घ) _end;

	parse_early_param();

	csky_memblock_init();

	unflatten_and_copy_device_tree();

#अगर_घोषित CONFIG_SMP
	setup_smp();
#पूर्ण_अगर

	sparse_init();

	fixaddr_init();

#अगर_घोषित CONFIG_HIGHMEM
	kmap_init();
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ va_pa_offset;
EXPORT_SYMBOL(va_pa_offset);

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_mmu_msa(व्योम)
अणु
#अगर_घोषित CONFIG_PAGE_OFFSET_80000000
	वापस पढ़ो_mmu_msa0();
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_OFFSET_A0000000
	वापस पढ़ो_mmu_msa1();
#पूर्ण_अगर
पूर्ण

यंत्रlinkage __visible व्योम __init csky_start(अचिन्हित पूर्णांक unused,
					    व्योम *dtb_start)
अणु
	/* Clean up bss section */
	स_रखो(__bss_start, 0, __bss_stop - __bss_start);

	va_pa_offset = पढ़ो_mmu_msa() & ~(SSEG_SIZE - 1);

	pre_trap_init();

	अगर (dtb_start == शून्य)
		early_init_dt_scan(__dtb_start);
	अन्यथा
		early_init_dt_scan(dtb_start);

	start_kernel();

	यंत्र अस्थिर("br .\n");
पूर्ण
