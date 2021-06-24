<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD9833/AD9834/AD9837/AD9838 SPI DDS driver
 *
 * Copyright 2010-2011 Analog Devices Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश "dds.h"

#समावेश "ad9834.h"

/* Registers */

#घोषणा AD9834_REG_CMD		0
#घोषणा AD9834_REG_FREQ0	BIT(14)
#घोषणा AD9834_REG_FREQ1	BIT(15)
#घोषणा AD9834_REG_PHASE0	(BIT(15) | BIT(14))
#घोषणा AD9834_REG_PHASE1	(BIT(15) | BIT(14) | BIT(13))

/* Command Control Bits */

#घोषणा AD9834_B28		BIT(13)
#घोषणा AD9834_HLB		BIT(12)
#घोषणा AD9834_FSEL		BIT(11)
#घोषणा AD9834_PSEL		BIT(10)
#घोषणा AD9834_PIN_SW		BIT(9)
#घोषणा AD9834_RESET		BIT(8)
#घोषणा AD9834_SLEEP1		BIT(7)
#घोषणा AD9834_SLEEP12		BIT(6)
#घोषणा AD9834_OPBITEN		BIT(5)
#घोषणा AD9834_SIGN_PIB		BIT(4)
#घोषणा AD9834_DIV2		BIT(3)
#घोषणा AD9834_MODE		BIT(1)

#घोषणा AD9834_FREQ_BITS	28
#घोषणा AD9834_PHASE_BITS	12

#घोषणा RES_MASK(bits)	(BIT(bits) - 1)

/**
 * काष्ठा ad9834_state - driver instance specअगरic data
 * @spi:		spi_device
 * @mclk:		बाह्यal master घड़ी
 * @control:		cached control word
 * @xfer:		शेष spi transfer
 * @msg:		शेष spi message
 * @freq_xfer:		tuning word spi transfer
 * @freq_msg:		tuning word spi message
 * @lock:		protect sensor state
 * @data:		spi transmit buffer
 * @freq_data:		tuning word spi transmit buffer
 */

काष्ठा ad9834_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा clk			*mclk;
	अचिन्हित लघु			control;
	अचिन्हित लघु			devid;
	काष्ठा spi_transfer		xfer;
	काष्ठा spi_message		msg;
	काष्ठा spi_transfer		freq_xfer[2];
	काष्ठा spi_message		freq_msg;
	काष्ठा mutex                    lock;   /* protect sensor state */

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be16				data ____cacheline_aligned;
	__be16				freq_data[2];
पूर्ण;

/**
 * ad9834_supported_device_ids:
 */

क्रमागत ad9834_supported_device_ids अणु
	ID_AD9833,
	ID_AD9834,
	ID_AD9837,
	ID_AD9838,
पूर्ण;

अटल अचिन्हित पूर्णांक ad9834_calc_freqreg(अचिन्हित दीर्घ mclk, अचिन्हित दीर्घ fout)
अणु
	अचिन्हित दीर्घ दीर्घ freqreg = (u64)fout * (u64)BIT(AD9834_FREQ_BITS);

	करो_भाग(freqreg, mclk);
	वापस freqreg;
पूर्ण

अटल पूर्णांक ad9834_ग_लिखो_frequency(काष्ठा ad9834_state *st,
				  अचिन्हित दीर्घ addr, अचिन्हित दीर्घ fout)
अणु
	अचिन्हित दीर्घ clk_freq;
	अचिन्हित दीर्घ regval;

	clk_freq = clk_get_rate(st->mclk);

	अगर (fout > (clk_freq / 2))
		वापस -EINVAL;

	regval = ad9834_calc_freqreg(clk_freq, fout);

	st->freq_data[0] = cpu_to_be16(addr | (regval &
				       RES_MASK(AD9834_FREQ_BITS / 2)));
	st->freq_data[1] = cpu_to_be16(addr | ((regval >>
				       (AD9834_FREQ_BITS / 2)) &
				       RES_MASK(AD9834_FREQ_BITS / 2)));

	वापस spi_sync(st->spi, &st->freq_msg);
पूर्ण

अटल पूर्णांक ad9834_ग_लिखो_phase(काष्ठा ad9834_state *st,
			      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ phase)
अणु
	अगर (phase > BIT(AD9834_PHASE_BITS))
		वापस -EINVAL;
	st->data = cpu_to_be16(addr | phase);

	वापस spi_sync(st->spi, &st->msg);
पूर्ण

अटल sमाप_प्रकार ad9834_ग_लिखो(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf,
			    माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad9834_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret;
	अचिन्हित दीर्घ val;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);
	चयन ((u32)this_attr->address) अणु
	हाल AD9834_REG_FREQ0:
	हाल AD9834_REG_FREQ1:
		ret = ad9834_ग_लिखो_frequency(st, this_attr->address, val);
		अवरोध;
	हाल AD9834_REG_PHASE0:
	हाल AD9834_REG_PHASE1:
		ret = ad9834_ग_लिखो_phase(st, this_attr->address, val);
		अवरोध;
	हाल AD9834_OPBITEN:
		अगर (st->control & AD9834_MODE) अणु
			ret = -EINVAL;  /* AD9843 reserved mode */
			अवरोध;
		पूर्ण

		अगर (val)
			st->control |= AD9834_OPBITEN;
		अन्यथा
			st->control &= ~AD9834_OPBITEN;

		st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	हाल AD9834_PIN_SW:
		अगर (val)
			st->control |= AD9834_PIN_SW;
		अन्यथा
			st->control &= ~AD9834_PIN_SW;
		st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	हाल AD9834_FSEL:
	हाल AD9834_PSEL:
		अगर (!val) अणु
			st->control &= ~(this_attr->address | AD9834_PIN_SW);
		पूर्ण अन्यथा अगर (val == 1) अणु
			st->control |= this_attr->address;
			st->control &= ~AD9834_PIN_SW;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	हाल AD9834_RESET:
		अगर (val)
			st->control &= ~AD9834_RESET;
		अन्यथा
			st->control |= AD9834_RESET;

		st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad9834_store_wavetype(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad9834_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret = 0;
	bool is_ad9833_7 = (st->devid == ID_AD9833) || (st->devid == ID_AD9837);

	mutex_lock(&st->lock);

	चयन ((u32)this_attr->address) अणु
	हाल 0:
		अगर (sysfs_streq(buf, "sine")) अणु
			st->control &= ~AD9834_MODE;
			अगर (is_ad9833_7)
				st->control &= ~AD9834_OPBITEN;
		पूर्ण अन्यथा अगर (sysfs_streq(buf, "triangle")) अणु
			अगर (is_ad9833_7) अणु
				st->control &= ~AD9834_OPBITEN;
				st->control |= AD9834_MODE;
			पूर्ण अन्यथा अगर (st->control & AD9834_OPBITEN) अणु
				ret = -EINVAL;	/* AD9843 reserved mode */
			पूर्ण अन्यथा अणु
				st->control |= AD9834_MODE;
			पूर्ण
		पूर्ण अन्यथा अगर (is_ad9833_7 && sysfs_streq(buf, "square")) अणु
			st->control &= ~AD9834_MODE;
			st->control |= AD9834_OPBITEN;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण

		अवरोध;
	हाल 1:
		अगर (sysfs_streq(buf, "square") &&
		    !(st->control & AD9834_MODE)) अणु
			st->control &= ~AD9834_MODE;
			st->control |= AD9834_OPBITEN;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
		ret = spi_sync(st->spi, &st->msg);
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल
sमाप_प्रकार ad9834_show_out0_wavetype_available(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad9834_state *st = iio_priv(indio_dev);
	अक्षर *str;

	अगर (st->devid == ID_AD9833 || st->devid == ID_AD9837)
		str = "sine triangle square";
	अन्यथा अगर (st->control & AD9834_OPBITEN)
		str = "sine";
	अन्यथा
		str = "sine triangle";

	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल IIO_DEVICE_ATTR(out_altvoltage0_out0_wavetype_available, 0444,
		       ad9834_show_out0_wavetype_available, शून्य, 0);

अटल
sमाप_प्रकार ad9834_show_out1_wavetype_available(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad9834_state *st = iio_priv(indio_dev);
	अक्षर *str;

	अगर (st->control & AD9834_MODE)
		str = "";
	अन्यथा
		str = "square";

	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल IIO_DEVICE_ATTR(out_altvoltage0_out1_wavetype_available, 0444,
		       ad9834_show_out1_wavetype_available, शून्य, 0);

/**
 * see dds.h क्रम further inक्रमmation
 */

अटल IIO_DEV_ATTR_FREQ(0, 0, 0200, शून्य, ad9834_ग_लिखो, AD9834_REG_FREQ0);
अटल IIO_DEV_ATTR_FREQ(0, 1, 0200, शून्य, ad9834_ग_लिखो, AD9834_REG_FREQ1);
अटल IIO_DEV_ATTR_FREQSYMBOL(0, 0200, शून्य, ad9834_ग_लिखो, AD9834_FSEL);
अटल IIO_CONST_ATTR_FREQ_SCALE(0, "1"); /* 1Hz */

अटल IIO_DEV_ATTR_PHASE(0, 0, 0200, शून्य, ad9834_ग_लिखो, AD9834_REG_PHASE0);
अटल IIO_DEV_ATTR_PHASE(0, 1, 0200, शून्य, ad9834_ग_लिखो, AD9834_REG_PHASE1);
अटल IIO_DEV_ATTR_PHASESYMBOL(0, 0200, शून्य, ad9834_ग_लिखो, AD9834_PSEL);
अटल IIO_CONST_ATTR_PHASE_SCALE(0, "0.0015339808"); /* 2PI/2^12 rad*/

अटल IIO_DEV_ATTR_PINCONTROL_EN(0, 0200, शून्य,
	ad9834_ग_लिखो, AD9834_PIN_SW);
अटल IIO_DEV_ATTR_OUT_ENABLE(0, 0200, शून्य, ad9834_ग_लिखो, AD9834_RESET);
अटल IIO_DEV_ATTR_OUTY_ENABLE(0, 1, 0200, शून्य,
	ad9834_ग_लिखो, AD9834_OPBITEN);
अटल IIO_DEV_ATTR_OUT_WAVETYPE(0, 0, ad9834_store_wavetype, 0);
अटल IIO_DEV_ATTR_OUT_WAVETYPE(0, 1, ad9834_store_wavetype, 1);

अटल काष्ठा attribute *ad9834_attributes[] = अणु
	&iio_dev_attr_out_altvoltage0_frequency0.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequency1.dev_attr.attr,
	&iio_स्थिर_attr_out_altvoltage0_frequency_scale.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase0.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase1.dev_attr.attr,
	&iio_स्थिर_attr_out_altvoltage0_phase_scale.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_pincontrol_en.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequencysymbol.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phasesymbol.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out_enable.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out1_enable.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out0_wavetype.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out1_wavetype.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out0_wavetype_available.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out1_wavetype_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ad9833_attributes[] = अणु
	&iio_dev_attr_out_altvoltage0_frequency0.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequency1.dev_attr.attr,
	&iio_स्थिर_attr_out_altvoltage0_frequency_scale.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase0.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase1.dev_attr.attr,
	&iio_स्थिर_attr_out_altvoltage0_phase_scale.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequencysymbol.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phasesymbol.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out_enable.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out0_wavetype.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out0_wavetype_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad9834_attribute_group = अणु
	.attrs = ad9834_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad9833_attribute_group = अणु
	.attrs = ad9833_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad9834_info = अणु
	.attrs = &ad9834_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad9833_info = अणु
	.attrs = &ad9833_attribute_group,
पूर्ण;

अटल व्योम ad9834_disable_reg(व्योम *data)
अणु
	काष्ठा regulator *reg = data;

	regulator_disable(reg);
पूर्ण

अटल व्योम ad9834_disable_clk(व्योम *data)
अणु
	काष्ठा clk *clk = data;

	clk_disable_unprepare(clk);
पूर्ण

अटल पूर्णांक ad9834_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad9834_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regulator *reg;
	पूर्णांक ret;

	reg = devm_regulator_get(&spi->dev, "avdd");
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	ret = regulator_enable(reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified AVDD supply\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&spi->dev, ad9834_disable_reg, reg);
	अगर (ret)
		वापस ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev) अणु
		ret = -ENOMEM;
		वापस ret;
	पूर्ण
	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->mclk = devm_clk_get(&spi->dev, शून्य);
	अगर (IS_ERR(st->mclk)) अणु
		ret = PTR_ERR(st->mclk);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(st->mclk);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable master clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&spi->dev, ad9834_disable_clk, st->mclk);
	अगर (ret)
		वापस ret;

	st->spi = spi;
	st->devid = spi_get_device_id(spi)->driver_data;
	indio_dev->name = spi_get_device_id(spi)->name;
	चयन (st->devid) अणु
	हाल ID_AD9833:
	हाल ID_AD9837:
		indio_dev->info = &ad9833_info;
		अवरोध;
	शेष:
		indio_dev->info = &ad9834_info;
		अवरोध;
	पूर्ण
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* Setup शेष messages */

	st->xfer.tx_buf = &st->data;
	st->xfer.len = 2;

	spi_message_init(&st->msg);
	spi_message_add_tail(&st->xfer, &st->msg);

	st->freq_xfer[0].tx_buf = &st->freq_data[0];
	st->freq_xfer[0].len = 2;
	st->freq_xfer[0].cs_change = 1;
	st->freq_xfer[1].tx_buf = &st->freq_data[1];
	st->freq_xfer[1].len = 2;

	spi_message_init(&st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[0], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[1], &st->freq_msg);

	st->control = AD9834_B28 | AD9834_RESET;
	st->control |= AD9834_DIV2;

	अगर (st->devid == ID_AD9834)
		st->control |= AD9834_SIGN_PIB;

	st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
	ret = spi_sync(st->spi, &st->msg);
	अगर (ret) अणु
		dev_err(&spi->dev, "device init failed\n");
		वापस ret;
	पूर्ण

	ret = ad9834_ग_लिखो_frequency(st, AD9834_REG_FREQ0, 1000000);
	अगर (ret)
		वापस ret;

	ret = ad9834_ग_लिखो_frequency(st, AD9834_REG_FREQ1, 5000000);
	अगर (ret)
		वापस ret;

	ret = ad9834_ग_लिखो_phase(st, AD9834_REG_PHASE0, 512);
	अगर (ret)
		वापस ret;

	ret = ad9834_ग_लिखो_phase(st, AD9834_REG_PHASE1, 1024);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad9834_id[] = अणु
	अणु"ad9833", ID_AD9833पूर्ण,
	अणु"ad9834", ID_AD9834पूर्ण,
	अणु"ad9837", ID_AD9837पूर्ण,
	अणु"ad9838", ID_AD9838पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad9834_id);

अटल स्थिर काष्ठा of_device_id ad9834_of_match[] = अणु
	अणु.compatible = "adi,ad9833"पूर्ण,
	अणु.compatible = "adi,ad9834"पूर्ण,
	अणु.compatible = "adi,ad9837"पूर्ण,
	अणु.compatible = "adi,ad9838"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ad9834_of_match);

अटल काष्ठा spi_driver ad9834_driver = अणु
	.driver = अणु
		.name	= "ad9834",
		.of_match_table = ad9834_of_match
	पूर्ण,
	.probe		= ad9834_probe,
	.id_table	= ad9834_id,
पूर्ण;
module_spi_driver(ad9834_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD9833/AD9834/AD9837/AD9838 DDS");
MODULE_LICENSE("GPL v2");
