<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Copyright (C) 2018 ROHM Semiconductors
//
// RTC driver क्रम ROHM BD70528 PMIC

#समावेश <linux/bcd.h>
#समावेश <linux/mfd/rohm-bd70528.h>
#समावेश <linux/mfd/rohm-bd71815.h>
#समावेश <linux/mfd/rohm-bd71828.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

/*
 * On BD71828 and BD71815 the ALM0 MASK is 14 bytes after the ALM0
 * block start
 */
#घोषणा BD718XX_ALM_EN_OFFSET 14

/*
 * We पढ़ो regs RTC_SEC => RTC_YEAR
 * this काष्ठा is ordered according to chip रेजिस्टरs.
 * Keep it u8 only (or packed) to aव्योम padding issues.
 */
काष्ठा bd70528_rtc_day अणु
	u8 sec;
	u8 min;
	u8 hour;
पूर्ण __packed;

काष्ठा bd70528_rtc_data अणु
	काष्ठा bd70528_rtc_day समय;
	u8 week;
	u8 day;
	u8 month;
	u8 year;
पूर्ण __packed;

काष्ठा bd70528_rtc_wake अणु
	काष्ठा bd70528_rtc_day समय;
	u8 ctrl;
पूर्ण __packed;

काष्ठा bd71828_rtc_alm अणु
	काष्ठा bd70528_rtc_data alm0;
	काष्ठा bd70528_rtc_data alm1;
	u8 alm_mask;
	u8 alm1_mask;
पूर्ण __packed;

काष्ठा bd70528_rtc_alm अणु
	काष्ठा bd70528_rtc_data data;
	u8 alm_mask;
	u8 alm_repeat;
पूर्ण __packed;

काष्ठा bd70528_rtc अणु
	काष्ठा rohm_regmap_dev *parent;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	u8 reg_समय_start;
	u8 bd718xx_alm_block_start;
	bool has_rtc_समयrs;
पूर्ण;

अटल पूर्णांक bd70528_set_wake(काष्ठा rohm_regmap_dev *bd70528,
			    पूर्णांक enable, पूर्णांक *old_state)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ctrl_reg;

	ret = regmap_पढ़ो(bd70528->regmap, BD70528_REG_WAKE_EN, &ctrl_reg);
	अगर (ret)
		वापस ret;

	अगर (old_state) अणु
		अगर (ctrl_reg & BD70528_MASK_WAKE_EN)
			*old_state |= BD70528_WAKE_STATE_BIT;
		अन्यथा
			*old_state &= ~BD70528_WAKE_STATE_BIT;

		अगर (!enable == !(*old_state & BD70528_WAKE_STATE_BIT))
			वापस 0;
	पूर्ण

	अगर (enable)
		ctrl_reg |= BD70528_MASK_WAKE_EN;
	अन्यथा
		ctrl_reg &= ~BD70528_MASK_WAKE_EN;

	वापस regmap_ग_लिखो(bd70528->regmap, BD70528_REG_WAKE_EN,
			    ctrl_reg);
पूर्ण

अटल पूर्णांक bd70528_set_elapsed_पंचांगr(काष्ठा rohm_regmap_dev *bd70528,
				   पूर्णांक enable, पूर्णांक *old_state)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ctrl_reg;

	/*
	 * TBD
	 * What is the purpose of elapsed समयr ?
	 * Is the समयout रेजिस्टरs counting करोwn, or is the disable - re-enable
	 * going to restart the elapsed-समय counting? If counting is restarted
	 * the समयout should be decreased by the amount of समय that has
	 * elapsed since starting the समयr. Maybe we should store the monotonic
	 * घड़ी value when समयr is started so that अगर RTC is set जबतक समयr
	 * is armed we could करो the compensation. This is a hack अगर RTC/प्रणाली
	 * clk are drअगरting. OTOH, RTC controlled via I2C is in any हाल
	 * inaccurate...
	 */
	ret = regmap_पढ़ो(bd70528->regmap, BD70528_REG_ELAPSED_TIMER_EN,
			  &ctrl_reg);
	अगर (ret)
		वापस ret;

	अगर (old_state) अणु
		अगर (ctrl_reg & BD70528_MASK_ELAPSED_TIMER_EN)
			*old_state |= BD70528_ELAPSED_STATE_BIT;
		अन्यथा
			*old_state &= ~BD70528_ELAPSED_STATE_BIT;

		अगर ((!enable) == (!(*old_state & BD70528_ELAPSED_STATE_BIT)))
			वापस 0;
	पूर्ण

	अगर (enable)
		ctrl_reg |= BD70528_MASK_ELAPSED_TIMER_EN;
	अन्यथा
		ctrl_reg &= ~BD70528_MASK_ELAPSED_TIMER_EN;

	वापस regmap_ग_लिखो(bd70528->regmap, BD70528_REG_ELAPSED_TIMER_EN,
			    ctrl_reg);
पूर्ण

अटल पूर्णांक bd70528_set_rtc_based_समयrs(काष्ठा bd70528_rtc *r, पूर्णांक new_state,
					पूर्णांक *old_state)
अणु
	पूर्णांक ret;

	ret = bd70528_wdt_set(r->parent, new_state & BD70528_WDT_STATE_BIT,
			      old_state);
	अगर (ret) अणु
		dev_err(r->dev,
			"Failed to disable WDG for RTC setting (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = bd70528_set_elapsed_पंचांगr(r->parent,
				      new_state & BD70528_ELAPSED_STATE_BIT,
				      old_state);
	अगर (ret) अणु
		dev_err(r->dev,
			"Failed to disable 'elapsed timer' for RTC setting\n");
		वापस ret;
	पूर्ण
	ret = bd70528_set_wake(r->parent, new_state & BD70528_WAKE_STATE_BIT,
			       old_state);
	अगर (ret) अणु
		dev_err(r->dev,
			"Failed to disable 'wake timer' for RTC setting\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_re_enable_rtc_based_समयrs(काष्ठा bd70528_rtc *r,
					      पूर्णांक old_state)
अणु
	अगर (!r->has_rtc_समयrs)
		वापस 0;

	वापस bd70528_set_rtc_based_समयrs(r, old_state, शून्य);
पूर्ण

अटल पूर्णांक bd70528_disable_rtc_based_समयrs(काष्ठा bd70528_rtc *r,
					    पूर्णांक *old_state)
अणु
	अगर (!r->has_rtc_समयrs)
		वापस 0;

	वापस bd70528_set_rtc_based_समयrs(r, 0, old_state);
पूर्ण

अटल अंतरभूत व्योम पंचांगday2rtc(काष्ठा rtc_समय *t, काष्ठा bd70528_rtc_day *d)
अणु
	d->sec &= ~BD70528_MASK_RTC_SEC;
	d->min &= ~BD70528_MASK_RTC_MINUTE;
	d->hour &= ~BD70528_MASK_RTC_HOUR;
	d->sec |= bin2bcd(t->पंचांग_sec);
	d->min |= bin2bcd(t->पंचांग_min);
	d->hour |= bin2bcd(t->पंचांग_hour);
पूर्ण

अटल अंतरभूत व्योम पंचांग2rtc(काष्ठा rtc_समय *t, काष्ठा bd70528_rtc_data *r)
अणु
	r->day &= ~BD70528_MASK_RTC_DAY;
	r->week &= ~BD70528_MASK_RTC_WEEK;
	r->month &= ~BD70528_MASK_RTC_MONTH;
	/*
	 * PM and 24H bits are not used by Wake - thus we clear them
	 * here and not in पंचांगday2rtc() which is also used by wake.
	 */
	r->समय.सour &= ~(BD70528_MASK_RTC_HOUR_PM | BD70528_MASK_RTC_HOUR_24H);

	पंचांगday2rtc(t, &r->समय);
	/*
	 * We करो always set समय in 24H mode.
	 */
	r->समय.सour |= BD70528_MASK_RTC_HOUR_24H;
	r->day |= bin2bcd(t->पंचांग_mday);
	r->week |= bin2bcd(t->पंचांग_wday);
	r->month |= bin2bcd(t->पंचांग_mon + 1);
	r->year = bin2bcd(t->पंचांग_year - 100);
पूर्ण

अटल अंतरभूत व्योम rtc2पंचांग(काष्ठा bd70528_rtc_data *r, काष्ठा rtc_समय *t)
अणु
	t->पंचांग_sec = bcd2bin(r->समय.sec & BD70528_MASK_RTC_SEC);
	t->पंचांग_min = bcd2bin(r->समय.min & BD70528_MASK_RTC_MINUTE);
	t->पंचांग_hour = bcd2bin(r->समय.सour & BD70528_MASK_RTC_HOUR);
	/*
	 * If RTC is in 12H mode, then bit BD70528_MASK_RTC_HOUR_PM
	 * is not BCD value but tells whether it is AM or PM
	 */
	अगर (!(r->समय.सour & BD70528_MASK_RTC_HOUR_24H)) अणु
		t->पंचांग_hour %= 12;
		अगर (r->समय.सour & BD70528_MASK_RTC_HOUR_PM)
			t->पंचांग_hour += 12;
	पूर्ण
	t->पंचांग_mday = bcd2bin(r->day & BD70528_MASK_RTC_DAY);
	t->पंचांग_mon = bcd2bin(r->month & BD70528_MASK_RTC_MONTH) - 1;
	t->पंचांग_year = 100 + bcd2bin(r->year & BD70528_MASK_RTC_YEAR);
	t->पंचांग_wday = bcd2bin(r->week & BD70528_MASK_RTC_WEEK);
पूर्ण

अटल पूर्णांक bd71828_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *a)
अणु
	पूर्णांक ret;
	काष्ठा bd71828_rtc_alm alm;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	ret = regmap_bulk_पढ़ो(r->regmap, r->bd718xx_alm_block_start, &alm,
			       माप(alm));
	अगर (ret) अणु
		dev_err(dev, "Failed to read alarm regs\n");
		वापस ret;
	पूर्ण

	पंचांग2rtc(&a->समय, &alm.alm0);

	अगर (!a->enabled)
		alm.alm_mask &= ~BD70528_MASK_ALM_EN;
	अन्यथा
		alm.alm_mask |= BD70528_MASK_ALM_EN;

	ret = regmap_bulk_ग_लिखो(r->regmap, r->bd718xx_alm_block_start, &alm,
				माप(alm));
	अगर (ret)
		dev_err(dev, "Failed to set alarm time\n");

	वापस ret;

पूर्ण

अटल पूर्णांक bd70528_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *a)
अणु
	काष्ठा bd70528_rtc_wake wake;
	काष्ठा bd70528_rtc_alm alm;
	पूर्णांक ret;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	ret = regmap_bulk_पढ़ो(r->regmap, BD70528_REG_RTC_WAKE_START, &wake,
			       माप(wake));
	अगर (ret) अणु
		dev_err(dev, "Failed to read wake regs\n");
		वापस ret;
	पूर्ण

	ret = regmap_bulk_पढ़ो(r->regmap, BD70528_REG_RTC_ALM_START, &alm,
			       माप(alm));
	अगर (ret) अणु
		dev_err(dev, "Failed to read alarm regs\n");
		वापस ret;
	पूर्ण

	पंचांग2rtc(&a->समय, &alm.data);
	पंचांगday2rtc(&a->समय, &wake.समय);

	अगर (a->enabled) अणु
		alm.alm_mask &= ~BD70528_MASK_ALM_EN;
		wake.ctrl |= BD70528_MASK_WAKE_EN;
	पूर्ण अन्यथा अणु
		alm.alm_mask |= BD70528_MASK_ALM_EN;
		wake.ctrl &= ~BD70528_MASK_WAKE_EN;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(r->regmap, BD70528_REG_RTC_WAKE_START, &wake,
				माप(wake));
	अगर (ret) अणु
		dev_err(dev, "Failed to set wake time\n");
		वापस ret;
	पूर्ण
	ret = regmap_bulk_ग_लिखो(r->regmap, BD70528_REG_RTC_ALM_START, &alm,
				माप(alm));
	अगर (ret)
		dev_err(dev, "Failed to set alarm time\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bd71828_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *a)
अणु
	पूर्णांक ret;
	काष्ठा bd71828_rtc_alm alm;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	ret = regmap_bulk_पढ़ो(r->regmap, r->bd718xx_alm_block_start, &alm,
			       माप(alm));
	अगर (ret) अणु
		dev_err(dev, "Failed to read alarm regs\n");
		वापस ret;
	पूर्ण

	rtc2पंचांग(&alm.alm0, &a->समय);
	a->समय.पंचांग_mday = -1;
	a->समय.पंचांग_mon = -1;
	a->समय.पंचांग_year = -1;
	a->enabled = !!(alm.alm_mask & BD70528_MASK_ALM_EN);
	a->pending = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *a)
अणु
	काष्ठा bd70528_rtc_alm alm;
	पूर्णांक ret;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	ret = regmap_bulk_पढ़ो(r->regmap, BD70528_REG_RTC_ALM_START, &alm,
			       माप(alm));
	अगर (ret) अणु
		dev_err(dev, "Failed to read alarm regs\n");
		वापस ret;
	पूर्ण

	rtc2पंचांग(&alm.data, &a->समय);
	a->समय.पंचांग_mday = -1;
	a->समय.पंचांग_mon = -1;
	a->समय.पंचांग_year = -1;
	a->enabled = !(alm.alm_mask & BD70528_MASK_ALM_EN);
	a->pending = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_set_समय_locked(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	पूर्णांक ret, पंचांगpret, old_states;
	काष्ठा bd70528_rtc_data rtc_data;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	ret = bd70528_disable_rtc_based_समयrs(r, &old_states);
	अगर (ret)
		वापस ret;

	पंचांगpret = regmap_bulk_पढ़ो(r->regmap, r->reg_समय_start, &rtc_data,
				  माप(rtc_data));
	अगर (पंचांगpret) अणु
		dev_err(dev, "Failed to read RTC time registers\n");
		जाओ renable_out;
	पूर्ण
	पंचांग2rtc(t, &rtc_data);

	पंचांगpret = regmap_bulk_ग_लिखो(r->regmap, r->reg_समय_start, &rtc_data,
				   माप(rtc_data));
	अगर (पंचांगpret) अणु
		dev_err(dev, "Failed to set RTC time\n");
		जाओ renable_out;
	पूर्ण

renable_out:
	ret = bd70528_re_enable_rtc_based_समयrs(r, old_states);
	अगर (पंचांगpret)
		ret = पंचांगpret;

	वापस ret;
पूर्ण

अटल पूर्णांक bd71828_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	वापस bd70528_set_समय_locked(dev, t);
पूर्ण

अटल पूर्णांक bd70528_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	पूर्णांक ret;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	bd70528_wdt_lock(r->parent);
	ret = bd70528_set_समय_locked(dev, t);
	bd70528_wdt_unlock(r->parent);
	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);
	काष्ठा bd70528_rtc_data rtc_data;
	पूर्णांक ret;

	/* पढ़ो the RTC date and समय रेजिस्टरs all at once */
	ret = regmap_bulk_पढ़ो(r->regmap, r->reg_समय_start, &rtc_data,
			       माप(rtc_data));
	अगर (ret) अणु
		dev_err(dev, "Failed to read RTC time (err %d)\n", ret);
		वापस ret;
	पूर्ण

	rtc2पंचांग(&rtc_data, t);

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_alm_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक enableval = BD70528_MASK_ALM_EN;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);

	अगर (enabled)
		enableval = 0;

	bd70528_wdt_lock(r->parent);
	ret = bd70528_set_wake(r->parent, enabled, शून्य);
	अगर (ret) अणु
		dev_err(dev, "Failed to change wake state\n");
		जाओ out_unlock;
	पूर्ण
	ret = regmap_update_bits(r->regmap, BD70528_REG_RTC_ALM_MASK,
				 BD70528_MASK_ALM_EN, enableval);
	अगर (ret)
		dev_err(dev, "Failed to change alarm state\n");

out_unlock:
	bd70528_wdt_unlock(r->parent);
	वापस ret;
पूर्ण

अटल पूर्णांक bd71828_alm_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	पूर्णांक ret;
	काष्ठा bd70528_rtc *r = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक enableval = BD70528_MASK_ALM_EN;

	अगर (!enabled)
		enableval = 0;

	ret = regmap_update_bits(r->regmap, r->bd718xx_alm_block_start +
				 BD718XX_ALM_EN_OFFSET, BD70528_MASK_ALM_EN,
				 enableval);
	अगर (ret)
		dev_err(dev, "Failed to change alarm state\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops bd70528_rtc_ops = अणु
	.पढ़ो_समय		= bd70528_get_समय,
	.set_समय		= bd70528_set_समय,
	.पढ़ो_alarm		= bd70528_पढ़ो_alarm,
	.set_alarm		= bd70528_set_alarm,
	.alarm_irq_enable	= bd70528_alm_enable,
पूर्ण;

अटल स्थिर काष्ठा rtc_class_ops bd71828_rtc_ops = अणु
	.पढ़ो_समय		= bd70528_get_समय,
	.set_समय		= bd71828_set_समय,
	.पढ़ो_alarm		= bd71828_पढ़ो_alarm,
	.set_alarm		= bd71828_set_alarm,
	.alarm_irq_enable	= bd71828_alm_enable,
पूर्ण;

अटल irqवापस_t alm_hndlr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rtc_device *rtc = data;

	rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF | RTC_PF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bd70528_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd70528_rtc *bd_rtc;
	स्थिर काष्ठा rtc_class_ops *rtc_ops;
	स्थिर अक्षर *irq_name;
	पूर्णांक ret;
	काष्ठा rtc_device *rtc;
	पूर्णांक irq;
	अचिन्हित पूर्णांक hr;
	bool enable_मुख्य_irq = false;
	u8 hour_reg;
	क्रमागत rohm_chip_type chip = platक्रमm_get_device_id(pdev)->driver_data;

	bd_rtc = devm_kzalloc(&pdev->dev, माप(*bd_rtc), GFP_KERNEL);
	अगर (!bd_rtc)
		वापस -ENOMEM;

	bd_rtc->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!bd_rtc->regmap) अणु
		dev_err(&pdev->dev, "No regmap\n");
		वापस -EINVAL;
	पूर्ण

	bd_rtc->dev = &pdev->dev;

	चयन (chip) अणु
	हाल ROHM_CHIP_TYPE_BD70528:
		bd_rtc->parent = dev_get_drvdata(pdev->dev.parent);
		अगर (!bd_rtc->parent) अणु
			dev_err(&pdev->dev, "No MFD data\n");
			वापस -EINVAL;
		पूर्ण
		irq_name = "bd70528-rtc-alm";
		bd_rtc->has_rtc_समयrs = true;
		bd_rtc->reg_समय_start = BD70528_REG_RTC_START;
		hour_reg = BD70528_REG_RTC_HOUR;
		enable_मुख्य_irq = true;
		rtc_ops = &bd70528_rtc_ops;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71815:
		irq_name = "bd71815-rtc-alm-0";
		bd_rtc->reg_समय_start = BD71815_REG_RTC_START;

		/*
		 * See also BD718XX_ALM_EN_OFFSET:
		 * This works क्रम BD71828 and BD71815 as they have same offset
		 * between ALM0 start and ALM0_MASK. If new ICs are to be
		 * added this requires proper check as ALM0_MASK is not located
		 * at the end of ALM0 block - but after all ALM blocks so अगर
		 * amount of ALMs dअगरfer the offset to enable/disable is likely
		 * to be incorrect and enable/disable must be given as own
		 * reg address here.
		 */
		bd_rtc->bd718xx_alm_block_start = BD71815_REG_RTC_ALM_START;
		hour_reg = BD71815_REG_HOUR;
		rtc_ops = &bd71828_rtc_ops;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71828:
		irq_name = "bd71828-rtc-alm-0";
		bd_rtc->reg_समय_start = BD71828_REG_RTC_START;
		bd_rtc->bd718xx_alm_block_start = BD71828_REG_RTC_ALM_START;
		hour_reg = BD71828_REG_RTC_HOUR;
		rtc_ops = &bd71828_rtc_ops;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown chip\n");
		वापस -ENOENT;
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, irq_name);

	अगर (irq < 0)
		वापस irq;

	platक्रमm_set_drvdata(pdev, bd_rtc);

	ret = regmap_पढ़ो(bd_rtc->regmap, hour_reg, &hr);

	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to reag RTC clock\n");
		वापस ret;
	पूर्ण

	अगर (!(hr & BD70528_MASK_RTC_HOUR_24H)) अणु
		काष्ठा rtc_समय t;

		ret = rtc_ops->पढ़ो_समय(&pdev->dev, &t);

		अगर (!ret)
			ret = rtc_ops->set_समय(&pdev->dev, &t);

		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Setting 24H clock for RTC failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	device_set_wakeup_capable(&pdev->dev, true);
	device_wakeup_enable(&pdev->dev);

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc)) अणु
		dev_err(&pdev->dev, "RTC device creation failed\n");
		वापस PTR_ERR(rtc);
	पूर्ण

	rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->range_max = RTC_TIMESTAMP_END_2099;
	rtc->ops = rtc_ops;

	/* Request alarm IRQ prior to रेजिस्टरig the RTC */
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, &alm_hndlr,
					IRQF_ONESHOT, "bd70528-rtc", rtc);
	अगर (ret)
		वापस ret;

	/*
	 *  BD70528 irq controller is not touching the मुख्य mask रेजिस्टर.
	 *  So enable the RTC block पूर्णांकerrupts at मुख्य level. We can just
	 *  leave them enabled as irq-controller should disable irqs
	 *  from sub-रेजिस्टरs when IRQ is disabled or मुक्तd.
	 */
	अगर (enable_मुख्य_irq) अणु
		ret = regmap_update_bits(bd_rtc->regmap,
				 BD70528_REG_INT_MAIN_MASK,
				 BD70528_INT_RTC_MASK, 0);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to enable RTC interrupts\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd718x7_rtc_id[] = अणु
	अणु "bd70528-rtc", ROHM_CHIP_TYPE_BD70528 पूर्ण,
	अणु "bd71828-rtc", ROHM_CHIP_TYPE_BD71828 पूर्ण,
	अणु "bd71815-rtc", ROHM_CHIP_TYPE_BD71815 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd718x7_rtc_id);

अटल काष्ठा platक्रमm_driver bd70528_rtc = अणु
	.driver = अणु
		.name = "bd70528-rtc"
	पूर्ण,
	.probe = bd70528_probe,
	.id_table = bd718x7_rtc_id,
पूर्ण;

module_platक्रमm_driver(bd70528_rtc);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD70528 and BD71828 PMIC RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd70528-rtc");
