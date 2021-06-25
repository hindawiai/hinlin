<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_H
#घोषणा __HID_ROCCAT_H

/*
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/types.h>

#घोषणा ROCCATIOCGREPSIZE _IOR('H', 0xf1, पूर्णांक)

#अगर_घोषित __KERNEL__

पूर्णांक roccat_connect(काष्ठा class *klass, काष्ठा hid_device *hid,
		पूर्णांक report_size);
व्योम roccat_disconnect(पूर्णांक minor);
पूर्णांक roccat_report_event(पूर्णांक minor, u8 स्थिर *data);

#पूर्ण_अगर

#पूर्ण_अगर
