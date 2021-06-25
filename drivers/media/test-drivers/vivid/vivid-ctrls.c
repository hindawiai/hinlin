<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-ctrls.c - control support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-common.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-cap.h"
#समावेश "vivid-vid-out.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-osd.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-cec.h"

#घोषणा VIVID_CID_CUSTOM_BASE		(V4L2_CID_USER_BASE | 0xf000)
#घोषणा VIVID_CID_BUTTON		(VIVID_CID_CUSTOM_BASE + 0)
#घोषणा VIVID_CID_BOOLEAN		(VIVID_CID_CUSTOM_BASE + 1)
#घोषणा VIVID_CID_INTEGER		(VIVID_CID_CUSTOM_BASE + 2)
#घोषणा VIVID_CID_INTEGER64		(VIVID_CID_CUSTOM_BASE + 3)
#घोषणा VIVID_CID_MENU			(VIVID_CID_CUSTOM_BASE + 4)
#घोषणा VIVID_CID_STRING		(VIVID_CID_CUSTOM_BASE + 5)
#घोषणा VIVID_CID_BITMASK		(VIVID_CID_CUSTOM_BASE + 6)
#घोषणा VIVID_CID_INTMENU		(VIVID_CID_CUSTOM_BASE + 7)
#घोषणा VIVID_CID_U32_ARRAY		(VIVID_CID_CUSTOM_BASE + 8)
#घोषणा VIVID_CID_U16_MATRIX		(VIVID_CID_CUSTOM_BASE + 9)
#घोषणा VIVID_CID_U8_4D_ARRAY		(VIVID_CID_CUSTOM_BASE + 10)
#घोषणा VIVID_CID_AREA			(VIVID_CID_CUSTOM_BASE + 11)
#घोषणा VIVID_CID_RO_INTEGER		(VIVID_CID_CUSTOM_BASE + 12)

#घोषणा VIVID_CID_VIVID_BASE		(0x00f00000 | 0xf000)
#घोषणा VIVID_CID_VIVID_CLASS		(0x00f00000 | 1)
#घोषणा VIVID_CID_TEST_PATTERN		(VIVID_CID_VIVID_BASE + 0)
#घोषणा VIVID_CID_OSD_TEXT_MODE		(VIVID_CID_VIVID_BASE + 1)
#घोषणा VIVID_CID_HOR_MOVEMENT		(VIVID_CID_VIVID_BASE + 2)
#घोषणा VIVID_CID_VERT_MOVEMENT		(VIVID_CID_VIVID_BASE + 3)
#घोषणा VIVID_CID_SHOW_BORDER		(VIVID_CID_VIVID_BASE + 4)
#घोषणा VIVID_CID_SHOW_SQUARE		(VIVID_CID_VIVID_BASE + 5)
#घोषणा VIVID_CID_INSERT_SAV		(VIVID_CID_VIVID_BASE + 6)
#घोषणा VIVID_CID_INSERT_EAV		(VIVID_CID_VIVID_BASE + 7)
#घोषणा VIVID_CID_VBI_CAP_INTERLACED	(VIVID_CID_VIVID_BASE + 8)

#घोषणा VIVID_CID_HFLIP			(VIVID_CID_VIVID_BASE + 20)
#घोषणा VIVID_CID_VFLIP			(VIVID_CID_VIVID_BASE + 21)
#घोषणा VIVID_CID_STD_ASPECT_RATIO	(VIVID_CID_VIVID_BASE + 22)
#घोषणा VIVID_CID_DV_TIMINGS_ASPECT_RATIO	(VIVID_CID_VIVID_BASE + 23)
#घोषणा VIVID_CID_TSTAMP_SRC		(VIVID_CID_VIVID_BASE + 24)
#घोषणा VIVID_CID_COLORSPACE		(VIVID_CID_VIVID_BASE + 25)
#घोषणा VIVID_CID_XFER_FUNC		(VIVID_CID_VIVID_BASE + 26)
#घोषणा VIVID_CID_YCBCR_ENC		(VIVID_CID_VIVID_BASE + 27)
#घोषणा VIVID_CID_QUANTIZATION		(VIVID_CID_VIVID_BASE + 28)
#घोषणा VIVID_CID_LIMITED_RGB_RANGE	(VIVID_CID_VIVID_BASE + 29)
#घोषणा VIVID_CID_ALPHA_MODE		(VIVID_CID_VIVID_BASE + 30)
#घोषणा VIVID_CID_HAS_CROP_CAP		(VIVID_CID_VIVID_BASE + 31)
#घोषणा VIVID_CID_HAS_COMPOSE_CAP	(VIVID_CID_VIVID_BASE + 32)
#घोषणा VIVID_CID_HAS_SCALER_CAP	(VIVID_CID_VIVID_BASE + 33)
#घोषणा VIVID_CID_HAS_CROP_OUT		(VIVID_CID_VIVID_BASE + 34)
#घोषणा VIVID_CID_HAS_COMPOSE_OUT	(VIVID_CID_VIVID_BASE + 35)
#घोषणा VIVID_CID_HAS_SCALER_OUT	(VIVID_CID_VIVID_BASE + 36)
#घोषणा VIVID_CID_LOOP_VIDEO		(VIVID_CID_VIVID_BASE + 37)
#घोषणा VIVID_CID_SEQ_WRAP		(VIVID_CID_VIVID_BASE + 38)
#घोषणा VIVID_CID_TIME_WRAP		(VIVID_CID_VIVID_BASE + 39)
#घोषणा VIVID_CID_MAX_EDID_BLOCKS	(VIVID_CID_VIVID_BASE + 40)
#घोषणा VIVID_CID_PERCENTAGE_FILL	(VIVID_CID_VIVID_BASE + 41)
#घोषणा VIVID_CID_REDUCED_FPS		(VIVID_CID_VIVID_BASE + 42)
#घोषणा VIVID_CID_HSV_ENC		(VIVID_CID_VIVID_BASE + 43)
#घोषणा VIVID_CID_DISPLAY_PRESENT	(VIVID_CID_VIVID_BASE + 44)

#घोषणा VIVID_CID_STD_SIGNAL_MODE	(VIVID_CID_VIVID_BASE + 60)
#घोषणा VIVID_CID_STANDARD		(VIVID_CID_VIVID_BASE + 61)
#घोषणा VIVID_CID_DV_TIMINGS_SIGNAL_MODE	(VIVID_CID_VIVID_BASE + 62)
#घोषणा VIVID_CID_DV_TIMINGS		(VIVID_CID_VIVID_BASE + 63)
#घोषणा VIVID_CID_PERC_DROPPED		(VIVID_CID_VIVID_BASE + 64)
#घोषणा VIVID_CID_DISCONNECT		(VIVID_CID_VIVID_BASE + 65)
#घोषणा VIVID_CID_DQBUF_ERROR		(VIVID_CID_VIVID_BASE + 66)
#घोषणा VIVID_CID_QUEUE_SETUP_ERROR	(VIVID_CID_VIVID_BASE + 67)
#घोषणा VIVID_CID_BUF_PREPARE_ERROR	(VIVID_CID_VIVID_BASE + 68)
#घोषणा VIVID_CID_START_STR_ERROR	(VIVID_CID_VIVID_BASE + 69)
#घोषणा VIVID_CID_QUEUE_ERROR		(VIVID_CID_VIVID_BASE + 70)
#घोषणा VIVID_CID_CLEAR_FB		(VIVID_CID_VIVID_BASE + 71)
#घोषणा VIVID_CID_REQ_VALIDATE_ERROR	(VIVID_CID_VIVID_BASE + 72)

#घोषणा VIVID_CID_RADIO_SEEK_MODE	(VIVID_CID_VIVID_BASE + 90)
#घोषणा VIVID_CID_RADIO_SEEK_PROG_LIM	(VIVID_CID_VIVID_BASE + 91)
#घोषणा VIVID_CID_RADIO_RX_RDS_RBDS	(VIVID_CID_VIVID_BASE + 92)
#घोषणा VIVID_CID_RADIO_RX_RDS_BLOCKIO	(VIVID_CID_VIVID_BASE + 93)

#घोषणा VIVID_CID_RADIO_TX_RDS_BLOCKIO	(VIVID_CID_VIVID_BASE + 94)

#घोषणा VIVID_CID_SDR_CAP_FM_DEVIATION	(VIVID_CID_VIVID_BASE + 110)

#घोषणा VIVID_CID_META_CAP_GENERATE_PTS	(VIVID_CID_VIVID_BASE + 111)
#घोषणा VIVID_CID_META_CAP_GENERATE_SCR	(VIVID_CID_VIVID_BASE + 112)

/* General User Controls */

अटल व्योम vivid_unरेजिस्टर_dev(bool valid, काष्ठा video_device *vdev)
अणु
	अगर (!valid)
		वापस;
	clear_bit(V4L2_FL_REGISTERED, &vdev->flags);
	v4l2_event_wake_all(vdev);
पूर्ण

अटल पूर्णांक vivid_user_gen_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_user_gen);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_DISCONNECT:
		v4l2_info(&dev->v4l2_dev, "disconnect\n");
		dev->disconnect_error = true;
		vivid_unरेजिस्टर_dev(dev->has_vid_cap, &dev->vid_cap_dev);
		vivid_unरेजिस्टर_dev(dev->has_vid_out, &dev->vid_out_dev);
		vivid_unरेजिस्टर_dev(dev->has_vbi_cap, &dev->vbi_cap_dev);
		vivid_unरेजिस्टर_dev(dev->has_vbi_out, &dev->vbi_out_dev);
		vivid_unरेजिस्टर_dev(dev->has_radio_rx, &dev->radio_rx_dev);
		vivid_unरेजिस्टर_dev(dev->has_radio_tx, &dev->radio_tx_dev);
		vivid_unरेजिस्टर_dev(dev->has_sdr_cap, &dev->sdr_cap_dev);
		vivid_unरेजिस्टर_dev(dev->has_meta_cap, &dev->meta_cap_dev);
		vivid_unरेजिस्टर_dev(dev->has_meta_out, &dev->meta_out_dev);
		vivid_unरेजिस्टर_dev(dev->has_touch_cap, &dev->touch_cap_dev);
		अवरोध;
	हाल VIVID_CID_BUTTON:
		dev->button_pressed = 30;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_user_gen_ctrl_ops = अणु
	.s_ctrl = vivid_user_gen_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_button = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_BUTTON,
	.name = "Button",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_boolean = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_BOOLEAN,
	.name = "Boolean",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_पूर्णांक32 = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_INTEGER,
	.name = "Integer 32 Bits",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0xffffffff80000000ULL,
	.max = 0x7fffffff,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_पूर्णांक64 = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_INTEGER64,
	.name = "Integer 64 Bits",
	.type = V4L2_CTRL_TYPE_INTEGER64,
	.min = 0x8000000000000000ULL,
	.max = 0x7fffffffffffffffLL,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_u32_array = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_U32_ARRAY,
	.name = "U32 1 Element Array",
	.type = V4L2_CTRL_TYPE_U32,
	.def = 0x18,
	.min = 0x10,
	.max = 0x20000,
	.step = 1,
	.dims = अणु 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_u16_matrix = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_U16_MATRIX,
	.name = "U16 8x16 Matrix",
	.type = V4L2_CTRL_TYPE_U16,
	.def = 0x18,
	.min = 0x10,
	.max = 0x2000,
	.step = 1,
	.dims = अणु 8, 16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_u8_4d_array = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_U8_4D_ARRAY,
	.name = "U8 2x3x4x5 Array",
	.type = V4L2_CTRL_TYPE_U8,
	.def = 0x18,
	.min = 0x10,
	.max = 0x20,
	.step = 1,
	.dims = अणु 2, 3, 4, 5 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_menu_strings[] = अणु
	"Menu Item 0 (Skipped)",
	"Menu Item 1",
	"Menu Item 2 (Skipped)",
	"Menu Item 3",
	"Menu Item 4",
	"Menu Item 5 (Skipped)",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_menu = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_MENU,
	.name = "Menu",
	.type = V4L2_CTRL_TYPE_MENU,
	.min = 1,
	.max = 4,
	.def = 3,
	.menu_skip_mask = 0x04,
	.qmenu = vivid_ctrl_menu_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_string = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_STRING,
	.name = "String",
	.type = V4L2_CTRL_TYPE_STRING,
	.min = 2,
	.max = 4,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_biपंचांगask = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_BITMASK,
	.name = "Bitmask",
	.type = V4L2_CTRL_TYPE_BITMASK,
	.def = 0x80002000,
	.min = 0,
	.max = 0x80402010,
	.step = 0,
पूर्ण;

अटल स्थिर s64 vivid_ctrl_पूर्णांक_menu_values[] = अणु
	1, 1, 2, 3, 5, 8, 13, 21, 42,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_पूर्णांक_menu = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_INTMENU,
	.name = "Integer Menu",
	.type = V4L2_CTRL_TYPE_INTEGER_MENU,
	.min = 1,
	.max = 8,
	.def = 4,
	.menu_skip_mask = 0x02,
	.qmenu_पूर्णांक = vivid_ctrl_पूर्णांक_menu_values,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_disconnect = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_DISCONNECT,
	.name = "Disconnect",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

अटल स्थिर काष्ठा v4l2_area area = अणु
	.width = 1000,
	.height = 2000,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_area = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_AREA,
	.name = "Area",
	.type = V4L2_CTRL_TYPE_AREA,
	.p_def.p_स्थिर = &area,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_ro_पूर्णांक32 = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.id = VIVID_CID_RO_INTEGER,
	.name = "Read-Only Integer 32 Bits",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.flags = V4L2_CTRL_FLAG_READ_ONLY,
	.min = 0,
	.max = 255,
	.step = 1,
पूर्ण;

/* Framebuffer Controls */

अटल पूर्णांक vivid_fb_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler,
					     काष्ठा vivid_dev, ctrl_hdl_fb);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_CLEAR_FB:
		vivid_clear_fb(dev);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_fb_ctrl_ops = अणु
	.s_ctrl = vivid_fb_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_clear_fb = अणु
	.ops = &vivid_fb_ctrl_ops,
	.id = VIVID_CID_CLEAR_FB,
	.name = "Clear Framebuffer",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;


/* Video User Controls */

अटल पूर्णांक vivid_user_vid_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_user_vid);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		dev->gain->val = (jअगरfies_to_msecs(jअगरfies) / 1000) & 0xff;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_user_vid_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_user_vid);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		dev->input_brightness[dev->input] = ctrl->val - dev->input * 128;
		tpg_s_brightness(&dev->tpg, dev->input_brightness[dev->input]);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		tpg_s_contrast(&dev->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		tpg_s_saturation(&dev->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		tpg_s_hue(&dev->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		dev->hflip = ctrl->val;
		tpg_s_hflip(&dev->tpg, dev->sensor_hflip ^ dev->hflip);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		dev->vflip = ctrl->val;
		tpg_s_vflip(&dev->tpg, dev->sensor_vflip ^ dev->vflip);
		अवरोध;
	हाल V4L2_CID_ALPHA_COMPONENT:
		tpg_s_alpha_component(&dev->tpg, ctrl->val);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_user_vid_ctrl_ops = अणु
	.g_अस्थिर_ctrl = vivid_user_vid_g_अस्थिर_ctrl,
	.s_ctrl = vivid_user_vid_s_ctrl,
पूर्ण;


/* Video Capture Controls */

अटल पूर्णांक vivid_vid_cap_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अटल स्थिर u32 colorspaces[] = अणु
		V4L2_COLORSPACE_SMPTE170M,
		V4L2_COLORSPACE_REC709,
		V4L2_COLORSPACE_SRGB,
		V4L2_COLORSPACE_OPRGB,
		V4L2_COLORSPACE_BT2020,
		V4L2_COLORSPACE_DCI_P3,
		V4L2_COLORSPACE_SMPTE240M,
		V4L2_COLORSPACE_470_SYSTEM_M,
		V4L2_COLORSPACE_470_SYSTEM_BG,
	पूर्ण;
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_vid_cap);
	अचिन्हित पूर्णांक i, j;

	चयन (ctrl->id) अणु
	हाल VIVID_CID_TEST_PATTERN:
		vivid_update_quality(dev);
		tpg_s_pattern(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_COLORSPACE:
		tpg_s_colorspace(&dev->tpg, colorspaces[ctrl->val]);
		vivid_send_source_change(dev, TV);
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
		vivid_send_source_change(dev, WEBCAM);
		अवरोध;
	हाल VIVID_CID_XFER_FUNC:
		tpg_s_xfer_func(&dev->tpg, ctrl->val);
		vivid_send_source_change(dev, TV);
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
		vivid_send_source_change(dev, WEBCAM);
		अवरोध;
	हाल VIVID_CID_YCBCR_ENC:
		tpg_s_ycbcr_enc(&dev->tpg, ctrl->val);
		vivid_send_source_change(dev, TV);
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
		vivid_send_source_change(dev, WEBCAM);
		अवरोध;
	हाल VIVID_CID_HSV_ENC:
		tpg_s_hsv_enc(&dev->tpg, ctrl->val ? V4L2_HSV_ENC_256 :
						     V4L2_HSV_ENC_180);
		vivid_send_source_change(dev, TV);
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
		vivid_send_source_change(dev, WEBCAM);
		अवरोध;
	हाल VIVID_CID_QUANTIZATION:
		tpg_s_quantization(&dev->tpg, ctrl->val);
		vivid_send_source_change(dev, TV);
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
		vivid_send_source_change(dev, WEBCAM);
		अवरोध;
	हाल V4L2_CID_DV_RX_RGB_RANGE:
		अगर (!vivid_is_hdmi_cap(dev))
			अवरोध;
		tpg_s_rgb_range(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_LIMITED_RGB_RANGE:
		tpg_s_real_rgb_range(&dev->tpg, ctrl->val ?
				V4L2_DV_RGB_RANGE_LIMITED : V4L2_DV_RGB_RANGE_FULL);
		अवरोध;
	हाल VIVID_CID_ALPHA_MODE:
		tpg_s_alpha_mode(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_HOR_MOVEMENT:
		tpg_s_mv_hor_mode(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_VERT_MOVEMENT:
		tpg_s_mv_vert_mode(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_OSD_TEXT_MODE:
		dev->osd_mode = ctrl->val;
		अवरोध;
	हाल VIVID_CID_PERCENTAGE_FILL:
		tpg_s_perc_fill(&dev->tpg, ctrl->val);
		क्रम (i = 0; i < VIDEO_MAX_FRAME; i++)
			dev->must_blank[i] = ctrl->val < 100;
		अवरोध;
	हाल VIVID_CID_INSERT_SAV:
		tpg_s_insert_sav(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_INSERT_EAV:
		tpg_s_insert_eav(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_HFLIP:
		dev->sensor_hflip = ctrl->val;
		tpg_s_hflip(&dev->tpg, dev->sensor_hflip ^ dev->hflip);
		अवरोध;
	हाल VIVID_CID_VFLIP:
		dev->sensor_vflip = ctrl->val;
		tpg_s_vflip(&dev->tpg, dev->sensor_vflip ^ dev->vflip);
		अवरोध;
	हाल VIVID_CID_REDUCED_FPS:
		dev->reduced_fps = ctrl->val;
		vivid_update_क्रमmat_cap(dev, true);
		अवरोध;
	हाल VIVID_CID_HAS_CROP_CAP:
		dev->has_crop_cap = ctrl->val;
		vivid_update_क्रमmat_cap(dev, true);
		अवरोध;
	हाल VIVID_CID_HAS_COMPOSE_CAP:
		dev->has_compose_cap = ctrl->val;
		vivid_update_क्रमmat_cap(dev, true);
		अवरोध;
	हाल VIVID_CID_HAS_SCALER_CAP:
		dev->has_scaler_cap = ctrl->val;
		vivid_update_क्रमmat_cap(dev, true);
		अवरोध;
	हाल VIVID_CID_SHOW_BORDER:
		tpg_s_show_border(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_SHOW_SQUARE:
		tpg_s_show_square(&dev->tpg, ctrl->val);
		अवरोध;
	हाल VIVID_CID_STD_ASPECT_RATIO:
		dev->std_aspect_ratio[dev->input] = ctrl->val;
		tpg_s_video_aspect(&dev->tpg, vivid_get_video_aspect(dev));
		अवरोध;
	हाल VIVID_CID_DV_TIMINGS_SIGNAL_MODE:
		dev->dv_timings_संकेत_mode[dev->input] =
			dev->ctrl_dv_timings_संकेत_mode->val;
		dev->query_dv_timings[dev->input] = dev->ctrl_dv_timings->val;

		dev->घातer_present = 0;
		क्रम (i = 0, j = 0;
		     i < ARRAY_SIZE(dev->dv_timings_संकेत_mode);
		     i++)
			अगर (dev->input_type[i] == HDMI) अणु
				अगर (dev->dv_timings_संकेत_mode[i] != NO_SIGNAL)
					dev->घातer_present |= (1 << j);
				j++;
			पूर्ण
		__v4l2_ctrl_s_ctrl(dev->ctrl_rx_घातer_present,
				   dev->घातer_present);

		v4l2_ctrl_activate(dev->ctrl_dv_timings,
			dev->dv_timings_संकेत_mode[dev->input] ==
				SELECTED_DV_TIMINGS);

		vivid_update_quality(dev);
		vivid_send_source_change(dev, HDMI);
		अवरोध;
	हाल VIVID_CID_DV_TIMINGS_ASPECT_RATIO:
		dev->dv_timings_aspect_ratio[dev->input] = ctrl->val;
		tpg_s_video_aspect(&dev->tpg, vivid_get_video_aspect(dev));
		अवरोध;
	हाल VIVID_CID_TSTAMP_SRC:
		dev->tstamp_src_is_soe = ctrl->val;
		dev->vb_vid_cap_q.बारtamp_flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		अगर (dev->tstamp_src_is_soe)
			dev->vb_vid_cap_q.बारtamp_flags |= V4L2_BUF_FLAG_TSTAMP_SRC_SOE;
		अवरोध;
	हाल VIVID_CID_MAX_EDID_BLOCKS:
		dev->edid_max_blocks = ctrl->val;
		अगर (dev->edid_blocks > dev->edid_max_blocks)
			dev->edid_blocks = dev->edid_max_blocks;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_vid_cap_ctrl_ops = अणु
	.s_ctrl = vivid_vid_cap_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_hor_movement_strings[] = अणु
	"Move Left Fast",
	"Move Left",
	"Move Left Slow",
	"No Movement",
	"Move Right Slow",
	"Move Right",
	"Move Right Fast",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_hor_movement = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_HOR_MOVEMENT,
	.name = "Horizontal Movement",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = TPG_MOVE_POS_FAST,
	.def = TPG_MOVE_NONE,
	.qmenu = vivid_ctrl_hor_movement_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_vert_movement_strings[] = अणु
	"Move Up Fast",
	"Move Up",
	"Move Up Slow",
	"No Movement",
	"Move Down Slow",
	"Move Down",
	"Move Down Fast",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_vert_movement = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_VERT_MOVEMENT,
	.name = "Vertical Movement",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = TPG_MOVE_POS_FAST,
	.def = TPG_MOVE_NONE,
	.qmenu = vivid_ctrl_vert_movement_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_show_border = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_SHOW_BORDER,
	.name = "Show Border",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_show_square = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_SHOW_SQUARE,
	.name = "Show Square",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_osd_mode_strings[] = अणु
	"All",
	"Counters Only",
	"None",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_osd_mode = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_OSD_TEXT_MODE,
	.name = "OSD Text Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_osd_mode_strings) - 2,
	.qmenu = vivid_ctrl_osd_mode_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_perc_fill = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_PERCENTAGE_FILL,
	.name = "Fill Percentage of Frame",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 100,
	.def = 100,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_insert_sav = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_INSERT_SAV,
	.name = "Insert SAV Code in Image",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_insert_eav = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_INSERT_EAV,
	.name = "Insert EAV Code in Image",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_hflip = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_HFLIP,
	.name = "Sensor Flipped Horizontally",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_vflip = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_VFLIP,
	.name = "Sensor Flipped Vertically",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_reduced_fps = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_REDUCED_FPS,
	.name = "Reduced Framerate",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_has_crop_cap = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_HAS_CROP_CAP,
	.name = "Enable Capture Cropping",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_has_compose_cap = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_HAS_COMPOSE_CAP,
	.name = "Enable Capture Composing",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_has_scaler_cap = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_HAS_SCALER_CAP,
	.name = "Enable Capture Scaler",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_tstamp_src_strings[] = अणु
	"End of Frame",
	"Start of Exposure",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_tstamp_src = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_TSTAMP_SRC,
	.name = "Timestamp Source",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_tstamp_src_strings) - 2,
	.qmenu = vivid_ctrl_tstamp_src_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_std_aspect_ratio = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_STD_ASPECT_RATIO,
	.name = "Standard Aspect Ratio",
	.type = V4L2_CTRL_TYPE_MENU,
	.min = 1,
	.max = 4,
	.def = 1,
	.qmenu = tpg_aspect_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_dv_timings_संकेत_mode_strings[] = अणु
	"Current DV Timings",
	"No Signal",
	"No Lock",
	"Out of Range",
	"Selected DV Timings",
	"Cycle Through All DV Timings",
	"Custom DV Timings",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_dv_timings_संकेत_mode = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_DV_TIMINGS_SIGNAL_MODE,
	.name = "DV Timings Signal Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = 5,
	.qmenu = vivid_ctrl_dv_timings_संकेत_mode_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_dv_timings_aspect_ratio = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_DV_TIMINGS_ASPECT_RATIO,
	.name = "DV Timings Aspect Ratio",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = 3,
	.qmenu = tpg_aspect_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_max_edid_blocks = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_MAX_EDID_BLOCKS,
	.name = "Maximum EDID Blocks",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 1,
	.max = 256,
	.def = 2,
	.step = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_colorspace_strings[] = अणु
	"SMPTE 170M",
	"Rec. 709",
	"sRGB",
	"opRGB",
	"BT.2020",
	"DCI-P3",
	"SMPTE 240M",
	"470 System M",
	"470 System BG",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_colorspace = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_COLORSPACE,
	.name = "Colorspace",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_colorspace_strings) - 2,
	.def = 2,
	.qmenu = vivid_ctrl_colorspace_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_xfer_func_strings[] = अणु
	"Default",
	"Rec. 709",
	"sRGB",
	"opRGB",
	"SMPTE 240M",
	"None",
	"DCI-P3",
	"SMPTE 2084",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_xfer_func = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_XFER_FUNC,
	.name = "Transfer Function",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_xfer_func_strings) - 2,
	.qmenu = vivid_ctrl_xfer_func_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_ycbcr_enc_strings[] = अणु
	"Default",
	"ITU-R 601",
	"Rec. 709",
	"xvYCC 601",
	"xvYCC 709",
	"",
	"BT.2020",
	"BT.2020 Constant Luminance",
	"SMPTE 240M",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_ycbcr_enc = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_YCBCR_ENC,
	.name = "Y'CbCr Encoding",
	.type = V4L2_CTRL_TYPE_MENU,
	.menu_skip_mask = 1 << 5,
	.max = ARRAY_SIZE(vivid_ctrl_ycbcr_enc_strings) - 2,
	.qmenu = vivid_ctrl_ycbcr_enc_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_hsv_enc_strings[] = अणु
	"Hue 0-179",
	"Hue 0-256",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_hsv_enc = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_HSV_ENC,
	.name = "HSV Encoding",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_hsv_enc_strings) - 2,
	.qmenu = vivid_ctrl_hsv_enc_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_quantization_strings[] = अणु
	"Default",
	"Full Range",
	"Limited Range",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_quantization = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_QUANTIZATION,
	.name = "Quantization",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_quantization_strings) - 2,
	.qmenu = vivid_ctrl_quantization_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_alpha_mode = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_ALPHA_MODE,
	.name = "Apply Alpha To Red Only",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_limited_rgb_range = अणु
	.ops = &vivid_vid_cap_ctrl_ops,
	.id = VIVID_CID_LIMITED_RGB_RANGE,
	.name = "Limited RGB Range (16-235)",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;


/* Video Loop Control */

अटल पूर्णांक vivid_loop_cap_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_loop_cap);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_LOOP_VIDEO:
		dev->loop_video = ctrl->val;
		vivid_update_quality(dev);
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_loop_cap_ctrl_ops = अणु
	.s_ctrl = vivid_loop_cap_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_loop_video = अणु
	.ops = &vivid_loop_cap_ctrl_ops,
	.id = VIVID_CID_LOOP_VIDEO,
	.name = "Loop Video",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;


/* VBI Capture Control */

अटल पूर्णांक vivid_vbi_cap_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_vbi_cap);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_VBI_CAP_INTERLACED:
		dev->vbi_cap_पूर्णांकerlaced = ctrl->val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_vbi_cap_ctrl_ops = अणु
	.s_ctrl = vivid_vbi_cap_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_vbi_cap_पूर्णांकerlaced = अणु
	.ops = &vivid_vbi_cap_ctrl_ops,
	.id = VIVID_CID_VBI_CAP_INTERLACED,
	.name = "Interlaced VBI Format",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;


/* Video Output Controls */

अटल पूर्णांक vivid_vid_out_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_vid_out);
	काष्ठा v4l2_bt_timings *bt = &dev->dv_timings_out.bt;
	u32 display_present = 0;
	अचिन्हित पूर्णांक i, j, bus_idx;

	चयन (ctrl->id) अणु
	हाल VIVID_CID_HAS_CROP_OUT:
		dev->has_crop_out = ctrl->val;
		vivid_update_क्रमmat_out(dev);
		अवरोध;
	हाल VIVID_CID_HAS_COMPOSE_OUT:
		dev->has_compose_out = ctrl->val;
		vivid_update_क्रमmat_out(dev);
		अवरोध;
	हाल VIVID_CID_HAS_SCALER_OUT:
		dev->has_scaler_out = ctrl->val;
		vivid_update_क्रमmat_out(dev);
		अवरोध;
	हाल V4L2_CID_DV_TX_MODE:
		dev->dvi_d_out = ctrl->val == V4L2_DV_TX_MODE_DVI_D;
		अगर (!vivid_is_hdmi_out(dev))
			अवरोध;
		अगर (!dev->dvi_d_out && (bt->flags & V4L2_DV_FL_IS_CE_VIDEO)) अणु
			अगर (bt->width == 720 && bt->height <= 576)
				dev->colorspace_out = V4L2_COLORSPACE_SMPTE170M;
			अन्यथा
				dev->colorspace_out = V4L2_COLORSPACE_REC709;
			dev->quantization_out = V4L2_QUANTIZATION_DEFAULT;
		पूर्ण अन्यथा अणु
			dev->colorspace_out = V4L2_COLORSPACE_SRGB;
			dev->quantization_out = dev->dvi_d_out ?
					V4L2_QUANTIZATION_LIM_RANGE :
					V4L2_QUANTIZATION_DEFAULT;
		पूर्ण
		अगर (dev->loop_video)
			vivid_send_source_change(dev, HDMI);
		अवरोध;
	हाल VIVID_CID_DISPLAY_PRESENT:
		अगर (dev->output_type[dev->output] != HDMI)
			अवरोध;

		dev->display_present[dev->output] = ctrl->val;
		क्रम (i = 0, j = 0; i < dev->num_outमाला_दो; i++)
			अगर (dev->output_type[i] == HDMI)
				display_present |=
					dev->display_present[i] << j++;

		__v4l2_ctrl_s_ctrl(dev->ctrl_tx_rxsense, display_present);

		अगर (dev->edid_blocks) अणु
			__v4l2_ctrl_s_ctrl(dev->ctrl_tx_edid_present,
					   display_present);
			__v4l2_ctrl_s_ctrl(dev->ctrl_tx_hotplug,
					   display_present);
		पूर्ण

		bus_idx = dev->cec_output2bus_map[dev->output];
		अगर (!dev->cec_tx_adap[bus_idx])
			अवरोध;

		अगर (ctrl->val && dev->edid_blocks)
			cec_s_phys_addr(dev->cec_tx_adap[bus_idx],
					dev->cec_tx_adap[bus_idx]->phys_addr,
					false);
		अन्यथा
			cec_phys_addr_invalidate(dev->cec_tx_adap[bus_idx]);

		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_vid_out_ctrl_ops = अणु
	.s_ctrl = vivid_vid_out_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_has_crop_out = अणु
	.ops = &vivid_vid_out_ctrl_ops,
	.id = VIVID_CID_HAS_CROP_OUT,
	.name = "Enable Output Cropping",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_has_compose_out = अणु
	.ops = &vivid_vid_out_ctrl_ops,
	.id = VIVID_CID_HAS_COMPOSE_OUT,
	.name = "Enable Output Composing",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_has_scaler_out = अणु
	.ops = &vivid_vid_out_ctrl_ops,
	.id = VIVID_CID_HAS_SCALER_OUT,
	.name = "Enable Output Scaler",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_display_present = अणु
	.ops = &vivid_vid_out_ctrl_ops,
	.id = VIVID_CID_DISPLAY_PRESENT,
	.name = "Display Present",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

/* Streaming Controls */

अटल पूर्णांक vivid_streaming_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_streaming);
	u64 rem;

	चयन (ctrl->id) अणु
	हाल VIVID_CID_DQBUF_ERROR:
		dev->dqbuf_error = true;
		अवरोध;
	हाल VIVID_CID_PERC_DROPPED:
		dev->perc_dropped_buffers = ctrl->val;
		अवरोध;
	हाल VIVID_CID_QUEUE_SETUP_ERROR:
		dev->queue_setup_error = true;
		अवरोध;
	हाल VIVID_CID_BUF_PREPARE_ERROR:
		dev->buf_prepare_error = true;
		अवरोध;
	हाल VIVID_CID_START_STR_ERROR:
		dev->start_streaming_error = true;
		अवरोध;
	हाल VIVID_CID_REQ_VALIDATE_ERROR:
		dev->req_validate_error = true;
		अवरोध;
	हाल VIVID_CID_QUEUE_ERROR:
		अगर (vb2_start_streaming_called(&dev->vb_vid_cap_q))
			vb2_queue_error(&dev->vb_vid_cap_q);
		अगर (vb2_start_streaming_called(&dev->vb_vbi_cap_q))
			vb2_queue_error(&dev->vb_vbi_cap_q);
		अगर (vb2_start_streaming_called(&dev->vb_vid_out_q))
			vb2_queue_error(&dev->vb_vid_out_q);
		अगर (vb2_start_streaming_called(&dev->vb_vbi_out_q))
			vb2_queue_error(&dev->vb_vbi_out_q);
		अगर (vb2_start_streaming_called(&dev->vb_sdr_cap_q))
			vb2_queue_error(&dev->vb_sdr_cap_q);
		अवरोध;
	हाल VIVID_CID_SEQ_WRAP:
		dev->seq_wrap = ctrl->val;
		अवरोध;
	हाल VIVID_CID_TIME_WRAP:
		dev->समय_wrap = ctrl->val;
		अगर (ctrl->val == 0) अणु
			dev->समय_wrap_offset = 0;
			अवरोध;
		पूर्ण
		/*
		 * We want to set the समय 16 seconds beक्रमe the 32 bit tv_sec
		 * value of काष्ठा समयval would wrap around. So first we
		 * calculate kसमय_get_ns() % ((1 << 32) * NSEC_PER_SEC), and
		 * then we set the offset to ((1 << 32) - 16) * NSEC_PER_SEC).
		 */
		भाग64_u64_rem(kसमय_get_ns(),
			0x100000000ULL * NSEC_PER_SEC, &rem);
		dev->समय_wrap_offset =
			(0x100000000ULL - 16) * NSEC_PER_SEC - rem;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_streaming_ctrl_ops = अणु
	.s_ctrl = vivid_streaming_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_dqbuf_error = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_DQBUF_ERROR,
	.name = "Inject V4L2_BUF_FLAG_ERROR",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_perc_dropped = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_PERC_DROPPED,
	.name = "Percentage of Dropped Buffers",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 100,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_queue_setup_error = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_QUEUE_SETUP_ERROR,
	.name = "Inject VIDIOC_REQBUFS Error",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_buf_prepare_error = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_BUF_PREPARE_ERROR,
	.name = "Inject VIDIOC_QBUF Error",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_start_streaming_error = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_START_STR_ERROR,
	.name = "Inject VIDIOC_STREAMON Error",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_queue_error = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_QUEUE_ERROR,
	.name = "Inject Fatal Streaming Error",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_req_validate_error = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_REQ_VALIDATE_ERROR,
	.name = "Inject req_validate() Error",
	.type = V4L2_CTRL_TYPE_BUTTON,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_seq_wrap = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_SEQ_WRAP,
	.name = "Wrap Sequence Number",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_समय_wrap = अणु
	.ops = &vivid_streaming_ctrl_ops,
	.id = VIVID_CID_TIME_WRAP,
	.name = "Wrap Timestamp",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;


/* SDTV Capture Controls */

अटल पूर्णांक vivid_sdtv_cap_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_sdtv_cap);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_STD_SIGNAL_MODE:
		dev->std_संकेत_mode[dev->input] =
			dev->ctrl_std_संकेत_mode->val;
		अगर (dev->std_संकेत_mode[dev->input] == SELECTED_STD)
			dev->query_std[dev->input] =
				vivid_standard[dev->ctrl_standard->val];
		v4l2_ctrl_activate(dev->ctrl_standard,
				   dev->std_संकेत_mode[dev->input] ==
					SELECTED_STD);
		vivid_update_quality(dev);
		vivid_send_source_change(dev, TV);
		vivid_send_source_change(dev, SVID);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_sdtv_cap_ctrl_ops = अणु
	.s_ctrl = vivid_sdtv_cap_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_std_संकेत_mode_strings[] = अणु
	"Current Standard",
	"No Signal",
	"No Lock",
	"",
	"Selected Standard",
	"Cycle Through All Standards",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_std_संकेत_mode = अणु
	.ops = &vivid_sdtv_cap_ctrl_ops,
	.id = VIVID_CID_STD_SIGNAL_MODE,
	.name = "Standard Signal Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vivid_ctrl_std_संकेत_mode_strings) - 2,
	.menu_skip_mask = 1 << 3,
	.qmenu = vivid_ctrl_std_संकेत_mode_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_standard = अणु
	.ops = &vivid_sdtv_cap_ctrl_ops,
	.id = VIVID_CID_STANDARD,
	.name = "Standard",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = 14,
	.qmenu = vivid_ctrl_standard_strings,
पूर्ण;



/* Radio Receiver Controls */

अटल पूर्णांक vivid_radio_rx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_radio_rx);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_RADIO_SEEK_MODE:
		dev->radio_rx_hw_seek_mode = ctrl->val;
		अवरोध;
	हाल VIVID_CID_RADIO_SEEK_PROG_LIM:
		dev->radio_rx_hw_seek_prog_lim = ctrl->val;
		अवरोध;
	हाल VIVID_CID_RADIO_RX_RDS_RBDS:
		dev->rds_gen.use_rbds = ctrl->val;
		अवरोध;
	हाल VIVID_CID_RADIO_RX_RDS_BLOCKIO:
		dev->radio_rx_rds_controls = ctrl->val;
		dev->radio_rx_caps &= ~V4L2_CAP_READWRITE;
		dev->radio_rx_rds_use_alternates = false;
		अगर (!dev->radio_rx_rds_controls) अणु
			dev->radio_rx_caps |= V4L2_CAP_READWRITE;
			__v4l2_ctrl_s_ctrl(dev->radio_rx_rds_pty, 0);
			__v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ta, 0);
			__v4l2_ctrl_s_ctrl(dev->radio_rx_rds_tp, 0);
			__v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ms, 0);
			__v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_psname, "");
			__v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_radiotext, "");
		पूर्ण
		v4l2_ctrl_activate(dev->radio_rx_rds_pty, dev->radio_rx_rds_controls);
		v4l2_ctrl_activate(dev->radio_rx_rds_psname, dev->radio_rx_rds_controls);
		v4l2_ctrl_activate(dev->radio_rx_rds_radiotext, dev->radio_rx_rds_controls);
		v4l2_ctrl_activate(dev->radio_rx_rds_ta, dev->radio_rx_rds_controls);
		v4l2_ctrl_activate(dev->radio_rx_rds_tp, dev->radio_rx_rds_controls);
		v4l2_ctrl_activate(dev->radio_rx_rds_ms, dev->radio_rx_rds_controls);
		dev->radio_rx_dev.device_caps = dev->radio_rx_caps;
		अवरोध;
	हाल V4L2_CID_RDS_RECEPTION:
		dev->radio_rx_rds_enabled = ctrl->val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_radio_rx_ctrl_ops = अणु
	.s_ctrl = vivid_radio_rx_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_radio_rds_mode_strings[] = अणु
	"Block I/O",
	"Controls",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_radio_rx_rds_blockio = अणु
	.ops = &vivid_radio_rx_ctrl_ops,
	.id = VIVID_CID_RADIO_RX_RDS_BLOCKIO,
	.name = "RDS Rx I/O Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.qmenu = vivid_ctrl_radio_rds_mode_strings,
	.max = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_radio_rx_rds_rbds = अणु
	.ops = &vivid_radio_rx_ctrl_ops,
	.id = VIVID_CID_RADIO_RX_RDS_RBDS,
	.name = "Generate RBDS Instead of RDS",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vivid_ctrl_radio_hw_seek_mode_strings[] = अणु
	"Bounded",
	"Wrap Around",
	"Both",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_radio_hw_seek_mode = अणु
	.ops = &vivid_radio_rx_ctrl_ops,
	.id = VIVID_CID_RADIO_SEEK_MODE,
	.name = "Radio HW Seek Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = 2,
	.qmenu = vivid_ctrl_radio_hw_seek_mode_strings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_radio_hw_seek_prog_lim = अणु
	.ops = &vivid_radio_rx_ctrl_ops,
	.id = VIVID_CID_RADIO_SEEK_PROG_LIM,
	.name = "Radio Programmable HW Seek",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;


/* Radio Transmitter Controls */

अटल पूर्णांक vivid_radio_tx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_radio_tx);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_RADIO_TX_RDS_BLOCKIO:
		dev->radio_tx_rds_controls = ctrl->val;
		dev->radio_tx_caps &= ~V4L2_CAP_READWRITE;
		अगर (!dev->radio_tx_rds_controls)
			dev->radio_tx_caps |= V4L2_CAP_READWRITE;
		dev->radio_tx_dev.device_caps = dev->radio_tx_caps;
		अवरोध;
	हाल V4L2_CID_RDS_TX_PTY:
		अगर (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_pty, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RDS_TX_PS_NAME:
		अगर (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_psname, ctrl->p_new.p_अक्षर);
		अवरोध;
	हाल V4L2_CID_RDS_TX_RADIO_TEXT:
		अगर (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_radiotext, ctrl->p_new.p_अक्षर);
		अवरोध;
	हाल V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT:
		अगर (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ta, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:
		अगर (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_tp, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RDS_TX_MUSIC_SPEECH:
		अगर (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ms, ctrl->val);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_radio_tx_ctrl_ops = अणु
	.s_ctrl = vivid_radio_tx_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_radio_tx_rds_blockio = अणु
	.ops = &vivid_radio_tx_ctrl_ops,
	.id = VIVID_CID_RADIO_TX_RDS_BLOCKIO,
	.name = "RDS Tx I/O Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.qmenu = vivid_ctrl_radio_rds_mode_strings,
	.max = 1,
	.def = 1,
पूर्ण;


/* SDR Capture Controls */

अटल पूर्णांक vivid_sdr_cap_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev, ctrl_hdl_sdr_cap);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_SDR_CAP_FM_DEVIATION:
		dev->sdr_fm_deviation = ctrl->val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_sdr_cap_ctrl_ops = अणु
	.s_ctrl = vivid_sdr_cap_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_sdr_cap_fm_deviation = अणु
	.ops = &vivid_sdr_cap_ctrl_ops,
	.id = VIVID_CID_SDR_CAP_FM_DEVIATION,
	.name = "FM Deviation",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min =    100,
	.max = 200000,
	.def =  75000,
	.step =     1,
पूर्ण;

/* Metadata Capture Control */

अटल पूर्णांक vivid_meta_cap_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vivid_dev *dev = container_of(ctrl->handler, काष्ठा vivid_dev,
					     ctrl_hdl_meta_cap);

	चयन (ctrl->id) अणु
	हाल VIVID_CID_META_CAP_GENERATE_PTS:
		dev->meta_pts = ctrl->val;
		अवरोध;
	हाल VIVID_CID_META_CAP_GENERATE_SCR:
		dev->meta_scr = ctrl->val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vivid_meta_cap_ctrl_ops = अणु
	.s_ctrl = vivid_meta_cap_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_meta_has_pts = अणु
	.ops = &vivid_meta_cap_ctrl_ops,
	.id = VIVID_CID_META_CAP_GENERATE_PTS,
	.name = "Generate PTS",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_meta_has_src_clk = अणु
	.ops = &vivid_meta_cap_ctrl_ops,
	.id = VIVID_CID_META_CAP_GENERATE_SCR,
	.name = "Generate SCR",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.def = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vivid_ctrl_class = अणु
	.ops = &vivid_user_gen_ctrl_ops,
	.flags = V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_WRITE_ONLY,
	.id = VIVID_CID_VIVID_CLASS,
	.name = "Vivid Controls",
	.type = V4L2_CTRL_TYPE_CTRL_CLASS,
पूर्ण;

पूर्णांक vivid_create_controls(काष्ठा vivid_dev *dev, bool show_ccs_cap,
		bool show_ccs_out, bool no_error_inj,
		bool has_sdtv, bool has_hdmi)
अणु
	काष्ठा v4l2_ctrl_handler *hdl_user_gen = &dev->ctrl_hdl_user_gen;
	काष्ठा v4l2_ctrl_handler *hdl_user_vid = &dev->ctrl_hdl_user_vid;
	काष्ठा v4l2_ctrl_handler *hdl_user_aud = &dev->ctrl_hdl_user_aud;
	काष्ठा v4l2_ctrl_handler *hdl_streaming = &dev->ctrl_hdl_streaming;
	काष्ठा v4l2_ctrl_handler *hdl_sdtv_cap = &dev->ctrl_hdl_sdtv_cap;
	काष्ठा v4l2_ctrl_handler *hdl_loop_cap = &dev->ctrl_hdl_loop_cap;
	काष्ठा v4l2_ctrl_handler *hdl_fb = &dev->ctrl_hdl_fb;
	काष्ठा v4l2_ctrl_handler *hdl_vid_cap = &dev->ctrl_hdl_vid_cap;
	काष्ठा v4l2_ctrl_handler *hdl_vid_out = &dev->ctrl_hdl_vid_out;
	काष्ठा v4l2_ctrl_handler *hdl_vbi_cap = &dev->ctrl_hdl_vbi_cap;
	काष्ठा v4l2_ctrl_handler *hdl_vbi_out = &dev->ctrl_hdl_vbi_out;
	काष्ठा v4l2_ctrl_handler *hdl_radio_rx = &dev->ctrl_hdl_radio_rx;
	काष्ठा v4l2_ctrl_handler *hdl_radio_tx = &dev->ctrl_hdl_radio_tx;
	काष्ठा v4l2_ctrl_handler *hdl_sdr_cap = &dev->ctrl_hdl_sdr_cap;
	काष्ठा v4l2_ctrl_handler *hdl_meta_cap = &dev->ctrl_hdl_meta_cap;
	काष्ठा v4l2_ctrl_handler *hdl_meta_out = &dev->ctrl_hdl_meta_out;
	काष्ठा v4l2_ctrl_handler *hdl_tch_cap = &dev->ctrl_hdl_touch_cap;

	काष्ठा v4l2_ctrl_config vivid_ctrl_dv_timings = अणु
		.ops = &vivid_vid_cap_ctrl_ops,
		.id = VIVID_CID_DV_TIMINGS,
		.name = "DV Timings",
		.type = V4L2_CTRL_TYPE_MENU,
	पूर्ण;
	पूर्णांक i;

	v4l2_ctrl_handler_init(hdl_user_gen, 10);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_user_vid, 9);
	v4l2_ctrl_new_custom(hdl_user_vid, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_user_aud, 2);
	v4l2_ctrl_new_custom(hdl_user_aud, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_streaming, 8);
	v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_sdtv_cap, 2);
	v4l2_ctrl_new_custom(hdl_sdtv_cap, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_loop_cap, 1);
	v4l2_ctrl_new_custom(hdl_loop_cap, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_fb, 1);
	v4l2_ctrl_new_custom(hdl_fb, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_vid_cap, 55);
	v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_vid_out, 26);
	अगर (!no_error_inj || dev->has_fb || dev->num_hdmi_outमाला_दो)
		v4l2_ctrl_new_custom(hdl_vid_out, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_vbi_cap, 21);
	v4l2_ctrl_new_custom(hdl_vbi_cap, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_vbi_out, 19);
	अगर (!no_error_inj)
		v4l2_ctrl_new_custom(hdl_vbi_out, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_radio_rx, 17);
	v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_radio_tx, 17);
	v4l2_ctrl_new_custom(hdl_radio_tx, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_sdr_cap, 19);
	v4l2_ctrl_new_custom(hdl_sdr_cap, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_meta_cap, 2);
	v4l2_ctrl_new_custom(hdl_meta_cap, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_meta_out, 2);
	v4l2_ctrl_new_custom(hdl_meta_out, &vivid_ctrl_class, शून्य);
	v4l2_ctrl_handler_init(hdl_tch_cap, 2);
	v4l2_ctrl_new_custom(hdl_tch_cap, &vivid_ctrl_class, शून्य);

	/* User Controls */
	dev->volume = v4l2_ctrl_new_std(hdl_user_aud, शून्य,
		V4L2_CID_AUDIO_VOLUME, 0, 255, 1, 200);
	dev->mute = v4l2_ctrl_new_std(hdl_user_aud, शून्य,
		V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	अगर (dev->has_vid_cap) अणु
		dev->brightness = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
		क्रम (i = 0; i < MAX_INPUTS; i++)
			dev->input_brightness[i] = 128;
		dev->contrast = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
		dev->saturation = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
		dev->hue = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_HUE, -128, 128, 1, 0);
		v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
		v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
		dev->स्वतःgain = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		dev->gain = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 100);
		dev->alpha = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 0);
	पूर्ण
	dev->button = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_button, शून्य);
	dev->पूर्णांक32 = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_पूर्णांक32, शून्य);
	dev->पूर्णांक64 = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_पूर्णांक64, शून्य);
	dev->boolean = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_boolean, शून्य);
	dev->menu = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_menu, शून्य);
	dev->string = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_string, शून्य);
	dev->biपंचांगask = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_biपंचांगask, शून्य);
	dev->पूर्णांक_menu = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_पूर्णांक_menu, शून्य);
	dev->ro_पूर्णांक32 = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_ro_पूर्णांक32, शून्य);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_area, शून्य);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_u32_array, शून्य);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_u16_matrix, शून्य);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_u8_4d_array, शून्य);

	अगर (dev->has_vid_cap) अणु
		/* Image Processing Controls */
		काष्ठा v4l2_ctrl_config vivid_ctrl_test_pattern = अणु
			.ops = &vivid_vid_cap_ctrl_ops,
			.id = VIVID_CID_TEST_PATTERN,
			.name = "Test Pattern",
			.type = V4L2_CTRL_TYPE_MENU,
			.max = TPG_PAT_NOISE,
			.qmenu = tpg_pattern_strings,
		पूर्ण;

		dev->test_pattern = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_test_pattern, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_perc_fill, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_hor_movement, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_vert_movement, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_osd_mode, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_show_border, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_show_square, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_hflip, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_vflip, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_insert_sav, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_insert_eav, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_reduced_fps, शून्य);
		अगर (show_ccs_cap) अणु
			dev->ctrl_has_crop_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_has_crop_cap, शून्य);
			dev->ctrl_has_compose_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_has_compose_cap, शून्य);
			dev->ctrl_has_scaler_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_has_scaler_cap, शून्य);
		पूर्ण

		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_tstamp_src, शून्य);
		dev->colorspace = v4l2_ctrl_new_custom(hdl_vid_cap,
			&vivid_ctrl_colorspace, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_xfer_func, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_ycbcr_enc, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_hsv_enc, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_quantization, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_alpha_mode, शून्य);
	पूर्ण

	अगर (dev->has_vid_out && show_ccs_out) अणु
		dev->ctrl_has_crop_out = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_has_crop_out, शून्य);
		dev->ctrl_has_compose_out = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_has_compose_out, शून्य);
		dev->ctrl_has_scaler_out = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_has_scaler_out, शून्य);
	पूर्ण

	/*
	 * Testing this driver with v4l2-compliance will trigger the error
	 * injection controls, and after that nothing will work as expected.
	 * So we have a module option to drop these error injecting controls
	 * allowing us to run v4l2_compliance again.
	 */
	अगर (!no_error_inj) अणु
		v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_disconnect, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_dqbuf_error, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_perc_dropped, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_queue_setup_error, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_buf_prepare_error, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_start_streaming_error, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_queue_error, शून्य);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_req_validate_error, शून्य);
#पूर्ण_अगर
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_seq_wrap, शून्य);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_समय_wrap, शून्य);
	पूर्ण

	अगर (has_sdtv && (dev->has_vid_cap || dev->has_vbi_cap)) अणु
		अगर (dev->has_vid_cap)
			v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_std_aspect_ratio, शून्य);
		dev->ctrl_std_संकेत_mode = v4l2_ctrl_new_custom(hdl_sdtv_cap,
			&vivid_ctrl_std_संकेत_mode, शून्य);
		dev->ctrl_standard = v4l2_ctrl_new_custom(hdl_sdtv_cap,
			&vivid_ctrl_standard, शून्य);
		अगर (dev->ctrl_std_संकेत_mode)
			v4l2_ctrl_cluster(2, &dev->ctrl_std_संकेत_mode);
		अगर (dev->has_raw_vbi_cap)
			v4l2_ctrl_new_custom(hdl_vbi_cap, &vivid_ctrl_vbi_cap_पूर्णांकerlaced, शून्य);
	पूर्ण

	अगर (dev->num_hdmi_inमाला_दो) अणु
		s64 hdmi_input_mask = GENMASK(dev->num_hdmi_inमाला_दो - 1, 0);

		dev->ctrl_dv_timings_संकेत_mode = v4l2_ctrl_new_custom(hdl_vid_cap,
					&vivid_ctrl_dv_timings_संकेत_mode, शून्य);

		vivid_ctrl_dv_timings.max = dev->query_dv_timings_size - 1;
		vivid_ctrl_dv_timings.qmenu =
			(स्थिर अक्षर * स्थिर *)dev->query_dv_timings_qmenu;
		dev->ctrl_dv_timings = v4l2_ctrl_new_custom(hdl_vid_cap,
			&vivid_ctrl_dv_timings, शून्य);
		अगर (dev->ctrl_dv_timings_संकेत_mode)
			v4l2_ctrl_cluster(2, &dev->ctrl_dv_timings_संकेत_mode);

		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_dv_timings_aspect_ratio, शून्य);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_max_edid_blocks, शून्य);
		dev->real_rgb_range_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
			&vivid_ctrl_limited_rgb_range, शून्य);
		dev->rgb_range_cap = v4l2_ctrl_new_std_menu(hdl_vid_cap,
			&vivid_vid_cap_ctrl_ops,
			V4L2_CID_DV_RX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
		dev->ctrl_rx_घातer_present = v4l2_ctrl_new_std(hdl_vid_cap,
			शून्य, V4L2_CID_DV_RX_POWER_PRESENT, 0, hdmi_input_mask,
			0, hdmi_input_mask);

	पूर्ण
	अगर (dev->num_hdmi_outमाला_दो) अणु
		s64 hdmi_output_mask = GENMASK(dev->num_hdmi_outमाला_दो - 1, 0);

		/*
		 * We aren't करोing anything with this at the moment, but
		 * HDMI outमाला_दो typically have this controls.
		 */
		dev->ctrl_tx_rgb_range = v4l2_ctrl_new_std_menu(hdl_vid_out, शून्य,
			V4L2_CID_DV_TX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
		dev->ctrl_tx_mode = v4l2_ctrl_new_std_menu(hdl_vid_out, शून्य,
			V4L2_CID_DV_TX_MODE, V4L2_DV_TX_MODE_HDMI,
			0, V4L2_DV_TX_MODE_HDMI);
		dev->ctrl_display_present = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_display_present, शून्य);
		dev->ctrl_tx_hotplug = v4l2_ctrl_new_std(hdl_vid_out,
			शून्य, V4L2_CID_DV_TX_HOTPLUG, 0, hdmi_output_mask,
			0, hdmi_output_mask);
		dev->ctrl_tx_rxsense = v4l2_ctrl_new_std(hdl_vid_out,
			शून्य, V4L2_CID_DV_TX_RXSENSE, 0, hdmi_output_mask,
			0, hdmi_output_mask);
		dev->ctrl_tx_edid_present = v4l2_ctrl_new_std(hdl_vid_out,
			शून्य, V4L2_CID_DV_TX_EDID_PRESENT, 0, hdmi_output_mask,
			0, hdmi_output_mask);
	पूर्ण
	अगर ((dev->has_vid_cap && dev->has_vid_out) ||
	    (dev->has_vbi_cap && dev->has_vbi_out))
		v4l2_ctrl_new_custom(hdl_loop_cap, &vivid_ctrl_loop_video, शून्य);

	अगर (dev->has_fb)
		v4l2_ctrl_new_custom(hdl_fb, &vivid_ctrl_clear_fb, शून्य);

	अगर (dev->has_radio_rx) अणु
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_hw_seek_mode, शून्य);
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_hw_seek_prog_lim, शून्य);
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_rx_rds_blockio, शून्य);
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_rx_rds_rbds, शून्य);
		v4l2_ctrl_new_std(hdl_radio_rx, &vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RECEPTION, 0, 1, 1, 1);
		dev->radio_rx_rds_pty = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_PTY, 0, 31, 1, 0);
		dev->radio_rx_rds_psname = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_PS_NAME, 0, 8, 8, 0);
		dev->radio_rx_rds_radiotext = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_RADIO_TEXT, 0, 64, 64, 0);
		dev->radio_rx_rds_ta = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
		dev->radio_rx_rds_tp = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_TRAFFIC_PROGRAM, 0, 1, 1, 0);
		dev->radio_rx_rds_ms = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_MUSIC_SPEECH, 0, 1, 1, 1);
	पूर्ण
	अगर (dev->has_radio_tx) अणु
		v4l2_ctrl_new_custom(hdl_radio_tx,
			&vivid_ctrl_radio_tx_rds_blockio, शून्य);
		dev->radio_tx_rds_pi = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_PI, 0, 0xffff, 1, 0x8088);
		dev->radio_tx_rds_pty = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_PTY, 0, 31, 1, 3);
		dev->radio_tx_rds_psname = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_PS_NAME, 0, 8, 8, 0);
		अगर (dev->radio_tx_rds_psname)
			v4l2_ctrl_s_ctrl_string(dev->radio_tx_rds_psname, "VIVID-TX");
		dev->radio_tx_rds_radiotext = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_RADIO_TEXT, 0, 64 * 2, 64, 0);
		अगर (dev->radio_tx_rds_radiotext)
			v4l2_ctrl_s_ctrl_string(dev->radio_tx_rds_radiotext,
			       "This is a VIVID default Radio Text template text, change at will");
		dev->radio_tx_rds_mono_stereo = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_MONO_STEREO, 0, 1, 1, 1);
		dev->radio_tx_rds_art_head = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_ARTIFICIAL_HEAD, 0, 1, 1, 0);
		dev->radio_tx_rds_compressed = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_COMPRESSED, 0, 1, 1, 0);
		dev->radio_tx_rds_dyn_pty = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_DYNAMIC_PTY, 0, 1, 1, 0);
		dev->radio_tx_rds_ta = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
		dev->radio_tx_rds_tp = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_TRAFFIC_PROGRAM, 0, 1, 1, 1);
		dev->radio_tx_rds_ms = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_MUSIC_SPEECH, 0, 1, 1, 1);
	पूर्ण
	अगर (dev->has_sdr_cap) अणु
		v4l2_ctrl_new_custom(hdl_sdr_cap,
			&vivid_ctrl_sdr_cap_fm_deviation, शून्य);
	पूर्ण
	अगर (dev->has_meta_cap) अणु
		v4l2_ctrl_new_custom(hdl_meta_cap,
				     &vivid_ctrl_meta_has_pts, शून्य);
		v4l2_ctrl_new_custom(hdl_meta_cap,
				     &vivid_ctrl_meta_has_src_clk, शून्य);
	पूर्ण

	अगर (hdl_user_gen->error)
		वापस hdl_user_gen->error;
	अगर (hdl_user_vid->error)
		वापस hdl_user_vid->error;
	अगर (hdl_user_aud->error)
		वापस hdl_user_aud->error;
	अगर (hdl_streaming->error)
		वापस hdl_streaming->error;
	अगर (hdl_sdr_cap->error)
		वापस hdl_sdr_cap->error;
	अगर (hdl_loop_cap->error)
		वापस hdl_loop_cap->error;

	अगर (dev->स्वतःgain)
		v4l2_ctrl_स्वतः_cluster(2, &dev->स्वतःgain, 0, true);

	अगर (dev->has_vid_cap) अणु
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_user_vid, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_user_aud, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_streaming, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_sdtv_cap, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_loop_cap, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_fb, शून्य, false);
		अगर (hdl_vid_cap->error)
			वापस hdl_vid_cap->error;
		dev->vid_cap_dev.ctrl_handler = hdl_vid_cap;
	पूर्ण
	अगर (dev->has_vid_out) अणु
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_user_aud, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_streaming, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_fb, शून्य, false);
		अगर (hdl_vid_out->error)
			वापस hdl_vid_out->error;
		dev->vid_out_dev.ctrl_handler = hdl_vid_out;
	पूर्ण
	अगर (dev->has_vbi_cap) अणु
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_streaming, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_sdtv_cap, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_loop_cap, शून्य, false);
		अगर (hdl_vbi_cap->error)
			वापस hdl_vbi_cap->error;
		dev->vbi_cap_dev.ctrl_handler = hdl_vbi_cap;
	पूर्ण
	अगर (dev->has_vbi_out) अणु
		v4l2_ctrl_add_handler(hdl_vbi_out, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_vbi_out, hdl_streaming, शून्य, false);
		अगर (hdl_vbi_out->error)
			वापस hdl_vbi_out->error;
		dev->vbi_out_dev.ctrl_handler = hdl_vbi_out;
	पूर्ण
	अगर (dev->has_radio_rx) अणु
		v4l2_ctrl_add_handler(hdl_radio_rx, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_radio_rx, hdl_user_aud, शून्य, false);
		अगर (hdl_radio_rx->error)
			वापस hdl_radio_rx->error;
		dev->radio_rx_dev.ctrl_handler = hdl_radio_rx;
	पूर्ण
	अगर (dev->has_radio_tx) अणु
		v4l2_ctrl_add_handler(hdl_radio_tx, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_radio_tx, hdl_user_aud, शून्य, false);
		अगर (hdl_radio_tx->error)
			वापस hdl_radio_tx->error;
		dev->radio_tx_dev.ctrl_handler = hdl_radio_tx;
	पूर्ण
	अगर (dev->has_sdr_cap) अणु
		v4l2_ctrl_add_handler(hdl_sdr_cap, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_sdr_cap, hdl_streaming, शून्य, false);
		अगर (hdl_sdr_cap->error)
			वापस hdl_sdr_cap->error;
		dev->sdr_cap_dev.ctrl_handler = hdl_sdr_cap;
	पूर्ण
	अगर (dev->has_meta_cap) अणु
		v4l2_ctrl_add_handler(hdl_meta_cap, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_meta_cap, hdl_streaming, शून्य, false);
		अगर (hdl_meta_cap->error)
			वापस hdl_meta_cap->error;
		dev->meta_cap_dev.ctrl_handler = hdl_meta_cap;
	पूर्ण
	अगर (dev->has_meta_out) अणु
		v4l2_ctrl_add_handler(hdl_meta_out, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_meta_out, hdl_streaming, शून्य, false);
		अगर (hdl_meta_out->error)
			वापस hdl_meta_out->error;
		dev->meta_out_dev.ctrl_handler = hdl_meta_out;
	पूर्ण
	अगर (dev->has_touch_cap) अणु
		v4l2_ctrl_add_handler(hdl_tch_cap, hdl_user_gen, शून्य, false);
		v4l2_ctrl_add_handler(hdl_tch_cap, hdl_streaming, शून्य, false);
		अगर (hdl_tch_cap->error)
			वापस hdl_tch_cap->error;
		dev->touch_cap_dev.ctrl_handler = hdl_tch_cap;
	पूर्ण
	वापस 0;
पूर्ण

व्योम vivid_मुक्त_controls(काष्ठा vivid_dev *dev)
अणु
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_vid_cap);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_vid_out);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_vbi_cap);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_vbi_out);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_radio_rx);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_radio_tx);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_sdr_cap);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_user_gen);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_user_vid);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_user_aud);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_streaming);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_sdtv_cap);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_loop_cap);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_fb);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_meta_cap);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_meta_out);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_hdl_touch_cap);
पूर्ण
