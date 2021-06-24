<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_CACHEINFO_H
#घोषणा _PPC_CACHEINFO_H

/* These are just hooks क्रम sysfs.c to use. */
बाह्य व्योम cacheinfo_cpu_online(अचिन्हित पूर्णांक cpu_id);
बाह्य व्योम cacheinfo_cpu_offline(अचिन्हित पूर्णांक cpu_id);

/* Allow migration/suspend to tear करोwn and rebuild the hierarchy. */
बाह्य व्योम cacheinfo_tearकरोwn(व्योम);
बाह्य व्योम cacheinfo_rebuild(व्योम);

#पूर्ण_अगर /* _PPC_CACHEINFO_H */
