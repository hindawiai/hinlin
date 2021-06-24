<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2011-2012 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (c) 2015, 2019, The Linux Foundation. All rights reserved.
 * Copyright (c) 2016 John Crispin <john@phrozen.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>
#समावेश <net/dsa.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phylink.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/etherdevice.h>

#समावेश "qca8k.h"

#घोषणा MIB_DESC(_s, _o, _n)	\
	अणु			\
		.size = (_s),	\
		.offset = (_o),	\
		.name = (_n),	\
	पूर्ण

अटल स्थिर काष्ठा qca8k_mib_desc ar8327_mib[] = अणु
	MIB_DESC(1, 0x00, "RxBroad"),
	MIB_DESC(1, 0x04, "RxPause"),
	MIB_DESC(1, 0x08, "RxMulti"),
	MIB_DESC(1, 0x0c, "RxFcsErr"),
	MIB_DESC(1, 0x10, "RxAlignErr"),
	MIB_DESC(1, 0x14, "RxRunt"),
	MIB_DESC(1, 0x18, "RxFragment"),
	MIB_DESC(1, 0x1c, "Rx64Byte"),
	MIB_DESC(1, 0x20, "Rx128Byte"),
	MIB_DESC(1, 0x24, "Rx256Byte"),
	MIB_DESC(1, 0x28, "Rx512Byte"),
	MIB_DESC(1, 0x2c, "Rx1024Byte"),
	MIB_DESC(1, 0x30, "Rx1518Byte"),
	MIB_DESC(1, 0x34, "RxMaxByte"),
	MIB_DESC(1, 0x38, "RxTooLong"),
	MIB_DESC(2, 0x3c, "RxGoodByte"),
	MIB_DESC(2, 0x44, "RxBadByte"),
	MIB_DESC(1, 0x4c, "RxOverFlow"),
	MIB_DESC(1, 0x50, "Filtered"),
	MIB_DESC(1, 0x54, "TxBroad"),
	MIB_DESC(1, 0x58, "TxPause"),
	MIB_DESC(1, 0x5c, "TxMulti"),
	MIB_DESC(1, 0x60, "TxUnderRun"),
	MIB_DESC(1, 0x64, "Tx64Byte"),
	MIB_DESC(1, 0x68, "Tx128Byte"),
	MIB_DESC(1, 0x6c, "Tx256Byte"),
	MIB_DESC(1, 0x70, "Tx512Byte"),
	MIB_DESC(1, 0x74, "Tx1024Byte"),
	MIB_DESC(1, 0x78, "Tx1518Byte"),
	MIB_DESC(1, 0x7c, "TxMaxByte"),
	MIB_DESC(1, 0x80, "TxOverSize"),
	MIB_DESC(2, 0x84, "TxByte"),
	MIB_DESC(1, 0x8c, "TxCollision"),
	MIB_DESC(1, 0x90, "TxAbortCol"),
	MIB_DESC(1, 0x94, "TxMultiCol"),
	MIB_DESC(1, 0x98, "TxSingleCol"),
	MIB_DESC(1, 0x9c, "TxExcDefer"),
	MIB_DESC(1, 0xa0, "TxDefer"),
	MIB_DESC(1, 0xa4, "TxLateCol"),
पूर्ण;

/* The 32bit चयन रेजिस्टरs are accessed indirectly. To achieve this we need
 * to set the page of the रेजिस्टर. Track the last page that was set to reduce
 * mdio ग_लिखोs
 */
अटल u16 qca8k_current_page = 0xffff;

अटल व्योम
qca8k_split_addr(u32 regaddr, u16 *r1, u16 *r2, u16 *page)
अणु
	regaddr >>= 1;
	*r1 = regaddr & 0x1e;

	regaddr >>= 5;
	*r2 = regaddr & 0x7;

	regaddr >>= 3;
	*page = regaddr & 0x3ff;
पूर्ण

अटल u32
qca8k_mii_पढ़ो32(काष्ठा mii_bus *bus, पूर्णांक phy_id, u32 regnum)
अणु
	u32 val;
	पूर्णांक ret;

	ret = bus->पढ़ो(bus, phy_id, regnum);
	अगर (ret >= 0) अणु
		val = ret;
		ret = bus->पढ़ो(bus, phy_id, regnum + 1);
		val |= ret << 16;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err_ratelimited(&bus->dev,
				    "failed to read qca8k 32bit register\n");
		वापस ret;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम
qca8k_mii_ग_लिखो32(काष्ठा mii_bus *bus, पूर्णांक phy_id, u32 regnum, u32 val)
अणु
	u16 lo, hi;
	पूर्णांक ret;

	lo = val & 0xffff;
	hi = (u16)(val >> 16);

	ret = bus->ग_लिखो(bus, phy_id, regnum, lo);
	अगर (ret >= 0)
		ret = bus->ग_लिखो(bus, phy_id, regnum + 1, hi);
	अगर (ret < 0)
		dev_err_ratelimited(&bus->dev,
				    "failed to write qca8k 32bit register\n");
पूर्ण

अटल व्योम
qca8k_set_page(काष्ठा mii_bus *bus, u16 page)
अणु
	अगर (page == qca8k_current_page)
		वापस;

	अगर (bus->ग_लिखो(bus, 0x18, 0, page) < 0)
		dev_err_ratelimited(&bus->dev,
				    "failed to set qca8k page\n");
	qca8k_current_page = page;
पूर्ण

अटल u32
qca8k_पढ़ो(काष्ठा qca8k_priv *priv, u32 reg)
अणु
	u16 r1, r2, page;
	u32 val;

	qca8k_split_addr(reg, &r1, &r2, &page);

	mutex_lock_nested(&priv->bus->mdio_lock, MDIO_MUTEX_NESTED);

	qca8k_set_page(priv->bus, page);
	val = qca8k_mii_पढ़ो32(priv->bus, 0x10 | r2, r1);

	mutex_unlock(&priv->bus->mdio_lock);

	वापस val;
पूर्ण

अटल व्योम
qca8k_ग_लिखो(काष्ठा qca8k_priv *priv, u32 reg, u32 val)
अणु
	u16 r1, r2, page;

	qca8k_split_addr(reg, &r1, &r2, &page);

	mutex_lock_nested(&priv->bus->mdio_lock, MDIO_MUTEX_NESTED);

	qca8k_set_page(priv->bus, page);
	qca8k_mii_ग_लिखो32(priv->bus, 0x10 | r2, r1, val);

	mutex_unlock(&priv->bus->mdio_lock);
पूर्ण

अटल u32
qca8k_rmw(काष्ठा qca8k_priv *priv, u32 reg, u32 mask, u32 val)
अणु
	u16 r1, r2, page;
	u32 ret;

	qca8k_split_addr(reg, &r1, &r2, &page);

	mutex_lock_nested(&priv->bus->mdio_lock, MDIO_MUTEX_NESTED);

	qca8k_set_page(priv->bus, page);
	ret = qca8k_mii_पढ़ो32(priv->bus, 0x10 | r2, r1);
	ret &= ~mask;
	ret |= val;
	qca8k_mii_ग_लिखो32(priv->bus, 0x10 | r2, r1, ret);

	mutex_unlock(&priv->bus->mdio_lock);

	वापस ret;
पूर्ण

अटल व्योम
qca8k_reg_set(काष्ठा qca8k_priv *priv, u32 reg, u32 val)
अणु
	qca8k_rmw(priv, reg, 0, val);
पूर्ण

अटल व्योम
qca8k_reg_clear(काष्ठा qca8k_priv *priv, u32 reg, u32 val)
अणु
	qca8k_rmw(priv, reg, val, 0);
पूर्ण

अटल पूर्णांक
qca8k_regmap_पढ़ो(व्योम *ctx, uपूर्णांक32_t reg, uपूर्णांक32_t *val)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ctx;

	*val = qca8k_पढ़ो(priv, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_regmap_ग_लिखो(व्योम *ctx, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ctx;

	qca8k_ग_लिखो(priv, reg, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_range qca8k_पढ़ोable_ranges[] = अणु
	regmap_reg_range(0x0000, 0x00e4), /* Global control */
	regmap_reg_range(0x0100, 0x0168), /* EEE control */
	regmap_reg_range(0x0200, 0x0270), /* Parser control */
	regmap_reg_range(0x0400, 0x0454), /* ACL */
	regmap_reg_range(0x0600, 0x0718), /* Lookup */
	regmap_reg_range(0x0800, 0x0b70), /* QM */
	regmap_reg_range(0x0c00, 0x0c80), /* PKT */
	regmap_reg_range(0x0e00, 0x0e98), /* L3 */
	regmap_reg_range(0x1000, 0x10ac), /* MIB - Port0 */
	regmap_reg_range(0x1100, 0x11ac), /* MIB - Port1 */
	regmap_reg_range(0x1200, 0x12ac), /* MIB - Port2 */
	regmap_reg_range(0x1300, 0x13ac), /* MIB - Port3 */
	regmap_reg_range(0x1400, 0x14ac), /* MIB - Port4 */
	regmap_reg_range(0x1500, 0x15ac), /* MIB - Port5 */
	regmap_reg_range(0x1600, 0x16ac), /* MIB - Port6 */

पूर्ण;

अटल स्थिर काष्ठा regmap_access_table qca8k_पढ़ोable_table = अणु
	.yes_ranges = qca8k_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(qca8k_पढ़ोable_ranges),
पूर्ण;

अटल काष्ठा regmap_config qca8k_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0x16ac, /* end MIB - Port6 range */
	.reg_पढ़ो = qca8k_regmap_पढ़ो,
	.reg_ग_लिखो = qca8k_regmap_ग_लिखो,
	.rd_table = &qca8k_पढ़ोable_table,
पूर्ण;

अटल पूर्णांक
qca8k_busy_रुको(काष्ठा qca8k_priv *priv, u32 reg, u32 mask)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(20);

	/* loop until the busy flag has cleared */
	करो अणु
		u32 val = qca8k_पढ़ो(priv, reg);
		पूर्णांक busy = val & mask;

		अगर (!busy)
			अवरोध;
		cond_resched();
	पूर्ण जबतक (!समय_after_eq(jअगरfies, समयout));

	वापस समय_after_eq(jअगरfies, समयout);
पूर्ण

अटल व्योम
qca8k_fdb_पढ़ो(काष्ठा qca8k_priv *priv, काष्ठा qca8k_fdb *fdb)
अणु
	u32 reg[4];
	पूर्णांक i;

	/* load the ARL table पूर्णांकo an array */
	क्रम (i = 0; i < 4; i++)
		reg[i] = qca8k_पढ़ो(priv, QCA8K_REG_ATU_DATA0 + (i * 4));

	/* vid - 83:72 */
	fdb->vid = (reg[2] >> QCA8K_ATU_VID_S) & QCA8K_ATU_VID_M;
	/* aging - 67:64 */
	fdb->aging = reg[2] & QCA8K_ATU_STATUS_M;
	/* porपंचांगask - 54:48 */
	fdb->port_mask = (reg[1] >> QCA8K_ATU_PORT_S) & QCA8K_ATU_PORT_M;
	/* mac - 47:0 */
	fdb->mac[0] = (reg[1] >> QCA8K_ATU_ADDR0_S) & 0xff;
	fdb->mac[1] = reg[1] & 0xff;
	fdb->mac[2] = (reg[0] >> QCA8K_ATU_ADDR2_S) & 0xff;
	fdb->mac[3] = (reg[0] >> QCA8K_ATU_ADDR3_S) & 0xff;
	fdb->mac[4] = (reg[0] >> QCA8K_ATU_ADDR4_S) & 0xff;
	fdb->mac[5] = reg[0] & 0xff;
पूर्ण

अटल व्योम
qca8k_fdb_ग_लिखो(काष्ठा qca8k_priv *priv, u16 vid, u8 port_mask, स्थिर u8 *mac,
		u8 aging)
अणु
	u32 reg[3] = अणु 0 पूर्ण;
	पूर्णांक i;

	/* vid - 83:72 */
	reg[2] = (vid & QCA8K_ATU_VID_M) << QCA8K_ATU_VID_S;
	/* aging - 67:64 */
	reg[2] |= aging & QCA8K_ATU_STATUS_M;
	/* porपंचांगask - 54:48 */
	reg[1] = (port_mask & QCA8K_ATU_PORT_M) << QCA8K_ATU_PORT_S;
	/* mac - 47:0 */
	reg[1] |= mac[0] << QCA8K_ATU_ADDR0_S;
	reg[1] |= mac[1];
	reg[0] |= mac[2] << QCA8K_ATU_ADDR2_S;
	reg[0] |= mac[3] << QCA8K_ATU_ADDR3_S;
	reg[0] |= mac[4] << QCA8K_ATU_ADDR4_S;
	reg[0] |= mac[5];

	/* load the array पूर्णांकo the ARL table */
	क्रम (i = 0; i < 3; i++)
		qca8k_ग_लिखो(priv, QCA8K_REG_ATU_DATA0 + (i * 4), reg[i]);
पूर्ण

अटल पूर्णांक
qca8k_fdb_access(काष्ठा qca8k_priv *priv, क्रमागत qca8k_fdb_cmd cmd, पूर्णांक port)
अणु
	u32 reg;

	/* Set the command and FDB index */
	reg = QCA8K_ATU_FUNC_BUSY;
	reg |= cmd;
	अगर (port >= 0) अणु
		reg |= QCA8K_ATU_FUNC_PORT_EN;
		reg |= (port & QCA8K_ATU_FUNC_PORT_M) << QCA8K_ATU_FUNC_PORT_S;
	पूर्ण

	/* Write the function रेजिस्टर triggering the table access */
	qca8k_ग_लिखो(priv, QCA8K_REG_ATU_FUNC, reg);

	/* रुको क्रम completion */
	अगर (qca8k_busy_रुको(priv, QCA8K_REG_ATU_FUNC, QCA8K_ATU_FUNC_BUSY))
		वापस -1;

	/* Check क्रम table full violation when adding an entry */
	अगर (cmd == QCA8K_FDB_LOAD) अणु
		reg = qca8k_पढ़ो(priv, QCA8K_REG_ATU_FUNC);
		अगर (reg & QCA8K_ATU_FUNC_FULL)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_fdb_next(काष्ठा qca8k_priv *priv, काष्ठा qca8k_fdb *fdb, पूर्णांक port)
अणु
	पूर्णांक ret;

	qca8k_fdb_ग_लिखो(priv, fdb->vid, fdb->port_mask, fdb->mac, fdb->aging);
	ret = qca8k_fdb_access(priv, QCA8K_FDB_NEXT, port);
	अगर (ret >= 0)
		qca8k_fdb_पढ़ो(priv, fdb);

	वापस ret;
पूर्ण

अटल पूर्णांक
qca8k_fdb_add(काष्ठा qca8k_priv *priv, स्थिर u8 *mac, u16 port_mask,
	      u16 vid, u8 aging)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->reg_mutex);
	qca8k_fdb_ग_लिखो(priv, vid, port_mask, mac, aging);
	ret = qca8k_fdb_access(priv, QCA8K_FDB_LOAD, -1);
	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
qca8k_fdb_del(काष्ठा qca8k_priv *priv, स्थिर u8 *mac, u16 port_mask, u16 vid)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->reg_mutex);
	qca8k_fdb_ग_लिखो(priv, vid, port_mask, mac, 0);
	ret = qca8k_fdb_access(priv, QCA8K_FDB_PURGE, -1);
	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल व्योम
qca8k_fdb_flush(काष्ठा qca8k_priv *priv)
अणु
	mutex_lock(&priv->reg_mutex);
	qca8k_fdb_access(priv, QCA8K_FDB_FLUSH, -1);
	mutex_unlock(&priv->reg_mutex);
पूर्ण

अटल पूर्णांक
qca8k_vlan_access(काष्ठा qca8k_priv *priv, क्रमागत qca8k_vlan_cmd cmd, u16 vid)
अणु
	u32 reg;

	/* Set the command and VLAN index */
	reg = QCA8K_VTU_FUNC1_BUSY;
	reg |= cmd;
	reg |= vid << QCA8K_VTU_FUNC1_VID_S;

	/* Write the function रेजिस्टर triggering the table access */
	qca8k_ग_लिखो(priv, QCA8K_REG_VTU_FUNC1, reg);

	/* रुको क्रम completion */
	अगर (qca8k_busy_रुको(priv, QCA8K_REG_VTU_FUNC1, QCA8K_VTU_FUNC1_BUSY))
		वापस -ETIMEDOUT;

	/* Check क्रम table full violation when adding an entry */
	अगर (cmd == QCA8K_VLAN_LOAD) अणु
		reg = qca8k_पढ़ो(priv, QCA8K_REG_VTU_FUNC1);
		अगर (reg & QCA8K_VTU_FUNC1_FULL)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_vlan_add(काष्ठा qca8k_priv *priv, u8 port, u16 vid, bool untagged)
अणु
	u32 reg;
	पूर्णांक ret;

	/*
	   We करो the right thing with VLAN 0 and treat it as untagged जबतक
	   preserving the tag on egress.
	 */
	अगर (vid == 0)
		वापस 0;

	mutex_lock(&priv->reg_mutex);
	ret = qca8k_vlan_access(priv, QCA8K_VLAN_READ, vid);
	अगर (ret < 0)
		जाओ out;

	reg = qca8k_पढ़ो(priv, QCA8K_REG_VTU_FUNC0);
	reg |= QCA8K_VTU_FUNC0_VALID | QCA8K_VTU_FUNC0_IVL_EN;
	reg &= ~(QCA8K_VTU_FUNC0_EG_MODE_MASK << QCA8K_VTU_FUNC0_EG_MODE_S(port));
	अगर (untagged)
		reg |= QCA8K_VTU_FUNC0_EG_MODE_UNTAG <<
				QCA8K_VTU_FUNC0_EG_MODE_S(port);
	अन्यथा
		reg |= QCA8K_VTU_FUNC0_EG_MODE_TAG <<
				QCA8K_VTU_FUNC0_EG_MODE_S(port);

	qca8k_ग_लिखो(priv, QCA8K_REG_VTU_FUNC0, reg);
	ret = qca8k_vlan_access(priv, QCA8K_VLAN_LOAD, vid);

out:
	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
qca8k_vlan_del(काष्ठा qca8k_priv *priv, u8 port, u16 vid)
अणु
	u32 reg, mask;
	पूर्णांक ret, i;
	bool del;

	mutex_lock(&priv->reg_mutex);
	ret = qca8k_vlan_access(priv, QCA8K_VLAN_READ, vid);
	अगर (ret < 0)
		जाओ out;

	reg = qca8k_पढ़ो(priv, QCA8K_REG_VTU_FUNC0);
	reg &= ~(3 << QCA8K_VTU_FUNC0_EG_MODE_S(port));
	reg |= QCA8K_VTU_FUNC0_EG_MODE_NOT <<
			QCA8K_VTU_FUNC0_EG_MODE_S(port);

	/* Check अगर we're the last member to be हटाओd */
	del = true;
	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++) अणु
		mask = QCA8K_VTU_FUNC0_EG_MODE_NOT;
		mask <<= QCA8K_VTU_FUNC0_EG_MODE_S(i);

		अगर ((reg & mask) != mask) अणु
			del = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (del) अणु
		ret = qca8k_vlan_access(priv, QCA8K_VLAN_PURGE, vid);
	पूर्ण अन्यथा अणु
		qca8k_ग_लिखो(priv, QCA8K_REG_VTU_FUNC0, reg);
		ret = qca8k_vlan_access(priv, QCA8K_VLAN_LOAD, vid);
	पूर्ण

out:
	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल व्योम
qca8k_mib_init(काष्ठा qca8k_priv *priv)
अणु
	mutex_lock(&priv->reg_mutex);
	qca8k_reg_set(priv, QCA8K_REG_MIB, QCA8K_MIB_FLUSH | QCA8K_MIB_BUSY);
	qca8k_busy_रुको(priv, QCA8K_REG_MIB, QCA8K_MIB_BUSY);
	qca8k_reg_set(priv, QCA8K_REG_MIB, QCA8K_MIB_CPU_KEEP);
	qca8k_ग_लिखो(priv, QCA8K_REG_MODULE_EN, QCA8K_MODULE_EN_MIB);
	mutex_unlock(&priv->reg_mutex);
पूर्ण

अटल व्योम
qca8k_port_set_status(काष्ठा qca8k_priv *priv, पूर्णांक port, पूर्णांक enable)
अणु
	u32 mask = QCA8K_PORT_STATUS_TXMAC | QCA8K_PORT_STATUS_RXMAC;

	/* Port 0 and 6 have no पूर्णांकernal PHY */
	अगर (port > 0 && port < 6)
		mask |= QCA8K_PORT_STATUS_LINK_AUTO;

	अगर (enable)
		qca8k_reg_set(priv, QCA8K_REG_PORT_STATUS(port), mask);
	अन्यथा
		qca8k_reg_clear(priv, QCA8K_REG_PORT_STATUS(port), mask);
पूर्ण

अटल u32
qca8k_port_to_phy(पूर्णांक port)
अणु
	/* From Andrew Lunn:
	 * Port 0 has no पूर्णांकernal phy.
	 * Port 1 has an पूर्णांकernal PHY at MDIO address 0.
	 * Port 2 has an पूर्णांकernal PHY at MDIO address 1.
	 * ...
	 * Port 5 has an पूर्णांकernal PHY at MDIO address 4.
	 * Port 6 has no पूर्णांकernal PHY.
	 */

	वापस port - 1;
पूर्ण

अटल पूर्णांक
qca8k_mdio_ग_लिखो(काष्ठा qca8k_priv *priv, पूर्णांक port, u32 regnum, u16 data)
अणु
	u32 phy, val;

	अगर (regnum >= QCA8K_MDIO_MASTER_MAX_REG)
		वापस -EINVAL;

	/* callee is responsible क्रम not passing bad ports,
	 * but we still would like to make spills impossible.
	 */
	phy = qca8k_port_to_phy(port) % PHY_MAX_ADDR;
	val = QCA8K_MDIO_MASTER_BUSY | QCA8K_MDIO_MASTER_EN |
	      QCA8K_MDIO_MASTER_WRITE | QCA8K_MDIO_MASTER_PHY_ADDR(phy) |
	      QCA8K_MDIO_MASTER_REG_ADDR(regnum) |
	      QCA8K_MDIO_MASTER_DATA(data);

	qca8k_ग_लिखो(priv, QCA8K_MDIO_MASTER_CTRL, val);

	वापस qca8k_busy_रुको(priv, QCA8K_MDIO_MASTER_CTRL,
		QCA8K_MDIO_MASTER_BUSY);
पूर्ण

अटल पूर्णांक
qca8k_mdio_पढ़ो(काष्ठा qca8k_priv *priv, पूर्णांक port, u32 regnum)
अणु
	u32 phy, val;

	अगर (regnum >= QCA8K_MDIO_MASTER_MAX_REG)
		वापस -EINVAL;

	/* callee is responsible क्रम not passing bad ports,
	 * but we still would like to make spills impossible.
	 */
	phy = qca8k_port_to_phy(port) % PHY_MAX_ADDR;
	val = QCA8K_MDIO_MASTER_BUSY | QCA8K_MDIO_MASTER_EN |
	      QCA8K_MDIO_MASTER_READ | QCA8K_MDIO_MASTER_PHY_ADDR(phy) |
	      QCA8K_MDIO_MASTER_REG_ADDR(regnum);

	qca8k_ग_लिखो(priv, QCA8K_MDIO_MASTER_CTRL, val);

	अगर (qca8k_busy_रुको(priv, QCA8K_MDIO_MASTER_CTRL,
			    QCA8K_MDIO_MASTER_BUSY))
		वापस -ETIMEDOUT;

	val = (qca8k_पढ़ो(priv, QCA8K_MDIO_MASTER_CTRL) &
		QCA8K_MDIO_MASTER_DATA_MASK);

	वापस val;
पूर्ण

अटल पूर्णांक
qca8k_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum, u16 data)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;

	वापस qca8k_mdio_ग_लिखो(priv, port, regnum, data);
पूर्ण

अटल पूर्णांक
qca8k_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;
	पूर्णांक ret;

	ret = qca8k_mdio_पढ़ो(priv, port, regnum);

	अगर (ret < 0)
		वापस 0xffff;

	वापस ret;
पूर्ण

अटल पूर्णांक
qca8k_setup_mdio_bus(काष्ठा qca8k_priv *priv)
अणु
	u32 पूर्णांकernal_mdio_mask = 0, बाह्यal_mdio_mask = 0, reg;
	काष्ठा device_node *ports, *port;
	पूर्णांक err;

	ports = of_get_child_by_name(priv->dev->of_node, "ports");
	अगर (!ports)
		वापस -EINVAL;

	क्रम_each_available_child_of_node(ports, port) अणु
		err = of_property_पढ़ो_u32(port, "reg", &reg);
		अगर (err) अणु
			of_node_put(port);
			of_node_put(ports);
			वापस err;
		पूर्ण

		अगर (!dsa_is_user_port(priv->ds, reg))
			जारी;

		अगर (of_property_पढ़ो_bool(port, "phy-handle"))
			बाह्यal_mdio_mask |= BIT(reg);
		अन्यथा
			पूर्णांकernal_mdio_mask |= BIT(reg);
	पूर्ण

	of_node_put(ports);
	अगर (!बाह्यal_mdio_mask && !पूर्णांकernal_mdio_mask) अणु
		dev_err(priv->dev, "no PHYs are defined.\n");
		वापस -EINVAL;
	पूर्ण

	/* The QCA8K_MDIO_MASTER_EN Bit, which grants access to PHYs through
	 * the MDIO_MASTER रेजिस्टर also _disconnects_ the बाह्यal MDC
	 * passthrough to the पूर्णांकernal PHYs. It's not possible to use both
	 * configurations at the same समय!
	 *
	 * Because this came up during the review process:
	 * If the बाह्यal mdio-bus driver is capable magically disabling
	 * the QCA8K_MDIO_MASTER_EN and mutex/spin-locking out the qca8k's
	 * accessors क्रम the समय being, it would be possible to pull this
	 * off.
	 */
	अगर (!!बाह्यal_mdio_mask && !!पूर्णांकernal_mdio_mask) अणु
		dev_err(priv->dev, "either internal or external mdio bus configuration is supported.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (बाह्यal_mdio_mask) अणु
		/* Make sure to disable the पूर्णांकernal mdio bus in हालs
		 * a dt-overlay and driver reload changed the configuration
		 */

		qca8k_reg_clear(priv, QCA8K_MDIO_MASTER_CTRL,
				QCA8K_MDIO_MASTER_EN);
		वापस 0;
	पूर्ण

	priv->ops.phy_पढ़ो = qca8k_phy_पढ़ो;
	priv->ops.phy_ग_लिखो = qca8k_phy_ग_लिखो;
	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	पूर्णांक ret, i;

	/* Make sure that port 0 is the cpu port */
	अगर (!dsa_is_cpu_port(ds, 0)) अणु
		pr_err("port 0 is not the CPU port\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&priv->reg_mutex);

	/* Start by setting up the रेजिस्टर mapping */
	priv->regmap = devm_regmap_init(ds->dev, शून्य, priv,
					&qca8k_regmap_config);
	अगर (IS_ERR(priv->regmap))
		pr_warn("regmap initialization failed");

	ret = qca8k_setup_mdio_bus(priv);
	अगर (ret)
		वापस ret;

	/* Enable CPU Port */
	qca8k_reg_set(priv, QCA8K_REG_GLOBAL_FW_CTRL0,
		      QCA8K_GLOBAL_FW_CTRL0_CPU_PORT_EN);

	/* Enable MIB counters */
	qca8k_mib_init(priv);

	/* Enable QCA header mode on the cpu port */
	qca8k_ग_लिखो(priv, QCA8K_REG_PORT_HDR_CTRL(QCA8K_CPU_PORT),
		    QCA8K_PORT_HDR_CTRL_ALL << QCA8K_PORT_HDR_CTRL_TX_S |
		    QCA8K_PORT_HDR_CTRL_ALL << QCA8K_PORT_HDR_CTRL_RX_S);

	/* Disable क्रमwarding by शेष on all ports */
	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++)
		qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(i),
			  QCA8K_PORT_LOOKUP_MEMBER, 0);

	/* Disable MAC by शेष on all ports */
	क्रम (i = 1; i < QCA8K_NUM_PORTS; i++)
		qca8k_port_set_status(priv, i, 0);

	/* Forward all unknown frames to CPU port क्रम Linux processing */
	qca8k_ग_लिखो(priv, QCA8K_REG_GLOBAL_FW_CTRL1,
		    BIT(0) << QCA8K_GLOBAL_FW_CTRL1_IGMP_DP_S |
		    BIT(0) << QCA8K_GLOBAL_FW_CTRL1_BC_DP_S |
		    BIT(0) << QCA8K_GLOBAL_FW_CTRL1_MC_DP_S |
		    BIT(0) << QCA8K_GLOBAL_FW_CTRL1_UC_DP_S);

	/* Setup connection between CPU port & user ports */
	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++) अणु
		/* CPU port माला_लो connected to all user ports of the चयन */
		अगर (dsa_is_cpu_port(ds, i)) अणु
			qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(QCA8K_CPU_PORT),
				  QCA8K_PORT_LOOKUP_MEMBER, dsa_user_ports(ds));
		पूर्ण

		/* Inभागidual user ports get connected to CPU port only */
		अगर (dsa_is_user_port(ds, i)) अणु
			पूर्णांक shअगरt = 16 * (i % 2);

			qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(i),
				  QCA8K_PORT_LOOKUP_MEMBER,
				  BIT(QCA8K_CPU_PORT));

			/* Enable ARP Auto-learning by शेष */
			qca8k_reg_set(priv, QCA8K_PORT_LOOKUP_CTRL(i),
				      QCA8K_PORT_LOOKUP_LEARN);

			/* For port based vlans to work we need to set the
			 * शेष egress vid
			 */
			qca8k_rmw(priv, QCA8K_EGRESS_VLAN(i),
				  0xfff << shअगरt,
				  QCA8K_PORT_VID_DEF << shअगरt);
			qca8k_ग_लिखो(priv, QCA8K_REG_PORT_VLAN_CTRL0(i),
				    QCA8K_PORT_VLAN_CVID(QCA8K_PORT_VID_DEF) |
				    QCA8K_PORT_VLAN_SVID(QCA8K_PORT_VID_DEF));
		पूर्ण
	पूर्ण

	/* Setup our port MTUs to match घातer on शेषs */
	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++)
		priv->port_mtu[i] = ETH_FRAME_LEN + ETH_FCS_LEN;
	qca8k_ग_लिखो(priv, QCA8K_MAX_FRAME_SIZE, ETH_FRAME_LEN + ETH_FCS_LEN);

	/* Flush the FDB table */
	qca8k_fdb_flush(priv);

	/* We करोn't have पूर्णांकerrupts क्रम link changes, so we need to poll */
	ds->pcs_poll = true;

	वापस 0;
पूर्ण

अटल व्योम
qca8k_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
			 स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;
	u32 reg, val;

	चयन (port) अणु
	हाल 0: /* 1st CPU port */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII_ID &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII)
			वापस;

		reg = QCA8K_REG_PORT0_PAD_CTRL;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
	हाल 5:
		/* Internal PHY, nothing to करो */
		वापस;
	हाल 6: /* 2nd CPU port / बाह्यal PHY */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII_ID &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_1000BASEX)
			वापस;

		reg = QCA8K_REG_PORT6_PAD_CTRL;
		अवरोध;
	शेष:
		dev_err(ds->dev, "%s: unsupported port: %i\n", __func__, port);
		वापस;
	पूर्ण

	अगर (port != 6 && phylink_स्वतःneg_inband(mode)) अणु
		dev_err(ds->dev, "%s: in-band negotiation unsupported\n",
			__func__);
		वापस;
	पूर्ण

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		/* RGMII mode means no delay so करोn't enable the delay */
		qca8k_ग_लिखो(priv, reg, QCA8K_PORT_PAD_RGMII_EN);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		/* RGMII_ID needs पूर्णांकernal delay. This is enabled through
		 * PORT5_PAD_CTRL क्रम all ports, rather than inभागidual port
		 * रेजिस्टरs
		 */
		qca8k_ग_लिखो(priv, reg,
			    QCA8K_PORT_PAD_RGMII_EN |
			    QCA8K_PORT_PAD_RGMII_TX_DELAY(QCA8K_MAX_DELAY) |
			    QCA8K_PORT_PAD_RGMII_RX_DELAY(QCA8K_MAX_DELAY));
		qca8k_ग_लिखो(priv, QCA8K_REG_PORT5_PAD_CTRL,
			    QCA8K_PORT_PAD_RGMII_RX_DELAY_EN);
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
		/* Enable SGMII on the port */
		qca8k_ग_लिखो(priv, reg, QCA8K_PORT_PAD_SGMII_EN);

		/* Enable/disable SerDes स्वतः-negotiation as necessary */
		val = qca8k_पढ़ो(priv, QCA8K_REG_PWS);
		अगर (phylink_स्वतःneg_inband(mode))
			val &= ~QCA8K_PWS_SERDES_AEN_DIS;
		अन्यथा
			val |= QCA8K_PWS_SERDES_AEN_DIS;
		qca8k_ग_लिखो(priv, QCA8K_REG_PWS, val);

		/* Configure the SGMII parameters */
		val = qca8k_पढ़ो(priv, QCA8K_REG_SGMII_CTRL);

		val |= QCA8K_SGMII_EN_PLL | QCA8K_SGMII_EN_RX |
			QCA8K_SGMII_EN_TX | QCA8K_SGMII_EN_SD;

		अगर (dsa_is_cpu_port(ds, port)) अणु
			/* CPU port, we're talking to the CPU MAC, be a PHY */
			val &= ~QCA8K_SGMII_MODE_CTRL_MASK;
			val |= QCA8K_SGMII_MODE_CTRL_PHY;
		पूर्ण अन्यथा अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
			val &= ~QCA8K_SGMII_MODE_CTRL_MASK;
			val |= QCA8K_SGMII_MODE_CTRL_MAC;
		पूर्ण अन्यथा अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX) अणु
			val &= ~QCA8K_SGMII_MODE_CTRL_MASK;
			val |= QCA8K_SGMII_MODE_CTRL_BASEX;
		पूर्ण

		qca8k_ग_लिखो(priv, QCA8K_REG_SGMII_CTRL, val);
		अवरोध;
	शेष:
		dev_err(ds->dev, "xMII mode %s not supported for port %d\n",
			phy_modes(state->पूर्णांकerface), port);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम
qca8k_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
		       अचिन्हित दीर्घ *supported,
		       काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	चयन (port) अणु
	हाल 0: /* 1st CPU port */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII_ID &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII)
			जाओ unsupported;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
	हाल 5:
		/* Internal PHY */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
			जाओ unsupported;
		अवरोध;
	हाल 6: /* 2nd CPU port / बाह्यal PHY */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII_ID &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_1000BASEX)
			जाओ unsupported;
		अवरोध;
	शेष:
unsupported:
		linkmode_zero(supported);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);
	phylink_set(mask, Autoneg);

	phylink_set(mask, 1000baseT_Full);
	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX)
		phylink_set(mask, 1000baseX_Full);

	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	linkmode_and(supported, supported, mask);
	linkmode_and(state->advertising, state->advertising, mask);
पूर्ण

अटल पूर्णांक
qca8k_phylink_mac_link_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा phylink_link_state *state)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;
	u32 reg;

	reg = qca8k_पढ़ो(priv, QCA8K_REG_PORT_STATUS(port));

	state->link = !!(reg & QCA8K_PORT_STATUS_LINK_UP);
	state->an_complete = state->link;
	state->an_enabled = !!(reg & QCA8K_PORT_STATUS_LINK_AUTO);
	state->duplex = (reg & QCA8K_PORT_STATUS_DUPLEX) ? DUPLEX_FULL :
							   DUPLEX_HALF;

	चयन (reg & QCA8K_PORT_STATUS_SPEED) अणु
	हाल QCA8K_PORT_STATUS_SPEED_10:
		state->speed = SPEED_10;
		अवरोध;
	हाल QCA8K_PORT_STATUS_SPEED_100:
		state->speed = SPEED_100;
		अवरोध;
	हाल QCA8K_PORT_STATUS_SPEED_1000:
		state->speed = SPEED_1000;
		अवरोध;
	शेष:
		state->speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	state->छोड़ो = MLO_PAUSE_NONE;
	अगर (reg & QCA8K_PORT_STATUS_RXFLOW)
		state->छोड़ो |= MLO_PAUSE_RX;
	अगर (reg & QCA8K_PORT_STATUS_TXFLOW)
		state->छोड़ो |= MLO_PAUSE_TX;

	वापस 1;
पूर्ण

अटल व्योम
qca8k_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
			    phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;

	qca8k_port_set_status(priv, port, 0);
पूर्ण

अटल व्योम
qca8k_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
			  phy_पूर्णांकerface_t पूर्णांकerface, काष्ठा phy_device *phydev,
			  पूर्णांक speed, पूर्णांक duplex, bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;
	u32 reg;

	अगर (phylink_स्वतःneg_inband(mode)) अणु
		reg = QCA8K_PORT_STATUS_LINK_AUTO;
	पूर्ण अन्यथा अणु
		चयन (speed) अणु
		हाल SPEED_10:
			reg = QCA8K_PORT_STATUS_SPEED_10;
			अवरोध;
		हाल SPEED_100:
			reg = QCA8K_PORT_STATUS_SPEED_100;
			अवरोध;
		हाल SPEED_1000:
			reg = QCA8K_PORT_STATUS_SPEED_1000;
			अवरोध;
		शेष:
			reg = QCA8K_PORT_STATUS_LINK_AUTO;
			अवरोध;
		पूर्ण

		अगर (duplex == DUPLEX_FULL)
			reg |= QCA8K_PORT_STATUS_DUPLEX;

		अगर (rx_छोड़ो || dsa_is_cpu_port(ds, port))
			reg |= QCA8K_PORT_STATUS_RXFLOW;

		अगर (tx_छोड़ो || dsa_is_cpu_port(ds, port))
			reg |= QCA8K_PORT_STATUS_TXFLOW;
	पूर्ण

	reg |= QCA8K_PORT_STATUS_TXMAC | QCA8K_PORT_STATUS_RXMAC;

	qca8k_ग_लिखो(priv, QCA8K_REG_PORT_STATUS(port), reg);
पूर्ण

अटल व्योम
qca8k_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset, uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ar8327_mib); i++)
		म_नकलन(data + i * ETH_GSTRING_LEN, ar8327_mib[i].name,
			ETH_GSTRING_LEN);
पूर्ण

अटल व्योम
qca8k_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
			uपूर्णांक64_t *data)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	स्थिर काष्ठा qca8k_mib_desc *mib;
	u32 reg, i;
	u64 hi;

	क्रम (i = 0; i < ARRAY_SIZE(ar8327_mib); i++) अणु
		mib = &ar8327_mib[i];
		reg = QCA8K_PORT_MIB_COUNTER(port) + mib->offset;

		data[i] = qca8k_पढ़ो(priv, reg);
		अगर (mib->size == 2) अणु
			hi = qca8k_पढ़ो(priv, reg + 4);
			data[i] |= hi << 32;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
qca8k_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस 0;

	वापस ARRAY_SIZE(ar8327_mib);
पूर्ण

अटल पूर्णांक
qca8k_set_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा ethtool_eee *eee)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	u32 lpi_en = QCA8K_REG_EEE_CTRL_LPI_EN(port);
	u32 reg;

	mutex_lock(&priv->reg_mutex);
	reg = qca8k_पढ़ो(priv, QCA8K_REG_EEE_CTRL);
	अगर (eee->eee_enabled)
		reg |= lpi_en;
	अन्यथा
		reg &= ~lpi_en;
	qca8k_ग_लिखो(priv, QCA8K_REG_EEE_CTRL, reg);
	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_get_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा ethtool_eee *e)
अणु
	/* Nothing to करो on the port's MAC */
	वापस 0;
पूर्ण

अटल व्योम
qca8k_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port, u8 state)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	u32 stp_state;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		stp_state = QCA8K_PORT_LOOKUP_STATE_DISABLED;
		अवरोध;
	हाल BR_STATE_BLOCKING:
		stp_state = QCA8K_PORT_LOOKUP_STATE_BLOCKING;
		अवरोध;
	हाल BR_STATE_LISTENING:
		stp_state = QCA8K_PORT_LOOKUP_STATE_LISTENING;
		अवरोध;
	हाल BR_STATE_LEARNING:
		stp_state = QCA8K_PORT_LOOKUP_STATE_LEARNING;
		अवरोध;
	हाल BR_STATE_FORWARDING:
	शेष:
		stp_state = QCA8K_PORT_LOOKUP_STATE_FORWARD;
		अवरोध;
	पूर्ण

	qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
		  QCA8K_PORT_LOOKUP_STATE_MASK, stp_state);
पूर्ण

अटल पूर्णांक
qca8k_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा net_device *br)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	पूर्णांक port_mask = BIT(QCA8K_CPU_PORT);
	पूर्णांक i;

	क्रम (i = 1; i < QCA8K_NUM_PORTS; i++) अणु
		अगर (dsa_to_port(ds, i)->bridge_dev != br)
			जारी;
		/* Add this port to the portvlan mask of the other ports
		 * in the bridge
		 */
		qca8k_reg_set(priv,
			      QCA8K_PORT_LOOKUP_CTRL(i),
			      BIT(port));
		अगर (i != port)
			port_mask |= BIT(i);
	पूर्ण
	/* Add all other ports to this ports portvlan mask */
	qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
		  QCA8K_PORT_LOOKUP_MEMBER, port_mask);

	वापस 0;
पूर्ण

अटल व्योम
qca8k_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा net_device *br)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	पूर्णांक i;

	क्रम (i = 1; i < QCA8K_NUM_PORTS; i++) अणु
		अगर (dsa_to_port(ds, i)->bridge_dev != br)
			जारी;
		/* Remove this port to the portvlan mask of the other ports
		 * in the bridge
		 */
		qca8k_reg_clear(priv,
				QCA8K_PORT_LOOKUP_CTRL(i),
				BIT(port));
	पूर्ण

	/* Set the cpu port to be the only one in the portvlan mask of
	 * this port
	 */
	qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
		  QCA8K_PORT_LOOKUP_MEMBER, BIT(QCA8K_CPU_PORT));
पूर्ण

अटल पूर्णांक
qca8k_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
		  काष्ठा phy_device *phy)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;

	qca8k_port_set_status(priv, port, 1);
	priv->port_sts[port].enabled = 1;

	अगर (dsa_is_user_port(ds, port))
		phy_support_asym_छोड़ो(phy);

	वापस 0;
पूर्ण

अटल व्योम
qca8k_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;

	qca8k_port_set_status(priv, port, 0);
	priv->port_sts[port].enabled = 0;
पूर्ण

अटल पूर्णांक
qca8k_port_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;
	पूर्णांक i, mtu = 0;

	priv->port_mtu[port] = new_mtu;

	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++)
		अगर (priv->port_mtu[i] > mtu)
			mtu = priv->port_mtu[i];

	/* Include L2 header / FCS length */
	qca8k_ग_लिखो(priv, QCA8K_MAX_FRAME_SIZE, mtu + ETH_HLEN + ETH_FCS_LEN);

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_port_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस QCA8K_MAX_MTU;
पूर्ण

अटल पूर्णांक
qca8k_port_fdb_insert(काष्ठा qca8k_priv *priv, स्थिर u8 *addr,
		      u16 port_mask, u16 vid)
अणु
	/* Set the vid to the port vlan id अगर no vid is set */
	अगर (!vid)
		vid = QCA8K_PORT_VID_DEF;

	वापस qca8k_fdb_add(priv, addr, port_mask, vid,
			     QCA8K_ATU_STATUS_STATIC);
पूर्ण

अटल पूर्णांक
qca8k_port_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	u16 port_mask = BIT(port);

	वापस qca8k_port_fdb_insert(priv, addr, port_mask, vid);
पूर्ण

अटल पूर्णांक
qca8k_port_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	u16 port_mask = BIT(port);

	अगर (!vid)
		vid = QCA8K_PORT_VID_DEF;

	वापस qca8k_fdb_del(priv, addr, port_mask, vid);
पूर्ण

अटल पूर्णांक
qca8k_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा qca8k_priv *priv = (काष्ठा qca8k_priv *)ds->priv;
	काष्ठा qca8k_fdb _fdb = अणु 0 पूर्ण;
	पूर्णांक cnt = QCA8K_NUM_FDB_RECORDS;
	bool is_अटल;
	पूर्णांक ret = 0;

	mutex_lock(&priv->reg_mutex);
	जबतक (cnt-- && !qca8k_fdb_next(priv, &_fdb, port)) अणु
		अगर (!_fdb.aging)
			अवरोध;
		is_अटल = (_fdb.aging == QCA8K_ATU_STATUS_STATIC);
		ret = cb(_fdb.mac, _fdb.vid, is_अटल, data);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_port_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool vlan_filtering,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;

	अगर (vlan_filtering) अणु
		qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
			  QCA8K_PORT_LOOKUP_VLAN_MODE,
			  QCA8K_PORT_LOOKUP_VLAN_MODE_SECURE);
	पूर्ण अन्यथा अणु
		qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
			  QCA8K_PORT_LOOKUP_VLAN_MODE,
			  QCA8K_PORT_LOOKUP_VLAN_MODE_NONE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_port_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		    काष्ठा netlink_ext_ack *extack)
अणु
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा qca8k_priv *priv = ds->priv;
	पूर्णांक ret = 0;

	ret = qca8k_vlan_add(priv, port, vlan->vid, untagged);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to add VLAN to port %d (%d)", port, ret);
		वापस ret;
	पूर्ण

	अगर (pvid) अणु
		पूर्णांक shअगरt = 16 * (port % 2);

		qca8k_rmw(priv, QCA8K_EGRESS_VLAN(port),
			  0xfff << shअगरt, vlan->vid << shअगरt);
		qca8k_ग_लिखो(priv, QCA8K_REG_PORT_VLAN_CTRL0(port),
			    QCA8K_PORT_VLAN_CVID(vlan->vid) |
			    QCA8K_PORT_VLAN_SVID(vlan->vid));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qca8k_port_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा qca8k_priv *priv = ds->priv;
	पूर्णांक ret = 0;

	ret = qca8k_vlan_del(priv, port, vlan->vid);
	अगर (ret)
		dev_err(priv->dev, "Failed to delete VLAN from port %d (%d)", port, ret);

	वापस ret;
पूर्ण

अटल क्रमागत dsa_tag_protocol
qca8k_get_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक port,
		       क्रमागत dsa_tag_protocol mp)
अणु
	वापस DSA_TAG_PROTO_QCA;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops qca8k_चयन_ops = अणु
	.get_tag_protocol	= qca8k_get_tag_protocol,
	.setup			= qca8k_setup,
	.get_strings		= qca8k_get_strings,
	.get_ethtool_stats	= qca8k_get_ethtool_stats,
	.get_sset_count		= qca8k_get_sset_count,
	.get_mac_eee		= qca8k_get_mac_eee,
	.set_mac_eee		= qca8k_set_mac_eee,
	.port_enable		= qca8k_port_enable,
	.port_disable		= qca8k_port_disable,
	.port_change_mtu	= qca8k_port_change_mtu,
	.port_max_mtu		= qca8k_port_max_mtu,
	.port_stp_state_set	= qca8k_port_stp_state_set,
	.port_bridge_join	= qca8k_port_bridge_join,
	.port_bridge_leave	= qca8k_port_bridge_leave,
	.port_fdb_add		= qca8k_port_fdb_add,
	.port_fdb_del		= qca8k_port_fdb_del,
	.port_fdb_dump		= qca8k_port_fdb_dump,
	.port_vlan_filtering	= qca8k_port_vlan_filtering,
	.port_vlan_add		= qca8k_port_vlan_add,
	.port_vlan_del		= qca8k_port_vlan_del,
	.phylink_validate	= qca8k_phylink_validate,
	.phylink_mac_link_state	= qca8k_phylink_mac_link_state,
	.phylink_mac_config	= qca8k_phylink_mac_config,
	.phylink_mac_link_करोwn	= qca8k_phylink_mac_link_करोwn,
	.phylink_mac_link_up	= qca8k_phylink_mac_link_up,
पूर्ण;

अटल पूर्णांक
qca8k_sw_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा qca8k_priv *priv;
	u32 id;

	/* allocate the निजी data काष्ठा so that we can probe the चयनes
	 * ID रेजिस्टर
	 */
	priv = devm_kzalloc(&mdiodev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->bus = mdiodev->bus;
	priv->dev = &mdiodev->dev;

	priv->reset_gpio = devm_gpiod_get_optional(priv->dev, "reset",
						   GPIOD_ASIS);
	अगर (IS_ERR(priv->reset_gpio))
		वापस PTR_ERR(priv->reset_gpio);

	अगर (priv->reset_gpio) अणु
		gpiod_set_value_cansleep(priv->reset_gpio, 1);
		/* The active low duration must be greater than 10 ms
		 * and checkpatch.pl wants 20 ms.
		 */
		msleep(20);
		gpiod_set_value_cansleep(priv->reset_gpio, 0);
	पूर्ण

	/* पढ़ो the चयनes ID रेजिस्टर */
	id = qca8k_पढ़ो(priv, QCA8K_REG_MASK_CTRL);
	id >>= QCA8K_MASK_CTRL_ID_S;
	id &= QCA8K_MASK_CTRL_ID_M;
	अगर (id != QCA8K_ID_QCA8337)
		वापस -ENODEV;

	priv->ds = devm_kzalloc(&mdiodev->dev, माप(*priv->ds), GFP_KERNEL);
	अगर (!priv->ds)
		वापस -ENOMEM;

	priv->ds->dev = &mdiodev->dev;
	priv->ds->num_ports = QCA8K_NUM_PORTS;
	priv->ds->priv = priv;
	priv->ops = qca8k_चयन_ops;
	priv->ds->ops = &priv->ops;
	mutex_init(&priv->reg_mutex);
	dev_set_drvdata(&mdiodev->dev, priv);

	वापस dsa_रेजिस्टर_चयन(priv->ds);
पूर्ण

अटल व्योम
qca8k_sw_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा qca8k_priv *priv = dev_get_drvdata(&mdiodev->dev);
	पूर्णांक i;

	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++)
		qca8k_port_set_status(priv, i, 0);

	dsa_unरेजिस्टर_चयन(priv->ds);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम
qca8k_set_pm(काष्ठा qca8k_priv *priv, पूर्णांक enable)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QCA8K_NUM_PORTS; i++) अणु
		अगर (!priv->port_sts[i].enabled)
			जारी;

		qca8k_port_set_status(priv, i, enable);
	पूर्ण
पूर्ण

अटल पूर्णांक qca8k_suspend(काष्ठा device *dev)
अणु
	काष्ठा qca8k_priv *priv = dev_get_drvdata(dev);

	qca8k_set_pm(priv, 0);

	वापस dsa_चयन_suspend(priv->ds);
पूर्ण

अटल पूर्णांक qca8k_resume(काष्ठा device *dev)
अणु
	काष्ठा qca8k_priv *priv = dev_get_drvdata(dev);

	qca8k_set_pm(priv, 1);

	वापस dsa_चयन_resume(priv->ds);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(qca8k_pm_ops,
			 qca8k_suspend, qca8k_resume);

अटल स्थिर काष्ठा of_device_id qca8k_of_match[] = अणु
	अणु .compatible = "qca,qca8334" पूर्ण,
	अणु .compatible = "qca,qca8337" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा mdio_driver qca8kmdio_driver = अणु
	.probe  = qca8k_sw_probe,
	.हटाओ = qca8k_sw_हटाओ,
	.mdiodrv.driver = अणु
		.name = "qca8k",
		.of_match_table = qca8k_of_match,
		.pm = &qca8k_pm_ops,
	पूर्ण,
पूर्ण;

mdio_module_driver(qca8kmdio_driver);

MODULE_AUTHOR("Mathieu Olivari, John Crispin <john@phrozen.org>");
MODULE_DESCRIPTION("Driver for QCA8K ethernet switch family");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qca8k");
