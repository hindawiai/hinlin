<शैली गुरु>
/*
 * TI Touch Screen driver
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sort.h>
#समावेश <linux/pm_wakeirq.h>

#समावेश <linux/mfd/ti_am335x_tscadc.h>

#घोषणा ADCFSM_STEPID		0x10
#घोषणा SEQ_SETTLE		275
#घोषणा MAX_12BIT		((1 << 12) - 1)

#घोषणा TSC_IRQENB_MASK		(IRQENB_FIFO0THRES | IRQENB_EOS | IRQENB_HW_PEN)

अटल स्थिर पूर्णांक config_pins[] = अणु
	STEPCONFIG_XPP,
	STEPCONFIG_XNN,
	STEPCONFIG_YPP,
	STEPCONFIG_YNN,
पूर्ण;

काष्ठा titsc अणु
	काष्ठा input_dev	*input;
	काष्ठा ti_tscadc_dev	*mfd_tscadc;
	काष्ठा device		*dev;
	अचिन्हित पूर्णांक		irq;
	अचिन्हित पूर्णांक		wires;
	अचिन्हित पूर्णांक		x_plate_resistance;
	bool			pen_करोwn;
	पूर्णांक			coordinate_पढ़ोouts;
	u32			config_inp[4];
	u32			bit_xp, bit_xn, bit_yp, bit_yn;
	u32			inp_xp, inp_xn, inp_yp, inp_yn;
	u32			step_mask;
	u32			अक्षरge_delay;
पूर्ण;

अटल अचिन्हित पूर्णांक titsc_पढ़ोl(काष्ठा titsc *ts, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(ts->mfd_tscadc->tscadc_base + reg);
पूर्ण

अटल व्योम titsc_ग_लिखोl(काष्ठा titsc *tsc, अचिन्हित पूर्णांक reg,
					अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, tsc->mfd_tscadc->tscadc_base + reg);
पूर्ण

अटल पूर्णांक titsc_config_wires(काष्ठा titsc *ts_dev)
अणु
	u32 analog_line[4];
	u32 wire_order[4];
	पूर्णांक i, bit_cfg;

	क्रम (i = 0; i < 4; i++) अणु
		/*
		 * Get the order in which TSC wires are attached
		 * w.r.t. each of the analog input lines on the EVM.
		 */
		analog_line[i] = (ts_dev->config_inp[i] & 0xF0) >> 4;
		wire_order[i] = ts_dev->config_inp[i] & 0x0F;
		अगर (WARN_ON(analog_line[i] > 7))
			वापस -EINVAL;
		अगर (WARN_ON(wire_order[i] > ARRAY_SIZE(config_pins)))
			वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक an_line;
		पूर्णांक wi_order;

		an_line = analog_line[i];
		wi_order = wire_order[i];
		bit_cfg = config_pins[wi_order];
		अगर (bit_cfg == 0)
			वापस -EINVAL;
		चयन (wi_order) अणु
		हाल 0:
			ts_dev->bit_xp = bit_cfg;
			ts_dev->inp_xp = an_line;
			अवरोध;

		हाल 1:
			ts_dev->bit_xn = bit_cfg;
			ts_dev->inp_xn = an_line;
			अवरोध;

		हाल 2:
			ts_dev->bit_yp = bit_cfg;
			ts_dev->inp_yp = an_line;
			अवरोध;
		हाल 3:
			ts_dev->bit_yn = bit_cfg;
			ts_dev->inp_yn = an_line;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम titsc_step_config(काष्ठा titsc *ts_dev)
अणु
	अचिन्हित पूर्णांक	config;
	पूर्णांक i;
	पूर्णांक end_step, first_step, tsc_steps;
	u32 stepenable;

	config = STEPCONFIG_MODE_HWSYNC |
			STEPCONFIG_AVG_16 | ts_dev->bit_xp;
	चयन (ts_dev->wires) अणु
	हाल 4:
		config |= STEPCONFIG_INP(ts_dev->inp_yp) | ts_dev->bit_xn;
		अवरोध;
	हाल 5:
		config |= ts_dev->bit_yn |
				STEPCONFIG_INP_AN4 | ts_dev->bit_xn |
				ts_dev->bit_yp;
		अवरोध;
	हाल 8:
		config |= STEPCONFIG_INP(ts_dev->inp_yp) | ts_dev->bit_xn;
		अवरोध;
	पूर्ण

	tsc_steps = ts_dev->coordinate_पढ़ोouts * 2 + 2;
	first_step = TOTAL_STEPS - tsc_steps;
	/* Steps 16 to 16-coordinate_पढ़ोouts is क्रम X */
	end_step = first_step + tsc_steps;
	क्रम (i = end_step - ts_dev->coordinate_पढ़ोouts; i < end_step; i++) अणु
		titsc_ग_लिखोl(ts_dev, REG_STEPCONFIG(i), config);
		titsc_ग_लिखोl(ts_dev, REG_STEPDELAY(i), STEPCONFIG_OPENDLY);
	पूर्ण

	config = 0;
	config = STEPCONFIG_MODE_HWSYNC |
			STEPCONFIG_AVG_16 | ts_dev->bit_yn |
			STEPCONFIG_INM_ADCREFM;
	चयन (ts_dev->wires) अणु
	हाल 4:
		config |= ts_dev->bit_yp | STEPCONFIG_INP(ts_dev->inp_xp);
		अवरोध;
	हाल 5:
		config |= ts_dev->bit_xp | STEPCONFIG_INP_AN4 |
				STEPCONFIG_XNP | STEPCONFIG_YPN;
		अवरोध;
	हाल 8:
		config |= ts_dev->bit_yp | STEPCONFIG_INP(ts_dev->inp_xp);
		अवरोध;
	पूर्ण

	/* 1 ... coordinate_पढ़ोouts is क्रम Y */
	end_step = first_step + ts_dev->coordinate_पढ़ोouts;
	क्रम (i = first_step; i < end_step; i++) अणु
		titsc_ग_लिखोl(ts_dev, REG_STEPCONFIG(i), config);
		titsc_ग_लिखोl(ts_dev, REG_STEPDELAY(i), STEPCONFIG_OPENDLY);
	पूर्ण

	/* Make CHARGECONFIG same as IDLECONFIG */

	config = titsc_पढ़ोl(ts_dev, REG_IDLECONFIG);
	titsc_ग_लिखोl(ts_dev, REG_CHARGECONFIG, config);
	titsc_ग_लिखोl(ts_dev, REG_CHARGEDELAY, ts_dev->अक्षरge_delay);

	/* coordinate_पढ़ोouts + 1 ... coordinate_पढ़ोouts + 2 is क्रम Z */
	config = STEPCONFIG_MODE_HWSYNC |
			STEPCONFIG_AVG_16 | ts_dev->bit_yp |
			ts_dev->bit_xn | STEPCONFIG_INM_ADCREFM |
			STEPCONFIG_INP(ts_dev->inp_xp);
	titsc_ग_लिखोl(ts_dev, REG_STEPCONFIG(end_step), config);
	titsc_ग_लिखोl(ts_dev, REG_STEPDELAY(end_step),
			STEPCONFIG_OPENDLY);

	end_step++;
	config |= STEPCONFIG_INP(ts_dev->inp_yn);
	titsc_ग_लिखोl(ts_dev, REG_STEPCONFIG(end_step), config);
	titsc_ग_लिखोl(ts_dev, REG_STEPDELAY(end_step),
			STEPCONFIG_OPENDLY);

	/* The steps end ... end - पढ़ोouts * 2 + 2 and bit 0 क्रम TS_Charge */
	stepenable = 1;
	क्रम (i = 0; i < tsc_steps; i++)
		stepenable |= 1 << (first_step + i + 1);

	ts_dev->step_mask = stepenable;
	am335x_tsc_se_set_cache(ts_dev->mfd_tscadc, ts_dev->step_mask);
पूर्ण

अटल पूर्णांक titsc_cmp_coord(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(पूर्णांक *)a - *(पूर्णांक *)b;
पूर्ण

अटल व्योम titsc_पढ़ो_coordinates(काष्ठा titsc *ts_dev,
		u32 *x, u32 *y, u32 *z1, u32 *z2)
अणु
	अचिन्हित पूर्णांक yvals[7], xvals[7];
	अचिन्हित पूर्णांक i, xsum = 0, ysum = 0;
	अचिन्हित पूर्णांक cपढ़ोs = ts_dev->coordinate_पढ़ोouts;

	क्रम (i = 0; i < cपढ़ोs; i++) अणु
		yvals[i] = titsc_पढ़ोl(ts_dev, REG_FIFO0);
		yvals[i] &= 0xfff;
	पूर्ण

	*z1 = titsc_पढ़ोl(ts_dev, REG_FIFO0);
	*z1 &= 0xfff;
	*z2 = titsc_पढ़ोl(ts_dev, REG_FIFO0);
	*z2 &= 0xfff;

	क्रम (i = 0; i < cपढ़ोs; i++) अणु
		xvals[i] = titsc_पढ़ोl(ts_dev, REG_FIFO0);
		xvals[i] &= 0xfff;
	पूर्ण

	/*
	 * If co-ordinates पढ़ोouts is less than 4 then
	 * report the average. In हाल of 4 or more
	 * पढ़ोouts, sort the co-ordinate samples, drop
	 * min and max values and report the average of
	 * reमुख्यing values.
	 */
	अगर (cपढ़ोs <=  3) अणु
		क्रम (i = 0; i < cपढ़ोs; i++) अणु
			ysum += yvals[i];
			xsum += xvals[i];
		पूर्ण
		ysum /= cपढ़ोs;
		xsum /= cपढ़ोs;
	पूर्ण अन्यथा अणु
		sort(yvals, cपढ़ोs, माप(अचिन्हित पूर्णांक),
		     titsc_cmp_coord, शून्य);
		sort(xvals, cपढ़ोs, माप(अचिन्हित पूर्णांक),
		     titsc_cmp_coord, शून्य);
		क्रम (i = 1; i < cपढ़ोs - 1; i++) अणु
			ysum += yvals[i];
			xsum += xvals[i];
		पूर्ण
		ysum /= cपढ़ोs - 2;
		xsum /= cपढ़ोs - 2;
	पूर्ण
	*y = ysum;
	*x = xsum;
पूर्ण

अटल irqवापस_t titsc_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा titsc *ts_dev = dev;
	काष्ठा input_dev *input_dev = ts_dev->input;
	अचिन्हित पूर्णांक fsm, status, irqclr = 0;
	अचिन्हित पूर्णांक x = 0, y = 0;
	अचिन्हित पूर्णांक z1, z2, z;

	status = titsc_पढ़ोl(ts_dev, REG_RAWIRQSTATUS);
	अगर (status & IRQENB_HW_PEN) अणु
		ts_dev->pen_करोwn = true;
		irqclr |= IRQENB_HW_PEN;
		pm_stay_awake(ts_dev->dev);
	पूर्ण

	अगर (status & IRQENB_PENUP) अणु
		fsm = titsc_पढ़ोl(ts_dev, REG_ADCFSM);
		अगर (fsm == ADCFSM_STEPID) अणु
			ts_dev->pen_करोwn = false;
			input_report_key(input_dev, BTN_TOUCH, 0);
			input_report_असल(input_dev, ABS_PRESSURE, 0);
			input_sync(input_dev);
			pm_relax(ts_dev->dev);
		पूर्ण अन्यथा अणु
			ts_dev->pen_करोwn = true;
		पूर्ण
		irqclr |= IRQENB_PENUP;
	पूर्ण

	अगर (status & IRQENB_EOS)
		irqclr |= IRQENB_EOS;

	/*
	 * ADC and touchscreen share the IRQ line.
	 * FIFO1 पूर्णांकerrupts are used by ADC. Handle FIFO0 IRQs here only
	 */
	अगर (status & IRQENB_FIFO0THRES) अणु

		titsc_पढ़ो_coordinates(ts_dev, &x, &y, &z1, &z2);

		अगर (ts_dev->pen_करोwn && z1 != 0 && z2 != 0) अणु
			/*
			 * Calculate pressure using क्रमmula
			 * Resistance(touch) = x plate resistance *
			 * x postion/4096 * ((z2 / z1) - 1)
			 */
			z = z1 - z2;
			z *= x;
			z *= ts_dev->x_plate_resistance;
			z /= z2;
			z = (z + 2047) >> 12;

			अगर (z <= MAX_12BIT) अणु
				input_report_असल(input_dev, ABS_X, x);
				input_report_असल(input_dev, ABS_Y, y);
				input_report_असल(input_dev, ABS_PRESSURE, z);
				input_report_key(input_dev, BTN_TOUCH, 1);
				input_sync(input_dev);
			पूर्ण
		पूर्ण
		irqclr |= IRQENB_FIFO0THRES;
	पूर्ण
	अगर (irqclr) अणु
		titsc_ग_लिखोl(ts_dev, REG_IRQSTATUS, irqclr);
		अगर (status & IRQENB_EOS)
			am335x_tsc_se_set_cache(ts_dev->mfd_tscadc,
						ts_dev->step_mask);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक titsc_parse_dt(काष्ठा platक्रमm_device *pdev,
					काष्ठा titsc *ts_dev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक err;

	अगर (!node)
		वापस -EINVAL;

	err = of_property_पढ़ो_u32(node, "ti,wires", &ts_dev->wires);
	अगर (err < 0)
		वापस err;
	चयन (ts_dev->wires) अणु
	हाल 4:
	हाल 5:
	हाल 8:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = of_property_पढ़ो_u32(node, "ti,x-plate-resistance",
			&ts_dev->x_plate_resistance);
	अगर (err < 0)
		वापस err;

	/*
	 * Try with the new binding first. If it fails, try again with
	 * bogus, miss-spelled version.
	 */
	err = of_property_पढ़ो_u32(node, "ti,coordinate-readouts",
			&ts_dev->coordinate_पढ़ोouts);
	अगर (err < 0) अणु
		dev_warn(&pdev->dev, "please use 'ti,coordinate-readouts' instead\n");
		err = of_property_पढ़ो_u32(node, "ti,coordiante-readouts",
				&ts_dev->coordinate_पढ़ोouts);
	पूर्ण

	अगर (err < 0)
		वापस err;

	अगर (ts_dev->coordinate_पढ़ोouts <= 0) अणु
		dev_warn(&pdev->dev,
			 "invalid co-ordinate readouts, resetting it to 5\n");
		ts_dev->coordinate_पढ़ोouts = 5;
	पूर्ण

	err = of_property_पढ़ो_u32(node, "ti,charge-delay",
				   &ts_dev->अक्षरge_delay);
	/*
	 * If ti,अक्षरge-delay value is not specअगरied, then use
	 * CHARGEDLY_OPENDLY as the शेष value.
	 */
	अगर (err < 0) अणु
		ts_dev->अक्षरge_delay = CHARGEDLY_OPENDLY;
		dev_warn(&pdev->dev, "ti,charge-delay not specified\n");
	पूर्ण

	वापस of_property_पढ़ो_u32_array(node, "ti,wire-config",
			ts_dev->config_inp, ARRAY_SIZE(ts_dev->config_inp));
पूर्ण

/*
 * The functions क्रम inserting/removing driver as a module.
 */

अटल पूर्णांक titsc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा titsc *ts_dev;
	काष्ठा input_dev *input_dev;
	काष्ठा ti_tscadc_dev *tscadc_dev = ti_tscadc_dev_get(pdev);
	पूर्णांक err;

	/* Allocate memory क्रम device */
	ts_dev = kzalloc(माप(*ts_dev), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!ts_dev || !input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate memory.\n");
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	tscadc_dev->tsc = ts_dev;
	ts_dev->mfd_tscadc = tscadc_dev;
	ts_dev->input = input_dev;
	ts_dev->irq = tscadc_dev->irq;
	ts_dev->dev = &pdev->dev;

	err = titsc_parse_dt(pdev, ts_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Could not find valid DT data.\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	err = request_irq(ts_dev->irq, titsc_irq,
			  IRQF_SHARED, pdev->dev.driver->name, ts_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to allocate irq.\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);
	err = dev_pm_set_wake_irq(&pdev->dev, ts_dev->irq);
	अगर (err)
		dev_err(&pdev->dev, "irq wake enable failed.\n");

	titsc_ग_लिखोl(ts_dev, REG_IRQSTATUS, TSC_IRQENB_MASK);
	titsc_ग_लिखोl(ts_dev, REG_IRQENABLE, IRQENB_FIFO0THRES);
	titsc_ग_लिखोl(ts_dev, REG_IRQENABLE, IRQENB_EOS);
	err = titsc_config_wires(ts_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "wrong i/p wire configuration\n");
		जाओ err_मुक्त_irq;
	पूर्ण
	titsc_step_config(ts_dev);
	titsc_ग_लिखोl(ts_dev, REG_FIFO0THR,
			ts_dev->coordinate_पढ़ोouts * 2 + 2 - 1);

	input_dev->name = "ti-tsc";
	input_dev->dev.parent = &pdev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_असल_params(input_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, MAX_12BIT, 0, 0);

	/* रेजिस्टर to the input प्रणाली */
	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ err_मुक्त_irq;

	platक्रमm_set_drvdata(pdev, ts_dev);
	वापस 0;

err_मुक्त_irq:
	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	मुक्त_irq(ts_dev->irq, ts_dev);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(ts_dev);
	वापस err;
पूर्ण

अटल पूर्णांक titsc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा titsc *ts_dev = platक्रमm_get_drvdata(pdev);
	u32 steps;

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	मुक्त_irq(ts_dev->irq, ts_dev);

	/* total steps followed by the enable mask */
	steps = 2 * ts_dev->coordinate_पढ़ोouts + 2;
	steps = (1 << steps) - 1;
	am335x_tsc_se_clr(ts_dev->mfd_tscadc, steps);

	input_unरेजिस्टर_device(ts_dev->input);

	kमुक्त(ts_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused titsc_suspend(काष्ठा device *dev)
अणु
	काष्ठा titsc *ts_dev = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक idle;

	अगर (device_may_wakeup(dev)) अणु
		titsc_ग_लिखोl(ts_dev, REG_IRQSTATUS, TSC_IRQENB_MASK);
		idle = titsc_पढ़ोl(ts_dev, REG_IRQENABLE);
		titsc_ग_लिखोl(ts_dev, REG_IRQENABLE,
				(idle | IRQENB_HW_PEN));
		titsc_ग_लिखोl(ts_dev, REG_IRQWAKEUP, IRQWKUP_ENB);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused titsc_resume(काष्ठा device *dev)
अणु
	काष्ठा titsc *ts_dev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		titsc_ग_लिखोl(ts_dev, REG_IRQWAKEUP,
				0x00);
		titsc_ग_लिखोl(ts_dev, REG_IRQCLR, IRQENB_HW_PEN);
		pm_relax(dev);
	पूर्ण
	titsc_step_config(ts_dev);
	titsc_ग_लिखोl(ts_dev, REG_FIFO0THR,
			ts_dev->coordinate_पढ़ोouts * 2 + 2 - 1);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(titsc_pm_ops, titsc_suspend, titsc_resume);

अटल स्थिर काष्ठा of_device_id ti_tsc_dt_ids[] = अणु
	अणु .compatible = "ti,am3359-tsc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_tsc_dt_ids);

अटल काष्ठा platक्रमm_driver ti_tsc_driver = अणु
	.probe	= titsc_probe,
	.हटाओ	= titsc_हटाओ,
	.driver	= अणु
		.name   = "TI-am335x-tsc",
		.pm	= &titsc_pm_ops,
		.of_match_table = ti_tsc_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_tsc_driver);

MODULE_DESCRIPTION("TI touchscreen controller driver");
MODULE_AUTHOR("Rachna Patil <rachna@ti.com>");
MODULE_LICENSE("GPL");
