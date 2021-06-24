<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Motorola PCAP2 touchscreen as found in the EZX phone platक्रमm.
 *
 *  Copyright (C) 2006 Harald Welte <laक्रमge@खोलोezx.org>
 *  Copyright (C) 2009 Daniel Ribeiro <drwyrm@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/ezx-pcap.h>

काष्ठा pcap_ts अणु
	काष्ठा pcap_chip *pcap;
	काष्ठा input_dev *input;
	काष्ठा delayed_work work;
	u16 x, y;
	u16 pressure;
	u8 पढ़ो_state;
पूर्ण;

#घोषणा SAMPLE_DELAY	20 /* msecs */

#घोषणा X_AXIS_MIN	0
#घोषणा X_AXIS_MAX	1023
#घोषणा Y_AXIS_MAX	X_AXIS_MAX
#घोषणा Y_AXIS_MIN	X_AXIS_MIN
#घोषणा PRESSURE_MAX	X_AXIS_MAX
#घोषणा PRESSURE_MIN	X_AXIS_MIN

अटल व्योम pcap_ts_पढ़ो_xy(व्योम *data, u16 res[2])
अणु
	काष्ठा pcap_ts *pcap_ts = data;

	चयन (pcap_ts->पढ़ो_state) अणु
	हाल PCAP_ADC_TS_M_PRESSURE:
		/* pressure पढ़ोing is unreliable */
		अगर (res[0] > PRESSURE_MIN && res[0] < PRESSURE_MAX)
			pcap_ts->pressure = res[0];
		pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_XY;
		schedule_delayed_work(&pcap_ts->work, 0);
		अवरोध;
	हाल PCAP_ADC_TS_M_XY:
		pcap_ts->y = res[0];
		pcap_ts->x = res[1];
		अगर (pcap_ts->x <= X_AXIS_MIN || pcap_ts->x >= X_AXIS_MAX ||
		    pcap_ts->y <= Y_AXIS_MIN || pcap_ts->y >= Y_AXIS_MAX) अणु
			/* pen has been released */
			input_report_असल(pcap_ts->input, ABS_PRESSURE, 0);
			input_report_key(pcap_ts->input, BTN_TOUCH, 0);

			pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_STANDBY;
			schedule_delayed_work(&pcap_ts->work, 0);
		पूर्ण अन्यथा अणु
			/* pen is touching the screen */
			input_report_असल(pcap_ts->input, ABS_X, pcap_ts->x);
			input_report_असल(pcap_ts->input, ABS_Y, pcap_ts->y);
			input_report_key(pcap_ts->input, BTN_TOUCH, 1);
			input_report_असल(pcap_ts->input, ABS_PRESSURE,
						pcap_ts->pressure);

			/* चयन back to pressure पढ़ो mode */
			pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_PRESSURE;
			schedule_delayed_work(&pcap_ts->work,
					msecs_to_jअगरfies(SAMPLE_DELAY));
		पूर्ण
		input_sync(pcap_ts->input);
		अवरोध;
	शेष:
		dev_warn(&pcap_ts->input->dev,
				"pcap_ts: Warning, unhandled read_state %d\n",
				pcap_ts->पढ़ो_state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pcap_ts_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा pcap_ts *pcap_ts = container_of(dw, काष्ठा pcap_ts, work);
	u8 ch[2];

	pcap_set_ts_bits(pcap_ts->pcap,
			pcap_ts->पढ़ो_state << PCAP_ADC_TS_M_SHIFT);

	अगर (pcap_ts->पढ़ो_state == PCAP_ADC_TS_M_STANDBY)
		वापस;

	/* start adc conversion */
	ch[0] = PCAP_ADC_CH_TS_X1;
	ch[1] = PCAP_ADC_CH_TS_Y1;
	pcap_adc_async(pcap_ts->pcap, PCAP_ADC_BANK_1, 0, ch,
						pcap_ts_पढ़ो_xy, pcap_ts);
पूर्ण

अटल irqवापस_t pcap_ts_event_touch(पूर्णांक pirq, व्योम *data)
अणु
	काष्ठा pcap_ts *pcap_ts = data;

	अगर (pcap_ts->पढ़ो_state == PCAP_ADC_TS_M_STANDBY) अणु
		pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_PRESSURE;
		schedule_delayed_work(&pcap_ts->work, 0);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcap_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pcap_ts *pcap_ts = input_get_drvdata(dev);

	pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_STANDBY;
	schedule_delayed_work(&pcap_ts->work, 0);

	वापस 0;
पूर्ण

अटल व्योम pcap_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pcap_ts *pcap_ts = input_get_drvdata(dev);

	cancel_delayed_work_sync(&pcap_ts->work);

	pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_NONTS;
	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->पढ़ो_state << PCAP_ADC_TS_M_SHIFT);
पूर्ण

अटल पूर्णांक pcap_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input_dev;
	काष्ठा pcap_ts *pcap_ts;
	पूर्णांक err = -ENOMEM;

	pcap_ts = kzalloc(माप(*pcap_ts), GFP_KERNEL);
	अगर (!pcap_ts)
		वापस err;

	pcap_ts->pcap = dev_get_drvdata(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, pcap_ts);

	input_dev = input_allocate_device();
	अगर (!input_dev)
		जाओ fail;

	INIT_DELAYED_WORK(&pcap_ts->work, pcap_ts_work);

	pcap_ts->पढ़ो_state = PCAP_ADC_TS_M_NONTS;
	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->पढ़ो_state << PCAP_ADC_TS_M_SHIFT);

	pcap_ts->input = input_dev;
	input_set_drvdata(input_dev, pcap_ts);

	input_dev->name = "pcap-touchscreen";
	input_dev->phys = "pcap_ts/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0002;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &pdev->dev;
	input_dev->खोलो = pcap_ts_खोलो;
	input_dev->बंद = pcap_ts_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, X_AXIS_MIN, X_AXIS_MAX, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, Y_AXIS_MIN, Y_AXIS_MAX, 0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, PRESSURE_MIN,
			     PRESSURE_MAX, 0, 0);

	err = input_रेजिस्टर_device(pcap_ts->input);
	अगर (err)
		जाओ fail_allocate;

	err = request_irq(pcap_to_irq(pcap_ts->pcap, PCAP_IRQ_TS),
			pcap_ts_event_touch, 0, "Touch Screen", pcap_ts);
	अगर (err)
		जाओ fail_रेजिस्टर;

	वापस 0;

fail_रेजिस्टर:
	input_unरेजिस्टर_device(input_dev);
	जाओ fail;
fail_allocate:
	input_मुक्त_device(input_dev);
fail:
	kमुक्त(pcap_ts);

	वापस err;
पूर्ण

अटल पूर्णांक pcap_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcap_ts *pcap_ts = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(pcap_to_irq(pcap_ts->pcap, PCAP_IRQ_TS), pcap_ts);
	cancel_delayed_work_sync(&pcap_ts->work);

	input_unरेजिस्टर_device(pcap_ts->input);

	kमुक्त(pcap_ts);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pcap_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा pcap_ts *pcap_ts = dev_get_drvdata(dev);

	pcap_set_ts_bits(pcap_ts->pcap, PCAP_ADC_TS_REF_LOWPWR);
	वापस 0;
पूर्ण

अटल पूर्णांक pcap_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा pcap_ts *pcap_ts = dev_get_drvdata(dev);

	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->पढ़ो_state << PCAP_ADC_TS_M_SHIFT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pcap_ts_pm_ops = अणु
	.suspend	= pcap_ts_suspend,
	.resume		= pcap_ts_resume,
पूर्ण;
#घोषणा PCAP_TS_PM_OPS (&pcap_ts_pm_ops)
#अन्यथा
#घोषणा PCAP_TS_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pcap_ts_driver = अणु
	.probe		= pcap_ts_probe,
	.हटाओ		= pcap_ts_हटाओ,
	.driver		= अणु
		.name	= "pcap-ts",
		.pm	= PCAP_TS_PM_OPS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pcap_ts_driver);

MODULE_DESCRIPTION("Motorola PCAP2 touchscreen driver");
MODULE_AUTHOR("Daniel Ribeiro / Harald Welte");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcap_ts");
