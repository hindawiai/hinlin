<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/समय64.h>

काष्ठा meson_vrtc_data अणु
	व्योम __iomem *io_alarm;
	काष्ठा rtc_device *rtc;
	अचिन्हित दीर्घ alarm_समय;
	bool enabled;
पूर्ण;

अटल पूर्णांक meson_vrtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा बारpec64 समय;

	dev_dbg(dev, "%s\n", __func__);
	kसमय_get_raw_ts64(&समय);
	rtc_समय64_to_पंचांग(समय.tv_sec, पंचांग);

	वापस 0;
पूर्ण

अटल व्योम meson_vrtc_set_wakeup_समय(काष्ठा meson_vrtc_data *vrtc,
				       अचिन्हित दीर्घ समय)
अणु
	ग_लिखोl_relaxed(समय, vrtc->io_alarm);
पूर्ण

अटल पूर्णांक meson_vrtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा meson_vrtc_data *vrtc = dev_get_drvdata(dev);

	dev_dbg(dev, "%s: alarm->enabled=%d\n", __func__, alarm->enabled);
	अगर (alarm->enabled)
		vrtc->alarm_समय = rtc_पंचांग_to_समय64(&alarm->समय);
	अन्यथा
		vrtc->alarm_समय = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_vrtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा meson_vrtc_data *vrtc = dev_get_drvdata(dev);

	vrtc->enabled = enabled;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops meson_vrtc_ops = अणु
	.पढ़ो_समय = meson_vrtc_पढ़ो_समय,
	.set_alarm = meson_vrtc_set_alarm,
	.alarm_irq_enable = meson_vrtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक meson_vrtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_vrtc_data *vrtc;

	vrtc = devm_kzalloc(&pdev->dev, माप(*vrtc), GFP_KERNEL);
	अगर (!vrtc)
		वापस -ENOMEM;

	vrtc->io_alarm = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vrtc->io_alarm))
		वापस PTR_ERR(vrtc->io_alarm);

	device_init_wakeup(&pdev->dev, 1);

	platक्रमm_set_drvdata(pdev, vrtc);

	vrtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(vrtc->rtc))
		वापस PTR_ERR(vrtc->rtc);

	vrtc->rtc->ops = &meson_vrtc_ops;
	वापस devm_rtc_रेजिस्टर_device(vrtc->rtc);
पूर्ण

अटल पूर्णांक __maybe_unused meson_vrtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा meson_vrtc_data *vrtc = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	अगर (vrtc->alarm_समय) अणु
		अचिन्हित दीर्घ local_समय;
		दीर्घ alarm_secs;
		काष्ठा बारpec64 समय;

		kसमय_get_raw_ts64(&समय);
		local_समय = समय.tv_sec;

		dev_dbg(dev, "alarm_time = %lus, local_time=%lus\n",
			vrtc->alarm_समय, local_समय);
		alarm_secs = vrtc->alarm_समय - local_समय;
		अगर (alarm_secs > 0) अणु
			meson_vrtc_set_wakeup_समय(vrtc, alarm_secs);
			dev_dbg(dev, "system will wakeup in %lds.\n",
				alarm_secs);
		पूर्ण अन्यथा अणु
			dev_err(dev, "alarm time already passed: %lds.\n",
				alarm_secs);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused meson_vrtc_resume(काष्ठा device *dev)
अणु
	काष्ठा meson_vrtc_data *vrtc = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	vrtc->alarm_समय = 0;
	meson_vrtc_set_wakeup_समय(vrtc, 0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(meson_vrtc_pm_ops,
			 meson_vrtc_suspend, meson_vrtc_resume);

अटल स्थिर काष्ठा of_device_id meson_vrtc_dt_match[] = अणु
	अणु .compatible = "amlogic,meson-vrtc"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_vrtc_dt_match);

अटल काष्ठा platक्रमm_driver meson_vrtc_driver = अणु
	.probe = meson_vrtc_probe,
	.driver = अणु
		.name = "meson-vrtc",
		.of_match_table = meson_vrtc_dt_match,
		.pm = &meson_vrtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_vrtc_driver);

MODULE_DESCRIPTION("Amlogic Virtual Wakeup RTC Timer driver");
MODULE_LICENSE("GPL");
