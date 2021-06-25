<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/kernel/setup.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 */

/*
 * This file handles the architecture-dependent parts of प्रणाली setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/console.h>
#समावेश <linux/genhd.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/nvram.h>
#समावेश <linux/initrd.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#अगर_घोषित CONFIG_AMIGA
#समावेश <यंत्र/amigahw.h>
#पूर्ण_अगर
#समावेश <यंत्र/atarihw.h>
#अगर_घोषित CONFIG_ATARI
#समावेश <यंत्र/atari_stram.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN3X
#समावेश <यंत्र/dvma.h>
#पूर्ण_अगर
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/natfeat.h>

#अगर !FPSTATESIZE || !NR_IRQS
#warning No CPU/platक्रमm type selected, your kernel will not work!
#warning Are you building an allnoconfig kernel?
#पूर्ण_अगर

अचिन्हित दीर्घ m68k_machtype;
EXPORT_SYMBOL(m68k_machtype);
अचिन्हित दीर्घ m68k_cputype;
EXPORT_SYMBOL(m68k_cputype);
अचिन्हित दीर्घ m68k_fputype;
अचिन्हित दीर्घ m68k_mmutype;
EXPORT_SYMBOL(m68k_mmutype);
#अगर_घोषित CONFIG_VME
अचिन्हित दीर्घ vme_brdtype;
EXPORT_SYMBOL(vme_brdtype);
#पूर्ण_अगर

पूर्णांक m68k_is040or060;
EXPORT_SYMBOL(m68k_is040or060);

बाह्य अचिन्हित दीर्घ availmem;

पूर्णांक m68k_num_memory;
EXPORT_SYMBOL(m68k_num_memory);
पूर्णांक m68k_realnum_memory;
EXPORT_SYMBOL(m68k_realnum_memory);
अचिन्हित दीर्घ m68k_memoffset;
काष्ठा m68k_mem_info m68k_memory[NUM_MEMINFO];
EXPORT_SYMBOL(m68k_memory);

अटल काष्ठा m68k_mem_info m68k_ramdisk __initdata;

अटल अक्षर m68k_command_line[CL_SIZE] __initdata;

व्योम (*mach_sched_init) (व्योम) __initdata = शून्य;
/* machine dependent irq functions */
व्योम (*mach_init_IRQ) (व्योम) __initdata = शून्य;
व्योम (*mach_get_model) (अक्षर *model);
व्योम (*mach_get_hardware_list) (काष्ठा seq_file *m);
/* machine dependent समयr functions */
पूर्णांक (*mach_hwclk) (पूर्णांक, काष्ठा rtc_समय*);
EXPORT_SYMBOL(mach_hwclk);
अचिन्हित पूर्णांक (*mach_get_ss)(व्योम);
पूर्णांक (*mach_get_rtc_pll)(काष्ठा rtc_pll_info *);
पूर्णांक (*mach_set_rtc_pll)(काष्ठा rtc_pll_info *);
EXPORT_SYMBOL(mach_get_ss);
EXPORT_SYMBOL(mach_get_rtc_pll);
EXPORT_SYMBOL(mach_set_rtc_pll);
व्योम (*mach_reset)( व्योम );
व्योम (*mach_halt)( व्योम );
व्योम (*mach_घातer_off)( व्योम );
#अगर_घोषित CONFIG_HEARTBEAT
व्योम (*mach_heartbeat) (पूर्णांक);
EXPORT_SYMBOL(mach_heartbeat);
#पूर्ण_अगर
#अगर_घोषित CONFIG_M68K_L2_CACHE
व्योम (*mach_l2_flush) (पूर्णांक);
#पूर्ण_अगर
#अगर defined(CONFIG_ISA) && defined(MULTI_ISA)
पूर्णांक isa_type;
पूर्णांक isa_sex;
EXPORT_SYMBOL(isa_type);
EXPORT_SYMBOL(isa_sex);
#पूर्ण_अगर

बाह्य पूर्णांक amiga_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक atari_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक mac_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक q40_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक bvme6000_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक mvme16x_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक mvme147_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक hp300_parse_bootinfo(स्थिर काष्ठा bi_record *);
बाह्य पूर्णांक apollo_parse_bootinfo(स्थिर काष्ठा bi_record *);

बाह्य व्योम config_amiga(व्योम);
बाह्य व्योम config_atari(व्योम);
बाह्य व्योम config_mac(व्योम);
बाह्य व्योम config_sun3(व्योम);
बाह्य व्योम config_apollo(व्योम);
बाह्य व्योम config_mvme147(व्योम);
बाह्य व्योम config_mvme16x(व्योम);
बाह्य व्योम config_bvme6000(व्योम);
बाह्य व्योम config_hp300(व्योम);
बाह्य व्योम config_q40(व्योम);
बाह्य व्योम config_sun3x(व्योम);

#घोषणा MASK_256K 0xfffc0000

बाह्य व्योम paging_init(व्योम);

अटल व्योम __init m68k_parse_bootinfo(स्थिर काष्ठा bi_record *record)
अणु
	uपूर्णांक16_t tag;

	save_bootinfo(record);

	जबतक ((tag = be16_to_cpu(record->tag)) != BI_LAST) अणु
		पूर्णांक unknown = 0;
		स्थिर व्योम *data = record->data;
		uपूर्णांक16_t size = be16_to_cpu(record->size);

		चयन (tag) अणु
		हाल BI_MACHTYPE:
		हाल BI_CPUTYPE:
		हाल BI_FPUTYPE:
		हाल BI_MMUTYPE:
			/* Alपढ़ोy set up by head.S */
			अवरोध;

		हाल BI_MEMCHUNK:
			अगर (m68k_num_memory < NUM_MEMINFO) अणु
				स्थिर काष्ठा mem_info *m = data;
				m68k_memory[m68k_num_memory].addr =
					be32_to_cpu(m->addr);
				m68k_memory[m68k_num_memory].size =
					be32_to_cpu(m->size);
				m68k_num_memory++;
			पूर्ण अन्यथा
				pr_warn("%s: too many memory chunks\n",
					__func__);
			अवरोध;

		हाल BI_RAMDISK:
			अणु
				स्थिर काष्ठा mem_info *m = data;
				m68k_ramdisk.addr = be32_to_cpu(m->addr);
				m68k_ramdisk.size = be32_to_cpu(m->size);
			पूर्ण
			अवरोध;

		हाल BI_COMMAND_LINE:
			strlcpy(m68k_command_line, data,
				माप(m68k_command_line));
			अवरोध;

		शेष:
			अगर (MACH_IS_AMIGA)
				unknown = amiga_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_ATARI)
				unknown = atari_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_MAC)
				unknown = mac_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_Q40)
				unknown = q40_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_BVME6000)
				unknown = bvme6000_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_MVME16x)
				unknown = mvme16x_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_MVME147)
				unknown = mvme147_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_HP300)
				unknown = hp300_parse_bootinfo(record);
			अन्यथा अगर (MACH_IS_APOLLO)
				unknown = apollo_parse_bootinfo(record);
			अन्यथा
				unknown = 1;
		पूर्ण
		अगर (unknown)
			pr_warn("%s: unknown tag 0x%04x ignored\n", __func__,
				tag);
		record = (काष्ठा bi_record *)((अचिन्हित दीर्घ)record + size);
	पूर्ण

	m68k_realnum_memory = m68k_num_memory;
#अगर_घोषित CONFIG_SINGLE_MEMORY_CHUNK
	अगर (m68k_num_memory > 1) अणु
		pr_warn("%s: ignoring last %i chunks of physical memory\n",
			__func__, (m68k_num_memory - 1));
		m68k_num_memory = 1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	/* The bootinfo is located right after the kernel */
	अगर (!CPU_IS_COLDFIRE)
		m68k_parse_bootinfo((स्थिर काष्ठा bi_record *)_end);

	अगर (CPU_IS_040)
		m68k_is040or060 = 4;
	अन्यथा अगर (CPU_IS_060)
		m68k_is040or060 = 6;

	/* FIXME: m68k_fputype is passed in by Penguin booter, which can
	 * be confused by software FPU emulation. BEWARE.
	 * We should really करो our own FPU check at startup.
	 * [what करो we करो with buggy 68LC040s? अगर we have problems
	 *  with them, we should add a test to check_bugs() below] */
#अगर defined(CONFIG_FPU) && !defined(CONFIG_M68KFPU_EMU_ONLY)
	/* clear the fpu अगर we have one */
	अगर (m68k_fputype & (FPU_68881|FPU_68882|FPU_68040|FPU_68060|FPU_COLDFIRE)) अणु
		अस्थिर पूर्णांक zero = 0;
		यंत्र अस्थिर ("frestore %0" : : "m" (zero));
	पूर्ण
#पूर्ण_अगर

	अगर (CPU_IS_060) अणु
		u32 pcr;

		यंत्र (".chip 68060; movec %%pcr,%0; .chip 68k"
		     : "=d" (pcr));
		अगर (((pcr >> 8) & 0xff) <= 5) अणु
			pr_warn("Enabling workaround for errata I14\n");
			यंत्र (".chip 68060; movec %0,%%pcr; .chip 68k"
			     : : "d" (pcr | 0x20));
		पूर्ण
	पूर्ण

	init_mm.start_code = PAGE_OFFSET;
	init_mm.end_code = (अचिन्हित दीर्घ)_etext;
	init_mm.end_data = (अचिन्हित दीर्घ)_edata;
	init_mm.brk = (अचिन्हित दीर्घ)_end;

#अगर defined(CONFIG_BOOTPARAM)
	म_नकलन(m68k_command_line, CONFIG_BOOTPARAM_STRING, CL_SIZE);
	m68k_command_line[CL_SIZE - 1] = 0;
#पूर्ण_अगर /* CONFIG_BOOTPARAM */
	process_uboot_commandline(&m68k_command_line[0], CL_SIZE);
	*cmdline_p = m68k_command_line;
	स_नकल(boot_command_line, *cmdline_p, CL_SIZE);

	parse_early_param();

	चयन (m68k_machtype) अणु
#अगर_घोषित CONFIG_AMIGA
	हाल MACH_AMIGA:
		config_amiga();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI
	हाल MACH_ATARI:
		config_atari();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAC
	हाल MACH_MAC:
		config_mac();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN3
	हाल MACH_SUN3:
		config_sun3();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_APOLLO
	हाल MACH_APOLLO:
		config_apollo();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MVME147
	हाल MACH_MVME147:
		config_mvme147();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MVME16x
	हाल MACH_MVME16x:
		config_mvme16x();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BVME6000
	हाल MACH_BVME6000:
		config_bvme6000();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HP300
	हाल MACH_HP300:
		config_hp300();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_Q40
	हाल MACH_Q40:
		config_q40();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN3X
	हाल MACH_SUN3X:
		config_sun3x();
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_COLDFIRE
	हाल MACH_M54XX:
	हाल MACH_M5441X:
		cf_booपंचांगem_alloc();
		cf_mmu_context_init();
		config_BSP(शून्य, 0);
		अवरोध;
#पूर्ण_अगर
	शेष:
		panic("No configuration setup");
	पूर्ण

	paging_init();

#अगर_घोषित CONFIG_NATFEAT
	nf_init();
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SUN3
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (m68k_ramdisk.size) अणु
		memblock_reserve(m68k_ramdisk.addr, m68k_ramdisk.size);
		initrd_start = (अचिन्हित दीर्घ)phys_to_virt(m68k_ramdisk.addr);
		initrd_end = initrd_start + m68k_ramdisk.size;
		pr_info("initrd: %08lx - %08lx\n", initrd_start, initrd_end);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATARI
	अगर (MACH_IS_ATARI)
		atari_stram_reserve_pages((व्योम *)availmem);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN3X
	अगर (MACH_IS_SUN3X) अणु
		dvma_init();
	पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* !CONFIG_SUN3 */

/* set ISA defs early as possible */
#अगर defined(CONFIG_ISA) && defined(MULTI_ISA)
	अगर (MACH_IS_Q40) अणु
		isa_type = ISA_TYPE_Q40;
		isa_sex = 0;
	पूर्ण
#अगर_घोषित CONFIG_AMIGA_PCMCIA
	अगर (MACH_IS_AMIGA && AMIGAHW_PRESENT(PCMCIA)) अणु
		isa_type = ISA_TYPE_AG;
		isa_sex = 1;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_ROM_ISA
	अगर (MACH_IS_ATARI) अणु
		isa_type = ISA_TYPE_ENEC;
		isa_sex = 0;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर अक्षर *cpu, *mmu, *fpu;
	अचिन्हित दीर्घ घड़ीfreq, घड़ीfactor;

#घोषणा LOOP_CYCLES_68020	(8)
#घोषणा LOOP_CYCLES_68030	(8)
#घोषणा LOOP_CYCLES_68040	(3)
#घोषणा LOOP_CYCLES_68060	(1)
#घोषणा LOOP_CYCLES_COLDFIRE	(2)

	अगर (CPU_IS_020) अणु
		cpu = "68020";
		घड़ीfactor = LOOP_CYCLES_68020;
	पूर्ण अन्यथा अगर (CPU_IS_030) अणु
		cpu = "68030";
		घड़ीfactor = LOOP_CYCLES_68030;
	पूर्ण अन्यथा अगर (CPU_IS_040) अणु
		cpu = "68040";
		घड़ीfactor = LOOP_CYCLES_68040;
	पूर्ण अन्यथा अगर (CPU_IS_060) अणु
		cpu = "68060";
		घड़ीfactor = LOOP_CYCLES_68060;
	पूर्ण अन्यथा अगर (CPU_IS_COLDFIRE) अणु
		cpu = "ColdFire";
		घड़ीfactor = LOOP_CYCLES_COLDFIRE;
	पूर्ण अन्यथा अणु
		cpu = "680x0";
		घड़ीfactor = 0;
	पूर्ण

#अगर_घोषित CONFIG_M68KFPU_EMU_ONLY
	fpu = "none(soft float)";
#अन्यथा
	अगर (m68k_fputype & FPU_68881)
		fpu = "68881";
	अन्यथा अगर (m68k_fputype & FPU_68882)
		fpu = "68882";
	अन्यथा अगर (m68k_fputype & FPU_68040)
		fpu = "68040";
	अन्यथा अगर (m68k_fputype & FPU_68060)
		fpu = "68060";
	अन्यथा अगर (m68k_fputype & FPU_SUNFPA)
		fpu = "Sun FPA";
	अन्यथा अगर (m68k_fputype & FPU_COLDFIRE)
		fpu = "ColdFire";
	अन्यथा
		fpu = "none";
#पूर्ण_अगर

	अगर (m68k_mmutype & MMU_68851)
		mmu = "68851";
	अन्यथा अगर (m68k_mmutype & MMU_68030)
		mmu = "68030";
	अन्यथा अगर (m68k_mmutype & MMU_68040)
		mmu = "68040";
	अन्यथा अगर (m68k_mmutype & MMU_68060)
		mmu = "68060";
	अन्यथा अगर (m68k_mmutype & MMU_SUN3)
		mmu = "Sun-3";
	अन्यथा अगर (m68k_mmutype & MMU_APOLLO)
		mmu = "Apollo";
	अन्यथा अगर (m68k_mmutype & MMU_COLDFIRE)
		mmu = "ColdFire";
	अन्यथा
		mmu = "unknown";

	घड़ीfreq = loops_per_jअगरfy * HZ * घड़ीfactor;

	seq_म_लिखो(m, "CPU:\t\t%s\n"
		   "MMU:\t\t%s\n"
		   "FPU:\t\t%s\n"
		   "Clocking:\t%lu.%1luMHz\n"
		   "BogoMips:\t%lu.%02lu\n"
		   "Calibration:\t%lu loops\n",
		   cpu, mmu, fpu,
		   घड़ीfreq/1000000,(घड़ीfreq/100000)%10,
		   loops_per_jअगरfy/(500000/HZ),(loops_per_jअगरfy/(5000/HZ))%100,
		   loops_per_jअगरfy);
	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < 1 ? (व्योम *)1 : शून्य;
पूर्ण
अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस शून्य;
पूर्ण
अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण
स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;

#अगर_घोषित CONFIG_PROC_HARDWARE
अटल पूर्णांक hardware_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर model[80];
	अचिन्हित दीर्घ mem;
	पूर्णांक i;

	अगर (mach_get_model)
		mach_get_model(model);
	अन्यथा
		म_नकल(model, "Unknown m68k");

	seq_म_लिखो(m, "Model:\t\t%s\n", model);
	क्रम (mem = 0, i = 0; i < m68k_num_memory; i++)
		mem += m68k_memory[i].size;
	seq_म_लिखो(m, "System Memory:\t%ldK\n", mem >> 10);

	अगर (mach_get_hardware_list)
		mach_get_hardware_list(m);

	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_hardware_init(व्योम)
अणु
	proc_create_single("hardware", 0, शून्य, hardware_proc_show);
	वापस 0;
पूर्ण
module_init(proc_hardware_init);
#पूर्ण_अगर

व्योम check_bugs(व्योम)
अणु
#अगर defined(CONFIG_FPU) && !defined(CONFIG_M68KFPU_EMU)
	अगर (m68k_fputype == 0) अणु
		pr_emerg("*** YOU DO NOT HAVE A FLOATING POINT UNIT, "
			"WHICH IS REQUIRED BY LINUX/M68K ***\n");
		pr_emerg("Upgrade your hardware or join the FPU "
			"emulation project\n");
		panic("no FPU");
	पूर्ण
#पूर्ण_अगर /* !CONFIG_M68KFPU_EMU */
पूर्ण

#अगर_घोषित CONFIG_ADB
अटल पूर्णांक __init adb_probe_sync_enable (अक्षर *str) अणु
	बाह्य पूर्णांक __adb_probe_sync;
	__adb_probe_sync = 1;
	वापस 1;
पूर्ण

__setup("adb_sync", adb_probe_sync_enable);
#पूर्ण_अगर /* CONFIG_ADB */

#अगर IS_ENABLED(CONFIG_NVRAM)
#अगर_घोषित CONFIG_MAC
अटल अचिन्हित अक्षर m68k_nvram_पढ़ो_byte(पूर्णांक addr)
अणु
	अगर (MACH_IS_MAC)
		वापस mac_pram_पढ़ो_byte(addr);
	वापस 0xff;
पूर्ण

अटल व्योम m68k_nvram_ग_लिखो_byte(अचिन्हित अक्षर val, पूर्णांक addr)
अणु
	अगर (MACH_IS_MAC)
		mac_pram_ग_लिखो_byte(val, addr);
पूर्ण
#पूर्ण_अगर /* CONFIG_MAC */

#अगर_घोषित CONFIG_ATARI
अटल sमाप_प्रकार m68k_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अगर (MACH_IS_ATARI)
		वापस atari_nvram_पढ़ो(buf, count, ppos);
	अन्यथा अगर (MACH_IS_MAC)
		वापस nvram_पढ़ो_bytes(buf, count, ppos);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार m68k_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अगर (MACH_IS_ATARI)
		वापस atari_nvram_ग_लिखो(buf, count, ppos);
	अन्यथा अगर (MACH_IS_MAC)
		वापस nvram_ग_लिखो_bytes(buf, count, ppos);
	वापस -EINVAL;
पूर्ण

अटल दीर्घ m68k_nvram_set_checksum(व्योम)
अणु
	अगर (MACH_IS_ATARI)
		वापस atari_nvram_set_checksum();
	वापस -EINVAL;
पूर्ण

अटल दीर्घ m68k_nvram_initialize(व्योम)
अणु
	अगर (MACH_IS_ATARI)
		वापस atari_nvram_initialize();
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATARI */

अटल sमाप_प्रकार m68k_nvram_get_size(व्योम)
अणु
	अगर (MACH_IS_ATARI)
		वापस atari_nvram_get_size();
	अन्यथा अगर (MACH_IS_MAC)
		वापस mac_pram_get_size();
	वापस -ENODEV;
पूर्ण

/* Atari device drivers call .पढ़ो (to get checksum validation) whereas
 * Mac and PowerMac device drivers just use .पढ़ो_byte.
 */
स्थिर काष्ठा nvram_ops arch_nvram_ops = अणु
#अगर_घोषित CONFIG_MAC
	.पढ़ो_byte      = m68k_nvram_पढ़ो_byte,
	.ग_लिखो_byte     = m68k_nvram_ग_लिखो_byte,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI
	.पढ़ो           = m68k_nvram_पढ़ो,
	.ग_लिखो          = m68k_nvram_ग_लिखो,
	.set_checksum   = m68k_nvram_set_checksum,
	.initialize     = m68k_nvram_initialize,
#पूर्ण_अगर
	.get_size       = m68k_nvram_get_size,
पूर्ण;
EXPORT_SYMBOL(arch_nvram_ops);
#पूर्ण_अगर /* CONFIG_NVRAM */
