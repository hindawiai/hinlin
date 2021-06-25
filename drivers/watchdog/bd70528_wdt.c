<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 ROHM Semiconductors
// ROHM BD70528MWV watchकरोg driver

#समावेश <linux/bcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rohm-bd70528.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

/*
 * Max समय we can set is 1 hour, 59 minutes and 59 seconds
 * and Minimum समय is 1 second
 */
#घोषणा WDT_MAX_MS	((2 * 60 * 60 - 1) * 1000)
#घोषणा WDT_MIN_MS	1000
#घोषणा DEFAULT_TIMEOUT	60

#घोषणा WD_CTRL_MAGIC1 0x55
#घोषणा WD_CTRL_MAGIC2 0xAA

काष्ठा wdtbd70528 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा rohm_regmap_dev *mfd;
	काष्ठा watchकरोg_device wdt;
पूर्ण;

/**
 * bd70528_wdt_set - arm or disarm watchकरोg समयr
 *
 * @data:	device data क्रम the PMIC instance we want to operate on
 * @enable:	new state of WDT. zero to disable, non zero to enable
 * @old_state:	previous state of WDT will be filled here
 *
 * Arm or disarm WDT on BD70528 PMIC. Expected to be called only by
 * BD70528 RTC and BD70528 WDT drivers. The rtc_समयr_lock must be taken
 * by calling bd70528_wdt_lock beक्रमe calling bd70528_wdt_set.
 */
पूर्णांक bd70528_wdt_set(काष्ठा rohm_regmap_dev *data, पूर्णांक enable, पूर्णांक *old_state)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा bd70528_data *bd70528 = container_of(data, काष्ठा bd70528_data,
						 chip);
	u8 wd_ctrl_arr[3] = अणु WD_CTRL_MAGIC1, WD_CTRL_MAGIC2, 0 पूर्ण;
	u8 *wd_ctrl = &wd_ctrl_arr[2];

	ret = regmap_पढ़ो(bd70528->chip.regmap, BD70528_REG_WDT_CTRL, &पंचांगp);
	अगर (ret)
		वापस ret;

	*wd_ctrl = (u8)पंचांगp;

	अगर (old_state) अणु
		अगर (*wd_ctrl & BD70528_MASK_WDT_EN)
			*old_state |= BD70528_WDT_STATE_BIT;
		अन्यथा
			*old_state &= ~BD70528_WDT_STATE_BIT;
		अगर ((!enable) == (!(*old_state & BD70528_WDT_STATE_BIT)))
			वापस 0;
	पूर्ण

	अगर (enable) अणु
		अगर (*wd_ctrl & BD70528_MASK_WDT_EN)
			वापस 0;
		*wd_ctrl |= BD70528_MASK_WDT_EN;
	पूर्ण अन्यथा अणु
		अगर (*wd_ctrl & BD70528_MASK_WDT_EN)
			*wd_ctrl &= ~BD70528_MASK_WDT_EN;
		अन्यथा
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_ग_लिखो(bd70528->chip.regmap, BD70528_REG_WDT_CTRL,
				   wd_ctrl_arr[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(bd70528->chip.regmap, BD70528_REG_WDT_CTRL, &पंचांगp);
	अगर ((पंचांगp & BD70528_MASK_WDT_EN) != (*wd_ctrl & BD70528_MASK_WDT_EN)) अणु
		dev_err(bd70528->chip.dev,
			"Watchdog ctrl mismatch (hw) 0x%x (set) 0x%x\n",
			पंचांगp, *wd_ctrl);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(bd70528_wdt_set);

/**
 * bd70528_wdt_lock - take WDT lock
 *
 * @data:	device data क्रम the PMIC instance we want to operate on
 *
 * Lock WDT क्रम arming/disarming in order to aव्योम race condition caused
 * by WDT state changes initiated by WDT and RTC drivers.
 */
व्योम bd70528_wdt_lock(काष्ठा rohm_regmap_dev *data)
अणु
	काष्ठा bd70528_data *bd70528 = container_of(data, काष्ठा bd70528_data,
						 chip);

	mutex_lock(&bd70528->rtc_समयr_lock);
पूर्ण
EXPORT_SYMBOL(bd70528_wdt_lock);

/**
 * bd70528_wdt_unlock - unlock WDT lock
 *
 * @data:	device data क्रम the PMIC instance we want to operate on
 *
 * Unlock WDT lock which has previously been taken by call to
 * bd70528_wdt_lock.
 */
व्योम bd70528_wdt_unlock(काष्ठा rohm_regmap_dev *data)
अणु
	काष्ठा bd70528_data *bd70528 = container_of(data, काष्ठा bd70528_data,
						 chip);

	mutex_unlock(&bd70528->rtc_समयr_lock);
पूर्ण
EXPORT_SYMBOL(bd70528_wdt_unlock);

अटल पूर्णांक bd70528_wdt_set_locked(काष्ठा wdtbd70528 *w, पूर्णांक enable)
अणु
	वापस bd70528_wdt_set(w->mfd, enable, शून्य);
पूर्ण

अटल पूर्णांक bd70528_wdt_change(काष्ठा wdtbd70528 *w, पूर्णांक enable)
अणु
	पूर्णांक ret;

	bd70528_wdt_lock(w->mfd);
	ret = bd70528_wdt_set_locked(w, enable);
	bd70528_wdt_unlock(w->mfd);

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा wdtbd70528 *w = watchकरोg_get_drvdata(wdt);

	dev_dbg(w->dev, "WDT ping...\n");
	वापस bd70528_wdt_change(w, 1);
पूर्ण

अटल पूर्णांक bd70528_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा wdtbd70528 *w = watchकरोg_get_drvdata(wdt);

	dev_dbg(w->dev, "WDT stopping...\n");
	वापस bd70528_wdt_change(w, 0);
पूर्ण

अटल पूर्णांक bd70528_wdt_set_समयout(काष्ठा watchकरोg_device *wdt,
				   अचिन्हित पूर्णांक समयout)
अणु
	अचिन्हित पूर्णांक hours;
	अचिन्हित पूर्णांक minutes;
	अचिन्हित पूर्णांक seconds;
	पूर्णांक ret;
	काष्ठा wdtbd70528 *w = watchकरोg_get_drvdata(wdt);

	seconds = समयout;
	hours = समयout / (60 * 60);
	/* Maximum समयout is 1h 59m 59s => hours is 1 or 0 */
	अगर (hours)
		seconds -= (60 * 60);
	minutes = seconds / 60;
	seconds = seconds % 60;

	bd70528_wdt_lock(w->mfd);

	ret = bd70528_wdt_set_locked(w, 0);
	अगर (ret)
		जाओ out_unlock;

	ret = regmap_update_bits(w->regmap, BD70528_REG_WDT_HOUR,
				 BD70528_MASK_WDT_HOUR, hours);
	अगर (ret) अणु
		dev_err(w->dev, "Failed to set WDT hours\n");
		जाओ out_en_unlock;
	पूर्ण
	ret = regmap_update_bits(w->regmap, BD70528_REG_WDT_MINUTE,
				 BD70528_MASK_WDT_MINUTE, bin2bcd(minutes));
	अगर (ret) अणु
		dev_err(w->dev, "Failed to set WDT minutes\n");
		जाओ out_en_unlock;
	पूर्ण
	ret = regmap_update_bits(w->regmap, BD70528_REG_WDT_SEC,
				 BD70528_MASK_WDT_SEC, bin2bcd(seconds));
	अगर (ret)
		dev_err(w->dev, "Failed to set WDT seconds\n");
	अन्यथा
		dev_dbg(w->dev, "WDT tmo set to %u\n", समयout);

out_en_unlock:
	ret = bd70528_wdt_set_locked(w, 1);
out_unlock:
	bd70528_wdt_unlock(w->mfd);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info bd70528_wdt_info = अणु
	.identity = "bd70528-wdt",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops bd70528_wdt_ops = अणु
	.start		= bd70528_wdt_start,
	.stop		= bd70528_wdt_stop,
	.set_समयout	= bd70528_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक bd70528_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rohm_regmap_dev *bd70528;
	काष्ठा wdtbd70528 *w;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	bd70528 = dev_get_drvdata(pdev->dev.parent);
	अगर (!bd70528) अणु
		dev_err(&pdev->dev, "No MFD driver data\n");
		वापस -EINVAL;
	पूर्ण
	w = devm_kzalloc(&pdev->dev, माप(*w), GFP_KERNEL);
	अगर (!w)
		वापस -ENOMEM;

	w->regmap = bd70528->regmap;
	w->mfd = bd70528;
	w->dev = &pdev->dev;

	w->wdt.info = &bd70528_wdt_info;
	w->wdt.ops =  &bd70528_wdt_ops;
	w->wdt.min_hw_heartbeat_ms = WDT_MIN_MS;
	w->wdt.max_hw_heartbeat_ms = WDT_MAX_MS;
	w->wdt.parent = pdev->dev.parent;
	w->wdt.समयout = DEFAULT_TIMEOUT;
	watchकरोg_set_drvdata(&w->wdt, w);
	watchकरोg_init_समयout(&w->wdt, 0, pdev->dev.parent);

	ret = bd70528_wdt_set_समयout(&w->wdt, w->wdt.समयout);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set the watchdog timeout\n");
		वापस ret;
	पूर्ण

	bd70528_wdt_lock(w->mfd);
	ret = regmap_पढ़ो(w->regmap, BD70528_REG_WDT_CTRL, &reg);
	bd70528_wdt_unlock(w->mfd);

	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get the watchdog state\n");
		वापस ret;
	पूर्ण
	अगर (reg & BD70528_MASK_WDT_EN) अणु
		dev_dbg(&pdev->dev, "watchdog was running during probe\n");
		set_bit(WDOG_HW_RUNNING, &w->wdt.status);
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(&pdev->dev, &w->wdt);
	अगर (ret < 0)
		dev_err(&pdev->dev, "watchdog registration failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver bd70528_wdt = अणु
	.driver = अणु
		.name = "bd70528-wdt"
	पूर्ण,
	.probe = bd70528_wdt_probe,
पूर्ण;

module_platक्रमm_driver(bd70528_wdt);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD70528 watchdog driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd70528-wdt");
