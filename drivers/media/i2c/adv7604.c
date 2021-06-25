<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adv7604 - Analog Devices ADV7604 video decoder driver
 *
 * Copyright 2012 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 */

/*
 * References (c = chapter, p = page):
 * REF_01 - Analog devices, ADV7604, Register Settings Recommendations,
 *		Revision 2.5, June 2010
 * REF_02 - Analog devices, Register map करोcumentation, Documentation of
 *		the रेजिस्टर maps, Software manual, Rev. F, June 2010
 * REF_03 - Analog devices, ADV7604, Hardware Manual, Rev. F, August 2010
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/i2c/adv7604.h>
#समावेश <media/cec.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-fwnode.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

MODULE_DESCRIPTION("Analog Devices ADV7604 video decoder driver");
MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com>");
MODULE_AUTHOR("Mats Randgaard <mats.randgaard@cisco.com>");
MODULE_LICENSE("GPL");

/* ADV7604 प्रणाली घड़ी frequency */
#घोषणा ADV76XX_FSC (28636360)

#घोषणा ADV76XX_RGB_OUT					(1 << 1)

#घोषणा ADV76XX_OP_FORMAT_SEL_8BIT			(0 << 0)
#घोषणा ADV7604_OP_FORMAT_SEL_10BIT			(1 << 0)
#घोषणा ADV76XX_OP_FORMAT_SEL_12BIT			(2 << 0)

#घोषणा ADV76XX_OP_MODE_SEL_SDR_422			(0 << 5)
#घोषणा ADV7604_OP_MODE_SEL_DDR_422			(1 << 5)
#घोषणा ADV76XX_OP_MODE_SEL_SDR_444			(2 << 5)
#घोषणा ADV7604_OP_MODE_SEL_DDR_444			(3 << 5)
#घोषणा ADV76XX_OP_MODE_SEL_SDR_422_2X			(4 << 5)
#घोषणा ADV7604_OP_MODE_SEL_ADI_CM			(5 << 5)

#घोषणा ADV76XX_OP_CH_SEL_GBR				(0 << 5)
#घोषणा ADV76XX_OP_CH_SEL_GRB				(1 << 5)
#घोषणा ADV76XX_OP_CH_SEL_BGR				(2 << 5)
#घोषणा ADV76XX_OP_CH_SEL_RGB				(3 << 5)
#घोषणा ADV76XX_OP_CH_SEL_BRG				(4 << 5)
#घोषणा ADV76XX_OP_CH_SEL_RBG				(5 << 5)

#घोषणा ADV76XX_OP_SWAP_CB_CR				(1 << 0)

#घोषणा ADV76XX_MAX_ADDRS (3)

#घोषणा ADV76XX_MAX_EDID_BLOCKS 4

क्रमागत adv76xx_type अणु
	ADV7604,
	ADV7611,
	ADV7612,
पूर्ण;

काष्ठा adv76xx_reg_seq अणु
	अचिन्हित पूर्णांक reg;
	u8 val;
पूर्ण;

काष्ठा adv76xx_क्रमmat_info अणु
	u32 code;
	u8 op_ch_sel;
	bool rgb_out;
	bool swap_cb_cr;
	u8 op_क्रमmat_sel;
पूर्ण;

काष्ठा adv76xx_cfg_पढ़ो_infoframe अणु
	स्थिर अक्षर *desc;
	u8 present_mask;
	u8 head_addr;
	u8 payload_addr;
पूर्ण;

काष्ठा adv76xx_chip_info अणु
	क्रमागत adv76xx_type type;

	bool has_afe;
	अचिन्हित पूर्णांक max_port;
	अचिन्हित पूर्णांक num_dv_ports;

	अचिन्हित पूर्णांक edid_enable_reg;
	अचिन्हित पूर्णांक edid_status_reg;
	अचिन्हित पूर्णांक edid_segment_reg;
	अचिन्हित पूर्णांक edid_segment_mask;
	अचिन्हित पूर्णांक edid_spa_loc_reg;
	अचिन्हित पूर्णांक edid_spa_loc_msb_mask;
	अचिन्हित पूर्णांक edid_spa_port_b_reg;
	अचिन्हित पूर्णांक lcf_reg;

	अचिन्हित पूर्णांक cable_det_mask;
	अचिन्हित पूर्णांक tdms_lock_mask;
	अचिन्हित पूर्णांक fmt_change_digital_mask;
	अचिन्हित पूर्णांक cp_csc;

	अचिन्हित पूर्णांक cec_irq_status;
	अचिन्हित पूर्णांक cec_rx_enable;
	अचिन्हित पूर्णांक cec_rx_enable_mask;
	bool cec_irq_swap;

	स्थिर काष्ठा adv76xx_क्रमmat_info *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;

	व्योम (*set_termination)(काष्ठा v4l2_subdev *sd, bool enable);
	व्योम (*setup_irqs)(काष्ठा v4l2_subdev *sd);
	अचिन्हित पूर्णांक (*पढ़ो_hdmi_pixelघड़ी)(काष्ठा v4l2_subdev *sd);
	अचिन्हित पूर्णांक (*पढ़ो_cable_det)(काष्ठा v4l2_subdev *sd);

	/* 0 = AFE, 1 = HDMI */
	स्थिर काष्ठा adv76xx_reg_seq *recommended_settings[2];
	अचिन्हित पूर्णांक num_recommended_settings[2];

	अचिन्हित दीर्घ page_mask;

	/* Masks क्रम timings */
	अचिन्हित पूर्णांक linewidth_mask;
	अचिन्हित पूर्णांक field0_height_mask;
	अचिन्हित पूर्णांक field1_height_mask;
	अचिन्हित पूर्णांक hfrontporch_mask;
	अचिन्हित पूर्णांक hsync_mask;
	अचिन्हित पूर्णांक hbackporch_mask;
	अचिन्हित पूर्णांक field0_vfrontporch_mask;
	अचिन्हित पूर्णांक field1_vfrontporch_mask;
	अचिन्हित पूर्णांक field0_vsync_mask;
	अचिन्हित पूर्णांक field1_vsync_mask;
	अचिन्हित पूर्णांक field0_vbackporch_mask;
	अचिन्हित पूर्णांक field1_vbackporch_mask;
पूर्ण;

/*
 **********************************************************************
 *
 *  Arrays with configuration parameters क्रम the ADV7604
 *
 **********************************************************************
 */

काष्ठा adv76xx_state अणु
	स्थिर काष्ठा adv76xx_chip_info *info;
	काष्ठा adv76xx_platक्रमm_data pdata;

	काष्ठा gpio_desc *hpd_gpio[4];
	काष्ठा gpio_desc *reset_gpio;

	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pads[ADV76XX_PAD_MAX];
	अचिन्हित पूर्णांक source_pad;

	काष्ठा v4l2_ctrl_handler hdl;

	क्रमागत adv76xx_pad selected_input;

	काष्ठा v4l2_dv_timings timings;
	स्थिर काष्ठा adv76xx_क्रमmat_info *क्रमmat;

	काष्ठा अणु
		u8 edid[ADV76XX_MAX_EDID_BLOCKS * 128];
		u32 present;
		अचिन्हित blocks;
	पूर्ण edid;
	u16 spa_port_a[2];
	काष्ठा v4l2_fract aspect_ratio;
	u32 rgb_quantization_range;
	काष्ठा delayed_work delayed_work_enable_hotplug;
	bool restart_stdi_once;

	/* CEC */
	काष्ठा cec_adapter *cec_adap;
	u8   cec_addr[ADV76XX_MAX_ADDRS];
	u8   cec_valid_addrs;
	bool cec_enabled_adap;

	/* i2c clients */
	काष्ठा i2c_client *i2c_clients[ADV76XX_PAGE_MAX];

	/* Regmaps */
	काष्ठा regmap *regmap[ADV76XX_PAGE_MAX];

	/* controls */
	काष्ठा v4l2_ctrl *detect_tx_5v_ctrl;
	काष्ठा v4l2_ctrl *analog_sampling_phase_ctrl;
	काष्ठा v4l2_ctrl *मुक्त_run_color_manual_ctrl;
	काष्ठा v4l2_ctrl *मुक्त_run_color_ctrl;
	काष्ठा v4l2_ctrl *rgb_quantization_range_ctrl;
पूर्ण;

अटल bool adv76xx_has_afe(काष्ठा adv76xx_state *state)
अणु
	वापस state->info->has_afe;
पूर्ण

/* Unsupported timings. This device cannot support 720p30. */
अटल स्थिर काष्ठा v4l2_dv_timings adv76xx_timings_exceptions[] = अणु
	V4L2_DV_BT_CEA_1280X720P30,
	अणु पूर्ण
पूर्ण;

अटल bool adv76xx_check_dv_timings(स्थिर काष्ठा v4l2_dv_timings *t, व्योम *hdl)
अणु
	पूर्णांक i;

	क्रम (i = 0; adv76xx_timings_exceptions[i].bt.width; i++)
		अगर (v4l2_match_dv_timings(t, adv76xx_timings_exceptions + i, 0, false))
			वापस false;
	वापस true;
पूर्ण

काष्ठा adv76xx_video_standards अणु
	काष्ठा v4l2_dv_timings timings;
	u8 vid_std;
	u8 v_freq;
पूर्ण;

/* sorted by number of lines */
अटल स्थिर काष्ठा adv76xx_video_standards adv7604_prim_mode_comp[] = अणु
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
अटल स्थिर काष्ठा adv76xx_video_standards adv7604_prim_mode_gr[] = अणु
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
अटल स्थिर काष्ठा adv76xx_video_standards adv76xx_prim_mode_hdmi_comp[] = अणु
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
अटल स्थिर काष्ठा adv76xx_video_standards adv76xx_prim_mode_hdmi_gr[] = अणु
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

अटल स्थिर काष्ठा v4l2_event adv76xx_ev_fmt = अणु
	.type = V4L2_EVENT_SOURCE_CHANGE,
	.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल अंतरभूत काष्ठा adv76xx_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv76xx_state, sd);
पूर्ण

अटल अंतरभूत अचिन्हित htotal(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_FRAME_WIDTH(t);
पूर्ण

अटल अंतरभूत अचिन्हित vtotal(स्थिर काष्ठा v4l2_bt_timings *t)
अणु
	वापस V4L2_DV_BT_FRAME_HEIGHT(t);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv76xx_पढ़ो_check(काष्ठा adv76xx_state *state,
			     पूर्णांक client_page, u8 reg)
अणु
	काष्ठा i2c_client *client = state->i2c_clients[client_page];
	पूर्णांक err;
	अचिन्हित पूर्णांक val;

	err = regmap_पढ़ो(state->regmap[client_page], reg, &val);

	अगर (err) अणु
		v4l_err(client, "error reading %02x, %02x\n",
				client->addr, reg);
		वापस err;
	पूर्ण
	वापस val;
पूर्ण

/* adv76xx_ग_लिखो_block(): Write raw data with a maximum of I2C_SMBUS_BLOCK_MAX
 * size to one or more रेजिस्टरs.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
अटल पूर्णांक adv76xx_ग_लिखो_block(काष्ठा adv76xx_state *state, पूर्णांक client_page,
			      अचिन्हित पूर्णांक init_reg, स्थिर व्योम *val,
			      माप_प्रकार val_len)
अणु
	काष्ठा regmap *regmap = state->regmap[client_page];

	अगर (val_len > I2C_SMBUS_BLOCK_MAX)
		val_len = I2C_SMBUS_BLOCK_MAX;

	वापस regmap_raw_ग_लिखो(regmap, init_reg, val, val_len);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक io_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_IO, reg);
पूर्ण

अटल अंतरभूत पूर्णांक io_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_IO], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक io_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask,
				   u8 val)
अणु
	वापस io_ग_लिखो(sd, reg, (io_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक avlink_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV7604_PAGE_AVLINK, reg);
पूर्ण

अटल अंतरभूत पूर्णांक avlink_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV7604_PAGE_AVLINK], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cec_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_CEC, reg);
पूर्ण

अटल अंतरभूत पूर्णांक cec_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_CEC], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cec_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask,
				   u8 val)
अणु
	वापस cec_ग_लिखो(sd, reg, (cec_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक infoframe_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_INFOFRAME, reg);
पूर्ण

अटल अंतरभूत पूर्णांक infoframe_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_INFOFRAME], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक afe_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_AFE, reg);
पूर्ण

अटल अंतरभूत पूर्णांक afe_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_AFE], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक rep_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_REP, reg);
पूर्ण

अटल अंतरभूत पूर्णांक rep_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_REP], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक rep_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस rep_ग_लिखो(sd, reg, (rep_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक edid_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_EDID, reg);
पूर्ण

अटल अंतरभूत पूर्णांक edid_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_EDID], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक edid_ग_लिखो_block(काष्ठा v4l2_subdev *sd,
					अचिन्हित पूर्णांक total_len, स्थिर u8 *val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	पूर्णांक err = 0;
	पूर्णांक i = 0;
	पूर्णांक len = 0;

	v4l2_dbg(2, debug, sd, "%s: write EDID block (%d byte)\n",
				__func__, total_len);

	जबतक (!err && i < total_len) अणु
		len = (total_len - i) > I2C_SMBUS_BLOCK_MAX ?
				I2C_SMBUS_BLOCK_MAX :
				(total_len - i);

		err = adv76xx_ग_लिखो_block(state, ADV76XX_PAGE_EDID,
				i, val + i, len);
		i += len;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम adv76xx_set_hpd(काष्ठा adv76xx_state *state, अचिन्हित पूर्णांक hpd)
अणु
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	अचिन्हित पूर्णांक i;

	अगर (info->type == ADV7604) अणु
		क्रम (i = 0; i < state->info->num_dv_ports; ++i)
			gpiod_set_value_cansleep(state->hpd_gpio[i], hpd & BIT(i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < state->info->num_dv_ports; ++i)
			io_ग_लिखो_clr_set(&state->sd, 0x20, 0x80 >> i,
					 (!!(hpd & BIT(i))) << (7 - i));
	पूर्ण

	v4l2_subdev_notअगरy(&state->sd, ADV76XX_HOTPLUG, &hpd);
पूर्ण

अटल व्योम adv76xx_delayed_work_enable_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा adv76xx_state *state = container_of(dwork, काष्ठा adv76xx_state,
						delayed_work_enable_hotplug);
	काष्ठा v4l2_subdev *sd = &state->sd;

	v4l2_dbg(2, debug, sd, "%s: enable hotplug\n", __func__);

	adv76xx_set_hpd(state, state->edid.present);
पूर्ण

अटल अंतरभूत पूर्णांक hdmi_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_HDMI, reg);
पूर्ण

अटल u16 hdmi_पढ़ो16(काष्ठा v4l2_subdev *sd, u8 reg, u16 mask)
अणु
	वापस ((hdmi_पढ़ो(sd, reg) << 8) | hdmi_पढ़ो(sd, reg + 1)) & mask;
पूर्ण

अटल अंतरभूत पूर्णांक hdmi_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_HDMI], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक hdmi_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस hdmi_ग_लिखो(sd, reg, (hdmi_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक test_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_TEST], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cp_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV76XX_PAGE_CP, reg);
पूर्ण

अटल u16 cp_पढ़ो16(काष्ठा v4l2_subdev *sd, u8 reg, u16 mask)
अणु
	वापस ((cp_पढ़ो(sd, reg) << 8) | cp_पढ़ो(sd, reg + 1)) & mask;
पूर्ण

अटल अंतरभूत पूर्णांक cp_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV76XX_PAGE_CP], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक cp_ग_लिखो_clr_set(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask, u8 val)
अणु
	वापस cp_ग_लिखो(sd, reg, (cp_पढ़ो(sd, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत पूर्णांक vdp_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस adv76xx_पढ़ो_check(state, ADV7604_PAGE_VDP, reg);
पूर्ण

अटल अंतरभूत पूर्णांक vdp_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस regmap_ग_लिखो(state->regmap[ADV7604_PAGE_VDP], reg, val);
पूर्ण

#घोषणा ADV76XX_REG(page, offset)	(((page) << 8) | (offset))
#घोषणा ADV76XX_REG_SEQ_TERM		0xffff

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक adv76xx_पढ़ो_reg(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	अचिन्हित पूर्णांक page = reg >> 8;
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	अगर (page >= ADV76XX_PAGE_MAX || !(BIT(page) & state->info->page_mask))
		वापस -EINVAL;

	reg &= 0xff;
	err = regmap_पढ़ो(state->regmap[page], reg, &val);

	वापस err ? err : val;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adv76xx_ग_लिखो_reg(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक reg, u8 val)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	अचिन्हित पूर्णांक page = reg >> 8;

	अगर (page >= ADV76XX_PAGE_MAX || !(BIT(page) & state->info->page_mask))
		वापस -EINVAL;

	reg &= 0xff;

	वापस regmap_ग_लिखो(state->regmap[page], reg, val);
पूर्ण

अटल व्योम adv76xx_ग_लिखो_reg_seq(काष्ठा v4l2_subdev *sd,
				  स्थिर काष्ठा adv76xx_reg_seq *reg_seq)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; reg_seq[i].reg != ADV76XX_REG_SEQ_TERM; i++)
		adv76xx_ग_लिखो_reg(sd, reg_seq[i].reg, reg_seq[i].val);
पूर्ण

/* -----------------------------------------------------------------------------
 * Format helpers
 */

अटल स्थिर काष्ठा adv76xx_क्रमmat_info adv7604_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_RGB888_1X24, ADV76XX_OP_CH_SEL_RGB, true, false,
	  ADV76XX_OP_MODE_SEL_SDR_444 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV10_2X10, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV7604_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU10_2X10, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV7604_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV12_2X12, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU12_2X12, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, ADV76XX_OP_CH_SEL_RBG, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1X16, ADV76XX_OP_CH_SEL_RBG, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1X16, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY10_1X20, ADV76XX_OP_CH_SEL_RBG, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV7604_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY10_1X20, ADV76XX_OP_CH_SEL_RBG, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV7604_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV10_1X20, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV7604_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU10_1X20, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV7604_OP_FORMAT_SEL_10BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY12_1X24, ADV76XX_OP_CH_SEL_RBG, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY12_1X24, ADV76XX_OP_CH_SEL_RBG, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV12_1X24, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU12_1X24, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_क्रमmat_info adv7611_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_RGB888_1X24, ADV76XX_OP_CH_SEL_RGB, true, false,
	  ADV76XX_OP_MODE_SEL_SDR_444 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV12_2X12, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU12_2X12, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, ADV76XX_OP_CH_SEL_RBG, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1X16, ADV76XX_OP_CH_SEL_RBG, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1X16, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY12_1X24, ADV76XX_OP_CH_SEL_RBG, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY12_1X24, ADV76XX_OP_CH_SEL_RBG, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV12_1X24, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU12_1X24, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_12BIT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_क्रमmat_info adv7612_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_RGB888_1X24, ADV76XX_OP_CH_SEL_RGB, true, false,
	  ADV76XX_OP_MODE_SEL_SDR_444 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422 | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, ADV76XX_OP_CH_SEL_RBG, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1X16, ADV76XX_OP_CH_SEL_RBG, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, ADV76XX_OP_CH_SEL_RGB, false, false,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1X16, ADV76XX_OP_CH_SEL_RGB, false, true,
	  ADV76XX_OP_MODE_SEL_SDR_422_2X | ADV76XX_OP_FORMAT_SEL_8BIT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_क्रमmat_info *
adv76xx_क्रमmat_info(काष्ठा adv76xx_state *state, u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < state->info->nक्रमmats; ++i) अणु
		अगर (state->info->क्रमmats[i].code == code)
			वापस &state->info->क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत bool is_analog_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस state->selected_input == ADV7604_PAD_VGA_RGB ||
	       state->selected_input == ADV7604_PAD_VGA_COMP;
पूर्ण

अटल अंतरभूत bool is_digital_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस state->selected_input == ADV76XX_PAD_HDMI_PORT_A ||
	       state->selected_input == ADV7604_PAD_HDMI_PORT_B ||
	       state->selected_input == ADV7604_PAD_HDMI_PORT_C ||
	       state->selected_input == ADV7604_PAD_HDMI_PORT_D;
पूर्ण

अटल स्थिर काष्ठा v4l2_dv_timings_cap adv7604_timings_cap_analog = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1200, 25000000, 170000000,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

अटल स्थिर काष्ठा v4l2_dv_timings_cap adv76xx_timings_cap_digital = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, 1920, 350, 1200, 25000000, 225000000,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

/*
 * Return the DV timings capabilities क्रम the requested sink pad. As a special
 * हाल, pad value -1 वापसs the capabilities क्रम the currently selected input.
 */
अटल स्थिर काष्ठा v4l2_dv_timings_cap *
adv76xx_get_dv_timings_cap(काष्ठा v4l2_subdev *sd, पूर्णांक pad)
अणु
	अगर (pad == -1) अणु
		काष्ठा adv76xx_state *state = to_state(sd);

		pad = state->selected_input;
	पूर्ण

	चयन (pad) अणु
	हाल ADV76XX_PAD_HDMI_PORT_A:
	हाल ADV7604_PAD_HDMI_PORT_B:
	हाल ADV7604_PAD_HDMI_PORT_C:
	हाल ADV7604_PAD_HDMI_PORT_D:
		वापस &adv76xx_timings_cap_digital;

	हाल ADV7604_PAD_VGA_RGB:
	हाल ADV7604_PAD_VGA_COMP:
	शेष:
		वापस &adv7604_timings_cap_analog;
	पूर्ण
पूर्ण


/* ----------------------------------------------------------------------- */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल व्योम adv76xx_inv_रेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_info(sd, "0x000-0x0ff: IO Map\n");
	v4l2_info(sd, "0x100-0x1ff: AVLink Map\n");
	v4l2_info(sd, "0x200-0x2ff: CEC Map\n");
	v4l2_info(sd, "0x300-0x3ff: InfoFrame Map\n");
	v4l2_info(sd, "0x400-0x4ff: ESDP Map\n");
	v4l2_info(sd, "0x500-0x5ff: DPP Map\n");
	v4l2_info(sd, "0x600-0x6ff: AFE Map\n");
	v4l2_info(sd, "0x700-0x7ff: Repeater Map\n");
	v4l2_info(sd, "0x800-0x8ff: EDID Map\n");
	v4l2_info(sd, "0x900-0x9ff: HDMI Map\n");
	v4l2_info(sd, "0xa00-0xaff: Test Map\n");
	v4l2_info(sd, "0xb00-0xbff: CP Map\n");
	v4l2_info(sd, "0xc00-0xcff: VDP Map\n");
पूर्ण

अटल पूर्णांक adv76xx_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	पूर्णांक ret;

	ret = adv76xx_पढ़ो_reg(sd, reg->reg);
	अगर (ret < 0) अणु
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv76xx_inv_रेजिस्टर(sd);
		वापस ret;
	पूर्ण

	reg->size = 1;
	reg->val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
					स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	पूर्णांक ret;

	ret = adv76xx_ग_लिखो_reg(sd, reg->reg, reg->val);
	अगर (ret < 0) अणु
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv76xx_inv_रेजिस्टर(sd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक adv7604_पढ़ो_cable_det(काष्ठा v4l2_subdev *sd)
अणु
	u8 value = io_पढ़ो(sd, 0x6f);

	वापस ((value & 0x10) >> 4)
	     | ((value & 0x08) >> 2)
	     | ((value & 0x04) << 0)
	     | ((value & 0x02) << 2);
पूर्ण

अटल अचिन्हित पूर्णांक adv7611_पढ़ो_cable_det(काष्ठा v4l2_subdev *sd)
अणु
	u8 value = io_पढ़ो(sd, 0x6f);

	वापस value & 1;
पूर्ण

अटल अचिन्हित पूर्णांक adv7612_पढ़ो_cable_det(काष्ठा v4l2_subdev *sd)
अणु
	/*  Reads CABLE_DET_A_RAW. For input B support, need to
	 *  account क्रम bit 7 [MSB] of 0x6a (ie. CABLE_DET_B_RAW)
	 */
	u8 value = io_पढ़ो(sd, 0x6f);

	वापस value & 1;
पूर्ण

अटल पूर्णांक adv76xx_s_detect_tx_5v_ctrl(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	u16 cable_det = info->पढ़ो_cable_det(sd);

	वापस v4l2_ctrl_s_ctrl(state->detect_tx_5v_ctrl, cable_det);
पूर्ण

अटल पूर्णांक find_and_set_predefined_video_timings(काष्ठा v4l2_subdev *sd,
		u8 prim_mode,
		स्थिर काष्ठा adv76xx_video_standards *predef_vid_timings,
		स्थिर काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक i;

	क्रम (i = 0; predef_vid_timings[i].timings.bt.width; i++) अणु
		अगर (!v4l2_match_dv_timings(timings, &predef_vid_timings[i].timings,
				is_digital_input(sd) ? 250000 : 1000000, false))
			जारी;
		io_ग_लिखो(sd, 0x00, predef_vid_timings[i].vid_std); /* video std */
		io_ग_लिखो(sd, 0x01, (predef_vid_timings[i].v_freq << 4) +
				prim_mode); /* v_freq and prim mode */
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक configure_predefined_video_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	पूर्णांक err;

	v4l2_dbg(1, debug, sd, "%s", __func__);

	अगर (adv76xx_has_afe(state)) अणु
		/* reset to शेष values */
		io_ग_लिखो(sd, 0x16, 0x43);
		io_ग_लिखो(sd, 0x17, 0x5a);
	पूर्ण
	/* disable embedded syncs क्रम स्वतः graphics mode */
	cp_ग_लिखो_clr_set(sd, 0x81, 0x10, 0x00);
	cp_ग_लिखो(sd, 0x8f, 0x00);
	cp_ग_लिखो(sd, 0x90, 0x00);
	cp_ग_लिखो(sd, 0xa2, 0x00);
	cp_ग_लिखो(sd, 0xa3, 0x00);
	cp_ग_लिखो(sd, 0xa4, 0x00);
	cp_ग_लिखो(sd, 0xa5, 0x00);
	cp_ग_लिखो(sd, 0xa6, 0x00);
	cp_ग_लिखो(sd, 0xa7, 0x00);
	cp_ग_लिखो(sd, 0xab, 0x00);
	cp_ग_लिखो(sd, 0xac, 0x00);

	अगर (is_analog_input(sd)) अणु
		err = find_and_set_predefined_video_timings(sd,
				0x01, adv7604_prim_mode_comp, timings);
		अगर (err)
			err = find_and_set_predefined_video_timings(sd,
					0x02, adv7604_prim_mode_gr, timings);
	पूर्ण अन्यथा अगर (is_digital_input(sd)) अणु
		err = find_and_set_predefined_video_timings(sd,
				0x05, adv76xx_prim_mode_hdmi_comp, timings);
		अगर (err)
			err = find_and_set_predefined_video_timings(sd,
					0x06, adv76xx_prim_mode_hdmi_gr, timings);
	पूर्ण अन्यथा अणु
		v4l2_dbg(2, debug, sd, "%s: Unknown port %d selected\n",
				__func__, state->selected_input);
		err = -1;
	पूर्ण


	वापस err;
पूर्ण

अटल व्योम configure_custom_video_timings(काष्ठा v4l2_subdev *sd,
		स्थिर काष्ठा v4l2_bt_timings *bt)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	u32 width = htotal(bt);
	u32 height = vtotal(bt);
	u16 cp_start_sav = bt->hsync + bt->hbackporch - 4;
	u16 cp_start_eav = width - bt->hfrontporch;
	u16 cp_start_vbi = height - bt->vfrontporch;
	u16 cp_end_vbi = bt->vsync + bt->vbackporch;
	u16 ch1_fr_ll = (((u32)bt->pixelघड़ी / 100) > 0) ?
		((width * (ADV76XX_FSC / 100)) / ((u32)bt->pixelघड़ी / 100)) : 0;
	स्थिर u8 pll[2] = अणु
		0xc0 | ((width >> 8) & 0x1f),
		width & 0xff
	पूर्ण;

	v4l2_dbg(2, debug, sd, "%s\n", __func__);

	अगर (is_analog_input(sd)) अणु
		/* स्वतः graphics */
		io_ग_लिखो(sd, 0x00, 0x07); /* video std */
		io_ग_लिखो(sd, 0x01, 0x02); /* prim mode */
		/* enable embedded syncs क्रम स्वतः graphics mode */
		cp_ग_लिखो_clr_set(sd, 0x81, 0x10, 0x10);

		/* Should only be set in स्वतः-graphics mode [REF_02, p. 91-92] */
		/* setup PLL_DIV_MAN_EN and PLL_DIV_RATIO */
		/* IO-map reg. 0x16 and 0x17 should be written in sequence */
		अगर (regmap_raw_ग_लिखो(state->regmap[ADV76XX_PAGE_IO],
					0x16, pll, 2))
			v4l2_err(sd, "writing to reg 0x16 and 0x17 failed\n");

		/* active video - horizontal timing */
		cp_ग_लिखो(sd, 0xa2, (cp_start_sav >> 4) & 0xff);
		cp_ग_लिखो(sd, 0xa3, ((cp_start_sav & 0x0f) << 4) |
				   ((cp_start_eav >> 8) & 0x0f));
		cp_ग_लिखो(sd, 0xa4, cp_start_eav & 0xff);

		/* active video - vertical timing */
		cp_ग_लिखो(sd, 0xa5, (cp_start_vbi >> 4) & 0xff);
		cp_ग_लिखो(sd, 0xa6, ((cp_start_vbi & 0xf) << 4) |
				   ((cp_end_vbi >> 8) & 0xf));
		cp_ग_लिखो(sd, 0xa7, cp_end_vbi & 0xff);
	पूर्ण अन्यथा अगर (is_digital_input(sd)) अणु
		/* set शेष prim_mode/vid_std क्रम HDMI
		   according to [REF_03, c. 4.2] */
		io_ग_लिखो(sd, 0x00, 0x02); /* video std */
		io_ग_लिखो(sd, 0x01, 0x06); /* prim mode */
	पूर्ण अन्यथा अणु
		v4l2_dbg(2, debug, sd, "%s: Unknown port %d selected\n",
				__func__, state->selected_input);
	पूर्ण

	cp_ग_लिखो(sd, 0x8f, (ch1_fr_ll >> 8) & 0x7);
	cp_ग_लिखो(sd, 0x90, ch1_fr_ll & 0xff);
	cp_ग_लिखो(sd, 0xab, (height >> 4) & 0xff);
	cp_ग_लिखो(sd, 0xac, (height & 0x0f) << 4);
पूर्ण

अटल व्योम adv76xx_set_offset(काष्ठा v4l2_subdev *sd, bool स्वतः_offset, u16 offset_a, u16 offset_b, u16 offset_c)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	u8 offset_buf[4];

	अगर (स्वतः_offset) अणु
		offset_a = 0x3ff;
		offset_b = 0x3ff;
		offset_c = 0x3ff;
	पूर्ण

	v4l2_dbg(2, debug, sd, "%s: %s offset: a = 0x%x, b = 0x%x, c = 0x%x\n",
			__func__, स्वतः_offset ? "Auto" : "Manual",
			offset_a, offset_b, offset_c);

	offset_buf[0] = (cp_पढ़ो(sd, 0x77) & 0xc0) | ((offset_a & 0x3f0) >> 4);
	offset_buf[1] = ((offset_a & 0x00f) << 4) | ((offset_b & 0x3c0) >> 6);
	offset_buf[2] = ((offset_b & 0x03f) << 2) | ((offset_c & 0x300) >> 8);
	offset_buf[3] = offset_c & 0x0ff;

	/* Registers must be written in this order with no i2c access in between */
	अगर (regmap_raw_ग_लिखो(state->regmap[ADV76XX_PAGE_CP],
			0x77, offset_buf, 4))
		v4l2_err(sd, "%s: i2c error writing to CP reg 0x77, 0x78, 0x79, 0x7a\n", __func__);
पूर्ण

अटल व्योम adv76xx_set_gain(काष्ठा v4l2_subdev *sd, bool स्वतः_gain, u16 gain_a, u16 gain_b, u16 gain_c)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
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
	अगर (regmap_raw_ग_लिखो(state->regmap[ADV76XX_PAGE_CP],
			     0x73, gain_buf, 4))
		v4l2_err(sd, "%s: i2c error writing to CP reg 0x73, 0x74, 0x75, 0x76\n", __func__);
पूर्ण

अटल व्योम set_rgb_quantization_range(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	bool rgb_output = io_पढ़ो(sd, 0x02) & 0x02;
	bool hdmi_संकेत = hdmi_पढ़ो(sd, 0x05) & 0x80;
	u8 y = HDMI_COLORSPACE_RGB;

	अगर (hdmi_संकेत && (io_पढ़ो(sd, 0x60) & 1))
		y = infoframe_पढ़ो(sd, 0x01) >> 5;

	v4l2_dbg(2, debug, sd, "%s: RGB quantization range: %d, RGB out: %d, HDMI: %d\n",
			__func__, state->rgb_quantization_range,
			rgb_output, hdmi_संकेत);

	adv76xx_set_gain(sd, true, 0x0, 0x0, 0x0);
	adv76xx_set_offset(sd, true, 0x0, 0x0, 0x0);
	io_ग_लिखो_clr_set(sd, 0x02, 0x04, rgb_output ? 0 : 4);

	चयन (state->rgb_quantization_range) अणु
	हाल V4L2_DV_RGB_RANGE_AUTO:
		अगर (state->selected_input == ADV7604_PAD_VGA_RGB) अणु
			/* Receiving analog RGB संकेत
			 * Set RGB full range (0-255) */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x10);
			अवरोध;
		पूर्ण

		अगर (state->selected_input == ADV7604_PAD_VGA_COMP) अणु
			/* Receiving analog YPbPr संकेत
			 * Set स्वतःmode */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0xf0);
			अवरोध;
		पूर्ण

		अगर (hdmi_संकेत) अणु
			/* Receiving HDMI संकेत
			 * Set स्वतःmode */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0xf0);
			अवरोध;
		पूर्ण

		/* Receiving DVI-D संकेत
		 * ADV7604 selects RGB limited range regardless of
		 * input क्रमmat (CE/IT) in स्वतःmatic mode */
		अगर (state->timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
			/* RGB limited range (16-235) */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x00);
		पूर्ण अन्यथा अणु
			/* RGB full range (0-255) */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x10);

			अगर (is_digital_input(sd) && rgb_output) अणु
				adv76xx_set_offset(sd, false, 0x40, 0x40, 0x40);
			पूर्ण अन्यथा अणु
				adv76xx_set_gain(sd, false, 0xe0, 0xe0, 0xe0);
				adv76xx_set_offset(sd, false, 0x70, 0x70, 0x70);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल V4L2_DV_RGB_RANGE_LIMITED:
		अगर (state->selected_input == ADV7604_PAD_VGA_COMP) अणु
			/* YCrCb limited range (16-235) */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x20);
			अवरोध;
		पूर्ण

		अगर (y != HDMI_COLORSPACE_RGB)
			अवरोध;

		/* RGB limited range (16-235) */
		io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x00);

		अवरोध;
	हाल V4L2_DV_RGB_RANGE_FULL:
		अगर (state->selected_input == ADV7604_PAD_VGA_COMP) अणु
			/* YCrCb full range (0-255) */
			io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x60);
			अवरोध;
		पूर्ण

		अगर (y != HDMI_COLORSPACE_RGB)
			अवरोध;

		/* RGB full range (0-255) */
		io_ग_लिखो_clr_set(sd, 0x02, 0xf0, 0x10);

		अगर (is_analog_input(sd) || hdmi_संकेत)
			अवरोध;

		/* Adjust gain/offset क्रम DVI-D संकेतs only */
		अगर (rgb_output) अणु
			adv76xx_set_offset(sd, false, 0x40, 0x40, 0x40);
		पूर्ण अन्यथा अणु
			adv76xx_set_gain(sd, false, 0xe0, 0xe0, 0xe0);
			adv76xx_set_offset(sd, false, 0x70, 0x70, 0x70);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक adv76xx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd =
		&container_of(ctrl->handler, काष्ठा adv76xx_state, hdl)->sd;

	काष्ठा adv76xx_state *state = to_state(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		cp_ग_लिखो(sd, 0x3c, ctrl->val);
		वापस 0;
	हाल V4L2_CID_CONTRAST:
		cp_ग_लिखो(sd, 0x3a, ctrl->val);
		वापस 0;
	हाल V4L2_CID_SATURATION:
		cp_ग_लिखो(sd, 0x3b, ctrl->val);
		वापस 0;
	हाल V4L2_CID_HUE:
		cp_ग_लिखो(sd, 0x3d, ctrl->val);
		वापस 0;
	हाल  V4L2_CID_DV_RX_RGB_RANGE:
		state->rgb_quantization_range = ctrl->val;
		set_rgb_quantization_range(sd);
		वापस 0;
	हाल V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE:
		अगर (!adv76xx_has_afe(state))
			वापस -EINVAL;
		/* Set the analog sampling phase. This is needed to find the
		   best sampling phase क्रम analog video: an application or
		   driver has to try a number of phases and analyze the picture
		   quality beक्रमe settling on the best perक्रमming phase. */
		afe_ग_लिखो(sd, 0xc8, ctrl->val);
		वापस 0;
	हाल V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL:
		/* Use the शेष blue color क्रम मुक्त running mode,
		   or supply your own. */
		cp_ग_लिखो_clr_set(sd, 0xbf, 0x04, ctrl->val << 2);
		वापस 0;
	हाल V4L2_CID_ADV_RX_FREE_RUN_COLOR:
		cp_ग_लिखो(sd, 0xc0, (ctrl->val & 0xff0000) >> 16);
		cp_ग_लिखो(sd, 0xc1, (ctrl->val & 0x00ff00) >> 8);
		cp_ग_लिखो(sd, 0xc2, (u8)(ctrl->val & 0x0000ff));
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adv76xx_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd =
		&container_of(ctrl->handler, काष्ठा adv76xx_state, hdl)->sd;

	अगर (ctrl->id == V4L2_CID_DV_RX_IT_CONTENT_TYPE) अणु
		ctrl->val = V4L2_DV_IT_CONTENT_TYPE_NO_ITC;
		अगर ((io_पढ़ो(sd, 0x60) & 1) && (infoframe_पढ़ो(sd, 0x03) & 0x80))
			ctrl->val = (infoframe_पढ़ो(sd, 0x05) >> 4) & 3;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत bool no_घातer(काष्ठा v4l2_subdev *sd)
अणु
	/* Entire chip or CP घातered off */
	वापस io_पढ़ो(sd, 0x0c) & 0x24;
पूर्ण

अटल अंतरभूत bool no_संकेत_पंचांगds(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	वापस !(io_पढ़ो(sd, 0x6a) & (0x10 >> state->selected_input));
पूर्ण

अटल अंतरभूत bool no_lock_पंचांगds(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;

	वापस (io_पढ़ो(sd, 0x6a) & info->tdms_lock_mask) != info->tdms_lock_mask;
पूर्ण

अटल अंतरभूत bool is_hdmi(काष्ठा v4l2_subdev *sd)
अणु
	वापस hdmi_पढ़ो(sd, 0x05) & 0x80;
पूर्ण

अटल अंतरभूत bool no_lock_sspd(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	/*
	 * Chips without a AFE करोn't expose रेजिस्टरs क्रम the SSPD, so just assume
	 * that we have a lock.
	 */
	अगर (adv76xx_has_afe(state))
		वापस false;

	/* TODO channel 2 */
	वापस ((cp_पढ़ो(sd, 0xb5) & 0xd0) != 0xd0);
पूर्ण

अटल अंतरभूत bool no_lock_stdi(काष्ठा v4l2_subdev *sd)
अणु
	/* TODO channel 2 */
	वापस !(cp_पढ़ो(sd, 0xb1) & 0x80);
पूर्ण

अटल अंतरभूत bool no_संकेत(काष्ठा v4l2_subdev *sd)
अणु
	bool ret;

	ret = no_घातer(sd);

	ret |= no_lock_stdi(sd);
	ret |= no_lock_sspd(sd);

	अगर (is_digital_input(sd)) अणु
		ret |= no_lock_पंचांगds(sd);
		ret |= no_संकेत_पंचांगds(sd);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत bool no_lock_cp(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	अगर (!adv76xx_has_afe(state))
		वापस false;

	/* CP has detected a non standard number of lines on the incoming
	   video compared to what it is configured to receive by s_dv_timings */
	वापस io_पढ़ो(sd, 0x12) & 0x01;
पूर्ण

अटल अंतरभूत bool in_मुक्त_run(काष्ठा v4l2_subdev *sd)
अणु
	वापस cp_पढ़ो(sd, 0xff) & 0x10;
पूर्ण

अटल पूर्णांक adv76xx_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	*status = 0;
	*status |= no_घातer(sd) ? V4L2_IN_ST_NO_POWER : 0;
	*status |= no_संकेत(sd) ? V4L2_IN_ST_NO_SIGNAL : 0;
	अगर (!in_मुक्त_run(sd) && no_lock_cp(sd))
		*status |= is_digital_input(sd) ?
			   V4L2_IN_ST_NO_SYNC : V4L2_IN_ST_NO_H_LOCK;

	v4l2_dbg(1, debug, sd, "%s: status = 0x%x\n", __func__, *status);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

काष्ठा stdi_पढ़ोback अणु
	u16 bl, lcf, lcvs;
	u8 hs_pol, vs_pol;
	bool पूर्णांकerlaced;
पूर्ण;

अटल पूर्णांक stdi2dv_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा stdi_पढ़ोback *stdi,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	u32 hfreq = (ADV76XX_FSC * 8) / stdi->bl;
	u32 pix_clk;
	पूर्णांक i;

	क्रम (i = 0; v4l2_dv_timings_presets[i].bt.width; i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *bt = &v4l2_dv_timings_presets[i].bt;

		अगर (!v4l2_valid_dv_timings(&v4l2_dv_timings_presets[i],
					   adv76xx_get_dv_timings_cap(sd, -1),
					   adv76xx_check_dv_timings, शून्य))
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
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	u8 polarity;

	अगर (no_lock_stdi(sd) || no_lock_sspd(sd)) अणु
		v4l2_dbg(2, debug, sd, "%s: STDI and/or SSPD not locked\n", __func__);
		वापस -1;
	पूर्ण

	/* पढ़ो STDI */
	stdi->bl = cp_पढ़ो16(sd, 0xb1, 0x3fff);
	stdi->lcf = cp_पढ़ो16(sd, info->lcf_reg, 0x7ff);
	stdi->lcvs = cp_पढ़ो(sd, 0xb3) >> 3;
	stdi->पूर्णांकerlaced = io_पढ़ो(sd, 0x12) & 0x10;

	अगर (adv76xx_has_afe(state)) अणु
		/* पढ़ो SSPD */
		polarity = cp_पढ़ो(sd, 0xb5);
		अगर ((polarity & 0x03) == 0x01) अणु
			stdi->hs_pol = polarity & 0x10
				     ? (polarity & 0x08 ? '+' : '-') : 'x';
			stdi->vs_pol = polarity & 0x40
				     ? (polarity & 0x20 ? '+' : '-') : 'x';
		पूर्ण अन्यथा अणु
			stdi->hs_pol = 'x';
			stdi->vs_pol = 'x';
		पूर्ण
	पूर्ण अन्यथा अणु
		polarity = hdmi_पढ़ो(sd, 0x05);
		stdi->hs_pol = polarity & 0x20 ? '+' : '-';
		stdi->vs_pol = polarity & 0x10 ? '+' : '-';
	पूर्ण

	अगर (no_lock_stdi(sd) || no_lock_sspd(sd)) अणु
		v4l2_dbg(2, debug, sd,
			"%s: signal lost during readout of STDI/SSPD\n", __func__);
		वापस -1;
	पूर्ण

	अगर (stdi->lcf < 239 || stdi->bl < 8 || stdi->bl == 0x3fff) अणु
		v4l2_dbg(2, debug, sd, "%s: invalid signal\n", __func__);
		स_रखो(stdi, 0, माप(काष्ठा stdi_पढ़ोback));
		वापस -1;
	पूर्ण

	v4l2_dbg(2, debug, sd,
		"%s: lcf (frame height - 1) = %d, bl = %d, lcvs (vsync) = %d, %chsync, %cvsync, %s\n",
		__func__, stdi->lcf, stdi->bl, stdi->lcvs,
		stdi->hs_pol, stdi->vs_pol,
		stdi->पूर्णांकerlaced ? "interlaced" : "progressive");

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	अगर (timings->pad >= state->source_pad)
		वापस -EINVAL;

	वापस v4l2_क्रमागत_dv_timings_cap(timings,
		adv76xx_get_dv_timings_cap(sd, timings->pad),
		adv76xx_check_dv_timings, शून्य);
पूर्ण

अटल पूर्णांक adv76xx_dv_timings_cap(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	अचिन्हित पूर्णांक pad = cap->pad;

	अगर (cap->pad >= state->source_pad)
		वापस -EINVAL;

	*cap = *adv76xx_get_dv_timings_cap(sd, pad);
	cap->pad = pad;

	वापस 0;
पूर्ण

/* Fill the optional fields .standards and .flags in काष्ठा v4l2_dv_timings
   अगर the क्रमmat is listed in adv76xx_timings[] */
अटल व्योम adv76xx_fill_optional_dv_timings_fields(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	v4l2_find_dv_timings_cap(timings, adv76xx_get_dv_timings_cap(sd, -1),
				 is_digital_input(sd) ? 250000 : 1000000,
				 adv76xx_check_dv_timings, शून्य);
पूर्ण

अटल अचिन्हित पूर्णांक adv7604_पढ़ो_hdmi_pixelघड़ी(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक a, b;

	a = hdmi_पढ़ो(sd, 0x06);
	b = hdmi_पढ़ो(sd, 0x3b);
	अगर (a < 0 || b < 0)
		वापस 0;

	वापस a * 1000000 + ((b & 0x30) >> 4) * 250000;
पूर्ण

अटल अचिन्हित पूर्णांक adv7611_पढ़ो_hdmi_pixelघड़ी(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक a, b;

	a = hdmi_पढ़ो(sd, 0x51);
	b = hdmi_पढ़ो(sd, 0x52);
	अगर (a < 0 || b < 0)
		वापस 0;

	वापस ((a << 1) | (b >> 7)) * 1000000 + (b & 0x7f) * 1000000 / 128;
पूर्ण

अटल अचिन्हित पूर्णांक adv76xx_पढ़ो_hdmi_pixelघड़ी(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	अचिन्हित पूर्णांक freq, bits_per_channel, pixelrepetition;

	freq = info->पढ़ो_hdmi_pixelघड़ी(sd);
	अगर (is_hdmi(sd)) अणु
		/* adjust क्रम deep color mode and pixel repetition */
		bits_per_channel = ((hdmi_पढ़ो(sd, 0x0b) & 0x60) >> 4) + 8;
		pixelrepetition = (hdmi_पढ़ो(sd, 0x05) & 0x0f) + 1;

		freq = freq * 8 / bits_per_channel / pixelrepetition;
	पूर्ण

	वापस freq;
पूर्ण

अटल पूर्णांक adv76xx_query_dv_timings(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	काष्ठा stdi_पढ़ोback stdi;

	अगर (!timings)
		वापस -EINVAL;

	स_रखो(timings, 0, माप(काष्ठा v4l2_dv_timings));

	अगर (no_संकेत(sd)) अणु
		state->restart_stdi_once = true;
		v4l2_dbg(1, debug, sd, "%s: no valid signal\n", __func__);
		वापस -ENOLINK;
	पूर्ण

	/* पढ़ो STDI */
	अगर (पढ़ो_stdi(sd, &stdi)) अणु
		v4l2_dbg(1, debug, sd, "%s: STDI/SSPD not locked\n", __func__);
		वापस -ENOLINK;
	पूर्ण
	bt->पूर्णांकerlaced = stdi.पूर्णांकerlaced ?
		V4L2_DV_INTERLACED : V4L2_DV_PROGRESSIVE;

	अगर (is_digital_input(sd)) अणु
		bool hdmi_संकेत = hdmi_पढ़ो(sd, 0x05) & 0x80;
		u8 vic = 0;
		u32 w, h;

		w = hdmi_पढ़ो16(sd, 0x07, info->linewidth_mask);
		h = hdmi_पढ़ो16(sd, 0x09, info->field0_height_mask);

		अगर (hdmi_संकेत && (io_पढ़ो(sd, 0x60) & 1))
			vic = infoframe_पढ़ो(sd, 0x04);

		अगर (vic && v4l2_find_dv_timings_cea861_vic(timings, vic) &&
		    bt->width == w && bt->height == h)
			जाओ found;

		timings->type = V4L2_DV_BT_656_1120;

		bt->width = w;
		bt->height = h;
		bt->pixelघड़ी = adv76xx_पढ़ो_hdmi_pixelघड़ी(sd);
		bt->hfrontporch = hdmi_पढ़ो16(sd, 0x20, info->hfrontporch_mask);
		bt->hsync = hdmi_पढ़ो16(sd, 0x22, info->hsync_mask);
		bt->hbackporch = hdmi_पढ़ो16(sd, 0x24, info->hbackporch_mask);
		bt->vfrontporch = hdmi_पढ़ो16(sd, 0x2a,
			info->field0_vfrontporch_mask) / 2;
		bt->vsync = hdmi_पढ़ो16(sd, 0x2e, info->field0_vsync_mask) / 2;
		bt->vbackporch = hdmi_पढ़ो16(sd, 0x32,
			info->field0_vbackporch_mask) / 2;
		bt->polarities = ((hdmi_पढ़ो(sd, 0x05) & 0x10) ? V4L2_DV_VSYNC_POS_POL : 0) |
			((hdmi_पढ़ो(sd, 0x05) & 0x20) ? V4L2_DV_HSYNC_POS_POL : 0);
		अगर (bt->पूर्णांकerlaced == V4L2_DV_INTERLACED) अणु
			bt->height += hdmi_पढ़ो16(sd, 0x0b,
				info->field1_height_mask);
			bt->il_vfrontporch = hdmi_पढ़ो16(sd, 0x2c,
				info->field1_vfrontporch_mask) / 2;
			bt->il_vsync = hdmi_पढ़ो16(sd, 0x30,
				info->field1_vsync_mask) / 2;
			bt->il_vbackporch = hdmi_पढ़ो16(sd, 0x34,
				info->field1_vbackporch_mask) / 2;
		पूर्ण
		adv76xx_fill_optional_dv_timings_fields(sd, timings);
	पूर्ण अन्यथा अणु
		/* find क्रमmat
		 * Since LCVS values are inaccurate [REF_03, p. 275-276],
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
				cp_ग_लिखो_clr_set(sd, 0x86, 0x06, 0x00);
				/* trigger STDI restart */
				cp_ग_लिखो_clr_set(sd, 0x86, 0x06, 0x04);
				/* reset to continuous mode */
				cp_ग_लिखो_clr_set(sd, 0x86, 0x06, 0x02);
				state->restart_stdi_once = false;
				वापस -ENOLINK;
			पूर्ण
			v4l2_dbg(1, debug, sd, "%s: format not supported\n", __func__);
			वापस -दुस्फल;
		पूर्ण
		state->restart_stdi_once = true;
	पूर्ण
found:

	अगर (no_संकेत(sd)) अणु
		v4l2_dbg(1, debug, sd, "%s: signal lost during readout\n", __func__);
		स_रखो(timings, 0, माप(काष्ठा v4l2_dv_timings));
		वापस -ENOLINK;
	पूर्ण

	अगर ((is_analog_input(sd) && bt->pixelघड़ी > 170000000) ||
			(is_digital_input(sd) && bt->pixelघड़ी > 225000000)) अणु
		v4l2_dbg(1, debug, sd, "%s: pixelclock out of range %d\n",
				__func__, (u32)bt->pixelघड़ी);
		वापस -दुस्फल;
	पूर्ण

	अगर (debug > 1)
		v4l2_prपूर्णांक_dv_timings(sd->name, "adv76xx_query_dv_timings: ",
				      timings, true);

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_s_dv_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	काष्ठा v4l2_bt_timings *bt;
	पूर्णांक err;

	अगर (!timings)
		वापस -EINVAL;

	अगर (v4l2_match_dv_timings(&state->timings, timings, 0, false)) अणु
		v4l2_dbg(1, debug, sd, "%s: no change\n", __func__);
		वापस 0;
	पूर्ण

	bt = &timings->bt;

	अगर (!v4l2_valid_dv_timings(timings, adv76xx_get_dv_timings_cap(sd, -1),
				   adv76xx_check_dv_timings, शून्य))
		वापस -दुस्फल;

	adv76xx_fill_optional_dv_timings_fields(sd, timings);

	state->timings = *timings;

	cp_ग_लिखो_clr_set(sd, 0x91, 0x40, bt->पूर्णांकerlaced ? 0x40 : 0x00);

	/* Use prim_mode and vid_std when available */
	err = configure_predefined_video_timings(sd, timings);
	अगर (err) अणु
		/* custom settings when the video क्रमmat
		 करोes not have prim_mode/vid_std */
		configure_custom_video_timings(sd, bt);
	पूर्ण

	set_rgb_quantization_range(sd);

	अगर (debug > 1)
		v4l2_prपूर्णांक_dv_timings(sd->name, "adv76xx_s_dv_timings: ",
				      timings, true);
	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_g_dv_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	*timings = state->timings;
	वापस 0;
पूर्ण

अटल व्योम adv7604_set_termination(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	hdmi_ग_लिखो(sd, 0x01, enable ? 0x00 : 0x78);
पूर्ण

अटल व्योम adv7611_set_termination(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	hdmi_ग_लिखो(sd, 0x83, enable ? 0xfe : 0xff);
पूर्ण

अटल व्योम enable_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	अगर (is_analog_input(sd)) अणु
		io_ग_लिखो(sd, 0x15, 0xb0);   /* Disable Tristate of Pins (no audio) */
	पूर्ण अन्यथा अगर (is_digital_input(sd)) अणु
		hdmi_ग_लिखो_clr_set(sd, 0x00, 0x03, state->selected_input);
		state->info->set_termination(sd, true);
		io_ग_लिखो(sd, 0x15, 0xa0);   /* Disable Tristate of Pins */
		hdmi_ग_लिखो_clr_set(sd, 0x1a, 0x10, 0x00); /* Unmute audio */
	पूर्ण अन्यथा अणु
		v4l2_dbg(2, debug, sd, "%s: Unknown port %d selected\n",
				__func__, state->selected_input);
	पूर्ण
पूर्ण

अटल व्योम disable_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	hdmi_ग_लिखो_clr_set(sd, 0x1a, 0x10, 0x10); /* Mute audio */
	msleep(16); /* 512 samples with >= 32 kHz sample rate [REF_03, c. 7.16.10] */
	io_ग_लिखो(sd, 0x15, 0xbe);   /* Tristate all outमाला_दो from video core */
	state->info->set_termination(sd, false);
पूर्ण

अटल व्योम select_input(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;

	अगर (is_analog_input(sd)) अणु
		adv76xx_ग_लिखो_reg_seq(sd, info->recommended_settings[0]);

		afe_ग_लिखो(sd, 0x00, 0x08); /* घातer up ADC */
		afe_ग_लिखो(sd, 0x01, 0x06); /* घातer up Analog Front End */
		afe_ग_लिखो(sd, 0xc8, 0x00); /* phase control */
	पूर्ण अन्यथा अगर (is_digital_input(sd)) अणु
		hdmi_ग_लिखो(sd, 0x00, state->selected_input & 0x03);

		adv76xx_ग_लिखो_reg_seq(sd, info->recommended_settings[1]);

		अगर (adv76xx_has_afe(state)) अणु
			afe_ग_लिखो(sd, 0x00, 0xff); /* घातer करोwn ADC */
			afe_ग_लिखो(sd, 0x01, 0xfe); /* घातer करोwn Analog Front End */
			afe_ग_लिखो(sd, 0xc8, 0x40); /* phase control */
		पूर्ण

		cp_ग_लिखो(sd, 0x3e, 0x00); /* CP core pre-gain control */
		cp_ग_लिखो(sd, 0xc3, 0x39); /* CP coast control. Graphics mode */
		cp_ग_लिखो(sd, 0x40, 0x80); /* CP core pre-gain control. Graphics mode */
	पूर्ण अन्यथा अणु
		v4l2_dbg(2, debug, sd, "%s: Unknown port %d selected\n",
				__func__, state->selected_input);
	पूर्ण
पूर्ण

अटल पूर्णांक adv76xx_s_routing(काष्ठा v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	v4l2_dbg(2, debug, sd, "%s: input %d, selected input %d",
			__func__, input, state->selected_input);

	अगर (input == state->selected_input)
		वापस 0;

	अगर (input > state->info->max_port)
		वापस -EINVAL;

	state->selected_input = input;

	disable_input(sd);
	select_input(sd);
	enable_input(sd);

	v4l2_subdev_notअगरy_event(sd, &adv76xx_ev_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	अगर (code->index >= state->info->nक्रमmats)
		वापस -EINVAL;

	code->code = state->info->क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल व्योम adv76xx_fill_क्रमmat(काष्ठा adv76xx_state *state,
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
 * adv76xx_bus_order value in row).
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
अटल अचिन्हित पूर्णांक adv76xx_op_ch_sel(काष्ठा adv76xx_state *state)
अणु
#घोषणा _SEL(a,b,c,d,e,f)	अणु \
	ADV76XX_OP_CH_SEL_##a, ADV76XX_OP_CH_SEL_##b, ADV76XX_OP_CH_SEL_##c, \
	ADV76XX_OP_CH_SEL_##d, ADV76XX_OP_CH_SEL_##e, ADV76XX_OP_CH_SEL_##f पूर्ण
#घोषणा _BUS(x)			[ADV7604_BUS_ORDER_##x]

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

अटल व्योम adv76xx_setup_क्रमmat(काष्ठा adv76xx_state *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;

	io_ग_लिखो_clr_set(sd, 0x02, 0x02,
			state->क्रमmat->rgb_out ? ADV76XX_RGB_OUT : 0);
	io_ग_लिखो(sd, 0x03, state->क्रमmat->op_क्रमmat_sel |
		 state->pdata.op_क्रमmat_mode_sel);
	io_ग_लिखो_clr_set(sd, 0x04, 0xe0, adv76xx_op_ch_sel(state));
	io_ग_लिखो_clr_set(sd, 0x05, 0x01,
			state->क्रमmat->swap_cb_cr ? ADV76XX_OP_SWAP_CB_CR : 0);
	set_rgb_quantization_range(sd);
पूर्ण

अटल पूर्णांक adv76xx_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	अगर (क्रमmat->pad != state->source_pad)
		वापस -EINVAL;

	adv76xx_fill_क्रमmat(state, &क्रमmat->क्रमmat);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		क्रमmat->क्रमmat.code = fmt->code;
	पूर्ण अन्यथा अणु
		क्रमmat->क्रमmat.code = state->क्रमmat->code;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;
	/* Only CROP, CROP_DEFAULT and CROP_BOUNDS are supported */
	अगर (sel->target > V4L2_SEL_TGT_CROP_BOUNDS)
		वापस -EINVAL;

	sel->r.left	= 0;
	sel->r.top	= 0;
	sel->r.width	= state->timings.bt.width;
	sel->r.height	= state->timings.bt.height;

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_क्रमmat_info *info;

	अगर (क्रमmat->pad != state->source_pad)
		वापस -EINVAL;

	info = adv76xx_क्रमmat_info(state, क्रमmat->क्रमmat.code);
	अगर (!info)
		info = adv76xx_क्रमmat_info(state, MEDIA_BUS_FMT_YUYV8_2X8);

	adv76xx_fill_क्रमmat(state, &क्रमmat->क्रमmat);
	क्रमmat->क्रमmat.code = info->code;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		fmt->code = क्रमmat->क्रमmat.code;
	पूर्ण अन्यथा अणु
		state->क्रमmat = info;
		adv76xx_setup_क्रमmat(state);
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7604_CEC)
अटल व्योम adv76xx_cec_tx_raw_status(काष्ठा v4l2_subdev *sd, u8 tx_raw_status)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

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

अटल व्योम adv76xx_cec_isr(काष्ठा v4l2_subdev *sd, bool *handled)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	u8 cec_irq;

	/* cec controller */
	cec_irq = io_पढ़ो(sd, info->cec_irq_status) & 0x0f;
	अगर (!cec_irq)
		वापस;

	v4l2_dbg(1, debug, sd, "%s: cec: irq 0x%x\n", __func__, cec_irq);
	adv76xx_cec_tx_raw_status(sd, cec_irq);
	अगर (cec_irq & 0x08) अणु
		काष्ठा cec_msg msg;

		msg.len = cec_पढ़ो(sd, 0x25) & 0x1f;
		अगर (msg.len > 16)
			msg.len = 16;

		अगर (msg.len) अणु
			u8 i;

			क्रम (i = 0; i < msg.len; i++)
				msg.msg[i] = cec_पढ़ो(sd, i + 0x15);
			cec_ग_लिखो(sd, info->cec_rx_enable,
				  info->cec_rx_enable_mask); /* re-enable rx */
			cec_received_msg(state->cec_adap, &msg);
		पूर्ण
	पूर्ण

	अगर (info->cec_irq_swap) अणु
		/*
		 * Note: the bit order is swapped between 0x4d and 0x4e
		 * on adv7604
		 */
		cec_irq = ((cec_irq & 0x08) >> 3) | ((cec_irq & 0x04) >> 1) |
			  ((cec_irq & 0x02) << 1) | ((cec_irq & 0x01) << 3);
	पूर्ण
	io_ग_लिखो(sd, info->cec_irq_status + 1, cec_irq);

	अगर (handled)
		*handled = true;
पूर्ण

अटल पूर्णांक adv76xx_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा adv76xx_state *state = cec_get_drvdata(adap);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
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
		io_ग_लिखो_clr_set(sd, info->cec_irq_status + 3, 0x0f, 0x0f);
		cec_ग_लिखो(sd, info->cec_rx_enable, info->cec_rx_enable_mask);
	पूर्ण अन्यथा अगर (state->cec_enabled_adap && !enable) अणु
		/* disable cec पूर्णांकerrupts */
		io_ग_लिखो_clr_set(sd, info->cec_irq_status + 3, 0x0f, 0x00);
		/* disable address mask 1-3 */
		cec_ग_लिखो_clr_set(sd, 0x27, 0x70, 0x00);
		/* घातer करोwn cec section */
		cec_ग_लिखो_clr_set(sd, 0x2a, 0x01, 0x00);
		state->cec_valid_addrs = 0;
	पूर्ण
	state->cec_enabled_adap = enable;
	adv76xx_s_detect_tx_5v_ctrl(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा adv76xx_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;
	अचिन्हित पूर्णांक i, मुक्त_idx = ADV76XX_MAX_ADDRS;

	अगर (!state->cec_enabled_adap)
		वापस addr == CEC_LOG_ADDR_INVALID ? 0 : -EIO;

	अगर (addr == CEC_LOG_ADDR_INVALID) अणु
		cec_ग_लिखो_clr_set(sd, 0x27, 0x70, 0);
		state->cec_valid_addrs = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ADV76XX_MAX_ADDRS; i++) अणु
		bool is_valid = state->cec_valid_addrs & (1 << i);

		अगर (मुक्त_idx == ADV76XX_MAX_ADDRS && !is_valid)
			मुक्त_idx = i;
		अगर (is_valid && state->cec_addr[i] == addr)
			वापस 0;
	पूर्ण
	अगर (i == ADV76XX_MAX_ADDRS) अणु
		i = मुक्त_idx;
		अगर (i == ADV76XX_MAX_ADDRS)
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

अटल पूर्णांक adv76xx_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				     u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा adv76xx_state *state = cec_get_drvdata(adap);
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

अटल स्थिर काष्ठा cec_adap_ops adv76xx_cec_adap_ops = अणु
	.adap_enable = adv76xx_cec_adap_enable,
	.adap_log_addr = adv76xx_cec_adap_log_addr,
	.adap_transmit = adv76xx_cec_adap_transmit,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक adv76xx_isr(काष्ठा v4l2_subdev *sd, u32 status, bool *handled)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	स्थिर u8 irq_reg_0x43 = io_पढ़ो(sd, 0x43);
	स्थिर u8 irq_reg_0x6b = io_पढ़ो(sd, 0x6b);
	स्थिर u8 irq_reg_0x70 = io_पढ़ो(sd, 0x70);
	u8 fmt_change_digital;
	u8 fmt_change;
	u8 tx_5v;

	अगर (irq_reg_0x43)
		io_ग_लिखो(sd, 0x44, irq_reg_0x43);
	अगर (irq_reg_0x70)
		io_ग_लिखो(sd, 0x71, irq_reg_0x70);
	अगर (irq_reg_0x6b)
		io_ग_लिखो(sd, 0x6c, irq_reg_0x6b);

	v4l2_dbg(2, debug, sd, "%s: ", __func__);

	/* क्रमmat change */
	fmt_change = irq_reg_0x43 & 0x98;
	fmt_change_digital = is_digital_input(sd)
			   ? irq_reg_0x6b & info->fmt_change_digital_mask
			   : 0;

	अगर (fmt_change || fmt_change_digital) अणु
		v4l2_dbg(1, debug, sd,
			"%s: fmt_change = 0x%x, fmt_change_digital = 0x%x\n",
			__func__, fmt_change, fmt_change_digital);

		v4l2_subdev_notअगरy_event(sd, &adv76xx_ev_fmt);

		अगर (handled)
			*handled = true;
	पूर्ण
	/* HDMI/DVI mode */
	अगर (irq_reg_0x6b & 0x01) अणु
		v4l2_dbg(1, debug, sd, "%s: irq %s mode\n", __func__,
			(io_पढ़ो(sd, 0x6a) & 0x01) ? "HDMI" : "DVI");
		set_rgb_quantization_range(sd);
		अगर (handled)
			*handled = true;
	पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7604_CEC)
	/* cec */
	adv76xx_cec_isr(sd, handled);
#पूर्ण_अगर

	/* tx 5v detect */
	tx_5v = irq_reg_0x70 & info->cable_det_mask;
	अगर (tx_5v) अणु
		v4l2_dbg(1, debug, sd, "%s: tx_5v: 0x%x\n", __func__, tx_5v);
		adv76xx_s_detect_tx_5v_ctrl(sd);
		अगर (handled)
			*handled = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t adv76xx_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा adv76xx_state *state = dev_id;
	bool handled = false;

	adv76xx_isr(&state->sd, 0, &handled);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक adv76xx_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	u8 *data = शून्य;

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	चयन (edid->pad) अणु
	हाल ADV76XX_PAD_HDMI_PORT_A:
	हाल ADV7604_PAD_HDMI_PORT_B:
	हाल ADV7604_PAD_HDMI_PORT_C:
	हाल ADV7604_PAD_HDMI_PORT_D:
		अगर (state->edid.present & (1 << edid->pad))
			data = state->edid.edid;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = data ? state->edid.blocks : 0;
		वापस 0;
	पूर्ण

	अगर (!data)
		वापस -ENODATA;

	अगर (edid->start_block >= state->edid.blocks)
		वापस -EINVAL;

	अगर (edid->start_block + edid->blocks > state->edid.blocks)
		edid->blocks = state->edid.blocks - edid->start_block;

	स_नकल(edid->edid, data + edid->start_block * 128, edid->blocks * 128);

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_set_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	अचिन्हित पूर्णांक spa_loc;
	u16 pa, parent_pa;
	पूर्णांक err;
	पूर्णांक i;

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->pad > ADV7604_PAD_HDMI_PORT_D)
		वापस -EINVAL;
	अगर (edid->start_block != 0)
		वापस -EINVAL;
	अगर (edid->blocks == 0) अणु
		/* Disable hotplug and I2C access to EDID RAM from DDC port */
		state->edid.present &= ~(1 << edid->pad);
		adv76xx_set_hpd(state, state->edid.present);
		rep_ग_लिखो_clr_set(sd, info->edid_enable_reg, 0x0f, state->edid.present);

		/* Fall back to a 16:9 aspect ratio */
		state->aspect_ratio.numerator = 16;
		state->aspect_ratio.denominator = 9;

		अगर (!state->edid.present) अणु
			state->edid.blocks = 0;
			cec_phys_addr_invalidate(state->cec_adap);
		पूर्ण

		v4l2_dbg(2, debug, sd, "%s: clear EDID pad %d, edid.present = 0x%x\n",
				__func__, edid->pad, state->edid.present);
		वापस 0;
	पूर्ण
	अगर (edid->blocks > ADV76XX_MAX_EDID_BLOCKS) अणु
		edid->blocks = ADV76XX_MAX_EDID_BLOCKS;
		वापस -E2BIG;
	पूर्ण

	pa = v4l2_get_edid_phys_addr(edid->edid, edid->blocks * 128, &spa_loc);
	err = v4l2_phys_addr_validate(pa, &parent_pa, शून्य);
	अगर (err)
		वापस err;

	अगर (!spa_loc) अणु
		/*
		 * There is no SPA, so just set spa_loc to 128 and pa to whatever
		 * data is there.
		 */
		spa_loc = 128;
		pa = (edid->edid[spa_loc] << 8) | edid->edid[spa_loc + 1];
	पूर्ण

	v4l2_dbg(2, debug, sd, "%s: write EDID pad %d, edid.present = 0x%x\n",
			__func__, edid->pad, state->edid.present);

	/* Disable hotplug and I2C access to EDID RAM from DDC port */
	cancel_delayed_work_sync(&state->delayed_work_enable_hotplug);
	adv76xx_set_hpd(state, 0);
	rep_ग_लिखो_clr_set(sd, info->edid_enable_reg, 0x0f, 0x00);

	चयन (edid->pad) अणु
	हाल ADV76XX_PAD_HDMI_PORT_A:
		state->spa_port_a[0] = pa >> 8;
		state->spa_port_a[1] = pa & 0xff;
		अवरोध;
	हाल ADV7604_PAD_HDMI_PORT_B:
		rep_ग_लिखो(sd, info->edid_spa_port_b_reg, pa >> 8);
		rep_ग_लिखो(sd, info->edid_spa_port_b_reg + 1, pa & 0xff);
		अवरोध;
	हाल ADV7604_PAD_HDMI_PORT_C:
		rep_ग_लिखो(sd, info->edid_spa_port_b_reg + 2, pa >> 8);
		rep_ग_लिखो(sd, info->edid_spa_port_b_reg + 3, pa & 0xff);
		अवरोध;
	हाल ADV7604_PAD_HDMI_PORT_D:
		rep_ग_लिखो(sd, info->edid_spa_port_b_reg + 4, pa >> 8);
		rep_ग_लिखो(sd, info->edid_spa_port_b_reg + 5, pa & 0xff);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (info->edid_spa_loc_reg) अणु
		u8 mask = info->edid_spa_loc_msb_mask;

		rep_ग_लिखो(sd, info->edid_spa_loc_reg, spa_loc & 0xff);
		rep_ग_लिखो_clr_set(sd, info->edid_spa_loc_reg + 1,
				  mask, (spa_loc & 0x100) ? mask : 0);
	पूर्ण

	edid->edid[spa_loc] = state->spa_port_a[0];
	edid->edid[spa_loc + 1] = state->spa_port_a[1];

	स_नकल(state->edid.edid, edid->edid, 128 * edid->blocks);
	state->edid.blocks = edid->blocks;
	state->aspect_ratio = v4l2_calc_aspect_ratio(edid->edid[0x15],
			edid->edid[0x16]);
	state->edid.present |= 1 << edid->pad;

	rep_ग_लिखो_clr_set(sd, info->edid_segment_reg,
			  info->edid_segment_mask, 0);
	err = edid_ग_लिखो_block(sd, 128 * min(edid->blocks, 2U), state->edid.edid);
	अगर (err < 0) अणु
		v4l2_err(sd, "error %d writing edid pad %d\n", err, edid->pad);
		वापस err;
	पूर्ण
	अगर (edid->blocks > 2) अणु
		rep_ग_लिखो_clr_set(sd, info->edid_segment_reg,
				  info->edid_segment_mask,
				  info->edid_segment_mask);
		err = edid_ग_लिखो_block(sd, 128 * (edid->blocks - 2),
				       state->edid.edid + 256);
		अगर (err < 0) अणु
			v4l2_err(sd, "error %d writing edid pad %d\n",
				 err, edid->pad);
			वापस err;
		पूर्ण
	पूर्ण

	/* adv76xx calculates the checksums and enables I2C access to पूर्णांकernal
	   EDID RAM from DDC port. */
	rep_ग_लिखो_clr_set(sd, info->edid_enable_reg, 0x0f, state->edid.present);

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (rep_पढ़ो(sd, info->edid_status_reg) & state->edid.present)
			अवरोध;
		mdelay(1);
	पूर्ण
	अगर (i == 1000) अणु
		v4l2_err(sd, "error enabling edid (0x%x)\n", state->edid.present);
		वापस -EIO;
	पूर्ण
	cec_s_phys_addr(state->cec_adap, parent_pa, false);

	/* enable hotplug after 100 ms */
	schedule_delayed_work(&state->delayed_work_enable_hotplug, HZ / 10);
	वापस 0;
पूर्ण

/*********** avi info frame CEA-861-E **************/

अटल स्थिर काष्ठा adv76xx_cfg_पढ़ो_infoframe adv76xx_cri[] = अणु
	अणु "AVI", 0x01, 0xe0, 0x00 पूर्ण,
	अणु "Audio", 0x02, 0xe3, 0x1c पूर्ण,
	अणु "SDP", 0x04, 0xe6, 0x2a पूर्ण,
	अणु "Vendor", 0x10, 0xec, 0x54 पूर्ण
पूर्ण;

अटल पूर्णांक adv76xx_पढ़ो_infoframe(काष्ठा v4l2_subdev *sd, पूर्णांक index,
				  जोड़ hdmi_infoframe *frame)
अणु
	uपूर्णांक8_t buffer[32];
	u8 len;
	पूर्णांक i;

	अगर (!(io_पढ़ो(sd, 0x60) & adv76xx_cri[index].present_mask)) अणु
		v4l2_info(sd, "%s infoframe not received\n",
			  adv76xx_cri[index].desc);
		वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		buffer[i] = infoframe_पढ़ो(sd,
					   adv76xx_cri[index].head_addr + i);

	len = buffer[2] + 1;

	अगर (len + 3 > माप(buffer)) अणु
		v4l2_err(sd, "%s: invalid %s infoframe length %d\n", __func__,
			 adv76xx_cri[index].desc, len);
		वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		buffer[i + 3] = infoframe_पढ़ो(sd,
				       adv76xx_cri[index].payload_addr + i);

	अगर (hdmi_infoframe_unpack(frame, buffer, माप(buffer)) < 0) अणु
		v4l2_err(sd, "%s: unpack of %s infoframe failed\n", __func__,
			 adv76xx_cri[index].desc);
		वापस -ENOENT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adv76xx_log_infoframes(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक i;

	अगर (!is_hdmi(sd)) अणु
		v4l2_info(sd, "receive DVI-D signal, no infoframes\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(adv76xx_cri); i++) अणु
		जोड़ hdmi_infoframe frame;
		काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

		अगर (adv76xx_पढ़ो_infoframe(sd, i, &frame))
			वापस;
		hdmi_infoframe_log(KERN_INFO, &client->dev, &frame);
	पूर्ण
पूर्ण

अटल पूर्णांक adv76xx_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	काष्ठा v4l2_dv_timings timings;
	काष्ठा stdi_पढ़ोback stdi;
	u8 reg_io_0x02 = io_पढ़ो(sd, 0x02);
	u8 edid_enabled;
	u8 cable_det;

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
	अटल स्थिर अक्षर * स्थिर hdmi_color_space_txt[16] = अणु
		"RGB limited range (16-235)", "RGB full range (0-255)",
		"YCbCr Bt.601 (16-235)", "YCbCr Bt.709 (16-235)",
		"xvYCC Bt.601", "xvYCC Bt.709",
		"YCbCr Bt.601 (0-255)", "YCbCr Bt.709 (0-255)",
		"sYCC", "opYCC 601", "opRGB", "invalid", "invalid",
		"invalid", "invalid", "invalid"
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
	edid_enabled = rep_पढ़ो(sd, info->edid_status_reg);
	v4l2_info(sd, "EDID enabled port A: %s, B: %s, C: %s, D: %s\n",
			((edid_enabled & 0x01) ? "Yes" : "No"),
			((edid_enabled & 0x02) ? "Yes" : "No"),
			((edid_enabled & 0x04) ? "Yes" : "No"),
			((edid_enabled & 0x08) ? "Yes" : "No"));
	v4l2_info(sd, "CEC: %s\n", state->cec_enabled_adap ?
			"enabled" : "disabled");
	अगर (state->cec_enabled_adap) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ADV76XX_MAX_ADDRS; i++) अणु
			bool is_valid = state->cec_valid_addrs & (1 << i);

			अगर (is_valid)
				v4l2_info(sd, "CEC Logical Address: 0x%x\n",
					  state->cec_addr[i]);
		पूर्ण
	पूर्ण

	v4l2_info(sd, "-----Signal status-----\n");
	cable_det = info->पढ़ो_cable_det(sd);
	v4l2_info(sd, "Cable detected (+5V power) port A: %s, B: %s, C: %s, D: %s\n",
			((cable_det & 0x01) ? "Yes" : "No"),
			((cable_det & 0x02) ? "Yes" : "No"),
			((cable_det & 0x04) ? "Yes" : "No"),
			((cable_det & 0x08) ? "Yes" : "No"));
	v4l2_info(sd, "TMDS signal detected: %s\n",
			no_संकेत_पंचांगds(sd) ? "false" : "true");
	v4l2_info(sd, "TMDS signal locked: %s\n",
			no_lock_पंचांगds(sd) ? "false" : "true");
	v4l2_info(sd, "SSPD locked: %s\n", no_lock_sspd(sd) ? "false" : "true");
	v4l2_info(sd, "STDI locked: %s\n", no_lock_stdi(sd) ? "false" : "true");
	v4l2_info(sd, "CP locked: %s\n", no_lock_cp(sd) ? "false" : "true");
	v4l2_info(sd, "CP free run: %s\n",
			(in_मुक्त_run(sd)) ? "on" : "off");
	v4l2_info(sd, "Prim-mode = 0x%x, video std = 0x%x, v_freq = 0x%x\n",
			io_पढ़ो(sd, 0x01) & 0x0f, io_पढ़ो(sd, 0x00) & 0x3f,
			(io_पढ़ो(sd, 0x01) & 0x70) >> 4);

	v4l2_info(sd, "-----Video Timings-----\n");
	अगर (पढ़ो_stdi(sd, &stdi))
		v4l2_info(sd, "STDI: not locked\n");
	अन्यथा
		v4l2_info(sd, "STDI: lcf (frame height - 1) = %d, bl = %d, lcvs (vsync) = %d, %s, %chsync, %cvsync\n",
				stdi.lcf, stdi.bl, stdi.lcvs,
				stdi.पूर्णांकerlaced ? "interlaced" : "progressive",
				stdi.hs_pol, stdi.vs_pol);
	अगर (adv76xx_query_dv_timings(sd, &timings))
		v4l2_info(sd, "No video detected\n");
	अन्यथा
		v4l2_prपूर्णांक_dv_timings(sd->name, "Detected format: ",
				      &timings, true);
	v4l2_prपूर्णांक_dv_timings(sd->name, "Configured format: ",
			      &state->timings, true);

	अगर (no_संकेत(sd))
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
			csc_coeff_sel_rb[cp_पढ़ो(sd, info->cp_csc) >> 4]);

	अगर (!is_digital_input(sd))
		वापस 0;

	v4l2_info(sd, "-----%s status-----\n", is_hdmi(sd) ? "HDMI" : "DVI-D");
	v4l2_info(sd, "Digital video port selected: %c\n",
			(hdmi_पढ़ो(sd, 0x00) & 0x03) + 'A');
	v4l2_info(sd, "HDCP encrypted content: %s\n",
			(hdmi_पढ़ो(sd, 0x05) & 0x40) ? "true" : "false");
	v4l2_info(sd, "HDCP keys read: %s%s\n",
			(hdmi_पढ़ो(sd, 0x04) & 0x20) ? "yes" : "no",
			(hdmi_पढ़ो(sd, 0x04) & 0x10) ? "ERROR" : "");
	अगर (is_hdmi(sd)) अणु
		bool audio_pll_locked = hdmi_पढ़ो(sd, 0x04) & 0x01;
		bool audio_sample_packet_detect = hdmi_पढ़ो(sd, 0x18) & 0x01;
		bool audio_mute = io_पढ़ो(sd, 0x65) & 0x40;

		v4l2_info(sd, "Audio: pll %s, samples %s, %s\n",
				audio_pll_locked ? "locked" : "not locked",
				audio_sample_packet_detect ? "detected" : "not detected",
				audio_mute ? "muted" : "enabled");
		अगर (audio_pll_locked && audio_sample_packet_detect) अणु
			v4l2_info(sd, "Audio format: %s\n",
					(hdmi_पढ़ो(sd, 0x07) & 0x20) ? "multi-channel" : "stereo");
		पूर्ण
		v4l2_info(sd, "Audio CTS: %u\n", (hdmi_पढ़ो(sd, 0x5b) << 12) +
				(hdmi_पढ़ो(sd, 0x5c) << 8) +
				(hdmi_पढ़ो(sd, 0x5d) & 0xf0));
		v4l2_info(sd, "Audio N: %u\n", ((hdmi_पढ़ो(sd, 0x5d) & 0x0f) << 16) +
				(hdmi_पढ़ो(sd, 0x5e) << 8) +
				hdmi_पढ़ो(sd, 0x5f));
		v4l2_info(sd, "AV Mute: %s\n", (hdmi_पढ़ो(sd, 0x04) & 0x40) ? "on" : "off");

		v4l2_info(sd, "Deep color mode: %s\n", deep_color_mode_txt[(hdmi_पढ़ो(sd, 0x0b) & 0x60) >> 5]);
		v4l2_info(sd, "HDMI colorspace: %s\n", hdmi_color_space_txt[hdmi_पढ़ो(sd, 0x53) & 0xf]);

		adv76xx_log_infoframes(sd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv76xx_subscribe_event(काष्ठा v4l2_subdev *sd,
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

अटल पूर्णांक adv76xx_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक err;

	err = cec_रेजिस्टर_adapter(state->cec_adap, &client->dev);
	अगर (err)
		cec_delete_adapter(state->cec_adap);
	वापस err;
पूर्ण

अटल व्योम adv76xx_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);

	cec_unरेजिस्टर_adapter(state->cec_adap);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops adv76xx_ctrl_ops = अणु
	.s_ctrl = adv76xx_s_ctrl,
	.g_अस्थिर_ctrl = adv76xx_g_अस्थिर_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv76xx_core_ops = अणु
	.log_status = adv76xx_log_status,
	.पूर्णांकerrupt_service_routine = adv76xx_isr,
	.subscribe_event = adv76xx_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = adv76xx_g_रेजिस्टर,
	.s_रेजिस्टर = adv76xx_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv76xx_video_ops = अणु
	.s_routing = adv76xx_s_routing,
	.g_input_status = adv76xx_g_input_status,
	.s_dv_timings = adv76xx_s_dv_timings,
	.g_dv_timings = adv76xx_g_dv_timings,
	.query_dv_timings = adv76xx_query_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv76xx_pad_ops = अणु
	.क्रमागत_mbus_code = adv76xx_क्रमागत_mbus_code,
	.get_selection = adv76xx_get_selection,
	.get_fmt = adv76xx_get_क्रमmat,
	.set_fmt = adv76xx_set_क्रमmat,
	.get_edid = adv76xx_get_edid,
	.set_edid = adv76xx_set_edid,
	.dv_timings_cap = adv76xx_dv_timings_cap,
	.क्रमागत_dv_timings = adv76xx_क्रमागत_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adv76xx_ops = अणु
	.core = &adv76xx_core_ops,
	.video = &adv76xx_video_ops,
	.pad = &adv76xx_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops adv76xx_पूर्णांक_ops = अणु
	.रेजिस्टरed = adv76xx_रेजिस्टरed,
	.unरेजिस्टरed = adv76xx_unरेजिस्टरed,
पूर्ण;

/* -------------------------- custom ctrls ---------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_config adv7604_ctrl_analog_sampling_phase = अणु
	.ops = &adv76xx_ctrl_ops,
	.id = V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE,
	.name = "Analog Sampling Phase",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 0x1f,
	.step = 1,
	.def = 0,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config adv76xx_ctrl_मुक्त_run_color_manual = अणु
	.ops = &adv76xx_ctrl_ops,
	.id = V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL,
	.name = "Free Running Color, Manual",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = false,
	.max = true,
	.step = 1,
	.def = false,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config adv76xx_ctrl_मुक्त_run_color = अणु
	.ops = &adv76xx_ctrl_ops,
	.id = V4L2_CID_ADV_RX_FREE_RUN_COLOR,
	.name = "Free Running Color",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0x0,
	.max = 0xffffff,
	.step = 0x1,
	.def = 0x0,
पूर्ण;

/* ----------------------------------------------------------------------- */

काष्ठा adv76xx_रेजिस्टर_map अणु
	स्थिर अक्षर *name;
	u8 शेष_addr;
पूर्ण;

अटल स्थिर काष्ठा adv76xx_रेजिस्टर_map adv76xx_शेष_addresses[] = अणु
	[ADV76XX_PAGE_IO] = अणु "main", 0x4c पूर्ण,
	[ADV7604_PAGE_AVLINK] = अणु "avlink", 0x42 पूर्ण,
	[ADV76XX_PAGE_CEC] = अणु "cec", 0x40 पूर्ण,
	[ADV76XX_PAGE_INFOFRAME] = अणु "infoframe", 0x3e पूर्ण,
	[ADV7604_PAGE_ESDP] = अणु "esdp", 0x38 पूर्ण,
	[ADV7604_PAGE_DPP] = अणु "dpp", 0x3c पूर्ण,
	[ADV76XX_PAGE_AFE] = अणु "afe", 0x26 पूर्ण,
	[ADV76XX_PAGE_REP] = अणु "rep", 0x32 पूर्ण,
	[ADV76XX_PAGE_EDID] = अणु "edid", 0x36 पूर्ण,
	[ADV76XX_PAGE_HDMI] = अणु "hdmi", 0x34 पूर्ण,
	[ADV76XX_PAGE_TEST] = अणु "test", 0x30 पूर्ण,
	[ADV76XX_PAGE_CP] = अणु "cp", 0x22 पूर्ण,
	[ADV7604_PAGE_VDP] = अणु "vdp", 0x24 पूर्ण,
पूर्ण;

अटल पूर्णांक adv76xx_core_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv76xx_state *state = to_state(sd);
	स्थिर काष्ठा adv76xx_chip_info *info = state->info;
	काष्ठा adv76xx_platक्रमm_data *pdata = &state->pdata;

	hdmi_ग_लिखो(sd, 0x48,
		(pdata->disable_pwrdnb ? 0x80 : 0) |
		(pdata->disable_cable_det_rst ? 0x40 : 0));

	disable_input(sd);

	अगर (pdata->शेष_input >= 0 &&
	    pdata->शेष_input < state->source_pad) अणु
		state->selected_input = pdata->शेष_input;
		select_input(sd);
		enable_input(sd);
	पूर्ण

	/* घातer */
	io_ग_लिखो(sd, 0x0c, 0x42);   /* Power up part and घातer करोwn VDP */
	io_ग_लिखो(sd, 0x0b, 0x44);   /* Power करोwn ESDP block */
	cp_ग_लिखो(sd, 0xcf, 0x01);   /* Power करोwn macrovision */

	/* HPD */
	अगर (info->type != ADV7604) अणु
		/* Set manual HPD values to 0 */
		io_ग_लिखो_clr_set(sd, 0x20, 0xc0, 0);
		/*
		 * Set HPA_DELAY to 200 ms and set स्वतःmatic HPD control
		 * to: पूर्णांकernal EDID is active AND a cable is detected
		 * AND the manual HPD control is set to 1.
		 */
		hdmi_ग_लिखो_clr_set(sd, 0x6c, 0xf6, 0x26);
	पूर्ण

	/* video क्रमmat */
	io_ग_लिखो_clr_set(sd, 0x02, 0x0f, pdata->alt_gamma << 3);
	io_ग_लिखो_clr_set(sd, 0x05, 0x0e, pdata->blank_data << 3 |
			pdata->insert_av_codes << 2 |
			pdata->replicate_av_codes << 1);
	adv76xx_setup_क्रमmat(state);

	cp_ग_लिखो(sd, 0x69, 0x30);   /* Enable CP CSC */

	/* VS, HS polarities */
	io_ग_लिखो(sd, 0x06, 0xa0 | pdata->inv_vs_pol << 2 |
		 pdata->inv_hs_pol << 1 | pdata->inv_llc_pol);

	/* Adjust drive strength */
	io_ग_लिखो(sd, 0x14, 0x40 | pdata->dr_str_data << 4 |
				pdata->dr_str_clk << 2 |
				pdata->dr_str_sync);

	cp_ग_लिखो(sd, 0xba, (pdata->hdmi_मुक्त_run_mode << 1) | 0x01); /* HDMI मुक्त run */
	cp_ग_लिखो(sd, 0xf3, 0xdc); /* Low threshold to enter/निकास मुक्त run mode */
	cp_ग_लिखो(sd, 0xf9, 0x23); /*  STDI ch. 1 - LCVS change threshold -
				      ADI recommended setting [REF_01, c. 2.3.3] */
	cp_ग_लिखो(sd, 0x45, 0x23); /*  STDI ch. 2 - LCVS change threshold -
				      ADI recommended setting [REF_01, c. 2.3.3] */
	cp_ग_लिखो(sd, 0xc9, 0x2d); /* use prim_mode and vid_std as मुक्त run resolution
				     क्रम digital क्रमmats */

	/* HDMI audio */
	hdmi_ग_लिखो_clr_set(sd, 0x15, 0x03, 0x03); /* Mute on FIFO over-/underflow [REF_01, c. 1.2.18] */
	hdmi_ग_लिखो_clr_set(sd, 0x1a, 0x0e, 0x08); /* Wait 1 s beक्रमe unmute */
	hdmi_ग_लिखो_clr_set(sd, 0x68, 0x06, 0x06); /* FIFO reset on over-/underflow [REF_01, c. 1.2.19] */

	/* TODO from platक्रमm data */
	afe_ग_लिखो(sd, 0xb5, 0x01);  /* Setting MCLK to 256Fs */

	अगर (adv76xx_has_afe(state)) अणु
		afe_ग_लिखो(sd, 0x02, pdata->ain_sel); /* Select analog input muxing mode */
		io_ग_लिखो_clr_set(sd, 0x30, 1 << 4, pdata->output_bus_lsb_to_msb << 4);
	पूर्ण

	/* पूर्णांकerrupts */
	io_ग_लिखो(sd, 0x40, 0xc0 | pdata->पूर्णांक1_config); /* Configure INT1 */
	io_ग_लिखो(sd, 0x46, 0x98); /* Enable SSPD, STDI and CP unlocked पूर्णांकerrupts */
	io_ग_लिखो(sd, 0x6e, info->fmt_change_digital_mask); /* Enable V_LOCKED and DE_REGEN_LCK पूर्णांकerrupts */
	io_ग_लिखो(sd, 0x73, info->cable_det_mask); /* Enable cable detection (+5v) पूर्णांकerrupts */
	info->setup_irqs(sd);

	वापस v4l2_ctrl_handler_setup(sd->ctrl_handler);
पूर्ण

अटल व्योम adv7604_setup_irqs(काष्ठा v4l2_subdev *sd)
अणु
	io_ग_लिखो(sd, 0x41, 0xd7); /* STDI irq क्रम any change, disable INT2 */
पूर्ण

अटल व्योम adv7611_setup_irqs(काष्ठा v4l2_subdev *sd)
अणु
	io_ग_लिखो(sd, 0x41, 0xd0); /* STDI irq क्रम any change, disable INT2 */
पूर्ण

अटल व्योम adv7612_setup_irqs(काष्ठा v4l2_subdev *sd)
अणु
	io_ग_लिखो(sd, 0x41, 0xd0); /* disable INT2 */
पूर्ण

अटल व्योम adv76xx_unरेजिस्टर_clients(काष्ठा adv76xx_state *state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(state->i2c_clients); ++i)
		i2c_unरेजिस्टर_device(state->i2c_clients[i]);
पूर्ण

अटल काष्ठा i2c_client *adv76xx_dummy_client(काष्ठा v4l2_subdev *sd,
					       अचिन्हित पूर्णांक page)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा adv76xx_state *state = to_state(sd);
	काष्ठा adv76xx_platक्रमm_data *pdata = &state->pdata;
	अचिन्हित पूर्णांक io_reg = 0xf2 + page;
	काष्ठा i2c_client *new_client;

	अगर (pdata && pdata->i2c_addresses[page])
		new_client = i2c_new_dummy_device(client->adapter,
					   pdata->i2c_addresses[page]);
	अन्यथा
		new_client = i2c_new_ancillary_device(client,
				adv76xx_शेष_addresses[page].name,
				adv76xx_शेष_addresses[page].शेष_addr);

	अगर (!IS_ERR(new_client))
		io_ग_लिखो(sd, io_reg, new_client->addr << 1);

	वापस new_client;
पूर्ण

अटल स्थिर काष्ठा adv76xx_reg_seq adv7604_recommended_settings_afe[] = अणु
	/* reset ADI recommended settings क्रम HDMI: */
	/* "ADV7604 Register Settings Recommendations (rev. 2.5, June 2010)" p. 4. */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x0d), 0x04 पूर्ण, /* HDMI filter optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x0d), 0x04 पूर्ण, /* HDMI filter optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x3d), 0x00 पूर्ण, /* DDC bus active pull-up control */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x3e), 0x74 पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x4e), 0x3b पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x57), 0x74 पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x58), 0x63 पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x8d), 0x18 पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x8e), 0x34 पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x93), 0x88 पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x94), 0x2e पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x96), 0x00 पूर्ण, /* enable स्वतःmatic EQ changing */

	/* set ADI recommended settings क्रम digitizer */
	/* "ADV7604 Register Settings Recommendations (rev. 2.5, June 2010)" p. 17. */
	अणु ADV76XX_REG(ADV76XX_PAGE_AFE, 0x12), 0x7b पूर्ण, /* ADC noise shaping filter controls */
	अणु ADV76XX_REG(ADV76XX_PAGE_AFE, 0x0c), 0x1f पूर्ण, /* CP core gain controls */
	अणु ADV76XX_REG(ADV76XX_PAGE_CP, 0x3e), 0x04 पूर्ण, /* CP core pre-gain control */
	अणु ADV76XX_REG(ADV76XX_PAGE_CP, 0xc3), 0x39 पूर्ण, /* CP coast control. Graphics mode */
	अणु ADV76XX_REG(ADV76XX_PAGE_CP, 0x40), 0x5c पूर्ण, /* CP core pre-gain control. Graphics mode */

	अणु ADV76XX_REG_SEQ_TERM, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_reg_seq adv7604_recommended_settings_hdmi[] = अणु
	/* set ADI recommended settings क्रम HDMI: */
	/* "ADV7604 Register Settings Recommendations (rev. 2.5, June 2010)" p. 4. */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x0d), 0x84 पूर्ण, /* HDMI filter optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x3d), 0x10 पूर्ण, /* DDC bus active pull-up control */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x3e), 0x39 पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x4e), 0x3b पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x57), 0xb6 पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x58), 0x03 पूर्ण, /* TMDS PLL optimization */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x8d), 0x18 पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x8e), 0x34 पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x93), 0x8b पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x94), 0x2d पूर्ण, /* equaliser */
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x96), 0x01 पूर्ण, /* enable स्वतःmatic EQ changing */

	/* reset ADI recommended settings क्रम digitizer */
	/* "ADV7604 Register Settings Recommendations (rev. 2.5, June 2010)" p. 17. */
	अणु ADV76XX_REG(ADV76XX_PAGE_AFE, 0x12), 0xfb पूर्ण, /* ADC noise shaping filter controls */
	अणु ADV76XX_REG(ADV76XX_PAGE_AFE, 0x0c), 0x0d पूर्ण, /* CP core gain controls */

	अणु ADV76XX_REG_SEQ_TERM, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_reg_seq adv7611_recommended_settings_hdmi[] = अणु
	/* ADV7611 Register Settings Recommendations Rev 1.5, May 2014 */
	अणु ADV76XX_REG(ADV76XX_PAGE_CP, 0x6c), 0x00 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x9b), 0x03 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x6f), 0x08 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x85), 0x1f पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x87), 0x70 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x57), 0xda पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x58), 0x01 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x03), 0x98 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x4c), 0x44 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x8d), 0x04 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x8e), 0x1e पूर्ण,

	अणु ADV76XX_REG_SEQ_TERM, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_reg_seq adv7612_recommended_settings_hdmi[] = अणु
	अणु ADV76XX_REG(ADV76XX_PAGE_CP, 0x6c), 0x00 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x9b), 0x03 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x6f), 0x08 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x85), 0x1f पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x87), 0x70 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x57), 0xda पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x58), 0x01 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x03), 0x98 पूर्ण,
	अणु ADV76XX_REG(ADV76XX_PAGE_HDMI, 0x4c), 0x44 पूर्ण,
	अणु ADV76XX_REG_SEQ_TERM, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adv76xx_chip_info adv76xx_chip_info[] = अणु
	[ADV7604] = अणु
		.type = ADV7604,
		.has_afe = true,
		.max_port = ADV7604_PAD_VGA_COMP,
		.num_dv_ports = 4,
		.edid_enable_reg = 0x77,
		.edid_status_reg = 0x7d,
		.edid_segment_reg = 0x77,
		.edid_segment_mask = 0x10,
		.edid_spa_loc_reg = 0x76,
		.edid_spa_loc_msb_mask = 0x40,
		.edid_spa_port_b_reg = 0x70,
		.lcf_reg = 0xb3,
		.tdms_lock_mask = 0xe0,
		.cable_det_mask = 0x1e,
		.fmt_change_digital_mask = 0xc1,
		.cp_csc = 0xfc,
		.cec_irq_status = 0x4d,
		.cec_rx_enable = 0x26,
		.cec_rx_enable_mask = 0x01,
		.cec_irq_swap = true,
		.क्रमmats = adv7604_क्रमmats,
		.nक्रमmats = ARRAY_SIZE(adv7604_क्रमmats),
		.set_termination = adv7604_set_termination,
		.setup_irqs = adv7604_setup_irqs,
		.पढ़ो_hdmi_pixelघड़ी = adv7604_पढ़ो_hdmi_pixelघड़ी,
		.पढ़ो_cable_det = adv7604_पढ़ो_cable_det,
		.recommended_settings = अणु
		    [0] = adv7604_recommended_settings_afe,
		    [1] = adv7604_recommended_settings_hdmi,
		पूर्ण,
		.num_recommended_settings = अणु
		    [0] = ARRAY_SIZE(adv7604_recommended_settings_afe),
		    [1] = ARRAY_SIZE(adv7604_recommended_settings_hdmi),
		पूर्ण,
		.page_mask = BIT(ADV76XX_PAGE_IO) | BIT(ADV7604_PAGE_AVLINK) |
			BIT(ADV76XX_PAGE_CEC) | BIT(ADV76XX_PAGE_INFOFRAME) |
			BIT(ADV7604_PAGE_ESDP) | BIT(ADV7604_PAGE_DPP) |
			BIT(ADV76XX_PAGE_AFE) | BIT(ADV76XX_PAGE_REP) |
			BIT(ADV76XX_PAGE_EDID) | BIT(ADV76XX_PAGE_HDMI) |
			BIT(ADV76XX_PAGE_TEST) | BIT(ADV76XX_PAGE_CP) |
			BIT(ADV7604_PAGE_VDP),
		.linewidth_mask = 0xfff,
		.field0_height_mask = 0xfff,
		.field1_height_mask = 0xfff,
		.hfrontporch_mask = 0x3ff,
		.hsync_mask = 0x3ff,
		.hbackporch_mask = 0x3ff,
		.field0_vfrontporch_mask = 0x1fff,
		.field0_vsync_mask = 0x1fff,
		.field0_vbackporch_mask = 0x1fff,
		.field1_vfrontporch_mask = 0x1fff,
		.field1_vsync_mask = 0x1fff,
		.field1_vbackporch_mask = 0x1fff,
	पूर्ण,
	[ADV7611] = अणु
		.type = ADV7611,
		.has_afe = false,
		.max_port = ADV76XX_PAD_HDMI_PORT_A,
		.num_dv_ports = 1,
		.edid_enable_reg = 0x74,
		.edid_status_reg = 0x76,
		.edid_segment_reg = 0x7a,
		.edid_segment_mask = 0x01,
		.lcf_reg = 0xa3,
		.tdms_lock_mask = 0x43,
		.cable_det_mask = 0x01,
		.fmt_change_digital_mask = 0x03,
		.cp_csc = 0xf4,
		.cec_irq_status = 0x93,
		.cec_rx_enable = 0x2c,
		.cec_rx_enable_mask = 0x02,
		.क्रमmats = adv7611_क्रमmats,
		.nक्रमmats = ARRAY_SIZE(adv7611_क्रमmats),
		.set_termination = adv7611_set_termination,
		.setup_irqs = adv7611_setup_irqs,
		.पढ़ो_hdmi_pixelघड़ी = adv7611_पढ़ो_hdmi_pixelघड़ी,
		.पढ़ो_cable_det = adv7611_पढ़ो_cable_det,
		.recommended_settings = अणु
		    [1] = adv7611_recommended_settings_hdmi,
		पूर्ण,
		.num_recommended_settings = अणु
		    [1] = ARRAY_SIZE(adv7611_recommended_settings_hdmi),
		पूर्ण,
		.page_mask = BIT(ADV76XX_PAGE_IO) | BIT(ADV76XX_PAGE_CEC) |
			BIT(ADV76XX_PAGE_INFOFRAME) | BIT(ADV76XX_PAGE_AFE) |
			BIT(ADV76XX_PAGE_REP) |  BIT(ADV76XX_PAGE_EDID) |
			BIT(ADV76XX_PAGE_HDMI) | BIT(ADV76XX_PAGE_CP),
		.linewidth_mask = 0x1fff,
		.field0_height_mask = 0x1fff,
		.field1_height_mask = 0x1fff,
		.hfrontporch_mask = 0x1fff,
		.hsync_mask = 0x1fff,
		.hbackporch_mask = 0x1fff,
		.field0_vfrontporch_mask = 0x3fff,
		.field0_vsync_mask = 0x3fff,
		.field0_vbackporch_mask = 0x3fff,
		.field1_vfrontporch_mask = 0x3fff,
		.field1_vsync_mask = 0x3fff,
		.field1_vbackporch_mask = 0x3fff,
	पूर्ण,
	[ADV7612] = अणु
		.type = ADV7612,
		.has_afe = false,
		.max_port = ADV76XX_PAD_HDMI_PORT_A,	/* B not supported */
		.num_dv_ports = 1,			/* normally 2 */
		.edid_enable_reg = 0x74,
		.edid_status_reg = 0x76,
		.edid_segment_reg = 0x7a,
		.edid_segment_mask = 0x01,
		.edid_spa_loc_reg = 0x70,
		.edid_spa_loc_msb_mask = 0x01,
		.edid_spa_port_b_reg = 0x52,
		.lcf_reg = 0xa3,
		.tdms_lock_mask = 0x43,
		.cable_det_mask = 0x01,
		.fmt_change_digital_mask = 0x03,
		.cp_csc = 0xf4,
		.cec_irq_status = 0x93,
		.cec_rx_enable = 0x2c,
		.cec_rx_enable_mask = 0x02,
		.क्रमmats = adv7612_क्रमmats,
		.nक्रमmats = ARRAY_SIZE(adv7612_क्रमmats),
		.set_termination = adv7611_set_termination,
		.setup_irqs = adv7612_setup_irqs,
		.पढ़ो_hdmi_pixelघड़ी = adv7611_पढ़ो_hdmi_pixelघड़ी,
		.पढ़ो_cable_det = adv7612_पढ़ो_cable_det,
		.recommended_settings = अणु
		    [1] = adv7612_recommended_settings_hdmi,
		पूर्ण,
		.num_recommended_settings = अणु
		    [1] = ARRAY_SIZE(adv7612_recommended_settings_hdmi),
		पूर्ण,
		.page_mask = BIT(ADV76XX_PAGE_IO) | BIT(ADV76XX_PAGE_CEC) |
			BIT(ADV76XX_PAGE_INFOFRAME) | BIT(ADV76XX_PAGE_AFE) |
			BIT(ADV76XX_PAGE_REP) |  BIT(ADV76XX_PAGE_EDID) |
			BIT(ADV76XX_PAGE_HDMI) | BIT(ADV76XX_PAGE_CP),
		.linewidth_mask = 0x1fff,
		.field0_height_mask = 0x1fff,
		.field1_height_mask = 0x1fff,
		.hfrontporch_mask = 0x1fff,
		.hsync_mask = 0x1fff,
		.hbackporch_mask = 0x1fff,
		.field0_vfrontporch_mask = 0x3fff,
		.field0_vsync_mask = 0x3fff,
		.field0_vbackporch_mask = 0x3fff,
		.field1_vfrontporch_mask = 0x3fff,
		.field1_vsync_mask = 0x3fff,
		.field1_vbackporch_mask = 0x3fff,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id adv76xx_i2c_id[] = अणु
	अणु "adv7604", (kernel_uदीर्घ_t)&adv76xx_chip_info[ADV7604] पूर्ण,
	अणु "adv7611", (kernel_uदीर्घ_t)&adv76xx_chip_info[ADV7611] पूर्ण,
	अणु "adv7612", (kernel_uदीर्घ_t)&adv76xx_chip_info[ADV7612] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv76xx_i2c_id);

अटल स्थिर काष्ठा of_device_id adv76xx_of_id[] __maybe_unused = अणु
	अणु .compatible = "adi,adv7611", .data = &adv76xx_chip_info[ADV7611] पूर्ण,
	अणु .compatible = "adi,adv7612", .data = &adv76xx_chip_info[ADV7612] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adv76xx_of_id);

अटल पूर्णांक adv76xx_parse_dt(काष्ठा adv76xx_state *state)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *endpoपूर्णांक;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक flags;
	पूर्णांक ret;
	u32 v;

	np = state->i2c_clients[ADV76XX_PAGE_IO]->dev.of_node;

	/* Parse the endpoपूर्णांक. */
	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (!endpoपूर्णांक)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(endpoपूर्णांक), &bus_cfg);
	of_node_put(endpoपूर्णांक);
	अगर (ret)
		वापस ret;

	अगर (!of_property_पढ़ो_u32(np, "default-input", &v))
		state->pdata.शेष_input = v;
	अन्यथा
		state->pdata.शेष_input = -1;

	flags = bus_cfg.bus.parallel.flags;

	अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		state->pdata.inv_hs_pol = 1;

	अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		state->pdata.inv_vs_pol = 1;

	अगर (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		state->pdata.inv_llc_pol = 1;

	अगर (bus_cfg.bus_type == V4L2_MBUS_BT656)
		state->pdata.insert_av_codes = 1;

	/* Disable the पूर्णांकerrupt क्रम now as no DT-based board uses it. */
	state->pdata.पूर्णांक1_config = ADV76XX_INT1_CONFIG_ACTIVE_HIGH;

	/* Hardcode the reमुख्यing platक्रमm data fields. */
	state->pdata.disable_pwrdnb = 0;
	state->pdata.disable_cable_det_rst = 0;
	state->pdata.blank_data = 1;
	state->pdata.op_क्रमmat_mode_sel = ADV7604_OP_FORMAT_MODE0;
	state->pdata.bus_order = ADV7604_BUS_ORDER_RGB;
	state->pdata.dr_str_data = ADV76XX_DR_STR_MEDIUM_HIGH;
	state->pdata.dr_str_clk = ADV76XX_DR_STR_MEDIUM_HIGH;
	state->pdata.dr_str_sync = ADV76XX_DR_STR_MEDIUM_HIGH;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config adv76xx_regmap_cnf[] = अणु
	अणु
		.name			= "io",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "avlink",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "cec",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "infoframe",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "esdp",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "epp",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "afe",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "rep",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "edid",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,

	अणु
		.name			= "hdmi",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "test",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "cp",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
	अणु
		.name			= "vdp",
		.reg_bits		= 8,
		.val_bits		= 8,

		.max_रेजिस्टर		= 0xff,
		.cache_type		= REGCACHE_NONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक configure_regmap(काष्ठा adv76xx_state *state, पूर्णांक region)
अणु
	पूर्णांक err;

	अगर (!state->i2c_clients[region])
		वापस -ENODEV;

	state->regmap[region] =
		devm_regmap_init_i2c(state->i2c_clients[region],
				     &adv76xx_regmap_cnf[region]);

	अगर (IS_ERR(state->regmap[region])) अणु
		err = PTR_ERR(state->regmap[region]);
		v4l_err(state->i2c_clients[region],
			"Error initializing regmap %d with error %d\n",
			region, err);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक configure_regmaps(काष्ठा adv76xx_state *state)
अणु
	पूर्णांक i, err;

	क्रम (i = ADV7604_PAGE_AVLINK ; i < ADV76XX_PAGE_MAX; i++) अणु
		err = configure_regmap(state, i);
		अगर (err && (err != -ENODEV))
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adv76xx_reset(काष्ठा adv76xx_state *state)
अणु
	अगर (state->reset_gpio) अणु
		/* ADV76XX can be reset by a low reset pulse of minimum 5 ms. */
		gpiod_set_value_cansleep(state->reset_gpio, 0);
		usleep_range(5000, 10000);
		gpiod_set_value_cansleep(state->reset_gpio, 1);
		/* It is recommended to रुको 5 ms after the low pulse beक्रमe */
		/* an I2C ग_लिखो is perक्रमmed to the ADV76XX. */
		usleep_range(5000, 10000);
	पूर्ण
पूर्ण

अटल पूर्णांक adv76xx_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	अटल स्थिर काष्ठा v4l2_dv_timings cea640x480 =
		V4L2_DV_BT_CEA_640X480P59_94;
	काष्ठा adv76xx_state *state;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_ctrl *ctrl;
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक val, val2;
	पूर्णांक err;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;
	v4l_dbg(1, debug, client, "detecting adv76xx client on address 0x%x\n",
			client->addr << 1);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->i2c_clients[ADV76XX_PAGE_IO] = client;

	/* initialize variables */
	state->restart_stdi_once = true;
	state->selected_input = ~0;

	अगर (IS_ENABLED(CONFIG_OF) && client->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *oid;

		oid = of_match_node(adv76xx_of_id, client->dev.of_node);
		state->info = oid->data;

		err = adv76xx_parse_dt(state);
		अगर (err < 0) अणु
			v4l_err(client, "DT parsing error\n");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (client->dev.platक्रमm_data) अणु
		काष्ठा adv76xx_platक्रमm_data *pdata = client->dev.platक्रमm_data;

		state->info = (स्थिर काष्ठा adv76xx_chip_info *)id->driver_data;
		state->pdata = *pdata;
	पूर्ण अन्यथा अणु
		v4l_err(client, "No platform data!\n");
		वापस -ENODEV;
	पूर्ण

	/* Request GPIOs. */
	क्रम (i = 0; i < state->info->num_dv_ports; ++i) अणु
		state->hpd_gpio[i] =
			devm_gpiod_get_index_optional(&client->dev, "hpd", i,
						      GPIOD_OUT_LOW);
		अगर (IS_ERR(state->hpd_gpio[i]))
			वापस PTR_ERR(state->hpd_gpio[i]);

		अगर (state->hpd_gpio[i])
			v4l_info(client, "Handling HPD %u GPIO\n", i);
	पूर्ण
	state->reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
								GPIOD_OUT_HIGH);
	अगर (IS_ERR(state->reset_gpio))
		वापस PTR_ERR(state->reset_gpio);

	adv76xx_reset(state);

	state->timings = cea640x480;
	state->क्रमmat = adv76xx_क्रमmat_info(state, MEDIA_BUS_FMT_YUYV8_2X8);

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &adv76xx_ops);
	snम_लिखो(sd->name, माप(sd->name), "%s %d-%04x",
		id->name, i2c_adapter_id(client->adapter),
		client->addr);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	sd->पूर्णांकernal_ops = &adv76xx_पूर्णांक_ops;

	/* Configure IO Regmap region */
	err = configure_regmap(state, ADV76XX_PAGE_IO);

	अगर (err) अणु
		v4l2_err(sd, "Error configuring IO regmap region\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Verअगरy that the chip is present. On ADV7604 the RD_INFO रेजिस्टर only
	 * identअगरies the revision, जबतक on ADV7611 it identअगरies the model as
	 * well. Use the HDMI slave address on ADV7604 and RD_INFO on ADV7611.
	 */
	चयन (state->info->type) अणु
	हाल ADV7604:
		err = regmap_पढ़ो(state->regmap[ADV76XX_PAGE_IO], 0xfb, &val);
		अगर (err) अणु
			v4l2_err(sd, "Error %d reading IO Regmap\n", err);
			वापस -ENODEV;
		पूर्ण
		अगर (val != 0x68) अणु
			v4l2_err(sd, "not an adv7604 on address 0x%x\n",
					client->addr << 1);
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	हाल ADV7611:
	हाल ADV7612:
		err = regmap_पढ़ो(state->regmap[ADV76XX_PAGE_IO],
				0xea,
				&val);
		अगर (err) अणु
			v4l2_err(sd, "Error %d reading IO Regmap\n", err);
			वापस -ENODEV;
		पूर्ण
		val2 = val << 8;
		err = regmap_पढ़ो(state->regmap[ADV76XX_PAGE_IO],
			    0xeb,
			    &val);
		अगर (err) अणु
			v4l2_err(sd, "Error %d reading IO Regmap\n", err);
			वापस -ENODEV;
		पूर्ण
		val |= val2;
		अगर ((state->info->type == ADV7611 && val != 0x2051) ||
			(state->info->type == ADV7612 && val != 0x2041)) अणु
			v4l2_err(sd, "not an adv761x on address 0x%x\n",
					client->addr << 1);
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	पूर्ण

	/* control handlers */
	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, adv76xx_has_afe(state) ? 9 : 8);

	v4l2_ctrl_new_std(hdl, &adv76xx_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &adv76xx_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &adv76xx_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &adv76xx_ctrl_ops,
			V4L2_CID_HUE, 0, 128, 1, 0);
	ctrl = v4l2_ctrl_new_std_menu(hdl, &adv76xx_ctrl_ops,
			V4L2_CID_DV_RX_IT_CONTENT_TYPE, V4L2_DV_IT_CONTENT_TYPE_NO_ITC,
			0, V4L2_DV_IT_CONTENT_TYPE_NO_ITC);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	state->detect_tx_5v_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_RX_POWER_PRESENT, 0,
			(1 << state->info->num_dv_ports) - 1, 0, 0);
	state->rgb_quantization_range_ctrl =
		v4l2_ctrl_new_std_menu(hdl, &adv76xx_ctrl_ops,
			V4L2_CID_DV_RX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);

	/* custom controls */
	अगर (adv76xx_has_afe(state))
		state->analog_sampling_phase_ctrl =
			v4l2_ctrl_new_custom(hdl, &adv7604_ctrl_analog_sampling_phase, शून्य);
	state->मुक्त_run_color_manual_ctrl =
		v4l2_ctrl_new_custom(hdl, &adv76xx_ctrl_मुक्त_run_color_manual, शून्य);
	state->मुक्त_run_color_ctrl =
		v4l2_ctrl_new_custom(hdl, &adv76xx_ctrl_मुक्त_run_color, शून्य);

	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		err = hdl->error;
		जाओ err_hdl;
	पूर्ण
	अगर (adv76xx_s_detect_tx_5v_ctrl(sd)) अणु
		err = -ENODEV;
		जाओ err_hdl;
	पूर्ण

	क्रम (i = 1; i < ADV76XX_PAGE_MAX; ++i) अणु
		काष्ठा i2c_client *dummy_client;

		अगर (!(BIT(i) & state->info->page_mask))
			जारी;

		dummy_client = adv76xx_dummy_client(sd, i);
		अगर (IS_ERR(dummy_client)) अणु
			err = PTR_ERR(dummy_client);
			v4l2_err(sd, "failed to create i2c client %u\n", i);
			जाओ err_i2c;
		पूर्ण

		state->i2c_clients[i] = dummy_client;
	पूर्ण

	INIT_DELAYED_WORK(&state->delayed_work_enable_hotplug,
			adv76xx_delayed_work_enable_hotplug);

	state->source_pad = state->info->num_dv_ports
			  + (state->info->has_afe ? 2 : 0);
	क्रम (i = 0; i < state->source_pad; ++i)
		state->pads[i].flags = MEDIA_PAD_FL_SINK;
	state->pads[state->source_pad].flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_DV_DECODER;

	err = media_entity_pads_init(&sd->entity, state->source_pad + 1,
				state->pads);
	अगर (err)
		जाओ err_work_queues;

	/* Configure regmaps */
	err = configure_regmaps(state);
	अगर (err)
		जाओ err_entity;

	err = adv76xx_core_init(sd);
	अगर (err)
		जाओ err_entity;

	अगर (client->irq) अणु
		err = devm_request_thपढ़ोed_irq(&client->dev,
						client->irq,
						शून्य, adv76xx_irq_handler,
						IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
						client->name, state);
		अगर (err)
			जाओ err_entity;
	पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7604_CEC)
	state->cec_adap = cec_allocate_adapter(&adv76xx_cec_adap_ops,
		state, dev_name(&client->dev),
		CEC_CAP_DEFAULTS, ADV76XX_MAX_ADDRS);
	err = PTR_ERR_OR_ZERO(state->cec_adap);
	अगर (err)
		जाओ err_entity;
#पूर्ण_अगर

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
			client->addr << 1, client->adapter->name);

	err = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (err)
		जाओ err_entity;

	वापस 0;

err_entity:
	media_entity_cleanup(&sd->entity);
err_work_queues:
	cancel_delayed_work(&state->delayed_work_enable_hotplug);
err_i2c:
	adv76xx_unरेजिस्टर_clients(state);
err_hdl:
	v4l2_ctrl_handler_मुक्त(hdl);
	वापस err;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv76xx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा adv76xx_state *state = to_state(sd);

	/* disable पूर्णांकerrupts */
	io_ग_लिखो(sd, 0x40, 0);
	io_ग_लिखो(sd, 0x41, 0);
	io_ग_लिखो(sd, 0x46, 0);
	io_ग_लिखो(sd, 0x6e, 0);
	io_ग_लिखो(sd, 0x73, 0);

	cancel_delayed_work_sync(&state->delayed_work_enable_hotplug);
	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	adv76xx_unरेजिस्टर_clients(to_state(sd));
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल काष्ठा i2c_driver adv76xx_driver = अणु
	.driver = अणु
		.name = "adv7604",
		.of_match_table = of_match_ptr(adv76xx_of_id),
	पूर्ण,
	.probe = adv76xx_probe,
	.हटाओ = adv76xx_हटाओ,
	.id_table = adv76xx_i2c_id,
पूर्ण;

module_i2c_driver(adv76xx_driver);
