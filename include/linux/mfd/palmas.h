<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * TI Palmas
 *
 * Copyright 2011-2013 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Ian Lartey <ian@slimlogic.co.uk>
 */

#अगर_अघोषित __LINUX_MFD_PALMAS_H
#घोषणा __LINUX_MFD_PALMAS_H

#समावेश <linux/usb/otg.h>
#समावेश <linux/leds.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/usb/phy_companion.h>

#घोषणा PALMAS_NUM_CLIENTS		3

/* The ID_REVISION NUMBERS */
#घोषणा PALMAS_CHIP_OLD_ID		0x0000
#घोषणा PALMAS_CHIP_ID			0xC035
#घोषणा PALMAS_CHIP_CHARGER_ID		0xC036

#घोषणा TPS65917_RESERVED		-1

#घोषणा is_palmas(a)	(((a) == PALMAS_CHIP_OLD_ID) || \
			((a) == PALMAS_CHIP_ID))
#घोषणा is_palmas_अक्षरger(a) ((a) == PALMAS_CHIP_CHARGER_ID)

/**
 * Palmas PMIC feature types
 *
 * PALMAS_PMIC_FEATURE_SMPS10_BOOST - used when the PMIC provides SMPS10_BOOST
 *	regulator.
 *
 * PALMAS_PMIC_HAS(b, f) - macro to check अगर a bandgap device is capable of a
 *	specअगरic feature (above) or not. Return non-zero, अगर yes.
 */
#घोषणा PALMAS_PMIC_FEATURE_SMPS10_BOOST	BIT(0)
#घोषणा PALMAS_PMIC_HAS(b, f)			\
			((b)->features & PALMAS_PMIC_FEATURE_ ## f)

काष्ठा palmas_pmic;
काष्ठा palmas_gpadc;
काष्ठा palmas_resource;
काष्ठा palmas_usb;
काष्ठा palmas_pmic_driver_data;
काष्ठा palmas_pmic_platक्रमm_data;

क्रमागत palmas_usb_state अणु
	PALMAS_USB_STATE_DISCONNECT,
	PALMAS_USB_STATE_VBUS,
	PALMAS_USB_STATE_ID,
पूर्ण;

काष्ठा palmas अणु
	काष्ठा device *dev;

	काष्ठा i2c_client *i2c_clients[PALMAS_NUM_CLIENTS];
	काष्ठा regmap *regmap[PALMAS_NUM_CLIENTS];

	/* Stored chip id */
	पूर्णांक id;

	अचिन्हित पूर्णांक features;
	/* IRQ Data */
	पूर्णांक irq;
	u32 irq_mask;
	काष्ठा mutex irq_lock;
	काष्ठा regmap_irq_chip_data *irq_data;

	काष्ठा palmas_pmic_driver_data *pmic_ddata;

	/* Child Devices */
	काष्ठा palmas_pmic *pmic;
	काष्ठा palmas_gpadc *gpadc;
	काष्ठा palmas_resource *resource;
	काष्ठा palmas_usb *usb;

	/* GPIO MUXing */
	u8 gpio_muxed;
	u8 led_muxed;
	u8 pwm_muxed;
पूर्ण;

#घोषणा PALMAS_EXT_REQ (PALMAS_EXT_CONTROL_ENABLE1 |	\
			PALMAS_EXT_CONTROL_ENABLE2 |	\
			PALMAS_EXT_CONTROL_NSLEEP)

काष्ठा palmas_sleep_requestor_info अणु
	पूर्णांक id;
	पूर्णांक reg_offset;
	पूर्णांक bit_pos;
पूर्ण;

काष्ठा palmas_regs_info अणु
	अक्षर	*name;
	अक्षर	*sname;
	u8	vsel_addr;
	u8	ctrl_addr;
	u8	tstep_addr;
	पूर्णांक	sleep_id;
पूर्ण;

काष्ठा palmas_pmic_driver_data अणु
	पूर्णांक smps_start;
	पूर्णांक smps_end;
	पूर्णांक lकरो_begin;
	पूर्णांक lकरो_end;
	पूर्णांक max_reg;
	bool has_regen3;
	काष्ठा palmas_regs_info *palmas_regs_info;
	काष्ठा of_regulator_match *palmas_matches;
	काष्ठा palmas_sleep_requestor_info *sleep_req_info;
	पूर्णांक (*smps_रेजिस्टर)(काष्ठा palmas_pmic *pmic,
			     काष्ठा palmas_pmic_driver_data *ddata,
			     काष्ठा palmas_pmic_platक्रमm_data *pdata,
			     स्थिर अक्षर *pdev_name,
			     काष्ठा regulator_config config);
	पूर्णांक (*lकरो_रेजिस्टर)(काष्ठा palmas_pmic *pmic,
			    काष्ठा palmas_pmic_driver_data *ddata,
			    काष्ठा palmas_pmic_platक्रमm_data *pdata,
			    स्थिर अक्षर *pdev_name,
			    काष्ठा regulator_config config);
पूर्ण;

काष्ठा palmas_adc_wakeup_property अणु
	पूर्णांक adc_channel_number;
	पूर्णांक adc_high_threshold;
	पूर्णांक adc_low_threshold;
पूर्ण;

काष्ठा palmas_gpadc_platक्रमm_data अणु
	/* Channel 3 current source is only enabled during conversion */
	पूर्णांक ch3_current;	/* 0: off; 1: 10uA; 2: 400uA; 3: 800 uA */

	/* Channel 0 current source can be used क्रम battery detection.
	 * If used क्रम battery detection this will cause a permanent current
	 * consumption depending on current level set here.
	 */
	पूर्णांक ch0_current;	/* 0: off; 1: 5uA; 2: 15uA; 3: 20 uA */
	bool extended_delay;	/* use extended delay क्रम conversion */

	/* शेष BAT_REMOVAL_DAT setting on device probe */
	पूर्णांक bat_removal;

	/* Sets the START_POLARITY bit in the RT_CTRL रेजिस्टर */
	पूर्णांक start_polarity;

	पूर्णांक स्वतः_conversion_period_ms;
	काष्ठा palmas_adc_wakeup_property *adc_wakeup1_data;
	काष्ठा palmas_adc_wakeup_property *adc_wakeup2_data;
पूर्ण;

काष्ठा palmas_reg_init अणु
	/* warm_rest controls the voltage levels after a warm reset
	 *
	 * 0: reload शेष values from OTP on warm reset
	 * 1: मुख्यtain voltage from VSEL on warm reset
	 */
	पूर्णांक warm_reset;

	/* roof_न्यूनमान controls whether the regulator uses the i2c style
	 * of DVS or uses the method where a GPIO or other control method is
	 * attached to the NSLEEP/ENABLE1/ENABLE2 pins
	 *
	 * For SMPS
	 *
	 * 0: i2c selection of voltage
	 * 1: pin selection of voltage.
	 *
	 * For LDO unused
	 */
	पूर्णांक roof_न्यूनमान;

	/* sleep_mode is the mode loaded to MODE_SLEEP bits as defined in
	 * the data sheet.
	 *
	 * For SMPS
	 *
	 * 0: Off
	 * 1: AUTO
	 * 2: ECO
	 * 3: Forced PWM
	 *
	 * For LDO
	 *
	 * 0: Off
	 * 1: On
	 */
	पूर्णांक mode_sleep;

	/* voltage_sel is the bitfield loaded onto the SMPSX_VOLTAGE
	 * रेजिस्टर. Set this is the शेष voltage set in OTP needs
	 * to be overridden.
	 */
	u8 vsel;

पूर्ण;

क्रमागत palmas_regulators अणु
	/* SMPS regulators */
	PALMAS_REG_SMPS12,
	PALMAS_REG_SMPS123,
	PALMAS_REG_SMPS3,
	PALMAS_REG_SMPS45,
	PALMAS_REG_SMPS457,
	PALMAS_REG_SMPS6,
	PALMAS_REG_SMPS7,
	PALMAS_REG_SMPS8,
	PALMAS_REG_SMPS9,
	PALMAS_REG_SMPS10_OUT2,
	PALMAS_REG_SMPS10_OUT1,
	/* LDO regulators */
	PALMAS_REG_LDO1,
	PALMAS_REG_LDO2,
	PALMAS_REG_LDO3,
	PALMAS_REG_LDO4,
	PALMAS_REG_LDO5,
	PALMAS_REG_LDO6,
	PALMAS_REG_LDO7,
	PALMAS_REG_LDO8,
	PALMAS_REG_LDO9,
	PALMAS_REG_LDOLN,
	PALMAS_REG_LDOUSB,
	/* External regulators */
	PALMAS_REG_REGEN1,
	PALMAS_REG_REGEN2,
	PALMAS_REG_REGEN3,
	PALMAS_REG_SYSEN1,
	PALMAS_REG_SYSEN2,
	/* Total number of regulators */
	PALMAS_NUM_REGS,
पूर्ण;

क्रमागत tps65917_regulators अणु
	/* SMPS regulators */
	TPS65917_REG_SMPS1,
	TPS65917_REG_SMPS2,
	TPS65917_REG_SMPS3,
	TPS65917_REG_SMPS4,
	TPS65917_REG_SMPS5,
	TPS65917_REG_SMPS12,
	/* LDO regulators */
	TPS65917_REG_LDO1,
	TPS65917_REG_LDO2,
	TPS65917_REG_LDO3,
	TPS65917_REG_LDO4,
	TPS65917_REG_LDO5,
	TPS65917_REG_REGEN1,
	TPS65917_REG_REGEN2,
	TPS65917_REG_REGEN3,

	/* Total number of regulators */
	TPS65917_NUM_REGS,
पूर्ण;

/* External controll संकेत name */
क्रमागत अणु
	PALMAS_EXT_CONTROL_ENABLE1      = 0x1,
	PALMAS_EXT_CONTROL_ENABLE2      = 0x2,
	PALMAS_EXT_CONTROL_NSLEEP       = 0x4,
पूर्ण;

/*
 * Palmas device resources can be controlled बाह्यally क्रम
 * enabling/disabling it rather than रेजिस्टर ग_लिखो through i2c.
 * Add the बाह्यal controlled requestor ID क्रम dअगरferent resources.
 */
क्रमागत palmas_बाह्यal_requestor_id अणु
	PALMAS_EXTERNAL_REQSTR_ID_REGEN1,
	PALMAS_EXTERNAL_REQSTR_ID_REGEN2,
	PALMAS_EXTERNAL_REQSTR_ID_SYSEN1,
	PALMAS_EXTERNAL_REQSTR_ID_SYSEN2,
	PALMAS_EXTERNAL_REQSTR_ID_CLK32KG,
	PALMAS_EXTERNAL_REQSTR_ID_CLK32KGAUDIO,
	PALMAS_EXTERNAL_REQSTR_ID_REGEN3,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS12,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS3,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS45,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS6,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS7,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS8,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS9,
	PALMAS_EXTERNAL_REQSTR_ID_SMPS10,
	PALMAS_EXTERNAL_REQSTR_ID_LDO1,
	PALMAS_EXTERNAL_REQSTR_ID_LDO2,
	PALMAS_EXTERNAL_REQSTR_ID_LDO3,
	PALMAS_EXTERNAL_REQSTR_ID_LDO4,
	PALMAS_EXTERNAL_REQSTR_ID_LDO5,
	PALMAS_EXTERNAL_REQSTR_ID_LDO6,
	PALMAS_EXTERNAL_REQSTR_ID_LDO7,
	PALMAS_EXTERNAL_REQSTR_ID_LDO8,
	PALMAS_EXTERNAL_REQSTR_ID_LDO9,
	PALMAS_EXTERNAL_REQSTR_ID_LDOLN,
	PALMAS_EXTERNAL_REQSTR_ID_LDOUSB,

	/* Last entry */
	PALMAS_EXTERNAL_REQSTR_ID_MAX,
पूर्ण;

क्रमागत tps65917_बाह्यal_requestor_id अणु
	TPS65917_EXTERNAL_REQSTR_ID_REGEN1,
	TPS65917_EXTERNAL_REQSTR_ID_REGEN2,
	TPS65917_EXTERNAL_REQSTR_ID_REGEN3,
	TPS65917_EXTERNAL_REQSTR_ID_SMPS1,
	TPS65917_EXTERNAL_REQSTR_ID_SMPS2,
	TPS65917_EXTERNAL_REQSTR_ID_SMPS3,
	TPS65917_EXTERNAL_REQSTR_ID_SMPS4,
	TPS65917_EXTERNAL_REQSTR_ID_SMPS5,
	TPS65917_EXTERNAL_REQSTR_ID_SMPS12,
	TPS65917_EXTERNAL_REQSTR_ID_LDO1,
	TPS65917_EXTERNAL_REQSTR_ID_LDO2,
	TPS65917_EXTERNAL_REQSTR_ID_LDO3,
	TPS65917_EXTERNAL_REQSTR_ID_LDO4,
	TPS65917_EXTERNAL_REQSTR_ID_LDO5,
	/* Last entry */
	TPS65917_EXTERNAL_REQSTR_ID_MAX,
पूर्ण;

काष्ठा palmas_pmic_platक्रमm_data अणु
	/* An array of poपूर्णांकers to regulator init data indexed by regulator
	 * ID
	 */
	काष्ठा regulator_init_data *reg_data[PALMAS_NUM_REGS];

	/* An array of poपूर्णांकers to काष्ठाures containing sleep mode and DVS
	 * configuration क्रम regulators indexed by ID
	 */
	काष्ठा palmas_reg_init *reg_init[PALMAS_NUM_REGS];

	/* use LDO6 क्रम vibrator control */
	पूर्णांक lकरो6_vibrator;

	/* Enable tracking mode of LDO8 */
	bool enable_lकरो8_tracking;
पूर्ण;

काष्ठा palmas_usb_platक्रमm_data अणु
	/* Do we enable the wakeup comparator on probe */
	पूर्णांक wakeup;
पूर्ण;

काष्ठा palmas_resource_platक्रमm_data अणु
	पूर्णांक regen1_mode_sleep;
	पूर्णांक regen2_mode_sleep;
	पूर्णांक sysen1_mode_sleep;
	पूर्णांक sysen2_mode_sleep;

	/* bitfield to be loaded to NSLEEP_RES_ASSIGN */
	u8 nsleep_res;
	/* bitfield to be loaded to NSLEEP_SMPS_ASSIGN */
	u8 nsleep_smps;
	/* bitfield to be loaded to NSLEEP_LDO_ASSIGN1 */
	u8 nsleep_lकरो1;
	/* bitfield to be loaded to NSLEEP_LDO_ASSIGN2 */
	u8 nsleep_lकरो2;

	/* bitfield to be loaded to ENABLE1_RES_ASSIGN */
	u8 enable1_res;
	/* bitfield to be loaded to ENABLE1_SMPS_ASSIGN */
	u8 enable1_smps;
	/* bitfield to be loaded to ENABLE1_LDO_ASSIGN1 */
	u8 enable1_lकरो1;
	/* bitfield to be loaded to ENABLE1_LDO_ASSIGN2 */
	u8 enable1_lकरो2;

	/* bitfield to be loaded to ENABLE2_RES_ASSIGN */
	u8 enable2_res;
	/* bitfield to be loaded to ENABLE2_SMPS_ASSIGN */
	u8 enable2_smps;
	/* bitfield to be loaded to ENABLE2_LDO_ASSIGN1 */
	u8 enable2_lकरो1;
	/* bitfield to be loaded to ENABLE2_LDO_ASSIGN2 */
	u8 enable2_lकरो2;
पूर्ण;

काष्ठा palmas_clk_platक्रमm_data अणु
	पूर्णांक clk32kg_mode_sleep;
	पूर्णांक clk32kgaudio_mode_sleep;
पूर्ण;

काष्ठा palmas_platक्रमm_data अणु
	पूर्णांक irq_flags;
	पूर्णांक gpio_base;

	/* bit value to be loaded to the POWER_CTRL रेजिस्टर */
	u8 घातer_ctrl;

	/*
	 * boolean to select अगर we want to configure muxing here
	 * then the two value to load पूर्णांकo the रेजिस्टरs अगर true
	 */
	पूर्णांक mux_from_pdata;
	u8 pad1, pad2;
	bool pm_off;

	काष्ठा palmas_pmic_platक्रमm_data *pmic_pdata;
	काष्ठा palmas_gpadc_platक्रमm_data *gpadc_pdata;
	काष्ठा palmas_usb_platक्रमm_data *usb_pdata;
	काष्ठा palmas_resource_platक्रमm_data *resource_pdata;
	काष्ठा palmas_clk_platक्रमm_data *clk_pdata;
पूर्ण;

काष्ठा palmas_gpadc_calibration अणु
	s32 gain;
	s32 gain_error;
	s32 offset_error;
पूर्ण;

#घोषणा PALMAS_DATASHEET_NAME(_name)	"palmas-gpadc-chan-"#_name

काष्ठा palmas_gpadc_result अणु
	s32 raw_code;
	s32 corrected_code;
	s32 result;
पूर्ण;

#घोषणा PALMAS_MAX_CHANNELS 16

/* Define the tps65917 IRQ numbers */
क्रमागत tps65917_irqs अणु
	/* INT1 रेजिस्टरs */
	TPS65917_RESERVED1,
	TPS65917_PWRON_IRQ,
	TPS65917_LONG_PRESS_KEY_IRQ,
	TPS65917_RESERVED2,
	TPS65917_PWRDOWN_IRQ,
	TPS65917_HOTDIE_IRQ,
	TPS65917_VSYS_MON_IRQ,
	TPS65917_RESERVED3,
	/* INT2 रेजिस्टरs */
	TPS65917_RESERVED4,
	TPS65917_OTP_ERROR_IRQ,
	TPS65917_WDT_IRQ,
	TPS65917_RESERVED5,
	TPS65917_RESET_IN_IRQ,
	TPS65917_FSD_IRQ,
	TPS65917_SHORT_IRQ,
	TPS65917_RESERVED6,
	/* INT3 रेजिस्टरs */
	TPS65917_GPADC_AUTO_0_IRQ,
	TPS65917_GPADC_AUTO_1_IRQ,
	TPS65917_GPADC_EOC_SW_IRQ,
	TPS65917_RESREVED6,
	TPS65917_RESERVED7,
	TPS65917_RESERVED8,
	TPS65917_RESERVED9,
	TPS65917_VBUS_IRQ,
	/* INT4 रेजिस्टरs */
	TPS65917_GPIO_0_IRQ,
	TPS65917_GPIO_1_IRQ,
	TPS65917_GPIO_2_IRQ,
	TPS65917_GPIO_3_IRQ,
	TPS65917_GPIO_4_IRQ,
	TPS65917_GPIO_5_IRQ,
	TPS65917_GPIO_6_IRQ,
	TPS65917_RESERVED10,
	/* Total Number IRQs */
	TPS65917_NUM_IRQ,
पूर्ण;

/* Define the palmas IRQ numbers */
क्रमागत palmas_irqs अणु
	/* INT1 रेजिस्टरs */
	PALMAS_CHARG_DET_N_VBUS_OVV_IRQ,
	PALMAS_PWRON_IRQ,
	PALMAS_LONG_PRESS_KEY_IRQ,
	PALMAS_RPWRON_IRQ,
	PALMAS_PWRDOWN_IRQ,
	PALMAS_HOTDIE_IRQ,
	PALMAS_VSYS_MON_IRQ,
	PALMAS_VBAT_MON_IRQ,
	/* INT2 रेजिस्टरs */
	PALMAS_RTC_ALARM_IRQ,
	PALMAS_RTC_TIMER_IRQ,
	PALMAS_WDT_IRQ,
	PALMAS_BATREMOVAL_IRQ,
	PALMAS_RESET_IN_IRQ,
	PALMAS_FBI_BB_IRQ,
	PALMAS_SHORT_IRQ,
	PALMAS_VAC_ACOK_IRQ,
	/* INT3 रेजिस्टरs */
	PALMAS_GPADC_AUTO_0_IRQ,
	PALMAS_GPADC_AUTO_1_IRQ,
	PALMAS_GPADC_EOC_SW_IRQ,
	PALMAS_GPADC_EOC_RT_IRQ,
	PALMAS_ID_OTG_IRQ,
	PALMAS_ID_IRQ,
	PALMAS_VBUS_OTG_IRQ,
	PALMAS_VBUS_IRQ,
	/* INT4 रेजिस्टरs */
	PALMAS_GPIO_0_IRQ,
	PALMAS_GPIO_1_IRQ,
	PALMAS_GPIO_2_IRQ,
	PALMAS_GPIO_3_IRQ,
	PALMAS_GPIO_4_IRQ,
	PALMAS_GPIO_5_IRQ,
	PALMAS_GPIO_6_IRQ,
	PALMAS_GPIO_7_IRQ,
	/* Total Number IRQs */
	PALMAS_NUM_IRQ,
पूर्ण;

/* Palmas GPADC Channels */
क्रमागत अणु
	PALMAS_ADC_CH_IN0,
	PALMAS_ADC_CH_IN1,
	PALMAS_ADC_CH_IN2,
	PALMAS_ADC_CH_IN3,
	PALMAS_ADC_CH_IN4,
	PALMAS_ADC_CH_IN5,
	PALMAS_ADC_CH_IN6,
	PALMAS_ADC_CH_IN7,
	PALMAS_ADC_CH_IN8,
	PALMAS_ADC_CH_IN9,
	PALMAS_ADC_CH_IN10,
	PALMAS_ADC_CH_IN11,
	PALMAS_ADC_CH_IN12,
	PALMAS_ADC_CH_IN13,
	PALMAS_ADC_CH_IN14,
	PALMAS_ADC_CH_IN15,
	PALMAS_ADC_CH_MAX,
पूर्ण;

/* Palmas GPADC Channel0 Current Source */
क्रमागत अणु
	PALMAS_ADC_CH0_CURRENT_SRC_0,
	PALMAS_ADC_CH0_CURRENT_SRC_5,
	PALMAS_ADC_CH0_CURRENT_SRC_15,
	PALMAS_ADC_CH0_CURRENT_SRC_20,
पूर्ण;

/* Palmas GPADC Channel3 Current Source */
क्रमागत अणु
	PALMAS_ADC_CH3_CURRENT_SRC_0,
	PALMAS_ADC_CH3_CURRENT_SRC_10,
	PALMAS_ADC_CH3_CURRENT_SRC_400,
	PALMAS_ADC_CH3_CURRENT_SRC_800,
पूर्ण;

काष्ठा palmas_pmic अणु
	काष्ठा palmas *palmas;
	काष्ठा device *dev;
	काष्ठा regulator_desc desc[PALMAS_NUM_REGS];
	काष्ठा mutex mutex;

	पूर्णांक smps123;
	पूर्णांक smps457;
	पूर्णांक smps12;

	पूर्णांक range[PALMAS_REG_SMPS10_OUT1];
	अचिन्हित पूर्णांक ramp_delay[PALMAS_REG_SMPS10_OUT1];
	अचिन्हित पूर्णांक current_reg_mode[PALMAS_REG_SMPS10_OUT1];
पूर्ण;

काष्ठा palmas_resource अणु
	काष्ठा palmas *palmas;
	काष्ठा device *dev;
पूर्ण;

काष्ठा palmas_usb अणु
	काष्ठा palmas *palmas;
	काष्ठा device *dev;

	काष्ठा extcon_dev *edev;

	पूर्णांक id_otg_irq;
	पूर्णांक id_irq;
	पूर्णांक vbus_otg_irq;
	पूर्णांक vbus_irq;

	पूर्णांक gpio_id_irq;
	पूर्णांक gpio_vbus_irq;
	काष्ठा gpio_desc *id_gpiod;
	काष्ठा gpio_desc *vbus_gpiod;
	अचिन्हित दीर्घ sw_debounce_jअगरfies;
	काष्ठा delayed_work wq_detectid;

	क्रमागत palmas_usb_state linkstat;
	पूर्णांक wakeup;
	bool enable_vbus_detection;
	bool enable_id_detection;
	bool enable_gpio_id_detection;
	bool enable_gpio_vbus_detection;
पूर्ण;

#घोषणा comparator_to_palmas(x) container_of((x), काष्ठा palmas_usb, comparator)

क्रमागत usb_irq_events अणु
	/* Wakeup events from INT3 */
	PALMAS_USB_ID_WAKEPUP,
	PALMAS_USB_VBUS_WAKEUP,

	/* ID_OTG_EVENTS */
	PALMAS_USB_ID_GND,
	N_PALMAS_USB_ID_GND,
	PALMAS_USB_ID_C,
	N_PALMAS_USB_ID_C,
	PALMAS_USB_ID_B,
	N_PALMAS_USB_ID_B,
	PALMAS_USB_ID_A,
	N_PALMAS_USB_ID_A,
	PALMAS_USB_ID_FLOAT,
	N_PALMAS_USB_ID_FLOAT,

	/* VBUS_OTG_EVENTS */
	PALMAS_USB_VB_SESS_END,
	N_PALMAS_USB_VB_SESS_END,
	PALMAS_USB_VB_SESS_VLD,
	N_PALMAS_USB_VB_SESS_VLD,
	PALMAS_USB_VA_SESS_VLD,
	N_PALMAS_USB_VA_SESS_VLD,
	PALMAS_USB_VA_VBUS_VLD,
	N_PALMAS_USB_VA_VBUS_VLD,
	PALMAS_USB_VADP_SNS,
	N_PALMAS_USB_VADP_SNS,
	PALMAS_USB_VADP_PRB,
	N_PALMAS_USB_VADP_PRB,
	PALMAS_USB_VOTG_SESS_VLD,
	N_PALMAS_USB_VOTG_SESS_VLD,
पूर्ण;

/* defines so we can store the mux settings */
#घोषणा PALMAS_GPIO_0_MUXED					(1 << 0)
#घोषणा PALMAS_GPIO_1_MUXED					(1 << 1)
#घोषणा PALMAS_GPIO_2_MUXED					(1 << 2)
#घोषणा PALMAS_GPIO_3_MUXED					(1 << 3)
#घोषणा PALMAS_GPIO_4_MUXED					(1 << 4)
#घोषणा PALMAS_GPIO_5_MUXED					(1 << 5)
#घोषणा PALMAS_GPIO_6_MUXED					(1 << 6)
#घोषणा PALMAS_GPIO_7_MUXED					(1 << 7)

#घोषणा PALMAS_LED1_MUXED					(1 << 0)
#घोषणा PALMAS_LED2_MUXED					(1 << 1)

#घोषणा PALMAS_PWM1_MUXED					(1 << 0)
#घोषणा PALMAS_PWM2_MUXED					(1 << 1)

/* helper macro to get correct slave number */
#घोषणा PALMAS_BASE_TO_SLAVE(x)		((x >> 8) - 1)
#घोषणा PALMAS_BASE_TO_REG(x, y)	((x & 0xFF) + y)

/* Base addresses of IP blocks in Palmas */
#घोषणा PALMAS_SMPS_DVS_BASE					0x020
#घोषणा PALMAS_RTC_BASE						0x100
#घोषणा PALMAS_VALIDITY_BASE					0x118
#घोषणा PALMAS_SMPS_BASE					0x120
#घोषणा PALMAS_LDO_BASE						0x150
#घोषणा PALMAS_DVFS_BASE					0x180
#घोषणा PALMAS_PMU_CONTROL_BASE					0x1A0
#घोषणा PALMAS_RESOURCE_BASE					0x1D4
#घोषणा PALMAS_PU_PD_OD_BASE					0x1F0
#घोषणा PALMAS_LED_BASE						0x200
#घोषणा PALMAS_INTERRUPT_BASE					0x210
#घोषणा PALMAS_USB_OTG_BASE					0x250
#घोषणा PALMAS_VIBRATOR_BASE					0x270
#घोषणा PALMAS_GPIO_BASE					0x280
#घोषणा PALMAS_USB_BASE						0x290
#घोषणा PALMAS_GPADC_BASE					0x2C0
#घोषणा PALMAS_TRIM_GPADC_BASE					0x3CD

/* Registers क्रम function RTC */
#घोषणा PALMAS_SECONDS_REG					0x00
#घोषणा PALMAS_MINUTES_REG					0x01
#घोषणा PALMAS_HOURS_REG					0x02
#घोषणा PALMAS_DAYS_REG						0x03
#घोषणा PALMAS_MONTHS_REG					0x04
#घोषणा PALMAS_YEARS_REG					0x05
#घोषणा PALMAS_WEEKS_REG					0x06
#घोषणा PALMAS_ALARM_SECONDS_REG				0x08
#घोषणा PALMAS_ALARM_MINUTES_REG				0x09
#घोषणा PALMAS_ALARM_HOURS_REG					0x0A
#घोषणा PALMAS_ALARM_DAYS_REG					0x0B
#घोषणा PALMAS_ALARM_MONTHS_REG					0x0C
#घोषणा PALMAS_ALARM_YEARS_REG					0x0D
#घोषणा PALMAS_RTC_CTRL_REG					0x10
#घोषणा PALMAS_RTC_STATUS_REG					0x11
#घोषणा PALMAS_RTC_INTERRUPTS_REG				0x12
#घोषणा PALMAS_RTC_COMP_LSB_REG					0x13
#घोषणा PALMAS_RTC_COMP_MSB_REG					0x14
#घोषणा PALMAS_RTC_RES_PROG_REG					0x15
#घोषणा PALMAS_RTC_RESET_STATUS_REG				0x16

/* Bit definitions क्रम SECONDS_REG */
#घोषणा PALMAS_SECONDS_REG_SEC1_MASK				0x70
#घोषणा PALMAS_SECONDS_REG_SEC1_SHIFT				0x04
#घोषणा PALMAS_SECONDS_REG_SEC0_MASK				0x0F
#घोषणा PALMAS_SECONDS_REG_SEC0_SHIFT				0x00

/* Bit definitions क्रम MINUTES_REG */
#घोषणा PALMAS_MINUTES_REG_MIN1_MASK				0x70
#घोषणा PALMAS_MINUTES_REG_MIN1_SHIFT				0x04
#घोषणा PALMAS_MINUTES_REG_MIN0_MASK				0x0F
#घोषणा PALMAS_MINUTES_REG_MIN0_SHIFT				0x00

/* Bit definitions क्रम HOURS_REG */
#घोषणा PALMAS_HOURS_REG_PM_NAM					0x80
#घोषणा PALMAS_HOURS_REG_PM_NAM_SHIFT				0x07
#घोषणा PALMAS_HOURS_REG_HOUR1_MASK				0x30
#घोषणा PALMAS_HOURS_REG_HOUR1_SHIFT				0x04
#घोषणा PALMAS_HOURS_REG_HOUR0_MASK				0x0F
#घोषणा PALMAS_HOURS_REG_HOUR0_SHIFT				0x00

/* Bit definitions क्रम DAYS_REG */
#घोषणा PALMAS_DAYS_REG_DAY1_MASK				0x30
#घोषणा PALMAS_DAYS_REG_DAY1_SHIFT				0x04
#घोषणा PALMAS_DAYS_REG_DAY0_MASK				0x0F
#घोषणा PALMAS_DAYS_REG_DAY0_SHIFT				0x00

/* Bit definitions क्रम MONTHS_REG */
#घोषणा PALMAS_MONTHS_REG_MONTH1				0x10
#घोषणा PALMAS_MONTHS_REG_MONTH1_SHIFT				0x04
#घोषणा PALMAS_MONTHS_REG_MONTH0_MASK				0x0F
#घोषणा PALMAS_MONTHS_REG_MONTH0_SHIFT				0x00

/* Bit definitions क्रम YEARS_REG */
#घोषणा PALMAS_YEARS_REG_YEAR1_MASK				0xf0
#घोषणा PALMAS_YEARS_REG_YEAR1_SHIFT				0x04
#घोषणा PALMAS_YEARS_REG_YEAR0_MASK				0x0F
#घोषणा PALMAS_YEARS_REG_YEAR0_SHIFT				0x00

/* Bit definitions क्रम WEEKS_REG */
#घोषणा PALMAS_WEEKS_REG_WEEK_MASK				0x07
#घोषणा PALMAS_WEEKS_REG_WEEK_SHIFT				0x00

/* Bit definitions क्रम ALARM_SECONDS_REG */
#घोषणा PALMAS_ALARM_SECONDS_REG_ALARM_SEC1_MASK		0x70
#घोषणा PALMAS_ALARM_SECONDS_REG_ALARM_SEC1_SHIFT		0x04
#घोषणा PALMAS_ALARM_SECONDS_REG_ALARM_SEC0_MASK		0x0F
#घोषणा PALMAS_ALARM_SECONDS_REG_ALARM_SEC0_SHIFT		0x00

/* Bit definitions क्रम ALARM_MINUTES_REG */
#घोषणा PALMAS_ALARM_MINUTES_REG_ALARM_MIN1_MASK		0x70
#घोषणा PALMAS_ALARM_MINUTES_REG_ALARM_MIN1_SHIFT		0x04
#घोषणा PALMAS_ALARM_MINUTES_REG_ALARM_MIN0_MASK		0x0F
#घोषणा PALMAS_ALARM_MINUTES_REG_ALARM_MIN0_SHIFT		0x00

/* Bit definitions क्रम ALARM_HOURS_REG */
#घोषणा PALMAS_ALARM_HOURS_REG_ALARM_PM_NAM			0x80
#घोषणा PALMAS_ALARM_HOURS_REG_ALARM_PM_NAM_SHIFT		0x07
#घोषणा PALMAS_ALARM_HOURS_REG_ALARM_HOUR1_MASK			0x30
#घोषणा PALMAS_ALARM_HOURS_REG_ALARM_HOUR1_SHIFT		0x04
#घोषणा PALMAS_ALARM_HOURS_REG_ALARM_HOUR0_MASK			0x0F
#घोषणा PALMAS_ALARM_HOURS_REG_ALARM_HOUR0_SHIFT		0x00

/* Bit definitions क्रम ALARM_DAYS_REG */
#घोषणा PALMAS_ALARM_DAYS_REG_ALARM_DAY1_MASK			0x30
#घोषणा PALMAS_ALARM_DAYS_REG_ALARM_DAY1_SHIFT			0x04
#घोषणा PALMAS_ALARM_DAYS_REG_ALARM_DAY0_MASK			0x0F
#घोषणा PALMAS_ALARM_DAYS_REG_ALARM_DAY0_SHIFT			0x00

/* Bit definitions क्रम ALARM_MONTHS_REG */
#घोषणा PALMAS_ALARM_MONTHS_REG_ALARM_MONTH1			0x10
#घोषणा PALMAS_ALARM_MONTHS_REG_ALARM_MONTH1_SHIFT		0x04
#घोषणा PALMAS_ALARM_MONTHS_REG_ALARM_MONTH0_MASK		0x0F
#घोषणा PALMAS_ALARM_MONTHS_REG_ALARM_MONTH0_SHIFT		0x00

/* Bit definitions क्रम ALARM_YEARS_REG */
#घोषणा PALMAS_ALARM_YEARS_REG_ALARM_YEAR1_MASK			0xf0
#घोषणा PALMAS_ALARM_YEARS_REG_ALARM_YEAR1_SHIFT		0x04
#घोषणा PALMAS_ALARM_YEARS_REG_ALARM_YEAR0_MASK			0x0F
#घोषणा PALMAS_ALARM_YEARS_REG_ALARM_YEAR0_SHIFT		0x00

/* Bit definitions क्रम RTC_CTRL_REG */
#घोषणा PALMAS_RTC_CTRL_REG_RTC_V_OPT				0x80
#घोषणा PALMAS_RTC_CTRL_REG_RTC_V_OPT_SHIFT			0x07
#घोषणा PALMAS_RTC_CTRL_REG_GET_TIME				0x40
#घोषणा PALMAS_RTC_CTRL_REG_GET_TIME_SHIFT			0x06
#घोषणा PALMAS_RTC_CTRL_REG_SET_32_COUNTER			0x20
#घोषणा PALMAS_RTC_CTRL_REG_SET_32_COUNTER_SHIFT		0x05
#घोषणा PALMAS_RTC_CTRL_REG_TEST_MODE				0x10
#घोषणा PALMAS_RTC_CTRL_REG_TEST_MODE_SHIFT			0x04
#घोषणा PALMAS_RTC_CTRL_REG_MODE_12_24				0x08
#घोषणा PALMAS_RTC_CTRL_REG_MODE_12_24_SHIFT			0x03
#घोषणा PALMAS_RTC_CTRL_REG_AUTO_COMP				0x04
#घोषणा PALMAS_RTC_CTRL_REG_AUTO_COMP_SHIFT			0x02
#घोषणा PALMAS_RTC_CTRL_REG_ROUND_30S				0x02
#घोषणा PALMAS_RTC_CTRL_REG_ROUND_30S_SHIFT			0x01
#घोषणा PALMAS_RTC_CTRL_REG_STOP_RTC				0x01
#घोषणा PALMAS_RTC_CTRL_REG_STOP_RTC_SHIFT			0x00

/* Bit definitions क्रम RTC_STATUS_REG */
#घोषणा PALMAS_RTC_STATUS_REG_POWER_UP				0x80
#घोषणा PALMAS_RTC_STATUS_REG_POWER_UP_SHIFT			0x07
#घोषणा PALMAS_RTC_STATUS_REG_ALARM				0x40
#घोषणा PALMAS_RTC_STATUS_REG_ALARM_SHIFT			0x06
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1D				0x20
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1D_SHIFT			0x05
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1H				0x10
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1H_SHIFT			0x04
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1M				0x08
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1M_SHIFT			0x03
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1S				0x04
#घोषणा PALMAS_RTC_STATUS_REG_EVENT_1S_SHIFT			0x02
#घोषणा PALMAS_RTC_STATUS_REG_RUN				0x02
#घोषणा PALMAS_RTC_STATUS_REG_RUN_SHIFT				0x01

/* Bit definitions क्रम RTC_INTERRUPTS_REG */
#घोषणा PALMAS_RTC_INTERRUPTS_REG_IT_SLEEP_MASK_EN		0x10
#घोषणा PALMAS_RTC_INTERRUPTS_REG_IT_SLEEP_MASK_EN_SHIFT	0x04
#घोषणा PALMAS_RTC_INTERRUPTS_REG_IT_ALARM			0x08
#घोषणा PALMAS_RTC_INTERRUPTS_REG_IT_ALARM_SHIFT		0x03
#घोषणा PALMAS_RTC_INTERRUPTS_REG_IT_TIMER			0x04
#घोषणा PALMAS_RTC_INTERRUPTS_REG_IT_TIMER_SHIFT		0x02
#घोषणा PALMAS_RTC_INTERRUPTS_REG_EVERY_MASK			0x03
#घोषणा PALMAS_RTC_INTERRUPTS_REG_EVERY_SHIFT			0x00

/* Bit definitions क्रम RTC_COMP_LSB_REG */
#घोषणा PALMAS_RTC_COMP_LSB_REG_RTC_COMP_LSB_MASK		0xFF
#घोषणा PALMAS_RTC_COMP_LSB_REG_RTC_COMP_LSB_SHIFT		0x00

/* Bit definitions क्रम RTC_COMP_MSB_REG */
#घोषणा PALMAS_RTC_COMP_MSB_REG_RTC_COMP_MSB_MASK		0xFF
#घोषणा PALMAS_RTC_COMP_MSB_REG_RTC_COMP_MSB_SHIFT		0x00

/* Bit definitions क्रम RTC_RES_PROG_REG */
#घोषणा PALMAS_RTC_RES_PROG_REG_SW_RES_PROG_MASK		0x3F
#घोषणा PALMAS_RTC_RES_PROG_REG_SW_RES_PROG_SHIFT		0x00

/* Bit definitions क्रम RTC_RESET_STATUS_REG */
#घोषणा PALMAS_RTC_RESET_STATUS_REG_RESET_STATUS		0x01
#घोषणा PALMAS_RTC_RESET_STATUS_REG_RESET_STATUS_SHIFT		0x00

/* Registers क्रम function BACKUP */
#घोषणा PALMAS_BACKUP0						0x00
#घोषणा PALMAS_BACKUP1						0x01
#घोषणा PALMAS_BACKUP2						0x02
#घोषणा PALMAS_BACKUP3						0x03
#घोषणा PALMAS_BACKUP4						0x04
#घोषणा PALMAS_BACKUP5						0x05
#घोषणा PALMAS_BACKUP6						0x06
#घोषणा PALMAS_BACKUP7						0x07

/* Bit definitions क्रम BACKUP0 */
#घोषणा PALMAS_BACKUP0_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP0_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP1 */
#घोषणा PALMAS_BACKUP1_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP1_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP2 */
#घोषणा PALMAS_BACKUP2_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP2_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP3 */
#घोषणा PALMAS_BACKUP3_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP3_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP4 */
#घोषणा PALMAS_BACKUP4_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP4_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP5 */
#घोषणा PALMAS_BACKUP5_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP5_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP6 */
#घोषणा PALMAS_BACKUP6_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP6_BACKUP_SHIFT				0x00

/* Bit definitions क्रम BACKUP7 */
#घोषणा PALMAS_BACKUP7_BACKUP_MASK				0xFF
#घोषणा PALMAS_BACKUP7_BACKUP_SHIFT				0x00

/* Registers क्रम function SMPS */
#घोषणा PALMAS_SMPS12_CTRL					0x00
#घोषणा PALMAS_SMPS12_TSTEP					0x01
#घोषणा PALMAS_SMPS12_FORCE					0x02
#घोषणा PALMAS_SMPS12_VOLTAGE					0x03
#घोषणा PALMAS_SMPS3_CTRL					0x04
#घोषणा PALMAS_SMPS3_VOLTAGE					0x07
#घोषणा PALMAS_SMPS45_CTRL					0x08
#घोषणा PALMAS_SMPS45_TSTEP					0x09
#घोषणा PALMAS_SMPS45_FORCE					0x0A
#घोषणा PALMAS_SMPS45_VOLTAGE					0x0B
#घोषणा PALMAS_SMPS6_CTRL					0x0C
#घोषणा PALMAS_SMPS6_TSTEP					0x0D
#घोषणा PALMAS_SMPS6_FORCE					0x0E
#घोषणा PALMAS_SMPS6_VOLTAGE					0x0F
#घोषणा PALMAS_SMPS7_CTRL					0x10
#घोषणा PALMAS_SMPS7_VOLTAGE					0x13
#घोषणा PALMAS_SMPS8_CTRL					0x14
#घोषणा PALMAS_SMPS8_TSTEP					0x15
#घोषणा PALMAS_SMPS8_FORCE					0x16
#घोषणा PALMAS_SMPS8_VOLTAGE					0x17
#घोषणा PALMAS_SMPS9_CTRL					0x18
#घोषणा PALMAS_SMPS9_VOLTAGE					0x1B
#घोषणा PALMAS_SMPS10_CTRL					0x1C
#घोषणा PALMAS_SMPS10_STATUS					0x1F
#घोषणा PALMAS_SMPS_CTRL					0x24
#घोषणा PALMAS_SMPS_PD_CTRL					0x25
#घोषणा PALMAS_SMPS_DITHER_EN					0x26
#घोषणा PALMAS_SMPS_THERMAL_EN					0x27
#घोषणा PALMAS_SMPS_THERMAL_STATUS				0x28
#घोषणा PALMAS_SMPS_SHORT_STATUS				0x29
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN			0x2A
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1				0x2B
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2				0x2C

/* Bit definitions क्रम SMPS12_CTRL */
#घोषणा PALMAS_SMPS12_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS12_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS12_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा PALMAS_SMPS12_CTRL_ROOF_FLOOR_EN_SHIFT			0x06
#घोषणा PALMAS_SMPS12_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS12_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS12_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS12_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS12_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS12_TSTEP */
#घोषणा PALMAS_SMPS12_TSTEP_TSTEP_MASK				0x03
#घोषणा PALMAS_SMPS12_TSTEP_TSTEP_SHIFT				0x00

/* Bit definitions क्रम SMPS12_FORCE */
#घोषणा PALMAS_SMPS12_FORCE_CMD					0x80
#घोषणा PALMAS_SMPS12_FORCE_CMD_SHIFT				0x07
#घोषणा PALMAS_SMPS12_FORCE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS12_FORCE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS12_VOLTAGE */
#घोषणा PALMAS_SMPS12_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS12_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS12_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS12_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS3_CTRL */
#घोषणा PALMAS_SMPS3_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS3_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS3_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS3_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS3_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS3_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS3_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS3_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS3_VOLTAGE */
#घोषणा PALMAS_SMPS3_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS3_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS3_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS3_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS45_CTRL */
#घोषणा PALMAS_SMPS45_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS45_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS45_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा PALMAS_SMPS45_CTRL_ROOF_FLOOR_EN_SHIFT			0x06
#घोषणा PALMAS_SMPS45_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS45_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS45_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS45_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS45_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS45_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS45_TSTEP */
#घोषणा PALMAS_SMPS45_TSTEP_TSTEP_MASK				0x03
#घोषणा PALMAS_SMPS45_TSTEP_TSTEP_SHIFT				0x00

/* Bit definitions क्रम SMPS45_FORCE */
#घोषणा PALMAS_SMPS45_FORCE_CMD					0x80
#घोषणा PALMAS_SMPS45_FORCE_CMD_SHIFT				0x07
#घोषणा PALMAS_SMPS45_FORCE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS45_FORCE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS45_VOLTAGE */
#घोषणा PALMAS_SMPS45_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS45_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS45_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS45_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS6_CTRL */
#घोषणा PALMAS_SMPS6_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS6_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS6_CTRL_ROOF_FLOOR_EN				0x40
#घोषणा PALMAS_SMPS6_CTRL_ROOF_FLOOR_EN_SHIFT			0x06
#घोषणा PALMAS_SMPS6_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS6_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS6_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS6_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS6_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS6_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS6_TSTEP */
#घोषणा PALMAS_SMPS6_TSTEP_TSTEP_MASK				0x03
#घोषणा PALMAS_SMPS6_TSTEP_TSTEP_SHIFT				0x00

/* Bit definitions क्रम SMPS6_FORCE */
#घोषणा PALMAS_SMPS6_FORCE_CMD					0x80
#घोषणा PALMAS_SMPS6_FORCE_CMD_SHIFT				0x07
#घोषणा PALMAS_SMPS6_FORCE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS6_FORCE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS6_VOLTAGE */
#घोषणा PALMAS_SMPS6_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS6_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS6_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS6_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS7_CTRL */
#घोषणा PALMAS_SMPS7_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS7_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS7_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS7_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS7_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS7_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS7_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS7_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS7_VOLTAGE */
#घोषणा PALMAS_SMPS7_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS7_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS7_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS7_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS8_CTRL */
#घोषणा PALMAS_SMPS8_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS8_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS8_CTRL_ROOF_FLOOR_EN				0x40
#घोषणा PALMAS_SMPS8_CTRL_ROOF_FLOOR_EN_SHIFT			0x06
#घोषणा PALMAS_SMPS8_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS8_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS8_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS8_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS8_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS8_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS8_TSTEP */
#घोषणा PALMAS_SMPS8_TSTEP_TSTEP_MASK				0x03
#घोषणा PALMAS_SMPS8_TSTEP_TSTEP_SHIFT				0x00

/* Bit definitions क्रम SMPS8_FORCE */
#घोषणा PALMAS_SMPS8_FORCE_CMD					0x80
#घोषणा PALMAS_SMPS8_FORCE_CMD_SHIFT				0x07
#घोषणा PALMAS_SMPS8_FORCE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS8_FORCE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS8_VOLTAGE */
#घोषणा PALMAS_SMPS8_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS8_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS8_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS8_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS9_CTRL */
#घोषणा PALMAS_SMPS9_CTRL_WR_S					0x80
#घोषणा PALMAS_SMPS9_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_SMPS9_CTRL_STATUS_MASK				0x30
#घोषणा PALMAS_SMPS9_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SMPS9_CTRL_MODE_SLEEP_MASK			0x0c
#घोषणा PALMAS_SMPS9_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SMPS9_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा PALMAS_SMPS9_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS9_VOLTAGE */
#घोषणा PALMAS_SMPS9_VOLTAGE_RANGE				0x80
#घोषणा PALMAS_SMPS9_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा PALMAS_SMPS9_VOLTAGE_VSEL_MASK				0x7F
#घोषणा PALMAS_SMPS9_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम SMPS10_CTRL */
#घोषणा PALMAS_SMPS10_CTRL_MODE_SLEEP_MASK			0xf0
#घोषणा PALMAS_SMPS10_CTRL_MODE_SLEEP_SHIFT			0x04
#घोषणा PALMAS_SMPS10_CTRL_MODE_ACTIVE_MASK			0x0F
#घोषणा PALMAS_SMPS10_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS10_STATUS */
#घोषणा PALMAS_SMPS10_STATUS_STATUS_MASK			0x0F
#घोषणा PALMAS_SMPS10_STATUS_STATUS_SHIFT			0x00

/* Bit definitions क्रम SMPS_CTRL */
#घोषणा PALMAS_SMPS_CTRL_SMPS45_SMPS457_EN			0x20
#घोषणा PALMAS_SMPS_CTRL_SMPS45_SMPS457_EN_SHIFT		0x05
#घोषणा PALMAS_SMPS_CTRL_SMPS12_SMPS123_EN			0x10
#घोषणा PALMAS_SMPS_CTRL_SMPS12_SMPS123_EN_SHIFT		0x04
#घोषणा PALMAS_SMPS_CTRL_SMPS45_PHASE_CTRL_MASK			0x0c
#घोषणा PALMAS_SMPS_CTRL_SMPS45_PHASE_CTRL_SHIFT		0x02
#घोषणा PALMAS_SMPS_CTRL_SMPS123_PHASE_CTRL_MASK		0x03
#घोषणा PALMAS_SMPS_CTRL_SMPS123_PHASE_CTRL_SHIFT		0x00

/* Bit definitions क्रम SMPS_PD_CTRL */
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS9				0x40
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS9_SHIFT				0x06
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS8				0x20
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS8_SHIFT				0x05
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS7				0x10
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS7_SHIFT				0x04
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS6				0x08
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS6_SHIFT				0x03
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS45				0x04
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS45_SHIFT			0x02
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS3				0x02
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS3_SHIFT				0x01
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS12				0x01
#घोषणा PALMAS_SMPS_PD_CTRL_SMPS12_SHIFT			0x00

/* Bit definitions क्रम SMPS_THERMAL_EN */
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS9				0x40
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS9_SHIFT			0x06
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS8				0x20
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS8_SHIFT			0x05
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS6				0x08
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS6_SHIFT			0x03
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS457				0x04
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS457_SHIFT			0x02
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS123				0x01
#घोषणा PALMAS_SMPS_THERMAL_EN_SMPS123_SHIFT			0x00

/* Bit definitions क्रम SMPS_THERMAL_STATUS */
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS9			0x40
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS9_SHIFT			0x06
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS8			0x20
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS8_SHIFT			0x05
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS6			0x08
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS6_SHIFT			0x03
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS457			0x04
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS457_SHIFT		0x02
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS123			0x01
#घोषणा PALMAS_SMPS_THERMAL_STATUS_SMPS123_SHIFT		0x00

/* Bit definitions क्रम SMPS_SHORT_STATUS */
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS10				0x80
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS10_SHIFT			0x07
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS9				0x40
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS9_SHIFT			0x06
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS8				0x20
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS8_SHIFT			0x05
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS7				0x10
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS7_SHIFT			0x04
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS6				0x08
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS6_SHIFT			0x03
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS45				0x04
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS45_SHIFT			0x02
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS3				0x02
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS3_SHIFT			0x01
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS12				0x01
#घोषणा PALMAS_SMPS_SHORT_STATUS_SMPS12_SHIFT			0x00

/* Bit definitions क्रम SMPS_NEGATIVE_CURRENT_LIMIT_EN */
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS9		0x40
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS9_SHIFT	0x06
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS8		0x20
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS8_SHIFT	0x05
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS7		0x10
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS7_SHIFT	0x04
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS6		0x08
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS6_SHIFT	0x03
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS45		0x04
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS45_SHIFT	0x02
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS3		0x02
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS3_SHIFT	0x01
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS12		0x01
#घोषणा PALMAS_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS12_SHIFT	0x00

/* Bit definitions क्रम SMPS_POWERGOOD_MASK1 */
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS10			0x80
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS10_SHIFT		0x07
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS9			0x40
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS9_SHIFT			0x06
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS8			0x20
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS8_SHIFT			0x05
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS7			0x10
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS7_SHIFT			0x04
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS6			0x08
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS6_SHIFT			0x03
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS45			0x04
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS45_SHIFT		0x02
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS3			0x02
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS3_SHIFT			0x01
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS12			0x01
#घोषणा PALMAS_SMPS_POWERGOOD_MASK1_SMPS12_SHIFT		0x00

/* Bit definitions क्रम SMPS_POWERGOOD_MASK2 */
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_POWERGOOD_TYPE_SELECT	0x80
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_POWERGOOD_TYPE_SELECT_SHIFT	0x07
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_GPIO_7			0x04
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_GPIO_7_SHIFT		0x02
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_VBUS			0x02
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_VBUS_SHIFT			0x01
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_ACOK			0x01
#घोषणा PALMAS_SMPS_POWERGOOD_MASK2_ACOK_SHIFT			0x00

/* Registers क्रम function LDO */
#घोषणा PALMAS_LDO1_CTRL					0x00
#घोषणा PALMAS_LDO1_VOLTAGE					0x01
#घोषणा PALMAS_LDO2_CTRL					0x02
#घोषणा PALMAS_LDO2_VOLTAGE					0x03
#घोषणा PALMAS_LDO3_CTRL					0x04
#घोषणा PALMAS_LDO3_VOLTAGE					0x05
#घोषणा PALMAS_LDO4_CTRL					0x06
#घोषणा PALMAS_LDO4_VOLTAGE					0x07
#घोषणा PALMAS_LDO5_CTRL					0x08
#घोषणा PALMAS_LDO5_VOLTAGE					0x09
#घोषणा PALMAS_LDO6_CTRL					0x0A
#घोषणा PALMAS_LDO6_VOLTAGE					0x0B
#घोषणा PALMAS_LDO7_CTRL					0x0C
#घोषणा PALMAS_LDO7_VOLTAGE					0x0D
#घोषणा PALMAS_LDO8_CTRL					0x0E
#घोषणा PALMAS_LDO8_VOLTAGE					0x0F
#घोषणा PALMAS_LDO9_CTRL					0x10
#घोषणा PALMAS_LDO9_VOLTAGE					0x11
#घोषणा PALMAS_LDOLN_CTRL					0x12
#घोषणा PALMAS_LDOLN_VOLTAGE					0x13
#घोषणा PALMAS_LDOUSB_CTRL					0x14
#घोषणा PALMAS_LDOUSB_VOLTAGE					0x15
#घोषणा PALMAS_LDO_CTRL						0x1A
#घोषणा PALMAS_LDO_PD_CTRL1					0x1B
#घोषणा PALMAS_LDO_PD_CTRL2					0x1C
#घोषणा PALMAS_LDO_SHORT_STATUS1				0x1D
#घोषणा PALMAS_LDO_SHORT_STATUS2				0x1E

/* Bit definitions क्रम LDO1_CTRL */
#घोषणा PALMAS_LDO1_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO1_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO1_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO1_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO1_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO1_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO1_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO1_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO1_VOLTAGE */
#घोषणा PALMAS_LDO1_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO1_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO2_CTRL */
#घोषणा PALMAS_LDO2_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO2_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO2_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO2_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO2_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO2_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO2_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO2_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO2_VOLTAGE */
#घोषणा PALMAS_LDO2_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO2_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO3_CTRL */
#घोषणा PALMAS_LDO3_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO3_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO3_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO3_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO3_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO3_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO3_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO3_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO3_VOLTAGE */
#घोषणा PALMAS_LDO3_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO3_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO4_CTRL */
#घोषणा PALMAS_LDO4_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO4_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO4_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO4_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO4_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO4_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO4_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO4_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO4_VOLTAGE */
#घोषणा PALMAS_LDO4_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO4_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO5_CTRL */
#घोषणा PALMAS_LDO5_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO5_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO5_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO5_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO5_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO5_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO5_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO5_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO5_VOLTAGE */
#घोषणा PALMAS_LDO5_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO5_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO6_CTRL */
#घोषणा PALMAS_LDO6_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO6_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO6_CTRL_LDO_VIB_EN				0x40
#घोषणा PALMAS_LDO6_CTRL_LDO_VIB_EN_SHIFT			0x06
#घोषणा PALMAS_LDO6_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO6_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO6_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO6_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO6_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO6_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO6_VOLTAGE */
#घोषणा PALMAS_LDO6_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO6_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO7_CTRL */
#घोषणा PALMAS_LDO7_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO7_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO7_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO7_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO7_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO7_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO7_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO7_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO7_VOLTAGE */
#घोषणा PALMAS_LDO7_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO7_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO8_CTRL */
#घोषणा PALMAS_LDO8_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO8_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO8_CTRL_LDO_TRACKING_EN			0x40
#घोषणा PALMAS_LDO8_CTRL_LDO_TRACKING_EN_SHIFT			0x06
#घोषणा PALMAS_LDO8_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO8_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO8_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO8_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO8_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO8_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO8_VOLTAGE */
#घोषणा PALMAS_LDO8_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO8_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDO9_CTRL */
#घोषणा PALMAS_LDO9_CTRL_WR_S					0x80
#घोषणा PALMAS_LDO9_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDO9_CTRL_LDO_BYPASS_EN				0x40
#घोषणा PALMAS_LDO9_CTRL_LDO_BYPASS_EN_SHIFT			0x06
#घोषणा PALMAS_LDO9_CTRL_STATUS					0x10
#घोषणा PALMAS_LDO9_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDO9_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDO9_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDO9_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDO9_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO9_VOLTAGE */
#घोषणा PALMAS_LDO9_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDO9_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDOLN_CTRL */
#घोषणा PALMAS_LDOLN_CTRL_WR_S					0x80
#घोषणा PALMAS_LDOLN_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDOLN_CTRL_STATUS				0x10
#घोषणा PALMAS_LDOLN_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDOLN_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDOLN_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDOLN_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDOLN_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDOLN_VOLTAGE */
#घोषणा PALMAS_LDOLN_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDOLN_VOLTAGE_VSEL_SHIFT				0x00

/* Bit definitions क्रम LDOUSB_CTRL */
#घोषणा PALMAS_LDOUSB_CTRL_WR_S					0x80
#घोषणा PALMAS_LDOUSB_CTRL_WR_S_SHIFT				0x07
#घोषणा PALMAS_LDOUSB_CTRL_STATUS				0x10
#घोषणा PALMAS_LDOUSB_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_LDOUSB_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_LDOUSB_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_LDOUSB_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_LDOUSB_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDOUSB_VOLTAGE */
#घोषणा PALMAS_LDOUSB_VOLTAGE_VSEL_MASK				0x3F
#घोषणा PALMAS_LDOUSB_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम LDO_CTRL */
#घोषणा PALMAS_LDO_CTRL_LDOUSB_ON_VBUS_VSYS			0x01
#घोषणा PALMAS_LDO_CTRL_LDOUSB_ON_VBUS_VSYS_SHIFT		0x00

/* Bit definitions क्रम LDO_PD_CTRL1 */
#घोषणा PALMAS_LDO_PD_CTRL1_LDO8				0x80
#घोषणा PALMAS_LDO_PD_CTRL1_LDO8_SHIFT				0x07
#घोषणा PALMAS_LDO_PD_CTRL1_LDO7				0x40
#घोषणा PALMAS_LDO_PD_CTRL1_LDO7_SHIFT				0x06
#घोषणा PALMAS_LDO_PD_CTRL1_LDO6				0x20
#घोषणा PALMAS_LDO_PD_CTRL1_LDO6_SHIFT				0x05
#घोषणा PALMAS_LDO_PD_CTRL1_LDO5				0x10
#घोषणा PALMAS_LDO_PD_CTRL1_LDO5_SHIFT				0x04
#घोषणा PALMAS_LDO_PD_CTRL1_LDO4				0x08
#घोषणा PALMAS_LDO_PD_CTRL1_LDO4_SHIFT				0x03
#घोषणा PALMAS_LDO_PD_CTRL1_LDO3				0x04
#घोषणा PALMAS_LDO_PD_CTRL1_LDO3_SHIFT				0x02
#घोषणा PALMAS_LDO_PD_CTRL1_LDO2				0x02
#घोषणा PALMAS_LDO_PD_CTRL1_LDO2_SHIFT				0x01
#घोषणा PALMAS_LDO_PD_CTRL1_LDO1				0x01
#घोषणा PALMAS_LDO_PD_CTRL1_LDO1_SHIFT				0x00

/* Bit definitions क्रम LDO_PD_CTRL2 */
#घोषणा PALMAS_LDO_PD_CTRL2_LDOUSB				0x04
#घोषणा PALMAS_LDO_PD_CTRL2_LDOUSB_SHIFT			0x02
#घोषणा PALMAS_LDO_PD_CTRL2_LDOLN				0x02
#घोषणा PALMAS_LDO_PD_CTRL2_LDOLN_SHIFT				0x01
#घोषणा PALMAS_LDO_PD_CTRL2_LDO9				0x01
#घोषणा PALMAS_LDO_PD_CTRL2_LDO9_SHIFT				0x00

/* Bit definitions क्रम LDO_SHORT_STATUS1 */
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO8				0x80
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO8_SHIFT			0x07
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO7				0x40
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO7_SHIFT			0x06
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO6				0x20
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO6_SHIFT			0x05
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO5				0x10
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO5_SHIFT			0x04
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO4				0x08
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO4_SHIFT			0x03
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO3				0x04
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO3_SHIFT			0x02
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO2				0x02
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO2_SHIFT			0x01
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO1				0x01
#घोषणा PALMAS_LDO_SHORT_STATUS1_LDO1_SHIFT			0x00

/* Bit definitions क्रम LDO_SHORT_STATUS2 */
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDOVANA			0x08
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDOVANA_SHIFT			0x03
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDOUSB				0x04
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDOUSB_SHIFT			0x02
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDOLN				0x02
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDOLN_SHIFT			0x01
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDO9				0x01
#घोषणा PALMAS_LDO_SHORT_STATUS2_LDO9_SHIFT			0x00

/* Registers क्रम function PMU_CONTROL */
#घोषणा PALMAS_DEV_CTRL						0x00
#घोषणा PALMAS_POWER_CTRL					0x01
#घोषणा PALMAS_VSYS_LO						0x02
#घोषणा PALMAS_VSYS_MON						0x03
#घोषणा PALMAS_VBAT_MON						0x04
#घोषणा PALMAS_WATCHDOG						0x05
#घोषणा PALMAS_BOOT_STATUS					0x06
#घोषणा PALMAS_BATTERY_BOUNCE					0x07
#घोषणा PALMAS_BACKUP_BATTERY_CTRL				0x08
#घोषणा PALMAS_LONG_PRESS_KEY					0x09
#घोषणा PALMAS_OSC_THERM_CTRL					0x0A
#घोषणा PALMAS_BATDEBOUNCING					0x0B
#घोषणा PALMAS_SWOFF_HWRST					0x0F
#घोषणा PALMAS_SWOFF_COLDRST					0x10
#घोषणा PALMAS_SWOFF_STATUS					0x11
#घोषणा PALMAS_PMU_CONFIG					0x12
#घोषणा PALMAS_SPARE						0x14
#घोषणा PALMAS_PMU_SECONDARY_INT				0x15
#घोषणा PALMAS_SW_REVISION					0x17
#घोषणा PALMAS_EXT_CHRG_CTRL					0x18
#घोषणा PALMAS_PMU_SECONDARY_INT2				0x19

/* Bit definitions क्रम DEV_CTRL */
#घोषणा PALMAS_DEV_CTRL_DEV_STATUS_MASK				0x0c
#घोषणा PALMAS_DEV_CTRL_DEV_STATUS_SHIFT			0x02
#घोषणा PALMAS_DEV_CTRL_SW_RST					0x02
#घोषणा PALMAS_DEV_CTRL_SW_RST_SHIFT				0x01
#घोषणा PALMAS_DEV_CTRL_DEV_ON					0x01
#घोषणा PALMAS_DEV_CTRL_DEV_ON_SHIFT				0x00

/* Bit definitions क्रम POWER_CTRL */
#घोषणा PALMAS_POWER_CTRL_ENABLE2_MASK				0x04
#घोषणा PALMAS_POWER_CTRL_ENABLE2_MASK_SHIFT			0x02
#घोषणा PALMAS_POWER_CTRL_ENABLE1_MASK				0x02
#घोषणा PALMAS_POWER_CTRL_ENABLE1_MASK_SHIFT			0x01
#घोषणा PALMAS_POWER_CTRL_NSLEEP_MASK				0x01
#घोषणा PALMAS_POWER_CTRL_NSLEEP_MASK_SHIFT			0x00

/* Bit definitions क्रम VSYS_LO */
#घोषणा PALMAS_VSYS_LO_THRESHOLD_MASK				0x1F
#घोषणा PALMAS_VSYS_LO_THRESHOLD_SHIFT				0x00

/* Bit definitions क्रम VSYS_MON */
#घोषणा PALMAS_VSYS_MON_ENABLE					0x80
#घोषणा PALMAS_VSYS_MON_ENABLE_SHIFT				0x07
#घोषणा PALMAS_VSYS_MON_THRESHOLD_MASK				0x3F
#घोषणा PALMAS_VSYS_MON_THRESHOLD_SHIFT				0x00

/* Bit definitions क्रम VBAT_MON */
#घोषणा PALMAS_VBAT_MON_ENABLE					0x80
#घोषणा PALMAS_VBAT_MON_ENABLE_SHIFT				0x07
#घोषणा PALMAS_VBAT_MON_THRESHOLD_MASK				0x3F
#घोषणा PALMAS_VBAT_MON_THRESHOLD_SHIFT				0x00

/* Bit definitions क्रम WATCHDOG */
#घोषणा PALMAS_WATCHDOG_LOCK					0x20
#घोषणा PALMAS_WATCHDOG_LOCK_SHIFT				0x05
#घोषणा PALMAS_WATCHDOG_ENABLE					0x10
#घोषणा PALMAS_WATCHDOG_ENABLE_SHIFT				0x04
#घोषणा PALMAS_WATCHDOG_MODE					0x08
#घोषणा PALMAS_WATCHDOG_MODE_SHIFT				0x03
#घोषणा PALMAS_WATCHDOG_TIMER_MASK				0x07
#घोषणा PALMAS_WATCHDOG_TIMER_SHIFT				0x00

/* Bit definitions क्रम BOOT_STATUS */
#घोषणा PALMAS_BOOT_STATUS_BOOT1				0x02
#घोषणा PALMAS_BOOT_STATUS_BOOT1_SHIFT				0x01
#घोषणा PALMAS_BOOT_STATUS_BOOT0				0x01
#घोषणा PALMAS_BOOT_STATUS_BOOT0_SHIFT				0x00

/* Bit definitions क्रम BATTERY_BOUNCE */
#घोषणा PALMAS_BATTERY_BOUNCE_BB_DELAY_MASK			0x3F
#घोषणा PALMAS_BATTERY_BOUNCE_BB_DELAY_SHIFT			0x00

/* Bit definitions क्रम BACKUP_BATTERY_CTRL */
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_18_15			0x80
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_18_15_SHIFT		0x07
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_EN_SLP			0x40
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_EN_SLP_SHIFT		0x06
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_EN_OFF			0x20
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_EN_OFF_SHIFT		0x05
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_PWEN			0x10
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_VRTC_PWEN_SHIFT		0x04
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG		0x08
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG_SHIFT	0x03
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_BB_SEL_MASK			0x06
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_BB_SEL_SHIFT			0x01
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN			0x01
#घोषणा PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN_SHIFT		0x00

/* Bit definitions क्रम LONG_PRESS_KEY */
#घोषणा PALMAS_LONG_PRESS_KEY_LPK_LOCK				0x80
#घोषणा PALMAS_LONG_PRESS_KEY_LPK_LOCK_SHIFT			0x07
#घोषणा PALMAS_LONG_PRESS_KEY_LPK_INT_CLR			0x10
#घोषणा PALMAS_LONG_PRESS_KEY_LPK_INT_CLR_SHIFT			0x04
#घोषणा PALMAS_LONG_PRESS_KEY_LPK_TIME_MASK			0x0c
#घोषणा PALMAS_LONG_PRESS_KEY_LPK_TIME_SHIFT			0x02
#घोषणा PALMAS_LONG_PRESS_KEY_PWRON_DEBOUNCE_MASK		0x03
#घोषणा PALMAS_LONG_PRESS_KEY_PWRON_DEBOUNCE_SHIFT		0x00

/* Bit definitions क्रम OSC_THERM_CTRL */
#घोषणा PALMAS_OSC_THERM_CTRL_VANA_ON_IN_SLEEP			0x80
#घोषणा PALMAS_OSC_THERM_CTRL_VANA_ON_IN_SLEEP_SHIFT		0x07
#घोषणा PALMAS_OSC_THERM_CTRL_INT_MASK_IN_SLEEP			0x40
#घोषणा PALMAS_OSC_THERM_CTRL_INT_MASK_IN_SLEEP_SHIFT		0x06
#घोषणा PALMAS_OSC_THERM_CTRL_RC15MHZ_ON_IN_SLEEP		0x20
#घोषणा PALMAS_OSC_THERM_CTRL_RC15MHZ_ON_IN_SLEEP_SHIFT		0x05
#घोषणा PALMAS_OSC_THERM_CTRL_THERM_OFF_IN_SLEEP		0x10
#घोषणा PALMAS_OSC_THERM_CTRL_THERM_OFF_IN_SLEEP_SHIFT		0x04
#घोषणा PALMAS_OSC_THERM_CTRL_THERM_HD_SEL_MASK			0x0c
#घोषणा PALMAS_OSC_THERM_CTRL_THERM_HD_SEL_SHIFT		0x02
#घोषणा PALMAS_OSC_THERM_CTRL_OSC_BYPASS			0x02
#घोषणा PALMAS_OSC_THERM_CTRL_OSC_BYPASS_SHIFT			0x01
#घोषणा PALMAS_OSC_THERM_CTRL_OSC_HPMODE			0x01
#घोषणा PALMAS_OSC_THERM_CTRL_OSC_HPMODE_SHIFT			0x00

/* Bit definitions क्रम BATDEBOUNCING */
#घोषणा PALMAS_BATDEBOUNCING_BAT_DEB_BYPASS			0x80
#घोषणा PALMAS_BATDEBOUNCING_BAT_DEB_BYPASS_SHIFT		0x07
#घोषणा PALMAS_BATDEBOUNCING_BINS_DEB_MASK			0x78
#घोषणा PALMAS_BATDEBOUNCING_BINS_DEB_SHIFT			0x03
#घोषणा PALMAS_BATDEBOUNCING_BEXT_DEB_MASK			0x07
#घोषणा PALMAS_BATDEBOUNCING_BEXT_DEB_SHIFT			0x00

/* Bit definitions क्रम SWOFF_HWRST */
#घोषणा PALMAS_SWOFF_HWRST_PWRON_LPK				0x80
#घोषणा PALMAS_SWOFF_HWRST_PWRON_LPK_SHIFT			0x07
#घोषणा PALMAS_SWOFF_HWRST_PWRDOWN				0x40
#घोषणा PALMAS_SWOFF_HWRST_PWRDOWN_SHIFT			0x06
#घोषणा PALMAS_SWOFF_HWRST_WTD					0x20
#घोषणा PALMAS_SWOFF_HWRST_WTD_SHIFT				0x05
#घोषणा PALMAS_SWOFF_HWRST_TSHUT				0x10
#घोषणा PALMAS_SWOFF_HWRST_TSHUT_SHIFT				0x04
#घोषणा PALMAS_SWOFF_HWRST_RESET_IN				0x08
#घोषणा PALMAS_SWOFF_HWRST_RESET_IN_SHIFT			0x03
#घोषणा PALMAS_SWOFF_HWRST_SW_RST				0x04
#घोषणा PALMAS_SWOFF_HWRST_SW_RST_SHIFT				0x02
#घोषणा PALMAS_SWOFF_HWRST_VSYS_LO				0x02
#घोषणा PALMAS_SWOFF_HWRST_VSYS_LO_SHIFT			0x01
#घोषणा PALMAS_SWOFF_HWRST_GPADC_SHUTDOWN			0x01
#घोषणा PALMAS_SWOFF_HWRST_GPADC_SHUTDOWN_SHIFT			0x00

/* Bit definitions क्रम SWOFF_COLDRST */
#घोषणा PALMAS_SWOFF_COLDRST_PWRON_LPK				0x80
#घोषणा PALMAS_SWOFF_COLDRST_PWRON_LPK_SHIFT			0x07
#घोषणा PALMAS_SWOFF_COLDRST_PWRDOWN				0x40
#घोषणा PALMAS_SWOFF_COLDRST_PWRDOWN_SHIFT			0x06
#घोषणा PALMAS_SWOFF_COLDRST_WTD				0x20
#घोषणा PALMAS_SWOFF_COLDRST_WTD_SHIFT				0x05
#घोषणा PALMAS_SWOFF_COLDRST_TSHUT				0x10
#घोषणा PALMAS_SWOFF_COLDRST_TSHUT_SHIFT			0x04
#घोषणा PALMAS_SWOFF_COLDRST_RESET_IN				0x08
#घोषणा PALMAS_SWOFF_COLDRST_RESET_IN_SHIFT			0x03
#घोषणा PALMAS_SWOFF_COLDRST_SW_RST				0x04
#घोषणा PALMAS_SWOFF_COLDRST_SW_RST_SHIFT			0x02
#घोषणा PALMAS_SWOFF_COLDRST_VSYS_LO				0x02
#घोषणा PALMAS_SWOFF_COLDRST_VSYS_LO_SHIFT			0x01
#घोषणा PALMAS_SWOFF_COLDRST_GPADC_SHUTDOWN			0x01
#घोषणा PALMAS_SWOFF_COLDRST_GPADC_SHUTDOWN_SHIFT		0x00

/* Bit definitions क्रम SWOFF_STATUS */
#घोषणा PALMAS_SWOFF_STATUS_PWRON_LPK				0x80
#घोषणा PALMAS_SWOFF_STATUS_PWRON_LPK_SHIFT			0x07
#घोषणा PALMAS_SWOFF_STATUS_PWRDOWN				0x40
#घोषणा PALMAS_SWOFF_STATUS_PWRDOWN_SHIFT			0x06
#घोषणा PALMAS_SWOFF_STATUS_WTD					0x20
#घोषणा PALMAS_SWOFF_STATUS_WTD_SHIFT				0x05
#घोषणा PALMAS_SWOFF_STATUS_TSHUT				0x10
#घोषणा PALMAS_SWOFF_STATUS_TSHUT_SHIFT				0x04
#घोषणा PALMAS_SWOFF_STATUS_RESET_IN				0x08
#घोषणा PALMAS_SWOFF_STATUS_RESET_IN_SHIFT			0x03
#घोषणा PALMAS_SWOFF_STATUS_SW_RST				0x04
#घोषणा PALMAS_SWOFF_STATUS_SW_RST_SHIFT			0x02
#घोषणा PALMAS_SWOFF_STATUS_VSYS_LO				0x02
#घोषणा PALMAS_SWOFF_STATUS_VSYS_LO_SHIFT			0x01
#घोषणा PALMAS_SWOFF_STATUS_GPADC_SHUTDOWN			0x01
#घोषणा PALMAS_SWOFF_STATUS_GPADC_SHUTDOWN_SHIFT		0x00

/* Bit definitions क्रम PMU_CONFIG */
#घोषणा PALMAS_PMU_CONFIG_MULTI_CELL_EN				0x40
#घोषणा PALMAS_PMU_CONFIG_MULTI_CELL_EN_SHIFT			0x06
#घोषणा PALMAS_PMU_CONFIG_SPARE_MASK				0x30
#घोषणा PALMAS_PMU_CONFIG_SPARE_SHIFT				0x04
#घोषणा PALMAS_PMU_CONFIG_SWOFF_DLY_MASK			0x0c
#घोषणा PALMAS_PMU_CONFIG_SWOFF_DLY_SHIFT			0x02
#घोषणा PALMAS_PMU_CONFIG_GATE_RESET_OUT			0x02
#घोषणा PALMAS_PMU_CONFIG_GATE_RESET_OUT_SHIFT			0x01
#घोषणा PALMAS_PMU_CONFIG_AUTODEVON				0x01
#घोषणा PALMAS_PMU_CONFIG_AUTODEVON_SHIFT			0x00

/* Bit definitions क्रम SPARE */
#घोषणा PALMAS_SPARE_SPARE_MASK					0xf8
#घोषणा PALMAS_SPARE_SPARE_SHIFT				0x03
#घोषणा PALMAS_SPARE_REGEN3_OD					0x04
#घोषणा PALMAS_SPARE_REGEN3_OD_SHIFT				0x02
#घोषणा PALMAS_SPARE_REGEN2_OD					0x02
#घोषणा PALMAS_SPARE_REGEN2_OD_SHIFT				0x01
#घोषणा PALMAS_SPARE_REGEN1_OD					0x01
#घोषणा PALMAS_SPARE_REGEN1_OD_SHIFT				0x00

/* Bit definitions क्रम PMU_SECONDARY_INT */
#घोषणा PALMAS_PMU_SECONDARY_INT_VBUS_OVV_INT_SRC		0x80
#घोषणा PALMAS_PMU_SECONDARY_INT_VBUS_OVV_INT_SRC_SHIFT		0x07
#घोषणा PALMAS_PMU_SECONDARY_INT_CHARG_DET_N_INT_SRC		0x40
#घोषणा PALMAS_PMU_SECONDARY_INT_CHARG_DET_N_INT_SRC_SHIFT	0x06
#घोषणा PALMAS_PMU_SECONDARY_INT_BB_INT_SRC			0x20
#घोषणा PALMAS_PMU_SECONDARY_INT_BB_INT_SRC_SHIFT		0x05
#घोषणा PALMAS_PMU_SECONDARY_INT_FBI_INT_SRC			0x10
#घोषणा PALMAS_PMU_SECONDARY_INT_FBI_INT_SRC_SHIFT		0x04
#घोषणा PALMAS_PMU_SECONDARY_INT_VBUS_OVV_MASK			0x08
#घोषणा PALMAS_PMU_SECONDARY_INT_VBUS_OVV_MASK_SHIFT		0x03
#घोषणा PALMAS_PMU_SECONDARY_INT_CHARG_DET_N_MASK		0x04
#घोषणा PALMAS_PMU_SECONDARY_INT_CHARG_DET_N_MASK_SHIFT		0x02
#घोषणा PALMAS_PMU_SECONDARY_INT_BB_MASK			0x02
#घोषणा PALMAS_PMU_SECONDARY_INT_BB_MASK_SHIFT			0x01
#घोषणा PALMAS_PMU_SECONDARY_INT_FBI_MASK			0x01
#घोषणा PALMAS_PMU_SECONDARY_INT_FBI_MASK_SHIFT			0x00

/* Bit definitions क्रम SW_REVISION */
#घोषणा PALMAS_SW_REVISION_SW_REVISION_MASK			0xFF
#घोषणा PALMAS_SW_REVISION_SW_REVISION_SHIFT			0x00

/* Bit definitions क्रम EXT_CHRG_CTRL */
#घोषणा PALMAS_EXT_CHRG_CTRL_VBUS_OVV_STATUS			0x80
#घोषणा PALMAS_EXT_CHRG_CTRL_VBUS_OVV_STATUS_SHIFT		0x07
#घोषणा PALMAS_EXT_CHRG_CTRL_CHARG_DET_N_STATUS			0x40
#घोषणा PALMAS_EXT_CHRG_CTRL_CHARG_DET_N_STATUS_SHIFT		0x06
#घोषणा PALMAS_EXT_CHRG_CTRL_VSYS_DEBOUNCE_DELAY		0x08
#घोषणा PALMAS_EXT_CHRG_CTRL_VSYS_DEBOUNCE_DELAY_SHIFT		0x03
#घोषणा PALMAS_EXT_CHRG_CTRL_CHRG_DET_N				0x04
#घोषणा PALMAS_EXT_CHRG_CTRL_CHRG_DET_N_SHIFT			0x02
#घोषणा PALMAS_EXT_CHRG_CTRL_AUTO_ACA_EN			0x02
#घोषणा PALMAS_EXT_CHRG_CTRL_AUTO_ACA_EN_SHIFT			0x01
#घोषणा PALMAS_EXT_CHRG_CTRL_AUTO_LDOUSB_EN			0x01
#घोषणा PALMAS_EXT_CHRG_CTRL_AUTO_LDOUSB_EN_SHIFT		0x00

/* Bit definitions क्रम PMU_SECONDARY_INT2 */
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS2_INT_SRC			0x20
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS2_INT_SRC_SHIFT		0x05
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS1_INT_SRC			0x10
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS1_INT_SRC_SHIFT		0x04
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS2_MASK			0x02
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS2_MASK_SHIFT		0x01
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS1_MASK			0x01
#घोषणा PALMAS_PMU_SECONDARY_INT2_DVFS1_MASK_SHIFT		0x00

/* Registers क्रम function RESOURCE */
#घोषणा PALMAS_CLK32KG_CTRL					0x00
#घोषणा PALMAS_CLK32KGAUDIO_CTRL				0x01
#घोषणा PALMAS_REGEN1_CTRL					0x02
#घोषणा PALMAS_REGEN2_CTRL					0x03
#घोषणा PALMAS_SYSEN1_CTRL					0x04
#घोषणा PALMAS_SYSEN2_CTRL					0x05
#घोषणा PALMAS_NSLEEP_RES_ASSIGN				0x06
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN				0x07
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1				0x08
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2				0x09
#घोषणा PALMAS_ENABLE1_RES_ASSIGN				0x0A
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN				0x0B
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1				0x0C
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2				0x0D
#घोषणा PALMAS_ENABLE2_RES_ASSIGN				0x0E
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN				0x0F
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1				0x10
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2				0x11
#घोषणा PALMAS_REGEN3_CTRL					0x12

/* Bit definitions क्रम CLK32KG_CTRL */
#घोषणा PALMAS_CLK32KG_CTRL_STATUS				0x10
#घोषणा PALMAS_CLK32KG_CTRL_STATUS_SHIFT			0x04
#घोषणा PALMAS_CLK32KG_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_CLK32KG_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_CLK32KG_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_CLK32KG_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम CLK32KGAUDIO_CTRL */
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_STATUS				0x10
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_STATUS_SHIFT			0x04
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_RESERVED3			0x08
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_RESERVED3_SHIFT		0x03
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_MODE_SLEEP			0x04
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_MODE_SLEEP_SHIFT		0x02
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_MODE_ACTIVE			0x01
#घोषणा PALMAS_CLK32KGAUDIO_CTRL_MODE_ACTIVE_SHIFT		0x00

/* Bit definitions क्रम REGEN1_CTRL */
#घोषणा PALMAS_REGEN1_CTRL_STATUS				0x10
#घोषणा PALMAS_REGEN1_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_REGEN1_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_REGEN1_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_REGEN1_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_REGEN1_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम REGEN2_CTRL */
#घोषणा PALMAS_REGEN2_CTRL_STATUS				0x10
#घोषणा PALMAS_REGEN2_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_REGEN2_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_REGEN2_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_REGEN2_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_REGEN2_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SYSEN1_CTRL */
#घोषणा PALMAS_SYSEN1_CTRL_STATUS				0x10
#घोषणा PALMAS_SYSEN1_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SYSEN1_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_SYSEN1_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SYSEN1_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_SYSEN1_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SYSEN2_CTRL */
#घोषणा PALMAS_SYSEN2_CTRL_STATUS				0x10
#घोषणा PALMAS_SYSEN2_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_SYSEN2_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_SYSEN2_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_SYSEN2_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_SYSEN2_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम NSLEEP_RES_ASSIGN */
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_REGEN3				0x40
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_REGEN3_SHIFT			0x06
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_CLK32KGAUDIO			0x20
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_CLK32KGAUDIO_SHIFT		0x05
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_CLK32KG			0x10
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_CLK32KG_SHIFT			0x04
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_SYSEN2				0x08
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_SYSEN2_SHIFT			0x03
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_SYSEN1				0x04
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_SYSEN1_SHIFT			0x02
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_REGEN2				0x02
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_REGEN2_SHIFT			0x01
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_REGEN1				0x01
#घोषणा PALMAS_NSLEEP_RES_ASSIGN_REGEN1_SHIFT			0x00

/* Bit definitions क्रम NSLEEP_SMPS_ASSIGN */
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS10			0x80
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS10_SHIFT			0x07
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS9				0x40
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS9_SHIFT			0x06
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS8				0x20
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS8_SHIFT			0x05
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS7				0x10
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS7_SHIFT			0x04
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS6				0x08
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS6_SHIFT			0x03
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS45			0x04
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS45_SHIFT			0x02
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS3				0x02
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS3_SHIFT			0x01
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS12			0x01
#घोषणा PALMAS_NSLEEP_SMPS_ASSIGN_SMPS12_SHIFT			0x00

/* Bit definitions क्रम NSLEEP_LDO_ASSIGN1 */
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO8				0x80
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO8_SHIFT			0x07
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO7				0x40
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO7_SHIFT			0x06
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO6				0x20
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO6_SHIFT			0x05
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO5				0x10
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO5_SHIFT			0x04
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO4				0x08
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO4_SHIFT			0x03
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO3				0x04
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO3_SHIFT			0x02
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO2				0x02
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO2_SHIFT			0x01
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO1				0x01
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN1_LDO1_SHIFT			0x00

/* Bit definitions क्रम NSLEEP_LDO_ASSIGN2 */
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2_LDOUSB			0x04
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2_LDOUSB_SHIFT			0x02
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2_LDOLN				0x02
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2_LDOLN_SHIFT			0x01
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2_LDO9				0x01
#घोषणा PALMAS_NSLEEP_LDO_ASSIGN2_LDO9_SHIFT			0x00

/* Bit definitions क्रम ENABLE1_RES_ASSIGN */
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_REGEN3			0x40
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_REGEN3_SHIFT			0x06
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_CLK32KGAUDIO			0x20
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_CLK32KGAUDIO_SHIFT		0x05
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_CLK32KG			0x10
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_CLK32KG_SHIFT			0x04
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_SYSEN2			0x08
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_SYSEN2_SHIFT			0x03
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_SYSEN1			0x04
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_SYSEN1_SHIFT			0x02
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_REGEN2			0x02
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_REGEN2_SHIFT			0x01
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_REGEN1			0x01
#घोषणा PALMAS_ENABLE1_RES_ASSIGN_REGEN1_SHIFT			0x00

/* Bit definitions क्रम ENABLE1_SMPS_ASSIGN */
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS10			0x80
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS10_SHIFT			0x07
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS9			0x40
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS9_SHIFT			0x06
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS8			0x20
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS8_SHIFT			0x05
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS7			0x10
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS7_SHIFT			0x04
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS6			0x08
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS6_SHIFT			0x03
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS45			0x04
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS45_SHIFT			0x02
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS3			0x02
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS3_SHIFT			0x01
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS12			0x01
#घोषणा PALMAS_ENABLE1_SMPS_ASSIGN_SMPS12_SHIFT			0x00

/* Bit definitions क्रम ENABLE1_LDO_ASSIGN1 */
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO8				0x80
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO8_SHIFT			0x07
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO7				0x40
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO7_SHIFT			0x06
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO6				0x20
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO6_SHIFT			0x05
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO5				0x10
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO5_SHIFT			0x04
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO4				0x08
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO4_SHIFT			0x03
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO3				0x04
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO3_SHIFT			0x02
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO2				0x02
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO2_SHIFT			0x01
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO1				0x01
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN1_LDO1_SHIFT			0x00

/* Bit definitions क्रम ENABLE1_LDO_ASSIGN2 */
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2_LDOUSB			0x04
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2_LDOUSB_SHIFT			0x02
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2_LDOLN			0x02
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2_LDOLN_SHIFT			0x01
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2_LDO9				0x01
#घोषणा PALMAS_ENABLE1_LDO_ASSIGN2_LDO9_SHIFT			0x00

/* Bit definitions क्रम ENABLE2_RES_ASSIGN */
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_REGEN3			0x40
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_REGEN3_SHIFT			0x06
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_CLK32KGAUDIO			0x20
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_CLK32KGAUDIO_SHIFT		0x05
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_CLK32KG			0x10
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_CLK32KG_SHIFT			0x04
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_SYSEN2			0x08
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_SYSEN2_SHIFT			0x03
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_SYSEN1			0x04
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_SYSEN1_SHIFT			0x02
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_REGEN2			0x02
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_REGEN2_SHIFT			0x01
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_REGEN1			0x01
#घोषणा PALMAS_ENABLE2_RES_ASSIGN_REGEN1_SHIFT			0x00

/* Bit definitions क्रम ENABLE2_SMPS_ASSIGN */
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS10			0x80
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS10_SHIFT			0x07
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS9			0x40
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS9_SHIFT			0x06
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS8			0x20
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS8_SHIFT			0x05
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS7			0x10
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS7_SHIFT			0x04
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS6			0x08
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS6_SHIFT			0x03
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS45			0x04
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS45_SHIFT			0x02
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS3			0x02
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS3_SHIFT			0x01
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS12			0x01
#घोषणा PALMAS_ENABLE2_SMPS_ASSIGN_SMPS12_SHIFT			0x00

/* Bit definitions क्रम ENABLE2_LDO_ASSIGN1 */
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO8				0x80
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO8_SHIFT			0x07
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO7				0x40
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO7_SHIFT			0x06
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO6				0x20
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO6_SHIFT			0x05
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO5				0x10
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO5_SHIFT			0x04
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO4				0x08
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO4_SHIFT			0x03
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO3				0x04
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO3_SHIFT			0x02
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO2				0x02
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO2_SHIFT			0x01
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO1				0x01
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN1_LDO1_SHIFT			0x00

/* Bit definitions क्रम ENABLE2_LDO_ASSIGN2 */
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2_LDOUSB			0x04
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2_LDOUSB_SHIFT			0x02
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2_LDOLN			0x02
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2_LDOLN_SHIFT			0x01
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2_LDO9				0x01
#घोषणा PALMAS_ENABLE2_LDO_ASSIGN2_LDO9_SHIFT			0x00

/* Bit definitions क्रम REGEN3_CTRL */
#घोषणा PALMAS_REGEN3_CTRL_STATUS				0x10
#घोषणा PALMAS_REGEN3_CTRL_STATUS_SHIFT				0x04
#घोषणा PALMAS_REGEN3_CTRL_MODE_SLEEP				0x04
#घोषणा PALMAS_REGEN3_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा PALMAS_REGEN3_CTRL_MODE_ACTIVE				0x01
#घोषणा PALMAS_REGEN3_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Registers क्रम function PAD_CONTROL */
#घोषणा PALMAS_OD_OUTPUT_CTRL2					0x02
#घोषणा PALMAS_POLARITY_CTRL2					0x03
#घोषणा PALMAS_PU_PD_INPUT_CTRL1				0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL2				0x05
#घोषणा PALMAS_PU_PD_INPUT_CTRL3				0x06
#घोषणा PALMAS_PU_PD_INPUT_CTRL5				0x07
#घोषणा PALMAS_OD_OUTPUT_CTRL					0x08
#घोषणा PALMAS_POLARITY_CTRL					0x09
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1				0x0A
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2				0x0B
#घोषणा PALMAS_I2C_SPI						0x0C
#घोषणा PALMAS_PU_PD_INPUT_CTRL4				0x0D
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD3				0x0E
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD4				0x0F

/* Bit definitions क्रम PU_PD_INPUT_CTRL1 */
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_RESET_IN_PD			0x40
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_RESET_IN_PD_SHIFT		0x06
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_GPADC_START_PU			0x20
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_GPADC_START_PU_SHIFT		0x05
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_GPADC_START_PD			0x10
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_GPADC_START_PD_SHIFT		0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_PWRDOWN_PD			0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_PWRDOWN_PD_SHIFT		0x02
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_NRESWARM_PU			0x02
#घोषणा PALMAS_PU_PD_INPUT_CTRL1_NRESWARM_PU_SHIFT		0x01

/* Bit definitions क्रम PU_PD_INPUT_CTRL2 */
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE2_PU			0x20
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE2_PU_SHIFT		0x05
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE2_PD			0x10
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE2_PD_SHIFT		0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE1_PU			0x08
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE1_PU_SHIFT		0x03
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE1_PD			0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_ENABLE1_PD_SHIFT		0x02
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_NSLEEP_PU			0x02
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_NSLEEP_PU_SHIFT		0x01
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_NSLEEP_PD			0x01
#घोषणा PALMAS_PU_PD_INPUT_CTRL2_NSLEEP_PD_SHIFT		0x00

/* Bit definitions क्रम PU_PD_INPUT_CTRL3 */
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_ACOK_PD			0x40
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_ACOK_PD_SHIFT			0x06
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_CHRG_DET_N_PD			0x10
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_CHRG_DET_N_PD_SHIFT		0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_POWERHOLD_PD			0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_POWERHOLD_PD_SHIFT		0x02
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_MSECURE_PD			0x01
#घोषणा PALMAS_PU_PD_INPUT_CTRL3_MSECURE_PD_SHIFT		0x00

/* Bit definitions क्रम OD_OUTPUT_CTRL */
#घोषणा PALMAS_OD_OUTPUT_CTRL_PWM_2_OD				0x80
#घोषणा PALMAS_OD_OUTPUT_CTRL_PWM_2_OD_SHIFT			0x07
#घोषणा PALMAS_OD_OUTPUT_CTRL_VBUSDET_OD			0x40
#घोषणा PALMAS_OD_OUTPUT_CTRL_VBUSDET_OD_SHIFT			0x06
#घोषणा PALMAS_OD_OUTPUT_CTRL_PWM_1_OD				0x20
#घोषणा PALMAS_OD_OUTPUT_CTRL_PWM_1_OD_SHIFT			0x05
#घोषणा PALMAS_OD_OUTPUT_CTRL_INT_OD				0x08
#घोषणा PALMAS_OD_OUTPUT_CTRL_INT_OD_SHIFT			0x03

/* Bit definitions क्रम POLARITY_CTRL */
#घोषणा PALMAS_POLARITY_CTRL_INT_POLARITY			0x80
#घोषणा PALMAS_POLARITY_CTRL_INT_POLARITY_SHIFT			0x07
#घोषणा PALMAS_POLARITY_CTRL_ENABLE2_POLARITY			0x40
#घोषणा PALMAS_POLARITY_CTRL_ENABLE2_POLARITY_SHIFT		0x06
#घोषणा PALMAS_POLARITY_CTRL_ENABLE1_POLARITY			0x20
#घोषणा PALMAS_POLARITY_CTRL_ENABLE1_POLARITY_SHIFT		0x05
#घोषणा PALMAS_POLARITY_CTRL_NSLEEP_POLARITY			0x10
#घोषणा PALMAS_POLARITY_CTRL_NSLEEP_POLARITY_SHIFT		0x04
#घोषणा PALMAS_POLARITY_CTRL_RESET_IN_POLARITY			0x08
#घोषणा PALMAS_POLARITY_CTRL_RESET_IN_POLARITY_SHIFT		0x03
#घोषणा PALMAS_POLARITY_CTRL_GPIO_3_CHRG_DET_N_POLARITY		0x04
#घोषणा PALMAS_POLARITY_CTRL_GPIO_3_CHRG_DET_N_POLARITY_SHIFT	0x02
#घोषणा PALMAS_POLARITY_CTRL_POWERGOOD_USB_PSEL_POLARITY	0x02
#घोषणा PALMAS_POLARITY_CTRL_POWERGOOD_USB_PSEL_POLARITY_SHIFT	0x01
#घोषणा PALMAS_POLARITY_CTRL_PWRDOWN_POLARITY			0x01
#घोषणा PALMAS_POLARITY_CTRL_PWRDOWN_POLARITY_SHIFT		0x00

/* Bit definitions क्रम PRIMARY_SECONDARY_PAD1 */
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_3			0x80
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_3_SHIFT		0x07
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK		0x60
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_SHIFT		0x05
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK		0x18
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT		0x03
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_0			0x04
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_0_SHIFT		0x02
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_VAC			0x02
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_VAC_SHIFT			0x01
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_POWERGOOD			0x01
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD1_POWERGOOD_SHIFT		0x00

/* Bit definitions क्रम PRIMARY_SECONDARY_PAD2 */
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_7_MASK		0x30
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_7_SHIFT		0x04
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_6			0x08
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_6_SHIFT		0x03
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_5_MASK		0x06
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_5_SHIFT		0x01
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_4			0x01
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_4_SHIFT		0x00

/* Bit definitions क्रम I2C_SPI */
#घोषणा PALMAS_I2C_SPI_I2C2OTP_EN				0x80
#घोषणा PALMAS_I2C_SPI_I2C2OTP_EN_SHIFT				0x07
#घोषणा PALMAS_I2C_SPI_I2C2OTP_PAGESEL				0x40
#घोषणा PALMAS_I2C_SPI_I2C2OTP_PAGESEL_SHIFT			0x06
#घोषणा PALMAS_I2C_SPI_ID_I2C2					0x20
#घोषणा PALMAS_I2C_SPI_ID_I2C2_SHIFT				0x05
#घोषणा PALMAS_I2C_SPI_I2C_SPI					0x10
#घोषणा PALMAS_I2C_SPI_I2C_SPI_SHIFT				0x04
#घोषणा PALMAS_I2C_SPI_ID_I2C1_MASK				0x0F
#घोषणा PALMAS_I2C_SPI_ID_I2C1_SHIFT				0x00

/* Bit definitions क्रम PU_PD_INPUT_CTRL4 */
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS2_DAT_PD			0x40
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS2_DAT_PD_SHIFT		0x06
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS2_CLK_PD			0x10
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS2_CLK_PD_SHIFT		0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS1_DAT_PD			0x04
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS1_DAT_PD_SHIFT		0x02
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS1_CLK_PD			0x01
#घोषणा PALMAS_PU_PD_INPUT_CTRL4_DVFS1_CLK_PD_SHIFT		0x00

/* Bit definitions क्रम PRIMARY_SECONDARY_PAD3 */
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2			0x02
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2_SHIFT		0x01
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD3_DVFS1			0x01
#घोषणा PALMAS_PRIMARY_SECONDARY_PAD3_DVFS1_SHIFT		0x00

/* Registers क्रम function LED_PWM */
#घोषणा PALMAS_LED_PERIOD_CTRL					0x00
#घोषणा PALMAS_LED_CTRL						0x01
#घोषणा PALMAS_PWM_CTRL1					0x02
#घोषणा PALMAS_PWM_CTRL2					0x03

/* Bit definitions क्रम LED_PERIOD_CTRL */
#घोषणा PALMAS_LED_PERIOD_CTRL_LED_2_PERIOD_MASK		0x38
#घोषणा PALMAS_LED_PERIOD_CTRL_LED_2_PERIOD_SHIFT		0x03
#घोषणा PALMAS_LED_PERIOD_CTRL_LED_1_PERIOD_MASK		0x07
#घोषणा PALMAS_LED_PERIOD_CTRL_LED_1_PERIOD_SHIFT		0x00

/* Bit definitions क्रम LED_CTRL */
#घोषणा PALMAS_LED_CTRL_LED_2_SEQ				0x20
#घोषणा PALMAS_LED_CTRL_LED_2_SEQ_SHIFT				0x05
#घोषणा PALMAS_LED_CTRL_LED_1_SEQ				0x10
#घोषणा PALMAS_LED_CTRL_LED_1_SEQ_SHIFT				0x04
#घोषणा PALMAS_LED_CTRL_LED_2_ON_TIME_MASK			0x0c
#घोषणा PALMAS_LED_CTRL_LED_2_ON_TIME_SHIFT			0x02
#घोषणा PALMAS_LED_CTRL_LED_1_ON_TIME_MASK			0x03
#घोषणा PALMAS_LED_CTRL_LED_1_ON_TIME_SHIFT			0x00

/* Bit definitions क्रम PWM_CTRL1 */
#घोषणा PALMAS_PWM_CTRL1_PWM_FREQ_EN				0x02
#घोषणा PALMAS_PWM_CTRL1_PWM_FREQ_EN_SHIFT			0x01
#घोषणा PALMAS_PWM_CTRL1_PWM_FREQ_SEL				0x01
#घोषणा PALMAS_PWM_CTRL1_PWM_FREQ_SEL_SHIFT			0x00

/* Bit definitions क्रम PWM_CTRL2 */
#घोषणा PALMAS_PWM_CTRL2_PWM_DUTY_SEL_MASK			0xFF
#घोषणा PALMAS_PWM_CTRL2_PWM_DUTY_SEL_SHIFT			0x00

/* Registers क्रम function INTERRUPT */
#घोषणा PALMAS_INT1_STATUS					0x00
#घोषणा PALMAS_INT1_MASK					0x01
#घोषणा PALMAS_INT1_LINE_STATE					0x02
#घोषणा PALMAS_INT1_EDGE_DETECT1_RESERVED			0x03
#घोषणा PALMAS_INT1_EDGE_DETECT2_RESERVED			0x04
#घोषणा PALMAS_INT2_STATUS					0x05
#घोषणा PALMAS_INT2_MASK					0x06
#घोषणा PALMAS_INT2_LINE_STATE					0x07
#घोषणा PALMAS_INT2_EDGE_DETECT1_RESERVED			0x08
#घोषणा PALMAS_INT2_EDGE_DETECT2_RESERVED			0x09
#घोषणा PALMAS_INT3_STATUS					0x0A
#घोषणा PALMAS_INT3_MASK					0x0B
#घोषणा PALMAS_INT3_LINE_STATE					0x0C
#घोषणा PALMAS_INT3_EDGE_DETECT1_RESERVED			0x0D
#घोषणा PALMAS_INT3_EDGE_DETECT2_RESERVED			0x0E
#घोषणा PALMAS_INT4_STATUS					0x0F
#घोषणा PALMAS_INT4_MASK					0x10
#घोषणा PALMAS_INT4_LINE_STATE					0x11
#घोषणा PALMAS_INT4_EDGE_DETECT1				0x12
#घोषणा PALMAS_INT4_EDGE_DETECT2				0x13
#घोषणा PALMAS_INT_CTRL						0x14

/* Bit definitions क्रम INT1_STATUS */
#घोषणा PALMAS_INT1_STATUS_VBAT_MON				0x80
#घोषणा PALMAS_INT1_STATUS_VBAT_MON_SHIFT			0x07
#घोषणा PALMAS_INT1_STATUS_VSYS_MON				0x40
#घोषणा PALMAS_INT1_STATUS_VSYS_MON_SHIFT			0x06
#घोषणा PALMAS_INT1_STATUS_HOTDIE				0x20
#घोषणा PALMAS_INT1_STATUS_HOTDIE_SHIFT				0x05
#घोषणा PALMAS_INT1_STATUS_PWRDOWN				0x10
#घोषणा PALMAS_INT1_STATUS_PWRDOWN_SHIFT			0x04
#घोषणा PALMAS_INT1_STATUS_RPWRON				0x08
#घोषणा PALMAS_INT1_STATUS_RPWRON_SHIFT				0x03
#घोषणा PALMAS_INT1_STATUS_LONG_PRESS_KEY			0x04
#घोषणा PALMAS_INT1_STATUS_LONG_PRESS_KEY_SHIFT			0x02
#घोषणा PALMAS_INT1_STATUS_PWRON				0x02
#घोषणा PALMAS_INT1_STATUS_PWRON_SHIFT				0x01
#घोषणा PALMAS_INT1_STATUS_CHARG_DET_N_VBUS_OVV			0x01
#घोषणा PALMAS_INT1_STATUS_CHARG_DET_N_VBUS_OVV_SHIFT		0x00

/* Bit definitions क्रम INT1_MASK */
#घोषणा PALMAS_INT1_MASK_VBAT_MON				0x80
#घोषणा PALMAS_INT1_MASK_VBAT_MON_SHIFT				0x07
#घोषणा PALMAS_INT1_MASK_VSYS_MON				0x40
#घोषणा PALMAS_INT1_MASK_VSYS_MON_SHIFT				0x06
#घोषणा PALMAS_INT1_MASK_HOTDIE					0x20
#घोषणा PALMAS_INT1_MASK_HOTDIE_SHIFT				0x05
#घोषणा PALMAS_INT1_MASK_PWRDOWN				0x10
#घोषणा PALMAS_INT1_MASK_PWRDOWN_SHIFT				0x04
#घोषणा PALMAS_INT1_MASK_RPWRON					0x08
#घोषणा PALMAS_INT1_MASK_RPWRON_SHIFT				0x03
#घोषणा PALMAS_INT1_MASK_LONG_PRESS_KEY				0x04
#घोषणा PALMAS_INT1_MASK_LONG_PRESS_KEY_SHIFT			0x02
#घोषणा PALMAS_INT1_MASK_PWRON					0x02
#घोषणा PALMAS_INT1_MASK_PWRON_SHIFT				0x01
#घोषणा PALMAS_INT1_MASK_CHARG_DET_N_VBUS_OVV			0x01
#घोषणा PALMAS_INT1_MASK_CHARG_DET_N_VBUS_OVV_SHIFT		0x00

/* Bit definitions क्रम INT1_LINE_STATE */
#घोषणा PALMAS_INT1_LINE_STATE_VBAT_MON				0x80
#घोषणा PALMAS_INT1_LINE_STATE_VBAT_MON_SHIFT			0x07
#घोषणा PALMAS_INT1_LINE_STATE_VSYS_MON				0x40
#घोषणा PALMAS_INT1_LINE_STATE_VSYS_MON_SHIFT			0x06
#घोषणा PALMAS_INT1_LINE_STATE_HOTDIE				0x20
#घोषणा PALMAS_INT1_LINE_STATE_HOTDIE_SHIFT			0x05
#घोषणा PALMAS_INT1_LINE_STATE_PWRDOWN				0x10
#घोषणा PALMAS_INT1_LINE_STATE_PWRDOWN_SHIFT			0x04
#घोषणा PALMAS_INT1_LINE_STATE_RPWRON				0x08
#घोषणा PALMAS_INT1_LINE_STATE_RPWRON_SHIFT			0x03
#घोषणा PALMAS_INT1_LINE_STATE_LONG_PRESS_KEY			0x04
#घोषणा PALMAS_INT1_LINE_STATE_LONG_PRESS_KEY_SHIFT		0x02
#घोषणा PALMAS_INT1_LINE_STATE_PWRON				0x02
#घोषणा PALMAS_INT1_LINE_STATE_PWRON_SHIFT			0x01
#घोषणा PALMAS_INT1_LINE_STATE_CHARG_DET_N_VBUS_OVV		0x01
#घोषणा PALMAS_INT1_LINE_STATE_CHARG_DET_N_VBUS_OVV_SHIFT	0x00

/* Bit definitions क्रम INT2_STATUS */
#घोषणा PALMAS_INT2_STATUS_VAC_ACOK				0x80
#घोषणा PALMAS_INT2_STATUS_VAC_ACOK_SHIFT			0x07
#घोषणा PALMAS_INT2_STATUS_SHORT				0x40
#घोषणा PALMAS_INT2_STATUS_SHORT_SHIFT				0x06
#घोषणा PALMAS_INT2_STATUS_FBI_BB				0x20
#घोषणा PALMAS_INT2_STATUS_FBI_BB_SHIFT				0x05
#घोषणा PALMAS_INT2_STATUS_RESET_IN				0x10
#घोषणा PALMAS_INT2_STATUS_RESET_IN_SHIFT			0x04
#घोषणा PALMAS_INT2_STATUS_BATREMOVAL				0x08
#घोषणा PALMAS_INT2_STATUS_BATREMOVAL_SHIFT			0x03
#घोषणा PALMAS_INT2_STATUS_WDT					0x04
#घोषणा PALMAS_INT2_STATUS_WDT_SHIFT				0x02
#घोषणा PALMAS_INT2_STATUS_RTC_TIMER				0x02
#घोषणा PALMAS_INT2_STATUS_RTC_TIMER_SHIFT			0x01
#घोषणा PALMAS_INT2_STATUS_RTC_ALARM				0x01
#घोषणा PALMAS_INT2_STATUS_RTC_ALARM_SHIFT			0x00

/* Bit definitions क्रम INT2_MASK */
#घोषणा PALMAS_INT2_MASK_VAC_ACOK				0x80
#घोषणा PALMAS_INT2_MASK_VAC_ACOK_SHIFT				0x07
#घोषणा PALMAS_INT2_MASK_SHORT					0x40
#घोषणा PALMAS_INT2_MASK_SHORT_SHIFT				0x06
#घोषणा PALMAS_INT2_MASK_FBI_BB					0x20
#घोषणा PALMAS_INT2_MASK_FBI_BB_SHIFT				0x05
#घोषणा PALMAS_INT2_MASK_RESET_IN				0x10
#घोषणा PALMAS_INT2_MASK_RESET_IN_SHIFT				0x04
#घोषणा PALMAS_INT2_MASK_BATREMOVAL				0x08
#घोषणा PALMAS_INT2_MASK_BATREMOVAL_SHIFT			0x03
#घोषणा PALMAS_INT2_MASK_WDT					0x04
#घोषणा PALMAS_INT2_MASK_WDT_SHIFT				0x02
#घोषणा PALMAS_INT2_MASK_RTC_TIMER				0x02
#घोषणा PALMAS_INT2_MASK_RTC_TIMER_SHIFT			0x01
#घोषणा PALMAS_INT2_MASK_RTC_ALARM				0x01
#घोषणा PALMAS_INT2_MASK_RTC_ALARM_SHIFT			0x00

/* Bit definitions क्रम INT2_LINE_STATE */
#घोषणा PALMAS_INT2_LINE_STATE_VAC_ACOK				0x80
#घोषणा PALMAS_INT2_LINE_STATE_VAC_ACOK_SHIFT			0x07
#घोषणा PALMAS_INT2_LINE_STATE_SHORT				0x40
#घोषणा PALMAS_INT2_LINE_STATE_SHORT_SHIFT			0x06
#घोषणा PALMAS_INT2_LINE_STATE_FBI_BB				0x20
#घोषणा PALMAS_INT2_LINE_STATE_FBI_BB_SHIFT			0x05
#घोषणा PALMAS_INT2_LINE_STATE_RESET_IN				0x10
#घोषणा PALMAS_INT2_LINE_STATE_RESET_IN_SHIFT			0x04
#घोषणा PALMAS_INT2_LINE_STATE_BATREMOVAL			0x08
#घोषणा PALMAS_INT2_LINE_STATE_BATREMOVAL_SHIFT			0x03
#घोषणा PALMAS_INT2_LINE_STATE_WDT				0x04
#घोषणा PALMAS_INT2_LINE_STATE_WDT_SHIFT			0x02
#घोषणा PALMAS_INT2_LINE_STATE_RTC_TIMER			0x02
#घोषणा PALMAS_INT2_LINE_STATE_RTC_TIMER_SHIFT			0x01
#घोषणा PALMAS_INT2_LINE_STATE_RTC_ALARM			0x01
#घोषणा PALMAS_INT2_LINE_STATE_RTC_ALARM_SHIFT			0x00

/* Bit definitions क्रम INT3_STATUS */
#घोषणा PALMAS_INT3_STATUS_VBUS					0x80
#घोषणा PALMAS_INT3_STATUS_VBUS_SHIFT				0x07
#घोषणा PALMAS_INT3_STATUS_VBUS_OTG				0x40
#घोषणा PALMAS_INT3_STATUS_VBUS_OTG_SHIFT			0x06
#घोषणा PALMAS_INT3_STATUS_ID					0x20
#घोषणा PALMAS_INT3_STATUS_ID_SHIFT				0x05
#घोषणा PALMAS_INT3_STATUS_ID_OTG				0x10
#घोषणा PALMAS_INT3_STATUS_ID_OTG_SHIFT				0x04
#घोषणा PALMAS_INT3_STATUS_GPADC_EOC_RT				0x08
#घोषणा PALMAS_INT3_STATUS_GPADC_EOC_RT_SHIFT			0x03
#घोषणा PALMAS_INT3_STATUS_GPADC_EOC_SW				0x04
#घोषणा PALMAS_INT3_STATUS_GPADC_EOC_SW_SHIFT			0x02
#घोषणा PALMAS_INT3_STATUS_GPADC_AUTO_1				0x02
#घोषणा PALMAS_INT3_STATUS_GPADC_AUTO_1_SHIFT			0x01
#घोषणा PALMAS_INT3_STATUS_GPADC_AUTO_0				0x01
#घोषणा PALMAS_INT3_STATUS_GPADC_AUTO_0_SHIFT			0x00

/* Bit definitions क्रम INT3_MASK */
#घोषणा PALMAS_INT3_MASK_VBUS					0x80
#घोषणा PALMAS_INT3_MASK_VBUS_SHIFT				0x07
#घोषणा PALMAS_INT3_MASK_VBUS_OTG				0x40
#घोषणा PALMAS_INT3_MASK_VBUS_OTG_SHIFT				0x06
#घोषणा PALMAS_INT3_MASK_ID					0x20
#घोषणा PALMAS_INT3_MASK_ID_SHIFT				0x05
#घोषणा PALMAS_INT3_MASK_ID_OTG					0x10
#घोषणा PALMAS_INT3_MASK_ID_OTG_SHIFT				0x04
#घोषणा PALMAS_INT3_MASK_GPADC_EOC_RT				0x08
#घोषणा PALMAS_INT3_MASK_GPADC_EOC_RT_SHIFT			0x03
#घोषणा PALMAS_INT3_MASK_GPADC_EOC_SW				0x04
#घोषणा PALMAS_INT3_MASK_GPADC_EOC_SW_SHIFT			0x02
#घोषणा PALMAS_INT3_MASK_GPADC_AUTO_1				0x02
#घोषणा PALMAS_INT3_MASK_GPADC_AUTO_1_SHIFT			0x01
#घोषणा PALMAS_INT3_MASK_GPADC_AUTO_0				0x01
#घोषणा PALMAS_INT3_MASK_GPADC_AUTO_0_SHIFT			0x00

/* Bit definitions क्रम INT3_LINE_STATE */
#घोषणा PALMAS_INT3_LINE_STATE_VBUS				0x80
#घोषणा PALMAS_INT3_LINE_STATE_VBUS_SHIFT			0x07
#घोषणा PALMAS_INT3_LINE_STATE_VBUS_OTG				0x40
#घोषणा PALMAS_INT3_LINE_STATE_VBUS_OTG_SHIFT			0x06
#घोषणा PALMAS_INT3_LINE_STATE_ID				0x20
#घोषणा PALMAS_INT3_LINE_STATE_ID_SHIFT				0x05
#घोषणा PALMAS_INT3_LINE_STATE_ID_OTG				0x10
#घोषणा PALMAS_INT3_LINE_STATE_ID_OTG_SHIFT			0x04
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_EOC_RT			0x08
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_EOC_RT_SHIFT		0x03
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_EOC_SW			0x04
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_EOC_SW_SHIFT		0x02
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_AUTO_1			0x02
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_AUTO_1_SHIFT		0x01
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_AUTO_0			0x01
#घोषणा PALMAS_INT3_LINE_STATE_GPADC_AUTO_0_SHIFT		0x00

/* Bit definitions क्रम INT4_STATUS */
#घोषणा PALMAS_INT4_STATUS_GPIO_7				0x80
#घोषणा PALMAS_INT4_STATUS_GPIO_7_SHIFT				0x07
#घोषणा PALMAS_INT4_STATUS_GPIO_6				0x40
#घोषणा PALMAS_INT4_STATUS_GPIO_6_SHIFT				0x06
#घोषणा PALMAS_INT4_STATUS_GPIO_5				0x20
#घोषणा PALMAS_INT4_STATUS_GPIO_5_SHIFT				0x05
#घोषणा PALMAS_INT4_STATUS_GPIO_4				0x10
#घोषणा PALMAS_INT4_STATUS_GPIO_4_SHIFT				0x04
#घोषणा PALMAS_INT4_STATUS_GPIO_3				0x08
#घोषणा PALMAS_INT4_STATUS_GPIO_3_SHIFT				0x03
#घोषणा PALMAS_INT4_STATUS_GPIO_2				0x04
#घोषणा PALMAS_INT4_STATUS_GPIO_2_SHIFT				0x02
#घोषणा PALMAS_INT4_STATUS_GPIO_1				0x02
#घोषणा PALMAS_INT4_STATUS_GPIO_1_SHIFT				0x01
#घोषणा PALMAS_INT4_STATUS_GPIO_0				0x01
#घोषणा PALMAS_INT4_STATUS_GPIO_0_SHIFT				0x00

/* Bit definitions क्रम INT4_MASK */
#घोषणा PALMAS_INT4_MASK_GPIO_7					0x80
#घोषणा PALMAS_INT4_MASK_GPIO_7_SHIFT				0x07
#घोषणा PALMAS_INT4_MASK_GPIO_6					0x40
#घोषणा PALMAS_INT4_MASK_GPIO_6_SHIFT				0x06
#घोषणा PALMAS_INT4_MASK_GPIO_5					0x20
#घोषणा PALMAS_INT4_MASK_GPIO_5_SHIFT				0x05
#घोषणा PALMAS_INT4_MASK_GPIO_4					0x10
#घोषणा PALMAS_INT4_MASK_GPIO_4_SHIFT				0x04
#घोषणा PALMAS_INT4_MASK_GPIO_3					0x08
#घोषणा PALMAS_INT4_MASK_GPIO_3_SHIFT				0x03
#घोषणा PALMAS_INT4_MASK_GPIO_2					0x04
#घोषणा PALMAS_INT4_MASK_GPIO_2_SHIFT				0x02
#घोषणा PALMAS_INT4_MASK_GPIO_1					0x02
#घोषणा PALMAS_INT4_MASK_GPIO_1_SHIFT				0x01
#घोषणा PALMAS_INT4_MASK_GPIO_0					0x01
#घोषणा PALMAS_INT4_MASK_GPIO_0_SHIFT				0x00

/* Bit definitions क्रम INT4_LINE_STATE */
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_7				0x80
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_7_SHIFT			0x07
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_6				0x40
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_6_SHIFT			0x06
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_5				0x20
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_5_SHIFT			0x05
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_4				0x10
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_4_SHIFT			0x04
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_3				0x08
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_3_SHIFT			0x03
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_2				0x04
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_2_SHIFT			0x02
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_1				0x02
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_1_SHIFT			0x01
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_0				0x01
#घोषणा PALMAS_INT4_LINE_STATE_GPIO_0_SHIFT			0x00

/* Bit definitions क्रम INT4_EDGE_DETECT1 */
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_3_RISING			0x80
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_3_RISING_SHIFT		0x07
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_3_FALLING			0x40
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_3_FALLING_SHIFT		0x06
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_2_RISING			0x20
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_2_RISING_SHIFT		0x05
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_2_FALLING			0x10
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_2_FALLING_SHIFT		0x04
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_1_RISING			0x08
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_1_RISING_SHIFT		0x03
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_1_FALLING			0x04
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_1_FALLING_SHIFT		0x02
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_0_RISING			0x02
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_0_RISING_SHIFT		0x01
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_0_FALLING			0x01
#घोषणा PALMAS_INT4_EDGE_DETECT1_GPIO_0_FALLING_SHIFT		0x00

/* Bit definitions क्रम INT4_EDGE_DETECT2 */
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_7_RISING			0x80
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_7_RISING_SHIFT		0x07
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_7_FALLING			0x40
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_7_FALLING_SHIFT		0x06
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_6_RISING			0x20
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_6_RISING_SHIFT		0x05
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_6_FALLING			0x10
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_6_FALLING_SHIFT		0x04
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_5_RISING			0x08
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_5_RISING_SHIFT		0x03
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_5_FALLING			0x04
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_5_FALLING_SHIFT		0x02
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_4_RISING			0x02
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_4_RISING_SHIFT		0x01
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_4_FALLING			0x01
#घोषणा PALMAS_INT4_EDGE_DETECT2_GPIO_4_FALLING_SHIFT		0x00

/* Bit definitions क्रम INT_CTRL */
#घोषणा PALMAS_INT_CTRL_INT_PENDING				0x04
#घोषणा PALMAS_INT_CTRL_INT_PENDING_SHIFT			0x02
#घोषणा PALMAS_INT_CTRL_INT_CLEAR				0x01
#घोषणा PALMAS_INT_CTRL_INT_CLEAR_SHIFT				0x00

/* Registers क्रम function USB_OTG */
#घोषणा PALMAS_USB_WAKEUP					0x03
#घोषणा PALMAS_USB_VBUS_CTRL_SET				0x04
#घोषणा PALMAS_USB_VBUS_CTRL_CLR				0x05
#घोषणा PALMAS_USB_ID_CTRL_SET					0x06
#घोषणा PALMAS_USB_ID_CTRL_CLEAR				0x07
#घोषणा PALMAS_USB_VBUS_INT_SRC					0x08
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET				0x09
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR				0x0A
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET				0x0B
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR				0x0C
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET				0x0D
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR				0x0E
#घोषणा PALMAS_USB_ID_INT_SRC					0x0F
#घोषणा PALMAS_USB_ID_INT_LATCH_SET				0x10
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR				0x11
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET				0x12
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR				0x13
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET				0x14
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR				0x15
#घोषणा PALMAS_USB_OTG_ADP_CTRL					0x16
#घोषणा PALMAS_USB_OTG_ADP_HIGH					0x17
#घोषणा PALMAS_USB_OTG_ADP_LOW					0x18
#घोषणा PALMAS_USB_OTG_ADP_RISE					0x19
#घोषणा PALMAS_USB_OTG_REVISION					0x1A

/* Bit definitions क्रम USB_WAKEUP */
#घोषणा PALMAS_USB_WAKEUP_ID_WK_UP_COMP				0x01
#घोषणा PALMAS_USB_WAKEUP_ID_WK_UP_COMP_SHIFT			0x00

/* Bit definitions क्रम USB_VBUS_CTRL_SET */
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_CHRG_VSYS			0x80
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_CHRG_VSYS_SHIFT		0x07
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_DISCHRG			0x20
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_DISCHRG_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_IADP_SRC			0x10
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_IADP_SRC_SHIFT		0x04
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_IADP_SINK			0x08
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_IADP_SINK_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_ACT_COMP			0x04
#घोषणा PALMAS_USB_VBUS_CTRL_SET_VBUS_ACT_COMP_SHIFT		0x02

/* Bit definitions क्रम USB_VBUS_CTRL_CLR */
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_CHRG_VSYS			0x80
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_CHRG_VSYS_SHIFT		0x07
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_DISCHRG			0x20
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_DISCHRG_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_IADP_SRC			0x10
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_IADP_SRC_SHIFT		0x04
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_IADP_SINK			0x08
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_IADP_SINK_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_ACT_COMP			0x04
#घोषणा PALMAS_USB_VBUS_CTRL_CLR_VBUS_ACT_COMP_SHIFT		0x02

/* Bit definitions क्रम USB_ID_CTRL_SET */
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_PU_220K			0x80
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_PU_220K_SHIFT			0x07
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_PU_100K			0x40
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_PU_100K_SHIFT			0x06
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_GND_DRV			0x20
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_GND_DRV_SHIFT			0x05
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_SRC_16U			0x10
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_SRC_16U_SHIFT			0x04
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_SRC_5U			0x08
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_SRC_5U_SHIFT			0x03
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_ACT_COMP			0x04
#घोषणा PALMAS_USB_ID_CTRL_SET_ID_ACT_COMP_SHIFT		0x02

/* Bit definitions क्रम USB_ID_CTRL_CLEAR */
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_PU_220K			0x80
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_PU_220K_SHIFT		0x07
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_PU_100K			0x40
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_PU_100K_SHIFT		0x06
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_GND_DRV			0x20
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_GND_DRV_SHIFT		0x05
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_SRC_16U			0x10
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_SRC_16U_SHIFT		0x04
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_SRC_5U			0x08
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_SRC_5U_SHIFT		0x03
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_ACT_COMP			0x04
#घोषणा PALMAS_USB_ID_CTRL_CLEAR_ID_ACT_COMP_SHIFT		0x02

/* Bit definitions क्रम USB_VBUS_INT_SRC */
#घोषणा PALMAS_USB_VBUS_INT_SRC_VOTG_SESS_VLD			0x80
#घोषणा PALMAS_USB_VBUS_INT_SRC_VOTG_SESS_VLD_SHIFT		0x07
#घोषणा PALMAS_USB_VBUS_INT_SRC_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_SRC_VADP_PRB_SHIFT			0x06
#घोषणा PALMAS_USB_VBUS_INT_SRC_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_SRC_VADP_SNS_SHIFT			0x05
#घोषणा PALMAS_USB_VBUS_INT_SRC_VA_VBUS_VLD			0x08
#घोषणा PALMAS_USB_VBUS_INT_SRC_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_SRC_VA_SESS_VLD			0x04
#घोषणा PALMAS_USB_VBUS_INT_SRC_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_SRC_VB_SESS_VLD			0x02
#घोषणा PALMAS_USB_VBUS_INT_SRC_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_SRC_VB_SESS_END			0x01
#घोषणा PALMAS_USB_VBUS_INT_SRC_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_VBUS_INT_LATCH_SET */
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VOTG_SESS_VLD		0x80
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VOTG_SESS_VLD_SHIFT	0x07
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VADP_PRB_SHIFT		0x06
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VADP_SNS_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_ADP			0x10
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_ADP_SHIFT			0x04
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VA_VBUS_VLD		0x08
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VA_SESS_VLD		0x04
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VB_SESS_VLD		0x02
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VB_SESS_END		0x01
#घोषणा PALMAS_USB_VBUS_INT_LATCH_SET_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_VBUS_INT_LATCH_CLR */
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VOTG_SESS_VLD		0x80
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VOTG_SESS_VLD_SHIFT	0x07
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VADP_PRB_SHIFT		0x06
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VADP_SNS_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_ADP			0x10
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_ADP_SHIFT			0x04
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VA_VBUS_VLD		0x08
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VA_SESS_VLD		0x04
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VB_SESS_VLD		0x02
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VB_SESS_END		0x01
#घोषणा PALMAS_USB_VBUS_INT_LATCH_CLR_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_VBUS_INT_EN_LO_SET */
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VOTG_SESS_VLD		0x80
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VOTG_SESS_VLD_SHIFT	0x07
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VADP_PRB_SHIFT		0x06
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VADP_SNS_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VA_VBUS_VLD		0x08
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VA_SESS_VLD		0x04
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VB_SESS_VLD		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VB_SESS_END		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_SET_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_VBUS_INT_EN_LO_CLR */
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VOTG_SESS_VLD		0x80
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VOTG_SESS_VLD_SHIFT	0x07
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VADP_PRB_SHIFT		0x06
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VADP_SNS_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VA_VBUS_VLD		0x08
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VA_SESS_VLD		0x04
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VB_SESS_VLD		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VB_SESS_END		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_LO_CLR_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_VBUS_INT_EN_HI_SET */
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VOTG_SESS_VLD		0x80
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VOTG_SESS_VLD_SHIFT	0x07
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VADP_PRB_SHIFT		0x06
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VADP_SNS_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_ADP			0x10
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_ADP_SHIFT			0x04
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VA_VBUS_VLD		0x08
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VA_SESS_VLD		0x04
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VB_SESS_VLD		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VB_SESS_END		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_SET_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_VBUS_INT_EN_HI_CLR */
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VOTG_SESS_VLD		0x80
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VOTG_SESS_VLD_SHIFT	0x07
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VADP_PRB			0x40
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VADP_PRB_SHIFT		0x06
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VADP_SNS			0x20
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VADP_SNS_SHIFT		0x05
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_ADP			0x10
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_ADP_SHIFT			0x04
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VA_VBUS_VLD		0x08
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VA_VBUS_VLD_SHIFT		0x03
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VA_SESS_VLD		0x04
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VA_SESS_VLD_SHIFT		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VB_SESS_VLD		0x02
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VB_SESS_VLD_SHIFT		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VB_SESS_END		0x01
#घोषणा PALMAS_USB_VBUS_INT_EN_HI_CLR_VB_SESS_END_SHIFT		0x00

/* Bit definitions क्रम USB_ID_INT_SRC */
#घोषणा PALMAS_USB_ID_INT_SRC_ID_FLOAT				0x10
#घोषणा PALMAS_USB_ID_INT_SRC_ID_FLOAT_SHIFT			0x04
#घोषणा PALMAS_USB_ID_INT_SRC_ID_A				0x08
#घोषणा PALMAS_USB_ID_INT_SRC_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_SRC_ID_B				0x04
#घोषणा PALMAS_USB_ID_INT_SRC_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_SRC_ID_C				0x02
#घोषणा PALMAS_USB_ID_INT_SRC_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_SRC_ID_GND				0x01
#घोषणा PALMAS_USB_ID_INT_SRC_ID_GND_SHIFT			0x00

/* Bit definitions क्रम USB_ID_INT_LATCH_SET */
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_FLOAT			0x10
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_FLOAT_SHIFT		0x04
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_A			0x08
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_B			0x04
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_C			0x02
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_GND			0x01
#घोषणा PALMAS_USB_ID_INT_LATCH_SET_ID_GND_SHIFT		0x00

/* Bit definitions क्रम USB_ID_INT_LATCH_CLR */
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_FLOAT			0x10
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_FLOAT_SHIFT		0x04
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_A			0x08
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_B			0x04
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_C			0x02
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_GND			0x01
#घोषणा PALMAS_USB_ID_INT_LATCH_CLR_ID_GND_SHIFT		0x00

/* Bit definitions क्रम USB_ID_INT_EN_LO_SET */
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_FLOAT			0x10
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_FLOAT_SHIFT		0x04
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_A			0x08
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_B			0x04
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_C			0x02
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_GND			0x01
#घोषणा PALMAS_USB_ID_INT_EN_LO_SET_ID_GND_SHIFT		0x00

/* Bit definitions क्रम USB_ID_INT_EN_LO_CLR */
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_FLOAT			0x10
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_FLOAT_SHIFT		0x04
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_A			0x08
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_B			0x04
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_C			0x02
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_GND			0x01
#घोषणा PALMAS_USB_ID_INT_EN_LO_CLR_ID_GND_SHIFT		0x00

/* Bit definitions क्रम USB_ID_INT_EN_HI_SET */
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_FLOAT			0x10
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_FLOAT_SHIFT		0x04
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_A			0x08
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_B			0x04
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_C			0x02
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_GND			0x01
#घोषणा PALMAS_USB_ID_INT_EN_HI_SET_ID_GND_SHIFT		0x00

/* Bit definitions क्रम USB_ID_INT_EN_HI_CLR */
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_FLOAT			0x10
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_FLOAT_SHIFT		0x04
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_A			0x08
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_A_SHIFT			0x03
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_B			0x04
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_B_SHIFT			0x02
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_C			0x02
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_C_SHIFT			0x01
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_GND			0x01
#घोषणा PALMAS_USB_ID_INT_EN_HI_CLR_ID_GND_SHIFT		0x00

/* Bit definitions क्रम USB_OTG_ADP_CTRL */
#घोषणा PALMAS_USB_OTG_ADP_CTRL_ADP_EN				0x04
#घोषणा PALMAS_USB_OTG_ADP_CTRL_ADP_EN_SHIFT			0x02
#घोषणा PALMAS_USB_OTG_ADP_CTRL_ADP_MODE_MASK			0x03
#घोषणा PALMAS_USB_OTG_ADP_CTRL_ADP_MODE_SHIFT			0x00

/* Bit definitions क्रम USB_OTG_ADP_HIGH */
#घोषणा PALMAS_USB_OTG_ADP_HIGH_T_ADP_HIGH_MASK			0xFF
#घोषणा PALMAS_USB_OTG_ADP_HIGH_T_ADP_HIGH_SHIFT		0x00

/* Bit definitions क्रम USB_OTG_ADP_LOW */
#घोषणा PALMAS_USB_OTG_ADP_LOW_T_ADP_LOW_MASK			0xFF
#घोषणा PALMAS_USB_OTG_ADP_LOW_T_ADP_LOW_SHIFT			0x00

/* Bit definitions क्रम USB_OTG_ADP_RISE */
#घोषणा PALMAS_USB_OTG_ADP_RISE_T_ADP_RISE_MASK			0xFF
#घोषणा PALMAS_USB_OTG_ADP_RISE_T_ADP_RISE_SHIFT		0x00

/* Bit definitions क्रम USB_OTG_REVISION */
#घोषणा PALMAS_USB_OTG_REVISION_OTG_REV				0x01
#घोषणा PALMAS_USB_OTG_REVISION_OTG_REV_SHIFT			0x00

/* Registers क्रम function VIBRATOR */
#घोषणा PALMAS_VIBRA_CTRL					0x00

/* Bit definitions क्रम VIBRA_CTRL */
#घोषणा PALMAS_VIBRA_CTRL_PWM_DUTY_SEL_MASK			0x06
#घोषणा PALMAS_VIBRA_CTRL_PWM_DUTY_SEL_SHIFT			0x01
#घोषणा PALMAS_VIBRA_CTRL_PWM_FREQ_SEL				0x01
#घोषणा PALMAS_VIBRA_CTRL_PWM_FREQ_SEL_SHIFT			0x00

/* Registers क्रम function GPIO */
#घोषणा PALMAS_GPIO_DATA_IN					0x00
#घोषणा PALMAS_GPIO_DATA_सूची					0x01
#घोषणा PALMAS_GPIO_DATA_OUT					0x02
#घोषणा PALMAS_GPIO_DEBOUNCE_EN					0x03
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT				0x04
#घोषणा PALMAS_GPIO_SET_DATA_OUT				0x05
#घोषणा PALMAS_PU_PD_GPIO_CTRL1					0x06
#घोषणा PALMAS_PU_PD_GPIO_CTRL2					0x07
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL				0x08
#घोषणा PALMAS_GPIO_DATA_IN2					0x09
#घोषणा PALMAS_GPIO_DATA_सूची2					0x0A
#घोषणा PALMAS_GPIO_DATA_OUT2					0x0B
#घोषणा PALMAS_GPIO_DEBOUNCE_EN2				0x0C
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT2				0x0D
#घोषणा PALMAS_GPIO_SET_DATA_OUT2				0x0E
#घोषणा PALMAS_PU_PD_GPIO_CTRL3					0x0F
#घोषणा PALMAS_PU_PD_GPIO_CTRL4					0x10
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL2				0x11

/* Bit definitions क्रम GPIO_DATA_IN */
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_7_IN				0x80
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_7_IN_SHIFT			0x07
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_6_IN				0x40
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_6_IN_SHIFT			0x06
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_5_IN				0x20
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_5_IN_SHIFT			0x05
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_4_IN				0x10
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_4_IN_SHIFT			0x04
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_3_IN				0x08
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_3_IN_SHIFT			0x03
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_2_IN				0x04
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_2_IN_SHIFT			0x02
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_1_IN				0x02
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_1_IN_SHIFT			0x01
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_0_IN				0x01
#घोषणा PALMAS_GPIO_DATA_IN_GPIO_0_IN_SHIFT			0x00

/* Bit definitions क्रम GPIO_DATA_सूची */
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_7_सूची				0x80
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_7_सूची_SHIFT			0x07
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_6_सूची				0x40
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_6_सूची_SHIFT			0x06
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_5_सूची				0x20
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_5_सूची_SHIFT			0x05
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_4_सूची				0x10
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_4_सूची_SHIFT			0x04
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_3_सूची				0x08
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_3_सूची_SHIFT			0x03
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_2_सूची				0x04
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_2_सूची_SHIFT			0x02
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_1_सूची				0x02
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_1_सूची_SHIFT			0x01
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_0_सूची				0x01
#घोषणा PALMAS_GPIO_DATA_सूची_GPIO_0_सूची_SHIFT			0x00

/* Bit definitions क्रम GPIO_DATA_OUT */
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_7_OUT				0x80
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_7_OUT_SHIFT			0x07
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_6_OUT				0x40
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_6_OUT_SHIFT			0x06
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_5_OUT				0x20
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_5_OUT_SHIFT			0x05
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_4_OUT				0x10
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_4_OUT_SHIFT			0x04
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_3_OUT				0x08
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_3_OUT_SHIFT			0x03
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_2_OUT				0x04
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_2_OUT_SHIFT			0x02
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_1_OUT				0x02
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_1_OUT_SHIFT			0x01
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_0_OUT				0x01
#घोषणा PALMAS_GPIO_DATA_OUT_GPIO_0_OUT_SHIFT			0x00

/* Bit definitions क्रम GPIO_DEBOUNCE_EN */
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_7_DEBOUNCE_EN		0x80
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_7_DEBOUNCE_EN_SHIFT	0x07
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_6_DEBOUNCE_EN		0x40
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_6_DEBOUNCE_EN_SHIFT	0x06
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_5_DEBOUNCE_EN		0x20
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_5_DEBOUNCE_EN_SHIFT	0x05
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_4_DEBOUNCE_EN		0x10
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_4_DEBOUNCE_EN_SHIFT	0x04
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_3_DEBOUNCE_EN		0x08
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_3_DEBOUNCE_EN_SHIFT	0x03
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_2_DEBOUNCE_EN		0x04
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_2_DEBOUNCE_EN_SHIFT	0x02
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_1_DEBOUNCE_EN		0x02
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_1_DEBOUNCE_EN_SHIFT	0x01
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_0_DEBOUNCE_EN		0x01
#घोषणा PALMAS_GPIO_DEBOUNCE_EN_GPIO_0_DEBOUNCE_EN_SHIFT	0x00

/* Bit definitions क्रम GPIO_CLEAR_DATA_OUT */
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_7_CLEAR_DATA_OUT	0x80
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_7_CLEAR_DATA_OUT_SHIFT	0x07
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_6_CLEAR_DATA_OUT	0x40
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_6_CLEAR_DATA_OUT_SHIFT	0x06
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_5_CLEAR_DATA_OUT	0x20
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_5_CLEAR_DATA_OUT_SHIFT	0x05
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_4_CLEAR_DATA_OUT	0x10
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_4_CLEAR_DATA_OUT_SHIFT	0x04
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_3_CLEAR_DATA_OUT	0x08
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_3_CLEAR_DATA_OUT_SHIFT	0x03
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_2_CLEAR_DATA_OUT	0x04
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_2_CLEAR_DATA_OUT_SHIFT	0x02
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_1_CLEAR_DATA_OUT	0x02
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_1_CLEAR_DATA_OUT_SHIFT	0x01
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_0_CLEAR_DATA_OUT	0x01
#घोषणा PALMAS_GPIO_CLEAR_DATA_OUT_GPIO_0_CLEAR_DATA_OUT_SHIFT	0x00

/* Bit definitions क्रम GPIO_SET_DATA_OUT */
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_7_SET_DATA_OUT		0x80
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_7_SET_DATA_OUT_SHIFT	0x07
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_6_SET_DATA_OUT		0x40
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_6_SET_DATA_OUT_SHIFT	0x06
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_5_SET_DATA_OUT		0x20
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_5_SET_DATA_OUT_SHIFT	0x05
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_4_SET_DATA_OUT		0x10
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_4_SET_DATA_OUT_SHIFT	0x04
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_3_SET_DATA_OUT		0x08
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_3_SET_DATA_OUT_SHIFT	0x03
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_2_SET_DATA_OUT		0x04
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_2_SET_DATA_OUT_SHIFT	0x02
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_1_SET_DATA_OUT		0x02
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_1_SET_DATA_OUT_SHIFT	0x01
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_0_SET_DATA_OUT		0x01
#घोषणा PALMAS_GPIO_SET_DATA_OUT_GPIO_0_SET_DATA_OUT_SHIFT	0x00

/* Bit definitions क्रम PU_PD_GPIO_CTRL1 */
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_3_PD			0x40
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_3_PD_SHIFT			0x06
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_2_PU			0x20
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_2_PU_SHIFT			0x05
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_2_PD			0x10
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_2_PD_SHIFT			0x04
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_1_PU			0x08
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_1_PU_SHIFT			0x03
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_1_PD			0x04
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_1_PD_SHIFT			0x02
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_0_PD			0x01
#घोषणा PALMAS_PU_PD_GPIO_CTRL1_GPIO_0_PD_SHIFT			0x00

/* Bit definitions क्रम PU_PD_GPIO_CTRL2 */
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_7_PD			0x40
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_7_PD_SHIFT			0x06
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_6_PU			0x20
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_6_PU_SHIFT			0x05
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_6_PD			0x10
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_6_PD_SHIFT			0x04
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_5_PU			0x08
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_5_PU_SHIFT			0x03
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_5_PD			0x04
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_5_PD_SHIFT			0x02
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_4_PU			0x02
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_4_PU_SHIFT			0x01
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_4_PD			0x01
#घोषणा PALMAS_PU_PD_GPIO_CTRL2_GPIO_4_PD_SHIFT			0x00

/* Bit definitions क्रम OD_OUTPUT_GPIO_CTRL */
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL_GPIO_5_OD			0x20
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL_GPIO_5_OD_SHIFT		0x05
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL_GPIO_2_OD			0x04
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL_GPIO_2_OD_SHIFT		0x02
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL_GPIO_1_OD			0x02
#घोषणा PALMAS_OD_OUTPUT_GPIO_CTRL_GPIO_1_OD_SHIFT		0x01

/* Registers क्रम function GPADC */
#घोषणा PALMAS_GPADC_CTRL1					0x00
#घोषणा PALMAS_GPADC_CTRL2					0x01
#घोषणा PALMAS_GPADC_RT_CTRL					0x02
#घोषणा PALMAS_GPADC_AUTO_CTRL					0x03
#घोषणा PALMAS_GPADC_STATUS					0x04
#घोषणा PALMAS_GPADC_RT_SELECT					0x05
#घोषणा PALMAS_GPADC_RT_CONV0_LSB				0x06
#घोषणा PALMAS_GPADC_RT_CONV0_MSB				0x07
#घोषणा PALMAS_GPADC_AUTO_SELECT				0x08
#घोषणा PALMAS_GPADC_AUTO_CONV0_LSB				0x09
#घोषणा PALMAS_GPADC_AUTO_CONV0_MSB				0x0A
#घोषणा PALMAS_GPADC_AUTO_CONV1_LSB				0x0B
#घोषणा PALMAS_GPADC_AUTO_CONV1_MSB				0x0C
#घोषणा PALMAS_GPADC_SW_SELECT					0x0D
#घोषणा PALMAS_GPADC_SW_CONV0_LSB				0x0E
#घोषणा PALMAS_GPADC_SW_CONV0_MSB				0x0F
#घोषणा PALMAS_GPADC_THRES_CONV0_LSB				0x10
#घोषणा PALMAS_GPADC_THRES_CONV0_MSB				0x11
#घोषणा PALMAS_GPADC_THRES_CONV1_LSB				0x12
#घोषणा PALMAS_GPADC_THRES_CONV1_MSB				0x13
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN				0x14
#घोषणा PALMAS_GPADC_SMPS_VSEL_MONITORING			0x15

/* Bit definitions क्रम GPADC_CTRL1 */
#घोषणा PALMAS_GPADC_CTRL1_RESERVED_MASK			0xc0
#घोषणा PALMAS_GPADC_CTRL1_RESERVED_SHIFT			0x06
#घोषणा PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_MASK			0x30
#घोषणा PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_SHIFT		0x04
#घोषणा PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_MASK			0x0c
#घोषणा PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_SHIFT		0x02
#घोषणा PALMAS_GPADC_CTRL1_BAT_REMOVAL_DET			0x02
#घोषणा PALMAS_GPADC_CTRL1_BAT_REMOVAL_DET_SHIFT		0x01
#घोषणा PALMAS_GPADC_CTRL1_GPADC_FORCE				0x01
#घोषणा PALMAS_GPADC_CTRL1_GPADC_FORCE_SHIFT			0x00

/* Bit definitions क्रम GPADC_CTRL2 */
#घोषणा PALMAS_GPADC_CTRL2_RESERVED_MASK			0x06
#घोषणा PALMAS_GPADC_CTRL2_RESERVED_SHIFT			0x01

/* Bit definitions क्रम GPADC_RT_CTRL */
#घोषणा PALMAS_GPADC_RT_CTRL_EXTEND_DELAY			0x02
#घोषणा PALMAS_GPADC_RT_CTRL_EXTEND_DELAY_SHIFT			0x01
#घोषणा PALMAS_GPADC_RT_CTRL_START_POLARITY			0x01
#घोषणा PALMAS_GPADC_RT_CTRL_START_POLARITY_SHIFT		0x00

/* Bit definitions क्रम GPADC_AUTO_CTRL */
#घोषणा PALMAS_GPADC_AUTO_CTRL_SHUTDOWN_CONV1			0x80
#घोषणा PALMAS_GPADC_AUTO_CTRL_SHUTDOWN_CONV1_SHIFT		0x07
#घोषणा PALMAS_GPADC_AUTO_CTRL_SHUTDOWN_CONV0			0x40
#घोषणा PALMAS_GPADC_AUTO_CTRL_SHUTDOWN_CONV0_SHIFT		0x06
#घोषणा PALMAS_GPADC_AUTO_CTRL_AUTO_CONV1_EN			0x20
#घोषणा PALMAS_GPADC_AUTO_CTRL_AUTO_CONV1_EN_SHIFT		0x05
#घोषणा PALMAS_GPADC_AUTO_CTRL_AUTO_CONV0_EN			0x10
#घोषणा PALMAS_GPADC_AUTO_CTRL_AUTO_CONV0_EN_SHIFT		0x04
#घोषणा PALMAS_GPADC_AUTO_CTRL_COUNTER_CONV_MASK		0x0F
#घोषणा PALMAS_GPADC_AUTO_CTRL_COUNTER_CONV_SHIFT		0x00

/* Bit definitions क्रम GPADC_STATUS */
#घोषणा PALMAS_GPADC_STATUS_GPADC_AVAILABLE			0x10
#घोषणा PALMAS_GPADC_STATUS_GPADC_AVAILABLE_SHIFT		0x04

/* Bit definitions क्रम GPADC_RT_SELECT */
#घोषणा PALMAS_GPADC_RT_SELECT_RT_CONV_EN			0x80
#घोषणा PALMAS_GPADC_RT_SELECT_RT_CONV_EN_SHIFT			0x07
#घोषणा PALMAS_GPADC_RT_SELECT_RT_CONV0_SEL_MASK		0x0F
#घोषणा PALMAS_GPADC_RT_SELECT_RT_CONV0_SEL_SHIFT		0x00

/* Bit definitions क्रम GPADC_RT_CONV0_LSB */
#घोषणा PALMAS_GPADC_RT_CONV0_LSB_RT_CONV0_LSB_MASK		0xFF
#घोषणा PALMAS_GPADC_RT_CONV0_LSB_RT_CONV0_LSB_SHIFT		0x00

/* Bit definitions क्रम GPADC_RT_CONV0_MSB */
#घोषणा PALMAS_GPADC_RT_CONV0_MSB_RT_CONV0_MSB_MASK		0x0F
#घोषणा PALMAS_GPADC_RT_CONV0_MSB_RT_CONV0_MSB_SHIFT		0x00

/* Bit definitions क्रम GPADC_AUTO_SELECT */
#घोषणा PALMAS_GPADC_AUTO_SELECT_AUTO_CONV1_SEL_MASK		0xF0
#घोषणा PALMAS_GPADC_AUTO_SELECT_AUTO_CONV1_SEL_SHIFT		0x04
#घोषणा PALMAS_GPADC_AUTO_SELECT_AUTO_CONV0_SEL_MASK		0x0F
#घोषणा PALMAS_GPADC_AUTO_SELECT_AUTO_CONV0_SEL_SHIFT		0x00

/* Bit definitions क्रम GPADC_AUTO_CONV0_LSB */
#घोषणा PALMAS_GPADC_AUTO_CONV0_LSB_AUTO_CONV0_LSB_MASK		0xFF
#घोषणा PALMAS_GPADC_AUTO_CONV0_LSB_AUTO_CONV0_LSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_AUTO_CONV0_MSB */
#घोषणा PALMAS_GPADC_AUTO_CONV0_MSB_AUTO_CONV0_MSB_MASK		0x0F
#घोषणा PALMAS_GPADC_AUTO_CONV0_MSB_AUTO_CONV0_MSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_AUTO_CONV1_LSB */
#घोषणा PALMAS_GPADC_AUTO_CONV1_LSB_AUTO_CONV1_LSB_MASK		0xFF
#घोषणा PALMAS_GPADC_AUTO_CONV1_LSB_AUTO_CONV1_LSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_AUTO_CONV1_MSB */
#घोषणा PALMAS_GPADC_AUTO_CONV1_MSB_AUTO_CONV1_MSB_MASK		0x0F
#घोषणा PALMAS_GPADC_AUTO_CONV1_MSB_AUTO_CONV1_MSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_SW_SELECT */
#घोषणा PALMAS_GPADC_SW_SELECT_SW_CONV_EN			0x80
#घोषणा PALMAS_GPADC_SW_SELECT_SW_CONV_EN_SHIFT			0x07
#घोषणा PALMAS_GPADC_SW_SELECT_SW_START_CONV0			0x10
#घोषणा PALMAS_GPADC_SW_SELECT_SW_START_CONV0_SHIFT		0x04
#घोषणा PALMAS_GPADC_SW_SELECT_SW_CONV0_SEL_MASK		0x0F
#घोषणा PALMAS_GPADC_SW_SELECT_SW_CONV0_SEL_SHIFT		0x00

/* Bit definitions क्रम GPADC_SW_CONV0_LSB */
#घोषणा PALMAS_GPADC_SW_CONV0_LSB_SW_CONV0_LSB_MASK		0xFF
#घोषणा PALMAS_GPADC_SW_CONV0_LSB_SW_CONV0_LSB_SHIFT		0x00

/* Bit definitions क्रम GPADC_SW_CONV0_MSB */
#घोषणा PALMAS_GPADC_SW_CONV0_MSB_SW_CONV0_MSB_MASK		0x0F
#घोषणा PALMAS_GPADC_SW_CONV0_MSB_SW_CONV0_MSB_SHIFT		0x00

/* Bit definitions क्रम GPADC_THRES_CONV0_LSB */
#घोषणा PALMAS_GPADC_THRES_CONV0_LSB_THRES_CONV0_LSB_MASK	0xFF
#घोषणा PALMAS_GPADC_THRES_CONV0_LSB_THRES_CONV0_LSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_THRES_CONV0_MSB */
#घोषणा PALMAS_GPADC_THRES_CONV0_MSB_THRES_CONV0_POL		0x80
#घोषणा PALMAS_GPADC_THRES_CONV0_MSB_THRES_CONV0_POL_SHIFT	0x07
#घोषणा PALMAS_GPADC_THRES_CONV0_MSB_THRES_CONV0_MSB_MASK	0x0F
#घोषणा PALMAS_GPADC_THRES_CONV0_MSB_THRES_CONV0_MSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_THRES_CONV1_LSB */
#घोषणा PALMAS_GPADC_THRES_CONV1_LSB_THRES_CONV1_LSB_MASK	0xFF
#घोषणा PALMAS_GPADC_THRES_CONV1_LSB_THRES_CONV1_LSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_THRES_CONV1_MSB */
#घोषणा PALMAS_GPADC_THRES_CONV1_MSB_THRES_CONV1_POL		0x80
#घोषणा PALMAS_GPADC_THRES_CONV1_MSB_THRES_CONV1_POL_SHIFT	0x07
#घोषणा PALMAS_GPADC_THRES_CONV1_MSB_THRES_CONV1_MSB_MASK	0x0F
#घोषणा PALMAS_GPADC_THRES_CONV1_MSB_THRES_CONV1_MSB_SHIFT	0x00

/* Bit definitions क्रम GPADC_SMPS_ILMONITOR_EN */
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN_SMPS_ILMON_EN		0x20
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN_SMPS_ILMON_EN_SHIFT	0x05
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN_SMPS_ILMON_REXT		0x10
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN_SMPS_ILMON_REXT_SHIFT	0x04
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN_SMPS_ILMON_SEL_MASK	0x0F
#घोषणा PALMAS_GPADC_SMPS_ILMONITOR_EN_SMPS_ILMON_SEL_SHIFT	0x00

/* Bit definitions क्रम GPADC_SMPS_VSEL_MONITORING */
#घोषणा PALMAS_GPADC_SMPS_VSEL_MONITORING_ACTIVE_PHASE		0x80
#घोषणा PALMAS_GPADC_SMPS_VSEL_MONITORING_ACTIVE_PHASE_SHIFT	0x07
#घोषणा PALMAS_GPADC_SMPS_VSEL_MONITORING_SMPS_VSEL_MONITORING_MASK	0x7F
#घोषणा PALMAS_GPADC_SMPS_VSEL_MONITORING_SMPS_VSEL_MONITORING_SHIFT	0x00

/* Registers क्रम function GPADC */
#घोषणा PALMAS_GPADC_TRIM1					0x00
#घोषणा PALMAS_GPADC_TRIM2					0x01
#घोषणा PALMAS_GPADC_TRIM3					0x02
#घोषणा PALMAS_GPADC_TRIM4					0x03
#घोषणा PALMAS_GPADC_TRIM5					0x04
#घोषणा PALMAS_GPADC_TRIM6					0x05
#घोषणा PALMAS_GPADC_TRIM7					0x06
#घोषणा PALMAS_GPADC_TRIM8					0x07
#घोषणा PALMAS_GPADC_TRIM9					0x08
#घोषणा PALMAS_GPADC_TRIM10					0x09
#घोषणा PALMAS_GPADC_TRIM11					0x0A
#घोषणा PALMAS_GPADC_TRIM12					0x0B
#घोषणा PALMAS_GPADC_TRIM13					0x0C
#घोषणा PALMAS_GPADC_TRIM14					0x0D
#घोषणा PALMAS_GPADC_TRIM15					0x0E
#घोषणा PALMAS_GPADC_TRIM16					0x0F

/* TPS659038 regen2_ctrl offset iss dअगरferent from palmas */
#घोषणा TPS659038_REGEN2_CTRL					0x12

/* TPS65917 Interrupt रेजिस्टरs */

/* Registers क्रम function INTERRUPT */
#घोषणा TPS65917_INT1_STATUS					0x00
#घोषणा TPS65917_INT1_MASK					0x01
#घोषणा TPS65917_INT1_LINE_STATE				0x02
#घोषणा TPS65917_INT2_STATUS					0x05
#घोषणा TPS65917_INT2_MASK					0x06
#घोषणा TPS65917_INT2_LINE_STATE				0x07
#घोषणा TPS65917_INT3_STATUS					0x0A
#घोषणा TPS65917_INT3_MASK					0x0B
#घोषणा TPS65917_INT3_LINE_STATE				0x0C
#घोषणा TPS65917_INT4_STATUS					0x0F
#घोषणा TPS65917_INT4_MASK					0x10
#घोषणा TPS65917_INT4_LINE_STATE				0x11
#घोषणा TPS65917_INT4_EDGE_DETECT1				0x12
#घोषणा TPS65917_INT4_EDGE_DETECT2				0x13
#घोषणा TPS65917_INT_CTRL					0x14

/* Bit definitions क्रम INT1_STATUS */
#घोषणा TPS65917_INT1_STATUS_VSYS_MON				0x40
#घोषणा TPS65917_INT1_STATUS_VSYS_MON_SHIFT			0x06
#घोषणा TPS65917_INT1_STATUS_HOTDIE				0x20
#घोषणा TPS65917_INT1_STATUS_HOTDIE_SHIFT			0x05
#घोषणा TPS65917_INT1_STATUS_PWRDOWN				0x10
#घोषणा TPS65917_INT1_STATUS_PWRDOWN_SHIFT			0x04
#घोषणा TPS65917_INT1_STATUS_LONG_PRESS_KEY			0x04
#घोषणा TPS65917_INT1_STATUS_LONG_PRESS_KEY_SHIFT		0x02
#घोषणा TPS65917_INT1_STATUS_PWRON				0x02
#घोषणा TPS65917_INT1_STATUS_PWRON_SHIFT			0x01

/* Bit definitions क्रम INT1_MASK */
#घोषणा TPS65917_INT1_MASK_VSYS_MON				0x40
#घोषणा TPS65917_INT1_MASK_VSYS_MON_SHIFT			0x06
#घोषणा TPS65917_INT1_MASK_HOTDIE				0x20
#घोषणा TPS65917_INT1_MASK_HOTDIE_SHIFT			0x05
#घोषणा TPS65917_INT1_MASK_PWRDOWN				0x10
#घोषणा TPS65917_INT1_MASK_PWRDOWN_SHIFT			0x04
#घोषणा TPS65917_INT1_MASK_LONG_PRESS_KEY			0x04
#घोषणा TPS65917_INT1_MASK_LONG_PRESS_KEY_SHIFT		0x02
#घोषणा TPS65917_INT1_MASK_PWRON				0x02
#घोषणा TPS65917_INT1_MASK_PWRON_SHIFT				0x01

/* Bit definitions क्रम INT1_LINE_STATE */
#घोषणा TPS65917_INT1_LINE_STATE_VSYS_MON			0x40
#घोषणा TPS65917_INT1_LINE_STATE_VSYS_MON_SHIFT		0x06
#घोषणा TPS65917_INT1_LINE_STATE_HOTDIE			0x20
#घोषणा TPS65917_INT1_LINE_STATE_HOTDIE_SHIFT			0x05
#घोषणा TPS65917_INT1_LINE_STATE_PWRDOWN			0x10
#घोषणा TPS65917_INT1_LINE_STATE_PWRDOWN_SHIFT			0x04
#घोषणा TPS65917_INT1_LINE_STATE_LONG_PRESS_KEY		0x04
#घोषणा TPS65917_INT1_LINE_STATE_LONG_PRESS_KEY_SHIFT		0x02
#घोषणा TPS65917_INT1_LINE_STATE_PWRON				0x02
#घोषणा TPS65917_INT1_LINE_STATE_PWRON_SHIFT			0x01

/* Bit definitions क्रम INT2_STATUS */
#घोषणा TPS65917_INT2_STATUS_SHORT				0x40
#घोषणा TPS65917_INT2_STATUS_SHORT_SHIFT			0x06
#घोषणा TPS65917_INT2_STATUS_FSD				0x20
#घोषणा TPS65917_INT2_STATUS_FSD_SHIFT				0x05
#घोषणा TPS65917_INT2_STATUS_RESET_IN				0x10
#घोषणा TPS65917_INT2_STATUS_RESET_IN_SHIFT			0x04
#घोषणा TPS65917_INT2_STATUS_WDT				0x04
#घोषणा TPS65917_INT2_STATUS_WDT_SHIFT				0x02
#घोषणा TPS65917_INT2_STATUS_OTP_ERROR				0x02
#घोषणा TPS65917_INT2_STATUS_OTP_ERROR_SHIFT			0x01

/* Bit definitions क्रम INT2_MASK */
#घोषणा TPS65917_INT2_MASK_SHORT				0x40
#घोषणा TPS65917_INT2_MASK_SHORT_SHIFT				0x06
#घोषणा TPS65917_INT2_MASK_FSD					0x20
#घोषणा TPS65917_INT2_MASK_FSD_SHIFT				0x05
#घोषणा TPS65917_INT2_MASK_RESET_IN				0x10
#घोषणा TPS65917_INT2_MASK_RESET_IN_SHIFT			0x04
#घोषणा TPS65917_INT2_MASK_WDT					0x04
#घोषणा TPS65917_INT2_MASK_WDT_SHIFT				0x02
#घोषणा TPS65917_INT2_MASK_OTP_ERROR_TIMER			0x02
#घोषणा TPS65917_INT2_MASK_OTP_ERROR_SHIFT			0x01

/* Bit definitions क्रम INT2_LINE_STATE */
#घोषणा TPS65917_INT2_LINE_STATE_SHORT				0x40
#घोषणा TPS65917_INT2_LINE_STATE_SHORT_SHIFT			0x06
#घोषणा TPS65917_INT2_LINE_STATE_FSD				0x20
#घोषणा TPS65917_INT2_LINE_STATE_FSD_SHIFT			0x05
#घोषणा TPS65917_INT2_LINE_STATE_RESET_IN			0x10
#घोषणा TPS65917_INT2_LINE_STATE_RESET_IN_SHIFT		0x04
#घोषणा TPS65917_INT2_LINE_STATE_WDT				0x04
#घोषणा TPS65917_INT2_LINE_STATE_WDT_SHIFT			0x02
#घोषणा TPS65917_INT2_LINE_STATE_OTP_ERROR			0x02
#घोषणा TPS65917_INT2_LINE_STATE_OTP_ERROR_SHIFT		0x01

/* Bit definitions क्रम INT3_STATUS */
#घोषणा TPS65917_INT3_STATUS_VBUS				0x80
#घोषणा TPS65917_INT3_STATUS_VBUS_SHIFT			0x07
#घोषणा TPS65917_INT3_STATUS_GPADC_EOC_SW			0x04
#घोषणा TPS65917_INT3_STATUS_GPADC_EOC_SW_SHIFT		0x02
#घोषणा TPS65917_INT3_STATUS_GPADC_AUTO_1			0x02
#घोषणा TPS65917_INT3_STATUS_GPADC_AUTO_1_SHIFT		0x01
#घोषणा TPS65917_INT3_STATUS_GPADC_AUTO_0			0x01
#घोषणा TPS65917_INT3_STATUS_GPADC_AUTO_0_SHIFT		0x00

/* Bit definitions क्रम INT3_MASK */
#घोषणा TPS65917_INT3_MASK_VBUS				0x80
#घोषणा TPS65917_INT3_MASK_VBUS_SHIFT				0x07
#घोषणा TPS65917_INT3_MASK_GPADC_EOC_SW			0x04
#घोषणा TPS65917_INT3_MASK_GPADC_EOC_SW_SHIFT			0x02
#घोषणा TPS65917_INT3_MASK_GPADC_AUTO_1			0x02
#घोषणा TPS65917_INT3_MASK_GPADC_AUTO_1_SHIFT			0x01
#घोषणा TPS65917_INT3_MASK_GPADC_AUTO_0			0x01
#घोषणा TPS65917_INT3_MASK_GPADC_AUTO_0_SHIFT			0x00

/* Bit definitions क्रम INT3_LINE_STATE */
#घोषणा TPS65917_INT3_LINE_STATE_VBUS				0x80
#घोषणा TPS65917_INT3_LINE_STATE_VBUS_SHIFT			0x07
#घोषणा TPS65917_INT3_LINE_STATE_GPADC_EOC_SW			0x04
#घोषणा TPS65917_INT3_LINE_STATE_GPADC_EOC_SW_SHIFT		0x02
#घोषणा TPS65917_INT3_LINE_STATE_GPADC_AUTO_1			0x02
#घोषणा TPS65917_INT3_LINE_STATE_GPADC_AUTO_1_SHIFT		0x01
#घोषणा TPS65917_INT3_LINE_STATE_GPADC_AUTO_0			0x01
#घोषणा TPS65917_INT3_LINE_STATE_GPADC_AUTO_0_SHIFT		0x00

/* Bit definitions क्रम INT4_STATUS */
#घोषणा TPS65917_INT4_STATUS_GPIO_6				0x40
#घोषणा TPS65917_INT4_STATUS_GPIO_6_SHIFT			0x06
#घोषणा TPS65917_INT4_STATUS_GPIO_5				0x20
#घोषणा TPS65917_INT4_STATUS_GPIO_5_SHIFT			0x05
#घोषणा TPS65917_INT4_STATUS_GPIO_4				0x10
#घोषणा TPS65917_INT4_STATUS_GPIO_4_SHIFT			0x04
#घोषणा TPS65917_INT4_STATUS_GPIO_3				0x08
#घोषणा TPS65917_INT4_STATUS_GPIO_3_SHIFT			0x03
#घोषणा TPS65917_INT4_STATUS_GPIO_2				0x04
#घोषणा TPS65917_INT4_STATUS_GPIO_2_SHIFT			0x02
#घोषणा TPS65917_INT4_STATUS_GPIO_1				0x02
#घोषणा TPS65917_INT4_STATUS_GPIO_1_SHIFT			0x01
#घोषणा TPS65917_INT4_STATUS_GPIO_0				0x01
#घोषणा TPS65917_INT4_STATUS_GPIO_0_SHIFT			0x00

/* Bit definitions क्रम INT4_MASK */
#घोषणा TPS65917_INT4_MASK_GPIO_6				0x40
#घोषणा TPS65917_INT4_MASK_GPIO_6_SHIFT			0x06
#घोषणा TPS65917_INT4_MASK_GPIO_5				0x20
#घोषणा TPS65917_INT4_MASK_GPIO_5_SHIFT			0x05
#घोषणा TPS65917_INT4_MASK_GPIO_4				0x10
#घोषणा TPS65917_INT4_MASK_GPIO_4_SHIFT			0x04
#घोषणा TPS65917_INT4_MASK_GPIO_3				0x08
#घोषणा TPS65917_INT4_MASK_GPIO_3_SHIFT			0x03
#घोषणा TPS65917_INT4_MASK_GPIO_2				0x04
#घोषणा TPS65917_INT4_MASK_GPIO_2_SHIFT			0x02
#घोषणा TPS65917_INT4_MASK_GPIO_1				0x02
#घोषणा TPS65917_INT4_MASK_GPIO_1_SHIFT			0x01
#घोषणा TPS65917_INT4_MASK_GPIO_0				0x01
#घोषणा TPS65917_INT4_MASK_GPIO_0_SHIFT			0x00

/* Bit definitions क्रम INT4_LINE_STATE */
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_6			0x40
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_6_SHIFT			0x06
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_5			0x20
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_5_SHIFT			0x05
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_4			0x10
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_4_SHIFT			0x04
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_3			0x08
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_3_SHIFT			0x03
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_2			0x04
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_2_SHIFT			0x02
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_1			0x02
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_1_SHIFT			0x01
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_0			0x01
#घोषणा TPS65917_INT4_LINE_STATE_GPIO_0_SHIFT			0x00

/* Bit definitions क्रम INT4_EDGE_DETECT1 */
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_3_RISING		0x80
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_3_RISING_SHIFT		0x07
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_3_FALLING		0x40
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_3_FALLING_SHIFT	0x06
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_2_RISING		0x20
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_2_RISING_SHIFT		0x05
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_2_FALLING		0x10
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_2_FALLING_SHIFT	0x04
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_1_RISING		0x08
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_1_RISING_SHIFT		0x03
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_1_FALLING		0x04
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_1_FALLING_SHIFT	0x02
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_0_RISING		0x02
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_0_RISING_SHIFT		0x01
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_0_FALLING		0x01
#घोषणा TPS65917_INT4_EDGE_DETECT1_GPIO_0_FALLING_SHIFT	0x00

/* Bit definitions क्रम INT4_EDGE_DETECT2 */
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_6_RISING		0x20
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_6_RISING_SHIFT		0x05
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_6_FALLING		0x10
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_6_FALLING_SHIFT	0x04
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_5_RISING		0x08
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_5_RISING_SHIFT		0x03
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_5_FALLING		0x04
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_5_FALLING_SHIFT	0x02
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_4_RISING		0x02
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_4_RISING_SHIFT		0x01
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_4_FALLING		0x01
#घोषणा TPS65917_INT4_EDGE_DETECT2_GPIO_4_FALLING_SHIFT	0x00

/* Bit definitions क्रम INT_CTRL */
#घोषणा TPS65917_INT_CTRL_INT_PENDING				0x04
#घोषणा TPS65917_INT_CTRL_INT_PENDING_SHIFT			0x02
#घोषणा TPS65917_INT_CTRL_INT_CLEAR				0x01
#घोषणा TPS65917_INT_CTRL_INT_CLEAR_SHIFT			0x00

/* TPS65917 SMPS Registers */

/* Registers क्रम function SMPS */
#घोषणा TPS65917_SMPS1_CTRL					0x00
#घोषणा TPS65917_SMPS1_FORCE					0x02
#घोषणा TPS65917_SMPS1_VOLTAGE					0x03
#घोषणा TPS65917_SMPS2_CTRL					0x04
#घोषणा TPS65917_SMPS2_FORCE					0x06
#घोषणा TPS65917_SMPS2_VOLTAGE					0x07
#घोषणा TPS65917_SMPS3_CTRL					0x0C
#घोषणा TPS65917_SMPS3_FORCE					0x0E
#घोषणा TPS65917_SMPS3_VOLTAGE					0x0F
#घोषणा TPS65917_SMPS4_CTRL					0x10
#घोषणा TPS65917_SMPS4_VOLTAGE					0x13
#घोषणा TPS65917_SMPS5_CTRL					0x18
#घोषणा TPS65917_SMPS5_VOLTAGE					0x1B
#घोषणा TPS65917_SMPS_CTRL					0x24
#घोषणा TPS65917_SMPS_PD_CTRL					0x25
#घोषणा TPS65917_SMPS_THERMAL_EN				0x27
#घोषणा TPS65917_SMPS_THERMAL_STATUS				0x28
#घोषणा TPS65917_SMPS_SHORT_STATUS				0x29
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN		0x2A
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1				0x2B
#घोषणा TPS65917_SMPS_POWERGOOD_MASK2				0x2C

/* Bit definitions क्रम SMPS1_CTRL */
#घोषणा TPS65917_SMPS1_CTRL_WR_S				0x80
#घोषणा TPS65917_SMPS1_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_SMPS1_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा TPS65917_SMPS1_CTRL_ROOF_FLOOR_EN_SHIFT		0x06
#घोषणा TPS65917_SMPS1_CTRL_STATUS_MASK			0x30
#घोषणा TPS65917_SMPS1_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_SMPS1_CTRL_MODE_SLEEP_MASK			0x0C
#घोषणा TPS65917_SMPS1_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_SMPS1_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा TPS65917_SMPS1_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS1_FORCE */
#घोषणा TPS65917_SMPS1_FORCE_CMD				0x80
#घोषणा TPS65917_SMPS1_FORCE_CMD_SHIFT				0x07
#घोषणा TPS65917_SMPS1_FORCE_VSEL_MASK				0x7F
#घोषणा TPS65917_SMPS1_FORCE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS1_VOLTAGE */
#घोषणा TPS65917_SMPS1_VOLTAGE_RANGE				0x80
#घोषणा TPS65917_SMPS1_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा TPS65917_SMPS1_VOLTAGE_VSEL_MASK			0x7F
#घोषणा TPS65917_SMPS1_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS2_CTRL */
#घोषणा TPS65917_SMPS2_CTRL_WR_S				0x80
#घोषणा TPS65917_SMPS2_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_SMPS2_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा TPS65917_SMPS2_CTRL_ROOF_FLOOR_EN_SHIFT		0x06
#घोषणा TPS65917_SMPS2_CTRL_STATUS_MASK			0x30
#घोषणा TPS65917_SMPS2_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_SMPS2_CTRL_MODE_SLEEP_MASK			0x0C
#घोषणा TPS65917_SMPS2_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_SMPS2_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा TPS65917_SMPS2_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS2_FORCE */
#घोषणा TPS65917_SMPS2_FORCE_CMD				0x80
#घोषणा TPS65917_SMPS2_FORCE_CMD_SHIFT				0x07
#घोषणा TPS65917_SMPS2_FORCE_VSEL_MASK				0x7F
#घोषणा TPS65917_SMPS2_FORCE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS2_VOLTAGE */
#घोषणा TPS65917_SMPS2_VOLTAGE_RANGE				0x80
#घोषणा TPS65917_SMPS2_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा TPS65917_SMPS2_VOLTAGE_VSEL_MASK			0x7F
#घोषणा TPS65917_SMPS2_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS3_CTRL */
#घोषणा TPS65917_SMPS3_CTRL_WR_S				0x80
#घोषणा TPS65917_SMPS3_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_SMPS3_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा TPS65917_SMPS3_CTRL_ROOF_FLOOR_EN_SHIFT		0x06
#घोषणा TPS65917_SMPS3_CTRL_STATUS_MASK			0x30
#घोषणा TPS65917_SMPS3_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_SMPS3_CTRL_MODE_SLEEP_MASK			0x0C
#घोषणा TPS65917_SMPS3_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_SMPS3_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा TPS65917_SMPS3_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS3_FORCE */
#घोषणा TPS65917_SMPS3_FORCE_CMD				0x80
#घोषणा TPS65917_SMPS3_FORCE_CMD_SHIFT				0x07
#घोषणा TPS65917_SMPS3_FORCE_VSEL_MASK				0x7F
#घोषणा TPS65917_SMPS3_FORCE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS3_VOLTAGE */
#घोषणा TPS65917_SMPS3_VOLTAGE_RANGE				0x80
#घोषणा TPS65917_SMPS3_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा TPS65917_SMPS3_VOLTAGE_VSEL_MASK			0x7F
#घोषणा TPS65917_SMPS3_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS4_CTRL */
#घोषणा TPS65917_SMPS4_CTRL_WR_S				0x80
#घोषणा TPS65917_SMPS4_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_SMPS4_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा TPS65917_SMPS4_CTRL_ROOF_FLOOR_EN_SHIFT		0x06
#घोषणा TPS65917_SMPS4_CTRL_STATUS_MASK			0x30
#घोषणा TPS65917_SMPS4_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_SMPS4_CTRL_MODE_SLEEP_MASK			0x0C
#घोषणा TPS65917_SMPS4_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_SMPS4_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा TPS65917_SMPS4_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS4_VOLTAGE */
#घोषणा TPS65917_SMPS4_VOLTAGE_RANGE				0x80
#घोषणा TPS65917_SMPS4_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा TPS65917_SMPS4_VOLTAGE_VSEL_MASK			0x7F
#घोषणा TPS65917_SMPS4_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS5_CTRL */
#घोषणा TPS65917_SMPS5_CTRL_WR_S				0x80
#घोषणा TPS65917_SMPS5_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_SMPS5_CTRL_ROOF_FLOOR_EN			0x40
#घोषणा TPS65917_SMPS5_CTRL_ROOF_FLOOR_EN_SHIFT		0x06
#घोषणा TPS65917_SMPS5_CTRL_STATUS_MASK			0x30
#घोषणा TPS65917_SMPS5_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_SMPS5_CTRL_MODE_SLEEP_MASK			0x0C
#घोषणा TPS65917_SMPS5_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_SMPS5_CTRL_MODE_ACTIVE_MASK			0x03
#घोषणा TPS65917_SMPS5_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम SMPS5_VOLTAGE */
#घोषणा TPS65917_SMPS5_VOLTAGE_RANGE				0x80
#घोषणा TPS65917_SMPS5_VOLTAGE_RANGE_SHIFT			0x07
#घोषणा TPS65917_SMPS5_VOLTAGE_VSEL_MASK			0x7F
#घोषणा TPS65917_SMPS5_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम SMPS_CTRL */
#घोषणा TPS65917_SMPS_CTRL_SMPS1_SMPS12_EN			0x10
#घोषणा TPS65917_SMPS_CTRL_SMPS1_SMPS12_EN_SHIFT		0x04
#घोषणा TPS65917_SMPS_CTRL_SMPS12_PHASE_CTRL			0x03
#घोषणा TPS65917_SMPS_CTRL_SMPS12_PHASE_CTRL_SHIFT		0x00

/* Bit definitions क्रम SMPS_PD_CTRL */
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS5				0x40
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS5_SHIFT			0x06
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS4				0x10
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS4_SHIFT			0x04
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS3				0x08
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS3_SHIFT			0x03
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS2				0x02
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS2_SHIFT			0x01
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS1				0x01
#घोषणा TPS65917_SMPS_PD_CTRL_SMPS1_SHIFT			0x00

/* Bit definitions क्रम SMPS_THERMAL_EN */
#घोषणा TPS65917_SMPS_THERMAL_EN_SMPS5				0x40
#घोषणा TPS65917_SMPS_THERMAL_EN_SMPS5_SHIFT			0x06
#घोषणा TPS65917_SMPS_THERMAL_EN_SMPS3				0x08
#घोषणा TPS65917_SMPS_THERMAL_EN_SMPS3_SHIFT			0x03
#घोषणा TPS65917_SMPS_THERMAL_EN_SMPS12			0x01
#घोषणा TPS65917_SMPS_THERMAL_EN_SMPS12_SHIFT			0x00

/* Bit definitions क्रम SMPS_THERMAL_STATUS */
#घोषणा TPS65917_SMPS_THERMAL_STATUS_SMPS5			0x40
#घोषणा TPS65917_SMPS_THERMAL_STATUS_SMPS5_SHIFT		0x06
#घोषणा TPS65917_SMPS_THERMAL_STATUS_SMPS3			0x08
#घोषणा TPS65917_SMPS_THERMAL_STATUS_SMPS3_SHIFT		0x03
#घोषणा TPS65917_SMPS_THERMAL_STATUS_SMPS12			0x01
#घोषणा TPS65917_SMPS_THERMAL_STATUS_SMPS12_SHIFT		0x00

/* Bit definitions क्रम SMPS_SHORT_STATUS */
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS5			0x40
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS5_SHIFT			0x06
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS4			0x10
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS4_SHIFT			0x04
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS3			0x08
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS3_SHIFT			0x03
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS2			0x02
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS2_SHIFT			0x01
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS1			0x01
#घोषणा TPS65917_SMPS_SHORT_STATUS_SMPS1_SHIFT			0x00

/* Bit definitions क्रम SMPS_NEGATIVE_CURRENT_LIMIT_EN */
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS5		0x40
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS5_SHIFT	0x06
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS4		0x10
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS4_SHIFT	0x04
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS3		0x08
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS3_SHIFT	0x03
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS2		0x02
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS2_SHIFT	0x01
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS1		0x01
#घोषणा TPS65917_SMPS_NEGATIVE_CURRENT_LIMIT_EN_SMPS1_SHIFT	0x00

/* Bit definitions क्रम SMPS_POWERGOOD_MASK1 */
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS5			0x40
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS5_SHIFT		0x06
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS4			0x10
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS4_SHIFT		0x04
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS3			0x08
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS3_SHIFT		0x03
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS2			0x02
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS2_SHIFT		0x01
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS1			0x01
#घोषणा TPS65917_SMPS_POWERGOOD_MASK1_SMPS1_SHIFT		0x00

/* Bit definitions क्रम SMPS_POWERGOOD_MASK2 */
#घोषणा TPS65917_SMPS_POWERGOOD_MASK2_POWERGOOD_TYPE_SELECT		0x80
#घोषणा TPS65917_SMPS_POWERGOOD_MASK2_POWERGOOD_TYPE_SELECT_SHIFT	0x07
#घोषणा TPS65917_SMPS_POWERGOOD_MASK2_OVC_ALARM_SHIFT			0x10
#घोषणा TPS65917_SMPS_POWERGOOD_MASK2_OVC_ALARM			0x04

/* Bit definitions क्रम SMPS_PLL_CTRL */

#घोषणा TPS65917_SMPS_PLL_CTRL_PLL_EN_PLL_BYPASS_SHIFT		0x08
#घोषणा TPS65917_SMPS_PLL_CTRL_PLL_PLL_EN_BYPASS		0x03
#घोषणा TPS65917_SMPS_PLL_CTRL_PLL_PLL_BYPASS_CLK_SHIFT	0x04
#घोषणा TPS65917_SMPS_PLL_CTRL_PLL_PLL_BYPASS_CLK		0x02

/* Registers क्रम function LDO */
#घोषणा TPS65917_LDO1_CTRL					0x00
#घोषणा TPS65917_LDO1_VOLTAGE					0x01
#घोषणा TPS65917_LDO2_CTRL					0x02
#घोषणा TPS65917_LDO2_VOLTAGE					0x03
#घोषणा TPS65917_LDO3_CTRL					0x04
#घोषणा TPS65917_LDO3_VOLTAGE					0x05
#घोषणा TPS65917_LDO4_CTRL					0x0E
#घोषणा TPS65917_LDO4_VOLTAGE					0x0F
#घोषणा TPS65917_LDO5_CTRL					0x12
#घोषणा TPS65917_LDO5_VOLTAGE					0x13
#घोषणा TPS65917_LDO_PD_CTRL1					0x1B
#घोषणा TPS65917_LDO_PD_CTRL2					0x1C
#घोषणा TPS65917_LDO_SHORT_STATUS1				0x1D
#घोषणा TPS65917_LDO_SHORT_STATUS2				0x1E
#घोषणा TPS65917_LDO_PD_CTRL3					0x2D
#घोषणा TPS65917_LDO_SHORT_STATUS3				0x2E

/* Bit definitions क्रम LDO1_CTRL */
#घोषणा TPS65917_LDO1_CTRL_WR_S				0x80
#घोषणा TPS65917_LDO1_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_LDO1_CTRL_BYPASS_EN				0x40
#घोषणा TPS65917_LDO1_CTRL_BYPASS_EN_SHIFT			0x06
#घोषणा TPS65917_LDO1_CTRL_STATUS				0x10
#घोषणा TPS65917_LDO1_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_LDO1_CTRL_MODE_SLEEP				0x04
#घोषणा TPS65917_LDO1_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_LDO1_CTRL_MODE_ACTIVE				0x01
#घोषणा TPS65917_LDO1_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO1_VOLTAGE */
#घोषणा TPS65917_LDO1_VOLTAGE_VSEL_MASK			0x2F
#घोषणा TPS65917_LDO1_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम LDO2_CTRL */
#घोषणा TPS65917_LDO2_CTRL_WR_S				0x80
#घोषणा TPS65917_LDO2_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_LDO2_CTRL_BYPASS_EN				0x40
#घोषणा TPS65917_LDO2_CTRL_BYPASS_EN_SHIFT			0x06
#घोषणा TPS65917_LDO2_CTRL_STATUS				0x10
#घोषणा TPS65917_LDO2_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_LDO2_CTRL_MODE_SLEEP				0x04
#घोषणा TPS65917_LDO2_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_LDO2_CTRL_MODE_ACTIVE				0x01
#घोषणा TPS65917_LDO2_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO2_VOLTAGE */
#घोषणा TPS65917_LDO2_VOLTAGE_VSEL_MASK			0x2F
#घोषणा TPS65917_LDO2_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम LDO3_CTRL */
#घोषणा TPS65917_LDO3_CTRL_WR_S				0x80
#घोषणा TPS65917_LDO3_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_LDO3_CTRL_STATUS				0x10
#घोषणा TPS65917_LDO3_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_LDO3_CTRL_MODE_SLEEP				0x04
#घोषणा TPS65917_LDO3_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_LDO3_CTRL_MODE_ACTIVE				0x01
#घोषणा TPS65917_LDO3_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO3_VOLTAGE */
#घोषणा TPS65917_LDO3_VOLTAGE_VSEL_MASK			0x2F
#घोषणा TPS65917_LDO3_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम LDO4_CTRL */
#घोषणा TPS65917_LDO4_CTRL_WR_S				0x80
#घोषणा TPS65917_LDO4_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_LDO4_CTRL_STATUS				0x10
#घोषणा TPS65917_LDO4_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_LDO4_CTRL_MODE_SLEEP				0x04
#घोषणा TPS65917_LDO4_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_LDO4_CTRL_MODE_ACTIVE				0x01
#घोषणा TPS65917_LDO4_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO4_VOLTAGE */
#घोषणा TPS65917_LDO4_VOLTAGE_VSEL_MASK			0x2F
#घोषणा TPS65917_LDO4_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम LDO5_CTRL */
#घोषणा TPS65917_LDO5_CTRL_WR_S				0x80
#घोषणा TPS65917_LDO5_CTRL_WR_S_SHIFT				0x07
#घोषणा TPS65917_LDO5_CTRL_STATUS				0x10
#घोषणा TPS65917_LDO5_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_LDO5_CTRL_MODE_SLEEP				0x04
#घोषणा TPS65917_LDO5_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_LDO5_CTRL_MODE_ACTIVE				0x01
#घोषणा TPS65917_LDO5_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम LDO5_VOLTAGE */
#घोषणा TPS65917_LDO5_VOLTAGE_VSEL_MASK			0x2F
#घोषणा TPS65917_LDO5_VOLTAGE_VSEL_SHIFT			0x00

/* Bit definitions क्रम LDO_PD_CTRL1 */
#घोषणा TPS65917_LDO_PD_CTRL1_LDO4				0x80
#घोषणा TPS65917_LDO_PD_CTRL1_LDO4_SHIFT			0x07
#घोषणा TPS65917_LDO_PD_CTRL1_LDO2				0x02
#घोषणा TPS65917_LDO_PD_CTRL1_LDO2_SHIFT			0x01
#घोषणा TPS65917_LDO_PD_CTRL1_LDO1				0x01
#घोषणा TPS65917_LDO_PD_CTRL1_LDO1_SHIFT			0x00

/* Bit definitions क्रम LDO_PD_CTRL2 */
#घोषणा TPS65917_LDO_PD_CTRL2_LDO3				0x04
#घोषणा TPS65917_LDO_PD_CTRL2_LDO3_SHIFT			0x02
#घोषणा TPS65917_LDO_PD_CTRL2_LDO5				0x02
#घोषणा TPS65917_LDO_PD_CTRL2_LDO5_SHIFT			0x01

/* Bit definitions क्रम LDO_PD_CTRL3 */
#घोषणा TPS65917_LDO_PD_CTRL2_LDOVANA				0x80
#घोषणा TPS65917_LDO_PD_CTRL2_LDOVANA_SHIFT			0x07

/* Bit definitions क्रम LDO_SHORT_STATUS1 */
#घोषणा TPS65917_LDO_SHORT_STATUS1_LDO4			0x80
#घोषणा TPS65917_LDO_SHORT_STATUS1_LDO4_SHIFT			0x07
#घोषणा TPS65917_LDO_SHORT_STATUS1_LDO2			0x02
#घोषणा TPS65917_LDO_SHORT_STATUS1_LDO2_SHIFT			0x01
#घोषणा TPS65917_LDO_SHORT_STATUS1_LDO1			0x01
#घोषणा TPS65917_LDO_SHORT_STATUS1_LDO1_SHIFT			0x00

/* Bit definitions क्रम LDO_SHORT_STATUS2 */
#घोषणा TPS65917_LDO_SHORT_STATUS2_LDO3			0x04
#घोषणा TPS65917_LDO_SHORT_STATUS2_LDO3_SHIFT			0x02
#घोषणा TPS65917_LDO_SHORT_STATUS2_LDO5			0x02
#घोषणा TPS65917_LDO_SHORT_STATUS2_LDO5_SHIFT			0x01

/* Bit definitions क्रम LDO_SHORT_STATUS2 */
#घोषणा TPS65917_LDO_SHORT_STATUS2_LDOVANA			0x80
#घोषणा TPS65917_LDO_SHORT_STATUS2_LDOVANA_SHIFT		0x07

/* Bit definitions क्रम REGEN1_CTRL */
#घोषणा TPS65917_REGEN1_CTRL_STATUS				0x10
#घोषणा TPS65917_REGEN1_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_REGEN1_CTRL_MODE_SLEEP			0x04
#घोषणा TPS65917_REGEN1_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_REGEN1_CTRL_MODE_ACTIVE			0x01
#घोषणा TPS65917_REGEN1_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम PLLEN_CTRL */
#घोषणा TPS65917_PLLEN_CTRL_STATUS				0x10
#घोषणा TPS65917_PLLEN_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_PLLEN_CTRL_MODE_SLEEP				0x04
#घोषणा TPS65917_PLLEN_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_PLLEN_CTRL_MODE_ACTIVE			0x01
#घोषणा TPS65917_PLLEN_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम REGEN2_CTRL */
#घोषणा TPS65917_REGEN2_CTRL_STATUS				0x10
#घोषणा TPS65917_REGEN2_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_REGEN2_CTRL_MODE_SLEEP			0x04
#घोषणा TPS65917_REGEN2_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_REGEN2_CTRL_MODE_ACTIVE			0x01
#घोषणा TPS65917_REGEN2_CTRL_MODE_ACTIVE_SHIFT			0x00

/* Bit definitions क्रम NSLEEP_RES_ASSIGN */
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_PLL_EN			0x08
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_PLL_EN_SHIFT		0x03
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_REGEN3			0x04
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_REGEN3_SHIFT		0x02
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_REGEN2			0x02
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_REGEN2_SHIFT		0x01
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_REGEN1			0x01
#घोषणा TPS65917_NSLEEP_RES_ASSIGN_REGEN1_SHIFT		0x00

/* Bit definitions क्रम NSLEEP_SMPS_ASSIGN */
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS5			0x40
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS5_SHIFT		0x06
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS4			0x10
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS4_SHIFT		0x04
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS3			0x08
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS3_SHIFT		0x03
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS2			0x02
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS2_SHIFT		0x01
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS1			0x01
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN_SMPS1_SHIFT		0x00

/* Bit definitions क्रम NSLEEP_LDO_ASSIGN1 */
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1_LDO4			0x80
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1_LDO4_SHIFT			0x07
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1_LDO2			0x02
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1_LDO2_SHIFT			0x01
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1_LDO1			0x01
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1_LDO1_SHIFT			0x00

/* Bit definitions क्रम NSLEEP_LDO_ASSIGN2 */
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN2_LDO3			0x04
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN2_LDO3_SHIFT			0x02
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN2_LDO5			0x02
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN2_LDO5_SHIFT			0x01

/* Bit definitions क्रम ENABLE1_RES_ASSIGN */
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_PLLEN			0x08
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_PLLEN_SHIFT		0x03
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_REGEN3			0x04
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_REGEN3_SHIFT		0x02
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_REGEN2			0x02
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_REGEN2_SHIFT		0x01
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_REGEN1			0x01
#घोषणा TPS65917_ENABLE1_RES_ASSIGN_REGEN1_SHIFT		0x00

/* Bit definitions क्रम ENABLE1_SMPS_ASSIGN */
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS5			0x40
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS5_SHIFT		0x06
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS4			0x10
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS4_SHIFT		0x04
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS3			0x08
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS3_SHIFT		0x03
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS2			0x02
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS2_SHIFT		0x01
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS1			0x01
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN_SMPS1_SHIFT		0x00

/* Bit definitions क्रम ENABLE1_LDO_ASSIGN1 */
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1_LDO4			0x80
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1_LDO4_SHIFT		0x07
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1_LDO2			0x02
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1_LDO2_SHIFT		0x01
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1_LDO1			0x01
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1_LDO1_SHIFT		0x00

/* Bit definitions क्रम ENABLE1_LDO_ASSIGN2 */
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN2_LDO3			0x04
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN2_LDO3_SHIFT		0x02
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN2_LDO5			0x02
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN2_LDO5_SHIFT		0x01

/* Bit definitions क्रम ENABLE2_RES_ASSIGN */
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_PLLEN			0x08
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_PLLEN_SHIFT		0x03
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_REGEN3			0x04
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_REGEN3_SHIFT		0x02
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_REGEN2			0x02
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_REGEN2_SHIFT		0x01
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_REGEN1			0x01
#घोषणा TPS65917_ENABLE2_RES_ASSIGN_REGEN1_SHIFT		0x00

/* Bit definitions क्रम ENABLE2_SMPS_ASSIGN */
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS5			0x40
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS5_SHIFT		0x06
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS4			0x10
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS4_SHIFT		0x04
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS3			0x08
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS3_SHIFT		0x03
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS2			0x02
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS2_SHIFT		0x01
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS1			0x01
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN_SMPS1_SHIFT		0x00

/* Bit definitions क्रम ENABLE2_LDO_ASSIGN1 */
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1_LDO4			0x80
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1_LDO4_SHIFT		0x07
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1_LDO2			0x02
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1_LDO2_SHIFT		0x01
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1_LDO1			0x01
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1_LDO1_SHIFT		0x00

/* Bit definitions क्रम ENABLE2_LDO_ASSIGN2 */
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN2_LDO3			0x04
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN2_LDO3_SHIFT		0x02
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN2_LDO5			0x02
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN2_LDO5_SHIFT		0x01

/* Bit definitions क्रम REGEN3_CTRL */
#घोषणा TPS65917_REGEN3_CTRL_STATUS				0x10
#घोषणा TPS65917_REGEN3_CTRL_STATUS_SHIFT			0x04
#घोषणा TPS65917_REGEN3_CTRL_MODE_SLEEP			0x04
#घोषणा TPS65917_REGEN3_CTRL_MODE_SLEEP_SHIFT			0x02
#घोषणा TPS65917_REGEN3_CTRL_MODE_ACTIVE			0x01
#घोषणा TPS65917_REGEN3_CTRL_MODE_ACTIVE_SHIFT			0x00

/* POWERHOLD Mask field क्रम PRIMARY_SECONDARY_PAD2 रेजिस्टर */
#घोषणा TPS65917_PRIMARY_SECONDARY_PAD2_GPIO_5_MASK		0xC

/* Registers क्रम function RESOURCE */
#घोषणा TPS65917_REGEN1_CTRL					0x2
#घोषणा TPS65917_PLLEN_CTRL					0x3
#घोषणा TPS65917_NSLEEP_RES_ASSIGN				0x6
#घोषणा TPS65917_NSLEEP_SMPS_ASSIGN				0x7
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN1				0x8
#घोषणा TPS65917_NSLEEP_LDO_ASSIGN2				0x9
#घोषणा TPS65917_ENABLE1_RES_ASSIGN				0xA
#घोषणा TPS65917_ENABLE1_SMPS_ASSIGN				0xB
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN1				0xC
#घोषणा TPS65917_ENABLE1_LDO_ASSIGN2				0xD
#घोषणा TPS65917_ENABLE2_RES_ASSIGN				0xE
#घोषणा TPS65917_ENABLE2_SMPS_ASSIGN				0xF
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN1				0x10
#घोषणा TPS65917_ENABLE2_LDO_ASSIGN2				0x11
#घोषणा TPS65917_REGEN2_CTRL					0x12
#घोषणा TPS65917_REGEN3_CTRL					0x13

अटल अंतरभूत पूर्णांक palmas_पढ़ो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक base,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक addr = PALMAS_BASE_TO_REG(base, reg);
	पूर्णांक slave_id = PALMAS_BASE_TO_SLAVE(base);

	वापस regmap_पढ़ो(palmas->regmap[slave_id], addr, val);
पूर्ण

अटल अंतरभूत पूर्णांक palmas_ग_लिखो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक base,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक addr = PALMAS_BASE_TO_REG(base, reg);
	पूर्णांक slave_id = PALMAS_BASE_TO_SLAVE(base);

	वापस regmap_ग_लिखो(palmas->regmap[slave_id], addr, value);
पूर्ण

अटल अंतरभूत पूर्णांक palmas_bulk_ग_लिखो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक base,
	अचिन्हित पूर्णांक reg, स्थिर व्योम *val, माप_प्रकार val_count)
अणु
	अचिन्हित पूर्णांक addr = PALMAS_BASE_TO_REG(base, reg);
	पूर्णांक slave_id = PALMAS_BASE_TO_SLAVE(base);

	वापस regmap_bulk_ग_लिखो(palmas->regmap[slave_id], addr,
			val, val_count);
पूर्ण

अटल अंतरभूत पूर्णांक palmas_bulk_पढ़ो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक base,
		अचिन्हित पूर्णांक reg, व्योम *val, माप_प्रकार val_count)
अणु
	अचिन्हित पूर्णांक addr = PALMAS_BASE_TO_REG(base, reg);
	पूर्णांक slave_id = PALMAS_BASE_TO_SLAVE(base);

	वापस regmap_bulk_पढ़ो(palmas->regmap[slave_id], addr,
		val, val_count);
पूर्ण

अटल अंतरभूत पूर्णांक palmas_update_bits(काष्ठा palmas *palmas, अचिन्हित पूर्णांक base,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक addr = PALMAS_BASE_TO_REG(base, reg);
	पूर्णांक slave_id = PALMAS_BASE_TO_SLAVE(base);

	वापस regmap_update_bits(palmas->regmap[slave_id], addr, mask, val);
पूर्ण

अटल अंतरभूत पूर्णांक palmas_irq_get_virq(काष्ठा palmas *palmas, पूर्णांक irq)
अणु
	वापस regmap_irq_get_virq(palmas->irq_data, irq);
पूर्ण


पूर्णांक palmas_ext_control_req_config(काष्ठा palmas *palmas,
	क्रमागत palmas_बाह्यal_requestor_id ext_control_req_id,
	पूर्णांक ext_ctrl, bool enable);

#पूर्ण_अगर /*  __LINUX_MFD_PALMAS_H */
