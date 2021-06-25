<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2009 Freescale Semiconductor, Inc.
 *
 * provides masks and opcode images क्रम use by code generation, emulation
 * and क्रम inकाष्ठाions that older assemblers might not know about
 */
#अगर_अघोषित _ASM_POWERPC_PPC_OPCODE_H
#घोषणा _ASM_POWERPC_PPC_OPCODE_H


#  define stringअगरy_in_c(...)	__VA_ARGS__
#  define ASM_CONST(x)		x


#घोषणा PPC_INST_VCMPEQUD_RC		0x100000c7
#घोषणा PPC_INST_VCMPEQUB_RC		0x10000006

#घोषणा __PPC_RC21     (0x1 << 10)

/* macros to insert fields पूर्णांकo opcodes */
#घोषणा ___PPC_RA(a)	(((a) & 0x1f) << 16)
#घोषणा ___PPC_RB(b)	(((b) & 0x1f) << 11)
#घोषणा ___PPC_RS(s)	(((s) & 0x1f) << 21)
#घोषणा ___PPC_RT(t)	___PPC_RS(t)

#घोषणा VCMPEQUD_RC(vrt, vra, vrb)	stringअगरy_in_c(.दीर्घ PPC_INST_VCMPEQUD_RC | \
			      ___PPC_RT(vrt) | ___PPC_RA(vra) | \
			      ___PPC_RB(vrb) | __PPC_RC21)

#घोषणा VCMPEQUB_RC(vrt, vra, vrb)	stringअगरy_in_c(.दीर्घ PPC_INST_VCMPEQUB_RC | \
			      ___PPC_RT(vrt) | ___PPC_RA(vra) | \
			      ___PPC_RB(vrb) | __PPC_RC21)

#पूर्ण_अगर /* _ASM_POWERPC_PPC_OPCODE_H */
