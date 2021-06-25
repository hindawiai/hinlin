<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PMIC_DA903X_H
#घोषणा __LINUX_PMIC_DA903X_H

/* Unअगरied sub device IDs क्रम DA9030/DA9034/DA9035 */
क्रमागत अणु
	DA9030_ID_LED_1,
	DA9030_ID_LED_2,
	DA9030_ID_LED_3,
	DA9030_ID_LED_4,
	DA9030_ID_LED_PC,
	DA9030_ID_VIBRA,
	DA9030_ID_WLED,
	DA9030_ID_BUCK1,
	DA9030_ID_BUCK2,
	DA9030_ID_LDO1,
	DA9030_ID_LDO2,
	DA9030_ID_LDO3,
	DA9030_ID_LDO4,
	DA9030_ID_LDO5,
	DA9030_ID_LDO6,
	DA9030_ID_LDO7,
	DA9030_ID_LDO8,
	DA9030_ID_LDO9,
	DA9030_ID_LDO10,
	DA9030_ID_LDO11,
	DA9030_ID_LDO12,
	DA9030_ID_LDO13,
	DA9030_ID_LDO14,
	DA9030_ID_LDO15,
	DA9030_ID_LDO16,
	DA9030_ID_LDO17,
	DA9030_ID_LDO18,
	DA9030_ID_LDO19,
	DA9030_ID_LDO_INT,	/* LDO Internal */
	DA9030_ID_BAT,		/* battery अक्षरger */

	DA9034_ID_LED_1,
	DA9034_ID_LED_2,
	DA9034_ID_VIBRA,
	DA9034_ID_WLED,
	DA9034_ID_TOUCH,

	DA9034_ID_BUCK1,
	DA9034_ID_BUCK2,
	DA9034_ID_LDO1,
	DA9034_ID_LDO2,
	DA9034_ID_LDO3,
	DA9034_ID_LDO4,
	DA9034_ID_LDO5,
	DA9034_ID_LDO6,
	DA9034_ID_LDO7,
	DA9034_ID_LDO8,
	DA9034_ID_LDO9,
	DA9034_ID_LDO10,
	DA9034_ID_LDO11,
	DA9034_ID_LDO12,
	DA9034_ID_LDO13,
	DA9034_ID_LDO14,
	DA9034_ID_LDO15,

	DA9035_ID_BUCK3,
पूर्ण;

/*
 * DA9030/DA9034 LEDs sub-devices uses generic "struct led_info"
 * as the platक्रमm_data
 */

/* DA9030 flags क्रम "struct led_info"
 */
#घोषणा DA9030_LED_RATE_ON	(0 << 5)
#घोषणा DA9030_LED_RATE_052S	(1 << 5)
#घोषणा DA9030_LED_DUTY_1_16	(0 << 3)
#घोषणा DA9030_LED_DUTY_1_8	(1 << 3)
#घोषणा DA9030_LED_DUTY_1_4	(2 << 3)
#घोषणा DA9030_LED_DUTY_1_2	(3 << 3)

#घोषणा DA9030_VIBRA_MODE_1P3V	(0 << 1)
#घोषणा DA9030_VIBRA_MODE_2P7V	(1 << 1)
#घोषणा DA9030_VIBRA_FREQ_1HZ	(0 << 2)
#घोषणा DA9030_VIBRA_FREQ_2HZ	(1 << 2)
#घोषणा DA9030_VIBRA_FREQ_4HZ	(2 << 2)
#घोषणा DA9030_VIBRA_FREQ_8HZ	(3 << 2)
#घोषणा DA9030_VIBRA_DUTY_ON	(0 << 4)
#घोषणा DA9030_VIBRA_DUTY_75P	(1 << 4)
#घोषणा DA9030_VIBRA_DUTY_50P	(2 << 4)
#घोषणा DA9030_VIBRA_DUTY_25P	(3 << 4)

/* DA9034 flags क्रम "struct led_info" */
#घोषणा DA9034_LED_RAMP		(1 << 7)

/* DA9034 touch screen platक्रमm data */
काष्ठा da9034_touch_pdata अणु
	पूर्णांक	पूर्णांकerval_ms;	/* sampling पूर्णांकerval जबतक pen करोwn */
	पूर्णांक	x_inverted;
	पूर्णांक	y_inverted;
पूर्ण;

काष्ठा da9034_backlight_pdata अणु
	पूर्णांक	output_current;	/* output current of WLED, from 0-31 (in mA) */
पूर्ण;

/* DA9030 battery अक्षरger data */
काष्ठा घातer_supply_info;

काष्ठा da9030_battery_info अणु
	/* battery parameters */
	काष्ठा घातer_supply_info *battery_info;

	/* current and voltage to use क्रम battery अक्षरging */
	अचिन्हित पूर्णांक अक्षरge_milliamp;
	अचिन्हित पूर्णांक अक्षरge_millivolt;

	/* voltage thresholds (in millivolts) */
	पूर्णांक vbat_low;
	पूर्णांक vbat_crit;
	पूर्णांक vbat_अक्षरge_start;
	पूर्णांक vbat_अक्षरge_stop;
	पूर्णांक vbat_अक्षरge_restart;

	/* battery nominal minimal and maximal voltages in millivolts */
	पूर्णांक vअक्षरge_min;
	पूर्णांक vअक्षरge_max;

	/* Temperature thresholds. These are DA9030 रेजिस्टर values
	   "as is" and should be measured क्रम each battery type */
	पूर्णांक tbat_low;
	पूर्णांक tbat_high;
	पूर्णांक tbat_restart;


	/* battery monitor पूर्णांकerval (seconds) */
	अचिन्हित पूर्णांक baपंचांगon_पूर्णांकerval;

	/* platक्रमm callbacks क्रम battery low and critical events */
	व्योम (*battery_low)(व्योम);
	व्योम (*battery_critical)(व्योम);
पूर्ण;

काष्ठा da903x_subdev_info अणु
	पूर्णांक		id;
	स्थिर अक्षर	*name;
	व्योम		*platक्रमm_data;
पूर्ण;

काष्ठा da903x_platक्रमm_data अणु
	पूर्णांक num_subdevs;
	काष्ठा da903x_subdev_info *subdevs;
पूर्ण;

/* bit definitions क्रम DA9030 events */
#घोषणा DA9030_EVENT_ONKEY		(1 << 0)
#घोषणा	DA9030_EVENT_PWREN		(1 << 1)
#घोषणा	DA9030_EVENT_EXTON		(1 << 2)
#घोषणा	DA9030_EVENT_CHDET		(1 << 3)
#घोषणा	DA9030_EVENT_TBAT		(1 << 4)
#घोषणा	DA9030_EVENT_VBATMON		(1 << 5)
#घोषणा	DA9030_EVENT_VBATMON_TXON	(1 << 6)
#घोषणा	DA9030_EVENT_CHIOVER		(1 << 7)
#घोषणा	DA9030_EVENT_TCTO		(1 << 8)
#घोषणा	DA9030_EVENT_CCTO		(1 << 9)
#घोषणा	DA9030_EVENT_ADC_READY		(1 << 10)
#घोषणा	DA9030_EVENT_VBUS_4P4		(1 << 11)
#घोषणा	DA9030_EVENT_VBUS_4P0		(1 << 12)
#घोषणा	DA9030_EVENT_SESS_VALID		(1 << 13)
#घोषणा	DA9030_EVENT_SRP_DETECT		(1 << 14)
#घोषणा	DA9030_EVENT_WATCHDOG		(1 << 15)
#घोषणा	DA9030_EVENT_LDO15		(1 << 16)
#घोषणा	DA9030_EVENT_LDO16		(1 << 17)
#घोषणा	DA9030_EVENT_LDO17		(1 << 18)
#घोषणा	DA9030_EVENT_LDO18		(1 << 19)
#घोषणा	DA9030_EVENT_LDO19		(1 << 20)
#घोषणा	DA9030_EVENT_BUCK2		(1 << 21)

/* bit definitions क्रम DA9034 events */
#घोषणा DA9034_EVENT_ONKEY		(1 << 0)
#घोषणा DA9034_EVENT_EXTON		(1 << 2)
#घोषणा DA9034_EVENT_CHDET		(1 << 3)
#घोषणा DA9034_EVENT_TBAT		(1 << 4)
#घोषणा DA9034_EVENT_VBATMON		(1 << 5)
#घोषणा DA9034_EVENT_REV_IOVER		(1 << 6)
#घोषणा DA9034_EVENT_CH_IOVER		(1 << 7)
#घोषणा DA9034_EVENT_CH_TCTO		(1 << 8)
#घोषणा DA9034_EVENT_CH_CCTO		(1 << 9)
#घोषणा DA9034_EVENT_USB_DEV		(1 << 10)
#घोषणा DA9034_EVENT_OTGCP_IOVER	(1 << 11)
#घोषणा DA9034_EVENT_VBUS_4P55		(1 << 12)
#घोषणा DA9034_EVENT_VBUS_3P8		(1 << 13)
#घोषणा DA9034_EVENT_SESS_1P8		(1 << 14)
#घोषणा DA9034_EVENT_SRP_READY		(1 << 15)
#घोषणा DA9034_EVENT_ADC_MAN		(1 << 16)
#घोषणा DA9034_EVENT_ADC_AUTO4		(1 << 17)
#घोषणा DA9034_EVENT_ADC_AUTO5		(1 << 18)
#घोषणा DA9034_EVENT_ADC_AUTO6		(1 << 19)
#घोषणा DA9034_EVENT_PEN_DOWN		(1 << 20)
#घोषणा DA9034_EVENT_TSI_READY		(1 << 21)
#घोषणा DA9034_EVENT_UART_TX		(1 << 22)
#घोषणा DA9034_EVENT_UART_RX		(1 << 23)
#घोषणा DA9034_EVENT_HEADSET		(1 << 25)
#घोषणा DA9034_EVENT_HOOKSWITCH		(1 << 26)
#घोषणा DA9034_EVENT_WATCHDOG		(1 << 27)

बाह्य पूर्णांक da903x_रेजिस्टर_notअगरier(काष्ठा device *dev,
		काष्ठा notअगरier_block *nb, अचिन्हित पूर्णांक events);
बाह्य पूर्णांक da903x_unरेजिस्टर_notअगरier(काष्ठा device *dev,
		काष्ठा notअगरier_block *nb, अचिन्हित पूर्णांक events);

/* Status Query Interface */
#घोषणा DA9030_STATUS_ONKEY		(1 << 0)
#घोषणा DA9030_STATUS_PWREN1		(1 << 1)
#घोषणा DA9030_STATUS_EXTON		(1 << 2)
#घोषणा DA9030_STATUS_CHDET		(1 << 3)
#घोषणा DA9030_STATUS_TBAT		(1 << 4)
#घोषणा DA9030_STATUS_VBATMON		(1 << 5)
#घोषणा DA9030_STATUS_VBATMON_TXON	(1 << 6)
#घोषणा DA9030_STATUS_MCLKDET		(1 << 7)

#घोषणा DA9034_STATUS_ONKEY		(1 << 0)
#घोषणा DA9034_STATUS_EXTON		(1 << 2)
#घोषणा DA9034_STATUS_CHDET		(1 << 3)
#घोषणा DA9034_STATUS_TBAT		(1 << 4)
#घोषणा DA9034_STATUS_VBATMON		(1 << 5)
#घोषणा DA9034_STATUS_PEN_DOWN		(1 << 6)
#घोषणा DA9034_STATUS_MCLKDET		(1 << 7)
#घोषणा DA9034_STATUS_USB_DEV		(1 << 8)
#घोषणा DA9034_STATUS_HEADSET		(1 << 9)
#घोषणा DA9034_STATUS_HOOKSWITCH	(1 << 10)
#घोषणा DA9034_STATUS_REMCON		(1 << 11)
#घोषणा DA9034_STATUS_VBUS_VALID_4P55	(1 << 12)
#घोषणा DA9034_STATUS_VBUS_VALID_3P8	(1 << 13)
#घोषणा DA9034_STATUS_SESS_VALID_1P8	(1 << 14)
#घोषणा DA9034_STATUS_SRP_READY		(1 << 15)

बाह्य पूर्णांक da903x_query_status(काष्ठा device *dev, अचिन्हित पूर्णांक status);


/* NOTE: the functions below are not पूर्णांकended क्रम use outside
 * of the DA903x sub-device drivers
 */
बाह्य पूर्णांक da903x_ग_लिखो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val);
बाह्य पूर्णांक da903x_ग_लिखोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val);
बाह्य पूर्णांक da903x_पढ़ो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t *val);
बाह्य पूर्णांक da903x_पढ़ोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val);
बाह्य पूर्णांक da903x_update(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val, uपूर्णांक8_t mask);
बाह्य पूर्णांक da903x_set_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask);
बाह्य पूर्णांक da903x_clr_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask);
#पूर्ण_अगर /* __LINUX_PMIC_DA903X_H */
