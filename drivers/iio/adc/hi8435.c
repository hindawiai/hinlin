<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Holt Integrated Circuits HI-8435 threshold detector driver
 *
 * Copyright (C) 2015 Zodiac Inflight Innovations
 * Copyright (C) 2015 Cogent Embedded, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_event.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpio/consumer.h>

#घोषणा DRV_NAME "hi8435"

/* Register offsets क्रम HI-8435 */
#घोषणा HI8435_CTRL_REG		0x02
#घोषणा HI8435_PSEN_REG		0x04
#घोषणा HI8435_TMDATA_REG	0x1E
#घोषणा HI8435_GOCENHYS_REG	0x3A
#घोषणा HI8435_SOCENHYS_REG	0x3C
#घोषणा HI8435_SO7_0_REG	0x10
#घोषणा HI8435_SO15_8_REG	0x12
#घोषणा HI8435_SO23_16_REG	0x14
#घोषणा HI8435_SO31_24_REG	0x16
#घोषणा HI8435_SO31_0_REG	0x78

#घोषणा HI8435_WRITE_OPCODE	0x00
#घोषणा HI8435_READ_OPCODE	0x80

/* CTRL रेजिस्टर bits */
#घोषणा HI8435_CTRL_TEST	0x01
#घोषणा HI8435_CTRL_SRST	0x02

काष्ठा hi8435_priv अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;

	अचिन्हित दीर्घ event_scan_mask; /* soft mask/unmask channels events */
	अचिन्हित पूर्णांक event_prev_val;

	अचिन्हित threshold_lo[2]; /* GND-Open and Supply-Open thresholds */
	अचिन्हित threshold_hi[2]; /* GND-Open and Supply-Open thresholds */
	u8 reg_buffer[3] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक hi8435_पढ़ोb(काष्ठा hi8435_priv *priv, u8 reg, u8 *val)
अणु
	reg |= HI8435_READ_OPCODE;
	वापस spi_ग_लिखो_then_पढ़ो(priv->spi, &reg, 1, val, 1);
पूर्ण

अटल पूर्णांक hi8435_पढ़ोw(काष्ठा hi8435_priv *priv, u8 reg, u16 *val)
अणु
	पूर्णांक ret;
	__be16 be_val;

	reg |= HI8435_READ_OPCODE;
	ret = spi_ग_लिखो_then_पढ़ो(priv->spi, &reg, 1, &be_val, 2);
	*val = be16_to_cpu(be_val);

	वापस ret;
पूर्ण

अटल पूर्णांक hi8435_पढ़ोl(काष्ठा hi8435_priv *priv, u8 reg, u32 *val)
अणु
	पूर्णांक ret;
	__be32 be_val;

	reg |= HI8435_READ_OPCODE;
	ret = spi_ग_लिखो_then_पढ़ो(priv->spi, &reg, 1, &be_val, 4);
	*val = be32_to_cpu(be_val);

	वापस ret;
पूर्ण

अटल पूर्णांक hi8435_ग_लिखोb(काष्ठा hi8435_priv *priv, u8 reg, u8 val)
अणु
	priv->reg_buffer[0] = reg | HI8435_WRITE_OPCODE;
	priv->reg_buffer[1] = val;

	वापस spi_ग_लिखो(priv->spi, priv->reg_buffer, 2);
पूर्ण

अटल पूर्णांक hi8435_ग_लिखोw(काष्ठा hi8435_priv *priv, u8 reg, u16 val)
अणु
	priv->reg_buffer[0] = reg | HI8435_WRITE_OPCODE;
	priv->reg_buffer[1] = (val >> 8) & 0xff;
	priv->reg_buffer[2] = val & 0xff;

	वापस spi_ग_लिखो(priv->spi, priv->reg_buffer, 3);
पूर्ण

अटल पूर्णांक hi8435_पढ़ो_raw(काष्ठा iio_dev *idev,
			   स्थिर काष्ठा iio_chan_spec *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	u32 पंचांगp;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = hi8435_पढ़ोl(priv, HI8435_SO31_0_REG, &पंचांगp);
		अगर (ret < 0)
			वापस ret;
		*val = !!(पंचांगp & BIT(chan->channel));
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hi8435_पढ़ो_event_config(काष्ठा iio_dev *idev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);

	वापस !!(priv->event_scan_mask & BIT(chan->channel));
पूर्ण

अटल पूर्णांक hi8435_ग_लिखो_event_config(काष्ठा iio_dev *idev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	पूर्णांक ret;
	u32 पंचांगp;

	अगर (state) अणु
		ret = hi8435_पढ़ोl(priv, HI8435_SO31_0_REG, &पंचांगp);
		अगर (ret < 0)
			वापस ret;
		अगर (पंचांगp & BIT(chan->channel))
			priv->event_prev_val |= BIT(chan->channel);
		अन्यथा
			priv->event_prev_val &= ~BIT(chan->channel);

		priv->event_scan_mask |= BIT(chan->channel);
	पूर्ण अन्यथा
		priv->event_scan_mask &= ~BIT(chan->channel);

	वापस 0;
पूर्ण

अटल पूर्णांक hi8435_पढ़ो_event_value(काष्ठा iio_dev *idev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   क्रमागत iio_event_type type,
				   क्रमागत iio_event_direction dir,
				   क्रमागत iio_event_info info,
				   पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	पूर्णांक ret;
	u8 mode, psen;
	u16 reg;

	ret = hi8435_पढ़ोb(priv, HI8435_PSEN_REG, &psen);
	अगर (ret < 0)
		वापस ret;

	/* Supply-Open or GND-Open sensing mode */
	mode = !!(psen & BIT(chan->channel / 8));

	ret = hi8435_पढ़ोw(priv, mode ? HI8435_SOCENHYS_REG :
				 HI8435_GOCENHYS_REG, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (dir == IIO_EV_सूची_FALLING)
		*val = ((reg & 0xff) - (reg >> 8)) / 2;
	अन्यथा अगर (dir == IIO_EV_सूची_RISING)
		*val = ((reg & 0xff) + (reg >> 8)) / 2;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक hi8435_ग_लिखो_event_value(काष्ठा iio_dev *idev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	पूर्णांक ret;
	u8 mode, psen;
	u16 reg;

	ret = hi8435_पढ़ोb(priv, HI8435_PSEN_REG, &psen);
	अगर (ret < 0)
		वापस ret;

	/* Supply-Open or GND-Open sensing mode */
	mode = !!(psen & BIT(chan->channel / 8));

	ret = hi8435_पढ़ोw(priv, mode ? HI8435_SOCENHYS_REG :
				 HI8435_GOCENHYS_REG, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (dir == IIO_EV_सूची_FALLING) अणु
		/* falling threshold range 2..21V, hysteresis minimum 2V */
		अगर (val < 2 || val > 21 || (val + 2) > priv->threshold_hi[mode])
			वापस -EINVAL;

		अगर (val == priv->threshold_lo[mode])
			वापस 0;

		priv->threshold_lo[mode] = val;

		/* hysteresis must not be odd */
		अगर ((priv->threshold_hi[mode] - priv->threshold_lo[mode]) % 2)
			priv->threshold_hi[mode]--;
	पूर्ण अन्यथा अगर (dir == IIO_EV_सूची_RISING) अणु
		/* rising threshold range 3..22V, hysteresis minimum 2V */
		अगर (val < 3 || val > 22 || val < (priv->threshold_lo[mode] + 2))
			वापस -EINVAL;

		अगर (val == priv->threshold_hi[mode])
			वापस 0;

		priv->threshold_hi[mode] = val;

		/* hysteresis must not be odd */
		अगर ((priv->threshold_hi[mode] - priv->threshold_lo[mode]) % 2)
			priv->threshold_lo[mode]++;
	पूर्ण

	/* program thresholds */
	mutex_lock(&priv->lock);

	ret = hi8435_पढ़ोw(priv, mode ? HI8435_SOCENHYS_REG :
				 HI8435_GOCENHYS_REG, &reg);
	अगर (ret < 0) अणु
		mutex_unlock(&priv->lock);
		वापस ret;
	पूर्ण

	/* hysteresis */
	reg = priv->threshold_hi[mode] - priv->threshold_lo[mode];
	reg <<= 8;
	/* threshold center */
	reg |= (priv->threshold_hi[mode] + priv->threshold_lo[mode]);

	ret = hi8435_ग_लिखोw(priv, mode ? HI8435_SOCENHYS_REG :
				  HI8435_GOCENHYS_REG, reg);

	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hi8435_debugfs_reg_access(काष्ठा iio_dev *idev,
				     अचिन्हित reg, अचिन्हित ग_लिखोval,
				     अचिन्हित *पढ़ोval)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	पूर्णांक ret;
	u8 val;

	अगर (पढ़ोval != शून्य) अणु
		ret = hi8435_पढ़ोb(priv, reg, &val);
		*पढ़ोval = val;
	पूर्ण अन्यथा अणु
		val = (u8)ग_लिखोval;
		ret = hi8435_ग_लिखोb(priv, reg, val);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec hi8435_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक hi8435_get_sensing_mode(काष्ठा iio_dev *idev,
				   स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	पूर्णांक ret;
	u8 reg;

	ret = hi8435_पढ़ोb(priv, HI8435_PSEN_REG, &reg);
	अगर (ret < 0)
		वापस ret;

	वापस !!(reg & BIT(chan->channel / 8));
पूर्ण

अटल पूर्णांक hi8435_set_sensing_mode(काष्ठा iio_dev *idev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   अचिन्हित पूर्णांक mode)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	पूर्णांक ret;
	u8 reg;

	mutex_lock(&priv->lock);

	ret = hi8435_पढ़ोb(priv, HI8435_PSEN_REG, &reg);
	अगर (ret < 0) अणु
		mutex_unlock(&priv->lock);
		वापस ret;
	पूर्ण

	reg &= ~BIT(chan->channel / 8);
	अगर (mode)
		reg |= BIT(chan->channel / 8);

	ret = hi8435_ग_लिखोb(priv, HI8435_PSEN_REG, reg);

	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर hi8435_sensing_modes[] = अणु "GND-Open",
						     "Supply-Open" पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत hi8435_sensing_mode = अणु
	.items = hi8435_sensing_modes,
	.num_items = ARRAY_SIZE(hi8435_sensing_modes),
	.get = hi8435_get_sensing_mode,
	.set = hi8435_set_sensing_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info hi8435_ext_info[] = अणु
	IIO_ENUM("sensing_mode", IIO_SEPARATE, &hi8435_sensing_mode),
	IIO_ENUM_AVAILABLE("sensing_mode", &hi8435_sensing_mode),
	अणुपूर्ण,
पूर्ण;

#घोषणा HI8435_VOLTAGE_CHANNEL(num)			\
अणु							\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = num,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.event_spec = hi8435_events,			\
	.num_event_specs = ARRAY_SIZE(hi8435_events),	\
	.ext_info = hi8435_ext_info,			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec hi8435_channels[] = अणु
	HI8435_VOLTAGE_CHANNEL(0),
	HI8435_VOLTAGE_CHANNEL(1),
	HI8435_VOLTAGE_CHANNEL(2),
	HI8435_VOLTAGE_CHANNEL(3),
	HI8435_VOLTAGE_CHANNEL(4),
	HI8435_VOLTAGE_CHANNEL(5),
	HI8435_VOLTAGE_CHANNEL(6),
	HI8435_VOLTAGE_CHANNEL(7),
	HI8435_VOLTAGE_CHANNEL(8),
	HI8435_VOLTAGE_CHANNEL(9),
	HI8435_VOLTAGE_CHANNEL(10),
	HI8435_VOLTAGE_CHANNEL(11),
	HI8435_VOLTAGE_CHANNEL(12),
	HI8435_VOLTAGE_CHANNEL(13),
	HI8435_VOLTAGE_CHANNEL(14),
	HI8435_VOLTAGE_CHANNEL(15),
	HI8435_VOLTAGE_CHANNEL(16),
	HI8435_VOLTAGE_CHANNEL(17),
	HI8435_VOLTAGE_CHANNEL(18),
	HI8435_VOLTAGE_CHANNEL(19),
	HI8435_VOLTAGE_CHANNEL(20),
	HI8435_VOLTAGE_CHANNEL(21),
	HI8435_VOLTAGE_CHANNEL(22),
	HI8435_VOLTAGE_CHANNEL(23),
	HI8435_VOLTAGE_CHANNEL(24),
	HI8435_VOLTAGE_CHANNEL(25),
	HI8435_VOLTAGE_CHANNEL(26),
	HI8435_VOLTAGE_CHANNEL(27),
	HI8435_VOLTAGE_CHANNEL(28),
	HI8435_VOLTAGE_CHANNEL(29),
	HI8435_VOLTAGE_CHANNEL(30),
	HI8435_VOLTAGE_CHANNEL(31),
	IIO_CHAN_SOFT_TIMESTAMP(32),
पूर्ण;

अटल स्थिर काष्ठा iio_info hi8435_info = अणु
	.पढ़ो_raw = hi8435_पढ़ो_raw,
	.पढ़ो_event_config = hi8435_पढ़ो_event_config,
	.ग_लिखो_event_config = hi8435_ग_लिखो_event_config,
	.पढ़ो_event_value = hi8435_पढ़ो_event_value,
	.ग_लिखो_event_value = hi8435_ग_लिखो_event_value,
	.debugfs_reg_access = hi8435_debugfs_reg_access,
पूर्ण;

अटल व्योम hi8435_iio_push_event(काष्ठा iio_dev *idev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	क्रमागत iio_event_direction dir;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक status = priv->event_prev_val ^ val;

	अगर (!status)
		वापस;

	क्रम_each_set_bit(i, &priv->event_scan_mask, 32) अणु
		अगर (status & BIT(i)) अणु
			dir = val & BIT(i) ? IIO_EV_सूची_RISING :
					     IIO_EV_सूची_FALLING;
			iio_push_event(idev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, i,
						    IIO_EV_TYPE_THRESH, dir),
				       iio_get_समय_ns(idev));
		पूर्ण
	पूर्ण

	priv->event_prev_val = val;
पूर्ण

अटल irqवापस_t hi8435_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *idev = pf->indio_dev;
	काष्ठा hi8435_priv *priv = iio_priv(idev);
	u32 val;
	पूर्णांक ret;

	ret = hi8435_पढ़ोl(priv, HI8435_SO31_0_REG, &val);
	अगर (ret < 0)
		जाओ err_पढ़ो;

	hi8435_iio_push_event(idev, val);

err_पढ़ो:
	iio_trigger_notअगरy_करोne(idev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hi8435_triggered_event_cleanup(व्योम *data)
अणु
	iio_triggered_event_cleanup(data);
पूर्ण

अटल पूर्णांक hi8435_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *idev;
	काष्ठा hi8435_priv *priv;
	काष्ठा gpio_desc *reset_gpio;
	पूर्णांक ret;

	idev = devm_iio_device_alloc(&spi->dev, माप(*priv));
	अगर (!idev)
		वापस -ENOMEM;

	priv = iio_priv(idev);
	priv->spi = spi;

	reset_gpio = devm_gpiod_get(&spi->dev, शून्य, GPIOD_OUT_LOW);
	अगर (IS_ERR(reset_gpio)) अणु
		/* chip s/w reset अगर h/w reset failed */
		hi8435_ग_लिखोb(priv, HI8435_CTRL_REG, HI8435_CTRL_SRST);
		hi8435_ग_लिखोb(priv, HI8435_CTRL_REG, 0);
	पूर्ण अन्यथा अणु
		udelay(5);
		gpiod_set_value_cansleep(reset_gpio, 1);
	पूर्ण

	spi_set_drvdata(spi, idev);
	mutex_init(&priv->lock);

	idev->name		= spi_get_device_id(spi)->name;
	idev->modes		= INDIO_सूचीECT_MODE;
	idev->info		= &hi8435_info;
	idev->channels		= hi8435_channels;
	idev->num_channels	= ARRAY_SIZE(hi8435_channels);

	/* unmask all events */
	priv->event_scan_mask = ~(0);
	/*
	 * There is a restriction in the chip - the hysteresis can not be odd.
	 * If the hysteresis is set to odd value then chip माला_लो पूर्णांकo lock state
	 * and not functional anymore.
	 * After chip reset the thresholds are in undefined state, so we need to
	 * initialize thresholds to some initial values and then prevent
	 * userspace setting odd hysteresis.
	 *
	 * Set threshold low voltage to 2V, threshold high voltage to 4V
	 * क्रम both GND-Open and Supply-Open sensing modes.
	 */
	priv->threshold_lo[0] = priv->threshold_lo[1] = 2;
	priv->threshold_hi[0] = priv->threshold_hi[1] = 4;
	hi8435_ग_लिखोw(priv, HI8435_GOCENHYS_REG, 0x206);
	hi8435_ग_लिखोw(priv, HI8435_SOCENHYS_REG, 0x206);

	ret = iio_triggered_event_setup(idev, शून्य, hi8435_trigger_handler);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev,
				       hi8435_triggered_event_cleanup,
				       idev);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, idev);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi8435_dt_ids[] = अणु
	अणु .compatible = "holt,hi8435" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi8435_dt_ids);

अटल स्थिर काष्ठा spi_device_id hi8435_id[] = अणु
	अणु "hi8435", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, hi8435_id);

अटल काष्ठा spi_driver hi8435_driver = अणु
	.driver	= अणु
		.name		= DRV_NAME,
		.of_match_table	= hi8435_dt_ids,
	पूर्ण,
	.probe		= hi8435_probe,
	.id_table	= hi8435_id,
पूर्ण;
module_spi_driver(hi8435_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladimir Barinov");
MODULE_DESCRIPTION("HI-8435 threshold detector");
