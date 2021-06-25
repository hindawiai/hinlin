<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

व्योम perf_regs_load(u64 *regs);

#घोषणा PERF_REGS_MASK	((1ULL << PERF_REG_ARM64_MAX) - 1)
#घोषणा PERF_REGS_MAX	PERF_REG_ARM64_MAX
#घोषणा PERF_SAMPLE_REGS_ABI	PERF_SAMPLE_REGS_ABI_64

#घोषणा PERF_REG_IP	PERF_REG_ARM64_PC
#घोषणा PERF_REG_SP	PERF_REG_ARM64_SP

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_ARM64_X0:
		वापस "x0";
	हाल PERF_REG_ARM64_X1:
		वापस "x1";
	हाल PERF_REG_ARM64_X2:
		वापस "x2";
	हाल PERF_REG_ARM64_X3:
		वापस "x3";
	हाल PERF_REG_ARM64_X4:
		वापस "x4";
	हाल PERF_REG_ARM64_X5:
		वापस "x5";
	हाल PERF_REG_ARM64_X6:
		वापस "x6";
	हाल PERF_REG_ARM64_X7:
		वापस "x7";
	हाल PERF_REG_ARM64_X8:
		वापस "x8";
	हाल PERF_REG_ARM64_X9:
		वापस "x9";
	हाल PERF_REG_ARM64_X10:
		वापस "x10";
	हाल PERF_REG_ARM64_X11:
		वापस "x11";
	हाल PERF_REG_ARM64_X12:
		वापस "x12";
	हाल PERF_REG_ARM64_X13:
		वापस "x13";
	हाल PERF_REG_ARM64_X14:
		वापस "x14";
	हाल PERF_REG_ARM64_X15:
		वापस "x15";
	हाल PERF_REG_ARM64_X16:
		वापस "x16";
	हाल PERF_REG_ARM64_X17:
		वापस "x17";
	हाल PERF_REG_ARM64_X18:
		वापस "x18";
	हाल PERF_REG_ARM64_X19:
		वापस "x19";
	हाल PERF_REG_ARM64_X20:
		वापस "x20";
	हाल PERF_REG_ARM64_X21:
		वापस "x21";
	हाल PERF_REG_ARM64_X22:
		वापस "x22";
	हाल PERF_REG_ARM64_X23:
		वापस "x23";
	हाल PERF_REG_ARM64_X24:
		वापस "x24";
	हाल PERF_REG_ARM64_X25:
		वापस "x25";
	हाल PERF_REG_ARM64_X26:
		वापस "x26";
	हाल PERF_REG_ARM64_X27:
		वापस "x27";
	हाल PERF_REG_ARM64_X28:
		वापस "x28";
	हाल PERF_REG_ARM64_X29:
		वापस "x29";
	हाल PERF_REG_ARM64_SP:
		वापस "sp";
	हाल PERF_REG_ARM64_LR:
		वापस "lr";
	हाल PERF_REG_ARM64_PC:
		वापस "pc";
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
