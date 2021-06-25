<शैली गुरु>
/*
 * Touchscreen driver क्रम the tps6507x chip.
 *
 * Copyright (c) 2009 RidgeRun (todd.fischer@ridgerun.com)
 *
 * Credits:
 *
 *    Using code from tsc2007, MtekVision Co., Ltd.
 *
 * For licencing details see kernel-base/COPYING
 *
 * TPS65070, TPS65073, TPS650731, and TPS650732 support
 * 10 bit touch screen पूर्णांकerface.
 */

#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/tps6507x.h>
#समावेश <linux/input/tps6507x-ts.h>
#समावेश <linux/delay.h>

#घोषणा TSC_DEFAULT_POLL_PERIOD 30 /* ms */
#घोषणा TPS_DEFAULT_MIN_PRESSURE 0x30
#घोषणा MAX_10BIT ((1 << 10) - 1)

#घोषणा	TPS6507X_ADCONFIG_CONVERT_TS (TPS6507X_ADCONFIG_AD_ENABLE | \
					 TPS6507X_ADCONFIG_START_CONVERSION | \
					 TPS6507X_ADCONFIG_INPUT_REAL_TSC)
#घोषणा	TPS6507X_ADCONFIG_POWER_DOWN_TS (TPS6507X_ADCONFIG_INPUT_REAL_TSC)

काष्ठा ts_event अणु
	u16	x;
	u16	y;
	u16	pressure;
पूर्ण;

काष्ठा tps6507x_ts अणु
	काष्ठा device		*dev;
	काष्ठा input_dev	*input;
	काष्ठा tps6507x_dev	*mfd;
	अक्षर			phys[32];
	काष्ठा ts_event		tc;
	u16			min_pressure;
	bool			penकरोwn;
पूर्ण;

अटल पूर्णांक tps6507x_पढ़ो_u8(काष्ठा tps6507x_ts *tsc, u8 reg, u8 *data)
अणु
	वापस tsc->mfd->पढ़ो_dev(tsc->mfd, reg, 1, data);
पूर्ण

अटल पूर्णांक tps6507x_ग_लिखो_u8(काष्ठा tps6507x_ts *tsc, u8 reg, u8 data)
अणु
	वापस tsc->mfd->ग_लिखो_dev(tsc->mfd, reg, 1, &data);
पूर्ण

अटल s32 tps6507x_adc_conversion(काष्ठा tps6507x_ts *tsc,
				   u8 tsc_mode, u16 *value)
अणु
	s32 ret;
	u8 adc_status;
	u8 result;

	/* Route input संकेत to A/D converter */

	ret = tps6507x_ग_लिखो_u8(tsc, TPS6507X_REG_TSCMODE, tsc_mode);
	अगर (ret) अणु
		dev_err(tsc->dev, "TSC mode read failed\n");
		जाओ err;
	पूर्ण

	/* Start A/D conversion */

	ret = tps6507x_ग_लिखो_u8(tsc, TPS6507X_REG_ADCONFIG,
				TPS6507X_ADCONFIG_CONVERT_TS);
	अगर (ret) अणु
		dev_err(tsc->dev, "ADC config write failed\n");
		वापस ret;
	पूर्ण

	करो अणु
		ret = tps6507x_पढ़ो_u8(tsc, TPS6507X_REG_ADCONFIG,
				       &adc_status);
		अगर (ret) अणु
			dev_err(tsc->dev, "ADC config read failed\n");
			जाओ err;
		पूर्ण
	पूर्ण जबतक (adc_status & TPS6507X_ADCONFIG_START_CONVERSION);

	ret = tps6507x_पढ़ो_u8(tsc, TPS6507X_REG_ADRESULT_2, &result);
	अगर (ret) अणु
		dev_err(tsc->dev, "ADC result 2 read failed\n");
		जाओ err;
	पूर्ण

	*value = (result & TPS6507X_REG_ADRESULT_2_MASK) << 8;

	ret = tps6507x_पढ़ो_u8(tsc, TPS6507X_REG_ADRESULT_1, &result);
	अगर (ret) अणु
		dev_err(tsc->dev, "ADC result 1 read failed\n");
		जाओ err;
	पूर्ण

	*value |= result;

	dev_dbg(tsc->dev, "TSC channel %d = 0x%X\n", tsc_mode, *value);

err:
	वापस ret;
पूर्ण

/* Need to call tps6507x_adc_standby() after using A/D converter क्रम the
 * touch screen पूर्णांकerrupt to work properly.
 */

अटल s32 tps6507x_adc_standby(काष्ठा tps6507x_ts *tsc)
अणु
	s32 ret;
	s32 loops = 0;
	u8 val;

	ret = tps6507x_ग_लिखो_u8(tsc,  TPS6507X_REG_ADCONFIG,
				TPS6507X_ADCONFIG_INPUT_TSC);
	अगर (ret)
		वापस ret;

	ret = tps6507x_ग_लिखो_u8(tsc, TPS6507X_REG_TSCMODE,
				TPS6507X_TSCMODE_STANDBY);
	अगर (ret)
		वापस ret;

	ret = tps6507x_पढ़ो_u8(tsc, TPS6507X_REG_INT, &val);
	अगर (ret)
		वापस ret;

	जबतक (val & TPS6507X_REG_TSC_INT) अणु
		mdelay(10);
		ret = tps6507x_पढ़ो_u8(tsc, TPS6507X_REG_INT, &val);
		अगर (ret)
			वापस ret;
		loops++;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tps6507x_ts_poll(काष्ठा input_dev *input_dev)
अणु
	काष्ठा tps6507x_ts *tsc = input_get_drvdata(input_dev);
	bool penकरोwn;
	s32 ret;

	ret = tps6507x_adc_conversion(tsc, TPS6507X_TSCMODE_PRESSURE,
				      &tsc->tc.pressure);
	अगर (ret)
		जाओ करोne;

	penकरोwn = tsc->tc.pressure > tsc->min_pressure;

	अगर (unlikely(!penकरोwn && tsc->penकरोwn)) अणु
		dev_dbg(tsc->dev, "UP\n");
		input_report_key(input_dev, BTN_TOUCH, 0);
		input_report_असल(input_dev, ABS_PRESSURE, 0);
		input_sync(input_dev);
		tsc->penकरोwn = false;
	पूर्ण

	अगर (penकरोwn) अणु

		अगर (!tsc->penकरोwn) अणु
			dev_dbg(tsc->dev, "DOWN\n");
			input_report_key(input_dev, BTN_TOUCH, 1);
		पूर्ण अन्यथा
			dev_dbg(tsc->dev, "still down\n");

		ret =  tps6507x_adc_conversion(tsc, TPS6507X_TSCMODE_X_POSITION,
					       &tsc->tc.x);
		अगर (ret)
			जाओ करोne;

		ret =  tps6507x_adc_conversion(tsc, TPS6507X_TSCMODE_Y_POSITION,
					       &tsc->tc.y);
		अगर (ret)
			जाओ करोne;

		input_report_असल(input_dev, ABS_X, tsc->tc.x);
		input_report_असल(input_dev, ABS_Y, tsc->tc.y);
		input_report_असल(input_dev, ABS_PRESSURE, tsc->tc.pressure);
		input_sync(input_dev);
		tsc->penकरोwn = true;
	पूर्ण

करोne:
	tps6507x_adc_standby(tsc);
पूर्ण

अटल पूर्णांक tps6507x_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps6507x_dev *tps6507x_dev = dev_get_drvdata(pdev->dev.parent);
	स्थिर काष्ठा tps6507x_board *tps_board;
	स्थिर काष्ठा touchscreen_init_data *init_data;
	काष्ठा tps6507x_ts *tsc;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	/*
	 * tps_board poपूर्णांकs to pmic related स्थिरants
	 * coming from the board-evm file.
	 */
	tps_board = dev_get_platdata(tps6507x_dev->dev);
	अगर (!tps_board) अणु
		dev_err(tps6507x_dev->dev,
			"Could not find tps6507x platform data\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * init_data poपूर्णांकs to array of regulator_init काष्ठाures
	 * coming from the board-evm file.
	 */
	init_data = tps_board->tps6507x_ts_init_data;

	tsc = devm_kzalloc(&pdev->dev, माप(काष्ठा tps6507x_ts), GFP_KERNEL);
	अगर (!tsc) अणु
		dev_err(tps6507x_dev->dev, "failed to allocate driver data\n");
		वापस -ENOMEM;
	पूर्ण

	tsc->mfd = tps6507x_dev;
	tsc->dev = tps6507x_dev->dev;
	tsc->min_pressure = init_data ?
			init_data->min_pressure : TPS_DEFAULT_MIN_PRESSURE;

	snम_लिखो(tsc->phys, माप(tsc->phys),
		 "%s/input0", dev_name(tsc->dev));

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(tsc->dev, "Failed to allocate polled input device.\n");
		वापस -ENOMEM;
	पूर्ण

	tsc->input = input_dev;
	input_set_drvdata(input_dev, tsc);

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, 0, MAX_10BIT, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MAX_10BIT, 0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, MAX_10BIT, 0, 0);

	input_dev->name = "TPS6507x Touchscreen";
	input_dev->phys = tsc->phys;
	input_dev->dev.parent = tsc->dev;
	input_dev->id.bustype = BUS_I2C;
	अगर (init_data) अणु
		input_dev->id.venकरोr = init_data->venकरोr;
		input_dev->id.product = init_data->product;
		input_dev->id.version = init_data->version;
	पूर्ण

	error = tps6507x_adc_standby(tsc);
	अगर (error)
		वापस error;

	error = input_setup_polling(input_dev, tps6507x_ts_poll);
	अगर (error)
		वापस error;

	input_set_poll_पूर्णांकerval(input_dev,
				init_data ? init_data->poll_period :
					    TSC_DEFAULT_POLL_PERIOD);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps6507x_ts_driver = अणु
	.driver = अणु
		.name = "tps6507x-ts",
	पूर्ण,
	.probe = tps6507x_ts_probe,
पूर्ण;
module_platक्रमm_driver(tps6507x_ts_driver);

MODULE_AUTHOR("Todd Fischer <todd.fischer@ridgerun.com>");
MODULE_DESCRIPTION("TPS6507x - TouchScreen driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps6507x-ts");
