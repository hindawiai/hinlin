<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <elfutils/libdwfl.h>
#समावेश "../../../util/unwind-libdw.h"
#समावेश "../../../util/perf_regs.h"
#समावेश "../../../util/event.h"

bool libdw__arch_set_initial_रेजिस्टरs(Dwfl_Thपढ़ो *thपढ़ो, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[17];
	अचिन्हित nregs;

#घोषणा REG(r) (अणु						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_X86_##r);	\
	val;							\
पूर्ण)

	अगर (user_regs->abi == PERF_SAMPLE_REGS_ABI_32) अणु
		dwarf_regs[0] = REG(AX);
		dwarf_regs[1] = REG(CX);
		dwarf_regs[2] = REG(DX);
		dwarf_regs[3] = REG(BX);
		dwarf_regs[4] = REG(SP);
		dwarf_regs[5] = REG(BP);
		dwarf_regs[6] = REG(SI);
		dwarf_regs[7] = REG(DI);
		dwarf_regs[8] = REG(IP);
		nregs = 9;
	पूर्ण अन्यथा अणु
		dwarf_regs[0]  = REG(AX);
		dwarf_regs[1]  = REG(DX);
		dwarf_regs[2]  = REG(CX);
		dwarf_regs[3]  = REG(BX);
		dwarf_regs[4]  = REG(SI);
		dwarf_regs[5]  = REG(DI);
		dwarf_regs[6]  = REG(BP);
		dwarf_regs[7]  = REG(SP);
		dwarf_regs[8]  = REG(R8);
		dwarf_regs[9]  = REG(R9);
		dwarf_regs[10] = REG(R10);
		dwarf_regs[11] = REG(R11);
		dwarf_regs[12] = REG(R12);
		dwarf_regs[13] = REG(R13);
		dwarf_regs[14] = REG(R14);
		dwarf_regs[15] = REG(R15);
		dwarf_regs[16] = REG(IP);
		nregs = 17;
	पूर्ण

	वापस dwfl_thपढ़ो_state_रेजिस्टरs(thपढ़ो, 0, nregs, dwarf_regs);
पूर्ण
