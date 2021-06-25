<शैली गुरु>
/*
 * arch/xtensa/kernel/setup.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995  Linus Torvalds
 * Copyright (C) 2001 - 2005  Tensilica Inc.
 * Copyright (C) 2014 - 2016  Cadence Design Systems Inc.
 *
 * Chris Zankel	<chris@zankel.net>
 * Joe Taylor	<joe@tensilica.com, joetylr@yahoo.com>
 * Kevin Chea
 * Marc Gauthier<marc@tensilica.com> <marc@alumni.uwaterloo.ca>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>

#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE)
# include <linux/console.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
# include <linux/seq_file.h>
#पूर्ण_अगर

#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/sysस्मृति.स>

#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE)
काष्ठा screen_info screen_info = अणु
	.orig_x = 0,
	.orig_y = 24,
	.orig_video_cols = 80,
	.orig_video_lines = 24,
	.orig_video_isVGA = 1,
	.orig_video_poपूर्णांकs = 16,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_INITRD
बाह्य अचिन्हित दीर्घ initrd_start;
बाह्य अचिन्हित दीर्घ initrd_end;
बाह्य पूर्णांक initrd_below_start_ok;
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
व्योम *dtb_start = __dtb_start;
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

/* Command line specअगरied as configuration option. */

अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE];

#अगर_घोषित CONFIG_CMDLINE_BOOL
अटल अक्षर शेष_command_line[COMMAND_LINE_SIZE] __initdata = CONFIG_CMDLINE;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PARSE_BOOTPARAM
/*
 * Boot parameter parsing.
 *
 * The Xtensa port uses a list of variable-sized tags to pass data to
 * the kernel. The first tag must be a BP_TAG_FIRST tag क्रम the list
 * to be recognised. The list is terminated with a zero-sized
 * BP_TAG_LAST tag.
 */

प्रकार काष्ठा tagtable अणु
	u32 tag;
	पूर्णांक (*parse)(स्थिर bp_tag_t*);
पूर्ण tagtable_t;

#घोषणा __tagtable(tag, fn) अटल tagtable_t __tagtable_##fn 		\
	__section(".taglist") __attribute__((used)) = अणु tag, fn पूर्ण

/* parse current tag */

अटल पूर्णांक __init parse_tag_mem(स्थिर bp_tag_t *tag)
अणु
	काष्ठा bp_meminfo *mi = (काष्ठा bp_meminfo *)(tag->data);

	अगर (mi->type != MEMORY_TYPE_CONVENTIONAL)
		वापस -1;

	वापस memblock_add(mi->start, mi->end - mi->start);
पूर्ण

__tagtable(BP_TAG_MEMORY, parse_tag_mem);

#अगर_घोषित CONFIG_BLK_DEV_INITRD

अटल पूर्णांक __init parse_tag_initrd(स्थिर bp_tag_t* tag)
अणु
	काष्ठा bp_meminfo *mi = (काष्ठा bp_meminfo *)(tag->data);

	initrd_start = (अचिन्हित दीर्घ)__va(mi->start);
	initrd_end = (अचिन्हित दीर्घ)__va(mi->end);

	वापस 0;
पूर्ण

__tagtable(BP_TAG_INITRD, parse_tag_initrd);

#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

#अगर_घोषित CONFIG_OF

अटल पूर्णांक __init parse_tag_fdt(स्थिर bp_tag_t *tag)
अणु
	dtb_start = __va(tag->data[0]);
	वापस 0;
पूर्ण

__tagtable(BP_TAG_FDT, parse_tag_fdt);

#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक __init parse_tag_cmdline(स्थिर bp_tag_t* tag)
अणु
	strlcpy(command_line, (अक्षर *)(tag->data), COMMAND_LINE_SIZE);
	वापस 0;
पूर्ण

__tagtable(BP_TAG_COMMAND_LINE, parse_tag_cmdline);

अटल पूर्णांक __init parse_bootparam(स्थिर bp_tag_t* tag)
अणु
	बाह्य tagtable_t __tagtable_begin, __tagtable_end;
	tagtable_t *t;

	/* Boot parameters must start with a BP_TAG_FIRST tag. */

	अगर (tag->id != BP_TAG_FIRST) अणु
		pr_warn("Invalid boot parameters!\n");
		वापस 0;
	पूर्ण

	tag = (bp_tag_t*)((अचिन्हित दीर्घ)tag + माप(bp_tag_t) + tag->size);

	/* Parse all tags. */

	जबतक (tag != शून्य && tag->id != BP_TAG_LAST) अणु
		क्रम (t = &__tagtable_begin; t < &__tagtable_end; t++) अणु
			अगर (tag->id == t->tag) अणु
				t->parse(tag);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (t == &__tagtable_end)
			pr_warn("Ignoring tag 0x%08x\n", tag->id);
		tag = (bp_tag_t*)((अचिन्हित दीर्घ)(tag + 1) + tag->size);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक __init parse_bootparam(स्थिर bp_tag_t *tag)
अणु
	pr_info("Ignoring boot parameters at %p\n", tag);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF

#अगर !XCHAL_HAVE_PTP_MMU || XCHAL_HAVE_SPANNING_WAY
अचिन्हित दीर्घ xtensa_kio_paddr = XCHAL_KIO_DEFAULT_PADDR;
EXPORT_SYMBOL(xtensa_kio_paddr);

अटल पूर्णांक __init xtensa_dt_io_area(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
		पूर्णांक depth, व्योम *data)
अणु
	स्थिर __be32 *ranges;
	पूर्णांक len;

	अगर (depth > 1)
		वापस 0;

	अगर (!of_flat_dt_is_compatible(node, "simple-bus"))
		वापस 0;

	ranges = of_get_flat_dt_prop(node, "ranges", &len);
	अगर (!ranges)
		वापस 1;
	अगर (len == 0)
		वापस 1;

	xtensa_kio_paddr = of_पढ़ो_uदीर्घ(ranges+1, 1);
	/* round करोwn to nearest 256MB boundary */
	xtensa_kio_paddr &= 0xf0000000;

	init_kio();

	वापस 1;
पूर्ण
#अन्यथा
अटल पूर्णांक __init xtensa_dt_io_area(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
		पूर्णांक depth, व्योम *data)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

व्योम __init early_init_devtree(व्योम *params)
अणु
	early_init_dt_scan(params);
	of_scan_flat_dt(xtensa_dt_io_area, शून्य);

	अगर (!command_line[0])
		strlcpy(command_line, boot_command_line, COMMAND_LINE_SIZE);
पूर्ण

#पूर्ण_अगर /* CONFIG_OF */

/*
 * Initialize architecture. (Early stage)
 */

व्योम __init init_arch(bp_tag_t *bp_start)
अणु
	/* Initialize MMU. */

	init_mmu();

	/* Initialize initial KASAN shaकरोw map */

	kasan_early_init();

	/* Parse boot parameters */

	अगर (bp_start)
		parse_bootparam(bp_start);

#अगर_घोषित CONFIG_OF
	early_init_devtree(dtb_start);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CMDLINE_BOOL
	अगर (!command_line[0])
		strlcpy(command_line, शेष_command_line, COMMAND_LINE_SIZE);
#पूर्ण_अगर

	/* Early hook क्रम platक्रमms */

	platक्रमm_init(bp_start);
पूर्ण

/*
 * Initialize प्रणाली. Setup memory and reserve regions.
 */

बाह्य अक्षर _end[];
बाह्य अक्षर _stext[];
बाह्य अक्षर _WinकरोwVectors_text_start;
बाह्य अक्षर _WinकरोwVectors_text_end;
बाह्य अक्षर _DebugInterruptVector_text_start;
बाह्य अक्षर _DebugInterruptVector_text_end;
बाह्य अक्षर _KernelExceptionVector_text_start;
बाह्य अक्षर _KernelExceptionVector_text_end;
बाह्य अक्षर _UserExceptionVector_text_start;
बाह्य अक्षर _UserExceptionVector_text_end;
बाह्य अक्षर _DoubleExceptionVector_text_start;
बाह्य अक्षर _DoubleExceptionVector_text_end;
बाह्य अक्षर _exception_text_start;
बाह्य अक्षर _exception_text_end;
#अगर XCHAL_EXCM_LEVEL >= 2
बाह्य अक्षर _Level2InterruptVector_text_start;
बाह्य अक्षर _Level2InterruptVector_text_end;
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 3
बाह्य अक्षर _Level3InterruptVector_text_start;
बाह्य अक्षर _Level3InterruptVector_text_end;
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 4
बाह्य अक्षर _Level4InterruptVector_text_start;
बाह्य अक्षर _Level4InterruptVector_text_end;
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 5
बाह्य अक्षर _Level5InterruptVector_text_start;
बाह्य अक्षर _Level5InterruptVector_text_end;
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 6
बाह्य अक्षर _Level6InterruptVector_text_start;
बाह्य अक्षर _Level6InterruptVector_text_end;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
बाह्य अक्षर _SecondaryResetVector_text_start;
बाह्य अक्षर _SecondaryResetVector_text_end;
#पूर्ण_अगर
#अगर_घोषित CONFIG_XIP_KERNEL
बाह्य अक्षर _xip_start[];
बाह्य अक्षर _xip_end[];
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक __init_memblock mem_reserve(अचिन्हित दीर्घ start,
					      अचिन्हित दीर्घ end)
अणु
	वापस memblock_reserve(start, end - start);
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	pr_info("config ID: %08x:%08x\n",
		xtensa_get_sr(SREG_EPC), xtensa_get_sr(SREG_EXCSAVE));
	अगर (xtensa_get_sr(SREG_EPC) != XCHAL_HW_CONFIGID0 ||
	    xtensa_get_sr(SREG_EXCSAVE) != XCHAL_HW_CONFIGID1)
		pr_info("built for config ID: %08x:%08x\n",
			XCHAL_HW_CONFIGID0, XCHAL_HW_CONFIGID1);

	*cmdline_p = command_line;
	platक्रमm_setup(cmdline_p);
	strlcpy(boot_command_line, *cmdline_p, COMMAND_LINE_SIZE);

	/* Reserve some memory regions */

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start < initrd_end &&
	    !mem_reserve(__pa(initrd_start), __pa(initrd_end)))
		initrd_below_start_ok = 1;
	अन्यथा
		initrd_start = 0;
#पूर्ण_अगर

	mem_reserve(__pa(_stext), __pa(_end));
#अगर_घोषित CONFIG_XIP_KERNEL
	mem_reserve(__pa(_xip_start), __pa(_xip_end));
#पूर्ण_अगर

#अगर_घोषित CONFIG_VECTORS_ADDR
	mem_reserve(__pa(&_WinकरोwVectors_text_start),
		    __pa(&_WinकरोwVectors_text_end));

	mem_reserve(__pa(&_DebugInterruptVector_text_start),
		    __pa(&_DebugInterruptVector_text_end));

	mem_reserve(__pa(&_KernelExceptionVector_text_start),
		    __pa(&_KernelExceptionVector_text_end));

	mem_reserve(__pa(&_UserExceptionVector_text_start),
		    __pa(&_UserExceptionVector_text_end));

	mem_reserve(__pa(&_DoubleExceptionVector_text_start),
		    __pa(&_DoubleExceptionVector_text_end));

	mem_reserve(__pa(&_exception_text_start),
		    __pa(&_exception_text_end));
#अगर XCHAL_EXCM_LEVEL >= 2
	mem_reserve(__pa(&_Level2InterruptVector_text_start),
		    __pa(&_Level2InterruptVector_text_end));
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 3
	mem_reserve(__pa(&_Level3InterruptVector_text_start),
		    __pa(&_Level3InterruptVector_text_end));
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 4
	mem_reserve(__pa(&_Level4InterruptVector_text_start),
		    __pa(&_Level4InterruptVector_text_end));
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 5
	mem_reserve(__pa(&_Level5InterruptVector_text_start),
		    __pa(&_Level5InterruptVector_text_end));
#पूर्ण_अगर
#अगर XCHAL_EXCM_LEVEL >= 6
	mem_reserve(__pa(&_Level6InterruptVector_text_start),
		    __pa(&_Level6InterruptVector_text_end));
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_VECTORS_ADDR */

#अगर_घोषित CONFIG_SMP
	mem_reserve(__pa(&_SecondaryResetVector_text_start),
		    __pa(&_SecondaryResetVector_text_end));
#पूर्ण_अगर
	parse_early_param();
	booपंचांगem_init();
	kasan_init();
	unflatten_and_copy_device_tree();

#अगर_घोषित CONFIG_SMP
	smp_init_cpus();
#पूर्ण_अगर

	paging_init();
	zones_init();

#अगर_घोषित CONFIG_VT
# अगर defined(CONFIG_VGA_CONSOLE)
	conचयनp = &vga_con;
# endअगर
#पूर्ण_अगर
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_data);

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा cpu *cpu = &per_cpu(cpu_data, i);
		cpu->hotpluggable = !!i;
		रेजिस्टर_cpu(cpu, i);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(topology_init);

व्योम cpu_reset(व्योम)
अणु
#अगर XCHAL_HAVE_PTP_MMU && IS_ENABLED(CONFIG_MMU)
	local_irq_disable();
	/*
	 * We have full MMU: all स्वतःload ways, ways 7, 8 and 9 of DTLB must
	 * be flushed.
	 * Way 4 is not currently used by linux.
	 * Ways 5 and 6 shall not be touched on MMUv2 as they are hardwired.
	 * Way 5 shall be flushed and way 6 shall be set to identity mapping
	 * on MMUv3.
	 */
	local_flush_tlb_all();
	invalidate_page_directory();
#अगर XCHAL_HAVE_SPANNING_WAY
	/* MMU v3 */
	अणु
		अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)cpu_reset;
		अचिन्हित दीर्घ paddr = __pa(vaddr);
		अचिन्हित दीर्घ पंचांगpaddr = vaddr + SZ_512M;
		अचिन्हित दीर्घ पंचांगp0, पंचांगp1, पंचांगp2, पंचांगp3;

		/*
		 * Find a place क्रम the temporary mapping. It must not be
		 * in the same 512MB region with vaddr or paddr, otherwise
		 * there may be multihit exception either on entry to the
		 * temporary mapping, or on entry to the identity mapping.
		 * (512MB is the biggest page size supported by TLB.)
		 */
		जबतक (((पंचांगpaddr ^ paddr) & -SZ_512M) == 0)
			पंचांगpaddr += SZ_512M;

		/* Invalidate mapping in the selected temporary area */
		अगर (itlb_probe(पंचांगpaddr) & BIT(ITLB_HIT_BIT))
			invalidate_itlb_entry(itlb_probe(पंचांगpaddr));
		अगर (itlb_probe(पंचांगpaddr + PAGE_SIZE) & BIT(ITLB_HIT_BIT))
			invalidate_itlb_entry(itlb_probe(पंचांगpaddr + PAGE_SIZE));

		/*
		 * Map two consecutive pages starting at the physical address
		 * of this function to the temporary mapping area.
		 */
		ग_लिखो_itlb_entry(__pte((paddr & PAGE_MASK) |
				       _PAGE_HW_VALID |
				       _PAGE_HW_EXEC |
				       _PAGE_CA_BYPASS),
				 पंचांगpaddr & PAGE_MASK);
		ग_लिखो_itlb_entry(__pte(((paddr & PAGE_MASK) + PAGE_SIZE) |
				       _PAGE_HW_VALID |
				       _PAGE_HW_EXEC |
				       _PAGE_CA_BYPASS),
				 (पंचांगpaddr & PAGE_MASK) + PAGE_SIZE);

		/* Reinitialize TLB */
		__यंत्र__ __अस्थिर__ ("movi	%0, 1f\n\t"
				      "movi	%3, 2f\n\t"
				      "add	%0, %0, %4\n\t"
				      "add	%3, %3, %5\n\t"
				      "jx	%0\n"
				      /*
				       * No literal, data or stack access
				       * below this poपूर्णांक
				       */
				      "1:\n\t"
				      /* Initialize *tlbcfg */
				      "movi	%0, 0\n\t"
				      "wsr	%0, itlbcfg\n\t"
				      "wsr	%0, dtlbcfg\n\t"
				      /* Invalidate TLB way 5 */
				      "movi	%0, 4\n\t"
				      "movi	%1, 5\n"
				      "1:\n\t"
				      "iitlb	%1\n\t"
				      "idtlb	%1\n\t"
				      "add	%1, %1, %6\n\t"
				      "addi	%0, %0, -1\n\t"
				      "bnez	%0, 1b\n\t"
				      /* Initialize TLB way 6 */
				      "movi	%0, 7\n\t"
				      "addi	%1, %9, 3\n\t"
				      "addi	%2, %9, 6\n"
				      "1:\n\t"
				      "witlb	%1, %2\n\t"
				      "wdtlb	%1, %2\n\t"
				      "add	%1, %1, %7\n\t"
				      "add	%2, %2, %7\n\t"
				      "addi	%0, %0, -1\n\t"
				      "bnez	%0, 1b\n\t"
				      "isync\n\t"
				      /* Jump to identity mapping */
				      "jx	%3\n"
				      "2:\n\t"
				      /* Complete way 6 initialization */
				      "witlb	%1, %2\n\t"
				      "wdtlb	%1, %2\n\t"
				      /* Invalidate temporary mapping */
				      "sub	%0, %9, %7\n\t"
				      "iitlb	%0\n\t"
				      "add	%0, %0, %8\n\t"
				      "iitlb	%0"
				      : "=&a"(पंचांगp0), "=&a"(पंचांगp1), "=&a"(पंचांगp2),
					"=&a"(पंचांगp3)
				      : "a"(पंचांगpaddr - vaddr),
					"a"(paddr - vaddr),
					"a"(SZ_128M), "a"(SZ_512M),
					"a"(PAGE_SIZE),
					"a"((पंचांगpaddr + SZ_512M) & PAGE_MASK)
				      : "memory");
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	__यंत्र__ __अस्थिर__ ("movi	a2, 0\n\t"
			      "wsr	a2, icountlevel\n\t"
			      "movi	a2, 0\n\t"
			      "wsr	a2, icount\n\t"
#अगर XCHAL_NUM_IBREAK > 0
			      "wsr	a2, ibreakenable\n\t"
#पूर्ण_अगर
#अगर XCHAL_HAVE_LOOPS
			      "wsr	a2, lcount\n\t"
#पूर्ण_अगर
			      "movi	a2, 0x1f\n\t"
			      "wsr	a2, ps\n\t"
			      "isync\n\t"
			      "jx	%0\n\t"
			      :
			      : "a" (XCHAL_RESET_VECTOR_VADDR)
			      : "a2");
	क्रम (;;)
		;
पूर्ण

व्योम machine_restart(अक्षर * cmd)
अणु
	platक्रमm_restart();
पूर्ण

व्योम machine_halt(व्योम)
अणु
	platक्रमm_halt();
	जबतक (1);
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	platक्रमm_घातer_off();
	जबतक (1);
पूर्ण
#अगर_घोषित CONFIG_PROC_FS

/*
 * Display some core inक्रमmation through /proc/cpuinfo.
 */

अटल पूर्णांक
c_show(काष्ठा seq_file *f, व्योम *slot)
अणु
	/* high-level stuff */
	seq_म_लिखो(f, "CPU count\t: %u\n"
		      "CPU list\t: %*pbl\n"
		      "vendor_id\t: Tensilica\n"
		      "model\t\t: Xtensa " XCHAL_HW_VERSION_NAME "\n"
		      "core ID\t\t: " XCHAL_CORE_ID "\n"
		      "build ID\t: 0x%x\n"
		      "config ID\t: %08x:%08x\n"
		      "byte order\t: %s\n"
		      "cpu MHz\t\t: %lu.%02lu\n"
		      "bogomips\t: %lu.%02lu\n",
		      num_online_cpus(),
		      cpumask_pr_args(cpu_online_mask),
		      XCHAL_BUILD_UNIQUE_ID,
		      xtensa_get_sr(SREG_EPC), xtensa_get_sr(SREG_EXCSAVE),
		      XCHAL_HAVE_BE ?  "big" : "little",
		      ccount_freq/1000000,
		      (ccount_freq/10000) % 100,
		      loops_per_jअगरfy/(500000/HZ),
		      (loops_per_jअगरfy/(5000/HZ)) % 100);
	seq_माला_दो(f, "flags\t\t: "
#अगर XCHAL_HAVE_NMI
		     "nmi "
#पूर्ण_अगर
#अगर XCHAL_HAVE_DEBUG
		     "debug "
# अगर XCHAL_HAVE_OCD
		     "ocd "
# endअगर
#पूर्ण_अगर
#अगर XCHAL_HAVE_DENSITY
	    	     "density "
#पूर्ण_अगर
#अगर XCHAL_HAVE_BOOLEANS
		     "boolean "
#पूर्ण_अगर
#अगर XCHAL_HAVE_LOOPS
		     "loop "
#पूर्ण_अगर
#अगर XCHAL_HAVE_NSA
		     "nsa "
#पूर्ण_अगर
#अगर XCHAL_HAVE_MINMAX
		     "minmax "
#पूर्ण_अगर
#अगर XCHAL_HAVE_SEXT
		     "sext "
#पूर्ण_अगर
#अगर XCHAL_HAVE_CLAMPS
		     "clamps "
#पूर्ण_अगर
#अगर XCHAL_HAVE_MAC16
		     "mac16 "
#पूर्ण_अगर
#अगर XCHAL_HAVE_MUL16
		     "mul16 "
#पूर्ण_अगर
#अगर XCHAL_HAVE_MUL32
		     "mul32 "
#पूर्ण_अगर
#अगर XCHAL_HAVE_MUL32_HIGH
		     "mul32h "
#पूर्ण_अगर
#अगर XCHAL_HAVE_FP
		     "fpu "
#पूर्ण_अगर
#अगर XCHAL_HAVE_S32C1I
		     "s32c1i "
#पूर्ण_अगर
#अगर XCHAL_HAVE_EXCLUSIVE
		     "exclusive "
#पूर्ण_अगर
		     "\n");

	/* Registers. */
	seq_म_लिखो(f,"physical aregs\t: %d\n"
		     "misc regs\t: %d\n"
		     "ibreak\t\t: %d\n"
		     "dbreak\t\t: %d\n",
		     XCHAL_NUM_AREGS,
		     XCHAL_NUM_MISC_REGS,
		     XCHAL_NUM_IBREAK,
		     XCHAL_NUM_DBREAK);


	/* Interrupt. */
	seq_म_लिखो(f,"num ints\t: %d\n"
		     "ext ints\t: %d\n"
		     "int levels\t: %d\n"
		     "timers\t\t: %d\n"
		     "debug level\t: %d\n",
		     XCHAL_NUM_INTERRUPTS,
		     XCHAL_NUM_EXTINTERRUPTS,
		     XCHAL_NUM_INTLEVELS,
		     XCHAL_NUM_TIMERS,
		     XCHAL_DEBUGLEVEL);

	/* Cache */
	seq_म_लिखो(f,"icache line size: %d\n"
		     "icache ways\t: %d\n"
		     "icache size\t: %d\n"
		     "icache flags\t: "
#अगर XCHAL_ICACHE_LINE_LOCKABLE
		     "lock "
#पूर्ण_अगर
		     "\n"
		     "dcache line size: %d\n"
		     "dcache ways\t: %d\n"
		     "dcache size\t: %d\n"
		     "dcache flags\t: "
#अगर XCHAL_DCACHE_IS_WRITEBACK
		     "writeback "
#पूर्ण_अगर
#अगर XCHAL_DCACHE_LINE_LOCKABLE
		     "lock "
#पूर्ण_अगर
		     "\n",
		     XCHAL_ICACHE_LINESIZE,
		     XCHAL_ICACHE_WAYS,
		     XCHAL_ICACHE_SIZE,
		     XCHAL_DCACHE_LINESIZE,
		     XCHAL_DCACHE_WAYS,
		     XCHAL_DCACHE_SIZE);

	वापस 0;
पूर्ण

/*
 * We show only CPU #0 info.
 */
अटल व्योम *
c_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	वापस (*pos == 0) ? (व्योम *)1 : शून्य;
पूर्ण

अटल व्योम *
c_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(f, pos);
पूर्ण

अटल व्योम
c_stop(काष्ठा seq_file *f, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op =
अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PROC_FS */
