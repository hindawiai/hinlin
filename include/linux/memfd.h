<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MEMFD_H
#घोषणा __LINUX_MEMFD_H

#समावेश <linux/file.h>

#अगर_घोषित CONFIG_MEMFD_CREATE
बाह्य दीर्घ memfd_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#अन्यथा
अटल अंतरभूत दीर्घ memfd_fcntl(काष्ठा file *f, अचिन्हित पूर्णांक c, अचिन्हित दीर्घ a)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MEMFD_H */
