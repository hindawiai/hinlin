<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_PERF_REGS_H
#घोषणा ARCH_PERF_REGS_H

#समावेश <मानककोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/perf_regs.h>

#घोषणा PERF_REGS_MAX PERF_REG_MIPS_MAX
#घोषणा PERF_REG_IP PERF_REG_MIPS_PC
#घोषणा PERF_REG_SP PERF_REG_MIPS_R29

#घोषणा PERF_REGS_MASK ((1ULL << PERF_REG_MIPS_MAX) - 1)

अटल अंतरभूत स्थिर अक्षर *__perf_reg_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PERF_REG_MIPS_PC:
		वापस "PC";
	हाल PERF_REG_MIPS_R1:
		वापस "$1";
	हाल PERF_REG_MIPS_R2:
		वापस "$2";
	हाल PERF_REG_MIPS_R3:
		वापस "$3";
	हाल PERF_REG_MIPS_R4:
		वापस "$4";
	हाल PERF_REG_MIPS_R5:
		वापस "$5";
	हाल PERF_REG_MIPS_R6:
		वापस "$6";
	हाल PERF_REG_MIPS_R7:
		वापस "$7";
	हाल PERF_REG_MIPS_R8:
		वापस "$8";
	हाल PERF_REG_MIPS_R9:
		वापस "$9";
	हाल PERF_REG_MIPS_R10:
		वापस "$10";
	हाल PERF_REG_MIPS_R11:
		वापस "$11";
	हाल PERF_REG_MIPS_R12:
		वापस "$12";
	हाल PERF_REG_MIPS_R13:
		वापस "$13";
	हाल PERF_REG_MIPS_R14:
		वापस "$14";
	हाल PERF_REG_MIPS_R15:
		वापस "$15";
	हाल PERF_REG_MIPS_R16:
		वापस "$16";
	हाल PERF_REG_MIPS_R17:
		वापस "$17";
	हाल PERF_REG_MIPS_R18:
		वापस "$18";
	हाल PERF_REG_MIPS_R19:
		वापस "$19";
	हाल PERF_REG_MIPS_R20:
		वापस "$20";
	हाल PERF_REG_MIPS_R21:
		वापस "$21";
	हाल PERF_REG_MIPS_R22:
		वापस "$22";
	हाल PERF_REG_MIPS_R23:
		वापस "$23";
	हाल PERF_REG_MIPS_R24:
		वापस "$24";
	हाल PERF_REG_MIPS_R25:
		वापस "$25";
	हाल PERF_REG_MIPS_R28:
		वापस "$28";
	हाल PERF_REG_MIPS_R29:
		वापस "$29";
	हाल PERF_REG_MIPS_R30:
		वापस "$30";
	हाल PERF_REG_MIPS_R31:
		वापस "$31";
	शेष:
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* ARCH_PERF_REGS_H */
