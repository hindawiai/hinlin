<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_hgt.c  --  R-Car VSP1 Histogram Generator 2D
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Niklas Sथघderlund (niklas.soderlund@ragnatech.se)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_hgt.h"

#घोषणा HGT_DATA_SIZE				((2 +  6 * 32) * 4)

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत u32 vsp1_hgt_पढ़ो(काष्ठा vsp1_hgt *hgt, u32 reg)
अणु
	वापस vsp1_पढ़ो(hgt->histo.entity.vsp1, reg);
पूर्ण

अटल अंतरभूत व्योम vsp1_hgt_ग_लिखो(काष्ठा vsp1_hgt *hgt,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Frame End Handler
 */

व्योम vsp1_hgt_frame_end(काष्ठा vsp1_entity *entity)
अणु
	काष्ठा vsp1_hgt *hgt = to_hgt(&entity->subdev);
	काष्ठा vsp1_histogram_buffer *buf;
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक n;
	u32 *data;

	buf = vsp1_histogram_buffer_get(&hgt->histo);
	अगर (!buf)
		वापस;

	data = buf->addr;

	*data++ = vsp1_hgt_पढ़ो(hgt, VI6_HGT_MAXMIN);
	*data++ = vsp1_hgt_पढ़ो(hgt, VI6_HGT_SUM);

	क्रम (m = 0; m < 6; ++m)
		क्रम (n = 0; n < 32; ++n)
			*data++ = vsp1_hgt_पढ़ो(hgt, VI6_HGT_HISTO(m, n));

	vsp1_histogram_buffer_complete(&hgt->histo, buf, HGT_DATA_SIZE);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

#घोषणा V4L2_CID_VSP1_HGT_HUE_AREAS	(V4L2_CID_USER_BASE | 0x1001)

अटल पूर्णांक hgt_hue_areas_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	स्थिर u8 *values = ctrl->p_new.p_u8;
	अचिन्हित पूर्णांक i;

	/*
	 * The hardware has स्थिरraपूर्णांकs on the hue area boundaries beyond the
	 * control min, max and step. The values must match one of the following
	 * expressions.
	 *
	 * 0L <= 0U <= 1L <= 1U <= 2L <= 2U <= 3L <= 3U <= 4L <= 4U <= 5L <= 5U
	 * 0U <= 1L <= 1U <= 2L <= 2U <= 3L <= 3U <= 4L <= 4U <= 5L <= 5U <= 0L
	 *
	 * Start by verअगरying the common part...
	 */
	क्रम (i = 1; i < (HGT_NUM_HUE_AREAS * 2) - 1; ++i) अणु
		अगर (values[i] > values[i+1])
			वापस -EINVAL;
	पूर्ण

	/* ... and handle 0L separately. */
	अगर (values[0] > values[1] && values[11] > values[0])
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hgt_hue_areas_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vsp1_hgt *hgt = container_of(ctrl->handler, काष्ठा vsp1_hgt,
					    ctrls);

	स_नकल(hgt->hue_areas, ctrl->p_new.p_u8, माप(hgt->hue_areas));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops hgt_hue_areas_ctrl_ops = अणु
	.try_ctrl = hgt_hue_areas_try_ctrl,
	.s_ctrl = hgt_hue_areas_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config hgt_hue_areas = अणु
	.ops = &hgt_hue_areas_ctrl_ops,
	.id = V4L2_CID_VSP1_HGT_HUE_AREAS,
	.name = "Boundary Values for Hue Area",
	.type = V4L2_CTRL_TYPE_U8,
	.min = 0,
	.max = 255,
	.def = 0,
	.step = 1,
	.dims = अणु 12 पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम hgt_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_hgt *hgt = to_hgt(&entity->subdev);
	काष्ठा v4l2_rect *compose;
	काष्ठा v4l2_rect *crop;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;
	u8 lower;
	u8 upper;
	अचिन्हित पूर्णांक i;

	crop = vsp1_entity_get_pad_selection(entity, entity->config,
					     HISTO_PAD_SINK, V4L2_SEL_TGT_CROP);
	compose = vsp1_entity_get_pad_selection(entity, entity->config,
						HISTO_PAD_SINK,
						V4L2_SEL_TGT_COMPOSE);

	vsp1_hgt_ग_लिखो(hgt, dlb, VI6_HGT_REGRST, VI6_HGT_REGRST_RCLEA);

	vsp1_hgt_ग_लिखो(hgt, dlb, VI6_HGT_OFFSET,
		       (crop->left << VI6_HGT_OFFSET_HOFFSET_SHIFT) |
		       (crop->top << VI6_HGT_OFFSET_VOFFSET_SHIFT));
	vsp1_hgt_ग_लिखो(hgt, dlb, VI6_HGT_SIZE,
		       (crop->width << VI6_HGT_SIZE_HSIZE_SHIFT) |
		       (crop->height << VI6_HGT_SIZE_VSIZE_SHIFT));

	mutex_lock(hgt->ctrls.lock);
	क्रम (i = 0; i < HGT_NUM_HUE_AREAS; ++i) अणु
		lower = hgt->hue_areas[i*2 + 0];
		upper = hgt->hue_areas[i*2 + 1];
		vsp1_hgt_ग_लिखो(hgt, dlb, VI6_HGT_HUE_AREA(i),
			       (lower << VI6_HGT_HUE_AREA_LOWER_SHIFT) |
			       (upper << VI6_HGT_HUE_AREA_UPPER_SHIFT));
	पूर्ण
	mutex_unlock(hgt->ctrls.lock);

	hratio = crop->width * 2 / compose->width / 3;
	vratio = crop->height * 2 / compose->height / 3;
	vsp1_hgt_ग_लिखो(hgt, dlb, VI6_HGT_MODE,
		       (hratio << VI6_HGT_MODE_HRATIO_SHIFT) |
		       (vratio << VI6_HGT_MODE_VRATIO_SHIFT));
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations hgt_entity_ops = अणु
	.configure_stream = hgt_configure_stream,
	.destroy = vsp1_histogram_destroy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

अटल स्थिर अचिन्हित पूर्णांक hgt_mbus_क्रमmats[] = अणु
	MEDIA_BUS_FMT_AHSV8888_1X32,
पूर्ण;

काष्ठा vsp1_hgt *vsp1_hgt_create(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_hgt *hgt;
	पूर्णांक ret;

	hgt = devm_kzalloc(vsp1->dev, माप(*hgt), GFP_KERNEL);
	अगर (hgt == शून्य)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&hgt->ctrls, 1);
	v4l2_ctrl_new_custom(&hgt->ctrls, &hgt_hue_areas, शून्य);

	hgt->histo.entity.subdev.ctrl_handler = &hgt->ctrls;

	/* Initialize the video device and queue क्रम statistics data. */
	ret = vsp1_histogram_init(vsp1, &hgt->histo, VSP1_ENTITY_HGT, "hgt",
				  &hgt_entity_ops, hgt_mbus_क्रमmats,
				  ARRAY_SIZE(hgt_mbus_क्रमmats),
				  HGT_DATA_SIZE, V4L2_META_FMT_VSP1_HGT);
	अगर (ret < 0) अणु
		vsp1_entity_destroy(&hgt->histo.entity);
		वापस ERR_PTR(ret);
	पूर्ण

	v4l2_ctrl_handler_setup(&hgt->ctrls);

	वापस hgt;
पूर्ण
