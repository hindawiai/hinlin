<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __IP30_COMMON_H
#घोषणा __IP30_COMMON_H

/*
 * Power Switch is wired via BaseIO BRIDGE slot #6.
 *
 * ACFail is wired via BaseIO BRIDGE slot #7.
 */
#घोषणा IP30_POWER_IRQ		HEART_L2_INT_POWER_BTN

#घोषणा IP30_HEART_L0_IRQ	(MIPS_CPU_IRQ_BASE + 2)
#घोषणा IP30_HEART_L1_IRQ	(MIPS_CPU_IRQ_BASE + 3)
#घोषणा IP30_HEART_L2_IRQ	(MIPS_CPU_IRQ_BASE + 4)
#घोषणा IP30_HEART_TIMER_IRQ	(MIPS_CPU_IRQ_BASE + 5)
#घोषणा IP30_HEART_ERR_IRQ	(MIPS_CPU_IRQ_BASE + 6)

बाह्य व्योम __init ip30_install_ipi(व्योम);
बाह्य काष्ठा plat_smp_ops ip30_smp_ops;
बाह्य व्योम __init ip30_per_cpu_init(व्योम);

#पूर्ण_अगर /* __IP30_COMMON_H */
