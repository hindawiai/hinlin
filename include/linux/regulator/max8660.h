<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * max8660.h  --  Voltage regulation क्रम the Maxim 8660/8661
 *
 * Copyright (C) 2009 Wolfram Sang, Pengutronix e.K.
 */

#अगर_अघोषित __LINUX_REGULATOR_MAX8660_H
#घोषणा __LINUX_REGULATOR_MAX8660_H

#समावेश <linux/regulator/machine.h>

क्रमागत अणु
	MAX8660_V3,
	MAX8660_V4,
	MAX8660_V5,
	MAX8660_V6,
	MAX8660_V7,
	MAX8660_V_END,
पूर्ण;

/**
 * max8660_subdev_data - regulator subdev data
 * @id: regulator id
 * @name: regulator name
 * @platक्रमm_data: regulator init data
 */
काष्ठा max8660_subdev_data अणु
	पूर्णांक				id;
	स्थिर अक्षर			*name;
	काष्ठा regulator_init_data	*platक्रमm_data;
पूर्ण;

/**
 * max8660_platक्रमm_data - platक्रमm data क्रम max8660
 * @num_subdevs: number of regulators used
 * @subdevs: poपूर्णांकer to regulators used
 * @en34_is_high: अगर EN34 is driven high, regulators cannot be en-/disabled.
 */
काष्ठा max8660_platक्रमm_data अणु
	पूर्णांक num_subdevs;
	काष्ठा max8660_subdev_data *subdevs;
	अचिन्हित en34_is_high:1;
पूर्ण;
#पूर्ण_अगर
