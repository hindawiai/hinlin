<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2012 ARM Limited
 */


#अगर_अघोषित __SPC_H_
#घोषणा __SPC_H_

पूर्णांक __init ve_spc_init(व्योम __iomem *base, u32 a15_clusid, पूर्णांक irq);
व्योम ve_spc_global_wakeup_irq(bool set);
व्योम ve_spc_cpu_wakeup_irq(u32 cluster, u32 cpu, bool set);
व्योम ve_spc_set_resume_addr(u32 cluster, u32 cpu, u32 addr);
व्योम ve_spc_घातerकरोwn(u32 cluster, bool enable);
पूर्णांक ve_spc_cpu_in_wfi(u32 cpu, u32 cluster);

#पूर्ण_अगर
