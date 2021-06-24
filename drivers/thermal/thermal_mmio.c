<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

काष्ठा thermal_mmio अणु
	व्योम __iomem *mmio_base;
	u32 (*पढ़ो_mmio)(व्योम __iomem *mmio_base);
	u32 mask;
	पूर्णांक factor;
पूर्ण;

अटल u32 thermal_mmio_पढ़ोb(व्योम __iomem *mmio_base)
अणु
	वापस पढ़ोb(mmio_base);
पूर्ण

अटल पूर्णांक thermal_mmio_get_temperature(व्योम *निजी, पूर्णांक *temp)
अणु
	पूर्णांक t;
	काष्ठा thermal_mmio *sensor =
		(काष्ठा thermal_mmio *)निजी;

	t = sensor->पढ़ो_mmio(sensor->mmio_base) & sensor->mask;
	t *= sensor->factor;

	*temp = t;

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_of_device_ops thermal_mmio_ops = अणु
	.get_temp = thermal_mmio_get_temperature,
पूर्ण;

अटल पूर्णांक thermal_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *resource;
	काष्ठा thermal_mmio *sensor;
	पूर्णांक (*sensor_init_func)(काष्ठा platक्रमm_device *pdev,
				काष्ठा thermal_mmio *sensor);
	काष्ठा thermal_zone_device *thermal_zone;
	पूर्णांक ret;
	पूर्णांक temperature;

	sensor = devm_kzalloc(&pdev->dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sensor->mmio_base = devm_ioremap_resource(&pdev->dev, resource);
	अगर (IS_ERR(sensor->mmio_base))
		वापस PTR_ERR(sensor->mmio_base);

	sensor_init_func = device_get_match_data(&pdev->dev);
	अगर (sensor_init_func) अणु
		ret = sensor_init_func(pdev, sensor);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed to initialize sensor (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	thermal_zone = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev,
							    0,
							    sensor,
							    &thermal_mmio_ops);
	अगर (IS_ERR(thermal_zone)) अणु
		dev_err(&pdev->dev,
			"failed to register sensor (%ld)\n",
			PTR_ERR(thermal_zone));
		वापस PTR_ERR(thermal_zone);
	पूर्ण

	thermal_mmio_get_temperature(sensor, &temperature);
	dev_info(&pdev->dev,
		 "thermal mmio sensor %s registered, current temperature: %d\n",
		 pdev->name, temperature);

	वापस 0;
पूर्ण

अटल पूर्णांक al_thermal_init(काष्ठा platक्रमm_device *pdev,
			   काष्ठा thermal_mmio *sensor)
अणु
	sensor->पढ़ो_mmio = thermal_mmio_पढ़ोb;
	sensor->mask = 0xff;
	sensor->factor = 1000;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id thermal_mmio_id_table[] = अणु
	अणु .compatible = "amazon,al-thermal", .data = al_thermal_initपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, thermal_mmio_id_table);

अटल काष्ठा platक्रमm_driver thermal_mmio_driver = अणु
	.probe = thermal_mmio_probe,
	.driver = अणु
		.name = "thermal-mmio",
		.of_match_table = of_match_ptr(thermal_mmio_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(thermal_mmio_driver);

MODULE_AUTHOR("Talel Shenhar <talel@amazon.com>");
MODULE_DESCRIPTION("Thermal MMIO Driver");
MODULE_LICENSE("GPL v2");
