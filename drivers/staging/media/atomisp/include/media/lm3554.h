<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/media/lm3554.h
 *
 * Copyright (c) 2010-2012 Intel Corporation. All Rights Reserved.
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
#अगर_अघोषित _LM3554_H_
#घोषणा _LM3554_H_

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा LM3554_ID      3554

#घोषणा	v4l2_queryctrl_entry_पूर्णांकeger(_id, _name,\
		_minimum, _maximum, _step, \
		_शेष_value, _flags)	\
	अणु\
		.id = (_id), \
		.type = V4L2_CTRL_TYPE_INTEGER, \
		.name = _name, \
		.minimum = (_minimum), \
		.maximum = (_maximum), \
		.step = (_step), \
		.शेष_value = (_शेष_value),\
		.flags = (_flags),\
	पूर्ण
#घोषणा	v4l2_queryctrl_entry_boolean(_id, _name,\
		_शेष_value, _flags)	\
	अणु\
		.id = (_id), \
		.type = V4L2_CTRL_TYPE_BOOLEAN, \
		.name = _name, \
		.minimum = 0, \
		.maximum = 1, \
		.step = 1, \
		.शेष_value = (_शेष_value),\
		.flags = (_flags),\
	पूर्ण

#घोषणा	s_ctrl_id_entry_पूर्णांकeger(_id, _name, \
		_minimum, _maximum, _step, \
		_शेष_value, _flags, \
		_s_ctrl, _g_ctrl)	\
	अणु\
		.qc = v4l2_queryctrl_entry_पूर्णांकeger(_id, _name,\
				_minimum, _maximum, _step,\
				_शेष_value, _flags), \
		.s_ctrl = _s_ctrl, \
		.g_ctrl = _g_ctrl, \
	पूर्ण

#घोषणा	s_ctrl_id_entry_boolean(_id, _name, \
		_शेष_value, _flags, \
		_s_ctrl, _g_ctrl)	\
	अणु\
		.qc = v4l2_queryctrl_entry_boolean(_id, _name,\
				_शेष_value, _flags), \
		.s_ctrl = _s_ctrl, \
		.g_ctrl = _g_ctrl, \
	पूर्ण

/* Value settings क्रम Flash Time-out Duration*/
#घोषणा LM3554_DEFAULT_TIMEOUT          512U
#घोषणा LM3554_MIN_TIMEOUT              32U
#घोषणा LM3554_MAX_TIMEOUT              1024U
#घोषणा LM3554_TIMEOUT_STEPSIZE         32U

/* Flash modes */
#घोषणा LM3554_MODE_SHUTDOWN            0
#घोषणा LM3554_MODE_INDICATOR           1
#घोषणा LM3554_MODE_TORCH               2
#घोषणा LM3554_MODE_FLASH               3

/* समयr delay समय */
#घोषणा LM3554_TIMER_DELAY		5

/* Percentage <-> value macros */
#घोषणा LM3554_MIN_PERCENT                   0U
#घोषणा LM3554_MAX_PERCENT                   100U
#घोषणा LM3554_CLAMP_PERCENTAGE(val) \
	clamp(val, LM3554_MIN_PERCENT, LM3554_MAX_PERCENT)

#घोषणा LM3554_VALUE_TO_PERCENT(v, step)     (((((अचिन्हित दीर्घ)(v)) * (step)) + 50) / 100)
#घोषणा LM3554_PERCENT_TO_VALUE(p, step)     (((((अचिन्हित दीर्घ)(p)) * 100) + (step >> 1)) / (step))

/* Product specअगरic limits
 * TODO: get these from platक्रमm data */
#घोषणा LM3554_FLASH_MAX_LVL   0x0F /* 1191mA */

/* Flash brightness, input is percentage, output is [0..15] */
#घोषणा LM3554_FLASH_STEP	\
	((100ul * (LM3554_MAX_PERCENT) + ((LM3554_FLASH_MAX_LVL) >> 1)) / ((LM3554_FLASH_MAX_LVL)))
#घोषणा LM3554_FLASH_DEFAULT_BRIGHTNESS \
	LM3554_VALUE_TO_PERCENT(13, LM3554_FLASH_STEP)

/* Torch brightness, input is percentage, output is [0..7] */
#घोषणा LM3554_TORCH_STEP                    1250
#घोषणा LM3554_TORCH_DEFAULT_BRIGHTNESS \
	LM3554_VALUE_TO_PERCENT(2, LM3554_TORCH_STEP)

/* Indicator brightness, input is percentage, output is [0..3] */
#घोषणा LM3554_INDICATOR_STEP                2500
#घोषणा LM3554_INDICATOR_DEFAULT_BRIGHTNESS \
	LM3554_VALUE_TO_PERCENT(1, LM3554_INDICATOR_STEP)

/*
 * lm3554_platक्रमm_data - Flash controller platक्रमm data
 */
काष्ठा lm3554_platक्रमm_data अणु
	काष्ठा gpio_desc *gpio_torch;
	काष्ठा gpio_desc *gpio_strobe;
	काष्ठा gpio_desc *gpio_reset;

	अचिन्हित पूर्णांक current_limit;
	अचिन्हित पूर्णांक envm_tx2;
	अचिन्हित पूर्णांक tx2_polarity;
पूर्ण;

#पूर्ण_अगर /* _LM3554_H_ */
