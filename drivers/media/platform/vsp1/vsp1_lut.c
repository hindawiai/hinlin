<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_lut.c  --  R-Car VSP1 Look-Up Table
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
#समावेश "vsp1_lut.h"

#घोषणा LUT_MIN_SIZE				4U
#घोषणा LUT_MAX_SIZE				8190U

#घोषणा LUT_SIZE				256

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_lut_ग_लिखो(काष्ठा vsp1_lut *lut,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

#घोषणा V4L2_CID_VSP1_LUT_TABLE			(V4L2_CID_USER_BASE | 0x1001)

अटल पूर्णांक lut_set_table(काष्ठा vsp1_lut *lut, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_dl_body *dlb;
	अचिन्हित पूर्णांक i;

	dlb = vsp1_dl_body_get(lut->pool);
	अगर (!dlb)
		वापस -ENOMEM;

	क्रम (i = 0; i < LUT_SIZE; ++i)
		vsp1_dl_body_ग_लिखो(dlb, VI6_LUT_TABLE + 4 * i,
				       ctrl->p_new.p_u32[i]);

	spin_lock_irq(&lut->lock);
	swap(lut->lut, dlb);
	spin_unlock_irq(&lut->lock);

	vsp1_dl_body_put(dlb);
	वापस 0;
पूर्ण

अटल पूर्णांक lut_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_lut *lut =
		container_of(ctrl->handler, काष्ठा vsp1_lut, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VSP1_LUT_TABLE:
		lut_set_table(lut, ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops lut_ctrl_ops = अणु
	.s_ctrl = lut_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config lut_table_control = अणु
	.ops = &lut_ctrl_ops,
	.id = V4L2_CID_VSP1_LUT_TABLE,
	.name = "Look-Up Table",
	.type = V4L2_CTRL_TYPE_U32,
	.min = 0x00000000,
	.max = 0x00ffffff,
	.step = 1,
	.def = 0,
	.dims = अणु LUT_SIZE पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Pad Operations
 */

अटल स्थिर अचिन्हित पूर्णांक lut_codes[] = अणु
	MEDIA_BUS_FMT_ARGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
पूर्ण;

अटल पूर्णांक lut_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, lut_codes,
					  ARRAY_SIZE(lut_codes));
पूर्ण

अटल पूर्णांक lut_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, LUT_MIN_SIZE,
					   LUT_MIN_SIZE, LUT_MAX_SIZE,
					   LUT_MAX_SIZE);
पूर्ण

अटल पूर्णांक lut_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	वापस vsp1_subdev_set_pad_क्रमmat(subdev, cfg, fmt, lut_codes,
					  ARRAY_SIZE(lut_codes),
					  LUT_MIN_SIZE, LUT_MIN_SIZE,
					  LUT_MAX_SIZE, LUT_MAX_SIZE);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर काष्ठा v4l2_subdev_pad_ops lut_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = lut_क्रमागत_mbus_code,
	.क्रमागत_frame_size = lut_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = lut_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops lut_ops = अणु
	.pad    = &lut_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम lut_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_lut *lut = to_lut(&entity->subdev);

	vsp1_lut_ग_लिखो(lut, dlb, VI6_LUT_CTRL, VI6_LUT_CTRL_EN);
पूर्ण

अटल व्योम lut_configure_frame(काष्ठा vsp1_entity *entity,
				काष्ठा vsp1_pipeline *pipe,
				काष्ठा vsp1_dl_list *dl,
				काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_lut *lut = to_lut(&entity->subdev);
	काष्ठा vsp1_dl_body *lut_dlb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lut->lock, flags);
	lut_dlb = lut->lut;
	lut->lut = शून्य;
	spin_unlock_irqrestore(&lut->lock, flags);

	अगर (lut_dlb) अणु
		vsp1_dl_list_add_body(dl, lut_dlb);

		/* Release our local reference. */
		vsp1_dl_body_put(lut_dlb);
	पूर्ण
पूर्ण

अटल व्योम lut_destroy(काष्ठा vsp1_entity *entity)
अणु
	काष्ठा vsp1_lut *lut = to_lut(&entity->subdev);

	vsp1_dl_body_pool_destroy(lut->pool);
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations lut_entity_ops = अणु
	.configure_stream = lut_configure_stream,
	.configure_frame = lut_configure_frame,
	.destroy = lut_destroy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_lut *vsp1_lut_create(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_lut *lut;
	पूर्णांक ret;

	lut = devm_kzalloc(vsp1->dev, माप(*lut), GFP_KERNEL);
	अगर (lut == शून्य)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&lut->lock);

	lut->entity.ops = &lut_entity_ops;
	lut->entity.type = VSP1_ENTITY_LUT;

	ret = vsp1_entity_init(vsp1, &lut->entity, "lut", 2, &lut_ops,
			       MEDIA_ENT_F_PROC_VIDEO_LUT);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/*
	 * Pre-allocate a body pool, with 3 bodies allowing a userspace update
	 * beक्रमe the hardware has committed a previous set of tables, handling
	 * both the queued and pending dl entries.
	 */
	lut->pool = vsp1_dl_body_pool_create(vsp1, 3, LUT_SIZE, 0);
	अगर (!lut->pool)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&lut->ctrls, 1);
	v4l2_ctrl_new_custom(&lut->ctrls, &lut_table_control, शून्य);

	lut->entity.subdev.ctrl_handler = &lut->ctrls;

	अगर (lut->ctrls.error) अणु
		dev_err(vsp1->dev, "lut: failed to initialize controls\n");
		ret = lut->ctrls.error;
		vsp1_entity_destroy(&lut->entity);
		वापस ERR_PTR(ret);
	पूर्ण

	v4l2_ctrl_handler_setup(&lut->ctrls);

	वापस lut;
पूर्ण
