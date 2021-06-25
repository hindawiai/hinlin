<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2007-2010 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_PHY_H
#घोषणा EF4_PHY_H

/****************************************************************************
 * 10Xpress (SFX7101) PHY
 */
बाह्य स्थिर काष्ठा ef4_phy_operations falcon_sfx7101_phy_ops;

व्योम tenxpress_set_id_led(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode);

/****************************************************************************
 * AMCC/Quake QT202x PHYs
 */
बाह्य स्थिर काष्ठा ef4_phy_operations falcon_qt202x_phy_ops;

/* These PHYs provide various H/W control states क्रम LEDs */
#घोषणा QUAKE_LED_LINK_INVAL	(0)
#घोषणा QUAKE_LED_LINK_STAT	(1)
#घोषणा QUAKE_LED_LINK_ACT	(2)
#घोषणा QUAKE_LED_LINK_ACTSTAT	(3)
#घोषणा QUAKE_LED_OFF		(4)
#घोषणा QUAKE_LED_ON		(5)
#घोषणा QUAKE_LED_LINK_INPUT	(6)	/* Pin is an input. */
/* What link the LED tracks */
#घोषणा QUAKE_LED_TXLINK	(0)
#घोषणा QUAKE_LED_RXLINK	(8)

व्योम falcon_qt202x_set_led(काष्ठा ef4_nic *p, पूर्णांक led, पूर्णांक state);

/****************************************************************************
* Tranचयन CX4 reसमयr
*/
बाह्य स्थिर काष्ठा ef4_phy_operations falcon_txc_phy_ops;

#घोषणा TXC_GPIO_सूची_INPUT	0
#घोषणा TXC_GPIO_सूची_OUTPUT	1

व्योम falcon_txc_set_gpio_dir(काष्ठा ef4_nic *efx, पूर्णांक pin, पूर्णांक dir);
व्योम falcon_txc_set_gpio_val(काष्ठा ef4_nic *efx, पूर्णांक pin, पूर्णांक val);

#पूर्ण_अगर
