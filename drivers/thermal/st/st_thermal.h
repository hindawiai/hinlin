<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ST Thermal Sensor Driver क्रम STi series of SoCs
 * Author: Ajit Pal Singh <ajitpal.singh@st.com>
 *
 * Copyright (C) 2003-2014 STMicroelectronics (R&D) Limited
 */

#अगर_अघोषित __STI_THERMAL_SYSCFG_H
#घोषणा __STI_THERMAL_SYSCFG_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

क्रमागत st_thermal_regfield_ids अणु
	INT_THRESH_HI = 0, /* Top two regfield IDs are mutually exclusive */
	TEMP_PWR = 0,
	DCORRECT,
	OVERFLOW,
	DATA,
	INT_ENABLE,

	MAX_REGFIELDS
पूर्ण;

/* Thermal sensor घातer states */
क्रमागत st_thermal_घातer_state अणु
	POWER_OFF = 0,
	POWER_ON
पूर्ण;

काष्ठा st_thermal_sensor;

/**
 * Description of निजी thermal sensor ops.
 *
 * @घातer_ctrl:		Function क्रम घातering on/off a sensor. Clock to the
 *			sensor is also controlled from this function.
 * @alloc_regfields: 	Allocate regmap रेजिस्टर fields, specअगरic to a sensor.
 * @करो_memmap_regmap: 	Memory map the thermal रेजिस्टर space and init regmap
 *			instance or find regmap instance.
 * @रेजिस्टर_irq: 	Register an पूर्णांकerrupt handler क्रम a sensor.
 */
काष्ठा st_thermal_sensor_ops अणु
	पूर्णांक (*घातer_ctrl)(काष्ठा st_thermal_sensor *, क्रमागत st_thermal_घातer_state);
	पूर्णांक (*alloc_regfields)(काष्ठा st_thermal_sensor *);
	पूर्णांक (*regmap_init)(काष्ठा st_thermal_sensor *);
	पूर्णांक (*रेजिस्टर_enable_irq)(काष्ठा st_thermal_sensor *);
	पूर्णांक (*enable_irq)(काष्ठा st_thermal_sensor *);
पूर्ण;

/**
 * Description of thermal driver compatible data.
 *
 * @reg_fields:		Poपूर्णांकer to the regfields array क्रम a sensor.
 * @sys_compat:		Poपूर्णांकer to the syscon node compatible string.
 * @ops: 		Poपूर्णांकer to निजी thermal ops क्रम a sensor.
 * @calibration_val: 	Default calibration value to be written to the DCORRECT
 *			रेजिस्टर field क्रम a sensor.
 * @temp_adjust_val: 	Value to be added/subtracted from the data पढ़ो from
 *			the sensor. If value needs to be added please provide a
 *			positive value and अगर it is to be subtracted please
 * 			provide a negative value.
 * @crit_temp: 		The temperature beyond which the SoC should be shutकरोwn
 * 			to prevent damage.
 */
काष्ठा st_thermal_compat_data अणु
	अक्षर *sys_compat;
	स्थिर काष्ठा reg_field *reg_fields;
	स्थिर काष्ठा st_thermal_sensor_ops *ops;
	अचिन्हित पूर्णांक calibration_val;
	पूर्णांक temp_adjust_val;
	पूर्णांक crit_temp;
पूर्ण;

काष्ठा st_thermal_sensor अणु
	काष्ठा device *dev;
	काष्ठा thermal_zone_device *thermal_dev;
	स्थिर काष्ठा st_thermal_sensor_ops *ops;
	स्थिर काष्ठा st_thermal_compat_data *cdata;
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *pwr;
	काष्ठा regmap_field *dcorrect;
	काष्ठा regmap_field *overflow;
	काष्ठा regmap_field *temp_data;
	काष्ठा regmap_field *पूर्णांक_thresh_hi;
	काष्ठा regmap_field *पूर्णांक_enable;
	पूर्णांक irq;
	व्योम __iomem *mmio_base;
पूर्ण;

बाह्य पूर्णांक st_thermal_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			       स्थिर काष्ठा of_device_id *st_thermal_of_match);
बाह्य पूर्णांक st_thermal_unरेजिस्टर(काष्ठा platक्रमm_device *pdev);
बाह्य स्थिर काष्ठा dev_pm_ops st_thermal_pm_ops;

#पूर्ण_अगर /* __STI_RESET_SYSCFG_H */
