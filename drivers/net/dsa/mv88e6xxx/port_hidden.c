<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch Hidden Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2019 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/bitfield.h>

#समावेश "chip.h"
#समावेश "port.h"

/* The mv88e6390 and mv88e6341 have some hidden रेजिस्टरs used क्रम debug and
 * development. The errata also makes use of them.
 */
पूर्णांक mv88e6xxx_port_hidden_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक block,
				पूर्णांक port, पूर्णांक reg, u16 val)
अणु
	u16 ctrl;
	पूर्णांक err;

	err = mv88e6xxx_port_ग_लिखो(chip, MV88E6XXX_PORT_RESERVED_1A_DATA_PORT,
				   MV88E6XXX_PORT_RESERVED_1A, val);
	अगर (err)
		वापस err;

	ctrl = MV88E6XXX_PORT_RESERVED_1A_BUSY |
	       MV88E6XXX_PORT_RESERVED_1A_WRITE |
	       block << MV88E6XXX_PORT_RESERVED_1A_BLOCK_SHIFT |
	       port << MV88E6XXX_PORT_RESERVED_1A_PORT_SHIFT |
	       reg;

	वापस mv88e6xxx_port_ग_लिखो(chip, MV88E6XXX_PORT_RESERVED_1A_CTRL_PORT,
				    MV88E6XXX_PORT_RESERVED_1A, ctrl);
पूर्ण

पूर्णांक mv88e6xxx_port_hidden_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_PORT_RESERVED_1A_BUSY);

	वापस mv88e6xxx_रुको_bit(chip, MV88E6XXX_PORT_RESERVED_1A_CTRL_PORT,
				  MV88E6XXX_PORT_RESERVED_1A, bit, 0);
पूर्ण

पूर्णांक mv88e6xxx_port_hidden_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक block, पूर्णांक port,
			       पूर्णांक reg, u16 *val)
अणु
	u16 ctrl;
	पूर्णांक err;

	ctrl = MV88E6XXX_PORT_RESERVED_1A_BUSY |
	       MV88E6XXX_PORT_RESERVED_1A_READ |
	       block << MV88E6XXX_PORT_RESERVED_1A_BLOCK_SHIFT |
	       port << MV88E6XXX_PORT_RESERVED_1A_PORT_SHIFT |
	       reg;

	err = mv88e6xxx_port_ग_लिखो(chip, MV88E6XXX_PORT_RESERVED_1A_CTRL_PORT,
				   MV88E6XXX_PORT_RESERVED_1A, ctrl);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_hidden_रुको(chip);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_port_पढ़ो(chip, MV88E6XXX_PORT_RESERVED_1A_DATA_PORT,
				   MV88E6XXX_PORT_RESERVED_1A, val);
पूर्ण
