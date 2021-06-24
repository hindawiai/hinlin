<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Copyright (C) 2018 ROHM Semiconductors
//
// घातer-supply driver क्रम ROHM BD70528 PMIC

/*
 * BD70528 अक्षरger HW state machine.
 *
 * The thermal shutकरोwn state is not drawn. From any other state but
 * battery error and suspend it is possible to go to TSD/TMP states
 * अगर temperature is out of bounds.
 *
 *  CHG_RST = H
 *  or CHG_EN=L
 *  or (DCIN2_UVLO=L && DCIN1_UVLO=L)
 *  or (DCIN2_OVLO=H & DCIN1_UVKLO=L)
 *
 *  +--------------+         +--------------+
 *  |              |         |              |
 *  |  Any state   +-------> |    Suspend   |
 *  |              |         |              |
 *  +--------------+         +------+-------+
 *                                  |
 *  CHG_EN = H && BAT_DET = H &&    |
 *  No errors (temp, bat_ov, UVLO,  |
 *  OVLO...)                        |
 *                                  |
 *  BAT_OV or             +---------v----------+
 *  (DBAT && TTRI)        |                    |
 *      +-----------------+   Trickle Charge   | <---------------+
 *      |                 |                    |                 |
 *      |                 +-------+------------+                 |
 *      |                         |                              |
 *      |                         |     ^                        |
 *      |        V_BAT > VTRI_TH  |     |  VBAT < VTRI_TH - 50mV |
 *      |                         |     |                        |
 *      |                         v     |                        |
 *      |                               |                        |
 *      |     BAT_OV or      +----------+----+                   |
 *      |     (DBAT && TFST) |               |                   |
 *      |   +----------------+  Fast Charge  |                   |
 *      |   |                |               |                   |
 *      v   v                +----+----------+                   |
 *                                |                              |
 *+----------------+   ILIM_DET=L |    ^ ILIM_DET                |
 *|                |   & CV_DET=H |    | or CV_DET=L             |
 *|  Battery Error |   & VBAT >   |    | or VBAT < VRECHG_TH     |
 *|                |   VRECHG_TH  |    | or IBAT  > IFST/x       |
 *+----------------+   & IBAT <   |    |                         |
 *                     IFST/x     v    |                         |
 *       ^                             |                         |
 *       |                   +---------+-+                       |
 *       |                   |           |                       |
 *       +-------------------+  Top OFF  |                       |
 *  BAT_OV = H or            |           |                       |
 *  (DBAT && TFST)           +-----+-----+                       |
 *                                 |                             |
 *           Stay top-off क्रम 15s  |                             |
 *                                 v                             |
 *                                                               |
 *                            +--------+                         |
 *                            |        |                         |
 *                            |  Done  +-------------------------+
 *                            |        |
 *                            +--------+   VBAT < VRECHG_TH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/rohm-bd70528.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/linear_range.h>

#घोषणा CHG_STAT_SUSPEND	0x0
#घोषणा CHG_STAT_TRICKLE	0x1
#घोषणा CHG_STAT_FAST		0x3
#घोषणा CHG_STAT_TOPOFF		0xe
#घोषणा CHG_STAT_DONE		0xf
#घोषणा CHG_STAT_OTP_TRICKLE	0x10
#घोषणा CHG_STAT_OTP_FAST	0x11
#घोषणा CHG_STAT_OTP_DONE	0x12
#घोषणा CHG_STAT_TSD_TRICKLE	0x20
#घोषणा CHG_STAT_TSD_FAST	0x21
#घोषणा CHG_STAT_TSD_TOPOFF	0x22
#घोषणा CHG_STAT_BAT_ERR	0x7f

अटल स्थिर अक्षर *bd70528_अक्षरger_model = "BD70528";
अटल स्थिर अक्षर *bd70528_अक्षरger_manufacturer = "ROHM Semiconductors";

#घोषणा BD_ERR_IRQ_HND(_name_, _wrn_)					\
अटल irqवापस_t bd0528_##_name_##_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)	\
अणु									\
	काष्ठा घातer_supply *psy = (काष्ठा घातer_supply *)arg;		\
									\
	घातer_supply_changed(psy);					\
	dev_err(&psy->dev, (_wrn_));					\
									\
	वापस IRQ_HANDLED;						\
पूर्ण

#घोषणा BD_INFO_IRQ_HND(_name_, _wrn_)					\
अटल irqवापस_t bd0528_##_name_##_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)	\
अणु									\
	काष्ठा घातer_supply *psy = (काष्ठा घातer_supply *)arg;		\
									\
	घातer_supply_changed(psy);					\
	dev_dbg(&psy->dev, (_wrn_));					\
									\
	वापस IRQ_HANDLED;						\
पूर्ण

#घोषणा BD_IRQ_HND(_name_) bd0528_##_name_##_पूर्णांकerrupt

काष्ठा bd70528_psy अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा घातer_supply *psy;
पूर्ण;

BD_ERR_IRQ_HND(BAT_OV_DET, "Battery overvoltage detected\n");
BD_ERR_IRQ_HND(DBAT_DET, "Dead battery detected\n");
BD_ERR_IRQ_HND(COLD_DET, "Battery cold\n");
BD_ERR_IRQ_HND(HOT_DET, "Battery hot\n");
BD_ERR_IRQ_HND(CHG_TSD, "Charger thermal shutdown\n");
BD_ERR_IRQ_HND(DCIN2_OV_DET, "DCIN2 overvoltage detected\n");

BD_INFO_IRQ_HND(BAT_OV_RES, "Battery voltage back to normal\n");
BD_INFO_IRQ_HND(COLD_RES, "Battery temperature back to normal\n");
BD_INFO_IRQ_HND(HOT_RES, "Battery temperature back to normal\n");
BD_INFO_IRQ_HND(BAT_RMV, "Battery removed\n");
BD_INFO_IRQ_HND(BAT_DET, "Battery detected\n");
BD_INFO_IRQ_HND(DCIN2_OV_RES, "DCIN2 voltage back to normal\n");
BD_INFO_IRQ_HND(DCIN2_RMV, "DCIN2 removed\n");
BD_INFO_IRQ_HND(DCIN2_DET, "DCIN2 detected\n");
BD_INFO_IRQ_HND(DCIN1_RMV, "DCIN1 removed\n");
BD_INFO_IRQ_HND(DCIN1_DET, "DCIN1 detected\n");

काष्ठा irq_name_pair अणु
	स्थिर अक्षर *n;
	irqवापस_t (*h)(पूर्णांक irq, व्योम *arg);
पूर्ण;

अटल पूर्णांक bd70528_get_irqs(काष्ठा platक्रमm_device *pdev,
			    काष्ठा bd70528_psy *bdpsy)
अणु
	पूर्णांक irq, i, ret;
	अचिन्हित पूर्णांक mask;
	अटल स्थिर काष्ठा irq_name_pair bd70528_chg_irqs[] = अणु
		अणु .n = "bd70528-bat-ov-res", .h = BD_IRQ_HND(BAT_OV_RES) पूर्ण,
		अणु .n = "bd70528-bat-ov-det", .h = BD_IRQ_HND(BAT_OV_DET) पूर्ण,
		अणु .n = "bd70528-bat-dead", .h = BD_IRQ_HND(DBAT_DET) पूर्ण,
		अणु .n = "bd70528-bat-warmed", .h = BD_IRQ_HND(COLD_RES) पूर्ण,
		अणु .n = "bd70528-bat-cold", .h = BD_IRQ_HND(COLD_DET) पूर्ण,
		अणु .n = "bd70528-bat-cooled", .h = BD_IRQ_HND(HOT_RES) पूर्ण,
		अणु .n = "bd70528-bat-hot", .h = BD_IRQ_HND(HOT_DET) पूर्ण,
		अणु .n = "bd70528-chg-tshd", .h = BD_IRQ_HND(CHG_TSD) पूर्ण,
		अणु .n = "bd70528-bat-removed", .h = BD_IRQ_HND(BAT_RMV) पूर्ण,
		अणु .n = "bd70528-bat-detected", .h = BD_IRQ_HND(BAT_DET) पूर्ण,
		अणु .n = "bd70528-dcin2-ov-res", .h = BD_IRQ_HND(DCIN2_OV_RES) पूर्ण,
		अणु .n = "bd70528-dcin2-ov-det", .h = BD_IRQ_HND(DCIN2_OV_DET) पूर्ण,
		अणु .n = "bd70528-dcin2-removed", .h = BD_IRQ_HND(DCIN2_RMV) पूर्ण,
		अणु .n = "bd70528-dcin2-detected", .h = BD_IRQ_HND(DCIN2_DET) पूर्ण,
		अणु .n = "bd70528-dcin1-removed", .h = BD_IRQ_HND(DCIN1_RMV) पूर्ण,
		अणु .n = "bd70528-dcin1-detected", .h = BD_IRQ_HND(DCIN1_DET) पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(bd70528_chg_irqs); i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, bd70528_chg_irqs[i].n);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "Bad IRQ information for %s (%d)\n",
				bd70528_chg_irqs[i].n, irq);
			वापस irq;
		पूर्ण
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						bd70528_chg_irqs[i].h,
						IRQF_ONESHOT,
						bd70528_chg_irqs[i].n,
						bdpsy->psy);

		अगर (ret)
			वापस ret;
	पूर्ण
	/*
	 * BD70528 irq controller is not touching the मुख्य mask रेजिस्टर.
	 * So enable the अक्षरger block पूर्णांकerrupts at मुख्य level. We can just
	 * leave them enabled as irq-controller should disable irqs
	 * from sub-रेजिस्टरs when IRQ is disabled or मुक्तd.
	 */
	mask = BD70528_REG_INT_BAT1_MASK | BD70528_REG_INT_BAT2_MASK;
	ret = regmap_update_bits(bdpsy->regmap,
				 BD70528_REG_INT_MAIN_MASK, mask, 0);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to enable charger IRQs\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_get_अक्षरger_status(काष्ठा bd70528_psy *bdpsy, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक v;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_CURR_STAT, &v);
	अगर (ret) अणु
		dev_err(bdpsy->dev, "Charger state read failure %d\n",
			ret);
		वापस ret;
	पूर्ण

	चयन (v & BD70528_MASK_CHG_STAT) अणु
	हाल CHG_STAT_SUSPEND:
	/* Maybe we should check the CHG_TTRI_EN? */
	हाल CHG_STAT_OTP_TRICKLE:
	हाल CHG_STAT_OTP_FAST:
	हाल CHG_STAT_OTP_DONE:
	हाल CHG_STAT_TSD_TRICKLE:
	हाल CHG_STAT_TSD_FAST:
	हाल CHG_STAT_TSD_TOPOFF:
	हाल CHG_STAT_BAT_ERR:
		*val = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल CHG_STAT_DONE:
		*val = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल CHG_STAT_TRICKLE:
	हाल CHG_STAT_FAST:
	हाल CHG_STAT_TOPOFF:
		*val = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	शेष:
		*val = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_get_अक्षरge_type(काष्ठा bd70528_psy *bdpsy, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक v;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_CURR_STAT, &v);
	अगर (ret) अणु
		dev_err(bdpsy->dev, "Charger state read failure %d\n",
			ret);
		वापस ret;
	पूर्ण

	चयन (v & BD70528_MASK_CHG_STAT) अणु
	हाल CHG_STAT_TRICKLE:
		*val = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अवरोध;
	हाल CHG_STAT_FAST:
	हाल CHG_STAT_TOPOFF:
		*val = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अवरोध;
	हाल CHG_STAT_DONE:
	हाल CHG_STAT_SUSPEND:
	/* Maybe we should check the CHG_TTRI_EN? */
	हाल CHG_STAT_OTP_TRICKLE:
	हाल CHG_STAT_OTP_FAST:
	हाल CHG_STAT_OTP_DONE:
	हाल CHG_STAT_TSD_TRICKLE:
	हाल CHG_STAT_TSD_FAST:
	हाल CHG_STAT_TSD_TOPOFF:
	हाल CHG_STAT_BAT_ERR:
		*val = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	शेष:
		*val = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_get_battery_health(काष्ठा bd70528_psy *bdpsy, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक v;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_BAT_STAT, &v);
	अगर (ret) अणु
		dev_err(bdpsy->dev, "Battery state read failure %d\n",
			ret);
		वापस ret;
	पूर्ण
	/* No battery? */
	अगर (!(v & BD70528_MASK_CHG_BAT_DETECT))
		*val = POWER_SUPPLY_HEALTH_DEAD;
	अन्यथा अगर (v & BD70528_MASK_CHG_BAT_OVERVOLT)
		*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	अन्यथा अगर (v & BD70528_MASK_CHG_BAT_TIMER)
		*val = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
	अन्यथा
		*val = POWER_SUPPLY_HEALTH_GOOD;

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_get_online(काष्ठा bd70528_psy *bdpsy, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक v;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_IN_STAT, &v);
	अगर (ret) अणु
		dev_err(bdpsy->dev, "DC1 IN state read failure %d\n",
			ret);
		वापस ret;
	पूर्ण

	*val = (v & BD70528_MASK_CHG_DCIN1_UVLO) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bd70528_get_present(काष्ठा bd70528_psy *bdpsy, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक v;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_BAT_STAT, &v);
	अगर (ret) अणु
		dev_err(bdpsy->dev, "Battery state read failure %d\n",
			ret);
		वापस ret;
	पूर्ण

	*val = (v & BD70528_MASK_CHG_BAT_DETECT) ? 1 : 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा linear_range current_limit_ranges[] = अणु
	अणु
		.min = 5,
		.step = 1,
		.min_sel = 0,
		.max_sel = 0x22,
	पूर्ण,
	अणु
		.min = 40,
		.step = 5,
		.min_sel = 0x23,
		.max_sel = 0x26,
	पूर्ण,
	अणु
		.min = 60,
		.step = 20,
		.min_sel = 0x27,
		.max_sel = 0x2d,
	पूर्ण,
	अणु
		.min = 200,
		.step = 50,
		.min_sel = 0x2e,
		.max_sel = 0x34,
	पूर्ण,
	अणु
		.min = 500,
		.step = 0,
		.min_sel = 0x35,
		.max_sel = 0x3f,
	पूर्ण,
पूर्ण;

/*
 * BD70528 would support setting and getting own अक्षरge current/
 * voltage क्रम low temperatures. The driver currently only पढ़ोs
 * the अक्षरge current at room temperature. We करो set both though.
 */
अटल स्थिर काष्ठा linear_range warm_अक्षरge_curr[] = अणु
	अणु
		.min = 10,
		.step = 10,
		.min_sel = 0,
		.max_sel = 0x12,
	पूर्ण,
	अणु
		.min = 200,
		.step = 25,
		.min_sel = 0x13,
		.max_sel = 0x1f,
	पूर्ण,
पूर्ण;

/*
 * Cold अक्षरge current selectors are identical to warm अक्षरge current
 * selectors. The dअगरference is that only smaller currents are available
 * at cold अक्षरge range.
 */
#घोषणा MAX_COLD_CHG_CURR_SEL 0x15
#घोषणा MAX_WARM_CHG_CURR_SEL 0x1f
#घोषणा MIN_CHG_CURR_SEL 0x0

अटल पूर्णांक get_अक्षरge_current(काष्ठा bd70528_psy *bdpsy, पूर्णांक *ma)
अणु
	अचिन्हित पूर्णांक sel;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_CHG_CURR_WARM,
			  &sel);
	अगर (ret) अणु
		dev_err(bdpsy->dev,
			"Charge current reading failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	sel &= BD70528_MASK_CHG_CHG_CURR;

	ret = linear_range_get_value_array(&warm_अक्षरge_curr[0],
					   ARRAY_SIZE(warm_अक्षरge_curr),
					   sel, ma);
	अगर (ret) अणु
		dev_err(bdpsy->dev,
			"Unknown charge current value 0x%x\n",
			sel);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक get_current_limit(काष्ठा bd70528_psy *bdpsy, पूर्णांक *ma)
अणु
	अचिन्हित पूर्णांक sel;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bdpsy->regmap, BD70528_REG_CHG_DCIN_ILIM,
			  &sel);

	अगर (ret) अणु
		dev_err(bdpsy->dev,
			"Input current limit reading failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	sel &= BD70528_MASK_CHG_DCIN_ILIM;

	ret = linear_range_get_value_array(&current_limit_ranges[0],
					   ARRAY_SIZE(current_limit_ranges),
					   sel, ma);
	अगर (ret) अणु
		/* Unspecअगरied values mean 500 mA */
		*ma = 500;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property bd70528_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल पूर्णांक bd70528_अक्षरger_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bd70528_psy *bdpsy = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		वापस bd70528_get_अक्षरger_status(bdpsy, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		वापस bd70528_get_अक्षरge_type(bdpsy, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_HEALTH:
		वापस bd70528_get_battery_health(bdpsy, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_PRESENT:
		वापस bd70528_get_present(bdpsy, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = get_current_limit(bdpsy, &val->पूर्णांकval);
		val->पूर्णांकval *= 1000;
		वापस ret;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = get_अक्षरge_current(bdpsy, &val->पूर्णांकval);
		val->पूर्णांकval *= 1000;
		वापस ret;
	हाल POWER_SUPPLY_PROP_ONLINE:
		वापस bd70528_get_online(bdpsy, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bd70528_अक्षरger_model;
		वापस 0;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = bd70528_अक्षरger_manufacturer;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bd70528_prop_is_writable(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_अक्षरge_current(काष्ठा bd70528_psy *bdpsy, पूर्णांक ma)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret = 0, पंचांगpret;
	bool found;

	अगर (ma > 500) अणु
		dev_warn(bdpsy->dev,
			 "Requested charge current %u exceed maximum (500mA)\n",
			 ma);
		reg = MAX_WARM_CHG_CURR_SEL;
		जाओ set;
	पूर्ण
	अगर (ma < 10) अणु
		dev_err(bdpsy->dev,
			"Requested charge current %u smaller than min (10mA)\n",
			 ma);
		reg = MIN_CHG_CURR_SEL;
		ret = -EINVAL;
		जाओ set;
	पूर्ण

/*
 * For BD70528 voltage/current limits we happily accept any value which
 * beदीर्घs the range. We could check अगर value matching the selector is
 * desired by computing the range min + (sel - sel_low) * range step - but
 * I guess it is enough अगर we use voltage/current which is बंदst (below)
 * the requested?
 */

	ret = linear_range_get_selector_low_array(warm_अक्षरge_curr,
						  ARRAY_SIZE(warm_अक्षरge_curr),
						  ma, &reg, &found);
	अगर (ret) अणु
		dev_err(bdpsy->dev,
			 "Unsupported charge current %u mA\n", ma);
		reg = MIN_CHG_CURR_SEL;
		जाओ set;
	पूर्ण
	अगर (!found) अणु
		/*
		 * There was a gap in supported values and we hit it.
		 * Yet a smaller value was found so we use it.
		 */
		dev_warn(bdpsy->dev,
			 "Unsupported charge current %u mA\n", ma);
	पूर्ण
set:

	पंचांगpret = regmap_update_bits(bdpsy->regmap,
				    BD70528_REG_CHG_CHG_CURR_WARM,
				    BD70528_MASK_CHG_CHG_CURR, reg);
	अगर (पंचांगpret)
		dev_err(bdpsy->dev,
			"Charge current write failure (%d)\n", पंचांगpret);

	अगर (reg > MAX_COLD_CHG_CURR_SEL)
		reg = MAX_COLD_CHG_CURR_SEL;

	अगर (!पंचांगpret)
		पंचांगpret = regmap_update_bits(bdpsy->regmap,
					    BD70528_REG_CHG_CHG_CURR_COLD,
					    BD70528_MASK_CHG_CHG_CURR, reg);

	अगर (!ret)
		ret = पंचांगpret;

	वापस ret;
पूर्ण

#घोषणा MAX_CURR_LIMIT_SEL 0x34
#घोषणा MIN_CURR_LIMIT_SEL 0x0

अटल पूर्णांक set_current_limit(काष्ठा bd70528_psy *bdpsy, पूर्णांक ma)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret = 0, पंचांगpret;
	bool found;

	अगर (ma > 500) अणु
		dev_warn(bdpsy->dev,
			 "Requested current limit %u exceed maximum (500mA)\n",
			 ma);
		reg = MAX_CURR_LIMIT_SEL;
		जाओ set;
	पूर्ण
	अगर (ma < 5) अणु
		dev_err(bdpsy->dev,
			"Requested current limit %u smaller than min (5mA)\n",
			ma);
		reg = MIN_CURR_LIMIT_SEL;
		ret = -EINVAL;
		जाओ set;
	पूर्ण

	ret = linear_range_get_selector_low_array(current_limit_ranges,
					ARRAY_SIZE(current_limit_ranges),
					ma, &reg, &found);
	अगर (ret) अणु
		dev_err(bdpsy->dev, "Unsupported current limit %umA\n", ma);
		reg = MIN_CURR_LIMIT_SEL;
		जाओ set;
	पूर्ण
	अगर (!found) अणु
		/*
		 * There was a gap in supported values and we hit it.
		 * We found a smaller value from ranges and use it.
		 * Warn user though.
		 */
		dev_warn(bdpsy->dev, "Unsupported current limit %umA\n", ma);
	पूर्ण

set:
	पंचांगpret = regmap_update_bits(bdpsy->regmap,
				    BD70528_REG_CHG_DCIN_ILIM,
				    BD70528_MASK_CHG_DCIN_ILIM, reg);

	अगर (!ret)
		ret = पंचांगpret;

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_अक्षरger_set_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bd70528_psy *bdpsy = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस set_current_limit(bdpsy, val->पूर्णांकval / 1000);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस set_अक्षरge_current(bdpsy, val->पूर्णांकval / 1000);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc bd70528_अक्षरger_desc = अणु
	.name		= "bd70528-charger",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= bd70528_अक्षरger_props,
	.num_properties	= ARRAY_SIZE(bd70528_अक्षरger_props),
	.get_property	= bd70528_अक्षरger_get_property,
	.set_property	= bd70528_अक्षरger_set_property,
	.property_is_ग_लिखोable	= bd70528_prop_is_writable,
पूर्ण;

अटल पूर्णांक bd70528_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd70528_psy *bdpsy;
	काष्ठा घातer_supply_config cfg = अणुपूर्ण;

	bdpsy = devm_kzalloc(&pdev->dev, माप(*bdpsy), GFP_KERNEL);
	अगर (!bdpsy)
		वापस -ENOMEM;

	bdpsy->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!bdpsy->regmap) अणु
		dev_err(&pdev->dev, "No regmap found for chip\n");
		वापस -EINVAL;
	पूर्ण
	bdpsy->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, bdpsy);
	cfg.drv_data = bdpsy;
	cfg.of_node = pdev->dev.parent->of_node;

	bdpsy->psy = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						&bd70528_अक्षरger_desc, &cfg);
	अगर (IS_ERR(bdpsy->psy)) अणु
		dev_err(&pdev->dev, "failed: power supply register\n");
		वापस PTR_ERR(bdpsy->psy);
	पूर्ण

	वापस bd70528_get_irqs(pdev, bdpsy);
पूर्ण

अटल काष्ठा platक्रमm_driver bd70528_घातer = अणु
	.driver = अणु
		.name = "bd70528-power"
	पूर्ण,
	.probe = bd70528_घातer_probe,
पूर्ण;

module_platक्रमm_driver(bd70528_घातer);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD70528 power-supply driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd70528-power");
