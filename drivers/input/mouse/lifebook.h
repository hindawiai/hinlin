<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Fujitsu B-series Lअगरebook PS/2 TouchScreen driver
 *
 * Copyright (c) 2005 Vojtech Pavlik
 */

#अगर_अघोषित _LIFEBOOK_H
#घोषणा _LIFEBOOK_H

पूर्णांक lअगरebook_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक lअगरebook_init(काष्ठा psmouse *psmouse);

#अगर_घोषित CONFIG_MOUSE_PS2_LIFEBOOK
व्योम lअगरebook_module_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम lअगरebook_module_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
