<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SWITCH_TO_H
#घोषणा _ASM_X86_SWITCH_TO_H

#समावेश <linux/sched/task_stack.h>

काष्ठा task_काष्ठा; /* one of the stranger aspects of C क्रमward declarations */

काष्ठा task_काष्ठा *__चयन_to_यंत्र(काष्ठा task_काष्ठा *prev,
				    काष्ठा task_काष्ठा *next);

__visible काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *prev,
					  काष्ठा task_काष्ठा *next);

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);

/*
 * This is the काष्ठाure poपूर्णांकed to by thपढ़ो.sp क्रम an inactive task.  The
 * order of the fields must match the code in __चयन_to_यंत्र().
 */
काष्ठा inactive_task_frame अणु
#अगर_घोषित CONFIG_X86_64
	अचिन्हित दीर्घ r15;
	अचिन्हित दीर्घ r14;
	अचिन्हित दीर्घ r13;
	अचिन्हित दीर्घ r12;
#अन्यथा
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ si;
	अचिन्हित दीर्घ di;
#पूर्ण_अगर
	अचिन्हित दीर्घ bx;

	/*
	 * These two fields must be together.  They क्रमm a stack frame header,
	 * needed by get_frame_poपूर्णांकer().
	 */
	अचिन्हित दीर्घ bp;
	अचिन्हित दीर्घ ret_addr;
पूर्ण;

काष्ठा विभाजन_frame अणु
	काष्ठा inactive_task_frame frame;
	काष्ठा pt_regs regs;
पूर्ण;

#घोषणा चयन_to(prev, next, last)					\
करो अणु									\
	((last) = __चयन_to_यंत्र((prev), (next)));			\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_X86_32
अटल अंतरभूत व्योम refresh_sysenter_cs(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	/* Only happens when SEP is enabled, no need to test "SEP"arately: */
	अगर (unlikely(this_cpu_पढ़ो(cpu_tss_rw.x86_tss.ss1) == thपढ़ो->sysenter_cs))
		वापस;

	this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.ss1, thपढ़ो->sysenter_cs);
	wrmsr(MSR_IA32_SYSENTER_CS, thपढ़ो->sysenter_cs, 0);
पूर्ण
#पूर्ण_अगर

/* This is used when चयनing tasks or entering/निकासing vm86 mode. */
अटल अंतरभूत व्योम update_task_stack(काष्ठा task_काष्ठा *task)
अणु
	/* sp0 always poपूर्णांकs to the entry trampoline stack, which is स्थिरant: */
#अगर_घोषित CONFIG_X86_32
	अगर (अटल_cpu_has(X86_FEATURE_XENPV))
		load_sp0(task->thपढ़ो.sp0);
	अन्यथा
		this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.sp1, task->thपढ़ो.sp0);
#अन्यथा
	/* Xen PV enters the kernel on the thपढ़ो stack. */
	अगर (अटल_cpu_has(X86_FEATURE_XENPV))
		load_sp0(task_top_of_stack(task));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम kthपढ़ो_frame_init(काष्ठा inactive_task_frame *frame,
				      अचिन्हित दीर्घ fun, अचिन्हित दीर्घ arg)
अणु
	frame->bx = fun;
#अगर_घोषित CONFIG_X86_32
	frame->di = arg;
#अन्यथा
	frame->r12 = arg;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_X86_SWITCH_TO_H */
