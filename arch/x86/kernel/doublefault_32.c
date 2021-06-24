<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/init_task.h>
#समावेश <linux/fs.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/traps.h>

#घोषणा ptr_ok(x) ((x) > PAGE_OFFSET && (x) < PAGE_OFFSET + MAXMEM)

#घोषणा TSS(x) this_cpu_पढ़ो(cpu_tss_rw.x86_tss.x)

अटल व्योम set_df_gdt_entry(अचिन्हित पूर्णांक cpu);

/*
 * Called by द्विगुन_fault with CR0.TS and EFLAGS.NT cleared.  The CPU thinks
 * we're running the द्विगुनfault task.  Cannot वापस.
 */
यंत्रlinkage noinstr व्योम __noवापस द्विगुनfault_shim(व्योम)
अणु
	अचिन्हित दीर्घ cr2;
	काष्ठा pt_regs regs;

	BUILD_BUG_ON(माप(काष्ठा द्विगुनfault_stack) != PAGE_SIZE);

	cr2 = native_पढ़ो_cr2();

	/* Reset back to the normal kernel task. */
	क्रमce_reload_TR();
	set_df_gdt_entry(smp_processor_id());

	trace_hardirqs_off();

	/*
	 * Fill in pt_regs.  A करोwnside of करोing this in C is that the unwinder
	 * won't see it (no ENCODE_FRAME_POINTER), so a nested stack dump
	 * won't successfully unwind to the source of the द्विगुन fault.
	 * The मुख्य dump from exc_द्विगुन_fault() is fine, though, since it
	 * uses these regs directly.
	 *
	 * If anyone ever cares, this could be moved to यंत्र.
	 */
	regs.ss		= TSS(ss);
	regs.__ssh	= 0;
	regs.sp		= TSS(sp);
	regs.flags	= TSS(flags);
	regs.cs		= TSS(cs);
	/* We won't go through the entry यंत्र, so we can leave __csh as 0. */
	regs.__csh	= 0;
	regs.ip		= TSS(ip);
	regs.orig_ax	= 0;
	regs.gs		= TSS(gs);
	regs.__gsh	= 0;
	regs.fs		= TSS(fs);
	regs.__fsh	= 0;
	regs.es		= TSS(es);
	regs.__esh	= 0;
	regs.ds		= TSS(ds);
	regs.__dsh	= 0;
	regs.ax		= TSS(ax);
	regs.bp		= TSS(bp);
	regs.di		= TSS(di);
	regs.si		= TSS(si);
	regs.dx		= TSS(dx);
	regs.cx		= TSS(cx);
	regs.bx		= TSS(bx);

	exc_द्विगुन_fault(&regs, 0, cr2);

	/*
	 * x86_32 करोes not save the original CR3 anywhere on a task चयन.
	 * This means that, even अगर we wanted to वापस, we would need to find
	 * some way to reस्थिरruct CR3.  We could make a credible guess based
	 * on cpu_tlbstate, but that would be racy and would not account क्रम
	 * PTI.
	 *
	 * Instead, करोn't bother.  We can वापस through
	 * शुरुआत_stack_करो_निकास() instead.
	 */
	panic("cannot return from double fault\n");
पूर्ण

DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा द्विगुनfault_stack, द्विगुनfault_stack) = अणु
	.tss = अणु
                /*
                 * No sp0 or ss0 -- we never run CPL != 0 with this TSS
                 * active.  sp is filled in later.
                 */
		.ldt		= 0,
	.io_biपंचांगap_base	= IO_BITMAP_OFFSET_INVALID,

		.ip		= (अचिन्हित दीर्घ) यंत्र_exc_द्विगुन_fault,
		.flags		= X86_EFLAGS_FIXED,
		.es		= __USER_DS,
		.cs		= __KERNEL_CS,
		.ss		= __KERNEL_DS,
		.ds		= __USER_DS,
		.fs		= __KERNEL_PERCPU,
		.gs		= 0,

		.__cr3		= __pa_nodebug(swapper_pg_dir),
	पूर्ण,
पूर्ण;

अटल व्योम set_df_gdt_entry(अचिन्हित पूर्णांक cpu)
अणु
	/* Set up द्विगुनfault TSS poपूर्णांकer in the GDT */
	__set_tss_desc(cpu, GDT_ENTRY_DOUBLEFAULT_TSS,
		       &get_cpu_entry_area(cpu)->द्विगुनfault_stack.tss);

पूर्ण

व्योम द्विगुनfault_init_cpu_tss(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा cpu_entry_area *cea = get_cpu_entry_area(cpu);

	/*
	 * The linker isn't smart enough to initialize percpu variables that
	 * poपूर्णांक to other places in percpu space.
	 */
        this_cpu_ग_लिखो(द्विगुनfault_stack.tss.sp,
                       (अचिन्हित दीर्घ)&cea->द्विगुनfault_stack.stack +
                       माप(द्विगुनfault_stack.stack));

	set_df_gdt_entry(cpu);
पूर्ण
