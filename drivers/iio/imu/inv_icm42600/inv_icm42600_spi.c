<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 InvenSense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/property.h>

#समावेश "inv_icm42600.h"

अटल पूर्णांक inv_icm42600_spi_bus_setup(काष्ठा inv_icm42600_state *st)
अणु
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret;

	/* setup पूर्णांकerface रेजिस्टरs */
	val = INV_ICM42600_INTF_CONFIG6_I3C_EN |
	      INV_ICM42600_INTF_CONFIG6_I3C_SDR_EN |
	      INV_ICM42600_INTF_CONFIG6_I3C_DDR_EN;
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INTF_CONFIG6,
				 INV_ICM42600_INTF_CONFIG6_MASK, val);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INTF_CONFIG4,
				 INV_ICM42600_INTF_CONFIG4_I3C_BUS_ONLY, 0);
	अगर (ret)
		वापस ret;

	/* set slew rates क्रम I2C and SPI */
	mask = INV_ICM42600_DRIVE_CONFIG_I2C_MASK |
	       INV_ICM42600_DRIVE_CONFIG_SPI_MASK;
	val = INV_ICM42600_DRIVE_CONFIG_I2C(INV_ICM42600_SLEW_RATE_20_60NS) |
	      INV_ICM42600_DRIVE_CONFIG_SPI(INV_ICM42600_SLEW_RATE_INF_2NS);
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_DRIVE_CONFIG,
				 mask, val);
	अगर (ret)
		वापस ret;

	/* disable i2c bus */
	वापस regmap_update_bits(st->map, INV_ICM42600_REG_INTF_CONFIG0,
				  INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK,
				  INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_I2C_DIS);
पूर्ण

अटल पूर्णांक inv_icm42600_probe(काष्ठा spi_device *spi)
अणु
	स्थिर व्योम *match;
	क्रमागत inv_icm42600_chip chip;
	काष्ठा regmap *regmap;

	match = device_get_match_data(&spi->dev);
	अगर (!match)
		वापस -EINVAL;
	chip = (क्रमागत inv_icm42600_chip)match;

	regmap = devm_regmap_init_spi(spi, &inv_icm42600_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस inv_icm42600_core_probe(regmap, chip, spi->irq,
				       inv_icm42600_spi_bus_setup);
पूर्ण

अटल स्थिर काष्ठा of_device_id inv_icm42600_of_matches[] = अणु
	अणु
		.compatible = "invensense,icm42600",
		.data = (व्योम *)INV_CHIP_ICM42600,
	पूर्ण, अणु
		.compatible = "invensense,icm42602",
		.data = (व्योम *)INV_CHIP_ICM42602,
	पूर्ण, अणु
		.compatible = "invensense,icm42605",
		.data = (व्योम *)INV_CHIP_ICM42605,
	पूर्ण, अणु
		.compatible = "invensense,icm42622",
		.data = (व्योम *)INV_CHIP_ICM42622,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, inv_icm42600_of_matches);

अटल काष्ठा spi_driver inv_icm42600_driver = अणु
	.driver = अणु
		.name = "inv-icm42600-spi",
		.of_match_table = inv_icm42600_of_matches,
		.pm = &inv_icm42600_pm_ops,
	पूर्ण,
	.probe = inv_icm42600_probe,
पूर्ण;
module_spi_driver(inv_icm42600_driver);

MODULE_AUTHOR("InvenSense, Inc.");
MODULE_DESCRIPTION("InvenSense ICM-426xx SPI driver");
MODULE_LICENSE("GPL");
