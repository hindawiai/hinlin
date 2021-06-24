<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Touchscreen driver क्रम Dialog Semiconductor DA9034
 *
 * Copyright (C) 2006-2008 Marvell International Ltd.
 *	Fengwei Yin <fengwei.yin@marvell.com>
 *	Bin Yang  <bin.yang@marvell.com>
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mfd/da903x.h>
#समावेश <linux/slab.h>

#घोषणा DA9034_MANUAL_CTRL	0x50
#घोषणा DA9034_LDO_ADC_EN	(1 << 4)

#घोषणा DA9034_AUTO_CTRL1	0x51

#घोषणा DA9034_AUTO_CTRL2	0x52
#घोषणा DA9034_AUTO_TSI_EN	(1 << 3)
#घोषणा DA9034_PEN_DETECT	(1 << 4)

#घोषणा DA9034_TSI_CTRL1	0x53
#घोषणा DA9034_TSI_CTRL2	0x54
#घोषणा DA9034_TSI_X_MSB	0x6c
#घोषणा DA9034_TSI_Y_MSB	0x6d
#घोषणा DA9034_TSI_XY_LSB	0x6e

क्रमागत अणु
	STATE_IDLE,	/* रुको क्रम penकरोwn */
	STATE_BUSY,	/* TSI busy sampling */
	STATE_STOP,	/* sample available */
	STATE_WAIT,	/* Wait to start next sample */
पूर्ण;

क्रमागत अणु
	EVENT_PEN_DOWN,
	EVENT_PEN_UP,
	EVENT_TSI_READY,
	EVENT_TIMEDOUT,
पूर्ण;

काष्ठा da9034_touch अणु
	काष्ठा device		*da9034_dev;
	काष्ठा input_dev	*input_dev;

	काष्ठा delayed_work	tsi_work;
	काष्ठा notअगरier_block	notअगरier;

	पूर्णांक	state;

	पूर्णांक	पूर्णांकerval_ms;
	पूर्णांक	x_inverted;
	पूर्णांक	y_inverted;

	पूर्णांक	last_x;
	पूर्णांक	last_y;
पूर्ण;

अटल अंतरभूत पूर्णांक is_pen_करोwn(काष्ठा da9034_touch *touch)
अणु
	वापस da903x_query_status(touch->da9034_dev, DA9034_STATUS_PEN_DOWN);
पूर्ण

अटल अंतरभूत पूर्णांक detect_pen_करोwn(काष्ठा da9034_touch *touch, पूर्णांक on)
अणु
	अगर (on)
		वापस da903x_set_bits(touch->da9034_dev,
				DA9034_AUTO_CTRL2, DA9034_PEN_DETECT);
	अन्यथा
		वापस da903x_clr_bits(touch->da9034_dev,
				DA9034_AUTO_CTRL2, DA9034_PEN_DETECT);
पूर्ण

अटल पूर्णांक पढ़ो_tsi(काष्ठा da9034_touch *touch)
अणु
	uपूर्णांक8_t _x, _y, _v;
	पूर्णांक ret;

	ret = da903x_पढ़ो(touch->da9034_dev, DA9034_TSI_X_MSB, &_x);
	अगर (ret)
		वापस ret;

	ret = da903x_पढ़ो(touch->da9034_dev, DA9034_TSI_Y_MSB, &_y);
	अगर (ret)
		वापस ret;

	ret = da903x_पढ़ो(touch->da9034_dev, DA9034_TSI_XY_LSB, &_v);
	अगर (ret)
		वापस ret;

	touch->last_x = ((_x << 2) & 0x3fc) | (_v & 0x3);
	touch->last_y = ((_y << 2) & 0x3fc) | ((_v & 0xc) >> 2);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक start_tsi(काष्ठा da9034_touch *touch)
अणु
	वापस da903x_set_bits(touch->da9034_dev,
			DA9034_AUTO_CTRL2, DA9034_AUTO_TSI_EN);
पूर्ण

अटल अंतरभूत पूर्णांक stop_tsi(काष्ठा da9034_touch *touch)
अणु
	वापस da903x_clr_bits(touch->da9034_dev,
			DA9034_AUTO_CTRL2, DA9034_AUTO_TSI_EN);
पूर्ण

अटल अंतरभूत व्योम report_pen_करोwn(काष्ठा da9034_touch *touch)
अणु
	पूर्णांक x = touch->last_x;
	पूर्णांक y = touch->last_y;

	x &= 0xfff;
	अगर (touch->x_inverted)
		x = 1024 - x;
	y &= 0xfff;
	अगर (touch->y_inverted)
		y = 1024 - y;

	input_report_असल(touch->input_dev, ABS_X, x);
	input_report_असल(touch->input_dev, ABS_Y, y);
	input_report_key(touch->input_dev, BTN_TOUCH, 1);

	input_sync(touch->input_dev);
पूर्ण

अटल अंतरभूत व्योम report_pen_up(काष्ठा da9034_touch *touch)
अणु
	input_report_key(touch->input_dev, BTN_TOUCH, 0);
	input_sync(touch->input_dev);
पूर्ण

अटल व्योम da9034_event_handler(काष्ठा da9034_touch *touch, पूर्णांक event)
अणु
	पूर्णांक err;

	चयन (touch->state) अणु
	हाल STATE_IDLE:
		अगर (event != EVENT_PEN_DOWN)
			अवरोध;

		/* Enable स्वतः measurement of the TSI, this will
		 * स्वतःmatically disable pen करोwn detection
		 */
		err = start_tsi(touch);
		अगर (err)
			जाओ err_reset;

		touch->state = STATE_BUSY;
		अवरोध;

	हाल STATE_BUSY:
		अगर (event != EVENT_TSI_READY)
			अवरोध;

		err = पढ़ो_tsi(touch);
		अगर (err)
			जाओ err_reset;

		/* Disable स्वतः measurement of the TSI, so that
		 * pen करोwn status will be available
		 */
		err = stop_tsi(touch);
		अगर (err)
			जाओ err_reset;

		touch->state = STATE_STOP;

		/* FIXME: PEN_अणुUP/DOWNपूर्ण events are expected to be
		 * available by stopping TSI, but this is found not
		 * always true, delay and simulate such an event
		 * here is more reliable
		 */
		mdelay(1);
		da9034_event_handler(touch,
				     is_pen_करोwn(touch) ? EVENT_PEN_DOWN :
							  EVENT_PEN_UP);
		अवरोध;

	हाल STATE_STOP:
		अगर (event == EVENT_PEN_DOWN) अणु
			report_pen_करोwn(touch);
			schedule_delayed_work(&touch->tsi_work,
				msecs_to_jअगरfies(touch->पूर्णांकerval_ms));
			touch->state = STATE_WAIT;
		पूर्ण

		अगर (event == EVENT_PEN_UP) अणु
			report_pen_up(touch);
			touch->state = STATE_IDLE;
		पूर्ण
		अवरोध;

	हाल STATE_WAIT:
		अगर (event != EVENT_TIMEDOUT)
			अवरोध;

		अगर (is_pen_करोwn(touch)) अणु
			start_tsi(touch);
			touch->state = STATE_BUSY;
		पूर्ण अन्यथा अणु
			report_pen_up(touch);
			touch->state = STATE_IDLE;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस;

err_reset:
	touch->state = STATE_IDLE;
	stop_tsi(touch);
	detect_pen_करोwn(touch, 1);
पूर्ण

अटल व्योम da9034_tsi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9034_touch *touch =
		container_of(work, काष्ठा da9034_touch, tsi_work.work);

	da9034_event_handler(touch, EVENT_TIMEDOUT);
पूर्ण

अटल पूर्णांक da9034_touch_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा da9034_touch *touch =
		container_of(nb, काष्ठा da9034_touch, notअगरier);

	अगर (event & DA9034_EVENT_TSI_READY)
		da9034_event_handler(touch, EVENT_TSI_READY);

	अगर ((event & DA9034_EVENT_PEN_DOWN) && touch->state == STATE_IDLE)
		da9034_event_handler(touch, EVENT_PEN_DOWN);

	वापस 0;
पूर्ण

अटल पूर्णांक da9034_touch_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा da9034_touch *touch = input_get_drvdata(dev);
	पूर्णांक ret;

	ret = da903x_रेजिस्टर_notअगरier(touch->da9034_dev, &touch->notअगरier,
			DA9034_EVENT_PEN_DOWN | DA9034_EVENT_TSI_READY);
	अगर (ret)
		वापस -EBUSY;

	/* Enable ADC LDO */
	ret = da903x_set_bits(touch->da9034_dev,
			DA9034_MANUAL_CTRL, DA9034_LDO_ADC_EN);
	अगर (ret)
		वापस ret;

	/* TSI_DELAY: 3 slots, TSI_SKIP: 3 slots */
	ret = da903x_ग_लिखो(touch->da9034_dev, DA9034_TSI_CTRL1, 0x1b);
	अगर (ret)
		वापस ret;

	ret = da903x_ग_लिखो(touch->da9034_dev, DA9034_TSI_CTRL2, 0x00);
	अगर (ret)
		वापस ret;

	touch->state = STATE_IDLE;
	detect_pen_करोwn(touch, 1);

	वापस 0;
पूर्ण

अटल व्योम da9034_touch_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा da9034_touch *touch = input_get_drvdata(dev);

	da903x_unरेजिस्टर_notअगरier(touch->da9034_dev, &touch->notअगरier,
			DA9034_EVENT_PEN_DOWN | DA9034_EVENT_TSI_READY);

	cancel_delayed_work_sync(&touch->tsi_work);

	touch->state = STATE_IDLE;
	stop_tsi(touch);
	detect_pen_करोwn(touch, 0);

	/* Disable ADC LDO */
	da903x_clr_bits(touch->da9034_dev,
			DA9034_MANUAL_CTRL, DA9034_LDO_ADC_EN);
पूर्ण


अटल पूर्णांक da9034_touch_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9034_touch_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा da9034_touch *touch;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	touch = devm_kzalloc(&pdev->dev, माप(काष्ठा da9034_touch),
			     GFP_KERNEL);
	अगर (!touch) अणु
		dev_err(&pdev->dev, "failed to allocate driver data\n");
		वापस -ENOMEM;
	पूर्ण

	touch->da9034_dev = pdev->dev.parent;

	अगर (pdata) अणु
		touch->पूर्णांकerval_ms	= pdata->पूर्णांकerval_ms;
		touch->x_inverted	= pdata->x_inverted;
		touch->y_inverted	= pdata->y_inverted;
	पूर्ण अन्यथा अणु
		/* fallback पूर्णांकo शेष */
		touch->पूर्णांकerval_ms	= 10;
	पूर्ण

	INIT_DELAYED_WORK(&touch->tsi_work, da9034_tsi_work);
	touch->notअगरier.notअगरier_call = da9034_touch_notअगरier;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name		= pdev->name;
	input_dev->खोलो		= da9034_touch_खोलो;
	input_dev->बंद	= da9034_touch_बंद;
	input_dev->dev.parent	= &pdev->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(ABS_X, input_dev->असलbit);
	__set_bit(ABS_Y, input_dev->असलbit);
	input_set_असल_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 1023, 0, 0);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	touch->input_dev = input_dev;
	input_set_drvdata(input_dev, touch);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9034_touch_driver = अणु
	.driver	= अणु
		.name	= "da9034-touch",
	पूर्ण,
	.probe		= da9034_touch_probe,
पूर्ण;
module_platक्रमm_driver(da9034_touch_driver);

MODULE_DESCRIPTION("Touchscreen driver for Dialog Semiconductor DA9034");
MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>, Bin Yang <bin.yang@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9034-touch");
