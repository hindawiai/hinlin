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

#अगर_अघोषित _CLOCK_BCM21664_H
#घोषणा _CLOCK_BCM21664_H

/*
 * This file defines the values used to specअगरy घड़ीs provided by
 * the घड़ी control units (CCUs) on Broadcom BCM21664 family SoCs.
 */

/* bcm21664 CCU device tree "compatible" strings */
#घोषणा BCM21664_DT_ROOT_CCU_COMPAT	"brcm,bcm21664-root-ccu"
#घोषणा BCM21664_DT_AON_CCU_COMPAT	"brcm,bcm21664-aon-ccu"
#घोषणा BCM21664_DT_MASTER_CCU_COMPAT	"brcm,bcm21664-master-ccu"
#घोषणा BCM21664_DT_SLAVE_CCU_COMPAT	"brcm,bcm21664-slave-ccu"

/* root CCU घड़ी ids */

#घोषणा BCM21664_ROOT_CCU_FRAC_1M		0
#घोषणा BCM21664_ROOT_CCU_CLOCK_COUNT		1

/* aon CCU घड़ी ids */

#घोषणा BCM21664_AON_CCU_HUB_TIMER		0
#घोषणा BCM21664_AON_CCU_CLOCK_COUNT		1

/* master CCU घड़ी ids */

#घोषणा BCM21664_MASTER_CCU_SDIO1		0
#घोषणा BCM21664_MASTER_CCU_SDIO2		1
#घोषणा BCM21664_MASTER_CCU_SDIO3		2
#घोषणा BCM21664_MASTER_CCU_SDIO4		3
#घोषणा BCM21664_MASTER_CCU_SDIO1_SLEEP		4
#घोषणा BCM21664_MASTER_CCU_SDIO2_SLEEP		5
#घोषणा BCM21664_MASTER_CCU_SDIO3_SLEEP		6
#घोषणा BCM21664_MASTER_CCU_SDIO4_SLEEP		7
#घोषणा BCM21664_MASTER_CCU_CLOCK_COUNT		8

/* slave CCU घड़ी ids */

#घोषणा BCM21664_SLAVE_CCU_UARTB		0
#घोषणा BCM21664_SLAVE_CCU_UARTB2		1
#घोषणा BCM21664_SLAVE_CCU_UARTB3		2
#घोषणा BCM21664_SLAVE_CCU_BSC1			3
#घोषणा BCM21664_SLAVE_CCU_BSC2			4
#घोषणा BCM21664_SLAVE_CCU_BSC3			5
#घोषणा BCM21664_SLAVE_CCU_BSC4			6
#घोषणा BCM21664_SLAVE_CCU_CLOCK_COUNT		7

#पूर्ण_अगर /* _CLOCK_BCM21664_H */
