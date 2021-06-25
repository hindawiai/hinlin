<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SiRFstar GNSS receiver driver
 *
 * Copyright (C) 2018 Johan Hovold <johan@kernel.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gnss.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sched.h>
#समावेश <linux/serdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#घोषणा SIRF_BOOT_DELAY			500
#घोषणा SIRF_ON_OFF_PULSE_TIME		100
#घोषणा SIRF_ACTIVATE_TIMEOUT		200
#घोषणा SIRF_HIBERNATE_TIMEOUT		200
/*
 * If no data arrives क्रम this समय, we assume that the chip is off.
 * REVISIT: The report cycle is configurable and can be several minutes दीर्घ,
 * so this will only work reliably अगर the report cycle is set to a reasonable
 * low value. Also घातer saving settings (like send data only on movement)
 * might things work even worse.
 * Workaround might be to parse shutकरोwn or bootup messages.
 */
#घोषणा SIRF_REPORT_CYCLE	2000

काष्ठा sirf_data अणु
	काष्ठा gnss_device *gdev;
	काष्ठा serdev_device *serdev;
	speed_t	speed;
	काष्ठा regulator *vcc;
	काष्ठा regulator *lna;
	काष्ठा gpio_desc *on_off;
	काष्ठा gpio_desc *wakeup;
	पूर्णांक irq;
	bool active;

	काष्ठा mutex gdev_mutex;
	bool खोलो;

	काष्ठा mutex serdev_mutex;
	पूर्णांक serdev_count;

	रुको_queue_head_t घातer_रुको;
पूर्ण;

अटल पूर्णांक sirf_serdev_खोलो(काष्ठा sirf_data *data)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&data->serdev_mutex);
	अगर (++data->serdev_count == 1) अणु
		ret = serdev_device_खोलो(data->serdev);
		अगर (ret) अणु
			data->serdev_count--;
			जाओ out_unlock;
		पूर्ण

		serdev_device_set_baudrate(data->serdev, data->speed);
		serdev_device_set_flow_control(data->serdev, false);
	पूर्ण

out_unlock:
	mutex_unlock(&data->serdev_mutex);

	वापस ret;
पूर्ण

अटल व्योम sirf_serdev_बंद(काष्ठा sirf_data *data)
अणु
	mutex_lock(&data->serdev_mutex);
	अगर (--data->serdev_count == 0)
		serdev_device_बंद(data->serdev);
	mutex_unlock(&data->serdev_mutex);
पूर्ण

अटल पूर्णांक sirf_खोलो(काष्ठा gnss_device *gdev)
अणु
	काष्ठा sirf_data *data = gnss_get_drvdata(gdev);
	काष्ठा serdev_device *serdev = data->serdev;
	पूर्णांक ret;

	mutex_lock(&data->gdev_mutex);
	data->खोलो = true;
	mutex_unlock(&data->gdev_mutex);

	ret = sirf_serdev_खोलो(data);
	अगर (ret) अणु
		mutex_lock(&data->gdev_mutex);
		data->खोलो = false;
		mutex_unlock(&data->gdev_mutex);
		वापस ret;
	पूर्ण

	ret = pm_runसमय_get_sync(&serdev->dev);
	अगर (ret < 0) अणु
		dev_err(&gdev->dev, "failed to runtime resume: %d\n", ret);
		pm_runसमय_put_noidle(&serdev->dev);
		जाओ err_बंद;
	पूर्ण

	वापस 0;

err_बंद:
	sirf_serdev_बंद(data);

	mutex_lock(&data->gdev_mutex);
	data->खोलो = false;
	mutex_unlock(&data->gdev_mutex);

	वापस ret;
पूर्ण

अटल व्योम sirf_बंद(काष्ठा gnss_device *gdev)
अणु
	काष्ठा sirf_data *data = gnss_get_drvdata(gdev);
	काष्ठा serdev_device *serdev = data->serdev;

	sirf_serdev_बंद(data);

	pm_runसमय_put(&serdev->dev);

	mutex_lock(&data->gdev_mutex);
	data->खोलो = false;
	mutex_unlock(&data->gdev_mutex);
पूर्ण

अटल पूर्णांक sirf_ग_लिखो_raw(काष्ठा gnss_device *gdev, स्थिर अचिन्हित अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा sirf_data *data = gnss_get_drvdata(gdev);
	काष्ठा serdev_device *serdev = data->serdev;
	पूर्णांक ret;

	/* ग_लिखो is only buffered synchronously */
	ret = serdev_device_ग_लिखो(serdev, buf, count, MAX_SCHEDULE_TIMEOUT);
	अगर (ret < 0 || ret < count)
		वापस ret;

	/* FIXME: determine अगर पूर्णांकerrupted? */
	serdev_device_रुको_until_sent(serdev, 0);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा gnss_operations sirf_gnss_ops = अणु
	.खोलो		= sirf_खोलो,
	.बंद		= sirf_बंद,
	.ग_लिखो_raw	= sirf_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक sirf_receive_buf(काष्ठा serdev_device *serdev,
				स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sirf_data *data = serdev_device_get_drvdata(serdev);
	काष्ठा gnss_device *gdev = data->gdev;
	पूर्णांक ret = 0;

	अगर (!data->wakeup && !data->active) अणु
		data->active = true;
		wake_up_पूर्णांकerruptible(&data->घातer_रुको);
	पूर्ण

	mutex_lock(&data->gdev_mutex);
	अगर (data->खोलो)
		ret = gnss_insert_raw(gdev, buf, count);
	mutex_unlock(&data->gdev_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops sirf_serdev_ops = अणु
	.receive_buf	= sirf_receive_buf,
	.ग_लिखो_wakeup	= serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल irqवापस_t sirf_wakeup_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sirf_data *data = dev_id;
	काष्ठा device *dev = &data->serdev->dev;
	पूर्णांक ret;

	ret = gpiod_get_value_cansleep(data->wakeup);
	dev_dbg(dev, "%s - wakeup = %d\n", __func__, ret);
	अगर (ret < 0)
		जाओ out;

	data->active = ret;
	wake_up_पूर्णांकerruptible(&data->घातer_रुको);
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sirf_रुको_क्रम_घातer_state_nowakeup(काष्ठा sirf_data *data,
						bool active,
						अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	/* Wait क्रम state change (including any shutकरोwn messages). */
	msleep(समयout);

	/* Wait क्रम data reception or समयout. */
	data->active = false;
	ret = रुको_event_पूर्णांकerruptible_समयout(data->घातer_रुको,
			data->active, msecs_to_jअगरfies(SIRF_REPORT_CYCLE));
	अगर (ret < 0)
		वापस ret;

	अगर (ret > 0 && !active)
		वापस -ETIMEDOUT;

	अगर (ret == 0 && active)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक sirf_रुको_क्रम_घातer_state(काष्ठा sirf_data *data, bool active,
					अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	अगर (!data->wakeup)
		वापस sirf_रुको_क्रम_घातer_state_nowakeup(data, active, समयout);

	ret = रुको_event_पूर्णांकerruptible_समयout(data->घातer_रुको,
			data->active == active, msecs_to_jअगरfies(समयout));
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0) अणु
		dev_warn(&data->serdev->dev, "timeout waiting for active state = %d\n",
				active);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sirf_pulse_on_off(काष्ठा sirf_data *data)
अणु
	gpiod_set_value_cansleep(data->on_off, 1);
	msleep(SIRF_ON_OFF_PULSE_TIME);
	gpiod_set_value_cansleep(data->on_off, 0);
पूर्ण

अटल पूर्णांक sirf_set_active(काष्ठा sirf_data *data, bool active)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक retries = 3;
	पूर्णांक ret;

	अगर (active)
		समयout = SIRF_ACTIVATE_TIMEOUT;
	अन्यथा
		समयout = SIRF_HIBERNATE_TIMEOUT;

	अगर (!data->wakeup) अणु
		ret = sirf_serdev_खोलो(data);
		अगर (ret)
			वापस ret;
	पूर्ण

	करो अणु
		sirf_pulse_on_off(data);
		ret = sirf_रुको_क्रम_घातer_state(data, active, समयout);
	पूर्ण जबतक (ret == -ETIMEDOUT && retries--);

	अगर (!data->wakeup)
		sirf_serdev_बंद(data);

	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sirf_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sirf_data *data = dev_get_drvdata(dev);
	पूर्णांक ret2;
	पूर्णांक ret;

	अगर (data->on_off)
		ret = sirf_set_active(data, false);
	अन्यथा
		ret = regulator_disable(data->vcc);

	अगर (ret)
		वापस ret;

	ret = regulator_disable(data->lna);
	अगर (ret)
		जाओ err_reenable;

	वापस 0;

err_reenable:
	अगर (data->on_off)
		ret2 = sirf_set_active(data, true);
	अन्यथा
		ret2 = regulator_enable(data->vcc);

	अगर (ret2)
		dev_err(dev,
			"failed to reenable power on failed suspend: %d\n",
			ret2);

	वापस ret;
पूर्ण

अटल पूर्णांक sirf_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sirf_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_enable(data->lna);
	अगर (ret)
		वापस ret;

	अगर (data->on_off)
		ret = sirf_set_active(data, true);
	अन्यथा
		ret = regulator_enable(data->vcc);

	अगर (ret)
		जाओ err_disable_lna;

	वापस 0;

err_disable_lna:
	regulator_disable(data->lna);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sirf_suspend(काष्ठा device *dev)
अणु
	काष्ठा sirf_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (!pm_runसमय_suspended(dev))
		ret = sirf_runसमय_suspend(dev);

	अगर (data->wakeup)
		disable_irq(data->irq);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sirf_resume(काष्ठा device *dev)
अणु
	काष्ठा sirf_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (data->wakeup)
		enable_irq(data->irq);

	अगर (!pm_runसमय_suspended(dev))
		ret = sirf_runसमय_resume(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sirf_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sirf_suspend, sirf_resume)
	SET_RUNTIME_PM_OPS(sirf_runसमय_suspend, sirf_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक sirf_parse_dt(काष्ठा serdev_device *serdev)
अणु
	काष्ठा sirf_data *data = serdev_device_get_drvdata(serdev);
	काष्ठा device_node *node = serdev->dev.of_node;
	u32 speed = 9600;

	of_property_पढ़ो_u32(node, "current-speed", &speed);

	data->speed = speed;

	वापस 0;
पूर्ण

अटल पूर्णांक sirf_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा device *dev = &serdev->dev;
	काष्ठा gnss_device *gdev;
	काष्ठा sirf_data *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	gdev = gnss_allocate_device(dev);
	अगर (!gdev)
		वापस -ENOMEM;

	gdev->type = GNSS_TYPE_SIRF;
	gdev->ops = &sirf_gnss_ops;
	gnss_set_drvdata(gdev, data);

	data->serdev = serdev;
	data->gdev = gdev;

	mutex_init(&data->gdev_mutex);
	mutex_init(&data->serdev_mutex);
	init_रुकोqueue_head(&data->घातer_रुको);

	serdev_device_set_drvdata(serdev, data);
	serdev_device_set_client_ops(serdev, &sirf_serdev_ops);

	ret = sirf_parse_dt(serdev);
	अगर (ret)
		जाओ err_put_device;

	data->vcc = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(data->vcc)) अणु
		ret = PTR_ERR(data->vcc);
		जाओ err_put_device;
	पूर्ण

	data->lna = devm_regulator_get(dev, "lna");
	अगर (IS_ERR(data->lna)) अणु
		ret = PTR_ERR(data->lna);
		जाओ err_put_device;
	पूर्ण

	data->on_off = devm_gpiod_get_optional(dev, "sirf,onoff",
			GPIOD_OUT_LOW);
	अगर (IS_ERR(data->on_off)) अणु
		ret = PTR_ERR(data->on_off);
		जाओ err_put_device;
	पूर्ण

	अगर (data->on_off) अणु
		data->wakeup = devm_gpiod_get_optional(dev, "sirf,wakeup",
				GPIOD_IN);
		अगर (IS_ERR(data->wakeup)) अणु
			ret = PTR_ERR(data->wakeup);
			जाओ err_put_device;
		पूर्ण

		ret = regulator_enable(data->vcc);
		अगर (ret)
			जाओ err_put_device;

		/* Wait क्रम chip to boot पूर्णांकo hibernate mode. */
		msleep(SIRF_BOOT_DELAY);
	पूर्ण

	अगर (data->wakeup) अणु
		ret = gpiod_get_value_cansleep(data->wakeup);
		अगर (ret < 0)
			जाओ err_disable_vcc;
		data->active = ret;

		ret = gpiod_to_irq(data->wakeup);
		अगर (ret < 0)
			जाओ err_disable_vcc;
		data->irq = ret;

		ret = request_thपढ़ोed_irq(data->irq, शून्य, sirf_wakeup_handler,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"wakeup", data);
		अगर (ret)
			जाओ err_disable_vcc;
	पूर्ण

	अगर (data->on_off) अणु
		अगर (!data->wakeup) अणु
			data->active = false;

			ret = sirf_serdev_खोलो(data);
			अगर (ret)
				जाओ err_disable_vcc;

			msleep(SIRF_REPORT_CYCLE);
			sirf_serdev_बंद(data);
		पूर्ण

		/* Force hibernate mode अगर alपढ़ोy active. */
		अगर (data->active) अणु
			ret = sirf_set_active(data, false);
			अगर (ret) अणु
				dev_err(dev, "failed to set hibernate mode: %d\n",
						ret);
				जाओ err_मुक्त_irq;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PM)) अणु
		pm_runसमय_set_suspended(dev);	/* clear runसमय_error flag */
		pm_runसमय_enable(dev);
	पूर्ण अन्यथा अणु
		ret = sirf_runसमय_resume(dev);
		अगर (ret < 0)
			जाओ err_मुक्त_irq;
	पूर्ण

	ret = gnss_रेजिस्टर_device(gdev);
	अगर (ret)
		जाओ err_disable_rpm;

	वापस 0;

err_disable_rpm:
	अगर (IS_ENABLED(CONFIG_PM))
		pm_runसमय_disable(dev);
	अन्यथा
		sirf_runसमय_suspend(dev);
err_मुक्त_irq:
	अगर (data->wakeup)
		मुक्त_irq(data->irq, data);
err_disable_vcc:
	अगर (data->on_off)
		regulator_disable(data->vcc);
err_put_device:
	gnss_put_device(data->gdev);

	वापस ret;
पूर्ण

अटल व्योम sirf_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा sirf_data *data = serdev_device_get_drvdata(serdev);

	gnss_deरेजिस्टर_device(data->gdev);

	अगर (IS_ENABLED(CONFIG_PM))
		pm_runसमय_disable(&serdev->dev);
	अन्यथा
		sirf_runसमय_suspend(&serdev->dev);

	अगर (data->wakeup)
		मुक्त_irq(data->irq, data);

	अगर (data->on_off)
		regulator_disable(data->vcc);

	gnss_put_device(data->gdev);
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sirf_of_match[] = अणु
	अणु .compatible = "fastrax,uc430" पूर्ण,
	अणु .compatible = "linx,r4" पूर्ण,
	अणु .compatible = "wi2wi,w2sg0004" पूर्ण,
	अणु .compatible = "wi2wi,w2sg0008i" पूर्ण,
	अणु .compatible = "wi2wi,w2sg0084i" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sirf_of_match);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver sirf_driver = अणु
	.driver	= अणु
		.name		= "gnss-sirf",
		.of_match_table	= of_match_ptr(sirf_of_match),
		.pm		= &sirf_pm_ops,
	पूर्ण,
	.probe	= sirf_probe,
	.हटाओ	= sirf_हटाओ,
पूर्ण;
module_serdev_device_driver(sirf_driver);

MODULE_AUTHOR("Johan Hovold <johan@kernel.org>");
MODULE_DESCRIPTION("SiRFstar GNSS receiver driver");
MODULE_LICENSE("GPL v2");
