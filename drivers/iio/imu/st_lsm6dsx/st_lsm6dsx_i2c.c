<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics st_lsm6dsx i2c driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "st_lsm6dsx.h"

अटल स्थिर काष्ठा regmap_config st_lsm6dsx_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक st_lsm6dsx_i2c_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक hw_id = id->driver_data;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &st_lsm6dsx_i2c_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस st_lsm6dsx_probe(&client->dev, client->irq, hw_id, regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id st_lsm6dsx_i2c_of_match[] = अणु
	अणु
		.compatible = "st,lsm6ds3",
		.data = (व्योम *)ST_LSM6DS3_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6ds3h",
		.data = (व्योम *)ST_LSM6DS3H_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dsl",
		.data = (व्योम *)ST_LSM6DSL_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dsm",
		.data = (व्योम *)ST_LSM6DSM_ID,
	पूर्ण,
	अणु
		.compatible = "st,ism330dlc",
		.data = (व्योम *)ST_ISM330DLC_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dso",
		.data = (व्योम *)ST_LSM6DSO_ID,
	पूर्ण,
	अणु
		.compatible = "st,asm330lhh",
		.data = (व्योम *)ST_ASM330LHH_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dsox",
		.data = (व्योम *)ST_LSM6DSOX_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dsr",
		.data = (व्योम *)ST_LSM6DSR_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6ds3tr-c",
		.data = (व्योम *)ST_LSM6DS3TRC_ID,
	पूर्ण,
	अणु
		.compatible = "st,ism330dhcx",
		.data = (व्योम *)ST_ISM330DHCX_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm9ds1-imu",
		.data = (व्योम *)ST_LSM9DS1_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6ds0",
		.data = (व्योम *)ST_LSM6DS0_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dsrx",
		.data = (व्योम *)ST_LSM6DSRX_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dst",
		.data = (व्योम *)ST_LSM6DST_ID,
	पूर्ण,
	अणु
		.compatible = "st,lsm6dsop",
		.data = (व्योम *)ST_LSM6DSOP_ID,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_lsm6dsx_i2c_of_match);

अटल स्थिर काष्ठा i2c_device_id st_lsm6dsx_i2c_id_table[] = अणु
	अणु ST_LSM6DS3_DEV_NAME, ST_LSM6DS3_ID पूर्ण,
	अणु ST_LSM6DS3H_DEV_NAME, ST_LSM6DS3H_ID पूर्ण,
	अणु ST_LSM6DSL_DEV_NAME, ST_LSM6DSL_ID पूर्ण,
	अणु ST_LSM6DSM_DEV_NAME, ST_LSM6DSM_ID पूर्ण,
	अणु ST_ISM330DLC_DEV_NAME, ST_ISM330DLC_ID पूर्ण,
	अणु ST_LSM6DSO_DEV_NAME, ST_LSM6DSO_ID पूर्ण,
	अणु ST_ASM330LHH_DEV_NAME, ST_ASM330LHH_ID पूर्ण,
	अणु ST_LSM6DSOX_DEV_NAME, ST_LSM6DSOX_ID पूर्ण,
	अणु ST_LSM6DSR_DEV_NAME, ST_LSM6DSR_ID पूर्ण,
	अणु ST_LSM6DS3TRC_DEV_NAME, ST_LSM6DS3TRC_ID पूर्ण,
	अणु ST_ISM330DHCX_DEV_NAME, ST_ISM330DHCX_ID पूर्ण,
	अणु ST_LSM9DS1_DEV_NAME, ST_LSM9DS1_ID पूर्ण,
	अणु ST_LSM6DS0_DEV_NAME, ST_LSM6DS0_ID पूर्ण,
	अणु ST_LSM6DSRX_DEV_NAME, ST_LSM6DSRX_ID पूर्ण,
	अणु ST_LSM6DST_DEV_NAME, ST_LSM6DST_ID पूर्ण,
	अणु ST_LSM6DSOP_DEV_NAME, ST_LSM6DSOP_ID पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st_lsm6dsx_i2c_id_table);

अटल काष्ठा i2c_driver st_lsm6dsx_driver = अणु
	.driver = अणु
		.name = "st_lsm6dsx_i2c",
		.pm = &st_lsm6dsx_pm_ops,
		.of_match_table = st_lsm6dsx_i2c_of_match,
	पूर्ण,
	.probe = st_lsm6dsx_i2c_probe,
	.id_table = st_lsm6dsx_i2c_id_table,
पूर्ण;
module_i2c_driver(st_lsm6dsx_driver);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi@st.com>");
MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics st_lsm6dsx i2c driver");
MODULE_LICENSE("GPL v2");
