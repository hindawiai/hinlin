<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अघोषित DEBUG

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/cacheflush.h>

#अगर defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	cache_push(page_to_phys(page), size);
पूर्ण

pgprot_t pgprot_dmacoherent(pgprot_t prot)
अणु
	अगर (CPU_IS_040_OR_060) अणु
		pgprot_val(prot) &= ~_PAGE_CACHE040;
		pgprot_val(prot) |= _PAGE_GLOBAL040 | _PAGE_NOCACHE_S;
	पूर्ण अन्यथा अणु
		pgprot_val(prot) |= _PAGE_NOCACHE030;
	पूर्ण
	वापस prot;
पूर्ण
#अन्यथा

#समावेश <यंत्र/cacheflush.h>

व्योम *arch_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	व्योम *ret;

	अगर (dev == शून्य || (*dev->dma_mask < 0xffffffff))
		gfp |= GFP_DMA;
	ret = (व्योम *)__get_मुक्त_pages(gfp, get_order(size));

	अगर (ret != शून्य) अणु
		स_रखो(ret, 0, size);
		*dma_handle = virt_to_phys(ret);
	पूर्ण
	वापस ret;
पूर्ण

व्योम arch_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)vaddr, get_order(size));
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU && !CONFIG_COLDFIRE */

व्योम arch_sync_dma_क्रम_device(phys_addr_t handle, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
	हाल DMA_TO_DEVICE:
		cache_push(handle, size);
		अवरोध;
	हाल DMA_FROM_DEVICE:
		cache_clear(handle, size);
		अवरोध;
	शेष:
		pr_err_ratelimited("dma_sync_single_for_device: unsupported dir %u\n",
				   dir);
		अवरोध;
	पूर्ण
पूर्ण
