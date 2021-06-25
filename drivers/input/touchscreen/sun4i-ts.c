<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Allwinner sunxi resistive touchscreen controller driver
 *
 * Copyright (C) 2013 - 2014 Hans de Goede <hdegoede@redhat.com>
 *
 * The hwmon parts are based on work by Corentin LABBE which is:
 * Copyright (C) 2013 Corentin LABBE <clabbe.montjoie@gmail.com>
 */

/*
 * The sun4i-ts controller is capable of detecting a second touch, but when a
 * second touch is present then the accuracy becomes so bad the reported touch
 * location is not useable.
 *
 * The original android driver contains some complicated heuristics using the
 * aprox. distance between the 2 touches to see अगर the user is making a pinch
 * खोलो / बंद movement, and then reports emulated multi-touch events around
 * the last touch coordinate (as the dual-touch coordinates are worthless).
 *
 * These kinds of heuristics are just asking क्रम trouble (and करोn't beदीर्घ
 * in the kernel). So this driver offers straight क्रमward, reliable single
 * touch functionality only.
 *
 * s.a. A20 User Manual "1.15 TP" (Documentation/arm/sunxi.rst)
 * (looks like the description in the A20 User Manual v1.3 is better
 * than the one in the A10 User Manual v.1.5)
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/thermal.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा TP_CTRL0		0x00
#घोषणा TP_CTRL1		0x04
#घोषणा TP_CTRL2		0x08
#घोषणा TP_CTRL3		0x0c
#घोषणा TP_INT_FIFOC		0x10
#घोषणा TP_INT_FIFOS		0x14
#घोषणा TP_TPR			0x18
#घोषणा TP_CDAT			0x1c
#घोषणा TEMP_DATA		0x20
#घोषणा TP_DATA			0x24

/* TP_CTRL0 bits */
#घोषणा ADC_FIRST_DLY(x)	((x) << 24) /* 8 bits */
#घोषणा ADC_FIRST_DLY_MODE(x)	((x) << 23)
#घोषणा ADC_CLK_SEL(x)		((x) << 22)
#घोषणा ADC_CLK_DIV(x)		((x) << 20) /* 3 bits */
#घोषणा FS_DIV(x)		((x) << 16) /* 4 bits */
#घोषणा T_ACQ(x)		((x) << 0) /* 16 bits */

/* TP_CTRL1 bits */
#घोषणा STYLUS_UP_DEBOUN(x)	((x) << 12) /* 8 bits */
#घोषणा STYLUS_UP_DEBOUN_EN(x)	((x) << 9)
#घोषणा TOUCH_PAN_CALI_EN(x)	((x) << 6)
#घोषणा TP_DUAL_EN(x)		((x) << 5)
#घोषणा TP_MODE_EN(x)		((x) << 4)
#घोषणा TP_ADC_SELECT(x)	((x) << 3)
#घोषणा ADC_CHAN_SELECT(x)	((x) << 0)  /* 3 bits */

/* on sun6i, bits 3~6 are left shअगरted by 1 to 4~7 */
#घोषणा SUN6I_TP_MODE_EN(x)	((x) << 5)

/* TP_CTRL2 bits */
#घोषणा TP_SENSITIVE_ADJUST(x)	((x) << 28) /* 4 bits */
#घोषणा TP_MODE_SELECT(x)	((x) << 26) /* 2 bits */
#घोषणा PRE_MEA_EN(x)		((x) << 24)
#घोषणा PRE_MEA_THRE_CNT(x)	((x) << 0) /* 24 bits */

/* TP_CTRL3 bits */
#घोषणा FILTER_EN(x)		((x) << 2)
#घोषणा FILTER_TYPE(x)		((x) << 0)  /* 2 bits */

/* TP_INT_FIFOC irq and fअगरo mask / control bits */
#घोषणा TEMP_IRQ_EN(x)		((x) << 18)
#घोषणा OVERRUN_IRQ_EN(x)	((x) << 17)
#घोषणा DATA_IRQ_EN(x)		((x) << 16)
#घोषणा TP_DATA_XY_CHANGE(x)	((x) << 13)
#घोषणा FIFO_TRIG(x)		((x) << 8)  /* 5 bits */
#घोषणा DATA_DRQ_EN(x)		((x) << 7)
#घोषणा FIFO_FLUSH(x)		((x) << 4)
#घोषणा TP_UP_IRQ_EN(x)		((x) << 1)
#घोषणा TP_DOWN_IRQ_EN(x)	((x) << 0)

/* TP_INT_FIFOS irq and fअगरo status bits */
#घोषणा TEMP_DATA_PENDING	BIT(18)
#घोषणा FIFO_OVERRUN_PENDING	BIT(17)
#घोषणा FIFO_DATA_PENDING	BIT(16)
#घोषणा TP_IDLE_FLG		BIT(2)
#घोषणा TP_UP_PENDING		BIT(1)
#घोषणा TP_DOWN_PENDING		BIT(0)

/* TP_TPR bits */
#घोषणा TEMP_ENABLE(x)		((x) << 16)
#घोषणा TEMP_PERIOD(x)		((x) << 0)  /* t = x * 256 * 16 / clkin */

काष्ठा sun4i_ts_data अणु
	काष्ठा device *dev;
	काष्ठा input_dev *input;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक irq;
	bool ignore_fअगरo_data;
	पूर्णांक temp_data;
	पूर्णांक temp_offset;
	पूर्णांक temp_step;
पूर्ण;

अटल व्योम sun4i_ts_irq_handle_input(काष्ठा sun4i_ts_data *ts, u32 reg_val)
अणु
	u32 x, y;

	अगर (reg_val & FIFO_DATA_PENDING) अणु
		x = पढ़ोl(ts->base + TP_DATA);
		y = पढ़ोl(ts->base + TP_DATA);
		/* The 1st location reported after an up event is unreliable */
		अगर (!ts->ignore_fअगरo_data) अणु
			input_report_असल(ts->input, ABS_X, x);
			input_report_असल(ts->input, ABS_Y, y);
			/*
			 * The hardware has a separate करोwn status bit, but
			 * that माला_लो set beक्रमe we get the first location,
			 * resulting in reporting a click on the old location.
			 */
			input_report_key(ts->input, BTN_TOUCH, 1);
			input_sync(ts->input);
		पूर्ण अन्यथा अणु
			ts->ignore_fअगरo_data = false;
		पूर्ण
	पूर्ण

	अगर (reg_val & TP_UP_PENDING) अणु
		ts->ignore_fअगरo_data = true;
		input_report_key(ts->input, BTN_TOUCH, 0);
		input_sync(ts->input);
	पूर्ण
पूर्ण

अटल irqवापस_t sun4i_ts_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_ts_data *ts = dev_id;
	u32 reg_val;

	reg_val  = पढ़ोl(ts->base + TP_INT_FIFOS);

	अगर (reg_val & TEMP_DATA_PENDING)
		ts->temp_data = पढ़ोl(ts->base + TEMP_DATA);

	अगर (ts->input)
		sun4i_ts_irq_handle_input(ts, reg_val);

	ग_लिखोl(reg_val, ts->base + TP_INT_FIFOS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा sun4i_ts_data *ts = input_get_drvdata(dev);

	/* Flush, set trig level to 1, enable temp, data and up irqs */
	ग_लिखोl(TEMP_IRQ_EN(1) | DATA_IRQ_EN(1) | FIFO_TRIG(1) | FIFO_FLUSH(1) |
		TP_UP_IRQ_EN(1), ts->base + TP_INT_FIFOC);

	वापस 0;
पूर्ण

अटल व्योम sun4i_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा sun4i_ts_data *ts = input_get_drvdata(dev);

	/* Deactivate all input IRQs */
	ग_लिखोl(TEMP_IRQ_EN(1), ts->base + TP_INT_FIFOC);
पूर्ण

अटल पूर्णांक sun4i_get_temp(स्थिर काष्ठा sun4i_ts_data *ts, पूर्णांक *temp)
अणु
	/* No temp_data until the first irq */
	अगर (ts->temp_data == -1)
		वापस -EAGAIN;

	*temp = ts->temp_data * ts->temp_step - ts->temp_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_get_tz_temp(व्योम *data, पूर्णांक *temp)
अणु
	वापस sun4i_get_temp(data, temp);
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops sun4i_ts_tz_ops = अणु
	.get_temp = sun4i_get_tz_temp,
पूर्ण;

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sun4i_ts_data *ts = dev_get_drvdata(dev);
	पूर्णांक temp;
	पूर्णांक error;

	error = sun4i_get_temp(ts, &temp);
	अगर (error)
		वापस error;

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार show_temp_label(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "SoC temperature\n");
पूर्ण

अटल DEVICE_ATTR(temp1_input, S_IRUGO, show_temp, शून्य);
अटल DEVICE_ATTR(temp1_label, S_IRUGO, show_temp_label, शून्य);

अटल काष्ठा attribute *sun4i_ts_attrs[] = अणु
	&dev_attr_temp1_input.attr,
	&dev_attr_temp1_label.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(sun4i_ts);

अटल पूर्णांक sun4i_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_ts_data *ts;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device *hwmon;
	काष्ठा thermal_zone_device *thermal;
	पूर्णांक error;
	u32 reg;
	bool ts_attached;
	u32 tp_sensitive_adjust = 15;
	u32 filter_type = 1;

	ts = devm_kzalloc(dev, माप(काष्ठा sun4i_ts_data), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->dev = dev;
	ts->ignore_fअगरo_data = true;
	ts->temp_data = -1;
	अगर (of_device_is_compatible(np, "allwinner,sun6i-a31-ts")) अणु
		/* Allwinner SDK has temperature (C) = (value / 6) - 271 */
		ts->temp_offset = 271000;
		ts->temp_step = 167;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "allwinner,sun4i-a10-ts")) अणु
		/*
		 * The A10 temperature sensor has quite a wide spपढ़ो, these
		 * parameters are based on the averaging of the calibration
		 * results of 4 completely dअगरferent boards, with a spपढ़ो of
		 * temp_step from 0.096 - 0.170 and temp_offset from 176 - 331.
		 */
		ts->temp_offset = 257000;
		ts->temp_step = 133;
	पूर्ण अन्यथा अणु
		/*
		 * The user manuals करो not contain the क्रमmula क्रम calculating
		 * the temperature. The क्रमmula used here is from the AXP209,
		 * which is deचिन्हित by X-Powers, an affiliate of Allwinner:
		 *
		 *     temperature (C) = (value * 0.1) - 144.7
		 *
		 * Allwinner करोes not have any करोcumentation whatsoever क्रम
		 * this hardware. Moreover, it is claimed that the sensor
		 * is inaccurate and cannot work properly.
		 */
		ts->temp_offset = 144700;
		ts->temp_step = 100;
	पूर्ण

	ts_attached = of_property_पढ़ो_bool(np, "allwinner,ts-attached");
	अगर (ts_attached) अणु
		ts->input = devm_input_allocate_device(dev);
		अगर (!ts->input)
			वापस -ENOMEM;

		ts->input->name = pdev->name;
		ts->input->phys = "sun4i_ts/input0";
		ts->input->खोलो = sun4i_ts_खोलो;
		ts->input->बंद = sun4i_ts_बंद;
		ts->input->id.bustype = BUS_HOST;
		ts->input->id.venकरोr = 0x0001;
		ts->input->id.product = 0x0001;
		ts->input->id.version = 0x0100;
		ts->input->evbit[0] =  BIT(EV_SYN) | BIT(EV_KEY) | BIT(EV_ABS);
		__set_bit(BTN_TOUCH, ts->input->keybit);
		input_set_असल_params(ts->input, ABS_X, 0, 4095, 0, 0);
		input_set_असल_params(ts->input, ABS_Y, 0, 4095, 0, 0);
		input_set_drvdata(ts->input, ts);
	पूर्ण

	ts->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ts->base))
		वापस PTR_ERR(ts->base);

	ts->irq = platक्रमm_get_irq(pdev, 0);
	error = devm_request_irq(dev, ts->irq, sun4i_ts_irq, 0, "sun4i-ts", ts);
	अगर (error)
		वापस error;

	/*
	 * Select HOSC clk, clkin = clk / 6, adc samplefreq = clkin / 8192,
	 * t_acq = clkin / (16 * 64)
	 */
	ग_लिखोl(ADC_CLK_SEL(0) | ADC_CLK_DIV(2) | FS_DIV(7) | T_ACQ(63),
	       ts->base + TP_CTRL0);

	/*
	 * tp_sensitive_adjust is an optional property
	 * tp_mode = 0 : only x and y coordinates, as we करोn't use dual touch
	 */
	of_property_पढ़ो_u32(np, "allwinner,tp-sensitive-adjust",
			     &tp_sensitive_adjust);
	ग_लिखोl(TP_SENSITIVE_ADJUST(tp_sensitive_adjust) | TP_MODE_SELECT(0),
	       ts->base + TP_CTRL2);

	/*
	 * Enable median and averaging filter, optional property क्रम
	 * filter type.
	 */
	of_property_पढ़ो_u32(np, "allwinner,filter-type", &filter_type);
	ग_लिखोl(FILTER_EN(1) | FILTER_TYPE(filter_type), ts->base + TP_CTRL3);

	/* Enable temperature measurement, period 1953 (2 seconds) */
	ग_लिखोl(TEMP_ENABLE(1) | TEMP_PERIOD(1953), ts->base + TP_TPR);

	/*
	 * Set stylus up debounce to aprox 10 ms, enable debounce, and
	 * finally enable tp mode.
	 */
	reg = STYLUS_UP_DEBOUN(5) | STYLUS_UP_DEBOUN_EN(1);
	अगर (of_device_is_compatible(np, "allwinner,sun6i-a31-ts"))
		reg |= SUN6I_TP_MODE_EN(1);
	अन्यथा
		reg |= TP_MODE_EN(1);
	ग_लिखोl(reg, ts->base + TP_CTRL1);

	/*
	 * The thermal core करोes not रेजिस्टर hwmon devices क्रम DT-based
	 * thermal zone sensors, such as this one.
	 */
	hwmon = devm_hwmon_device_रेजिस्टर_with_groups(ts->dev, "sun4i_ts",
						       ts, sun4i_ts_groups);
	अगर (IS_ERR(hwmon))
		वापस PTR_ERR(hwmon);

	thermal = devm_thermal_zone_of_sensor_रेजिस्टर(ts->dev, 0, ts,
						       &sun4i_ts_tz_ops);
	अगर (IS_ERR(thermal))
		वापस PTR_ERR(thermal);

	ग_लिखोl(TEMP_IRQ_EN(1), ts->base + TP_INT_FIFOC);

	अगर (ts_attached) अणु
		error = input_रेजिस्टर_device(ts->input);
		अगर (error) अणु
			ग_लिखोl(0, ts->base + TP_INT_FIFOC);
			वापस error;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, ts);
	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_ts_data *ts = platक्रमm_get_drvdata(pdev);

	/* Explicit unरेजिस्टर to aव्योम खोलो/बंद changing the imask later */
	अगर (ts->input)
		input_unरेजिस्टर_device(ts->input);

	/* Deactivate all IRQs */
	ग_लिखोl(0, ts->base + TP_INT_FIFOC);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_ts_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-ts", पूर्ण,
	अणु .compatible = "allwinner,sun5i-a13-ts", पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-ts", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_ts_of_match);

अटल काष्ठा platक्रमm_driver sun4i_ts_driver = अणु
	.driver = अणु
		.name	= "sun4i-ts",
		.of_match_table = of_match_ptr(sun4i_ts_of_match),
	पूर्ण,
	.probe	= sun4i_ts_probe,
	.हटाओ	= sun4i_ts_हटाओ,
पूर्ण;

module_platक्रमm_driver(sun4i_ts_driver);

MODULE_DESCRIPTION("Allwinner sun4i resistive touchscreen controller driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
