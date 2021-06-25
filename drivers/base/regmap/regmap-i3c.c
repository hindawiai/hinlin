<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.

#समावेश <linux/regmap.h>
#समावेश <linux/i3c/device.h>
#समावेश <linux/i3c/master.h>
#समावेश <linux/module.h>

अटल पूर्णांक regmap_i3c_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा i3c_device *i3c = dev_to_i3cdev(dev);
	काष्ठा i3c_priv_xfer xfers[] = अणु
		अणु
			.rnw = false,
			.len = count,
			.data.out = data,
		पूर्ण,
	पूर्ण;

	वापस i3c_device_करो_priv_xfers(i3c, xfers, 1);
पूर्ण

अटल पूर्णांक regmap_i3c_पढ़ो(व्योम *context,
			   स्थिर व्योम *reg, माप_प्रकार reg_size,
			   व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i3c_device *i3c = dev_to_i3cdev(dev);
	काष्ठा i3c_priv_xfer xfers[2];

	xfers[0].rnw = false;
	xfers[0].len = reg_size;
	xfers[0].data.out = reg;

	xfers[1].rnw = true;
	xfers[1].len = val_size;
	xfers[1].data.in = val;

	वापस i3c_device_करो_priv_xfers(i3c, xfers, 2);
पूर्ण

अटल काष्ठा regmap_bus regmap_i3c = अणु
	.ग_लिखो = regmap_i3c_ग_लिखो,
	.पढ़ो = regmap_i3c_पढ़ो,
पूर्ण;

काष्ठा regmap *__devm_regmap_init_i3c(काष्ठा i3c_device *i3c,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	वापस __devm_regmap_init(&i3c->dev, &regmap_i3c, &i3c->dev, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_i3c);

MODULE_AUTHOR("Vitor Soares <vitor.soares@synopsys.com>");
MODULE_DESCRIPTION("Regmap I3C Module");
MODULE_LICENSE("GPL v2");
