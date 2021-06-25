<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * isl9305 - Intersil ISL9305 DCDC regulator
 *
 * Copyright 2014 Linaro Ltd
 *
 * Author: Mark Brown <broonie@kernel.org>
 */

#अगर_अघोषित __ISL9305_H
#घोषणा __ISL9305_H

#घोषणा ISL9305_DCD1 0
#घोषणा ISL9305_DCD2 1
#घोषणा ISL9305_LDO1 2
#घोषणा ISL9305_LDO2 3

#घोषणा ISL9305_MAX_REGULATOR ISL9305_LDO2

काष्ठा regulator_init_data;

काष्ठा isl9305_pdata अणु
	काष्ठा regulator_init_data *init_data[ISL9305_MAX_REGULATOR + 1];
पूर्ण;

#पूर्ण_अगर
