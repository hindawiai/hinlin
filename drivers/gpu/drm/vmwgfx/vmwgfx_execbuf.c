<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009 - 2015 VMware, Inc., Palo Alto, CA., USA
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
#समावेश <linux/sync_file.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_reg.h"
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश "vmwgfx_so.h"
#समावेश "vmwgfx_binding.h"

#घोषणा VMW_RES_HT_ORDER 12

/*
 * Helper macro to get dx_ctx_node अगर available otherwise prपूर्णांक an error
 * message. This is क्रम use in command verअगरier function where अगर dx_ctx_node
 * is not set then command is invalid.
 */
#घोषणा VMW_GET_CTX_NODE(__sw_context)                                        \
(अणु                                                                            \
	__sw_context->dx_ctx_node ? __sw_context->dx_ctx_node : (अणु            \
		VMW_DEBUG_USER("SM context is not set at %s\n", __func__);    \
		__sw_context->dx_ctx_node;                                    \
	पूर्ण);                                                                   \
पूर्ण)

#घोषणा VMW_DECLARE_CMD_VAR(__var, __type)                                    \
	काष्ठा अणु                                                              \
		SVGA3dCmdHeader header;                                       \
		__type body;                                                  \
	पूर्ण __var

/**
 * काष्ठा vmw_relocation - Buffer object relocation
 *
 * @head: List head क्रम the command submission context's relocation list
 * @vbo: Non ref-counted poपूर्णांकer to buffer object
 * @mob_loc: Poपूर्णांकer to location क्रम mob id to be modअगरied
 * @location: Poपूर्णांकer to location क्रम guest poपूर्णांकer to be modअगरied
 */
काष्ठा vmw_relocation अणु
	काष्ठा list_head head;
	काष्ठा vmw_buffer_object *vbo;
	जोड़ अणु
		SVGAMobId *mob_loc;
		SVGAGuestPtr *location;
	पूर्ण;
पूर्ण;

/**
 * क्रमागत vmw_resource_relocation_type - Relocation type क्रम resources
 *
 * @vmw_res_rel_normal: Traditional relocation. The resource id in the
 * command stream is replaced with the actual id after validation.
 * @vmw_res_rel_nop: NOP relocation. The command is unconditionally replaced
 * with a NOP.
 * @vmw_res_rel_cond_nop: Conditional NOP relocation. If the resource id after
 * validation is -1, the command is replaced with a NOP. Otherwise no action.
 * @vmw_res_rel_max: Last value in the क्रमागत - used क्रम error checking
*/
क्रमागत vmw_resource_relocation_type अणु
	vmw_res_rel_normal,
	vmw_res_rel_nop,
	vmw_res_rel_cond_nop,
	vmw_res_rel_max
पूर्ण;

/**
 * काष्ठा vmw_resource_relocation - Relocation info क्रम resources
 *
 * @head: List head क्रम the software context's relocation list.
 * @res: Non-ref-counted poपूर्णांकer to the resource.
 * @offset: Offset of single byte entries पूर्णांकo the command buffer where the id
 * that needs fixup is located.
 * @rel_type: Type of relocation.
 */
काष्ठा vmw_resource_relocation अणु
	काष्ठा list_head head;
	स्थिर काष्ठा vmw_resource *res;
	u32 offset:29;
	क्रमागत vmw_resource_relocation_type rel_type:3;
पूर्ण;

/**
 * काष्ठा vmw_ctx_validation_info - Extra validation metadata क्रम contexts
 *
 * @head: List head of context list
 * @ctx: The context resource
 * @cur: The context's persistent binding state
 * @staged: The binding state changes of this command buffer
 */
काष्ठा vmw_ctx_validation_info अणु
	काष्ठा list_head head;
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_ctx_binding_state *cur;
	काष्ठा vmw_ctx_binding_state *staged;
पूर्ण;

/**
 * काष्ठा vmw_cmd_entry - Describe a command क्रम the verअगरier
 *
 * @func: Call-back to handle the command.
 * @user_allow: Whether allowed from the execbuf ioctl.
 * @gb_disable: Whether disabled अगर guest-backed objects are available.
 * @gb_enable: Whether enabled अगरf guest-backed objects are available.
 * @cmd_name: Name of the command.
 */
काष्ठा vmw_cmd_entry अणु
	पूर्णांक (*func) (काष्ठा vmw_निजी *, काष्ठा vmw_sw_context *,
		     SVGA3dCmdHeader *);
	bool user_allow;
	bool gb_disable;
	bool gb_enable;
	स्थिर अक्षर *cmd_name;
पूर्ण;

#घोषणा VMW_CMD_DEF(_cmd, _func, _user_allow, _gb_disable, _gb_enable)	\
	[(_cmd) - SVGA_3D_CMD_BASE] = अणु(_func), (_user_allow),\
				       (_gb_disable), (_gb_enable), #_cmdपूर्ण

अटल पूर्णांक vmw_resource_context_res_add(काष्ठा vmw_निजी *dev_priv,
					काष्ठा vmw_sw_context *sw_context,
					काष्ठा vmw_resource *ctx);
अटल पूर्णांक vmw_translate_mob_ptr(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGAMobId *id,
				 काष्ठा vmw_buffer_object **vmw_bo_p);
/**
 * vmw_ptr_dअगरf - Compute the offset from a to b in bytes
 *
 * @a: A starting poपूर्णांकer.
 * @b: A poपूर्णांकer offset in the same address space.
 *
 * Returns: The offset in bytes between the two poपूर्णांकers.
 */
अटल माप_प्रकार vmw_ptr_dअगरf(व्योम *a, व्योम *b)
अणु
	वापस (अचिन्हित दीर्घ) b - (अचिन्हित दीर्घ) a;
पूर्ण

/**
 * vmw_execbuf_bindings_commit - Commit modअगरied binding state
 *
 * @sw_context: The command submission context
 * @backoff: Whether this is part of the error path and binding state changes
 * should be ignored
 */
अटल व्योम vmw_execbuf_bindings_commit(काष्ठा vmw_sw_context *sw_context,
					bool backoff)
अणु
	काष्ठा vmw_ctx_validation_info *entry;

	list_क्रम_each_entry(entry, &sw_context->ctx_list, head) अणु
		अगर (!backoff)
			vmw_binding_state_commit(entry->cur, entry->staged);

		अगर (entry->staged != sw_context->staged_bindings)
			vmw_binding_state_मुक्त(entry->staged);
		अन्यथा
			sw_context->staged_bindings_inuse = false;
	पूर्ण

	/* List entries are मुक्तd with the validation context */
	INIT_LIST_HEAD(&sw_context->ctx_list);
पूर्ण

/**
 * vmw_bind_dx_query_mob - Bind the DX query MOB अगर referenced
 *
 * @sw_context: The command submission context
 */
अटल व्योम vmw_bind_dx_query_mob(काष्ठा vmw_sw_context *sw_context)
अणु
	अगर (sw_context->dx_query_mob)
		vmw_context_bind_dx_query(sw_context->dx_query_ctx,
					  sw_context->dx_query_mob);
पूर्ण

/**
 * vmw_cmd_ctx_first_setup - Perक्रमm the setup needed when a context is added to
 * the validate list.
 *
 * @dev_priv: Poपूर्णांकer to the device निजी:
 * @sw_context: The command submission context
 * @res: Poपूर्णांकer to the resource
 * @node: The validation node holding the context resource metadata
 */
अटल पूर्णांक vmw_cmd_ctx_first_setup(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   काष्ठा vmw_resource *res,
				   काष्ठा vmw_ctx_validation_info *node)
अणु
	पूर्णांक ret;

	ret = vmw_resource_context_res_add(dev_priv, sw_context, res);
	अगर (unlikely(ret != 0))
		जाओ out_err;

	अगर (!sw_context->staged_bindings) अणु
		sw_context->staged_bindings = vmw_binding_state_alloc(dev_priv);
		अगर (IS_ERR(sw_context->staged_bindings)) अणु
			ret = PTR_ERR(sw_context->staged_bindings);
			sw_context->staged_bindings = शून्य;
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (sw_context->staged_bindings_inuse) अणु
		node->staged = vmw_binding_state_alloc(dev_priv);
		अगर (IS_ERR(node->staged)) अणु
			ret = PTR_ERR(node->staged);
			node->staged = शून्य;
			जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		node->staged = sw_context->staged_bindings;
		sw_context->staged_bindings_inuse = true;
	पूर्ण

	node->ctx = res;
	node->cur = vmw_context_binding_state(res);
	list_add_tail(&node->head, &sw_context->ctx_list);

	वापस 0;

out_err:
	वापस ret;
पूर्ण

/**
 * vmw_execbuf_res_size - calculate extra size क्रमe the resource validation node
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठा.
 * @res_type: The resource type.
 *
 * Guest-backed contexts and DX contexts require extra size to store execbuf
 * निजी inक्रमmation in the validation node. Typically the binding manager
 * associated data काष्ठाures.
 *
 * Returns: The extra size requirement based on resource type.
 */
अटल अचिन्हित पूर्णांक vmw_execbuf_res_size(काष्ठा vmw_निजी *dev_priv,
					 क्रमागत vmw_res_type res_type)
अणु
	वापस (res_type == vmw_res_dx_context ||
		(res_type == vmw_res_context && dev_priv->has_mob)) ?
		माप(काष्ठा vmw_ctx_validation_info) : 0;
पूर्ण

/**
 * vmw_execbuf_rcache_update - Update a resource-node cache entry
 *
 * @rcache: Poपूर्णांकer to the entry to update.
 * @res: Poपूर्णांकer to the resource.
 * @निजी: Poपूर्णांकer to the execbuf-निजी space in the resource validation
 * node.
 */
अटल व्योम vmw_execbuf_rcache_update(काष्ठा vmw_res_cache_entry *rcache,
				      काष्ठा vmw_resource *res,
				      व्योम *निजी)
अणु
	rcache->res = res;
	rcache->निजी = निजी;
	rcache->valid = 1;
	rcache->valid_handle = 0;
पूर्ण

/**
 * vmw_execbuf_res_noref_val_add - Add a resource described by an unreferenced
 * rcu-रक्षित poपूर्णांकer to the validation list.
 *
 * @sw_context: Poपूर्णांकer to the software context.
 * @res: Unreferenced rcu-रक्षित poपूर्णांकer to the resource.
 * @dirty: Whether to change dirty status.
 *
 * Returns: 0 on success. Negative error code on failure. Typical error codes
 * are %-EINVAL on inconsistency and %-ESRCH अगर the resource was करोomed.
 */
अटल पूर्णांक vmw_execbuf_res_noref_val_add(काष्ठा vmw_sw_context *sw_context,
					 काष्ठा vmw_resource *res,
					 u32 dirty)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;
	क्रमागत vmw_res_type res_type = vmw_res_type(res);
	काष्ठा vmw_res_cache_entry *rcache;
	काष्ठा vmw_ctx_validation_info *ctx_info;
	bool first_usage;
	अचिन्हित पूर्णांक priv_size;

	rcache = &sw_context->res_cache[res_type];
	अगर (likely(rcache->valid && rcache->res == res)) अणु
		अगर (dirty)
			vmw_validation_res_set_dirty(sw_context->ctx,
						     rcache->निजी, dirty);
		vmw_user_resource_noref_release();
		वापस 0;
	पूर्ण

	priv_size = vmw_execbuf_res_size(dev_priv, res_type);
	ret = vmw_validation_add_resource(sw_context->ctx, res, priv_size,
					  dirty, (व्योम **)&ctx_info,
					  &first_usage);
	vmw_user_resource_noref_release();
	अगर (ret)
		वापस ret;

	अगर (priv_size && first_usage) अणु
		ret = vmw_cmd_ctx_first_setup(dev_priv, sw_context, res,
					      ctx_info);
		अगर (ret) अणु
			VMW_DEBUG_USER("Failed first usage context setup.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	vmw_execbuf_rcache_update(rcache, res, ctx_info);
	वापस 0;
पूर्ण

/**
 * vmw_execbuf_res_noctx_val_add - Add a non-context resource to the resource
 * validation list अगर it's not alपढ़ोy on it
 *
 * @sw_context: Poपूर्णांकer to the software context.
 * @res: Poपूर्णांकer to the resource.
 * @dirty: Whether to change dirty status.
 *
 * Returns: Zero on success. Negative error code on failure.
 */
अटल पूर्णांक vmw_execbuf_res_noctx_val_add(काष्ठा vmw_sw_context *sw_context,
					 काष्ठा vmw_resource *res,
					 u32 dirty)
अणु
	काष्ठा vmw_res_cache_entry *rcache;
	क्रमागत vmw_res_type res_type = vmw_res_type(res);
	व्योम *ptr;
	पूर्णांक ret;

	rcache = &sw_context->res_cache[res_type];
	अगर (likely(rcache->valid && rcache->res == res)) अणु
		अगर (dirty)
			vmw_validation_res_set_dirty(sw_context->ctx,
						     rcache->निजी, dirty);
		वापस 0;
	पूर्ण

	ret = vmw_validation_add_resource(sw_context->ctx, res, 0, dirty,
					  &ptr, शून्य);
	अगर (ret)
		वापस ret;

	vmw_execbuf_rcache_update(rcache, res, ptr);

	वापस 0;
पूर्ण

/**
 * vmw_view_res_val_add - Add a view and the surface it's poपूर्णांकing to to the
 * validation list
 *
 * @sw_context: The software context holding the validation list.
 * @view: Poपूर्णांकer to the view resource.
 *
 * Returns 0 अगर success, negative error code otherwise.
 */
अटल पूर्णांक vmw_view_res_val_add(काष्ठा vmw_sw_context *sw_context,
				काष्ठा vmw_resource *view)
अणु
	पूर्णांक ret;

	/*
	 * First add the resource the view is poपूर्णांकing to, otherwise it may be
	 * swapped out when the view is validated.
	 */
	ret = vmw_execbuf_res_noctx_val_add(sw_context, vmw_view_srf(view),
					    vmw_view_dirtying(view));
	अगर (ret)
		वापस ret;

	वापस vmw_execbuf_res_noctx_val_add(sw_context, view,
					     VMW_RES_सूचीTY_NONE);
पूर्ण

/**
 * vmw_view_id_val_add - Look up a view and add it and the surface it's poपूर्णांकing
 * to to the validation list.
 *
 * @sw_context: The software context holding the validation list.
 * @view_type: The view type to look up.
 * @id: view id of the view.
 *
 * The view is represented by a view id and the DX context it's created on, or
 * scheduled क्रम creation on. If there is no DX context set, the function will
 * वापस an -EINVAL error poपूर्णांकer.
 *
 * Returns: Unreferenced poपूर्णांकer to the resource on success, negative error
 * poपूर्णांकer on failure.
 */
अटल काष्ठा vmw_resource *
vmw_view_id_val_add(काष्ठा vmw_sw_context *sw_context,
		    क्रमागत vmw_view_type view_type, u32 id)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = sw_context->dx_ctx_node;
	काष्ठा vmw_resource *view;
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस ERR_PTR(-EINVAL);

	view = vmw_view_lookup(sw_context->man, view_type, id);
	अगर (IS_ERR(view))
		वापस view;

	ret = vmw_view_res_val_add(sw_context, view);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस view;
पूर्ण

/**
 * vmw_resource_context_res_add - Put resources previously bound to a context on
 * the validation list
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure
 * @sw_context: Poपूर्णांकer to a software context used क्रम this command submission
 * @ctx: Poपूर्णांकer to the context resource
 *
 * This function माला_दो all resources that were previously bound to @ctx on the
 * resource validation list. This is part of the context state reemission
 */
अटल पूर्णांक vmw_resource_context_res_add(काष्ठा vmw_निजी *dev_priv,
					काष्ठा vmw_sw_context *sw_context,
					काष्ठा vmw_resource *ctx)
अणु
	काष्ठा list_head *binding_list;
	काष्ठा vmw_ctx_bindinfo *entry;
	पूर्णांक ret = 0;
	काष्ठा vmw_resource *res;
	u32 i;
	u32 cotable_max = has_sm5_context(ctx->dev_priv) ?
		SVGA_COTABLE_MAX : SVGA_COTABLE_DX10_MAX;

	/* Add all cotables to the validation list. */
	अगर (has_sm4_context(dev_priv) &&
	    vmw_res_type(ctx) == vmw_res_dx_context) अणु
		क्रम (i = 0; i < cotable_max; ++i) अणु
			res = vmw_context_cotable(ctx, i);
			अगर (IS_ERR(res))
				जारी;

			ret = vmw_execbuf_res_noctx_val_add(sw_context, res,
							    VMW_RES_सूचीTY_SET);
			अगर (unlikely(ret != 0))
				वापस ret;
		पूर्ण
	पूर्ण

	/* Add all resources bound to the context to the validation list */
	mutex_lock(&dev_priv->binding_mutex);
	binding_list = vmw_context_binding_list(ctx);

	list_क्रम_each_entry(entry, binding_list, ctx_list) अणु
		अगर (vmw_res_type(entry->res) == vmw_res_view)
			ret = vmw_view_res_val_add(sw_context, entry->res);
		अन्यथा
			ret = vmw_execbuf_res_noctx_val_add
				(sw_context, entry->res,
				 vmw_binding_dirtying(entry->bt));
		अगर (unlikely(ret != 0))
			अवरोध;
	पूर्ण

	अगर (has_sm4_context(dev_priv) &&
	    vmw_res_type(ctx) == vmw_res_dx_context) अणु
		काष्ठा vmw_buffer_object *dx_query_mob;

		dx_query_mob = vmw_context_get_dx_query_mob(ctx);
		अगर (dx_query_mob)
			ret = vmw_validation_add_bo(sw_context->ctx,
						    dx_query_mob, true, false);
	पूर्ण

	mutex_unlock(&dev_priv->binding_mutex);
	वापस ret;
पूर्ण

/**
 * vmw_resource_relocation_add - Add a relocation to the relocation list
 *
 * @sw_context: Poपूर्णांकer to the software context.
 * @res: The resource.
 * @offset: Offset पूर्णांकo the command buffer currently being parsed where the id
 * that needs fixup is located. Granularity is one byte.
 * @rel_type: Relocation type.
 */
अटल पूर्णांक vmw_resource_relocation_add(काष्ठा vmw_sw_context *sw_context,
				       स्थिर काष्ठा vmw_resource *res,
				       अचिन्हित दीर्घ offset,
				       क्रमागत vmw_resource_relocation_type
				       rel_type)
अणु
	काष्ठा vmw_resource_relocation *rel;

	rel = vmw_validation_mem_alloc(sw_context->ctx, माप(*rel));
	अगर (unlikely(!rel)) अणु
		VMW_DEBUG_USER("Failed to allocate a resource relocation.\n");
		वापस -ENOMEM;
	पूर्ण

	rel->res = res;
	rel->offset = offset;
	rel->rel_type = rel_type;
	list_add_tail(&rel->head, &sw_context->res_relocations);

	वापस 0;
पूर्ण

/**
 * vmw_resource_relocations_मुक्त - Free all relocations on a list
 *
 * @list: Poपूर्णांकer to the head of the relocation list
 */
अटल व्योम vmw_resource_relocations_मुक्त(काष्ठा list_head *list)
अणु
	/* Memory is validation context memory, so no need to मुक्त it */
	INIT_LIST_HEAD(list);
पूर्ण

/**
 * vmw_resource_relocations_apply - Apply all relocations on a list
 *
 * @cb: Poपूर्णांकer to the start of the command buffer bein patch. This need not be
 * the same buffer as the one being parsed when the relocation list was built,
 * but the contents must be the same modulo the resource ids.
 * @list: Poपूर्णांकer to the head of the relocation list.
 */
अटल व्योम vmw_resource_relocations_apply(uपूर्णांक32_t *cb,
					   काष्ठा list_head *list)
अणु
	काष्ठा vmw_resource_relocation *rel;

	/* Validate the काष्ठा vmw_resource_relocation member size */
	BUILD_BUG_ON(SVGA_CB_MAX_SIZE >= (1 << 29));
	BUILD_BUG_ON(vmw_res_rel_max >= (1 << 3));

	list_क्रम_each_entry(rel, list, head) अणु
		u32 *addr = (u32 *)((अचिन्हित दीर्घ) cb + rel->offset);
		चयन (rel->rel_type) अणु
		हाल vmw_res_rel_normal:
			*addr = rel->res->id;
			अवरोध;
		हाल vmw_res_rel_nop:
			*addr = SVGA_3D_CMD_NOP;
			अवरोध;
		शेष:
			अगर (rel->res->id == -1)
				*addr = SVGA_3D_CMD_NOP;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक vmw_cmd_invalid(काष्ठा vmw_निजी *dev_priv,
			   काष्ठा vmw_sw_context *sw_context,
			   SVGA3dCmdHeader *header)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vmw_cmd_ok(काष्ठा vmw_निजी *dev_priv,
		      काष्ठा vmw_sw_context *sw_context,
		      SVGA3dCmdHeader *header)
अणु
	वापस 0;
पूर्ण

/**
 * vmw_resources_reserve - Reserve all resources on the sw_context's resource
 * list.
 *
 * @sw_context: Poपूर्णांकer to the software context.
 *
 * Note that since vmware's command submission currently is रक्षित by the
 * cmdbuf mutex, no fancy deadlock aव्योमance is required क्रम resources, since
 * only a single thपढ़ो at once will attempt this.
 */
अटल पूर्णांक vmw_resources_reserve(काष्ठा vmw_sw_context *sw_context)
अणु
	पूर्णांक ret;

	ret = vmw_validation_res_reserve(sw_context->ctx, true);
	अगर (ret)
		वापस ret;

	अगर (sw_context->dx_query_mob) अणु
		काष्ठा vmw_buffer_object *expected_dx_query_mob;

		expected_dx_query_mob =
			vmw_context_get_dx_query_mob(sw_context->dx_query_ctx);
		अगर (expected_dx_query_mob &&
		    expected_dx_query_mob != sw_context->dx_query_mob) अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * vmw_cmd_res_check - Check that a resource is present and अगर so, put it on the
 * resource validate list unless it's alपढ़ोy there.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @sw_context: Poपूर्णांकer to the software context.
 * @res_type: Resource type.
 * @dirty: Whether to change dirty status.
 * @converter: User-space visisble type specअगरic inक्रमmation.
 * @id_loc: Poपूर्णांकer to the location in the command buffer currently being parsed
 * from where the user-space resource id handle is located.
 * @p_res: Poपूर्णांकer to poपूर्णांकer to resource validalidation node. Populated on
 * निकास.
 */
अटल पूर्णांक
vmw_cmd_res_check(काष्ठा vmw_निजी *dev_priv,
		  काष्ठा vmw_sw_context *sw_context,
		  क्रमागत vmw_res_type res_type,
		  u32 dirty,
		  स्थिर काष्ठा vmw_user_resource_conv *converter,
		  uपूर्णांक32_t *id_loc,
		  काष्ठा vmw_resource **p_res)
अणु
	काष्ठा vmw_res_cache_entry *rcache = &sw_context->res_cache[res_type];
	काष्ठा vmw_resource *res;
	पूर्णांक ret;

	अगर (p_res)
		*p_res = शून्य;

	अगर (*id_loc == SVGA3D_INVALID_ID) अणु
		अगर (res_type == vmw_res_context) अणु
			VMW_DEBUG_USER("Illegal context invalid id.\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (likely(rcache->valid_handle && *id_loc == rcache->handle)) अणु
		res = rcache->res;
		अगर (dirty)
			vmw_validation_res_set_dirty(sw_context->ctx,
						     rcache->निजी, dirty);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक size = vmw_execbuf_res_size(dev_priv, res_type);

		ret = vmw_validation_preload_res(sw_context->ctx, size);
		अगर (ret)
			वापस ret;

		res = vmw_user_resource_noref_lookup_handle
			(dev_priv, sw_context->fp->tfile, *id_loc, converter);
		अगर (IS_ERR(res)) अणु
			VMW_DEBUG_USER("Could not find/use resource 0x%08x.\n",
				       (अचिन्हित पूर्णांक) *id_loc);
			वापस PTR_ERR(res);
		पूर्ण

		ret = vmw_execbuf_res_noref_val_add(sw_context, res, dirty);
		अगर (unlikely(ret != 0))
			वापस ret;

		अगर (rcache->valid && rcache->res == res) अणु
			rcache->valid_handle = true;
			rcache->handle = *id_loc;
		पूर्ण
	पूर्ण

	ret = vmw_resource_relocation_add(sw_context, res,
					  vmw_ptr_dअगरf(sw_context->buf_start,
						       id_loc),
					  vmw_res_rel_normal);
	अगर (p_res)
		*p_res = res;

	वापस 0;
पूर्ण

/**
 * vmw_rebind_dx_query - Rebind DX query associated with the context
 *
 * @ctx_res: context the query beदीर्घs to
 *
 * This function assumes binding_mutex is held.
 */
अटल पूर्णांक vmw_rebind_all_dx_query(काष्ठा vmw_resource *ctx_res)
अणु
	काष्ठा vmw_निजी *dev_priv = ctx_res->dev_priv;
	काष्ठा vmw_buffer_object *dx_query_mob;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXBindAllQuery);

	dx_query_mob = vmw_context_get_dx_query_mob(ctx_res);

	अगर (!dx_query_mob || dx_query_mob->dx_query_ctx)
		वापस 0;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), ctx_res->id);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_BIND_ALL_QUERY;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = ctx_res->id;
	cmd->body.mobid = dx_query_mob->base.mem.start;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	vmw_context_bind_dx_query(ctx_res, dx_query_mob);

	वापस 0;
पूर्ण

/**
 * vmw_rebind_contexts - Rebind all resources previously bound to referenced
 * contexts.
 *
 * @sw_context: Poपूर्णांकer to the software context.
 *
 * Rebind context binding poपूर्णांकs that have been scrubbed because of eviction.
 */
अटल पूर्णांक vmw_rebind_contexts(काष्ठा vmw_sw_context *sw_context)
अणु
	काष्ठा vmw_ctx_validation_info *val;
	पूर्णांक ret;

	list_क्रम_each_entry(val, &sw_context->ctx_list, head) अणु
		ret = vmw_binding_rebind_all(val->cur);
		अगर (unlikely(ret != 0)) अणु
			अगर (ret != -ERESTARTSYS)
				VMW_DEBUG_USER("Failed to rebind context.\n");
			वापस ret;
		पूर्ण

		ret = vmw_rebind_all_dx_query(val->ctx);
		अगर (ret != 0) अणु
			VMW_DEBUG_USER("Failed to rebind queries.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_view_bindings_add - Add an array of view bindings to a context binding
 * state tracker.
 *
 * @sw_context: The execbuf state used क्रम this command.
 * @view_type: View type क्रम the bindings.
 * @binding_type: Binding type क्रम the bindings.
 * @shader_slot: The shader slot to user क्रम the bindings.
 * @view_ids: Array of view ids to be bound.
 * @num_views: Number of view ids in @view_ids.
 * @first_slot: The binding slot to be used क्रम the first view id in @view_ids.
 */
अटल पूर्णांक vmw_view_bindings_add(काष्ठा vmw_sw_context *sw_context,
				 क्रमागत vmw_view_type view_type,
				 क्रमागत vmw_ctx_binding_type binding_type,
				 uपूर्णांक32 shader_slot,
				 uपूर्णांक32 view_ids[], u32 num_views,
				 u32 first_slot)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	u32 i;

	अगर (!ctx_node)
		वापस -EINVAL;

	क्रम (i = 0; i < num_views; ++i) अणु
		काष्ठा vmw_ctx_bindinfo_view binding;
		काष्ठा vmw_resource *view = शून्य;

		अगर (view_ids[i] != SVGA3D_INVALID_ID) अणु
			view = vmw_view_id_val_add(sw_context, view_type,
						   view_ids[i]);
			अगर (IS_ERR(view)) अणु
				VMW_DEBUG_USER("View not found.\n");
				वापस PTR_ERR(view);
			पूर्ण
		पूर्ण
		binding.bi.ctx = ctx_node->ctx;
		binding.bi.res = view;
		binding.bi.bt = binding_type;
		binding.shader_slot = shader_slot;
		binding.slot = first_slot + i;
		vmw_binding_add(ctx_node->staged, &binding.bi,
				shader_slot, binding.slot);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_cmd_cid_check - Check a command header क्रम valid context inक्रमmation.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @sw_context: Poपूर्णांकer to the software context.
 * @header: A command header with an embedded user-space context handle.
 *
 * Convenience function: Call vmw_cmd_res_check with the user-space context
 * handle embedded in @header.
 */
अटल पूर्णांक vmw_cmd_cid_check(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा vmw_sw_context *sw_context,
			     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, uपूर्णांक32_t) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				 VMW_RES_सूचीTY_SET, user_context_converter,
				 &cmd->body, शून्य);
पूर्ण

/**
 * vmw_execbuf_info_from_res - Get the निजी validation metadata क्रम a
 * recently validated resource
 *
 * @sw_context: Poपूर्णांकer to the command submission context
 * @res: The resource
 *
 * The resource poपूर्णांकed to by @res needs to be present in the command submission
 * context's resource cache and hence the last resource of that type to be
 * processed by the validation code.
 *
 * Return: a poपूर्णांकer to the निजी metadata of the resource, or शून्य अगर it
 * wasn't found
 */
अटल काष्ठा vmw_ctx_validation_info *
vmw_execbuf_info_from_res(काष्ठा vmw_sw_context *sw_context,
			  काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_res_cache_entry *rcache =
		&sw_context->res_cache[vmw_res_type(res)];

	अगर (rcache->valid && rcache->res == res)
		वापस rcache->निजी;

	WARN_ON_ONCE(true);
	वापस शून्य;
पूर्ण

अटल पूर्णांक vmw_cmd_set_render_target_check(काष्ठा vmw_निजी *dev_priv,
					   काष्ठा vmw_sw_context *sw_context,
					   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSetRenderTarget);
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_resource *res;
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);

	अगर (cmd->body.type >= SVGA3D_RT_MAX) अणु
		VMW_DEBUG_USER("Illegal render target type %u.\n",
			       (अचिन्हित पूर्णांक) cmd->body.type);
		वापस -EINVAL;
	पूर्ण

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				VMW_RES_सूचीTY_SET, user_context_converter,
				&cmd->body.cid, &ctx);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_SET, user_surface_converter,
				&cmd->body.target.sid, &res);
	अगर (unlikely(ret))
		वापस ret;

	अगर (dev_priv->has_mob) अणु
		काष्ठा vmw_ctx_bindinfo_view binding;
		काष्ठा vmw_ctx_validation_info *node;

		node = vmw_execbuf_info_from_res(sw_context, ctx);
		अगर (!node)
			वापस -EINVAL;

		binding.bi.ctx = ctx;
		binding.bi.res = res;
		binding.bi.bt = vmw_ctx_binding_rt;
		binding.slot = cmd->body.type;
		vmw_binding_add(node->staged, &binding.bi, 0, binding.slot);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_surface_copy_check(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा vmw_sw_context *sw_context,
				      SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSurfaceCopy);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.src.sid, शून्य);
	अगर (ret)
		वापस ret;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_SET, user_surface_converter,
				 &cmd->body.dest.sid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_buffer_copy_check(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXBufferCopy);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.src, शून्य);
	अगर (ret != 0)
		वापस ret;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_SET, user_surface_converter,
				 &cmd->body.dest, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_pred_copy_check(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXPredCopyRegion);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.srcSid, शून्य);
	अगर (ret != 0)
		वापस ret;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_SET, user_surface_converter,
				 &cmd->body.dstSid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_stretch_blt_check(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSurfaceStretchBlt);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.src.sid, शून्य);
	अगर (unlikely(ret != 0))
		वापस ret;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_SET, user_surface_converter,
				 &cmd->body.dest.sid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_blt_surf_screen_check(काष्ठा vmw_निजी *dev_priv,
					 काष्ठा vmw_sw_context *sw_context,
					 SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdBlitSurfaceToScreen) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.srcImage.sid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_present_check(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdPresent) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.sid, शून्य);
पूर्ण

/**
 * vmw_query_bo_चयन_prepare - Prepare to चयन pinned buffer क्रम queries.
 *
 * @dev_priv: The device निजी काष्ठाure.
 * @new_query_bo: The new buffer holding query results.
 * @sw_context: The software context used क्रम this command submission.
 *
 * This function checks whether @new_query_bo is suitable क्रम holding query
 * results, and अगर another buffer currently is pinned क्रम query results. If so,
 * the function prepares the state of @sw_context क्रम चयनing pinned buffers
 * after successful submission of the current command batch.
 */
अटल पूर्णांक vmw_query_bo_चयन_prepare(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_buffer_object *new_query_bo,
				       काष्ठा vmw_sw_context *sw_context)
अणु
	काष्ठा vmw_res_cache_entry *ctx_entry =
		&sw_context->res_cache[vmw_res_context];
	पूर्णांक ret;

	BUG_ON(!ctx_entry->valid);
	sw_context->last_query_ctx = ctx_entry->res;

	अगर (unlikely(new_query_bo != sw_context->cur_query_bo)) अणु

		अगर (unlikely(new_query_bo->base.mem.num_pages > 4)) अणु
			VMW_DEBUG_USER("Query buffer too large.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (unlikely(sw_context->cur_query_bo != शून्य)) अणु
			sw_context->needs_post_query_barrier = true;
			ret = vmw_validation_add_bo(sw_context->ctx,
						    sw_context->cur_query_bo,
						    dev_priv->has_mob, false);
			अगर (unlikely(ret != 0))
				वापस ret;
		पूर्ण
		sw_context->cur_query_bo = new_query_bo;

		ret = vmw_validation_add_bo(sw_context->ctx,
					    dev_priv->dummy_query_bo,
					    dev_priv->has_mob, false);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_query_bo_चयन_commit - Finalize चयनing pinned query buffer
 *
 * @dev_priv: The device निजी काष्ठाure.
 * @sw_context: The software context used क्रम this command submission batch.
 *
 * This function will check अगर we're चयनing query buffers, and will then,
 * issue a dummy occlusion query रुको used as a query barrier. When the fence
 * object following that query रुको has संकेतed, we are sure that all preceding
 * queries have finished, and the old query buffer can be unpinned. However,
 * since both the new query buffer and the old one are fenced with that fence,
 * we can करो an asynchronus unpin now, and be sure that the old query buffer
 * won't be moved until the fence has संकेतed.
 *
 * As mentioned above, both the new - and old query buffers need to be fenced
 * using a sequence emitted *after* calling this function.
 */
अटल व्योम vmw_query_bo_चयन_commit(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context)
अणु
	/*
	 * The validate list should still hold references to all
	 * contexts here.
	 */
	अगर (sw_context->needs_post_query_barrier) अणु
		काष्ठा vmw_res_cache_entry *ctx_entry =
			&sw_context->res_cache[vmw_res_context];
		काष्ठा vmw_resource *ctx;
		पूर्णांक ret;

		BUG_ON(!ctx_entry->valid);
		ctx = ctx_entry->res;

		ret = vmw_cmd_emit_dummy_query(dev_priv, ctx->id);

		अगर (unlikely(ret != 0))
			VMW_DEBUG_USER("Out of fifo space for dummy query.\n");
	पूर्ण

	अगर (dev_priv->pinned_bo != sw_context->cur_query_bo) अणु
		अगर (dev_priv->pinned_bo) अणु
			vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
			vmw_bo_unreference(&dev_priv->pinned_bo);
		पूर्ण

		अगर (!sw_context->needs_post_query_barrier) अणु
			vmw_bo_pin_reserved(sw_context->cur_query_bo, true);

			/*
			 * We pin also the dummy_query_bo buffer so that we
			 * करोn't need to validate it when emitting dummy queries
			 * in context destroy paths.
			 */
			अगर (!dev_priv->dummy_query_bo_pinned) अणु
				vmw_bo_pin_reserved(dev_priv->dummy_query_bo,
						    true);
				dev_priv->dummy_query_bo_pinned = true;
			पूर्ण

			BUG_ON(sw_context->last_query_ctx == शून्य);
			dev_priv->query_cid = sw_context->last_query_ctx->id;
			dev_priv->query_cid_valid = true;
			dev_priv->pinned_bo =
				vmw_bo_reference(sw_context->cur_query_bo);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmw_translate_mob_poपूर्णांकer - Prepare to translate a user-space buffer handle
 * to a MOB id.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @sw_context: The software context used क्रम this command batch validation.
 * @id: Poपूर्णांकer to the user-space handle to be translated.
 * @vmw_bo_p: Poपूर्णांकs to a location that, on successful वापस will carry a
 * non-reference-counted poपूर्णांकer to the buffer object identअगरied by the
 * user-space handle in @id.
 *
 * This function saves inक्रमmation needed to translate a user-space buffer
 * handle to a MOB id. The translation करोes not take place immediately, but
 * during a call to vmw_apply_relocations().
 *
 * This function builds a relocation list and a list of buffers to validate. The
 * क्रमmer needs to be मुक्तd using either vmw_apply_relocations() or
 * vmw_मुक्त_relocations(). The latter needs to be मुक्तd using
 * vmw_clear_validations.
 */
अटल पूर्णांक vmw_translate_mob_ptr(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGAMobId *id,
				 काष्ठा vmw_buffer_object **vmw_bo_p)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	uपूर्णांक32_t handle = *id;
	काष्ठा vmw_relocation *reloc;
	पूर्णांक ret;

	vmw_validation_preload_bo(sw_context->ctx);
	vmw_bo = vmw_user_bo_noref_lookup(sw_context->fp->tfile, handle);
	अगर (IS_ERR(vmw_bo)) अणु
		VMW_DEBUG_USER("Could not find or use MOB buffer.\n");
		वापस PTR_ERR(vmw_bo);
	पूर्ण

	ret = vmw_validation_add_bo(sw_context->ctx, vmw_bo, true, false);
	vmw_user_bo_noref_release();
	अगर (unlikely(ret != 0))
		वापस ret;

	reloc = vmw_validation_mem_alloc(sw_context->ctx, माप(*reloc));
	अगर (!reloc)
		वापस -ENOMEM;

	reloc->mob_loc = id;
	reloc->vbo = vmw_bo;

	*vmw_bo_p = vmw_bo;
	list_add_tail(&reloc->head, &sw_context->bo_relocations);

	वापस 0;
पूर्ण

/**
 * vmw_translate_guest_poपूर्णांकer - Prepare to translate a user-space buffer handle
 * to a valid SVGAGuestPtr
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @sw_context: The software context used क्रम this command batch validation.
 * @ptr: Poपूर्णांकer to the user-space handle to be translated.
 * @vmw_bo_p: Poपूर्णांकs to a location that, on successful वापस will carry a
 * non-reference-counted poपूर्णांकer to the DMA buffer identअगरied by the user-space
 * handle in @id.
 *
 * This function saves inक्रमmation needed to translate a user-space buffer
 * handle to a valid SVGAGuestPtr. The translation करोes not take place
 * immediately, but during a call to vmw_apply_relocations().
 *
 * This function builds a relocation list and a list of buffers to validate.
 * The क्रमmer needs to be मुक्तd using either vmw_apply_relocations() or
 * vmw_मुक्त_relocations(). The latter needs to be मुक्तd using
 * vmw_clear_validations.
 */
अटल पूर्णांक vmw_translate_guest_ptr(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGAGuestPtr *ptr,
				   काष्ठा vmw_buffer_object **vmw_bo_p)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	uपूर्णांक32_t handle = ptr->gmrId;
	काष्ठा vmw_relocation *reloc;
	पूर्णांक ret;

	vmw_validation_preload_bo(sw_context->ctx);
	vmw_bo = vmw_user_bo_noref_lookup(sw_context->fp->tfile, handle);
	अगर (IS_ERR(vmw_bo)) अणु
		VMW_DEBUG_USER("Could not find or use GMR region.\n");
		वापस PTR_ERR(vmw_bo);
	पूर्ण

	ret = vmw_validation_add_bo(sw_context->ctx, vmw_bo, false, false);
	vmw_user_bo_noref_release();
	अगर (unlikely(ret != 0))
		वापस ret;

	reloc = vmw_validation_mem_alloc(sw_context->ctx, माप(*reloc));
	अगर (!reloc)
		वापस -ENOMEM;

	reloc->location = ptr;
	reloc->vbo = vmw_bo;
	*vmw_bo_p = vmw_bo;
	list_add_tail(&reloc->head, &sw_context->bo_relocations);

	वापस 0;
पूर्ण

/**
 * vmw_cmd_dx_define_query - validate SVGA_3D_CMD_DX_DEFINE_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 *
 * This function adds the new query पूर्णांकo the query COTABLE
 */
अटल पूर्णांक vmw_cmd_dx_define_query(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXDefineQuery);
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_resource *cotable_res;
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);

	अगर (cmd->body.type <  SVGA3D_QUERYTYPE_MIN ||
	    cmd->body.type >= SVGA3D_QUERYTYPE_MAX)
		वापस -EINVAL;

	cotable_res = vmw_context_cotable(ctx_node->ctx, SVGA_COTABLE_DXQUERY);
	ret = vmw_cotable_notअगरy(cotable_res, cmd->body.queryId);

	वापस ret;
पूर्ण

/**
 * vmw_cmd_dx_bind_query - validate SVGA_3D_CMD_DX_BIND_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 *
 * The query bind operation will eventually associate the query ID with its
 * backing MOB.  In this function, we take the user mode MOB ID and use
 * vmw_translate_mob_ptr() to translate it to its kernel mode equivalent.
 */
अटल पूर्णांक vmw_cmd_dx_bind_query(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXBindQuery);
	काष्ठा vmw_buffer_object *vmw_bo;
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);

	/*
	 * Look up the buffer poपूर्णांकed to by q.mobid, put it on the relocation
	 * list so its kernel mode MOB ID can be filled in later
	 */
	ret = vmw_translate_mob_ptr(dev_priv, sw_context, &cmd->body.mobid,
				    &vmw_bo);

	अगर (ret != 0)
		वापस ret;

	sw_context->dx_query_mob = vmw_bo;
	sw_context->dx_query_ctx = sw_context->dx_ctx_node->ctx;
	वापस 0;
पूर्ण

/**
 * vmw_cmd_begin_gb_query - validate SVGA_3D_CMD_BEGIN_GB_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_begin_gb_query(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdBeginGBQuery) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				 VMW_RES_सूचीTY_SET, user_context_converter,
				 &cmd->body.cid, शून्य);
पूर्ण

/**
 * vmw_cmd_begin_query - validate SVGA_3D_CMD_BEGIN_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_begin_query(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_sw_context *sw_context,
			       SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdBeginQuery) =
		container_of(header, typeof(*cmd), header);

	अगर (unlikely(dev_priv->has_mob)) अणु
		VMW_DECLARE_CMD_VAR(gb_cmd, SVGA3dCmdBeginGBQuery);

		BUG_ON(माप(gb_cmd) != माप(*cmd));

		gb_cmd.header.id = SVGA_3D_CMD_BEGIN_GB_QUERY;
		gb_cmd.header.size = cmd->header.size;
		gb_cmd.body.cid = cmd->body.cid;
		gb_cmd.body.type = cmd->body.type;

		स_नकल(cmd, &gb_cmd, माप(*cmd));
		वापस vmw_cmd_begin_gb_query(dev_priv, sw_context, header);
	पूर्ण

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				 VMW_RES_सूचीTY_SET, user_context_converter,
				 &cmd->body.cid, शून्य);
पूर्ण

/**
 * vmw_cmd_end_gb_query - validate SVGA_3D_CMD_END_GB_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_end_gb_query(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_sw_context *sw_context,
				SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdEndGBQuery);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_cid_check(dev_priv, sw_context, header);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_translate_mob_ptr(dev_priv, sw_context, &cmd->body.mobid,
				    &vmw_bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_query_bo_चयन_prepare(dev_priv, vmw_bo, sw_context);

	वापस ret;
पूर्ण

/**
 * vmw_cmd_end_query - validate SVGA_3D_CMD_END_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_end_query(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा vmw_sw_context *sw_context,
			     SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdEndQuery);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	अगर (dev_priv->has_mob) अणु
		VMW_DECLARE_CMD_VAR(gb_cmd, SVGA3dCmdEndGBQuery);

		BUG_ON(माप(gb_cmd) != माप(*cmd));

		gb_cmd.header.id = SVGA_3D_CMD_END_GB_QUERY;
		gb_cmd.header.size = cmd->header.size;
		gb_cmd.body.cid = cmd->body.cid;
		gb_cmd.body.type = cmd->body.type;
		gb_cmd.body.mobid = cmd->body.guestResult.gmrId;
		gb_cmd.body.offset = cmd->body.guestResult.offset;

		स_नकल(cmd, &gb_cmd, माप(*cmd));
		वापस vmw_cmd_end_gb_query(dev_priv, sw_context, header);
	पूर्ण

	ret = vmw_cmd_cid_check(dev_priv, sw_context, header);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_translate_guest_ptr(dev_priv, sw_context,
				      &cmd->body.guestResult, &vmw_bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_query_bo_चयन_prepare(dev_priv, vmw_bo, sw_context);

	वापस ret;
पूर्ण

/**
 * vmw_cmd_रुको_gb_query - validate SVGA_3D_CMD_WAIT_GB_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_रुको_gb_query(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdWaitForGBQuery);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_cid_check(dev_priv, sw_context, header);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_translate_mob_ptr(dev_priv, sw_context, &cmd->body.mobid,
				    &vmw_bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	वापस 0;
पूर्ण

/**
 * vmw_cmd_रुको_query - validate SVGA_3D_CMD_WAIT_QUERY command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context used क्रम this command submission.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_रुको_query(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_sw_context *sw_context,
			      SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdWaitForQuery);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);
	अगर (dev_priv->has_mob) अणु
		VMW_DECLARE_CMD_VAR(gb_cmd, SVGA3dCmdWaitForGBQuery);

		BUG_ON(माप(gb_cmd) != माप(*cmd));

		gb_cmd.header.id = SVGA_3D_CMD_WAIT_FOR_GB_QUERY;
		gb_cmd.header.size = cmd->header.size;
		gb_cmd.body.cid = cmd->body.cid;
		gb_cmd.body.type = cmd->body.type;
		gb_cmd.body.mobid = cmd->body.guestResult.gmrId;
		gb_cmd.body.offset = cmd->body.guestResult.offset;

		स_नकल(cmd, &gb_cmd, माप(*cmd));
		वापस vmw_cmd_रुको_gb_query(dev_priv, sw_context, header);
	पूर्ण

	ret = vmw_cmd_cid_check(dev_priv, sw_context, header);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_translate_guest_ptr(dev_priv, sw_context,
				      &cmd->body.guestResult, &vmw_bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_dma(काष्ठा vmw_निजी *dev_priv,
		       काष्ठा vmw_sw_context *sw_context,
		       SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_buffer_object *vmw_bo = शून्य;
	काष्ठा vmw_surface *srf = शून्य;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSurfaceDMA);
	पूर्णांक ret;
	SVGA3dCmdSurfaceDMASuffix *suffix;
	uपूर्णांक32_t bo_size;
	bool dirty;

	cmd = container_of(header, typeof(*cmd), header);
	suffix = (SVGA3dCmdSurfaceDMASuffix *)((अचिन्हित दीर्घ) &cmd->body +
					       header->size - माप(*suffix));

	/* Make sure device and verअगरier stays in sync. */
	अगर (unlikely(suffix->suffixSize != माप(*suffix))) अणु
		VMW_DEBUG_USER("Invalid DMA suffix size.\n");
		वापस -EINVAL;
	पूर्ण

	ret = vmw_translate_guest_ptr(dev_priv, sw_context,
				      &cmd->body.guest.ptr, &vmw_bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	/* Make sure DMA करोesn't cross BO boundaries. */
	bo_size = vmw_bo->base.base.size;
	अगर (unlikely(cmd->body.guest.ptr.offset > bo_size)) अणु
		VMW_DEBUG_USER("Invalid DMA offset.\n");
		वापस -EINVAL;
	पूर्ण

	bo_size -= cmd->body.guest.ptr.offset;
	अगर (unlikely(suffix->maximumOffset > bo_size))
		suffix->maximumOffset = bo_size;

	dirty = (cmd->body.transfer == SVGA3D_WRITE_HOST_VRAM) ?
		VMW_RES_सूचीTY_SET : 0;
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				dirty, user_surface_converter,
				&cmd->body.host.sid, शून्य);
	अगर (unlikely(ret != 0)) अणु
		अगर (unlikely(ret != -ERESTARTSYS))
			VMW_DEBUG_USER("could not find surface for DMA.\n");
		वापस ret;
	पूर्ण

	srf = vmw_res_to_srf(sw_context->res_cache[vmw_res_surface].res);

	vmw_kms_cursor_snoop(srf, sw_context->fp->tfile, &vmw_bo->base, header);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_draw(काष्ठा vmw_निजी *dev_priv,
			काष्ठा vmw_sw_context *sw_context,
			SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDrawPrimitives);
	SVGA3dVertexDecl *decl = (SVGA3dVertexDecl *)(
		(अचिन्हित दीर्घ)header + माप(*cmd));
	SVGA3dPrimitiveRange *range;
	uपूर्णांक32_t i;
	uपूर्णांक32_t maxnum;
	पूर्णांक ret;

	ret = vmw_cmd_cid_check(dev_priv, sw_context, header);
	अगर (unlikely(ret != 0))
		वापस ret;

	cmd = container_of(header, typeof(*cmd), header);
	maxnum = (header->size - माप(cmd->body)) / माप(*decl);

	अगर (unlikely(cmd->body.numVertexDecls > maxnum)) अणु
		VMW_DEBUG_USER("Illegal number of vertex declarations.\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cmd->body.numVertexDecls; ++i, ++decl) अणु
		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
					VMW_RES_सूचीTY_NONE,
					user_surface_converter,
					&decl->array.surfaceId, शून्य);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण

	maxnum = (header->size - माप(cmd->body) -
		  cmd->body.numVertexDecls * माप(*decl)) / माप(*range);
	अगर (unlikely(cmd->body.numRanges > maxnum)) अणु
		VMW_DEBUG_USER("Illegal number of index ranges.\n");
		वापस -EINVAL;
	पूर्ण

	range = (SVGA3dPrimitiveRange *) decl;
	क्रम (i = 0; i < cmd->body.numRanges; ++i, ++range) अणु
		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
					VMW_RES_सूचीTY_NONE,
					user_surface_converter,
					&range->indexArray.surfaceId, शून्य);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_tex_state(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा vmw_sw_context *sw_context,
			     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSetTextureState);
	SVGA3dTextureState *last_state = (SVGA3dTextureState *)
	  ((अचिन्हित दीर्घ) header + header->size + माप(header));
	SVGA3dTextureState *cur_state = (SVGA3dTextureState *)
		((अचिन्हित दीर्घ) header + माप(*cmd));
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_resource *res;
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				VMW_RES_सूचीTY_SET, user_context_converter,
				&cmd->body.cid, &ctx);
	अगर (unlikely(ret != 0))
		वापस ret;

	क्रम (; cur_state < last_state; ++cur_state) अणु
		अगर (likely(cur_state->name != SVGA3D_TS_BIND_TEXTURE))
			जारी;

		अगर (cur_state->stage >= SVGA3D_NUM_TEXTURE_UNITS) अणु
			VMW_DEBUG_USER("Illegal texture/sampler unit %u.\n",
				       (अचिन्हित पूर्णांक) cur_state->stage);
			वापस -EINVAL;
		पूर्ण

		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
					VMW_RES_सूचीTY_NONE,
					user_surface_converter,
					&cur_state->value, &res);
		अगर (unlikely(ret != 0))
			वापस ret;

		अगर (dev_priv->has_mob) अणु
			काष्ठा vmw_ctx_bindinfo_tex binding;
			काष्ठा vmw_ctx_validation_info *node;

			node = vmw_execbuf_info_from_res(sw_context, ctx);
			अगर (!node)
				वापस -EINVAL;

			binding.bi.ctx = ctx;
			binding.bi.res = res;
			binding.bi.bt = vmw_ctx_binding_tex;
			binding.texture_stage = cur_state->stage;
			vmw_binding_add(node->staged, &binding.bi, 0,
					binding.texture_stage);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_check_define_gmrfb(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा vmw_sw_context *sw_context,
				      व्योम *buf)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;

	काष्ठा अणु
		uपूर्णांक32_t header;
		SVGAFअगरoCmdDefineGMRFB body;
	पूर्ण *cmd = buf;

	वापस vmw_translate_guest_ptr(dev_priv, sw_context, &cmd->body.ptr,
				       &vmw_bo);
पूर्ण

/**
 * vmw_cmd_res_चयन_backup - Utility function to handle backup buffer
 * चयनing
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @res: Poपूर्णांकer to the resource.
 * @buf_id: Poपूर्णांकer to the user-space backup buffer handle in the command
 * stream.
 * @backup_offset: Offset of backup पूर्णांकo MOB.
 *
 * This function prepares क्रम रेजिस्टरing a चयन of backup buffers in the
 * resource metadata just prior to unreserving. It's basically a wrapper around
 * vmw_cmd_res_चयन_backup with a dअगरferent पूर्णांकerface.
 */
अटल पूर्णांक vmw_cmd_res_चयन_backup(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     काष्ठा vmw_resource *res, uपूर्णांक32_t *buf_id,
				     अचिन्हित दीर्घ backup_offset)
अणु
	काष्ठा vmw_buffer_object *vbo;
	व्योम *info;
	पूर्णांक ret;

	info = vmw_execbuf_info_from_res(sw_context, res);
	अगर (!info)
		वापस -EINVAL;

	ret = vmw_translate_mob_ptr(dev_priv, sw_context, buf_id, &vbo);
	अगर (ret)
		वापस ret;

	vmw_validation_res_चयन_backup(sw_context->ctx, info, vbo,
					 backup_offset);
	वापस 0;
पूर्ण

/**
 * vmw_cmd_चयन_backup - Utility function to handle backup buffer चयनing
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @res_type: The resource type.
 * @converter: Inक्रमmation about user-space binding क्रम this resource type.
 * @res_id: Poपूर्णांकer to the user-space resource handle in the command stream.
 * @buf_id: Poपूर्णांकer to the user-space backup buffer handle in the command
 * stream.
 * @backup_offset: Offset of backup पूर्णांकo MOB.
 *
 * This function prepares क्रम रेजिस्टरing a चयन of backup buffers in the
 * resource metadata just prior to unreserving. It's basically a wrapper around
 * vmw_cmd_res_चयन_backup with a dअगरferent पूर्णांकerface.
 */
अटल पूर्णांक vmw_cmd_चयन_backup(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 क्रमागत vmw_res_type res_type,
				 स्थिर काष्ठा vmw_user_resource_conv
				 *converter, uपूर्णांक32_t *res_id, uपूर्णांक32_t *buf_id,
				 अचिन्हित दीर्घ backup_offset)
अणु
	काष्ठा vmw_resource *res;
	पूर्णांक ret;

	ret = vmw_cmd_res_check(dev_priv, sw_context, res_type,
				VMW_RES_सूचीTY_NONE, converter, res_id, &res);
	अगर (ret)
		वापस ret;

	वापस vmw_cmd_res_चयन_backup(dev_priv, sw_context, res, buf_id,
					 backup_offset);
पूर्ण

/**
 * vmw_cmd_bind_gb_surface - Validate SVGA_3D_CMD_BIND_GB_SURFACE command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_bind_gb_surface(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdBindGBSurface) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_चयन_backup(dev_priv, sw_context, vmw_res_surface,
				     user_surface_converter, &cmd->body.sid,
				     &cmd->body.mobid, 0);
पूर्ण

/**
 * vmw_cmd_update_gb_image - Validate SVGA_3D_CMD_UPDATE_GB_IMAGE command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_update_gb_image(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdUpdateGBImage) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.image.sid, शून्य);
पूर्ण

/**
 * vmw_cmd_update_gb_surface - Validate SVGA_3D_CMD_UPDATE_GB_SURFACE command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_update_gb_surface(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdUpdateGBSurface) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_CLEAR, user_surface_converter,
				 &cmd->body.sid, शून्य);
पूर्ण

/**
 * vmw_cmd_पढ़ोback_gb_image - Validate SVGA_3D_CMD_READBACK_GB_IMAGE command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_पढ़ोback_gb_image(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdReadbackGBImage) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.image.sid, शून्य);
पूर्ण

/**
 * vmw_cmd_पढ़ोback_gb_surface - Validate SVGA_3D_CMD_READBACK_GB_SURFACE
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_पढ़ोback_gb_surface(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_sw_context *sw_context,
				       SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdReadbackGBSurface) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_CLEAR, user_surface_converter,
				 &cmd->body.sid, शून्य);
पूर्ण

/**
 * vmw_cmd_invalidate_gb_image - Validate SVGA_3D_CMD_INVALIDATE_GB_IMAGE
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_invalidate_gb_image(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_sw_context *sw_context,
				       SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdInvalidateGBImage) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.image.sid, शून्य);
पूर्ण

/**
 * vmw_cmd_invalidate_gb_surface - Validate SVGA_3D_CMD_INVALIDATE_GB_SURFACE
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_invalidate_gb_surface(काष्ठा vmw_निजी *dev_priv,
					 काष्ठा vmw_sw_context *sw_context,
					 SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdInvalidateGBSurface) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_CLEAR, user_surface_converter,
				 &cmd->body.sid, शून्य);
पूर्ण

/**
 * vmw_cmd_shader_define - Validate SVGA_3D_CMD_SHADER_DEFINE command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_shader_define(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDefineShader);
	पूर्णांक ret;
	माप_प्रकार size;
	काष्ठा vmw_resource *ctx;

	cmd = container_of(header, typeof(*cmd), header);

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				VMW_RES_सूचीTY_SET, user_context_converter,
				&cmd->body.cid, &ctx);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (unlikely(!dev_priv->has_mob))
		वापस 0;

	size = cmd->header.size - माप(cmd->body);
	ret = vmw_compat_shader_add(dev_priv, vmw_context_res_man(ctx),
				    cmd->body.shid, cmd + 1, cmd->body.type,
				    size, &sw_context->staged_cmd_res);
	अगर (unlikely(ret != 0))
		वापस ret;

	वापस vmw_resource_relocation_add(sw_context, शून्य,
					   vmw_ptr_dअगरf(sw_context->buf_start,
							&cmd->header.id),
					   vmw_res_rel_nop);
पूर्ण

/**
 * vmw_cmd_shader_destroy - Validate SVGA_3D_CMD_SHADER_DESTROY command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_shader_destroy(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDestroyShader);
	पूर्णांक ret;
	काष्ठा vmw_resource *ctx;

	cmd = container_of(header, typeof(*cmd), header);

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				VMW_RES_सूचीTY_SET, user_context_converter,
				&cmd->body.cid, &ctx);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (unlikely(!dev_priv->has_mob))
		वापस 0;

	ret = vmw_shader_हटाओ(vmw_context_res_man(ctx), cmd->body.shid,
				cmd->body.type, &sw_context->staged_cmd_res);
	अगर (unlikely(ret != 0))
		वापस ret;

	वापस vmw_resource_relocation_add(sw_context, शून्य,
					   vmw_ptr_dअगरf(sw_context->buf_start,
							&cmd->header.id),
					   vmw_res_rel_nop);
पूर्ण

/**
 * vmw_cmd_set_shader - Validate SVGA_3D_CMD_SET_SHADER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_set_shader(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_sw_context *sw_context,
			      SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSetShader);
	काष्ठा vmw_ctx_bindinfo_shader binding;
	काष्ठा vmw_resource *ctx, *res = शून्य;
	काष्ठा vmw_ctx_validation_info *ctx_info;
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);

	अगर (cmd->body.type >= SVGA3D_SHADERTYPE_PREDX_MAX) अणु
		VMW_DEBUG_USER("Illegal shader type %u.\n",
			       (अचिन्हित पूर्णांक) cmd->body.type);
		वापस -EINVAL;
	पूर्ण

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				VMW_RES_सूचीTY_SET, user_context_converter,
				&cmd->body.cid, &ctx);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (!dev_priv->has_mob)
		वापस 0;

	अगर (cmd->body.shid != SVGA3D_INVALID_ID) अणु
		/*
		 * This is the compat shader path - Per device guest-backed
		 * shaders, but user-space thinks it's per context host-
		 * backed shaders.
		 */
		res = vmw_shader_lookup(vmw_context_res_man(ctx),
					cmd->body.shid, cmd->body.type);
		अगर (!IS_ERR(res)) अणु
			ret = vmw_execbuf_res_noctx_val_add(sw_context, res,
							    VMW_RES_सूचीTY_NONE);
			अगर (unlikely(ret != 0))
				वापस ret;

			ret = vmw_resource_relocation_add
				(sw_context, res,
				 vmw_ptr_dअगरf(sw_context->buf_start,
					      &cmd->body.shid),
				 vmw_res_rel_normal);
			अगर (unlikely(ret != 0))
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (IS_ERR_OR_शून्य(res)) अणु
		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_shader,
					VMW_RES_सूचीTY_NONE,
					user_shader_converter, &cmd->body.shid,
					&res);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण

	ctx_info = vmw_execbuf_info_from_res(sw_context, ctx);
	अगर (!ctx_info)
		वापस -EINVAL;

	binding.bi.ctx = ctx;
	binding.bi.res = res;
	binding.bi.bt = vmw_ctx_binding_shader;
	binding.shader_slot = cmd->body.type - SVGA3D_SHADERTYPE_MIN;
	vmw_binding_add(ctx_info->staged, &binding.bi, binding.shader_slot, 0);

	वापस 0;
पूर्ण

/**
 * vmw_cmd_set_shader_स्थिर - Validate SVGA_3D_CMD_SET_SHADER_CONST command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_set_shader_स्थिर(काष्ठा vmw_निजी *dev_priv,
				    काष्ठा vmw_sw_context *sw_context,
				    SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdSetShaderConst);
	पूर्णांक ret;

	cmd = container_of(header, typeof(*cmd), header);

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
				VMW_RES_सूचीTY_SET, user_context_converter,
				&cmd->body.cid, शून्य);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (dev_priv->has_mob)
		header->id = SVGA_3D_CMD_SET_GB_SHADERCONSTS_INLINE;

	वापस 0;
पूर्ण

/**
 * vmw_cmd_bind_gb_shader - Validate SVGA_3D_CMD_BIND_GB_SHADER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_bind_gb_shader(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdBindGBShader) =
		container_of(header, typeof(*cmd), header);

	वापस vmw_cmd_चयन_backup(dev_priv, sw_context, vmw_res_shader,
				     user_shader_converter, &cmd->body.shid,
				     &cmd->body.mobid, cmd->body.offsetInBytes);
पूर्ण

/**
 * vmw_cmd_dx_set_single_स्थिरant_buffer - Validate
 * SVGA_3D_CMD_DX_SET_SINGLE_CONSTANT_BUFFER command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक
vmw_cmd_dx_set_single_स्थिरant_buffer(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा vmw_sw_context *sw_context,
				      SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXSetSingleConstantBuffer);
	SVGA3dShaderType max_shader_num = has_sm5_context(dev_priv) ?
		SVGA3D_NUM_SHADERTYPE : SVGA3D_NUM_SHADERTYPE_DX10;

	काष्ठा vmw_resource *res = शून्य;
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_ctx_bindinfo_cb binding;
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.sid, &res);
	अगर (unlikely(ret != 0))
		वापस ret;

	binding.bi.ctx = ctx_node->ctx;
	binding.bi.res = res;
	binding.bi.bt = vmw_ctx_binding_cb;
	binding.shader_slot = cmd->body.type - SVGA3D_SHADERTYPE_MIN;
	binding.offset = cmd->body.offsetInBytes;
	binding.size = cmd->body.sizeInBytes;
	binding.slot = cmd->body.slot;

	अगर (binding.shader_slot >= max_shader_num ||
	    binding.slot >= SVGA3D_DX_MAX_CONSTBUFFERS) अणु
		VMW_DEBUG_USER("Illegal const buffer shader %u slot %u.\n",
			       (अचिन्हित पूर्णांक) cmd->body.type,
			       (अचिन्हित पूर्णांक) binding.slot);
		वापस -EINVAL;
	पूर्ण

	vmw_binding_add(ctx_node->staged, &binding.bi, binding.shader_slot,
			binding.slot);

	वापस 0;
पूर्ण

/**
 * vmw_cmd_dx_set_shader_res - Validate SVGA_3D_CMD_DX_SET_SHADER_RESOURCES
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_set_shader_res(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXSetShaderResources) =
		container_of(header, typeof(*cmd), header);
	SVGA3dShaderType max_allowed = has_sm5_context(dev_priv) ?
		SVGA3D_SHADERTYPE_MAX : SVGA3D_SHADERTYPE_DX10_MAX;

	u32 num_sr_view = (cmd->header.size - माप(cmd->body)) /
		माप(SVGA3dShaderResourceViewId);

	अगर ((u64) cmd->body.startView + (u64) num_sr_view >
	    (u64) SVGA3D_DX_MAX_SRVIEWS ||
	    cmd->body.type >= max_allowed) अणु
		VMW_DEBUG_USER("Invalid shader binding.\n");
		वापस -EINVAL;
	पूर्ण

	वापस vmw_view_bindings_add(sw_context, vmw_view_sr,
				     vmw_ctx_binding_sr,
				     cmd->body.type - SVGA3D_SHADERTYPE_MIN,
				     (व्योम *) &cmd[1], num_sr_view,
				     cmd->body.startView);
पूर्ण

/**
 * vmw_cmd_dx_set_shader - Validate SVGA_3D_CMD_DX_SET_SHADER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_set_shader(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_sw_context *sw_context,
				 SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXSetShader);
	SVGA3dShaderType max_allowed = has_sm5_context(dev_priv) ?
		SVGA3D_SHADERTYPE_MAX : SVGA3D_SHADERTYPE_DX10_MAX;
	काष्ठा vmw_resource *res = शून्य;
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_ctx_bindinfo_shader binding;
	पूर्णांक ret = 0;

	अगर (!ctx_node)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);

	अगर (cmd->body.type >= max_allowed ||
	    cmd->body.type < SVGA3D_SHADERTYPE_MIN) अणु
		VMW_DEBUG_USER("Illegal shader type %u.\n",
			       (अचिन्हित पूर्णांक) cmd->body.type);
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->body.shaderId != SVGA3D_INVALID_ID) अणु
		res = vmw_shader_lookup(sw_context->man, cmd->body.shaderId, 0);
		अगर (IS_ERR(res)) अणु
			VMW_DEBUG_USER("Could not find shader for binding.\n");
			वापस PTR_ERR(res);
		पूर्ण

		ret = vmw_execbuf_res_noctx_val_add(sw_context, res,
						    VMW_RES_सूचीTY_NONE);
		अगर (ret)
			वापस ret;
	पूर्ण

	binding.bi.ctx = ctx_node->ctx;
	binding.bi.res = res;
	binding.bi.bt = vmw_ctx_binding_dx_shader;
	binding.shader_slot = cmd->body.type - SVGA3D_SHADERTYPE_MIN;

	vmw_binding_add(ctx_node->staged, &binding.bi, binding.shader_slot, 0);

	वापस 0;
पूर्ण

/**
 * vmw_cmd_dx_set_vertex_buffers - Validates SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_set_vertex_buffers(काष्ठा vmw_निजी *dev_priv,
					 काष्ठा vmw_sw_context *sw_context,
					 SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_ctx_bindinfo_vb binding;
	काष्ठा vmw_resource *res;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetVertexBuffers body;
		SVGA3dVertexBuffer buf[];
	पूर्ण *cmd;
	पूर्णांक i, ret, num;

	अगर (!ctx_node)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);
	num = (cmd->header.size - माप(cmd->body)) /
		माप(SVGA3dVertexBuffer);
	अगर ((u64)num + (u64)cmd->body.startBuffer >
	    (u64)SVGA3D_DX_MAX_VERTEXBUFFERS) अणु
		VMW_DEBUG_USER("Invalid number of vertex buffers.\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
					VMW_RES_सूचीTY_NONE,
					user_surface_converter,
					&cmd->buf[i].sid, &res);
		अगर (unlikely(ret != 0))
			वापस ret;

		binding.bi.ctx = ctx_node->ctx;
		binding.bi.bt = vmw_ctx_binding_vb;
		binding.bi.res = res;
		binding.offset = cmd->buf[i].offset;
		binding.stride = cmd->buf[i].stride;
		binding.slot = i + cmd->body.startBuffer;

		vmw_binding_add(ctx_node->staged, &binding.bi, 0, binding.slot);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_cmd_dx_ia_set_vertex_buffers - Validate
 * SVGA_3D_CMD_DX_IA_SET_INDEX_BUFFER command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_set_index_buffer(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_sw_context *sw_context,
				       SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_ctx_bindinfo_ib binding;
	काष्ठा vmw_resource *res;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXSetIndexBuffer);
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.sid, &res);
	अगर (unlikely(ret != 0))
		वापस ret;

	binding.bi.ctx = ctx_node->ctx;
	binding.bi.res = res;
	binding.bi.bt = vmw_ctx_binding_ib;
	binding.offset = cmd->body.offset;
	binding.क्रमmat = cmd->body.क्रमmat;

	vmw_binding_add(ctx_node->staged, &binding.bi, 0, 0);

	वापस 0;
पूर्ण

/**
 * vmw_cmd_dx_set_rendertarget - Validate SVGA_3D_CMD_DX_SET_RENDERTARGETS
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_set_rendertarमाला_लो(काष्ठा vmw_निजी *dev_priv,
					काष्ठा vmw_sw_context *sw_context,
					SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXSetRenderTarमाला_लो) =
		container_of(header, typeof(*cmd), header);
	u32 num_rt_view = (cmd->header.size - माप(cmd->body)) /
		माप(SVGA3dRenderTargetViewId);
	पूर्णांक ret;

	अगर (num_rt_view > SVGA3D_MAX_SIMULTANEOUS_RENDER_TARGETS) अणु
		VMW_DEBUG_USER("Invalid DX Rendertarget binding.\n");
		वापस -EINVAL;
	पूर्ण

	ret = vmw_view_bindings_add(sw_context, vmw_view_ds, vmw_ctx_binding_ds,
				    0, &cmd->body.depthStencilViewId, 1, 0);
	अगर (ret)
		वापस ret;

	वापस vmw_view_bindings_add(sw_context, vmw_view_rt,
				     vmw_ctx_binding_dx_rt, 0, (व्योम *)&cmd[1],
				     num_rt_view, 0);
पूर्ण

/**
 * vmw_cmd_dx_clear_rendertarget_view - Validate
 * SVGA_3D_CMD_DX_CLEAR_RENDERTARGET_VIEW command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_clear_rendertarget_view(काष्ठा vmw_निजी *dev_priv,
					      काष्ठा vmw_sw_context *sw_context,
					      SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXClearRenderTargetView) =
		container_of(header, typeof(*cmd), header);
	काष्ठा vmw_resource *ret;

	ret = vmw_view_id_val_add(sw_context, vmw_view_rt,
				  cmd->body.renderTargetViewId);

	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

/**
 * vmw_cmd_dx_clear_rendertarget_view - Validate
 * SVGA_3D_CMD_DX_CLEAR_DEPTHSTENCIL_VIEW command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_clear_depthstencil_view(काष्ठा vmw_निजी *dev_priv,
					      काष्ठा vmw_sw_context *sw_context,
					      SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXClearDepthStencilView) =
		container_of(header, typeof(*cmd), header);
	काष्ठा vmw_resource *ret;

	ret = vmw_view_id_val_add(sw_context, vmw_view_ds,
				  cmd->body.depthStencilViewId);

	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

अटल पूर्णांक vmw_cmd_dx_view_define(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_resource *srf;
	काष्ठा vmw_resource *res;
	क्रमागत vmw_view_type view_type;
	पूर्णांक ret;
	/*
	 * This is based on the fact that all affected define commands have the
	 * same initial command body layout.
	 */
	काष्ठा अणु
		SVGA3dCmdHeader header;
		uपूर्णांक32 defined_id;
		uपूर्णांक32 sid;
	पूर्ण *cmd;

	अगर (!ctx_node)
		वापस -EINVAL;

	view_type = vmw_view_cmd_to_type(header->id);
	अगर (view_type == vmw_view_max)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);
	अगर (unlikely(cmd->sid == SVGA3D_INVALID_ID)) अणु
		VMW_DEBUG_USER("Invalid surface id.\n");
		वापस -EINVAL;
	पूर्ण
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->sid, &srf);
	अगर (unlikely(ret != 0))
		वापस ret;

	res = vmw_context_cotable(ctx_node->ctx, vmw_view_cotables[view_type]);
	ret = vmw_cotable_notअगरy(res, cmd->defined_id);
	अगर (unlikely(ret != 0))
		वापस ret;

	वापस vmw_view_add(sw_context->man, ctx_node->ctx, srf, view_type,
			    cmd->defined_id, header,
			    header->size + माप(*header),
			    &sw_context->staged_cmd_res);
पूर्ण

/**
 * vmw_cmd_dx_set_so_tarमाला_लो - Validate SVGA_3D_CMD_DX_SET_SOTARGETS command.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_set_so_tarमाला_लो(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_ctx_bindinfo_so_target binding;
	काष्ठा vmw_resource *res;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetSOTarमाला_लो body;
		SVGA3dSoTarget tarमाला_लो[];
	पूर्ण *cmd;
	पूर्णांक i, ret, num;

	अगर (!ctx_node)
		वापस -EINVAL;

	cmd = container_of(header, typeof(*cmd), header);
	num = (cmd->header.size - माप(cmd->body)) / माप(SVGA3dSoTarget);

	अगर (num > SVGA3D_DX_MAX_SOTARGETS) अणु
		VMW_DEBUG_USER("Invalid DX SO binding.\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
					VMW_RES_सूचीTY_SET,
					user_surface_converter,
					&cmd->tarमाला_लो[i].sid, &res);
		अगर (unlikely(ret != 0))
			वापस ret;

		binding.bi.ctx = ctx_node->ctx;
		binding.bi.res = res;
		binding.bi.bt = vmw_ctx_binding_so_target,
		binding.offset = cmd->tarमाला_लो[i].offset;
		binding.size = cmd->tarमाला_लो[i].sizeInBytes;
		binding.slot = i;

		vmw_binding_add(ctx_node->staged, &binding.bi, 0, binding.slot);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_dx_so_define(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_sw_context *sw_context,
				SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_resource *res;
	/*
	 * This is based on the fact that all affected define commands have
	 * the same initial command body layout.
	 */
	काष्ठा अणु
		SVGA3dCmdHeader header;
		uपूर्णांक32 defined_id;
	पूर्ण *cmd;
	क्रमागत vmw_so_type so_type;
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	so_type = vmw_so_cmd_to_type(header->id);
	res = vmw_context_cotable(ctx_node->ctx, vmw_so_cotables[so_type]);
	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cotable_notअगरy(res, cmd->defined_id);

	वापस ret;
पूर्ण

/**
 * vmw_cmd_dx_check_subresource - Validate SVGA_3D_CMD_DX_[X]_SUBRESOURCE
 * command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_check_subresource(काष्ठा vmw_निजी *dev_priv,
					काष्ठा vmw_sw_context *sw_context,
					SVGA3dCmdHeader *header)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		जोड़ अणु
			SVGA3dCmdDXReadbackSubResource r_body;
			SVGA3dCmdDXInvalidateSubResource i_body;
			SVGA3dCmdDXUpdateSubResource u_body;
			SVGA3dSurfaceId sid;
		पूर्ण;
	पूर्ण *cmd;

	BUILD_BUG_ON(दुरत्व(typeof(*cmd), r_body.sid) !=
		     दुरत्व(typeof(*cmd), sid));
	BUILD_BUG_ON(दुरत्व(typeof(*cmd), i_body.sid) !=
		     दुरत्व(typeof(*cmd), sid));
	BUILD_BUG_ON(दुरत्व(typeof(*cmd), u_body.sid) !=
		     दुरत्व(typeof(*cmd), sid));

	cmd = container_of(header, typeof(*cmd), header);
	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->sid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_dx_cid_check(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_sw_context *sw_context,
				SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);

	अगर (!ctx_node)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * vmw_cmd_dx_view_हटाओ - validate a view हटाओ command and schedule the view
 * resource क्रम removal.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 *
 * Check that the view exists, and अगर it was not created using this command
 * batch, conditionally make this command a NOP.
 */
अटल पूर्णांक vmw_cmd_dx_view_हटाओ(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा अणु
		SVGA3dCmdHeader header;
		जोड़ vmw_view_destroy body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	क्रमागत vmw_view_type view_type = vmw_view_cmd_to_type(header->id);
	काष्ठा vmw_resource *view;
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	ret = vmw_view_हटाओ(sw_context->man, cmd->body.view_id, view_type,
			      &sw_context->staged_cmd_res, &view);
	अगर (ret || !view)
		वापस ret;

	/*
	 * If the view wasn't created during this command batch, it might
	 * have been हटाओd due to a context swapout, so add a
	 * relocation to conditionally make this command a NOP to aव्योम
	 * device errors.
	 */
	वापस vmw_resource_relocation_add(sw_context, view,
					   vmw_ptr_dअगरf(sw_context->buf_start,
							&cmd->header.id),
					   vmw_res_rel_cond_nop);
पूर्ण

/**
 * vmw_cmd_dx_define_shader - Validate SVGA_3D_CMD_DX_DEFINE_SHADER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_define_shader(काष्ठा vmw_निजी *dev_priv,
				    काष्ठा vmw_sw_context *sw_context,
				    SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	काष्ठा vmw_resource *res;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXDefineShader) =
		container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	res = vmw_context_cotable(ctx_node->ctx, SVGA_COTABLE_DXSHADER);
	ret = vmw_cotable_notअगरy(res, cmd->body.shaderId);
	अगर (ret)
		वापस ret;

	वापस vmw_dx_shader_add(sw_context->man, ctx_node->ctx,
				 cmd->body.shaderId, cmd->body.type,
				 &sw_context->staged_cmd_res);
पूर्ण

/**
 * vmw_cmd_dx_destroy_shader - Validate SVGA_3D_CMD_DX_DESTROY_SHADER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_destroy_shader(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = VMW_GET_CTX_NODE(sw_context);
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXDestroyShader) =
		container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	अगर (!ctx_node)
		वापस -EINVAL;

	ret = vmw_shader_हटाओ(sw_context->man, cmd->body.shaderId, 0,
				&sw_context->staged_cmd_res);

	वापस ret;
पूर्ण

/**
 * vmw_cmd_dx_bind_shader - Validate SVGA_3D_CMD_DX_BIND_SHADER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_bind_shader(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_resource *res;
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXBindShader) =
		container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	अगर (cmd->body.cid != SVGA3D_INVALID_ID) अणु
		ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_context,
					VMW_RES_सूचीTY_SET,
					user_context_converter, &cmd->body.cid,
					&ctx);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		काष्ठा vmw_ctx_validation_info *ctx_node =
			VMW_GET_CTX_NODE(sw_context);

		अगर (!ctx_node)
			वापस -EINVAL;

		ctx = ctx_node->ctx;
	पूर्ण

	res = vmw_shader_lookup(vmw_context_res_man(ctx), cmd->body.shid, 0);
	अगर (IS_ERR(res)) अणु
		VMW_DEBUG_USER("Could not find shader to bind.\n");
		वापस PTR_ERR(res);
	पूर्ण

	ret = vmw_execbuf_res_noctx_val_add(sw_context, res,
					    VMW_RES_सूचीTY_NONE);
	अगर (ret) अणु
		VMW_DEBUG_USER("Error creating resource validation node.\n");
		वापस ret;
	पूर्ण

	वापस vmw_cmd_res_चयन_backup(dev_priv, sw_context, res,
					 &cmd->body.mobid,
					 cmd->body.offsetInBytes);
पूर्ण

/**
 * vmw_cmd_dx_genmips - Validate SVGA_3D_CMD_DX_GENMIPS command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_genmips(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_sw_context *sw_context,
			      SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXGenMips) =
		container_of(header, typeof(*cmd), header);
	काष्ठा vmw_resource *ret;

	ret = vmw_view_id_val_add(sw_context, vmw_view_sr,
				  cmd->body.shaderResourceViewId);

	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

/**
 * vmw_cmd_dx_transfer_from_buffer - Validate
 * SVGA_3D_CMD_DX_TRANSFER_FROM_BUFFER command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_dx_transfer_from_buffer(काष्ठा vmw_निजी *dev_priv,
					   काष्ठा vmw_sw_context *sw_context,
					   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdDXTransferFromBuffer) =
		container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				VMW_RES_सूचीTY_NONE, user_surface_converter,
				&cmd->body.srcSid, शून्य);
	अगर (ret != 0)
		वापस ret;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_SET, user_surface_converter,
				 &cmd->body.destSid, शून्य);
पूर्ण

/**
 * vmw_cmd_पूर्णांकra_surface_copy - Validate SVGA_3D_CMD_INTRA_SURFACE_COPY command
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 * @sw_context: The software context being used क्रम this batch.
 * @header: Poपूर्णांकer to the command header in the command stream.
 */
अटल पूर्णांक vmw_cmd_पूर्णांकra_surface_copy(काष्ठा vmw_निजी *dev_priv,
					   काष्ठा vmw_sw_context *sw_context,
					   SVGA3dCmdHeader *header)
अणु
	VMW_DECLARE_CMD_VAR(*cmd, SVGA3dCmdIntraSurfaceCopy) =
		container_of(header, typeof(*cmd), header);

	अगर (!(dev_priv->capabilities2 & SVGA_CAP2_INTRA_SURFACE_COPY))
		वापस -EINVAL;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_SET, user_surface_converter,
				 &cmd->body.surface.sid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_sm5(काष्ठा vmw_निजी *dev_priv,
		       काष्ठा vmw_sw_context *sw_context,
		       SVGA3dCmdHeader *header)
अणु
	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cmd_sm5_view_define(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	वापस vmw_cmd_dx_view_define(dev_priv, sw_context, header);
पूर्ण

अटल पूर्णांक vmw_cmd_sm5_view_हटाओ(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	वापस vmw_cmd_dx_view_हटाओ(dev_priv, sw_context, header);
पूर्ण

अटल पूर्णांक vmw_cmd_clear_uav_uपूर्णांक(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_sw_context *sw_context,
				  SVGA3dCmdHeader *header)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXClearUAViewUपूर्णांक body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	काष्ठा vmw_resource *ret;

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	ret = vmw_view_id_val_add(sw_context, vmw_view_ua,
				  cmd->body.uaViewId);

	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

अटल पूर्णांक vmw_cmd_clear_uav_भग्न(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   SVGA3dCmdHeader *header)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXClearUAViewFloat body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	काष्ठा vmw_resource *ret;

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	ret = vmw_view_id_val_add(sw_context, vmw_view_ua,
				  cmd->body.uaViewId);

	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

अटल पूर्णांक vmw_cmd_set_uav(काष्ठा vmw_निजी *dev_priv,
			   काष्ठा vmw_sw_context *sw_context,
			   SVGA3dCmdHeader *header)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetUAViews body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	u32 num_uav = (cmd->header.size - माप(cmd->body)) /
		माप(SVGA3dUAViewId);
	पूर्णांक ret;

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	अगर (num_uav > SVGA3D_MAX_UAVIEWS) अणु
		VMW_DEBUG_USER("Invalid UAV binding.\n");
		वापस -EINVAL;
	पूर्ण

	ret = vmw_view_bindings_add(sw_context, vmw_view_ua,
				    vmw_ctx_binding_uav, 0, (व्योम *)&cmd[1],
				    num_uav, 0);
	अगर (ret)
		वापस ret;

	vmw_binding_add_uav_index(sw_context->dx_ctx_node->staged, 0,
					 cmd->body.uavSpliceIndex);

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_cmd_set_cs_uav(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_sw_context *sw_context,
			      SVGA3dCmdHeader *header)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetCSUAViews body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	u32 num_uav = (cmd->header.size - माप(cmd->body)) /
		माप(SVGA3dUAViewId);
	पूर्णांक ret;

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	अगर (num_uav > SVGA3D_MAX_UAVIEWS) अणु
		VMW_DEBUG_USER("Invalid UAV binding.\n");
		वापस -EINVAL;
	पूर्ण

	ret = vmw_view_bindings_add(sw_context, vmw_view_ua,
				    vmw_ctx_binding_cs_uav, 0, (व्योम *)&cmd[1],
				    num_uav, 0);
	अगर (ret)
		वापस ret;

	vmw_binding_add_uav_index(sw_context->dx_ctx_node->staged, 1,
				  cmd->body.startIndex);

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_cmd_dx_define_streamoutput(काष्ठा vmw_निजी *dev_priv,
					  काष्ठा vmw_sw_context *sw_context,
					  SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = sw_context->dx_ctx_node;
	काष्ठा vmw_resource *res;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDefineStreamOutputWithMob body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	अगर (!ctx_node) अणु
		DRM_ERROR("DX Context not set.\n");
		वापस -EINVAL;
	पूर्ण

	res = vmw_context_cotable(ctx_node->ctx, SVGA_COTABLE_STREAMOUTPUT);
	ret = vmw_cotable_notअगरy(res, cmd->body.soid);
	अगर (ret)
		वापस ret;

	वापस vmw_dx_streamoutput_add(sw_context->man, ctx_node->ctx,
				       cmd->body.soid,
				       &sw_context->staged_cmd_res);
पूर्ण

अटल पूर्णांक vmw_cmd_dx_destroy_streamoutput(काष्ठा vmw_निजी *dev_priv,
					   काष्ठा vmw_sw_context *sw_context,
					   SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = sw_context->dx_ctx_node;
	काष्ठा vmw_resource *res;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDestroyStreamOutput body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);

	अगर (!ctx_node) अणु
		DRM_ERROR("DX Context not set.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * When device करोes not support SM5 then streamoutput with mob command is
	 * not available to user-space. Simply वापस in this हाल.
	 */
	अगर (!has_sm5_context(dev_priv))
		वापस 0;

	/*
	 * With SM5 capable device अगर lookup fails then user-space probably used
	 * old streamoutput define command. Return without an error.
	 */
	res = vmw_dx_streamoutput_lookup(vmw_context_res_man(ctx_node->ctx),
					 cmd->body.soid);
	अगर (IS_ERR(res))
		वापस 0;

	वापस vmw_dx_streamoutput_हटाओ(sw_context->man, cmd->body.soid,
					  &sw_context->staged_cmd_res);
पूर्ण

अटल पूर्णांक vmw_cmd_dx_bind_streamoutput(काष्ठा vmw_निजी *dev_priv,
					काष्ठा vmw_sw_context *sw_context,
					SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = sw_context->dx_ctx_node;
	काष्ठा vmw_resource *res;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXBindStreamOutput body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	अगर (!ctx_node) अणु
		DRM_ERROR("DX Context not set.\n");
		वापस -EINVAL;
	पूर्ण

	res = vmw_dx_streamoutput_lookup(vmw_context_res_man(ctx_node->ctx),
					 cmd->body.soid);
	अगर (IS_ERR(res)) अणु
		DRM_ERROR("Could not find streamoutput to bind.\n");
		वापस PTR_ERR(res);
	पूर्ण

	vmw_dx_streamoutput_set_size(res, cmd->body.sizeInBytes);

	ret = vmw_execbuf_res_noctx_val_add(sw_context, res,
					    VMW_RES_सूचीTY_NONE);
	अगर (ret) अणु
		DRM_ERROR("Error creating resource validation node.\n");
		वापस ret;
	पूर्ण

	वापस vmw_cmd_res_चयन_backup(dev_priv, sw_context, res,
					 &cmd->body.mobid,
					 cmd->body.offsetInBytes);
पूर्ण

अटल पूर्णांक vmw_cmd_dx_set_streamoutput(काष्ठा vmw_निजी *dev_priv,
				       काष्ठा vmw_sw_context *sw_context,
				       SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_ctx_validation_info *ctx_node = sw_context->dx_ctx_node;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_ctx_bindinfo_so binding;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetStreamOutput body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);
	पूर्णांक ret;

	अगर (!ctx_node) अणु
		DRM_ERROR("DX Context not set.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->body.soid == SVGA3D_INVALID_ID)
		वापस 0;

	/*
	 * When device करोes not support SM5 then streamoutput with mob command is
	 * not available to user-space. Simply वापस in this हाल.
	 */
	अगर (!has_sm5_context(dev_priv))
		वापस 0;

	/*
	 * With SM5 capable device अगर lookup fails then user-space probably used
	 * old streamoutput define command. Return without an error.
	 */
	res = vmw_dx_streamoutput_lookup(vmw_context_res_man(ctx_node->ctx),
					 cmd->body.soid);
	अगर (IS_ERR(res)) अणु
		वापस 0;
	पूर्ण

	ret = vmw_execbuf_res_noctx_val_add(sw_context, res,
					    VMW_RES_सूचीTY_NONE);
	अगर (ret) अणु
		DRM_ERROR("Error creating resource validation node.\n");
		वापस ret;
	पूर्ण

	binding.bi.ctx = ctx_node->ctx;
	binding.bi.res = res;
	binding.bi.bt = vmw_ctx_binding_so;
	binding.slot = 0; /* Only one SO set to context at a समय. */

	vmw_binding_add(sw_context->dx_ctx_node->staged, &binding.bi, 0,
			binding.slot);

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_cmd_indexed_instanced_indirect(काष्ठा vmw_निजी *dev_priv,
					      काष्ठा vmw_sw_context *sw_context,
					      SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_draw_indexed_instanced_indirect_cmd अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDrawIndexedInstancedIndirect body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.argsBufferSid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_instanced_indirect(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा vmw_sw_context *sw_context,
				      SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_draw_instanced_indirect_cmd अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDrawInstancedIndirect body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.argsBufferSid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_dispatch_indirect(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_sw_context *sw_context,
				     SVGA3dCmdHeader *header)
अणु
	काष्ठा vmw_dispatch_indirect_cmd अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXDispatchIndirect body;
	पूर्ण *cmd = container_of(header, typeof(*cmd), header);

	अगर (!has_sm5_context(dev_priv))
		वापस -EINVAL;

	वापस vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				 VMW_RES_सूचीTY_NONE, user_surface_converter,
				 &cmd->body.argsBufferSid, शून्य);
पूर्ण

अटल पूर्णांक vmw_cmd_check_not_3d(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_sw_context *sw_context,
				व्योम *buf, uपूर्णांक32_t *size)
अणु
	uपूर्णांक32_t size_reमुख्यing = *size;
	uपूर्णांक32_t cmd_id;

	cmd_id = ((uपूर्णांक32_t *)buf)[0];
	चयन (cmd_id) अणु
	हाल SVGA_CMD_UPDATE:
		*size = माप(uपूर्णांक32_t) + माप(SVGAFअगरoCmdUpdate);
		अवरोध;
	हाल SVGA_CMD_DEFINE_GMRFB:
		*size = माप(uपूर्णांक32_t) + माप(SVGAFअगरoCmdDefineGMRFB);
		अवरोध;
	हाल SVGA_CMD_BLIT_GMRFB_TO_SCREEN:
		*size = माप(uपूर्णांक32_t) + माप(SVGAFअगरoCmdBlitGMRFBToScreen);
		अवरोध;
	हाल SVGA_CMD_BLIT_SCREEN_TO_GMRFB:
		*size = माप(uपूर्णांक32_t) + माप(SVGAFअगरoCmdBlitGMRFBToScreen);
		अवरोध;
	शेष:
		VMW_DEBUG_USER("Unsupported SVGA command: %u.\n", cmd_id);
		वापस -EINVAL;
	पूर्ण

	अगर (*size > size_reमुख्यing) अणु
		VMW_DEBUG_USER("Invalid SVGA command (size mismatch): %u.\n",
			       cmd_id);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(!sw_context->kernel)) अणु
		VMW_DEBUG_USER("Kernel only SVGA command: %u.\n", cmd_id);
		वापस -EPERM;
	पूर्ण

	अगर (cmd_id == SVGA_CMD_DEFINE_GMRFB)
		वापस vmw_cmd_check_define_gmrfb(dev_priv, sw_context, buf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vmw_cmd_entry vmw_cmd_entries[SVGA_3D_CMD_MAX] = अणु
	VMW_CMD_DEF(SVGA_3D_CMD_SURFACE_DEFINE, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SURFACE_DESTROY, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SURFACE_COPY, &vmw_cmd_surface_copy_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SURFACE_STRETCHBLT, &vmw_cmd_stretch_blt_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SURFACE_DMA, &vmw_cmd_dma,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_CONTEXT_DEFINE, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_CONTEXT_DESTROY, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETTRANSFORM, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETZRANGE, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETRENDERSTATE, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETRENDERTARGET,
		    &vmw_cmd_set_render_target_check, true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETTEXTURESTATE, &vmw_cmd_tex_state,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETMATERIAL, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETLIGHTDATA, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETLIGHTENABLED, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETVIEWPORT, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETCLIPPLANE, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_CLEAR, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_PRESENT, &vmw_cmd_present_check,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SHADER_DEFINE, &vmw_cmd_shader_define,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SHADER_DESTROY, &vmw_cmd_shader_destroy,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SET_SHADER, &vmw_cmd_set_shader,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SET_SHADER_CONST, &vmw_cmd_set_shader_स्थिर,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DRAW_PRIMITIVES, &vmw_cmd_draw,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SETSCISSORRECT, &vmw_cmd_cid_check,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_BEGIN_QUERY, &vmw_cmd_begin_query,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_END_QUERY, &vmw_cmd_end_query,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_WAIT_FOR_QUERY, &vmw_cmd_रुको_query,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_PRESENT_READBACK, &vmw_cmd_ok,
		    true, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN,
		    &vmw_cmd_blt_surf_screen_check, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SURFACE_DEFINE_V2, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_GENERATE_MIPMAPS, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_ACTIVATE_SURFACE, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEACTIVATE_SURFACE, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SCREEN_DMA, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD1, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD2, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD12, &vmw_cmd_invalid, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD13, &vmw_cmd_invalid, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD14, &vmw_cmd_invalid, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD15, &vmw_cmd_invalid, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD16, &vmw_cmd_invalid, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_DEAD17, &vmw_cmd_invalid, false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_SET_OTABLE_BASE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_READBACK_OTABLE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DEFINE_GB_MOB, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DESTROY_GB_MOB, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_REDEFINE_GB_MOB64, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_UPDATE_GB_MOB_MAPPING, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DEFINE_GB_SURFACE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DESTROY_GB_SURFACE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_BIND_GB_SURFACE, &vmw_cmd_bind_gb_surface,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_COND_BIND_GB_SURFACE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_UPDATE_GB_IMAGE, &vmw_cmd_update_gb_image,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_UPDATE_GB_SURFACE,
		    &vmw_cmd_update_gb_surface, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_READBACK_GB_IMAGE,
		    &vmw_cmd_पढ़ोback_gb_image, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_READBACK_GB_SURFACE,
		    &vmw_cmd_पढ़ोback_gb_surface, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_INVALIDATE_GB_IMAGE,
		    &vmw_cmd_invalidate_gb_image, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_INVALIDATE_GB_SURFACE,
		    &vmw_cmd_invalidate_gb_surface, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DEFINE_GB_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DESTROY_GB_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_BIND_GB_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_READBACK_GB_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_INVALIDATE_GB_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DEFINE_GB_SHADER, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_BIND_GB_SHADER, &vmw_cmd_bind_gb_shader,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DESTROY_GB_SHADER, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_SET_OTABLE_BASE64, &vmw_cmd_invalid,
		    false, false, false),
	VMW_CMD_DEF(SVGA_3D_CMD_BEGIN_GB_QUERY, &vmw_cmd_begin_gb_query,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_END_GB_QUERY, &vmw_cmd_end_gb_query,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_WAIT_FOR_GB_QUERY, &vmw_cmd_रुको_gb_query,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_NOP, &vmw_cmd_ok,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_NOP_ERROR, &vmw_cmd_ok,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_ENABLE_GART, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DISABLE_GART, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_MAP_MOB_INTO_GART, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_UNMAP_GART_RANGE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DEFINE_GB_SCREENTARGET, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DESTROY_GB_SCREENTARGET, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_BIND_GB_SCREENTARGET, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_UPDATE_GB_SCREENTARGET, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_READBACK_GB_IMAGE_PARTIAL, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_INVALIDATE_GB_IMAGE_PARTIAL, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_SET_GB_SHADERCONSTS_INLINE, &vmw_cmd_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_GB_SCREEN_DMA, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_BIND_GB_SURFACE_WITH_PITCH, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_GB_MOB_FENCE, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DEFINE_GB_SURFACE_V2, &vmw_cmd_invalid,
		    false, false, true),

	/* SM commands */
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_BIND_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_READBACK_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_INVALIDATE_CONTEXT, &vmw_cmd_invalid,
		    false, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_SINGLE_CONSTANT_BUFFER,
		    &vmw_cmd_dx_set_single_स्थिरant_buffer, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_SHADER_RESOURCES,
		    &vmw_cmd_dx_set_shader_res, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_SHADER, &vmw_cmd_dx_set_shader,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_SAMPLERS, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW_INDEXED, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW_INSTANCED, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW_AUTO, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS,
		    &vmw_cmd_dx_set_vertex_buffers, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_INDEX_BUFFER,
		    &vmw_cmd_dx_set_index_buffer, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_RENDERTARGETS,
		    &vmw_cmd_dx_set_rendertarमाला_लो, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_BLEND_STATE, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_DEPTHSTENCIL_STATE,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_RASTERIZER_STATE,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_QUERY, &vmw_cmd_dx_define_query,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_QUERY, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_BIND_QUERY, &vmw_cmd_dx_bind_query,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_QUERY_OFFSET,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_BEGIN_QUERY, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_END_QUERY, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_READBACK_QUERY, &vmw_cmd_invalid,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_PREDICATION, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_VIEWPORTS, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_SCISSORRECTS, &vmw_cmd_dx_cid_check,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_CLEAR_RENDERTARGET_VIEW,
		    &vmw_cmd_dx_clear_rendertarget_view, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_CLEAR_DEPTHSTENCIL_VIEW,
		    &vmw_cmd_dx_clear_depthstencil_view, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_PRED_COPY, &vmw_cmd_invalid,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_GENMIPS, &vmw_cmd_dx_genmips,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_UPDATE_SUBRESOURCE,
		    &vmw_cmd_dx_check_subresource, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_READBACK_SUBRESOURCE,
		    &vmw_cmd_dx_check_subresource, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_INVALIDATE_SUBRESOURCE,
		    &vmw_cmd_dx_check_subresource, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW,
		    &vmw_cmd_dx_view_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW,
		    &vmw_cmd_dx_view_हटाओ, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_RENDERTARGET_VIEW,
		    &vmw_cmd_dx_view_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW,
		    &vmw_cmd_dx_view_हटाओ, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW,
		    &vmw_cmd_dx_view_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW,
		    &vmw_cmd_dx_view_हटाओ, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT,
		    &vmw_cmd_dx_so_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_BLEND_STATE,
		    &vmw_cmd_dx_so_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_BLEND_STATE,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE,
		    &vmw_cmd_dx_so_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE,
		    &vmw_cmd_dx_so_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE,
		    &vmw_cmd_dx_so_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_SHADER,
		    &vmw_cmd_dx_define_shader, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_SHADER,
		    &vmw_cmd_dx_destroy_shader, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_BIND_SHADER,
		    &vmw_cmd_dx_bind_shader, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT,
		    &vmw_cmd_dx_so_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT,
		    &vmw_cmd_dx_destroy_streamoutput, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_STREAMOUTPUT,
		    &vmw_cmd_dx_set_streamoutput, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_SOTARGETS,
		    &vmw_cmd_dx_set_so_tarमाला_लो, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_INPUT_LAYOUT,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_TOPOLOGY,
		    &vmw_cmd_dx_cid_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_BUFFER_COPY,
		    &vmw_cmd_buffer_copy_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_PRED_COPY_REGION,
		    &vmw_cmd_pred_copy_check, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_TRANSFER_FROM_BUFFER,
		    &vmw_cmd_dx_transfer_from_buffer,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_INTRA_SURFACE_COPY, &vmw_cmd_पूर्णांकra_surface_copy,
		    true, false, true),

	/*
	 * SM5 commands
	 */
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_UA_VIEW, &vmw_cmd_sm5_view_define,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DESTROY_UA_VIEW, &vmw_cmd_sm5_view_हटाओ,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_CLEAR_UA_VIEW_UINT, &vmw_cmd_clear_uav_uपूर्णांक,
		    true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_CLEAR_UA_VIEW_FLOAT,
		    &vmw_cmd_clear_uav_भग्न, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_COPY_STRUCTURE_COUNT, &vmw_cmd_invalid, true,
		    false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_UA_VIEWS, &vmw_cmd_set_uav, true, false,
		    true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED_INसूचीECT,
		    &vmw_cmd_indexed_instanced_indirect, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DRAW_INSTANCED_INसूचीECT,
		    &vmw_cmd_instanced_indirect, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DISPATCH, &vmw_cmd_sm5, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DISPATCH_INसूचीECT,
		    &vmw_cmd_dispatch_indirect, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_SET_CS_UA_VIEWS, &vmw_cmd_set_cs_uav, true,
		    false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW_V2,
		    &vmw_cmd_sm5_view_define, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT_WITH_MOB,
		    &vmw_cmd_dx_define_streamoutput, true, false, true),
	VMW_CMD_DEF(SVGA_3D_CMD_DX_BIND_STREAMOUTPUT,
		    &vmw_cmd_dx_bind_streamoutput, true, false, true),
पूर्ण;

bool vmw_cmd_describe(स्थिर व्योम *buf, u32 *size, अक्षर स्थिर **cmd)
अणु
	u32 cmd_id = ((u32 *) buf)[0];

	अगर (cmd_id >= SVGA_CMD_MAX) अणु
		SVGA3dCmdHeader *header = (SVGA3dCmdHeader *) buf;
		स्थिर काष्ठा vmw_cmd_entry *entry;

		*size = header->size + माप(SVGA3dCmdHeader);
		cmd_id = header->id;
		अगर (cmd_id >= SVGA_3D_CMD_MAX)
			वापस false;

		cmd_id -= SVGA_3D_CMD_BASE;
		entry = &vmw_cmd_entries[cmd_id];
		*cmd = entry->cmd_name;
		वापस true;
	पूर्ण

	चयन (cmd_id) अणु
	हाल SVGA_CMD_UPDATE:
		*cmd = "SVGA_CMD_UPDATE";
		*size = माप(u32) + माप(SVGAFअगरoCmdUpdate);
		अवरोध;
	हाल SVGA_CMD_DEFINE_GMRFB:
		*cmd = "SVGA_CMD_DEFINE_GMRFB";
		*size = माप(u32) + माप(SVGAFअगरoCmdDefineGMRFB);
		अवरोध;
	हाल SVGA_CMD_BLIT_GMRFB_TO_SCREEN:
		*cmd = "SVGA_CMD_BLIT_GMRFB_TO_SCREEN";
		*size = माप(u32) + माप(SVGAFअगरoCmdBlitGMRFBToScreen);
		अवरोध;
	हाल SVGA_CMD_BLIT_SCREEN_TO_GMRFB:
		*cmd = "SVGA_CMD_BLIT_SCREEN_TO_GMRFB";
		*size = माप(u32) + माप(SVGAFअगरoCmdBlitGMRFBToScreen);
		अवरोध;
	शेष:
		*cmd = "UNKNOWN";
		*size = 0;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक vmw_cmd_check(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा vmw_sw_context *sw_context, व्योम *buf,
			 uपूर्णांक32_t *size)
अणु
	uपूर्णांक32_t cmd_id;
	uपूर्णांक32_t size_reमुख्यing = *size;
	SVGA3dCmdHeader *header = (SVGA3dCmdHeader *) buf;
	पूर्णांक ret;
	स्थिर काष्ठा vmw_cmd_entry *entry;
	bool gb = dev_priv->capabilities & SVGA_CAP_GBOBJECTS;

	cmd_id = ((uपूर्णांक32_t *)buf)[0];
	/* Handle any none 3D commands */
	अगर (unlikely(cmd_id < SVGA_CMD_MAX))
		वापस vmw_cmd_check_not_3d(dev_priv, sw_context, buf, size);


	cmd_id = header->id;
	*size = header->size + माप(SVGA3dCmdHeader);

	cmd_id -= SVGA_3D_CMD_BASE;
	अगर (unlikely(*size > size_reमुख्यing))
		जाओ out_invalid;

	अगर (unlikely(cmd_id >= SVGA_3D_CMD_MAX - SVGA_3D_CMD_BASE))
		जाओ out_invalid;

	entry = &vmw_cmd_entries[cmd_id];
	अगर (unlikely(!entry->func))
		जाओ out_invalid;

	अगर (unlikely(!entry->user_allow && !sw_context->kernel))
		जाओ out_privileged;

	अगर (unlikely(entry->gb_disable && gb))
		जाओ out_old;

	अगर (unlikely(entry->gb_enable && !gb))
		जाओ out_new;

	ret = entry->func(dev_priv, sw_context, header);
	अगर (unlikely(ret != 0)) अणु
		VMW_DEBUG_USER("SVGA3D command: %d failed with error %d\n",
			       cmd_id + SVGA_3D_CMD_BASE, ret);
		वापस ret;
	पूर्ण

	वापस 0;
out_invalid:
	VMW_DEBUG_USER("Invalid SVGA3D command: %d\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	वापस -EINVAL;
out_privileged:
	VMW_DEBUG_USER("Privileged SVGA3D command: %d\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	वापस -EPERM;
out_old:
	VMW_DEBUG_USER("Deprecated (disallowed) SVGA3D command: %d\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	वापस -EINVAL;
out_new:
	VMW_DEBUG_USER("SVGA3D command: %d not supported by virtual device.\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vmw_cmd_check_all(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा vmw_sw_context *sw_context, व्योम *buf,
			     uपूर्णांक32_t size)
अणु
	पूर्णांक32_t cur_size = size;
	पूर्णांक ret;

	sw_context->buf_start = buf;

	जबतक (cur_size > 0) अणु
		size = cur_size;
		ret = vmw_cmd_check(dev_priv, sw_context, buf, &size);
		अगर (unlikely(ret != 0))
			वापस ret;
		buf = (व्योम *)((अचिन्हित दीर्घ) buf + size);
		cur_size -= size;
	पूर्ण

	अगर (unlikely(cur_size != 0)) अणु
		VMW_DEBUG_USER("Command verifier out of sync.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vmw_मुक्त_relocations(काष्ठा vmw_sw_context *sw_context)
अणु
	/* Memory is validation context memory, so no need to मुक्त it */
	INIT_LIST_HEAD(&sw_context->bo_relocations);
पूर्ण

अटल व्योम vmw_apply_relocations(काष्ठा vmw_sw_context *sw_context)
अणु
	काष्ठा vmw_relocation *reloc;
	काष्ठा tपंचांग_buffer_object *bo;

	list_क्रम_each_entry(reloc, &sw_context->bo_relocations, head) अणु
		bo = &reloc->vbo->base;
		चयन (bo->mem.mem_type) अणु
		हाल TTM_PL_VRAM:
			reloc->location->offset += bo->mem.start << PAGE_SHIFT;
			reloc->location->gmrId = SVGA_GMR_FRAMEBUFFER;
			अवरोध;
		हाल VMW_PL_GMR:
			reloc->location->gmrId = bo->mem.start;
			अवरोध;
		हाल VMW_PL_MOB:
			*reloc->mob_loc = bo->mem.start;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
	vmw_मुक्त_relocations(sw_context);
पूर्ण

अटल पूर्णांक vmw_resize_cmd_bounce(काष्ठा vmw_sw_context *sw_context,
				 uपूर्णांक32_t size)
अणु
	अगर (likely(sw_context->cmd_bounce_size >= size))
		वापस 0;

	अगर (sw_context->cmd_bounce_size == 0)
		sw_context->cmd_bounce_size = VMWGFX_CMD_BOUNCE_INIT_SIZE;

	जबतक (sw_context->cmd_bounce_size < size) अणु
		sw_context->cmd_bounce_size =
			PAGE_ALIGN(sw_context->cmd_bounce_size +
				   (sw_context->cmd_bounce_size >> 1));
	पूर्ण

	vमुक्त(sw_context->cmd_bounce);
	sw_context->cmd_bounce = vदो_स्मृति(sw_context->cmd_bounce_size);

	अगर (sw_context->cmd_bounce == शून्य) अणु
		VMW_DEBUG_USER("Failed to allocate command bounce buffer.\n");
		sw_context->cmd_bounce_size = 0;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vmw_execbuf_fence_commands - create and submit a command stream fence
 *
 * Creates a fence object and submits a command stream marker.
 * If this fails क्रम some reason, We sync the fअगरo and वापस शून्य.
 * It is then safe to fence buffers with a शून्य poपूर्णांकer.
 *
 * If @p_handle is not शून्य @file_priv must also not be शून्य. Creates a
 * userspace handle अगर @p_handle is not शून्य, otherwise not.
 */

पूर्णांक vmw_execbuf_fence_commands(काष्ठा drm_file *file_priv,
			       काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_fence_obj **p_fence,
			       uपूर्णांक32_t *p_handle)
अणु
	uपूर्णांक32_t sequence;
	पूर्णांक ret;
	bool synced = false;

	/* p_handle implies file_priv. */
	BUG_ON(p_handle != शून्य && file_priv == शून्य);

	ret = vmw_cmd_send_fence(dev_priv, &sequence);
	अगर (unlikely(ret != 0)) अणु
		VMW_DEBUG_USER("Fence submission error. Syncing.\n");
		synced = true;
	पूर्ण

	अगर (p_handle != शून्य)
		ret = vmw_user_fence_create(file_priv, dev_priv->fman,
					    sequence, p_fence, p_handle);
	अन्यथा
		ret = vmw_fence_create(dev_priv->fman, sequence, p_fence);

	अगर (unlikely(ret != 0 && !synced)) अणु
		(व्योम) vmw_fallback_रुको(dev_priv, false, false, sequence,
					 false, VMW_FENCE_WAIT_TIMEOUT);
		*p_fence = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * vmw_execbuf_copy_fence_user - copy fence object inक्रमmation to user-space.
 *
 * @dev_priv: Poपूर्णांकer to a vmw_निजी काष्ठा.
 * @vmw_fp: Poपूर्णांकer to the काष्ठा vmw_fpriv representing the calling file.
 * @ret: Return value from fence object creation.
 * @user_fence_rep: User space address of a काष्ठा drm_vmw_fence_rep to which
 * the inक्रमmation should be copied.
 * @fence: Poपूर्णांकer to the fenc object.
 * @fence_handle: User-space fence handle.
 * @out_fence_fd: exported file descriptor क्रम the fence.  -1 अगर not used
 * @sync_file:  Only used to clean up in हाल of an error in this function.
 *
 * This function copies fence inक्रमmation to user-space. If copying fails, the
 * user-space काष्ठा drm_vmw_fence_rep::error member is hopefully left
 * untouched, and अगर it's preloaded with an -EFAULT by user-space, the error
 * will hopefully be detected.
 *
 * Also अगर copying fails, user-space will be unable to संकेत the fence object
 * so we रुको क्रम it immediately, and then unreference the user-space reference.
 */
व्योम
vmw_execbuf_copy_fence_user(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_fpriv *vmw_fp, पूर्णांक ret,
			    काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
			    काष्ठा vmw_fence_obj *fence, uपूर्णांक32_t fence_handle,
			    पूर्णांक32_t out_fence_fd, काष्ठा sync_file *sync_file)
अणु
	काष्ठा drm_vmw_fence_rep fence_rep;

	अगर (user_fence_rep == शून्य)
		वापस;

	स_रखो(&fence_rep, 0, माप(fence_rep));

	fence_rep.error = ret;
	fence_rep.fd = out_fence_fd;
	अगर (ret == 0) अणु
		BUG_ON(fence == शून्य);

		fence_rep.handle = fence_handle;
		fence_rep.seqno = fence->base.seqno;
		vmw_update_seqno(dev_priv, &dev_priv->fअगरo);
		fence_rep.passed_seqno = dev_priv->last_पढ़ो_seqno;
	पूर्ण

	/*
	 * copy_to_user errors will be detected by user space not seeing
	 * fence_rep::error filled in. Typically user-space would have pre-set
	 * that member to -EFAULT.
	 */
	ret = copy_to_user(user_fence_rep, &fence_rep,
			   माप(fence_rep));

	/*
	 * User-space lost the fence object. We need to sync and unreference the
	 * handle.
	 */
	अगर (unlikely(ret != 0) && (fence_rep.error == 0)) अणु
		अगर (sync_file)
			fput(sync_file->file);

		अगर (fence_rep.fd != -1) अणु
			put_unused_fd(fence_rep.fd);
			fence_rep.fd = -1;
		पूर्ण

		tपंचांग_ref_object_base_unref(vmw_fp->tfile, fence_handle,
					  TTM_REF_USAGE);
		VMW_DEBUG_USER("Fence copy error. Syncing.\n");
		(व्योम) vmw_fence_obj_रुको(fence, false, false,
					  VMW_FENCE_WAIT_TIMEOUT);
	पूर्ण
पूर्ण

/**
 * vmw_execbuf_submit_fअगरo - Patch a command batch and submit it using the fअगरo.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @kernel_commands: Poपूर्णांकer to the unpatched command batch.
 * @command_size: Size of the unpatched command batch.
 * @sw_context: Structure holding the relocation lists.
 *
 * Side effects: If this function वापसs 0, then the command batch poपूर्णांकed to
 * by @kernel_commands will have been modअगरied.
 */
अटल पूर्णांक vmw_execbuf_submit_fअगरo(काष्ठा vmw_निजी *dev_priv,
				   व्योम *kernel_commands, u32 command_size,
				   काष्ठा vmw_sw_context *sw_context)
अणु
	व्योम *cmd;

	अगर (sw_context->dx_ctx_node)
		cmd = VMW_CMD_CTX_RESERVE(dev_priv, command_size,
					  sw_context->dx_ctx_node->ctx->id);
	अन्यथा
		cmd = VMW_CMD_RESERVE(dev_priv, command_size);

	अगर (!cmd)
		वापस -ENOMEM;

	vmw_apply_relocations(sw_context);
	स_नकल(cmd, kernel_commands, command_size);
	vmw_resource_relocations_apply(cmd, &sw_context->res_relocations);
	vmw_resource_relocations_मुक्त(&sw_context->res_relocations);
	vmw_cmd_commit(dev_priv, command_size);

	वापस 0;
पूर्ण

/**
 * vmw_execbuf_submit_cmdbuf - Patch a command batch and submit it using the
 * command buffer manager.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @header: Opaque handle to the command buffer allocation.
 * @command_size: Size of the unpatched command batch.
 * @sw_context: Structure holding the relocation lists.
 *
 * Side effects: If this function वापसs 0, then the command buffer represented
 * by @header will have been modअगरied.
 */
अटल पूर्णांक vmw_execbuf_submit_cmdbuf(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_cmdbuf_header *header,
				     u32 command_size,
				     काष्ठा vmw_sw_context *sw_context)
अणु
	u32 id = ((sw_context->dx_ctx_node) ? sw_context->dx_ctx_node->ctx->id :
		  SVGA3D_INVALID_ID);
	व्योम *cmd = vmw_cmdbuf_reserve(dev_priv->cman, command_size, id, false,
				       header);

	vmw_apply_relocations(sw_context);
	vmw_resource_relocations_apply(cmd, &sw_context->res_relocations);
	vmw_resource_relocations_मुक्त(&sw_context->res_relocations);
	vmw_cmdbuf_commit(dev_priv->cman, command_size, header, false);

	वापस 0;
पूर्ण

/**
 * vmw_execbuf_cmdbuf - Prepare, अगर possible, a user-space command batch क्रम
 * submission using a command buffer.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @user_commands: User-space poपूर्णांकer to the commands to be submitted.
 * @command_size: Size of the unpatched command batch.
 * @header: Out parameter वापसing the opaque poपूर्णांकer to the command buffer.
 *
 * This function checks whether we can use the command buffer manager क्रम
 * submission and अगर so, creates a command buffer of suitable size and copies
 * the user data पूर्णांकo that buffer.
 *
 * On successful वापस, the function वापसs a poपूर्णांकer to the data in the
 * command buffer and *@header is set to non-शून्य.
 *
 * @kernel_commands: If command buffers could not be used, the function will
 * वापस the value of @kernel_commands on function call. That value may be
 * शून्य. In that हाल, the value of *@header will be set to शून्य.
 *
 * If an error is encountered, the function will वापस a poपूर्णांकer error value.
 * If the function is पूर्णांकerrupted by a संकेत जबतक sleeping, it will वापस
 * -ERESTARTSYS casted to a poपूर्णांकer error value.
 */
अटल व्योम *vmw_execbuf_cmdbuf(काष्ठा vmw_निजी *dev_priv,
				व्योम __user *user_commands,
				व्योम *kernel_commands, u32 command_size,
				काष्ठा vmw_cmdbuf_header **header)
अणु
	माप_प्रकार cmdbuf_size;
	पूर्णांक ret;

	*header = शून्य;
	अगर (command_size > SVGA_CB_MAX_SIZE) अणु
		VMW_DEBUG_USER("Command buffer is too large.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!dev_priv->cman || kernel_commands)
		वापस kernel_commands;

	/* If possible, add a little space क्रम fencing. */
	cmdbuf_size = command_size + 512;
	cmdbuf_size = min_t(माप_प्रकार, cmdbuf_size, SVGA_CB_MAX_SIZE);
	kernel_commands = vmw_cmdbuf_alloc(dev_priv->cman, cmdbuf_size, true,
					   header);
	अगर (IS_ERR(kernel_commands))
		वापस kernel_commands;

	ret = copy_from_user(kernel_commands, user_commands, command_size);
	अगर (ret) अणु
		VMW_DEBUG_USER("Failed copying commands.\n");
		vmw_cmdbuf_header_मुक्त(*header);
		*header = शून्य;
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस kernel_commands;
पूर्ण

अटल पूर्णांक vmw_execbuf_tie_context(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_sw_context *sw_context,
				   uपूर्णांक32_t handle)
अणु
	काष्ठा vmw_resource *res;
	पूर्णांक ret;
	अचिन्हित पूर्णांक size;

	अगर (handle == SVGA3D_INVALID_ID)
		वापस 0;

	size = vmw_execbuf_res_size(dev_priv, vmw_res_dx_context);
	ret = vmw_validation_preload_res(sw_context->ctx, size);
	अगर (ret)
		वापस ret;

	res = vmw_user_resource_noref_lookup_handle
		(dev_priv, sw_context->fp->tfile, handle,
		 user_context_converter);
	अगर (IS_ERR(res)) अणु
		VMW_DEBUG_USER("Could not find or user DX context 0x%08x.\n",
			       (अचिन्हित पूर्णांक) handle);
		वापस PTR_ERR(res);
	पूर्ण

	ret = vmw_execbuf_res_noref_val_add(sw_context, res, VMW_RES_सूचीTY_SET);
	अगर (unlikely(ret != 0))
		वापस ret;

	sw_context->dx_ctx_node = vmw_execbuf_info_from_res(sw_context, res);
	sw_context->man = vmw_context_res_man(res);

	वापस 0;
पूर्ण

पूर्णांक vmw_execbuf_process(काष्ठा drm_file *file_priv,
			काष्ठा vmw_निजी *dev_priv,
			व्योम __user *user_commands, व्योम *kernel_commands,
			uपूर्णांक32_t command_size, uपूर्णांक64_t throttle_us,
			uपूर्णांक32_t dx_context_handle,
			काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
			काष्ठा vmw_fence_obj **out_fence, uपूर्णांक32_t flags)
अणु
	काष्ठा vmw_sw_context *sw_context = &dev_priv->ctx;
	काष्ठा vmw_fence_obj *fence = शून्य;
	काष्ठा vmw_cmdbuf_header *header;
	uपूर्णांक32_t handle = 0;
	पूर्णांक ret;
	पूर्णांक32_t out_fence_fd = -1;
	काष्ठा sync_file *sync_file = शून्य;
	DECLARE_VAL_CONTEXT(val_ctx, &sw_context->res_ht, 1);

	vmw_validation_set_val_mem(&val_ctx, &dev_priv->vvm);

	अगर (flags & DRM_VMW_EXECBUF_FLAG_EXPORT_FENCE_FD) अणु
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		अगर (out_fence_fd < 0) अणु
			VMW_DEBUG_USER("Failed to get a fence fd.\n");
			वापस out_fence_fd;
		पूर्ण
	पूर्ण

	अगर (throttle_us) अणु
		VMW_DEBUG_USER("Throttling is no longer supported.\n");
	पूर्ण

	kernel_commands = vmw_execbuf_cmdbuf(dev_priv, user_commands,
					     kernel_commands, command_size,
					     &header);
	अगर (IS_ERR(kernel_commands)) अणु
		ret = PTR_ERR(kernel_commands);
		जाओ out_मुक्त_fence_fd;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&dev_priv->cmdbuf_mutex);
	अगर (ret) अणु
		ret = -ERESTARTSYS;
		जाओ out_मुक्त_header;
	पूर्ण

	sw_context->kernel = false;
	अगर (kernel_commands == शून्य) अणु
		ret = vmw_resize_cmd_bounce(sw_context, command_size);
		अगर (unlikely(ret != 0))
			जाओ out_unlock;

		ret = copy_from_user(sw_context->cmd_bounce, user_commands,
				     command_size);
		अगर (unlikely(ret != 0)) अणु
			ret = -EFAULT;
			VMW_DEBUG_USER("Failed copying commands.\n");
			जाओ out_unlock;
		पूर्ण

		kernel_commands = sw_context->cmd_bounce;
	पूर्ण अन्यथा अगर (!header) अणु
		sw_context->kernel = true;
	पूर्ण

	sw_context->fp = vmw_fpriv(file_priv);
	INIT_LIST_HEAD(&sw_context->ctx_list);
	sw_context->cur_query_bo = dev_priv->pinned_bo;
	sw_context->last_query_ctx = शून्य;
	sw_context->needs_post_query_barrier = false;
	sw_context->dx_ctx_node = शून्य;
	sw_context->dx_query_mob = शून्य;
	sw_context->dx_query_ctx = शून्य;
	स_रखो(sw_context->res_cache, 0, माप(sw_context->res_cache));
	INIT_LIST_HEAD(&sw_context->res_relocations);
	INIT_LIST_HEAD(&sw_context->bo_relocations);

	अगर (sw_context->staged_bindings)
		vmw_binding_state_reset(sw_context->staged_bindings);

	अगर (!sw_context->res_ht_initialized) अणु
		ret = drm_ht_create(&sw_context->res_ht, VMW_RES_HT_ORDER);
		अगर (unlikely(ret != 0))
			जाओ out_unlock;

		sw_context->res_ht_initialized = true;
	पूर्ण

	INIT_LIST_HEAD(&sw_context->staged_cmd_res);
	sw_context->ctx = &val_ctx;
	ret = vmw_execbuf_tie_context(dev_priv, sw_context, dx_context_handle);
	अगर (unlikely(ret != 0))
		जाओ out_err_nores;

	ret = vmw_cmd_check_all(dev_priv, sw_context, kernel_commands,
				command_size);
	अगर (unlikely(ret != 0))
		जाओ out_err_nores;

	ret = vmw_resources_reserve(sw_context);
	अगर (unlikely(ret != 0))
		जाओ out_err_nores;

	ret = vmw_validation_bo_reserve(&val_ctx, true);
	अगर (unlikely(ret != 0))
		जाओ out_err_nores;

	ret = vmw_validation_bo_validate(&val_ctx, true);
	अगर (unlikely(ret != 0))
		जाओ out_err;

	ret = vmw_validation_res_validate(&val_ctx, true);
	अगर (unlikely(ret != 0))
		जाओ out_err;

	vmw_validation_drop_ht(&val_ctx);

	ret = mutex_lock_पूर्णांकerruptible(&dev_priv->binding_mutex);
	अगर (unlikely(ret != 0)) अणु
		ret = -ERESTARTSYS;
		जाओ out_err;
	पूर्ण

	अगर (dev_priv->has_mob) अणु
		ret = vmw_rebind_contexts(sw_context);
		अगर (unlikely(ret != 0))
			जाओ out_unlock_binding;
	पूर्ण

	अगर (!header) अणु
		ret = vmw_execbuf_submit_fअगरo(dev_priv, kernel_commands,
					      command_size, sw_context);
	पूर्ण अन्यथा अणु
		ret = vmw_execbuf_submit_cmdbuf(dev_priv, header, command_size,
						sw_context);
		header = शून्य;
	पूर्ण
	mutex_unlock(&dev_priv->binding_mutex);
	अगर (ret)
		जाओ out_err;

	vmw_query_bo_चयन_commit(dev_priv, sw_context);
	ret = vmw_execbuf_fence_commands(file_priv, dev_priv, &fence,
					 (user_fence_rep) ? &handle : शून्य);
	/*
	 * This error is harmless, because अगर fence submission fails,
	 * vmw_fअगरo_send_fence will sync. The error will be propagated to
	 * user-space in @fence_rep
	 */
	अगर (ret != 0)
		VMW_DEBUG_USER("Fence submission error. Syncing.\n");

	vmw_execbuf_bindings_commit(sw_context, false);
	vmw_bind_dx_query_mob(sw_context);
	vmw_validation_res_unreserve(&val_ctx, false);

	vmw_validation_bo_fence(sw_context->ctx, fence);

	अगर (unlikely(dev_priv->pinned_bo != शून्य && !dev_priv->query_cid_valid))
		__vmw_execbuf_release_pinned_bo(dev_priv, fence);

	/*
	 * If anything fails here, give up trying to export the fence and करो a
	 * sync since the user mode will not be able to sync the fence itself.
	 * This ensures we are still functionally correct.
	 */
	अगर (flags & DRM_VMW_EXECBUF_FLAG_EXPORT_FENCE_FD) अणु

		sync_file = sync_file_create(&fence->base);
		अगर (!sync_file) अणु
			VMW_DEBUG_USER("Sync file create failed for fence\n");
			put_unused_fd(out_fence_fd);
			out_fence_fd = -1;

			(व्योम) vmw_fence_obj_रुको(fence, false, false,
						  VMW_FENCE_WAIT_TIMEOUT);
		पूर्ण अन्यथा अणु
			/* Link the fence with the FD created earlier */
			fd_install(out_fence_fd, sync_file->file);
		पूर्ण
	पूर्ण

	vmw_execbuf_copy_fence_user(dev_priv, vmw_fpriv(file_priv), ret,
				    user_fence_rep, fence, handle, out_fence_fd,
				    sync_file);

	/* Don't unreference when handing fence out */
	अगर (unlikely(out_fence != शून्य)) अणु
		*out_fence = fence;
		fence = शून्य;
	पूर्ण अन्यथा अगर (likely(fence != शून्य)) अणु
		vmw_fence_obj_unreference(&fence);
	पूर्ण

	vmw_cmdbuf_res_commit(&sw_context->staged_cmd_res);
	mutex_unlock(&dev_priv->cmdbuf_mutex);

	/*
	 * Unreference resources outside of the cmdbuf_mutex to aव्योम deadlocks
	 * in resource deकाष्ठाion paths.
	 */
	vmw_validation_unref_lists(&val_ctx);

	वापस 0;

out_unlock_binding:
	mutex_unlock(&dev_priv->binding_mutex);
out_err:
	vmw_validation_bo_backoff(&val_ctx);
out_err_nores:
	vmw_execbuf_bindings_commit(sw_context, true);
	vmw_validation_res_unreserve(&val_ctx, true);
	vmw_resource_relocations_मुक्त(&sw_context->res_relocations);
	vmw_मुक्त_relocations(sw_context);
	अगर (unlikely(dev_priv->pinned_bo != शून्य && !dev_priv->query_cid_valid))
		__vmw_execbuf_release_pinned_bo(dev_priv, शून्य);
out_unlock:
	vmw_cmdbuf_res_revert(&sw_context->staged_cmd_res);
	vmw_validation_drop_ht(&val_ctx);
	WARN_ON(!list_empty(&sw_context->ctx_list));
	mutex_unlock(&dev_priv->cmdbuf_mutex);

	/*
	 * Unreference resources outside of the cmdbuf_mutex to aव्योम deadlocks
	 * in resource deकाष्ठाion paths.
	 */
	vmw_validation_unref_lists(&val_ctx);
out_मुक्त_header:
	अगर (header)
		vmw_cmdbuf_header_मुक्त(header);
out_मुक्त_fence_fd:
	अगर (out_fence_fd >= 0)
		put_unused_fd(out_fence_fd);

	वापस ret;
पूर्ण

/**
 * vmw_execbuf_unpin_panic - Idle the fअगरo and unpin the query buffer.
 *
 * @dev_priv: The device निजी काष्ठाure.
 *
 * This function is called to idle the fअगरo and unpin the query buffer अगर the
 * normal way to करो this hits an error, which should typically be extremely
 * rare.
 */
अटल व्योम vmw_execbuf_unpin_panic(काष्ठा vmw_निजी *dev_priv)
अणु
	VMW_DEBUG_USER("Can't unpin query buffer. Trying to recover.\n");

	(व्योम) vmw_fallback_रुको(dev_priv, false, true, 0, false, 10*HZ);
	vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
	अगर (dev_priv->dummy_query_bo_pinned) अणु
		vmw_bo_pin_reserved(dev_priv->dummy_query_bo, false);
		dev_priv->dummy_query_bo_pinned = false;
	पूर्ण
पूर्ण


/**
 * __vmw_execbuf_release_pinned_bo - Flush queries and unpin the pinned query
 * bo.
 *
 * @dev_priv: The device निजी काष्ठाure.
 * @fence: If non-शून्य should poपूर्णांक to a काष्ठा vmw_fence_obj issued _after_ a
 * query barrier that flushes all queries touching the current buffer poपूर्णांकed to
 * by @dev_priv->pinned_bo
 *
 * This function should be used to unpin the pinned query bo, or as a query
 * barrier when we need to make sure that all queries have finished beक्रमe the
 * next fअगरo command. (For example on hardware context deकाष्ठाions where the
 * hardware may otherwise leak unfinished queries).
 *
 * This function करोes not वापस any failure codes, but make attempts to करो safe
 * unpinning in हाल of errors.
 *
 * The function will synchronize on the previous query barrier, and will thus
 * not finish until that barrier has executed.
 *
 * the @dev_priv->cmdbuf_mutex needs to be held by the current thपढ़ो beक्रमe
 * calling this function.
 */
व्योम __vmw_execbuf_release_pinned_bo(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_fence_obj *fence)
अणु
	पूर्णांक ret = 0;
	काष्ठा vmw_fence_obj *lfence = शून्य;
	DECLARE_VAL_CONTEXT(val_ctx, शून्य, 0);

	अगर (dev_priv->pinned_bo == शून्य)
		जाओ out_unlock;

	ret = vmw_validation_add_bo(&val_ctx, dev_priv->pinned_bo, false,
				    false);
	अगर (ret)
		जाओ out_no_reserve;

	ret = vmw_validation_add_bo(&val_ctx, dev_priv->dummy_query_bo, false,
				    false);
	अगर (ret)
		जाओ out_no_reserve;

	ret = vmw_validation_bo_reserve(&val_ctx, false);
	अगर (ret)
		जाओ out_no_reserve;

	अगर (dev_priv->query_cid_valid) अणु
		BUG_ON(fence != शून्य);
		ret = vmw_cmd_emit_dummy_query(dev_priv, dev_priv->query_cid);
		अगर (ret)
			जाओ out_no_emit;
		dev_priv->query_cid_valid = false;
	पूर्ण

	vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
	अगर (dev_priv->dummy_query_bo_pinned) अणु
		vmw_bo_pin_reserved(dev_priv->dummy_query_bo, false);
		dev_priv->dummy_query_bo_pinned = false;
	पूर्ण
	अगर (fence == शून्य) अणु
		(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv, &lfence,
						  शून्य);
		fence = lfence;
	पूर्ण
	vmw_validation_bo_fence(&val_ctx, fence);
	अगर (lfence != शून्य)
		vmw_fence_obj_unreference(&lfence);

	vmw_validation_unref_lists(&val_ctx);
	vmw_bo_unreference(&dev_priv->pinned_bo);

out_unlock:
	वापस;
out_no_emit:
	vmw_validation_bo_backoff(&val_ctx);
out_no_reserve:
	vmw_validation_unref_lists(&val_ctx);
	vmw_execbuf_unpin_panic(dev_priv);
	vmw_bo_unreference(&dev_priv->pinned_bo);
पूर्ण

/**
 * vmw_execbuf_release_pinned_bo - Flush queries and unpin the pinned query bo.
 *
 * @dev_priv: The device निजी काष्ठाure.
 *
 * This function should be used to unpin the pinned query bo, or as a query
 * barrier when we need to make sure that all queries have finished beक्रमe the
 * next fअगरo command. (For example on hardware context deकाष्ठाions where the
 * hardware may otherwise leak unfinished queries).
 *
 * This function करोes not वापस any failure codes, but make attempts to करो safe
 * unpinning in हाल of errors.
 *
 * The function will synchronize on the previous query barrier, and will thus
 * not finish until that barrier has executed.
 */
व्योम vmw_execbuf_release_pinned_bo(काष्ठा vmw_निजी *dev_priv)
अणु
	mutex_lock(&dev_priv->cmdbuf_mutex);
	अगर (dev_priv->query_cid_valid)
		__vmw_execbuf_release_pinned_bo(dev_priv, शून्य);
	mutex_unlock(&dev_priv->cmdbuf_mutex);
पूर्ण

पूर्णांक vmw_execbuf_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_vmw_execbuf_arg *arg = data;
	पूर्णांक ret;
	काष्ठा dma_fence *in_fence = शून्य;

	/*
	 * Extend the ioctl argument जबतक मुख्यtaining backwards compatibility:
	 * We take dअगरferent code paths depending on the value of arg->version.
	 *
	 * Note: The ioctl argument is extended and zeropadded by core DRM.
	 */
	अगर (unlikely(arg->version > DRM_VMW_EXECBUF_VERSION ||
		     arg->version == 0)) अणु
		VMW_DEBUG_USER("Incorrect execbuf version.\n");
		वापस -EINVAL;
	पूर्ण

	चयन (arg->version) अणु
	हाल 1:
		/* For v1 core DRM have extended + zeropadded the data */
		arg->context_handle = (uपूर्णांक32_t) -1;
		अवरोध;
	हाल 2:
	शेष:
		/* For v2 and later core DRM would have correctly copied it */
		अवरोध;
	पूर्ण

	/* If imported a fence FD from अन्यथाwhere, then रुको on it */
	अगर (arg->flags & DRM_VMW_EXECBUF_FLAG_IMPORT_FENCE_FD) अणु
		in_fence = sync_file_get_fence(arg->imported_fence_fd);

		अगर (!in_fence) अणु
			VMW_DEBUG_USER("Cannot get imported fence\n");
			वापस -EINVAL;
		पूर्ण

		ret = vmw_रुको_dma_fence(dev_priv->fman, in_fence);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_execbuf_process(file_priv, dev_priv,
				  (व्योम __user *)(अचिन्हित दीर्घ)arg->commands,
				  शून्य, arg->command_size, arg->throttle_us,
				  arg->context_handle,
				  (व्योम __user *)(अचिन्हित दीर्घ)arg->fence_rep,
				  शून्य, arg->flags);

	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	अगर (unlikely(ret != 0))
		जाओ out;

	vmw_kms_cursor_post_execbuf(dev_priv);

out:
	अगर (in_fence)
		dma_fence_put(in_fence);
	वापस ret;
पूर्ण
