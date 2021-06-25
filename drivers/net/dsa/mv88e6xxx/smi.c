<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx System Management Interface (SMI) support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2019 Vivien Didelot <vivien.didelot@gmail.com>
 */

#समावेश "chip.h"
#समावेश "smi.h"

/* The चयन ADDR[4:1] configuration pins define the chip SMI device address
 * (ADDR[0] is always zero, thus only even SMI addresses can be strapped).
 *
 * When ADDR is all zero, the chip uses Single-chip Addressing Mode, assuming it
 * is the only device connected to the SMI master. In this mode it responds to
 * all 32 possible SMI addresses, and thus maps directly the पूर्णांकernal devices.
 *
 * When ADDR is non-zero, the chip uses Multi-chip Addressing Mode, allowing
 * multiple devices to share the SMI पूर्णांकerface. In this mode it responds to only
 * 2 रेजिस्टरs, used to indirectly access the पूर्णांकernal SMI devices.
 *
 * Some chips use a dअगरferent scheme: Only the ADDR4 pin is used क्रम
 * configuration, and the device responds to 16 of the 32 SMI
 * addresses, allowing two to coexist on the same SMI पूर्णांकerface.
 */

अटल पूर्णांक mv88e6xxx_smi_direct_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				     पूर्णांक dev, पूर्णांक reg, u16 *data)
अणु
	पूर्णांक ret;

	ret = mdiobus_पढ़ो_nested(chip->bus, dev, reg);
	अगर (ret < 0)
		वापस ret;

	*data = ret & 0xffff;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_smi_direct_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      पूर्णांक dev, पूर्णांक reg, u16 data)
अणु
	पूर्णांक ret;

	ret = mdiobus_ग_लिखो_nested(chip->bus, dev, reg, data);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_smi_direct_रुको(काष्ठा mv88e6xxx_chip *chip,
				     पूर्णांक dev, पूर्णांक reg, पूर्णांक bit, पूर्णांक val)
अणु
	u16 data;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		err = mv88e6xxx_smi_direct_पढ़ो(chip, dev, reg, &data);
		अगर (err)
			वापस err;

		अगर (!!(data & BIT(bit)) == !!val)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल स्थिर काष्ठा mv88e6xxx_bus_ops mv88e6xxx_smi_direct_ops = अणु
	.पढ़ो = mv88e6xxx_smi_direct_पढ़ो,
	.ग_लिखो = mv88e6xxx_smi_direct_ग_लिखो,
पूर्ण;

अटल पूर्णांक mv88e6xxx_smi_dual_direct_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
					  पूर्णांक dev, पूर्णांक reg, u16 *data)
अणु
	वापस mv88e6xxx_smi_direct_पढ़ो(chip, chip->sw_addr + dev, reg, data);
पूर्ण

अटल पूर्णांक mv88e6xxx_smi_dual_direct_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक dev, पूर्णांक reg, u16 data)
अणु
	वापस mv88e6xxx_smi_direct_ग_लिखो(chip, chip->sw_addr + dev, reg, data);
पूर्ण

अटल स्थिर काष्ठा mv88e6xxx_bus_ops mv88e6xxx_smi_dual_direct_ops = अणु
	.पढ़ो = mv88e6xxx_smi_dual_direct_पढ़ो,
	.ग_लिखो = mv88e6xxx_smi_dual_direct_ग_लिखो,
पूर्ण;

/* Offset 0x00: SMI Command Register
 * Offset 0x01: SMI Data Register
 */

अटल पूर्णांक mv88e6xxx_smi_indirect_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				       पूर्णांक dev, पूर्णांक reg, u16 *data)
अणु
	पूर्णांक err;

	err = mv88e6xxx_smi_direct_रुको(chip, chip->sw_addr,
					MV88E6XXX_SMI_CMD, 15, 0);
	अगर (err)
		वापस err;

	err = mv88e6xxx_smi_direct_ग_लिखो(chip, chip->sw_addr,
					 MV88E6XXX_SMI_CMD,
					 MV88E6XXX_SMI_CMD_BUSY |
					 MV88E6XXX_SMI_CMD_MODE_22 |
					 MV88E6XXX_SMI_CMD_OP_22_READ |
					 (dev << 5) | reg);
	अगर (err)
		वापस err;

	err = mv88e6xxx_smi_direct_रुको(chip, chip->sw_addr,
					MV88E6XXX_SMI_CMD, 15, 0);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_smi_direct_पढ़ो(chip, chip->sw_addr,
					 MV88E6XXX_SMI_DATA, data);
पूर्ण

अटल पूर्णांक mv88e6xxx_smi_indirect_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
					पूर्णांक dev, पूर्णांक reg, u16 data)
अणु
	पूर्णांक err;

	err = mv88e6xxx_smi_direct_रुको(chip, chip->sw_addr,
					MV88E6XXX_SMI_CMD, 15, 0);
	अगर (err)
		वापस err;

	err = mv88e6xxx_smi_direct_ग_लिखो(chip, chip->sw_addr,
					 MV88E6XXX_SMI_DATA, data);
	अगर (err)
		वापस err;

	err = mv88e6xxx_smi_direct_ग_लिखो(chip, chip->sw_addr,
					 MV88E6XXX_SMI_CMD,
					 MV88E6XXX_SMI_CMD_BUSY |
					 MV88E6XXX_SMI_CMD_MODE_22 |
					 MV88E6XXX_SMI_CMD_OP_22_WRITE |
					 (dev << 5) | reg);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_smi_direct_रुको(chip, chip->sw_addr,
					 MV88E6XXX_SMI_CMD, 15, 0);
पूर्ण

अटल स्थिर काष्ठा mv88e6xxx_bus_ops mv88e6xxx_smi_indirect_ops = अणु
	.पढ़ो = mv88e6xxx_smi_indirect_पढ़ो,
	.ग_लिखो = mv88e6xxx_smi_indirect_ग_लिखो,
पूर्ण;

पूर्णांक mv88e6xxx_smi_init(काष्ठा mv88e6xxx_chip *chip,
		       काष्ठा mii_bus *bus, पूर्णांक sw_addr)
अणु
	अगर (chip->info->dual_chip)
		chip->smi_ops = &mv88e6xxx_smi_dual_direct_ops;
	अन्यथा अगर (sw_addr == 0)
		chip->smi_ops = &mv88e6xxx_smi_direct_ops;
	अन्यथा अगर (chip->info->multi_chip)
		chip->smi_ops = &mv88e6xxx_smi_indirect_ops;
	अन्यथा
		वापस -EINVAL;

	chip->bus = bus;
	chip->sw_addr = sw_addr;

	वापस 0;
पूर्ण
