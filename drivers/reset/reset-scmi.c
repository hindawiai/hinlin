<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARM System Control and Management Interface (ARM SCMI) reset driver
 *
 * Copyright (C) 2019-2021 ARM Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/scmi_protocol.h>

अटल स्थिर काष्ठा scmi_reset_proto_ops *reset_ops;

/**
 * काष्ठा scmi_reset_data - reset controller inक्रमmation काष्ठाure
 * @rcdev: reset controller entity
 * @ph: ARM SCMI protocol handle used क्रम communication with प्रणाली controller
 */
काष्ठा scmi_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	स्थिर काष्ठा scmi_protocol_handle *ph;
पूर्ण;

#घोषणा to_scmi_reset_data(p)	container_of((p), काष्ठा scmi_reset_data, rcdev)
#घोषणा to_scmi_handle(p)	(to_scmi_reset_data(p)->ph)

/**
 * scmi_reset_निश्चित() - निश्चित device reset
 * @rcdev: reset controller entity
 * @id: ID of the reset to be निश्चितed
 *
 * This function implements the reset driver op to निश्चित a device's reset
 * using the ARM SCMI protocol.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक
scmi_reset_निश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	स्थिर काष्ठा scmi_protocol_handle *ph = to_scmi_handle(rcdev);

	वापस reset_ops->निश्चित(ph, id);
पूर्ण

/**
 * scmi_reset_deनिश्चित() - deनिश्चित device reset
 * @rcdev: reset controller entity
 * @id: ID of the reset to be deनिश्चितed
 *
 * This function implements the reset driver op to deनिश्चित a device's reset
 * using the ARM SCMI protocol.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक
scmi_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	स्थिर काष्ठा scmi_protocol_handle *ph = to_scmi_handle(rcdev);

	वापस reset_ops->deनिश्चित(ph, id);
पूर्ण

/**
 * scmi_reset_reset() - reset the device
 * @rcdev: reset controller entity
 * @id: ID of the reset संकेत to be reset(निश्चित + deनिश्चित)
 *
 * This function implements the reset driver op to trigger a device's
 * reset संकेत using the ARM SCMI protocol.
 *
 * Return: 0 क्रम successful request, अन्यथा a corresponding error value
 */
अटल पूर्णांक
scmi_reset_reset(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	स्थिर काष्ठा scmi_protocol_handle *ph = to_scmi_handle(rcdev);

	वापस reset_ops->reset(ph, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops scmi_reset_ops = अणु
	.निश्चित		= scmi_reset_निश्चित,
	.deनिश्चित	= scmi_reset_deनिश्चित,
	.reset		= scmi_reset_reset,
पूर्ण;

अटल पूर्णांक scmi_reset_probe(काष्ठा scmi_device *sdev)
अणु
	काष्ठा scmi_reset_data *data;
	काष्ठा device *dev = &sdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा scmi_handle *handle = sdev->handle;
	काष्ठा scmi_protocol_handle *ph;

	अगर (!handle)
		वापस -ENODEV;

	reset_ops = handle->devm_protocol_get(sdev, SCMI_PROTOCOL_RESET, &ph);
	अगर (IS_ERR(reset_ops))
		वापस PTR_ERR(reset_ops);

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->rcdev.ops = &scmi_reset_ops;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.of_node = np;
	data->rcdev.nr_resets = reset_ops->num_करोमुख्यs_get(ph);
	data->ph = ph;

	वापस devm_reset_controller_रेजिस्टर(dev, &data->rcdev);
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_id_table[] = अणु
	अणु SCMI_PROTOCOL_RESET, "reset" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(scmi, scmi_id_table);

अटल काष्ठा scmi_driver scmi_reset_driver = अणु
	.name = "scmi-reset",
	.probe = scmi_reset_probe,
	.id_table = scmi_id_table,
पूर्ण;
module_scmi_driver(scmi_reset_driver);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCMI reset controller driver");
MODULE_LICENSE("GPL v2");
