<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2019 NXP */

#अगर_अघोषित _FSL_ENETC_MDIO_H_
#घोषणा _FSL_ENETC_MDIO_H_

#समावेश <linux/phy.h>

/* PCS रेजिस्टरs */
#घोषणा ENETC_PCS_LINK_TIMER1			0x12
#घोषणा ENETC_PCS_LINK_TIMER1_VAL		0x06a0
#घोषणा ENETC_PCS_LINK_TIMER2			0x13
#घोषणा ENETC_PCS_LINK_TIMER2_VAL		0x0003
#घोषणा ENETC_PCS_IF_MODE			0x14
#घोषणा ENETC_PCS_IF_MODE_SGMII_EN		BIT(0)
#घोषणा ENETC_PCS_IF_MODE_USE_SGMII_AN		BIT(1)
#घोषणा ENETC_PCS_IF_MODE_SGMII_SPEED(x)	(((x) << 2) & GENMASK(3, 2))
#घोषणा ENETC_PCS_IF_MODE_DUPLEX_HALF		BIT(3)

/* Not a mistake, the SerDes PLL needs to be set at 3.125 GHz by Reset
 * Configuration Word (RCW, outside Linux control) क्रम 2.5G SGMII mode. The PCS
 * still thinks it's at gigabit.
 */
क्रमागत enetc_pcs_speed अणु
	ENETC_PCS_SPEED_10	= 0,
	ENETC_PCS_SPEED_100	= 1,
	ENETC_PCS_SPEED_1000	= 2,
	ENETC_PCS_SPEED_2500	= 2,
पूर्ण;

काष्ठा enetc_hw;

काष्ठा enetc_mdio_priv अणु
	काष्ठा enetc_hw *hw;
	पूर्णांक mdio_base;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_FSL_ENETC_MDIO)

पूर्णांक enetc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum);
पूर्णांक enetc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum, u16 value);
काष्ठा enetc_hw *enetc_hw_alloc(काष्ठा device *dev, व्योम __iomem *port_regs);

#अन्यथा

अटल अंतरभूत पूर्णांक enetc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत पूर्णांक enetc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum,
				   u16 value)
अणु वापस -EINVAL; पूर्ण
काष्ठा enetc_hw *enetc_hw_alloc(काष्ठा device *dev, व्योम __iomem *port_regs)
अणु वापस ERR_PTR(-EINVAL); पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
