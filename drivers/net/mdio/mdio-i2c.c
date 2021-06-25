<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MDIO I2C bridge
 *
 * Copyright (C) 2015-2016 Russell King
 *
 * Network PHYs can appear on I2C buses when they are part of SFP module.
 * This driver exposes these PHYs to the networking PHY code, allowing
 * our PHY drivers access to these PHYs, and so allowing configuration
 * of their settings.
 */
#समावेश <linux/i2c.h>
#समावेश <linux/mdio/mdio-i2c.h>
#समावेश <linux/phy.h>

/*
 * I2C bus addresses 0x50 and 0x51 are normally an EEPROM, which is
 * specअगरied to be present in SFP modules.  These correspond with PHY
 * addresses 16 and 17.  Disallow access to these "phy" addresses.
 */
अटल bool i2c_mii_valid_phy_id(पूर्णांक phy_id)
अणु
	वापस phy_id != 0x10 && phy_id != 0x11;
पूर्ण

अटल अचिन्हित पूर्णांक i2c_mii_phy_addr(पूर्णांक phy_id)
अणु
	वापस phy_id + 0x40;
पूर्ण

अटल पूर्णांक i2c_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा i2c_adapter *i2c = bus->priv;
	काष्ठा i2c_msg msgs[2];
	u8 addr[3], data[2], *p;
	पूर्णांक bus_addr, ret;

	अगर (!i2c_mii_valid_phy_id(phy_id))
		वापस 0xffff;

	p = addr;
	अगर (reg & MII_ADDR_C45) अणु
		*p++ = 0x20 | ((reg >> 16) & 31);
		*p++ = reg >> 8;
	पूर्ण
	*p++ = reg;

	bus_addr = i2c_mii_phy_addr(phy_id);
	msgs[0].addr = bus_addr;
	msgs[0].flags = 0;
	msgs[0].len = p - addr;
	msgs[0].buf = addr;
	msgs[1].addr = bus_addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = माप(data);
	msgs[1].buf = data;

	ret = i2c_transfer(i2c, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		वापस 0xffff;

	वापस data[0] << 8 | data[1];
पूर्ण

अटल पूर्णांक i2c_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 val)
अणु
	काष्ठा i2c_adapter *i2c = bus->priv;
	काष्ठा i2c_msg msg;
	पूर्णांक ret;
	u8 data[5], *p;

	अगर (!i2c_mii_valid_phy_id(phy_id))
		वापस 0;

	p = data;
	अगर (reg & MII_ADDR_C45) अणु
		*p++ = (reg >> 16) & 31;
		*p++ = reg >> 8;
	पूर्ण
	*p++ = reg;
	*p++ = val >> 8;
	*p++ = val;

	msg.addr = i2c_mii_phy_addr(phy_id);
	msg.flags = 0;
	msg.len = p - data;
	msg.buf = data;

	ret = i2c_transfer(i2c, &msg, 1);

	वापस ret < 0 ? ret : 0;
पूर्ण

काष्ठा mii_bus *mdio_i2c_alloc(काष्ठा device *parent, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा mii_bus *mii;

	अगर (!i2c_check_functionality(i2c, I2C_FUNC_I2C))
		वापस ERR_PTR(-EINVAL);

	mii = mdiobus_alloc();
	अगर (!mii)
		वापस ERR_PTR(-ENOMEM);

	snम_लिखो(mii->id, MII_BUS_ID_SIZE, "i2c:%s", dev_name(parent));
	mii->parent = parent;
	mii->पढ़ो = i2c_mii_पढ़ो;
	mii->ग_लिखो = i2c_mii_ग_लिखो;
	mii->priv = i2c;

	वापस mii;
पूर्ण
EXPORT_SYMBOL_GPL(mdio_i2c_alloc);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("MDIO I2C bridge library");
MODULE_LICENSE("GPL v2");
