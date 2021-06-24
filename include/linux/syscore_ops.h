<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  syscore_ops.h - System core operations.
 *
 *  Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */

#अगर_अघोषित _LINUX_SYSCORE_OPS_H
#घोषणा _LINUX_SYSCORE_OPS_H

#समावेश <linux/list.h>

काष्ठा syscore_ops अणु
	काष्ठा list_head node;
	पूर्णांक (*suspend)(व्योम);
	व्योम (*resume)(व्योम);
	व्योम (*shutकरोwn)(व्योम);
पूर्ण;

बाह्य व्योम रेजिस्टर_syscore_ops(काष्ठा syscore_ops *ops);
बाह्य व्योम unरेजिस्टर_syscore_ops(काष्ठा syscore_ops *ops);
#अगर_घोषित CONFIG_PM_SLEEP
बाह्य पूर्णांक syscore_suspend(व्योम);
बाह्य व्योम syscore_resume(व्योम);
#पूर्ण_अगर
बाह्य व्योम syscore_shutकरोwn(व्योम);

#पूर्ण_अगर
