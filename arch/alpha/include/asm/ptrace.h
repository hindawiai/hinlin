<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASMAXP_PTRACE_H
#घोषणा _ASMAXP_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>


#घोषणा arch_has_single_step()		(1)
#घोषणा user_mode(regs) (((regs)->ps & 8) != 0)
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->pc)
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#घोषणा current_user_stack_poपूर्णांकer() rdusp()

#घोषणा task_pt_regs(task) \
  ((काष्ठा pt_regs *) (task_stack_page(task) + 2*PAGE_SIZE) - 1)

#घोषणा current_pt_regs() \
  ((काष्ठा pt_regs *) ((अक्षर *)current_thपढ़ो_info() + 2*PAGE_SIZE) - 1)
#घोषणा संकेत_pt_regs current_pt_regs

#घोषणा क्रमce_successful_syscall_वापस() (current_pt_regs()->r0 = 0)

अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->r0;
पूर्ण

#पूर्ण_अगर
