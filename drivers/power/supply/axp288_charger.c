<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * axp288_अक्षरger.c - X-घातer AXP288 PMIC Charger driver
 *
 * Copyright (C) 2016-2017 Hans de Goede <hdegoede@redhat.com>
 * Copyright (C) 2014 Intel Corporation
 * Author: Ramakrishna Pallala <ramakrishna.pallala@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/extcon.h>
#समावेश <linux/dmi.h>

#घोषणा PS_STAT_VBUS_TRIGGER		BIT(0)
#घोषणा PS_STAT_BAT_CHRG_सूची		BIT(2)
#घोषणा PS_STAT_VBAT_ABOVE_VHOLD	BIT(3)
#घोषणा PS_STAT_VBUS_VALID		BIT(4)
#घोषणा PS_STAT_VBUS_PRESENT		BIT(5)

#घोषणा CHRG_STAT_BAT_SAFE_MODE		BIT(3)
#घोषणा CHRG_STAT_BAT_VALID		BIT(4)
#घोषणा CHRG_STAT_BAT_PRESENT		BIT(5)
#घोषणा CHRG_STAT_CHARGING		BIT(6)
#घोषणा CHRG_STAT_PMIC_OTP		BIT(7)

#घोषणा VBUS_ISPOUT_CUR_LIM_MASK	0x03
#घोषणा VBUS_ISPOUT_CUR_LIM_BIT_POS	0
#घोषणा VBUS_ISPOUT_CUR_LIM_900MA	0x0	/* 900mA */
#घोषणा VBUS_ISPOUT_CUR_LIM_1500MA	0x1	/* 1500mA */
#घोषणा VBUS_ISPOUT_CUR_LIM_2000MA	0x2	/* 2000mA */
#घोषणा VBUS_ISPOUT_CUR_NO_LIM		0x3	/* 2500mA */
#घोषणा VBUS_ISPOUT_VHOLD_SET_MASK	0x31
#घोषणा VBUS_ISPOUT_VHOLD_SET_BIT_POS	0x3
#घोषणा VBUS_ISPOUT_VHOLD_SET_OFFSET	4000	/* 4000mV */
#घोषणा VBUS_ISPOUT_VHOLD_SET_LSB_RES	100	/* 100mV */
#घोषणा VBUS_ISPOUT_VHOLD_SET_4300MV	0x3	/* 4300mV */
#घोषणा VBUS_ISPOUT_VBUS_PATH_DIS	BIT(7)

#घोषणा CHRG_CCCV_CC_MASK		0xf		/* 4 bits */
#घोषणा CHRG_CCCV_CC_BIT_POS		0
#घोषणा CHRG_CCCV_CC_OFFSET		200		/* 200mA */
#घोषणा CHRG_CCCV_CC_LSB_RES		200		/* 200mA */
#घोषणा CHRG_CCCV_ITERM_20P		BIT(4)		/* 20% of CC */
#घोषणा CHRG_CCCV_CV_MASK		0x60		/* 2 bits */
#घोषणा CHRG_CCCV_CV_BIT_POS		5
#घोषणा CHRG_CCCV_CV_4100MV		0x0		/* 4.10V */
#घोषणा CHRG_CCCV_CV_4150MV		0x1		/* 4.15V */
#घोषणा CHRG_CCCV_CV_4200MV		0x2		/* 4.20V */
#घोषणा CHRG_CCCV_CV_4350MV		0x3		/* 4.35V */
#घोषणा CHRG_CCCV_CHG_EN		BIT(7)

#घोषणा CNTL2_CC_TIMEOUT_MASK		0x3	/* 2 bits */
#घोषणा CNTL2_CC_TIMEOUT_OFFSET		6	/* 6 Hrs */
#घोषणा CNTL2_CC_TIMEOUT_LSB_RES	2	/* 2 Hrs */
#घोषणा CNTL2_CC_TIMEOUT_12HRS		0x3	/* 12 Hrs */
#घोषणा CNTL2_CHGLED_TYPEB		BIT(4)
#घोषणा CNTL2_CHG_OUT_TURNON		BIT(5)
#घोषणा CNTL2_PC_TIMEOUT_MASK		0xC0
#घोषणा CNTL2_PC_TIMEOUT_OFFSET		40	/* 40 mins */
#घोषणा CNTL2_PC_TIMEOUT_LSB_RES	10	/* 10 mins */
#घोषणा CNTL2_PC_TIMEOUT_70MINS		0x3

#घोषणा CHRG_ILIM_TEMP_LOOP_EN		BIT(3)
#घोषणा CHRG_VBUS_ILIM_MASK		0xf0
#घोषणा CHRG_VBUS_ILIM_BIT_POS		4
#घोषणा CHRG_VBUS_ILIM_100MA		0x0	/* 100mA */
#घोषणा CHRG_VBUS_ILIM_500MA		0x1	/* 500mA */
#घोषणा CHRG_VBUS_ILIM_900MA		0x2	/* 900mA */
#घोषणा CHRG_VBUS_ILIM_1500MA		0x3	/* 1500mA */
#घोषणा CHRG_VBUS_ILIM_2000MA		0x4	/* 2000mA */
#घोषणा CHRG_VBUS_ILIM_2500MA		0x5	/* 2500mA */
#घोषणा CHRG_VBUS_ILIM_3000MA		0x6	/* 3000mA */
#घोषणा CHRG_VBUS_ILIM_3500MA		0x7	/* 3500mA */
#घोषणा CHRG_VBUS_ILIM_4000MA		0x8	/* 4000mA */

#घोषणा CHRG_VLTFC_0C			0xA5	/* 0 DegC */
#घोषणा CHRG_VHTFC_45C			0x1F	/* 45 DegC */

#घोषणा FG_CNTL_OCV_ADJ_EN		BIT(3)

#घोषणा CV_4100MV			4100	/* 4100mV */
#घोषणा CV_4150MV			4150	/* 4150mV */
#घोषणा CV_4200MV			4200	/* 4200mV */
#घोषणा CV_4350MV			4350	/* 4350mV */

#घोषणा AXP288_EXTCON_DEV_NAME		"axp288_extcon"
#घोषणा USB_HOST_EXTCON_HID		"INT3496"
#घोषणा USB_HOST_EXTCON_NAME		"INT3496:00"

क्रमागत अणु
	VBUS_OV_IRQ = 0,
	CHARGE_DONE_IRQ,
	CHARGE_CHARGING_IRQ,
	BAT_SAFE_QUIT_IRQ,
	BAT_SAFE_ENTER_IRQ,
	QCBTU_IRQ,
	CBTU_IRQ,
	QCBTO_IRQ,
	CBTO_IRQ,
	CHRG_INTR_END,
पूर्ण;

काष्ठा axp288_chrg_info अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *regmap_irqc;
	पूर्णांक irq[CHRG_INTR_END];
	काष्ठा घातer_supply *psy_usb;

	/* OTG/Host mode */
	काष्ठा अणु
		काष्ठा work_काष्ठा work;
		काष्ठा extcon_dev *cable;
		काष्ठा notअगरier_block id_nb;
		bool id_लघु;
	पूर्ण otg;

	/* SDP/CDP/DCP USB अक्षरging cable notअगरications */
	काष्ठा अणु
		काष्ठा extcon_dev *edev;
		काष्ठा notअगरier_block nb;
		काष्ठा work_काष्ठा work;
	पूर्ण cable;

	पूर्णांक cc;
	पूर्णांक cv;
	पूर्णांक max_cc;
	पूर्णांक max_cv;
पूर्ण;

अटल अंतरभूत पूर्णांक axp288_अक्षरger_set_cc(काष्ठा axp288_chrg_info *info, पूर्णांक cc)
अणु
	u8 reg_val;
	पूर्णांक ret;

	अगर (cc < CHRG_CCCV_CC_OFFSET)
		cc = CHRG_CCCV_CC_OFFSET;
	अन्यथा अगर (cc > info->max_cc)
		cc = info->max_cc;

	reg_val = (cc - CHRG_CCCV_CC_OFFSET) / CHRG_CCCV_CC_LSB_RES;
	cc = (reg_val * CHRG_CCCV_CC_LSB_RES) + CHRG_CCCV_CC_OFFSET;
	reg_val = reg_val << CHRG_CCCV_CC_BIT_POS;

	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CC_MASK, reg_val);
	अगर (ret >= 0)
		info->cc = cc;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक axp288_अक्षरger_set_cv(काष्ठा axp288_chrg_info *info, पूर्णांक cv)
अणु
	u8 reg_val;
	पूर्णांक ret;

	अगर (cv <= CV_4100MV) अणु
		reg_val = CHRG_CCCV_CV_4100MV;
		cv = CV_4100MV;
	पूर्ण अन्यथा अगर (cv <= CV_4150MV) अणु
		reg_val = CHRG_CCCV_CV_4150MV;
		cv = CV_4150MV;
	पूर्ण अन्यथा अगर (cv <= CV_4200MV) अणु
		reg_val = CHRG_CCCV_CV_4200MV;
		cv = CV_4200MV;
	पूर्ण अन्यथा अणु
		reg_val = CHRG_CCCV_CV_4350MV;
		cv = CV_4350MV;
	पूर्ण

	reg_val = reg_val << CHRG_CCCV_CV_BIT_POS;

	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CV_MASK, reg_val);

	अगर (ret >= 0)
		info->cv = cv;

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_get_vbus_inlmt(काष्ठा axp288_chrg_info *info)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, AXP20X_CHRG_BAK_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	val >>= CHRG_VBUS_ILIM_BIT_POS;
	चयन (val) अणु
	हाल CHRG_VBUS_ILIM_100MA:
		वापस 100000;
	हाल CHRG_VBUS_ILIM_500MA:
		वापस 500000;
	हाल CHRG_VBUS_ILIM_900MA:
		वापस 900000;
	हाल CHRG_VBUS_ILIM_1500MA:
		वापस 1500000;
	हाल CHRG_VBUS_ILIM_2000MA:
		वापस 2000000;
	हाल CHRG_VBUS_ILIM_2500MA:
		वापस 2500000;
	हाल CHRG_VBUS_ILIM_3000MA:
		वापस 3000000;
	हाल CHRG_VBUS_ILIM_3500MA:
		वापस 3500000;
	शेष:
		/* All b1xxx values map to 4000 mA */
		वापस 4000000;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक axp288_अक्षरger_set_vbus_inlmt(काष्ठा axp288_chrg_info *info,
					   पूर्णांक inlmt)
अणु
	पूर्णांक ret;
	u8 reg_val;

	अगर (inlmt >= 4000000)
		reg_val = CHRG_VBUS_ILIM_4000MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 3500000)
		reg_val = CHRG_VBUS_ILIM_3500MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 3000000)
		reg_val = CHRG_VBUS_ILIM_3000MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 2500000)
		reg_val = CHRG_VBUS_ILIM_2500MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 2000000)
		reg_val = CHRG_VBUS_ILIM_2000MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 1500000)
		reg_val = CHRG_VBUS_ILIM_1500MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 900000)
		reg_val = CHRG_VBUS_ILIM_900MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा अगर (inlmt >= 500000)
		reg_val = CHRG_VBUS_ILIM_500MA << CHRG_VBUS_ILIM_BIT_POS;
	अन्यथा
		reg_val = CHRG_VBUS_ILIM_100MA << CHRG_VBUS_ILIM_BIT_POS;

	ret = regmap_update_bits(info->regmap, AXP20X_CHRG_BAK_CTRL,
				 CHRG_VBUS_ILIM_MASK, reg_val);
	अगर (ret < 0)
		dev_err(&info->pdev->dev, "charger BAK control %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_vbus_path_select(काष्ठा axp288_chrg_info *info,
								bool enable)
अणु
	पूर्णांक ret;

	अगर (enable)
		ret = regmap_update_bits(info->regmap, AXP20X_VBUS_IPSOUT_MGMT,
					VBUS_ISPOUT_VBUS_PATH_DIS, 0);
	अन्यथा
		ret = regmap_update_bits(info->regmap, AXP20X_VBUS_IPSOUT_MGMT,
			VBUS_ISPOUT_VBUS_PATH_DIS, VBUS_ISPOUT_VBUS_PATH_DIS);

	अगर (ret < 0)
		dev_err(&info->pdev->dev, "axp288 vbus path select %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_enable_अक्षरger(काष्ठा axp288_chrg_info *info,
								bool enable)
अणु
	पूर्णांक ret;

	अगर (enable)
		ret = regmap_update_bits(info->regmap, AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CHG_EN, CHRG_CCCV_CHG_EN);
	अन्यथा
		ret = regmap_update_bits(info->regmap, AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CHG_EN, 0);
	अगर (ret < 0)
		dev_err(&info->pdev->dev, "axp288 enable charger %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_is_present(काष्ठा axp288_chrg_info *info)
अणु
	पूर्णांक ret, present = 0;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(info->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & PS_STAT_VBUS_PRESENT)
		present = 1;
	वापस present;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_is_online(काष्ठा axp288_chrg_info *info)
अणु
	पूर्णांक ret, online = 0;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(info->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & PS_STAT_VBUS_VALID)
		online = 1;
	वापस online;
पूर्ण

अटल पूर्णांक axp288_get_अक्षरger_health(काष्ठा axp288_chrg_info *info)
अणु
	पूर्णांक ret, pwr_stat, chrg_stat;
	पूर्णांक health = POWER_SUPPLY_HEALTH_UNKNOWN;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(info->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	अगर ((ret < 0) || !(val & PS_STAT_VBUS_PRESENT))
		जाओ health_पढ़ो_fail;
	अन्यथा
		pwr_stat = val;

	ret = regmap_पढ़ो(info->regmap, AXP20X_PWR_OP_MODE, &val);
	अगर (ret < 0)
		जाओ health_पढ़ो_fail;
	अन्यथा
		chrg_stat = val;

	अगर (!(pwr_stat & PS_STAT_VBUS_VALID))
		health = POWER_SUPPLY_HEALTH_DEAD;
	अन्यथा अगर (chrg_stat & CHRG_STAT_PMIC_OTP)
		health = POWER_SUPPLY_HEALTH_OVERHEAT;
	अन्यथा अगर (chrg_stat & CHRG_STAT_BAT_SAFE_MODE)
		health = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
	अन्यथा
		health = POWER_SUPPLY_HEALTH_GOOD;

health_पढ़ो_fail:
	वापस health;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_usb_set_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp288_chrg_info *info = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;
	पूर्णांक scaled_val;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		scaled_val = min(val->पूर्णांकval, info->max_cc);
		scaled_val = DIV_ROUND_CLOSEST(scaled_val, 1000);
		ret = axp288_अक्षरger_set_cc(info, scaled_val);
		अगर (ret < 0)
			dev_warn(&info->pdev->dev, "set charge current failed\n");
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		scaled_val = min(val->पूर्णांकval, info->max_cv);
		scaled_val = DIV_ROUND_CLOSEST(scaled_val, 1000);
		ret = axp288_अक्षरger_set_cv(info, scaled_val);
		अगर (ret < 0)
			dev_warn(&info->pdev->dev, "set charge voltage failed\n");
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = axp288_अक्षरger_set_vbus_inlmt(info, val->पूर्णांकval);
		अगर (ret < 0)
			dev_warn(&info->pdev->dev, "set input current limit failed\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_usb_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp288_chrg_info *info = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		/* Check क्रम OTG हाल first */
		अगर (info->otg.id_लघु) अणु
			val->पूर्णांकval = 0;
			अवरोध;
		पूर्ण
		ret = axp288_अक्षरger_is_present(info);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		/* Check क्रम OTG हाल first */
		अगर (info->otg.id_लघु) अणु
			val->पूर्णांकval = 0;
			अवरोध;
		पूर्ण
		ret = axp288_अक्षरger_is_online(info);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = axp288_get_अक्षरger_health(info);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		val->पूर्णांकval = info->cc * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = info->max_cc * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->पूर्णांकval = info->cv * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->पूर्णांकval = info->max_cv * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = axp288_अक्षरger_get_vbus_inlmt(info);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp288_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = 1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property axp288_usb_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc axp288_अक्षरger_desc = अणु
	.name			= "axp288_charger",
	.type			= POWER_SUPPLY_TYPE_USB,
	.properties		= axp288_usb_props,
	.num_properties		= ARRAY_SIZE(axp288_usb_props),
	.get_property		= axp288_अक्षरger_usb_get_property,
	.set_property		= axp288_अक्षरger_usb_set_property,
	.property_is_ग_लिखोable	= axp288_अक्षरger_property_is_ग_लिखोable,
पूर्ण;

अटल irqवापस_t axp288_अक्षरger_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा axp288_chrg_info *info = dev;
	पूर्णांक i;

	क्रम (i = 0; i < CHRG_INTR_END; i++) अणु
		अगर (info->irq[i] == irq)
			अवरोध;
	पूर्ण

	अगर (i >= CHRG_INTR_END) अणु
		dev_warn(&info->pdev->dev, "spurious interrupt!!\n");
		वापस IRQ_NONE;
	पूर्ण

	चयन (i) अणु
	हाल VBUS_OV_IRQ:
		dev_dbg(&info->pdev->dev, "VBUS Over Voltage INTR\n");
		अवरोध;
	हाल CHARGE_DONE_IRQ:
		dev_dbg(&info->pdev->dev, "Charging Done INTR\n");
		अवरोध;
	हाल CHARGE_CHARGING_IRQ:
		dev_dbg(&info->pdev->dev, "Start Charging IRQ\n");
		अवरोध;
	हाल BAT_SAFE_QUIT_IRQ:
		dev_dbg(&info->pdev->dev,
			"Quit Safe Mode(restart timer) Charging IRQ\n");
		अवरोध;
	हाल BAT_SAFE_ENTER_IRQ:
		dev_dbg(&info->pdev->dev,
			"Enter Safe Mode(timer expire) Charging IRQ\n");
		अवरोध;
	हाल QCBTU_IRQ:
		dev_dbg(&info->pdev->dev,
			"Quit Battery Under Temperature(CHRG) INTR\n");
		अवरोध;
	हाल CBTU_IRQ:
		dev_dbg(&info->pdev->dev,
			"Hit Battery Under Temperature(CHRG) INTR\n");
		अवरोध;
	हाल QCBTO_IRQ:
		dev_dbg(&info->pdev->dev,
			"Quit Battery Over Temperature(CHRG) INTR\n");
		अवरोध;
	हाल CBTO_IRQ:
		dev_dbg(&info->pdev->dev,
			"Hit Battery Over Temperature(CHRG) INTR\n");
		अवरोध;
	शेष:
		dev_warn(&info->pdev->dev, "Spurious Interrupt!!!\n");
		जाओ out;
	पूर्ण

	घातer_supply_changed(info->psy_usb);
out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * The HP Pavilion x2 10 series comes in a number of variants:
 * Bay Trail SoC    + AXP288 PMIC, Micro-USB, DMI_BOARD_NAME: "8021"
 * Bay Trail SoC    + AXP288 PMIC, Type-C,    DMI_BOARD_NAME: "815D"
 * Cherry Trail SoC + AXP288 PMIC, Type-C,    DMI_BOARD_NAME: "813E"
 * Cherry Trail SoC + TI PMIC,     Type-C,    DMI_BOARD_NAME: "827C" or "82F4"
 *
 * The variants with the AXP288 + Type-C connector are all kinds of special:
 *
 * 1. They use a Type-C connector which the AXP288 करोes not support, so when
 * using a Type-C अक्षरger it is not recognized. Unlike most AXP288 devices,
 * this model actually has mostly working ACPI AC / Battery code, the ACPI code
 * "solves" this by simply setting the input_current_limit to 3A.
 * There are still some issues with the ACPI code, so we use this native driver,
 * and to solve the अक्षरging not working (500mA is not enough) issue we hardcode
 * the 3A input_current_limit like the ACPI code करोes.
 *
 * 2. If no अक्षरger is connected the machine boots with the vbus-path disabled.
 * Normally this is करोne when a 5V boost converter is active to aव्योम the PMIC
 * trying to अक्षरge from the 5V boost converter's output. This is करोne when
 * an OTG host cable is inserted and the ID pin on the micro-B receptacle is
 * pulled low and the ID pin has an ACPI event handler associated with it
 * which re-enables the vbus-path when the ID pin is pulled high when the
 * OTG host cable is हटाओd. The Type-C connector has no ID pin, there is
 * no ID pin handler and there appears to be no 5V boost converter, so we
 * end up not अक्षरging because the vbus-path is disabled, until we unplug
 * the अक्षरger which स्वतःmatically clears the vbus-path disable bit and then
 * on the second plug-in of the adapter we start अक्षरging. To solve the not
 * अक्षरging on first अक्षरger plugin we unconditionally enable the vbus-path at
 * probe on this model, which is safe since there is no 5V boost converter.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id axp288_hp_x2_dmi_ids[] = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "HP Pavilion x2 Detachable"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "815D"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "HP Pavilion x2 Detachable"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "813E"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

अटल व्योम axp288_अक्षरger_extcon_evt_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा axp288_chrg_info *info =
	    container_of(work, काष्ठा axp288_chrg_info, cable.work);
	पूर्णांक ret, current_limit;
	काष्ठा extcon_dev *edev = info->cable.edev;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(info->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "Error reading status (%d)\n", ret);
		वापस;
	पूर्ण

	/* Offline? Disable अक्षरging and bail */
	अगर (!(val & PS_STAT_VBUS_VALID)) अणु
		dev_dbg(&info->pdev->dev, "USB charger disconnected\n");
		axp288_अक्षरger_enable_अक्षरger(info, false);
		घातer_supply_changed(info->psy_usb);
		वापस;
	पूर्ण

	/* Determine cable/अक्षरger type */
	अगर (dmi_check_प्रणाली(axp288_hp_x2_dmi_ids)) अणु
		/* See comment above axp288_hp_x2_dmi_ids declaration */
		dev_dbg(&info->pdev->dev, "HP X2 with Type-C, setting inlmt to 3A\n");
		current_limit = 3000000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_SDP) > 0) अणु
		dev_dbg(&info->pdev->dev, "USB SDP charger is connected\n");
		current_limit = 500000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_CDP) > 0) अणु
		dev_dbg(&info->pdev->dev, "USB CDP charger is connected\n");
		current_limit = 1500000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_DCP) > 0) अणु
		dev_dbg(&info->pdev->dev, "USB DCP charger is connected\n");
		current_limit = 2000000;
	पूर्ण अन्यथा अणु
		/* Charger type detection still in progress, bail. */
		वापस;
	पूर्ण

	/* Set vbus current limit first, then enable अक्षरger */
	ret = axp288_अक्षरger_set_vbus_inlmt(info, current_limit);
	अगर (ret == 0)
		axp288_अक्षरger_enable_अक्षरger(info, true);
	अन्यथा
		dev_err(&info->pdev->dev,
			"error setting current limit (%d)\n", ret);

	घातer_supply_changed(info->psy_usb);
पूर्ण

अटल पूर्णांक axp288_अक्षरger_handle_cable_evt(काष्ठा notअगरier_block *nb,
					   अचिन्हित दीर्घ event, व्योम *param)
अणु
	काष्ठा axp288_chrg_info *info =
		container_of(nb, काष्ठा axp288_chrg_info, cable.nb);
	schedule_work(&info->cable.work);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम axp288_अक्षरger_otg_evt_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा axp288_chrg_info *info =
	    container_of(work, काष्ठा axp288_chrg_info, otg.work);
	काष्ठा extcon_dev *edev = info->otg.cable;
	पूर्णांक ret, usb_host = extcon_get_state(edev, EXTCON_USB_HOST);

	dev_dbg(&info->pdev->dev, "external connector USB-Host is %s\n",
				usb_host ? "attached" : "detached");

	/*
	 * Set usb_id_लघु flag to aव्योम running अक्षरger detection logic
	 * in हाल usb host.
	 */
	info->otg.id_लघु = usb_host;

	/* Disable VBUS path beक्रमe enabling the 5V boost */
	ret = axp288_अक्षरger_vbus_path_select(info, !info->otg.id_लघु);
	अगर (ret < 0)
		dev_warn(&info->pdev->dev, "vbus path disable failed\n");
पूर्ण

अटल पूर्णांक axp288_अक्षरger_handle_otg_evt(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *param)
अणु
	काष्ठा axp288_chrg_info *info =
	    container_of(nb, काष्ठा axp288_chrg_info, otg.id_nb);

	schedule_work(&info->otg.work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक अक्षरger_init_hw_regs(काष्ठा axp288_chrg_info *info)
अणु
	पूर्णांक ret, cc, cv;
	अचिन्हित पूर्णांक val;

	/* Program temperature thresholds */
	ret = regmap_ग_लिखो(info->regmap, AXP20X_V_LTF_CHRG, CHRG_VLTFC_0C);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
							AXP20X_V_LTF_CHRG, ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(info->regmap, AXP20X_V_HTF_CHRG, CHRG_VHTFC_45C);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
							AXP20X_V_HTF_CHRG, ret);
		वापस ret;
	पूर्ण

	/* Do not turn-off अक्षरger o/p after अक्षरge cycle ends */
	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL2,
				CNTL2_CHG_OUT_TURNON, CNTL2_CHG_OUT_TURNON);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
						AXP20X_CHRG_CTRL2, ret);
		वापस ret;
	पूर्ण

	/* Setup ending condition क्रम अक्षरging to be 10% of I(chrg) */
	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL1,
				CHRG_CCCV_ITERM_20P, 0);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
						AXP20X_CHRG_CTRL1, ret);
		वापस ret;
	पूर्ण

	/* Disable OCV-SOC curve calibration */
	ret = regmap_update_bits(info->regmap,
				AXP20X_CC_CTRL,
				FG_CNTL_OCV_ADJ_EN, 0);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
						AXP20X_CC_CTRL, ret);
		वापस ret;
	पूर्ण

	अगर (dmi_check_प्रणाली(axp288_hp_x2_dmi_ids)) अणु
		/* See comment above axp288_hp_x2_dmi_ids declaration */
		ret = axp288_अक्षरger_vbus_path_select(info, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Read current अक्षरge voltage and current limit */
	ret = regmap_पढ़ो(info->regmap, AXP20X_CHRG_CTRL1, &val);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "register(%x) read error(%d)\n",
			AXP20X_CHRG_CTRL1, ret);
		वापस ret;
	पूर्ण

	/* Determine अक्षरge voltage */
	cv = (val & CHRG_CCCV_CV_MASK) >> CHRG_CCCV_CV_BIT_POS;
	चयन (cv) अणु
	हाल CHRG_CCCV_CV_4100MV:
		info->cv = CV_4100MV;
		अवरोध;
	हाल CHRG_CCCV_CV_4150MV:
		info->cv = CV_4150MV;
		अवरोध;
	हाल CHRG_CCCV_CV_4200MV:
		info->cv = CV_4200MV;
		अवरोध;
	हाल CHRG_CCCV_CV_4350MV:
		info->cv = CV_4350MV;
		अवरोध;
	पूर्ण

	/* Determine अक्षरge current limit */
	cc = (val & CHRG_CCCV_CC_MASK) >> CHRG_CCCV_CC_BIT_POS;
	cc = (cc * CHRG_CCCV_CC_LSB_RES) + CHRG_CCCV_CC_OFFSET;
	info->cc = cc;

	/*
	 * Do not allow the user to configure higher settings then those
	 * set by the firmware
	 */
	info->max_cv = info->cv;
	info->max_cc = info->cc;

	वापस 0;
पूर्ण

अटल व्योम axp288_अक्षरger_cancel_work(व्योम *data)
अणु
	काष्ठा axp288_chrg_info *info = data;

	cancel_work_sync(&info->otg.work);
	cancel_work_sync(&info->cable.work);
पूर्ण

अटल पूर्णांक axp288_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i, pirq;
	काष्ठा axp288_chrg_info *info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config अक्षरger_cfg = अणुपूर्ण;
	अचिन्हित पूर्णांक val;

	/*
	 * On some devices the fuelgauge and अक्षरger parts of the axp288 are
	 * not used, check that the fuelgauge is enabled (CC_CTRL != 0).
	 */
	ret = regmap_पढ़ो(axp20x->regmap, AXP20X_CC_CTRL, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val == 0)
		वापस -ENODEV;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->pdev = pdev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;

	info->cable.edev = extcon_get_extcon_dev(AXP288_EXTCON_DEV_NAME);
	अगर (info->cable.edev == शून्य) अणु
		dev_dbg(&pdev->dev, "%s is not ready, probe deferred\n",
			AXP288_EXTCON_DEV_NAME);
		वापस -EPROBE_DEFER;
	पूर्ण

	अगर (acpi_dev_present(USB_HOST_EXTCON_HID, शून्य, -1)) अणु
		info->otg.cable = extcon_get_extcon_dev(USB_HOST_EXTCON_NAME);
		अगर (info->otg.cable == शून्य) अणु
			dev_dbg(dev, "EXTCON_USB_HOST is not ready, probe deferred\n");
			वापस -EPROBE_DEFER;
		पूर्ण
		dev_info(&pdev->dev,
			 "Using " USB_HOST_EXTCON_HID " extcon for usb-id\n");
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	ret = अक्षरger_init_hw_regs(info);
	अगर (ret)
		वापस ret;

	/* Register with घातer supply class */
	अक्षरger_cfg.drv_data = info;
	info->psy_usb = devm_घातer_supply_रेजिस्टर(dev, &axp288_अक्षरger_desc,
						   &अक्षरger_cfg);
	अगर (IS_ERR(info->psy_usb)) अणु
		ret = PTR_ERR(info->psy_usb);
		dev_err(dev, "failed to register power supply: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Cancel our work on cleanup, रेजिस्टर this beक्रमe the notअगरiers */
	ret = devm_add_action(dev, axp288_अक्षरger_cancel_work, info);
	अगर (ret)
		वापस ret;

	/* Register क्रम extcon notअगरication */
	INIT_WORK(&info->cable.work, axp288_अक्षरger_extcon_evt_worker);
	info->cable.nb.notअगरier_call = axp288_अक्षरger_handle_cable_evt;
	ret = devm_extcon_रेजिस्टर_notअगरier_all(dev, info->cable.edev,
						&info->cable.nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register cable extcon notifier\n");
		वापस ret;
	पूर्ण
	schedule_work(&info->cable.work);

	/* Register क्रम OTG notअगरication */
	INIT_WORK(&info->otg.work, axp288_अक्षरger_otg_evt_worker);
	info->otg.id_nb.notअगरier_call = axp288_अक्षरger_handle_otg_evt;
	अगर (info->otg.cable) अणु
		ret = devm_extcon_रेजिस्टर_notअगरier(&pdev->dev, info->otg.cable,
					EXTCON_USB_HOST, &info->otg.id_nb);
		अगर (ret) अणु
			dev_err(dev, "failed to register EXTCON_USB_HOST notifier\n");
			वापस ret;
		पूर्ण
		schedule_work(&info->otg.work);
	पूर्ण

	/* Register अक्षरger पूर्णांकerrupts */
	क्रम (i = 0; i < CHRG_INTR_END; i++) अणु
		pirq = platक्रमm_get_irq(info->pdev, i);
		अगर (pirq < 0)
			वापस pirq;

		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		अगर (info->irq[i] < 0) अणु
			dev_warn(&info->pdev->dev,
				"failed to get virtual interrupt=%d\n", pirq);
			वापस info->irq[i];
		पूर्ण
		ret = devm_request_thपढ़ोed_irq(&info->pdev->dev, info->irq[i],
					शून्य, axp288_अक्षरger_irq_thपढ़ो_handler,
					IRQF_ONESHOT, info->pdev->name, info);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request interrupt=%d\n",
								info->irq[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id axp288_अक्षरger_id_table[] = अणु
	अणु .name = "axp288_charger" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, axp288_अक्षरger_id_table);

अटल काष्ठा platक्रमm_driver axp288_अक्षरger_driver = अणु
	.probe = axp288_अक्षरger_probe,
	.id_table = axp288_अक्षरger_id_table,
	.driver = अणु
		.name = "axp288_charger",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axp288_अक्षरger_driver);

MODULE_AUTHOR("Ramakrishna Pallala <ramakrishna.pallala@intel.com>");
MODULE_DESCRIPTION("X-power AXP288 Charger Driver");
MODULE_LICENSE("GPL v2");
