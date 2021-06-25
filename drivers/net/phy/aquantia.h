<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* HWMON driver क्रम Aquantia PHY
 *
 * Author: Nikita Yushchenko <nikita.yoush@cogentembedded.com>
 * Author: Andrew Lunn <andrew@lunn.ch>
 * Author: Heiner Kallweit <hkallweit1@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/phy.h>

#अगर IS_REACHABLE(CONFIG_HWMON)
पूर्णांक aqr_hwmon_probe(काष्ठा phy_device *phydev);
#अन्यथा
अटल अंतरभूत पूर्णांक aqr_hwmon_probe(काष्ठा phy_device *phydev) अणु वापस 0; पूर्ण
#पूर्ण_अगर
