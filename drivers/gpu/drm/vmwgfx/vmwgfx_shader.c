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

काष्ठा vmw_shader अणु
	काष्ठा vmw_resource res;
	SVGA3dShaderType type;
	uपूर्णांक32_t size;
	uपूर्णांक8_t num_input_sig;
	uपूर्णांक8_t num_output_sig;
पूर्ण;

काष्ठा vmw_user_shader अणु
	काष्ठा tपंचांग_base_object base;
	काष्ठा vmw_shader shader;
पूर्ण;

काष्ठा vmw_dx_shader अणु
	काष्ठा vmw_resource res;
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_resource *cotable;
	u32 id;
	bool committed;
	काष्ठा list_head cotable_head;
पूर्ण;

अटल uपूर्णांक64_t vmw_user_shader_size;
अटल uपूर्णांक64_t vmw_shader_size;
अटल माप_प्रकार vmw_shader_dx_size;

अटल व्योम vmw_user_shader_मुक्त(काष्ठा vmw_resource *res);
अटल काष्ठा vmw_resource *
vmw_user_shader_base_to_res(काष्ठा tपंचांग_base_object *base);

अटल पूर्णांक vmw_gb_shader_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_gb_shader_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_gb_shader_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_gb_shader_destroy(काष्ठा vmw_resource *res);

अटल पूर्णांक vmw_dx_shader_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_dx_shader_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_dx_shader_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf);
अटल व्योम vmw_dx_shader_commit_notअगरy(काष्ठा vmw_resource *res,
					क्रमागत vmw_cmdbuf_res_state state);
अटल bool vmw_shader_id_ok(u32 user_key, SVGA3dShaderType shader_type);
अटल u32 vmw_shader_key(u32 user_key, SVGA3dShaderType shader_type);
अटल uपूर्णांक64_t vmw_user_shader_size;

अटल स्थिर काष्ठा vmw_user_resource_conv user_shader_conv = अणु
	.object_type = VMW_RES_SHADER,
	.base_obj_to_res = vmw_user_shader_base_to_res,
	.res_मुक्त = vmw_user_shader_मुक्त
पूर्ण;

स्थिर काष्ठा vmw_user_resource_conv *user_shader_converter =
	&user_shader_conv;


अटल स्थिर काष्ठा vmw_res_func vmw_gb_shader_func = अणु
	.res_type = vmw_res_shader,
	.needs_backup = true,
	.may_evict = true,
	.prio = 3,
	.dirty_prio = 3,
	.type_name = "guest backed shaders",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_gb_shader_create,
	.destroy = vmw_gb_shader_destroy,
	.bind = vmw_gb_shader_bind,
	.unbind = vmw_gb_shader_unbind
पूर्ण;

अटल स्थिर काष्ठा vmw_res_func vmw_dx_shader_func = अणु
	.res_type = vmw_res_shader,
	.needs_backup = true,
	.may_evict = true,
	.prio = 3,
	.dirty_prio = 3,
	.type_name = "dx shaders",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_dx_shader_create,
	/*
	 * The destroy callback is only called with a committed resource on
	 * context destroy, in which हाल we destroy the cotable anyway,
	 * so there's no need to destroy DX shaders separately.
	 */
	.destroy = शून्य,
	.bind = vmw_dx_shader_bind,
	.unbind = vmw_dx_shader_unbind,
	.commit_notअगरy = vmw_dx_shader_commit_notअगरy,
पूर्ण;

/*
 * Shader management:
 */

अटल अंतरभूत काष्ठा vmw_shader *
vmw_res_to_shader(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_shader, res);
पूर्ण

/**
 * vmw_res_to_dx_shader - typecast a काष्ठा vmw_resource to a
 * काष्ठा vmw_dx_shader
 *
 * @res: Poपूर्णांकer to the काष्ठा vmw_resource.
 */
अटल अंतरभूत काष्ठा vmw_dx_shader *
vmw_res_to_dx_shader(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_dx_shader, res);
पूर्ण

अटल व्योम vmw_hw_shader_destroy(काष्ठा vmw_resource *res)
अणु
	अगर (likely(res->func->destroy))
		(व्योम) res->func->destroy(res);
	अन्यथा
		res->id = -1;
पूर्ण


अटल पूर्णांक vmw_gb_shader_init(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_resource *res,
			      uपूर्णांक32_t size,
			      uपूर्णांक64_t offset,
			      SVGA3dShaderType type,
			      uपूर्णांक8_t num_input_sig,
			      uपूर्णांक8_t num_output_sig,
			      काष्ठा vmw_buffer_object *byte_code,
			      व्योम (*res_मुक्त) (काष्ठा vmw_resource *res))
अणु
	काष्ठा vmw_shader *shader = vmw_res_to_shader(res);
	पूर्णांक ret;

	ret = vmw_resource_init(dev_priv, res, true, res_मुक्त,
				&vmw_gb_shader_func);

	अगर (unlikely(ret != 0)) अणु
		अगर (res_मुक्त)
			res_मुक्त(res);
		अन्यथा
			kमुक्त(res);
		वापस ret;
	पूर्ण

	res->backup_size = size;
	अगर (byte_code) अणु
		res->backup = vmw_bo_reference(byte_code);
		res->backup_offset = offset;
	पूर्ण
	shader->size = size;
	shader->type = type;
	shader->num_input_sig = num_input_sig;
	shader->num_output_sig = num_output_sig;

	res->hw_destroy = vmw_hw_shader_destroy;
	वापस 0;
पूर्ण

/*
 * GB shader code:
 */

अटल पूर्णांक vmw_gb_shader_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_shader *shader = vmw_res_to_shader(res);
	पूर्णांक ret;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBShader body;
	पूर्ण *cmd;

	अगर (likely(res->id != -1))
		वापस 0;

	ret = vmw_resource_alloc_id(res);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate a shader id.\n");
		जाओ out_no_id;
	पूर्ण

	अगर (unlikely(res->id >= VMWGFX_NUM_GB_SHADER)) अणु
		ret = -EBUSY;
		जाओ out_no_fअगरo;
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य)) अणु
		ret = -ENOMEM;
		जाओ out_no_fअगरo;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_DEFINE_GB_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.shid = res->id;
	cmd->body.type = shader->type;
	cmd->body.sizeInBytes = shader->size;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	vmw_fअगरo_resource_inc(dev_priv);

	वापस 0;

out_no_fअगरo:
	vmw_resource_release_id(res);
out_no_id:
	वापस ret;
पूर्ण

अटल पूर्णांक vmw_gb_shader_bind(काष्ठा vmw_resource *res,
			      काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBShader body;
	पूर्ण *cmd;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;

	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_BIND_GB_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.shid = res->id;
	cmd->body.mobid = bo->mem.start;
	cmd->body.offsetInBytes = res->backup_offset;
	res->backup_dirty = false;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_gb_shader_unbind(काष्ठा vmw_resource *res,
				bool पढ़ोback,
				काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBShader body;
	पूर्ण *cmd;
	काष्ठा vmw_fence_obj *fence;

	BUG_ON(res->backup->base.mem.mem_type != VMW_PL_MOB);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_BIND_GB_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.shid = res->id;
	cmd->body.mobid = SVGA3D_INVALID_ID;
	cmd->body.offsetInBytes = 0;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	/*
	 * Create a fence object and fence the backup buffer.
	 */

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv,
					  &fence, शून्य);

	vmw_bo_fence_single(val_buf->bo, fence);

	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_gb_shader_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDestroyGBShader body;
	पूर्ण *cmd;

	अगर (likely(res->id == -1))
		वापस 0;

	mutex_lock(&dev_priv->binding_mutex);
	vmw_binding_res_list_scrub(&res->binding_head);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य)) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस -ENOMEM;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_DESTROY_GB_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.shid = res->id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	mutex_unlock(&dev_priv->binding_mutex);
	vmw_resource_release_id(res);
	vmw_fअगरo_resource_dec(dev_priv);

	वापस 0;
पूर्ण

/*
 * DX shader code:
 */

/**
 * vmw_dx_shader_commit_notअगरy - Notअगरy that a shader operation has been
 * committed to hardware from a user-supplied command stream.
 *
 * @res: Poपूर्णांकer to the shader resource.
 * @state: Indicating whether a creation or removal has been committed.
 *
 */
अटल व्योम vmw_dx_shader_commit_notअगरy(काष्ठा vmw_resource *res,
					क्रमागत vmw_cmdbuf_res_state state)
अणु
	काष्ठा vmw_dx_shader *shader = vmw_res_to_dx_shader(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	अगर (state == VMW_CMDBUF_RES_ADD) अणु
		mutex_lock(&dev_priv->binding_mutex);
		vmw_cotable_add_resource(shader->cotable,
					 &shader->cotable_head);
		shader->committed = true;
		res->id = shader->id;
		mutex_unlock(&dev_priv->binding_mutex);
	पूर्ण अन्यथा अणु
		mutex_lock(&dev_priv->binding_mutex);
		list_del_init(&shader->cotable_head);
		shader->committed = false;
		res->id = -1;
		mutex_unlock(&dev_priv->binding_mutex);
	पूर्ण
पूर्ण

/**
 * vmw_dx_shader_unscrub - Have the device reattach a MOB to a DX shader.
 *
 * @res: The shader resource
 *
 * This function reverts a scrub operation.
 */
अटल पूर्णांक vmw_dx_shader_unscrub(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_dx_shader *shader = vmw_res_to_dx_shader(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindShader body;
	पूर्ण *cmd;

	अगर (!list_empty(&shader->cotable_head) || !shader->committed)
		वापस 0;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), shader->ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_BIND_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = shader->ctx->id;
	cmd->body.shid = shader->id;
	cmd->body.mobid = res->backup->base.mem.start;
	cmd->body.offsetInBytes = res->backup_offset;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	vmw_cotable_add_resource(shader->cotable, &shader->cotable_head);

	वापस 0;
पूर्ण

/**
 * vmw_dx_shader_create - The DX shader create callback
 *
 * @res: The DX shader resource
 *
 * The create callback is called as part of resource validation and
 * makes sure that we unscrub the shader अगर it's previously been scrubbed.
 */
अटल पूर्णांक vmw_dx_shader_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_dx_shader *shader = vmw_res_to_dx_shader(res);
	पूर्णांक ret = 0;

	WARN_ON_ONCE(!shader->committed);

	अगर (vmw_resource_mob_attached(res)) अणु
		mutex_lock(&dev_priv->binding_mutex);
		ret = vmw_dx_shader_unscrub(res);
		mutex_unlock(&dev_priv->binding_mutex);
	पूर्ण

	res->id = shader->id;
	वापस ret;
पूर्ण

/**
 * vmw_dx_shader_bind - The DX shader bind callback
 *
 * @res: The DX shader resource
 * @val_buf: Poपूर्णांकer to the validate buffer.
 *
 */
अटल पूर्णांक vmw_dx_shader_bind(काष्ठा vmw_resource *res,
			      काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;

	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);
	mutex_lock(&dev_priv->binding_mutex);
	vmw_dx_shader_unscrub(res);
	mutex_unlock(&dev_priv->binding_mutex);

	वापस 0;
पूर्ण

/**
 * vmw_dx_shader_scrub - Have the device unbind a MOB from a DX shader.
 *
 * @res: The shader resource
 *
 * This function unbinds a MOB from the DX shader without requiring the
 * MOB dma_buffer to be reserved. The driver still considers the MOB bound.
 * However, once the driver eventually decides to unbind the MOB, it करोesn't
 * need to access the context.
 */
अटल पूर्णांक vmw_dx_shader_scrub(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_dx_shader *shader = vmw_res_to_dx_shader(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindShader body;
	पूर्ण *cmd;

	अगर (list_empty(&shader->cotable_head))
		वापस 0;

	WARN_ON_ONCE(!shader->committed);
	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_BIND_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = shader->ctx->id;
	cmd->body.shid = res->id;
	cmd->body.mobid = SVGA3D_INVALID_ID;
	cmd->body.offsetInBytes = 0;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	res->id = -1;
	list_del_init(&shader->cotable_head);

	वापस 0;
पूर्ण

/**
 * vmw_dx_shader_unbind - The dx shader unbind callback.
 *
 * @res: The shader resource
 * @पढ़ोback: Whether this is a पढ़ोback unbind. Currently unused.
 * @val_buf: MOB buffer inक्रमmation.
 */
अटल पूर्णांक vmw_dx_shader_unbind(काष्ठा vmw_resource *res,
				bool पढ़ोback,
				काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_fence_obj *fence;
	पूर्णांक ret;

	BUG_ON(res->backup->base.mem.mem_type != VMW_PL_MOB);

	mutex_lock(&dev_priv->binding_mutex);
	ret = vmw_dx_shader_scrub(res);
	mutex_unlock(&dev_priv->binding_mutex);

	अगर (ret)
		वापस ret;

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv,
					  &fence, शून्य);
	vmw_bo_fence_single(val_buf->bo, fence);

	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

/**
 * vmw_dx_shader_cotable_list_scrub - The cotable unbind_func callback क्रम
 * DX shaders.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठाure.
 * @list: The list of cotable resources.
 * @पढ़ोback: Whether the call was part of a पढ़ोback unbind.
 *
 * Scrubs all shader MOBs so that any subsequent shader unbind or shader
 * destroy operation won't need to swap in the context.
 */
व्योम vmw_dx_shader_cotable_list_scrub(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा list_head *list,
				      bool पढ़ोback)
अणु
	काष्ठा vmw_dx_shader *entry, *next;

	lockdep_निश्चित_held_once(&dev_priv->binding_mutex);

	list_क्रम_each_entry_safe(entry, next, list, cotable_head) अणु
		WARN_ON(vmw_dx_shader_scrub(&entry->res));
		अगर (!पढ़ोback)
			entry->committed = false;
	पूर्ण
पूर्ण

/**
 * vmw_dx_shader_res_मुक्त - The DX shader मुक्त callback
 *
 * @res: The shader resource
 *
 * Frees the DX shader resource and updates memory accounting.
 */
अटल व्योम vmw_dx_shader_res_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_dx_shader *shader = vmw_res_to_dx_shader(res);

	vmw_resource_unreference(&shader->cotable);
	kमुक्त(shader);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), vmw_shader_dx_size);
पूर्ण

/**
 * vmw_dx_shader_add - Add a shader resource as a command buffer managed
 * resource.
 *
 * @man: The command buffer resource manager.
 * @ctx: Poपूर्णांकer to the context resource.
 * @user_key: The id used क्रम this shader.
 * @shader_type: The shader type.
 * @list: The list of staged command buffer managed resources.
 */
पूर्णांक vmw_dx_shader_add(काष्ठा vmw_cmdbuf_res_manager *man,
		      काष्ठा vmw_resource *ctx,
		      u32 user_key,
		      SVGA3dShaderType shader_type,
		      काष्ठा list_head *list)
अणु
	काष्ठा vmw_dx_shader *shader;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_निजी *dev_priv = ctx->dev_priv;
	काष्ठा tपंचांग_operation_ctx tपंचांग_opt_ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (!vmw_shader_dx_size)
		vmw_shader_dx_size = tपंचांग_round_pot(माप(*shader));

	अगर (!vmw_shader_id_ok(user_key, shader_type))
		वापस -EINVAL;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv), vmw_shader_dx_size,
				   &tपंचांग_opt_ctx);
	अगर (ret) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for shader "
				  "creation.\n");
		वापस ret;
	पूर्ण

	shader = kदो_स्मृति(माप(*shader), GFP_KERNEL);
	अगर (!shader) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), vmw_shader_dx_size);
		वापस -ENOMEM;
	पूर्ण

	res = &shader->res;
	shader->ctx = ctx;
	shader->cotable = vmw_resource_reference
		(vmw_context_cotable(ctx, SVGA_COTABLE_DXSHADER));
	shader->id = user_key;
	shader->committed = false;
	INIT_LIST_HEAD(&shader->cotable_head);
	ret = vmw_resource_init(dev_priv, res, true,
				vmw_dx_shader_res_मुक्त, &vmw_dx_shader_func);
	अगर (ret)
		जाओ out_resource_init;

	/*
	 * The user_key name-space is not per shader type क्रम DX shaders,
	 * so when hashing, use a single zero shader type.
	 */
	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_shader,
				 vmw_shader_key(user_key, 0),
				 res, list);
	अगर (ret)
		जाओ out_resource_init;

	res->id = shader->id;
	res->hw_destroy = vmw_hw_shader_destroy;

out_resource_init:
	vmw_resource_unreference(&res);

	वापस ret;
पूर्ण



/*
 * User-space shader management:
 */

अटल काष्ठा vmw_resource *
vmw_user_shader_base_to_res(काष्ठा tपंचांग_base_object *base)
अणु
	वापस &(container_of(base, काष्ठा vmw_user_shader, base)->
		 shader.res);
पूर्ण

अटल व्योम vmw_user_shader_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_user_shader *ushader =
		container_of(res, काष्ठा vmw_user_shader, shader.res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	tपंचांग_base_object_kमुक्त(ushader, base);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
			    vmw_user_shader_size);
पूर्ण

अटल व्योम vmw_shader_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_shader *shader = vmw_res_to_shader(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	kमुक्त(shader);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
			    vmw_shader_size);
पूर्ण

/*
 * This function is called when user space has no more references on the
 * base object. It releases the base-object's reference on the resource object.
 */

अटल व्योम vmw_user_shader_base_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;
	काष्ठा vmw_resource *res = vmw_user_shader_base_to_res(base);

	*p_base = शून्य;
	vmw_resource_unreference(&res);
पूर्ण

पूर्णांक vmw_shader_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_shader_arg *arg = (काष्ठा drm_vmw_shader_arg *)data;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	वापस tपंचांग_ref_object_base_unref(tfile, arg->handle,
					 TTM_REF_USAGE);
पूर्ण

अटल पूर्णांक vmw_user_shader_alloc(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_buffer_object *buffer,
				 माप_प्रकार shader_size,
				 माप_प्रकार offset,
				 SVGA3dShaderType shader_type,
				 uपूर्णांक8_t num_input_sig,
				 uपूर्णांक8_t num_output_sig,
				 काष्ठा tपंचांग_object_file *tfile,
				 u32 *handle)
अणु
	काष्ठा vmw_user_shader *ushader;
	काष्ठा vmw_resource *res, *पंचांगp;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (unlikely(vmw_user_shader_size == 0))
		vmw_user_shader_size =
			tपंचांग_round_pot(माप(काष्ठा vmw_user_shader)) +
			VMW_IDA_ACC_SIZE + TTM_OBJ_EXTRA_SIZE;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_user_shader_size,
				   &ctx);
	अगर (unlikely(ret != 0)) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for shader "
				  "creation.\n");
		जाओ out;
	पूर्ण

	ushader = kzalloc(माप(*ushader), GFP_KERNEL);
	अगर (unlikely(!ushader)) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
				    vmw_user_shader_size);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	res = &ushader->shader.res;
	ushader->base.shareable = false;
	ushader->base.tfile = शून्य;

	/*
	 * From here on, the deकाष्ठाor takes over resource मुक्तing.
	 */

	ret = vmw_gb_shader_init(dev_priv, res, shader_size,
				 offset, shader_type, num_input_sig,
				 num_output_sig, buffer,
				 vmw_user_shader_मुक्त);
	अगर (unlikely(ret != 0))
		जाओ out;

	पंचांगp = vmw_resource_reference(res);
	ret = tपंचांग_base_object_init(tfile, &ushader->base, false,
				   VMW_RES_SHADER,
				   &vmw_user_shader_base_release, शून्य);

	अगर (unlikely(ret != 0)) अणु
		vmw_resource_unreference(&पंचांगp);
		जाओ out_err;
	पूर्ण

	अगर (handle)
		*handle = ushader->base.handle;
out_err:
	vmw_resource_unreference(&res);
out:
	वापस ret;
पूर्ण


अटल काष्ठा vmw_resource *vmw_shader_alloc(काष्ठा vmw_निजी *dev_priv,
					     काष्ठा vmw_buffer_object *buffer,
					     माप_प्रकार shader_size,
					     माप_प्रकार offset,
					     SVGA3dShaderType shader_type)
अणु
	काष्ठा vmw_shader *shader;
	काष्ठा vmw_resource *res;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (unlikely(vmw_shader_size == 0))
		vmw_shader_size =
			tपंचांग_round_pot(माप(काष्ठा vmw_shader)) +
			VMW_IDA_ACC_SIZE;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_shader_size,
				   &ctx);
	अगर (unlikely(ret != 0)) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for shader "
				  "creation.\n");
		जाओ out_err;
	पूर्ण

	shader = kzalloc(माप(*shader), GFP_KERNEL);
	अगर (unlikely(!shader)) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
				    vmw_shader_size);
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	res = &shader->res;

	/*
	 * From here on, the deकाष्ठाor takes over resource मुक्तing.
	 */
	ret = vmw_gb_shader_init(dev_priv, res, shader_size,
				 offset, shader_type, 0, 0, buffer,
				 vmw_shader_मुक्त);

out_err:
	वापस ret ? ERR_PTR(ret) : res;
पूर्ण


अटल पूर्णांक vmw_shader_define(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
			     क्रमागत drm_vmw_shader_type shader_type_drm,
			     u32 buffer_handle, माप_प्रकार size, माप_प्रकार offset,
			     uपूर्णांक8_t num_input_sig, uपूर्णांक8_t num_output_sig,
			     uपूर्णांक32_t *shader_handle)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_buffer_object *buffer = शून्य;
	SVGA3dShaderType shader_type;
	पूर्णांक ret;

	अगर (buffer_handle != SVGA3D_INVALID_ID) अणु
		ret = vmw_user_bo_lookup(tfile, buffer_handle,
					     &buffer, शून्य);
		अगर (unlikely(ret != 0)) अणु
			VMW_DEBUG_USER("Couldn't find buffer for shader creation.\n");
			वापस ret;
		पूर्ण

		अगर ((u64)buffer->base.base.size < (u64)size + (u64)offset) अणु
			VMW_DEBUG_USER("Illegal buffer- or shader size.\n");
			ret = -EINVAL;
			जाओ out_bad_arg;
		पूर्ण
	पूर्ण

	चयन (shader_type_drm) अणु
	हाल drm_vmw_shader_type_vs:
		shader_type = SVGA3D_SHADERTYPE_VS;
		अवरोध;
	हाल drm_vmw_shader_type_ps:
		shader_type = SVGA3D_SHADERTYPE_PS;
		अवरोध;
	शेष:
		VMW_DEBUG_USER("Illegal shader type.\n");
		ret = -EINVAL;
		जाओ out_bad_arg;
	पूर्ण

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		जाओ out_bad_arg;

	ret = vmw_user_shader_alloc(dev_priv, buffer, size, offset,
				    shader_type, num_input_sig,
				    num_output_sig, tfile, shader_handle);

	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
out_bad_arg:
	vmw_bo_unreference(&buffer);
	वापस ret;
पूर्ण

/**
 * vmw_shader_id_ok - Check whether a compat shader user key and
 * shader type are within valid bounds.
 *
 * @user_key: User space id of the shader.
 * @shader_type: Shader type.
 *
 * Returns true अगर valid false अगर not.
 */
अटल bool vmw_shader_id_ok(u32 user_key, SVGA3dShaderType shader_type)
अणु
	वापस user_key <= ((1 << 20) - 1) && (अचिन्हित) shader_type < 16;
पूर्ण

/**
 * vmw_shader_key - Compute a hash key suitable क्रम a compat shader.
 *
 * @user_key: User space id of the shader.
 * @shader_type: Shader type.
 *
 * Returns a hash key suitable क्रम a command buffer managed resource
 * manager hash table.
 */
अटल u32 vmw_shader_key(u32 user_key, SVGA3dShaderType shader_type)
अणु
	वापस user_key | (shader_type << 20);
पूर्ण

/**
 * vmw_shader_हटाओ - Stage a compat shader क्रम removal.
 *
 * @man: Poपूर्णांकer to the compat shader manager identअगरying the shader namespace.
 * @user_key: The key that is used to identअगरy the shader. The key is
 * unique to the shader type.
 * @shader_type: Shader type.
 * @list: Caller's list of staged command buffer resource actions.
 */
पूर्णांक vmw_shader_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
		      u32 user_key, SVGA3dShaderType shader_type,
		      काष्ठा list_head *list)
अणु
	काष्ठा vmw_resource *dummy;

	अगर (!vmw_shader_id_ok(user_key, shader_type))
		वापस -EINVAL;

	वापस vmw_cmdbuf_res_हटाओ(man, vmw_cmdbuf_res_shader,
				     vmw_shader_key(user_key, shader_type),
				     list, &dummy);
पूर्ण

/**
 * vmw_compat_shader_add - Create a compat shader and stage it क्रम addition
 * as a command buffer managed resource.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठाure.
 * @man: Poपूर्णांकer to the compat shader manager identअगरying the shader namespace.
 * @user_key: The key that is used to identअगरy the shader. The key is
 * unique to the shader type.
 * @bytecode: Poपूर्णांकer to the bytecode of the shader.
 * @shader_type: Shader type.
 * @size: Command size.
 * @list: Caller's list of staged command buffer resource actions.
 *
 */
पूर्णांक vmw_compat_shader_add(काष्ठा vmw_निजी *dev_priv,
			  काष्ठा vmw_cmdbuf_res_manager *man,
			  u32 user_key, स्थिर व्योम *bytecode,
			  SVGA3dShaderType shader_type,
			  माप_प्रकार size,
			  काष्ठा list_head *list)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, true पूर्ण;
	काष्ठा vmw_buffer_object *buf;
	काष्ठा tपंचांग_bo_kmap_obj map;
	bool is_iomem;
	पूर्णांक ret;
	काष्ठा vmw_resource *res;

	अगर (!vmw_shader_id_ok(user_key, shader_type))
		वापस -EINVAL;

	/* Allocate and pin a DMA buffer */
	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (unlikely(!buf))
		वापस -ENOMEM;

	ret = vmw_bo_init(dev_priv, buf, size, &vmw_sys_placement,
			      true, true, vmw_bo_bo_मुक्त);
	अगर (unlikely(ret != 0))
		जाओ out;

	ret = tपंचांग_bo_reserve(&buf->base, false, true, शून्य);
	अगर (unlikely(ret != 0))
		जाओ no_reserve;

	/* Map and copy shader bytecode. */
	ret = tपंचांग_bo_kmap(&buf->base, 0, PAGE_ALIGN(size) >> PAGE_SHIFT,
			  &map);
	अगर (unlikely(ret != 0)) अणु
		tपंचांग_bo_unreserve(&buf->base);
		जाओ no_reserve;
	पूर्ण

	स_नकल(tपंचांग_kmap_obj_भव(&map, &is_iomem), bytecode, size);
	WARN_ON(is_iomem);

	tपंचांग_bo_kunmap(&map);
	ret = tपंचांग_bo_validate(&buf->base, &vmw_sys_placement, &ctx);
	WARN_ON(ret != 0);
	tपंचांग_bo_unreserve(&buf->base);

	res = vmw_shader_alloc(dev_priv, buf, size, 0, shader_type);
	अगर (unlikely(ret != 0))
		जाओ no_reserve;

	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_shader,
				 vmw_shader_key(user_key, shader_type),
				 res, list);
	vmw_resource_unreference(&res);
no_reserve:
	vmw_bo_unreference(&buf);
out:
	वापस ret;
पूर्ण

/**
 * vmw_shader_lookup - Look up a compat shader
 *
 * @man: Poपूर्णांकer to the command buffer managed resource manager identअगरying
 * the shader namespace.
 * @user_key: The user space id of the shader.
 * @shader_type: The shader type.
 *
 * Returns a refcounted poपूर्णांकer to a काष्ठा vmw_resource अगर the shader was
 * found. An error poपूर्णांकer otherwise.
 */
काष्ठा vmw_resource *
vmw_shader_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
		  u32 user_key,
		  SVGA3dShaderType shader_type)
अणु
	अगर (!vmw_shader_id_ok(user_key, shader_type))
		वापस ERR_PTR(-EINVAL);

	वापस vmw_cmdbuf_res_lookup(man, vmw_cmdbuf_res_shader,
				     vmw_shader_key(user_key, shader_type));
पूर्ण

पूर्णांक vmw_shader_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_shader_create_arg *arg =
		(काष्ठा drm_vmw_shader_create_arg *)data;

	वापस vmw_shader_define(dev, file_priv, arg->shader_type,
				 arg->buffer_handle,
				 arg->size, arg->offset,
				 0, 0,
				 &arg->shader_handle);
पूर्ण
