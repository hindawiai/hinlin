<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * adv7180.c Analog Devices ADV7180 video decoder driver
 * Copyright (c) 2009 Intel Corporation
 * Copyright (C) 2013 Cogent Embedded, Inc.
 * Copyright (C) 2013 Renesas Solutions Corp.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>

#घोषणा ADV7180_STD_AD_PAL_BG_NTSC_J_SECAM		0x0
#घोषणा ADV7180_STD_AD_PAL_BG_NTSC_J_SECAM_PED		0x1
#घोषणा ADV7180_STD_AD_PAL_N_NTSC_J_SECAM		0x2
#घोषणा ADV7180_STD_AD_PAL_N_NTSC_M_SECAM		0x3
#घोषणा ADV7180_STD_NTSC_J				0x4
#घोषणा ADV7180_STD_NTSC_M				0x5
#घोषणा ADV7180_STD_PAL60				0x6
#घोषणा ADV7180_STD_NTSC_443				0x7
#घोषणा ADV7180_STD_PAL_BG				0x8
#घोषणा ADV7180_STD_PAL_N				0x9
#घोषणा ADV7180_STD_PAL_M				0xa
#घोषणा ADV7180_STD_PAL_M_PED				0xb
#घोषणा ADV7180_STD_PAL_COMB_N				0xc
#घोषणा ADV7180_STD_PAL_COMB_N_PED			0xd
#घोषणा ADV7180_STD_PAL_SECAM				0xe
#घोषणा ADV7180_STD_PAL_SECAM_PED			0xf

#घोषणा ADV7180_REG_INPUT_CONTROL			0x0000
#घोषणा ADV7180_INPUT_CONTROL_INSEL_MASK		0x0f

#घोषणा ADV7182_REG_INPUT_VIDSEL			0x0002

#घोषणा ADV7180_REG_OUTPUT_CONTROL			0x0003
#घोषणा ADV7180_REG_EXTENDED_OUTPUT_CONTROL		0x0004
#घोषणा ADV7180_EXTENDED_OUTPUT_CONTROL_NTSCDIS		0xC5

#घोषणा ADV7180_REG_AUTODETECT_ENABLE			0x0007
#घोषणा ADV7180_AUTODETECT_DEFAULT			0x7f
/* Contrast */
#घोषणा ADV7180_REG_CON		0x0008	/*Unचिन्हित */
#घोषणा ADV7180_CON_MIN		0
#घोषणा ADV7180_CON_DEF		128
#घोषणा ADV7180_CON_MAX		255
/* Brightness*/
#घोषणा ADV7180_REG_BRI		0x000a	/*Signed */
#घोषणा ADV7180_BRI_MIN		-128
#घोषणा ADV7180_BRI_DEF		0
#घोषणा ADV7180_BRI_MAX		127
/* Hue */
#घोषणा ADV7180_REG_HUE		0x000b	/*Signed, inverted */
#घोषणा ADV7180_HUE_MIN		-127
#घोषणा ADV7180_HUE_DEF		0
#घोषणा ADV7180_HUE_MAX		128

#घोषणा ADV7180_REG_CTRL		0x000e
#घोषणा ADV7180_CTRL_IRQ_SPACE		0x20

#घोषणा ADV7180_REG_PWR_MAN		0x0f
#घोषणा ADV7180_PWR_MAN_ON		0x04
#घोषणा ADV7180_PWR_MAN_OFF		0x24
#घोषणा ADV7180_PWR_MAN_RES		0x80

#घोषणा ADV7180_REG_STATUS1		0x0010
#घोषणा ADV7180_STATUS1_IN_LOCK		0x01
#घोषणा ADV7180_STATUS1_AUTOD_MASK	0x70
#घोषणा ADV7180_STATUS1_AUTOD_NTSM_M_J	0x00
#घोषणा ADV7180_STATUS1_AUTOD_NTSC_4_43 0x10
#घोषणा ADV7180_STATUS1_AUTOD_PAL_M	0x20
#घोषणा ADV7180_STATUS1_AUTOD_PAL_60	0x30
#घोषणा ADV7180_STATUS1_AUTOD_PAL_B_G	0x40
#घोषणा ADV7180_STATUS1_AUTOD_SECAM	0x50
#घोषणा ADV7180_STATUS1_AUTOD_PAL_COMB	0x60
#घोषणा ADV7180_STATUS1_AUTOD_SECAM_525	0x70

#घोषणा ADV7180_REG_IDENT 0x0011
#घोषणा ADV7180_ID_7180 0x18

#घोषणा ADV7180_REG_STATUS3		0x0013
#घोषणा ADV7180_REG_ANALOG_CLAMP_CTL	0x0014
#घोषणा ADV7180_REG_SHAP_FILTER_CTL_1	0x0017
#घोषणा ADV7180_REG_CTRL_2		0x001d
#घोषणा ADV7180_REG_VSYNC_FIELD_CTL_1	0x0031
#घोषणा ADV7180_REG_MANUAL_WIN_CTL_1	0x003d
#घोषणा ADV7180_REG_MANUAL_WIN_CTL_2	0x003e
#घोषणा ADV7180_REG_MANUAL_WIN_CTL_3	0x003f
#घोषणा ADV7180_REG_LOCK_CNT		0x0051
#घोषणा ADV7180_REG_CVBS_TRIM		0x0052
#घोषणा ADV7180_REG_CLAMP_ADJ		0x005a
#घोषणा ADV7180_REG_RES_CIR		0x005f
#घोषणा ADV7180_REG_DIFF_MODE		0x0060

#घोषणा ADV7180_REG_ICONF1		0x2040
#घोषणा ADV7180_ICONF1_ACTIVE_LOW	0x01
#घोषणा ADV7180_ICONF1_PSYNC_ONLY	0x10
#घोषणा ADV7180_ICONF1_ACTIVE_TO_CLR	0xC0
/* Saturation */
#घोषणा ADV7180_REG_SD_SAT_CB	0x00e3	/*Unचिन्हित */
#घोषणा ADV7180_REG_SD_SAT_CR	0x00e4	/*Unचिन्हित */
#घोषणा ADV7180_SAT_MIN		0
#घोषणा ADV7180_SAT_DEF		128
#घोषणा ADV7180_SAT_MAX		255

#घोषणा ADV7180_IRQ1_LOCK	0x01
#घोषणा ADV7180_IRQ1_UNLOCK	0x02
#घोषणा ADV7180_REG_ISR1	0x2042
#घोषणा ADV7180_REG_ICR1	0x2043
#घोषणा ADV7180_REG_IMR1	0x2044
#घोषणा ADV7180_REG_IMR2	0x2048
#घोषणा ADV7180_IRQ3_AD_CHANGE	0x08
#घोषणा ADV7180_REG_ISR3	0x204A
#घोषणा ADV7180_REG_ICR3	0x204B
#घोषणा ADV7180_REG_IMR3	0x204C
#घोषणा ADV7180_REG_IMR4	0x2050

#घोषणा ADV7180_REG_NTSC_V_BIT_END	0x00E6
#घोषणा ADV7180_NTSC_V_BIT_END_MANUAL_NVEND	0x4F

#घोषणा ADV7180_REG_VPP_SLAVE_ADDR	0xFD
#घोषणा ADV7180_REG_CSI_SLAVE_ADDR	0xFE

#घोषणा ADV7180_REG_ACE_CTRL1		0x4080
#घोषणा ADV7180_REG_ACE_CTRL5		0x4084
#घोषणा ADV7180_REG_FLCONTROL		0x40e0
#घोषणा ADV7180_FLCONTROL_FL_ENABLE 0x1

#घोषणा ADV7180_REG_RST_CLAMP	0x809c
#घोषणा ADV7180_REG_AGC_ADJ1	0x80b6
#घोषणा ADV7180_REG_AGC_ADJ2	0x80c0

#घोषणा ADV7180_CSI_REG_PWRDN	0x00
#घोषणा ADV7180_CSI_PWRDN	0x80

#घोषणा ADV7180_INPUT_CVBS_AIN1 0x00
#घोषणा ADV7180_INPUT_CVBS_AIN2 0x01
#घोषणा ADV7180_INPUT_CVBS_AIN3 0x02
#घोषणा ADV7180_INPUT_CVBS_AIN4 0x03
#घोषणा ADV7180_INPUT_CVBS_AIN5 0x04
#घोषणा ADV7180_INPUT_CVBS_AIN6 0x05
#घोषणा ADV7180_INPUT_SVIDEO_AIN1_AIN2 0x06
#घोषणा ADV7180_INPUT_SVIDEO_AIN3_AIN4 0x07
#घोषणा ADV7180_INPUT_SVIDEO_AIN5_AIN6 0x08
#घोषणा ADV7180_INPUT_YPRPB_AIN1_AIN2_AIN3 0x09
#घोषणा ADV7180_INPUT_YPRPB_AIN4_AIN5_AIN6 0x0a

#घोषणा ADV7182_INPUT_CVBS_AIN1 0x00
#घोषणा ADV7182_INPUT_CVBS_AIN2 0x01
#घोषणा ADV7182_INPUT_CVBS_AIN3 0x02
#घोषणा ADV7182_INPUT_CVBS_AIN4 0x03
#घोषणा ADV7182_INPUT_CVBS_AIN5 0x04
#घोषणा ADV7182_INPUT_CVBS_AIN6 0x05
#घोषणा ADV7182_INPUT_CVBS_AIN7 0x06
#घोषणा ADV7182_INPUT_CVBS_AIN8 0x07
#घोषणा ADV7182_INPUT_SVIDEO_AIN1_AIN2 0x08
#घोषणा ADV7182_INPUT_SVIDEO_AIN3_AIN4 0x09
#घोषणा ADV7182_INPUT_SVIDEO_AIN5_AIN6 0x0a
#घोषणा ADV7182_INPUT_SVIDEO_AIN7_AIN8 0x0b
#घोषणा ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3 0x0c
#घोषणा ADV7182_INPUT_YPRPB_AIN4_AIN5_AIN6 0x0d
#घोषणा ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2 0x0e
#घोषणा ADV7182_INPUT_DIFF_CVBS_AIN3_AIN4 0x0f
#घोषणा ADV7182_INPUT_DIFF_CVBS_AIN5_AIN6 0x10
#घोषणा ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8 0x11

#घोषणा ADV7180_DEFAULT_CSI_I2C_ADDR 0x44
#घोषणा ADV7180_DEFAULT_VPP_I2C_ADDR 0x42

#घोषणा V4L2_CID_ADV_FAST_SWITCH	(V4L2_CID_USER_ADV7180_BASE + 0x00)

/* Initial number of frames to skip to aव्योम possible garbage */
#घोषणा ADV7180_NUM_OF_SKIP_FRAMES       2

काष्ठा adv7180_state;

#घोषणा ADV7180_FLAG_RESET_POWERED	BIT(0)
#घोषणा ADV7180_FLAG_V2			BIT(1)
#घोषणा ADV7180_FLAG_MIPI_CSI2		BIT(2)
#घोषणा ADV7180_FLAG_I2P		BIT(3)

काष्ठा adv7180_chip_info अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक valid_input_mask;
	पूर्णांक (*set_std)(काष्ठा adv7180_state *st, अचिन्हित पूर्णांक std);
	पूर्णांक (*select_input)(काष्ठा adv7180_state *st, अचिन्हित पूर्णांक input);
	पूर्णांक (*init)(काष्ठा adv7180_state *state);
पूर्ण;

काष्ठा adv7180_state अणु
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा v4l2_subdev	sd;
	काष्ठा media_pad	pad;
	काष्ठा mutex		mutex; /* mutual excl. when accessing chip */
	पूर्णांक			irq;
	काष्ठा gpio_desc	*pwdn_gpio;
	v4l2_std_id		curr_norm;
	bool			घातered;
	bool			streaming;
	u8			input;

	काष्ठा i2c_client	*client;
	अचिन्हित पूर्णांक		रेजिस्टर_page;
	काष्ठा i2c_client	*csi_client;
	काष्ठा i2c_client	*vpp_client;
	स्थिर काष्ठा adv7180_chip_info *chip_info;
	क्रमागत v4l2_field		field;
पूर्ण;
#घोषणा to_adv7180_sd(_ctrl) (&container_of(_ctrl->handler,		\
					    काष्ठा adv7180_state,	\
					    ctrl_hdl)->sd)

अटल पूर्णांक adv7180_select_page(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक page)
अणु
	अगर (state->रेजिस्टर_page != page) अणु
		i2c_smbus_ग_लिखो_byte_data(state->client, ADV7180_REG_CTRL,
			page);
		state->रेजिस्टर_page = page;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_ग_लिखो(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक value)
अणु
	lockdep_निश्चित_held(&state->mutex);
	adv7180_select_page(state, reg >> 8);
	वापस i2c_smbus_ग_लिखो_byte_data(state->client, reg & 0xff, value);
पूर्ण

अटल पूर्णांक adv7180_पढ़ो(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक reg)
अणु
	lockdep_निश्चित_held(&state->mutex);
	adv7180_select_page(state, reg >> 8);
	वापस i2c_smbus_पढ़ो_byte_data(state->client, reg & 0xff);
पूर्ण

अटल पूर्णांक adv7180_csi_ग_लिखो(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(state->csi_client, reg, value);
पूर्ण

अटल पूर्णांक adv7180_set_video_standard(काष्ठा adv7180_state *state,
	अचिन्हित पूर्णांक std)
अणु
	वापस state->chip_info->set_std(state, std);
पूर्ण

अटल पूर्णांक adv7180_vpp_ग_लिखो(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(state->vpp_client, reg, value);
पूर्ण

अटल v4l2_std_id adv7180_std_to_v4l2(u8 status1)
अणु
	/* in हाल V4L2_IN_ST_NO_SIGNAL */
	अगर (!(status1 & ADV7180_STATUS1_IN_LOCK))
		वापस V4L2_STD_UNKNOWN;

	चयन (status1 & ADV7180_STATUS1_AUTOD_MASK) अणु
	हाल ADV7180_STATUS1_AUTOD_NTSM_M_J:
		वापस V4L2_STD_NTSC;
	हाल ADV7180_STATUS1_AUTOD_NTSC_4_43:
		वापस V4L2_STD_NTSC_443;
	हाल ADV7180_STATUS1_AUTOD_PAL_M:
		वापस V4L2_STD_PAL_M;
	हाल ADV7180_STATUS1_AUTOD_PAL_60:
		वापस V4L2_STD_PAL_60;
	हाल ADV7180_STATUS1_AUTOD_PAL_B_G:
		वापस V4L2_STD_PAL;
	हाल ADV7180_STATUS1_AUTOD_SECAM:
		वापस V4L2_STD_SECAM;
	हाल ADV7180_STATUS1_AUTOD_PAL_COMB:
		वापस V4L2_STD_PAL_Nc | V4L2_STD_PAL_N;
	हाल ADV7180_STATUS1_AUTOD_SECAM_525:
		वापस V4L2_STD_SECAM;
	शेष:
		वापस V4L2_STD_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक v4l2_std_to_adv7180(v4l2_std_id std)
अणु
	अगर (std == V4L2_STD_PAL_60)
		वापस ADV7180_STD_PAL60;
	अगर (std == V4L2_STD_NTSC_443)
		वापस ADV7180_STD_NTSC_443;
	अगर (std == V4L2_STD_PAL_N)
		वापस ADV7180_STD_PAL_N;
	अगर (std == V4L2_STD_PAL_M)
		वापस ADV7180_STD_PAL_M;
	अगर (std == V4L2_STD_PAL_Nc)
		वापस ADV7180_STD_PAL_COMB_N;

	अगर (std & V4L2_STD_PAL)
		वापस ADV7180_STD_PAL_BG;
	अगर (std & V4L2_STD_NTSC)
		वापस ADV7180_STD_NTSC_M;
	अगर (std & V4L2_STD_SECAM)
		वापस ADV7180_STD_PAL_SECAM;

	वापस -EINVAL;
पूर्ण

अटल u32 adv7180_status_to_v4l2(u8 status1)
अणु
	अगर (!(status1 & ADV7180_STATUS1_IN_LOCK))
		वापस V4L2_IN_ST_NO_SIGNAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __adv7180_status(काष्ठा adv7180_state *state, u32 *status,
			    v4l2_std_id *std)
अणु
	पूर्णांक status1 = adv7180_पढ़ो(state, ADV7180_REG_STATUS1);

	अगर (status1 < 0)
		वापस status1;

	अगर (status)
		*status = adv7180_status_to_v4l2(status1);
	अगर (std)
		*std = adv7180_std_to_v4l2(status1);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा adv7180_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv7180_state, sd);
पूर्ण

अटल पूर्णांक adv7180_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक err = mutex_lock_पूर्णांकerruptible(&state->mutex);
	अगर (err)
		वापस err;

	अगर (state->streaming) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	err = adv7180_set_video_standard(state,
			ADV7180_STD_AD_PAL_BG_NTSC_J_SECAM);
	अगर (err)
		जाओ unlock;

	msleep(100);
	__adv7180_status(state, शून्य, std);

	err = v4l2_std_to_adv7180(state->curr_norm);
	अगर (err < 0)
		जाओ unlock;

	err = adv7180_set_video_standard(state, err);

unlock:
	mutex_unlock(&state->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक adv7180_s_routing(काष्ठा v4l2_subdev *sd, u32 input,
			     u32 output, u32 config)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret = mutex_lock_पूर्णांकerruptible(&state->mutex);

	अगर (ret)
		वापस ret;

	अगर (input > 31 || !(BIT(input) & state->chip_info->valid_input_mask)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = state->chip_info->select_input(state, input);

	अगर (ret == 0)
		state->input = input;
out:
	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret = mutex_lock_पूर्णांकerruptible(&state->mutex);
	अगर (ret)
		वापस ret;

	ret = __adv7180_status(state, status, शून्य);
	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_program_std(काष्ठा adv7180_state *state)
अणु
	पूर्णांक ret;

	ret = v4l2_std_to_adv7180(state->curr_norm);
	अगर (ret < 0)
		वापस ret;

	ret = adv7180_set_video_standard(state, ret);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret = mutex_lock_पूर्णांकerruptible(&state->mutex);

	अगर (ret)
		वापस ret;

	/* Make sure we can support this std */
	ret = v4l2_std_to_adv7180(std);
	अगर (ret < 0)
		जाओ out;

	state->curr_norm = std;

	ret = adv7180_program_std(state);
out:
	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	काष्ठा adv7180_state *state = to_state(sd);

	*norm = state->curr_norm;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा adv7180_state *state = to_state(sd);

	अगर (state->curr_norm & V4L2_STD_525_60) अणु
		fi->पूर्णांकerval.numerator = 1001;
		fi->पूर्णांकerval.denominator = 30000;
	पूर्ण अन्यथा अणु
		fi->पूर्णांकerval.numerator = 1;
		fi->पूर्णांकerval.denominator = 25;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adv7180_set_घातer_pin(काष्ठा adv7180_state *state, bool on)
अणु
	अगर (!state->pwdn_gpio)
		वापस;

	अगर (on) अणु
		gpiod_set_value_cansleep(state->pwdn_gpio, 0);
		usleep_range(5000, 10000);
	पूर्ण अन्यथा अणु
		gpiod_set_value_cansleep(state->pwdn_gpio, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक adv7180_set_घातer(काष्ठा adv7180_state *state, bool on)
अणु
	u8 val;
	पूर्णांक ret;

	अगर (on)
		val = ADV7180_PWR_MAN_ON;
	अन्यथा
		val = ADV7180_PWR_MAN_OFF;

	ret = adv7180_ग_लिखो(state, ADV7180_REG_PWR_MAN, val);
	अगर (ret)
		वापस ret;

	अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) अणु
		अगर (on) अणु
			adv7180_csi_ग_लिखो(state, 0xDE, 0x02);
			adv7180_csi_ग_लिखो(state, 0xD2, 0xF7);
			adv7180_csi_ग_लिखो(state, 0xD8, 0x65);
			adv7180_csi_ग_लिखो(state, 0xE0, 0x09);
			adv7180_csi_ग_लिखो(state, 0x2C, 0x00);
			अगर (state->field == V4L2_FIELD_NONE)
				adv7180_csi_ग_लिखो(state, 0x1D, 0x80);
			adv7180_csi_ग_लिखो(state, 0x00, 0x00);
		पूर्ण अन्यथा अणु
			adv7180_csi_ग_लिखो(state, 0x00, 0x80);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&state->mutex);
	अगर (ret)
		वापस ret;

	ret = adv7180_set_घातer(state, on);
	अगर (ret == 0)
		state->घातered = on;

	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_adv7180_sd(ctrl);
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret = mutex_lock_पूर्णांकerruptible(&state->mutex);
	पूर्णांक val;

	अगर (ret)
		वापस ret;
	val = ctrl->val;
	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ret = adv7180_ग_लिखो(state, ADV7180_REG_BRI, val);
		अवरोध;
	हाल V4L2_CID_HUE:
		/*Hue is inverted according to HSL अक्षरt */
		ret = adv7180_ग_लिखो(state, ADV7180_REG_HUE, -val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = adv7180_ग_लिखो(state, ADV7180_REG_CON, val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		/*
		 *This could be V4L2_CID_BLUE_BALANCE/V4L2_CID_RED_BALANCE
		 *Let's not confuse the user, everybody understands saturation
		 */
		ret = adv7180_ग_लिखो(state, ADV7180_REG_SD_SAT_CB, val);
		अगर (ret < 0)
			अवरोध;
		ret = adv7180_ग_लिखो(state, ADV7180_REG_SD_SAT_CR, val);
		अवरोध;
	हाल V4L2_CID_ADV_FAST_SWITCH:
		अगर (ctrl->val) अणु
			/* ADI required ग_लिखो */
			adv7180_ग_लिखो(state, 0x80d9, 0x44);
			adv7180_ग_लिखो(state, ADV7180_REG_FLCONTROL,
				ADV7180_FLCONTROL_FL_ENABLE);
		पूर्ण अन्यथा अणु
			/* ADI required ग_लिखो */
			adv7180_ग_लिखो(state, 0x80d9, 0xc4);
			adv7180_ग_लिखो(state, ADV7180_REG_FLCONTROL, 0x00);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&state->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adv7180_ctrl_ops = अणु
	.s_ctrl = adv7180_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config adv7180_ctrl_fast_चयन = अणु
	.ops = &adv7180_ctrl_ops,
	.id = V4L2_CID_ADV_FAST_SWITCH,
	.name = "Fast Switching",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
पूर्ण;

अटल पूर्णांक adv7180_init_controls(काष्ठा adv7180_state *state)
अणु
	v4l2_ctrl_handler_init(&state->ctrl_hdl, 4);

	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, ADV7180_BRI_MIN,
			  ADV7180_BRI_MAX, 1, ADV7180_BRI_DEF);
	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_CONTRAST, ADV7180_CON_MIN,
			  ADV7180_CON_MAX, 1, ADV7180_CON_DEF);
	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_SATURATION, ADV7180_SAT_MIN,
			  ADV7180_SAT_MAX, 1, ADV7180_SAT_DEF);
	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_HUE, ADV7180_HUE_MIN,
			  ADV7180_HUE_MAX, 1, ADV7180_HUE_DEF);
	v4l2_ctrl_new_custom(&state->ctrl_hdl, &adv7180_ctrl_fast_चयन, शून्य);

	state->sd.ctrl_handler = &state->ctrl_hdl;
	अगर (state->ctrl_hdl.error) अणु
		पूर्णांक err = state->ctrl_hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->ctrl_hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_handler_setup(&state->ctrl_hdl);

	वापस 0;
पूर्ण
अटल व्योम adv7180_निकास_controls(काष्ठा adv7180_state *state)
अणु
	v4l2_ctrl_handler_मुक्त(&state->ctrl_hdl);
पूर्ण

अटल पूर्णांक adv7180_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index != 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_mbus_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा adv7180_state *state = to_state(sd);

	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	fmt->width = 720;
	fmt->height = state->curr_norm & V4L2_STD_525_60 ? 480 : 576;

	अगर (state->field == V4L2_FIELD_ALTERNATE)
		fmt->height /= 2;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_set_field_mode(काष्ठा adv7180_state *state)
अणु
	अगर (!(state->chip_info->flags & ADV7180_FLAG_I2P))
		वापस 0;

	अगर (state->field == V4L2_FIELD_NONE) अणु
		अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) अणु
			adv7180_csi_ग_लिखो(state, 0x01, 0x20);
			adv7180_csi_ग_लिखो(state, 0x02, 0x28);
			adv7180_csi_ग_लिखो(state, 0x03, 0x38);
			adv7180_csi_ग_लिखो(state, 0x04, 0x30);
			adv7180_csi_ग_लिखो(state, 0x05, 0x30);
			adv7180_csi_ग_लिखो(state, 0x06, 0x80);
			adv7180_csi_ग_लिखो(state, 0x07, 0x70);
			adv7180_csi_ग_लिखो(state, 0x08, 0x50);
		पूर्ण
		adv7180_vpp_ग_लिखो(state, 0xa3, 0x00);
		adv7180_vpp_ग_लिखो(state, 0x5b, 0x00);
		adv7180_vpp_ग_लिखो(state, 0x55, 0x80);
	पूर्ण अन्यथा अणु
		अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) अणु
			adv7180_csi_ग_लिखो(state, 0x01, 0x18);
			adv7180_csi_ग_लिखो(state, 0x02, 0x18);
			adv7180_csi_ग_लिखो(state, 0x03, 0x30);
			adv7180_csi_ग_लिखो(state, 0x04, 0x20);
			adv7180_csi_ग_लिखो(state, 0x05, 0x28);
			adv7180_csi_ग_लिखो(state, 0x06, 0x40);
			adv7180_csi_ग_लिखो(state, 0x07, 0x58);
			adv7180_csi_ग_लिखो(state, 0x08, 0x30);
		पूर्ण
		adv7180_vpp_ग_लिखो(state, 0xa3, 0x70);
		adv7180_vpp_ग_लिखो(state, 0x5b, 0x80);
		adv7180_vpp_ग_लिखो(state, 0x55, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7180_state *state = to_state(sd);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		क्रमmat->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	पूर्ण अन्यथा अणु
		adv7180_mbus_fmt(sd, &क्रमmat->क्रमmat);
		क्रमmat->क्रमmat.field = state->field;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	काष्ठा v4l2_mbus_framefmt *framefmt;
	पूर्णांक ret;

	चयन (क्रमmat->क्रमmat.field) अणु
	हाल V4L2_FIELD_NONE:
		अगर (state->chip_info->flags & ADV7180_FLAG_I2P)
			अवरोध;
		fallthrough;
	शेष:
		क्रमmat->क्रमmat.field = V4L2_FIELD_ALTERNATE;
		अवरोध;
	पूर्ण

	ret = adv7180_mbus_fmt(sd,  &क्रमmat->क्रमmat);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		अगर (state->field != क्रमmat->क्रमmat.field) अणु
			state->field = क्रमmat->क्रमmat.field;
			adv7180_set_घातer(state, false);
			adv7180_set_field_mode(state);
			adv7180_set_घातer(state, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		*framefmt = क्रमmat->क्रमmat;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_init_cfg(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = cfg ? V4L2_SUBDEV_FORMAT_TRY
			: V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	वापस adv7180_set_pad_क्रमmat(sd, cfg, &fmt);
पूर्ण

अटल पूर्णांक adv7180_get_mbus_config(काष्ठा v4l2_subdev *sd,
				   अचिन्हित पूर्णांक pad,
				   काष्ठा v4l2_mbus_config *cfg)
अणु
	काष्ठा adv7180_state *state = to_state(sd);

	अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) अणु
		cfg->type = V4L2_MBUS_CSI2_DPHY;
		cfg->flags = V4L2_MBUS_CSI2_1_LANE |
				V4L2_MBUS_CSI2_CHANNEL_0 |
				V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	पूर्ण अन्यथा अणु
		/*
		 * The ADV7180 sensor supports BT.601/656 output modes.
		 * The BT.656 is शेष and not yet configurable by s/w.
		 */
		cfg->flags = V4L2_MBUS_MASTER | V4L2_MBUS_PCLK_SAMPLE_RISING |
				 V4L2_MBUS_DATA_ACTIVE_HIGH;
		cfg->type = V4L2_MBUS_BT656;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_get_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	*frames = ADV7180_NUM_OF_SKIP_FRAMES;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_g_pixelaspect(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fract *aspect)
अणु
	काष्ठा adv7180_state *state = to_state(sd);

	अगर (state->curr_norm & V4L2_STD_525_60) अणु
		aspect->numerator = 11;
		aspect->denominator = 10;
	पूर्ण अन्यथा अणु
		aspect->numerator = 54;
		aspect->denominator = 59;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_g_tvnorms(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	*norm = V4L2_STD_ALL;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret;

	/* It's always safe to stop streaming, no need to take the lock */
	अगर (!enable) अणु
		state->streaming = enable;
		वापस 0;
	पूर्ण

	/* Must रुको until querystd released the lock */
	ret = mutex_lock_पूर्णांकerruptible(&state->mutex);
	अगर (ret)
		वापस ret;
	state->streaming = enable;
	mutex_unlock(&state->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7180_subscribe_event(काष्ठा v4l2_subdev *sd,
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

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv7180_video_ops = अणु
	.s_std = adv7180_s_std,
	.g_std = adv7180_g_std,
	.g_frame_पूर्णांकerval = adv7180_g_frame_पूर्णांकerval,
	.querystd = adv7180_querystd,
	.g_input_status = adv7180_g_input_status,
	.s_routing = adv7180_s_routing,
	.g_pixelaspect = adv7180_g_pixelaspect,
	.g_tvnorms = adv7180_g_tvnorms,
	.s_stream = adv7180_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv7180_core_ops = अणु
	.s_घातer = adv7180_s_घातer,
	.subscribe_event = adv7180_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv7180_pad_ops = अणु
	.init_cfg = adv7180_init_cfg,
	.क्रमागत_mbus_code = adv7180_क्रमागत_mbus_code,
	.set_fmt = adv7180_set_pad_क्रमmat,
	.get_fmt = adv7180_get_pad_क्रमmat,
	.get_mbus_config = adv7180_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops adv7180_sensor_ops = अणु
	.g_skip_frames = adv7180_get_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adv7180_ops = अणु
	.core = &adv7180_core_ops,
	.video = &adv7180_video_ops,
	.pad = &adv7180_pad_ops,
	.sensor = &adv7180_sensor_ops,
पूर्ण;

अटल irqवापस_t adv7180_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा adv7180_state *state = devid;
	u8 isr3;

	mutex_lock(&state->mutex);
	isr3 = adv7180_पढ़ो(state, ADV7180_REG_ISR3);
	/* clear */
	adv7180_ग_लिखो(state, ADV7180_REG_ICR3, isr3);

	अगर (isr3 & ADV7180_IRQ3_AD_CHANGE) अणु
		अटल स्थिर काष्ठा v4l2_event src_ch = अणु
			.type = V4L2_EVENT_SOURCE_CHANGE,
			.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
		पूर्ण;

		v4l2_subdev_notअगरy_event(&state->sd, &src_ch);
	पूर्ण
	mutex_unlock(&state->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adv7180_init(काष्ठा adv7180_state *state)
अणु
	पूर्णांक ret;

	/* ITU-R BT.656-4 compatible */
	ret = adv7180_ग_लिखो(state, ADV7180_REG_EXTENDED_OUTPUT_CONTROL,
			ADV7180_EXTENDED_OUTPUT_CONTROL_NTSCDIS);
	अगर (ret < 0)
		वापस ret;

	/* Manually set V bit end position in NTSC mode */
	वापस adv7180_ग_लिखो(state, ADV7180_REG_NTSC_V_BIT_END,
					ADV7180_NTSC_V_BIT_END_MANUAL_NVEND);
पूर्ण

अटल पूर्णांक adv7180_set_std(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक std)
अणु
	वापस adv7180_ग_लिखो(state, ADV7180_REG_INPUT_CONTROL,
		(std << 4) | state->input);
पूर्ण

अटल पूर्णांक adv7180_select_input(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक input)
अणु
	पूर्णांक ret;

	ret = adv7180_पढ़ो(state, ADV7180_REG_INPUT_CONTROL);
	अगर (ret < 0)
		वापस ret;

	ret &= ~ADV7180_INPUT_CONTROL_INSEL_MASK;
	ret |= input;
	वापस adv7180_ग_लिखो(state, ADV7180_REG_INPUT_CONTROL, ret);
पूर्ण

अटल पूर्णांक adv7182_init(काष्ठा adv7180_state *state)
अणु
	अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2)
		adv7180_ग_लिखो(state, ADV7180_REG_CSI_SLAVE_ADDR,
			ADV7180_DEFAULT_CSI_I2C_ADDR << 1);

	अगर (state->chip_info->flags & ADV7180_FLAG_I2P)
		adv7180_ग_लिखो(state, ADV7180_REG_VPP_SLAVE_ADDR,
			ADV7180_DEFAULT_VPP_I2C_ADDR << 1);

	अगर (state->chip_info->flags & ADV7180_FLAG_V2) अणु
		/* ADI recommended ग_लिखोs क्रम improved video quality */
		adv7180_ग_लिखो(state, 0x0080, 0x51);
		adv7180_ग_लिखो(state, 0x0081, 0x51);
		adv7180_ग_लिखो(state, 0x0082, 0x68);
	पूर्ण

	/* ADI required ग_लिखोs */
	अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) अणु
		adv7180_ग_लिखो(state, ADV7180_REG_OUTPUT_CONTROL, 0x4e);
		adv7180_ग_लिखो(state, ADV7180_REG_EXTENDED_OUTPUT_CONTROL, 0x57);
		adv7180_ग_लिखो(state, ADV7180_REG_CTRL_2, 0xc0);
	पूर्ण अन्यथा अणु
		अगर (state->chip_info->flags & ADV7180_FLAG_V2)
			adv7180_ग_लिखो(state,
				      ADV7180_REG_EXTENDED_OUTPUT_CONTROL,
				      0x17);
		अन्यथा
			adv7180_ग_लिखो(state,
				      ADV7180_REG_EXTENDED_OUTPUT_CONTROL,
				      0x07);
		adv7180_ग_लिखो(state, ADV7180_REG_OUTPUT_CONTROL, 0x0c);
		adv7180_ग_लिखो(state, ADV7180_REG_CTRL_2, 0x40);
	पूर्ण

	adv7180_ग_लिखो(state, 0x0013, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7182_set_std(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक std)
अणु
	वापस adv7180_ग_लिखो(state, ADV7182_REG_INPUT_VIDSEL, std << 4);
पूर्ण

क्रमागत adv7182_input_type अणु
	ADV7182_INPUT_TYPE_CVBS,
	ADV7182_INPUT_TYPE_DIFF_CVBS,
	ADV7182_INPUT_TYPE_SVIDEO,
	ADV7182_INPUT_TYPE_YPBPR,
पूर्ण;

अटल क्रमागत adv7182_input_type adv7182_get_input_type(अचिन्हित पूर्णांक input)
अणु
	चयन (input) अणु
	हाल ADV7182_INPUT_CVBS_AIN1:
	हाल ADV7182_INPUT_CVBS_AIN2:
	हाल ADV7182_INPUT_CVBS_AIN3:
	हाल ADV7182_INPUT_CVBS_AIN4:
	हाल ADV7182_INPUT_CVBS_AIN5:
	हाल ADV7182_INPUT_CVBS_AIN6:
	हाल ADV7182_INPUT_CVBS_AIN7:
	हाल ADV7182_INPUT_CVBS_AIN8:
		वापस ADV7182_INPUT_TYPE_CVBS;
	हाल ADV7182_INPUT_SVIDEO_AIN1_AIN2:
	हाल ADV7182_INPUT_SVIDEO_AIN3_AIN4:
	हाल ADV7182_INPUT_SVIDEO_AIN5_AIN6:
	हाल ADV7182_INPUT_SVIDEO_AIN7_AIN8:
		वापस ADV7182_INPUT_TYPE_SVIDEO;
	हाल ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3:
	हाल ADV7182_INPUT_YPRPB_AIN4_AIN5_AIN6:
		वापस ADV7182_INPUT_TYPE_YPBPR;
	हाल ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2:
	हाल ADV7182_INPUT_DIFF_CVBS_AIN3_AIN4:
	हाल ADV7182_INPUT_DIFF_CVBS_AIN5_AIN6:
	हाल ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8:
		वापस ADV7182_INPUT_TYPE_DIFF_CVBS;
	शेष: /* Will never happen */
		वापस 0;
	पूर्ण
पूर्ण

/* ADI recommended ग_लिखोs to रेजिस्टरs 0x52, 0x53, 0x54 */
अटल अचिन्हित पूर्णांक adv7182_lbias_settings[][3] = अणु
	[ADV7182_INPUT_TYPE_CVBS] = अणु 0xCB, 0x4E, 0x80 पूर्ण,
	[ADV7182_INPUT_TYPE_DIFF_CVBS] = अणु 0xC0, 0x4E, 0x80 पूर्ण,
	[ADV7182_INPUT_TYPE_SVIDEO] = अणु 0x0B, 0xCE, 0x80 पूर्ण,
	[ADV7182_INPUT_TYPE_YPBPR] = अणु 0x0B, 0x4E, 0xC0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक adv7280_lbias_settings[][3] = अणु
	[ADV7182_INPUT_TYPE_CVBS] = अणु 0xCD, 0x4E, 0x80 पूर्ण,
	[ADV7182_INPUT_TYPE_DIFF_CVBS] = अणु 0xC0, 0x4E, 0x80 पूर्ण,
	[ADV7182_INPUT_TYPE_SVIDEO] = अणु 0x0B, 0xCE, 0x80 पूर्ण,
	[ADV7182_INPUT_TYPE_YPBPR] = अणु 0x0B, 0x4E, 0xC0 पूर्ण,
पूर्ण;

अटल पूर्णांक adv7182_select_input(काष्ठा adv7180_state *state, अचिन्हित पूर्णांक input)
अणु
	क्रमागत adv7182_input_type input_type;
	अचिन्हित पूर्णांक *lbias;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = adv7180_ग_लिखो(state, ADV7180_REG_INPUT_CONTROL, input);
	अगर (ret)
		वापस ret;

	/* Reset clamp circuitry - ADI recommended ग_लिखोs */
	adv7180_ग_लिखो(state, ADV7180_REG_RST_CLAMP, 0x00);
	adv7180_ग_लिखो(state, ADV7180_REG_RST_CLAMP, 0xff);

	input_type = adv7182_get_input_type(input);

	चयन (input_type) अणु
	हाल ADV7182_INPUT_TYPE_CVBS:
	हाल ADV7182_INPUT_TYPE_DIFF_CVBS:
		/* ADI recommends to use the SH1 filter */
		adv7180_ग_लिखो(state, ADV7180_REG_SHAP_FILTER_CTL_1, 0x41);
		अवरोध;
	शेष:
		adv7180_ग_लिखो(state, ADV7180_REG_SHAP_FILTER_CTL_1, 0x01);
		अवरोध;
	पूर्ण

	अगर (state->chip_info->flags & ADV7180_FLAG_V2)
		lbias = adv7280_lbias_settings[input_type];
	अन्यथा
		lbias = adv7182_lbias_settings[input_type];

	क्रम (i = 0; i < ARRAY_SIZE(adv7182_lbias_settings[0]); i++)
		adv7180_ग_लिखो(state, ADV7180_REG_CVBS_TRIM + i, lbias[i]);

	अगर (input_type == ADV7182_INPUT_TYPE_DIFF_CVBS) अणु
		/* ADI required ग_लिखोs to make dअगरferential CVBS work */
		adv7180_ग_लिखो(state, ADV7180_REG_RES_CIR, 0xa8);
		adv7180_ग_लिखो(state, ADV7180_REG_CLAMP_ADJ, 0x90);
		adv7180_ग_लिखो(state, ADV7180_REG_DIFF_MODE, 0xb0);
		adv7180_ग_लिखो(state, ADV7180_REG_AGC_ADJ1, 0x08);
		adv7180_ग_लिखो(state, ADV7180_REG_AGC_ADJ2, 0xa0);
	पूर्ण अन्यथा अणु
		adv7180_ग_लिखो(state, ADV7180_REG_RES_CIR, 0xf0);
		adv7180_ग_लिखो(state, ADV7180_REG_CLAMP_ADJ, 0xd0);
		adv7180_ग_लिखो(state, ADV7180_REG_DIFF_MODE, 0x10);
		adv7180_ग_लिखो(state, ADV7180_REG_AGC_ADJ1, 0x9c);
		adv7180_ग_लिखो(state, ADV7180_REG_AGC_ADJ2, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा adv7180_chip_info adv7180_info = अणु
	.flags = ADV7180_FLAG_RESET_POWERED,
	/* We cannot discriminate between LQFP and 40-pin LFCSP, so accept
	 * all inमाला_दो and let the card driver take care of validation
	 */
	.valid_input_mask = BIT(ADV7180_INPUT_CVBS_AIN1) |
		BIT(ADV7180_INPUT_CVBS_AIN2) |
		BIT(ADV7180_INPUT_CVBS_AIN3) |
		BIT(ADV7180_INPUT_CVBS_AIN4) |
		BIT(ADV7180_INPUT_CVBS_AIN5) |
		BIT(ADV7180_INPUT_CVBS_AIN6) |
		BIT(ADV7180_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7180_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7180_INPUT_SVIDEO_AIN5_AIN6) |
		BIT(ADV7180_INPUT_YPRPB_AIN1_AIN2_AIN3) |
		BIT(ADV7180_INPUT_YPRPB_AIN4_AIN5_AIN6),
	.init = adv7180_init,
	.set_std = adv7180_set_std,
	.select_input = adv7180_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7182_info = अणु
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN3) |
		BIT(ADV7182_INPUT_CVBS_AIN4) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN3_AIN4),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7280_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_I2P,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN3) |
		BIT(ADV7182_INPUT_CVBS_AIN4) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7280_m_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_MIPI_CSI2 | ADV7180_FLAG_I2P,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN3) |
		BIT(ADV7182_INPUT_CVBS_AIN4) |
		BIT(ADV7182_INPUT_CVBS_AIN5) |
		BIT(ADV7182_INPUT_CVBS_AIN6) |
		BIT(ADV7182_INPUT_CVBS_AIN7) |
		BIT(ADV7182_INPUT_CVBS_AIN8) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7182_INPUT_SVIDEO_AIN5_AIN6) |
		BIT(ADV7182_INPUT_SVIDEO_AIN7_AIN8) |
		BIT(ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3) |
		BIT(ADV7182_INPUT_YPRPB_AIN4_AIN5_AIN6),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7281_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_MIPI_CSI2,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN7) |
		BIT(ADV7182_INPUT_CVBS_AIN8) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN7_AIN8) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7281_m_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_MIPI_CSI2,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN3) |
		BIT(ADV7182_INPUT_CVBS_AIN4) |
		BIT(ADV7182_INPUT_CVBS_AIN7) |
		BIT(ADV7182_INPUT_CVBS_AIN8) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7182_INPUT_SVIDEO_AIN7_AIN8) |
		BIT(ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN3_AIN4) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7281_ma_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_MIPI_CSI2,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN3) |
		BIT(ADV7182_INPUT_CVBS_AIN4) |
		BIT(ADV7182_INPUT_CVBS_AIN5) |
		BIT(ADV7182_INPUT_CVBS_AIN6) |
		BIT(ADV7182_INPUT_CVBS_AIN7) |
		BIT(ADV7182_INPUT_CVBS_AIN8) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7182_INPUT_SVIDEO_AIN5_AIN6) |
		BIT(ADV7182_INPUT_SVIDEO_AIN7_AIN8) |
		BIT(ADV7182_INPUT_YPRPB_AIN1_AIN2_AIN3) |
		BIT(ADV7182_INPUT_YPRPB_AIN4_AIN5_AIN6) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN3_AIN4) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN5_AIN6) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7282_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_I2P,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN7) |
		BIT(ADV7182_INPUT_CVBS_AIN8) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN7_AIN8) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल स्थिर काष्ठा adv7180_chip_info adv7282_m_info = अणु
	.flags = ADV7180_FLAG_V2 | ADV7180_FLAG_MIPI_CSI2 | ADV7180_FLAG_I2P,
	.valid_input_mask = BIT(ADV7182_INPUT_CVBS_AIN1) |
		BIT(ADV7182_INPUT_CVBS_AIN2) |
		BIT(ADV7182_INPUT_CVBS_AIN3) |
		BIT(ADV7182_INPUT_CVBS_AIN4) |
		BIT(ADV7182_INPUT_CVBS_AIN7) |
		BIT(ADV7182_INPUT_CVBS_AIN8) |
		BIT(ADV7182_INPUT_SVIDEO_AIN1_AIN2) |
		BIT(ADV7182_INPUT_SVIDEO_AIN3_AIN4) |
		BIT(ADV7182_INPUT_SVIDEO_AIN7_AIN8) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN1_AIN2) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN3_AIN4) |
		BIT(ADV7182_INPUT_DIFF_CVBS_AIN7_AIN8),
	.init = adv7182_init,
	.set_std = adv7182_set_std,
	.select_input = adv7182_select_input,
पूर्ण;

अटल पूर्णांक init_device(काष्ठा adv7180_state *state)
अणु
	पूर्णांक ret;

	mutex_lock(&state->mutex);

	adv7180_set_घातer_pin(state, true);

	adv7180_ग_लिखो(state, ADV7180_REG_PWR_MAN, ADV7180_PWR_MAN_RES);
	usleep_range(5000, 10000);

	ret = state->chip_info->init(state);
	अगर (ret)
		जाओ out_unlock;

	ret = adv7180_program_std(state);
	अगर (ret)
		जाओ out_unlock;

	adv7180_set_field_mode(state);

	/* रेजिस्टर क्रम पूर्णांकerrupts */
	अगर (state->irq > 0) अणु
		/* config the Interrupt pin to be active low */
		ret = adv7180_ग_लिखो(state, ADV7180_REG_ICONF1,
						ADV7180_ICONF1_ACTIVE_LOW |
						ADV7180_ICONF1_PSYNC_ONLY);
		अगर (ret < 0)
			जाओ out_unlock;

		ret = adv7180_ग_लिखो(state, ADV7180_REG_IMR1, 0);
		अगर (ret < 0)
			जाओ out_unlock;

		ret = adv7180_ग_लिखो(state, ADV7180_REG_IMR2, 0);
		अगर (ret < 0)
			जाओ out_unlock;

		/* enable AD change पूर्णांकerrupts पूर्णांकerrupts */
		ret = adv7180_ग_लिखो(state, ADV7180_REG_IMR3,
						ADV7180_IRQ3_AD_CHANGE);
		अगर (ret < 0)
			जाओ out_unlock;

		ret = adv7180_ग_लिखो(state, ADV7180_REG_IMR4, 0);
		अगर (ret < 0)
			जाओ out_unlock;
	पूर्ण

out_unlock:
	mutex_unlock(&state->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adv7180_state *state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;

	state->client = client;
	state->field = V4L2_FIELD_ALTERNATE;
	state->chip_info = (काष्ठा adv7180_chip_info *)id->driver_data;

	state->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(state->pwdn_gpio)) अणु
		ret = PTR_ERR(state->pwdn_gpio);
		v4l_err(client, "request for power pin failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) अणु
		state->csi_client = i2c_new_dummy_device(client->adapter,
				ADV7180_DEFAULT_CSI_I2C_ADDR);
		अगर (IS_ERR(state->csi_client))
			वापस PTR_ERR(state->csi_client);
	पूर्ण

	अगर (state->chip_info->flags & ADV7180_FLAG_I2P) अणु
		state->vpp_client = i2c_new_dummy_device(client->adapter,
				ADV7180_DEFAULT_VPP_I2C_ADDR);
		अगर (IS_ERR(state->vpp_client)) अणु
			ret = PTR_ERR(state->vpp_client);
			जाओ err_unरेजिस्टर_csi_client;
		पूर्ण
	पूर्ण

	state->irq = client->irq;
	mutex_init(&state->mutex);
	state->curr_norm = V4L2_STD_NTSC;
	अगर (state->chip_info->flags & ADV7180_FLAG_RESET_POWERED)
		state->घातered = true;
	अन्यथा
		state->घातered = false;
	state->input = 0;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &adv7180_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;

	ret = adv7180_init_controls(state);
	अगर (ret)
		जाओ err_unरेजिस्टर_vpp_client;

	state->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;
	ret = media_entity_pads_init(&sd->entity, 1, &state->pad);
	अगर (ret)
		जाओ err_मुक्त_ctrl;

	ret = init_device(state);
	अगर (ret)
		जाओ err_media_entity_cleanup;

	अगर (state->irq) अणु
		ret = request_thपढ़ोed_irq(client->irq, शून्य, adv7180_irq,
					   IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
					   KBUILD_MODNAME, state);
		अगर (ret)
			जाओ err_media_entity_cleanup;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret)
		जाओ err_मुक्त_irq;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
		 client->addr, client->adapter->name);

	वापस 0;

err_मुक्त_irq:
	अगर (state->irq > 0)
		मुक्त_irq(client->irq, state);
err_media_entity_cleanup:
	media_entity_cleanup(&sd->entity);
err_मुक्त_ctrl:
	adv7180_निकास_controls(state);
err_unरेजिस्टर_vpp_client:
	i2c_unरेजिस्टर_device(state->vpp_client);
err_unरेजिस्टर_csi_client:
	i2c_unरेजिस्टर_device(state->csi_client);
	mutex_destroy(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adv7180_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा adv7180_state *state = to_state(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);

	अगर (state->irq > 0)
		मुक्त_irq(client->irq, state);

	media_entity_cleanup(&sd->entity);
	adv7180_निकास_controls(state);

	i2c_unरेजिस्टर_device(state->vpp_client);
	i2c_unरेजिस्टर_device(state->csi_client);

	adv7180_set_घातer_pin(state, false);

	mutex_destroy(&state->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adv7180_id[] = अणु
	अणु "adv7180", (kernel_uदीर्घ_t)&adv7180_info पूर्ण,
	अणु "adv7180cp", (kernel_uदीर्घ_t)&adv7180_info पूर्ण,
	अणु "adv7180st", (kernel_uदीर्घ_t)&adv7180_info पूर्ण,
	अणु "adv7182", (kernel_uदीर्घ_t)&adv7182_info पूर्ण,
	अणु "adv7280", (kernel_uदीर्घ_t)&adv7280_info पूर्ण,
	अणु "adv7280-m", (kernel_uदीर्घ_t)&adv7280_m_info पूर्ण,
	अणु "adv7281", (kernel_uदीर्घ_t)&adv7281_info पूर्ण,
	अणु "adv7281-m", (kernel_uदीर्घ_t)&adv7281_m_info पूर्ण,
	अणु "adv7281-ma", (kernel_uदीर्घ_t)&adv7281_ma_info पूर्ण,
	अणु "adv7282", (kernel_uदीर्घ_t)&adv7282_info पूर्ण,
	अणु "adv7282-m", (kernel_uदीर्घ_t)&adv7282_m_info पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv7180_id);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adv7180_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा adv7180_state *state = to_state(sd);

	वापस adv7180_set_घातer(state, false);
पूर्ण

अटल पूर्णांक adv7180_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा adv7180_state *state = to_state(sd);
	पूर्णांक ret;

	ret = init_device(state);
	अगर (ret < 0)
		वापस ret;

	ret = adv7180_set_घातer(state, state->घातered);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(adv7180_pm_ops, adv7180_suspend, adv7180_resume);
#घोषणा ADV7180_PM_OPS (&adv7180_pm_ops)

#अन्यथा
#घोषणा ADV7180_PM_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id adv7180_of_id[] = अणु
	अणु .compatible = "adi,adv7180", पूर्ण,
	अणु .compatible = "adi,adv7180cp", पूर्ण,
	अणु .compatible = "adi,adv7180st", पूर्ण,
	अणु .compatible = "adi,adv7182", पूर्ण,
	अणु .compatible = "adi,adv7280", पूर्ण,
	अणु .compatible = "adi,adv7280-m", पूर्ण,
	अणु .compatible = "adi,adv7281", पूर्ण,
	अणु .compatible = "adi,adv7281-m", पूर्ण,
	अणु .compatible = "adi,adv7281-ma", पूर्ण,
	अणु .compatible = "adi,adv7282", पूर्ण,
	अणु .compatible = "adi,adv7282-m", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, adv7180_of_id);
#पूर्ण_अगर

अटल काष्ठा i2c_driver adv7180_driver = अणु
	.driver = अणु
		   .name = KBUILD_MODNAME,
		   .pm = ADV7180_PM_OPS,
		   .of_match_table = of_match_ptr(adv7180_of_id),
		   पूर्ण,
	.probe = adv7180_probe,
	.हटाओ = adv7180_हटाओ,
	.id_table = adv7180_id,
पूर्ण;

module_i2c_driver(adv7180_driver);

MODULE_DESCRIPTION("Analog Devices ADV7180 video decoder driver");
MODULE_AUTHOR("Mocean Laboratories");
MODULE_LICENSE("GPL v2");
