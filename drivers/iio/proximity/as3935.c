<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * as3935.c - Support क्रम AS3935 Franklin lightning sensor
 *
 * Copyright (C) 2014, 2017-2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा AS3935_AFE_GAIN		0x00
#घोषणा AS3935_AFE_MASK		0x3F
#घोषणा AS3935_AFE_GAIN_MAX	0x1F
#घोषणा AS3935_AFE_PWR_BIT	BIT(0)

#घोषणा AS3935_NFLWDTH		0x01
#घोषणा AS3935_NFLWDTH_MASK	0x7f

#घोषणा AS3935_INT		0x03
#घोषणा AS3935_INT_MASK		0x0f
#घोषणा AS3935_DISTURB_INT	BIT(2)
#घोषणा AS3935_EVENT_INT	BIT(3)
#घोषणा AS3935_NOISE_INT	BIT(0)

#घोषणा AS3935_DATA		0x07
#घोषणा AS3935_DATA_MASK	0x3F

#घोषणा AS3935_TUNE_CAP		0x08
#घोषणा AS3935_DEFAULTS		0x3C
#घोषणा AS3935_CALIBRATE	0x3D

#घोषणा AS3935_READ_DATA	BIT(14)
#घोषणा AS3935_ADDRESS(x)	((x) << 8)

#घोषणा MAX_PF_CAP		120
#घोषणा TUNE_CAP_DIV		8

काष्ठा as3935_state अणु
	काष्ठा spi_device *spi;
	काष्ठा iio_trigger *trig;
	काष्ठा mutex lock;
	काष्ठा delayed_work work;

	अचिन्हित दीर्घ noise_tripped;
	u32 tune_cap;
	u32 nflwdth_reg;
	u8 buffer[16]; /* 8-bit data + 56-bit padding + 64-bit बारtamp */
	u8 buf[2] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec as3935_channels[] = अणु
	अणु
		.type           = IIO_PROXIMITY,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_SCALE),
		.scan_index     = 0,
		.scan_type = अणु
			.sign           = 'u',
			.realbits       = 6,
			.storagebits    = 8,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल पूर्णांक as3935_पढ़ो(काष्ठा as3935_state *st, अचिन्हित पूर्णांक reg, पूर्णांक *val)
अणु
	u8 cmd;
	पूर्णांक ret;

	cmd = (AS3935_READ_DATA | AS3935_ADDRESS(reg)) >> 8;
	ret = spi_w8r8(st->spi, cmd);
	अगर (ret < 0)
		वापस ret;
	*val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक as3935_ग_लिखो(काष्ठा as3935_state *st,
				अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	u8 *buf = st->buf;

	buf[0] = AS3935_ADDRESS(reg) >> 8;
	buf[1] = val;

	वापस spi_ग_लिखो(st->spi, buf, 2);
पूर्ण

अटल sमाप_प्रकार as3935_sensor_sensitivity_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा as3935_state *st = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक val, ret;

	ret = as3935_पढ़ो(st, AS3935_AFE_GAIN, &val);
	अगर (ret)
		वापस ret;
	val = (val & AS3935_AFE_MASK) >> 1;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार as3935_sensor_sensitivity_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा as3935_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ((स्थिर अक्षर *) buf, 10, &val);
	अगर (ret)
		वापस -EINVAL;

	अगर (val > AS3935_AFE_GAIN_MAX)
		वापस -EINVAL;

	as3935_ग_लिखो(st, AS3935_AFE_GAIN, val << 1);

	वापस len;
पूर्ण

अटल sमाप_प्रकार as3935_noise_level_tripped_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा as3935_state *st = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = प्र_लिखो(buf, "%d\n", !समय_after(jअगरfies, st->noise_tripped + HZ));
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल IIO_DEVICE_ATTR(sensor_sensitivity, S_IRUGO | S_IWUSR,
	as3935_sensor_sensitivity_show, as3935_sensor_sensitivity_store, 0);

अटल IIO_DEVICE_ATTR(noise_level_tripped, S_IRUGO,
	as3935_noise_level_tripped_show, शून्य, 0);

अटल काष्ठा attribute *as3935_attributes[] = अणु
	&iio_dev_attr_sensor_sensitivity.dev_attr.attr,
	&iio_dev_attr_noise_level_tripped.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group as3935_attribute_group = अणु
	.attrs = as3935_attributes,
पूर्ण;

अटल पूर्णांक as3935_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा as3935_state *st = iio_priv(indio_dev);
	पूर्णांक ret;


	चयन (m) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
	हाल IIO_CHAN_INFO_RAW:
		*val2 = 0;
		ret = as3935_पढ़ो(st, AS3935_DATA, val);
		अगर (ret)
			वापस ret;

		/* storm out of range */
		अगर (*val == AS3935_DATA_MASK)
			वापस -EINVAL;

		अगर (m == IIO_CHAN_INFO_RAW)
			वापस IIO_VAL_INT;

		अगर (m == IIO_CHAN_INFO_PROCESSED)
			*val *= 1000;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info as3935_info = अणु
	.attrs = &as3935_attribute_group,
	.पढ़ो_raw = &as3935_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t as3935_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा as3935_state *st = iio_priv(indio_dev);
	पूर्णांक val, ret;

	ret = as3935_पढ़ो(st, AS3935_DATA, &val);
	अगर (ret)
		जाओ err_पढ़ो;

	st->buffer[0] = val & AS3935_DATA_MASK;
	iio_push_to_buffers_with_बारtamp(indio_dev, &st->buffer,
					   iio_get_समय_ns(indio_dev));
err_पढ़ो:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops iio_पूर्णांकerrupt_trigger_ops = अणु
पूर्ण;

अटल व्योम as3935_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा as3935_state *st;
	पूर्णांक val;
	पूर्णांक ret;

	st = container_of(work, काष्ठा as3935_state, work.work);

	ret = as3935_पढ़ो(st, AS3935_INT, &val);
	अगर (ret) अणु
		dev_warn(&st->spi->dev, "read error\n");
		वापस;
	पूर्ण

	val &= AS3935_INT_MASK;

	चयन (val) अणु
	हाल AS3935_EVENT_INT:
		iio_trigger_poll_chained(st->trig);
		अवरोध;
	हाल AS3935_DISTURB_INT:
	हाल AS3935_NOISE_INT:
		mutex_lock(&st->lock);
		st->noise_tripped = jअगरfies;
		mutex_unlock(&st->lock);
		dev_warn(&st->spi->dev, "noise level is too high\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t as3935_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा as3935_state *st = iio_priv(indio_dev);

	/*
	 * Delay work क्रम >2 milliseconds after an पूर्णांकerrupt to allow
	 * estimated distance to recalculated.
	 */

	schedule_delayed_work(&st->work, msecs_to_jअगरfies(3));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम calibrate_as3935(काष्ठा as3935_state *st)
अणु
	as3935_ग_लिखो(st, AS3935_DEFAULTS, 0x96);
	as3935_ग_लिखो(st, AS3935_CALIBRATE, 0x96);
	as3935_ग_लिखो(st, AS3935_TUNE_CAP,
		BIT(5) | (st->tune_cap / TUNE_CAP_DIV));

	mdelay(2);
	as3935_ग_लिखो(st, AS3935_TUNE_CAP, (st->tune_cap / TUNE_CAP_DIV));
	as3935_ग_लिखो(st, AS3935_NFLWDTH, st->nflwdth_reg);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक as3935_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा as3935_state *st = iio_priv(indio_dev);
	पूर्णांक val, ret;

	mutex_lock(&st->lock);
	ret = as3935_पढ़ो(st, AS3935_AFE_GAIN, &val);
	अगर (ret)
		जाओ err_suspend;
	val |= AS3935_AFE_PWR_BIT;

	ret = as3935_ग_लिखो(st, AS3935_AFE_GAIN, val);

err_suspend:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक as3935_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा as3935_state *st = iio_priv(indio_dev);
	पूर्णांक val, ret;

	mutex_lock(&st->lock);
	ret = as3935_पढ़ो(st, AS3935_AFE_GAIN, &val);
	अगर (ret)
		जाओ err_resume;
	val &= ~AS3935_AFE_PWR_BIT;
	ret = as3935_ग_लिखो(st, AS3935_AFE_GAIN, val);

	calibrate_as3935(st);

err_resume:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(as3935_pm_ops, as3935_suspend, as3935_resume);
#घोषणा AS3935_PM_OPS (&as3935_pm_ops)

#अन्यथा
#घोषणा AS3935_PM_OPS शून्य
#पूर्ण_अगर

अटल व्योम as3935_stop_work(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा as3935_state *st = iio_priv(indio_dev);

	cancel_delayed_work_sync(&st->work);
पूर्ण

अटल पूर्णांक as3935_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_trigger *trig;
	काष्ठा as3935_state *st;
	पूर्णांक ret;

	/* Be sure lightning event पूर्णांकerrupt is specअगरied */
	अगर (!spi->irq) अणु
		dev_err(dev, "unable to get event interrupt\n");
		वापस -EINVAL;
	पूर्ण

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	spi_set_drvdata(spi, indio_dev);
	mutex_init(&st->lock);

	ret = device_property_पढ़ो_u32(dev,
			"ams,tuning-capacitor-pf", &st->tune_cap);
	अगर (ret) अणु
		st->tune_cap = 0;
		dev_warn(dev, "no tuning-capacitor-pf set, defaulting to %d",
			st->tune_cap);
	पूर्ण

	अगर (st->tune_cap > MAX_PF_CAP) अणु
		dev_err(dev, "wrong tuning-capacitor-pf setting of %d\n",
			st->tune_cap);
		वापस -EINVAL;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev,
			"ams,nflwdth", &st->nflwdth_reg);
	अगर (!ret && st->nflwdth_reg > AS3935_NFLWDTH_MASK) अणु
		dev_err(dev, "invalid nflwdth setting of %d\n",
			st->nflwdth_reg);
		वापस -EINVAL;
	पूर्ण

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = as3935_channels;
	indio_dev->num_channels = ARRAY_SIZE(as3935_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &as3935_info;

	trig = devm_iio_trigger_alloc(dev, "%s-dev%d",
				      indio_dev->name, indio_dev->id);

	अगर (!trig)
		वापस -ENOMEM;

	st->trig = trig;
	st->noise_tripped = jअगरfies - HZ;
	iio_trigger_set_drvdata(trig, indio_dev);
	trig->ops = &iio_पूर्णांकerrupt_trigger_ops;

	ret = devm_iio_trigger_रेजिस्टर(dev, trig);
	अगर (ret) अणु
		dev_err(dev, "failed to register trigger\n");
		वापस ret;
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					      iio_pollfunc_store_समय,
					      as3935_trigger_handler, शून्य);

	अगर (ret) अणु
		dev_err(dev, "cannot setup iio trigger\n");
		वापस ret;
	पूर्ण

	calibrate_as3935(st);

	INIT_DELAYED_WORK(&st->work, as3935_event_work);
	ret = devm_add_action(dev, as3935_stop_work, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(dev, spi->irq,
				&as3935_पूर्णांकerrupt_handler,
				IRQF_TRIGGER_RISING,
				dev_name(dev),
				indio_dev);

	अगर (ret) अणु
		dev_err(dev, "unable to request irq\n");
		वापस ret;
	पूर्ण

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register device\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id as3935_of_match[] = अणु
	अणु .compatible = "ams,as3935", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, as3935_of_match);

अटल स्थिर काष्ठा spi_device_id as3935_id[] = अणु
	अणु"as3935", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, as3935_id);

अटल काष्ठा spi_driver as3935_driver = अणु
	.driver = अणु
		.name	= "as3935",
		.of_match_table = as3935_of_match,
		.pm	= AS3935_PM_OPS,
	पूर्ण,
	.probe		= as3935_probe,
	.id_table	= as3935_id,
पूर्ण;
module_spi_driver(as3935_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("AS3935 lightning sensor");
MODULE_LICENSE("GPL");
