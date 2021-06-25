<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Device driver क्रम monitoring ambient light पूर्णांकensity (lux)
 * and proximity (prox) within the TAOS TSL2772 family of devices.
 *
 * Copyright (c) 2012, TAOS Corporation.
 * Copyright (c) 2017-2018 Brian Masney <masneyb@onstation.org>
 */

#अगर_अघोषित __TSL2772_H
#घोषणा __TSL2772_H

काष्ठा tsl2772_lux अणु
	अचिन्हित पूर्णांक ch0;
	अचिन्हित पूर्णांक ch1;
पूर्ण;

/* Max number of segments allowable in LUX table */
#घोषणा TSL2772_MAX_LUX_TABLE_SIZE		6
/* The शेष LUX tables all have 3 elements.  */
#घोषणा TSL2772_DEF_LUX_TABLE_SZ		3
#घोषणा TSL2772_DEFAULT_TABLE_BYTES (माप(काष्ठा tsl2772_lux) * \
				     TSL2772_DEF_LUX_TABLE_SZ)

/* Proximity diode to use */
#घोषणा TSL2772_DIODE0                  0x01
#घोषणा TSL2772_DIODE1                  0x02
#घोषणा TSL2772_DIODE_BOTH              0x03

/* LED Power */
#घोषणा TSL2772_100_mA                  0x00
#घोषणा TSL2772_50_mA                   0x01
#घोषणा TSL2772_25_mA                   0x02
#घोषणा TSL2772_13_mA                   0x03

/**
 * काष्ठा tsl2772_settings - Settings क्रम the tsl2772 driver
 *  @als_समय:              Integration समय of the ALS channel ADCs in 2.73 ms
 *                          increments. Total पूर्णांकegration समय is
 *                          (256 - als_समय) * 2.73.
 *  @als_gain:              Index पूर्णांकo the tsl2772_als_gain array.
 *  @als_gain_trim:         Default gain trim to account क्रम aperture effects.
 *  @रुको_समय:             Time between proximity and ALS cycles in 2.73
 *                          periods.
 *  @prox_समय:             Integration समय of the proximity ADC in 2.73 ms
 *                          increments. Total पूर्णांकegration समय is
 *                          (256 - prx_समय) * 2.73.
 *  @prox_gain:             Index पूर्णांकo the tsl2772_prx_gain array.
 *  @als_prox_config:       The value of the ALS / Proximity configuration
 *                          रेजिस्टर.
 *  @als_cal_target:        Known बाह्यal ALS पढ़ोing क्रम calibration.
 *  @als_persistence:       H/W Filters, Number of 'out of limits' ALS पढ़ोings.
 *  @als_पूर्णांकerrupt_en:      Enable/Disable ALS पूर्णांकerrupts
 *  @als_thresh_low:        CH0 'low' count to trigger पूर्णांकerrupt.
 *  @als_thresh_high:       CH0 'high' count to trigger पूर्णांकerrupt.
 *  @prox_persistence:      H/W Filters, Number of 'out of limits' proximity
 *                          पढ़ोings.
 *  @prox_पूर्णांकerrupt_en:     Enable/Disable proximity पूर्णांकerrupts.
 *  @prox_thres_low:        Low threshold proximity detection.
 *  @prox_thres_high:       High threshold proximity detection.
 *  @prox_pulse_count:      Number अगर proximity emitter pulses.
 *  @prox_max_samples_cal:  The number of samples that are taken when perक्रमming
 *                          a proximity calibration.
 *  @prox_diode             Which diode(s) to use क्रम driving the बाह्यal
 *                          LED(s) क्रम proximity sensing.
 *  @prox_घातer             The amount of घातer to use क्रम the बाह्यal LED(s).
 */
काष्ठा tsl2772_settings अणु
	पूर्णांक als_समय;
	पूर्णांक als_gain;
	पूर्णांक als_gain_trim;
	पूर्णांक रुको_समय;
	पूर्णांक prox_समय;
	पूर्णांक prox_gain;
	पूर्णांक als_prox_config;
	पूर्णांक als_cal_target;
	u8 als_persistence;
	bool als_पूर्णांकerrupt_en;
	पूर्णांक als_thresh_low;
	पूर्णांक als_thresh_high;
	u8 prox_persistence;
	bool prox_पूर्णांकerrupt_en;
	पूर्णांक prox_thres_low;
	पूर्णांक prox_thres_high;
	पूर्णांक prox_pulse_count;
	पूर्णांक prox_max_samples_cal;
	पूर्णांक prox_diode;
	पूर्णांक prox_घातer;
पूर्ण;

/**
 * काष्ठा tsl2772_platक्रमm_data - Platक्रमm callback, glass and शेषs
 * @platक्रमm_lux_table:        Device specअगरic glass coefficents
 * @platक्रमm_शेष_settings: Device specअगरic घातer on शेषs
 */
काष्ठा tsl2772_platक्रमm_data अणु
	काष्ठा tsl2772_lux platक्रमm_lux_table[TSL2772_MAX_LUX_TABLE_SIZE];
	काष्ठा tsl2772_settings *platक्रमm_शेष_settings;
पूर्ण;

#पूर्ण_अगर /* __TSL2772_H */
