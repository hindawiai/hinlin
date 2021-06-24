<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_KGDB_H
#घोषणा _SPARC_KGDB_H

#अगर_घोषित CONFIG_SPARC32
#घोषणा BUFMAX			2048
#अन्यथा
#घोषणा BUFMAX			4096
#पूर्ण_अगर

क्रमागत regnames अणु
	GDB_G0, GDB_G1, GDB_G2, GDB_G3, GDB_G4, GDB_G5, GDB_G6, GDB_G7,
	GDB_O0, GDB_O1, GDB_O2, GDB_O3, GDB_O4, GDB_O5, GDB_SP, GDB_O7,
	GDB_L0, GDB_L1, GDB_L2, GDB_L3, GDB_L4, GDB_L5, GDB_L6, GDB_L7,
	GDB_I0, GDB_I1, GDB_I2, GDB_I3, GDB_I4, GDB_I5, GDB_FP, GDB_I7,
	GDB_F0,
	GDB_F31 = GDB_F0 + 31,
#अगर_घोषित CONFIG_SPARC32
	GDB_Y, GDB_PSR, GDB_WIM, GDB_TBR, GDB_PC, GDB_NPC,
	GDB_FSR, GDB_CSR,
#अन्यथा
	GDB_F32 = GDB_F0 + 32,
	GDB_F62 = GDB_F32 + 15,
	GDB_PC, GDB_NPC, GDB_STATE, GDB_FSR, GDB_FPRS, GDB_Y,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SPARC32
#घोषणा NUMREGBYTES		((GDB_CSR + 1) * 4)
#अन्यथा
#घोषणा NUMREGBYTES		((GDB_Y + 1) * 8)
#पूर्ण_अगर

काष्ठा pt_regs;
यंत्रlinkage व्योम kgdb_trap(अचिन्हित दीर्घ trap_level, काष्ठा pt_regs *regs);

व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम);

#घोषणा BREAK_INSTR_SIZE	4
#घोषणा CACHE_FLUSH_IS_SAFE	1

#पूर्ण_अगर /* _SPARC_KGDB_H */
