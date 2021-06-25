<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ST Thermal Sensor Driver क्रम memory mapped sensors.
 * Author: Ajit Pal Singh <ajitpal.singh@st.com>
 *
 * Copyright (C) 2003-2014 STMicroelectronics (R&D) Limited
 */

#समावेश <linux/of.h>
#समावेश <linux/module.h>

#समावेश "st_thermal.h"

#घोषणा STIH416_MPE_CONF			0x0
#घोषणा STIH416_MPE_STATUS			0x4
#घोषणा STIH416_MPE_INT_THRESH			0x8
#घोषणा STIH416_MPE_INT_EN			0xC

/* Power control bits क्रम the memory mapped thermal sensor */
#घोषणा THERMAL_PDN				BIT(4)
#घोषणा THERMAL_SRSTN				BIT(10)

अटल स्थिर काष्ठा reg_field st_mmap_thermal_regfields[MAX_REGFIELDS] = अणु
	/*
	 * According to the STIH416 MPE temp sensor data sheet -
	 * the PDN (Power Down Bit) and SRSTN (Soft Reset Bit) need to be
	 * written simultaneously क्रम घातering on and off the temperature
	 * sensor. regmap_update_bits() will be used to update the रेजिस्टर.
	 */
	[INT_THRESH_HI]	= REG_FIELD(STIH416_MPE_INT_THRESH, 	0,  7),
	[DCORRECT]	= REG_FIELD(STIH416_MPE_CONF,		5,  9),
	[OVERFLOW]	= REG_FIELD(STIH416_MPE_STATUS,		9,  9),
	[DATA]		= REG_FIELD(STIH416_MPE_STATUS,		11, 18),
	[INT_ENABLE]	= REG_FIELD(STIH416_MPE_INT_EN,		0,  0),
पूर्ण;

अटल irqवापस_t st_mmap_thermal_trip_handler(पूर्णांक irq, व्योम *sdata)
अणु
	काष्ठा st_thermal_sensor *sensor = sdata;

	thermal_zone_device_update(sensor->thermal_dev,
				   THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

/* Private ops क्रम the Memory Mapped based thermal sensors */
अटल पूर्णांक st_mmap_घातer_ctrl(काष्ठा st_thermal_sensor *sensor,
			      क्रमागत st_thermal_घातer_state घातer_state)
अणु
	स्थिर अचिन्हित पूर्णांक mask = (THERMAL_PDN | THERMAL_SRSTN);
	स्थिर अचिन्हित पूर्णांक val = घातer_state ? mask : 0;

	वापस regmap_update_bits(sensor->regmap, STIH416_MPE_CONF, mask, val);
पूर्ण

अटल पूर्णांक st_mmap_alloc_regfields(काष्ठा st_thermal_sensor *sensor)
अणु
	काष्ठा device *dev = sensor->dev;
	काष्ठा regmap *regmap = sensor->regmap;
	स्थिर काष्ठा reg_field *reg_fields = sensor->cdata->reg_fields;

	sensor->पूर्णांक_thresh_hi = devm_regmap_field_alloc(dev, regmap,
						reg_fields[INT_THRESH_HI]);
	sensor->पूर्णांक_enable = devm_regmap_field_alloc(dev, regmap,
						reg_fields[INT_ENABLE]);

	अगर (IS_ERR(sensor->पूर्णांक_thresh_hi) || IS_ERR(sensor->पूर्णांक_enable)) अणु
		dev_err(dev, "failed to alloc mmap regfields\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_mmap_enable_irq(काष्ठा st_thermal_sensor *sensor)
अणु
	पूर्णांक ret;

	/* Set upper critical threshold */
	ret = regmap_field_ग_लिखो(sensor->पूर्णांक_thresh_hi,
				 sensor->cdata->crit_temp -
				 sensor->cdata->temp_adjust_val);
	अगर (ret)
		वापस ret;

	वापस regmap_field_ग_लिखो(sensor->पूर्णांक_enable, 1);
पूर्ण

अटल पूर्णांक st_mmap_रेजिस्टर_enable_irq(काष्ठा st_thermal_sensor *sensor)
अणु
	काष्ठा device *dev = sensor->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret;

	sensor->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sensor->irq < 0)
		वापस sensor->irq;

	ret = devm_request_thपढ़ोed_irq(dev, sensor->irq,
					शून्य, st_mmap_thermal_trip_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev->driver->name, sensor);
	अगर (ret) अणु
		dev_err(dev, "failed to register IRQ %d\n", sensor->irq);
		वापस ret;
	पूर्ण

	वापस st_mmap_enable_irq(sensor);
पूर्ण

अटल स्थिर काष्ठा regmap_config st_416mpe_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक st_mmap_regmap_init(काष्ठा st_thermal_sensor *sensor)
अणु
	काष्ठा device *dev = sensor->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "no memory resources defined\n");
		वापस -ENODEV;
	पूर्ण

	sensor->mmio_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(sensor->mmio_base)) अणु
		dev_err(dev, "failed to remap IO\n");
		वापस PTR_ERR(sensor->mmio_base);
	पूर्ण

	sensor->regmap = devm_regmap_init_mmio(dev, sensor->mmio_base,
				&st_416mpe_regmap_config);
	अगर (IS_ERR(sensor->regmap)) अणु
		dev_err(dev, "failed to initialise regmap\n");
		वापस PTR_ERR(sensor->regmap);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा st_thermal_sensor_ops st_mmap_sensor_ops = अणु
	.घातer_ctrl		= st_mmap_घातer_ctrl,
	.alloc_regfields	= st_mmap_alloc_regfields,
	.regmap_init		= st_mmap_regmap_init,
	.रेजिस्टर_enable_irq	= st_mmap_रेजिस्टर_enable_irq,
	.enable_irq		= st_mmap_enable_irq,
पूर्ण;

/* Compatible device data stih416 mpe thermal sensor */
अटल स्थिर काष्ठा st_thermal_compat_data st_416mpe_cdata = अणु
	.reg_fields		= st_mmap_thermal_regfields,
	.ops			= &st_mmap_sensor_ops,
	.calibration_val	= 14,
	.temp_adjust_val	= -95,
	.crit_temp		= 120,
पूर्ण;

/* Compatible device data stih407 thermal sensor */
अटल स्थिर काष्ठा st_thermal_compat_data st_407_cdata = अणु
	.reg_fields		= st_mmap_thermal_regfields,
	.ops			= &st_mmap_sensor_ops,
	.calibration_val	= 16,
	.temp_adjust_val	= -95,
	.crit_temp		= 120,
पूर्ण;

अटल स्थिर काष्ठा of_device_id st_mmap_thermal_of_match[] = अणु
	अणु .compatible = "st,stih416-mpe-thermal", .data = &st_416mpe_cdata पूर्ण,
	अणु .compatible = "st,stih407-thermal",     .data = &st_407_cdata पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st_mmap_thermal_of_match);

अटल पूर्णांक st_mmap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस st_thermal_रेजिस्टर(pdev,  st_mmap_thermal_of_match);
पूर्ण

अटल पूर्णांक st_mmap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस st_thermal_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver st_mmap_thermal_driver = अणु
	.driver = अणु
		.name	= "st_thermal_mmap",
		.pm     = &st_thermal_pm_ops,
		.of_match_table = st_mmap_thermal_of_match,
	पूर्ण,
	.probe		= st_mmap_probe,
	.हटाओ		= st_mmap_हटाओ,
पूर्ण;

module_platक्रमm_driver(st_mmap_thermal_driver);

MODULE_AUTHOR("STMicroelectronics (R&D) Limited <ajitpal.singh@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STi SoC Thermal Sensor Driver");
MODULE_LICENSE("GPL v2");
