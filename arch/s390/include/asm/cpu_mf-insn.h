<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम CPU-MF inकाष्ठाions
 *
 * Copyright IBM Corp. 2019
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */
#अगर_अघोषित _ASM_S390_CPU_MF_INSN_H
#घोषणा _ASM_S390_CPU_MF_INSN_H

#अगर_घोषित __ASSEMBLY__

/* Macro to generate the STCCTM inकाष्ठाion with a customized
 * M3 field designating the counter set.
 */
.macro	STCCTM	r1 m3 db2
	.insn	rsy,0xeb0000000017,\ल1,\m3 & 0xf,\db2
.endm

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
