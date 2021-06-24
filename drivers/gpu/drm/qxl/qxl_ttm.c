<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/delay.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/qxl_drm.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

अटल काष्ठा qxl_device *qxl_get_qdev(काष्ठा tपंचांग_device *bdev)
अणु
	काष्ठा qxl_mman *mman;
	काष्ठा qxl_device *qdev;

	mman = container_of(bdev, काष्ठा qxl_mman, bdev);
	qdev = container_of(mman, काष्ठा qxl_device, mman);
	वापस qdev;
पूर्ण

अटल व्योम qxl_evict_flags(काष्ठा tपंचांग_buffer_object *bo,
				काष्ठा tपंचांग_placement *placement)
अणु
	काष्ठा qxl_bo *qbo;
	अटल स्थिर काष्ठा tपंचांग_place placements = अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_SYSTEM,
		.flags = 0
	पूर्ण;

	अगर (!qxl_tपंचांग_bo_is_qxl_bo(bo)) अणु
		placement->placement = &placements;
		placement->busy_placement = &placements;
		placement->num_placement = 1;
		placement->num_busy_placement = 1;
		वापस;
	पूर्ण
	qbo = to_qxl_bo(bo);
	qxl_tपंचांग_placement_from_करोमुख्य(qbo, QXL_GEM_DOMAIN_CPU);
	*placement = qbo->placement;
पूर्ण

पूर्णांक qxl_tपंचांग_io_mem_reserve(काष्ठा tपंचांग_device *bdev,
			   काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा qxl_device *qdev = qxl_get_qdev(bdev);

	चयन (mem->mem_type) अणु
	हाल TTM_PL_SYSTEM:
		/* प्रणाली memory */
		वापस 0;
	हाल TTM_PL_VRAM:
		mem->bus.is_iomem = true;
		mem->bus.offset = (mem->start << PAGE_SHIFT) + qdev->vram_base;
		mem->bus.caching = tपंचांग_cached;
		अवरोध;
	हाल TTM_PL_PRIV:
		mem->bus.is_iomem = true;
		mem->bus.offset = (mem->start << PAGE_SHIFT) +
			qdev->surfaceram_base;
		mem->bus.caching = tपंचांग_cached;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * TTM backend functions.
 */
अटल व्योम qxl_tपंचांग_backend_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	tपंचांग_tt_destroy_common(bdev, tपंचांग);
	tपंचांग_tt_fini(tपंचांग);
	kमुक्त(tपंचांग);
पूर्ण

अटल काष्ठा tपंचांग_tt *qxl_tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo,
					uपूर्णांक32_t page_flags)
अणु
	काष्ठा tपंचांग_tt *tपंचांग;

	tपंचांग = kzalloc(माप(काष्ठा tपंचांग_tt), GFP_KERNEL);
	अगर (tपंचांग == शून्य)
		वापस शून्य;
	अगर (tपंचांग_tt_init(tपंचांग, bo, page_flags, tपंचांग_cached)) अणु
		kमुक्त(tपंचांग);
		वापस शून्य;
	पूर्ण
	वापस tपंचांग;
पूर्ण

अटल व्योम qxl_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			       काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा qxl_bo *qbo;
	काष्ठा qxl_device *qdev;

	अगर (!qxl_tपंचांग_bo_is_qxl_bo(bo))
		वापस;
	qbo = to_qxl_bo(bo);
	qdev = to_qxl(qbo->tbo.base.dev);

	अगर (bo->mem.mem_type == TTM_PL_PRIV && qbo->surface_id)
		qxl_surface_evict(qdev, qbo, new_mem ? true : false);
पूर्ण

अटल पूर्णांक qxl_bo_move(काष्ठा tपंचांग_buffer_object *bo, bool evict,
		       काष्ठा tपंचांग_operation_ctx *ctx,
		       काष्ठा tपंचांग_resource *new_mem,
		       काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा tपंचांग_resource *old_mem = &bo->mem;
	पूर्णांक ret;

	qxl_bo_move_notअगरy(bo, new_mem);

	ret = tपंचांग_bo_रुको_ctx(bo, ctx);
	अगर (ret)
		वापस ret;

	अगर (old_mem->mem_type == TTM_PL_SYSTEM && bo->tपंचांग == शून्य) अणु
		tपंचांग_bo_move_null(bo, new_mem);
		वापस 0;
	पूर्ण
	वापस tपंचांग_bo_move_स_नकल(bo, ctx, new_mem);
पूर्ण

अटल व्योम qxl_bo_delete_mem_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	qxl_bo_move_notअगरy(bo, शून्य);
पूर्ण

अटल काष्ठा tपंचांग_device_funcs qxl_bo_driver = अणु
	.tपंचांग_tt_create = &qxl_tपंचांग_tt_create,
	.tपंचांग_tt_destroy = &qxl_tपंचांग_backend_destroy,
	.eviction_valuable = tपंचांग_bo_eviction_valuable,
	.evict_flags = &qxl_evict_flags,
	.move = &qxl_bo_move,
	.io_mem_reserve = &qxl_tपंचांग_io_mem_reserve,
	.delete_mem_notअगरy = &qxl_bo_delete_mem_notअगरy,
पूर्ण;

अटल पूर्णांक qxl_tपंचांग_init_mem_type(काष्ठा qxl_device *qdev,
				 अचिन्हित पूर्णांक type,
				 uपूर्णांक64_t size)
अणु
	वापस tपंचांग_range_man_init(&qdev->mman.bdev, type, false, size);
पूर्ण

पूर्णांक qxl_tपंचांग_init(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक r;
	पूर्णांक num_io_pages; /* != rom->num_io_pages, we include surface0 */

	/* No others user of address space so set it to 0 */
	r = tपंचांग_device_init(&qdev->mman.bdev, &qxl_bo_driver, शून्य,
			    qdev->ddev.anon_inode->i_mapping,
			    qdev->ddev.vma_offset_manager,
			    false, false);
	अगर (r) अणु
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		वापस r;
	पूर्ण
	/* NOTE: this includes the framebuffer (aka surface 0) */
	num_io_pages = qdev->rom->ram_header_offset / PAGE_SIZE;
	r = qxl_tपंचांग_init_mem_type(qdev, TTM_PL_VRAM, num_io_pages);
	अगर (r) अणु
		DRM_ERROR("Failed initializing VRAM heap.\n");
		वापस r;
	पूर्ण
	r = qxl_tपंचांग_init_mem_type(qdev, TTM_PL_PRIV,
				  qdev->surfaceram_size / PAGE_SIZE);
	अगर (r) अणु
		DRM_ERROR("Failed initializing Surfaces heap.\n");
		वापस r;
	पूर्ण
	DRM_INFO("qxl: %uM of VRAM memory size\n",
		 (अचिन्हित पूर्णांक)qdev->vram_size / (1024 * 1024));
	DRM_INFO("qxl: %luM of IO pages memory ready (VRAM domain)\n",
		 ((अचिन्हित पूर्णांक)num_io_pages * PAGE_SIZE) / (1024 * 1024));
	DRM_INFO("qxl: %uM of Surface memory size\n",
		 (अचिन्हित पूर्णांक)qdev->surfaceram_size / (1024 * 1024));
	वापस 0;
पूर्ण

व्योम qxl_tपंचांग_fini(काष्ठा qxl_device *qdev)
अणु
	tपंचांग_range_man_fini(&qdev->mman.bdev, TTM_PL_VRAM);
	tपंचांग_range_man_fini(&qdev->mman.bdev, TTM_PL_PRIV);
	tपंचांग_device_fini(&qdev->mman.bdev);
	DRM_INFO("qxl: ttm finalized\n");
पूर्ण

#घोषणा QXL_DEBUGFS_MEM_TYPES 2

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक qxl_mm_dump_table(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = (काष्ठा tपंचांग_resource_manager *)node->info_ent->data;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	tपंचांग_resource_manager_debug(man, &p);
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम qxl_tपंचांग_debugfs_init(काष्ठा qxl_device *qdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	अटल काष्ठा drm_info_list qxl_mem_types_list[QXL_DEBUGFS_MEM_TYPES];
	अटल अक्षर qxl_mem_types_names[QXL_DEBUGFS_MEM_TYPES][32];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < QXL_DEBUGFS_MEM_TYPES; i++) अणु
		अगर (i == 0)
			प्र_लिखो(qxl_mem_types_names[i], "qxl_mem_mm");
		अन्यथा
			प्र_लिखो(qxl_mem_types_names[i], "qxl_surf_mm");
		qxl_mem_types_list[i].name = qxl_mem_types_names[i];
		qxl_mem_types_list[i].show = &qxl_mm_dump_table;
		qxl_mem_types_list[i].driver_features = 0;
		अगर (i == 0)
			qxl_mem_types_list[i].data = tपंचांग_manager_type(&qdev->mman.bdev, TTM_PL_VRAM);
		अन्यथा
			qxl_mem_types_list[i].data = tपंचांग_manager_type(&qdev->mman.bdev, TTM_PL_PRIV);

	पूर्ण
	qxl_debugfs_add_files(qdev, qxl_mem_types_list, i);
#पूर्ण_अगर
पूर्ण
