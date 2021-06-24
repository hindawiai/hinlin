<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_UML_STACKTRACE_H
#घोषणा _ASM_UML_STACKTRACE_H

#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>

काष्ठा stack_frame अणु
	काष्ठा stack_frame *next_frame;
	अचिन्हित दीर्घ वापस_address;
पूर्ण;

काष्ठा stacktrace_ops अणु
	व्योम (*address)(व्योम *data, अचिन्हित दीर्घ address, पूर्णांक reliable);
पूर्ण;

#अगर_घोषित CONFIG_FRAME_POINTER
अटल अंतरभूत अचिन्हित दीर्घ
get_frame_poपूर्णांकer(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *segv_regs)
अणु
	अगर (!task || task == current)
		वापस segv_regs ? PT_REGS_BP(segv_regs) : current_bp();
	वापस KSTK_EBP(task);
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ
get_frame_poपूर्णांकer(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *segv_regs)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ
*get_stack_poपूर्णांकer(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *segv_regs)
अणु
	अगर (!task || task == current)
		वापस segv_regs ? (अचिन्हित दीर्घ *)PT_REGS_SP(segv_regs) : current_sp();
	वापस (अचिन्हित दीर्घ *)KSTK_ESP(task);
पूर्ण

व्योम dump_trace(काष्ठा task_काष्ठा *tsk, स्थिर काष्ठा stacktrace_ops *ops, व्योम *data);

#पूर्ण_अगर /* _ASM_UML_STACKTRACE_H */
