<शैली गुरु>
/*
 * linux/arch/h8300/boot/traps.c -- general exception handling code
 * H8/300 support Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * Cloned from Linux/m68k.
 *
 * No original Copyright holder listed,
 * Probable original (C) Roman Zippel (asचिन्हित DJD, 1999)
 *
 * Copyright 1999-2000 D. Jeff Dionne, <jeff@rt-control.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/bug.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/page.h>

अटल DEFINE_SPINLOCK(die_lock);

/*
 * this must be called very early as the kernel might
 * use some inकाष्ठाion that are emulated on the 060
 */

व्योम __init base_trap_init(व्योम)
अणु
पूर्ण

व्योम __init trap_init(व्योम)
अणु
पूर्ण

यंत्रlinkage व्योम set_esp0(अचिन्हित दीर्घ ssp)
अणु
	current->thपढ़ो.esp0 = ssp;
पूर्ण

/*
 *	Generic dumping code. Used क्रम panic and debug.
 */

अटल व्योम dump(काष्ठा pt_regs *fp)
अणु
	अचिन्हित दीर्घ	*sp;
	अचिन्हित अक्षर	*tp;
	पूर्णांक		i;

	pr_info("\nCURRENT PROCESS:\n\n");
	pr_info("COMM=%s PID=%d\n", current->comm, current->pid);
	अगर (current->mm) अणु
		pr_info("TEXT=%08x-%08x DATA=%08x-%08x BSS=%08x-%08x\n",
			(पूर्णांक) current->mm->start_code,
			(पूर्णांक) current->mm->end_code,
			(पूर्णांक) current->mm->start_data,
			(पूर्णांक) current->mm->end_data,
			(पूर्णांक) current->mm->end_data,
			(पूर्णांक) current->mm->brk);
		pr_info("USER-STACK=%08x  KERNEL-STACK=%08lx\n\n",
			(पूर्णांक) current->mm->start_stack,
			(पूर्णांक) PAGE_SIZE+(अचिन्हित दीर्घ)current);
	पूर्ण

	show_regs(fp);
	pr_info("\nCODE:");
	tp = ((अचिन्हित अक्षर *) fp->pc) - 0x20;
	क्रम (sp = (अचिन्हित दीर्घ *) tp, i = 0; (i < 0x40);  i += 4) अणु
		अगर ((i % 0x10) == 0)
			pr_info("\n%08x: ", (पूर्णांक) (tp + i));
		pr_info("%08x ", (पूर्णांक) *sp++);
	पूर्ण
	pr_info("\n");

	pr_info("\nKERNEL STACK:");
	tp = ((अचिन्हित अक्षर *) fp) - 0x40;
	क्रम (sp = (अचिन्हित दीर्घ *) tp, i = 0; (i < 0xc0); i += 4) अणु
		अगर ((i % 0x10) == 0)
			pr_info("\n%08x: ", (पूर्णांक) (tp + i));
		pr_info("%08x ", (पूर्णांक) *sp++);
	पूर्ण
	pr_info("\n");
	अगर (STACK_MAGIC != *(अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)current+PAGE_SIZE))
		pr_info("(Possibly corrupted stack page??)\n");

	pr_info("\n\n");
पूर्ण

व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *fp, अचिन्हित दीर्घ err)
अणु
	अटल पूर्णांक diecount;

	oops_enter();

	console_verbose();
	spin_lock_irq(&die_lock);
	report_bug(fp->pc, fp);
	pr_crit("%s: %04lx [#%d] ", str, err & 0xffff, ++diecount);
	dump(fp);

	spin_unlock_irq(&die_lock);
	करो_निकास(संक_अंश);
पूर्ण

अटल पूर्णांक kstack_depth_to_prपूर्णांक = 24;

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *esp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ *stack,  addr;
	पूर्णांक i;

	अगर (esp == शून्य)
		esp = (अचिन्हित दीर्घ *) &esp;

	stack = esp;

	prपूर्णांकk("%sStack from %08lx:", loglvl, (अचिन्हित दीर्घ)stack);
	क्रम (i = 0; i < kstack_depth_to_prपूर्णांक; i++) अणु
		अगर (((अचिन्हित दीर्घ)stack & (THREAD_SIZE - 1)) >=
		    THREAD_SIZE-4)
			अवरोध;
		अगर (i % 8 == 0)
			prपूर्णांकk("%s ", loglvl);
		pr_cont(" %08lx", *stack++);
	पूर्ण

	prपूर्णांकk("%s\nCall Trace:\n", loglvl);
	i = 0;
	stack = esp;
	जबतक (((अचिन्हित दीर्घ)stack & (THREAD_SIZE - 1)) < THREAD_SIZE-4) अणु
		addr = *stack++;
		/*
		 * If the address is either in the text segment of the
		 * kernel, or in the region which contains vदो_स्मृति'ed
		 * memory, it *may* be the address of a calling
		 * routine; अगर so, prपूर्णांक it so that someone tracing
		 * करोwn the cause of the crash will be able to figure
		 * out the call path that was taken.
		 */
		अगर (check_kernel_text(addr)) अणु
			अगर (i % 4 == 0)
				prपूर्णांकk("%s       ", loglvl);
			pr_cont(" [<%08lx>]", addr);
			i++;
		पूर्ण
	पूर्ण
	prपूर्णांकk("%s\n", loglvl);
पूर्ण
