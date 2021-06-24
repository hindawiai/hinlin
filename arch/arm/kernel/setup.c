<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/setup.c
 *
 *  Copyright (C) 1995-2001 Russell King
 */
#समावेश <linux/efi.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/utsname.h>
#समावेश <linux/initrd.h>
#समावेश <linux/console.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/init.h>
#समावेश <linux/kexec.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/memblock.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/sort.h>
#समावेश <linux/psci.h>

#समावेश <यंत्र/unअगरied.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/procinfo.h>
#समावेश <यंत्र/psci.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/memblock.h>
#समावेश <यंत्र/virt.h>
#समावेश <यंत्र/kasan.h>

#समावेश "atags.h"


#अगर defined(CONFIG_FPE_NWFPE) || defined(CONFIG_FPE_FASTFPE)
अक्षर fpe_type[8];

अटल पूर्णांक __init fpe_setup(अक्षर *line)
अणु
	स_नकल(fpe_type, line, 8);
	वापस 1;
पूर्ण

__setup("fpe=", fpe_setup);
#पूर्ण_अगर

बाह्य व्योम init_शेष_cache_policy(अचिन्हित दीर्घ);
बाह्य व्योम paging_init(स्थिर काष्ठा machine_desc *desc);
बाह्य व्योम early_mm_init(स्थिर काष्ठा machine_desc *);
बाह्य व्योम adjust_lowmem_bounds(व्योम);
बाह्य क्रमागत reboot_mode reboot_mode;
बाह्य व्योम setup_dma_zone(स्थिर काष्ठा machine_desc *desc);

अचिन्हित पूर्णांक processor_id;
EXPORT_SYMBOL(processor_id);
अचिन्हित पूर्णांक __machine_arch_type __पढ़ो_mostly;
EXPORT_SYMBOL(__machine_arch_type);
अचिन्हित पूर्णांक cacheid __पढ़ो_mostly;
EXPORT_SYMBOL(cacheid);

अचिन्हित पूर्णांक __atags_poपूर्णांकer __initdata;

अचिन्हित पूर्णांक प्रणाली_rev;
EXPORT_SYMBOL(प्रणाली_rev);

स्थिर अक्षर *प्रणाली_serial;
EXPORT_SYMBOL(प्रणाली_serial);

अचिन्हित पूर्णांक प्रणाली_serial_low;
EXPORT_SYMBOL(प्रणाली_serial_low);

अचिन्हित पूर्णांक प्रणाली_serial_high;
EXPORT_SYMBOL(प्रणाली_serial_high);

अचिन्हित पूर्णांक elf_hwcap __पढ़ो_mostly;
EXPORT_SYMBOL(elf_hwcap);

अचिन्हित पूर्णांक elf_hwcap2 __पढ़ो_mostly;
EXPORT_SYMBOL(elf_hwcap2);


#अगर_घोषित MULTI_CPU
काष्ठा processor processor __ro_after_init;
#अगर defined(CONFIG_BIG_LITTLE) && defined(CONFIG_HARDEN_BRANCH_PREDICTOR)
काष्ठा processor *cpu_vtable[NR_CPUS] = अणु
	[0] = &processor,
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित MULTI_TLB
काष्ठा cpu_tlb_fns cpu_tlb __ro_after_init;
#पूर्ण_अगर
#अगर_घोषित MULTI_USER
काष्ठा cpu_user_fns cpu_user __ro_after_init;
#पूर्ण_अगर
#अगर_घोषित MULTI_CACHE
काष्ठा cpu_cache_fns cpu_cache __ro_after_init;
#पूर्ण_अगर
#अगर_घोषित CONFIG_OUTER_CACHE
काष्ठा outer_cache_fns outer_cache __ro_after_init;
EXPORT_SYMBOL(outer_cache);
#पूर्ण_अगर

/*
 * Cached cpu_architecture() result क्रम use by assembler code.
 * C code should use the cpu_architecture() function instead of accessing this
 * variable directly.
 */
पूर्णांक __cpu_architecture __पढ़ो_mostly = CPU_ARCH_UNKNOWN;

काष्ठा stack अणु
	u32 irq[3];
	u32 abt[3];
	u32 und[3];
	u32 fiq[3];
पूर्ण ____cacheline_aligned;

#अगर_अघोषित CONFIG_CPU_V7M
अटल काष्ठा stack stacks[NR_CPUS];
#पूर्ण_अगर

अक्षर elf_platक्रमm[ELF_PLATFORM_SIZE];
EXPORT_SYMBOL(elf_platक्रमm);

अटल स्थिर अक्षर *cpu_name;
अटल स्थिर अक्षर *machine_name;
अटल अक्षर __initdata cmd_line[COMMAND_LINE_SIZE];
स्थिर काष्ठा machine_desc *machine_desc __initdata;

अटल जोड़ अणु अक्षर c[4]; अचिन्हित दीर्घ l; पूर्ण endian_test __initdata = अणु अणु 'l', '?', '?', 'b' पूर्ण पूर्ण;
#घोषणा ENDIANNESS ((अक्षर)endian_test.l)

DEFINE_PER_CPU(काष्ठा cpuinfo_arm, cpu_data);

/*
 * Standard memory resources
 */
अटल काष्ठा resource mem_res[] = अणु
	अणु
		.name = "Video RAM",
		.start = 0,
		.end = 0,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.name = "Kernel code",
		.start = 0,
		.end = 0,
		.flags = IORESOURCE_SYSTEM_RAM
	पूर्ण,
	अणु
		.name = "Kernel data",
		.start = 0,
		.end = 0,
		.flags = IORESOURCE_SYSTEM_RAM
	पूर्ण
पूर्ण;

#घोषणा video_ram   mem_res[0]
#घोषणा kernel_code mem_res[1]
#घोषणा kernel_data mem_res[2]

अटल काष्ठा resource io_res[] = अणु
	अणु
		.name = "reserved",
		.start = 0x3bc,
		.end = 0x3be,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
	अणु
		.name = "reserved",
		.start = 0x378,
		.end = 0x37f,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
	अणु
		.name = "reserved",
		.start = 0x278,
		.end = 0x27f,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण
पूर्ण;

#घोषणा lp0 io_res[0]
#घोषणा lp1 io_res[1]
#घोषणा lp2 io_res[2]

अटल स्थिर अक्षर *proc_arch[] = अणु
	"undefined/unknown",
	"3",
	"4",
	"4T",
	"5",
	"5T",
	"5TE",
	"5TEJ",
	"6TEJ",
	"7",
	"7M",
	"?(12)",
	"?(13)",
	"?(14)",
	"?(15)",
	"?(16)",
	"?(17)",
पूर्ण;

#अगर_घोषित CONFIG_CPU_V7M
अटल पूर्णांक __get_cpu_architecture(व्योम)
अणु
	वापस CPU_ARCH_ARMv7M;
पूर्ण
#अन्यथा
अटल पूर्णांक __get_cpu_architecture(व्योम)
अणु
	पूर्णांक cpu_arch;

	अगर ((पढ़ो_cpuid_id() & 0x0008f000) == 0) अणु
		cpu_arch = CPU_ARCH_UNKNOWN;
	पूर्ण अन्यथा अगर ((पढ़ो_cpuid_id() & 0x0008f000) == 0x00007000) अणु
		cpu_arch = (पढ़ो_cpuid_id() & (1 << 23)) ? CPU_ARCH_ARMv4T : CPU_ARCH_ARMv3;
	पूर्ण अन्यथा अगर ((पढ़ो_cpuid_id() & 0x00080000) == 0x00000000) अणु
		cpu_arch = (पढ़ो_cpuid_id() >> 16) & 7;
		अगर (cpu_arch)
			cpu_arch += CPU_ARCH_ARMv3;
	पूर्ण अन्यथा अगर ((पढ़ो_cpuid_id() & 0x000f0000) == 0x000f0000) अणु
		/* Revised CPUID क्रमmat. Read the Memory Model Feature
		 * Register 0 and check क्रम VMSAv7 or PMSAv7 */
		अचिन्हित पूर्णांक mmfr0 = पढ़ो_cpuid_ext(CPUID_EXT_MMFR0);
		अगर ((mmfr0 & 0x0000000f) >= 0x00000003 ||
		    (mmfr0 & 0x000000f0) >= 0x00000030)
			cpu_arch = CPU_ARCH_ARMv7;
		अन्यथा अगर ((mmfr0 & 0x0000000f) == 0x00000002 ||
			 (mmfr0 & 0x000000f0) == 0x00000020)
			cpu_arch = CPU_ARCH_ARMv6;
		अन्यथा
			cpu_arch = CPU_ARCH_UNKNOWN;
	पूर्ण अन्यथा
		cpu_arch = CPU_ARCH_UNKNOWN;

	वापस cpu_arch;
पूर्ण
#पूर्ण_अगर

पूर्णांक __pure cpu_architecture(व्योम)
अणु
	BUG_ON(__cpu_architecture == CPU_ARCH_UNKNOWN);

	वापस __cpu_architecture;
पूर्ण

अटल पूर्णांक cpu_has_aliasing_icache(अचिन्हित पूर्णांक arch)
अणु
	पूर्णांक aliasing_icache;
	अचिन्हित पूर्णांक id_reg, num_sets, line_size;

	/* PIPT caches never alias. */
	अगर (icache_is_pipt())
		वापस 0;

	/* arch specअगरies the रेजिस्टर क्रमmat */
	चयन (arch) अणु
	हाल CPU_ARCH_ARMv7:
		set_csselr(CSSELR_ICACHE | CSSELR_L1);
		isb();
		id_reg = पढ़ो_ccsidr();
		line_size = 4 << ((id_reg & 0x7) + 2);
		num_sets = ((id_reg >> 13) & 0x7fff) + 1;
		aliasing_icache = (line_size * num_sets) > PAGE_SIZE;
		अवरोध;
	हाल CPU_ARCH_ARMv6:
		aliasing_icache = पढ़ो_cpuid_cachetype() & (1 << 11);
		अवरोध;
	शेष:
		/* I-cache aliases will be handled by D-cache aliasing code */
		aliasing_icache = 0;
	पूर्ण

	वापस aliasing_icache;
पूर्ण

अटल व्योम __init cacheid_init(व्योम)
अणु
	अचिन्हित पूर्णांक arch = cpu_architecture();

	अगर (arch >= CPU_ARCH_ARMv6) अणु
		अचिन्हित पूर्णांक cachetype = पढ़ो_cpuid_cachetype();

		अगर ((arch == CPU_ARCH_ARMv7M) && !(cachetype & 0xf000f)) अणु
			cacheid = 0;
		पूर्ण अन्यथा अगर ((cachetype & (7 << 29)) == 4 << 29) अणु
			/* ARMv7 रेजिस्टर क्रमmat */
			arch = CPU_ARCH_ARMv7;
			cacheid = CACHEID_VIPT_NONALIASING;
			चयन (cachetype & (3 << 14)) अणु
			हाल (1 << 14):
				cacheid |= CACHEID_ASID_TAGGED;
				अवरोध;
			हाल (3 << 14):
				cacheid |= CACHEID_PIPT;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			arch = CPU_ARCH_ARMv6;
			अगर (cachetype & (1 << 23))
				cacheid = CACHEID_VIPT_ALIASING;
			अन्यथा
				cacheid = CACHEID_VIPT_NONALIASING;
		पूर्ण
		अगर (cpu_has_aliasing_icache(arch))
			cacheid |= CACHEID_VIPT_I_ALIASING;
	पूर्ण अन्यथा अणु
		cacheid = CACHEID_VIVT;
	पूर्ण

	pr_info("CPU: %s data cache, %s instruction cache\n",
		cache_is_vivt() ? "VIVT" :
		cache_is_vipt_aliasing() ? "VIPT aliasing" :
		cache_is_vipt_nonaliasing() ? "PIPT / VIPT nonaliasing" : "unknown",
		cache_is_vivt() ? "VIVT" :
		icache_is_vivt_asid_tagged() ? "VIVT ASID tagged" :
		icache_is_vipt_aliasing() ? "VIPT aliasing" :
		icache_is_pipt() ? "PIPT" :
		cache_is_vipt_nonaliasing() ? "VIPT nonaliasing" : "unknown");
पूर्ण

/*
 * These functions re-use the assembly code in head.S, which
 * alपढ़ोy provide the required functionality.
 */
बाह्य काष्ठा proc_info_list *lookup_processor_type(अचिन्हित पूर्णांक);

व्योम __init early_prपूर्णांक(स्थिर अक्षर *str, ...)
अणु
	बाह्य व्योम prपूर्णांकascii(स्थिर अक्षर *);
	अक्षर buf[256];
	बहु_सूची ap;

	बहु_शुरू(ap, str);
	vsnम_लिखो(buf, माप(buf), str, ap);
	बहु_पूर्ण(ap);

#अगर_घोषित CONFIG_DEBUG_LL
	prपूर्णांकascii(buf);
#पूर्ण_अगर
	prपूर्णांकk("%s", buf);
पूर्ण

#अगर_घोषित CONFIG_ARM_PATCH_IDIV

अटल अंतरभूत u32 __attribute_स्थिर__ sभाग_inकाष्ठाion(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_THUMB2_KERNEL)) अणु
		/* "sdiv r0, r0, r1" */
		u32 insn = __opcode_thumb32_compose(0xfb90, 0xf0f1);
		वापस __opcode_to_mem_thumb32(insn);
	पूर्ण

	/* "sdiv r0, r0, r1" */
	वापस __opcode_to_mem_arm(0xe710f110);
पूर्ण

अटल अंतरभूत u32 __attribute_स्थिर__ uभाग_inकाष्ठाion(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_THUMB2_KERNEL)) अणु
		/* "udiv r0, r0, r1" */
		u32 insn = __opcode_thumb32_compose(0xfbb0, 0xf0f1);
		वापस __opcode_to_mem_thumb32(insn);
	पूर्ण

	/* "udiv r0, r0, r1" */
	वापस __opcode_to_mem_arm(0xe730f110);
पूर्ण

अटल अंतरभूत u32 __attribute_स्थिर__ bx_lr_inकाष्ठाion(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_THUMB2_KERNEL)) अणु
		/* "bx lr; nop" */
		u32 insn = __opcode_thumb32_compose(0x4770, 0x46c0);
		वापस __opcode_to_mem_thumb32(insn);
	पूर्ण

	/* "bx lr" */
	वापस __opcode_to_mem_arm(0xe12fff1e);
पूर्ण

अटल व्योम __init patch_aeabi_iभाग(व्योम)
अणु
	बाह्य व्योम __aeabi_uiभाग(व्योम);
	बाह्य व्योम __aeabi_iभाग(व्योम);
	uपूर्णांकptr_t fn_addr;
	अचिन्हित पूर्णांक mask;

	mask = IS_ENABLED(CONFIG_THUMB2_KERNEL) ? HWCAP_IDIVT : HWCAP_IDIVA;
	अगर (!(elf_hwcap & mask))
		वापस;

	pr_info("CPU: div instructions available: patching division code\n");

	fn_addr = ((uपूर्णांकptr_t)&__aeabi_uiभाग) & ~1;
	यंत्र ("" : "+g" (fn_addr));
	((u32 *)fn_addr)[0] = uभाग_inकाष्ठाion();
	((u32 *)fn_addr)[1] = bx_lr_inकाष्ठाion();
	flush_icache_range(fn_addr, fn_addr + 8);

	fn_addr = ((uपूर्णांकptr_t)&__aeabi_iभाग) & ~1;
	यंत्र ("" : "+g" (fn_addr));
	((u32 *)fn_addr)[0] = sभाग_inकाष्ठाion();
	((u32 *)fn_addr)[1] = bx_lr_inकाष्ठाion();
	flush_icache_range(fn_addr, fn_addr + 8);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम patch_aeabi_iभाग(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __init cpuid_init_hwcaps(व्योम)
अणु
	पूर्णांक block;
	u32 isar5;

	अगर (cpu_architecture() < CPU_ARCH_ARMv7)
		वापस;

	block = cpuid_feature_extract(CPUID_EXT_ISAR0, 24);
	अगर (block >= 2)
		elf_hwcap |= HWCAP_IDIVA;
	अगर (block >= 1)
		elf_hwcap |= HWCAP_IDIVT;

	/* LPAE implies atomic ldrd/strd inकाष्ठाions */
	block = cpuid_feature_extract(CPUID_EXT_MMFR0, 0);
	अगर (block >= 5)
		elf_hwcap |= HWCAP_LPAE;

	/* check क्रम supported v8 Crypto inकाष्ठाions */
	isar5 = पढ़ो_cpuid_ext(CPUID_EXT_ISAR5);

	block = cpuid_feature_extract_field(isar5, 4);
	अगर (block >= 2)
		elf_hwcap2 |= HWCAP2_PMULL;
	अगर (block >= 1)
		elf_hwcap2 |= HWCAP2_AES;

	block = cpuid_feature_extract_field(isar5, 8);
	अगर (block >= 1)
		elf_hwcap2 |= HWCAP2_SHA1;

	block = cpuid_feature_extract_field(isar5, 12);
	अगर (block >= 1)
		elf_hwcap2 |= HWCAP2_SHA2;

	block = cpuid_feature_extract_field(isar5, 16);
	अगर (block >= 1)
		elf_hwcap2 |= HWCAP2_CRC32;
पूर्ण

अटल व्योम __init elf_hwcap_fixup(व्योम)
अणु
	अचिन्हित id = पढ़ो_cpuid_id();

	/*
	 * HWCAP_TLS is available only on 1136 r1p0 and later,
	 * see also kuser_get_tls_init.
	 */
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_ARM1136 &&
	    ((id >> 20) & 3) == 0) अणु
		elf_hwcap &= ~HWCAP_TLS;
		वापस;
	पूर्ण

	/* Verअगरy अगर CPUID scheme is implemented */
	अगर ((id & 0x000f0000) != 0x000f0000)
		वापस;

	/*
	 * If the CPU supports LDREX/STREX and LDREXB/STREXB,
	 * aव्योम advertising SWP; it may not be atomic with
	 * multiprocessing cores.
	 */
	अगर (cpuid_feature_extract(CPUID_EXT_ISAR3, 12) > 1 ||
	    (cpuid_feature_extract(CPUID_EXT_ISAR3, 12) == 1 &&
	     cpuid_feature_extract(CPUID_EXT_ISAR4, 20) >= 3))
		elf_hwcap &= ~HWCAP_SWP;
पूर्ण

/*
 * cpu_init - initialise one CPU.
 *
 * cpu_init sets up the per-CPU stacks.
 */
व्योम notrace cpu_init(व्योम)
अणु
#अगर_अघोषित CONFIG_CPU_V7M
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा stack *stk = &stacks[cpu];

	अगर (cpu >= NR_CPUS) अणु
		pr_crit("CPU%u: bad primary CPU number\n", cpu);
		BUG();
	पूर्ण

	/*
	 * This only works on resume and secondary cores. For booting on the
	 * boot cpu, smp_prepare_boot_cpu is called after percpu area setup.
	 */
	set_my_cpu_offset(per_cpu_offset(cpu));

	cpu_proc_init();

	/*
	 * Define the placement स्थिरraपूर्णांक क्रम the अंतरभूत यंत्र directive below.
	 * In Thumb-2, msr with an immediate value is not allowed.
	 */
#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा PLC_l	"l"
#घोषणा PLC_r	"r"
#अन्यथा
#घोषणा PLC_l	"I"
#घोषणा PLC_r	"I"
#पूर्ण_अगर

	/*
	 * setup stacks क्रम re-entrant exception handlers
	 */
	__यंत्र__ (
	"msr	cpsr_c, %1\n\t"
	"add	r14, %0, %2\n\t"
	"mov	sp, r14\n\t"
	"msr	cpsr_c, %3\n\t"
	"add	r14, %0, %4\n\t"
	"mov	sp, r14\n\t"
	"msr	cpsr_c, %5\n\t"
	"add	r14, %0, %6\n\t"
	"mov	sp, r14\n\t"
	"msr	cpsr_c, %7\n\t"
	"add	r14, %0, %8\n\t"
	"mov	sp, r14\n\t"
	"msr	cpsr_c, %9"
	    :
	    : "r" (stk),
	      PLC_r (PSR_F_BIT | PSR_I_BIT | IRQ_MODE),
	      "I" (दुरत्व(काष्ठा stack, irq[0])),
	      PLC_r (PSR_F_BIT | PSR_I_BIT | ABT_MODE),
	      "I" (दुरत्व(काष्ठा stack, abt[0])),
	      PLC_r (PSR_F_BIT | PSR_I_BIT | UND_MODE),
	      "I" (दुरत्व(काष्ठा stack, und[0])),
	      PLC_r (PSR_F_BIT | PSR_I_BIT | FIQ_MODE),
	      "I" (दुरत्व(काष्ठा stack, fiq[0])),
	      PLC_l (PSR_F_BIT | PSR_I_BIT | SVC_MODE)
	    : "r14");
#पूर्ण_अगर
पूर्ण

u32 __cpu_logical_map[NR_CPUS] = अणु [0 ... NR_CPUS-1] = MPIDR_INVALID पूर्ण;

व्योम __init smp_setup_processor_id(व्योम)
अणु
	पूर्णांक i;
	u32 mpidr = is_smp() ? पढ़ो_cpuid_mpidr() & MPIDR_HWID_BITMASK : 0;
	u32 cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	cpu_logical_map(0) = cpu;
	क्रम (i = 1; i < nr_cpu_ids; ++i)
		cpu_logical_map(i) = i == cpu ? 0 : i;

	/*
	 * clear __my_cpu_offset on boot CPU to aव्योम hang caused by
	 * using percpu variable early, क्रम example, lockdep will
	 * access percpu variable inside lock_release
	 */
	set_my_cpu_offset(0);

	pr_info("Booting Linux on physical CPU 0x%x\n", mpidr);
पूर्ण

काष्ठा mpidr_hash mpidr_hash;
#अगर_घोषित CONFIG_SMP
/**
 * smp_build_mpidr_hash - Pre-compute shअगरts required at each affinity
 *			  level in order to build a linear index from an
 *			  MPIDR value. Resulting algorithm is a collision
 *			  मुक्त hash carried out through shअगरting and ORing
 */
अटल व्योम __init smp_build_mpidr_hash(व्योम)
अणु
	u32 i, affinity;
	u32 fs[3], bits[3], ls, mask = 0;
	/*
	 * Pre-scan the list of MPIDRS and filter out bits that करो
	 * not contribute to affinity levels, ie they never toggle.
	 */
	क्रम_each_possible_cpu(i)
		mask |= (cpu_logical_map(i) ^ cpu_logical_map(0));
	pr_debug("mask of set bits 0x%x\n", mask);
	/*
	 * Find and stash the last and first bit set at all affinity levels to
	 * check how many bits are required to represent them.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		affinity = MPIDR_AFFINITY_LEVEL(mask, i);
		/*
		 * Find the MSB bit and LSB bits position
		 * to determine how many bits are required
		 * to express the affinity level.
		 */
		ls = fls(affinity);
		fs[i] = affinity ? ffs(affinity) - 1 : 0;
		bits[i] = ls - fs[i];
	पूर्ण
	/*
	 * An index can be created from the MPIDR by isolating the
	 * signअगरicant bits at each affinity level and by shअगरting
	 * them in order to compress the 24 bits values space to a
	 * compressed set of values. This is equivalent to hashing
	 * the MPIDR through shअगरting and ORing. It is a collision मुक्त
	 * hash though not minimal since some levels might contain a number
	 * of CPUs that is not an exact घातer of 2 and their bit
	 * representation might contain holes, eg MPIDR[7:0] = अणु0x2, 0x80पूर्ण.
	 */
	mpidr_hash.shअगरt_aff[0] = fs[0];
	mpidr_hash.shअगरt_aff[1] = MPIDR_LEVEL_BITS + fs[1] - bits[0];
	mpidr_hash.shअगरt_aff[2] = 2*MPIDR_LEVEL_BITS + fs[2] -
						(bits[1] + bits[0]);
	mpidr_hash.mask = mask;
	mpidr_hash.bits = bits[2] + bits[1] + bits[0];
	pr_debug("MPIDR hash: aff0[%u] aff1[%u] aff2[%u] mask[0x%x] bits[%u]\n",
				mpidr_hash.shअगरt_aff[0],
				mpidr_hash.shअगरt_aff[1],
				mpidr_hash.shअगरt_aff[2],
				mpidr_hash.mask,
				mpidr_hash.bits);
	/*
	 * 4x is an arbitrary value used to warn on a hash table much bigger
	 * than expected on most प्रणालीs.
	 */
	अगर (mpidr_hash_size() > 4 * num_possible_cpus())
		pr_warn("Large number of MPIDR hash buckets detected\n");
	sync_cache_w(&mpidr_hash);
पूर्ण
#पूर्ण_अगर

/*
 * locate processor in the list of supported processor types.  The linker
 * builds this table क्रम us from the entries in arch/arm/mm/proc-*.S
 */
काष्ठा proc_info_list *lookup_processor(u32 midr)
अणु
	काष्ठा proc_info_list *list = lookup_processor_type(midr);

	अगर (!list) अणु
		pr_err("CPU%u: configuration botched (ID %08x), CPU halted\n",
		       smp_processor_id(), midr);
		जबतक (1)
		/* can't use cpu_relax() here as it may require MMU setup */;
	पूर्ण

	वापस list;
पूर्ण

अटल व्योम __init setup_processor(व्योम)
अणु
	अचिन्हित पूर्णांक midr = पढ़ो_cpuid_id();
	काष्ठा proc_info_list *list = lookup_processor(midr);

	cpu_name = list->cpu_name;
	__cpu_architecture = __get_cpu_architecture();

	init_proc_vtable(list->proc);
#अगर_घोषित MULTI_TLB
	cpu_tlb = *list->tlb;
#पूर्ण_अगर
#अगर_घोषित MULTI_USER
	cpu_user = *list->user;
#पूर्ण_अगर
#अगर_घोषित MULTI_CACHE
	cpu_cache = *list->cache;
#पूर्ण_अगर

	pr_info("CPU: %s [%08x] revision %d (ARMv%s), cr=%08lx\n",
		list->cpu_name, midr, midr & 15,
		proc_arch[cpu_architecture()], get_cr());

	snम_लिखो(init_utsname()->machine, __NEW_UTS_LEN + 1, "%s%c",
		 list->arch_name, ENDIANNESS);
	snम_लिखो(elf_platक्रमm, ELF_PLATFORM_SIZE, "%s%c",
		 list->elf_name, ENDIANNESS);
	elf_hwcap = list->elf_hwcap;

	cpuid_init_hwcaps();
	patch_aeabi_iभाग();

#अगर_अघोषित CONFIG_ARM_THUMB
	elf_hwcap &= ~(HWCAP_THUMB | HWCAP_IDIVT);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMU
	init_शेष_cache_policy(list->__cpu_mm_mmu_flags);
#पूर्ण_अगर
	erratum_a15_798181_init();

	elf_hwcap_fixup();

	cacheid_init();
	cpu_init();
पूर्ण

व्योम __init dump_machine_table(व्योम)
अणु
	स्थिर काष्ठा machine_desc *p;

	early_prपूर्णांक("Available machine support:\n\nID (hex)\tNAME\n");
	क्रम_each_machine_desc(p)
		early_prपूर्णांक("%08x\t%s\n", p->nr, p->name);

	early_prपूर्णांक("\nPlease check your kernel config and/or bootloader.\n");

	जबतक (true)
		/* can't use cpu_relax() here as it may require MMU setup */;
पूर्ण

पूर्णांक __init arm_add_memory(u64 start, u64 size)
अणु
	u64 aligned_start;

	/*
	 * Ensure that start/size are aligned to a page boundary.
	 * Size is rounded करोwn, start is rounded up.
	 */
	aligned_start = PAGE_ALIGN(start);
	अगर (aligned_start > start + size)
		size = 0;
	अन्यथा
		size -= aligned_start - start;

#अगर_अघोषित CONFIG_PHYS_ADDR_T_64BIT
	अगर (aligned_start > अच_दीर्घ_उच्च) अणु
		pr_crit("Ignoring memory at 0x%08llx outside 32-bit physical address space\n",
			start);
		वापस -EINVAL;
	पूर्ण

	अगर (aligned_start + size > अच_दीर्घ_उच्च) अणु
		pr_crit("Truncating memory at 0x%08llx to fit in 32-bit physical address space\n",
			(दीर्घ दीर्घ)start);
		/*
		 * To ensure bank->start + bank->size is representable in
		 * 32 bits, we use अच_दीर्घ_उच्च as the upper limit rather than 4GB.
		 * This means we lose a page after masking.
		 */
		size = अच_दीर्घ_उच्च - aligned_start;
	पूर्ण
#पूर्ण_अगर

	अगर (aligned_start < PHYS_OFFSET) अणु
		अगर (aligned_start + size <= PHYS_OFFSET) अणु
			pr_info("Ignoring memory below PHYS_OFFSET: 0x%08llx-0x%08llx\n",
				aligned_start, aligned_start + size);
			वापस -EINVAL;
		पूर्ण

		pr_info("Ignoring memory below PHYS_OFFSET: 0x%08llx-0x%08llx\n",
			aligned_start, (u64)PHYS_OFFSET);

		size -= PHYS_OFFSET - aligned_start;
		aligned_start = PHYS_OFFSET;
	पूर्ण

	start = aligned_start;
	size = size & ~(phys_addr_t)(PAGE_SIZE - 1);

	/*
	 * Check whether this memory region has non-zero size or
	 * invalid node number.
	 */
	अगर (size == 0)
		वापस -EINVAL;

	memblock_add(start, size);
	वापस 0;
पूर्ण

/*
 * Pick out the memory size.  We look क्रम mem=size@start,
 * where start and size are "size[KkMm]"
 */

अटल पूर्णांक __init early_mem(अक्षर *p)
अणु
	अटल पूर्णांक usermem __initdata = 0;
	u64 size;
	u64 start;
	अक्षर *endp;

	/*
	 * If the user specअगरies memory size, we
	 * blow away any स्वतःmatically generated
	 * size.
	 */
	अगर (usermem == 0) अणु
		usermem = 1;
		memblock_हटाओ(memblock_start_of_DRAM(),
			memblock_end_of_DRAM() - memblock_start_of_DRAM());
	पूर्ण

	start = PHYS_OFFSET;
	size  = memparse(p, &endp);
	अगर (*endp == '@')
		start = memparse(endp + 1, शून्य);

	arm_add_memory(start, size);

	वापस 0;
पूर्ण
early_param("mem", early_mem);

अटल व्योम __init request_standard_resources(स्थिर काष्ठा machine_desc *mdesc)
अणु
	phys_addr_t start, end, res_end;
	काष्ठा resource *res;
	u64 i;

	kernel_code.start   = virt_to_phys(_text);
	kernel_code.end     = virt_to_phys(__init_begin - 1);
	kernel_data.start   = virt_to_phys(_sdata);
	kernel_data.end     = virt_to_phys(_end - 1);

	क्रम_each_mem_range(i, &start, &end) अणु
		अचिन्हित दीर्घ boot_alias_start;

		/*
		 * In memblock, end poपूर्णांकs to the first byte after the
		 * range जबतक in resourses, end poपूर्णांकs to the last byte in
		 * the range.
		 */
		res_end = end - 1;

		/*
		 * Some प्रणालीs have a special memory alias which is only
		 * used क्रम booting.  We need to advertise this region to
		 * kexec-tools so they know where bootable RAM is located.
		 */
		boot_alias_start = phys_to_idmap(start);
		अगर (arm_has_idmap_alias() && boot_alias_start != IDMAP_INVALID_ADDR) अणु
			res = memblock_alloc(माप(*res), SMP_CACHE_BYTES);
			अगर (!res)
				panic("%s: Failed to allocate %zu bytes\n",
				      __func__, माप(*res));
			res->name = "System RAM (boot alias)";
			res->start = boot_alias_start;
			res->end = phys_to_idmap(res_end);
			res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;
			request_resource(&iomem_resource, res);
		पूर्ण

		res = memblock_alloc(माप(*res), SMP_CACHE_BYTES);
		अगर (!res)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      माप(*res));
		res->name  = "System RAM";
		res->start = start;
		res->end = res_end;
		res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

		request_resource(&iomem_resource, res);

		अगर (kernel_code.start >= res->start &&
		    kernel_code.end <= res->end)
			request_resource(res, &kernel_code);
		अगर (kernel_data.start >= res->start &&
		    kernel_data.end <= res->end)
			request_resource(res, &kernel_data);
	पूर्ण

	अगर (mdesc->video_start) अणु
		video_ram.start = mdesc->video_start;
		video_ram.end   = mdesc->video_end;
		request_resource(&iomem_resource, &video_ram);
	पूर्ण

	/*
	 * Some machines करोn't have the possibility of ever
	 * possessing lp0, lp1 or lp2
	 */
	अगर (mdesc->reserve_lp0)
		request_resource(&ioport_resource, &lp0);
	अगर (mdesc->reserve_lp1)
		request_resource(&ioport_resource, &lp1);
	अगर (mdesc->reserve_lp2)
		request_resource(&ioport_resource, &lp2);
पूर्ण

#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE) || \
    defined(CONFIG_EFI)
काष्ठा screen_info screen_info = अणु
 .orig_video_lines	= 30,
 .orig_video_cols	= 80,
 .orig_video_mode	= 0,
 .orig_video_ega_bx	= 0,
 .orig_video_isVGA	= 1,
 .orig_video_poपूर्णांकs	= 8
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init customize_machine(व्योम)
अणु
	/*
	 * customizes platक्रमm devices, or adds new ones
	 * On DT based machines, we fall back to populating the
	 * machine from the device tree, अगर no callback is provided,
	 * otherwise we would always need an init_machine callback.
	 */
	अगर (machine_desc->init_machine)
		machine_desc->init_machine();

	वापस 0;
पूर्ण
arch_initcall(customize_machine);

अटल पूर्णांक __init init_machine_late(व्योम)
अणु
	काष्ठा device_node *root;
	पूर्णांक ret;

	अगर (machine_desc->init_late)
		machine_desc->init_late();

	root = of_find_node_by_path("/");
	अगर (root) अणु
		ret = of_property_पढ़ो_string(root, "serial-number",
					      &प्रणाली_serial);
		अगर (ret)
			प्रणाली_serial = शून्य;
	पूर्ण

	अगर (!प्रणाली_serial)
		प्रणाली_serial = kaप्र_लिखो(GFP_KERNEL, "%08x%08x",
					  प्रणाली_serial_high,
					  प्रणाली_serial_low);

	वापस 0;
पूर्ण
late_initcall(init_machine_late);

#अगर_घोषित CONFIG_KEXEC
/*
 * The crash region must be aligned to 128MB to aव्योम
 * zImage relocating below the reserved region.
 */
#घोषणा CRASH_ALIGN	(128 << 20)

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ get_total_mem(व्योम)
अणु
	अचिन्हित दीर्घ total;

	total = max_low_pfn - min_low_pfn;
	वापस total << PAGE_SHIFT;
पूर्ण

/**
 * reserve_crashkernel() - reserves memory are क्रम crash kernel
 *
 * This function reserves memory area given in "crashkernel=" kernel command
 * line parameter. The memory reserved is used by a dump capture kernel when
 * primary kernel is crashing.
 */
अटल व्योम __init reserve_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ crash_size, crash_base;
	अचिन्हित दीर्घ दीर्घ total_mem;
	पूर्णांक ret;

	total_mem = get_total_mem();
	ret = parse_crashkernel(boot_command_line, total_mem,
				&crash_size, &crash_base);
	अगर (ret)
		वापस;

	अगर (crash_base <= 0) अणु
		अचिन्हित दीर्घ दीर्घ crash_max = idmap_to_phys((u32)~0);
		अचिन्हित दीर्घ दीर्घ lowmem_max = __pa(high_memory - 1) + 1;
		अगर (crash_max > lowmem_max)
			crash_max = lowmem_max;
		crash_base = memblock_find_in_range(CRASH_ALIGN, crash_max,
						    crash_size, CRASH_ALIGN);
		अगर (!crash_base) अणु
			pr_err("crashkernel reservation failed - No suitable area found.\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ दीर्घ start;

		start = memblock_find_in_range(crash_base,
					       crash_base + crash_size,
					       crash_size, SECTION_SIZE);
		अगर (start != crash_base) अणु
			pr_err("crashkernel reservation failed - memory is in use.\n");
			वापस;
		पूर्ण
	पूर्ण

	ret = memblock_reserve(crash_base, crash_size);
	अगर (ret < 0) अणु
		pr_warn("crashkernel reservation failed - memory is in use (0x%lx)\n",
			(अचिन्हित दीर्घ)crash_base);
		वापस;
	पूर्ण

	pr_info("Reserving %ldMB of memory at %ldMB for crashkernel (System RAM: %ldMB)\n",
		(अचिन्हित दीर्घ)(crash_size >> 20),
		(अचिन्हित दीर्घ)(crash_base >> 20),
		(अचिन्हित दीर्घ)(total_mem >> 20));

	/* The crashk resource must always be located in normal mem */
	crashk_res.start = crash_base;
	crashk_res.end = crash_base + crash_size - 1;
	insert_resource(&iomem_resource, &crashk_res);

	अगर (arm_has_idmap_alias()) अणु
		/*
		 * If we have a special RAM alias क्रम use at boot, we
		 * need to advertise to kexec tools where the alias is.
		 */
		अटल काष्ठा resource crashk_boot_res = अणु
			.name = "Crash kernel (boot alias)",
			.flags = IORESOURCE_BUSY | IORESOURCE_MEM,
		पूर्ण;

		crashk_boot_res.start = phys_to_idmap(crash_base);
		crashk_boot_res.end = crashk_boot_res.start + crash_size - 1;
		insert_resource(&iomem_resource, &crashk_boot_res);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम reserve_crashkernel(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC */

व्योम __init hyp_mode_check(व्योम)
अणु
#अगर_घोषित CONFIG_ARM_VIRT_EXT
	sync_boot_mode();

	अगर (is_hyp_mode_available()) अणु
		pr_info("CPU: All CPU(s) started in HYP mode.\n");
		pr_info("CPU: Virtualization extensions available.\n");
	पूर्ण अन्यथा अगर (is_hyp_mode_mismatched()) अणु
		pr_warn("CPU: WARNING: CPU(s) started in wrong/inconsistent modes (primary CPU mode 0x%x)\n",
			__boot_cpu_mode & MODE_MASK);
		pr_warn("CPU: This may indicate a broken bootloader or firmware.\n");
	पूर्ण अन्यथा
		pr_info("CPU: All CPU(s) started in SVC mode.\n");
#पूर्ण_अगर
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	स्थिर काष्ठा machine_desc *mdesc = शून्य;
	व्योम *atags_vaddr = शून्य;

	अगर (__atags_poपूर्णांकer)
		atags_vaddr = FDT_VIRT_BASE(__atags_poपूर्णांकer);

	setup_processor();
	अगर (atags_vaddr) अणु
		mdesc = setup_machine_fdt(atags_vaddr);
		अगर (mdesc)
			memblock_reserve(__atags_poपूर्णांकer,
					 fdt_totalsize(atags_vaddr));
	पूर्ण
	अगर (!mdesc)
		mdesc = setup_machine_tags(atags_vaddr, __machine_arch_type);
	अगर (!mdesc) अणु
		early_prपूर्णांक("\nError: invalid dtb and unrecognized/unsupported machine ID\n");
		early_prपूर्णांक("  r1=0x%08x, r2=0x%08x\n", __machine_arch_type,
			    __atags_poपूर्णांकer);
		अगर (__atags_poपूर्णांकer)
			early_prपूर्णांक("  r2[]=%*ph\n", 16, atags_vaddr);
		dump_machine_table();
	पूर्ण

	machine_desc = mdesc;
	machine_name = mdesc->name;
	dump_stack_set_arch_desc("%s", mdesc->name);

	अगर (mdesc->reboot_mode != REBOOT_HARD)
		reboot_mode = mdesc->reboot_mode;

	init_mm.start_code = (अचिन्हित दीर्घ) _text;
	init_mm.end_code   = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data   = (अचिन्हित दीर्घ) _edata;
	init_mm.brk	   = (अचिन्हित दीर्घ) _end;

	/* populate cmd_line too क्रम later use, preserving boot_command_line */
	strlcpy(cmd_line, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = cmd_line;

	early_fixmap_init();
	early_ioremap_init();

	parse_early_param();

#अगर_घोषित CONFIG_MMU
	early_mm_init(mdesc);
#पूर्ण_अगर
	setup_dma_zone(mdesc);
	xen_early_init();
	efi_init();
	/*
	 * Make sure the calculation क्रम lowmem/highmem is set appropriately
	 * beक्रमe reserving/allocating any memory
	 */
	adjust_lowmem_bounds();
	arm_memblock_init(mdesc);
	/* Memory may have been हटाओd so recalculate the bounds. */
	adjust_lowmem_bounds();

	early_ioremap_reset();

	paging_init(mdesc);
	kasan_init();
	request_standard_resources(mdesc);

	अगर (mdesc->restart)
		arm_pm_restart = mdesc->restart;

	unflatten_device_tree();

	arm_dt_init_cpu_maps();
	psci_dt_init();
#अगर_घोषित CONFIG_SMP
	अगर (is_smp()) अणु
		अगर (!mdesc->smp_init || !mdesc->smp_init()) अणु
			अगर (psci_smp_available())
				smp_set_ops(&psci_smp_ops);
			अन्यथा अगर (mdesc->smp)
				smp_set_ops(mdesc->smp);
		पूर्ण
		smp_init_cpus();
		smp_build_mpidr_hash();
	पूर्ण
#पूर्ण_अगर

	अगर (!is_smp())
		hyp_mode_check();

	reserve_crashkernel();

#अगर_घोषित CONFIG_GENERIC_IRQ_MULTI_HANDLER
	handle_arch_irq = mdesc->handle_irq;
#पूर्ण_अगर

#अगर_घोषित CONFIG_VT
#अगर defined(CONFIG_VGA_CONSOLE)
	conचयनp = &vga_con;
#पूर्ण_अगर
#पूर्ण_अगर

	अगर (mdesc->init_early)
		mdesc->init_early();
पूर्ण


अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpuinfo_arm *cpuinfo = &per_cpu(cpu_data, cpu);
		cpuinfo->cpu.hotpluggable = platक्रमm_can_hotplug_cpu(cpu);
		रेजिस्टर_cpu(&cpuinfo->cpu, cpu);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(topology_init);

#अगर_घोषित CONFIG_HAVE_PROC_CPU
अटल पूर्णांक __init proc_cpu_init(व्योम)
अणु
	काष्ठा proc_dir_entry *res;

	res = proc_सूची_गढ़ो("cpu", शून्य);
	अगर (!res)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
fs_initcall(proc_cpu_init);
#पूर्ण_अगर

अटल स्थिर अक्षर *hwcap_str[] = अणु
	"swp",
	"half",
	"thumb",
	"26bit",
	"fastmult",
	"fpa",
	"vfp",
	"edsp",
	"java",
	"iwmmxt",
	"crunch",
	"thumbee",
	"neon",
	"vfpv3",
	"vfpv3d16",
	"tls",
	"vfpv4",
	"idiva",
	"idivt",
	"vfpd32",
	"lpae",
	"evtstrm",
	शून्य
पूर्ण;

अटल स्थिर अक्षर *hwcap2_str[] = अणु
	"aes",
	"pmull",
	"sha1",
	"sha2",
	"crc32",
	शून्य
पूर्ण;

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i, j;
	u32 cpuid;

	क्रम_each_online_cpu(i) अणु
		/*
		 * glibc पढ़ोs /proc/cpuinfo to determine the number of
		 * online processors, looking क्रम lines beginning with
		 * "processor".  Give glibc what it expects.
		 */
		seq_म_लिखो(m, "processor\t: %d\n", i);
		cpuid = is_smp() ? per_cpu(cpu_data, i).cpuid : पढ़ो_cpuid_id();
		seq_म_लिखो(m, "model name\t: %s rev %d (%s)\n",
			   cpu_name, cpuid & 15, elf_platक्रमm);

#अगर defined(CONFIG_SMP)
		seq_म_लिखो(m, "BogoMIPS\t: %lu.%02lu\n",
			   per_cpu(cpu_data, i).loops_per_jअगरfy / (500000UL/HZ),
			   (per_cpu(cpu_data, i).loops_per_jअगरfy / (5000UL/HZ)) % 100);
#अन्यथा
		seq_म_लिखो(m, "BogoMIPS\t: %lu.%02lu\n",
			   loops_per_jअगरfy / (500000/HZ),
			   (loops_per_jअगरfy / (5000/HZ)) % 100);
#पूर्ण_अगर
		/* dump out the processor features */
		seq_माला_दो(m, "Features\t: ");

		क्रम (j = 0; hwcap_str[j]; j++)
			अगर (elf_hwcap & (1 << j))
				seq_म_लिखो(m, "%s ", hwcap_str[j]);

		क्रम (j = 0; hwcap2_str[j]; j++)
			अगर (elf_hwcap2 & (1 << j))
				seq_म_लिखो(m, "%s ", hwcap2_str[j]);

		seq_म_लिखो(m, "\nCPU implementer\t: 0x%02x\n", cpuid >> 24);
		seq_म_लिखो(m, "CPU architecture: %s\n",
			   proc_arch[cpu_architecture()]);

		अगर ((cpuid & 0x0008f000) == 0x00000000) अणु
			/* pre-ARM7 */
			seq_म_लिखो(m, "CPU part\t: %07x\n", cpuid >> 4);
		पूर्ण अन्यथा अणु
			अगर ((cpuid & 0x0008f000) == 0x00007000) अणु
				/* ARM7 */
				seq_म_लिखो(m, "CPU variant\t: 0x%02x\n",
					   (cpuid >> 16) & 127);
			पूर्ण अन्यथा अणु
				/* post-ARM7 */
				seq_म_लिखो(m, "CPU variant\t: 0x%x\n",
					   (cpuid >> 20) & 15);
			पूर्ण
			seq_म_लिखो(m, "CPU part\t: 0x%03x\n",
				   (cpuid >> 4) & 0xfff);
		पूर्ण
		seq_म_लिखो(m, "CPU revision\t: %d\n\n", cpuid & 15);
	पूर्ण

	seq_म_लिखो(m, "Hardware\t: %s\n", machine_name);
	seq_म_लिखो(m, "Revision\t: %04x\n", प्रणाली_rev);
	seq_म_लिखो(m, "Serial\t\t: %s\n", प्रणाली_serial);

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
	.show	= c_show
पूर्ण;
