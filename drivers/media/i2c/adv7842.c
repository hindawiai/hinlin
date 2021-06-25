<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adv7842 - Analog Devices ADV7842 video decoder driver
 *
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

/*
 * References (c = chapter, p = page):
 * REF_01 - Analog devices, ADV7842,
 *		Register Settings Recommendations, Rev. 1.9, April 2011
 * REF_02 - Analog devices, Software User Guide, UG-206,
 *		ADV7842 I2C Register Maps, Rev. 0, November 2010
 * REF_03 - Analog devices, Hardware User Guide, UG-214,
 *		ADV7842 Fast Switching 2:1 HDMI 1.4 Receiver with 3D-Comb
 *		Decoder and Digitizer , Rev. 0, January 2011
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/hdmi.h>
#समावेश <media/cec.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/i2c/adv7842.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

MODULE_DESCRIPTION("Analog Devices ADV7842 video decoder driver");
MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com>");
MODULE_AUTHOR("Martin Bugge <marbugge@cisco.com>");
MODULE_LICENSE("GPL");

/* ADV7842 प्रणाली घड़ी frequency */
#घोषणा ADV7842_fsc (28636360)

#घोषणा ADV7842_RGB_OUT					(1 << 1)

#घोषणा ADV7842_OP_FORMAT_SEL_8BIT			(0 << 0)
#घोषणा ADV7842_OP_FORMAT_SEL_10BIT			(1 << 0)
#घोषणा ADV7842_OP_FORMAT_SEL_12BIT			(2 << 0)

#घोषणा ADV7842_OP_MODE_SEL_SDR_422			(0 << 5)
#घोषणा ADV7842_OP_MODE_SEL_DDR_422			(1 << 5)
#घोषणा ADV7842_OP_MODE_SEL_SDR_444			(2 << 5)
#घोषणा ADV7842_OP_MODE_SEL_DDR_444			(3 << 5)
#घोषणा ADV7842_OP_MODE_SEL_SDR_422_2X			(4 << 5)
#घोषणा ADV7842_OP_MODE_SEL_ADI_CM			(5 << 5)

#घोषणा ADV7842_OP_CH_SEL_GBR				(0 << 5)
#घोषणा ADV7842_OP_CH_SEL_GRB				(1 << 5)
#घोषणा ADV7842_OP_CH_SEL_BGR				(2 << 5)
#घोषणा ADV7842_OP_CH_SEL_RGB				(3 << 5)
#घोषणा ADV7842_OP_CH_SEL_BRG				(4 << 5)
#घोषणा ADV7842_OP_CH_SEL_RBG				(5 << 5)

#घोषणा ADV7842_OP_SWAP_CB_CR				(1 << 0)

#घोषणा ADV7842_MAX_ADDRS (3)

/*
**********************************************************************
*
*  Arrays with configuration parameters क्रम the ADV7842
*
**********************************************************************
*/

काष्ठा adv7842_क्रमmat_info अणु
	u32 code;
	u8 op_ch_sel;
	bool rgb_out;
	bool swap_cb_cr;
	u8 op_क्रमmat_sel;
पूर्ण;

काष्ठा adv7842_state अणु
	काष्ठा adv7842_platक्रमm_data pdata;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pads[ADV7842_PAD_SOURCE + 1];
	काष्ठा v4l2_ctrl_handler hdl;
	क्रमागत adv7842_mode mode;
	काष्ठा v4l2_dv_timings timings;
	क्रमागत adv7842_vid_std_select vid_std_select;

	स्थिर काष्ठा adv7842_क्रमmat_info *क्रमmat;

	v4l2_std_id norm;
	काष्ठा अणु
		u8 edid[256];
		u32 blocks;
		u32 present;
	पूर्ण hdmi_edid;
	काष्ठा अणु
		u8 edid[256];
		u32 blocks;
		u32 present;
	पूर्ण vga_edid;
	काष्ठा v4l2_fract aspect_ratio;
	u32 rgb_quantization_range;
	bool is_cea_क्रमmat;
	काष्ठा delayed_work delayed_work_enable_hotplug;
	bool restart_stdi_once;
	bool hdmi_port_a;

	/* i2c clients */
	काष्ठा i2c_client *i2c_sdp_io;
	काष्ठा i2c_client *i2c_sdp;
	काष्ठा i2c_client *i2c_cp;
	काष्ठा i2c_client *i2c_vdp;
	काष्ठा i2c_client *i2c_afe;
	काष्ठा i2c_client *i2c_hdmi;
	काष्ठा i2c_client *i2c_repeater;
	काष्ठा i2c_client *i2c_edid;
	काष्ठा i2c_client *i2c_infoframe;
	काष्ठा i2c_client *i2c_cec;
	काष्ठा i2c_client *i2c_avlink;

	/* controls */
	काष्ठा v4l2_ctrl *detect_tx_5v_ctrl;
	काष्ठा v4l2_ctrl *analog_sampling_phase_ctrl;
	काष्ठा v4l2_ctrl *मुक्त_run_color_ctrl_manual;
	काष्ठा v4l2_ctrl *मुक्त_run_color_ctrl;
	काष्ठा v4l2_ctrl *rgb_quantization_range_ctrl;

	काष्ठा cec_adapter *cec_adap;
	u8   cec_addr[ADV7842_MAX_ADDRS];
	u8   cec_valid_addrs;
	bool cec_enabled_adap;
पूर्ण;

/* Unsupported timings. This device cannot support 720p30. */
अटल स्थिर काष्ठा v4l2_dv_timings adv7842_timings_exceptions[] = अणु
	V4L2_DV_BT_CEA_1280X720P30,
	अणु पूर्ण
पूर्ण;

अटल bool adv7842_check_dv_timings(स्थिर काष्ठा v4l2_dv_timings *t, व्योम *hdl)
अणु
	पूर्णांक i;

	क्रम (i = 0; adv7842_timings_exceptions[i].bt.width; i++)
		अगर (v4l2_match_dv_timings(t, adv7842_timings_exceptions + i, 0, false))
			वापस false;
	वापस true;
पूर्ण

काष्ठा adv7842_video_standards अणु
	काष्ठा v4l2_dv_timings timings;
	u8 vid_std;
	u8 v_freq;
पूर्ण;

/* sorted by number of lines */
अटल स्थिर काष्ठा adv7842_video_standards adv7842_prim_mode_comp[] = अणु
	/* अणु V4L2_DV_BT_CEA_720X480P59_94, 0x0a, 0x00 पूर्ण, TODO flickering */
	अणु V4L2_DV_BT_CEA_720X576P50, 0x0b, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P50, 0x19, 0x01 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P60, 0x19, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P24, 0x1e, 0x04 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P25, 0x1e, 0x03 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P30, 0x1e, 0x02 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P50, 0x1e, 0x01 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P60, 0x1e, 0x00 पूर्ण,
	/* TODO add 1920x1080P60_RB (CVT timing) */
	अणु पूर्ण,
पूर्ण;

/* sorted by number of lines */
अटल स्थिर काष्ठा adv7842_video_standards adv7842_prim_mode_gr[] = अणु
	अणु V4L2_DV_BT_DMT_640X480P60, 0x08, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P72, 0x09, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P75, 0x0a, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P85, 0x0b, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P56, 0x00, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P60, 0x01, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P72, 0x02, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P75, 0x03, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P85, 0x04, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P60, 0x0c, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P70, 0x0d, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P75, 0x0e, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P85, 0x0f, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1280X1024P60, 0x05, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1280X1024P75, 0x06, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1360X768P60, 0x12, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1366X768P60, 0x13, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1400X1050P60, 0x14, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1400X1050P75, 0x15, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1600X1200P60, 0x16, 0x00 पूर्ण, /* TODO not tested */
	/* TODO add 1600X1200P60_RB (not a DMT timing) */
	अणु V4L2_DV_BT_DMT_1680X1050P60, 0x18, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1920X1200P60_RB, 0x19, 0x00 पूर्ण, /* TODO not tested */
	अणु पूर्ण,
पूर्ण;

/* sorted by number of lines */
अटल स्थिर काष्ठा adv7842_video_standards adv7842_prim_mode_hdmi_comp[] = अणु
	अणु V4L2_DV_BT_CEA_720X480P59_94, 0x0a, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_720X576P50, 0x0b, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P50, 0x13, 0x01 पूर्ण,
	अणु V4L2_DV_BT_CEA_1280X720P60, 0x13, 0x00 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P24, 0x1e, 0x04 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P25, 0x1e, 0x03 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P30, 0x1e, 0x02 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P50, 0x1e, 0x01 पूर्ण,
	अणु V4L2_DV_BT_CEA_1920X1080P60, 0x1e, 0x00 पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* sorted by number of lines */
अटल स्थिर काष्ठा adv7842_video_standards adv7842_prim_mode_hdmi_gr[] = अणु
	अणु V4L2_DV_BT_DMT_640X480P60, 0x08, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P72, 0x09, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P75, 0x0a, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_640X480P85, 0x0b, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P56, 0x00, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P60, 0x01, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P72, 0x02, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P75, 0x03, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_800X600P85, 0x04, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P60, 0x0c, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P70, 0x0d, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P75, 0x0e, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1024X768P85, 0x0f, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1280X1024P60, 0x05, 0x00 पूर्ण,
	अणु V4L2_DV_BT_DMT_1280X1024P75, 0x06, 0x00 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_event adv7842_ev_fmt = अणु
	.type = V4L2_EVENT_SOURCE_CHANGE,
	.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल अंतरभूत काष्ठा adv7842_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv7842_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा adv7842_state, hdl)->sd;
पूर्ण

अटल अंतरभूत अचिन्हित hblanking(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_BLANKING_WIDTH(t);
पूर्ण

अटल अंतरभूत अचिन्हित htotal(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_FRAME_WIDTH(t);
पूर्ण

अटल अंतरभूत अचिन्हित vblanking(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_BLANKING_HEIGHT(t);
पूर्ण

अटल अंतरभूत अचिन्हित vtotal(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_FRAME_HEIGHT(t);
पूर्ण


/* ----------------------------------------------------------------------- */

अटल s32 adv_smbus_पढ़ो_byte_data_check(काष्ठा i2c_client *client,
					  u8 command, bool check)
अणु
	जोड़ i2c_smbus_data data;

	अगर (!i2c_smbus_xfer(client->adapter, client->addr, client->flags,
			    I2C_SMBUS_READ, command,
			    I2C_SMBUS_BYTE_DATA, &data))
		वापस data.byte;
	अगर (check)
		v4l_err(client, "error reading %02x, %02x\n",
			client->addr, command);
	वापस -EIO;
पूर्ण

अटल s32 adv_smbus_पढ़ो_byte_data(काष्ठा i2c_client *client, u8 command)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांक ret = adv_smbus_पढ़ो_byte_data_check(client, command, true);

		अगर (ret >= 0) अणु
			अगर (i)
				v4l_err(client, "read ok after %d retries\n", i);
			वापस ret;
		पूर्ण
	पूर्ण
	v4l_err(client, "read failed\n");
	वापस -EIO;
पूर्ण

अटल s32 adv_smbus_ग_लिखो_byte_data(काष्ठा i2c_client *client,
				     u8 command, u8 value)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक err;
	पूर्णांक i;

	data.byte = value;
	क्रम (i = 0; i < 3; i++) अणु
		err = i2c_smbus_xfer(client->adapter, client->addr,
				     client->flags,
				     I2C_SMBUS_WRITE, command,
				     I2C_SMBUS_BYTE_DATA, &data);
		अगर (!err)
			अवरोध;
	पूर्ण
	अगर (err < 0)
		v4l_err(client, "error writing %02x, %02x, %02x\n",
			client->addr, command, value);
	वापस err;
पूर्ण

अटल व्योम adv_smbus_ग_लिखो_byte_no_check(काष्ठा i2c_client *client,
					  u8 command, u8 value)
अणु
	जोड़ i2c_smbus_data data;
	data.byte = value;

	i2c_smbus_xfer(client->adapter, client->addr,
		       client->flags,
		       I2C_SMBUS_WRITE, command,
		       I2C_SMBUS_BYTE_DATA, &data);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक io_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस adv_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक io_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस adv_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक io_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस io_ग_लिखो(sd, reg, (io_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक io_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd,
				   u8 reg, u8 mask, u8 val)
अणु
	वापस io_ग_लिखो(sd, reg, (io_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक avlink_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_avlink, reg);
पूर्ण

अटल अंतरभूत पूर्णांक avlink_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_avlink, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cec_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_cec, reg);
पूर्ण

अटल अंतरभूत पूर्णांक cec_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_cec, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cec_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस cec_ग_लिखो(sd, reg, (cec_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक infoframe_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_infoframe, reg);
पूर्ण

अटल अंतरभूत पूर्णांक infoframe_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_infoframe, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक sdp_io_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_sdp_io, reg);
पूर्ण

अटल अंतरभूत पूर्णांक sdp_io_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_sdp_io, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक sdp_io_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस sdp_io_ग_लिखो(sd, reg, (sdp_io_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक sdp_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_sdp, reg);
पूर्ण

अटल अंतरभूत पूर्णांक sdp_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_sdp, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक sdp_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस sdp_ग_लिखो(sd, reg, (sdp_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक afe_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_afe, reg);
पूर्ण

अटल अंतरभूत पूर्णांक afe_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_afe, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक afe_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस afe_ग_लिखो(sd, reg, (afe_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक rep_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_repeater, reg);
पूर्ण

अटल अंतरभूत पूर्णांक rep_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_repeater, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक rep_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस rep_ग_लिखो(sd, reg, (rep_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक edid_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_edid, reg);
पूर्ण

अटल अंतरभूत पूर्णांक edid_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_edid, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक hdmi_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_hdmi, reg);
पूर्ण

अटल अंतरभूत पूर्णांक hdmi_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_hdmi, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक hdmi_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस hdmi_ग_लिखो(sd, reg, (hdmi_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक cp_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_cp, reg);
पूर्ण

अटल अंतरभूत पूर्णांक cp_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_cp, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cp_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस cp_ग_लिखो(sd, reg, (cp_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक vdp_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_vdp, reg);
पूर्ण

अटल अंतरभूत पूर्णांक vdp_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस adv_smbus_ग_लिखो_byte_data(state->i2c_vdp, reg, val);
पूर्ण

अटल व्योम मुख्य_reset(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	adv_smbus_ग_लिखो_byte_no_check(client, 0xff, 0x80);

	mdelay(5);
पूर्ण

/* -----------------------------------------------------------------------------
 * Format helpers
 */

अटल स्थिर काष्ठा adv7842_क्रमmat_info adv7842_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_RGB888_1X24, ADV7842_OP_CH_SEL_RGB, true, false,
	  ADV7842_OP_MODE_SEL_SDR_444 | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, ADV7842_OP_CH_SEL_RGB, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422 | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, ADV7842_OP_CH_SEL_RGB, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422 | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV10_2X10, ADV7842_OP_CH_SEL_RGB, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422 | ADV7842_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU10_2X10, ADV7842_OP_CH_SEL_RGB, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422 | ADV7842_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV12_2X12, ADV7842_OP_CH_SEL_RGB, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422 | ADV7842_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU12_2X12, ADV7842_OP_CH_SEL_RGB, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422 | ADV7842_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, ADV7842_OP_CH_SEL_RBG, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1X16, ADV7842_OP_CH_SEL_RBG, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, ADV7842_OP_CH_SEL_RGB, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1X16, ADV7842_OP_CH_SEL_RGB, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY10_1X20, ADV7842_OP_CH_SEL_RBG, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY10_1X20, ADV7842_OP_CH_SEL_RBG, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV10_1X20, ADV7842_OP_CH_SEL_RGB, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU10_1X20, ADV7842_OP_CH_SEL_RGB, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY12_1X24, ADV7842_OP_CH_SEL_RBG, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY12_1X24, ADV7842_OP_CH_SEL_RBG, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV12_1X24, ADV7842_OP_CH_SEL_RGB, false, false,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU12_1X24, ADV7842_OP_CH_SEL_RGB, false, true,
	  ADV7842_OP_MODE_SEL_SDR_422_2X | ADV7842_OP_FORMAT_SEL_12BIT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv7842_क्रमmat_info *
adv7842_क्रमmat_info(काष्ठा adv7842_state *state, u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adv7842_क्रमmats); ++i) अणु
		अगर (adv7842_क्रमmats[i].code == code)
			वापस &adv7842_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत bool is_analog_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस ((state->mode == ADV7842_MODE_RGB) ||
		(state->mode == ADV7842_MODE_COMP));
पूर्ण

अटल अंतरभूत bool is_digital_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	वापस state->mode == ADV7842_MODE_HDMI;
पूर्ण

अटल स्थिर काष्ठा v4l2_dv_timings_cap adv7842_timings_cap_analog = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1200, 25000000, 170000000,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

अटल स्थिर काष्ठा v4l2_dv_timings_cap adv7842_timings_cap_digital = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1200, 25000000, 225000000,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा v4l2_dv_timings_cap *
adv7842_get_dv_timings_cap(काष्ठा v4l2_subdev *sd)
अणु
	वापस is_digital_input(sd) ? &adv7842_timings_cap_digital :
				      &adv7842_timings_cap_analog;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल u16 adv7842_पढ़ो_cable_det(काष्ठा v4l2_subdev *sd)
अणु
	u8 reg = io_पढ़ो(sd, 0x6f);
	u16 val = 0;

	अगर (reg & 0x02)
		val |= 1; /* port A */
	अगर (reg & 0x01)
		val |= 2; /* port B */
	वापस val;
पूर्ण

अटल व्योम adv7842_delayed_work_enable_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा adv7842_state *state = container_of(dwork,
			काष्ठा adv7842_state, delayed_work_enable_hotplug);
	काष्ठा v4l2_subdev *sd = &state->sd;
	पूर्णांक present = state->hdmi_edid.present;
	u8 mask = 0;

	v4l2_dbg(2, debug, sd, "%s: enable hotplug on ports: 0x%x\n",
			__func__, present);

	अगर (present & (0x04 << ADV7842_EDID_PORT_A))
		mask |= 0x20;
	अगर (present & (0x04 << ADV7842_EDID_PORT_B))
		mask |= 0x10;
	io_ग_लिखो_and_or(sd, 0x20, 0xcf, mask);
पूर्ण

अटल पूर्णांक edid_ग_लिखो_vga_segment(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा adv7842_state *state = to_state(sd);
	स्थिर u8 *edid = state->vga_edid.edid;
	u32 blocks = state->vga_edid.blocks;
	पूर्णांक err = 0;
	पूर्णांक i;

	v4l2_dbg(2, debug, sd, "%s: write EDID on VGA port\n", __func__);

	/* HPA disable on port A and B */
	io_ग_लिखो_and_or(sd, 0x20, 0xcf, 0x00);

	/* Disable I2C access to पूर्णांकernal EDID ram from VGA DDC port */
	rep_ग_लिखो_and_or(sd, 0x7f, 0x7f, 0x00);

	/* edid segment poपूर्णांकer '1' क्रम VGA port */
	rep_ग_लिखो_and_or(sd, 0x77, 0xef, 0x10);

	क्रम (i = 0; !err && i < blocks * 128; i += I2C_SMBUS_BLOCK_MAX)
		err = i2c_smbus_ग_लिखो_i2c_block_data(state->i2c_edid, i,
						     I2C_SMBUS_BLOCK_MAX,
						     edid + i);
	अगर (err)
		वापस err;

	/* Calculates the checksums and enables I2C access
	 * to पूर्णांकernal EDID ram from VGA DDC port.
	 */
	rep_ग_लिखो_and_or(sd, 0x7f, 0x7f, 0x80);

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (rep_पढ़ो(sd, 0x79) & 0x20)
			अवरोध;
		mdelay(1);
	पूर्ण
	अगर (i == 1000) अणु
		v4l_err(client, "error enabling edid on VGA port\n");
		वापस -EIO;
	पूर्ण

	/* enable hotplug after 200 ms */
	schedule_delayed_work(&state->delayed_work_enable_hotplug, HZ / 5);

	वापस 0;
पूर्ण

अटल पूर्णांक edid_ग_लिखो_hdmi_segment(काष्ठा v4l2_subdev *sd, u8 port)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा adv7842_state *state = to_state(sd);
	स्थिर u8 *edid = state->hdmi_edid.edid;
	u32 blocks = state->hdmi_edid.blocks;
	पूर्णांक spa_loc;
	u16 pa, parent_pa;
	पूर्णांक err = 0;
	पूर्णांक i;

	v4l2_dbg(2, debug, sd, "%s: write EDID on port %c\n",
			__func__, (port == ADV7842_EDID_PORT_A) ? 'A' : 'B');

	/* HPA disable on port A and B */
	io_ग_लिखो_and_or(sd, 0x20, 0xcf, 0x00);

	/* Disable I2C access to पूर्णांकernal EDID ram from HDMI DDC ports */
	rep_ग_लिखो_and_or(sd, 0x77, 0xf3, 0x00);

	अगर (!state->hdmi_edid.present) अणु
		cec_phys_addr_invalidate(state->cec_adap);
		वापस 0;
	पूर्ण

	pa = v4l2_get_edid_phys_addr(edid, blocks * 128, &spa_loc);
	err = v4l2_phys_addr_validate(pa, &parent_pa, शून्य);
	अगर (err)
		वापस err;

	अगर (!spa_loc) अणु
		/*
		 * There is no SPA, so just set spa_loc to 128 and pa to whatever
		 * data is there.
		 */
		spa_loc = 128;
		pa = (edid[spa_loc] << 8) | edid[spa_loc + 1];
	पूर्ण

	/* edid segment poपूर्णांकer '0' क्रम HDMI ports */
	rep_ग_लिखो_and_or(sd, 0x77, 0xef, 0x00);

	क्रम (i = 0; !err && i < blocks * 128; i += I2C_SMBUS_BLOCK_MAX)
		err = i2c_smbus_ग_लिखो_i2c_block_data(state->i2c_edid, i,
						     I2C_SMBUS_BLOCK_MAX, edid + i);
	अगर (err)
		वापस err;

	अगर (port == ADV7842_EDID_PORT_A) अणु
		rep_ग_लिखो(sd, 0x72, pa >> 8);
		rep_ग_लिखो(sd, 0x73, pa & 0xff);
	पूर्ण अन्यथा अणु
		rep_ग_लिखो(sd, 0x74, pa >> 8);
		rep_ग_लिखो(sd, 0x75, pa & 0xff);
	पूर्ण
	rep_ग_लिखो(sd, 0x76, spa_loc & 0xff);
	rep_ग_लिखो_and_or(sd, 0x77, 0xbf, (spa_loc >> 2) & 0x40);

	/* Calculates the checksums and enables I2C access to पूर्णांकernal
	 * EDID ram from HDMI DDC ports
	 */
	rep_ग_लिखो_and_or(sd, 0x77, 0xf3, state->hdmi_edid.present);

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (rep_पढ़ो(sd, 0x7d) & state->hdmi_edid.present)
			अवरोध;
		mdelay(1);
	पूर्ण
	अगर (i == 1000) अणु
		v4l_err(client, "error enabling edid on port %c\n",
				(port == ADV7842_EDID_PORT_A) ? 'A' : 'B');
		वापस -EIO;
	पूर्ण
	cec_s_phys_addr(state->cec_adap, parent_pa, false);

	/* enable hotplug after 200 ms */
	schedule_delayed_work(&state->delayed_work_enable_hotplug, HZ / 5);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल व्योम adv7842_inv_रेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_info(sd, "0x000-0x0ff: IO Map\n");
	v4l2_info(sd, "0x100-0x1ff: AVLink Map\n");
	v4l2_info(sd, "0x200-0x2ff: CEC Map\n");
	v4l2_info(sd, "0x300-0x3ff: InfoFrame Map\n");
	v4l2_info(sd, "0x400-0x4ff: SDP_IO Map\n");
	v4l2_info(sd, "0x500-0x5ff: SDP Map\n");
	v4l2_info(sd, "0x600-0x6ff: AFE Map\n");
	v4l2_info(sd, "0x700-0x7ff: Repeater Map\n");
	v4l2_info(sd, "0x800-0x8ff: EDID Map\n");
	v4l2_info(sd, "0x900-0x9ff: HDMI Map\n");
	v4l2_info(sd, "0xa00-0xaff: CP Map\n");
	v4l2_info(sd, "0xb00-0xbff: VDP Map\n");
पूर्ण

अटल पूर्णांक adv7842_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->size = 1;
	चयन (reg->reg >> 8) अणु
	हाल 0:
		reg->val = io_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 1:
		reg->val = avlink_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 2:
		reg->val = cec_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 3:
		reg->val = infoframe_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 4:
		reg->val = sdp_io_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 5:
		reg->val = sdp_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 6:
		reg->val = afe_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 7:
		reg->val = rep_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 8:
		reg->val = edid_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 9:
		reg->val = hdmi_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 0xa:
		reg->val = cp_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	हाल 0xb:
		reg->val = vdp_पढ़ो(sd, reg->reg & 0xff);
		अवरोध;
	शेष:
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv7842_inv_रेजिस्टर(sd);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
		स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	u8 val = reg->val & 0xff;

	चयन (reg->reg >> 8) अणु
	हाल 0:
		io_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 1:
		avlink_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 2:
		cec_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 3:
		infoframe_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 4:
		sdp_io_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 5:
		sdp_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 6:
		afe_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 7:
		rep_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 8:
		edid_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 9:
		hdmi_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 0xa:
		cp_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	हाल 0xb:
		vdp_ग_लिखो(sd, reg->reg & 0xff, val);
		अवरोध;
	शेष:
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv7842_inv_रेजिस्टर(sd);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adv7842_s_detect_tx_5v_ctrl(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	u16 cable_det = adv7842_पढ़ो_cable_det(sd);

	v4l2_dbg(1, debug, sd, "%s: 0x%x\n", __func__, cable_det);

	वापस v4l2_ctrl_s_ctrl(state->detect_tx_5v_ctrl, cable_det);
पूर्ण

अटल पूर्णांक find_and_set_predefined_video_timings(काष्ठा v4l2_subdev *sd,
		u8 prim_mode,
		स्थिर काष्ठा adv7842_video_standards *predef_vid_timings,
		स्थिर काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक i;

	क्रम (i = 0; predef_vid_timings[i].timings.bt.width; i++) अणु
		अगर (!v4l2_match_dv_timings(timings, &predef_vid_timings[i].timings,
				  is_digital_input(sd) ? 250000 : 1000000, false))
			जारी;
		/* video std */
		io_ग_लिखो(sd, 0x00, predef_vid_timings[i].vid_std);
		/* v_freq and prim mode */
		io_ग_लिखो(sd, 0x01, (predef_vid_timings[i].v_freq << 4) + prim_mode);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक configure_predefined_video_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	पूर्णांक err;

	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	/* reset to शेष values */
	io_ग_लिखो(sd, 0x16, 0x43);
	io_ग_लिखो(sd, 0x17, 0x5a);
	/* disable embedded syncs क्रम स्वतः graphics mode */
	cp_ग_लिखो_and_or(sd, 0x81, 0xef, 0x00);
	cp_ग_लिखो(sd, 0x26, 0x00);
	cp_ग_लिखो(sd, 0x27, 0x00);
	cp_ग_लिखो(sd, 0x28, 0x00);
	cp_ग_लिखो(sd, 0x29, 0x00);
	cp_ग_लिखो(sd, 0x8f, 0x40);
	cp_ग_लिखो(sd, 0x90, 0x00);
	cp_ग_लिखो(sd, 0xa5, 0x00);
	cp_ग_लिखो(sd, 0xa6, 0x00);
	cp_ग_लिखो(sd, 0xa7, 0x00);
	cp_ग_लिखो(sd, 0xab, 0x00);
	cp_ग_लिखो(sd, 0xac, 0x00);

	चयन (state->mode) अणु
	हाल ADV7842_MODE_COMP:
	हाल ADV7842_MODE_RGB:
		err = find_and_set_predefined_video_timings(sd,
				0x01, adv7842_prim_mode_comp, timings);
		अगर (err)
			err = find_and_set_predefined_video_timings(sd,
					0x02, adv7842_prim_mode_gr, timings);
		अवरोध;
	हाल ADV7842_MODE_HDMI:
		err = find_and_set_predefined_video_timings(sd,
				0x05, adv7842_prim_mode_hdmi_comp, timings);
		अगर (err)
			err = find_and_set_predefined_video_timings(sd,
					0x06, adv7842_prim_mode_hdmi_gr, timings);
		अवरोध;
	शेष:
		v4l2_dbg(2, debug, sd, "%s: Unknown mode %d\n",
				__func__, state->mode);
		err = -1;
		अवरोध;
	पूर्ण


	वापस err;
पूर्ण

अटल व्योम configure_custom_video_timings(काष्ठा v4l2_subdev *sd,
		स्थिर काष्ठा v4l2_bt_timings *bt)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u32 width = htotal(bt);
	u32 height = vtotal(bt);
	u16 cp_start_sav = bt->hsync + bt->hbackporch - 4;
	u16 cp_start_eav = width - bt->hfrontporch;
	u16 cp_start_vbi = height - bt->vfrontporch + 1;
	u16 cp_end_vbi = bt->vsync + bt->vbackporch + 1;
	u16 ch1_fr_ll = (((u32)bt->pixelघड़ी / 100) > 0) ?
		((width * (ADV7842_fsc / 100)) / ((u32)bt->pixelघड़ी / 100)) : 0;
	स्थिर u8 pll[2] = अणु
		0xc0 | ((width >> 8) & 0x1f),
		width & 0xff
	पूर्ण;

	v4l2_dbg(2, debug, sd, "%s\n", __func__);

	चयन (state->mode) अणु
	हाल ADV7842_MODE_COMP:
	हाल ADV7842_MODE_RGB:
		/* स्वतः graphics */
		io_ग_लिखो(sd, 0x00, 0x07); /* video std */
		io_ग_लिखो(sd, 0x01, 0x02); /* prim mode */
		/* enable embedded syncs क्रम स्वतः graphics mode */
		cp_ग_लिखो_and_or(sd, 0x81, 0xef, 0x10);

		/* Should only be set in स्वतः-graphics mode [REF_02, p. 91-92] */
		/* setup PLL_DIV_MAN_EN and PLL_DIV_RATIO */
		/* IO-map reg. 0x16 and 0x17 should be written in sequence */
		अगर (i2c_smbus_ग_लिखो_i2c_block_data(client, 0x16, 2, pll)) अणु
			v4l2_err(sd, "writing to reg 0x16 and 0x17 failed\n");
			अवरोध;
		पूर्ण

		/* active video - horizontal timing */
		cp_ग_लिखो(sd, 0x26, (cp_start_sav >> 8) & 0xf);
		cp_ग_लिखो(sd, 0x27, (cp_start_sav & 0xff));
		cp_ग_लिखो(sd, 0x28, (cp_start_eav >> 8) & 0xf);
		cp_ग_लिखो(sd, 0x29, (cp_start_eav & 0xff));

		/* active video - vertical timing */
		cp_ग_लिखो(sd, 0xa5, (cp_start_vbi >> 4) & 0xff);
		cp_ग_लिखो(sd, 0xa6, ((cp_start_vbi & 0xf) << 4) |
					((cp_end_vbi >> 8) & 0xf));
		cp_ग_लिखो(sd, 0xa7, cp_end_vbi & 0xff);
		अवरोध;
	हाल ADV7842_MODE_HDMI:
		/* set शेष prim_mode/vid_std क्रम HDMI
		   according to [REF_03, c. 4.2] */
		io_ग_लिखो(sd, 0x00, 0x02); /* video std */
		io_ग_लिखो(sd, 0x01, 0x06); /* prim mode */
		अवरोध;
	शेष:
		v4l2_dbg(2, debug, sd, "%s: Unknown mode %d\n",
				__func__, state->mode);
		अवरोध;
	पूर्ण

	cp_ग_लिखो(sd, 0x8f, (ch1_fr_ll >> 8) & 0x7);
	cp_ग_लिखो(sd, 0x90, ch1_fr_ll & 0xff);
	cp_ग_लिखो(sd, 0xab, (height >> 4) & 0xff);
	cp_ग_लिखो(sd, 0xac, (height & 0x0f) << 4);
पूर्ण

अटल व्योम adv7842_set_offset(काष्ठा v4l2_subdev *sd, bool स्वतः_offset, u16 offset_a, u16 offset_b, u16 offset_c)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	u8 offset_buf[4];

	अगर (स्वतः_offset) अणु
		offset_a = 0x3ff;
		offset_b = 0x3ff;
		offset_c = 0x3ff;
	पूर्ण

	v4l2_dbg(2, debug, sd, "%s: %s offset: a = 0x%x, b = 0x%x, c = 0x%x\n",
		 __func__, स्वतः_offset ? "Auto" : "Manual",
		 offset_a, offset_b, offset_c);

	offset_buf[0]= (cp_पढ़ो(sd, 0x77) & 0xc0) | ((offset_a & 0x3f0) >> 4);
	offset_buf[1] = ((offset_a & 0x00f) << 4) | ((offset_b & 0x3c0) >> 6);
	offset_buf[2] = ((offset_b & 0x03f) << 2) | ((offset_c & 0x300) >> 8);
	offset_buf[3] = offset_c & 0x0ff;

	/* Registers must be written in this order with no i2c access in between */
	अगर (i2c_smbus_ग_लिखो_i2c_block_data(state->i2c_cp, 0x77, 4, offset_buf))
		v4l2_err(sd, "%s: i2c error writing to CP reg 0x77, 0x78, 0x79, 0x7a\n", __func__);
पूर्ण

अटल व्योम adv7842_set_gain(काष्ठा v4l2_subdev *sd, bool स्वतः_gain, u16 gain_a, u16 gain_b, u16 gain_c)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	u8 gain_buf[4];
	u8 gain_man = 1;
	u8 agc_mode_man = 1;

	अगर (स्वतः_gain) अणु
		gain_man = 0;
		agc_mode_man = 0;
		gain_a = 0x100;
		gain_b = 0x100;
		gain_c = 0x100;
	पूर्ण

	v4l2_dbg(2, debug, sd, "%s: %s gain: a = 0x%x, b = 0x%x, c = 0x%x\n",
		 __func__, स्वतः_gain ? "Auto" : "Manual",
		 gain_a, gain_b, gain_c);

	gain_buf[0] = ((gain_man << 7) | (agc_mode_man << 6) | ((gain_a & 0x3f0) >> 4));
	gain_buf[1] = (((gain_a & 0x00f) << 4) | ((gain_b & 0x3c0) >> 6));
	gain_buf[2] = (((gain_b & 0x03f) << 2) | ((gain_c & 0x300) >> 8));
	gain_buf[3] = ((gain_c & 0x0ff));

	/* Registers must be written in this order with no i2c access in between */
	अगर (i2c_smbus_ग_लिखो_i2c_block_data(state->i2c_cp, 0x73, 4, gain_buf))
		v4l2_err(sd, "%s: i2c error writing to CP reg 0x73, 0x74, 0x75, 0x76\n", __func__);
पूर्ण

अटल व्योम set_rgb_quantization_range(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	bool rgb_output = io_पढ़ो(sd, 0x02) & 0x02;
	bool hdmi_संकेत = hdmi_पढ़ो(sd, 0x05) & 0x80;
	u8 y = HDMI_COLORSPACE_RGB;

	अगर (hdmi_संकेत && (io_पढ़ो(sd, 0x60) & 1))
		y = infoframe_पढ़ो(sd, 0x01) >> 5;

	v4l2_dbg(2, debug, sd, "%s: RGB quantization range: %d, RGB out: %d, HDMI: %d\n",
			__func__, state->rgb_quantization_range,
			rgb_output, hdmi_संकेत);

	adv7842_set_gain(sd, true, 0x0, 0x0, 0x0);
	adv7842_set_offset(sd, true, 0x0, 0x0, 0x0);
	io_ग_लिखो_clr_set(sd, 0x02, 0x04, rgb_output ? 0 : 4);

	चयन (state->rgb_quantization_range) अणु
	हाल V4L2_DV_RGB_RANGE_AUTO:
		अगर (state->mode == ADV7842_MODE_RGB) अणु
			/* Receiving analog RGB संकेत
			 * Set RGB full range (0-255) */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x10);
			अवरोध;
		पूर्ण

		अगर (state->mode == ADV7842_MODE_COMP) अणु
			/* Receiving analog YPbPr संकेत
			 * Set स्वतःmode */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0xf0);
			अवरोध;
		पूर्ण

		अगर (hdmi_संकेत) अणु
			/* Receiving HDMI संकेत
			 * Set स्वतःmode */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0xf0);
			अवरोध;
		पूर्ण

		/* Receiving DVI-D संकेत
		 * ADV7842 selects RGB limited range regardless of
		 * input क्रमmat (CE/IT) in स्वतःmatic mode */
		अगर (state->timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
			/* RGB limited range (16-235) */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x00);
		पूर्ण अन्यथा अणु
			/* RGB full range (0-255) */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x10);

			अगर (is_digital_input(sd) && rgb_output) अणु
				adv7842_set_offset(sd, false, 0x40, 0x40, 0x40);
			पूर्ण अन्यथा अणु
				adv7842_set_gain(sd, false, 0xe0, 0xe0, 0xe0);
				adv7842_set_offset(sd, false, 0x70, 0x70, 0x70);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल V4L2_DV_RGB_RANGE_LIMITED:
		अगर (state->mode == ADV7842_MODE_COMP) अणु
			/* YCrCb limited range (16-235) */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x20);
			अवरोध;
		पूर्ण

		अगर (y != HDMI_COLORSPACE_RGB)
			अवरोध;

		/* RGB limited range (16-235) */
		io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x00);

		अवरोध;
	हाल V4L2_DV_RGB_RANGE_FULL:
		अगर (state->mode == ADV7842_MODE_COMP) अणु
			/* YCrCb full range (0-255) */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x60);
			अवरोध;
		पूर्ण

		अगर (y != HDMI_COLORSPACE_RGB)
			अवरोध;

		/* RGB full range (0-255) */
		io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x10);

		अगर (is_analog_input(sd) || hdmi_संकेत)
			अवरोध;

		/* Adjust gain/offset क्रम DVI-D संकेतs only */
		अगर (rgb_output) अणु
			adv7842_set_offset(sd, false, 0x40, 0x40, 0x40);
		पूर्ण अन्यथा अणु
			adv7842_set_gain(sd, false, 0xe0, 0xe0, 0xe0);
			adv7842_set_offset(sd, false, 0x70, 0x70, 0x70);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक adv7842_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा adv7842_state *state = to_state(sd);

	/* TODO SDP ctrls
	   contrast/brightness/hue/मुक्त run is acting a bit strange,
	   not sure अगर sdp csc is correct.
	 */
	चयन (ctrl->id) अणु
	/* standard ctrls */
	हाल V4L2_CID_BRIGHTNESS:
		cp_ग_लिखो(sd, 0x3c, ctrl->val);
		sdp_ग_लिखो(sd, 0x14, ctrl->val);
		/* ignore lsb sdp 0x17[3:2] */
		वापस 0;
	हाल V4L2_CID_CONTRAST:
		cp_ग_लिखो(sd, 0x3a, ctrl->val);
		sdp_ग_लिखो(sd, 0x13, ctrl->val);
		/* ignore lsb sdp 0x17[1:0] */
		वापस 0;
	हाल V4L2_CID_SATURATION:
		cp_ग_लिखो(sd, 0x3b, ctrl->val);
		sdp_ग_लिखो(sd, 0x15, ctrl->val);
		/* ignore lsb sdp 0x17[5:4] */
		वापस 0;
	हाल V4L2_CID_HUE:
		cp_ग_लिखो(sd, 0x3d, ctrl->val);
		sdp_ग_लिखो(sd, 0x16, ctrl->val);
		/* ignore lsb sdp 0x17[7:6] */
		वापस 0;
		/* custom ctrls */
	हाल V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE:
		afe_ग_लिखो(sd, 0xc8, ctrl->val);
		वापस 0;
	हाल V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL:
		cp_ग_लिखो_and_or(sd, 0xbf, ~0x04, (ctrl->val << 2));
		sdp_ग_लिखो_and_or(sd, 0xdd, ~0x04, (ctrl->val << 2));
		वापस 0;
	हाल V4L2_CID_ADV_RX_FREE_RUN_COLOR: अणु
		u8 R = (ctrl->val & 0xff0000) >> 16;
		u8 G = (ctrl->val & 0x00ff00) >> 8;
		u8 B = (ctrl->val & 0x0000ff);
		/* RGB -> YUV, numerical approximation */
		पूर्णांक Y = 66 * R + 129 * G + 25 * B;
		पूर्णांक U = -38 * R - 74 * G + 112 * B;
		पूर्णांक V = 112 * R - 94 * G - 18 * B;

		/* Scale करोwn to 8 bits with rounding */
		Y = (Y + 128) >> 8;
		U = (U + 128) >> 8;
		V = (V + 128) >> 8;
		/* make U,V positive */
		Y += 16;
		U += 128;
		V += 128;

		v4l2_dbg(1, debug, sd, "R %x, G %x, B %x\n", R, G, B);
		v4l2_dbg(1, debug, sd, "Y %x, U %x, V %x\n", Y, U, V);

		/* CP */
		cp_ग_लिखो(sd, 0xc1, R);
		cp_ग_लिखो(sd, 0xc0, G);
		cp_ग_लिखो(sd, 0xc2, B);
		/* SDP */
		sdp_ग_लिखो(sd, 0xde, Y);
		sdp_ग_लिखो(sd, 0xdf, (V & 0xf0) | ((U >> 4) & 0x0f));
		वापस 0;
	पूर्ण
	हाल V4L2_CID_DV_RX_RGB_RANGE:
		state->rgb_quantization_range = ctrl->val;
		set_rgb_quantization_range(sd);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adv7842_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	अगर (ctrl->id == V4L2_CID_DV_RX_IT_CONTENT_TYPE) अणु
		ctrl->val = V4L2_DV_IT_CONTENT_TYPE_NO_ITC;
		अगर ((io_पढ़ो(sd, 0x60) & 1) && (infoframe_पढ़ो(sd, 0x03) & 0x80))
			ctrl->val = (infoframe_पढ़ो(sd, 0x05) >> 4) & 3;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool no_घातer(काष्ठा v4l2_subdev *sd)
अणु
	वापस io_पढ़ो(sd, 0x0c) & 0x24;
पूर्ण

अटल अंतरभूत bool no_cp_संकेत(काष्ठा v4l2_subdev *sd)
अणु
	वापस ((cp_पढ़ो(sd, 0xb5) & 0xd0) != 0xd0) || !(cp_पढ़ो(sd, 0xb1) & 0x80);
पूर्ण

अटल अंतरभूत bool is_hdmi(काष्ठा v4l2_subdev *sd)
अणु
	वापस hdmi_पढ़ो(sd, 0x05) & 0x80;
पूर्ण

अटल पूर्णांक adv7842_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	*status = 0;

	अगर (io_पढ़ो(sd, 0x0c) & 0x24)
		*status |= V4L2_IN_ST_NO_POWER;

	अगर (state->mode == ADV7842_MODE_SDP) अणु
		/* status from SDP block */
		अगर (!(sdp_पढ़ो(sd, 0x5A) & 0x01))
			*status |= V4L2_IN_ST_NO_SIGNAL;

		v4l2_dbg(1, debug, sd, "%s: SDP status = 0x%x\n",
				__func__, *status);
		वापस 0;
	पूर्ण
	/* status from CP block */
	अगर ((cp_पढ़ो(sd, 0xb5) & 0xd0) != 0xd0 ||
			!(cp_पढ़ो(sd, 0xb1) & 0x80))
		/* TODO channel 2 */
		*status |= V4L2_IN_ST_NO_SIGNAL;

	अगर (is_digital_input(sd) && ((io_पढ़ो(sd, 0x74) & 0x03) != 0x03))
		*status |= V4L2_IN_ST_NO_SIGNAL;

	v4l2_dbg(1, debug, sd, "%s: CP status = 0x%x\n",
			__func__, *status);

	वापस 0;
पूर्ण

काष्ठा stdi_पढ़ोback अणु
	u16 bl, lcf, lcvs;
	u8 hs_pol, vs_pol;
	bool पूर्णांकerlaced;
पूर्ण;

अटल पूर्णांक stdi2dv_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा stdi_पढ़ोback *stdi,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	u32 hfreq = (ADV7842_fsc * 8) / stdi->bl;
	u32 pix_clk;
	पूर्णांक i;

	क्रम (i = 0; v4l2_dv_timings_presets[i].bt.width; i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *bt = &v4l2_dv_timings_presets[i].bt;

		अगर (!v4l2_valid_dv_timings(&v4l2_dv_timings_presets[i],
					   adv7842_get_dv_timings_cap(sd),
					   adv7842_check_dv_timings, शून्य))
			जारी;
		अगर (vtotal(bt) != stdi->lcf + 1)
			जारी;
		अगर (bt->vsync != stdi->lcvs)
			जारी;

		pix_clk = hfreq * htotal(bt);

		अगर ((pix_clk < bt->pixelघड़ी + 1000000) &&
		    (pix_clk > bt->pixelघड़ी - 1000000)) अणु
			*timings = v4l2_dv_timings_presets[i];
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (v4l2_detect_cvt(stdi->lcf + 1, hfreq, stdi->lcvs, 0,
			(stdi->hs_pol == '+' ? V4L2_DV_HSYNC_POS_POL : 0) |
			(stdi->vs_pol == '+' ? V4L2_DV_VSYNC_POS_POL : 0),
			false, timings))
		वापस 0;
	अगर (v4l2_detect_gtf(stdi->lcf + 1, hfreq, stdi->lcvs,
			(stdi->hs_pol == '+' ? V4L2_DV_HSYNC_POS_POL : 0) |
			(stdi->vs_pol == '+' ? V4L2_DV_VSYNC_POS_POL : 0),
			false, state->aspect_ratio, timings))
		वापस 0;

	v4l2_dbg(2, debug, sd,
		"%s: No format candidate found for lcvs = %d, lcf=%d, bl = %d, %chsync, %cvsync\n",
		__func__, stdi->lcvs, stdi->lcf, stdi->bl,
		stdi->hs_pol, stdi->vs_pol);
	वापस -1;
पूर्ण

अटल पूर्णांक पढ़ो_stdi(काष्ठा v4l2_subdev *sd, काष्ठा stdi_पढ़ोback *stdi)
अणु
	u32 status;

	adv7842_g_input_status(sd, &status);
	अगर (status & V4L2_IN_ST_NO_SIGNAL) अणु
		v4l2_dbg(2, debug, sd, "%s: no signal\n", __func__);
		वापस -ENOLINK;
	पूर्ण

	stdi->bl = ((cp_पढ़ो(sd, 0xb1) & 0x3f) << 8) | cp_पढ़ो(sd, 0xb2);
	stdi->lcf = ((cp_पढ़ो(sd, 0xb3) & 0x7) << 8) | cp_पढ़ो(sd, 0xb4);
	stdi->lcvs = cp_पढ़ो(sd, 0xb3) >> 3;

	अगर ((cp_पढ़ो(sd, 0xb5) & 0x80) && ((cp_पढ़ो(sd, 0xb5) & 0x03) == 0x01)) अणु
		stdi->hs_pol = ((cp_पढ़ो(sd, 0xb5) & 0x10) ?
			((cp_पढ़ो(sd, 0xb5) & 0x08) ? '+' : '-') : 'x');
		stdi->vs_pol = ((cp_पढ़ो(sd, 0xb5) & 0x40) ?
			((cp_पढ़ो(sd, 0xb5) & 0x20) ? '+' : '-') : 'x');
	पूर्ण अन्यथा अणु
		stdi->hs_pol = 'x';
		stdi->vs_pol = 'x';
	पूर्ण
	stdi->पूर्णांकerlaced = (cp_पढ़ो(sd, 0xb1) & 0x40) ? true : false;

	अगर (stdi->lcf < 239 || stdi->bl < 8 || stdi->bl == 0x3fff) अणु
		v4l2_dbg(2, debug, sd, "%s: invalid signal\n", __func__);
		वापस -ENOLINK;
	पूर्ण

	v4l2_dbg(2, debug, sd,
		"%s: lcf (frame height - 1) = %d, bl = %d, lcvs (vsync) = %d, %chsync, %cvsync, %s\n",
		 __func__, stdi->lcf, stdi->bl, stdi->lcvs,
		 stdi->hs_pol, stdi->vs_pol,
		 stdi->पूर्णांकerlaced ? "interlaced" : "progressive");

	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->pad != 0)
		वापस -EINVAL;

	वापस v4l2_क्रमागत_dv_timings_cap(timings,
		adv7842_get_dv_timings_cap(sd), adv7842_check_dv_timings, शून्य);
पूर्ण

अटल पूर्णांक adv7842_dv_timings_cap(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (cap->pad != 0)
		वापस -EINVAL;

	*cap = *adv7842_get_dv_timings_cap(sd);
	वापस 0;
पूर्ण

/* Fill the optional fields .standards and .flags in काष्ठा v4l2_dv_timings
   अगर the क्रमmat is listed in adv7842_timings[] */
अटल व्योम adv7842_fill_optional_dv_timings_fields(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	v4l2_find_dv_timings_cap(timings, adv7842_get_dv_timings_cap(sd),
			is_digital_input(sd) ? 250000 : 1000000,
			adv7842_check_dv_timings, शून्य);
	timings->bt.flags |= V4L2_DV_FL_CAN_DETECT_REDUCED_FPS;
पूर्ण

अटल पूर्णांक adv7842_query_dv_timings(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	काष्ठा stdi_पढ़ोback stdi = अणु 0 पूर्ण;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	स_रखो(timings, 0, माप(काष्ठा v4l2_dv_timings));

	/* SDP block */
	अगर (state->mode == ADV7842_MODE_SDP)
		वापस -ENODATA;

	/* पढ़ो STDI */
	अगर (पढ़ो_stdi(sd, &stdi)) अणु
		state->restart_stdi_once = true;
		v4l2_dbg(1, debug, sd, "%s: no valid signal\n", __func__);
		वापस -ENOLINK;
	पूर्ण
	bt->पूर्णांकerlaced = stdi.पूर्णांकerlaced ?
		V4L2_DV_INTERLACED : V4L2_DV_PROGRESSIVE;
	bt->standards = V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT;

	अगर (is_digital_input(sd)) अणु
		u32 freq;

		timings->type = V4L2_DV_BT_656_1120;

		bt->width = (hdmi_पढ़ो(sd, 0x07) & 0x0f) * 256 + hdmi_पढ़ो(sd, 0x08);
		bt->height = (hdmi_पढ़ो(sd, 0x09) & 0x0f) * 256 + hdmi_पढ़ो(sd, 0x0a);
		freq = ((hdmi_पढ़ो(sd, 0x51) << 1) + (hdmi_पढ़ो(sd, 0x52) >> 7)) * 1000000;
		freq += ((hdmi_पढ़ो(sd, 0x52) & 0x7f) * 7813);
		अगर (is_hdmi(sd)) अणु
			/* adjust क्रम deep color mode */
			freq = freq * 8 / (((hdmi_पढ़ो(sd, 0x0b) & 0xc0) >> 6) * 2 + 8);
		पूर्ण
		bt->pixelघड़ी = freq;
		bt->hfrontporch = (hdmi_पढ़ो(sd, 0x20) & 0x03) * 256 +
			hdmi_पढ़ो(sd, 0x21);
		bt->hsync = (hdmi_पढ़ो(sd, 0x22) & 0x03) * 256 +
			hdmi_पढ़ो(sd, 0x23);
		bt->hbackporch = (hdmi_पढ़ो(sd, 0x24) & 0x03) * 256 +
			hdmi_पढ़ो(sd, 0x25);
		bt->vfrontporch = ((hdmi_पढ़ो(sd, 0x2a) & 0x1f) * 256 +
			hdmi_पढ़ो(sd, 0x2b)) / 2;
		bt->vsync = ((hdmi_पढ़ो(sd, 0x2e) & 0x1f) * 256 +
			hdmi_पढ़ो(sd, 0x2f)) / 2;
		bt->vbackporch = ((hdmi_पढ़ो(sd, 0x32) & 0x1f) * 256 +
			hdmi_पढ़ो(sd, 0x33)) / 2;
		bt->polarities = ((hdmi_पढ़ो(sd, 0x05) & 0x10) ? V4L2_DV_VSYNC_POS_POL : 0) |
			((hdmi_पढ़ो(sd, 0x05) & 0x20) ? V4L2_DV_HSYNC_POS_POL : 0);
		अगर (bt->पूर्णांकerlaced == V4L2_DV_INTERLACED) अणु
			bt->height += (hdmi_पढ़ो(sd, 0x0b) & 0x0f) * 256 +
					hdmi_पढ़ो(sd, 0x0c);
			bt->il_vfrontporch = ((hdmi_पढ़ो(sd, 0x2c) & 0x1f) * 256 +
					hdmi_पढ़ो(sd, 0x2d)) / 2;
			bt->il_vsync = ((hdmi_पढ़ो(sd, 0x30) & 0x1f) * 256 +
					hdmi_पढ़ो(sd, 0x31)) / 2;
			bt->il_vbackporch = ((hdmi_पढ़ो(sd, 0x34) & 0x1f) * 256 +
					hdmi_पढ़ो(sd, 0x35)) / 2;
		पूर्ण अन्यथा अणु
			bt->il_vfrontporch = 0;
			bt->il_vsync = 0;
			bt->il_vbackporch = 0;
		पूर्ण
		adv7842_fill_optional_dv_timings_fields(sd, timings);
		अगर ((timings->bt.flags & V4L2_DV_FL_CAN_REDUCE_FPS) &&
		    freq < bt->pixelघड़ी) अणु
			u32 reduced_freq = ((u32)bt->pixelघड़ी / 1001) * 1000;
			u32 delta_freq = असल(freq - reduced_freq);

			अगर (delta_freq < ((u32)bt->pixelघड़ी - reduced_freq) / 2)
				timings->bt.flags |= V4L2_DV_FL_REDUCED_FPS;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* find क्रमmat
		 * Since LCVS values are inaccurate [REF_03, p. 339-340],
		 * stdi2dv_timings() is called with lcvs +-1 अगर the first attempt fails.
		 */
		अगर (!stdi2dv_timings(sd, &stdi, timings))
			जाओ found;
		stdi.lcvs += 1;
		v4l2_dbg(1, debug, sd, "%s: lcvs + 1 = %d\n", __func__, stdi.lcvs);
		अगर (!stdi2dv_timings(sd, &stdi, timings))
			जाओ found;
		stdi.lcvs -= 2;
		v4l2_dbg(1, debug, sd, "%s: lcvs - 1 = %d\n", __func__, stdi.lcvs);
		अगर (stdi2dv_timings(sd, &stdi, timings)) अणु
			/*
			 * The STDI block may measure wrong values, especially
			 * क्रम lcvs and lcf. If the driver can not find any
			 * valid timing, the STDI block is restarted to measure
			 * the video timings again. The function will वापस an
			 * error, but the restart of STDI will generate a new
			 * STDI पूर्णांकerrupt and the क्रमmat detection process will
			 * restart.
			 */
			अगर (state->restart_stdi_once) अणु
				v4l2_dbg(1, debug, sd, "%s: restart STDI\n", __func__);
				/* TODO restart STDI क्रम Sync Channel 2 */
				/* enter one-shot mode */
				cp_ग_लिखो_and_or(sd, 0x86, 0xf9, 0x00);
				/* trigger STDI restart */
				cp_ग_लिखो_and_or(sd, 0x86, 0xf9, 0x04);
				/* reset to continuous mode */
				cp_ग_लिखो_and_or(sd, 0x86, 0xf9, 0x02);
				state->restart_stdi_once = false;
				वापस -ENOLINK;
			पूर्ण
			v4l2_dbg(1, debug, sd, "%s: format not supported\n", __func__);
			वापस -दुस्फल;
		पूर्ण
		state->restart_stdi_once = true;
	पूर्ण
found:

	अगर (debug > 1)
		v4l2_prपूर्णांक_dv_timings(sd->name, "adv7842_query_dv_timings:",
				timings, true);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_s_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा v4l2_bt_timings *bt;
	पूर्णांक err;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (state->mode == ADV7842_MODE_SDP)
		वापस -ENODATA;

	अगर (v4l2_match_dv_timings(&state->timings, timings, 0, false)) अणु
		v4l2_dbg(1, debug, sd, "%s: no change\n", __func__);
		वापस 0;
	पूर्ण

	bt = &timings->bt;

	अगर (!v4l2_valid_dv_timings(timings, adv7842_get_dv_timings_cap(sd),
				   adv7842_check_dv_timings, शून्य))
		वापस -दुस्फल;

	adv7842_fill_optional_dv_timings_fields(sd, timings);

	state->timings = *timings;

	cp_ग_लिखो(sd, 0x91, bt->पूर्णांकerlaced ? 0x40 : 0x00);

	/* Use prim_mode and vid_std when available */
	err = configure_predefined_video_timings(sd, timings);
	अगर (err) अणु
		/* custom settings when the video क्रमmat
		  करोes not have prim_mode/vid_std */
		configure_custom_video_timings(sd, bt);
	पूर्ण

	set_rgb_quantization_range(sd);


	अगर (debug > 1)
		v4l2_prपूर्णांक_dv_timings(sd->name, "adv7842_s_dv_timings: ",
				      timings, true);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_g_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	अगर (state->mode == ADV7842_MODE_SDP)
		वापस -ENODATA;
	*timings = state->timings;
	वापस 0;
पूर्ण

अटल व्योम enable_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	set_rgb_quantization_range(sd);
	चयन (state->mode) अणु
	हाल ADV7842_MODE_SDP:
	हाल ADV7842_MODE_COMP:
	हाल ADV7842_MODE_RGB:
		io_ग_लिखो(sd, 0x15, 0xb0);   /* Disable Tristate of Pins (no audio) */
		अवरोध;
	हाल ADV7842_MODE_HDMI:
		hdmi_ग_लिखो(sd, 0x01, 0x00); /* Enable HDMI घड़ी terminators */
		io_ग_लिखो(sd, 0x15, 0xa0);   /* Disable Tristate of Pins */
		hdmi_ग_लिखो_and_or(sd, 0x1a, 0xef, 0x00); /* Unmute audio */
		अवरोध;
	शेष:
		v4l2_dbg(2, debug, sd, "%s: Unknown mode %d\n",
			 __func__, state->mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम disable_input(काष्ठा v4l2_subdev *sd)
अणु
	hdmi_ग_लिखो_and_or(sd, 0x1a, 0xef, 0x10); /* Mute audio [REF_01, c. 2.2.2] */
	msleep(16); /* 512 samples with >= 32 kHz sample rate [REF_03, c. 8.29] */
	io_ग_लिखो(sd, 0x15, 0xbe);   /* Tristate all outमाला_दो from video core */
	hdmi_ग_लिखो(sd, 0x01, 0x78); /* Disable HDMI घड़ी terminators */
पूर्ण

अटल व्योम sdp_csc_coeff(काष्ठा v4l2_subdev *sd,
			  स्थिर काष्ठा adv7842_sdp_csc_coeff *c)
अणु
	/* csc स्वतः/manual */
	sdp_io_ग_लिखो_and_or(sd, 0xe0, 0xbf, c->manual ? 0x00 : 0x40);

	अगर (!c->manual)
		वापस;

	/* csc scaling */
	sdp_io_ग_लिखो_and_or(sd, 0xe0, 0x7f, c->scaling == 2 ? 0x80 : 0x00);

	/* A coeff */
	sdp_io_ग_लिखो_and_or(sd, 0xe0, 0xe0, c->A1 >> 8);
	sdp_io_ग_लिखो(sd, 0xe1, c->A1);
	sdp_io_ग_लिखो_and_or(sd, 0xe2, 0xe0, c->A2 >> 8);
	sdp_io_ग_लिखो(sd, 0xe3, c->A2);
	sdp_io_ग_लिखो_and_or(sd, 0xe4, 0xe0, c->A3 >> 8);
	sdp_io_ग_लिखो(sd, 0xe5, c->A3);

	/* A scale */
	sdp_io_ग_लिखो_and_or(sd, 0xe6, 0x80, c->A4 >> 8);
	sdp_io_ग_लिखो(sd, 0xe7, c->A4);

	/* B coeff */
	sdp_io_ग_लिखो_and_or(sd, 0xe8, 0xe0, c->B1 >> 8);
	sdp_io_ग_लिखो(sd, 0xe9, c->B1);
	sdp_io_ग_लिखो_and_or(sd, 0xea, 0xe0, c->B2 >> 8);
	sdp_io_ग_लिखो(sd, 0xeb, c->B2);
	sdp_io_ग_लिखो_and_or(sd, 0xec, 0xe0, c->B3 >> 8);
	sdp_io_ग_लिखो(sd, 0xed, c->B3);

	/* B scale */
	sdp_io_ग_लिखो_and_or(sd, 0xee, 0x80, c->B4 >> 8);
	sdp_io_ग_लिखो(sd, 0xef, c->B4);

	/* C coeff */
	sdp_io_ग_लिखो_and_or(sd, 0xf0, 0xe0, c->C1 >> 8);
	sdp_io_ग_लिखो(sd, 0xf1, c->C1);
	sdp_io_ग_लिखो_and_or(sd, 0xf2, 0xe0, c->C2 >> 8);
	sdp_io_ग_लिखो(sd, 0xf3, c->C2);
	sdp_io_ग_लिखो_and_or(sd, 0xf4, 0xe0, c->C3 >> 8);
	sdp_io_ग_लिखो(sd, 0xf5, c->C3);

	/* C scale */
	sdp_io_ग_लिखो_and_or(sd, 0xf6, 0x80, c->C4 >> 8);
	sdp_io_ग_लिखो(sd, 0xf7, c->C4);
पूर्ण

अटल व्योम select_input(काष्ठा v4l2_subdev *sd,
			 क्रमागत adv7842_vid_std_select vid_std_select)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	चयन (state->mode) अणु
	हाल ADV7842_MODE_SDP:
		io_ग_लिखो(sd, 0x00, vid_std_select); /* video std: CVBS or YC mode */
		io_ग_लिखो(sd, 0x01, 0); /* prim mode */
		/* enable embedded syncs क्रम स्वतः graphics mode */
		cp_ग_लिखो_and_or(sd, 0x81, 0xef, 0x10);

		afe_ग_लिखो(sd, 0x00, 0x00); /* घातer up ADC */
		afe_ग_लिखो(sd, 0xc8, 0x00); /* phase control */

		io_ग_लिखो(sd, 0xdd, 0x90); /* Manual 2x output घड़ी */
		/* script says रेजिस्टर 0xde, which करोn't exist in manual */

		/* Manual analog input muxing mode, CVBS (6.4)*/
		afe_ग_लिखो_and_or(sd, 0x02, 0x7f, 0x80);
		अगर (vid_std_select == ADV7842_SDP_VID_STD_CVBS_SD_4x1) अणु
			afe_ग_लिखो(sd, 0x03, 0xa0); /* ADC0 to AIN10 (CVBS), ADC1 N/C*/
			afe_ग_लिखो(sd, 0x04, 0x00); /* ADC2 N/C,ADC3 N/C*/
		पूर्ण अन्यथा अणु
			afe_ग_लिखो(sd, 0x03, 0xa0); /* ADC0 to AIN10 (CVBS), ADC1 N/C*/
			afe_ग_लिखो(sd, 0x04, 0xc0); /* ADC2 to AIN12, ADC3 N/C*/
		पूर्ण
		afe_ग_लिखो(sd, 0x0c, 0x1f); /* ADI recommend ग_लिखो */
		afe_ग_लिखो(sd, 0x12, 0x63); /* ADI recommend ग_लिखो */

		sdp_io_ग_लिखो(sd, 0xb2, 0x60); /* Disable AV codes */
		sdp_io_ग_लिखो(sd, 0xc8, 0xe3); /* Disable Ancillary data */

		/* SDP recommended settings */
		sdp_ग_लिखो(sd, 0x00, 0x3F); /* Autodetect PAL NTSC (not SECAM) */
		sdp_ग_लिखो(sd, 0x01, 0x00); /* Pedestal Off */

		sdp_ग_लिखो(sd, 0x03, 0xE4); /* Manual VCR Gain Luma 0x40B */
		sdp_ग_लिखो(sd, 0x04, 0x0B); /* Manual Luma setting */
		sdp_ग_लिखो(sd, 0x05, 0xC3); /* Manual Chroma setting 0x3FE */
		sdp_ग_लिखो(sd, 0x06, 0xFE); /* Manual Chroma setting */
		sdp_ग_लिखो(sd, 0x12, 0x0D); /* Frame TBC,I_P, 3D comb enabled */
		sdp_ग_लिखो(sd, 0xA7, 0x00); /* ADI Recommended Write */
		sdp_io_ग_लिखो(sd, 0xB0, 0x00); /* Disable H and v blanking */

		/* deपूर्णांकerlacer enabled and 3D comb */
		sdp_ग_लिखो_and_or(sd, 0x12, 0xf6, 0x09);

		अवरोध;

	हाल ADV7842_MODE_COMP:
	हाल ADV7842_MODE_RGB:
		/* Automatic analog input muxing mode */
		afe_ग_लिखो_and_or(sd, 0x02, 0x7f, 0x00);
		/* set mode and select मुक्त run resolution */
		io_ग_लिखो(sd, 0x00, vid_std_select); /* video std */
		io_ग_लिखो(sd, 0x01, 0x02); /* prim mode */
		cp_ग_लिखो_and_or(sd, 0x81, 0xef, 0x10); /* enable embedded syncs
							  क्रम स्वतः graphics mode */

		afe_ग_लिखो(sd, 0x00, 0x00); /* घातer up ADC */
		afe_ग_लिखो(sd, 0xc8, 0x00); /* phase control */
		अगर (state->mode == ADV7842_MODE_COMP) अणु
			/* क्रमce to YCrCb */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x60);
		पूर्ण अन्यथा अणु
			/* क्रमce to RGB */
			io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0x10);
		पूर्ण

		/* set ADI recommended settings क्रम digitizer */
		/* "ADV7842 Register Settings Recommendations
		 * (rev. 1.8, November 2010)" p. 9. */
		afe_ग_लिखो(sd, 0x0c, 0x1f); /* ADC Range improvement */
		afe_ग_लिखो(sd, 0x12, 0x63); /* ADC Range improvement */

		/* set to शेष gain क्रम RGB */
		cp_ग_लिखो(sd, 0x73, 0x10);
		cp_ग_लिखो(sd, 0x74, 0x04);
		cp_ग_लिखो(sd, 0x75, 0x01);
		cp_ग_लिखो(sd, 0x76, 0x00);

		cp_ग_लिखो(sd, 0x3e, 0x04); /* CP core pre-gain control */
		cp_ग_लिखो(sd, 0xc3, 0x39); /* CP coast control. Graphics mode */
		cp_ग_लिखो(sd, 0x40, 0x5c); /* CP core pre-gain control. Graphics mode */
		अवरोध;

	हाल ADV7842_MODE_HDMI:
		/* Automatic analog input muxing mode */
		afe_ग_लिखो_and_or(sd, 0x02, 0x7f, 0x00);
		/* set mode and select मुक्त run resolution */
		अगर (state->hdmi_port_a)
			hdmi_ग_लिखो(sd, 0x00, 0x02); /* select port A */
		अन्यथा
			hdmi_ग_लिखो(sd, 0x00, 0x03); /* select port B */
		io_ग_लिखो(sd, 0x00, vid_std_select); /* video std */
		io_ग_लिखो(sd, 0x01, 5); /* prim mode */
		cp_ग_लिखो_and_or(sd, 0x81, 0xef, 0x00); /* disable embedded syncs
							  क्रम स्वतः graphics mode */

		/* set ADI recommended settings क्रम HDMI: */
		/* "ADV7842 Register Settings Recommendations
		 * (rev. 1.8, November 2010)" p. 3. */
		hdmi_ग_लिखो(sd, 0xc0, 0x00);
		hdmi_ग_लिखो(sd, 0x0d, 0x34); /* ADI recommended ग_लिखो */
		hdmi_ग_लिखो(sd, 0x3d, 0x10); /* ADI recommended ग_लिखो */
		hdmi_ग_लिखो(sd, 0x44, 0x85); /* TMDS PLL optimization */
		hdmi_ग_लिखो(sd, 0x46, 0x1f); /* ADI recommended ग_लिखो */
		hdmi_ग_लिखो(sd, 0x57, 0xb6); /* TMDS PLL optimization */
		hdmi_ग_लिखो(sd, 0x58, 0x03); /* TMDS PLL optimization */
		hdmi_ग_लिखो(sd, 0x60, 0x88); /* TMDS PLL optimization */
		hdmi_ग_लिखो(sd, 0x61, 0x88); /* TMDS PLL optimization */
		hdmi_ग_लिखो(sd, 0x6c, 0x18); /* Disable ISRC clearing bit,
					       Improve robustness */
		hdmi_ग_लिखो(sd, 0x75, 0x10); /* DDC drive strength */
		hdmi_ग_लिखो(sd, 0x85, 0x1f); /* equaliser */
		hdmi_ग_लिखो(sd, 0x87, 0x70); /* ADI recommended ग_लिखो */
		hdmi_ग_लिखो(sd, 0x89, 0x04); /* equaliser */
		hdmi_ग_लिखो(sd, 0x8a, 0x1e); /* equaliser */
		hdmi_ग_लिखो(sd, 0x93, 0x04); /* equaliser */
		hdmi_ग_लिखो(sd, 0x94, 0x1e); /* equaliser */
		hdmi_ग_लिखो(sd, 0x99, 0xa1); /* ADI recommended ग_लिखो */
		hdmi_ग_लिखो(sd, 0x9b, 0x09); /* ADI recommended ग_लिखो */
		hdmi_ग_लिखो(sd, 0x9d, 0x02); /* equaliser */

		afe_ग_लिखो(sd, 0x00, 0xff); /* घातer करोwn ADC */
		afe_ग_लिखो(sd, 0xc8, 0x40); /* phase control */

		/* set to शेष gain क्रम HDMI */
		cp_ग_लिखो(sd, 0x73, 0x10);
		cp_ग_लिखो(sd, 0x74, 0x04);
		cp_ग_लिखो(sd, 0x75, 0x01);
		cp_ग_लिखो(sd, 0x76, 0x00);

		/* reset ADI recommended settings क्रम digitizer */
		/* "ADV7842 Register Settings Recommendations
		 * (rev. 2.5, June 2010)" p. 17. */
		afe_ग_लिखो(sd, 0x12, 0xfb); /* ADC noise shaping filter controls */
		afe_ग_लिखो(sd, 0x0c, 0x0d); /* CP core gain controls */
		cp_ग_लिखो(sd, 0x3e, 0x00); /* CP core pre-gain control */

		/* CP coast control */
		cp_ग_लिखो(sd, 0xc3, 0x33); /* Component mode */

		/* color space conversion, स्वतःdetect color space */
		io_ग_लिखो_and_or(sd, 0x02, 0x0f, 0xf0);
		अवरोध;

	शेष:
		v4l2_dbg(2, debug, sd, "%s: Unknown mode %d\n",
			 __func__, state->mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक adv7842_s_routing(काष्ठा v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	v4l2_dbg(2, debug, sd, "%s: input %d\n", __func__, input);

	चयन (input) अणु
	हाल ADV7842_SELECT_HDMI_PORT_A:
		state->mode = ADV7842_MODE_HDMI;
		state->vid_std_select = ADV7842_HDMI_COMP_VID_STD_HD_1250P;
		state->hdmi_port_a = true;
		अवरोध;
	हाल ADV7842_SELECT_HDMI_PORT_B:
		state->mode = ADV7842_MODE_HDMI;
		state->vid_std_select = ADV7842_HDMI_COMP_VID_STD_HD_1250P;
		state->hdmi_port_a = false;
		अवरोध;
	हाल ADV7842_SELECT_VGA_COMP:
		state->mode = ADV7842_MODE_COMP;
		state->vid_std_select = ADV7842_RGB_VID_STD_AUTO_GRAPH_MODE;
		अवरोध;
	हाल ADV7842_SELECT_VGA_RGB:
		state->mode = ADV7842_MODE_RGB;
		state->vid_std_select = ADV7842_RGB_VID_STD_AUTO_GRAPH_MODE;
		अवरोध;
	हाल ADV7842_SELECT_SDP_CVBS:
		state->mode = ADV7842_MODE_SDP;
		state->vid_std_select = ADV7842_SDP_VID_STD_CVBS_SD_4x1;
		अवरोध;
	हाल ADV7842_SELECT_SDP_YC:
		state->mode = ADV7842_MODE_SDP;
		state->vid_std_select = ADV7842_SDP_VID_STD_YC_SD4_x1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	disable_input(sd);
	select_input(sd, state->vid_std_select);
	enable_input(sd);

	v4l2_subdev_notअगरy_event(sd, &adv7842_ev_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(adv7842_क्रमmats))
		वापस -EINVAL;
	code->code = adv7842_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल व्योम adv7842_fill_क्रमmat(काष्ठा adv7842_state *state,
				काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	स_रखो(क्रमmat, 0, माप(*क्रमmat));

	क्रमmat->width = state->timings.bt.width;
	क्रमmat->height = state->timings.bt.height;
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	अगर (state->timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO)
		क्रमmat->colorspace = (state->timings.bt.height <= 576) ?
			V4L2_COLORSPACE_SMPTE170M : V4L2_COLORSPACE_REC709;
पूर्ण

/*
 * Compute the op_ch_sel value required to obtain on the bus the component order
 * corresponding to the selected क्रमmat taking पूर्णांकo account bus reordering
 * applied by the board at the output of the device.
 *
 * The following table gives the op_ch_value from the क्रमmat component order
 * (expressed as op_ch_sel value in column) and the bus reordering (expressed as
 * adv7842_bus_order value in row).
 *
 *           |	GBR(0)	GRB(1)	BGR(2)	RGB(3)	BRG(4)	RBG(5)
 * ----------+-------------------------------------------------
 * RGB (NOP) |	GBR	GRB	BGR	RGB	BRG	RBG
 * GRB (1-2) |	BGR	RGB	GBR	GRB	RBG	BRG
 * RBG (2-3) |	GRB	GBR	BRG	RBG	BGR	RGB
 * BGR (1-3) |	RBG	BRG	RGB	BGR	GRB	GBR
 * BRG (ROR) |	BRG	RBG	GRB	GBR	RGB	BGR
 * GBR (ROL) |	RGB	BGR	RBG	BRG	GBR	GRB
 */
अटल अचिन्हित पूर्णांक adv7842_op_ch_sel(काष्ठा adv7842_state *state)
अणु
#घोषणा _SEL(a, b, c, d, e, f)	अणु \
	ADV7842_OP_CH_SEL_##a, ADV7842_OP_CH_SEL_##b, ADV7842_OP_CH_SEL_##c, \
	ADV7842_OP_CH_SEL_##d, ADV7842_OP_CH_SEL_##e, ADV7842_OP_CH_SEL_##f पूर्ण
#घोषणा _BUS(x)			[ADV7842_BUS_ORDER_##x]

	अटल स्थिर अचिन्हित पूर्णांक op_ch_sel[6][6] = अणु
		_BUS(RGB) /* NOP */ = _SEL(GBR, GRB, BGR, RGB, BRG, RBG),
		_BUS(GRB) /* 1-2 */ = _SEL(BGR, RGB, GBR, GRB, RBG, BRG),
		_BUS(RBG) /* 2-3 */ = _SEL(GRB, GBR, BRG, RBG, BGR, RGB),
		_BUS(BGR) /* 1-3 */ = _SEL(RBG, BRG, RGB, BGR, GRB, GBR),
		_BUS(BRG) /* ROR */ = _SEL(BRG, RBG, GRB, GBR, RGB, BGR),
		_BUS(GBR) /* ROL */ = _SEL(RGB, BGR, RBG, BRG, GBR, GRB),
	पूर्ण;

	वापस op_ch_sel[state->pdata.bus_order][state->क्रमmat->op_ch_sel >> 5];
पूर्ण

अटल व्योम adv7842_setup_क्रमmat(काष्ठा adv7842_state *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;

	io_ग_लिखो_clr_set(sd, 0x02, 0x02,
			state->क्रमmat->rgb_out ? ADV7842_RGB_OUT : 0);
	io_ग_लिखो(sd, 0x03, state->क्रमmat->op_क्रमmat_sel |
		 state->pdata.op_क्रमmat_mode_sel);
	io_ग_लिखो_clr_set(sd, 0x04, 0xe0, adv7842_op_ch_sel(state));
	io_ग_लिखो_clr_set(sd, 0x05, 0x01,
			state->क्रमmat->swap_cb_cr ? ADV7842_OP_SWAP_CB_CR : 0);
	set_rgb_quantization_range(sd);
पूर्ण

अटल पूर्णांक adv7842_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	अगर (क्रमmat->pad != ADV7842_PAD_SOURCE)
		वापस -EINVAL;

	अगर (state->mode == ADV7842_MODE_SDP) अणु
		/* SPD block */
		अगर (!(sdp_पढ़ो(sd, 0x5a) & 0x01))
			वापस -EINVAL;
		क्रमmat->क्रमmat.code = MEDIA_BUS_FMT_YUYV8_2X8;
		क्रमmat->क्रमmat.width = 720;
		/* valid संकेत */
		अगर (state->norm & V4L2_STD_525_60)
			क्रमmat->क्रमmat.height = 480;
		अन्यथा
			क्रमmat->क्रमmat.height = 576;
		क्रमmat->क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M;
		वापस 0;
	पूर्ण

	adv7842_fill_क्रमmat(state, &क्रमmat->क्रमmat);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		क्रमmat->क्रमmat.code = fmt->code;
	पूर्ण अन्यथा अणु
		क्रमmat->क्रमmat.code = state->क्रमmat->code;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	स्थिर काष्ठा adv7842_क्रमmat_info *info;

	अगर (क्रमmat->pad != ADV7842_PAD_SOURCE)
		वापस -EINVAL;

	अगर (state->mode == ADV7842_MODE_SDP)
		वापस adv7842_get_क्रमmat(sd, cfg, क्रमmat);

	info = adv7842_क्रमmat_info(state, क्रमmat->क्रमmat.code);
	अगर (info == शून्य)
		info = adv7842_क्रमmat_info(state, MEDIA_BUS_FMT_YUYV8_2X8);

	adv7842_fill_क्रमmat(state, &क्रमmat->क्रमmat);
	क्रमmat->क्रमmat.code = info->code;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		fmt->code = क्रमmat->क्रमmat.code;
	पूर्ण अन्यथा अणु
		state->क्रमmat = info;
		adv7842_setup_क्रमmat(state);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adv7842_irq_enable(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	अगर (enable) अणु
		/* Enable SSPD, STDI and CP locked/unlocked पूर्णांकerrupts */
		io_ग_लिखो(sd, 0x46, 0x9c);
		/* ESDP_50HZ_DET पूर्णांकerrupt */
		io_ग_लिखो(sd, 0x5a, 0x10);
		/* Enable CABLE_DET_A/B_ST (+5v) पूर्णांकerrupt */
		io_ग_लिखो(sd, 0x73, 0x03);
		/* Enable V_LOCKED and DE_REGEN_LCK पूर्णांकerrupts */
		io_ग_लिखो(sd, 0x78, 0x03);
		/* Enable SDP Standard Detection Change and SDP Video Detected */
		io_ग_लिखो(sd, 0xa0, 0x09);
		/* Enable HDMI_MODE पूर्णांकerrupt */
		io_ग_लिखो(sd, 0x69, 0x08);
	पूर्ण अन्यथा अणु
		io_ग_लिखो(sd, 0x46, 0x0);
		io_ग_लिखो(sd, 0x5a, 0x0);
		io_ग_लिखो(sd, 0x73, 0x0);
		io_ग_लिखो(sd, 0x78, 0x0);
		io_ग_लिखो(sd, 0xa0, 0x0);
		io_ग_लिखो(sd, 0x69, 0x0);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7842_CEC)
अटल व्योम adv7842_cec_tx_raw_status(काष्ठा v4l2_subdev *sd, u8 tx_raw_status)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	अगर ((cec_पढ़ो(sd, 0x11) & 0x01) == 0) अणु
		v4l2_dbg(1, debug, sd, "%s: tx raw: tx disabled\n", __func__);
		वापस;
	पूर्ण

	अगर (tx_raw_status & 0x02) अणु
		v4l2_dbg(1, debug, sd, "%s: tx raw: arbitration lost\n",
			 __func__);
		cec_transmit_करोne(state->cec_adap, CEC_TX_STATUS_ARB_LOST,
				  1, 0, 0, 0);
		वापस;
	पूर्ण
	अगर (tx_raw_status & 0x04) अणु
		u8 status;
		u8 nack_cnt;
		u8 low_drive_cnt;

		v4l2_dbg(1, debug, sd, "%s: tx raw: retry failed\n", __func__);
		/*
		 * We set this status bit since this hardware perक्रमms
		 * retransmissions.
		 */
		status = CEC_TX_STATUS_MAX_RETRIES;
		nack_cnt = cec_पढ़ो(sd, 0x14) & 0xf;
		अगर (nack_cnt)
			status |= CEC_TX_STATUS_NACK;
		low_drive_cnt = cec_पढ़ो(sd, 0x14) >> 4;
		अगर (low_drive_cnt)
			status |= CEC_TX_STATUS_LOW_DRIVE;
		cec_transmit_करोne(state->cec_adap, status,
				  0, nack_cnt, low_drive_cnt, 0);
		वापस;
	पूर्ण
	अगर (tx_raw_status & 0x01) अणु
		v4l2_dbg(1, debug, sd, "%s: tx raw: ready ok\n", __func__);
		cec_transmit_करोne(state->cec_adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम adv7842_cec_isr(काष्ठा v4l2_subdev *sd, bool *handled)
अणु
	u8 cec_irq;

	/* cec controller */
	cec_irq = io_पढ़ो(sd, 0x93) & 0x0f;
	अगर (!cec_irq)
		वापस;

	v4l2_dbg(1, debug, sd, "%s: cec: irq 0x%x\n", __func__, cec_irq);
	adv7842_cec_tx_raw_status(sd, cec_irq);
	अगर (cec_irq & 0x08) अणु
		काष्ठा adv7842_state *state = to_state(sd);
		काष्ठा cec_msg msg;

		msg.len = cec_पढ़ो(sd, 0x25) & 0x1f;
		अगर (msg.len > 16)
			msg.len = 16;

		अगर (msg.len) अणु
			u8 i;

			क्रम (i = 0; i < msg.len; i++)
				msg.msg[i] = cec_पढ़ो(sd, i + 0x15);
			cec_ग_लिखो(sd, 0x26, 0x01); /* re-enable rx */
			cec_received_msg(state->cec_adap, &msg);
		पूर्ण
	पूर्ण

	io_ग_लिखो(sd, 0x94, cec_irq);

	अगर (handled)
		*handled = true;
पूर्ण

अटल पूर्णांक adv7842_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा adv7842_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;

	अगर (!state->cec_enabled_adap && enable) अणु
		cec_ग_लिखो_clr_set(sd, 0x2a, 0x01, 0x01); /* घातer up cec */
		cec_ग_लिखो(sd, 0x2c, 0x01);	/* cec soft reset */
		cec_ग_लिखो_clr_set(sd, 0x11, 0x01, 0); /* initially disable tx */
		/* enabled irqs: */
		/* tx: पढ़ोy */
		/* tx: arbitration lost */
		/* tx: retry समयout */
		/* rx: पढ़ोy */
		io_ग_लिखो_clr_set(sd, 0x96, 0x0f, 0x0f);
		cec_ग_लिखो(sd, 0x26, 0x01);            /* enable rx */
	पूर्ण अन्यथा अगर (state->cec_enabled_adap && !enable) अणु
		/* disable cec पूर्णांकerrupts */
		io_ग_लिखो_clr_set(sd, 0x96, 0x0f, 0x00);
		/* disable address mask 1-3 */
		cec_ग_लिखो_clr_set(sd, 0x27, 0x70, 0x00);
		/* घातer करोwn cec section */
		cec_ग_लिखो_clr_set(sd, 0x2a, 0x01, 0x00);
		state->cec_valid_addrs = 0;
	पूर्ण
	state->cec_enabled_adap = enable;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा adv7842_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;
	अचिन्हित पूर्णांक i, मुक्त_idx = ADV7842_MAX_ADDRS;

	अगर (!state->cec_enabled_adap)
		वापस addr == CEC_LOG_ADDR_INVALID ? 0 : -EIO;

	अगर (addr == CEC_LOG_ADDR_INVALID) अणु
		cec_ग_लिखो_clr_set(sd, 0x27, 0x70, 0);
		state->cec_valid_addrs = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ADV7842_MAX_ADDRS; i++) अणु
		bool is_valid = state->cec_valid_addrs & (1 << i);

		अगर (मुक्त_idx == ADV7842_MAX_ADDRS && !is_valid)
			मुक्त_idx = i;
		अगर (is_valid && state->cec_addr[i] == addr)
			वापस 0;
	पूर्ण
	अगर (i == ADV7842_MAX_ADDRS) अणु
		i = मुक्त_idx;
		अगर (i == ADV7842_MAX_ADDRS)
			वापस -ENXIO;
	पूर्ण
	state->cec_addr[i] = addr;
	state->cec_valid_addrs |= 1 << i;

	चयन (i) अणु
	हाल 0:
		/* enable address mask 0 */
		cec_ग_लिखो_clr_set(sd, 0x27, 0x10, 0x10);
		/* set address क्रम mask 0 */
		cec_ग_लिखो_clr_set(sd, 0x28, 0x0f, addr);
		अवरोध;
	हाल 1:
		/* enable address mask 1 */
		cec_ग_लिखो_clr_set(sd, 0x27, 0x20, 0x20);
		/* set address क्रम mask 1 */
		cec_ग_लिखो_clr_set(sd, 0x28, 0xf0, addr << 4);
		अवरोध;
	हाल 2:
		/* enable address mask 2 */
		cec_ग_लिखो_clr_set(sd, 0x27, 0x40, 0x40);
		/* set address क्रम mask 1 */
		cec_ग_लिखो_clr_set(sd, 0x29, 0x0f, addr);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				     u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा adv7842_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 len = msg->len;
	अचिन्हित पूर्णांक i;

	/*
	 * The number of retries is the number of attempts - 1, but retry
	 * at least once. It's not clear अगर a value of 0 is allowed, so
	 * let's करो at least one retry.
	 */
	cec_ग_लिखो_clr_set(sd, 0x12, 0x70, max(1, attempts - 1) << 4);

	अगर (len > 16) अणु
		v4l2_err(sd, "%s: len exceeded 16 (%d)\n", __func__, len);
		वापस -EINVAL;
	पूर्ण

	/* ग_लिखो data */
	क्रम (i = 0; i < len; i++)
		cec_ग_लिखो(sd, i, msg->msg[i]);

	/* set length (data + header) */
	cec_ग_लिखो(sd, 0x10, len);
	/* start transmit, enable tx */
	cec_ग_लिखो(sd, 0x11, 0x01);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops adv7842_cec_adap_ops = अणु
	.adap_enable = adv7842_cec_adap_enable,
	.adap_log_addr = adv7842_cec_adap_log_addr,
	.adap_transmit = adv7842_cec_adap_transmit,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक adv7842_isr(काष्ठा v4l2_subdev *sd, u32 status, bool *handled)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	u8 fmt_change_cp, fmt_change_digital, fmt_change_sdp;
	u8 irq_status[6];

	adv7842_irq_enable(sd, false);

	/* पढ़ो status */
	irq_status[0] = io_पढ़ो(sd, 0x43);
	irq_status[1] = io_पढ़ो(sd, 0x57);
	irq_status[2] = io_पढ़ो(sd, 0x70);
	irq_status[3] = io_पढ़ो(sd, 0x75);
	irq_status[4] = io_पढ़ो(sd, 0x9d);
	irq_status[5] = io_पढ़ो(sd, 0x66);

	/* and clear */
	अगर (irq_status[0])
		io_ग_लिखो(sd, 0x44, irq_status[0]);
	अगर (irq_status[1])
		io_ग_लिखो(sd, 0x58, irq_status[1]);
	अगर (irq_status[2])
		io_ग_लिखो(sd, 0x71, irq_status[2]);
	अगर (irq_status[3])
		io_ग_लिखो(sd, 0x76, irq_status[3]);
	अगर (irq_status[4])
		io_ग_लिखो(sd, 0x9e, irq_status[4]);
	अगर (irq_status[5])
		io_ग_लिखो(sd, 0x67, irq_status[5]);

	adv7842_irq_enable(sd, true);

	v4l2_dbg(1, debug, sd, "%s: irq %x, %x, %x, %x, %x, %x\n", __func__,
		 irq_status[0], irq_status[1], irq_status[2],
		 irq_status[3], irq_status[4], irq_status[5]);

	/* क्रमmat change CP */
	fmt_change_cp = irq_status[0] & 0x9c;

	/* क्रमmat change SDP */
	अगर (state->mode == ADV7842_MODE_SDP)
		fmt_change_sdp = (irq_status[1] & 0x30) | (irq_status[4] & 0x09);
	अन्यथा
		fmt_change_sdp = 0;

	/* digital क्रमmat CP */
	अगर (is_digital_input(sd))
		fmt_change_digital = irq_status[3] & 0x03;
	अन्यथा
		fmt_change_digital = 0;

	/* क्रमmat change */
	अगर (fmt_change_cp || fmt_change_digital || fmt_change_sdp) अणु
		v4l2_dbg(1, debug, sd,
			 "%s: fmt_change_cp = 0x%x, fmt_change_digital = 0x%x, fmt_change_sdp = 0x%x\n",
			 __func__, fmt_change_cp, fmt_change_digital,
			 fmt_change_sdp);
		v4l2_subdev_notअगरy_event(sd, &adv7842_ev_fmt);
		अगर (handled)
			*handled = true;
	पूर्ण

	/* HDMI/DVI mode */
	अगर (irq_status[5] & 0x08) अणु
		v4l2_dbg(1, debug, sd, "%s: irq %s mode\n", __func__,
			 (io_पढ़ो(sd, 0x65) & 0x08) ? "HDMI" : "DVI");
		set_rgb_quantization_range(sd);
		अगर (handled)
			*handled = true;
	पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7842_CEC)
	/* cec */
	adv7842_cec_isr(sd, handled);
#पूर्ण_अगर

	/* tx 5v detect */
	अगर (irq_status[2] & 0x3) अणु
		v4l2_dbg(1, debug, sd, "%s: irq tx_5v\n", __func__);
		adv7842_s_detect_tx_5v_ctrl(sd);
		अगर (handled)
			*handled = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	u32 blocks = 0;
	u8 *data = शून्य;

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	चयन (edid->pad) अणु
	हाल ADV7842_EDID_PORT_A:
	हाल ADV7842_EDID_PORT_B:
		अगर (state->hdmi_edid.present & (0x04 << edid->pad)) अणु
			data = state->hdmi_edid.edid;
			blocks = state->hdmi_edid.blocks;
		पूर्ण
		अवरोध;
	हाल ADV7842_EDID_PORT_VGA:
		अगर (state->vga_edid.present) अणु
			data = state->vga_edid.edid;
			blocks = state->vga_edid.blocks;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = blocks;
		वापस 0;
	पूर्ण

	अगर (!data)
		वापस -ENODATA;

	अगर (edid->start_block >= blocks)
		वापस -EINVAL;

	अगर (edid->start_block + edid->blocks > blocks)
		edid->blocks = blocks - edid->start_block;

	स_नकल(edid->edid, data + edid->start_block * 128, edid->blocks * 128);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_set_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *e)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	पूर्णांक err = 0;

	स_रखो(e->reserved, 0, माप(e->reserved));

	अगर (e->pad > ADV7842_EDID_PORT_VGA)
		वापस -EINVAL;
	अगर (e->start_block != 0)
		वापस -EINVAL;
	अगर (e->blocks > 2) अणु
		e->blocks = 2;
		वापस -E2BIG;
	पूर्ण

	/* toकरो, per edid */
	अगर (e->blocks)
		state->aspect_ratio = v4l2_calc_aspect_ratio(e->edid[0x15],
							     e->edid[0x16]);

	चयन (e->pad) अणु
	हाल ADV7842_EDID_PORT_VGA:
		स_रखो(&state->vga_edid.edid, 0, 256);
		state->vga_edid.blocks = e->blocks;
		state->vga_edid.present = e->blocks ? 0x1 : 0x0;
		अगर (e->blocks)
			स_नकल(&state->vga_edid.edid, e->edid, 128 * e->blocks);
		err = edid_ग_लिखो_vga_segment(sd);
		अवरोध;
	हाल ADV7842_EDID_PORT_A:
	हाल ADV7842_EDID_PORT_B:
		स_रखो(&state->hdmi_edid.edid, 0, 256);
		state->hdmi_edid.blocks = e->blocks;
		अगर (e->blocks) अणु
			state->hdmi_edid.present |= 0x04 << e->pad;
			स_नकल(&state->hdmi_edid.edid, e->edid, 128 * e->blocks);
		पूर्ण अन्यथा अणु
			state->hdmi_edid.present &= ~(0x04 << e->pad);
			adv7842_s_detect_tx_5v_ctrl(sd);
		पूर्ण
		err = edid_ग_लिखो_hdmi_segment(sd, e->pad);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (err < 0)
		v4l2_err(sd, "error %d writing edid on port %d\n", err, e->pad);
	वापस err;
पूर्ण

काष्ठा adv7842_cfg_पढ़ो_infoframe अणु
	स्थिर अक्षर *desc;
	u8 present_mask;
	u8 head_addr;
	u8 payload_addr;
पूर्ण;

अटल व्योम log_infoframe(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा adv7842_cfg_पढ़ो_infoframe *cri)
अणु
	पूर्णांक i;
	u8 buffer[32];
	जोड़ hdmi_infoframe frame;
	u8 len;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा device *dev = &client->dev;

	अगर (!(io_पढ़ो(sd, 0x60) & cri->present_mask)) अणु
		v4l2_info(sd, "%s infoframe not received\n", cri->desc);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		buffer[i] = infoframe_पढ़ो(sd, cri->head_addr + i);

	len = buffer[2] + 1;

	अगर (len + 3 > माप(buffer)) अणु
		v4l2_err(sd, "%s: invalid %s infoframe length %d\n", __func__, cri->desc, len);
		वापस;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		buffer[i + 3] = infoframe_पढ़ो(sd, cri->payload_addr + i);

	अगर (hdmi_infoframe_unpack(&frame, buffer, माप(buffer)) < 0) अणु
		v4l2_err(sd, "%s: unpack of %s infoframe failed\n", __func__, cri->desc);
		वापस;
	पूर्ण

	hdmi_infoframe_log(KERN_INFO, dev, &frame);
पूर्ण

अटल व्योम adv7842_log_infoframes(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा adv7842_cfg_पढ़ो_infoframe cri[] = अणु
		अणु "AVI", 0x01, 0xe0, 0x00 पूर्ण,
		अणु "Audio", 0x02, 0xe3, 0x1c पूर्ण,
		अणु "SDP", 0x04, 0xe6, 0x2a पूर्ण,
		अणु "Vendor", 0x10, 0xec, 0x54 पूर्ण
	पूर्ण;

	अगर (!(hdmi_पढ़ो(sd, 0x05) & 0x80)) अणु
		v4l2_info(sd, "receive DVI-D signal, no infoframes\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cri); i++)
		log_infoframe(sd, &cri[i]);
पूर्ण

#अगर 0
/* Let's keep it here क्रम now, as it could be useful क्रम debug */
अटल स्थिर अक्षर * स्थिर prim_mode_txt[] = अणु
	"SDP",
	"Component",
	"Graphics",
	"Reserved",
	"CVBS & HDMI AUDIO",
	"HDMI-Comp",
	"HDMI-GR",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक adv7842_sdp_log_status(काष्ठा v4l2_subdev *sd)
अणु
	/* SDP (Standard definition processor) block */
	u8 sdp_संकेत_detected = sdp_पढ़ो(sd, 0x5A) & 0x01;

	v4l2_info(sd, "Chip powered %s\n", no_घातer(sd) ? "off" : "on");
	v4l2_info(sd, "Prim-mode = 0x%x, video std = 0x%x\n",
		  io_पढ़ो(sd, 0x01) & 0x0f, io_पढ़ो(sd, 0x00) & 0x3f);

	v4l2_info(sd, "SDP: free run: %s\n",
		(sdp_पढ़ो(sd, 0x56) & 0x01) ? "on" : "off");
	v4l2_info(sd, "SDP: %s\n", sdp_संकेत_detected ?
		"valid SD/PR signal detected" : "invalid/no signal");
	अगर (sdp_संकेत_detected) अणु
		अटल स्थिर अक्षर * स्थिर sdp_std_txt[] = अणु
			"NTSC-M/J",
			"1?",
			"NTSC-443",
			"60HzSECAM",
			"PAL-M",
			"5?",
			"PAL-60",
			"7?", "8?", "9?", "a?", "b?",
			"PAL-CombN",
			"d?",
			"PAL-BGHID",
			"SECAM"
		पूर्ण;
		v4l2_info(sd, "SDP: standard %s\n",
			sdp_std_txt[sdp_पढ़ो(sd, 0x52) & 0x0f]);
		v4l2_info(sd, "SDP: %s\n",
			(sdp_पढ़ो(sd, 0x59) & 0x08) ? "50Hz" : "60Hz");
		v4l2_info(sd, "SDP: %s\n",
			(sdp_पढ़ो(sd, 0x57) & 0x08) ? "Interlaced" : "Progressive");
		v4l2_info(sd, "SDP: deinterlacer %s\n",
			(sdp_पढ़ो(sd, 0x12) & 0x08) ? "enabled" : "disabled");
		v4l2_info(sd, "SDP: csc %s mode\n",
			(sdp_io_पढ़ो(sd, 0xe0) & 0x40) ? "auto" : "manual");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_cp_log_status(काष्ठा v4l2_subdev *sd)
अणु
	/* CP block */
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा v4l2_dv_timings timings;
	u8 reg_io_0x02 = io_पढ़ो(sd, 0x02);
	u8 reg_io_0x21 = io_पढ़ो(sd, 0x21);
	u8 reg_rep_0x77 = rep_पढ़ो(sd, 0x77);
	u8 reg_rep_0x7d = rep_पढ़ो(sd, 0x7d);
	bool audio_pll_locked = hdmi_पढ़ो(sd, 0x04) & 0x01;
	bool audio_sample_packet_detect = hdmi_पढ़ो(sd, 0x18) & 0x01;
	bool audio_mute = io_पढ़ो(sd, 0x65) & 0x40;

	अटल स्थिर अक्षर * स्थिर csc_coeff_sel_rb[16] = अणु
		"bypassed", "YPbPr601 -> RGB", "reserved", "YPbPr709 -> RGB",
		"reserved", "RGB -> YPbPr601", "reserved", "RGB -> YPbPr709",
		"reserved", "YPbPr709 -> YPbPr601", "YPbPr601 -> YPbPr709",
		"reserved", "reserved", "reserved", "reserved", "manual"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर input_color_space_txt[16] = अणु
		"RGB limited range (16-235)", "RGB full range (0-255)",
		"YCbCr Bt.601 (16-235)", "YCbCr Bt.709 (16-235)",
		"xvYCC Bt.601", "xvYCC Bt.709",
		"YCbCr Bt.601 (0-255)", "YCbCr Bt.709 (0-255)",
		"invalid", "invalid", "invalid", "invalid", "invalid",
		"invalid", "invalid", "automatic"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर rgb_quantization_range_txt[] = अणु
		"Automatic",
		"RGB limited range (16-235)",
		"RGB full range (0-255)",
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर deep_color_mode_txt[4] = अणु
		"8-bits per channel",
		"10-bits per channel",
		"12-bits per channel",
		"16-bits per channel (not supported)"
	पूर्ण;

	v4l2_info(sd, "-----Chip status-----\n");
	v4l2_info(sd, "Chip power: %s\n", no_घातer(sd) ? "off" : "on");
	v4l2_info(sd, "HDMI/DVI-D port selected: %s\n",
			state->hdmi_port_a ? "A" : "B");
	v4l2_info(sd, "EDID A %s, B %s\n",
		  ((reg_rep_0x7d & 0x04) && (reg_rep_0x77 & 0x04)) ?
		  "enabled" : "disabled",
		  ((reg_rep_0x7d & 0x08) && (reg_rep_0x77 & 0x08)) ?
		  "enabled" : "disabled");
	v4l2_info(sd, "HPD A %s, B %s\n",
		  reg_io_0x21 & 0x02 ? "enabled" : "disabled",
		  reg_io_0x21 & 0x01 ? "enabled" : "disabled");
	v4l2_info(sd, "CEC: %s\n", state->cec_enabled_adap ?
			"enabled" : "disabled");
	अगर (state->cec_enabled_adap) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ADV7842_MAX_ADDRS; i++) अणु
			bool is_valid = state->cec_valid_addrs & (1 << i);

			अगर (is_valid)
				v4l2_info(sd, "CEC Logical Address: 0x%x\n",
					  state->cec_addr[i]);
		पूर्ण
	पूर्ण

	v4l2_info(sd, "-----Signal status-----\n");
	अगर (state->hdmi_port_a) अणु
		v4l2_info(sd, "Cable detected (+5V power): %s\n",
			  io_पढ़ो(sd, 0x6f) & 0x02 ? "true" : "false");
		v4l2_info(sd, "TMDS signal detected: %s\n",
			  (io_पढ़ो(sd, 0x6a) & 0x02) ? "true" : "false");
		v4l2_info(sd, "TMDS signal locked: %s\n",
			  (io_पढ़ो(sd, 0x6a) & 0x20) ? "true" : "false");
	पूर्ण अन्यथा अणु
		v4l2_info(sd, "Cable detected (+5V power):%s\n",
			  io_पढ़ो(sd, 0x6f) & 0x01 ? "true" : "false");
		v4l2_info(sd, "TMDS signal detected: %s\n",
			  (io_पढ़ो(sd, 0x6a) & 0x01) ? "true" : "false");
		v4l2_info(sd, "TMDS signal locked: %s\n",
			  (io_पढ़ो(sd, 0x6a) & 0x10) ? "true" : "false");
	पूर्ण
	v4l2_info(sd, "CP free run: %s\n",
		  (!!(cp_पढ़ो(sd, 0xff) & 0x10) ? "on" : "off"));
	v4l2_info(sd, "Prim-mode = 0x%x, video std = 0x%x, v_freq = 0x%x\n",
		  io_पढ़ो(sd, 0x01) & 0x0f, io_पढ़ो(sd, 0x00) & 0x3f,
		  (io_पढ़ो(sd, 0x01) & 0x70) >> 4);

	v4l2_info(sd, "-----Video Timings-----\n");
	अगर (no_cp_संकेत(sd)) अणु
		v4l2_info(sd, "STDI: not locked\n");
	पूर्ण अन्यथा अणु
		u32 bl = ((cp_पढ़ो(sd, 0xb1) & 0x3f) << 8) | cp_पढ़ो(sd, 0xb2);
		u32 lcf = ((cp_पढ़ो(sd, 0xb3) & 0x7) << 8) | cp_पढ़ो(sd, 0xb4);
		u32 lcvs = cp_पढ़ो(sd, 0xb3) >> 3;
		u32 fcl = ((cp_पढ़ो(sd, 0xb8) & 0x1f) << 8) | cp_पढ़ो(sd, 0xb9);
		अक्षर hs_pol = ((cp_पढ़ो(sd, 0xb5) & 0x10) ?
				((cp_पढ़ो(sd, 0xb5) & 0x08) ? '+' : '-') : 'x');
		अक्षर vs_pol = ((cp_पढ़ो(sd, 0xb5) & 0x40) ?
				((cp_पढ़ो(sd, 0xb5) & 0x20) ? '+' : '-') : 'x');
		v4l2_info(sd,
			"STDI: lcf (frame height - 1) = %d, bl = %d, lcvs (vsync) = %d, fcl = %d, %s, %chsync, %cvsync\n",
			lcf, bl, lcvs, fcl,
			(cp_पढ़ो(sd, 0xb1) & 0x40) ?
				"interlaced" : "progressive",
			hs_pol, vs_pol);
	पूर्ण
	अगर (adv7842_query_dv_timings(sd, &timings))
		v4l2_info(sd, "No video detected\n");
	अन्यथा
		v4l2_prपूर्णांक_dv_timings(sd->name, "Detected format: ",
				      &timings, true);
	v4l2_prपूर्णांक_dv_timings(sd->name, "Configured format: ",
			&state->timings, true);

	अगर (no_cp_संकेत(sd))
		वापस 0;

	v4l2_info(sd, "-----Color space-----\n");
	v4l2_info(sd, "RGB quantization range ctrl: %s\n",
		  rgb_quantization_range_txt[state->rgb_quantization_range]);
	v4l2_info(sd, "Input color space: %s\n",
		  input_color_space_txt[reg_io_0x02 >> 4]);
	v4l2_info(sd, "Output color space: %s %s, alt-gamma %s\n",
		  (reg_io_0x02 & 0x02) ? "RGB" : "YCbCr",
		  (((reg_io_0x02 >> 2) & 0x01) ^ (reg_io_0x02 & 0x01)) ?
			"(16-235)" : "(0-255)",
		  (reg_io_0x02 & 0x08) ? "enabled" : "disabled");
	v4l2_info(sd, "Color space conversion: %s\n",
		  csc_coeff_sel_rb[cp_पढ़ो(sd, 0xf4) >> 4]);

	अगर (!is_digital_input(sd))
		वापस 0;

	v4l2_info(sd, "-----%s status-----\n", is_hdmi(sd) ? "HDMI" : "DVI-D");
	v4l2_info(sd, "HDCP encrypted content: %s\n",
			(hdmi_पढ़ो(sd, 0x05) & 0x40) ? "true" : "false");
	v4l2_info(sd, "HDCP keys read: %s%s\n",
			(hdmi_पढ़ो(sd, 0x04) & 0x20) ? "yes" : "no",
			(hdmi_पढ़ो(sd, 0x04) & 0x10) ? "ERROR" : "");
	अगर (!is_hdmi(sd))
		वापस 0;

	v4l2_info(sd, "Audio: pll %s, samples %s, %s\n",
			audio_pll_locked ? "locked" : "not locked",
			audio_sample_packet_detect ? "detected" : "not detected",
			audio_mute ? "muted" : "enabled");
	अगर (audio_pll_locked && audio_sample_packet_detect) अणु
		v4l2_info(sd, "Audio format: %s\n",
			(hdmi_पढ़ो(sd, 0x07) & 0x40) ? "multi-channel" : "stereo");
	पूर्ण
	v4l2_info(sd, "Audio CTS: %u\n", (hdmi_पढ़ो(sd, 0x5b) << 12) +
			(hdmi_पढ़ो(sd, 0x5c) << 8) +
			(hdmi_पढ़ो(sd, 0x5d) & 0xf0));
	v4l2_info(sd, "Audio N: %u\n", ((hdmi_पढ़ो(sd, 0x5d) & 0x0f) << 16) +
			(hdmi_पढ़ो(sd, 0x5e) << 8) +
			hdmi_पढ़ो(sd, 0x5f));
	v4l2_info(sd, "AV Mute: %s\n",
			(hdmi_पढ़ो(sd, 0x04) & 0x40) ? "on" : "off");
	v4l2_info(sd, "Deep color mode: %s\n",
			deep_color_mode_txt[hdmi_पढ़ो(sd, 0x0b) >> 6]);

	adv7842_log_infoframes(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	अगर (state->mode == ADV7842_MODE_SDP)
		वापस adv7842_sdp_log_status(sd);
	वापस adv7842_cp_log_status(sd);
पूर्ण

अटल पूर्णांक adv7842_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (state->mode != ADV7842_MODE_SDP)
		वापस -ENODATA;

	अगर (!(sdp_पढ़ो(sd, 0x5A) & 0x01)) अणु
		*std = 0;
		v4l2_dbg(1, debug, sd, "%s: no valid signal\n", __func__);
		वापस 0;
	पूर्ण

	चयन (sdp_पढ़ो(sd, 0x52) & 0x0f) अणु
	हाल 0:
		/* NTSC-M/J */
		*std &= V4L2_STD_NTSC;
		अवरोध;
	हाल 2:
		/* NTSC-443 */
		*std &= V4L2_STD_NTSC_443;
		अवरोध;
	हाल 3:
		/* 60HzSECAM */
		*std &= V4L2_STD_SECAM;
		अवरोध;
	हाल 4:
		/* PAL-M */
		*std &= V4L2_STD_PAL_M;
		अवरोध;
	हाल 6:
		/* PAL-60 */
		*std &= V4L2_STD_PAL_60;
		अवरोध;
	हाल 0xc:
		/* PAL-CombN */
		*std &= V4L2_STD_PAL_Nc;
		अवरोध;
	हाल 0xe:
		/* PAL-BGHID */
		*std &= V4L2_STD_PAL;
		अवरोध;
	हाल 0xf:
		/* SECAM */
		*std &= V4L2_STD_SECAM;
		अवरोध;
	शेष:
		*std &= V4L2_STD_ALL;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adv7842_s_sdp_io(काष्ठा v4l2_subdev *sd, काष्ठा adv7842_sdp_io_sync_adjusपंचांगent *s)
अणु
	अगर (s && s->adjust) अणु
		sdp_io_ग_लिखो(sd, 0x94, (s->hs_beg >> 8) & 0xf);
		sdp_io_ग_लिखो(sd, 0x95, s->hs_beg & 0xff);
		sdp_io_ग_लिखो(sd, 0x96, (s->hs_width >> 8) & 0xf);
		sdp_io_ग_लिखो(sd, 0x97, s->hs_width & 0xff);
		sdp_io_ग_लिखो(sd, 0x98, (s->de_beg >> 8) & 0xf);
		sdp_io_ग_लिखो(sd, 0x99, s->de_beg & 0xff);
		sdp_io_ग_लिखो(sd, 0x9a, (s->de_end >> 8) & 0xf);
		sdp_io_ग_लिखो(sd, 0x9b, s->de_end & 0xff);
		sdp_io_ग_लिखो(sd, 0xa8, s->vs_beg_o);
		sdp_io_ग_लिखो(sd, 0xa9, s->vs_beg_e);
		sdp_io_ग_लिखो(sd, 0xaa, s->vs_end_o);
		sdp_io_ग_लिखो(sd, 0xab, s->vs_end_e);
		sdp_io_ग_लिखो(sd, 0xac, s->de_v_beg_o);
		sdp_io_ग_लिखो(sd, 0xad, s->de_v_beg_e);
		sdp_io_ग_लिखो(sd, 0xae, s->de_v_end_o);
		sdp_io_ग_लिखो(sd, 0xaf, s->de_v_end_e);
	पूर्ण अन्यथा अणु
		/* set to शेष */
		sdp_io_ग_लिखो(sd, 0x94, 0x00);
		sdp_io_ग_लिखो(sd, 0x95, 0x00);
		sdp_io_ग_लिखो(sd, 0x96, 0x00);
		sdp_io_ग_लिखो(sd, 0x97, 0x20);
		sdp_io_ग_लिखो(sd, 0x98, 0x00);
		sdp_io_ग_लिखो(sd, 0x99, 0x00);
		sdp_io_ग_लिखो(sd, 0x9a, 0x00);
		sdp_io_ग_लिखो(sd, 0x9b, 0x00);
		sdp_io_ग_लिखो(sd, 0xa8, 0x04);
		sdp_io_ग_लिखो(sd, 0xa9, 0x04);
		sdp_io_ग_लिखो(sd, 0xaa, 0x04);
		sdp_io_ग_लिखो(sd, 0xab, 0x04);
		sdp_io_ग_लिखो(sd, 0xac, 0x04);
		sdp_io_ग_लिखो(sd, 0xad, 0x04);
		sdp_io_ग_लिखो(sd, 0xae, 0x04);
		sdp_io_ग_लिखो(sd, 0xaf, 0x04);
	पूर्ण
पूर्ण

अटल पूर्णांक adv7842_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा adv7842_platक्रमm_data *pdata = &state->pdata;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (state->mode != ADV7842_MODE_SDP)
		वापस -ENODATA;

	अगर (norm & V4L2_STD_625_50)
		adv7842_s_sdp_io(sd, &pdata->sdp_io_sync_625);
	अन्यथा अगर (norm & V4L2_STD_525_60)
		adv7842_s_sdp_io(sd, &pdata->sdp_io_sync_525);
	अन्यथा
		adv7842_s_sdp_io(sd, शून्य);

	अगर (norm & V4L2_STD_ALL) अणु
		state->norm = norm;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adv7842_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (state->mode != ADV7842_MODE_SDP)
		वापस -ENODATA;

	*norm = state->norm;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv7842_core_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा adv7842_platक्रमm_data *pdata = &state->pdata;
	hdmi_ग_लिखो(sd, 0x48,
		   (pdata->disable_pwrdnb ? 0x80 : 0) |
		   (pdata->disable_cable_det_rst ? 0x40 : 0));

	disable_input(sd);

	/*
	 * Disable I2C access to पूर्णांकernal EDID ram from HDMI DDC ports
	 * Disable स्वतः edid enable when leaving घातerकरोwn mode
	 */
	rep_ग_लिखो_and_or(sd, 0x77, 0xd3, 0x20);

	/* घातer */
	io_ग_लिखो(sd, 0x0c, 0x42);   /* Power up part and घातer करोwn VDP */
	io_ग_लिखो(sd, 0x15, 0x80);   /* Power up pads */

	/* video क्रमmat */
	io_ग_लिखो(sd, 0x02, 0xf0 | pdata->alt_gamma << 3);
	io_ग_लिखो_and_or(sd, 0x05, 0xf0, pdata->blank_data << 3 |
			pdata->insert_av_codes << 2 |
			pdata->replicate_av_codes << 1);
	adv7842_setup_क्रमmat(state);

	/* HDMI audio */
	hdmi_ग_लिखो_and_or(sd, 0x1a, 0xf1, 0x08); /* Wait 1 s beक्रमe unmute */

	/* Drive strength */
	io_ग_लिखो_and_or(sd, 0x14, 0xc0,
			pdata->dr_str_data << 4 |
			pdata->dr_str_clk << 2 |
			pdata->dr_str_sync);

	/* HDMI मुक्त run */
	cp_ग_लिखो_and_or(sd, 0xba, 0xfc, pdata->hdmi_मुक्त_run_enable |
					(pdata->hdmi_मुक्त_run_mode << 1));

	/* SPD मुक्त run */
	sdp_ग_लिखो_and_or(sd, 0xdd, 0xf0, pdata->sdp_मुक्त_run_क्रमce |
					 (pdata->sdp_मुक्त_run_cbar_en << 1) |
					 (pdata->sdp_मुक्त_run_man_col_en << 2) |
					 (pdata->sdp_मुक्त_run_स्वतः << 3));

	/* TODO from platक्रमm data */
	cp_ग_लिखो(sd, 0x69, 0x14);   /* Enable CP CSC */
	io_ग_लिखो(sd, 0x06, 0xa6);   /* positive VS and HS and DE */
	cp_ग_लिखो(sd, 0xf3, 0xdc); /* Low threshold to enter/निकास मुक्त run mode */
	afe_ग_लिखो(sd, 0xb5, 0x01);  /* Setting MCLK to 256Fs */

	afe_ग_लिखो(sd, 0x02, pdata->ain_sel); /* Select analog input muxing mode */
	io_ग_लिखो_and_or(sd, 0x30, ~(1 << 4), pdata->output_bus_lsb_to_msb << 4);

	sdp_csc_coeff(sd, &pdata->sdp_csc_coeff);

	/* toकरो, improve settings क्रम sdram */
	अगर (pdata->sd_ram_size >= 128) अणु
		sdp_ग_लिखो(sd, 0x12, 0x0d); /* Frame TBC,3D comb enabled */
		अगर (pdata->sd_ram_ddr) अणु
			/* SDP setup क्रम the AD eval board */
			sdp_io_ग_लिखो(sd, 0x6f, 0x00); /* DDR mode */
			sdp_io_ग_लिखो(sd, 0x75, 0x0a); /* 128 MB memory size */
			sdp_io_ग_लिखो(sd, 0x7a, 0xa5); /* Timing Adjusपंचांगent */
			sdp_io_ग_लिखो(sd, 0x7b, 0x8f); /* Timing Adjusपंचांगent */
			sdp_io_ग_लिखो(sd, 0x60, 0x01); /* SDRAM reset */
		पूर्ण अन्यथा अणु
			sdp_io_ग_लिखो(sd, 0x75, 0x0a); /* 64 MB memory size ?*/
			sdp_io_ग_लिखो(sd, 0x74, 0x00); /* must be zero क्रम sdr sdram */
			sdp_io_ग_लिखो(sd, 0x79, 0x33); /* CAS latency to 3,
							 depends on memory */
			sdp_io_ग_लिखो(sd, 0x6f, 0x01); /* SDR mode */
			sdp_io_ग_लिखो(sd, 0x7a, 0xa5); /* Timing Adjusपंचांगent */
			sdp_io_ग_लिखो(sd, 0x7b, 0x8f); /* Timing Adjusपंचांगent */
			sdp_io_ग_लिखो(sd, 0x60, 0x01); /* SDRAM reset */
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Manual UG-214, rev 0 is bit confusing on this bit
		 * but a '1' disables any संकेत अगर the Ram is active.
		 */
		sdp_io_ग_लिखो(sd, 0x29, 0x10); /* Tristate memory पूर्णांकerface */
	पूर्ण

	select_input(sd, pdata->vid_std_select);

	enable_input(sd);

	अगर (pdata->hpa_स्वतः) अणु
		/* HPA स्वतः, HPA 0.5s after Edid set and Cable detect */
		hdmi_ग_लिखो(sd, 0x69, 0x5c);
	पूर्ण अन्यथा अणु
		/* HPA manual */
		hdmi_ग_लिखो(sd, 0x69, 0xa3);
		/* HPA disable on port A and B */
		io_ग_लिखो_and_or(sd, 0x20, 0xcf, 0x00);
	पूर्ण

	/* LLC */
	io_ग_लिखो(sd, 0x19, 0x80 | pdata->llc_dll_phase);
	io_ग_लिखो(sd, 0x33, 0x40);

	/* पूर्णांकerrupts */
	io_ग_लिखो(sd, 0x40, 0xf2); /* Configure INT1 */

	adv7842_irq_enable(sd, true);

	वापस v4l2_ctrl_handler_setup(sd->ctrl_handler);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv7842_ddr_ram_test(काष्ठा v4l2_subdev *sd)
अणु
	/*
	 * From ADV784x बाह्यal Memory test.pdf
	 *
	 * Reset must just been perक्रमmed beक्रमe running test.
	 * Recommended to reset after test.
	 */
	पूर्णांक i;
	पूर्णांक pass = 0;
	पूर्णांक fail = 0;
	पूर्णांक complete = 0;

	io_ग_लिखो(sd, 0x00, 0x01);  /* Program SDP 4x1 */
	io_ग_लिखो(sd, 0x01, 0x00);  /* Program SDP mode */
	afe_ग_लिखो(sd, 0x80, 0x92); /* SDP Recommended Write */
	afe_ग_लिखो(sd, 0x9B, 0x01); /* SDP Recommended Write ADV7844ES1 */
	afe_ग_लिखो(sd, 0x9C, 0x60); /* SDP Recommended Write ADV7844ES1 */
	afe_ग_लिखो(sd, 0x9E, 0x02); /* SDP Recommended Write ADV7844ES1 */
	afe_ग_लिखो(sd, 0xA0, 0x0B); /* SDP Recommended Write ADV7844ES1 */
	afe_ग_लिखो(sd, 0xC3, 0x02); /* Memory BIST Initialisation */
	io_ग_लिखो(sd, 0x0C, 0x40);  /* Power up ADV7844 */
	io_ग_लिखो(sd, 0x15, 0xBA);  /* Enable outमाला_दो */
	sdp_ग_लिखो(sd, 0x12, 0x00); /* Disable 3D comb, Frame TBC & 3DNR */
	io_ग_लिखो(sd, 0xFF, 0x04);  /* Reset memory controller */

	usleep_range(5000, 6000);

	sdp_ग_लिखो(sd, 0x12, 0x00);    /* Disable 3D Comb, Frame TBC & 3DNR */
	sdp_io_ग_लिखो(sd, 0x2A, 0x01); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x7c, 0x19); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x80, 0x87); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x81, 0x4a); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x82, 0x2c); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x83, 0x0e); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x84, 0x94); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x85, 0x62); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x7d, 0x00); /* Memory BIST Initialisation */
	sdp_io_ग_लिखो(sd, 0x7e, 0x1a); /* Memory BIST Initialisation */

	usleep_range(5000, 6000);

	sdp_io_ग_लिखो(sd, 0xd9, 0xd5); /* Enable BIST Test */
	sdp_ग_लिखो(sd, 0x12, 0x05); /* Enable FRAME TBC & 3D COMB */

	msleep(20);

	क्रम (i = 0; i < 10; i++) अणु
		u8 result = sdp_io_पढ़ो(sd, 0xdb);
		अगर (result & 0x10) अणु
			complete++;
			अगर (result & 0x20)
				fail++;
			अन्यथा
				pass++;
		पूर्ण
		msleep(20);
	पूर्ण

	v4l2_dbg(1, debug, sd,
		"Ram Test: completed %d of %d: pass %d, fail %d\n",
		complete, i, pass, fail);

	अगर (!complete || fail)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल व्योम adv7842_reग_लिखो_i2c_addresses(काष्ठा v4l2_subdev *sd,
		काष्ठा adv7842_platक्रमm_data *pdata)
अणु
	io_ग_लिखो(sd, 0xf1, pdata->i2c_sdp << 1);
	io_ग_लिखो(sd, 0xf2, pdata->i2c_sdp_io << 1);
	io_ग_लिखो(sd, 0xf3, pdata->i2c_avlink << 1);
	io_ग_लिखो(sd, 0xf4, pdata->i2c_cec << 1);
	io_ग_लिखो(sd, 0xf5, pdata->i2c_infoframe << 1);

	io_ग_लिखो(sd, 0xf8, pdata->i2c_afe << 1);
	io_ग_लिखो(sd, 0xf9, pdata->i2c_repeater << 1);
	io_ग_लिखो(sd, 0xfa, pdata->i2c_edid << 1);
	io_ग_लिखो(sd, 0xfb, pdata->i2c_hdmi << 1);

	io_ग_लिखो(sd, 0xfd, pdata->i2c_cp << 1);
	io_ग_लिखो(sd, 0xfe, pdata->i2c_vdp << 1);
पूर्ण

अटल पूर्णांक adv7842_command_ram_test(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा adv7842_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_dv_timings timings;
	पूर्णांक ret = 0;

	अगर (!pdata)
		वापस -ENODEV;

	अगर (!pdata->sd_ram_size || !pdata->sd_ram_ddr) अणु
		v4l2_info(sd, "no sdram or no ddr sdram\n");
		वापस -EINVAL;
	पूर्ण

	मुख्य_reset(sd);

	adv7842_reग_लिखो_i2c_addresses(sd, pdata);

	/* run ram test */
	ret = adv7842_ddr_ram_test(sd);

	मुख्य_reset(sd);

	adv7842_reग_लिखो_i2c_addresses(sd, pdata);

	/* and re-init chip and state */
	adv7842_core_init(sd);

	disable_input(sd);

	select_input(sd, state->vid_std_select);

	enable_input(sd);

	edid_ग_लिखो_vga_segment(sd);
	edid_ग_लिखो_hdmi_segment(sd, ADV7842_EDID_PORT_A);
	edid_ग_लिखो_hdmi_segment(sd, ADV7842_EDID_PORT_B);

	timings = state->timings;

	स_रखो(&state->timings, 0, माप(काष्ठा v4l2_dv_timings));

	adv7842_s_dv_timings(sd, &timings);

	वापस ret;
पूर्ण

अटल दीर्घ adv7842_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ADV7842_CMD_RAM_TEST:
		वापस adv7842_command_ram_test(sd);
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक adv7842_subscribe_event(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_fh *fh,
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

अटल पूर्णांक adv7842_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक err;

	err = cec_रेजिस्टर_adapter(state->cec_adap, &client->dev);
	अगर (err)
		cec_delete_adapter(state->cec_adap);
	वापस err;
पूर्ण

अटल व्योम adv7842_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);

	cec_unरेजिस्टर_adapter(state->cec_adap);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops adv7842_ctrl_ops = अणु
	.s_ctrl = adv7842_s_ctrl,
	.g_अस्थिर_ctrl = adv7842_g_अस्थिर_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv7842_core_ops = अणु
	.log_status = adv7842_log_status,
	.ioctl = adv7842_ioctl,
	.पूर्णांकerrupt_service_routine = adv7842_isr,
	.subscribe_event = adv7842_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = adv7842_g_रेजिस्टर,
	.s_रेजिस्टर = adv7842_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv7842_video_ops = अणु
	.g_std = adv7842_g_std,
	.s_std = adv7842_s_std,
	.s_routing = adv7842_s_routing,
	.querystd = adv7842_querystd,
	.g_input_status = adv7842_g_input_status,
	.s_dv_timings = adv7842_s_dv_timings,
	.g_dv_timings = adv7842_g_dv_timings,
	.query_dv_timings = adv7842_query_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv7842_pad_ops = अणु
	.क्रमागत_mbus_code = adv7842_क्रमागत_mbus_code,
	.get_fmt = adv7842_get_क्रमmat,
	.set_fmt = adv7842_set_क्रमmat,
	.get_edid = adv7842_get_edid,
	.set_edid = adv7842_set_edid,
	.क्रमागत_dv_timings = adv7842_क्रमागत_dv_timings,
	.dv_timings_cap = adv7842_dv_timings_cap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adv7842_ops = अणु
	.core = &adv7842_core_ops,
	.video = &adv7842_video_ops,
	.pad = &adv7842_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops adv7842_पूर्णांक_ops = अणु
	.रेजिस्टरed = adv7842_रेजिस्टरed,
	.unरेजिस्टरed = adv7842_unरेजिस्टरed,
पूर्ण;

/* -------------------------- custom ctrls ---------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_config adv7842_ctrl_analog_sampling_phase = अणु
	.ops = &adv7842_ctrl_ops,
	.id = V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE,
	.name = "Analog Sampling Phase",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 0x1f,
	.step = 1,
	.def = 0,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config adv7842_ctrl_मुक्त_run_color_manual = अणु
	.ops = &adv7842_ctrl_ops,
	.id = V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL,
	.name = "Free Running Color, Manual",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config adv7842_ctrl_मुक्त_run_color = अणु
	.ops = &adv7842_ctrl_ops,
	.id = V4L2_CID_ADV_RX_FREE_RUN_COLOR,
	.name = "Free Running Color",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.max = 0xffffff,
	.step = 0x1,
पूर्ण;


अटल व्योम adv7842_unरेजिस्टर_clients(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	i2c_unरेजिस्टर_device(state->i2c_avlink);
	i2c_unरेजिस्टर_device(state->i2c_cec);
	i2c_unरेजिस्टर_device(state->i2c_infoframe);
	i2c_unरेजिस्टर_device(state->i2c_sdp_io);
	i2c_unरेजिस्टर_device(state->i2c_sdp);
	i2c_unरेजिस्टर_device(state->i2c_afe);
	i2c_unरेजिस्टर_device(state->i2c_repeater);
	i2c_unरेजिस्टर_device(state->i2c_edid);
	i2c_unरेजिस्टर_device(state->i2c_hdmi);
	i2c_unरेजिस्टर_device(state->i2c_cp);
	i2c_unरेजिस्टर_device(state->i2c_vdp);

	state->i2c_avlink = शून्य;
	state->i2c_cec = शून्य;
	state->i2c_infoframe = शून्य;
	state->i2c_sdp_io = शून्य;
	state->i2c_sdp = शून्य;
	state->i2c_afe = शून्य;
	state->i2c_repeater = शून्य;
	state->i2c_edid = शून्य;
	state->i2c_hdmi = शून्य;
	state->i2c_cp = शून्य;
	state->i2c_vdp = शून्य;
पूर्ण

अटल काष्ठा i2c_client *adv7842_dummy_client(काष्ठा v4l2_subdev *sd, स्थिर अक्षर *desc,
					       u8 addr, u8 io_reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा i2c_client *cp;

	io_ग_लिखो(sd, io_reg, addr << 1);

	अगर (addr == 0) अणु
		v4l2_err(sd, "no %s i2c addr configured\n", desc);
		वापस शून्य;
	पूर्ण

	cp = i2c_new_dummy_device(client->adapter, io_पढ़ो(sd, io_reg) >> 1);
	अगर (IS_ERR(cp)) अणु
		v4l2_err(sd, "register %s on i2c addr 0x%x failed with %ld\n",
			 desc, addr, PTR_ERR(cp));
		cp = शून्य;
	पूर्ण

	वापस cp;
पूर्ण

अटल पूर्णांक adv7842_रेजिस्टर_clients(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7842_state *state = to_state(sd);
	काष्ठा adv7842_platक्रमm_data *pdata = &state->pdata;

	state->i2c_avlink = adv7842_dummy_client(sd, "avlink", pdata->i2c_avlink, 0xf3);
	state->i2c_cec = adv7842_dummy_client(sd, "cec", pdata->i2c_cec, 0xf4);
	state->i2c_infoframe = adv7842_dummy_client(sd, "infoframe", pdata->i2c_infoframe, 0xf5);
	state->i2c_sdp_io = adv7842_dummy_client(sd, "sdp_io", pdata->i2c_sdp_io, 0xf2);
	state->i2c_sdp = adv7842_dummy_client(sd, "sdp", pdata->i2c_sdp, 0xf1);
	state->i2c_afe = adv7842_dummy_client(sd, "afe", pdata->i2c_afe, 0xf8);
	state->i2c_repeater = adv7842_dummy_client(sd, "repeater", pdata->i2c_repeater, 0xf9);
	state->i2c_edid = adv7842_dummy_client(sd, "edid", pdata->i2c_edid, 0xfa);
	state->i2c_hdmi = adv7842_dummy_client(sd, "hdmi", pdata->i2c_hdmi, 0xfb);
	state->i2c_cp = adv7842_dummy_client(sd, "cp", pdata->i2c_cp, 0xfd);
	state->i2c_vdp = adv7842_dummy_client(sd, "vdp", pdata->i2c_vdp, 0xfe);

	अगर (!state->i2c_avlink ||
	    !state->i2c_cec ||
	    !state->i2c_infoframe ||
	    !state->i2c_sdp_io ||
	    !state->i2c_sdp ||
	    !state->i2c_afe ||
	    !state->i2c_repeater ||
	    !state->i2c_edid ||
	    !state->i2c_hdmi ||
	    !state->i2c_cp ||
	    !state->i2c_vdp)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7842_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adv7842_state *state;
	अटल स्थिर काष्ठा v4l2_dv_timings cea640x480 =
		V4L2_DV_BT_CEA_640X480P59_94;
	काष्ठा adv7842_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_ctrl *ctrl;
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक i;
	u16 rev;
	पूर्णांक err;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_dbg(1, debug, client, "detecting adv7842 client on address 0x%x\n",
		client->addr << 1);

	अगर (!pdata) अणु
		v4l_err(client, "No platform data!\n");
		वापस -ENODEV;
	पूर्ण

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	/* platक्रमm data */
	state->pdata = *pdata;
	state->timings = cea640x480;
	state->क्रमmat = adv7842_क्रमmat_info(state, MEDIA_BUS_FMT_YUYV8_2X8);

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &adv7842_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	sd->पूर्णांकernal_ops = &adv7842_पूर्णांक_ops;
	state->mode = pdata->mode;

	state->hdmi_port_a = pdata->input == ADV7842_SELECT_HDMI_PORT_A;
	state->restart_stdi_once = true;

	/* i2c access to adv7842? */
	rev = adv_smbus_पढ़ो_byte_data_check(client, 0xea, false) << 8 |
		adv_smbus_पढ़ो_byte_data_check(client, 0xeb, false);
	अगर (rev != 0x2012) अणु
		v4l2_info(sd, "got rev=0x%04x on first read attempt\n", rev);
		rev = adv_smbus_पढ़ो_byte_data_check(client, 0xea, false) << 8 |
			adv_smbus_पढ़ो_byte_data_check(client, 0xeb, false);
	पूर्ण
	अगर (rev != 0x2012) अणु
		v4l2_info(sd, "not an adv7842 on address 0x%x (rev=0x%04x)\n",
			  client->addr << 1, rev);
		वापस -ENODEV;
	पूर्ण

	अगर (pdata->chip_reset)
		मुख्य_reset(sd);

	/* control handlers */
	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 6);

	/* add in ascending ID order */
	v4l2_ctrl_new_std(hdl, &adv7842_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &adv7842_ctrl_ops,
			  V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &adv7842_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &adv7842_ctrl_ops,
			  V4L2_CID_HUE, 0, 128, 1, 0);
	ctrl = v4l2_ctrl_new_std_menu(hdl, &adv7842_ctrl_ops,
			V4L2_CID_DV_RX_IT_CONTENT_TYPE, V4L2_DV_IT_CONTENT_TYPE_NO_ITC,
			0, V4L2_DV_IT_CONTENT_TYPE_NO_ITC);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	/* custom controls */
	state->detect_tx_5v_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_RX_POWER_PRESENT, 0, 3, 0, 0);
	state->analog_sampling_phase_ctrl = v4l2_ctrl_new_custom(hdl,
			&adv7842_ctrl_analog_sampling_phase, शून्य);
	state->मुक्त_run_color_ctrl_manual = v4l2_ctrl_new_custom(hdl,
			&adv7842_ctrl_मुक्त_run_color_manual, शून्य);
	state->मुक्त_run_color_ctrl = v4l2_ctrl_new_custom(hdl,
			&adv7842_ctrl_मुक्त_run_color, शून्य);
	state->rgb_quantization_range_ctrl =
		v4l2_ctrl_new_std_menu(hdl, &adv7842_ctrl_ops,
			V4L2_CID_DV_RX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		err = hdl->error;
		जाओ err_hdl;
	पूर्ण
	अगर (adv7842_s_detect_tx_5v_ctrl(sd)) अणु
		err = -ENODEV;
		जाओ err_hdl;
	पूर्ण

	अगर (adv7842_रेजिस्टर_clients(sd) < 0) अणु
		err = -ENOMEM;
		v4l2_err(sd, "failed to create all i2c clients\n");
		जाओ err_i2c;
	पूर्ण


	INIT_DELAYED_WORK(&state->delayed_work_enable_hotplug,
			adv7842_delayed_work_enable_hotplug);

	sd->entity.function = MEDIA_ENT_F_DV_DECODER;
	क्रम (i = 0; i < ADV7842_PAD_SOURCE; ++i)
		state->pads[i].flags = MEDIA_PAD_FL_SINK;
	state->pads[ADV7842_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	err = media_entity_pads_init(&sd->entity, ADV7842_PAD_SOURCE + 1,
				     state->pads);
	अगर (err)
		जाओ err_work_queues;

	err = adv7842_core_init(sd);
	अगर (err)
		जाओ err_entity;

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7842_CEC)
	state->cec_adap = cec_allocate_adapter(&adv7842_cec_adap_ops,
		state, dev_name(&client->dev),
		CEC_CAP_DEFAULTS, ADV7842_MAX_ADDRS);
	err = PTR_ERR_OR_ZERO(state->cec_adap);
	अगर (err)
		जाओ err_entity;
#पूर्ण_अगर

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
		  client->addr << 1, client->adapter->name);
	वापस 0;

err_entity:
	media_entity_cleanup(&sd->entity);
err_work_queues:
	cancel_delayed_work(&state->delayed_work_enable_hotplug);
err_i2c:
	adv7842_unरेजिस्टर_clients(sd);
err_hdl:
	v4l2_ctrl_handler_मुक्त(hdl);
	वापस err;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv7842_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा adv7842_state *state = to_state(sd);

	adv7842_irq_enable(sd, false);
	cancel_delayed_work_sync(&state->delayed_work_enable_hotplug);
	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	adv7842_unरेजिस्टर_clients(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id adv7842_id[] = अणु
	अणु "adv7842", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv7842_id);

/* ----------------------------------------------------------------------- */

अटल काष्ठा i2c_driver adv7842_driver = अणु
	.driver = अणु
		.name = "adv7842",
	पूर्ण,
	.probe = adv7842_probe,
	.हटाओ = adv7842_हटाओ,
	.id_table = adv7842_id,
पूर्ण;

module_i2c_driver(adv7842_driver);
