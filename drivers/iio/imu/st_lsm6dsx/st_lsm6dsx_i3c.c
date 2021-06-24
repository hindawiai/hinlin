<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 *
 * Author: Vitor Soares <vitor.soares@synopsys.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i3c/device.h>
#समावेश <linux/i3c/master.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "st_lsm6dsx.h"

अटल स्थिर काष्ठा i3c_device_id st_lsm6dsx_i3c_ids[] = अणु
	I3C_DEVICE(0x0104, 0x006C, (व्योम *)ST_LSM6DSO_ID),
	I3C_DEVICE(0x0104, 0x006B, (व्योम *)ST_LSM6DSR_ID),
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i3c, st_lsm6dsx_i3c_ids);

अटल पूर्णांक st_lsm6dsx_i3c_probe(काष्ठा i3c_device *i3cdev)
अणु
	काष्ठा regmap_config st_lsm6dsx_i3c_regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;
	स्थिर काष्ठा i3c_device_id *id = i3c_device_match_id(i3cdev,
							    st_lsm6dsx_i3c_ids);
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i3c(i3cdev, &st_lsm6dsx_i3c_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i3cdev->dev, "Failed to register i3c regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस st_lsm6dsx_probe(&i3cdev->dev, 0, (uपूर्णांकptr_t)id->data, regmap);
पूर्ण

अटल काष्ठा i3c_driver st_lsm6dsx_driver = अणु
	.driver = अणु
		.name = "st_lsm6dsx_i3c",
		.pm = &st_lsm6dsx_pm_ops,
	पूर्ण,
	.probe = st_lsm6dsx_i3c_probe,
	.id_table = st_lsm6dsx_i3c_ids,
पूर्ण;
module_i3c_driver(st_lsm6dsx_driver);

MODULE_AUTHOR("Vitor Soares <vitor.soares@synopsys.com>");
MODULE_DESCRIPTION("STMicroelectronics st_lsm6dsx i3c driver");
MODULE_LICENSE("GPL v2");
