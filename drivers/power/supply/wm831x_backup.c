<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backup battery driver क्रम Wolfson Microelectronics wm831x PMICs
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/auxadc.h>
#समावेश <linux/mfd/wm831x/pmu.h>
#समावेश <linux/mfd/wm831x/pdata.h>

काष्ठा wm831x_backup अणु
	काष्ठा wm831x *wm831x;
	काष्ठा घातer_supply *backup;
	काष्ठा घातer_supply_desc backup_desc;
	अक्षर name[20];
पूर्ण;

अटल पूर्णांक wm831x_backup_पढ़ो_voltage(काष्ठा wm831x *wm831x,
				     क्रमागत wm831x_auxadc src,
				     जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;

	ret = wm831x_auxadc_पढ़ो_uv(wm831x, src);
	अगर (ret >= 0)
		val->पूर्णांकval = ret;

	वापस ret;
पूर्ण

/*********************************************************************
 *		Backup supply properties
 *********************************************************************/

अटल व्योम wm831x_config_backup(काष्ठा wm831x *wm831x)
अणु
	काष्ठा wm831x_pdata *wm831x_pdata = wm831x->dev->platक्रमm_data;
	काष्ठा wm831x_backup_pdata *pdata;
	पूर्णांक ret, reg;

	अगर (!wm831x_pdata || !wm831x_pdata->backup) अणु
		dev_warn(wm831x->dev,
			 "No backup battery charger configuration\n");
		वापस;
	पूर्ण

	pdata = wm831x_pdata->backup;

	reg = 0;

	अगर (pdata->अक्षरger_enable)
		reg |= WM831X_BKUP_CHG_ENA | WM831X_BKUP_BATT_DET_ENA;
	अगर (pdata->no_स्थिरant_voltage)
		reg |= WM831X_BKUP_CHG_MODE;

	चयन (pdata->vlim) अणु
	हाल 2500:
		अवरोध;
	हाल 3100:
		reg |= WM831X_BKUP_CHG_VLIM;
		अवरोध;
	शेष:
		dev_err(wm831x->dev, "Invalid backup voltage limit %dmV\n",
			pdata->vlim);
	पूर्ण

	चयन (pdata->ilim) अणु
	हाल 100:
		अवरोध;
	हाल 200:
		reg |= 1;
		अवरोध;
	हाल 300:
		reg |= 2;
		अवरोध;
	हाल 400:
		reg |= 3;
		अवरोध;
	शेष:
		dev_err(wm831x->dev, "Invalid backup current limit %duA\n",
			pdata->ilim);
	पूर्ण

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret != 0) अणु
		dev_err(wm831x->dev, "Failed to unlock registers: %d\n", ret);
		वापस;
	पूर्ण

	ret = wm831x_set_bits(wm831x, WM831X_BACKUP_CHARGER_CONTROL,
			      WM831X_BKUP_CHG_ENA_MASK |
			      WM831X_BKUP_CHG_MODE_MASK |
			      WM831X_BKUP_BATT_DET_ENA_MASK |
			      WM831X_BKUP_CHG_VLIM_MASK |
			      WM831X_BKUP_CHG_ILIM_MASK,
			      reg);
	अगर (ret != 0)
		dev_err(wm831x->dev,
			"Failed to set backup charger config: %d\n", ret);

	wm831x_reg_lock(wm831x);
पूर्ण

अटल पूर्णांक wm831x_backup_get_prop(काष्ठा घातer_supply *psy,
				  क्रमागत घातer_supply_property psp,
				  जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm831x_backup *devdata = dev_get_drvdata(psy->dev.parent);
	काष्ठा wm831x *wm831x = devdata->wm831x;
	पूर्णांक ret = 0;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_BACKUP_CHARGER_CONTROL);
	अगर (ret < 0)
		वापस ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (ret & WM831X_BKUP_CHG_STS)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = wm831x_backup_पढ़ो_voltage(wm831x, WM831X_AUX_BKUP_BATT,
						val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRESENT:
		अगर (ret & WM831X_BKUP_CHG_STS)
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property wm831x_backup_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_PRESENT,
पूर्ण;

/*********************************************************************
 *		Initialisation
 *********************************************************************/

अटल पूर्णांक wm831x_backup_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *wm831x_pdata = wm831x->dev->platक्रमm_data;
	काष्ठा wm831x_backup *devdata;

	devdata = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_backup),
				GFP_KERNEL);
	अगर (devdata == शून्य)
		वापस -ENOMEM;

	devdata->wm831x = wm831x;
	platक्रमm_set_drvdata(pdev, devdata);

	/* We ignore configuration failures since we can still पढ़ो
	 * back the status without enabling the अक्षरger (which may
	 * alपढ़ोy be enabled anyway).
	 */
	wm831x_config_backup(wm831x);

	अगर (wm831x_pdata && wm831x_pdata->wm831x_num)
		snम_लिखो(devdata->name, माप(devdata->name),
			 "wm831x-backup.%d", wm831x_pdata->wm831x_num);
	अन्यथा
		snम_लिखो(devdata->name, माप(devdata->name),
			 "wm831x-backup");

	devdata->backup_desc.name = devdata->name;
	devdata->backup_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	devdata->backup_desc.properties = wm831x_backup_props;
	devdata->backup_desc.num_properties = ARRAY_SIZE(wm831x_backup_props);
	devdata->backup_desc.get_property = wm831x_backup_get_prop;
	devdata->backup = घातer_supply_रेजिस्टर(&pdev->dev,
						&devdata->backup_desc, शून्य);

	वापस PTR_ERR_OR_ZERO(devdata->backup);
पूर्ण

अटल पूर्णांक wm831x_backup_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x_backup *devdata = platक्रमm_get_drvdata(pdev);

	घातer_supply_unरेजिस्टर(devdata->backup);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_backup_driver = अणु
	.probe = wm831x_backup_probe,
	.हटाओ = wm831x_backup_हटाओ,
	.driver = अणु
		.name = "wm831x-backup",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm831x_backup_driver);

MODULE_DESCRIPTION("Backup battery charger driver for WM831x PMICs");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-backup");
