<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <elfutils/libdwfl.h>
#समावेश <linux/kernel.h>
#समावेश "../../../util/unwind-libdw.h"
#समावेश "../../../util/perf_regs.h"
#समावेश "../../../util/event.h"

/* See backends/ppc_initreg.c and backends/ppc_regs.c in elfutils.  */
अटल स्थिर पूर्णांक special_regs[3][2] = अणु
	अणु 65, PERF_REG_POWERPC_LINK पूर्ण,
	अणु 101, PERF_REG_POWERPC_XER पूर्ण,
	अणु 109, PERF_REG_POWERPC_CTR पूर्ण,
पूर्ण;

bool libdw__arch_set_initial_रेजिस्टरs(Dwfl_Thपढ़ो *thपढ़ो, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[32], dwarf_nip;
	माप_प्रकार i;

#घोषणा REG(r) (अणु						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_POWERPC_##r);	\
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
	dwarf_regs[11] = REG(R11);
	dwarf_regs[12] = REG(R12);
	dwarf_regs[13] = REG(R13);
	dwarf_regs[14] = REG(R14);
	dwarf_regs[15] = REG(R15);
	dwarf_regs[16] = REG(R16);
	dwarf_regs[17] = REG(R17);
	dwarf_regs[18] = REG(R18);
	dwarf_regs[19] = REG(R19);
	dwarf_regs[20] = REG(R20);
	dwarf_regs[21] = REG(R21);
	dwarf_regs[22] = REG(R22);
	dwarf_regs[23] = REG(R23);
	dwarf_regs[24] = REG(R24);
	dwarf_regs[25] = REG(R25);
	dwarf_regs[26] = REG(R26);
	dwarf_regs[27] = REG(R27);
	dwarf_regs[28] = REG(R28);
	dwarf_regs[29] = REG(R29);
	dwarf_regs[30] = REG(R30);
	dwarf_regs[31] = REG(R31);
	अगर (!dwfl_thपढ़ो_state_रेजिस्टरs(thपढ़ो, 0, 32, dwarf_regs))
		वापस false;

	dwarf_nip = REG(NIP);
	dwfl_thपढ़ो_state_रेजिस्टर_pc(thपढ़ो, dwarf_nip);
	क्रम (i = 0; i < ARRAY_SIZE(special_regs); i++) अणु
		Dwarf_Word val = 0;
		perf_reg_value(&val, user_regs, special_regs[i][1]);
		अगर (!dwfl_thपढ़ो_state_रेजिस्टरs(thपढ़ो,
						 special_regs[i][0], 1,
						 &val))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
