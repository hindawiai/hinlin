<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 - 2010 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 */

#अगर_अघोषित __LINUX_MCS_H
#घोषणा __LINUX_MCS_H

#घोषणा MCS_KEY_MAP(v, c)	((((v) & 0xff) << 16) | ((c) & 0xffff))
#घोषणा MCS_KEY_VAL(v)		(((v) >> 16) & 0xff)
#घोषणा MCS_KEY_CODE(v)		((v) & 0xffff)

काष्ठा mcs_platक्रमm_data अणु
	व्योम (*घातeron)(bool);
	व्योम (*cfg_pin)(व्योम);

	/* touchscreen */
	अचिन्हित पूर्णांक x_size;
	अचिन्हित पूर्णांक y_size;

	/* touchkey */
	स्थिर u32 *keymap;
	अचिन्हित पूर्णांक keymap_size;
	अचिन्हित पूर्णांक key_maxval;
	bool no_स्वतःrepeat;
पूर्ण;

#पूर्ण_अगर	/* __LINUX_MCS_H */
