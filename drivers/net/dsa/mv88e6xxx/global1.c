<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch Global (1) Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश <linux/bitfield.h>

#समावेश "chip.h"
#समावेश "global1.h"

पूर्णांक mv88e6xxx_g1_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक addr = chip->info->global1_addr;

	वापस mv88e6xxx_पढ़ो(chip, addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_g1_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 val)
अणु
	पूर्णांक addr = chip->info->global1_addr;

	वापस mv88e6xxx_ग_लिखो(chip, addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_g1_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, पूर्णांक
			  bit, पूर्णांक val)
अणु
	वापस mv88e6xxx_रुको_bit(chip, chip->info->global1_addr, reg,
				  bit, val);
पूर्ण

पूर्णांक mv88e6xxx_g1_रुको_mask(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
			   u16 mask, u16 val)
अणु
	वापस mv88e6xxx_रुको_mask(chip, chip->info->global1_addr, reg,
				   mask, val);
पूर्ण

/* Offset 0x00: Switch Global Status Register */

अटल पूर्णांक mv88e6185_g1_रुको_ppu_disabled(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g1_रुको_mask(chip, MV88E6XXX_G1_STS,
				      MV88E6185_G1_STS_PPU_STATE_MASK,
				      MV88E6185_G1_STS_PPU_STATE_DISABLED);
पूर्ण

अटल पूर्णांक mv88e6185_g1_रुको_ppu_polling(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g1_रुको_mask(chip, MV88E6XXX_G1_STS,
				      MV88E6185_G1_STS_PPU_STATE_MASK,
				      MV88E6185_G1_STS_PPU_STATE_POLLING);
पूर्ण

अटल पूर्णांक mv88e6352_g1_रुको_ppu_polling(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6352_G1_STS_PPU_STATE);

	वापस mv88e6xxx_g1_रुको_bit(chip, MV88E6XXX_G1_STS, bit, 1);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_रुको_init_पढ़ोy(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G1_STS_INIT_READY);

	/* Wait up to 1 second क्रम the चयन to be पढ़ोy. The InitReady bit 11
	 * is set to a one when all units inside the device (ATU, VTU, etc.)
	 * have finished their initialization and are पढ़ोy to accept frames.
	 */
	वापस mv88e6xxx_g1_रुको_bit(chip, MV88E6XXX_G1_STS, bit, 1);
पूर्ण

व्योम mv88e6xxx_g1_रुको_eeprom_करोne(काष्ठा mv88e6xxx_chip *chip)
अणु
	स्थिर अचिन्हित दीर्घ समयout = jअगरfies + 1 * HZ;
	u16 val;
	पूर्णांक err;

	/* Wait up to 1 second क्रम the चयन to finish पढ़ोing the
	 * EEPROM.
	 */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STS, &val);
		अगर (err) अणु
			dev_err(chip->dev, "Error reading status");
			वापस;
		पूर्ण

		/* If the चयन is still resetting, it may not
		 * respond on the bus, and so MDIO पढ़ो वापसs
		 * 0xffff. Dअगरferentiate between that, and रुकोing क्रम
		 * the EEPROM to be करोne by bit 0 being set.
		 */
		अगर (val != 0xffff &&
		    val & BIT(MV88E6XXX_G1_STS_IRQ_EEPROM_DONE))
			वापस;

		usleep_range(1000, 2000);
	पूर्ण

	dev_err(chip->dev, "Timeout waiting for EEPROM done");
पूर्ण

/* Offset 0x01: Switch MAC Address Register Bytes 0 & 1
 * Offset 0x02: Switch MAC Address Register Bytes 2 & 3
 * Offset 0x03: Switch MAC Address Register Bytes 4 & 5
 */
पूर्णांक mv88e6xxx_g1_set_चयन_mac(काष्ठा mv88e6xxx_chip *chip, u8 *addr)
अणु
	u16 reg;
	पूर्णांक err;

	reg = (addr[0] << 8) | addr[1];
	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_MAC_01, reg);
	अगर (err)
		वापस err;

	reg = (addr[2] << 8) | addr[3];
	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_MAC_23, reg);
	अगर (err)
		वापस err;

	reg = (addr[4] << 8) | addr[5];
	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_MAC_45, reg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* Offset 0x04: Switch Global Control Register */

पूर्णांक mv88e6185_g1_reset(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	/* Set the SWReset bit 15 aदीर्घ with the PPUEn bit 14, to also restart
	 * the PPU, including re-करोing PHY detection and initialization
	 */
	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &val);
	अगर (err)
		वापस err;

	val |= MV88E6XXX_G1_CTL1_SW_RESET;
	val |= MV88E6XXX_G1_CTL1_PPU_ENABLE;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, val);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_रुको_init_पढ़ोy(chip);
	अगर (err)
		वापस err;

	वापस mv88e6185_g1_रुको_ppu_polling(chip);
पूर्ण

पूर्णांक mv88e6250_g1_reset(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	/* Set the SWReset bit 15 */
	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &val);
	अगर (err)
		वापस err;

	val |= MV88E6XXX_G1_CTL1_SW_RESET;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, val);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_रुको_init_पढ़ोy(chip);
पूर्ण

पूर्णांक mv88e6352_g1_reset(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	err = mv88e6250_g1_reset(chip);
	अगर (err)
		वापस err;

	वापस mv88e6352_g1_रुको_ppu_polling(chip);
पूर्ण

पूर्णांक mv88e6185_g1_ppu_enable(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &val);
	अगर (err)
		वापस err;

	val |= MV88E6XXX_G1_CTL1_PPU_ENABLE;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, val);
	अगर (err)
		वापस err;

	वापस mv88e6185_g1_रुको_ppu_polling(chip);
पूर्ण

पूर्णांक mv88e6185_g1_ppu_disable(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &val);
	अगर (err)
		वापस err;

	val &= ~MV88E6XXX_G1_CTL1_PPU_ENABLE;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, val);
	अगर (err)
		वापस err;

	वापस mv88e6185_g1_रुको_ppu_disabled(chip);
पूर्ण

पूर्णांक mv88e6185_g1_set_max_frame_size(काष्ठा mv88e6xxx_chip *chip, पूर्णांक mtu)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &val);
	अगर (err)
		वापस err;

	val &= ~MV88E6185_G1_CTL1_MAX_FRAME_1632;

	अगर (mtu > 1518)
		val |= MV88E6185_G1_CTL1_MAX_FRAME_1632;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, val);
पूर्ण

/* Offset 0x10: IP-PRI Mapping Register 0
 * Offset 0x11: IP-PRI Mapping Register 1
 * Offset 0x12: IP-PRI Mapping Register 2
 * Offset 0x13: IP-PRI Mapping Register 3
 * Offset 0x14: IP-PRI Mapping Register 4
 * Offset 0x15: IP-PRI Mapping Register 5
 * Offset 0x16: IP-PRI Mapping Register 6
 * Offset 0x17: IP-PRI Mapping Register 7
 */

पूर्णांक mv88e6085_g1_ip_pri_map(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	/* Reset the IP TOS/DअगरfServ/Traffic priorities to शेषs */
	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_0, 0x0000);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_1, 0x0000);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_2, 0x5555);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_3, 0x5555);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_4, 0xaaaa);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_5, 0xaaaa);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_6, 0xffff);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IP_PRI_7, 0xffff);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* Offset 0x18: IEEE-PRI Register */

पूर्णांक mv88e6085_g1_ieee_pri_map(काष्ठा mv88e6xxx_chip *chip)
अणु
	/* Reset the IEEE Tag priorities to शेषs */
	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IEEE_PRI, 0xfa41);
पूर्ण

पूर्णांक mv88e6250_g1_ieee_pri_map(काष्ठा mv88e6xxx_chip *chip)
अणु
	/* Reset the IEEE Tag priorities to शेषs */
	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_IEEE_PRI, 0xfa50);
पूर्ण

/* Offset 0x1a: Monitor Control */
/* Offset 0x1a: Monitor & MGMT Control on some devices */

पूर्णांक mv88e6095_g1_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
				 क्रमागत mv88e6xxx_egress_direction direction,
				 पूर्णांक port)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6185_G1_MONITOR_CTL, &reg);
	अगर (err)
		वापस err;

	चयन (direction) अणु
	हाल MV88E6XXX_EGRESS_सूची_INGRESS:
		reg &= ~MV88E6185_G1_MONITOR_CTL_INGRESS_DEST_MASK;
		reg |= port <<
		       __bf_shf(MV88E6185_G1_MONITOR_CTL_INGRESS_DEST_MASK);
		अवरोध;
	हाल MV88E6XXX_EGRESS_सूची_EGRESS:
		reg &= ~MV88E6185_G1_MONITOR_CTL_EGRESS_DEST_MASK;
		reg |= port <<
		       __bf_shf(MV88E6185_G1_MONITOR_CTL_EGRESS_DEST_MASK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6185_G1_MONITOR_CTL, reg);
पूर्ण

/* Older generations also call this the ARP destination. It has been
 * generalized in more modern devices such that more than ARP can
 * egress it
 */
पूर्णांक mv88e6095_g1_set_cpu_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6185_G1_MONITOR_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6185_G1_MONITOR_CTL_ARP_DEST_MASK;
	reg |= port << __bf_shf(MV88E6185_G1_MONITOR_CTL_ARP_DEST_MASK);

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6185_G1_MONITOR_CTL, reg);
पूर्ण

अटल पूर्णांक mv88e6390_g1_monitor_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      u16 poपूर्णांकer, u8 data)
अणु
	u16 reg;

	reg = MV88E6390_G1_MONITOR_MGMT_CTL_UPDATE | poपूर्णांकer | data;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6390_G1_MONITOR_MGMT_CTL, reg);
पूर्ण

पूर्णांक mv88e6390_g1_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
				 क्रमागत mv88e6xxx_egress_direction direction,
				 पूर्णांक port)
अणु
	u16 ptr;

	चयन (direction) अणु
	हाल MV88E6XXX_EGRESS_सूची_INGRESS:
		ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_INGRESS_DEST;
		अवरोध;
	हाल MV88E6XXX_EGRESS_सूची_EGRESS:
		ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_EGRESS_DEST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mv88e6390_g1_monitor_ग_लिखो(chip, ptr, port);
पूर्ण

पूर्णांक mv88e6390_g1_set_cpu_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_CPU_DEST;

	/* Use the शेष high priority क्रम management frames sent to
	 * the CPU.
	 */
	port |= MV88E6390_G1_MONITOR_MGMT_CTL_PTR_CPU_DEST_MGMTPRI;

	वापस mv88e6390_g1_monitor_ग_लिखो(chip, ptr, port);
पूर्ण

पूर्णांक mv88e6390_g1_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 ptr;
	पूर्णांक err;

	/* 01:80:c2:00:00:00-01:80:c2:00:00:07 are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XLO;
	err = mv88e6390_g1_monitor_ग_लिखो(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	/* 01:80:c2:00:00:08-01:80:c2:00:00:0f are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XHI;
	err = mv88e6390_g1_monitor_ग_लिखो(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	/* 01:80:c2:00:00:20-01:80:c2:00:00:27 are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XLO;
	err = mv88e6390_g1_monitor_ग_लिखो(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	/* 01:80:c2:00:00:28-01:80:c2:00:00:2f are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XHI;
	err = mv88e6390_g1_monitor_ग_लिखो(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* Offset 0x1c: Global Control 2 */

अटल पूर्णांक mv88e6xxx_g1_ctl2_mask(काष्ठा mv88e6xxx_chip *chip, u16 mask,
				  u16 val)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL2, &reg);
	अगर (err)
		वापस err;

	reg &= ~mask;
	reg |= val & mask;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL2, reg);
पूर्ण

पूर्णांक mv88e6185_g1_set_cascade_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	स्थिर u16 mask = MV88E6185_G1_CTL2_CASCADE_PORT_MASK;

	वापस mv88e6xxx_g1_ctl2_mask(chip, mask, port << __bf_shf(mask));
पूर्ण

पूर्णांक mv88e6085_g1_rmu_disable(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g1_ctl2_mask(chip, MV88E6085_G1_CTL2_P10RM |
				      MV88E6085_G1_CTL2_RM_ENABLE, 0);
पूर्ण

पूर्णांक mv88e6352_g1_rmu_disable(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g1_ctl2_mask(chip, MV88E6352_G1_CTL2_RMU_MODE_MASK,
				      MV88E6352_G1_CTL2_RMU_MODE_DISABLED);
पूर्ण

पूर्णांक mv88e6390_g1_rmu_disable(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g1_ctl2_mask(chip, MV88E6390_G1_CTL2_RMU_MODE_MASK,
				      MV88E6390_G1_CTL2_RMU_MODE_DISABLED);
पूर्ण

पूर्णांक mv88e6390_g1_stats_set_histogram(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_g1_ctl2_mask(chip, MV88E6390_G1_CTL2_HIST_MODE_MASK,
				      MV88E6390_G1_CTL2_HIST_MODE_RX |
				      MV88E6390_G1_CTL2_HIST_MODE_TX);
पूर्ण

पूर्णांक mv88e6xxx_g1_set_device_number(काष्ठा mv88e6xxx_chip *chip, पूर्णांक index)
अणु
	वापस mv88e6xxx_g1_ctl2_mask(chip,
				      MV88E6XXX_G1_CTL2_DEVICE_NUMBER_MASK,
				      index);
पूर्ण

/* Offset 0x1d: Statistics Operation 2 */

अटल पूर्णांक mv88e6xxx_g1_stats_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G1_STATS_OP_BUSY);

	वापस mv88e6xxx_g1_रुको_bit(chip, MV88E6XXX_G1_STATS_OP, bit, 0);
पूर्ण

पूर्णांक mv88e6095_g1_stats_set_histogram(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STATS_OP, &val);
	अगर (err)
		वापस err;

	val |= MV88E6XXX_G1_STATS_OP_HIST_RX_TX;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_STATS_OP, val);

	वापस err;
पूर्ण

पूर्णांक mv88e6xxx_g1_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	पूर्णांक err;

	/* Snapshot the hardware statistics counters क्रम this port. */
	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_CAPTURE_PORT |
				 MV88E6XXX_G1_STATS_OP_HIST_RX_TX | port);
	अगर (err)
		वापस err;

	/* Wait क्रम the snapshotting to complete. */
	वापस mv88e6xxx_g1_stats_रुको(chip);
पूर्ण

पूर्णांक mv88e6320_g1_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	port = (port + 1) << 5;

	वापस mv88e6xxx_g1_stats_snapshot(chip, port);
पूर्ण

पूर्णांक mv88e6390_g1_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	पूर्णांक err;

	port = (port + 1) << 5;

	/* Snapshot the hardware statistics counters क्रम this port. */
	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_CAPTURE_PORT | port);
	अगर (err)
		वापस err;

	/* Wait क्रम the snapshotting to complete. */
	वापस mv88e6xxx_g1_stats_रुको(chip);
पूर्ण

व्योम mv88e6xxx_g1_stats_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक stat, u32 *val)
अणु
	u32 value;
	u16 reg;
	पूर्णांक err;

	*val = 0;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_READ_CAPTURED | stat);
	अगर (err)
		वापस;

	err = mv88e6xxx_g1_stats_रुको(chip);
	अगर (err)
		वापस;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STATS_COUNTER_32, &reg);
	अगर (err)
		वापस;

	value = reg << 16;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STATS_COUNTER_01, &reg);
	अगर (err)
		वापस;

	*val = value | reg;
पूर्ण

पूर्णांक mv88e6xxx_g1_stats_clear(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;
	u16 val;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STATS_OP, &val);
	अगर (err)
		वापस err;

	/* Keep the histogram mode bits */
	val &= MV88E6XXX_G1_STATS_OP_HIST_RX_TX;
	val |= MV88E6XXX_G1_STATS_OP_BUSY | MV88E6XXX_G1_STATS_OP_FLUSH_ALL;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_STATS_OP, val);
	अगर (err)
		वापस err;

	/* Wait क्रम the flush to complete. */
	वापस mv88e6xxx_g1_stats_रुको(chip);
पूर्ण
