<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SuperH Video Output Unit (VOU) driver header
 *
 * Copyright (C) 2010, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#अगर_अघोषित SH_VOU_H
#घोषणा SH_VOU_H

#समावेश <linux/i2c.h>

/* Bus flags */
#घोषणा SH_VOU_PCLK_FALLING	(1 << 0)
#घोषणा SH_VOU_HSYNC_LOW	(1 << 1)
#घोषणा SH_VOU_VSYNC_LOW	(1 << 2)

क्रमागत sh_vou_bus_fmt अणु
	SH_VOU_BUS_8BIT,
	SH_VOU_BUS_16BIT,
	SH_VOU_BUS_BT656,
पूर्ण;

काष्ठा sh_vou_pdata अणु
	क्रमागत sh_vou_bus_fmt bus_fmt;
	पूर्णांक i2c_adap;
	काष्ठा i2c_board_info *board_info;
	अचिन्हित दीर्घ flags;
पूर्ण;

#पूर्ण_अगर
