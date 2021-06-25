<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 * arch/ia64/include/यंत्र/native/irq.h
 *
 * Copyright (c) 2008 Isaku Yamahata <yamahata at valinux co jp>
 *                    VA Linux Systems Japan K.K.
 */

#अगर_अघोषित _ASM_IA64_NATIVE_IRQ_H
#घोषणा _ASM_IA64_NATIVE_IRQ_H

#घोषणा NR_VECTORS	256

#अगर (NR_VECTORS + 32 * NR_CPUS) < 1024
#घोषणा IA64_NATIVE_NR_IRQS (NR_VECTORS + 32 * NR_CPUS)
#अन्यथा
#घोषणा IA64_NATIVE_NR_IRQS 1024
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IA64_NATIVE_IRQ_H */
