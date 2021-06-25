<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <elfutils/libdwfl.h>
#समावेश "../../util/unwind-libdw.h"
#समावेश "../../util/perf_regs.h"
#समावेश "../../util/event.h"

bool libdw__arch_set_initial_रेजिस्टरs(Dwfl_Thपढ़ो *thपढ़ो, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[PERF_REG_ARM_MAX];

#घोषणा REG(r) (अणु						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_ARM_##r);	\
	val;							\
पूर्ण)

	dwarf_regs[0]  = REG(R0);
	dwarf_regs[1]  = REG(R1);
	dwarf_regs[2]  = REG(R2);
	dwarf_regs[3]  = REG(R3);
	dwarf_regs[4]  = REG(R4);
	dwarf_regs[5]  = REG(R5);
	dwarf_regs[6]  = REG(R6);
	dwarf_regs[7]  = REG(R7);
	dwarf_regs[8]  = REG(R8);
	dwarf_regs[9]  = REG(R9);
	dwarf_regs[10] = REG(R10);
	dwarf_regs[11] = REG(FP);
	dwarf_regs[12] = REG(IP);
	dwarf_regs[13] = REG(SP);
	dwarf_regs[14] = REG(LR);
	dwarf_regs[15] = REG(PC);

	वापस dwfl_thपढ़ो_state_रेजिस्टरs(thपढ़ो, 0, PERF_REG_ARM_MAX,
					   dwarf_regs);
पूर्ण
