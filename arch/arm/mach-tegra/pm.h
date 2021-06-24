<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Google, Inc.
 * Copyright (c) 2010-2012 NVIDIA Corporation. All rights reserved.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 */

#अगर_अघोषित _MACH_TEGRA_PM_H_
#घोषणा _MACH_TEGRA_PM_H_

काष्ठा tegra_lp1_iram अणु
	व्योम	*start_addr;
	व्योम	*end_addr;
पूर्ण;

बाह्य काष्ठा tegra_lp1_iram tegra_lp1_iram;
बाह्य व्योम (*tegra_sleep_core_finish)(अचिन्हित दीर्घ v2p);

व्योम tegra20_lp1_iram_hook(व्योम);
व्योम tegra20_sleep_core_init(व्योम);
व्योम tegra30_lp1_iram_hook(व्योम);
व्योम tegra30_sleep_core_init(व्योम);

बाह्य व्योम (*tegra_tear_करोwn_cpu)(व्योम);

#अगर_घोषित CONFIG_PM_SLEEP
व्योम tegra_init_suspend(व्योम);
#अन्यथा
अटल अंतरभूत व्योम tegra_init_suspend(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _MACH_TEGRA_PM_H_ */
