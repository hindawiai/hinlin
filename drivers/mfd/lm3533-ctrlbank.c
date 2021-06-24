<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm3533-ctrlbank.c -- LM3533 Generic Control Bank पूर्णांकerface
 *
 * Copyright (C) 2011-2012 Texas Instruments
 *
 * Author: Johan Hovold <jhovold@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश <linux/mfd/lm3533.h>


#घोषणा LM3533_MAX_CURRENT_MIN		5000
#घोषणा LM3533_MAX_CURRENT_MAX		29800
#घोषणा LM3533_MAX_CURRENT_STEP		800

#घोषणा LM3533_PWM_MAX			0x3f

#घोषणा LM3533_REG_PWM_BASE		0x14
#घोषणा LM3533_REG_MAX_CURRENT_BASE	0x1f
#घोषणा LM3533_REG_CTRLBANK_ENABLE	0x27
#घोषणा LM3533_REG_BRIGHTNESS_BASE	0x40


अटल अंतरभूत u8 lm3533_ctrlbank_get_reg(काष्ठा lm3533_ctrlbank *cb, u8 base)
अणु
	वापस base + cb->id;
पूर्ण

पूर्णांक lm3533_ctrlbank_enable(काष्ठा lm3533_ctrlbank *cb)
अणु
	u8 mask;
	पूर्णांक ret;

	dev_dbg(cb->dev, "%s - %d\n", __func__, cb->id);

	mask = 1 << cb->id;
	ret = lm3533_update(cb->lm3533, LM3533_REG_CTRLBANK_ENABLE,
								mask, mask);
	अगर (ret)
		dev_err(cb->dev, "failed to enable ctrlbank %d\n", cb->id);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_enable);

पूर्णांक lm3533_ctrlbank_disable(काष्ठा lm3533_ctrlbank *cb)
अणु
	u8 mask;
	पूर्णांक ret;

	dev_dbg(cb->dev, "%s - %d\n", __func__, cb->id);

	mask = 1 << cb->id;
	ret = lm3533_update(cb->lm3533, LM3533_REG_CTRLBANK_ENABLE, 0, mask);
	अगर (ret)
		dev_err(cb->dev, "failed to disable ctrlbank %d\n", cb->id);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_disable);

/*
 * Full-scale current.
 *
 * imax		5000 - 29800 uA (800 uA step)
 */
पूर्णांक lm3533_ctrlbank_set_max_current(काष्ठा lm3533_ctrlbank *cb, u16 imax)
अणु
	u8 reg;
	u8 val;
	पूर्णांक ret;

	अगर (imax < LM3533_MAX_CURRENT_MIN || imax > LM3533_MAX_CURRENT_MAX)
		वापस -EINVAL;

	val = (imax - LM3533_MAX_CURRENT_MIN) / LM3533_MAX_CURRENT_STEP;

	reg = lm3533_ctrlbank_get_reg(cb, LM3533_REG_MAX_CURRENT_BASE);
	ret = lm3533_ग_लिखो(cb->lm3533, reg, val);
	अगर (ret)
		dev_err(cb->dev, "failed to set max current\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_set_max_current);

पूर्णांक lm3533_ctrlbank_set_brightness(काष्ठा lm3533_ctrlbank *cb, u8 val)
अणु
	u8 reg;
	पूर्णांक ret;

	reg = lm3533_ctrlbank_get_reg(cb, LM3533_REG_BRIGHTNESS_BASE);
	ret = lm3533_ग_लिखो(cb->lm3533, reg, val);
	अगर (ret)
		dev_err(cb->dev, "failed to set brightness\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_set_brightness);

पूर्णांक lm3533_ctrlbank_get_brightness(काष्ठा lm3533_ctrlbank *cb, u8 *val)
अणु
	u8 reg;
	पूर्णांक ret;

	reg = lm3533_ctrlbank_get_reg(cb, LM3533_REG_BRIGHTNESS_BASE);
	ret = lm3533_पढ़ो(cb->lm3533, reg, val);
	अगर (ret)
		dev_err(cb->dev, "failed to get brightness\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_get_brightness);

/*
 * PWM-input control mask:
 *
 *   bit 5 - PWM-input enabled in Zone 4
 *   bit 4 - PWM-input enabled in Zone 3
 *   bit 3 - PWM-input enabled in Zone 2
 *   bit 2 - PWM-input enabled in Zone 1
 *   bit 1 - PWM-input enabled in Zone 0
 *   bit 0 - PWM-input enabled
 */
पूर्णांक lm3533_ctrlbank_set_pwm(काष्ठा lm3533_ctrlbank *cb, u8 val)
अणु
	u8 reg;
	पूर्णांक ret;

	अगर (val > LM3533_PWM_MAX)
		वापस -EINVAL;

	reg = lm3533_ctrlbank_get_reg(cb, LM3533_REG_PWM_BASE);
	ret = lm3533_ग_लिखो(cb->lm3533, reg, val);
	अगर (ret)
		dev_err(cb->dev, "failed to set PWM mask\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_set_pwm);

पूर्णांक lm3533_ctrlbank_get_pwm(काष्ठा lm3533_ctrlbank *cb, u8 *val)
अणु
	u8 reg;
	पूर्णांक ret;

	reg = lm3533_ctrlbank_get_reg(cb, LM3533_REG_PWM_BASE);
	ret = lm3533_पढ़ो(cb->lm3533, reg, val);
	अगर (ret)
		dev_err(cb->dev, "failed to get PWM mask\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ctrlbank_get_pwm);

MODULE_AUTHOR("Johan Hovold <jhovold@gmail.com>");
MODULE_DESCRIPTION("LM3533 Control Bank interface");
MODULE_LICENSE("GPL");
