<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright तऊ 2018 VMware, Inc., Palo Alto, CA., USA
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
#समावेश <linux/slab.h>
#समावेश "vmwgfx_validation.h"
#समावेश "vmwgfx_drv.h"

/**
 * काष्ठा vmw_validation_bo_node - Buffer object validation metadata.
 * @base: Metadata used क्रम TTM reservation- and validation.
 * @hash: A hash entry used क्रम the duplicate detection hash table.
 * @coherent_count: If चयनing backup buffers, number of new coherent
 * resources that will have this buffer as a backup buffer.
 * @as_mob: Validate as mob.
 * @cpu_blit: Validate क्रम cpu blit access.
 *
 * Bit fields are used since these काष्ठाures are allocated and मुक्तd in
 * large numbers and space conservation is desired.
 */
काष्ठा vmw_validation_bo_node अणु
	काष्ठा tपंचांग_validate_buffer base;
	काष्ठा drm_hash_item hash;
	अचिन्हित पूर्णांक coherent_count;
	u32 as_mob : 1;
	u32 cpu_blit : 1;
पूर्ण;
/**
 * काष्ठा vmw_validation_res_node - Resource validation metadata.
 * @head: List head क्रम the resource validation list.
 * @hash: A hash entry used क्रम the duplicate detection hash table.
 * @res: Reference counted resource poपूर्णांकer.
 * @new_backup: Non ref-counted poपूर्णांकer to new backup buffer to be asचिन्हित
 * to a resource.
 * @new_backup_offset: Offset पूर्णांकo the new backup mob क्रम resources that can
 * share MOBs.
 * @no_buffer_needed: Kernel करोes not need to allocate a MOB during validation,
 * the command stream provides a mob bind operation.
 * @चयनing_backup: The validation process is चयनing backup MOB.
 * @first_usage: True अगरf the resource has been seen only once in the current
 * validation batch.
 * @reserved: Whether the resource is currently reserved by this process.
 * @dirty_set: Change dirty status of the resource.
 * @dirty: Dirty inक्रमmation VMW_RES_सूचीTY_XX.
 * @निजी: Optionally additional memory क्रम caller-निजी data.
 *
 * Bit fields are used since these काष्ठाures are allocated and मुक्तd in
 * large numbers and space conservation is desired.
 */
काष्ठा vmw_validation_res_node अणु
	काष्ठा list_head head;
	काष्ठा drm_hash_item hash;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_buffer_object *new_backup;
	अचिन्हित दीर्घ new_backup_offset;
	u32 no_buffer_needed : 1;
	u32 चयनing_backup : 1;
	u32 first_usage : 1;
	u32 reserved : 1;
	u32 dirty : 1;
	u32 dirty_set : 1;
	अचिन्हित दीर्घ निजी[0];
पूर्ण;

/**
 * vmw_validation_mem_alloc - Allocate kernel memory from the validation
 * context based allocator
 * @ctx: The validation context
 * @size: The number of bytes to allocated.
 *
 * The memory allocated may not exceed PAGE_SIZE, and the वापसed
 * address is aligned to माप(दीर्घ). All memory allocated this way is
 * reclaimed after validation when calling any of the exported functions:
 * vmw_validation_unref_lists()
 * vmw_validation_revert()
 * vmw_validation_करोne()
 *
 * Return: Poपूर्णांकer to the allocated memory on success. शून्य on failure.
 */
व्योम *vmw_validation_mem_alloc(काष्ठा vmw_validation_context *ctx,
			       अचिन्हित पूर्णांक size)
अणु
	व्योम *addr;

	size = vmw_validation_align(size);
	अगर (size > PAGE_SIZE)
		वापस शून्य;

	अगर (ctx->mem_size_left < size) अणु
		काष्ठा page *page;

		अगर (ctx->vm && ctx->vm_size_left < PAGE_SIZE) अणु
			पूर्णांक ret = ctx->vm->reserve_mem(ctx->vm, ctx->vm->gran);

			अगर (ret)
				वापस शून्य;

			ctx->vm_size_left += ctx->vm->gran;
			ctx->total_mem += ctx->vm->gran;
		पूर्ण

		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		अगर (!page)
			वापस शून्य;

		अगर (ctx->vm)
			ctx->vm_size_left -= PAGE_SIZE;

		list_add_tail(&page->lru, &ctx->page_list);
		ctx->page_address = page_address(page);
		ctx->mem_size_left = PAGE_SIZE;
	पूर्ण

	addr = (व्योम *) (ctx->page_address + (PAGE_SIZE - ctx->mem_size_left));
	ctx->mem_size_left -= size;

	वापस addr;
पूर्ण

/**
 * vmw_validation_mem_मुक्त - Free all memory allocated using
 * vmw_validation_mem_alloc()
 * @ctx: The validation context
 *
 * All memory previously allocated क्रम this context using
 * vmw_validation_mem_alloc() is मुक्तd.
 */
अटल व्योम vmw_validation_mem_मुक्त(काष्ठा vmw_validation_context *ctx)
अणु
	काष्ठा page *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &ctx->page_list, lru) अणु
		list_del_init(&entry->lru);
		__मुक्त_page(entry);
	पूर्ण

	ctx->mem_size_left = 0;
	अगर (ctx->vm && ctx->total_mem) अणु
		ctx->vm->unreserve_mem(ctx->vm, ctx->total_mem);
		ctx->total_mem = 0;
		ctx->vm_size_left = 0;
	पूर्ण
पूर्ण

/**
 * vmw_validation_find_bo_dup - Find a duplicate buffer object entry in the
 * validation context's lists.
 * @ctx: The validation context to search.
 * @vbo: The buffer object to search क्रम.
 *
 * Return: Poपूर्णांकer to the काष्ठा vmw_validation_bo_node referencing the
 * duplicate, or शून्य अगर none found.
 */
अटल काष्ठा vmw_validation_bo_node *
vmw_validation_find_bo_dup(काष्ठा vmw_validation_context *ctx,
			   काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा  vmw_validation_bo_node *bo_node = शून्य;

	अगर (!ctx->merge_dups)
		वापस शून्य;

	अगर (ctx->ht) अणु
		काष्ठा drm_hash_item *hash;

		अगर (!drm_ht_find_item(ctx->ht, (अचिन्हित दीर्घ) vbo, &hash))
			bo_node = container_of(hash, typeof(*bo_node), hash);
	पूर्ण अन्यथा अणु
		काष्ठा  vmw_validation_bo_node *entry;

		list_क्रम_each_entry(entry, &ctx->bo_list, base.head) अणु
			अगर (entry->base.bo == &vbo->base) अणु
				bo_node = entry;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस bo_node;
पूर्ण

/**
 * vmw_validation_find_res_dup - Find a duplicate resource entry in the
 * validation context's lists.
 * @ctx: The validation context to search.
 * @res: Reference counted resource poपूर्णांकer.
 *
 * Return: Poपूर्णांकer to the काष्ठा vmw_validation_bo_node referencing the
 * duplicate, or शून्य अगर none found.
 */
अटल काष्ठा vmw_validation_res_node *
vmw_validation_find_res_dup(काष्ठा vmw_validation_context *ctx,
			    काष्ठा vmw_resource *res)
अणु
	काष्ठा  vmw_validation_res_node *res_node = शून्य;

	अगर (!ctx->merge_dups)
		वापस शून्य;

	अगर (ctx->ht) अणु
		काष्ठा drm_hash_item *hash;

		अगर (!drm_ht_find_item(ctx->ht, (अचिन्हित दीर्घ) res, &hash))
			res_node = container_of(hash, typeof(*res_node), hash);
	पूर्ण अन्यथा अणु
		काष्ठा  vmw_validation_res_node *entry;

		list_क्रम_each_entry(entry, &ctx->resource_ctx_list, head) अणु
			अगर (entry->res == res) अणु
				res_node = entry;
				जाओ out;
			पूर्ण
		पूर्ण

		list_क्रम_each_entry(entry, &ctx->resource_list, head) अणु
			अगर (entry->res == res) अणु
				res_node = entry;
				अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण
out:
	वापस res_node;
पूर्ण

/**
 * vmw_validation_add_bo - Add a buffer object to the validation context.
 * @ctx: The validation context.
 * @vbo: The buffer object.
 * @as_mob: Validate as mob, otherwise suitable क्रम GMR operations.
 * @cpu_blit: Validate in a page-mappable location.
 *
 * Return: Zero on success, negative error code otherwise.
 */
पूर्णांक vmw_validation_add_bo(काष्ठा vmw_validation_context *ctx,
			  काष्ठा vmw_buffer_object *vbo,
			  bool as_mob,
			  bool cpu_blit)
अणु
	काष्ठा vmw_validation_bo_node *bo_node;

	bo_node = vmw_validation_find_bo_dup(ctx, vbo);
	अगर (bo_node) अणु
		अगर (bo_node->as_mob != as_mob ||
		    bo_node->cpu_blit != cpu_blit) अणु
			DRM_ERROR("Inconsistent buffer usage.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा tपंचांग_validate_buffer *val_buf;
		पूर्णांक ret;

		bo_node = vmw_validation_mem_alloc(ctx, माप(*bo_node));
		अगर (!bo_node)
			वापस -ENOMEM;

		अगर (ctx->ht) अणु
			bo_node->hash.key = (अचिन्हित दीर्घ) vbo;
			ret = drm_ht_insert_item(ctx->ht, &bo_node->hash);
			अगर (ret) अणु
				DRM_ERROR("Failed to initialize a buffer "
					  "validation entry.\n");
				वापस ret;
			पूर्ण
		पूर्ण
		val_buf = &bo_node->base;
		val_buf->bo = tपंचांग_bo_get_unless_zero(&vbo->base);
		अगर (!val_buf->bo)
			वापस -ESRCH;
		val_buf->num_shared = 0;
		list_add_tail(&val_buf->head, &ctx->bo_list);
		bo_node->as_mob = as_mob;
		bo_node->cpu_blit = cpu_blit;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_validation_add_resource - Add a resource to the validation context.
 * @ctx: The validation context.
 * @res: The resource.
 * @priv_size: Size of निजी, additional metadata.
 * @dirty: Whether to change dirty status.
 * @p_node: Output poपूर्णांकer of additional metadata address.
 * @first_usage: Whether this was the first समय this resource was seen.
 *
 * Return: Zero on success, negative error code otherwise.
 */
पूर्णांक vmw_validation_add_resource(काष्ठा vmw_validation_context *ctx,
				काष्ठा vmw_resource *res,
				माप_प्रकार priv_size,
				u32 dirty,
				व्योम **p_node,
				bool *first_usage)
अणु
	काष्ठा vmw_validation_res_node *node;
	पूर्णांक ret;

	node = vmw_validation_find_res_dup(ctx, res);
	अगर (node) अणु
		node->first_usage = 0;
		जाओ out_fill;
	पूर्ण

	node = vmw_validation_mem_alloc(ctx, माप(*node) + priv_size);
	अगर (!node) अणु
		VMW_DEBUG_USER("Failed to allocate a resource validation entry.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ctx->ht) अणु
		node->hash.key = (अचिन्हित दीर्घ) res;
		ret = drm_ht_insert_item(ctx->ht, &node->hash);
		अगर (ret) अणु
			DRM_ERROR("Failed to initialize a resource validation "
				  "entry.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	node->res = vmw_resource_reference_unless_करोomed(res);
	अगर (!node->res)
		वापस -ESRCH;

	node->first_usage = 1;
	अगर (!res->dev_priv->has_mob) अणु
		list_add_tail(&node->head, &ctx->resource_list);
	पूर्ण अन्यथा अणु
		चयन (vmw_res_type(res)) अणु
		हाल vmw_res_context:
		हाल vmw_res_dx_context:
			list_add(&node->head, &ctx->resource_ctx_list);
			अवरोध;
		हाल vmw_res_cotable:
			list_add_tail(&node->head, &ctx->resource_ctx_list);
			अवरोध;
		शेष:
			list_add_tail(&node->head, &ctx->resource_list);
			अवरोध;
		पूर्ण
	पूर्ण

out_fill:
	अगर (dirty) अणु
		node->dirty_set = 1;
		/* Overwriting previous inक्रमmation here is पूर्णांकentional! */
		node->dirty = (dirty & VMW_RES_सूचीTY_SET) ? 1 : 0;
	पूर्ण
	अगर (first_usage)
		*first_usage = node->first_usage;
	अगर (p_node)
		*p_node = &node->निजी;

	वापस 0;
पूर्ण

/**
 * vmw_validation_res_set_dirty - Register a resource dirty set or clear during
 * validation.
 * @ctx: The validation context.
 * @val_निजी: The additional meta-data poपूर्णांकer वापसed when the
 * resource was रेजिस्टरed with the validation context. Used to identअगरy
 * the resource.
 * @dirty: Dirty inक्रमmation VMW_RES_सूचीTY_XX
 */
व्योम vmw_validation_res_set_dirty(काष्ठा vmw_validation_context *ctx,
				  व्योम *val_निजी, u32 dirty)
अणु
	काष्ठा vmw_validation_res_node *val;

	अगर (!dirty)
		वापस;

	val = container_of(val_निजी, typeof(*val), निजी);
	val->dirty_set = 1;
	/* Overwriting previous inक्रमmation here is पूर्णांकentional! */
	val->dirty = (dirty & VMW_RES_सूचीTY_SET) ? 1 : 0;
पूर्ण

/**
 * vmw_validation_res_चयन_backup - Register a backup MOB चयन during
 * validation.
 * @ctx: The validation context.
 * @val_निजी: The additional meta-data poपूर्णांकer वापसed when the
 * resource was रेजिस्टरed with the validation context. Used to identअगरy
 * the resource.
 * @vbo: The new backup buffer object MOB. This buffer object needs to have
 * alपढ़ोy been रेजिस्टरed with the validation context.
 * @backup_offset: Offset पूर्णांकo the new backup MOB.
 */
व्योम vmw_validation_res_चयन_backup(काष्ठा vmw_validation_context *ctx,
				      व्योम *val_निजी,
				      काष्ठा vmw_buffer_object *vbo,
				      अचिन्हित दीर्घ backup_offset)
अणु
	काष्ठा vmw_validation_res_node *val;

	val = container_of(val_निजी, typeof(*val), निजी);

	val->चयनing_backup = 1;
	अगर (val->first_usage)
		val->no_buffer_needed = 1;

	val->new_backup = vbo;
	val->new_backup_offset = backup_offset;
पूर्ण

/**
 * vmw_validation_res_reserve - Reserve all resources रेजिस्टरed with this
 * validation context.
 * @ctx: The validation context.
 * @पूर्णांकr: Use पूर्णांकerruptible रुकोs when possible.
 *
 * Return: Zero on success, -ERESTARTSYS अगर पूर्णांकerrupted. Negative error
 * code on failure.
 */
पूर्णांक vmw_validation_res_reserve(काष्ठा vmw_validation_context *ctx,
			       bool पूर्णांकr)
अणु
	काष्ठा vmw_validation_res_node *val;
	पूर्णांक ret = 0;

	list_splice_init(&ctx->resource_ctx_list, &ctx->resource_list);

	list_क्रम_each_entry(val, &ctx->resource_list, head) अणु
		काष्ठा vmw_resource *res = val->res;

		ret = vmw_resource_reserve(res, पूर्णांकr, val->no_buffer_needed);
		अगर (ret)
			जाओ out_unreserve;

		val->reserved = 1;
		अगर (res->backup) अणु
			काष्ठा vmw_buffer_object *vbo = res->backup;

			ret = vmw_validation_add_bo
				(ctx, vbo, vmw_resource_needs_backup(res),
				 false);
			अगर (ret)
				जाओ out_unreserve;
		पूर्ण

		अगर (val->चयनing_backup && val->new_backup &&
		    res->coherent) अणु
			काष्ठा vmw_validation_bo_node *bo_node =
				vmw_validation_find_bo_dup(ctx,
							   val->new_backup);

			अगर (WARN_ON(!bo_node)) अणु
				ret = -EINVAL;
				जाओ out_unreserve;
			पूर्ण
			bo_node->coherent_count++;
		पूर्ण
	पूर्ण

	वापस 0;

out_unreserve:
	vmw_validation_res_unreserve(ctx, true);
	वापस ret;
पूर्ण

/**
 * vmw_validation_res_unreserve - Unreserve all reserved resources
 * रेजिस्टरed with this validation context.
 * @ctx: The validation context.
 * @backoff: Whether this is a backoff- of a commit-type operation. This
 * is used to determine whether to चयन backup MOBs or not.
 */
व्योम vmw_validation_res_unreserve(काष्ठा vmw_validation_context *ctx,
				 bool backoff)
अणु
	काष्ठा vmw_validation_res_node *val;

	list_splice_init(&ctx->resource_ctx_list, &ctx->resource_list);
	अगर (backoff)
		list_क्रम_each_entry(val, &ctx->resource_list, head) अणु
			अगर (val->reserved)
				vmw_resource_unreserve(val->res,
						       false, false, false,
						       शून्य, 0);
		पूर्ण
	अन्यथा
		list_क्रम_each_entry(val, &ctx->resource_list, head) अणु
			अगर (val->reserved)
				vmw_resource_unreserve(val->res,
						       val->dirty_set,
						       val->dirty,
						       val->चयनing_backup,
						       val->new_backup,
						       val->new_backup_offset);
		पूर्ण
पूर्ण

/**
 * vmw_validation_bo_validate_single - Validate a single buffer object.
 * @bo: The TTM buffer object base.
 * @पूर्णांकerruptible: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 * @validate_as_mob: Whether to validate in MOB memory.
 *
 * Return: Zero on success, -ERESTARTSYS अगर पूर्णांकerrupted. Negative error
 * code on failure.
 */
पूर्णांक vmw_validation_bo_validate_single(काष्ठा tपंचांग_buffer_object *bo,
				      bool पूर्णांकerruptible,
				      bool validate_as_mob)
अणु
	काष्ठा vmw_buffer_object *vbo =
		container_of(bo, काष्ठा vmw_buffer_object, base);
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = पूर्णांकerruptible,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&vbo->cpu_ग_लिखोrs))
		वापस -EBUSY;

	अगर (vbo->base.pin_count > 0)
		वापस 0;

	अगर (validate_as_mob)
		वापस tपंचांग_bo_validate(bo, &vmw_mob_placement, &ctx);

	/**
	 * Put BO in VRAM अगर there is space, otherwise as a GMR.
	 * If there is no space in VRAM and GMR ids are all used up,
	 * start evicting GMRs to make room. If the DMA buffer can't be
	 * used as a GMR, this will वापस -ENOMEM.
	 */

	ret = tपंचांग_bo_validate(bo, &vmw_vram_gmr_placement, &ctx);
	अगर (ret == 0 || ret == -ERESTARTSYS)
		वापस ret;

	/**
	 * If that failed, try VRAM again, this समय evicting
	 * previous contents.
	 */

	ret = tपंचांग_bo_validate(bo, &vmw_vram_placement, &ctx);
	वापस ret;
पूर्ण

/**
 * vmw_validation_bo_validate - Validate all buffer objects रेजिस्टरed with
 * the validation context.
 * @ctx: The validation context.
 * @पूर्णांकr: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 *
 * Return: Zero on success, -ERESTARTSYS अगर पूर्णांकerrupted,
 * negative error code on failure.
 */
पूर्णांक vmw_validation_bo_validate(काष्ठा vmw_validation_context *ctx, bool पूर्णांकr)
अणु
	काष्ठा vmw_validation_bo_node *entry;
	पूर्णांक ret;

	list_क्रम_each_entry(entry, &ctx->bo_list, base.head) अणु
		काष्ठा vmw_buffer_object *vbo =
			container_of(entry->base.bo, typeof(*vbo), base);

		अगर (entry->cpu_blit) अणु
			काष्ठा tपंचांग_operation_ctx ctx = अणु
				.पूर्णांकerruptible = पूर्णांकr,
				.no_रुको_gpu = false
			पूर्ण;

			ret = tपंचांग_bo_validate(entry->base.bo,
					      &vmw_nonfixed_placement, &ctx);
		पूर्ण अन्यथा अणु
			ret = vmw_validation_bo_validate_single
			(entry->base.bo, पूर्णांकr, entry->as_mob);
		पूर्ण
		अगर (ret)
			वापस ret;

		/*
		 * Rather than having the resource code allocating the bo
		 * dirty tracker in resource_unreserve() where we can't fail,
		 * Do it here when validating the buffer object.
		 */
		अगर (entry->coherent_count) अणु
			अचिन्हित पूर्णांक coherent_count = entry->coherent_count;

			जबतक (coherent_count) अणु
				ret = vmw_bo_dirty_add(vbo);
				अगर (ret)
					वापस ret;

				coherent_count--;
			पूर्ण
			entry->coherent_count -= coherent_count;
		पूर्ण

		अगर (vbo->dirty)
			vmw_bo_dirty_scan(vbo);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vmw_validation_res_validate - Validate all resources रेजिस्टरed with the
 * validation context.
 * @ctx: The validation context.
 * @पूर्णांकr: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 *
 * Beक्रमe this function is called, all resource backup buffers must have
 * been validated.
 *
 * Return: Zero on success, -ERESTARTSYS अगर पूर्णांकerrupted,
 * negative error code on failure.
 */
पूर्णांक vmw_validation_res_validate(काष्ठा vmw_validation_context *ctx, bool पूर्णांकr)
अणु
	काष्ठा vmw_validation_res_node *val;
	पूर्णांक ret;

	list_क्रम_each_entry(val, &ctx->resource_list, head) अणु
		काष्ठा vmw_resource *res = val->res;
		काष्ठा vmw_buffer_object *backup = res->backup;

		ret = vmw_resource_validate(res, पूर्णांकr, val->dirty_set &&
					    val->dirty);
		अगर (ret) अणु
			अगर (ret != -ERESTARTSYS)
				DRM_ERROR("Failed to validate resource.\n");
			वापस ret;
		पूर्ण

		/* Check अगर the resource चयनed backup buffer */
		अगर (backup && res->backup && (backup != res->backup)) अणु
			काष्ठा vmw_buffer_object *vbo = res->backup;

			ret = vmw_validation_add_bo
				(ctx, vbo, vmw_resource_needs_backup(res),
				 false);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vmw_validation_drop_ht - Reset the hash table used क्रम duplicate finding
 * and unरेजिस्टर it from this validation context.
 * @ctx: The validation context.
 *
 * The hash table used क्रम duplicate finding is an expensive resource and
 * may be रक्षित by mutexes that may cause deadlocks during resource
 * unreferencing अगर held. After resource- and buffer object रेजिस्टरing,
 * there is no दीर्घer any use क्रम this hash table, so allow मुक्तing it
 * either to लघुen any mutex locking समय, or beक्रमe resources- and
 * buffer objects are मुक्तd during validation context cleanup.
 */
व्योम vmw_validation_drop_ht(काष्ठा vmw_validation_context *ctx)
अणु
	काष्ठा vmw_validation_bo_node *entry;
	काष्ठा vmw_validation_res_node *val;

	अगर (!ctx->ht)
		वापस;

	list_क्रम_each_entry(entry, &ctx->bo_list, base.head)
		(व्योम) drm_ht_हटाओ_item(ctx->ht, &entry->hash);

	list_क्रम_each_entry(val, &ctx->resource_list, head)
		(व्योम) drm_ht_हटाओ_item(ctx->ht, &val->hash);

	list_क्रम_each_entry(val, &ctx->resource_ctx_list, head)
		(व्योम) drm_ht_हटाओ_item(ctx->ht, &val->hash);

	ctx->ht = शून्य;
पूर्ण

/**
 * vmw_validation_unref_lists - Unरेजिस्टर previously रेजिस्टरed buffer
 * object and resources.
 * @ctx: The validation context.
 *
 * Note that this function may cause buffer object- and resource deकाष्ठाors
 * to be invoked.
 */
व्योम vmw_validation_unref_lists(काष्ठा vmw_validation_context *ctx)
अणु
	काष्ठा vmw_validation_bo_node *entry;
	काष्ठा vmw_validation_res_node *val;

	list_क्रम_each_entry(entry, &ctx->bo_list, base.head) अणु
		tपंचांग_bo_put(entry->base.bo);
		entry->base.bo = शून्य;
	पूर्ण

	list_splice_init(&ctx->resource_ctx_list, &ctx->resource_list);
	list_क्रम_each_entry(val, &ctx->resource_list, head)
		vmw_resource_unreference(&val->res);

	/*
	 * No need to detach each list entry since they are all मुक्तd with
	 * vmw_validation_मुक्त_mem. Just make the inaccessible.
	 */
	INIT_LIST_HEAD(&ctx->bo_list);
	INIT_LIST_HEAD(&ctx->resource_list);

	vmw_validation_mem_मुक्त(ctx);
पूर्ण

/**
 * vmw_validation_prepare - Prepare a validation context क्रम command
 * submission.
 * @ctx: The validation context.
 * @mutex: The mutex used to protect resource reservation.
 * @पूर्णांकr: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 *
 * Note that the single reservation mutex @mutex is an unक्रमtunate
 * स्थिरruct. Ideally resource reservation should be moved to per-resource
 * ww_mutexes.
 * If this functions करोesn't वापस Zero to indicate success, all resources
 * are left unreserved but still referenced.
 * Return: Zero on success, -ERESTARTSYS अगर पूर्णांकerrupted, negative error code
 * on error.
 */
पूर्णांक vmw_validation_prepare(काष्ठा vmw_validation_context *ctx,
			   काष्ठा mutex *mutex,
			   bool पूर्णांकr)
अणु
	पूर्णांक ret = 0;

	अगर (mutex) अणु
		अगर (पूर्णांकr)
			ret = mutex_lock_पूर्णांकerruptible(mutex);
		अन्यथा
			mutex_lock(mutex);
		अगर (ret)
			वापस -ERESTARTSYS;
	पूर्ण

	ctx->res_mutex = mutex;
	ret = vmw_validation_res_reserve(ctx, पूर्णांकr);
	अगर (ret)
		जाओ out_no_res_reserve;

	ret = vmw_validation_bo_reserve(ctx, पूर्णांकr);
	अगर (ret)
		जाओ out_no_bo_reserve;

	ret = vmw_validation_bo_validate(ctx, पूर्णांकr);
	अगर (ret)
		जाओ out_no_validate;

	ret = vmw_validation_res_validate(ctx, पूर्णांकr);
	अगर (ret)
		जाओ out_no_validate;

	वापस 0;

out_no_validate:
	vmw_validation_bo_backoff(ctx);
out_no_bo_reserve:
	vmw_validation_res_unreserve(ctx, true);
out_no_res_reserve:
	अगर (mutex)
		mutex_unlock(mutex);

	वापस ret;
पूर्ण

/**
 * vmw_validation_revert - Revert validation actions अगर command submission
 * failed.
 *
 * @ctx: The validation context.
 *
 * The caller still needs to unref resources after a call to this function.
 */
व्योम vmw_validation_revert(काष्ठा vmw_validation_context *ctx)
अणु
	vmw_validation_bo_backoff(ctx);
	vmw_validation_res_unreserve(ctx, true);
	अगर (ctx->res_mutex)
		mutex_unlock(ctx->res_mutex);
	vmw_validation_unref_lists(ctx);
पूर्ण

/**
 * vmw_validation_cone - Commit validation actions after command submission
 * success.
 * @ctx: The validation context.
 * @fence: Fence with which to fence all buffer objects taking part in the
 * command submission.
 *
 * The caller करोes NOT need to unref resources after a call to this function.
 */
व्योम vmw_validation_करोne(काष्ठा vmw_validation_context *ctx,
			 काष्ठा vmw_fence_obj *fence)
अणु
	vmw_validation_bo_fence(ctx, fence);
	vmw_validation_res_unreserve(ctx, false);
	अगर (ctx->res_mutex)
		mutex_unlock(ctx->res_mutex);
	vmw_validation_unref_lists(ctx);
पूर्ण

/**
 * vmw_validation_preload_bo - Preload the validation memory allocator क्रम a
 * call to vmw_validation_add_bo().
 * @ctx: Poपूर्णांकer to the validation context.
 *
 * Iff this function वापसs successfully, the next call to
 * vmw_validation_add_bo() is guaranteed not to sleep. An error is not fatal
 * but व्योमs the guarantee.
 *
 * Returns: Zero अगर successful, %-EINVAL otherwise.
 */
पूर्णांक vmw_validation_preload_bo(काष्ठा vmw_validation_context *ctx)
अणु
	अचिन्हित पूर्णांक size = माप(काष्ठा vmw_validation_bo_node);

	अगर (!vmw_validation_mem_alloc(ctx, size))
		वापस -ENOMEM;

	ctx->mem_size_left += size;
	वापस 0;
पूर्ण

/**
 * vmw_validation_preload_res - Preload the validation memory allocator क्रम a
 * call to vmw_validation_add_res().
 * @ctx: Poपूर्णांकer to the validation context.
 * @size: Size of the validation node extra data. See below.
 *
 * Iff this function वापसs successfully, the next call to
 * vmw_validation_add_res() with the same or smaller @size is guaranteed not to
 * sleep. An error is not fatal but व्योमs the guarantee.
 *
 * Returns: Zero अगर successful, %-EINVAL otherwise.
 */
पूर्णांक vmw_validation_preload_res(काष्ठा vmw_validation_context *ctx,
			       अचिन्हित पूर्णांक size)
अणु
	size = vmw_validation_align(माप(काष्ठा vmw_validation_res_node) +
				    size) +
		vmw_validation_align(माप(काष्ठा vmw_validation_bo_node));
	अगर (!vmw_validation_mem_alloc(ctx, size))
		वापस -ENOMEM;

	ctx->mem_size_left += size;
	वापस 0;
पूर्ण

/**
 * vmw_validation_bo_backoff - Unreserve buffer objects रेजिस्टरed with a
 * validation context
 * @ctx: The validation context
 *
 * This function unreserves the buffer objects previously reserved using
 * vmw_validation_bo_reserve. It's typically used as part of an error path
 */
व्योम vmw_validation_bo_backoff(काष्ठा vmw_validation_context *ctx)
अणु
	काष्ठा vmw_validation_bo_node *entry;

	/*
	 * Switching coherent resource backup buffers failed.
	 * Release corresponding buffer object dirty trackers.
	 */
	list_क्रम_each_entry(entry, &ctx->bo_list, base.head) अणु
		अगर (entry->coherent_count) अणु
			अचिन्हित पूर्णांक coherent_count = entry->coherent_count;
			काष्ठा vmw_buffer_object *vbo =
				container_of(entry->base.bo, typeof(*vbo),
					     base);

			जबतक (coherent_count--)
				vmw_bo_dirty_release(vbo);
		पूर्ण
	पूर्ण

	tपंचांग_eu_backoff_reservation(&ctx->ticket, &ctx->bo_list);
पूर्ण
