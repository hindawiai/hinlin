<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_hgo.c  --  R-Car VSP1 Histogram Generator 1D
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_hgo.h"

#घोषणा HGO_DATA_SIZE				((2 + 256) * 4)

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत u32 vsp1_hgo_पढ़ो(काष्ठा vsp1_hgo *hgo, u32 reg)
अणु
	वापस vsp1_पढ़ो(hgo->histo.entity.vsp1, reg);
पूर्ण

अटल अंतरभूत व्योम vsp1_hgo_ग_लिखो(काष्ठा vsp1_hgo *hgo,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Frame End Handler
 */

व्योम vsp1_hgo_frame_end(काष्ठा vsp1_entity *entity)
अणु
	काष्ठा vsp1_hgo *hgo = to_hgo(&entity->subdev);
	काष्ठा vsp1_histogram_buffer *buf;
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;
	u32 *data;

	buf = vsp1_histogram_buffer_get(&hgo->histo);
	अगर (!buf)
		वापस;

	data = buf->addr;

	अगर (hgo->num_bins == 256) अणु
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_SUM);

		क्रम (i = 0; i < 256; ++i) अणु
			vsp1_ग_लिखो(hgo->histo.entity.vsp1,
				   VI6_HGO_EXT_HIST_ADDR, i);
			*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_EXT_HIST_DATA);
		पूर्ण

		size = (2 + 256) * माप(u32);
	पूर्ण अन्यथा अगर (hgo->max_rgb) अणु
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_SUM);

		क्रम (i = 0; i < 64; ++i)
			*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_HISTO(i));

		size = (2 + 64) * माप(u32);
	पूर्ण अन्यथा अणु
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_R_MAXMIN);
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_B_MAXMIN);

		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_R_SUM);
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_SUM);
		*data++ = vsp1_hgo_पढ़ो(hgo, VI6_HGO_B_SUM);

		क्रम (i = 0; i < 64; ++i) अणु
			data[i] = vsp1_hgo_पढ़ो(hgo, VI6_HGO_R_HISTO(i));
			data[i+64] = vsp1_hgo_पढ़ो(hgo, VI6_HGO_G_HISTO(i));
			data[i+128] = vsp1_hgo_पढ़ो(hgo, VI6_HGO_B_HISTO(i));
		पूर्ण

		size = (6 + 64 * 3) * माप(u32);
	पूर्ण

	vsp1_histogram_buffer_complete(&hgo->histo, buf, size);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

#घोषणा V4L2_CID_VSP1_HGO_MAX_RGB		(V4L2_CID_USER_BASE | 0x1001)
#घोषणा V4L2_CID_VSP1_HGO_NUM_BINS		(V4L2_CID_USER_BASE | 0x1002)

अटल स्थिर काष्ठा v4l2_ctrl_config hgo_max_rgb_control = अणु
	.id = V4L2_CID_VSP1_HGO_MAX_RGB,
	.name = "Maximum RGB Mode",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.def = 0,
	.step = 1,
	.flags = V4L2_CTRL_FLAG_MODIFY_LAYOUT,
पूर्ण;

अटल स्थिर s64 hgo_num_bins[] = अणु
	64, 256,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config hgo_num_bins_control = अणु
	.id = V4L2_CID_VSP1_HGO_NUM_BINS,
	.name = "Number of Bins",
	.type = V4L2_CTRL_TYPE_INTEGER_MENU,
	.min = 0,
	.max = 1,
	.def = 0,
	.qmenu_पूर्णांक = hgo_num_bins,
	.flags = V4L2_CTRL_FLAG_MODIFY_LAYOUT,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम hgo_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_hgo *hgo = to_hgo(&entity->subdev);
	काष्ठा v4l2_rect *compose;
	काष्ठा v4l2_rect *crop;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;

	crop = vsp1_entity_get_pad_selection(entity, entity->config,
					     HISTO_PAD_SINK, V4L2_SEL_TGT_CROP);
	compose = vsp1_entity_get_pad_selection(entity, entity->config,
						HISTO_PAD_SINK,
						V4L2_SEL_TGT_COMPOSE);

	vsp1_hgo_ग_लिखो(hgo, dlb, VI6_HGO_REGRST, VI6_HGO_REGRST_RCLEA);

	vsp1_hgo_ग_लिखो(hgo, dlb, VI6_HGO_OFFSET,
		       (crop->left << VI6_HGO_OFFSET_HOFFSET_SHIFT) |
		       (crop->top << VI6_HGO_OFFSET_VOFFSET_SHIFT));
	vsp1_hgo_ग_लिखो(hgo, dlb, VI6_HGO_SIZE,
		       (crop->width << VI6_HGO_SIZE_HSIZE_SHIFT) |
		       (crop->height << VI6_HGO_SIZE_VSIZE_SHIFT));

	mutex_lock(hgo->ctrls.handler.lock);
	hgo->max_rgb = hgo->ctrls.max_rgb->cur.val;
	अगर (hgo->ctrls.num_bins)
		hgo->num_bins = hgo_num_bins[hgo->ctrls.num_bins->cur.val];
	mutex_unlock(hgo->ctrls.handler.lock);

	hratio = crop->width * 2 / compose->width / 3;
	vratio = crop->height * 2 / compose->height / 3;
	vsp1_hgo_ग_लिखो(hgo, dlb, VI6_HGO_MODE,
		       (hgo->num_bins == 256 ? VI6_HGO_MODE_STEP : 0) |
		       (hgo->max_rgb ? VI6_HGO_MODE_MAXRGB : 0) |
		       (hratio << VI6_HGO_MODE_HRATIO_SHIFT) |
		       (vratio << VI6_HGO_MODE_VRATIO_SHIFT));
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations hgo_entity_ops = अणु
	.configure_stream = hgo_configure_stream,
	.destroy = vsp1_histogram_destroy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

अटल स्थिर अचिन्हित पूर्णांक hgo_mbus_क्रमmats[] = अणु
	MEDIA_BUS_FMT_AYUV8_1X32,
	MEDIA_BUS_FMT_ARGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
पूर्ण;

काष्ठा vsp1_hgo *vsp1_hgo_create(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_hgo *hgo;
	पूर्णांक ret;

	hgo = devm_kzalloc(vsp1->dev, माप(*hgo), GFP_KERNEL);
	अगर (hgo == शून्य)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&hgo->ctrls.handler,
			       vsp1->info->gen == 3 ? 2 : 1);
	hgo->ctrls.max_rgb = v4l2_ctrl_new_custom(&hgo->ctrls.handler,
						  &hgo_max_rgb_control, शून्य);
	अगर (vsp1->info->gen == 3)
		hgo->ctrls.num_bins =
			v4l2_ctrl_new_custom(&hgo->ctrls.handler,
					     &hgo_num_bins_control, शून्य);

	hgo->max_rgb = false;
	hgo->num_bins = 64;

	hgo->histo.entity.subdev.ctrl_handler = &hgo->ctrls.handler;

	/* Initialize the video device and queue क्रम statistics data. */
	ret = vsp1_histogram_init(vsp1, &hgo->histo, VSP1_ENTITY_HGO, "hgo",
				  &hgo_entity_ops, hgo_mbus_क्रमmats,
				  ARRAY_SIZE(hgo_mbus_क्रमmats),
				  HGO_DATA_SIZE, V4L2_META_FMT_VSP1_HGO);
	अगर (ret < 0) अणु
		vsp1_entity_destroy(&hgo->histo.entity);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hgo;
पूर्ण
