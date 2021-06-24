<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/fixed.h>

काष्ठा fixed_regulator_data अणु
	काष्ठा fixed_voltage_config cfg;
	काष्ठा regulator_init_data init_data;
	काष्ठा platक्रमm_device pdev;
पूर्ण;

अटल व्योम regulator_fixed_release(काष्ठा device *dev)
अणु
	काष्ठा fixed_regulator_data *data = container_of(dev,
			काष्ठा fixed_regulator_data, pdev.dev);
	kमुक्त(data->cfg.supply_name);
	kमुक्त(data);
पूर्ण

/**
 * regulator_रेजिस्टर_fixed_name - रेजिस्टर a no-op fixed regulator
 * @id: platक्रमm device id
 * @name: name to be used क्रम the regulator
 * @supplies: consumers क्रम this regulator
 * @num_supplies: number of consumers
 * @uv: voltage in microvolts
 */
काष्ठा platक्रमm_device *regulator_रेजिस्टर_always_on(पूर्णांक id, स्थिर अक्षर *name,
	काष्ठा regulator_consumer_supply *supplies, पूर्णांक num_supplies, पूर्णांक uv)
अणु
	काष्ठा fixed_regulator_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	data->cfg.supply_name = kstrdup(name, GFP_KERNEL);
	अगर (!data->cfg.supply_name) अणु
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	data->cfg.microvolts = uv;
	data->cfg.enabled_at_boot = 1;
	data->cfg.init_data = &data->init_data;

	data->init_data.स्थिरraपूर्णांकs.always_on = 1;
	data->init_data.consumer_supplies = supplies;
	data->init_data.num_consumer_supplies = num_supplies;

	data->pdev.name = "reg-fixed-voltage";
	data->pdev.id = id;
	data->pdev.dev.platक्रमm_data = &data->cfg;
	data->pdev.dev.release = regulator_fixed_release;

	platक्रमm_device_रेजिस्टर(&data->pdev);

	वापस &data->pdev;
पूर्ण
