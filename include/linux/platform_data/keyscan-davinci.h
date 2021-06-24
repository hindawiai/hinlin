<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Texas Instruments, Inc
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 */

#अगर_अघोषित DAVINCI_KEYSCAN_H
#घोषणा DAVINCI_KEYSCAN_H

#समावेश <linux/पन.स>

क्रमागत davinci_matrix_types अणु
	DAVINCI_KEYSCAN_MATRIX_4X4,
	DAVINCI_KEYSCAN_MATRIX_5X3,
पूर्ण;

काष्ठा davinci_ks_platक्रमm_data अणु
	पूर्णांक		(*device_enable)(काष्ठा device *dev);
	अचिन्हित लघु	*keymap;
	u32		keymapsize;
	u8		rep:1;
	u8		strobe;
	u8		पूर्णांकerval;
	u8		matrix_type;
पूर्ण;

#पूर्ण_अगर

