<शैली गुरु>
/*
 * TI Touch Screen / ADC MFD driver
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sched.h>

#समावेश <linux/mfd/ti_am335x_tscadc.h>

अटल स्थिर काष्ठा regmap_config tscadc_regmap_config = अणु
	.name = "ti_tscadc",
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
पूर्ण;

व्योम am335x_tsc_se_set_cache(काष्ठा ti_tscadc_dev *tscadc, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tscadc->reg_lock, flags);
	tscadc->reg_se_cache |= val;
	अगर (tscadc->adc_रुकोing)
		wake_up(&tscadc->reg_se_रुको);
	अन्यथा अगर (!tscadc->adc_in_use)
		regmap_ग_लिखो(tscadc->regmap, REG_SE, tscadc->reg_se_cache);

	spin_unlock_irqrestore(&tscadc->reg_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(am335x_tsc_se_set_cache);

अटल व्योम am335x_tscadc_need_adc(काष्ठा ti_tscadc_dev *tscadc)
अणु
	DEFINE_WAIT(रुको);
	u32 reg;

	regmap_पढ़ो(tscadc->regmap, REG_ADCFSM, &reg);
	अगर (reg & SEQ_STATUS) अणु
		tscadc->adc_रुकोing = true;
		prepare_to_रुको(&tscadc->reg_se_रुको, &रुको,
				TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&tscadc->reg_lock);

		schedule();

		spin_lock_irq(&tscadc->reg_lock);
		finish_रुको(&tscadc->reg_se_रुको, &रुको);

		/*
		 * Sequencer should either be idle or
		 * busy applying the अक्षरge step.
		 */
		regmap_पढ़ो(tscadc->regmap, REG_ADCFSM, &reg);
		WARN_ON((reg & SEQ_STATUS) && !(reg & CHARGE_STEP));
		tscadc->adc_रुकोing = false;
	पूर्ण
	tscadc->adc_in_use = true;
पूर्ण

व्योम am335x_tsc_se_set_once(काष्ठा ti_tscadc_dev *tscadc, u32 val)
अणु
	spin_lock_irq(&tscadc->reg_lock);
	am335x_tscadc_need_adc(tscadc);

	regmap_ग_लिखो(tscadc->regmap, REG_SE, val);
	spin_unlock_irq(&tscadc->reg_lock);
पूर्ण
EXPORT_SYMBOL_GPL(am335x_tsc_se_set_once);

व्योम am335x_tsc_se_adc_करोne(काष्ठा ti_tscadc_dev *tscadc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tscadc->reg_lock, flags);
	tscadc->adc_in_use = false;
	regmap_ग_लिखो(tscadc->regmap, REG_SE, tscadc->reg_se_cache);
	spin_unlock_irqrestore(&tscadc->reg_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(am335x_tsc_se_adc_करोne);

व्योम am335x_tsc_se_clr(काष्ठा ti_tscadc_dev *tscadc, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tscadc->reg_lock, flags);
	tscadc->reg_se_cache &= ~val;
	regmap_ग_लिखो(tscadc->regmap, REG_SE, tscadc->reg_se_cache);
	spin_unlock_irqrestore(&tscadc->reg_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(am335x_tsc_se_clr);

अटल व्योम tscadc_idle_config(काष्ठा ti_tscadc_dev *tscadc)
अणु
	अचिन्हित पूर्णांक idleconfig;

	idleconfig = STEPCONFIG_YNN | STEPCONFIG_INM_ADCREFM |
			STEPCONFIG_INP_ADCREFM | STEPCONFIG_YPN;

	regmap_ग_लिखो(tscadc->regmap, REG_IDLECONFIG, idleconfig);
पूर्ण

अटल	पूर्णांक ti_tscadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_tscadc_dev	*tscadc;
	काष्ठा resource		*res;
	काष्ठा clk		*clk;
	काष्ठा device_node	*node;
	काष्ठा mfd_cell		*cell;
	काष्ठा property         *prop;
	स्थिर __be32            *cur;
	u32			val;
	पूर्णांक			err, ctrl;
	पूर्णांक			घड़ी_rate;
	पूर्णांक			tsc_wires = 0, adc_channels = 0, total_channels;
	पूर्णांक			पढ़ोouts = 0;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "Could not find valid DT data.\n");
		वापस -EINVAL;
	पूर्ण

	node = of_get_child_by_name(pdev->dev.of_node, "tsc");
	of_property_पढ़ो_u32(node, "ti,wires", &tsc_wires);
	of_property_पढ़ो_u32(node, "ti,coordiante-readouts", &पढ़ोouts);

	node = of_get_child_by_name(pdev->dev.of_node, "adc");
	of_property_क्रम_each_u32(node, "ti,adc-channels", prop, cur, val) अणु
		adc_channels++;
		अगर (val > 7) अणु
			dev_err(&pdev->dev, " PIN numbers are 0..7 (not %d)\n",
					val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	total_channels = tsc_wires + adc_channels;
	अगर (total_channels > 8) अणु
		dev_err(&pdev->dev, "Number of i/p channels more than 8\n");
		वापस -EINVAL;
	पूर्ण
	अगर (total_channels == 0) अणु
		dev_err(&pdev->dev, "Need atleast one channel.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (पढ़ोouts * 2 + 2 + adc_channels > 16) अणु
		dev_err(&pdev->dev, "Too many step configurations requested\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate memory क्रम device */
	tscadc = devm_kzalloc(&pdev->dev, माप(*tscadc), GFP_KERNEL);
	अगर (!tscadc)
		वापस -ENOMEM;

	tscadc->dev = &pdev->dev;

	err = platक्रमm_get_irq(pdev, 0);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "no irq ID is specified.\n");
		जाओ ret;
	पूर्ण अन्यथा
		tscadc->irq = err;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tscadc->tscadc_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(tscadc->tscadc_base))
		वापस PTR_ERR(tscadc->tscadc_base);

	tscadc->tscadc_phys_base = res->start;
	tscadc->regmap = devm_regmap_init_mmio(&pdev->dev,
			tscadc->tscadc_base, &tscadc_regmap_config);
	अगर (IS_ERR(tscadc->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		err = PTR_ERR(tscadc->regmap);
		जाओ ret;
	पूर्ण

	spin_lock_init(&tscadc->reg_lock);
	init_रुकोqueue_head(&tscadc->reg_se_रुको);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	/*
	 * The TSC_ADC_Subप्रणाली has 2 घड़ी करोमुख्यs
	 * OCP_CLK and ADC_CLK.
	 * The ADC घड़ी is expected to run at target of 3MHz,
	 * and expected to capture 12-bit data at a rate of 200 KSPS.
	 * The TSC_ADC_SS controller design assumes the OCP घड़ी is
	 * at least 6x faster than the ADC घड़ी.
	 */
	clk = devm_clk_get(&pdev->dev, "adc_tsc_fck");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get TSC fck\n");
		err = PTR_ERR(clk);
		जाओ err_disable_clk;
	पूर्ण
	घड़ी_rate = clk_get_rate(clk);
	tscadc->clk_भाग = घड़ी_rate / ADC_CLK;

	/* TSCADC_CLKDIV needs to be configured to the value minus 1 */
	tscadc->clk_भाग--;
	regmap_ग_लिखो(tscadc->regmap, REG_CLKDIV, tscadc->clk_भाग);

	/* Set the control रेजिस्टर bits */
	ctrl = CNTRLREG_STEPCONFIGWRT |	CNTRLREG_STEPID;
	regmap_ग_लिखो(tscadc->regmap, REG_CTRL, ctrl);

	/* Set रेजिस्टर bits क्रम Idle Config Mode */
	अगर (tsc_wires > 0) अणु
		tscadc->tsc_wires = tsc_wires;
		अगर (tsc_wires == 5)
			ctrl |= CNTRLREG_5WIRE | CNTRLREG_TSCENB;
		अन्यथा
			ctrl |= CNTRLREG_4WIRE | CNTRLREG_TSCENB;
		tscadc_idle_config(tscadc);
	पूर्ण

	/* Enable the TSC module enable bit */
	ctrl |= CNTRLREG_TSCSSENB;
	regmap_ग_लिखो(tscadc->regmap, REG_CTRL, ctrl);

	tscadc->used_cells = 0;
	tscadc->tsc_cell = -1;
	tscadc->adc_cell = -1;

	/* TSC Cell */
	अगर (tsc_wires > 0) अणु
		tscadc->tsc_cell = tscadc->used_cells;
		cell = &tscadc->cells[tscadc->used_cells++];
		cell->name = "TI-am335x-tsc";
		cell->of_compatible = "ti,am3359-tsc";
		cell->platक्रमm_data = &tscadc;
		cell->pdata_size = माप(tscadc);
	पूर्ण

	/* ADC Cell */
	अगर (adc_channels > 0) अणु
		tscadc->adc_cell = tscadc->used_cells;
		cell = &tscadc->cells[tscadc->used_cells++];
		cell->name = "TI-am335x-adc";
		cell->of_compatible = "ti,am3359-adc";
		cell->platक्रमm_data = &tscadc;
		cell->pdata_size = माप(tscadc);
	पूर्ण

	err = mfd_add_devices(&pdev->dev, PLATFORM_DEVID_AUTO,
			      tscadc->cells, tscadc->used_cells, शून्य,
			      0, शून्य);
	अगर (err < 0)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, tscadc);
	वापस 0;

err_disable_clk:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
ret:
	वापस err;
पूर्ण

अटल पूर्णांक ti_tscadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_tscadc_dev	*tscadc = platक्रमm_get_drvdata(pdev);

	regmap_ग_लिखो(tscadc->regmap, REG_SE, 0x00);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	mfd_हटाओ_devices(tscadc->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ti_tscadc_can_wakeup(काष्ठा device *dev, व्योम *data)
अणु
	वापस device_may_wakeup(dev);
पूर्ण

अटल पूर्णांक __maybe_unused tscadc_suspend(काष्ठा device *dev)
अणु
	काष्ठा ti_tscadc_dev	*tscadc = dev_get_drvdata(dev);

	regmap_ग_लिखो(tscadc->regmap, REG_SE, 0x00);
	अगर (device_क्रम_each_child(dev, शून्य, ti_tscadc_can_wakeup)) अणु
		u32 ctrl;

		regmap_पढ़ो(tscadc->regmap, REG_CTRL, &ctrl);
		ctrl &= ~(CNTRLREG_POWERDOWN);
		ctrl |= CNTRLREG_TSCSSENB;
		regmap_ग_लिखो(tscadc->regmap, REG_CTRL, ctrl);
	पूर्ण
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tscadc_resume(काष्ठा device *dev)
अणु
	काष्ठा ti_tscadc_dev	*tscadc = dev_get_drvdata(dev);
	u32 ctrl;

	pm_runसमय_get_sync(dev);

	/* context restore */
	ctrl = CNTRLREG_STEPCONFIGWRT |	CNTRLREG_STEPID;
	regmap_ग_लिखो(tscadc->regmap, REG_CTRL, ctrl);

	अगर (tscadc->tsc_cell != -1) अणु
		अगर (tscadc->tsc_wires == 5)
			ctrl |= CNTRLREG_5WIRE | CNTRLREG_TSCENB;
		अन्यथा
			ctrl |= CNTRLREG_4WIRE | CNTRLREG_TSCENB;
		tscadc_idle_config(tscadc);
	पूर्ण
	ctrl |= CNTRLREG_TSCSSENB;
	regmap_ग_लिखो(tscadc->regmap, REG_CTRL, ctrl);

	regmap_ग_लिखो(tscadc->regmap, REG_CLKDIV, tscadc->clk_भाग);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tscadc_pm_ops, tscadc_suspend, tscadc_resume);

अटल स्थिर काष्ठा of_device_id ti_tscadc_dt_ids[] = अणु
	अणु .compatible = "ti,am3359-tscadc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_tscadc_dt_ids);

अटल काष्ठा platक्रमm_driver ti_tscadc_driver = अणु
	.driver = अणु
		.name   = "ti_am3359-tscadc",
		.pm	= &tscadc_pm_ops,
		.of_match_table = ti_tscadc_dt_ids,
	पूर्ण,
	.probe	= ti_tscadc_probe,
	.हटाओ	= ti_tscadc_हटाओ,

पूर्ण;

module_platक्रमm_driver(ti_tscadc_driver);

MODULE_DESCRIPTION("TI touchscreen / ADC MFD controller driver");
MODULE_AUTHOR("Rachna Patil <rachna@ti.com>");
MODULE_LICENSE("GPL");
