<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx System Management Interface (SMI) support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2019 Vivien Didelot <vivien.didelot@gmail.com>
 */

#अगर_अघोषित _MV88E6XXX_SMI_H
#घोषणा _MV88E6XXX_SMI_H

#समावेश "chip.h"

/* Offset 0x00: SMI Command Register */
#घोषणा MV88E6XXX_SMI_CMD			0x00
#घोषणा MV88E6XXX_SMI_CMD_BUSY			0x8000
#घोषणा MV88E6XXX_SMI_CMD_MODE_MASK		0x1000
#घोषणा MV88E6XXX_SMI_CMD_MODE_45		0x0000
#घोषणा MV88E6XXX_SMI_CMD_MODE_22		0x1000
#घोषणा MV88E6XXX_SMI_CMD_OP_MASK		0x0c00
#घोषणा MV88E6XXX_SMI_CMD_OP_22_WRITE		0x0400
#घोषणा MV88E6XXX_SMI_CMD_OP_22_READ		0x0800
#घोषणा MV88E6XXX_SMI_CMD_OP_45_WRITE_ADDR	0x0000
#घोषणा MV88E6XXX_SMI_CMD_OP_45_WRITE_DATA	0x0400
#घोषणा MV88E6XXX_SMI_CMD_OP_45_READ_DATA	0x0800
#घोषणा MV88E6XXX_SMI_CMD_OP_45_READ_DATA_INC	0x0c00
#घोषणा MV88E6XXX_SMI_CMD_DEV_ADDR_MASK		0x003e
#घोषणा MV88E6XXX_SMI_CMD_REG_ADDR_MASK		0x001f

/* Offset 0x01: SMI Data Register */
#घोषणा MV88E6XXX_SMI_DATA			0x01

पूर्णांक mv88e6xxx_smi_init(काष्ठा mv88e6xxx_chip *chip,
		       काष्ठा mii_bus *bus, पूर्णांक sw_addr);

अटल अंतरभूत पूर्णांक mv88e6xxx_smi_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				     पूर्णांक dev, पूर्णांक reg, u16 *data)
अणु
	अगर (chip->smi_ops && chip->smi_ops->पढ़ो)
		वापस chip->smi_ops->पढ़ो(chip, dev, reg, data);

	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_smi_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      पूर्णांक dev, पूर्णांक reg, u16 data)
अणु
	अगर (chip->smi_ops && chip->smi_ops->ग_लिखो)
		वापस chip->smi_ops->ग_लिखो(chip, dev, reg, data);

	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर /* _MV88E6XXX_SMI_H */
