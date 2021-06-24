<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#अगर_अघोषित __TIDSS_DISPC_COEF_H__
#घोषणा __TIDSS_DISPC_COEF_H__

#समावेश <linux/types.h>

काष्ठा tidss_scale_coefs अणु
	s16 c2[16];
	s16 c1[16];
	u16 c0[9];
पूर्ण;

स्थिर काष्ठा tidss_scale_coefs *tidss_get_scale_coefs(काष्ठा device *dev,
						      u32 firinc,
						      bool five_taps);

#पूर्ण_अगर
