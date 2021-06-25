<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP4 Bandgap temperature sensor driver
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 * Contact:
 *   Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */
#अगर_अघोषित __TI_BANDGAP_H
#घोषणा __TI_BANDGAP_H

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm.h>

काष्ठा gpio_desc;

/**
 * DOC: bandgap driver data काष्ठाure
 * ==================================
 *
 *   +----------+----------------+
 *   | काष्ठा temp_sensor_regval |
 *   +---------------------------+
 *              * (Array of)
 *              |
 *              |
 *   +-------------------+   +-----------------+
 *   | काष्ठा ti_bandgap |-->| काष्ठा device * |
 *   +----------+--------+   +-----------------+
 *              |
 *              |
 *              V
 *   +------------------------+
 *   | काष्ठा ti_bandgap_data |
 *   +------------------------+
 *              |
 *              |
 *              * (Array of)
 * +------------+------------------------------------------------------+
 * | +----------+------------+   +-------------------------+           |
 * | | काष्ठा ti_temp_sensor |-->| काष्ठा temp_sensor_data |           |
 * | +-----------------------+   +------------+------------+           |
 * |            |                                                      |
 * |            +                                                      |
 * |            V                                                      |
 * | +----------+-------------------+                                  |
 * | | काष्ठा temp_sensor_रेजिस्टरs |                                  |
 * | +------------------------------+                                  |
 * |                                                                   |
 * +-------------------------------------------------------------------+
 *
 * Above is a simple diagram describing how the data काष्ठाure below
 * are organized. For each bandgap device there should be a ti_bandgap_data
 * containing the device instance configuration, as well as, an array of
 * sensors, representing every sensor instance present in this bandgap.
 */

/**
 * काष्ठा temp_sensor_रेजिस्टरs - descriptor to access रेजिस्टरs and bitfields
 * @temp_sensor_ctrl: TEMP_SENSOR_CTRL रेजिस्टर offset
 * @bgap_tempsoff_mask: mask to temp_sensor_ctrl.tempsoff
 * @bgap_soc_mask: mask to temp_sensor_ctrl.soc
 * @bgap_eocz_mask: mask to temp_sensor_ctrl.eocz
 * @bgap_dtemp_mask: mask to temp_sensor_ctrl.dtemp
 * @bgap_mask_ctrl: BANDGAP_MASK_CTRL रेजिस्टर offset
 * @mask_hot_mask: mask to bandgap_mask_ctrl.mask_hot
 * @mask_cold_mask: mask to bandgap_mask_ctrl.mask_cold
 * @mask_counter_delay_mask: mask to bandgap_mask_ctrl.mask_counter_delay
 * @mask_मुक्तze_mask: mask to bandgap_mask_ctrl.mask_मुक्त
 * @bgap_mode_ctrl: BANDGAP_MODE_CTRL रेजिस्टर offset
 * @mode_ctrl_mask: mask to bandgap_mode_ctrl.mode_ctrl
 * @bgap_counter: BANDGAP_COUNTER रेजिस्टर offset
 * @counter_mask: mask to bandgap_counter.counter
 * @bgap_threshold: BANDGAP_THRESHOLD रेजिस्टर offset (TALERT thresholds)
 * @threshold_thot_mask: mask to bandgap_threhold.thot
 * @threshold_tcold_mask: mask to bandgap_threhold.tcold
 * @tshut_threshold: TSHUT_THRESHOLD रेजिस्टर offset (TSHUT thresholds)
 * @tshut_hot_mask: mask to tshut_threhold.thot
 * @tshut_cold_mask: mask to tshut_threhold.thot
 * @bgap_status: BANDGAP_STATUS रेजिस्टर offset
 * @status_hot_mask: mask to bandgap_status.hot
 * @status_cold_mask: mask to bandgap_status.cold
 * @ctrl_dtemp_1: CTRL_DTEMP1 रेजिस्टर offset
 * @ctrl_dtemp_2: CTRL_DTEMP2 रेजिस्टर offset
 * @bgap_efuse: BANDGAP_EFUSE रेजिस्टर offset
 *
 * The रेजिस्टर offsets and bitfields might change across
 * OMAP and variants versions. Hence this काष्ठा serves as a
 * descriptor map on how to access the रेजिस्टरs and the bitfields.
 *
 * This descriptor contains रेजिस्टरs of all versions of bandgap chips.
 * Not all versions will use all रेजिस्टरs, depending on the available
 * features. Please पढ़ो TRMs क्रम descriptive explanation on each bitfield.
 */

काष्ठा temp_sensor_रेजिस्टरs अणु
	u32	temp_sensor_ctrl;
	u32	bgap_tempsoff_mask;
	u32	bgap_soc_mask;
	u32	bgap_eocz_mask;
	u32	bgap_dtemp_mask;

	u32	bgap_mask_ctrl;
	u32	mask_hot_mask;
	u32	mask_cold_mask;
	u32	mask_counter_delay_mask;
	u32	mask_मुक्तze_mask;

	u32	bgap_mode_ctrl;
	u32	mode_ctrl_mask;

	u32	bgap_counter;
	u32	counter_mask;

	u32	bgap_threshold;
	u32	threshold_thot_mask;
	u32	threshold_tcold_mask;

	u32	tshut_threshold;
	u32	tshut_hot_mask;
	u32	tshut_cold_mask;

	u32	bgap_status;
	u32	status_hot_mask;
	u32	status_cold_mask;

	u32	ctrl_dtemp_1;
	u32	ctrl_dtemp_2;
	u32	bgap_efuse;
पूर्ण;

/**
 * काष्ठा temp_sensor_data - The thresholds and limits क्रम temperature sensors.
 * @tshut_hot: temperature to trigger a thermal reset (initial value)
 * @tshut_cold: temp to get the plat out of reset due to thermal (init val)
 * @t_hot: temperature to trigger a thermal alert (high initial value)
 * @t_cold: temperature to trigger a thermal alert (low initial value)
 * @min_freq: sensor minimum घड़ी rate
 * @max_freq: sensor maximum घड़ी rate
 *
 * This data काष्ठाure will hold the required thresholds and temperature limits
 * क्रम a specअगरic temperature sensor, like shutकरोwn temperature, alert
 * temperature, घड़ी / rate used, ADC conversion limits and update पूर्णांकervals
 */
काष्ठा temp_sensor_data अणु
	u32	tshut_hot;
	u32	tshut_cold;
	u32	t_hot;
	u32	t_cold;
	u32	min_freq;
	u32	max_freq;
पूर्ण;

काष्ठा ti_bandgap_data;

/**
 * काष्ठा temp_sensor_regval - temperature sensor रेजिस्टर values and priv data
 * @bg_mode_ctrl: temp sensor control रेजिस्टर value
 * @bg_ctrl: bandgap ctrl रेजिस्टर value
 * @bg_counter: bandgap counter value
 * @bg_threshold: bandgap threshold रेजिस्टर value
 * @tshut_threshold: bandgap tshut रेजिस्टर value
 * @data: निजी data
 *
 * Data काष्ठाure to save and restore bandgap रेजिस्टर set context. Only
 * required रेजिस्टरs are shaकरोwed, when needed.
 */
काष्ठा temp_sensor_regval अणु
	u32			bg_mode_ctrl;
	u32			bg_ctrl;
	u32			bg_counter;
	u32			bg_threshold;
	u32			tshut_threshold;
	व्योम			*data;
पूर्ण;

/**
 * काष्ठा ti_bandgap - bandgap device काष्ठाure
 * @dev: काष्ठा device poपूर्णांकer
 * @base: io memory base address
 * @conf: काष्ठा with bandgap configuration set (# sensors, conv_table, etc)
 * @regval: temperature sensor रेजिस्टर values
 * @fघड़ी: poपूर्णांकer to functional घड़ी of temperature sensor
 * @भाग_clk: poपूर्णांकer to भागider घड़ी of temperature sensor fclk
 * @lock: spinlock क्रम ti_bandgap काष्ठाure
 * @irq: MPU IRQ number क्रम thermal alert
 * @tshut_gpio: GPIO where Tshut संकेत is routed
 * @clk_rate: Holds current घड़ी rate
 *
 * The bandgap device काष्ठाure representing the bandgap device instance.
 * It holds most of the dynamic stuff. Configurations and sensor specअगरic
 * entries are inside the @conf काष्ठाure.
 */
काष्ठा ti_bandgap अणु
	काष्ठा device			*dev;
	व्योम __iomem			*base;
	स्थिर काष्ठा ti_bandgap_data	*conf;
	काष्ठा temp_sensor_regval	*regval;
	काष्ठा clk			*fघड़ी;
	काष्ठा clk			*भाग_clk;
	spinlock_t			lock; /* shields this काष्ठा */
	पूर्णांक				irq;
	काष्ठा gpio_desc		*tshut_gpiod;
	u32				clk_rate;
	काष्ठा notअगरier_block		nb;
	अचिन्हित पूर्णांक is_suspended:1;
पूर्ण;

/**
 * काष्ठा ti_temp_sensor - bandgap temperature sensor configuration data
 * @ts_data: poपूर्णांकer to काष्ठा with thresholds, limits of temperature sensor
 * @रेजिस्टरs: poपूर्णांकer to the list of रेजिस्टर offsets and bitfields
 * @करोमुख्य: the name of the करोमुख्य where the sensor is located
 * @slope_pcb: sensor gradient slope info क्रम hotspot extrapolation equation
 *             with no बाह्यal influence
 * @स्थिरant_pcb: sensor gradient स्थिर info क्रम hotspot extrapolation equation
 *             with no बाह्यal influence
 * @रेजिस्टर_cooling: function to describe how this sensor is going to be cooled
 * @unरेजिस्टर_cooling: function to release cooling data
 *
 * Data काष्ठाure to describe a temperature sensor handled by a bandgap device.
 * It should provide configuration details on this sensor, such as how to
 * access the रेजिस्टरs affecting this sensor, shaकरोw रेजिस्टर buffer, how to
 * assess the gradient from hotspot, how to coolकरोwn the करोमुख्य when sensor
 * reports too hot temperature.
 */
काष्ठा ti_temp_sensor अणु
	काष्ठा temp_sensor_data		*ts_data;
	काष्ठा temp_sensor_रेजिस्टरs	*रेजिस्टरs;
	अक्षर				*करोमुख्य;
	/* क्रम hotspot extrapolation */
	स्थिर पूर्णांक			slope_pcb;
	स्थिर पूर्णांक			स्थिरant_pcb;
	पूर्णांक (*रेजिस्टर_cooling)(काष्ठा ti_bandgap *bgp, पूर्णांक id);
	पूर्णांक (*unरेजिस्टर_cooling)(काष्ठा ti_bandgap *bgp, पूर्णांक id);
पूर्ण;

/**
 * DOC: ti bandgap feature types
 *
 * TI_BANDGAP_FEATURE_TSHUT - used when the thermal shutकरोwn संकेत output
 *      of a bandgap device instance is routed to the processor. This means
 *      the प्रणाली must react and perक्रमm the shutकरोwn by itself (handle an
 *      IRQ, क्रम instance).
 *
 * TI_BANDGAP_FEATURE_TSHUT_CONFIG - used when the bandgap device has control
 *      over the thermal shutकरोwn configuration. This means that the thermal
 *      shutकरोwn thresholds are programmable, क्रम instance.
 *
 * TI_BANDGAP_FEATURE_TALERT - used when the bandgap device instance outमाला_दो
 *      a संकेत representing violation of programmable alert thresholds.
 *
 * TI_BANDGAP_FEATURE_MODE_CONFIG - used when it is possible to choose which
 *      mode, continuous or one shot, the bandgap device instance will operate.
 *
 * TI_BANDGAP_FEATURE_COUNTER - used when the bandgap device instance allows
 *      programming the update पूर्णांकerval of its पूर्णांकernal state machine.
 *
 * TI_BANDGAP_FEATURE_POWER_SWITCH - used when the bandgap device allows
 *      itself to be चयनed on/off.
 *
 * TI_BANDGAP_FEATURE_CLK_CTRL - used when the घड़ीs feeding the bandgap
 *      device are gateable or not.
 *
 * TI_BANDGAP_FEATURE_FREEZE_BIT - used when the bandgap device features
 *      a history buffer that its update can be मुक्तzed/unमुक्तzed.
 *
 * TI_BANDGAP_FEATURE_COUNTER_DELAY - used when the bandgap device features
 *	a delay programming based on distinct values.
 *
 * TI_BANDGAP_FEATURE_HISTORY_BUFFER - used when the bandgap device features
 *	a history buffer of temperatures.
 *
 * TI_BANDGAP_FEATURE_ERRATA_814 - used to workaorund when the bandgap device
 *	has Errata 814
 * TI_BANDGAP_FEATURE_UNRELIABLE - used when the sensor पढ़ोings are too
 *	inaccurate.
 * TI_BANDGAP_FEATURE_CONT_MODE_ONLY - used when single mode hangs the sensor
 * TI_BANDGAP_HAS(b, f) - macro to check अगर a bandgap device is capable of a
 *      specअगरic feature (above) or not. Return non-zero, अगर yes.
 */
#घोषणा TI_BANDGAP_FEATURE_TSHUT		BIT(0)
#घोषणा TI_BANDGAP_FEATURE_TSHUT_CONFIG		BIT(1)
#घोषणा TI_BANDGAP_FEATURE_TALERT		BIT(2)
#घोषणा TI_BANDGAP_FEATURE_MODE_CONFIG		BIT(3)
#घोषणा TI_BANDGAP_FEATURE_COUNTER		BIT(4)
#घोषणा TI_BANDGAP_FEATURE_POWER_SWITCH		BIT(5)
#घोषणा TI_BANDGAP_FEATURE_CLK_CTRL		BIT(6)
#घोषणा TI_BANDGAP_FEATURE_FREEZE_BIT		BIT(7)
#घोषणा TI_BANDGAP_FEATURE_COUNTER_DELAY	BIT(8)
#घोषणा TI_BANDGAP_FEATURE_HISTORY_BUFFER	BIT(9)
#घोषणा TI_BANDGAP_FEATURE_ERRATA_814		BIT(10)
#घोषणा TI_BANDGAP_FEATURE_UNRELIABLE		BIT(11)
#घोषणा TI_BANDGAP_FEATURE_CONT_MODE_ONLY	BIT(12)
#घोषणा TI_BANDGAP_HAS(b, f)			\
			((b)->conf->features & TI_BANDGAP_FEATURE_ ## f)

/**
 * काष्ठा ti_bandgap_data - ti bandgap data configuration काष्ठाure
 * @features: a bitwise flag set to describe the device features
 * @conv_table: Poपूर्णांकer to ADC to temperature conversion table
 * @adc_start_val: ADC conversion table starting value
 * @adc_end_val: ADC conversion table ending value
 * @fघड़ी_name: घड़ी name of the functional घड़ी
 * @भाग_ck_name: घड़ी name of the घड़ी भागisor
 * @sensor_count: count of temperature sensor within this bandgap device
 * @report_temperature: callback to report thermal alert to thermal API
 * @expose_sensor: callback to export sensor to thermal API
 * @हटाओ_sensor: callback to destroy sensor from thermal API
 * @sensors: array of sensors present in this bandgap instance
 *
 * This is a data काष्ठाure which should hold most of the अटल configuration
 * of a bandgap device instance. It should describe which features this instance
 * is capable of, the घड़ी names to feed this device, the amount of sensors and
 * their configuration representation, and how to export and unexport them to
 * a thermal API.
 */
काष्ठा ti_bandgap_data अणु
	अचिन्हित पूर्णांक			features;
	स्थिर पूर्णांक			*conv_table;
	u32				adc_start_val;
	u32				adc_end_val;
	अक्षर				*fघड़ी_name;
	अक्षर				*भाग_ck_name;
	पूर्णांक				sensor_count;
	पूर्णांक (*report_temperature)(काष्ठा ti_bandgap *bgp, पूर्णांक id);
	पूर्णांक (*expose_sensor)(काष्ठा ti_bandgap *bgp, पूर्णांक id, अक्षर *करोमुख्य);
	पूर्णांक (*हटाओ_sensor)(काष्ठा ti_bandgap *bgp, पूर्णांक id);

	/* this needs to be at the end */
	काष्ठा ti_temp_sensor		sensors[];
पूर्ण;

पूर्णांक ti_bandgap_पढ़ो_thot(काष्ठा ti_bandgap *bgp, पूर्णांक id, पूर्णांक *thot);
पूर्णांक ti_bandgap_ग_लिखो_thot(काष्ठा ti_bandgap *bgp, पूर्णांक id, पूर्णांक val);
पूर्णांक ti_bandgap_पढ़ो_tcold(काष्ठा ti_bandgap *bgp, पूर्णांक id, पूर्णांक *tcold);
पूर्णांक ti_bandgap_ग_लिखो_tcold(काष्ठा ti_bandgap *bgp, पूर्णांक id, पूर्णांक val);
पूर्णांक ti_bandgap_पढ़ो_update_पूर्णांकerval(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				    पूर्णांक *पूर्णांकerval);
पूर्णांक ti_bandgap_ग_लिखो_update_पूर्णांकerval(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				     u32 पूर्णांकerval);
पूर्णांक ti_bandgap_पढ़ो_temperature(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				  पूर्णांक *temperature);
पूर्णांक ti_bandgap_set_sensor_data(काष्ठा ti_bandgap *bgp, पूर्णांक id, व्योम *data);
व्योम *ti_bandgap_get_sensor_data(काष्ठा ti_bandgap *bgp, पूर्णांक id);
पूर्णांक ti_bandgap_get_trend(काष्ठा ti_bandgap *bgp, पूर्णांक id, पूर्णांक *trend);

#अगर_घोषित CONFIG_OMAP3_THERMAL
बाह्य स्थिर काष्ठा ti_bandgap_data omap34xx_data;
बाह्य स्थिर काष्ठा ti_bandgap_data omap36xx_data;
#अन्यथा
#घोषणा omap34xx_data					शून्य
#घोषणा omap36xx_data					शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OMAP4_THERMAL
बाह्य स्थिर काष्ठा ti_bandgap_data omap4430_data;
बाह्य स्थिर काष्ठा ti_bandgap_data omap4460_data;
बाह्य स्थिर काष्ठा ti_bandgap_data omap4470_data;
#अन्यथा
#घोषणा omap4430_data					शून्य
#घोषणा omap4460_data					शून्य
#घोषणा omap4470_data					शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OMAP5_THERMAL
बाह्य स्थिर काष्ठा ti_bandgap_data omap5430_data;
#अन्यथा
#घोषणा omap5430_data					शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_DRA752_THERMAL
बाह्य स्थिर काष्ठा ti_bandgap_data dra752_data;
#अन्यथा
#घोषणा dra752_data					शून्य
#पूर्ण_अगर
#पूर्ण_अगर
