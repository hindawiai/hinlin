<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// TI LMU Common Core
// Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/

#अगर_अघोषित _TI_LMU_COMMON_H_
#घोषणा _TI_LMU_COMMON_H_

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/uleds.h>

#घोषणा LMU_11BIT_LSB_MASK	(BIT(0) | BIT(1) | BIT(2))
#घोषणा LMU_11BIT_MSB_SHIFT	3

#घोषणा MAX_BRIGHTNESS_8BIT	255
#घोषणा MAX_BRIGHTNESS_11BIT	2047

काष्ठा ti_lmu_bank अणु
	काष्ठा regmap *regmap;

	पूर्णांक max_brightness;

	u8 lsb_brightness_reg;
	u8 msb_brightness_reg;

	u8 runसमय_ramp_reg;
	u32 ramp_up_usec;
	u32 ramp_करोwn_usec;
पूर्ण;

पूर्णांक ti_lmu_common_set_brightness(काष्ठा ti_lmu_bank *lmu_bank, पूर्णांक brightness);

पूर्णांक ti_lmu_common_set_ramp(काष्ठा ti_lmu_bank *lmu_bank);

पूर्णांक ti_lmu_common_get_ramp_params(काष्ठा device *dev,
				  काष्ठा fwnode_handle *child,
				  काष्ठा ti_lmu_bank *lmu_data);

पूर्णांक ti_lmu_common_get_brt_res(काष्ठा device *dev, काष्ठा fwnode_handle *child,
			      काष्ठा ti_lmu_bank *lmu_data);

#पूर्ण_अगर /* _TI_LMU_COMMON_H_ */
