<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: cphy.h                                                              *
 * $Revision: 1.7 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
 * Description:                                                              *
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

#अगर_अघोषित _CXGB_CPHY_H_
#घोषणा _CXGB_CPHY_H_

#समावेश "common.h"

काष्ठा mdio_ops अणु
	व्योम (*init)(adapter_t *adapter, स्थिर काष्ठा board_info *bi);
	पूर्णांक  (*पढ़ो)(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
		     u16 reg_addr);
	पूर्णांक  (*ग_लिखो)(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
		      u16 reg_addr, u16 val);
	अचिन्हित mode_support;
पूर्ण;

/* PHY पूर्णांकerrupt types */
क्रमागत अणु
	cphy_cause_link_change = 0x1,
	cphy_cause_error = 0x2,
	cphy_cause_fअगरo_error = 0x3
पूर्ण;

क्रमागत अणु
	PHY_LINK_UP = 0x1,
	PHY_AUTONEG_RDY = 0x2,
	PHY_AUTONEG_EN = 0x4
पूर्ण;

काष्ठा cphy;

/* PHY operations */
काष्ठा cphy_ops अणु
	व्योम (*destroy)(काष्ठा cphy *);
	पूर्णांक (*reset)(काष्ठा cphy *, पूर्णांक रुको);

	पूर्णांक (*पूर्णांकerrupt_enable)(काष्ठा cphy *);
	पूर्णांक (*पूर्णांकerrupt_disable)(काष्ठा cphy *);
	पूर्णांक (*पूर्णांकerrupt_clear)(काष्ठा cphy *);
	पूर्णांक (*पूर्णांकerrupt_handler)(काष्ठा cphy *);

	पूर्णांक (*स्वतःneg_enable)(काष्ठा cphy *);
	पूर्णांक (*स्वतःneg_disable)(काष्ठा cphy *);
	पूर्णांक (*स्वतःneg_restart)(काष्ठा cphy *);

	पूर्णांक (*advertise)(काष्ठा cphy *phy, अचिन्हित पूर्णांक advertise_map);
	पूर्णांक (*set_loopback)(काष्ठा cphy *, पूर्णांक on);
	पूर्णांक (*set_speed_duplex)(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex);
	पूर्णांक (*get_link_status)(काष्ठा cphy *phy, पूर्णांक *link_ok, पूर्णांक *speed,
			       पूर्णांक *duplex, पूर्णांक *fc);

	u32 mmds;
पूर्ण;

/* A PHY instance */
काष्ठा cphy अणु
	पूर्णांक state;	/* Link status state machine */
	adapter_t *adapter;                  /* associated adapter */

	काष्ठा delayed_work phy_update;

	u16 bmsr;
	पूर्णांक count;
	पूर्णांक act_count;
	पूर्णांक act_on;

	u32 elmer_gpo;

	स्थिर काष्ठा cphy_ops *ops;            /* PHY operations */
	काष्ठा mdio_अगर_info mdio;
	काष्ठा cphy_instance *instance;
पूर्ण;

/* Convenience MDIO पढ़ो/ग_लिखो wrappers */
अटल अंतरभूत पूर्णांक cphy_mdio_पढ़ो(काष्ठा cphy *cphy, पूर्णांक mmd, पूर्णांक reg,
				 अचिन्हित पूर्णांक *valp)
अणु
	पूर्णांक rc = cphy->mdio.mdio_पढ़ो(cphy->mdio.dev, cphy->mdio.prtad, mmd,
				      reg);
	*valp = (rc >= 0) ? rc : -1;
	वापस (rc >= 0) ? 0 : rc;
पूर्ण

अटल अंतरभूत पूर्णांक cphy_mdio_ग_लिखो(काष्ठा cphy *cphy, पूर्णांक mmd, पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	वापस cphy->mdio.mdio_ग_लिखो(cphy->mdio.dev, cphy->mdio.prtad, mmd,
				     reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक simple_mdio_पढ़ो(काष्ठा cphy *cphy, पूर्णांक reg,
				   अचिन्हित पूर्णांक *valp)
अणु
	वापस cphy_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, reg, valp);
पूर्ण

अटल अंतरभूत पूर्णांक simple_mdio_ग_लिखो(काष्ठा cphy *cphy, पूर्णांक reg,
				    अचिन्हित पूर्णांक val)
अणु
	वापस cphy_mdio_ग_लिखो(cphy, MDIO_DEVAD_NONE, reg, val);
पूर्ण

/* Convenience initializer */
अटल अंतरभूत व्योम cphy_init(काष्ठा cphy *phy, काष्ठा net_device *dev,
			     पूर्णांक phy_addr, स्थिर काष्ठा cphy_ops *phy_ops,
			     स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	काष्ठा adapter *adapter = netdev_priv(dev);
	phy->adapter = adapter;
	phy->ops     = phy_ops;
	अगर (mdio_ops) अणु
		phy->mdio.prtad = phy_addr;
		phy->mdio.mmds = phy_ops->mmds;
		phy->mdio.mode_support = mdio_ops->mode_support;
		phy->mdio.mdio_पढ़ो = mdio_ops->पढ़ो;
		phy->mdio.mdio_ग_लिखो = mdio_ops->ग_लिखो;
	पूर्ण
	phy->mdio.dev = dev;
पूर्ण

/* Operations of the PHY-instance factory */
काष्ठा gphy अणु
	/* Conकाष्ठा a PHY instance with the given PHY address */
	काष्ठा cphy *(*create)(काष्ठा net_device *dev, पूर्णांक phy_addr,
			       स्थिर काष्ठा mdio_ops *mdio_ops);

	/*
	 * Reset the PHY chip.  This resets the whole PHY chip, not inभागidual
	 * ports.
	 */
	पूर्णांक (*reset)(adapter_t *adapter);
पूर्ण;

बाह्य स्थिर काष्ठा gphy t1_my3126_ops;
बाह्य स्थिर काष्ठा gphy t1_mv88e1xxx_ops;
बाह्य स्थिर काष्ठा gphy t1_vsc8244_ops;
बाह्य स्थिर काष्ठा gphy t1_mv88x201x_ops;

#पूर्ण_अगर /* _CXGB_CPHY_H_ */
