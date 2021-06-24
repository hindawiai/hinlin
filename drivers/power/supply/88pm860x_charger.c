<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery driver क्रम Marvell 88PM860x PMIC
 *
 * Copyright (c) 2012 Marvell International Ltd.
 * Author:	Jett Zhou <jtzhou@marvell.com>
 *		Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/भाग64.h>

/* bit definitions of Status Query Interface 2 */
#घोषणा STATUS2_CHG		(1 << 2)

/* bit definitions of Reset Out Register */
#घोषणा RESET_SW_PD		(1 << 7)

/* bit definitions of PreReg 1 */
#घोषणा PREREG1_90MA		(0x0)
#घोषणा PREREG1_180MA		(0x1)
#घोषणा PREREG1_450MA		(0x4)
#घोषणा PREREG1_540MA		(0x5)
#घोषणा PREREG1_1350MA		(0xE)
#घोषणा PREREG1_VSYS_4_5V	(3 << 4)

/* bit definitions of Charger Control 1 Register */
#घोषणा CC1_MODE_OFF		(0)
#घोषणा CC1_MODE_PRECHARGE	(1)
#घोषणा CC1_MODE_FASTCHARGE	(2)
#घोषणा CC1_MODE_PULSECHARGE	(3)
#घोषणा CC1_ITERM_20MA		(0 << 2)
#घोषणा CC1_ITERM_60MA		(2 << 2)
#घोषणा CC1_VFCHG_4_2V		(9 << 4)

/* bit definitions of Charger Control 2 Register */
#घोषणा CC2_ICHG_100MA		(0x1)
#घोषणा CC2_ICHG_500MA		(0x9)
#घोषणा CC2_ICHG_1000MA		(0x13)

/* bit definitions of Charger Control 3 Register */
#घोषणा CC3_180MIN_TIMEOUT	(0x6 << 4)
#घोषणा CC3_270MIN_TIMEOUT	(0x7 << 4)
#घोषणा CC3_360MIN_TIMEOUT	(0xA << 4)
#घोषणा CC3_DISABLE_TIMEOUT	(0xF << 4)

/* bit definitions of Charger Control 4 Register */
#घोषणा CC4_IPRE_40MA		(7)
#घोषणा CC4_VPCHG_3_2V		(3 << 4)
#घोषणा CC4_IFCHG_MON_EN	(1 << 6)
#घोषणा CC4_BTEMP_MON_EN	(1 << 7)

/* bit definitions of Charger Control 6 Register */
#घोषणा CC6_BAT_OV_EN		(1 << 2)
#घोषणा CC6_BAT_UV_EN		(1 << 3)
#घोषणा CC6_UV_VBAT_SET		(0x3 << 6)	/* 2.8v */

/* bit definitions of Charger Control 7 Register */
#घोषणा CC7_BAT_REM_EN		(1 << 3)
#घोषणा CC7_IFSM_EN		(1 << 7)

/* bit definitions of Measurement Enable 1 Register */
#घोषणा MEAS1_VBAT		(1 << 0)

/* bit definitions of Measurement Enable 3 Register */
#घोषणा MEAS3_IBAT_EN		(1 << 0)
#घोषणा MEAS3_CC_EN		(1 << 2)

#घोषणा FSM_INIT		0
#घोषणा FSM_DISCHARGE		1
#घोषणा FSM_PRECHARGE		2
#घोषणा FSM_FASTCHARGE		3

#घोषणा PRECHARGE_THRESHOLD	3100
#घोषणा POWEROFF_THRESHOLD	3400
#घोषणा CHARGE_THRESHOLD	4000
#घोषणा DISCHARGE_THRESHOLD	4180

/* over-temperature on PM8606 setting */
#घोषणा OVER_TEMP_FLAG		(1 << 6)
#घोषणा OVTEMP_AUTORECOVER	(1 << 3)

/* over-voltage protect on vchg setting mv */
#घोषणा VCHG_NORMAL_LOW		4200
#घोषणा VCHG_NORMAL_CHECK	5800
#घोषणा VCHG_NORMAL_HIGH	6000
#घोषणा VCHG_OVP_LOW		5500

काष्ठा pm860x_अक्षरger_info अणु
	काष्ठा pm860x_chip *chip;
	काष्ठा i2c_client *i2c;
	काष्ठा i2c_client *i2c_8606;
	काष्ठा device *dev;

	काष्ठा घातer_supply *usb;
	काष्ठा mutex lock;
	पूर्णांक irq_nums;
	पूर्णांक irq[7];
	अचिन्हित state:3;	/* fsm state */
	अचिन्हित online:1;	/* usb अक्षरger */
	अचिन्हित present:1;	/* battery present */
	अचिन्हित allowed:1;
पूर्ण;

अटल अक्षर *pm860x_supplied_to[] = अणु
	"battery-monitor",
पूर्ण;

अटल पूर्णांक measure_vchg(काष्ठा pm860x_अक्षरger_info *info, पूर्णांक *data)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक ret = 0;

	ret = pm860x_bulk_पढ़ो(info->i2c, PM8607_VCHG_MEAS1, 2, buf);
	अगर (ret < 0)
		वापस ret;

	*data = ((buf[0] & 0xff) << 4) | (buf[1] & 0x0f);
	/* V_BATT_MEAS(mV) = value * 5 * 1.8 * 1000 / (2^12) */
	*data = ((*data & 0xfff) * 9 * 125) >> 9;

	dev_dbg(info->dev, "%s, vchg: %d mv\n", __func__, *data);

	वापस ret;
पूर्ण

अटल व्योम set_vchg_threshold(काष्ठा pm860x_अक्षरger_info *info,
			       पूर्णांक min, पूर्णांक max)
अणु
	पूर्णांक data;

	/* (पंचांगp << 8) * / 5 / 1800 */
	अगर (min <= 0)
		data = 0;
	अन्यथा
		data = (min << 5) / 1125;
	pm860x_reg_ग_लिखो(info->i2c, PM8607_VCHG_LOWTH, data);
	dev_dbg(info->dev, "VCHG_LOWTH:%dmv, 0x%x\n", min, data);

	अगर (max <= 0)
		data = 0xff;
	अन्यथा
		data = (max << 5) / 1125;
	pm860x_reg_ग_लिखो(info->i2c, PM8607_VCHG_HIGHTH, data);
	dev_dbg(info->dev, "VCHG_HIGHTH:%dmv, 0x%x\n", max, data);

पूर्ण

अटल व्योम set_vbatt_threshold(काष्ठा pm860x_अक्षरger_info *info,
				पूर्णांक min, पूर्णांक max)
अणु
	पूर्णांक data;

	/* (पंचांगp << 8) * 3 / 1800 */
	अगर (min <= 0)
		data = 0;
	अन्यथा
		data = (min << 5) / 675;
	pm860x_reg_ग_लिखो(info->i2c, PM8607_VBAT_LOWTH, data);
	dev_dbg(info->dev, "VBAT Min:%dmv, LOWTH:0x%x\n", min, data);

	अगर (max <= 0)
		data = 0xff;
	अन्यथा
		data = (max << 5) / 675;
	pm860x_reg_ग_लिखो(info->i2c, PM8607_VBAT_HIGHTH, data);
	dev_dbg(info->dev, "VBAT Max:%dmv, HIGHTH:0x%x\n", max, data);

	वापस;
पूर्ण

अटल पूर्णांक start_preअक्षरge(काष्ठा pm860x_अक्षरger_info *info)
अणु
	पूर्णांक ret;

	dev_dbg(info->dev, "Start Pre-charging!\n");
	set_vbatt_threshold(info, 0, 0);

	ret = pm860x_reg_ग_लिखो(info->i2c_8606, PM8606_PREREGULATORA,
			       PREREG1_1350MA | PREREG1_VSYS_4_5V);
	अगर (ret < 0)
		जाओ out;
	/* stop अक्षरging */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3,
			      CC1_MODE_OFF);
	अगर (ret < 0)
		जाओ out;
	/* set 270 minutes समयout */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL3, (0xf << 4),
			      CC3_270MIN_TIMEOUT);
	अगर (ret < 0)
		जाओ out;
	/* set preअक्षरge current, termination voltage, IBAT & TBAT monitor */
	ret = pm860x_reg_ग_लिखो(info->i2c, PM8607_CHG_CTRL4,
			       CC4_IPRE_40MA | CC4_VPCHG_3_2V |
			       CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN);
	अगर (ret < 0)
		जाओ out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL7,
			      CC7_BAT_REM_EN | CC7_IFSM_EN,
			      CC7_BAT_REM_EN | CC7_IFSM_EN);
	अगर (ret < 0)
		जाओ out;
	/* trigger preअक्षरge */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3,
			      CC1_MODE_PRECHARGE);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक start_fastअक्षरge(काष्ठा pm860x_अक्षरger_info *info)
अणु
	पूर्णांक ret;

	dev_dbg(info->dev, "Start Fast-charging!\n");

	/* set fastअक्षरge termination current & voltage, disable अक्षरging */
	ret = pm860x_reg_ग_लिखो(info->i2c, PM8607_CHG_CTRL1,
			       CC1_MODE_OFF | CC1_ITERM_60MA |
			       CC1_VFCHG_4_2V);
	अगर (ret < 0)
		जाओ out;
	ret = pm860x_reg_ग_लिखो(info->i2c_8606, PM8606_PREREGULATORA,
			       PREREG1_540MA | PREREG1_VSYS_4_5V);
	अगर (ret < 0)
		जाओ out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL2, 0x1f,
			      CC2_ICHG_500MA);
	अगर (ret < 0)
		जाओ out;
	/* set 270 minutes समयout */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL3, (0xf << 4),
			      CC3_270MIN_TIMEOUT);
	अगर (ret < 0)
		जाओ out;
	/* set IBAT & TBAT monitor */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL4,
			      CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN,
			      CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN);
	अगर (ret < 0)
		जाओ out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL6,
			      CC6_BAT_OV_EN | CC6_BAT_UV_EN |
			      CC6_UV_VBAT_SET,
			      CC6_BAT_OV_EN | CC6_BAT_UV_EN |
			      CC6_UV_VBAT_SET);
	अगर (ret < 0)
		जाओ out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL7,
			      CC7_BAT_REM_EN | CC7_IFSM_EN,
			      CC7_BAT_REM_EN | CC7_IFSM_EN);
	अगर (ret < 0)
		जाओ out;
	/* launch fast-अक्षरge */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3,
			      CC1_MODE_FASTCHARGE);
	/* vchg threshold setting */
	set_vchg_threshold(info, VCHG_NORMAL_LOW, VCHG_NORMAL_HIGH);
out:
	वापस ret;
पूर्ण

अटल व्योम stop_अक्षरge(काष्ठा pm860x_अक्षरger_info *info, पूर्णांक vbatt)
अणु
	dev_dbg(info->dev, "Stop charging!\n");
	pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3, CC1_MODE_OFF);
	अगर (vbatt > CHARGE_THRESHOLD && info->online)
		set_vbatt_threshold(info, CHARGE_THRESHOLD, 0);
पूर्ण

अटल व्योम घातer_off_notअगरication(काष्ठा pm860x_अक्षरger_info *info)
अणु
	dev_dbg(info->dev, "Power-off notification!\n");
पूर्ण

अटल पूर्णांक set_अक्षरging_fsm(काष्ठा pm860x_अक्षरger_info *info)
अणु
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval data;
	अचिन्हित अक्षर fsm_state[][16] = अणु "init", "discharge", "precharge",
		"fastcharge",
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक vbatt;

	psy = घातer_supply_get_by_name(pm860x_supplied_to[0]);
	अगर (!psy)
		वापस -EINVAL;
	ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_VOLTAGE_NOW,
			&data);
	अगर (ret) अणु
		घातer_supply_put(psy);
		वापस ret;
	पूर्ण
	vbatt = data.पूर्णांकval / 1000;

	ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_PRESENT, &data);
	अगर (ret) अणु
		घातer_supply_put(psy);
		वापस ret;
	पूर्ण
	घातer_supply_put(psy);

	mutex_lock(&info->lock);
	info->present = data.पूर्णांकval;

	dev_dbg(info->dev, "Entering FSM:%s, Charger:%s, Battery:%s, "
		"Allowed:%d\n",
		&fsm_state[info->state][0],
		(info->online) ? "online" : "N/A",
		(info->present) ? "present" : "N/A", info->allowed);
	dev_dbg(info->dev, "set_charging_fsm:vbatt:%d(mV)\n", vbatt);

	चयन (info->state) अणु
	हाल FSM_INIT:
		अगर (info->online && info->present && info->allowed) अणु
			अगर (vbatt < PRECHARGE_THRESHOLD) अणु
				info->state = FSM_PRECHARGE;
				start_preअक्षरge(info);
			पूर्ण अन्यथा अगर (vbatt > DISCHARGE_THRESHOLD) अणु
				info->state = FSM_DISCHARGE;
				stop_अक्षरge(info, vbatt);
			पूर्ण अन्यथा अगर (vbatt < DISCHARGE_THRESHOLD) अणु
				info->state = FSM_FASTCHARGE;
				start_fastअक्षरge(info);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (vbatt < POWEROFF_THRESHOLD) अणु
				घातer_off_notअगरication(info);
			पूर्ण अन्यथा अणु
				info->state = FSM_DISCHARGE;
				stop_अक्षरge(info, vbatt);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल FSM_PRECHARGE:
		अगर (info->online && info->present && info->allowed) अणु
			अगर (vbatt > PRECHARGE_THRESHOLD) अणु
				info->state = FSM_FASTCHARGE;
				start_fastअक्षरge(info);
			पूर्ण
		पूर्ण अन्यथा अणु
			info->state = FSM_DISCHARGE;
			stop_अक्षरge(info, vbatt);
		पूर्ण
		अवरोध;
	हाल FSM_FASTCHARGE:
		अगर (info->online && info->present && info->allowed) अणु
			अगर (vbatt < PRECHARGE_THRESHOLD) अणु
				info->state = FSM_PRECHARGE;
				start_preअक्षरge(info);
			पूर्ण
		पूर्ण अन्यथा अणु
			info->state = FSM_DISCHARGE;
			stop_अक्षरge(info, vbatt);
		पूर्ण
		अवरोध;
	हाल FSM_DISCHARGE:
		अगर (info->online && info->present && info->allowed) अणु
			अगर (vbatt < PRECHARGE_THRESHOLD) अणु
				info->state = FSM_PRECHARGE;
				start_preअक्षरge(info);
			पूर्ण अन्यथा अगर (vbatt < DISCHARGE_THRESHOLD) अणु
				info->state = FSM_FASTCHARGE;
				start_fastअक्षरge(info);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (vbatt < POWEROFF_THRESHOLD)
				घातer_off_notअगरication(info);
			अन्यथा अगर (vbatt > CHARGE_THRESHOLD && info->online)
				set_vbatt_threshold(info, CHARGE_THRESHOLD, 0);
		पूर्ण
		अवरोध;
	शेष:
		dev_warn(info->dev, "FSM meets wrong state:%d\n",
			 info->state);
		अवरोध;
	पूर्ण
	dev_dbg(info->dev,
		"Out FSM:%s, Charger:%s, Battery:%s, Allowed:%d\n",
		&fsm_state[info->state][0],
		(info->online) ? "online" : "N/A",
		(info->present) ? "present" : "N/A", info->allowed);
	mutex_unlock(&info->lock);

	वापस 0;
पूर्ण

अटल irqवापस_t pm860x_अक्षरger_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_अक्षरger_info *info = data;
	पूर्णांक ret;

	mutex_lock(&info->lock);
	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_STATUS_2);
	अगर (ret < 0) अणु
		mutex_unlock(&info->lock);
		जाओ out;
	पूर्ण
	अगर (ret & STATUS2_CHG) अणु
		info->online = 1;
		info->allowed = 1;
	पूर्ण अन्यथा अणु
		info->online = 0;
		info->allowed = 0;
	पूर्ण
	mutex_unlock(&info->lock);
	dev_dbg(info->dev, "%s, Charger:%s, Allowed:%d\n", __func__,
		(info->online) ? "online" : "N/A", info->allowed);

	set_अक्षरging_fsm(info);

	घातer_supply_changed(info->usb);
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm860x_temp_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा घातer_supply *psy;
	काष्ठा pm860x_अक्षरger_info *info = data;
	जोड़ घातer_supply_propval temp;
	पूर्णांक value;
	पूर्णांक ret;

	psy = घातer_supply_get_by_name(pm860x_supplied_to[0]);
	अगर (!psy)
		वापस IRQ_HANDLED;
	ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_TEMP, &temp);
	अगर (ret)
		जाओ out;
	value = temp.पूर्णांकval / 10;

	mutex_lock(&info->lock);
	/* Temperature < -10 C or >40 C, Will not allow अक्षरge */
	अगर (value < -10 || value > 40)
		info->allowed = 0;
	अन्यथा
		info->allowed = 1;
	dev_dbg(info->dev, "%s, Allowed: %d\n", __func__, info->allowed);
	mutex_unlock(&info->lock);

	set_अक्षरging_fsm(info);
out:
	घातer_supply_put(psy);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm860x_exception_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_अक्षरger_info *info = data;

	mutex_lock(&info->lock);
	info->allowed = 0;
	mutex_unlock(&info->lock);
	dev_dbg(info->dev, "%s, irq: %d\n", __func__, irq);

	set_अक्षरging_fsm(info);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm860x_करोne_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_अक्षरger_info *info = data;
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;
	पूर्णांक vbatt;

	mutex_lock(&info->lock);
	/* pre-अक्षरge करोne, will transimit to fast-अक्षरge stage */
	अगर (info->state == FSM_PRECHARGE) अणु
		info->allowed = 1;
		जाओ out;
	पूर्ण
	/*
	 * Fast अक्षरge करोne, delay to पढ़ो
	 * the correct status of CHG_DET.
	 */
	mdelay(5);
	info->allowed = 0;
	psy = घातer_supply_get_by_name(pm860x_supplied_to[0]);
	अगर (!psy)
		जाओ out;
	ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_VOLTAGE_NOW,
			&val);
	अगर (ret)
		जाओ out_psy_put;
	vbatt = val.पूर्णांकval / 1000;
	/*
	 * CHG_DONE पूर्णांकerrupt is faster than CHG_DET पूर्णांकerrupt when
	 * plug in/out usb, So we can not rely on info->online, we
	 * need check pm8607 status रेजिस्टर to check usb is online
	 * or not, then we can decide it is real अक्षरge करोne
	 * स्वतःmatically or it is triggered by usb plug out;
	 */
	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_STATUS_2);
	अगर (ret < 0)
		जाओ out_psy_put;
	अगर (vbatt > CHARGE_THRESHOLD && ret & STATUS2_CHG)
		घातer_supply_set_property(psy, POWER_SUPPLY_PROP_CHARGE_FULL,
				&val);

out_psy_put:
	घातer_supply_put(psy);
out:
	mutex_unlock(&info->lock);
	dev_dbg(info->dev, "%s, Allowed: %d\n", __func__, info->allowed);
	set_अक्षरging_fsm(info);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm860x_vbattery_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_अक्षरger_info *info = data;

	mutex_lock(&info->lock);

	set_vbatt_threshold(info, 0, 0);

	अगर (info->present && info->online)
		info->allowed = 1;
	अन्यथा
		info->allowed = 0;
	mutex_unlock(&info->lock);
	dev_dbg(info->dev, "%s, Allowed: %d\n", __func__, info->allowed);

	set_अक्षरging_fsm(info);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm860x_vchg_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_अक्षरger_info *info = data;
	पूर्णांक vchg = 0;

	अगर (info->present)
		जाओ out;

	measure_vchg(info, &vchg);

	mutex_lock(&info->lock);
	अगर (!info->online) अणु
		पूर्णांक status;
		/* check अगर over-temp on pm8606 or not */
		status = pm860x_reg_पढ़ो(info->i2c_8606, PM8606_FLAGS);
		अगर (status & OVER_TEMP_FLAG) अणु
			/* clear over temp flag and set स्वतः recover */
			pm860x_set_bits(info->i2c_8606, PM8606_FLAGS,
					OVER_TEMP_FLAG, OVER_TEMP_FLAG);
			pm860x_set_bits(info->i2c_8606,
					PM8606_VSYS,
					OVTEMP_AUTORECOVER,
					OVTEMP_AUTORECOVER);
			dev_dbg(info->dev,
				"%s, pm8606 over-temp occurred\n", __func__);
		पूर्ण
	पूर्ण

	अगर (vchg > VCHG_NORMAL_CHECK) अणु
		set_vchg_threshold(info, VCHG_OVP_LOW, 0);
		info->allowed = 0;
		dev_dbg(info->dev,
			"%s,pm8607 over-vchg occurred,vchg = %dmv\n",
			__func__, vchg);
	पूर्ण अन्यथा अगर (vchg < VCHG_OVP_LOW) अणु
		set_vchg_threshold(info, VCHG_NORMAL_LOW,
				   VCHG_NORMAL_HIGH);
		info->allowed = 1;
		dev_dbg(info->dev,
			"%s,pm8607 over-vchg recover,vchg = %dmv\n",
			__func__, vchg);
	पूर्ण
	mutex_unlock(&info->lock);

	dev_dbg(info->dev, "%s, Allowed: %d\n", __func__, info->allowed);
	set_अक्षरging_fsm(info);
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm860x_usb_get_prop(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property psp,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pm860x_अक्षरger_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (info->state == FSM_FASTCHARGE ||
				info->state == FSM_PRECHARGE)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = info->online;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property pm860x_usb_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल पूर्णांक pm860x_init_अक्षरger(काष्ठा pm860x_अक्षरger_info *info)
अणु
	पूर्णांक ret;

	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_STATUS_2);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&info->lock);
	info->state = FSM_INIT;
	अगर (ret & STATUS2_CHG) अणु
		info->online = 1;
		info->allowed = 1;
	पूर्ण अन्यथा अणु
		info->online = 0;
		info->allowed = 0;
	पूर्ण
	mutex_unlock(&info->lock);

	set_अक्षरging_fsm(info);
	वापस 0;
पूर्ण

अटल काष्ठा pm860x_irq_desc अणु
	स्थिर अक्षर *name;
	irqवापस_t (*handler)(पूर्णांक irq, व्योम *data);
पूर्ण pm860x_irq_descs[] = अणु
	अणु "usb supply detect", pm860x_अक्षरger_handler पूर्ण,
	अणु "charge done", pm860x_करोne_handler पूर्ण,
	अणु "charge timeout", pm860x_exception_handler पूर्ण,
	अणु "charge fault", pm860x_exception_handler पूर्ण,
	अणु "temperature", pm860x_temp_handler पूर्ण,
	अणु "vbatt", pm860x_vbattery_handler पूर्ण,
	अणु "vchg", pm860x_vchg_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pm860x_अक्षरger_desc = अणु
	.name		= "usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= pm860x_usb_props,
	.num_properties	= ARRAY_SIZE(pm860x_usb_props),
	.get_property	= pm860x_usb_get_prop,
पूर्ण;

अटल पूर्णांक pm860x_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा pm860x_अक्षरger_info *info;
	पूर्णांक ret;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक j;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	count = pdev->num_resources;
	क्रम (i = 0, j = 0; i < count; i++) अणु
		info->irq[j] = platक्रमm_get_irq(pdev, i);
		अगर (info->irq[j] < 0)
			जारी;
		j++;
	पूर्ण
	info->irq_nums = j;

	info->chip = chip;
	info->i2c =
	    (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->i2c_8606 =
	    (chip->id == CHIP_PM8607) ? chip->companion : chip->client;
	अगर (!info->i2c_8606) अणु
		dev_err(&pdev->dev, "Missed I2C address of 88PM8606!\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	info->dev = &pdev->dev;

	/* set init value क्रम the हाल we are not using battery */
	set_vchg_threshold(info, VCHG_NORMAL_LOW, VCHG_OVP_LOW);

	mutex_init(&info->lock);
	platक्रमm_set_drvdata(pdev, info);

	psy_cfg.drv_data = info;
	psy_cfg.supplied_to = pm860x_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(pm860x_supplied_to);
	info->usb = घातer_supply_रेजिस्टर(&pdev->dev, &pm860x_अक्षरger_desc,
					  &psy_cfg);
	अगर (IS_ERR(info->usb)) अणु
		ret = PTR_ERR(info->usb);
		जाओ out;
	पूर्ण

	pm860x_init_अक्षरger(info);

	क्रम (i = 0; i < ARRAY_SIZE(info->irq); i++) अणु
		ret = request_thपढ़ोed_irq(info->irq[i], शून्य,
			pm860x_irq_descs[i].handler,
			IRQF_ONESHOT, pm860x_irq_descs[i].name, info);
		अगर (ret < 0) अणु
			dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
				info->irq[i], ret);
			जाओ out_irq;
		पूर्ण
	पूर्ण
	वापस 0;

out_irq:
	घातer_supply_unरेजिस्टर(info->usb);
	जबतक (--i >= 0)
		मुक्त_irq(info->irq[i], info);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pm860x_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_अक्षरger_info *info = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	घातer_supply_unरेजिस्टर(info->usb);
	क्रम (i = 0; i < info->irq_nums; i++)
		मुक्त_irq(info->irq[i], info);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm860x_अक्षरger_driver = अणु
	.driver = अणु
		   .name = "88pm860x-charger",
	पूर्ण,
	.probe = pm860x_अक्षरger_probe,
	.हटाओ = pm860x_अक्षरger_हटाओ,
पूर्ण;
module_platक्रमm_driver(pm860x_अक्षरger_driver);

MODULE_DESCRIPTION("Marvell 88PM860x Charger driver");
MODULE_LICENSE("GPL");
