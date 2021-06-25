<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम Virtual PS/2 Mouse on VMware and QEMU hypervisors.
 *
 * Copyright (C) 2014, VMware, Inc. All Rights Reserved.
 */

#अगर_अघोषित _VMMOUSE_H
#घोषणा _VMMOUSE_H

#घोषणा VMMOUSE_PSNAME  "VirtualPS/2"

पूर्णांक vmmouse_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक vmmouse_init(काष्ठा psmouse *psmouse);

#पूर्ण_अगर
