<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI LP8788 MFD Device
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#अगर_अघोषित __MFD_LP8788_H__
#घोषणा __MFD_LP8788_H__

#समावेश <linux/gpपन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

#घोषणा LP8788_DEV_BUCK		"lp8788-buck"
#घोषणा LP8788_DEV_DLDO		"lp8788-dldo"
#घोषणा LP8788_DEV_ALDO		"lp8788-aldo"
#घोषणा LP8788_DEV_CHARGER	"lp8788-charger"
#घोषणा LP8788_DEV_RTC		"lp8788-rtc"
#घोषणा LP8788_DEV_BACKLIGHT	"lp8788-backlight"
#घोषणा LP8788_DEV_VIBRATOR	"lp8788-vibrator"
#घोषणा LP8788_DEV_KEYLED	"lp8788-keyled"
#घोषणा LP8788_DEV_ADC		"lp8788-adc"

#घोषणा LP8788_NUM_BUCKS	4
#घोषणा LP8788_NUM_DLDOS	12
#घोषणा LP8788_NUM_ALDOS	10
#घोषणा LP8788_NUM_BUCK2_DVS	2

#घोषणा LP8788_CHG_IRQ		"CHG_IRQ"
#घोषणा LP8788_PRSW_IRQ		"PRSW_IRQ"
#घोषणा LP8788_BATT_IRQ		"BATT_IRQ"
#घोषणा LP8788_ALM_IRQ		"ALARM_IRQ"

क्रमागत lp8788_पूर्णांक_id अणु
	/* पूर्णांकerrup रेजिस्टर 1 : Addr 00h */
	LP8788_INT_TSDL,
	LP8788_INT_TSDH,
	LP8788_INT_UVLO,
	LP8788_INT_FLAGMON,
	LP8788_INT_PWRON_TIME,
	LP8788_INT_PWRON,
	LP8788_INT_COMP1,
	LP8788_INT_COMP2,

	/* पूर्णांकerrupt रेजिस्टर 2 : Addr 01h */
	LP8788_INT_CHG_INPUT_STATE,
	LP8788_INT_CHG_STATE,
	LP8788_INT_EOC,
	LP8788_INT_CHG_RESTART,
	LP8788_INT_RESTART_TIMEOUT,
	LP8788_INT_FULLCHG_TIMEOUT,
	LP8788_INT_PRECHG_TIMEOUT,

	/* पूर्णांकerrupt रेजिस्टर 3 : Addr 02h */
	LP8788_INT_RTC_ALARM1 = 17,
	LP8788_INT_RTC_ALARM2,
	LP8788_INT_ENTER_SYS_SUPPORT,
	LP8788_INT_EXIT_SYS_SUPPORT,
	LP8788_INT_BATT_LOW,
	LP8788_INT_NO_BATT,

	LP8788_पूर्णांक_उच्च = 24,
पूर्ण;

क्रमागत lp8788_dvs_sel अणु
	DVS_SEL_V0,
	DVS_SEL_V1,
	DVS_SEL_V2,
	DVS_SEL_V3,
पूर्ण;

क्रमागत lp8788_ext_lकरो_en_id अणु
	EN_ALDO1,
	EN_ALDO234,
	EN_ALDO5,
	EN_ALDO7,
	EN_DLDO7,
	EN_DLDO911,
	EN_LDOS_MAX,
पूर्ण;

क्रमागत lp8788_अक्षरger_event अणु
	NO_CHARGER,
	CHARGER_DETECTED,
पूर्ण;

क्रमागत lp8788_bl_ctrl_mode अणु
	LP8788_BL_REGISTER_ONLY,
	LP8788_BL_COMB_PWM_BASED,	/* PWM + I2C, changed by PWM input */
	LP8788_BL_COMB_REGISTER_BASED,	/* PWM + I2C, changed by I2C */
पूर्ण;

क्रमागत lp8788_bl_dim_mode अणु
	LP8788_DIM_EXPONENTIAL,
	LP8788_DIM_LINEAR,
पूर्ण;

क्रमागत lp8788_bl_full_scale_current अणु
	LP8788_FULLSCALE_5000uA,
	LP8788_FULLSCALE_8500uA,
	LP8788_FULLSCALE_1200uA,
	LP8788_FULLSCALE_1550uA,
	LP8788_FULLSCALE_1900uA,
	LP8788_FULLSCALE_2250uA,
	LP8788_FULLSCALE_2600uA,
	LP8788_FULLSCALE_2950uA,
पूर्ण;

क्रमागत lp8788_bl_ramp_step अणु
	LP8788_RAMP_8us,
	LP8788_RAMP_1024us,
	LP8788_RAMP_2048us,
	LP8788_RAMP_4096us,
	LP8788_RAMP_8192us,
	LP8788_RAMP_16384us,
	LP8788_RAMP_32768us,
	LP8788_RAMP_65538us,
पूर्ण;

क्रमागत lp8788_isink_scale अणु
	LP8788_ISINK_SCALE_100mA,
	LP8788_ISINK_SCALE_120mA,
पूर्ण;

क्रमागत lp8788_isink_number अणु
	LP8788_ISINK_1,
	LP8788_ISINK_2,
	LP8788_ISINK_3,
पूर्ण;

क्रमागत lp8788_alarm_sel अणु
	LP8788_ALARM_1,
	LP8788_ALARM_2,
	LP8788_ALARM_MAX,
पूर्ण;

क्रमागत lp8788_adc_id अणु
	LPADC_VBATT_5P5,
	LPADC_VIN_CHG,
	LPADC_IBATT,
	LPADC_IC_TEMP,
	LPADC_VBATT_6P0,
	LPADC_VBATT_5P0,
	LPADC_ADC1,
	LPADC_ADC2,
	LPADC_VDD,
	LPADC_VCOIN,
	LPADC_VDD_LDO,
	LPADC_ADC3,
	LPADC_ADC4,
	LPADC_MAX,
पूर्ण;

काष्ठा lp8788;

/*
 * lp8788_buck1_dvs
 * @gpio         : gpio pin number क्रम dvs control
 * @vsel         : dvs selector क्रम buck v1 रेजिस्टर
 */
काष्ठा lp8788_buck1_dvs अणु
	पूर्णांक gpio;
	क्रमागत lp8788_dvs_sel vsel;
पूर्ण;

/*
 * lp8788_buck2_dvs
 * @gpio         : two gpio pin numbers are used क्रम dvs
 * @vsel         : dvs selector क्रम buck v2 रेजिस्टर
 */
काष्ठा lp8788_buck2_dvs अणु
	पूर्णांक gpio[LP8788_NUM_BUCK2_DVS];
	क्रमागत lp8788_dvs_sel vsel;
पूर्ण;

/*
 * काष्ठा lp8788_chg_param
 * @addr         : अक्षरging control रेजिस्टर address (range : 0x11 ~ 0x1C)
 * @val          : अक्षरging parameter value
 */
काष्ठा lp8788_chg_param अणु
	u8 addr;
	u8 val;
पूर्ण;

/*
 * काष्ठा lp8788_अक्षरger_platक्रमm_data
 * @adc_vbatt         : adc channel name क्रम battery voltage
 * @adc_batt_temp     : adc channel name क्रम battery temperature
 * @max_vbatt_mv      : used क्रम calculating battery capacity
 * @chg_params        : initial अक्षरging parameters
 * @num_chg_params    : numbers of अक्षरging parameters
 * @अक्षरger_event     : the अक्षरger event can be reported to the platक्रमm side
 */
काष्ठा lp8788_अक्षरger_platक्रमm_data अणु
	स्थिर अक्षर *adc_vbatt;
	स्थिर अक्षर *adc_batt_temp;
	अचिन्हित पूर्णांक max_vbatt_mv;
	काष्ठा lp8788_chg_param *chg_params;
	पूर्णांक num_chg_params;
	व्योम (*अक्षरger_event) (काष्ठा lp8788 *lp,
				क्रमागत lp8788_अक्षरger_event event);
पूर्ण;

/*
 * काष्ठा lp8788_backlight_platक्रमm_data
 * @name                  : backlight driver name. (शेष: "lcd-backlight")
 * @initial_brightness    : initial value of backlight brightness
 * @bl_mode               : brightness control by pwm or lp8788 रेजिस्टर
 * @dim_mode              : dimming mode selection
 * @full_scale            : full scale current setting
 * @rise_समय             : brightness ramp up step समय
 * @fall_समय             : brightness ramp करोwn step समय
 * @pwm_pol               : pwm polarity setting when bl_mode is pwm based
 * @period_ns             : platक्रमm specअगरic pwm period value. unit is nano.
			    Only valid when bl_mode is LP8788_BL_COMB_PWM_BASED
 */
काष्ठा lp8788_backlight_platक्रमm_data अणु
	अक्षर *name;
	पूर्णांक initial_brightness;
	क्रमागत lp8788_bl_ctrl_mode bl_mode;
	क्रमागत lp8788_bl_dim_mode dim_mode;
	क्रमागत lp8788_bl_full_scale_current full_scale;
	क्रमागत lp8788_bl_ramp_step rise_समय;
	क्रमागत lp8788_bl_ramp_step fall_समय;
	क्रमागत pwm_polarity pwm_pol;
	अचिन्हित पूर्णांक period_ns;
पूर्ण;

/*
 * काष्ठा lp8788_led_platक्रमm_data
 * @name         : led driver name. (शेष: "keyboard-backlight")
 * @scale        : current scale
 * @num          : current sink number
 * @iout_code    : current output value (Addr 9Ah ~ 9Bh)
 */
काष्ठा lp8788_led_platक्रमm_data अणु
	अक्षर *name;
	क्रमागत lp8788_isink_scale scale;
	क्रमागत lp8788_isink_number num;
	पूर्णांक iout_code;
पूर्ण;

/*
 * काष्ठा lp8788_vib_platक्रमm_data
 * @name         : vibrator driver name
 * @scale        : current scale
 * @num          : current sink number
 * @iout_code    : current output value (Addr 9Ah ~ 9Bh)
 * @pwm_code     : PWM code value (Addr 9Ch ~ 9Eh)
 */
काष्ठा lp8788_vib_platक्रमm_data अणु
	अक्षर *name;
	क्रमागत lp8788_isink_scale scale;
	क्रमागत lp8788_isink_number num;
	पूर्णांक iout_code;
	पूर्णांक pwm_code;
पूर्ण;

/*
 * काष्ठा lp8788_platक्रमm_data
 * @init_func    : used क्रम initializing रेजिस्टरs
 *                 beक्रमe mfd driver is रेजिस्टरed
 * @buck_data    : regulator initial data क्रम buck
 * @dlकरो_data    : regulator initial data क्रम digital lकरो
 * @alकरो_data    : regulator initial data क्रम analog lकरो
 * @buck1_dvs    : gpio configurations क्रम buck1 dvs
 * @buck2_dvs    : gpio configurations क्रम buck2 dvs
 * @chg_pdata    : platक्रमm data क्रम अक्षरger driver
 * @alarm_sel    : rtc alarm selection (1 or 2)
 * @bl_pdata     : configurable data क्रम backlight driver
 * @led_pdata    : configurable data क्रम led driver
 * @vib_pdata    : configurable data क्रम vibrator driver
 * @adc_pdata    : iio map data क्रम adc driver
 */
काष्ठा lp8788_platक्रमm_data अणु
	/* general प्रणाली inक्रमmation */
	पूर्णांक (*init_func) (काष्ठा lp8788 *lp);

	/* regulators */
	काष्ठा regulator_init_data *buck_data[LP8788_NUM_BUCKS];
	काष्ठा regulator_init_data *dlकरो_data[LP8788_NUM_DLDOS];
	काष्ठा regulator_init_data *alकरो_data[LP8788_NUM_ALDOS];
	काष्ठा lp8788_buck1_dvs *buck1_dvs;
	काष्ठा lp8788_buck2_dvs *buck2_dvs;

	/* अक्षरger */
	काष्ठा lp8788_अक्षरger_platक्रमm_data *chg_pdata;

	/* rtc alarm */
	क्रमागत lp8788_alarm_sel alarm_sel;

	/* backlight */
	काष्ठा lp8788_backlight_platक्रमm_data *bl_pdata;

	/* current sinks */
	काष्ठा lp8788_led_platक्रमm_data *led_pdata;
	काष्ठा lp8788_vib_platक्रमm_data *vib_pdata;

	/* adc iio map data */
	काष्ठा iio_map *adc_pdata;
पूर्ण;

/*
 * काष्ठा lp8788
 * @dev          : parent device poपूर्णांकer
 * @regmap       : used क्रम i2c communcation on accessing रेजिस्टरs
 * @irqdm        : पूर्णांकerrupt करोमुख्य क्रम handling nested पूर्णांकerrupt
 * @irq          : pin number of IRQ_N
 * @pdata        : lp8788 platक्रमm specअगरic data
 */
काष्ठा lp8788 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा irq_करोमुख्य *irqdm;
	पूर्णांक irq;
	काष्ठा lp8788_platक्रमm_data *pdata;
पूर्ण;

पूर्णांक lp8788_irq_init(काष्ठा lp8788 *lp, पूर्णांक chip_irq);
व्योम lp8788_irq_निकास(काष्ठा lp8788 *lp);
पूर्णांक lp8788_पढ़ो_byte(काष्ठा lp8788 *lp, u8 reg, u8 *data);
पूर्णांक lp8788_पढ़ो_multi_bytes(काष्ठा lp8788 *lp, u8 reg, u8 *data, माप_प्रकार count);
पूर्णांक lp8788_ग_लिखो_byte(काष्ठा lp8788 *lp, u8 reg, u8 data);
पूर्णांक lp8788_update_bits(काष्ठा lp8788 *lp, u8 reg, u8 mask, u8 data);
#पूर्ण_अगर
