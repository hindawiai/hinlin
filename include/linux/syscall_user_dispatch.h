<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 Collabora Ltd.
 */
#अगर_अघोषित _SYSCALL_USER_DISPATCH_H
#घोषणा _SYSCALL_USER_DISPATCH_H

#समावेश <linux/thपढ़ो_info.h>

#अगर_घोषित CONFIG_GENERIC_ENTRY

काष्ठा syscall_user_dispatch अणु
	अक्षर __user	*selector;
	अचिन्हित दीर्घ	offset;
	अचिन्हित दीर्घ	len;
	bool		on_dispatch;
पूर्ण;

पूर्णांक set_syscall_user_dispatch(अचिन्हित दीर्घ mode, अचिन्हित दीर्घ offset,
			      अचिन्हित दीर्घ len, अक्षर __user *selector);

#घोषणा clear_syscall_work_syscall_user_dispatch(tsk) \
	clear_task_syscall_work(tsk, SYSCALL_USER_DISPATCH)

#अन्यथा
काष्ठा syscall_user_dispatch अणुपूर्ण;

अटल अंतरभूत पूर्णांक set_syscall_user_dispatch(अचिन्हित दीर्घ mode, अचिन्हित दीर्घ offset,
					    अचिन्हित दीर्घ len, अक्षर __user *selector)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम clear_syscall_work_syscall_user_dispatch(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_ENTRY */

#पूर्ण_अगर /* _SYSCALL_USER_DISPATCH_H */
