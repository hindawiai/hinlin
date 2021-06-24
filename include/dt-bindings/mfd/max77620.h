<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides macros क्रम MAXIM MAX77620 device bindings.
 *
 * Copyright (c) 2016, NVIDIA Corporation.
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#अगर_अघोषित _DT_BINDINGS_MFD_MAX77620_H
#घोषणा _DT_BINDINGS_MFD_MAX77620_H

/* MAX77620 पूर्णांकerrupts */
#घोषणा MAX77620_IRQ_TOP_GLBL		0 /* Low-Battery */
#घोषणा MAX77620_IRQ_TOP_SD		1 /* SD घातer fail */
#घोषणा MAX77620_IRQ_TOP_LDO		2 /* LDO घातer fail */
#घोषणा MAX77620_IRQ_TOP_GPIO		3 /* GPIO पूर्णांकernal पूर्णांक to MAX77620 */
#घोषणा MAX77620_IRQ_TOP_RTC		4 /* RTC */
#घोषणा MAX77620_IRQ_TOP_32K		5 /* 32kHz oscillator */
#घोषणा MAX77620_IRQ_TOP_ONOFF		6 /* ON/OFF oscillator */
#घोषणा MAX77620_IRQ_LBT_MBATLOW	7 /* Thermal alarm status, > 120C */
#घोषणा MAX77620_IRQ_LBT_TJALRM1	8 /* Thermal alarm status, > 120C */
#घोषणा MAX77620_IRQ_LBT_TJALRM2	9 /* Thermal alarm status, > 140C */

/* FPS event source */
#घोषणा MAX77620_FPS_EVENT_SRC_EN0		0
#घोषणा MAX77620_FPS_EVENT_SRC_EN1		1
#घोषणा MAX77620_FPS_EVENT_SRC_SW		2

/* Device state when FPS event LOW  */
#घोषणा MAX77620_FPS_INACTIVE_STATE_SLEEP	0
#घोषणा MAX77620_FPS_INACTIVE_STATE_LOW_POWER	1

/* FPS source */
#घोषणा MAX77620_FPS_SRC_0			0
#घोषणा MAX77620_FPS_SRC_1			1
#घोषणा MAX77620_FPS_SRC_2			2
#घोषणा MAX77620_FPS_SRC_NONE			3
#घोषणा MAX77620_FPS_SRC_DEF			4

#पूर्ण_अगर
