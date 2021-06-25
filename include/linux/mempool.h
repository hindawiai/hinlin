<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * memory buffer pool support
 */
#अगर_अघोषित _LINUX_MEMPOOL_H
#घोषणा _LINUX_MEMPOOL_H

#समावेश <linux/रुको.h>
#समावेश <linux/compiler.h>

काष्ठा kmem_cache;

प्रकार व्योम * (mempool_alloc_t)(gfp_t gfp_mask, व्योम *pool_data);
प्रकार व्योम (mempool_मुक्त_t)(व्योम *element, व्योम *pool_data);

प्रकार काष्ठा mempool_s अणु
	spinlock_t lock;
	पूर्णांक min_nr;		/* nr of elements at *elements */
	पूर्णांक curr_nr;		/* Current nr of elements at *elements */
	व्योम **elements;

	व्योम *pool_data;
	mempool_alloc_t *alloc;
	mempool_मुक्त_t *मुक्त;
	रुको_queue_head_t रुको;
पूर्ण mempool_t;

अटल अंतरभूत bool mempool_initialized(mempool_t *pool)
अणु
	वापस pool->elements != शून्य;
पूर्ण

व्योम mempool_निकास(mempool_t *pool);
पूर्णांक mempool_init_node(mempool_t *pool, पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
		      mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data,
		      gfp_t gfp_mask, पूर्णांक node_id);
पूर्णांक mempool_init(mempool_t *pool, पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
		 mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data);

बाह्य mempool_t *mempool_create(पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
			mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data);
बाह्य mempool_t *mempool_create_node(पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
			mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data,
			gfp_t gfp_mask, पूर्णांक nid);

बाह्य पूर्णांक mempool_resize(mempool_t *pool, पूर्णांक new_min_nr);
बाह्य व्योम mempool_destroy(mempool_t *pool);
बाह्य व्योम *mempool_alloc(mempool_t *pool, gfp_t gfp_mask) __दो_स्मृति;
बाह्य व्योम mempool_मुक्त(व्योम *element, mempool_t *pool);

/*
 * A mempool_alloc_t and mempool_मुक्त_t that get the memory from
 * a slab cache that is passed in through pool_data.
 * Note: the slab cache may not have a ctor function.
 */
व्योम *mempool_alloc_slab(gfp_t gfp_mask, व्योम *pool_data);
व्योम mempool_मुक्त_slab(व्योम *element, व्योम *pool_data);

अटल अंतरभूत पूर्णांक
mempool_init_slab_pool(mempool_t *pool, पूर्णांक min_nr, काष्ठा kmem_cache *kc)
अणु
	वापस mempool_init(pool, min_nr, mempool_alloc_slab,
			    mempool_मुक्त_slab, (व्योम *) kc);
पूर्ण

अटल अंतरभूत mempool_t *
mempool_create_slab_pool(पूर्णांक min_nr, काष्ठा kmem_cache *kc)
अणु
	वापस mempool_create(min_nr, mempool_alloc_slab, mempool_मुक्त_slab,
			      (व्योम *) kc);
पूर्ण

/*
 * a mempool_alloc_t and a mempool_मुक्त_t to kदो_स्मृति and kमुक्त the
 * amount of memory specअगरied by pool_data
 */
व्योम *mempool_kदो_स्मृति(gfp_t gfp_mask, व्योम *pool_data);
व्योम mempool_kमुक्त(व्योम *element, व्योम *pool_data);

अटल अंतरभूत पूर्णांक mempool_init_kदो_स्मृति_pool(mempool_t *pool, पूर्णांक min_nr, माप_प्रकार size)
अणु
	वापस mempool_init(pool, min_nr, mempool_kदो_स्मृति,
			    mempool_kमुक्त, (व्योम *) size);
पूर्ण

अटल अंतरभूत mempool_t *mempool_create_kदो_स्मृति_pool(पूर्णांक min_nr, माप_प्रकार size)
अणु
	वापस mempool_create(min_nr, mempool_kदो_स्मृति, mempool_kमुक्त,
			      (व्योम *) size);
पूर्ण

/*
 * A mempool_alloc_t and mempool_मुक्त_t क्रम a simple page allocator that
 * allocates pages of the order specअगरied by pool_data
 */
व्योम *mempool_alloc_pages(gfp_t gfp_mask, व्योम *pool_data);
व्योम mempool_मुक्त_pages(व्योम *element, व्योम *pool_data);

अटल अंतरभूत पूर्णांक mempool_init_page_pool(mempool_t *pool, पूर्णांक min_nr, पूर्णांक order)
अणु
	वापस mempool_init(pool, min_nr, mempool_alloc_pages,
			    mempool_मुक्त_pages, (व्योम *)(दीर्घ)order);
पूर्ण

अटल अंतरभूत mempool_t *mempool_create_page_pool(पूर्णांक min_nr, पूर्णांक order)
अणु
	वापस mempool_create(min_nr, mempool_alloc_pages, mempool_मुक्त_pages,
			      (व्योम *)(दीर्घ)order);
पूर्ण

#पूर्ण_अगर /* _LINUX_MEMPOOL_H */
