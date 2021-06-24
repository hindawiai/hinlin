<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (c) 2007 Jiri Kosina
 */
#अगर_अघोषित _HIDRAW_H
#घोषणा _HIDRAW_H

#समावेश <uapi/linux/hidraw.h>


काष्ठा hidraw अणु
	अचिन्हित पूर्णांक minor;
	पूर्णांक exist;
	पूर्णांक खोलो;
	रुको_queue_head_t रुको;
	काष्ठा hid_device *hid;
	काष्ठा device *dev;
	spinlock_t list_lock;
	काष्ठा list_head list;
पूर्ण;

काष्ठा hidraw_report अणु
	__u8 *value;
	पूर्णांक len;
पूर्ण;

काष्ठा hidraw_list अणु
	काष्ठा hidraw_report buffer[HIDRAW_BUFFER_SIZE];
	पूर्णांक head;
	पूर्णांक tail;
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा hidraw *hidraw;
	काष्ठा list_head node;
	काष्ठा mutex पढ़ो_mutex;
पूर्ण;

#अगर_घोषित CONFIG_HIDRAW
पूर्णांक hidraw_init(व्योम);
व्योम hidraw_निकास(व्योम);
पूर्णांक hidraw_report_event(काष्ठा hid_device *, u8 *, पूर्णांक);
पूर्णांक hidraw_connect(काष्ठा hid_device *);
व्योम hidraw_disconnect(काष्ठा hid_device *);
#अन्यथा
अटल अंतरभूत पूर्णांक hidraw_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम hidraw_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक hidraw_report_event(काष्ठा hid_device *hid, u8 *data, पूर्णांक len) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक hidraw_connect(काष्ठा hid_device *hid) अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम hidraw_disconnect(काष्ठा hid_device *hid) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
