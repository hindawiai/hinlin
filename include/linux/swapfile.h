<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SWAPखाता_H
#घोषणा _LINUX_SWAPखाता_H

/*
 * these were अटल in swapfile.c but frontswap.c needs them and we करोn't
 * want to expose them to the करोzens of source files that include swap.h
 */
बाह्य spinlock_t swap_lock;
बाह्य काष्ठा plist_head swap_active_head;
बाह्य काष्ठा swap_info_काष्ठा *swap_info[];
बाह्य पूर्णांक try_to_unuse(अचिन्हित पूर्णांक, bool, अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ generic_max_swapfile_size(व्योम);
बाह्य अचिन्हित दीर्घ max_swapfile_size(व्योम);

#पूर्ण_अगर /* _LINUX_SWAPखाता_H */
