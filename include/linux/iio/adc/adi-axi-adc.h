<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Analog Devices Generic AXI ADC IP core driver/library
 * Link: https://wiki.analog.com/resources/fpga/करोcs/axi_adc_ip
 *
 * Copyright 2012-2020 Analog Devices Inc.
 */
#अगर_अघोषित __ADI_AXI_ADC_H__
#घोषणा __ADI_AXI_ADC_H__

काष्ठा device;
काष्ठा iio_chan_spec;

/**
 * काष्ठा adi_axi_adc_chip_info - Chip specअगरic inक्रमmation
 * @name		Chip name
 * @id			Chip ID (usually product ID)
 * @channels		Channel specअगरications of type @काष्ठा iio_chan_spec
 * @num_channels	Number of @channels
 * @scale_table		Supported scales by the chip; tuples of 2 पूर्णांकs
 * @num_scales		Number of scales in the table
 * @max_rate		Maximum sampling rate supported by the device
 */
काष्ठा adi_axi_adc_chip_info अणु
	स्थिर अक्षर			*name;
	अचिन्हित पूर्णांक			id;

	स्थिर काष्ठा iio_chan_spec	*channels;
	अचिन्हित पूर्णांक			num_channels;

	स्थिर अचिन्हित पूर्णांक		(*scale_table)[2];
	पूर्णांक				num_scales;

	अचिन्हित दीर्घ			max_rate;
पूर्ण;

/**
 * काष्ठा adi_axi_adc_conv - data of the ADC attached to the AXI ADC
 * @chip_info		chip info details क्रम the client ADC
 * @preenable_setup	op to run in the client beक्रमe enabling the AXI ADC
 * @reg_access		IIO debugfs_reg_access hook क्रम the client ADC
 * @पढ़ो_raw		IIO पढ़ो_raw hook क्रम the client ADC
 * @ग_लिखो_raw		IIO ग_लिखो_raw hook क्रम the client ADC
 */
काष्ठा adi_axi_adc_conv अणु
	स्थिर काष्ठा adi_axi_adc_chip_info		*chip_info;

	पूर्णांक (*preenable_setup)(काष्ठा adi_axi_adc_conv *conv);
	पूर्णांक (*reg_access)(काष्ठा adi_axi_adc_conv *conv, अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval);
	पूर्णांक (*पढ़ो_raw)(काष्ठा adi_axi_adc_conv *conv,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask);
	पूर्णांक (*ग_लिखो_raw)(काष्ठा adi_axi_adc_conv *conv,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 पूर्णांक val, पूर्णांक val2, दीर्घ mask);
पूर्ण;

काष्ठा adi_axi_adc_conv *devm_adi_axi_adc_conv_रेजिस्टर(काष्ठा device *dev,
							माप_प्रकार माप_priv);

व्योम *adi_axi_adc_conv_priv(काष्ठा adi_axi_adc_conv *conv);

#पूर्ण_अगर
