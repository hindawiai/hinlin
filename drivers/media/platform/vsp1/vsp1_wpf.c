<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_wpf.c  --  R-Car VSP1 Write Pixel Formatter
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

#घोषणा WPF_GEN2_MAX_WIDTH			2048U
#घोषणा WPF_GEN2_MAX_HEIGHT			2048U
#घोषणा WPF_GEN3_MAX_WIDTH			8190U
#घोषणा WPF_GEN3_MAX_HEIGHT			8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_wpf_ग_लिखो(काष्ठा vsp1_rwpf *wpf,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg + wpf->entity.index * VI6_WPF_OFFSET, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

क्रमागत wpf_flip_ctrl अणु
	WPF_CTRL_VFLIP = 0,
	WPF_CTRL_HFLIP = 1,
पूर्ण;

अटल पूर्णांक vsp1_wpf_set_rotation(काष्ठा vsp1_rwpf *wpf, अचिन्हित पूर्णांक rotation)
अणु
	काष्ठा vsp1_video *video = wpf->video;
	काष्ठा v4l2_mbus_framefmt *sink_क्रमmat;
	काष्ठा v4l2_mbus_framefmt *source_क्रमmat;
	bool rotate;
	पूर्णांक ret = 0;

	/*
	 * Only consider the 0तओ/180तओ from/to 90तओ/270तओ modअगरications, the rest
	 * is taken care of by the flipping configuration.
	 */
	rotate = rotation == 90 || rotation == 270;
	अगर (rotate == wpf->flip.rotate)
		वापस 0;

	/* Changing rotation isn't allowed when buffers are allocated. */
	mutex_lock(&video->lock);

	अगर (vb2_is_busy(&video->queue)) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	sink_क्रमmat = vsp1_entity_get_pad_क्रमmat(&wpf->entity,
						 wpf->entity.config,
						 RWPF_PAD_SINK);
	source_क्रमmat = vsp1_entity_get_pad_क्रमmat(&wpf->entity,
						   wpf->entity.config,
						   RWPF_PAD_SOURCE);

	mutex_lock(&wpf->entity.lock);

	अगर (rotate) अणु
		source_क्रमmat->width = sink_क्रमmat->height;
		source_क्रमmat->height = sink_क्रमmat->width;
	पूर्ण अन्यथा अणु
		source_क्रमmat->width = sink_क्रमmat->width;
		source_क्रमmat->height = sink_क्रमmat->height;
	पूर्ण

	wpf->flip.rotate = rotate;

	mutex_unlock(&wpf->entity.lock);

करोne:
	mutex_unlock(&video->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vsp1_wpf_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_rwpf *wpf =
		container_of(ctrl->handler, काष्ठा vsp1_rwpf, ctrls);
	अचिन्हित पूर्णांक rotation;
	u32 flip = 0;
	पूर्णांक ret;

	/* Update the rotation. */
	rotation = wpf->flip.ctrls.rotate ? wpf->flip.ctrls.rotate->val : 0;
	ret = vsp1_wpf_set_rotation(wpf, rotation);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Compute the flip value resulting from all three controls, with
	 * rotation by 180तओ flipping the image in both directions. Store the
	 * result in the pending flip field क्रम the next frame that will be
	 * processed.
	 */
	अगर (wpf->flip.ctrls.vflip->val)
		flip |= BIT(WPF_CTRL_VFLIP);

	अगर (wpf->flip.ctrls.hflip && wpf->flip.ctrls.hflip->val)
		flip |= BIT(WPF_CTRL_HFLIP);

	अगर (rotation == 180 || rotation == 270)
		flip ^= BIT(WPF_CTRL_VFLIP) | BIT(WPF_CTRL_HFLIP);

	spin_lock_irq(&wpf->flip.lock);
	wpf->flip.pending = flip;
	spin_unlock_irq(&wpf->flip.lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vsp1_wpf_ctrl_ops = अणु
	.s_ctrl = vsp1_wpf_s_ctrl,
पूर्ण;

अटल पूर्णांक wpf_init_controls(काष्ठा vsp1_rwpf *wpf)
अणु
	काष्ठा vsp1_device *vsp1 = wpf->entity.vsp1;
	अचिन्हित पूर्णांक num_flip_ctrls;

	spin_lock_init(&wpf->flip.lock);

	अगर (wpf->entity.index != 0) अणु
		/* Only WPF0 supports flipping. */
		num_flip_ctrls = 0;
	पूर्ण अन्यथा अगर (vsp1_feature(vsp1, VSP1_HAS_WPF_HFLIP)) अणु
		/*
		 * When horizontal flip is supported the WPF implements three
		 * controls (horizontal flip, vertical flip and rotation).
		 */
		num_flip_ctrls = 3;
	पूर्ण अन्यथा अगर (vsp1_feature(vsp1, VSP1_HAS_WPF_VFLIP)) अणु
		/*
		 * When only vertical flip is supported the WPF implements a
		 * single control (vertical flip).
		 */
		num_flip_ctrls = 1;
	पूर्ण अन्यथा अणु
		/* Otherwise flipping is not supported. */
		num_flip_ctrls = 0;
	पूर्ण

	vsp1_rwpf_init_ctrls(wpf, num_flip_ctrls);

	अगर (num_flip_ctrls >= 1) अणु
		wpf->flip.ctrls.vflip =
			v4l2_ctrl_new_std(&wpf->ctrls, &vsp1_wpf_ctrl_ops,
					  V4L2_CID_VFLIP, 0, 1, 1, 0);
	पूर्ण

	अगर (num_flip_ctrls == 3) अणु
		wpf->flip.ctrls.hflip =
			v4l2_ctrl_new_std(&wpf->ctrls, &vsp1_wpf_ctrl_ops,
					  V4L2_CID_HFLIP, 0, 1, 1, 0);
		wpf->flip.ctrls.rotate =
			v4l2_ctrl_new_std(&wpf->ctrls, &vsp1_wpf_ctrl_ops,
					  V4L2_CID_ROTATE, 0, 270, 90, 0);
		v4l2_ctrl_cluster(3, &wpf->flip.ctrls.vflip);
	पूर्ण

	अगर (wpf->ctrls.error) अणु
		dev_err(vsp1->dev, "wpf%u: failed to initialize controls\n",
			wpf->entity.index);
		वापस wpf->ctrls.error;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Core Operations
 */

अटल पूर्णांक wpf_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा vsp1_rwpf *wpf = to_rwpf(subdev);
	काष्ठा vsp1_device *vsp1 = wpf->entity.vsp1;

	अगर (enable)
		वापस 0;

	/*
	 * Write to रेजिस्टरs directly when stopping the stream as there will be
	 * no pipeline run to apply the display list.
	 */
	vsp1_ग_लिखो(vsp1, VI6_WPF_IRQ_ENB(wpf->entity.index), 0);
	vsp1_ग_लिखो(vsp1, wpf->entity.index * VI6_WPF_OFFSET +
		   VI6_WPF_SRCRPF, 0);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर काष्ठा v4l2_subdev_video_ops wpf_video_ops = अणु
	.s_stream = wpf_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops wpf_ops = अणु
	.video	= &wpf_video_ops,
	.pad    = &vsp1_rwpf_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम vsp1_wpf_destroy(काष्ठा vsp1_entity *entity)
अणु
	काष्ठा vsp1_rwpf *wpf = entity_to_rwpf(entity);

	vsp1_dlm_destroy(wpf->dlm);
पूर्ण

अटल पूर्णांक wpf_configure_ग_लिखोback_chain(काष्ठा vsp1_rwpf *wpf,
					 काष्ठा vsp1_dl_list *dl)
अणु
	अचिन्हित पूर्णांक index = wpf->entity.index;
	काष्ठा vsp1_dl_list *dl_next;
	काष्ठा vsp1_dl_body *dlb;

	dl_next = vsp1_dl_list_get(wpf->dlm);
	अगर (!dl_next) अणु
		dev_err(wpf->entity.vsp1->dev,
			"Failed to obtain a dl list, disabling writeback\n");
		वापस -ENOMEM;
	पूर्ण

	dlb = vsp1_dl_list_get_body0(dl_next);
	vsp1_dl_body_ग_लिखो(dlb, VI6_WPF_WRBCK_CTRL(index), 0);
	vsp1_dl_list_add_chain(dl, dl_next);

	वापस 0;
पूर्ण

अटल व्योम wpf_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_rwpf *wpf = to_rwpf(&entity->subdev);
	काष्ठा vsp1_device *vsp1 = wpf->entity.vsp1;
	स्थिर काष्ठा v4l2_mbus_framefmt *source_क्रमmat;
	स्थिर काष्ठा v4l2_mbus_framefmt *sink_क्रमmat;
	अचिन्हित पूर्णांक index = wpf->entity.index;
	अचिन्हित पूर्णांक i;
	u32 outfmt = 0;
	u32 srcrpf = 0;
	पूर्णांक ret;

	sink_क्रमmat = vsp1_entity_get_pad_क्रमmat(&wpf->entity,
						 wpf->entity.config,
						 RWPF_PAD_SINK);
	source_क्रमmat = vsp1_entity_get_pad_क्रमmat(&wpf->entity,
						   wpf->entity.config,
						   RWPF_PAD_SOURCE);

	/* Format */
	अगर (!pipe->lअगर || wpf->ग_लिखोback) अणु
		स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &wpf->क्रमmat;
		स्थिर काष्ठा vsp1_क्रमmat_info *fmtinfo = wpf->fmtinfo;

		outfmt = fmtinfo->hwfmt << VI6_WPF_OUTFMT_WRFMT_SHIFT;

		अगर (wpf->flip.rotate)
			outfmt |= VI6_WPF_OUTFMT_ROT;

		अगर (fmtinfo->alpha)
			outfmt |= VI6_WPF_OUTFMT_PXA;
		अगर (fmtinfo->swap_yc)
			outfmt |= VI6_WPF_OUTFMT_SPYCS;
		अगर (fmtinfo->swap_uv)
			outfmt |= VI6_WPF_OUTFMT_SPUVS;

		/* Destination stride and byte swapping. */
		vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_DSTM_STRIDE_Y,
			       क्रमmat->plane_fmt[0].bytesperline);
		अगर (क्रमmat->num_planes > 1)
			vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_DSTM_STRIDE_C,
				       क्रमmat->plane_fmt[1].bytesperline);

		vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_DSWAP, fmtinfo->swap);

		अगर (vsp1_feature(vsp1, VSP1_HAS_WPF_HFLIP) && index == 0)
			vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_ROT_CTRL,
				       VI6_WPF_ROT_CTRL_LN16 |
				       (256 << VI6_WPF_ROT_CTRL_LMEM_WD_SHIFT));
	पूर्ण

	अगर (sink_क्रमmat->code != source_क्रमmat->code)
		outfmt |= VI6_WPF_OUTFMT_CSC;

	wpf->outfmt = outfmt;

	vsp1_dl_body_ग_लिखो(dlb, VI6_DPR_WPF_FPORCH(index),
			   VI6_DPR_WPF_FPORCH_FP_WPFN);

	/*
	 * Sources. If the pipeline has a single input and BRx is not used,
	 * configure it as the master layer. Otherwise configure all
	 * inमाला_दो as sub-layers and select the भव RPF as the master
	 * layer.
	 */
	क्रम (i = 0; i < vsp1->info->rpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *input = pipe->inमाला_दो[i];

		अगर (!input)
			जारी;

		srcrpf |= (!pipe->brx && pipe->num_inमाला_दो == 1)
			? VI6_WPF_SRCRPF_RPF_ACT_MST(input->entity.index)
			: VI6_WPF_SRCRPF_RPF_ACT_SUB(input->entity.index);
	पूर्ण

	अगर (pipe->brx)
		srcrpf |= pipe->brx->type == VSP1_ENTITY_BRU
			? VI6_WPF_SRCRPF_VIRACT_MST
			: VI6_WPF_SRCRPF_VIRACT2_MST;

	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_SRCRPF, srcrpf);

	/* Enable पूर्णांकerrupts. */
	vsp1_dl_body_ग_लिखो(dlb, VI6_WPF_IRQ_STA(index), 0);
	vsp1_dl_body_ग_लिखो(dlb, VI6_WPF_IRQ_ENB(index),
			   VI6_WFP_IRQ_ENB_DFEE);

	/*
	 * Configure ग_लिखोback क्रम display pipelines (the wpf ग_लिखोback flag is
	 * never set क्रम memory-to-memory pipelines). Start by adding a chained
	 * display list to disable ग_लिखोback after a single frame, and process
	 * to enable ग_लिखोback. If the display list allocation fails करोn't
	 * enable ग_लिखोback as we wouldn't be able to safely disable it,
	 * resulting in possible memory corruption.
	 */
	अगर (wpf->ग_लिखोback) अणु
		ret = wpf_configure_ग_लिखोback_chain(wpf, dl);
		अगर (ret < 0)
			wpf->ग_लिखोback = false;
	पूर्ण

	vsp1_dl_body_ग_लिखो(dlb, VI6_WPF_WRBCK_CTRL(index),
			   wpf->ग_लिखोback ? VI6_WPF_WRBCK_CTRL_WBMD : 0);
पूर्ण

अटल व्योम wpf_configure_frame(काष्ठा vsp1_entity *entity,
				काष्ठा vsp1_pipeline *pipe,
				काष्ठा vsp1_dl_list *dl,
				काष्ठा vsp1_dl_body *dlb)
अणु
	स्थिर अचिन्हित पूर्णांक mask = BIT(WPF_CTRL_VFLIP)
				| BIT(WPF_CTRL_HFLIP);
	काष्ठा vsp1_rwpf *wpf = to_rwpf(&entity->subdev);
	अचिन्हित दीर्घ flags;
	u32 outfmt;

	spin_lock_irqsave(&wpf->flip.lock, flags);
	wpf->flip.active = (wpf->flip.active & ~mask)
			 | (wpf->flip.pending & mask);
	spin_unlock_irqrestore(&wpf->flip.lock, flags);

	outfmt = (wpf->alpha << VI6_WPF_OUTFMT_PDV_SHIFT) | wpf->outfmt;

	अगर (wpf->flip.active & BIT(WPF_CTRL_VFLIP))
		outfmt |= VI6_WPF_OUTFMT_FLP;
	अगर (wpf->flip.active & BIT(WPF_CTRL_HFLIP))
		outfmt |= VI6_WPF_OUTFMT_HFLP;

	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_OUTFMT, outfmt);
पूर्ण

अटल व्योम wpf_configure_partition(काष्ठा vsp1_entity *entity,
				    काष्ठा vsp1_pipeline *pipe,
				    काष्ठा vsp1_dl_list *dl,
				    काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_rwpf *wpf = to_rwpf(&entity->subdev);
	काष्ठा vsp1_device *vsp1 = wpf->entity.vsp1;
	काष्ठा vsp1_rwpf_memory mem = wpf->mem;
	स्थिर काष्ठा v4l2_mbus_framefmt *sink_क्रमmat;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &wpf->क्रमmat;
	स्थिर काष्ठा vsp1_क्रमmat_info *fmtinfo = wpf->fmtinfo;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक left;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक flip;
	अचिन्हित पूर्णांक i;

	sink_क्रमmat = vsp1_entity_get_pad_क्रमmat(&wpf->entity,
						 wpf->entity.config,
						 RWPF_PAD_SINK);
	width = sink_क्रमmat->width;
	height = sink_क्रमmat->height;
	left = 0;

	/*
	 * Cropping. The partition algorithm can split the image पूर्णांकo
	 * multiple slices.
	 */
	अगर (pipe->partitions > 1) अणु
		width = pipe->partition->wpf.width;
		left = pipe->partition->wpf.left;
	पूर्ण

	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_HSZCLIP, VI6_WPF_SZCLIP_EN |
		       (0 << VI6_WPF_SZCLIP_OFST_SHIFT) |
		       (width << VI6_WPF_SZCLIP_SIZE_SHIFT));
	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_VSZCLIP, VI6_WPF_SZCLIP_EN |
		       (0 << VI6_WPF_SZCLIP_OFST_SHIFT) |
		       (height << VI6_WPF_SZCLIP_SIZE_SHIFT));

	/*
	 * For display pipelines without ग_लिखोback enabled there's no memory
	 * address to configure, वापस now.
	 */
	अगर (pipe->lअगर && !wpf->ग_लिखोback)
		वापस;

	/*
	 * Update the memory offsets based on flipping configuration.
	 * The destination addresses poपूर्णांक to the locations where the
	 * VSP starts writing to memory, which can be any corner of the
	 * image depending on the combination of flipping and rotation.
	 */

	/*
	 * First take the partition left coordinate पूर्णांकo account.
	 * Compute the offset to order the partitions correctly on the
	 * output based on whether flipping is enabled. Consider
	 * horizontal flipping when rotation is disabled but vertical
	 * flipping when rotation is enabled, as rotating the image
	 * चयनes the horizontal and vertical directions. The offset
	 * is applied horizontally or vertically accordingly.
	 */
	flip = wpf->flip.active;

	अगर (flip & BIT(WPF_CTRL_HFLIP) && !wpf->flip.rotate)
		offset = क्रमmat->width - left - width;
	अन्यथा अगर (flip & BIT(WPF_CTRL_VFLIP) && wpf->flip.rotate)
		offset = क्रमmat->height - left - width;
	अन्यथा
		offset = left;

	क्रम (i = 0; i < क्रमmat->num_planes; ++i) अणु
		अचिन्हित पूर्णांक hsub = i > 0 ? fmtinfo->hsub : 1;
		अचिन्हित पूर्णांक vsub = i > 0 ? fmtinfo->vsub : 1;

		अगर (wpf->flip.rotate)
			mem.addr[i] += offset / vsub
				     * क्रमmat->plane_fmt[i].bytesperline;
		अन्यथा
			mem.addr[i] += offset / hsub
				     * fmtinfo->bpp[i] / 8;
	पूर्ण

	अगर (flip & BIT(WPF_CTRL_VFLIP)) अणु
		/*
		 * When rotating the output (after rotation) image
		 * height is equal to the partition width (beक्रमe
		 * rotation). Otherwise it is equal to the output
		 * image height.
		 */
		अगर (wpf->flip.rotate)
			height = width;
		अन्यथा
			height = क्रमmat->height;

		mem.addr[0] += (height - 1)
			     * क्रमmat->plane_fmt[0].bytesperline;

		अगर (क्रमmat->num_planes > 1) अणु
			offset = (height / fmtinfo->vsub - 1)
			       * क्रमmat->plane_fmt[1].bytesperline;
			mem.addr[1] += offset;
			mem.addr[2] += offset;
		पूर्ण
	पूर्ण

	अगर (wpf->flip.rotate && !(flip & BIT(WPF_CTRL_HFLIP))) अणु
		अचिन्हित पूर्णांक hoffset = max(0, (पूर्णांक)क्रमmat->width - 16);

		/*
		 * Compute the output coordinate. The partition
		 * horizontal (left) offset becomes a vertical offset.
		 */
		क्रम (i = 0; i < क्रमmat->num_planes; ++i) अणु
			अचिन्हित पूर्णांक hsub = i > 0 ? fmtinfo->hsub : 1;

			mem.addr[i] += hoffset / hsub
				     * fmtinfo->bpp[i] / 8;
		पूर्ण
	पूर्ण

	/*
	 * On Gen3 hardware the SPUVS bit has no effect on 3-planar
	 * क्रमmats. Swap the U and V planes manually in that हाल.
	 */
	अगर (vsp1->info->gen == 3 && क्रमmat->num_planes == 3 &&
	    fmtinfo->swap_uv)
		swap(mem.addr[1], mem.addr[2]);

	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_DSTM_ADDR_Y, mem.addr[0]);
	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_DSTM_ADDR_C0, mem.addr[1]);
	vsp1_wpf_ग_लिखो(wpf, dlb, VI6_WPF_DSTM_ADDR_C1, mem.addr[2]);

	/*
	 * Writeback operates in single-shot mode and lasts क्रम a single frame,
	 * reset the ग_लिखोback flag to false क्रम the next frame.
	 */
	wpf->ग_लिखोback = false;
पूर्ण

अटल अचिन्हित पूर्णांक wpf_max_width(काष्ठा vsp1_entity *entity,
				  काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_rwpf *wpf = to_rwpf(&entity->subdev);

	वापस wpf->flip.rotate ? 256 : wpf->max_width;
पूर्ण

अटल व्योम wpf_partition(काष्ठा vsp1_entity *entity,
			  काष्ठा vsp1_pipeline *pipe,
			  काष्ठा vsp1_partition *partition,
			  अचिन्हित पूर्णांक partition_idx,
			  काष्ठा vsp1_partition_winकरोw *winकरोw)
अणु
	partition->wpf = *winकरोw;
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations wpf_entity_ops = अणु
	.destroy = vsp1_wpf_destroy,
	.configure_stream = wpf_configure_stream,
	.configure_frame = wpf_configure_frame,
	.configure_partition = wpf_configure_partition,
	.max_width = wpf_max_width,
	.partition = wpf_partition,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_rwpf *vsp1_wpf_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vsp1_rwpf *wpf;
	अक्षर name[6];
	पूर्णांक ret;

	wpf = devm_kzalloc(vsp1->dev, माप(*wpf), GFP_KERNEL);
	अगर (wpf == शून्य)
		वापस ERR_PTR(-ENOMEM);

	अगर (vsp1->info->gen == 2) अणु
		wpf->max_width = WPF_GEN2_MAX_WIDTH;
		wpf->max_height = WPF_GEN2_MAX_HEIGHT;
	पूर्ण अन्यथा अणु
		wpf->max_width = WPF_GEN3_MAX_WIDTH;
		wpf->max_height = WPF_GEN3_MAX_HEIGHT;
	पूर्ण

	wpf->entity.ops = &wpf_entity_ops;
	wpf->entity.type = VSP1_ENTITY_WPF;
	wpf->entity.index = index;

	प्र_लिखो(name, "wpf.%u", index);
	ret = vsp1_entity_init(vsp1, &wpf->entity, name, 2, &wpf_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/* Initialize the display list manager. */
	wpf->dlm = vsp1_dlm_create(vsp1, index, 64);
	अगर (!wpf->dlm) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* Initialize the control handler. */
	ret = wpf_init_controls(wpf);
	अगर (ret < 0) अणु
		dev_err(vsp1->dev, "wpf%u: failed to initialize controls\n",
			index);
		जाओ error;
	पूर्ण

	v4l2_ctrl_handler_setup(&wpf->ctrls);

	वापस wpf;

error:
	vsp1_entity_destroy(&wpf->entity);
	वापस ERR_PTR(ret);
पूर्ण
