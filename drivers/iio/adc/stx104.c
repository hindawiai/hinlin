<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the Apex Embedded Systems STX104
 * Copyright (C) 2016 William Breathitt Gray
 */
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>

#घोषणा STX104_OUT_CHAN(chan) अणु				\
	.type = IIO_VOLTAGE,				\
	.channel = chan,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.indexed = 1,					\
	.output = 1					\
पूर्ण
#घोषणा STX104_IN_CHAN(chan, dअगरf) अणु					\
	.type = IIO_VOLTAGE,						\
	.channel = chan,						\
	.channel2 = chan,						\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_HARDWAREGAIN) |	\
		BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.indexed = 1,							\
	.dअगरferential = dअगरf						\
पूर्ण

#घोषणा STX104_NUM_OUT_CHAN 2

#घोषणा STX104_EXTENT 16

अटल अचिन्हित पूर्णांक base[max_num_isa_dev(STX104_EXTENT)];
अटल अचिन्हित पूर्णांक num_stx104;
module_param_hw_array(base, uपूर्णांक, ioport, &num_stx104, 0);
MODULE_PARM_DESC(base, "Apex Embedded Systems STX104 base addresses");

/**
 * काष्ठा stx104_iio - IIO device निजी data काष्ठाure
 * @chan_out_states:	channels' output states
 * @base:		base port address of the IIO device
 */
काष्ठा stx104_iio अणु
	अचिन्हित पूर्णांक chan_out_states[STX104_NUM_OUT_CHAN];
	अचिन्हित पूर्णांक base;
पूर्ण;

/**
 * काष्ठा stx104_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @lock:	synchronization lock to prevent I/O race conditions
 * @base:	base port address of the GPIO device
 * @out_state:	output bits state
 */
काष्ठा stx104_gpio अणु
	काष्ठा gpio_chip chip;
	spinlock_t lock;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक out_state;
पूर्ण;

अटल पूर्णांक stx104_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा stx104_iio *स्थिर priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक adc_config;
	पूर्णांक adbu;
	पूर्णांक gain;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		/* get gain configuration */
		adc_config = inb(priv->base + 11);
		gain = adc_config & 0x3;

		*val = 1 << gain;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->output) अणु
			*val = priv->chan_out_states[chan->channel];
			वापस IIO_VAL_INT;
		पूर्ण

		/* select ADC channel */
		outb(chan->channel | (chan->channel << 4), priv->base + 2);

		/* trigger ADC sample capture and रुको क्रम completion */
		outb(0, priv->base);
		जबतक (inb(priv->base + 8) & BIT(7));

		*val = inw(priv->base);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		/* get ADC bipolar/unipolar configuration */
		adc_config = inb(priv->base + 11);
		adbu = !(adc_config & BIT(2));

		*val = -32768 * adbu;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* get ADC bipolar/unipolar and gain configuration */
		adc_config = inb(priv->base + 11);
		adbu = !(adc_config & BIT(2));
		gain = adc_config & 0x3;

		*val = 5;
		*val2 = 15 - adbu + gain;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक stx104_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा stx104_iio *स्थिर priv = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		/* Only four gain states (x1, x2, x4, x8) */
		चयन (val) अणु
		हाल 1:
			outb(0, priv->base + 11);
			अवरोध;
		हाल 2:
			outb(1, priv->base + 11);
			अवरोध;
		हाल 4:
			outb(2, priv->base + 11);
			अवरोध;
		हाल 8:
			outb(3, priv->base + 11);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->output) अणु
			/* DAC can only accept up to a 16-bit value */
			अगर ((अचिन्हित पूर्णांक)val > 65535)
				वापस -EINVAL;

			priv->chan_out_states[chan->channel] = val;
			outw(val, priv->base + 4 + 2 * chan->channel);

			वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info stx104_info = अणु
	.पढ़ो_raw = stx104_पढ़ो_raw,
	.ग_लिखो_raw = stx104_ग_लिखो_raw
पूर्ण;

/* single-ended input channels configuration */
अटल स्थिर काष्ठा iio_chan_spec stx104_channels_sing[] = अणु
	STX104_OUT_CHAN(0), STX104_OUT_CHAN(1),
	STX104_IN_CHAN(0, 0), STX104_IN_CHAN(1, 0), STX104_IN_CHAN(2, 0),
	STX104_IN_CHAN(3, 0), STX104_IN_CHAN(4, 0), STX104_IN_CHAN(5, 0),
	STX104_IN_CHAN(6, 0), STX104_IN_CHAN(7, 0), STX104_IN_CHAN(8, 0),
	STX104_IN_CHAN(9, 0), STX104_IN_CHAN(10, 0), STX104_IN_CHAN(11, 0),
	STX104_IN_CHAN(12, 0), STX104_IN_CHAN(13, 0), STX104_IN_CHAN(14, 0),
	STX104_IN_CHAN(15, 0)
पूर्ण;
/* dअगरferential input channels configuration */
अटल स्थिर काष्ठा iio_chan_spec stx104_channels_dअगरf[] = अणु
	STX104_OUT_CHAN(0), STX104_OUT_CHAN(1),
	STX104_IN_CHAN(0, 1), STX104_IN_CHAN(1, 1), STX104_IN_CHAN(2, 1),
	STX104_IN_CHAN(3, 1), STX104_IN_CHAN(4, 1), STX104_IN_CHAN(5, 1),
	STX104_IN_CHAN(6, 1), STX104_IN_CHAN(7, 1)
पूर्ण;

अटल पूर्णांक stx104_gpio_get_direction(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	/* GPIO 0-3 are input only, जबतक the rest are output only */
	अगर (offset < 4)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक stx104_gpio_direction_input(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= 4)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक stx104_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	अगर (offset < 4)
		वापस -EINVAL;

	chip->set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक stx104_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा stx104_gpio *स्थिर stx104gpio = gpiochip_get_data(chip);

	अगर (offset >= 4)
		वापस -EINVAL;

	वापस !!(inb(stx104gpio->base) & BIT(offset));
पूर्ण

अटल पूर्णांक stx104_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
	अचिन्हित दीर्घ *bits)
अणु
	काष्ठा stx104_gpio *स्थिर stx104gpio = gpiochip_get_data(chip);

	*bits = inb(stx104gpio->base);

	वापस 0;
पूर्ण

अटल व्योम stx104_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
	पूर्णांक value)
अणु
	काष्ठा stx104_gpio *स्थिर stx104gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset) >> 4;
	अचिन्हित दीर्घ flags;

	अगर (offset < 4)
		वापस;

	spin_lock_irqsave(&stx104gpio->lock, flags);

	अगर (value)
		stx104gpio->out_state |= mask;
	अन्यथा
		stx104gpio->out_state &= ~mask;

	outb(stx104gpio->out_state, stx104gpio->base);

	spin_unlock_irqrestore(&stx104gpio->lock, flags);
पूर्ण

#घोषणा STX104_NGPIO 8
अटल स्थिर अक्षर *stx104_names[STX104_NGPIO] = अणु
	"DIN0", "DIN1", "DIN2", "DIN3", "DOUT0", "DOUT1", "DOUT2", "DOUT3"
पूर्ण;

अटल व्योम stx104_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा stx104_gpio *स्थिर stx104gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	/* verअगरy masked GPIO are output */
	अगर (!(*mask & 0xF0))
		वापस;

	*mask >>= 4;
	*bits >>= 4;

	spin_lock_irqsave(&stx104gpio->lock, flags);

	stx104gpio->out_state &= ~*mask;
	stx104gpio->out_state |= *mask & *bits;
	outb(stx104gpio->out_state, stx104gpio->base);

	spin_unlock_irqrestore(&stx104gpio->lock, flags);
पूर्ण

अटल पूर्णांक stx104_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा stx104_iio *priv;
	काष्ठा stx104_gpio *stx104gpio;
	पूर्णांक err;

	indio_dev = devm_iio_device_alloc(dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	stx104gpio = devm_kzalloc(dev, माप(*stx104gpio), GFP_KERNEL);
	अगर (!stx104gpio)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], STX104_EXTENT,
		dev_name(dev))) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + STX104_EXTENT);
		वापस -EBUSY;
	पूर्ण

	indio_dev->info = &stx104_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* determine अगर dअगरferential inमाला_दो */
	अगर (inb(base[id] + 8) & BIT(5)) अणु
		indio_dev->num_channels = ARRAY_SIZE(stx104_channels_dअगरf);
		indio_dev->channels = stx104_channels_dअगरf;
	पूर्ण अन्यथा अणु
		indio_dev->num_channels = ARRAY_SIZE(stx104_channels_sing);
		indio_dev->channels = stx104_channels_sing;
	पूर्ण

	indio_dev->name = dev_name(dev);

	priv = iio_priv(indio_dev);
	priv->base = base[id];

	/* configure device क्रम software trigger operation */
	outb(0, base[id] + 9);

	/* initialize gain setting to x1 */
	outb(0, base[id] + 11);

	/* initialize DAC output to 0V */
	outw(0, base[id] + 4);
	outw(0, base[id] + 6);

	stx104gpio->chip.label = dev_name(dev);
	stx104gpio->chip.parent = dev;
	stx104gpio->chip.owner = THIS_MODULE;
	stx104gpio->chip.base = -1;
	stx104gpio->chip.ngpio = STX104_NGPIO;
	stx104gpio->chip.names = stx104_names;
	stx104gpio->chip.get_direction = stx104_gpio_get_direction;
	stx104gpio->chip.direction_input = stx104_gpio_direction_input;
	stx104gpio->chip.direction_output = stx104_gpio_direction_output;
	stx104gpio->chip.get = stx104_gpio_get;
	stx104gpio->chip.get_multiple = stx104_gpio_get_multiple;
	stx104gpio->chip.set = stx104_gpio_set;
	stx104gpio->chip.set_multiple = stx104_gpio_set_multiple;
	stx104gpio->base = base[id] + 3;
	stx104gpio->out_state = 0x0;

	spin_lock_init(&stx104gpio->lock);

	err = devm_gpiochip_add_data(dev, &stx104gpio->chip, stx104gpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा isa_driver stx104_driver = अणु
	.probe = stx104_probe,
	.driver = अणु
		.name = "stx104"
	पूर्ण,
पूर्ण;

module_isa_driver(stx104_driver, num_stx104);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("Apex Embedded Systems STX104 IIO driver");
MODULE_LICENSE("GPL v2");
