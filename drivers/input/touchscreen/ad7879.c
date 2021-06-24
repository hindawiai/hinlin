<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD7879/AD7889 based touchscreen and GPIO driver
 *
 * Copyright (C) 2008-2010 Michael Hennerich, Analog Devices Inc.
 *
 * History:
 * Copyright (c) 2005 David Brownell
 * Copyright (c) 2006 Nokia Corporation
 * Various changes: Imre Deak <imre.deak@nokia.com>
 *
 * Using code from:
 *  - corgi_ts.c
 *	Copyright (C) 2004-2005 Riअक्षरd Purdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copyright (C) 2002 MontaVista Software
 *	Copyright (C) 2004 Texas Instruments
 *	Copyright (C) 2005 Dirk Behme
 *  - ad7877.c
 *	Copyright (C) 2006-2008 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>

#समावेश <linux/input/touchscreen.h>
#समावेश <linux/module.h>
#समावेश "ad7879.h"

#घोषणा AD7879_REG_ZEROS		0
#घोषणा AD7879_REG_CTRL1		1
#घोषणा AD7879_REG_CTRL2		2
#घोषणा AD7879_REG_CTRL3		3
#घोषणा AD7879_REG_AUX1HIGH		4
#घोषणा AD7879_REG_AUX1LOW		5
#घोषणा AD7879_REG_TEMP1HIGH		6
#घोषणा AD7879_REG_TEMP1LOW		7
#घोषणा AD7879_REG_XPLUS		8
#घोषणा AD7879_REG_YPLUS		9
#घोषणा AD7879_REG_Z1			10
#घोषणा AD7879_REG_Z2			11
#घोषणा AD7879_REG_AUXVBAT		12
#घोषणा AD7879_REG_TEMP			13
#घोषणा AD7879_REG_REVID		14

/* Control REG 1 */
#घोषणा AD7879_TMR(x)			((x & 0xFF) << 0)
#घोषणा AD7879_ACQ(x)			((x & 0x3) << 8)
#घोषणा AD7879_MODE_NOC			(0 << 10)	/* Do not convert */
#घोषणा AD7879_MODE_SCC			(1 << 10)	/* Single channel conversion */
#घोषणा AD7879_MODE_SEQ0		(2 << 10)	/* Sequence 0 in Slave Mode */
#घोषणा AD7879_MODE_SEQ1		(3 << 10)	/* Sequence 1 in Master Mode */
#घोषणा AD7879_MODE_INT			(1 << 15)	/* PENIRQ disabled INT enabled */

/* Control REG 2 */
#घोषणा AD7879_FCD(x)			((x & 0x3) << 0)
#घोषणा AD7879_RESET			(1 << 4)
#घोषणा AD7879_MFS(x)			((x & 0x3) << 5)
#घोषणा AD7879_AVG(x)			((x & 0x3) << 7)
#घोषणा	AD7879_SER			(1 << 9)	/* non-dअगरferential */
#घोषणा	AD7879_DFR			(0 << 9)	/* dअगरferential */
#घोषणा AD7879_GPIOPOL			(1 << 10)
#घोषणा AD7879_GPIOसूची			(1 << 11)
#घोषणा AD7879_GPIO_DATA		(1 << 12)
#घोषणा AD7879_GPIO_EN			(1 << 13)
#घोषणा AD7879_PM(x)			((x & 0x3) << 14)
#घोषणा AD7879_PM_SHUTDOWN		(0)
#घोषणा AD7879_PM_DYN			(1)
#घोषणा AD7879_PM_FULLON		(2)

/* Control REG 3 */
#घोषणा AD7879_TEMPMASK_BIT		(1<<15)
#घोषणा AD7879_AUXVBATMASK_BIT		(1<<14)
#घोषणा AD7879_INTMODE_BIT		(1<<13)
#घोषणा AD7879_GPIOALERTMASK_BIT	(1<<12)
#घोषणा AD7879_AUXLOW_BIT		(1<<11)
#घोषणा AD7879_AUXHIGH_BIT		(1<<10)
#घोषणा AD7879_TEMPLOW_BIT		(1<<9)
#घोषणा AD7879_TEMPHIGH_BIT		(1<<8)
#घोषणा AD7879_YPLUS_BIT		(1<<7)
#घोषणा AD7879_XPLUS_BIT		(1<<6)
#घोषणा AD7879_Z1_BIT			(1<<5)
#घोषणा AD7879_Z2_BIT			(1<<4)
#घोषणा AD7879_AUX_BIT			(1<<3)
#घोषणा AD7879_VBAT_BIT			(1<<2)
#घोषणा AD7879_TEMP_BIT			(1<<1)

क्रमागत अणु
	AD7879_SEQ_YPOS  = 0,
	AD7879_SEQ_XPOS  = 1,
	AD7879_SEQ_Z1    = 2,
	AD7879_SEQ_Z2    = 3,
	AD7879_NR_SENSE  = 4,
पूर्ण;

#घोषणा	MAX_12BIT			((1<<12)-1)
#घोषणा	TS_PEN_UP_TIMEOUT		msecs_to_jअगरfies(50)

काष्ठा ad7879 अणु
	काष्ठा regmap		*regmap;
	काष्ठा device		*dev;
	काष्ठा input_dev	*input;
	काष्ठा समयr_list	समयr;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip	gc;
	काष्ठा mutex		mutex;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		irq;
	bool			disabled;	/* P: input->mutex */
	bool			suspended;	/* P: input->mutex */
	bool			swap_xy;
	u16			conversion_data[AD7879_NR_SENSE];
	अक्षर			phys[32];
	u8			first_conversion_delay;
	u8			acquisition_समय;
	u8			averaging;
	u8			pen_करोwn_acc_पूर्णांकerval;
	u8			median;
	u16			x_plate_ohms;
	u16			cmd_crtl1;
	u16			cmd_crtl2;
	u16			cmd_crtl3;
	पूर्णांक			x;
	पूर्णांक			y;
	पूर्णांक			Rt;
पूर्ण;

अटल पूर्णांक ad7879_पढ़ो(काष्ठा ad7879 *ts, u8 reg)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = regmap_पढ़ो(ts->regmap, reg, &val);
	अगर (error) अणु
		dev_err(ts->dev, "failed to read register %#02x: %d\n",
			reg, error);
		वापस error;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक ad7879_ग_लिखो(काष्ठा ad7879 *ts, u8 reg, u16 val)
अणु
	पूर्णांक error;

	error = regmap_ग_लिखो(ts->regmap, reg, val);
	अगर (error) अणु
		dev_err(ts->dev,
			"failed to write %#04x to register %#02x: %d\n",
			val, reg, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7879_report(काष्ठा ad7879 *ts)
अणु
	काष्ठा input_dev *input_dev = ts->input;
	अचिन्हित Rt;
	u16 x, y, z1, z2;

	x = ts->conversion_data[AD7879_SEQ_XPOS] & MAX_12BIT;
	y = ts->conversion_data[AD7879_SEQ_YPOS] & MAX_12BIT;
	z1 = ts->conversion_data[AD7879_SEQ_Z1] & MAX_12BIT;
	z2 = ts->conversion_data[AD7879_SEQ_Z2] & MAX_12BIT;

	अगर (ts->swap_xy)
		swap(x, y);

	/*
	 * The samples processed here are alपढ़ोy preprocessed by the AD7879.
	 * The preprocessing function consists of a median and an averaging
	 * filter.  The combination of these two techniques provides a robust
	 * solution, discarding the spurious noise in the संकेत and keeping
	 * only the data of पूर्णांकerest.  The size of both filters is
	 * programmable. (dev.platक्रमm_data, see linux/platक्रमm_data/ad7879.h)
	 * Other user-programmable conversion controls include variable
	 * acquisition समय, and first conversion delay. Up to 16 averages can
	 * be taken per conversion.
	 */

	अगर (likely(x && z1)) अणु
		/* compute touch pressure resistance using equation #1 */
		Rt = (z2 - z1) * x * ts->x_plate_ohms;
		Rt /= z1;
		Rt = (Rt + 2047) >> 12;

		/*
		 * Sample found inconsistent, pressure is beyond
		 * the maximum. Don't report it to user space.
		 */
		अगर (Rt > input_असल_get_max(input_dev, ABS_PRESSURE))
			वापस -EINVAL;

		/*
		 * Note that we delay reporting events by one sample.
		 * This is करोne to aव्योम reporting last sample of the
		 * touch sequence, which may be incomplete अगर finger
		 * leaves the surface beक्रमe last पढ़ोing is taken.
		 */
		अगर (समयr_pending(&ts->समयr)) अणु
			/* Touch जारीs */
			input_report_key(input_dev, BTN_TOUCH, 1);
			input_report_असल(input_dev, ABS_X, ts->x);
			input_report_असल(input_dev, ABS_Y, ts->y);
			input_report_असल(input_dev, ABS_PRESSURE, ts->Rt);
			input_sync(input_dev);
		पूर्ण

		ts->x = x;
		ts->y = y;
		ts->Rt = Rt;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ad7879_ts_event_release(काष्ठा ad7879 *ts)
अणु
	काष्ठा input_dev *input_dev = ts->input;

	input_report_असल(input_dev, ABS_PRESSURE, 0);
	input_report_key(input_dev, BTN_TOUCH, 0);
	input_sync(input_dev);
पूर्ण

अटल व्योम ad7879_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ad7879 *ts = from_समयr(ts, t, समयr);

	ad7879_ts_event_release(ts);
पूर्ण

अटल irqवापस_t ad7879_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा ad7879 *ts = handle;
	पूर्णांक error;

	error = regmap_bulk_पढ़ो(ts->regmap, AD7879_REG_XPLUS,
				 ts->conversion_data, AD7879_NR_SENSE);
	अगर (error)
		dev_err_ratelimited(ts->dev, "failed to read %#02x: %d\n",
				    AD7879_REG_XPLUS, error);
	अन्यथा अगर (!ad7879_report(ts))
		mod_समयr(&ts->समयr, jअगरfies + TS_PEN_UP_TIMEOUT);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __ad7879_enable(काष्ठा ad7879 *ts)
अणु
	ad7879_ग_लिखो(ts, AD7879_REG_CTRL2, ts->cmd_crtl2);
	ad7879_ग_लिखो(ts, AD7879_REG_CTRL3, ts->cmd_crtl3);
	ad7879_ग_लिखो(ts, AD7879_REG_CTRL1, ts->cmd_crtl1);

	enable_irq(ts->irq);
पूर्ण

अटल व्योम __ad7879_disable(काष्ठा ad7879 *ts)
अणु
	u16 reg = (ts->cmd_crtl2 & ~AD7879_PM(-1)) |
		AD7879_PM(AD7879_PM_SHUTDOWN);
	disable_irq(ts->irq);

	अगर (del_समयr_sync(&ts->समयr))
		ad7879_ts_event_release(ts);

	ad7879_ग_लिखो(ts, AD7879_REG_CTRL2, reg);
पूर्ण


अटल पूर्णांक ad7879_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा ad7879 *ts = input_get_drvdata(input);

	/* रक्षित by input->mutex */
	अगर (!ts->disabled && !ts->suspended)
		__ad7879_enable(ts);

	वापस 0;
पूर्ण

अटल व्योम ad7879_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा ad7879 *ts = input_get_drvdata(input);

	/* रक्षित by input->mutex */
	अगर (!ts->disabled && !ts->suspended)
		__ad7879_disable(ts);
पूर्ण

अटल पूर्णांक __maybe_unused ad7879_suspend(काष्ठा device *dev)
अणु
	काष्ठा ad7879 *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->input->mutex);

	अगर (!ts->suspended && !ts->disabled && input_device_enabled(ts->input))
		__ad7879_disable(ts);

	ts->suspended = true;

	mutex_unlock(&ts->input->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ad7879_resume(काष्ठा device *dev)
अणु
	काष्ठा ad7879 *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->input->mutex);

	अगर (ts->suspended && !ts->disabled && input_device_enabled(ts->input))
		__ad7879_enable(ts);

	ts->suspended = false;

	mutex_unlock(&ts->input->mutex);

	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(ad7879_pm_ops, ad7879_suspend, ad7879_resume);
EXPORT_SYMBOL(ad7879_pm_ops);

अटल व्योम ad7879_toggle(काष्ठा ad7879 *ts, bool disable)
अणु
	mutex_lock(&ts->input->mutex);

	अगर (!ts->suspended && input_device_enabled(ts->input)) अणु

		अगर (disable) अणु
			अगर (ts->disabled)
				__ad7879_enable(ts);
		पूर्ण अन्यथा अणु
			अगर (!ts->disabled)
				__ad7879_disable(ts);
		पूर्ण
	पूर्ण

	ts->disabled = disable;

	mutex_unlock(&ts->input->mutex);
पूर्ण

अटल sमाप_प्रकार ad7879_disable_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad7879 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->disabled);
पूर्ण

अटल sमाप_प्रकार ad7879_disable_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ad7879 *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	ad7879_toggle(ts, val);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(disable, 0664, ad7879_disable_show, ad7879_disable_store);

अटल काष्ठा attribute *ad7879_attributes[] = अणु
	&dev_attr_disable.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7879_attr_group = अणु
	.attrs = ad7879_attributes,
पूर्ण;

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक ad7879_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित gpio)
अणु
	काष्ठा ad7879 *ts = gpiochip_get_data(chip);
	पूर्णांक err;

	mutex_lock(&ts->mutex);
	ts->cmd_crtl2 |= AD7879_GPIO_EN | AD7879_GPIOसूची | AD7879_GPIOPOL;
	err = ad7879_ग_लिखो(ts, AD7879_REG_CTRL2, ts->cmd_crtl2);
	mutex_unlock(&ts->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक ad7879_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित gpio, पूर्णांक level)
अणु
	काष्ठा ad7879 *ts = gpiochip_get_data(chip);
	पूर्णांक err;

	mutex_lock(&ts->mutex);
	ts->cmd_crtl2 &= ~AD7879_GPIOसूची;
	ts->cmd_crtl2 |= AD7879_GPIO_EN | AD7879_GPIOPOL;
	अगर (level)
		ts->cmd_crtl2 |= AD7879_GPIO_DATA;
	अन्यथा
		ts->cmd_crtl2 &= ~AD7879_GPIO_DATA;

	err = ad7879_ग_लिखो(ts, AD7879_REG_CTRL2, ts->cmd_crtl2);
	mutex_unlock(&ts->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक ad7879_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा ad7879 *ts = gpiochip_get_data(chip);
	u16 val;

	mutex_lock(&ts->mutex);
	val = ad7879_पढ़ो(ts, AD7879_REG_CTRL2);
	mutex_unlock(&ts->mutex);

	वापस !!(val & AD7879_GPIO_DATA);
पूर्ण

अटल व्योम ad7879_gpio_set_value(काष्ठा gpio_chip *chip,
				  अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा ad7879 *ts = gpiochip_get_data(chip);

	mutex_lock(&ts->mutex);
	अगर (value)
		ts->cmd_crtl2 |= AD7879_GPIO_DATA;
	अन्यथा
		ts->cmd_crtl2 &= ~AD7879_GPIO_DATA;

	ad7879_ग_लिखो(ts, AD7879_REG_CTRL2, ts->cmd_crtl2);
	mutex_unlock(&ts->mutex);
पूर्ण

अटल पूर्णांक ad7879_gpio_add(काष्ठा ad7879 *ts)
अणु
	पूर्णांक ret = 0;

	mutex_init(&ts->mutex);

	/* Do not create a chip unless flagged क्रम it */
	अगर (!device_property_पढ़ो_bool(ts->dev, "gpio-controller"))
		वापस 0;

	ts->gc.direction_input = ad7879_gpio_direction_input;
	ts->gc.direction_output = ad7879_gpio_direction_output;
	ts->gc.get = ad7879_gpio_get_value;
	ts->gc.set = ad7879_gpio_set_value;
	ts->gc.can_sleep = 1;
	ts->gc.base = -1;
	ts->gc.ngpio = 1;
	ts->gc.label = "AD7879-GPIO";
	ts->gc.owner = THIS_MODULE;
	ts->gc.parent = ts->dev;

	ret = devm_gpiochip_add_data(ts->dev, &ts->gc, ts);
	अगर (ret)
		dev_err(ts->dev, "failed to register gpio %d\n",
			ts->gc.base);

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक ad7879_gpio_add(काष्ठा ad7879 *ts)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ad7879_parse_dt(काष्ठा device *dev, काष्ठा ad7879 *ts)
अणु
	पूर्णांक err;
	u32 पंचांगp;

	err = device_property_पढ़ो_u32(dev, "adi,resistance-plate-x", &पंचांगp);
	अगर (err) अणु
		dev_err(dev, "failed to get resistance-plate-x property\n");
		वापस err;
	पूर्ण
	ts->x_plate_ohms = (u16)पंचांगp;

	device_property_पढ़ो_u8(dev, "adi,first-conversion-delay",
				&ts->first_conversion_delay);
	device_property_पढ़ो_u8(dev, "adi,acquisition-time",
				&ts->acquisition_समय);
	device_property_पढ़ो_u8(dev, "adi,median-filter-size", &ts->median);
	device_property_पढ़ो_u8(dev, "adi,averaging", &ts->averaging);
	device_property_पढ़ो_u8(dev, "adi,conversion-interval",
				&ts->pen_करोwn_acc_पूर्णांकerval);

	ts->swap_xy = device_property_पढ़ो_bool(dev, "touchscreen-swapped-x-y");

	वापस 0;
पूर्ण

पूर्णांक ad7879_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		 पूर्णांक irq, u16 bustype, u8 devid)
अणु
	काष्ठा ad7879 *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;
	u16 revid;

	अगर (irq <= 0) अणु
		dev_err(dev, "No IRQ specified\n");
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	err = ad7879_parse_dt(dev, ts);
	अगर (err)
		वापस err;

	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->dev = dev;
	ts->input = input_dev;
	ts->irq = irq;
	ts->regmap = regmap;

	समयr_setup(&ts->समयr, ad7879_समयr, 0);
	snम_लिखो(ts->phys, माप(ts->phys), "%s/input0", dev_name(dev));

	input_dev->name = "AD7879 Touchscreen";
	input_dev->phys = ts->phys;
	input_dev->dev.parent = dev;
	input_dev->id.bustype = bustype;

	input_dev->खोलो = ad7879_खोलो;
	input_dev->बंद = ad7879_बंद;

	input_set_drvdata(input_dev, ts);

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);

	input_set_असल_params(input_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MAX_12BIT, 0, 0);
	input_set_capability(input_dev, EV_ABS, ABS_PRESSURE);
	touchscreen_parse_properties(input_dev, false, शून्य);
	अगर (!input_असल_get_max(input_dev, ABS_PRESSURE)) अणु
		dev_err(dev, "Touchscreen pressure is not specified\n");
		वापस -EINVAL;
	पूर्ण

	err = ad7879_ग_लिखो(ts, AD7879_REG_CTRL2, AD7879_RESET);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to write %s\n", input_dev->name);
		वापस err;
	पूर्ण

	revid = ad7879_पढ़ो(ts, AD7879_REG_REVID);
	input_dev->id.product = (revid & 0xff);
	input_dev->id.version = revid >> 8;
	अगर (input_dev->id.product != devid) अणु
		dev_err(dev, "Failed to probe %s (%x vs %x)\n",
			input_dev->name, devid, revid);
		वापस -ENODEV;
	पूर्ण

	ts->cmd_crtl3 = AD7879_YPLUS_BIT |
			AD7879_XPLUS_BIT |
			AD7879_Z2_BIT |
			AD7879_Z1_BIT |
			AD7879_TEMPMASK_BIT |
			AD7879_AUXVBATMASK_BIT |
			AD7879_GPIOALERTMASK_BIT;

	ts->cmd_crtl2 = AD7879_PM(AD7879_PM_DYN) | AD7879_DFR |
			AD7879_AVG(ts->averaging) |
			AD7879_MFS(ts->median) |
			AD7879_FCD(ts->first_conversion_delay);

	ts->cmd_crtl1 = AD7879_MODE_INT | AD7879_MODE_SEQ1 |
			AD7879_ACQ(ts->acquisition_समय) |
			AD7879_TMR(ts->pen_करोwn_acc_पूर्णांकerval);

	err = devm_request_thपढ़ोed_irq(dev, ts->irq, शून्य, ad7879_irq,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					dev_name(dev), ts);
	अगर (err) अणु
		dev_err(dev, "Failed to request IRQ: %d\n", err);
		वापस err;
	पूर्ण

	__ad7879_disable(ts);

	err = devm_device_add_group(dev, &ad7879_attr_group);
	अगर (err)
		वापस err;

	err = ad7879_gpio_add(ts);
	अगर (err)
		वापस err;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		वापस err;

	dev_set_drvdata(dev, ts);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ad7879_probe);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("AD7879(-1) touchscreen Driver");
MODULE_LICENSE("GPL");
