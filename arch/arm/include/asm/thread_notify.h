<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/thपढ़ो_notअगरy.h
 *
 *  Copyright (C) 2006 Russell King.
 */
#अगर_अघोषित ASMARM_THREAD_NOTIFY_H
#घोषणा ASMARM_THREAD_NOTIFY_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/notअगरier.h>
#समावेश <यंत्र/thपढ़ो_info.h>

अटल अंतरभूत पूर्णांक thपढ़ो_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *n)
अणु
	बाह्य काष्ठा atomic_notअगरier_head thपढ़ो_notअगरy_head;
	वापस atomic_notअगरier_chain_रेजिस्टर(&thपढ़ो_notअगरy_head, n);
पूर्ण

अटल अंतरभूत व्योम thपढ़ो_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *n)
अणु
	बाह्य काष्ठा atomic_notअगरier_head thपढ़ो_notअगरy_head;
	atomic_notअगरier_chain_unरेजिस्टर(&thपढ़ो_notअगरy_head, n);
पूर्ण

अटल अंतरभूत व्योम thपढ़ो_notअगरy(अचिन्हित दीर्घ rc, काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	बाह्य काष्ठा atomic_notअगरier_head thपढ़ो_notअगरy_head;
	atomic_notअगरier_call_chain(&thपढ़ो_notअगरy_head, rc, thपढ़ो);
पूर्ण

#पूर्ण_अगर

/*
 * These are the reason codes क्रम the thपढ़ो notअगरier.
 */
#घोषणा THREAD_NOTIFY_FLUSH	0
#घोषणा THREAD_NOTIFY_EXIT	1
#घोषणा THREAD_NOTIFY_SWITCH	2
#घोषणा THREAD_NOTIFY_COPY	3

#पूर्ण_अगर
#पूर्ण_अगर
