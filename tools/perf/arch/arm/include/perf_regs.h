<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

व्योम perf_regs_load(u64 *regs);

#घोषणा PERF_REGS_MASK	((1ULL << PERF_REG_ARM_MAX) - 1)
#घोषणा PERF_REGS_MAX	PERF_REG_ARM_MAX
#घोषणा PERF_SAMPLE_REGS_ABI	PERF_SAMPLE_REGS_ABI_32

#घोषणा PERF_REG_IP	PERF_REG_ARM_PC
#घोषणा PERF_REG_SP	PERF_REG_ARM_SP

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_ARM_R0:
		वापस "r0";
	हाल PERF_REG_ARM_R1:
		वापस "r1";
	हाल PERF_REG_ARM_R2:
		वापस "r2";
	हाल PERF_REG_ARM_R3:
		वापस "r3";
	हाल PERF_REG_ARM_R4:
		वापस "r4";
	हाल PERF_REG_ARM_R5:
		वापस "r5";
	हाल PERF_REG_ARM_R6:
		वापस "r6";
	हाल PERF_REG_ARM_R7:
		वापस "r7";
	हाल PERF_REG_ARM_R8:
		वापस "r8";
	हाल PERF_REG_ARM_R9:
		वापस "r9";
	हाल PERF_REG_ARM_R10:
		वापस "r10";
	हाल PERF_REG_ARM_FP:
		वापस "fp";
	हाल PERF_REG_ARM_IP:
		वापस "ip";
	हाल PERF_REG_ARM_SP:
		वापस "sp";
	हाल PERF_REG_ARM_LR:
		वापस "lr";
	हाल PERF_REG_ARM_PC:
		वापस "pc";
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
