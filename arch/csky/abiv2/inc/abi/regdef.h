<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_REGDEF_H
#घोषणा __ASM_CSKY_REGDEF_H

#अगर_घोषित __ASSEMBLY__
#घोषणा syscallid	r7
#अन्यथा
#घोषणा syscallid	"r7"
#पूर्ण_अगर

#घोषणा regs_syscallid(regs) regs->regs[3]
#घोषणा regs_fp(regs) regs->regs[4]

/*
 * PSR क्रमmat:
 * | 31 | 30-24 | 23-16 | 15 14 | 13-10 | 9 | 8-0 |
 *   S              VEC     TM            MM
 *
 *   S: Super Mode
 * VEC: Exception Number
 *  TM: Trace Mode
 *  MM: Memory unaligned addr access
 */
#घोषणा DEFAULT_PSR_VALUE	0x80000200

#घोषणा SYSTRACE_SAVENUM	5

#घोषणा TRAP0_SIZE		4

#पूर्ण_अगर /* __ASM_CSKY_REGDEF_H */
