<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_DEBUG_H
#घोषणा __HID_DEBUG_H

/*
 *  Copyright (c) 2007-2009	Jiri Kosina
 */

/*
 */

#अगर_घोषित CONFIG_DEBUG_FS

#समावेश <linux/kfअगरo.h>

#घोषणा HID_DEBUG_बफ_मानE 512
#घोषणा HID_DEBUG_FIFOSIZE 512

व्योम hid_dump_input(काष्ठा hid_device *, काष्ठा hid_usage *, __s32);
व्योम hid_dump_report(काष्ठा hid_device *, पूर्णांक , u8 *, पूर्णांक);
व्योम hid_dump_device(काष्ठा hid_device *, काष्ठा seq_file *);
व्योम hid_dump_field(काष्ठा hid_field *, पूर्णांक, काष्ठा seq_file *);
अक्षर *hid_resolv_usage(अचिन्हित, काष्ठा seq_file *);
व्योम hid_debug_रेजिस्टर(काष्ठा hid_device *, स्थिर अक्षर *);
व्योम hid_debug_unरेजिस्टर(काष्ठा hid_device *);
व्योम hid_debug_init(व्योम);
व्योम hid_debug_निकास(व्योम);
व्योम hid_debug_event(काष्ठा hid_device *, अक्षर *);

काष्ठा hid_debug_list अणु
	DECLARE_KFIFO_PTR(hid_debug_fअगरo, अक्षर);
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा hid_device *hdev;
	काष्ठा list_head node;
	काष्ठा mutex पढ़ो_mutex;
पूर्ण;

#अन्यथा

#घोषणा hid_dump_input(a,b,c)		करो अणु पूर्ण जबतक (0)
#घोषणा hid_dump_report(a,b,c,d)	करो अणु पूर्ण जबतक (0)
#घोषणा hid_dump_device(a,b)		करो अणु पूर्ण जबतक (0)
#घोषणा hid_dump_field(a,b,c)		करो अणु पूर्ण जबतक (0)
#घोषणा hid_resolv_usage(a,b)		करो अणु पूर्ण जबतक (0)
#घोषणा hid_debug_रेजिस्टर(a, b)	करो अणु पूर्ण जबतक (0)
#घोषणा hid_debug_unरेजिस्टर(a)		करो अणु पूर्ण जबतक (0)
#घोषणा hid_debug_init()		करो अणु पूर्ण जबतक (0)
#घोषणा hid_debug_निकास()		करो अणु पूर्ण जबतक (0)
#घोषणा hid_debug_event(a,b)		करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#पूर्ण_अगर
