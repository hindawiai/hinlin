<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LED_H
#घोषणा LED_H

#घोषणा	LED7		0x80		/* top (or furthest right) LED */
#घोषणा	LED6		0x40
#घोषणा	LED5		0x20
#घोषणा	LED4		0x10
#घोषणा	LED3		0x08
#घोषणा	LED2		0x04
#घोषणा	LED1		0x02
#घोषणा	LED0		0x01		/* bottom (or furthest left) LED */

#घोषणा	LED_LAN_TX	LED0		/* क्रम LAN transmit activity */
#घोषणा	LED_LAN_RCV	LED1		/* क्रम LAN receive activity */
#घोषणा	LED_DISK_IO	LED2		/* क्रम disk activity */
#घोषणा	LED_HEARTBEAT	LED3		/* heartbeat */

/* values क्रम pdc_chassis_lcd_info_ret_block.model: */
#घोषणा DISPLAY_MODEL_LCD  0		/* KittyHawk LED or LCD */
#घोषणा DISPLAY_MODEL_NONE 1		/* no LED or LCD */
#घोषणा DISPLAY_MODEL_LASI 2		/* LASI style 8 bit LED */
#घोषणा DISPLAY_MODEL_OLD_ASP 0x7F	/* faked: ASP style 8 x 1 bit LED (only very old ASP versions) */

#घोषणा LED_CMD_REG_NONE 0		/* शून्य == no addr क्रम the cmd रेजिस्टर */

/* रेजिस्टर_led_driver() */
पूर्णांक __init रेजिस्टर_led_driver(पूर्णांक model, अचिन्हित दीर्घ cmd_reg, अचिन्हित दीर्घ data_reg);

/* रेजिस्टरs the LED regions क्रम procfs */
व्योम __init रेजिस्टर_led_regions(व्योम);

#अगर_घोषित CONFIG_CHASSIS_LCD_LED
/* ग_लिखोs a string to the LCD display (अगर possible on this h/w) */
पूर्णांक lcd_prपूर्णांक(स्थिर अक्षर *str);
#अन्यथा
#घोषणा lcd_prपूर्णांक(str)
#पूर्ण_अगर

/* मुख्य LED initialization function (uses PDC) */ 
पूर्णांक __init led_init(व्योम);

#पूर्ण_अगर /* LED_H */
