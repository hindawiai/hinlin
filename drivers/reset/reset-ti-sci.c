<शैली गुरु>
/*
 * Texas Instrument's System Control Interface (TI-SCI) reset driver
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
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

#समावेश <linux/idr.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>

/**
 * काष्ठा ti_sci_reset_control - reset control काष्ठाure
 * @dev_id: SoC-specअगरic device identअगरier
 * @reset_mask: reset mask to use क्रम toggling reset
 * @lock: synchronize reset_mask पढ़ो-modअगरy-ग_लिखोs
 */
काष्ठा ti_sci_reset_control अणु
	u32 dev_id;
	u32 reset_mask;
	काष्ठा mutex lock;
पूर्ण;

/**
 * काष्ठा ti_sci_reset_data - reset controller inक्रमmation काष्ठाure
 * @rcdev: reset controller entity
 * @dev: reset controller device poपूर्णांकer
 * @sci: TI SCI handle used क्रम communication with प्रणाली controller
 * @idr: idr काष्ठाure क्रम mapping ids to reset control काष्ठाures
 */
काष्ठा ti_sci_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा device *dev;
	स्थिर काष्ठा ti_sci_handle *sci;
	काष्ठा idr idr;
पूर्ण;

#घोषणा to_ti_sci_reset_data(p)	\
	container_of((p), काष्ठा ti_sci_reset_data, rcdev)

/**
 * ti_sci_reset_set() - program a device's reset
 * @rcdev: reset controller entity
 * @id: ID of the reset to toggle
 * @निश्चित: boolean flag to indicate निश्चित or deनिश्चित
 *
 * This is a common पूर्णांकernal function used to निश्चित or deनिश्चित a device's
 * reset using the TI SCI protocol. The device's reset is निश्चितed अगर the
 * @निश्चित argument is true, or deनिश्चितed अगर @निश्चित argument is false.
 * The mechanism itself is a पढ़ो-modअगरy-ग_लिखो procedure, the current device
 * reset रेजिस्टर is पढ़ो using a TI SCI device operation, the new value is
 * set or un-set using the reset's mask, and the new reset value written by
 * using another TI SCI device operation.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक ti_sci_reset_set(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा ti_sci_reset_data *data = to_ti_sci_reset_data(rcdev);
	स्थिर काष्ठा ti_sci_handle *sci = data->sci;
	स्थिर काष्ठा ti_sci_dev_ops *dev_ops = &sci->ops.dev_ops;
	काष्ठा ti_sci_reset_control *control;
	u32 reset_state;
	पूर्णांक ret;

	control = idr_find(&data->idr, id);
	अगर (!control)
		वापस -EINVAL;

	mutex_lock(&control->lock);

	ret = dev_ops->get_device_resets(sci, control->dev_id, &reset_state);
	अगर (ret)
		जाओ out;

	अगर (निश्चित)
		reset_state |= control->reset_mask;
	अन्यथा
		reset_state &= ~control->reset_mask;

	ret = dev_ops->set_device_resets(sci, control->dev_id, reset_state);
out:
	mutex_unlock(&control->lock);

	वापस ret;
पूर्ण

/**
 * ti_sci_reset_निश्चित() - निश्चित device reset
 * @rcdev: reset controller entity
 * @id: ID of the reset to be निश्चितed
 *
 * This function implements the reset driver op to निश्चित a device's reset
 * using the TI SCI protocol. This invokes the function ti_sci_reset_set()
 * with the corresponding parameters as passed in, but with the @निश्चित
 * argument set to true क्रम निश्चितing the reset.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक ti_sci_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस ti_sci_reset_set(rcdev, id, true);
पूर्ण

/**
 * ti_sci_reset_deनिश्चित() - deनिश्चित device reset
 * @rcdev: reset controller entity
 * @id: ID of the reset to be deनिश्चितed
 *
 * This function implements the reset driver op to deनिश्चित a device's reset
 * using the TI SCI protocol. This invokes the function ti_sci_reset_set()
 * with the corresponding parameters as passed in, but with the @निश्चित
 * argument set to false क्रम deनिश्चितing the reset.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक ti_sci_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस ti_sci_reset_set(rcdev, id, false);
पूर्ण

/**
 * ti_sci_reset_status() - check device reset status
 * @rcdev: reset controller entity
 * @id: ID of reset to be checked
 *
 * This function implements the reset driver op to वापस the status of a
 * device's reset using the TI SCI protocol. The reset रेजिस्टर value is पढ़ो
 * by invoking the TI SCI device operation .get_device_resets(), and the
 * status of the specअगरic reset is extracted and वापसed using this reset's
 * reset mask.
 *
 * Return: 0 अगर reset is deनिश्चितed, or a non-zero value अगर reset is निश्चितed
 */
अटल पूर्णांक ti_sci_reset_status(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा ti_sci_reset_data *data = to_ti_sci_reset_data(rcdev);
	स्थिर काष्ठा ti_sci_handle *sci = data->sci;
	स्थिर काष्ठा ti_sci_dev_ops *dev_ops = &sci->ops.dev_ops;
	काष्ठा ti_sci_reset_control *control;
	u32 reset_state;
	पूर्णांक ret;

	control = idr_find(&data->idr, id);
	अगर (!control)
		वापस -EINVAL;

	ret = dev_ops->get_device_resets(sci, control->dev_id, &reset_state);
	अगर (ret)
		वापस ret;

	वापस reset_state & control->reset_mask;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops ti_sci_reset_ops = अणु
	.निश्चित		= ti_sci_reset_निश्चित,
	.deनिश्चित	= ti_sci_reset_deनिश्चित,
	.status		= ti_sci_reset_status,
पूर्ण;

/**
 * ti_sci_reset_of_xlate() - translate a set of OF arguments to a reset ID
 * @rcdev: reset controller entity
 * @reset_spec: OF reset argument specअगरier
 *
 * This function perक्रमms the translation of the reset argument specअगरier
 * values defined in a reset consumer device node. The function allocates a
 * reset control काष्ठाure क्रम that device reset, and will be used by the
 * driver क्रम perक्रमming any reset functions on that reset. An idr काष्ठाure
 * is allocated and used to map to the reset control काष्ठाure. This idr
 * is used by the driver to करो reset lookups.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक ti_sci_reset_of_xlate(काष्ठा reset_controller_dev *rcdev,
				 स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	काष्ठा ti_sci_reset_data *data = to_ti_sci_reset_data(rcdev);
	काष्ठा ti_sci_reset_control *control;

	अगर (WARN_ON(reset_spec->args_count != rcdev->of_reset_n_cells))
		वापस -EINVAL;

	control = devm_kzalloc(data->dev, माप(*control), GFP_KERNEL);
	अगर (!control)
		वापस -ENOMEM;

	control->dev_id = reset_spec->args[0];
	control->reset_mask = reset_spec->args[1];
	mutex_init(&control->lock);

	वापस idr_alloc(&data->idr, control, 0, 0, GFP_KERNEL);
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_sci_reset_of_match[] = अणु
	अणु .compatible = "ti,sci-reset", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sci_reset_of_match);

अटल पूर्णांक ti_sci_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_sci_reset_data *data;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->sci = devm_ti_sci_get_handle(&pdev->dev);
	अगर (IS_ERR(data->sci))
		वापस PTR_ERR(data->sci);

	data->rcdev.ops = &ti_sci_reset_ops;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.of_node = pdev->dev.of_node;
	data->rcdev.of_reset_n_cells = 2;
	data->rcdev.of_xlate = ti_sci_reset_of_xlate;
	data->dev = &pdev->dev;
	idr_init(&data->idr);

	platक्रमm_set_drvdata(pdev, data);

	वापस reset_controller_रेजिस्टर(&data->rcdev);
पूर्ण

अटल पूर्णांक ti_sci_reset_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_sci_reset_data *data = platक्रमm_get_drvdata(pdev);

	reset_controller_unरेजिस्टर(&data->rcdev);

	idr_destroy(&data->idr);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_sci_reset_driver = अणु
	.probe = ti_sci_reset_probe,
	.हटाओ = ti_sci_reset_हटाओ,
	.driver = अणु
		.name = "ti-sci-reset",
		.of_match_table = ti_sci_reset_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_sci_reset_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TI System Control Interface (TI SCI) Reset driver");
MODULE_LICENSE("GPL v2");
