<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Support code क्रम Analog Devices Sigma-Delta ADCs
 *
 * Copyright 2012 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */
#अगर_अघोषित __AD_SIGMA_DELTA_H__
#घोषणा __AD_SIGMA_DELTA_H__

क्रमागत ad_sigma_delta_mode अणु
	AD_SD_MODE_CONTINUOUS = 0,
	AD_SD_MODE_SINGLE = 1,
	AD_SD_MODE_IDLE = 2,
	AD_SD_MODE_POWERDOWN = 3,
पूर्ण;

/**
 * काष्ठा ad_sigma_delta_calib_data - Calibration data क्रम Sigma Delta devices
 * @mode: Calibration mode.
 * @channel: Calibration channel.
 */
काष्ठा ad_sd_calib_data अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक channel;
पूर्ण;

काष्ठा ad_sigma_delta;
काष्ठा iio_dev;

/**
 * काष्ठा ad_sigma_delta_info - Sigma Delta driver specअगरic callbacks and options
 * @set_channel: Will be called to select the current channel, may be शून्य.
 * @set_mode: Will be called to select the current mode, may be शून्य.
 * @postprocess_sample: Is called क्रम each sampled data word, can be used to
 *		modअगरy or drop the sample data, it, may be शून्य.
 * @has_रेजिस्टरs: true अगर the device has writable and पढ़ोable रेजिस्टरs, false
 *		अगर there is just one पढ़ो-only sample data shअगरt रेजिस्टर.
 * @addr_shअगरt: Shअगरt of the रेजिस्टर address in the communications रेजिस्टर.
 * @पढ़ो_mask: Mask क्रम the communications रेजिस्टर having the पढ़ो bit set.
 * @data_reg: Address of the data रेजिस्टर, अगर 0 the शेष address of 0x3 will
 *   be used.
 * @irq_flags: flags क्रम the पूर्णांकerrupt used by the triggered buffer
 */
काष्ठा ad_sigma_delta_info अणु
	पूर्णांक (*set_channel)(काष्ठा ad_sigma_delta *, अचिन्हित पूर्णांक channel);
	पूर्णांक (*set_mode)(काष्ठा ad_sigma_delta *, क्रमागत ad_sigma_delta_mode mode);
	पूर्णांक (*postprocess_sample)(काष्ठा ad_sigma_delta *, अचिन्हित पूर्णांक raw_sample);
	bool has_रेजिस्टरs;
	अचिन्हित पूर्णांक addr_shअगरt;
	अचिन्हित पूर्णांक पढ़ो_mask;
	अचिन्हित पूर्णांक data_reg;
	अचिन्हित दीर्घ irq_flags;
पूर्ण;

/**
 * काष्ठा ad_sigma_delta - Sigma Delta device काष्ठा
 * @spi: The spi device associated with the Sigma Delta device.
 * @trig: The IIO trigger associated with the Sigma Delta device.
 *
 * Most of the fields are निजी to the sigma delta library code and should not
 * be accessed by inभागidual drivers.
 */
काष्ठा ad_sigma_delta अणु
	काष्ठा spi_device	*spi;
	काष्ठा iio_trigger	*trig;

/* निजी: */
	काष्ठा completion	completion;
	bool			irq_dis;

	bool			bus_locked;
	bool			keep_cs_निश्चितed;

	uपूर्णांक8_t			comm;

	स्थिर काष्ठा ad_sigma_delta_info *info;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * 'tx_buf' is up to 32 bits.
	 * 'rx_buf' is up to 32 bits per sample + 64 bit बारtamp,
	 * rounded to 16 bytes to take पूर्णांकo account padding.
	 */
	uपूर्णांक8_t				tx_buf[4] ____cacheline_aligned;
	uपूर्णांक8_t				rx_buf[16] __aligned(8);
पूर्ण;

अटल अंतरभूत पूर्णांक ad_sigma_delta_set_channel(काष्ठा ad_sigma_delta *sd,
	अचिन्हित पूर्णांक channel)
अणु
	अगर (sd->info->set_channel)
		वापस sd->info->set_channel(sd, channel);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ad_sigma_delta_set_mode(काष्ठा ad_sigma_delta *sd,
	अचिन्हित पूर्णांक mode)
अणु
	अगर (sd->info->set_mode)
		वापस sd->info->set_mode(sd, mode);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ad_sigma_delta_postprocess_sample(काष्ठा ad_sigma_delta *sd,
	अचिन्हित पूर्णांक raw_sample)
अणु
	अगर (sd->info->postprocess_sample)
		वापस sd->info->postprocess_sample(sd, raw_sample);

	वापस 0;
पूर्ण

व्योम ad_sd_set_comm(काष्ठा ad_sigma_delta *sigma_delta, uपूर्णांक8_t comm);
पूर्णांक ad_sd_ग_लिखो_reg(काष्ठा ad_sigma_delta *sigma_delta, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक val);
पूर्णांक ad_sd_पढ़ो_reg(काष्ठा ad_sigma_delta *sigma_delta, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक *val);

पूर्णांक ad_sd_reset(काष्ठा ad_sigma_delta *sigma_delta,
	अचिन्हित पूर्णांक reset_length);

पूर्णांक ad_sigma_delta_single_conversion(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val);
पूर्णांक ad_sd_calibrate(काष्ठा ad_sigma_delta *sigma_delta,
	अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक channel);
पूर्णांक ad_sd_calibrate_all(काष्ठा ad_sigma_delta *sigma_delta,
	स्थिर काष्ठा ad_sd_calib_data *cd, अचिन्हित पूर्णांक n);
पूर्णांक ad_sd_init(काष्ठा ad_sigma_delta *sigma_delta, काष्ठा iio_dev *indio_dev,
	काष्ठा spi_device *spi, स्थिर काष्ठा ad_sigma_delta_info *info);

पूर्णांक ad_sd_setup_buffer_and_trigger(काष्ठा iio_dev *indio_dev);
व्योम ad_sd_cleanup_buffer_and_trigger(काष्ठा iio_dev *indio_dev);

पूर्णांक ad_sd_validate_trigger(काष्ठा iio_dev *indio_dev, काष्ठा iio_trigger *trig);

#पूर्ण_अगर
