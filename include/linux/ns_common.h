<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NS_COMMON_H
#घोषणा _LINUX_NS_COMMON_H

#समावेश <linux/refcount.h>

काष्ठा proc_ns_operations;

काष्ठा ns_common अणु
	atomic_दीर्घ_t stashed;
	स्थिर काष्ठा proc_ns_operations *ops;
	अचिन्हित पूर्णांक inum;
	refcount_t count;
पूर्ण;

#पूर्ण_अगर
