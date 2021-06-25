<शैली गुरु>
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 *
 * SPDX-License-Identअगरier: GPL-2.0
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

#घोषणा SPRD_RTC_SEC_CNT_VALUE		0x0
#घोषणा SPRD_RTC_MIN_CNT_VALUE		0x4
#घोषणा SPRD_RTC_HOUR_CNT_VALUE		0x8
#घोषणा SPRD_RTC_DAY_CNT_VALUE		0xc
#घोषणा SPRD_RTC_SEC_CNT_UPD		0x10
#घोषणा SPRD_RTC_MIN_CNT_UPD		0x14
#घोषणा SPRD_RTC_HOUR_CNT_UPD		0x18
#घोषणा SPRD_RTC_DAY_CNT_UPD		0x1c
#घोषणा SPRD_RTC_SEC_ALM_UPD		0x20
#घोषणा SPRD_RTC_MIN_ALM_UPD		0x24
#घोषणा SPRD_RTC_HOUR_ALM_UPD		0x28
#घोषणा SPRD_RTC_DAY_ALM_UPD		0x2c
#घोषणा SPRD_RTC_INT_EN			0x30
#घोषणा SPRD_RTC_INT_RAW_STS		0x34
#घोषणा SPRD_RTC_INT_CLR		0x38
#घोषणा SPRD_RTC_INT_MASK_STS		0x3C
#घोषणा SPRD_RTC_SEC_ALM_VALUE		0x40
#घोषणा SPRD_RTC_MIN_ALM_VALUE		0x44
#घोषणा SPRD_RTC_HOUR_ALM_VALUE		0x48
#घोषणा SPRD_RTC_DAY_ALM_VALUE		0x4c
#घोषणा SPRD_RTC_SPG_VALUE		0x50
#घोषणा SPRD_RTC_SPG_UPD		0x54
#घोषणा SPRD_RTC_PWR_CTRL		0x58
#घोषणा SPRD_RTC_PWR_STS		0x5c
#घोषणा SPRD_RTC_SEC_AUXALM_UPD		0x60
#घोषणा SPRD_RTC_MIN_AUXALM_UPD		0x64
#घोषणा SPRD_RTC_HOUR_AUXALM_UPD	0x68
#घोषणा SPRD_RTC_DAY_AUXALM_UPD		0x6c

/* BIT & MASK definition क्रम SPRD_RTC_INT_* रेजिस्टरs */
#घोषणा SPRD_RTC_SEC_EN			BIT(0)
#घोषणा SPRD_RTC_MIN_EN			BIT(1)
#घोषणा SPRD_RTC_HOUR_EN		BIT(2)
#घोषणा SPRD_RTC_DAY_EN			BIT(3)
#घोषणा SPRD_RTC_ALARM_EN		BIT(4)
#घोषणा SPRD_RTC_HRS_FORMAT_EN		BIT(5)
#घोषणा SPRD_RTC_AUXALM_EN		BIT(6)
#घोषणा SPRD_RTC_SPG_UPD_EN		BIT(7)
#घोषणा SPRD_RTC_SEC_UPD_EN		BIT(8)
#घोषणा SPRD_RTC_MIN_UPD_EN		BIT(9)
#घोषणा SPRD_RTC_HOUR_UPD_EN		BIT(10)
#घोषणा SPRD_RTC_DAY_UPD_EN		BIT(11)
#घोषणा SPRD_RTC_ALMSEC_UPD_EN		BIT(12)
#घोषणा SPRD_RTC_ALMMIN_UPD_EN		BIT(13)
#घोषणा SPRD_RTC_ALMHOUR_UPD_EN		BIT(14)
#घोषणा SPRD_RTC_ALMDAY_UPD_EN		BIT(15)
#घोषणा SPRD_RTC_INT_MASK		GENMASK(15, 0)

#घोषणा SPRD_RTC_TIME_INT_MASK				\
	(SPRD_RTC_SEC_UPD_EN | SPRD_RTC_MIN_UPD_EN |	\
	 SPRD_RTC_HOUR_UPD_EN | SPRD_RTC_DAY_UPD_EN)

#घोषणा SPRD_RTC_ALMTIME_INT_MASK				\
	(SPRD_RTC_ALMSEC_UPD_EN | SPRD_RTC_ALMMIN_UPD_EN |	\
	 SPRD_RTC_ALMHOUR_UPD_EN | SPRD_RTC_ALMDAY_UPD_EN)

#घोषणा SPRD_RTC_ALM_INT_MASK			\
	(SPRD_RTC_SEC_EN | SPRD_RTC_MIN_EN |	\
	 SPRD_RTC_HOUR_EN | SPRD_RTC_DAY_EN |	\
	 SPRD_RTC_ALARM_EN | SPRD_RTC_AUXALM_EN)

/* second/minute/hour/day values mask definition */
#घोषणा SPRD_RTC_SEC_MASK		GENMASK(5, 0)
#घोषणा SPRD_RTC_MIN_MASK		GENMASK(5, 0)
#घोषणा SPRD_RTC_HOUR_MASK		GENMASK(4, 0)
#घोषणा SPRD_RTC_DAY_MASK		GENMASK(15, 0)

/* alarm lock definition क्रम SPRD_RTC_SPG_UPD रेजिस्टर */
#घोषणा SPRD_RTC_ALMLOCK_MASK		GENMASK(7, 0)
#घोषणा SPRD_RTC_ALM_UNLOCK		0xa5
#घोषणा SPRD_RTC_ALM_LOCK		(~SPRD_RTC_ALM_UNLOCK &	\
					 SPRD_RTC_ALMLOCK_MASK)

/* SPG values definition क्रम SPRD_RTC_SPG_UPD रेजिस्टर */
#घोषणा SPRD_RTC_POWEROFF_ALM_FLAG	BIT(8)

/* घातer control/status definition */
#घोषणा SPRD_RTC_POWER_RESET_VALUE	0x96
#घोषणा SPRD_RTC_POWER_STS_CLEAR	GENMASK(7, 0)
#घोषणा SPRD_RTC_POWER_STS_SHIFT	8
#घोषणा SPRD_RTC_POWER_STS_VALID	\
	(~SPRD_RTC_POWER_RESET_VALUE << SPRD_RTC_POWER_STS_SHIFT)

/* समयout of synchronizing समय and alarm रेजिस्टरs (us) */
#घोषणा SPRD_RTC_POLL_TIMEOUT		200000
#घोषणा SPRD_RTC_POLL_DELAY_US		20000

काष्ठा sprd_rtc अणु
	काष्ठा rtc_device	*rtc;
	काष्ठा regmap		*regmap;
	काष्ठा device		*dev;
	u32			base;
	पूर्णांक			irq;
	bool			valid;
पूर्ण;

/*
 * The Spपढ़ोtrum RTC controller has 3 groups रेजिस्टरs, including समय, normal
 * alarm and auxiliary alarm. The समय group रेजिस्टरs are used to set RTC समय,
 * the normal alarm रेजिस्टरs are used to set normal alarm, and the auxiliary
 * alarm रेजिस्टरs are used to set auxiliary alarm. Both alarm event and
 * auxiliary alarm event can wake up प्रणाली from deep sleep, but only alarm
 * event can घातer up प्रणाली from घातer करोwn status.
 */
क्रमागत sprd_rtc_reg_types अणु
	SPRD_RTC_TIME,
	SPRD_RTC_ALARM,
	SPRD_RTC_AUX_ALARM,
पूर्ण;

अटल पूर्णांक sprd_rtc_clear_alarm_पूर्णांकs(काष्ठा sprd_rtc *rtc)
अणु
	वापस regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			    SPRD_RTC_ALM_INT_MASK);
पूर्ण

अटल पूर्णांक sprd_rtc_lock_alarm(काष्ठा sprd_rtc *rtc, bool lock)
अणु
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + SPRD_RTC_SPG_VALUE, &val);
	अगर (ret)
		वापस ret;

	val &= ~SPRD_RTC_ALMLOCK_MASK;
	अगर (lock)
		val |= SPRD_RTC_ALM_LOCK;
	अन्यथा
		val |= SPRD_RTC_ALM_UNLOCK | SPRD_RTC_POWEROFF_ALM_FLAG;

	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_SPG_UPD, val);
	अगर (ret)
		वापस ret;

	/* रुको until the SPG value is updated successfully */
	ret = regmap_पढ़ो_poll_समयout(rtc->regmap,
				       rtc->base + SPRD_RTC_INT_RAW_STS, val,
				       (val & SPRD_RTC_SPG_UPD_EN),
				       SPRD_RTC_POLL_DELAY_US,
				       SPRD_RTC_POLL_TIMEOUT);
	अगर (ret) अणु
		dev_err(rtc->dev, "failed to update SPG value:%d\n", ret);
		वापस ret;
	पूर्ण

	वापस regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			    SPRD_RTC_SPG_UPD_EN);
पूर्ण

अटल पूर्णांक sprd_rtc_get_secs(काष्ठा sprd_rtc *rtc, क्रमागत sprd_rtc_reg_types type,
			     समय64_t *secs)
अणु
	u32 sec_reg, min_reg, hour_reg, day_reg;
	u32 val, sec, min, hour, day;
	पूर्णांक ret;

	चयन (type) अणु
	हाल SPRD_RTC_TIME:
		sec_reg = SPRD_RTC_SEC_CNT_VALUE;
		min_reg = SPRD_RTC_MIN_CNT_VALUE;
		hour_reg = SPRD_RTC_HOUR_CNT_VALUE;
		day_reg = SPRD_RTC_DAY_CNT_VALUE;
		अवरोध;
	हाल SPRD_RTC_ALARM:
		sec_reg = SPRD_RTC_SEC_ALM_VALUE;
		min_reg = SPRD_RTC_MIN_ALM_VALUE;
		hour_reg = SPRD_RTC_HOUR_ALM_VALUE;
		day_reg = SPRD_RTC_DAY_ALM_VALUE;
		अवरोध;
	हाल SPRD_RTC_AUX_ALARM:
		sec_reg = SPRD_RTC_SEC_AUXALM_UPD;
		min_reg = SPRD_RTC_MIN_AUXALM_UPD;
		hour_reg = SPRD_RTC_HOUR_AUXALM_UPD;
		day_reg = SPRD_RTC_DAY_AUXALM_UPD;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + sec_reg, &val);
	अगर (ret)
		वापस ret;

	sec = val & SPRD_RTC_SEC_MASK;

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + min_reg, &val);
	अगर (ret)
		वापस ret;

	min = val & SPRD_RTC_MIN_MASK;

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + hour_reg, &val);
	अगर (ret)
		वापस ret;

	hour = val & SPRD_RTC_HOUR_MASK;

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + day_reg, &val);
	अगर (ret)
		वापस ret;

	day = val & SPRD_RTC_DAY_MASK;
	*secs = (((समय64_t)(day * 24) + hour) * 60 + min) * 60 + sec;
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_rtc_set_secs(काष्ठा sprd_rtc *rtc, क्रमागत sprd_rtc_reg_types type,
			     समय64_t secs)
अणु
	u32 sec_reg, min_reg, hour_reg, day_reg, sts_mask;
	u32 sec, min, hour, day, val;
	पूर्णांक ret, rem;

	/* convert seconds to RTC समय क्रमmat */
	day = भाग_s64_rem(secs, 86400, &rem);
	hour = rem / 3600;
	rem -= hour * 3600;
	min = rem / 60;
	sec = rem - min * 60;

	चयन (type) अणु
	हाल SPRD_RTC_TIME:
		sec_reg = SPRD_RTC_SEC_CNT_UPD;
		min_reg = SPRD_RTC_MIN_CNT_UPD;
		hour_reg = SPRD_RTC_HOUR_CNT_UPD;
		day_reg = SPRD_RTC_DAY_CNT_UPD;
		sts_mask = SPRD_RTC_TIME_INT_MASK;
		अवरोध;
	हाल SPRD_RTC_ALARM:
		sec_reg = SPRD_RTC_SEC_ALM_UPD;
		min_reg = SPRD_RTC_MIN_ALM_UPD;
		hour_reg = SPRD_RTC_HOUR_ALM_UPD;
		day_reg = SPRD_RTC_DAY_ALM_UPD;
		sts_mask = SPRD_RTC_ALMTIME_INT_MASK;
		अवरोध;
	हाल SPRD_RTC_AUX_ALARM:
		sec_reg = SPRD_RTC_SEC_AUXALM_UPD;
		min_reg = SPRD_RTC_MIN_AUXALM_UPD;
		hour_reg = SPRD_RTC_HOUR_AUXALM_UPD;
		day_reg = SPRD_RTC_DAY_AUXALM_UPD;
		sts_mask = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + sec_reg, sec);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + min_reg, min);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + hour_reg, hour);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + day_reg, day);
	अगर (ret)
		वापस ret;

	अगर (type == SPRD_RTC_AUX_ALARM)
		वापस 0;

	/*
	 * Since the समय and normal alarm रेजिस्टरs are put in always-घातer-on
	 * region supplied by VDDRTC, then these रेजिस्टरs changing समय will
	 * be very दीर्घ, about 125ms. Thus here we should रुको until all
	 * values are updated successfully.
	 */
	ret = regmap_पढ़ो_poll_समयout(rtc->regmap,
				       rtc->base + SPRD_RTC_INT_RAW_STS, val,
				       ((val & sts_mask) == sts_mask),
				       SPRD_RTC_POLL_DELAY_US,
				       SPRD_RTC_POLL_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(rtc->dev, "set time/alarm values timeout\n");
		वापस ret;
	पूर्ण

	वापस regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			    sts_mask);
पूर्ण

अटल पूर्णांक sprd_rtc_set_aux_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sprd_rtc *rtc = dev_get_drvdata(dev);
	समय64_t secs = rtc_पंचांग_to_समय64(&alrm->समय);
	पूर्णांक ret;

	/* clear the auxiliary alarm पूर्णांकerrupt status */
	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			   SPRD_RTC_AUXALM_EN);
	अगर (ret)
		वापस ret;

	ret = sprd_rtc_set_secs(rtc, SPRD_RTC_AUX_ALARM, secs);
	अगर (ret)
		वापस ret;

	अगर (alrm->enabled) अणु
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_AUXALM_EN,
					 SPRD_RTC_AUXALM_EN);
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_AUXALM_EN, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sprd_rtc *rtc = dev_get_drvdata(dev);
	समय64_t secs;
	पूर्णांक ret;

	अगर (!rtc->valid) अणु
		dev_warn(dev, "RTC values are invalid\n");
		वापस -EINVAL;
	पूर्ण

	ret = sprd_rtc_get_secs(rtc, SPRD_RTC_TIME, &secs);
	अगर (ret)
		वापस ret;

	rtc_समय64_to_पंचांग(secs, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sprd_rtc *rtc = dev_get_drvdata(dev);
	समय64_t secs = rtc_पंचांग_to_समय64(पंचांग);
	पूर्णांक ret;

	ret = sprd_rtc_set_secs(rtc, SPRD_RTC_TIME, secs);
	अगर (ret)
		वापस ret;

	अगर (!rtc->valid) अणु
		/* Clear RTC घातer status firstly */
		ret = regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_PWR_CTRL,
				   SPRD_RTC_POWER_STS_CLEAR);
		अगर (ret)
			वापस ret;

		/*
		 * Set RTC घातer status to indicate now RTC has valid समय
		 * values.
		 */
		ret = regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_PWR_CTRL,
				   SPRD_RTC_POWER_STS_VALID);
		अगर (ret)
			वापस ret;

		rtc->valid = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sprd_rtc *rtc = dev_get_drvdata(dev);
	समय64_t secs;
	पूर्णांक ret;
	u32 val;

	/*
	 * The RTC core checks to see अगर there is an alarm alपढ़ोy set in RTC
	 * hardware, and we always पढ़ो the normal alarm at this समय.
	 */
	ret = sprd_rtc_get_secs(rtc, SPRD_RTC_ALARM, &secs);
	अगर (ret)
		वापस ret;

	rtc_समय64_to_पंचांग(secs, &alrm->समय);

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + SPRD_RTC_INT_EN, &val);
	अगर (ret)
		वापस ret;

	alrm->enabled = !!(val & SPRD_RTC_ALARM_EN);

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + SPRD_RTC_INT_RAW_STS, &val);
	अगर (ret)
		वापस ret;

	alrm->pending = !!(val & SPRD_RTC_ALARM_EN);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sprd_rtc *rtc = dev_get_drvdata(dev);
	समय64_t secs = rtc_पंचांग_to_समय64(&alrm->समय);
	काष्ठा rtc_समय aie_समय =
		rtc_kसमय_प्रकारo_पंचांग(rtc->rtc->aie_समयr.node.expires);
	पूर्णांक ret;

	/*
	 * We have 2 groups alarms: normal alarm and auxiliary alarm. Since
	 * both normal alarm event and auxiliary alarm event can wake up प्रणाली
	 * from deep sleep, but only alarm event can घातer up प्रणाली from घातer
	 * करोwn status. Moreover we करो not need to poll about 125ms when
	 * updating auxiliary alarm रेजिस्टरs. Thus we usually set auxiliary
	 * alarm when wake up प्रणाली from deep sleep, and क्रम other scenarios,
	 * we should set normal alarm with polling status.
	 *
	 * So here we check अगर the alarm समय is set by aie_समयr, अगर yes, we
	 * should set normal alarm, अगर not, we should set auxiliary alarm which
	 * means it is just a wake event.
	 */
	अगर (!rtc->rtc->aie_समयr.enabled || rtc_पंचांग_sub(&aie_समय, &alrm->समय))
		वापस sprd_rtc_set_aux_alarm(dev, alrm);

	/* clear the alarm पूर्णांकerrupt status firstly */
	ret = regmap_ग_लिखो(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			   SPRD_RTC_ALARM_EN);
	अगर (ret)
		वापस ret;

	ret = sprd_rtc_set_secs(rtc, SPRD_RTC_ALARM, secs);
	अगर (ret)
		वापस ret;

	अगर (alrm->enabled) अणु
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_ALARM_EN,
					 SPRD_RTC_ALARM_EN);
		अगर (ret)
			वापस ret;

		/* unlock the alarm to enable the alarm function. */
		ret = sprd_rtc_lock_alarm(rtc, false);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rtc->regmap,
				   rtc->base + SPRD_RTC_INT_EN,
				   SPRD_RTC_ALARM_EN, 0);

		/*
		 * Lock the alarm function in हाल fake alarm event will घातer
		 * up प्रणालीs.
		 */
		ret = sprd_rtc_lock_alarm(rtc, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा sprd_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (enabled) अणु
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_ALARM_EN | SPRD_RTC_AUXALM_EN,
					 SPRD_RTC_ALARM_EN | SPRD_RTC_AUXALM_EN);
		अगर (ret)
			वापस ret;

		ret = sprd_rtc_lock_alarm(rtc, false);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rtc->regmap, rtc->base + SPRD_RTC_INT_EN,
				   SPRD_RTC_ALARM_EN | SPRD_RTC_AUXALM_EN, 0);

		ret = sprd_rtc_lock_alarm(rtc, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sprd_rtc_ops = अणु
	.पढ़ो_समय = sprd_rtc_पढ़ो_समय,
	.set_समय = sprd_rtc_set_समय,
	.पढ़ो_alarm = sprd_rtc_पढ़ो_alarm,
	.set_alarm = sprd_rtc_set_alarm,
	.alarm_irq_enable = sprd_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t sprd_rtc_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sprd_rtc *rtc = dev_id;
	पूर्णांक ret;

	ret = sprd_rtc_clear_alarm_पूर्णांकs(rtc);
	अगर (ret)
		वापस IRQ_RETVAL(ret);

	rtc_update_irq(rtc->rtc, 1, RTC_AF | RTC_IRQF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sprd_rtc_check_घातer_करोwn(काष्ठा sprd_rtc *rtc)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + SPRD_RTC_PWR_STS, &val);
	अगर (ret)
		वापस ret;

	/*
	 * If the RTC घातer status value is SPRD_RTC_POWER_RESET_VALUE, which
	 * means the RTC has been घातered करोwn, so the RTC समय values are
	 * invalid.
	 */
	rtc->valid = val != SPRD_RTC_POWER_RESET_VALUE;
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_rtc_check_alarm_पूर्णांक(काष्ठा sprd_rtc *rtc)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rtc->regmap, rtc->base + SPRD_RTC_SPG_VALUE, &val);
	अगर (ret)
		वापस ret;

	/*
	 * The SPRD_RTC_INT_EN रेजिस्टर is not put in always-घातer-on region
	 * supplied by VDDRTC, so we should check अगर we need enable the alarm
	 * पूर्णांकerrupt when प्रणाली booting.
	 *
	 * If we have set SPRD_RTC_POWEROFF_ALM_FLAG which is saved in
	 * always-घातer-on region, that means we have set one alarm last समय,
	 * so we should enable the alarm पूर्णांकerrupt to help RTC core to see अगर
	 * there is an alarm alपढ़ोy set in RTC hardware.
	 */
	अगर (!(val & SPRD_RTC_POWEROFF_ALM_FLAG))
		वापस 0;

	वापस regmap_update_bits(rtc->regmap, rtc->base + SPRD_RTC_INT_EN,
				  SPRD_RTC_ALARM_EN, SPRD_RTC_ALARM_EN);
पूर्ण

अटल पूर्णांक sprd_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा sprd_rtc *rtc;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!rtc->regmap)
		वापस -ENODEV;

	ret = of_property_पढ़ो_u32(node, "reg", &rtc->base);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get RTC base address\n");
		वापस ret;
	पूर्ण

	rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rtc->irq < 0)
		वापस rtc->irq;

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc))
		वापस PTR_ERR(rtc->rtc);

	rtc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, rtc);

	/* check अगर we need set the alarm पूर्णांकerrupt */
	ret = sprd_rtc_check_alarm_पूर्णांक(rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to check RTC alarm interrupt\n");
		वापस ret;
	पूर्ण

	/* check अगर RTC समय values are valid */
	ret = sprd_rtc_check_घातer_करोwn(rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to check RTC time values\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
					sprd_rtc_handler,
					IRQF_ONESHOT | IRQF_EARLY_RESUME,
					pdev->name, rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request RTC irq\n");
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	rtc->rtc->ops = &sprd_rtc_ops;
	rtc->rtc->range_min = 0;
	rtc->rtc->range_max = 5662310399LL;
	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret) अणु
		device_init_wakeup(&pdev->dev, 0);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_rtc_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-rtc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_rtc_of_match);

अटल काष्ठा platक्रमm_driver sprd_rtc_driver = अणु
	.driver = अणु
		.name = "sprd-rtc",
		.of_match_table = sprd_rtc_of_match,
	पूर्ण,
	.probe	= sprd_rtc_probe,
पूर्ण;
module_platक्रमm_driver(sprd_rtc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Spreadtrum RTC Device Driver");
MODULE_AUTHOR("Baolin Wang <baolin.wang@spreadtrum.com>");
