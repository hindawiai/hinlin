<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम AD5823 VCM.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित __AD5823_H__
#घोषणा __AD5823_H__

#समावेश <linux/types.h>

#घोषणा AD5823_VCM_ADDR	0x0c

#घोषणा AD5823_REG_RESET		0x01
#घोषणा AD5823_REG_MODE			0x02
#घोषणा AD5823_REG_VCM_MOVE_TIME	0x03
#घोषणा AD5823_REG_VCM_CODE_MSB		0x04
#घोषणा AD5823_REG_VCM_CODE_LSB		0x05
#घोषणा AD5823_REG_VCM_THRESHOLD_MSB	0x06
#घोषणा AD5823_REG_VCM_THRESHOLD_LSB	0x07

#घोषणा AD5823_REG_LENGTH		0x1

#घोषणा AD5823_RING_CTRL_ENABLE		0x04
#घोषणा AD5823_RING_CTRL_DISABLE	0x00

#घोषणा AD5823_RESOन_अंकCE_PERIOD		100000
#घोषणा AD5823_RESOन_अंकCE_COEF		512
#घोषणा AD5823_HIGH_FREQ_RANGE		0x80

#घोषणा VCM_CODE_MSB_MASK		0xfc
#घोषणा AD5823_INIT_FOCUS_POS           350

क्रमागत ad5823_tok_type अणु
	AD5823_8BIT  = 0x1,
	AD5823_16BIT = 0x2,
पूर्ण;

क्रमागत ad5823_vcm_mode अणु
	AD5823_ARC_RES0 = 0x0,	/* Actuator response control RES1 */
	AD5823_ARC_RES1 = 0x1,	/* Actuator response control RES0.5 */
	AD5823_ARC_RES2 = 0x2,	/* Actuator response control RES2 */
	AD5823_ESRC = 0x3,	/* Enhanced slew rate control */
	AD5823_सूचीECT = 0x4,	/* Direct control */
पूर्ण;

#घोषणा AD5823_INVALID_CONFIG	0xffffffff
#घोषणा AD5823_MAX_FOCUS_POS	1023
#घोषणा DELAY_PER_STEP_NS	1000000
#घोषणा DELAY_MAX_PER_STEP_NS	(1000000 * 1023)
#पूर्ण_अगर
