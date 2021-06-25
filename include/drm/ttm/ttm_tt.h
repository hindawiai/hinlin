<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2006-2009 Vmware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
#अगर_अघोषित _TTM_TT_H_
#घोषणा _TTM_TT_H_

#समावेश <linux/types.h>
#समावेश <drm/tपंचांग/tपंचांग_caching.h>

काष्ठा tपंचांग_bo_device;
काष्ठा tपंचांग_tt;
काष्ठा tपंचांग_resource;
काष्ठा tपंचांग_buffer_object;
काष्ठा tपंचांग_operation_ctx;

#घोषणा TTM_PAGE_FLAG_SWAPPED         (1 << 4)
#घोषणा TTM_PAGE_FLAG_ZERO_ALLOC      (1 << 6)
#घोषणा TTM_PAGE_FLAG_SG              (1 << 8)
#घोषणा TTM_PAGE_FLAG_NO_RETRY	      (1 << 9)

#घोषणा TTM_PAGE_FLAG_PRIV_POPULATED  (1 << 31)

/**
 * काष्ठा tपंचांग_tt
 *
 * @pages: Array of pages backing the data.
 * @page_flags: see TTM_PAGE_FLAG_*
 * @num_pages: Number of pages in the page array.
 * @sg: क्रम SG objects via dma-buf
 * @dma_address: The DMA (bus) addresses of the pages
 * @swap_storage: Poपूर्णांकer to shmem काष्ठा file क्रम swap storage.
 * @pages_list: used by some page allocation backend
 * @caching: The current caching state of the pages.
 *
 * This is a काष्ठाure holding the pages, caching- and aperture binding
 * status क्रम a buffer object that isn't backed by fixed (VRAM / AGP)
 * memory.
 */
काष्ठा tपंचांग_tt अणु
	काष्ठा page **pages;
	uपूर्णांक32_t page_flags;
	uपूर्णांक32_t num_pages;
	काष्ठा sg_table *sg;
	dma_addr_t *dma_address;
	काष्ठा file *swap_storage;
	क्रमागत tपंचांग_caching caching;
पूर्ण;

अटल अंतरभूत bool tपंचांग_tt_is_populated(काष्ठा tपंचांग_tt *tt)
अणु
	वापस tt->page_flags & TTM_PAGE_FLAG_PRIV_POPULATED;
पूर्ण

/**
 * tपंचांग_tt_create
 *
 * @bo: poपूर्णांकer to a काष्ठा tपंचांग_buffer_object
 * @zero_alloc: true अगर allocated pages needs to be zeroed
 *
 * Make sure we have a TTM काष्ठाure allocated क्रम the given BO.
 * No pages are actually allocated.
 */
पूर्णांक tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo, bool zero_alloc);

/**
 * tपंचांग_tt_init
 *
 * @tपंचांग: The काष्ठा tपंचांग_tt.
 * @bo: The buffer object we create the tपंचांग क्रम.
 * @page_flags: Page flags as identअगरied by TTM_PAGE_FLAG_XX flags.
 * @caching: the desired caching state of the pages
 *
 * Create a काष्ठा tपंचांग_tt to back data with प्रणाली memory pages.
 * No pages are actually allocated.
 * Returns:
 * शून्य: Out of memory.
 */
पूर्णांक tपंचांग_tt_init(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_buffer_object *bo,
		uपूर्णांक32_t page_flags, क्रमागत tपंचांग_caching caching);
पूर्णांक tपंचांग_sg_tt_init(काष्ठा tपंचांग_tt *tपंचांग_dma, काष्ठा tपंचांग_buffer_object *bo,
		   uपूर्णांक32_t page_flags, क्रमागत tपंचांग_caching caching);

/**
 * tपंचांग_tt_fini
 *
 * @tपंचांग: the tपंचांग_tt काष्ठाure.
 *
 * Free memory of tपंचांग_tt काष्ठाure
 */
व्योम tपंचांग_tt_fini(काष्ठा tपंचांग_tt *tपंचांग);

/**
 * tपंचांग_tपंचांग_destroy:
 *
 * @tपंचांग: The काष्ठा tपंचांग_tt.
 *
 * Unbind, unpopulate and destroy common काष्ठा tपंचांग_tt.
 */
व्योम tपंचांग_tt_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);

/**
 * tपंचांग_tt_destroy_common:
 *
 * Called from driver to destroy common path.
 */
व्योम tपंचांग_tt_destroy_common(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);

/**
 * tपंचांग_tt_swapin:
 *
 * @tपंचांग: The काष्ठा tपंचांग_tt.
 *
 * Swap in a previously swap out tपंचांग_tt.
 */
पूर्णांक tपंचांग_tt_swapin(काष्ठा tपंचांग_tt *tपंचांग);
पूर्णांक tपंचांग_tt_swapout(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग,
		   gfp_t gfp_flags);

/**
 * tपंचांग_tt_populate - allocate pages क्रम a tपंचांग
 *
 * @tपंचांग: Poपूर्णांकer to the tपंचांग_tt काष्ठाure
 *
 * Calls the driver method to allocate pages क्रम a tपंचांग
 */
पूर्णांक tपंचांग_tt_populate(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_operation_ctx *ctx);

/**
 * tपंचांग_tt_unpopulate - मुक्त pages from a tपंचांग
 *
 * @tपंचांग: Poपूर्णांकer to the tपंचांग_tt काष्ठाure
 *
 * Calls the driver method to मुक्त all pages from a tपंचांग
 */
व्योम tपंचांग_tt_unpopulate(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);

व्योम tपंचांग_tt_mgr_init(अचिन्हित दीर्घ num_pages, अचिन्हित दीर्घ num_dma32_pages);

#अगर IS_ENABLED(CONFIG_AGP)
#समावेश <linux/agp_backend.h>

/**
 * tपंचांग_agp_tt_create
 *
 * @bo: Buffer object we allocate the tपंचांग क्रम.
 * @bridge: The agp bridge this device is sitting on.
 * @page_flags: Page flags as identअगरied by TTM_PAGE_FLAG_XX flags.
 *
 *
 * Create a TTM backend that uses the indicated AGP bridge as an aperture
 * क्रम TT memory. This function uses the linux agpgart पूर्णांकerface to
 * bind and unbind memory backing a tपंचांग_tt.
 */
काष्ठा tपंचांग_tt *tपंचांग_agp_tt_create(काष्ठा tपंचांग_buffer_object *bo,
				 काष्ठा agp_bridge_data *bridge,
				 uपूर्णांक32_t page_flags);
पूर्णांक tपंचांग_agp_bind(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *bo_mem);
व्योम tपंचांग_agp_unbind(काष्ठा tपंचांग_tt *tपंचांग);
व्योम tपंचांग_agp_destroy(काष्ठा tपंचांग_tt *tपंचांग);
bool tपंचांग_agp_is_bound(काष्ठा tपंचांग_tt *tपंचांग);
#पूर्ण_अगर

#पूर्ण_अगर
