<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Microchip MCP3911, Two-channel Analog Front End
 *
 * Copyright (C) 2018 Marcus Folkesson <marcus.folkesson@gmail.com>
 * Copyright (C) 2018 Kent Gustavsson <kent@minoris.se>
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#घोषणा MCP3911_REG_CHANNEL0		0x00
#घोषणा MCP3911_REG_CHANNEL1		0x03
#घोषणा MCP3911_REG_MOD			0x06
#घोषणा MCP3911_REG_PHASE		0x07
#घोषणा MCP3911_REG_GAIN		0x09

#घोषणा MCP3911_REG_STATUSCOM		0x0a
#घोषणा MCP3911_STATUSCOM_CH1_24WIDTH	BIT(4)
#घोषणा MCP3911_STATUSCOM_CH0_24WIDTH	BIT(3)
#घोषणा MCP3911_STATUSCOM_EN_OFFCAL	BIT(2)
#घोषणा MCP3911_STATUSCOM_EN_GAINCAL	BIT(1)

#घोषणा MCP3911_REG_CONFIG		0x0c
#घोषणा MCP3911_CONFIG_CLKEXT		BIT(1)
#घोषणा MCP3911_CONFIG_VREFEXT		BIT(2)

#घोषणा MCP3911_REG_OFFCAL_CH0		0x0e
#घोषणा MCP3911_REG_GAINCAL_CH0		0x11
#घोषणा MCP3911_REG_OFFCAL_CH1		0x14
#घोषणा MCP3911_REG_GAINCAL_CH1		0x17
#घोषणा MCP3911_REG_VREFCAL		0x1a

#घोषणा MCP3911_CHANNEL(x)		(MCP3911_REG_CHANNEL0 + x * 3)
#घोषणा MCP3911_OFFCAL(x)		(MCP3911_REG_OFFCAL_CH0 + x * 6)

/* Internal voltage reference in uV */
#घोषणा MCP3911_INT_VREF_UV		1200000

#घोषणा MCP3911_REG_READ(reg, id)	((((reg) << 1) | ((id) << 5) | (1 << 0)) & 0xff)
#घोषणा MCP3911_REG_WRITE(reg, id)	((((reg) << 1) | ((id) << 5) | (0 << 0)) & 0xff)

#घोषणा MCP3911_NUM_CHANNELS		2

काष्ठा mcp3911 अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	काष्ठा regulator *vref;
	काष्ठा clk *clki;
	u32 dev_addr;
पूर्ण;

अटल पूर्णांक mcp3911_पढ़ो(काष्ठा mcp3911 *adc, u8 reg, u32 *val, u8 len)
अणु
	पूर्णांक ret;

	reg = MCP3911_REG_READ(reg, adc->dev_addr);
	ret = spi_ग_लिखो_then_पढ़ो(adc->spi, &reg, 1, val, len);
	अगर (ret < 0)
		वापस ret;

	be32_to_cpus(val);
	*val >>= ((4 - len) * 8);
	dev_dbg(&adc->spi->dev, "reading 0x%x from register 0x%x\n", *val,
		reg >> 1);
	वापस ret;
पूर्ण

अटल पूर्णांक mcp3911_ग_लिखो(काष्ठा mcp3911 *adc, u8 reg, u32 val, u8 len)
अणु
	dev_dbg(&adc->spi->dev, "writing 0x%x to register 0x%x\n", val, reg);

	val <<= (3 - len) * 8;
	cpu_to_be32s(&val);
	val |= MCP3911_REG_WRITE(reg, adc->dev_addr);

	वापस spi_ग_लिखो(adc->spi, &val, len + 1);
पूर्ण

अटल पूर्णांक mcp3911_update(काष्ठा mcp3911 *adc, u8 reg, u32 mask,
		u32 val, u8 len)
अणु
	u32 पंचांगp;
	पूर्णांक ret;

	ret = mcp3911_पढ़ो(adc, reg, &पंचांगp, len);
	अगर (ret)
		वापस ret;

	val &= mask;
	val |= पंचांगp & ~mask;
	वापस mcp3911_ग_लिखो(adc, reg, val, len);
पूर्ण

अटल पूर्णांक mcp3911_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp3911 *adc = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&adc->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = mcp3911_पढ़ो(adc,
				   MCP3911_CHANNEL(channel->channel), val, 3);
		अगर (ret)
			जाओ out;

		ret = IIO_VAL_INT;
		अवरोध;

	हाल IIO_CHAN_INFO_OFFSET:
		ret = mcp3911_पढ़ो(adc,
				   MCP3911_OFFCAL(channel->channel), val, 3);
		अगर (ret)
			जाओ out;

		ret = IIO_VAL_INT;
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		अगर (adc->vref) अणु
			ret = regulator_get_voltage(adc->vref);
			अगर (ret < 0) अणु
				dev_err(indio_dev->dev.parent,
					"failed to get vref voltage: %d\n",
				       ret);
				जाओ out;
			पूर्ण

			*val = ret / 1000;
		पूर्ण अन्यथा अणु
			*val = MCP3911_INT_VREF_UV;
		पूर्ण

		*val2 = 24;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&adc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mcp3911_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक val,
			    पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mcp3911 *adc = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&adc->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (val2 != 0) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/* Write offset */
		ret = mcp3911_ग_लिखो(adc, MCP3911_OFFCAL(channel->channel), val,
				    3);
		अगर (ret)
			जाओ out;

		/* Enable offset*/
		ret = mcp3911_update(adc, MCP3911_REG_STATUSCOM,
				MCP3911_STATUSCOM_EN_OFFCAL,
				MCP3911_STATUSCOM_EN_OFFCAL, 2);
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&adc->lock);
	वापस ret;
पूर्ण

#घोषणा MCP3911_CHAN(idx) अणु					\
		.type = IIO_VOLTAGE,				\
		.indexed = 1,					\
		.channel = idx,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			BIT(IIO_CHAN_INFO_OFFSET) |		\
			BIT(IIO_CHAN_INFO_SCALE),		\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mcp3911_channels[] = अणु
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
पूर्ण;

अटल स्थिर काष्ठा iio_info mcp3911_info = अणु
	.पढ़ो_raw = mcp3911_पढ़ो_raw,
	.ग_लिखो_raw = mcp3911_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक mcp3911_config(काष्ठा mcp3911 *adc, काष्ठा device_node *of_node)
अणु
	u32 configreg;
	पूर्णांक ret;

	of_property_पढ़ो_u32(of_node, "device-addr", &adc->dev_addr);
	अगर (adc->dev_addr > 3) अणु
		dev_err(&adc->spi->dev,
			"invalid device address (%i). Must be in range 0-3.\n",
			adc->dev_addr);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&adc->spi->dev, "use device address %i\n", adc->dev_addr);

	ret = mcp3911_पढ़ो(adc, MCP3911_REG_CONFIG, &configreg, 2);
	अगर (ret)
		वापस ret;

	अगर (adc->vref) अणु
		dev_dbg(&adc->spi->dev, "use external voltage reference\n");
		configreg |= MCP3911_CONFIG_VREFEXT;
	पूर्ण अन्यथा अणु
		dev_dbg(&adc->spi->dev,
			"use internal voltage reference (1.2V)\n");
		configreg &= ~MCP3911_CONFIG_VREFEXT;
	पूर्ण

	अगर (adc->clki) अणु
		dev_dbg(&adc->spi->dev, "use external clock as clocksource\n");
		configreg |= MCP3911_CONFIG_CLKEXT;
	पूर्ण अन्यथा अणु
		dev_dbg(&adc->spi->dev,
			"use crystal oscillator as clocksource\n");
		configreg &= ~MCP3911_CONFIG_CLKEXT;
	पूर्ण

	वापस  mcp3911_ग_लिखो(adc, MCP3911_REG_CONFIG, configreg, 2);
पूर्ण

अटल पूर्णांक mcp3911_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mcp3911 *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	adc->vref = devm_regulator_get_optional(&adc->spi->dev, "vref");
	अगर (IS_ERR(adc->vref)) अणु
		अगर (PTR_ERR(adc->vref) == -ENODEV) अणु
			adc->vref = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&adc->spi->dev,
				"failed to get regulator (%ld)\n",
				PTR_ERR(adc->vref));
			वापस PTR_ERR(adc->vref);
		पूर्ण

	पूर्ण अन्यथा अणु
		ret = regulator_enable(adc->vref);
		अगर (ret)
			वापस ret;
	पूर्ण

	adc->clki = devm_clk_get(&adc->spi->dev, शून्य);
	अगर (IS_ERR(adc->clki)) अणु
		अगर (PTR_ERR(adc->clki) == -ENOENT) अणु
			adc->clki = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&adc->spi->dev,
				"failed to get adc clk (%ld)\n",
				PTR_ERR(adc->clki));
			ret = PTR_ERR(adc->clki);
			जाओ reg_disable;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(adc->clki);
		अगर (ret < 0) अणु
			dev_err(&adc->spi->dev,
				"Failed to enable clki: %d\n", ret);
			जाओ reg_disable;
		पूर्ण
	पूर्ण

	ret = mcp3911_config(adc, spi->dev.of_node);
	अगर (ret)
		जाओ clk_disable;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mcp3911_info;
	spi_set_drvdata(spi, indio_dev);

	indio_dev->channels = mcp3911_channels;
	indio_dev->num_channels = ARRAY_SIZE(mcp3911_channels);

	mutex_init(&adc->lock);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ clk_disable;

	वापस ret;

clk_disable:
	clk_disable_unprepare(adc->clki);
reg_disable:
	अगर (adc->vref)
		regulator_disable(adc->vref);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp3911_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा mcp3911 *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	clk_disable_unprepare(adc->clki);
	अगर (adc->vref)
		regulator_disable(adc->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp3911_dt_ids[] = अणु
	अणु .compatible = "microchip,mcp3911" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp3911_dt_ids);

अटल स्थिर काष्ठा spi_device_id mcp3911_id[] = अणु
	अणु "mcp3911", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp3911_id);

अटल काष्ठा spi_driver mcp3911_driver = अणु
	.driver = अणु
		.name = "mcp3911",
		.of_match_table = mcp3911_dt_ids,
	पूर्ण,
	.probe = mcp3911_probe,
	.हटाओ = mcp3911_हटाओ,
	.id_table = mcp3911_id,
पूर्ण;
module_spi_driver(mcp3911_driver);

MODULE_AUTHOR("Marcus Folkesson <marcus.folkesson@gmail.com>");
MODULE_AUTHOR("Kent Gustavsson <kent@minoris.se>");
MODULE_DESCRIPTION("Microchip Technology MCP3911");
MODULE_LICENSE("GPL v2");
