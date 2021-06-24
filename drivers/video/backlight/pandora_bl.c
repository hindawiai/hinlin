<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम Panकरोra handheld.
 * Panकरोra uses TWL4030 PWM0 -> TPS61161 combo क्रम control backlight.
 * Based on pwm_bl.c
 *
 * Copyright 2009,2012 Graधठvydas Ignotas <notasas@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/err.h>

#घोषणा TWL_PWM0_ON		0x00
#घोषणा TWL_PWM0_OFF		0x01

#घोषणा TWL_INTBR_GPBR1		0x0c
#घोषणा TWL_INTBR_PMBR1		0x0d

#घोषणा TWL_PMBR1_PWM0_MUXMASK	0x0c
#घोषणा TWL_PMBR1_PWM0		0x04
#घोषणा PWM0_CLK_ENABLE		BIT(0)
#घोषणा PWM0_ENABLE		BIT(2)

/* range accepted by hardware */
#घोषणा MIN_VALUE 9
#घोषणा MAX_VALUE 63
#घोषणा MAX_USER_VALUE (MAX_VALUE - MIN_VALUE)

काष्ठा panकरोra_निजी अणु
	अचिन्हित old_state;
#घोषणा PANDORABL_WAS_OFF 1
पूर्ण;

अटल पूर्णांक panकरोra_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	पूर्णांक brightness = bl->props.brightness;
	काष्ठा panकरोra_निजी *priv = bl_get_data(bl);
	u8 r;

	अगर (bl->props.घातer != FB_BLANK_UNBLANK)
		brightness = 0;
	अगर (bl->props.state & BL_CORE_FBBLANK)
		brightness = 0;
	अगर (bl->props.state & BL_CORE_SUSPENDED)
		brightness = 0;

	अगर ((अचिन्हित पूर्णांक)brightness > MAX_USER_VALUE)
		brightness = MAX_USER_VALUE;

	अगर (brightness == 0) अणु
		अगर (priv->old_state == PANDORABL_WAS_OFF)
			जाओ करोne;

		/* first disable PWM0 output, then घड़ी */
		twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &r, TWL_INTBR_GPBR1);
		r &= ~PWM0_ENABLE;
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, r, TWL_INTBR_GPBR1);
		r &= ~PWM0_CLK_ENABLE;
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, r, TWL_INTBR_GPBR1);

		जाओ करोne;
	पूर्ण

	अगर (priv->old_state == PANDORABL_WAS_OFF) अणु
		/*
		 * set PWM duty cycle to max. TPS61161 seems to use this
		 * to calibrate it's PWM sensitivity when it starts.
		 */
		twl_i2c_ग_लिखो_u8(TWL_MODULE_PWM, MAX_VALUE, TWL_PWM0_OFF);

		/* first enable घड़ी, then PWM0 out */
		twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &r, TWL_INTBR_GPBR1);
		r &= ~PWM0_ENABLE;
		r |= PWM0_CLK_ENABLE;
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, r, TWL_INTBR_GPBR1);
		r |= PWM0_ENABLE;
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, r, TWL_INTBR_GPBR1);

		/*
		 * TI made it very easy to enable digital control, so easy that
		 * it often triggers unपूर्णांकentionally and disabes PWM control,
		 * so रुको until 1 wire mode detection winकरोw ends.
		 */
		usleep_range(2000, 10000);
	पूर्ण

	twl_i2c_ग_लिखो_u8(TWL_MODULE_PWM, MIN_VALUE + brightness, TWL_PWM0_OFF);

करोne:
	अगर (brightness != 0)
		priv->old_state = 0;
	अन्यथा
		priv->old_state = PANDORABL_WAS_OFF;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops panकरोra_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= panकरोra_backlight_update_status,
पूर्ण;

अटल पूर्णांक panकरोra_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bl;
	काष्ठा panकरोra_निजी *priv;
	u8 r;

	priv = devm_kदो_स्मृति(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&pdev->dev, "failed to allocate driver private data\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.max_brightness = MAX_USER_VALUE;
	props.type = BACKLIGHT_RAW;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, pdev->name, &pdev->dev,
					priv, &panकरोra_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	platक्रमm_set_drvdata(pdev, bl);

	/* 64 cycle period, ON position 0 */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PWM, 0x80, TWL_PWM0_ON);

	priv->old_state = PANDORABL_WAS_OFF;
	bl->props.brightness = MAX_USER_VALUE;
	backlight_update_status(bl);

	/* enable PWM function in pin mux */
	twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &r, TWL_INTBR_PMBR1);
	r &= ~TWL_PMBR1_PWM0_MUXMASK;
	r |= TWL_PMBR1_PWM0;
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, r, TWL_INTBR_PMBR1);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver panकरोra_backlight_driver = अणु
	.driver		= अणु
		.name	= "pandora-backlight",
	पूर्ण,
	.probe		= panकरोra_backlight_probe,
पूर्ण;

module_platक्रमm_driver(panकरोra_backlight_driver);

MODULE_AUTHOR("Graधठvydas Ignotas <notasas@gmail.com>");
MODULE_DESCRIPTION("Pandora Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pandora-backlight");
