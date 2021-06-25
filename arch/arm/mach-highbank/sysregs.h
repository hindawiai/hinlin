<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2011 Calxeda, Inc.
 */
#अगर_अघोषित _MACH_HIGHBANK__SYSREGS_H_
#घोषणा _MACH_HIGHBANK__SYSREGS_H_

#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश "core.h"

बाह्य व्योम __iomem *sregs_base;

#घोषणा HB_SREG_A9_PWR_REQ		0xf00
#घोषणा HB_SREG_A9_BOOT_STAT		0xf04
#घोषणा HB_SREG_A9_BOOT_DATA		0xf08

#घोषणा HB_PWR_SUSPEND			0
#घोषणा HB_PWR_SOFT_RESET		1
#घोषणा HB_PWR_HARD_RESET		2
#घोषणा HB_PWR_SHUTDOWN			3

#घोषणा SREG_CPU_PWR_CTRL(c)		(0x200 + ((c) * 4))

अटल अंतरभूत व्योम highbank_set_core_pwr(व्योम)
अणु
	पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(smp_processor_id()), 0);
	अगर (scu_base_addr)
		scu_घातer_mode(scu_base_addr, SCU_PM_POWEROFF);
	अन्यथा
		ग_लिखोl_relaxed(1, sregs_base + SREG_CPU_PWR_CTRL(cpu));
पूर्ण

अटल अंतरभूत व्योम highbank_clear_core_pwr(व्योम)
अणु
	पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(smp_processor_id()), 0);
	अगर (scu_base_addr)
		scu_घातer_mode(scu_base_addr, SCU_PM_NORMAL);
	अन्यथा
		ग_लिखोl_relaxed(0, sregs_base + SREG_CPU_PWR_CTRL(cpu));
पूर्ण

अटल अंतरभूत व्योम highbank_set_pwr_suspend(व्योम)
अणु
	ग_लिखोl(HB_PWR_SUSPEND, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_set_core_pwr();
पूर्ण

अटल अंतरभूत व्योम highbank_set_pwr_shutकरोwn(व्योम)
अणु
	ग_लिखोl(HB_PWR_SHUTDOWN, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_set_core_pwr();
पूर्ण

अटल अंतरभूत व्योम highbank_set_pwr_soft_reset(व्योम)
अणु
	ग_लिखोl(HB_PWR_SOFT_RESET, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_set_core_pwr();
पूर्ण

अटल अंतरभूत व्योम highbank_set_pwr_hard_reset(व्योम)
अणु
	ग_लिखोl(HB_PWR_HARD_RESET, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_set_core_pwr();
पूर्ण

अटल अंतरभूत व्योम highbank_clear_pwr_request(व्योम)
अणु
	ग_लिखोl(~0UL, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_clear_core_pwr();
पूर्ण

#पूर्ण_अगर
