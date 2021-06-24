<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * super.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_SUPER_H
#घोषणा OCFS2_SUPER_H

__म_लिखो(3, 4)
पूर्णांक __ocfs2_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		   स्थिर अक्षर *fmt, ...);

#घोषणा ocfs2_error(sb, fmt, ...)					\
	__ocfs2_error(sb, __PRETTY_FUNCTION__, fmt, ##__VA_ARGS__)

__म_लिखो(3, 4)
व्योम __ocfs2_पात(काष्ठा super_block *sb, स्थिर अक्षर *function,
		   स्थिर अक्षर *fmt, ...);

#घोषणा ocfs2_पात(sb, fmt, ...)					\
	__ocfs2_पात(sb, __PRETTY_FUNCTION__, fmt, ##__VA_ARGS__)

/*
 * Void संकेत blockers, because in-kernel sigprocmask() only fails
 * when SIG_* is wrong.
 */
व्योम ocfs2_block_संकेतs(sigset_t *oldset);
व्योम ocfs2_unblock_संकेतs(sigset_t *oldset);

#पूर्ण_अगर /* OCFS2_SUPER_H */
