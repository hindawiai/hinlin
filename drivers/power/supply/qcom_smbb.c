<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2014, Sony Mobile Communications Inc.
 *
 * This driver is क्रम the multi-block Switch-Mode Battery Charger and Boost
 * (SMBB) hardware, found in Qualcomm PM8941 PMICs.  The अक्षरger is an
 * पूर्णांकegrated, single-cell lithium-ion battery अक्षरger.
 *
 * Sub-components:
 *  - Charger core
 *  - Buck
 *  - DC अक्षरge-path
 *  - USB अक्षरge-path
 *  - Battery पूर्णांकerface
 *  - Boost (not implemented)
 *  - Misc
 *  - HF-Buck
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/regulator/driver.h>

#घोषणा SMBB_CHG_VMAX		0x040
#घोषणा SMBB_CHG_VSAFE		0x041
#घोषणा SMBB_CHG_CFG		0x043
#घोषणा SMBB_CHG_IMAX		0x044
#घोषणा SMBB_CHG_ISAFE		0x045
#घोषणा SMBB_CHG_VIN_MIN	0x047
#घोषणा SMBB_CHG_CTRL		0x049
#घोषणा CTRL_EN			BIT(7)
#घोषणा SMBB_CHG_VBAT_WEAK	0x052
#घोषणा SMBB_CHG_IBAT_TERM_CHG	0x05b
#घोषणा IBAT_TERM_CHG_IEOC	BIT(7)
#घोषणा IBAT_TERM_CHG_IEOC_BMS	BIT(7)
#घोषणा IBAT_TERM_CHG_IEOC_CHG	0
#घोषणा SMBB_CHG_VBAT_DET	0x05d
#घोषणा SMBB_CHG_TCHG_MAX_EN	0x060
#घोषणा TCHG_MAX_EN		BIT(7)
#घोषणा SMBB_CHG_WDOG_TIME	0x062
#घोषणा SMBB_CHG_WDOG_EN	0x065
#घोषणा WDOG_EN			BIT(7)

#घोषणा SMBB_BUCK_REG_MODE	0x174
#घोषणा BUCK_REG_MODE		BIT(0)
#घोषणा BUCK_REG_MODE_VBAT	BIT(0)
#घोषणा BUCK_REG_MODE_VSYS	0

#घोषणा SMBB_BAT_PRES_STATUS	0x208
#घोषणा PRES_STATUS_BAT_PRES	BIT(7)
#घोषणा SMBB_BAT_TEMP_STATUS	0x209
#घोषणा TEMP_STATUS_OK		BIT(7)
#घोषणा TEMP_STATUS_HOT		BIT(6)
#घोषणा SMBB_BAT_BTC_CTRL	0x249
#घोषणा BTC_CTRL_COMP_EN	BIT(7)
#घोषणा BTC_CTRL_COLD_EXT	BIT(1)
#घोषणा BTC_CTRL_HOT_EXT_N	BIT(0)

#घोषणा SMBB_USB_IMAX		0x344
#घोषणा SMBB_USB_OTG_CTL	0x348
#घोषणा OTG_CTL_EN		BIT(0)
#घोषणा SMBB_USB_ENUM_TIMER_STOP 0x34e
#घोषणा ENUM_TIMER_STOP		BIT(0)
#घोषणा SMBB_USB_SEC_ACCESS	0x3d0
#घोषणा SEC_ACCESS_MAGIC	0xa5
#घोषणा SMBB_USB_REV_BST	0x3ed
#घोषणा REV_BST_CHG_GONE	BIT(7)

#घोषणा SMBB_DC_IMAX		0x444

#घोषणा SMBB_MISC_REV2		0x601
#घोषणा SMBB_MISC_BOOT_DONE	0x642
#घोषणा BOOT_DONE		BIT(7)

#घोषणा STATUS_USBIN_VALID	BIT(0) /* USB connection is valid */
#घोषणा STATUS_DCIN_VALID	BIT(1) /* DC connection is valid */
#घोषणा STATUS_BAT_HOT		BIT(2) /* Battery temp 1=Hot, 0=Cold */
#घोषणा STATUS_BAT_OK		BIT(3) /* Battery temp OK */
#घोषणा STATUS_BAT_PRESENT	BIT(4) /* Battery is present */
#घोषणा STATUS_CHG_DONE		BIT(5) /* Charge cycle is complete */
#घोषणा STATUS_CHG_TRKL		BIT(6) /* Trickle अक्षरging */
#घोषणा STATUS_CHG_FAST		BIT(7) /* Fast अक्षरging */
#घोषणा STATUS_CHG_GONE		BIT(8) /* No अक्षरger is connected */

क्रमागत smbb_attr अणु
	ATTR_BAT_ISAFE,
	ATTR_BAT_IMAX,
	ATTR_USBIN_IMAX,
	ATTR_DCIN_IMAX,
	ATTR_BAT_VSAFE,
	ATTR_BAT_VMAX,
	ATTR_BAT_VMIN,
	ATTR_CHG_VDET,
	ATTR_VIN_MIN,
	_ATTR_CNT,
पूर्ण;

काष्ठा smbb_अक्षरger अणु
	अचिन्हित पूर्णांक revision;
	अचिन्हित पूर्णांक addr;
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;

	bool dc_disabled;
	bool jeita_ext_temp;
	अचिन्हित दीर्घ status;
	काष्ठा mutex statlock;

	अचिन्हित पूर्णांक attr[_ATTR_CNT];

	काष्ठा घातer_supply *usb_psy;
	काष्ठा घातer_supply *dc_psy;
	काष्ठा घातer_supply *bat_psy;
	काष्ठा regmap *regmap;

	काष्ठा regulator_desc otg_rdesc;
	काष्ठा regulator_dev *otg_reg;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक smbb_usb_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_NONE,
पूर्ण;

अटल पूर्णांक smbb_vbat_weak_fn(अचिन्हित पूर्णांक index)
अणु
	वापस 2100000 + index * 100000;
पूर्ण

अटल पूर्णांक smbb_vin_fn(अचिन्हित पूर्णांक index)
अणु
	अगर (index > 42)
		वापस 5600000 + (index - 43) * 200000;
	वापस 3400000 + index * 50000;
पूर्ण

अटल पूर्णांक smbb_vmax_fn(अचिन्हित पूर्णांक index)
अणु
	वापस 3240000 + index * 10000;
पूर्ण

अटल पूर्णांक smbb_vbat_det_fn(अचिन्हित पूर्णांक index)
अणु
	वापस 3240000 + index * 20000;
पूर्ण

अटल पूर्णांक smbb_imax_fn(अचिन्हित पूर्णांक index)
अणु
	अगर (index < 2)
		वापस 100000 + index * 50000;
	वापस index * 100000;
पूर्ण

अटल पूर्णांक smbb_bat_imax_fn(अचिन्हित पूर्णांक index)
अणु
	वापस index * 50000;
पूर्ण

अटल अचिन्हित पूर्णांक smbb_hw_lookup(अचिन्हित पूर्णांक val, पूर्णांक (*fn)(अचिन्हित पूर्णांक))
अणु
	अचिन्हित पूर्णांक widx;
	अचिन्हित पूर्णांक sel;

	क्रम (widx = sel = 0; (*fn)(widx) <= val; ++widx)
		sel = widx;

	वापस sel;
पूर्ण

अटल स्थिर काष्ठा smbb_अक्षरger_attr अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक safe_reg;
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक fail_ok;
	पूर्णांक (*hw_fn)(अचिन्हित पूर्णांक);
पूर्ण smbb_अक्षरger_attrs[] = अणु
	[ATTR_BAT_ISAFE] = अणु
		.name = "qcom,fast-charge-safe-current",
		.reg = SMBB_CHG_ISAFE,
		.max = 3000000,
		.min = 200000,
		.hw_fn = smbb_bat_imax_fn,
		.fail_ok = 1,
	पूर्ण,
	[ATTR_BAT_IMAX] = अणु
		.name = "qcom,fast-charge-current-limit",
		.reg = SMBB_CHG_IMAX,
		.safe_reg = SMBB_CHG_ISAFE,
		.max = 3000000,
		.min = 200000,
		.hw_fn = smbb_bat_imax_fn,
	पूर्ण,
	[ATTR_DCIN_IMAX] = अणु
		.name = "qcom,dc-current-limit",
		.reg = SMBB_DC_IMAX,
		.max = 2500000,
		.min = 100000,
		.hw_fn = smbb_imax_fn,
	पूर्ण,
	[ATTR_BAT_VSAFE] = अणु
		.name = "qcom,fast-charge-safe-voltage",
		.reg = SMBB_CHG_VSAFE,
		.max = 5000000,
		.min = 3240000,
		.hw_fn = smbb_vmax_fn,
		.fail_ok = 1,
	पूर्ण,
	[ATTR_BAT_VMAX] = अणु
		.name = "qcom,fast-charge-high-threshold-voltage",
		.reg = SMBB_CHG_VMAX,
		.safe_reg = SMBB_CHG_VSAFE,
		.max = 5000000,
		.min = 3240000,
		.hw_fn = smbb_vmax_fn,
	पूर्ण,
	[ATTR_BAT_VMIN] = अणु
		.name = "qcom,fast-charge-low-threshold-voltage",
		.reg = SMBB_CHG_VBAT_WEAK,
		.max = 3600000,
		.min = 2100000,
		.hw_fn = smbb_vbat_weak_fn,
	पूर्ण,
	[ATTR_CHG_VDET] = अणु
		.name = "qcom,auto-recharge-threshold-voltage",
		.reg = SMBB_CHG_VBAT_DET,
		.max = 5000000,
		.min = 3240000,
		.hw_fn = smbb_vbat_det_fn,
	पूर्ण,
	[ATTR_VIN_MIN] = अणु
		.name = "qcom,minimum-input-voltage",
		.reg = SMBB_CHG_VIN_MIN,
		.max = 9600000,
		.min = 4200000,
		.hw_fn = smbb_vin_fn,
	पूर्ण,
	[ATTR_USBIN_IMAX] = अणु
		.name = "usb-charge-current-limit",
		.reg = SMBB_USB_IMAX,
		.max = 2500000,
		.min = 100000,
		.hw_fn = smbb_imax_fn,
	पूर्ण,
पूर्ण;

अटल पूर्णांक smbb_अक्षरger_attr_ग_लिखो(काष्ठा smbb_अक्षरger *chg,
		क्रमागत smbb_attr which, अचिन्हित पूर्णांक val)
अणु
	स्थिर काष्ठा smbb_अक्षरger_attr *prop;
	अचिन्हित पूर्णांक wval;
	अचिन्हित पूर्णांक out;
	पूर्णांक rc;

	prop = &smbb_अक्षरger_attrs[which];

	अगर (val > prop->max || val < prop->min) अणु
		dev_err(chg->dev, "value out of range for %s [%u:%u]\n",
			prop->name, prop->min, prop->max);
		वापस -EINVAL;
	पूर्ण

	अगर (prop->safe_reg) अणु
		rc = regmap_पढ़ो(chg->regmap,
				chg->addr + prop->safe_reg, &wval);
		अगर (rc) अणु
			dev_err(chg->dev,
				"unable to read safe value for '%s'\n",
				prop->name);
			वापस rc;
		पूर्ण

		wval = prop->hw_fn(wval);

		अगर (val > wval) अणु
			dev_warn(chg->dev,
				"%s above safe value, clamping at %u\n",
				prop->name, wval);
			val = wval;
		पूर्ण
	पूर्ण

	wval = smbb_hw_lookup(val, prop->hw_fn);

	rc = regmap_ग_लिखो(chg->regmap, chg->addr + prop->reg, wval);
	अगर (rc) अणु
		dev_err(chg->dev, "unable to update %s", prop->name);
		वापस rc;
	पूर्ण
	out = prop->hw_fn(wval);
	अगर (out != val) अणु
		dev_warn(chg->dev,
			"%s inaccurate, rounded to %u\n",
			prop->name, out);
	पूर्ण

	dev_dbg(chg->dev, "%s <= %d\n", prop->name, out);

	chg->attr[which] = out;

	वापस 0;
पूर्ण

अटल पूर्णांक smbb_अक्षरger_attr_पढ़ो(काष्ठा smbb_अक्षरger *chg,
		क्रमागत smbb_attr which)
अणु
	स्थिर काष्ठा smbb_अक्षरger_attr *prop;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	prop = &smbb_अक्षरger_attrs[which];

	rc = regmap_पढ़ो(chg->regmap, chg->addr + prop->reg, &val);
	अगर (rc) अणु
		dev_err(chg->dev, "failed to read %s\n", prop->name);
		वापस rc;
	पूर्ण
	val = prop->hw_fn(val);
	dev_dbg(chg->dev, "%s => %d\n", prop->name, val);

	chg->attr[which] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक smbb_अक्षरger_attr_parse(काष्ठा smbb_अक्षरger *chg,
		क्रमागत smbb_attr which)
अणु
	स्थिर काष्ठा smbb_अक्षरger_attr *prop;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	prop = &smbb_अक्षरger_attrs[which];

	rc = of_property_पढ़ो_u32(chg->dev->of_node, prop->name, &val);
	अगर (rc == 0) अणु
		rc = smbb_अक्षरger_attr_ग_लिखो(chg, which, val);
		अगर (!rc || !prop->fail_ok)
			वापस rc;
	पूर्ण
	वापस smbb_अक्षरger_attr_पढ़ो(chg, which);
पूर्ण

अटल व्योम smbb_set_line_flag(काष्ठा smbb_अक्षरger *chg, पूर्णांक irq, पूर्णांक flag)
अणु
	bool state;
	पूर्णांक ret;

	ret = irq_get_irqchip_state(irq, IRQCHIP_STATE_LINE_LEVEL, &state);
	अगर (ret < 0) अणु
		dev_err(chg->dev, "failed to read irq line\n");
		वापस;
	पूर्ण

	mutex_lock(&chg->statlock);
	अगर (state)
		chg->status |= flag;
	अन्यथा
		chg->status &= ~flag;
	mutex_unlock(&chg->statlock);

	dev_dbg(chg->dev, "status = %03lx\n", chg->status);
पूर्ण

अटल irqवापस_t smbb_usb_valid_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_USBIN_VALID);
	extcon_set_state_sync(chg->edev, EXTCON_USB,
				chg->status & STATUS_USBIN_VALID);
	घातer_supply_changed(chg->usb_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_dc_valid_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_DCIN_VALID);
	अगर (!chg->dc_disabled)
		घातer_supply_changed(chg->dc_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_bat_temp_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	rc = regmap_पढ़ो(chg->regmap, chg->addr + SMBB_BAT_TEMP_STATUS, &val);
	अगर (rc)
		वापस IRQ_HANDLED;

	mutex_lock(&chg->statlock);
	अगर (val & TEMP_STATUS_OK) अणु
		chg->status |= STATUS_BAT_OK;
	पूर्ण अन्यथा अणु
		chg->status &= ~STATUS_BAT_OK;
		अगर (val & TEMP_STATUS_HOT)
			chg->status |= STATUS_BAT_HOT;
	पूर्ण
	mutex_unlock(&chg->statlock);

	घातer_supply_changed(chg->bat_psy);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_bat_present_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_BAT_PRESENT);
	घातer_supply_changed(chg->bat_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_chg_करोne_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_CHG_DONE);
	घातer_supply_changed(chg->bat_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_chg_gone_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_CHG_GONE);
	घातer_supply_changed(chg->bat_psy);
	घातer_supply_changed(chg->usb_psy);
	अगर (!chg->dc_disabled)
		घातer_supply_changed(chg->dc_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_chg_fast_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_CHG_FAST);
	घातer_supply_changed(chg->bat_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t smbb_chg_trkl_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा smbb_अक्षरger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_CHG_TRKL);
	घातer_supply_changed(chg->bat_psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा smbb_irq अणु
	स्थिर अक्षर *name;
	irqवापस_t (*handler)(पूर्णांक, व्योम *);
पूर्ण smbb_अक्षरger_irqs[] = अणु
	अणु "chg-done", smbb_chg_करोne_handler पूर्ण,
	अणु "chg-fast", smbb_chg_fast_handler पूर्ण,
	अणु "chg-trkl", smbb_chg_trkl_handler पूर्ण,
	अणु "bat-temp-ok", smbb_bat_temp_handler पूर्ण,
	अणु "bat-present", smbb_bat_present_handler पूर्ण,
	अणु "chg-gone", smbb_chg_gone_handler पूर्ण,
	अणु "usb-valid", smbb_usb_valid_handler पूर्ण,
	अणु "dc-valid", smbb_dc_valid_handler पूर्ण,
पूर्ण;

अटल पूर्णांक smbb_usbin_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smbb_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक rc = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		mutex_lock(&chg->statlock);
		val->पूर्णांकval = !(chg->status & STATUS_CHG_GONE) &&
				(chg->status & STATUS_USBIN_VALID);
		mutex_unlock(&chg->statlock);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		val->पूर्णांकval = chg->attr[ATTR_USBIN_IMAX];
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX:
		val->पूर्णांकval = 2500000;
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smbb_usbin_set_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smbb_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक rc;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		rc = smbb_अक्षरger_attr_ग_लिखो(chg, ATTR_USBIN_IMAX,
				val->पूर्णांकval);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smbb_dcin_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smbb_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक rc = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		mutex_lock(&chg->statlock);
		val->पूर्णांकval = !(chg->status & STATUS_CHG_GONE) &&
				(chg->status & STATUS_DCIN_VALID);
		mutex_unlock(&chg->statlock);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		val->पूर्णांकval = chg->attr[ATTR_DCIN_IMAX];
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX:
		val->पूर्णांकval = 2500000;
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smbb_dcin_set_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smbb_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक rc;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		rc = smbb_अक्षरger_attr_ग_लिखो(chg, ATTR_DCIN_IMAX,
				val->पूर्णांकval);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smbb_अक्षरger_writable_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp)
अणु
	वापस psp == POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT;
पूर्ण

अटल पूर्णांक smbb_battery_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smbb_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	अचिन्हित दीर्घ status;
	पूर्णांक rc = 0;

	mutex_lock(&chg->statlock);
	status = chg->status;
	mutex_unlock(&chg->statlock);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (status & STATUS_CHG_GONE)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (!(status & (STATUS_DCIN_VALID | STATUS_USBIN_VALID)))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (status & STATUS_CHG_DONE)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा अगर (!(status & STATUS_BAT_OK))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (status & (STATUS_CHG_FAST | STATUS_CHG_TRKL))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा /* everything is ok क्रम अक्षरging, but we are not... */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (status & STATUS_BAT_OK)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अन्यथा अगर (status & STATUS_BAT_HOT)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_COLD;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		अगर (status & STATUS_CHG_FAST)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अन्यथा अगर (status & STATUS_CHG_TRKL)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!(status & STATUS_BAT_PRESENT);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		val->पूर्णांकval = chg->attr[ATTR_BAT_IMAX];
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		val->पूर्णांकval = chg->attr[ATTR_BAT_VMAX];
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		/* this अक्षरger is a single-cell lithium-ion battery अक्षरger
		* only.  If you hook up some other technology, there will be
		* fireworks.
		*/
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = 3000000; /* single-cell li-ion low end */
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smbb_battery_set_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smbb_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक rc;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		rc = smbb_अक्षरger_attr_ग_लिखो(chg, ATTR_BAT_IMAX, val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		rc = smbb_अक्षरger_attr_ग_लिखो(chg, ATTR_BAT_VMAX, val->पूर्णांकval);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smbb_battery_writable_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_property smbb_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX,
पूर्ण;

अटल क्रमागत घातer_supply_property smbb_battery_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_TECHNOLOGY,
पूर्ण;

अटल स्थिर काष्ठा reg_off_mask_शेष अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक value;
	अचिन्हित पूर्णांक rev_mask;
पूर्ण smbb_अक्षरger_setup[] = अणु
	/* The bootloader is supposed to set this... make sure anyway. */
	अणु SMBB_MISC_BOOT_DONE, BOOT_DONE, BOOT_DONE पूर्ण,

	/* Disable software समयr */
	अणु SMBB_CHG_TCHG_MAX_EN, TCHG_MAX_EN, 0 पूर्ण,

	/* Clear and disable watchकरोg */
	अणु SMBB_CHG_WDOG_TIME, 0xff, 160 पूर्ण,
	अणु SMBB_CHG_WDOG_EN, WDOG_EN, 0 पूर्ण,

	/* Use अक्षरger based EoC detection */
	अणु SMBB_CHG_IBAT_TERM_CHG, IBAT_TERM_CHG_IEOC, IBAT_TERM_CHG_IEOC_CHG पूर्ण,

	/* Disable GSM PA load adjusपंचांगent.
	* The PA संकेत is incorrectly connected on v2.
	*/
	अणु SMBB_CHG_CFG, 0xff, 0x00, BIT(3) पूर्ण,

	/* Use VBAT (not VSYS) to compensate क्रम IR drop during fast अक्षरging */
	अणु SMBB_BUCK_REG_MODE, BUCK_REG_MODE, BUCK_REG_MODE_VBAT पूर्ण,

	/* Enable battery temperature comparators */
	अणु SMBB_BAT_BTC_CTRL, BTC_CTRL_COMP_EN, BTC_CTRL_COMP_EN पूर्ण,

	/* Stop USB क्रमागतeration समयr */
	अणु SMBB_USB_ENUM_TIMER_STOP, ENUM_TIMER_STOP, ENUM_TIMER_STOP पूर्ण,

#अगर 0 /* FIXME supposedly only to disable hardware ARB termination */
	अणु SMBB_USB_SEC_ACCESS, SEC_ACCESS_MAGIC पूर्ण,
	अणु SMBB_USB_REV_BST, 0xff, REV_BST_CHG_GONE पूर्ण,
#पूर्ण_अगर

	/* Stop USB क्रमागतeration समयr, again */
	अणु SMBB_USB_ENUM_TIMER_STOP, ENUM_TIMER_STOP, ENUM_TIMER_STOP पूर्ण,

	/* Enable अक्षरging */
	अणु SMBB_CHG_CTRL, CTRL_EN, CTRL_EN पूर्ण,
पूर्ण;

अटल अक्षर *smbb_bअगर[] = अणु "smbb-bif" पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bat_psy_desc = अणु
	.name = "smbb-bif",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = smbb_battery_properties,
	.num_properties = ARRAY_SIZE(smbb_battery_properties),
	.get_property = smbb_battery_get_property,
	.set_property = smbb_battery_set_property,
	.property_is_ग_लिखोable = smbb_battery_writable_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc usb_psy_desc = अणु
	.name = "smbb-usbin",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = smbb_अक्षरger_properties,
	.num_properties = ARRAY_SIZE(smbb_अक्षरger_properties),
	.get_property = smbb_usbin_get_property,
	.set_property = smbb_usbin_set_property,
	.property_is_ग_लिखोable = smbb_अक्षरger_writable_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc dc_psy_desc = अणु
	.name = "smbb-dcin",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = smbb_अक्षरger_properties,
	.num_properties = ARRAY_SIZE(smbb_अक्षरger_properties),
	.get_property = smbb_dcin_get_property,
	.set_property = smbb_dcin_set_property,
	.property_is_ग_लिखोable = smbb_अक्षरger_writable_property,
पूर्ण;

अटल पूर्णांक smbb_chg_otg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा smbb_अक्षरger *chg = rdev_get_drvdata(rdev);
	पूर्णांक rc;

	rc = regmap_update_bits(chg->regmap, chg->addr + SMBB_USB_OTG_CTL,
				OTG_CTL_EN, OTG_CTL_EN);
	अगर (rc)
		dev_err(chg->dev, "failed to update OTG_CTL\n");
	वापस rc;
पूर्ण

अटल पूर्णांक smbb_chg_otg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा smbb_अक्षरger *chg = rdev_get_drvdata(rdev);
	पूर्णांक rc;

	rc = regmap_update_bits(chg->regmap, chg->addr + SMBB_USB_OTG_CTL,
				OTG_CTL_EN, 0);
	अगर (rc)
		dev_err(chg->dev, "failed to update OTG_CTL\n");
	वापस rc;
पूर्ण

अटल पूर्णांक smbb_chg_otg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा smbb_अक्षरger *chg = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक value = 0;
	पूर्णांक rc;

	rc = regmap_पढ़ो(chg->regmap, chg->addr + SMBB_USB_OTG_CTL, &value);
	अगर (rc)
		dev_err(chg->dev, "failed to read OTG_CTL\n");

	वापस !!(value & OTG_CTL_EN);
पूर्ण

अटल स्थिर काष्ठा regulator_ops smbb_chg_otg_ops = अणु
	.enable = smbb_chg_otg_enable,
	.disable = smbb_chg_otg_disable,
	.is_enabled = smbb_chg_otg_is_enabled,
पूर्ण;

अटल पूर्णांक smbb_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config bat_cfg = अणुपूर्ण;
	काष्ठा घातer_supply_config usb_cfg = अणुपूर्ण;
	काष्ठा घातer_supply_config dc_cfg = अणुपूर्ण;
	काष्ठा smbb_अक्षरger *chg;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक rc, i;

	chg = devm_kzalloc(&pdev->dev, माप(*chg), GFP_KERNEL);
	अगर (!chg)
		वापस -ENOMEM;

	chg->dev = &pdev->dev;
	mutex_init(&chg->statlock);

	chg->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!chg->regmap) अणु
		dev_err(&pdev->dev, "failed to locate regmap\n");
		वापस -ENODEV;
	पूर्ण

	rc = of_property_पढ़ो_u32(pdev->dev.of_node, "reg", &chg->addr);
	अगर (rc) अणु
		dev_err(&pdev->dev, "missing or invalid 'reg' property\n");
		वापस rc;
	पूर्ण

	rc = regmap_पढ़ो(chg->regmap, chg->addr + SMBB_MISC_REV2, &chg->revision);
	अगर (rc) अणु
		dev_err(&pdev->dev, "unable to read revision\n");
		वापस rc;
	पूर्ण

	chg->revision += 1;
	अगर (chg->revision != 2 && chg->revision != 3) अणु
		dev_err(&pdev->dev, "v1 hardware not supported\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(&pdev->dev, "Initializing SMBB rev %u", chg->revision);

	chg->dc_disabled = of_property_पढ़ो_bool(pdev->dev.of_node, "qcom,disable-dc");

	क्रम (i = 0; i < _ATTR_CNT; ++i) अणु
		rc = smbb_अक्षरger_attr_parse(chg, i);
		अगर (rc) अणु
			dev_err(&pdev->dev, "failed to parse/apply settings\n");
			वापस rc;
		पूर्ण
	पूर्ण

	bat_cfg.drv_data = chg;
	bat_cfg.of_node = pdev->dev.of_node;
	chg->bat_psy = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						  &bat_psy_desc,
						  &bat_cfg);
	अगर (IS_ERR(chg->bat_psy)) अणु
		dev_err(&pdev->dev, "failed to register battery\n");
		वापस PTR_ERR(chg->bat_psy);
	पूर्ण

	usb_cfg.drv_data = chg;
	usb_cfg.supplied_to = smbb_bअगर;
	usb_cfg.num_supplicants = ARRAY_SIZE(smbb_bअगर);
	chg->usb_psy = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						  &usb_psy_desc,
						  &usb_cfg);
	अगर (IS_ERR(chg->usb_psy)) अणु
		dev_err(&pdev->dev, "failed to register USB power supply\n");
		वापस PTR_ERR(chg->usb_psy);
	पूर्ण

	chg->edev = devm_extcon_dev_allocate(&pdev->dev, smbb_usb_extcon_cable);
	अगर (IS_ERR(chg->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	rc = devm_extcon_dev_रेजिस्टर(&pdev->dev, chg->edev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		वापस rc;
	पूर्ण

	अगर (!chg->dc_disabled) अणु
		dc_cfg.drv_data = chg;
		dc_cfg.supplied_to = smbb_bअगर;
		dc_cfg.num_supplicants = ARRAY_SIZE(smbb_bअगर);
		chg->dc_psy = devm_घातer_supply_रेजिस्टर(&pdev->dev,
							 &dc_psy_desc,
							 &dc_cfg);
		अगर (IS_ERR(chg->dc_psy)) अणु
			dev_err(&pdev->dev, "failed to register DC power supply\n");
			वापस PTR_ERR(chg->dc_psy);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(smbb_अक्षरger_irqs); ++i) अणु
		पूर्णांक irq;

		irq = platक्रमm_get_irq_byname(pdev, smbb_अक्षरger_irqs[i].name);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "failed to get irq '%s'\n",
				smbb_अक्षरger_irqs[i].name);
			वापस irq;
		पूर्ण

		smbb_अक्षरger_irqs[i].handler(irq, chg);

		rc = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
				smbb_अक्षरger_irqs[i].handler, IRQF_ONESHOT,
				smbb_अक्षरger_irqs[i].name, chg);
		अगर (rc) अणु
			dev_err(&pdev->dev, "failed to request irq '%s'\n",
				smbb_अक्षरger_irqs[i].name);
			वापस rc;
		पूर्ण
	पूर्ण

	/*
	 * otg regulator is used to control VBUS voltage direction
	 * when USB चयनes between host and gadget mode
	 */
	chg->otg_rdesc.id = -1;
	chg->otg_rdesc.name = "otg-vbus";
	chg->otg_rdesc.ops = &smbb_chg_otg_ops;
	chg->otg_rdesc.owner = THIS_MODULE;
	chg->otg_rdesc.type = REGULATOR_VOLTAGE;
	chg->otg_rdesc.supply_name = "usb-otg-in";
	chg->otg_rdesc.of_match = "otg-vbus";

	config.dev = &pdev->dev;
	config.driver_data = chg;

	chg->otg_reg = devm_regulator_रेजिस्टर(&pdev->dev, &chg->otg_rdesc,
					       &config);
	अगर (IS_ERR(chg->otg_reg))
		वापस PTR_ERR(chg->otg_reg);

	chg->jeita_ext_temp = of_property_पढ़ो_bool(pdev->dev.of_node,
			"qcom,jeita-extended-temp-range");

	/* Set temperature range to [35%:70%] or [25%:80%] accordingly */
	rc = regmap_update_bits(chg->regmap, chg->addr + SMBB_BAT_BTC_CTRL,
			BTC_CTRL_COLD_EXT | BTC_CTRL_HOT_EXT_N,
			chg->jeita_ext_temp ?
				BTC_CTRL_COLD_EXT :
				BTC_CTRL_HOT_EXT_N);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"unable to set %s temperature range\n",
			chg->jeita_ext_temp ? "JEITA extended" : "normal");
		वापस rc;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(smbb_अक्षरger_setup); ++i) अणु
		स्थिर काष्ठा reg_off_mask_शेष *r = &smbb_अक्षरger_setup[i];

		अगर (r->rev_mask & BIT(chg->revision))
			जारी;

		rc = regmap_update_bits(chg->regmap, chg->addr + r->offset,
				r->mask, r->value);
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"unable to initializing charging, bailing\n");
			वापस rc;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, chg);

	वापस 0;
पूर्ण

अटल पूर्णांक smbb_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smbb_अक्षरger *chg;

	chg = platक्रमm_get_drvdata(pdev);

	regmap_update_bits(chg->regmap, chg->addr + SMBB_CHG_CTRL, CTRL_EN, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id smbb_अक्षरger_id_table[] = अणु
	अणु .compatible = "qcom,pm8941-charger" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, smbb_अक्षरger_id_table);

अटल काष्ठा platक्रमm_driver smbb_अक्षरger_driver = अणु
	.probe	  = smbb_अक्षरger_probe,
	.हटाओ	 = smbb_अक्षरger_हटाओ,
	.driver	 = अणु
		.name   = "qcom-smbb",
		.of_match_table = smbb_अक्षरger_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(smbb_अक्षरger_driver);

MODULE_DESCRIPTION("Qualcomm Switch-Mode Battery Charger and Boost driver");
MODULE_LICENSE("GPL v2");
