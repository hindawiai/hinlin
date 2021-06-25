<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA9150 Fuel-Gauge Driver
 *
 * Copyright (c) 2015 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/mfd/da9150/core.h>
#समावेश <linux/mfd/da9150/रेजिस्टरs.h>

/* Core2Wire */
#घोषणा DA9150_QIF_READ		(0x0 << 7)
#घोषणा DA9150_QIF_WRITE	(0x1 << 7)
#घोषणा DA9150_QIF_CODE_MASK	0x7F

#घोषणा DA9150_QIF_BYTE_SIZE	8
#घोषणा DA9150_QIF_BYTE_MASK	0xFF
#घोषणा DA9150_QIF_SHORT_SIZE	2
#घोषणा DA9150_QIF_LONG_SIZE	4

/* QIF Codes */
#घोषणा DA9150_QIF_UAVG			6
#घोषणा DA9150_QIF_UAVG_SIZE		DA9150_QIF_LONG_SIZE
#घोषणा DA9150_QIF_IAVG			8
#घोषणा DA9150_QIF_IAVG_SIZE		DA9150_QIF_LONG_SIZE
#घोषणा DA9150_QIF_NTCAVG		12
#घोषणा DA9150_QIF_NTCAVG_SIZE		DA9150_QIF_LONG_SIZE
#घोषणा DA9150_QIF_SHUNT_VAL		36
#घोषणा DA9150_QIF_SHUNT_VAL_SIZE	DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_SD_GAIN		38
#घोषणा DA9150_QIF_SD_GAIN_SIZE		DA9150_QIF_LONG_SIZE
#घोषणा DA9150_QIF_FCC_MAH		40
#घोषणा DA9150_QIF_FCC_MAH_SIZE		DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_SOC_PCT		43
#घोषणा DA9150_QIF_SOC_PCT_SIZE		DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_CHARGE_LIMIT		44
#घोषणा DA9150_QIF_CHARGE_LIMIT_SIZE	DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_DISCHARGE_LIMIT	45
#घोषणा DA9150_QIF_DISCHARGE_LIMIT_SIZE	DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_FW_MAIN_VER		118
#घोषणा DA9150_QIF_FW_MAIN_VER_SIZE	DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_E_FG_STATUS		126
#घोषणा DA9150_QIF_E_FG_STATUS_SIZE	DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_SYNC			127
#घोषणा DA9150_QIF_SYNC_SIZE		DA9150_QIF_SHORT_SIZE
#घोषणा DA9150_QIF_MAX_CODES		128

/* QIF Sync Timeout */
#घोषणा DA9150_QIF_SYNC_TIMEOUT		1000
#घोषणा DA9150_QIF_SYNC_RETRIES		10

/* QIF E_FG_STATUS */
#घोषणा DA9150_FG_IRQ_LOW_SOC_MASK	(1 << 0)
#घोषणा DA9150_FG_IRQ_HIGH_SOC_MASK	(1 << 1)
#घोषणा DA9150_FG_IRQ_SOC_MASK	\
	(DA9150_FG_IRQ_LOW_SOC_MASK | DA9150_FG_IRQ_HIGH_SOC_MASK)

/* Private data */
काष्ठा da9150_fg अणु
	काष्ठा da9150 *da9150;
	काष्ठा device *dev;

	काष्ठा mutex io_lock;

	काष्ठा घातer_supply *battery;
	काष्ठा delayed_work work;
	u32 पूर्णांकerval;

	पूर्णांक warn_soc;
	पूर्णांक crit_soc;
	पूर्णांक soc;
पूर्ण;

/* Battery Properties */
अटल u32 da9150_fg_पढ़ो_attr(काष्ठा da9150_fg *fg, u8 code, u8 size)

अणु
	u8 buf[DA9150_QIF_LONG_SIZE];
	u8 पढ़ो_addr;
	u32 res = 0;
	पूर्णांक i;

	/* Set QIF code (READ mode) */
	पढ़ो_addr = (code & DA9150_QIF_CODE_MASK) | DA9150_QIF_READ;

	da9150_पढ़ो_qअगर(fg->da9150, पढ़ो_addr, size, buf);
	क्रम (i = 0; i < size; ++i)
		res |= (buf[i] << (i * DA9150_QIF_BYTE_SIZE));

	वापस res;
पूर्ण

अटल व्योम da9150_fg_ग_लिखो_attr(काष्ठा da9150_fg *fg, u8 code, u8 size,
				 u32 val)

अणु
	u8 buf[DA9150_QIF_LONG_SIZE];
	u8 ग_लिखो_addr;
	पूर्णांक i;

	/* Set QIF code (WRITE mode) */
	ग_लिखो_addr = (code & DA9150_QIF_CODE_MASK) | DA9150_QIF_WRITE;

	क्रम (i = 0; i < size; ++i) अणु
		buf[i] = (val >> (i * DA9150_QIF_BYTE_SIZE)) &
			 DA9150_QIF_BYTE_MASK;
	पूर्ण
	da9150_ग_लिखो_qअगर(fg->da9150, ग_लिखो_addr, size, buf);
पूर्ण

/* Trigger QIF Sync to update QIF पढ़ोable data */
अटल व्योम da9150_fg_पढ़ो_sync_start(काष्ठा da9150_fg *fg)
अणु
	पूर्णांक i = 0;
	u32 res = 0;

	mutex_lock(&fg->io_lock);

	/* Check अगर QIF sync alपढ़ोy requested, and ग_लिखो to sync अगर not */
	res = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SYNC,
				  DA9150_QIF_SYNC_SIZE);
	अगर (res > 0)
		da9150_fg_ग_लिखो_attr(fg, DA9150_QIF_SYNC,
				     DA9150_QIF_SYNC_SIZE, 0);

	/* Wait क्रम sync to complete */
	res = 0;
	जबतक ((res == 0) && (i++ < DA9150_QIF_SYNC_RETRIES)) अणु
		usleep_range(DA9150_QIF_SYNC_TIMEOUT,
			     DA9150_QIF_SYNC_TIMEOUT * 2);
		res = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SYNC,
					  DA9150_QIF_SYNC_SIZE);
	पूर्ण

	/* Check अगर sync completed */
	अगर (res == 0)
		dev_err(fg->dev, "Failed to perform QIF read sync!\n");
पूर्ण

/*
 * Should always be called after QIF sync पढ़ो has been perक्रमmed, and all
 * attributes required have been accessed.
 */
अटल अंतरभूत व्योम da9150_fg_पढ़ो_sync_end(काष्ठा da9150_fg *fg)
अणु
	mutex_unlock(&fg->io_lock);
पूर्ण

/* Sync पढ़ो of single QIF attribute */
अटल u32 da9150_fg_पढ़ो_attr_sync(काष्ठा da9150_fg *fg, u8 code, u8 size)
अणु
	u32 val;

	da9150_fg_पढ़ो_sync_start(fg);
	val = da9150_fg_पढ़ो_attr(fg, code, size);
	da9150_fg_पढ़ो_sync_end(fg);

	वापस val;
पूर्ण

/* Wait क्रम QIF Sync, ग_लिखो QIF data and रुको क्रम ack */
अटल व्योम da9150_fg_ग_लिखो_attr_sync(काष्ठा da9150_fg *fg, u8 code, u8 size,
				      u32 val)
अणु
	पूर्णांक i = 0;
	u32 res = 0, sync_val;

	mutex_lock(&fg->io_lock);

	/* Check अगर QIF sync alपढ़ोy requested */
	res = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SYNC,
				  DA9150_QIF_SYNC_SIZE);

	/* Wait क्रम an existing sync to complete */
	जबतक ((res == 0) && (i++ < DA9150_QIF_SYNC_RETRIES)) अणु
		usleep_range(DA9150_QIF_SYNC_TIMEOUT,
			     DA9150_QIF_SYNC_TIMEOUT * 2);
		res = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SYNC,
					  DA9150_QIF_SYNC_SIZE);
	पूर्ण

	अगर (res == 0) अणु
		dev_err(fg->dev, "Timeout waiting for existing QIF sync!\n");
		mutex_unlock(&fg->io_lock);
		वापस;
	पूर्ण

	/* Write value क्रम QIF code */
	da9150_fg_ग_लिखो_attr(fg, code, size, val);

	/* Wait क्रम ग_लिखो acknowledgment */
	i = 0;
	sync_val = res;
	जबतक ((res == sync_val) && (i++ < DA9150_QIF_SYNC_RETRIES)) अणु
		usleep_range(DA9150_QIF_SYNC_TIMEOUT,
			     DA9150_QIF_SYNC_TIMEOUT * 2);
		res = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SYNC,
					  DA9150_QIF_SYNC_SIZE);
	पूर्ण

	mutex_unlock(&fg->io_lock);

	/* Check ग_लिखो was actually successful */
	अगर (res != (sync_val + 1))
		dev_err(fg->dev, "Error performing QIF sync write for code %d\n",
			code);
पूर्ण

/* Power Supply attributes */
अटल पूर्णांक da9150_fg_capacity(काष्ठा da9150_fg *fg,
			      जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = da9150_fg_पढ़ो_attr_sync(fg, DA9150_QIF_SOC_PCT,
					       DA9150_QIF_SOC_PCT_SIZE);

	अगर (val->पूर्णांकval > 100)
		val->पूर्णांकval = 100;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_fg_current_avg(काष्ठा da9150_fg *fg,
				 जोड़ घातer_supply_propval *val)
अणु
	u32 iavg, sd_gain, shunt_val;
	u64 भाग, res;

	da9150_fg_पढ़ो_sync_start(fg);
	iavg = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_IAVG,
				   DA9150_QIF_IAVG_SIZE);
	shunt_val = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SHUNT_VAL,
					DA9150_QIF_SHUNT_VAL_SIZE);
	sd_gain = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_SD_GAIN,
				      DA9150_QIF_SD_GAIN_SIZE);
	da9150_fg_पढ़ो_sync_end(fg);

	भाग = (u64) (sd_gain * shunt_val * 65536ULL);
	करो_भाग(भाग, 1000000);
	res = (u64) (iavg * 1000000ULL);
	करो_भाग(res, भाग);

	val->पूर्णांकval = (पूर्णांक) res;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_fg_voltage_avg(काष्ठा da9150_fg *fg,
				 जोड़ घातer_supply_propval *val)
अणु
	u64 res;

	val->पूर्णांकval = da9150_fg_पढ़ो_attr_sync(fg, DA9150_QIF_UAVG,
					       DA9150_QIF_UAVG_SIZE);

	res = (u64) (val->पूर्णांकval * 186ULL);
	करो_भाग(res, 10000);
	val->पूर्णांकval = (पूर्णांक) res;

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_fg_अक्षरge_full(काष्ठा da9150_fg *fg,
				 जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = da9150_fg_पढ़ो_attr_sync(fg, DA9150_QIF_FCC_MAH,
					       DA9150_QIF_FCC_MAH_SIZE);

	val->पूर्णांकval = val->पूर्णांकval * 1000;

	वापस 0;
पूर्ण

/*
 * Temperature पढ़ोing from device is only valid अगर battery/प्रणाली provides
 * valid NTC to associated pin of DA9150 chip.
 */
अटल पूर्णांक da9150_fg_temp(काष्ठा da9150_fg *fg,
			  जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = da9150_fg_पढ़ो_attr_sync(fg, DA9150_QIF_NTCAVG,
					       DA9150_QIF_NTCAVG_SIZE);

	val->पूर्णांकval = (val->पूर्णांकval * 10) / 1048576;

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property da9150_fg_props[] = अणु
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल पूर्णांक da9150_fg_get_prop(काष्ठा घातer_supply *psy,
			      क्रमागत घातer_supply_property psp,
			      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा da9150_fg *fg = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = da9150_fg_capacity(fg, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9150_fg_current_avg(fg, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = da9150_fg_voltage_avg(fg, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = da9150_fg_अक्षरge_full(fg, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = da9150_fg_temp(fg, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Repeated SOC check */
अटल bool da9150_fg_soc_changed(काष्ठा da9150_fg *fg)
अणु
	जोड़ घातer_supply_propval val;

	da9150_fg_capacity(fg, &val);
	अगर (val.पूर्णांकval != fg->soc) अणु
		fg->soc = val.पूर्णांकval;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम da9150_fg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9150_fg *fg = container_of(work, काष्ठा da9150_fg, work.work);

	/* Report अगर SOC has changed */
	अगर (da9150_fg_soc_changed(fg))
		घातer_supply_changed(fg->battery);

	schedule_delayed_work(&fg->work, msecs_to_jअगरfies(fg->पूर्णांकerval));
पूर्ण

/* SOC level event configuration */
अटल व्योम da9150_fg_soc_event_config(काष्ठा da9150_fg *fg)
अणु
	पूर्णांक soc;

	soc = da9150_fg_पढ़ो_attr_sync(fg, DA9150_QIF_SOC_PCT,
				       DA9150_QIF_SOC_PCT_SIZE);

	अगर (soc > fg->warn_soc) अणु
		/* If SOC > warn level, set disअक्षरge warn level event */
		da9150_fg_ग_लिखो_attr_sync(fg, DA9150_QIF_DISCHARGE_LIMIT,
					  DA9150_QIF_DISCHARGE_LIMIT_SIZE,
					  fg->warn_soc + 1);
	पूर्ण अन्यथा अगर ((soc <= fg->warn_soc) && (soc > fg->crit_soc)) अणु
		/*
		 * If SOC <= warn level, set disअक्षरge crit level event,
		 * and set अक्षरge warn level event.
		 */
		da9150_fg_ग_लिखो_attr_sync(fg, DA9150_QIF_DISCHARGE_LIMIT,
					  DA9150_QIF_DISCHARGE_LIMIT_SIZE,
					  fg->crit_soc + 1);

		da9150_fg_ग_लिखो_attr_sync(fg, DA9150_QIF_CHARGE_LIMIT,
					  DA9150_QIF_CHARGE_LIMIT_SIZE,
					  fg->warn_soc);
	पूर्ण अन्यथा अगर (soc <= fg->crit_soc) अणु
		/* If SOC <= crit level, set अक्षरge crit level event */
		da9150_fg_ग_लिखो_attr_sync(fg, DA9150_QIF_CHARGE_LIMIT,
					  DA9150_QIF_CHARGE_LIMIT_SIZE,
					  fg->crit_soc);
	पूर्ण
पूर्ण

अटल irqवापस_t da9150_fg_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9150_fg *fg = data;
	u32 e_fg_status;

	/* Read FG IRQ status info */
	e_fg_status = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_E_FG_STATUS,
					  DA9150_QIF_E_FG_STATUS_SIZE);

	/* Handle warning/critical threhold events */
	अगर (e_fg_status & DA9150_FG_IRQ_SOC_MASK)
		da9150_fg_soc_event_config(fg);

	/* Clear any FG IRQs */
	da9150_fg_ग_लिखो_attr(fg, DA9150_QIF_E_FG_STATUS,
			     DA9150_QIF_E_FG_STATUS_SIZE, e_fg_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा da9150_fg_pdata *da9150_fg_dt_pdata(काष्ठा device *dev)
अणु
	काष्ठा device_node *fg_node = dev->of_node;
	काष्ठा da9150_fg_pdata *pdata;

	pdata = devm_kzalloc(dev, माप(काष्ठा da9150_fg_pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	of_property_पढ़ो_u32(fg_node, "dlg,update-interval",
			     &pdata->update_पूर्णांकerval);
	of_property_पढ़ो_u8(fg_node, "dlg,warn-soc-level",
			    &pdata->warn_soc_lvl);
	of_property_पढ़ो_u8(fg_node, "dlg,crit-soc-level",
			    &pdata->crit_soc_lvl);

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc fg_desc = अणु
	.name		= "da9150-fg",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= da9150_fg_props,
	.num_properties	= ARRAY_SIZE(da9150_fg_props),
	.get_property	= da9150_fg_get_prop,
पूर्ण;

अटल पूर्णांक da9150_fg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9150 *da9150 = dev_get_drvdata(dev->parent);
	काष्ठा da9150_fg_pdata *fg_pdata = dev_get_platdata(dev);
	काष्ठा da9150_fg *fg;
	पूर्णांक ver, irq, ret = 0;

	fg = devm_kzalloc(dev, माप(*fg), GFP_KERNEL);
	अगर (fg == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, fg);
	fg->da9150 = da9150;
	fg->dev = dev;

	mutex_init(&fg->io_lock);

	/* Enable QIF */
	da9150_set_bits(da9150, DA9150_CORE2WIRE_CTRL_A, DA9150_FG_QIF_EN_MASK,
			DA9150_FG_QIF_EN_MASK);

	fg->battery = devm_घातer_supply_रेजिस्टर(dev, &fg_desc, शून्य);
	अगर (IS_ERR(fg->battery)) अणु
		ret = PTR_ERR(fg->battery);
		वापस ret;
	पूर्ण

	ver = da9150_fg_पढ़ो_attr(fg, DA9150_QIF_FW_MAIN_VER,
				  DA9150_QIF_FW_MAIN_VER_SIZE);
	dev_info(dev, "Version: 0x%x\n", ver);

	/* Handle DT data अगर provided */
	अगर (dev->of_node) अणु
		fg_pdata = da9150_fg_dt_pdata(dev);
		dev->platक्रमm_data = fg_pdata;
	पूर्ण

	/* Handle any pdata provided */
	अगर (fg_pdata) अणु
		fg->पूर्णांकerval = fg_pdata->update_पूर्णांकerval;

		अगर (fg_pdata->warn_soc_lvl > 100)
			dev_warn(dev, "Invalid SOC warning level provided, Ignoring");
		अन्यथा
			fg->warn_soc = fg_pdata->warn_soc_lvl;

		अगर ((fg_pdata->crit_soc_lvl > 100) ||
		    (fg_pdata->crit_soc_lvl >= fg_pdata->warn_soc_lvl))
			dev_warn(dev, "Invalid SOC critical level provided, Ignoring");
		अन्यथा
			fg->crit_soc = fg_pdata->crit_soc_lvl;


	पूर्ण

	/* Configure initial SOC level events */
	da9150_fg_soc_event_config(fg);

	/*
	 * If an पूर्णांकerval period has been provided then setup repeating
	 * work क्रम reporting data updates.
	 */
	अगर (fg->पूर्णांकerval) अणु
		INIT_DELAYED_WORK(&fg->work, da9150_fg_work);
		schedule_delayed_work(&fg->work,
				      msecs_to_jअगरfies(fg->पूर्णांकerval));
	पूर्ण

	/* Register IRQ */
	irq = platक्रमm_get_irq_byname(pdev, "FG");
	अगर (irq < 0) अणु
		dev_err(dev, "Failed to get IRQ FG: %d\n", irq);
		ret = irq;
		जाओ irq_fail;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, da9150_fg_irq,
					IRQF_ONESHOT, "FG", fg);
	अगर (ret) अणु
		dev_err(dev, "Failed to request IRQ %d: %d\n", irq, ret);
		जाओ irq_fail;
	पूर्ण

	वापस 0;

irq_fail:
	अगर (fg->पूर्णांकerval)
		cancel_delayed_work(&fg->work);

	वापस ret;
पूर्ण

अटल पूर्णांक da9150_fg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9150_fg *fg = platक्रमm_get_drvdata(pdev);

	अगर (fg->पूर्णांकerval)
		cancel_delayed_work(&fg->work);

	वापस 0;
पूर्ण

अटल पूर्णांक da9150_fg_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9150_fg *fg = platक्रमm_get_drvdata(pdev);

	/*
	 * Trigger SOC check to happen now so as to indicate any value change
	 * since last check beक्रमe suspend.
	 */
	अगर (fg->पूर्णांकerval)
		flush_delayed_work(&fg->work);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9150_fg_driver = अणु
	.driver = अणु
		.name = "da9150-fuel-gauge",
	पूर्ण,
	.probe = da9150_fg_probe,
	.हटाओ = da9150_fg_हटाओ,
	.resume = da9150_fg_resume,
पूर्ण;

module_platक्रमm_driver(da9150_fg_driver);

MODULE_DESCRIPTION("Fuel-Gauge Driver for DA9150");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
