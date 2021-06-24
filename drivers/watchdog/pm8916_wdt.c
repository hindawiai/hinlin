<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

#घोषणा PON_INT_RT_STS			0x10
#घोषणा PMIC_WD_BARK_STS_BIT		BIT(6)

#घोषणा PON_PMIC_WD_RESET_S1_TIMER	0x54
#घोषणा PON_PMIC_WD_RESET_S2_TIMER	0x55

#घोषणा PON_PMIC_WD_RESET_S2_CTL	0x56
#घोषणा RESET_TYPE_WARM			0x01
#घोषणा RESET_TYPE_SHUTDOWN		0x04
#घोषणा RESET_TYPE_HARD			0x07

#घोषणा PON_PMIC_WD_RESET_S2_CTL2	0x57
#घोषणा S2_RESET_EN_BIT			BIT(7)

#घोषणा PON_PMIC_WD_RESET_PET		0x58
#घोषणा WATCHDOG_PET_BIT		BIT(0)

#घोषणा PM8916_WDT_DEFAULT_TIMEOUT	32
#घोषणा PM8916_WDT_MIN_TIMEOUT		1
#घोषणा PM8916_WDT_MAX_TIMEOUT		127

काष्ठा pm8916_wdt अणु
	काष्ठा regmap *regmap;
	काष्ठा watchकरोg_device wdev;
	u32 baseaddr;
पूर्ण;

अटल पूर्णांक pm8916_wdt_start(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा pm8916_wdt *wdt = watchकरोg_get_drvdata(wdev);

	वापस regmap_update_bits(wdt->regmap,
				  wdt->baseaddr + PON_PMIC_WD_RESET_S2_CTL2,
				  S2_RESET_EN_BIT, S2_RESET_EN_BIT);
पूर्ण

अटल पूर्णांक pm8916_wdt_stop(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा pm8916_wdt *wdt = watchकरोg_get_drvdata(wdev);

	वापस regmap_update_bits(wdt->regmap,
				  wdt->baseaddr + PON_PMIC_WD_RESET_S2_CTL2,
				  S2_RESET_EN_BIT, 0);
पूर्ण

अटल पूर्णांक pm8916_wdt_ping(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा pm8916_wdt *wdt = watchकरोg_get_drvdata(wdev);

	वापस regmap_update_bits(wdt->regmap,
				  wdt->baseaddr + PON_PMIC_WD_RESET_PET,
				  WATCHDOG_PET_BIT, WATCHDOG_PET_BIT);
पूर्ण

अटल पूर्णांक pm8916_wdt_configure_समयrs(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा pm8916_wdt *wdt = watchकरोg_get_drvdata(wdev);
	पूर्णांक err;

	err = regmap_ग_लिखो(wdt->regmap,
			   wdt->baseaddr + PON_PMIC_WD_RESET_S1_TIMER,
			   wdev->समयout - wdev->preसमयout);
	अगर (err)
		वापस err;

	वापस regmap_ग_लिखो(wdt->regmap,
			    wdt->baseaddr + PON_PMIC_WD_RESET_S2_TIMER,
			    wdev->preसमयout);
पूर्ण

अटल पूर्णांक pm8916_wdt_set_समयout(काष्ठा watchकरोg_device *wdev,
				  अचिन्हित पूर्णांक समयout)
अणु
	wdev->समयout = समयout;

	वापस pm8916_wdt_configure_समयrs(wdev);
पूर्ण

अटल पूर्णांक pm8916_wdt_set_preसमयout(काष्ठा watchकरोg_device *wdev,
				     अचिन्हित पूर्णांक preसमयout)
अणु
	wdev->preसमयout = preसमयout;

	वापस pm8916_wdt_configure_समयrs(wdev);
पूर्ण

अटल irqवापस_t pm8916_wdt_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा pm8916_wdt *wdt = arg;
	पूर्णांक err, sts;

	err = regmap_पढ़ो(wdt->regmap, wdt->baseaddr + PON_INT_RT_STS, &sts);
	अगर (err)
		वापस IRQ_HANDLED;

	अगर (sts & PMIC_WD_BARK_STS_BIT)
		watchकरोg_notअगरy_preसमयout(&wdt->wdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info pm8916_wdt_ident = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "QCOM PM8916 PON WDT",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info pm8916_wdt_pt_ident = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE |
		   WDIOF_PRETIMEOUT,
	.identity = "QCOM PM8916 PON WDT",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops pm8916_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = pm8916_wdt_start,
	.stop = pm8916_wdt_stop,
	.ping = pm8916_wdt_ping,
	.set_समयout = pm8916_wdt_set_समयout,
	.set_preसमयout = pm8916_wdt_set_preसमयout,
पूर्ण;

अटल पूर्णांक pm8916_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pm8916_wdt *wdt;
	काष्ठा device *parent;
	पूर्णांक err, irq;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	parent = dev->parent;

	/*
	 * The pm8916-pon-wdt is a child of the pon device, which is a child
	 * of the pm8916 mfd device. We want access to the pm8916 रेजिस्टरs.
	 * Retrieve regmap from pm8916 (parent->parent) and base address
	 * from pm8916-pon (pon).
	 */
	wdt->regmap = dev_get_regmap(parent->parent, शून्य);
	अगर (!wdt->regmap) अणु
		dev_err(dev, "failed to locate regmap\n");
		वापस -ENODEV;
	पूर्ण

	err = device_property_पढ़ो_u32(parent, "reg", &wdt->baseaddr);
	अगर (err) अणु
		dev_err(dev, "failed to get pm8916-pon address\n");
		वापस err;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq > 0) अणु
		err = devm_request_irq(dev, irq, pm8916_wdt_isr, 0,
				       "pm8916_wdt", wdt);
		अगर (err)
			वापस err;

		wdt->wdev.info = &pm8916_wdt_pt_ident;
	पूर्ण अन्यथा अणु
		अगर (irq == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		wdt->wdev.info = &pm8916_wdt_ident;
	पूर्ण

	/* Configure watchकरोg to hard-reset mode */
	err = regmap_ग_लिखो(wdt->regmap,
			   wdt->baseaddr + PON_PMIC_WD_RESET_S2_CTL,
			   RESET_TYPE_HARD);
	अगर (err) अणु
		dev_err(dev, "failed configure watchdog\n");
		वापस err;
	पूर्ण

	wdt->wdev.ops = &pm8916_wdt_ops,
	wdt->wdev.parent = dev;
	wdt->wdev.min_समयout = PM8916_WDT_MIN_TIMEOUT;
	wdt->wdev.max_समयout = PM8916_WDT_MAX_TIMEOUT;
	wdt->wdev.समयout = PM8916_WDT_DEFAULT_TIMEOUT;
	wdt->wdev.preसमयout = 0;
	watchकरोg_set_drvdata(&wdt->wdev, wdt);
	platक्रमm_set_drvdata(pdev, wdt);

	watchकरोg_init_समयout(&wdt->wdev, 0, dev);
	pm8916_wdt_configure_समयrs(&wdt->wdev);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdev);
पूर्ण

अटल पूर्णांक __maybe_unused pm8916_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा pm8916_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdev))
		वापस pm8916_wdt_stop(&wdt->wdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm8916_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा pm8916_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdev))
		वापस pm8916_wdt_start(&wdt->wdev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pm8916_wdt_pm_ops, pm8916_wdt_suspend,
			 pm8916_wdt_resume);

अटल स्थिर काष्ठा of_device_id pm8916_wdt_id_table[] = अणु
	अणु .compatible = "qcom,pm8916-wdt" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8916_wdt_id_table);

अटल काष्ठा platक्रमm_driver pm8916_wdt_driver = अणु
	.probe = pm8916_wdt_probe,
	.driver = अणु
		.name = "pm8916-wdt",
		.of_match_table = of_match_ptr(pm8916_wdt_id_table),
		.pm = &pm8916_wdt_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pm8916_wdt_driver);

MODULE_AUTHOR("Loic Poulain <loic.poulain@linaro.org>");
MODULE_DESCRIPTION("Qualcomm pm8916 watchdog driver");
MODULE_LICENSE("GPL v2");
