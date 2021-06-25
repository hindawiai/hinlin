<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

#घोषणा PERF_REGS_MASK	((1ULL << PERF_REG_CSKY_MAX) - 1)
#घोषणा PERF_REGS_MAX	PERF_REG_CSKY_MAX
#घोषणा PERF_SAMPLE_REGS_ABI	PERF_SAMPLE_REGS_ABI_32

#घोषणा PERF_REG_IP	PERF_REG_CSKY_PC
#घोषणा PERF_REG_SP	PERF_REG_CSKY_SP

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_CSKY_A0:
		वापस "a0";
	हाल PERF_REG_CSKY_A1:
		वापस "a1";
	हाल PERF_REG_CSKY_A2:
		वापस "a2";
	हाल PERF_REG_CSKY_A3:
		वापस "a3";
	हाल PERF_REG_CSKY_REGS0:
		वापस "regs0";
	हाल PERF_REG_CSKY_REGS1:
		वापस "regs1";
	हाल PERF_REG_CSKY_REGS2:
		वापस "regs2";
	हाल PERF_REG_CSKY_REGS3:
		वापस "regs3";
	हाल PERF_REG_CSKY_REGS4:
		वापस "regs4";
	हाल PERF_REG_CSKY_REGS5:
		वापस "regs5";
	हाल PERF_REG_CSKY_REGS6:
		वापस "regs6";
	हाल PERF_REG_CSKY_REGS7:
		वापस "regs7";
	हाल PERF_REG_CSKY_REGS8:
		वापस "regs8";
	हाल PERF_REG_CSKY_REGS9:
		वापस "regs9";
	हाल PERF_REG_CSKY_SP:
		वापस "sp";
	हाल PERF_REG_CSKY_LR:
		वापस "lr";
	हाल PERF_REG_CSKY_PC:
		वापस "pc";
#अगर defined(__CSKYABIV2__)
	हाल PERF_REG_CSKY_EXREGS0:
		वापस "exregs0";
	हाल PERF_REG_CSKY_EXREGS1:
		वापस "exregs1";
	हाल PERF_REG_CSKY_EXREGS2:
		वापस "exregs2";
	हाल PERF_REG_CSKY_EXREGS3:
		वापस "exregs3";
	हाल PERF_REG_CSKY_EXREGS4:
		वापस "exregs4";
	हाल PERF_REG_CSKY_EXREGS5:
		वापस "exregs5";
	हाल PERF_REG_CSKY_EXREGS6:
		वापस "exregs6";
	हाल PERF_REG_CSKY_EXREGS7:
		वापस "exregs7";
	हाल PERF_REG_CSKY_EXREGS8:
		वापस "exregs8";
	हाल PERF_REG_CSKY_EXREGS9:
		वापस "exregs9";
	हाल PERF_REG_CSKY_EXREGS10:
		वापस "exregs10";
	हाल PERF_REG_CSKY_EXREGS11:
		वापस "exregs11";
	हाल PERF_REG_CSKY_EXREGS12:
		वापस "exregs12";
	हाल PERF_REG_CSKY_EXREGS13:
		वापस "exregs13";
	हाल PERF_REG_CSKY_EXREGS14:
		वापस "exregs14";
	हाल PERF_REG_CSKY_TLS:
		वापस "tls";
	हाल PERF_REG_CSKY_HI:
		वापस "hi";
	हाल PERF_REG_CSKY_LO:
		वापस "lo";
#पूर्ण_अगर
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
