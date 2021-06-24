<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA9150 GPADC Driver
 *
 * Copyright (c) 2014 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>
#समावेश <linux/mfd/da9150/core.h>
#समावेश <linux/mfd/da9150/रेजिस्टरs.h>

/* Channels */
क्रमागत da9150_gpadc_hw_channel अणु
	DA9150_GPADC_HW_CHAN_GPIOA_2V = 0,
	DA9150_GPADC_HW_CHAN_GPIOA_2V_,
	DA9150_GPADC_HW_CHAN_GPIOB_2V,
	DA9150_GPADC_HW_CHAN_GPIOB_2V_,
	DA9150_GPADC_HW_CHAN_GPIOC_2V,
	DA9150_GPADC_HW_CHAN_GPIOC_2V_,
	DA9150_GPADC_HW_CHAN_GPIOD_2V,
	DA9150_GPADC_HW_CHAN_GPIOD_2V_,
	DA9150_GPADC_HW_CHAN_IBUS_SENSE,
	DA9150_GPADC_HW_CHAN_IBUS_SENSE_,
	DA9150_GPADC_HW_CHAN_VBUS_DIV,
	DA9150_GPADC_HW_CHAN_VBUS_DIV_,
	DA9150_GPADC_HW_CHAN_ID,
	DA9150_GPADC_HW_CHAN_ID_,
	DA9150_GPADC_HW_CHAN_VSYS,
	DA9150_GPADC_HW_CHAN_VSYS_,
	DA9150_GPADC_HW_CHAN_GPIOA_6V,
	DA9150_GPADC_HW_CHAN_GPIOA_6V_,
	DA9150_GPADC_HW_CHAN_GPIOB_6V,
	DA9150_GPADC_HW_CHAN_GPIOB_6V_,
	DA9150_GPADC_HW_CHAN_GPIOC_6V,
	DA9150_GPADC_HW_CHAN_GPIOC_6V_,
	DA9150_GPADC_HW_CHAN_GPIOD_6V,
	DA9150_GPADC_HW_CHAN_GPIOD_6V_,
	DA9150_GPADC_HW_CHAN_VBAT,
	DA9150_GPADC_HW_CHAN_VBAT_,
	DA9150_GPADC_HW_CHAN_TBAT,
	DA9150_GPADC_HW_CHAN_TBAT_,
	DA9150_GPADC_HW_CHAN_TJUNC_CORE,
	DA9150_GPADC_HW_CHAN_TJUNC_CORE_,
	DA9150_GPADC_HW_CHAN_TJUNC_OVP,
	DA9150_GPADC_HW_CHAN_TJUNC_OVP_,
पूर्ण;

क्रमागत da9150_gpadc_channel अणु
	DA9150_GPADC_CHAN_GPIOA = 0,
	DA9150_GPADC_CHAN_GPIOB,
	DA9150_GPADC_CHAN_GPIOC,
	DA9150_GPADC_CHAN_GPIOD,
	DA9150_GPADC_CHAN_IBUS,
	DA9150_GPADC_CHAN_VBUS,
	DA9150_GPADC_CHAN_VSYS,
	DA9150_GPADC_CHAN_VBAT,
	DA9150_GPADC_CHAN_TBAT,
	DA9150_GPADC_CHAN_TJUNC_CORE,
	DA9150_GPADC_CHAN_TJUNC_OVP,
पूर्ण;

/* Private data */
काष्ठा da9150_gpadc अणु
	काष्ठा da9150 *da9150;
	काष्ठा device *dev;

	काष्ठा mutex lock;
	काष्ठा completion complete;
पूर्ण;


अटल irqवापस_t da9150_gpadc_irq(पूर्णांक irq, व्योम *data)
अणु

	काष्ठा da9150_gpadc *gpadc = data;

	complete(&gpadc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9150_gpadc_पढ़ो_adc(काष्ठा da9150_gpadc *gpadc, पूर्णांक hw_chan)
अणु
	u8 result_regs[2];
	पूर्णांक result;

	mutex_lock(&gpadc->lock);

	/* Set channel & enable measurement */
	da9150_reg_ग_लिखो(gpadc->da9150, DA9150_GPADC_MAN,
			 (DA9150_GPADC_EN_MASK |
			  hw_chan << DA9150_GPADC_MUX_SHIFT));

	/* Consume left-over completion from a previous समयout */
	try_रुको_क्रम_completion(&gpadc->complete);

	/* Check क्रम actual completion */
	रुको_क्रम_completion_समयout(&gpadc->complete, msecs_to_jअगरfies(5));

	/* Read result and status from device */
	da9150_bulk_पढ़ो(gpadc->da9150, DA9150_GPADC_RES_A, 2, result_regs);

	mutex_unlock(&gpadc->lock);

	/* Check to make sure device really has completed पढ़ोing */
	अगर (result_regs[1] & DA9150_GPADC_RUN_MASK) अणु
		dev_err(gpadc->dev, "Timeout on channel %d of GPADC\n",
			hw_chan);
		वापस -ETIMEDOUT;
	पूर्ण

	/* LSBs - 2 bits */
	result = (result_regs[1] & DA9150_GPADC_RES_L_MASK) >>
		 DA9150_GPADC_RES_L_SHIFT;
	/* MSBs - 8 bits */
	result |= result_regs[0] << DA9150_GPADC_RES_L_BITS;

	वापस result;
पूर्ण

अटल अंतरभूत पूर्णांक da9150_gpadc_gpio_6v_voltage_now(पूर्णांक raw_val)
अणु
	/* Convert to mV */
	वापस (6 * ((raw_val * 1000) + 500)) / 1024;
पूर्ण

अटल अंतरभूत पूर्णांक da9150_gpadc_ibus_current_avg(पूर्णांक raw_val)
अणु
	/* Convert to mA */
	वापस (4 * ((raw_val * 1000) + 500)) / 2048;
पूर्ण

अटल अंतरभूत पूर्णांक da9150_gpadc_vbus_21v_voltage_now(पूर्णांक raw_val)
अणु
	/* Convert to mV */
	वापस (21 * ((raw_val * 1000) + 500)) / 1024;
पूर्ण

अटल अंतरभूत पूर्णांक da9150_gpadc_vsys_6v_voltage_now(पूर्णांक raw_val)
अणु
	/* Convert to mV */
	वापस (3 * ((raw_val * 1000) + 500)) / 512;
पूर्ण

अटल पूर्णांक da9150_gpadc_पढ़ो_processed(काष्ठा da9150_gpadc *gpadc, पूर्णांक channel,
				       पूर्णांक hw_chan, पूर्णांक *val)
अणु
	पूर्णांक raw_val;

	raw_val = da9150_gpadc_पढ़ो_adc(gpadc, hw_chan);
	अगर (raw_val < 0)
		वापस raw_val;

	चयन (channel) अणु
	हाल DA9150_GPADC_CHAN_GPIOA:
	हाल DA9150_GPADC_CHAN_GPIOB:
	हाल DA9150_GPADC_CHAN_GPIOC:
	हाल DA9150_GPADC_CHAN_GPIOD:
		*val = da9150_gpadc_gpio_6v_voltage_now(raw_val);
		अवरोध;
	हाल DA9150_GPADC_CHAN_IBUS:
		*val = da9150_gpadc_ibus_current_avg(raw_val);
		अवरोध;
	हाल DA9150_GPADC_CHAN_VBUS:
		*val = da9150_gpadc_vbus_21v_voltage_now(raw_val);
		अवरोध;
	हाल DA9150_GPADC_CHAN_VSYS:
		*val = da9150_gpadc_vsys_6v_voltage_now(raw_val);
		अवरोध;
	शेष:
		/* No processing क्रम other channels so वापस raw value */
		*val = raw_val;
		अवरोध;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक da9150_gpadc_पढ़ो_scale(पूर्णांक channel, पूर्णांक *val, पूर्णांक *val2)
अणु
	चयन (channel) अणु
	हाल DA9150_GPADC_CHAN_VBAT:
		*val = 2932;
		*val2 = 1000;
		वापस IIO_VAL_FRACTIONAL;
	हाल DA9150_GPADC_CHAN_TJUNC_CORE:
	हाल DA9150_GPADC_CHAN_TJUNC_OVP:
		*val = 1000000;
		*val2 = 4420;
		वापस IIO_VAL_FRACTIONAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक da9150_gpadc_पढ़ो_offset(पूर्णांक channel, पूर्णांक *val)
अणु
	चयन (channel) अणु
	हाल DA9150_GPADC_CHAN_VBAT:
		*val = 1500000 / 2932;
		वापस IIO_VAL_INT;
	हाल DA9150_GPADC_CHAN_TJUNC_CORE:
	हाल DA9150_GPADC_CHAN_TJUNC_OVP:
		*val = -144;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक da9150_gpadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा da9150_gpadc *gpadc = iio_priv(indio_dev);

	अगर ((chan->channel < DA9150_GPADC_CHAN_GPIOA) ||
	    (chan->channel > DA9150_GPADC_CHAN_TJUNC_OVP))
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		वापस da9150_gpadc_पढ़ो_processed(gpadc, chan->channel,
						   chan->address, val);
	हाल IIO_CHAN_INFO_SCALE:
		वापस da9150_gpadc_पढ़ो_scale(chan->channel, val, val2);
	हाल IIO_CHAN_INFO_OFFSET:
		वापस da9150_gpadc_पढ़ो_offset(chan->channel, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info da9150_gpadc_info = अणु
	.पढ़ो_raw = &da9150_gpadc_पढ़ो_raw,
पूर्ण;

#घोषणा DA9150_GPADC_CHANNEL(_id, _hw_id, _type, chan_info,	\
			     _ext_name) अणु			\
	.type = _type,						\
	.indexed = 1,						\
	.channel = DA9150_GPADC_CHAN_##_id,			\
	.address = DA9150_GPADC_HW_CHAN_##_hw_id,		\
	.info_mask_separate = chan_info,			\
	.extend_name = _ext_name,				\
	.datasheet_name = #_id,					\
पूर्ण

#घोषणा DA9150_GPADC_CHANNEL_RAW(_id, _hw_id, _type, _ext_name)	\
	DA9150_GPADC_CHANNEL(_id, _hw_id, _type,		\
			     BIT(IIO_CHAN_INFO_RAW), _ext_name)

#घोषणा DA9150_GPADC_CHANNEL_SCALED(_id, _hw_id, _type, _ext_name)	\
	DA9150_GPADC_CHANNEL(_id, _hw_id, _type,			\
			     BIT(IIO_CHAN_INFO_RAW) |			\
			     BIT(IIO_CHAN_INFO_SCALE) |			\
			     BIT(IIO_CHAN_INFO_OFFSET),			\
			     _ext_name)

#घोषणा DA9150_GPADC_CHANNEL_PROCESSED(_id, _hw_id, _type, _ext_name)	\
	DA9150_GPADC_CHANNEL(_id, _hw_id, _type,			\
			     BIT(IIO_CHAN_INFO_PROCESSED), _ext_name)

/* Supported channels */
अटल स्थिर काष्ठा iio_chan_spec da9150_gpadc_channels[] = अणु
	DA9150_GPADC_CHANNEL_PROCESSED(GPIOA, GPIOA_6V, IIO_VOLTAGE, शून्य),
	DA9150_GPADC_CHANNEL_PROCESSED(GPIOB, GPIOB_6V, IIO_VOLTAGE, शून्य),
	DA9150_GPADC_CHANNEL_PROCESSED(GPIOC, GPIOC_6V, IIO_VOLTAGE, शून्य),
	DA9150_GPADC_CHANNEL_PROCESSED(GPIOD, GPIOD_6V, IIO_VOLTAGE, शून्य),
	DA9150_GPADC_CHANNEL_PROCESSED(IBUS, IBUS_SENSE, IIO_CURRENT, "ibus"),
	DA9150_GPADC_CHANNEL_PROCESSED(VBUS, VBUS_DIV_, IIO_VOLTAGE, "vbus"),
	DA9150_GPADC_CHANNEL_PROCESSED(VSYS, VSYS, IIO_VOLTAGE, "vsys"),
	DA9150_GPADC_CHANNEL_SCALED(VBAT, VBAT, IIO_VOLTAGE, "vbat"),
	DA9150_GPADC_CHANNEL_RAW(TBAT, TBAT, IIO_VOLTAGE, "tbat"),
	DA9150_GPADC_CHANNEL_SCALED(TJUNC_CORE, TJUNC_CORE, IIO_TEMP,
				    "tjunc_core"),
	DA9150_GPADC_CHANNEL_SCALED(TJUNC_OVP, TJUNC_OVP, IIO_TEMP,
				    "tjunc_ovp"),
पूर्ण;

/* Default maps used by da9150-अक्षरger */
अटल काष्ठा iio_map da9150_gpadc_शेष_maps[] = अणु
	अणु
		.consumer_dev_name = "da9150-charger",
		.consumer_channel = "CHAN_IBUS",
		.adc_channel_label = "IBUS",
	पूर्ण,
	अणु
		.consumer_dev_name = "da9150-charger",
		.consumer_channel = "CHAN_VBUS",
		.adc_channel_label = "VBUS",
	पूर्ण,
	अणु
		.consumer_dev_name = "da9150-charger",
		.consumer_channel = "CHAN_TJUNC",
		.adc_channel_label = "TJUNC_CORE",
	पूर्ण,
	अणु
		.consumer_dev_name = "da9150-charger",
		.consumer_channel = "CHAN_VBAT",
		.adc_channel_label = "VBAT",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक da9150_gpadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9150 *da9150 = dev_get_drvdata(dev->parent);
	काष्ठा da9150_gpadc *gpadc;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक irq, ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*gpadc));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "Failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण
	gpadc = iio_priv(indio_dev);

	platक्रमm_set_drvdata(pdev, indio_dev);
	gpadc->da9150 = da9150;
	gpadc->dev = dev;
	mutex_init(&gpadc->lock);
	init_completion(&gpadc->complete);

	irq = platक्रमm_get_irq_byname(pdev, "GPADC");
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, da9150_gpadc_irq,
					IRQF_ONESHOT, "GPADC", gpadc);
	अगर (ret) अणु
		dev_err(dev, "Failed to request IRQ %d: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	ret = iio_map_array_रेजिस्टर(indio_dev, da9150_gpadc_शेष_maps);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IIO maps: %d\n", ret);
		वापस ret;
	पूर्ण

	indio_dev->name = dev_name(dev);
	indio_dev->info = &da9150_gpadc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = da9150_gpadc_channels;
	indio_dev->num_channels = ARRAY_SIZE(da9150_gpadc_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IIO device: %d\n", ret);
		जाओ iio_map_unreg;
	पूर्ण

	वापस 0;

iio_map_unreg:
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक da9150_gpadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9150_gpadc_driver = अणु
	.driver = अणु
		.name = "da9150-gpadc",
	पूर्ण,
	.probe = da9150_gpadc_probe,
	.हटाओ = da9150_gpadc_हटाओ,
पूर्ण;

module_platक्रमm_driver(da9150_gpadc_driver);

MODULE_DESCRIPTION("GPADC Driver for DA9150");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
