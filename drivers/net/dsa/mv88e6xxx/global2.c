<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch Global 2 Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश "chip.h"
#समावेश "global1.h" /* क्रम MV88E6XXX_G1_STS_IRQ_DEVICE */
#समावेश "global2.h"

पूर्णांक mv88e6xxx_g2_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 *val)
अणु
	वापस mv88e6xxx_पढ़ो(chip, chip->info->global2_addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_g2_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 val)
अणु
	वापस mv88e6xxx_ग_लिखो(chip, chip->info->global2_addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_g2_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, पूर्णांक
			  bit, पूर्णांक val)
अणु
	वापस mv88e6xxx_रुको_bit(chip, chip->info->global2_addr, reg,
				  bit, val);
पूर्ण

/* Offset 0x00: Interrupt Source Register */

अटल पूर्णांक mv88e6xxx_g2_पूर्णांक_source(काष्ठा mv88e6xxx_chip *chip, u16 *src)
अणु
	/* Read (and clear most of) the Interrupt Source bits */
	वापस mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_INT_SRC, src);
पूर्ण

/* Offset 0x01: Interrupt Mask Register */

अटल पूर्णांक mv88e6xxx_g2_पूर्णांक_mask(काष्ठा mv88e6xxx_chip *chip, u16 mask)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_INT_MASK, mask);
पूर्ण

/* Offset 0x02: Management Enable 2x */

अटल पूर्णांक mv88e6xxx_g2_mgmt_enable_2x(काष्ठा mv88e6xxx_chip *chip, u16 en2x)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_MGMT_EN_2X, en2x);
पूर्ण

/* Offset 0x03: Management Enable 0x */

अटल पूर्णांक mv88e6xxx_g2_mgmt_enable_0x(काष्ठा mv88e6xxx_chip *chip, u16 en0x)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_MGMT_EN_0X, en0x);
पूर्ण

/* Offset 0x05: Switch Management Register */

अटल पूर्णांक mv88e6xxx_g2_चयन_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip,
					     bool enable)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_SWITCH_MGMT, &val);
	अगर (err)
		वापस err;

	अगर (enable)
		val |= MV88E6XXX_G2_SWITCH_MGMT_RSVD2CPU;
	अन्यथा
		val &= ~MV88E6XXX_G2_SWITCH_MGMT_RSVD2CPU;

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SWITCH_MGMT, val);
पूर्ण

पूर्णांक mv88e6185_g2_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	/* Consider the frames with reserved multicast destination
	 * addresses matching 01:80:c2:00:00:0x as MGMT.
	 */
	err = mv88e6xxx_g2_mgmt_enable_0x(chip, 0xffff);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_चयन_mgmt_rsvd2cpu(chip, true);
पूर्ण

पूर्णांक mv88e6352_g2_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	/* Consider the frames with reserved multicast destination
	 * addresses matching 01:80:c2:00:00:2x as MGMT.
	 */
	err = mv88e6xxx_g2_mgmt_enable_2x(chip, 0xffff);
	अगर (err)
		वापस err;

	वापस mv88e6185_g2_mgmt_rsvd2cpu(chip);
पूर्ण

/* Offset 0x06: Device Mapping Table रेजिस्टर */

पूर्णांक mv88e6xxx_g2_device_mapping_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक target,
				      पूर्णांक port)
अणु
	u16 val = (target << 8) | (port & 0x1f);
	/* Modern chips use 5 bits to define a device mapping port,
	 * but bit 4 is reserved on older chips, so it is safe to use.
	 */

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_DEVICE_MAPPING,
				  MV88E6XXX_G2_DEVICE_MAPPING_UPDATE | val);
पूर्ण

/* Offset 0x07: Trunk Mask Table रेजिस्टर */

पूर्णांक mv88e6xxx_g2_trunk_mask_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक num,
				  bool hash, u16 mask)
अणु
	u16 val = (num << 12) | (mask & mv88e6xxx_port_mask(chip));

	अगर (hash)
		val |= MV88E6XXX_G2_TRUNK_MASK_HASH;

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_TRUNK_MASK,
				  MV88E6XXX_G2_TRUNK_MASK_UPDATE | val);
पूर्ण

/* Offset 0x08: Trunk Mapping Table रेजिस्टर */

पूर्णांक mv88e6xxx_g2_trunk_mapping_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक id,
				     u16 map)
अणु
	स्थिर u16 port_mask = BIT(mv88e6xxx_num_ports(chip)) - 1;
	u16 val = (id << 11) | (map & port_mask);

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_TRUNK_MAPPING,
				  MV88E6XXX_G2_TRUNK_MAPPING_UPDATE | val);
पूर्ण

पूर्णांक mv88e6xxx_g2_trunk_clear(काष्ठा mv88e6xxx_chip *chip)
अणु
	स्थिर u16 port_mask = BIT(mv88e6xxx_num_ports(chip)) - 1;
	पूर्णांक i, err;

	/* Clear all eight possible Trunk Mask vectors */
	क्रम (i = 0; i < 8; ++i) अणु
		err = mv88e6xxx_g2_trunk_mask_ग_लिखो(chip, i, false, port_mask);
		अगर (err)
			वापस err;
	पूर्ण

	/* Clear all sixteen possible Trunk ID routing vectors */
	क्रम (i = 0; i < 16; ++i) अणु
		err = mv88e6xxx_g2_trunk_mapping_ग_लिखो(chip, i, 0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Offset 0x09: Ingress Rate Command रेजिस्टर
 * Offset 0x0A: Ingress Rate Data रेजिस्टर
 */

अटल पूर्णांक mv88e6xxx_g2_irl_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G2_IRL_CMD_BUSY);

	वापस mv88e6xxx_g2_रुको_bit(chip, MV88E6XXX_G2_IRL_CMD, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_irl_op(काष्ठा mv88e6xxx_chip *chip, u16 op, पूर्णांक port,
			       पूर्णांक res, पूर्णांक reg)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_IRL_CMD,
				 MV88E6XXX_G2_IRL_CMD_BUSY | op | (port << 8) |
				 (res << 5) | reg);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_irl_रुको(chip);
पूर्ण

पूर्णांक mv88e6352_g2_irl_init_all(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_g2_irl_op(chip, MV88E6352_G2_IRL_CMD_OP_INIT_ALL, port,
				   0, 0);
पूर्ण

पूर्णांक mv88e6390_g2_irl_init_all(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_g2_irl_op(chip, MV88E6390_G2_IRL_CMD_OP_INIT_ALL, port,
				   0, 0);
पूर्ण

/* Offset 0x0B: Cross-chip Port VLAN (Addr) Register
 * Offset 0x0C: Cross-chip Port VLAN Data Register
 */

अटल पूर्णांक mv88e6xxx_g2_pvt_op_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G2_PVT_ADDR_BUSY);

	वापस mv88e6xxx_g2_रुको_bit(chip, MV88E6XXX_G2_PVT_ADDR, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_pvt_op(काष्ठा mv88e6xxx_chip *chip, पूर्णांक src_dev,
			       पूर्णांक src_port, u16 op)
अणु
	पूर्णांक err;

	/* 9-bit Cross-chip PVT poपूर्णांकer: with MV88E6XXX_G2_MISC_5_BIT_PORT
	 * cleared, source device is 5-bit, source port is 4-bit.
	 */
	op |= MV88E6XXX_G2_PVT_ADDR_BUSY;
	op |= (src_dev & 0x1f) << 4;
	op |= (src_port & 0xf);

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_PVT_ADDR, op);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_pvt_op_रुको(chip);
पूर्ण

पूर्णांक mv88e6xxx_g2_pvt_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक src_dev,
			  पूर्णांक src_port, u16 *data)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g2_pvt_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_pvt_op(chip, src_dev, src_port,
				  MV88E6XXX_G2_PVT_ADDR_OP_READ);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_PVT_DATA, data);
पूर्ण

पूर्णांक mv88e6xxx_g2_pvt_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक src_dev,
			   पूर्णांक src_port, u16 data)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g2_pvt_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_PVT_DATA, data);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_pvt_op(chip, src_dev, src_port,
				   MV88E6XXX_G2_PVT_ADDR_OP_WRITE_PVLAN);
पूर्ण

/* Offset 0x0D: Switch MAC/WoL/WoF रेजिस्टर */

अटल पूर्णांक mv88e6xxx_g2_चयन_mac_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
					 अचिन्हित पूर्णांक poपूर्णांकer, u8 data)
अणु
	u16 val = (poपूर्णांकer << 8) | data;

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SWITCH_MAC,
				  MV88E6XXX_G2_SWITCH_MAC_UPDATE | val);
पूर्ण

पूर्णांक mv88e6xxx_g2_set_चयन_mac(काष्ठा mv88e6xxx_chip *chip, u8 *addr)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < 6; i++) अणु
		err = mv88e6xxx_g2_चयन_mac_ग_लिखो(chip, i, addr[i]);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Offset 0x0E: ATU Statistics */

पूर्णांक mv88e6xxx_g2_atu_stats_set(काष्ठा mv88e6xxx_chip *chip, u16 kind, u16 bin)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_ATU_STATS,
				  kind | bin);
पूर्ण

पूर्णांक mv88e6xxx_g2_atu_stats_get(काष्ठा mv88e6xxx_chip *chip, u16 *stats)
अणु
	वापस mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_ATU_STATS, stats);
पूर्ण

/* Offset 0x0F: Priority Override Table */

अटल पूर्णांक mv88e6xxx_g2_pot_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक poपूर्णांकer,
				  u8 data)
अणु
	u16 val = (poपूर्णांकer << 8) | (data & 0x7);

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_PRIO_OVERRIDE,
				  MV88E6XXX_G2_PRIO_OVERRIDE_UPDATE | val);
पूर्ण

पूर्णांक mv88e6xxx_g2_pot_clear(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक i, err;

	/* Clear all sixteen possible Priority Override entries */
	क्रम (i = 0; i < 16; i++) अणु
		err = mv88e6xxx_g2_pot_ग_लिखो(chip, i, 0);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Offset 0x14: EEPROM Command
 * Offset 0x15: EEPROM Data (क्रम 16-bit data access)
 * Offset 0x15: EEPROM Addr (क्रम 8-bit data access)
 */

अटल पूर्णांक mv88e6xxx_g2_eeprom_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G2_EEPROM_CMD_BUSY);
	पूर्णांक err;

	err = mv88e6xxx_g2_रुको_bit(chip, MV88E6XXX_G2_EEPROM_CMD, bit, 0);
	अगर (err)
		वापस err;

	bit = __bf_shf(MV88E6XXX_G2_EEPROM_CMD_RUNNING);

	वापस mv88e6xxx_g2_रुको_bit(chip, MV88E6XXX_G2_EEPROM_CMD, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_eeprom_cmd(काष्ठा mv88e6xxx_chip *chip, u16 cmd)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_EEPROM_CMD,
				 MV88E6XXX_G2_EEPROM_CMD_BUSY | cmd);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_eeprom_रुको(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_eeprom_पढ़ो8(काष्ठा mv88e6xxx_chip *chip,
				     u16 addr, u8 *data)
अणु
	u16 cmd = MV88E6XXX_G2_EEPROM_CMD_OP_READ;
	पूर्णांक err;

	err = mv88e6xxx_g2_eeprom_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6390_G2_EEPROM_ADDR, addr);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_eeprom_cmd(chip, cmd);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_EEPROM_CMD, &cmd);
	अगर (err)
		वापस err;

	*data = cmd & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_eeprom_ग_लिखो8(काष्ठा mv88e6xxx_chip *chip,
				      u16 addr, u8 data)
अणु
	u16 cmd = MV88E6XXX_G2_EEPROM_CMD_OP_WRITE |
		MV88E6XXX_G2_EEPROM_CMD_WRITE_EN;
	पूर्णांक err;

	err = mv88e6xxx_g2_eeprom_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6390_G2_EEPROM_ADDR, addr);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_eeprom_cmd(chip, cmd | data);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_eeprom_पढ़ो16(काष्ठा mv88e6xxx_chip *chip,
				      u8 addr, u16 *data)
अणु
	u16 cmd = MV88E6XXX_G2_EEPROM_CMD_OP_READ | addr;
	पूर्णांक err;

	err = mv88e6xxx_g2_eeprom_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_eeprom_cmd(chip, cmd);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_पढ़ो(chip, MV88E6352_G2_EEPROM_DATA, data);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_eeprom_ग_लिखो16(काष्ठा mv88e6xxx_chip *chip,
				       u8 addr, u16 data)
अणु
	u16 cmd = MV88E6XXX_G2_EEPROM_CMD_OP_WRITE | addr;
	पूर्णांक err;

	err = mv88e6xxx_g2_eeprom_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6352_G2_EEPROM_DATA, data);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_eeprom_cmd(chip, cmd);
पूर्ण

पूर्णांक mv88e6xxx_g2_get_eeprom8(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	अचिन्हित पूर्णांक offset = eeprom->offset;
	अचिन्हित पूर्णांक len = eeprom->len;
	पूर्णांक err;

	eeprom->len = 0;

	जबतक (len) अणु
		err = mv88e6xxx_g2_eeprom_पढ़ो8(chip, offset, data);
		अगर (err)
			वापस err;

		eeprom->len++;
		offset++;
		data++;
		len--;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_g2_set_eeprom8(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	अचिन्हित पूर्णांक offset = eeprom->offset;
	अचिन्हित पूर्णांक len = eeprom->len;
	पूर्णांक err;

	eeprom->len = 0;

	जबतक (len) अणु
		err = mv88e6xxx_g2_eeprom_ग_लिखो8(chip, offset, *data);
		अगर (err)
			वापस err;

		eeprom->len++;
		offset++;
		data++;
		len--;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_g2_get_eeprom16(काष्ठा mv88e6xxx_chip *chip,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	अचिन्हित पूर्णांक offset = eeprom->offset;
	अचिन्हित पूर्णांक len = eeprom->len;
	u16 val;
	पूर्णांक err;

	eeprom->len = 0;

	अगर (offset & 1) अणु
		err = mv88e6xxx_g2_eeprom_पढ़ो16(chip, offset >> 1, &val);
		अगर (err)
			वापस err;

		*data++ = (val >> 8) & 0xff;

		offset++;
		len--;
		eeprom->len++;
	पूर्ण

	जबतक (len >= 2) अणु
		err = mv88e6xxx_g2_eeprom_पढ़ो16(chip, offset >> 1, &val);
		अगर (err)
			वापस err;

		*data++ = val & 0xff;
		*data++ = (val >> 8) & 0xff;

		offset += 2;
		len -= 2;
		eeprom->len += 2;
	पूर्ण

	अगर (len) अणु
		err = mv88e6xxx_g2_eeprom_पढ़ो16(chip, offset >> 1, &val);
		अगर (err)
			वापस err;

		*data++ = val & 0xff;

		offset++;
		len--;
		eeprom->len++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_g2_set_eeprom16(काष्ठा mv88e6xxx_chip *chip,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	अचिन्हित पूर्णांक offset = eeprom->offset;
	अचिन्हित पूर्णांक len = eeprom->len;
	u16 val;
	पूर्णांक err;

	/* Ensure the RO WriteEn bit is set */
	err = mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_EEPROM_CMD, &val);
	अगर (err)
		वापस err;

	अगर (!(val & MV88E6XXX_G2_EEPROM_CMD_WRITE_EN))
		वापस -EROFS;

	eeprom->len = 0;

	अगर (offset & 1) अणु
		err = mv88e6xxx_g2_eeprom_पढ़ो16(chip, offset >> 1, &val);
		अगर (err)
			वापस err;

		val = (*data++ << 8) | (val & 0xff);

		err = mv88e6xxx_g2_eeprom_ग_लिखो16(chip, offset >> 1, val);
		अगर (err)
			वापस err;

		offset++;
		len--;
		eeprom->len++;
	पूर्ण

	जबतक (len >= 2) अणु
		val = *data++;
		val |= *data++ << 8;

		err = mv88e6xxx_g2_eeprom_ग_लिखो16(chip, offset >> 1, val);
		अगर (err)
			वापस err;

		offset += 2;
		len -= 2;
		eeprom->len += 2;
	पूर्ण

	अगर (len) अणु
		err = mv88e6xxx_g2_eeprom_पढ़ो16(chip, offset >> 1, &val);
		अगर (err)
			वापस err;

		val = (val & 0xff00) | *data++;

		err = mv88e6xxx_g2_eeprom_ग_लिखो16(chip, offset >> 1, val);
		अगर (err)
			वापस err;

		offset++;
		len--;
		eeprom->len++;
	पूर्ण

	वापस 0;
पूर्ण

/* Offset 0x18: SMI PHY Command Register
 * Offset 0x19: SMI PHY Data Register
 */

अटल पूर्णांक mv88e6xxx_g2_smi_phy_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G2_SMI_PHY_CMD_BUSY);

	वापस mv88e6xxx_g2_रुको_bit(chip, MV88E6XXX_G2_SMI_PHY_CMD, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_smi_phy_cmd(काष्ठा mv88e6xxx_chip *chip, u16 cmd)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SMI_PHY_CMD,
				 MV88E6XXX_G2_SMI_PHY_CMD_BUSY | cmd);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_smi_phy_रुको(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_smi_phy_access(काष्ठा mv88e6xxx_chip *chip,
				       bool बाह्यal, bool c45, u16 op, पूर्णांक dev,
				       पूर्णांक reg)
अणु
	u16 cmd = op;

	अगर (बाह्यal)
		cmd |= MV88E6390_G2_SMI_PHY_CMD_FUNC_EXTERNAL;
	अन्यथा
		cmd |= MV88E6390_G2_SMI_PHY_CMD_FUNC_INTERNAL; /* empty mask */

	अगर (c45)
		cmd |= MV88E6XXX_G2_SMI_PHY_CMD_MODE_45; /* empty mask */
	अन्यथा
		cmd |= MV88E6XXX_G2_SMI_PHY_CMD_MODE_22;

	dev <<= __bf_shf(MV88E6XXX_G2_SMI_PHY_CMD_DEV_ADDR_MASK);
	cmd |= dev & MV88E6XXX_G2_SMI_PHY_CMD_DEV_ADDR_MASK;
	cmd |= reg & MV88E6XXX_G2_SMI_PHY_CMD_REG_ADDR_MASK;

	वापस mv88e6xxx_g2_smi_phy_cmd(chip, cmd);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_smi_phy_access_c22(काष्ठा mv88e6xxx_chip *chip,
					   bool बाह्यal, u16 op, पूर्णांक dev,
					   पूर्णांक reg)
अणु
	वापस mv88e6xxx_g2_smi_phy_access(chip, बाह्यal, false, op, dev, reg);
पूर्ण

/* IEEE 802.3 Clause 22 Read Data Register */
अटल पूर्णांक mv88e6xxx_g2_smi_phy_पढ़ो_data_c22(काष्ठा mv88e6xxx_chip *chip,
					      bool बाह्यal, पूर्णांक dev, पूर्णांक reg,
					      u16 *data)
अणु
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_22_READ_DATA;
	पूर्णांक err;

	err = mv88e6xxx_g2_smi_phy_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_smi_phy_access_c22(chip, बाह्यal, op, dev, reg);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
पूर्ण

/* IEEE 802.3 Clause 22 Write Data Register */
अटल पूर्णांक mv88e6xxx_g2_smi_phy_ग_लिखो_data_c22(काष्ठा mv88e6xxx_chip *chip,
					       bool बाह्यal, पूर्णांक dev, पूर्णांक reg,
					       u16 data)
अणु
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_22_WRITE_DATA;
	पूर्णांक err;

	err = mv88e6xxx_g2_smi_phy_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_smi_phy_access_c22(chip, बाह्यal, op, dev, reg);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_smi_phy_access_c45(काष्ठा mv88e6xxx_chip *chip,
					   bool बाह्यal, u16 op, पूर्णांक port,
					   पूर्णांक dev)
अणु
	वापस mv88e6xxx_g2_smi_phy_access(chip, बाह्यal, true, op, port, dev);
पूर्ण

/* IEEE 802.3 Clause 45 Write Address Register */
अटल पूर्णांक mv88e6xxx_g2_smi_phy_ग_लिखो_addr_c45(काष्ठा mv88e6xxx_chip *chip,
					       bool बाह्यal, पूर्णांक port, पूर्णांक dev,
					       पूर्णांक addr)
अणु
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WRITE_ADDR;
	पूर्णांक err;

	err = mv88e6xxx_g2_smi_phy_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SMI_PHY_DATA, addr);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_smi_phy_access_c45(chip, बाह्यal, op, port, dev);
पूर्ण

/* IEEE 802.3 Clause 45 Read Data Register */
अटल पूर्णांक mv88e6xxx_g2_smi_phy_पढ़ो_data_c45(काष्ठा mv88e6xxx_chip *chip,
					      bool बाह्यal, पूर्णांक port, पूर्णांक dev,
					      u16 *data)
अणु
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_READ_DATA;
	पूर्णांक err;

	err = mv88e6xxx_g2_smi_phy_access_c45(chip, बाह्यal, op, port, dev);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_smi_phy_पढ़ो_c45(काष्ठा mv88e6xxx_chip *chip,
					 bool बाह्यal, पूर्णांक port, पूर्णांक reg,
					 u16 *data)
अणु
	पूर्णांक dev = (reg >> 16) & 0x1f;
	पूर्णांक addr = reg & 0xffff;
	पूर्णांक err;

	err = mv88e6xxx_g2_smi_phy_ग_लिखो_addr_c45(chip, बाह्यal, port, dev,
						  addr);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_smi_phy_पढ़ो_data_c45(chip, बाह्यal, port, dev,
						  data);
पूर्ण

/* IEEE 802.3 Clause 45 Write Data Register */
अटल पूर्णांक mv88e6xxx_g2_smi_phy_ग_लिखो_data_c45(काष्ठा mv88e6xxx_chip *chip,
					       bool बाह्यal, पूर्णांक port, पूर्णांक dev,
					       u16 data)
अणु
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WRITE_DATA;
	पूर्णांक err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_smi_phy_access_c45(chip, बाह्यal, op, port, dev);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_smi_phy_ग_लिखो_c45(काष्ठा mv88e6xxx_chip *chip,
					  bool बाह्यal, पूर्णांक port, पूर्णांक reg,
					  u16 data)
अणु
	पूर्णांक dev = (reg >> 16) & 0x1f;
	पूर्णांक addr = reg & 0xffff;
	पूर्णांक err;

	err = mv88e6xxx_g2_smi_phy_ग_लिखो_addr_c45(chip, बाह्यal, port, dev,
						  addr);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g2_smi_phy_ग_लिखो_data_c45(chip, बाह्यal, port, dev,
						   data);
पूर्ण

पूर्णांक mv88e6xxx_g2_smi_phy_पढ़ो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			      पूर्णांक addr, पूर्णांक reg, u16 *val)
अणु
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	bool बाह्यal = mdio_bus->बाह्यal;

	अगर (reg & MII_ADDR_C45)
		वापस mv88e6xxx_g2_smi_phy_पढ़ो_c45(chip, बाह्यal, addr, reg,
						     val);

	वापस mv88e6xxx_g2_smi_phy_पढ़ो_data_c22(chip, बाह्यal, addr, reg,
						  val);
पूर्ण

पूर्णांक mv88e6xxx_g2_smi_phy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			       पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	bool बाह्यal = mdio_bus->बाह्यal;

	अगर (reg & MII_ADDR_C45)
		वापस mv88e6xxx_g2_smi_phy_ग_लिखो_c45(chip, बाह्यal, addr, reg,
						      val);

	वापस mv88e6xxx_g2_smi_phy_ग_लिखो_data_c22(chip, बाह्यal, addr, reg,
						   val);
पूर्ण

/* Offset 0x1B: Watchकरोg Control */
अटल पूर्णांक mv88e6097_watchकरोg_action(काष्ठा mv88e6xxx_chip *chip, पूर्णांक irq)
अणु
	u16 reg;

	mv88e6xxx_g2_पढ़ो(chip, MV88E6352_G2_WDOG_CTL, &reg);

	dev_info(chip->dev, "Watchdog event: 0x%04x", reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mv88e6097_watchकरोg_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 reg;

	mv88e6xxx_g2_पढ़ो(chip, MV88E6352_G2_WDOG_CTL, &reg);

	reg &= ~(MV88E6352_G2_WDOG_CTL_EGRESS_ENABLE |
		 MV88E6352_G2_WDOG_CTL_QC_ENABLE);

	mv88e6xxx_g2_ग_लिखो(chip, MV88E6352_G2_WDOG_CTL, reg);
पूर्ण

अटल पूर्णांक mv88e6097_watchकरोg_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6352_G2_WDOG_CTL,
				  MV88E6352_G2_WDOG_CTL_EGRESS_ENABLE |
				  MV88E6352_G2_WDOG_CTL_QC_ENABLE |
				  MV88E6352_G2_WDOG_CTL_SWRESET);
पूर्ण

स्थिर काष्ठा mv88e6xxx_irq_ops mv88e6097_watchकरोg_ops = अणु
	.irq_action = mv88e6097_watchकरोg_action,
	.irq_setup = mv88e6097_watchकरोg_setup,
	.irq_मुक्त = mv88e6097_watchकरोg_मुक्त,
पूर्ण;

अटल व्योम mv88e6250_watchकरोg_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 reg;

	mv88e6xxx_g2_पढ़ो(chip, MV88E6250_G2_WDOG_CTL, &reg);

	reg &= ~(MV88E6250_G2_WDOG_CTL_EGRESS_ENABLE |
		 MV88E6250_G2_WDOG_CTL_QC_ENABLE);

	mv88e6xxx_g2_ग_लिखो(chip, MV88E6250_G2_WDOG_CTL, reg);
पूर्ण

अटल पूर्णांक mv88e6250_watchकरोg_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6250_G2_WDOG_CTL,
				  MV88E6250_G2_WDOG_CTL_EGRESS_ENABLE |
				  MV88E6250_G2_WDOG_CTL_QC_ENABLE |
				  MV88E6250_G2_WDOG_CTL_SWRESET);
पूर्ण

स्थिर काष्ठा mv88e6xxx_irq_ops mv88e6250_watchकरोg_ops = अणु
	.irq_action = mv88e6097_watchकरोg_action,
	.irq_setup = mv88e6250_watchकरोg_setup,
	.irq_मुक्त = mv88e6250_watchकरोg_मुक्त,
पूर्ण;

अटल पूर्णांक mv88e6390_watchकरोg_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6390_G2_WDOG_CTL,
				  MV88E6390_G2_WDOG_CTL_UPDATE |
				  MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE |
				  MV88E6390_G2_WDOG_CTL_CUT_THROUGH |
				  MV88E6390_G2_WDOG_CTL_QUEUE_CONTROLLER |
				  MV88E6390_G2_WDOG_CTL_EGRESS |
				  MV88E6390_G2_WDOG_CTL_FORCE_IRQ);
पूर्ण

अटल पूर्णांक mv88e6390_watchकरोg_action(काष्ठा mv88e6xxx_chip *chip, पूर्णांक irq)
अणु
	u16 reg;

	mv88e6xxx_g2_ग_लिखो(chip, MV88E6390_G2_WDOG_CTL,
			   MV88E6390_G2_WDOG_CTL_PTR_EVENT);
	mv88e6xxx_g2_पढ़ो(chip, MV88E6390_G2_WDOG_CTL, &reg);

	dev_info(chip->dev, "Watchdog event: 0x%04x",
		 reg & MV88E6390_G2_WDOG_CTL_DATA_MASK);

	mv88e6xxx_g2_ग_लिखो(chip, MV88E6390_G2_WDOG_CTL,
			   MV88E6390_G2_WDOG_CTL_PTR_HISTORY);
	mv88e6xxx_g2_पढ़ो(chip, MV88E6390_G2_WDOG_CTL, &reg);

	dev_info(chip->dev, "Watchdog history: 0x%04x",
		 reg & MV88E6390_G2_WDOG_CTL_DATA_MASK);

	/* Trigger a software reset to try to recover the चयन */
	अगर (chip->info->ops->reset)
		chip->info->ops->reset(chip);

	mv88e6390_watchकरोg_setup(chip);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mv88e6390_watchकरोg_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	mv88e6xxx_g2_ग_लिखो(chip, MV88E6390_G2_WDOG_CTL,
			   MV88E6390_G2_WDOG_CTL_UPDATE |
			   MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE);
पूर्ण

स्थिर काष्ठा mv88e6xxx_irq_ops mv88e6390_watchकरोg_ops = अणु
	.irq_action = mv88e6390_watchकरोg_action,
	.irq_setup = mv88e6390_watchकरोg_setup,
	.irq_मुक्त = mv88e6390_watchकरोg_मुक्त,
पूर्ण;

अटल irqवापस_t mv88e6xxx_g2_watchकरोg_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv88e6xxx_chip *chip = dev_id;
	irqवापस_t ret = IRQ_NONE;

	mv88e6xxx_reg_lock(chip);
	अगर (chip->info->ops->watchकरोg_ops->irq_action)
		ret = chip->info->ops->watchकरोg_ops->irq_action(chip, irq);
	mv88e6xxx_reg_unlock(chip);

	वापस ret;
पूर्ण

अटल व्योम mv88e6xxx_g2_watchकरोg_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	mv88e6xxx_reg_lock(chip);
	अगर (chip->info->ops->watchकरोg_ops->irq_मुक्त)
		chip->info->ops->watchकरोg_ops->irq_मुक्त(chip);
	mv88e6xxx_reg_unlock(chip);

	मुक्त_irq(chip->watchकरोg_irq, chip);
	irq_dispose_mapping(chip->watchकरोg_irq);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_watchकरोg_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	chip->watchकरोg_irq = irq_find_mapping(chip->g2_irq.करोमुख्य,
					      MV88E6XXX_G2_INT_SOURCE_WATCHDOG);
	अगर (chip->watchकरोg_irq < 0)
		वापस chip->watchकरोg_irq;

	snम_लिखो(chip->watchकरोg_irq_name, माप(chip->watchकरोg_irq_name),
		 "mv88e6xxx-%s-watchdog", dev_name(chip->dev));

	err = request_thपढ़ोed_irq(chip->watchकरोg_irq, शून्य,
				   mv88e6xxx_g2_watchकरोg_thपढ़ो_fn,
				   IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
				   chip->watchकरोg_irq_name, chip);
	अगर (err)
		वापस err;

	mv88e6xxx_reg_lock(chip);
	अगर (chip->info->ops->watchकरोg_ops->irq_setup)
		err = chip->info->ops->watchकरोg_ops->irq_setup(chip);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

/* Offset 0x1D: Misc Register */

अटल पूर्णांक mv88e6xxx_g2_misc_5_bit_port(काष्ठा mv88e6xxx_chip *chip,
					bool port_5_bit)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_MISC, &val);
	अगर (err)
		वापस err;

	अगर (port_5_bit)
		val |= MV88E6XXX_G2_MISC_5_BIT_PORT;
	अन्यथा
		val &= ~MV88E6XXX_G2_MISC_5_BIT_PORT;

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_MISC, val);
पूर्ण

पूर्णांक mv88e6xxx_g2_misc_4_bit_port(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g2_misc_5_bit_port(chip, false);
पूर्ण

अटल व्योम mv88e6xxx_g2_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक n = d->hwirq;

	chip->g2_irq.masked |= (1 << n);
पूर्ण

अटल व्योम mv88e6xxx_g2_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक n = d->hwirq;

	chip->g2_irq.masked &= ~(1 << n);
पूर्ण

अटल irqवापस_t mv88e6xxx_g2_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv88e6xxx_chip *chip = dev_id;
	अचिन्हित पूर्णांक nhandled = 0;
	अचिन्हित पूर्णांक sub_irq;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;
	u16 reg;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_g2_पूर्णांक_source(chip, &reg);
	mv88e6xxx_reg_unlock(chip);
	अगर (err)
		जाओ out;

	क्रम (n = 0; n < 16; ++n) अणु
		अगर (reg & (1 << n)) अणु
			sub_irq = irq_find_mapping(chip->g2_irq.करोमुख्य, n);
			handle_nested_irq(sub_irq);
			++nhandled;
		पूर्ण
	पूर्ण
out:
	वापस (nhandled > 0 ? IRQ_HANDLED : IRQ_NONE);
पूर्ण

अटल व्योम mv88e6xxx_g2_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);

	mv88e6xxx_reg_lock(chip);
पूर्ण

अटल व्योम mv88e6xxx_g2_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	पूर्णांक err;

	err = mv88e6xxx_g2_पूर्णांक_mask(chip, ~chip->g2_irq.masked);
	अगर (err)
		dev_err(chip->dev, "failed to mask interrupts\n");

	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल स्थिर काष्ठा irq_chip mv88e6xxx_g2_irq_chip = अणु
	.name			= "mv88e6xxx-g2",
	.irq_mask		= mv88e6xxx_g2_irq_mask,
	.irq_unmask		= mv88e6xxx_g2_irq_unmask,
	.irq_bus_lock		= mv88e6xxx_g2_irq_bus_lock,
	.irq_bus_sync_unlock	= mv88e6xxx_g2_irq_bus_sync_unlock,
पूर्ण;

अटल पूर्णांक mv88e6xxx_g2_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d,
				       अचिन्हित पूर्णांक irq,
				       irq_hw_number_t hwirq)
अणु
	काष्ठा mv88e6xxx_chip *chip = d->host_data;

	irq_set_chip_data(irq, d->host_data);
	irq_set_chip_and_handler(irq, &chip->g2_irq.chip, handle_level_irq);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mv88e6xxx_g2_irq_करोमुख्य_ops = अणु
	.map	= mv88e6xxx_g2_irq_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

व्योम mv88e6xxx_g2_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक irq, virq;

	mv88e6xxx_g2_watchकरोg_मुक्त(chip);

	मुक्त_irq(chip->device_irq, chip);
	irq_dispose_mapping(chip->device_irq);

	क्रम (irq = 0; irq < 16; irq++) अणु
		virq = irq_find_mapping(chip->g2_irq.करोमुख्य, irq);
		irq_dispose_mapping(virq);
	पूर्ण

	irq_करोमुख्य_हटाओ(chip->g2_irq.करोमुख्य);
पूर्ण

पूर्णांक mv88e6xxx_g2_irq_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err, irq, virq;

	chip->g2_irq.masked = ~0;
	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_g2_पूर्णांक_mask(chip, ~chip->g2_irq.masked);
	mv88e6xxx_reg_unlock(chip);
	अगर (err)
		वापस err;

	chip->g2_irq.करोमुख्य = irq_करोमुख्य_add_simple(
		chip->dev->of_node, 16, 0, &mv88e6xxx_g2_irq_करोमुख्य_ops, chip);
	अगर (!chip->g2_irq.करोमुख्य)
		वापस -ENOMEM;

	क्रम (irq = 0; irq < 16; irq++)
		irq_create_mapping(chip->g2_irq.करोमुख्य, irq);

	chip->g2_irq.chip = mv88e6xxx_g2_irq_chip;

	chip->device_irq = irq_find_mapping(chip->g1_irq.करोमुख्य,
					    MV88E6XXX_G1_STS_IRQ_DEVICE);
	अगर (chip->device_irq < 0) अणु
		err = chip->device_irq;
		जाओ out;
	पूर्ण

	snम_लिखो(chip->device_irq_name, माप(chip->device_irq_name),
		 "mv88e6xxx-%s-g2", dev_name(chip->dev));

	err = request_thपढ़ोed_irq(chip->device_irq, शून्य,
				   mv88e6xxx_g2_irq_thपढ़ो_fn,
				   IRQF_ONESHOT, chip->device_irq_name, chip);
	अगर (err)
		जाओ out;

	वापस mv88e6xxx_g2_watchकरोg_setup(chip);

out:
	क्रम (irq = 0; irq < 16; irq++) अणु
		virq = irq_find_mapping(chip->g2_irq.करोमुख्य, irq);
		irq_dispose_mapping(virq);
	पूर्ण

	irq_करोमुख्य_हटाओ(chip->g2_irq.करोमुख्य);

	वापस err;
पूर्ण

पूर्णांक mv88e6xxx_g2_irq_mdio_setup(काष्ठा mv88e6xxx_chip *chip,
				काष्ठा mii_bus *bus)
अणु
	पूर्णांक phy, irq, err, err_phy;

	क्रम (phy = 0; phy < chip->info->num_पूर्णांकernal_phys; phy++) अणु
		irq = irq_find_mapping(chip->g2_irq.करोमुख्य, phy);
		अगर (irq < 0) अणु
			err = irq;
			जाओ out;
		पूर्ण
		bus->irq[chip->info->phy_base_addr + phy] = irq;
	पूर्ण
	वापस 0;
out:
	err_phy = phy;

	क्रम (phy = 0; phy < err_phy; phy++)
		irq_dispose_mapping(bus->irq[phy]);

	वापस err;
पूर्ण

व्योम mv88e6xxx_g2_irq_mdio_मुक्त(काष्ठा mv88e6xxx_chip *chip,
				काष्ठा mii_bus *bus)
अणु
	पूर्णांक phy;

	क्रम (phy = 0; phy < chip->info->num_पूर्णांकernal_phys; phy++)
		irq_dispose_mapping(bus->irq[phy]);
पूर्ण
