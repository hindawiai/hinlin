<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
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
 *
 * Copyright 2005 (C) Jes Sorensen <jes@trained-monkey.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/rculist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/of_device.h>
#समावेश <linux/vदो_स्मृति.h>

अटल अंतरभूत माप_प्रकार chunk_size(स्थिर काष्ठा gen_pool_chunk *chunk)
अणु
	वापस chunk->end_addr - chunk->start_addr + 1;
पूर्ण

अटल पूर्णांक set_bits_ll(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask_to_set)
अणु
	अचिन्हित दीर्घ val, nval;

	nval = *addr;
	करो अणु
		val = nval;
		अगर (val & mask_to_set)
			वापस -EBUSY;
		cpu_relax();
	पूर्ण जबतक ((nval = cmpxchg(addr, val, val | mask_to_set)) != val);

	वापस 0;
पूर्ण

अटल पूर्णांक clear_bits_ll(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask_to_clear)
अणु
	अचिन्हित दीर्घ val, nval;

	nval = *addr;
	करो अणु
		val = nval;
		अगर ((val & mask_to_clear) != mask_to_clear)
			वापस -EBUSY;
		cpu_relax();
	पूर्ण जबतक ((nval = cmpxchg(addr, val, val & ~mask_to_clear)) != val);

	वापस 0;
पूर्ण

/*
 * biपंचांगap_set_ll - set the specअगरied number of bits at the specअगरied position
 * @map: poपूर्णांकer to a biपंचांगap
 * @start: a bit position in @map
 * @nr: number of bits to set
 *
 * Set @nr bits start from @start in @map lock-lessly. Several users
 * can set/clear the same biपंचांगap simultaneously without lock. If two
 * users set the same bit, one user will वापस reमुख्य bits, otherwise
 * वापस 0.
 */
अटल अचिन्हित दीर्घ
biपंचांगap_set_ll(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ *p = map + BIT_WORD(start);
	स्थिर अचिन्हित दीर्घ size = start + nr;
	पूर्णांक bits_to_set = BITS_PER_LONG - (start % BITS_PER_LONG);
	अचिन्हित दीर्घ mask_to_set = BITMAP_FIRST_WORD_MASK(start);

	जबतक (nr >= bits_to_set) अणु
		अगर (set_bits_ll(p, mask_to_set))
			वापस nr;
		nr -= bits_to_set;
		bits_to_set = BITS_PER_LONG;
		mask_to_set = ~0UL;
		p++;
	पूर्ण
	अगर (nr) अणु
		mask_to_set &= BITMAP_LAST_WORD_MASK(size);
		अगर (set_bits_ll(p, mask_to_set))
			वापस nr;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * biपंचांगap_clear_ll - clear the specअगरied number of bits at the specअगरied position
 * @map: poपूर्णांकer to a biपंचांगap
 * @start: a bit position in @map
 * @nr: number of bits to set
 *
 * Clear @nr bits start from @start in @map lock-lessly. Several users
 * can set/clear the same biपंचांगap simultaneously without lock. If two
 * users clear the same bit, one user will वापस reमुख्य bits,
 * otherwise वापस 0.
 */
अटल अचिन्हित दीर्घ
biपंचांगap_clear_ll(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ *p = map + BIT_WORD(start);
	स्थिर अचिन्हित दीर्घ size = start + nr;
	पूर्णांक bits_to_clear = BITS_PER_LONG - (start % BITS_PER_LONG);
	अचिन्हित दीर्घ mask_to_clear = BITMAP_FIRST_WORD_MASK(start);

	जबतक (nr >= bits_to_clear) अणु
		अगर (clear_bits_ll(p, mask_to_clear))
			वापस nr;
		nr -= bits_to_clear;
		bits_to_clear = BITS_PER_LONG;
		mask_to_clear = ~0UL;
		p++;
	पूर्ण
	अगर (nr) अणु
		mask_to_clear &= BITMAP_LAST_WORD_MASK(size);
		अगर (clear_bits_ll(p, mask_to_clear))
			वापस nr;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * gen_pool_create - create a new special memory pool
 * @min_alloc_order: log base 2 of number of bytes each biपंचांगap bit represents
 * @nid: node id of the node the pool काष्ठाure should be allocated on, or -1
 *
 * Create a new special memory pool that can be used to manage special purpose
 * memory not managed by the regular kदो_स्मृति/kमुक्त पूर्णांकerface.
 */
काष्ठा gen_pool *gen_pool_create(पूर्णांक min_alloc_order, पूर्णांक nid)
अणु
	काष्ठा gen_pool *pool;

	pool = kदो_स्मृति_node(माप(काष्ठा gen_pool), GFP_KERNEL, nid);
	अगर (pool != शून्य) अणु
		spin_lock_init(&pool->lock);
		INIT_LIST_HEAD(&pool->chunks);
		pool->min_alloc_order = min_alloc_order;
		pool->algo = gen_pool_first_fit;
		pool->data = शून्य;
		pool->name = शून्य;
	पूर्ण
	वापस pool;
पूर्ण
EXPORT_SYMBOL(gen_pool_create);

/**
 * gen_pool_add_owner- add a new chunk of special memory to the pool
 * @pool: pool to add new memory chunk to
 * @virt: भव starting address of memory chunk to add to pool
 * @phys: physical starting address of memory chunk to add to pool
 * @size: size in bytes of the memory chunk to add to pool
 * @nid: node id of the node the chunk काष्ठाure and biपंचांगap should be
 *       allocated on, or -1
 * @owner: निजी data the publisher would like to recall at alloc समय
 *
 * Add a new chunk of special memory to the specअगरied pool.
 *
 * Returns 0 on success or a -ve त्रुटि_सं on failure.
 */
पूर्णांक gen_pool_add_owner(काष्ठा gen_pool *pool, अचिन्हित दीर्घ virt, phys_addr_t phys,
		 माप_प्रकार size, पूर्णांक nid, व्योम *owner)
अणु
	काष्ठा gen_pool_chunk *chunk;
	अचिन्हित दीर्घ nbits = size >> pool->min_alloc_order;
	अचिन्हित दीर्घ nbytes = माप(काष्ठा gen_pool_chunk) +
				BITS_TO_LONGS(nbits) * माप(दीर्घ);

	chunk = vzalloc_node(nbytes, nid);
	अगर (unlikely(chunk == शून्य))
		वापस -ENOMEM;

	chunk->phys_addr = phys;
	chunk->start_addr = virt;
	chunk->end_addr = virt + size - 1;
	chunk->owner = owner;
	atomic_दीर्घ_set(&chunk->avail, size);

	spin_lock(&pool->lock);
	list_add_rcu(&chunk->next_chunk, &pool->chunks);
	spin_unlock(&pool->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(gen_pool_add_owner);

/**
 * gen_pool_virt_to_phys - वापस the physical address of memory
 * @pool: pool to allocate from
 * @addr: starting address of memory
 *
 * Returns the physical address on success, or -1 on error.
 */
phys_addr_t gen_pool_virt_to_phys(काष्ठा gen_pool *pool, अचिन्हित दीर्घ addr)
अणु
	काष्ठा gen_pool_chunk *chunk;
	phys_addr_t paddr = -1;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &pool->chunks, next_chunk) अणु
		अगर (addr >= chunk->start_addr && addr <= chunk->end_addr) अणु
			paddr = chunk->phys_addr + (addr - chunk->start_addr);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस paddr;
पूर्ण
EXPORT_SYMBOL(gen_pool_virt_to_phys);

/**
 * gen_pool_destroy - destroy a special memory pool
 * @pool: pool to destroy
 *
 * Destroy the specअगरied special memory pool. Verअगरies that there are no
 * outstanding allocations.
 */
व्योम gen_pool_destroy(काष्ठा gen_pool *pool)
अणु
	काष्ठा list_head *_chunk, *_next_chunk;
	काष्ठा gen_pool_chunk *chunk;
	पूर्णांक order = pool->min_alloc_order;
	अचिन्हित दीर्घ bit, end_bit;

	list_क्रम_each_safe(_chunk, _next_chunk, &pool->chunks) अणु
		chunk = list_entry(_chunk, काष्ठा gen_pool_chunk, next_chunk);
		list_del(&chunk->next_chunk);

		end_bit = chunk_size(chunk) >> order;
		bit = find_next_bit(chunk->bits, end_bit, 0);
		BUG_ON(bit < end_bit);

		vमुक्त(chunk);
	पूर्ण
	kमुक्त_स्थिर(pool->name);
	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL(gen_pool_destroy);

/**
 * gen_pool_alloc_algo_owner - allocate special memory from the pool
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @algo: algorithm passed from caller
 * @data: data passed to algorithm
 * @owner: optionally retrieve the chunk owner
 *
 * Allocate the requested number of bytes from the specअगरied pool.
 * Uses the pool allocation function (with first-fit algorithm by शेष).
 * Can not be used in NMI handler on architectures without
 * NMI-safe cmpxchg implementation.
 */
अचिन्हित दीर्घ gen_pool_alloc_algo_owner(काष्ठा gen_pool *pool, माप_प्रकार size,
		genpool_algo_t algo, व्योम *data, व्योम **owner)
अणु
	काष्ठा gen_pool_chunk *chunk;
	अचिन्हित दीर्घ addr = 0;
	पूर्णांक order = pool->min_alloc_order;
	अचिन्हित दीर्घ nbits, start_bit, end_bit, reमुख्य;

#अगर_अघोषित CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG
	BUG_ON(in_nmi());
#पूर्ण_अगर

	अगर (owner)
		*owner = शून्य;

	अगर (size == 0)
		वापस 0;

	nbits = (size + (1UL << order) - 1) >> order;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &pool->chunks, next_chunk) अणु
		अगर (size > atomic_दीर्घ_पढ़ो(&chunk->avail))
			जारी;

		start_bit = 0;
		end_bit = chunk_size(chunk) >> order;
retry:
		start_bit = algo(chunk->bits, end_bit, start_bit,
				 nbits, data, pool, chunk->start_addr);
		अगर (start_bit >= end_bit)
			जारी;
		reमुख्य = biपंचांगap_set_ll(chunk->bits, start_bit, nbits);
		अगर (reमुख्य) अणु
			reमुख्य = biपंचांगap_clear_ll(chunk->bits, start_bit,
						 nbits - reमुख्य);
			BUG_ON(reमुख्य);
			जाओ retry;
		पूर्ण

		addr = chunk->start_addr + ((अचिन्हित दीर्घ)start_bit << order);
		size = nbits << order;
		atomic_दीर्घ_sub(size, &chunk->avail);
		अगर (owner)
			*owner = chunk->owner;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस addr;
पूर्ण
EXPORT_SYMBOL(gen_pool_alloc_algo_owner);

/**
 * gen_pool_dma_alloc - allocate special memory from the pool क्रम DMA usage
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @dma: dma-view physical address वापस value.  Use %शून्य अगर unneeded.
 *
 * Allocate the requested number of bytes from the specअगरied pool.
 * Uses the pool allocation function (with first-fit algorithm by शेष).
 * Can not be used in NMI handler on architectures without
 * NMI-safe cmpxchg implementation.
 *
 * Return: भव address of the allocated memory, or %शून्य on failure
 */
व्योम *gen_pool_dma_alloc(काष्ठा gen_pool *pool, माप_प्रकार size, dma_addr_t *dma)
अणु
	वापस gen_pool_dma_alloc_algo(pool, size, dma, pool->algo, pool->data);
पूर्ण
EXPORT_SYMBOL(gen_pool_dma_alloc);

/**
 * gen_pool_dma_alloc_algo - allocate special memory from the pool क्रम DMA
 * usage with the given pool algorithm
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @dma: DMA-view physical address वापस value. Use %शून्य अगर unneeded.
 * @algo: algorithm passed from caller
 * @data: data passed to algorithm
 *
 * Allocate the requested number of bytes from the specअगरied pool. Uses the
 * given pool allocation function. Can not be used in NMI handler on
 * architectures without NMI-safe cmpxchg implementation.
 *
 * Return: भव address of the allocated memory, or %शून्य on failure
 */
व्योम *gen_pool_dma_alloc_algo(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, genpool_algo_t algo, व्योम *data)
अणु
	अचिन्हित दीर्घ vaddr;

	अगर (!pool)
		वापस शून्य;

	vaddr = gen_pool_alloc_algo(pool, size, algo, data);
	अगर (!vaddr)
		वापस शून्य;

	अगर (dma)
		*dma = gen_pool_virt_to_phys(pool, vaddr);

	वापस (व्योम *)vaddr;
पूर्ण
EXPORT_SYMBOL(gen_pool_dma_alloc_algo);

/**
 * gen_pool_dma_alloc_align - allocate special memory from the pool क्रम DMA
 * usage with the given alignment
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @dma: DMA-view physical address वापस value. Use %शून्य अगर unneeded.
 * @align: alignment in bytes क्रम starting address
 *
 * Allocate the requested number bytes from the specअगरied pool, with the given
 * alignment restriction. Can not be used in NMI handler on architectures
 * without NMI-safe cmpxchg implementation.
 *
 * Return: भव address of the allocated memory, or %शून्य on failure
 */
व्योम *gen_pool_dma_alloc_align(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, पूर्णांक align)
अणु
	काष्ठा genpool_data_align data = अणु .align = align पूर्ण;

	वापस gen_pool_dma_alloc_algo(pool, size, dma,
			gen_pool_first_fit_align, &data);
पूर्ण
EXPORT_SYMBOL(gen_pool_dma_alloc_align);

/**
 * gen_pool_dma_zalloc - allocate special zeroed memory from the pool क्रम
 * DMA usage
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @dma: dma-view physical address वापस value.  Use %शून्य अगर unneeded.
 *
 * Allocate the requested number of zeroed bytes from the specअगरied pool.
 * Uses the pool allocation function (with first-fit algorithm by शेष).
 * Can not be used in NMI handler on architectures without
 * NMI-safe cmpxchg implementation.
 *
 * Return: भव address of the allocated zeroed memory, or %शून्य on failure
 */
व्योम *gen_pool_dma_zalloc(काष्ठा gen_pool *pool, माप_प्रकार size, dma_addr_t *dma)
अणु
	वापस gen_pool_dma_zalloc_algo(pool, size, dma, pool->algo, pool->data);
पूर्ण
EXPORT_SYMBOL(gen_pool_dma_zalloc);

/**
 * gen_pool_dma_zalloc_algo - allocate special zeroed memory from the pool क्रम
 * DMA usage with the given pool algorithm
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @dma: DMA-view physical address वापस value. Use %शून्य अगर unneeded.
 * @algo: algorithm passed from caller
 * @data: data passed to algorithm
 *
 * Allocate the requested number of zeroed bytes from the specअगरied pool. Uses
 * the given pool allocation function. Can not be used in NMI handler on
 * architectures without NMI-safe cmpxchg implementation.
 *
 * Return: भव address of the allocated zeroed memory, or %शून्य on failure
 */
व्योम *gen_pool_dma_zalloc_algo(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, genpool_algo_t algo, व्योम *data)
अणु
	व्योम *vaddr = gen_pool_dma_alloc_algo(pool, size, dma, algo, data);

	अगर (vaddr)
		स_रखो(vaddr, 0, size);

	वापस vaddr;
पूर्ण
EXPORT_SYMBOL(gen_pool_dma_zalloc_algo);

/**
 * gen_pool_dma_zalloc_align - allocate special zeroed memory from the pool क्रम
 * DMA usage with the given alignment
 * @pool: pool to allocate from
 * @size: number of bytes to allocate from the pool
 * @dma: DMA-view physical address वापस value. Use %शून्य अगर unneeded.
 * @align: alignment in bytes क्रम starting address
 *
 * Allocate the requested number of zeroed bytes from the specअगरied pool,
 * with the given alignment restriction. Can not be used in NMI handler on
 * architectures without NMI-safe cmpxchg implementation.
 *
 * Return: भव address of the allocated zeroed memory, or %शून्य on failure
 */
व्योम *gen_pool_dma_zalloc_align(काष्ठा gen_pool *pool, माप_प्रकार size,
		dma_addr_t *dma, पूर्णांक align)
अणु
	काष्ठा genpool_data_align data = अणु .align = align पूर्ण;

	वापस gen_pool_dma_zalloc_algo(pool, size, dma,
			gen_pool_first_fit_align, &data);
पूर्ण
EXPORT_SYMBOL(gen_pool_dma_zalloc_align);

/**
 * gen_pool_मुक्त_owner - मुक्त allocated special memory back to the pool
 * @pool: pool to मुक्त to
 * @addr: starting address of memory to मुक्त back to pool
 * @size: size in bytes of memory to मुक्त
 * @owner: निजी data stashed at gen_pool_add() समय
 *
 * Free previously allocated special memory back to the specअगरied
 * pool.  Can not be used in NMI handler on architectures without
 * NMI-safe cmpxchg implementation.
 */
व्योम gen_pool_मुक्त_owner(काष्ठा gen_pool *pool, अचिन्हित दीर्घ addr, माप_प्रकार size,
		व्योम **owner)
अणु
	काष्ठा gen_pool_chunk *chunk;
	पूर्णांक order = pool->min_alloc_order;
	अचिन्हित दीर्घ start_bit, nbits, reमुख्य;

#अगर_अघोषित CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG
	BUG_ON(in_nmi());
#पूर्ण_अगर

	अगर (owner)
		*owner = शून्य;

	nbits = (size + (1UL << order) - 1) >> order;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &pool->chunks, next_chunk) अणु
		अगर (addr >= chunk->start_addr && addr <= chunk->end_addr) अणु
			BUG_ON(addr + size - 1 > chunk->end_addr);
			start_bit = (addr - chunk->start_addr) >> order;
			reमुख्य = biपंचांगap_clear_ll(chunk->bits, start_bit, nbits);
			BUG_ON(reमुख्य);
			size = nbits << order;
			atomic_दीर्घ_add(size, &chunk->avail);
			अगर (owner)
				*owner = chunk->owner;
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	BUG();
पूर्ण
EXPORT_SYMBOL(gen_pool_मुक्त_owner);

/**
 * gen_pool_क्रम_each_chunk - call func क्रम every chunk of generic memory pool
 * @pool:	the generic memory pool
 * @func:	func to call
 * @data:	additional data used by @func
 *
 * Call @func क्रम every chunk of generic memory pool.  The @func is
 * called with rcu_पढ़ो_lock held.
 */
व्योम gen_pool_क्रम_each_chunk(काष्ठा gen_pool *pool,
	व्योम (*func)(काष्ठा gen_pool *pool, काष्ठा gen_pool_chunk *chunk, व्योम *data),
	व्योम *data)
अणु
	काष्ठा gen_pool_chunk *chunk;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &(pool)->chunks, next_chunk)
		func(pool, chunk, data);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(gen_pool_क्रम_each_chunk);

/**
 * gen_pool_has_addr - checks अगर an address falls within the range of a pool
 * @pool:	the generic memory pool
 * @start:	start address
 * @size:	size of the region
 *
 * Check अगर the range of addresses falls within the specअगरied pool. Returns
 * true अगर the entire range is contained in the pool and false otherwise.
 */
bool gen_pool_has_addr(काष्ठा gen_pool *pool, अचिन्हित दीर्घ start,
			माप_प्रकार size)
अणु
	bool found = false;
	अचिन्हित दीर्घ end = start + size - 1;
	काष्ठा gen_pool_chunk *chunk;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &(pool)->chunks, next_chunk) अणु
		अगर (start >= chunk->start_addr && start <= chunk->end_addr) अणु
			अगर (end <= chunk->end_addr) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस found;
पूर्ण
EXPORT_SYMBOL(gen_pool_has_addr);

/**
 * gen_pool_avail - get available मुक्त space of the pool
 * @pool: pool to get available मुक्त space
 *
 * Return available मुक्त space of the specअगरied pool.
 */
माप_प्रकार gen_pool_avail(काष्ठा gen_pool *pool)
अणु
	काष्ठा gen_pool_chunk *chunk;
	माप_प्रकार avail = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &pool->chunks, next_chunk)
		avail += atomic_दीर्घ_पढ़ो(&chunk->avail);
	rcu_पढ़ो_unlock();
	वापस avail;
पूर्ण
EXPORT_SYMBOL_GPL(gen_pool_avail);

/**
 * gen_pool_size - get size in bytes of memory managed by the pool
 * @pool: pool to get size
 *
 * Return size in bytes of memory managed by the pool.
 */
माप_प्रकार gen_pool_size(काष्ठा gen_pool *pool)
अणु
	काष्ठा gen_pool_chunk *chunk;
	माप_प्रकार size = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(chunk, &pool->chunks, next_chunk)
		size += chunk_size(chunk);
	rcu_पढ़ो_unlock();
	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(gen_pool_size);

/**
 * gen_pool_set_algo - set the allocation algorithm
 * @pool: pool to change allocation algorithm
 * @algo: custom algorithm function
 * @data: additional data used by @algo
 *
 * Call @algo क्रम each memory allocation in the pool.
 * If @algo is शून्य use gen_pool_first_fit as शेष
 * memory allocation function.
 */
व्योम gen_pool_set_algo(काष्ठा gen_pool *pool, genpool_algo_t algo, व्योम *data)
अणु
	rcu_पढ़ो_lock();

	pool->algo = algo;
	अगर (!pool->algo)
		pool->algo = gen_pool_first_fit;

	pool->data = data;

	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(gen_pool_set_algo);

/**
 * gen_pool_first_fit - find the first available region
 * of memory matching the size requirement (no alignment स्थिरraपूर्णांक)
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @data: additional data - unused
 * @pool: pool to find the fit region memory from
 * @start_addr: not used in this function
 */
अचिन्हित दीर्घ gen_pool_first_fit(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr, व्योम *data,
		काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr)
अणु
	वापस biपंचांगap_find_next_zero_area(map, size, start, nr, 0);
पूर्ण
EXPORT_SYMBOL(gen_pool_first_fit);

/**
 * gen_pool_first_fit_align - find the first available region
 * of memory matching the size requirement (alignment स्थिरraपूर्णांक)
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @data: data क्रम alignment
 * @pool: pool to get order from
 * @start_addr: start addr of alloction chunk
 */
अचिन्हित दीर्घ gen_pool_first_fit_align(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr, व्योम *data,
		काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr)
अणु
	काष्ठा genpool_data_align *alignment;
	अचिन्हित दीर्घ align_mask, align_off;
	पूर्णांक order;

	alignment = data;
	order = pool->min_alloc_order;
	align_mask = ((alignment->align + (1UL << order) - 1) >> order) - 1;
	align_off = (start_addr & (alignment->align - 1)) >> order;

	वापस biपंचांगap_find_next_zero_area_off(map, size, start, nr,
					      align_mask, align_off);
पूर्ण
EXPORT_SYMBOL(gen_pool_first_fit_align);

/**
 * gen_pool_fixed_alloc - reserve a specअगरic region
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @data: data क्रम alignment
 * @pool: pool to get order from
 * @start_addr: not used in this function
 */
अचिन्हित दीर्घ gen_pool_fixed_alloc(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr, व्योम *data,
		काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr)
अणु
	काष्ठा genpool_data_fixed *fixed_data;
	पूर्णांक order;
	अचिन्हित दीर्घ offset_bit;
	अचिन्हित दीर्घ start_bit;

	fixed_data = data;
	order = pool->min_alloc_order;
	offset_bit = fixed_data->offset >> order;
	अगर (WARN_ON(fixed_data->offset & ((1UL << order) - 1)))
		वापस size;

	start_bit = biपंचांगap_find_next_zero_area(map, size,
			start + offset_bit, nr, 0);
	अगर (start_bit != offset_bit)
		start_bit = size;
	वापस start_bit;
पूर्ण
EXPORT_SYMBOL(gen_pool_fixed_alloc);

/**
 * gen_pool_first_fit_order_align - find the first available region
 * of memory matching the size requirement. The region will be aligned
 * to the order of the size specअगरied.
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @data: additional data - unused
 * @pool: pool to find the fit region memory from
 * @start_addr: not used in this function
 */
अचिन्हित दीर्घ gen_pool_first_fit_order_align(अचिन्हित दीर्घ *map,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ start,
		अचिन्हित पूर्णांक nr, व्योम *data, काष्ठा gen_pool *pool,
		अचिन्हित दीर्घ start_addr)
अणु
	अचिन्हित दीर्घ align_mask = roundup_घात_of_two(nr) - 1;

	वापस biपंचांगap_find_next_zero_area(map, size, start, nr, align_mask);
पूर्ण
EXPORT_SYMBOL(gen_pool_first_fit_order_align);

/**
 * gen_pool_best_fit - find the best fitting region of memory
 * matching the size requirement (no alignment स्थिरraपूर्णांक)
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @data: additional data - unused
 * @pool: pool to find the fit region memory from
 * @start_addr: not used in this function
 *
 * Iterate over the biपंचांगap to find the smallest मुक्त region
 * which we can allocate the memory.
 */
अचिन्हित दीर्घ gen_pool_best_fit(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr, व्योम *data,
		काष्ठा gen_pool *pool, अचिन्हित दीर्घ start_addr)
अणु
	अचिन्हित दीर्घ start_bit = size;
	अचिन्हित दीर्घ len = size + 1;
	अचिन्हित दीर्घ index;

	index = biपंचांगap_find_next_zero_area(map, size, start, nr, 0);

	जबतक (index < size) अणु
		अचिन्हित दीर्घ next_bit = find_next_bit(map, size, index + nr);
		अगर ((next_bit - index) < len) अणु
			len = next_bit - index;
			start_bit = index;
			अगर (len == nr)
				वापस start_bit;
		पूर्ण
		index = biपंचांगap_find_next_zero_area(map, size,
						   next_bit + 1, nr, 0);
	पूर्ण

	वापस start_bit;
पूर्ण
EXPORT_SYMBOL(gen_pool_best_fit);

अटल व्योम devm_gen_pool_release(काष्ठा device *dev, व्योम *res)
अणु
	gen_pool_destroy(*(काष्ठा gen_pool **)res);
पूर्ण

अटल पूर्णांक devm_gen_pool_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा gen_pool **p = res;

	/* शून्य data matches only a pool without an asचिन्हित name */
	अगर (!data && !(*p)->name)
		वापस 1;

	अगर (!data || !(*p)->name)
		वापस 0;

	वापस !म_भेद((*p)->name, data);
पूर्ण

/**
 * gen_pool_get - Obtain the gen_pool (अगर any) क्रम a device
 * @dev: device to retrieve the gen_pool from
 * @name: name of a gen_pool or शून्य, identअगरies a particular gen_pool on device
 *
 * Returns the gen_pool क्रम the device अगर one is present, or शून्य.
 */
काष्ठा gen_pool *gen_pool_get(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा gen_pool **p;

	p = devres_find(dev, devm_gen_pool_release, devm_gen_pool_match,
			(व्योम *)name);
	अगर (!p)
		वापस शून्य;
	वापस *p;
पूर्ण
EXPORT_SYMBOL_GPL(gen_pool_get);

/**
 * devm_gen_pool_create - managed gen_pool_create
 * @dev: device that provides the gen_pool
 * @min_alloc_order: log base 2 of number of bytes each biपंचांगap bit represents
 * @nid: node selector क्रम allocated gen_pool, %NUMA_NO_NODE क्रम all nodes
 * @name: name of a gen_pool or शून्य, identअगरies a particular gen_pool on device
 *
 * Create a new special memory pool that can be used to manage special purpose
 * memory not managed by the regular kदो_स्मृति/kमुक्त पूर्णांकerface. The pool will be
 * स्वतःmatically destroyed by the device management code.
 */
काष्ठा gen_pool *devm_gen_pool_create(काष्ठा device *dev, पूर्णांक min_alloc_order,
				      पूर्णांक nid, स्थिर अक्षर *name)
अणु
	काष्ठा gen_pool **ptr, *pool;
	स्थिर अक्षर *pool_name = शून्य;

	/* Check that genpool to be created is uniquely addressed on device */
	अगर (gen_pool_get(dev, name))
		वापस ERR_PTR(-EINVAL);

	अगर (name) अणु
		pool_name = kstrdup_स्थिर(name, GFP_KERNEL);
		अगर (!pool_name)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ptr = devres_alloc(devm_gen_pool_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		जाओ मुक्त_pool_name;

	pool = gen_pool_create(min_alloc_order, nid);
	अगर (!pool)
		जाओ मुक्त_devres;

	*ptr = pool;
	pool->name = pool_name;
	devres_add(dev, ptr);

	वापस pool;

मुक्त_devres:
	devres_मुक्त(ptr);
मुक्त_pool_name:
	kमुक्त_स्थिर(pool_name);

	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL(devm_gen_pool_create);

#अगर_घोषित CONFIG_OF
/**
 * of_gen_pool_get - find a pool by phandle property
 * @np: device node
 * @propname: property name containing phandle(s)
 * @index: index पूर्णांकo the phandle array
 *
 * Returns the pool that contains the chunk starting at the physical
 * address of the device tree node poपूर्णांकed at by the phandle property,
 * or शून्य अगर not found.
 */
काष्ठा gen_pool *of_gen_pool_get(काष्ठा device_node *np,
	स्थिर अक्षर *propname, पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np_pool, *parent;
	स्थिर अक्षर *name = शून्य;
	काष्ठा gen_pool *pool = शून्य;

	np_pool = of_parse_phandle(np, propname, index);
	अगर (!np_pool)
		वापस शून्य;

	pdev = of_find_device_by_node(np_pool);
	अगर (!pdev) अणु
		/* Check अगर named gen_pool is created by parent node device */
		parent = of_get_parent(np_pool);
		pdev = of_find_device_by_node(parent);
		of_node_put(parent);

		of_property_पढ़ो_string(np_pool, "label", &name);
		अगर (!name)
			name = np_pool->name;
	पूर्ण
	अगर (pdev)
		pool = gen_pool_get(&pdev->dev, name);
	of_node_put(np_pool);

	वापस pool;
पूर्ण
EXPORT_SYMBOL_GPL(of_gen_pool_get);
#पूर्ण_अगर /* CONFIG_OF */
