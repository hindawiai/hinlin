<शैली गुरु>
/*
 * include/linux/dmapool.h
 *
 * Allocation pools क्रम DMAable (coherent) memory.
 *
 * This file is licensed under  the terms of the GNU General Public 
 * License version 2. This program is licensed "as is" without any 
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित LINUX_DMAPOOL_H
#घोषणा	LINUX_DMAPOOL_H

#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/पन.स>

काष्ठा device;

#अगर_घोषित CONFIG_HAS_DMA

काष्ठा dma_pool *dma_pool_create(स्थिर अक्षर *name, काष्ठा device *dev, 
			माप_प्रकार size, माप_प्रकार align, माप_प्रकार allocation);

व्योम dma_pool_destroy(काष्ठा dma_pool *pool);

व्योम *dma_pool_alloc(काष्ठा dma_pool *pool, gfp_t mem_flags,
		     dma_addr_t *handle);
व्योम dma_pool_मुक्त(काष्ठा dma_pool *pool, व्योम *vaddr, dma_addr_t addr);

/*
 * Managed DMA pool
 */
काष्ठा dma_pool *dmam_pool_create(स्थिर अक्षर *name, काष्ठा device *dev,
				  माप_प्रकार size, माप_प्रकार align, माप_प्रकार allocation);
व्योम dmam_pool_destroy(काष्ठा dma_pool *pool);

#अन्यथा /* !CONFIG_HAS_DMA */
अटल अंतरभूत काष्ठा dma_pool *dma_pool_create(स्थिर अक्षर *name,
	काष्ठा device *dev, माप_प्रकार size, माप_प्रकार align, माप_प्रकार allocation)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम dma_pool_destroy(काष्ठा dma_pool *pool) अणु पूर्ण
अटल अंतरभूत व्योम *dma_pool_alloc(काष्ठा dma_pool *pool, gfp_t mem_flags,
				   dma_addr_t *handle) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम dma_pool_मुक्त(काष्ठा dma_pool *pool, व्योम *vaddr,
				 dma_addr_t addr) अणु पूर्ण
अटल अंतरभूत काष्ठा dma_pool *dmam_pool_create(स्थिर अक्षर *name,
	काष्ठा device *dev, माप_प्रकार size, माप_प्रकार align, माप_प्रकार allocation)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम dmam_pool_destroy(काष्ठा dma_pool *pool) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_HAS_DMA */

अटल अंतरभूत व्योम *dma_pool_zalloc(काष्ठा dma_pool *pool, gfp_t mem_flags,
				    dma_addr_t *handle)
अणु
	वापस dma_pool_alloc(pool, mem_flags | __GFP_ZERO, handle);
पूर्ण

#पूर्ण_अगर

