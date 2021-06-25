<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_PTRACE_H
#घोषणा _H8300_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

काष्ठा task_काष्ठा;

#अगर_अघोषित __ASSEMBLY__
#अगर_अघोषित PS_S
#घोषणा PS_S  (0x10)
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_H8300H)
#घोषणा H8300_REGS_NO 11
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_H8S)
#घोषणा H8300_REGS_NO 12
#पूर्ण_अगर

#घोषणा arch_has_single_step()	(1)

#घोषणा user_mode(regs) (!((regs)->ccr & PS_S))
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->pc)
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#घोषणा user_stack_poपूर्णांकer(regs) ((regs)->sp)
#घोषणा current_pt_regs() ((काष्ठा pt_regs *) \
	(THREAD_SIZE + (अचिन्हित दीर्घ)current_thपढ़ो_info()) - 1)
#घोषणा संकेत_pt_regs() ((काष्ठा pt_regs *)current->thपढ़ो.esp0)
#घोषणा current_user_stack_poपूर्णांकer() rdusp()
#घोषणा task_pt_regs(task) \
	((काष्ठा pt_regs *) (task_stack_page(task) + THREAD_SIZE) - 1)

बाह्य दीर्घ h8300_get_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno);
बाह्य पूर्णांक h8300_put_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno,
			 अचिन्हित दीर्घ data);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _H8300_PTRACE_H */
