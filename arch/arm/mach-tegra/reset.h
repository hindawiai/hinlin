<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-tegra/reset.h
 *
 * CPU reset dispatcher.
 *
 * Copyright (c) 2011, NVIDIA Corporation.
 */

#अगर_अघोषित __MACH_TEGRA_RESET_H
#घोषणा __MACH_TEGRA_RESET_H

#घोषणा TEGRA_RESET_MASK_PRESENT	0
#घोषणा TEGRA_RESET_MASK_LP1		1
#घोषणा TEGRA_RESET_MASK_LP2		2
#घोषणा TEGRA_RESET_STARTUP_SECONDARY	3
#घोषणा TEGRA_RESET_STARTUP_LP2		4
#घोषणा TEGRA_RESET_STARTUP_LP1		5
#घोषणा TEGRA_RESET_TF_PRESENT		6
#घोषणा TEGRA_RESET_DATA_SIZE		7

#घोषणा RESET_DATA(x)	((TEGRA_RESET_##x)*4)

#अगर_अघोषित __ASSEMBLY__

#समावेश "irammap.h"

बाह्य अचिन्हित दीर्घ __tegra_cpu_reset_handler_data[TEGRA_RESET_DATA_SIZE];

व्योम __tegra_cpu_reset_handler_start(व्योम);
व्योम __tegra_cpu_reset_handler(व्योम);
व्योम __tegra20_cpu1_resettable_status_offset(व्योम);
व्योम __tegra_cpu_reset_handler_end(व्योम);

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा tegra_cpu_lp1_mask \
	(IO_ADDRESS(TEGRA_IRAM_BASE + TEGRA_IRAM_RESET_HANDLER_OFFSET + \
	((u32)&__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_LP1] - \
	 (u32)__tegra_cpu_reset_handler_start)))
#घोषणा tegra_cpu_lp2_mask \
	(IO_ADDRESS(TEGRA_IRAM_BASE + TEGRA_IRAM_RESET_HANDLER_OFFSET + \
	((u32)&__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_LP2] - \
	 (u32)__tegra_cpu_reset_handler_start)))
#पूर्ण_अगर

#घोषणा tegra_cpu_reset_handler_offset \
		((u32)__tegra_cpu_reset_handler - \
		 (u32)__tegra_cpu_reset_handler_start)

#घोषणा tegra_cpu_reset_handler_size \
		(__tegra_cpu_reset_handler_end - \
		 __tegra_cpu_reset_handler_start)

व्योम __init tegra_cpu_reset_handler_init(व्योम);

#पूर्ण_अगर
#पूर्ण_अगर
