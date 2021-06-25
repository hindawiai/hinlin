<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common prep/pmac/chrp boot and setup code.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/initrd.h>
#समावेश <linux/tty.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/cpu.h>
#समावेश <linux/console.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/nvram.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/bootx.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/machdep.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/xmon.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/serial.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/kdump.h>
#समावेश <यंत्र/feature-fixups.h>
#समावेश <यंत्र/early_ioremap.h>

#समावेश "setup.h"

#घोषणा DBG(fmt...)

बाह्य व्योम bootx_init(अचिन्हित दीर्घ r4, अचिन्हित दीर्घ phys);

पूर्णांक boot_cpuid_phys;
EXPORT_SYMBOL_GPL(boot_cpuid_phys);

पूर्णांक smp_hw_index[NR_CPUS];
EXPORT_SYMBOL(smp_hw_index);

अचिन्हित पूर्णांक DMA_MODE_READ;
अचिन्हित पूर्णांक DMA_MODE_WRITE;

EXPORT_SYMBOL(DMA_MODE_READ);
EXPORT_SYMBOL(DMA_MODE_WRITE);

/*
 * This is run beक्रमe start_kernel(), the kernel has been relocated
 * and we are running with enough of the MMU enabled to have our
 * proper kernel भव addresses
 *
 * We करो the initial parsing of the flat device-tree and prepares
 * क्रम the MMU to be fully initialized.
 */
notrace व्योम __init machine_init(u64 dt_ptr)
अणु
	काष्ठा ppc_inst *addr = (काष्ठा ppc_inst *)patch_site_addr(&patch__स_रखो_nocache);
	काष्ठा ppc_inst insn;

	/* Configure अटल keys first, now that we're relocated. */
	setup_feature_keys();

	early_ioremap_init();

	/* Enable early debugging अगर any specअगरied (see udbg.h) */
	udbg_early_init();

	patch_inकाष्ठाion_site(&patch__स_नकल_nocache, ppc_inst(PPC_INST_NOP));

	create_cond_branch(&insn, addr, branch_target(addr), 0x820000);
	patch_inकाष्ठाion(addr, insn);	/* replace b by bne cr0 */

	/* Do some early initialization based on the flat device tree */
	early_init_devtree(__va(dt_ptr));

	early_init_mmu();

	setup_kdump_trampoline();
पूर्ण

/* Checks "l2cr=xxxx" command-line option */
अटल पूर्णांक __init ppc_setup_l2cr(अक्षर *str)
अणु
	अगर (cpu_has_feature(CPU_FTR_L2CR)) अणु
		अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(str, शून्य, 0);
		prपूर्णांकk(KERN_INFO "l2cr set to %lx\n", val);
		_set_L2CR(0);		/* क्रमce invalidate by disable cache */
		_set_L2CR(val);		/* and enable it */
	पूर्ण
	वापस 1;
पूर्ण
__setup("l2cr=", ppc_setup_l2cr);

/* Checks "l3cr=xxxx" command-line option */
अटल पूर्णांक __init ppc_setup_l3cr(अक्षर *str)
अणु
	अगर (cpu_has_feature(CPU_FTR_L3CR)) अणु
		अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(str, शून्य, 0);
		prपूर्णांकk(KERN_INFO "l3cr set to %lx\n", val);
		_set_L3CR(val);		/* and enable it */
	पूर्ण
	वापस 1;
पूर्ण
__setup("l3cr=", ppc_setup_l3cr);

अटल पूर्णांक __init ppc_init(व्योम)
अणु
	/* clear the progress line */
	अगर (ppc_md.progress)
		ppc_md.progress("             ", 0xffff);

	/* call platक्रमm init */
	अगर (ppc_md.init != शून्य) अणु
		ppc_md.init();
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(ppc_init);

अटल व्योम *__init alloc_stack(व्योम)
अणु
	व्योम *ptr = memblock_alloc(THREAD_SIZE, THREAD_ALIGN);

	अगर (!ptr)
		panic("cannot allocate %d bytes for stack at %pS\n",
		      THREAD_SIZE, (व्योम *)_RET_IP_);

	वापस ptr;
पूर्ण

व्योम __init irqstack_early_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (IS_ENABLED(CONFIG_VMAP_STACK))
		वापस;

	/* पूर्णांकerrupt stacks must be in lowmem, we get that क्रम मुक्त on ppc32
	 * as the memblock is limited to lowmem by शेष */
	क्रम_each_possible_cpu(i) अणु
		softirq_ctx[i] = alloc_stack();
		hardirq_ctx[i] = alloc_stack();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_VMAP_STACK
व्योम *emergency_ctx[NR_CPUS] __ro_after_init = अणु[0] = &init_stackपूर्ण;

व्योम __init emergency_stack_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_possible_cpu(i)
		emergency_ctx[i] = alloc_stack();
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
व्योम __init exc_lvl_early_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, hw_cpu;

	/* पूर्णांकerrupt stacks must be in lowmem, we get that क्रम मुक्त on ppc32
	 * as the memblock is limited to lowmem by MEMBLOCK_REAL_LIMIT */
	क्रम_each_possible_cpu(i) अणु
#अगर_घोषित CONFIG_SMP
		hw_cpu = get_hard_smp_processor_id(i);
#अन्यथा
		hw_cpu = 0;
#पूर्ण_अगर

		critirq_ctx[hw_cpu] = alloc_stack();
#अगर_घोषित CONFIG_BOOKE
		dbgirq_ctx[hw_cpu] = alloc_stack();
		mcheckirq_ctx[hw_cpu] = alloc_stack();
#पूर्ण_अगर
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम __init setup_घातer_save(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	अगर (cpu_has_feature(CPU_FTR_CAN_DOZE) ||
	    cpu_has_feature(CPU_FTR_CAN_NAP))
		ppc_md.घातer_save = ppc6xx_idle;
#पूर्ण_अगर

#अगर_घोषित CONFIG_E500
	अगर (cpu_has_feature(CPU_FTR_CAN_DOZE) ||
	    cpu_has_feature(CPU_FTR_CAN_NAP))
		ppc_md.घातer_save = e500_idle;
#पूर्ण_अगर
पूर्ण

__init व्योम initialize_cache_info(व्योम)
अणु
	/*
	 * Set cache line size based on type of cpu as a शेष.
	 * Systems with OF can look in the properties on the cpu node(s)
	 * क्रम a possibly more accurate value.
	 */
	dcache_bsize = cur_cpu_spec->dcache_bsize;
	icache_bsize = cur_cpu_spec->icache_bsize;
पूर्ण
