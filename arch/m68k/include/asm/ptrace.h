<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_PTRACE_H
#घोषणा _M68K_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

#अगर_अघोषित __ASSEMBLY__

#अगर_अघोषित PS_S
#घोषणा PS_S  (0x2000)
#घोषणा PS_M  (0x1000)
#पूर्ण_अगर

#घोषणा user_mode(regs) (!((regs)->sr & PS_S))
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->pc)
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#घोषणा current_pt_regs() \
	(काष्ठा pt_regs *)((अक्षर *)current_thपढ़ो_info() + THREAD_SIZE) - 1
#घोषणा current_user_stack_poपूर्णांकer() rdusp()

#घोषणा arch_has_single_step()	(1)

#अगर_घोषित CONFIG_MMU
#घोषणा arch_has_block_step()	(1)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _M68K_PTRACE_H */
