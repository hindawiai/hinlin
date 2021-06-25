<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2015 VMware, Inc., Palo Alto, CA., USA
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
 * This file implements the vmwgfx context binding manager,
 * The sole reason क्रम having to use this code is that vmware guest
 * backed contexts can be swapped out to their backing mobs by the device
 * at any समय, also swapped in at any समय. At swapin समय, the device
 * validates the context bindings to make sure they poपूर्णांक to valid resources.
 * It's this outside-of-drawcall validation (that can happen at any समय),
 * that makes this code necessary.
 *
 * We thereक्रमe need to समाप्त any context bindings poपूर्णांकing to a resource
 * when the resource is swapped out. Furthermore, अगर the vmwgfx driver has
 * swapped out the context we can't swap it in again to समाप्त bindings because
 * of backing mob reservation lockdep violations, so as part of
 * context swapout, also समाप्त all bindings of a context, so that they are
 * alपढ़ोy समाप्तed अगर a resource to which a binding poपूर्णांकs
 * needs to be swapped out.
 *
 * Note that a resource can be poपूर्णांकed to by bindings from multiple contexts,
 * Thereक्रमe we can't easily protect this data by a per context mutex
 * (unless we use deadlock-safe WW mutexes). So we use a global binding_mutex
 * to protect all binding manager data.
 *
 * Finally, any association between a context and a global resource
 * (surface, shader or even DX query) is conceptually a context binding that
 * needs to be tracked by this code.
 */

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_binding.h"
#समावेश "device_include/svga3d_reg.h"

#घोषणा VMW_BINDING_RT_BIT     0
#घोषणा VMW_BINDING_PS_BIT     1
#घोषणा VMW_BINDING_SO_T_BIT   2
#घोषणा VMW_BINDING_VB_BIT     3
#घोषणा VMW_BINDING_UAV_BIT    4
#घोषणा VMW_BINDING_CS_UAV_BIT 5
#घोषणा VMW_BINDING_NUM_BITS   6

#घोषणा VMW_BINDING_PS_SR_BIT  0

/**
 * काष्ठा vmw_ctx_binding_state - per context binding state
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठाure.
 * @list: linked list of inभागidual active bindings.
 * @render_tarमाला_लो: Render target bindings.
 * @texture_units: Texture units bindings.
 * @ds_view: Depth-stencil view binding.
 * @so_tarमाला_लो: StreamOutput target bindings.
 * @vertex_buffers: Vertex buffer bindings.
 * @index_buffer: Index buffer binding.
 * @per_shader: Per shader-type bindings.
 * @ua_views: UAV bindings.
 * @so_state: StreamOutput bindings.
 * @dirty: Biपंचांगap tracking per binding-type changes that have not yet
 * been emitted to the device.
 * @dirty_vb: Biपंचांगap tracking inभागidual vertex buffer binding changes that
 * have not yet been emitted to the device.
 * @bind_cmd_buffer: Scratch space used to स्थिरruct binding commands.
 * @bind_cmd_count: Number of binding command data entries in @bind_cmd_buffer
 * @bind_first_slot: Used together with @bind_cmd_buffer to indicate the
 * device binding slot of the first command data entry in @bind_cmd_buffer.
 *
 * Note that this काष्ठाure also provides storage space क्रम the inभागidual
 * काष्ठा vmw_ctx_binding objects, so that no dynamic allocation is needed
 * क्रम inभागidual bindings.
 *
 */
काष्ठा vmw_ctx_binding_state अणु
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा list_head list;
	काष्ठा vmw_ctx_bindinfo_view render_tarमाला_लो[SVGA3D_RT_MAX];
	काष्ठा vmw_ctx_bindinfo_tex texture_units[SVGA3D_NUM_TEXTURE_UNITS];
	काष्ठा vmw_ctx_bindinfo_view ds_view;
	काष्ठा vmw_ctx_bindinfo_so_target so_tarमाला_लो[SVGA3D_DX_MAX_SOTARGETS];
	काष्ठा vmw_ctx_bindinfo_vb vertex_buffers[SVGA3D_DX_MAX_VERTEXBUFFERS];
	काष्ठा vmw_ctx_bindinfo_ib index_buffer;
	काष्ठा vmw_dx_shader_bindings per_shader[SVGA3D_NUM_SHADERTYPE];
	काष्ठा vmw_ctx_bindinfo_uav ua_views[VMW_MAX_UAV_BIND_TYPE];
	काष्ठा vmw_ctx_bindinfo_so so_state;

	अचिन्हित दीर्घ dirty;
	DECLARE_BITMAP(dirty_vb, SVGA3D_DX_MAX_VERTEXBUFFERS);

	u32 bind_cmd_buffer[VMW_MAX_VIEW_BINDINGS];
	u32 bind_cmd_count;
	u32 bind_first_slot;
पूर्ण;

अटल पूर्णांक vmw_binding_scrub_shader(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_render_target(काष्ठा vmw_ctx_bindinfo *bi,
					   bool rebind);
अटल पूर्णांक vmw_binding_scrub_texture(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_cb(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_dx_rt(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_sr(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_so_target(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_emit_dirty(काष्ठा vmw_ctx_binding_state *cbs);
अटल पूर्णांक vmw_binding_scrub_dx_shader(काष्ठा vmw_ctx_bindinfo *bi,
				       bool rebind);
अटल पूर्णांक vmw_binding_scrub_ib(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_vb(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_uav(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_cs_uav(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);
अटल पूर्णांक vmw_binding_scrub_so(काष्ठा vmw_ctx_bindinfo *bi, bool rebind);

अटल व्योम vmw_binding_build_निश्चितs(व्योम) __attribute__ ((unused));

प्रकार पूर्णांक (*vmw_scrub_func)(काष्ठा vmw_ctx_bindinfo *, bool);

/**
 * काष्ठा vmw_binding_info - Per binding type inक्रमmation क्रम the binding
 * manager
 *
 * @size: The size of the काष्ठा binding derived from a काष्ठा vmw_ctx_bindinfo.
 * @offsets: array[shader_slot] of offsets to the array[slot]
 * of काष्ठा bindings क्रम the binding type.
 * @scrub_func: Poपूर्णांकer to the scrub function क्रम this binding type.
 *
 * Holds अटल inक्रमmation to help optimize the binding manager and aव्योम
 * an excessive amount of चयन statements.
 */
काष्ठा vmw_binding_info अणु
	माप_प्रकार size;
	स्थिर माप_प्रकार *offsets;
	vmw_scrub_func scrub_func;
पूर्ण;

/*
 * A number of अटल variables that help determine the scrub func and the
 * location of the काष्ठा vmw_ctx_bindinfo slots क्रम each binding type.
 */
अटल स्थिर माप_प्रकार vmw_binding_shader_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[0].shader),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[1].shader),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[2].shader),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[3].shader),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[4].shader),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[5].shader),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_rt_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, render_tarमाला_लो),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_tex_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, texture_units),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_cb_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[0].स्थिर_buffers),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[1].स्थिर_buffers),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[2].स्थिर_buffers),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[3].स्थिर_buffers),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[4].स्थिर_buffers),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[5].स्थिर_buffers),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_dx_ds_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, ds_view),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_sr_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[0].shader_res),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[1].shader_res),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[2].shader_res),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[3].shader_res),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[4].shader_res),
	दुरत्व(काष्ठा vmw_ctx_binding_state, per_shader[5].shader_res),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_so_target_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, so_tarमाला_लो),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_vb_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, vertex_buffers),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_ib_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, index_buffer),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_uav_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, ua_views[0].views),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_cs_uav_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, ua_views[1].views),
पूर्ण;
अटल स्थिर माप_प्रकार vmw_binding_so_offsets[] = अणु
	दुरत्व(काष्ठा vmw_ctx_binding_state, so_state),
पूर्ण;

अटल स्थिर काष्ठा vmw_binding_info vmw_binding_infos[] = अणु
	[vmw_ctx_binding_shader] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_shader),
		.offsets = vmw_binding_shader_offsets,
		.scrub_func = vmw_binding_scrub_shaderपूर्ण,
	[vmw_ctx_binding_rt] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_rt_offsets,
		.scrub_func = vmw_binding_scrub_render_targetपूर्ण,
	[vmw_ctx_binding_tex] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_tex),
		.offsets = vmw_binding_tex_offsets,
		.scrub_func = vmw_binding_scrub_textureपूर्ण,
	[vmw_ctx_binding_cb] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_cb),
		.offsets = vmw_binding_cb_offsets,
		.scrub_func = vmw_binding_scrub_cbपूर्ण,
	[vmw_ctx_binding_dx_shader] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_shader),
		.offsets = vmw_binding_shader_offsets,
		.scrub_func = vmw_binding_scrub_dx_shaderपूर्ण,
	[vmw_ctx_binding_dx_rt] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_rt_offsets,
		.scrub_func = vmw_binding_scrub_dx_rtपूर्ण,
	[vmw_ctx_binding_sr] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_sr_offsets,
		.scrub_func = vmw_binding_scrub_srपूर्ण,
	[vmw_ctx_binding_ds] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_dx_ds_offsets,
		.scrub_func = vmw_binding_scrub_dx_rtपूर्ण,
	[vmw_ctx_binding_so_target] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_so_target),
		.offsets = vmw_binding_so_target_offsets,
		.scrub_func = vmw_binding_scrub_so_targetपूर्ण,
	[vmw_ctx_binding_vb] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_vb),
		.offsets = vmw_binding_vb_offsets,
		.scrub_func = vmw_binding_scrub_vbपूर्ण,
	[vmw_ctx_binding_ib] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_ib),
		.offsets = vmw_binding_ib_offsets,
		.scrub_func = vmw_binding_scrub_ibपूर्ण,
	[vmw_ctx_binding_uav] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_uav_offsets,
		.scrub_func = vmw_binding_scrub_uavपूर्ण,
	[vmw_ctx_binding_cs_uav] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_cs_uav_offsets,
		.scrub_func = vmw_binding_scrub_cs_uavपूर्ण,
	[vmw_ctx_binding_so] = अणु
		.size = माप(काष्ठा vmw_ctx_bindinfo_so),
		.offsets = vmw_binding_so_offsets,
		.scrub_func = vmw_binding_scrub_soपूर्ण,
पूर्ण;

/**
 * vmw_cbs_context - Return a poपूर्णांकer to the context resource of a
 * context binding state tracker.
 *
 * @cbs: The context binding state tracker.
 *
 * Provided there are any active bindings, this function will वापस an
 * unreferenced poपूर्णांकer to the context resource that owns the context
 * binding state tracker. If there are no active bindings, this function
 * will वापस शून्य. Note that the caller must somehow ensure that a reference
 * is held on the context resource prior to calling this function.
 */
अटल स्थिर काष्ठा vmw_resource *
vmw_cbs_context(स्थिर काष्ठा vmw_ctx_binding_state *cbs)
अणु
	अगर (list_empty(&cbs->list))
		वापस शून्य;

	वापस list_first_entry(&cbs->list, काष्ठा vmw_ctx_bindinfo,
				ctx_list)->ctx;
पूर्ण

/**
 * vmw_binding_loc - determine the काष्ठा vmw_ctx_bindinfo slot location.
 *
 * @cbs: Poपूर्णांकer to a काष्ठा vmw_ctx_binding state which holds the slot.
 * @bt: The binding type.
 * @shader_slot: The shader slot of the binding. If none, then set to 0.
 * @slot: The slot of the binding.
 */
अटल काष्ठा vmw_ctx_bindinfo *
vmw_binding_loc(काष्ठा vmw_ctx_binding_state *cbs,
		क्रमागत vmw_ctx_binding_type bt, u32 shader_slot, u32 slot)
अणु
	स्थिर काष्ठा vmw_binding_info *b = &vmw_binding_infos[bt];
	माप_प्रकार offset = b->offsets[shader_slot] + b->size*slot;

	वापस (काष्ठा vmw_ctx_bindinfo *)((u8 *) cbs + offset);
पूर्ण

/**
 * vmw_binding_drop: Stop tracking a context binding
 *
 * @bi: Poपूर्णांकer to binding tracker storage.
 *
 * Stops tracking a context binding, and re-initializes its storage.
 * Typically used when the context binding is replaced with a binding to
 * another (or the same, क्रम that matter) resource.
 */
अटल व्योम vmw_binding_drop(काष्ठा vmw_ctx_bindinfo *bi)
अणु
	list_del(&bi->ctx_list);
	अगर (!list_empty(&bi->res_list))
		list_del(&bi->res_list);
	bi->ctx = शून्य;
पूर्ण

/**
 * vmw_binding_add: Start tracking a context binding
 *
 * @cbs: Poपूर्णांकer to the context binding state tracker.
 * @bi: Inक्रमmation about the binding to track.
 * @shader_slot: The shader slot of the binding.
 * @slot: The slot of the binding.
 *
 * Starts tracking the binding in the context binding
 * state काष्ठाure @cbs.
 */
व्योम vmw_binding_add(काष्ठा vmw_ctx_binding_state *cbs,
		    स्थिर काष्ठा vmw_ctx_bindinfo *bi,
		    u32 shader_slot, u32 slot)
अणु
	काष्ठा vmw_ctx_bindinfo *loc =
		vmw_binding_loc(cbs, bi->bt, shader_slot, slot);
	स्थिर काष्ठा vmw_binding_info *b = &vmw_binding_infos[bi->bt];

	अगर (loc->ctx != शून्य)
		vmw_binding_drop(loc);

	स_नकल(loc, bi, b->size);
	loc->scrubbed = false;
	list_add(&loc->ctx_list, &cbs->list);
	INIT_LIST_HEAD(&loc->res_list);
पूर्ण

/**
 * vmw_binding_add_uav_index - Add UAV index क्रम tracking.
 * @cbs: Poपूर्णांकer to the context binding state tracker.
 * @slot: UAV type to which bind this index.
 * @index: The splice index to track.
 */
व्योम vmw_binding_add_uav_index(काष्ठा vmw_ctx_binding_state *cbs, uपूर्णांक32 slot,
			       uपूर्णांक32 index)
अणु
	cbs->ua_views[slot].index = index;
पूर्ण

/**
 * vmw_binding_transfer: Transfer a context binding tracking entry.
 *
 * @cbs: Poपूर्णांकer to the persistent context binding state tracker.
 * @from: Staged binding info built during execbuf
 * @bi: Inक्रमmation about the binding to track.
 *
 */
अटल व्योम vmw_binding_transfer(काष्ठा vmw_ctx_binding_state *cbs,
				 स्थिर काष्ठा vmw_ctx_binding_state *from,
				 स्थिर काष्ठा vmw_ctx_bindinfo *bi)
अणु
	माप_प्रकार offset = (अचिन्हित दीर्घ)bi - (अचिन्हित दीर्घ)from;
	काष्ठा vmw_ctx_bindinfo *loc = (काष्ठा vmw_ctx_bindinfo *)
		((अचिन्हित दीर्घ) cbs + offset);

	अगर (loc->ctx != शून्य) अणु
		WARN_ON(bi->scrubbed);

		vmw_binding_drop(loc);
	पूर्ण

	अगर (bi->res != शून्य) अणु
		स_नकल(loc, bi, vmw_binding_infos[bi->bt].size);
		list_add_tail(&loc->ctx_list, &cbs->list);
		list_add_tail(&loc->res_list, &loc->res->binding_head);
	पूर्ण
पूर्ण

/**
 * vmw_binding_state_समाप्त - Kill all bindings associated with a
 * काष्ठा vmw_ctx_binding state काष्ठाure, and re-initialize the काष्ठाure.
 *
 * @cbs: Poपूर्णांकer to the context binding state tracker.
 *
 * Emits commands to scrub all bindings associated with the
 * context binding state tracker. Then re-initializes the whole काष्ठाure.
 */
व्योम vmw_binding_state_समाप्त(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	काष्ठा vmw_ctx_bindinfo *entry, *next;

	vmw_binding_state_scrub(cbs);
	list_क्रम_each_entry_safe(entry, next, &cbs->list, ctx_list)
		vmw_binding_drop(entry);
पूर्ण

/**
 * vmw_binding_state_scrub - Scrub all bindings associated with a
 * काष्ठा vmw_ctx_binding state काष्ठाure.
 *
 * @cbs: Poपूर्णांकer to the context binding state tracker.
 *
 * Emits commands to scrub all bindings associated with the
 * context binding state tracker.
 */
व्योम vmw_binding_state_scrub(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	काष्ठा vmw_ctx_bindinfo *entry;

	list_क्रम_each_entry(entry, &cbs->list, ctx_list) अणु
		अगर (!entry->scrubbed) अणु
			(व्योम) vmw_binding_infos[entry->bt].scrub_func
				(entry, false);
			entry->scrubbed = true;
		पूर्ण
	पूर्ण

	(व्योम) vmw_binding_emit_dirty(cbs);
पूर्ण

/**
 * vmw_binding_res_list_समाप्त - Kill all bindings on a
 * resource binding list
 *
 * @head: list head of resource binding list
 *
 * Kills all bindings associated with a specअगरic resource. Typically
 * called beक्रमe the resource is destroyed.
 */
व्योम vmw_binding_res_list_समाप्त(काष्ठा list_head *head)
अणु
	काष्ठा vmw_ctx_bindinfo *entry, *next;

	vmw_binding_res_list_scrub(head);
	list_क्रम_each_entry_safe(entry, next, head, res_list)
		vmw_binding_drop(entry);
पूर्ण

/**
 * vmw_binding_res_list_scrub - Scrub all bindings on a
 * resource binding list
 *
 * @head: list head of resource binding list
 *
 * Scrub all bindings associated with a specअगरic resource. Typically
 * called beक्रमe the resource is evicted.
 */
व्योम vmw_binding_res_list_scrub(काष्ठा list_head *head)
अणु
	काष्ठा vmw_ctx_bindinfo *entry;

	list_क्रम_each_entry(entry, head, res_list) अणु
		अगर (!entry->scrubbed) अणु
			(व्योम) vmw_binding_infos[entry->bt].scrub_func
				(entry, false);
			entry->scrubbed = true;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(entry, head, res_list) अणु
		काष्ठा vmw_ctx_binding_state *cbs =
			vmw_context_binding_state(entry->ctx);

		(व्योम) vmw_binding_emit_dirty(cbs);
	पूर्ण
पूर्ण


/**
 * vmw_binding_state_commit - Commit staged binding info
 *
 * @to:   Staged binding info area to copy पूर्णांकo to.
 * @from: Staged binding info built during execbuf.
 *
 * Transfers binding info from a temporary काष्ठाure
 * (typically used by execbuf) to the persistent
 * काष्ठाure in the context. This can be करोne once commands have been
 * submitted to hardware
 */
व्योम vmw_binding_state_commit(काष्ठा vmw_ctx_binding_state *to,
			      काष्ठा vmw_ctx_binding_state *from)
अणु
	काष्ठा vmw_ctx_bindinfo *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &from->list, ctx_list) अणु
		vmw_binding_transfer(to, from, entry);
		vmw_binding_drop(entry);
	पूर्ण

	/* Also transfer uav splice indices */
	to->ua_views[0].index = from->ua_views[0].index;
	to->ua_views[1].index = from->ua_views[1].index;
पूर्ण

/**
 * vmw_binding_rebind_all - Rebind all scrubbed bindings of a context
 *
 * @cbs: Poपूर्णांकer to the context binding state tracker.
 *
 * Walks through the context binding list and rebinds all scrubbed
 * resources.
 */
पूर्णांक vmw_binding_rebind_all(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	काष्ठा vmw_ctx_bindinfo *entry;
	पूर्णांक ret;

	list_क्रम_each_entry(entry, &cbs->list, ctx_list) अणु
		अगर (likely(!entry->scrubbed))
			जारी;

		अगर ((entry->res == शून्य || entry->res->id ==
			    SVGA3D_INVALID_ID))
			जारी;

		ret = vmw_binding_infos[entry->bt].scrub_func(entry, true);
		अगर (unlikely(ret != 0))
			वापस ret;

		entry->scrubbed = false;
	पूर्ण

	वापस vmw_binding_emit_dirty(cbs);
पूर्ण

/**
 * vmw_binding_scrub_shader - scrub a shader binding from a context.
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_shader(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_shader *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdSetShader body;
	पूर्ण *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_SET_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = bi->ctx->id;
	cmd->body.type = binding->shader_slot + SVGA3D_SHADERTYPE_MIN;
	cmd->body.shid = ((rebind) ? bi->res->id : SVGA3D_INVALID_ID);
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_render_target - scrub a render target binding
 * from a context.
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_render_target(काष्ठा vmw_ctx_bindinfo *bi,
					   bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_view *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdSetRenderTarget body;
	पूर्ण *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_SETRENDERTARGET;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = bi->ctx->id;
	cmd->body.type = binding->slot;
	cmd->body.target.sid = ((rebind) ? bi->res->id : SVGA3D_INVALID_ID);
	cmd->body.target.face = 0;
	cmd->body.target.mipmap = 0;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_texture - scrub a texture binding from a context.
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 *
 * TODO: Possibly complement this function with a function that takes
 * a list of texture bindings and combines them to a single command.
 */
अटल पूर्णांक vmw_binding_scrub_texture(काष्ठा vmw_ctx_bindinfo *bi,
				     bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_tex *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		काष्ठा अणु
			SVGA3dCmdSetTextureState c;
			SVGA3dTextureState s1;
		पूर्ण body;
	पूर्ण *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_SETTEXTURESTATE;
	cmd->header.size = माप(cmd->body);
	cmd->body.c.cid = bi->ctx->id;
	cmd->body.s1.stage = binding->texture_stage;
	cmd->body.s1.name = SVGA3D_TS_BIND_TEXTURE;
	cmd->body.s1.value = ((rebind) ? bi->res->id : SVGA3D_INVALID_ID);
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_dx_shader - scrub a dx shader binding from a context.
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_dx_shader(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_shader *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetShader body;
	पूर्ण *cmd;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), bi->ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_SHADER;
	cmd->header.size = माप(cmd->body);
	cmd->body.type = binding->shader_slot + SVGA3D_SHADERTYPE_MIN;
	cmd->body.shaderId = ((rebind) ? bi->res->id : SVGA3D_INVALID_ID);
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_cb - scrub a स्थिरant buffer binding from a context.
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_cb(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_cb *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetSingleConstantBuffer body;
	पूर्ण *cmd;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), bi->ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_SINGLE_CONSTANT_BUFFER;
	cmd->header.size = माप(cmd->body);
	cmd->body.slot = binding->slot;
	cmd->body.type = binding->shader_slot + SVGA3D_SHADERTYPE_MIN;
	अगर (rebind) अणु
		cmd->body.offsetInBytes = binding->offset;
		cmd->body.sizeInBytes = binding->size;
		cmd->body.sid = bi->res->id;
	पूर्ण अन्यथा अणु
		cmd->body.offsetInBytes = 0;
		cmd->body.sizeInBytes = 0;
		cmd->body.sid = SVGA3D_INVALID_ID;
	पूर्ण
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_collect_view_ids - Build view id data क्रम a view binding command
 * without checking which bindings actually need to be emitted
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 * @bi: Poपूर्णांकer to where the binding info array is stored in @cbs
 * @max_num: Maximum number of entries in the @bi array.
 *
 * Scans the @bi array क्रम bindings and builds a buffer of view id data.
 * Stops at the first non-existing binding in the @bi array.
 * On output, @cbs->bind_cmd_count contains the number of bindings to be
 * emitted, @cbs->bind_first_slot is set to zero, and @cbs->bind_cmd_buffer
 * contains the command data.
 */
अटल व्योम vmw_collect_view_ids(काष्ठा vmw_ctx_binding_state *cbs,
				 स्थिर काष्ठा vmw_ctx_bindinfo *bi,
				 u32 max_num)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo_view *biv =
		container_of(bi, काष्ठा vmw_ctx_bindinfo_view, bi);
	अचिन्हित दीर्घ i;

	cbs->bind_cmd_count = 0;
	cbs->bind_first_slot = 0;

	क्रम (i = 0; i < max_num; ++i, ++biv) अणु
		अगर (!biv->bi.ctx)
			अवरोध;

		cbs->bind_cmd_buffer[cbs->bind_cmd_count++] =
			((biv->bi.scrubbed) ?
			 SVGA3D_INVALID_ID : biv->bi.res->id);
	पूर्ण
पूर्ण

/**
 * vmw_collect_dirty_view_ids - Build view id data क्रम a view binding command
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 * @bi: Poपूर्णांकer to where the binding info array is stored in @cbs
 * @dirty: Biपंचांगap indicating which bindings need to be emitted.
 * @max_num: Maximum number of entries in the @bi array.
 *
 * Scans the @bi array क्रम bindings that need to be emitted and
 * builds a buffer of view id data.
 * On output, @cbs->bind_cmd_count contains the number of bindings to be
 * emitted, @cbs->bind_first_slot indicates the index of the first emitted
 * binding, and @cbs->bind_cmd_buffer contains the command data.
 */
अटल व्योम vmw_collect_dirty_view_ids(काष्ठा vmw_ctx_binding_state *cbs,
				       स्थिर काष्ठा vmw_ctx_bindinfo *bi,
				       अचिन्हित दीर्घ *dirty,
				       u32 max_num)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo_view *biv =
		container_of(bi, काष्ठा vmw_ctx_bindinfo_view, bi);
	अचिन्हित दीर्घ i, next_bit;

	cbs->bind_cmd_count = 0;
	i = find_first_bit(dirty, max_num);
	next_bit = i;
	cbs->bind_first_slot = i;

	biv += i;
	क्रम (; i < max_num; ++i, ++biv) अणु
		cbs->bind_cmd_buffer[cbs->bind_cmd_count++] =
			((!biv->bi.ctx || biv->bi.scrubbed) ?
			 SVGA3D_INVALID_ID : biv->bi.res->id);

		अगर (next_bit == i) अणु
			next_bit = find_next_bit(dirty, max_num, i + 1);
			अगर (next_bit >= max_num)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmw_binding_emit_set_sr - Issue delayed DX shader resource binding commands
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 * @shader_slot: The shader slot of the binding.
 */
अटल पूर्णांक vmw_emit_set_sr(काष्ठा vmw_ctx_binding_state *cbs,
			   पूर्णांक shader_slot)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo *loc =
		&cbs->per_shader[shader_slot].shader_res[0].bi;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetShaderResources body;
	पूर्ण *cmd;
	माप_प्रकार cmd_size, view_id_size;
	स्थिर काष्ठा vmw_resource *ctx = vmw_cbs_context(cbs);

	vmw_collect_dirty_view_ids(cbs, loc,
				   cbs->per_shader[shader_slot].dirty_sr,
				   SVGA3D_DX_MAX_SRVIEWS);
	अगर (cbs->bind_cmd_count == 0)
		वापस 0;

	view_id_size = cbs->bind_cmd_count*माप(uपूर्णांक32);
	cmd_size = माप(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_RESERVE(ctx->dev_priv, cmd_size, ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_SHADER_RESOURCES;
	cmd->header.size = माप(cmd->body) + view_id_size;
	cmd->body.type = shader_slot + SVGA3D_SHADERTYPE_MIN;
	cmd->body.startView = cbs->bind_first_slot;

	स_नकल(&cmd[1], cbs->bind_cmd_buffer, view_id_size);

	vmw_cmd_commit(ctx->dev_priv, cmd_size);
	biपंचांगap_clear(cbs->per_shader[shader_slot].dirty_sr,
		     cbs->bind_first_slot, cbs->bind_cmd_count);

	वापस 0;
पूर्ण

/**
 * vmw_binding_emit_set_rt - Issue delayed DX rendertarget binding commands
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 */
अटल पूर्णांक vmw_emit_set_rt(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo *loc = &cbs->render_tarमाला_लो[0].bi;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetRenderTarमाला_लो body;
	पूर्ण *cmd;
	माप_प्रकार cmd_size, view_id_size;
	स्थिर काष्ठा vmw_resource *ctx = vmw_cbs_context(cbs);

	vmw_collect_view_ids(cbs, loc, SVGA3D_MAX_SIMULTANEOUS_RENDER_TARGETS);
	view_id_size = cbs->bind_cmd_count*माप(uपूर्णांक32);
	cmd_size = माप(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_RESERVE(ctx->dev_priv, cmd_size, ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_RENDERTARGETS;
	cmd->header.size = माप(cmd->body) + view_id_size;

	अगर (cbs->ds_view.bi.ctx && !cbs->ds_view.bi.scrubbed)
		cmd->body.depthStencilViewId = cbs->ds_view.bi.res->id;
	अन्यथा
		cmd->body.depthStencilViewId = SVGA3D_INVALID_ID;

	स_नकल(&cmd[1], cbs->bind_cmd_buffer, view_id_size);

	vmw_cmd_commit(ctx->dev_priv, cmd_size);

	वापस 0;

पूर्ण

/**
 * vmw_collect_so_tarमाला_लो - Build SVGA3dSoTarget data क्रम a binding command
 * without checking which bindings actually need to be emitted
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 * @bi: Poपूर्णांकer to where the binding info array is stored in @cbs
 * @max_num: Maximum number of entries in the @bi array.
 *
 * Scans the @bi array क्रम bindings and builds a buffer of SVGA3dSoTarget data.
 * Stops at the first non-existing binding in the @bi array.
 * On output, @cbs->bind_cmd_count contains the number of bindings to be
 * emitted, @cbs->bind_first_slot is set to zero, and @cbs->bind_cmd_buffer
 * contains the command data.
 */
अटल व्योम vmw_collect_so_tarमाला_लो(काष्ठा vmw_ctx_binding_state *cbs,
				   स्थिर काष्ठा vmw_ctx_bindinfo *bi,
				   u32 max_num)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo_so_target *biso =
		container_of(bi, काष्ठा vmw_ctx_bindinfo_so_target, bi);
	अचिन्हित दीर्घ i;
	SVGA3dSoTarget *so_buffer = (SVGA3dSoTarget *) cbs->bind_cmd_buffer;

	cbs->bind_cmd_count = 0;
	cbs->bind_first_slot = 0;

	क्रम (i = 0; i < max_num; ++i, ++biso, ++so_buffer,
		    ++cbs->bind_cmd_count) अणु
		अगर (!biso->bi.ctx)
			अवरोध;

		अगर (!biso->bi.scrubbed) अणु
			so_buffer->sid = biso->bi.res->id;
			so_buffer->offset = biso->offset;
			so_buffer->sizeInBytes = biso->size;
		पूर्ण अन्यथा अणु
			so_buffer->sid = SVGA3D_INVALID_ID;
			so_buffer->offset = 0;
			so_buffer->sizeInBytes = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmw_emit_set_so_target - Issue delayed streamout binding commands
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 */
अटल पूर्णांक vmw_emit_set_so_target(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo *loc = &cbs->so_tarमाला_लो[0].bi;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetSOTarमाला_लो body;
	पूर्ण *cmd;
	माप_प्रकार cmd_size, so_target_size;
	स्थिर काष्ठा vmw_resource *ctx = vmw_cbs_context(cbs);

	vmw_collect_so_tarमाला_लो(cbs, loc, SVGA3D_DX_MAX_SOTARGETS);
	अगर (cbs->bind_cmd_count == 0)
		वापस 0;

	so_target_size = cbs->bind_cmd_count*माप(SVGA3dSoTarget);
	cmd_size = माप(*cmd) + so_target_size;
	cmd = VMW_CMD_CTX_RESERVE(ctx->dev_priv, cmd_size, ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_SOTARGETS;
	cmd->header.size = माप(cmd->body) + so_target_size;
	स_नकल(&cmd[1], cbs->bind_cmd_buffer, so_target_size);

	vmw_cmd_commit(ctx->dev_priv, cmd_size);

	वापस 0;

पूर्ण

/**
 * vmw_binding_emit_dirty_ps - Issue delayed per shader binding commands
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 *
 */
अटल पूर्णांक vmw_binding_emit_dirty_ps(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	काष्ठा vmw_dx_shader_bindings *sb = &cbs->per_shader[0];
	u32 i;
	पूर्णांक ret;

	क्रम (i = 0; i < SVGA3D_NUM_SHADERTYPE_DX10; ++i, ++sb) अणु
		अगर (!test_bit(VMW_BINDING_PS_SR_BIT, &sb->dirty))
			जारी;

		ret = vmw_emit_set_sr(cbs, i);
		अगर (ret)
			अवरोध;

		__clear_bit(VMW_BINDING_PS_SR_BIT, &sb->dirty);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_collect_dirty_vbs - Build SVGA3dVertexBuffer data क्रम a
 * SVGA3dCmdDXSetVertexBuffers command
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 * @bi: Poपूर्णांकer to where the binding info array is stored in @cbs
 * @dirty: Biपंचांगap indicating which bindings need to be emitted.
 * @max_num: Maximum number of entries in the @bi array.
 *
 * Scans the @bi array क्रम bindings that need to be emitted and
 * builds a buffer of SVGA3dVertexBuffer data.
 * On output, @cbs->bind_cmd_count contains the number of bindings to be
 * emitted, @cbs->bind_first_slot indicates the index of the first emitted
 * binding, and @cbs->bind_cmd_buffer contains the command data.
 */
अटल व्योम vmw_collect_dirty_vbs(काष्ठा vmw_ctx_binding_state *cbs,
				  स्थिर काष्ठा vmw_ctx_bindinfo *bi,
				  अचिन्हित दीर्घ *dirty,
				  u32 max_num)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo_vb *biv =
		container_of(bi, काष्ठा vmw_ctx_bindinfo_vb, bi);
	अचिन्हित दीर्घ i, next_bit;
	SVGA3dVertexBuffer *vbs = (SVGA3dVertexBuffer *) &cbs->bind_cmd_buffer;

	cbs->bind_cmd_count = 0;
	i = find_first_bit(dirty, max_num);
	next_bit = i;
	cbs->bind_first_slot = i;

	biv += i;
	क्रम (; i < max_num; ++i, ++biv, ++vbs) अणु
		अगर (!biv->bi.ctx || biv->bi.scrubbed) अणु
			vbs->sid = SVGA3D_INVALID_ID;
			vbs->stride = 0;
			vbs->offset = 0;
		पूर्ण अन्यथा अणु
			vbs->sid = biv->bi.res->id;
			vbs->stride = biv->stride;
			vbs->offset = biv->offset;
		पूर्ण
		cbs->bind_cmd_count++;
		अगर (next_bit == i) अणु
			next_bit = find_next_bit(dirty, max_num, i + 1);
			अगर (next_bit >= max_num)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmw_binding_emit_set_vb - Issue delayed vertex buffer binding commands
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 *
 */
अटल पूर्णांक vmw_emit_set_vb(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo *loc =
		&cbs->vertex_buffers[0].bi;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetVertexBuffers body;
	पूर्ण *cmd;
	माप_प्रकार cmd_size, set_vb_size;
	स्थिर काष्ठा vmw_resource *ctx = vmw_cbs_context(cbs);

	vmw_collect_dirty_vbs(cbs, loc, cbs->dirty_vb,
			     SVGA3D_DX_MAX_VERTEXBUFFERS);
	अगर (cbs->bind_cmd_count == 0)
		वापस 0;

	set_vb_size = cbs->bind_cmd_count*माप(SVGA3dVertexBuffer);
	cmd_size = माप(*cmd) + set_vb_size;
	cmd = VMW_CMD_CTX_RESERVE(ctx->dev_priv, cmd_size, ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS;
	cmd->header.size = माप(cmd->body) + set_vb_size;
	cmd->body.startBuffer = cbs->bind_first_slot;

	स_नकल(&cmd[1], cbs->bind_cmd_buffer, set_vb_size);

	vmw_cmd_commit(ctx->dev_priv, cmd_size);
	biपंचांगap_clear(cbs->dirty_vb,
		     cbs->bind_first_slot, cbs->bind_cmd_count);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_emit_set_uav(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo *loc = &cbs->ua_views[0].views[0].bi;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetUAViews body;
	पूर्ण *cmd;
	माप_प्रकार cmd_size, view_id_size;
	स्थिर काष्ठा vmw_resource *ctx = vmw_cbs_context(cbs);

	vmw_collect_view_ids(cbs, loc, SVGA3D_MAX_UAVIEWS);
	view_id_size = cbs->bind_cmd_count*माप(uपूर्णांक32);
	cmd_size = माप(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_RESERVE(ctx->dev_priv, cmd_size, ctx->id);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_UA_VIEWS;
	cmd->header.size = माप(cmd->body) + view_id_size;

	/* Splice index is specअगरied user-space   */
	cmd->body.uavSpliceIndex = cbs->ua_views[0].index;

	स_नकल(&cmd[1], cbs->bind_cmd_buffer, view_id_size);

	vmw_cmd_commit(ctx->dev_priv, cmd_size);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_emit_set_cs_uav(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	स्थिर काष्ठा vmw_ctx_bindinfo *loc = &cbs->ua_views[1].views[0].bi;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetCSUAViews body;
	पूर्ण *cmd;
	माप_प्रकार cmd_size, view_id_size;
	स्थिर काष्ठा vmw_resource *ctx = vmw_cbs_context(cbs);

	vmw_collect_view_ids(cbs, loc, SVGA3D_MAX_UAVIEWS);
	view_id_size = cbs->bind_cmd_count*माप(uपूर्णांक32);
	cmd_size = माप(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_RESERVE(ctx->dev_priv, cmd_size, ctx->id);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_CS_UA_VIEWS;
	cmd->header.size = माप(cmd->body) + view_id_size;

	/* Start index is specअगरied user-space */
	cmd->body.startIndex = cbs->ua_views[1].index;

	स_नकल(&cmd[1], cbs->bind_cmd_buffer, view_id_size);

	vmw_cmd_commit(ctx->dev_priv, cmd_size);

	वापस 0;
पूर्ण

/**
 * vmw_binding_emit_dirty - Issue delayed binding commands
 *
 * @cbs: Poपूर्णांकer to the context's काष्ठा vmw_ctx_binding_state
 *
 * This function issues the delayed binding commands that arise from
 * previous scrub / unscrub calls. These binding commands are typically
 * commands that batch a number of bindings and thereक्रमe it makes sense
 * to delay them.
 */
अटल पूर्णांक vmw_binding_emit_dirty(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ hit = 0;

	जबतक ((hit = find_next_bit(&cbs->dirty, VMW_BINDING_NUM_BITS, hit))
	      < VMW_BINDING_NUM_BITS) अणु

		चयन (hit) अणु
		हाल VMW_BINDING_RT_BIT:
			ret = vmw_emit_set_rt(cbs);
			अवरोध;
		हाल VMW_BINDING_PS_BIT:
			ret = vmw_binding_emit_dirty_ps(cbs);
			अवरोध;
		हाल VMW_BINDING_SO_T_BIT:
			ret = vmw_emit_set_so_target(cbs);
			अवरोध;
		हाल VMW_BINDING_VB_BIT:
			ret = vmw_emit_set_vb(cbs);
			अवरोध;
		हाल VMW_BINDING_UAV_BIT:
			ret = vmw_emit_set_uav(cbs);
			अवरोध;
		हाल VMW_BINDING_CS_UAV_BIT:
			ret = vmw_emit_set_cs_uav(cbs);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अगर (ret)
			वापस ret;

		__clear_bit(hit, &cbs->dirty);
		hit++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_sr - Schedule a dx shaderresource binding
 * scrub from a context
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_sr(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_view *biv =
		container_of(bi, काष्ठा vmw_ctx_bindinfo_view, bi);
	काष्ठा vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(biv->slot, cbs->per_shader[biv->shader_slot].dirty_sr);
	__set_bit(VMW_BINDING_PS_SR_BIT,
		  &cbs->per_shader[biv->shader_slot].dirty);
	__set_bit(VMW_BINDING_PS_BIT, &cbs->dirty);

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_dx_rt - Schedule a dx rendertarget binding
 * scrub from a context
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_dx_rt(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_RT_BIT, &cbs->dirty);

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_so_target - Schedule a dx streamoutput buffer binding
 * scrub from a context
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_so_target(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_SO_T_BIT, &cbs->dirty);

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_vb - Schedule a dx vertex buffer binding
 * scrub from a context
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_vb(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_vb *bivb =
		container_of(bi, काष्ठा vmw_ctx_bindinfo_vb, bi);
	काष्ठा vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(bivb->slot, cbs->dirty_vb);
	__set_bit(VMW_BINDING_VB_BIT, &cbs->dirty);

	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_ib - scrub a dx index buffer binding from a context
 *
 * @bi: single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_ib(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_ib *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetIndexBuffer body;
	पूर्ण *cmd;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), bi->ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_INDEX_BUFFER;
	cmd->header.size = माप(cmd->body);
	अगर (rebind) अणु
		cmd->body.sid = bi->res->id;
		cmd->body.क्रमmat = binding->क्रमmat;
		cmd->body.offset = binding->offset;
	पूर्ण अन्यथा अणु
		cmd->body.sid = SVGA3D_INVALID_ID;
		cmd->body.क्रमmat = 0;
		cmd->body.offset = 0;
	पूर्ण

	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_binding_scrub_uav(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_binding_state *cbs = vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_UAV_BIT, &cbs->dirty);
	वापस 0;
पूर्ण

अटल पूर्णांक vmw_binding_scrub_cs_uav(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_binding_state *cbs = vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_CS_UAV_BIT, &cbs->dirty);
	वापस 0;
पूर्ण

/**
 * vmw_binding_scrub_so - Scrub a streamoutput binding from context.
 * @bi: Single binding inक्रमmation.
 * @rebind: Whether to issue a bind instead of scrub command.
 */
अटल पूर्णांक vmw_binding_scrub_so(काष्ठा vmw_ctx_bindinfo *bi, bool rebind)
अणु
	काष्ठा vmw_ctx_bindinfo_so *binding =
		container_of(bi, typeof(*binding), bi);
	काष्ठा vmw_निजी *dev_priv = bi->ctx->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetStreamOutput body;
	पूर्ण *cmd;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), bi->ctx->id);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_DX_SET_STREAMOUTPUT;
	cmd->header.size = माप(cmd->body);
	cmd->body.soid = rebind ? bi->res->id : SVGA3D_INVALID_ID;
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_binding_state_alloc - Allocate a काष्ठा vmw_ctx_binding_state with
 * memory accounting.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 *
 * Returns a poपूर्णांकer to a newly allocated काष्ठा or an error poपूर्णांकer on error.
 */
काष्ठा vmw_ctx_binding_state *
vmw_binding_state_alloc(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_ctx_binding_state *cbs;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv), माप(*cbs),
				&ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	cbs = vzalloc(माप(*cbs));
	अगर (!cbs) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), माप(*cbs));
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	cbs->dev_priv = dev_priv;
	INIT_LIST_HEAD(&cbs->list);

	वापस cbs;
पूर्ण

/**
 * vmw_binding_state_मुक्त - Free a काष्ठा vmw_ctx_binding_state and its
 * memory accounting info.
 *
 * @cbs: Poपूर्णांकer to the काष्ठा vmw_ctx_binding_state to be मुक्तd.
 */
व्योम vmw_binding_state_मुक्त(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	काष्ठा vmw_निजी *dev_priv = cbs->dev_priv;

	vमुक्त(cbs);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), माप(*cbs));
पूर्ण

/**
 * vmw_binding_state_list - Get the binding list of a
 * काष्ठा vmw_ctx_binding_state
 *
 * @cbs: Poपूर्णांकer to the काष्ठा vmw_ctx_binding_state
 *
 * Returns the binding list which can be used to traverse through the bindings
 * and access the resource inक्रमmation of all bindings.
 */
काष्ठा list_head *vmw_binding_state_list(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	वापस &cbs->list;
पूर्ण

/**
 * vmwgfx_binding_state_reset - clear a काष्ठा vmw_ctx_binding_state
 *
 * @cbs: Poपूर्णांकer to the काष्ठा vmw_ctx_binding_state to be cleared
 *
 * Drops all bindings रेजिस्टरed in @cbs. No device binding actions are
 * perक्रमmed.
 */
व्योम vmw_binding_state_reset(काष्ठा vmw_ctx_binding_state *cbs)
अणु
	काष्ठा vmw_ctx_bindinfo *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &cbs->list, ctx_list)
		vmw_binding_drop(entry);
पूर्ण

/**
 * vmw_binding_dirtying - Return whether a binding type is dirtying its resource
 * @binding_type: The binding type
 *
 * Each समय a resource is put on the validation list as the result of a
 * context binding referencing it, we need to determine whether that resource
 * will be dirtied (written to by the GPU) as a result of the corresponding
 * GPU operation. Currently rendertarget-, depth-stencil-, stream-output-target
 * and unordered access view bindings are capable of dirtying its resource.
 *
 * Return: Whether the binding type dirties the resource its binding poपूर्णांकs to.
 */
u32 vmw_binding_dirtying(क्रमागत vmw_ctx_binding_type binding_type)
अणु
	अटल u32 is_binding_dirtying[vmw_ctx_binding_max] = अणु
		[vmw_ctx_binding_rt] = VMW_RES_सूचीTY_SET,
		[vmw_ctx_binding_dx_rt] = VMW_RES_सूचीTY_SET,
		[vmw_ctx_binding_ds] = VMW_RES_सूचीTY_SET,
		[vmw_ctx_binding_so_target] = VMW_RES_सूचीTY_SET,
		[vmw_ctx_binding_uav] = VMW_RES_सूचीTY_SET,
		[vmw_ctx_binding_cs_uav] = VMW_RES_सूचीTY_SET,
	पूर्ण;

	/* Review this function as new bindings are added. */
	BUILD_BUG_ON(vmw_ctx_binding_max != 14);
	वापस is_binding_dirtying[binding_type];
पूर्ण

/*
 * This function is unused at run-समय, and only used to hold various build
 * निश्चितs important क्रम code optimization assumptions.
 */
अटल व्योम vmw_binding_build_निश्चितs(व्योम)
अणु
	BUILD_BUG_ON(SVGA3D_NUM_SHADERTYPE_DX10 != 3);
	BUILD_BUG_ON(SVGA3D_MAX_SIMULTANEOUS_RENDER_TARGETS > SVGA3D_RT_MAX);
	BUILD_BUG_ON(माप(uपूर्णांक32) != माप(u32));

	/*
	 * काष्ठा vmw_ctx_binding_state::bind_cmd_buffer is used क्रम various
	 * view id arrays.
	 */
	BUILD_BUG_ON(VMW_MAX_VIEW_BINDINGS < SVGA3D_RT_MAX);
	BUILD_BUG_ON(VMW_MAX_VIEW_BINDINGS < SVGA3D_DX_MAX_SRVIEWS);
	BUILD_BUG_ON(VMW_MAX_VIEW_BINDINGS < SVGA3D_DX_MAX_CONSTBUFFERS);

	/*
	 * काष्ठा vmw_ctx_binding_state::bind_cmd_buffer is used क्रम
	 * u32 view ids, SVGA3dSoTarमाला_लो and SVGA3dVertexBuffers
	 */
	BUILD_BUG_ON(SVGA3D_DX_MAX_SOTARGETS*माप(SVGA3dSoTarget) >
		     VMW_MAX_VIEW_BINDINGS*माप(u32));
	BUILD_BUG_ON(SVGA3D_DX_MAX_VERTEXBUFFERS*माप(SVGA3dVertexBuffer) >
		     VMW_MAX_VIEW_BINDINGS*माप(u32));
पूर्ण
