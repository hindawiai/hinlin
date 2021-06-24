<शैली गुरु>
/*  SPDX-License-Identअगरier: GPL-2.0 */
/* mt9t112 Camera
 *
 * Copyright (C) 2009 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 */

#अगर_अघोषित __MT9T112_H__
#घोषणा __MT9T112_H__

काष्ठा mt9t112_pll_भागider अणु
	u8 m, n;
	u8 p1, p2, p3, p4, p5, p6, p7;
पूर्ण;

/**
 * काष्ठा mt9t112_platक्रमm_data - mt9t112 driver पूर्णांकerface
 * @flags:			Sensor media bus configuration.
 * @भागider:			Sensor PLL configuration
 */
काष्ठा mt9t112_platक्रमm_data अणु
#घोषणा MT9T112_FLAG_PCLK_RISING_EDGE	BIT(0)
	u32 flags;
	काष्ठा mt9t112_pll_भागider भागider;
पूर्ण;

#पूर्ण_अगर /* __MT9T112_H__ */
