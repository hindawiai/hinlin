<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ST Thermal Sensor Driver क्रम syscfg based sensors.
 * Author: Ajit Pal Singh <ajitpal.singh@st.com>
 *
 * Copyright (C) 2003-2014 STMicroelectronics (R&D) Limited
 */

#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "st_thermal.h"

/* STiH415 */
#घोषणा STIH415_SYSCFG_FRONT(num)		((num - 100) * 4)
#घोषणा STIH415_SAS_THSENS_CONF			STIH415_SYSCFG_FRONT(178)
#घोषणा STIH415_SAS_THSENS_STATUS		STIH415_SYSCFG_FRONT(198)
#घोषणा STIH415_SYSCFG_MPE(num)			((num - 600) * 4)
#घोषणा STIH415_MPE_THSENS_CONF			STIH415_SYSCFG_MPE(607)
#घोषणा STIH415_MPE_THSENS_STATUS		STIH415_SYSCFG_MPE(667)

/* STiH416 */
#घोषणा STIH416_SYSCFG_FRONT(num)		((num - 1000) * 4)
#घोषणा STIH416_SAS_THSENS_CONF			STIH416_SYSCFG_FRONT(1552)
#घोषणा STIH416_SAS_THSENS_STATUS1		STIH416_SYSCFG_FRONT(1554)
#घोषणा STIH416_SAS_THSENS_STATUS2		STIH416_SYSCFG_FRONT(1594)

/* STiD127 */
#घोषणा STID127_SYSCFG_CPU(num)			((num - 700) * 4)
#घोषणा STID127_THSENS_CONF			STID127_SYSCFG_CPU(743)
#घोषणा STID127_THSENS_STATUS			STID127_SYSCFG_CPU(767)

अटल स्थिर काष्ठा reg_field st_415sas_regfields[MAX_REGFIELDS] = अणु
	[TEMP_PWR] = REG_FIELD(STIH415_SAS_THSENS_CONF,   9,  9),
	[DCORRECT] = REG_FIELD(STIH415_SAS_THSENS_CONF,   4,  8),
	[OVERFLOW] = REG_FIELD(STIH415_SAS_THSENS_STATUS, 8,  8),
	[DATA] 	   = REG_FIELD(STIH415_SAS_THSENS_STATUS, 10, 16),
पूर्ण;

अटल स्थिर काष्ठा reg_field st_415mpe_regfields[MAX_REGFIELDS] = अणु
	[TEMP_PWR] = REG_FIELD(STIH415_MPE_THSENS_CONF,   8,  8),
	[DCORRECT] = REG_FIELD(STIH415_MPE_THSENS_CONF,   3,  7),
	[OVERFLOW] = REG_FIELD(STIH415_MPE_THSENS_STATUS, 9,  9),
	[DATA]     = REG_FIELD(STIH415_MPE_THSENS_STATUS, 11, 18),
पूर्ण;

अटल स्थिर काष्ठा reg_field st_416sas_regfields[MAX_REGFIELDS] = अणु
	[TEMP_PWR] = REG_FIELD(STIH416_SAS_THSENS_CONF,    9,  9),
	[DCORRECT] = REG_FIELD(STIH416_SAS_THSENS_CONF,    4,  8),
	[OVERFLOW] = REG_FIELD(STIH416_SAS_THSENS_STATUS1, 8,  8),
	[DATA]     = REG_FIELD(STIH416_SAS_THSENS_STATUS2, 10, 16),
पूर्ण;

अटल स्थिर काष्ठा reg_field st_127_regfields[MAX_REGFIELDS] = अणु
	[TEMP_PWR] = REG_FIELD(STID127_THSENS_CONF,   7,  7),
	[DCORRECT] = REG_FIELD(STID127_THSENS_CONF,   2,  6),
	[OVERFLOW] = REG_FIELD(STID127_THSENS_STATUS, 9,  9),
	[DATA]     = REG_FIELD(STID127_THSENS_STATUS, 11, 18),
पूर्ण;

/* Private OPs क्रम System Configuration Register based thermal sensors */
अटल पूर्णांक st_syscfg_घातer_ctrl(काष्ठा st_thermal_sensor *sensor,
				क्रमागत st_thermal_घातer_state घातer_state)
अणु
	वापस regmap_field_ग_लिखो(sensor->pwr, घातer_state);
पूर्ण

अटल पूर्णांक st_syscfg_alloc_regfields(काष्ठा st_thermal_sensor *sensor)
अणु
	काष्ठा device *dev = sensor->dev;

	sensor->pwr = devm_regmap_field_alloc(dev, sensor->regmap,
					sensor->cdata->reg_fields[TEMP_PWR]);

	अगर (IS_ERR(sensor->pwr)) अणु
		dev_err(dev, "failed to alloc syscfg regfields\n");
		वापस PTR_ERR(sensor->pwr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_syscfg_regmap_init(काष्ठा st_thermal_sensor *sensor)
अणु
	sensor->regmap =
		syscon_regmap_lookup_by_compatible(sensor->cdata->sys_compat);
	अगर (IS_ERR(sensor->regmap)) अणु
		dev_err(sensor->dev, "failed to find syscfg regmap\n");
		वापस PTR_ERR(sensor->regmap);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा st_thermal_sensor_ops st_syscfg_sensor_ops = अणु
	.घातer_ctrl		= st_syscfg_घातer_ctrl,
	.alloc_regfields	= st_syscfg_alloc_regfields,
	.regmap_init		= st_syscfg_regmap_init,
पूर्ण;

/* Compatible device data क्रम stih415 sas thermal sensor */
अटल स्थिर काष्ठा st_thermal_compat_data st_415sas_cdata = अणु
	.sys_compat		= "st,stih415-front-syscfg",
	.reg_fields		= st_415sas_regfields,
	.ops			= &st_syscfg_sensor_ops,
	.calibration_val	= 16,
	.temp_adjust_val	= 20,
	.crit_temp		= 120,
पूर्ण;

/* Compatible device data क्रम stih415 mpe thermal sensor */
अटल स्थिर काष्ठा st_thermal_compat_data st_415mpe_cdata = अणु
	.sys_compat		= "st,stih415-system-syscfg",
	.reg_fields		= st_415mpe_regfields,
	.ops			= &st_syscfg_sensor_ops,
	.calibration_val	= 16,
	.temp_adjust_val	= -103,
	.crit_temp		= 120,
पूर्ण;

/* Compatible device data क्रम stih416 sas thermal sensor */
अटल स्थिर काष्ठा st_thermal_compat_data st_416sas_cdata = अणु
	.sys_compat		= "st,stih416-front-syscfg",
	.reg_fields		= st_416sas_regfields,
	.ops			= &st_syscfg_sensor_ops,
	.calibration_val	= 16,
	.temp_adjust_val	= 20,
	.crit_temp		= 120,
पूर्ण;

/* Compatible device data क्रम stid127 thermal sensor */
अटल स्थिर काष्ठा st_thermal_compat_data st_127_cdata = अणु
	.sys_compat		= "st,stid127-cpu-syscfg",
	.reg_fields		= st_127_regfields,
	.ops			= &st_syscfg_sensor_ops,
	.calibration_val	= 8,
	.temp_adjust_val	= -103,
	.crit_temp		= 120,
पूर्ण;

अटल स्थिर काष्ठा of_device_id st_syscfg_thermal_of_match[] = अणु
	अणु .compatible = "st,stih415-sas-thermal", .data = &st_415sas_cdata पूर्ण,
	अणु .compatible = "st,stih415-mpe-thermal", .data = &st_415mpe_cdata पूर्ण,
	अणु .compatible = "st,stih416-sas-thermal", .data = &st_416sas_cdata पूर्ण,
	अणु .compatible = "st,stid127-thermal",     .data = &st_127_cdata पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st_syscfg_thermal_of_match);

अटल पूर्णांक st_syscfg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस st_thermal_रेजिस्टर(pdev, st_syscfg_thermal_of_match);
पूर्ण

अटल पूर्णांक st_syscfg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस st_thermal_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver st_syscfg_thermal_driver = अणु
	.driver = अणु
		.name	= "st_syscfg_thermal",
		.pm     = &st_thermal_pm_ops,
		.of_match_table =  st_syscfg_thermal_of_match,
	पूर्ण,
	.probe		= st_syscfg_probe,
	.हटाओ		= st_syscfg_हटाओ,
पूर्ण;
module_platक्रमm_driver(st_syscfg_thermal_driver);

MODULE_AUTHOR("STMicroelectronics (R&D) Limited <ajitpal.singh@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STi SoC Thermal Sensor Driver");
MODULE_LICENSE("GPL v2");
