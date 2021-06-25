<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PERF_REGS_H
#घोषणा _LINUX_PERF_REGS_H

#समावेश <linux/sched/task_stack.h>

काष्ठा perf_regs अणु
	__u64		abi;
	काष्ठा pt_regs	*regs;
पूर्ण;

#अगर_घोषित CONFIG_HAVE_PERF_REGS
#समावेश <यंत्र/perf_regs.h>

#अगर_अघोषित PERF_REG_EXTENDED_MASK
#घोषणा PERF_REG_EXTENDED_MASK	0
#पूर्ण_अगर

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx);
पूर्णांक perf_reg_validate(u64 mask);
u64 perf_reg_abi(काष्ठा task_काष्ठा *task);
व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs);
#अन्यथा

#घोषणा PERF_REG_EXTENDED_MASK	0

अटल अंतरभूत u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक perf_reg_validate(u64 mask)
अणु
	वापस mask ? -ENOSYS : 0;
पूर्ण

अटल अंतरभूत u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
	वापस PERF_SAMPLE_REGS_ABI_NONE;
पूर्ण

अटल अंतरभूत व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
				      काष्ठा pt_regs *regs)
अणु
	regs_user->regs = task_pt_regs(current);
	regs_user->abi = perf_reg_abi(current);
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_PERF_REGS */
#पूर्ण_अगर /* _LINUX_PERF_REGS_H */
