<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Load Analog Devices SigmaStudio firmware files
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#समावेश <linux/regmap.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>

#समावेश "sigmadsp.h"

अटल पूर्णांक sigmadsp_ग_लिखो_regmap(व्योम *control_data,
	अचिन्हित पूर्णांक addr, स्थिर uपूर्णांक8_t data[], माप_प्रकार len)
अणु
	वापस regmap_raw_ग_लिखो(control_data, addr,
		data, len);
पूर्ण

अटल पूर्णांक sigmadsp_पढ़ो_regmap(व्योम *control_data,
	अचिन्हित पूर्णांक addr, uपूर्णांक8_t data[], माप_प्रकार len)
अणु
	वापस regmap_raw_पढ़ो(control_data, addr,
		data, len);
पूर्ण

/**
 * devm_sigmadsp_init_regmap() - Initialize SigmaDSP instance
 * @dev: The parent device
 * @regmap: Regmap instance to use
 * @ops: The sigmadsp_ops to use क्रम this instance
 * @firmware_name: Name of the firmware file to load
 *
 * Allocates a SigmaDSP instance and loads the specअगरied firmware file.
 *
 * Returns a poपूर्णांकer to a काष्ठा sigmadsp on success, or a PTR_ERR() on error.
 */
काष्ठा sigmadsp *devm_sigmadsp_init_regmap(काष्ठा device *dev,
	काष्ठा regmap *regmap, स्थिर काष्ठा sigmadsp_ops *ops,
	स्थिर अक्षर *firmware_name)
अणु
	काष्ठा sigmadsp *sigmadsp;

	sigmadsp = devm_sigmadsp_init(dev, ops, firmware_name);
	अगर (IS_ERR(sigmadsp))
		वापस sigmadsp;

	sigmadsp->control_data = regmap;
	sigmadsp->ग_लिखो = sigmadsp_ग_लिखो_regmap;
	sigmadsp->पढ़ो = sigmadsp_पढ़ो_regmap;

	वापस sigmadsp;
पूर्ण
EXPORT_SYMBOL_GPL(devm_sigmadsp_init_regmap);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("SigmaDSP regmap firmware loader");
MODULE_LICENSE("GPL");
