<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_uअगर.c  --  R-Car VSP1 User Logic Interface
 *
 * Copyright (C) 2017-2018 Laurent Pinअक्षरt
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sys_soc.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_entity.h"
#समावेश "vsp1_uif.h"

#घोषणा UIF_MIN_SIZE				4U
#घोषणा UIF_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत u32 vsp1_uअगर_पढ़ो(काष्ठा vsp1_uअगर *uअगर, u32 reg)
अणु
	वापस vsp1_पढ़ो(uअगर->entity.vsp1,
			 uअगर->entity.index * VI6_UIF_OFFSET + reg);
पूर्ण

अटल अंतरभूत व्योम vsp1_uअगर_ग_लिखो(काष्ठा vsp1_uअगर *uअगर,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg + uअगर->entity.index * VI6_UIF_OFFSET, data);
पूर्ण

u32 vsp1_uअगर_get_crc(काष्ठा vsp1_uअगर *uअगर)
अणु
	वापस vsp1_uअगर_पढ़ो(uअगर, VI6_UIF_DISCOM_DOCMCCRCR);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Pad Operations
 */

अटल स्थिर अचिन्हित पूर्णांक uअगर_codes[] = अणु
	MEDIA_BUS_FMT_ARGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
पूर्ण;

अटल पूर्णांक uअगर_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, uअगर_codes,
					  ARRAY_SIZE(uअगर_codes));
पूर्ण

अटल पूर्णांक uअगर_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, UIF_MIN_SIZE,
					   UIF_MIN_SIZE, UIF_MAX_SIZE,
					   UIF_MAX_SIZE);
पूर्ण

अटल पूर्णांक uअगर_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	वापस vsp1_subdev_set_pad_क्रमmat(subdev, cfg, fmt, uअगर_codes,
					  ARRAY_SIZE(uअगर_codes),
					  UIF_MIN_SIZE, UIF_MIN_SIZE,
					  UIF_MAX_SIZE, UIF_MAX_SIZE);
पूर्ण

अटल पूर्णांक uअगर_get_selection(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_uअगर *uअगर = to_uअगर(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	अगर (sel->pad != UIF_PAD_SINK)
		वापस -EINVAL;

	mutex_lock(&uअगर->entity.lock);

	config = vsp1_entity_get_pad_config(&uअगर->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&uअगर->entity, config,
						    UIF_PAD_SINK);
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = क्रमmat->width;
		sel->r.height = क्रमmat->height;
		अवरोध;

	हाल V4L2_SEL_TGT_CROP:
		sel->r = *vsp1_entity_get_pad_selection(&uअगर->entity, config,
							sel->pad, sel->target);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

करोne:
	mutex_unlock(&uअगर->entity.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक uअगर_set_selection(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_uअगर *uअगर = to_uअगर(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *selection;
	पूर्णांक ret = 0;

	अगर (sel->pad != UIF_PAD_SINK ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&uअगर->entity.lock);

	config = vsp1_entity_get_pad_config(&uअगर->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* The crop rectangle must be inside the input frame. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&uअगर->entity, config, UIF_PAD_SINK);

	sel->r.left = clamp_t(अचिन्हित पूर्णांक, sel->r.left, 0, क्रमmat->width - 1);
	sel->r.top = clamp_t(अचिन्हित पूर्णांक, sel->r.top, 0, क्रमmat->height - 1);
	sel->r.width = clamp_t(अचिन्हित पूर्णांक, sel->r.width, UIF_MIN_SIZE,
			       क्रमmat->width - sel->r.left);
	sel->r.height = clamp_t(अचिन्हित पूर्णांक, sel->r.height, UIF_MIN_SIZE,
				क्रमmat->height - sel->r.top);

	/* Store the crop rectangle. */
	selection = vsp1_entity_get_pad_selection(&uअगर->entity, config,
						  sel->pad, V4L2_SEL_TGT_CROP);
	*selection = sel->r;

करोne:
	mutex_unlock(&uअगर->entity.lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर काष्ठा v4l2_subdev_pad_ops uअगर_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = uअगर_क्रमागत_mbus_code,
	.क्रमागत_frame_size = uअगर_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = uअगर_set_क्रमmat,
	.get_selection = uअगर_get_selection,
	.set_selection = uअगर_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops uअगर_ops = अणु
	.pad    = &uअगर_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम uअगर_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_uअगर *uअगर = to_uअगर(&entity->subdev);
	स्थिर काष्ठा v4l2_rect *crop;
	अचिन्हित पूर्णांक left;
	अचिन्हित पूर्णांक width;

	vsp1_uअगर_ग_लिखो(uअगर, dlb, VI6_UIF_DISCOM_DOCMPMR,
		       VI6_UIF_DISCOM_DOCMPMR_SEL(9));

	crop = vsp1_entity_get_pad_selection(entity, entity->config,
					     UIF_PAD_SINK, V4L2_SEL_TGT_CROP);

	left = crop->left;
	width = crop->width;

	/* On M3-W the horizontal coordinates are twice the रेजिस्टर value. */
	अगर (uअगर->m3w_quirk) अणु
		left /= 2;
		width /= 2;
	पूर्ण

	vsp1_uअगर_ग_लिखो(uअगर, dlb, VI6_UIF_DISCOM_DOCMSPXR, left);
	vsp1_uअगर_ग_लिखो(uअगर, dlb, VI6_UIF_DISCOM_DOCMSPYR, crop->top);
	vsp1_uअगर_ग_लिखो(uअगर, dlb, VI6_UIF_DISCOM_DOCMSZXR, width);
	vsp1_uअगर_ग_लिखो(uअगर, dlb, VI6_UIF_DISCOM_DOCMSZYR, crop->height);

	vsp1_uअगर_ग_लिखो(uअगर, dlb, VI6_UIF_DISCOM_DOCMCR,
		       VI6_UIF_DISCOM_DOCMCR_CMPR);
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations uअगर_entity_ops = अणु
	.configure_stream = uअगर_configure_stream,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

अटल स्थिर काष्ठा soc_device_attribute vsp1_r8a7796[] = अणु
	अणु .soc_id = "r8a7796" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा vsp1_uअगर *vsp1_uअगर_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vsp1_uअगर *uअगर;
	अक्षर name[6];
	पूर्णांक ret;

	uअगर = devm_kzalloc(vsp1->dev, माप(*uअगर), GFP_KERNEL);
	अगर (!uअगर)
		वापस ERR_PTR(-ENOMEM);

	अगर (soc_device_match(vsp1_r8a7796))
		uअगर->m3w_quirk = true;

	uअगर->entity.ops = &uअगर_entity_ops;
	uअगर->entity.type = VSP1_ENTITY_UIF;
	uअगर->entity.index = index;

	/* The datasheet names the two UIF instances UIF4 and UIF5. */
	प्र_लिखो(name, "uif.%u", index + 4);
	ret = vsp1_entity_init(vsp1, &uअगर->entity, name, 2, &uअगर_ops,
			       MEDIA_ENT_F_PROC_VIDEO_STATISTICS);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस uअगर;
पूर्ण
