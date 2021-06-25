<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश "d71_dev.h"
#समावेश "komeda_kms.h"
#समावेश "malidp_io.h"
#समावेश "komeda_framebuffer.h"
#समावेश "komeda_color_mgmt.h"

अटल व्योम get_resources_id(u32 hw_id, u32 *pipe_id, u32 *comp_id)
अणु
	u32 id = BLOCK_INFO_BLK_ID(hw_id);
	u32 pipe = id;

	चयन (BLOCK_INFO_BLK_TYPE(hw_id)) अणु
	हाल D71_BLK_TYPE_LPU_WB_LAYER:
		id = KOMEDA_COMPONENT_WB_LAYER;
		अवरोध;
	हाल D71_BLK_TYPE_CU_SPLITTER:
		id = KOMEDA_COMPONENT_SPLITTER;
		अवरोध;
	हाल D71_BLK_TYPE_CU_SCALER:
		pipe = id / D71_PIPELINE_MAX_SCALERS;
		id %= D71_PIPELINE_MAX_SCALERS;
		id += KOMEDA_COMPONENT_SCALER0;
		अवरोध;
	हाल D71_BLK_TYPE_CU:
		id += KOMEDA_COMPONENT_COMPIZ0;
		अवरोध;
	हाल D71_BLK_TYPE_LPU_LAYER:
		pipe = id / D71_PIPELINE_MAX_LAYERS;
		id %= D71_PIPELINE_MAX_LAYERS;
		id += KOMEDA_COMPONENT_LAYER0;
		अवरोध;
	हाल D71_BLK_TYPE_DOU_IPS:
		id += KOMEDA_COMPONENT_IPS0;
		अवरोध;
	हाल D71_BLK_TYPE_CU_MERGER:
		id = KOMEDA_COMPONENT_MERGER;
		अवरोध;
	हाल D71_BLK_TYPE_DOU:
		id = KOMEDA_COMPONENT_TIMING_CTRLR;
		अवरोध;
	शेष:
		id = 0xFFFFFFFF;
	पूर्ण

	अगर (comp_id)
		*comp_id = id;

	अगर (pipe_id)
		*pipe_id = pipe;
पूर्ण

अटल u32 get_valid_inमाला_दो(काष्ठा block_header *blk)
अणु
	u32 valid_inमाला_दो = 0, comp_id;
	पूर्णांक i;

	क्रम (i = 0; i < PIPELINE_INFO_N_VALID_INPUTS(blk->pipeline_info); i++) अणु
		get_resources_id(blk->input_ids[i], शून्य, &comp_id);
		अगर (comp_id == 0xFFFFFFFF)
			जारी;
		valid_inमाला_दो |= BIT(comp_id);
	पूर्ण

	वापस valid_inमाला_दो;
पूर्ण

अटल व्योम get_values_from_reg(व्योम __iomem *reg, u32 offset,
				u32 count, u32 *val)
अणु
	u32 i, addr;

	क्रम (i = 0; i < count; i++) अणु
		addr = offset + (i << 2);
		/* 0xA4 is WO रेजिस्टर */
		अगर (addr != 0xA4)
			val[i] = malidp_पढ़ो32(reg, addr);
		अन्यथा
			val[i] = 0xDEADDEAD;
	पूर्ण
पूर्ण

अटल व्योम dump_block_header(काष्ठा seq_file *sf, व्योम __iomem *reg)
अणु
	काष्ठा block_header hdr;
	u32 i, n_input, n_output;

	d71_पढ़ो_block_header(reg, &hdr);
	seq_म_लिखो(sf, "BLOCK_INFO:\t\t0x%X\n", hdr.block_info);
	seq_म_लिखो(sf, "PIPELINE_INFO:\t\t0x%X\n", hdr.pipeline_info);

	n_output = PIPELINE_INFO_N_OUTPUTS(hdr.pipeline_info);
	n_input  = PIPELINE_INFO_N_VALID_INPUTS(hdr.pipeline_info);

	क्रम (i = 0; i < n_input; i++)
		seq_म_लिखो(sf, "VALID_INPUT_ID%u:\t0x%X\n",
			   i, hdr.input_ids[i]);

	क्रम (i = 0; i < n_output; i++)
		seq_म_लिखो(sf, "OUTPUT_ID%u:\t\t0x%X\n",
			   i, hdr.output_ids[i]);
पूर्ण

/* On D71, we are using the global line size. From D32, every component have
 * a line size रेजिस्टर to indicate the fअगरo size.
 */
अटल u32 __get_blk_line_size(काष्ठा d71_dev *d71, u32 __iomem *reg,
			       u32 max_शेष)
अणु
	अगर (!d71->periph_addr)
		max_शेष = malidp_पढ़ो32(reg, BLK_MAX_LINE_SIZE);

	वापस max_शेष;
पूर्ण

अटल u32 get_blk_line_size(काष्ठा d71_dev *d71, u32 __iomem *reg)
अणु
	वापस __get_blk_line_size(d71, reg, d71->max_line_size);
पूर्ण

अटल u32 to_rot_ctrl(u32 rot)
अणु
	u32 lr_ctrl = 0;

	चयन (rot & DRM_MODE_ROTATE_MASK) अणु
	हाल DRM_MODE_ROTATE_0:
		lr_ctrl |= L_ROT(L_ROT_R0);
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		lr_ctrl |= L_ROT(L_ROT_R90);
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		lr_ctrl |= L_ROT(L_ROT_R180);
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		lr_ctrl |= L_ROT(L_ROT_R270);
		अवरोध;
	पूर्ण

	अगर (rot & DRM_MODE_REFLECT_X)
		lr_ctrl |= L_HFLIP;
	अगर (rot & DRM_MODE_REFLECT_Y)
		lr_ctrl |= L_VFLIP;

	वापस lr_ctrl;
पूर्ण

अटल u32 to_ad_ctrl(u64 modअगरier)
अणु
	u32 afbc_ctrl = AD_AEN;

	अगर (!modअगरier)
		वापस 0;

	अगर ((modअगरier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK) ==
	    AFBC_FORMAT_MOD_BLOCK_SIZE_32x8)
		afbc_ctrl |= AD_WB;

	अगर (modअगरier & AFBC_FORMAT_MOD_YTR)
		afbc_ctrl |= AD_YT;
	अगर (modअगरier & AFBC_FORMAT_MOD_SPLIT)
		afbc_ctrl |= AD_BS;
	अगर (modअगरier & AFBC_FORMAT_MOD_TILED)
		afbc_ctrl |= AD_TH;

	वापस afbc_ctrl;
पूर्ण

अटल अंतरभूत u32 to_d71_input_id(काष्ठा komeda_component_state *st, पूर्णांक idx)
अणु
	काष्ठा komeda_component_output *input = &st->inमाला_दो[idx];

	/* अगर input is not active, set hw input_id(0) to disable it */
	अगर (has_bit(idx, st->active_inमाला_दो))
		वापस input->component->hw_id + input->output_port;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम d71_layer_update_fb(काष्ठा komeda_component *c,
				काष्ठा komeda_fb *kfb,
				dma_addr_t *addr)
अणु
	काष्ठा drm_framebuffer *fb = &kfb->base;
	स्थिर काष्ठा drm_क्रमmat_info *info = fb->क्रमmat;
	u32 __iomem *reg = c->reg;
	पूर्णांक block_h;

	अगर (info->num_planes > 2)
		malidp_ग_लिखो64(reg, BLK_P2_PTR_LOW, addr[2]);

	अगर (info->num_planes > 1) अणु
		block_h = drm_क्रमmat_info_block_height(info, 1);
		malidp_ग_लिखो32(reg, BLK_P1_STRIDE, fb->pitches[1] * block_h);
		malidp_ग_लिखो64(reg, BLK_P1_PTR_LOW, addr[1]);
	पूर्ण

	block_h = drm_क्रमmat_info_block_height(info, 0);
	malidp_ग_लिखो32(reg, BLK_P0_STRIDE, fb->pitches[0] * block_h);
	malidp_ग_लिखो64(reg, BLK_P0_PTR_LOW, addr[0]);
	malidp_ग_लिखो32(reg, LAYER_FMT, kfb->क्रमmat_caps->hw_id);
पूर्ण

अटल व्योम d71_layer_disable(काष्ठा komeda_component *c)
अणु
	malidp_ग_लिखो32_mask(c->reg, BLK_CONTROL, L_EN, 0);
पूर्ण

अटल व्योम d71_layer_update(काष्ठा komeda_component *c,
			     काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_layer_state *st = to_layer_st(state);
	काष्ठा drm_plane_state *plane_st = state->plane->state;
	काष्ठा drm_framebuffer *fb = plane_st->fb;
	काष्ठा komeda_fb *kfb = to_kfb(fb);
	u32 __iomem *reg = c->reg;
	u32 ctrl_mask = L_EN | L_ROT(L_ROT_R270) | L_HFLIP | L_VFLIP | L_TBU_EN;
	u32 ctrl = L_EN | to_rot_ctrl(st->rot);

	d71_layer_update_fb(c, kfb, st->addr);

	malidp_ग_लिखो32(reg, AD_CONTROL, to_ad_ctrl(fb->modअगरier));
	अगर (fb->modअगरier) अणु
		u64 addr;

		malidp_ग_लिखो32(reg, LAYER_AD_H_CROP, HV_CROP(st->afbc_crop_l,
							     st->afbc_crop_r));
		malidp_ग_लिखो32(reg, LAYER_AD_V_CROP, HV_CROP(st->afbc_crop_t,
							     st->afbc_crop_b));
		/* afbc 1.2 wants payload, afbc 1.0/1.1 wants end_addr */
		अगर (fb->modअगरier & AFBC_FORMAT_MOD_TILED)
			addr = st->addr[0] + kfb->offset_payload;
		अन्यथा
			addr = st->addr[0] + kfb->afbc_size - 1;

		malidp_ग_लिखो32(reg, BLK_P1_PTR_LOW, lower_32_bits(addr));
		malidp_ग_लिखो32(reg, BLK_P1_PTR_HIGH, upper_32_bits(addr));
	पूर्ण

	अगर (fb->क्रमmat->is_yuv) अणु
		u32 upsampling = 0;

		चयन (kfb->क्रमmat_caps->fourcc) अणु
		हाल DRM_FORMAT_YUYV:
			upsampling = fb->modअगरier ? LR_CHI422_BILINEAR :
				     LR_CHI422_REPLICATION;
			अवरोध;
		हाल DRM_FORMAT_UYVY:
			upsampling = LR_CHI422_REPLICATION;
			अवरोध;
		हाल DRM_FORMAT_NV12:
		हाल DRM_FORMAT_YUV420_8BIT:
		हाल DRM_FORMAT_YUV420_10BIT:
		हाल DRM_FORMAT_YUV420:
		हाल DRM_FORMAT_P010:
		/* these fmt support MPGE/JPEG both, here perfer JPEG*/
			upsampling = LR_CHI420_JPEG;
			अवरोध;
		हाल DRM_FORMAT_X0L2:
			upsampling = LR_CHI420_JPEG;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		malidp_ग_लिखो32(reg, LAYER_R_CONTROL, upsampling);
		malidp_ग_लिखो_group(reg, LAYER_YUV_RGB_COEFF0,
				   KOMEDA_N_YUV2RGB_COEFFS,
				   komeda_select_yuv2rgb_coeffs(
					plane_st->color_encoding,
					plane_st->color_range));
	पूर्ण

	malidp_ग_लिखो32(reg, BLK_IN_SIZE, HV_SIZE(st->hsize, st->vsize));

	अगर (kfb->is_va)
		ctrl |= L_TBU_EN;
	malidp_ग_लिखो32_mask(reg, BLK_CONTROL, ctrl_mask, ctrl);
पूर्ण

अटल व्योम d71_layer_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v[15], i;
	bool rich, rgb2rgb;
	अक्षर *prefix;

	get_values_from_reg(c->reg, LAYER_INFO, 1, &v[14]);
	अगर (v[14] & 0x1) अणु
		rich = true;
		prefix = "LR_";
	पूर्ण अन्यथा अणु
		rich = false;
		prefix = "LS_";
	पूर्ण

	rgb2rgb = !!(v[14] & L_INFO_CM);

	dump_block_header(sf, c->reg);

	seq_म_लिखो(sf, "%sLAYER_INFO:\t\t0x%X\n", prefix, v[14]);

	get_values_from_reg(c->reg, 0xD0, 1, v);
	seq_म_लिखो(sf, "%sCONTROL:\t\t0x%X\n", prefix, v[0]);
	अगर (rich) अणु
		get_values_from_reg(c->reg, 0xD4, 1, v);
		seq_म_लिखो(sf, "LR_RICH_CONTROL:\t0x%X\n", v[0]);
	पूर्ण
	get_values_from_reg(c->reg, 0xD8, 4, v);
	seq_म_लिखो(sf, "%sFORMAT:\t\t0x%X\n", prefix, v[0]);
	seq_म_लिखो(sf, "%sIT_COEFFTAB:\t\t0x%X\n", prefix, v[1]);
	seq_म_लिखो(sf, "%sIN_SIZE:\t\t0x%X\n", prefix, v[2]);
	seq_म_लिखो(sf, "%sPALPHA:\t\t0x%X\n", prefix, v[3]);

	get_values_from_reg(c->reg, 0x100, 3, v);
	seq_म_लिखो(sf, "%sP0_PTR_LOW:\t\t0x%X\n", prefix, v[0]);
	seq_म_लिखो(sf, "%sP0_PTR_HIGH:\t\t0x%X\n", prefix, v[1]);
	seq_म_लिखो(sf, "%sP0_STRIDE:\t\t0x%X\n", prefix, v[2]);

	get_values_from_reg(c->reg, 0x110, 2, v);
	seq_म_लिखो(sf, "%sP1_PTR_LOW:\t\t0x%X\n", prefix, v[0]);
	seq_म_लिखो(sf, "%sP1_PTR_HIGH:\t\t0x%X\n", prefix, v[1]);
	अगर (rich) अणु
		get_values_from_reg(c->reg, 0x118, 1, v);
		seq_म_लिखो(sf, "LR_P1_STRIDE:\t\t0x%X\n", v[0]);

		get_values_from_reg(c->reg, 0x120, 2, v);
		seq_म_लिखो(sf, "LR_P2_PTR_LOW:\t\t0x%X\n", v[0]);
		seq_म_लिखो(sf, "LR_P2_PTR_HIGH:\t\t0x%X\n", v[1]);

		get_values_from_reg(c->reg, 0x130, 12, v);
		क्रम (i = 0; i < 12; i++)
			seq_म_लिखो(sf, "LR_YUV_RGB_COEFF%u:\t0x%X\n", i, v[i]);
	पूर्ण

	अगर (rgb2rgb) अणु
		get_values_from_reg(c->reg, LAYER_RGB_RGB_COEFF0, 12, v);
		क्रम (i = 0; i < 12; i++)
			seq_म_लिखो(sf, "LS_RGB_RGB_COEFF%u:\t0x%X\n", i, v[i]);
	पूर्ण

	get_values_from_reg(c->reg, 0x160, 3, v);
	seq_म_लिखो(sf, "%sAD_CONTROL:\t\t0x%X\n", prefix, v[0]);
	seq_म_लिखो(sf, "%sAD_H_CROP:\t\t0x%X\n", prefix, v[1]);
	seq_म_लिखो(sf, "%sAD_V_CROP:\t\t0x%X\n", prefix, v[2]);
पूर्ण

अटल पूर्णांक d71_layer_validate(काष्ठा komeda_component *c,
			      काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_layer_state *st = to_layer_st(state);
	काष्ठा komeda_layer *layer = to_layer(c);
	काष्ठा drm_plane_state *plane_st;
	काष्ठा drm_framebuffer *fb;
	u32 fourcc, line_sz, max_line_sz;

	plane_st = drm_atomic_get_new_plane_state(state->obj.state,
						  state->plane);
	fb = plane_st->fb;
	fourcc = fb->क्रमmat->क्रमmat;

	अगर (drm_rotation_90_or_270(st->rot))
		line_sz = st->vsize - st->afbc_crop_t - st->afbc_crop_b;
	अन्यथा
		line_sz = st->hsize - st->afbc_crop_l - st->afbc_crop_r;

	अगर (fb->modअगरier) अणु
		अगर ((fb->modअगरier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK) ==
			AFBC_FORMAT_MOD_BLOCK_SIZE_32x8)
			max_line_sz = layer->line_sz;
		अन्यथा
			max_line_sz = layer->line_sz / 2;

		अगर (line_sz > max_line_sz) अणु
			DRM_DEBUG_ATOMIC("afbc request line_sz: %d exceed the max afbc line_sz: %d.\n",
					 line_sz, max_line_sz);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (fourcc == DRM_FORMAT_YUV420_10BIT && line_sz > 2046 && (st->afbc_crop_l % 4)) अणु
		DRM_DEBUG_ATOMIC("YUV420_10BIT input_hsize: %d exceed the max size 2046.\n",
				 line_sz);
		वापस -EINVAL;
	पूर्ण

	अगर (fourcc == DRM_FORMAT_X0L2 && line_sz > 2046 && (st->addr[0] % 16)) अणु
		DRM_DEBUG_ATOMIC("X0L2 input_hsize: %d exceed the max size 2046.\n",
				 line_sz);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_layer_funcs = अणु
	.validate	= d71_layer_validate,
	.update		= d71_layer_update,
	.disable	= d71_layer_disable,
	.dump_रेजिस्टर	= d71_layer_dump,
पूर्ण;

अटल पूर्णांक d71_layer_init(काष्ठा d71_dev *d71,
			  काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_layer *layer;
	u32 pipe_id, layer_id, layer_info;

	get_resources_id(blk->block_info, &pipe_id, &layer_id);
	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*layer),
				 layer_id,
				 BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_layer_funcs, 0,
				 get_valid_inमाला_दो(blk),
				 1, reg, "LPU%d_LAYER%d", pipe_id, layer_id);
	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to add layer component\n");
		वापस PTR_ERR(c);
	पूर्ण

	layer = to_layer(c);
	layer_info = malidp_पढ़ो32(reg, LAYER_INFO);

	अगर (layer_info & L_INFO_RF)
		layer->layer_type = KOMEDA_FMT_RICH_LAYER;
	अन्यथा
		layer->layer_type = KOMEDA_FMT_SIMPLE_LAYER;

	अगर (!d71->periph_addr) अणु
		/* D32 or newer product */
		layer->line_sz = malidp_पढ़ो32(reg, BLK_MAX_LINE_SIZE);
		layer->yuv_line_sz = L_INFO_YUV_MAX_LINESZ(layer_info);
	पूर्ण अन्यथा अगर (d71->max_line_size > 2048) अणु
		/* D71 4K */
		layer->line_sz = d71->max_line_size;
		layer->yuv_line_sz = layer->line_sz / 2;
	पूर्ण अन्यथा	अणु
		/* D71 2K */
		अगर (layer->layer_type == KOMEDA_FMT_RICH_LAYER) अणु
			/* rich layer is 4K configuration */
			layer->line_sz = d71->max_line_size * 2;
			layer->yuv_line_sz = layer->line_sz / 2;
		पूर्ण अन्यथा अणु
			layer->line_sz = d71->max_line_size;
			layer->yuv_line_sz = 0;
		पूर्ण
	पूर्ण

	set_range(&layer->hsize_in, 4, layer->line_sz);

	set_range(&layer->vsize_in, 4, d71->max_vsize);

	malidp_ग_लिखो32(reg, LAYER_PALPHA, D71_PALPHA_DEF_MAP);

	layer->supported_rots = DRM_MODE_ROTATE_MASK | DRM_MODE_REFLECT_MASK;

	वापस 0;
पूर्ण

अटल व्योम d71_wb_layer_update(काष्ठा komeda_component *c,
				काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_layer_state *st = to_layer_st(state);
	काष्ठा drm_connector_state *conn_st = state->wb_conn->state;
	काष्ठा komeda_fb *kfb = to_kfb(conn_st->ग_लिखोback_job->fb);
	u32 ctrl = L_EN | LW_OFM, mask = L_EN | LW_OFM | LW_TBU_EN;
	u32 __iomem *reg = c->reg;

	d71_layer_update_fb(c, kfb, st->addr);

	अगर (kfb->is_va)
		ctrl |= LW_TBU_EN;

	malidp_ग_लिखो32(reg, BLK_IN_SIZE, HV_SIZE(st->hsize, st->vsize));
	malidp_ग_लिखो32(reg, BLK_INPUT_ID0, to_d71_input_id(state, 0));
	malidp_ग_लिखो32_mask(reg, BLK_CONTROL, mask, ctrl);
पूर्ण

अटल व्योम d71_wb_layer_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v[12], i;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 1, v);
	seq_म_लिखो(sf, "LW_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xD0, 3, v);
	seq_म_लिखो(sf, "LW_CONTROL:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "LW_PROG_LINE:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "LW_FORMAT:\t\t0x%X\n", v[2]);

	get_values_from_reg(c->reg, 0xE0, 1, v);
	seq_म_लिखो(sf, "LW_IN_SIZE:\t\t0x%X\n", v[0]);

	क्रम (i = 0; i < 2; i++) अणु
		get_values_from_reg(c->reg, 0x100 + i * 0x10, 3, v);
		seq_म_लिखो(sf, "LW_P%u_PTR_LOW:\t\t0x%X\n", i, v[0]);
		seq_म_लिखो(sf, "LW_P%u_PTR_HIGH:\t\t0x%X\n", i, v[1]);
		seq_म_लिखो(sf, "LW_P%u_STRIDE:\t\t0x%X\n", i, v[2]);
	पूर्ण

	get_values_from_reg(c->reg, 0x130, 12, v);
	क्रम (i = 0; i < 12; i++)
		seq_म_लिखो(sf, "LW_RGB_YUV_COEFF%u:\t0x%X\n", i, v[i]);
पूर्ण

अटल व्योम d71_wb_layer_disable(काष्ठा komeda_component *c)
अणु
	malidp_ग_लिखो32(c->reg, BLK_INPUT_ID0, 0);
	malidp_ग_लिखो32_mask(c->reg, BLK_CONTROL, L_EN, 0);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_wb_layer_funcs = अणु
	.update		= d71_wb_layer_update,
	.disable	= d71_wb_layer_disable,
	.dump_रेजिस्टर	= d71_wb_layer_dump,
पूर्ण;

अटल पूर्णांक d71_wb_layer_init(काष्ठा d71_dev *d71,
			     काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_layer *wb_layer;
	u32 pipe_id, layer_id;

	get_resources_id(blk->block_info, &pipe_id, &layer_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*wb_layer),
				 layer_id, BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_wb_layer_funcs,
				 1, get_valid_inमाला_दो(blk), 0, reg,
				 "LPU%d_LAYER_WR", pipe_id);
	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to add wb_layer component\n");
		वापस PTR_ERR(c);
	पूर्ण

	wb_layer = to_layer(c);
	wb_layer->layer_type = KOMEDA_FMT_WB_LAYER;
	wb_layer->line_sz = get_blk_line_size(d71, reg);
	wb_layer->yuv_line_sz = wb_layer->line_sz;

	set_range(&wb_layer->hsize_in, 64, wb_layer->line_sz);
	set_range(&wb_layer->vsize_in, 64, d71->max_vsize);

	वापस 0;
पूर्ण

अटल व्योम d71_component_disable(काष्ठा komeda_component *c)
अणु
	u32 __iomem *reg = c->reg;
	u32 i;

	malidp_ग_लिखो32(reg, BLK_CONTROL, 0);

	क्रम (i = 0; i < c->max_active_inमाला_दो; i++) अणु
		malidp_ग_लिखो32(reg, BLK_INPUT_ID0 + (i << 2), 0);

		/* Besides clearing the input ID to zero, D71 compiz also has
		 * input enable bit in CU_INPUTx_CONTROL which need to be
		 * cleared.
		 */
		अगर (has_bit(c->id, KOMEDA_PIPELINE_COMPIZS))
			malidp_ग_लिखो32(reg, CU_INPUT0_CONTROL +
				       i * CU_PER_INPUT_REGS * 4,
				       CU_INPUT_CTRL_ALPHA(0xFF));
	पूर्ण
पूर्ण

अटल व्योम compiz_enable_input(u32 __iomem *id_reg,
				u32 __iomem *cfg_reg,
				u32 input_hw_id,
				काष्ठा komeda_compiz_input_cfg *cin)
अणु
	u32 ctrl = CU_INPUT_CTRL_EN;
	u8 blend = cin->pixel_blend_mode;

	अगर (blend == DRM_MODE_BLEND_PIXEL_NONE)
		ctrl |= CU_INPUT_CTRL_PAD;
	अन्यथा अगर (blend == DRM_MODE_BLEND_PREMULTI)
		ctrl |= CU_INPUT_CTRL_PMUL;

	ctrl |= CU_INPUT_CTRL_ALPHA(cin->layer_alpha);

	malidp_ग_लिखो32(id_reg, BLK_INPUT_ID0, input_hw_id);

	malidp_ग_लिखो32(cfg_reg, CU_INPUT0_SIZE,
		       HV_SIZE(cin->hsize, cin->vsize));
	malidp_ग_लिखो32(cfg_reg, CU_INPUT0_OFFSET,
		       HV_OFFSET(cin->hoffset, cin->voffset));
	malidp_ग_लिखो32(cfg_reg, CU_INPUT0_CONTROL, ctrl);
पूर्ण

अटल व्योम d71_compiz_update(काष्ठा komeda_component *c,
			      काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_compiz_state *st = to_compiz_st(state);
	u32 __iomem *reg = c->reg;
	u32 __iomem *id_reg, *cfg_reg;
	u32 index;

	क्रम_each_changed_input(state, index) अणु
		id_reg = reg + index;
		cfg_reg = reg + index * CU_PER_INPUT_REGS;
		अगर (state->active_inमाला_दो & BIT(index)) अणु
			compiz_enable_input(id_reg, cfg_reg,
					    to_d71_input_id(state, index),
					    &st->cins[index]);
		पूर्ण अन्यथा अणु
			malidp_ग_लिखो32(id_reg, BLK_INPUT_ID0, 0);
			malidp_ग_लिखो32(cfg_reg, CU_INPUT0_CONTROL, 0);
		पूर्ण
	पूर्ण

	malidp_ग_लिखो32(reg, BLK_SIZE, HV_SIZE(st->hsize, st->vsize));
पूर्ण

अटल व्योम d71_compiz_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v[8], i;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 5, v);
	क्रम (i = 0; i < 5; i++)
		seq_म_लिखो(sf, "CU_INPUT_ID%u:\t\t0x%X\n", i, v[i]);

	get_values_from_reg(c->reg, 0xA0, 5, v);
	seq_म_लिखो(sf, "CU_IRQ_RAW_STATUS:\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "CU_IRQ_CLEAR:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "CU_IRQ_MASK:\t\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "CU_IRQ_STATUS:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "CU_STATUS:\t\t0x%X\n", v[4]);

	get_values_from_reg(c->reg, 0xD0, 2, v);
	seq_म_लिखो(sf, "CU_CONTROL:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "CU_SIZE:\t\t0x%X\n", v[1]);

	get_values_from_reg(c->reg, 0xDC, 1, v);
	seq_म_लिखो(sf, "CU_BG_COLOR:\t\t0x%X\n", v[0]);

	क्रम (i = 0, v[4] = 0xE0; i < 5; i++, v[4] += 0x10) अणु
		get_values_from_reg(c->reg, v[4], 3, v);
		seq_म_लिखो(sf, "CU_INPUT%u_SIZE:\t\t0x%X\n", i, v[0]);
		seq_म_लिखो(sf, "CU_INPUT%u_OFFSET:\t0x%X\n", i, v[1]);
		seq_म_लिखो(sf, "CU_INPUT%u_CONTROL:\t0x%X\n", i, v[2]);
	पूर्ण

	get_values_from_reg(c->reg, 0x130, 2, v);
	seq_म_लिखो(sf, "CU_USER_LOW:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "CU_USER_HIGH:\t\t0x%X\n", v[1]);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_compiz_funcs = अणु
	.update		= d71_compiz_update,
	.disable	= d71_component_disable,
	.dump_रेजिस्टर	= d71_compiz_dump,
पूर्ण;

अटल पूर्णांक d71_compiz_init(काष्ठा d71_dev *d71,
			   काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_compiz *compiz;
	u32 pipe_id, comp_id;

	get_resources_id(blk->block_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*compiz),
				 comp_id,
				 BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_compiz_funcs,
				 CU_NUM_INPUT_IDS, get_valid_inमाला_दो(blk),
				 CU_NUM_OUTPUT_IDS, reg,
				 "CU%d", pipe_id);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);

	compiz = to_compiz(c);

	set_range(&compiz->hsize, 64, get_blk_line_size(d71, reg));
	set_range(&compiz->vsize, 64, d71->max_vsize);

	वापस 0;
पूर्ण

अटल व्योम d71_scaler_update_filter_lut(u32 __iomem *reg, u32 hsize_in,
					 u32 vsize_in, u32 hsize_out,
					 u32 vsize_out)
अणु
	u32 val = 0;

	अगर (hsize_in <= hsize_out)
		val  |= 0x62;
	अन्यथा अगर (hsize_in <= (hsize_out + hsize_out / 2))
		val |= 0x63;
	अन्यथा अगर (hsize_in <= hsize_out * 2)
		val |= 0x64;
	अन्यथा अगर (hsize_in <= hsize_out * 2 + (hsize_out * 3) / 4)
		val |= 0x65;
	अन्यथा
		val |= 0x66;

	अगर (vsize_in <= vsize_out)
		val  |= SC_VTSEL(0x6A);
	अन्यथा अगर (vsize_in <= (vsize_out + vsize_out / 2))
		val |= SC_VTSEL(0x6B);
	अन्यथा अगर (vsize_in <= vsize_out * 2)
		val |= SC_VTSEL(0x6C);
	अन्यथा अगर (vsize_in <= vsize_out * 2 + vsize_out * 3 / 4)
		val |= SC_VTSEL(0x6D);
	अन्यथा
		val |= SC_VTSEL(0x6E);

	malidp_ग_लिखो32(reg, SC_COEFFTAB, val);
पूर्ण

अटल व्योम d71_scaler_update(काष्ठा komeda_component *c,
			      काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_scaler_state *st = to_scaler_st(state);
	u32 __iomem *reg = c->reg;
	u32 init_ph, delta_ph, ctrl;

	d71_scaler_update_filter_lut(reg, st->hsize_in, st->vsize_in,
				     st->hsize_out, st->vsize_out);

	malidp_ग_लिखो32(reg, BLK_IN_SIZE, HV_SIZE(st->hsize_in, st->vsize_in));
	malidp_ग_लिखो32(reg, SC_OUT_SIZE, HV_SIZE(st->hsize_out, st->vsize_out));
	malidp_ग_लिखो32(reg, SC_H_CROP, HV_CROP(st->left_crop, st->right_crop));

	/* क्रम right part, HW only sample the valid pixel which means the pixels
	 * in left_crop will be jumpped, and the first sample pixel is:
	 *
	 * dst_a = st->total_hsize_out - st->hsize_out + st->left_crop + 0.5;
	 *
	 * Then the corresponding texel in src is:
	 *
	 * h_delta_phase = st->total_hsize_in / st->total_hsize_out;
	 * src_a = dst_A * h_delta_phase;
	 *
	 * and h_init_phase is src_a deduct the real source start src_S;
	 *
	 * src_S = st->total_hsize_in - st->hsize_in;
	 * h_init_phase = src_a - src_S;
	 *
	 * And HW precision क्रम the initial/delta_phase is 16:16 fixed poपूर्णांक,
	 * the following is the simplअगरied क्रमmula
	 */
	अगर (st->right_part) अणु
		u32 dst_a = st->total_hsize_out - st->hsize_out + st->left_crop;

		अगर (st->en_img_enhancement)
			dst_a -= 1;

		init_ph = ((st->total_hsize_in * (2 * dst_a + 1) -
			    2 * st->total_hsize_out * (st->total_hsize_in -
			    st->hsize_in)) << 15) / st->total_hsize_out;
	पूर्ण अन्यथा अणु
		init_ph = (st->total_hsize_in << 15) / st->total_hsize_out;
	पूर्ण

	malidp_ग_लिखो32(reg, SC_H_INIT_PH, init_ph);

	delta_ph = (st->total_hsize_in << 16) / st->total_hsize_out;
	malidp_ग_लिखो32(reg, SC_H_DELTA_PH, delta_ph);

	init_ph = (st->total_vsize_in << 15) / st->vsize_out;
	malidp_ग_लिखो32(reg, SC_V_INIT_PH, init_ph);

	delta_ph = (st->total_vsize_in << 16) / st->vsize_out;
	malidp_ग_लिखो32(reg, SC_V_DELTA_PH, delta_ph);

	ctrl = 0;
	ctrl |= st->en_scaling ? SC_CTRL_SCL : 0;
	ctrl |= st->en_alpha ? SC_CTRL_AP : 0;
	ctrl |= st->en_img_enhancement ? SC_CTRL_IENH : 0;
	/* If we use the hardware splitter we shouldn't set SC_CTRL_LS */
	अगर (st->en_split &&
	    state->inमाला_दो[0].component->id != KOMEDA_COMPONENT_SPLITTER)
		ctrl |= SC_CTRL_LS;

	malidp_ग_लिखो32(reg, BLK_CONTROL, ctrl);
	malidp_ग_लिखो32(reg, BLK_INPUT_ID0, to_d71_input_id(state, 0));
पूर्ण

अटल व्योम d71_scaler_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v[10];

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 1, v);
	seq_म_लिखो(sf, "SC_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xD0, 1, v);
	seq_म_लिखो(sf, "SC_CONTROL:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xDC, 9, v);
	seq_म_लिखो(sf, "SC_COEFFTAB:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "SC_IN_SIZE:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "SC_OUT_SIZE:\t\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "SC_H_CROP:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "SC_V_CROP:\t\t0x%X\n", v[4]);
	seq_म_लिखो(sf, "SC_H_INIT_PH:\t\t0x%X\n", v[5]);
	seq_म_लिखो(sf, "SC_H_DELTA_PH:\t\t0x%X\n", v[6]);
	seq_म_लिखो(sf, "SC_V_INIT_PH:\t\t0x%X\n", v[7]);
	seq_म_लिखो(sf, "SC_V_DELTA_PH:\t\t0x%X\n", v[8]);

	get_values_from_reg(c->reg, 0x130, 10, v);
	seq_म_लिखो(sf, "SC_ENH_LIMITS:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "SC_ENH_COEFF0:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "SC_ENH_COEFF1:\t\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "SC_ENH_COEFF2:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "SC_ENH_COEFF3:\t\t0x%X\n", v[4]);
	seq_म_लिखो(sf, "SC_ENH_COEFF4:\t\t0x%X\n", v[5]);
	seq_म_लिखो(sf, "SC_ENH_COEFF5:\t\t0x%X\n", v[6]);
	seq_म_लिखो(sf, "SC_ENH_COEFF6:\t\t0x%X\n", v[7]);
	seq_म_लिखो(sf, "SC_ENH_COEFF7:\t\t0x%X\n", v[8]);
	seq_म_लिखो(sf, "SC_ENH_COEFF8:\t\t0x%X\n", v[9]);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_scaler_funcs = अणु
	.update		= d71_scaler_update,
	.disable	= d71_component_disable,
	.dump_रेजिस्टर	= d71_scaler_dump,
पूर्ण;

अटल पूर्णांक d71_scaler_init(काष्ठा d71_dev *d71,
			   काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_scaler *scaler;
	u32 pipe_id, comp_id;

	get_resources_id(blk->block_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*scaler),
				 comp_id, BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_scaler_funcs,
				 1, get_valid_inमाला_दो(blk), 1, reg,
				 "CU%d_SCALER%d",
				 pipe_id, BLOCK_INFO_BLK_ID(blk->block_info));

	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to initialize scaler");
		वापस PTR_ERR(c);
	पूर्ण

	scaler = to_scaler(c);
	set_range(&scaler->hsize, 4, __get_blk_line_size(d71, reg, 2048));
	set_range(&scaler->vsize, 4, 4096);
	scaler->max_करोwnscaling = 6;
	scaler->max_upscaling = 64;
	scaler->scaling_split_overlap = 8;
	scaler->enh_split_overlap = 1;

	malidp_ग_लिखो32(c->reg, BLK_CONTROL, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक d71_करोwnscaling_clk_check(काष्ठा komeda_pipeline *pipe,
				     काष्ठा drm_display_mode *mode,
				     अचिन्हित दीर्घ aclk_rate,
				     काष्ठा komeda_data_flow_cfg *dflow)
अणु
	u32 h_in = dflow->in_w;
	u32 v_in = dflow->in_h;
	u32 v_out = dflow->out_h;
	u64 fraction, denominator;

	/* D71 करोwnscaling must satisfy the following equation
	 *
	 *   ACLK                   h_in * v_in
	 * ------- >= ---------------------------------------------
	 *  PXLCLK     (h_total - (1 + 2 * v_in / v_out)) * v_out
	 *
	 * In only horizontal करोwnscaling situation, the right side should be
	 * multiplied by (h_total - 3) / (h_active - 3), then equation becomes
	 *
	 *   ACLK          h_in
	 * ------- >= ----------------
	 *  PXLCLK     (h_active - 3)
	 *
	 * To aव्योम precision lost the equation 1 will be convert to:
	 *
	 *   ACLK             h_in * v_in
	 * ------- >= -----------------------------------
	 *  PXLCLK     (h_total -1 ) * v_out -  2 * v_in
	 */
	अगर (v_in == v_out) अणु
		fraction = h_in;
		denominator = mode->hdisplay - 3;
	पूर्ण अन्यथा अणु
		fraction = h_in * v_in;
		denominator = (mode->htotal - 1) * v_out -  2 * v_in;
	पूर्ण

	वापस aclk_rate * denominator >= mode->crtc_घड़ी * 1000 * fraction ?
	       0 : -EINVAL;
पूर्ण

अटल व्योम d71_splitter_update(काष्ठा komeda_component *c,
				काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_splitter_state *st = to_splitter_st(state);
	u32 __iomem *reg = c->reg;

	malidp_ग_लिखो32(reg, BLK_INPUT_ID0, to_d71_input_id(state, 0));
	malidp_ग_लिखो32(reg, BLK_SIZE, HV_SIZE(st->hsize, st->vsize));
	malidp_ग_लिखो32(reg, SP_OVERLAP_SIZE, st->overlap & 0x1FFF);
	malidp_ग_लिखो32(reg, BLK_CONTROL, BLK_CTRL_EN);
पूर्ण

अटल व्योम d71_splitter_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v[3];

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, BLK_INPUT_ID0, 1, v);
	seq_म_लिखो(sf, "SP_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, BLK_CONTROL, 3, v);
	seq_म_लिखो(sf, "SP_CONTROL:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "SP_SIZE:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "SP_OVERLAP_SIZE:\t0x%X\n", v[2]);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_splitter_funcs = अणु
	.update		= d71_splitter_update,
	.disable	= d71_component_disable,
	.dump_रेजिस्टर	= d71_splitter_dump,
पूर्ण;

अटल पूर्णांक d71_splitter_init(काष्ठा d71_dev *d71,
			     काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_splitter *splitter;
	u32 pipe_id, comp_id;

	get_resources_id(blk->block_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*splitter),
				 comp_id,
				 BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_splitter_funcs,
				 1, get_valid_inमाला_दो(blk), 2, reg,
				 "CU%d_SPLITTER", pipe_id);

	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to initialize splitter");
		वापस -1;
	पूर्ण

	splitter = to_splitter(c);

	set_range(&splitter->hsize, 4, get_blk_line_size(d71, reg));
	set_range(&splitter->vsize, 4, d71->max_vsize);

	वापस 0;
पूर्ण

अटल व्योम d71_merger_update(काष्ठा komeda_component *c,
			      काष्ठा komeda_component_state *state)
अणु
	काष्ठा komeda_merger_state *st = to_merger_st(state);
	u32 __iomem *reg = c->reg;
	u32 index;

	क्रम_each_changed_input(state, index)
		malidp_ग_लिखो32(reg, MG_INPUT_ID0 + index * 4,
			       to_d71_input_id(state, index));

	malidp_ग_लिखो32(reg, MG_SIZE, HV_SIZE(st->hsize_merged,
					     st->vsize_merged));
	malidp_ग_लिखो32(reg, BLK_CONTROL, BLK_CTRL_EN);
पूर्ण

अटल व्योम d71_merger_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, MG_INPUT_ID0, 1, &v);
	seq_म_लिखो(sf, "MG_INPUT_ID0:\t\t0x%X\n", v);

	get_values_from_reg(c->reg, MG_INPUT_ID1, 1, &v);
	seq_म_लिखो(sf, "MG_INPUT_ID1:\t\t0x%X\n", v);

	get_values_from_reg(c->reg, BLK_CONTROL, 1, &v);
	seq_म_लिखो(sf, "MG_CONTROL:\t\t0x%X\n", v);

	get_values_from_reg(c->reg, MG_SIZE, 1, &v);
	seq_म_लिखो(sf, "MG_SIZE:\t\t0x%X\n", v);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_merger_funcs = अणु
	.update		= d71_merger_update,
	.disable	= d71_component_disable,
	.dump_रेजिस्टर	= d71_merger_dump,
पूर्ण;

अटल पूर्णांक d71_merger_init(काष्ठा d71_dev *d71,
			   काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_merger *merger;
	u32 pipe_id, comp_id;

	get_resources_id(blk->block_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*merger),
				 comp_id,
				 BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_merger_funcs,
				 MG_NUM_INPUTS_IDS, get_valid_inमाला_दो(blk),
				 MG_NUM_OUTPUTS_IDS, reg,
				 "CU%d_MERGER", pipe_id);

	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to initialize merger.\n");
		वापस PTR_ERR(c);
	पूर्ण

	merger = to_merger(c);

	set_range(&merger->hsize_merged, 4,
		  __get_blk_line_size(d71, reg, 4032));
	set_range(&merger->vsize_merged, 4, 4096);

	वापस 0;
पूर्ण

अटल व्योम d71_improc_update(काष्ठा komeda_component *c,
			      काष्ठा komeda_component_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_st = state->crtc->state;
	काष्ठा komeda_improc_state *st = to_improc_st(state);
	काष्ठा d71_pipeline *pipe = to_d71_pipeline(c->pipeline);
	u32 __iomem *reg = c->reg;
	u32 index, mask = 0, ctrl = 0;

	क्रम_each_changed_input(state, index)
		malidp_ग_लिखो32(reg, BLK_INPUT_ID0 + index * 4,
			       to_d71_input_id(state, index));

	malidp_ग_लिखो32(reg, BLK_SIZE, HV_SIZE(st->hsize, st->vsize));
	malidp_ग_लिखो32(reg, IPS_DEPTH, st->color_depth);

	अगर (crtc_st->color_mgmt_changed) अणु
		mask |= IPS_CTRL_FT | IPS_CTRL_RGB;

		अगर (crtc_st->gamma_lut) अणु
			malidp_ग_लिखो_group(pipe->करोu_ft_coeff_addr, FT_COEFF0,
					   KOMEDA_N_GAMMA_COEFFS,
					   st->fgamma_coeffs);
			ctrl |= IPS_CTRL_FT; /* enable gamma */
		पूर्ण

		अगर (crtc_st->cपंचांग) अणु
			malidp_ग_लिखो_group(reg, IPS_RGB_RGB_COEFF0,
					   KOMEDA_N_CTM_COEFFS,
					   st->cपंचांग_coeffs);
			ctrl |= IPS_CTRL_RGB; /* enable gamut */
		पूर्ण
	पूर्ण

	mask |= IPS_CTRL_YUV | IPS_CTRL_CHD422 | IPS_CTRL_CHD420;

	/* config color क्रमmat */
	अगर (st->color_क्रमmat == DRM_COLOR_FORMAT_YCRCB420)
		ctrl |= IPS_CTRL_YUV | IPS_CTRL_CHD422 | IPS_CTRL_CHD420;
	अन्यथा अगर (st->color_क्रमmat == DRM_COLOR_FORMAT_YCRCB422)
		ctrl |= IPS_CTRL_YUV | IPS_CTRL_CHD422;
	अन्यथा अगर (st->color_क्रमmat == DRM_COLOR_FORMAT_YCRCB444)
		ctrl |= IPS_CTRL_YUV;

	malidp_ग_लिखो32_mask(reg, BLK_CONTROL, mask, ctrl);
पूर्ण

अटल व्योम d71_improc_dump(काष्ठा komeda_component *c, काष्ठा seq_file *sf)
अणु
	u32 v[12], i;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 2, v);
	seq_म_लिखो(sf, "IPS_INPUT_ID0:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "IPS_INPUT_ID1:\t\t0x%X\n", v[1]);

	get_values_from_reg(c->reg, 0xC0, 1, v);
	seq_म_लिखो(sf, "IPS_INFO:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xD0, 3, v);
	seq_म_लिखो(sf, "IPS_CONTROL:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "IPS_SIZE:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "IPS_DEPTH:\t\t0x%X\n", v[2]);

	get_values_from_reg(c->reg, 0x130, 12, v);
	क्रम (i = 0; i < 12; i++)
		seq_म_लिखो(sf, "IPS_RGB_RGB_COEFF%u:\t0x%X\n", i, v[i]);

	get_values_from_reg(c->reg, 0x170, 12, v);
	क्रम (i = 0; i < 12; i++)
		seq_म_लिखो(sf, "IPS_RGB_YUV_COEFF%u:\t0x%X\n", i, v[i]);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_improc_funcs = अणु
	.update		= d71_improc_update,
	.disable	= d71_component_disable,
	.dump_रेजिस्टर	= d71_improc_dump,
पूर्ण;

अटल पूर्णांक d71_improc_init(काष्ठा d71_dev *d71,
			   काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_improc *improc;
	u32 pipe_id, comp_id, value;

	get_resources_id(blk->block_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*improc),
				 comp_id,
				 BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_improc_funcs, IPS_NUM_INPUT_IDS,
				 get_valid_inमाला_दो(blk),
				 IPS_NUM_OUTPUT_IDS, reg, "DOU%d_IPS", pipe_id);
	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to add improc component\n");
		वापस PTR_ERR(c);
	पूर्ण

	improc = to_improc(c);
	improc->supported_color_depths = BIT(8) | BIT(10);
	improc->supported_color_क्रमmats = DRM_COLOR_FORMAT_RGB444 |
					  DRM_COLOR_FORMAT_YCRCB444 |
					  DRM_COLOR_FORMAT_YCRCB422;
	value = malidp_पढ़ो32(reg, BLK_INFO);
	अगर (value & IPS_INFO_CHD420)
		improc->supported_color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB420;

	improc->supports_csc = true;
	improc->supports_gamma = true;

	वापस 0;
पूर्ण

अटल व्योम d71_timing_ctrlr_disable(काष्ठा komeda_component *c)
अणु
	malidp_ग_लिखो32_mask(c->reg, BLK_CONTROL, BS_CTRL_EN, 0);
पूर्ण

अटल व्योम d71_timing_ctrlr_update(काष्ठा komeda_component *c,
				    काष्ठा komeda_component_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_st = state->crtc->state;
	काष्ठा drm_display_mode *mode = &crtc_st->adjusted_mode;
	u32 __iomem *reg = c->reg;
	u32 hactive, hfront_porch, hback_porch, hsync_len;
	u32 vactive, vfront_porch, vback_porch, vsync_len;
	u32 value;

	hactive = mode->crtc_hdisplay;
	hfront_porch = mode->crtc_hsync_start - mode->crtc_hdisplay;
	hsync_len = mode->crtc_hsync_end - mode->crtc_hsync_start;
	hback_porch = mode->crtc_htotal - mode->crtc_hsync_end;

	vactive = mode->crtc_vdisplay;
	vfront_porch = mode->crtc_vsync_start - mode->crtc_vdisplay;
	vsync_len = mode->crtc_vsync_end - mode->crtc_vsync_start;
	vback_porch = mode->crtc_vtotal - mode->crtc_vsync_end;

	malidp_ग_लिखो32(reg, BS_ACTIVESIZE, HV_SIZE(hactive, vactive));
	malidp_ग_लिखो32(reg, BS_HINTERVALS, BS_H_INTVALS(hfront_porch,
							hback_porch));
	malidp_ग_लिखो32(reg, BS_VINTERVALS, BS_V_INTVALS(vfront_porch,
							vback_porch));

	value = BS_SYNC_VSW(vsync_len) | BS_SYNC_HSW(hsync_len);
	value |= mode->flags & DRM_MODE_FLAG_PVSYNC ? BS_SYNC_VSP : 0;
	value |= mode->flags & DRM_MODE_FLAG_PHSYNC ? BS_SYNC_HSP : 0;
	malidp_ग_लिखो32(reg, BS_SYNC, value);

	malidp_ग_लिखो32(reg, BS_PROG_LINE, D71_DEFAULT_PREPRETCH_LINE - 1);
	malidp_ग_लिखो32(reg, BS_PREFETCH_LINE, D71_DEFAULT_PREPRETCH_LINE);

	/* configure bs control रेजिस्टर */
	value = BS_CTRL_EN | BS_CTRL_VM;
	अगर (c->pipeline->dual_link) अणु
		malidp_ग_लिखो32(reg, BS_DRIFT_TO, hfront_porch + 16);
		value |= BS_CTRL_DL;
	पूर्ण

	malidp_ग_लिखो32(reg, BLK_CONTROL, value);
पूर्ण

अटल व्योम d71_timing_ctrlr_dump(काष्ठा komeda_component *c,
				  काष्ठा seq_file *sf)
अणु
	u32 v[8], i;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0xC0, 1, v);
	seq_म_लिखो(sf, "BS_INFO:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xD0, 8, v);
	seq_म_लिखो(sf, "BS_CONTROL:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "BS_PROG_LINE:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "BS_PREFETCH_LINE:\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "BS_BG_COLOR:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "BS_ACTIVESIZE:\t\t0x%X\n", v[4]);
	seq_म_लिखो(sf, "BS_HINTERVALS:\t\t0x%X\n", v[5]);
	seq_म_लिखो(sf, "BS_VINTERVALS:\t\t0x%X\n", v[6]);
	seq_म_लिखो(sf, "BS_SYNC:\t\t0x%X\n", v[7]);

	get_values_from_reg(c->reg, 0x100, 3, v);
	seq_म_लिखो(sf, "BS_DRIFT_TO:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "BS_FRAME_TO:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "BS_TE_TO:\t\t0x%X\n", v[2]);

	get_values_from_reg(c->reg, 0x110, 3, v);
	क्रम (i = 0; i < 3; i++)
		seq_म_लिखो(sf, "BS_T%u_INTERVAL:\t\t0x%X\n", i, v[i]);

	get_values_from_reg(c->reg, 0x120, 5, v);
	क्रम (i = 0; i < 2; i++) अणु
		seq_म_लिखो(sf, "BS_CRC%u_LOW:\t\t0x%X\n", i, v[i << 1]);
		seq_म_लिखो(sf, "BS_CRC%u_HIGH:\t\t0x%X\n", i, v[(i << 1) + 1]);
	पूर्ण
	seq_म_लिखो(sf, "BS_USER:\t\t0x%X\n", v[4]);
पूर्ण

अटल स्थिर काष्ठा komeda_component_funcs d71_timing_ctrlr_funcs = अणु
	.update		= d71_timing_ctrlr_update,
	.disable	= d71_timing_ctrlr_disable,
	.dump_रेजिस्टर	= d71_timing_ctrlr_dump,
पूर्ण;

अटल पूर्णांक d71_timing_ctrlr_init(काष्ठा d71_dev *d71,
				 काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_timing_ctrlr *ctrlr;
	u32 pipe_id, comp_id;

	get_resources_id(blk->block_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, माप(*ctrlr),
				 KOMEDA_COMPONENT_TIMING_CTRLR,
				 BLOCK_INFO_INPUT_ID(blk->block_info),
				 &d71_timing_ctrlr_funcs,
				 1, BIT(KOMEDA_COMPONENT_IPS0 + pipe_id),
				 BS_NUM_OUTPUT_IDS, reg, "DOU%d_BS", pipe_id);
	अगर (IS_ERR(c)) अणु
		DRM_ERROR("Failed to add display_ctrl component\n");
		वापस PTR_ERR(c);
	पूर्ण

	ctrlr = to_ctrlr(c);

	ctrlr->supports_dual_link = d71->supports_dual_link;

	वापस 0;
पूर्ण

पूर्णांक d71_probe_block(काष्ठा d71_dev *d71,
		    काष्ठा block_header *blk, u32 __iomem *reg)
अणु
	काष्ठा d71_pipeline *pipe;
	पूर्णांक blk_id = BLOCK_INFO_BLK_ID(blk->block_info);

	पूर्णांक err = 0;

	चयन (BLOCK_INFO_BLK_TYPE(blk->block_info)) अणु
	हाल D71_BLK_TYPE_GCU:
		अवरोध;

	हाल D71_BLK_TYPE_LPU:
		pipe = d71->pipes[blk_id];
		pipe->lpu_addr = reg;
		अवरोध;

	हाल D71_BLK_TYPE_LPU_LAYER:
		err = d71_layer_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_LPU_WB_LAYER:
		err = d71_wb_layer_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_CU:
		pipe = d71->pipes[blk_id];
		pipe->cu_addr = reg;
		err = d71_compiz_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_CU_SCALER:
		err = d71_scaler_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_CU_SPLITTER:
		err = d71_splitter_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_CU_MERGER:
		err = d71_merger_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_DOU:
		pipe = d71->pipes[blk_id];
		pipe->करोu_addr = reg;
		अवरोध;

	हाल D71_BLK_TYPE_DOU_IPS:
		err = d71_improc_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_DOU_FT_COEFF:
		pipe = d71->pipes[blk_id];
		pipe->करोu_ft_coeff_addr = reg;
		अवरोध;

	हाल D71_BLK_TYPE_DOU_BS:
		err = d71_timing_ctrlr_init(d71, blk, reg);
		अवरोध;

	हाल D71_BLK_TYPE_GLB_LT_COEFF:
		अवरोध;

	हाल D71_BLK_TYPE_GLB_SCL_COEFF:
		d71->glb_scl_coeff_addr[blk_id] = reg;
		अवरोध;

	शेष:
		DRM_ERROR("Unknown block (block_info: 0x%x) is found\n",
			  blk->block_info);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम d71_gcu_dump(काष्ठा d71_dev *d71, काष्ठा seq_file *sf)
अणु
	u32 v[5];

	seq_माला_दो(sf, "\n------ GCU ------\n");

	get_values_from_reg(d71->gcu_addr, 0, 3, v);
	seq_म_लिखो(sf, "GLB_ARCH_ID:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "GLB_CORE_ID:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "GLB_CORE_INFO:\t\t0x%X\n", v[2]);

	get_values_from_reg(d71->gcu_addr, 0x10, 1, v);
	seq_म_लिखो(sf, "GLB_IRQ_STATUS:\t\t0x%X\n", v[0]);

	get_values_from_reg(d71->gcu_addr, 0xA0, 5, v);
	seq_म_लिखो(sf, "GCU_IRQ_RAW_STATUS:\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "GCU_IRQ_CLEAR:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "GCU_IRQ_MASK:\t\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "GCU_IRQ_STATUS:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "GCU_STATUS:\t\t0x%X\n", v[4]);

	get_values_from_reg(d71->gcu_addr, 0xD0, 3, v);
	seq_म_लिखो(sf, "GCU_CONTROL:\t\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "GCU_CONFIG_VALID0:\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "GCU_CONFIG_VALID1:\t0x%X\n", v[2]);
पूर्ण

अटल व्योम d71_lpu_dump(काष्ठा d71_pipeline *pipe, काष्ठा seq_file *sf)
अणु
	u32 v[6];

	seq_म_लिखो(sf, "\n------ LPU%d ------\n", pipe->base.id);

	dump_block_header(sf, pipe->lpu_addr);

	get_values_from_reg(pipe->lpu_addr, 0xA0, 6, v);
	seq_म_लिखो(sf, "LPU_IRQ_RAW_STATUS:\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "LPU_IRQ_CLEAR:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "LPU_IRQ_MASK:\t\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "LPU_IRQ_STATUS:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "LPU_STATUS:\t\t0x%X\n", v[4]);
	seq_म_लिखो(sf, "LPU_TBU_STATUS:\t\t0x%X\n", v[5]);

	get_values_from_reg(pipe->lpu_addr, 0xC0, 1, v);
	seq_म_लिखो(sf, "LPU_INFO:\t\t0x%X\n", v[0]);

	get_values_from_reg(pipe->lpu_addr, 0xD0, 3, v);
	seq_म_लिखो(sf, "LPU_RAXI_CONTROL:\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "LPU_WAXI_CONTROL:\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "LPU_TBU_CONTROL:\t0x%X\n", v[2]);
पूर्ण

अटल व्योम d71_करोu_dump(काष्ठा d71_pipeline *pipe, काष्ठा seq_file *sf)
अणु
	u32 v[5];

	seq_म_लिखो(sf, "\n------ DOU%d ------\n", pipe->base.id);

	dump_block_header(sf, pipe->करोu_addr);

	get_values_from_reg(pipe->करोu_addr, 0xA0, 5, v);
	seq_म_लिखो(sf, "DOU_IRQ_RAW_STATUS:\t0x%X\n", v[0]);
	seq_म_लिखो(sf, "DOU_IRQ_CLEAR:\t\t0x%X\n", v[1]);
	seq_म_लिखो(sf, "DOU_IRQ_MASK:\t\t0x%X\n", v[2]);
	seq_म_लिखो(sf, "DOU_IRQ_STATUS:\t\t0x%X\n", v[3]);
	seq_म_लिखो(sf, "DOU_STATUS:\t\t0x%X\n", v[4]);
पूर्ण

अटल व्योम d71_pipeline_dump(काष्ठा komeda_pipeline *pipe, काष्ठा seq_file *sf)
अणु
	काष्ठा d71_pipeline *d71_pipe = to_d71_pipeline(pipe);

	d71_lpu_dump(d71_pipe, sf);
	d71_करोu_dump(d71_pipe, sf);
पूर्ण

स्थिर काष्ठा komeda_pipeline_funcs d71_pipeline_funcs = अणु
	.करोwnscaling_clk_check	= d71_करोwnscaling_clk_check,
	.dump_रेजिस्टर		= d71_pipeline_dump,
पूर्ण;

व्योम d71_dump(काष्ठा komeda_dev *mdev, काष्ठा seq_file *sf)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;

	d71_gcu_dump(d71, sf);
पूर्ण
