<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Nano River Technologies viperboard IIO ADC driver
 *
 *  (C) 2012 by Lemonage GmbH
 *  Author: Lars Poeschel <poeschel@lemonage.de>
 *  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/usb.h>
#समावेश <linux/iio/iपन.स>

#समावेश <linux/mfd/viperboard.h>

#घोषणा VPRBRD_ADC_CMD_GET		0x00

काष्ठा vprbrd_adc_msg अणु
	u8 cmd;
	u8 chan;
	u8 val;
पूर्ण __packed;

काष्ठा vprbrd_adc अणु
	काष्ठा vprbrd *vb;
पूर्ण;

#घोषणा VPRBRD_ADC_CHANNEL(_index) अणु			\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = _index,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
पूर्ण

अटल काष्ठा iio_chan_spec स्थिर vprbrd_adc_iio_channels[] = अणु
	VPRBRD_ADC_CHANNEL(0),
	VPRBRD_ADC_CHANNEL(1),
	VPRBRD_ADC_CHANNEL(2),
	VPRBRD_ADC_CHANNEL(3),
पूर्ण;

अटल पूर्णांक vprbrd_iio_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val,
				पूर्णांक *val2,
				दीर्घ info)
अणु
	पूर्णांक ret, error = 0;
	काष्ठा vprbrd_adc *adc = iio_priv(iio_dev);
	काष्ठा vprbrd *vb = adc->vb;
	काष्ठा vprbrd_adc_msg *admsg = (काष्ठा vprbrd_adc_msg *)vb->buf;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&vb->lock);

		admsg->cmd = VPRBRD_ADC_CMD_GET;
		admsg->chan = chan->channel;
		admsg->val = 0x00;

		ret = usb_control_msg(vb->usb_dev,
			usb_sndctrlpipe(vb->usb_dev, 0), VPRBRD_USB_REQUEST_ADC,
			VPRBRD_USB_TYPE_OUT, 0x0000, 0x0000, admsg,
			माप(काष्ठा vprbrd_adc_msg), VPRBRD_USB_TIMEOUT_MS);
		अगर (ret != माप(काष्ठा vprbrd_adc_msg)) अणु
			dev_err(&iio_dev->dev, "usb send error on adc read\n");
			error = -EREMOTEIO;
		पूर्ण

		ret = usb_control_msg(vb->usb_dev,
			usb_rcvctrlpipe(vb->usb_dev, 0), VPRBRD_USB_REQUEST_ADC,
			VPRBRD_USB_TYPE_IN, 0x0000, 0x0000, admsg,
			माप(काष्ठा vprbrd_adc_msg), VPRBRD_USB_TIMEOUT_MS);

		*val = admsg->val;

		mutex_unlock(&vb->lock);

		अगर (ret != माप(काष्ठा vprbrd_adc_msg)) अणु
			dev_err(&iio_dev->dev, "usb recv error on adc read\n");
			error = -EREMOTEIO;
		पूर्ण

		अगर (error)
			जाओ error;

		वापस IIO_VAL_INT;
	शेष:
		error = -EINVAL;
		अवरोध;
	पूर्ण
error:
	वापस error;
पूर्ण

अटल स्थिर काष्ठा iio_info vprbrd_adc_iio_info = अणु
	.पढ़ो_raw = &vprbrd_iio_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक vprbrd_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vprbrd *vb = dev_get_drvdata(pdev->dev.parent);
	काष्ठा vprbrd_adc *adc;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	/* रेजिस्टरing iio */
	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	adc = iio_priv(indio_dev);
	adc->vb = vb;
	indio_dev->name = "viperboard adc";
	indio_dev->info = &vprbrd_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = vprbrd_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(vprbrd_adc_iio_channels);

	ret = devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register iio (adc)");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vprbrd_adc_driver = अणु
	.driver = अणु
		.name	= "viperboard-adc",
	पूर्ण,
	.probe		= vprbrd_adc_probe,
पूर्ण;

module_platक्रमm_driver(vprbrd_adc_driver);

MODULE_AUTHOR("Lars Poeschel <poeschel@lemonage.de>");
MODULE_DESCRIPTION("IIO ADC driver for Nano River Techs Viperboard");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:viperboard-adc");
