<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Power supply driver क्रम the RICOH RN5T618 घातer management chip family
 *
 * Copyright (C) 2020 Andreas Kemnade
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/rn5t618.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा CHG_STATE_ADP_INPUT 0x40
#घोषणा CHG_STATE_USB_INPUT 0x80
#घोषणा CHG_STATE_MASK	0x1f
#घोषणा CHG_STATE_CHG_OFF	0
#घोषणा CHG_STATE_CHG_READY_VADP	1
#घोषणा CHG_STATE_CHG_TRICKLE	2
#घोषणा CHG_STATE_CHG_RAPID	3
#घोषणा CHG_STATE_CHG_COMPLETE	4
#घोषणा CHG_STATE_SUSPEND	5
#घोषणा CHG_STATE_VCHG_OVER_VOL	6
#घोषणा CHG_STATE_BAT_ERROR	7
#घोषणा CHG_STATE_NO_BAT	8
#घोषणा CHG_STATE_BAT_OVER_VOL	9
#घोषणा CHG_STATE_BAT_TEMP_ERR	10
#घोषणा CHG_STATE_DIE_ERR	11
#घोषणा CHG_STATE_DIE_SHUTDOWN	12
#घोषणा CHG_STATE_NO_BAT2	13
#घोषणा CHG_STATE_CHG_READY_VUSB	14

#घोषणा FG_ENABLE 1

काष्ठा rn5t618_घातer_info अणु
	काष्ठा rn5t618 *rn5t618;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *adp;
	पूर्णांक irq;
पूर्ण;

अटल क्रमागत घातer_supply_property rn5t618_usb_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property rn5t618_adp_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;


अटल क्रमागत घातer_supply_property rn5t618_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
पूर्ण;

अटल पूर्णांक rn5t618_battery_पढ़ो_द्विगुनreg(काष्ठा rn5t618_घातer_info *info,
					  u8 reg, u16 *result)
अणु
	पूर्णांक ret, i;
	u8 data[2];
	u16 old, new;

	old = 0;
	/* Prevent races when रेजिस्टरs are changing. */
	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_bulk_पढ़ो(info->rn5t618->regmap,
				       reg, data, माप(data));
		अगर (ret)
			वापस ret;

		new = data[0] << 8;
		new |= data[1];
		अगर (new == old)
			अवरोध;

		old = new;
	पूर्ण

	*result = new;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_decode_status(अचिन्हित पूर्णांक status)
अणु
	चयन (status & CHG_STATE_MASK) अणु
	हाल CHG_STATE_CHG_OFF:
	हाल CHG_STATE_SUSPEND:
	हाल CHG_STATE_VCHG_OVER_VOL:
	हाल CHG_STATE_DIE_SHUTDOWN:
		वापस POWER_SUPPLY_STATUS_DISCHARGING;

	हाल CHG_STATE_CHG_TRICKLE:
	हाल CHG_STATE_CHG_RAPID:
		वापस POWER_SUPPLY_STATUS_CHARGING;

	हाल CHG_STATE_CHG_COMPLETE:
		वापस POWER_SUPPLY_STATUS_FULL;

	शेष:
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण
पूर्ण

अटल पूर्णांक rn5t618_battery_status(काष्ठा rn5t618_घातer_info *info,
				  जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGSTATE, &v);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;

	अगर (v & 0xc0) अणु /* USB or ADP plugged */
		val->पूर्णांकval = rn5t618_decode_status(v);
	पूर्ण अन्यथा
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;

	वापस ret;
पूर्ण

अटल पूर्णांक rn5t618_battery_present(काष्ठा rn5t618_घातer_info *info,
				   जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGSTATE, &v);
	अगर (ret)
		वापस ret;

	v &= CHG_STATE_MASK;
	अगर ((v == CHG_STATE_NO_BAT) || (v == CHG_STATE_NO_BAT2))
		val->पूर्णांकval = 0;
	अन्यथा
		val->पूर्णांकval = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक rn5t618_battery_voltage_now(काष्ठा rn5t618_घातer_info *info,
				       जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_VOLTAGE_1, &res);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = res * 2 * 2500 / 4095 * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_current_now(काष्ठा rn5t618_घातer_info *info,
				       जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_CC_AVEREG1, &res);
	अगर (ret)
		वापस ret;

	/* current is negative when disअक्षरging */
	val->पूर्णांकval = sign_extend32(res, 13) * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_capacity(काष्ठा rn5t618_घातer_info *info,
				    जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->rn5t618->regmap, RN5T618_SOC, &v);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = v;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_temp(काष्ठा rn5t618_घातer_info *info,
				जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_TEMP_1, &res);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = sign_extend32(res, 11) * 10 / 16;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_tte(काष्ठा rn5t618_घातer_info *info,
			       जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_TT_EMPTY_H, &res);
	अगर (ret)
		वापस ret;

	अगर (res == 65535)
		वापस -ENODATA;

	val->पूर्णांकval = res * 60;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_ttf(काष्ठा rn5t618_घातer_info *info,
			       जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_TT_FULL_H, &res);
	अगर (ret)
		वापस ret;

	अगर (res == 65535)
		वापस -ENODATA;

	val->पूर्णांकval = res * 60;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_अक्षरge_full(काष्ठा rn5t618_घातer_info *info,
				       जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_FA_CAP_H, &res);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = res * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_अक्षरge_now(काष्ठा rn5t618_घातer_info *info,
				      जोड़ घातer_supply_propval *val)
अणु
	u16 res;
	पूर्णांक ret;

	ret = rn5t618_battery_पढ़ो_द्विगुनreg(info, RN5T618_RE_CAP_H, &res);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = res * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_battery_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा rn5t618_घातer_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = rn5t618_battery_status(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = rn5t618_battery_present(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = rn5t618_battery_voltage_now(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = rn5t618_battery_current_now(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = rn5t618_battery_capacity(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = rn5t618_battery_temp(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		ret = rn5t618_battery_tte(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
		ret = rn5t618_battery_ttf(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = rn5t618_battery_अक्षरge_full(info, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = rn5t618_battery_अक्षरge_now(info, val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rn5t618_adp_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा rn5t618_घातer_info *info = घातer_supply_get_drvdata(psy);
	अचिन्हित पूर्णांक chgstate;
	bool online;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGSTATE, &chgstate);
	अगर (ret)
		वापस ret;

	online = !!(chgstate & CHG_STATE_ADP_INPUT);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!online) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
		पूर्ण
		val->पूर्णांकval = rn5t618_decode_status(chgstate);
		अगर (val->पूर्णांकval != POWER_SUPPLY_STATUS_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rn5t618_usb_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा rn5t618_घातer_info *info = घातer_supply_get_drvdata(psy);
	अचिन्हित पूर्णांक chgstate;
	bool online;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGSTATE, &chgstate);
	अगर (ret)
		वापस ret;

	online = !!(chgstate & CHG_STATE_USB_INPUT);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!online) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
		पूर्ण
		val->पूर्णांकval = rn5t618_decode_status(chgstate);
		अगर (val->पूर्णांकval != POWER_SUPPLY_STATUS_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc rn5t618_battery_desc = अणु
	.name                   = "rn5t618-battery",
	.type                   = POWER_SUPPLY_TYPE_BATTERY,
	.properties             = rn5t618_battery_props,
	.num_properties         = ARRAY_SIZE(rn5t618_battery_props),
	.get_property           = rn5t618_battery_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc rn5t618_adp_desc = अणु
	.name                   = "rn5t618-adp",
	.type                   = POWER_SUPPLY_TYPE_MAINS,
	.properties             = rn5t618_adp_props,
	.num_properties         = ARRAY_SIZE(rn5t618_adp_props),
	.get_property           = rn5t618_adp_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc rn5t618_usb_desc = अणु
	.name                   = "rn5t618-usb",
	.type                   = POWER_SUPPLY_TYPE_USB,
	.properties             = rn5t618_usb_props,
	.num_properties         = ARRAY_SIZE(rn5t618_usb_props),
	.get_property           = rn5t618_usb_get_property,
पूर्ण;

अटल irqवापस_t rn5t618_अक्षरger_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा rn5t618_घातer_info *info = dev_get_drvdata(dev);

	अचिन्हित पूर्णांक ctrl, stat1, stat2, err;

	regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGERR_IRR, &err);
	regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGCTRL_IRR, &ctrl);
	regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGSTAT_IRR1, &stat1);
	regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CHGSTAT_IRR2, &stat2);

	regmap_ग_लिखो(info->rn5t618->regmap, RN5T618_CHGERR_IRR, 0);
	regmap_ग_लिखो(info->rn5t618->regmap, RN5T618_CHGCTRL_IRR, 0);
	regmap_ग_लिखो(info->rn5t618->regmap, RN5T618_CHGSTAT_IRR1, 0);
	regmap_ग_लिखो(info->rn5t618->regmap, RN5T618_CHGSTAT_IRR2, 0);

	dev_dbg(dev, "chgerr: %x chgctrl: %x chgstat: %x chgstat2: %x\n",
		err, ctrl, stat1, stat2);

	घातer_supply_changed(info->usb);
	घातer_supply_changed(info->adp);
	घातer_supply_changed(info->battery);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rn5t618_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक v;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा rn5t618_घातer_info *info;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->pdev = pdev;
	info->rn5t618 = dev_get_drvdata(pdev->dev.parent);
	info->irq = -1;

	platक्रमm_set_drvdata(pdev, info);

	ret = regmap_पढ़ो(info->rn5t618->regmap, RN5T618_CONTROL, &v);
	अगर (ret)
		वापस ret;

	अगर (!(v & FG_ENABLE)) अणु
		/* E.g. the venकरोr kernels of various Kobo and Tolino Ebook
		 * पढ़ोers disable the fuel gauge on shutकरोwn. If a kernel
		 * without fuel gauge support is booted after that, the fuel
		 * gauge will get decalibrated.
		 */
		dev_info(&pdev->dev, "Fuel gauge not enabled, enabling now\n");
		dev_info(&pdev->dev, "Expect imprecise results\n");
		regmap_update_bits(info->rn5t618->regmap, RN5T618_CONTROL,
				   FG_ENABLE, FG_ENABLE);
	पूर्ण

	psy_cfg.drv_data = info;
	info->battery = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						   &rn5t618_battery_desc,
						   &psy_cfg);
	अगर (IS_ERR(info->battery)) अणु
		ret = PTR_ERR(info->battery);
		dev_err(&pdev->dev, "failed to register battery: %d\n", ret);
		वापस ret;
	पूर्ण

	info->adp = devm_घातer_supply_रेजिस्टर(&pdev->dev,
					       &rn5t618_adp_desc,
					       &psy_cfg);
	अगर (IS_ERR(info->adp)) अणु
		ret = PTR_ERR(info->adp);
		dev_err(&pdev->dev, "failed to register adp: %d\n", ret);
		वापस ret;
	पूर्ण

	info->usb = devm_घातer_supply_रेजिस्टर(&pdev->dev,
					       &rn5t618_usb_desc,
					       &psy_cfg);
	अगर (IS_ERR(info->usb)) अणु
		ret = PTR_ERR(info->usb);
		dev_err(&pdev->dev, "failed to register usb: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (info->rn5t618->irq_data)
		info->irq = regmap_irq_get_virq(info->rn5t618->irq_data,
						RN5T618_IRQ_CHG);

	अगर (info->irq < 0)
		info->irq = -1;
	अन्यथा अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
						rn5t618_अक्षरger_irq,
						IRQF_ONESHOT,
						"rn5t618_power",
						&pdev->dev);

		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "request IRQ:%d fail\n",
				info->irq);
			info->irq = -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rn5t618_घातer_driver = अणु
	.driver = अणु
		.name   = "rn5t618-power",
	पूर्ण,
	.probe = rn5t618_घातer_probe,
पूर्ण;

module_platक्रमm_driver(rn5t618_घातer_driver);
MODULE_ALIAS("platform:rn5t618-power");
MODULE_DESCRIPTION("Power supply driver for RICOH RN5T618");
MODULE_LICENSE("GPL");
