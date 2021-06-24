<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _GSC_HWMON_H
#घोषणा _GSC_HWMON_H

क्रमागत gsc_hwmon_mode अणु
	mode_temperature,
	mode_voltage_24bit,
	mode_voltage_raw,
	mode_voltage_16bit,
	mode_fan,
	mode_max,
पूर्ण;

/**
 * काष्ठा gsc_hwmon_channel - configuration parameters
 * @reg:  I2C रेजिस्टर offset
 * @mode: channel mode
 * @name: channel name
 * @mvoffset: voltage offset
 * @vभाग: voltage भागider array (2 resistor values in milli-ohms)
 */
काष्ठा gsc_hwmon_channel अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक mode;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक mvoffset;
	अचिन्हित पूर्णांक vभाग[2];
पूर्ण;

/**
 * काष्ठा gsc_hwmon_platक्रमm_data - platक्रमm data क्रम gsc_hwmon driver
 * @channels:	poपूर्णांकer to array of gsc_hwmon_channel काष्ठाures
 *		describing channels
 * @nchannels:	number of elements in @channels array
 * @vreference: voltage reference (mV)
 * @resolution: ADC bit resolution
 * @fan_base: रेजिस्टर base क्रम FAN controller
 */
काष्ठा gsc_hwmon_platक्रमm_data अणु
	स्थिर काष्ठा gsc_hwmon_channel *channels;
	पूर्णांक nchannels;
	अचिन्हित पूर्णांक resolution;
	अचिन्हित पूर्णांक vreference;
	अचिन्हित पूर्णांक fan_base;
पूर्ण;
#पूर्ण_अगर
