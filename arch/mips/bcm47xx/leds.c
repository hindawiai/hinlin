<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "bcm47xx_private.h"

#समावेश <linux/leds.h>
#समावेश <bcm47xx_board.h>

/**************************************************
 * Database
 **************************************************/

#घोषणा BCM47XX_GPIO_LED(_gpio, _color, _function, _active_low,		\
			 _शेष_state)				\
	अणु								\
		.name		= "bcm47xx:" _color ":" _function,	\
		.gpio		= _gpio,				\
		.active_low	= _active_low,				\
		.शेष_state	= _शेष_state,			\
	पूर्ण

#घोषणा BCM47XX_GPIO_LED_TRIGGER(_gpio, _color, _function, _active_low,	\
				 _शेष_trigger)			\
	अणु								\
		.name		= "bcm47xx:" _color ":" _function,	\
		.gpio		= _gpio,				\
		.active_low	= _active_low,				\
		.शेष_state	= LEDS_GPIO_DEFSTATE_OFF,		\
		.शेष_trigger	= _शेष_trigger,		\
	पूर्ण

/* Asus */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_rtn12[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(2, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "unk", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_rtn15u[] __initस्थिर = अणु
	/* TODO: Add "wlan" LED */
	BCM47XX_GPIO_LED(3, "blue", "wan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(4, "blue", "lan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "blue", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(9, "blue", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_rtn16[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "blue", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "blue", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_rtn66u[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(12, "blue", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(15, "blue", "usb", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl300g[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl320ge[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(11, "unk", "link", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl330ge[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl500g[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl500gd[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl500gpv1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl500gpv2[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(1, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl500w[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(5, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl520gc[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(1, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl520gu[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(1, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wl700ge[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON), /* Labeled "READY" (there is no "power" LED). Originally ON, flashing on USB activity. */
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_asus_wlhdd[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(2, "unk", "usb", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Belkin */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_belkin_f7d4301[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(10, "green", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(11, "amber", "power", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(12, "unk", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(13, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(14, "unk", "usb0", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(15, "unk", "usb1", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Buffalo */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_whr2_a54g54[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_whr_g125[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "bridge", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "unk", "internal", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "unk", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_whr_g54s[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "green", "bridge", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "green", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "green", "internal", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "red", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_whr_hp_g54[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "bridge", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "unk", "internal", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "unk", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_wzr_g300n[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "bridge", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "unk", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_wzr_rs_g54[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(6, "unk", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "vpn", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_buffalo_wzr_rs_g54hp[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(6, "unk", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "vpn", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Dell */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_dell_पंचांग2300[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(6, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

/* D-Link */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_dlink_dir130[] __initस्थिर = अणु
	BCM47XX_GPIO_LED_TRIGGER(0, "green", "status", 1, "timer"), /* Originally blinking when device is पढ़ोy, separated from "power" LED */
	BCM47XX_GPIO_LED(6, "blue", "unk", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_dlink_dir330[] __initस्थिर = अणु
	BCM47XX_GPIO_LED_TRIGGER(0, "green", "status", 1, "timer"), /* Originally blinking when device is पढ़ोy, separated from "power" LED */
	BCM47XX_GPIO_LED(4, "unk", "usb", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "blue", "unk", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Huawei */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_huawei_e970[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Linksys */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_e1000v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "blue", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "blue", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(2, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(4, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_e1000v21[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(5, "blue", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(6, "blue", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "amber", "wps", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(8, "blue", "wps", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_e2000v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "blue", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "blue", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(4, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_e3000v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "unk", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_e3200v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(3, "green", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_e4200v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(5, "white", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt150nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "green", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt150nv11[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "green", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt160nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt160nv3[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(2, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(4, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt300n_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "green", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt300nv11[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "green", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt310nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "blue", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(9, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt54g_generic[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "dmz", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(5, "white", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "orange", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt54g3gv2[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(2, "green", "3g", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "blue", "3g", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Verअगरied on: WRT54GS V1.0 */
अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt54g_type_0101[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "green", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "green", "dmz", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Verअगरied on: WRT54GL V1.1 */
अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt54g_type_0467[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "green", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(2, "white", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "orange", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "green", "dmz", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt610nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "usb",  1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "power",  0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "amber", "wps",  1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(9, "blue", "wps",  1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrt610nv2[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "amber", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "blue", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "unk", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_linksys_wrtsl54gs[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "green", "dmz", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(5, "white", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "orange", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Luxul */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_abr_4400_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(12, "green", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED_TRIGGER(15, "green", "status", 0, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xap_310_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED_TRIGGER(6, "green", "status", 1, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xap_1210_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED_TRIGGER(6, "green", "status", 1, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xap_1230_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(3, "blue", "2ghz", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(4, "green", "bridge", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED_TRIGGER(6, "green", "status", 1, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xap_1240_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(3, "blue", "2ghz", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(4, "green", "bridge", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED_TRIGGER(6, "green", "status", 1, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xap_1500_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED_TRIGGER(13, "green", "status", 1, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xap1500_v1_extra[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(44, "green", "5ghz", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(76, "green", "2ghz", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xbr_4400_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(12, "green", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED_TRIGGER(15, "green", "status", 0, "timer"),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xvw_p30_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED_TRIGGER(0, "blue", "status", 1, "timer"),
	BCM47XX_GPIO_LED(1, "green", "link", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xwr_600_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(3, "green", "wps", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED_TRIGGER(6, "green", "status", 1, "timer"),
	BCM47XX_GPIO_LED(9, "green", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xwr_1750_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(5, "green", "5ghz", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(12, "green", "usb", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED_TRIGGER(13, "green", "status", 0, "timer"),
	BCM47XX_GPIO_LED(15, "green", "wps", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_luxul_xwr1750_v1_extra[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(76, "green", "2ghz", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Microsoft */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_microsoft_nm700[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(6, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

/* Motorola */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_motorola_we800g[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "amber", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "unk", "unk", 1, LEDS_GPIO_DEFSTATE_OFF), /* There are only 3 LEDs: Power, Wireless and Device (ethernet) */
	BCM47XX_GPIO_LED(4, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_motorola_wr850gp[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(6, "unk", "dmz", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_motorola_wr850gv2v3[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "unk", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "unk", "diag", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Netgear */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_netgear_wndr3400v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(2, "green", "usb", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "amber", "power", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_netgear_wndr4500v1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "green", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "green", "power", 1, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "power", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(8, "green", "usb1", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(9, "green", "2ghz", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(11, "blue", "5ghz", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(14, "green", "usb2", 1, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_netgear_wnr1000_v3[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "blue", "wlan", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "green", "wps", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_netgear_wnr3500lv1[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "blue", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(1, "green", "wps", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(2, "green", "wan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(7, "amber", "power", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_netgear_wnr834bv2[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(2, "green", "power", 0, LEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_LED(3, "amber", "power", 0, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(7, "unk", "connected", 0, LEDS_GPIO_DEFSTATE_OFF),
पूर्ण;

/* Siemens */
अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_siemens_se505v2[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(0, "unk", "dmz", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(3, "unk", "wlan", 1, LEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_LED(5, "unk", "power", 1, LEDS_GPIO_DEFSTATE_ON),
पूर्ण;

/* SimpleTech */

अटल स्थिर काष्ठा gpio_led
bcm47xx_leds_simpletech_simpleshare[] __initस्थिर = अणु
	BCM47XX_GPIO_LED(1, "unk", "status", 1, LEDS_GPIO_DEFSTATE_OFF), /* "Ready" LED */
पूर्ण;

/**************************************************
 * Init
 **************************************************/

अटल काष्ठा gpio_led_platक्रमm_data bcm47xx_leds_pdata __initdata;

#घोषणा bcm47xx_set_pdata(dev_leds) करो अणु				\
	bcm47xx_leds_pdata.leds = dev_leds;				\
	bcm47xx_leds_pdata.num_leds = ARRAY_SIZE(dev_leds);		\
पूर्ण जबतक (0)

अटल काष्ठा gpio_led_platक्रमm_data bcm47xx_leds_pdata_extra __initdata = अणुपूर्ण;
#घोषणा bcm47xx_set_pdata_extra(dev_leds) करो अणु				\
	bcm47xx_leds_pdata_extra.leds = dev_leds;			\
	bcm47xx_leds_pdata_extra.num_leds = ARRAY_SIZE(dev_leds);	\
पूर्ण जबतक (0)

व्योम __init bcm47xx_leds_रेजिस्टर(व्योम)
अणु
	क्रमागत bcm47xx_board board = bcm47xx_board_get();

	चयन (board) अणु
	हाल BCM47XX_BOARD_ASUS_RTN12:
		bcm47xx_set_pdata(bcm47xx_leds_asus_rtn12);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_RTN15U:
		bcm47xx_set_pdata(bcm47xx_leds_asus_rtn15u);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_RTN16:
		bcm47xx_set_pdata(bcm47xx_leds_asus_rtn16);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_RTN66U:
		bcm47xx_set_pdata(bcm47xx_leds_asus_rtn66u);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL300G:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl300g);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL320GE:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl320ge);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL330GE:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl330ge);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500G:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl500g);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500GD:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl500gd);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500GPV1:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl500gpv1);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500GPV2:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl500gpv2);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500W:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl500w);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL520GC:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl520gc);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL520GU:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl520gu);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL700GE:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wl700ge);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WLHDD:
		bcm47xx_set_pdata(bcm47xx_leds_asus_wlhdd);
		अवरोध;

	हाल BCM47XX_BOARD_BELKIN_F7D3301:
	हाल BCM47XX_BOARD_BELKIN_F7D3302:
	हाल BCM47XX_BOARD_BELKIN_F7D4301:
	हाल BCM47XX_BOARD_BELKIN_F7D4302:
	हाल BCM47XX_BOARD_BELKIN_F7D4401:
		bcm47xx_set_pdata(bcm47xx_leds_belkin_f7d4301);
		अवरोध;

	हाल BCM47XX_BOARD_BUFFALO_WHR2_A54G54:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_whr2_a54g54);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WHR_G125:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_whr_g125);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WHR_G54S:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_whr_g54s);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WHR_HP_G54:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_whr_hp_g54);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WZR_G300N:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_wzr_g300n);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WZR_RS_G54:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_wzr_rs_g54);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WZR_RS_G54HP:
		bcm47xx_set_pdata(bcm47xx_leds_buffalo_wzr_rs_g54hp);
		अवरोध;

	हाल BCM47XX_BOARD_DELL_TM2300:
		bcm47xx_set_pdata(bcm47xx_leds_dell_पंचांग2300);
		अवरोध;

	हाल BCM47XX_BOARD_DLINK_सूची130:
		bcm47xx_set_pdata(bcm47xx_leds_dlink_dir130);
		अवरोध;
	हाल BCM47XX_BOARD_DLINK_सूची330:
		bcm47xx_set_pdata(bcm47xx_leds_dlink_dir330);
		अवरोध;

	हाल BCM47XX_BOARD_HUAWEI_E970:
		bcm47xx_set_pdata(bcm47xx_leds_huawei_e970);
		अवरोध;

	हाल BCM47XX_BOARD_LINKSYS_E1000V1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_e1000v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E1000V21:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_e1000v21);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E2000V1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_e2000v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E3000V1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_e3000v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E3200V1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_e3200v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E4200V1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_e4200v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT150NV1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt150nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT150NV11:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt150nv11);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT160NV1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt160nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT160NV3:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt160nv3);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT300N_V1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt300n_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT300NV11:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt300nv11);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT310NV1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt310nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT54G3GV2:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt54g3gv2);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0101:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt54g_type_0101);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0467:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt54g_type_0467);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0708:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt54g_generic);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT610NV1:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt610nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT610NV2:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrt610nv2);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRTSL54GS:
		bcm47xx_set_pdata(bcm47xx_leds_linksys_wrtsl54gs);
		अवरोध;

	हाल BCM47XX_BOARD_LUXUL_ABR_4400_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_abr_4400_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_310_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xap_310_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1210_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xap_1210_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1230_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xap_1230_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1240_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xap_1240_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1500_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xap_1500_v1);
		bcm47xx_set_pdata_extra(bcm47xx_leds_luxul_xap1500_v1_extra);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XBR_4400_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xbr_4400_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XVW_P30_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xvw_p30_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XWR_600_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xwr_600_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XWR_1750_V1:
		bcm47xx_set_pdata(bcm47xx_leds_luxul_xwr_1750_v1);
		bcm47xx_set_pdata_extra(bcm47xx_leds_luxul_xwr1750_v1_extra);
		अवरोध;

	हाल BCM47XX_BOARD_MICROSOFT_MN700:
		bcm47xx_set_pdata(bcm47xx_leds_microsoft_nm700);
		अवरोध;

	हाल BCM47XX_BOARD_MOTOROLA_WE800G:
		bcm47xx_set_pdata(bcm47xx_leds_motorola_we800g);
		अवरोध;
	हाल BCM47XX_BOARD_MOTOROLA_WR850GP:
		bcm47xx_set_pdata(bcm47xx_leds_motorola_wr850gp);
		अवरोध;
	हाल BCM47XX_BOARD_MOTOROLA_WR850GV2V3:
		bcm47xx_set_pdata(bcm47xx_leds_motorola_wr850gv2v3);
		अवरोध;

	हाल BCM47XX_BOARD_NETGEAR_WNDR3400V1:
		bcm47xx_set_pdata(bcm47xx_leds_netgear_wndr3400v1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNDR4500V1:
		bcm47xx_set_pdata(bcm47xx_leds_netgear_wndr4500v1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNR1000_V3:
		bcm47xx_set_pdata(bcm47xx_leds_netgear_wnr1000_v3);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNR3500L:
		bcm47xx_set_pdata(bcm47xx_leds_netgear_wnr3500lv1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNR834BV2:
		bcm47xx_set_pdata(bcm47xx_leds_netgear_wnr834bv2);
		अवरोध;

	हाल BCM47XX_BOARD_SIEMENS_SE505V2:
		bcm47xx_set_pdata(bcm47xx_leds_siemens_se505v2);
		अवरोध;

	हाल BCM47XX_BOARD_SIMPLETECH_SIMPLESHARE:
		bcm47xx_set_pdata(bcm47xx_leds_simpletech_simpleshare);
		अवरोध;

	शेष:
		pr_debug("No LEDs configuration found for this device\n");
		वापस;
	पूर्ण

	gpio_led_रेजिस्टर_device(-1, &bcm47xx_leds_pdata);
	अगर (bcm47xx_leds_pdata_extra.num_leds)
		gpio_led_रेजिस्टर_device(0, &bcm47xx_leds_pdata_extra);
पूर्ण
