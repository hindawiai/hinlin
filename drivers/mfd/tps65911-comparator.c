<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tps65910.c  --  TI TPS6591x
 *
 * Copyright 2010 Texas Instruments Inc.
 *
 * Author: Jorge Eduarकरो Candelaria <jedu@slimlogic.co.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mfd/tps65910.h>

#घोषणा COMP1					0
#घोषणा COMP2					1

/* Comparator 1 voltage selection table in millivolts */
अटल स्थिर u16 COMP_VSEL_TABLE[] = अणु
	0, 2500, 2500, 2500, 2500, 2550, 2600, 2650,
	2700, 2750, 2800, 2850, 2900, 2950, 3000, 3050,
	3100, 3150, 3200, 3250, 3300, 3350, 3400, 3450,
	3500,
पूर्ण;

काष्ठा comparator अणु
	स्थिर अक्षर *name;
	पूर्णांक reg;
	पूर्णांक uV_max;
	स्थिर u16 *vsel_table;
पूर्ण;

अटल काष्ठा comparator tps_comparators[] = अणु
	अणु
		.name = "COMP1",
		.reg = TPS65911_VMBCH,
		.uV_max = 3500,
		.vsel_table = COMP_VSEL_TABLE,
	पूर्ण,
	अणु
		.name = "COMP2",
		.reg = TPS65911_VMBCH2,
		.uV_max = 3500,
		.vsel_table = COMP_VSEL_TABLE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक comp_threshold_set(काष्ठा tps65910 *tps65910, पूर्णांक id, पूर्णांक voltage)
अणु
	काष्ठा comparator tps_comp = tps_comparators[id];
	पूर्णांक curr_voltage = 0;
	पूर्णांक ret;
	u8 index = 0, val;

	जबतक (curr_voltage < tps_comp.uV_max) अणु
		curr_voltage = tps_comp.vsel_table[index];
		अगर (curr_voltage >= voltage)
			अवरोध;
		अन्यथा अगर (curr_voltage < voltage)
			index ++;
	पूर्ण

	अगर (curr_voltage > tps_comp.uV_max)
		वापस -EINVAL;

	val = index << 1;
	ret = regmap_ग_लिखो(tps65910->regmap, tps_comp.reg, val);

	वापस ret;
पूर्ण

अटल पूर्णांक comp_threshold_get(काष्ठा tps65910 *tps65910, पूर्णांक id)
अणु
	काष्ठा comparator tps_comp = tps_comparators[id];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps65910->regmap, tps_comp.reg, &val);
	अगर (ret < 0)
		वापस ret;

	val >>= 1;
	वापस tps_comp.vsel_table[val];
पूर्ण

अटल sमाप_प्रकार comp_threshold_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tps65910 *tps65910 = dev_get_drvdata(dev->parent);
	काष्ठा attribute comp_attr = attr->attr;
	पूर्णांक id, uVolt;

	अगर (!म_भेद(comp_attr.name, "comp1_threshold"))
		id = COMP1;
	अन्यथा अगर (!म_भेद(comp_attr.name, "comp2_threshold"))
		id = COMP2;
	अन्यथा
		वापस -EINVAL;

	uVolt = comp_threshold_get(tps65910, id);

	वापस प्र_लिखो(buf, "%d\n", uVolt);
पूर्ण

अटल DEVICE_ATTR(comp1_threshold, S_IRUGO, comp_threshold_show, शून्य);
अटल DEVICE_ATTR(comp2_threshold, S_IRUGO, comp_threshold_show, शून्य);

अटल पूर्णांक tps65911_comparator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65910 *tps65910 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65910_board *pdata = dev_get_platdata(tps65910->dev);
	पूर्णांक ret;

	ret = comp_threshold_set(tps65910, COMP1,  pdata->vmbch_threshold);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot set COMP1 threshold\n");
		वापस ret;
	पूर्ण

	ret = comp_threshold_set(tps65910, COMP2, pdata->vmbch2_threshold);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot set COMP2 threshold\n");
		वापस ret;
	पूर्ण

	/* Create sysfs entry */
	ret = device_create_file(&pdev->dev, &dev_attr_comp1_threshold);
	अगर (ret < 0)
		dev_err(&pdev->dev, "failed to add COMP1 sysfs file\n");

	ret = device_create_file(&pdev->dev, &dev_attr_comp2_threshold);
	अगर (ret < 0)
		dev_err(&pdev->dev, "failed to add COMP2 sysfs file\n");

	वापस ret;
पूर्ण

अटल पूर्णांक tps65911_comparator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65910 *tps65910;

	tps65910 = dev_get_drvdata(pdev->dev.parent);
	device_हटाओ_file(&pdev->dev, &dev_attr_comp2_threshold);
	device_हटाओ_file(&pdev->dev, &dev_attr_comp1_threshold);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps65911_comparator_driver = अणु
	.driver = अणु
		.name = "tps65911-comparator",
	पूर्ण,
	.probe = tps65911_comparator_probe,
	.हटाओ = tps65911_comparator_हटाओ,
पूर्ण;

अटल पूर्णांक __init tps65911_comparator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps65911_comparator_driver);
पूर्ण
subsys_initcall(tps65911_comparator_init);

अटल व्योम __निकास tps65911_comparator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps65911_comparator_driver);
पूर्ण
module_निकास(tps65911_comparator_निकास);

MODULE_AUTHOR("Jorge Eduardo Candelaria <jedu@slimlogic.co.uk>");
MODULE_DESCRIPTION("TPS65911 comparator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps65911-comparator");
