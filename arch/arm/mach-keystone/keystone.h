<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2013 Texas Instruments, Inc.
 *	Cyril Chemparathy <cyril@ti.com>
 *	Santosh Shilimkar <santosh.shillimkar@ti.com>
 */

#अगर_अघोषित __KEYSTONE_H__
#घोषणा __KEYSTONE_H__

#घोषणा KEYSTONE_MON_CPU_UP_IDX		0x00

#अगर_अघोषित __ASSEMBLER__

बाह्य स्थिर काष्ठा smp_operations keystone_smp_ops;
बाह्य व्योम secondary_startup(व्योम);
बाह्य u32 keystone_cpu_smc(u32 command, u32 cpu, u32 addr);
बाह्य पूर्णांक keystone_pm_runसमय_init(व्योम);

#पूर्ण_अगर /* __ASSEMBLER__ */
#पूर्ण_अगर /* __KEYSTONE_H__ */
