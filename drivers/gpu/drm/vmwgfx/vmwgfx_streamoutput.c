<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright तऊ 2018-2019 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"
#समावेश "vmwgfx_binding.h"

/**
 * काष्ठा vmw_dx_streamoutput - Streamoutput resource metadata.
 * @res: Base resource काष्ठा.
 * @ctx: Non-refcounted context to which @res beदीर्घ.
 * @cotable: Refcounted cotable holding this Streamoutput.
 * @cotable_head: List head क्रम cotable-so_res list.
 * @id: User-space provided identअगरier.
 * @size: User-space provided mob size.
 * @committed: Whether streamoutput is actually created or pending creation.
 */
काष्ठा vmw_dx_streamoutput अणु
	काष्ठा vmw_resource res;
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_resource *cotable;
	काष्ठा list_head cotable_head;
	u32 id;
	u32 size;
	bool committed;
पूर्ण;

अटल पूर्णांक vmw_dx_streamoutput_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_dx_streamoutput_bind(काष्ठा vmw_resource *res,
				    काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_dx_streamoutput_unbind(काष्ठा vmw_resource *res, bool पढ़ोback,
				      काष्ठा tपंचांग_validate_buffer *val_buf);
अटल व्योम vmw_dx_streamoutput_commit_notअगरy(काष्ठा vmw_resource *res,
					      क्रमागत vmw_cmdbuf_res_state state);

अटल माप_प्रकार vmw_streamoutput_size;

अटल स्थिर काष्ठा vmw_res_func vmw_dx_streamoutput_func = अणु
	.res_type = vmw_res_streamoutput,
	.needs_backup = true,
	.may_evict = false,
	.type_name = "DX streamoutput",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_dx_streamoutput_create,
	.destroy = शून्य, /* Command buffer managed resource. */
	.bind = vmw_dx_streamoutput_bind,
	.unbind = vmw_dx_streamoutput_unbind,
	.commit_notअगरy = vmw_dx_streamoutput_commit_notअगरy,
पूर्ण;

अटल अंतरभूत काष्ठा vmw_dx_streamoutput *
vmw_res_to_dx_streamoutput(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_dx_streamoutput, res);
पूर्ण

/**
 * vmw_dx_streamoutput_unscrub - Reattach the MOB to streamoutput.
 * @res: The streamoutput resource.
 *
 * Return: 0 on success, negative error code on failure.
 */
अटल पूर्णांक vmw_dx_streamoutput_unscrub(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_dx_streamoutput *so = vmw_res_to_dx_streamoutput(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindStreamOutput body;
	पूर्ण *cmd;

	अगर (!list_empty(&so->cotable_head) || !so->committed )
		वापस 0;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), so->ctx->id);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_BIND_STREAMOUTPUT;
	cmd->header.size = माप(cmd->body);
	cmd->body.soid = so->id;
	cmd->body.mobid = res->backup->base.mem.start;
	cmd->body.offsetInBytes = res->backup_offset;
	cmd->body.sizeInBytes = so->size;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	vmw_cotable_add_resource(so->cotable, &so->cotable_head);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_dx_streamoutput_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_dx_streamoutput *so = vmw_res_to_dx_streamoutput(res);
	पूर्णांक ret = 0;

	WARN_ON_ONCE(!so->committed);

	अगर (vmw_resource_mob_attached(res)) अणु
		mutex_lock(&dev_priv->binding_mutex);
		ret = vmw_dx_streamoutput_unscrub(res);
		mutex_unlock(&dev_priv->binding_mutex);
	पूर्ण

	res->id = so->id;

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_dx_streamoutput_bind(काष्ठा vmw_resource *res,
				    काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;
	पूर्णांक ret;

	अगर (WARN_ON(bo->mem.mem_type != VMW_PL_MOB))
		वापस -EINVAL;

	mutex_lock(&dev_priv->binding_mutex);
	ret = vmw_dx_streamoutput_unscrub(res);
	mutex_unlock(&dev_priv->binding_mutex);

	वापस ret;
पूर्ण

/**
 * vmw_dx_streamoutput_scrub - Unbind the MOB from streamoutput.
 * @res: The streamoutput resource.
 *
 * Return: 0 on success, negative error code on failure.
 */
अटल पूर्णांक vmw_dx_streamoutput_scrub(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_dx_streamoutput *so = vmw_res_to_dx_streamoutput(res);
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindStreamOutput body;
	पूर्ण *cmd;

	अगर (list_empty(&so->cotable_head))
		वापस 0;

	WARN_ON_ONCE(!so->committed);

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), so->ctx->id);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_BIND_STREAMOUTPUT;
	cmd->header.size = माप(cmd->body);
	cmd->body.soid = res->id;
	cmd->body.mobid = SVGA3D_INVALID_ID;
	cmd->body.offsetInBytes = 0;
	cmd->body.sizeInBytes = so->size;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	res->id = -1;
	list_del_init(&so->cotable_head);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_dx_streamoutput_unbind(काष्ठा vmw_resource *res, bool पढ़ोback,
				      काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_fence_obj *fence;
	पूर्णांक ret;

	अगर (WARN_ON(res->backup->base.mem.mem_type != VMW_PL_MOB))
		वापस -EINVAL;

	mutex_lock(&dev_priv->binding_mutex);
	ret = vmw_dx_streamoutput_scrub(res);
	mutex_unlock(&dev_priv->binding_mutex);

	अगर (ret)
		वापस ret;

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv, &fence, शून्य);
	vmw_bo_fence_single(val_buf->bo, fence);

	अगर (fence != शून्य)
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

अटल व्योम vmw_dx_streamoutput_commit_notअगरy(काष्ठा vmw_resource *res,
					   क्रमागत vmw_cmdbuf_res_state state)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_dx_streamoutput *so = vmw_res_to_dx_streamoutput(res);

	अगर (state == VMW_CMDBUF_RES_ADD) अणु
		mutex_lock(&dev_priv->binding_mutex);
		vmw_cotable_add_resource(so->cotable, &so->cotable_head);
		so->committed = true;
		res->id = so->id;
		mutex_unlock(&dev_priv->binding_mutex);
	पूर्ण अन्यथा अणु
		mutex_lock(&dev_priv->binding_mutex);
		list_del_init(&so->cotable_head);
		so->committed = false;
		res->id = -1;
		mutex_unlock(&dev_priv->binding_mutex);
	पूर्ण
पूर्ण

/**
 * vmw_dx_streamoutput_lookup - Do a streamoutput resource lookup by user key.
 * @man: Command buffer managed resource manager क्रम current context.
 * @user_key: User-space identअगरier क्रम lookup.
 *
 * Return: Valid refcounted vmw_resource on success, error poपूर्णांकer on failure.
 */
काष्ठा vmw_resource *
vmw_dx_streamoutput_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
			   u32 user_key)
अणु
	वापस vmw_cmdbuf_res_lookup(man, vmw_cmdbuf_res_streamoutput,
				     user_key);
पूर्ण

अटल व्योम vmw_dx_streamoutput_res_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_dx_streamoutput *so = vmw_res_to_dx_streamoutput(res);

	vmw_resource_unreference(&so->cotable);
	kमुक्त(so);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), vmw_streamoutput_size);
पूर्ण

अटल व्योम vmw_dx_streamoutput_hw_destroy(काष्ठा vmw_resource *res)
अणु
	/* Destroyed by user-space cmd buf or as part of context takeकरोwn. */
	res->id = -1;
पूर्ण

/**
 * vmw_dx_streamoutput_add - Add a streamoutput as a cmd buf managed resource.
 * @man: Command buffer managed resource manager क्रम current context.
 * @ctx: Poपूर्णांकer to context resource.
 * @user_key: The identअगरier क्रम this streamoutput.
 * @list: The list of staged command buffer managed resources.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक vmw_dx_streamoutput_add(काष्ठा vmw_cmdbuf_res_manager *man,
			    काष्ठा vmw_resource *ctx, u32 user_key,
			    काष्ठा list_head *list)
अणु
	काष्ठा vmw_dx_streamoutput *so;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_निजी *dev_priv = ctx->dev_priv;
	काष्ठा tपंचांग_operation_ctx tपंचांग_opt_ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (!vmw_streamoutput_size)
		vmw_streamoutput_size = tपंचांग_round_pot(माप(*so));

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_streamoutput_size, &tपंचांग_opt_ctx);
	अगर (ret) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for streamout.\n");
		वापस ret;
	पूर्ण

	so = kदो_स्मृति(माप(*so), GFP_KERNEL);
	अगर (!so) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
				    vmw_streamoutput_size);
		वापस -ENOMEM;
	पूर्ण

	res = &so->res;
	so->ctx = ctx;
	so->cotable = vmw_resource_reference
		(vmw_context_cotable(ctx, SVGA_COTABLE_STREAMOUTPUT));
	so->id = user_key;
	so->committed = false;
	INIT_LIST_HEAD(&so->cotable_head);
	ret = vmw_resource_init(dev_priv, res, true,
				vmw_dx_streamoutput_res_मुक्त,
				&vmw_dx_streamoutput_func);
	अगर (ret)
		जाओ out_resource_init;

	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_streamoutput, user_key,
				 res, list);
	अगर (ret)
		जाओ out_resource_init;

	res->id = so->id;
	res->hw_destroy = vmw_dx_streamoutput_hw_destroy;

out_resource_init:
	vmw_resource_unreference(&res);

	वापस ret;
पूर्ण

/**
 * vmw_dx_streamoutput_set_size - Sets streamoutput mob size in res काष्ठा.
 * @res: The streamoutput res क्रम which need to set size.
 * @size: The size provided by user-space to set.
 */
व्योम vmw_dx_streamoutput_set_size(काष्ठा vmw_resource *res, u32 size)
अणु
	काष्ठा vmw_dx_streamoutput *so = vmw_res_to_dx_streamoutput(res);

	so->size = size;
पूर्ण

/**
 * vmw_dx_streamoutput_हटाओ - Stage streamoutput क्रम removal.
 * @man: Command buffer managed resource manager क्रम current context.
 * @user_key: The identअगरier क्रम this streamoutput.
 * @list: The list of staged command buffer managed resources.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक vmw_dx_streamoutput_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
			       u32 user_key,
			       काष्ठा list_head *list)
अणु
	काष्ठा vmw_resource *r;

	वापस vmw_cmdbuf_res_हटाओ(man, vmw_cmdbuf_res_streamoutput,
				     (u32)user_key, list, &r);
पूर्ण

/**
 * vmw_dx_streamoutput_cotable_list_scrub - cotable unbind_func callback.
 * @dev_priv: Device निजी.
 * @list: The list of cotable resources.
 * @पढ़ोback: Whether the call was part of a पढ़ोback unbind.
 */
व्योम vmw_dx_streamoutput_cotable_list_scrub(काष्ठा vmw_निजी *dev_priv,
					    काष्ठा list_head *list,
					    bool पढ़ोback)
अणु
	काष्ठा vmw_dx_streamoutput *entry, *next;

	lockdep_निश्चित_held_once(&dev_priv->binding_mutex);

	list_क्रम_each_entry_safe(entry, next, list, cotable_head) अणु
		WARN_ON(vmw_dx_streamoutput_scrub(&entry->res));
		अगर (!पढ़ोback)
			entry->committed =false;
	पूर्ण
पूर्ण
