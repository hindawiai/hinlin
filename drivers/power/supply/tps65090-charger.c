<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery अक्षरger driver क्रम TI's tps65090
 *
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.

 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/tps65090.h>

#घोषणा TPS65090_CHARGER_ENABLE	BIT(0)
#घोषणा TPS65090_VACG		BIT(1)
#घोषणा TPS65090_NOITERM	BIT(5)

#घोषणा POLL_INTERVAL		(HZ * 2)	/* Used when no irq */

काष्ठा tps65090_अक्षरger अणु
	काष्ठा	device	*dev;
	पूर्णांक	ac_online;
	पूर्णांक	prev_ac_online;
	पूर्णांक	irq;
	काष्ठा task_काष्ठा	*poll_task;
	bool			passive_mode;
	काष्ठा घातer_supply	*ac;
	काष्ठा tps65090_platक्रमm_data *pdata;
पूर्ण;

अटल क्रमागत घातer_supply_property tps65090_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल पूर्णांक tps65090_low_chrg_current(काष्ठा tps65090_अक्षरger *अक्षरger)
अणु
	पूर्णांक ret;

	अगर (अक्षरger->passive_mode)
		वापस 0;

	ret = tps65090_ग_लिखो(अक्षरger->dev->parent, TPS65090_REG_CG_CTRL5,
			TPS65090_NOITERM);
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): error reading in register 0x%x\n",
			__func__, TPS65090_REG_CG_CTRL5);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps65090_enable_अक्षरging(काष्ठा tps65090_अक्षरger *अक्षरger)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t ctrl0 = 0;

	अगर (अक्षरger->passive_mode)
		वापस 0;

	ret = tps65090_पढ़ो(अक्षरger->dev->parent, TPS65090_REG_CG_CTRL0,
			    &ctrl0);
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): error reading in register 0x%x\n",
				__func__, TPS65090_REG_CG_CTRL0);
		वापस ret;
	पूर्ण

	ret = tps65090_ग_लिखो(अक्षरger->dev->parent, TPS65090_REG_CG_CTRL0,
				(ctrl0 | TPS65090_CHARGER_ENABLE));
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): error writing in register 0x%x\n",
				__func__, TPS65090_REG_CG_CTRL0);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps65090_config_अक्षरger(काष्ठा tps65090_अक्षरger *अक्षरger)
अणु
	uपूर्णांक8_t पूर्णांकrmask = 0;
	पूर्णांक ret;

	अगर (अक्षरger->passive_mode)
		वापस 0;

	अगर (अक्षरger->pdata->enable_low_current_chrg) अणु
		ret = tps65090_low_chrg_current(अक्षरger);
		अगर (ret < 0) अणु
			dev_err(अक्षरger->dev,
				"error configuring low charge current\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Enable the VACG पूर्णांकerrupt क्रम AC घातer detect */
	ret = tps65090_पढ़ो(अक्षरger->dev->parent, TPS65090_REG_INTR_MASK,
			    &पूर्णांकrmask);
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): error reading in register 0x%x\n",
			__func__, TPS65090_REG_INTR_MASK);
		वापस ret;
	पूर्ण

	ret = tps65090_ग_लिखो(अक्षरger->dev->parent, TPS65090_REG_INTR_MASK,
			     (पूर्णांकrmask | TPS65090_VACG));
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): error writing in register 0x%x\n",
			__func__, TPS65090_REG_CG_CTRL0);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65090_ac_get_property(काष्ठा घातer_supply *psy,
			क्रमागत घातer_supply_property psp,
			जोड़ घातer_supply_propval *val)
अणु
	काष्ठा tps65090_अक्षरger *अक्षरger = घातer_supply_get_drvdata(psy);

	अगर (psp == POWER_SUPPLY_PROP_ONLINE) अणु
		val->पूर्णांकval = अक्षरger->ac_online;
		अक्षरger->prev_ac_online = अक्षरger->ac_online;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल irqवापस_t tps65090_अक्षरger_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tps65090_अक्षरger *अक्षरger = dev_id;
	पूर्णांक ret;
	uपूर्णांक8_t status1 = 0;
	uपूर्णांक8_t पूर्णांकrsts = 0;

	ret = tps65090_पढ़ो(अक्षरger->dev->parent, TPS65090_REG_CG_STATUS1,
			    &status1);
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): Error in reading reg 0x%x\n",
				__func__, TPS65090_REG_CG_STATUS1);
		वापस IRQ_HANDLED;
	पूर्ण
	msleep(75);
	ret = tps65090_पढ़ो(अक्षरger->dev->parent, TPS65090_REG_INTR_STS,
			    &पूर्णांकrsts);
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev, "%s(): Error in reading reg 0x%x\n",
				__func__, TPS65090_REG_INTR_STS);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकrsts & TPS65090_VACG) अणु
		ret = tps65090_enable_अक्षरging(अक्षरger);
		अगर (ret < 0)
			वापस IRQ_HANDLED;
		अक्षरger->ac_online = 1;
	पूर्ण अन्यथा अणु
		अक्षरger->ac_online = 0;
	पूर्ण

	/* Clear पूर्णांकerrupts. */
	अगर (!अक्षरger->passive_mode) अणु
		ret = tps65090_ग_लिखो(अक्षरger->dev->parent,
				     TPS65090_REG_INTR_STS, 0x00);
		अगर (ret < 0) अणु
			dev_err(अक्षरger->dev,
				"%s(): Error in writing reg 0x%x\n",
				__func__, TPS65090_REG_INTR_STS);
		पूर्ण
	पूर्ण

	अगर (अक्षरger->prev_ac_online != अक्षरger->ac_online)
		घातer_supply_changed(अक्षरger->ac);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा tps65090_platक्रमm_data *
		tps65090_parse_dt_अक्षरger_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65090_platक्रमm_data *pdata;
	काष्ठा device_node *np = pdev->dev.of_node;
	अचिन्हित पूर्णांक prop;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Memory alloc for tps65090_pdata failed\n");
		वापस शून्य;
	पूर्ण

	prop = of_property_पढ़ो_bool(np, "ti,enable-low-current-chrg");
	pdata->enable_low_current_chrg = prop;

	pdata->irq_base = -1;

	वापस pdata;

पूर्ण

अटल पूर्णांक tps65090_अक्षरger_poll_task(व्योम *data)
अणु
	set_मुक्तzable();

	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule_समयout_पूर्णांकerruptible(POLL_INTERVAL);
		try_to_मुक्तze();
		tps65090_अक्षरger_isr(-1, data);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc tps65090_अक्षरger_desc = अणु
	.name			= "tps65090-ac",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.get_property		= tps65090_ac_get_property,
	.properties		= tps65090_ac_props,
	.num_properties		= ARRAY_SIZE(tps65090_ac_props),
पूर्ण;

अटल पूर्णांक tps65090_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65090_अक्षरger *cdata;
	काष्ठा tps65090_platक्रमm_data *pdata;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	uपूर्णांक8_t status1 = 0;
	पूर्णांक ret;
	पूर्णांक irq;

	pdata = dev_get_platdata(pdev->dev.parent);

	अगर (IS_ENABLED(CONFIG_OF) && !pdata && pdev->dev.of_node)
		pdata = tps65090_parse_dt_अक्षरger_data(pdev);

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "%s():no platform data available\n",
				__func__);
		वापस -ENODEV;
	पूर्ण

	cdata = devm_kzalloc(&pdev->dev, माप(*cdata), GFP_KERNEL);
	अगर (!cdata) अणु
		dev_err(&pdev->dev, "failed to allocate memory status\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, cdata);

	cdata->dev			= &pdev->dev;
	cdata->pdata			= pdata;

	psy_cfg.supplied_to		= pdata->supplied_to;
	psy_cfg.num_supplicants		= pdata->num_supplicants;
	psy_cfg.of_node			= pdev->dev.of_node;
	psy_cfg.drv_data		= cdata;

	cdata->ac = घातer_supply_रेजिस्टर(&pdev->dev, &tps65090_अक्षरger_desc,
			&psy_cfg);
	अगर (IS_ERR(cdata->ac)) अणु
		dev_err(&pdev->dev, "failed: power supply register\n");
		वापस PTR_ERR(cdata->ac);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		irq = -ENXIO;
	cdata->irq = irq;

	ret = tps65090_config_अक्षरger(cdata);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "charger config failed, err %d\n", ret);
		जाओ fail_unरेजिस्टर_supply;
	पूर्ण

	/* Check क्रम अक्षरger presence */
	ret = tps65090_पढ़ो(cdata->dev->parent, TPS65090_REG_CG_STATUS1,
			&status1);
	अगर (ret < 0) अणु
		dev_err(cdata->dev, "%s(): Error in reading reg 0x%x", __func__,
			TPS65090_REG_CG_STATUS1);
		जाओ fail_unरेजिस्टर_supply;
	पूर्ण

	अगर (status1 != 0) अणु
		ret = tps65090_enable_अक्षरging(cdata);
		अगर (ret < 0) अणु
			dev_err(cdata->dev, "error enabling charger\n");
			जाओ fail_unरेजिस्टर_supply;
		पूर्ण
		cdata->ac_online = 1;
		घातer_supply_changed(cdata->ac);
	पूर्ण

	अगर (irq != -ENXIO) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
			tps65090_अक्षरger_isr, IRQF_ONESHOT, "tps65090-charger", cdata);
		अगर (ret) अणु
			dev_err(cdata->dev,
				"Unable to register irq %d err %d\n", irq,
				ret);
			जाओ fail_unरेजिस्टर_supply;
		पूर्ण
	पूर्ण अन्यथा अणु
		cdata->poll_task = kthपढ़ो_run(tps65090_अक्षरger_poll_task,
					      cdata, "ktps65090charger");
		cdata->passive_mode = true;
		अगर (IS_ERR(cdata->poll_task)) अणु
			ret = PTR_ERR(cdata->poll_task);
			dev_err(cdata->dev,
				"Unable to run kthread err %d\n", ret);
			जाओ fail_unरेजिस्टर_supply;
		पूर्ण
	पूर्ण

	वापस 0;

fail_unरेजिस्टर_supply:
	घातer_supply_unरेजिस्टर(cdata->ac);

	वापस ret;
पूर्ण

अटल पूर्णांक tps65090_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65090_अक्षरger *cdata = platक्रमm_get_drvdata(pdev);

	अगर (cdata->irq == -ENXIO)
		kthपढ़ो_stop(cdata->poll_task);
	घातer_supply_unरेजिस्टर(cdata->ac);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_tps65090_अक्षरger_match[] = अणु
	अणु .compatible = "ti,tps65090-charger", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_tps65090_अक्षरger_match);

अटल काष्ठा platक्रमm_driver tps65090_अक्षरger_driver = अणु
	.driver	= अणु
		.name	= "tps65090-charger",
		.of_match_table = of_tps65090_अक्षरger_match,
	पूर्ण,
	.probe	= tps65090_अक्षरger_probe,
	.हटाओ = tps65090_अक्षरger_हटाओ,
पूर्ण;
module_platक्रमm_driver(tps65090_अक्षरger_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Syed Rafiuddin <srafiuddin@nvidia.com>");
MODULE_DESCRIPTION("tps65090 battery charger driver");
