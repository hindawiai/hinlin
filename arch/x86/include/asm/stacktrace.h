<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen, SuSE Lअसल
 */

#अगर_अघोषित _ASM_X86_STACKTRACE_H
#घोषणा _ASM_X86_STACKTRACE_H

#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/चयन_to.h>

क्रमागत stack_type अणु
	STACK_TYPE_UNKNOWN,
	STACK_TYPE_TASK,
	STACK_TYPE_IRQ,
	STACK_TYPE_SOFTIRQ,
	STACK_TYPE_ENTRY,
	STACK_TYPE_EXCEPTION,
	STACK_TYPE_EXCEPTION_LAST = STACK_TYPE_EXCEPTION + N_EXCEPTION_STACKS-1,
पूर्ण;

काष्ठा stack_info अणु
	क्रमागत stack_type type;
	अचिन्हित दीर्घ *begin, *end, *next_sp;
पूर्ण;

bool in_task_stack(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
		   काष्ठा stack_info *info);

bool in_entry_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info);

पूर्णांक get_stack_info(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
		   काष्ठा stack_info *info, अचिन्हित दीर्घ *visit_mask);
bool get_stack_info_noinstr(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
			    काष्ठा stack_info *info);

स्थिर अक्षर *stack_type_name(क्रमागत stack_type type);

अटल अंतरभूत bool on_stack(काष्ठा stack_info *info, व्योम *addr, माप_प्रकार len)
अणु
	व्योम *begin = info->begin;
	व्योम *end   = info->end;

	वापस (info->type != STACK_TYPE_UNKNOWN &&
		addr >= begin && addr < end &&
		addr + len > begin && addr + len <= end);
पूर्ण

#अगर_घोषित CONFIG_X86_32
#घोषणा STACKSLOTS_PER_LINE 8
#अन्यथा
#घोषणा STACKSLOTS_PER_LINE 4
#पूर्ण_अगर

#अगर_घोषित CONFIG_FRAME_POINTER
अटल अंतरभूत अचिन्हित दीर्घ *
get_frame_poपूर्णांकer(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अगर (regs)
		वापस (अचिन्हित दीर्घ *)regs->bp;

	अगर (task == current)
		वापस __builtin_frame_address(0);

	वापस &((काष्ठा inactive_task_frame *)task->thपढ़ो.sp)->bp;
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ *
get_frame_poपूर्णांकer(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_FRAME_POINTER */

अटल अंतरभूत अचिन्हित दीर्घ *
get_stack_poपूर्णांकer(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अगर (regs)
		वापस (अचिन्हित दीर्घ *)regs->sp;

	अगर (task == current)
		वापस __builtin_frame_address(0);

	वापस (अचिन्हित दीर्घ *)task->thपढ़ो.sp;
पूर्ण

/* The क्रमm of the top of the frame on the stack */
काष्ठा stack_frame अणु
	काष्ठा stack_frame *next_frame;
	अचिन्हित दीर्घ वापस_address;
पूर्ण;

काष्ठा stack_frame_ia32 अणु
    u32 next_frame;
    u32 वापस_address;
पूर्ण;

व्योम show_opcodes(काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl);
व्योम show_ip(काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl);
#पूर्ण_अगर /* _ASM_X86_STACKTRACE_H */
