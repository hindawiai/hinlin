<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tc358743 - Toshiba HDMI to CSI-2 bridge
 *
 * Copyright 2015 Cisco Systems, Inc. and/or its affiliates. All rights
 * reserved.
 */

/*
 * References (c = chapter, p = page):
 * REF_01 - Toshiba, TC358743XBG (H2C), Functional Specअगरication, Rev 0.60
 * REF_02 - Toshiba, TC358743XBG_HDMI-CSI_Tv11p_nm.xls
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/hdmi.h>
#समावेश <media/cec.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/i2c/tc358743.h>

#समावेश "tc358743_regs.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-3)");

MODULE_DESCRIPTION("Toshiba TC358743 HDMI to CSI-2 bridge driver");
MODULE_AUTHOR("Ramakrishnan Muthukrishnan <ram@rkrishnan.org>");
MODULE_AUTHOR("Mikhail Khelik <mkhelik@cisco.com>");
MODULE_AUTHOR("Mats Randgaard <matrandg@cisco.com>");
MODULE_LICENSE("GPL");

#घोषणा EDID_NUM_BLOCKS_MAX 8
#घोषणा EDID_BLOCK_SIZE 128

#घोषणा I2C_MAX_XFER_SIZE  (EDID_BLOCK_SIZE + 2)

#घोषणा POLL_INTERVAL_CEC_MS	10
#घोषणा POLL_INTERVAL_MS	1000

अटल स्थिर काष्ठा v4l2_dv_timings_cap tc358743_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	/* Pixel घड़ी from REF_01 p. 20. Min/max height/width are unknown */
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1200, 13000000, 165000000,
			V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
			V4L2_DV_BT_CAP_PROGRESSIVE |
			V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

काष्ठा tc358743_state अणु
	काष्ठा tc358743_platक्रमm_data pdata;
	काष्ठा v4l2_fwnode_bus_mipi_csi2 bus;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा i2c_client *i2c_client;
	/* CONFCTL is modअगरied in ops and tc358743_hdmi_sys_पूर्णांक_handler */
	काष्ठा mutex confctl_mutex;

	/* controls */
	काष्ठा v4l2_ctrl *detect_tx_5v_ctrl;
	काष्ठा v4l2_ctrl *audio_sampling_rate_ctrl;
	काष्ठा v4l2_ctrl *audio_present_ctrl;

	काष्ठा delayed_work delayed_work_enable_hotplug;

	काष्ठा समयr_list समयr;
	काष्ठा work_काष्ठा work_i2c_poll;

	/* edid  */
	u8 edid_blocks_written;

	काष्ठा v4l2_dv_timings timings;
	u32 mbus_fmt_code;
	u8 csi_lanes_in_use;

	काष्ठा gpio_desc *reset_gpio;

	काष्ठा cec_adapter *cec_adap;
पूर्ण;

अटल व्योम tc358743_enable_पूर्णांकerrupts(काष्ठा v4l2_subdev *sd,
		bool cable_connected);
अटल पूर्णांक tc358743_s_ctrl_detect_tx_5v(काष्ठा v4l2_subdev *sd);

अटल अंतरभूत काष्ठा tc358743_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tc358743_state, sd);
पूर्ण

/* --------------- I2C --------------- */

अटल व्योम i2c_rd(काष्ठा v4l2_subdev *sd, u16 reg, u8 *values, u32 n)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा i2c_client *client = state->i2c_client;
	पूर्णांक err;
	u8 buf[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 2,
			.buf = buf,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = n,
			.buf = values,
		पूर्ण,
	पूर्ण;

	err = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (err != ARRAY_SIZE(msgs)) अणु
		v4l2_err(sd, "%s: reading register 0x%x from 0x%x failed\n",
				__func__, reg, client->addr);
	पूर्ण
पूर्ण

अटल व्योम i2c_wr(काष्ठा v4l2_subdev *sd, u16 reg, u8 *values, u32 n)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा i2c_client *client = state->i2c_client;
	पूर्णांक err, i;
	काष्ठा i2c_msg msg;
	u8 data[I2C_MAX_XFER_SIZE];

	अगर ((2 + n) > I2C_MAX_XFER_SIZE) अणु
		n = I2C_MAX_XFER_SIZE - 2;
		v4l2_warn(sd, "i2c wr reg=%04x: len=%d is too big!\n",
			  reg, 2 + n);
	पूर्ण

	msg.addr = client->addr;
	msg.buf = data;
	msg.len = 2 + n;
	msg.flags = 0;

	data[0] = reg >> 8;
	data[1] = reg & 0xff;

	क्रम (i = 0; i < n; i++)
		data[2 + i] = values[i];

	err = i2c_transfer(client->adapter, &msg, 1);
	अगर (err != 1) अणु
		v4l2_err(sd, "%s: writing register 0x%x from 0x%x failed\n",
				__func__, reg, client->addr);
		वापस;
	पूर्ण

	अगर (debug < 3)
		वापस;

	चयन (n) अणु
	हाल 1:
		v4l2_info(sd, "I2C write 0x%04x = 0x%02x",
				reg, data[2]);
		अवरोध;
	हाल 2:
		v4l2_info(sd, "I2C write 0x%04x = 0x%02x%02x",
				reg, data[3], data[2]);
		अवरोध;
	हाल 4:
		v4l2_info(sd, "I2C write 0x%04x = 0x%02x%02x%02x%02x",
				reg, data[5], data[4], data[3], data[2]);
		अवरोध;
	शेष:
		v4l2_info(sd, "I2C write %d bytes from address 0x%04x\n",
				n, reg);
	पूर्ण
पूर्ण

अटल noअंतरभूत u32 i2c_rdreg(काष्ठा v4l2_subdev *sd, u16 reg, u32 n)
अणु
	__le32 val = 0;

	i2c_rd(sd, reg, (u8 __क्रमce *)&val, n);

	वापस le32_to_cpu(val);
पूर्ण

अटल noअंतरभूत व्योम i2c_wrreg(काष्ठा v4l2_subdev *sd, u16 reg, u32 val, u32 n)
अणु
	__le32 raw = cpu_to_le32(val);

	i2c_wr(sd, reg, (u8 __क्रमce *)&raw, n);
पूर्ण

अटल u8 i2c_rd8(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	वापस i2c_rdreg(sd, reg, 1);
पूर्ण

अटल व्योम i2c_wr8(काष्ठा v4l2_subdev *sd, u16 reg, u8 val)
अणु
	i2c_wrreg(sd, reg, val, 1);
पूर्ण

अटल व्योम i2c_wr8_and_or(काष्ठा v4l2_subdev *sd, u16 reg,
		u8 mask, u8 val)
अणु
	i2c_wrreg(sd, reg, (i2c_rdreg(sd, reg, 1) & mask) | val, 1);
पूर्ण

अटल u16 i2c_rd16(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	वापस i2c_rdreg(sd, reg, 2);
पूर्ण

अटल व्योम i2c_wr16(काष्ठा v4l2_subdev *sd, u16 reg, u16 val)
अणु
	i2c_wrreg(sd, reg, val, 2);
पूर्ण

अटल व्योम i2c_wr16_and_or(काष्ठा v4l2_subdev *sd, u16 reg, u16 mask, u16 val)
अणु
	i2c_wrreg(sd, reg, (i2c_rdreg(sd, reg, 2) & mask) | val, 2);
पूर्ण

अटल u32 i2c_rd32(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	वापस i2c_rdreg(sd, reg, 4);
पूर्ण

अटल व्योम i2c_wr32(काष्ठा v4l2_subdev *sd, u16 reg, u32 val)
अणु
	i2c_wrreg(sd, reg, val, 4);
पूर्ण

/* --------------- STATUS --------------- */

अटल अंतरभूत bool is_hdmi(काष्ठा v4l2_subdev *sd)
अणु
	वापस i2c_rd8(sd, SYS_STATUS) & MASK_S_HDMI;
पूर्ण

अटल अंतरभूत bool tx_5v_घातer_present(काष्ठा v4l2_subdev *sd)
अणु
	वापस i2c_rd8(sd, SYS_STATUS) & MASK_S_DDC5V;
पूर्ण

अटल अंतरभूत bool no_संकेत(काष्ठा v4l2_subdev *sd)
अणु
	वापस !(i2c_rd8(sd, SYS_STATUS) & MASK_S_TMDS);
पूर्ण

अटल अंतरभूत bool no_sync(काष्ठा v4l2_subdev *sd)
अणु
	वापस !(i2c_rd8(sd, SYS_STATUS) & MASK_S_SYNC);
पूर्ण

अटल अंतरभूत bool audio_present(काष्ठा v4l2_subdev *sd)
अणु
	वापस i2c_rd8(sd, AU_STATUS0) & MASK_S_A_SAMPLE;
पूर्ण

अटल पूर्णांक get_audio_sampling_rate(काष्ठा v4l2_subdev *sd)
अणु
	अटल स्थिर पूर्णांक code_to_rate[] = अणु
		44100, 0, 48000, 32000, 22050, 384000, 24000, 352800,
		88200, 768000, 96000, 705600, 176400, 0, 192000, 0
	पूर्ण;

	/* Register FS_SET is not cleared when the cable is disconnected */
	अगर (no_संकेत(sd))
		वापस 0;

	वापस code_to_rate[i2c_rd8(sd, FS_SET) & MASK_FS];
पूर्ण

/* --------------- TIMINGS --------------- */

अटल अंतरभूत अचिन्हित fps(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	अगर (!V4L2_DV_BT_FRAME_HEIGHT(t) || !V4L2_DV_BT_FRAME_WIDTH(t))
		वापस 0;

	वापस DIV_ROUND_CLOSEST((अचिन्हित)t->pixelघड़ी,
			V4L2_DV_BT_FRAME_HEIGHT(t) * V4L2_DV_BT_FRAME_WIDTH(t));
पूर्ण

अटल पूर्णांक tc358743_get_detected_timings(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	अचिन्हित width, height, frame_width, frame_height, frame_पूर्णांकerval, fps;

	स_रखो(timings, 0, माप(काष्ठा v4l2_dv_timings));

	अगर (no_संकेत(sd)) अणु
		v4l2_dbg(1, debug, sd, "%s: no valid signal\n", __func__);
		वापस -ENOLINK;
	पूर्ण
	अगर (no_sync(sd)) अणु
		v4l2_dbg(1, debug, sd, "%s: no sync on signal\n", __func__);
		वापस -ENOLCK;
	पूर्ण

	timings->type = V4L2_DV_BT_656_1120;
	bt->पूर्णांकerlaced = i2c_rd8(sd, VI_STATUS1) & MASK_S_V_INTERLACE ?
		V4L2_DV_INTERLACED : V4L2_DV_PROGRESSIVE;

	width = ((i2c_rd8(sd, DE_WIDTH_H_HI) & 0x1f) << 8) +
		i2c_rd8(sd, DE_WIDTH_H_LO);
	height = ((i2c_rd8(sd, DE_WIDTH_V_HI) & 0x1f) << 8) +
		i2c_rd8(sd, DE_WIDTH_V_LO);
	frame_width = ((i2c_rd8(sd, H_SIZE_HI) & 0x1f) << 8) +
		i2c_rd8(sd, H_SIZE_LO);
	frame_height = (((i2c_rd8(sd, V_SIZE_HI) & 0x3f) << 8) +
		i2c_rd8(sd, V_SIZE_LO)) / 2;
	/* frame पूर्णांकerval in milliseconds * 10
	 * Require SYS_FREQ0 and SYS_FREQ1 are precisely set */
	frame_पूर्णांकerval = ((i2c_rd8(sd, FV_CNT_HI) & 0x3) << 8) +
		i2c_rd8(sd, FV_CNT_LO);
	fps = (frame_पूर्णांकerval > 0) ?
		DIV_ROUND_CLOSEST(10000, frame_पूर्णांकerval) : 0;

	bt->width = width;
	bt->height = height;
	bt->vsync = frame_height - height;
	bt->hsync = frame_width - width;
	bt->pixelघड़ी = frame_width * frame_height * fps;
	अगर (bt->पूर्णांकerlaced == V4L2_DV_INTERLACED) अणु
		bt->height *= 2;
		bt->il_vsync = bt->vsync + 1;
		bt->pixelघड़ी /= 2;
	पूर्ण

	वापस 0;
पूर्ण

/* --------------- HOTPLUG / HDCP / EDID --------------- */

अटल व्योम tc358743_delayed_work_enable_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tc358743_state *state = container_of(dwork,
			काष्ठा tc358743_state, delayed_work_enable_hotplug);
	काष्ठा v4l2_subdev *sd = &state->sd;

	v4l2_dbg(2, debug, sd, "%s:\n", __func__);

	i2c_wr8_and_or(sd, HPD_CTL, ~MASK_HPD_OUT0, MASK_HPD_OUT0);
पूर्ण

अटल व्योम tc358743_set_hdmi_hdcp(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	v4l2_dbg(2, debug, sd, "%s: %s\n", __func__, enable ?
				"enable" : "disable");

	अगर (enable) अणु
		i2c_wr8_and_or(sd, HDCP_REG3, ~KEY_RD_CMD, KEY_RD_CMD);

		i2c_wr8_and_or(sd, HDCP_MODE, ~MASK_MANUAL_AUTHENTICATION, 0);

		i2c_wr8_and_or(sd, HDCP_REG1, 0xff,
				MASK_AUTH_UNAUTH_SEL_16_FRAMES |
				MASK_AUTH_UNAUTH_AUTO);

		i2c_wr8_and_or(sd, HDCP_REG2, ~MASK_AUTO_P3_RESET,
				SET_AUTO_P3_RESET_FRAMES(0x0f));
	पूर्ण अन्यथा अणु
		i2c_wr8_and_or(sd, HDCP_MODE, ~MASK_MANUAL_AUTHENTICATION,
				MASK_MANUAL_AUTHENTICATION);
	पूर्ण
पूर्ण

अटल व्योम tc358743_disable_edid(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	v4l2_dbg(2, debug, sd, "%s:\n", __func__);

	cancel_delayed_work_sync(&state->delayed_work_enable_hotplug);

	/* DDC access to EDID is also disabled when hotplug is disabled. See
	 * रेजिस्टर DDC_CTL */
	i2c_wr8_and_or(sd, HPD_CTL, ~MASK_HPD_OUT0, 0x0);
पूर्ण

अटल व्योम tc358743_enable_edid(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	अगर (state->edid_blocks_written == 0) अणु
		v4l2_dbg(2, debug, sd, "%s: no EDID -> no hotplug\n", __func__);
		tc358743_s_ctrl_detect_tx_5v(sd);
		वापस;
	पूर्ण

	v4l2_dbg(2, debug, sd, "%s:\n", __func__);

	/* Enable hotplug after 100 ms. DDC access to EDID is also enabled when
	 * hotplug is enabled. See रेजिस्टर DDC_CTL */
	schedule_delayed_work(&state->delayed_work_enable_hotplug, HZ / 10);

	tc358743_enable_पूर्णांकerrupts(sd, true);
	tc358743_s_ctrl_detect_tx_5v(sd);
पूर्ण

अटल व्योम tc358743_erase_bksv(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++)
		i2c_wr8(sd, BKSV + i, 0);
पूर्ण

/* --------------- AVI infoframe --------------- */

अटल व्योम prपूर्णांक_avi_infoframe(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा device *dev = &client->dev;
	जोड़ hdmi_infoframe frame;
	u8 buffer[HDMI_INFOFRAME_SIZE(AVI)];

	अगर (!is_hdmi(sd)) अणु
		v4l2_info(sd, "DVI-D signal - AVI infoframe not supported\n");
		वापस;
	पूर्ण

	i2c_rd(sd, PK_AVI_0HEAD, buffer, HDMI_INFOFRAME_SIZE(AVI));

	अगर (hdmi_infoframe_unpack(&frame, buffer, माप(buffer)) < 0) अणु
		v4l2_err(sd, "%s: unpack of AVI infoframe failed\n", __func__);
		वापस;
	पूर्ण

	hdmi_infoframe_log(KERN_INFO, dev, &frame);
पूर्ण

/* --------------- CTRLS --------------- */

अटल पूर्णांक tc358743_s_ctrl_detect_tx_5v(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	वापस v4l2_ctrl_s_ctrl(state->detect_tx_5v_ctrl,
			tx_5v_घातer_present(sd));
पूर्ण

अटल पूर्णांक tc358743_s_ctrl_audio_sampling_rate(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	वापस v4l2_ctrl_s_ctrl(state->audio_sampling_rate_ctrl,
			get_audio_sampling_rate(sd));
पूर्ण

अटल पूर्णांक tc358743_s_ctrl_audio_present(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	वापस v4l2_ctrl_s_ctrl(state->audio_present_ctrl,
			audio_present(sd));
पूर्ण

अटल पूर्णांक tc358743_update_controls(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक ret = 0;

	ret |= tc358743_s_ctrl_detect_tx_5v(sd);
	ret |= tc358743_s_ctrl_audio_sampling_rate(sd);
	ret |= tc358743_s_ctrl_audio_present(sd);

	वापस ret;
पूर्ण

/* --------------- INIT --------------- */

अटल व्योम tc358743_reset_phy(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	i2c_wr8_and_or(sd, PHY_RST, ~MASK_RESET_CTRL, 0);
	i2c_wr8_and_or(sd, PHY_RST, ~MASK_RESET_CTRL, MASK_RESET_CTRL);
पूर्ण

अटल व्योम tc358743_reset(काष्ठा v4l2_subdev *sd, uपूर्णांक16_t mask)
अणु
	u16 sysctl = i2c_rd16(sd, SYSCTL);

	i2c_wr16(sd, SYSCTL, sysctl | mask);
	i2c_wr16(sd, SYSCTL, sysctl & ~mask);
पूर्ण

अटल अंतरभूत व्योम tc358743_sleep_mode(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	i2c_wr16_and_or(sd, SYSCTL, ~MASK_SLEEP,
			enable ? MASK_SLEEP : 0);
पूर्ण

अटल अंतरभूत व्योम enable_stream(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	v4l2_dbg(3, debug, sd, "%s: %sable\n",
			__func__, enable ? "en" : "dis");

	अगर (enable) अणु
		/* It is critical क्रम CSI receiver to see lane transition
		 * LP11->HS. Set to non-continuous mode to enable घड़ी lane
		 * LP11 state. */
		i2c_wr32(sd, TXOPTIONCNTRL, 0);
		/* Set to continuous mode to trigger LP11->HS transition */
		i2c_wr32(sd, TXOPTIONCNTRL, MASK_CONTCLKMODE);
		/* Unmute video */
		i2c_wr8(sd, VI_MUTE, MASK_AUTO_MUTE);
	पूर्ण अन्यथा अणु
		/* Mute video so that all data lanes go to LSP11 state.
		 * No data is output to CSI Tx block. */
		i2c_wr8(sd, VI_MUTE, MASK_AUTO_MUTE | MASK_VI_MUTE);
	पूर्ण

	mutex_lock(&state->confctl_mutex);
	i2c_wr16_and_or(sd, CONFCTL, ~(MASK_VBUFEN | MASK_ABUFEN),
			enable ? (MASK_VBUFEN | MASK_ABUFEN) : 0x0);
	mutex_unlock(&state->confctl_mutex);
पूर्ण

अटल व्योम tc358743_set_pll(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा tc358743_platक्रमm_data *pdata = &state->pdata;
	u16 pllctl0 = i2c_rd16(sd, PLLCTL0);
	u16 pllctl1 = i2c_rd16(sd, PLLCTL1);
	u16 pllctl0_new = SET_PLL_PRD(pdata->pll_prd) |
		SET_PLL_FBD(pdata->pll_fbd);
	u32 hsck = (pdata->refclk_hz / pdata->pll_prd) * pdata->pll_fbd;

	v4l2_dbg(2, debug, sd, "%s:\n", __func__);

	/* Only reग_लिखो when needed (new value or disabled), since rewriting
	 * triggers another क्रमmat change event. */
	अगर ((pllctl0 != pllctl0_new) || ((pllctl1 & MASK_PLL_EN) == 0)) अणु
		u16 pll_frs;

		अगर (hsck > 500000000)
			pll_frs = 0x0;
		अन्यथा अगर (hsck > 250000000)
			pll_frs = 0x1;
		अन्यथा अगर (hsck > 125000000)
			pll_frs = 0x2;
		अन्यथा
			pll_frs = 0x3;

		v4l2_dbg(1, debug, sd, "%s: updating PLL clock\n", __func__);
		tc358743_sleep_mode(sd, true);
		i2c_wr16(sd, PLLCTL0, pllctl0_new);
		i2c_wr16_and_or(sd, PLLCTL1,
				~(MASK_PLL_FRS | MASK_RESETB | MASK_PLL_EN),
				(SET_PLL_FRS(pll_frs) | MASK_RESETB |
				 MASK_PLL_EN));
		udelay(10); /* REF_02, Sheet "Source HDMI" */
		i2c_wr16_and_or(sd, PLLCTL1, ~MASK_CKEN, MASK_CKEN);
		tc358743_sleep_mode(sd, false);
	पूर्ण
पूर्ण

अटल व्योम tc358743_set_ref_clk(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा tc358743_platक्रमm_data *pdata = &state->pdata;
	u32 sys_freq;
	u32 lockdet_ref;
	u32 cec_freq;
	u16 fh_min;
	u16 fh_max;

	BUG_ON(!(pdata->refclk_hz == 26000000 ||
		 pdata->refclk_hz == 27000000 ||
		 pdata->refclk_hz == 42000000));

	sys_freq = pdata->refclk_hz / 10000;
	i2c_wr8(sd, SYS_FREQ0, sys_freq & 0x00ff);
	i2c_wr8(sd, SYS_FREQ1, (sys_freq & 0xff00) >> 8);

	i2c_wr8_and_or(sd, PHY_CTL0, ~MASK_PHY_SYSCLK_IND,
			(pdata->refclk_hz == 42000000) ?
			MASK_PHY_SYSCLK_IND : 0x0);

	fh_min = pdata->refclk_hz / 100000;
	i2c_wr8(sd, FH_MIN0, fh_min & 0x00ff);
	i2c_wr8(sd, FH_MIN1, (fh_min & 0xff00) >> 8);

	fh_max = (fh_min * 66) / 10;
	i2c_wr8(sd, FH_MAX0, fh_max & 0x00ff);
	i2c_wr8(sd, FH_MAX1, (fh_max & 0xff00) >> 8);

	lockdet_ref = pdata->refclk_hz / 100;
	i2c_wr8(sd, LOCKDET_REF0, lockdet_ref & 0x0000ff);
	i2c_wr8(sd, LOCKDET_REF1, (lockdet_ref & 0x00ff00) >> 8);
	i2c_wr8(sd, LOCKDET_REF2, (lockdet_ref & 0x0f0000) >> 16);

	i2c_wr8_and_or(sd, NCO_F0_MOD, ~MASK_NCO_F0_MOD,
			(pdata->refclk_hz == 27000000) ?
			MASK_NCO_F0_MOD_27MHZ : 0x0);

	/*
	 * Trial and error suggests that the शेष रेजिस्टर value
	 * of 656 is क्रम a 42 MHz reference घड़ी. Use that to derive
	 * a new value based on the actual reference घड़ी.
	 */
	cec_freq = (656 * sys_freq) / 4200;
	i2c_wr16(sd, CECHCLK, cec_freq);
	i2c_wr16(sd, CECLCLK, cec_freq);
पूर्ण

अटल व्योम tc358743_set_csi_color_space(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	चयन (state->mbus_fmt_code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		v4l2_dbg(2, debug, sd, "%s: YCbCr 422 16-bit\n", __func__);
		i2c_wr8_and_or(sd, VOUT_SET2,
				~(MASK_SEL422 | MASK_VOUT_422FIL_100) & 0xff,
				MASK_SEL422 | MASK_VOUT_422FIL_100);
		i2c_wr8_and_or(sd, VI_REP, ~MASK_VOUT_COLOR_SEL & 0xff,
				MASK_VOUT_COLOR_601_YCBCR_LIMITED);
		mutex_lock(&state->confctl_mutex);
		i2c_wr16_and_or(sd, CONFCTL, ~MASK_YCBCRFMT,
				MASK_YCBCRFMT_422_8_BIT);
		mutex_unlock(&state->confctl_mutex);
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		v4l2_dbg(2, debug, sd, "%s: RGB 888 24-bit\n", __func__);
		i2c_wr8_and_or(sd, VOUT_SET2,
				~(MASK_SEL422 | MASK_VOUT_422FIL_100) & 0xff,
				0x00);
		i2c_wr8_and_or(sd, VI_REP, ~MASK_VOUT_COLOR_SEL & 0xff,
				MASK_VOUT_COLOR_RGB_FULL);
		mutex_lock(&state->confctl_mutex);
		i2c_wr16_and_or(sd, CONFCTL, ~MASK_YCBCRFMT, 0);
		mutex_unlock(&state->confctl_mutex);
		अवरोध;
	शेष:
		v4l2_dbg(2, debug, sd, "%s: Unsupported format code 0x%x\n",
				__func__, state->mbus_fmt_code);
	पूर्ण
पूर्ण

अटल अचिन्हित tc358743_num_csi_lanes_needed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा v4l2_bt_timings *bt = &state->timings.bt;
	काष्ठा tc358743_platक्रमm_data *pdata = &state->pdata;
	u32 bits_pr_pixel =
		(state->mbus_fmt_code == MEDIA_BUS_FMT_UYVY8_1X16) ?  16 : 24;
	u32 bps = bt->width * bt->height * fps(bt) * bits_pr_pixel;
	u32 bps_pr_lane = (pdata->refclk_hz / pdata->pll_prd) * pdata->pll_fbd;

	वापस DIV_ROUND_UP(bps, bps_pr_lane);
पूर्ण

अटल व्योम tc358743_set_csi(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा tc358743_platक्रमm_data *pdata = &state->pdata;
	अचिन्हित lanes = tc358743_num_csi_lanes_needed(sd);

	v4l2_dbg(3, debug, sd, "%s:\n", __func__);

	state->csi_lanes_in_use = lanes;

	tc358743_reset(sd, MASK_CTXRST);

	अगर (lanes < 1)
		i2c_wr32(sd, CLW_CNTRL, MASK_CLW_LANEDISABLE);
	अगर (lanes < 1)
		i2c_wr32(sd, D0W_CNTRL, MASK_D0W_LANEDISABLE);
	अगर (lanes < 2)
		i2c_wr32(sd, D1W_CNTRL, MASK_D1W_LANEDISABLE);
	अगर (lanes < 3)
		i2c_wr32(sd, D2W_CNTRL, MASK_D2W_LANEDISABLE);
	अगर (lanes < 4)
		i2c_wr32(sd, D3W_CNTRL, MASK_D3W_LANEDISABLE);

	i2c_wr32(sd, LINEINITCNT, pdata->lineinitcnt);
	i2c_wr32(sd, LPTXTIMECNT, pdata->lptxसमयcnt);
	i2c_wr32(sd, TCLK_HEADERCNT, pdata->tclk_headercnt);
	i2c_wr32(sd, TCLK_TRAILCNT, pdata->tclk_trailcnt);
	i2c_wr32(sd, THS_HEADERCNT, pdata->ths_headercnt);
	i2c_wr32(sd, TWAKEUP, pdata->twakeup);
	i2c_wr32(sd, TCLK_POSTCNT, pdata->tclk_postcnt);
	i2c_wr32(sd, THS_TRAILCNT, pdata->ths_trailcnt);
	i2c_wr32(sd, HSTXVREGCNT, pdata->hstxvregcnt);

	i2c_wr32(sd, HSTXVREGEN,
			((lanes > 0) ? MASK_CLM_HSTXVREGEN : 0x0) |
			((lanes > 0) ? MASK_D0M_HSTXVREGEN : 0x0) |
			((lanes > 1) ? MASK_D1M_HSTXVREGEN : 0x0) |
			((lanes > 2) ? MASK_D2M_HSTXVREGEN : 0x0) |
			((lanes > 3) ? MASK_D3M_HSTXVREGEN : 0x0));

	i2c_wr32(sd, TXOPTIONCNTRL, (state->bus.flags &
		 V4L2_MBUS_CSI2_CONTINUOUS_CLOCK) ? MASK_CONTCLKMODE : 0);
	i2c_wr32(sd, STARTCNTRL, MASK_START);
	i2c_wr32(sd, CSI_START, MASK_STRT);

	i2c_wr32(sd, CSI_CONFW, MASK_MODE_SET |
			MASK_ADDRESS_CSI_CONTROL |
			MASK_CSI_MODE |
			MASK_TXHSMD |
			((lanes == 4) ? MASK_NOL_4 :
			 (lanes == 3) ? MASK_NOL_3 :
			 (lanes == 2) ? MASK_NOL_2 : MASK_NOL_1));

	i2c_wr32(sd, CSI_CONFW, MASK_MODE_SET |
			MASK_ADDRESS_CSI_ERR_INTENA | MASK_TXBRK | MASK_QUNK |
			MASK_WCER | MASK_INER);

	i2c_wr32(sd, CSI_CONFW, MASK_MODE_CLEAR |
			MASK_ADDRESS_CSI_ERR_HALT | MASK_TXBRK | MASK_QUNK);

	i2c_wr32(sd, CSI_CONFW, MASK_MODE_SET |
			MASK_ADDRESS_CSI_INT_ENA | MASK_INTER);
पूर्ण

अटल व्योम tc358743_set_hdmi_phy(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा tc358743_platक्रमm_data *pdata = &state->pdata;

	/* Default settings from REF_02, sheet "Source HDMI"
	 * and custom settings as platक्रमm data */
	i2c_wr8_and_or(sd, PHY_EN, ~MASK_ENABLE_PHY, 0x0);
	i2c_wr8(sd, PHY_CTL1, SET_PHY_AUTO_RST1_US(1600) |
			SET_FREQ_RANGE_MODE_CYCLES(1));
	i2c_wr8_and_or(sd, PHY_CTL2, ~MASK_PHY_AUTO_RSTn,
			(pdata->hdmi_phy_स्वतः_reset_पंचांगds_detected ?
			 MASK_PHY_AUTO_RST2 : 0) |
			(pdata->hdmi_phy_स्वतः_reset_पंचांगds_in_range ?
			 MASK_PHY_AUTO_RST3 : 0) |
			(pdata->hdmi_phy_स्वतः_reset_पंचांगds_valid ?
			 MASK_PHY_AUTO_RST4 : 0));
	i2c_wr8(sd, PHY_BIAS, 0x40);
	i2c_wr8(sd, PHY_CSQ, SET_CSQ_CNT_LEVEL(0x0a));
	i2c_wr8(sd, AVM_CTL, 45);
	i2c_wr8_and_or(sd, HDMI_DET, ~MASK_HDMI_DET_V,
			pdata->hdmi_detection_delay << 4);
	i2c_wr8_and_or(sd, HV_RST, ~(MASK_H_PI_RST | MASK_V_PI_RST),
			(pdata->hdmi_phy_स्वतः_reset_hsync_out_of_range ?
			 MASK_H_PI_RST : 0) |
			(pdata->hdmi_phy_स्वतः_reset_vsync_out_of_range ?
			 MASK_V_PI_RST : 0));
	i2c_wr8_and_or(sd, PHY_EN, ~MASK_ENABLE_PHY, MASK_ENABLE_PHY);
पूर्ण

अटल व्योम tc358743_set_hdmi_audio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	/* Default settings from REF_02, sheet "Source HDMI" */
	i2c_wr8(sd, FORCE_MUTE, 0x00);
	i2c_wr8(sd, AUTO_CMD0, MASK_AUTO_MUTE7 | MASK_AUTO_MUTE6 |
			MASK_AUTO_MUTE5 | MASK_AUTO_MUTE4 |
			MASK_AUTO_MUTE1 | MASK_AUTO_MUTE0);
	i2c_wr8(sd, AUTO_CMD1, MASK_AUTO_MUTE9);
	i2c_wr8(sd, AUTO_CMD2, MASK_AUTO_PLAY3 | MASK_AUTO_PLAY2);
	i2c_wr8(sd, BUFINIT_START, SET_BUFINIT_START_MS(500));
	i2c_wr8(sd, FS_MUTE, 0x00);
	i2c_wr8(sd, FS_IMODE, MASK_NLPCM_SMODE | MASK_FS_SMODE);
	i2c_wr8(sd, ACR_MODE, MASK_CTS_MODE);
	i2c_wr8(sd, ACR_MDF0, MASK_ACR_L2MDF_1976_PPM | MASK_ACR_L1MDF_976_PPM);
	i2c_wr8(sd, ACR_MDF1, MASK_ACR_L3MDF_3906_PPM);
	i2c_wr8(sd, SDO_MODE1, MASK_SDO_FMT_I2S);
	i2c_wr8(sd, DIV_MODE, SET_DIV_DLY_MS(100));

	mutex_lock(&state->confctl_mutex);
	i2c_wr16_and_or(sd, CONFCTL, 0xffff, MASK_AUDCHNUM_2 |
			MASK_AUDOUTSEL_I2S | MASK_AUTOINDEX);
	mutex_unlock(&state->confctl_mutex);
पूर्ण

अटल व्योम tc358743_set_hdmi_info_frame_mode(काष्ठा v4l2_subdev *sd)
अणु
	/* Default settings from REF_02, sheet "Source HDMI" */
	i2c_wr8(sd, PK_INT_MODE, MASK_ISRC2_INT_MODE | MASK_ISRC_INT_MODE |
			MASK_ACP_INT_MODE | MASK_VS_INT_MODE |
			MASK_SPD_INT_MODE | MASK_MS_INT_MODE |
			MASK_AUD_INT_MODE | MASK_AVI_INT_MODE);
	i2c_wr8(sd, NO_PKT_LIMIT, 0x2c);
	i2c_wr8(sd, NO_PKT_CLR, 0x53);
	i2c_wr8(sd, ERR_PK_LIMIT, 0x01);
	i2c_wr8(sd, NO_PKT_LIMIT2, 0x30);
	i2c_wr8(sd, NO_GDB_LIMIT, 0x10);
पूर्ण

अटल व्योम tc358743_initial_setup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा tc358743_platक्रमm_data *pdata = &state->pdata;

	/*
	 * IR is not supported by this driver.
	 * CEC is only enabled अगर needed.
	 */
	i2c_wr16_and_or(sd, SYSCTL, ~(MASK_IRRST | MASK_CECRST),
				     (MASK_IRRST | MASK_CECRST));

	tc358743_reset(sd, MASK_CTXRST | MASK_HDMIRST);
#अगर_घोषित CONFIG_VIDEO_TC358743_CEC
	tc358743_reset(sd, MASK_CECRST);
#पूर्ण_अगर
	tc358743_sleep_mode(sd, false);

	i2c_wr16(sd, FIFOCTL, pdata->fअगरo_level);

	tc358743_set_ref_clk(sd);

	i2c_wr8_and_or(sd, DDC_CTL, ~MASK_DDC5V_MODE,
			pdata->ddc5v_delay & MASK_DDC5V_MODE);
	i2c_wr8_and_or(sd, EDID_MODE, ~MASK_EDID_MODE, MASK_EDID_MODE_E_DDC);

	tc358743_set_hdmi_phy(sd);
	tc358743_set_hdmi_hdcp(sd, pdata->enable_hdcp);
	tc358743_set_hdmi_audio(sd);
	tc358743_set_hdmi_info_frame_mode(sd);

	/* All CE and IT क्रमmats are detected as RGB full range in DVI mode */
	i2c_wr8_and_or(sd, VI_MODE, ~MASK_RGB_DVI, 0);

	i2c_wr8_and_or(sd, VOUT_SET2, ~MASK_VOUTCOLORMODE,
			MASK_VOUTCOLORMODE_AUTO);
	i2c_wr8(sd, VOUT_SET3, MASK_VOUT_EXTCNT);
पूर्ण

/* --------------- CEC --------------- */

#अगर_घोषित CONFIG_VIDEO_TC358743_CEC
अटल पूर्णांक tc358743_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा tc358743_state *state = adap->priv;
	काष्ठा v4l2_subdev *sd = &state->sd;

	i2c_wr32(sd, CECIMSK, enable ? MASK_CECTIM | MASK_CECRIM : 0);
	i2c_wr32(sd, CECICLR, MASK_CECTICLR | MASK_CECRICLR);
	i2c_wr32(sd, CECEN, enable);
	अगर (enable)
		i2c_wr32(sd, CECREN, MASK_CECREN);
	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_cec_adap_monitor_all_enable(काष्ठा cec_adapter *adap,
						bool enable)
अणु
	काष्ठा tc358743_state *state = adap->priv;
	काष्ठा v4l2_subdev *sd = &state->sd;
	u32 reg;

	reg = i2c_rd32(sd, CECRCTL1);
	अगर (enable)
		reg |= MASK_CECOTH;
	अन्यथा
		reg &= ~MASK_CECOTH;
	i2c_wr32(sd, CECRCTL1, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा tc358743_state *state = adap->priv;
	काष्ठा v4l2_subdev *sd = &state->sd;
	अचिन्हित पूर्णांक la = 0;

	अगर (log_addr != CEC_LOG_ADDR_INVALID) अणु
		la = i2c_rd32(sd, CECADD);
		la |= 1 << log_addr;
	पूर्ण
	i2c_wr32(sd, CECADD, la);
	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				   u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा tc358743_state *state = adap->priv;
	काष्ठा v4l2_subdev *sd = &state->sd;
	अचिन्हित पूर्णांक i;

	i2c_wr32(sd, CECTCTL,
		 (cec_msg_is_broadcast(msg) ? MASK_CECBRD : 0) |
		 (संकेत_मुक्त_समय - 1));
	क्रम (i = 0; i < msg->len; i++)
		i2c_wr32(sd, CECTBUF1 + i * 4,
			msg->msg[i] | ((i == msg->len - 1) ? MASK_CECTEOM : 0));
	i2c_wr32(sd, CECTEN, MASK_CECTEN);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops tc358743_cec_adap_ops = अणु
	.adap_enable = tc358743_cec_adap_enable,
	.adap_log_addr = tc358743_cec_adap_log_addr,
	.adap_transmit = tc358743_cec_adap_transmit,
	.adap_monitor_all_enable = tc358743_cec_adap_monitor_all_enable,
पूर्ण;

अटल व्योम tc358743_cec_handler(काष्ठा v4l2_subdev *sd, u16 पूर्णांकstatus,
				 bool *handled)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	अचिन्हित पूर्णांक cec_rxपूर्णांक, cec_txपूर्णांक;
	अचिन्हित पूर्णांक clr = 0;

	cec_rxपूर्णांक = i2c_rd32(sd, CECRSTAT);
	cec_txपूर्णांक = i2c_rd32(sd, CECTSTAT);

	अगर (पूर्णांकstatus & MASK_CEC_RINT)
		clr |= MASK_CECRICLR;
	अगर (पूर्णांकstatus & MASK_CEC_TINT)
		clr |= MASK_CECTICLR;
	i2c_wr32(sd, CECICLR, clr);

	अगर ((पूर्णांकstatus & MASK_CEC_TINT) && cec_txपूर्णांक) अणु
		अगर (cec_txपूर्णांक & MASK_CECTIEND)
			cec_transmit_attempt_करोne(state->cec_adap,
						  CEC_TX_STATUS_OK);
		अन्यथा अगर (cec_txपूर्णांक & MASK_CECTIAL)
			cec_transmit_attempt_करोne(state->cec_adap,
						  CEC_TX_STATUS_ARB_LOST);
		अन्यथा अगर (cec_txपूर्णांक & MASK_CECTIACK)
			cec_transmit_attempt_करोne(state->cec_adap,
						  CEC_TX_STATUS_NACK);
		अन्यथा अगर (cec_txपूर्णांक & MASK_CECTIUR) अणु
			/*
			 * Not sure when this bit is set. Treat
			 * it as an error क्रम now.
			 */
			cec_transmit_attempt_करोne(state->cec_adap,
						  CEC_TX_STATUS_ERROR);
		पूर्ण
		अगर (handled)
			*handled = true;
	पूर्ण
	अगर ((पूर्णांकstatus & MASK_CEC_RINT) &&
	    (cec_rxपूर्णांक & MASK_CECRIEND)) अणु
		काष्ठा cec_msg msg = अणुपूर्ण;
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक v;

		v = i2c_rd32(sd, CECRCTR);
		msg.len = v & 0x1f;
		क्रम (i = 0; i < msg.len; i++) अणु
			v = i2c_rd32(sd, CECRBUF1 + i * 4);
			msg.msg[i] = v & 0xff;
		पूर्ण
		cec_received_msg(state->cec_adap, &msg);
		अगर (handled)
			*handled = true;
	पूर्ण
	i2c_wr16(sd, INTSTATUS,
		 पूर्णांकstatus & (MASK_CEC_RINT | MASK_CEC_TINT));
पूर्ण

#पूर्ण_अगर

/* --------------- IRQ --------------- */

अटल व्योम tc358743_क्रमmat_change(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा v4l2_dv_timings timings;
	स्थिर काष्ठा v4l2_event tc358743_ev_fmt = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
	पूर्ण;

	अगर (tc358743_get_detected_timings(sd, &timings)) अणु
		enable_stream(sd, false);

		v4l2_dbg(1, debug, sd, "%s: No signal\n",
				__func__);
	पूर्ण अन्यथा अणु
		अगर (!v4l2_match_dv_timings(&state->timings, &timings, 0, false))
			enable_stream(sd, false);

		अगर (debug)
			v4l2_prपूर्णांक_dv_timings(sd->name,
					"tc358743_format_change: New format: ",
					&timings, false);
	पूर्ण

	अगर (sd->devnode)
		v4l2_subdev_notअगरy_event(sd, &tc358743_ev_fmt);
पूर्ण

अटल व्योम tc358743_init_पूर्णांकerrupts(काष्ठा v4l2_subdev *sd)
अणु
	u16 i;

	/* clear पूर्णांकerrupt status रेजिस्टरs */
	क्रम (i = SYS_INT; i <= KEY_INT; i++)
		i2c_wr8(sd, i, 0xff);

	i2c_wr16(sd, INTSTATUS, 0xffff);
पूर्ण

अटल व्योम tc358743_enable_पूर्णांकerrupts(काष्ठा v4l2_subdev *sd,
		bool cable_connected)
अणु
	v4l2_dbg(2, debug, sd, "%s: cable connected = %d\n", __func__,
			cable_connected);

	अगर (cable_connected) अणु
		i2c_wr8(sd, SYS_INTM, ~(MASK_M_DDC | MASK_M_DVI_DET |
					MASK_M_HDMI_DET) & 0xff);
		i2c_wr8(sd, CLK_INTM, ~MASK_M_IN_DE_CHG);
		i2c_wr8(sd, CBIT_INTM, ~(MASK_M_CBIT_FS | MASK_M_AF_LOCK |
					MASK_M_AF_UNLOCK) & 0xff);
		i2c_wr8(sd, AUDIO_INTM, ~MASK_M_BUFINIT_END);
		i2c_wr8(sd, MISC_INTM, ~MASK_M_SYNC_CHG);
	पूर्ण अन्यथा अणु
		i2c_wr8(sd, SYS_INTM, ~MASK_M_DDC & 0xff);
		i2c_wr8(sd, CLK_INTM, 0xff);
		i2c_wr8(sd, CBIT_INTM, 0xff);
		i2c_wr8(sd, AUDIO_INTM, 0xff);
		i2c_wr8(sd, MISC_INTM, 0xff);
	पूर्ण
पूर्ण

अटल व्योम tc358743_hdmi_audio_पूर्णांक_handler(काष्ठा v4l2_subdev *sd,
		bool *handled)
अणु
	u8 audio_पूर्णांक_mask = i2c_rd8(sd, AUDIO_INTM);
	u8 audio_पूर्णांक = i2c_rd8(sd, AUDIO_INT) & ~audio_पूर्णांक_mask;

	i2c_wr8(sd, AUDIO_INT, audio_पूर्णांक);

	v4l2_dbg(3, debug, sd, "%s: AUDIO_INT = 0x%02x\n", __func__, audio_पूर्णांक);

	tc358743_s_ctrl_audio_sampling_rate(sd);
	tc358743_s_ctrl_audio_present(sd);
पूर्ण

अटल व्योम tc358743_csi_err_पूर्णांक_handler(काष्ठा v4l2_subdev *sd, bool *handled)
अणु
	v4l2_err(sd, "%s: CSI_ERR = 0x%x\n", __func__, i2c_rd32(sd, CSI_ERR));

	i2c_wr32(sd, CSI_INT_CLR, MASK_ICRER);
पूर्ण

अटल व्योम tc358743_hdmi_misc_पूर्णांक_handler(काष्ठा v4l2_subdev *sd,
		bool *handled)
अणु
	u8 misc_पूर्णांक_mask = i2c_rd8(sd, MISC_INTM);
	u8 misc_पूर्णांक = i2c_rd8(sd, MISC_INT) & ~misc_पूर्णांक_mask;

	i2c_wr8(sd, MISC_INT, misc_पूर्णांक);

	v4l2_dbg(3, debug, sd, "%s: MISC_INT = 0x%02x\n", __func__, misc_पूर्णांक);

	अगर (misc_पूर्णांक & MASK_I_SYNC_CHG) अणु
		/* Reset the HDMI PHY to try to trigger proper lock on the
		 * incoming video क्रमmat. Erase BKSV to prevent that old keys
		 * are used when a new source is connected. */
		अगर (no_sync(sd) || no_संकेत(sd)) अणु
			tc358743_reset_phy(sd);
			tc358743_erase_bksv(sd);
		पूर्ण

		tc358743_क्रमmat_change(sd);

		misc_पूर्णांक &= ~MASK_I_SYNC_CHG;
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (misc_पूर्णांक) अणु
		v4l2_err(sd, "%s: Unhandled MISC_INT interrupts: 0x%02x\n",
				__func__, misc_पूर्णांक);
	पूर्ण
पूर्ण

अटल व्योम tc358743_hdmi_cbit_पूर्णांक_handler(काष्ठा v4l2_subdev *sd,
		bool *handled)
अणु
	u8 cbit_पूर्णांक_mask = i2c_rd8(sd, CBIT_INTM);
	u8 cbit_पूर्णांक = i2c_rd8(sd, CBIT_INT) & ~cbit_पूर्णांक_mask;

	i2c_wr8(sd, CBIT_INT, cbit_पूर्णांक);

	v4l2_dbg(3, debug, sd, "%s: CBIT_INT = 0x%02x\n", __func__, cbit_पूर्णांक);

	अगर (cbit_पूर्णांक & MASK_I_CBIT_FS) अणु

		v4l2_dbg(1, debug, sd, "%s: Audio sample rate changed\n",
				__func__);
		tc358743_s_ctrl_audio_sampling_rate(sd);

		cbit_पूर्णांक &= ~MASK_I_CBIT_FS;
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (cbit_पूर्णांक & (MASK_I_AF_LOCK | MASK_I_AF_UNLOCK)) अणु

		v4l2_dbg(1, debug, sd, "%s: Audio present changed\n",
				__func__);
		tc358743_s_ctrl_audio_present(sd);

		cbit_पूर्णांक &= ~(MASK_I_AF_LOCK | MASK_I_AF_UNLOCK);
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (cbit_पूर्णांक) अणु
		v4l2_err(sd, "%s: Unhandled CBIT_INT interrupts: 0x%02x\n",
				__func__, cbit_पूर्णांक);
	पूर्ण
पूर्ण

अटल व्योम tc358743_hdmi_clk_पूर्णांक_handler(काष्ठा v4l2_subdev *sd, bool *handled)
अणु
	u8 clk_पूर्णांक_mask = i2c_rd8(sd, CLK_INTM);
	u8 clk_पूर्णांक = i2c_rd8(sd, CLK_INT) & ~clk_पूर्णांक_mask;

	/* Bit 7 and bit 6 are set even when they are masked */
	i2c_wr8(sd, CLK_INT, clk_पूर्णांक | 0x80 | MASK_I_OUT_H_CHG);

	v4l2_dbg(3, debug, sd, "%s: CLK_INT = 0x%02x\n", __func__, clk_पूर्णांक);

	अगर (clk_पूर्णांक & (MASK_I_IN_DE_CHG)) अणु

		v4l2_dbg(1, debug, sd, "%s: DE size or position has changed\n",
				__func__);

		/* If the source चयन to a new resolution with the same pixel
		 * frequency as the existing (e.g. 1080p25 -> 720p50), the
		 * I_SYNC_CHG पूर्णांकerrupt is not always triggered, जबतक the
		 * I_IN_DE_CHG पूर्णांकerrupt seems to work fine. Format change
		 * notअगरications are only sent when the संकेत is stable to
		 * reduce the number of notअगरications. */
		अगर (!no_संकेत(sd) && !no_sync(sd))
			tc358743_क्रमmat_change(sd);

		clk_पूर्णांक &= ~(MASK_I_IN_DE_CHG);
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (clk_पूर्णांक) अणु
		v4l2_err(sd, "%s: Unhandled CLK_INT interrupts: 0x%02x\n",
				__func__, clk_पूर्णांक);
	पूर्ण
पूर्ण

अटल व्योम tc358743_hdmi_sys_पूर्णांक_handler(काष्ठा v4l2_subdev *sd, bool *handled)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	u8 sys_पूर्णांक_mask = i2c_rd8(sd, SYS_INTM);
	u8 sys_पूर्णांक = i2c_rd8(sd, SYS_INT) & ~sys_पूर्णांक_mask;

	i2c_wr8(sd, SYS_INT, sys_पूर्णांक);

	v4l2_dbg(3, debug, sd, "%s: SYS_INT = 0x%02x\n", __func__, sys_पूर्णांक);

	अगर (sys_पूर्णांक & MASK_I_DDC) अणु
		bool tx_5v = tx_5v_घातer_present(sd);

		v4l2_dbg(1, debug, sd, "%s: Tx 5V power present: %s\n",
				__func__, tx_5v ?  "yes" : "no");

		अगर (tx_5v) अणु
			tc358743_enable_edid(sd);
		पूर्ण अन्यथा अणु
			tc358743_enable_पूर्णांकerrupts(sd, false);
			tc358743_disable_edid(sd);
			स_रखो(&state->timings, 0, माप(state->timings));
			tc358743_erase_bksv(sd);
			tc358743_update_controls(sd);
		पूर्ण

		sys_पूर्णांक &= ~MASK_I_DDC;
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (sys_पूर्णांक & MASK_I_DVI) अणु
		v4l2_dbg(1, debug, sd, "%s: HDMI->DVI change detected\n",
				__func__);

		/* Reset the HDMI PHY to try to trigger proper lock on the
		 * incoming video क्रमmat. Erase BKSV to prevent that old keys
		 * are used when a new source is connected. */
		अगर (no_sync(sd) || no_संकेत(sd)) अणु
			tc358743_reset_phy(sd);
			tc358743_erase_bksv(sd);
		पूर्ण

		sys_पूर्णांक &= ~MASK_I_DVI;
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (sys_पूर्णांक & MASK_I_HDMI) अणु
		v4l2_dbg(1, debug, sd, "%s: DVI->HDMI change detected\n",
				__func__);

		/* Register is reset in DVI mode (REF_01, c. 6.6.41) */
		i2c_wr8(sd, ANA_CTL, MASK_APPL_PCSX_NORMAL | MASK_ANALOG_ON);

		sys_पूर्णांक &= ~MASK_I_HDMI;
		अगर (handled)
			*handled = true;
	पूर्ण

	अगर (sys_पूर्णांक) अणु
		v4l2_err(sd, "%s: Unhandled SYS_INT interrupts: 0x%02x\n",
				__func__, sys_पूर्णांक);
	पूर्ण
पूर्ण

/* --------------- CORE OPS --------------- */

अटल पूर्णांक tc358743_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	काष्ठा v4l2_dv_timings timings;
	uपूर्णांक8_t hdmi_sys_status =  i2c_rd8(sd, SYS_STATUS);
	uपूर्णांक16_t sysctl = i2c_rd16(sd, SYSCTL);
	u8 vi_status3 =  i2c_rd8(sd, VI_STATUS3);
	स्थिर पूर्णांक deep_color_mode[4] = अणु 8, 10, 12, 16 पूर्ण;
	अटल स्थिर अक्षर * स्थिर input_color_space[] = अणु
		"RGB", "YCbCr 601", "opRGB", "YCbCr 709", "NA (4)",
		"xvYCC 601", "NA(6)", "xvYCC 709", "NA(8)", "sYCC601",
		"NA(10)", "NA(11)", "NA(12)", "opYCC 601"पूर्ण;

	v4l2_info(sd, "-----Chip status-----\n");
	v4l2_info(sd, "Chip ID: 0x%02x\n",
			(i2c_rd16(sd, CHIPID) & MASK_CHIPID) >> 8);
	v4l2_info(sd, "Chip revision: 0x%02x\n",
			i2c_rd16(sd, CHIPID) & MASK_REVID);
	v4l2_info(sd, "Reset: IR: %d, CEC: %d, CSI TX: %d, HDMI: %d\n",
			!!(sysctl & MASK_IRRST),
			!!(sysctl & MASK_CECRST),
			!!(sysctl & MASK_CTXRST),
			!!(sysctl & MASK_HDMIRST));
	v4l2_info(sd, "Sleep mode: %s\n", sysctl & MASK_SLEEP ? "on" : "off");
	v4l2_info(sd, "Cable detected (+5V power): %s\n",
			hdmi_sys_status & MASK_S_DDC5V ? "yes" : "no");
	v4l2_info(sd, "DDC lines enabled: %s\n",
			(i2c_rd8(sd, EDID_MODE) & MASK_EDID_MODE_E_DDC) ?
			"yes" : "no");
	v4l2_info(sd, "Hotplug enabled: %s\n",
			(i2c_rd8(sd, HPD_CTL) & MASK_HPD_OUT0) ?
			"yes" : "no");
	v4l2_info(sd, "CEC enabled: %s\n",
			(i2c_rd16(sd, CECEN) & MASK_CECEN) ?  "yes" : "no");
	v4l2_info(sd, "-----Signal status-----\n");
	v4l2_info(sd, "TMDS signal detected: %s\n",
			hdmi_sys_status & MASK_S_TMDS ? "yes" : "no");
	v4l2_info(sd, "Stable sync signal: %s\n",
			hdmi_sys_status & MASK_S_SYNC ? "yes" : "no");
	v4l2_info(sd, "PHY PLL locked: %s\n",
			hdmi_sys_status & MASK_S_PHY_PLL ? "yes" : "no");
	v4l2_info(sd, "PHY DE detected: %s\n",
			hdmi_sys_status & MASK_S_PHY_SCDT ? "yes" : "no");

	अगर (tc358743_get_detected_timings(sd, &timings)) अणु
		v4l2_info(sd, "No video detected\n");
	पूर्ण अन्यथा अणु
		v4l2_prपूर्णांक_dv_timings(sd->name, "Detected format: ", &timings,
				true);
	पूर्ण
	v4l2_prपूर्णांक_dv_timings(sd->name, "Configured format: ", &state->timings,
			true);

	v4l2_info(sd, "-----CSI-TX status-----\n");
	v4l2_info(sd, "Lanes needed: %d\n",
			tc358743_num_csi_lanes_needed(sd));
	v4l2_info(sd, "Lanes in use: %d\n",
			state->csi_lanes_in_use);
	v4l2_info(sd, "Waiting for particular sync signal: %s\n",
			(i2c_rd16(sd, CSI_STATUS) & MASK_S_WSYNC) ?
			"yes" : "no");
	v4l2_info(sd, "Transmit mode: %s\n",
			(i2c_rd16(sd, CSI_STATUS) & MASK_S_TXACT) ?
			"yes" : "no");
	v4l2_info(sd, "Receive mode: %s\n",
			(i2c_rd16(sd, CSI_STATUS) & MASK_S_RXACT) ?
			"yes" : "no");
	v4l2_info(sd, "Stopped: %s\n",
			(i2c_rd16(sd, CSI_STATUS) & MASK_S_HLT) ?
			"yes" : "no");
	v4l2_info(sd, "Color space: %s\n",
			state->mbus_fmt_code == MEDIA_BUS_FMT_UYVY8_1X16 ?
			"YCbCr 422 16-bit" :
			state->mbus_fmt_code == MEDIA_BUS_FMT_RGB888_1X24 ?
			"RGB 888 24-bit" : "Unsupported");

	v4l2_info(sd, "-----%s status-----\n", is_hdmi(sd) ? "HDMI" : "DVI-D");
	v4l2_info(sd, "HDCP encrypted content: %s\n",
			hdmi_sys_status & MASK_S_HDCP ? "yes" : "no");
	v4l2_info(sd, "Input color space: %s %s range\n",
			input_color_space[(vi_status3 & MASK_S_V_COLOR) >> 1],
			(vi_status3 & MASK_LIMITED) ? "limited" : "full");
	अगर (!is_hdmi(sd))
		वापस 0;
	v4l2_info(sd, "AV Mute: %s\n", hdmi_sys_status & MASK_S_AVMUTE ? "on" :
			"off");
	v4l2_info(sd, "Deep color mode: %d-bits per channel\n",
			deep_color_mode[(i2c_rd8(sd, VI_STATUS1) &
				MASK_S_DEEPCOLOR) >> 2]);
	prपूर्णांक_avi_infoframe(sd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल व्योम tc358743_prपूर्णांक_रेजिस्टर_map(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_info(sd, "0x0000-0x00FF: Global Control Register\n");
	v4l2_info(sd, "0x0100-0x01FF: CSI2-TX PHY Register\n");
	v4l2_info(sd, "0x0200-0x03FF: CSI2-TX PPI Register\n");
	v4l2_info(sd, "0x0400-0x05FF: Reserved\n");
	v4l2_info(sd, "0x0600-0x06FF: CEC Register\n");
	v4l2_info(sd, "0x0700-0x84FF: Reserved\n");
	v4l2_info(sd, "0x8500-0x85FF: HDMIRX System Control Register\n");
	v4l2_info(sd, "0x8600-0x86FF: HDMIRX Audio Control Register\n");
	v4l2_info(sd, "0x8700-0x87FF: HDMIRX InfoFrame packet data Register\n");
	v4l2_info(sd, "0x8800-0x88FF: HDMIRX HDCP Port Register\n");
	v4l2_info(sd, "0x8900-0x89FF: HDMIRX Video Output Port & 3D Register\n");
	v4l2_info(sd, "0x8A00-0x8BFF: Reserved\n");
	v4l2_info(sd, "0x8C00-0x8FFF: HDMIRX EDID-RAM (1024bytes)\n");
	v4l2_info(sd, "0x9000-0x90FF: HDMIRX GBD Extraction Control\n");
	v4l2_info(sd, "0x9100-0x92FF: HDMIRX GBD RAM read\n");
	v4l2_info(sd, "0x9300-      : Reserved\n");
पूर्ण

अटल पूर्णांक tc358743_get_reg_size(u16 address)
अणु
	/* REF_01 p. 66-72 */
	अगर (address <= 0x00ff)
		वापस 2;
	अन्यथा अगर ((address >= 0x0100) && (address <= 0x06FF))
		वापस 4;
	अन्यथा अगर ((address >= 0x0700) && (address <= 0x84ff))
		वापस 2;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक tc358743_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	अगर (reg->reg > 0xffff) अणु
		tc358743_prपूर्णांक_रेजिस्टर_map(sd);
		वापस -EINVAL;
	पूर्ण

	reg->size = tc358743_get_reg_size(reg->reg);

	reg->val = i2c_rdreg(sd, reg->reg, reg->size);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			       स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	अगर (reg->reg > 0xffff) अणु
		tc358743_prपूर्णांक_रेजिस्टर_map(sd);
		वापस -EINVAL;
	पूर्ण

	/* It should not be possible क्रम the user to enable HDCP with a simple
	 * v4l2-dbg command.
	 *
	 * DO NOT REMOVE THIS unless all other issues with HDCP have been
	 * resolved.
	 */
	अगर (reg->reg == HDCP_MODE ||
	    reg->reg == HDCP_REG1 ||
	    reg->reg == HDCP_REG2 ||
	    reg->reg == HDCP_REG3 ||
	    reg->reg == BCAPS)
		वापस 0;

	i2c_wrreg(sd, (u16)reg->reg, reg->val,
			tc358743_get_reg_size(reg->reg));

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tc358743_isr(काष्ठा v4l2_subdev *sd, u32 status, bool *handled)
अणु
	u16 पूर्णांकstatus = i2c_rd16(sd, INTSTATUS);

	v4l2_dbg(1, debug, sd, "%s: IntStatus = 0x%04x\n", __func__, पूर्णांकstatus);

	अगर (पूर्णांकstatus & MASK_HDMI_INT) अणु
		u8 hdmi_पूर्णांक0 = i2c_rd8(sd, HDMI_INT0);
		u8 hdmi_पूर्णांक1 = i2c_rd8(sd, HDMI_INT1);

		अगर (hdmi_पूर्णांक0 & MASK_I_MISC)
			tc358743_hdmi_misc_पूर्णांक_handler(sd, handled);
		अगर (hdmi_पूर्णांक1 & MASK_I_CBIT)
			tc358743_hdmi_cbit_पूर्णांक_handler(sd, handled);
		अगर (hdmi_पूर्णांक1 & MASK_I_CLK)
			tc358743_hdmi_clk_पूर्णांक_handler(sd, handled);
		अगर (hdmi_पूर्णांक1 & MASK_I_SYS)
			tc358743_hdmi_sys_पूर्णांक_handler(sd, handled);
		अगर (hdmi_पूर्णांक1 & MASK_I_AUD)
			tc358743_hdmi_audio_पूर्णांक_handler(sd, handled);

		i2c_wr16(sd, INTSTATUS, MASK_HDMI_INT);
		पूर्णांकstatus &= ~MASK_HDMI_INT;
	पूर्ण

#अगर_घोषित CONFIG_VIDEO_TC358743_CEC
	अगर (पूर्णांकstatus & (MASK_CEC_RINT | MASK_CEC_TINT)) अणु
		tc358743_cec_handler(sd, पूर्णांकstatus, handled);
		i2c_wr16(sd, INTSTATUS,
			 पूर्णांकstatus & (MASK_CEC_RINT | MASK_CEC_TINT));
		पूर्णांकstatus &= ~(MASK_CEC_RINT | MASK_CEC_TINT);
	पूर्ण
#पूर्ण_अगर

	अगर (पूर्णांकstatus & MASK_CSI_INT) अणु
		u32 csi_पूर्णांक = i2c_rd32(sd, CSI_INT);

		अगर (csi_पूर्णांक & MASK_INTER)
			tc358743_csi_err_पूर्णांक_handler(sd, handled);

		i2c_wr16(sd, INTSTATUS, MASK_CSI_INT);
	पूर्ण

	पूर्णांकstatus = i2c_rd16(sd, INTSTATUS);
	अगर (पूर्णांकstatus) अणु
		v4l2_dbg(1, debug, sd,
				"%s: Unhandled IntStatus interrupts: 0x%02x\n",
				__func__, पूर्णांकstatus);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t tc358743_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tc358743_state *state = dev_id;
	bool handled = false;

	tc358743_isr(&state->sd, 0, &handled);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम tc358743_irq_poll_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tc358743_state *state = from_समयr(state, t, समयr);
	अचिन्हित पूर्णांक msecs;

	schedule_work(&state->work_i2c_poll);
	/*
	 * If CEC is present, then we need to poll more frequently,
	 * otherwise we will miss CEC messages.
	 */
	msecs = state->cec_adap ? POLL_INTERVAL_CEC_MS : POLL_INTERVAL_MS;
	mod_समयr(&state->समयr, jअगरfies + msecs_to_jअगरfies(msecs));
पूर्ण

अटल व्योम tc358743_work_i2c_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tc358743_state *state = container_of(work,
			काष्ठा tc358743_state, work_i2c_poll);
	bool handled;

	tc358743_isr(&state->sd, 0, &handled);
पूर्ण

अटल पूर्णांक tc358743_subscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				    काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subdev_subscribe(sd, fh, sub);
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_ctrl_subdev_subscribe_event(sd, fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* --------------- VIDEO OPS --------------- */

अटल पूर्णांक tc358743_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	*status = 0;
	*status |= no_संकेत(sd) ? V4L2_IN_ST_NO_SIGNAL : 0;
	*status |= no_sync(sd) ? V4L2_IN_ST_NO_SYNC : 0;

	v4l2_dbg(1, debug, sd, "%s: status = 0x%x\n", __func__, *status);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_s_dv_timings(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	अगर (!timings)
		वापस -EINVAL;

	अगर (debug)
		v4l2_prपूर्णांक_dv_timings(sd->name, "tc358743_s_dv_timings: ",
				timings, false);

	अगर (v4l2_match_dv_timings(&state->timings, timings, 0, false)) अणु
		v4l2_dbg(1, debug, sd, "%s: no change\n", __func__);
		वापस 0;
	पूर्ण

	अगर (!v4l2_valid_dv_timings(timings,
				&tc358743_timings_cap, शून्य, शून्य)) अणु
		v4l2_dbg(1, debug, sd, "%s: timings out of range\n", __func__);
		वापस -दुस्फल;
	पूर्ण

	state->timings = *timings;

	enable_stream(sd, false);
	tc358743_set_pll(sd);
	tc358743_set_csi(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_g_dv_timings(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	*timings = state->timings;

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->pad != 0)
		वापस -EINVAL;

	वापस v4l2_क्रमागत_dv_timings_cap(timings,
			&tc358743_timings_cap, शून्य, शून्य);
पूर्ण

अटल पूर्णांक tc358743_query_dv_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक ret;

	ret = tc358743_get_detected_timings(sd, timings);
	अगर (ret)
		वापस ret;

	अगर (debug)
		v4l2_prपूर्णांक_dv_timings(sd->name, "tc358743_query_dv_timings: ",
				timings, false);

	अगर (!v4l2_valid_dv_timings(timings,
				&tc358743_timings_cap, शून्य, शून्य)) अणु
		v4l2_dbg(1, debug, sd, "%s: timings out of range\n", __func__);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_dv_timings_cap(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (cap->pad != 0)
		वापस -EINVAL;

	*cap = tc358743_timings_cap;

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_get_mbus_config(काष्ठा v4l2_subdev *sd,
				    अचिन्हित पूर्णांक pad,
				    काष्ठा v4l2_mbus_config *cfg)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	cfg->type = V4L2_MBUS_CSI2_DPHY;

	/* Support क्रम non-continuous CSI-2 घड़ी is missing in the driver */
	cfg->flags = V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;

	चयन (state->csi_lanes_in_use) अणु
	हाल 1:
		cfg->flags |= V4L2_MBUS_CSI2_1_LANE;
		अवरोध;
	हाल 2:
		cfg->flags |= V4L2_MBUS_CSI2_2_LANE;
		अवरोध;
	हाल 3:
		cfg->flags |= V4L2_MBUS_CSI2_3_LANE;
		अवरोध;
	हाल 4:
		cfg->flags |= V4L2_MBUS_CSI2_4_LANE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	enable_stream(sd, enable);
	अगर (!enable) अणु
		/* Put all lanes in LP-11 state (STOPSTATE) */
		tc358743_set_csi(sd);
	पूर्ण

	वापस 0;
पूर्ण

/* --------------- PAD OPS --------------- */

अटल पूर्णांक tc358743_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	चयन (code->index) अणु
	हाल 0:
		code->code = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	हाल 1:
		code->code = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	u8 vi_rep = i2c_rd8(sd, VI_REP);

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;

	क्रमmat->क्रमmat.code = state->mbus_fmt_code;
	क्रमmat->क्रमmat.width = state->timings.bt.width;
	क्रमmat->क्रमmat.height = state->timings.bt.height;
	क्रमmat->क्रमmat.field = V4L2_FIELD_NONE;

	चयन (vi_rep & MASK_VOUT_COLOR_SEL) अणु
	हाल MASK_VOUT_COLOR_RGB_FULL:
	हाल MASK_VOUT_COLOR_RGB_LIMITED:
		क्रमmat->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
		अवरोध;
	हाल MASK_VOUT_COLOR_601_YCBCR_LIMITED:
	हाल MASK_VOUT_COLOR_601_YCBCR_FULL:
		क्रमmat->क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M;
		अवरोध;
	हाल MASK_VOUT_COLOR_709_YCBCR_FULL:
	हाल MASK_VOUT_COLOR_709_YCBCR_LIMITED:
		क्रमmat->क्रमmat.colorspace = V4L2_COLORSPACE_REC709;
		अवरोध;
	शेष:
		क्रमmat->क्रमmat.colorspace = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	u32 code = क्रमmat->क्रमmat.code; /* is overwritten by get_fmt */
	पूर्णांक ret = tc358743_get_fmt(sd, cfg, क्रमmat);

	क्रमmat->क्रमmat.code = code;

	अगर (ret)
		वापस ret;

	चयन (code) अणु
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;

	state->mbus_fmt_code = क्रमmat->क्रमmat.code;

	enable_stream(sd, false);
	tc358743_set_pll(sd);
	tc358743_set_csi(sd);
	tc358743_set_csi_color_space(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_g_edid(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_edid *edid)
अणु
	काष्ठा tc358743_state *state = to_state(sd);

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->pad != 0)
		वापस -EINVAL;

	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = state->edid_blocks_written;
		वापस 0;
	पूर्ण

	अगर (state->edid_blocks_written == 0)
		वापस -ENODATA;

	अगर (edid->start_block >= state->edid_blocks_written ||
			edid->blocks == 0)
		वापस -EINVAL;

	अगर (edid->start_block + edid->blocks > state->edid_blocks_written)
		edid->blocks = state->edid_blocks_written - edid->start_block;

	i2c_rd(sd, EDID_RAM + (edid->start_block * EDID_BLOCK_SIZE), edid->edid,
			edid->blocks * EDID_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358743_s_edid(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_edid *edid)
अणु
	काष्ठा tc358743_state *state = to_state(sd);
	u16 edid_len = edid->blocks * EDID_BLOCK_SIZE;
	u16 pa;
	पूर्णांक err;
	पूर्णांक i;

	v4l2_dbg(2, debug, sd, "%s, pad %d, start block %d, blocks %d\n",
		 __func__, edid->pad, edid->start_block, edid->blocks);

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->pad != 0)
		वापस -EINVAL;

	अगर (edid->start_block != 0)
		वापस -EINVAL;

	अगर (edid->blocks > EDID_NUM_BLOCKS_MAX) अणु
		edid->blocks = EDID_NUM_BLOCKS_MAX;
		वापस -E2BIG;
	पूर्ण
	pa = cec_get_edid_phys_addr(edid->edid, edid->blocks * 128, शून्य);
	err = v4l2_phys_addr_validate(pa, &pa, शून्य);
	अगर (err)
		वापस err;

	cec_phys_addr_invalidate(state->cec_adap);

	tc358743_disable_edid(sd);

	i2c_wr8(sd, EDID_LEN1, edid_len & 0xff);
	i2c_wr8(sd, EDID_LEN2, edid_len >> 8);

	अगर (edid->blocks == 0) अणु
		state->edid_blocks_written = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < edid_len; i += EDID_BLOCK_SIZE)
		i2c_wr(sd, EDID_RAM + i, edid->edid + i, EDID_BLOCK_SIZE);

	state->edid_blocks_written = edid->blocks;

	cec_s_phys_addr(state->cec_adap, pa, false);

	अगर (tx_5v_घातer_present(sd))
		tc358743_enable_edid(sd);

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops tc358743_core_ops = अणु
	.log_status = tc358743_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = tc358743_g_रेजिस्टर,
	.s_रेजिस्टर = tc358743_s_रेजिस्टर,
#पूर्ण_अगर
	.पूर्णांकerrupt_service_routine = tc358743_isr,
	.subscribe_event = tc358743_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops tc358743_video_ops = अणु
	.g_input_status = tc358743_g_input_status,
	.s_dv_timings = tc358743_s_dv_timings,
	.g_dv_timings = tc358743_g_dv_timings,
	.query_dv_timings = tc358743_query_dv_timings,
	.s_stream = tc358743_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tc358743_pad_ops = अणु
	.क्रमागत_mbus_code = tc358743_क्रमागत_mbus_code,
	.set_fmt = tc358743_set_fmt,
	.get_fmt = tc358743_get_fmt,
	.get_edid = tc358743_g_edid,
	.set_edid = tc358743_s_edid,
	.क्रमागत_dv_timings = tc358743_क्रमागत_dv_timings,
	.dv_timings_cap = tc358743_dv_timings_cap,
	.get_mbus_config = tc358743_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tc358743_ops = अणु
	.core = &tc358743_core_ops,
	.video = &tc358743_video_ops,
	.pad = &tc358743_pad_ops,
पूर्ण;

/* --------------- CUSTOM CTRLS --------------- */

अटल स्थिर काष्ठा v4l2_ctrl_config tc358743_ctrl_audio_sampling_rate = अणु
	.id = TC358743_CID_AUDIO_SAMPLING_RATE,
	.name = "Audio sampling rate",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 768000,
	.step = 1,
	.def = 0,
	.flags = V4L2_CTRL_FLAG_READ_ONLY,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config tc358743_ctrl_audio_present = अणु
	.id = TC358743_CID_AUDIO_PRESENT,
	.name = "Audio present",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
	.flags = V4L2_CTRL_FLAG_READ_ONLY,
पूर्ण;

/* --------------- PROBE / REMOVE --------------- */

#अगर_घोषित CONFIG_OF
अटल व्योम tc358743_gpio_reset(काष्ठा tc358743_state *state)
अणु
	usleep_range(5000, 10000);
	gpiod_set_value(state->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value(state->reset_gpio, 0);
	msleep(20);
पूर्ण

अटल पूर्णांक tc358743_probe_of(काष्ठा tc358743_state *state)
अणु
	काष्ठा device *dev = &state->i2c_client->dev;
	काष्ठा v4l2_fwnode_endpoपूर्णांक endpoपूर्णांक = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *ep;
	काष्ठा clk *refclk;
	u32 bps_pr_lane;
	पूर्णांक ret;

	refclk = devm_clk_get(dev, "refclk");
	अगर (IS_ERR(refclk)) अणु
		अगर (PTR_ERR(refclk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get refclk: %ld\n",
				PTR_ERR(refclk));
		वापस PTR_ERR(refclk);
	पूर्ण

	ep = of_graph_get_next_endpoपूर्णांक(dev->of_node, शून्य);
	अगर (!ep) अणु
		dev_err(dev, "missing endpoint node\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(of_fwnode_handle(ep), &endpoपूर्णांक);
	अगर (ret) अणु
		dev_err(dev, "failed to parse endpoint\n");
		जाओ put_node;
	पूर्ण

	अगर (endpoपूर्णांक.bus_type != V4L2_MBUS_CSI2_DPHY ||
	    endpoपूर्णांक.bus.mipi_csi2.num_data_lanes == 0 ||
	    endpoपूर्णांक.nr_of_link_frequencies == 0) अणु
		dev_err(dev, "missing CSI-2 properties in endpoint\n");
		ret = -EINVAL;
		जाओ मुक्त_endpoपूर्णांक;
	पूर्ण

	अगर (endpoपूर्णांक.bus.mipi_csi2.num_data_lanes > 4) अणु
		dev_err(dev, "invalid number of lanes\n");
		ret = -EINVAL;
		जाओ मुक्त_endpoपूर्णांक;
	पूर्ण

	state->bus = endpoपूर्णांक.bus.mipi_csi2;

	ret = clk_prepare_enable(refclk);
	अगर (ret) अणु
		dev_err(dev, "Failed! to enable clock\n");
		जाओ मुक्त_endpoपूर्णांक;
	पूर्ण

	state->pdata.refclk_hz = clk_get_rate(refclk);
	state->pdata.ddc5v_delay = DDC5V_DELAY_100_MS;
	state->pdata.enable_hdcp = false;
	/* A FIFO level of 16 should be enough क्रम 2-lane 720p60 at 594 MHz. */
	state->pdata.fअगरo_level = 16;
	/*
	 * The PLL input घड़ी is obtained by भागiding refclk by pll_prd.
	 * It must be between 6 MHz and 40 MHz, lower frequency is better.
	 */
	चयन (state->pdata.refclk_hz) अणु
	हाल 26000000:
	हाल 27000000:
	हाल 42000000:
		state->pdata.pll_prd = state->pdata.refclk_hz / 6000000;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported refclk rate: %u Hz\n",
			state->pdata.refclk_hz);
		जाओ disable_clk;
	पूर्ण

	/*
	 * The CSI bps per lane must be between 62.5 Mbps and 1 Gbps.
	 * The शेष is 594 Mbps क्रम 4-lane 1080p60 or 2-lane 720p60.
	 */
	bps_pr_lane = 2 * endpoपूर्णांक.link_frequencies[0];
	अगर (bps_pr_lane < 62500000U || bps_pr_lane > 1000000000U) अणु
		dev_err(dev, "unsupported bps per lane: %u bps\n", bps_pr_lane);
		जाओ disable_clk;
	पूर्ण

	/* The CSI speed per lane is refclk / pll_prd * pll_fbd */
	state->pdata.pll_fbd = bps_pr_lane /
			       state->pdata.refclk_hz * state->pdata.pll_prd;

	/*
	 * FIXME: These timings are from REF_02 क्रम 594 Mbps per lane (297 MHz
	 * link frequency). In principle it should be possible to calculate
	 * them based on link frequency and resolution.
	 */
	अगर (bps_pr_lane != 594000000U)
		dev_warn(dev, "untested bps per lane: %u bps\n", bps_pr_lane);
	state->pdata.lineinitcnt = 0xe80;
	state->pdata.lptxसमयcnt = 0x003;
	/* tclk-preparecnt: 3, tclk-zerocnt: 20 */
	state->pdata.tclk_headercnt = 0x1403;
	state->pdata.tclk_trailcnt = 0x00;
	/* ths-preparecnt: 3, ths-zerocnt: 1 */
	state->pdata.ths_headercnt = 0x0103;
	state->pdata.twakeup = 0x4882;
	state->pdata.tclk_postcnt = 0x008;
	state->pdata.ths_trailcnt = 0x2;
	state->pdata.hstxvregcnt = 0;

	state->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(state->reset_gpio)) अणु
		dev_err(dev, "failed to get reset gpio\n");
		ret = PTR_ERR(state->reset_gpio);
		जाओ disable_clk;
	पूर्ण

	अगर (state->reset_gpio)
		tc358743_gpio_reset(state);

	ret = 0;
	जाओ मुक्त_endpoपूर्णांक;

disable_clk:
	clk_disable_unprepare(refclk);
मुक्त_endpoपूर्णांक:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&endpoपूर्णांक);
put_node:
	of_node_put(ep);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक tc358743_probe_of(काष्ठा tc358743_state *state)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tc358743_probe(काष्ठा i2c_client *client)
अणु
	अटल काष्ठा v4l2_dv_timings शेष_timing =
		V4L2_DV_BT_CEA_640X480P59_94;
	काष्ठा tc358743_state *state;
	काष्ठा tc358743_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_subdev *sd;
	u16 irq_mask = MASK_HDMI_MSK | MASK_CSI_MSK;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;
	v4l_dbg(1, debug, client, "chip found @ 0x%x (%s)\n",
		client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(काष्ठा tc358743_state),
			GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->i2c_client = client;

	/* platक्रमm data */
	अगर (pdata) अणु
		state->pdata = *pdata;
		state->bus.flags = V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	पूर्ण अन्यथा अणु
		err = tc358743_probe_of(state);
		अगर (err == -ENODEV)
			v4l_err(client, "No platform data!\n");
		अगर (err)
			वापस err;
	पूर्ण

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tc358743_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;

	/* i2c access */
	अगर ((i2c_rd16(sd, CHIPID) & MASK_CHIPID) != 0) अणु
		v4l2_info(sd, "not a TC358743 on address 0x%x\n",
			  client->addr << 1);
		वापस -ENODEV;
	पूर्ण

	/* control handlers */
	v4l2_ctrl_handler_init(&state->hdl, 3);

	state->detect_tx_5v_ctrl = v4l2_ctrl_new_std(&state->hdl, शून्य,
			V4L2_CID_DV_RX_POWER_PRESENT, 0, 1, 0, 0);

	/* custom controls */
	state->audio_sampling_rate_ctrl = v4l2_ctrl_new_custom(&state->hdl,
			&tc358743_ctrl_audio_sampling_rate, शून्य);

	state->audio_present_ctrl = v4l2_ctrl_new_custom(&state->hdl,
			&tc358743_ctrl_audio_present, शून्य);

	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		err = state->hdl.error;
		जाओ err_hdl;
	पूर्ण

	अगर (tc358743_update_controls(sd)) अणु
		err = -ENODEV;
		जाओ err_hdl;
	पूर्ण

	state->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	err = media_entity_pads_init(&sd->entity, 1, &state->pad);
	अगर (err < 0)
		जाओ err_hdl;

	state->mbus_fmt_code = MEDIA_BUS_FMT_RGB888_1X24;

	sd->dev = &client->dev;
	err = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (err < 0)
		जाओ err_hdl;

	mutex_init(&state->confctl_mutex);

	INIT_DELAYED_WORK(&state->delayed_work_enable_hotplug,
			tc358743_delayed_work_enable_hotplug);

#अगर_घोषित CONFIG_VIDEO_TC358743_CEC
	state->cec_adap = cec_allocate_adapter(&tc358743_cec_adap_ops,
		state, dev_name(&client->dev),
		CEC_CAP_DEFAULTS | CEC_CAP_MONITOR_ALL, CEC_MAX_LOG_ADDRS);
	अगर (IS_ERR(state->cec_adap)) अणु
		err = PTR_ERR(state->cec_adap);
		जाओ err_hdl;
	पूर्ण
	irq_mask |= MASK_CEC_RMSK | MASK_CEC_TMSK;
#पूर्ण_अगर

	tc358743_initial_setup(sd);

	tc358743_s_dv_timings(sd, &शेष_timing);

	tc358743_set_csi_color_space(sd);

	tc358743_init_पूर्णांकerrupts(sd);

	अगर (state->i2c_client->irq) अणु
		err = devm_request_thपढ़ोed_irq(&client->dev,
						state->i2c_client->irq,
						शून्य, tc358743_irq_handler,
						IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
						"tc358743", state);
		अगर (err)
			जाओ err_work_queues;
	पूर्ण अन्यथा अणु
		INIT_WORK(&state->work_i2c_poll,
			  tc358743_work_i2c_poll);
		समयr_setup(&state->समयr, tc358743_irq_poll_समयr, 0);
		state->समयr.expires = jअगरfies +
				       msecs_to_jअगरfies(POLL_INTERVAL_MS);
		add_समयr(&state->समयr);
	पूर्ण

	err = cec_रेजिस्टर_adapter(state->cec_adap, &client->dev);
	अगर (err < 0) अणु
		pr_err("%s: failed to register the cec device\n", __func__);
		cec_delete_adapter(state->cec_adap);
		state->cec_adap = शून्य;
		जाओ err_work_queues;
	पूर्ण

	tc358743_enable_पूर्णांकerrupts(sd, tx_5v_घातer_present(sd));
	i2c_wr16(sd, INTMASK, ~irq_mask);

	err = v4l2_ctrl_handler_setup(sd->ctrl_handler);
	अगर (err)
		जाओ err_work_queues;

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
		  client->addr << 1, client->adapter->name);

	वापस 0;

err_work_queues:
	cec_unरेजिस्टर_adapter(state->cec_adap);
	अगर (!state->i2c_client->irq)
		flush_work(&state->work_i2c_poll);
	cancel_delayed_work(&state->delayed_work_enable_hotplug);
	mutex_destroy(&state->confctl_mutex);
err_hdl:
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस err;
पूर्ण

अटल पूर्णांक tc358743_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा tc358743_state *state = to_state(sd);

	अगर (!state->i2c_client->irq) अणु
		del_समयr_sync(&state->समयr);
		flush_work(&state->work_i2c_poll);
	पूर्ण
	cancel_delayed_work_sync(&state->delayed_work_enable_hotplug);
	cec_unरेजिस्टर_adapter(state->cec_adap);
	v4l2_async_unरेजिस्टर_subdev(sd);
	v4l2_device_unरेजिस्टर_subdev(sd);
	mutex_destroy(&state->confctl_mutex);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(&state->hdl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tc358743_id[] = अणु
	अणु"tc358743", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tc358743_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tc358743_of_match[] = अणु
	अणु .compatible = "toshiba,tc358743" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tc358743_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tc358743_driver = अणु
	.driver = अणु
		.name = "tc358743",
		.of_match_table = of_match_ptr(tc358743_of_match),
	पूर्ण,
	.probe_new = tc358743_probe,
	.हटाओ = tc358743_हटाओ,
	.id_table = tc358743_id,
पूर्ण;

module_i2c_driver(tc358743_driver);
