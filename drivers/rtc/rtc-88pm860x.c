<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Real Time Clock driver क्रम Marvell 88PM860x PMIC
 *
 * Copyright (c) 2010 Marvell International Ltd.
 * Author:	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/88pm860x.h>

#घोषणा VRTC_CALIBRATION

काष्ठा pm860x_rtc_info अणु
	काष्ठा pm860x_chip	*chip;
	काष्ठा i2c_client	*i2c;
	काष्ठा rtc_device	*rtc_dev;
	काष्ठा device		*dev;
	काष्ठा delayed_work	calib_work;

	पूर्णांक			irq;
	पूर्णांक			vrtc;
पूर्ण;

#घोषणा REG_VRTC_MEAS1		0x7D

#घोषणा REG0_ADDR		0xB0
#घोषणा REG1_ADDR		0xB2
#घोषणा REG2_ADDR		0xB4
#घोषणा REG3_ADDR		0xB6

#घोषणा REG0_DATA		0xB1
#घोषणा REG1_DATA		0xB3
#घोषणा REG2_DATA		0xB5
#घोषणा REG3_DATA		0xB7

/* bit definitions of Measurement Enable Register 2 (0x51) */
#घोषणा MEAS2_VRTC		(1 << 0)

/* bit definitions of RTC Register 1 (0xA0) */
#घोषणा ALARM_EN		(1 << 3)
#घोषणा ALARM_WAKEUP		(1 << 4)
#घोषणा ALARM			(1 << 5)
#घोषणा RTC1_USE_XO		(1 << 7)

#घोषणा VRTC_CALIB_INTERVAL	(HZ * 60 * 10)		/* 10 minutes */

अटल irqवापस_t rtc_update_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_rtc_info *info = (काष्ठा pm860x_rtc_info *)data;
	पूर्णांक mask;

	mask = ALARM | ALARM_WAKEUP;
	pm860x_set_bits(info->i2c, PM8607_RTC1, mask | ALARM_EN, mask);
	rtc_update_irq(info->rtc_dev, 1, RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm860x_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pm860x_rtc_info *info = dev_get_drvdata(dev);

	अगर (enabled)
		pm860x_set_bits(info->i2c, PM8607_RTC1, ALARM_EN, ALARM_EN);
	अन्यथा
		pm860x_set_bits(info->i2c, PM8607_RTC1, ALARM_EN, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pm860x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[8];
	अचिन्हित दीर्घ ticks, base, data;

	pm860x_page_bulk_पढ़ो(info->i2c, REG0_ADDR, 8, buf);
	dev_dbg(info->dev, "%x-%x-%x-%x-%x-%x-%x-%x\n", buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	base = ((अचिन्हित दीर्घ)buf[1] << 24) | (buf[3] << 16) |
		(buf[5] << 8) | buf[7];

	/* load 32-bit पढ़ो-only counter */
	pm860x_bulk_पढ़ो(info->i2c, PM8607_RTC_COUNTER1, 4, buf);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	rtc_समय64_to_पंचांग(ticks, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pm860x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[4];
	अचिन्हित दीर्घ ticks, base, data;

	ticks = rtc_पंचांग_to_समय64(पंचांग);

	/* load 32-bit पढ़ो-only counter */
	pm860x_bulk_पढ़ो(info->i2c, PM8607_RTC_COUNTER1, 4, buf);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	base = ticks - data;
	dev_dbg(info->dev, "set base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	pm860x_page_reg_ग_लिखो(info->i2c, REG0_DATA, (base >> 24) & 0xFF);
	pm860x_page_reg_ग_लिखो(info->i2c, REG1_DATA, (base >> 16) & 0xFF);
	pm860x_page_reg_ग_लिखो(info->i2c, REG2_DATA, (base >> 8) & 0xFF);
	pm860x_page_reg_ग_लिखो(info->i2c, REG3_DATA, base & 0xFF);

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pm860x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[8];
	अचिन्हित दीर्घ ticks, base, data;
	पूर्णांक ret;

	pm860x_page_bulk_पढ़ो(info->i2c, REG0_ADDR, 8, buf);
	dev_dbg(info->dev, "%x-%x-%x-%x-%x-%x-%x-%x\n", buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	base = ((अचिन्हित दीर्घ)buf[1] << 24) | (buf[3] << 16) |
		(buf[5] << 8) | buf[7];

	pm860x_bulk_पढ़ो(info->i2c, PM8607_RTC_EXPIRE1, 4, buf);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	rtc_समय64_to_पंचांग(ticks, &alrm->समय);
	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_RTC1);
	alrm->enabled = (ret & ALARM_EN) ? 1 : 0;
	alrm->pending = (ret & (ALARM | ALARM_WAKEUP)) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pm860x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ticks, base, data;
	अचिन्हित अक्षर buf[8];
	पूर्णांक mask;

	pm860x_set_bits(info->i2c, PM8607_RTC1, ALARM_EN, 0);

	pm860x_page_bulk_पढ़ो(info->i2c, REG0_ADDR, 8, buf);
	dev_dbg(info->dev, "%x-%x-%x-%x-%x-%x-%x-%x\n", buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	base = ((अचिन्हित दीर्घ)buf[1] << 24) | (buf[3] << 16) |
		(buf[5] << 8) | buf[7];

	ticks = rtc_पंचांग_to_समय64(&alrm->समय);
	data = ticks - base;

	buf[0] = data & 0xff;
	buf[1] = (data >> 8) & 0xff;
	buf[2] = (data >> 16) & 0xff;
	buf[3] = (data >> 24) & 0xff;
	pm860x_bulk_ग_लिखो(info->i2c, PM8607_RTC_EXPIRE1, 4, buf);
	अगर (alrm->enabled) अणु
		mask = ALARM | ALARM_WAKEUP | ALARM_EN;
		pm860x_set_bits(info->i2c, PM8607_RTC1, mask, mask);
	पूर्ण अन्यथा अणु
		mask = ALARM | ALARM_WAKEUP | ALARM_EN;
		pm860x_set_bits(info->i2c, PM8607_RTC1, mask,
				ALARM | ALARM_WAKEUP);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pm860x_rtc_ops = अणु
	.पढ़ो_समय	= pm860x_rtc_पढ़ो_समय,
	.set_समय	= pm860x_rtc_set_समय,
	.पढ़ो_alarm	= pm860x_rtc_पढ़ो_alarm,
	.set_alarm	= pm860x_rtc_set_alarm,
	.alarm_irq_enable = pm860x_rtc_alarm_irq_enable,
पूर्ण;

#अगर_घोषित VRTC_CALIBRATION
अटल व्योम calibrate_vrtc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pm860x_rtc_info *info = container_of(work,
		काष्ठा pm860x_rtc_info, calib_work.work);
	अचिन्हित अक्षर buf[2];
	अचिन्हित पूर्णांक sum, data, mean, vrtc_set;
	पूर्णांक i;

	क्रम (i = 0, sum = 0; i < 16; i++) अणु
		msleep(100);
		pm860x_bulk_पढ़ो(info->i2c, REG_VRTC_MEAS1, 2, buf);
		data = (buf[0] << 4) | buf[1];
		data = (data * 5400) >> 12;	/* convert to mv */
		sum += data;
	पूर्ण
	mean = sum >> 4;
	vrtc_set = 2700 + (info->vrtc & 0x3) * 200;
	dev_dbg(info->dev, "mean:%d, vrtc_set:%d\n", mean, vrtc_set);

	sum = pm860x_reg_पढ़ो(info->i2c, PM8607_RTC_MISC1);
	data = sum & 0x3;
	अगर ((mean + 200) < vrtc_set) अणु
		/* try higher voltage */
		अगर (++data == 4)
			जाओ out;
		data = (sum & 0xf8) | (data & 0x3);
		pm860x_reg_ग_लिखो(info->i2c, PM8607_RTC_MISC1, data);
	पूर्ण अन्यथा अगर ((mean - 200) > vrtc_set) अणु
		/* try lower voltage */
		अगर (data-- == 0)
			जाओ out;
		data = (sum & 0xf8) | (data & 0x3);
		pm860x_reg_ग_लिखो(info->i2c, PM8607_RTC_MISC1, data);
	पूर्ण अन्यथा
		जाओ out;
	dev_dbg(info->dev, "set 0x%x to RTC_MISC1\n", data);
	/* trigger next calibration since VRTC is updated */
	schedule_delayed_work(&info->calib_work, VRTC_CALIB_INTERVAL);
	वापस;
out:
	/* disable measurement */
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VRTC, 0);
	dev_dbg(info->dev, "finish VRTC calibration\n");
	वापस;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल पूर्णांक pm860x_rtc_dt_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा pm860x_rtc_info *info)
अणु
	काष्ठा device_node *np = pdev->dev.parent->of_node;
	पूर्णांक ret;
	अगर (!np)
		वापस -ENODEV;
	np = of_get_child_by_name(np, "rtc");
	अगर (!np) अणु
		dev_err(&pdev->dev, "failed to find rtc node\n");
		वापस -ENODEV;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "marvell,88pm860x-vrtc", &info->vrtc);
	अगर (ret)
		info->vrtc = 0;
	of_node_put(np);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा pm860x_rtc_dt_init(x, y)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक pm860x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_rtc_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा pm860x_rtc_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->irq = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq < 0)
		वापस info->irq;

	info->chip = chip;
	info->i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, info);

	info->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(info->rtc_dev))
		वापस PTR_ERR(info->rtc_dev);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
					rtc_update_handler, IRQF_ONESHOT, "rtc",
					info);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		वापस ret;
	पूर्ण

	/* set addresses of 32-bit base value क्रम RTC समय */
	pm860x_page_reg_ग_लिखो(info->i2c, REG0_ADDR, REG0_DATA);
	pm860x_page_reg_ग_लिखो(info->i2c, REG1_ADDR, REG1_DATA);
	pm860x_page_reg_ग_लिखो(info->i2c, REG2_ADDR, REG2_DATA);
	pm860x_page_reg_ग_लिखो(info->i2c, REG3_ADDR, REG3_DATA);

	pm860x_rtc_dt_init(pdev, info);

	info->rtc_dev->ops = &pm860x_rtc_ops;
	info->rtc_dev->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(info->rtc_dev);
	अगर (ret)
		वापस ret;

	/*
	 * enable पूर्णांकernal XO instead of पूर्णांकernal 3.25MHz घड़ी since it can
	 * मुक्त running in PMIC घातer-करोwn state.
	 */
	pm860x_set_bits(info->i2c, PM8607_RTC1, RTC1_USE_XO, RTC1_USE_XO);

#अगर_घोषित VRTC_CALIBRATION
	/* <00> -- 2.7V, <01> -- 2.9V, <10> -- 3.1V, <11> -- 3.3V */
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VRTC, MEAS2_VRTC);

	/* calibrate VRTC */
	INIT_DELAYED_WORK(&info->calib_work, calibrate_vrtc_work);
	schedule_delayed_work(&info->calib_work, VRTC_CALIB_INTERVAL);
#पूर्ण_अगर	/* VRTC_CALIBRATION */

	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_rtc_info *info = platक्रमm_get_drvdata(pdev);

#अगर_घोषित VRTC_CALIBRATION
	cancel_delayed_work_sync(&info->calib_work);
	/* disable measurement */
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VRTC, 0);
#पूर्ण_अगर	/* VRTC_CALIBRATION */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pm860x_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag |= 1 << PM8607_IRQ_RTC;
	वापस 0;
पूर्ण
अटल पूर्णांक pm860x_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag &= ~(1 << PM8607_IRQ_RTC);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pm860x_rtc_pm_ops, pm860x_rtc_suspend, pm860x_rtc_resume);

अटल काष्ठा platक्रमm_driver pm860x_rtc_driver = अणु
	.driver		= अणु
		.name	= "88pm860x-rtc",
		.pm	= &pm860x_rtc_pm_ops,
	पूर्ण,
	.probe		= pm860x_rtc_probe,
	.हटाओ		= pm860x_rtc_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm860x_rtc_driver);

MODULE_DESCRIPTION("Marvell 88PM860x RTC driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
