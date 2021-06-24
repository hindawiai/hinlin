<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface of Maxim max8649
 *
 * Copyright (C) 2009-2010 Marvell International Ltd.
 *      Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#अगर_अघोषित __LINUX_REGULATOR_MAX8649_H
#घोषणा	__LINUX_REGULATOR_MAX8649_H

#समावेश <linux/regulator/machine.h>

क्रमागत अणु
	MAX8649_EXTCLK_26MHZ = 0,
	MAX8649_EXTCLK_13MHZ,
	MAX8649_EXTCLK_19MHZ,	/* 19.2MHz */
पूर्ण;

क्रमागत अणु
	MAX8649_RAMP_32MV = 0,
	MAX8649_RAMP_16MV,
	MAX8649_RAMP_8MV,
	MAX8649_RAMP_4MV,
	MAX8649_RAMP_2MV,
	MAX8649_RAMP_1MV,
	MAX8649_RAMP_0_5MV,
	MAX8649_RAMP_0_25MV,
पूर्ण;

काष्ठा max8649_platक्रमm_data अणु
	काष्ठा regulator_init_data *regulator;

	अचिन्हित	mode:2;		/* bit[1:0] = VID1,VID0 */
	अचिन्हित	extclk_freq:2;
	अचिन्हित	extclk:1;
	अचिन्हित	ramp_timing:3;
	अचिन्हित	ramp_करोwn:1;
पूर्ण;

#पूर्ण_अगर	/* __LINUX_REGULATOR_MAX8649_H */
