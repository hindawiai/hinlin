<शैली गुरु>
/*
 * rtc-palmas.c -- Palmas Real Time Clock driver.

 * RTC driver क्रम TI Palma series devices like TPS65913,
 * TPS65914 घातer management IC.
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/bcd.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/rtc.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>

काष्ठा palmas_rtc अणु
	काष्ठा rtc_device	*rtc;
	काष्ठा device		*dev;
	अचिन्हित पूर्णांक		irq;
पूर्ण;

/* Total number of RTC रेजिस्टरs needed to set समय*/
#घोषणा PALMAS_NUM_TIME_REGS	(PALMAS_YEARS_REG - PALMAS_SECONDS_REG + 1)

अटल पूर्णांक palmas_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर rtc_data[PALMAS_NUM_TIME_REGS];
	काष्ठा palmas *palmas = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	/* Copy RTC counting रेजिस्टरs to अटल रेजिस्टरs or latches */
	ret = palmas_update_bits(palmas, PALMAS_RTC_BASE, PALMAS_RTC_CTRL_REG,
		PALMAS_RTC_CTRL_REG_GET_TIME, PALMAS_RTC_CTRL_REG_GET_TIME);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC CTRL reg update failed, err: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = palmas_bulk_पढ़ो(palmas, PALMAS_RTC_BASE, PALMAS_SECONDS_REG,
			rtc_data, PALMAS_NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_SECONDS reg read failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rtc_data[0]);
	पंचांग->पंचांग_min = bcd2bin(rtc_data[1]);
	पंचांग->पंचांग_hour = bcd2bin(rtc_data[2]);
	पंचांग->पंचांग_mday = bcd2bin(rtc_data[3]);
	पंचांग->पंचांग_mon = bcd2bin(rtc_data[4]) - 1;
	पंचांग->पंचांग_year = bcd2bin(rtc_data[5]) + 100;

	वापस ret;
पूर्ण

अटल पूर्णांक palmas_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर rtc_data[PALMAS_NUM_TIME_REGS];
	काष्ठा palmas *palmas = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	rtc_data[0] = bin2bcd(पंचांग->पंचांग_sec);
	rtc_data[1] = bin2bcd(पंचांग->पंचांग_min);
	rtc_data[2] = bin2bcd(पंचांग->पंचांग_hour);
	rtc_data[3] = bin2bcd(पंचांग->पंचांग_mday);
	rtc_data[4] = bin2bcd(पंचांग->पंचांग_mon + 1);
	rtc_data[5] = bin2bcd(पंचांग->पंचांग_year - 100);

	/* Stop RTC जबतक updating the RTC समय रेजिस्टरs */
	ret = palmas_update_bits(palmas, PALMAS_RTC_BASE, PALMAS_RTC_CTRL_REG,
		PALMAS_RTC_CTRL_REG_STOP_RTC, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC stop failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = palmas_bulk_ग_लिखो(palmas, PALMAS_RTC_BASE, PALMAS_SECONDS_REG,
		rtc_data, PALMAS_NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_SECONDS reg write failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	/* Start back RTC */
	ret = palmas_update_bits(palmas, PALMAS_RTC_BASE, PALMAS_RTC_CTRL_REG,
		PALMAS_RTC_CTRL_REG_STOP_RTC, PALMAS_RTC_CTRL_REG_STOP_RTC);
	अगर (ret < 0)
		dev_err(dev, "RTC start failed, err = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित enabled)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(dev->parent);
	u8 val;

	val = enabled ? PALMAS_RTC_INTERRUPTS_REG_IT_ALARM : 0;
	वापस palmas_ग_लिखो(palmas, PALMAS_RTC_BASE,
		PALMAS_RTC_INTERRUPTS_REG, val);
पूर्ण

अटल पूर्णांक palmas_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	अचिन्हित अक्षर alarm_data[PALMAS_NUM_TIME_REGS];
	u32 पूर्णांक_val;
	काष्ठा palmas *palmas = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	ret = palmas_bulk_पढ़ो(palmas, PALMAS_RTC_BASE,
			PALMAS_ALARM_SECONDS_REG,
			alarm_data, PALMAS_NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_ALARM_SECONDS read failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	alm->समय.पंचांग_sec = bcd2bin(alarm_data[0]);
	alm->समय.पंचांग_min = bcd2bin(alarm_data[1]);
	alm->समय.पंचांग_hour = bcd2bin(alarm_data[2]);
	alm->समय.पंचांग_mday = bcd2bin(alarm_data[3]);
	alm->समय.पंचांग_mon = bcd2bin(alarm_data[4]) - 1;
	alm->समय.पंचांग_year = bcd2bin(alarm_data[5]) + 100;

	ret = palmas_पढ़ो(palmas, PALMAS_RTC_BASE, PALMAS_RTC_INTERRUPTS_REG,
			&पूर्णांक_val);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_INTERRUPTS reg read failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (पूर्णांक_val & PALMAS_RTC_INTERRUPTS_REG_IT_ALARM)
		alm->enabled = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	अचिन्हित अक्षर alarm_data[PALMAS_NUM_TIME_REGS];
	काष्ठा palmas *palmas = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	ret = palmas_rtc_alarm_irq_enable(dev, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "Disable RTC alarm failed\n");
		वापस ret;
	पूर्ण

	alarm_data[0] = bin2bcd(alm->समय.पंचांग_sec);
	alarm_data[1] = bin2bcd(alm->समय.पंचांग_min);
	alarm_data[2] = bin2bcd(alm->समय.पंचांग_hour);
	alarm_data[3] = bin2bcd(alm->समय.पंचांग_mday);
	alarm_data[4] = bin2bcd(alm->समय.पंचांग_mon + 1);
	alarm_data[5] = bin2bcd(alm->समय.पंचांग_year - 100);

	ret = palmas_bulk_ग_लिखो(palmas, PALMAS_RTC_BASE,
		PALMAS_ALARM_SECONDS_REG, alarm_data, PALMAS_NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "ALARM_SECONDS_REG write failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (alm->enabled)
		ret = palmas_rtc_alarm_irq_enable(dev, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_clear_पूर्णांकerrupts(काष्ठा device *dev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(dev->parent);
	अचिन्हित पूर्णांक rtc_reg;
	पूर्णांक ret;

	ret = palmas_पढ़ो(palmas, PALMAS_RTC_BASE, PALMAS_RTC_STATUS_REG,
				&rtc_reg);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_STATUS read failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = palmas_ग_लिखो(palmas, PALMAS_RTC_BASE, PALMAS_RTC_STATUS_REG,
			rtc_reg);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_STATUS write failed, err = %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t palmas_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा palmas_rtc *palmas_rtc = context;
	काष्ठा device *dev = palmas_rtc->dev;
	पूर्णांक ret;

	ret = palmas_clear_पूर्णांकerrupts(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC interrupt clear failed, err = %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	rtc_update_irq(palmas_rtc->rtc, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops palmas_rtc_ops = अणु
	.पढ़ो_समय	= palmas_rtc_पढ़ो_समय,
	.set_समय	= palmas_rtc_set_समय,
	.पढ़ो_alarm	= palmas_rtc_पढ़ो_alarm,
	.set_alarm	= palmas_rtc_set_alarm,
	.alarm_irq_enable = palmas_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक palmas_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	काष्ठा palmas_rtc *palmas_rtc = शून्य;
	पूर्णांक ret;
	bool enable_bb_अक्षरging = false;
	bool high_bb_अक्षरging = false;

	अगर (pdev->dev.of_node) अणु
		enable_bb_अक्षरging = of_property_पढ़ो_bool(pdev->dev.of_node,
					"ti,backup-battery-chargeable");
		high_bb_अक्षरging = of_property_पढ़ो_bool(pdev->dev.of_node,
					"ti,backup-battery-charge-high-current");
	पूर्ण

	palmas_rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा palmas_rtc),
			GFP_KERNEL);
	अगर (!palmas_rtc)
		वापस -ENOMEM;

	/* Clear pending पूर्णांकerrupts */
	ret = palmas_clear_पूर्णांकerrupts(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "clear RTC int failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	palmas_rtc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, palmas_rtc);

	अगर (enable_bb_अक्षरging) अणु
		अचिन्हित reg = PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG;

		अगर (high_bb_अक्षरging)
			reg = 0;

		ret = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
			PALMAS_BACKUP_BATTERY_CTRL,
			PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG, reg);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"BACKUP_BATTERY_CTRL update failed, %d\n", ret);
			वापस ret;
		पूर्ण

		ret = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
			PALMAS_BACKUP_BATTERY_CTRL,
			PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN,
			PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"BACKUP_BATTERY_CTRL update failed, %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Start RTC */
	ret = palmas_update_bits(palmas, PALMAS_RTC_BASE, PALMAS_RTC_CTRL_REG,
			PALMAS_RTC_CTRL_REG_STOP_RTC,
			PALMAS_RTC_CTRL_REG_STOP_RTC);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "RTC_CTRL write failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	palmas_rtc->irq = platक्रमm_get_irq(pdev, 0);

	device_init_wakeup(&pdev->dev, 1);
	palmas_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
				&palmas_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(palmas_rtc->rtc)) अणु
		ret = PTR_ERR(palmas_rtc->rtc);
		dev_err(&pdev->dev, "RTC register failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, palmas_rtc->irq, शून्य,
			palmas_rtc_पूर्णांकerrupt,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT,
			dev_name(&pdev->dev), palmas_rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "IRQ request failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक palmas_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	palmas_rtc_alarm_irq_enable(&pdev->dev, 0);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक palmas_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा palmas_rtc *palmas_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(palmas_rtc->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा palmas_rtc *palmas_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(palmas_rtc->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(palmas_rtc_pm_ops, palmas_rtc_suspend,
			 palmas_rtc_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_palmas_rtc_match[] = अणु
	अणु .compatible = "ti,palmas-rtc"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_palmas_rtc_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver palmas_rtc_driver = अणु
	.probe		= palmas_rtc_probe,
	.हटाओ		= palmas_rtc_हटाओ,
	.driver		= अणु
		.name	= "palmas-rtc",
		.pm	= &palmas_rtc_pm_ops,
		.of_match_table = of_match_ptr(of_palmas_rtc_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(palmas_rtc_driver);

MODULE_ALIAS("platform:palmas_rtc");
MODULE_DESCRIPTION("TI PALMAS series RTC driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
