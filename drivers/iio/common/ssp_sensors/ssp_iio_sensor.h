<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SSP_IIO_SENSOR_H__
#घोषणा __SSP_IIO_SENSOR_H__

#घोषणा SSP_CHANNEL_AG(_type, _mod, _index) \
अणु \
		.type = _type,\
		.modअगरied = 1,\
		.channel2 = _mod,\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ),\
		.scan_index = _index,\
		.scan_type = अणु\
			.sign = 's',\
			.realbits = 16,\
			.storagebits = 16,\
			.shअगरt = 0,\
			.endianness = IIO_LE,\
		पूर्ण,\
पूर्ण

/* It is defined here as it is a mixed बारtamp */
#घोषणा SSP_CHAN_TIMESTAMP(_si) अणु					\
	.type = IIO_TIMESTAMP,						\
	.channel = -1,							\
	.scan_index = _si,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 64,						\
		.storagebits = 64,					\
		पूर्ण,							\
पूर्ण

#घोषणा SSP_MS_PER_S			1000
#घोषणा SSP_INVERTED_SCALING_FACTOR	1000000U

#घोषणा SSP_FACTOR_WITH_MS \
	(SSP_INVERTED_SCALING_FACTOR * SSP_MS_PER_S)

पूर्णांक ssp_common_buffer_postenable(काष्ठा iio_dev *indio_dev);

पूर्णांक ssp_common_buffer_postdisable(काष्ठा iio_dev *indio_dev);

पूर्णांक ssp_common_process_data(काष्ठा iio_dev *indio_dev, व्योम *buf,
			    अचिन्हित पूर्णांक len, पूर्णांक64_t बारtamp);

/* Converts समय in ms to frequency */
अटल अंतरभूत व्योम ssp_convert_to_freq(u32 समय, पूर्णांक *पूर्णांकeger_part,
				       पूर्णांक *fractional)
अणु
	अगर (समय == 0) अणु
		*fractional = 0;
		*पूर्णांकeger_part = 0;
		वापस;
	पूर्ण

	*पूर्णांकeger_part = SSP_FACTOR_WITH_MS / समय;
	*fractional = *पूर्णांकeger_part % SSP_INVERTED_SCALING_FACTOR;
	*पूर्णांकeger_part = *पूर्णांकeger_part / SSP_INVERTED_SCALING_FACTOR;
पूर्ण

/* Converts frequency to समय in ms */
अटल अंतरभूत पूर्णांक ssp_convert_to_समय(पूर्णांक पूर्णांकeger_part, पूर्णांक fractional)
अणु
	u64 value;

	value = (u64)पूर्णांकeger_part * SSP_INVERTED_SCALING_FACTOR + fractional;
	अगर (value == 0)
		वापस 0;

	वापस भाग64_u64((u64)SSP_FACTOR_WITH_MS, value);
पूर्ण
#पूर्ण_अगर /* __SSP_IIO_SENSOR_H__ */
