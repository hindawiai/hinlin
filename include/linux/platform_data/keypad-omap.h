<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2006 Komal Shah <komal_shah802003@yahoo.com>
 */
#अगर_अघोषित __KEYPAD_OMAP_H
#घोषणा __KEYPAD_OMAP_H

#अगर_अघोषित CONFIG_ARCH_OMAP1
#warning Please update the board to use matrix-keypad driver
#घोषणा omap_पढ़ोw(reg)		0
#घोषणा omap_ग_लिखोw(val, reg)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#समावेश <linux/input/matrix_keypad.h>

काष्ठा omap_kp_platक्रमm_data अणु
	पूर्णांक rows;
	पूर्णांक cols;
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	bool rep;
	अचिन्हित दीर्घ delay;
	bool dbounce;
	/* specअगरic to OMAP242x*/
	अचिन्हित पूर्णांक *row_gpios;
	अचिन्हित पूर्णांक *col_gpios;
पूर्ण;

/* Group (0..3) -- when multiple keys are pressed, only the
 * keys pressed in the same group are considered as pressed. This is
 * in order to workaround certain crappy HW designs that produce ghost
 * keypresses. Two मुक्त bits, not used by neither row/col nor keynum,
 * must be available क्रम use as group bits. The below GROUP_SHIFT
 * macro definition is based on some prior knowledge of the
 * matrix_keypad defined KEY() macro पूर्णांकernals.
 */
#घोषणा GROUP_SHIFT	14
#घोषणा GROUP_0		(0 << GROUP_SHIFT)
#घोषणा GROUP_1		(1 << GROUP_SHIFT)
#घोषणा GROUP_2		(2 << GROUP_SHIFT)
#घोषणा GROUP_3		(3 << GROUP_SHIFT)
#घोषणा GROUP_MASK	GROUP_3
#अगर KEY_MAX & GROUP_MASK
#त्रुटि Group bits in conflict with keynum bits
#पूर्ण_अगर


#पूर्ण_अगर

