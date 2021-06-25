<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: mv88x201x.c                                                         *
 * $Revision: 1.12 $                                                         *
 * $Date: 2005/04/15 19:27:14 $                                              *
 * Description:                                                              *
 *  Marvell PHY (mv88x201x) functionality.                                   *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#समावेश "cphy.h"
#समावेश "elmer0.h"

/*
 * The 88x2010 Rev C. requires some link status रेजिस्टरs * to be पढ़ो
 * twice in order to get the right values. Future * revisions will fix
 * this problem and then this macro * can disappear.
 */
#घोषणा MV88x2010_LINK_STATUS_BUGS    1

अटल पूर्णांक led_init(काष्ठा cphy *cphy)
अणु
	/* Setup the LED रेजिस्टरs so we can turn on/off.
	 * Writing these bits maps control to another
	 * रेजिस्टर. mmd(0x1) addr(0x7)
	 */
	cphy_mdio_ग_लिखो(cphy, MDIO_MMD_PCS, 0x8304, 0xdddd);
	वापस 0;
पूर्ण

अटल पूर्णांक led_link(काष्ठा cphy *cphy, u32 करो_enable)
अणु
	u32 led = 0;
#घोषणा LINK_ENABLE_BIT 0x1

	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_CTRL2, &led);

	अगर (करो_enable & LINK_ENABLE_BIT) अणु
		led |= LINK_ENABLE_BIT;
		cphy_mdio_ग_लिखो(cphy, MDIO_MMD_PMAPMD, MDIO_CTRL2, led);
	पूर्ण अन्यथा अणु
		led &= ~LINK_ENABLE_BIT;
		cphy_mdio_ग_लिखो(cphy, MDIO_MMD_PMAPMD, MDIO_CTRL2, led);
	पूर्ण
	वापस 0;
पूर्ण

/* Port Reset */
अटल पूर्णांक mv88x201x_reset(काष्ठा cphy *cphy, पूर्णांक रुको)
अणु
	/* This can be करोne through रेजिस्टरs.  It is not required since
	 * a full chip reset is used.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक mv88x201x_पूर्णांकerrupt_enable(काष्ठा cphy *cphy)
अणु
	/* Enable PHY LASI पूर्णांकerrupts. */
	cphy_mdio_ग_लिखो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL,
			MDIO_PMA_LASI_LSALARM);

	/* Enable Marvell पूर्णांकerrupts through Elmer0. */
	अगर (t1_is_asic(cphy->adapter)) अणु
		u32 elmer;

		t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_INT_ENABLE, &elmer);
		elmer |= ELMER0_GP_BIT6;
		t1_tpi_ग_लिखो(cphy->adapter, A_ELMER0_INT_ENABLE, elmer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mv88x201x_पूर्णांकerrupt_disable(काष्ठा cphy *cphy)
अणु
	/* Disable PHY LASI पूर्णांकerrupts. */
	cphy_mdio_ग_लिखो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL, 0x0);

	/* Disable Marvell पूर्णांकerrupts through Elmer0. */
	अगर (t1_is_asic(cphy->adapter)) अणु
		u32 elmer;

		t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_INT_ENABLE, &elmer);
		elmer &= ~ELMER0_GP_BIT6;
		t1_tpi_ग_लिखो(cphy->adapter, A_ELMER0_INT_ENABLE, elmer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mv88x201x_पूर्णांकerrupt_clear(काष्ठा cphy *cphy)
अणु
	u32 elmer;
	u32 val;

#अगर_घोषित MV88x2010_LINK_STATUS_BUGS
	/* Required to पढ़ो twice beक्रमe clear takes affect. */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_RXSTAT, &val);
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_TXSTAT, &val);
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_STAT, &val);

	/* Read this रेजिस्टर after the others above it अन्यथा
	 * the रेजिस्टर करोesn't clear correctly.
	 */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
#पूर्ण_अगर

	/* Clear link status. */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
	/* Clear PHY LASI पूर्णांकerrupts. */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_STAT, &val);

#अगर_घोषित MV88x2010_LINK_STATUS_BUGS
	/* Do it again. */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_RXSTAT, &val);
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_TXSTAT, &val);
#पूर्ण_अगर

	/* Clear Marvell पूर्णांकerrupts through Elmer0. */
	अगर (t1_is_asic(cphy->adapter)) अणु
		t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_INT_CAUSE, &elmer);
		elmer |= ELMER0_GP_BIT6;
		t1_tpi_ग_लिखो(cphy->adapter, A_ELMER0_INT_CAUSE, elmer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mv88x201x_पूर्णांकerrupt_handler(काष्ठा cphy *cphy)
अणु
	/* Clear पूर्णांकerrupts */
	mv88x201x_पूर्णांकerrupt_clear(cphy);

	/* We have only enabled link change पूर्णांकerrupts and so
	 * cphy_cause must be a link change पूर्णांकerrupt.
	 */
	वापस cphy_cause_link_change;
पूर्ण

अटल पूर्णांक mv88x201x_set_loopback(काष्ठा cphy *cphy, पूर्णांक on)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mv88x201x_get_link_status(काष्ठा cphy *cphy, पूर्णांक *link_ok,
				     पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	u32 val = 0;

	अगर (link_ok) अणु
		/* Read link status. */
		cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
		val &= MDIO_STAT1_LSTATUS;
		*link_ok = (val == MDIO_STAT1_LSTATUS);
		/* Turn on/off Link LED */
		led_link(cphy, *link_ok);
	पूर्ण
	अगर (speed)
		*speed = SPEED_10000;
	अगर (duplex)
		*duplex = DUPLEX_FULL;
	अगर (fc)
		*fc = PAUSE_RX | PAUSE_TX;
	वापस 0;
पूर्ण

अटल व्योम mv88x201x_destroy(काष्ठा cphy *cphy)
अणु
	kमुक्त(cphy);
पूर्ण

अटल स्थिर काष्ठा cphy_ops mv88x201x_ops = अणु
	.destroy           = mv88x201x_destroy,
	.reset             = mv88x201x_reset,
	.पूर्णांकerrupt_enable  = mv88x201x_पूर्णांकerrupt_enable,
	.पूर्णांकerrupt_disable = mv88x201x_पूर्णांकerrupt_disable,
	.पूर्णांकerrupt_clear   = mv88x201x_पूर्णांकerrupt_clear,
	.पूर्णांकerrupt_handler = mv88x201x_पूर्णांकerrupt_handler,
	.get_link_status   = mv88x201x_get_link_status,
	.set_loopback      = mv88x201x_set_loopback,
	.mmds              = (MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS |
			      MDIO_DEVS_PHYXS | MDIO_DEVS_WIS),
पूर्ण;

अटल काष्ठा cphy *mv88x201x_phy_create(काष्ठा net_device *dev, पूर्णांक phy_addr,
					 स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	u32 val;
	काष्ठा cphy *cphy = kzalloc(माप(*cphy), GFP_KERNEL);

	अगर (!cphy)
		वापस शून्य;

	cphy_init(cphy, dev, phy_addr, &mv88x201x_ops, mdio_ops);

	/* Commands the PHY to enable XFP's घड़ी. */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PCS, 0x8300, &val);
	cphy_mdio_ग_लिखो(cphy, MDIO_MMD_PCS, 0x8300, val | 1);

	/* Clear link status. Required because of a bug in the PHY.  */
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_STAT2, &val);
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PCS, MDIO_STAT2, &val);

	/* Allows क्रम Link,Ack LED turn on/off */
	led_init(cphy);
	वापस cphy;
पूर्ण

/* Chip Reset */
अटल पूर्णांक mv88x201x_phy_reset(adapter_t *adapter)
अणु
	u32 val;

	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~4;
	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	msleep(100);

	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val | 4);
	msleep(1000);

	/* Now lets enable the Laser. Delay 100us */
	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val |= 0x8000;
	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(100);
	वापस 0;
पूर्ण

स्थिर काष्ठा gphy t1_mv88x201x_ops = अणु
	.create = mv88x201x_phy_create,
	.reset = mv88x201x_phy_reset
पूर्ण;
