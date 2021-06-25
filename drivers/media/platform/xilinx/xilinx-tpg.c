<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Test Pattern Generator
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/xilinx-v4l2-controls.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "xilinx-vip.h"
#समावेश "xilinx-vtc.h"

#घोषणा XTPG_CTRL_STATUS_SLAVE_ERROR		(1 << 16)
#घोषणा XTPG_CTRL_IRQ_SLAVE_ERROR		(1 << 16)

#घोषणा XTPG_PATTERN_CONTROL			0x0100
#घोषणा XTPG_PATTERN_MASK			(0xf << 0)
#घोषणा XTPG_PATTERN_CONTROL_CROSS_HAIRS	(1 << 4)
#घोषणा XTPG_PATTERN_CONTROL_MOVING_BOX		(1 << 5)
#घोषणा XTPG_PATTERN_CONTROL_COLOR_MASK_SHIFT	6
#घोषणा XTPG_PATTERN_CONTROL_COLOR_MASK_MASK	(0xf << 6)
#घोषणा XTPG_PATTERN_CONTROL_STUCK_PIXEL	(1 << 9)
#घोषणा XTPG_PATTERN_CONTROL_NOISE		(1 << 10)
#घोषणा XTPG_PATTERN_CONTROL_MOTION		(1 << 12)
#घोषणा XTPG_MOTION_SPEED			0x0104
#घोषणा XTPG_CROSS_HAIRS			0x0108
#घोषणा XTPG_CROSS_HAIRS_ROW_SHIFT		0
#घोषणा XTPG_CROSS_HAIRS_ROW_MASK		(0xfff << 0)
#घोषणा XTPG_CROSS_HAIRS_COLUMN_SHIFT		16
#घोषणा XTPG_CROSS_HAIRS_COLUMN_MASK		(0xfff << 16)
#घोषणा XTPG_ZPLATE_HOR_CONTROL			0x010c
#घोषणा XTPG_ZPLATE_VER_CONTROL			0x0110
#घोषणा XTPG_ZPLATE_START_SHIFT			0
#घोषणा XTPG_ZPLATE_START_MASK			(0xffff << 0)
#घोषणा XTPG_ZPLATE_SPEED_SHIFT			16
#घोषणा XTPG_ZPLATE_SPEED_MASK			(0xffff << 16)
#घोषणा XTPG_BOX_SIZE				0x0114
#घोषणा XTPG_BOX_COLOR				0x0118
#घोषणा XTPG_STUCK_PIXEL_THRESH			0x011c
#घोषणा XTPG_NOISE_GAIN				0x0120
#घोषणा XTPG_BAYER_PHASE			0x0124
#घोषणा XTPG_BAYER_PHASE_RGGB			0
#घोषणा XTPG_BAYER_PHASE_GRBG			1
#घोषणा XTPG_BAYER_PHASE_GBRG			2
#घोषणा XTPG_BAYER_PHASE_BGGR			3
#घोषणा XTPG_BAYER_PHASE_OFF			4

/*
 * The minimum blanking value is one घड़ी cycle क्रम the front porch, one घड़ी
 * cycle क्रम the sync pulse and one घड़ी cycle क्रम the back porch.
 */
#घोषणा XTPG_MIN_HBLANK			3
#घोषणा XTPG_MAX_HBLANK			(XVTC_MAX_HSIZE - XVIP_MIN_WIDTH)
#घोषणा XTPG_MIN_VBLANK			3
#घोषणा XTPG_MAX_VBLANK			(XVTC_MAX_VSIZE - XVIP_MIN_HEIGHT)

/**
 * काष्ठा xtpg_device - Xilinx Test Pattern Generator device काष्ठाure
 * @xvip: Xilinx Video IP device
 * @pads: media pads
 * @npads: number of pads (1 or 2)
 * @has_input: whether an input is connected to the sink pad
 * @क्रमmats: active V4L2 media bus क्रमmat क्रम each pad
 * @शेष_क्रमmat: शेष V4L2 media bus क्रमmat
 * @vip_क्रमmat: क्रमmat inक्रमmation corresponding to the active क्रमmat
 * @bayer: boolean flag अगर TPG is set to any bayer क्रमmat
 * @ctrl_handler: control handler
 * @hblank: horizontal blanking control
 * @vblank: vertical blanking control
 * @pattern: test pattern control
 * @streaming: is the video stream active
 * @vtc: video timing controller
 * @vपंचांगux_gpio: video timing mux GPIO
 */
काष्ठा xtpg_device अणु
	काष्ठा xvip_device xvip;

	काष्ठा media_pad pads[2];
	अचिन्हित पूर्णांक npads;
	bool has_input;

	काष्ठा v4l2_mbus_framefmt क्रमmats[2];
	काष्ठा v4l2_mbus_framefmt शेष_क्रमmat;
	स्थिर काष्ठा xvip_video_क्रमmat *vip_क्रमmat;
	bool bayer;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *pattern;
	bool streaming;

	काष्ठा xvtc_device *vtc;
	काष्ठा gpio_desc *vपंचांगux_gpio;
पूर्ण;

अटल अंतरभूत काष्ठा xtpg_device *to_tpg(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा xtpg_device, xvip.subdev);
पूर्ण

अटल u32 xtpg_get_bayer_phase(अचिन्हित पूर्णांक code)
अणु
	चयन (code) अणु
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		वापस XTPG_BAYER_PHASE_RGGB;
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		वापस XTPG_BAYER_PHASE_GRBG;
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
		वापस XTPG_BAYER_PHASE_GBRG;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		वापस XTPG_BAYER_PHASE_BGGR;
	शेष:
		वापस XTPG_BAYER_PHASE_OFF;
	पूर्ण
पूर्ण

अटल व्योम __xtpg_update_pattern_control(काष्ठा xtpg_device *xtpg,
					  bool passthrough, bool pattern)
अणु
	u32 pattern_mask = (1 << (xtpg->pattern->maximum + 1)) - 1;

	/*
	 * If the TPG has no sink pad or no input connected to its sink pad
	 * passthrough mode can't be enabled.
	 */
	अगर (xtpg->npads == 1 || !xtpg->has_input)
		passthrough = false;

	/* If passthrough mode is allowed unmask bit 0. */
	अगर (passthrough)
		pattern_mask &= ~1;

	/* If test pattern mode is allowed unmask all other bits. */
	अगर (pattern)
		pattern_mask &= 1;

	__v4l2_ctrl_modअगरy_range(xtpg->pattern, 0, xtpg->pattern->maximum,
				 pattern_mask, pattern ? 9 : 0);
पूर्ण

अटल व्योम xtpg_update_pattern_control(काष्ठा xtpg_device *xtpg,
					bool passthrough, bool pattern)
अणु
	mutex_lock(xtpg->ctrl_handler.lock);
	__xtpg_update_pattern_control(xtpg, passthrough, pattern);
	mutex_unlock(xtpg->ctrl_handler.lock);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Video Operations
 */

अटल पूर्णांक xtpg_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा xtpg_device *xtpg = to_tpg(subdev);
	अचिन्हित पूर्णांक width = xtpg->क्रमmats[0].width;
	अचिन्हित पूर्णांक height = xtpg->क्रमmats[0].height;
	bool passthrough;
	u32 bayer_phase;

	अगर (!enable) अणु
		xvip_stop(&xtpg->xvip);
		अगर (xtpg->vtc)
			xvtc_generator_stop(xtpg->vtc);

		xtpg_update_pattern_control(xtpg, true, true);
		xtpg->streaming = false;
		वापस 0;
	पूर्ण

	xvip_set_frame_size(&xtpg->xvip, &xtpg->क्रमmats[0]);

	अगर (xtpg->vtc) अणु
		काष्ठा xvtc_config config = अणु
			.hblank_start = width,
			.hsync_start = width + 1,
			.vblank_start = height,
			.vsync_start = height + 1,
		पूर्ण;
		अचिन्हित पूर्णांक htotal;
		अचिन्हित पूर्णांक vtotal;

		htotal = min_t(अचिन्हित पूर्णांक, XVTC_MAX_HSIZE,
			       v4l2_ctrl_g_ctrl(xtpg->hblank) + width);
		vtotal = min_t(अचिन्हित पूर्णांक, XVTC_MAX_VSIZE,
			       v4l2_ctrl_g_ctrl(xtpg->vblank) + height);

		config.hsync_end = htotal - 1;
		config.hsize = htotal;
		config.vsync_end = vtotal - 1;
		config.vsize = vtotal;

		xvtc_generator_start(xtpg->vtc, &config);
	पूर्ण

	/*
	 * Configure the bayer phase and video timing mux based on the
	 * operation mode (passthrough or test pattern generation). The test
	 * pattern can be modअगरied by the control set handler, we thus need to
	 * take the control lock here to aव्योम races.
	 */
	mutex_lock(xtpg->ctrl_handler.lock);

	xvip_clr_and_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
			 XTPG_PATTERN_MASK, xtpg->pattern->cur.val);

	/*
	 * Switching between passthrough and test pattern generation modes isn't
	 * allowed during streaming, update the control range accordingly.
	 */
	passthrough = xtpg->pattern->cur.val == 0;
	__xtpg_update_pattern_control(xtpg, passthrough, !passthrough);

	xtpg->streaming = true;

	mutex_unlock(xtpg->ctrl_handler.lock);

	/*
	 * For TPG v5.0, the bayer phase needs to be off क्रम the pass through
	 * mode, otherwise the बाह्यal input would be subsampled.
	 */
	bayer_phase = passthrough ? XTPG_BAYER_PHASE_OFF
		    : xtpg_get_bayer_phase(xtpg->क्रमmats[0].code);
	xvip_ग_लिखो(&xtpg->xvip, XTPG_BAYER_PHASE, bayer_phase);

	अगर (xtpg->vपंचांगux_gpio)
		gpiod_set_value_cansleep(xtpg->vपंचांगux_gpio, !passthrough);

	xvip_start(&xtpg->xvip);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Pad Operations
 */

अटल काष्ठा v4l2_mbus_framefmt *
__xtpg_get_pad_क्रमmat(काष्ठा xtpg_device *xtpg,
		      काष्ठा v4l2_subdev_pad_config *cfg,
		      अचिन्हित पूर्णांक pad, u32 which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&xtpg->xvip.subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &xtpg->क्रमmats[pad];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक xtpg_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा xtpg_device *xtpg = to_tpg(subdev);

	fmt->क्रमmat = *__xtpg_get_pad_क्रमmat(xtpg, cfg, fmt->pad, fmt->which);

	वापस 0;
पूर्ण

अटल पूर्णांक xtpg_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा xtpg_device *xtpg = to_tpg(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	u32 bayer_phase;

	__क्रमmat = __xtpg_get_pad_क्रमmat(xtpg, cfg, fmt->pad, fmt->which);

	/* In two pads mode the source pad क्रमmat is always identical to the
	 * sink pad क्रमmat.
	 */
	अगर (xtpg->npads == 2 && fmt->pad == 1) अणु
		fmt->क्रमmat = *__क्रमmat;
		वापस 0;
	पूर्ण

	/* Bayer phase is configurable at runसमय */
	अगर (xtpg->bayer) अणु
		bayer_phase = xtpg_get_bayer_phase(fmt->क्रमmat.code);
		अगर (bayer_phase != XTPG_BAYER_PHASE_OFF)
			__क्रमmat->code = fmt->क्रमmat.code;
	पूर्ण

	xvip_set_क्रमmat_size(__क्रमmat, fmt);

	fmt->क्रमmat = *__क्रमmat;

	/* Propagate the क्रमmat to the source pad. */
	अगर (xtpg->npads == 2) अणु
		__क्रमmat = __xtpg_get_pad_क्रमmat(xtpg, cfg, 1, fmt->which);
		*__क्रमmat = fmt->क्रमmat;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल पूर्णांक xtpg_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, cfg, fse->pad);

	अगर (fse->index || fse->code != क्रमmat->code)
		वापस -EINVAL;

	/* Min / max values क्रम pad 0 is always fixed in both one and two pads
	 * modes. In two pads mode, the source pad(= 1) size is identical to
	 * the sink pad size */
	अगर (fse->pad == 0) अणु
		fse->min_width = XVIP_MIN_WIDTH;
		fse->max_width = XVIP_MAX_WIDTH;
		fse->min_height = XVIP_MIN_HEIGHT;
		fse->max_height = XVIP_MAX_HEIGHT;
	पूर्ण अन्यथा अणु
		fse->min_width = क्रमmat->width;
		fse->max_width = क्रमmat->width;
		fse->min_height = क्रमmat->height;
		fse->max_height = क्रमmat->height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xtpg_खोलो(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा xtpg_device *xtpg = to_tpg(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, fh->pad, 0);
	*क्रमmat = xtpg->शेष_क्रमmat;

	अगर (xtpg->npads == 2) अणु
		क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, fh->pad, 1);
		*क्रमmat = xtpg->शेष_क्रमmat;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xtpg_बंद(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xtpg_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा xtpg_device *xtpg = container_of(ctrl->handler,
						काष्ठा xtpg_device,
						ctrl_handler);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_TEST_PATTERN:
		xvip_clr_and_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				 XTPG_PATTERN_MASK, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_CROSS_HAIRS:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_CROSS_HAIRS, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_MOVING_BOX:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_MOVING_BOX, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_COLOR_MASK:
		xvip_clr_and_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				 XTPG_PATTERN_CONTROL_COLOR_MASK_MASK,
				 ctrl->val <<
				 XTPG_PATTERN_CONTROL_COLOR_MASK_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_STUCK_PIXEL:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_STUCK_PIXEL, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_NOISE:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_NOISE, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_MOTION:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_MOTION, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_MOTION_SPEED:
		xvip_ग_लिखो(&xtpg->xvip, XTPG_MOTION_SPEED, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_CROSS_HAIR_ROW:
		xvip_clr_and_set(&xtpg->xvip, XTPG_CROSS_HAIRS,
				 XTPG_CROSS_HAIRS_ROW_MASK,
				 ctrl->val << XTPG_CROSS_HAIRS_ROW_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_CROSS_HAIR_COLUMN:
		xvip_clr_and_set(&xtpg->xvip, XTPG_CROSS_HAIRS,
				 XTPG_CROSS_HAIRS_COLUMN_MASK,
				 ctrl->val << XTPG_CROSS_HAIRS_COLUMN_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_ZPLATE_HOR_START:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_HOR_CONTROL,
				 XTPG_ZPLATE_START_MASK,
				 ctrl->val << XTPG_ZPLATE_START_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_ZPLATE_HOR_SPEED:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_HOR_CONTROL,
				 XTPG_ZPLATE_SPEED_MASK,
				 ctrl->val << XTPG_ZPLATE_SPEED_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_ZPLATE_VER_START:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_VER_CONTROL,
				 XTPG_ZPLATE_START_MASK,
				 ctrl->val << XTPG_ZPLATE_START_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_ZPLATE_VER_SPEED:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_VER_CONTROL,
				 XTPG_ZPLATE_SPEED_MASK,
				 ctrl->val << XTPG_ZPLATE_SPEED_SHIFT);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_BOX_SIZE:
		xvip_ग_लिखो(&xtpg->xvip, XTPG_BOX_SIZE, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_BOX_COLOR:
		xvip_ग_लिखो(&xtpg->xvip, XTPG_BOX_COLOR, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_STUCK_PIXEL_THRESH:
		xvip_ग_लिखो(&xtpg->xvip, XTPG_STUCK_PIXEL_THRESH, ctrl->val);
		वापस 0;
	हाल V4L2_CID_XILINX_TPG_NOISE_GAIN:
		xvip_ग_लिखो(&xtpg->xvip, XTPG_NOISE_GAIN, ctrl->val);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops xtpg_ctrl_ops = अणु
	.s_ctrl	= xtpg_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops xtpg_core_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops xtpg_video_ops = अणु
	.s_stream = xtpg_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops xtpg_pad_ops = अणु
	.क्रमागत_mbus_code		= xvip_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= xtpg_क्रमागत_frame_size,
	.get_fmt		= xtpg_get_क्रमmat,
	.set_fmt		= xtpg_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops xtpg_ops = अणु
	.core   = &xtpg_core_ops,
	.video  = &xtpg_video_ops,
	.pad    = &xtpg_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops xtpg_पूर्णांकernal_ops = अणु
	.खोलो	= xtpg_खोलो,
	.बंद	= xtpg_बंद,
पूर्ण;

/*
 * Control Config
 */

अटल स्थिर अक्षर *स्थिर xtpg_pattern_strings[] = अणु
	"Passthrough",
	"Horizontal Ramp",
	"Vertical Ramp",
	"Temporal Ramp",
	"Solid Red",
	"Solid Green",
	"Solid Blue",
	"Solid Black",
	"Solid White",
	"Color Bars",
	"Zone Plate",
	"Tartan Color Bars",
	"Cross Hatch",
	"None",
	"Vertical/Horizontal Ramps",
	"Black/White Checker Board",
पूर्ण;

अटल काष्ठा v4l2_ctrl_config xtpg_ctrls[] = अणु
	अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_CROSS_HAIRS,
		.name	= "Test Pattern: Cross Hairs",
		.type	= V4L2_CTRL_TYPE_BOOLEAN,
		.min	= false,
		.max	= true,
		.step	= 1,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_MOVING_BOX,
		.name	= "Test Pattern: Moving Box",
		.type	= V4L2_CTRL_TYPE_BOOLEAN,
		.min	= false,
		.max	= true,
		.step	= 1,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_COLOR_MASK,
		.name	= "Test Pattern: Color Mask",
		.type	= V4L2_CTRL_TYPE_BITMASK,
		.min	= 0,
		.max	= 0xf,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_STUCK_PIXEL,
		.name	= "Test Pattern: Stuck Pixel",
		.type	= V4L2_CTRL_TYPE_BOOLEAN,
		.min	= false,
		.max	= true,
		.step	= 1,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_NOISE,
		.name	= "Test Pattern: Noise",
		.type	= V4L2_CTRL_TYPE_BOOLEAN,
		.min	= false,
		.max	= true,
		.step	= 1,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_MOTION,
		.name	= "Test Pattern: Motion",
		.type	= V4L2_CTRL_TYPE_BOOLEAN,
		.min	= false,
		.max	= true,
		.step	= 1,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_MOTION_SPEED,
		.name	= "Test Pattern: Motion Speed",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 8) - 1,
		.step	= 1,
		.def	= 4,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_CROSS_HAIR_ROW,
		.name	= "Test Pattern: Cross Hairs Row",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 12) - 1,
		.step	= 1,
		.def	= 0x64,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_CROSS_HAIR_COLUMN,
		.name	= "Test Pattern: Cross Hairs Column",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 12) - 1,
		.step	= 1,
		.def	= 0x64,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_ZPLATE_HOR_START,
		.name	= "Test Pattern: Zplate Horizontal Start Pos",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0x1e,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_ZPLATE_HOR_SPEED,
		.name	= "Test Pattern: Zplate Horizontal Speed",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_ZPLATE_VER_START,
		.name	= "Test Pattern: Zplate Vertical Start Pos",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 1,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_ZPLATE_VER_SPEED,
		.name	= "Test Pattern: Zplate Vertical Speed",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_BOX_SIZE,
		.name	= "Test Pattern: Box Size",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 12) - 1,
		.step	= 1,
		.def	= 0x32,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_BOX_COLOR,
		.name	= "Test Pattern: Box Color(RGB)",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 24) - 1,
		.step	= 1,
		.def	= 0,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_STUCK_PIXEL_THRESH,
		.name	= "Test Pattern: Stuck Pixel threshold",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण, अणु
		.ops	= &xtpg_ctrl_ops,
		.id	= V4L2_CID_XILINX_TPG_NOISE_GAIN,
		.name	= "Test Pattern: Noise Gain",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= 0,
		.max	= (1 << 8) - 1,
		.step	= 1,
		.def	= 0,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media Operations
 */

अटल स्थिर काष्ठा media_entity_operations xtpg_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Power Management
 */

अटल पूर्णांक __maybe_unused xtpg_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा xtpg_device *xtpg = dev_get_drvdata(dev);

	xvip_suspend(&xtpg->xvip);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xtpg_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा xtpg_device *xtpg = dev_get_drvdata(dev);

	xvip_resume(&xtpg->xvip);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Platक्रमm Device Driver
 */

अटल पूर्णांक xtpg_parse_of(काष्ठा xtpg_device *xtpg)
अणु
	काष्ठा device *dev = xtpg->xvip.dev;
	काष्ठा device_node *node = xtpg->xvip.dev->of_node;
	काष्ठा device_node *ports;
	काष्ठा device_node *port;
	अचिन्हित पूर्णांक nports = 0;
	bool has_endpoपूर्णांक = false;

	ports = of_get_child_by_name(node, "ports");
	अगर (ports == शून्य)
		ports = node;

	क्रम_each_child_of_node(ports, port) अणु
		स्थिर काष्ठा xvip_video_क्रमmat *क्रमmat;
		काष्ठा device_node *endpoपूर्णांक;

		अगर (!of_node_name_eq(port, "port"))
			जारी;

		क्रमmat = xvip_of_get_क्रमmat(port);
		अगर (IS_ERR(क्रमmat)) अणु
			dev_err(dev, "invalid format in DT");
			of_node_put(port);
			वापस PTR_ERR(क्रमmat);
		पूर्ण

		/* Get and check the क्रमmat description */
		अगर (!xtpg->vip_क्रमmat) अणु
			xtpg->vip_क्रमmat = क्रमmat;
		पूर्ण अन्यथा अगर (xtpg->vip_क्रमmat != क्रमmat) अणु
			dev_err(dev, "in/out format mismatch in DT");
			of_node_put(port);
			वापस -EINVAL;
		पूर्ण

		अगर (nports == 0) अणु
			endpoपूर्णांक = of_get_next_child(port, शून्य);
			अगर (endpoपूर्णांक)
				has_endpoपूर्णांक = true;
			of_node_put(endpoपूर्णांक);
		पूर्ण

		/* Count the number of ports. */
		nports++;
	पूर्ण

	अगर (nports != 1 && nports != 2) अणु
		dev_err(dev, "invalid number of ports %u\n", nports);
		वापस -EINVAL;
	पूर्ण

	xtpg->npads = nports;
	अगर (nports == 2 && has_endpoपूर्णांक)
		xtpg->has_input = true;

	वापस 0;
पूर्ण

अटल पूर्णांक xtpg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *subdev;
	काष्ठा xtpg_device *xtpg;
	u32 i, bayer_phase;
	पूर्णांक ret;

	xtpg = devm_kzalloc(&pdev->dev, माप(*xtpg), GFP_KERNEL);
	अगर (!xtpg)
		वापस -ENOMEM;

	xtpg->xvip.dev = &pdev->dev;

	ret = xtpg_parse_of(xtpg);
	अगर (ret < 0)
		वापस ret;

	ret = xvip_init_resources(&xtpg->xvip);
	अगर (ret < 0)
		वापस ret;

	xtpg->vपंचांगux_gpio = devm_gpiod_get_optional(&pdev->dev, "timing",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(xtpg->vपंचांगux_gpio)) अणु
		ret = PTR_ERR(xtpg->vपंचांगux_gpio);
		जाओ error_resource;
	पूर्ण

	xtpg->vtc = xvtc_of_get(pdev->dev.of_node);
	अगर (IS_ERR(xtpg->vtc)) अणु
		ret = PTR_ERR(xtpg->vtc);
		जाओ error_resource;
	पूर्ण

	/* Reset and initialize the core */
	xvip_reset(&xtpg->xvip);

	/* Initialize V4L2 subdevice and media entity. Pad numbers depend on the
	 * number of pads.
	 */
	अगर (xtpg->npads == 2) अणु
		xtpg->pads[0].flags = MEDIA_PAD_FL_SINK;
		xtpg->pads[1].flags = MEDIA_PAD_FL_SOURCE;
	पूर्ण अन्यथा अणु
		xtpg->pads[0].flags = MEDIA_PAD_FL_SOURCE;
	पूर्ण

	/* Initialize the शेष क्रमmat */
	xtpg->शेष_क्रमmat.code = xtpg->vip_क्रमmat->code;
	xtpg->शेष_क्रमmat.field = V4L2_FIELD_NONE;
	xtpg->शेष_क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
	xvip_get_frame_size(&xtpg->xvip, &xtpg->शेष_क्रमmat);

	bayer_phase = xtpg_get_bayer_phase(xtpg->vip_क्रमmat->code);
	अगर (bayer_phase != XTPG_BAYER_PHASE_OFF)
		xtpg->bayer = true;

	xtpg->क्रमmats[0] = xtpg->शेष_क्रमmat;
	अगर (xtpg->npads == 2)
		xtpg->क्रमmats[1] = xtpg->शेष_क्रमmat;

	/* Initialize V4L2 subdevice and media entity */
	subdev = &xtpg->xvip.subdev;
	v4l2_subdev_init(subdev, &xtpg_ops);
	subdev->dev = &pdev->dev;
	subdev->पूर्णांकernal_ops = &xtpg_पूर्णांकernal_ops;
	strscpy(subdev->name, dev_name(&pdev->dev), माप(subdev->name));
	v4l2_set_subdevdata(subdev, xtpg);
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev->entity.ops = &xtpg_media_ops;

	ret = media_entity_pads_init(&subdev->entity, xtpg->npads, xtpg->pads);
	अगर (ret < 0)
		जाओ error;

	v4l2_ctrl_handler_init(&xtpg->ctrl_handler, 3 + ARRAY_SIZE(xtpg_ctrls));

	xtpg->vblank = v4l2_ctrl_new_std(&xtpg->ctrl_handler, &xtpg_ctrl_ops,
					 V4L2_CID_VBLANK, XTPG_MIN_VBLANK,
					 XTPG_MAX_VBLANK, 1, 100);
	xtpg->hblank = v4l2_ctrl_new_std(&xtpg->ctrl_handler, &xtpg_ctrl_ops,
					 V4L2_CID_HBLANK, XTPG_MIN_HBLANK,
					 XTPG_MAX_HBLANK, 1, 100);
	xtpg->pattern = v4l2_ctrl_new_std_menu_items(&xtpg->ctrl_handler,
					&xtpg_ctrl_ops, V4L2_CID_TEST_PATTERN,
					ARRAY_SIZE(xtpg_pattern_strings) - 1,
					1, 9, xtpg_pattern_strings);

	क्रम (i = 0; i < ARRAY_SIZE(xtpg_ctrls); i++)
		v4l2_ctrl_new_custom(&xtpg->ctrl_handler, &xtpg_ctrls[i], शून्य);

	अगर (xtpg->ctrl_handler.error) अणु
		dev_err(&pdev->dev, "failed to add controls\n");
		ret = xtpg->ctrl_handler.error;
		जाओ error;
	पूर्ण
	subdev->ctrl_handler = &xtpg->ctrl_handler;

	xtpg_update_pattern_control(xtpg, true, true);

	ret = v4l2_ctrl_handler_setup(&xtpg->ctrl_handler);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to set controls\n");
		जाओ error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, xtpg);

	xvip_prपूर्णांक_version(&xtpg->xvip);

	ret = v4l2_async_रेजिस्टर_subdev(subdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register subdev\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(&xtpg->ctrl_handler);
	media_entity_cleanup(&subdev->entity);
	xvtc_put(xtpg->vtc);
error_resource:
	xvip_cleanup_resources(&xtpg->xvip);
	वापस ret;
पूर्ण

अटल पूर्णांक xtpg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xtpg_device *xtpg = platक्रमm_get_drvdata(pdev);
	काष्ठा v4l2_subdev *subdev = &xtpg->xvip.subdev;

	v4l2_async_unरेजिस्टर_subdev(subdev);
	v4l2_ctrl_handler_मुक्त(&xtpg->ctrl_handler);
	media_entity_cleanup(&subdev->entity);

	xvip_cleanup_resources(&xtpg->xvip);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(xtpg_pm_ops, xtpg_pm_suspend, xtpg_pm_resume);

अटल स्थिर काष्ठा of_device_id xtpg_of_id_table[] = अणु
	अणु .compatible = "xlnx,v-tpg-5.0" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xtpg_of_id_table);

अटल काष्ठा platक्रमm_driver xtpg_driver = अणु
	.driver = अणु
		.name		= "xilinx-tpg",
		.pm		= &xtpg_pm_ops,
		.of_match_table	= xtpg_of_id_table,
	पूर्ण,
	.probe			= xtpg_probe,
	.हटाओ			= xtpg_हटाओ,
पूर्ण;

module_platक्रमm_driver(xtpg_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Xilinx Test Pattern Generator Driver");
MODULE_LICENSE("GPL v2");
