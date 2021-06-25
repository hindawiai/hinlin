<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010-2013
 * Author: Rickard Andersson <rickard.andersson@stericsson.com> क्रम
 *         ST-Ericsson.
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org> क्रम Linaro.
 */

#अगर_अघोषित ARM_UX500_PM_H
#घोषणा ARM_UX500_PM_H

पूर्णांक prcmu_gic_decouple(व्योम);
पूर्णांक prcmu_gic_recouple(व्योम);
bool prcmu_gic_pending_irq(व्योम);
bool prcmu_pending_irq(व्योम);
bool prcmu_is_cpu_in_wfi(पूर्णांक cpu);
पूर्णांक prcmu_copy_gic_settings(व्योम);
व्योम ux500_pm_init(u32 phy_base, u32 size);

#पूर्ण_अगर /* ARM_UX500_PM_H */
