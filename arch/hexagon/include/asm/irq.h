<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_IRQ_H_
#घोषणा _ASM_IRQ_H_

/* Number of first-level पूर्णांकerrupts associated with the CPU core. */
#घोषणा HEXAGON_CPUINTS 32

/*
 * Must define NR_IRQS beक्रमe including <यंत्र-generic/irq.h>
 * 64 == the two SIRC's, 176 == the two gpio's
 *
 * IRQ configuration is still in flux; defining this to a comक्रमtably
 * large number.
 */
#घोषणा NR_IRQS 512

#समावेश <यंत्र-generic/irq.h>

#पूर्ण_अगर
