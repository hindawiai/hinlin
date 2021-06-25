<शैली गुरु>
/*
 * TI SYSCON regmap reset driver
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *	Suman Anna <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/reset/ti-syscon.h>

/**
 * काष्ठा ti_syscon_reset_control - reset control काष्ठाure
 * @निश्चित_offset: reset निश्चित control रेजिस्टर offset from syscon base
 * @निश्चित_bit: reset निश्चित bit in the reset निश्चित control रेजिस्टर
 * @deनिश्चित_offset: reset deनिश्चित control रेजिस्टर offset from syscon base
 * @deनिश्चित_bit: reset deनिश्चित bit in the reset deनिश्चित control रेजिस्टर
 * @status_offset: reset status रेजिस्टर offset from syscon base
 * @status_bit: reset status bit in the reset status रेजिस्टर
 * @flags: reset flag indicating how the (de)निश्चित and status are handled
 */
काष्ठा ti_syscon_reset_control अणु
	अचिन्हित पूर्णांक निश्चित_offset;
	अचिन्हित पूर्णांक निश्चित_bit;
	अचिन्हित पूर्णांक deनिश्चित_offset;
	अचिन्हित पूर्णांक deनिश्चित_bit;
	अचिन्हित पूर्णांक status_offset;
	अचिन्हित पूर्णांक status_bit;
	u32 flags;
पूर्ण;

/**
 * काष्ठा ti_syscon_reset_data - reset controller inक्रमmation काष्ठाure
 * @rcdev: reset controller entity
 * @regmap: regmap handle containing the memory-mapped reset रेजिस्टरs
 * @controls: array of reset controls
 * @nr_controls: number of controls in control array
 */
काष्ठा ti_syscon_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा regmap *regmap;
	काष्ठा ti_syscon_reset_control *controls;
	अचिन्हित पूर्णांक nr_controls;
पूर्ण;

#घोषणा to_ti_syscon_reset_data(rcdev)	\
	container_of(rcdev, काष्ठा ti_syscon_reset_data, rcdev)

/**
 * ti_syscon_reset_निश्चित() - निश्चित device reset
 * @rcdev: reset controller entity
 * @id: ID of the reset to be निश्चितed
 *
 * This function implements the reset driver op to निश्चित a device's reset.
 * This निश्चितs the reset in a manner prescribed by the reset flags.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक ti_syscon_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा ti_syscon_reset_data *data = to_ti_syscon_reset_data(rcdev);
	काष्ठा ti_syscon_reset_control *control;
	अचिन्हित पूर्णांक mask, value;

	अगर (id >= data->nr_controls)
		वापस -EINVAL;

	control = &data->controls[id];

	अगर (control->flags & ASSERT_NONE)
		वापस -ENOTSUPP; /* निश्चित not supported क्रम this reset */

	mask = BIT(control->निश्चित_bit);
	value = (control->flags & ASSERT_SET) ? mask : 0x0;

	वापस regmap_ग_लिखो_bits(data->regmap, control->निश्चित_offset, mask, value);
पूर्ण

/**
 * ti_syscon_reset_deनिश्चित() - deनिश्चित device reset
 * @rcdev: reset controller entity
 * @id: ID of reset to be deनिश्चितed
 *
 * This function implements the reset driver op to deनिश्चित a device's reset.
 * This deनिश्चितs the reset in a manner prescribed by the reset flags.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक ti_syscon_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा ti_syscon_reset_data *data = to_ti_syscon_reset_data(rcdev);
	काष्ठा ti_syscon_reset_control *control;
	अचिन्हित पूर्णांक mask, value;

	अगर (id >= data->nr_controls)
		वापस -EINVAL;

	control = &data->controls[id];

	अगर (control->flags & DEASSERT_NONE)
		वापस -ENOTSUPP; /* deनिश्चित not supported क्रम this reset */

	mask = BIT(control->deनिश्चित_bit);
	value = (control->flags & DEASSERT_SET) ? mask : 0x0;

	वापस regmap_ग_लिखो_bits(data->regmap, control->deनिश्चित_offset, mask, value);
पूर्ण

/**
 * ti_syscon_reset_status() - check device reset status
 * @rcdev: reset controller entity
 * @id: ID of the reset क्रम which the status is being requested
 *
 * This function implements the reset driver op to वापस the status of a
 * device's reset.
 *
 * Return: 0 अगर reset is deनिश्चितed, true अगर reset is निश्चितed, अन्यथा a
 * corresponding error value
 */
अटल पूर्णांक ti_syscon_reset_status(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा ti_syscon_reset_data *data = to_ti_syscon_reset_data(rcdev);
	काष्ठा ti_syscon_reset_control *control;
	अचिन्हित पूर्णांक reset_state;
	पूर्णांक ret;

	अगर (id >= data->nr_controls)
		वापस -EINVAL;

	control = &data->controls[id];

	अगर (control->flags & STATUS_NONE)
		वापस -ENOTSUPP; /* status not supported क्रम this reset */

	ret = regmap_पढ़ो(data->regmap, control->status_offset, &reset_state);
	अगर (ret)
		वापस ret;

	वापस !(reset_state & BIT(control->status_bit)) ==
		!(control->flags & STATUS_SET);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops ti_syscon_reset_ops = अणु
	.निश्चित		= ti_syscon_reset_निश्चित,
	.deनिश्चित	= ti_syscon_reset_deनिश्चित,
	.status		= ti_syscon_reset_status,
पूर्ण;

अटल पूर्णांक ti_syscon_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ti_syscon_reset_data *data;
	काष्ठा regmap *regmap;
	स्थिर __be32 *list;
	काष्ठा ti_syscon_reset_control *controls;
	पूर्णांक size, nr_controls, i;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	regmap = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	list = of_get_property(np, "ti,reset-bits", &size);
	अगर (!list || (size / माप(*list)) % 7 != 0) अणु
		dev_err(dev, "invalid DT reset description\n");
		वापस -EINVAL;
	पूर्ण

	nr_controls = (size / माप(*list)) / 7;
	controls = devm_kसुस्मृति(dev, nr_controls, माप(*controls),
				GFP_KERNEL);
	अगर (!controls)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_controls; i++) अणु
		controls[i].निश्चित_offset = be32_to_cpup(list++);
		controls[i].निश्चित_bit = be32_to_cpup(list++);
		controls[i].deनिश्चित_offset = be32_to_cpup(list++);
		controls[i].deनिश्चित_bit = be32_to_cpup(list++);
		controls[i].status_offset = be32_to_cpup(list++);
		controls[i].status_bit = be32_to_cpup(list++);
		controls[i].flags = be32_to_cpup(list++);
	पूर्ण

	data->rcdev.ops = &ti_syscon_reset_ops;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.of_node = np;
	data->rcdev.nr_resets = nr_controls;
	data->regmap = regmap;
	data->controls = controls;
	data->nr_controls = nr_controls;

	platक्रमm_set_drvdata(pdev, data);

	वापस devm_reset_controller_रेजिस्टर(dev, &data->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_syscon_reset_of_match[] = अणु
	अणु .compatible = "ti,syscon-reset", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_syscon_reset_of_match);

अटल काष्ठा platक्रमm_driver ti_syscon_reset_driver = अणु
	.probe = ti_syscon_reset_probe,
	.driver = अणु
		.name = "ti-syscon-reset",
		.of_match_table = ti_syscon_reset_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_syscon_reset_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
MODULE_DESCRIPTION("TI SYSCON Regmap Reset Driver");
MODULE_LICENSE("GPL v2");
