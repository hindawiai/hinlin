<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * fan53555.h - Fairchild Regulator FAN53555 Driver
 *
 * Copyright (C) 2012 Marvell Technology Ltd.
 * Yunfan Zhang <yfzhang@marvell.com>
 */

#अगर_अघोषित __FAN53555_H__
#घोषणा __FAN53555_H__

/* VSEL ID */
क्रमागत अणु
	FAN53555_VSEL_ID_0 = 0,
	FAN53555_VSEL_ID_1,
पूर्ण;

/* Transition slew rate limiting from a low to high voltage.
 * -----------------------
 *   Bin |Slew Rate(mV/uS)
 * ------|----------------
 *   000 |    64.00
 * ------|----------------
 *   001 |    32.00
 * ------|----------------
 *   010 |    16.00
 * ------|----------------
 *   011 |     8.00
 * ------|----------------
 *   100 |     4.00
 * ------|----------------
 *   101 |     2.00
 * ------|----------------
 *   110 |     1.00
 * ------|----------------
 *   111 |     0.50
 * -----------------------
 */
क्रमागत अणु
	FAN53555_SLEW_RATE_64MV = 0,
	FAN53555_SLEW_RATE_32MV,
	FAN53555_SLEW_RATE_16MV,
	FAN53555_SLEW_RATE_8MV,
	FAN53555_SLEW_RATE_4MV,
	FAN53555_SLEW_RATE_2MV,
	FAN53555_SLEW_RATE_1MV,
	FAN53555_SLEW_RATE_0_5MV,
पूर्ण;

काष्ठा fan53555_platक्रमm_data अणु
	काष्ठा regulator_init_data *regulator;
	अचिन्हित पूर्णांक slew_rate;
	/* Sleep VSEL ID */
	अचिन्हित पूर्णांक sleep_vsel_id;
पूर्ण;

#पूर्ण_अगर /* __FAN53555_H__ */
