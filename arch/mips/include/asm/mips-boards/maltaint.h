<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000,2012 MIPS Technologies, Inc.  All rights reserved.
 *	Carsten Langgaard <carstenl@mips.com>
 *	Steven J. Hill <sjhill@mips.com>
 */
#अगर_अघोषित _MIPS_MALTAINT_H
#घोषणा _MIPS_MALTAINT_H

/*
 * Interrupts 0..15 are used क्रम Malta ISA compatible पूर्णांकerrupts
 */
#घोषणा MALTA_INT_BASE		0

/* CPU पूर्णांकerrupt offsets */
#घोषणा MIPSCPU_INT_SW0		0
#घोषणा MIPSCPU_INT_SW1		1
#घोषणा MIPSCPU_INT_MB0		2
#घोषणा MIPSCPU_INT_I8259A	MIPSCPU_INT_MB0
#घोषणा MIPSCPU_INT_GIC		MIPSCPU_INT_MB0 /* GIC chained पूर्णांकerrupt */
#घोषणा MIPSCPU_INT_MB1		3
#घोषणा MIPSCPU_INT_SMI		MIPSCPU_INT_MB1
#घोषणा MIPSCPU_INT_MB2		4
#घोषणा MIPSCPU_INT_MB3		5
#घोषणा MIPSCPU_INT_COREHI	MIPSCPU_INT_MB3
#घोषणा MIPSCPU_INT_MB4		6
#घोषणा MIPSCPU_INT_CORELO	MIPSCPU_INT_MB4

/*
 * Interrupts 96..127 are used क्रम Soc-it Classic पूर्णांकerrupts
 */
#घोषणा MSC01C_INT_BASE		96

/* SOC-it Classic पूर्णांकerrupt offsets */
#घोषणा MSC01C_INT_TMR		0
#घोषणा MSC01C_INT_PCI		1

/*
 * Interrupts 96..127 are used क्रम Soc-it EIC पूर्णांकerrupts
 */
#घोषणा MSC01E_INT_BASE		96

/* SOC-it EIC पूर्णांकerrupt offsets */
#घोषणा MSC01E_INT_SW0		1
#घोषणा MSC01E_INT_SW1		2
#घोषणा MSC01E_INT_MB0		3
#घोषणा MSC01E_INT_I8259A	MSC01E_INT_MB0
#घोषणा MSC01E_INT_MB1		4
#घोषणा MSC01E_INT_SMI		MSC01E_INT_MB1
#घोषणा MSC01E_INT_MB2		5
#घोषणा MSC01E_INT_MB3		6
#घोषणा MSC01E_INT_COREHI	MSC01E_INT_MB3
#घोषणा MSC01E_INT_MB4		7
#घोषणा MSC01E_INT_CORELO	MSC01E_INT_MB4
#घोषणा MSC01E_INT_TMR		8
#घोषणा MSC01E_INT_PCI		9
#घोषणा MSC01E_INT_PERFCTR	10
#घोषणा MSC01E_INT_CPUCTR	11

#पूर्ण_अगर /* !(_MIPS_MALTAINT_H) */
