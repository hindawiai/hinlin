<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mfd/si476x-prop.c -- Subroutines to access
 * properties of si476x chips
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */
#समावेश <linux/module.h>

#समावेश <linux/mfd/si476x-core.h>

काष्ठा si476x_property_range अणु
	u16 low, high;
पूर्ण;

अटल bool si476x_core_element_is_in_array(u16 element,
					    स्थिर u16 array[],
					    माप_प्रकार size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		अगर (element == array[i])
			वापस true;

	वापस false;
पूर्ण

अटल bool si476x_core_element_is_in_range(u16 element,
					    स्थिर काष्ठा si476x_property_range range[],
					    माप_प्रकार size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		अगर (element <= range[i].high && element >= range[i].low)
			वापस true;

	वापस false;
पूर्ण

अटल bool si476x_core_is_valid_property_a10(काष्ठा si476x_core *core,
					      u16 property)
अणु
	अटल स्थिर u16 valid_properties[] = अणु
		0x0000,
		0x0500, 0x0501,
		0x0600,
		0x0709, 0x070C, 0x070D, 0x70E, 0x710,
		0x0718,
		0x1207, 0x1208,
		0x2007,
		0x2300,
	पूर्ण;

	अटल स्थिर काष्ठा si476x_property_range valid_ranges[] = अणु
		अणु 0x0200, 0x0203 पूर्ण,
		अणु 0x0300, 0x0303 पूर्ण,
		अणु 0x0400, 0x0404 पूर्ण,
		अणु 0x0700, 0x0707 पूर्ण,
		अणु 0x1100, 0x1102 पूर्ण,
		अणु 0x1200, 0x1204 पूर्ण,
		अणु 0x1300, 0x1306 पूर्ण,
		अणु 0x2000, 0x2005 पूर्ण,
		अणु 0x2100, 0x2104 पूर्ण,
		अणु 0x2106, 0x2106 पूर्ण,
		अणु 0x2200, 0x220E पूर्ण,
		अणु 0x3100, 0x3104 पूर्ण,
		अणु 0x3207, 0x320F पूर्ण,
		अणु 0x3300, 0x3304 पूर्ण,
		अणु 0x3500, 0x3517 पूर्ण,
		अणु 0x3600, 0x3617 पूर्ण,
		अणु 0x3700, 0x3717 पूर्ण,
		अणु 0x4000, 0x4003 पूर्ण,
	पूर्ण;

	वापस	si476x_core_element_is_in_range(property, valid_ranges,
						ARRAY_SIZE(valid_ranges)) ||
		si476x_core_element_is_in_array(property, valid_properties,
						ARRAY_SIZE(valid_properties));
पूर्ण

अटल bool si476x_core_is_valid_property_a20(काष्ठा si476x_core *core,
					      u16 property)
अणु
	अटल स्थिर u16 valid_properties[] = अणु
		0x071B,
		0x1006,
		0x2210,
		0x3401,
	पूर्ण;

	अटल स्थिर काष्ठा si476x_property_range valid_ranges[] = अणु
		अणु 0x2215, 0x2219 पूर्ण,
	पूर्ण;

	वापस	si476x_core_is_valid_property_a10(core, property) ||
		si476x_core_element_is_in_range(property, valid_ranges,
						ARRAY_SIZE(valid_ranges))  ||
		si476x_core_element_is_in_array(property, valid_properties,
						ARRAY_SIZE(valid_properties));
पूर्ण

अटल bool si476x_core_is_valid_property_a30(काष्ठा si476x_core *core,
					      u16 property)
अणु
	अटल स्थिर u16 valid_properties[] = अणु
		0x071C, 0x071D,
		0x1007, 0x1008,
		0x220F, 0x2214,
		0x2301,
		0x3105, 0x3106,
		0x3402,
	पूर्ण;

	अटल स्थिर काष्ठा si476x_property_range valid_ranges[] = अणु
		अणु 0x0405, 0x0411 पूर्ण,
		अणु 0x2008, 0x200B पूर्ण,
		अणु 0x2220, 0x2223 पूर्ण,
		अणु 0x3100, 0x3106 पूर्ण,
	पूर्ण;

	वापस	si476x_core_is_valid_property_a20(core, property) ||
		si476x_core_element_is_in_range(property, valid_ranges,
						ARRAY_SIZE(valid_ranges)) ||
		si476x_core_element_is_in_array(property, valid_properties,
						ARRAY_SIZE(valid_properties));
पूर्ण

प्रकार bool (*valid_property_pred_t) (काष्ठा si476x_core *, u16);

अटल bool si476x_core_is_valid_property(काष्ठा si476x_core *core,
					  u16 property)
अणु
	अटल स्थिर valid_property_pred_t is_valid_property[] = अणु
		[SI476X_REVISION_A10] = si476x_core_is_valid_property_a10,
		[SI476X_REVISION_A20] = si476x_core_is_valid_property_a20,
		[SI476X_REVISION_A30] = si476x_core_is_valid_property_a30,
	पूर्ण;

	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस is_valid_property[core->revision](core, property);
पूर्ण


अटल bool si476x_core_is_पढ़ोonly_property(काष्ठा si476x_core *core,
					     u16 property)
अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);

	चयन (core->revision) अणु
	हाल SI476X_REVISION_A10:
		वापस (property == 0x3200);
	हाल SI476X_REVISION_A20:
		वापस (property == 0x1006 ||
			property == 0x2210 ||
			property == 0x3200);
	हाल SI476X_REVISION_A30:
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल bool si476x_core_regmap_पढ़ोable_रेजिस्टर(काष्ठा device *dev,
						 अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा si476x_core *core = i2c_get_clientdata(client);

	वापस si476x_core_is_valid_property(core, (u16) reg);

पूर्ण

अटल bool si476x_core_regmap_writable_रेजिस्टर(काष्ठा device *dev,
						 अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा si476x_core *core = i2c_get_clientdata(client);

	वापस si476x_core_is_valid_property(core, (u16) reg) &&
		!si476x_core_is_पढ़ोonly_property(core, (u16) reg);
पूर्ण


अटल पूर्णांक si476x_core_regmap_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक val)
अणु
	वापस si476x_core_cmd_set_property(context, reg, val);
पूर्ण

अटल पूर्णांक si476x_core_regmap_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित *val)
अणु
	काष्ठा si476x_core *core = context;
	पूर्णांक err;

	err = si476x_core_cmd_get_property(core, reg);
	अगर (err < 0)
		वापस err;

	*val = err;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा regmap_config si476x_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.max_रेजिस्टर = 0x4003,

	.ग_लिखोable_reg = si476x_core_regmap_writable_रेजिस्टर,
	.पढ़ोable_reg = si476x_core_regmap_पढ़ोable_रेजिस्टर,

	.reg_पढ़ो = si476x_core_regmap_पढ़ो,
	.reg_ग_लिखो = si476x_core_regmap_ग_लिखो,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

काष्ठा regmap *devm_regmap_init_si476x(काष्ठा si476x_core *core)
अणु
	वापस devm_regmap_init(&core->client->dev, शून्य,
				core, &si476x_regmap_config);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_init_si476x);
