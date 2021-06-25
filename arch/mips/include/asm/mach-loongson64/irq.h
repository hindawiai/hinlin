<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_LOONGSON64_IRQ_H_
#घोषणा __ASM_MACH_LOONGSON64_IRQ_H_

/* cpu core पूर्णांकerrupt numbers */
#घोषणा NR_IRQS_LEGACY		16
#घोषणा NR_MIPS_CPU_IRQS	8
#घोषणा NR_MAX_CHAINED_IRQS	40 /* Chained IRQs means those not directly used by devices */
#घोषणा NR_IRQS			(NR_IRQS_LEGACY + NR_MIPS_CPU_IRQS + NR_MAX_CHAINED_IRQS + 256)

#घोषणा MIPS_CPU_IRQ_BASE 	NR_IRQS_LEGACY

#समावेश <यंत्र/mach-generic/irq.h>

#पूर्ण_अगर /* __ASM_MACH_LOONGSON64_IRQ_H_ */
