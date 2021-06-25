<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_brx.c  --  R-Car VSP1 Blend ROP Unit (BRU and BRS)
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_brx.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_video.h"

#घोषणा BRX_MIN_SIZE				1U
#घोषणा BRX_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_brx_ग_लिखो(काष्ठा vsp1_brx *brx,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, brx->base + reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

अटल पूर्णांक brx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_brx *brx =
		container_of(ctrl->handler, काष्ठा vsp1_brx, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BG_COLOR:
		brx->bgcolor = ctrl->val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops brx_ctrl_ops = अणु
	.s_ctrl = brx_s_ctrl,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

/*
 * The BRx can't perक्रमm क्रमmat conversion, all sink and source क्रमmats must be
 * identical. We pick the क्रमmat on the first sink pad (pad 0) and propagate it
 * to all other pads.
 */

अटल पूर्णांक brx_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अटल स्थिर अचिन्हित पूर्णांक codes[] = अणु
		MEDIA_BUS_FMT_ARGB8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	पूर्ण;

	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, codes,
					  ARRAY_SIZE(codes));
पूर्ण

अटल पूर्णांक brx_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index)
		वापस -EINVAL;

	अगर (fse->code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
	    fse->code != MEDIA_BUS_FMT_AYUV8_1X32)
		वापस -EINVAL;

	fse->min_width = BRX_MIN_SIZE;
	fse->max_width = BRX_MAX_SIZE;
	fse->min_height = BRX_MIN_SIZE;
	fse->max_height = BRX_MAX_SIZE;

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_rect *brx_get_compose(काष्ठा vsp1_brx *brx,
					 काष्ठा v4l2_subdev_pad_config *cfg,
					 अचिन्हित पूर्णांक pad)
अणु
	वापस v4l2_subdev_get_try_compose(&brx->entity.subdev, cfg, pad);
पूर्ण

अटल व्योम brx_try_क्रमmat(काष्ठा vsp1_brx *brx,
			   काष्ठा v4l2_subdev_pad_config *config,
			   अचिन्हित पूर्णांक pad, काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	चयन (pad) अणु
	हाल BRX_PAD_SINK(0):
		/* Default to YUV अगर the requested क्रमmat is not supported. */
		अगर (fmt->code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
		    fmt->code != MEDIA_BUS_FMT_AYUV8_1X32)
			fmt->code = MEDIA_BUS_FMT_AYUV8_1X32;
		अवरोध;

	शेष:
		/* The BRx can't perक्रमm क्रमmat conversion. */
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&brx->entity, config,
						    BRX_PAD_SINK(0));
		fmt->code = क्रमmat->code;
		अवरोध;
	पूर्ण

	fmt->width = clamp(fmt->width, BRX_MIN_SIZE, BRX_MAX_SIZE);
	fmt->height = clamp(fmt->height, BRX_MIN_SIZE, BRX_MAX_SIZE);
	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

अटल पूर्णांक brx_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_brx *brx = to_brx(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	mutex_lock(&brx->entity.lock);

	config = vsp1_entity_get_pad_config(&brx->entity, cfg, fmt->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	brx_try_क्रमmat(brx, config, fmt->pad, &fmt->क्रमmat);

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&brx->entity, config, fmt->pad);
	*क्रमmat = fmt->क्रमmat;

	/* Reset the compose rectangle. */
	अगर (fmt->pad != brx->entity.source_pad) अणु
		काष्ठा v4l2_rect *compose;

		compose = brx_get_compose(brx, config, fmt->pad);
		compose->left = 0;
		compose->top = 0;
		compose->width = क्रमmat->width;
		compose->height = क्रमmat->height;
	पूर्ण

	/* Propagate the क्रमmat code to all pads. */
	अगर (fmt->pad == BRX_PAD_SINK(0)) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i <= brx->entity.source_pad; ++i) अणु
			क्रमmat = vsp1_entity_get_pad_क्रमmat(&brx->entity,
							    config, i);
			क्रमmat->code = fmt->क्रमmat.code;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&brx->entity.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक brx_get_selection(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_brx *brx = to_brx(subdev);
	काष्ठा v4l2_subdev_pad_config *config;

	अगर (sel->pad == brx->entity.source_pad)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = BRX_MAX_SIZE;
		sel->r.height = BRX_MAX_SIZE;
		वापस 0;

	हाल V4L2_SEL_TGT_COMPOSE:
		config = vsp1_entity_get_pad_config(&brx->entity, cfg,
						    sel->which);
		अगर (!config)
			वापस -EINVAL;

		mutex_lock(&brx->entity.lock);
		sel->r = *brx_get_compose(brx, config, sel->pad);
		mutex_unlock(&brx->entity.lock);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक brx_set_selection(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_brx *brx = to_brx(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *compose;
	पूर्णांक ret = 0;

	अगर (sel->pad == brx->entity.source_pad)
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_COMPOSE)
		वापस -EINVAL;

	mutex_lock(&brx->entity.lock);

	config = vsp1_entity_get_pad_config(&brx->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/*
	 * The compose rectangle top left corner must be inside the output
	 * frame.
	 */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&brx->entity, config,
					    brx->entity.source_pad);
	sel->r.left = clamp_t(अचिन्हित पूर्णांक, sel->r.left, 0, क्रमmat->width - 1);
	sel->r.top = clamp_t(अचिन्हित पूर्णांक, sel->r.top, 0, क्रमmat->height - 1);

	/*
	 * Scaling isn't supported, the compose rectangle size must be identical
	 * to the sink क्रमmat size.
	 */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&brx->entity, config, sel->pad);
	sel->r.width = क्रमmat->width;
	sel->r.height = क्रमmat->height;

	compose = brx_get_compose(brx, config, sel->pad);
	*compose = sel->r;

करोne:
	mutex_unlock(&brx->entity.lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops brx_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = brx_क्रमागत_mbus_code,
	.क्रमागत_frame_size = brx_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = brx_set_क्रमmat,
	.get_selection = brx_get_selection,
	.set_selection = brx_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops brx_ops = अणु
	.pad    = &brx_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम brx_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_brx *brx = to_brx(&entity->subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक i;

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&brx->entity, brx->entity.config,
					    brx->entity.source_pad);

	/*
	 * The hardware is extremely flexible but we have no userspace API to
	 * expose all the parameters, nor is it clear whether we would have use
	 * हालs क्रम all the supported modes. Let's just hardcode the parameters
	 * to sane शेष values क्रम now.
	 */

	/*
	 * Disable dithering and enable color data normalization unless the
	 * क्रमmat at the pipeline output is premultiplied.
	 */
	flags = pipe->output ? pipe->output->क्रमmat.flags : 0;
	vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_INCTRL,
		       flags & V4L2_PIX_FMT_FLAG_PREMUL_ALPHA ?
		       0 : VI6_BRU_INCTRL_NRM);

	/*
	 * Set the background position to cover the whole output image and
	 * configure its color.
	 */
	vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_VIRRPF_SIZE,
		       (क्रमmat->width << VI6_BRU_VIRRPF_SIZE_HSIZE_SHIFT) |
		       (क्रमmat->height << VI6_BRU_VIRRPF_SIZE_VSIZE_SHIFT));
	vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_VIRRPF_LOC, 0);

	vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_VIRRPF_COL, brx->bgcolor |
		       (0xff << VI6_BRU_VIRRPF_COL_A_SHIFT));

	/*
	 * Route BRU input 1 as SRC input to the ROP unit and configure the ROP
	 * unit with a NOP operation to make BRU input 1 available as the
	 * Blend/ROP unit B SRC input. Only needed क्रम BRU, the BRS has no ROP
	 * unit.
	 */
	अगर (entity->type == VSP1_ENTITY_BRU)
		vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_ROP,
			       VI6_BRU_ROP_DSTSEL_BRUIN(1) |
			       VI6_BRU_ROP_CROP(VI6_ROP_NOP) |
			       VI6_BRU_ROP_AROP(VI6_ROP_NOP));

	क्रम (i = 0; i < brx->entity.source_pad; ++i) अणु
		bool premultiplied = false;
		u32 ctrl = 0;

		/*
		 * Configure all Blend/ROP units corresponding to an enabled BRx
		 * input क्रम alpha blending. Blend/ROP units corresponding to
		 * disabled BRx inमाला_दो are used in ROP NOP mode to ignore the
		 * SRC input.
		 */
		अगर (brx->inमाला_दो[i].rpf) अणु
			ctrl |= VI6_BRU_CTRL_RBC;

			premultiplied = brx->inमाला_दो[i].rpf->क्रमmat.flags
				      & V4L2_PIX_FMT_FLAG_PREMUL_ALPHA;
		पूर्ण अन्यथा अणु
			ctrl |= VI6_BRU_CTRL_CROP(VI6_ROP_NOP)
			     |  VI6_BRU_CTRL_AROP(VI6_ROP_NOP);
		पूर्ण

		/*
		 * Select the भव RPF as the Blend/ROP unit A DST input to
		 * serve as a background color.
		 */
		अगर (i == 0)
			ctrl |= VI6_BRU_CTRL_DSTSEL_VRPF;

		/*
		 * Route inमाला_दो 0 to 3 as SRC inमाला_दो to Blend/ROP units A to D
		 * in that order. In the BRU the Blend/ROP unit B SRC is
		 * hardwired to the ROP unit output, the corresponding रेजिस्टर
		 * bits must be set to 0. The BRS has no ROP unit and करोesn't
		 * need any special processing.
		 */
		अगर (!(entity->type == VSP1_ENTITY_BRU && i == 1))
			ctrl |= VI6_BRU_CTRL_SRCSEL_BRUIN(i);

		vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_CTRL(i), ctrl);

		/*
		 * Hardcode the blending क्रमmula to
		 *
		 *	DSTc = DSTc * (1 - SRCa) + SRCc * SRCa
		 *	DSTa = DSTa * (1 - SRCa) + SRCa
		 *
		 * when the SRC input isn't premultiplied, and to
		 *
		 *	DSTc = DSTc * (1 - SRCa) + SRCc
		 *	DSTa = DSTa * (1 - SRCa) + SRCa
		 *
		 * otherwise.
		 */
		vsp1_brx_ग_लिखो(brx, dlb, VI6_BRU_BLD(i),
			       VI6_BRU_BLD_CCMDX_255_SRC_A |
			       (premultiplied ? VI6_BRU_BLD_CCMDY_COEFY :
						VI6_BRU_BLD_CCMDY_SRC_A) |
			       VI6_BRU_BLD_ACMDX_255_SRC_A |
			       VI6_BRU_BLD_ACMDY_COEFY |
			       (0xff << VI6_BRU_BLD_COEFY_SHIFT));
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations brx_entity_ops = अणु
	.configure_stream = brx_configure_stream,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_brx *vsp1_brx_create(काष्ठा vsp1_device *vsp1,
				 क्रमागत vsp1_entity_type type)
अणु
	काष्ठा vsp1_brx *brx;
	अचिन्हित पूर्णांक num_pads;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	brx = devm_kzalloc(vsp1->dev, माप(*brx), GFP_KERNEL);
	अगर (brx == शून्य)
		वापस ERR_PTR(-ENOMEM);

	brx->base = type == VSP1_ENTITY_BRU ? VI6_BRU_BASE : VI6_BRS_BASE;
	brx->entity.ops = &brx_entity_ops;
	brx->entity.type = type;

	अगर (type == VSP1_ENTITY_BRU) अणु
		num_pads = vsp1->info->num_bru_inमाला_दो + 1;
		name = "bru";
	पूर्ण अन्यथा अणु
		num_pads = 3;
		name = "brs";
	पूर्ण

	ret = vsp1_entity_init(vsp1, &brx->entity, name, num_pads, &brx_ops,
			       MEDIA_ENT_F_PROC_VIDEO_COMPOSER);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&brx->ctrls, 1);
	v4l2_ctrl_new_std(&brx->ctrls, &brx_ctrl_ops, V4L2_CID_BG_COLOR,
			  0, 0xffffff, 1, 0);

	brx->bgcolor = 0;

	brx->entity.subdev.ctrl_handler = &brx->ctrls;

	अगर (brx->ctrls.error) अणु
		dev_err(vsp1->dev, "%s: failed to initialize controls\n", name);
		ret = brx->ctrls.error;
		vsp1_entity_destroy(&brx->entity);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस brx;
पूर्ण
