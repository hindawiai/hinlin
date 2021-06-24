<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_clu.c  --  R-Car VSP1 Cubic Look-Up Table
 *
 * Copyright (C) 2015-2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_clu.h"
#समावेश "vsp1_dl.h"

#घोषणा CLU_MIN_SIZE				4U
#घोषणा CLU_MAX_SIZE				8190U

#घोषणा CLU_SIZE				(17 * 17 * 17)

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_clu_ग_लिखो(काष्ठा vsp1_clu *clu,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

#घोषणा V4L2_CID_VSP1_CLU_TABLE			(V4L2_CID_USER_BASE | 0x1001)
#घोषणा V4L2_CID_VSP1_CLU_MODE			(V4L2_CID_USER_BASE | 0x1002)
#घोषणा V4L2_CID_VSP1_CLU_MODE_2D		0
#घोषणा V4L2_CID_VSP1_CLU_MODE_3D		1

अटल पूर्णांक clu_set_table(काष्ठा vsp1_clu *clu, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_dl_body *dlb;
	अचिन्हित पूर्णांक i;

	dlb = vsp1_dl_body_get(clu->pool);
	अगर (!dlb)
		वापस -ENOMEM;

	vsp1_dl_body_ग_लिखो(dlb, VI6_CLU_ADDR, 0);
	क्रम (i = 0; i < CLU_SIZE; ++i)
		vsp1_dl_body_ग_लिखो(dlb, VI6_CLU_DATA, ctrl->p_new.p_u32[i]);

	spin_lock_irq(&clu->lock);
	swap(clu->clu, dlb);
	spin_unlock_irq(&clu->lock);

	vsp1_dl_body_put(dlb);
	वापस 0;
पूर्ण

अटल पूर्णांक clu_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_clu *clu =
		container_of(ctrl->handler, काष्ठा vsp1_clu, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VSP1_CLU_TABLE:
		clu_set_table(clu, ctrl);
		अवरोध;

	हाल V4L2_CID_VSP1_CLU_MODE:
		clu->mode = ctrl->val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops clu_ctrl_ops = अणु
	.s_ctrl = clu_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config clu_table_control = अणु
	.ops = &clu_ctrl_ops,
	.id = V4L2_CID_VSP1_CLU_TABLE,
	.name = "Look-Up Table",
	.type = V4L2_CTRL_TYPE_U32,
	.min = 0x00000000,
	.max = 0x00ffffff,
	.step = 1,
	.def = 0,
	.dims = अणु 17, 17, 17 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर clu_mode_menu[] = अणु
	"2D",
	"3D",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config clu_mode_control = अणु
	.ops = &clu_ctrl_ops,
	.id = V4L2_CID_VSP1_CLU_MODE,
	.name = "Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.min = 0,
	.max = 1,
	.def = 1,
	.qmenu = clu_mode_menu,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Pad Operations
 */

अटल स्थिर अचिन्हित पूर्णांक clu_codes[] = अणु
	MEDIA_BUS_FMT_ARGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
पूर्ण;

अटल पूर्णांक clu_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, clu_codes,
					  ARRAY_SIZE(clu_codes));
पूर्ण

अटल पूर्णांक clu_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, CLU_MIN_SIZE,
					   CLU_MIN_SIZE, CLU_MAX_SIZE,
					   CLU_MAX_SIZE);
पूर्ण

अटल पूर्णांक clu_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	वापस vsp1_subdev_set_pad_क्रमmat(subdev, cfg, fmt, clu_codes,
					  ARRAY_SIZE(clu_codes),
					  CLU_MIN_SIZE, CLU_MIN_SIZE,
					  CLU_MAX_SIZE, CLU_MAX_SIZE);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर काष्ठा v4l2_subdev_pad_ops clu_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = clu_क्रमागत_mbus_code,
	.क्रमागत_frame_size = clu_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = clu_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops clu_ops = अणु
	.pad    = &clu_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम clu_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_clu *clu = to_clu(&entity->subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	/*
	 * The yuv_mode can't be changed during streaming. Cache it पूर्णांकernally
	 * क्रम future runसमय configuration calls.
	 */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&clu->entity,
					    clu->entity.config,
					    CLU_PAD_SINK);
	clu->yuv_mode = क्रमmat->code == MEDIA_BUS_FMT_AYUV8_1X32;
पूर्ण

अटल व्योम clu_configure_frame(काष्ठा vsp1_entity *entity,
				काष्ठा vsp1_pipeline *pipe,
				काष्ठा vsp1_dl_list *dl,
				काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_clu *clu = to_clu(&entity->subdev);
	काष्ठा vsp1_dl_body *clu_dlb;
	अचिन्हित दीर्घ flags;
	u32 ctrl = VI6_CLU_CTRL_AAI | VI6_CLU_CTRL_MVS | VI6_CLU_CTRL_EN;

	/* 2D mode can only be used with the YCbCr pixel encoding. */
	अगर (clu->mode == V4L2_CID_VSP1_CLU_MODE_2D && clu->yuv_mode)
		ctrl |= VI6_CLU_CTRL_AX1I_2D | VI6_CLU_CTRL_AX2I_2D
		     |  VI6_CLU_CTRL_OS0_2D | VI6_CLU_CTRL_OS1_2D
		     |  VI6_CLU_CTRL_OS2_2D | VI6_CLU_CTRL_M2D;

	vsp1_clu_ग_लिखो(clu, dlb, VI6_CLU_CTRL, ctrl);

	spin_lock_irqsave(&clu->lock, flags);
	clu_dlb = clu->clu;
	clu->clu = शून्य;
	spin_unlock_irqrestore(&clu->lock, flags);

	अगर (clu_dlb) अणु
		vsp1_dl_list_add_body(dl, clu_dlb);

		/* Release our local reference. */
		vsp1_dl_body_put(clu_dlb);
	पूर्ण
पूर्ण

अटल व्योम clu_destroy(काष्ठा vsp1_entity *entity)
अणु
	काष्ठा vsp1_clu *clu = to_clu(&entity->subdev);

	vsp1_dl_body_pool_destroy(clu->pool);
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations clu_entity_ops = अणु
	.configure_stream = clu_configure_stream,
	.configure_frame = clu_configure_frame,
	.destroy = clu_destroy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_clu *vsp1_clu_create(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_clu *clu;
	पूर्णांक ret;

	clu = devm_kzalloc(vsp1->dev, माप(*clu), GFP_KERNEL);
	अगर (clu == शून्य)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&clu->lock);

	clu->entity.ops = &clu_entity_ops;
	clu->entity.type = VSP1_ENTITY_CLU;

	ret = vsp1_entity_init(vsp1, &clu->entity, "clu", 2, &clu_ops,
			       MEDIA_ENT_F_PROC_VIDEO_LUT);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/*
	 * Pre-allocate a body pool, with 3 bodies allowing a userspace update
	 * beक्रमe the hardware has committed a previous set of tables, handling
	 * both the queued and pending dl entries. One extra entry is added to
	 * the CLU_SIZE to allow क्रम the VI6_CLU_ADDR header.
	 */
	clu->pool = vsp1_dl_body_pool_create(clu->entity.vsp1, 3, CLU_SIZE + 1,
					     0);
	अगर (!clu->pool)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&clu->ctrls, 2);
	v4l2_ctrl_new_custom(&clu->ctrls, &clu_table_control, शून्य);
	v4l2_ctrl_new_custom(&clu->ctrls, &clu_mode_control, शून्य);

	clu->entity.subdev.ctrl_handler = &clu->ctrls;

	अगर (clu->ctrls.error) अणु
		dev_err(vsp1->dev, "clu: failed to initialize controls\n");
		ret = clu->ctrls.error;
		vsp1_entity_destroy(&clu->entity);
		वापस ERR_PTR(ret);
	पूर्ण

	v4l2_ctrl_handler_setup(&clu->ctrls);

	वापस clu;
पूर्ण
