<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित MFD_STW481X_H
#घोषणा MFD_STW481X_H

#समावेश <linux/i2c.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>

/* These रेजिस्टरs are accessed from more than one driver */
#घोषणा STW_CONF1			0x11U
#घोषणा STW_CONF1_PDN_VMMC		0x01U
#घोषणा STW_CONF1_VMMC_MASK		0x0eU
#घोषणा STW_CONF1_VMMC_1_8V		0x02U
#घोषणा STW_CONF1_VMMC_2_85V		0x04U
#घोषणा STW_CONF1_VMMC_3V		0x06U
#घोषणा STW_CONF1_VMMC_1_85V		0x08U
#घोषणा STW_CONF1_VMMC_2_6V		0x0aU
#घोषणा STW_CONF1_VMMC_2_7V		0x0cU
#घोषणा STW_CONF1_VMMC_3_3V		0x0eU
#घोषणा STW_CONF1_MMC_LS_STATUS		0x10U
#घोषणा STW_PCTL_REG_LO			0x1eU
#घोषणा STW_PCTL_REG_HI			0x1fU
#घोषणा STW_CONF1_V_MONITORING		0x20U
#घोषणा STW_CONF1_IT_WARN		0x40U
#घोषणा STW_CONF1_PDN_VAUX		0x80U
#घोषणा STW_CONF2			0x20U
#घोषणा STW_CONF2_MASK_TWARN		0x01U
#घोषणा STW_CONF2_VMMC_EXT		0x02U
#घोषणा STW_CONF2_MASK_IT_WAKE_UP	0x04U
#घोषणा STW_CONF2_GPO1			0x08U
#घोषणा STW_CONF2_GPO2			0x10U
#घोषणा STW_VCORE_SLEEP			0x21U

/**
 * काष्ठा stw481x - state holder क्रम the Stw481x drivers
 * @i2c_client: corresponding I2C client
 * @map: regmap handle to access device रेजिस्टरs
 */
काष्ठा stw481x अणु
	काष्ठा i2c_client	*client;
	काष्ठा regmap		*map;
पूर्ण;

#पूर्ण_अगर
