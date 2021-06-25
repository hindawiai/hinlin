<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_KDEBUG_H
#घोषणा _SPARC64_KDEBUG_H

काष्ठा pt_regs;

व्योम bad_trap(काष्ठा pt_regs *, दीर्घ);

/* Grossly misnamed. */
क्रमागत die_val अणु
	DIE_OOPS = 1,
	DIE_DEBUG,	/* ta 0x70 */
	DIE_DEBUG_2,	/* ta 0x71 */
	DIE_BPT,	/* ta 0x73 */
	DIE_SSTEP,	/* ta 0x74 */
	DIE_DIE,
	DIE_TRAP,
	DIE_TRAP_TL1,
	DIE_CALL,
	DIE_NMI,
	DIE_NMIWATCHDOG,
पूर्ण;

#पूर्ण_अगर
