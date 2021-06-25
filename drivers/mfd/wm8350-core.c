<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8350-core.c  --  Device access क्रम Wolfson WM8350
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood, Mark Brown
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/audपन.स>
#समावेश <linux/mfd/wm8350/comparator.h>
#समावेश <linux/mfd/wm8350/gpपन.स>
#समावेश <linux/mfd/wm8350/pmic.h>
#समावेश <linux/mfd/wm8350/rtc.h>
#समावेश <linux/mfd/wm8350/supply.h>
#समावेश <linux/mfd/wm8350/wdt.h>

#घोषणा WM8350_CLOCK_CONTROL_1		0x28
#घोषणा WM8350_AIF_TEST			0x74

/* debug */
#घोषणा WM8350_BUS_DEBUG 0
#अगर WM8350_BUS_DEBUG
#घोषणा dump(regs, src) करो अणु \
	पूर्णांक i_; \
	u16 *src_ = src; \
	prपूर्णांकk(KERN_DEBUG); \
	क्रम (i_ = 0; i_ < regs; i_++) \
		prपूर्णांकk(" 0x%4.4x", *src_++); \
	prपूर्णांकk("\n"); \
पूर्ण जबतक (0);
#अन्यथा
#घोषणा dump(bytes, src)
#पूर्ण_अगर

#घोषणा WM8350_LOCK_DEBUG 0
#अगर WM8350_LOCK_DEBUG
#घोषणा ldbg(क्रमmat, arg...) prपूर्णांकk(क्रमmat, ## arg)
#अन्यथा
#घोषणा ldbg(क्रमmat, arg...)
#पूर्ण_अगर

/*
 * WM8350 Device IO
 */
अटल DEFINE_MUTEX(reg_lock_mutex);

/*
 * Safe पढ़ो, modअगरy, ग_लिखो methods
 */
पूर्णांक wm8350_clear_bits(काष्ठा wm8350 *wm8350, u16 reg, u16 mask)
अणु
	वापस regmap_update_bits(wm8350->regmap, reg, mask, 0);
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_clear_bits);

पूर्णांक wm8350_set_bits(काष्ठा wm8350 *wm8350, u16 reg, u16 mask)
अणु
	वापस regmap_update_bits(wm8350->regmap, reg, mask, mask);
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_set_bits);

u16 wm8350_reg_पढ़ो(काष्ठा wm8350 *wm8350, पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक data;
	पूर्णांक err;

	err = regmap_पढ़ो(wm8350->regmap, reg, &data);
	अगर (err)
		dev_err(wm8350->dev, "read from reg R%d failed\n", reg);

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_reg_पढ़ो);

पूर्णांक wm8350_reg_ग_लिखो(काष्ठा wm8350 *wm8350, पूर्णांक reg, u16 val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(wm8350->regmap, reg, val);

	अगर (ret)
		dev_err(wm8350->dev, "write to reg R%d failed\n", reg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_reg_ग_लिखो);

पूर्णांक wm8350_block_पढ़ो(काष्ठा wm8350 *wm8350, पूर्णांक start_reg, पूर्णांक regs,
		      u16 *dest)
अणु
	पूर्णांक err = 0;

	err = regmap_bulk_पढ़ो(wm8350->regmap, start_reg, dest, regs);
	अगर (err)
		dev_err(wm8350->dev, "block read starting from R%d failed\n",
			start_reg);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_block_पढ़ो);

पूर्णांक wm8350_block_ग_लिखो(काष्ठा wm8350 *wm8350, पूर्णांक start_reg, पूर्णांक regs,
		       u16 *src)
अणु
	पूर्णांक ret = 0;

	ret = regmap_bulk_ग_लिखो(wm8350->regmap, start_reg, src, regs);
	अगर (ret)
		dev_err(wm8350->dev, "block write starting at R%d failed\n",
			start_reg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_block_ग_लिखो);

/**
 * wm8350_reg_lock()
 *
 * The WM8350 has a hardware lock which can be used to prevent ग_लिखोs to
 * some रेजिस्टरs (generally those which can cause particularly serious
 * problems अगर misused).  This function enables that lock.
 *
 * @wm8350: poपूर्णांकer to local driver data काष्ठाure
 */
पूर्णांक wm8350_reg_lock(काष्ठा wm8350 *wm8350)
अणु
	पूर्णांक ret;

	mutex_lock(&reg_lock_mutex);

	ldbg(__func__);

	ret = wm8350_reg_ग_लिखो(wm8350, WM8350_SECURITY, WM8350_LOCK_KEY);
	अगर (ret)
		dev_err(wm8350->dev, "lock failed\n");

	wm8350->unlocked = false;

	mutex_unlock(&reg_lock_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_reg_lock);

/**
 * wm8350_reg_unlock()
 *
 * The WM8350 has a hardware lock which can be used to prevent ग_लिखोs to
 * some रेजिस्टरs (generally those which can cause particularly serious
 * problems अगर misused).  This function disables that lock so updates
 * can be perक्रमmed.  For maximum safety this should be करोne only when
 * required.
 *
 * @wm8350: poपूर्णांकer to local driver data काष्ठाure
 */
पूर्णांक wm8350_reg_unlock(काष्ठा wm8350 *wm8350)
अणु
	पूर्णांक ret;

	mutex_lock(&reg_lock_mutex);

	ldbg(__func__);

	ret = wm8350_reg_ग_लिखो(wm8350, WM8350_SECURITY, WM8350_UNLOCK_KEY);
	अगर (ret)
		dev_err(wm8350->dev, "unlock failed\n");

	wm8350->unlocked = true;

	mutex_unlock(&reg_lock_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_reg_unlock);

पूर्णांक wm8350_पढ़ो_auxadc(काष्ठा wm8350 *wm8350, पूर्णांक channel, पूर्णांक scale, पूर्णांक vref)
अणु
	u16 reg, result = 0;

	अगर (channel < WM8350_AUXADC_AUX1 || channel > WM8350_AUXADC_TEMP)
		वापस -EINVAL;
	अगर (channel >= WM8350_AUXADC_USB && channel <= WM8350_AUXADC_TEMP
	    && (scale != 0 || vref != 0))
		वापस -EINVAL;

	mutex_lock(&wm8350->auxadc_mutex);

	/* Turn on the ADC */
	reg = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_5);
	wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_5, reg | WM8350_AUXADC_ENA);

	अगर (scale || vref) अणु
		reg = scale << 13;
		reg |= vref << 12;
		wm8350_reg_ग_लिखो(wm8350, WM8350_AUX1_READBACK + channel, reg);
	पूर्ण

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_DIGITISER_CONTROL_1);
	reg |= 1 << channel | WM8350_AUXADC_POLL;
	wm8350_reg_ग_लिखो(wm8350, WM8350_DIGITISER_CONTROL_1, reg);

	/* If a late IRQ left the completion संकेतled then consume
	 * the completion. */
	try_रुको_क्रम_completion(&wm8350->auxadc_करोne);

	/* We ignore the result of the completion and just check क्रम a
	 * conversion result, allowing us to soldier on अगर the IRQ
	 * infraकाष्ठाure is not set up क्रम the chip. */
	रुको_क्रम_completion_समयout(&wm8350->auxadc_करोne, msecs_to_jअगरfies(5));

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_DIGITISER_CONTROL_1);
	अगर (reg & WM8350_AUXADC_POLL)
		dev_err(wm8350->dev, "adc chn %d read timeout\n", channel);
	अन्यथा
		result = wm8350_reg_पढ़ो(wm8350,
					 WM8350_AUX1_READBACK + channel);

	/* Turn off the ADC */
	reg = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_5);
	wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_5,
			 reg & ~WM8350_AUXADC_ENA);

	mutex_unlock(&wm8350->auxadc_mutex);

	वापस result & WM8350_AUXADC_DATA1_MASK;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_पढ़ो_auxadc);

अटल irqवापस_t wm8350_auxadc_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा wm8350 *wm8350 = irq_data;

	complete(&wm8350->auxadc_करोne);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Register a client device.  This is non-fatal since there is no need to
 * fail the entire device init due to a single platक्रमm device failing.
 */
अटल व्योम wm8350_client_dev_रेजिस्टर(काष्ठा wm8350 *wm8350,
				       स्थिर अक्षर *name,
				       काष्ठा platक्रमm_device **pdev)
अणु
	पूर्णांक ret;

	*pdev = platक्रमm_device_alloc(name, -1);
	अगर (*pdev == शून्य) अणु
		dev_err(wm8350->dev, "Failed to allocate %s\n", name);
		वापस;
	पूर्ण

	(*pdev)->dev.parent = wm8350->dev;
	platक्रमm_set_drvdata(*pdev, wm8350);
	ret = platक्रमm_device_add(*pdev);
	अगर (ret != 0) अणु
		dev_err(wm8350->dev, "Failed to register %s: %d\n", name, ret);
		platक्रमm_device_put(*pdev);
		*pdev = शून्य;
	पूर्ण
पूर्ण

पूर्णांक wm8350_device_init(काष्ठा wm8350 *wm8350, पूर्णांक irq,
		       काष्ठा wm8350_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक id1, id2, mask_rev;
	अचिन्हित पूर्णांक cust_id, mode, chip_rev;

	dev_set_drvdata(wm8350->dev, wm8350);

	/* get WM8350 revision and config mode */
	ret = regmap_पढ़ो(wm8350->regmap, WM8350_RESET_ID, &id1);
	अगर (ret != 0) अणु
		dev_err(wm8350->dev, "Failed to read ID: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(wm8350->regmap, WM8350_ID, &id2);
	अगर (ret != 0) अणु
		dev_err(wm8350->dev, "Failed to read ID: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(wm8350->regmap, WM8350_REVISION, &mask_rev);
	अगर (ret != 0) अणु
		dev_err(wm8350->dev, "Failed to read revision: %d\n", ret);
		जाओ err;
	पूर्ण

	अगर (id1 != 0x6143) अणु
		dev_err(wm8350->dev,
			"Device with ID %x is not a WM8350\n", id1);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	mode = (id2 & WM8350_CONF_STS_MASK) >> 10;
	cust_id = id2 & WM8350_CUST_ID_MASK;
	chip_rev = (id2 & WM8350_CHIP_REV_MASK) >> 12;
	dev_info(wm8350->dev,
		 "CONF_STS %d, CUST_ID %d, MASK_REV %d, CHIP_REV %d\n",
		 mode, cust_id, mask_rev, chip_rev);

	अगर (cust_id != 0) अणु
		dev_err(wm8350->dev, "Unsupported CUST_ID\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	चयन (mask_rev) अणु
	हाल 0:
		wm8350->pmic.max_dcdc = WM8350_DCDC_6;
		wm8350->pmic.max_isink = WM8350_ISINK_B;

		चयन (chip_rev) अणु
		हाल WM8350_REV_E:
			dev_info(wm8350->dev, "WM8350 Rev E\n");
			अवरोध;
		हाल WM8350_REV_F:
			dev_info(wm8350->dev, "WM8350 Rev F\n");
			अवरोध;
		हाल WM8350_REV_G:
			dev_info(wm8350->dev, "WM8350 Rev G\n");
			wm8350->घातer.rev_g_coeff = 1;
			अवरोध;
		हाल WM8350_REV_H:
			dev_info(wm8350->dev, "WM8350 Rev H\n");
			wm8350->घातer.rev_g_coeff = 1;
			अवरोध;
		शेष:
			/* For safety we refuse to run on unknown hardware */
			dev_err(wm8350->dev, "Unknown WM8350 CHIP_REV\n");
			ret = -ENODEV;
			जाओ err;
		पूर्ण
		अवरोध;

	हाल 1:
		wm8350->pmic.max_dcdc = WM8350_DCDC_4;
		wm8350->pmic.max_isink = WM8350_ISINK_A;

		चयन (chip_rev) अणु
		हाल 0:
			dev_info(wm8350->dev, "WM8351 Rev A\n");
			wm8350->घातer.rev_g_coeff = 1;
			अवरोध;

		हाल 1:
			dev_info(wm8350->dev, "WM8351 Rev B\n");
			wm8350->घातer.rev_g_coeff = 1;
			अवरोध;

		शेष:
			dev_err(wm8350->dev, "Unknown WM8351 CHIP_REV\n");
			ret = -ENODEV;
			जाओ err;
		पूर्ण
		अवरोध;

	हाल 2:
		wm8350->pmic.max_dcdc = WM8350_DCDC_6;
		wm8350->pmic.max_isink = WM8350_ISINK_B;

		चयन (chip_rev) अणु
		हाल 0:
			dev_info(wm8350->dev, "WM8352 Rev A\n");
			wm8350->घातer.rev_g_coeff = 1;
			अवरोध;

		शेष:
			dev_err(wm8350->dev, "Unknown WM8352 CHIP_REV\n");
			ret = -ENODEV;
			जाओ err;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(wm8350->dev, "Unknown MASK_REV\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	mutex_init(&wm8350->auxadc_mutex);
	init_completion(&wm8350->auxadc_करोne);

	ret = wm8350_irq_init(wm8350, irq, pdata);
	अगर (ret < 0)
		जाओ err;

	अगर (wm8350->irq_base) अणु
		ret = request_thपढ़ोed_irq(wm8350->irq_base +
					   WM8350_IRQ_AUXADC_DATARDY,
					   शून्य, wm8350_auxadc_irq,
					   IRQF_ONESHOT,
					   "auxadc", wm8350);
		अगर (ret < 0)
			dev_warn(wm8350->dev,
				 "Failed to request AUXADC IRQ: %d\n", ret);
	पूर्ण

	अगर (pdata && pdata->init) अणु
		ret = pdata->init(wm8350);
		अगर (ret != 0) अणु
			dev_err(wm8350->dev, "Platform init() failed: %d\n",
				ret);
			जाओ err_irq;
		पूर्ण
	पूर्ण

	wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0x0);

	wm8350_client_dev_रेजिस्टर(wm8350, "wm8350-codec",
				   &(wm8350->codec.pdev));
	wm8350_client_dev_रेजिस्टर(wm8350, "wm8350-gpio",
				   &(wm8350->gpio.pdev));
	wm8350_client_dev_रेजिस्टर(wm8350, "wm8350-hwmon",
				   &(wm8350->hwmon.pdev));
	wm8350_client_dev_रेजिस्टर(wm8350, "wm8350-power",
				   &(wm8350->घातer.pdev));
	wm8350_client_dev_रेजिस्टर(wm8350, "wm8350-rtc", &(wm8350->rtc.pdev));
	wm8350_client_dev_रेजिस्टर(wm8350, "wm8350-wdt", &(wm8350->wdt.pdev));

	वापस 0;

err_irq:
	wm8350_irq_निकास(wm8350);
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_device_init);
