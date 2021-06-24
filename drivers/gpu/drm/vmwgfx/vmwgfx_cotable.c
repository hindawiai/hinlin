<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2014-2015 VMware, Inc., Palo Alto, CA., USA
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
/*
 * Treat context OTables as resources to make use of the resource
 * backing MOB eviction mechanism, that is used to पढ़ो back the COTable
 * whenever the backing MOB is evicted.
 */

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"
#समावेश "vmwgfx_so.h"

/**
 * काष्ठा vmw_cotable - Context Object Table resource
 *
 * @res: काष्ठा vmw_resource we are deriving from.
 * @ctx: non-refcounted poपूर्णांकer to the owning context.
 * @size_पढ़ो_back: Size of data पढ़ो back during eviction.
 * @seen_entries: Seen entries in command stream क्रम this cotable.
 * @type: The cotable type.
 * @scrubbed: Whether the cotable has been scrubbed.
 * @resource_list: List of resources in the cotable.
 */
काष्ठा vmw_cotable अणु
	काष्ठा vmw_resource res;
	काष्ठा vmw_resource *ctx;
	माप_प्रकार size_पढ़ो_back;
	पूर्णांक seen_entries;
	u32 type;
	bool scrubbed;
	काष्ठा list_head resource_list;
पूर्ण;

/**
 * काष्ठा vmw_cotable_info - Static info about cotable types
 *
 * @min_initial_entries: Min number of initial पूर्णांकries at cotable allocation
 * क्रम this cotable type.
 * @size: Size of each entry.
 * @unbind_func: Unbind call-back function.
 */
काष्ठा vmw_cotable_info अणु
	u32 min_initial_entries;
	u32 size;
	व्योम (*unbind_func)(काष्ठा vmw_निजी *, काष्ठा list_head *,
			    bool);
पूर्ण;

अटल स्थिर काष्ठा vmw_cotable_info co_info[] = अणु
	अणु1, माप(SVGACOTableDXRTViewEntry), &vmw_view_cotable_list_destroyपूर्ण,
	अणु1, माप(SVGACOTableDXDSViewEntry), &vmw_view_cotable_list_destroyपूर्ण,
	अणु1, माप(SVGACOTableDXSRViewEntry), &vmw_view_cotable_list_destroyपूर्ण,
	अणु1, माप(SVGACOTableDXElementLayoutEntry), शून्यपूर्ण,
	अणु1, माप(SVGACOTableDXBlendStateEntry), शून्यपूर्ण,
	अणु1, माप(SVGACOTableDXDepthStencilEntry), शून्यपूर्ण,
	अणु1, माप(SVGACOTableDXRasterizerStateEntry), शून्यपूर्ण,
	अणु1, माप(SVGACOTableDXSamplerEntry), शून्यपूर्ण,
	अणु1, माप(SVGACOTableDXStreamOutputEntry), &vmw_dx_streamoutput_cotable_list_scrubपूर्ण,
	अणु1, माप(SVGACOTableDXQueryEntry), शून्यपूर्ण,
	अणु1, माप(SVGACOTableDXShaderEntry), &vmw_dx_shader_cotable_list_scrubपूर्ण,
	अणु1, माप(SVGACOTableDXUAViewEntry), &vmw_view_cotable_list_destroyपूर्ण
पूर्ण;

/*
 * Cotables with bindings that we हटाओ must be scrubbed first,
 * otherwise, the device will swap in an invalid context when we हटाओ
 * bindings beक्रमe scrubbing a cotable...
 */
स्थिर SVGACOTableType vmw_cotable_scrub_order[] = अणु
	SVGA_COTABLE_RTVIEW,
	SVGA_COTABLE_DSVIEW,
	SVGA_COTABLE_SRVIEW,
	SVGA_COTABLE_DXSHADER,
	SVGA_COTABLE_ELEMENTLAYOUT,
	SVGA_COTABLE_BLENDSTATE,
	SVGA_COTABLE_DEPTHSTENCIL,
	SVGA_COTABLE_RASTERIZERSTATE,
	SVGA_COTABLE_SAMPLER,
	SVGA_COTABLE_STREAMOUTPUT,
	SVGA_COTABLE_DXQUERY,
	SVGA_COTABLE_UAVIEW,
पूर्ण;

अटल पूर्णांक vmw_cotable_bind(काष्ठा vmw_resource *res,
			    काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_cotable_unbind(काष्ठा vmw_resource *res,
			      bool पढ़ोback,
			      काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_cotable_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_cotable_destroy(काष्ठा vmw_resource *res);

अटल स्थिर काष्ठा vmw_res_func vmw_cotable_func = अणु
	.res_type = vmw_res_cotable,
	.needs_backup = true,
	.may_evict = true,
	.prio = 3,
	.dirty_prio = 3,
	.type_name = "context guest backed object tables",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_cotable_create,
	.destroy = vmw_cotable_destroy,
	.bind = vmw_cotable_bind,
	.unbind = vmw_cotable_unbind,
पूर्ण;

/**
 * vmw_cotable - Convert a काष्ठा vmw_resource poपूर्णांकer to a काष्ठा
 * vmw_cotable poपूर्णांकer
 *
 * @res: Poपूर्णांकer to the resource.
 */
अटल काष्ठा vmw_cotable *vmw_cotable(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_cotable, res);
पूर्ण

/**
 * vmw_cotable_destroy - Cotable resource destroy callback
 *
 * @res: Poपूर्णांकer to the cotable resource.
 *
 * There is no device cotable destroy command, so this function only
 * makes sure that the resource id is set to invalid.
 */
अटल पूर्णांक vmw_cotable_destroy(काष्ठा vmw_resource *res)
अणु
	res->id = -1;
	वापस 0;
पूर्ण

/**
 * vmw_cotable_unscrub - Unकरो a cotable unscrub operation
 *
 * @res: Poपूर्णांकer to the cotable resource
 *
 * This function issues commands to (re)bind the cotable to
 * its backing mob, which needs to be validated and reserved at this poपूर्णांक.
 * This is identical to bind() except the function पूर्णांकerface looks dअगरferent.
 */
अटल पूर्णांक vmw_cotable_unscrub(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = &res->backup->base;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetCOTable body;
	पूर्ण *cmd;

	WARN_ON_ONCE(bo->mem.mem_type != VMW_PL_MOB);
	dma_resv_निश्चित_held(bo->base.resv);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;

	WARN_ON(vcotbl->ctx->id == SVGA3D_INVALID_ID);
	WARN_ON(bo->mem.mem_type != VMW_PL_MOB);
	cmd->header.id = SVGA_3D_CMD_DX_SET_COTABLE;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = vcotbl->ctx->id;
	cmd->body.type = vcotbl->type;
	cmd->body.mobid = bo->mem.start;
	cmd->body.validSizeInBytes = vcotbl->size_पढ़ो_back;

	vmw_cmd_commit_flush(dev_priv, माप(*cmd));
	vcotbl->scrubbed = false;

	वापस 0;
पूर्ण

/**
 * vmw_cotable_bind - Unकरो a cotable unscrub operation
 *
 * @res: Poपूर्णांकer to the cotable resource
 * @val_buf: Poपूर्णांकer to a काष्ठा tपंचांग_validate_buffer prepared by the caller
 * क्रम convenience / fencing.
 *
 * This function issues commands to (re)bind the cotable to
 * its backing mob, which needs to be validated and reserved at this poपूर्णांक.
 */
अटल पूर्णांक vmw_cotable_bind(काष्ठा vmw_resource *res,
			    काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	/*
	 * The create() callback may have changed @res->backup without
	 * the caller noticing, and with val_buf->bo still poपूर्णांकing to
	 * the old backup buffer. Although hackish, and not used currently,
	 * take the opportunity to correct the value here so that it's not
	 * misused in the future.
	 */
	val_buf->bo = &res->backup->base;

	वापस vmw_cotable_unscrub(res);
पूर्ण

/**
 * vmw_cotable_scrub - Scrub the cotable from the device.
 *
 * @res: Poपूर्णांकer to the cotable resource.
 * @पढ़ोback: Whether initiate a पढ़ोback of the cotable data to the backup
 * buffer.
 *
 * In some situations (context swapouts) it might be desirable to make the
 * device क्रमget about the cotable without perक्रमming a full unbind. A full
 * unbind requires reserved backup buffers and it might not be possible to
 * reserve them due to locking order violation issues. The vmw_cotable_scrub
 * function implements a partial unbind() without that requirement but with the
 * following restrictions.
 * 1) Beक्रमe the cotable is again used by the GPU, vmw_cotable_unscrub() must
 *    be called.
 * 2) Beक्रमe the cotable backing buffer is used by the CPU, or during the
 *    resource deकाष्ठाion, vmw_cotable_unbind() must be called.
 */
पूर्णांक vmw_cotable_scrub(काष्ठा vmw_resource *res, bool पढ़ोback)
अणु
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	माप_प्रकार submit_size;

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXReadbackCOTable body;
	पूर्ण *cmd0;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetCOTable body;
	पूर्ण *cmd1;

	अगर (vcotbl->scrubbed)
		वापस 0;

	अगर (co_info[vcotbl->type].unbind_func)
		co_info[vcotbl->type].unbind_func(dev_priv,
						  &vcotbl->resource_list,
						  पढ़ोback);
	submit_size = माप(*cmd1);
	अगर (पढ़ोback)
		submit_size += माप(*cmd0);

	cmd1 = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (!cmd1)
		वापस -ENOMEM;

	vcotbl->size_पढ़ो_back = 0;
	अगर (पढ़ोback) अणु
		cmd0 = (व्योम *) cmd1;
		cmd0->header.id = SVGA_3D_CMD_DX_READBACK_COTABLE;
		cmd0->header.size = माप(cmd0->body);
		cmd0->body.cid = vcotbl->ctx->id;
		cmd0->body.type = vcotbl->type;
		cmd1 = (व्योम *) &cmd0[1];
		vcotbl->size_पढ़ो_back = res->backup_size;
	पूर्ण
	cmd1->header.id = SVGA_3D_CMD_DX_SET_COTABLE;
	cmd1->header.size = माप(cmd1->body);
	cmd1->body.cid = vcotbl->ctx->id;
	cmd1->body.type = vcotbl->type;
	cmd1->body.mobid = SVGA3D_INVALID_ID;
	cmd1->body.validSizeInBytes = 0;
	vmw_cmd_commit_flush(dev_priv, submit_size);
	vcotbl->scrubbed = true;

	/* Trigger a create() on next validate. */
	res->id = -1;

	वापस 0;
पूर्ण

/**
 * vmw_cotable_unbind - Cotable resource unbind callback
 *
 * @res: Poपूर्णांकer to the cotable resource.
 * @पढ़ोback: Whether to पढ़ो back cotable data to the backup buffer.
 * @val_buf: Poपूर्णांकer to a काष्ठा tपंचांग_validate_buffer prepared by the caller
 * क्रम convenience / fencing.
 *
 * Unbinds the cotable from the device and fences the backup buffer.
 */
अटल पूर्णांक vmw_cotable_unbind(काष्ठा vmw_resource *res,
			      bool पढ़ोback,
			      काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;
	काष्ठा vmw_fence_obj *fence;

	अगर (!vmw_resource_mob_attached(res))
		वापस 0;

	WARN_ON_ONCE(bo->mem.mem_type != VMW_PL_MOB);
	dma_resv_निश्चित_held(bo->base.resv);

	mutex_lock(&dev_priv->binding_mutex);
	अगर (!vcotbl->scrubbed)
		vmw_dx_context_scrub_cotables(vcotbl->ctx, पढ़ोback);
	mutex_unlock(&dev_priv->binding_mutex);
	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv, &fence, शून्य);
	vmw_bo_fence_single(bo, fence);
	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

/**
 * vmw_cotable_पढ़ोback - Read back a cotable without unbinding.
 *
 * @res: The cotable resource.
 *
 * Reads back a cotable to its backing mob without scrubbing the MOB from
 * the cotable. The MOB is fenced क्रम subsequent CPU access.
 */
अटल पूर्णांक vmw_cotable_पढ़ोback(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXReadbackCOTable body;
	पूर्ण *cmd;
	काष्ठा vmw_fence_obj *fence;

	अगर (!vcotbl->scrubbed) अणु
		cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
		अगर (!cmd)
			वापस -ENOMEM;

		cmd->header.id = SVGA_3D_CMD_DX_READBACK_COTABLE;
		cmd->header.size = माप(cmd->body);
		cmd->body.cid = vcotbl->ctx->id;
		cmd->body.type = vcotbl->type;
		vcotbl->size_पढ़ो_back = res->backup_size;
		vmw_cmd_commit(dev_priv, माप(*cmd));
	पूर्ण

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv, &fence, शून्य);
	vmw_bo_fence_single(&res->backup->base, fence);
	vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

/**
 * vmw_cotable_resize - Resize a cotable.
 *
 * @res: The cotable resource.
 * @new_size: The new size.
 *
 * Resizes a cotable and binds the new backup buffer.
 * On failure the cotable is left पूर्णांकact.
 * Important! This function may not fail once the MOB चयन has been
 * committed to hardware. That would put the device context in an
 * invalid state which we can't currently recover from.
 */
अटल पूर्णांक vmw_cotable_resize(काष्ठा vmw_resource *res, माप_प्रकार new_size)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);
	काष्ठा vmw_buffer_object *buf, *old_buf = res->backup;
	काष्ठा tपंचांग_buffer_object *bo, *old_bo = &res->backup->base;
	माप_प्रकार old_size = res->backup_size;
	माप_प्रकार old_size_पढ़ो_back = vcotbl->size_पढ़ो_back;
	माप_प्रकार cur_size_पढ़ो_back;
	काष्ठा tपंचांग_bo_kmap_obj old_map, new_map;
	पूर्णांक ret;
	माप_प्रकार i;

	ret = vmw_cotable_पढ़ोback(res);
	अगर (ret)
		वापस ret;

	cur_size_पढ़ो_back = vcotbl->size_पढ़ो_back;
	vcotbl->size_पढ़ो_back = old_size_पढ़ो_back;

	/*
	 * While device is processing, Allocate and reserve a buffer object
	 * क्रम the new COTable. Initially pin the buffer object to make sure
	 * we can use tryreserve without failure.
	 */
	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = vmw_bo_init(dev_priv, buf, new_size, &vmw_mob_placement,
			  true, true, vmw_bo_bo_मुक्त);
	अगर (ret) अणु
		DRM_ERROR("Failed initializing new cotable MOB.\n");
		वापस ret;
	पूर्ण

	bo = &buf->base;
	WARN_ON_ONCE(tपंचांग_bo_reserve(bo, false, true, शून्य));

	ret = tपंचांग_bo_रुको(old_bo, false, false);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed waiting for cotable unbind.\n");
		जाओ out_रुको;
	पूर्ण

	/*
	 * Do a page by page copy of COTables. This eliminates slow vmap()s.
	 * This should really be a TTM utility.
	 */
	क्रम (i = 0; i < old_bo->mem.num_pages; ++i) अणु
		bool dummy;

		ret = tपंचांग_bo_kmap(old_bo, i, 1, &old_map);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Failed mapping old COTable on resize.\n");
			जाओ out_रुको;
		पूर्ण
		ret = tपंचांग_bo_kmap(bo, i, 1, &new_map);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Failed mapping new COTable on resize.\n");
			जाओ out_map_new;
		पूर्ण
		स_नकल(tपंचांग_kmap_obj_भव(&new_map, &dummy),
		       tपंचांग_kmap_obj_भव(&old_map, &dummy),
		       PAGE_SIZE);
		tपंचांग_bo_kunmap(&new_map);
		tपंचांग_bo_kunmap(&old_map);
	पूर्ण

	/* Unpin new buffer, and चयन backup buffers. */
	ret = tपंचांग_bo_validate(bo, &vmw_mob_placement, &ctx);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed validating new COTable backup buffer.\n");
		जाओ out_रुको;
	पूर्ण

	vmw_resource_mob_detach(res);
	res->backup = buf;
	res->backup_size = new_size;
	vcotbl->size_पढ़ो_back = cur_size_पढ़ो_back;

	/*
	 * Now tell the device to चयन. If this fails, then we need to
	 * revert the full resize.
	 */
	ret = vmw_cotable_unscrub(res);
	अगर (ret) अणु
		DRM_ERROR("Failed switching COTable backup buffer.\n");
		res->backup = old_buf;
		res->backup_size = old_size;
		vcotbl->size_पढ़ो_back = old_size_पढ़ो_back;
		vmw_resource_mob_attach(res);
		जाओ out_रुको;
	पूर्ण

	vmw_resource_mob_attach(res);
	/* Let go of the old mob. */
	vmw_bo_unreference(&old_buf);
	res->id = vcotbl->type;

	/* Release the pin acquired in vmw_bo_init */
	tपंचांग_bo_unpin(bo);

	वापस 0;

out_map_new:
	tपंचांग_bo_kunmap(&old_map);
out_रुको:
	tपंचांग_bo_unpin(bo);
	tपंचांग_bo_unreserve(bo);
	vmw_bo_unreference(&buf);

	वापस ret;
पूर्ण

/**
 * vmw_cotable_create - Cotable resource create callback
 *
 * @res: Poपूर्णांकer to a cotable resource.
 *
 * There is no separate create command क्रम cotables, so this callback, which
 * is called beक्रमe bind() in the validation sequence is instead used क्रम two
 * things.
 * 1) Unscrub the cotable अगर it is scrubbed and still attached to a backup
 *    buffer.
 * 2) Resize the cotable अगर needed.
 */
अटल पूर्णांक vmw_cotable_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);
	माप_प्रकार new_size = res->backup_size;
	माप_प्रकार needed_size;
	पूर्णांक ret;

	/* Check whether we need to resize the cotable */
	needed_size = (vcotbl->seen_entries + 1) * co_info[vcotbl->type].size;
	जबतक (needed_size > new_size)
		new_size *= 2;

	अगर (likely(new_size <= res->backup_size)) अणु
		अगर (vcotbl->scrubbed && vmw_resource_mob_attached(res)) अणु
			ret = vmw_cotable_unscrub(res);
			अगर (ret)
				वापस ret;
		पूर्ण
		res->id = vcotbl->type;
		वापस 0;
	पूर्ण

	वापस vmw_cotable_resize(res, new_size);
पूर्ण

/**
 * vmw_hw_cotable_destroy - Cotable hw_destroy callback
 *
 * @res: Poपूर्णांकer to a cotable resource.
 *
 * The final (part of resource deकाष्ठाion) destroy callback.
 */
अटल व्योम vmw_hw_cotable_destroy(काष्ठा vmw_resource *res)
अणु
	(व्योम) vmw_cotable_destroy(res);
पूर्ण

अटल माप_प्रकार cotable_acc_size;

/**
 * vmw_cotable_मुक्त - Cotable resource deकाष्ठाor
 *
 * @res: Poपूर्णांकer to a cotable resource.
 */
अटल व्योम vmw_cotable_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	kमुक्त(res);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), cotable_acc_size);
पूर्ण

/**
 * vmw_cotable_alloc - Create a cotable resource
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @ctx: Poपूर्णांकer to the context resource.
 * The cotable resource will not add a refcount.
 * @type: The cotable type.
 */
काष्ठा vmw_resource *vmw_cotable_alloc(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_resource *ctx,
				       u32 type)
अणु
	काष्ठा vmw_cotable *vcotbl;
	काष्ठा tपंचांग_operation_ctx tपंचांग_opt_ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;
	u32 num_entries;

	अगर (unlikely(cotable_acc_size == 0))
		cotable_acc_size = tपंचांग_round_pot(माप(काष्ठा vmw_cotable));

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   cotable_acc_size, &tपंचांग_opt_ctx);
	अगर (unlikely(ret))
		वापस ERR_PTR(ret);

	vcotbl = kzalloc(माप(*vcotbl), GFP_KERNEL);
	अगर (unlikely(!vcotbl)) अणु
		ret = -ENOMEM;
		जाओ out_no_alloc;
	पूर्ण

	ret = vmw_resource_init(dev_priv, &vcotbl->res, true,
				vmw_cotable_मुक्त, &vmw_cotable_func);
	अगर (unlikely(ret != 0))
		जाओ out_no_init;

	INIT_LIST_HEAD(&vcotbl->resource_list);
	vcotbl->res.id = type;
	vcotbl->res.backup_size = PAGE_SIZE;
	num_entries = PAGE_SIZE / co_info[type].size;
	अगर (num_entries < co_info[type].min_initial_entries) अणु
		vcotbl->res.backup_size = co_info[type].min_initial_entries *
			co_info[type].size;
		vcotbl->res.backup_size =
			(vcotbl->res.backup_size + PAGE_SIZE - 1) & PAGE_MASK;
	पूर्ण

	vcotbl->scrubbed = true;
	vcotbl->seen_entries = -1;
	vcotbl->type = type;
	vcotbl->ctx = ctx;

	vcotbl->res.hw_destroy = vmw_hw_cotable_destroy;

	वापस &vcotbl->res;

out_no_init:
	kमुक्त(vcotbl);
out_no_alloc:
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), cotable_acc_size);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * vmw_cotable_notअगरy - Notअगरy the cotable about an item creation
 *
 * @res: Poपूर्णांकer to a cotable resource.
 * @id: Item id.
 */
पूर्णांक vmw_cotable_notअगरy(काष्ठा vmw_resource *res, पूर्णांक id)
अणु
	काष्ठा vmw_cotable *vcotbl = vmw_cotable(res);

	अगर (id < 0 || id >= SVGA_COTABLE_MAX_IDS) अणु
		DRM_ERROR("Illegal COTable id. Type is %u. Id is %d\n",
			  (अचिन्हित) vcotbl->type, id);
		वापस -EINVAL;
	पूर्ण

	अगर (vcotbl->seen_entries < id) अणु
		/* Trigger a call to create() on next validate */
		res->id = -1;
		vcotbl->seen_entries = id;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_cotable_add_view - add a view to the cotable's list of active views.
 *
 * @res: poपूर्णांकer काष्ठा vmw_resource representing the cotable.
 * @head: poपूर्णांकer to the काष्ठा list_head member of the resource, dedicated
 * to the cotable active resource list.
 */
व्योम vmw_cotable_add_resource(काष्ठा vmw_resource *res, काष्ठा list_head *head)
अणु
	काष्ठा vmw_cotable *vcotbl =
		container_of(res, काष्ठा vmw_cotable, res);

	list_add_tail(head, &vcotbl->resource_list);
पूर्ण
