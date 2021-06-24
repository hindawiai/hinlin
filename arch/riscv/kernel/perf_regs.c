<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd. */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/perf_regs.h>
#समावेश <यंत्र/ptrace.h>

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	अगर (WARN_ON_ONCE((u32)idx >= PERF_REG_RISCV_MAX))
		वापस 0;

	वापस ((अचिन्हित दीर्घ *)regs)[idx];
पूर्ण

#घोषणा REG_RESERVED (~((1ULL << PERF_REG_RISCV_MAX) - 1))

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask || mask & REG_RESERVED)
		वापस -EINVAL;

	वापस 0;
पूर्ण

u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
#अगर __riscv_xlen == 64
	वापस PERF_SAMPLE_REGS_ABI_64;
#अन्यथा
	वापस PERF_SAMPLE_REGS_ABI_32;
#पूर्ण_अगर
पूर्ण

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	regs_user->regs = task_pt_regs(current);
	regs_user->abi = perf_reg_abi(current);
पूर्ण
