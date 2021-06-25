<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
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
#अगर_अघोषित VMW_SO_H
#घोषणा VMW_SO_H

क्रमागत vmw_view_type अणु
	vmw_view_sr,
	vmw_view_rt,
	vmw_view_ds,
	vmw_view_ua,
	vmw_view_max,
पूर्ण;

क्रमागत vmw_so_type अणु
	vmw_so_el,
	vmw_so_bs,
	vmw_so_ds,
	vmw_so_rs,
	vmw_so_ss,
	vmw_so_so,
	vmw_so_max,
पूर्ण;

/**
 * जोड़ vmw_view_destroy - view deकाष्ठाion command body
 *
 * @rtv: RenderTarget view deकाष्ठाion command body
 * @srv: ShaderResource view deकाष्ठाion command body
 * @dsv: DepthStencil view deकाष्ठाion command body
 * @view_id: A single u32 view id.
 *
 * The assumption here is that all जोड़ members are really represented by a
 * single u32 in the command stream. If that's not the हाल,
 * the size of this जोड़ will not equal the size of an u32, and the
 * assumption is invalid, and we detect that at compile समय in the
 * vmw_so_build_निश्चितs() function.
 */
जोड़ vmw_view_destroy अणु
	काष्ठा SVGA3dCmdDXDestroyRenderTargetView rtv;
	काष्ठा SVGA3dCmdDXDestroyShaderResourceView srv;
	काष्ठा SVGA3dCmdDXDestroyDepthStencilView dsv;
	काष्ठा SVGA3dCmdDXDestroyUAView uav;
	u32 view_id;
पूर्ण;

/* Map क्रमागत vmw_view_type to view destroy command ids*/
बाह्य स्थिर u32 vmw_view_destroy_cmds[];

/* Map क्रमागत vmw_view_type to SVGACOTableType */
बाह्य स्थिर SVGACOTableType vmw_view_cotables[];

/* Map क्रमागत vmw_so_type to SVGACOTableType */
बाह्य स्थिर SVGACOTableType vmw_so_cotables[];

/*
 * vmw_view_cmd_to_type - Return the view type क्रम a create or destroy command
 *
 * @id: The SVGA3D command id.
 *
 * For a given view create or destroy command id, वापस the corresponding
 * क्रमागत vmw_view_type. If the command is unknown, वापस vmw_view_max.
 * The validity of the simplअगरied calculation is verअगरied in the
 * vmw_so_build_निश्चितs() function.
 */
अटल अंतरभूत क्रमागत vmw_view_type vmw_view_cmd_to_type(u32 id)
अणु
	u32 पंचांगp = (id - SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW) / 2;

	अगर (id == SVGA_3D_CMD_DX_DEFINE_UA_VIEW ||
	    id == SVGA_3D_CMD_DX_DESTROY_UA_VIEW)
		वापस vmw_view_ua;

	अगर (पंचांगp > (u32)vmw_view_max)
		वापस vmw_view_max;

	वापस (क्रमागत vmw_view_type) पंचांगp;
पूर्ण

/*
 * vmw_so_cmd_to_type - Return the state object type क्रम a
 * create or destroy command
 *
 * @id: The SVGA3D command id.
 *
 * For a given state object create or destroy command id,
 * वापस the corresponding क्रमागत vmw_so_type. If the command is uknown,
 * वापस vmw_so_max. We should perhaps optimize this function using
 * a similar strategy as vmw_view_cmd_to_type().
 */
अटल अंतरभूत क्रमागत vmw_so_type vmw_so_cmd_to_type(u32 id)
अणु
	चयन (id) अणु
	हाल SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT:
	हाल SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT:
		वापस vmw_so_el;
	हाल SVGA_3D_CMD_DX_DEFINE_BLEND_STATE:
	हाल SVGA_3D_CMD_DX_DESTROY_BLEND_STATE:
		वापस vmw_so_bs;
	हाल SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE:
	हाल SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE:
		वापस vmw_so_ds;
	हाल SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE:
	हाल SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE:
		वापस vmw_so_rs;
	हाल SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE:
	हाल SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE:
		वापस vmw_so_ss;
	हाल SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT:
	हाल SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT_WITH_MOB:
	हाल SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT:
		वापस vmw_so_so;
	शेष:
		अवरोध;
	पूर्ण
	वापस vmw_so_max;
पूर्ण

/*
 * View management - vmwgfx_so.c
 */
बाह्य पूर्णांक vmw_view_add(काष्ठा vmw_cmdbuf_res_manager *man,
			काष्ठा vmw_resource *ctx,
			काष्ठा vmw_resource *srf,
			क्रमागत vmw_view_type view_type,
			u32 user_key,
			स्थिर व्योम *cmd,
			माप_प्रकार cmd_size,
			काष्ठा list_head *list);

बाह्य पूर्णांक vmw_view_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
			   u32 user_key, क्रमागत vmw_view_type view_type,
			   काष्ठा list_head *list,
			   काष्ठा vmw_resource **res_p);

बाह्य व्योम vmw_view_surface_list_destroy(काष्ठा vmw_निजी *dev_priv,
					  काष्ठा list_head *view_list);
बाह्य व्योम vmw_view_cotable_list_destroy(काष्ठा vmw_निजी *dev_priv,
					  काष्ठा list_head *list,
					  bool पढ़ोback);
बाह्य काष्ठा vmw_resource *vmw_view_srf(काष्ठा vmw_resource *res);
बाह्य काष्ठा vmw_resource *vmw_view_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
					    क्रमागत vmw_view_type view_type,
					    u32 user_key);
बाह्य u32 vmw_view_dirtying(काष्ठा vmw_resource *res);
#पूर्ण_अगर
