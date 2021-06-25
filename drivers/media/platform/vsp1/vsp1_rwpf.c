<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_rwpf.c  --  R-Car VSP1 Read and Write Pixel Formatters
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_video.h"

#घोषणा RWPF_MIN_WIDTH				1
#घोषणा RWPF_MIN_HEIGHT				1

काष्ठा v4l2_rect *vsp1_rwpf_get_crop(काष्ठा vsp1_rwpf *rwpf,
				     काष्ठा v4l2_subdev_pad_config *config)
अणु
	वापस v4l2_subdev_get_try_crop(&rwpf->entity.subdev, config,
					RWPF_PAD_SINK);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Pad Operations
 */

अटल पूर्णांक vsp1_rwpf_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अटल स्थिर अचिन्हित पूर्णांक codes[] = अणु
		MEDIA_BUS_FMT_ARGB8888_1X32,
		MEDIA_BUS_FMT_AHSV8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	पूर्ण;

	अगर (code->index >= ARRAY_SIZE(codes))
		वापस -EINVAL;

	code->code = codes[code->index];

	वापस 0;
पूर्ण

अटल पूर्णांक vsp1_rwpf_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा vsp1_rwpf *rwpf = to_rwpf(subdev);

	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, RWPF_MIN_WIDTH,
					   RWPF_MIN_HEIGHT, rwpf->max_width,
					   rwpf->max_height);
पूर्ण

अटल पूर्णांक vsp1_rwpf_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_rwpf *rwpf = to_rwpf(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	mutex_lock(&rwpf->entity.lock);

	config = vsp1_entity_get_pad_config(&rwpf->entity, cfg, fmt->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* Default to YUV अगर the requested क्रमmat is not supported. */
	अगर (fmt->क्रमmat.code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
	    fmt->क्रमmat.code != MEDIA_BUS_FMT_AHSV8888_1X32 &&
	    fmt->क्रमmat.code != MEDIA_BUS_FMT_AYUV8_1X32)
		fmt->क्रमmat.code = MEDIA_BUS_FMT_AYUV8_1X32;

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&rwpf->entity, config, fmt->pad);

	अगर (fmt->pad == RWPF_PAD_SOURCE) अणु
		/*
		 * The RWPF perक्रमms क्रमmat conversion but can't scale, only the
		 * क्रमmat code can be changed on the source pad.
		 */
		क्रमmat->code = fmt->क्रमmat.code;
		fmt->क्रमmat = *क्रमmat;
		जाओ करोne;
	पूर्ण

	क्रमmat->code = fmt->क्रमmat.code;
	क्रमmat->width = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.width,
				RWPF_MIN_WIDTH, rwpf->max_width);
	क्रमmat->height = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.height,
				 RWPF_MIN_HEIGHT, rwpf->max_height);
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	fmt->क्रमmat = *क्रमmat;

	अगर (rwpf->entity.type == VSP1_ENTITY_RPF) अणु
		काष्ठा v4l2_rect *crop;

		/* Update the sink crop rectangle. */
		crop = vsp1_rwpf_get_crop(rwpf, config);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->क्रमmat.width;
		crop->height = fmt->क्रमmat.height;
	पूर्ण

	/* Propagate the क्रमmat to the source pad. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&rwpf->entity, config,
					    RWPF_PAD_SOURCE);
	*क्रमmat = fmt->क्रमmat;

	अगर (rwpf->flip.rotate) अणु
		क्रमmat->width = fmt->क्रमmat.height;
		क्रमmat->height = fmt->क्रमmat.width;
	पूर्ण

करोne:
	mutex_unlock(&rwpf->entity.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vsp1_rwpf_get_selection(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_rwpf *rwpf = to_rwpf(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	/*
	 * Cropping is only supported on the RPF and is implemented on the sink
	 * pad.
	 */
	अगर (rwpf->entity.type == VSP1_ENTITY_WPF || sel->pad != RWPF_PAD_SINK)
		वापस -EINVAL;

	mutex_lock(&rwpf->entity.lock);

	config = vsp1_entity_get_pad_config(&rwpf->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *vsp1_rwpf_get_crop(rwpf, config);
		अवरोध;

	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&rwpf->entity, config,
						    RWPF_PAD_SINK);
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = क्रमmat->width;
		sel->r.height = क्रमmat->height;
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

करोne:
	mutex_unlock(&rwpf->entity.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vsp1_rwpf_set_selection(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_rwpf *rwpf = to_rwpf(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;
	पूर्णांक ret = 0;

	/*
	 * Cropping is only supported on the RPF and is implemented on the sink
	 * pad.
	 */
	अगर (rwpf->entity.type == VSP1_ENTITY_WPF || sel->pad != RWPF_PAD_SINK)
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&rwpf->entity.lock);

	config = vsp1_entity_get_pad_config(&rwpf->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* Make sure the crop rectangle is entirely contained in the image. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&rwpf->entity, config,
					    RWPF_PAD_SINK);

	/*
	 * Restrict the crop rectangle coordinates to multiples of 2 to aव्योम
	 * shअगरting the color plane.
	 */
	अगर (क्रमmat->code == MEDIA_BUS_FMT_AYUV8_1X32) अणु
		sel->r.left = ALIGN(sel->r.left, 2);
		sel->r.top = ALIGN(sel->r.top, 2);
		sel->r.width = round_करोwn(sel->r.width, 2);
		sel->r.height = round_करोwn(sel->r.height, 2);
	पूर्ण

	sel->r.left = min_t(अचिन्हित पूर्णांक, sel->r.left, क्रमmat->width - 2);
	sel->r.top = min_t(अचिन्हित पूर्णांक, sel->r.top, क्रमmat->height - 2);
	sel->r.width = min_t(अचिन्हित पूर्णांक, sel->r.width,
			     क्रमmat->width - sel->r.left);
	sel->r.height = min_t(अचिन्हित पूर्णांक, sel->r.height,
			      क्रमmat->height - sel->r.top);

	crop = vsp1_rwpf_get_crop(rwpf, config);
	*crop = sel->r;

	/* Propagate the क्रमmat to the source pad. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&rwpf->entity, config,
					    RWPF_PAD_SOURCE);
	क्रमmat->width = crop->width;
	क्रमmat->height = crop->height;

करोne:
	mutex_unlock(&rwpf->entity.lock);
	वापस ret;
पूर्ण

स्थिर काष्ठा v4l2_subdev_pad_ops vsp1_rwpf_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = vsp1_rwpf_क्रमागत_mbus_code,
	.क्रमागत_frame_size = vsp1_rwpf_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = vsp1_rwpf_set_क्रमmat,
	.get_selection = vsp1_rwpf_get_selection,
	.set_selection = vsp1_rwpf_set_selection,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Controls
 */

अटल पूर्णांक vsp1_rwpf_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_rwpf *rwpf =
		container_of(ctrl->handler, काष्ठा vsp1_rwpf, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ALPHA_COMPONENT:
		rwpf->alpha = ctrl->val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vsp1_rwpf_ctrl_ops = अणु
	.s_ctrl = vsp1_rwpf_s_ctrl,
पूर्ण;

पूर्णांक vsp1_rwpf_init_ctrls(काष्ठा vsp1_rwpf *rwpf, अचिन्हित पूर्णांक ncontrols)
अणु
	v4l2_ctrl_handler_init(&rwpf->ctrls, ncontrols + 1);
	v4l2_ctrl_new_std(&rwpf->ctrls, &vsp1_rwpf_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	rwpf->entity.subdev.ctrl_handler = &rwpf->ctrls;

	वापस rwpf->ctrls.error;
पूर्ण
