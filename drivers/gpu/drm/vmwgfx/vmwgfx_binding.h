<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
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
#अगर_अघोषित _VMWGFX_BINDING_H_
#घोषणा _VMWGFX_BINDING_H_

#समावेश <linux/list.h>

#समावेश "device_include/svga3d_reg.h"

#घोषणा VMW_MAX_VIEW_BINDINGS 128

#घोषणा VMW_MAX_UAV_BIND_TYPE 2

काष्ठा vmw_निजी;
काष्ठा vmw_ctx_binding_state;

/*
 * क्रमागत vmw_ctx_binding_type - असलtract resource to context binding types
 */
क्रमागत vmw_ctx_binding_type अणु
	vmw_ctx_binding_shader,
	vmw_ctx_binding_rt,
	vmw_ctx_binding_tex,
	vmw_ctx_binding_cb,
	vmw_ctx_binding_dx_shader,
	vmw_ctx_binding_dx_rt,
	vmw_ctx_binding_sr,
	vmw_ctx_binding_ds,
	vmw_ctx_binding_so_target,
	vmw_ctx_binding_vb,
	vmw_ctx_binding_ib,
	vmw_ctx_binding_uav,
	vmw_ctx_binding_cs_uav,
	vmw_ctx_binding_so,
	vmw_ctx_binding_max
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo - single binding metadata
 *
 * @ctx_list: List head क्रम the context's list of bindings.
 * @res_list: List head क्रम a resource's list of bindings.
 * @ctx: Non-refcounted poपूर्णांकer to the context that owns the binding. शून्य
 * indicates no binding present.
 * @res: Non-refcounted poपूर्णांकer to the resource the binding poपूर्णांकs to. This
 * is typically a surface or a view.
 * @bt: Binding type.
 * @scrubbed: Whether the binding has been scrubbed from the context.
 */
काष्ठा vmw_ctx_bindinfo अणु
	काष्ठा list_head ctx_list;
	काष्ठा list_head res_list;
	काष्ठा vmw_resource *ctx;
	काष्ठा vmw_resource *res;
	क्रमागत vmw_ctx_binding_type bt;
	bool scrubbed;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_tex - texture stage binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @texture_stage: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_tex अणु
	काष्ठा vmw_ctx_bindinfo bi;
	uपूर्णांक32 texture_stage;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_shader - Shader binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @shader_slot: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_shader अणु
	काष्ठा vmw_ctx_bindinfo bi;
	SVGA3dShaderType shader_slot;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_cb - Constant buffer binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @shader_slot: Device data used to reस्थिरruct binding command.
 * @offset: Device data used to reस्थिरruct binding command.
 * @size: Device data used to reस्थिरruct binding command.
 * @slot: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_cb अणु
	काष्ठा vmw_ctx_bindinfo bi;
	SVGA3dShaderType shader_slot;
	uपूर्णांक32 offset;
	uपूर्णांक32 size;
	uपूर्णांक32 slot;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_view - View binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @shader_slot: Device data used to reस्थिरruct binding command.
 * @slot: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_view अणु
	काष्ठा vmw_ctx_bindinfo bi;
	SVGA3dShaderType shader_slot;
	uपूर्णांक32 slot;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_so_target - StreamOutput binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @offset: Device data used to reस्थिरruct binding command.
 * @size: Device data used to reस्थिरruct binding command.
 * @slot: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_so_target अणु
	काष्ठा vmw_ctx_bindinfo bi;
	uपूर्णांक32 offset;
	uपूर्णांक32 size;
	uपूर्णांक32 slot;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_vb - Vertex buffer binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @offset: Device data used to reस्थिरruct binding command.
 * @stride: Device data used to reस्थिरruct binding command.
 * @slot: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_vb अणु
	काष्ठा vmw_ctx_bindinfo bi;
	uपूर्णांक32 offset;
	uपूर्णांक32 stride;
	uपूर्णांक32 slot;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_ib - StreamOutput binding metadata
 *
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @offset: Device data used to reस्थिरruct binding command.
 * @क्रमmat: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_ib अणु
	काष्ठा vmw_ctx_bindinfo bi;
	uपूर्णांक32 offset;
	uपूर्णांक32 क्रमmat;
पूर्ण;

/**
 * काष्ठा vmw_dx_shader_bindings - per shader type context binding state
 *
 * @shader: The shader binding क्रम this shader type
 * @स्थिर_buffer: Const buffer bindings क्रम this shader type.
 * @shader_res: Shader resource view bindings क्रम this shader type.
 * @dirty_sr: Biपंचांगap tracking inभागidual shader resource bindings changes
 * that have not yet been emitted to the device.
 * @dirty: Biपंचांगap tracking per-binding type binding changes that have not
 * yet been emitted to the device.
 */
काष्ठा vmw_dx_shader_bindings अणु
	काष्ठा vmw_ctx_bindinfo_shader shader;
	काष्ठा vmw_ctx_bindinfo_cb स्थिर_buffers[SVGA3D_DX_MAX_CONSTBUFFERS];
	काष्ठा vmw_ctx_bindinfo_view shader_res[SVGA3D_DX_MAX_SRVIEWS];
	DECLARE_BITMAP(dirty_sr, SVGA3D_DX_MAX_SRVIEWS);
	अचिन्हित दीर्घ dirty;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_uav - UAV context binding state.
 * @views: UAV view bindings.
 * @splice_index: The device splice index set by user-space.
 */
काष्ठा vmw_ctx_bindinfo_uav अणु
	काष्ठा vmw_ctx_bindinfo_view views[SVGA3D_MAX_UAVIEWS];
	uपूर्णांक32 index;
पूर्ण;

/**
 * काष्ठा vmw_ctx_bindinfo_so - Stream output binding metadata.
 * @bi: काष्ठा vmw_ctx_bindinfo we derive from.
 * @slot: Device data used to reस्थिरruct binding command.
 */
काष्ठा vmw_ctx_bindinfo_so अणु
	काष्ठा vmw_ctx_bindinfo bi;
	uपूर्णांक32 slot;
पूर्ण;

बाह्य व्योम vmw_binding_add(काष्ठा vmw_ctx_binding_state *cbs,
			    स्थिर काष्ठा vmw_ctx_bindinfo *ci,
			    u32 shader_slot, u32 slot);
बाह्य व्योम vmw_binding_add_uav_index(काष्ठा vmw_ctx_binding_state *cbs,
				      uपूर्णांक32 slot, uपूर्णांक32 splice_index);
बाह्य व्योम
vmw_binding_state_commit(काष्ठा vmw_ctx_binding_state *to,
			 काष्ठा vmw_ctx_binding_state *from);
बाह्य व्योम vmw_binding_res_list_समाप्त(काष्ठा list_head *head);
बाह्य व्योम vmw_binding_res_list_scrub(काष्ठा list_head *head);
बाह्य पूर्णांक vmw_binding_rebind_all(काष्ठा vmw_ctx_binding_state *cbs);
बाह्य व्योम vmw_binding_state_समाप्त(काष्ठा vmw_ctx_binding_state *cbs);
बाह्य व्योम vmw_binding_state_scrub(काष्ठा vmw_ctx_binding_state *cbs);
बाह्य काष्ठा vmw_ctx_binding_state *
vmw_binding_state_alloc(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_binding_state_मुक्त(काष्ठा vmw_ctx_binding_state *cbs);
बाह्य काष्ठा list_head *
vmw_binding_state_list(काष्ठा vmw_ctx_binding_state *cbs);
बाह्य व्योम vmw_binding_state_reset(काष्ठा vmw_ctx_binding_state *cbs);
बाह्य u32 vmw_binding_dirtying(क्रमागत vmw_ctx_binding_type binding_type);


#पूर्ण_अगर
