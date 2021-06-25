<शैली गुरु>
/*
 * ths8200 - Texas Instruments THS8200 video encoder driver
 *
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/v4l2-dv-timings.h>

#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>

#समावेश "ths8200_regs.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

MODULE_DESCRIPTION("Texas Instruments THS8200 video encoder driver");
MODULE_AUTHOR("Mats Randgaard <mats.randgaard@cisco.com>");
MODULE_AUTHOR("Martin Bugge <martin.bugge@cisco.com>");
MODULE_LICENSE("GPL v2");

काष्ठा ths8200_state अणु
	काष्ठा v4l2_subdev sd;
	uपूर्णांक8_t chip_version;
	/* Is the ths8200 घातered on? */
	bool घातer_on;
	काष्ठा v4l2_dv_timings dv_timings;
पूर्ण;

अटल स्थिर काष्ठा v4l2_dv_timings_cap ths8200_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1080, 25000000, 148500000,
		V4L2_DV_BT_STD_CEA861, V4L2_DV_BT_CAP_PROGRESSIVE)
पूर्ण;

अटल अंतरभूत काष्ठा ths8200_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ths8200_state, sd);
पूर्ण

अटल अंतरभूत अचिन्हित htotal(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_FRAME_WIDTH(t);
पूर्ण

अटल अंतरभूत अचिन्हित vtotal(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_FRAME_HEIGHT(t);
पूर्ण

अटल पूर्णांक ths8200_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक ths8200_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	v4l2_err(sd, "I2C Write Problem\n");
	वापस ret;
पूर्ण

/* To set specअगरic bits in the रेजिस्टर, a clear-mask is given (to be AND-ed),
 * and then the value-mask (to be OR-ed).
 */
अटल अंतरभूत व्योम
ths8200_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg,
		     uपूर्णांक8_t clr_mask, uपूर्णांक8_t val_mask)
अणु
	ths8200_ग_लिखो(sd, reg, (ths8200_पढ़ो(sd, reg) & clr_mask) | val_mask);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG

अटल पूर्णांक ths8200_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = ths8200_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ths8200_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	ths8200_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ths8200_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ths8200_state *state = to_state(sd);
	uपूर्णांक8_t reg_03 = ths8200_पढ़ो(sd, THS8200_CHIP_CTL);

	v4l2_info(sd, "----- Chip status -----\n");
	v4l2_info(sd, "version: %u\n", state->chip_version);
	v4l2_info(sd, "power: %s\n", (reg_03 & 0x0c) ? "off" : "on");
	v4l2_info(sd, "reset: %s\n", (reg_03 & 0x01) ? "off" : "on");
	v4l2_info(sd, "test pattern: %s\n",
		  (reg_03 & 0x20) ? "enabled" : "disabled");
	v4l2_info(sd, "format: %ux%u\n",
		  ths8200_पढ़ो(sd, THS8200_DTG2_PIXEL_CNT_MSB) * 256 +
		  ths8200_पढ़ो(sd, THS8200_DTG2_PIXEL_CNT_LSB),
		  (ths8200_पढ़ो(sd, THS8200_DTG2_LINE_CNT_MSB) & 0x07) * 256 +
		  ths8200_पढ़ो(sd, THS8200_DTG2_LINE_CNT_LSB));
	v4l2_prपूर्णांक_dv_timings(sd->name, "Configured format:",
			      &state->dv_timings, true);
	वापस 0;
पूर्ण

/* Power up/करोwn ths8200 */
अटल पूर्णांक ths8200_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ths8200_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s: power %s\n", __func__, on ? "on" : "off");

	state->घातer_on = on;

	/* Power up/करोwn - leave in reset state until input video is present */
	ths8200_ग_लिखो_and_or(sd, THS8200_CHIP_CTL, 0xf2, (on ? 0x00 : 0x0c));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ths8200_core_ops = अणु
	.log_status = ths8200_log_status,
	.s_घातer = ths8200_s_घातer,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = ths8200_g_रेजिस्टर,
	.s_रेजिस्टर = ths8200_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev video operations
 */

अटल पूर्णांक ths8200_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ths8200_state *state = to_state(sd);

	अगर (enable && !state->घातer_on)
		ths8200_s_घातer(sd, true);

	ths8200_ग_लिखो_and_or(sd, THS8200_CHIP_CTL, 0xfe,
			     (enable ? 0x01 : 0x00));

	v4l2_dbg(1, debug, sd, "%s: %sable\n",
		 __func__, (enable ? "en" : "dis"));

	वापस 0;
पूर्ण

अटल व्योम ths8200_core_init(काष्ठा v4l2_subdev *sd)
अणु
	/* setup घड़ीs */
	ths8200_ग_लिखो_and_or(sd, THS8200_CHIP_CTL, 0x3f, 0xc0);

	/**** Data path control (DATA) ****/
	/* Set FSADJ 700 mV,
	 * bypass 422-444 पूर्णांकerpolation,
	 * input क्रमmat 30 bit RGB444
	 */
	ths8200_ग_लिखो(sd, THS8200_DATA_CNTL, 0x70);

	/* DTG Mode (Video blocked during blanking
	 * VESA slave
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG1_MODE, 0x87);

	/**** Display Timing Generator Control, Part 1 (DTG1). ****/

	/* Disable embedded syncs on the output by setting
	 * the amplitude to zero क्रम all channels.
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG1_Y_SYNC_MSB, 0x00);
	ths8200_ग_लिखो(sd, THS8200_DTG1_CBCR_SYNC_MSB, 0x00);
पूर्ण

अटल व्योम ths8200_setup(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_bt_timings *bt)
अणु
	uपूर्णांक8_t polarity = 0;
	uपूर्णांक16_t line_start_active_video = (bt->vsync + bt->vbackporch);
	uपूर्णांक16_t line_start_front_porch  = (vtotal(bt) - bt->vfrontporch);

	/*** System ****/
	/* Set chip in reset जबतक it is configured */
	ths8200_s_stream(sd, false);

	/* configure video output timings */
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_A, bt->hsync);
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_B, bt->hfrontporch);

	/* Zero क्रम progressive scan क्रमmats.*/
	अगर (!bt->पूर्णांकerlaced)
		ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_C, 0x00);

	/* Distance from leading edge of h sync to start of active video.
	 * MSB in 0x2b
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_D_LSB,
		      (bt->hbackporch + bt->hsync) & 0xff);
	/* Zero क्रम SDTV-mode. MSB in 0x2b */
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_E_LSB, 0x00);
	/*
	 * MSB क्रम dtg1_spec(d/e/h). See comment क्रम
	 * corresponding LSB रेजिस्टरs.
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_DEH_MSB,
		      ((bt->hbackporch + bt->hsync) & 0x100) >> 1);

	/* h front porch */
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_K_LSB, (bt->hfrontporch) & 0xff);
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_K_MSB,
		      ((bt->hfrontporch) & 0x700) >> 8);

	/* Half the line length. Used to calculate SDTV line types. */
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_G_LSB, (htotal(bt)/2) & 0xff);
	ths8200_ग_लिखो(sd, THS8200_DTG1_SPEC_G_MSB,
		      ((htotal(bt)/2) >> 8) & 0x0f);

	/* Total pixels per line (ex. 720p: 1650) */
	ths8200_ग_लिखो(sd, THS8200_DTG1_TOT_PIXELS_MSB, htotal(bt) >> 8);
	ths8200_ग_लिखो(sd, THS8200_DTG1_TOT_PIXELS_LSB, htotal(bt) & 0xff);

	/* Frame height and field height */
	/* Field height should be programmed higher than frame_size क्रम
	 * progressive scan क्रमmats
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG1_FRAME_FIELD_SZ_MSB,
		      ((vtotal(bt) >> 4) & 0xf0) + 0x7);
	ths8200_ग_लिखो(sd, THS8200_DTG1_FRAME_SZ_LSB, vtotal(bt) & 0xff);

	/* Should be programmed higher than frame_size
	 * क्रम progressive क्रमmats
	 */
	अगर (!bt->पूर्णांकerlaced)
		ths8200_ग_लिखो(sd, THS8200_DTG1_FIELD_SZ_LSB, 0xff);

	/**** Display Timing Generator Control, Part 2 (DTG2). ****/
	/* Set अवरोधpoपूर्णांक line numbers and types
	 * THS8200 generates line types with dअगरferent properties. A line type
	 * that sets all the RGB-outमाला_दो to zero is used in the blanking areas,
	 * जबतक a line type that enable the RGB-outमाला_दो is used in active video
	 * area. The line numbers क्रम start of active video, start of front
	 * porch and after the last line in the frame must be set with the
	 * corresponding line types.
	 *
	 * Line types:
	 * 0x9 - Full normal sync pulse: Blocks data when dtg1_pass is off.
	 *       Used in blanking area.
	 * 0x0 - Active video: Video data is always passed. Used in active
	 *       video area.
	 */
	ths8200_ग_लिखो_and_or(sd, THS8200_DTG2_BP1_2_MSB, 0x88,
			     ((line_start_active_video >> 4) & 0x70) +
			     ((line_start_front_porch >> 8) & 0x07));
	ths8200_ग_लिखो(sd, THS8200_DTG2_BP3_4_MSB, ((vtotal(bt)) >> 4) & 0x70);
	ths8200_ग_लिखो(sd, THS8200_DTG2_BP1_LSB, line_start_active_video & 0xff);
	ths8200_ग_लिखो(sd, THS8200_DTG2_BP2_LSB, line_start_front_porch & 0xff);
	ths8200_ग_लिखो(sd, THS8200_DTG2_BP3_LSB, (vtotal(bt)) & 0xff);

	/* line types */
	ths8200_ग_लिखो(sd, THS8200_DTG2_LINETYPE1, 0x90);
	ths8200_ग_लिखो(sd, THS8200_DTG2_LINETYPE2, 0x90);

	/* h sync width transmitted */
	ths8200_ग_लिखो(sd, THS8200_DTG2_HLENGTH_LSB, bt->hsync & 0xff);
	ths8200_ग_लिखो_and_or(sd, THS8200_DTG2_HLENGTH_LSB_HDLY_MSB, 0x3f,
			     (bt->hsync >> 2) & 0xc0);

	/* The pixel value h sync is निश्चितed on */
	ths8200_ग_लिखो_and_or(sd, THS8200_DTG2_HLENGTH_LSB_HDLY_MSB, 0xe0,
			     (htotal(bt) >> 8) & 0x1f);
	ths8200_ग_लिखो(sd, THS8200_DTG2_HLENGTH_HDLY_LSB, htotal(bt));

	/* v sync width transmitted (must add 1 to get correct output) */
	ths8200_ग_लिखो(sd, THS8200_DTG2_VLENGTH1_LSB, (bt->vsync + 1) & 0xff);
	ths8200_ग_लिखो_and_or(sd, THS8200_DTG2_VLENGTH1_MSB_VDLY1_MSB, 0x3f,
			     ((bt->vsync + 1) >> 2) & 0xc0);

	/* The pixel value v sync is निश्चितed on (must add 1 to get correct output) */
	ths8200_ग_लिखो_and_or(sd, THS8200_DTG2_VLENGTH1_MSB_VDLY1_MSB, 0xf8,
			     ((vtotal(bt) + 1) >> 8) & 0x7);
	ths8200_ग_लिखो(sd, THS8200_DTG2_VDLY1_LSB, vtotal(bt) + 1);

	/* For progressive video vlength2 must be set to all 0 and vdly2 must
	 * be set to all 1.
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG2_VLENGTH2_LSB, 0x00);
	ths8200_ग_लिखो(sd, THS8200_DTG2_VLENGTH2_MSB_VDLY2_MSB, 0x07);
	ths8200_ग_लिखो(sd, THS8200_DTG2_VDLY2_LSB, 0xff);

	/* Internal delay factors to synchronize the sync pulses and the data */
	/* Experimental values delays (hor 0, ver 0) */
	ths8200_ग_लिखो(sd, THS8200_DTG2_HS_IN_DLY_MSB, 0);
	ths8200_ग_लिखो(sd, THS8200_DTG2_HS_IN_DLY_LSB, 0);
	ths8200_ग_लिखो(sd, THS8200_DTG2_VS_IN_DLY_MSB, 0);
	ths8200_ग_लिखो(sd, THS8200_DTG2_VS_IN_DLY_LSB, 0);

	/* Polarity of received and transmitted sync संकेतs */
	अगर (bt->polarities & V4L2_DV_HSYNC_POS_POL) अणु
		polarity |= 0x01; /* HS_IN */
		polarity |= 0x08; /* HS_OUT */
	पूर्ण
	अगर (bt->polarities & V4L2_DV_VSYNC_POS_POL) अणु
		polarity |= 0x02; /* VS_IN */
		polarity |= 0x10; /* VS_OUT */
	पूर्ण

	/* RGB mode, no embedded timings */
	/* Timing of video input bus is derived from HS, VS, and FID dedicated
	 * inमाला_दो
	 */
	ths8200_ग_लिखो(sd, THS8200_DTG2_CNTL, 0x44 | polarity);

	/* leave reset */
	ths8200_s_stream(sd, true);

	v4l2_dbg(1, debug, sd, "%s: frame %dx%d, polarity %d\n"
		 "horizontal: front porch %d, back porch %d, sync %d\n"
		 "vertical: sync %d\n", __func__, htotal(bt), vtotal(bt),
		 polarity, bt->hfrontporch, bt->hbackporch,
		 bt->hsync, bt->vsync);
पूर्ण

अटल पूर्णांक ths8200_s_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा ths8200_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (!v4l2_valid_dv_timings(timings, &ths8200_timings_cap,
				शून्य, शून्य))
		वापस -EINVAL;

	अगर (!v4l2_find_dv_timings_cap(timings, &ths8200_timings_cap, 10,
				शून्य, शून्य)) अणु
		v4l2_dbg(1, debug, sd, "Unsupported format\n");
		वापस -EINVAL;
	पूर्ण

	timings->bt.flags &= ~V4L2_DV_FL_REDUCED_FPS;

	/* save timings */
	state->dv_timings = *timings;

	ths8200_setup(sd, &timings->bt);

	वापस 0;
पूर्ण

अटल पूर्णांक ths8200_g_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा ths8200_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	*timings = state->dv_timings;

	वापस 0;
पूर्ण

अटल पूर्णांक ths8200_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->pad != 0)
		वापस -EINVAL;

	वापस v4l2_क्रमागत_dv_timings_cap(timings, &ths8200_timings_cap,
			शून्य, शून्य);
पूर्ण

अटल पूर्णांक ths8200_dv_timings_cap(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (cap->pad != 0)
		वापस -EINVAL;

	*cap = ths8200_timings_cap;
	वापस 0;
पूर्ण

/* Specअगरic video subप्रणाली operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_video_ops ths8200_video_ops = अणु
	.s_stream = ths8200_s_stream,
	.s_dv_timings = ths8200_s_dv_timings,
	.g_dv_timings = ths8200_g_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ths8200_pad_ops = अणु
	.क्रमागत_dv_timings = ths8200_क्रमागत_dv_timings,
	.dv_timings_cap = ths8200_dv_timings_cap,
पूर्ण;

/* V4L2 top level operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_ops ths8200_ops = अणु
	.core  = &ths8200_core_ops,
	.video = &ths8200_video_ops,
	.pad = &ths8200_pad_ops,
पूर्ण;

अटल पूर्णांक ths8200_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ths8200_state *state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक error;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &ths8200_ops);

	state->chip_version = ths8200_पढ़ो(sd, THS8200_VERSION);
	v4l2_dbg(1, debug, sd, "chip version 0x%x\n", state->chip_version);

	ths8200_core_init(sd);

	error = v4l2_async_रेजिस्टर_subdev(&state->sd);
	अगर (error)
		वापस error;

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
		  client->addr << 1, client->adapter->name);

	वापस 0;
पूर्ण

अटल पूर्णांक ths8200_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ths8200_state *decoder = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s removed @ 0x%x (%s)\n", client->name,
		 client->addr << 1, client->adapter->name);

	ths8200_s_घातer(sd, false);
	v4l2_async_unरेजिस्टर_subdev(&decoder->sd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ths8200_id[] = अणु
	अणु "ths8200", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ths8200_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ths8200_of_match[] = अणु
	अणु .compatible = "ti,ths8200", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ths8200_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ths8200_driver = अणु
	.driver = अणु
		.name = "ths8200",
		.of_match_table = of_match_ptr(ths8200_of_match),
	पूर्ण,
	.probe_new = ths8200_probe,
	.हटाओ = ths8200_हटाओ,
	.id_table = ths8200_id,
पूर्ण;

module_i2c_driver(ths8200_driver);
