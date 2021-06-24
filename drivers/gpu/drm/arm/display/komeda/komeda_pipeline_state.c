<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <linux/clk.h>
#समावेश "komeda_dev.h"
#समावेश "komeda_kms.h"
#समावेश "komeda_pipeline.h"
#समावेश "komeda_framebuffer.h"

अटल अंतरभूत bool is_चयनing_user(व्योम *old, व्योम *new)
अणु
	अगर (!old || !new)
		वापस false;

	वापस old != new;
पूर्ण

अटल काष्ठा komeda_pipeline_state *
komeda_pipeline_get_state(काष्ठा komeda_pipeline *pipe,
			  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_निजी_state *priv_st;

	priv_st = drm_atomic_get_निजी_obj_state(state, &pipe->obj);
	अगर (IS_ERR(priv_st))
		वापस ERR_CAST(priv_st);

	वापस priv_to_pipe_st(priv_st);
पूर्ण

काष्ठा komeda_pipeline_state *
komeda_pipeline_get_old_state(काष्ठा komeda_pipeline *pipe,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_निजी_state *priv_st;

	priv_st = drm_atomic_get_old_निजी_obj_state(state, &pipe->obj);
	अगर (priv_st)
		वापस priv_to_pipe_st(priv_st);
	वापस शून्य;
पूर्ण

अटल काष्ठा komeda_pipeline_state *
komeda_pipeline_get_new_state(काष्ठा komeda_pipeline *pipe,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_निजी_state *priv_st;

	priv_st = drm_atomic_get_new_निजी_obj_state(state, &pipe->obj);
	अगर (priv_st)
		वापस priv_to_pipe_st(priv_st);
	वापस शून्य;
पूर्ण

/* Assign pipeline क्रम crtc */
अटल काष्ठा komeda_pipeline_state *
komeda_pipeline_get_state_and_set_crtc(काष्ठा komeda_pipeline *pipe,
				       काष्ठा drm_atomic_state *state,
				       काष्ठा drm_crtc *crtc)
अणु
	काष्ठा komeda_pipeline_state *st;

	st = komeda_pipeline_get_state(pipe, state);
	अगर (IS_ERR(st))
		वापस st;

	अगर (is_चयनing_user(crtc, st->crtc)) अणु
		DRM_DEBUG_ATOMIC("CRTC%d required pipeline%d is busy.\n",
				 drm_crtc_index(crtc), pipe->id);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	/* pipeline only can be disabled when the it is मुक्त or unused */
	अगर (!crtc && st->active_comps) अणु
		DRM_DEBUG_ATOMIC("Disabling a busy pipeline:%d.\n", pipe->id);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	st->crtc = crtc;

	अगर (crtc) अणु
		काष्ठा komeda_crtc_state *kcrtc_st;

		kcrtc_st = to_kcrtc_st(drm_atomic_get_new_crtc_state(state,
								     crtc));

		kcrtc_st->active_pipes |= BIT(pipe->id);
		kcrtc_st->affected_pipes |= BIT(pipe->id);
	पूर्ण
	वापस st;
पूर्ण

अटल काष्ठा komeda_component_state *
komeda_component_get_state(काष्ठा komeda_component *c,
			   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_निजी_state *priv_st;

	WARN_ON(!drm_modeset_is_locked(&c->pipeline->obj.lock));

	priv_st = drm_atomic_get_निजी_obj_state(state, &c->obj);
	अगर (IS_ERR(priv_st))
		वापस ERR_CAST(priv_st);

	वापस priv_to_comp_st(priv_st);
पूर्ण

अटल काष्ठा komeda_component_state *
komeda_component_get_old_state(काष्ठा komeda_component *c,
			       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_निजी_state *priv_st;

	priv_st = drm_atomic_get_old_निजी_obj_state(state, &c->obj);
	अगर (priv_st)
		वापस priv_to_comp_st(priv_st);
	वापस शून्य;
पूर्ण

/**
 * komeda_component_get_state_and_set_user()
 *
 * @c: component to get state and set user
 * @state: global atomic state
 * @user: direct user, the binding user
 * @crtc: the CRTC user, the big boss :)
 *
 * This function accepts two users:
 * -   The direct user: can be plane/crtc/wb_connector depends on component
 * -   The big boss (CRTC)
 * CRTC is the big boss (the final user), because all component resources
 * eventually will be asचिन्हित to CRTC, like the layer will be binding to
 * kms_plane, but kms plane will be binding to a CRTC eventually.
 *
 * The big boss (CRTC) is क्रम pipeline assignment, since &komeda_component isn't
 * independent and can be asचिन्हित to CRTC मुक्तly, but beदीर्घs to a specअगरic
 * pipeline, only pipeline can be shared between crtc, and pipeline as a whole
 * (include all the पूर्णांकernal components) asचिन्हित to a specअगरic CRTC.
 *
 * So when set a user to komeda_component, need first to check the status of
 * component->pipeline to see अगर the pipeline is available on this specअगरic
 * CRTC. अगर the pipeline is busy (asचिन्हित to another CRTC), even the required
 * component is मुक्त, the component still cannot be asचिन्हित to the direct user.
 */
अटल काष्ठा komeda_component_state *
komeda_component_get_state_and_set_user(काष्ठा komeda_component *c,
					काष्ठा drm_atomic_state *state,
					व्योम *user,
					काष्ठा drm_crtc *crtc)
अणु
	काष्ठा komeda_pipeline_state *pipe_st;
	काष्ठा komeda_component_state *st;

	/* First check अगर the pipeline is available */
	pipe_st = komeda_pipeline_get_state_and_set_crtc(c->pipeline,
							 state, crtc);
	अगर (IS_ERR(pipe_st))
		वापस ERR_CAST(pipe_st);

	st = komeda_component_get_state(c, state);
	अगर (IS_ERR(st))
		वापस st;

	/* check अगर the component has been occupied */
	अगर (is_चयनing_user(user, st->binding_user)) अणु
		DRM_DEBUG_ATOMIC("required %s is busy.\n", c->name);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	st->binding_user = user;
	/* mark the component as active अगर user is valid */
	अगर (st->binding_user)
		pipe_st->active_comps |= BIT(c->id);

	वापस st;
पूर्ण

अटल व्योम
komeda_component_add_input(काष्ठा komeda_component_state *state,
			   काष्ठा komeda_component_output *input,
			   पूर्णांक idx)
अणु
	काष्ठा komeda_component *c = state->component;

	WARN_ON((idx < 0 || idx >= c->max_active_inमाला_दो));

	/* since the inमाला_दो[i] is only valid when it is active. So अगर a input[i]
	 * is a newly enabled input which चयनes from disable to enable, then
	 * the old inमाला_दो[i] is undefined (NOT zeroed), we can not rely on
	 * स_भेद, but directly mark it changed
	 */
	अगर (!has_bit(idx, state->affected_inमाला_दो) ||
	    स_भेद(&state->inमाला_दो[idx], input, माप(*input))) अणु
		स_नकल(&state->inमाला_दो[idx], input, माप(*input));
		state->changed_active_inमाला_दो |= BIT(idx);
	पूर्ण
	state->active_inमाला_दो |= BIT(idx);
	state->affected_inमाला_दो |= BIT(idx);
पूर्ण

अटल पूर्णांक
komeda_component_check_input(काष्ठा komeda_component_state *state,
			     काष्ठा komeda_component_output *input,
			     पूर्णांक idx)
अणु
	काष्ठा komeda_component *c = state->component;

	अगर ((idx < 0) || (idx >= c->max_active_inमाला_दो)) अणु
		DRM_DEBUG_ATOMIC("%s required an invalid %s-input[%d].\n",
				 input->component->name, c->name, idx);
		वापस -EINVAL;
	पूर्ण

	अगर (has_bit(idx, state->active_inमाला_दो)) अणु
		DRM_DEBUG_ATOMIC("%s required %s-input[%d] has been occupied already.\n",
				 input->component->name, c->name, idx);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
komeda_component_set_output(काष्ठा komeda_component_output *output,
			    काष्ठा komeda_component *comp,
			    u8 output_port)
अणु
	output->component = comp;
	output->output_port = output_port;
पूर्ण

अटल पूर्णांक
komeda_component_validate_निजी(काष्ठा komeda_component *c,
				  काष्ठा komeda_component_state *st)
अणु
	पूर्णांक err;

	अगर (!c->funcs->validate)
		वापस 0;

	err = c->funcs->validate(c, st);
	अगर (err)
		DRM_DEBUG_ATOMIC("%s validate private failed.\n", c->name);

	वापस err;
पूर्ण

/* Get current available scaler from the component->supported_outमाला_दो */
अटल काष्ठा komeda_scaler *
komeda_component_get_avail_scaler(काष्ठा komeda_component *c,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा komeda_pipeline_state *pipe_st;
	u32 avail_scalers;

	pipe_st = komeda_pipeline_get_state(c->pipeline, state);
	अगर (!pipe_st)
		वापस शून्य;

	avail_scalers = (pipe_st->active_comps & KOMEDA_PIPELINE_SCALERS) ^
			KOMEDA_PIPELINE_SCALERS;

	c = komeda_component_pickup_output(c, avail_scalers);

	वापस to_scaler(c);
पूर्ण

अटल व्योम
komeda_rotate_data_flow(काष्ठा komeda_data_flow_cfg *dflow, u32 rot)
अणु
	अगर (drm_rotation_90_or_270(rot)) अणु
		swap(dflow->in_h, dflow->in_w);
		swap(dflow->total_in_h, dflow->total_in_w);
	पूर्ण
पूर्ण

अटल पूर्णांक
komeda_layer_check_cfg(काष्ठा komeda_layer *layer,
		       काष्ठा komeda_fb *kfb,
		       काष्ठा komeda_data_flow_cfg *dflow)
अणु
	u32 src_x, src_y, src_w, src_h;
	u32 line_sz, max_line_sz;

	अगर (!komeda_fb_is_layer_supported(kfb, layer->layer_type, dflow->rot))
		वापस -EINVAL;

	अगर (layer->base.id == KOMEDA_COMPONENT_WB_LAYER) अणु
		src_x = dflow->out_x;
		src_y = dflow->out_y;
		src_w = dflow->out_w;
		src_h = dflow->out_h;
	पूर्ण अन्यथा अणु
		src_x = dflow->in_x;
		src_y = dflow->in_y;
		src_w = dflow->in_w;
		src_h = dflow->in_h;
	पूर्ण

	अगर (komeda_fb_check_src_coords(kfb, src_x, src_y, src_w, src_h))
		वापस -EINVAL;

	अगर (!in_range(&layer->hsize_in, src_w)) अणु
		DRM_DEBUG_ATOMIC("invalidate src_w %d.\n", src_w);
		वापस -EINVAL;
	पूर्ण

	अगर (!in_range(&layer->vsize_in, src_h)) अणु
		DRM_DEBUG_ATOMIC("invalidate src_h %d.\n", src_h);
		वापस -EINVAL;
	पूर्ण

	अगर (drm_rotation_90_or_270(dflow->rot))
		line_sz = dflow->in_h;
	अन्यथा
		line_sz = dflow->in_w;

	अगर (kfb->base.क्रमmat->hsub > 1)
		max_line_sz = layer->yuv_line_sz;
	अन्यथा
		max_line_sz = layer->line_sz;

	अगर (line_sz > max_line_sz) अणु
		DRM_DEBUG_ATOMIC("Required line_sz: %d exceeds the max size %d\n",
				 line_sz, max_line_sz);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_layer_validate(काष्ठा komeda_layer *layer,
		      काष्ठा komeda_plane_state *kplane_st,
		      काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_plane_state *plane_st = &kplane_st->base;
	काष्ठा drm_framebuffer *fb = plane_st->fb;
	काष्ठा komeda_fb *kfb = to_kfb(fb);
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_layer_state *st;
	पूर्णांक i, err;

	err = komeda_layer_check_cfg(layer, kfb, dflow);
	अगर (err)
		वापस err;

	c_st = komeda_component_get_state_and_set_user(&layer->base,
			plane_st->state, plane_st->plane, plane_st->crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_layer_st(c_st);

	st->rot = dflow->rot;

	अगर (fb->modअगरier) अणु
		st->hsize = kfb->aligned_w;
		st->vsize = kfb->aligned_h;
		st->afbc_crop_l = dflow->in_x;
		st->afbc_crop_r = kfb->aligned_w - dflow->in_x - dflow->in_w;
		st->afbc_crop_t = dflow->in_y;
		st->afbc_crop_b = kfb->aligned_h - dflow->in_y - dflow->in_h;
	पूर्ण अन्यथा अणु
		st->hsize = dflow->in_w;
		st->vsize = dflow->in_h;
		st->afbc_crop_l = 0;
		st->afbc_crop_r = 0;
		st->afbc_crop_t = 0;
		st->afbc_crop_b = 0;
	पूर्ण

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++)
		st->addr[i] = komeda_fb_get_pixel_addr(kfb, dflow->in_x,
						       dflow->in_y, i);

	err = komeda_component_validate_निजी(&layer->base, c_st);
	अगर (err)
		वापस err;

	/* update the data flow क्रम the next stage */
	komeda_component_set_output(&dflow->input, &layer->base, 0);

	/*
	 * The rotation has been handled by layer, so adjusted the data flow क्रम
	 * the next stage.
	 */
	komeda_rotate_data_flow(dflow, st->rot);

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_wb_layer_validate(काष्ठा komeda_layer *wb_layer,
			 काष्ठा drm_connector_state *conn_st,
			 काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा komeda_fb *kfb = to_kfb(conn_st->ग_लिखोback_job->fb);
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_layer_state *st;
	पूर्णांक i, err;

	err = komeda_layer_check_cfg(wb_layer, kfb, dflow);
	अगर (err)
		वापस err;

	c_st = komeda_component_get_state_and_set_user(&wb_layer->base,
			conn_st->state, conn_st->connector, conn_st->crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_layer_st(c_st);

	st->hsize = dflow->out_w;
	st->vsize = dflow->out_h;

	क्रम (i = 0; i < kfb->base.क्रमmat->num_planes; i++)
		st->addr[i] = komeda_fb_get_pixel_addr(kfb, dflow->out_x,
						       dflow->out_y, i);

	komeda_component_add_input(&st->base, &dflow->input, 0);
	komeda_component_set_output(&dflow->input, &wb_layer->base, 0);

	वापस 0;
पूर्ण

अटल bool scaling_ratio_valid(u32 size_in, u32 size_out,
				u32 max_upscaling, u32 max_करोwnscaling)
अणु
	अगर (size_out > size_in * max_upscaling)
		वापस false;
	अन्यथा अगर (size_in > size_out * max_करोwnscaling)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक
komeda_scaler_check_cfg(काष्ठा komeda_scaler *scaler,
			काष्ठा komeda_crtc_state *kcrtc_st,
			काष्ठा komeda_data_flow_cfg *dflow)
अणु
	u32 hsize_in, vsize_in, hsize_out, vsize_out;
	u32 max_upscaling;

	hsize_in = dflow->in_w;
	vsize_in = dflow->in_h;
	hsize_out = dflow->out_w;
	vsize_out = dflow->out_h;

	अगर (!in_range(&scaler->hsize, hsize_in) ||
	    !in_range(&scaler->hsize, hsize_out)) अणु
		DRM_DEBUG_ATOMIC("Invalid horizontal sizes");
		वापस -EINVAL;
	पूर्ण

	अगर (!in_range(&scaler->vsize, vsize_in) ||
	    !in_range(&scaler->vsize, vsize_out)) अणु
		DRM_DEBUG_ATOMIC("Invalid vertical sizes");
		वापस -EINVAL;
	पूर्ण

	/* If input comes from compiz that means the scaling is क्रम ग_लिखोback
	 * and scaler can not करो upscaling क्रम ग_लिखोback
	 */
	अगर (has_bit(dflow->input.component->id, KOMEDA_PIPELINE_COMPIZS))
		max_upscaling = 1;
	अन्यथा
		max_upscaling = scaler->max_upscaling;

	अगर (!scaling_ratio_valid(hsize_in, hsize_out, max_upscaling,
				 scaler->max_करोwnscaling)) अणु
		DRM_DEBUG_ATOMIC("Invalid horizontal scaling ratio");
		वापस -EINVAL;
	पूर्ण

	अगर (!scaling_ratio_valid(vsize_in, vsize_out, max_upscaling,
				 scaler->max_करोwnscaling)) अणु
		DRM_DEBUG_ATOMIC("Invalid vertical scaling ratio");
		वापस -EINVAL;
	पूर्ण

	अगर (hsize_in > hsize_out || vsize_in > vsize_out) अणु
		काष्ठा komeda_pipeline *pipe = scaler->base.pipeline;
		पूर्णांक err;

		err = pipe->funcs->करोwnscaling_clk_check(pipe,
					&kcrtc_st->base.adjusted_mode,
					komeda_crtc_get_aclk(kcrtc_st), dflow);
		अगर (err) अणु
			DRM_DEBUG_ATOMIC("aclk can't satisfy the clock requirement of the downscaling\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_scaler_validate(व्योम *user,
		       काष्ठा komeda_crtc_state *kcrtc_st,
		       काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_atomic_state *drm_st = kcrtc_st->base.state;
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_scaler_state *st;
	काष्ठा komeda_scaler *scaler;
	पूर्णांक err = 0;

	अगर (!(dflow->en_scaling || dflow->en_img_enhancement))
		वापस 0;

	scaler = komeda_component_get_avail_scaler(dflow->input.component,
						   drm_st);
	अगर (!scaler) अणु
		DRM_DEBUG_ATOMIC("No scaler available");
		वापस -EINVAL;
	पूर्ण

	err = komeda_scaler_check_cfg(scaler, kcrtc_st, dflow);
	अगर (err)
		वापस err;

	c_st = komeda_component_get_state_and_set_user(&scaler->base,
			drm_st, user, kcrtc_st->base.crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_scaler_st(c_st);

	st->hsize_in = dflow->in_w;
	st->vsize_in = dflow->in_h;
	st->hsize_out = dflow->out_w;
	st->vsize_out = dflow->out_h;
	st->right_crop = dflow->right_crop;
	st->left_crop = dflow->left_crop;
	st->total_vsize_in = dflow->total_in_h;
	st->total_hsize_in = dflow->total_in_w;
	st->total_hsize_out = dflow->total_out_w;

	/* Enable alpha processing अगर the next stage needs the pixel alpha */
	st->en_alpha = dflow->pixel_blend_mode != DRM_MODE_BLEND_PIXEL_NONE;
	st->en_scaling = dflow->en_scaling;
	st->en_img_enhancement = dflow->en_img_enhancement;
	st->en_split = dflow->en_split;
	st->right_part = dflow->right_part;

	komeda_component_add_input(&st->base, &dflow->input, 0);
	komeda_component_set_output(&dflow->input, &scaler->base, 0);
	वापस err;
पूर्ण

अटल व्योम komeda_split_data_flow(काष्ठा komeda_scaler *scaler,
				   काष्ठा komeda_data_flow_cfg *dflow,
				   काष्ठा komeda_data_flow_cfg *l_dflow,
				   काष्ठा komeda_data_flow_cfg *r_dflow);

अटल पूर्णांक
komeda_splitter_validate(काष्ठा komeda_splitter *splitter,
			 काष्ठा drm_connector_state *conn_st,
			 काष्ठा komeda_data_flow_cfg *dflow,
			 काष्ठा komeda_data_flow_cfg *l_output,
			 काष्ठा komeda_data_flow_cfg *r_output)
अणु
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_splitter_state *st;

	अगर (!splitter) अणु
		DRM_DEBUG_ATOMIC("Current HW doesn't support splitter.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!in_range(&splitter->hsize, dflow->in_w)) अणु
		DRM_DEBUG_ATOMIC("split in_w:%d is out of the acceptable range.\n",
				 dflow->in_w);
		वापस -EINVAL;
	पूर्ण

	अगर (!in_range(&splitter->vsize, dflow->in_h)) अणु
		DRM_DEBUG_ATOMIC("split in_h: %d exceeds the acceptable range.\n",
				 dflow->in_h);
		वापस -EINVAL;
	पूर्ण

	c_st = komeda_component_get_state_and_set_user(&splitter->base,
			conn_st->state, conn_st->connector, conn_st->crtc);

	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	komeda_split_data_flow(splitter->base.pipeline->scalers[0],
			       dflow, l_output, r_output);

	st = to_splitter_st(c_st);
	st->hsize = dflow->in_w;
	st->vsize = dflow->in_h;
	st->overlap = dflow->overlap;

	komeda_component_add_input(&st->base, &dflow->input, 0);
	komeda_component_set_output(&l_output->input, &splitter->base, 0);
	komeda_component_set_output(&r_output->input, &splitter->base, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_merger_validate(काष्ठा komeda_merger *merger,
		       व्योम *user,
		       काष्ठा komeda_crtc_state *kcrtc_st,
		       काष्ठा komeda_data_flow_cfg *left_input,
		       काष्ठा komeda_data_flow_cfg *right_input,
		       काष्ठा komeda_data_flow_cfg *output)
अणु
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_merger_state *st;
	पूर्णांक err = 0;

	अगर (!merger) अणु
		DRM_DEBUG_ATOMIC("No merger is available");
		वापस -EINVAL;
	पूर्ण

	अगर (!in_range(&merger->hsize_merged, output->out_w)) अणु
		DRM_DEBUG_ATOMIC("merged_w: %d is out of the accepted range.\n",
				 output->out_w);
		वापस -EINVAL;
	पूर्ण

	अगर (!in_range(&merger->vsize_merged, output->out_h)) अणु
		DRM_DEBUG_ATOMIC("merged_h: %d is out of the accepted range.\n",
				 output->out_h);
		वापस -EINVAL;
	पूर्ण

	c_st = komeda_component_get_state_and_set_user(&merger->base,
			kcrtc_st->base.state, kcrtc_st->base.crtc, kcrtc_st->base.crtc);

	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_merger_st(c_st);
	st->hsize_merged = output->out_w;
	st->vsize_merged = output->out_h;

	komeda_component_add_input(c_st, &left_input->input, 0);
	komeda_component_add_input(c_st, &right_input->input, 1);
	komeda_component_set_output(&output->input, &merger->base, 0);

	वापस err;
पूर्ण

व्योम pipeline_composition_size(काष्ठा komeda_crtc_state *kcrtc_st,
			       u16 *hsize, u16 *vsize)
अणु
	काष्ठा drm_display_mode *m = &kcrtc_st->base.adjusted_mode;

	अगर (hsize)
		*hsize = m->hdisplay;
	अगर (vsize)
		*vsize = m->vdisplay;
पूर्ण

अटल पूर्णांक
komeda_compiz_set_input(काष्ठा komeda_compiz *compiz,
			काष्ठा komeda_crtc_state *kcrtc_st,
			काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_atomic_state *drm_st = kcrtc_st->base.state;
	काष्ठा komeda_component_state *c_st, *old_st;
	काष्ठा komeda_compiz_input_cfg *cin;
	u16 compiz_w, compiz_h;
	पूर्णांक idx = dflow->blending_zorder;

	pipeline_composition_size(kcrtc_st, &compiz_w, &compiz_h);
	/* check display rect */
	अगर ((dflow->out_x + dflow->out_w > compiz_w) ||
	    (dflow->out_y + dflow->out_h > compiz_h) ||
	     dflow->out_w == 0 || dflow->out_h == 0) अणु
		DRM_DEBUG_ATOMIC("invalid disp rect [x=%d, y=%d, w=%d, h=%d]\n",
				 dflow->out_x, dflow->out_y,
				 dflow->out_w, dflow->out_h);
		वापस -EINVAL;
	पूर्ण

	c_st = komeda_component_get_state_and_set_user(&compiz->base, drm_st,
			kcrtc_st->base.crtc, kcrtc_st->base.crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	अगर (komeda_component_check_input(c_st, &dflow->input, idx))
		वापस -EINVAL;

	cin = &(to_compiz_st(c_st)->cins[idx]);

	cin->hsize   = dflow->out_w;
	cin->vsize   = dflow->out_h;
	cin->hoffset = dflow->out_x;
	cin->voffset = dflow->out_y;
	cin->pixel_blend_mode = dflow->pixel_blend_mode;
	cin->layer_alpha = dflow->layer_alpha;

	old_st = komeda_component_get_old_state(&compiz->base, drm_st);

	/* compare with old to check अगर this input has been changed */
	अगर (WARN_ON(!old_st) ||
	    स_भेद(&(to_compiz_st(old_st)->cins[idx]), cin, माप(*cin)))
		c_st->changed_active_inमाला_दो |= BIT(idx);

	komeda_component_add_input(c_st, &dflow->input, idx);
	komeda_component_set_output(&dflow->input, &compiz->base, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_compiz_validate(काष्ठा komeda_compiz *compiz,
		       काष्ठा komeda_crtc_state *state,
		       काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_compiz_state *st;

	c_st = komeda_component_get_state_and_set_user(&compiz->base,
			state->base.state, state->base.crtc, state->base.crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_compiz_st(c_st);

	pipeline_composition_size(state, &st->hsize, &st->vsize);

	komeda_component_set_output(&dflow->input, &compiz->base, 0);

	/* compiz output dflow will be fed to the next pipeline stage, prepare
	 * the data flow configuration क्रम the next stage
	 */
	अगर (dflow) अणु
		dflow->in_w = st->hsize;
		dflow->in_h = st->vsize;
		dflow->out_w = dflow->in_w;
		dflow->out_h = dflow->in_h;
		/* the output data of compiz करोesn't have alpha, it only can be
		 * used as bottom layer when blend it with master layers
		 */
		dflow->pixel_blend_mode = DRM_MODE_BLEND_PIXEL_NONE;
		dflow->layer_alpha = 0xFF;
		dflow->blending_zorder = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_improc_validate(काष्ठा komeda_improc *improc,
		       काष्ठा komeda_crtc_state *kcrtc_st,
		       काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_crtc *crtc = kcrtc_st->base.crtc;
	काष्ठा drm_crtc_state *crtc_st = &kcrtc_st->base;
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_improc_state *st;

	c_st = komeda_component_get_state_and_set_user(&improc->base,
			kcrtc_st->base.state, crtc, crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_improc_st(c_st);

	st->hsize = dflow->in_w;
	st->vsize = dflow->in_h;

	अगर (drm_atomic_crtc_needs_modeset(crtc_st)) अणु
		u32 output_depths, output_क्रमmats;
		u32 avail_depths, avail_क्रमmats;

		komeda_crtc_get_color_config(crtc_st, &output_depths,
					     &output_क्रमmats);

		avail_depths = output_depths & improc->supported_color_depths;
		अगर (avail_depths == 0) अणु
			DRM_DEBUG_ATOMIC("No available color depths, conn depths: 0x%x & display: 0x%x\n",
					 output_depths,
					 improc->supported_color_depths);
			वापस -EINVAL;
		पूर्ण

		avail_क्रमmats = output_क्रमmats &
				improc->supported_color_क्रमmats;
		अगर (!avail_क्रमmats) अणु
			DRM_DEBUG_ATOMIC("No available color_formats, conn formats 0x%x & display: 0x%x\n",
					 output_क्रमmats,
					 improc->supported_color_क्रमmats);
			वापस -EINVAL;
		पूर्ण

		st->color_depth = __fls(avail_depths);
		st->color_क्रमmat = BIT(__ffs(avail_क्रमmats));
	पूर्ण

	अगर (kcrtc_st->base.color_mgmt_changed) अणु
		drm_lut_to_fgamma_coeffs(kcrtc_st->base.gamma_lut,
					 st->fgamma_coeffs);
		drm_cपंचांग_to_coeffs(kcrtc_st->base.cपंचांग, st->cपंचांग_coeffs);
	पूर्ण

	komeda_component_add_input(&st->base, &dflow->input, 0);
	komeda_component_set_output(&dflow->input, &improc->base, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_timing_ctrlr_validate(काष्ठा komeda_timing_ctrlr *ctrlr,
			     काष्ठा komeda_crtc_state *kcrtc_st,
			     काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_crtc *crtc = kcrtc_st->base.crtc;
	काष्ठा komeda_timing_ctrlr_state *st;
	काष्ठा komeda_component_state *c_st;

	c_st = komeda_component_get_state_and_set_user(&ctrlr->base,
			kcrtc_st->base.state, crtc, crtc);
	अगर (IS_ERR(c_st))
		वापस PTR_ERR(c_st);

	st = to_ctrlr_st(c_st);

	komeda_component_add_input(&st->base, &dflow->input, 0);
	komeda_component_set_output(&dflow->input, &ctrlr->base, 0);

	वापस 0;
पूर्ण

व्योम komeda_complete_data_flow_cfg(काष्ठा komeda_layer *layer,
				   काष्ठा komeda_data_flow_cfg *dflow,
				   काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा komeda_scaler *scaler = layer->base.pipeline->scalers[0];
	u32 w = dflow->in_w;
	u32 h = dflow->in_h;

	dflow->total_in_w = dflow->in_w;
	dflow->total_in_h = dflow->in_h;
	dflow->total_out_w = dflow->out_w;

	/* अगर क्रमmat करोesn't have alpha, fix blend mode to PIXEL_NONE */
	अगर (!fb->क्रमmat->has_alpha)
		dflow->pixel_blend_mode = DRM_MODE_BLEND_PIXEL_NONE;

	अगर (drm_rotation_90_or_270(dflow->rot))
		swap(w, h);

	dflow->en_scaling = (w != dflow->out_w) || (h != dflow->out_h);
	dflow->is_yuv = fb->क्रमmat->is_yuv;

	/* try to enable image enhancer अगर data flow is a 2x+ upscaling */
	dflow->en_img_enhancement = dflow->out_w >= 2 * w ||
				    dflow->out_h >= 2 * h;

	/* try to enable split अगर scaling exceed the scaler's acceptable
	 * input/output range.
	 */
	अगर (dflow->en_scaling && scaler)
		dflow->en_split = !in_range(&scaler->hsize, dflow->in_w) ||
				  !in_range(&scaler->hsize, dflow->out_w);
पूर्ण

अटल bool merger_is_available(काष्ठा komeda_pipeline *pipe,
				काष्ठा komeda_data_flow_cfg *dflow)
अणु
	u32 avail_inमाला_दो = pipe->merger ?
			   pipe->merger->base.supported_inमाला_दो : 0;

	वापस has_bit(dflow->input.component->id, avail_inमाला_दो);
पूर्ण

पूर्णांक komeda_build_layer_data_flow(काष्ठा komeda_layer *layer,
				 काष्ठा komeda_plane_state *kplane_st,
				 काष्ठा komeda_crtc_state *kcrtc_st,
				 काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_plane *plane = kplane_st->base.plane;
	काष्ठा komeda_pipeline *pipe = layer->base.pipeline;
	पूर्णांक err;

	DRM_DEBUG_ATOMIC("%s handling [PLANE:%d:%s]: src[x/y:%d/%d, w/h:%d/%d] disp[x/y:%d/%d, w/h:%d/%d]",
			 layer->base.name, plane->base.id, plane->name,
			 dflow->in_x, dflow->in_y, dflow->in_w, dflow->in_h,
			 dflow->out_x, dflow->out_y, dflow->out_w, dflow->out_h);

	err = komeda_layer_validate(layer, kplane_st, dflow);
	अगर (err)
		वापस err;

	err = komeda_scaler_validate(plane, kcrtc_st, dflow);
	अगर (err)
		वापस err;

	/* अगर split, check अगर can put the data flow पूर्णांकo merger */
	अगर (dflow->en_split && merger_is_available(pipe, dflow))
		वापस 0;

	err = komeda_compiz_set_input(pipe->compiz, kcrtc_st, dflow);

	वापस err;
पूर्ण

/*
 * Split is पूर्णांकroduced क्रम workaround scaler's input/output size limitation.
 * The idea is simple, अगर one scaler can not fit the requirement, use two.
 * So split splits the big source image to two half parts (left/right) and करो
 * the scaling by two scaler separately and independently.
 * But split also imports an edge problem in the middle of the image when
 * scaling, to aव्योम it, split isn't a simple half-and-half, but add an extra
 * pixels (overlap) to both side, after split the left/right will be:
 * - left: [0, src_length/2 + overlap]
 * - right: [src_length/2 - overlap, src_length]
 * The extra overlap करो eliminate the edge problem, but which may also generates
 * unnecessary pixels when scaling, we need to crop them beक्रमe scaler output
 * the result to the next stage. and क्रम the how to crop, it depends on the
 * unneeded pixels, another words the position where overlay has been added.
 * - left: crop the right
 * - right: crop the left
 *
 * The diagram क्रम how to करो the split
 *
 *  <---------------------left->out_w ---------------->
 * |--------------------------------|---right_crop-----| <- left after split
 *  \                                \                /
 *   \                                \<--overlap--->/
 *   |-----------------|-------------|(Middle)------|-----------------| <- src
 *                     /<---overlap--->\                               \
 *                    /                 \                               \
 * right after split->|-----left_crop---|--------------------------------|
 *                    ^<------------------- right->out_w --------------->^
 *
 * NOTE: To consistent with HW the output_w always contains the crop size.
 */

अटल व्योम komeda_split_data_flow(काष्ठा komeda_scaler *scaler,
				   काष्ठा komeda_data_flow_cfg *dflow,
				   काष्ठा komeda_data_flow_cfg *l_dflow,
				   काष्ठा komeda_data_flow_cfg *r_dflow)
अणु
	bool r90 = drm_rotation_90_or_270(dflow->rot);
	bool flip_h = has_flip_h(dflow->rot);
	u32 l_out, r_out, overlap;

	स_नकल(l_dflow, dflow, माप(*dflow));
	स_नकल(r_dflow, dflow, माप(*dflow));

	l_dflow->right_part = false;
	r_dflow->right_part = true;
	r_dflow->blending_zorder = dflow->blending_zorder + 1;

	overlap = 0;
	अगर (dflow->en_scaling && scaler)
		overlap += scaler->scaling_split_overlap;

	/* original dflow may fed पूर्णांकo splitter, and which करोesn't need
	 * enhancement overlap
	 */
	dflow->overlap = overlap;

	अगर (dflow->en_img_enhancement && scaler)
		overlap += scaler->enh_split_overlap;

	l_dflow->overlap = overlap;
	r_dflow->overlap = overlap;

	/* split the origin content */
	/* left/right here always means the left/right part of display image,
	 * not the source Image
	 */
	/* DRM rotation is anti-घड़ीwise */
	अगर (r90) अणु
		अगर (dflow->en_scaling) अणु
			l_dflow->in_h = ALIGN(dflow->in_h, 2) / 2 + l_dflow->overlap;
			r_dflow->in_h = l_dflow->in_h;
		पूर्ण अन्यथा अगर (dflow->en_img_enhancement) अणु
			/* enhancer only */
			l_dflow->in_h = ALIGN(dflow->in_h, 2) / 2 + l_dflow->overlap;
			r_dflow->in_h = dflow->in_h / 2 + r_dflow->overlap;
		पूर्ण अन्यथा अणु
			/* split without scaler, no overlap */
			l_dflow->in_h = ALIGN(((dflow->in_h + 1) >> 1), 2);
			r_dflow->in_h = dflow->in_h - l_dflow->in_h;
		पूर्ण

		/* Consider YUV क्रमmat, after split, the split source w/h
		 * may not aligned to 2. we have two choices क्रम such हाल.
		 * 1. scaler is enabled (overlap != 0), we can करो a alignment
		 *    both left/right and crop the extra data by scaler.
		 * 2. scaler is not enabled, only align the split left
		 *    src/disp, and the rest part assign to right
		 */
		अगर ((overlap != 0) && dflow->is_yuv) अणु
			l_dflow->in_h = ALIGN(l_dflow->in_h, 2);
			r_dflow->in_h = ALIGN(r_dflow->in_h, 2);
		पूर्ण

		अगर (flip_h)
			l_dflow->in_y = dflow->in_y + dflow->in_h - l_dflow->in_h;
		अन्यथा
			r_dflow->in_y = dflow->in_y + dflow->in_h - r_dflow->in_h;
	पूर्ण अन्यथा अणु
		अगर (dflow->en_scaling) अणु
			l_dflow->in_w = ALIGN(dflow->in_w, 2) / 2 + l_dflow->overlap;
			r_dflow->in_w = l_dflow->in_w;
		पूर्ण अन्यथा अगर (dflow->en_img_enhancement) अणु
			l_dflow->in_w = ALIGN(dflow->in_w, 2) / 2 + l_dflow->overlap;
			r_dflow->in_w = dflow->in_w / 2 + r_dflow->overlap;
		पूर्ण अन्यथा अणु
			l_dflow->in_w = ALIGN(((dflow->in_w + 1) >> 1), 2);
			r_dflow->in_w = dflow->in_w - l_dflow->in_w;
		पूर्ण

		/* करो YUV alignment when scaler enabled */
		अगर ((overlap != 0) && dflow->is_yuv) अणु
			l_dflow->in_w = ALIGN(l_dflow->in_w, 2);
			r_dflow->in_w = ALIGN(r_dflow->in_w, 2);
		पूर्ण

		/* on flip_h, the left display content from the right-source */
		अगर (flip_h)
			l_dflow->in_x = dflow->in_w + dflow->in_x - l_dflow->in_w;
		अन्यथा
			r_dflow->in_x = dflow->in_w + dflow->in_x - r_dflow->in_w;
	पूर्ण

	/* split the disp_rect */
	अगर (dflow->en_scaling || dflow->en_img_enhancement)
		l_dflow->out_w = ((dflow->out_w + 1) >> 1);
	अन्यथा
		l_dflow->out_w = ALIGN(((dflow->out_w + 1) >> 1), 2);

	r_dflow->out_w = dflow->out_w - l_dflow->out_w;

	l_dflow->out_x = dflow->out_x;
	r_dflow->out_x = l_dflow->out_w + l_dflow->out_x;

	/* calculate the scaling crop */
	/* left scaler output more data and करो crop */
	अगर (r90) अणु
		l_out = (dflow->out_w * l_dflow->in_h) / dflow->in_h;
		r_out = (dflow->out_w * r_dflow->in_h) / dflow->in_h;
	पूर्ण अन्यथा अणु
		l_out = (dflow->out_w * l_dflow->in_w) / dflow->in_w;
		r_out = (dflow->out_w * r_dflow->in_w) / dflow->in_w;
	पूर्ण

	l_dflow->left_crop  = 0;
	l_dflow->right_crop = l_out - l_dflow->out_w;
	r_dflow->left_crop  = r_out - r_dflow->out_w;
	r_dflow->right_crop = 0;

	/* out_w includes the crop length */
	l_dflow->out_w += l_dflow->right_crop + l_dflow->left_crop;
	r_dflow->out_w += r_dflow->right_crop + r_dflow->left_crop;
पूर्ण

/* For layer split, a plane state will be split to two data flows and handled
 * by two separated komeda layer input pipelines. komeda supports two types of
 * layer split:
 * - none-scaling split:
 *             / layer-left -> \
 * plane_state                  compiz-> ...
 *             \ layer-right-> /
 *
 * - scaling split:
 *             / layer-left -> scaler->\
 * plane_state                          merger -> compiz-> ...
 *             \ layer-right-> scaler->/
 *
 * Since merger only supports scaler as input, so क्रम none-scaling split, two
 * layer data flows will be output to compiz directly. क्रम scaling_split, two
 * data flow will be merged by merger firstly, then merger outमाला_दो one merged
 * data flow to compiz.
 */
पूर्णांक komeda_build_layer_split_data_flow(काष्ठा komeda_layer *left,
				       काष्ठा komeda_plane_state *kplane_st,
				       काष्ठा komeda_crtc_state *kcrtc_st,
				       काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_plane *plane = kplane_st->base.plane;
	काष्ठा komeda_pipeline *pipe = left->base.pipeline;
	काष्ठा komeda_layer *right = left->right;
	काष्ठा komeda_data_flow_cfg l_dflow, r_dflow;
	पूर्णांक err;

	komeda_split_data_flow(pipe->scalers[0], dflow, &l_dflow, &r_dflow);

	DRM_DEBUG_ATOMIC("Assign %s + %s to [PLANE:%d:%s]: "
			 "src[x/y:%d/%d, w/h:%d/%d] disp[x/y:%d/%d, w/h:%d/%d]",
			 left->base.name, right->base.name,
			 plane->base.id, plane->name,
			 dflow->in_x, dflow->in_y, dflow->in_w, dflow->in_h,
			 dflow->out_x, dflow->out_y, dflow->out_w, dflow->out_h);

	err = komeda_build_layer_data_flow(left, kplane_st, kcrtc_st, &l_dflow);
	अगर (err)
		वापस err;

	err = komeda_build_layer_data_flow(right, kplane_st, kcrtc_st, &r_dflow);
	अगर (err)
		वापस err;

	/* The rotation has been handled by layer, so adjusted the data flow */
	komeda_rotate_data_flow(dflow, dflow->rot);

	/* left and right dflow has been merged to compiz alपढ़ोy,
	 * no need merger to merge them anymore.
	 */
	अगर (r_dflow.input.component == l_dflow.input.component)
		वापस 0;

	/* line merger path */
	err = komeda_merger_validate(pipe->merger, plane, kcrtc_st,
				     &l_dflow, &r_dflow, dflow);
	अगर (err)
		वापस err;

	err = komeda_compiz_set_input(pipe->compiz, kcrtc_st, dflow);

	वापस err;
पूर्ण

/* ग_लिखोback data path: compiz -> scaler -> wb_layer -> memory */
पूर्णांक komeda_build_wb_data_flow(काष्ठा komeda_layer *wb_layer,
			      काष्ठा drm_connector_state *conn_st,
			      काष्ठा komeda_crtc_state *kcrtc_st,
			      काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_connector *conn = conn_st->connector;
	पूर्णांक err;

	err = komeda_scaler_validate(conn, kcrtc_st, dflow);
	अगर (err)
		वापस err;

	वापस komeda_wb_layer_validate(wb_layer, conn_st, dflow);
पूर्ण

/* ग_लिखोback scaling split data path:
 *                   /-> scaler ->\
 * compiz -> splitter              merger -> wb_layer -> memory
 *                   \-> scaler ->/
 */
पूर्णांक komeda_build_wb_split_data_flow(काष्ठा komeda_layer *wb_layer,
				    काष्ठा drm_connector_state *conn_st,
				    काष्ठा komeda_crtc_state *kcrtc_st,
				    काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा komeda_pipeline *pipe = wb_layer->base.pipeline;
	काष्ठा drm_connector *conn = conn_st->connector;
	काष्ठा komeda_data_flow_cfg l_dflow, r_dflow;
	पूर्णांक err;

	err = komeda_splitter_validate(pipe->splitter, conn_st,
				       dflow, &l_dflow, &r_dflow);
	अगर (err)
		वापस err;
	err = komeda_scaler_validate(conn, kcrtc_st, &l_dflow);
	अगर (err)
		वापस err;

	err = komeda_scaler_validate(conn, kcrtc_st, &r_dflow);
	अगर (err)
		वापस err;

	err = komeda_merger_validate(pipe->merger, conn_st, kcrtc_st,
				     &l_dflow, &r_dflow, dflow);
	अगर (err)
		वापस err;

	वापस komeda_wb_layer_validate(wb_layer, conn_st, dflow);
पूर्ण

/* build display output data flow, the data path is:
 * compiz -> improc -> timing_ctrlr
 */
पूर्णांक komeda_build_display_data_flow(काष्ठा komeda_crtc *kcrtc,
				   काष्ठा komeda_crtc_state *kcrtc_st)
अणु
	काष्ठा komeda_pipeline *master = kcrtc->master;
	काष्ठा komeda_pipeline *slave  = kcrtc->slave;
	काष्ठा komeda_data_flow_cfg m_dflow; /* master data flow */
	काष्ठा komeda_data_flow_cfg s_dflow; /* slave data flow */
	पूर्णांक err;

	स_रखो(&m_dflow, 0, माप(m_dflow));
	स_रखो(&s_dflow, 0, माप(s_dflow));

	अगर (slave && has_bit(slave->id, kcrtc_st->active_pipes)) अणु
		err = komeda_compiz_validate(slave->compiz, kcrtc_st, &s_dflow);
		अगर (err)
			वापस err;

		/* merge the slave dflow पूर्णांकo master pipeline */
		err = komeda_compiz_set_input(master->compiz, kcrtc_st,
					      &s_dflow);
		अगर (err)
			वापस err;
	पूर्ण

	err = komeda_compiz_validate(master->compiz, kcrtc_st, &m_dflow);
	अगर (err)
		वापस err;

	err = komeda_improc_validate(master->improc, kcrtc_st, &m_dflow);
	अगर (err)
		वापस err;

	err = komeda_timing_ctrlr_validate(master->ctrlr, kcrtc_st, &m_dflow);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम
komeda_pipeline_unbound_components(काष्ठा komeda_pipeline *pipe,
				   काष्ठा komeda_pipeline_state *new)
अणु
	काष्ठा drm_atomic_state *drm_st = new->obj.state;
	काष्ठा komeda_pipeline_state *old = priv_to_pipe_st(pipe->obj.state);
	काष्ठा komeda_component_state *c_st;
	काष्ठा komeda_component *c;
	u32 id;
	अचिन्हित दीर्घ disabling_comps;

	WARN_ON(!old);

	disabling_comps = (~new->active_comps) & old->active_comps;

	/* unbound all disabling component */
	क्रम_each_set_bit(id, &disabling_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, id);
		c_st = komeda_component_get_state_and_set_user(c,
				drm_st, शून्य, new->crtc);
		WARN_ON(IS_ERR(c_st));
	पूर्ण
पूर्ण

/* release unclaimed pipeline resource */
पूर्णांक komeda_release_unclaimed_resources(काष्ठा komeda_pipeline *pipe,
				       काष्ठा komeda_crtc_state *kcrtc_st)
अणु
	काष्ठा drm_atomic_state *drm_st = kcrtc_st->base.state;
	काष्ठा komeda_pipeline_state *st;

	/* ignore the pipeline which is not affected */
	अगर (!pipe || !has_bit(pipe->id, kcrtc_st->affected_pipes))
		वापस 0;

	अगर (has_bit(pipe->id, kcrtc_st->active_pipes))
		st = komeda_pipeline_get_new_state(pipe, drm_st);
	अन्यथा
		st = komeda_pipeline_get_state_and_set_crtc(pipe, drm_st, शून्य);

	अगर (WARN_ON(IS_ERR_OR_शून्य(st)))
		वापस -EINVAL;

	komeda_pipeline_unbound_components(pipe, st);

	वापस 0;
पूर्ण

/* Since standaदीर्घ disabled components must be disabled separately and in the
 * last, So a complete disable operation may needs to call pipeline_disable
 * twice (two phase disabling).
 * Phase 1: disable the common components, flush it.
 * Phase 2: disable the standalone disabled components, flush it.
 *
 * RETURNS:
 * true: disable is not complete, needs a phase 2 disable.
 * false: disable is complete.
 */
bool komeda_pipeline_disable(काष्ठा komeda_pipeline *pipe,
			     काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा komeda_pipeline_state *old;
	काष्ठा komeda_component *c;
	काष्ठा komeda_component_state *c_st;
	u32 id;
	अचिन्हित दीर्घ disabling_comps;

	old = komeda_pipeline_get_old_state(pipe, old_state);

	disabling_comps = old->active_comps &
			  (~pipe->standalone_disabled_comps);
	अगर (!disabling_comps)
		disabling_comps = old->active_comps &
				  pipe->standalone_disabled_comps;

	DRM_DEBUG_ATOMIC("PIPE%d: active_comps: 0x%x, disabling_comps: 0x%lx.\n",
			 pipe->id, old->active_comps, disabling_comps);

	क्रम_each_set_bit(id, &disabling_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, id);
		c_st = priv_to_comp_st(c->obj.state);

		/*
		 * If we disabled a component then all active_inमाला_दो should be
		 * put in the list of changed_active_inमाला_दो, so they get
		 * re-enabled.
		 * This usually happens during a modeset when the pipeline is
		 * first disabled and then the actual state माला_लो committed
		 * again.
		 */
		c_st->changed_active_inमाला_दो |= c_st->active_inमाला_दो;

		c->funcs->disable(c);
	पूर्ण

	/* Update the pipeline state, अगर there are components that are still
	 * active, वापस true क्रम calling the phase 2 disable.
	 */
	old->active_comps &= ~disabling_comps;

	वापस old->active_comps ? true : false;
पूर्ण

व्योम komeda_pipeline_update(काष्ठा komeda_pipeline *pipe,
			    काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा komeda_pipeline_state *new = priv_to_pipe_st(pipe->obj.state);
	काष्ठा komeda_pipeline_state *old;
	काष्ठा komeda_component *c;
	u32 id;
	अचिन्हित दीर्घ changed_comps;

	old = komeda_pipeline_get_old_state(pipe, old_state);

	changed_comps = new->active_comps | old->active_comps;

	DRM_DEBUG_ATOMIC("PIPE%d: active_comps: 0x%x, changed: 0x%lx.\n",
			 pipe->id, new->active_comps, changed_comps);

	क्रम_each_set_bit(id, &changed_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, id);

		अगर (new->active_comps & BIT(c->id))
			c->funcs->update(c, priv_to_comp_st(c->obj.state));
		अन्यथा
			c->funcs->disable(c);
	पूर्ण
पूर्ण
