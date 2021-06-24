<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * debug.h - NTFS kernel debug support. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_DEBUG_H
#घोषणा _LINUX_NTFS_DEBUG_H

#समावेश <linux/fs.h>

#समावेश "runlist.h"

#अगर_घोषित DEBUG

बाह्य पूर्णांक debug_msgs;

बाह्य __म_लिखो(4, 5)
व्योम __ntfs_debug(स्थिर अक्षर *file, पूर्णांक line, स्थिर अक्षर *function,
		  स्थिर अक्षर *क्रमmat, ...);
/**
 * ntfs_debug - ग_लिखो a debug level message to syslog
 * @f:		a म_लिखो क्रमmat string containing the message
 * @...:	the variables to substitute पूर्णांकo @f
 *
 * ntfs_debug() ग_लिखोs a DEBUG level message to the syslog but only अगर the
 * driver was compiled with -DDEBUG. Otherwise, the call turns पूर्णांकo a NOP.
 */
#घोषणा ntfs_debug(f, a...)						\
	__ntfs_debug(__खाता__, __LINE__, __func__, f, ##a)

बाह्य व्योम ntfs_debug_dump_runlist(स्थिर runlist_element *rl);

#अन्यथा	/* !DEBUG */

#घोषणा ntfs_debug(fmt, ...)						\
करो अणु									\
	अगर (0)								\
		no_prपूर्णांकk(fmt, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा ntfs_debug_dump_runlist(rl)	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर	/* !DEBUG */

बाह्य  __म_लिखो(3, 4)
व्योम __ntfs_warning(स्थिर अक्षर *function, स्थिर काष्ठा super_block *sb,
		    स्थिर अक्षर *fmt, ...);
#घोषणा ntfs_warning(sb, f, a...)	__ntfs_warning(__func__, sb, f, ##a)

बाह्य  __म_लिखो(3, 4)
व्योम __ntfs_error(स्थिर अक्षर *function, स्थिर काष्ठा super_block *sb,
		  स्थिर अक्षर *fmt, ...);
#घोषणा ntfs_error(sb, f, a...)		__ntfs_error(__func__, sb, f, ##a)

#पूर्ण_अगर /* _LINUX_NTFS_DEBUG_H */
