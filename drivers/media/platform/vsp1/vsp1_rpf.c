<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_rpf.c  --  R-Car VSP1 Read Pixel Formatter
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_video.h"

#घोषणा RPF_MAX_WIDTH				8190
#घोषणा RPF_MAX_HEIGHT				8190

/* Pre extended display list command data काष्ठाure. */
काष्ठा vsp1_extcmd_स्वतः_fld_body अणु
	u32 top_y0;
	u32 bottom_y0;
	u32 top_c0;
	u32 bottom_c0;
	u32 top_c1;
	u32 bottom_c1;
	u32 reserved0;
	u32 reserved1;
पूर्ण __packed;

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_rpf_ग_लिखो(काष्ठा vsp1_rwpf *rpf,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg + rpf->entity.index * VI6_RPF_OFFSET,
			       data);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर काष्ठा v4l2_subdev_ops rpf_ops = अणु
	.pad    = &vsp1_rwpf_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम rpf_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_rwpf *rpf = to_rwpf(&entity->subdev);
	स्थिर काष्ठा vsp1_क्रमmat_info *fmtinfo = rpf->fmtinfo;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &rpf->क्रमmat;
	स्थिर काष्ठा v4l2_mbus_framefmt *source_क्रमmat;
	स्थिर काष्ठा v4l2_mbus_framefmt *sink_क्रमmat;
	अचिन्हित पूर्णांक left = 0;
	अचिन्हित पूर्णांक top = 0;
	u32 pstride;
	u32 infmt;

	/* Stride */
	pstride = क्रमmat->plane_fmt[0].bytesperline
		<< VI6_RPF_SRCM_PSTRIDE_Y_SHIFT;
	अगर (क्रमmat->num_planes > 1)
		pstride |= क्रमmat->plane_fmt[1].bytesperline
			<< VI6_RPF_SRCM_PSTRIDE_C_SHIFT;

	/*
	 * pstride has both STRIDE_Y and STRIDE_C, but multiplying the whole
	 * of pstride by 2 is conveniently OK here as we are multiplying both
	 * values.
	 */
	अगर (pipe->पूर्णांकerlaced)
		pstride *= 2;

	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_SRCM_PSTRIDE, pstride);

	/* Format */
	sink_क्रमmat = vsp1_entity_get_pad_क्रमmat(&rpf->entity,
						 rpf->entity.config,
						 RWPF_PAD_SINK);
	source_क्रमmat = vsp1_entity_get_pad_क्रमmat(&rpf->entity,
						   rpf->entity.config,
						   RWPF_PAD_SOURCE);

	infmt = VI6_RPF_INFMT_CIPM
	      | (fmtinfo->hwfmt << VI6_RPF_INFMT_RDFMT_SHIFT);

	अगर (fmtinfo->swap_yc)
		infmt |= VI6_RPF_INFMT_SPYCS;
	अगर (fmtinfo->swap_uv)
		infmt |= VI6_RPF_INFMT_SPUVS;

	अगर (sink_क्रमmat->code != source_क्रमmat->code)
		infmt |= VI6_RPF_INFMT_CSC;

	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_INFMT, infmt);
	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_DSWAP, fmtinfo->swap);

	/* Output location. */
	अगर (pipe->brx) अणु
		स्थिर काष्ठा v4l2_rect *compose;

		compose = vsp1_entity_get_pad_selection(pipe->brx,
							pipe->brx->config,
							rpf->brx_input,
							V4L2_SEL_TGT_COMPOSE);
		left = compose->left;
		top = compose->top;
	पूर्ण

	अगर (pipe->पूर्णांकerlaced)
		top /= 2;

	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_LOC,
		       (left << VI6_RPF_LOC_HCOORD_SHIFT) |
		       (top << VI6_RPF_LOC_VCOORD_SHIFT));

	/*
	 * On Gen2 use the alpha channel (extended to 8 bits) when available or
	 * a fixed alpha value set through the V4L2_CID_ALPHA_COMPONENT control
	 * otherwise.
	 *
	 * The Gen3 RPF has extended alpha capability and can both multiply the
	 * alpha channel by a fixed global alpha value, and multiply the pixel
	 * components to convert the input to premultiplied alpha.
	 *
	 * As alpha premultiplication is available in the BRx क्रम both Gen2 and
	 * Gen3 we handle it there and use the Gen3 alpha multiplier क्रम global
	 * alpha multiplication only. This however prevents conversion to
	 * premultiplied alpha अगर no BRx is present in the pipeline. If that use
	 * हाल turns out to be useful we will revisit the implementation (क्रम
	 * Gen3 only).
	 *
	 * We enable alpha multiplication on Gen3 using the fixed alpha value
	 * set through the V4L2_CID_ALPHA_COMPONENT control when the input
	 * contains an alpha channel. On Gen2 the global alpha is ignored in
	 * that हाल.
	 *
	 * In all हालs, disable color keying.
	 */
	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_ALPH_SEL, VI6_RPF_ALPH_SEL_AEXT_EXT |
		       (fmtinfo->alpha ? VI6_RPF_ALPH_SEL_ASEL_PACKED
				       : VI6_RPF_ALPH_SEL_ASEL_FIXED));

	अगर (entity->vsp1->info->gen == 3) अणु
		u32 mult;

		अगर (fmtinfo->alpha) अणु
			/*
			 * When the input contains an alpha channel enable the
			 * alpha multiplier. If the input is premultiplied we
			 * need to multiply both the alpha channel and the pixel
			 * components by the global alpha value to keep them
			 * premultiplied. Otherwise multiply the alpha channel
			 * only.
			 */
			bool premultiplied = क्रमmat->flags
					   & V4L2_PIX_FMT_FLAG_PREMUL_ALPHA;

			mult = VI6_RPF_MULT_ALPHA_A_MMD_RATIO
			     | (premultiplied ?
				VI6_RPF_MULT_ALPHA_P_MMD_RATIO :
				VI6_RPF_MULT_ALPHA_P_MMD_NONE);
		पूर्ण अन्यथा अणु
			/*
			 * When the input करोesn't contain an alpha channel the
			 * global alpha value is applied in the unpacking unit,
			 * the alpha multiplier isn't needed and must be
			 * disabled.
			 */
			mult = VI6_RPF_MULT_ALPHA_A_MMD_NONE
			     | VI6_RPF_MULT_ALPHA_P_MMD_NONE;
		पूर्ण

		rpf->mult_alpha = mult;
	पूर्ण

	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_MSK_CTRL, 0);
	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_CKEY_CTRL, 0);

पूर्ण

अटल व्योम vsp1_rpf_configure_स्वतःfld(काष्ठा vsp1_rwpf *rpf,
				       काष्ठा vsp1_dl_list *dl)
अणु
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &rpf->क्रमmat;
	काष्ठा vsp1_dl_ext_cmd *cmd;
	काष्ठा vsp1_extcmd_स्वतः_fld_body *स्वतः_fld;
	u32 offset_y, offset_c;

	cmd = vsp1_dl_get_pre_cmd(dl);
	अगर (WARN_ONCE(!cmd, "Failed to obtain an autofld cmd"))
		वापस;

	/* Re-index our स्वतः_fld to match the current RPF. */
	स्वतः_fld = cmd->data;
	स्वतः_fld = &स्वतः_fld[rpf->entity.index];

	स्वतः_fld->top_y0 = rpf->mem.addr[0];
	स्वतः_fld->top_c0 = rpf->mem.addr[1];
	स्वतः_fld->top_c1 = rpf->mem.addr[2];

	offset_y = क्रमmat->plane_fmt[0].bytesperline;
	offset_c = क्रमmat->plane_fmt[1].bytesperline;

	स्वतः_fld->bottom_y0 = rpf->mem.addr[0] + offset_y;
	स्वतः_fld->bottom_c0 = rpf->mem.addr[1] + offset_c;
	स्वतः_fld->bottom_c1 = rpf->mem.addr[2] + offset_c;

	cmd->flags |= VI6_DL_EXT_AUTOFLD_INT | BIT(16 + rpf->entity.index);
पूर्ण

अटल व्योम rpf_configure_frame(काष्ठा vsp1_entity *entity,
				काष्ठा vsp1_pipeline *pipe,
				काष्ठा vsp1_dl_list *dl,
				काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_rwpf *rpf = to_rwpf(&entity->subdev);

	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_VRTCOL_SET,
		       rpf->alpha << VI6_RPF_VRTCOL_SET_LAYA_SHIFT);
	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_MULT_ALPHA, rpf->mult_alpha |
		       (rpf->alpha << VI6_RPF_MULT_ALPHA_RATIO_SHIFT));

	vsp1_pipeline_propagate_alpha(pipe, dlb, rpf->alpha);
पूर्ण

अटल व्योम rpf_configure_partition(काष्ठा vsp1_entity *entity,
				    काष्ठा vsp1_pipeline *pipe,
				    काष्ठा vsp1_dl_list *dl,
				    काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_rwpf *rpf = to_rwpf(&entity->subdev);
	काष्ठा vsp1_rwpf_memory mem = rpf->mem;
	काष्ठा vsp1_device *vsp1 = rpf->entity.vsp1;
	स्थिर काष्ठा vsp1_क्रमmat_info *fmtinfo = rpf->fmtinfo;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &rpf->क्रमmat;
	काष्ठा v4l2_rect crop;

	/*
	 * Source size and crop offsets.
	 *
	 * The crop offsets correspond to the location of the crop
	 * rectangle top left corner in the plane buffer. Only two
	 * offsets are needed, as planes 2 and 3 always have identical
	 * strides.
	 */
	crop = *vsp1_rwpf_get_crop(rpf, rpf->entity.config);

	/*
	 * Partition Algorithm Control
	 *
	 * The partition algorithm can split this frame पूर्णांकo multiple
	 * slices. We must scale our partition winकरोw based on the pipe
	 * configuration to match the destination partition winकरोw.
	 * To achieve this, we adjust our crop to provide a 'sub-crop'
	 * matching the expected partition winकरोw. Only 'left' and
	 * 'width' need to be adjusted.
	 */
	अगर (pipe->partitions > 1) अणु
		crop.width = pipe->partition->rpf.width;
		crop.left += pipe->partition->rpf.left;
	पूर्ण

	अगर (pipe->पूर्णांकerlaced) अणु
		crop.height = round_करोwn(crop.height / 2, fmtinfo->vsub);
		crop.top = round_करोwn(crop.top / 2, fmtinfo->vsub);
	पूर्ण

	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_SRC_BSIZE,
		       (crop.width << VI6_RPF_SRC_BSIZE_BHSIZE_SHIFT) |
		       (crop.height << VI6_RPF_SRC_BSIZE_BVSIZE_SHIFT));
	vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_SRC_ESIZE,
		       (crop.width << VI6_RPF_SRC_ESIZE_EHSIZE_SHIFT) |
		       (crop.height << VI6_RPF_SRC_ESIZE_EVSIZE_SHIFT));

	mem.addr[0] += crop.top * क्रमmat->plane_fmt[0].bytesperline
		     + crop.left * fmtinfo->bpp[0] / 8;

	अगर (क्रमmat->num_planes > 1) अणु
		अचिन्हित पूर्णांक offset;

		offset = crop.top * क्रमmat->plane_fmt[1].bytesperline
		       + crop.left / fmtinfo->hsub
		       * fmtinfo->bpp[1] / 8;
		mem.addr[1] += offset;
		mem.addr[2] += offset;
	पूर्ण

	/*
	 * On Gen3 hardware the SPUVS bit has no effect on 3-planar
	 * क्रमmats. Swap the U and V planes manually in that हाल.
	 */
	अगर (vsp1->info->gen == 3 && क्रमmat->num_planes == 3 &&
	    fmtinfo->swap_uv)
		swap(mem.addr[1], mem.addr[2]);

	/*
	 * Interlaced pipelines will use the extended pre-cmd to process
	 * SRCM_ADDR_अणुY,C0,C1पूर्ण.
	 */
	अगर (pipe->पूर्णांकerlaced) अणु
		vsp1_rpf_configure_स्वतःfld(rpf, dl);
	पूर्ण अन्यथा अणु
		vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_SRCM_ADDR_Y, mem.addr[0]);
		vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_SRCM_ADDR_C0, mem.addr[1]);
		vsp1_rpf_ग_लिखो(rpf, dlb, VI6_RPF_SRCM_ADDR_C1, mem.addr[2]);
	पूर्ण
पूर्ण

अटल व्योम rpf_partition(काष्ठा vsp1_entity *entity,
			  काष्ठा vsp1_pipeline *pipe,
			  काष्ठा vsp1_partition *partition,
			  अचिन्हित पूर्णांक partition_idx,
			  काष्ठा vsp1_partition_winकरोw *winकरोw)
अणु
	partition->rpf = *winकरोw;
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations rpf_entity_ops = अणु
	.configure_stream = rpf_configure_stream,
	.configure_frame = rpf_configure_frame,
	.configure_partition = rpf_configure_partition,
	.partition = rpf_partition,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_rwpf *vsp1_rpf_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vsp1_rwpf *rpf;
	अक्षर name[6];
	पूर्णांक ret;

	rpf = devm_kzalloc(vsp1->dev, माप(*rpf), GFP_KERNEL);
	अगर (rpf == शून्य)
		वापस ERR_PTR(-ENOMEM);

	rpf->max_width = RPF_MAX_WIDTH;
	rpf->max_height = RPF_MAX_HEIGHT;

	rpf->entity.ops = &rpf_entity_ops;
	rpf->entity.type = VSP1_ENTITY_RPF;
	rpf->entity.index = index;

	प्र_लिखो(name, "rpf.%u", index);
	ret = vsp1_entity_init(vsp1, &rpf->entity, name, 2, &rpf_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/* Initialize the control handler. */
	ret = vsp1_rwpf_init_ctrls(rpf, 0);
	अगर (ret < 0) अणु
		dev_err(vsp1->dev, "rpf%u: failed to initialize controls\n",
			index);
		जाओ error;
	पूर्ण

	v4l2_ctrl_handler_setup(&rpf->ctrls);

	वापस rpf;

error:
	vsp1_entity_destroy(&rpf->entity);
	वापस ERR_PTR(ret);
पूर्ण
