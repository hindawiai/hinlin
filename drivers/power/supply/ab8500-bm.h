<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _AB8500_CHARGER_H_
#घोषणा _AB8500_CHARGER_H_

#समावेश <linux/kernel.h>

/*
 * System control 2 रेजिस्टर offsets.
 * bank = 0x02
 */
#घोषणा AB8500_MAIN_WDOG_CTRL_REG	0x01
#घोषणा AB8500_LOW_BAT_REG		0x03
#घोषणा AB8500_BATT_OK_REG		0x04
/*
 * USB/ULPI रेजिस्टर offsets
 * Bank : 0x5
 */
#घोषणा AB8500_USB_LINE_STAT_REG	0x80
#घोषणा AB8500_USB_LINE_CTRL2_REG	0x82
#घोषणा AB8500_USB_LINK1_STAT_REG	0x94

/*
 * Charger / status रेजिस्टर offfsets
 * Bank : 0x0B
 */
#घोषणा AB8500_CH_STATUS1_REG		0x00
#घोषणा AB8500_CH_STATUS2_REG		0x01
#घोषणा AB8500_CH_USBCH_STAT1_REG	0x02
#घोषणा AB8500_CH_USBCH_STAT2_REG	0x03
#घोषणा AB8540_CH_USBCH_STAT3_REG	0x04
#घोषणा AB8500_CH_STAT_REG		0x05

/*
 * Charger / control रेजिस्टर offfsets
 * Bank : 0x0B
 */
#घोषणा AB8500_CH_VOLT_LVL_REG		0x40
#घोषणा AB8500_CH_VOLT_LVL_MAX_REG	0x41  /*Only in Cut2.0*/
#घोषणा AB8500_CH_OPT_CRNTLVL_REG	0x42
#घोषणा AB8500_CH_OPT_CRNTLVL_MAX_REG	0x43  /*Only in Cut2.0*/
#घोषणा AB8500_CH_WD_TIMER_REG		0x50
#घोषणा AB8500_CHARG_WD_CTRL		0x51
#घोषणा AB8500_BTEMP_HIGH_TH		0x52
#घोषणा AB8500_LED_INDICATOR_PWM_CTRL	0x53
#घोषणा AB8500_LED_INDICATOR_PWM_DUTY	0x54
#घोषणा AB8500_BATT_OVV			0x55
#घोषणा AB8500_CHARGER_CTRL		0x56
#घोषणा AB8500_BAT_CTRL_CURRENT_SOURCE	0x60  /*Only in Cut2.0*/

/*
 * Charger / मुख्य control रेजिस्टर offsets
 * Bank : 0x0B
 */
#घोषणा AB8500_MCH_CTRL1		0x80
#घोषणा AB8500_MCH_CTRL2		0x81
#घोषणा AB8500_MCH_IPT_CURLVL_REG	0x82
#घोषणा AB8500_CH_WD_REG		0x83

/*
 * Charger / USB control रेजिस्टर offsets
 * Bank : 0x0B
 */
#घोषणा AB8500_USBCH_CTRL1_REG		0xC0
#घोषणा AB8500_USBCH_CTRL2_REG		0xC1
#घोषणा AB8500_USBCH_IPT_CRNTLVL_REG	0xC2
#घोषणा AB8540_USB_PP_MODE_REG		0xC5
#घोषणा AB8540_USB_PP_CHR_REG		0xC6

/*
 * Gas Gauge रेजिस्टर offsets
 * Bank : 0x0C
 */
#घोषणा AB8500_GASG_CC_CTRL_REG		0x00
#घोषणा AB8500_GASG_CC_ACCU1_REG	0x01
#घोषणा AB8500_GASG_CC_ACCU2_REG	0x02
#घोषणा AB8500_GASG_CC_ACCU3_REG	0x03
#घोषणा AB8500_GASG_CC_ACCU4_REG	0x04
#घोषणा AB8500_GASG_CC_SMPL_CNTRL_REG	0x05
#घोषणा AB8500_GASG_CC_SMPL_CNTRH_REG	0x06
#घोषणा AB8500_GASG_CC_SMPL_CNVL_REG	0x07
#घोषणा AB8500_GASG_CC_SMPL_CNVH_REG	0x08
#घोषणा AB8500_GASG_CC_CNTR_AVGOFF_REG	0x09
#घोषणा AB8500_GASG_CC_OFFSET_REG	0x0A
#घोषणा AB8500_GASG_CC_NCOV_ACCU	0x10
#घोषणा AB8500_GASG_CC_NCOV_ACCU_CTRL	0x11
#घोषणा AB8500_GASG_CC_NCOV_ACCU_LOW	0x12
#घोषणा AB8500_GASG_CC_NCOV_ACCU_MED	0x13
#घोषणा AB8500_GASG_CC_NCOV_ACCU_HIGH	0x14

/*
 * Interrupt रेजिस्टर offsets
 * Bank : 0x0E
 */
#घोषणा AB8500_IT_SOURCE2_REG		0x01
#घोषणा AB8500_IT_SOURCE21_REG		0x14

/*
 * RTC रेजिस्टर offsets
 * Bank: 0x0F
 */
#घोषणा AB8500_RTC_BACKUP_CHG_REG	0x0C
#घोषणा AB8500_RTC_CC_CONF_REG		0x01
#घोषणा AB8500_RTC_CTRL_REG		0x0B
#घोषणा AB8500_RTC_CTRL1_REG		0x11

/*
 * OTP रेजिस्टर offsets
 * Bank : 0x15
 */
#घोषणा AB8500_OTP_CONF_15		0x0E

/* GPADC स्थिरants from AB8500 spec, UM0836 */
#घोषणा ADC_RESOLUTION			1024
#घोषणा ADC_CH_MAIN_MIN			0
#घोषणा ADC_CH_MAIN_MAX			20030
#घोषणा ADC_CH_VBUS_MIN			0
#घोषणा ADC_CH_VBUS_MAX			20030
#घोषणा ADC_CH_VBAT_MIN			2300
#घोषणा ADC_CH_VBAT_MAX			4800
#घोषणा ADC_CH_BKBAT_MIN		0
#घोषणा ADC_CH_BKBAT_MAX		3200

/* Main अक्षरge i/p current */
#घोषणा MAIN_CH_IP_CUR_0P9A		0x80
#घोषणा MAIN_CH_IP_CUR_1P0A		0x90
#घोषणा MAIN_CH_IP_CUR_1P1A		0xA0
#घोषणा MAIN_CH_IP_CUR_1P2A		0xB0
#घोषणा MAIN_CH_IP_CUR_1P3A		0xC0
#घोषणा MAIN_CH_IP_CUR_1P4A		0xD0
#घोषणा MAIN_CH_IP_CUR_1P5A		0xE0

/* ChVoltLevel */
#घोषणा CH_VOL_LVL_3P5			0x00
#घोषणा CH_VOL_LVL_4P0			0x14
#घोषणा CH_VOL_LVL_4P05			0x16
#घोषणा CH_VOL_LVL_4P1			0x1B
#घोषणा CH_VOL_LVL_4P15			0x20
#घोषणा CH_VOL_LVL_4P2			0x25
#घोषणा CH_VOL_LVL_4P6			0x4D

/* ChOutputCurrentLevel */
#घोषणा CH_OP_CUR_LVL_0P1		0x00
#घोषणा CH_OP_CUR_LVL_0P2		0x01
#घोषणा CH_OP_CUR_LVL_0P3		0x02
#घोषणा CH_OP_CUR_LVL_0P4		0x03
#घोषणा CH_OP_CUR_LVL_0P5		0x04
#घोषणा CH_OP_CUR_LVL_0P6		0x05
#घोषणा CH_OP_CUR_LVL_0P7		0x06
#घोषणा CH_OP_CUR_LVL_0P8		0x07
#घोषणा CH_OP_CUR_LVL_0P9		0x08
#घोषणा CH_OP_CUR_LVL_1P4		0x0D
#घोषणा CH_OP_CUR_LVL_1P5		0x0E
#घोषणा CH_OP_CUR_LVL_1P6		0x0F
#घोषणा CH_OP_CUR_LVL_2P		0x3F

/* BTEMP High thermal limits */
#घोषणा BTEMP_HIGH_TH_57_0		0x00
#घोषणा BTEMP_HIGH_TH_52		0x01
#घोषणा BTEMP_HIGH_TH_57_1		0x02
#घोषणा BTEMP_HIGH_TH_62		0x03

/* current is mA */
#घोषणा USB_0P1A			100
#घोषणा USB_0P2A			200
#घोषणा USB_0P3A			300
#घोषणा USB_0P4A			400
#घोषणा USB_0P5A			500

#घोषणा LOW_BAT_3P1V			0x20
#घोषणा LOW_BAT_2P3V			0x00
#घोषणा LOW_BAT_RESET			0x01
#घोषणा LOW_BAT_ENABLE			0x01

/* Backup battery स्थिरants */
#घोषणा BUP_ICH_SEL_50UA		0x00
#घोषणा BUP_ICH_SEL_150UA		0x04
#घोषणा BUP_ICH_SEL_300UA		0x08
#घोषणा BUP_ICH_SEL_700UA		0x0C

क्रमागत bup_vch_sel अणु
	BUP_VCH_SEL_2P5V,
	BUP_VCH_SEL_2P6V,
	BUP_VCH_SEL_2P8V,
	BUP_VCH_SEL_3P1V,
	/*
	 * Note that the following 5 values 2.7v, 2.9v, 3.0v, 3.2v, 3.3v
	 * are only available on ab8540. You can't choose these 5
	 * voltage on ab8500/ab8505/ab9540.
	 */
	BUP_VCH_SEL_2P7V,
	BUP_VCH_SEL_2P9V,
	BUP_VCH_SEL_3P0V,
	BUP_VCH_SEL_3P2V,
	BUP_VCH_SEL_3P3V,
पूर्ण;

#घोषणा BUP_VCH_RANGE		0x02
#घोषणा VBUP33_VRTCN		0x01

/* Battery OVV स्थिरants */
#घोषणा BATT_OVV_ENA			0x02
#घोषणा BATT_OVV_TH_3P7			0x00
#घोषणा BATT_OVV_TH_4P75		0x01

/* A value to indicate over voltage */
#घोषणा BATT_OVV_VALUE			4750

/* VBUS OVV स्थिरants */
#घोषणा VBUS_OVV_SELECT_MASK		0x78
#घोषणा VBUS_OVV_SELECT_5P6V		0x00
#घोषणा VBUS_OVV_SELECT_5P7V		0x08
#घोषणा VBUS_OVV_SELECT_5P8V		0x10
#घोषणा VBUS_OVV_SELECT_5P9V		0x18
#घोषणा VBUS_OVV_SELECT_6P0V		0x20
#घोषणा VBUS_OVV_SELECT_6P1V		0x28
#घोषणा VBUS_OVV_SELECT_6P2V		0x30
#घोषणा VBUS_OVV_SELECT_6P3V		0x38

#घोषणा VBUS_AUTO_IN_CURR_LIM_ENA	0x04

/* Fuel Gauge स्थिरants */
#घोषणा RESET_ACCU			0x02
#घोषणा READ_REQ			0x01
#घोषणा CC_DEEP_SLEEP_ENA		0x02
#घोषणा CC_PWR_UP_ENA			0x01
#घोषणा CC_SAMPLES_40			0x28
#घोषणा RD_NCONV_ACCU_REQ		0x01
#घोषणा CC_CALIB			0x08
#घोषणा CC_INTAVGOFFSET_ENA		0x10
#घोषणा CC_MUXOFFSET			0x80
#घोषणा CC_INT_CAL_N_AVG_MASK		0x60
#घोषणा CC_INT_CAL_SAMPLES_16		0x40
#घोषणा CC_INT_CAL_SAMPLES_8		0x20
#घोषणा CC_INT_CAL_SAMPLES_4		0x00

/* RTC स्थिरants */
#घोषणा RTC_BUP_CH_ENA			0x10

/* BatCtrl Current Source Constants */
#घोषणा BAT_CTRL_7U_ENA			0x01
#घोषणा BAT_CTRL_20U_ENA		0x02
#घोषणा BAT_CTRL_18U_ENA		0x01
#घोषणा BAT_CTRL_16U_ENA		0x02
#घोषणा BAT_CTRL_CMP_ENA		0x04
#घोषणा FORCE_BAT_CTRL_CMP_HIGH		0x08
#घोषणा BAT_CTRL_PULL_UP_ENA		0x10

/* Battery type */
#घोषणा BATTERY_UNKNOWN			00

/* Registers क्रम pcut feature in ab8505 and ab9540 */
#घोषणा AB8505_RTC_PCUT_CTL_STATUS_REG	0x12
#घोषणा AB8505_RTC_PCUT_TIME_REG	0x13
#घोषणा AB8505_RTC_PCUT_MAX_TIME_REG	0x14
#घोषणा AB8505_RTC_PCUT_FLAG_TIME_REG	0x15
#घोषणा AB8505_RTC_PCUT_RESTART_REG	0x16
#घोषणा AB8505_RTC_PCUT_DEBOUNCE_REG	0x17

/* USB Power Path स्थिरants क्रम ab8540 */
#घोषणा BUS_VSYS_VOL_SELECT_MASK		0x06
#घोषणा BUS_VSYS_VOL_SELECT_3P6V		0x00
#घोषणा BUS_VSYS_VOL_SELECT_3P325V		0x02
#घोषणा BUS_VSYS_VOL_SELECT_3P9V		0x04
#घोषणा BUS_VSYS_VOL_SELECT_4P3V		0x06
#घोषणा BUS_POWER_PATH_MODE_ENA			0x01
#घोषणा BUS_PP_PRECHG_CURRENT_MASK		0x0E
#घोषणा BUS_POWER_PATH_PRECHG_ENA		0x01

/*
 * ADC क्रम the battery thermistor.
 * When using the ABx500_ADC_THERM_BATCTRL the battery ID resistor is combined
 * with a NTC resistor to both identअगरy the battery and to measure its
 * temperature. Dअगरferent phone manufactures uses dअगरferent techniques to both
 * identअगरy the battery and to पढ़ो its temperature.
 */
क्रमागत abx500_adc_therm अणु
	ABx500_ADC_THERM_BATCTRL,
	ABx500_ADC_THERM_BATTEMP,
पूर्ण;

/**
 * काष्ठा abx500_res_to_temp - defines one poपूर्णांक in a temp to res curve. To
 * be used in battery packs that combines the identअगरication resistor with a
 * NTC resistor.
 * @temp:			battery pack temperature in Celsius
 * @resist:			NTC resistor net total resistance
 */
काष्ठा abx500_res_to_temp अणु
	पूर्णांक temp;
	पूर्णांक resist;
पूर्ण;

/**
 * काष्ठा abx500_v_to_cap - Table क्रम translating voltage to capacity
 * @voltage:		Voltage in mV
 * @capacity:		Capacity in percent
 */
काष्ठा abx500_v_to_cap अणु
	पूर्णांक voltage;
	पूर्णांक capacity;
पूर्ण;

/* Forward declaration */
काष्ठा abx500_fg;

/**
 * काष्ठा abx500_fg_parameters - Fuel gauge algorithm parameters, in seconds
 * अगर not specअगरied
 * @recovery_sleep_समयr:	Time between measurements जबतक recovering
 * @recovery_total_समय:	Total recovery समय
 * @init_समयr:			Measurement पूर्णांकerval during startup
 * @init_discard_समय:		Time we discard voltage measurement at startup
 * @init_total_समय:		Total init समय during startup
 * @high_curr_समय:		Time current has to be high to go to recovery
 * @accu_अक्षरging:		FG accumulation समय जबतक अक्षरging
 * @accu_high_curr:		FG accumulation समय in high current mode
 * @high_curr_threshold:	High current threshold, in mA
 * @lowbat_threshold:		Low battery threshold, in mV
 * @overbat_threshold:		Over battery threshold, in mV
 * @battok_falling_th_sel0	Threshold in mV क्रम battOk संकेत sel0
 *				Resolution in 50 mV step.
 * @battok_raising_th_sel1	Threshold in mV क्रम battOk संकेत sel1
 *				Resolution in 50 mV step.
 * @user_cap_limit		Capacity reported from user must be within this
 *				limit to be considered as sane, in percentage
 *				poपूर्णांकs.
 * @मुख्यt_thres			This is the threshold where we stop reporting
 *				battery full जबतक in मुख्यtenance, in per cent
 * @pcut_enable:			Enable घातer cut feature in ab8505
 * @pcut_max_समय:		Max समय threshold
 * @pcut_flag_समय:		Flagसमय threshold
 * @pcut_max_restart:		Max number of restarts
 * @pcut_debounce_समय:		Sets battery debounce समय
 */
काष्ठा abx500_fg_parameters अणु
	पूर्णांक recovery_sleep_समयr;
	पूर्णांक recovery_total_समय;
	पूर्णांक init_समयr;
	पूर्णांक init_discard_समय;
	पूर्णांक init_total_समय;
	पूर्णांक high_curr_समय;
	पूर्णांक accu_अक्षरging;
	पूर्णांक accu_high_curr;
	पूर्णांक high_curr_threshold;
	पूर्णांक lowbat_threshold;
	पूर्णांक overbat_threshold;
	पूर्णांक battok_falling_th_sel0;
	पूर्णांक battok_raising_th_sel1;
	पूर्णांक user_cap_limit;
	पूर्णांक मुख्यt_thres;
	bool pcut_enable;
	u8 pcut_max_समय;
	u8 pcut_flag_समय;
	u8 pcut_max_restart;
	u8 pcut_debounce_समय;
पूर्ण;

/**
 * काष्ठा abx500_अक्षरger_maximization - काष्ठा used by the board config.
 * @use_maxi:		Enable maximization क्रम this battery type
 * @maxi_chg_curr:	Maximum अक्षरger current allowed
 * @maxi_रुको_cycles:	cycles to रुको beक्रमe setting अक्षरger current
 * @अक्षरger_curr_step	delta between two अक्षरger current settings (mA)
 */
काष्ठा abx500_maxim_parameters अणु
	bool ena_maxi;
	पूर्णांक chg_curr;
	पूर्णांक रुको_cycles;
	पूर्णांक अक्षरger_curr_step;
पूर्ण;

/**
 * काष्ठा abx500_battery_type - dअगरferent batteries supported
 * @name:			battery technology
 * @resis_high:			battery upper resistance limit
 * @resis_low:			battery lower resistance limit
 * @अक्षरge_full_design:		Maximum battery capacity in mAh
 * @nominal_voltage:		Nominal voltage of the battery in mV
 * @termination_vol:		max voltage upto which battery can be अक्षरged
 * @termination_curr		battery अक्षरging termination current in mA
 * @reअक्षरge_cap		battery capacity limit that will trigger a new
 *				full अक्षरging cycle in the हाल where मुख्यtenan-
 *				-ce अक्षरging has been disabled
 * @normal_cur_lvl:		अक्षरger current in normal state in mA
 * @normal_vol_lvl:		अक्षरger voltage in normal state in mV
 * @मुख्यt_a_cur_lvl:		अक्षरger current in मुख्यtenance A state in mA
 * @मुख्यt_a_vol_lvl:		अक्षरger voltage in मुख्यtenance A state in mV
 * @मुख्यt_a_chg_समयr_h:	अक्षरge समय in मुख्यtenance A state
 * @मुख्यt_b_cur_lvl:		अक्षरger current in मुख्यtenance B state in mA
 * @मुख्यt_b_vol_lvl:		अक्षरger voltage in मुख्यtenance B state in mV
 * @मुख्यt_b_chg_समयr_h:	अक्षरge समय in मुख्यtenance B state
 * @low_high_cur_lvl:		अक्षरger current in temp low/high state in mA
 * @low_high_vol_lvl:		अक्षरger voltage in temp low/high state in mV'
 * @battery_resistance:		battery inner resistance in mOhm.
 * @n_r_t_tbl_elements:		number of elements in r_to_t_tbl
 * @r_to_t_tbl:			table containing resistance to temp poपूर्णांकs
 * @n_v_cap_tbl_elements:	number of elements in v_to_cap_tbl
 * @v_to_cap_tbl:		Voltage to capacity (in %) table
 * @n_batres_tbl_elements	number of elements in the batres_tbl
 * @batres_tbl			battery पूर्णांकernal resistance vs temperature table
 */
काष्ठा abx500_battery_type अणु
	पूर्णांक name;
	पूर्णांक resis_high;
	पूर्णांक resis_low;
	पूर्णांक अक्षरge_full_design;
	पूर्णांक nominal_voltage;
	पूर्णांक termination_vol;
	पूर्णांक termination_curr;
	पूर्णांक reअक्षरge_cap;
	पूर्णांक normal_cur_lvl;
	पूर्णांक normal_vol_lvl;
	पूर्णांक मुख्यt_a_cur_lvl;
	पूर्णांक मुख्यt_a_vol_lvl;
	पूर्णांक मुख्यt_a_chg_समयr_h;
	पूर्णांक मुख्यt_b_cur_lvl;
	पूर्णांक मुख्यt_b_vol_lvl;
	पूर्णांक मुख्यt_b_chg_समयr_h;
	पूर्णांक low_high_cur_lvl;
	पूर्णांक low_high_vol_lvl;
	पूर्णांक battery_resistance;
	पूर्णांक n_temp_tbl_elements;
	स्थिर काष्ठा abx500_res_to_temp *r_to_t_tbl;
	पूर्णांक n_v_cap_tbl_elements;
	स्थिर काष्ठा abx500_v_to_cap *v_to_cap_tbl;
	पूर्णांक n_batres_tbl_elements;
	स्थिर काष्ठा batres_vs_temp *batres_tbl;
पूर्ण;

/**
 * काष्ठा abx500_bm_capacity_levels - abx500 capacity level data
 * @critical:		critical capacity level in percent
 * @low:		low capacity level in percent
 * @normal:		normal capacity level in percent
 * @high:		high capacity level in percent
 * @full:		full capacity level in percent
 */
काष्ठा abx500_bm_capacity_levels अणु
	पूर्णांक critical;
	पूर्णांक low;
	पूर्णांक normal;
	पूर्णांक high;
	पूर्णांक full;
पूर्ण;

/**
 * काष्ठा abx500_bm_अक्षरger_parameters - Charger specअगरic parameters
 * @usb_volt_max:	maximum allowed USB अक्षरger voltage in mV
 * @usb_curr_max:	maximum allowed USB अक्षरger current in mA
 * @ac_volt_max:	maximum allowed AC अक्षरger voltage in mV
 * @ac_curr_max:	maximum allowed AC अक्षरger current in mA
 */
काष्ठा abx500_bm_अक्षरger_parameters अणु
	पूर्णांक usb_volt_max;
	पूर्णांक usb_curr_max;
	पूर्णांक ac_volt_max;
	पूर्णांक ac_curr_max;
पूर्ण;

/**
 * काष्ठा abx500_bm_data - abx500 battery management data
 * @temp_under		under this temp, अक्षरging is stopped
 * @temp_low		between this temp and temp_under अक्षरging is reduced
 * @temp_high		between this temp and temp_over अक्षरging is reduced
 * @temp_over		over this temp, अक्षरging is stopped
 * @temp_now		present battery temperature
 * @temp_पूर्णांकerval_chg	temperature measurement पूर्णांकerval in s when अक्षरging
 * @temp_पूर्णांकerval_nochg	temperature measurement पूर्णांकerval in s when not अक्षरging
 * @मुख्य_safety_पंचांगr_h	safety समयr क्रम मुख्य अक्षरger
 * @usb_safety_पंचांगr_h	safety समयr क्रम usb अक्षरger
 * @bkup_bat_v		voltage which we अक्षरge the backup battery with
 * @bkup_bat_i		current which we अक्षरge the backup battery with
 * @no_मुख्यtenance	indicates that मुख्यtenance अक्षरging is disabled
 * @capacity_scaling    indicates whether capacity scaling is to be used
 * @abx500_adc_therm	placement of thermistor, batctrl or battemp adc
 * @chg_unknown_bat	flag to enable अक्षरging of unknown batteries
 * @enable_overshoot	flag to enable VBAT overshoot control
 * @स्वतः_trig		flag to enable स्वतः adc trigger
 * @fg_res		resistance of FG resistor in 0.1mOhm
 * @n_btypes		number of elements in array bat_type
 * @batt_id		index of the identअगरied battery in array bat_type
 * @पूर्णांकerval_अक्षरging	अक्षरge alg cycle period समय when अक्षरging (sec)
 * @पूर्णांकerval_not_अक्षरging अक्षरge alg cycle period समय when not अक्षरging (sec)
 * @temp_hysteresis	temperature hysteresis
 * @gnd_lअगरt_resistance	Battery ground to phone ground resistance (mOhm)
 * @n_chg_out_curr		number of elements in array chg_output_curr
 * @n_chg_in_curr		number of elements in array chg_input_curr
 * @chg_output_curr	अक्षरger output current level map
 * @chg_input_curr		अक्षरger input current level map
 * @maxi		maximization parameters
 * @cap_levels		capacity in percent क्रम the dअगरferent capacity levels
 * @bat_type		table of supported battery types
 * @chg_params		अक्षरger parameters
 * @fg_params		fuel gauge parameters
 */
काष्ठा abx500_bm_data अणु
	पूर्णांक temp_under;
	पूर्णांक temp_low;
	पूर्णांक temp_high;
	पूर्णांक temp_over;
	पूर्णांक temp_now;
	पूर्णांक temp_पूर्णांकerval_chg;
	पूर्णांक temp_पूर्णांकerval_nochg;
	पूर्णांक मुख्य_safety_पंचांगr_h;
	पूर्णांक usb_safety_पंचांगr_h;
	पूर्णांक bkup_bat_v;
	पूर्णांक bkup_bat_i;
	bool स्वतःघातer_cfg;
	bool ac_enabled;
	bool usb_enabled;
	bool no_मुख्यtenance;
	bool capacity_scaling;
	bool chg_unknown_bat;
	bool enable_overshoot;
	bool स्वतः_trig;
	क्रमागत abx500_adc_therm adc_therm;
	पूर्णांक fg_res;
	पूर्णांक n_btypes;
	पूर्णांक batt_id;
	पूर्णांक पूर्णांकerval_अक्षरging;
	पूर्णांक पूर्णांकerval_not_अक्षरging;
	पूर्णांक temp_hysteresis;
	पूर्णांक gnd_lअगरt_resistance;
	पूर्णांक n_chg_out_curr;
	पूर्णांक n_chg_in_curr;
	पूर्णांक *chg_output_curr;
	पूर्णांक *chg_input_curr;
	स्थिर काष्ठा abx500_maxim_parameters *maxi;
	स्थिर काष्ठा abx500_bm_capacity_levels *cap_levels;
	काष्ठा abx500_battery_type *bat_type;
	स्थिर काष्ठा abx500_bm_अक्षरger_parameters *chg_params;
	स्थिर काष्ठा abx500_fg_parameters *fg_params;
पूर्ण;

क्रमागत अणु
	NTC_EXTERNAL = 0,
	NTC_INTERNAL,
पूर्ण;

/**
 * काष्ठा res_to_temp - defines one poपूर्णांक in a temp to res curve. To
 * be used in battery packs that combines the identअगरication resistor with a
 * NTC resistor.
 * @temp:			battery pack temperature in Celsius
 * @resist:			NTC resistor net total resistance
 */
काष्ठा res_to_temp अणु
	पूर्णांक temp;
	पूर्णांक resist;
पूर्ण;

/**
 * काष्ठा batres_vs_temp - defines one poपूर्णांक in a temp vs battery पूर्णांकernal
 * resistance curve.
 * @temp:			battery pack temperature in Celsius
 * @resist:			battery पूर्णांकernal reistance in mOhm
 */
काष्ठा batres_vs_temp अणु
	पूर्णांक temp;
	पूर्णांक resist;
पूर्ण;

/* Forward declaration */
काष्ठा ab8500_fg;

/**
 * काष्ठा ab8500_fg_parameters - Fuel gauge algorithm parameters, in seconds
 * अगर not specअगरied
 * @recovery_sleep_समयr:	Time between measurements जबतक recovering
 * @recovery_total_समय:	Total recovery समय
 * @init_समयr:			Measurement पूर्णांकerval during startup
 * @init_discard_समय:		Time we discard voltage measurement at startup
 * @init_total_समय:		Total init समय during startup
 * @high_curr_समय:		Time current has to be high to go to recovery
 * @accu_अक्षरging:		FG accumulation समय जबतक अक्षरging
 * @accu_high_curr:		FG accumulation समय in high current mode
 * @high_curr_threshold:	High current threshold, in mA
 * @lowbat_threshold:		Low battery threshold, in mV
 * @battok_falling_th_sel0	Threshold in mV क्रम battOk संकेत sel0
 *				Resolution in 50 mV step.
 * @battok_raising_th_sel1	Threshold in mV क्रम battOk संकेत sel1
 *				Resolution in 50 mV step.
 * @user_cap_limit		Capacity reported from user must be within this
 *				limit to be considered as sane, in percentage
 *				poपूर्णांकs.
 * @मुख्यt_thres			This is the threshold where we stop reporting
 *				battery full जबतक in मुख्यtenance, in per cent
 * @pcut_enable:			Enable घातer cut feature in ab8505
 * @pcut_max_समय:		Max समय threshold
 * @pcut_flag_समय:		Flagसमय threshold
 * @pcut_max_restart:		Max number of restarts
 * @pcut_debunce_समय:	Sets battery debounce समय
 */
काष्ठा ab8500_fg_parameters अणु
	पूर्णांक recovery_sleep_समयr;
	पूर्णांक recovery_total_समय;
	पूर्णांक init_समयr;
	पूर्णांक init_discard_समय;
	पूर्णांक init_total_समय;
	पूर्णांक high_curr_समय;
	पूर्णांक accu_अक्षरging;
	पूर्णांक accu_high_curr;
	पूर्णांक high_curr_threshold;
	पूर्णांक lowbat_threshold;
	पूर्णांक battok_falling_th_sel0;
	पूर्णांक battok_raising_th_sel1;
	पूर्णांक user_cap_limit;
	पूर्णांक मुख्यt_thres;
	bool pcut_enable;
	u8 pcut_max_समय;
	u8 pcut_flag_समय;
	u8 pcut_max_restart;
	u8 pcut_debunce_समय;
पूर्ण;

/**
 * काष्ठा ab8500_अक्षरger_maximization - काष्ठा used by the board config.
 * @use_maxi:		Enable maximization क्रम this battery type
 * @maxi_chg_curr:	Maximum अक्षरger current allowed
 * @maxi_रुको_cycles:	cycles to रुको beक्रमe setting अक्षरger current
 * @अक्षरger_curr_step	delta between two अक्षरger current settings (mA)
 */
काष्ठा ab8500_maxim_parameters अणु
	bool ena_maxi;
	पूर्णांक chg_curr;
	पूर्णांक रुको_cycles;
	पूर्णांक अक्षरger_curr_step;
पूर्ण;

/**
 * काष्ठा ab8500_bm_capacity_levels - ab8500 capacity level data
 * @critical:		critical capacity level in percent
 * @low:		low capacity level in percent
 * @normal:		normal capacity level in percent
 * @high:		high capacity level in percent
 * @full:		full capacity level in percent
 */
काष्ठा ab8500_bm_capacity_levels अणु
	पूर्णांक critical;
	पूर्णांक low;
	पूर्णांक normal;
	पूर्णांक high;
	पूर्णांक full;
पूर्ण;

/**
 * काष्ठा ab8500_bm_अक्षरger_parameters - Charger specअगरic parameters
 * @usb_volt_max:	maximum allowed USB अक्षरger voltage in mV
 * @usb_curr_max:	maximum allowed USB अक्षरger current in mA
 * @ac_volt_max:	maximum allowed AC अक्षरger voltage in mV
 * @ac_curr_max:	maximum allowed AC अक्षरger current in mA
 */
काष्ठा ab8500_bm_अक्षरger_parameters अणु
	पूर्णांक usb_volt_max;
	पूर्णांक usb_curr_max;
	पूर्णांक ac_volt_max;
	पूर्णांक ac_curr_max;
पूर्ण;

/**
 * काष्ठा ab8500_bm_data - ab8500 battery management data
 * @temp_under		under this temp, अक्षरging is stopped
 * @temp_low		between this temp and temp_under अक्षरging is reduced
 * @temp_high		between this temp and temp_over अक्षरging is reduced
 * @temp_over		over this temp, अक्षरging is stopped
 * @temp_पूर्णांकerval_chg	temperature measurement पूर्णांकerval in s when अक्षरging
 * @temp_पूर्णांकerval_nochg	temperature measurement पूर्णांकerval in s when not अक्षरging
 * @मुख्य_safety_पंचांगr_h	safety समयr क्रम मुख्य अक्षरger
 * @usb_safety_पंचांगr_h	safety समयr क्रम usb अक्षरger
 * @bkup_bat_v		voltage which we अक्षरge the backup battery with
 * @bkup_bat_i		current which we अक्षरge the backup battery with
 * @no_मुख्यtenance	indicates that मुख्यtenance अक्षरging is disabled
 * @capacity_scaling    indicates whether capacity scaling is to be used
 * @adc_therm		placement of thermistor, batctrl or battemp adc
 * @chg_unknown_bat	flag to enable अक्षरging of unknown batteries
 * @enable_overshoot	flag to enable VBAT overshoot control
 * @fg_res		resistance of FG resistor in 0.1mOhm
 * @n_btypes		number of elements in array bat_type
 * @batt_id		index of the identअगरied battery in array bat_type
 * @पूर्णांकerval_अक्षरging	अक्षरge alg cycle period समय when अक्षरging (sec)
 * @पूर्णांकerval_not_अक्षरging अक्षरge alg cycle period समय when not अक्षरging (sec)
 * @temp_hysteresis	temperature hysteresis
 * @gnd_lअगरt_resistance	Battery ground to phone ground resistance (mOhm)
 * @maxi:		maximization parameters
 * @cap_levels		capacity in percent क्रम the dअगरferent capacity levels
 * @bat_type		table of supported battery types
 * @chg_params		अक्षरger parameters
 * @fg_params		fuel gauge parameters
 */
काष्ठा ab8500_bm_data अणु
	पूर्णांक temp_under;
	पूर्णांक temp_low;
	पूर्णांक temp_high;
	पूर्णांक temp_over;
	पूर्णांक temp_पूर्णांकerval_chg;
	पूर्णांक temp_पूर्णांकerval_nochg;
	पूर्णांक मुख्य_safety_पंचांगr_h;
	पूर्णांक usb_safety_पंचांगr_h;
	पूर्णांक bkup_bat_v;
	पूर्णांक bkup_bat_i;
	bool no_मुख्यtenance;
	bool capacity_scaling;
	bool chg_unknown_bat;
	bool enable_overshoot;
	क्रमागत abx500_adc_therm adc_therm;
	पूर्णांक fg_res;
	पूर्णांक n_btypes;
	पूर्णांक batt_id;
	पूर्णांक पूर्णांकerval_अक्षरging;
	पूर्णांक पूर्णांकerval_not_अक्षरging;
	पूर्णांक temp_hysteresis;
	पूर्णांक gnd_lअगरt_resistance;
	स्थिर काष्ठा ab8500_maxim_parameters *maxi;
	स्थिर काष्ठा ab8500_bm_capacity_levels *cap_levels;
	स्थिर काष्ठा ab8500_bm_अक्षरger_parameters *chg_params;
	स्थिर काष्ठा ab8500_fg_parameters *fg_params;
पूर्ण;

बाह्य काष्ठा abx500_bm_data ab8500_bm_data;

व्योम ab8500_अक्षरger_usb_state_changed(u8 bm_usb_state, u16 mA);
काष्ठा ab8500_fg *ab8500_fg_get(व्योम);
पूर्णांक ab8500_fg_inst_curr_blocking(काष्ठा ab8500_fg *dev);
पूर्णांक ab8500_fg_inst_curr_start(काष्ठा ab8500_fg *di);
पूर्णांक ab8500_fg_inst_curr_finalize(काष्ठा ab8500_fg *di, पूर्णांक *res);
पूर्णांक ab8500_fg_inst_curr_started(काष्ठा ab8500_fg *di);
पूर्णांक ab8500_fg_inst_curr_करोne(काष्ठा ab8500_fg *di);
पूर्णांक ab8500_bm_of_probe(काष्ठा device *dev,
		       काष्ठा device_node *np,
		       काष्ठा abx500_bm_data *bm);

#पूर्ण_अगर /* _AB8500_CHARGER_H_ */
