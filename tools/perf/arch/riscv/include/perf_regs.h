<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd. */

#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

#घोषणा PERF_REGS_MASK	((1ULL << PERF_REG_RISCV_MAX) - 1)
#घोषणा PERF_REGS_MAX	PERF_REG_RISCV_MAX
#अगर __riscv_xlen == 64
#घोषणा PERF_SAMPLE_REGS_ABI    PERF_SAMPLE_REGS_ABI_64
#अन्यथा
#घोषणा PERF_SAMPLE_REGS_ABI	PERF_SAMPLE_REGS_ABI_32
#पूर्ण_अगर

#घोषणा PERF_REG_IP	PERF_REG_RISCV_PC
#घोषणा PERF_REG_SP	PERF_REG_RISCV_SP

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_RISCV_PC:
		वापस "pc";
	हाल PERF_REG_RISCV_RA:
		वापस "ra";
	हाल PERF_REG_RISCV_SP:
		वापस "sp";
	हाल PERF_REG_RISCV_GP:
		वापस "gp";
	हाल PERF_REG_RISCV_TP:
		वापस "tp";
	हाल PERF_REG_RISCV_T0:
		वापस "t0";
	हाल PERF_REG_RISCV_T1:
		वापस "t1";
	हाल PERF_REG_RISCV_T2:
		वापस "t2";
	हाल PERF_REG_RISCV_S0:
		वापस "s0";
	हाल PERF_REG_RISCV_S1:
		वापस "s1";
	हाल PERF_REG_RISCV_A0:
		वापस "a0";
	हाल PERF_REG_RISCV_A1:
		वापस "a1";
	हाल PERF_REG_RISCV_A2:
		वापस "a2";
	हाल PERF_REG_RISCV_A3:
		वापस "a3";
	हाल PERF_REG_RISCV_A4:
		वापस "a4";
	हाल PERF_REG_RISCV_A5:
		वापस "a5";
	हाल PERF_REG_RISCV_A6:
		वापस "a6";
	हाल PERF_REG_RISCV_A7:
		वापस "a7";
	हाल PERF_REG_RISCV_S2:
		वापस "s2";
	हाल PERF_REG_RISCV_S3:
		वापस "s3";
	हाल PERF_REG_RISCV_S4:
		वापस "s4";
	हाल PERF_REG_RISCV_S5:
		वापस "s5";
	हाल PERF_REG_RISCV_S6:
		वापस "s6";
	हाल PERF_REG_RISCV_S7:
		वापस "s7";
	हाल PERF_REG_RISCV_S8:
		वापस "s8";
	हाल PERF_REG_RISCV_S9:
		वापस "s9";
	हाल PERF_REG_RISCV_S10:
		वापस "s10";
	हाल PERF_REG_RISCV_S11:
		वापस "s11";
	हाल PERF_REG_RISCV_T3:
		वापस "t3";
	हाल PERF_REG_RISCV_T4:
		वापस "t4";
	हाल PERF_REG_RISCV_T5:
		वापस "t5";
	हाल PERF_REG_RISCV_T6:
		वापस "t6";
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
