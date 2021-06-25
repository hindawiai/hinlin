<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device Mapper Uevent Support
 *
 * Copyright IBM Corporation, 2007
 * 	Author: Mike Anderson <andmike@linux.vnet.ibm.com>
 */
#अगर_अघोषित DM_UEVENT_H
#घोषणा DM_UEVENT_H

क्रमागत dm_uevent_type अणु
	DM_UEVENT_PATH_FAILED,
	DM_UEVENT_PATH_REINSTATED,
पूर्ण;

#अगर_घोषित CONFIG_DM_UEVENT

बाह्य पूर्णांक dm_uevent_init(व्योम);
बाह्य व्योम dm_uevent_निकास(व्योम);
बाह्य व्योम dm_send_uevents(काष्ठा list_head *events, काष्ठा kobject *kobj);
बाह्य व्योम dm_path_uevent(क्रमागत dm_uevent_type event_type,
			   काष्ठा dm_target *ti, स्थिर अक्षर *path,
			   अचिन्हित nr_valid_paths);

#अन्यथा

अटल अंतरभूत पूर्णांक dm_uevent_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dm_uevent_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम dm_send_uevents(काष्ठा list_head *events,
				   काष्ठा kobject *kobj)
अणु
पूर्ण
अटल अंतरभूत व्योम dm_path_uevent(क्रमागत dm_uevent_type event_type,
				  काष्ठा dm_target *ti, स्थिर अक्षर *path,
				  अचिन्हित nr_valid_paths)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_DM_UEVENT */

#पूर्ण_अगर	/* DM_UEVENT_H */
