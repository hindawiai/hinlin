<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/cpu.h>
#समावेश <linux/memblock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/console.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/cache_info.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/fpu.h>
#समावेश <nds32_पूर्णांकrinsic.h>

#घोषणा HWCAP_MFUSR_PC		0x000001
#घोषणा HWCAP_EXT		0x000002
#घोषणा HWCAP_EXT2		0x000004
#घोषणा HWCAP_FPU		0x000008
#घोषणा HWCAP_AUDIO		0x000010
#घोषणा HWCAP_BASE16		0x000020
#घोषणा HWCAP_STRING		0x000040
#घोषणा HWCAP_REDUCED_REGS	0x000080
#घोषणा HWCAP_VIDEO		0x000100
#घोषणा HWCAP_ENCRYPT		0x000200
#घोषणा HWCAP_EDM		0x000400
#घोषणा HWCAP_LMDMA		0x000800
#घोषणा HWCAP_PFM		0x001000
#घोषणा HWCAP_HSMP		0x002000
#घोषणा HWCAP_TRACE		0x004000
#घोषणा HWCAP_DIV		0x008000
#घोषणा HWCAP_MAC		0x010000
#घोषणा HWCAP_L2C		0x020000
#घोषणा HWCAP_FPU_DP		0x040000
#घोषणा HWCAP_V2		0x080000
#घोषणा HWCAP_DX_REGS		0x100000
#घोषणा HWCAP_HWPRE		0x200000

अचिन्हित दीर्घ cpu_id, cpu_rev, cpu_cfgid;
bool has_fpu = false;
अक्षर cpu_series;
अक्षर *endianness = शून्य;

अचिन्हित पूर्णांक __atags_poपूर्णांकer __initdata;
अचिन्हित पूर्णांक elf_hwcap;
EXPORT_SYMBOL(elf_hwcap);

/*
 * The following string table, must sync with HWCAP_xx biपंचांगask,
 * which is defined above
 */
अटल स्थिर अक्षर *hwcap_str[] = अणु
	"mfusr_pc",
	"perf1",
	"perf2",
	"fpu",
	"audio",
	"16b",
	"string",
	"reduced_regs",
	"video",
	"encrypt",
	"edm",
	"lmdma",
	"pfm",
	"hsmp",
	"trace",
	"div",
	"mac",
	"l2c",
	"fpu_dp",
	"v2",
	"dx_regs",
	"hw_pre",
	शून्य,
पूर्ण;

#अगर_घोषित CONFIG_CPU_DCACHE_WRITETHROUGH
#घोषणा WRITE_METHOD "write through"
#अन्यथा
#घोषणा WRITE_METHOD "write back"
#पूर्ण_अगर

काष्ठा cache_info L1_cache_info[2];
अटल व्योम __init dump_cpu_info(पूर्णांक cpu)
अणु
	पूर्णांक i, p = 0;
	अक्षर str[माप(hwcap_str) + 16];

	क्रम (i = 0; hwcap_str[i]; i++) अणु
		अगर (elf_hwcap & (1 << i)) अणु
			प्र_लिखो(str + p, "%s ", hwcap_str[i]);
			p += म_माप(hwcap_str[i]) + 1;
		पूर्ण
	पूर्ण

	pr_info("CPU%d Features: %s\n", cpu, str);

	L1_cache_info[ICACHE].ways = CACHE_WAY(ICACHE);
	L1_cache_info[ICACHE].line_size = CACHE_LINE_SIZE(ICACHE);
	L1_cache_info[ICACHE].sets = CACHE_SET(ICACHE);
	L1_cache_info[ICACHE].size =
	    L1_cache_info[ICACHE].ways * L1_cache_info[ICACHE].line_size *
	    L1_cache_info[ICACHE].sets / 1024;
	pr_info("L1I:%dKB/%dS/%dW/%dB\n", L1_cache_info[ICACHE].size,
		L1_cache_info[ICACHE].sets, L1_cache_info[ICACHE].ways,
		L1_cache_info[ICACHE].line_size);
	L1_cache_info[DCACHE].ways = CACHE_WAY(DCACHE);
	L1_cache_info[DCACHE].line_size = CACHE_LINE_SIZE(DCACHE);
	L1_cache_info[DCACHE].sets = CACHE_SET(DCACHE);
	L1_cache_info[DCACHE].size =
	    L1_cache_info[DCACHE].ways * L1_cache_info[DCACHE].line_size *
	    L1_cache_info[DCACHE].sets / 1024;
	pr_info("L1D:%dKB/%dS/%dW/%dB\n", L1_cache_info[DCACHE].size,
		L1_cache_info[DCACHE].sets, L1_cache_info[DCACHE].ways,
		L1_cache_info[DCACHE].line_size);
	pr_info("L1 D-Cache is %s\n", WRITE_METHOD);
	अगर (L1_cache_info[DCACHE].size != L1_CACHE_BYTES)
		pr_crit
		    ("The cache line size(%d) of this processor is not the same as L1_CACHE_BYTES(%d).\n",
		     L1_cache_info[DCACHE].size, L1_CACHE_BYTES);
#अगर_घोषित CONFIG_CPU_CACHE_ALIASING
	अणु
		पूर्णांक aliasing_num;
		aliasing_num =
		    L1_cache_info[ICACHE].size * 1024 / PAGE_SIZE /
		    L1_cache_info[ICACHE].ways;
		L1_cache_info[ICACHE].aliasing_num = aliasing_num;
		L1_cache_info[ICACHE].aliasing_mask =
		    (aliasing_num - 1) << PAGE_SHIFT;
		aliasing_num =
		    L1_cache_info[DCACHE].size * 1024 / PAGE_SIZE /
		    L1_cache_info[DCACHE].ways;
		L1_cache_info[DCACHE].aliasing_num = aliasing_num;
		L1_cache_info[DCACHE].aliasing_mask =
		    (aliasing_num - 1) << PAGE_SHIFT;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FPU
	/* Disable fpu and enable when it is used. */
	अगर (has_fpu)
		disable_fpu();
#पूर्ण_अगर
पूर्ण

अटल व्योम __init setup_cpuinfo(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp = 0, cpu_name;

	cpu_dcache_inval_all();
	cpu_icache_inval_all();
	__nds32__isb();

	cpu_id = (__nds32__mfsr(NDS32_SR_CPU_VER) & CPU_VER_mskCPUID) >> CPU_VER_offCPUID;
	cpu_name = ((cpu_id) & 0xf0) >> 4;
	cpu_series = cpu_name ? cpu_name - 10 + 'A' : 'N';
	cpu_id = cpu_id & 0xf;
	cpu_rev = (__nds32__mfsr(NDS32_SR_CPU_VER) & CPU_VER_mskREV) >> CPU_VER_offREV;
	cpu_cfgid = (__nds32__mfsr(NDS32_SR_CPU_VER) & CPU_VER_mskCFGID) >> CPU_VER_offCFGID;

	pr_info("CPU:%c%ld, CPU_VER 0x%08x(id %lu, rev %lu, cfg %lu)\n",
		cpu_series, cpu_id, __nds32__mfsr(NDS32_SR_CPU_VER), cpu_id, cpu_rev, cpu_cfgid);

	elf_hwcap |= HWCAP_MFUSR_PC;

	अगर (((__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskBASEV) >> MSC_CFG_offBASEV) == 0) अणु
		अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskDIV)
			elf_hwcap |= HWCAP_DIV;

		अगर ((__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskMAC)
		    || (cpu_id == 12 && cpu_rev < 4))
			elf_hwcap |= HWCAP_MAC;
	पूर्ण अन्यथा अणु
		elf_hwcap |= HWCAP_V2;
		elf_hwcap |= HWCAP_DIV;
		elf_hwcap |= HWCAP_MAC;
	पूर्ण

	अगर (cpu_cfgid & 0x0001)
		elf_hwcap |= HWCAP_EXT;

	अगर (cpu_cfgid & 0x0002)
		elf_hwcap |= HWCAP_BASE16;

	अगर (cpu_cfgid & 0x0004)
		elf_hwcap |= HWCAP_EXT2;

	अगर (cpu_cfgid & 0x0008) अणु
		elf_hwcap |= HWCAP_FPU;
		has_fpu = true;
	पूर्ण
	अगर (cpu_cfgid & 0x0010)
		elf_hwcap |= HWCAP_STRING;

	अगर (__nds32__mfsr(NDS32_SR_MMU_CFG) & MMU_CFG_mskDE)
		endianness = "MSB";
	अन्यथा
		endianness = "LSB";

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskEDM)
		elf_hwcap |= HWCAP_EDM;

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskLMDMA)
		elf_hwcap |= HWCAP_LMDMA;

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskPFM)
		elf_hwcap |= HWCAP_PFM;

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskHSMP)
		elf_hwcap |= HWCAP_HSMP;

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskTRACE)
		elf_hwcap |= HWCAP_TRACE;

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskAUDIO)
		elf_hwcap |= HWCAP_AUDIO;

	अगर (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskL2C)
		elf_hwcap |= HWCAP_L2C;

#अगर_घोषित CONFIG_HW_PRE
	अगर (__nds32__mfsr(NDS32_SR_MISC_CTL) & MISC_CTL_makHWPRE_EN)
		elf_hwcap |= HWCAP_HWPRE;
#पूर्ण_अगर

	पंचांगp = __nds32__mfsr(NDS32_SR_CACHE_CTL);
	अगर (!IS_ENABLED(CONFIG_CPU_DCACHE_DISABLE))
		पंचांगp |= CACHE_CTL_mskDC_EN;

	अगर (!IS_ENABLED(CONFIG_CPU_ICACHE_DISABLE))
		पंचांगp |= CACHE_CTL_mskIC_EN;
	__nds32__mtsr_isb(पंचांगp, NDS32_SR_CACHE_CTL);

	dump_cpu_info(smp_processor_id());
पूर्ण

अटल व्योम __init setup_memory(व्योम)
अणु
	अचिन्हित दीर्घ ram_start_pfn;
	अचिन्हित दीर्घ मुक्त_ram_start_pfn;
	phys_addr_t memory_start, memory_end;
	काष्ठा memblock_region *region;

	memory_end = memory_start = 0;

	/* Find मुख्य memory where is the kernel */
	memory_start = memblock_start_of_DRAM();
	memory_end = memblock_end_of_DRAM();

	अगर (!memory_end) अणु
		panic("No memory!");
	पूर्ण

	ram_start_pfn = PFN_UP(memblock_start_of_DRAM());
	/* मुक्त_ram_start_pfn is first page after kernel */
	मुक्त_ram_start_pfn = PFN_UP(__pa(&_end));
	max_pfn = PFN_DOWN(memblock_end_of_DRAM());
	/* it could update max_pfn */
	अगर (max_pfn - ram_start_pfn <= MAXMEM_PFN)
		max_low_pfn = max_pfn;
	अन्यथा अणु
		max_low_pfn = MAXMEM_PFN + ram_start_pfn;
		अगर (!IS_ENABLED(CONFIG_HIGHMEM))
			max_pfn = MAXMEM_PFN + ram_start_pfn;
	पूर्ण
	/* high_memory is related with VMALLOC */
	high_memory = (व्योम *)__va(max_low_pfn * PAGE_SIZE);
	min_low_pfn = मुक्त_ram_start_pfn;

	/*
	 * initialize the boot-समय allocator (with low memory only).
	 *
	 * This makes the memory from the end of the kernel to the end of
	 * RAM usable.
	 */
	memblock_set_bottom_up(true);
	memblock_reserve(PFN_PHYS(ram_start_pfn), PFN_PHYS(मुक्त_ram_start_pfn - ram_start_pfn));

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	memblock_dump_all();
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	early_init_devtree(__atags_poपूर्णांकer ? \
		phys_to_virt(__atags_poपूर्णांकer) : __dtb_start);

	setup_cpuinfo();

	init_mm.start_code = (अचिन्हित दीर्घ)&_stext;
	init_mm.end_code = (अचिन्हित दीर्घ)&_etext;
	init_mm.end_data = (अचिन्हित दीर्घ)&_edata;
	init_mm.brk = (अचिन्हित दीर्घ)&_end;

	/* setup booपंचांगem allocator */
	setup_memory();

	/* paging_init() sets up the MMU and marks all pages as reserved */
	paging_init();

	/* invalidate all TLB entries because the new mapping is created */
	__nds32__tlbop_flua();

	/* use generic way to parse */
	parse_early_param();

	unflatten_and_copy_device_tree();

	*cmdline_p = boot_command_line;
	early_trap_init();
पूर्ण

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	seq_म_लिखो(m, "Processor\t: %c%ld (id %lu, rev %lu, cfg %lu)\n",
		   cpu_series, cpu_id, cpu_id, cpu_rev, cpu_cfgid);

	seq_म_लिखो(m, "L1I\t\t: %luKB/%luS/%luW/%luB\n",
		   CACHE_SET(ICACHE) * CACHE_WAY(ICACHE) *
		   CACHE_LINE_SIZE(ICACHE) / 1024, CACHE_SET(ICACHE),
		   CACHE_WAY(ICACHE), CACHE_LINE_SIZE(ICACHE));

	seq_म_लिखो(m, "L1D\t\t: %luKB/%luS/%luW/%luB\n",
		   CACHE_SET(DCACHE) * CACHE_WAY(DCACHE) *
		   CACHE_LINE_SIZE(DCACHE) / 1024, CACHE_SET(DCACHE),
		   CACHE_WAY(DCACHE), CACHE_LINE_SIZE(DCACHE));

	seq_म_लिखो(m, "BogoMIPS\t: %lu.%02lu\n",
		   loops_per_jअगरfy / (500000 / HZ),
		   (loops_per_jअगरfy / (5000 / HZ)) % 100);

	/* dump out the processor features */
	seq_माला_दो(m, "Features\t: ");

	क्रम (i = 0; hwcap_str[i]; i++)
		अगर (elf_hwcap & (1 << i))
			seq_म_लिखो(m, "%s ", hwcap_str[i]);

	seq_माला_दो(m, "\n\n");

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t * pos)
अणु
	वापस *pos < 1 ? (व्योम *)1 : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t * pos)
अणु
	++*pos;
	वापस शून्य;
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

काष्ठा seq_operations cpuinfo_op = अणु
	.start = c_start,
	.next = c_next,
	.stop = c_stop,
	.show = c_show
पूर्ण;
