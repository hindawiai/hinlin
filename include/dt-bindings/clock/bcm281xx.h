<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 * Copyright 2013 Linaro Limited
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _CLOCK_BCM281XX_H
#घोषणा _CLOCK_BCM281XX_H

/*
 * This file defines the values used to specअगरy घड़ीs provided by
 * the घड़ी control units (CCUs) on Broadcom BCM281XX family SoCs.
 */

/*
 * These are the bcm281xx CCU device tree "compatible" strings.
 * We're stuck with using "bcm11351" in the string because wild
 * cards aren't allowed, and that name was the first one defined
 * in this family of devices.
 */
#घोषणा BCM281XX_DT_ROOT_CCU_COMPAT	"brcm,bcm11351-root-ccu"
#घोषणा BCM281XX_DT_AON_CCU_COMPAT	"brcm,bcm11351-aon-ccu"
#घोषणा BCM281XX_DT_HUB_CCU_COMPAT	"brcm,bcm11351-hub-ccu"
#घोषणा BCM281XX_DT_MASTER_CCU_COMPAT	"brcm,bcm11351-master-ccu"
#घोषणा BCM281XX_DT_SLAVE_CCU_COMPAT	"brcm,bcm11351-slave-ccu"

/* root CCU घड़ी ids */

#घोषणा BCM281XX_ROOT_CCU_FRAC_1M		0
#घोषणा BCM281XX_ROOT_CCU_CLOCK_COUNT		1

/* aon CCU घड़ी ids */

#घोषणा BCM281XX_AON_CCU_HUB_TIMER		0
#घोषणा BCM281XX_AON_CCU_PMU_BSC		1
#घोषणा BCM281XX_AON_CCU_PMU_BSC_VAR		2
#घोषणा BCM281XX_AON_CCU_CLOCK_COUNT		3

/* hub CCU घड़ी ids */

#घोषणा BCM281XX_HUB_CCU_TMON_1M		0
#घोषणा BCM281XX_HUB_CCU_CLOCK_COUNT		1

/* master CCU घड़ी ids */

#घोषणा BCM281XX_MASTER_CCU_SDIO1		0
#घोषणा BCM281XX_MASTER_CCU_SDIO2		1
#घोषणा BCM281XX_MASTER_CCU_SDIO3		2
#घोषणा BCM281XX_MASTER_CCU_SDIO4		3
#घोषणा BCM281XX_MASTER_CCU_USB_IC		4
#घोषणा BCM281XX_MASTER_CCU_HSIC2_48M		5
#घोषणा BCM281XX_MASTER_CCU_HSIC2_12M		6
#घोषणा BCM281XX_MASTER_CCU_CLOCK_COUNT		7

/* slave CCU घड़ी ids */

#घोषणा BCM281XX_SLAVE_CCU_UARTB		0
#घोषणा BCM281XX_SLAVE_CCU_UARTB2		1
#घोषणा BCM281XX_SLAVE_CCU_UARTB3		2
#घोषणा BCM281XX_SLAVE_CCU_UARTB4		3
#घोषणा BCM281XX_SLAVE_CCU_SSP0			4
#घोषणा BCM281XX_SLAVE_CCU_SSP2			5
#घोषणा BCM281XX_SLAVE_CCU_BSC1			6
#घोषणा BCM281XX_SLAVE_CCU_BSC2			7
#घोषणा BCM281XX_SLAVE_CCU_BSC3			8
#घोषणा BCM281XX_SLAVE_CCU_PWM			9
#घोषणा BCM281XX_SLAVE_CCU_CLOCK_COUNT		10

#पूर्ण_अगर /* _CLOCK_BCM281XX_H */
