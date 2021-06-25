<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MMP2 Power Management Routines
 *
 * (C) Copyright 2010 Marvell International Ltd.
 * All Rights Reserved
 */

#अगर_अघोषित __MMP2_PM_H__
#घोषणा __MMP2_PM_H__

#समावेश "addr-map.h"

#घोषणा APMU_PJ_IDLE_CFG			APMU_REG(0x018)
#घोषणा APMU_PJ_IDLE_CFG_PJ_IDLE		(1 << 1)
#घोषणा APMU_PJ_IDLE_CFG_PJ_PWRDWN		(1 << 5)
#घोषणा APMU_PJ_IDLE_CFG_PWR_SW(x)		((x) << 16)
#घोषणा APMU_PJ_IDLE_CFG_L2_PWR_SW		(1 << 19)
#घोषणा APMU_PJ_IDLE_CFG_ISO_MODE_CNTRL_MASK	(3 << 28)

#घोषणा APMU_SRAM_PWR_DWN			APMU_REG(0x08c)

#घोषणा MPMU_SCCR				MPMU_REG(0x038)
#घोषणा MPMU_PCR_PJ				MPMU_REG(0x1000)
#घोषणा MPMU_PCR_PJ_AXISD			(1 << 31)
#घोषणा MPMU_PCR_PJ_SLPEN			(1 << 29)
#घोषणा MPMU_PCR_PJ_SPSD			(1 << 28)
#घोषणा MPMU_PCR_PJ_DDRCORSD			(1 << 27)
#घोषणा MPMU_PCR_PJ_APBSD			(1 << 26)
#घोषणा MPMU_PCR_PJ_INTCLR			(1 << 24)
#घोषणा MPMU_PCR_PJ_SLPWP0			(1 << 23)
#घोषणा MPMU_PCR_PJ_SLPWP1			(1 << 22)
#घोषणा MPMU_PCR_PJ_SLPWP2			(1 << 21)
#घोषणा MPMU_PCR_PJ_SLPWP3			(1 << 20)
#घोषणा MPMU_PCR_PJ_VCTCXOSD			(1 << 19)
#घोषणा MPMU_PCR_PJ_SLPWP4			(1 << 18)
#घोषणा MPMU_PCR_PJ_SLPWP5			(1 << 17)
#घोषणा MPMU_PCR_PJ_SLPWP6			(1 << 16)
#घोषणा MPMU_PCR_PJ_SLPWP7			(1 << 15)

#घोषणा MPMU_PLL2_CTRL1				MPMU_REG(0x0414)
#घोषणा MPMU_CGR_PJ				MPMU_REG(0x1024)
#घोषणा MPMU_WUCRM_PJ				MPMU_REG(0x104c)
#घोषणा MPMU_WUCRM_PJ_WAKEUP(x)			(1 << (x))
#घोषणा MPMU_WUCRM_PJ_RTC_ALARM			(1 << 17)

क्रमागत अणु
	POWER_MODE_ACTIVE = 0,
	POWER_MODE_CORE_INTIDLE,
	POWER_MODE_CORE_EXTIDLE,
	POWER_MODE_APPS_IDLE,
	POWER_MODE_APPS_SLEEP,
	POWER_MODE_CHIP_SLEEP,
	POWER_MODE_SYS_SLEEP,
पूर्ण;

बाह्य व्योम mmp2_pm_enter_lowघातer_mode(पूर्णांक state);
बाह्य पूर्णांक mmp2_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on);
#पूर्ण_अगर
