<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "mpu3050.h"

अटल स्थिर काष्ठा regmap_config mpu3050_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक mpu3050_i2c_bypass_select(काष्ठा i2c_mux_core *mux, u32 chan_id)
अणु
	काष्ठा mpu3050 *mpu3050 = i2c_mux_priv(mux);

	/* Just घातer up the device, that is all that is needed */
	pm_runसमय_get_sync(mpu3050->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_i2c_bypass_deselect(काष्ठा i2c_mux_core *mux, u32 chan_id)
अणु
	काष्ठा mpu3050 *mpu3050 = i2c_mux_priv(mux);

	pm_runसमय_mark_last_busy(mpu3050->dev);
	pm_runसमय_put_स्वतःsuspend(mpu3050->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name;
	काष्ठा mpu3050 *mpu3050;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	अगर (id)
		name = id->name;
	अन्यथा
		वापस -ENODEV;

	regmap = devm_regmap_init_i2c(client, &mpu3050_i2c_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = mpu3050_common_probe(&client->dev, regmap, client->irq, name);
	अगर (ret)
		वापस ret;

	/* The मुख्य driver is up, now रेजिस्टर the I2C mux */
	mpu3050 = iio_priv(dev_get_drvdata(&client->dev));
	mpu3050->i2cmux = i2c_mux_alloc(client->adapter, &client->dev,
					1, 0, I2C_MUX_LOCKED | I2C_MUX_GATE,
					mpu3050_i2c_bypass_select,
					mpu3050_i2c_bypass_deselect);
	/* Just fail the mux, there is no poपूर्णांक in समाप्तing the driver */
	अगर (!mpu3050->i2cmux)
		dev_err(&client->dev, "failed to allocate I2C mux\n");
	अन्यथा अणु
		mpu3050->i2cmux->priv = mpu3050;
		/* Ignore failure, not critical */
		i2c_mux_add_adapter(mpu3050->i2cmux, 0, 0, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(&client->dev);
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);

	अगर (mpu3050->i2cmux)
		i2c_mux_del_adapters(mpu3050->i2cmux);

	वापस mpu3050_common_हटाओ(&client->dev);
पूर्ण

/*
 * device id table is used to identअगरy what device can be
 * supported by this driver
 */
अटल स्थिर काष्ठा i2c_device_id mpu3050_i2c_id[] = अणु
	अणु "mpu3050" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mpu3050_i2c_id);

अटल स्थिर काष्ठा of_device_id mpu3050_i2c_of_match[] = अणु
	अणु .compatible = "invensense,mpu3050", .data = "mpu3050" पूर्ण,
	/* Deprecated venकरोr ID from the Input driver */
	अणु .compatible = "invn,mpu3050", .data = "mpu3050" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpu3050_i2c_of_match);

अटल काष्ठा i2c_driver mpu3050_i2c_driver = अणु
	.probe = mpu3050_i2c_probe,
	.हटाओ = mpu3050_i2c_हटाओ,
	.id_table = mpu3050_i2c_id,
	.driver = अणु
		.of_match_table = mpu3050_i2c_of_match,
		.name = "mpu3050-i2c",
		.pm = &mpu3050_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_i2c_driver(mpu3050_i2c_driver);

MODULE_AUTHOR("Linus Walleij");
MODULE_DESCRIPTION("Invensense MPU3050 gyroscope driver");
MODULE_LICENSE("GPL");
