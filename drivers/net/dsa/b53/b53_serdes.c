<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause
/*
 * Northstar Plus चयन SerDes/SGMII PHY मुख्य logic
 *
 * Copyright (C) 2018 Florian Fainelli <f.fainelli@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>
#समावेश <net/dsa.h>

#समावेश "b53_priv.h"
#समावेश "b53_serdes.h"
#समावेश "b53_regs.h"

अटल व्योम b53_serdes_ग_लिखो_blk(काष्ठा b53_device *dev, u8 offset, u16 block,
				 u16 value)
अणु
	b53_ग_लिखो16(dev, B53_SERDES_PAGE, B53_SERDES_BLKADDR, block);
	b53_ग_लिखो16(dev, B53_SERDES_PAGE, offset, value);
पूर्ण

अटल u16 b53_serdes_पढ़ो_blk(काष्ठा b53_device *dev, u8 offset, u16 block)
अणु
	u16 value;

	b53_ग_लिखो16(dev, B53_SERDES_PAGE, B53_SERDES_BLKADDR, block);
	b53_पढ़ो16(dev, B53_SERDES_PAGE, offset, &value);

	वापस value;
पूर्ण

अटल व्योम b53_serdes_set_lane(काष्ठा b53_device *dev, u8 lane)
अणु
	अगर (dev->serdes_lane == lane)
		वापस;

	WARN_ON(lane > 1);

	b53_serdes_ग_लिखो_blk(dev, B53_SERDES_LANE,
			     SERDES_XGXSBLK0_BLOCKADDRESS, lane);
	dev->serdes_lane = lane;
पूर्ण

अटल व्योम b53_serdes_ग_लिखो(काष्ठा b53_device *dev, u8 lane,
			     u8 offset, u16 block, u16 value)
अणु
	b53_serdes_set_lane(dev, lane);
	b53_serdes_ग_लिखो_blk(dev, offset, block, value);
पूर्ण

अटल u16 b53_serdes_पढ़ो(काष्ठा b53_device *dev, u8 lane,
			   u8 offset, u16 block)
अणु
	b53_serdes_set_lane(dev, lane);
	वापस b53_serdes_पढ़ो_blk(dev, offset, block);
पूर्ण

व्योम b53_serdes_config(काष्ठा b53_device *dev, पूर्णांक port, अचिन्हित पूर्णांक mode,
		       स्थिर काष्ठा phylink_link_state *state)
अणु
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 reg;

	अगर (lane == B53_INVALID_LANE)
		वापस;

	reg = b53_serdes_पढ़ो(dev, lane, B53_SERDES_DIGITAL_CONTROL(1),
			      SERDES_DIGITAL_BLK);
	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX)
		reg |= FIBER_MODE_1000X;
	अन्यथा
		reg &= ~FIBER_MODE_1000X;
	b53_serdes_ग_लिखो(dev, lane, B53_SERDES_DIGITAL_CONTROL(1),
			 SERDES_DIGITAL_BLK, reg);
पूर्ण
EXPORT_SYMBOL(b53_serdes_config);

व्योम b53_serdes_an_restart(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 reg;

	अगर (lane == B53_INVALID_LANE)
		वापस;

	reg = b53_serdes_पढ़ो(dev, lane, B53_SERDES_MII_REG(MII_BMCR),
			      SERDES_MII_BLK);
	reg |= BMCR_ANRESTART;
	b53_serdes_ग_लिखो(dev, lane, B53_SERDES_MII_REG(MII_BMCR),
			 SERDES_MII_BLK, reg);
पूर्ण
EXPORT_SYMBOL(b53_serdes_an_restart);

पूर्णांक b53_serdes_link_state(काष्ठा b53_device *dev, पूर्णांक port,
			  काष्ठा phylink_link_state *state)
अणु
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 dig, bmsr;

	अगर (lane == B53_INVALID_LANE)
		वापस 1;

	dig = b53_serdes_पढ़ो(dev, lane, B53_SERDES_DIGITAL_STATUS,
			      SERDES_DIGITAL_BLK);
	bmsr = b53_serdes_पढ़ो(dev, lane, B53_SERDES_MII_REG(MII_BMSR),
			       SERDES_MII_BLK);

	चयन ((dig >> SPEED_STATUS_SHIFT) & SPEED_STATUS_MASK) अणु
	हाल SPEED_STATUS_10:
		state->speed = SPEED_10;
		अवरोध;
	हाल SPEED_STATUS_100:
		state->speed = SPEED_100;
		अवरोध;
	हाल SPEED_STATUS_1000:
		state->speed = SPEED_1000;
		अवरोध;
	शेष:
	हाल SPEED_STATUS_2500:
		state->speed = SPEED_2500;
		अवरोध;
	पूर्ण

	state->duplex = dig & DUPLEX_STATUS ? DUPLEX_FULL : DUPLEX_HALF;
	state->an_complete = !!(bmsr & BMSR_ANEGCOMPLETE);
	state->link = !!(dig & LINK_STATUS);
	अगर (dig & PAUSE_RESOLUTION_RX_SIDE)
		state->छोड़ो |= MLO_PAUSE_RX;
	अगर (dig & PAUSE_RESOLUTION_TX_SIDE)
		state->छोड़ो |= MLO_PAUSE_TX;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_serdes_link_state);

व्योम b53_serdes_link_set(काष्ठा b53_device *dev, पूर्णांक port, अचिन्हित पूर्णांक mode,
			 phy_पूर्णांकerface_t पूर्णांकerface, bool link_up)
अणु
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 reg;

	अगर (lane == B53_INVALID_LANE)
		वापस;

	reg = b53_serdes_पढ़ो(dev, lane, B53_SERDES_MII_REG(MII_BMCR),
			      SERDES_MII_BLK);
	अगर (link_up)
		reg &= ~BMCR_PDOWN;
	अन्यथा
		reg |= BMCR_PDOWN;
	b53_serdes_ग_लिखो(dev, lane, B53_SERDES_MII_REG(MII_BMCR),
			 SERDES_MII_BLK, reg);
पूर्ण
EXPORT_SYMBOL(b53_serdes_link_set);

व्योम b53_serdes_phylink_validate(काष्ठा b53_device *dev, पूर्णांक port,
				 अचिन्हित दीर्घ *supported,
				 काष्ठा phylink_link_state *state)
अणु
	u8 lane = b53_serdes_map_lane(dev, port);

	अगर (lane == B53_INVALID_LANE)
		वापस;

	चयन (lane) अणु
	हाल 0:
		phylink_set(supported, 2500baseX_Full);
		fallthrough;
	हाल 1:
		phylink_set(supported, 1000baseX_Full);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(b53_serdes_phylink_validate);

पूर्णांक b53_serdes_init(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 id0, msb, lsb;

	अगर (lane == B53_INVALID_LANE)
		वापस -EINVAL;

	id0 = b53_serdes_पढ़ो(dev, lane, B53_SERDES_ID0, SERDES_ID0);
	msb = b53_serdes_पढ़ो(dev, lane, B53_SERDES_MII_REG(MII_PHYSID1),
			      SERDES_MII_BLK);
	lsb = b53_serdes_पढ़ो(dev, lane, B53_SERDES_MII_REG(MII_PHYSID2),
			      SERDES_MII_BLK);
	अगर (id0 == 0 || id0 == 0xffff) अणु
		dev_err(dev->dev, "SerDes not initialized, check settings\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(dev->dev,
		 "SerDes lane %d, model: %d, rev %c%d (OUI: 0x%08x)\n",
		 lane, id0 & SERDES_ID0_MODEL_MASK,
		 (id0 >> SERDES_ID0_REV_LETTER_SHIFT) + 0x41,
		 (id0 >> SERDES_ID0_REV_NUM_SHIFT) & SERDES_ID0_REV_NUM_MASK,
		 (u32)msb << 16 | lsb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_serdes_init);

MODULE_AUTHOR("Florian Fainelli <f.fainelli@gmail.com>");
MODULE_DESCRIPTION("B53 Switch SerDes driver");
MODULE_LICENSE("Dual BSD/GPL");
