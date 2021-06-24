<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DNOTIFY_H
#घोषणा _LINUX_DNOTIFY_H
/*
 * Directory notअगरication क्रम Linux
 *
 * Copyright (C) 2000,2002 Stephen Rothwell
 */

#समावेश <linux/fs.h>

काष्ठा dnotअगरy_काष्ठा अणु
	काष्ठा dnotअगरy_काष्ठा *	dn_next;
	__u32			dn_mask;
	पूर्णांक			dn_fd;
	काष्ठा file *		dn_filp;
	fl_owner_t		dn_owner;
पूर्ण;

#अगर_घोषित __KERNEL__


#अगर_घोषित CONFIG_DNOTIFY

#घोषणा DNOTIFY_ALL_EVENTS (FS_DELETE | FS_DELETE_CHILD |\
			    FS_MODIFY | FS_MODIFY_CHILD |\
			    FS_ACCESS | FS_ACCESS_CHILD |\
			    FS_ATTRIB | FS_ATTRIB_CHILD |\
			    FS_CREATE | FS_DN_RENAME |\
			    FS_MOVED_FROM | FS_MOVED_TO)

बाह्य पूर्णांक dir_notअगरy_enable;
बाह्य व्योम dnotअगरy_flush(काष्ठा file *, fl_owner_t);
बाह्य पूर्णांक fcntl_dirnotअगरy(पूर्णांक, काष्ठा file *, अचिन्हित दीर्घ);

#अन्यथा

अटल अंतरभूत व्योम dnotअगरy_flush(काष्ठा file *filp, fl_owner_t id)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक fcntl_dirnotअगरy(पूर्णांक fd, काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* CONFIG_DNOTIFY */

#पूर्ण_अगर /* __KERNEL __ */

#पूर्ण_अगर /* _LINUX_DNOTIFY_H */
