<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
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

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"
#समावेश "vmwgfx_so.h"
#समावेश "vmwgfx_binding.h"

/*
 * The currently only reason we need to keep track of views is that अगर we
 * destroy a hardware surface, all views poपूर्णांकing to it must also be destroyed,
 * otherwise the device will error.
 * So in particuar अगर a surface is evicted, we must destroy all views poपूर्णांकing
 * to it, and all context bindings of that view. Similarly we must restore
 * the view bindings, views and surfaces poपूर्णांकed to by the views when a
 * context is referenced in the command stream.
 */

/**
 * काष्ठा vmw_view - view metadata
 *
 * @rcu: RCU callback head
 * @res: The काष्ठा vmw_resource we derive from
 * @ctx: Non-refcounted poपूर्णांकer to the context this view beदीर्घs to.
 * @srf: Refcounted poपूर्णांकer to the surface poपूर्णांकed to by this view.
 * @cotable: Refcounted poपूर्णांकer to the cotable holding this view.
 * @srf_head: List head क्रम the surface-to-view list.
 * @cotable_head: List head क्रम the cotable-to_view list.
 * @view_type: View type.
 * @view_id: User-space per context view id. Currently used also as per
 * context device view id.
 * @cmd_size: Size of the SVGA3D define view command that we've copied from the
 * command stream.
 * @committed: Whether the view is actually created or pending creation at the
 * device level.
 * @cmd: The SVGA3D define view command copied from the command stream.
 */
काष्ठा vmw_view अणु
	काष्ठा rcu_head rcu;
	काष्ठा vmw_resource res;
	काष्ठा vmw_resource *ctx;      /* Immutable */
	काष्ठा vmw_resource *srf;      /* Immutable */
	काष्ठा vmw_resource *cotable;  /* Immutable */
	काष्ठा list_head srf_head;     /* Protected by binding_mutex */
	काष्ठा list_head cotable_head; /* Protected by binding_mutex */
	अचिन्हित view_type;            /* Immutable */
	अचिन्हित view_id;              /* Immutable */
	u32 cmd_size;                  /* Immutable */
	bool committed;                /* Protected by binding_mutex */
	u32 cmd[1];                    /* Immutable */
पूर्ण;

अटल पूर्णांक vmw_view_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_view_destroy(काष्ठा vmw_resource *res);
अटल व्योम vmw_hw_view_destroy(काष्ठा vmw_resource *res);
अटल व्योम vmw_view_commit_notअगरy(काष्ठा vmw_resource *res,
				   क्रमागत vmw_cmdbuf_res_state state);

अटल स्थिर काष्ठा vmw_res_func vmw_view_func = अणु
	.res_type = vmw_res_view,
	.needs_backup = false,
	.may_evict = false,
	.type_name = "DX view",
	.backup_placement = शून्य,
	.create = vmw_view_create,
	.commit_notअगरy = vmw_view_commit_notअगरy,
पूर्ण;

/**
 * काष्ठा vmw_view - view define command body stub
 *
 * @view_id: The device id of the view being defined
 * @sid: The surface id of the view being defined
 *
 * This generic काष्ठा is used by the code to change @view_id and @sid of a
 * saved view define command.
 */
काष्ठा vmw_view_define अणु
	uपूर्णांक32 view_id;
	uपूर्णांक32 sid;
पूर्ण;

/**
 * vmw_view - Convert a काष्ठा vmw_resource to a काष्ठा vmw_view
 *
 * @res: Poपूर्णांकer to the resource to convert.
 *
 * Returns a poपूर्णांकer to a काष्ठा vmw_view.
 */
अटल काष्ठा vmw_view *vmw_view(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_view, res);
पूर्ण

/**
 * vmw_view_commit_notअगरy - Notअगरy that a view operation has been committed to
 * hardware from a user-supplied command stream.
 *
 * @res: Poपूर्णांकer to the view resource.
 * @state: Indicating whether a creation or removal has been committed.
 *
 */
अटल व्योम vmw_view_commit_notअगरy(काष्ठा vmw_resource *res,
				   क्रमागत vmw_cmdbuf_res_state state)
अणु
	काष्ठा vmw_view *view = vmw_view(res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	mutex_lock(&dev_priv->binding_mutex);
	अगर (state == VMW_CMDBUF_RES_ADD) अणु
		काष्ठा vmw_surface *srf = vmw_res_to_srf(view->srf);

		list_add_tail(&view->srf_head, &srf->view_list);
		vmw_cotable_add_resource(view->cotable, &view->cotable_head);
		view->committed = true;
		res->id = view->view_id;

	पूर्ण अन्यथा अणु
		list_del_init(&view->cotable_head);
		list_del_init(&view->srf_head);
		view->committed = false;
		res->id = -1;
	पूर्ण
	mutex_unlock(&dev_priv->binding_mutex);
पूर्ण

/**
 * vmw_view_create - Create a hardware view.
 *
 * @res: Poपूर्णांकer to the view resource.
 *
 * Create a hardware view. Typically used अगर that view has previously been
 * destroyed by an eviction operation.
 */
अटल पूर्णांक vmw_view_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_view *view = vmw_view(res);
	काष्ठा vmw_surface *srf = vmw_res_to_srf(view->srf);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		काष्ठा vmw_view_define body;
	पूर्ण *cmd;

	mutex_lock(&dev_priv->binding_mutex);
	अगर (!view->committed) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस 0;
	पूर्ण

	cmd = VMW_CMD_CTX_RESERVE(res->dev_priv, view->cmd_size, view->ctx->id);
	अगर (!cmd) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(cmd, &view->cmd, view->cmd_size);
	WARN_ON(cmd->body.view_id != view->view_id);
	/* Sid may have changed due to surface eviction. */
	WARN_ON(view->srf->id == SVGA3D_INVALID_ID);
	cmd->body.sid = view->srf->id;
	vmw_cmd_commit(res->dev_priv, view->cmd_size);
	res->id = view->view_id;
	list_add_tail(&view->srf_head, &srf->view_list);
	vmw_cotable_add_resource(view->cotable, &view->cotable_head);
	mutex_unlock(&dev_priv->binding_mutex);

	वापस 0;
पूर्ण

/**
 * vmw_view_destroy - Destroy a hardware view.
 *
 * @res: Poपूर्णांकer to the view resource.
 *
 * Destroy a hardware view. Typically used on unexpected termination of the
 * owning process or अगर the surface the view is poपूर्णांकing to is destroyed.
 */
अटल पूर्णांक vmw_view_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_view *view = vmw_view(res);
	काष्ठा अणु
		SVGA3dCmdHeader header;
		जोड़ vmw_view_destroy body;
	पूर्ण *cmd;

	lockdep_निश्चित_held_once(&dev_priv->binding_mutex);
	vmw_binding_res_list_scrub(&res->binding_head);

	अगर (!view->committed || res->id == -1)
		वापस 0;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), view->ctx->id);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = vmw_view_destroy_cmds[view->view_type];
	cmd->header.size = माप(cmd->body);
	cmd->body.view_id = view->view_id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	res->id = -1;
	list_del_init(&view->cotable_head);
	list_del_init(&view->srf_head);

	वापस 0;
पूर्ण

/**
 * vmw_hw_view_destroy - Destroy a hardware view as part of resource cleanup.
 *
 * @res: Poपूर्णांकer to the view resource.
 *
 * Destroy a hardware view अगर it's still present.
 */
अटल व्योम vmw_hw_view_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	mutex_lock(&dev_priv->binding_mutex);
	WARN_ON(vmw_view_destroy(res));
	res->id = -1;
	mutex_unlock(&dev_priv->binding_mutex);
पूर्ण

/**
 * vmw_view_key - Compute a view key suitable क्रम the cmdbuf resource manager
 *
 * @user_key: The user-space id used क्रम the view.
 * @view_type: The view type.
 *
 * Destroy a hardware view अगर it's still present.
 */
अटल u32 vmw_view_key(u32 user_key, क्रमागत vmw_view_type view_type)
अणु
	वापस user_key | (view_type << 20);
पूर्ण

/**
 * vmw_view_id_ok - Basic view id and type range checks.
 *
 * @user_key: The user-space id used क्रम the view.
 * @view_type: The view type.
 *
 * Checks that the view id and type (typically provided by user-space) is
 * valid.
 */
अटल bool vmw_view_id_ok(u32 user_key, क्रमागत vmw_view_type view_type)
अणु
	वापस (user_key < SVGA_COTABLE_MAX_IDS &&
		view_type < vmw_view_max);
पूर्ण

/**
 * vmw_view_res_मुक्त - resource res_मुक्त callback क्रम view resources
 *
 * @res: Poपूर्णांकer to a काष्ठा vmw_resource
 *
 * Frees memory and memory accounting held by a काष्ठा vmw_view.
 */
अटल व्योम vmw_view_res_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_view *view = vmw_view(res);
	माप_प्रकार size = दुरत्व(काष्ठा vmw_view, cmd) + view->cmd_size;
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	vmw_resource_unreference(&view->cotable);
	vmw_resource_unreference(&view->srf);
	kमुक्त_rcu(view, rcu);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), size);
पूर्ण

/**
 * vmw_view_add - Create a view resource and stage it क्रम addition
 * as a command buffer managed resource.
 *
 * @man: Poपूर्णांकer to the compat shader manager identअगरying the shader namespace.
 * @ctx: Poपूर्णांकer to a काष्ठा vmw_resource identअगरying the active context.
 * @srf: Poपूर्णांकer to a काष्ठा vmw_resource identअगरying the surface the view
 * poपूर्णांकs to.
 * @view_type: The view type deduced from the view create command.
 * @user_key: The key that is used to identअगरy the shader. The key is
 * unique to the view type and to the context.
 * @cmd: Poपूर्णांकer to the view create command in the command stream.
 * @cmd_size: Size of the view create command in the command stream.
 * @list: Caller's list of staged command buffer resource actions.
 */
पूर्णांक vmw_view_add(काष्ठा vmw_cmdbuf_res_manager *man,
		 काष्ठा vmw_resource *ctx,
		 काष्ठा vmw_resource *srf,
		 क्रमागत vmw_view_type view_type,
		 u32 user_key,
		 स्थिर व्योम *cmd,
		 माप_प्रकार cmd_size,
		 काष्ठा list_head *list)
अणु
	अटल स्थिर माप_प्रकार vmw_view_define_sizes[] = अणु
		[vmw_view_sr] = माप(SVGA3dCmdDXDefineShaderResourceView),
		[vmw_view_rt] = माप(SVGA3dCmdDXDefineRenderTargetView),
		[vmw_view_ds] = माप(SVGA3dCmdDXDefineDepthStencilView),
		[vmw_view_ua] = माप(SVGA3dCmdDXDefineUAView)
	पूर्ण;

	काष्ठा vmw_निजी *dev_priv = ctx->dev_priv;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_view *view;
	काष्ठा tपंचांग_operation_ctx tपंचांग_opt_ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (cmd_size != vmw_view_define_sizes[view_type] +
	    माप(SVGA3dCmdHeader)) अणु
		VMW_DEBUG_USER("Illegal view create command size.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!vmw_view_id_ok(user_key, view_type)) अणु
		VMW_DEBUG_USER("Illegal view add view id.\n");
		वापस -EINVAL;
	पूर्ण

	size = दुरत्व(काष्ठा vmw_view, cmd) + cmd_size;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv), size, &tपंचांग_opt_ctx);
	अगर (ret) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for view creation\n");
		वापस ret;
	पूर्ण

	view = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!view) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), size);
		वापस -ENOMEM;
	पूर्ण

	res = &view->res;
	view->ctx = ctx;
	view->srf = vmw_resource_reference(srf);
	view->cotable = vmw_resource_reference
		(vmw_context_cotable(ctx, vmw_view_cotables[view_type]));
	view->view_type = view_type;
	view->view_id = user_key;
	view->cmd_size = cmd_size;
	view->committed = false;
	INIT_LIST_HEAD(&view->srf_head);
	INIT_LIST_HEAD(&view->cotable_head);
	स_नकल(&view->cmd, cmd, cmd_size);
	ret = vmw_resource_init(dev_priv, res, true,
				vmw_view_res_मुक्त, &vmw_view_func);
	अगर (ret)
		जाओ out_resource_init;

	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_view,
				 vmw_view_key(user_key, view_type),
				 res, list);
	अगर (ret)
		जाओ out_resource_init;

	res->id = view->view_id;
	res->hw_destroy = vmw_hw_view_destroy;

out_resource_init:
	vmw_resource_unreference(&res);

	वापस ret;
पूर्ण

/**
 * vmw_view_हटाओ - Stage a view क्रम removal.
 *
 * @man: Poपूर्णांकer to the view manager identअगरying the shader namespace.
 * @user_key: The key that is used to identअगरy the view. The key is
 * unique to the view type.
 * @view_type: View type
 * @list: Caller's list of staged command buffer resource actions.
 * @res_p: If the resource is in an alपढ़ोy committed state, poपूर्णांकs to the
 * काष्ठा vmw_resource on successful वापस. The poपूर्णांकer will be
 * non ref-counted.
 */
पूर्णांक vmw_view_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
		    u32 user_key, क्रमागत vmw_view_type view_type,
		    काष्ठा list_head *list,
		    काष्ठा vmw_resource **res_p)
अणु
	अगर (!vmw_view_id_ok(user_key, view_type)) अणु
		VMW_DEBUG_USER("Illegal view remove view id.\n");
		वापस -EINVAL;
	पूर्ण

	वापस vmw_cmdbuf_res_हटाओ(man, vmw_cmdbuf_res_view,
				     vmw_view_key(user_key, view_type),
				     list, res_p);
पूर्ण

/**
 * vmw_view_cotable_list_destroy - Evict all views beदीर्घing to a cotable.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @list: List of views beदीर्घing to a cotable.
 * @पढ़ोback: Unused. Needed क्रम function पूर्णांकerface only.
 *
 * This function evicts all views beदीर्घing to a cotable.
 * It must be called with the binding_mutex held, and the caller must hold
 * a reference to the view resource. This is typically called beक्रमe the
 * cotable is paged out.
 */
व्योम vmw_view_cotable_list_destroy(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा list_head *list,
				   bool पढ़ोback)
अणु
	काष्ठा vmw_view *entry, *next;

	lockdep_निश्चित_held_once(&dev_priv->binding_mutex);

	list_क्रम_each_entry_safe(entry, next, list, cotable_head)
		WARN_ON(vmw_view_destroy(&entry->res));
पूर्ण

/**
 * vmw_view_surface_list_destroy - Evict all views poपूर्णांकing to a surface
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @list: List of views poपूर्णांकing to a surface.
 *
 * This function evicts all views poपूर्णांकing to a surface. This is typically
 * called beक्रमe the surface is evicted.
 */
व्योम vmw_view_surface_list_destroy(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा list_head *list)
अणु
	काष्ठा vmw_view *entry, *next;

	lockdep_निश्चित_held_once(&dev_priv->binding_mutex);

	list_क्रम_each_entry_safe(entry, next, list, srf_head)
		WARN_ON(vmw_view_destroy(&entry->res));
पूर्ण

/**
 * vmw_view_srf - Return a non-refcounted poपूर्णांकer to the surface a view is
 * poपूर्णांकing to.
 *
 * @res: poपूर्णांकer to a view resource.
 *
 * Note that the view itself is holding a reference, so as दीर्घ
 * the view resource is alive, the surface resource will be.
 */
काष्ठा vmw_resource *vmw_view_srf(काष्ठा vmw_resource *res)
अणु
	वापस vmw_view(res)->srf;
पूर्ण

/**
 * vmw_view_lookup - Look up a view.
 *
 * @man: The context's cmdbuf ref manager.
 * @view_type: The view type.
 * @user_key: The view user id.
 *
 * वापसs a refcounted poपूर्णांकer to a view or an error poपूर्णांकer अगर not found.
 */
काष्ठा vmw_resource *vmw_view_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
				     क्रमागत vmw_view_type view_type,
				     u32 user_key)
अणु
	वापस vmw_cmdbuf_res_lookup(man, vmw_cmdbuf_res_view,
				     vmw_view_key(user_key, view_type));
पूर्ण

/**
 * vmw_view_dirtying - Return whether a view type is dirtying its resource
 * @res: Poपूर्णांकer to the view
 *
 * Each समय a resource is put on the validation list as the result of a
 * view poपूर्णांकing to it, we need to determine whether that resource will
 * be dirtied (written to by the GPU) as a result of the corresponding
 * GPU operation. Currently only rendertarget-, depth-stencil and unordered
 * access views are capable of dirtying its resource.
 *
 * Return: Whether the view type of @res dirties the resource it poपूर्णांकs to.
 */
u32 vmw_view_dirtying(काष्ठा vmw_resource *res)
अणु
	अटल u32 view_is_dirtying[vmw_view_max] = अणु
		[vmw_view_rt] = VMW_RES_सूचीTY_SET,
		[vmw_view_ds] = VMW_RES_सूचीTY_SET,
		[vmw_view_ua] = VMW_RES_सूचीTY_SET,
	पूर्ण;

	/* Update this function as we add more view types */
	BUILD_BUG_ON(vmw_view_max != 4);
	वापस view_is_dirtying[vmw_view(res)->view_type];
पूर्ण

स्थिर u32 vmw_view_destroy_cmds[] = अणु
	[vmw_view_sr] = SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW,
	[vmw_view_rt] = SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW,
	[vmw_view_ds] = SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW,
	[vmw_view_ua] = SVGA_3D_CMD_DX_DESTROY_UA_VIEW,
पूर्ण;

स्थिर SVGACOTableType vmw_view_cotables[] = अणु
	[vmw_view_sr] = SVGA_COTABLE_SRVIEW,
	[vmw_view_rt] = SVGA_COTABLE_RTVIEW,
	[vmw_view_ds] = SVGA_COTABLE_DSVIEW,
	[vmw_view_ua] = SVGA_COTABLE_UAVIEW,
पूर्ण;

स्थिर SVGACOTableType vmw_so_cotables[] = अणु
	[vmw_so_el] = SVGA_COTABLE_ELEMENTLAYOUT,
	[vmw_so_bs] = SVGA_COTABLE_BLENDSTATE,
	[vmw_so_ds] = SVGA_COTABLE_DEPTHSTENCIL,
	[vmw_so_rs] = SVGA_COTABLE_RASTERIZERSTATE,
	[vmw_so_ss] = SVGA_COTABLE_SAMPLER,
	[vmw_so_so] = SVGA_COTABLE_STREAMOUTPUT
पूर्ण;


/* To हटाओ unused function warning */
अटल व्योम vmw_so_build_निश्चितs(व्योम) __attribute__((used));


/*
 * This function is unused at run-समय, and only used to dump various build
 * निश्चितs important क्रम code optimization assumptions.
 */
अटल व्योम vmw_so_build_निश्चितs(व्योम)
अणु
	/* Assert that our vmw_view_cmd_to_type() function is correct. */
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 1);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DEFINE_RENDERTARGET_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 2);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 3);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 4);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 5);

	/* Assert that our "one body fits all" assumption is valid */
	BUILD_BUG_ON(माप(जोड़ vmw_view_destroy) != माप(u32));

	/* Assert that the view key space can hold all view ids. */
	BUILD_BUG_ON(SVGA_COTABLE_MAX_IDS >= ((1 << 20) - 1));

	/*
	 * Assert that the offset of sid in all view define commands
	 * is what we assume it to be.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा vmw_view_define, sid) !=
		     दुरत्व(SVGA3dCmdDXDefineShaderResourceView, sid));
	BUILD_BUG_ON(दुरत्व(काष्ठा vmw_view_define, sid) !=
		     दुरत्व(SVGA3dCmdDXDefineRenderTargetView, sid));
	BUILD_BUG_ON(दुरत्व(काष्ठा vmw_view_define, sid) !=
		     दुरत्व(SVGA3dCmdDXDefineDepthStencilView, sid));
पूर्ण
