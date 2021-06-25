<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Touchscreen driver क्रम WM831x PMICs
 *
 * Copyright 2011 Wolfson Microelectronics plc.
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/pm.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/irq.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/*
 * R16424 (0x4028) - Touch Control 1
 */
#घोषणा WM831X_TCH_ENA                          0x8000  /* TCH_ENA */
#घोषणा WM831X_TCH_CVT_ENA                      0x4000  /* TCH_CVT_ENA */
#घोषणा WM831X_TCH_SLPENA                       0x1000  /* TCH_SLPENA */
#घोषणा WM831X_TCH_Z_ENA                        0x0400  /* TCH_Z_ENA */
#घोषणा WM831X_TCH_Y_ENA                        0x0200  /* TCH_Y_ENA */
#घोषणा WM831X_TCH_X_ENA                        0x0100  /* TCH_X_ENA */
#घोषणा WM831X_TCH_DELAY_MASK                   0x00E0  /* TCH_DELAY - [7:5] */
#घोषणा WM831X_TCH_DELAY_SHIFT                       5  /* TCH_DELAY - [7:5] */
#घोषणा WM831X_TCH_DELAY_WIDTH                       3  /* TCH_DELAY - [7:5] */
#घोषणा WM831X_TCH_RATE_MASK                    0x001F  /* TCH_RATE - [4:0] */
#घोषणा WM831X_TCH_RATE_SHIFT                        0  /* TCH_RATE - [4:0] */
#घोषणा WM831X_TCH_RATE_WIDTH                        5  /* TCH_RATE - [4:0] */

/*
 * R16425 (0x4029) - Touch Control 2
 */
#घोषणा WM831X_TCH_PD_WK                        0x2000  /* TCH_PD_WK */
#घोषणा WM831X_TCH_5WIRE                        0x1000  /* TCH_5WIRE */
#घोषणा WM831X_TCH_PDONLY                       0x0800  /* TCH_PDONLY */
#घोषणा WM831X_TCH_ISEL                         0x0100  /* TCH_ISEL */
#घोषणा WM831X_TCH_RPU_MASK                     0x000F  /* TCH_RPU - [3:0] */
#घोषणा WM831X_TCH_RPU_SHIFT                         0  /* TCH_RPU - [3:0] */
#घोषणा WM831X_TCH_RPU_WIDTH                         4  /* TCH_RPU - [3:0] */

/*
 * R16426-8 (0x402A-C) - Touch Data X/Y/X
 */
#घोषणा WM831X_TCH_PD                           0x8000  /* TCH_PD1 */
#घोषणा WM831X_TCH_DATA_MASK                    0x0FFF  /* TCH_DATA - [11:0] */
#घोषणा WM831X_TCH_DATA_SHIFT                        0  /* TCH_DATA - [11:0] */
#घोषणा WM831X_TCH_DATA_WIDTH                       12  /* TCH_DATA - [11:0] */

काष्ठा wm831x_ts अणु
	काष्ठा input_dev *input_dev;
	काष्ठा wm831x *wm831x;
	अचिन्हित पूर्णांक data_irq;
	अचिन्हित पूर्णांक pd_irq;
	bool pressure;
	bool pen_करोwn;
	काष्ठा work_काष्ठा pd_data_work;
पूर्ण;

अटल व्योम wm831x_pd_data_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm831x_ts *wm831x_ts =
		container_of(work, काष्ठा wm831x_ts, pd_data_work);

	अगर (wm831x_ts->pen_करोwn) अणु
		enable_irq(wm831x_ts->data_irq);
		dev_dbg(wm831x_ts->wm831x->dev, "IRQ PD->DATA done\n");
	पूर्ण अन्यथा अणु
		enable_irq(wm831x_ts->pd_irq);
		dev_dbg(wm831x_ts->wm831x->dev, "IRQ DATA->PD done\n");
	पूर्ण
पूर्ण

अटल irqवापस_t wm831x_ts_data_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा wm831x_ts *wm831x_ts = irq_data;
	काष्ठा wm831x *wm831x = wm831x_ts->wm831x;
	अटल पूर्णांक data_types[] = अणु ABS_X, ABS_Y, ABS_PRESSURE पूर्ण;
	u16 data[3];
	पूर्णांक count;
	पूर्णांक i, ret;

	अगर (wm831x_ts->pressure)
		count = 3;
	अन्यथा
		count = 2;

	wm831x_set_bits(wm831x, WM831X_INTERRUPT_STATUS_1,
			WM831X_TCHDATA_EINT, WM831X_TCHDATA_EINT);

	ret = wm831x_bulk_पढ़ो(wm831x, WM831X_TOUCH_DATA_X, count,
			       data);
	अगर (ret != 0) अणु
		dev_err(wm831x->dev, "Failed to read touch data: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * We get a pen करोwn पढ़ोing on every पढ़ोing, report pen up अगर any
	 * inभागidual पढ़ोing करोes so.
	 */
	wm831x_ts->pen_करोwn = true;
	क्रम (i = 0; i < count; i++) अणु
		अगर (!(data[i] & WM831X_TCH_PD)) अणु
			wm831x_ts->pen_करोwn = false;
			जारी;
		पूर्ण
		input_report_असल(wm831x_ts->input_dev, data_types[i],
				 data[i] & WM831X_TCH_DATA_MASK);
	पूर्ण

	अगर (!wm831x_ts->pen_करोwn) अणु
		/* Switch from data to pen करोwn */
		dev_dbg(wm831x->dev, "IRQ DATA->PD\n");

		disable_irq_nosync(wm831x_ts->data_irq);

		/* Don't need data any more */
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
				WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA |
				WM831X_TCH_Z_ENA, 0);

		/* Flush any final samples that arrived जबतक पढ़ोing */
		wm831x_set_bits(wm831x, WM831X_INTERRUPT_STATUS_1,
				WM831X_TCHDATA_EINT, WM831X_TCHDATA_EINT);

		wm831x_bulk_पढ़ो(wm831x, WM831X_TOUCH_DATA_X, count, data);

		अगर (wm831x_ts->pressure)
			input_report_असल(wm831x_ts->input_dev,
					 ABS_PRESSURE, 0);

		input_report_key(wm831x_ts->input_dev, BTN_TOUCH, 0);

		schedule_work(&wm831x_ts->pd_data_work);
	पूर्ण अन्यथा अणु
		input_report_key(wm831x_ts->input_dev, BTN_TOUCH, 1);
	पूर्ण

	input_sync(wm831x_ts->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm831x_ts_pen_करोwn_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा wm831x_ts *wm831x_ts = irq_data;
	काष्ठा wm831x *wm831x = wm831x_ts->wm831x;
	पूर्णांक ena = 0;

	अगर (wm831x_ts->pen_करोwn)
		वापस IRQ_HANDLED;

	disable_irq_nosync(wm831x_ts->pd_irq);

	/* Start collecting data */
	अगर (wm831x_ts->pressure)
		ena |= WM831X_TCH_Z_ENA;

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA | WM831X_TCH_Z_ENA,
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA | ena);

	wm831x_set_bits(wm831x, WM831X_INTERRUPT_STATUS_1,
			WM831X_TCHPD_EINT, WM831X_TCHPD_EINT);

	wm831x_ts->pen_करोwn = true;

	/* Switch from pen करोwn to data */
	dev_dbg(wm831x->dev, "IRQ PD->DATA\n");
	schedule_work(&wm831x_ts->pd_data_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm831x_ts_input_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा wm831x_ts *wm831x_ts = input_get_drvdata(idev);
	काष्ठा wm831x *wm831x = wm831x_ts->wm831x;

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_ENA | WM831X_TCH_CVT_ENA |
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA |
			WM831X_TCH_Z_ENA, WM831X_TCH_ENA);

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_CVT_ENA, WM831X_TCH_CVT_ENA);

	वापस 0;
पूर्ण

अटल व्योम wm831x_ts_input_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा wm831x_ts *wm831x_ts = input_get_drvdata(idev);
	काष्ठा wm831x *wm831x = wm831x_ts->wm831x;

	/* Shut the controller करोwn, disabling all other functionality too */
	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_ENA | WM831X_TCH_X_ENA |
			WM831X_TCH_Y_ENA | WM831X_TCH_Z_ENA, 0);

	/* Make sure any pending IRQs are करोne, the above will prevent
	 * new ones firing.
	 */
	synchronize_irq(wm831x_ts->data_irq);
	synchronize_irq(wm831x_ts->pd_irq);

	/* Make sure the IRQ completion work is quiesced */
	flush_work(&wm831x_ts->pd_data_work);

	/* If we ended up with the pen करोwn then make sure we revert back
	 * to pen detection state क्रम the next समय we start up.
	 */
	अगर (wm831x_ts->pen_करोwn) अणु
		disable_irq(wm831x_ts->data_irq);
		enable_irq(wm831x_ts->pd_irq);
		wm831x_ts->pen_करोwn = false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm831x_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x_ts *wm831x_ts;
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *core_pdata = dev_get_platdata(pdev->dev.parent);
	काष्ठा wm831x_touch_pdata *pdata = शून्य;
	काष्ठा input_dev *input_dev;
	पूर्णांक error, irqf;

	अगर (core_pdata)
		pdata = core_pdata->touch;

	wm831x_ts = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_ts),
				 GFP_KERNEL);
	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!wm831x_ts || !input_dev) अणु
		error = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	wm831x_ts->wm831x = wm831x;
	wm831x_ts->input_dev = input_dev;
	INIT_WORK(&wm831x_ts->pd_data_work, wm831x_pd_data_work);

	/*
	 * If we have a direct IRQ use it, otherwise use the पूर्णांकerrupt
	 * from the WM831x IRQ controller.
	 */
	wm831x_ts->data_irq = wm831x_irq(wm831x,
					 platक्रमm_get_irq_byname(pdev,
								 "TCHDATA"));
	अगर (pdata && pdata->data_irq)
		wm831x_ts->data_irq = pdata->data_irq;

	wm831x_ts->pd_irq = wm831x_irq(wm831x,
				       platक्रमm_get_irq_byname(pdev, "TCHPD"));
	अगर (pdata && pdata->pd_irq)
		wm831x_ts->pd_irq = pdata->pd_irq;

	अगर (pdata)
		wm831x_ts->pressure = pdata->pressure;
	अन्यथा
		wm831x_ts->pressure = true;

	/* Five wire touchscreens can't report pressure */
	अगर (pdata && pdata->fivewire) अणु
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
				WM831X_TCH_5WIRE, WM831X_TCH_5WIRE);

		/* Pressure measurements are not possible क्रम five wire mode */
		WARN_ON(pdata->pressure && pdata->fivewire);
		wm831x_ts->pressure = false;
	पूर्ण अन्यथा अणु
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
				WM831X_TCH_5WIRE, 0);
	पूर्ण

	अगर (pdata) अणु
		चयन (pdata->isel) अणु
		शेष:
			dev_err(&pdev->dev, "Unsupported ISEL setting: %d\n",
				pdata->isel);
			fallthrough;
		हाल 200:
		हाल 0:
			wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
					WM831X_TCH_ISEL, 0);
			अवरोध;
		हाल 400:
			wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
					WM831X_TCH_ISEL, WM831X_TCH_ISEL);
			अवरोध;
		पूर्ण
	पूर्ण

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
			WM831X_TCH_PDONLY, 0);

	/* Default to 96 samples/sec */
	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_RATE_MASK, 6);

	अगर (pdata && pdata->data_irqf)
		irqf = pdata->data_irqf;
	अन्यथा
		irqf = IRQF_TRIGGER_HIGH;

	error = request_thपढ़ोed_irq(wm831x_ts->data_irq,
				     शून्य, wm831x_ts_data_irq,
				     irqf | IRQF_ONESHOT | IRQF_NO_AUTOEN,
				     "Touchscreen data", wm831x_ts);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to request data IRQ %d: %d\n",
			wm831x_ts->data_irq, error);
		जाओ err_alloc;
	पूर्ण

	अगर (pdata && pdata->pd_irqf)
		irqf = pdata->pd_irqf;
	अन्यथा
		irqf = IRQF_TRIGGER_HIGH;

	error = request_thपढ़ोed_irq(wm831x_ts->pd_irq,
				     शून्य, wm831x_ts_pen_करोwn_irq,
				     irqf | IRQF_ONESHOT,
				     "Touchscreen pen down", wm831x_ts);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to request pen down IRQ %d: %d\n",
			wm831x_ts->pd_irq, error);
		जाओ err_data_irq;
	पूर्ण

	/* set up touch configuration */
	input_dev->name = "WM831x touchscreen";
	input_dev->phys = "wm831x";
	input_dev->खोलो = wm831x_ts_input_खोलो;
	input_dev->बंद = wm831x_ts_input_बंद;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_X, 0, 4095, 5, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 4095, 5, 0);
	अगर (wm831x_ts->pressure)
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 4095, 5, 0);

	input_set_drvdata(input_dev, wm831x_ts);
	input_dev->dev.parent = &pdev->dev;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		जाओ err_pd_irq;

	platक्रमm_set_drvdata(pdev, wm831x_ts);
	वापस 0;

err_pd_irq:
	मुक्त_irq(wm831x_ts->pd_irq, wm831x_ts);
err_data_irq:
	मुक्त_irq(wm831x_ts->data_irq, wm831x_ts);
err_alloc:

	वापस error;
पूर्ण

अटल पूर्णांक wm831x_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x_ts *wm831x_ts = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(wm831x_ts->pd_irq, wm831x_ts);
	मुक्त_irq(wm831x_ts->data_irq, wm831x_ts);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_ts_driver = अणु
	.driver = अणु
		.name = "wm831x-touch",
	पूर्ण,
	.probe = wm831x_ts_probe,
	.हटाओ = wm831x_ts_हटाओ,
पूर्ण;
module_platक्रमm_driver(wm831x_ts_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM831x PMIC touchscreen driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-touch");
