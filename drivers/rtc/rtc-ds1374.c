<शैली गुरु>
/*
 * RTC client/driver क्रम the Maxim/Dallas DS1374 Real-Time Clock over I2C
 *
 * Based on code by Randy Vinson <rvinson@mvista.com>,
 * which was based on the m41t00.c by Mark Greer <mgreer@mvista.com>.
 *
 * Copyright (C) 2014 Rose Technology
 * Copyright (C) 2006-2007 Freescale Semiconductor
 *
 * 2005 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
/*
 * It would be more efficient to use i2c msgs/i2c_transfer directly but, as
 * recommended in .../Documentation/i2c/writing-clients.rst section
 * "Sending and receiving", using SMBus level communication is preferred.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#अगर_घोषित CONFIG_RTC_DRV_DS1374_WDT
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/reboot.h>
#समावेश <linux/watchकरोg.h>
#पूर्ण_अगर

#घोषणा DS1374_REG_TOD0		0x00 /* Time of Day */
#घोषणा DS1374_REG_TOD1		0x01
#घोषणा DS1374_REG_TOD2		0x02
#घोषणा DS1374_REG_TOD3		0x03
#घोषणा DS1374_REG_WDALM0	0x04 /* Watchकरोg/Alarm */
#घोषणा DS1374_REG_WDALM1	0x05
#घोषणा DS1374_REG_WDALM2	0x06
#घोषणा DS1374_REG_CR		0x07 /* Control */
#घोषणा DS1374_REG_CR_AIE	0x01 /* Alarm Int. Enable */
#घोषणा DS1374_REG_CR_WDSTR	0x08 /* 1=INT, 0=RST */
#घोषणा DS1374_REG_CR_WDALM	0x20 /* 1=Watchकरोg, 0=Alarm */
#घोषणा DS1374_REG_CR_WACE	0x40 /* WD/Alarm counter enable */
#घोषणा DS1374_REG_SR		0x08 /* Status */
#घोषणा DS1374_REG_SR_OSF	0x80 /* Oscillator Stop Flag */
#घोषणा DS1374_REG_SR_AF	0x01 /* Alarm Flag */
#घोषणा DS1374_REG_TCR		0x09 /* Trickle Charge */

अटल स्थिर काष्ठा i2c_device_id ds1374_id[] = अणु
	अणु "ds1374", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds1374_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ds1374_of_match[] = अणु
	अणु .compatible = "dallas,ds1374" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1374_of_match);
#पूर्ण_अगर

काष्ठा ds1374 अणु
	काष्ठा i2c_client *client;
	काष्ठा rtc_device *rtc;
	काष्ठा work_काष्ठा work;
#अगर_घोषित CONFIG_RTC_DRV_DS1374_WDT
	काष्ठा watchकरोg_device wdt;
#पूर्ण_अगर
	/* The mutex protects alarm operations, and prevents a race
	 * between the enable_irq() in the workqueue and the मुक्त_irq()
	 * in the हटाओ function.
	 */
	काष्ठा mutex mutex;
	पूर्णांक निकासing;
पूर्ण;

अटल काष्ठा i2c_driver ds1374_driver;

अटल पूर्णांक ds1374_पढ़ो_rtc(काष्ठा i2c_client *client, u32 *समय,
			   पूर्णांक reg, पूर्णांक nbytes)
अणु
	u8 buf[4];
	पूर्णांक ret;
	पूर्णांक i;

	अगर (WARN_ON(nbytes > 4))
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, nbytes, buf);

	अगर (ret < 0)
		वापस ret;
	अगर (ret < nbytes)
		वापस -EIO;

	क्रम (i = nbytes - 1, *समय = 0; i >= 0; i--)
		*समय = (*समय << 8) | buf[i];

	वापस 0;
पूर्ण

अटल पूर्णांक ds1374_ग_लिखो_rtc(काष्ठा i2c_client *client, u32 समय,
			    पूर्णांक reg, पूर्णांक nbytes)
अणु
	u8 buf[4];
	पूर्णांक i;

	अगर (nbytes > 4) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nbytes; i++) अणु
		buf[i] = समय & 0xff;
		समय >>= 8;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_i2c_block_data(client, reg, nbytes, buf);
पूर्ण

अटल पूर्णांक ds1374_check_rtc_status(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret = 0;
	पूर्णांक control, stat;

	stat = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_SR);
	अगर (stat < 0)
		वापस stat;

	अगर (stat & DS1374_REG_SR_OSF)
		dev_warn(&client->dev,
			 "oscillator discontinuity flagged, time unreliable\n");

	stat &= ~(DS1374_REG_SR_OSF | DS1374_REG_SR_AF);

	ret = i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_SR, stat);
	अगर (ret < 0)
		वापस ret;

	/* If the alarm is pending, clear it beक्रमe requesting
	 * the पूर्णांकerrupt, so an पूर्णांकerrupt event isn't reported
	 * beक्रमe everything is initialized.
	 */

	control = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
	अगर (control < 0)
		वापस control;

	control &= ~(DS1374_REG_CR_WACE | DS1374_REG_CR_AIE);
	वापस i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, control);
पूर्ण

अटल पूर्णांक ds1374_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u32 iसमय;
	पूर्णांक ret;

	ret = ds1374_पढ़ो_rtc(client, &iसमय, DS1374_REG_TOD0, 4);
	अगर (!ret)
		rtc_समय64_to_पंचांग(iसमय, समय);

	वापस ret;
पूर्ण

अटल पूर्णांक ds1374_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ iसमय = rtc_पंचांग_to_समय64(समय);

	वापस ds1374_ग_लिखो_rtc(client, iसमय, DS1374_REG_TOD0, 4);
पूर्ण

#अगर_अघोषित CONFIG_RTC_DRV_DS1374_WDT
/* The ds1374 has a decrementer क्रम an alarm, rather than a comparator.
 * If the समय of day is changed, then the alarm will need to be
 * reset.
 */
अटल पूर्णांक ds1374_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ds1374 *ds1374 = i2c_get_clientdata(client);
	u32 now, cur_alarm;
	पूर्णांक cr, sr;
	पूर्णांक ret = 0;

	अगर (client->irq <= 0)
		वापस -EINVAL;

	mutex_lock(&ds1374->mutex);

	cr = ret = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
	अगर (ret < 0)
		जाओ out;

	sr = ret = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_SR);
	अगर (ret < 0)
		जाओ out;

	ret = ds1374_पढ़ो_rtc(client, &now, DS1374_REG_TOD0, 4);
	अगर (ret)
		जाओ out;

	ret = ds1374_पढ़ो_rtc(client, &cur_alarm, DS1374_REG_WDALM0, 3);
	अगर (ret)
		जाओ out;

	rtc_समय64_to_पंचांग(now + cur_alarm, &alarm->समय);
	alarm->enabled = !!(cr & DS1374_REG_CR_WACE);
	alarm->pending = !!(sr & DS1374_REG_SR_AF);

out:
	mutex_unlock(&ds1374->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ds1374_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ds1374 *ds1374 = i2c_get_clientdata(client);
	काष्ठा rtc_समय now;
	अचिन्हित दीर्घ new_alarm, iसमय;
	पूर्णांक cr;
	पूर्णांक ret = 0;

	अगर (client->irq <= 0)
		वापस -EINVAL;

	ret = ds1374_पढ़ो_समय(dev, &now);
	अगर (ret < 0)
		वापस ret;

	new_alarm = rtc_पंचांग_to_समय64(&alarm->समय);
	iसमय = rtc_पंचांग_to_समय64(&now);

	/* This can happen due to races, in addition to dates that are
	 * truly in the past.  To aव्योम requiring the caller to check क्रम
	 * races, dates in the past are assumed to be in the recent past
	 * (i.e. not something that we'd rather the caller know about via
	 * an error), and the alarm is set to go off as soon as possible.
	 */
	अगर (समय_beक्रमe_eq(new_alarm, iसमय))
		new_alarm = 1;
	अन्यथा
		new_alarm -= iसमय;

	mutex_lock(&ds1374->mutex);

	ret = cr = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
	अगर (ret < 0)
		जाओ out;

	/* Disable any existing alarm beक्रमe setting the new one
	 * (or lack thereof). */
	cr &= ~DS1374_REG_CR_WACE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, cr);
	अगर (ret < 0)
		जाओ out;

	ret = ds1374_ग_लिखो_rtc(client, new_alarm, DS1374_REG_WDALM0, 3);
	अगर (ret)
		जाओ out;

	अगर (alarm->enabled) अणु
		cr |= DS1374_REG_CR_WACE | DS1374_REG_CR_AIE;
		cr &= ~DS1374_REG_CR_WDALM;

		ret = i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, cr);
	पूर्ण

out:
	mutex_unlock(&ds1374->mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t ds1374_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	काष्ठा ds1374 *ds1374 = i2c_get_clientdata(client);

	disable_irq_nosync(irq);
	schedule_work(&ds1374->work);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ds1374_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ds1374 *ds1374 = container_of(work, काष्ठा ds1374, work);
	काष्ठा i2c_client *client = ds1374->client;
	पूर्णांक stat, control;

	mutex_lock(&ds1374->mutex);

	stat = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_SR);
	अगर (stat < 0)
		जाओ unlock;

	अगर (stat & DS1374_REG_SR_AF) अणु
		stat &= ~DS1374_REG_SR_AF;
		i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_SR, stat);

		control = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
		अगर (control < 0)
			जाओ out;

		control &= ~(DS1374_REG_CR_WACE | DS1374_REG_CR_AIE);
		i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, control);

		rtc_update_irq(ds1374->rtc, 1, RTC_AF | RTC_IRQF);
	पूर्ण

out:
	अगर (!ds1374->निकासing)
		enable_irq(client->irq);
unlock:
	mutex_unlock(&ds1374->mutex);
पूर्ण

#अगर_अघोषित CONFIG_RTC_DRV_DS1374_WDT
अटल पूर्णांक ds1374_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ds1374 *ds1374 = i2c_get_clientdata(client);
	पूर्णांक ret;

	mutex_lock(&ds1374->mutex);

	ret = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
	अगर (ret < 0)
		जाओ out;

	अगर (enabled) अणु
		ret |= DS1374_REG_CR_WACE | DS1374_REG_CR_AIE;
		ret &= ~DS1374_REG_CR_WDALM;
	पूर्ण अन्यथा अणु
		ret &= ~DS1374_REG_CR_WACE;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, ret);

out:
	mutex_unlock(&ds1374->mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops ds1374_rtc_ops = अणु
	.पढ़ो_समय = ds1374_पढ़ो_समय,
	.set_समय = ds1374_set_समय,
#अगर_अघोषित CONFIG_RTC_DRV_DS1374_WDT
	.पढ़ो_alarm = ds1374_पढ़ो_alarm,
	.set_alarm = ds1374_set_alarm,
	.alarm_irq_enable = ds1374_alarm_irq_enable,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_RTC_DRV_DS1374_WDT
/*
 *****************************************************************************
 *
 * Watchकरोg Driver
 *
 *****************************************************************************
 */
/* Default margin */
#घोषणा TIMER_MARGIN_DEFAULT	32
#घोषणा TIMER_MARGIN_MIN	1
#घोषणा TIMER_MARGIN_MAX	4095 /* 24-bit value */

अटल पूर्णांक wdt_margin;
module_param(wdt_margin, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_margin, "Watchdog timeout in seconds (default 32s)");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default ="
		__MODULE_STRING(WATCHDOG_NOWAYOUT)")");

अटल स्थिर काष्ठा watchकरोg_info ds1374_wdt_info = अणु
	.identity       = "DS1374 Watchdog",
	.options        = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
						WDIOF_MAGICCLOSE,
पूर्ण;

अटल पूर्णांक ds1374_wdt_समय_रखोout(काष्ठा watchकरोg_device *wdt, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा ds1374 *ds1374 = watchकरोg_get_drvdata(wdt);
	काष्ठा i2c_client *client = ds1374->client;
	पूर्णांक ret, cr;

	wdt->समयout = समयout;

	cr = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
	अगर (cr < 0)
		वापस cr;

	/* Disable any existing watchकरोg/alarm beक्रमe setting the new one */
	cr &= ~DS1374_REG_CR_WACE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, cr);
	अगर (ret < 0)
		वापस ret;

	/* Set new watchकरोg समय */
	समयout = समयout * 4096;
	ret = ds1374_ग_लिखो_rtc(client, समयout, DS1374_REG_WDALM0, 3);
	अगर (ret)
		वापस ret;

	/* Enable watchकरोg समयr */
	cr |= DS1374_REG_CR_WACE | DS1374_REG_CR_WDALM;
	cr &= ~DS1374_REG_CR_WDSTR;/* क्रम RST PIN */
	cr &= ~DS1374_REG_CR_AIE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, cr);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Reload the watchकरोg समयr.  (ie, pat the watchकरोg)
 */
अटल पूर्णांक ds1374_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा ds1374 *ds1374 = watchकरोg_get_drvdata(wdt);
	u32 val;

	वापस ds1374_पढ़ो_rtc(ds1374->client, &val, DS1374_REG_WDALM0, 3);
पूर्ण

अटल पूर्णांक ds1374_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा ds1374 *ds1374 = watchकरोg_get_drvdata(wdt);
	काष्ठा i2c_client *client = ds1374->client;
	पूर्णांक cr;

	cr = i2c_smbus_पढ़ो_byte_data(client, DS1374_REG_CR);
	अगर (cr < 0)
		वापस cr;

	/* Disable watchकरोg समयr */
	cr &= ~DS1374_REG_CR_WACE;

	वापस i2c_smbus_ग_लिखो_byte_data(client, DS1374_REG_CR, cr);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops ds1374_wdt_ops = अणु
	.owner          = THIS_MODULE,
	.start          = ds1374_wdt_start,
	.stop           = ds1374_wdt_stop,
	.set_समयout    = ds1374_wdt_समय_रखोout,
पूर्ण;
#पूर्ण_अगर /*CONFIG_RTC_DRV_DS1374_WDT*/
/*
 *****************************************************************************
 *
 *	Driver Interface
 *
 *****************************************************************************
 */
अटल पूर्णांक ds1374_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ds1374 *ds1374;
	पूर्णांक ret;

	ds1374 = devm_kzalloc(&client->dev, माप(काष्ठा ds1374), GFP_KERNEL);
	अगर (!ds1374)
		वापस -ENOMEM;

	ds1374->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(ds1374->rtc))
		वापस PTR_ERR(ds1374->rtc);

	ds1374->client = client;
	i2c_set_clientdata(client, ds1374);

	INIT_WORK(&ds1374->work, ds1374_work);
	mutex_init(&ds1374->mutex);

	ret = ds1374_check_rtc_status(client);
	अगर (ret)
		वापस ret;

	अगर (client->irq > 0) अणु
		ret = devm_request_irq(&client->dev, client->irq, ds1374_irq, 0,
					"ds1374", client);
		अगर (ret) अणु
			dev_err(&client->dev, "unable to request IRQ\n");
			वापस ret;
		पूर्ण

		device_set_wakeup_capable(&client->dev, 1);
	पूर्ण

	ds1374->rtc->ops = &ds1374_rtc_ops;
	ds1374->rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(ds1374->rtc);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_RTC_DRV_DS1374_WDT
	ds1374->wdt.info = &ds1374_wdt_info;
	ds1374->wdt.ops = &ds1374_wdt_ops;
	ds1374->wdt.समयout = TIMER_MARGIN_DEFAULT;
	ds1374->wdt.min_समयout = TIMER_MARGIN_MIN;
	ds1374->wdt.max_समयout = TIMER_MARGIN_MAX;

	watchकरोg_init_समयout(&ds1374->wdt, wdt_margin, &client->dev);
	watchकरोg_set_nowayout(&ds1374->wdt, nowayout);
	watchकरोg_stop_on_reboot(&ds1374->wdt);
	watchकरोg_stop_on_unरेजिस्टर(&ds1374->wdt);
	watchकरोg_set_drvdata(&ds1374->wdt, ds1374);
	ds1374_wdt_समय_रखोout(&ds1374->wdt, ds1374->wdt.समयout);

	ret = devm_watchकरोg_रेजिस्टर_device(&client->dev, &ds1374->wdt);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक ds1374_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ds1374 *ds1374 = i2c_get_clientdata(client);

	अगर (client->irq > 0) अणु
		mutex_lock(&ds1374->mutex);
		ds1374->निकासing = 1;
		mutex_unlock(&ds1374->mutex);

		devm_मुक्त_irq(&client->dev, client->irq, client);
		cancel_work_sync(&ds1374->work);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ds1374_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (client->irq > 0 && device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1374_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (client->irq > 0 && device_may_wakeup(&client->dev))
		disable_irq_wake(client->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ds1374_pm, ds1374_suspend, ds1374_resume);

अटल काष्ठा i2c_driver ds1374_driver = अणु
	.driver = अणु
		.name = "rtc-ds1374",
		.of_match_table = of_match_ptr(ds1374_of_match),
		.pm = &ds1374_pm,
	पूर्ण,
	.probe = ds1374_probe,
	.हटाओ = ds1374_हटाओ,
	.id_table = ds1374_id,
पूर्ण;

module_i2c_driver(ds1374_driver);

MODULE_AUTHOR("Scott Wood <scottwood@freescale.com>");
MODULE_DESCRIPTION("Maxim/Dallas DS1374 RTC Driver");
MODULE_LICENSE("GPL");
