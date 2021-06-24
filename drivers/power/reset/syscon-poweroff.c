<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic Syscon Poweroff Driver
 *
 * Copyright (c) 2015, National Instruments Corp.
 * Author: Moritz Fischer <moritz.fischer@ettus.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>

अटल काष्ठा regmap *map;
अटल u32 offset;
अटल u32 value;
अटल u32 mask;

अटल व्योम syscon_घातeroff(व्योम)
अणु
	/* Issue the घातeroff */
	regmap_update_bits(map, offset, mask, value);

	mdelay(1000);

	pr_emerg("Unable to poweroff system\n");
पूर्ण

अटल पूर्णांक syscon_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक mask_err, value_err;

	map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node, "regmap");
	अगर (IS_ERR(map)) अणु
		dev_err(&pdev->dev, "unable to get syscon");
		वापस PTR_ERR(map);
	पूर्ण

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "offset", &offset)) अणु
		dev_err(&pdev->dev, "unable to read 'offset'");
		वापस -EINVAL;
	पूर्ण

	value_err = of_property_पढ़ो_u32(pdev->dev.of_node, "value", &value);
	mask_err = of_property_पढ़ो_u32(pdev->dev.of_node, "mask", &mask);
	अगर (value_err && mask_err) अणु
		dev_err(&pdev->dev, "unable to read 'value' and 'mask'");
		वापस -EINVAL;
	पूर्ण

	अगर (value_err) अणु
		/* support old binding */
		value = mask;
		mask = 0xFFFFFFFF;
	पूर्ण अन्यथा अगर (mask_err) अणु
		/* support value without mask*/
		mask = 0xFFFFFFFF;
	पूर्ण

	अगर (pm_घातer_off) अणु
		dev_err(&pdev->dev, "pm_power_off already claimed for %ps",
			pm_घातer_off);
		वापस -EBUSY;
	पूर्ण

	pm_घातer_off = syscon_घातeroff;

	वापस 0;
पूर्ण

अटल पूर्णांक syscon_घातeroff_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == syscon_घातeroff)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id syscon_घातeroff_of_match[] = अणु
	अणु .compatible = "syscon-poweroff" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver syscon_घातeroff_driver = अणु
	.probe = syscon_घातeroff_probe,
	.हटाओ = syscon_घातeroff_हटाओ,
	.driver = अणु
		.name = "syscon-poweroff",
		.of_match_table = syscon_घातeroff_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init syscon_घातeroff_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&syscon_घातeroff_driver);
पूर्ण
device_initcall(syscon_घातeroff_रेजिस्टर);
