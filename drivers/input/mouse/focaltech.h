<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Focaltech TouchPad PS/2 mouse driver
 *
 * Copyright (c) 2014 Red Hat Inc.
 * Copyright (c) 2014 Mathias Gottschlag <mgottschlag@gmail.com>
 *
 * Red Hat authors:
 *
 * Hans de Goede <hdegoede@redhat.com>
 */

#अगर_अघोषित _FOCALTECH_H
#घोषणा _FOCALTECH_H

पूर्णांक focaltech_detect(काष्ठा psmouse *psmouse, bool set_properties);

#अगर_घोषित CONFIG_MOUSE_PS2_FOCALTECH
पूर्णांक focaltech_init(काष्ठा psmouse *psmouse);
#अन्यथा
अटल अंतरभूत पूर्णांक focaltech_init(काष्ठा psmouse *psmouse)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
