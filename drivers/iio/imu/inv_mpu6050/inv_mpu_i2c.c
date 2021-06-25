<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (C) 2012 Invensense, Inc.
*/

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश "inv_mpu_iio.h"

अटल स्थिर काष्ठा regmap_config inv_mpu_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक inv_mpu6050_select_bypass(काष्ठा i2c_mux_core *muxc, u32 chan_id)
अणु
	वापस 0;
पूर्ण

अटल bool inv_mpu_i2c_aux_bus(काष्ठा device *dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_get_drvdata(dev));

	चयन (st->chip_type) अणु
	हाल INV_ICM20608:
	हाल INV_ICM20609:
	हाल INV_ICM20689:
	हाल INV_ICM20602:
	हाल INV_IAM20680:
		/* no i2c auxiliary bus on the chip */
		वापस false;
	हाल INV_MPU9150:
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		अगर (st->magn_disabled)
			वापस true;
		अन्यथा
			वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक inv_mpu_i2c_aux_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	काष्ठा device_node *mux_node;
	पूर्णांक ret;

	/*
	 * MPU9xxx magnetometer support requires to disable i2c auxiliary bus.
	 * To ensure backward compatibility with existing setups, करो not disable
	 * i2c auxiliary bus अगर it used.
	 * Check क्रम i2c-gate node in devicetree and set magnetometer disabled.
	 * Only MPU6500 is supported by ACPI, no need to check.
	 */
	चयन (st->chip_type) अणु
	हाल INV_MPU9150:
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		mux_node = of_get_child_by_name(dev->of_node, "i2c-gate");
		अगर (mux_node != शून्य) अणु
			st->magn_disabled = true;
			dev_warn(dev, "disable internal use of magnetometer\n");
		पूर्ण
		of_node_put(mux_node);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* enable i2c bypass when using i2c auxiliary bus */
	अगर (inv_mpu_i2c_aux_bus(dev)) अणु
		ret = regmap_ग_लिखो(st->map, st->reg->पूर्णांक_pin_cfg,
				   st->irq_mask | INV_MPU6050_BIT_BYPASS_EN);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  inv_mpu_probe() - probe function.
 *  @client:          i2c client.
 *  @id:              i2c device id.
 *
 *  Returns 0 on success, a negative error code otherwise.
 */
अटल पूर्णांक inv_mpu_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर व्योम *match;
	काष्ठा inv_mpu6050_state *st;
	पूर्णांक result;
	क्रमागत inv_devices chip_type;
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	match = device_get_match_data(&client->dev);
	अगर (match) अणु
		chip_type = (क्रमागत inv_devices)match;
		name = client->name;
	पूर्ण अन्यथा अगर (id) अणु
		chip_type = (क्रमागत inv_devices)
			id->driver_data;
		name = id->name;
	पूर्ण अन्यथा अणु
		वापस -ENOSYS;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &inv_mpu_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	result = inv_mpu_core_probe(regmap, client->irq, name,
				    inv_mpu_i2c_aux_setup, chip_type);
	अगर (result < 0)
		वापस result;

	st = iio_priv(dev_get_drvdata(&client->dev));
	अगर (inv_mpu_i2c_aux_bus(&client->dev)) अणु
		/* declare i2c auxiliary bus */
		st->muxc = i2c_mux_alloc(client->adapter, &client->dev,
					 1, 0, I2C_MUX_LOCKED | I2C_MUX_GATE,
					 inv_mpu6050_select_bypass, शून्य);
		अगर (!st->muxc)
			वापस -ENOMEM;
		st->muxc->priv = dev_get_drvdata(&client->dev);
		result = i2c_mux_add_adapter(st->muxc, 0, 0, 0);
		अगर (result)
			वापस result;
		result = inv_mpu_acpi_create_mux_client(client);
		अगर (result)
			जाओ out_del_mux;
	पूर्ण

	वापस 0;

out_del_mux:
	i2c_mux_del_adapters(st->muxc);
	वापस result;
पूर्ण

अटल पूर्णांक inv_mpu_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);

	अगर (st->muxc) अणु
		inv_mpu_acpi_delete_mux_client(client);
		i2c_mux_del_adapters(st->muxc);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * device id table is used to identअगरy what device can be
 * supported by this driver
 */
अटल स्थिर काष्ठा i2c_device_id inv_mpu_id[] = अणु
	अणु"mpu6050", INV_MPU6050पूर्ण,
	अणु"mpu6500", INV_MPU6500पूर्ण,
	अणु"mpu6515", INV_MPU6515पूर्ण,
	अणु"mpu6880", INV_MPU6880पूर्ण,
	अणु"mpu9150", INV_MPU9150पूर्ण,
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

MODULE_DEVICE_TABLE(i2c, inv_mpu_id);

अटल स्थिर काष्ठा of_device_id inv_of_match[] = अणु
	अणु
		.compatible = "invensense,mpu6050",
		.data = (व्योम *)INV_MPU6050
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
		.compatible = "invensense,mpu9150",
		.data = (व्योम *)INV_MPU9150
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
	अणु"INVN6500", INV_MPU6500पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, inv_acpi_match);

अटल काष्ठा i2c_driver inv_mpu_driver = अणु
	.probe		=	inv_mpu_probe,
	.हटाओ		=	inv_mpu_हटाओ,
	.id_table	=	inv_mpu_id,
	.driver = अणु
		.of_match_table = inv_of_match,
		.acpi_match_table = ACPI_PTR(inv_acpi_match),
		.name	=	"inv-mpu6050-i2c",
		.pm     =       &inv_mpu_pmops,
	पूर्ण,
पूर्ण;

module_i2c_driver(inv_mpu_driver);

MODULE_AUTHOR("Invensense Corporation");
MODULE_DESCRIPTION("Invensense device MPU6050 driver");
MODULE_LICENSE("GPL");
