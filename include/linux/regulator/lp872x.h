<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#अगर_अघोषित __LP872X_REGULATOR_H__
#घोषणा __LP872X_REGULATOR_H__

#समावेश <linux/regulator/machine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#घोषणा LP872X_MAX_REGULATORS		9

#घोषणा LP8720_ENABLE_DELAY		200
#घोषणा LP8725_ENABLE_DELAY		30000

क्रमागत lp872x_regulator_id अणु
	LP8720_ID_BASE,
	LP8720_ID_LDO1 = LP8720_ID_BASE,
	LP8720_ID_LDO2,
	LP8720_ID_LDO3,
	LP8720_ID_LDO4,
	LP8720_ID_LDO5,
	LP8720_ID_BUCK,

	LP8725_ID_BASE,
	LP8725_ID_LDO1 = LP8725_ID_BASE,
	LP8725_ID_LDO2,
	LP8725_ID_LDO3,
	LP8725_ID_LDO4,
	LP8725_ID_LDO5,
	LP8725_ID_LILO1,
	LP8725_ID_LILO2,
	LP8725_ID_BUCK1,
	LP8725_ID_BUCK2,

	LP872X_ID_MAX,
पूर्ण;

क्रमागत lp872x_dvs_state अणु
	DVS_LOW  = GPIOF_OUT_INIT_LOW,
	DVS_HIGH = GPIOF_OUT_INIT_HIGH,
पूर्ण;

क्रमागत lp872x_dvs_sel अणु
	SEL_V1,
	SEL_V2,
पूर्ण;

/**
 * lp872x_dvs
 * @gpio       : gpio pin number क्रम dvs control
 * @vsel       : dvs selector क्रम buck v1 or buck v2 रेजिस्टर
 * @init_state : initial dvs pin state
 */
काष्ठा lp872x_dvs अणु
	पूर्णांक gpio;
	क्रमागत lp872x_dvs_sel vsel;
	क्रमागत lp872x_dvs_state init_state;
पूर्ण;

/**
 * lp872x_regdata
 * @id        : regulator id
 * @init_data : init data क्रम each regulator
 */
काष्ठा lp872x_regulator_data अणु
	क्रमागत lp872x_regulator_id id;
	काष्ठा regulator_init_data *init_data;
पूर्ण;

/**
 * lp872x_platक्रमm_data
 * @general_config    : the value of LP872X_GENERAL_CFG रेजिस्टर
 * @update_config     : अगर LP872X_GENERAL_CFG रेजिस्टर is updated, set true
 * @regulator_data    : platक्रमm regulator id and init data
 * @dvs               : dvs data क्रम buck voltage control
 * @enable_gpio       : gpio pin number क्रम enable control
 */
काष्ठा lp872x_platक्रमm_data अणु
	u8 general_config;
	bool update_config;
	काष्ठा lp872x_regulator_data regulator_data[LP872X_MAX_REGULATORS];
	काष्ठा lp872x_dvs *dvs;
	पूर्णांक enable_gpio;
पूर्ण;

#पूर्ण_अगर
