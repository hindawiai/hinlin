<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TSC2004/TSC2005 touchscreen driver core
 *
 * Copyright (C) 2006-2010 Nokia Corporation
 * Copyright (C) 2015 QWERTY Embedded Design
 * Copyright (C) 2015 EMAC Inc.
 *
 * Author: Lauri Leukkunen <lauri.leukkunen@nokia.com>
 * based on TSC2301 driver by Klaus K. Pedersen <klaus.k.pedersen@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpio/consumer.h>
#समावेश "tsc200x-core.h"

/*
 * The touchscreen पूर्णांकerface operates as follows:
 *
 * 1) Pen is pressed against the touchscreen.
 * 2) TSC200X perक्रमms AD conversion.
 * 3) After the conversion is करोne TSC200X drives DAV line करोwn.
 * 4) GPIO IRQ is received and tsc200x_irq_thपढ़ो() is scheduled.
 * 5) tsc200x_irq_thपढ़ो() queues up a transfer to fetch the x, y, z1, z2
 *    values.
 * 6) tsc200x_irq_thपढ़ो() reports coordinates to input layer and sets up
 *    tsc200x_penup_समयr() to be called after TSC200X_PENUP_TIME_MS (40ms).
 * 7) When the penup समयr expires, there have not been touch or DAV पूर्णांकerrupts
 *    during the last 40ms which means the pen has been lअगरted.
 *
 * ESD recovery via a hardware reset is करोne अगर the TSC200X करोesn't respond
 * after a configurable period (in ms) of activity. If esd_समयout is 0, the
 * watchकरोg is disabled.
 */

अटल स्थिर काष्ठा regmap_range tsc200x_writable_ranges[] = अणु
	regmap_reg_range(TSC200X_REG_AUX_HIGH, TSC200X_REG_CFR2),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tsc200x_writable_table = अणु
	.yes_ranges = tsc200x_writable_ranges,
	.n_yes_ranges = ARRAY_SIZE(tsc200x_writable_ranges),
पूर्ण;

स्थिर काष्ठा regmap_config tsc200x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.reg_stride = 0x08,
	.max_रेजिस्टर = 0x78,
	.पढ़ो_flag_mask = TSC200X_REG_READ,
	.ग_लिखो_flag_mask = TSC200X_REG_PND0,
	.wr_table = &tsc200x_writable_table,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;
EXPORT_SYMBOL_GPL(tsc200x_regmap_config);

काष्ठा tsc200x_data अणु
	u16 x;
	u16 y;
	u16 z1;
	u16 z2;
पूर्ण __packed;
#घोषणा TSC200X_DATA_REGS 4

काष्ठा tsc200x अणु
	काष्ठा device           *dev;
	काष्ठा regmap		*regmap;
	__u16                   bustype;

	काष्ठा input_dev	*idev;
	अक्षर			phys[32];

	काष्ठा mutex		mutex;

	/* raw copy of previous x,y,z */
	पूर्णांक			in_x;
	पूर्णांक			in_y;
	पूर्णांक                     in_z1;
	पूर्णांक			in_z2;

	spinlock_t		lock;
	काष्ठा समयr_list	penup_समयr;

	अचिन्हित पूर्णांक		esd_समयout;
	काष्ठा delayed_work	esd_work;
	अचिन्हित दीर्घ		last_valid_पूर्णांकerrupt;

	अचिन्हित पूर्णांक		x_plate_ohm;

	bool			खोलोed;
	bool			suspended;

	bool			pen_करोwn;

	काष्ठा regulator	*vio;

	काष्ठा gpio_desc	*reset_gpio;
	पूर्णांक			(*tsc200x_cmd)(काष्ठा device *dev, u8 cmd);
	पूर्णांक			irq;
पूर्ण;

अटल व्योम tsc200x_update_pen_state(काष्ठा tsc200x *ts,
				     पूर्णांक x, पूर्णांक y, पूर्णांक pressure)
अणु
	अगर (pressure) अणु
		input_report_असल(ts->idev, ABS_X, x);
		input_report_असल(ts->idev, ABS_Y, y);
		input_report_असल(ts->idev, ABS_PRESSURE, pressure);
		अगर (!ts->pen_करोwn) अणु
			input_report_key(ts->idev, BTN_TOUCH, !!pressure);
			ts->pen_करोwn = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		input_report_असल(ts->idev, ABS_PRESSURE, 0);
		अगर (ts->pen_करोwn) अणु
			input_report_key(ts->idev, BTN_TOUCH, 0);
			ts->pen_करोwn = false;
		पूर्ण
	पूर्ण
	input_sync(ts->idev);
	dev_dbg(ts->dev, "point(%4d,%4d), pressure (%4d)\n", x, y,
		pressure);
पूर्ण

अटल irqवापस_t tsc200x_irq_thपढ़ो(पूर्णांक irq, व्योम *_ts)
अणु
	काष्ठा tsc200x *ts = _ts;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pressure;
	काष्ठा tsc200x_data tsdata;
	पूर्णांक error;

	/* पढ़ो the coordinates */
	error = regmap_bulk_पढ़ो(ts->regmap, TSC200X_REG_X, &tsdata,
				 TSC200X_DATA_REGS);
	अगर (unlikely(error))
		जाओ out;

	/* validate position */
	अगर (unlikely(tsdata.x > MAX_12BIT || tsdata.y > MAX_12BIT))
		जाओ out;

	/* Skip पढ़ोing अगर the pressure components are out of range */
	अगर (unlikely(tsdata.z1 == 0 || tsdata.z2 > MAX_12BIT))
		जाओ out;
	अगर (unlikely(tsdata.z1 >= tsdata.z2))
		जाओ out;

       /*
	* Skip poपूर्णांक अगर this is a pen करोwn with the exact same values as
	* the value beक्रमe pen-up - that implies SPI fed us stale data
	*/
	अगर (!ts->pen_करोwn &&
	    ts->in_x == tsdata.x && ts->in_y == tsdata.y &&
	    ts->in_z1 == tsdata.z1 && ts->in_z2 == tsdata.z2) अणु
		जाओ out;
	पूर्ण

	/*
	 * At this poपूर्णांक we are happy we have a valid and useful पढ़ोing.
	 * Remember it क्रम later comparisons. We may now begin करोwnsampling.
	 */
	ts->in_x = tsdata.x;
	ts->in_y = tsdata.y;
	ts->in_z1 = tsdata.z1;
	ts->in_z2 = tsdata.z2;

	/* Compute touch pressure resistance using equation #1 */
	pressure = tsdata.x * (tsdata.z2 - tsdata.z1) / tsdata.z1;
	pressure = pressure * ts->x_plate_ohm / 4096;
	अगर (unlikely(pressure > MAX_12BIT))
		जाओ out;

	spin_lock_irqsave(&ts->lock, flags);

	tsc200x_update_pen_state(ts, tsdata.x, tsdata.y, pressure);
	mod_समयr(&ts->penup_समयr,
		  jअगरfies + msecs_to_jअगरfies(TSC200X_PENUP_TIME_MS));

	spin_unlock_irqrestore(&ts->lock, flags);

	ts->last_valid_पूर्णांकerrupt = jअगरfies;
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tsc200x_penup_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tsc200x *ts = from_समयr(ts, t, penup_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ts->lock, flags);
	tsc200x_update_pen_state(ts, 0, 0, 0);
	spin_unlock_irqrestore(&ts->lock, flags);
पूर्ण

अटल व्योम tsc200x_start_scan(काष्ठा tsc200x *ts)
अणु
	regmap_ग_लिखो(ts->regmap, TSC200X_REG_CFR0, TSC200X_CFR0_INITVALUE);
	regmap_ग_लिखो(ts->regmap, TSC200X_REG_CFR1, TSC200X_CFR1_INITVALUE);
	regmap_ग_लिखो(ts->regmap, TSC200X_REG_CFR2, TSC200X_CFR2_INITVALUE);
	ts->tsc200x_cmd(ts->dev, TSC200X_CMD_NORMAL);
पूर्ण

अटल व्योम tsc200x_stop_scan(काष्ठा tsc200x *ts)
अणु
	ts->tsc200x_cmd(ts->dev, TSC200X_CMD_STOP);
पूर्ण

अटल व्योम tsc200x_reset(काष्ठा tsc200x *ts)
अणु
	अगर (ts->reset_gpio) अणु
		gpiod_set_value_cansleep(ts->reset_gpio, 1);
		usleep_range(100, 500); /* only 10us required */
		gpiod_set_value_cansleep(ts->reset_gpio, 0);
	पूर्ण
पूर्ण

/* must be called with ts->mutex held */
अटल व्योम __tsc200x_disable(काष्ठा tsc200x *ts)
अणु
	tsc200x_stop_scan(ts);

	disable_irq(ts->irq);
	del_समयr_sync(&ts->penup_समयr);

	cancel_delayed_work_sync(&ts->esd_work);

	enable_irq(ts->irq);
पूर्ण

/* must be called with ts->mutex held */
अटल व्योम __tsc200x_enable(काष्ठा tsc200x *ts)
अणु
	tsc200x_start_scan(ts);

	अगर (ts->esd_समयout && ts->reset_gpio) अणु
		ts->last_valid_पूर्णांकerrupt = jअगरfies;
		schedule_delayed_work(&ts->esd_work,
				round_jअगरfies_relative(
					msecs_to_jअगरfies(ts->esd_समयout)));
	पूर्ण
पूर्ण

अटल sमाप_प्रकार tsc200x_selftest_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा tsc200x *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक temp_high;
	अचिन्हित पूर्णांक temp_high_orig;
	अचिन्हित पूर्णांक temp_high_test;
	bool success = true;
	पूर्णांक error;

	mutex_lock(&ts->mutex);

	/*
	 * Test TSC200X communications via temp high रेजिस्टर.
	 */
	__tsc200x_disable(ts);

	error = regmap_पढ़ो(ts->regmap, TSC200X_REG_TEMP_HIGH, &temp_high_orig);
	अगर (error) अणु
		dev_warn(dev, "selftest failed: read error %d\n", error);
		success = false;
		जाओ out;
	पूर्ण

	temp_high_test = (temp_high_orig - 1) & MAX_12BIT;

	error = regmap_ग_लिखो(ts->regmap, TSC200X_REG_TEMP_HIGH, temp_high_test);
	अगर (error) अणु
		dev_warn(dev, "selftest failed: write error %d\n", error);
		success = false;
		जाओ out;
	पूर्ण

	error = regmap_पढ़ो(ts->regmap, TSC200X_REG_TEMP_HIGH, &temp_high);
	अगर (error) अणु
		dev_warn(dev, "selftest failed: read error %d after write\n",
			 error);
		success = false;
		जाओ out;
	पूर्ण

	अगर (temp_high != temp_high_test) अणु
		dev_warn(dev, "selftest failed: %d != %d\n",
			 temp_high, temp_high_test);
		success = false;
	पूर्ण

	/* hardware reset */
	tsc200x_reset(ts);

	अगर (!success)
		जाओ out;

	/* test that the reset really happened */
	error = regmap_पढ़ो(ts->regmap, TSC200X_REG_TEMP_HIGH, &temp_high);
	अगर (error) अणु
		dev_warn(dev, "selftest failed: read error %d after reset\n",
			 error);
		success = false;
		जाओ out;
	पूर्ण

	अगर (temp_high != temp_high_orig) अणु
		dev_warn(dev, "selftest failed after reset: %d != %d\n",
			 temp_high, temp_high_orig);
		success = false;
	पूर्ण

out:
	__tsc200x_enable(ts);
	mutex_unlock(&ts->mutex);

	वापस प्र_लिखो(buf, "%d\n", success);
पूर्ण

अटल DEVICE_ATTR(selftest, S_IRUGO, tsc200x_selftest_show, शून्य);

अटल काष्ठा attribute *tsc200x_attrs[] = अणु
	&dev_attr_selftest.attr,
	शून्य
पूर्ण;

अटल umode_t tsc200x_attr_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा tsc200x *ts = dev_get_drvdata(dev);
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_selftest.attr) अणु
		अगर (!ts->reset_gpio)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group tsc200x_attr_group = अणु
	.is_visible	= tsc200x_attr_is_visible,
	.attrs		= tsc200x_attrs,
पूर्ण;

अटल व्योम tsc200x_esd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tsc200x *ts = container_of(work, काष्ठा tsc200x, esd_work.work);
	पूर्णांक error;
	अचिन्हित पूर्णांक r;

	अगर (!mutex_trylock(&ts->mutex)) अणु
		/*
		 * If the mutex is taken, it means that disable or enable is in
		 * progress. In that हाल just reschedule the work. If the work
		 * is not needed, it will be canceled by disable.
		 */
		जाओ reschedule;
	पूर्ण

	अगर (समय_is_after_jअगरfies(ts->last_valid_पूर्णांकerrupt +
				  msecs_to_jअगरfies(ts->esd_समयout)))
		जाओ out;

	/* We should be able to पढ़ो रेजिस्टर without disabling पूर्णांकerrupts. */
	error = regmap_पढ़ो(ts->regmap, TSC200X_REG_CFR0, &r);
	अगर (!error &&
	    !((r ^ TSC200X_CFR0_INITVALUE) & TSC200X_CFR0_RW_MASK)) अणु
		जाओ out;
	पूर्ण

	/*
	 * If we could not पढ़ो our known value from configuration रेजिस्टर 0
	 * then we should reset the controller as अगर from घातer-up and start
	 * scanning again.
	 */
	dev_info(ts->dev, "TSC200X not responding - resetting\n");

	disable_irq(ts->irq);
	del_समयr_sync(&ts->penup_समयr);

	tsc200x_update_pen_state(ts, 0, 0, 0);

	tsc200x_reset(ts);

	enable_irq(ts->irq);
	tsc200x_start_scan(ts);

out:
	mutex_unlock(&ts->mutex);
reschedule:
	/* re-arm the watchकरोg */
	schedule_delayed_work(&ts->esd_work,
			      round_jअगरfies_relative(
					msecs_to_jअगरfies(ts->esd_समयout)));
पूर्ण

अटल पूर्णांक tsc200x_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा tsc200x *ts = input_get_drvdata(input);

	mutex_lock(&ts->mutex);

	अगर (!ts->suspended)
		__tsc200x_enable(ts);

	ts->खोलोed = true;

	mutex_unlock(&ts->mutex);

	वापस 0;
पूर्ण

अटल व्योम tsc200x_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा tsc200x *ts = input_get_drvdata(input);

	mutex_lock(&ts->mutex);

	अगर (!ts->suspended)
		__tsc200x_disable(ts);

	ts->खोलोed = false;

	mutex_unlock(&ts->mutex);
पूर्ण

पूर्णांक tsc200x_probe(काष्ठा device *dev, पूर्णांक irq, स्थिर काष्ठा input_id *tsc_id,
		  काष्ठा regmap *regmap,
		  पूर्णांक (*tsc200x_cmd)(काष्ठा device *dev, u8 cmd))
अणु
	काष्ठा tsc200x *ts;
	काष्ठा input_dev *input_dev;
	u32 x_plate_ohm;
	u32 esd_समयout;
	पूर्णांक error;

	अगर (irq <= 0) अणु
		dev_err(dev, "no irq\n");
		वापस -ENODEV;
	पूर्ण

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	अगर (!tsc200x_cmd) अणु
		dev_err(dev, "no cmd function\n");
		वापस -ENODEV;
	पूर्ण

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	ts->irq = irq;
	ts->dev = dev;
	ts->idev = input_dev;
	ts->regmap = regmap;
	ts->tsc200x_cmd = tsc200x_cmd;

	error = device_property_पढ़ो_u32(dev, "ti,x-plate-ohms", &x_plate_ohm);
	ts->x_plate_ohm = error ? TSC200X_DEF_RESISTOR : x_plate_ohm;

	error = device_property_पढ़ो_u32(dev, "ti,esd-recovery-timeout-ms",
					 &esd_समयout);
	ts->esd_समयout = error ? 0 : esd_समयout;

	ts->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);
		dev_err(dev, "error acquiring reset gpio: %d\n", error);
		वापस error;
	पूर्ण

	ts->vio = devm_regulator_get(dev, "vio");
	अगर (IS_ERR(ts->vio)) अणु
		error = PTR_ERR(ts->vio);
		dev_err(dev, "error acquiring vio regulator: %d", error);
		वापस error;
	पूर्ण

	mutex_init(&ts->mutex);

	spin_lock_init(&ts->lock);
	समयr_setup(&ts->penup_समयr, tsc200x_penup_समयr, 0);

	INIT_DELAYED_WORK(&ts->esd_work, tsc200x_esd_work);

	snम_लिखो(ts->phys, माप(ts->phys),
		 "%s/input-ts", dev_name(dev));

	अगर (tsc_id->product == 2004) अणु
		input_dev->name = "TSC200X touchscreen";
	पूर्ण अन्यथा अणु
		input_dev->name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						 "TSC%04d touchscreen",
						 tsc_id->product);
		अगर (!input_dev->name)
			वापस -ENOMEM;
	पूर्ण

	input_dev->phys = ts->phys;
	input_dev->id = *tsc_id;

	input_dev->खोलो = tsc200x_खोलो;
	input_dev->बंद = tsc200x_बंद;

	input_set_drvdata(input_dev, ts);

	__set_bit(INPUT_PROP_सूचीECT, input_dev->propbit);
	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);

	input_set_असल_params(input_dev, ABS_X,
			     0, MAX_12BIT, TSC200X_DEF_X_FUZZ, 0);
	input_set_असल_params(input_dev, ABS_Y,
			     0, MAX_12BIT, TSC200X_DEF_Y_FUZZ, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE,
			     0, MAX_12BIT, TSC200X_DEF_P_FUZZ, 0);

	touchscreen_parse_properties(input_dev, false, शून्य);

	/* Ensure the touchscreen is off */
	tsc200x_stop_scan(ts);

	error = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					  tsc200x_irq_thपढ़ो,
					  IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					  "tsc200x", ts);
	अगर (error) अणु
		dev_err(dev, "Failed to request irq, err: %d\n", error);
		वापस error;
	पूर्ण

	error = regulator_enable(ts->vio);
	अगर (error)
		वापस error;

	dev_set_drvdata(dev, ts);
	error = sysfs_create_group(&dev->kobj, &tsc200x_attr_group);
	अगर (error) अणु
		dev_err(dev,
			"Failed to create sysfs attributes, err: %d\n", error);
		जाओ disable_regulator;
	पूर्ण

	error = input_रेजिस्टर_device(ts->idev);
	अगर (error) अणु
		dev_err(dev,
			"Failed to register input device, err: %d\n", error);
		जाओ err_हटाओ_sysfs;
	पूर्ण

	irq_set_irq_wake(irq, 1);
	वापस 0;

err_हटाओ_sysfs:
	sysfs_हटाओ_group(&dev->kobj, &tsc200x_attr_group);
disable_regulator:
	regulator_disable(ts->vio);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(tsc200x_probe);

पूर्णांक tsc200x_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tsc200x *ts = dev_get_drvdata(dev);

	sysfs_हटाओ_group(&dev->kobj, &tsc200x_attr_group);

	regulator_disable(ts->vio);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tsc200x_हटाओ);

अटल पूर्णांक __maybe_unused tsc200x_suspend(काष्ठा device *dev)
अणु
	काष्ठा tsc200x *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->mutex);

	अगर (!ts->suspended && ts->खोलोed)
		__tsc200x_disable(ts);

	ts->suspended = true;

	mutex_unlock(&ts->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tsc200x_resume(काष्ठा device *dev)
अणु
	काष्ठा tsc200x *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->mutex);

	अगर (ts->suspended && ts->खोलोed)
		__tsc200x_enable(ts);

	ts->suspended = false;

	mutex_unlock(&ts->mutex);

	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(tsc200x_pm_ops, tsc200x_suspend, tsc200x_resume);
EXPORT_SYMBOL_GPL(tsc200x_pm_ops);

MODULE_AUTHOR("Lauri Leukkunen <lauri.leukkunen@nokia.com>");
MODULE_DESCRIPTION("TSC200x Touchscreen Driver Core");
MODULE_LICENSE("GPL");
