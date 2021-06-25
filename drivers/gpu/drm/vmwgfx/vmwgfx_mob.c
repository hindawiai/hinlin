<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2012-2015 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <linux/highस्मृति.स>

#समावेश "vmwgfx_drv.h"

/*
 * If we set up the screen target otable, screen objects stop working.
 */

#घोषणा VMW_OTABLE_SETUP_SUB ((VMWGFX_ENABLE_SCREEN_TARGET_OTABLE ? 0 : 1))

#अगर_घोषित CONFIG_64BIT
#घोषणा VMW_PPN_SIZE 8
#घोषणा VMW_MOBFMT_PTDEPTH_0 SVGA3D_MOBFMT_PTDEPTH64_0
#घोषणा VMW_MOBFMT_PTDEPTH_1 SVGA3D_MOBFMT_PTDEPTH64_1
#घोषणा VMW_MOBFMT_PTDEPTH_2 SVGA3D_MOBFMT_PTDEPTH64_2
#अन्यथा
#घोषणा VMW_PPN_SIZE 4
#घोषणा VMW_MOBFMT_PTDEPTH_0 SVGA3D_MOBFMT_PTDEPTH_0
#घोषणा VMW_MOBFMT_PTDEPTH_1 SVGA3D_MOBFMT_PTDEPTH_1
#घोषणा VMW_MOBFMT_PTDEPTH_2 SVGA3D_MOBFMT_PTDEPTH_2
#पूर्ण_अगर

/*
 * काष्ठा vmw_mob - Structure containing page table and metadata क्रम a
 * Guest Memory OBject.
 *
 * @num_pages       Number of pages that make up the page table.
 * @pt_level        The indirection level of the page table. 0-2.
 * @pt_root_page    DMA address of the level 0 page of the page table.
 */
काष्ठा vmw_mob अणु
	काष्ठा tपंचांग_buffer_object *pt_bo;
	अचिन्हित दीर्घ num_pages;
	अचिन्हित pt_level;
	dma_addr_t pt_root_page;
	uपूर्णांक32_t id;
पूर्ण;

/*
 * काष्ठा vmw_otable - Guest Memory OBject table metadata
 *
 * @size:           Size of the table (page-aligned).
 * @page_table:     Poपूर्णांकer to a काष्ठा vmw_mob holding the page table.
 */
अटल स्थिर काष्ठा vmw_otable pre_dx_tables[] = अणु
	अणुVMWGFX_NUM_MOB * SVGA3D_OTABLE_MOB_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_SURFACE * SVGA3D_OTABLE_SURFACE_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_CONTEXT * SVGA3D_OTABLE_CONTEXT_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_SHADER * SVGA3D_OTABLE_SHADER_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_SCREEN_TARGET * SVGA3D_OTABLE_SCREEN_TARGET_ENTRY_SIZE,
	 शून्य, VMWGFX_ENABLE_SCREEN_TARGET_OTABLEपूर्ण
पूर्ण;

अटल स्थिर काष्ठा vmw_otable dx_tables[] = अणु
	अणुVMWGFX_NUM_MOB * SVGA3D_OTABLE_MOB_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_SURFACE * SVGA3D_OTABLE_SURFACE_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_CONTEXT * SVGA3D_OTABLE_CONTEXT_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_SHADER * SVGA3D_OTABLE_SHADER_ENTRY_SIZE, शून्य, trueपूर्ण,
	अणुVMWGFX_NUM_GB_SCREEN_TARGET * SVGA3D_OTABLE_SCREEN_TARGET_ENTRY_SIZE,
	 शून्य, VMWGFX_ENABLE_SCREEN_TARGET_OTABLEपूर्ण,
	अणुVMWGFX_NUM_DXCONTEXT * माप(SVGAOTableDXContextEntry), शून्य, trueपूर्ण,
पूर्ण;

अटल पूर्णांक vmw_mob_pt_populate(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_mob *mob);
अटल व्योम vmw_mob_pt_setup(काष्ठा vmw_mob *mob,
			     काष्ठा vmw_piter data_iter,
			     अचिन्हित दीर्घ num_data_pages);


अटल अंतरभूत व्योम vmw_bo_unpin_unlocked(काष्ठा tपंचांग_buffer_object *bo)
अणु
	पूर्णांक ret = tपंचांग_bo_reserve(bo, false, true, शून्य);
	BUG_ON(ret != 0);
	tपंचांग_bo_unpin(bo);
	tपंचांग_bo_unreserve(bo);
पूर्ण


/*
 * vmw_setup_otable_base - Issue an object table base setup command to
 * the device
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठाure
 * @type:           Type of object table base
 * @offset          Start of table offset पूर्णांकo dev_priv::otable_bo
 * @otable          Poपूर्णांकer to otable metadata;
 *
 * This function वापसs -ENOMEM अगर it fails to reserve fअगरo space,
 * and may block रुकोing क्रम fअगरo space.
 */
अटल पूर्णांक vmw_setup_otable_base(काष्ठा vmw_निजी *dev_priv,
				 SVGAOTableType type,
				 काष्ठा tपंचांग_buffer_object *otable_bo,
				 अचिन्हित दीर्घ offset,
				 काष्ठा vmw_otable *otable)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdSetOTableBase64 body;
	पूर्ण *cmd;
	काष्ठा vmw_mob *mob;
	स्थिर काष्ठा vmw_sg_table *vsgt;
	काष्ठा vmw_piter iter;
	पूर्णांक ret;

	BUG_ON(otable->page_table != शून्य);

	vsgt = vmw_bo_sg_table(otable_bo);
	vmw_piter_start(&iter, vsgt, offset >> PAGE_SHIFT);
	WARN_ON(!vmw_piter_next(&iter));

	mob = vmw_mob_create(otable->size >> PAGE_SHIFT);
	अगर (unlikely(mob == शून्य)) अणु
		DRM_ERROR("Failed creating OTable page table.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (otable->size <= PAGE_SIZE) अणु
		mob->pt_level = VMW_MOBFMT_PTDEPTH_0;
		mob->pt_root_page = vmw_piter_dma_addr(&iter);
	पूर्ण अन्यथा अगर (vsgt->num_regions == 1) अणु
		mob->pt_level = SVGA3D_MOBFMT_RANGE;
		mob->pt_root_page = vmw_piter_dma_addr(&iter);
	पूर्ण अन्यथा अणु
		ret = vmw_mob_pt_populate(dev_priv, mob);
		अगर (unlikely(ret != 0))
			जाओ out_no_populate;

		vmw_mob_pt_setup(mob, iter, otable->size >> PAGE_SHIFT);
		mob->pt_level += VMW_MOBFMT_PTDEPTH_1 - SVGA3D_MOBFMT_PTDEPTH_1;
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य)) अणु
		ret = -ENOMEM;
		जाओ out_no_fअगरo;
	पूर्ण

	स_रखो(cmd, 0, माप(*cmd));
	cmd->header.id = SVGA_3D_CMD_SET_OTABLE_BASE64;
	cmd->header.size = माप(cmd->body);
	cmd->body.type = type;
	cmd->body.baseAddress = mob->pt_root_page >> PAGE_SHIFT;
	cmd->body.sizeInBytes = otable->size;
	cmd->body.validSizeInBytes = 0;
	cmd->body.ptDepth = mob->pt_level;

	/*
	 * The device करोesn't support this, But the otable size is
	 * determined at compile-समय, so this BUG shouldn't trigger
	 * अक्रमomly.
	 */
	BUG_ON(mob->pt_level == VMW_MOBFMT_PTDEPTH_2);

	vmw_cmd_commit(dev_priv, माप(*cmd));
	otable->page_table = mob;

	वापस 0;

out_no_fअगरo:
out_no_populate:
	vmw_mob_destroy(mob);
	वापस ret;
पूर्ण

/*
 * vmw_takeकरोwn_otable_base - Issue an object table base takeकरोwn command
 * to the device
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठाure
 * @type:           Type of object table base
 *
 */
अटल व्योम vmw_takeकरोwn_otable_base(काष्ठा vmw_निजी *dev_priv,
				     SVGAOTableType type,
				     काष्ठा vmw_otable *otable)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdSetOTableBase body;
	पूर्ण *cmd;
	काष्ठा tपंचांग_buffer_object *bo;

	अगर (otable->page_table == शून्य)
		वापस;

	bo = otable->page_table->pt_bo;
	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->header.id = SVGA_3D_CMD_SET_OTABLE_BASE;
	cmd->header.size = माप(cmd->body);
	cmd->body.type = type;
	cmd->body.baseAddress = 0;
	cmd->body.sizeInBytes = 0;
	cmd->body.validSizeInBytes = 0;
	cmd->body.ptDepth = SVGA3D_MOBFMT_INVALID;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	अगर (bo) अणु
		पूर्णांक ret;

		ret = tपंचांग_bo_reserve(bo, false, true, शून्य);
		BUG_ON(ret != 0);

		vmw_bo_fence_single(bo, शून्य);
		tपंचांग_bo_unreserve(bo);
	पूर्ण

	vmw_mob_destroy(otable->page_table);
	otable->page_table = शून्य;
पूर्ण


अटल पूर्णांक vmw_otable_batch_setup(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_otable_batch *batch)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ bo_size;
	काष्ठा vmw_otable *otables = batch->otables;
	SVGAOTableType i;
	पूर्णांक ret;

	bo_size = 0;
	क्रम (i = 0; i < batch->num_otables; ++i) अणु
		अगर (!otables[i].enabled)
			जारी;

		otables[i].size =
			(otables[i].size + PAGE_SIZE - 1) & PAGE_MASK;
		bo_size += otables[i].size;
	पूर्ण

	ret = vmw_bo_create_and_populate(dev_priv, bo_size, &batch->otable_bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	offset = 0;
	क्रम (i = 0; i < batch->num_otables; ++i) अणु
		अगर (!batch->otables[i].enabled)
			जारी;

		ret = vmw_setup_otable_base(dev_priv, i, batch->otable_bo,
					    offset,
					    &otables[i]);
		अगर (unlikely(ret != 0))
			जाओ out_no_setup;
		offset += otables[i].size;
	पूर्ण

	वापस 0;

out_no_setup:
	क्रम (i = 0; i < batch->num_otables; ++i) अणु
		अगर (batch->otables[i].enabled)
			vmw_takeकरोwn_otable_base(dev_priv, i,
						 &batch->otables[i]);
	पूर्ण

	vmw_bo_unpin_unlocked(batch->otable_bo);
	tपंचांग_bo_put(batch->otable_bo);
	batch->otable_bo = शून्य;
	वापस ret;
पूर्ण

/*
 * vmw_otables_setup - Set up guest backed memory object tables
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठाure
 *
 * Takes care of the device guest backed surface
 * initialization, by setting up the guest backed memory object tables.
 * Returns 0 on success and various error codes on failure. A successful वापस
 * means the object tables can be taken करोwn using the vmw_otables_takeकरोwn
 * function.
 */
पूर्णांक vmw_otables_setup(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_otable **otables = &dev_priv->otable_batch.otables;
	पूर्णांक ret;

	अगर (has_sm4_context(dev_priv)) अणु
		*otables = kmemdup(dx_tables, माप(dx_tables), GFP_KERNEL);
		अगर (!(*otables))
			वापस -ENOMEM;

		dev_priv->otable_batch.num_otables = ARRAY_SIZE(dx_tables);
	पूर्ण अन्यथा अणु
		*otables = kmemdup(pre_dx_tables, माप(pre_dx_tables),
				   GFP_KERNEL);
		अगर (!(*otables))
			वापस -ENOMEM;

		dev_priv->otable_batch.num_otables = ARRAY_SIZE(pre_dx_tables);
	पूर्ण

	ret = vmw_otable_batch_setup(dev_priv, &dev_priv->otable_batch);
	अगर (unlikely(ret != 0))
		जाओ out_setup;

	वापस 0;

out_setup:
	kमुक्त(*otables);
	वापस ret;
पूर्ण

अटल व्योम vmw_otable_batch_takeकरोwn(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_otable_batch *batch)
अणु
	SVGAOTableType i;
	काष्ठा tपंचांग_buffer_object *bo = batch->otable_bo;
	पूर्णांक ret;

	क्रम (i = 0; i < batch->num_otables; ++i)
		अगर (batch->otables[i].enabled)
			vmw_takeकरोwn_otable_base(dev_priv, i,
						 &batch->otables[i]);

	ret = tपंचांग_bo_reserve(bo, false, true, शून्य);
	BUG_ON(ret != 0);

	vmw_bo_fence_single(bo, शून्य);
	tपंचांग_bo_unpin(bo);
	tपंचांग_bo_unreserve(bo);

	tपंचांग_bo_unpin(batch->otable_bo);
	tपंचांग_bo_put(batch->otable_bo);
	batch->otable_bo = शून्य;
पूर्ण

/*
 * vmw_otables_takeकरोwn - Take करोwn guest backed memory object tables
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठाure
 *
 * Take करोwn the Guest Memory Object tables.
 */
व्योम vmw_otables_takeकरोwn(काष्ठा vmw_निजी *dev_priv)
अणु
	vmw_otable_batch_takeकरोwn(dev_priv, &dev_priv->otable_batch);
	kमुक्त(dev_priv->otable_batch.otables);
पूर्ण

/*
 * vmw_mob_calculate_pt_pages - Calculate the number of page table pages
 * needed क्रम a guest backed memory object.
 *
 * @data_pages:  Number of data pages in the memory object buffer.
 */
अटल अचिन्हित दीर्घ vmw_mob_calculate_pt_pages(अचिन्हित दीर्घ data_pages)
अणु
	अचिन्हित दीर्घ data_size = data_pages * PAGE_SIZE;
	अचिन्हित दीर्घ tot_size = 0;

	जबतक (likely(data_size > PAGE_SIZE)) अणु
		data_size = DIV_ROUND_UP(data_size, PAGE_SIZE);
		data_size *= VMW_PPN_SIZE;
		tot_size += (data_size + PAGE_SIZE - 1) & PAGE_MASK;
	पूर्ण

	वापस tot_size >> PAGE_SHIFT;
पूर्ण

/*
 * vmw_mob_create - Create a mob, but करोn't populate it.
 *
 * @data_pages:  Number of data pages of the underlying buffer object.
 */
काष्ठा vmw_mob *vmw_mob_create(अचिन्हित दीर्घ data_pages)
अणु
	काष्ठा vmw_mob *mob = kzalloc(माप(*mob), GFP_KERNEL);

	अगर (unlikely(!mob))
		वापस शून्य;

	mob->num_pages = vmw_mob_calculate_pt_pages(data_pages);

	वापस mob;
पूर्ण

/*
 * vmw_mob_pt_populate - Populate the mob pagetable
 *
 * @mob:         Poपूर्णांकer to the mob the pagetable of which we want to
 *               populate.
 *
 * This function allocates memory to be used क्रम the pagetable, and
 * adjusts TTM memory accounting accordingly. Returns ENOMEM अगर
 * memory resources aren't sufficient and may cause TTM buffer objects
 * to be swapped out by using the TTM memory accounting function.
 */
अटल पूर्णांक vmw_mob_pt_populate(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_mob *mob)
अणु
	BUG_ON(mob->pt_bo != शून्य);

	वापस vmw_bo_create_and_populate(dev_priv, mob->num_pages * PAGE_SIZE, &mob->pt_bo);
पूर्ण

/**
 * vmw_mob_assign_ppn - Assign a value to a page table entry
 *
 * @addr: Poपूर्णांकer to poपूर्णांकer to page table entry.
 * @val: The page table entry
 *
 * Assigns a value to a page table entry poपूर्णांकed to by *@addr and increments
 * *@addr according to the page table entry size.
 */
#अगर (VMW_PPN_SIZE == 8)
अटल व्योम vmw_mob_assign_ppn(u32 **addr, dma_addr_t val)
अणु
	*((u64 *) *addr) = val >> PAGE_SHIFT;
	*addr += 2;
पूर्ण
#अन्यथा
अटल व्योम vmw_mob_assign_ppn(u32 **addr, dma_addr_t val)
अणु
	*(*addr)++ = val >> PAGE_SHIFT;
पूर्ण
#पूर्ण_अगर

/*
 * vmw_mob_build_pt - Build a pagetable
 *
 * @data_addr:      Array of DMA addresses to the underlying buffer
 *                  object's data pages.
 * @num_data_pages: Number of buffer object data pages.
 * @pt_pages:       Array of page poपूर्णांकers to the page table pages.
 *
 * Returns the number of page table pages actually used.
 * Uses atomic kmaps of highmem pages to aव्योम TLB thrashing.
 */
अटल अचिन्हित दीर्घ vmw_mob_build_pt(काष्ठा vmw_piter *data_iter,
				      अचिन्हित दीर्घ num_data_pages,
				      काष्ठा vmw_piter *pt_iter)
अणु
	अचिन्हित दीर्घ pt_size = num_data_pages * VMW_PPN_SIZE;
	अचिन्हित दीर्घ num_pt_pages = DIV_ROUND_UP(pt_size, PAGE_SIZE);
	अचिन्हित दीर्घ pt_page;
	u32 *addr, *save_addr;
	अचिन्हित दीर्घ i;
	काष्ठा page *page;

	क्रम (pt_page = 0; pt_page < num_pt_pages; ++pt_page) अणु
		page = vmw_piter_page(pt_iter);

		save_addr = addr = kmap_atomic(page);

		क्रम (i = 0; i < PAGE_SIZE / VMW_PPN_SIZE; ++i) अणु
			vmw_mob_assign_ppn(&addr,
					   vmw_piter_dma_addr(data_iter));
			अगर (unlikely(--num_data_pages == 0))
				अवरोध;
			WARN_ON(!vmw_piter_next(data_iter));
		पूर्ण
		kunmap_atomic(save_addr);
		vmw_piter_next(pt_iter);
	पूर्ण

	वापस num_pt_pages;
पूर्ण

/*
 * vmw_mob_build_pt - Set up a multilevel mob pagetable
 *
 * @mob:            Poपूर्णांकer to a mob whose page table needs setting up.
 * @data_addr       Array of DMA addresses to the buffer object's data
 *                  pages.
 * @num_data_pages: Number of buffer object data pages.
 *
 * Uses tail recursion to set up a multilevel mob page table.
 */
अटल व्योम vmw_mob_pt_setup(काष्ठा vmw_mob *mob,
			     काष्ठा vmw_piter data_iter,
			     अचिन्हित दीर्घ num_data_pages)
अणु
	अचिन्हित दीर्घ num_pt_pages = 0;
	काष्ठा tपंचांग_buffer_object *bo = mob->pt_bo;
	काष्ठा vmw_piter save_pt_iter;
	काष्ठा vmw_piter pt_iter;
	स्थिर काष्ठा vmw_sg_table *vsgt;
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(bo, false, true, शून्य);
	BUG_ON(ret != 0);

	vsgt = vmw_bo_sg_table(bo);
	vmw_piter_start(&pt_iter, vsgt, 0);
	BUG_ON(!vmw_piter_next(&pt_iter));
	mob->pt_level = 0;
	जबतक (likely(num_data_pages > 1)) अणु
		++mob->pt_level;
		BUG_ON(mob->pt_level > 2);
		save_pt_iter = pt_iter;
		num_pt_pages = vmw_mob_build_pt(&data_iter, num_data_pages,
						&pt_iter);
		data_iter = save_pt_iter;
		num_data_pages = num_pt_pages;
	पूर्ण

	mob->pt_root_page = vmw_piter_dma_addr(&save_pt_iter);
	tपंचांग_bo_unreserve(bo);
पूर्ण

/*
 * vmw_mob_destroy - Destroy a mob, unpopulating first अगर necessary.
 *
 * @mob:            Poपूर्णांकer to a mob to destroy.
 */
व्योम vmw_mob_destroy(काष्ठा vmw_mob *mob)
अणु
	अगर (mob->pt_bo) अणु
		vmw_bo_unpin_unlocked(mob->pt_bo);
		tपंचांग_bo_put(mob->pt_bo);
		mob->pt_bo = शून्य;
	पूर्ण
	kमुक्त(mob);
पूर्ण

/*
 * vmw_mob_unbind - Hide a mob from the device.
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी.
 * @mob_id:         Device id of the mob to unbind.
 */
व्योम vmw_mob_unbind(काष्ठा vmw_निजी *dev_priv,
		    काष्ठा vmw_mob *mob)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDestroyGBMob body;
	पूर्ण *cmd;
	पूर्णांक ret;
	काष्ठा tपंचांग_buffer_object *bo = mob->pt_bo;

	अगर (bo) अणु
		ret = tपंचांग_bo_reserve(bo, false, true, शून्य);
		/*
		 * Noone अन्यथा should be using this buffer.
		 */
		BUG_ON(ret != 0);
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (cmd) अणु
		cmd->header.id = SVGA_3D_CMD_DESTROY_GB_MOB;
		cmd->header.size = माप(cmd->body);
		cmd->body.mobid = mob->id;
		vmw_cmd_commit(dev_priv, माप(*cmd));
	पूर्ण

	अगर (bo) अणु
		vmw_bo_fence_single(bo, शून्य);
		tपंचांग_bo_unreserve(bo);
	पूर्ण
	vmw_fअगरo_resource_dec(dev_priv);
पूर्ण

/*
 * vmw_mob_bind - Make a mob visible to the device after first
 *                populating it अगर necessary.
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी.
 * @mob:            Poपूर्णांकer to the mob we're making visible.
 * @data_addr:      Array of DMA addresses to the data pages of the underlying
 *                  buffer object.
 * @num_data_pages: Number of data pages of the underlying buffer
 *                  object.
 * @mob_id:         Device id of the mob to bind
 *
 * This function is पूर्णांकended to be पूर्णांकerfaced with the tपंचांग_tt backend
 * code.
 */
पूर्णांक vmw_mob_bind(काष्ठा vmw_निजी *dev_priv,
		 काष्ठा vmw_mob *mob,
		 स्थिर काष्ठा vmw_sg_table *vsgt,
		 अचिन्हित दीर्घ num_data_pages,
		 पूर्णांक32_t mob_id)
अणु
	पूर्णांक ret;
	bool pt_set_up = false;
	काष्ठा vmw_piter data_iter;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBMob64 body;
	पूर्ण *cmd;

	mob->id = mob_id;
	vmw_piter_start(&data_iter, vsgt, 0);
	अगर (unlikely(!vmw_piter_next(&data_iter)))
		वापस 0;

	अगर (likely(num_data_pages == 1)) अणु
		mob->pt_level = VMW_MOBFMT_PTDEPTH_0;
		mob->pt_root_page = vmw_piter_dma_addr(&data_iter);
	पूर्ण अन्यथा अगर (vsgt->num_regions == 1) अणु
		mob->pt_level = SVGA3D_MOBFMT_RANGE;
		mob->pt_root_page = vmw_piter_dma_addr(&data_iter);
	पूर्ण अन्यथा अगर (unlikely(mob->pt_bo == शून्य)) अणु
		ret = vmw_mob_pt_populate(dev_priv, mob);
		अगर (unlikely(ret != 0))
			वापस ret;

		vmw_mob_pt_setup(mob, data_iter, num_data_pages);
		pt_set_up = true;
		mob->pt_level += VMW_MOBFMT_PTDEPTH_1 - SVGA3D_MOBFMT_PTDEPTH_1;
	पूर्ण

	vmw_fअगरo_resource_inc(dev_priv);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		जाओ out_no_cmd_space;

	cmd->header.id = SVGA_3D_CMD_DEFINE_GB_MOB64;
	cmd->header.size = माप(cmd->body);
	cmd->body.mobid = mob_id;
	cmd->body.ptDepth = mob->pt_level;
	cmd->body.base = mob->pt_root_page >> PAGE_SHIFT;
	cmd->body.sizeInBytes = num_data_pages * PAGE_SIZE;

	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;

out_no_cmd_space:
	vmw_fअगरo_resource_dec(dev_priv);
	अगर (pt_set_up) अणु
		vmw_bo_unpin_unlocked(mob->pt_bo);
		tपंचांग_bo_put(mob->pt_bo);
		mob->pt_bo = शून्य;
	पूर्ण

	वापस -ENOMEM;
पूर्ण
