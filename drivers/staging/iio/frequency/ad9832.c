<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD9832 SPI DDS driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <यंत्र/भाग64.h>

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "ad9832.h"

#समावेश "dds.h"

/* Registers */

#घोषणा AD9832_FREQ0LL		0x0
#घोषणा AD9832_FREQ0HL		0x1
#घोषणा AD9832_FREQ0LM		0x2
#घोषणा AD9832_FREQ0HM		0x3
#घोषणा AD9832_FREQ1LL		0x4
#घोषणा AD9832_FREQ1HL		0x5
#घोषणा AD9832_FREQ1LM		0x6
#घोषणा AD9832_FREQ1HM		0x7
#घोषणा AD9832_PHASE0L		0x8
#घोषणा AD9832_PHASE0H		0x9
#घोषणा AD9832_PHASE1L		0xA
#घोषणा AD9832_PHASE1H		0xB
#घोषणा AD9832_PHASE2L		0xC
#घोषणा AD9832_PHASE2H		0xD
#घोषणा AD9832_PHASE3L		0xE
#घोषणा AD9832_PHASE3H		0xF

#घोषणा AD9832_PHASE_SYM	0x10
#घोषणा AD9832_FREQ_SYM		0x11
#घोषणा AD9832_PINCTRL_EN	0x12
#घोषणा AD9832_OUTPUT_EN	0x13

/* Command Control Bits */

#घोषणा AD9832_CMD_PHA8BITSW	0x1
#घोषणा AD9832_CMD_PHA16BITSW	0x0
#घोषणा AD9832_CMD_FRE8BITSW	0x3
#घोषणा AD9832_CMD_FRE16BITSW	0x2
#घोषणा AD9832_CMD_FPSELECT	0x6
#घोषणा AD9832_CMD_SYNCSELSRC	0x8
#घोषणा AD9832_CMD_SLEEPRESCLR	0xC

#घोषणा AD9832_FREQ		BIT(11)
#घोषणा AD9832_PHASE(x)		(((x) & 3) << 9)
#घोषणा AD9832_SYNC		BIT(13)
#घोषणा AD9832_SELSRC		BIT(12)
#घोषणा AD9832_SLEEP		BIT(13)
#घोषणा AD9832_RESET		BIT(12)
#घोषणा AD9832_CLR		BIT(11)
#घोषणा CMD_SHIFT		12
#घोषणा ADD_SHIFT		8
#घोषणा AD9832_FREQ_BITS	32
#घोषणा AD9832_PHASE_BITS	12
#घोषणा RES_MASK(bits)		((1 << (bits)) - 1)

/**
 * काष्ठा ad9832_state - driver instance specअगरic data
 * @spi:		spi_device
 * @avdd:		supply regulator क्रम the analog section
 * @dvdd:		supply regulator क्रम the digital section
 * @mclk:		बाह्यal master घड़ी
 * @ctrl_fp:		cached frequency/phase control word
 * @ctrl_ss:		cached sync/selsrc control word
 * @ctrl_src:		cached sleep/reset/clr word
 * @xfer:		शेष spi transfer
 * @msg:		शेष spi message
 * @freq_xfer:		tuning word spi transfer
 * @freq_msg:		tuning word spi message
 * @phase_xfer:		tuning word spi transfer
 * @phase_msg:		tuning word spi message
 * @lock:		protect sensor state
 * @data:		spi transmit buffer
 * @phase_data:		tuning word spi transmit buffer
 * @freq_data:		tuning word spi transmit buffer
 */

काष्ठा ad9832_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*avdd;
	काष्ठा regulator		*dvdd;
	काष्ठा clk			*mclk;
	अचिन्हित लघु			ctrl_fp;
	अचिन्हित लघु			ctrl_ss;
	अचिन्हित लघु			ctrl_src;
	काष्ठा spi_transfer		xfer;
	काष्ठा spi_message		msg;
	काष्ठा spi_transfer		freq_xfer[4];
	काष्ठा spi_message		freq_msg;
	काष्ठा spi_transfer		phase_xfer[2];
	काष्ठा spi_message		phase_msg;
	काष्ठा mutex			lock;	/* protect sensor state */
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		__be16			freq_data[4]____cacheline_aligned;
		__be16			phase_data[2];
		__be16			data;
	पूर्ण;
पूर्ण;

अटल अचिन्हित दीर्घ ad9832_calc_freqreg(अचिन्हित दीर्घ mclk, अचिन्हित दीर्घ fout)
अणु
	अचिन्हित दीर्घ दीर्घ freqreg = (u64)fout *
				     (u64)((u64)1L << AD9832_FREQ_BITS);
	करो_भाग(freqreg, mclk);
	वापस freqreg;
पूर्ण

अटल पूर्णांक ad9832_ग_लिखो_frequency(काष्ठा ad9832_state *st,
				  अचिन्हित पूर्णांक addr, अचिन्हित दीर्घ fout)
अणु
	अचिन्हित दीर्घ regval;

	अगर (fout > (clk_get_rate(st->mclk) / 2))
		वापस -EINVAL;

	regval = ad9832_calc_freqreg(clk_get_rate(st->mclk), fout);

	st->freq_data[0] = cpu_to_be16((AD9832_CMD_FRE8BITSW << CMD_SHIFT) |
					(addr << ADD_SHIFT) |
					((regval >> 24) & 0xFF));
	st->freq_data[1] = cpu_to_be16((AD9832_CMD_FRE16BITSW << CMD_SHIFT) |
					((addr - 1) << ADD_SHIFT) |
					((regval >> 16) & 0xFF));
	st->freq_data[2] = cpu_to_be16((AD9832_CMD_FRE8BITSW << CMD_SHIFT) |
					((addr - 2) << ADD_SHIFT) |
					((regval >> 8) & 0xFF));
	st->freq_data[3] = cpu_to_be16((AD9832_CMD_FRE16BITSW << CMD_SHIFT) |
					((addr - 3) << ADD_SHIFT) |
					((regval >> 0) & 0xFF));

	वापस spi_sync(st->spi, &st->freq_msg);
पूर्ण

अटल पूर्णांक ad9832_ग_लिखो_phase(काष्ठा ad9832_state *st,
			      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ phase)
अणु
	अगर (phase > BIT(AD9832_PHASE_BITS))
		वापस -EINVAL;

	st->phase_data[0] = cpu_to_be16((AD9832_CMD_PHA8BITSW << CMD_SHIFT) |
					(addr << ADD_SHIFT) |
					((phase >> 8) & 0xFF));
	st->phase_data[1] = cpu_to_be16((AD9832_CMD_PHA16BITSW << CMD_SHIFT) |
					((addr - 1) << ADD_SHIFT) |
					(phase & 0xFF));

	वापस spi_sync(st->spi, &st->phase_msg);
पूर्ण

अटल sमाप_प्रकार ad9832_ग_लिखो(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad9832_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret;
	अचिन्हित दीर्घ val;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		जाओ error_ret;

	mutex_lock(&st->lock);
	चयन ((u32)this_attr->address) अणु
	हाल AD9832_FREQ0HM:
	हाल AD9832_FREQ1HM:
		ret = ad9832_ग_लिखो_frequency(st, this_attr->address, val);
		अवरोध;
	हाल AD9832_PHASE0H:
	हाल AD9832_PHASE1H:
	हाल AD9832_PHASE2H:
	हाल AD9832_PHASE3H:
		ret = ad9832_ग_लिखो_phase(st, this_attr->address, val);
		अवरोध;
	हाल AD9832_PINCTRL_EN:
		अगर (val)
			st->ctrl_ss &= ~AD9832_SELSRC;
		अन्यथा
			st->ctrl_ss |= AD9832_SELSRC;
		st->data = cpu_to_be16((AD9832_CMD_SYNCSELSRC << CMD_SHIFT) |
					st->ctrl_ss);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	हाल AD9832_FREQ_SYM:
		अगर (val == 1) अणु
			st->ctrl_fp |= AD9832_FREQ;
		पूर्ण अन्यथा अगर (val == 0) अणु
			st->ctrl_fp &= ~AD9832_FREQ;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		st->data = cpu_to_be16((AD9832_CMD_FPSELECT << CMD_SHIFT) |
					st->ctrl_fp);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	हाल AD9832_PHASE_SYM:
		अगर (val > 3) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		st->ctrl_fp &= ~AD9832_PHASE(3);
		st->ctrl_fp |= AD9832_PHASE(val);

		st->data = cpu_to_be16((AD9832_CMD_FPSELECT << CMD_SHIFT) |
					st->ctrl_fp);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	हाल AD9832_OUTPUT_EN:
		अगर (val)
			st->ctrl_src &= ~(AD9832_RESET | AD9832_SLEEP |
					AD9832_CLR);
		अन्यथा
			st->ctrl_src |= AD9832_RESET;

		st->data = cpu_to_be16((AD9832_CMD_SLEEPRESCLR << CMD_SHIFT) |
					st->ctrl_src);
		ret = spi_sync(st->spi, &st->msg);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&st->lock);

error_ret:
	वापस ret ? ret : len;
पूर्ण

/*
 * see dds.h क्रम further inक्रमmation
 */

अटल IIO_DEV_ATTR_FREQ(0, 0, 0200, शून्य, ad9832_ग_लिखो, AD9832_FREQ0HM);
अटल IIO_DEV_ATTR_FREQ(0, 1, 0200, शून्य, ad9832_ग_लिखो, AD9832_FREQ1HM);
अटल IIO_DEV_ATTR_FREQSYMBOL(0, 0200, शून्य, ad9832_ग_लिखो, AD9832_FREQ_SYM);
अटल IIO_CONST_ATTR_FREQ_SCALE(0, "1"); /* 1Hz */

अटल IIO_DEV_ATTR_PHASE(0, 0, 0200, शून्य, ad9832_ग_लिखो, AD9832_PHASE0H);
अटल IIO_DEV_ATTR_PHASE(0, 1, 0200, शून्य, ad9832_ग_लिखो, AD9832_PHASE1H);
अटल IIO_DEV_ATTR_PHASE(0, 2, 0200, शून्य, ad9832_ग_लिखो, AD9832_PHASE2H);
अटल IIO_DEV_ATTR_PHASE(0, 3, 0200, शून्य, ad9832_ग_लिखो, AD9832_PHASE3H);
अटल IIO_DEV_ATTR_PHASESYMBOL(0, 0200, शून्य,
				ad9832_ग_लिखो, AD9832_PHASE_SYM);
अटल IIO_CONST_ATTR_PHASE_SCALE(0, "0.0015339808"); /* 2PI/2^12 rad*/

अटल IIO_DEV_ATTR_PINCONTROL_EN(0, 0200, शून्य,
				ad9832_ग_लिखो, AD9832_PINCTRL_EN);
अटल IIO_DEV_ATTR_OUT_ENABLE(0, 0200, शून्य,
				ad9832_ग_लिखो, AD9832_OUTPUT_EN);

अटल काष्ठा attribute *ad9832_attributes[] = अणु
	&iio_dev_attr_out_altvoltage0_frequency0.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequency1.dev_attr.attr,
	&iio_स्थिर_attr_out_altvoltage0_frequency_scale.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase0.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase1.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase2.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phase3.dev_attr.attr,
	&iio_स्थिर_attr_out_altvoltage0_phase_scale.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_pincontrol_en.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequencysymbol.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_phasesymbol.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_out_enable.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad9832_attribute_group = अणु
	.attrs = ad9832_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad9832_info = अणु
	.attrs = &ad9832_attribute_group,
पूर्ण;

अटल पूर्णांक ad9832_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad9832_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad9832_state *st;
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_dbg(&spi->dev, "no platform data?\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);

	st->avdd = devm_regulator_get(&spi->dev, "avdd");
	अगर (IS_ERR(st->avdd))
		वापस PTR_ERR(st->avdd);

	ret = regulator_enable(st->avdd);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified AVDD supply\n");
		वापस ret;
	पूर्ण

	st->dvdd = devm_regulator_get(&spi->dev, "dvdd");
	अगर (IS_ERR(st->dvdd)) अणु
		ret = PTR_ERR(st->dvdd);
		जाओ error_disable_avdd;
	पूर्ण

	ret = regulator_enable(st->dvdd);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified DVDD supply\n");
		जाओ error_disable_avdd;
	पूर्ण

	st->mclk = devm_clk_get(&spi->dev, "mclk");
	अगर (IS_ERR(st->mclk)) अणु
		ret = PTR_ERR(st->mclk);
		जाओ error_disable_dvdd;
	पूर्ण

	ret = clk_prepare_enable(st->mclk);
	अगर (ret < 0)
		जाओ error_disable_dvdd;

	st->spi = spi;
	mutex_init(&st->lock);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad9832_info;
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
	st->freq_xfer[1].cs_change = 1;
	st->freq_xfer[2].tx_buf = &st->freq_data[2];
	st->freq_xfer[2].len = 2;
	st->freq_xfer[2].cs_change = 1;
	st->freq_xfer[3].tx_buf = &st->freq_data[3];
	st->freq_xfer[3].len = 2;

	spi_message_init(&st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[0], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[1], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[2], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[3], &st->freq_msg);

	st->phase_xfer[0].tx_buf = &st->phase_data[0];
	st->phase_xfer[0].len = 2;
	st->phase_xfer[0].cs_change = 1;
	st->phase_xfer[1].tx_buf = &st->phase_data[1];
	st->phase_xfer[1].len = 2;

	spi_message_init(&st->phase_msg);
	spi_message_add_tail(&st->phase_xfer[0], &st->phase_msg);
	spi_message_add_tail(&st->phase_xfer[1], &st->phase_msg);

	st->ctrl_src = AD9832_SLEEP | AD9832_RESET | AD9832_CLR;
	st->data = cpu_to_be16((AD9832_CMD_SLEEPRESCLR << CMD_SHIFT) |
					st->ctrl_src);
	ret = spi_sync(st->spi, &st->msg);
	अगर (ret) अणु
		dev_err(&spi->dev, "device init failed\n");
		जाओ error_unprepare_mclk;
	पूर्ण

	ret = ad9832_ग_लिखो_frequency(st, AD9832_FREQ0HM, pdata->freq0);
	अगर (ret)
		जाओ error_unprepare_mclk;

	ret = ad9832_ग_लिखो_frequency(st, AD9832_FREQ1HM, pdata->freq1);
	अगर (ret)
		जाओ error_unprepare_mclk;

	ret = ad9832_ग_लिखो_phase(st, AD9832_PHASE0H, pdata->phase0);
	अगर (ret)
		जाओ error_unprepare_mclk;

	ret = ad9832_ग_लिखो_phase(st, AD9832_PHASE1H, pdata->phase1);
	अगर (ret)
		जाओ error_unprepare_mclk;

	ret = ad9832_ग_लिखो_phase(st, AD9832_PHASE2H, pdata->phase2);
	अगर (ret)
		जाओ error_unprepare_mclk;

	ret = ad9832_ग_लिखो_phase(st, AD9832_PHASE3H, pdata->phase3);
	अगर (ret)
		जाओ error_unprepare_mclk;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_unprepare_mclk;

	वापस 0;

error_unprepare_mclk:
	clk_disable_unprepare(st->mclk);
error_disable_dvdd:
	regulator_disable(st->dvdd);
error_disable_avdd:
	regulator_disable(st->avdd);

	वापस ret;
पूर्ण

अटल पूर्णांक ad9832_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad9832_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	clk_disable_unprepare(st->mclk);
	regulator_disable(st->dvdd);
	regulator_disable(st->avdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad9832_id[] = अणु
	अणु"ad9832", 0पूर्ण,
	अणु"ad9835", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad9832_id);

अटल काष्ठा spi_driver ad9832_driver = अणु
	.driver = अणु
		.name	= "ad9832",
	पूर्ण,
	.probe		= ad9832_probe,
	.हटाओ		= ad9832_हटाओ,
	.id_table	= ad9832_id,
पूर्ण;
module_spi_driver(ad9832_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD9832/AD9835 DDS");
MODULE_LICENSE("GPL v2");
