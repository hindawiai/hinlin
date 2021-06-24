<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LinkStation घातer off restart driver
 * Copyright (C) 2020 Daniel Gonzथँlez Cabanelas <dgcbueu@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/phy.h>

/* Defines from the eth phy Marvell driver */
#घोषणा MII_MARVELL_COPPER_PAGE		0
#घोषणा MII_MARVELL_LED_PAGE		3
#घोषणा MII_MARVELL_WOL_PAGE		17
#घोषणा MII_MARVELL_PHY_PAGE		22

#घोषणा MII_PHY_LED_CTRL		16
#घोषणा MII_88E1318S_PHY_LED_TCR	18
#घोषणा MII_88E1318S_PHY_WOL_CTRL	16
#घोषणा MII_M1011_IEVENT		19

#घोषणा MII_88E1318S_PHY_LED_TCR_INTn_ENABLE		BIT(7)
#घोषणा MII_88E1318S_PHY_LED_TCR_FORCE_INT		BIT(15)
#घोषणा MII_88E1318S_PHY_WOL_CTRL_CLEAR_WOL_STATUS	BIT(12)
#घोषणा LED2_FORCE_ON					(0x8 << 8)
#घोषणा LEDMASK						GENMASK(11,8)

अटल काष्ठा phy_device *phydev;

अटल व्योम mvphy_reg_पूर्णांकn(u16 data)
अणु
	पूर्णांक rc = 0, saved_page;

	saved_page = phy_select_page(phydev, MII_MARVELL_LED_PAGE);
	अगर (saved_page < 0)
		जाओ err;

	/* Force manual LED2 control to let INTn work */
	__phy_modअगरy(phydev, MII_PHY_LED_CTRL, LEDMASK, LED2_FORCE_ON);

	/* Set the LED[2]/INTn pin to the required state */
	__phy_modअगरy(phydev, MII_88E1318S_PHY_LED_TCR,
		     MII_88E1318S_PHY_LED_TCR_FORCE_INT,
		     MII_88E1318S_PHY_LED_TCR_INTn_ENABLE | data);

	अगर (!data) अणु
		/* Clear पूर्णांकerrupts to ensure INTn won't be holded in high state */
		__phy_ग_लिखो(phydev, MII_MARVELL_PHY_PAGE, MII_MARVELL_COPPER_PAGE);
		__phy_पढ़ो(phydev, MII_M1011_IEVENT);

		/* If WOL was enabled and a magic packet was received beक्रमe घातering
		 * off, we won't be able to wake up by sending another magic packet.
		 * Clear WOL status.
		 */
		__phy_ग_लिखो(phydev, MII_MARVELL_PHY_PAGE, MII_MARVELL_WOL_PAGE);
		__phy_set_bits(phydev, MII_88E1318S_PHY_WOL_CTRL,
			       MII_88E1318S_PHY_WOL_CTRL_CLEAR_WOL_STATUS);
	पूर्ण
err:
	rc = phy_restore_page(phydev, saved_page, rc);
	अगर (rc < 0)
		dev_err(&phydev->mdio.dev, "Write register failed, %d\n", rc);
पूर्ण

अटल पूर्णांक linkstation_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ action, व्योम *unused)
अणु
	अगर (action == SYS_RESTART)
		mvphy_reg_पूर्णांकn(MII_88E1318S_PHY_LED_TCR_FORCE_INT);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block linkstation_reboot_nb = अणु
	.notअगरier_call = linkstation_reboot_notअगरier,
पूर्ण;

अटल व्योम linkstation_घातeroff(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&linkstation_reboot_nb);
	mvphy_reg_पूर्णांकn(0);

	kernel_restart("Power off");
पूर्ण

अटल स्थिर काष्ठा of_device_id ls_घातeroff_of_match[] = अणु
	अणु .compatible = "buffalo,ls421d" पूर्ण,
	अणु .compatible = "buffalo,ls421de" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init linkstation_घातeroff_init(व्योम)
अणु
	काष्ठा mii_bus *bus;
	काष्ठा device_node *dn;

	dn = of_find_matching_node(शून्य, ls_घातeroff_of_match);
	अगर (!dn)
		वापस -ENODEV;
	of_node_put(dn);

	dn = of_find_node_by_name(शून्य, "mdio");
	अगर (!dn)
		वापस -ENODEV;

	bus = of_mdio_find_bus(dn);
	of_node_put(dn);
	अगर (!bus)
		वापस -EPROBE_DEFER;

	phydev = phy_find_first(bus);
	put_device(&bus->dev);
	अगर (!phydev)
		वापस -EPROBE_DEFER;

	रेजिस्टर_reboot_notअगरier(&linkstation_reboot_nb);
	pm_घातer_off = linkstation_घातeroff;

	वापस 0;
पूर्ण

अटल व्योम __निकास linkstation_घातeroff_निकास(व्योम)
अणु
	pm_घातer_off = शून्य;
	unरेजिस्टर_reboot_notअगरier(&linkstation_reboot_nb);
पूर्ण

module_init(linkstation_घातeroff_init);
module_निकास(linkstation_घातeroff_निकास);

MODULE_AUTHOR("Daniel Gonzथँlez Cabanelas <dgcbueu@gmail.com>");
MODULE_DESCRIPTION("LinkStation power off driver");
MODULE_LICENSE("GPL v2");
