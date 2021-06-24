<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mempool.h>
#समावेश <linux/slab.h>

#घोषणा SG_MEMPOOL_NR		ARRAY_SIZE(sg_pools)
#घोषणा SG_MEMPOOL_SIZE		2

काष्ठा sg_pool अणु
	माप_प्रकार		size;
	अक्षर		*name;
	काष्ठा kmem_cache	*slab;
	mempool_t	*pool;
पूर्ण;

#घोषणा SP(x) अणु .size = x, "sgpool-" __stringअगरy(x) पूर्ण
#अगर (SG_CHUNK_SIZE < 32)
#त्रुटि SG_CHUNK_SIZE is too small (must be 32 or greater)
#पूर्ण_अगर
अटल काष्ठा sg_pool sg_pools[] = अणु
	SP(8),
	SP(16),
#अगर (SG_CHUNK_SIZE > 32)
	SP(32),
#अगर (SG_CHUNK_SIZE > 64)
	SP(64),
#अगर (SG_CHUNK_SIZE > 128)
	SP(128),
#अगर (SG_CHUNK_SIZE > 256)
#त्रुटि SG_CHUNK_SIZE is too large (256 MAX)
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
	SP(SG_CHUNK_SIZE)
पूर्ण;
#अघोषित SP

अटल अंतरभूत अचिन्हित पूर्णांक sg_pool_index(अचिन्हित लघु nents)
अणु
	अचिन्हित पूर्णांक index;

	BUG_ON(nents > SG_CHUNK_SIZE);

	अगर (nents <= 8)
		index = 0;
	अन्यथा
		index = get_count_order(nents) - 3;

	वापस index;
पूर्ण

अटल व्योम sg_pool_मुक्त(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents)
अणु
	काष्ठा sg_pool *sgp;

	sgp = sg_pools + sg_pool_index(nents);
	mempool_मुक्त(sgl, sgp->pool);
पूर्ण

अटल काष्ठा scatterlist *sg_pool_alloc(अचिन्हित पूर्णांक nents, gfp_t gfp_mask)
अणु
	काष्ठा sg_pool *sgp;

	sgp = sg_pools + sg_pool_index(nents);
	वापस mempool_alloc(sgp->pool, gfp_mask);
पूर्ण

/**
 * sg_मुक्त_table_chained - Free a previously mapped sg table
 * @table:	The sg table header to use
 * @nents_first_chunk: size of the first_chunk SGL passed to
 *		sg_alloc_table_chained
 *
 *  Description:
 *    Free an sg table previously allocated and setup with
 *    sg_alloc_table_chained().
 *
 *    @nents_first_chunk has to be same with that same parameter passed
 *    to sg_alloc_table_chained().
 *
 **/
व्योम sg_मुक्त_table_chained(काष्ठा sg_table *table,
		अचिन्हित nents_first_chunk)
अणु
	अगर (table->orig_nents <= nents_first_chunk)
		वापस;

	अगर (nents_first_chunk == 1)
		nents_first_chunk = 0;

	__sg_मुक्त_table(table, SG_CHUNK_SIZE, nents_first_chunk, sg_pool_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(sg_मुक्त_table_chained);

/**
 * sg_alloc_table_chained - Allocate and chain SGLs in an sg table
 * @table:	The sg table header to use
 * @nents:	Number of entries in sg list
 * @first_chunk: first SGL
 * @nents_first_chunk: number of the SGL of @first_chunk
 *
 *  Description:
 *    Allocate and chain SGLs in an sg table. If @nents@ is larger than
 *    @nents_first_chunk a chained sg table will be setup. @first_chunk is
 *    ignored अगर nents_first_chunk <= 1 because user expects the SGL poपूर्णांकs
 *    non-chain SGL.
 *
 **/
पूर्णांक sg_alloc_table_chained(काष्ठा sg_table *table, पूर्णांक nents,
		काष्ठा scatterlist *first_chunk, अचिन्हित nents_first_chunk)
अणु
	पूर्णांक ret;

	BUG_ON(!nents);

	अगर (first_chunk && nents_first_chunk) अणु
		अगर (nents <= nents_first_chunk) अणु
			table->nents = table->orig_nents = nents;
			sg_init_table(table->sgl, nents);
			वापस 0;
		पूर्ण
	पूर्ण

	/* User supposes that the 1st SGL includes real entry */
	अगर (nents_first_chunk <= 1) अणु
		first_chunk = शून्य;
		nents_first_chunk = 0;
	पूर्ण

	ret = __sg_alloc_table(table, nents, SG_CHUNK_SIZE,
			       first_chunk, nents_first_chunk,
			       GFP_ATOMIC, sg_pool_alloc);
	अगर (unlikely(ret))
		sg_मुक्त_table_chained(table, nents_first_chunk);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sg_alloc_table_chained);

अटल __init पूर्णांक sg_pool_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SG_MEMPOOL_NR; i++) अणु
		काष्ठा sg_pool *sgp = sg_pools + i;
		पूर्णांक size = sgp->size * माप(काष्ठा scatterlist);

		sgp->slab = kmem_cache_create(sgp->name, size, 0,
				SLAB_HWCACHE_ALIGN, शून्य);
		अगर (!sgp->slab) अणु
			prपूर्णांकk(KERN_ERR "SG_POOL: can't init sg slab %s\n",
					sgp->name);
			जाओ cleanup_sdb;
		पूर्ण

		sgp->pool = mempool_create_slab_pool(SG_MEMPOOL_SIZE,
						     sgp->slab);
		अगर (!sgp->pool) अणु
			prपूर्णांकk(KERN_ERR "SG_POOL: can't init sg mempool %s\n",
					sgp->name);
			जाओ cleanup_sdb;
		पूर्ण
	पूर्ण

	वापस 0;

cleanup_sdb:
	क्रम (i = 0; i < SG_MEMPOOL_NR; i++) अणु
		काष्ठा sg_pool *sgp = sg_pools + i;

		mempool_destroy(sgp->pool);
		kmem_cache_destroy(sgp->slab);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल __निकास व्योम sg_pool_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SG_MEMPOOL_NR; i++) अणु
		काष्ठा sg_pool *sgp = sg_pools + i;
		mempool_destroy(sgp->pool);
		kmem_cache_destroy(sgp->slab);
	पूर्ण
पूर्ण

module_init(sg_pool_init);
module_निकास(sg_pool_निकास);
