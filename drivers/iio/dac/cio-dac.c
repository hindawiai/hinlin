<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the Measurement Computing CIO-DAC
 * Copyright (C) 2016 William Breathitt Gray
 *
 * This driver supports the following Measurement Computing devices: CIO-DAC16,
 * CIO-DAC06, and PC104-DAC06.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

#घोषणा CIO_DAC_NUM_CHAN 16

#घोषणा CIO_DAC_CHAN(chan) अणु				\
	.type = IIO_VOLTAGE,				\
	.channel = chan,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.indexed = 1,					\
	.output = 1					\
पूर्ण

#घोषणा CIO_DAC_EXTENT 32

अटल अचिन्हित पूर्णांक base[max_num_isa_dev(CIO_DAC_EXTENT)];
अटल अचिन्हित पूर्णांक num_cio_dac;
module_param_hw_array(base, uपूर्णांक, ioport, &num_cio_dac, 0);
MODULE_PARM_DESC(base, "Measurement Computing CIO-DAC base addresses");

/**
 * काष्ठा cio_dac_iio - IIO device निजी data काष्ठाure
 * @chan_out_states:	channels' output states
 * @base:		base port address of the IIO device
 */
काष्ठा cio_dac_iio अणु
	पूर्णांक chan_out_states[CIO_DAC_NUM_CHAN];
	अचिन्हित पूर्णांक base;
पूर्ण;

अटल पूर्णांक cio_dac_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cio_dac_iio *स्थिर priv = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	*val = priv->chan_out_states[chan->channel];

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक cio_dac_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cio_dac_iio *स्थिर priv = iio_priv(indio_dev);
	स्थिर अचिन्हित पूर्णांक chan_addr_offset = 2 * chan->channel;

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	/* DAC can only accept up to a 16-bit value */
	अगर ((अचिन्हित पूर्णांक)val > 65535)
		वापस -EINVAL;

	priv->chan_out_states[chan->channel] = val;
	outw(val, priv->base + chan_addr_offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info cio_dac_info = अणु
	.पढ़ो_raw = cio_dac_पढ़ो_raw,
	.ग_लिखो_raw = cio_dac_ग_लिखो_raw
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec cio_dac_channels[CIO_DAC_NUM_CHAN] = अणु
	CIO_DAC_CHAN(0), CIO_DAC_CHAN(1), CIO_DAC_CHAN(2), CIO_DAC_CHAN(3),
	CIO_DAC_CHAN(4), CIO_DAC_CHAN(5), CIO_DAC_CHAN(6), CIO_DAC_CHAN(7),
	CIO_DAC_CHAN(8), CIO_DAC_CHAN(9), CIO_DAC_CHAN(10), CIO_DAC_CHAN(11),
	CIO_DAC_CHAN(12), CIO_DAC_CHAN(13), CIO_DAC_CHAN(14), CIO_DAC_CHAN(15)
पूर्ण;

अटल पूर्णांक cio_dac_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा cio_dac_iio *priv;
	अचिन्हित पूर्णांक i;

	indio_dev = devm_iio_device_alloc(dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], CIO_DAC_EXTENT,
		dev_name(dev))) अणु
		dev_err(dev, "Unable to request port addresses (0x%X-0x%X)\n",
			base[id], base[id] + CIO_DAC_EXTENT);
		वापस -EBUSY;
	पूर्ण

	indio_dev->info = &cio_dac_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = cio_dac_channels;
	indio_dev->num_channels = CIO_DAC_NUM_CHAN;
	indio_dev->name = dev_name(dev);

	priv = iio_priv(indio_dev);
	priv->base = base[id];

	/* initialize DAC outमाला_दो to 0V */
	क्रम (i = 0; i < 32; i += 2)
		outw(0, base[id] + i);

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा isa_driver cio_dac_driver = अणु
	.probe = cio_dac_probe,
	.driver = अणु
		.name = "cio-dac"
	पूर्ण
पूर्ण;

module_isa_driver(cio_dac_driver, num_cio_dac);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("Measurement Computing CIO-DAC IIO driver");
MODULE_LICENSE("GPL v2");
