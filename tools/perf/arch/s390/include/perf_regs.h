<शैली गुरु>
#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

व्योम perf_regs_load(u64 *regs);

#घोषणा PERF_REGS_MASK ((1ULL << PERF_REG_S390_MAX) - 1)
#घोषणा PERF_REGS_MAX PERF_REG_S390_MAX
#घोषणा PERF_SAMPLE_REGS_ABI PERF_SAMPLE_REGS_ABI_64

#घोषणा PERF_REG_IP PERF_REG_S390_PC
#घोषणा PERF_REG_SP PERF_REG_S390_R15

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_S390_R0:
		वापस "R0";
	हाल PERF_REG_S390_R1:
		वापस "R1";
	हाल PERF_REG_S390_R2:
		वापस "R2";
	हाल PERF_REG_S390_R3:
		वापस "R3";
	हाल PERF_REG_S390_R4:
		वापस "R4";
	हाल PERF_REG_S390_R5:
		वापस "R5";
	हाल PERF_REG_S390_R6:
		वापस "R6";
	हाल PERF_REG_S390_R7:
		वापस "R7";
	हाल PERF_REG_S390_R8:
		वापस "R8";
	हाल PERF_REG_S390_R9:
		वापस "R9";
	हाल PERF_REG_S390_R10:
		वापस "R10";
	हाल PERF_REG_S390_R11:
		वापस "R11";
	हाल PERF_REG_S390_R12:
		वापस "R12";
	हाल PERF_REG_S390_R13:
		वापस "R13";
	हाल PERF_REG_S390_R14:
		वापस "R14";
	हाल PERF_REG_S390_R15:
		वापस "R15";
	हाल PERF_REG_S390_FP0:
		वापस "FP0";
	हाल PERF_REG_S390_FP1:
		वापस "FP1";
	हाल PERF_REG_S390_FP2:
		वापस "FP2";
	हाल PERF_REG_S390_FP3:
		वापस "FP3";
	हाल PERF_REG_S390_FP4:
		वापस "FP4";
	हाल PERF_REG_S390_FP5:
		वापस "FP5";
	हाल PERF_REG_S390_FP6:
		वापस "FP6";
	हाल PERF_REG_S390_FP7:
		वापस "FP7";
	हाल PERF_REG_S390_FP8:
		वापस "FP8";
	हाल PERF_REG_S390_FP9:
		वापस "FP9";
	हाल PERF_REG_S390_FP10:
		वापस "FP10";
	हाल PERF_REG_S390_FP11:
		वापस "FP11";
	हाल PERF_REG_S390_FP12:
		वापस "FP12";
	हाल PERF_REG_S390_FP13:
		वापस "FP13";
	हाल PERF_REG_S390_FP14:
		वापस "FP14";
	हाल PERF_REG_S390_FP15:
		वापस "FP15";
	हाल PERF_REG_S390_MASK:
		वापस "MASK";
	हाल PERF_REG_S390_PC:
		वापस "PC";
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
