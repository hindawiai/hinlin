<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _KSTACK_H
#घोषणा _KSTACK_H

#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq.h>

/* SP must be STACK_BIAS adjusted alपढ़ोy.  */
अटल अंतरभूत bool kstack_valid(काष्ठा thपढ़ो_info *tp, अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ) tp;

	/* Stack poपूर्णांकer must be 16-byte aligned.  */
	अगर (sp & (16UL - 1))
		वापस false;

	अगर (sp >= (base + माप(काष्ठा thपढ़ो_info)) &&
	    sp <= (base + THREAD_SIZE - माप(काष्ठा sparc_stackf)))
		वापस true;

	अगर (hardirq_stack[tp->cpu]) अणु
		base = (अचिन्हित दीर्घ) hardirq_stack[tp->cpu];
		अगर (sp >= base &&
		    sp <= (base + THREAD_SIZE - माप(काष्ठा sparc_stackf)))
			वापस true;
		base = (अचिन्हित दीर्घ) softirq_stack[tp->cpu];
		अगर (sp >= base &&
		    sp <= (base + THREAD_SIZE - माप(काष्ठा sparc_stackf)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Does "regs" poपूर्णांक to a valid pt_regs trap frame?  */
अटल अंतरभूत bool kstack_is_trap_frame(काष्ठा thपढ़ो_info *tp, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ) tp;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) regs;

	अगर (addr >= base &&
	    addr <= (base + THREAD_SIZE - माप(*regs)))
		जाओ check_magic;

	अगर (hardirq_stack[tp->cpu]) अणु
		base = (अचिन्हित दीर्घ) hardirq_stack[tp->cpu];
		अगर (addr >= base &&
		    addr <= (base + THREAD_SIZE - माप(*regs)))
			जाओ check_magic;
		base = (अचिन्हित दीर्घ) softirq_stack[tp->cpu];
		अगर (addr >= base &&
		    addr <= (base + THREAD_SIZE - माप(*regs)))
			जाओ check_magic;
	पूर्ण
	वापस false;

check_magic:
	अगर ((regs->magic & ~0x1ff) == PT_REGS_MAGIC)
		वापस true;
	वापस false;

पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत)) व्योम *set_hardirq_stack(व्योम)
अणु
	व्योम *orig_sp, *sp = hardirq_stack[smp_processor_id()];

	__यंत्र__ __अस्थिर__("mov %%sp, %0" : "=r" (orig_sp));
	अगर (orig_sp < sp ||
	    orig_sp > (sp + THREAD_SIZE)) अणु
		sp += THREAD_SIZE - 192 - STACK_BIAS;
		__यंत्र__ __अस्थिर__("mov %0, %%sp" : : "r" (sp));
	पूर्ण

	वापस orig_sp;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत)) व्योम restore_hardirq_stack(व्योम *orig_sp)
अणु
	__यंत्र__ __अस्थिर__("mov %0, %%sp" : : "r" (orig_sp));
पूर्ण

#पूर्ण_अगर /* _KSTACK_H */
