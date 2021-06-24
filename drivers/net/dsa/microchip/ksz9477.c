<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip KSZ9477 चयन driver मुख्य logic
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/platक्रमm_data/microchip-ksz.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <net/dsa.h>
#समावेश <net/चयनdev.h>

#समावेश "ksz9477_reg.h"
#समावेश "ksz_common.h"

/* Used with variable features to indicate capabilities. */
#घोषणा GBIT_SUPPORT			BIT(0)
#घोषणा NEW_XMII			BIT(1)
#घोषणा IS_9893				BIT(2)

अटल स्थिर काष्ठा अणु
	पूर्णांक index;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण ksz9477_mib_names[TOTAL_SWITCH_COUNTER_NUM] = अणु
	अणु 0x00, "rx_hi" पूर्ण,
	अणु 0x01, "rx_undersize" पूर्ण,
	अणु 0x02, "rx_fragments" पूर्ण,
	अणु 0x03, "rx_oversize" पूर्ण,
	अणु 0x04, "rx_jabbers" पूर्ण,
	अणु 0x05, "rx_symbol_err" पूर्ण,
	अणु 0x06, "rx_crc_err" पूर्ण,
	अणु 0x07, "rx_align_err" पूर्ण,
	अणु 0x08, "rx_mac_ctrl" पूर्ण,
	अणु 0x09, "rx_pause" पूर्ण,
	अणु 0x0A, "rx_bcast" पूर्ण,
	अणु 0x0B, "rx_mcast" पूर्ण,
	अणु 0x0C, "rx_ucast" पूर्ण,
	अणु 0x0D, "rx_64_or_less" पूर्ण,
	अणु 0x0E, "rx_65_127" पूर्ण,
	अणु 0x0F, "rx_128_255" पूर्ण,
	अणु 0x10, "rx_256_511" पूर्ण,
	अणु 0x11, "rx_512_1023" पूर्ण,
	अणु 0x12, "rx_1024_1522" पूर्ण,
	अणु 0x13, "rx_1523_2000" पूर्ण,
	अणु 0x14, "rx_2001" पूर्ण,
	अणु 0x15, "tx_hi" पूर्ण,
	अणु 0x16, "tx_late_col" पूर्ण,
	अणु 0x17, "tx_pause" पूर्ण,
	अणु 0x18, "tx_bcast" पूर्ण,
	अणु 0x19, "tx_mcast" पूर्ण,
	अणु 0x1A, "tx_ucast" पूर्ण,
	अणु 0x1B, "tx_deferred" पूर्ण,
	अणु 0x1C, "tx_total_col" पूर्ण,
	अणु 0x1D, "tx_exc_col" पूर्ण,
	अणु 0x1E, "tx_single_col" पूर्ण,
	अणु 0x1F, "tx_mult_col" पूर्ण,
	अणु 0x80, "rx_total" पूर्ण,
	अणु 0x81, "tx_total" पूर्ण,
	अणु 0x82, "rx_discards" पूर्ण,
	अणु 0x83, "tx_discards" पूर्ण,
पूर्ण;

अटल व्योम ksz_cfg(काष्ठा ksz_device *dev, u32 addr, u8 bits, bool set)
अणु
	regmap_update_bits(dev->regmap[0], addr, bits, set ? bits : 0);
पूर्ण

अटल व्योम ksz_port_cfg(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset, u8 bits,
			 bool set)
अणु
	regmap_update_bits(dev->regmap[0], PORT_CTRL_ADDR(port, offset),
			   bits, set ? bits : 0);
पूर्ण

अटल व्योम ksz9477_cfg32(काष्ठा ksz_device *dev, u32 addr, u32 bits, bool set)
अणु
	regmap_update_bits(dev->regmap[2], addr, bits, set ? bits : 0);
पूर्ण

अटल व्योम ksz9477_port_cfg32(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
			       u32 bits, bool set)
अणु
	regmap_update_bits(dev->regmap[2], PORT_CTRL_ADDR(port, offset),
			   bits, set ? bits : 0);
पूर्ण

अटल पूर्णांक ksz9477_रुको_vlan_ctrl_पढ़ोy(काष्ठा ksz_device *dev)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout(dev->regmap[0], REG_SW_VLAN_CTRL,
					val, !(val & VLAN_START), 10, 1000);
पूर्ण

अटल पूर्णांक ksz9477_get_vlan_table(काष्ठा ksz_device *dev, u16 vid,
				  u32 *vlan_table)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->vlan_mutex);

	ksz_ग_लिखो16(dev, REG_SW_VLAN_ENTRY_INDEX__2, vid & VLAN_INDEX_M);
	ksz_ग_लिखो8(dev, REG_SW_VLAN_CTRL, VLAN_READ | VLAN_START);

	/* रुको to be cleared */
	ret = ksz9477_रुको_vlan_ctrl_पढ़ोy(dev);
	अगर (ret) अणु
		dev_dbg(dev->dev, "Failed to read vlan table\n");
		जाओ निकास;
	पूर्ण

	ksz_पढ़ो32(dev, REG_SW_VLAN_ENTRY__4, &vlan_table[0]);
	ksz_पढ़ो32(dev, REG_SW_VLAN_ENTRY_UNTAG__4, &vlan_table[1]);
	ksz_पढ़ो32(dev, REG_SW_VLAN_ENTRY_PORTS__4, &vlan_table[2]);

	ksz_ग_लिखो8(dev, REG_SW_VLAN_CTRL, 0);

निकास:
	mutex_unlock(&dev->vlan_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ksz9477_set_vlan_table(काष्ठा ksz_device *dev, u16 vid,
				  u32 *vlan_table)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->vlan_mutex);

	ksz_ग_लिखो32(dev, REG_SW_VLAN_ENTRY__4, vlan_table[0]);
	ksz_ग_लिखो32(dev, REG_SW_VLAN_ENTRY_UNTAG__4, vlan_table[1]);
	ksz_ग_लिखो32(dev, REG_SW_VLAN_ENTRY_PORTS__4, vlan_table[2]);

	ksz_ग_लिखो16(dev, REG_SW_VLAN_ENTRY_INDEX__2, vid & VLAN_INDEX_M);
	ksz_ग_लिखो8(dev, REG_SW_VLAN_CTRL, VLAN_START | VLAN_WRITE);

	/* रुको to be cleared */
	ret = ksz9477_रुको_vlan_ctrl_पढ़ोy(dev);
	अगर (ret) अणु
		dev_dbg(dev->dev, "Failed to write vlan table\n");
		जाओ निकास;
	पूर्ण

	ksz_ग_लिखो8(dev, REG_SW_VLAN_CTRL, 0);

	/* update vlan cache table */
	dev->vlan_cache[vid].table[0] = vlan_table[0];
	dev->vlan_cache[vid].table[1] = vlan_table[1];
	dev->vlan_cache[vid].table[2] = vlan_table[2];

निकास:
	mutex_unlock(&dev->vlan_mutex);

	वापस ret;
पूर्ण

अटल व्योम ksz9477_पढ़ो_table(काष्ठा ksz_device *dev, u32 *table)
अणु
	ksz_पढ़ो32(dev, REG_SW_ALU_VAL_A, &table[0]);
	ksz_पढ़ो32(dev, REG_SW_ALU_VAL_B, &table[1]);
	ksz_पढ़ो32(dev, REG_SW_ALU_VAL_C, &table[2]);
	ksz_पढ़ो32(dev, REG_SW_ALU_VAL_D, &table[3]);
पूर्ण

अटल व्योम ksz9477_ग_लिखो_table(काष्ठा ksz_device *dev, u32 *table)
अणु
	ksz_ग_लिखो32(dev, REG_SW_ALU_VAL_A, table[0]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_VAL_B, table[1]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_VAL_C, table[2]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_VAL_D, table[3]);
पूर्ण

अटल पूर्णांक ksz9477_रुको_alu_पढ़ोy(काष्ठा ksz_device *dev)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout(dev->regmap[2], REG_SW_ALU_CTRL__4,
					val, !(val & ALU_START), 10, 1000);
पूर्ण

अटल पूर्णांक ksz9477_रुको_alu_sta_पढ़ोy(काष्ठा ksz_device *dev)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout(dev->regmap[2],
					REG_SW_ALU_STAT_CTRL__4,
					val, !(val & ALU_STAT_START),
					10, 1000);
पूर्ण

अटल पूर्णांक ksz9477_reset_चयन(काष्ठा ksz_device *dev)
अणु
	u8 data8;
	u32 data32;

	/* reset चयन */
	ksz_cfg(dev, REG_SW_OPERATION, SW_RESET, true);

	/* turn off SPI DO Edge select */
	regmap_update_bits(dev->regmap[0], REG_SW_GLOBAL_SERIAL_CTRL_0,
			   SPI_AUTO_EDGE_DETECTION, 0);

	/* शेष configuration */
	ksz_पढ़ो8(dev, REG_SW_LUE_CTRL_1, &data8);
	data8 = SW_AGING_ENABLE | SW_LINK_AUTO_AGING |
	      SW_SRC_ADDR_FILTER | SW_FLUSH_STP_TABLE | SW_FLUSH_MSTP_TABLE;
	ksz_ग_लिखो8(dev, REG_SW_LUE_CTRL_1, data8);

	/* disable पूर्णांकerrupts */
	ksz_ग_लिखो32(dev, REG_SW_INT_MASK__4, SWITCH_INT_MASK);
	ksz_ग_लिखो32(dev, REG_SW_PORT_INT_MASK__4, 0x7F);
	ksz_पढ़ो32(dev, REG_SW_PORT_INT_STATUS__4, &data32);

	/* set broadcast storm protection 10% rate */
	regmap_update_bits(dev->regmap[1], REG_SW_MAC_CTRL_2,
			   BROADCAST_STORM_RATE,
			   (BROADCAST_STORM_VALUE *
			   BROADCAST_STORM_PROT_RATE) / 100);

	अगर (dev->synclko_125)
		ksz_ग_लिखो8(dev, REG_SW_GLOBAL_OUTPUT_CTRL__1,
			   SW_ENABLE_REFCLKO | SW_REFCLKO_IS_125MHZ);

	वापस 0;
पूर्ण

अटल व्योम ksz9477_r_mib_cnt(काष्ठा ksz_device *dev, पूर्णांक port, u16 addr,
			      u64 *cnt)
अणु
	काष्ठा ksz_port *p = &dev->ports[port];
	अचिन्हित पूर्णांक val;
	u32 data;
	पूर्णांक ret;

	/* retain the flush/मुक्तze bit */
	data = p->मुक्तze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	data |= MIB_COUNTER_READ;
	data |= (addr << MIB_COUNTER_INDEX_S);
	ksz_pग_लिखो32(dev, port, REG_PORT_MIB_CTRL_STAT__4, data);

	ret = regmap_पढ़ो_poll_समयout(dev->regmap[2],
			PORT_CTRL_ADDR(port, REG_PORT_MIB_CTRL_STAT__4),
			val, !(val & MIB_COUNTER_READ), 10, 1000);
	/* failed to पढ़ो MIB. get out of loop */
	अगर (ret) अणु
		dev_dbg(dev->dev, "Failed to get MIB\n");
		वापस;
	पूर्ण

	/* count resets upon पढ़ो */
	ksz_pपढ़ो32(dev, port, REG_PORT_MIB_DATA, &data);
	*cnt += data;
पूर्ण

अटल व्योम ksz9477_r_mib_pkt(काष्ठा ksz_device *dev, पूर्णांक port, u16 addr,
			      u64 *dropped, u64 *cnt)
अणु
	addr = ksz9477_mib_names[addr].index;
	ksz9477_r_mib_cnt(dev, port, addr, cnt);
पूर्ण

अटल व्योम ksz9477_मुक्तze_mib(काष्ठा ksz_device *dev, पूर्णांक port, bool मुक्तze)
अणु
	u32 val = मुक्तze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	काष्ठा ksz_port *p = &dev->ports[port];

	/* enable/disable the port क्रम flush/मुक्तze function */
	mutex_lock(&p->mib.cnt_mutex);
	ksz_pग_लिखो32(dev, port, REG_PORT_MIB_CTRL_STAT__4, val);

	/* used by MIB counter पढ़ोing code to know मुक्तze is enabled */
	p->मुक्तze = मुक्तze;
	mutex_unlock(&p->mib.cnt_mutex);
पूर्ण

अटल व्योम ksz9477_port_init_cnt(काष्ठा ksz_device *dev, पूर्णांक port)
अणु
	काष्ठा ksz_port_mib *mib = &dev->ports[port].mib;

	/* flush all enabled port MIB counters */
	mutex_lock(&mib->cnt_mutex);
	ksz_pग_लिखो32(dev, port, REG_PORT_MIB_CTRL_STAT__4,
		     MIB_COUNTER_FLUSH_FREEZE);
	ksz_ग_लिखो8(dev, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FLUSH);
	ksz_pग_लिखो32(dev, port, REG_PORT_MIB_CTRL_STAT__4, 0);
	mutex_unlock(&mib->cnt_mutex);

	mib->cnt_ptr = 0;
	स_रखो(mib->counters, 0, dev->mib_cnt * माप(u64));
पूर्ण

अटल क्रमागत dsa_tag_protocol ksz9477_get_tag_protocol(काष्ठा dsa_चयन *ds,
						      पूर्णांक port,
						      क्रमागत dsa_tag_protocol mp)
अणु
	क्रमागत dsa_tag_protocol proto = DSA_TAG_PROTO_KSZ9477;
	काष्ठा ksz_device *dev = ds->priv;

	अगर (dev->features & IS_9893)
		proto = DSA_TAG_PROTO_KSZ9893;
	वापस proto;
पूर्ण

अटल पूर्णांक ksz9477_phy_पढ़ो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u16 val = 0xffff;

	/* No real PHY after this. Simulate the PHY.
	 * A fixed PHY can be setup in the device tree, but this function is
	 * still called क्रम that port during initialization.
	 * For RGMII PHY there is no way to access it so the fixed PHY should
	 * be used.  For SGMII PHY the supporting code will be added later.
	 */
	अगर (addr >= dev->phy_port_cnt) अणु
		काष्ठा ksz_port *p = &dev->ports[addr];

		चयन (reg) अणु
		हाल MII_BMCR:
			val = 0x1140;
			अवरोध;
		हाल MII_BMSR:
			val = 0x796d;
			अवरोध;
		हाल MII_PHYSID1:
			val = 0x0022;
			अवरोध;
		हाल MII_PHYSID2:
			val = 0x1631;
			अवरोध;
		हाल MII_ADVERTISE:
			val = 0x05e1;
			अवरोध;
		हाल MII_LPA:
			val = 0xc5e1;
			अवरोध;
		हाल MII_CTRL1000:
			val = 0x0700;
			अवरोध;
		हाल MII_STAT1000:
			अगर (p->phydev.speed == SPEED_1000)
				val = 0x3800;
			अन्यथा
				val = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ksz_pपढ़ो16(dev, addr, 0x100 + (reg << 1), &val);
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक ksz9477_phy_ग_लिखो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg,
			       u16 val)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	/* No real PHY after this. */
	अगर (addr >= dev->phy_port_cnt)
		वापस 0;

	/* No gigabit support.  Do not ग_लिखो to this रेजिस्टर. */
	अगर (!(dev->features & GBIT_SUPPORT) && reg == MII_CTRL1000)
		वापस 0;
	ksz_pग_लिखो16(dev, addr, 0x100 + (reg << 1), val);

	वापस 0;
पूर्ण

अटल व्योम ksz9477_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				u32 stringset, uपूर्णांक8_t *buf)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < TOTAL_SWITCH_COUNTER_NUM; i++) अणु
		स_नकल(buf + i * ETH_GSTRING_LEN, ksz9477_mib_names[i].string,
		       ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल व्योम ksz9477_cfg_port_member(काष्ठा ksz_device *dev, पूर्णांक port,
				    u8 member)
अणु
	ksz_pग_लिखो32(dev, port, REG_PORT_VLAN_MEMBERSHIP__4, member);
	dev->ports[port].member = member;
पूर्ण

अटल व्योम ksz9477_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       u8 state)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	काष्ठा ksz_port *p = &dev->ports[port];
	u8 data;
	पूर्णांक member = -1;
	पूर्णांक क्रमward = dev->member;

	ksz_pपढ़ो8(dev, port, P_STP_CTRL, &data);
	data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE | PORT_LEARN_DISABLE);

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		data |= PORT_LEARN_DISABLE;
		अगर (port != dev->cpu_port)
			member = 0;
		अवरोध;
	हाल BR_STATE_LISTENING:
		data |= (PORT_RX_ENABLE | PORT_LEARN_DISABLE);
		अगर (port != dev->cpu_port &&
		    p->stp_state == BR_STATE_DISABLED)
			member = dev->host_mask | p->vid_member;
		अवरोध;
	हाल BR_STATE_LEARNING:
		data |= PORT_RX_ENABLE;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);

		/* This function is also used पूर्णांकernally. */
		अगर (port == dev->cpu_port)
			अवरोध;

		member = dev->host_mask | p->vid_member;
		mutex_lock(&dev->dev_mutex);

		/* Port is a member of a bridge. */
		अगर (dev->br_member & (1 << port)) अणु
			dev->member |= (1 << port);
			member = dev->member;
		पूर्ण
		mutex_unlock(&dev->dev_mutex);
		अवरोध;
	हाल BR_STATE_BLOCKING:
		data |= PORT_LEARN_DISABLE;
		अगर (port != dev->cpu_port &&
		    p->stp_state == BR_STATE_DISABLED)
			member = dev->host_mask | p->vid_member;
		अवरोध;
	शेष:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		वापस;
	पूर्ण

	ksz_pग_लिखो8(dev, port, P_STP_CTRL, data);
	p->stp_state = state;
	mutex_lock(&dev->dev_mutex);
	/* Port membership may share रेजिस्टर with STP state. */
	अगर (member >= 0 && member != p->member)
		ksz9477_cfg_port_member(dev, port, (u8)member);

	/* Check अगर क्रमwarding needs to be updated. */
	अगर (state != BR_STATE_FORWARDING) अणु
		अगर (dev->br_member & (1 << port))
			dev->member &= ~(1 << port);
	पूर्ण

	/* When topology has changed the function ksz_update_port_member
	 * should be called to modअगरy port क्रमwarding behavior.
	 */
	अगर (क्रमward != dev->member)
		ksz_update_port_member(dev, port);
	mutex_unlock(&dev->dev_mutex);
पूर्ण

अटल व्योम ksz9477_flush_dyn_mac_table(काष्ठा ksz_device *dev, पूर्णांक port)
अणु
	u8 data;

	regmap_update_bits(dev->regmap[0], REG_SW_LUE_CTRL_2,
			   SW_FLUSH_OPTION_M << SW_FLUSH_OPTION_S,
			   SW_FLUSH_OPTION_DYN_MAC << SW_FLUSH_OPTION_S);

	अगर (port < dev->port_cnt) अणु
		/* flush inभागidual port */
		ksz_pपढ़ो8(dev, port, P_STP_CTRL, &data);
		अगर (!(data & PORT_LEARN_DISABLE))
			ksz_pग_लिखो8(dev, port, P_STP_CTRL,
				    data | PORT_LEARN_DISABLE);
		ksz_cfg(dev, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, true);
		ksz_pग_लिखो8(dev, port, P_STP_CTRL, data);
	पूर्ण अन्यथा अणु
		/* flush all */
		ksz_cfg(dev, S_FLUSH_TABLE_CTRL, SW_FLUSH_STP_TABLE, true);
	पूर्ण
पूर्ण

अटल पूर्णांक ksz9477_port_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       bool flag,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	अगर (flag) अणु
		ksz_port_cfg(dev, port, REG_PORT_LUE_CTRL,
			     PORT_VLAN_LOOKUP_VID_0, true);
		ksz_cfg(dev, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, true);
	पूर्ण अन्यथा अणु
		ksz_cfg(dev, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, false);
		ksz_port_cfg(dev, port, REG_PORT_LUE_CTRL,
			     PORT_VLAN_LOOKUP_VID_0, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9477_port_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u32 vlan_table[3];
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	पूर्णांक err;

	err = ksz9477_get_vlan_table(dev, vlan->vid, vlan_table);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to get vlan table");
		वापस err;
	पूर्ण

	vlan_table[0] = VLAN_VALID | (vlan->vid & VLAN_FID_M);
	अगर (untagged)
		vlan_table[1] |= BIT(port);
	अन्यथा
		vlan_table[1] &= ~BIT(port);
	vlan_table[1] &= ~(BIT(dev->cpu_port));

	vlan_table[2] |= BIT(port) | BIT(dev->cpu_port);

	err = ksz9477_set_vlan_table(dev, vlan->vid, vlan_table);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to set vlan table");
		वापस err;
	पूर्ण

	/* change PVID */
	अगर (vlan->flags & BRIDGE_VLAN_INFO_PVID)
		ksz_pग_लिखो16(dev, port, REG_PORT_DEFAULT_VID, vlan->vid);

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9477_port_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	u32 vlan_table[3];
	u16 pvid;

	ksz_pपढ़ो16(dev, port, REG_PORT_DEFAULT_VID, &pvid);
	pvid = pvid & 0xFFF;

	अगर (ksz9477_get_vlan_table(dev, vlan->vid, vlan_table)) अणु
		dev_dbg(dev->dev, "Failed to get vlan table\n");
		वापस -ETIMEDOUT;
	पूर्ण

	vlan_table[2] &= ~BIT(port);

	अगर (pvid == vlan->vid)
		pvid = 1;

	अगर (untagged)
		vlan_table[1] &= ~BIT(port);

	अगर (ksz9477_set_vlan_table(dev, vlan->vid, vlan_table)) अणु
		dev_dbg(dev->dev, "Failed to set vlan table\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ksz_pग_लिखो16(dev, port, REG_PORT_DEFAULT_VID, pvid);

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9477_port_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u32 alu_table[4];
	u32 data;
	पूर्णांक ret = 0;

	mutex_lock(&dev->alu_mutex);

	/* find any entry with mac & vid */
	data = vid << ALU_FID_INDEX_S;
	data |= ((addr[0] << 8) | addr[1]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_INDEX_0, data);

	data = ((addr[2] << 24) | (addr[3] << 16));
	data |= ((addr[4] << 8) | addr[5]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_INDEX_1, data);

	/* start पढ़ो operation */
	ksz_ग_लिखो32(dev, REG_SW_ALU_CTRL__4, ALU_READ | ALU_START);

	/* रुको to be finished */
	ret = ksz9477_रुको_alu_पढ़ोy(dev);
	अगर (ret) अणु
		dev_dbg(dev->dev, "Failed to read ALU\n");
		जाओ निकास;
	पूर्ण

	/* पढ़ो ALU entry */
	ksz9477_पढ़ो_table(dev, alu_table);

	/* update ALU entry */
	alu_table[0] = ALU_V_STATIC_VALID;
	alu_table[1] |= BIT(port);
	अगर (vid)
		alu_table[1] |= ALU_V_USE_FID;
	alu_table[2] = (vid << ALU_V_FID_S);
	alu_table[2] |= ((addr[0] << 8) | addr[1]);
	alu_table[3] = ((addr[2] << 24) | (addr[3] << 16));
	alu_table[3] |= ((addr[4] << 8) | addr[5]);

	ksz9477_ग_लिखो_table(dev, alu_table);

	ksz_ग_लिखो32(dev, REG_SW_ALU_CTRL__4, ALU_WRITE | ALU_START);

	/* रुको to be finished */
	ret = ksz9477_रुको_alu_पढ़ोy(dev);
	अगर (ret)
		dev_dbg(dev->dev, "Failed to write ALU\n");

निकास:
	mutex_unlock(&dev->alu_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ksz9477_port_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u32 alu_table[4];
	u32 data;
	पूर्णांक ret = 0;

	mutex_lock(&dev->alu_mutex);

	/* पढ़ो any entry with mac & vid */
	data = vid << ALU_FID_INDEX_S;
	data |= ((addr[0] << 8) | addr[1]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_INDEX_0, data);

	data = ((addr[2] << 24) | (addr[3] << 16));
	data |= ((addr[4] << 8) | addr[5]);
	ksz_ग_लिखो32(dev, REG_SW_ALU_INDEX_1, data);

	/* start पढ़ो operation */
	ksz_ग_लिखो32(dev, REG_SW_ALU_CTRL__4, ALU_READ | ALU_START);

	/* रुको to be finished */
	ret = ksz9477_रुको_alu_पढ़ोy(dev);
	अगर (ret) अणु
		dev_dbg(dev->dev, "Failed to read ALU\n");
		जाओ निकास;
	पूर्ण

	ksz_पढ़ो32(dev, REG_SW_ALU_VAL_A, &alu_table[0]);
	अगर (alu_table[0] & ALU_V_STATIC_VALID) अणु
		ksz_पढ़ो32(dev, REG_SW_ALU_VAL_B, &alu_table[1]);
		ksz_पढ़ो32(dev, REG_SW_ALU_VAL_C, &alu_table[2]);
		ksz_पढ़ो32(dev, REG_SW_ALU_VAL_D, &alu_table[3]);

		/* clear क्रमwarding port */
		alu_table[2] &= ~BIT(port);

		/* अगर there is no port to क्रमward, clear table */
		अगर ((alu_table[2] & ALU_V_PORT_MAP) == 0) अणु
			alu_table[0] = 0;
			alu_table[1] = 0;
			alu_table[2] = 0;
			alu_table[3] = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		alu_table[0] = 0;
		alu_table[1] = 0;
		alu_table[2] = 0;
		alu_table[3] = 0;
	पूर्ण

	ksz9477_ग_लिखो_table(dev, alu_table);

	ksz_ग_लिखो32(dev, REG_SW_ALU_CTRL__4, ALU_WRITE | ALU_START);

	/* रुको to be finished */
	ret = ksz9477_रुको_alu_पढ़ोy(dev);
	अगर (ret)
		dev_dbg(dev->dev, "Failed to write ALU\n");

निकास:
	mutex_unlock(&dev->alu_mutex);

	वापस ret;
पूर्ण

अटल व्योम ksz9477_convert_alu(काष्ठा alu_काष्ठा *alu, u32 *alu_table)
अणु
	alu->is_अटल = !!(alu_table[0] & ALU_V_STATIC_VALID);
	alu->is_src_filter = !!(alu_table[0] & ALU_V_SRC_FILTER);
	alu->is_dst_filter = !!(alu_table[0] & ALU_V_DST_FILTER);
	alu->prio_age = (alu_table[0] >> ALU_V_PRIO_AGE_CNT_S) &
			ALU_V_PRIO_AGE_CNT_M;
	alu->mstp = alu_table[0] & ALU_V_MSTP_M;

	alu->is_override = !!(alu_table[1] & ALU_V_OVERRIDE);
	alu->is_use_fid = !!(alu_table[1] & ALU_V_USE_FID);
	alu->port_क्रमward = alu_table[1] & ALU_V_PORT_MAP;

	alu->fid = (alu_table[2] >> ALU_V_FID_S) & ALU_V_FID_M;

	alu->mac[0] = (alu_table[2] >> 8) & 0xFF;
	alu->mac[1] = alu_table[2] & 0xFF;
	alu->mac[2] = (alu_table[3] >> 24) & 0xFF;
	alu->mac[3] = (alu_table[3] >> 16) & 0xFF;
	alu->mac[4] = (alu_table[3] >> 8) & 0xFF;
	alu->mac[5] = alu_table[3] & 0xFF;
पूर्ण

अटल पूर्णांक ksz9477_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	पूर्णांक ret = 0;
	u32 ksz_data;
	u32 alu_table[4];
	काष्ठा alu_काष्ठा alu;
	पूर्णांक समयout;

	mutex_lock(&dev->alu_mutex);

	/* start ALU search */
	ksz_ग_लिखो32(dev, REG_SW_ALU_CTRL__4, ALU_START | ALU_SEARCH);

	करो अणु
		समयout = 1000;
		करो अणु
			ksz_पढ़ो32(dev, REG_SW_ALU_CTRL__4, &ksz_data);
			अगर ((ksz_data & ALU_VALID) || !(ksz_data & ALU_START))
				अवरोध;
			usleep_range(1, 10);
		पूर्ण जबतक (समयout-- > 0);

		अगर (!समयout) अणु
			dev_dbg(dev->dev, "Failed to search ALU\n");
			ret = -ETIMEDOUT;
			जाओ निकास;
		पूर्ण

		/* पढ़ो ALU table */
		ksz9477_पढ़ो_table(dev, alu_table);

		ksz9477_convert_alu(&alu, alu_table);

		अगर (alu.port_क्रमward & BIT(port)) अणु
			ret = cb(alu.mac, alu.fid, alu.is_अटल, data);
			अगर (ret)
				जाओ निकास;
		पूर्ण
	पूर्ण जबतक (ksz_data & ALU_START);

निकास:

	/* stop ALU search */
	ksz_ग_लिखो32(dev, REG_SW_ALU_CTRL__4, 0);

	mutex_unlock(&dev->alu_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ksz9477_port_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u32 अटल_table[4];
	u32 data;
	पूर्णांक index;
	u32 mac_hi, mac_lo;
	पूर्णांक err = 0;

	mac_hi = ((mdb->addr[0] << 8) | mdb->addr[1]);
	mac_lo = ((mdb->addr[2] << 24) | (mdb->addr[3] << 16));
	mac_lo |= ((mdb->addr[4] << 8) | mdb->addr[5]);

	mutex_lock(&dev->alu_mutex);

	क्रम (index = 0; index < dev->num_अटलs; index++) अणु
		/* find empty slot first */
		data = (index << ALU_STAT_INDEX_S) |
			ALU_STAT_READ | ALU_STAT_START;
		ksz_ग_लिखो32(dev, REG_SW_ALU_STAT_CTRL__4, data);

		/* रुको to be finished */
		err = ksz9477_रुको_alu_sta_पढ़ोy(dev);
		अगर (err) अणु
			dev_dbg(dev->dev, "Failed to read ALU STATIC\n");
			जाओ निकास;
		पूर्ण

		/* पढ़ो ALU अटल table */
		ksz9477_पढ़ो_table(dev, अटल_table);

		अगर (अटल_table[0] & ALU_V_STATIC_VALID) अणु
			/* check this has same vid & mac address */
			अगर (((अटल_table[2] >> ALU_V_FID_S) == mdb->vid) &&
			    ((अटल_table[2] & ALU_V_MAC_ADDR_HI) == mac_hi) &&
			    अटल_table[3] == mac_lo) अणु
				/* found matching one */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* found empty one */
			अवरोध;
		पूर्ण
	पूर्ण

	/* no available entry */
	अगर (index == dev->num_अटलs) अणु
		err = -ENOSPC;
		जाओ निकास;
	पूर्ण

	/* add entry */
	अटल_table[0] = ALU_V_STATIC_VALID;
	अटल_table[1] |= BIT(port);
	अगर (mdb->vid)
		अटल_table[1] |= ALU_V_USE_FID;
	अटल_table[2] = (mdb->vid << ALU_V_FID_S);
	अटल_table[2] |= mac_hi;
	अटल_table[3] = mac_lo;

	ksz9477_ग_लिखो_table(dev, अटल_table);

	data = (index << ALU_STAT_INDEX_S) | ALU_STAT_START;
	ksz_ग_लिखो32(dev, REG_SW_ALU_STAT_CTRL__4, data);

	/* रुको to be finished */
	अगर (ksz9477_रुको_alu_sta_पढ़ोy(dev))
		dev_dbg(dev->dev, "Failed to read ALU STATIC\n");

निकास:
	mutex_unlock(&dev->alu_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ksz9477_port_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u32 अटल_table[4];
	u32 data;
	पूर्णांक index;
	पूर्णांक ret = 0;
	u32 mac_hi, mac_lo;

	mac_hi = ((mdb->addr[0] << 8) | mdb->addr[1]);
	mac_lo = ((mdb->addr[2] << 24) | (mdb->addr[3] << 16));
	mac_lo |= ((mdb->addr[4] << 8) | mdb->addr[5]);

	mutex_lock(&dev->alu_mutex);

	क्रम (index = 0; index < dev->num_अटलs; index++) अणु
		/* find empty slot first */
		data = (index << ALU_STAT_INDEX_S) |
			ALU_STAT_READ | ALU_STAT_START;
		ksz_ग_लिखो32(dev, REG_SW_ALU_STAT_CTRL__4, data);

		/* रुको to be finished */
		ret = ksz9477_रुको_alu_sta_पढ़ोy(dev);
		अगर (ret) अणु
			dev_dbg(dev->dev, "Failed to read ALU STATIC\n");
			जाओ निकास;
		पूर्ण

		/* पढ़ो ALU अटल table */
		ksz9477_पढ़ो_table(dev, अटल_table);

		अगर (अटल_table[0] & ALU_V_STATIC_VALID) अणु
			/* check this has same vid & mac address */

			अगर (((अटल_table[2] >> ALU_V_FID_S) == mdb->vid) &&
			    ((अटल_table[2] & ALU_V_MAC_ADDR_HI) == mac_hi) &&
			    अटल_table[3] == mac_lo) अणु
				/* found matching one */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* no available entry */
	अगर (index == dev->num_अटलs)
		जाओ निकास;

	/* clear port */
	अटल_table[1] &= ~BIT(port);

	अगर ((अटल_table[1] & ALU_V_PORT_MAP) == 0) अणु
		/* delete entry */
		अटल_table[0] = 0;
		अटल_table[1] = 0;
		अटल_table[2] = 0;
		अटल_table[3] = 0;
	पूर्ण

	ksz9477_ग_लिखो_table(dev, अटल_table);

	data = (index << ALU_STAT_INDEX_S) | ALU_STAT_START;
	ksz_ग_लिखो32(dev, REG_SW_ALU_STAT_CTRL__4, data);

	/* रुको to be finished */
	ret = ksz9477_रुको_alu_sta_पढ़ोy(dev);
	अगर (ret)
		dev_dbg(dev->dev, "Failed to read ALU STATIC\n");

निकास:
	mutex_unlock(&dev->alu_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ksz9477_port_mirror_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा dsa_mall_mirror_tc_entry *mirror,
				   bool ingress)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	अगर (ingress)
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_RX, true);
	अन्यथा
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_TX, true);

	ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_SNIFFER, false);

	/* configure mirror port */
	ksz_port_cfg(dev, mirror->to_local_port, P_MIRROR_CTRL,
		     PORT_MIRROR_SNIFFER, true);

	ksz_cfg(dev, S_MIRROR_CTRL, SW_MIRROR_RX_TX, false);

	वापस 0;
पूर्ण

अटल व्योम ksz9477_port_mirror_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा dsa_mall_mirror_tc_entry *mirror)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u8 data;

	अगर (mirror->ingress)
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_RX, false);
	अन्यथा
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_TX, false);

	ksz_pपढ़ो8(dev, port, P_MIRROR_CTRL, &data);

	अगर (!(data & (PORT_MIRROR_RX | PORT_MIRROR_TX)))
		ksz_port_cfg(dev, mirror->to_local_port, P_MIRROR_CTRL,
			     PORT_MIRROR_SNIFFER, false);
पूर्ण

अटल bool ksz9477_get_gbit(काष्ठा ksz_device *dev, u8 data)
अणु
	bool gbit;

	अगर (dev->features & NEW_XMII)
		gbit = !(data & PORT_MII_NOT_1GBIT);
	अन्यथा
		gbit = !!(data & PORT_MII_1000MBIT_S1);
	वापस gbit;
पूर्ण

अटल व्योम ksz9477_set_gbit(काष्ठा ksz_device *dev, bool gbit, u8 *data)
अणु
	अगर (dev->features & NEW_XMII) अणु
		अगर (gbit)
			*data &= ~PORT_MII_NOT_1GBIT;
		अन्यथा
			*data |= PORT_MII_NOT_1GBIT;
	पूर्ण अन्यथा अणु
		अगर (gbit)
			*data |= PORT_MII_1000MBIT_S1;
		अन्यथा
			*data &= ~PORT_MII_1000MBIT_S1;
	पूर्ण
पूर्ण

अटल पूर्णांक ksz9477_get_xmii(काष्ठा ksz_device *dev, u8 data)
अणु
	पूर्णांक mode;

	अगर (dev->features & NEW_XMII) अणु
		चयन (data & PORT_MII_SEL_M) अणु
		हाल PORT_MII_SEL:
			mode = 0;
			अवरोध;
		हाल PORT_RMII_SEL:
			mode = 1;
			अवरोध;
		हाल PORT_GMII_SEL:
			mode = 2;
			अवरोध;
		शेष:
			mode = 3;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (data & PORT_MII_SEL_M) अणु
		हाल PORT_MII_SEL_S1:
			mode = 0;
			अवरोध;
		हाल PORT_RMII_SEL_S1:
			mode = 1;
			अवरोध;
		हाल PORT_GMII_SEL_S1:
			mode = 2;
			अवरोध;
		शेष:
			mode = 3;
		पूर्ण
	पूर्ण
	वापस mode;
पूर्ण

अटल व्योम ksz9477_set_xmii(काष्ठा ksz_device *dev, पूर्णांक mode, u8 *data)
अणु
	u8 xmii;

	अगर (dev->features & NEW_XMII) अणु
		चयन (mode) अणु
		हाल 0:
			xmii = PORT_MII_SEL;
			अवरोध;
		हाल 1:
			xmii = PORT_RMII_SEL;
			अवरोध;
		हाल 2:
			xmii = PORT_GMII_SEL;
			अवरोध;
		शेष:
			xmii = PORT_RGMII_SEL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (mode) अणु
		हाल 0:
			xmii = PORT_MII_SEL_S1;
			अवरोध;
		हाल 1:
			xmii = PORT_RMII_SEL_S1;
			अवरोध;
		हाल 2:
			xmii = PORT_GMII_SEL_S1;
			अवरोध;
		शेष:
			xmii = PORT_RGMII_SEL_S1;
			अवरोध;
		पूर्ण
	पूर्ण
	*data &= ~PORT_MII_SEL_M;
	*data |= xmii;
पूर्ण

अटल phy_पूर्णांकerface_t ksz9477_get_पूर्णांकerface(काष्ठा ksz_device *dev, पूर्णांक port)
अणु
	phy_पूर्णांकerface_t पूर्णांकerface;
	bool gbit;
	पूर्णांक mode;
	u8 data8;

	अगर (port < dev->phy_port_cnt)
		वापस PHY_INTERFACE_MODE_NA;
	ksz_pपढ़ो8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
	gbit = ksz9477_get_gbit(dev, data8);
	mode = ksz9477_get_xmii(dev, data8);
	चयन (mode) अणु
	हाल 2:
		पूर्णांकerface = PHY_INTERFACE_MODE_GMII;
		अगर (gbit)
			अवरोध;
		fallthrough;
	हाल 0:
		पूर्णांकerface = PHY_INTERFACE_MODE_MII;
		अवरोध;
	हाल 1:
		पूर्णांकerface = PHY_INTERFACE_MODE_RMII;
		अवरोध;
	शेष:
		पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;
		अगर (data8 & PORT_RGMII_ID_EG_ENABLE)
			पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_TXID;
		अगर (data8 & PORT_RGMII_ID_IG_ENABLE) अणु
			पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_RXID;
			अगर (data8 & PORT_RGMII_ID_EG_ENABLE)
				पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_ID;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस पूर्णांकerface;
पूर्ण

अटल व्योम ksz9477_port_mmd_ग_लिखो(काष्ठा ksz_device *dev, पूर्णांक port,
				   u8 dev_addr, u16 reg_addr, u16 val)
अणु
	ksz_pग_लिखो16(dev, port, REG_PORT_PHY_MMD_SETUP,
		     MMD_SETUP(PORT_MMD_OP_INDEX, dev_addr));
	ksz_pग_लिखो16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, reg_addr);
	ksz_pग_लिखो16(dev, port, REG_PORT_PHY_MMD_SETUP,
		     MMD_SETUP(PORT_MMD_OP_DATA_NO_INCR, dev_addr));
	ksz_pग_लिखो16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, val);
पूर्ण

अटल व्योम ksz9477_phy_errata_setup(काष्ठा ksz_device *dev, पूर्णांक port)
अणु
	/* Apply PHY settings to address errata listed in
	 * KSZ9477, KSZ9897, KSZ9896, KSZ9567, KSZ8565
	 * Silicon Errata and Data Sheet Clarअगरication करोcuments:
	 *
	 * Register settings are needed to improve PHY receive perक्रमmance
	 */
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x01, 0x6f, 0xdd0b);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x01, 0x8f, 0x6032);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x01, 0x9d, 0x248c);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x01, 0x75, 0x0060);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x01, 0xd3, 0x7777);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x06, 0x3008);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x08, 0x2001);

	/* Transmit waveक्रमm amplitude can be improved
	 * (1000BASE-T, 100BASE-TX, 10BASE-Te)
	 */
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x04, 0x00d0);

	/* Energy Efficient Ethernet (EEE) feature select must
	 * be manually disabled (except on KSZ8565 which is 100Mbit)
	 */
	अगर (dev->features & GBIT_SUPPORT)
		ksz9477_port_mmd_ग_लिखो(dev, port, 0x07, 0x3c, 0x0000);

	/* Register settings are required to meet data sheet
	 * supply current specअगरications
	 */
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x13, 0x6eff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x14, 0xe6ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x15, 0x6eff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x16, 0xe6ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x17, 0x00ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x18, 0x43ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x19, 0xc3ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x1a, 0x6fff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x1b, 0x07ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x1c, 0x0fff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x1d, 0xe7ff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x1e, 0xefff);
	ksz9477_port_mmd_ग_लिखो(dev, port, 0x1c, 0x20, 0xeeee);
पूर्ण

अटल व्योम ksz9477_port_setup(काष्ठा ksz_device *dev, पूर्णांक port, bool cpu_port)
अणु
	u8 data8;
	u8 member;
	u16 data16;
	काष्ठा ksz_port *p = &dev->ports[port];

	/* enable tag tail क्रम host port */
	अगर (cpu_port)
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE,
			     true);

	ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_MAC_LOOPBACK, false);

	/* set back pressure */
	ksz_port_cfg(dev, port, REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE, true);

	/* enable broadcast storm limit */
	ksz_port_cfg(dev, port, P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, true);

	/* disable DअगरfServ priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE, false);

	/* replace priority */
	ksz_port_cfg(dev, port, REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING,
		     false);
	ksz9477_port_cfg32(dev, port, REG_PORT_MTI_QUEUE_CTRL_0__4,
			   MTI_PVID_REPLACE, false);

	/* enable 802.1p priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE, true);

	अगर (port < dev->phy_port_cnt) अणु
		/* करो not क्रमce flow control */
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
			     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL,
			     false);

		अगर (dev->phy_errata_9477)
			ksz9477_phy_errata_setup(dev, port);
	पूर्ण अन्यथा अणु
		/* क्रमce flow control */
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
			     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL,
			     true);

		/* configure MAC to 1G & RGMII mode */
		ksz_pपढ़ो8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
		चयन (p->पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_MII:
			ksz9477_set_xmii(dev, 0, &data8);
			ksz9477_set_gbit(dev, false, &data8);
			p->phydev.speed = SPEED_100;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RMII:
			ksz9477_set_xmii(dev, 1, &data8);
			ksz9477_set_gbit(dev, false, &data8);
			p->phydev.speed = SPEED_100;
			अवरोध;
		हाल PHY_INTERFACE_MODE_GMII:
			ksz9477_set_xmii(dev, 2, &data8);
			ksz9477_set_gbit(dev, true, &data8);
			p->phydev.speed = SPEED_1000;
			अवरोध;
		शेष:
			ksz9477_set_xmii(dev, 3, &data8);
			ksz9477_set_gbit(dev, true, &data8);
			data8 &= ~PORT_RGMII_ID_IG_ENABLE;
			data8 &= ~PORT_RGMII_ID_EG_ENABLE;
			अगर (p->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
			    p->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
				data8 |= PORT_RGMII_ID_IG_ENABLE;
			अगर (p->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
			    p->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
				data8 |= PORT_RGMII_ID_EG_ENABLE;
			/* On KSZ9893, disable RGMII in-band status support */
			अगर (dev->features & IS_9893)
				data8 &= ~PORT_MII_MAC_MODE;
			p->phydev.speed = SPEED_1000;
			अवरोध;
		पूर्ण
		ksz_pग_लिखो8(dev, port, REG_PORT_XMII_CTRL_1, data8);
		p->phydev.duplex = 1;
	पूर्ण
	mutex_lock(&dev->dev_mutex);
	अगर (cpu_port)
		member = dev->port_mask;
	अन्यथा
		member = dev->host_mask | p->vid_member;
	mutex_unlock(&dev->dev_mutex);
	ksz9477_cfg_port_member(dev, port, member);

	/* clear pending पूर्णांकerrupts */
	अगर (port < dev->phy_port_cnt)
		ksz_pपढ़ो16(dev, port, REG_PORT_PHY_INT_ENABLE, &data16);
पूर्ण

अटल व्योम ksz9477_config_cpu_port(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	काष्ठा ksz_port *p;
	पूर्णांक i;

	क्रम (i = 0; i < dev->port_cnt; i++) अणु
		अगर (dsa_is_cpu_port(ds, i) && (dev->cpu_ports & (1 << i))) अणु
			phy_पूर्णांकerface_t पूर्णांकerface;
			स्थिर अक्षर *prev_msg;
			स्थिर अक्षर *prev_mode;

			dev->cpu_port = i;
			dev->host_mask = (1 << dev->cpu_port);
			dev->port_mask |= dev->host_mask;
			p = &dev->ports[i];

			/* Read from XMII रेजिस्टर to determine host port
			 * पूर्णांकerface.  If set specअगरically in device tree
			 * note the dअगरference to help debugging.
			 */
			पूर्णांकerface = ksz9477_get_पूर्णांकerface(dev, i);
			अगर (!p->पूर्णांकerface) अणु
				अगर (dev->compat_पूर्णांकerface) अणु
					dev_warn(dev->dev,
						 "Using legacy switch \"phy-mode\" property, because it is missing on port %d node. "
						 "Please update your device tree.\n",
						 i);
					p->पूर्णांकerface = dev->compat_पूर्णांकerface;
				पूर्ण अन्यथा अणु
					p->पूर्णांकerface = पूर्णांकerface;
				पूर्ण
			पूर्ण
			अगर (पूर्णांकerface && पूर्णांकerface != p->पूर्णांकerface) अणु
				prev_msg = " instead of ";
				prev_mode = phy_modes(पूर्णांकerface);
			पूर्ण अन्यथा अणु
				prev_msg = "";
				prev_mode = "";
			पूर्ण
			dev_info(dev->dev,
				 "Port%d: using phy mode %s%s%s\n",
				 i,
				 phy_modes(p->पूर्णांकerface),
				 prev_msg,
				 prev_mode);

			/* enable cpu port */
			ksz9477_port_setup(dev, i, true);
			p->vid_member = dev->port_mask;
			p->on = 1;
		पूर्ण
	पूर्ण

	dev->member = dev->host_mask;

	क्रम (i = 0; i < dev->port_cnt; i++) अणु
		अगर (i == dev->cpu_port)
			जारी;
		p = &dev->ports[i];

		/* Initialize to non-zero so that ksz_cfg_port_member() will
		 * be called.
		 */
		p->vid_member = (1 << i);
		p->member = dev->port_mask;
		ksz9477_port_stp_state_set(ds, i, BR_STATE_DISABLED);
		p->on = 1;
		अगर (i < dev->phy_port_cnt)
			p->phy = 1;
		अगर (dev->chip_id == 0x00947700 && i == 6) अणु
			p->sgmii = 1;

			/* SGMII PHY detection code is not implemented yet. */
			p->phy = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ksz9477_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	पूर्णांक ret = 0;

	dev->vlan_cache = devm_kसुस्मृति(dev->dev, माप(काष्ठा vlan_table),
				       dev->num_vlans, GFP_KERNEL);
	अगर (!dev->vlan_cache)
		वापस -ENOMEM;

	ret = ksz9477_reset_चयन(dev);
	अगर (ret) अणु
		dev_err(ds->dev, "failed to reset switch\n");
		वापस ret;
	पूर्ण

	/* Required क्रम port partitioning. */
	ksz9477_cfg32(dev, REG_SW_QM_CTRL__4, UNICAST_VLAN_BOUNDARY,
		      true);

	/* Do not work correctly with tail tagging. */
	ksz_cfg(dev, REG_SW_MAC_CTRL_0, SW_CHECK_LENGTH, false);

	/* accept packet up to 2000bytes */
	ksz_cfg(dev, REG_SW_MAC_CTRL_1, SW_LEGAL_PACKET_DISABLE, true);

	ksz9477_config_cpu_port(ds);

	ksz_cfg(dev, REG_SW_MAC_CTRL_1, MULTICAST_STORM_DISABLE, true);

	/* queue based egress rate limit */
	ksz_cfg(dev, REG_SW_MAC_CTRL_5, SW_OUT_RATE_LIMIT_QUEUE_BASED, true);

	/* enable global MIB counter मुक्तze function */
	ksz_cfg(dev, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FREEZE, true);

	/* start चयन */
	ksz_cfg(dev, REG_SW_OPERATION, SW_START, true);

	ksz_init_mib_समयr(dev);

	ds->configure_vlan_जबतक_not_filtering = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops ksz9477_चयन_ops = अणु
	.get_tag_protocol	= ksz9477_get_tag_protocol,
	.setup			= ksz9477_setup,
	.phy_पढ़ो		= ksz9477_phy_पढ़ो16,
	.phy_ग_लिखो		= ksz9477_phy_ग_लिखो16,
	.phylink_mac_link_करोwn	= ksz_mac_link_करोwn,
	.port_enable		= ksz_enable_port,
	.get_strings		= ksz9477_get_strings,
	.get_ethtool_stats	= ksz_get_ethtool_stats,
	.get_sset_count		= ksz_sset_count,
	.port_bridge_join	= ksz_port_bridge_join,
	.port_bridge_leave	= ksz_port_bridge_leave,
	.port_stp_state_set	= ksz9477_port_stp_state_set,
	.port_fast_age		= ksz_port_fast_age,
	.port_vlan_filtering	= ksz9477_port_vlan_filtering,
	.port_vlan_add		= ksz9477_port_vlan_add,
	.port_vlan_del		= ksz9477_port_vlan_del,
	.port_fdb_dump		= ksz9477_port_fdb_dump,
	.port_fdb_add		= ksz9477_port_fdb_add,
	.port_fdb_del		= ksz9477_port_fdb_del,
	.port_mdb_add           = ksz9477_port_mdb_add,
	.port_mdb_del           = ksz9477_port_mdb_del,
	.port_mirror_add	= ksz9477_port_mirror_add,
	.port_mirror_del	= ksz9477_port_mirror_del,
पूर्ण;

अटल u32 ksz9477_get_port_addr(पूर्णांक port, पूर्णांक offset)
अणु
	वापस PORT_CTRL_ADDR(port, offset);
पूर्ण

अटल पूर्णांक ksz9477_चयन_detect(काष्ठा ksz_device *dev)
अणु
	u8 data8;
	u8 id_hi;
	u8 id_lo;
	u32 id32;
	पूर्णांक ret;

	/* turn off SPI DO Edge select */
	ret = ksz_पढ़ो8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, &data8);
	अगर (ret)
		वापस ret;

	data8 &= ~SPI_AUTO_EDGE_DETECTION;
	ret = ksz_ग_लिखो8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, data8);
	अगर (ret)
		वापस ret;

	/* पढ़ो chip id */
	ret = ksz_पढ़ो32(dev, REG_CHIP_ID0__1, &id32);
	अगर (ret)
		वापस ret;
	ret = ksz_पढ़ो8(dev, REG_GLOBAL_OPTIONS, &data8);
	अगर (ret)
		वापस ret;

	/* Number of ports can be reduced depending on chip. */
	dev->phy_port_cnt = 5;

	/* Default capability is gigabit capable. */
	dev->features = GBIT_SUPPORT;

	dev_dbg(dev->dev, "Switch detect: ID=%08x%02x\n", id32, data8);
	id_hi = (u8)(id32 >> 16);
	id_lo = (u8)(id32 >> 8);
	अगर ((id_lo & 0xf) == 3) अणु
		/* Chip is from KSZ9893 design. */
		dev_info(dev->dev, "Found KSZ9893\n");
		dev->features |= IS_9893;

		/* Chip करोes not support gigabit. */
		अगर (data8 & SW_QW_ABLE)
			dev->features &= ~GBIT_SUPPORT;
		dev->phy_port_cnt = 2;
	पूर्ण अन्यथा अणु
		dev_info(dev->dev, "Found KSZ9477 or compatible\n");
		/* Chip uses new XMII रेजिस्टर definitions. */
		dev->features |= NEW_XMII;

		/* Chip करोes not support gigabit. */
		अगर (!(data8 & SW_GIGABIT_ABLE))
			dev->features &= ~GBIT_SUPPORT;
	पूर्ण

	/* Change chip id to known ones so it can be matched against them. */
	id32 = (id_hi << 16) | (id_lo << 8);

	dev->chip_id = id32;

	वापस 0;
पूर्ण

काष्ठा ksz_chip_data अणु
	u32 chip_id;
	स्थिर अक्षर *dev_name;
	पूर्णांक num_vlans;
	पूर्णांक num_alus;
	पूर्णांक num_अटलs;
	पूर्णांक cpu_ports;
	पूर्णांक port_cnt;
	bool phy_errata_9477;
पूर्ण;

अटल स्थिर काष्ठा ksz_chip_data ksz9477_चयन_chips[] = अणु
	अणु
		.chip_id = 0x00947700,
		.dev_name = "KSZ9477",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_अटलs = 16,
		.cpu_ports = 0x7F,	/* can be configured as cpu port */
		.port_cnt = 7,		/* total physical port count */
		.phy_errata_9477 = true,
	पूर्ण,
	अणु
		.chip_id = 0x00989700,
		.dev_name = "KSZ9897",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_अटलs = 16,
		.cpu_ports = 0x7F,	/* can be configured as cpu port */
		.port_cnt = 7,		/* total physical port count */
		.phy_errata_9477 = true,
	पूर्ण,
	अणु
		.chip_id = 0x00989300,
		.dev_name = "KSZ9893",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_अटलs = 16,
		.cpu_ports = 0x07,	/* can be configured as cpu port */
		.port_cnt = 3,		/* total port count */
	पूर्ण,
	अणु
		.chip_id = 0x00956700,
		.dev_name = "KSZ9567",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_अटलs = 16,
		.cpu_ports = 0x7F,	/* can be configured as cpu port */
		.port_cnt = 7,		/* total physical port count */
		.phy_errata_9477 = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ksz9477_चयन_init(काष्ठा ksz_device *dev)
अणु
	पूर्णांक i;

	dev->ds->ops = &ksz9477_चयन_ops;

	क्रम (i = 0; i < ARRAY_SIZE(ksz9477_चयन_chips); i++) अणु
		स्थिर काष्ठा ksz_chip_data *chip = &ksz9477_चयन_chips[i];

		अगर (dev->chip_id == chip->chip_id) अणु
			dev->name = chip->dev_name;
			dev->num_vlans = chip->num_vlans;
			dev->num_alus = chip->num_alus;
			dev->num_अटलs = chip->num_अटलs;
			dev->port_cnt = chip->port_cnt;
			dev->cpu_ports = chip->cpu_ports;
			dev->phy_errata_9477 = chip->phy_errata_9477;

			अवरोध;
		पूर्ण
	पूर्ण

	/* no चयन found */
	अगर (!dev->port_cnt)
		वापस -ENODEV;

	dev->port_mask = (1 << dev->port_cnt) - 1;

	dev->reg_mib_cnt = SWITCH_COUNTER_NUM;
	dev->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;

	dev->ports = devm_kzalloc(dev->dev,
				  dev->port_cnt * माप(काष्ठा ksz_port),
				  GFP_KERNEL);
	अगर (!dev->ports)
		वापस -ENOMEM;
	क्रम (i = 0; i < dev->port_cnt; i++) अणु
		mutex_init(&dev->ports[i].mib.cnt_mutex);
		dev->ports[i].mib.counters =
			devm_kzalloc(dev->dev,
				     माप(u64) *
				     (TOTAL_SWITCH_COUNTER_NUM + 1),
				     GFP_KERNEL);
		अगर (!dev->ports[i].mib.counters)
			वापस -ENOMEM;
	पूर्ण

	/* set the real number of ports */
	dev->ds->num_ports = dev->port_cnt;

	वापस 0;
पूर्ण

अटल व्योम ksz9477_चयन_निकास(काष्ठा ksz_device *dev)
अणु
	ksz9477_reset_चयन(dev);
पूर्ण

अटल स्थिर काष्ठा ksz_dev_ops ksz9477_dev_ops = अणु
	.get_port_addr = ksz9477_get_port_addr,
	.cfg_port_member = ksz9477_cfg_port_member,
	.flush_dyn_mac_table = ksz9477_flush_dyn_mac_table,
	.port_setup = ksz9477_port_setup,
	.r_mib_cnt = ksz9477_r_mib_cnt,
	.r_mib_pkt = ksz9477_r_mib_pkt,
	.मुक्तze_mib = ksz9477_मुक्तze_mib,
	.port_init_cnt = ksz9477_port_init_cnt,
	.shutकरोwn = ksz9477_reset_चयन,
	.detect = ksz9477_चयन_detect,
	.init = ksz9477_चयन_init,
	.निकास = ksz9477_चयन_निकास,
पूर्ण;

पूर्णांक ksz9477_चयन_रेजिस्टर(काष्ठा ksz_device *dev)
अणु
	पूर्णांक ret, i;
	काष्ठा phy_device *phydev;

	ret = ksz_चयन_रेजिस्टर(dev, &ksz9477_dev_ops);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dev->phy_port_cnt; ++i) अणु
		अगर (!dsa_is_user_port(dev->ds, i))
			जारी;

		phydev = dsa_to_port(dev->ds, i)->slave->phydev;

		/* The MAC actually cannot run in 1000 half-duplex mode. */
		phy_हटाओ_link_mode(phydev,
				     ETHTOOL_LINK_MODE_1000baseT_Half_BIT);

		/* PHY करोes not support gigabit. */
		अगर (!(dev->features & GBIT_SUPPORT))
			phy_हटाओ_link_mode(phydev,
					     ETHTOOL_LINK_MODE_1000baseT_Full_BIT);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ksz9477_चयन_रेजिस्टर);

MODULE_AUTHOR("Woojung Huh <Woojung.Huh@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch DSA Driver");
MODULE_LICENSE("GPL");
