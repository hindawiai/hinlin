<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित MFD_TPS6105X_H
#घोषणा MFD_TPS6105X_H

#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/machine.h>

/*
 * Register definitions to all subdrivers
 */
#घोषणा TPS6105X_REG_0			0x00
#घोषणा TPS6105X_REG0_MODE_SHIFT	6
#घोषणा TPS6105X_REG0_MODE_MASK		(0x03<<6)
/* These defines क्रम both reg0 and reg1 */
#घोषणा TPS6105X_REG0_MODE_SHUTDOWN	0x00
#घोषणा TPS6105X_REG0_MODE_TORCH	0x01
#घोषणा TPS6105X_REG0_MODE_TORCH_FLASH	0x02
#घोषणा TPS6105X_REG0_MODE_VOLTAGE	0x03
#घोषणा TPS6105X_REG0_VOLTAGE_SHIFT	4
#घोषणा TPS6105X_REG0_VOLTAGE_MASK	(3<<4)
#घोषणा TPS6105X_REG0_VOLTAGE_450	0
#घोषणा TPS6105X_REG0_VOLTAGE_500	1
#घोषणा TPS6105X_REG0_VOLTAGE_525	2
#घोषणा TPS6105X_REG0_VOLTAGE_500_2	3
#घोषणा TPS6105X_REG0_DIMMING_SHIFT	3
#घोषणा TPS6105X_REG0_TORCHC_SHIFT	0
#घोषणा TPS6105X_REG0_TORCHC_MASK	(7<<0)
#घोषणा TPS6105X_REG0_TORCHC_0		0x00
#घोषणा TPS6105X_REG0_TORCHC_50		0x01
#घोषणा TPS6105X_REG0_TORCHC_75		0x02
#घोषणा TPS6105X_REG0_TORCHC_100	0x03
#घोषणा TPS6105X_REG0_TORCHC_150	0x04
#घोषणा TPS6105X_REG0_TORCHC_200	0x05
#घोषणा TPS6105X_REG0_TORCHC_250_400	0x06
#घोषणा TPS6105X_REG0_TORCHC_250_500	0x07
#घोषणा TPS6105X_REG_1			0x01
#घोषणा TPS6105X_REG1_MODE_SHIFT	6
#घोषणा TPS6105X_REG1_MODE_MASK		(0x03<<6)
#घोषणा TPS6105X_REG1_MODE_SHUTDOWN	0x00
#घोषणा TPS6105X_REG1_MODE_TORCH	0x01
#घोषणा TPS6105X_REG1_MODE_TORCH_FLASH	0x02
#घोषणा TPS6105X_REG1_MODE_VOLTAGE	0x03
#घोषणा TPS6105X_REG_2			0x02
#घोषणा TPS6105X_REG_3			0x03

/**
 * क्रमागत tps6105x_mode - desired mode क्रम the TPS6105x
 * @TPS6105X_MODE_SHUTDOWN: this instance is inactive, not used क्रम anything
 * @TPS61905X_MODE_TORCH: this instance is used as a LED, usually a जबतक
 *	LED, क्रम example as backlight or flashlight. If this is set, the
 *	TPS6105X will रेजिस्टर to the LED framework
 * @TPS6105X_MODE_TORCH_FLASH: this instance is used as a flashgun, usually
 *	in a camera
 * @TPS6105X_MODE_VOLTAGE: this instance is used as a voltage regulator and
 *	will रेजिस्टर to the regulator framework
 */
क्रमागत tps6105x_mode अणु
	TPS6105X_MODE_SHUTDOWN,
	TPS6105X_MODE_TORCH,
	TPS6105X_MODE_TORCH_FLASH,
	TPS6105X_MODE_VOLTAGE,
पूर्ण;

/**
 * काष्ठा tps6105x_platक्रमm_data - TPS61905x platक्रमm data
 * @mode: what mode this instance shall be operated in,
 *	this is not selectable at runसमय
 * @regulator_data: initialization data क्रम the voltage
 *	regulator अगर used as a voltage source
 */
काष्ठा tps6105x_platक्रमm_data अणु
	क्रमागत tps6105x_mode mode;
	काष्ठा regulator_init_data *regulator_data;
पूर्ण;

/**
 * काष्ठा tps6105x - state holder क्रम the TPS6105x drivers
 * @i2c_client: corresponding I2C client
 * @regulator: regulator device अगर used in voltage mode
 * @regmap: used क्रम i2c communcation on accessing रेजिस्टरs
 */
काष्ठा tps6105x अणु
	काष्ठा tps6105x_platक्रमm_data *pdata;
	काष्ठा i2c_client	*client;
	काष्ठा regulator_dev	*regulator;
	काष्ठा regmap		*regmap;
पूर्ण;

#पूर्ण_अगर
