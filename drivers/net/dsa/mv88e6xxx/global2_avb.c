<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch Global 2 Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * Copyright (c) 2017 National Instruments
 *	Bअक्रमon Streअगरf <bअक्रमon.streअगरf@ni.com>
 */

#समावेश <linux/bitfield.h>

#समावेश "global2.h"

/* Offset 0x16: AVB Command Register
 * Offset 0x17: AVB Data Register
 *
 * There are two dअगरferent versions of this रेजिस्टर पूर्णांकerface:
 *    "6352": 3-bit "op" field, 4-bit "port" field.
 *    "6390": 2-bit "op" field, 5-bit "port" field.
 *
 * The "op" codes are dअगरferent between the two, as well as the special
 * port fields क्रम global PTP and TAI configuration.
 */

/* mv88e6xxx_g2_avb_पढ़ो -- Read one or multiple 16-bit words.
 * The hardware supports snapshotting up to four contiguous रेजिस्टरs.
 */
अटल पूर्णांक mv88e6xxx_g2_avb_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6352_G2_AVB_CMD_BUSY);

	वापस mv88e6xxx_g2_रुको_bit(chip, MV88E6352_G2_AVB_CMD, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_avb_पढ़ो(काष्ठा mv88e6xxx_chip *chip, u16 पढ़ोop,
				 u16 *data, पूर्णांक len)
अणु
	पूर्णांक err;
	पूर्णांक i;

	err = mv88e6xxx_g2_avb_रुको(chip);
	अगर (err)
		वापस err;

	/* Hardware can only snapshot four words. */
	अगर (len > 4)
		वापस -E2BIG;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6352_G2_AVB_CMD,
				 MV88E6352_G2_AVB_CMD_BUSY | पढ़ोop);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_avb_रुको(chip);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < len; ++i) अणु
		err = mv88e6xxx_g2_पढ़ो(chip, MV88E6352_G2_AVB_DATA,
					&data[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* mv88e6xxx_g2_avb_ग_लिखो -- Write one 16-bit word. */
अटल पूर्णांक mv88e6xxx_g2_avb_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, u16 ग_लिखोop,
				  u16 data)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g2_avb_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6352_G2_AVB_DATA, data);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6352_G2_AVB_CMD,
				 MV88E6352_G2_AVB_CMD_BUSY | ग_लिखोop);

	वापस mv88e6xxx_g2_avb_रुको(chip);
पूर्ण

अटल पूर्णांक mv88e6352_g2_avb_port_ptp_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
					  पूर्णांक port, पूर्णांक addr, u16 *data,
					  पूर्णांक len)
अणु
	u16 पढ़ोop = (len == 1 ? MV88E6352_G2_AVB_CMD_OP_READ :
				 MV88E6352_G2_AVB_CMD_OP_READ_INCR) |
		     (port << 8) | (MV88E6352_G2_AVB_CMD_BLOCK_PTP << 5) |
		     addr;

	वापस mv88e6xxx_g2_avb_पढ़ो(chip, पढ़ोop, data, len);
पूर्ण

अटल पूर्णांक mv88e6352_g2_avb_port_ptp_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक port, पूर्णांक addr, u16 data)
अणु
	u16 ग_लिखोop = MV88E6352_G2_AVB_CMD_OP_WRITE | (port << 8) |
		      (MV88E6352_G2_AVB_CMD_BLOCK_PTP << 5) | addr;

	वापस mv88e6xxx_g2_avb_ग_लिखो(chip, ग_लिखोop, data);
पूर्ण

अटल पूर्णांक mv88e6352_g2_avb_ptp_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				     u16 *data, पूर्णांक len)
अणु
	वापस mv88e6352_g2_avb_port_ptp_पढ़ो(chip,
					MV88E6352_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data, len);
पूर्ण

अटल पूर्णांक mv88e6352_g2_avb_ptp_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				      u16 data)
अणु
	वापस mv88e6352_g2_avb_port_ptp_ग_लिखो(chip,
					MV88E6352_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data);
पूर्ण

अटल पूर्णांक mv88e6352_g2_avb_tai_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				     u16 *data, पूर्णांक len)
अणु
	वापस mv88e6352_g2_avb_port_ptp_पढ़ो(chip,
					MV88E6352_G2_AVB_CMD_PORT_TAIGLOBAL,
					addr, data, len);
पूर्ण

अटल पूर्णांक mv88e6352_g2_avb_tai_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				      u16 data)
अणु
	वापस mv88e6352_g2_avb_port_ptp_ग_लिखो(chip,
					MV88E6352_G2_AVB_CMD_PORT_TAIGLOBAL,
					addr, data);
पूर्ण

स्थिर काष्ठा mv88e6xxx_avb_ops mv88e6352_avb_ops = अणु
	.port_ptp_पढ़ो		= mv88e6352_g2_avb_port_ptp_पढ़ो,
	.port_ptp_ग_लिखो		= mv88e6352_g2_avb_port_ptp_ग_लिखो,
	.ptp_पढ़ो		= mv88e6352_g2_avb_ptp_पढ़ो,
	.ptp_ग_लिखो		= mv88e6352_g2_avb_ptp_ग_लिखो,
	.tai_पढ़ो		= mv88e6352_g2_avb_tai_पढ़ो,
	.tai_ग_लिखो		= mv88e6352_g2_avb_tai_ग_लिखो,
पूर्ण;

अटल पूर्णांक mv88e6165_g2_avb_tai_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				     u16 *data, पूर्णांक len)
अणु
	वापस mv88e6352_g2_avb_port_ptp_पढ़ो(chip,
					MV88E6165_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data, len);
पूर्ण

अटल पूर्णांक mv88e6165_g2_avb_tai_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				      u16 data)
अणु
	वापस mv88e6352_g2_avb_port_ptp_ग_लिखो(chip,
					MV88E6165_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data);
पूर्ण

स्थिर काष्ठा mv88e6xxx_avb_ops mv88e6165_avb_ops = अणु
	.port_ptp_पढ़ो		= mv88e6352_g2_avb_port_ptp_पढ़ो,
	.port_ptp_ग_लिखो		= mv88e6352_g2_avb_port_ptp_ग_लिखो,
	.ptp_पढ़ो		= mv88e6352_g2_avb_ptp_पढ़ो,
	.ptp_ग_लिखो		= mv88e6352_g2_avb_ptp_ग_लिखो,
	.tai_पढ़ो		= mv88e6165_g2_avb_tai_पढ़ो,
	.tai_ग_लिखो		= mv88e6165_g2_avb_tai_ग_लिखो,
पूर्ण;

अटल पूर्णांक mv88e6390_g2_avb_port_ptp_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
					  पूर्णांक port, पूर्णांक addr, u16 *data,
					  पूर्णांक len)
अणु
	u16 पढ़ोop = (len == 1 ? MV88E6390_G2_AVB_CMD_OP_READ :
				 MV88E6390_G2_AVB_CMD_OP_READ_INCR) |
		     (port << 8) | (MV88E6352_G2_AVB_CMD_BLOCK_PTP << 5) |
		     addr;

	वापस mv88e6xxx_g2_avb_पढ़ो(chip, पढ़ोop, data, len);
पूर्ण

अटल पूर्णांक mv88e6390_g2_avb_port_ptp_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक port, पूर्णांक addr, u16 data)
अणु
	u16 ग_लिखोop = MV88E6390_G2_AVB_CMD_OP_WRITE | (port << 8) |
		      (MV88E6352_G2_AVB_CMD_BLOCK_PTP << 5) | addr;

	वापस mv88e6xxx_g2_avb_ग_लिखो(chip, ग_लिखोop, data);
पूर्ण

अटल पूर्णांक mv88e6390_g2_avb_ptp_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				     u16 *data, पूर्णांक len)
अणु
	वापस mv88e6390_g2_avb_port_ptp_पढ़ो(chip,
					MV88E6390_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data, len);
पूर्ण

अटल पूर्णांक mv88e6390_g2_avb_ptp_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				      u16 data)
अणु
	वापस mv88e6390_g2_avb_port_ptp_ग_लिखो(chip,
					MV88E6390_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data);
पूर्ण

अटल पूर्णांक mv88e6390_g2_avb_tai_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				     u16 *data, पूर्णांक len)
अणु
	वापस mv88e6390_g2_avb_port_ptp_पढ़ो(chip,
					MV88E6390_G2_AVB_CMD_PORT_TAIGLOBAL,
					addr, data, len);
पूर्ण

अटल पूर्णांक mv88e6390_g2_avb_tai_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
				      u16 data)
अणु
	वापस mv88e6390_g2_avb_port_ptp_ग_लिखो(chip,
					MV88E6390_G2_AVB_CMD_PORT_TAIGLOBAL,
					addr, data);
पूर्ण

स्थिर काष्ठा mv88e6xxx_avb_ops mv88e6390_avb_ops = अणु
	.port_ptp_पढ़ो		= mv88e6390_g2_avb_port_ptp_पढ़ो,
	.port_ptp_ग_लिखो		= mv88e6390_g2_avb_port_ptp_ग_लिखो,
	.ptp_पढ़ो		= mv88e6390_g2_avb_ptp_पढ़ो,
	.ptp_ग_लिखो		= mv88e6390_g2_avb_ptp_ग_लिखो,
	.tai_पढ़ो		= mv88e6390_g2_avb_tai_पढ़ो,
	.tai_ग_लिखो		= mv88e6390_g2_avb_tai_ग_लिखो,
पूर्ण;
