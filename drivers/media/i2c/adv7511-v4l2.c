<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices ADV7511 HDMI Transmitter Device Driver
 *
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

/*
 * This file is named adv7511-v4l2.c so it करोesn't conflict with the Analog
 * Device ADV7511 (config fragment CONFIG_DRM_I2C_ADV7511).
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/i2c/adv7511.h>
#समावेश <media/cec.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

MODULE_DESCRIPTION("Analog Devices ADV7511 HDMI Transmitter Device Driver");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL v2");

#घोषणा MASK_ADV7511_EDID_RDY_INT   0x04
#घोषणा MASK_ADV7511_MSEN_INT       0x40
#घोषणा MASK_ADV7511_HPD_INT        0x80

#घोषणा MASK_ADV7511_HPD_DETECT     0x40
#घोषणा MASK_ADV7511_MSEN_DETECT    0x20
#घोषणा MASK_ADV7511_EDID_RDY       0x10

#घोषणा EDID_MAX_RETRIES (8)
#घोषणा EDID_DELAY 250
#घोषणा EDID_MAX_SEGM 8

#घोषणा ADV7511_MAX_WIDTH 1920
#घोषणा ADV7511_MAX_HEIGHT 1200
#घोषणा ADV7511_MIN_PIXELCLOCK 20000000
#घोषणा ADV7511_MAX_PIXELCLOCK 225000000

#घोषणा ADV7511_MAX_ADDRS (3)

/*
**********************************************************************
*
*  Arrays with configuration parameters क्रम the ADV7511
*
**********************************************************************
*/

काष्ठा i2c_reg_value अणु
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर value;
पूर्ण;

काष्ठा adv7511_state_edid अणु
	/* total number of blocks */
	u32 blocks;
	/* Number of segments पढ़ो */
	u32 segments;
	u8 data[EDID_MAX_SEGM * 256];
	/* Number of EDID पढ़ो retries left */
	अचिन्हित पढ़ो_retries;
	bool complete;
पूर्ण;

काष्ठा adv7511_state अणु
	काष्ठा adv7511_platक्रमm_data pdata;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler hdl;
	पूर्णांक chip_revision;
	u8 i2c_edid_addr;
	u8 i2c_pkपंचांगem_addr;
	u8 i2c_cec_addr;

	काष्ठा i2c_client *i2c_cec;
	काष्ठा cec_adapter *cec_adap;
	u8   cec_addr[ADV7511_MAX_ADDRS];
	u8   cec_valid_addrs;
	bool cec_enabled_adap;

	/* Is the adv7511 घातered on? */
	bool घातer_on;
	/* Did we receive hotplug and rx-sense संकेतs? */
	bool have_monitor;
	bool enabled_irq;
	/* timings from s_dv_timings */
	काष्ठा v4l2_dv_timings dv_timings;
	u32 fmt_code;
	u32 colorspace;
	u32 ycbcr_enc;
	u32 quantization;
	u32 xfer_func;
	u32 content_type;
	/* controls */
	काष्ठा v4l2_ctrl *hdmi_mode_ctrl;
	काष्ठा v4l2_ctrl *hotplug_ctrl;
	काष्ठा v4l2_ctrl *rx_sense_ctrl;
	काष्ठा v4l2_ctrl *have_edid0_ctrl;
	काष्ठा v4l2_ctrl *rgb_quantization_range_ctrl;
	काष्ठा v4l2_ctrl *content_type_ctrl;
	काष्ठा i2c_client *i2c_edid;
	काष्ठा i2c_client *i2c_pkपंचांगem;
	काष्ठा adv7511_state_edid edid;
	/* Running counter of the number of detected EDIDs (क्रम debugging) */
	अचिन्हित edid_detect_counter;
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा delayed_work edid_handler; /* work entry */
पूर्ण;

अटल व्योम adv7511_check_monitor_present_status(काष्ठा v4l2_subdev *sd);
अटल bool adv7511_check_edid_status(काष्ठा v4l2_subdev *sd);
अटल व्योम adv7511_setup(काष्ठा v4l2_subdev *sd);
अटल पूर्णांक adv7511_s_i2s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq);
अटल पूर्णांक adv7511_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq);


अटल स्थिर काष्ठा v4l2_dv_timings_cap adv7511_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(640, ADV7511_MAX_WIDTH, 350, ADV7511_MAX_HEIGHT,
		ADV7511_MIN_PIXELCLOCK, ADV7511_MAX_PIXELCLOCK,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM)
पूर्ण;

अटल अंतरभूत काष्ठा adv7511_state *get_adv7511_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv7511_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा adv7511_state, hdl)->sd;
पूर्ण

/* ------------------------ I2C ----------------------------------------------- */

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
	वापस -1;
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
	वापस -1;
पूर्ण

अटल पूर्णांक adv7511_rd(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस adv_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक adv7511_wr(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	v4l2_err(sd, "%s: i2c write error\n", __func__);
	वापस ret;
पूर्ण

/* To set specअगरic bits in the रेजिस्टर, a clear-mask is given (to be AND-ed),
   and then the value-mask (to be OR-ed). */
अटल अंतरभूत व्योम adv7511_wr_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 clr_mask, u8 val_mask)
अणु
	adv7511_wr(sd, reg, (adv7511_rd(sd, reg) & clr_mask) | val_mask);
पूर्ण

अटल पूर्णांक adv7511_edid_rd(काष्ठा v4l2_subdev *sd, uपूर्णांक16_t len, uपूर्णांक8_t *buf)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	पूर्णांक i;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	क्रम (i = 0; i < len; i += I2C_SMBUS_BLOCK_MAX) अणु
		s32 ret;

		ret = i2c_smbus_पढ़ो_i2c_block_data(state->i2c_edid, i,
						    I2C_SMBUS_BLOCK_MAX, buf + i);
		अगर (ret < 0) अणु
			v4l2_err(sd, "%s: i2c read error\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक adv7511_cec_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	वापस i2c_smbus_पढ़ो_byte_data(state->i2c_cec, reg);
पूर्ण

अटल पूर्णांक adv7511_cec_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(state->i2c_cec, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	v4l2_err(sd, "%s: I2C Write Problem\n", __func__);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक adv7511_cec_ग_लिखो_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 mask,
				   u8 val)
अणु
	वापस adv7511_cec_ग_लिखो(sd, reg, (adv7511_cec_पढ़ो(sd, reg) & mask) | val);
पूर्ण

अटल पूर्णांक adv7511_pkपंचांगem_rd(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	वापस adv_smbus_पढ़ो_byte_data(state->i2c_pkपंचांगem, reg);
पूर्ण

अटल पूर्णांक adv7511_pkपंचांगem_wr(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(state->i2c_pkपंचांगem, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	v4l2_err(sd, "%s: i2c write error\n", __func__);
	वापस ret;
पूर्ण

/* To set specअगरic bits in the रेजिस्टर, a clear-mask is given (to be AND-ed),
   and then the value-mask (to be OR-ed). */
अटल अंतरभूत व्योम adv7511_pkपंचांगem_wr_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 clr_mask, u8 val_mask)
अणु
	adv7511_pkपंचांगem_wr(sd, reg, (adv7511_pkपंचांगem_rd(sd, reg) & clr_mask) | val_mask);
पूर्ण

अटल अंतरभूत bool adv7511_have_hotplug(काष्ठा v4l2_subdev *sd)
अणु
	वापस adv7511_rd(sd, 0x42) & MASK_ADV7511_HPD_DETECT;
पूर्ण

अटल अंतरभूत bool adv7511_have_rx_sense(काष्ठा v4l2_subdev *sd)
अणु
	वापस adv7511_rd(sd, 0x42) & MASK_ADV7511_MSEN_DETECT;
पूर्ण

अटल व्योम adv7511_csc_conversion_mode(काष्ठा v4l2_subdev *sd, u8 mode)
अणु
	adv7511_wr_and_or(sd, 0x18, 0x9f, (mode & 0x3)<<5);
पूर्ण

अटल व्योम adv7511_csc_coeff(काष्ठा v4l2_subdev *sd,
			      u16 A1, u16 A2, u16 A3, u16 A4,
			      u16 B1, u16 B2, u16 B3, u16 B4,
			      u16 C1, u16 C2, u16 C3, u16 C4)
अणु
	/* A */
	adv7511_wr_and_or(sd, 0x18, 0xe0, A1>>8);
	adv7511_wr(sd, 0x19, A1);
	adv7511_wr_and_or(sd, 0x1A, 0xe0, A2>>8);
	adv7511_wr(sd, 0x1B, A2);
	adv7511_wr_and_or(sd, 0x1c, 0xe0, A3>>8);
	adv7511_wr(sd, 0x1d, A3);
	adv7511_wr_and_or(sd, 0x1e, 0xe0, A4>>8);
	adv7511_wr(sd, 0x1f, A4);

	/* B */
	adv7511_wr_and_or(sd, 0x20, 0xe0, B1>>8);
	adv7511_wr(sd, 0x21, B1);
	adv7511_wr_and_or(sd, 0x22, 0xe0, B2>>8);
	adv7511_wr(sd, 0x23, B2);
	adv7511_wr_and_or(sd, 0x24, 0xe0, B3>>8);
	adv7511_wr(sd, 0x25, B3);
	adv7511_wr_and_or(sd, 0x26, 0xe0, B4>>8);
	adv7511_wr(sd, 0x27, B4);

	/* C */
	adv7511_wr_and_or(sd, 0x28, 0xe0, C1>>8);
	adv7511_wr(sd, 0x29, C1);
	adv7511_wr_and_or(sd, 0x2A, 0xe0, C2>>8);
	adv7511_wr(sd, 0x2B, C2);
	adv7511_wr_and_or(sd, 0x2C, 0xe0, C3>>8);
	adv7511_wr(sd, 0x2D, C3);
	adv7511_wr_and_or(sd, 0x2E, 0xe0, C4>>8);
	adv7511_wr(sd, 0x2F, C4);
पूर्ण

अटल व्योम adv7511_csc_rgb_full2limit(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	अगर (enable) अणु
		u8 csc_mode = 0;
		adv7511_csc_conversion_mode(sd, csc_mode);
		adv7511_csc_coeff(sd,
				  4096-564, 0, 0, 256,
				  0, 4096-564, 0, 256,
				  0, 0, 4096-564, 256);
		/* enable CSC */
		adv7511_wr_and_or(sd, 0x18, 0x7f, 0x80);
		/* AVI infoframe: Limited range RGB (16-235) */
		adv7511_wr_and_or(sd, 0x57, 0xf3, 0x04);
	पूर्ण अन्यथा अणु
		/* disable CSC */
		adv7511_wr_and_or(sd, 0x18, 0x7f, 0x0);
		/* AVI infoframe: Full range RGB (0-255) */
		adv7511_wr_and_or(sd, 0x57, 0xf3, 0x08);
	पूर्ण
पूर्ण

अटल व्योम adv7511_set_rgb_quantization_mode(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	/* Only makes sense क्रम RGB क्रमmats */
	अगर (state->fmt_code != MEDIA_BUS_FMT_RGB888_1X24) अणु
		/* so just keep quantization */
		adv7511_csc_rgb_full2limit(sd, false);
		वापस;
	पूर्ण

	चयन (ctrl->val) अणु
	हाल V4L2_DV_RGB_RANGE_AUTO:
		/* स्वतःmatic */
		अगर (state->dv_timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
			/* CE क्रमmat, RGB limited range (16-235) */
			adv7511_csc_rgb_full2limit(sd, true);
		पूर्ण अन्यथा अणु
			/* not CE क्रमmat, RGB full range (0-255) */
			adv7511_csc_rgb_full2limit(sd, false);
		पूर्ण
		अवरोध;
	हाल V4L2_DV_RGB_RANGE_LIMITED:
		/* RGB limited range (16-235) */
		adv7511_csc_rgb_full2limit(sd, true);
		अवरोध;
	हाल V4L2_DV_RGB_RANGE_FULL:
		/* RGB full range (0-255) */
		adv7511_csc_rgb_full2limit(sd, false);
		अवरोध;
	पूर्ण
पूर्ण

/* ------------------------------ CTRL OPS ------------------------------ */

अटल पूर्णांक adv7511_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	v4l2_dbg(1, debug, sd, "%s: ctrl id: %d, ctrl->val %d\n", __func__, ctrl->id, ctrl->val);

	अगर (state->hdmi_mode_ctrl == ctrl) अणु
		/* Set HDMI or DVI-D */
		adv7511_wr_and_or(sd, 0xaf, 0xfd, ctrl->val == V4L2_DV_TX_MODE_HDMI ? 0x02 : 0x00);
		वापस 0;
	पूर्ण
	अगर (state->rgb_quantization_range_ctrl == ctrl) अणु
		adv7511_set_rgb_quantization_mode(sd, ctrl);
		वापस 0;
	पूर्ण
	अगर (state->content_type_ctrl == ctrl) अणु
		u8 itc, cn;

		state->content_type = ctrl->val;
		itc = state->content_type != V4L2_DV_IT_CONTENT_TYPE_NO_ITC;
		cn = itc ? state->content_type : V4L2_DV_IT_CONTENT_TYPE_GRAPHICS;
		adv7511_wr_and_or(sd, 0x57, 0x7f, itc << 7);
		adv7511_wr_and_or(sd, 0x59, 0xcf, cn << 4);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adv7511_ctrl_ops = अणु
	.s_ctrl = adv7511_s_ctrl,
पूर्ण;

/* ---------------------------- CORE OPS ------------------------------------------- */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल व्योम adv7511_inv_रेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	v4l2_info(sd, "0x000-0x0ff: Main Map\n");
	अगर (state->i2c_cec)
		v4l2_info(sd, "0x100-0x1ff: CEC Map\n");
पूर्ण

अटल पूर्णांक adv7511_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	reg->size = 1;
	चयन (reg->reg >> 8) अणु
	हाल 0:
		reg->val = adv7511_rd(sd, reg->reg & 0xff);
		अवरोध;
	हाल 1:
		अगर (state->i2c_cec) अणु
			reg->val = adv7511_cec_पढ़ो(sd, reg->reg & 0xff);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv7511_inv_रेजिस्टर(sd);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	चयन (reg->reg >> 8) अणु
	हाल 0:
		adv7511_wr(sd, reg->reg & 0xff, reg->val & 0xff);
		अवरोध;
	हाल 1:
		अगर (state->i2c_cec) अणु
			adv7511_cec_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv7511_inv_रेजिस्टर(sd);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा adv7511_cfg_पढ़ो_infoframe अणु
	स्थिर अक्षर *desc;
	u8 present_reg;
	u8 present_mask;
	u8 header[3];
	u16 payload_addr;
पूर्ण;

अटल u8 hdmi_infoframe_checksum(u8 *ptr, माप_प्रकार size)
अणु
	u8 csum = 0;
	माप_प्रकार i;

	/* compute checksum */
	क्रम (i = 0; i < size; i++)
		csum += ptr[i];

	वापस 256 - csum;
पूर्ण

अटल व्योम log_infoframe(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा adv7511_cfg_पढ़ो_infoframe *cri)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा device *dev = &client->dev;
	जोड़ hdmi_infoframe frame;
	u8 buffer[32];
	u8 len;
	पूर्णांक i;

	अगर (!(adv7511_rd(sd, cri->present_reg) & cri->present_mask)) अणु
		v4l2_info(sd, "%s infoframe not transmitted\n", cri->desc);
		वापस;
	पूर्ण

	स_नकल(buffer, cri->header, माप(cri->header));

	len = buffer[2];

	अगर (len + 4 > माप(buffer)) अणु
		v4l2_err(sd, "%s: invalid %s infoframe length %d\n", __func__, cri->desc, len);
		वापस;
	पूर्ण

	अगर (cri->payload_addr >= 0x100) अणु
		क्रम (i = 0; i < len; i++)
			buffer[i + 4] = adv7511_pkपंचांगem_rd(sd, cri->payload_addr + i - 0x100);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len; i++)
			buffer[i + 4] = adv7511_rd(sd, cri->payload_addr + i);
	पूर्ण
	buffer[3] = 0;
	buffer[3] = hdmi_infoframe_checksum(buffer, len + 4);

	अगर (hdmi_infoframe_unpack(&frame, buffer, माप(buffer)) < 0) अणु
		v4l2_err(sd, "%s: unpack of %s infoframe failed\n", __func__, cri->desc);
		वापस;
	पूर्ण

	hdmi_infoframe_log(KERN_INFO, dev, &frame);
पूर्ण

अटल व्योम adv7511_log_infoframes(काष्ठा v4l2_subdev *sd)
अणु
	अटल स्थिर काष्ठा adv7511_cfg_पढ़ो_infoframe cri[] = अणु
		अणु "AVI", 0x44, 0x10, अणु 0x82, 2, 13 पूर्ण, 0x55 पूर्ण,
		अणु "Audio", 0x44, 0x08, अणु 0x84, 1, 10 पूर्ण, 0x73 पूर्ण,
		अणु "SDP", 0x40, 0x40, अणु 0x83, 1, 25 पूर्ण, 0x103 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cri); i++)
		log_infoframe(sd, &cri[i]);
पूर्ण

अटल पूर्णांक adv7511_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	काष्ठा adv7511_state_edid *edid = &state->edid;
	पूर्णांक i;

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

	v4l2_info(sd, "power %s\n", state->घातer_on ? "on" : "off");
	v4l2_info(sd, "%s hotplug, %s Rx Sense, %s EDID (%d block(s))\n",
		  (adv7511_rd(sd, 0x42) & MASK_ADV7511_HPD_DETECT) ? "detected" : "no",
		  (adv7511_rd(sd, 0x42) & MASK_ADV7511_MSEN_DETECT) ? "detected" : "no",
		  edid->segments ? "found" : "no",
		  edid->blocks);
	v4l2_info(sd, "%s output %s\n",
		  (adv7511_rd(sd, 0xaf) & 0x02) ?
		  "HDMI" : "DVI-D",
		  (adv7511_rd(sd, 0xa1) & 0x3c) ?
		  "disabled" : "enabled");
	v4l2_info(sd, "state: %s, error: %s, detect count: %u, msk/irq: %02x/%02x\n",
			  states[adv7511_rd(sd, 0xc8) & 0xf],
			  errors[adv7511_rd(sd, 0xc8) >> 4], state->edid_detect_counter,
			  adv7511_rd(sd, 0x94), adv7511_rd(sd, 0x96));
	v4l2_info(sd, "RGB quantization: %s range\n", adv7511_rd(sd, 0x18) & 0x80 ? "limited" : "full");
	अगर (adv7511_rd(sd, 0xaf) & 0x02) अणु
		/* HDMI only */
		u8 manual_cts = adv7511_rd(sd, 0x0a) & 0x80;
		u32 N = (adv7511_rd(sd, 0x01) & 0xf) << 16 |
			adv7511_rd(sd, 0x02) << 8 |
			adv7511_rd(sd, 0x03);
		u8 vic_detect = adv7511_rd(sd, 0x3e) >> 2;
		u8 vic_sent = adv7511_rd(sd, 0x3d) & 0x3f;
		u32 CTS;

		अगर (manual_cts)
			CTS = (adv7511_rd(sd, 0x07) & 0xf) << 16 |
			      adv7511_rd(sd, 0x08) << 8 |
			      adv7511_rd(sd, 0x09);
		अन्यथा
			CTS = (adv7511_rd(sd, 0x04) & 0xf) << 16 |
			      adv7511_rd(sd, 0x05) << 8 |
			      adv7511_rd(sd, 0x06);
		v4l2_info(sd, "CTS %s mode: N %d, CTS %d\n",
			  manual_cts ? "manual" : "automatic", N, CTS);
		v4l2_info(sd, "VIC: detected %d, sent %d\n",
			  vic_detect, vic_sent);
		adv7511_log_infoframes(sd);
	पूर्ण
	अगर (state->dv_timings.type == V4L2_DV_BT_656_1120)
		v4l2_prपूर्णांक_dv_timings(sd->name, "timings: ",
				&state->dv_timings, false);
	अन्यथा
		v4l2_info(sd, "no timings set\n");
	v4l2_info(sd, "i2c edid addr: 0x%x\n", state->i2c_edid_addr);

	अगर (state->i2c_cec == शून्य)
		वापस 0;

	v4l2_info(sd, "i2c cec addr: 0x%x\n", state->i2c_cec_addr);

	v4l2_info(sd, "CEC: %s\n", state->cec_enabled_adap ?
			"enabled" : "disabled");
	अगर (state->cec_enabled_adap) अणु
		क्रम (i = 0; i < ADV7511_MAX_ADDRS; i++) अणु
			bool is_valid = state->cec_valid_addrs & (1 << i);

			अगर (is_valid)
				v4l2_info(sd, "CEC Logical Address: 0x%x\n",
					  state->cec_addr[i]);
		पूर्ण
	पूर्ण
	v4l2_info(sd, "i2c pktmem addr: 0x%x\n", state->i2c_pkपंचांगem_addr);
	वापस 0;
पूर्ण

/* Power up/करोwn adv7511 */
अटल पूर्णांक adv7511_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	स्थिर पूर्णांक retries = 20;
	पूर्णांक i;

	v4l2_dbg(1, debug, sd, "%s: power %s\n", __func__, on ? "on" : "off");

	state->घातer_on = on;

	अगर (!on) अणु
		/* Power करोwn */
		adv7511_wr_and_or(sd, 0x41, 0xbf, 0x40);
		वापस true;
	पूर्ण

	/* Power up */
	/* The adv7511 करोes not always come up immediately.
	   Retry multiple बार. */
	क्रम (i = 0; i < retries; i++) अणु
		adv7511_wr_and_or(sd, 0x41, 0xbf, 0x0);
		अगर ((adv7511_rd(sd, 0x41) & 0x40) == 0)
			अवरोध;
		adv7511_wr_and_or(sd, 0x41, 0xbf, 0x40);
		msleep(10);
	पूर्ण
	अगर (i == retries) अणु
		v4l2_dbg(1, debug, sd, "%s: failed to powerup the adv7511!\n", __func__);
		adv7511_s_घातer(sd, 0);
		वापस false;
	पूर्ण
	अगर (i > 1)
		v4l2_dbg(1, debug, sd, "%s: needed %d retries to powerup the adv7511\n", __func__, i);

	/* Reserved रेजिस्टरs that must be set */
	adv7511_wr(sd, 0x98, 0x03);
	adv7511_wr_and_or(sd, 0x9a, 0xfe, 0x70);
	adv7511_wr(sd, 0x9c, 0x30);
	adv7511_wr_and_or(sd, 0x9d, 0xfc, 0x01);
	adv7511_wr(sd, 0xa2, 0xa4);
	adv7511_wr(sd, 0xa3, 0xa4);
	adv7511_wr(sd, 0xe0, 0xd0);
	adv7511_wr(sd, 0xf9, 0x00);

	adv7511_wr(sd, 0x43, state->i2c_edid_addr);
	adv7511_wr(sd, 0x45, state->i2c_pkपंचांगem_addr);

	/* Set number of attempts to पढ़ो the EDID */
	adv7511_wr(sd, 0xc9, 0xf);
	वापस true;
पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7511_CEC)
अटल पूर्णांक adv7511_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा adv7511_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;

	अगर (state->i2c_cec == शून्य)
		वापस -EIO;

	अगर (!state->cec_enabled_adap && enable) अणु
		/* घातer up cec section */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4e, 0xfc, 0x01);
		/* legacy mode and clear all rx buffers */
		adv7511_cec_ग_लिखो(sd, 0x4a, 0x00);
		adv7511_cec_ग_लिखो(sd, 0x4a, 0x07);
		adv7511_cec_ग_लिखो_and_or(sd, 0x11, 0xfe, 0); /* initially disable tx */
		/* enabled irqs: */
		/* tx: पढ़ोy */
		/* tx: arbitration lost */
		/* tx: retry समयout */
		/* rx: पढ़ोy 1 */
		अगर (state->enabled_irq)
			adv7511_wr_and_or(sd, 0x95, 0xc0, 0x39);
	पूर्ण अन्यथा अगर (state->cec_enabled_adap && !enable) अणु
		अगर (state->enabled_irq)
			adv7511_wr_and_or(sd, 0x95, 0xc0, 0x00);
		/* disable address mask 1-3 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4b, 0x8f, 0x00);
		/* घातer करोwn cec section */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4e, 0xfc, 0x00);
		state->cec_valid_addrs = 0;
	पूर्ण
	state->cec_enabled_adap = enable;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा adv7511_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;
	अचिन्हित पूर्णांक i, मुक्त_idx = ADV7511_MAX_ADDRS;

	अगर (!state->cec_enabled_adap)
		वापस addr == CEC_LOG_ADDR_INVALID ? 0 : -EIO;

	अगर (addr == CEC_LOG_ADDR_INVALID) अणु
		adv7511_cec_ग_लिखो_and_or(sd, 0x4b, 0x8f, 0);
		state->cec_valid_addrs = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ADV7511_MAX_ADDRS; i++) अणु
		bool is_valid = state->cec_valid_addrs & (1 << i);

		अगर (मुक्त_idx == ADV7511_MAX_ADDRS && !is_valid)
			मुक्त_idx = i;
		अगर (is_valid && state->cec_addr[i] == addr)
			वापस 0;
	पूर्ण
	अगर (i == ADV7511_MAX_ADDRS) अणु
		i = मुक्त_idx;
		अगर (i == ADV7511_MAX_ADDRS)
			वापस -ENXIO;
	पूर्ण
	state->cec_addr[i] = addr;
	state->cec_valid_addrs |= 1 << i;

	चयन (i) अणु
	हाल 0:
		/* enable address mask 0 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4b, 0xef, 0x10);
		/* set address क्रम mask 0 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4c, 0xf0, addr);
		अवरोध;
	हाल 1:
		/* enable address mask 1 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4b, 0xdf, 0x20);
		/* set address क्रम mask 1 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4c, 0x0f, addr << 4);
		अवरोध;
	हाल 2:
		/* enable address mask 2 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4b, 0xbf, 0x40);
		/* set address क्रम mask 1 */
		adv7511_cec_ग_लिखो_and_or(sd, 0x4d, 0xf0, addr);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				     u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा adv7511_state *state = cec_get_drvdata(adap);
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 len = msg->len;
	अचिन्हित पूर्णांक i;

	v4l2_dbg(1, debug, sd, "%s: len %d\n", __func__, len);

	अगर (len > 16) अणु
		v4l2_err(sd, "%s: len exceeded 16 (%d)\n", __func__, len);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The number of retries is the number of attempts - 1, but retry
	 * at least once. It's not clear अगर a value of 0 is allowed, so
	 * let's करो at least one retry.
	 */
	adv7511_cec_ग_लिखो_and_or(sd, 0x12, ~0x70, max(1, attempts - 1) << 4);

	/* clear cec tx irq status */
	adv7511_wr(sd, 0x97, 0x38);

	/* ग_लिखो data */
	क्रम (i = 0; i < len; i++)
		adv7511_cec_ग_लिखो(sd, i, msg->msg[i]);

	/* set length (data + header) */
	adv7511_cec_ग_लिखो(sd, 0x10, len);
	/* start transmit, enable tx */
	adv7511_cec_ग_लिखो(sd, 0x11, 0x01);
	वापस 0;
पूर्ण

अटल व्योम adv_cec_tx_raw_status(काष्ठा v4l2_subdev *sd, u8 tx_raw_status)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	अगर ((adv7511_cec_पढ़ो(sd, 0x11) & 0x01) == 0) अणु
		v4l2_dbg(1, debug, sd, "%s: tx raw: tx disabled\n", __func__);
		वापस;
	पूर्ण

	अगर (tx_raw_status & 0x10) अणु
		v4l2_dbg(1, debug, sd,
			 "%s: tx raw: arbitration lost\n", __func__);
		cec_transmit_करोne(state->cec_adap, CEC_TX_STATUS_ARB_LOST,
				  1, 0, 0, 0);
		वापस;
	पूर्ण
	अगर (tx_raw_status & 0x08) अणु
		u8 status;
		u8 nack_cnt;
		u8 low_drive_cnt;

		v4l2_dbg(1, debug, sd, "%s: tx raw: retry failed\n", __func__);
		/*
		 * We set this status bit since this hardware perक्रमms
		 * retransmissions.
		 */
		status = CEC_TX_STATUS_MAX_RETRIES;
		nack_cnt = adv7511_cec_पढ़ो(sd, 0x14) & 0xf;
		अगर (nack_cnt)
			status |= CEC_TX_STATUS_NACK;
		low_drive_cnt = adv7511_cec_पढ़ो(sd, 0x14) >> 4;
		अगर (low_drive_cnt)
			status |= CEC_TX_STATUS_LOW_DRIVE;
		cec_transmit_करोne(state->cec_adap, status,
				  0, nack_cnt, low_drive_cnt, 0);
		वापस;
	पूर्ण
	अगर (tx_raw_status & 0x20) अणु
		v4l2_dbg(1, debug, sd, "%s: tx raw: ready ok\n", __func__);
		cec_transmit_करोne(state->cec_adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
		वापस;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops adv7511_cec_adap_ops = अणु
	.adap_enable = adv7511_cec_adap_enable,
	.adap_log_addr = adv7511_cec_adap_log_addr,
	.adap_transmit = adv7511_cec_adap_transmit,
पूर्ण;
#पूर्ण_अगर

/* Enable पूर्णांकerrupts */
अटल व्योम adv7511_set_isr(काष्ठा v4l2_subdev *sd, bool enable)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	u8 irqs = MASK_ADV7511_HPD_INT | MASK_ADV7511_MSEN_INT;
	u8 irqs_rd;
	पूर्णांक retries = 100;

	v4l2_dbg(2, debug, sd, "%s: %s\n", __func__, enable ? "enable" : "disable");

	अगर (state->enabled_irq == enable)
		वापस;
	state->enabled_irq = enable;

	/* The datasheet says that the EDID पढ़ोy पूर्णांकerrupt should be
	   disabled अगर there is no hotplug. */
	अगर (!enable)
		irqs = 0;
	अन्यथा अगर (adv7511_have_hotplug(sd))
		irqs |= MASK_ADV7511_EDID_RDY_INT;

	/*
	 * This i2c ग_लिखो can fail (approx. 1 in 1000 ग_लिखोs). But it
	 * is essential that this रेजिस्टर is correct, so retry it
	 * multiple बार.
	 *
	 * Note that the i2c ग_लिखो करोes not report an error, but the पढ़ोback
	 * clearly shows the wrong value.
	 */
	करो अणु
		adv7511_wr(sd, 0x94, irqs);
		irqs_rd = adv7511_rd(sd, 0x94);
	पूर्ण जबतक (retries-- && irqs_rd != irqs);

	अगर (irqs_rd != irqs)
		v4l2_err(sd, "Could not set interrupts: hw failure?\n");

	adv7511_wr_and_or(sd, 0x95, 0xc0,
			  (state->cec_enabled_adap && enable) ? 0x39 : 0x00);
पूर्ण

/* Interrupt handler */
अटल पूर्णांक adv7511_isr(काष्ठा v4l2_subdev *sd, u32 status, bool *handled)
अणु
	u8 irq_status;
	u8 cec_irq;

	/* disable पूर्णांकerrupts to prevent a race condition */
	adv7511_set_isr(sd, false);
	irq_status = adv7511_rd(sd, 0x96);
	cec_irq = adv7511_rd(sd, 0x97);
	/* clear detected पूर्णांकerrupts */
	adv7511_wr(sd, 0x96, irq_status);
	adv7511_wr(sd, 0x97, cec_irq);

	v4l2_dbg(1, debug, sd, "%s: irq 0x%x, cec-irq 0x%x\n", __func__,
		 irq_status, cec_irq);

	अगर (irq_status & (MASK_ADV7511_HPD_INT | MASK_ADV7511_MSEN_INT))
		adv7511_check_monitor_present_status(sd);
	अगर (irq_status & MASK_ADV7511_EDID_RDY_INT)
		adv7511_check_edid_status(sd);

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7511_CEC)
	अगर (cec_irq & 0x38)
		adv_cec_tx_raw_status(sd, cec_irq);

	अगर (cec_irq & 1) अणु
		काष्ठा adv7511_state *state = get_adv7511_state(sd);
		काष्ठा cec_msg msg;

		msg.len = adv7511_cec_पढ़ो(sd, 0x25) & 0x1f;

		v4l2_dbg(1, debug, sd, "%s: cec msg len %d\n", __func__,
			 msg.len);

		अगर (msg.len > 16)
			msg.len = 16;

		अगर (msg.len) अणु
			u8 i;

			क्रम (i = 0; i < msg.len; i++)
				msg.msg[i] = adv7511_cec_पढ़ो(sd, i + 0x15);

			adv7511_cec_ग_लिखो(sd, 0x4a, 0); /* toggle to re-enable rx 1 */
			adv7511_cec_ग_लिखो(sd, 0x4a, 1);
			cec_received_msg(state->cec_adap, &msg);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* enable पूर्णांकerrupts */
	adv7511_set_isr(sd, true);

	अगर (handled)
		*handled = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv7511_core_ops = अणु
	.log_status = adv7511_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = adv7511_g_रेजिस्टर,
	.s_रेजिस्टर = adv7511_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer = adv7511_s_घातer,
	.पूर्णांकerrupt_service_routine = adv7511_isr,
पूर्ण;

/* ------------------------------ VIDEO OPS ------------------------------ */

/* Enable/disable adv7511 output */
अटल पूर्णांक adv7511_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	v4l2_dbg(1, debug, sd, "%s: %sable\n", __func__, (enable ? "en" : "dis"));
	adv7511_wr_and_or(sd, 0xa1, ~0x3c, (enable ? 0 : 0x3c));
	अगर (enable) अणु
		adv7511_check_monitor_present_status(sd);
	पूर्ण अन्यथा अणु
		adv7511_s_घातer(sd, 0);
		state->have_monitor = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_s_dv_timings(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	u32 fps;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	/* quick sanity check */
	अगर (!v4l2_valid_dv_timings(timings, &adv7511_timings_cap, शून्य, शून्य))
		वापस -EINVAL;

	/* Fill the optional fields .standards and .flags in काष्ठा v4l2_dv_timings
	   अगर the क्रमmat is one of the CEA or DMT timings. */
	v4l2_find_dv_timings_cap(timings, &adv7511_timings_cap, 0, शून्य, शून्य);

	/* save timings */
	state->dv_timings = *timings;

	/* set h/vsync polarities */
	adv7511_wr_and_or(sd, 0x17, 0x9f,
		((bt->polarities & V4L2_DV_VSYNC_POS_POL) ? 0 : 0x40) |
		((bt->polarities & V4L2_DV_HSYNC_POS_POL) ? 0 : 0x20));

	fps = (u32)bt->pixelघड़ी / (V4L2_DV_BT_FRAME_WIDTH(bt) * V4L2_DV_BT_FRAME_HEIGHT(bt));
	चयन (fps) अणु
	हाल 24:
		adv7511_wr_and_or(sd, 0xfb, 0xf9, 1 << 1);
		अवरोध;
	हाल 25:
		adv7511_wr_and_or(sd, 0xfb, 0xf9, 2 << 1);
		अवरोध;
	हाल 30:
		adv7511_wr_and_or(sd, 0xfb, 0xf9, 3 << 1);
		अवरोध;
	शेष:
		adv7511_wr_and_or(sd, 0xfb, 0xf9, 0);
		अवरोध;
	पूर्ण

	/* update quantization range based on new dv_timings */
	adv7511_set_rgb_quantization_mode(sd, state->rgb_quantization_range_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_g_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (!timings)
		वापस -EINVAL;

	*timings = state->dv_timings;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->pad != 0)
		वापस -EINVAL;

	वापस v4l2_क्रमागत_dv_timings_cap(timings, &adv7511_timings_cap, शून्य, शून्य);
पूर्ण

अटल पूर्णांक adv7511_dv_timings_cap(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (cap->pad != 0)
		वापस -EINVAL;

	*cap = adv7511_timings_cap;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv7511_video_ops = अणु
	.s_stream = adv7511_s_stream,
	.s_dv_timings = adv7511_s_dv_timings,
	.g_dv_timings = adv7511_g_dv_timings,
पूर्ण;

/* ------------------------------ AUDIO OPS ------------------------------ */
अटल पूर्णांक adv7511_s_audio_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	v4l2_dbg(1, debug, sd, "%s: %sable\n", __func__, (enable ? "en" : "dis"));

	अगर (enable)
		adv7511_wr_and_or(sd, 0x4b, 0x3f, 0x80);
	अन्यथा
		adv7511_wr_and_or(sd, 0x4b, 0x3f, 0x40);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
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
	adv7511_wr(sd, 0x01, (N >> 16) & 0xf);
	adv7511_wr(sd, 0x02, (N >> 8) & 0xff);
	adv7511_wr(sd, 0x03, N & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_s_i2s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
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
	adv7511_wr_and_or(sd, 0x15, 0xf, i2s_sf);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_s_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output, u32 config)
अणु
	/* Only 2 channels in use क्रम application */
	adv7511_wr_and_or(sd, 0x73, 0xf8, 0x1);
	/* Speaker mapping */
	adv7511_wr(sd, 0x76, 0x00);

	/* 16 bit audio word length */
	adv7511_wr_and_or(sd, 0x14, 0xf0, 0x02);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_audio_ops adv7511_audio_ops = अणु
	.s_stream = adv7511_s_audio_stream,
	.s_घड़ी_freq = adv7511_s_घड़ी_freq,
	.s_i2s_घड़ी_freq = adv7511_s_i2s_घड़ी_freq,
	.s_routing = adv7511_s_routing,
पूर्ण;

/* ---------------------------- PAD OPS ------------------------------------- */

अटल पूर्णांक adv7511_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->pad != 0)
		वापस -EINVAL;

	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = state->edid.blocks;
		वापस 0;
	पूर्ण

	अगर (state->edid.blocks == 0)
		वापस -ENODATA;

	अगर (edid->start_block >= state->edid.blocks)
		वापस -EINVAL;

	अगर (edid->start_block + edid->blocks > state->edid.blocks)
		edid->blocks = state->edid.blocks - edid->start_block;

	स_नकल(edid->edid, &state->edid.data[edid->start_block * 128],
	       128 * edid->blocks);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad != 0)
		वापस -EINVAL;

	चयन (code->index) अणु
	हाल 0:
		code->code = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	हाल 1:
		code->code = MEDIA_BUS_FMT_YUYV8_1X16;
		अवरोध;
	हाल 2:
		code->code = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adv7511_fill_क्रमmat(काष्ठा adv7511_state *state,
				काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	क्रमmat->width = state->dv_timings.bt.width;
	क्रमmat->height = state->dv_timings.bt.height;
	क्रमmat->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक adv7511_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;

	स_रखो(&क्रमmat->क्रमmat, 0, माप(क्रमmat->क्रमmat));
	adv7511_fill_क्रमmat(state, &क्रमmat->क्रमmat);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		क्रमmat->क्रमmat.code = fmt->code;
		क्रमmat->क्रमmat.colorspace = fmt->colorspace;
		क्रमmat->क्रमmat.ycbcr_enc = fmt->ycbcr_enc;
		क्रमmat->क्रमmat.quantization = fmt->quantization;
		क्रमmat->क्रमmat.xfer_func = fmt->xfer_func;
	पूर्ण अन्यथा अणु
		क्रमmat->क्रमmat.code = state->fmt_code;
		क्रमmat->क्रमmat.colorspace = state->colorspace;
		क्रमmat->क्रमmat.ycbcr_enc = state->ycbcr_enc;
		क्रमmat->क्रमmat.quantization = state->quantization;
		क्रमmat->क्रमmat.xfer_func = state->xfer_func;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	/*
	 * Bitfield namings come the CEA-861-F standard, table 8 "Auxiliary
	 * Video Inक्रमmation (AVI) InfoFrame Format"
	 *
	 * c = Colorimetry
	 * ec = Extended Colorimetry
	 * y = RGB or YCbCr
	 * q = RGB Quantization Range
	 * yq = YCC Quantization Range
	 */
	u8 c = HDMI_COLORIMETRY_NONE;
	u8 ec = HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
	u8 y = HDMI_COLORSPACE_RGB;
	u8 q = HDMI_QUANTIZATION_RANGE_DEFAULT;
	u8 yq = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
	u8 itc = state->content_type != V4L2_DV_IT_CONTENT_TYPE_NO_ITC;
	u8 cn = itc ? state->content_type : V4L2_DV_IT_CONTENT_TYPE_GRAPHICS;

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;
	चयन (क्रमmat->क्रमmat.code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adv7511_fill_क्रमmat(state, &क्रमmat->क्रमmat);
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		fmt->code = क्रमmat->क्रमmat.code;
		fmt->colorspace = क्रमmat->क्रमmat.colorspace;
		fmt->ycbcr_enc = क्रमmat->क्रमmat.ycbcr_enc;
		fmt->quantization = क्रमmat->क्रमmat.quantization;
		fmt->xfer_func = क्रमmat->क्रमmat.xfer_func;
		वापस 0;
	पूर्ण

	चयन (क्रमmat->क्रमmat.code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		adv7511_wr_and_or(sd, 0x15, 0xf0, 0x01);
		adv7511_wr_and_or(sd, 0x16, 0x03, 0xb8);
		y = HDMI_COLORSPACE_YUV422;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		adv7511_wr_and_or(sd, 0x15, 0xf0, 0x01);
		adv7511_wr_and_or(sd, 0x16, 0x03, 0xbc);
		y = HDMI_COLORSPACE_YUV422;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	शेष:
		adv7511_wr_and_or(sd, 0x15, 0xf0, 0x00);
		adv7511_wr_and_or(sd, 0x16, 0x03, 0x00);
		अवरोध;
	पूर्ण
	state->fmt_code = क्रमmat->क्रमmat.code;
	state->colorspace = क्रमmat->क्रमmat.colorspace;
	state->ycbcr_enc = क्रमmat->क्रमmat.ycbcr_enc;
	state->quantization = क्रमmat->क्रमmat.quantization;
	state->xfer_func = क्रमmat->क्रमmat.xfer_func;

	चयन (क्रमmat->क्रमmat.colorspace) अणु
	हाल V4L2_COLORSPACE_OPRGB:
		c = HDMI_COLORIMETRY_EXTENDED;
		ec = y ? HDMI_EXTENDED_COLORIMETRY_OPYCC_601 :
			 HDMI_EXTENDED_COLORIMETRY_OPRGB;
		अवरोध;
	हाल V4L2_COLORSPACE_SMPTE170M:
		c = y ? HDMI_COLORIMETRY_ITU_601 : HDMI_COLORIMETRY_NONE;
		अगर (y && क्रमmat->क्रमmat.ycbcr_enc == V4L2_YCBCR_ENC_XV601) अणु
			c = HDMI_COLORIMETRY_EXTENDED;
			ec = HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
		पूर्ण
		अवरोध;
	हाल V4L2_COLORSPACE_REC709:
		c = y ? HDMI_COLORIMETRY_ITU_709 : HDMI_COLORIMETRY_NONE;
		अगर (y && क्रमmat->क्रमmat.ycbcr_enc == V4L2_YCBCR_ENC_XV709) अणु
			c = HDMI_COLORIMETRY_EXTENDED;
			ec = HDMI_EXTENDED_COLORIMETRY_XV_YCC_709;
		पूर्ण
		अवरोध;
	हाल V4L2_COLORSPACE_SRGB:
		c = y ? HDMI_COLORIMETRY_EXTENDED : HDMI_COLORIMETRY_NONE;
		ec = y ? HDMI_EXTENDED_COLORIMETRY_S_YCC_601 :
			 HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
		अवरोध;
	हाल V4L2_COLORSPACE_BT2020:
		c = HDMI_COLORIMETRY_EXTENDED;
		अगर (y && क्रमmat->क्रमmat.ycbcr_enc == V4L2_YCBCR_ENC_BT2020_CONST_LUM)
			ec = 5; /* Not yet available in hdmi.h */
		अन्यथा
			ec = 6; /* Not yet available in hdmi.h */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * CEA-861-F says that क्रम RGB क्रमmats the YCC range must match the
	 * RGB range, although sources should ignore the YCC range.
	 *
	 * The RGB quantization range shouldn't be non-zero if the EDID doesn't
	 * have the Q bit set in the Video Capabilities Data Block, however this
	 * isn't checked at the moment. The assumption is that the application
	 * knows the EDID and can detect this.
	 *
	 * The same is true क्रम the YCC quantization range: non-standard YCC
	 * quantization ranges should only be sent अगर the EDID has the YQ bit
	 * set in the Video Capabilities Data Block.
	 */
	चयन (क्रमmat->क्रमmat.quantization) अणु
	हाल V4L2_QUANTIZATION_FULL_RANGE:
		q = y ? HDMI_QUANTIZATION_RANGE_DEFAULT :
			HDMI_QUANTIZATION_RANGE_FULL;
		yq = q ? q - 1 : HDMI_YCC_QUANTIZATION_RANGE_FULL;
		अवरोध;
	हाल V4L2_QUANTIZATION_LIM_RANGE:
		q = y ? HDMI_QUANTIZATION_RANGE_DEFAULT :
			HDMI_QUANTIZATION_RANGE_LIMITED;
		yq = q ? q - 1 : HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
		अवरोध;
	पूर्ण

	adv7511_wr_and_or(sd, 0x4a, 0xbf, 0);
	adv7511_wr_and_or(sd, 0x55, 0x9f, y << 5);
	adv7511_wr_and_or(sd, 0x56, 0x3f, c << 6);
	adv7511_wr_and_or(sd, 0x57, 0x83, (ec << 4) | (q << 2) | (itc << 7));
	adv7511_wr_and_or(sd, 0x59, 0x0f, (yq << 6) | (cn << 4));
	adv7511_wr_and_or(sd, 0x4a, 0xff, 1);
	adv7511_set_rgb_quantization_mode(sd, state->rgb_quantization_range_ctrl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv7511_pad_ops = अणु
	.get_edid = adv7511_get_edid,
	.क्रमागत_mbus_code = adv7511_क्रमागत_mbus_code,
	.get_fmt = adv7511_get_fmt,
	.set_fmt = adv7511_set_fmt,
	.क्रमागत_dv_timings = adv7511_क्रमागत_dv_timings,
	.dv_timings_cap = adv7511_dv_timings_cap,
पूर्ण;

/* --------------------- SUBDEV OPS --------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_ops adv7511_ops = अणु
	.core  = &adv7511_core_ops,
	.pad  = &adv7511_pad_ops,
	.video = &adv7511_video_ops,
	.audio = &adv7511_audio_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */
अटल व्योम adv7511_dbg_dump_edid(पूर्णांक lvl, पूर्णांक debug, काष्ठा v4l2_subdev *sd, पूर्णांक segment, u8 *buf)
अणु
	अगर (debug >= lvl) अणु
		पूर्णांक i, j;
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
पूर्ण

अटल व्योम adv7511_notअगरy_no_edid(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	काष्ठा adv7511_edid_detect ed;

	/* We failed to पढ़ो the EDID, so send an event क्रम this. */
	ed.present = false;
	ed.segment = adv7511_rd(sd, 0xc4);
	ed.phys_addr = CEC_PHYS_ADDR_INVALID;
	cec_s_phys_addr(state->cec_adap, ed.phys_addr, false);
	v4l2_subdev_notअगरy(sd, ADV7511_EDID_DETECT, (व्योम *)&ed);
	v4l2_ctrl_s_ctrl(state->have_edid0_ctrl, 0x0);
पूर्ण

अटल व्योम adv7511_edid_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा adv7511_state *state = container_of(dwork, काष्ठा adv7511_state, edid_handler);
	काष्ठा v4l2_subdev *sd = &state->sd;

	v4l2_dbg(1, debug, sd, "%s:\n", __func__);

	अगर (adv7511_check_edid_status(sd)) अणु
		/* Return अगर we received the EDID. */
		वापस;
	पूर्ण

	अगर (adv7511_have_hotplug(sd)) अणु
		/* We must retry पढ़ोing the EDID several बार, it is possible
		 * that initially the EDID couldn't be पढ़ो due to i2c errors
		 * (DVI connectors are particularly prone to this problem). */
		अगर (state->edid.पढ़ो_retries) अणु
			state->edid.पढ़ो_retries--;
			v4l2_dbg(1, debug, sd, "%s: edid read failed\n", __func__);
			state->have_monitor = false;
			adv7511_s_घातer(sd, false);
			adv7511_s_घातer(sd, true);
			queue_delayed_work(state->work_queue, &state->edid_handler, EDID_DELAY);
			वापस;
		पूर्ण
	पूर्ण

	/* We failed to पढ़ो the EDID, so send an event क्रम this. */
	adv7511_notअगरy_no_edid(sd);
	v4l2_dbg(1, debug, sd, "%s: no edid found\n", __func__);
पूर्ण

अटल व्योम adv7511_audio_setup(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	adv7511_s_i2s_घड़ी_freq(sd, 48000);
	adv7511_s_घड़ी_freq(sd, 48000);
	adv7511_s_routing(sd, 0, 0, 0);
पूर्ण

/* Configure hdmi transmitter. */
अटल व्योम adv7511_setup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	/* Input क्रमmat: RGB 4:4:4 */
	adv7511_wr_and_or(sd, 0x15, 0xf0, 0x0);
	/* Output क्रमmat: RGB 4:4:4 */
	adv7511_wr_and_or(sd, 0x16, 0x7f, 0x0);
	/* 1st order पूर्णांकerpolation 4:2:2 -> 4:4:4 up conversion, Aspect ratio: 16:9 */
	adv7511_wr_and_or(sd, 0x17, 0xf9, 0x06);
	/* Disable pixel repetition */
	adv7511_wr_and_or(sd, 0x3b, 0x9f, 0x0);
	/* Disable CSC */
	adv7511_wr_and_or(sd, 0x18, 0x7f, 0x0);
	/* Output क्रमmat: RGB 4:4:4, Active Format Inक्रमmation is valid,
	 * underscanned */
	adv7511_wr_and_or(sd, 0x55, 0x9c, 0x12);
	/* AVI Info frame packet enable, Audio Info frame disable */
	adv7511_wr_and_or(sd, 0x44, 0xe7, 0x10);
	/* Colorimetry, Active क्रमmat aspect ratio: same as picure. */
	adv7511_wr(sd, 0x56, 0xa8);
	/* No encryption */
	adv7511_wr_and_or(sd, 0xaf, 0xed, 0x0);

	/* Positive clk edge capture क्रम input video घड़ी */
	adv7511_wr_and_or(sd, 0xba, 0x1f, 0x60);

	adv7511_audio_setup(sd);

	v4l2_ctrl_handler_setup(&state->hdl);
पूर्ण

अटल व्योम adv7511_notअगरy_monitor_detect(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_monitor_detect mdt;
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	mdt.present = state->have_monitor;
	v4l2_subdev_notअगरy(sd, ADV7511_MONITOR_DETECT, (व्योम *)&mdt);
पूर्ण

अटल व्योम adv7511_check_monitor_present_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	/* पढ़ो hotplug and rx-sense state */
	u8 status = adv7511_rd(sd, 0x42);

	v4l2_dbg(1, debug, sd, "%s: status: 0x%x%s%s\n",
			 __func__,
			 status,
			 status & MASK_ADV7511_HPD_DETECT ? ", hotplug" : "",
			 status & MASK_ADV7511_MSEN_DETECT ? ", rx-sense" : "");

	/* update पढ़ो only ctrls */
	v4l2_ctrl_s_ctrl(state->hotplug_ctrl, adv7511_have_hotplug(sd) ? 0x1 : 0x0);
	v4l2_ctrl_s_ctrl(state->rx_sense_ctrl, adv7511_have_rx_sense(sd) ? 0x1 : 0x0);

	अगर ((status & MASK_ADV7511_HPD_DETECT) && ((status & MASK_ADV7511_MSEN_DETECT) || state->edid.segments)) अणु
		v4l2_dbg(1, debug, sd, "%s: hotplug and (rx-sense or edid)\n", __func__);
		अगर (!state->have_monitor) अणु
			v4l2_dbg(1, debug, sd, "%s: monitor detected\n", __func__);
			state->have_monitor = true;
			adv7511_set_isr(sd, true);
			अगर (!adv7511_s_घातer(sd, true)) अणु
				v4l2_dbg(1, debug, sd, "%s: monitor detected, powerup failed\n", __func__);
				वापस;
			पूर्ण
			adv7511_setup(sd);
			adv7511_notअगरy_monitor_detect(sd);
			state->edid.पढ़ो_retries = EDID_MAX_RETRIES;
			queue_delayed_work(state->work_queue, &state->edid_handler, EDID_DELAY);
		पूर्ण
	पूर्ण अन्यथा अगर (status & MASK_ADV7511_HPD_DETECT) अणु
		v4l2_dbg(1, debug, sd, "%s: hotplug detected\n", __func__);
		state->edid.पढ़ो_retries = EDID_MAX_RETRIES;
		queue_delayed_work(state->work_queue, &state->edid_handler, EDID_DELAY);
	पूर्ण अन्यथा अगर (!(status & MASK_ADV7511_HPD_DETECT)) अणु
		v4l2_dbg(1, debug, sd, "%s: hotplug not detected\n", __func__);
		अगर (state->have_monitor) अणु
			v4l2_dbg(1, debug, sd, "%s: monitor not detected\n", __func__);
			state->have_monitor = false;
			adv7511_notअगरy_monitor_detect(sd);
		पूर्ण
		adv7511_s_घातer(sd, false);
		स_रखो(&state->edid, 0, माप(काष्ठा adv7511_state_edid));
		adv7511_notअगरy_no_edid(sd);
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
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	u32 blocks = state->edid.blocks;
	u8 *data = state->edid.data;

	अगर (!edid_block_verअगरy_crc(&data[segment * 256]))
		वापस false;
	अगर ((segment + 1) * 2 <= blocks)
		वापस edid_block_verअगरy_crc(&data[segment * 256 + 128]);
	वापस true;
पूर्ण

अटल bool edid_verअगरy_header(काष्ठा v4l2_subdev *sd, u32 segment)
अणु
	अटल स्थिर u8 hdmi_header[] = अणु
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
	पूर्ण;
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	u8 *data = state->edid.data;

	अगर (segment != 0)
		वापस true;
	वापस !स_भेद(data, hdmi_header, माप(hdmi_header));
पूर्ण

अटल bool adv7511_check_edid_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	u8 edidRdy = adv7511_rd(sd, 0xc5);

	v4l2_dbg(1, debug, sd, "%s: edid ready (retries: %d)\n",
			 __func__, EDID_MAX_RETRIES - state->edid.पढ़ो_retries);

	अगर (state->edid.complete)
		वापस true;

	अगर (edidRdy & MASK_ADV7511_EDID_RDY) अणु
		पूर्णांक segment = adv7511_rd(sd, 0xc4);
		काष्ठा adv7511_edid_detect ed;
		पूर्णांक err;

		अगर (segment >= EDID_MAX_SEGM) अणु
			v4l2_err(sd, "edid segment number too big\n");
			वापस false;
		पूर्ण
		v4l2_dbg(1, debug, sd, "%s: got segment %d\n", __func__, segment);
		err = adv7511_edid_rd(sd, 256, &state->edid.data[segment * 256]);
		अगर (!err) अणु
			adv7511_dbg_dump_edid(2, debug, sd, segment, &state->edid.data[segment * 256]);
			अगर (segment == 0) अणु
				state->edid.blocks = state->edid.data[0x7e] + 1;
				v4l2_dbg(1, debug, sd, "%s: %d blocks in total\n",
					 __func__, state->edid.blocks);
			पूर्ण
		पूर्ण

		अगर (err || !edid_verअगरy_crc(sd, segment) || !edid_verअगरy_header(sd, segment)) अणु
			/* Couldn't पढ़ो EDID or EDID is invalid. Force retry! */
			अगर (!err)
				v4l2_err(sd, "%s: edid crc or header error\n", __func__);
			state->have_monitor = false;
			adv7511_s_घातer(sd, false);
			adv7511_s_घातer(sd, true);
			वापस false;
		पूर्ण
		/* one more segment पढ़ो ok */
		state->edid.segments = segment + 1;
		v4l2_ctrl_s_ctrl(state->have_edid0_ctrl, 0x1);
		अगर (((state->edid.data[0x7e] >> 1) + 1) > state->edid.segments) अणु
			/* Request next EDID segment */
			v4l2_dbg(1, debug, sd, "%s: request segment %d\n", __func__, state->edid.segments);
			adv7511_wr(sd, 0xc9, 0xf);
			adv7511_wr(sd, 0xc4, state->edid.segments);
			state->edid.पढ़ो_retries = EDID_MAX_RETRIES;
			queue_delayed_work(state->work_queue, &state->edid_handler, EDID_DELAY);
			वापस false;
		पूर्ण

		v4l2_dbg(1, debug, sd, "%s: edid complete with %d segment(s)\n", __func__, state->edid.segments);
		state->edid.complete = true;
		ed.phys_addr = cec_get_edid_phys_addr(state->edid.data,
						      state->edid.segments * 256,
						      शून्य);
		/* report when we have all segments
		   but report only क्रम segment 0
		 */
		ed.present = true;
		ed.segment = 0;
		state->edid_detect_counter++;
		cec_s_phys_addr(state->cec_adap, ed.phys_addr, false);
		v4l2_subdev_notअगरy(sd, ADV7511_EDID_DETECT, (व्योम *)&ed);
		वापस ed.present;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक adv7511_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक err;

	err = cec_रेजिस्टर_adapter(state->cec_adap, &client->dev);
	अगर (err)
		cec_delete_adapter(state->cec_adap);
	वापस err;
पूर्ण

अटल व्योम adv7511_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	cec_unरेजिस्टर_adapter(state->cec_adap);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops adv7511_पूर्णांक_ops = अणु
	.रेजिस्टरed = adv7511_रेजिस्टरed,
	.unरेजिस्टरed = adv7511_unरेजिस्टरed,
पूर्ण;

/* ----------------------------------------------------------------------- */
/* Setup ADV7511 */
अटल व्योम adv7511_init_setup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7511_state *state = get_adv7511_state(sd);
	काष्ठा adv7511_state_edid *edid = &state->edid;
	u32 cec_clk = state->pdata.cec_clk;
	u8 ratio;

	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	/* clear all पूर्णांकerrupts */
	adv7511_wr(sd, 0x96, 0xff);
	adv7511_wr(sd, 0x97, 0xff);
	/*
	 * Stop HPD from resetting a lot of रेजिस्टरs.
	 * It might leave the chip in a partly un-initialized state,
	 * in particular with regards to hotplug bounces.
	 */
	adv7511_wr_and_or(sd, 0xd6, 0x3f, 0xc0);
	स_रखो(edid, 0, माप(काष्ठा adv7511_state_edid));
	state->have_monitor = false;
	adv7511_set_isr(sd, false);
	adv7511_s_stream(sd, false);
	adv7511_s_audio_stream(sd, false);

	अगर (state->i2c_cec == शून्य)
		वापस;

	v4l2_dbg(1, debug, sd, "%s: cec_clk %d\n", __func__, cec_clk);

	/* cec soft reset */
	adv7511_cec_ग_लिखो(sd, 0x50, 0x01);
	adv7511_cec_ग_लिखो(sd, 0x50, 0x00);

	/* legacy mode */
	adv7511_cec_ग_लिखो(sd, 0x4a, 0x00);
	adv7511_cec_ग_लिखो(sd, 0x4a, 0x07);

	अगर (cec_clk % 750000 != 0)
		v4l2_err(sd, "%s: cec_clk %d, not multiple of 750 Khz\n",
			 __func__, cec_clk);

	ratio = (cec_clk / 750000) - 1;
	adv7511_cec_ग_लिखो(sd, 0x4e, ratio << 2);
पूर्ण

अटल पूर्णांक adv7511_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adv7511_state *state;
	काष्ठा adv7511_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_subdev *sd;
	u8 chip_id[2];
	पूर्णांक err = -EIO;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	state = devm_kzalloc(&client->dev, माप(काष्ठा adv7511_state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	/* Platक्रमm data */
	अगर (!pdata) अणु
		v4l_err(client, "No platform data!\n");
		वापस -ENODEV;
	पूर्ण
	स_नकल(&state->pdata, pdata, माप(state->pdata));
	state->fmt_code = MEDIA_BUS_FMT_RGB888_1X24;
	state->colorspace = V4L2_COLORSPACE_SRGB;

	sd = &state->sd;

	v4l2_dbg(1, debug, sd, "detecting adv7511 client on address 0x%x\n",
			 client->addr << 1);

	v4l2_i2c_subdev_init(sd, client, &adv7511_ops);
	sd->पूर्णांकernal_ops = &adv7511_पूर्णांक_ops;

	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 10);
	/* add in ascending ID order */
	state->hdmi_mode_ctrl = v4l2_ctrl_new_std_menu(hdl, &adv7511_ctrl_ops,
			V4L2_CID_DV_TX_MODE, V4L2_DV_TX_MODE_HDMI,
			0, V4L2_DV_TX_MODE_DVI_D);
	state->hotplug_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_TX_HOTPLUG, 0, 1, 0, 0);
	state->rx_sense_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_TX_RXSENSE, 0, 1, 0, 0);
	state->have_edid0_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_TX_EDID_PRESENT, 0, 1, 0, 0);
	state->rgb_quantization_range_ctrl =
		v4l2_ctrl_new_std_menu(hdl, &adv7511_ctrl_ops,
			V4L2_CID_DV_TX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
	state->content_type_ctrl =
		v4l2_ctrl_new_std_menu(hdl, &adv7511_ctrl_ops,
			V4L2_CID_DV_TX_IT_CONTENT_TYPE, V4L2_DV_IT_CONTENT_TYPE_NO_ITC,
			0, V4L2_DV_IT_CONTENT_TYPE_NO_ITC);
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

	/* EDID and CEC i2c addr */
	state->i2c_edid_addr = state->pdata.i2c_edid << 1;
	state->i2c_cec_addr = state->pdata.i2c_cec << 1;
	state->i2c_pkपंचांगem_addr = state->pdata.i2c_pkपंचांगem << 1;

	state->chip_revision = adv7511_rd(sd, 0x0);
	chip_id[0] = adv7511_rd(sd, 0xf5);
	chip_id[1] = adv7511_rd(sd, 0xf6);
	अगर (chip_id[0] != 0x75 || chip_id[1] != 0x11) अणु
		v4l2_err(sd, "chip_id != 0x7511, read 0x%02x%02x\n", chip_id[0],
			 chip_id[1]);
		err = -EIO;
		जाओ err_entity;
	पूर्ण

	state->i2c_edid = i2c_new_dummy_device(client->adapter,
					state->i2c_edid_addr >> 1);
	अगर (IS_ERR(state->i2c_edid)) अणु
		v4l2_err(sd, "failed to register edid i2c client\n");
		err = PTR_ERR(state->i2c_edid);
		जाओ err_entity;
	पूर्ण

	adv7511_wr(sd, 0xe1, state->i2c_cec_addr);
	अगर (state->pdata.cec_clk < 3000000 ||
	    state->pdata.cec_clk > 100000000) अणु
		v4l2_err(sd, "%s: cec_clk %u outside range, disabling cec\n",
				__func__, state->pdata.cec_clk);
		state->pdata.cec_clk = 0;
	पूर्ण

	अगर (state->pdata.cec_clk) अणु
		state->i2c_cec = i2c_new_dummy_device(client->adapter,
					       state->i2c_cec_addr >> 1);
		अगर (IS_ERR(state->i2c_cec)) अणु
			v4l2_err(sd, "failed to register cec i2c client\n");
			err = PTR_ERR(state->i2c_cec);
			जाओ err_unreg_edid;
		पूर्ण
		adv7511_wr(sd, 0xe2, 0x00); /* घातer up cec section */
	पूर्ण अन्यथा अणु
		adv7511_wr(sd, 0xe2, 0x01); /* घातer करोwn cec section */
	पूर्ण

	state->i2c_pkपंचांगem = i2c_new_dummy_device(client->adapter, state->i2c_pkपंचांगem_addr >> 1);
	अगर (IS_ERR(state->i2c_pkपंचांगem)) अणु
		v4l2_err(sd, "failed to register pktmem i2c client\n");
		err = PTR_ERR(state->i2c_pkपंचांगem);
		जाओ err_unreg_cec;
	पूर्ण

	state->work_queue = create_singlethपढ़ो_workqueue(sd->name);
	अगर (state->work_queue == शून्य) अणु
		v4l2_err(sd, "could not create workqueue\n");
		err = -ENOMEM;
		जाओ err_unreg_pkपंचांगem;
	पूर्ण

	INIT_DELAYED_WORK(&state->edid_handler, adv7511_edid_handler);

	adv7511_init_setup(sd);

#अगर IS_ENABLED(CONFIG_VIDEO_ADV7511_CEC)
	state->cec_adap = cec_allocate_adapter(&adv7511_cec_adap_ops,
		state, dev_name(&client->dev), CEC_CAP_DEFAULTS,
		ADV7511_MAX_ADDRS);
	err = PTR_ERR_OR_ZERO(state->cec_adap);
	अगर (err) अणु
		destroy_workqueue(state->work_queue);
		जाओ err_unreg_pkपंचांगem;
	पूर्ण
#पूर्ण_अगर

	adv7511_set_isr(sd, true);
	adv7511_check_monitor_present_status(sd);

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
			  client->addr << 1, client->adapter->name);
	वापस 0;

err_unreg_pkपंचांगem:
	i2c_unरेजिस्टर_device(state->i2c_pkपंचांगem);
err_unreg_cec:
	i2c_unरेजिस्टर_device(state->i2c_cec);
err_unreg_edid:
	i2c_unरेजिस्टर_device(state->i2c_edid);
err_entity:
	media_entity_cleanup(&sd->entity);
err_hdl:
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस err;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv7511_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा adv7511_state *state = get_adv7511_state(sd);

	state->chip_revision = -1;

	v4l2_dbg(1, debug, sd, "%s removed @ 0x%x (%s)\n", client->name,
		 client->addr << 1, client->adapter->name);

	adv7511_set_isr(sd, false);
	adv7511_init_setup(sd);
	cancel_delayed_work_sync(&state->edid_handler);
	i2c_unरेजिस्टर_device(state->i2c_edid);
	i2c_unरेजिस्टर_device(state->i2c_cec);
	i2c_unरेजिस्टर_device(state->i2c_pkपंचांगem);
	destroy_workqueue(state->work_queue);
	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id adv7511_id[] = अणु
	अणु "adv7511-v4l2", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv7511_id);

अटल काष्ठा i2c_driver adv7511_driver = अणु
	.driver = अणु
		.name = "adv7511-v4l2",
	पूर्ण,
	.probe = adv7511_probe,
	.हटाओ = adv7511_हटाओ,
	.id_table = adv7511_id,
पूर्ण;

module_i2c_driver(adv7511_driver);
