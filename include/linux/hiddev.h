<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 1999-2000 Vojtech Pavlik
 *
 *  Sponsored by SuSE
 */
/*
 * 
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@suse.cz>, or by paper mail:
 * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Reखुला
 */
#अगर_अघोषित _HIDDEV_H
#घोषणा _HIDDEV_H

#समावेश <uapi/linux/hiddev.h>


/*
 * In-kernel definitions.
 */

काष्ठा hiddev अणु
	पूर्णांक minor;
	पूर्णांक exist;
	पूर्णांक खोलो;
	काष्ठा mutex existancelock;
	रुको_queue_head_t रुको;
	काष्ठा hid_device *hid;
	काष्ठा list_head list;
	spinlock_t list_lock;
	bool initialized;
पूर्ण;

काष्ठा hid_device;
काष्ठा hid_usage;
काष्ठा hid_field;
काष्ठा hid_report;

#अगर_घोषित CONFIG_USB_HIDDEV
पूर्णांक hiddev_connect(काष्ठा hid_device *hid, अचिन्हित पूर्णांक क्रमce);
व्योम hiddev_disconnect(काष्ठा hid_device *);
व्योम hiddev_hid_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
		      काष्ठा hid_usage *usage, __s32 value);
व्योम hiddev_report_event(काष्ठा hid_device *hid, काष्ठा hid_report *report);
#अन्यथा
अटल अंतरभूत पूर्णांक hiddev_connect(काष्ठा hid_device *hid,
		अचिन्हित पूर्णांक क्रमce)
अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम hiddev_disconnect(काष्ठा hid_device *hid) अणु पूर्ण
अटल अंतरभूत व्योम hiddev_hid_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
		      काष्ठा hid_usage *usage, __s32 value) अणु पूर्ण
अटल अंतरभूत व्योम hiddev_report_event(काष्ठा hid_device *hid, काष्ठा hid_report *report) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
