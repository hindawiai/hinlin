<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Kionix, Inc.
 * Written by Chris Hudson <chudson@kionix.com>
 */

#अगर_अघोषित __KXTJ9_H__
#घोषणा __KXTJ9_H__

#घोषणा KXTJ9_I2C_ADDR		0x0F

काष्ठा kxtj9_platक्रमm_data अणु
	अचिन्हित पूर्णांक min_पूर्णांकerval;	/* minimum poll पूर्णांकerval (in milli-seconds) */
	अचिन्हित पूर्णांक init_पूर्णांकerval;	/* initial poll पूर्णांकerval (in milli-seconds) */

	/*
	 * By शेष, x is axis 0, y is axis 1, z is axis 2; these can be
	 * changed to account क्रम sensor orientation within the host device.
	 */
	u8 axis_map_x;
	u8 axis_map_y;
	u8 axis_map_z;

	/*
	 * Each axis can be negated to account क्रम sensor orientation within
	 * the host device.
	 */
	bool negate_x;
	bool negate_y;
	bool negate_z;

	/* CTRL_REG1: set resolution, g-range, data पढ़ोy enable */
	/* Output resolution: 8-bit valid or 12-bit valid */
	#घोषणा RES_8BIT		0
	#घोषणा RES_12BIT		(1 << 6)
	u8 res_12bit;
	/* Output g-range: +/-2g, 4g, or 8g */
	#घोषणा KXTJ9_G_2G		0
	#घोषणा KXTJ9_G_4G		(1 << 3)
	#घोषणा KXTJ9_G_8G		(1 << 4)
	u8 g_range;

	पूर्णांक (*init)(व्योम);
	व्योम (*निकास)(व्योम);
	पूर्णांक (*घातer_on)(व्योम);
	पूर्णांक (*घातer_off)(व्योम);
पूर्ण;
#पूर्ण_अगर  /* __KXTJ9_H__ */
