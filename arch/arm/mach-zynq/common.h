<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file contains common function prototypes to aव्योम बाह्यs
 * in the c files.
 *
 *  Copyright (C) 2011 Xilinx
 */

#अगर_अघोषित __MACH_ZYNQ_COMMON_H__
#घोषणा __MACH_ZYNQ_COMMON_H__

बाह्य पूर्णांक zynq_slcr_init(व्योम);
बाह्य पूर्णांक zynq_early_slcr_init(व्योम);
बाह्य व्योम zynq_slcr_cpu_stop(पूर्णांक cpu);
बाह्य व्योम zynq_slcr_cpu_start(पूर्णांक cpu);
बाह्य bool zynq_slcr_cpu_state_पढ़ो(पूर्णांक cpu);
बाह्य व्योम zynq_slcr_cpu_state_ग_लिखो(पूर्णांक cpu, bool die);
बाह्य u32 zynq_slcr_get_device_id(व्योम);

#अगर_घोषित CONFIG_SMP
बाह्य अक्षर zynq_secondary_trampoline;
बाह्य अक्षर zynq_secondary_trampoline_jump;
बाह्य अक्षर zynq_secondary_trampoline_end;
बाह्य पूर्णांक zynq_cpun_start(u32 address, पूर्णांक cpu);
बाह्य स्थिर काष्ठा smp_operations zynq_smp_ops;
#पूर्ण_अगर

बाह्य व्योम __iomem *zynq_scu_base;

व्योम zynq_pm_late_init(व्योम);

अटल अंतरभूत व्योम zynq_core_pm_init(व्योम)
अणु
	/* A9 घड़ी gating */
	यंत्र अस्थिर ("mrc  p15, 0, r12, c15, c0, 0\n"
		      "orr  r12, r12, #1\n"
		      "mcr  p15, 0, r12, c15, c0, 0\n"
		      : /* no outमाला_दो */
		      : /* no inमाला_दो */
		      : "r12");
पूर्ण

#पूर्ण_अगर
