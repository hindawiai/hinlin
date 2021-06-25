<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_KGDB_H_
#घोषणा __ASM_KGDB_H_

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/sgidefs.h>

#अगर (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2) || \
	(_MIPS_ISA == _MIPS_ISA_MIPS32)

#घोषणा KGDB_GDB_REG_SIZE	32
#घोषणा GDB_SIZखातापूर्ण_REG		माप(u32)

#या_अगर (_MIPS_ISA == _MIPS_ISA_MIPS3) || (_MIPS_ISA == _MIPS_ISA_MIPS4) || \
	(_MIPS_ISA == _MIPS_ISA_MIPS64)

#अगर_घोषित CONFIG_32BIT
#घोषणा KGDB_GDB_REG_SIZE	32
#घोषणा GDB_SIZखातापूर्ण_REG		माप(u32)
#अन्यथा /* CONFIG_CPU_32BIT */
#घोषणा KGDB_GDB_REG_SIZE	64
#घोषणा GDB_SIZखातापूर्ण_REG		माप(u64)
#पूर्ण_अगर
#अन्यथा
#त्रुटि "Need to set KGDB_GDB_REG_SIZE for MIPS ISA"
#पूर्ण_अगर /* _MIPS_ISA */

#घोषणा BUFMAX			2048
#घोषणा DBG_MAX_REG_NUM		72
#घोषणा NUMREGBYTES		(DBG_MAX_REG_NUM * माप(GDB_SIZखातापूर्ण_REG))
#घोषणा NUMCRITREGBYTES		(12 * माप(GDB_SIZखातापूर्ण_REG))
#घोषणा BREAK_INSTR_SIZE	4
#घोषणा CACHE_FLUSH_IS_SAFE	0

बाह्य व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम);
बाह्य व्योम *saved_vectors[32];
बाह्य व्योम handle_exception(काष्ठा pt_regs *regs);
बाह्य व्योम अवरोधinst(व्योम);
बाह्य पूर्णांक kgdb_ll_trap(पूर्णांक cmd, स्थिर अक्षर *str,
			काष्ठा pt_regs *regs, दीर्घ err, पूर्णांक trap, पूर्णांक sig);

#पूर्ण_अगर				/* __KERNEL__ */

#पूर्ण_अगर /* __ASM_KGDB_H_ */
