<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Driver क्रम Asix PHYs
 *
 * Author: Michael Schmitz <schmitzmic@gmail.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

#घोषणा PHY_ID_ASIX_AX88796B		0x003b1841

MODULE_DESCRIPTION("Asix PHY driver");
MODULE_AUTHOR("Michael Schmitz <schmitzmic@gmail.com>");
MODULE_LICENSE("GPL");

/**
 * asix_soft_reset - software reset the PHY via BMCR_RESET bit
 * @phydev: target phy_device काष्ठा
 *
 * Description: Perक्रमm a software PHY reset using the standard
 * BMCR_RESET bit and poll क्रम the reset bit to be cleared.
 * Toggle BMCR_RESET bit off to accommodate broken AX8796B PHY implementation
 * such as used on the Inभागidual Computers' X-Surf 100 Zorro card.
 *
 * Returns: 0 on success, < 0 on failure
 */
अटल पूर्णांक asix_soft_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Asix PHY won't reset unless reset bit toggles */
	ret = phy_ग_लिखो(phydev, MII_BMCR, 0);
	अगर (ret < 0)
		वापस ret;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल काष्ठा phy_driver asix_driver[] = अणु अणु
	.phy_id		= PHY_ID_ASIX_AX88796B,
	.name		= "Asix Electronics AX88796B",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.soft_reset	= asix_soft_reset,
पूर्ण पूर्ण;

module_phy_driver(asix_driver);

अटल काष्ठा mdio_device_id __maybe_unused asix_tbl[] = अणु
	अणु PHY_ID_ASIX_AX88796B, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, asix_tbl);
