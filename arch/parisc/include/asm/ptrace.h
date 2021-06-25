<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* written by Philipp Rumpf, Copyright (C) 1999 SuSE GmbH Nuernberg
** Copyright (C) 2000 Grant Grundler, Hewlett-Packard
*/
#अगर_अघोषित _PARISC_PTRACE_H
#घोषणा _PARISC_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>


#घोषणा task_regs(task) ((काष्ठा pt_regs *) ((अक्षर *)(task) + TASK_REGS))

#घोषणा arch_has_single_step()	1
#घोषणा arch_has_block_step()	1

/* XXX should we use iaoq[1] or iaoq[0] ? */
#घोषणा user_mode(regs)			(((regs)->iaoq[0] & 3) ? 1 : 0)
#घोषणा user_space(regs)		(((regs)->iasq[1] != 0) ? 1 : 0)
#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	((regs)->iaoq[0] & ~3)
#घोषणा user_stack_poपूर्णांकer(regs)	((regs)->gr[30])
अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *);

अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->gr[28];
पूर्ण

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
						अचिन्हित दीर्घ val)
अणु
	regs->iaoq[0] = val;
	regs->iaoq[1] = val + 4;
पूर्ण

/* Query offset/name of रेजिस्टर from its name/offset */
बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);
#घोषणा MAX_REG_OFFSET (दुरत्व(काष्ठा pt_regs, ipsw))

#घोषणा kernel_stack_poपूर्णांकer(regs) ((regs)->gr[30])

अटल अंतरभूत अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs,
					      अचिन्हित पूर्णांक offset)
अणु
	अगर (unlikely(offset > MAX_REG_OFFSET))
		वापस 0;
	वापस *(अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)regs + offset);
पूर्ण

अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n);
पूर्णांक regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr);

#पूर्ण_अगर
