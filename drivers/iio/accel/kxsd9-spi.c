<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "kxsd9.h"

अटल पूर्णांक kxsd9_spi_probe(काष्ठा spi_device *spi)
अणु
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x0e,
	पूर्ण;
	काष्ठा regmap *regmap;

	spi->mode = SPI_MODE_0;
	regmap = devm_regmap_init_spi(spi, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "%s: regmap allocation failed: %ld\n",
			__func__, PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस kxsd9_common_probe(&spi->dev,
				  regmap,
				  spi_get_device_id(spi)->name);
पूर्ण

अटल पूर्णांक kxsd9_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस kxsd9_common_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id kxsd9_spi_id[] = अणु
	अणु"kxsd9", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, kxsd9_spi_id);

अटल स्थिर काष्ठा of_device_id kxsd9_of_match[] = अणु
        अणु .compatible = "kionix,kxsd9" पूर्ण,
        अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, kxsd9_of_match);

अटल काष्ठा spi_driver kxsd9_spi_driver = अणु
	.driver = अणु
		.name = "kxsd9",
		.pm = &kxsd9_dev_pm_ops,
		.of_match_table = kxsd9_of_match,
	पूर्ण,
	.probe = kxsd9_spi_probe,
	.हटाओ = kxsd9_spi_हटाओ,
	.id_table = kxsd9_spi_id,
पूर्ण;
module_spi_driver(kxsd9_spi_driver);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Kionix KXSD9 SPI driver");
MODULE_LICENSE("GPL v2");
