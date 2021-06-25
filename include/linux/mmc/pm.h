<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/include/linux/mmc/pm.h
 *
 * Author:	Nicolas Pitre
 * Copyright:	(C) 2009 Marvell Technology Group Ltd.
 */

#अगर_अघोषित LINUX_MMC_PM_H
#घोषणा LINUX_MMC_PM_H

/*
 * These flags are used to describe घातer management features that
 * some cards (typically SDIO cards) might wish to benefit from when
 * the host प्रणाली is being suspended.  There are several layers of
 * असलtractions involved, from the host controller driver, to the MMC core
 * code, to the SDIO core code, to finally get to the actual SDIO function
 * driver.  This file is thereक्रमe used क्रम common definitions shared across
 * all those layers.
 */

प्रकार अचिन्हित पूर्णांक mmc_pm_flag_t;

#घोषणा MMC_PM_KEEP_POWER	(1 << 0)	/* preserve card घातer during suspend */
#घोषणा MMC_PM_WAKE_SDIO_IRQ	(1 << 1)	/* wake up host प्रणाली on SDIO IRQ निश्चितion */

#पूर्ण_अगर /* LINUX_MMC_PM_H */
