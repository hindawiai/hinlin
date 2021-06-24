<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * h3600 aपंचांगel micro companion support, touchscreen subdevice
 * Author : Alessandro Gardich <gremlin@gremlin.it>
 * Author : Dmitry Artamonow <mad_soft@inbox.ru>
 * Author : Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/ipaq-micro.h>

काष्ठा touchscreen_data अणु
	काष्ठा input_dev *input;
	काष्ठा ipaq_micro *micro;
पूर्ण;

अटल व्योम micro_ts_receive(व्योम *data, पूर्णांक len, अचिन्हित अक्षर *msg)
अणु
	काष्ठा touchscreen_data *ts = data;

	अगर (len == 4) अणु
		input_report_असल(ts->input, ABS_X,
				 be16_to_cpup((__be16 *) &msg[2]));
		input_report_असल(ts->input, ABS_Y,
				 be16_to_cpup((__be16 *) &msg[0]));
		input_report_key(ts->input, BTN_TOUCH, 1);
		input_sync(ts->input);
	पूर्ण अन्यथा अगर (len == 0) अणु
		input_report_असल(ts->input, ABS_X, 0);
		input_report_असल(ts->input, ABS_Y, 0);
		input_report_key(ts->input, BTN_TOUCH, 0);
		input_sync(ts->input);
	पूर्ण
पूर्ण

अटल व्योम micro_ts_toggle_receive(काष्ठा touchscreen_data *ts, bool enable)
अणु
	काष्ठा ipaq_micro *micro = ts->micro;

	spin_lock_irq(&micro->lock);

	अगर (enable) अणु
		micro->ts = micro_ts_receive;
		micro->ts_data = ts;
	पूर्ण अन्यथा अणु
		micro->ts = शून्य;
		micro->ts_data = शून्य;
	पूर्ण

	spin_unlock_irq(&ts->micro->lock);
पूर्ण

अटल पूर्णांक micro_ts_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा touchscreen_data *ts = input_get_drvdata(input);

	micro_ts_toggle_receive(ts, true);

	वापस 0;
पूर्ण

अटल व्योम micro_ts_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा touchscreen_data *ts = input_get_drvdata(input);

	micro_ts_toggle_receive(ts, false);
पूर्ण

अटल पूर्णांक micro_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipaq_micro *micro = dev_get_drvdata(pdev->dev.parent);
	काष्ठा touchscreen_data *ts;
	पूर्णांक error;

	ts = devm_kzalloc(&pdev->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->micro = micro;

	ts->input = devm_input_allocate_device(&pdev->dev);
	अगर (!ts->input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->input->name = "ipaq micro ts";
	ts->input->खोलो = micro_ts_खोलो;
	ts->input->बंद = micro_ts_बंद;

	input_set_drvdata(ts->input, ts);

	input_set_capability(ts->input, EV_KEY, BTN_TOUCH);
	input_set_capability(ts->input, EV_ABS, ABS_X);
	input_set_capability(ts->input, EV_ABS, ABS_Y);
	input_set_असल_params(ts->input, ABS_X, 0, 1023, 0, 0);
	input_set_असल_params(ts->input, ABS_Y, 0, 1023, 0, 0);

	error = input_रेजिस्टर_device(ts->input);
	अगर (error) अणु
		dev_err(&pdev->dev, "error registering touch input\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ts);

	dev_info(&pdev->dev, "iPAQ micro touchscreen\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused micro_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा touchscreen_data *ts = dev_get_drvdata(dev);

	micro_ts_toggle_receive(ts, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused micro_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा touchscreen_data *ts = dev_get_drvdata(dev);
	काष्ठा input_dev *input = ts->input;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input))
		micro_ts_toggle_receive(ts, true);

	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops micro_ts_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(micro_ts_suspend, micro_ts_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver micro_ts_device_driver = अणु
	.driver	= अणु
		.name	= "ipaq-micro-ts",
		.pm	= &micro_ts_dev_pm_ops,
	पूर्ण,
	.probe	= micro_ts_probe,
पूर्ण;
module_platक्रमm_driver(micro_ts_device_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("driver for iPAQ Atmel micro touchscreen");
MODULE_ALIAS("platform:ipaq-micro-ts");
