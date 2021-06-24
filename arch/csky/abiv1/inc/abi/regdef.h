<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_REGDEF_H
#घोषणा __ASM_CSKY_REGDEF_H

#अगर_घोषित __ASSEMBLY__
#घोषणा syscallid	r1
#अन्यथा
#घोषणा syscallid	"r1"
#पूर्ण_अगर

#घोषणा regs_syscallid(regs) regs->regs[9]
#घोषणा regs_fp(regs) regs->regs[2]

/*
 * PSR क्रमmat:
 * | 31 | 30-24 | 23-16 | 15 14 | 13-0 |
 *   S     CPID     VEC     TM
 *
 *    S: Super Mode
 * CPID: Coprocessor id, only 15 क्रम MMU
 *  VEC: Exception Number
 *   TM: Trace Mode
 */
#घोषणा DEFAULT_PSR_VALUE	0x8f000000

#घोषणा SYSTRACE_SAVENUM	2

#घोषणा TRAP0_SIZE		2

#पूर्ण_अगर /* __ASM_CSKY_REGDEF_H */
