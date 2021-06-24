<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic serial GNSS receiver driver
 *
 * Copyright (C) 2018 Johan Hovold <johan@kernel.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gnss.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/serdev.h>
#समावेश <linux/slab.h>

#समावेश "serial.h"

अटल पूर्णांक gnss_serial_खोलो(काष्ठा gnss_device *gdev)
अणु
	काष्ठा gnss_serial *gserial = gnss_get_drvdata(gdev);
	काष्ठा serdev_device *serdev = gserial->serdev;
	पूर्णांक ret;

	ret = serdev_device_खोलो(serdev);
	अगर (ret)
		वापस ret;

	serdev_device_set_baudrate(serdev, gserial->speed);
	serdev_device_set_flow_control(serdev, false);

	ret = pm_runसमय_get_sync(&serdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&serdev->dev);
		जाओ err_बंद;
	पूर्ण

	वापस 0;

err_बंद:
	serdev_device_बंद(serdev);

	वापस ret;
पूर्ण

अटल व्योम gnss_serial_बंद(काष्ठा gnss_device *gdev)
अणु
	काष्ठा gnss_serial *gserial = gnss_get_drvdata(gdev);
	काष्ठा serdev_device *serdev = gserial->serdev;

	serdev_device_बंद(serdev);

	pm_runसमय_put(&serdev->dev);
पूर्ण

अटल पूर्णांक gnss_serial_ग_लिखो_raw(काष्ठा gnss_device *gdev,
		स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gnss_serial *gserial = gnss_get_drvdata(gdev);
	काष्ठा serdev_device *serdev = gserial->serdev;
	पूर्णांक ret;

	/* ग_लिखो is only buffered synchronously */
	ret = serdev_device_ग_लिखो(serdev, buf, count, MAX_SCHEDULE_TIMEOUT);
	अगर (ret < 0 || ret < count)
		वापस ret;

	/* FIXME: determine अगर पूर्णांकerrupted? */
	serdev_device_रुको_until_sent(serdev, 0);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा gnss_operations gnss_serial_gnss_ops = अणु
	.खोलो		= gnss_serial_खोलो,
	.बंद		= gnss_serial_बंद,
	.ग_लिखो_raw	= gnss_serial_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक gnss_serial_receive_buf(काष्ठा serdev_device *serdev,
					स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gnss_serial *gserial = serdev_device_get_drvdata(serdev);
	काष्ठा gnss_device *gdev = gserial->gdev;

	वापस gnss_insert_raw(gdev, buf, count);
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops gnss_serial_serdev_ops = अणु
	.receive_buf	= gnss_serial_receive_buf,
	.ग_लिखो_wakeup	= serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल पूर्णांक gnss_serial_set_घातer(काष्ठा gnss_serial *gserial,
					क्रमागत gnss_serial_pm_state state)
अणु
	अगर (!gserial->ops || !gserial->ops->set_घातer)
		वापस 0;

	वापस gserial->ops->set_घातer(gserial, state);
पूर्ण

/*
 * FIXME: need to provide subdriver शेषs or separate dt parsing from
 * allocation.
 */
अटल पूर्णांक gnss_serial_parse_dt(काष्ठा serdev_device *serdev)
अणु
	काष्ठा gnss_serial *gserial = serdev_device_get_drvdata(serdev);
	काष्ठा device_node *node = serdev->dev.of_node;
	u32 speed = 4800;

	of_property_पढ़ो_u32(node, "current-speed", &speed);

	gserial->speed = speed;

	वापस 0;
पूर्ण

काष्ठा gnss_serial *gnss_serial_allocate(काष्ठा serdev_device *serdev,
						माप_प्रकार data_size)
अणु
	काष्ठा gnss_serial *gserial;
	काष्ठा gnss_device *gdev;
	पूर्णांक ret;

	gserial = kzalloc(माप(*gserial) + data_size, GFP_KERNEL);
	अगर (!gserial)
		वापस ERR_PTR(-ENOMEM);

	gdev = gnss_allocate_device(&serdev->dev);
	अगर (!gdev) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_gserial;
	पूर्ण

	gdev->ops = &gnss_serial_gnss_ops;
	gnss_set_drvdata(gdev, gserial);

	gserial->serdev = serdev;
	gserial->gdev = gdev;

	serdev_device_set_drvdata(serdev, gserial);
	serdev_device_set_client_ops(serdev, &gnss_serial_serdev_ops);

	ret = gnss_serial_parse_dt(serdev);
	अगर (ret)
		जाओ err_put_device;

	वापस gserial;

err_put_device:
	gnss_put_device(gserial->gdev);
err_मुक्त_gserial:
	kमुक्त(gserial);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(gnss_serial_allocate);

व्योम gnss_serial_मुक्त(काष्ठा gnss_serial *gserial)
अणु
	gnss_put_device(gserial->gdev);
	kमुक्त(gserial);
पूर्ण;
EXPORT_SYMBOL_GPL(gnss_serial_मुक्त);

पूर्णांक gnss_serial_रेजिस्टर(काष्ठा gnss_serial *gserial)
अणु
	काष्ठा serdev_device *serdev = gserial->serdev;
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_PM)) अणु
		pm_runसमय_enable(&serdev->dev);
	पूर्ण अन्यथा अणु
		ret = gnss_serial_set_घातer(gserial, GNSS_SERIAL_ACTIVE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = gnss_रेजिस्टर_device(gserial->gdev);
	अगर (ret)
		जाओ err_disable_rpm;

	वापस 0;

err_disable_rpm:
	अगर (IS_ENABLED(CONFIG_PM))
		pm_runसमय_disable(&serdev->dev);
	अन्यथा
		gnss_serial_set_घातer(gserial, GNSS_SERIAL_OFF);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gnss_serial_रेजिस्टर);

व्योम gnss_serial_deरेजिस्टर(काष्ठा gnss_serial *gserial)
अणु
	काष्ठा serdev_device *serdev = gserial->serdev;

	gnss_deरेजिस्टर_device(gserial->gdev);

	अगर (IS_ENABLED(CONFIG_PM))
		pm_runसमय_disable(&serdev->dev);
	अन्यथा
		gnss_serial_set_घातer(gserial, GNSS_SERIAL_OFF);
पूर्ण
EXPORT_SYMBOL_GPL(gnss_serial_deरेजिस्टर);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gnss_serial_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gnss_serial *gserial = dev_get_drvdata(dev);

	वापस gnss_serial_set_घातer(gserial, GNSS_SERIAL_STANDBY);
पूर्ण

अटल पूर्णांक gnss_serial_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gnss_serial *gserial = dev_get_drvdata(dev);

	वापस gnss_serial_set_घातer(gserial, GNSS_SERIAL_ACTIVE);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक gnss_serial_prepare(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 1;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gnss_serial_suspend(काष्ठा device *dev)
अणु
	काष्ठा gnss_serial *gserial = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	/*
	 * FIXME: serdev currently lacks support क्रम managing the underlying
	 * device's wakeup settings. A workaround would be to बंद the serdev
	 * device here अगर it is खोलो.
	 */

	अगर (!pm_runसमय_suspended(dev))
		ret = gnss_serial_set_घातer(gserial, GNSS_SERIAL_STANDBY);

	वापस ret;
पूर्ण

अटल पूर्णांक gnss_serial_resume(काष्ठा device *dev)
अणु
	काष्ठा gnss_serial *gserial = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (!pm_runसमय_suspended(dev))
		ret = gnss_serial_set_घातer(gserial, GNSS_SERIAL_ACTIVE);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

स्थिर काष्ठा dev_pm_ops gnss_serial_pm_ops = अणु
	.prepare	= gnss_serial_prepare,
	SET_SYSTEM_SLEEP_PM_OPS(gnss_serial_suspend, gnss_serial_resume)
	SET_RUNTIME_PM_OPS(gnss_serial_runसमय_suspend, gnss_serial_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(gnss_serial_pm_ops);

MODULE_AUTHOR("Johan Hovold <johan@kernel.org>");
MODULE_DESCRIPTION("Generic serial GNSS receiver driver");
MODULE_LICENSE("GPL v2");
