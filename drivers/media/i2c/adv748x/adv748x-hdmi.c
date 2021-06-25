<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Analog Devices ADV748X HDMI receiver and Component Processor (CP)
 *
 * Copyright (C) 2017 Renesas Electronics Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश <uapi/linux/v4l2-dv-timings.h>

#समावेश "adv748x.h"

/* -----------------------------------------------------------------------------
 * HDMI and CP
 */

#घोषणा ADV748X_HDMI_MIN_WIDTH		640
#घोषणा ADV748X_HDMI_MAX_WIDTH		1920
#घोषणा ADV748X_HDMI_MIN_HEIGHT		480
#घोषणा ADV748X_HDMI_MAX_HEIGHT		1200

/* V4L2_DV_BT_CEA_720X480I59_94 - 0.5 MHz */
#घोषणा ADV748X_HDMI_MIN_PIXELCLOCK	13000000
/* V4L2_DV_BT_DMT_1600X1200P60 */
#घोषणा ADV748X_HDMI_MAX_PIXELCLOCK	162000000

अटल स्थिर काष्ठा v4l2_dv_timings_cap adv748x_hdmi_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,

	V4L2_INIT_BT_TIMINGS(ADV748X_HDMI_MIN_WIDTH, ADV748X_HDMI_MAX_WIDTH,
			     ADV748X_HDMI_MIN_HEIGHT, ADV748X_HDMI_MAX_HEIGHT,
			     ADV748X_HDMI_MIN_PIXELCLOCK,
			     ADV748X_HDMI_MAX_PIXELCLOCK,
			     V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT,
			     V4L2_DV_BT_CAP_PROGRESSIVE)
पूर्ण;

काष्ठा adv748x_hdmi_video_standards अणु
	काष्ठा v4l2_dv_timings timings;
	u8 vid_std;
	u8 v_freq;
पूर्ण;

अटल स्थिर काष्ठा adv748x_hdmi_video_standards
adv748x_hdmi_video_standards[] = अणु
	अणु V4L2_DV_BT_CEA_720X480P59_94, 0x4a, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_720X576P50, 0x4b, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P60, 0x53, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P50, 0x53, 0x01 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P30, 0x53, 0x02 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P25, 0x53, 0x03 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P24, 0x53, 0x04 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P60, 0x5e, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P50, 0x5e, 0x01 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P30, 0x5e, 0x02 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P25, 0x5e, 0x03 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P24, 0x5e, 0x04 पूर्ण,
	/* SVGA */
	अणु V4L2_DV_BT_DMT_800X600P56, 0x80, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P60, 0x81, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P72, 0x82, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P75, 0x83, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P85, 0x84, 0x00 पूर्ण,
	/* SXGA */
	अणु V4L2_DV_BT_DMT_1280X1024P60, 0x85, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1280X1024P75, 0x86, 0x00 पूर्ण,
	/* VGA */
	अणु V4L2_DV_BT_DMT_640X480P60, 0x88, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P72, 0x89, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P75, 0x8a, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P85, 0x8b, 0x00 पूर्ण,
	/* XGA */
	अणु V4L2_DV_BT_DMT_1024X768P60, 0x8c, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P70, 0x8d, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P75, 0x8e, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P85, 0x8f, 0x00 पूर्ण,
	/* UXGA */
	अणु V4L2_DV_BT_DMT_1600X1200P60, 0x96, 0x00 पूर्ण,
पूर्ण;

अटल व्योम adv748x_hdmi_fill_क्रमmat(काष्ठा adv748x_hdmi *hdmi,
				     काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	स_रखो(fmt, 0, माप(*fmt));

	fmt->code = MEDIA_BUS_FMT_RGB888_1X24;
	fmt->field = hdmi->timings.bt.पूर्णांकerlaced ?
			V4L2_FIELD_ALTERNATE : V4L2_FIELD_NONE;

	/* TODO: The colorspace depends on the AVI InfoFrame contents */
	fmt->colorspace = V4L2_COLORSPACE_SRGB;

	fmt->width = hdmi->timings.bt.width;
	fmt->height = hdmi->timings.bt.height;

	अगर (fmt->field == V4L2_FIELD_ALTERNATE)
		fmt->height /= 2;
पूर्ण

अटल व्योम adv748x_fill_optional_dv_timings(काष्ठा v4l2_dv_timings *timings)
अणु
	v4l2_find_dv_timings_cap(timings, &adv748x_hdmi_timings_cap,
				 250000, शून्य, शून्य);
पूर्ण

अटल bool adv748x_hdmi_has_संकेत(काष्ठा adv748x_state *state)
अणु
	पूर्णांक val;

	/* Check that VERT_FILTER and DE_REGEN is locked */
	val = hdmi_पढ़ो(state, ADV748X_HDMI_LW1);
	वापस (val & ADV748X_HDMI_LW1_VERT_FILTER) &&
	       (val & ADV748X_HDMI_LW1_DE_REGEN);
पूर्ण

अटल पूर्णांक adv748x_hdmi_पढ़ो_pixelघड़ी(काष्ठा adv748x_state *state)
अणु
	पूर्णांक a, b;

	a = hdmi_पढ़ो(state, ADV748X_HDMI_TMDS_1);
	b = hdmi_पढ़ो(state, ADV748X_HDMI_TMDS_2);
	अगर (a < 0 || b < 0)
		वापस -ENODATA;

	/*
	 * The high 9 bits store TMDS frequency measurement in MHz
	 * The low 7 bits of TMDS_2 store the 7-bit TMDS fractional frequency
	 * measurement in 1/128 MHz
	 */
	वापस ((a << 1) | (b >> 7)) * 1000000 + (b & 0x7f) * 1000000 / 128;
पूर्ण

/*
 * adv748x_hdmi_set_de_timings: Adjust horizontal picture offset through DE
 *
 * HDMI CP uses a Data Enable synchronisation timing reference
 *
 * Vary the leading and trailing edge position of the DE संकेत output by the CP
 * core. Values are stored as चिन्हित-twos-complement in one-pixel-घड़ी units
 *
 * The start and end are shअगरted equally by the 10-bit shअगरt value.
 */
अटल व्योम adv748x_hdmi_set_de_timings(काष्ठा adv748x_state *state, पूर्णांक shअगरt)
अणु
	u8 high, low;

	/* POS_HIGH stores bits 8 and 9 of both the start and end */
	high = ADV748X_CP_DE_POS_HIGH_SET;
	high |= (shअगरt & 0x300) >> 8;
	low = shअगरt & 0xff;

	/* The sequence of the ग_लिखोs is important and must be followed */
	cp_ग_लिखो(state, ADV748X_CP_DE_POS_HIGH, high);
	cp_ग_लिखो(state, ADV748X_CP_DE_POS_END_LOW, low);

	high |= (shअगरt & 0x300) >> 6;

	cp_ग_लिखो(state, ADV748X_CP_DE_POS_HIGH, high);
	cp_ग_लिखो(state, ADV748X_CP_DE_POS_START_LOW, low);
पूर्ण

अटल पूर्णांक adv748x_hdmi_set_video_timings(काष्ठा adv748x_state *state,
					  स्थिर काष्ठा v4l2_dv_timings *timings)
अणु
	स्थिर काष्ठा adv748x_hdmi_video_standards *stds =
		adv748x_hdmi_video_standards;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adv748x_hdmi_video_standards); i++) अणु
		अगर (!v4l2_match_dv_timings(timings, &stds[i].timings, 250000,
					   false))
			जारी;
	पूर्ण

	अगर (i >= ARRAY_SIZE(adv748x_hdmi_video_standards))
		वापस -EINVAL;

	/*
	 * When setting cp_vid_std to either 720p, 1080i, or 1080p, the video
	 * will get shअगरted horizontally to the left in active video mode.
	 * The de_h_start and de_h_end controls are used to centre the picture
	 * correctly
	 */
	चयन (stds[i].vid_std) अणु
	हाल 0x53: /* 720p */
		adv748x_hdmi_set_de_timings(state, -40);
		अवरोध;
	हाल 0x54: /* 1080i */
	हाल 0x5e: /* 1080p */
		adv748x_hdmi_set_de_timings(state, -44);
		अवरोध;
	शेष:
		adv748x_hdmi_set_de_timings(state, 0);
		अवरोध;
	पूर्ण

	io_ग_लिखो(state, ADV748X_IO_VID_STD, stds[i].vid_std);
	io_clrset(state, ADV748X_IO_DATAPATH, ADV748X_IO_DATAPATH_VFREQ_M,
		  stds[i].v_freq << ADV748X_IO_DATAPATH_VFREQ_SHIFT);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * v4l2_subdev_video_ops
 */

अटल पूर्णांक adv748x_hdmi_s_dv_timings(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	पूर्णांक ret;

	अगर (!timings)
		वापस -EINVAL;

	अगर (v4l2_match_dv_timings(&hdmi->timings, timings, 0, false))
		वापस 0;

	अगर (!v4l2_valid_dv_timings(timings, &adv748x_hdmi_timings_cap,
				   शून्य, शून्य))
		वापस -दुस्फल;

	adv748x_fill_optional_dv_timings(timings);

	mutex_lock(&state->mutex);

	ret = adv748x_hdmi_set_video_timings(state, timings);
	अगर (ret)
		जाओ error;

	hdmi->timings = *timings;

	cp_clrset(state, ADV748X_CP_VID_ADJ_2, ADV748X_CP_VID_ADJ_2_INTERLACED,
		  timings->bt.पूर्णांकerlaced ?
				  ADV748X_CP_VID_ADJ_2_INTERLACED : 0);

	mutex_unlock(&state->mutex);

	वापस 0;

error:
	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_hdmi_g_dv_timings(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);

	mutex_lock(&state->mutex);

	*timings = hdmi->timings;

	mutex_unlock(&state->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_hdmi_query_dv_timings(काष्ठा v4l2_subdev *sd,
					 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	पूर्णांक pixelघड़ी;
	पूर्णांक polarity;

	अगर (!timings)
		वापस -EINVAL;

	स_रखो(timings, 0, माप(काष्ठा v4l2_dv_timings));

	अगर (!adv748x_hdmi_has_संकेत(state))
		वापस -ENOLINK;

	pixelघड़ी = adv748x_hdmi_पढ़ो_pixelघड़ी(state);
	अगर (pixelघड़ी < 0)
		वापस -ENODATA;

	timings->type = V4L2_DV_BT_656_1120;

	bt->pixelघड़ी = pixelघड़ी;
	bt->पूर्णांकerlaced = hdmi_पढ़ो(state, ADV748X_HDMI_F1H1) &
				ADV748X_HDMI_F1H1_INTERLACED ?
				V4L2_DV_INTERLACED : V4L2_DV_PROGRESSIVE;
	bt->width = hdmi_पढ़ो16(state, ADV748X_HDMI_LW1,
				ADV748X_HDMI_LW1_WIDTH_MASK);
	bt->height = hdmi_पढ़ो16(state, ADV748X_HDMI_F0H1,
				 ADV748X_HDMI_F0H1_HEIGHT_MASK);
	bt->hfrontporch = hdmi_पढ़ो16(state, ADV748X_HDMI_HFRONT_PORCH,
				      ADV748X_HDMI_HFRONT_PORCH_MASK);
	bt->hsync = hdmi_पढ़ो16(state, ADV748X_HDMI_HSYNC_WIDTH,
				ADV748X_HDMI_HSYNC_WIDTH_MASK);
	bt->hbackporch = hdmi_पढ़ो16(state, ADV748X_HDMI_HBACK_PORCH,
				     ADV748X_HDMI_HBACK_PORCH_MASK);
	bt->vfrontporch = hdmi_पढ़ो16(state, ADV748X_HDMI_VFRONT_PORCH,
				      ADV748X_HDMI_VFRONT_PORCH_MASK) / 2;
	bt->vsync = hdmi_पढ़ो16(state, ADV748X_HDMI_VSYNC_WIDTH,
				ADV748X_HDMI_VSYNC_WIDTH_MASK) / 2;
	bt->vbackporch = hdmi_पढ़ो16(state, ADV748X_HDMI_VBACK_PORCH,
				     ADV748X_HDMI_VBACK_PORCH_MASK) / 2;

	polarity = hdmi_पढ़ो(state, 0x05);
	bt->polarities = (polarity & BIT(4) ? V4L2_DV_VSYNC_POS_POL : 0) |
		(polarity & BIT(5) ? V4L2_DV_HSYNC_POS_POL : 0);

	अगर (bt->पूर्णांकerlaced == V4L2_DV_INTERLACED) अणु
		bt->height += hdmi_पढ़ो16(state, 0x0b, 0x1fff);
		bt->il_vfrontporch = hdmi_पढ़ो16(state, 0x2c, 0x3fff) / 2;
		bt->il_vsync = hdmi_पढ़ो16(state, 0x30, 0x3fff) / 2;
		bt->il_vbackporch = hdmi_पढ़ो16(state, 0x34, 0x3fff) / 2;
	पूर्ण

	adv748x_fill_optional_dv_timings(timings);

	/*
	 * No पूर्णांकerrupt handling is implemented yet.
	 * There should be an IRQ when a cable is plugged and the new timings
	 * should be figured out and stored to state.
	 */
	hdmi->timings = *timings;

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_hdmi_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);

	mutex_lock(&state->mutex);

	*status = adv748x_hdmi_has_संकेत(state) ? 0 : V4L2_IN_ST_NO_SIGNAL;

	mutex_unlock(&state->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_hdmi_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	पूर्णांक ret;

	mutex_lock(&state->mutex);

	ret = adv748x_tx_घातer(hdmi->tx, enable);
	अगर (ret)
		जाओ करोne;

	अगर (adv748x_hdmi_has_संकेत(state))
		adv_dbg(state, "Detected HDMI signal\n");
	अन्यथा
		adv_dbg(state, "Couldn't detect HDMI video signal\n");

करोne:
	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_hdmi_g_pixelaspect(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_fract *aspect)
अणु
	aspect->numerator = 1;
	aspect->denominator = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv748x_video_ops_hdmi = अणु
	.s_dv_timings = adv748x_hdmi_s_dv_timings,
	.g_dv_timings = adv748x_hdmi_g_dv_timings,
	.query_dv_timings = adv748x_hdmi_query_dv_timings,
	.g_input_status = adv748x_hdmi_g_input_status,
	.s_stream = adv748x_hdmi_s_stream,
	.g_pixelaspect = adv748x_hdmi_g_pixelaspect,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_pad_ops
 */

अटल पूर्णांक adv748x_hdmi_propagate_pixelrate(काष्ठा adv748x_hdmi *hdmi)
अणु
	काष्ठा v4l2_subdev *tx;
	काष्ठा v4l2_dv_timings timings;

	tx = adv748x_get_remote_sd(&hdmi->pads[ADV748X_HDMI_SOURCE]);
	अगर (!tx)
		वापस -ENOLINK;

	adv748x_hdmi_query_dv_timings(&hdmi->sd, &timings);

	वापस adv748x_csi2_set_pixelrate(tx, timings.bt.pixelघड़ी);
पूर्ण

अटल पूर्णांक adv748x_hdmi_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index != 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_RGB888_1X24;

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_hdmi_get_क्रमmat(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;

	अगर (sdक्रमmat->pad != ADV748X_HDMI_SOURCE)
		वापस -EINVAL;

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mbusक्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, sdक्रमmat->pad);
		sdक्रमmat->क्रमmat = *mbusक्रमmat;
	पूर्ण अन्यथा अणु
		adv748x_hdmi_fill_क्रमmat(hdmi, &sdक्रमmat->क्रमmat);
		adv748x_hdmi_propagate_pixelrate(hdmi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_hdmi_set_क्रमmat(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;

	अगर (sdक्रमmat->pad != ADV748X_HDMI_SOURCE)
		वापस -EINVAL;

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस adv748x_hdmi_get_क्रमmat(sd, cfg, sdक्रमmat);

	mbusक्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, sdक्रमmat->pad);
	*mbusक्रमmat = sdक्रमmat->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_hdmi_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (!hdmi->edid.present)
		वापस -ENODATA;

	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = hdmi->edid.blocks;
		वापस 0;
	पूर्ण

	अगर (edid->start_block >= hdmi->edid.blocks)
		वापस -EINVAL;

	अगर (edid->start_block + edid->blocks > hdmi->edid.blocks)
		edid->blocks = hdmi->edid.blocks - edid->start_block;

	स_नकल(edid->edid, hdmi->edid.edid + edid->start_block * 128,
			edid->blocks * 128);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक adv748x_hdmi_edid_ग_लिखो_block(काष्ठा adv748x_hdmi *hdmi,
					अचिन्हित पूर्णांक total_len, स्थिर u8 *val)
अणु
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	पूर्णांक err = 0;
	पूर्णांक i = 0;
	पूर्णांक len = 0;

	adv_dbg(state, "%s: write EDID block (%d byte)\n",
				__func__, total_len);

	जबतक (!err && i < total_len) अणु
		len = (total_len - i) > I2C_SMBUS_BLOCK_MAX ?
				I2C_SMBUS_BLOCK_MAX :
				(total_len - i);

		err = adv748x_ग_लिखो_block(state, ADV748X_PAGE_EDID,
				i, val + i, len);
		i += len;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक adv748x_hdmi_set_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	पूर्णांक err;

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->start_block != 0)
		वापस -EINVAL;

	अगर (edid->blocks == 0) अणु
		hdmi->edid.blocks = 0;
		hdmi->edid.present = 0;

		/* Fall back to a 16:9 aspect ratio */
		hdmi->aspect_ratio.numerator = 16;
		hdmi->aspect_ratio.denominator = 9;

		/* Disable the EDID */
		repeater_ग_लिखो(state, ADV748X_REPEATER_EDID_SZ,
			       edid->blocks << ADV748X_REPEATER_EDID_SZ_SHIFT);

		repeater_ग_लिखो(state, ADV748X_REPEATER_EDID_CTL, 0);

		वापस 0;
	पूर्ण

	अगर (edid->blocks > 4) अणु
		edid->blocks = 4;
		वापस -E2BIG;
	पूर्ण

	स_नकल(hdmi->edid.edid, edid->edid, 128 * edid->blocks);
	hdmi->edid.blocks = edid->blocks;
	hdmi->edid.present = true;

	hdmi->aspect_ratio = v4l2_calc_aspect_ratio(edid->edid[0x15],
			edid->edid[0x16]);

	err = adv748x_hdmi_edid_ग_लिखो_block(hdmi, 128 * edid->blocks,
			hdmi->edid.edid);
	अगर (err < 0) अणु
		v4l2_err(sd, "error %d writing edid pad %d\n", err, edid->pad);
		वापस err;
	पूर्ण

	repeater_ग_लिखो(state, ADV748X_REPEATER_EDID_SZ,
		       edid->blocks << ADV748X_REPEATER_EDID_SZ_SHIFT);

	repeater_ग_लिखो(state, ADV748X_REPEATER_EDID_CTL,
		       ADV748X_REPEATER_EDID_CTL_EN);

	वापस 0;
पूर्ण

अटल bool adv748x_hdmi_check_dv_timings(स्थिर काष्ठा v4l2_dv_timings *timings,
					  व्योम *hdl)
अणु
	स्थिर काष्ठा adv748x_hdmi_video_standards *stds =
		adv748x_hdmi_video_standards;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; stds[i].timings.bt.width; i++)
		अगर (v4l2_match_dv_timings(timings, &stds[i].timings, 0, false))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक adv748x_hdmi_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	वापस v4l2_क्रमागत_dv_timings_cap(timings, &adv748x_hdmi_timings_cap,
					adv748x_hdmi_check_dv_timings, शून्य);
पूर्ण

अटल पूर्णांक adv748x_hdmi_dv_timings_cap(काष्ठा v4l2_subdev *sd,
				       काष्ठा v4l2_dv_timings_cap *cap)
अणु
	*cap = adv748x_hdmi_timings_cap;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv748x_pad_ops_hdmi = अणु
	.क्रमागत_mbus_code = adv748x_hdmi_क्रमागत_mbus_code,
	.set_fmt = adv748x_hdmi_set_क्रमmat,
	.get_fmt = adv748x_hdmi_get_क्रमmat,
	.get_edid = adv748x_hdmi_get_edid,
	.set_edid = adv748x_hdmi_set_edid,
	.dv_timings_cap = adv748x_hdmi_dv_timings_cap,
	.क्रमागत_dv_timings = adv748x_hdmi_क्रमागत_dv_timings,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_ops
 */

अटल स्थिर काष्ठा v4l2_subdev_ops adv748x_ops_hdmi = अणु
	.video = &adv748x_video_ops_hdmi,
	.pad = &adv748x_pad_ops_hdmi,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Controls
 */

अटल स्थिर अक्षर * स्थिर hdmi_ctrl_patgen_menu[] = अणु
	"Disabled",
	"Solid Color",
	"Color Bars",
	"Ramp Grey",
	"Ramp Blue",
	"Ramp Red",
	"Checkered"
पूर्ण;

अटल पूर्णांक adv748x_hdmi_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा adv748x_hdmi *hdmi = adv748x_ctrl_to_hdmi(ctrl);
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	पूर्णांक ret;
	u8 pattern;

	/* Enable video adjusपंचांगent first */
	ret = cp_clrset(state, ADV748X_CP_VID_ADJ,
			ADV748X_CP_VID_ADJ_ENABLE,
			ADV748X_CP_VID_ADJ_ENABLE);
	अगर (ret < 0)
		वापस ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ret = cp_ग_लिखो(state, ADV748X_CP_BRI, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		ret = cp_ग_लिखो(state, ADV748X_CP_HUE, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = cp_ग_लिखो(state, ADV748X_CP_CON, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ret = cp_ग_लिखो(state, ADV748X_CP_SAT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		pattern = ctrl->val;

		/* Pattern is 0-indexed. Ctrl Menu is 1-indexed */
		अगर (pattern) अणु
			pattern--;
			pattern |= ADV748X_CP_PAT_GEN_EN;
		पूर्ण

		ret = cp_ग_लिखो(state, ADV748X_CP_PAT_GEN, pattern);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adv748x_hdmi_ctrl_ops = अणु
	.s_ctrl = adv748x_hdmi_s_ctrl,
पूर्ण;

अटल पूर्णांक adv748x_hdmi_init_controls(काष्ठा adv748x_hdmi *hdmi)
अणु
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);

	v4l2_ctrl_handler_init(&hdmi->ctrl_hdl, 5);

	/* Use our mutex क्रम the controls */
	hdmi->ctrl_hdl.lock = &state->mutex;

	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, ADV748X_CP_BRI_MIN,
			  ADV748X_CP_BRI_MAX, 1, ADV748X_CP_BRI_DEF);
	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_CONTRAST, ADV748X_CP_CON_MIN,
			  ADV748X_CP_CON_MAX, 1, ADV748X_CP_CON_DEF);
	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_SATURATION, ADV748X_CP_SAT_MIN,
			  ADV748X_CP_SAT_MAX, 1, ADV748X_CP_SAT_DEF);
	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_HUE, ADV748X_CP_HUE_MIN,
			  ADV748X_CP_HUE_MAX, 1, ADV748X_CP_HUE_DEF);

	/*
	 * Toकरो: V4L2_CID_DV_RX_POWER_PRESENT should also be supported when
	 * पूर्णांकerrupts are handled correctly
	 */

	v4l2_ctrl_new_std_menu_items(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(hdmi_ctrl_patgen_menu) - 1,
				     0, 0, hdmi_ctrl_patgen_menu);

	hdmi->sd.ctrl_handler = &hdmi->ctrl_hdl;
	अगर (hdmi->ctrl_hdl.error) अणु
		v4l2_ctrl_handler_मुक्त(&hdmi->ctrl_hdl);
		वापस hdmi->ctrl_hdl.error;
	पूर्ण

	वापस v4l2_ctrl_handler_setup(&hdmi->ctrl_hdl);
पूर्ण

पूर्णांक adv748x_hdmi_init(काष्ठा adv748x_hdmi *hdmi)
अणु
	काष्ठा adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	अटल स्थिर काष्ठा v4l2_dv_timings cea1280x720 =
		V4L2_DV_BT_CEA_1280X720P30;
	पूर्णांक ret;

	hdmi->timings = cea1280x720;

	/* Initialise a शेष 16:9 aspect ratio */
	hdmi->aspect_ratio.numerator = 16;
	hdmi->aspect_ratio.denominator = 9;

	adv748x_subdev_init(&hdmi->sd, state, &adv748x_ops_hdmi,
			    MEDIA_ENT_F_IO_DTV, "hdmi");

	hdmi->pads[ADV748X_HDMI_SINK].flags = MEDIA_PAD_FL_SINK;
	hdmi->pads[ADV748X_HDMI_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&hdmi->sd.entity,
				     ADV748X_HDMI_NR_PADS, hdmi->pads);
	अगर (ret)
		वापस ret;

	ret = adv748x_hdmi_init_controls(hdmi);
	अगर (ret)
		जाओ err_मुक्त_media;

	वापस 0;

err_मुक्त_media:
	media_entity_cleanup(&hdmi->sd.entity);

	वापस ret;
पूर्ण

व्योम adv748x_hdmi_cleanup(काष्ठा adv748x_hdmi *hdmi)
अणु
	v4l2_device_unरेजिस्टर_subdev(&hdmi->sd);
	media_entity_cleanup(&hdmi->sd.entity);
	v4l2_ctrl_handler_मुक्त(&hdmi->ctrl_hdl);
पूर्ण
