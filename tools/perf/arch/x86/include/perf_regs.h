<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

व्योम perf_regs_load(u64 *regs);

#घोषणा PERF_REGS_MAX PERF_REG_X86_XMM_MAX
#अगर_अघोषित HAVE_ARCH_X86_64_SUPPORT
#घोषणा PERF_REGS_MASK ((1ULL << PERF_REG_X86_32_MAX) - 1)
#घोषणा PERF_SAMPLE_REGS_ABI PERF_SAMPLE_REGS_ABI_32
#अन्यथा
#घोषणा REG_NOSUPPORT ((1ULL << PERF_REG_X86_DS) | \
		       (1ULL << PERF_REG_X86_ES) | \
		       (1ULL << PERF_REG_X86_FS) | \
		       (1ULL << PERF_REG_X86_GS))
#घोषणा PERF_REGS_MASK (((1ULL << PERF_REG_X86_64_MAX) - 1) & ~REG_NOSUPPORT)
#घोषणा PERF_SAMPLE_REGS_ABI PERF_SAMPLE_REGS_ABI_64
#पूर्ण_अगर
#घोषणा PERF_REG_IP PERF_REG_X86_IP
#घोषणा PERF_REG_SP PERF_REG_X86_SP

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_X86_AX:
		वापस "AX";
	हाल PERF_REG_X86_BX:
		वापस "BX";
	हाल PERF_REG_X86_CX:
		वापस "CX";
	हाल PERF_REG_X86_DX:
		वापस "DX";
	हाल PERF_REG_X86_SI:
		वापस "SI";
	हाल PERF_REG_X86_DI:
		वापस "DI";
	हाल PERF_REG_X86_BP:
		वापस "BP";
	हाल PERF_REG_X86_SP:
		वापस "SP";
	हाल PERF_REG_X86_IP:
		वापस "IP";
	हाल PERF_REG_X86_FLAGS:
		वापस "FLAGS";
	हाल PERF_REG_X86_CS:
		वापस "CS";
	हाल PERF_REG_X86_SS:
		वापस "SS";
	हाल PERF_REG_X86_DS:
		वापस "DS";
	हाल PERF_REG_X86_ES:
		वापस "ES";
	हाल PERF_REG_X86_FS:
		वापस "FS";
	हाल PERF_REG_X86_GS:
		वापस "GS";
#अगर_घोषित HAVE_ARCH_X86_64_SUPPORT
	हाल PERF_REG_X86_R8:
		वापस "R8";
	हाल PERF_REG_X86_R9:
		वापस "R9";
	हाल PERF_REG_X86_R10:
		वापस "R10";
	हाल PERF_REG_X86_R11:
		वापस "R11";
	हाल PERF_REG_X86_R12:
		वापस "R12";
	हाल PERF_REG_X86_R13:
		वापस "R13";
	हाल PERF_REG_X86_R14:
		वापस "R14";
	हाल PERF_REG_X86_R15:
		वापस "R15";
#पूर्ण_अगर /* HAVE_ARCH_X86_64_SUPPORT */

#घोषणा XMM(x) \
	हाल PERF_REG_X86_XMM ## x:	\
	हाल PERF_REG_X86_XMM ## x + 1:	\
		वापस "XMM" #x;
	XMM(0)
	XMM(1)
	XMM(2)
	XMM(3)
	XMM(4)
	XMM(5)
	XMM(6)
	XMM(7)
	XMM(8)
	XMM(9)
	XMM(10)
	XMM(11)
	XMM(12)
	XMM(13)
	XMM(14)
	XMM(15)
#अघोषित XMM
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
