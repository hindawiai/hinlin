<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cs42l42.h -- CS42L42 ALSA SoC audio driver DT bindings header
 *
 * Copyright 2016 Cirrus Logic, Inc.
 *
 * Author: James Schulman <james.schulman@cirrus.com>
 * Author: Brian Austin <brian.austin@cirrus.com>
 * Author: Michael White <michael.white@cirrus.com>
 */

#अगर_अघोषित __DT_CS42L42_H
#घोषणा __DT_CS42L42_H

/* HPOUT Load Capacity */
#घोषणा CS42L42_HPOUT_LOAD_1NF		0
#घोषणा CS42L42_HPOUT_LOAD_10NF		1

/* HPOUT Clamp to GND Override */
#घोषणा CS42L42_HPOUT_CLAMP_EN		0
#घोषणा CS42L42_HPOUT_CLAMP_DIS		1

/* Tip Sense Inversion */
#घोषणा CS42L42_TS_INV_DIS			0
#घोषणा CS42L42_TS_INV_EN			1

/* Tip Sense Debounce */
#घोषणा CS42L42_TS_DBNCE_0			0
#घोषणा CS42L42_TS_DBNCE_125			1
#घोषणा CS42L42_TS_DBNCE_250			2
#घोषणा CS42L42_TS_DBNCE_500			3
#घोषणा CS42L42_TS_DBNCE_750			4
#घोषणा CS42L42_TS_DBNCE_1000			5
#घोषणा CS42L42_TS_DBNCE_1250			6
#घोषणा CS42L42_TS_DBNCE_1500			7

/* Button Press Software Debounce Times */
#घोषणा CS42L42_BTN_DET_INIT_DBNCE_MIN		0
#घोषणा CS42L42_BTN_DET_INIT_DBNCE_DEFAULT	100
#घोषणा CS42L42_BTN_DET_INIT_DBNCE_MAX		200

#घोषणा CS42L42_BTN_DET_EVENT_DBNCE_MIN		0
#घोषणा CS42L42_BTN_DET_EVENT_DBNCE_DEFAULT	10
#घोषणा CS42L42_BTN_DET_EVENT_DBNCE_MAX		20

/* Button Detect Level Sensitivities */
#घोषणा CS42L42_NUM_BIASES		4

#घोषणा CS42L42_HS_DET_LEVEL_15		0x0F
#घोषणा CS42L42_HS_DET_LEVEL_8		0x08
#घोषणा CS42L42_HS_DET_LEVEL_4		0x04
#घोषणा CS42L42_HS_DET_LEVEL_1		0x01

#घोषणा CS42L42_HS_DET_LEVEL_MIN	0
#घोषणा CS42L42_HS_DET_LEVEL_MAX	0x3F

/* HS Bias Ramp Rate */

#घोषणा CS42L42_HSBIAS_RAMP_FAST_RISE_SLOW_FALL		0
#घोषणा CS42L42_HSBIAS_RAMP_FAST			1
#घोषणा CS42L42_HSBIAS_RAMP_SLOW			2
#घोषणा CS42L42_HSBIAS_RAMP_SLOWEST			3

#घोषणा CS42L42_HSBIAS_RAMP_TIME0			10
#घोषणा CS42L42_HSBIAS_RAMP_TIME1			40
#घोषणा CS42L42_HSBIAS_RAMP_TIME2			90
#घोषणा CS42L42_HSBIAS_RAMP_TIME3			170

#पूर्ण_अगर /* __DT_CS42L42_H */
