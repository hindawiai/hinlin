<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STMicroelectronics STMPE811 Touchscreen Driver
 *
 * (C) 2010 Luotao Fu <l.fu@pengutronix.de>
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/mfd/sपंचांगpe.h>

/* Register layouts and functionalities are identical on all sपंचांगpexxx variants
 * with touchscreen controller
 */
#घोषणा STMPE_REG_INT_STA		0x0B
#घोषणा STMPE_REG_TSC_CTRL		0x40
#घोषणा STMPE_REG_TSC_CFG		0x41
#घोषणा STMPE_REG_FIFO_TH		0x4A
#घोषणा STMPE_REG_FIFO_STA		0x4B
#घोषणा STMPE_REG_FIFO_SIZE		0x4C
#घोषणा STMPE_REG_TSC_DATA_XYZ		0x52
#घोषणा STMPE_REG_TSC_FRACTION_Z	0x56
#घोषणा STMPE_REG_TSC_I_DRIVE		0x58

#घोषणा OP_MOD_XYZ			0

#घोषणा STMPE_TSC_CTRL_TSC_EN		(1<<0)

#घोषणा STMPE_FIFO_STA_RESET		(1<<0)

#घोषणा STMPE_IRQ_TOUCH_DET		0

#घोषणा STMPE_TS_NAME			"stmpe-ts"
#घोषणा XY_MASK				0xfff

/**
 * काष्ठा sपंचांगpe_touch - sपंचांगpe811 touch screen controller state
 * @sपंचांगpe: poपूर्णांकer back to STMPE MFD container
 * @idev: रेजिस्टरed input device
 * @work: a work item used to scan the device
 * @dev: a poपूर्णांकer back to the MFD cell काष्ठा device*
 * @prop: Touchscreen properties
 * @ave_ctrl: Sample average control
 * (0 -> 1 sample, 1 -> 2 samples, 2 -> 4 samples, 3 -> 8 samples)
 * @touch_det_delay: Touch detect पूर्णांकerrupt delay
 * (0 -> 10 us, 1 -> 50 us, 2 -> 100 us, 3 -> 500 us,
 * 4-> 1 ms, 5 -> 5 ms, 6 -> 10 ms, 7 -> 50 ms)
 * recommended is 3
 * @settling: Panel driver settling समय
 * (0 -> 10 us, 1 -> 100 us, 2 -> 500 us, 3 -> 1 ms,
 * 4 -> 5 ms, 5 -> 10 ms, 6 क्रम 50 ms, 7 -> 100 ms)
 * recommended is 2
 * @fraction_z: Length of the fractional part in z
 * (fraction_z ([0..7]) = Count of the fractional part)
 * recommended is 7
 * @i_drive: current limit value of the touchscreen drivers
 * (0 -> 20 mA typical 35 mA max, 1 -> 50 mA typical 80 mA max)
 */
काष्ठा sपंचांगpe_touch अणु
	काष्ठा sपंचांगpe *sपंचांगpe;
	काष्ठा input_dev *idev;
	काष्ठा delayed_work work;
	काष्ठा device *dev;
	काष्ठा touchscreen_properties prop;
	u8 ave_ctrl;
	u8 touch_det_delay;
	u8 settling;
	u8 fraction_z;
	u8 i_drive;
पूर्ण;

अटल पूर्णांक __sपंचांगpe_reset_fअगरo(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	पूर्णांक ret;

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_REG_FIFO_STA,
			STMPE_FIFO_STA_RESET, STMPE_FIFO_STA_RESET);
	अगर (ret)
		वापस ret;

	वापस sपंचांगpe_set_bits(sपंचांगpe, STMPE_REG_FIFO_STA,
			STMPE_FIFO_STA_RESET, 0);
पूर्ण

अटल व्योम sपंचांगpe_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक पूर्णांक_sta;
	u32 समयout = 40;

	काष्ठा sपंचांगpe_touch *ts =
	    container_of(work, काष्ठा sपंचांगpe_touch, work.work);

	पूर्णांक_sta = sपंचांगpe_reg_पढ़ो(ts->sपंचांगpe, STMPE_REG_INT_STA);

	/*
	 * touch_det someबार get desनिश्चितed or just get stuck. This appears
	 * to be a silicon bug, We still have to clearअगरy this with the
	 * manufacture. As a workaround We release the key anyway अगर the
	 * touch_det keeps coming in after 4ms, जबतक the FIFO contains no value
	 * during the whole समय.
	 */
	जबतक ((पूर्णांक_sta & (1 << STMPE_IRQ_TOUCH_DET)) && (समयout > 0)) अणु
		समयout--;
		पूर्णांक_sta = sपंचांगpe_reg_पढ़ो(ts->sपंचांगpe, STMPE_REG_INT_STA);
		udelay(100);
	पूर्ण

	/* reset the FIFO beक्रमe we report release event */
	__sपंचांगpe_reset_fअगरo(ts->sपंचांगpe);

	input_report_असल(ts->idev, ABS_PRESSURE, 0);
	input_report_key(ts->idev, BTN_TOUCH, 0);
	input_sync(ts->idev);
पूर्ण

अटल irqवापस_t sपंचांगpe_ts_handler(पूर्णांक irq, व्योम *data)
अणु
	u8 data_set[4];
	पूर्णांक x, y, z;
	काष्ठा sपंचांगpe_touch *ts = data;

	/*
	 * Cancel scheduled polling क्रम release अगर we have new value
	 * available. Wait अगर the polling is alपढ़ोy running.
	 */
	cancel_delayed_work_sync(&ts->work);

	/*
	 * The FIFO someबार just crashes and stops generating पूर्णांकerrupts. This
	 * appears to be a silicon bug. We still have to clearअगरy this with
	 * the manufacture. As a workaround we disable the TSC जबतक we are
	 * collecting data and flush the FIFO after पढ़ोing
	 */
	sपंचांगpe_set_bits(ts->sपंचांगpe, STMPE_REG_TSC_CTRL,
				STMPE_TSC_CTRL_TSC_EN, 0);

	sपंचांगpe_block_पढ़ो(ts->sपंचांगpe, STMPE_REG_TSC_DATA_XYZ, 4, data_set);

	x = (data_set[0] << 4) | (data_set[1] >> 4);
	y = ((data_set[1] & 0xf) << 8) | data_set[2];
	z = data_set[3];

	touchscreen_report_pos(ts->idev, &ts->prop, x, y, false);
	input_report_असल(ts->idev, ABS_PRESSURE, z);
	input_report_key(ts->idev, BTN_TOUCH, 1);
	input_sync(ts->idev);

       /* flush the FIFO after we have पढ़ो out our values. */
	__sपंचांगpe_reset_fअगरo(ts->sपंचांगpe);

	/* reenable the tsc */
	sपंचांगpe_set_bits(ts->sपंचांगpe, STMPE_REG_TSC_CTRL,
			STMPE_TSC_CTRL_TSC_EN, STMPE_TSC_CTRL_TSC_EN);

	/* start polling क्रम touch_det to detect release */
	schedule_delayed_work(&ts->work, msecs_to_jअगरfies(50));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांगpe_init_hw(काष्ठा sपंचांगpe_touch *ts)
अणु
	पूर्णांक ret;
	u8 tsc_cfg, tsc_cfg_mask;
	काष्ठा sपंचांगpe *sपंचांगpe = ts->sपंचांगpe;
	काष्ठा device *dev = ts->dev;

	ret = sपंचांगpe_enable(sपंचांगpe, STMPE_BLOCK_TOUCHSCREEN | STMPE_BLOCK_ADC);
	अगर (ret) अणु
		dev_err(dev, "Could not enable clock for ADC and TS\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगpe811_adc_common_init(sपंचांगpe);
	अगर (ret) अणु
		sपंचांगpe_disable(sपंचांगpe, STMPE_BLOCK_TOUCHSCREEN | STMPE_BLOCK_ADC);
		वापस ret;
	पूर्ण

	tsc_cfg = STMPE_AVE_CTRL(ts->ave_ctrl) |
		  STMPE_DET_DELAY(ts->touch_det_delay) |
		  STMPE_SETTLING(ts->settling);
	tsc_cfg_mask = STMPE_AVE_CTRL(0xff) | STMPE_DET_DELAY(0xff) |
		       STMPE_SETTLING(0xff);

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_REG_TSC_CFG, tsc_cfg_mask, tsc_cfg);
	अगर (ret) अणु
		dev_err(dev, "Could not config touch\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_REG_TSC_FRACTION_Z,
			STMPE_FRACTION_Z(0xff), STMPE_FRACTION_Z(ts->fraction_z));
	अगर (ret) अणु
		dev_err(dev, "Could not config touch\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_REG_TSC_I_DRIVE,
			STMPE_I_DRIVE(0xff), STMPE_I_DRIVE(ts->i_drive));
	अगर (ret) अणु
		dev_err(dev, "Could not config touch\n");
		वापस ret;
	पूर्ण

	/* set FIFO to 1 क्रम single poपूर्णांक पढ़ोing */
	ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe, STMPE_REG_FIFO_TH, 1);
	अगर (ret) अणु
		dev_err(dev, "Could not set FIFO\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_REG_TSC_CTRL,
			STMPE_OP_MODE(0xff), STMPE_OP_MODE(OP_MOD_XYZ));
	अगर (ret) अणु
		dev_err(dev, "Could not set mode\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा sपंचांगpe_touch *ts = input_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = __sपंचांगpe_reset_fअगरo(ts->sपंचांगpe);
	अगर (ret)
		वापस ret;

	वापस sपंचांगpe_set_bits(ts->sपंचांगpe, STMPE_REG_TSC_CTRL,
			STMPE_TSC_CTRL_TSC_EN, STMPE_TSC_CTRL_TSC_EN);
पूर्ण

अटल व्योम sपंचांगpe_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा sपंचांगpe_touch *ts = input_get_drvdata(dev);

	cancel_delayed_work_sync(&ts->work);

	sपंचांगpe_set_bits(ts->sपंचांगpe, STMPE_REG_TSC_CTRL,
			STMPE_TSC_CTRL_TSC_EN, 0);
पूर्ण

अटल व्योम sपंचांगpe_ts_get_platक्रमm_info(काष्ठा platक्रमm_device *pdev,
					काष्ठा sपंचांगpe_touch *ts)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 val;

	अगर (np) अणु
		अगर (!of_property_पढ़ो_u32(np, "st,sample-time", &val))
			ts->sपंचांगpe->sample_समय = val;
		अगर (!of_property_पढ़ो_u32(np, "st,mod-12b", &val))
			ts->sपंचांगpe->mod_12b = val;
		अगर (!of_property_पढ़ो_u32(np, "st,ref-sel", &val))
			ts->sपंचांगpe->ref_sel = val;
		अगर (!of_property_पढ़ो_u32(np, "st,adc-freq", &val))
			ts->sपंचांगpe->adc_freq = val;
		अगर (!of_property_पढ़ो_u32(np, "st,ave-ctrl", &val))
			ts->ave_ctrl = val;
		अगर (!of_property_पढ़ो_u32(np, "st,touch-det-delay", &val))
			ts->touch_det_delay = val;
		अगर (!of_property_पढ़ो_u32(np, "st,settling", &val))
			ts->settling = val;
		अगर (!of_property_पढ़ो_u32(np, "st,fraction-z", &val))
			ts->fraction_z = val;
		अगर (!of_property_पढ़ो_u32(np, "st,i-drive", &val))
			ts->i_drive = val;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगpe_input_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sपंचांगpe_touch *ts;
	काष्ठा input_dev *idev;
	पूर्णांक error;
	पूर्णांक ts_irq;

	ts_irq = platक्रमm_get_irq_byname(pdev, "FIFO_TH");
	अगर (ts_irq < 0)
		वापस ts_irq;

	ts = devm_kzalloc(&pdev->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	idev = devm_input_allocate_device(&pdev->dev);
	अगर (!idev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ts);
	ts->sपंचांगpe = sपंचांगpe;
	ts->idev = idev;
	ts->dev = &pdev->dev;

	sपंचांगpe_ts_get_platक्रमm_info(pdev, ts);

	INIT_DELAYED_WORK(&ts->work, sपंचांगpe_work);

	error = devm_request_thपढ़ोed_irq(&pdev->dev, ts_irq,
					  शून्य, sपंचांगpe_ts_handler,
					  IRQF_ONESHOT, STMPE_TS_NAME, ts);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to request IRQ %d\n", ts_irq);
		वापस error;
	पूर्ण

	error = sपंचांगpe_init_hw(ts);
	अगर (error)
		वापस error;

	idev->name = STMPE_TS_NAME;
	idev->phys = STMPE_TS_NAME"/input0";
	idev->id.bustype = BUS_I2C;

	idev->खोलो = sपंचांगpe_ts_खोलो;
	idev->बंद = sपंचांगpe_ts_बंद;

	input_set_drvdata(idev, ts);

	input_set_capability(idev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(idev, ABS_X, 0, XY_MASK, 0, 0);
	input_set_असल_params(idev, ABS_Y, 0, XY_MASK, 0, 0);
	input_set_असल_params(idev, ABS_PRESSURE, 0x0, 0xff, 0, 0);

	touchscreen_parse_properties(idev, false, &ts->prop);

	error = input_रेजिस्टर_device(idev);
	अगर (error) अणु
		dev_err(&pdev->dev, "Could not register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगpe_touch *ts = platक्रमm_get_drvdata(pdev);

	sपंचांगpe_disable(ts->sपंचांगpe, STMPE_BLOCK_TOUCHSCREEN);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांगpe_ts_driver = अणु
	.driver = अणु
		.name = STMPE_TS_NAME,
	पूर्ण,
	.probe = sपंचांगpe_input_probe,
	.हटाओ = sपंचांगpe_ts_हटाओ,
पूर्ण;
module_platक्रमm_driver(sपंचांगpe_ts_driver);

अटल स्थिर काष्ठा of_device_id sपंचांगpe_ts_ids[] = अणु
	अणु .compatible = "st,stmpe-ts", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगpe_ts_ids);

MODULE_AUTHOR("Luotao Fu <l.fu@pengutronix.de>");
MODULE_DESCRIPTION("STMPEXXX touchscreen driver");
MODULE_LICENSE("GPL");
