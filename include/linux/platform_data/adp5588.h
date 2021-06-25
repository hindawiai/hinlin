<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Analog Devices ADP5588 I/O Expander and QWERTY Keypad Controller
 *
 * Copyright 2009-2010 Analog Devices Inc.
 */

#अगर_अघोषित _ADP5588_H
#घोषणा _ADP5588_H

#घोषणा DEV_ID 0x00		/* Device ID */
#घोषणा CFG 0x01		/* Configuration Register1 */
#घोषणा INT_STAT 0x02		/* Interrupt Status Register */
#घोषणा KEY_LCK_EC_STAT 0x03	/* Key Lock and Event Counter Register */
#घोषणा Key_EVENTA 0x04		/* Key Event Register A */
#घोषणा Key_EVENTB 0x05		/* Key Event Register B */
#घोषणा Key_EVENTC 0x06		/* Key Event Register C */
#घोषणा Key_EVENTD 0x07		/* Key Event Register D */
#घोषणा Key_EVENTE 0x08		/* Key Event Register E */
#घोषणा Key_EVENTF 0x09		/* Key Event Register F */
#घोषणा Key_EVENTG 0x0A		/* Key Event Register G */
#घोषणा Key_EVENTH 0x0B		/* Key Event Register H */
#घोषणा Key_EVENTI 0x0C		/* Key Event Register I */
#घोषणा Key_EVENTJ 0x0D		/* Key Event Register J */
#घोषणा KP_LCK_TMR 0x0E		/* Keypad Lock1 to Lock2 Timer */
#घोषणा UNLOCK1 0x0F		/* Unlock Key1 */
#घोषणा UNLOCK2 0x10		/* Unlock Key2 */
#घोषणा GPIO_INT_STAT1 0x11	/* GPIO Interrupt Status */
#घोषणा GPIO_INT_STAT2 0x12	/* GPIO Interrupt Status */
#घोषणा GPIO_INT_STAT3 0x13	/* GPIO Interrupt Status */
#घोषणा GPIO_DAT_STAT1 0x14	/* GPIO Data Status, Read twice to clear */
#घोषणा GPIO_DAT_STAT2 0x15	/* GPIO Data Status, Read twice to clear */
#घोषणा GPIO_DAT_STAT3 0x16	/* GPIO Data Status, Read twice to clear */
#घोषणा GPIO_DAT_OUT1 0x17	/* GPIO DATA OUT */
#घोषणा GPIO_DAT_OUT2 0x18	/* GPIO DATA OUT */
#घोषणा GPIO_DAT_OUT3 0x19	/* GPIO DATA OUT */
#घोषणा GPIO_INT_EN1 0x1A	/* GPIO Interrupt Enable */
#घोषणा GPIO_INT_EN2 0x1B	/* GPIO Interrupt Enable */
#घोषणा GPIO_INT_EN3 0x1C	/* GPIO Interrupt Enable */
#घोषणा KP_GPIO1 0x1D		/* Keypad or GPIO Selection */
#घोषणा KP_GPIO2 0x1E		/* Keypad or GPIO Selection */
#घोषणा KP_GPIO3 0x1F		/* Keypad or GPIO Selection */
#घोषणा GPI_EM1 0x20		/* GPI Event Mode 1 */
#घोषणा GPI_EM2 0x21		/* GPI Event Mode 2 */
#घोषणा GPI_EM3 0x22		/* GPI Event Mode 3 */
#घोषणा GPIO_सूची1 0x23		/* GPIO Data Direction */
#घोषणा GPIO_सूची2 0x24		/* GPIO Data Direction */
#घोषणा GPIO_सूची3 0x25		/* GPIO Data Direction */
#घोषणा GPIO_INT_LVL1 0x26	/* GPIO Edge/Level Detect */
#घोषणा GPIO_INT_LVL2 0x27	/* GPIO Edge/Level Detect */
#घोषणा GPIO_INT_LVL3 0x28	/* GPIO Edge/Level Detect */
#घोषणा Debounce_DIS1 0x29	/* Debounce Disable */
#घोषणा Debounce_DIS2 0x2A	/* Debounce Disable */
#घोषणा Debounce_DIS3 0x2B	/* Debounce Disable */
#घोषणा GPIO_PULL1 0x2C		/* GPIO Pull Disable */
#घोषणा GPIO_PULL2 0x2D		/* GPIO Pull Disable */
#घोषणा GPIO_PULL3 0x2E		/* GPIO Pull Disable */
#घोषणा CMP_CFG_STAT 0x30	/* Comparator Configuration and Status Register */
#घोषणा CMP_CONFG_SENS1 0x31	/* Sensor1 Comparator Configuration Register */
#घोषणा CMP_CONFG_SENS2 0x32	/* L2 Light Sensor Reference Level, Output Falling क्रम Sensor 1 */
#घोषणा CMP1_LVL2_TRIP 0x33	/* L2 Light Sensor Hysteresis (Active when Output Rising) क्रम Sensor 1 */
#घोषणा CMP1_LVL2_HYS 0x34	/* L3 Light Sensor Reference Level, Output Falling For Sensor 1 */
#घोषणा CMP1_LVL3_TRIP 0x35	/* L3 Light Sensor Hysteresis (Active when Output Rising) For Sensor 1 */
#घोषणा CMP1_LVL3_HYS 0x36	/* Sensor 2 Comparator Configuration Register */
#घोषणा CMP2_LVL2_TRIP 0x37	/* L2 Light Sensor Reference Level, Output Falling क्रम Sensor 2 */
#घोषणा CMP2_LVL2_HYS 0x38	/* L2 Light Sensor Hysteresis (Active when Output Rising) क्रम Sensor 2 */
#घोषणा CMP2_LVL3_TRIP 0x39	/* L3 Light Sensor Reference Level, Output Falling For Sensor 2 */
#घोषणा CMP2_LVL3_HYS 0x3A	/* L3 Light Sensor Hysteresis (Active when Output Rising) For Sensor 2 */
#घोषणा CMP1_ADC_DAT_R1 0x3B	/* Comparator 1 ADC data Register1 */
#घोषणा CMP1_ADC_DAT_R2 0x3C	/* Comparator 1 ADC data Register2 */
#घोषणा CMP2_ADC_DAT_R1 0x3D	/* Comparator 2 ADC data Register1 */
#घोषणा CMP2_ADC_DAT_R2 0x3E	/* Comparator 2 ADC data Register2 */

#घोषणा ADP5588_DEVICE_ID_MASK	0xF

 /* Configuration Register1 */
#घोषणा ADP5588_AUTO_INC	(1 << 7)
#घोषणा ADP5588_GPIEM_CFG	(1 << 6)
#घोषणा ADP5588_OVR_FLOW_M	(1 << 5)
#घोषणा ADP5588_INT_CFG		(1 << 4)
#घोषणा ADP5588_OVR_FLOW_IEN	(1 << 3)
#घोषणा ADP5588_K_LCK_IM	(1 << 2)
#घोषणा ADP5588_GPI_IEN		(1 << 1)
#घोषणा ADP5588_KE_IEN		(1 << 0)

/* Interrupt Status Register */
#घोषणा ADP5588_CMP2_INT	(1 << 5)
#घोषणा ADP5588_CMP1_INT	(1 << 4)
#घोषणा ADP5588_OVR_FLOW_INT	(1 << 3)
#घोषणा ADP5588_K_LCK_INT	(1 << 2)
#घोषणा ADP5588_GPI_INT		(1 << 1)
#घोषणा ADP5588_KE_INT		(1 << 0)

/* Key Lock and Event Counter Register */
#घोषणा ADP5588_K_LCK_EN	(1 << 6)
#घोषणा ADP5588_LCK21		0x30
#घोषणा ADP5588_KEC		0xF

#घोषणा ADP5588_MAXGPIO		18
#घोषणा ADP5588_BANK(offs)	((offs) >> 3)
#घोषणा ADP5588_BIT(offs)	(1u << ((offs) & 0x7))

/* Put one of these काष्ठाures in i2c_board_info platक्रमm_data */

#घोषणा ADP5588_KEYMAPSIZE	80

#घोषणा GPI_PIN_ROW0 97
#घोषणा GPI_PIN_ROW1 98
#घोषणा GPI_PIN_ROW2 99
#घोषणा GPI_PIN_ROW3 100
#घोषणा GPI_PIN_ROW4 101
#घोषणा GPI_PIN_ROW5 102
#घोषणा GPI_PIN_ROW6 103
#घोषणा GPI_PIN_ROW7 104
#घोषणा GPI_PIN_COL0 105
#घोषणा GPI_PIN_COL1 106
#घोषणा GPI_PIN_COL2 107
#घोषणा GPI_PIN_COL3 108
#घोषणा GPI_PIN_COL4 109
#घोषणा GPI_PIN_COL5 110
#घोषणा GPI_PIN_COL6 111
#घोषणा GPI_PIN_COL7 112
#घोषणा GPI_PIN_COL8 113
#घोषणा GPI_PIN_COL9 114

#घोषणा GPI_PIN_ROW_BASE GPI_PIN_ROW0
#घोषणा GPI_PIN_ROW_END GPI_PIN_ROW7
#घोषणा GPI_PIN_COL_BASE GPI_PIN_COL0
#घोषणा GPI_PIN_COL_END GPI_PIN_COL9

#घोषणा GPI_PIN_BASE GPI_PIN_ROW_BASE
#घोषणा GPI_PIN_END GPI_PIN_COL_END

#घोषणा ADP5588_GPIMAPSIZE_MAX (GPI_PIN_END - GPI_PIN_BASE + 1)

काष्ठा adp5588_gpi_map अणु
	अचिन्हित लघु pin;
	अचिन्हित लघु sw_evt;
पूर्ण;

काष्ठा adp5588_kpad_platक्रमm_data अणु
	पूर्णांक rows;			/* Number of rows */
	पूर्णांक cols;			/* Number of columns */
	स्थिर अचिन्हित लघु *keymap;	/* Poपूर्णांकer to keymap */
	अचिन्हित लघु keymapsize;	/* Keymap size */
	अचिन्हित repeat:1;		/* Enable key repeat */
	अचिन्हित en_keylock:1;		/* Enable Key Lock feature */
	अचिन्हित लघु unlock_key1;	/* Unlock Key 1 */
	अचिन्हित लघु unlock_key2;	/* Unlock Key 2 */
	स्थिर काष्ठा adp5588_gpi_map *gpimap;
	अचिन्हित लघु gpimapsize;
	स्थिर काष्ठा adp5588_gpio_platक्रमm_data *gpio_data;
पूर्ण;

काष्ठा i2c_client; /* क्रमward declaration */

काष्ठा adp5588_gpio_platक्रमm_data अणु
	पूर्णांक gpio_start;		/* GPIO Chip base # */
	स्थिर अक्षर *स्थिर *names;
	अचिन्हित irq_base;	/* पूर्णांकerrupt base # */
	अचिन्हित pullup_dis_mask; /* Pull-Up Disable Mask */
	पूर्णांक	(*setup)(काष्ठा i2c_client *client,
				अचिन्हित gpio, अचिन्हित ngpio,
				व्योम *context);
	पूर्णांक	(*tearकरोwn)(काष्ठा i2c_client *client,
				अचिन्हित gpio, अचिन्हित ngpio,
				व्योम *context);
	व्योम	*context;
पूर्ण;

#पूर्ण_अगर
