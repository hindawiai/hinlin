<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power off through MediaTek PMIC
 *
 * Copyright (C) 2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/mfd/mt6397/rtc.h>

काष्ठा mt6323_pwrc अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	u32 base;
पूर्ण;

अटल काष्ठा mt6323_pwrc *mt_pwrc;

अटल व्योम mt6323_करो_pwroff(व्योम)
अणु
	काष्ठा mt6323_pwrc *pwrc = mt_pwrc;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	regmap_ग_लिखो(pwrc->regmap, pwrc->base + RTC_BBPU, RTC_BBPU_KEY);
	regmap_ग_लिखो(pwrc->regmap, pwrc->base + RTC_WRTGR_MT6323, 1);

	ret = regmap_पढ़ो_poll_समयout(pwrc->regmap,
					pwrc->base + RTC_BBPU, val,
					!(val & RTC_BBPU_CBUSY),
					MTK_RTC_POLL_DELAY_US,
					MTK_RTC_POLL_TIMEOUT);
	अगर (ret)
		dev_err(pwrc->dev, "failed to write BBPU: %d\n", ret);

	/* Wait some समय until प्रणाली करोwn, otherwise, notice with a warn */
	mdelay(1000);

	WARN_ONCE(1, "Unable to power off system\n");
पूर्ण

अटल पूर्णांक mt6323_pwrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6397_chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा mt6323_pwrc *pwrc;
	काष्ठा resource *res;

	pwrc = devm_kzalloc(&pdev->dev, माप(*pwrc), GFP_KERNEL);
	अगर (!pwrc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pwrc->base = res->start;
	pwrc->regmap = mt6397_chip->regmap;
	pwrc->dev = &pdev->dev;
	mt_pwrc = pwrc;

	pm_घातer_off = &mt6323_करो_pwroff;

	वापस 0;
पूर्ण

अटल पूर्णांक mt6323_pwrc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == &mt6323_करो_pwroff)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt6323_pwrc_dt_match[] = अणु
	अणु .compatible = "mediatek,mt6323-pwrc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6323_pwrc_dt_match);

अटल काष्ठा platक्रमm_driver mt6323_pwrc_driver = अणु
	.probe          = mt6323_pwrc_probe,
	.हटाओ         = mt6323_pwrc_हटाओ,
	.driver         = अणु
		.name   = "mt6323-pwrc",
		.of_match_table = mt6323_pwrc_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mt6323_pwrc_driver);

MODULE_DESCRIPTION("Poweroff driver for MT6323 PMIC");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("GPL v2");
