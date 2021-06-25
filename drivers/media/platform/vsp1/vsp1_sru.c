<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_sru.c  --  R-Car VSP1 Super Resolution Unit
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_sru.h"

#घोषणा SRU_MIN_SIZE				4U
#घोषणा SRU_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_sru_ग_लिखो(काष्ठा vsp1_sru *sru,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

#घोषणा V4L2_CID_VSP1_SRU_INTENSITY		(V4L2_CID_USER_BASE | 0x1001)

काष्ठा vsp1_sru_param अणु
	u32 ctrl0;
	u32 ctrl2;
पूर्ण;

#घोषणा VI6_SRU_CTRL0_PARAMS(p0, p1)			\
	(((p0) << VI6_SRU_CTRL0_PARAM0_SHIFT) |		\
	 ((p1) << VI6_SRU_CTRL0_PARAM1_SHIFT))

#घोषणा VI6_SRU_CTRL2_PARAMS(p6, p7, p8)		\
	(((p6) << VI6_SRU_CTRL2_PARAM6_SHIFT) |		\
	 ((p7) << VI6_SRU_CTRL2_PARAM7_SHIFT) |		\
	 ((p8) << VI6_SRU_CTRL2_PARAM8_SHIFT))

अटल स्थिर काष्ठा vsp1_sru_param vsp1_sru_params[] = अणु
	अणु
		.ctrl0 = VI6_SRU_CTRL0_PARAMS(256, 4) | VI6_SRU_CTRL0_EN,
		.ctrl2 = VI6_SRU_CTRL2_PARAMS(24, 40, 255),
	पूर्ण, अणु
		.ctrl0 = VI6_SRU_CTRL0_PARAMS(256, 4) | VI6_SRU_CTRL0_EN,
		.ctrl2 = VI6_SRU_CTRL2_PARAMS(8, 16, 255),
	पूर्ण, अणु
		.ctrl0 = VI6_SRU_CTRL0_PARAMS(384, 5) | VI6_SRU_CTRL0_EN,
		.ctrl2 = VI6_SRU_CTRL2_PARAMS(36, 60, 255),
	पूर्ण, अणु
		.ctrl0 = VI6_SRU_CTRL0_PARAMS(384, 5) | VI6_SRU_CTRL0_EN,
		.ctrl2 = VI6_SRU_CTRL2_PARAMS(12, 27, 255),
	पूर्ण, अणु
		.ctrl0 = VI6_SRU_CTRL0_PARAMS(511, 6) | VI6_SRU_CTRL0_EN,
		.ctrl2 = VI6_SRU_CTRL2_PARAMS(48, 80, 255),
	पूर्ण, अणु
		.ctrl0 = VI6_SRU_CTRL0_PARAMS(511, 6) | VI6_SRU_CTRL0_EN,
		.ctrl2 = VI6_SRU_CTRL2_PARAMS(16, 36, 255),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sru_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_sru *sru =
		container_of(ctrl->handler, काष्ठा vsp1_sru, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VSP1_SRU_INTENSITY:
		sru->पूर्णांकensity = ctrl->val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sru_ctrl_ops = अणु
	.s_ctrl = sru_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config sru_पूर्णांकensity_control = अणु
	.ops = &sru_ctrl_ops,
	.id = V4L2_CID_VSP1_SRU_INTENSITY,
	.name = "Intensity",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 1,
	.max = 6,
	.def = 1,
	.step = 1,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल पूर्णांक sru_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
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

अटल पूर्णांक sru_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा vsp1_sru *sru = to_sru(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	config = vsp1_entity_get_pad_config(&sru->entity, cfg, fse->which);
	अगर (!config)
		वापस -EINVAL;

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&sru->entity, config, SRU_PAD_SINK);

	mutex_lock(&sru->entity.lock);

	अगर (fse->index || fse->code != क्रमmat->code) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (fse->pad == SRU_PAD_SINK) अणु
		fse->min_width = SRU_MIN_SIZE;
		fse->max_width = SRU_MAX_SIZE;
		fse->min_height = SRU_MIN_SIZE;
		fse->max_height = SRU_MAX_SIZE;
	पूर्ण अन्यथा अणु
		fse->min_width = क्रमmat->width;
		fse->min_height = क्रमmat->height;
		अगर (क्रमmat->width <= SRU_MAX_SIZE / 2 &&
		    क्रमmat->height <= SRU_MAX_SIZE / 2) अणु
			fse->max_width = क्रमmat->width * 2;
			fse->max_height = क्रमmat->height * 2;
		पूर्ण अन्यथा अणु
			fse->max_width = क्रमmat->width;
			fse->max_height = क्रमmat->height;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&sru->entity.lock);
	वापस ret;
पूर्ण

अटल व्योम sru_try_क्रमmat(काष्ठा vsp1_sru *sru,
			   काष्ठा v4l2_subdev_pad_config *config,
			   अचिन्हित पूर्णांक pad, काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक input_area;
	अचिन्हित पूर्णांक output_area;

	चयन (pad) अणु
	हाल SRU_PAD_SINK:
		/* Default to YUV अगर the requested क्रमmat is not supported. */
		अगर (fmt->code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
		    fmt->code != MEDIA_BUS_FMT_AYUV8_1X32)
			fmt->code = MEDIA_BUS_FMT_AYUV8_1X32;

		fmt->width = clamp(fmt->width, SRU_MIN_SIZE, SRU_MAX_SIZE);
		fmt->height = clamp(fmt->height, SRU_MIN_SIZE, SRU_MAX_SIZE);
		अवरोध;

	हाल SRU_PAD_SOURCE:
		/* The SRU can't perक्रमm क्रमmat conversion. */
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&sru->entity, config,
						    SRU_PAD_SINK);
		fmt->code = क्रमmat->code;

		/*
		 * We can upscale by 2 in both direction, but not independently.
		 * Compare the input and output rectangles areas (aव्योमing
		 * पूर्णांकeger overflows on the output): अगर the requested output
		 * area is larger than 1.5^2 the input area upscale by two,
		 * otherwise करोn't scale.
		 */
		input_area = क्रमmat->width * क्रमmat->height;
		output_area = min(fmt->width, SRU_MAX_SIZE)
			    * min(fmt->height, SRU_MAX_SIZE);

		अगर (fmt->width <= SRU_MAX_SIZE / 2 &&
		    fmt->height <= SRU_MAX_SIZE / 2 &&
		    output_area > input_area * 9 / 4) अणु
			fmt->width = क्रमmat->width * 2;
			fmt->height = क्रमmat->height * 2;
		पूर्ण अन्यथा अणु
			fmt->width = क्रमmat->width;
			fmt->height = क्रमmat->height;
		पूर्ण
		अवरोध;
	पूर्ण

	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

अटल पूर्णांक sru_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_sru *sru = to_sru(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	mutex_lock(&sru->entity.lock);

	config = vsp1_entity_get_pad_config(&sru->entity, cfg, fmt->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	sru_try_क्रमmat(sru, config, fmt->pad, &fmt->क्रमmat);

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&sru->entity, config, fmt->pad);
	*क्रमmat = fmt->क्रमmat;

	अगर (fmt->pad == SRU_PAD_SINK) अणु
		/* Propagate the क्रमmat to the source pad. */
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&sru->entity, config,
						    SRU_PAD_SOURCE);
		*क्रमmat = fmt->क्रमmat;

		sru_try_क्रमmat(sru, config, SRU_PAD_SOURCE, क्रमmat);
	पूर्ण

करोne:
	mutex_unlock(&sru->entity.lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops sru_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = sru_क्रमागत_mbus_code,
	.क्रमागत_frame_size = sru_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = sru_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops sru_ops = अणु
	.pad    = &sru_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम sru_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	स्थिर काष्ठा vsp1_sru_param *param;
	काष्ठा vsp1_sru *sru = to_sru(&entity->subdev);
	काष्ठा v4l2_mbus_framefmt *input;
	काष्ठा v4l2_mbus_framefmt *output;
	u32 ctrl0;

	input = vsp1_entity_get_pad_क्रमmat(&sru->entity, sru->entity.config,
					   SRU_PAD_SINK);
	output = vsp1_entity_get_pad_क्रमmat(&sru->entity, sru->entity.config,
					    SRU_PAD_SOURCE);

	अगर (input->code == MEDIA_BUS_FMT_ARGB8888_1X32)
		ctrl0 = VI6_SRU_CTRL0_PARAM2 | VI6_SRU_CTRL0_PARAM3
		      | VI6_SRU_CTRL0_PARAM4;
	अन्यथा
		ctrl0 = VI6_SRU_CTRL0_PARAM3;

	अगर (input->width != output->width)
		ctrl0 |= VI6_SRU_CTRL0_MODE_UPSCALE;

	param = &vsp1_sru_params[sru->पूर्णांकensity - 1];

	ctrl0 |= param->ctrl0;

	vsp1_sru_ग_लिखो(sru, dlb, VI6_SRU_CTRL0, ctrl0);
	vsp1_sru_ग_लिखो(sru, dlb, VI6_SRU_CTRL1, VI6_SRU_CTRL1_PARAM5);
	vsp1_sru_ग_लिखो(sru, dlb, VI6_SRU_CTRL2, param->ctrl2);
पूर्ण

अटल अचिन्हित पूर्णांक sru_max_width(काष्ठा vsp1_entity *entity,
				  काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_sru *sru = to_sru(&entity->subdev);
	काष्ठा v4l2_mbus_framefmt *input;
	काष्ठा v4l2_mbus_framefmt *output;

	input = vsp1_entity_get_pad_क्रमmat(&sru->entity, sru->entity.config,
					   SRU_PAD_SINK);
	output = vsp1_entity_get_pad_क्रमmat(&sru->entity, sru->entity.config,
					    SRU_PAD_SOURCE);

	/*
	 * The maximum input width of the SRU is 288 input pixels, but 32
	 * pixels are reserved to support overlapping partition winकरोws when
	 * scaling.
	 */
	अगर (input->width != output->width)
		वापस 512;
	अन्यथा
		वापस 256;
पूर्ण

अटल व्योम sru_partition(काष्ठा vsp1_entity *entity,
			  काष्ठा vsp1_pipeline *pipe,
			  काष्ठा vsp1_partition *partition,
			  अचिन्हित पूर्णांक partition_idx,
			  काष्ठा vsp1_partition_winकरोw *winकरोw)
अणु
	काष्ठा vsp1_sru *sru = to_sru(&entity->subdev);
	काष्ठा v4l2_mbus_framefmt *input;
	काष्ठा v4l2_mbus_framefmt *output;

	input = vsp1_entity_get_pad_क्रमmat(&sru->entity, sru->entity.config,
					   SRU_PAD_SINK);
	output = vsp1_entity_get_pad_क्रमmat(&sru->entity, sru->entity.config,
					    SRU_PAD_SOURCE);

	/* Adapt अगर SRUx2 is enabled. */
	अगर (input->width != output->width) अणु
		winकरोw->width /= 2;
		winकरोw->left /= 2;
	पूर्ण

	partition->sru = *winकरोw;
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations sru_entity_ops = अणु
	.configure_stream = sru_configure_stream,
	.max_width = sru_max_width,
	.partition = sru_partition,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_sru *vsp1_sru_create(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_sru *sru;
	पूर्णांक ret;

	sru = devm_kzalloc(vsp1->dev, माप(*sru), GFP_KERNEL);
	अगर (sru == शून्य)
		वापस ERR_PTR(-ENOMEM);

	sru->entity.ops = &sru_entity_ops;
	sru->entity.type = VSP1_ENTITY_SRU;

	ret = vsp1_entity_init(vsp1, &sru->entity, "sru", 2, &sru_ops,
			       MEDIA_ENT_F_PROC_VIDEO_SCALER);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&sru->ctrls, 1);
	v4l2_ctrl_new_custom(&sru->ctrls, &sru_पूर्णांकensity_control, शून्य);

	sru->पूर्णांकensity = 1;

	sru->entity.subdev.ctrl_handler = &sru->ctrls;

	अगर (sru->ctrls.error) अणु
		dev_err(vsp1->dev, "sru: failed to initialize controls\n");
		ret = sru->ctrls.error;
		vsp1_entity_destroy(&sru->entity);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस sru;
पूर्ण
