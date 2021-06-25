<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "bcm47xx_private.h"

#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <bcm47xx_board.h>
#समावेश <bcm47xx.h>

/**************************************************
 * Database
 **************************************************/

#घोषणा BCM47XX_GPIO_KEY(_gpio, _code)					\
	अणु								\
		.code		= _code,				\
		.gpio		= _gpio,				\
		.active_low	= 1,					\
	पूर्ण

#घोषणा BCM47XX_GPIO_KEY_H(_gpio, _code)				\
	अणु								\
		.code		= _code,				\
		.gpio		= _gpio,				\
	पूर्ण

/* Asus */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_rtn12[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(1, KEY_RESTART),
	BCM47XX_GPIO_KEY(4, BTN_0), /* Router mode */
	BCM47XX_GPIO_KEY(5, BTN_1), /* Repeater mode */
	BCM47XX_GPIO_KEY(6, BTN_2), /* AP mode */
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_rtn16[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(8, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_rtn66u[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(9, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl300g[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl320ge[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl330ge[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl500g[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl500gd[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl500gpv1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_RESTART),
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl500gpv2[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_RESTART),
	BCM47XX_GPIO_KEY(3, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl500w[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY_H(6, KEY_RESTART),
	BCM47XX_GPIO_KEY_H(7, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl520gc[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_RESTART),
	BCM47XX_GPIO_KEY(3, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl520gu[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_RESTART),
	BCM47XX_GPIO_KEY(3, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wl700ge[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_POWER), /* Hard disk घातer चयन */
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON), /* EZSetup */
	BCM47XX_GPIO_KEY(6, KEY_COPY), /* Copy data from USB to पूर्णांकernal disk */
	BCM47XX_GPIO_KEY(7, KEY_RESTART), /* Hard reset */
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_asus_wlhdd[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

/* Huawei */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_huawei_e970[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

/* Belkin */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_belkin_f7d4301[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
	BCM47XX_GPIO_KEY(8, KEY_WPS_BUTTON),
पूर्ण;

/* Buffalo */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_whr2_a54g54[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_whr_g125[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
	BCM47XX_GPIO_KEY(5, BTN_0), /* Router / AP mode swtich */
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_whr_g54s[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY_H(4, KEY_RESTART),
	BCM47XX_GPIO_KEY(5, BTN_0), /* Router / AP mode swtich */
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_whr_hp_g54[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
	BCM47XX_GPIO_KEY(5, BTN_0), /* Router / AP mode swtich */
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_wzr_g300n[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_wzr_rs_g54[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_buffalo_wzr_rs_g54hp[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
पूर्ण;

/* Dell */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_dell_पंचांग2300[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_RESTART),
पूर्ण;

/* D-Link */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_dlink_dir130[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(3, KEY_RESTART),
	BCM47XX_GPIO_KEY(7, KEY_UNKNOWN),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_dlink_dir330[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(3, KEY_RESTART),
	BCM47XX_GPIO_KEY(7, KEY_UNKNOWN),
पूर्ण;

/* Linksys */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_e1000v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_e1000v21[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(9, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(10, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_e2000v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(8, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_e3000v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_e3200v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_RESTART),
	BCM47XX_GPIO_KEY(8, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_e4200v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt150nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt150nv11[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt160nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt160nv3[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt300n_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt300nv11[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_UNKNOWN),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt310nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
	BCM47XX_GPIO_KEY(8, KEY_UNKNOWN),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt54g3gv2[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_WIMAX),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt54g_generic[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt610nv1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
	BCM47XX_GPIO_KEY(8, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrt610nv2[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_linksys_wrtsl54gs[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

/* Luxul */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_abr_4400_v1[] = अणु
	BCM47XX_GPIO_KEY(14, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xap_310_v1[] = अणु
	BCM47XX_GPIO_KEY(20, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xap_1210_v1[] = अणु
	BCM47XX_GPIO_KEY(8, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xap_1230_v1[] = अणु
	BCM47XX_GPIO_KEY(8, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xap_1240_v1[] = अणु
	BCM47XX_GPIO_KEY(8, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xap_1500_v1[] = अणु
	BCM47XX_GPIO_KEY(14, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xbr_4400_v1[] = अणु
	BCM47XX_GPIO_KEY(14, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xvw_p30_v1[] = अणु
	BCM47XX_GPIO_KEY(20, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xwr_600_v1[] = अणु
	BCM47XX_GPIO_KEY(8, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_luxul_xwr_1750_v1[] = अणु
	BCM47XX_GPIO_KEY(14, KEY_RESTART),
पूर्ण;

/* Microsoft */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_microsoft_nm700[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(7, KEY_RESTART),
पूर्ण;

/* Motorola */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_motorola_we800g[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_motorola_wr850gp[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_motorola_wr850gv2v3[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(5, KEY_RESTART),
पूर्ण;

/* Netgear */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_r6200_v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_RFKILL),
	BCM47XX_GPIO_KEY(3, KEY_RESTART),
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wndr3400v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
	BCM47XX_GPIO_KEY(6, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(8, KEY_RFKILL),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wndr3400_v3[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(12, KEY_RESTART),
	BCM47XX_GPIO_KEY(23, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wndr3700v3[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_RFKILL),
	BCM47XX_GPIO_KEY(3, KEY_RESTART),
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wndr4500v1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(5, KEY_RFKILL),
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wnr1000_v3[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(2, KEY_WPS_BUTTON),
	BCM47XX_GPIO_KEY(3, KEY_RESTART),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wnr3500lv1[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(4, KEY_RESTART),
	BCM47XX_GPIO_KEY(6, KEY_WPS_BUTTON),
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_netgear_wnr834bv2[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(6, KEY_RESTART),
पूर्ण;

/* SimpleTech */

अटल स्थिर काष्ठा gpio_keys_button
bcm47xx_buttons_simpletech_simpleshare[] __initस्थिर = अणु
	BCM47XX_GPIO_KEY(0, KEY_RESTART),
पूर्ण;

/**************************************************
 * Init
 **************************************************/

अटल काष्ठा gpio_keys_platक्रमm_data bcm47xx_button_pdata;

अटल काष्ठा platक्रमm_device bcm47xx_buttons_gpio_keys = अणु
	.name = "gpio-keys",
	.dev = अणु
		.platक्रमm_data = &bcm47xx_button_pdata,
	पूर्ण
पूर्ण;

/* Copy data from __initस्थिर */
अटल पूर्णांक __init bcm47xx_buttons_copy(स्थिर काष्ठा gpio_keys_button *buttons,
				       माप_प्रकार nbuttons)
अणु
	माप_प्रकार size = nbuttons * माप(*buttons);

	bcm47xx_button_pdata.buttons = kmemdup(buttons, size, GFP_KERNEL);
	अगर (!bcm47xx_button_pdata.buttons)
		वापस -ENOMEM;
	bcm47xx_button_pdata.nbuttons = nbuttons;

	वापस 0;
पूर्ण

#घोषणा bcm47xx_copy_bdata(dev_buttons)					\
	bcm47xx_buttons_copy(dev_buttons, ARRAY_SIZE(dev_buttons));

पूर्णांक __init bcm47xx_buttons_रेजिस्टर(व्योम)
अणु
	क्रमागत bcm47xx_board board = bcm47xx_board_get();
	पूर्णांक err;

	चयन (board) अणु
	हाल BCM47XX_BOARD_ASUS_RTN12:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_rtn12);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_RTN16:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_rtn16);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_RTN66U:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_rtn66u);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL300G:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl300g);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL320GE:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl320ge);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL330GE:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl330ge);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500G:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl500g);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500GD:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl500gd);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500GPV1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl500gpv1);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500GPV2:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl500gpv2);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL500W:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl500w);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL520GC:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl520gc);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL520GU:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl520gu);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WL700GE:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wl700ge);
		अवरोध;
	हाल BCM47XX_BOARD_ASUS_WLHDD:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_asus_wlhdd);
		अवरोध;

	हाल BCM47XX_BOARD_BELKIN_F7D3301:
	हाल BCM47XX_BOARD_BELKIN_F7D3302:
	हाल BCM47XX_BOARD_BELKIN_F7D4301:
	हाल BCM47XX_BOARD_BELKIN_F7D4302:
	हाल BCM47XX_BOARD_BELKIN_F7D4401:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_belkin_f7d4301);
		अवरोध;

	हाल BCM47XX_BOARD_BUFFALO_WHR2_A54G54:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_whr2_a54g54);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WHR_G125:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_whr_g125);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WHR_G54S:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_whr_g54s);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WHR_HP_G54:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_whr_hp_g54);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WZR_G300N:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_wzr_g300n);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WZR_RS_G54:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_wzr_rs_g54);
		अवरोध;
	हाल BCM47XX_BOARD_BUFFALO_WZR_RS_G54HP:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_buffalo_wzr_rs_g54hp);
		अवरोध;

	हाल BCM47XX_BOARD_DELL_TM2300:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_dell_पंचांग2300);
		अवरोध;

	हाल BCM47XX_BOARD_DLINK_सूची130:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_dlink_dir130);
		अवरोध;
	हाल BCM47XX_BOARD_DLINK_सूची330:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_dlink_dir330);
		अवरोध;

	हाल BCM47XX_BOARD_HUAWEI_E970:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_huawei_e970);
		अवरोध;

	हाल BCM47XX_BOARD_LINKSYS_E1000V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_e1000v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E1000V21:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_e1000v21);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E2000V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_e2000v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E3000V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_e3000v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E3200V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_e3200v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_E4200V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_e4200v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT150NV1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt150nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT150NV11:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt150nv11);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT160NV1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt160nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT160NV3:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt160nv3);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT300N_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt300n_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT300NV11:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt300nv11);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT310NV1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt310nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT54G3GV2:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt54g3gv2);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0101:
	हाल BCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0467:
	हाल BCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0708:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt54g_generic);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT610NV1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt610nv1);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRT610NV2:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrt610nv2);
		अवरोध;
	हाल BCM47XX_BOARD_LINKSYS_WRTSL54GS:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_linksys_wrtsl54gs);
		अवरोध;

	हाल BCM47XX_BOARD_LUXUL_ABR_4400_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_abr_4400_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_310_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xap_310_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1210_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xap_1210_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1230_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xap_1230_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1240_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xap_1240_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XAP_1500_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xap_1500_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XBR_4400_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xbr_4400_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XVW_P30_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xvw_p30_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XWR_600_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xwr_600_v1);
		अवरोध;
	हाल BCM47XX_BOARD_LUXUL_XWR_1750_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_luxul_xwr_1750_v1);
		अवरोध;

	हाल BCM47XX_BOARD_MICROSOFT_MN700:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_microsoft_nm700);
		अवरोध;

	हाल BCM47XX_BOARD_MOTOROLA_WE800G:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_motorola_we800g);
		अवरोध;
	हाल BCM47XX_BOARD_MOTOROLA_WR850GP:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_motorola_wr850gp);
		अवरोध;
	हाल BCM47XX_BOARD_MOTOROLA_WR850GV2V3:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_motorola_wr850gv2v3);
		अवरोध;

	हाल BCM47XX_BOARD_NETGEAR_R6200_V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_r6200_v1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNDR3400V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wndr3400v1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNDR3400_V3:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wndr3400_v3);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNDR3700V3:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wndr3700v3);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNDR4500V1:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wndr4500v1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNR1000_V3:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wnr1000_v3);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNR3500L:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wnr3500lv1);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNR834BV2:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_netgear_wnr834bv2);
		अवरोध;

	हाल BCM47XX_BOARD_SIMPLETECH_SIMPLESHARE:
		err = bcm47xx_copy_bdata(bcm47xx_buttons_simpletech_simpleshare);
		अवरोध;

	शेष:
		pr_debug("No buttons configuration found for this device\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (err)
		वापस -ENOMEM;

	err = platक्रमm_device_रेजिस्टर(&bcm47xx_buttons_gpio_keys);
	अगर (err) अणु
		pr_err("Failed to register platform device: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
