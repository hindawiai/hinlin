<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * act8865.h  --  Voltage regulation क्रम active-semi act88xx PMUs
 *
 * Copyright (C) 2013 Aपंचांगel Corporation.
 */

#अगर_अघोषित __LINUX_REGULATOR_ACT8865_H
#घोषणा __LINUX_REGULATOR_ACT8865_H

#समावेश <linux/regulator/machine.h>

क्रमागत अणु
	ACT8600_ID_DCDC1,
	ACT8600_ID_DCDC2,
	ACT8600_ID_DCDC3,
	ACT8600_ID_SUDCDC4,
	ACT8600_ID_LDO5,
	ACT8600_ID_LDO6,
	ACT8600_ID_LDO7,
	ACT8600_ID_LDO8,
	ACT8600_ID_LDO9,
	ACT8600_ID_LDO10,
पूर्ण;

क्रमागत अणु
	ACT8865_ID_DCDC1,
	ACT8865_ID_DCDC2,
	ACT8865_ID_DCDC3,
	ACT8865_ID_LDO1,
	ACT8865_ID_LDO2,
	ACT8865_ID_LDO3,
	ACT8865_ID_LDO4,
	ACT8865_REG_NUM,
पूर्ण;

क्रमागत अणु
	ACT8846_ID_REG1,
	ACT8846_ID_REG2,
	ACT8846_ID_REG3,
	ACT8846_ID_REG4,
	ACT8846_ID_REG5,
	ACT8846_ID_REG6,
	ACT8846_ID_REG7,
	ACT8846_ID_REG8,
	ACT8846_ID_REG9,
	ACT8846_ID_REG10,
	ACT8846_ID_REG11,
	ACT8846_ID_REG12,
	ACT8846_REG_NUM,
पूर्ण;

क्रमागत अणु
	ACT8600,
	ACT8865,
	ACT8846,
पूर्ण;

/**
 * act8865_regulator_data - regulator data
 * @id: regulator id
 * @name: regulator name
 * @init_data: regulator init data
 * @of_node: device tree node (optional)
 */
काष्ठा act8865_regulator_data अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	काष्ठा regulator_init_data *init_data;
	काष्ठा device_node *of_node;
पूर्ण;

/**
 * act8865_platक्रमm_data - platक्रमm data क्रम act8865
 * @num_regulators: number of regulators used
 * @regulators: poपूर्णांकer to regulators used
 */
काष्ठा act8865_platक्रमm_data अणु
	पूर्णांक num_regulators;
	काष्ठा act8865_regulator_data *regulators;
पूर्ण;
#पूर्ण_अगर
