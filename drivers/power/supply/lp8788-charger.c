<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - battery अक्षरger driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

/* रेजिस्टर address */
#घोषणा LP8788_CHG_STATUS		0x07
#घोषणा LP8788_CHG_IDCIN		0x13
#घोषणा LP8788_CHG_IBATT		0x14
#घोषणा LP8788_CHG_VTERM		0x15
#घोषणा LP8788_CHG_EOC			0x16

/* mask/shअगरt bits */
#घोषणा LP8788_CHG_INPUT_STATE_M	0x03	/* Addr 07h */
#घोषणा LP8788_CHG_STATE_M		0x3C
#घोषणा LP8788_CHG_STATE_S		2
#घोषणा LP8788_NO_BATT_M		BIT(6)
#घोषणा LP8788_BAD_BATT_M		BIT(7)
#घोषणा LP8788_CHG_IBATT_M		0x1F	/* Addr 14h */
#घोषणा LP8788_CHG_VTERM_M		0x0F	/* Addr 15h */
#घोषणा LP8788_CHG_EOC_LEVEL_M		0x30	/* Addr 16h */
#घोषणा LP8788_CHG_EOC_LEVEL_S		4
#घोषणा LP8788_CHG_EOC_TIME_M		0x0E
#घोषणा LP8788_CHG_EOC_TIME_S		1
#घोषणा LP8788_CHG_EOC_MODE_M		BIT(0)

#घोषणा LP8788_CHARGER_NAME		"charger"
#घोषणा LP8788_BATTERY_NAME		"main_batt"

#घोषणा LP8788_CHG_START		0x11
#घोषणा LP8788_CHG_END			0x1C

#घोषणा LP8788_ISEL_MAX			23
#घोषणा LP8788_ISEL_STEP		50
#घोषणा LP8788_VTERM_MIN		4100
#घोषणा LP8788_VTERM_STEP		25
#घोषणा LP8788_MAX_BATT_CAPACITY	100
#घोषणा LP8788_MAX_CHG_IRQS		11

क्रमागत lp8788_अक्षरging_state अणु
	LP8788_OFF,
	LP8788_WARM_UP,
	LP8788_LOW_INPUT = 0x3,
	LP8788_PRECHARGE,
	LP8788_CC,
	LP8788_CV,
	LP8788_MAINTEन_अंकCE,
	LP8788_BATTERY_FAULT,
	LP8788_SYSTEM_SUPPORT = 0xC,
	LP8788_HIGH_CURRENT = 0xF,
	LP8788_MAX_CHG_STATE,
पूर्ण;

क्रमागत lp8788_अक्षरger_adc_sel अणु
	LP8788_VBATT,
	LP8788_BATT_TEMP,
	LP8788_NUM_CHG_ADC,
पूर्ण;

क्रमागत lp8788_अक्षरger_input_state अणु
	LP8788_SYSTEM_SUPPLY = 1,
	LP8788_FULL_FUNCTION,
पूर्ण;

/*
 * काष्ठा lp8788_chg_irq
 * @which        : lp8788 पूर्णांकerrupt id
 * @virq         : Linux IRQ number from irq_करोमुख्य
 */
काष्ठा lp8788_chg_irq अणु
	क्रमागत lp8788_पूर्णांक_id which;
	पूर्णांक virq;
पूर्ण;

/*
 * काष्ठा lp8788_अक्षरger
 * @lp           : used क्रम accessing the रेजिस्टरs of mfd lp8788 device
 * @अक्षरger      : घातer supply driver क्रम the battery अक्षरger
 * @battery      : घातer supply driver क्रम the battery
 * @अक्षरger_work : work queue क्रम अक्षरger input पूर्णांकerrupts
 * @chan         : iio channels क्रम getting adc values
 *                 eg) battery voltage, capacity and temperature
 * @irqs         : अक्षरger dedicated पूर्णांकerrupts
 * @num_irqs     : total numbers of अक्षरger पूर्णांकerrupts
 * @pdata        : अक्षरger platक्रमm specअगरic data
 */
काष्ठा lp8788_अक्षरger अणु
	काष्ठा lp8788 *lp;
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply *battery;
	काष्ठा work_काष्ठा अक्षरger_work;
	काष्ठा iio_channel *chan[LP8788_NUM_CHG_ADC];
	काष्ठा lp8788_chg_irq irqs[LP8788_MAX_CHG_IRQS];
	पूर्णांक num_irqs;
	काष्ठा lp8788_अक्षरger_platक्रमm_data *pdata;
पूर्ण;

अटल अक्षर *battery_supplied_to[] = अणु
	LP8788_BATTERY_NAME,
पूर्ण;

अटल क्रमागत घातer_supply_property lp8788_अक्षरger_prop[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CURRENT_MAX,
पूर्ण;

अटल क्रमागत घातer_supply_property lp8788_battery_prop[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल bool lp8788_is_अक्षरger_detected(काष्ठा lp8788_अक्षरger *pchg)
अणु
	u8 data;

	lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	data &= LP8788_CHG_INPUT_STATE_M;

	वापस data == LP8788_SYSTEM_SUPPLY || data == LP8788_FULL_FUNCTION;
पूर्ण

अटल पूर्णांक lp8788_अक्षरger_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lp8788_अक्षरger *pchg = dev_get_drvdata(psy->dev.parent);
	u8 पढ़ो;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = lp8788_is_अक्षरger_detected(pchg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_IDCIN, &पढ़ो);
		val->पूर्णांकval = LP8788_ISEL_STEP *
				(min_t(पूर्णांक, पढ़ो, LP8788_ISEL_MAX) + 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_battery_status(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	क्रमागत lp8788_अक्षरging_state state;
	u8 data;
	पूर्णांक ret;

	ret = lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	अगर (ret)
		वापस ret;

	state = (data & LP8788_CHG_STATE_M) >> LP8788_CHG_STATE_S;
	चयन (state) अणु
	हाल LP8788_OFF:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल LP8788_PRECHARGE:
	हाल LP8788_CC:
	हाल LP8788_CV:
	हाल LP8788_HIGH_CURRENT:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल LP8788_MAINTEन_अंकCE:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_battery_health(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	u8 data;
	पूर्णांक ret;

	ret = lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	अगर (ret)
		वापस ret;

	अगर (data & LP8788_NO_BATT_M)
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
	अन्यथा अगर (data & LP8788_BAD_BATT_M)
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
	अन्यथा
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_battery_present(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	u8 data;
	पूर्णांक ret;

	ret = lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = !(data & LP8788_NO_BATT_M);
	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_vbatt_adc(काष्ठा lp8788_अक्षरger *pchg, पूर्णांक *result)
अणु
	काष्ठा iio_channel *channel = pchg->chan[LP8788_VBATT];

	अगर (!channel)
		वापस -EINVAL;

	वापस iio_पढ़ो_channel_processed(channel, result);
पूर्ण

अटल पूर्णांक lp8788_get_battery_voltage(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	वापस lp8788_get_vbatt_adc(pchg, &val->पूर्णांकval);
पूर्ण

अटल पूर्णांक lp8788_get_battery_capacity(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lp8788 *lp = pchg->lp;
	काष्ठा lp8788_अक्षरger_platक्रमm_data *pdata = pchg->pdata;
	अचिन्हित पूर्णांक max_vbatt;
	पूर्णांक vbatt;
	क्रमागत lp8788_अक्षरging_state state;
	u8 data;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -EINVAL;

	max_vbatt = pdata->max_vbatt_mv;
	अगर (max_vbatt == 0)
		वापस -EINVAL;

	ret = lp8788_पढ़ो_byte(lp, LP8788_CHG_STATUS, &data);
	अगर (ret)
		वापस ret;

	state = (data & LP8788_CHG_STATE_M) >> LP8788_CHG_STATE_S;

	अगर (state == LP8788_MAINTEन_अंकCE) अणु
		val->पूर्णांकval = LP8788_MAX_BATT_CAPACITY;
	पूर्ण अन्यथा अणु
		ret = lp8788_get_vbatt_adc(pchg, &vbatt);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = (vbatt * LP8788_MAX_BATT_CAPACITY) / max_vbatt;
		val->पूर्णांकval = min(val->पूर्णांकval, LP8788_MAX_BATT_CAPACITY);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_battery_temperature(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा iio_channel *channel = pchg->chan[LP8788_BATT_TEMP];
	पूर्णांक result;
	पूर्णांक ret;

	अगर (!channel)
		वापस -EINVAL;

	ret = iio_पढ़ो_channel_processed(channel, &result);
	अगर (ret < 0)
		वापस -EINVAL;

	/* unit: 0.1 'C */
	val->पूर्णांकval = result * 10;

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_battery_अक्षरging_current(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	u8 पढ़ो;

	lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_IBATT, &पढ़ो);
	पढ़ो &= LP8788_CHG_IBATT_M;
	val->पूर्णांकval = LP8788_ISEL_STEP *
			(min_t(पूर्णांक, पढ़ो, LP8788_ISEL_MAX) + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_get_अक्षरging_termination_voltage(काष्ठा lp8788_अक्षरger *pchg,
				जोड़ घातer_supply_propval *val)
अणु
	u8 पढ़ो;

	lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_VTERM, &पढ़ो);
	पढ़ो &= LP8788_CHG_VTERM_M;
	val->पूर्णांकval = LP8788_VTERM_MIN + LP8788_VTERM_STEP * पढ़ो;

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_battery_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lp8788_अक्षरger *pchg = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		वापस lp8788_get_battery_status(pchg, val);
	हाल POWER_SUPPLY_PROP_HEALTH:
		वापस lp8788_get_battery_health(pchg, val);
	हाल POWER_SUPPLY_PROP_PRESENT:
		वापस lp8788_get_battery_present(pchg, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		वापस lp8788_get_battery_voltage(pchg, val);
	हाल POWER_SUPPLY_PROP_CAPACITY:
		वापस lp8788_get_battery_capacity(pchg, val);
	हाल POWER_SUPPLY_PROP_TEMP:
		वापस lp8788_get_battery_temperature(pchg, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस lp8788_get_battery_अक्षरging_current(pchg, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		वापस lp8788_get_अक्षरging_termination_voltage(pchg, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत bool lp8788_is_valid_अक्षरger_रेजिस्टर(u8 addr)
अणु
	वापस addr >= LP8788_CHG_START && addr <= LP8788_CHG_END;
पूर्ण

अटल पूर्णांक lp8788_update_अक्षरger_params(काष्ठा platक्रमm_device *pdev,
					काष्ठा lp8788_अक्षरger *pchg)
अणु
	काष्ठा lp8788 *lp = pchg->lp;
	काष्ठा lp8788_अक्षरger_platक्रमm_data *pdata = pchg->pdata;
	काष्ठा lp8788_chg_param *param;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!pdata || !pdata->chg_params) अणु
		dev_info(&pdev->dev, "skip updating charger parameters\n");
		वापस 0;
	पूर्ण

	/* settting अक्षरging parameters */
	क्रम (i = 0; i < pdata->num_chg_params; i++) अणु
		param = pdata->chg_params + i;

		अगर (lp8788_is_valid_अक्षरger_रेजिस्टर(param->addr)) अणु
			ret = lp8788_ग_लिखो_byte(lp, param->addr, param->val);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc lp8788_psy_अक्षरger_desc = अणु
	.name		= LP8788_CHARGER_NAME,
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= lp8788_अक्षरger_prop,
	.num_properties	= ARRAY_SIZE(lp8788_अक्षरger_prop),
	.get_property	= lp8788_अक्षरger_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc lp8788_psy_battery_desc = अणु
	.name		= LP8788_BATTERY_NAME,
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= lp8788_battery_prop,
	.num_properties	= ARRAY_SIZE(lp8788_battery_prop),
	.get_property	= lp8788_battery_get_property,
पूर्ण;

अटल व्योम lp8788_psy_unरेजिस्टर(काष्ठा lp8788_अक्षरger *pchg)
अणु
	घातer_supply_unरेजिस्टर(pchg->battery);
	घातer_supply_unरेजिस्टर(pchg->अक्षरger);
पूर्ण

अटल व्योम lp8788_अक्षरger_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lp8788_अक्षरger *pchg =
		container_of(work, काष्ठा lp8788_अक्षरger, अक्षरger_work);
	काष्ठा lp8788_अक्षरger_platक्रमm_data *pdata = pchg->pdata;
	क्रमागत lp8788_अक्षरger_event event = lp8788_is_अक्षरger_detected(pchg);

	pdata->अक्षरger_event(pchg->lp, event);
पूर्ण

अटल bool lp8788_find_irq_id(काष्ठा lp8788_अक्षरger *pchg, पूर्णांक virq, पूर्णांक *id)
अणु
	bool found = false;
	पूर्णांक i;

	क्रम (i = 0; i < pchg->num_irqs; i++) अणु
		अगर (pchg->irqs[i].virq == virq) अणु
			*id = pchg->irqs[i].which;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल irqवापस_t lp8788_अक्षरger_irq_thपढ़ो(पूर्णांक virq, व्योम *ptr)
अणु
	काष्ठा lp8788_अक्षरger *pchg = ptr;
	काष्ठा lp8788_अक्षरger_platक्रमm_data *pdata = pchg->pdata;
	पूर्णांक id = -1;

	अगर (!lp8788_find_irq_id(pchg, virq, &id))
		वापस IRQ_NONE;

	चयन (id) अणु
	हाल LP8788_INT_CHG_INPUT_STATE:
	हाल LP8788_INT_CHG_STATE:
	हाल LP8788_INT_EOC:
	हाल LP8788_INT_BATT_LOW:
	हाल LP8788_INT_NO_BATT:
		घातer_supply_changed(pchg->अक्षरger);
		घातer_supply_changed(pchg->battery);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* report अक्षरger dectection event अगर used */
	अगर (!pdata)
		जाओ irq_handled;

	अगर (pdata->अक्षरger_event && id == LP8788_INT_CHG_INPUT_STATE)
		schedule_work(&pchg->अक्षरger_work);

irq_handled:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lp8788_set_irqs(काष्ठा platक्रमm_device *pdev,
			काष्ठा lp8788_अक्षरger *pchg, स्थिर अक्षर *name)
अणु
	काष्ठा resource *r;
	काष्ठा irq_करोमुख्य *irqdm = pchg->lp->irqdm;
	पूर्णांक irq_start;
	पूर्णांक irq_end;
	पूर्णांक virq;
	पूर्णांक nr_irq;
	पूर्णांक i;
	पूर्णांक ret;

	/* no error even अगर no irq resource */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, name);
	अगर (!r)
		वापस 0;

	irq_start = r->start;
	irq_end = r->end;

	क्रम (i = irq_start; i <= irq_end; i++) अणु
		nr_irq = pchg->num_irqs;

		virq = irq_create_mapping(irqdm, i);
		pchg->irqs[nr_irq].virq = virq;
		pchg->irqs[nr_irq].which = i;
		pchg->num_irqs++;

		ret = request_thपढ़ोed_irq(virq, शून्य,
					lp8788_अक्षरger_irq_thपढ़ो,
					IRQF_ONESHOT, name, pchg);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (i <= irq_end)
		जाओ err_मुक्त_irq;

	वापस 0;

err_मुक्त_irq:
	क्रम (i = 0; i < pchg->num_irqs; i++)
		मुक्त_irq(pchg->irqs[i].virq, pchg);
	वापस ret;
पूर्ण

अटल पूर्णांक lp8788_irq_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				काष्ठा lp8788_अक्षरger *pchg)
अणु
	स्थिर अक्षर *name[] = अणु
		LP8788_CHG_IRQ, LP8788_PRSW_IRQ, LP8788_BATT_IRQ
	पूर्ण;
	पूर्णांक i;
	पूर्णांक ret;

	INIT_WORK(&pchg->अक्षरger_work, lp8788_अक्षरger_event);
	pchg->num_irqs = 0;

	क्रम (i = 0; i < ARRAY_SIZE(name); i++) अणु
		ret = lp8788_set_irqs(pdev, pchg, name[i]);
		अगर (ret) अणु
			dev_warn(&pdev->dev, "irq setup failed: %s\n", name[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pchg->num_irqs > LP8788_MAX_CHG_IRQS) अणु
		dev_err(&pdev->dev, "invalid total number of irqs: %d\n",
			pchg->num_irqs);
		वापस -EINVAL;
	पूर्ण


	वापस 0;
पूर्ण

अटल व्योम lp8788_irq_unरेजिस्टर(काष्ठा platक्रमm_device *pdev,
				  काष्ठा lp8788_अक्षरger *pchg)
अणु
	पूर्णांक i;
	पूर्णांक irq;

	क्रम (i = 0; i < pchg->num_irqs; i++) अणु
		irq = pchg->irqs[i].virq;
		अगर (!irq)
			जारी;

		मुक्त_irq(irq, pchg);
	पूर्ण
पूर्ण

अटल व्योम lp8788_setup_adc_channel(काष्ठा device *dev,
				काष्ठा lp8788_अक्षरger *pchg)
अणु
	काष्ठा lp8788_अक्षरger_platक्रमm_data *pdata = pchg->pdata;
	काष्ठा iio_channel *chan;

	अगर (!pdata)
		वापस;

	/* ADC channel क्रम battery voltage */
	chan = devm_iio_channel_get(dev, pdata->adc_vbatt);
	pchg->chan[LP8788_VBATT] = IS_ERR(chan) ? शून्य : chan;

	/* ADC channel क्रम battery temperature */
	chan = devm_iio_channel_get(dev, pdata->adc_batt_temp);
	pchg->chan[LP8788_BATT_TEMP] = IS_ERR(chan) ? शून्य : chan;
पूर्ण

अटल sमाप_प्रकार lp8788_show_अक्षरger_status(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lp8788_अक्षरger *pchg = dev_get_drvdata(dev);
	क्रमागत lp8788_अक्षरging_state state;
	अटल स्थिर अक्षर * स्थिर desc[LP8788_MAX_CHG_STATE] = अणु
		[LP8788_OFF] = "CHARGER OFF",
		[LP8788_WARM_UP] = "WARM UP",
		[LP8788_LOW_INPUT] = "LOW INPUT STATE",
		[LP8788_PRECHARGE] = "CHARGING - PRECHARGE",
		[LP8788_CC] = "CHARGING - CC",
		[LP8788_CV] = "CHARGING - CV",
		[LP8788_MAINTEन_अंकCE] = "NO CHARGING - MAINTENANCE",
		[LP8788_BATTERY_FAULT] = "BATTERY FAULT",
		[LP8788_SYSTEM_SUPPORT] = "SYSTEM SUPPORT",
		[LP8788_HIGH_CURRENT] = "HIGH CURRENT",
	पूर्ण;
	u8 data;

	lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	state = (data & LP8788_CHG_STATE_M) >> LP8788_CHG_STATE_S;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", desc[state]);
पूर्ण

अटल sमाप_प्रकार lp8788_show_eoc_समय(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lp8788_अक्षरger *pchg = dev_get_drvdata(dev);
	अटल स्थिर अक्षर * स्थिर sसमय[] = अणु
		"400ms", "5min", "10min", "15min",
		"20min", "25min", "30min", "No timeout"
	पूर्ण;
	u8 val;

	lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_EOC, &val);
	val = (val & LP8788_CHG_EOC_TIME_M) >> LP8788_CHG_EOC_TIME_S;

	वापस scnम_लिखो(buf, PAGE_SIZE, "End Of Charge Time: %s\n",
			sसमय[val]);
पूर्ण

अटल sमाप_प्रकार lp8788_show_eoc_level(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lp8788_अक्षरger *pchg = dev_get_drvdata(dev);
	अटल स्थिर अक्षर * स्थिर असल_level[] = अणु
			"25mA", "49mA", "75mA", "98mA"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर relative_level[] = अणु
			"5%", "10%", "15%", "20%"
	पूर्ण;
	स्थिर अक्षर *level;
	u8 val;
	u8 mode;

	lp8788_पढ़ो_byte(pchg->lp, LP8788_CHG_EOC, &val);

	mode = val & LP8788_CHG_EOC_MODE_M;
	val = (val & LP8788_CHG_EOC_LEVEL_M) >> LP8788_CHG_EOC_LEVEL_S;
	level = mode ? असल_level[val] : relative_level[val];

	वापस scnम_लिखो(buf, PAGE_SIZE, "End Of Charge Level: %s\n", level);
पूर्ण

अटल DEVICE_ATTR(अक्षरger_status, S_IRUSR, lp8788_show_अक्षरger_status, शून्य);
अटल DEVICE_ATTR(eoc_समय, S_IRUSR, lp8788_show_eoc_समय, शून्य);
अटल DEVICE_ATTR(eoc_level, S_IRUSR, lp8788_show_eoc_level, शून्य);

अटल काष्ठा attribute *lp8788_अक्षरger_sysfs_attrs[] = अणु
	&dev_attr_अक्षरger_status.attr,
	&dev_attr_eoc_समय.attr,
	&dev_attr_eoc_level.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(lp8788_अक्षरger_sysfs);

अटल पूर्णांक lp8788_psy_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				काष्ठा lp8788_अक्षरger *pchg)
अणु
	काष्ठा घातer_supply_config अक्षरger_cfg = अणुपूर्ण;

	अक्षरger_cfg.attr_grp = lp8788_अक्षरger_sysfs_groups;
	अक्षरger_cfg.supplied_to = battery_supplied_to;
	अक्षरger_cfg.num_supplicants = ARRAY_SIZE(battery_supplied_to);

	pchg->अक्षरger = घातer_supply_रेजिस्टर(&pdev->dev,
					      &lp8788_psy_अक्षरger_desc,
					      &अक्षरger_cfg);
	अगर (IS_ERR(pchg->अक्षरger))
		वापस -EPERM;

	pchg->battery = घातer_supply_रेजिस्टर(&pdev->dev,
					      &lp8788_psy_battery_desc, शून्य);
	अगर (IS_ERR(pchg->battery)) अणु
		घातer_supply_unरेजिस्टर(pchg->अक्षरger);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lp8788_अक्षरger *pchg;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pchg = devm_kzalloc(dev, माप(काष्ठा lp8788_अक्षरger), GFP_KERNEL);
	अगर (!pchg)
		वापस -ENOMEM;

	pchg->lp = lp;
	pchg->pdata = lp->pdata ? lp->pdata->chg_pdata : शून्य;
	platक्रमm_set_drvdata(pdev, pchg);

	ret = lp8788_update_अक्षरger_params(pdev, pchg);
	अगर (ret)
		वापस ret;

	lp8788_setup_adc_channel(&pdev->dev, pchg);

	ret = lp8788_psy_रेजिस्टर(pdev, pchg);
	अगर (ret)
		वापस ret;

	ret = lp8788_irq_रेजिस्टर(pdev, pchg);
	अगर (ret)
		dev_warn(dev, "failed to register charger irq: %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788_अक्षरger *pchg = platक्रमm_get_drvdata(pdev);

	flush_work(&pchg->अक्षरger_work);
	lp8788_irq_unरेजिस्टर(pdev, pchg);
	lp8788_psy_unरेजिस्टर(pchg);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_अक्षरger_driver = अणु
	.probe = lp8788_अक्षरger_probe,
	.हटाओ = lp8788_अक्षरger_हटाओ,
	.driver = अणु
		.name = LP8788_DEV_CHARGER,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp8788_अक्षरger_driver);

MODULE_DESCRIPTION("TI LP8788 Charger Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-charger");
