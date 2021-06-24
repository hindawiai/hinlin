<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices AD9389B/AD9889B video encoder driver
 *
 * Copyright 2012 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

/*
 * References (c = chapter, p = page):
 * REF_01 - Analog Devices, Programming Guide, AD9889B/AD9389B,
 * HDMI Transitter, Rev. A, October 2010
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/ad9389b.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

MODULE_DESCRIPTION("Analog Devices AD9389B/AD9889B video encoder driver");
MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com>");
MODULE_AUTHOR("Martin Bugge <marbugge@cisco.com>");
MODULE_LICENSE("GPL");

#घोषणा MASK_AD9389B_EDID_RDY_INT   0x04
#घोषणा MASK_AD9389B_MSEN_INT       0x40
#घोषणा MASK_AD9389B_HPD_INT        0x80

#घोषणा MASK_AD9389B_HPD_DETECT     0x40
#घोषणा MASK_AD9389B_MSEN_DETECT    0x20
#घोषणा MASK_AD9389B_EDID_RDY       0x10

#घोषणा EDID_MAX_RETRIES (8)
#घोषणा EDID_DELAY 250
#घोषणा EDID_MAX_SEGM 8

/*
**********************************************************************
*
*  Arrays with configuration parameters क्रम the AD9389B
*
**********************************************************************
*/

काष्ठा ad9389b_state_edid अणु
	/* total number of blocks */
	u32 blocks;
	/* Number of segments पढ़ो */
	u32 segments;
	u8 data[EDID_MAX_SEGM * 256];
	/* Number of EDID पढ़ो retries left */
	अचिन्हित पढ़ो_retries;
पूर्ण;

काष्ठा ad9389b_state अणु
	काष्ठा ad9389b_platक्रमm_data pdata;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler hdl;
	पूर्णांक chip_revision;
	/* Is the ad9389b घातered on? */
	bool घातer_on;
	/* Did we receive hotplug and rx-sense संकेतs? */
	bool have_monitor;
	/* timings from s_dv_timings */
	काष्ठा v4l2_dv_timings dv_timings;
	/* controls */
	काष्ठा v4l2_ctrl *hdmi_mode_ctrl;
	काष्ठा v4l2_ctrl *hotplug_ctrl;
	काष्ठा v4l2_ctrl *rx_sense_ctrl;
	काष्ठा v4l2_ctrl *have_edid0_ctrl;
	काष्ठा v4l2_ctrl *rgb_quantization_range_ctrl;
	काष्ठा i2c_client *edid_i2c_client;
	काष्ठा ad9389b_state_edid edid;
	/* Running counter of the number of detected EDIDs (क्रम debugging) */
	अचिन्हित edid_detect_counter;
	काष्ठा delayed_work edid_handler; /* work entry */
पूर्ण;

अटल व्योम ad9389b_check_monitor_present_status(काष्ठा v4l2_subdev *sd);
अटल bool ad9389b_check_edid_status(काष्ठा v4l2_subdev *sd);
अटल व्योम ad9389b_setup(काष्ठा v4l2_subdev *sd);
अटल पूर्णांक ad9389b_s_i2s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq);
अटल पूर्णांक ad9389b_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq);

अटल अंतरभूत काष्ठा ad9389b_state *get_ad9389b_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ad9389b_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ad9389b_state, hdl)->sd;
पूर्ण

/* ------------------------ I2C ----------------------------------------------- */

अटल पूर्णांक ad9389b_rd(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक ad9389b_wr(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	v4l2_err(sd, "%s: failed reg 0x%x, val 0x%x\n", __func__, reg, val);
	वापस ret;
पूर्ण

/* To set specअगरic bits in the रेजिस्टर, a clear-mask is given (to be AND-ed),
   and then the value-mask (to be OR-ed). */
अटल अंतरभूत व्योम ad9389b_wr_and_or(काष्ठा v4l2_subdev *sd, u8 reg,
				     u8 clr_mask, u8 val_mask)
अणु
	ad9389b_wr(sd, reg, (ad9389b_rd(sd, reg) & clr_mask) | val_mask);
पूर्ण

अटल व्योम ad9389b_edid_rd(काष्ठा v4l2_subdev *sd, u16 len, u8 *buf)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	पूर्णांक i;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	क्रम (i = 0; i < len; i++)
		buf[i] = i2c_smbus_पढ़ो_byte_data(state->edid_i2c_client, i);
पूर्ण

अटल अंतरभूत bool ad9389b_have_hotplug(काष्ठा v4l2_subdev *sd)
अणु
	वापस ad9389b_rd(sd, 0x42) & MASK_AD9389B_HPD_DETECT;
पूर्ण

अटल अंतरभूत bool ad9389b_have_rx_sense(काष्ठा v4l2_subdev *sd)
अणु
	वापस ad9389b_rd(sd, 0x42) & MASK_AD9389B_MSEN_DETECT;
पूर्ण

अटल व्योम ad9389b_csc_conversion_mode(काष्ठा v4l2_subdev *sd, u8 mode)
अणु
	ad9389b_wr_and_or(sd, 0x17, 0xe7, (mode & 0x3)<<3);
	ad9389b_wr_and_or(sd, 0x18, 0x9f, (mode & 0x3)<<5);
पूर्ण

अटल व्योम ad9389b_csc_coeff(काष्ठा v4l2_subdev *sd,
			      u16 A1, u16 A2, u16 A3, u16 A4,
			      u16 B1, u16 B2, u16 B3, u16 B4,
			      u16 C1, u16 C2, u16 C3, u16 C4)
अणु
	/* A */
	ad9389b_wr_and_or(sd, 0x18, 0xe0, A1>>8);
	ad9389b_wr(sd, 0x19, A1);
	ad9389b_wr_and_or(sd, 0x1A, 0xe0, A2>>8);
	ad9389b_wr(sd, 0x1B, A2);
	ad9389b_wr_and_or(sd, 0x1c, 0xe0, A3>>8);
	ad9389b_wr(sd, 0x1d, A3);
	ad9389b_wr_and_or(sd, 0x1e, 0xe0, A4>>8);
	ad9389b_wr(sd, 0x1f, A4);

	/* B */
	ad9389b_wr_and_or(sd, 0x20, 0xe0, B1>>8);
	ad9389b_wr(sd, 0x21, B1);
	ad9389b_wr_and_or(sd, 0x22, 0xe0, B2>>8);
	ad9389b_wr(sd, 0x23, B2);
	ad9389b_wr_and_or(sd, 0x24, 0xe0, B3>>8);
	ad9389b_wr(sd, 0x25, B3);
	ad9389b_wr_and_or(sd, 0x26, 0xe0, B4>>8);
	ad9389b_wr(sd, 0x27, B4);

	/* C */
	ad9389b_wr_and_or(sd, 0x28, 0xe0, C1>>8);
	ad9389b_wr(sd, 0x29, C1);
	ad9389b_wr_and_or(sd, 0x2A, 0xe0, C2>>8);
	ad9389b_wr(sd, 0x2B, C2);
	ad9389b_wr_and_or(sd, 0x2C, 0xe0, C3>>8);
	ad9389b_wr(sd, 0x2D, C3);
	ad9389b_wr_and_or(sd, 0x2E, 0xe0, C4>>8);
	ad9389b_wr(sd, 0x2F, C4);
पूर्ण

अटल व्योम ad9389b_csc_rgb_full2limit(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	अगर (enable) अणु
		u8 csc_mode = 0;

		ad9389b_csc_conversion_mode(sd, csc_mode);
		ad9389b_csc_coeff(sd,
				  4096-564, 0, 0, 256,
				  0, 4096-564, 0, 256,
				  0, 0, 4096-564, 256);
		/* enable CSC */
		ad9389b_wr_and_or(sd, 0x3b, 0xfe, 0x1);
		/* AVI infoframe: Limited range RGB (16-235) */
		ad9389b_wr_and_or(sd, 0xcd, 0xf9, 0x02);
	पूर्ण अन्यथा अणु
		/* disable CSC */
		ad9389b_wr_and_or(sd, 0x3b, 0xfe, 0x0);
		/* AVI infoframe: Full range RGB (0-255) */
		ad9389b_wr_and_or(sd, 0xcd, 0xf9, 0x04);
	पूर्ण
पूर्ण

अटल व्योम ad9389b_set_IT_content_AVI_InfoFrame(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	अगर (state->dv_timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
		/* CE क्रमmat, not IT  */
		ad9389b_wr_and_or(sd, 0xcd, 0xbf, 0x00);
	पूर्ण अन्यथा अणु
		/* IT क्रमmat */
		ad9389b_wr_and_or(sd, 0xcd, 0xbf, 0x40);
	पूर्ण
पूर्ण

अटल पूर्णांक ad9389b_set_rgb_quantization_mode(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	चयन (ctrl->val) अणु
	हाल V4L2_DV_RGB_RANGE_AUTO:
		/* स्वतःmatic */
		अगर (state->dv_timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
			/* CE क्रमmat, RGB limited range (16-235) */
			ad9389b_csc_rgb_full2limit(sd, true);
		पूर्ण अन्यथा अणु
			/* not CE क्रमmat, RGB full range (0-255) */
			ad9389b_csc_rgb_full2limit(sd, false);
		पूर्ण
		अवरोध;
	हाल V4L2_DV_RGB_RANGE_LIMITED:
		/* RGB limited range (16-235) */
		ad9389b_csc_rgb_full2limit(sd, true);
		अवरोध;
	हाल V4L2_DV_RGB_RANGE_FULL:
		/* RGB full range (0-255) */
		ad9389b_csc_rgb_full2limit(sd, false);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ad9389b_set_manual_pll_gear(काष्ठा v4l2_subdev *sd, u32 pixelघड़ी)
अणु
	u8 gear;

	/* Workaround क्रम TMDS PLL problem
	 * The TMDS PLL in AD9389b change gear when the chip is heated above a
	 * certain temperature. The output is disabled when the PLL change gear
	 * so the monitor has to lock on the संकेत again. A workaround क्रम
	 * this is to use the manual PLL gears. This is a solution from Analog
	 * Devices that is not करोcumented in the datasheets.
	 * 0x98 [7] = enable manual gearing. 0x98 [6:4] = gear
	 *
	 * The pixel frequency ranges are based on पढ़ोout of the gear the
	 * स्वतःmatic gearing selects क्रम dअगरferent pixel घड़ीs
	 * (पढ़ो from 0x9e [3:1]).
	 */

	अगर (pixelघड़ी > 140000000)
		gear = 0xc0; /* 4th gear */
	अन्यथा अगर (pixelघड़ी > 117000000)
		gear = 0xb0; /* 3rd gear */
	अन्यथा अगर (pixelघड़ी > 87000000)
		gear = 0xa0; /* 2nd gear */
	अन्यथा अगर (pixelघड़ी > 60000000)
		gear = 0x90; /* 1st gear */
	अन्यथा
		gear = 0x80; /* 0th gear */

	ad9389b_wr_and_or(sd, 0x98, 0x0f, gear);
पूर्ण

/* ------------------------------ CTRL OPS ------------------------------ */

अटल पूर्णांक ad9389b_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	v4l2_dbg(1, debug, sd,
		 "%s: ctrl id: %d, ctrl->val %d\n", __func__, ctrl->id, ctrl->val);

	अगर (state->hdmi_mode_ctrl == ctrl) अणु
		/* Set HDMI or DVI-D */
		ad9389b_wr_and_or(sd, 0xaf, 0xfd,
				  ctrl->val == V4L2_DV_TX_MODE_HDMI ? 0x02 : 0x00);
		वापस 0;
	पूर्ण
	अगर (state->rgb_quantization_range_ctrl == ctrl)
		वापस ad9389b_set_rgb_quantization_mode(sd, ctrl);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ad9389b_ctrl_ops = अणु
	.s_ctrl = ad9389b_s_ctrl,
पूर्ण;

/* ---------------------------- CORE OPS ------------------------------------------- */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ad9389b_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = ad9389b_rd(sd, reg->reg & 0xff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ad9389b_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	ad9389b_wr(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ad9389b_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	काष्ठा ad9389b_state_edid *edid = &state->edid;

	अटल स्थिर अक्षर * स्थिर states[] = अणु
		"in reset",
		"reading EDID",
		"idle",
		"initializing HDCP",
		"HDCP enabled",
		"initializing HDCP repeater",
		"6", "7", "8", "9", "A", "B", "C", "D", "E", "F"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर errors[] = अणु
		"no error",
		"bad receiver BKSV",
		"Ri mismatch",
		"Pj mismatch",
		"i2c error",
		"timed out",
		"max repeater cascade exceeded",
		"hash check failed",
		"too many devices",
		"9", "A", "B", "C", "D", "E", "F"
	पूर्ण;

	u8 manual_gear;

	v4l2_info(sd, "chip revision %d\n", state->chip_revision);
	v4l2_info(sd, "power %s\n", state->घातer_on ? "on" : "off");
	v4l2_info(sd, "%s hotplug, %s Rx Sense, %s EDID (%d block(s))\n",
		  (ad9389b_rd(sd, 0x42) & MASK_AD9389B_HPD_DETECT) ?
		  "detected" : "no",
		  (ad9389b_rd(sd, 0x42) & MASK_AD9389B_MSEN_DETECT) ?
		  "detected" : "no",
		  edid->segments ? "found" : "no", edid->blocks);
	v4l2_info(sd, "%s output %s\n",
		  (ad9389b_rd(sd, 0xaf) & 0x02) ?
		  "HDMI" : "DVI-D",
		  (ad9389b_rd(sd, 0xa1) & 0x3c) ?
		  "disabled" : "enabled");
	v4l2_info(sd, "ad9389b: %s\n", (ad9389b_rd(sd, 0xb8) & 0x40) ?
		  "encrypted" : "no encryption");
	v4l2_info(sd, "state: %s, error: %s, detect count: %u, msk/irq: %02x/%02x\n",
		  states[ad9389b_rd(sd, 0xc8) & 0xf],
		  errors[ad9389b_rd(sd, 0xc8) >> 4],
		  state->edid_detect_counter,
		  ad9389b_rd(sd, 0x94), ad9389b_rd(sd, 0x96));
	manual_gear = ad9389b_rd(sd, 0x98) & 0x80;
	v4l2_info(sd, "ad9389b: RGB quantization: %s range\n",
		  ad9389b_rd(sd, 0x3b) & 0x01 ? "limited" : "full");
	v4l2_info(sd, "ad9389b: %s gear %d\n",
		  manual_gear ? "manual" : "automatic",
		  manual_gear ? ((ad9389b_rd(sd, 0x98) & 0x70) >> 4) :
		  ((ad9389b_rd(sd, 0x9e) & 0x0e) >> 1));
	अगर (ad9389b_rd(sd, 0xaf) & 0x02) अणु
		/* HDMI only */
		u8 manual_cts = ad9389b_rd(sd, 0x0a) & 0x80;
		u32 N = (ad9389b_rd(sd, 0x01) & 0xf) << 16 |
			ad9389b_rd(sd, 0x02) << 8 |
			ad9389b_rd(sd, 0x03);
		u8 vic_detect = ad9389b_rd(sd, 0x3e) >> 2;
		u8 vic_sent = ad9389b_rd(sd, 0x3d) & 0x3f;
		u32 CTS;

		अगर (manual_cts)
			CTS = (ad9389b_rd(sd, 0x07) & 0xf) << 16 |
			      ad9389b_rd(sd, 0x08) << 8 |
			      ad9389b_rd(sd, 0x09);
		अन्यथा
			CTS = (ad9389b_rd(sd, 0x04) & 0xf) << 16 |
			      ad9389b_rd(sd, 0x05) << 8 |
			      ad9389b_rd(sd, 0x06);
		N = (ad9389b_rd(sd, 0x01) & 0xf) << 16 |
		    ad9389b_rd(sd, 0x02) << 8 |
		    ad9389b_rd(sd, 0x03);

		v4l2_info(sd, "ad9389b: CTS %s mode: N %d, CTS %d\n",
			  manual_cts ? "manual" : "automatic", N, CTS);

		v4l2_info(sd, "ad9389b: VIC: detected %d, sent %d\n",
			  vic_detect, vic_sent);
	पूर्ण
	अगर (state->dv_timings.type == V4L2_DV_BT_656_1120)
		v4l2_prपूर्णांक_dv_timings(sd->name, "timings: ",
				&state->dv_timings, false);
	अन्यथा
		v4l2_info(sd, "no timings set\n");
	वापस 0;
पूर्ण

/* Power up/करोwn ad9389b */
अटल पूर्णांक ad9389b_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	काष्ठा ad9389b_platक्रमm_data *pdata = &state->pdata;
	स्थिर पूर्णांक retries = 20;
	पूर्णांक i;

	v4l2_dbg(1, debug, sd, "%s: power %s\n", __func__, on ? "on" : "off");

	state->घातer_on = on;

	अगर (!on) अणु
		/* Power करोwn */
		ad9389b_wr_and_or(sd, 0x41, 0xbf, 0x40);
		वापस true;
	पूर्ण

	/* Power up */
	/* The ad9389b करोes not always come up immediately.
	   Retry multiple बार. */
	क्रम (i = 0; i < retries; i++) अणु
		ad9389b_wr_and_or(sd, 0x41, 0xbf, 0x0);
		अगर ((ad9389b_rd(sd, 0x41) & 0x40) == 0)
			अवरोध;
		ad9389b_wr_and_or(sd, 0x41, 0xbf, 0x40);
		msleep(10);
	पूर्ण
	अगर (i == retries) अणु
		v4l2_dbg(1, debug, sd, "failed to powerup the ad9389b\n");
		ad9389b_s_घातer(sd, 0);
		वापस false;
	पूर्ण
	अगर (i > 1)
		v4l2_dbg(1, debug, sd,
			 "needed %d retries to powerup the ad9389b\n", i);

	/* Select chip: AD9389B */
	ad9389b_wr_and_or(sd, 0xba, 0xef, 0x10);

	/* Reserved रेजिस्टरs that must be set according to REF_01 p. 11*/
	ad9389b_wr_and_or(sd, 0x98, 0xf0, 0x07);
	ad9389b_wr(sd, 0x9c, 0x38);
	ad9389b_wr_and_or(sd, 0x9d, 0xfc, 0x01);

	/* Dअगरferential output drive strength */
	अगर (pdata->dअगरf_data_drive_strength > 0)
		ad9389b_wr(sd, 0xa2, pdata->dअगरf_data_drive_strength);
	अन्यथा
		ad9389b_wr(sd, 0xa2, 0x87);

	अगर (pdata->dअगरf_clk_drive_strength > 0)
		ad9389b_wr(sd, 0xa3, pdata->dअगरf_clk_drive_strength);
	अन्यथा
		ad9389b_wr(sd, 0xa3, 0x87);

	ad9389b_wr(sd, 0x0a, 0x01);
	ad9389b_wr(sd, 0xbb, 0xff);

	/* Set number of attempts to पढ़ो the EDID */
	ad9389b_wr(sd, 0xc9, 0xf);
	वापस true;
पूर्ण

/* Enable पूर्णांकerrupts */
अटल व्योम ad9389b_set_isr(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	u8 irqs = MASK_AD9389B_HPD_INT | MASK_AD9389B_MSEN_INT;
	u8 irqs_rd;
	पूर्णांक retries = 100;

	/* The datasheet says that the EDID पढ़ोy पूर्णांकerrupt should be
	   disabled अगर there is no hotplug. */
	अगर (!enable)
		irqs = 0;
	अन्यथा अगर (ad9389b_have_hotplug(sd))
		irqs |= MASK_AD9389B_EDID_RDY_INT;

	/*
	 * This i2c ग_लिखो can fail (approx. 1 in 1000 ग_लिखोs). But it
	 * is essential that this रेजिस्टर is correct, so retry it
	 * multiple बार.
	 *
	 * Note that the i2c ग_लिखो करोes not report an error, but the पढ़ोback
	 * clearly shows the wrong value.
	 */
	करो अणु
		ad9389b_wr(sd, 0x94, irqs);
		irqs_rd = ad9389b_rd(sd, 0x94);
	पूर्ण जबतक (retries-- && irqs_rd != irqs);

	अगर (irqs_rd != irqs)
		v4l2_err(sd, "Could not set interrupts: hw failure?\n");
पूर्ण

/* Interrupt handler */
अटल पूर्णांक ad9389b_isr(काष्ठा v4l2_subdev *sd, u32 status, bool *handled)
अणु
	u8 irq_status;

	/* disable पूर्णांकerrupts to prevent a race condition */
	ad9389b_set_isr(sd, false);
	irq_status = ad9389b_rd(sd, 0x96);
	/* clear detected पूर्णांकerrupts */
	ad9389b_wr(sd, 0x96, irq_status);
	/* enable पूर्णांकerrupts */
	ad9389b_set_isr(sd, true);

	v4l2_dbg(1, debug, sd, "%s: irq_status 0x%x\n", __func__, irq_status);

	अगर (irq_status & (MASK_AD9389B_HPD_INT))
		ad9389b_check_monitor_present_status(sd);
	अगर (irq_status & MASK_AD9389B_EDID_RDY_INT)
		ad9389b_check_edid_status(sd);

	*handled = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ad9389b_core_ops = अणु
	.log_status = ad9389b_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = ad9389b_g_रेजिस्टर,
	.s_रेजिस्टर = ad9389b_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer = ad9389b_s_घातer,
	.पूर्णांकerrupt_service_routine = ad9389b_isr,
पूर्ण;

/* ------------------------------ VIDEO OPS ------------------------------ */

/* Enable/disable ad9389b output */
अटल पूर्णांक ad9389b_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	v4l2_dbg(1, debug, sd, "%s: %sable\n", __func__, (enable ? "en" : "dis"));

	ad9389b_wr_and_or(sd, 0xa1, ~0x3c, (enable ? 0 : 0x3c));
	अगर (enable) अणु
		ad9389b_check_monitor_present_status(sd);
	पूर्ण अन्यथा अणु
		ad9389b_s_घातer(sd, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_dv_timings_cap ad9389b_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1200, 25000000, 170000000,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_REDUCED_BLANKING |
		V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

अटल पूर्णांक ad9389b_s_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	/* quick sanity check */
	अगर (!v4l2_valid_dv_timings(timings, &ad9389b_timings_cap, शून्य, शून्य))
		वापस -EINVAL;

	/* Fill the optional fields .standards and .flags in काष्ठा v4l2_dv_timings
	   अगर the क्रमmat is one of the CEA or DMT timings. */
	v4l2_find_dv_timings_cap(timings, &ad9389b_timings_cap, 0, शून्य, शून्य);

	timings->bt.flags &= ~V4L2_DV_FL_REDUCED_FPS;

	/* save timings */
	state->dv_timings = *timings;

	/* update quantization range based on new dv_timings */
	ad9389b_set_rgb_quantization_mode(sd, state->rgb_quantization_range_ctrl);

	/* update PLL gear based on new dv_timings */
	अगर (state->pdata.पंचांगds_pll_gear == AD9389B_TMDS_PLL_GEAR_SEMI_AUTOMATIC)
		ad9389b_set_manual_pll_gear(sd, (u32)timings->bt.pixelघड़ी);

	/* update AVI infoframe */
	ad9389b_set_IT_content_AVI_InfoFrame(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक ad9389b_g_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (!timings)
		वापस -EINVAL;

	*timings = state->dv_timings;

	वापस 0;
पूर्ण

अटल पूर्णांक ad9389b_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->pad != 0)
		वापस -EINVAL;

	वापस v4l2_क्रमागत_dv_timings_cap(timings, &ad9389b_timings_cap,
			शून्य, शून्य);
पूर्ण

अटल पूर्णांक ad9389b_dv_timings_cap(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (cap->pad != 0)
		वापस -EINVAL;

	*cap = ad9389b_timings_cap;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ad9389b_video_ops = अणु
	.s_stream = ad9389b_s_stream,
	.s_dv_timings = ad9389b_s_dv_timings,
	.g_dv_timings = ad9389b_g_dv_timings,
पूर्ण;

/* ------------------------------ PAD OPS ------------------------------ */

अटल पूर्णांक ad9389b_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	अगर (edid->pad != 0)
		वापस -EINVAL;
	अगर (edid->blocks == 0 || edid->blocks > 256)
		वापस -EINVAL;
	अगर (!state->edid.segments) अणु
		v4l2_dbg(1, debug, sd, "EDID segment 0 not found\n");
		वापस -ENODATA;
	पूर्ण
	अगर (edid->start_block >= state->edid.segments * 2)
		वापस -E2BIG;
	अगर (edid->blocks + edid->start_block >= state->edid.segments * 2)
		edid->blocks = state->edid.segments * 2 - edid->start_block;
	स_नकल(edid->edid, &state->edid.data[edid->start_block * 128],
	       128 * edid->blocks);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ad9389b_pad_ops = अणु
	.get_edid = ad9389b_get_edid,
	.क्रमागत_dv_timings = ad9389b_क्रमागत_dv_timings,
	.dv_timings_cap = ad9389b_dv_timings_cap,
पूर्ण;

/* ------------------------------ AUDIO OPS ------------------------------ */

अटल पूर्णांक ad9389b_s_audio_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	v4l2_dbg(1, debug, sd, "%s: %sable\n", __func__, (enable ? "en" : "dis"));

	अगर (enable)
		ad9389b_wr_and_or(sd, 0x45, 0x3f, 0x80);
	अन्यथा
		ad9389b_wr_and_or(sd, 0x45, 0x3f, 0x40);

	वापस 0;
पूर्ण

अटल पूर्णांक ad9389b_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	u32 N;

	चयन (freq) अणु
	हाल 32000:  N = 4096;  अवरोध;
	हाल 44100:  N = 6272;  अवरोध;
	हाल 48000:  N = 6144;  अवरोध;
	हाल 88200:  N = 12544; अवरोध;
	हाल 96000:  N = 12288; अवरोध;
	हाल 176400: N = 25088; अवरोध;
	हाल 192000: N = 24576; अवरोध;
	शेष:
	     वापस -EINVAL;
	पूर्ण

	/* Set N (used with CTS to regenerate the audio घड़ी) */
	ad9389b_wr(sd, 0x01, (N >> 16) & 0xf);
	ad9389b_wr(sd, 0x02, (N >> 8) & 0xff);
	ad9389b_wr(sd, 0x03, N & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक ad9389b_s_i2s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	u32 i2s_sf;

	चयन (freq) अणु
	हाल 32000:  i2s_sf = 0x30; अवरोध;
	हाल 44100:  i2s_sf = 0x00; अवरोध;
	हाल 48000:  i2s_sf = 0x20; अवरोध;
	हाल 88200:  i2s_sf = 0x80; अवरोध;
	हाल 96000:  i2s_sf = 0xa0; अवरोध;
	हाल 176400: i2s_sf = 0xc0; अवरोध;
	हाल 192000: i2s_sf = 0xe0; अवरोध;
	शेष:
	     वापस -EINVAL;
	पूर्ण

	/* Set sampling frequency क्रम I2S audio to 48 kHz */
	ad9389b_wr_and_or(sd, 0x15, 0xf, i2s_sf);

	वापस 0;
पूर्ण

अटल पूर्णांक ad9389b_s_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output, u32 config)
अणु
	/* TODO based on input/output/config */
	/* TODO See datasheet "Programmers guide" p. 39-40 */

	/* Only 2 channels in use क्रम application */
	ad9389b_wr_and_or(sd, 0x50, 0x1f, 0x20);
	/* Speaker mapping */
	ad9389b_wr(sd, 0x51, 0x00);

	/* TODO Where should this be placed? */
	/* 16 bit audio word length */
	ad9389b_wr_and_or(sd, 0x14, 0xf0, 0x02);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_audio_ops ad9389b_audio_ops = अणु
	.s_stream = ad9389b_s_audio_stream,
	.s_घड़ी_freq = ad9389b_s_घड़ी_freq,
	.s_i2s_घड़ी_freq = ad9389b_s_i2s_घड़ी_freq,
	.s_routing = ad9389b_s_routing,
पूर्ण;

/* --------------------- SUBDEV OPS --------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_ops ad9389b_ops = अणु
	.core  = &ad9389b_core_ops,
	.video = &ad9389b_video_ops,
	.audio = &ad9389b_audio_ops,
	.pad = &ad9389b_pad_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */
अटल व्योम ad9389b_dbg_dump_edid(पूर्णांक lvl, पूर्णांक debug, काष्ठा v4l2_subdev *sd,
				  पूर्णांक segment, u8 *buf)
अणु
	पूर्णांक i, j;

	अगर (debug < lvl)
		वापस;

	v4l2_dbg(lvl, debug, sd, "edid segment %d\n", segment);
	क्रम (i = 0; i < 256; i += 16) अणु
		u8 b[128];
		u8 *bp = b;

		अगर (i == 128)
			v4l2_dbg(lvl, debug, sd, "\n");
		क्रम (j = i; j < i + 16; j++) अणु
			प्र_लिखो(bp, "0x%02x, ", buf[j]);
			bp += 6;
		पूर्ण
		bp[0] = '\0';
		v4l2_dbg(lvl, debug, sd, "%s\n", b);
	पूर्ण
पूर्ण

अटल व्योम ad9389b_edid_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा ad9389b_state *state =
		container_of(dwork, काष्ठा ad9389b_state, edid_handler);
	काष्ठा v4l2_subdev *sd = &state->sd;
	काष्ठा ad9389b_edid_detect ed;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (ad9389b_check_edid_status(sd)) अणु
		/* Return अगर we received the EDID. */
		वापस;
	पूर्ण

	अगर (ad9389b_have_hotplug(sd)) अणु
		/* We must retry पढ़ोing the EDID several बार, it is possible
		 * that initially the EDID couldn't be पढ़ो due to i2c errors
		 * (DVI connectors are particularly prone to this problem). */
		अगर (state->edid.पढ़ो_retries) अणु
			state->edid.पढ़ो_retries--;
			v4l2_dbg(1, debug, sd, "%s: edid read failed\n", __func__);
			ad9389b_s_घातer(sd, false);
			ad9389b_s_घातer(sd, true);
			schedule_delayed_work(&state->edid_handler, EDID_DELAY);
			वापस;
		पूर्ण
	पूर्ण

	/* We failed to पढ़ो the EDID, so send an event क्रम this. */
	ed.present = false;
	ed.segment = ad9389b_rd(sd, 0xc4);
	v4l2_subdev_notअगरy(sd, AD9389B_EDID_DETECT, (व्योम *)&ed);
	v4l2_dbg(1, debug, sd, "%s: no edid found\n", __func__);
पूर्ण

अटल व्योम ad9389b_audio_setup(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	ad9389b_s_i2s_घड़ी_freq(sd, 48000);
	ad9389b_s_घड़ी_freq(sd, 48000);
	ad9389b_s_routing(sd, 0, 0, 0);
पूर्ण

/* Initial setup of AD9389b */

/* Configure hdmi transmitter. */
अटल व्योम ad9389b_setup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	/* Input क्रमmat: RGB 4:4:4 */
	ad9389b_wr_and_or(sd, 0x15, 0xf1, 0x0);
	/* Output क्रमmat: RGB 4:4:4 */
	ad9389b_wr_and_or(sd, 0x16, 0x3f, 0x0);
	/* 1st order पूर्णांकerpolation 4:2:2 -> 4:4:4 up conversion,
	   Aspect ratio: 16:9 */
	ad9389b_wr_and_or(sd, 0x17, 0xf9, 0x06);
	/* Output क्रमmat: RGB 4:4:4, Active Format Inक्रमmation is valid. */
	ad9389b_wr_and_or(sd, 0x45, 0xc7, 0x08);
	/* Underscanned */
	ad9389b_wr_and_or(sd, 0x46, 0x3f, 0x80);
	/* Setup video क्रमmat */
	ad9389b_wr(sd, 0x3c, 0x0);
	/* Active क्रमmat aspect ratio: same as picure. */
	ad9389b_wr(sd, 0x47, 0x80);
	/* No encryption */
	ad9389b_wr_and_or(sd, 0xaf, 0xef, 0x0);
	/* Positive clk edge capture क्रम input video घड़ी */
	ad9389b_wr_and_or(sd, 0xba, 0x1f, 0x60);

	ad9389b_audio_setup(sd);

	v4l2_ctrl_handler_setup(&state->hdl);

	ad9389b_set_IT_content_AVI_InfoFrame(sd);
पूर्ण

अटल व्योम ad9389b_notअगरy_monitor_detect(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_monitor_detect mdt;
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	mdt.present = state->have_monitor;
	v4l2_subdev_notअगरy(sd, AD9389B_MONITOR_DETECT, (व्योम *)&mdt);
पूर्ण

अटल व्योम ad9389b_update_monitor_present_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	/* पढ़ो hotplug and rx-sense state */
	u8 status = ad9389b_rd(sd, 0x42);

	v4l2_dbg(1, debug, sd, "%s: status: 0x%x%s%s\n",
		 __func__,
		 status,
		 status & MASK_AD9389B_HPD_DETECT ? ", hotplug" : "",
		 status & MASK_AD9389B_MSEN_DETECT ? ", rx-sense" : "");

	अगर (status & MASK_AD9389B_HPD_DETECT) अणु
		v4l2_dbg(1, debug, sd, "%s: hotplug detected\n", __func__);
		state->have_monitor = true;
		अगर (!ad9389b_s_घातer(sd, true)) अणु
			v4l2_dbg(1, debug, sd,
				 "%s: monitor detected, powerup failed\n", __func__);
			वापस;
		पूर्ण
		ad9389b_setup(sd);
		ad9389b_notअगरy_monitor_detect(sd);
		state->edid.पढ़ो_retries = EDID_MAX_RETRIES;
		schedule_delayed_work(&state->edid_handler, EDID_DELAY);
	पूर्ण अन्यथा अगर (!(status & MASK_AD9389B_HPD_DETECT)) अणु
		v4l2_dbg(1, debug, sd, "%s: hotplug not detected\n", __func__);
		state->have_monitor = false;
		ad9389b_notअगरy_monitor_detect(sd);
		ad9389b_s_घातer(sd, false);
		स_रखो(&state->edid, 0, माप(काष्ठा ad9389b_state_edid));
	पूर्ण

	/* update पढ़ो only ctrls */
	v4l2_ctrl_s_ctrl(state->hotplug_ctrl, ad9389b_have_hotplug(sd) ? 0x1 : 0x0);
	v4l2_ctrl_s_ctrl(state->rx_sense_ctrl, ad9389b_have_rx_sense(sd) ? 0x1 : 0x0);
	v4l2_ctrl_s_ctrl(state->have_edid0_ctrl, state->edid.segments ? 0x1 : 0x0);

	/* update with setting from ctrls */
	ad9389b_s_ctrl(state->rgb_quantization_range_ctrl);
	ad9389b_s_ctrl(state->hdmi_mode_ctrl);
पूर्ण

अटल व्योम ad9389b_check_monitor_present_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	पूर्णांक retry = 0;

	ad9389b_update_monitor_present_status(sd);

	/*
	 * Rapid toggling of the hotplug may leave the chip घातered off,
	 * even अगर we think it is on. In that हाल reset and घातer up again.
	 */
	जबतक (state->घातer_on && (ad9389b_rd(sd, 0x41) & 0x40)) अणु
		अगर (++retry > 5) अणु
			v4l2_err(sd, "retried %d times, give up\n", retry);
			वापस;
		पूर्ण
		v4l2_dbg(1, debug, sd, "%s: reset and re-check status (%d)\n", __func__, retry);
		ad9389b_notअगरy_monitor_detect(sd);
		cancel_delayed_work_sync(&state->edid_handler);
		स_रखो(&state->edid, 0, माप(काष्ठा ad9389b_state_edid));
		ad9389b_s_घातer(sd, false);
		ad9389b_update_monitor_present_status(sd);
	पूर्ण
पूर्ण

अटल bool edid_block_verअगरy_crc(u8 *edid_block)
अणु
	u8 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 128; i++)
		sum += edid_block[i];
	वापस sum == 0;
पूर्ण

अटल bool edid_verअगरy_crc(काष्ठा v4l2_subdev *sd, u32 segment)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	u32 blocks = state->edid.blocks;
	u8 *data = state->edid.data;

	अगर (edid_block_verअगरy_crc(&data[segment * 256])) अणु
		अगर ((segment + 1) * 2 <= blocks)
			वापस edid_block_verअगरy_crc(&data[segment * 256 + 128]);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool edid_verअगरy_header(काष्ठा v4l2_subdev *sd, u32 segment)
अणु
	अटल स्थिर u8 hdmi_header[] = अणु
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
	पूर्ण;
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	u8 *data = state->edid.data;
	पूर्णांक i;

	अगर (segment)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(hdmi_header); i++)
		अगर (data[i] != hdmi_header[i])
			वापस false;

	वापस true;
पूर्ण

अटल bool ad9389b_check_edid_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	काष्ठा ad9389b_edid_detect ed;
	पूर्णांक segment;
	u8 edidRdy = ad9389b_rd(sd, 0xc5);

	v4l2_dbg(1, debug, sd, "%s: edid ready (retries: %d)\n",
		 __func__, EDID_MAX_RETRIES - state->edid.पढ़ो_retries);

	अगर (!(edidRdy & MASK_AD9389B_EDID_RDY))
		वापस false;

	segment = ad9389b_rd(sd, 0xc4);
	अगर (segment >= EDID_MAX_SEGM) अणु
		v4l2_err(sd, "edid segment number too big\n");
		वापस false;
	पूर्ण
	v4l2_dbg(1, debug, sd, "%s: got segment %d\n", __func__, segment);
	ad9389b_edid_rd(sd, 256, &state->edid.data[segment * 256]);
	ad9389b_dbg_dump_edid(2, debug, sd, segment,
			      &state->edid.data[segment * 256]);
	अगर (segment == 0) अणु
		state->edid.blocks = state->edid.data[0x7e] + 1;
		v4l2_dbg(1, debug, sd, "%s: %d blocks in total\n",
			 __func__, state->edid.blocks);
	पूर्ण
	अगर (!edid_verअगरy_crc(sd, segment) ||
	    !edid_verअगरy_header(sd, segment)) अणु
		/* edid crc error, क्रमce reपढ़ो of edid segment */
		v4l2_err(sd, "%s: edid crc or header error\n", __func__);
		ad9389b_s_घातer(sd, false);
		ad9389b_s_घातer(sd, true);
		वापस false;
	पूर्ण
	/* one more segment पढ़ो ok */
	state->edid.segments = segment + 1;
	अगर (((state->edid.data[0x7e] >> 1) + 1) > state->edid.segments) अणु
		/* Request next EDID segment */
		v4l2_dbg(1, debug, sd, "%s: request segment %d\n",
			 __func__, state->edid.segments);
		ad9389b_wr(sd, 0xc9, 0xf);
		ad9389b_wr(sd, 0xc4, state->edid.segments);
		state->edid.पढ़ो_retries = EDID_MAX_RETRIES;
		schedule_delayed_work(&state->edid_handler, EDID_DELAY);
		वापस false;
	पूर्ण

	/* report when we have all segments but report only क्रम segment 0 */
	ed.present = true;
	ed.segment = 0;
	v4l2_subdev_notअगरy(sd, AD9389B_EDID_DETECT, (व्योम *)&ed);
	state->edid_detect_counter++;
	v4l2_ctrl_s_ctrl(state->have_edid0_ctrl, state->edid.segments ? 0x1 : 0x0);
	वापस ed.present;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल व्योम ad9389b_init_setup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);
	काष्ठा ad9389b_state_edid *edid = &state->edid;

	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	/* clear all पूर्णांकerrupts */
	ad9389b_wr(sd, 0x96, 0xff);

	स_रखो(edid, 0, माप(काष्ठा ad9389b_state_edid));
	state->have_monitor = false;
	ad9389b_set_isr(sd, false);
पूर्ण

अटल पूर्णांक ad9389b_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा v4l2_dv_timings dv1080p60 = V4L2_DV_BT_CEA_1920X1080P60;
	काष्ठा ad9389b_state *state;
	काष्ठा ad9389b_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक err = -EIO;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_dbg(1, debug, client, "detecting ad9389b client on address 0x%x\n",
		client->addr << 1);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	/* Platक्रमm data */
	अगर (pdata == शून्य) अणु
		v4l_err(client, "No platform data!\n");
		वापस -ENODEV;
	पूर्ण
	स_नकल(&state->pdata, pdata, माप(state->pdata));

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &ad9389b_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 5);

	state->hdmi_mode_ctrl = v4l2_ctrl_new_std_menu(hdl, &ad9389b_ctrl_ops,
			V4L2_CID_DV_TX_MODE, V4L2_DV_TX_MODE_HDMI,
			0, V4L2_DV_TX_MODE_DVI_D);
	state->hotplug_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_TX_HOTPLUG, 0, 1, 0, 0);
	state->rx_sense_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_TX_RXSENSE, 0, 1, 0, 0);
	state->have_edid0_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_TX_EDID_PRESENT, 0, 1, 0, 0);
	state->rgb_quantization_range_ctrl =
		v4l2_ctrl_new_std_menu(hdl, &ad9389b_ctrl_ops,
			V4L2_CID_DV_TX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		err = hdl->error;

		जाओ err_hdl;
	पूर्ण
	state->pad.flags = MEDIA_PAD_FL_SINK;
	sd->entity.function = MEDIA_ENT_F_DV_ENCODER;
	err = media_entity_pads_init(&sd->entity, 1, &state->pad);
	अगर (err)
		जाओ err_hdl;

	state->chip_revision = ad9389b_rd(sd, 0x0);
	अगर (state->chip_revision != 2) अणु
		v4l2_err(sd, "chip_revision %d != 2\n", state->chip_revision);
		err = -EIO;
		जाओ err_entity;
	पूर्ण
	v4l2_dbg(1, debug, sd, "reg 0x41 0x%x, chip version (reg 0x00) 0x%x\n",
		 ad9389b_rd(sd, 0x41), state->chip_revision);

	state->edid_i2c_client = i2c_new_dummy_device(client->adapter, (0x7e >> 1));
	अगर (IS_ERR(state->edid_i2c_client)) अणु
		v4l2_err(sd, "failed to register edid i2c client\n");
		err = PTR_ERR(state->edid_i2c_client);
		जाओ err_entity;
	पूर्ण

	INIT_DELAYED_WORK(&state->edid_handler, ad9389b_edid_handler);
	state->dv_timings = dv1080p60;

	ad9389b_init_setup(sd);
	ad9389b_set_isr(sd, true);

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
		  client->addr << 1, client->adapter->name);
	वापस 0;

err_entity:
	media_entity_cleanup(&sd->entity);
err_hdl:
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस err;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक ad9389b_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ad9389b_state *state = get_ad9389b_state(sd);

	state->chip_revision = -1;

	v4l2_dbg(1, debug, sd, "%s removed @ 0x%x (%s)\n", client->name,
		 client->addr << 1, client->adapter->name);

	ad9389b_s_stream(sd, false);
	ad9389b_s_audio_stream(sd, false);
	ad9389b_init_setup(sd);
	cancel_delayed_work_sync(&state->edid_handler);
	i2c_unरेजिस्टर_device(state->edid_i2c_client);
	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id ad9389b_id[] = अणु
	अणु "ad9389b", 0 पूर्ण,
	अणु "ad9889b", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad9389b_id);

अटल काष्ठा i2c_driver ad9389b_driver = अणु
	.driver = अणु
		.name = "ad9389b",
	पूर्ण,
	.probe = ad9389b_probe,
	.हटाओ = ad9389b_हटाओ,
	.id_table = ad9389b_id,
पूर्ण;

module_i2c_driver(ad9389b_driver);
