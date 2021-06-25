<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PXA910 Power Management Routines
 *
 * (C) Copyright 2009 Marvell International Ltd.
 * All Rights Reserved
 */

#अगर_अघोषित __PXA910_PM_H__
#घोषणा __PXA910_PM_H__

#घोषणा APMU_MOH_IDLE_CFG			APMU_REG(0x0018)
#घोषणा APMU_MOH_IDLE_CFG_MOH_IDLE		(1 << 1)
#घोषणा APMU_MOH_IDLE_CFG_MOH_PWRDWN		(1 << 5)
#घोषणा APMU_MOH_IDLE_CFG_MOH_SRAM_PWRDWN	(1 << 6)
#घोषणा APMU_MOH_IDLE_CFG_MOH_PWR_SW(x)		(((x) & 0x3) << 16)
#घोषणा APMU_MOH_IDLE_CFG_MOH_L2_PWR_SW(x)	(((x) & 0x3) << 18)
#घोषणा APMU_MOH_IDLE_CFG_MOH_DIS_MC_SW_REQ	(1 << 21)
#घोषणा APMU_MOH_IDLE_CFG_MOH_MC_WAKE_EN	(1 << 20)

#घोषणा APMU_SQU_CLK_GATE_CTRL			APMU_REG(0x001c)
#घोषणा APMU_MC_HW_SLP_TYPE			APMU_REG(0x00b0)

#घोषणा MPMU_FCCR				MPMU_REG(0x0008)
#घोषणा MPMU_APCR				MPMU_REG(0x1000)
#घोषणा MPMU_APCR_AXISD				(1 << 31)
#घोषणा MPMU_APCR_DSPSD				(1 << 30)
#घोषणा MPMU_APCR_SLPEN				(1 << 29)
#घोषणा MPMU_APCR_DTCMSD			(1 << 28)
#घोषणा MPMU_APCR_DDRCORSD			(1 << 27)
#घोषणा MPMU_APCR_APBSD				(1 << 26)
#घोषणा MPMU_APCR_BBSD				(1 << 25)
#घोषणा MPMU_APCR_SLPWP0			(1 << 23)
#घोषणा MPMU_APCR_SLPWP1			(1 << 22)
#घोषणा MPMU_APCR_SLPWP2			(1 << 21)
#घोषणा MPMU_APCR_SLPWP3			(1 << 20)
#घोषणा MPMU_APCR_VCTCXOSD			(1 << 19)
#घोषणा MPMU_APCR_SLPWP4			(1 << 18)
#घोषणा MPMU_APCR_SLPWP5			(1 << 17)
#घोषणा MPMU_APCR_SLPWP6			(1 << 16)
#घोषणा MPMU_APCR_SLPWP7			(1 << 15)
#घोषणा MPMU_APCR_MSASLPEN			(1 << 14)
#घोषणा MPMU_APCR_STBYEN			(1 << 13)

#घोषणा MPMU_AWUCRM				MPMU_REG(0x104c)
#घोषणा MPMU_AWUCRM_AP_ASYNC_INT		(1 << 25)
#घोषणा MPMU_AWUCRM_AP_FULL_IDLE		(1 << 24)
#घोषणा MPMU_AWUCRM_SDH1			(1 << 23)
#घोषणा MPMU_AWUCRM_SDH2			(1 << 22)
#घोषणा MPMU_AWUCRM_KEYPRESS			(1 << 21)
#घोषणा MPMU_AWUCRM_TRACKBALL			(1 << 20)
#घोषणा MPMU_AWUCRM_NEWROTARY			(1 << 19)
#घोषणा MPMU_AWUCRM_RTC_ALARM			(1 << 17)
#घोषणा MPMU_AWUCRM_AP2_TIMER_3			(1 << 13)
#घोषणा MPMU_AWUCRM_AP2_TIMER_2			(1 << 12)
#घोषणा MPMU_AWUCRM_AP2_TIMER_1			(1 << 11)
#घोषणा MPMU_AWUCRM_AP1_TIMER_3			(1 << 10)
#घोषणा MPMU_AWUCRM_AP1_TIMER_2			(1 << 9)
#घोषणा MPMU_AWUCRM_AP1_TIMER_1			(1 << 8)
#घोषणा MPMU_AWUCRM_WAKEUP(x)			(1 << ((x) & 0x7))

क्रमागत अणु
	POWER_MODE_ACTIVE = 0,
	POWER_MODE_CORE_INTIDLE,
	POWER_MODE_CORE_EXTIDLE,
	POWER_MODE_APPS_IDLE,
	POWER_MODE_APPS_SLEEP,
	POWER_MODE_SYS_SLEEP,
	POWER_MODE_HIBERNATE,
	POWER_MODE_UDR,
पूर्ण;

बाह्य पूर्णांक pxa910_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on);

#पूर्ण_अगर
