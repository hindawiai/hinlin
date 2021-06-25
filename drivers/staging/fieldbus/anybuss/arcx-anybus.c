<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arcx Anybus-S Controller driver
 *
 * Copyright (C) 2018 Arcx Inc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regmap.h>

/* move to <linux/anybuss-controller.h> when taking this out of staging */
#समावेश "anybuss-controller.h"

#घोषणा CPLD_STATUS1		0x80
#घोषणा CPLD_CONTROL		0x80
#घोषणा CPLD_CONTROL_CRST	0x40
#घोषणा CPLD_CONTROL_RST1	0x04
#घोषणा CPLD_CONTROL_RST2	0x80
#घोषणा CPLD_STATUS1_AB		0x02
#घोषणा CPLD_STATUS1_CAN_POWER	0x01
#घोषणा CPLD_DESIGN_LO		0x81
#घोषणा CPLD_DESIGN_HI		0x82
#घोषणा CPLD_CAP		0x83
#घोषणा CPLD_CAP_COMPAT		0x01
#घोषणा CPLD_CAP_SEP_RESETS	0x02

काष्ठा controller_priv अणु
	काष्ठा device *class_dev;
	bool common_reset;
	काष्ठा gpio_desc *reset_gpiod;
	व्योम __iomem *cpld_base;
	काष्ठा mutex ctrl_lock; /* protects CONTROL रेजिस्टर */
	u8 control_reg;
	अक्षर version[3];
	u16 design_no;
पूर्ण;

अटल व्योम करो_reset(काष्ठा controller_priv *cd, u8 rst_bit, bool reset)
अणु
	mutex_lock(&cd->ctrl_lock);
	/*
	 * CPLD_CONTROL is ग_लिखो-only, so cache its value in
	 * cd->control_reg
	 */
	अगर (reset)
		cd->control_reg &= ~rst_bit;
	अन्यथा
		cd->control_reg |= rst_bit;
	ग_लिखोb(cd->control_reg, cd->cpld_base + CPLD_CONTROL);
	/*
	 * h/w work-around:
	 * the hardware is 'too fast', so a reset followed by an immediate
	 * not-reset will _not_ change the anybus reset line in any way,
	 * losing the reset. to prevent this from happening, पूर्णांकroduce
	 * a minimum reset duration.
	 * Verअगरied minimum safe duration required using a scope
	 * on 14-June-2018: 100 us.
	 */
	अगर (reset)
		usleep_range(100, 200);
	mutex_unlock(&cd->ctrl_lock);
पूर्ण

अटल पूर्णांक anybuss_reset(काष्ठा controller_priv *cd,
			 अचिन्हित दीर्घ id, bool reset)
अणु
	अगर (id >= 2)
		वापस -EINVAL;
	अगर (cd->common_reset)
		करो_reset(cd, CPLD_CONTROL_CRST, reset);
	अन्यथा
		करो_reset(cd, id ? CPLD_CONTROL_RST2 : CPLD_CONTROL_RST1, reset);
	वापस 0;
पूर्ण

अटल व्योम export_reset_0(काष्ठा device *dev, bool निश्चित)
अणु
	काष्ठा controller_priv *cd = dev_get_drvdata(dev);

	anybuss_reset(cd, 0, निश्चित);
पूर्ण

अटल व्योम export_reset_1(काष्ठा device *dev, bool निश्चित)
अणु
	काष्ठा controller_priv *cd = dev_get_drvdata(dev);

	anybuss_reset(cd, 1, निश्चित);
पूर्ण

/*
 * parallel bus limitation:
 *
 * the anybus is 8-bit wide. we can't assume that the hardware will translate
 * word accesses on the parallel bus to multiple byte-accesses on the anybus.
 *
 * the imx WEIM bus करोes not provide this type of translation.
 *
 * to be safe, we will limit parallel bus accesses to a single byte
 * at a समय क्रम now.
 */

अटल स्थिर काष्ठा regmap_config arcx_regmap_cfg = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.max_रेजिस्टर = 0x7ff,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	/*
	 * single-byte parallel bus accesses are atomic, so करोn't
	 * require any synchronization.
	 */
	.disable_locking = true,
पूर्ण;

अटल काष्ठा regmap *create_parallel_regmap(काष्ठा platक्रमm_device *pdev,
					     पूर्णांक idx)
अणु
	व्योम __iomem *base;
	काष्ठा device *dev = &pdev->dev;

	base = devm_platक्रमm_ioremap_resource(pdev, idx + 1);
	अगर (IS_ERR(base))
		वापस ERR_CAST(base);
	वापस devm_regmap_init_mmio(dev, base, &arcx_regmap_cfg);
पूर्ण

अटल काष्ठा anybuss_host *
create_anybus_host(काष्ठा platक्रमm_device *pdev, पूर्णांक idx)
अणु
	काष्ठा anybuss_ops ops = अणुपूर्ण;

	चयन (idx) अणु
	हाल 0:
		ops.reset = export_reset_0;
		अवरोध;
	हाल 1:
		ops.reset = export_reset_1;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	ops.host_idx = idx;
	ops.regmap = create_parallel_regmap(pdev, idx);
	अगर (IS_ERR(ops.regmap))
		वापस ERR_CAST(ops.regmap);
	ops.irq = platक्रमm_get_irq(pdev, idx);
	अगर (ops.irq <= 0)
		वापस ERR_PTR(-EINVAL);
	वापस devm_anybuss_host_common_probe(&pdev->dev, &ops);
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा controller_priv *cd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", cd->version);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार design_number_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा controller_priv *cd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", cd->design_no);
पूर्ण
अटल DEVICE_ATTR_RO(design_number);

अटल काष्ठा attribute *controller_attributes[] = अणु
	&dev_attr_version.attr,
	&dev_attr_design_number.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group controller_attribute_group = अणु
	.attrs = controller_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *controller_attribute_groups[] = अणु
	&controller_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम controller_device_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक can_घातer_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा controller_priv *cd = rdev_get_drvdata(rdev);

	वापस !(पढ़ोb(cd->cpld_base + CPLD_STATUS1) & CPLD_STATUS1_CAN_POWER);
पूर्ण

अटल स्थिर काष्ठा regulator_ops can_घातer_ops = अणु
	.is_enabled = can_घातer_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc can_घातer_desc = अणु
	.name = "regulator-can-power",
	.id = -1,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.ops = &can_घातer_ops,
पूर्ण;

अटल काष्ठा class *controller_class;
अटल DEFINE_IDA(controller_index_ida);

अटल पूर्णांक controller_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा controller_priv *cd;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *regulator;
	पूर्णांक err, id;
	काष्ठा anybuss_host *host;
	u8 status1, cap;

	cd = devm_kzalloc(dev, माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस -ENOMEM;
	dev_set_drvdata(dev, cd);
	mutex_init(&cd->ctrl_lock);
	cd->reset_gpiod = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cd->reset_gpiod))
		वापस PTR_ERR(cd->reset_gpiod);

	/* CPLD control memory, sits at index 0 */
	cd->cpld_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cd->cpld_base)) अणु
		dev_err(dev,
			"failed to map cpld base address\n");
		err = PTR_ERR(cd->cpld_base);
		जाओ out_reset;
	पूर्ण

	/* identअगरy cpld */
	status1 = पढ़ोb(cd->cpld_base + CPLD_STATUS1);
	cd->design_no = (पढ़ोb(cd->cpld_base + CPLD_DESIGN_HI) << 8) |
				पढ़ोb(cd->cpld_base + CPLD_DESIGN_LO);
	snम_लिखो(cd->version, माप(cd->version), "%c%d",
		 'A' + ((status1 >> 5) & 0x7),
		 (status1 >> 2) & 0x7);
	dev_info(dev, "design number %d, revision %s\n",
		 cd->design_no,
		cd->version);
	cap = पढ़ोb(cd->cpld_base + CPLD_CAP);
	अगर (!(cap & CPLD_CAP_COMPAT)) अणु
		dev_err(dev, "unsupported controller [cap=0x%02X]", cap);
		err = -ENODEV;
		जाओ out_reset;
	पूर्ण

	अगर (status1 & CPLD_STATUS1_AB) अणु
		dev_info(dev, "has anybus-S slot(s)");
		cd->common_reset = !(cap & CPLD_CAP_SEP_RESETS);
		dev_info(dev, "supports %s", cd->common_reset ?
			"a common reset" : "separate resets");
		क्रम (id = 0; id < 2; id++) अणु
			host = create_anybus_host(pdev, id);
			अगर (!IS_ERR(host))
				जारी;
			err = PTR_ERR(host);
			/* -ENODEV is fine, it just means no card detected */
			अगर (err != -ENODEV)
				जाओ out_reset;
		पूर्ण
	पूर्ण

	id = ida_simple_get(&controller_index_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		err = id;
		जाओ out_reset;
	पूर्ण
	/* export can घातer पढ़ोout as a regulator */
	config.dev = dev;
	config.driver_data = cd;
	regulator = devm_regulator_रेजिस्टर(dev, &can_घातer_desc, &config);
	अगर (IS_ERR(regulator)) अणु
		err = PTR_ERR(regulator);
		जाओ out_ida;
	पूर्ण
	/* make controller info visible to userspace */
	cd->class_dev = kzalloc(माप(*cd->class_dev), GFP_KERNEL);
	अगर (!cd->class_dev) अणु
		err = -ENOMEM;
		जाओ out_ida;
	पूर्ण
	cd->class_dev->class = controller_class;
	cd->class_dev->groups = controller_attribute_groups;
	cd->class_dev->parent = dev;
	cd->class_dev->id = id;
	cd->class_dev->release = controller_device_release;
	dev_set_name(cd->class_dev, "%d", cd->class_dev->id);
	dev_set_drvdata(cd->class_dev, cd);
	err = device_रेजिस्टर(cd->class_dev);
	अगर (err)
		जाओ out_dev;
	वापस 0;
out_dev:
	put_device(cd->class_dev);
out_ida:
	ida_simple_हटाओ(&controller_index_ida, id);
out_reset:
	gpiod_set_value_cansleep(cd->reset_gpiod, 1);
	वापस err;
पूर्ण

अटल पूर्णांक controller_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा controller_priv *cd = platक्रमm_get_drvdata(pdev);
	पूर्णांक id = cd->class_dev->id;

	device_unरेजिस्टर(cd->class_dev);
	ida_simple_हटाओ(&controller_index_ida, id);
	gpiod_set_value_cansleep(cd->reset_gpiod, 1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id controller_of_match[] = अणु
	अणु .compatible = "arcx,anybus-controller" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, controller_of_match);

अटल काष्ठा platक्रमm_driver controller_driver = अणु
	.probe = controller_probe,
	.हटाओ = controller_हटाओ,
	.driver		= अणु
		.name   = "arcx-anybus-controller",
		.of_match_table	= of_match_ptr(controller_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init controller_init(व्योम)
अणु
	पूर्णांक err;

	controller_class = class_create(THIS_MODULE, "arcx_anybus_controller");
	अगर (IS_ERR(controller_class))
		वापस PTR_ERR(controller_class);
	err = platक्रमm_driver_रेजिस्टर(&controller_driver);
	अगर (err)
		class_destroy(controller_class);

	वापस err;
पूर्ण

अटल व्योम __निकास controller_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&controller_driver);
	class_destroy(controller_class);
	ida_destroy(&controller_index_ida);
पूर्ण

module_init(controller_init);
module_निकास(controller_निकास);

MODULE_DESCRIPTION("Arcx Anybus-S Controller driver");
MODULE_AUTHOR("Sven Van Asbroeck <TheSven73@gmail.com>");
MODULE_LICENSE("GPL v2");
