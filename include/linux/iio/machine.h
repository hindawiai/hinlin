<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Industrial I/O in kernel access map definitions क्रम board files.
 *
 * Copyright (c) 2011 Jonathan Cameron
 */

#अगर_अघोषित __LINUX_IIO_MACHINE_H__
#घोषणा __LINUX_IIO_MACHINE_H__

/**
 * काष्ठा iio_map - description of link between consumer and device channels
 * @adc_channel_label:	Label used to identअगरy the channel on the provider.
 *			This is matched against the datasheet_name element
 *			of काष्ठा iio_chan_spec.
 * @consumer_dev_name:	Name to uniquely identअगरy the consumer device.
 * @consumer_channel:	Unique name used to identअगरy the channel on the
 *			consumer side.
 * @consumer_data:	Data about the channel क्रम use by the consumer driver.
 */
काष्ठा iio_map अणु
	स्थिर अक्षर *adc_channel_label;
	स्थिर अक्षर *consumer_dev_name;
	स्थिर अक्षर *consumer_channel;
	व्योम *consumer_data;
पूर्ण;

#घोषणा IIO_MAP(_provider_channel, _consumer_dev_name, _consumer_channel) \
अणु									  \
	.adc_channel_label = _provider_channel,				  \
	.consumer_dev_name = _consumer_dev_name,			  \
	.consumer_channel  = _consumer_channel,				  \
पूर्ण

#पूर्ण_अगर
