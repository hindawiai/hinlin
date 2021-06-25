<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// SPI driven IR LED device driver
//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
// Copyright (c) Andi Shyti <andi@etezian.org>

#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <media/rc-core.h>

#घोषणा IR_SPI_DRIVER_NAME		"ir-spi"

#घोषणा IR_SPI_DEFAULT_FREQUENCY	38000
#घोषणा IR_SPI_MAX_बफ_मानE		 4096

काष्ठा ir_spi_data अणु
	u32 freq;
	bool negated;

	u16 tx_buf[IR_SPI_MAX_बफ_मानE];
	u16 pulse;
	u16 space;

	काष्ठा rc_dev *rc;
	काष्ठा spi_device *spi;
	काष्ठा regulator *regulator;
पूर्ण;

अटल पूर्णांक ir_spi_tx(काष्ठा rc_dev *dev,
		     अचिन्हित पूर्णांक *buffer, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित पूर्णांक len = 0;
	काष्ठा ir_spi_data *idata = dev->priv;
	काष्ठा spi_transfer xfer;

	/* convert the pulse/space संकेत to raw binary संकेत */
	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित पूर्णांक periods;
		पूर्णांक j;
		u16 val;

		periods = DIV_ROUND_CLOSEST(buffer[i] * idata->freq, 1000000);

		अगर (len + periods >= IR_SPI_MAX_बफ_मानE)
			वापस -EINVAL;

		/*
		 * the first value in buffer is a pulse, so that 0, 2, 4, ...
		 * contain a pulse duration. On the contrary, 1, 3, 5, ...
		 * contain a space duration.
		 */
		val = (i % 2) ? idata->space : idata->pulse;
		क्रम (j = 0; j < periods; j++)
			idata->tx_buf[len++] = val;
	पूर्ण

	स_रखो(&xfer, 0, माप(xfer));

	xfer.speed_hz = idata->freq * 16;
	xfer.len = len * माप(*idata->tx_buf);
	xfer.tx_buf = idata->tx_buf;

	ret = regulator_enable(idata->regulator);
	अगर (ret)
		वापस ret;

	ret = spi_sync_transfer(idata->spi, &xfer, 1);
	अगर (ret)
		dev_err(&idata->spi->dev, "unable to deliver the signal\n");

	regulator_disable(idata->regulator);

	वापस ret ? ret : count;
पूर्ण

अटल पूर्णांक ir_spi_set_tx_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा ir_spi_data *idata = dev->priv;

	अगर (!carrier)
		वापस -EINVAL;

	idata->freq = carrier;

	वापस 0;
पूर्ण

अटल पूर्णांक ir_spi_set_duty_cycle(काष्ठा rc_dev *dev, u32 duty_cycle)
अणु
	काष्ठा ir_spi_data *idata = dev->priv;
	पूर्णांक bits = (duty_cycle * 15) / 100;

	idata->pulse = GENMASK(bits, 0);

	अगर (idata->negated) अणु
		idata->pulse = ~idata->pulse;
		idata->space = 0xffff;
	पूर्ण अन्यथा अणु
		idata->space = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ir_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	u8 dc;
	काष्ठा ir_spi_data *idata;

	idata = devm_kzalloc(&spi->dev, माप(*idata), GFP_KERNEL);
	अगर (!idata)
		वापस -ENOMEM;

	idata->regulator = devm_regulator_get(&spi->dev, "irda_regulator");
	अगर (IS_ERR(idata->regulator))
		वापस PTR_ERR(idata->regulator);

	idata->rc = devm_rc_allocate_device(&spi->dev, RC_DRIVER_IR_RAW_TX);
	अगर (!idata->rc)
		वापस -ENOMEM;

	idata->rc->tx_ir           = ir_spi_tx;
	idata->rc->s_tx_carrier    = ir_spi_set_tx_carrier;
	idata->rc->s_tx_duty_cycle = ir_spi_set_duty_cycle;
	idata->rc->device_name	   = "IR SPI";
	idata->rc->driver_name     = IR_SPI_DRIVER_NAME;
	idata->rc->priv            = idata;
	idata->spi                 = spi;

	idata->negated = of_property_पढ़ो_bool(spi->dev.of_node,
							"led-active-low");
	ret = of_property_पढ़ो_u8(spi->dev.of_node, "duty-cycle", &dc);
	अगर (ret)
		dc = 50;

	/* ir_spi_set_duty_cycle cannot fail,
	 * it वापसs पूर्णांक to be compatible with the
	 * rc->s_tx_duty_cycle function
	 */
	ir_spi_set_duty_cycle(idata->rc, dc);

	idata->freq = IR_SPI_DEFAULT_FREQUENCY;

	वापस devm_rc_रेजिस्टर_device(&spi->dev, idata->rc);
पूर्ण

अटल पूर्णांक ir_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ir_spi_of_match[] = अणु
	अणु .compatible = "ir-spi-led" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ir_spi_of_match);

अटल काष्ठा spi_driver ir_spi_driver = अणु
	.probe = ir_spi_probe,
	.हटाओ = ir_spi_हटाओ,
	.driver = अणु
		.name = IR_SPI_DRIVER_NAME,
		.of_match_table = ir_spi_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(ir_spi_driver);

MODULE_AUTHOR("Andi Shyti <andi@etezian.org>");
MODULE_DESCRIPTION("SPI IR LED");
MODULE_LICENSE("GPL v2");
