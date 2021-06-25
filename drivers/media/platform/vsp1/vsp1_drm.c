<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_drm.c  --  R-Car VSP1 DRM/KMS Interface
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/vsp1.h>

#समावेश "vsp1.h"
#समावेश "vsp1_brx.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_drm.h"
#समावेश "vsp1_lif.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_uif.h"

#घोषणा BRX_NAME(e)	(e)->type == VSP1_ENTITY_BRU ? "BRU" : "BRS"

/* -----------------------------------------------------------------------------
 * Interrupt Handling
 */

अटल व्योम vsp1_du_pipeline_frame_end(काष्ठा vsp1_pipeline *pipe,
				       अचिन्हित पूर्णांक completion)
अणु
	काष्ठा vsp1_drm_pipeline *drm_pipe = to_vsp1_drm_pipeline(pipe);

	अगर (drm_pipe->du_complete) अणु
		काष्ठा vsp1_entity *uअगर = drm_pipe->uअगर;
		अचिन्हित पूर्णांक status = completion
				    & (VSP1_DU_STATUS_COMPLETE |
				       VSP1_DU_STATUS_WRITEBACK);
		u32 crc;

		crc = uअगर ? vsp1_uअगर_get_crc(to_uअगर(&uअगर->subdev)) : 0;
		drm_pipe->du_complete(drm_pipe->du_निजी, status, crc);
	पूर्ण

	अगर (completion & VSP1_DL_FRAME_END_INTERNAL) अणु
		drm_pipe->क्रमce_brx_release = false;
		wake_up(&drm_pipe->रुको_queue);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Pipeline Configuration
 */

/*
 * Insert the UIF in the pipeline between the prev and next entities. If no UIF
 * is available connect the two entities directly.
 */
अटल पूर्णांक vsp1_du_insert_uअगर(काष्ठा vsp1_device *vsp1,
			      काष्ठा vsp1_pipeline *pipe,
			      काष्ठा vsp1_entity *uअगर,
			      काष्ठा vsp1_entity *prev, अचिन्हित पूर्णांक prev_pad,
			      काष्ठा vsp1_entity *next, अचिन्हित पूर्णांक next_pad)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	पूर्णांक ret;

	अगर (!uअगर) अणु
		/*
		 * If there's no UIF to be inserted, connect the previous and
		 * next entities directly.
		 */
		prev->sink = next;
		prev->sink_pad = next_pad;
		वापस 0;
	पूर्ण

	prev->sink = uअगर;
	prev->sink_pad = UIF_PAD_SINK;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.pad = prev_pad;

	ret = v4l2_subdev_call(&prev->subdev, pad, get_fmt, शून्य, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	क्रमmat.pad = UIF_PAD_SINK;

	ret = v4l2_subdev_call(&uअगर->subdev, pad, set_fmt, शून्य, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: set format %ux%u (%x) on UIF sink\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code);

	/*
	 * The UIF करोesn't mangle the क्रमmat between its sink and source pads,
	 * so there is no need to retrieve the क्रमmat on its source pad.
	 */

	uअगर->sink = next;
	uअगर->sink_pad = next_pad;

	वापस 0;
पूर्ण

/* Setup one RPF and the connected BRx sink pad. */
अटल पूर्णांक vsp1_du_pipeline_setup_rpf(काष्ठा vsp1_device *vsp1,
				      काष्ठा vsp1_pipeline *pipe,
				      काष्ठा vsp1_rwpf *rpf,
				      काष्ठा vsp1_entity *uअगर,
				      अचिन्हित पूर्णांक brx_input)
अणु
	काष्ठा v4l2_subdev_selection sel;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	स्थिर काष्ठा v4l2_rect *crop;
	पूर्णांक ret;

	/*
	 * Configure the क्रमmat on the RPF sink pad and propagate it up to the
	 * BRx sink pad.
	 */
	crop = &vsp1->drm->inमाला_दो[rpf->entity.index].crop;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.pad = RWPF_PAD_SINK;
	क्रमmat.क्रमmat.width = crop->width + crop->left;
	क्रमmat.क्रमmat.height = crop->height + crop->top;
	क्रमmat.क्रमmat.code = rpf->fmtinfo->mbus;
	क्रमmat.क्रमmat.field = V4L2_FIELD_NONE;

	ret = v4l2_subdev_call(&rpf->entity.subdev, pad, set_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev,
		"%s: set format %ux%u (%x) on RPF%u sink\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, rpf->entity.index);

	स_रखो(&sel, 0, माप(sel));
	sel.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sel.pad = RWPF_PAD_SINK;
	sel.target = V4L2_SEL_TGT_CROP;
	sel.r = *crop;

	ret = v4l2_subdev_call(&rpf->entity.subdev, pad, set_selection, शून्य,
			       &sel);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev,
		"%s: set selection (%u,%u)/%ux%u on RPF%u sink\n",
		__func__, sel.r.left, sel.r.top, sel.r.width, sel.r.height,
		rpf->entity.index);

	/*
	 * RPF source, hardcode the क्रमmat to ARGB8888 to turn on क्रमmat
	 * conversion अगर needed.
	 */
	क्रमmat.pad = RWPF_PAD_SOURCE;

	ret = v4l2_subdev_call(&rpf->entity.subdev, pad, get_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev,
		"%s: got format %ux%u (%x) on RPF%u source\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, rpf->entity.index);

	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_ARGB8888_1X32;

	ret = v4l2_subdev_call(&rpf->entity.subdev, pad, set_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	/* Insert and configure the UIF अगर available. */
	ret = vsp1_du_insert_uअगर(vsp1, pipe, uअगर, &rpf->entity, RWPF_PAD_SOURCE,
				 pipe->brx, brx_input);
	अगर (ret < 0)
		वापस ret;

	/* BRx sink, propagate the क्रमmat from the RPF source. */
	क्रमmat.pad = brx_input;

	ret = v4l2_subdev_call(&pipe->brx->subdev, pad, set_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: set format %ux%u (%x) on %s pad %u\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, BRX_NAME(pipe->brx), क्रमmat.pad);

	sel.pad = brx_input;
	sel.target = V4L2_SEL_TGT_COMPOSE;
	sel.r = vsp1->drm->inमाला_दो[rpf->entity.index].compose;

	ret = v4l2_subdev_call(&pipe->brx->subdev, pad, set_selection, शून्य,
			       &sel);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: set selection (%u,%u)/%ux%u on %s pad %u\n",
		__func__, sel.r.left, sel.r.top, sel.r.width, sel.r.height,
		BRX_NAME(pipe->brx), sel.pad);

	वापस 0;
पूर्ण

/* Setup the BRx source pad. */
अटल पूर्णांक vsp1_du_pipeline_setup_inमाला_दो(काष्ठा vsp1_device *vsp1,
					 काष्ठा vsp1_pipeline *pipe);
अटल व्योम vsp1_du_pipeline_configure(काष्ठा vsp1_pipeline *pipe);

अटल पूर्णांक vsp1_du_pipeline_setup_brx(काष्ठा vsp1_device *vsp1,
				      काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_drm_pipeline *drm_pipe = to_vsp1_drm_pipeline(pipe);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा vsp1_entity *brx;
	पूर्णांक ret;

	/*
	 * Pick a BRx:
	 * - If we need more than two inमाला_दो, use the BRU.
	 * - Otherwise, अगर we are not क्रमced to release our BRx, keep it.
	 * - Else, use any मुक्त BRx (अक्रमomly starting with the BRU).
	 */
	अगर (pipe->num_inमाला_दो > 2)
		brx = &vsp1->bru->entity;
	अन्यथा अगर (pipe->brx && !drm_pipe->क्रमce_brx_release)
		brx = pipe->brx;
	अन्यथा अगर (vsp1_feature(vsp1, VSP1_HAS_BRU) && !vsp1->bru->entity.pipe)
		brx = &vsp1->bru->entity;
	अन्यथा
		brx = &vsp1->brs->entity;

	/* Switch BRx अगर needed. */
	अगर (brx != pipe->brx) अणु
		काष्ठा vsp1_entity *released_brx = शून्य;

		/* Release our BRx अगर we have one. */
		अगर (pipe->brx) अणु
			dev_dbg(vsp1->dev, "%s: pipe %u: releasing %s\n",
				__func__, pipe->lअगर->index,
				BRX_NAME(pipe->brx));

			/*
			 * The BRx might be acquired by the other pipeline in
			 * the next step. We must thus हटाओ it from the list
			 * of entities क्रम this pipeline. The other pipeline's
			 * hardware configuration will reconfigure the BRx
			 * routing.
			 *
			 * However, अगर the other pipeline करोesn't acquire our
			 * BRx, we need to keep it in the list, otherwise the
			 * hardware configuration step won't disconnect it from
			 * the pipeline. To solve this, store the released BRx
			 * poपूर्णांकer to add it back to the list of entities later
			 * अगर it isn't acquired by the other pipeline.
			 */
			released_brx = pipe->brx;

			list_del(&pipe->brx->list_pipe);
			pipe->brx->sink = शून्य;
			pipe->brx->pipe = शून्य;
			pipe->brx = शून्य;
		पूर्ण

		/*
		 * If the BRx we need is in use, क्रमce the owner pipeline to
		 * चयन to the other BRx and रुको until the चयन completes.
		 */
		अगर (brx->pipe) अणु
			काष्ठा vsp1_drm_pipeline *owner_pipe;

			dev_dbg(vsp1->dev, "%s: pipe %u: waiting for %s\n",
				__func__, pipe->lअगर->index, BRX_NAME(brx));

			owner_pipe = to_vsp1_drm_pipeline(brx->pipe);
			owner_pipe->क्रमce_brx_release = true;

			vsp1_du_pipeline_setup_inमाला_दो(vsp1, &owner_pipe->pipe);
			vsp1_du_pipeline_configure(&owner_pipe->pipe);

			ret = रुको_event_समयout(owner_pipe->रुको_queue,
						 !owner_pipe->क्रमce_brx_release,
						 msecs_to_jअगरfies(500));
			अगर (ret == 0)
				dev_warn(vsp1->dev,
					 "DRM pipeline %u reconfiguration timeout\n",
					 owner_pipe->pipe.lअगर->index);
		पूर्ण

		/*
		 * If the BRx we have released previously hasn't been acquired
		 * by the other pipeline, add it back to the entities list (with
		 * the pipe poपूर्णांकer शून्य) to let vsp1_du_pipeline_configure()
		 * disconnect it from the hardware pipeline.
		 */
		अगर (released_brx && !released_brx->pipe)
			list_add_tail(&released_brx->list_pipe,
				      &pipe->entities);

		/* Add the BRx to the pipeline. */
		dev_dbg(vsp1->dev, "%s: pipe %u: acquired %s\n",
			__func__, pipe->lअगर->index, BRX_NAME(brx));

		pipe->brx = brx;
		pipe->brx->pipe = pipe;
		pipe->brx->sink = &pipe->output->entity;
		pipe->brx->sink_pad = 0;

		list_add_tail(&pipe->brx->list_pipe, &pipe->entities);
	पूर्ण

	/*
	 * Configure the क्रमmat on the BRx source and verअगरy that it matches the
	 * requested क्रमmat. We करोn't set the media bus code as it is configured
	 * on the BRx sink pad 0 and propagated inside the entity, not on the
	 * source pad.
	 */
	क्रमmat.pad = brx->source_pad;
	क्रमmat.क्रमmat.width = drm_pipe->width;
	क्रमmat.क्रमmat.height = drm_pipe->height;
	क्रमmat.क्रमmat.field = V4L2_FIELD_NONE;

	ret = v4l2_subdev_call(&brx->subdev, pad, set_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: set format %ux%u (%x) on %s pad %u\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, BRX_NAME(brx), brx->source_pad);

	अगर (क्रमmat.क्रमmat.width != drm_pipe->width ||
	    क्रमmat.क्रमmat.height != drm_pipe->height) अणु
		dev_dbg(vsp1->dev, "%s: format mismatch\n", __func__);
		वापस -EPIPE;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rpf_zpos(काष्ठा vsp1_device *vsp1, काष्ठा vsp1_rwpf *rpf)
अणु
	वापस vsp1->drm->inमाला_दो[rpf->entity.index].zpos;
पूर्ण

/* Setup the input side of the pipeline (RPFs and BRx). */
अटल पूर्णांक vsp1_du_pipeline_setup_inमाला_दो(काष्ठा vsp1_device *vsp1,
					काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_drm_pipeline *drm_pipe = to_vsp1_drm_pipeline(pipe);
	काष्ठा vsp1_rwpf *inमाला_दो[VSP1_MAX_RPF] = अणु शून्य, पूर्ण;
	काष्ठा vsp1_entity *uअगर;
	bool use_uअगर = false;
	काष्ठा vsp1_brx *brx;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Count the number of enabled inमाला_दो and sort them by Z-order. */
	pipe->num_inमाला_दो = 0;

	क्रम (i = 0; i < vsp1->info->rpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *rpf = vsp1->rpf[i];
		अचिन्हित पूर्णांक j;

		अगर (!pipe->inमाला_दो[i])
			जारी;

		/* Insert the RPF in the sorted RPFs array. */
		क्रम (j = pipe->num_inमाला_दो++; j > 0; --j) अणु
			अगर (rpf_zpos(vsp1, inमाला_दो[j-1]) <= rpf_zpos(vsp1, rpf))
				अवरोध;
			inमाला_दो[j] = inमाला_दो[j-1];
		पूर्ण

		inमाला_दो[j] = rpf;
	पूर्ण

	/*
	 * Setup the BRx. This must be करोne beक्रमe setting up the RPF input
	 * pipelines as the BRx sink compose rectangles depend on the BRx source
	 * क्रमmat.
	 */
	ret = vsp1_du_pipeline_setup_brx(vsp1, pipe);
	अगर (ret < 0) अणु
		dev_err(vsp1->dev, "%s: failed to setup %s source\n", __func__,
			BRX_NAME(pipe->brx));
		वापस ret;
	पूर्ण

	brx = to_brx(&pipe->brx->subdev);

	/* Setup the RPF input pipeline क्रम every enabled input. */
	क्रम (i = 0; i < pipe->brx->source_pad; ++i) अणु
		काष्ठा vsp1_rwpf *rpf = inमाला_दो[i];

		अगर (!rpf) अणु
			brx->inमाला_दो[i].rpf = शून्य;
			जारी;
		पूर्ण

		अगर (!rpf->entity.pipe) अणु
			rpf->entity.pipe = pipe;
			list_add_tail(&rpf->entity.list_pipe, &pipe->entities);
		पूर्ण

		brx->inमाला_दो[i].rpf = rpf;
		rpf->brx_input = i;
		rpf->entity.sink = pipe->brx;
		rpf->entity.sink_pad = i;

		dev_dbg(vsp1->dev, "%s: connecting RPF.%u to %s:%u\n",
			__func__, rpf->entity.index, BRX_NAME(pipe->brx), i);

		uअगर = drm_pipe->crc.source == VSP1_DU_CRC_PLANE &&
		      drm_pipe->crc.index == i ? drm_pipe->uअगर : शून्य;
		अगर (uअगर)
			use_uअगर = true;
		ret = vsp1_du_pipeline_setup_rpf(vsp1, pipe, rpf, uअगर, i);
		अगर (ret < 0) अणु
			dev_err(vsp1->dev,
				"%s: failed to setup RPF.%u\n",
				__func__, rpf->entity.index);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Insert and configure the UIF at the BRx output अगर available. */
	uअगर = drm_pipe->crc.source == VSP1_DU_CRC_OUTPUT ? drm_pipe->uअगर : शून्य;
	अगर (uअगर)
		use_uअगर = true;
	ret = vsp1_du_insert_uअगर(vsp1, pipe, uअगर,
				 pipe->brx, pipe->brx->source_pad,
				 &pipe->output->entity, 0);
	अगर (ret < 0)
		dev_err(vsp1->dev, "%s: failed to setup UIF after %s\n",
			__func__, BRX_NAME(pipe->brx));

	/*
	 * If the UIF is not in use schedule it क्रम removal by setting its pipe
	 * poपूर्णांकer to शून्य, vsp1_du_pipeline_configure() will हटाओ it from the
	 * hardware pipeline and from the pipeline's list of entities. Otherwise
	 * make sure it is present in the pipeline's list of entities अगर it
	 * wasn't alपढ़ोy.
	 */
	अगर (drm_pipe->uअगर && !use_uअगर) अणु
		drm_pipe->uअगर->pipe = शून्य;
	पूर्ण अन्यथा अगर (drm_pipe->uअगर && !drm_pipe->uअगर->pipe) अणु
		drm_pipe->uअगर->pipe = pipe;
		list_add_tail(&drm_pipe->uअगर->list_pipe, &pipe->entities);
	पूर्ण

	वापस 0;
पूर्ण

/* Setup the output side of the pipeline (WPF and LIF). */
अटल पूर्णांक vsp1_du_pipeline_setup_output(काष्ठा vsp1_device *vsp1,
					 काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_drm_pipeline *drm_pipe = to_vsp1_drm_pipeline(pipe);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु 0, पूर्ण;
	पूर्णांक ret;

	क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.pad = RWPF_PAD_SINK;
	क्रमmat.क्रमmat.width = drm_pipe->width;
	क्रमmat.क्रमmat.height = drm_pipe->height;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_ARGB8888_1X32;
	क्रमmat.क्रमmat.field = V4L2_FIELD_NONE;

	ret = v4l2_subdev_call(&pipe->output->entity.subdev, pad, set_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: set format %ux%u (%x) on WPF%u sink\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, pipe->output->entity.index);

	क्रमmat.pad = RWPF_PAD_SOURCE;
	ret = v4l2_subdev_call(&pipe->output->entity.subdev, pad, get_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: got format %ux%u (%x) on WPF%u source\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, pipe->output->entity.index);

	क्रमmat.pad = LIF_PAD_SINK;
	ret = v4l2_subdev_call(&pipe->lअगर->subdev, pad, set_fmt, शून्य,
			       &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vsp1->dev, "%s: set format %ux%u (%x) on LIF%u sink\n",
		__func__, क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		क्रमmat.क्रमmat.code, pipe->lअगर->index);

	/*
	 * Verअगरy that the क्रमmat at the output of the pipeline matches the
	 * requested frame size and media bus code.
	 */
	अगर (क्रमmat.क्रमmat.width != drm_pipe->width ||
	    क्रमmat.क्रमmat.height != drm_pipe->height ||
	    क्रमmat.क्रमmat.code != MEDIA_BUS_FMT_ARGB8888_1X32) अणु
		dev_dbg(vsp1->dev, "%s: format mismatch on LIF%u\n", __func__,
			pipe->lअगर->index);
		वापस -EPIPE;
	पूर्ण

	वापस 0;
पूर्ण

/* Configure all entities in the pipeline. */
अटल व्योम vsp1_du_pipeline_configure(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_drm_pipeline *drm_pipe = to_vsp1_drm_pipeline(pipe);
	काष्ठा vsp1_entity *entity;
	काष्ठा vsp1_entity *next;
	काष्ठा vsp1_dl_list *dl;
	काष्ठा vsp1_dl_body *dlb;
	अचिन्हित पूर्णांक dl_flags = 0;

	अगर (drm_pipe->क्रमce_brx_release)
		dl_flags |= VSP1_DL_FRAME_END_INTERNAL;
	अगर (pipe->output->ग_लिखोback)
		dl_flags |= VSP1_DL_FRAME_END_WRITEBACK;

	dl = vsp1_dl_list_get(pipe->output->dlm);
	dlb = vsp1_dl_list_get_body0(dl);

	list_क्रम_each_entry_safe(entity, next, &pipe->entities, list_pipe) अणु
		/* Disconnect unused entities from the pipeline. */
		अगर (!entity->pipe) अणु
			vsp1_dl_body_ग_लिखो(dlb, entity->route->reg,
					   VI6_DPR_NODE_UNUSED);

			entity->sink = शून्य;
			list_del(&entity->list_pipe);

			जारी;
		पूर्ण

		vsp1_entity_route_setup(entity, pipe, dlb);
		vsp1_entity_configure_stream(entity, pipe, dl, dlb);
		vsp1_entity_configure_frame(entity, pipe, dl, dlb);
		vsp1_entity_configure_partition(entity, pipe, dl, dlb);
	पूर्ण

	vsp1_dl_list_commit(dl, dl_flags);
पूर्ण

अटल पूर्णांक vsp1_du_pipeline_set_rwpf_क्रमmat(काष्ठा vsp1_device *vsp1,
					    काष्ठा vsp1_rwpf *rwpf,
					    u32 pixelक्रमmat, अचिन्हित पूर्णांक pitch)
अणु
	स्थिर काष्ठा vsp1_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक chroma_hsub;

	fmtinfo = vsp1_get_क्रमmat_info(vsp1, pixelक्रमmat);
	अगर (!fmtinfo) अणु
		dev_dbg(vsp1->dev, "Unsupported pixel format %08x\n",
			pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Only क्रमmats with three planes can affect the chroma planes pitch.
	 * All क्रमmats with two planes have a horizontal subsampling value of 2,
	 * but combine U and V in a single chroma plane, which thus results in
	 * the luma plane and chroma plane having the same pitch.
	 */
	chroma_hsub = (fmtinfo->planes == 3) ? fmtinfo->hsub : 1;

	rwpf->fmtinfo = fmtinfo;
	rwpf->क्रमmat.num_planes = fmtinfo->planes;
	rwpf->क्रमmat.plane_fmt[0].bytesperline = pitch;
	rwpf->क्रमmat.plane_fmt[1].bytesperline = pitch / chroma_hsub;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * DU Driver API
 */

पूर्णांक vsp1_du_init(काष्ठा device *dev)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);

	अगर (!vsp1)
		वापस -EPROBE_DEFER;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_init);

/**
 * vsp1_du_setup_lअगर - Setup the output part of the VSP pipeline
 * @dev: the VSP device
 * @pipe_index: the DRM pipeline index
 * @cfg: the LIF configuration
 *
 * Configure the output part of VSP DRM pipeline क्रम the given frame @cfg.width
 * and @cfg.height. This sets up क्रमmats on the BRx source pad, the WPF sink and
 * source pads, and the LIF sink pad.
 *
 * The @pipe_index argument selects which DRM pipeline to setup. The number of
 * available pipelines depend on the VSP instance.
 *
 * As the media bus code on the blend unit source pad is conditioned by the
 * configuration of its sink 0 pad, we also set up the क्रमmats on all blend unit
 * sinks, even अगर the configuration will be overwritten later by
 * vsp1_du_setup_rpf(). This ensures that the blend unit configuration is set to
 * a well defined state.
 *
 * Return 0 on success or a negative error code on failure.
 */
पूर्णांक vsp1_du_setup_lअगर(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index,
		      स्थिर काष्ठा vsp1_du_lअगर_config *cfg)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);
	काष्ठा vsp1_drm_pipeline *drm_pipe;
	काष्ठा vsp1_pipeline *pipe;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (pipe_index >= vsp1->info->lअगर_count)
		वापस -EINVAL;

	drm_pipe = &vsp1->drm->pipe[pipe_index];
	pipe = &drm_pipe->pipe;

	अगर (!cfg) अणु
		काष्ठा vsp1_brx *brx;

		mutex_lock(&vsp1->drm->lock);

		brx = to_brx(&pipe->brx->subdev);

		/*
		 * शून्य configuration means the CRTC is being disabled, stop
		 * the pipeline and turn the light off.
		 */
		ret = vsp1_pipeline_stop(pipe);
		अगर (ret == -ETIMEDOUT)
			dev_err(vsp1->dev, "DRM pipeline stop timeout\n");

		क्रम (i = 0; i < ARRAY_SIZE(pipe->inमाला_दो); ++i) अणु
			काष्ठा vsp1_rwpf *rpf = pipe->inमाला_दो[i];

			अगर (!rpf)
				जारी;

			/*
			 * Remove the RPF from the pipe and the list of BRx
			 * inमाला_दो.
			 */
			WARN_ON(!rpf->entity.pipe);
			rpf->entity.pipe = शून्य;
			list_del(&rpf->entity.list_pipe);
			pipe->inमाला_दो[i] = शून्य;

			brx->inमाला_दो[rpf->brx_input].rpf = शून्य;
		पूर्ण

		drm_pipe->du_complete = शून्य;
		pipe->num_inमाला_दो = 0;

		dev_dbg(vsp1->dev, "%s: pipe %u: releasing %s\n",
			__func__, pipe->lअगर->index,
			BRX_NAME(pipe->brx));

		list_del(&pipe->brx->list_pipe);
		pipe->brx->pipe = शून्य;
		pipe->brx = शून्य;

		mutex_unlock(&vsp1->drm->lock);

		vsp1_dlm_reset(pipe->output->dlm);
		vsp1_device_put(vsp1);

		dev_dbg(vsp1->dev, "%s: pipeline disabled\n", __func__);

		वापस 0;
	पूर्ण

	drm_pipe->width = cfg->width;
	drm_pipe->height = cfg->height;
	pipe->पूर्णांकerlaced = cfg->पूर्णांकerlaced;

	dev_dbg(vsp1->dev, "%s: configuring LIF%u with format %ux%u%s\n",
		__func__, pipe_index, cfg->width, cfg->height,
		pipe->पूर्णांकerlaced ? "i" : "");

	mutex_lock(&vsp1->drm->lock);

	/* Setup क्रमmats through the pipeline. */
	ret = vsp1_du_pipeline_setup_inमाला_दो(vsp1, pipe);
	अगर (ret < 0)
		जाओ unlock;

	ret = vsp1_du_pipeline_setup_output(vsp1, pipe);
	अगर (ret < 0)
		जाओ unlock;

	/* Enable the VSP1. */
	ret = vsp1_device_get(vsp1);
	अगर (ret < 0)
		जाओ unlock;

	/*
	 * Register a callback to allow us to notअगरy the DRM driver of frame
	 * completion events.
	 */
	drm_pipe->du_complete = cfg->callback;
	drm_pipe->du_निजी = cfg->callback_data;

	/* Disable the display पूर्णांकerrupts. */
	vsp1_ग_लिखो(vsp1, VI6_DISP_IRQ_STA(pipe_index), 0);
	vsp1_ग_लिखो(vsp1, VI6_DISP_IRQ_ENB(pipe_index), 0);

	/* Configure all entities in the pipeline. */
	vsp1_du_pipeline_configure(pipe);

unlock:
	mutex_unlock(&vsp1->drm->lock);

	अगर (ret < 0)
		वापस ret;

	/* Start the pipeline. */
	spin_lock_irqsave(&pipe->irqlock, flags);
	vsp1_pipeline_run(pipe);
	spin_unlock_irqrestore(&pipe->irqlock, flags);

	dev_dbg(vsp1->dev, "%s: pipeline enabled\n", __func__);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_setup_lअगर);

/**
 * vsp1_du_atomic_begin - Prepare क्रम an atomic update
 * @dev: the VSP device
 * @pipe_index: the DRM pipeline index
 */
व्योम vsp1_du_atomic_begin(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_atomic_begin);

/**
 * vsp1_du_atomic_update - Setup one RPF input of the VSP pipeline
 * @dev: the VSP device
 * @pipe_index: the DRM pipeline index
 * @rpf_index: index of the RPF to setup (0-based)
 * @cfg: the RPF configuration
 *
 * Configure the VSP to perक्रमm image composition through RPF @rpf_index as
 * described by the @cfg configuration. The image to compose is referenced by
 * @cfg.mem and composed using the @cfg.src crop rectangle and the @cfg.dst
 * composition rectangle. The Z-order is configurable with higher @zpos values
 * displayed on top.
 *
 * If the @cfg configuration is शून्य, the RPF will be disabled. Calling the
 * function on a disabled RPF is allowed.
 *
 * Image क्रमmat as stored in memory is expressed as a V4L2 @cfg.pixelक्रमmat
 * value. The memory pitch is configurable to allow क्रम padding at end of lines,
 * or simply क्रम images that extend beyond the crop rectangle boundaries. The
 * @cfg.pitch value is expressed in bytes and applies to all planes क्रम
 * multiplanar क्रमmats.
 *
 * The source memory buffer is referenced by the DMA address of its planes in
 * the @cfg.mem array. Up to two planes are supported. The second plane DMA
 * address is ignored क्रम क्रमmats using a single plane.
 *
 * This function isn't reentrant, the caller needs to serialize calls.
 *
 * Return 0 on success or a negative error code on failure.
 */
पूर्णांक vsp1_du_atomic_update(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index,
			  अचिन्हित पूर्णांक rpf_index,
			  स्थिर काष्ठा vsp1_du_atomic_config *cfg)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);
	काष्ठा vsp1_drm_pipeline *drm_pipe = &vsp1->drm->pipe[pipe_index];
	काष्ठा vsp1_rwpf *rpf;
	पूर्णांक ret;

	अगर (rpf_index >= vsp1->info->rpf_count)
		वापस -EINVAL;

	rpf = vsp1->rpf[rpf_index];

	अगर (!cfg) अणु
		dev_dbg(vsp1->dev, "%s: RPF%u: disable requested\n", __func__,
			rpf_index);

		/*
		 * Remove the RPF from the pipeline's inमाला_दो. Keep it in the
		 * pipeline's entity list to let vsp1_du_pipeline_configure()
		 * हटाओ it from the hardware pipeline.
		 */
		rpf->entity.pipe = शून्य;
		drm_pipe->pipe.inमाला_दो[rpf_index] = शून्य;
		वापस 0;
	पूर्ण

	dev_dbg(vsp1->dev,
		"%s: RPF%u: (%u,%u)/%ux%u -> (%u,%u)/%ux%u (%08x), pitch %u dma { %pad, %pad, %pad } zpos %u\n",
		__func__, rpf_index,
		cfg->src.left, cfg->src.top, cfg->src.width, cfg->src.height,
		cfg->dst.left, cfg->dst.top, cfg->dst.width, cfg->dst.height,
		cfg->pixelक्रमmat, cfg->pitch, &cfg->mem[0], &cfg->mem[1],
		&cfg->mem[2], cfg->zpos);

	/*
	 * Store the क्रमmat, stride, memory buffer address, crop and compose
	 * rectangles and Z-order position and क्रम the input.
	 */
	ret = vsp1_du_pipeline_set_rwpf_क्रमmat(vsp1, rpf, cfg->pixelक्रमmat,
					       cfg->pitch);
	अगर (ret < 0)
		वापस ret;

	rpf->alpha = cfg->alpha;

	rpf->mem.addr[0] = cfg->mem[0];
	rpf->mem.addr[1] = cfg->mem[1];
	rpf->mem.addr[2] = cfg->mem[2];

	vsp1->drm->inमाला_दो[rpf_index].crop = cfg->src;
	vsp1->drm->inमाला_दो[rpf_index].compose = cfg->dst;
	vsp1->drm->inमाला_दो[rpf_index].zpos = cfg->zpos;

	drm_pipe->pipe.inमाला_दो[rpf_index] = rpf;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_atomic_update);

/**
 * vsp1_du_atomic_flush - Commit an atomic update
 * @dev: the VSP device
 * @pipe_index: the DRM pipeline index
 * @cfg: atomic pipe configuration
 */
व्योम vsp1_du_atomic_flush(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index,
			  स्थिर काष्ठा vsp1_du_atomic_pipe_config *cfg)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);
	काष्ठा vsp1_drm_pipeline *drm_pipe = &vsp1->drm->pipe[pipe_index];
	काष्ठा vsp1_pipeline *pipe = &drm_pipe->pipe;
	पूर्णांक ret;

	drm_pipe->crc = cfg->crc;

	mutex_lock(&vsp1->drm->lock);

	अगर (cfg->ग_लिखोback.pixelक्रमmat) अणु
		स्थिर काष्ठा vsp1_du_ग_लिखोback_config *wb_cfg = &cfg->ग_लिखोback;

		ret = vsp1_du_pipeline_set_rwpf_क्रमmat(vsp1, pipe->output,
						       wb_cfg->pixelक्रमmat,
						       wb_cfg->pitch);
		अगर (WARN_ON(ret < 0))
			जाओ करोne;

		pipe->output->mem.addr[0] = wb_cfg->mem[0];
		pipe->output->mem.addr[1] = wb_cfg->mem[1];
		pipe->output->mem.addr[2] = wb_cfg->mem[2];
		pipe->output->ग_लिखोback = true;
	पूर्ण

	vsp1_du_pipeline_setup_inमाला_दो(vsp1, pipe);
	vsp1_du_pipeline_configure(pipe);

करोne:
	mutex_unlock(&vsp1->drm->lock);
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_atomic_flush);

पूर्णांक vsp1_du_map_sg(काष्ठा device *dev, काष्ठा sg_table *sgt)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);

	/*
	 * As all the buffers allocated by the DU driver are coherent, we can
	 * skip cache sync. This will need to be revisited when support क्रम
	 * non-coherent buffers will be added to the DU driver.
	 */
	वापस dma_map_sgtable(vsp1->bus_master, sgt, DMA_TO_DEVICE,
			       DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_map_sg);

व्योम vsp1_du_unmap_sg(काष्ठा device *dev, काष्ठा sg_table *sgt)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);

	dma_unmap_sgtable(vsp1->bus_master, sgt, DMA_TO_DEVICE,
			  DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण
EXPORT_SYMBOL_GPL(vsp1_du_unmap_sg);

/* -----------------------------------------------------------------------------
 * Initialization
 */

पूर्णांक vsp1_drm_init(काष्ठा vsp1_device *vsp1)
अणु
	अचिन्हित पूर्णांक i;

	vsp1->drm = devm_kzalloc(vsp1->dev, माप(*vsp1->drm), GFP_KERNEL);
	अगर (!vsp1->drm)
		वापस -ENOMEM;

	mutex_init(&vsp1->drm->lock);

	/* Create one DRM pipeline per LIF. */
	क्रम (i = 0; i < vsp1->info->lअगर_count; ++i) अणु
		काष्ठा vsp1_drm_pipeline *drm_pipe = &vsp1->drm->pipe[i];
		काष्ठा vsp1_pipeline *pipe = &drm_pipe->pipe;

		init_रुकोqueue_head(&drm_pipe->रुको_queue);

		vsp1_pipeline_init(pipe);

		pipe->frame_end = vsp1_du_pipeline_frame_end;

		/*
		 * The output side of the DRM pipeline is अटल, add the
		 * corresponding entities manually.
		 */
		pipe->output = vsp1->wpf[i];
		pipe->lअगर = &vsp1->lअगर[i]->entity;

		pipe->output->entity.pipe = pipe;
		pipe->output->entity.sink = pipe->lअगर;
		pipe->output->entity.sink_pad = 0;
		list_add_tail(&pipe->output->entity.list_pipe, &pipe->entities);

		pipe->lअगर->pipe = pipe;
		list_add_tail(&pipe->lअगर->list_pipe, &pipe->entities);

		/*
		 * CRC computation is initially disabled, करोn't add the UIF to
		 * the pipeline.
		 */
		अगर (i < vsp1->info->uअगर_count)
			drm_pipe->uअगर = &vsp1->uअगर[i]->entity;
	पूर्ण

	/* Disable all RPFs initially. */
	क्रम (i = 0; i < vsp1->info->rpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *input = vsp1->rpf[i];

		INIT_LIST_HEAD(&input->entity.list_pipe);
	पूर्ण

	वापस 0;
पूर्ण

व्योम vsp1_drm_cleanup(काष्ठा vsp1_device *vsp1)
अणु
	mutex_destroy(&vsp1->drm->lock);
पूर्ण
