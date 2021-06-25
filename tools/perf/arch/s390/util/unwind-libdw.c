<शैली गुरु>
#समावेश <linux/kernel.h>
#समावेश <elfutils/libdwfl.h>
#समावेश "../../util/unwind-libdw.h"
#समावेश "../../util/perf_regs.h"
#समावेश "../../util/event.h"
#समावेश "dwarf-regs-table.h"


bool libdw__arch_set_initial_रेजिस्टरs(Dwfl_Thपढ़ो *thपढ़ो, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[ARRAY_SIZE(s390_dwarf_regs)];

#घोषणा REG(r) (अणु						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_S390_##r);	\
	val;							\
पूर्ण)
	/*
	 * For DWARF रेजिस्टर mapping details,
	 * see also perf/arch/s390/include/dwarf-regs-table.h
	 */
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

	dwarf_regs[16] = REG(FP0);
	dwarf_regs[17] = REG(FP2);
	dwarf_regs[18] = REG(FP4);
	dwarf_regs[19] = REG(FP6);
	dwarf_regs[20] = REG(FP1);
	dwarf_regs[21] = REG(FP3);
	dwarf_regs[22] = REG(FP5);
	dwarf_regs[23] = REG(FP7);
	dwarf_regs[24] = REG(FP8);
	dwarf_regs[25] = REG(FP10);
	dwarf_regs[26] = REG(FP12);
	dwarf_regs[27] = REG(FP14);
	dwarf_regs[28] = REG(FP9);
	dwarf_regs[29] = REG(FP11);
	dwarf_regs[30] = REG(FP13);
	dwarf_regs[31] = REG(FP15);

	dwarf_regs[64] = REG(MASK);
	dwarf_regs[65] = REG(PC);

	dwfl_thपढ़ो_state_रेजिस्टर_pc(thपढ़ो, dwarf_regs[65]);
	वापस dwfl_thपढ़ो_state_रेजिस्टरs(thपढ़ो, 0, 32, dwarf_regs);
पूर्ण
