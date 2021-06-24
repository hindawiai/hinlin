<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASMARM_TRAP_H
#घोषणा _ASMARM_TRAP_H

#समावेश <linux/list.h>

काष्ठा pt_regs;
काष्ठा task_काष्ठा;

काष्ठा undef_hook अणु
	काष्ठा list_head node;
	u32 instr_mask;
	u32 instr_val;
	u32 cpsr_mask;
	u32 cpsr_val;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr);
पूर्ण;

व्योम रेजिस्टर_undef_hook(काष्ठा undef_hook *hook);
व्योम unरेजिस्टर_undef_hook(काष्ठा undef_hook *hook);

अटल अंतरभूत पूर्णांक __in_irqentry_text(अचिन्हित दीर्घ ptr)
अणु
	बाह्य अक्षर __irqentry_text_start[];
	बाह्य अक्षर __irqentry_text_end[];

	वापस ptr >= (अचिन्हित दीर्घ)&__irqentry_text_start &&
	       ptr < (अचिन्हित दीर्घ)&__irqentry_text_end;
पूर्ण

बाह्य व्योम __init early_trap_init(व्योम *);
बाह्य व्योम dump_backtrace_entry(अचिन्हित दीर्घ where, अचिन्हित दीर्घ from,
				 अचिन्हित दीर्घ frame, स्थिर अक्षर *loglvl);
बाह्य व्योम ptrace_अवरोध(काष्ठा pt_regs *regs);

बाह्य व्योम *vectors_page;

#पूर्ण_अगर
