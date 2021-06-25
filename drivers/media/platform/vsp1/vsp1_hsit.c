<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_hsit.c  --  R-Car VSP1 Hue Saturation value (Inverse) Transक्रमm
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
#समावेश "vsp1_hsit.h"

#घोषणा HSIT_MIN_SIZE				4U
#घोषणा HSIT_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_hsit_ग_लिखो(काष्ठा vsp1_hsit *hsit,
				   काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल पूर्णांक hsit_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा vsp1_hsit *hsit = to_hsit(subdev);

	अगर (code->index > 0)
		वापस -EINVAL;

	अगर ((code->pad == HSIT_PAD_SINK && !hsit->inverse) |
	    (code->pad == HSIT_PAD_SOURCE && hsit->inverse))
		code->code = MEDIA_BUS_FMT_ARGB8888_1X32;
	अन्यथा
		code->code = MEDIA_BUS_FMT_AHSV8888_1X32;

	वापस 0;
पूर्ण

अटल पूर्णांक hsit_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, HSIT_MIN_SIZE,
					   HSIT_MIN_SIZE, HSIT_MAX_SIZE,
					   HSIT_MAX_SIZE);
पूर्ण

अटल पूर्णांक hsit_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_hsit *hsit = to_hsit(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	mutex_lock(&hsit->entity.lock);

	config = vsp1_entity_get_pad_config(&hsit->entity, cfg, fmt->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&hsit->entity, config, fmt->pad);

	अगर (fmt->pad == HSIT_PAD_SOURCE) अणु
		/*
		 * The HST and HSI output क्रमmat code and resolution can't be
		 * modअगरied.
		 */
		fmt->क्रमmat = *क्रमmat;
		जाओ करोne;
	पूर्ण

	क्रमmat->code = hsit->inverse ? MEDIA_BUS_FMT_AHSV8888_1X32
		     : MEDIA_BUS_FMT_ARGB8888_1X32;
	क्रमmat->width = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.width,
				HSIT_MIN_SIZE, HSIT_MAX_SIZE);
	क्रमmat->height = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.height,
				 HSIT_MIN_SIZE, HSIT_MAX_SIZE);
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	fmt->क्रमmat = *क्रमmat;

	/* Propagate the क्रमmat to the source pad. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&hsit->entity, config,
					    HSIT_PAD_SOURCE);
	*क्रमmat = fmt->क्रमmat;
	क्रमmat->code = hsit->inverse ? MEDIA_BUS_FMT_ARGB8888_1X32
		     : MEDIA_BUS_FMT_AHSV8888_1X32;

करोne:
	mutex_unlock(&hsit->entity.lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops hsit_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = hsit_क्रमागत_mbus_code,
	.क्रमागत_frame_size = hsit_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = hsit_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops hsit_ops = अणु
	.pad    = &hsit_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम hsit_configure_stream(काष्ठा vsp1_entity *entity,
				  काष्ठा vsp1_pipeline *pipe,
				  काष्ठा vsp1_dl_list *dl,
				  काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_hsit *hsit = to_hsit(&entity->subdev);

	अगर (hsit->inverse)
		vsp1_hsit_ग_लिखो(hsit, dlb, VI6_HSI_CTRL, VI6_HSI_CTRL_EN);
	अन्यथा
		vsp1_hsit_ग_लिखो(hsit, dlb, VI6_HST_CTRL, VI6_HST_CTRL_EN);
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations hsit_entity_ops = अणु
	.configure_stream = hsit_configure_stream,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_hsit *vsp1_hsit_create(काष्ठा vsp1_device *vsp1, bool inverse)
अणु
	काष्ठा vsp1_hsit *hsit;
	पूर्णांक ret;

	hsit = devm_kzalloc(vsp1->dev, माप(*hsit), GFP_KERNEL);
	अगर (hsit == शून्य)
		वापस ERR_PTR(-ENOMEM);

	hsit->inverse = inverse;

	hsit->entity.ops = &hsit_entity_ops;

	अगर (inverse)
		hsit->entity.type = VSP1_ENTITY_HSI;
	अन्यथा
		hsit->entity.type = VSP1_ENTITY_HST;

	ret = vsp1_entity_init(vsp1, &hsit->entity, inverse ? "hsi" : "hst",
			       2, &hsit_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_ENC_CONV);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस hsit;
पूर्ण
