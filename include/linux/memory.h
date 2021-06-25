<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/memory.h - generic memory definition
 *
 * This is मुख्यly क्रम topological representation. We define the
 * basic "struct memory_block" here, which can be embedded in per-arch
 * definitions or NUMA inक्रमmation.
 *
 * Basic handling of the devices is करोne in drivers/base/memory.c
 * and प्रणाली devices are handled in drivers/base/sys.c.
 *
 * Memory block are exported via sysfs in the class/memory/devices/
 * directory.
 *
 */
#अगर_अघोषित _LINUX_MEMORY_H_
#घोषणा _LINUX_MEMORY_H_

#समावेश <linux/node.h>
#समावेश <linux/compiler.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>

#घोषणा MIN_MEMORY_BLOCK_SIZE     (1UL << SECTION_SIZE_BITS)

काष्ठा memory_block अणु
	अचिन्हित दीर्घ start_section_nr;
	अचिन्हित दीर्घ state;		/* serialized by the dev->lock */
	पूर्णांक online_type;		/* क्रम passing data to online routine */
	पूर्णांक nid;			/* NID क्रम this memory block */
	काष्ठा device dev;
	/*
	 * Number of vmemmap pages. These pages
	 * lay at the beginning of the memory block.
	 */
	अचिन्हित दीर्घ nr_vmemmap_pages;
पूर्ण;

पूर्णांक arch_get_memory_phys_device(अचिन्हित दीर्घ start_pfn);
अचिन्हित दीर्घ memory_block_size_bytes(व्योम);
पूर्णांक set_memory_block_size_order(अचिन्हित पूर्णांक order);

/* These states are exposed to userspace as text strings in sysfs */
#घोषणा	MEM_ONLINE		(1<<0) /* exposed to userspace */
#घोषणा	MEM_GOING_OFFLINE	(1<<1) /* exposed to userspace */
#घोषणा	MEM_OFFLINE		(1<<2) /* exposed to userspace */
#घोषणा	MEM_GOING_ONLINE	(1<<3)
#घोषणा	MEM_CANCEL_ONLINE	(1<<4)
#घोषणा	MEM_CANCEL_OFFLINE	(1<<5)

काष्ठा memory_notअगरy अणु
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ nr_pages;
	पूर्णांक status_change_nid_normal;
	पूर्णांक status_change_nid_high;
	पूर्णांक status_change_nid;
पूर्ण;

काष्ठा notअगरier_block;
काष्ठा mem_section;

/*
 * Priorities क्रम the hotplug memory callback routines (stored in decreasing
 * order in the callback chain)
 */
#घोषणा SLAB_CALLBACK_PRI       1
#घोषणा IPC_CALLBACK_PRI        10

#अगर_अघोषित CONFIG_MEMORY_HOTPLUG_SPARSE
अटल अंतरभूत व्योम memory_dev_init(व्योम)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_memory_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_memory_notअगरier(काष्ठा notअगरier_block *nb)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक memory_notअगरy(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस 0;
पूर्ण
#अन्यथा
बाह्य पूर्णांक रेजिस्टर_memory_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य व्योम unरेजिस्टर_memory_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक create_memory_block_devices(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ vmemmap_pages);
व्योम हटाओ_memory_block_devices(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
बाह्य व्योम memory_dev_init(व्योम);
बाह्य पूर्णांक memory_notअगरy(अचिन्हित दीर्घ val, व्योम *v);
बाह्य काष्ठा memory_block *find_memory_block(काष्ठा mem_section *);
प्रकार पूर्णांक (*walk_memory_blocks_func_t)(काष्ठा memory_block *, व्योम *);
बाह्य पूर्णांक walk_memory_blocks(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			      व्योम *arg, walk_memory_blocks_func_t func);
बाह्य पूर्णांक क्रम_each_memory_block(व्योम *arg, walk_memory_blocks_func_t func);
#घोषणा CONFIG_MEM_BLOCK_SIZE	(PAGES_PER_SECTION<<PAGE_SHIFT)
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG_SPARSE */

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
#घोषणा hotplug_memory_notअगरier(fn, pri) (अणु		\
	अटल __meminitdata काष्ठा notअगरier_block fn##_mem_nb =\
		अणु .notअगरier_call = fn, .priority = pri पूर्ण;\
	रेजिस्टर_memory_notअगरier(&fn##_mem_nb);			\
पूर्ण)
#घोषणा रेजिस्टर_hoपंचांगemory_notअगरier(nb)		रेजिस्टर_memory_notअगरier(nb)
#घोषणा unरेजिस्टर_hoपंचांगemory_notअगरier(nb) 	unरेजिस्टर_memory_notअगरier(nb)
#अन्यथा
#घोषणा hotplug_memory_notअगरier(fn, pri)	(अणु 0; पूर्ण)
/* These aren't अंतरभूत functions due to a GCC bug. */
#घोषणा रेजिस्टर_hoपंचांगemory_notअगरier(nb)    (अणु (व्योम)(nb); 0; पूर्ण)
#घोषणा unरेजिस्टर_hoपंचांगemory_notअगरier(nb)  (अणु (व्योम)(nb); पूर्ण)
#पूर्ण_अगर

/*
 * Kernel text modअगरication mutex, used क्रम code patching. Users of this lock
 * can sleep.
 */
बाह्य काष्ठा mutex text_mutex;

#पूर्ण_अगर /* _LINUX_MEMORY_H_ */
