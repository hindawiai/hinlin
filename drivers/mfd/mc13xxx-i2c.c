<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2009-2010 Creative Product Design
 * Marc Reilly marc@cpdesign.com.au
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mc13xxx.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>

#समावेश "mc13xxx.h"

अटल स्थिर काष्ठा i2c_device_id mc13xxx_i2c_device_id[] = अणु
	अणु
		.name = "mc13892",
		.driver_data = (kernel_uदीर्घ_t)&mc13xxx_variant_mc13892,
	पूर्ण, अणु
		.name = "mc34708",
		.driver_data = (kernel_uदीर्घ_t)&mc13xxx_variant_mc34708,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mc13xxx_i2c_device_id);

अटल स्थिर काष्ठा of_device_id mc13xxx_dt_ids[] = अणु
	अणु
		.compatible = "fsl,mc13892",
		.data = &mc13xxx_variant_mc13892,
	पूर्ण, अणु
		.compatible = "fsl,mc34708",
		.data = &mc13xxx_variant_mc34708,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mc13xxx_dt_ids);

अटल स्थिर काष्ठा regmap_config mc13xxx_regmap_i2c_config = अणु
	.reg_bits = 8,
	.val_bits = 24,

	.max_रेजिस्टर = MC13XXX_NUMREGS,

	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक mc13xxx_i2c_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mc13xxx *mc13xxx;
	पूर्णांक ret;

	mc13xxx = devm_kzalloc(&client->dev, माप(*mc13xxx), GFP_KERNEL);
	अगर (!mc13xxx)
		वापस -ENOMEM;

	dev_set_drvdata(&client->dev, mc13xxx);

	mc13xxx->irq = client->irq;

	mc13xxx->regmap = devm_regmap_init_i2c(client,
					       &mc13xxx_regmap_i2c_config);
	अगर (IS_ERR(mc13xxx->regmap)) अणु
		ret = PTR_ERR(mc13xxx->regmap);
		dev_err(&client->dev, "Failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (client->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *of_id =
			of_match_device(mc13xxx_dt_ids, &client->dev);
		mc13xxx->variant = of_id->data;
	पूर्ण अन्यथा अणु
		mc13xxx->variant = (व्योम *)id->driver_data;
	पूर्ण

	वापस mc13xxx_common_init(&client->dev);
पूर्ण

अटल पूर्णांक mc13xxx_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस mc13xxx_common_निकास(&client->dev);
पूर्ण

अटल काष्ठा i2c_driver mc13xxx_i2c_driver = अणु
	.id_table = mc13xxx_i2c_device_id,
	.driver = अणु
		.name = "mc13xxx",
		.of_match_table = mc13xxx_dt_ids,
	पूर्ण,
	.probe = mc13xxx_i2c_probe,
	.हटाओ = mc13xxx_i2c_हटाओ,
पूर्ण;

अटल पूर्णांक __init mc13xxx_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&mc13xxx_i2c_driver);
पूर्ण
subsys_initcall(mc13xxx_i2c_init);

अटल व्योम __निकास mc13xxx_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&mc13xxx_i2c_driver);
पूर्ण
module_निकास(mc13xxx_i2c_निकास);

MODULE_DESCRIPTION("i2c driver for Freescale MC13XXX PMIC");
MODULE_AUTHOR("Marc Reilly <marc@cpdesign.com.au");
MODULE_LICENSE("GPL v2");
