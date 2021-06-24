<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (C) 2015 Intel Corporation Inc.
*/
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश "inv_mpu_iio.h"

अटल स्थिर काष्ठा regmap_config inv_mpu_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक inv_mpu_i2c_disable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	अगर (st->reg->i2c_अगर) अणु
		ret = regmap_ग_लिखो(st->map, st->reg->i2c_अगर,
				   INV_ICM20602_BIT_I2C_IF_DIS);
	पूर्ण अन्यथा अणु
		st->chip_config.user_ctrl |= INV_MPU6050_BIT_I2C_IF_DIS;
		ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl,
				   st->chip_config.user_ctrl);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक inv_mpu_probe(काष्ठा spi_device *spi)
अणु
	स्थिर व्योम *match;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *spi_id;
	स्थिर अक्षर *name = शून्य;
	क्रमागत inv_devices chip_type;

	अगर ((spi_id = spi_get_device_id(spi))) अणु
		chip_type = (क्रमागत inv_devices)spi_id->driver_data;
		name = spi_id->name;
	पूर्ण अन्यथा अगर ((match = device_get_match_data(&spi->dev))) अणु
		chip_type = (क्रमागत inv_devices)match;
		name = dev_name(&spi->dev);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	regmap = devm_regmap_init_spi(spi, &inv_mpu_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस inv_mpu_core_probe(regmap, spi->irq, name,
				  inv_mpu_i2c_disable, chip_type);
पूर्ण

/*
 * device id table is used to identअगरy what device can be
 * supported by this driver
 */
अटल स्थिर काष्ठा spi_device_id inv_mpu_id[] = अणु
	अणु"mpu6000", INV_MPU6000पूर्ण,
	अणु"mpu6500", INV_MPU6500पूर्ण,
	अणु"mpu6515", INV_MPU6515पूर्ण,
	अणु"mpu6880", INV_MPU6880पूर्ण,
	अणु"mpu9250", INV_MPU9250पूर्ण,
	अणु"mpu9255", INV_MPU9255पूर्ण,
	अणु"icm20608", INV_ICM20608पूर्ण,
	अणु"icm20609", INV_ICM20609पूर्ण,
	अणु"icm20689", INV_ICM20689पूर्ण,
	अणु"icm20602", INV_ICM20602पूर्ण,
	अणु"icm20690", INV_ICM20690पूर्ण,
	अणु"iam20680", INV_IAM20680पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, inv_mpu_id);

अटल स्थिर काष्ठा of_device_id inv_of_match[] = अणु
	अणु
		.compatible = "invensense,mpu6000",
		.data = (व्योम *)INV_MPU6000
	पूर्ण,
	अणु
		.compatible = "invensense,mpu6500",
		.data = (व्योम *)INV_MPU6500
	पूर्ण,
	अणु
		.compatible = "invensense,mpu6515",
		.data = (व्योम *)INV_MPU6515
	पूर्ण,
	अणु
		.compatible = "invensense,mpu6880",
		.data = (व्योम *)INV_MPU6880
	पूर्ण,
	अणु
		.compatible = "invensense,mpu9250",
		.data = (व्योम *)INV_MPU9250
	पूर्ण,
	अणु
		.compatible = "invensense,mpu9255",
		.data = (व्योम *)INV_MPU9255
	पूर्ण,
	अणु
		.compatible = "invensense,icm20608",
		.data = (व्योम *)INV_ICM20608
	पूर्ण,
	अणु
		.compatible = "invensense,icm20609",
		.data = (व्योम *)INV_ICM20609
	पूर्ण,
	अणु
		.compatible = "invensense,icm20689",
		.data = (व्योम *)INV_ICM20689
	पूर्ण,
	अणु
		.compatible = "invensense,icm20602",
		.data = (व्योम *)INV_ICM20602
	पूर्ण,
	अणु
		.compatible = "invensense,icm20690",
		.data = (व्योम *)INV_ICM20690
	पूर्ण,
	अणु
		.compatible = "invensense,iam20680",
		.data = (व्योम *)INV_IAM20680
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, inv_of_match);

अटल स्थिर काष्ठा acpi_device_id inv_acpi_match[] = अणु
	अणु"INVN6000", INV_MPU6000पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, inv_acpi_match);

अटल काष्ठा spi_driver inv_mpu_driver = अणु
	.probe		=	inv_mpu_probe,
	.id_table	=	inv_mpu_id,
	.driver = अणु
		.of_match_table = inv_of_match,
		.acpi_match_table = ACPI_PTR(inv_acpi_match),
		.name	=	"inv-mpu6000-spi",
		.pm     =       &inv_mpu_pmops,
	पूर्ण,
पूर्ण;

module_spi_driver(inv_mpu_driver);

MODULE_AUTHOR("Adriana Reus <adriana.reus@intel.com>");
MODULE_DESCRIPTION("Invensense device MPU6000 driver");
MODULE_LICENSE("GPL");
