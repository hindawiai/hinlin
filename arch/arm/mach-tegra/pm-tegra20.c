<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, NVIDIA Corporation. All rights reserved.
 */

#समावेश <linux/kernel.h>

#समावेश "pm.h"

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य u32 tegra20_iram_start, tegra20_iram_end;
बाह्य व्योम tegra20_sleep_core_finish(अचिन्हित दीर्घ);

व्योम tegra20_lp1_iram_hook(व्योम)
अणु
	tegra_lp1_iram.start_addr = &tegra20_iram_start;
	tegra_lp1_iram.end_addr = &tegra20_iram_end;
पूर्ण

व्योम tegra20_sleep_core_init(व्योम)
अणु
	tegra_sleep_core_finish = tegra20_sleep_core_finish;
पूर्ण
#पूर्ण_अगर
