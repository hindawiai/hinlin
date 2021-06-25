<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2009-2010 Pengutronix
 * Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>
 *
 * loosely based on an earlier driver that has
 * Copyright 2009 Pengutronix, Sascha Hauer <s.hauer@pengutronix.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mc13xxx.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>

#समावेश "mc13xxx.h"

अटल स्थिर काष्ठा spi_device_id mc13xxx_device_id[] = अणु
	अणु
		.name = "mc13783",
		.driver_data = (kernel_uदीर्घ_t)&mc13xxx_variant_mc13783,
	पूर्ण, अणु
		.name = "mc13892",
		.driver_data = (kernel_uदीर्घ_t)&mc13xxx_variant_mc13892,
	पूर्ण, अणु
		.name = "mc34708",
		.driver_data = (kernel_uदीर्घ_t)&mc13xxx_variant_mc34708,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mc13xxx_device_id);

अटल स्थिर काष्ठा of_device_id mc13xxx_dt_ids[] = अणु
	अणु .compatible = "fsl,mc13783", .data = &mc13xxx_variant_mc13783, पूर्ण,
	अणु .compatible = "fsl,mc13892", .data = &mc13xxx_variant_mc13892, पूर्ण,
	अणु .compatible = "fsl,mc34708", .data = &mc13xxx_variant_mc34708, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mc13xxx_dt_ids);

अटल स्थिर काष्ठा regmap_config mc13xxx_regmap_spi_config = अणु
	.reg_bits = 7,
	.pad_bits = 1,
	.val_bits = 24,
	.ग_लिखो_flag_mask = 0x80,

	.max_रेजिस्टर = MC13XXX_NUMREGS,

	.cache_type = REGCACHE_NONE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक mc13xxx_spi_पढ़ो(व्योम *context, स्थिर व्योम *reg, माप_प्रकार reg_size,
				व्योम *val, माप_प्रकार val_size)
अणु
	अचिन्हित अक्षर w[4] = अणु *((अचिन्हित अक्षर *) reg), 0, 0, 0पूर्ण;
	अचिन्हित अक्षर r[4];
	अचिन्हित अक्षर *p = val;
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा spi_transfer t = अणु
		.tx_buf = w,
		.rx_buf = r,
		.len = 4,
	पूर्ण;

	काष्ठा spi_message m;
	पूर्णांक ret;

	अगर (val_size != 3 || reg_size != 1)
		वापस -ENOTSUPP;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	ret = spi_sync(spi, &m);

	स_नकल(p, &r[1], 3);

	वापस ret;
पूर्ण

अटल पूर्णांक mc13xxx_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	स्थिर अक्षर *reg = data;

	अगर (count != 4)
		वापस -ENOTSUPP;

	/* include errata fix क्रम spi audio problems */
	अगर (*reg == MC13783_AUDIO_CODEC || *reg == MC13783_AUDIO_DAC)
		spi_ग_लिखो(spi, data, count);

	वापस spi_ग_लिखो(spi, data, count);
पूर्ण

/*
 * We cannot use regmap-spi generic bus implementation here.
 * The MC13783 chip will get corrupted अगर CS संकेत is deनिश्चितed
 * and on i.Mx31 SoC (the target SoC क्रम MC13783 PMIC) the SPI controller
 * has the following errata (DSPhl22960):
 * "The CSPI negates SS when the FIFO becomes empty with
 * SSCTL= 0. Software cannot guarantee that the FIFO will not
 * drain because of higher priority पूर्णांकerrupts and the
 * non-realसमय अक्षरacteristics of the operating प्रणाली. As a
 * result, the SS will negate beक्रमe all of the data has been
 * transferred to/from the peripheral."
 * We workaround this by accessing the SPI controller with a
 * single transfert.
 */

अटल काष्ठा regmap_bus regmap_mc13xxx_bus = अणु
	.ग_लिखो = mc13xxx_spi_ग_लिखो,
	.पढ़ो = mc13xxx_spi_पढ़ो,
पूर्ण;

अटल पूर्णांक mc13xxx_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा mc13xxx *mc13xxx;
	पूर्णांक ret;

	mc13xxx = devm_kzalloc(&spi->dev, माप(*mc13xxx), GFP_KERNEL);
	अगर (!mc13xxx)
		वापस -ENOMEM;

	dev_set_drvdata(&spi->dev, mc13xxx);

	spi->mode = SPI_MODE_0 | SPI_CS_HIGH;

	mc13xxx->irq = spi->irq;

	spi->max_speed_hz = spi->max_speed_hz ? : 26000000;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	mc13xxx->regmap = devm_regmap_init(&spi->dev, &regmap_mc13xxx_bus,
					   &spi->dev,
					   &mc13xxx_regmap_spi_config);
	अगर (IS_ERR(mc13xxx->regmap)) अणु
		ret = PTR_ERR(mc13xxx->regmap);
		dev_err(&spi->dev, "Failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (spi->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *of_id =
			of_match_device(mc13xxx_dt_ids, &spi->dev);

		mc13xxx->variant = of_id->data;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा spi_device_id *id_entry = spi_get_device_id(spi);

		mc13xxx->variant = (व्योम *)id_entry->driver_data;
	पूर्ण

	वापस mc13xxx_common_init(&spi->dev);
पूर्ण

अटल पूर्णांक mc13xxx_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस mc13xxx_common_निकास(&spi->dev);
पूर्ण

अटल काष्ठा spi_driver mc13xxx_spi_driver = अणु
	.id_table = mc13xxx_device_id,
	.driver = अणु
		.name = "mc13xxx",
		.of_match_table = mc13xxx_dt_ids,
	पूर्ण,
	.probe = mc13xxx_spi_probe,
	.हटाओ = mc13xxx_spi_हटाओ,
पूर्ण;

अटल पूर्णांक __init mc13xxx_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&mc13xxx_spi_driver);
पूर्ण
subsys_initcall(mc13xxx_init);

अटल व्योम __निकास mc13xxx_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&mc13xxx_spi_driver);
पूर्ण
module_निकास(mc13xxx_निकास);

MODULE_DESCRIPTION("Core driver for Freescale MC13XXX PMIC");
MODULE_AUTHOR("Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>");
MODULE_LICENSE("GPL v2");
