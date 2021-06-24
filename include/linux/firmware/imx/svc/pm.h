<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *
 * Header file containing the खुला API क्रम the System Controller (SC)
 * Power Management (PM) function. This includes functions क्रम घातer state
 * control, घड़ी control, reset control, and wake-up event control.
 *
 * PM_SVC (SVC) Power Management Service
 *
 * Module क्रम the Power Management (PM) service.
 */

#अगर_अघोषित _SC_PM_API_H
#घोषणा _SC_PM_API_H

#समावेश <linux/firmware/imx/sci.h>

/*
 * This type is used to indicate RPC PM function calls.
 */
क्रमागत imx_sc_pm_func अणु
	IMX_SC_PM_FUNC_UNKNOWN = 0,
	IMX_SC_PM_FUNC_SET_SYS_POWER_MODE = 19,
	IMX_SC_PM_FUNC_SET_PARTITION_POWER_MODE = 1,
	IMX_SC_PM_FUNC_GET_SYS_POWER_MODE = 2,
	IMX_SC_PM_FUNC_SET_RESOURCE_POWER_MODE = 3,
	IMX_SC_PM_FUNC_GET_RESOURCE_POWER_MODE = 4,
	IMX_SC_PM_FUNC_REQ_LOW_POWER_MODE = 16,
	IMX_SC_PM_FUNC_SET_CPU_RESUME_ADDR = 17,
	IMX_SC_PM_FUNC_REQ_SYS_IF_POWER_MODE = 18,
	IMX_SC_PM_FUNC_SET_CLOCK_RATE = 5,
	IMX_SC_PM_FUNC_GET_CLOCK_RATE = 6,
	IMX_SC_PM_FUNC_CLOCK_ENABLE = 7,
	IMX_SC_PM_FUNC_SET_CLOCK_PARENT = 14,
	IMX_SC_PM_FUNC_GET_CLOCK_PARENT = 15,
	IMX_SC_PM_FUNC_RESET = 13,
	IMX_SC_PM_FUNC_RESET_REASON = 10,
	IMX_SC_PM_FUNC_BOOT = 8,
	IMX_SC_PM_FUNC_REBOOT = 9,
	IMX_SC_PM_FUNC_REBOOT_PARTITION = 12,
	IMX_SC_PM_FUNC_CPU_START = 11,
पूर्ण;

/*
 * Defines क्रम ALL parameters
 */
#घोषणा IMX_SC_PM_CLK_ALL		UINT8_MAX	/* All घड़ीs */

/*
 * Defines क्रम SC PM Power Mode
 */
#घोषणा IMX_SC_PM_PW_MODE_OFF	0	/* Power off */
#घोषणा IMX_SC_PM_PW_MODE_STBY	1	/* Power in standby */
#घोषणा IMX_SC_PM_PW_MODE_LP	2	/* Power in low-घातer */
#घोषणा IMX_SC_PM_PW_MODE_ON	3	/* Power on */

/*
 * Defines क्रम SC PM CLK
 */
#घोषणा IMX_SC_PM_CLK_SLV_BUS	0	/* Slave bus घड़ी */
#घोषणा IMX_SC_PM_CLK_MST_BUS	1	/* Master bus घड़ी */
#घोषणा IMX_SC_PM_CLK_PER	2	/* Peripheral घड़ी */
#घोषणा IMX_SC_PM_CLK_PHY	3	/* Phy घड़ी */
#घोषणा IMX_SC_PM_CLK_MISC	4	/* Misc घड़ी */
#घोषणा IMX_SC_PM_CLK_MISC0	0	/* Misc 0 घड़ी */
#घोषणा IMX_SC_PM_CLK_MISC1	1	/* Misc 1 घड़ी */
#घोषणा IMX_SC_PM_CLK_MISC2	2	/* Misc 2 घड़ी */
#घोषणा IMX_SC_PM_CLK_MISC3	3	/* Misc 3 घड़ी */
#घोषणा IMX_SC_PM_CLK_MISC4	4	/* Misc 4 घड़ी */
#घोषणा IMX_SC_PM_CLK_CPU	2	/* CPU घड़ी */
#घोषणा IMX_SC_PM_CLK_PLL	4	/* PLL */
#घोषणा IMX_SC_PM_CLK_BYPASS	4	/* Bypass घड़ी */

/*
 * Defines क्रम SC PM CLK Parent
 */
#घोषणा IMX_SC_PM_PARENT_XTAL	0	/* Parent is XTAL. */
#घोषणा IMX_SC_PM_PARENT_PLL0	1	/* Parent is PLL0 */
#घोषणा IMX_SC_PM_PARENT_PLL1	2	/* Parent is PLL1 or PLL0/2 */
#घोषणा IMX_SC_PM_PARENT_PLL2	3	/* Parent in PLL2 or PLL0/4 */
#घोषणा IMX_SC_PM_PARENT_BYPS	4	/* Parent is a bypass घड़ी. */

#पूर्ण_अगर /* _SC_PM_API_H */
