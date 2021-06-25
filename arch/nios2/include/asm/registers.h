<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 */

#अगर_अघोषित _ASM_NIOS2_REGISTERS_H
#घोषणा _ASM_NIOS2_REGISTERS_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/cpuinfo.h>
#पूर्ण_अगर

/* control रेजिस्टर numbers */
#घोषणा CTL_STATUS	0
#घोषणा CTL_ESTATUS	1
#घोषणा CTL_BSTATUS	2
#घोषणा CTL_IENABLE	3
#घोषणा CTL_IPENDING	4
#घोषणा CTL_CPUID	5
#घोषणा CTL_RSV1	6
#घोषणा CTL_EXCEPTION	7
#घोषणा CTL_PTEADDR	8
#घोषणा CTL_TLBACC	9
#घोषणा CTL_TLBMISC	10
#घोषणा CTL_RSV2	11
#घोषणा CTL_BADADDR	12
#घोषणा CTL_CONFIG	13
#घोषणा CTL_MPUBASE	14
#घोषणा CTL_MPUACC	15

/* access control रेजिस्टरs using GCC builtins */
#घोषणा RDCTL(r)	__builtin_rdctl(r)
#घोषणा WRCTL(r, v)	__builtin_wrctl(r, v)

/* status रेजिस्टर bits */
#घोषणा STATUS_PIE	(1 << 0)	/* processor पूर्णांकerrupt enable */
#घोषणा STATUS_U	(1 << 1)	/* user mode */
#घोषणा STATUS_EH	(1 << 2)	/* Exception mode */

/* estatus रेजिस्टर bits */
#घोषणा ESTATUS_EPIE	(1 << 0)	/* processor पूर्णांकerrupt enable */
#घोषणा ESTATUS_EU	(1 << 1)	/* user mode */
#घोषणा ESTATUS_EH	(1 << 2)	/* Exception mode */

/* tlbmisc रेजिस्टर bits */
#घोषणा TLBMISC_PID_SHIFT	4
#अगर_अघोषित __ASSEMBLY__
#घोषणा TLBMISC_PID_MASK	((1UL << cpuinfo.tlb_pid_num_bits) - 1)
#पूर्ण_अगर
#घोषणा TLBMISC_WAY_MASK	0xf
#घोषणा TLBMISC_WAY_SHIFT	20

#घोषणा TLBMISC_PID	(TLBMISC_PID_MASK << TLBMISC_PID_SHIFT)	/* TLB PID */
#घोषणा TLBMISC_WE	(1 << 18)	/* TLB ग_लिखो enable */
#घोषणा TLBMISC_RD	(1 << 19)	/* TLB पढ़ो */
#घोषणा TLBMISC_WAY	(TLBMISC_WAY_MASK << TLBMISC_WAY_SHIFT) /* TLB way */

#पूर्ण_अगर /* _ASM_NIOS2_REGISTERS_H */
