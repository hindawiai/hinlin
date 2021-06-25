<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_lअगर.c  --  R-Car VSP1 LCD Controller Interface
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_lif.h"

#घोषणा LIF_MIN_SIZE				2U
#घोषणा LIF_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_lअगर_ग_लिखो(काष्ठा vsp1_lअगर *lअगर,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg + lअगर->entity.index * VI6_LIF_OFFSET,
			       data);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर अचिन्हित पूर्णांक lअगर_codes[] = अणु
	MEDIA_BUS_FMT_ARGB8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
पूर्ण;

अटल पूर्णांक lअगर_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, lअगर_codes,
					  ARRAY_SIZE(lअगर_codes));
पूर्ण

अटल पूर्णांक lअगर_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, LIF_MIN_SIZE,
					   LIF_MIN_SIZE, LIF_MAX_SIZE,
					   LIF_MAX_SIZE);
पूर्ण

अटल पूर्णांक lअगर_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	वापस vsp1_subdev_set_pad_क्रमmat(subdev, cfg, fmt, lअगर_codes,
					  ARRAY_SIZE(lअगर_codes),
					  LIF_MIN_SIZE, LIF_MIN_SIZE,
					  LIF_MAX_SIZE, LIF_MAX_SIZE);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops lअगर_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = lअगर_क्रमागत_mbus_code,
	.क्रमागत_frame_size = lअगर_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = lअगर_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops lअगर_ops = अणु
	.pad    = &lअगर_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम lअगर_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा vsp1_lअगर *lअगर = to_lअगर(&entity->subdev);
	अचिन्हित पूर्णांक hbth;
	अचिन्हित पूर्णांक obth;
	अचिन्हित पूर्णांक lbth;

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&lअगर->entity, lअगर->entity.config,
					    LIF_PAD_SOURCE);

	चयन (entity->vsp1->version & VI6_IP_VERSION_MODEL_MASK) अणु
	हाल VI6_IP_VERSION_MODEL_VSPD_GEN2:
	हाल VI6_IP_VERSION_MODEL_VSPD_V2H:
		hbth = 1536;
		obth = min(128U, (क्रमmat->width + 1) / 2 * क्रमmat->height - 4);
		lbth = 1520;
		अवरोध;

	हाल VI6_IP_VERSION_MODEL_VSPDL_GEN3:
	हाल VI6_IP_VERSION_MODEL_VSPD_V3:
		hbth = 0;
		obth = 1500;
		lbth = 0;
		अवरोध;

	हाल VI6_IP_VERSION_MODEL_VSPD_GEN3:
	शेष:
		hbth = 0;
		obth = 3000;
		lbth = 0;
		अवरोध;
	पूर्ण

	vsp1_lअगर_ग_लिखो(lअगर, dlb, VI6_LIF_CSBTH,
			(hbth << VI6_LIF_CSBTH_HBTH_SHIFT) |
			(lbth << VI6_LIF_CSBTH_LBTH_SHIFT));

	vsp1_lअगर_ग_लिखो(lअगर, dlb, VI6_LIF_CTRL,
			(obth << VI6_LIF_CTRL_OBTH_SHIFT) |
			(क्रमmat->code == 0 ? VI6_LIF_CTRL_CFMT : 0) |
			VI6_LIF_CTRL_REQSEL | VI6_LIF_CTRL_LIF_EN);

	/*
	 * On R-Car V3M the LIF0 buffer attribute रेजिस्टर has to be set to a
	 * non-शेष value to guarantee proper operation (otherwise artअगरacts
	 * may appear on the output). The value required by the manual is not
	 * explained but is likely a buffer size or threshold.
	 */
	अगर ((entity->vsp1->version & VI6_IP_VERSION_MASK) ==
	    (VI6_IP_VERSION_MODEL_VSPD_V3 | VI6_IP_VERSION_SOC_V3M))
		vsp1_lअगर_ग_लिखो(lअगर, dlb, VI6_LIF_LBA,
			       VI6_LIF_LBA_LBA0 |
			       (1536 << VI6_LIF_LBA_LBA1_SHIFT));
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations lअगर_entity_ops = अणु
	.configure_stream = lअगर_configure_stream,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_lअगर *vsp1_lअगर_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vsp1_lअगर *lअगर;
	पूर्णांक ret;

	lअगर = devm_kzalloc(vsp1->dev, माप(*lअगर), GFP_KERNEL);
	अगर (lअगर == शून्य)
		वापस ERR_PTR(-ENOMEM);

	lअगर->entity.ops = &lअगर_entity_ops;
	lअगर->entity.type = VSP1_ENTITY_LIF;
	lअगर->entity.index = index;

	/*
	 * The LIF is never exposed to userspace, but media entity registration
	 * requires a function to be set. Use PROC_VIDEO_PIXEL_FORMATTER just to
	 * aव्योम triggering a WARN_ON(), the value won't be seen anywhere.
	 */
	ret = vsp1_entity_init(vsp1, &lअगर->entity, "lif", 2, &lअगर_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस lअगर;
पूर्ण
