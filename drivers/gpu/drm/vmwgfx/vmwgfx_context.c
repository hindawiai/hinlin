<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"
#समावेश "vmwgfx_binding.h"

काष्ठा vmw_user_context अणु
	काष्ठा tपंचांग_base_object base;
	काष्ठा vmw_resource res;
	काष्ठा vmw_ctx_binding_state *cbs;
	काष्ठा vmw_cmdbuf_res_manager *man;
	काष्ठा vmw_resource *cotables[SVGA_COTABLE_MAX];
	spinlock_t cotable_lock;
	काष्ठा vmw_buffer_object *dx_query_mob;
पूर्ण;

अटल व्योम vmw_user_context_मुक्त(काष्ठा vmw_resource *res);
अटल काष्ठा vmw_resource *
vmw_user_context_base_to_res(काष्ठा tपंचांग_base_object *base);

अटल पूर्णांक vmw_gb_context_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_gb_context_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_gb_context_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_gb_context_destroy(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_dx_context_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_dx_context_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_dx_context_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_dx_context_destroy(काष्ठा vmw_resource *res);

अटल uपूर्णांक64_t vmw_user_context_size;

अटल स्थिर काष्ठा vmw_user_resource_conv user_context_conv = अणु
	.object_type = VMW_RES_CONTEXT,
	.base_obj_to_res = vmw_user_context_base_to_res,
	.res_मुक्त = vmw_user_context_मुक्त
पूर्ण;

स्थिर काष्ठा vmw_user_resource_conv *user_context_converter =
	&user_context_conv;


अटल स्थिर काष्ठा vmw_res_func vmw_legacy_context_func = अणु
	.res_type = vmw_res_context,
	.needs_backup = false,
	.may_evict = false,
	.type_name = "legacy contexts",
	.backup_placement = शून्य,
	.create = शून्य,
	.destroy = शून्य,
	.bind = शून्य,
	.unbind = शून्य
पूर्ण;

अटल स्थिर काष्ठा vmw_res_func vmw_gb_context_func = अणु
	.res_type = vmw_res_context,
	.needs_backup = true,
	.may_evict = true,
	.prio = 3,
	.dirty_prio = 3,
	.type_name = "guest backed contexts",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_gb_context_create,
	.destroy = vmw_gb_context_destroy,
	.bind = vmw_gb_context_bind,
	.unbind = vmw_gb_context_unbind
पूर्ण;

अटल स्थिर काष्ठा vmw_res_func vmw_dx_context_func = अणु
	.res_type = vmw_res_dx_context,
	.needs_backup = true,
	.may_evict = true,
	.prio = 3,
	.dirty_prio = 3,
	.type_name = "dx contexts",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_dx_context_create,
	.destroy = vmw_dx_context_destroy,
	.bind = vmw_dx_context_bind,
	.unbind = vmw_dx_context_unbind
पूर्ण;

/*
 * Context management:
 */

अटल व्योम vmw_context_cotables_unref(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_user_context *uctx)
अणु
	काष्ठा vmw_resource *res;
	पूर्णांक i;
	u32 cotable_max = has_sm5_context(dev_priv) ?
		SVGA_COTABLE_MAX : SVGA_COTABLE_DX10_MAX;

	क्रम (i = 0; i < cotable_max; ++i) अणु
		spin_lock(&uctx->cotable_lock);
		res = uctx->cotables[i];
		uctx->cotables[i] = शून्य;
		spin_unlock(&uctx->cotable_lock);

		अगर (res)
			vmw_resource_unreference(&res);
	पूर्ण
पूर्ण

अटल व्योम vmw_hw_context_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_user_context *uctx =
		container_of(res, काष्ठा vmw_user_context, res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDestroyContext body;
	पूर्ण *cmd;


	अगर (res->func->destroy == vmw_gb_context_destroy ||
	    res->func->destroy == vmw_dx_context_destroy) अणु
		mutex_lock(&dev_priv->cmdbuf_mutex);
		vmw_cmdbuf_res_man_destroy(uctx->man);
		mutex_lock(&dev_priv->binding_mutex);
		vmw_binding_state_समाप्त(uctx->cbs);
		(व्योम) res->func->destroy(res);
		mutex_unlock(&dev_priv->binding_mutex);
		अगर (dev_priv->pinned_bo != शून्य &&
		    !dev_priv->query_cid_valid)
			__vmw_execbuf_release_pinned_bo(dev_priv, शून्य);
		mutex_unlock(&dev_priv->cmdbuf_mutex);
		vmw_context_cotables_unref(dev_priv, uctx);
		वापस;
	पूर्ण

	vmw_execbuf_release_pinned_bo(dev_priv);
	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस;

	cmd->header.id = SVGA_3D_CMD_CONTEXT_DESTROY;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;

	vmw_cmd_commit(dev_priv, माप(*cmd));
	vmw_fअगरo_resource_dec(dev_priv);
पूर्ण

अटल पूर्णांक vmw_gb_context_init(काष्ठा vmw_निजी *dev_priv,
			       bool dx,
			       काष्ठा vmw_resource *res,
			       व्योम (*res_मुक्त)(काष्ठा vmw_resource *res))
अणु
	पूर्णांक ret, i;
	काष्ठा vmw_user_context *uctx =
		container_of(res, काष्ठा vmw_user_context, res);

	res->backup_size = (dx ? माप(SVGADXContextMobFormat) :
			    SVGA3D_CONTEXT_DATA_SIZE);
	ret = vmw_resource_init(dev_priv, res, true,
				res_मुक्त,
				dx ? &vmw_dx_context_func :
				&vmw_gb_context_func);
	अगर (unlikely(ret != 0))
		जाओ out_err;

	अगर (dev_priv->has_mob) अणु
		uctx->man = vmw_cmdbuf_res_man_create(dev_priv);
		अगर (IS_ERR(uctx->man)) अणु
			ret = PTR_ERR(uctx->man);
			uctx->man = शून्य;
			जाओ out_err;
		पूर्ण
	पूर्ण

	uctx->cbs = vmw_binding_state_alloc(dev_priv);
	अगर (IS_ERR(uctx->cbs)) अणु
		ret = PTR_ERR(uctx->cbs);
		जाओ out_err;
	पूर्ण

	spin_lock_init(&uctx->cotable_lock);

	अगर (dx) अणु
		u32 cotable_max = has_sm5_context(dev_priv) ?
			SVGA_COTABLE_MAX : SVGA_COTABLE_DX10_MAX;
		क्रम (i = 0; i < cotable_max; ++i) अणु
			uctx->cotables[i] = vmw_cotable_alloc(dev_priv,
							      &uctx->res, i);
			अगर (IS_ERR(uctx->cotables[i])) अणु
				ret = PTR_ERR(uctx->cotables[i]);
				जाओ out_cotables;
			पूर्ण
		पूर्ण
	पूर्ण

	res->hw_destroy = vmw_hw_context_destroy;
	वापस 0;

out_cotables:
	vmw_context_cotables_unref(dev_priv, uctx);
out_err:
	अगर (res_मुक्त)
		res_मुक्त(res);
	अन्यथा
		kमुक्त(res);
	वापस ret;
पूर्ण

अटल पूर्णांक vmw_context_init(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_resource *res,
			    व्योम (*res_मुक्त)(काष्ठा vmw_resource *res),
			    bool dx)
अणु
	पूर्णांक ret;

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineContext body;
	पूर्ण *cmd;

	अगर (dev_priv->has_mob)
		वापस vmw_gb_context_init(dev_priv, dx, res, res_मुक्त);

	ret = vmw_resource_init(dev_priv, res, false,
				res_मुक्त, &vmw_legacy_context_func);

	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate a resource id.\n");
		जाओ out_early;
	पूर्ण

	अगर (unlikely(res->id >= SVGA3D_MAX_CONTEXT_IDS)) अणु
		DRM_ERROR("Out of hw context ids.\n");
		vmw_resource_unreference(&res);
		वापस -ENOMEM;
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य)) अणु
		vmw_resource_unreference(&res);
		वापस -ENOMEM;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_CONTEXT_DEFINE;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;

	vmw_cmd_commit(dev_priv, माप(*cmd));
	vmw_fअगरo_resource_inc(dev_priv);
	res->hw_destroy = vmw_hw_context_destroy;
	वापस 0;

out_early:
	अगर (res_मुक्त == शून्य)
		kमुक्त(res);
	अन्यथा
		res_मुक्त(res);
	वापस ret;
पूर्ण


/*
 * GB context.
 */

अटल पूर्णांक vmw_gb_context_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBContext body;
	पूर्ण *cmd;

	अगर (likely(res->id != -1))
		वापस 0;

	ret = vmw_resource_alloc_id(res);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate a context id.\n");
		जाओ out_no_id;
	पूर्ण

	अगर (unlikely(res->id >= VMWGFX_NUM_GB_CONTEXT)) अणु
		ret = -EBUSY;
		जाओ out_no_fअगरo;
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य)) अणु
		ret = -ENOMEM;
		जाओ out_no_fअगरo;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_DEFINE_GB_CONTEXT;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	vmw_fअगरo_resource_inc(dev_priv);

	वापस 0;

out_no_fअगरo:
	vmw_resource_release_id(res);
out_no_id:
	वापस ret;
पूर्ण

अटल पूर्णांक vmw_gb_context_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBContext body;
	पूर्ण *cmd;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;

	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_BIND_GB_CONTEXT;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;
	cmd->body.mobid = bo->mem.start;
	cmd->body.validContents = res->backup_dirty;
	res->backup_dirty = false;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_gb_context_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;
	काष्ठा vmw_fence_obj *fence;
	काष्ठा vmw_user_context *uctx =
		container_of(res, काष्ठा vmw_user_context, res);

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdReadbackGBContext body;
	पूर्ण *cmd1;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBContext body;
	पूर्ण *cmd2;
	uपूर्णांक32_t submit_size;
	uपूर्णांक8_t *cmd;


	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	mutex_lock(&dev_priv->binding_mutex);
	vmw_binding_state_scrub(uctx->cbs);

	submit_size = माप(*cmd2) + (पढ़ोback ? माप(*cmd1) : 0);

	cmd = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(cmd == शून्य)) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस -ENOMEM;
	पूर्ण

	cmd2 = (व्योम *) cmd;
	अगर (पढ़ोback) अणु
		cmd1 = (व्योम *) cmd;
		cmd1->header.id = SVGA_3D_CMD_READBACK_GB_CONTEXT;
		cmd1->header.size = माप(cmd1->body);
		cmd1->body.cid = res->id;
		cmd2 = (व्योम *) (&cmd1[1]);
	पूर्ण
	cmd2->header.id = SVGA_3D_CMD_BIND_GB_CONTEXT;
	cmd2->header.size = माप(cmd2->body);
	cmd2->body.cid = res->id;
	cmd2->body.mobid = SVGA3D_INVALID_ID;

	vmw_cmd_commit(dev_priv, submit_size);
	mutex_unlock(&dev_priv->binding_mutex);

	/*
	 * Create a fence object and fence the backup buffer.
	 */

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv,
					  &fence, शून्य);

	vmw_bo_fence_single(bo, fence);

	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_gb_context_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDestroyGBContext body;
	पूर्ण *cmd;

	अगर (likely(res->id == -1))
		वापस 0;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DESTROY_GB_CONTEXT;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	अगर (dev_priv->query_cid == res->id)
		dev_priv->query_cid_valid = false;
	vmw_resource_release_id(res);
	vmw_fअगरo_resource_dec(dev_priv);

	वापस 0;
पूर्ण

/*
 * DX context.
 */

अटल पूर्णांक vmw_dx_context_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDefineContext body;
	पूर्ण *cmd;

	अगर (likely(res->id != -1))
		वापस 0;

	ret = vmw_resource_alloc_id(res);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate a context id.\n");
		जाओ out_no_id;
	पूर्ण

	अगर (unlikely(res->id >= VMWGFX_NUM_DXCONTEXT)) अणु
		ret = -EBUSY;
		जाओ out_no_fअगरo;
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य)) अणु
		ret = -ENOMEM;
		जाओ out_no_fअगरo;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_DX_DEFINE_CONTEXT;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	vmw_fअगरo_resource_inc(dev_priv);

	वापस 0;

out_no_fअगरo:
	vmw_resource_release_id(res);
out_no_id:
	वापस ret;
पूर्ण

अटल पूर्णांक vmw_dx_context_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindContext body;
	पूर्ण *cmd;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;

	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_BIND_CONTEXT;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;
	cmd->body.mobid = bo->mem.start;
	cmd->body.validContents = res->backup_dirty;
	res->backup_dirty = false;
	vmw_cmd_commit(dev_priv, माप(*cmd));


	वापस 0;
पूर्ण

/**
 * vmw_dx_context_scrub_cotables - Scrub all bindings and
 * cotables from a context
 *
 * @ctx: Poपूर्णांकer to the context resource
 * @पढ़ोback: Whether to save the otable contents on scrubbing.
 *
 * COtables must be unbound beक्रमe their context, but unbinding requires
 * the backup buffer being reserved, whereas scrubbing करोes not.
 * This function scrubs all cotables of a context, potentially पढ़ोing back
 * the contents पूर्णांकo their backup buffers. However, scrubbing cotables
 * also makes the device context invalid, so scrub all bindings first so
 * that करोesn't have to be करोne later with an invalid context.
 */
व्योम vmw_dx_context_scrub_cotables(काष्ठा vmw_resource *ctx,
				   bool पढ़ोback)
अणु
	काष्ठा vmw_user_context *uctx =
		container_of(ctx, काष्ठा vmw_user_context, res);
	u32 cotable_max = has_sm5_context(ctx->dev_priv) ?
		SVGA_COTABLE_MAX : SVGA_COTABLE_DX10_MAX;
	पूर्णांक i;

	vmw_binding_state_scrub(uctx->cbs);
	क्रम (i = 0; i < cotable_max; ++i) अणु
		काष्ठा vmw_resource *res;

		/* Aव्योम racing with ongoing cotable deकाष्ठाion. */
		spin_lock(&uctx->cotable_lock);
		res = uctx->cotables[vmw_cotable_scrub_order[i]];
		अगर (res)
			res = vmw_resource_reference_unless_करोomed(res);
		spin_unlock(&uctx->cotable_lock);
		अगर (!res)
			जारी;

		WARN_ON(vmw_cotable_scrub(res, पढ़ोback));
		vmw_resource_unreference(&res);
	पूर्ण
पूर्ण

अटल पूर्णांक vmw_dx_context_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;
	काष्ठा vmw_fence_obj *fence;
	काष्ठा vmw_user_context *uctx =
		container_of(res, काष्ठा vmw_user_context, res);

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXReadbackContext body;
	पूर्ण *cmd1;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindContext body;
	पूर्ण *cmd2;
	uपूर्णांक32_t submit_size;
	uपूर्णांक8_t *cmd;


	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	mutex_lock(&dev_priv->binding_mutex);
	vmw_dx_context_scrub_cotables(res, पढ़ोback);

	अगर (uctx->dx_query_mob && uctx->dx_query_mob->dx_query_ctx &&
	    पढ़ोback) अणु
		WARN_ON(uctx->dx_query_mob->dx_query_ctx != res);
		अगर (vmw_query_पढ़ोback_all(uctx->dx_query_mob))
			DRM_ERROR("Failed to read back query states\n");
	पूर्ण

	submit_size = माप(*cmd2) + (पढ़ोback ? माप(*cmd1) : 0);

	cmd = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(cmd == शून्य)) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस -ENOMEM;
	पूर्ण

	cmd2 = (व्योम *) cmd;
	अगर (पढ़ोback) अणु
		cmd1 = (व्योम *) cmd;
		cmd1->header.id = SVGA_3D_CMD_DX_READBACK_CONTEXT;
		cmd1->header.size = माप(cmd1->body);
		cmd1->body.cid = res->id;
		cmd2 = (व्योम *) (&cmd1[1]);
	पूर्ण
	cmd2->header.id = SVGA_3D_CMD_DX_BIND_CONTEXT;
	cmd2->header.size = माप(cmd2->body);
	cmd2->body.cid = res->id;
	cmd2->body.mobid = SVGA3D_INVALID_ID;

	vmw_cmd_commit(dev_priv, submit_size);
	mutex_unlock(&dev_priv->binding_mutex);

	/*
	 * Create a fence object and fence the backup buffer.
	 */

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv,
					  &fence, शून्य);

	vmw_bo_fence_single(bo, fence);

	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_dx_context_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDestroyContext body;
	पूर्ण *cmd;

	अगर (likely(res->id == -1))
		वापस 0;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_DESTROY_CONTEXT;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = res->id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	अगर (dev_priv->query_cid == res->id)
		dev_priv->query_cid_valid = false;
	vmw_resource_release_id(res);
	vmw_fअगरo_resource_dec(dev_priv);

	वापस 0;
पूर्ण

/*
 * User-space context management:
 */

अटल काष्ठा vmw_resource *
vmw_user_context_base_to_res(काष्ठा tपंचांग_base_object *base)
अणु
	वापस &(container_of(base, काष्ठा vmw_user_context, base)->res);
पूर्ण

अटल व्योम vmw_user_context_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_user_context *ctx =
	    container_of(res, काष्ठा vmw_user_context, res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	अगर (ctx->cbs)
		vmw_binding_state_मुक्त(ctx->cbs);

	(व्योम) vmw_context_bind_dx_query(res, शून्य);

	tपंचांग_base_object_kमुक्त(ctx, base);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
			    vmw_user_context_size);
पूर्ण

/*
 * This function is called when user space has no more references on the
 * base object. It releases the base-object's reference on the resource object.
 */

अटल व्योम vmw_user_context_base_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;
	काष्ठा vmw_user_context *ctx =
	    container_of(base, काष्ठा vmw_user_context, base);
	काष्ठा vmw_resource *res = &ctx->res;

	*p_base = शून्य;
	vmw_resource_unreference(&res);
पूर्ण

पूर्णांक vmw_context_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_context_arg *arg = (काष्ठा drm_vmw_context_arg *)data;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	वापस tपंचांग_ref_object_base_unref(tfile, arg->cid, TTM_REF_USAGE);
पूर्ण

अटल पूर्णांक vmw_context_define(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv, bool dx)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_user_context *ctx;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_resource *पंचांगp;
	काष्ठा drm_vmw_context_arg *arg = (काष्ठा drm_vmw_context_arg *)data;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा tपंचांग_operation_ctx tपंचांग_opt_ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (!has_sm4_context(dev_priv) && dx) अणु
		VMW_DEBUG_USER("DX contexts not supported by device.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(vmw_user_context_size == 0))
		vmw_user_context_size = tपंचांग_round_pot(माप(*ctx)) +
		  ((dev_priv->has_mob) ? vmw_cmdbuf_res_man_size() : 0) +
		  + VMW_IDA_ACC_SIZE + TTM_OBJ_EXTRA_SIZE;

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_user_context_size,
				   &tपंचांग_opt_ctx);
	अगर (unlikely(ret != 0)) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for context"
				  " creation.\n");
		जाओ out_unlock;
	पूर्ण

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (unlikely(!ctx)) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
				    vmw_user_context_size);
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	res = &ctx->res;
	ctx->base.shareable = false;
	ctx->base.tfile = शून्य;

	/*
	 * From here on, the deकाष्ठाor takes over resource मुक्तing.
	 */

	ret = vmw_context_init(dev_priv, res, vmw_user_context_मुक्त, dx);
	अगर (unlikely(ret != 0))
		जाओ out_unlock;

	पंचांगp = vmw_resource_reference(&ctx->res);
	ret = tपंचांग_base_object_init(tfile, &ctx->base, false, VMW_RES_CONTEXT,
				   &vmw_user_context_base_release, शून्य);

	अगर (unlikely(ret != 0)) अणु
		vmw_resource_unreference(&पंचांगp);
		जाओ out_err;
	पूर्ण

	arg->cid = ctx->base.handle;
out_err:
	vmw_resource_unreference(&res);
out_unlock:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण

पूर्णांक vmw_context_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv)
अणु
	वापस vmw_context_define(dev, data, file_priv, false);
पूर्ण

पूर्णांक vmw_extended_context_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv)
अणु
	जोड़ drm_vmw_extended_context_arg *arg = (typeof(arg)) data;
	काष्ठा drm_vmw_context_arg *rep = &arg->rep;

	चयन (arg->req) अणु
	हाल drm_vmw_context_legacy:
		वापस vmw_context_define(dev, rep, file_priv, false);
	हाल drm_vmw_context_dx:
		वापस vmw_context_define(dev, rep, file_priv, true);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * vmw_context_binding_list - Return a list of context bindings
 *
 * @ctx: The context resource
 *
 * Returns the current list of bindings of the given context. Note that
 * this list becomes stale as soon as the dev_priv::binding_mutex is unlocked.
 */
काष्ठा list_head *vmw_context_binding_list(काष्ठा vmw_resource *ctx)
अणु
	काष्ठा vmw_user_context *uctx =
		container_of(ctx, काष्ठा vmw_user_context, res);

	वापस vmw_binding_state_list(uctx->cbs);
पूर्ण

काष्ठा vmw_cmdbuf_res_manager *vmw_context_res_man(काष्ठा vmw_resource *ctx)
अणु
	वापस container_of(ctx, काष्ठा vmw_user_context, res)->man;
पूर्ण

काष्ठा vmw_resource *vmw_context_cotable(काष्ठा vmw_resource *ctx,
					 SVGACOTableType cotable_type)
अणु
	u32 cotable_max = has_sm5_context(ctx->dev_priv) ?
		SVGA_COTABLE_MAX : SVGA_COTABLE_DX10_MAX;

	अगर (cotable_type >= cotable_max)
		वापस ERR_PTR(-EINVAL);

	वापस container_of(ctx, काष्ठा vmw_user_context, res)->
		cotables[cotable_type];
पूर्ण

/**
 * vmw_context_binding_state -
 * Return a poपूर्णांकer to a context binding state काष्ठाure
 *
 * @ctx: The context resource
 *
 * Returns the current state of bindings of the given context. Note that
 * this state becomes stale as soon as the dev_priv::binding_mutex is unlocked.
 */
काष्ठा vmw_ctx_binding_state *
vmw_context_binding_state(काष्ठा vmw_resource *ctx)
अणु
	वापस container_of(ctx, काष्ठा vmw_user_context, res)->cbs;
पूर्ण

/**
 * vmw_context_bind_dx_query -
 * Sets query MOB क्रम the context.  If @mob is शून्य, then this function will
 * हटाओ the association between the MOB and the context.  This function
 * assumes the binding_mutex is held.
 *
 * @ctx_res: The context resource
 * @mob: a reference to the query MOB
 *
 * Returns -EINVAL अगर a MOB has alपढ़ोy been set and करोes not match the one
 * specअगरied in the parameter.  0 otherwise.
 */
पूर्णांक vmw_context_bind_dx_query(काष्ठा vmw_resource *ctx_res,
			      काष्ठा vmw_buffer_object *mob)
अणु
	काष्ठा vmw_user_context *uctx =
		container_of(ctx_res, काष्ठा vmw_user_context, res);

	अगर (mob == शून्य) अणु
		अगर (uctx->dx_query_mob) अणु
			uctx->dx_query_mob->dx_query_ctx = शून्य;
			vmw_bo_unreference(&uctx->dx_query_mob);
			uctx->dx_query_mob = शून्य;
		पूर्ण

		वापस 0;
	पूर्ण

	/* Can only have one MOB per context क्रम queries */
	अगर (uctx->dx_query_mob && uctx->dx_query_mob != mob)
		वापस -EINVAL;

	mob->dx_query_ctx  = ctx_res;

	अगर (!uctx->dx_query_mob)
		uctx->dx_query_mob = vmw_bo_reference(mob);

	वापस 0;
पूर्ण

/**
 * vmw_context_get_dx_query_mob - Returns non-counted reference to DX query mob
 *
 * @ctx_res: The context resource
 */
काष्ठा vmw_buffer_object *
vmw_context_get_dx_query_mob(काष्ठा vmw_resource *ctx_res)
अणु
	काष्ठा vmw_user_context *uctx =
		container_of(ctx_res, काष्ठा vmw_user_context, res);

	वापस uctx->dx_query_mob;
पूर्ण
