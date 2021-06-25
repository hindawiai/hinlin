<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI LMU (Lighting Management Unit) Devices
 *
 * Copyright 2017 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 */

#अगर_अघोषित __MFD_TI_LMU_H__
#घोषणा __MFD_TI_LMU_H__

#समावेश <linux/gpपन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpio/consumer.h>

/* Notअगरier event */
#घोषणा LMU_EVENT_MONITOR_DONE		0x01

क्रमागत ti_lmu_id अणु
	LM3631,
	LM3632,
	LM3633,
	LM3695,
	LM36274,
	LMU_MAX_ID,
पूर्ण;

क्रमागत ti_lmu_max_current अणु
	LMU_IMAX_5mA,
	LMU_IMAX_6mA,
	LMU_IMAX_7mA = 0x03,
	LMU_IMAX_8mA,
	LMU_IMAX_9mA,
	LMU_IMAX_10mA = 0x07,
	LMU_IMAX_11mA,
	LMU_IMAX_12mA,
	LMU_IMAX_13mA,
	LMU_IMAX_14mA,
	LMU_IMAX_15mA = 0x0D,
	LMU_IMAX_16mA,
	LMU_IMAX_17mA,
	LMU_IMAX_18mA,
	LMU_IMAX_19mA,
	LMU_IMAX_20mA = 0x13,
	LMU_IMAX_21mA,
	LMU_IMAX_22mA,
	LMU_IMAX_23mA = 0x17,
	LMU_IMAX_24mA,
	LMU_IMAX_25mA,
	LMU_IMAX_26mA,
	LMU_IMAX_27mA = 0x1C,
	LMU_IMAX_28mA,
	LMU_IMAX_29mA,
	LMU_IMAX_30mA,
पूर्ण;

क्रमागत lm363x_regulator_id अणु
	LM3631_BOOST,		/* Boost output */
	LM3631_LDO_CONT,	/* Display panel controller */
	LM3631_LDO_OREF,	/* Gamma reference */
	LM3631_LDO_POS,		/* Positive display bias output */
	LM3631_LDO_NEG,		/* Negative display bias output */
	LM3632_BOOST,		/* Boost output */
	LM3632_LDO_POS,		/* Positive display bias output */
	LM3632_LDO_NEG,		/* Negative display bias output */
	LM36274_BOOST,		/* Boost output */
	LM36274_LDO_POS,	/* Positive display bias output */
	LM36274_LDO_NEG,	/* Negative display bias output */
पूर्ण;

/**
 * काष्ठा ti_lmu
 *
 * @dev:	Parent device poपूर्णांकer
 * @regmap:	Used क्रम i2c communcation on accessing रेजिस्टरs
 * @en_gpio:	GPIO क्रम HWEN pin [Optional]
 * @notअगरier:	Notअगरier क्रम reporting hwmon event
 */
काष्ठा ti_lmu अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *en_gpio;
	काष्ठा blocking_notअगरier_head notअगरier;
पूर्ण;
#पूर्ण_अगर
