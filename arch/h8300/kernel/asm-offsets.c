<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate यंत्र statements containing #घोषणाs,
 * compile this file to assembler, and then extract the
 * #घोषणाs from the assembly-language output.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/ptrace.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* offsets पूर्णांकo the task काष्ठा */
	OFFSET(TASK_STATE, task_काष्ठा, state);
	OFFSET(TASK_FLAGS, task_काष्ठा, flags);
	OFFSET(TASK_PTRACE, task_काष्ठा, ptrace);
	OFFSET(TASK_BLOCKED, task_काष्ठा, blocked);
	OFFSET(TASK_THREAD, task_काष्ठा, thपढ़ो);
	OFFSET(TASK_THREAD_INFO, task_काष्ठा, stack);
	OFFSET(TASK_MM, task_काष्ठा, mm);
	OFFSET(TASK_ACTIVE_MM, task_काष्ठा, active_mm);

	/* offsets पूर्णांकo the irq_cpustat_t काष्ठा */
	DEFINE(CPUSTAT_SOFTIRQ_PENDING, दुरत्व(irq_cpustat_t,
						 __softirq_pending));

	/* offsets पूर्णांकo the thपढ़ो काष्ठा */
	OFFSET(THREAD_KSP, thपढ़ो_काष्ठा, ksp);
	OFFSET(THREAD_USP, thपढ़ो_काष्ठा, usp);
	OFFSET(THREAD_CCR, thपढ़ो_काष्ठा, ccr);

	/* offsets पूर्णांकo the pt_regs काष्ठा */
	DEFINE(LER0,  दुरत्व(काष्ठा pt_regs, er0)      - माप(दीर्घ));
	DEFINE(LER1,  दुरत्व(काष्ठा pt_regs, er1)      - माप(दीर्घ));
	DEFINE(LER2,  दुरत्व(काष्ठा pt_regs, er2)      - माप(दीर्घ));
	DEFINE(LER3,  दुरत्व(काष्ठा pt_regs, er3)      - माप(दीर्घ));
	DEFINE(LER4,  दुरत्व(काष्ठा pt_regs, er4)      - माप(दीर्घ));
	DEFINE(LER5,  दुरत्व(काष्ठा pt_regs, er5)      - माप(दीर्घ));
	DEFINE(LER6,  दुरत्व(काष्ठा pt_regs, er6)      - माप(दीर्घ));
	DEFINE(LORIG, दुरत्व(काष्ठा pt_regs, orig_er0) - माप(दीर्घ));
	DEFINE(LSP,   दुरत्व(काष्ठा pt_regs, sp)       - माप(दीर्घ));
	DEFINE(LCCR,  दुरत्व(काष्ठा pt_regs, ccr)      - माप(दीर्घ));
	DEFINE(LVEC,  दुरत्व(काष्ठा pt_regs, vector)   - माप(दीर्घ));
#अगर defined(CONFIG_CPU_H8S)
	DEFINE(LEXR,  दुरत्व(काष्ठा pt_regs, exr)      - माप(दीर्घ));
#पूर्ण_अगर
	DEFINE(LRET,  दुरत्व(काष्ठा pt_regs, pc)       - माप(दीर्घ));

	DEFINE(PT_PTRACED, PT_PTRACED);

	/* offsets in thपढ़ो_info काष्ठाure */
	OFFSET(TI_TASK, thपढ़ो_info, task);
	OFFSET(TI_FLAGS, thपढ़ो_info, flags);
	OFFSET(TI_CPU, thपढ़ो_info, cpu);
	OFFSET(TI_PRE, thपढ़ो_info, preempt_count);
#अगर_घोषित CONFIG_PREEMPTION
	DEFINE(TI_PRE_COUNT, दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
#पूर्ण_अगर

	वापस 0;
पूर्ण
