<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AD7606 ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#अगर_अघोषित IIO_ADC_AD7606_H_
#घोषणा IIO_ADC_AD7606_H_

#घोषणा AD760X_CHANNEL(num, mask_sep, mask_type, mask_all) अणु	\
		.type = IIO_VOLTAGE,				\
		.indexed = 1,					\
		.channel = num,					\
		.address = num,					\
		.info_mask_separate = mask_sep,			\
		.info_mask_shared_by_type = mask_type,		\
		.info_mask_shared_by_all = mask_all,		\
		.scan_index = num,				\
		.scan_type = अणु					\
			.sign = 's',				\
			.realbits = 16,				\
			.storagebits = 16,			\
			.endianness = IIO_CPU,			\
		पूर्ण,						\
पूर्ण

#घोषणा AD7605_CHANNEL(num)				\
	AD760X_CHANNEL(num, BIT(IIO_CHAN_INFO_RAW),	\
		BIT(IIO_CHAN_INFO_SCALE), 0)

#घोषणा AD7606_CHANNEL(num)				\
	AD760X_CHANNEL(num, BIT(IIO_CHAN_INFO_RAW),	\
		BIT(IIO_CHAN_INFO_SCALE),		\
		BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO))

#घोषणा AD7616_CHANNEL(num)	\
	AD760X_CHANNEL(num, BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),\
		0, BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO))

/**
 * काष्ठा ad7606_chip_info - chip specअगरic inक्रमmation
 * @channels:		channel specअगरication
 * @num_channels:	number of channels
 * @oversampling_avail	poपूर्णांकer to the array which stores the available
 *			oversampling ratios.
 * @oversampling_num	number of elements stored in oversampling_avail array
 * @os_req_reset	some devices require a reset to update oversampling
 * @init_delay_ms	required delay in miliseconds क्रम initialization
 *			after a restart
 */
काष्ठा ad7606_chip_info अणु
	स्थिर काष्ठा iio_chan_spec	*channels;
	अचिन्हित पूर्णांक			num_channels;
	स्थिर अचिन्हित पूर्णांक		*oversampling_avail;
	अचिन्हित पूर्णांक			oversampling_num;
	bool				os_req_reset;
	अचिन्हित दीर्घ			init_delay_ms;
पूर्ण;

/**
 * काष्ठा ad7606_state - driver instance specअगरic data
 * @dev		poपूर्णांकer to kernel device
 * @chip_info		entry in the table of chips that describes this device
 * @reg		regulator info क्रम the the घातer supply of the device
 * @bops		bus operations (SPI or parallel)
 * @range		voltage range selection, selects which scale to apply
 * @oversampling	oversampling selection
 * @base_address	address from where to पढ़ो data in parallel operation
 * @sw_mode_en		software mode enabled
 * @scale_avail		poपूर्णांकer to the array which stores the available scales
 * @num_scales		number of elements stored in the scale_avail array
 * @oversampling_avail	poपूर्णांकer to the array which stores the available
 *			oversampling ratios.
 * @num_os_ratios	number of elements stored in oversampling_avail array
 * @ग_लिखो_scale		poपूर्णांकer to the function which ग_लिखोs the scale
 * @ग_लिखो_os		poपूर्णांकer to the function which ग_लिखोs the os
 * @lock		protect sensor state from concurrent accesses to GPIOs
 * @gpio_convst	GPIO descriptor क्रम conversion start संकेत (CONVST)
 * @gpio_reset		GPIO descriptor क्रम device hard-reset
 * @gpio_range		GPIO descriptor क्रम range selection
 * @gpio_standby	GPIO descriptor क्रम stand-by संकेत (STBY),
 *			controls घातer-करोwn mode of device
 * @gpio_frstdata	GPIO descriptor क्रम पढ़ोing from device when data
 *			is being पढ़ो on the first channel
 * @gpio_os		GPIO descriptors to control oversampling on the device
 * @complete		completion to indicate end of conversion
 * @trig		The IIO trigger associated with the device.
 * @data		buffer क्रम पढ़ोing data from the device
 * @d16			be16 buffer क्रम पढ़ोing data from the device
 */
काष्ठा ad7606_state अणु
	काष्ठा device			*dev;
	स्थिर काष्ठा ad7606_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	स्थिर काष्ठा ad7606_bus_ops	*bops;
	अचिन्हित पूर्णांक			range[16];
	अचिन्हित पूर्णांक			oversampling;
	व्योम __iomem			*base_address;
	bool				sw_mode_en;
	स्थिर अचिन्हित पूर्णांक		*scale_avail;
	अचिन्हित पूर्णांक			num_scales;
	स्थिर अचिन्हित पूर्णांक		*oversampling_avail;
	अचिन्हित पूर्णांक			num_os_ratios;
	पूर्णांक (*ग_लिखो_scale)(काष्ठा iio_dev *indio_dev, पूर्णांक ch, पूर्णांक val);
	पूर्णांक (*ग_लिखो_os)(काष्ठा iio_dev *indio_dev, पूर्णांक val);

	काष्ठा mutex			lock; /* protect sensor state */
	काष्ठा gpio_desc		*gpio_convst;
	काष्ठा gpio_desc		*gpio_reset;
	काष्ठा gpio_desc		*gpio_range;
	काष्ठा gpio_desc		*gpio_standby;
	काष्ठा gpio_desc		*gpio_frstdata;
	काष्ठा gpio_descs		*gpio_os;
	काष्ठा iio_trigger		*trig;
	काष्ठा completion		completion;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * 16 * 16-bit samples + 64-bit बारtamp
	 */
	अचिन्हित लघु			data[20] ____cacheline_aligned;
	__be16				d16[2];
पूर्ण;

/**
 * काष्ठा ad7606_bus_ops - driver bus operations
 * @पढ़ो_block		function poपूर्णांकer क्रम पढ़ोing blocks of data
 * @sw_mode_config:	poपूर्णांकer to a function which configured the device
 *			क्रम software mode
 * @reg_पढ़ो	function poपूर्णांकer क्रम पढ़ोing spi रेजिस्टर
 * @reg_ग_लिखो	function poपूर्णांकer क्रम writing spi रेजिस्टर
 * @ग_लिखो_mask	function poपूर्णांकer क्रम ग_लिखो spi रेजिस्टर with mask
 * @rd_wr_cmd	poपूर्णांकer to the function which calculates the spi address
 */
काष्ठा ad7606_bus_ops अणु
	/* more methods added in future? */
	पूर्णांक (*पढ़ो_block)(काष्ठा device *dev, पूर्णांक num, व्योम *data);
	पूर्णांक (*sw_mode_config)(काष्ठा iio_dev *indio_dev);
	पूर्णांक (*reg_पढ़ो)(काष्ठा ad7606_state *st, अचिन्हित पूर्णांक addr);
	पूर्णांक (*reg_ग_लिखो)(काष्ठा ad7606_state *st,
				अचिन्हित पूर्णांक addr,
				अचिन्हित पूर्णांक val);
	पूर्णांक (*ग_लिखो_mask)(काष्ठा ad7606_state *st,
				 अचिन्हित पूर्णांक addr,
				 अचिन्हित दीर्घ mask,
				 अचिन्हित पूर्णांक val);
	u16 (*rd_wr_cmd)(पूर्णांक addr, अक्षर isWriteOp);
पूर्ण;

पूर्णांक ad7606_probe(काष्ठा device *dev, पूर्णांक irq, व्योम __iomem *base_address,
		 स्थिर अक्षर *name, अचिन्हित पूर्णांक id,
		 स्थिर काष्ठा ad7606_bus_ops *bops);

क्रमागत ad7606_supported_device_ids अणु
	ID_AD7605_4,
	ID_AD7606_8,
	ID_AD7606_6,
	ID_AD7606_4,
	ID_AD7606B,
	ID_AD7616,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य स्थिर काष्ठा dev_pm_ops ad7606_pm_ops;
#घोषणा AD7606_PM_OPS (&ad7606_pm_ops)
#अन्यथा
#घोषणा AD7606_PM_OPS शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* IIO_ADC_AD7606_H_ */
