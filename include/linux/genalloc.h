<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Basic general purpose allocator क्रम managing special purpose
 * memory, क्रम example, memory that is not managed by the regular
 * kदो_स्मृति/kमुक्त पूर्णांकerface.  Uses क्रम this includes on-device special
 * memory, uncached memory etc.
 *
 * It is safe to use the allocator in NMI handlers and other special
 * unblockable contexts that could otherwise deadlock on locks.  This
 * is implemented by using atomic operations and retries on any
 * conflicts.  The disadvantage is that there may be livelocks in
 * extreme हालs.  For better scalability, one allocator can be used
 * क्रम each CPU.
 *
 * The lockless operation only works अगर there is enough memory
 * available.  If new memory is added to the pool a lock has to be
 * still taken.  So any user relying on locklessness has to ensure
 * that sufficient memory is pपुनः_स्मृतिated.
 *
 * The basic atomic operation of this allocator is cmpxchg on दीर्घ.
 * On architectures that करोn't have NMI-safe cmpxchg implementation,
 * the allocator can NOT be used in NMI handler.  So code uses the
 * allocator in NMI handler should depend on
 * CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG.
 */


#अगर_अघोषित __GENALLOC_H__
#घोषणा __GENALLOC_H__

#समावेश <linux/types.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/atomic.h>

काष्ठा device;
काष्ठा device_node;
काष्ठा gen_pool;

/**
 * प्रकार genpool_algo_t: Allocation callback function type definition
 * @map: Poपूर्णांकer to biपंचांगap
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @data: optional additional data used by the callback
 * @pool: the pool being allocated from
 */
प्रकार अचिन्हित दीर्घ (*genpool_algo_t)(अचिन्हित दीर्घ *map,
			अचिन्हित दीर्घ size,
			अचिन्हित दीर्घ start,
			अचिन्हित पूर्णांक nr,
			व्योम *data, काष्ठा gen_pool *pool,
			अचिन्हित दीर्घ start_addr);

/*
 *  General purpose special memory pool descriptor.
 */
काष्ठा gen_pool अणु
	spinlock_t lock;
	काष्ठा list_head chunks;	/* list of chunks in this pool */
	पूर्णांक min_alloc_order;		/* minimum allocation order */

	genpool_algo_t algo;		/* allocation function */
	व्योम *data;

	स्थिर अक्षर *name;
पूर्ण;

/*
 *  General purpose special memory pool chunk descriptor.
 */
काष्ठा gen_pool_chunk अणु
	काष्ठा list_head next_chunk;	/* next chunk in pool */
	atomic_दीर्घ_t avail;
	phys_addr_t phys_addr;		/* physical starting address of memory chunk */
	व्योम *owner;			/* निजी data to retrieve at alloc समय */
	अचिन्हित दीर्घ start_addr;	/* start address of memory chunk */
	अचिन्हित दीर्घ end_addr;		/* end address of memory chunk (inclusive) */
	अचिन्हित दीर्घ bits[];		/* biपंचांगap क्रम allocating memory chunk */
पूर्ण;

/*
 *  gen_pool data descriptor क्रम gen_pool_first_fit_align.
 */
काष्ठा genpool_data_align अणु
	पूर्णांक align;		/* alignment by bytes क्रम starting address */
पूर्ण;

/*
 *  gen_pool data descriptor क्रम gen_pool_fixed_alloc.
 */
काष्ठा genpool_data_fixed अणु
	अचिन्हित दीर्घ offset;		/* The offset of the specअगरic region */
पूर्ण;

बाह्य काष्ठा gen_pool *gen_pool_create(पूर्णांक, पूर्णांक);
बाह्य phys_addr_t gen_pool_virt_to_phys(काष्ठा gen_pool *pool, अचिन्हित दीर्घ);
बाह्य पूर्णांक gen_pool_add_owner(काष्ठा gen_pool *, अचिन्हित दीर्घ, phys_addr_t,
			     माप_प्रकार, पूर्णांक, व्योम *);

अटल अंतरभूत पूर्णांक gen_pool_add_virt(काष्ठा gen_pool *pool, अचिन्हित दीर्घ addr,
		phys_addr_t phys, माप_प्रकार size, पूर्णांक nid)
अणु
	वापस gen_pool_add_owner(pool, addr, phys, size, nid, शून्य);
पूर्ण

/**
 * gen_pool_add - add a new chunk of special memory to the pool
 * @pool: pool to add new memory chunk to
 * @addr: starting address of memory chunk to add to pool
 * @size: size in bytes of the memory chunk to add to pool
 * @nid: node id of the node the chunk काष्ठाure and biपंचांगap should be
 *       allocated on, or -1
 *
 * Add a new chunk of special memory to the specअगरied pool.
 *
 * Returns 0 on success or a -ve त्रुटि_सं on failure.
 */
अटल अंतरभूत पूर्णांक gen_pool_add(काष्ठा gen_pool *pool, अचिन्हित दीर्घ addr,
			       माप_प्रकार size, पूर्णांक nid)
अणु
	वापस gen_pool_add_virt(pool, addr, -1, size, nid);
पूर्ण
बाह्य व्योम gen_pool_destroy(काष्ठा gen_pool *);
अचिन्हित दीर्घ gen_pool_alloc_algo_owner(काष्ठा gen_pool *pool, माप_प्रकार size,
		genpool_algo_t algo, व्योम *data, व्योम **owner);

अटल अंतरभूत अचिन्हित दीर्घ gen_pool_alloc_owner(काष्ठा gen_pool *pool,
		माप_प्रकार size, व्योम **owner)
अणु
	वापस gen_pool_alloc_algo_owner(pool, size, pool->algo, pool->data,
			owner);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ gen_pool_alloc_algo(काष्ठा gen_pool *pool,
		माप_प्रकार size, genpool_algo_t algo, व्योम *data)
अणु
	वापस gen_pool_alloc_algo_owner(pool, size, algo, data, शून्य);
पूर्ण

/**
 * gen_pool_alloc - allocate special memory from the pool
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 *
 * Allocate the requested number of bytes from the specअगरied pool.
 * Uses the pool allocation function (with first-fit algorithm by शेष).
 * Can not be used in NMI handler on architectures without
 * NMI-safe cmpxchg implementation.
 */
अटल अंतरभूत अचिन्हित दीर्घ gen_pool_alloc(काष्ठा gen_pool *pool, माप_प्रकार size)
अणु
	वापस gen_pool_alloc_algo(pool, size, pool->algo, pool->data);
पूर्ण

बाह्य व्योम *gen_pool_dma_alloc(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma);
बाह्य व्योम *gen_pool_dma_alloc_algo(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, genpool_algo_t algo, व्योम *data);
बाह्य व्योम *gen_pool_dma_alloc_align(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, पूर्णांक align);
बाह्य व्योम *gen_pool_dma_zalloc(काष्ठा gen_pool *pool, माप_प्रकार size, dma_addr_t *dma);
बाह्य व्योम *gen_pool_dma_zalloc_algo(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, genpool_algo_t algo, व्योम *data);
बाह्य व्योम *gen_pool_dma_zalloc_align(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, पूर्णांक align);
बाह्य व्योम gen_pool_मुक्त_owner(काष्ठा gen_pool *pool, अचिन्हित दीर्घ addr,
		माप_प्रकार size, व्योम **owner);
अटल अंतरभूत व्योम gen_pool_मुक्त(काष्ठा gen_pool *pool, अचिन्हित दीर्घ addr,
                माप_प्रकार size)
अणु
	gen_pool_मुक्त_owner(pool, addr, size, शून्य);
पूर्ण

बाह्य व्योम gen_pool_क्रम_each_chunk(काष्ठा gen_pool *,
	व्योम (*)(काष्ठा gen_pool *, काष्ठा gen_pool_chunk *, व्योम *), व्योम *);
बाह्य माप_प्रकार gen_pool_avail(काष्ठा gen_pool *);
बाह्य माप_प्रकार gen_pool_size(काष्ठा gen_pool *);

बाह्य व्योम gen_pool_set_algo(काष्ठा gen_pool *pool, genpool_algo_t algo,
		व्योम *data);

बाह्य अचिन्हित दीर्घ gen_pool_first_fit(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr, व्योम *data,
		काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr);

बाह्य अचिन्हित दीर्घ gen_pool_fixed_alloc(अचिन्हित दीर्घ *map,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr,
		व्योम *data, काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr);

बाह्य अचिन्हित दीर्घ gen_pool_first_fit_align(अचिन्हित दीर्घ *map,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr,
		व्योम *data, काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr);


बाह्य अचिन्हित दीर्घ gen_pool_first_fit_order_align(अचिन्हित दीर्घ *map,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr,
		व्योम *data, काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr);

बाह्य अचिन्हित दीर्घ gen_pool_best_fit(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr, व्योम *data,
		काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr);


बाह्य काष्ठा gen_pool *devm_gen_pool_create(काष्ठा device *dev,
		पूर्णांक min_alloc_order, पूर्णांक nid, स्थिर अक्षर *name);
बाह्य काष्ठा gen_pool *gen_pool_get(काष्ठा device *dev, स्थिर अक्षर *name);

बाह्य bool gen_pool_has_addr(काष्ठा gen_pool *pool, अचिन्हित दीर्घ start,
			माप_प्रकार size);

#अगर_घोषित CONFIG_OF
बाह्य काष्ठा gen_pool *of_gen_pool_get(काष्ठा device_node *np,
	स्थिर अक्षर *propname, पूर्णांक index);
#अन्यथा
अटल अंतरभूत काष्ठा gen_pool *of_gen_pool_get(काष्ठा device_node *np,
	स्थिर अक्षर *propname, पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __GENALLOC_H__ */
