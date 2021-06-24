<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SWAP_CGROUP_H
#घोषणा __LINUX_SWAP_CGROUP_H

#समावेश <linux/swap.h>

#अगर_घोषित CONFIG_MEMCG_SWAP

बाह्य अचिन्हित लघु swap_cgroup_cmpxchg(swp_entry_t ent,
					अचिन्हित लघु old, अचिन्हित लघु new);
बाह्य अचिन्हित लघु swap_cgroup_record(swp_entry_t ent, अचिन्हित लघु id,
					 अचिन्हित पूर्णांक nr_ents);
बाह्य अचिन्हित लघु lookup_swap_cgroup_id(swp_entry_t ent);
बाह्य पूर्णांक swap_cgroup_swapon(पूर्णांक type, अचिन्हित दीर्घ max_pages);
बाह्य व्योम swap_cgroup_swapoff(पूर्णांक type);

#अन्यथा

अटल अंतरभूत
अचिन्हित लघु swap_cgroup_record(swp_entry_t ent, अचिन्हित लघु id,
				  अचिन्हित पूर्णांक nr_ents)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
अचिन्हित लघु lookup_swap_cgroup_id(swp_entry_t ent)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
swap_cgroup_swapon(पूर्णांक type, अचिन्हित दीर्घ max_pages)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम swap_cgroup_swapoff(पूर्णांक type)
अणु
	वापस;
पूर्ण

#पूर्ण_अगर /* CONFIG_MEMCG_SWAP */

#पूर्ण_अगर /* __LINUX_SWAP_CGROUP_H */
