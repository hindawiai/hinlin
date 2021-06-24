<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    gpio functions.
    Merging GPIO support पूर्णांकo driver:
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-gpio.h"
#समावेश "tuner-xc2028.h"
#समावेश <media/tuner.h>
#समावेश <media/v4l2-ctrls.h>

/*
 * GPIO assignment of Yuan MPG600/MPG160
 *
 *    bit 15  14  13  12 |  11  10   9   8 |   7   6   5   4 |   3   2   1   0
 * OUTPUT         IN1 IN0                                       AM3 AM2 AM1 AM0
 *  INPUT                   DM1         DM0
 *
 *   IN* : Input selection
 *          IN1 IN0
 *           1   1  N/A
 *           1   0  Line
 *           0   1  N/A
 *           0   0  Tuner
 *
 *   AM* : Audio Mode
 *          AM3  0: Normal        1: Mixed(Sub+Main channel)
 *          AM2  0: Subchannel    1: Main channel
 *          AM1  0: Stereo        1: Mono
 *          AM0  0: Normal        1: Mute
 *
 *   DM* : Detected tuner audio Mode
 *          DM1  0: Stereo        1: Mono
 *          DM0  0: Multiplex     1: Normal
 *
 * GPIO Initial Settings
 *           MPG600   MPG160
 *     सूची   0x3080   0x7080
 *  OUTPUT   0x000C   0x400C
 *
 *  Special thanks to Makoto Iguchi <iguchi@tahoo.org> and Mr. Anonymous
 *  क्रम analyzing GPIO of MPG160.
 *
 *****************************************************************************
 *
 * GPIO assignment of Avermedia M179 (per inक्रमmation direct from AVerMedia)
 *
 *    bit 15  14  13  12 |  11  10   9   8 |   7   6   5   4 |   3   2   1   0
 * OUTPUT IN0 AM0 IN1               AM1 AM2       IN2     BR0   BR1
 *  INPUT
 *
 *   IN* : Input selection
 *          IN0 IN1 IN2
 *           *   1   *  Mute
 *           0   0   0  Line-In
 *           1   0   0  TV Tuner Audio
 *           0   0   1  FM Audio
 *           1   0   1  Mute
 *
 *   AM* : Audio Mode
 *          AM0 AM1 AM2
 *           0   0   0  TV Tuner Audio: L_OUT=(L+R)/2, R_OUT=SAP
 *           0   0   1  TV Tuner Audio: L_OUT=R_OUT=SAP   (SAP)
 *           0   1   0  TV Tuner Audio: L_OUT=L, R_OUT=R   (stereo)
 *           0   1   1  TV Tuner Audio: mute
 *           1   *   *  TV Tuner Audio: L_OUT=R_OUT=(L+R)/2   (mono)
 *
 *   BR* : Audio Sample Rate (BR stands क्रम bitrate क्रम some reason)
 *          BR0 BR1
 *           0   0   32 kHz
 *           0   1   44.1 kHz
 *           1   0   48 kHz
 *
 *   DM* : Detected tuner audio Mode
 *         Unknown currently
 *
 * Special thanks to AVerMedia Technologies, Inc. and Jiun-Kuei Jung at
 * AVerMedia क्रम providing the GPIO inक्रमmation used to add support
 * क्रम the M179 cards.
 */

/********************* GPIO stuffs *********************/

/* GPIO रेजिस्टरs */
#घोषणा IVTV_REG_GPIO_IN    0x9008
#घोषणा IVTV_REG_GPIO_OUT   0x900c
#घोषणा IVTV_REG_GPIO_सूची   0x9020

व्योम ivtv_reset_ir_gpio(काष्ठा ivtv *itv)
अणु
	पूर्णांक curdir, curout;

	अगर (itv->card->type != IVTV_CARD_PVR_150)
		वापस;
	IVTV_DEBUG_INFO("Resetting PVR150 IR\n");
	curout = पढ़ो_reg(IVTV_REG_GPIO_OUT);
	curdir = पढ़ो_reg(IVTV_REG_GPIO_सूची);
	curdir |= 0x80;
	ग_लिखो_reg(curdir, IVTV_REG_GPIO_सूची);
	curout = (curout & ~0xF) | 1;
	ग_लिखो_reg(curout, IVTV_REG_GPIO_OUT);
	/* We could use something अन्यथा क्रम smaller समय */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(1));
	curout |= 2;
	ग_लिखो_reg(curout, IVTV_REG_GPIO_OUT);
	curdir &= ~0x80;
	ग_लिखो_reg(curdir, IVTV_REG_GPIO_सूची);
पूर्ण

/* Xceive tuner reset function */
पूर्णांक ivtv_reset_tuner_gpio(व्योम *dev, पूर्णांक component, पूर्णांक cmd, पूर्णांक value)
अणु
	काष्ठा i2c_algo_bit_data *algo = dev;
	काष्ठा ivtv *itv = algo->data;
	u32 curout;

	अगर (cmd != XC2028_TUNER_RESET)
		वापस 0;
	IVTV_DEBUG_INFO("Resetting tuner\n");
	curout = पढ़ो_reg(IVTV_REG_GPIO_OUT);
	curout &= ~(1 << itv->card->xceive_pin);
	ग_लिखो_reg(curout, IVTV_REG_GPIO_OUT);
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(1));

	curout |= 1 << itv->card->xceive_pin;
	ग_लिखो_reg(curout, IVTV_REG_GPIO_OUT);
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(1));
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ivtv *sd_to_ivtv(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ivtv, sd_gpio);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ivtv, hdl_gpio)->sd_gpio;
पूर्ण

अटल पूर्णांक subdev_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	mask = itv->card->gpio_audio_freq.mask;
	चयन (freq) अणु
	हाल 32000:
		data = itv->card->gpio_audio_freq.f32000;
		अवरोध;
	हाल 44100:
		data = itv->card->gpio_audio_freq.f44100;
		अवरोध;
	हाल 48000:
	शेष:
		data = itv->card->gpio_audio_freq.f48000;
		अवरोध;
	पूर्ण
	अगर (mask)
		ग_लिखो_reg((पढ़ो_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	वापस 0;
पूर्ण

अटल पूर्णांक subdev_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask;

	mask = itv->card->gpio_audio_detect.mask;
	अगर (mask == 0 || (पढ़ो_reg(IVTV_REG_GPIO_IN) & mask))
		vt->rxsubchans = V4L2_TUNER_SUB_STEREO |
			V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	अन्यथा
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	वापस 0;
पूर्ण

अटल पूर्णांक subdev_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	mask = itv->card->gpio_audio_mode.mask;
	चयन (vt->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG1:
		data = itv->card->gpio_audio_mode.lang1;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		data = itv->card->gpio_audio_mode.lang2;
		अवरोध;
	हाल V4L2_TUNER_MODE_MONO:
		data = itv->card->gpio_audio_mode.mono;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
	शेष:
		data = itv->card->gpio_audio_mode.stereo;
		अवरोध;
	पूर्ण
	अगर (mask)
		ग_लिखो_reg((पढ़ो_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	वापस 0;
पूर्ण

अटल पूर्णांक subdev_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	mask = itv->card->gpio_audio_input.mask;
	data = itv->card->gpio_audio_input.radio;
	अगर (mask)
		ग_लिखो_reg((पढ़ो_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	वापस 0;
पूर्ण

अटल पूर्णांक subdev_s_audio_routing(काष्ठा v4l2_subdev *sd,
				  u32 input, u32 output, u32 config)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	अगर (input > 2)
		वापस -EINVAL;
	mask = itv->card->gpio_audio_input.mask;
	चयन (input) अणु
	हाल 0:
		data = itv->card->gpio_audio_input.tuner;
		अवरोध;
	हाल 1:
		data = itv->card->gpio_audio_input.linein;
		अवरोध;
	हाल 2:
	शेष:
		data = itv->card->gpio_audio_input.radio;
		अवरोध;
	पूर्ण
	अगर (mask)
		ग_लिखो_reg((पढ़ो_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	वापस 0;
पूर्ण

अटल पूर्णांक subdev_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		mask = itv->card->gpio_audio_mute.mask;
		data = ctrl->val ? itv->card->gpio_audio_mute.mute : 0;
		अगर (mask)
			ग_लिखो_reg((पढ़ो_reg(IVTV_REG_GPIO_OUT) & ~mask) |
					(data & mask), IVTV_REG_GPIO_OUT);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल पूर्णांक subdev_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);

	IVTV_INFO("GPIO status: DIR=0x%04x OUT=0x%04x IN=0x%04x\n",
			पढ़ो_reg(IVTV_REG_GPIO_सूची), पढ़ो_reg(IVTV_REG_GPIO_OUT),
			पढ़ो_reg(IVTV_REG_GPIO_IN));
	v4l2_ctrl_handler_log_status(&itv->hdl_gpio, sd->name);
	वापस 0;
पूर्ण

अटल पूर्णांक subdev_s_video_routing(काष्ठा v4l2_subdev *sd,
				  u32 input, u32 output, u32 config)
अणु
	काष्ठा ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	अगर (input > 2) /* 0:Tuner 1:Composite 2:S-Video */
		वापस -EINVAL;
	mask = itv->card->gpio_video_input.mask;
	अगर (input == 0)
		data = itv->card->gpio_video_input.tuner;
	अन्यथा अगर (input == 1)
		data = itv->card->gpio_video_input.composite;
	अन्यथा
		data = itv->card->gpio_video_input.svideo;
	अगर (mask)
		ग_लिखो_reg((पढ़ो_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops gpio_ctrl_ops = अणु
	.s_ctrl = subdev_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops subdev_core_ops = अणु
	.log_status = subdev_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops subdev_tuner_ops = अणु
	.s_radio = subdev_s_radio,
	.g_tuner = subdev_g_tuner,
	.s_tuner = subdev_s_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops subdev_audio_ops = अणु
	.s_घड़ी_freq = subdev_s_घड़ी_freq,
	.s_routing = subdev_s_audio_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops subdev_video_ops = अणु
	.s_routing = subdev_s_video_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops subdev_ops = अणु
	.core = &subdev_core_ops,
	.tuner = &subdev_tuner_ops,
	.audio = &subdev_audio_ops,
	.video = &subdev_video_ops,
पूर्ण;

पूर्णांक ivtv_gpio_init(काष्ठा ivtv *itv)
अणु
	u16 pin = 0;

	अगर (itv->card->xceive_pin)
		pin = 1 << itv->card->xceive_pin;

	अगर ((itv->card->gpio_init.direction | pin) == 0)
		वापस 0;

	IVTV_DEBUG_INFO("GPIO initial dir: %08x out: %08x\n",
		   पढ़ो_reg(IVTV_REG_GPIO_सूची), पढ़ो_reg(IVTV_REG_GPIO_OUT));

	/* init output data then direction */
	ग_लिखो_reg(itv->card->gpio_init.initial_value | pin, IVTV_REG_GPIO_OUT);
	ग_लिखो_reg(itv->card->gpio_init.direction | pin, IVTV_REG_GPIO_सूची);
	v4l2_subdev_init(&itv->sd_gpio, &subdev_ops);
	snम_लिखो(itv->sd_gpio.name, माप(itv->sd_gpio.name), "%s-gpio", itv->v4l2_dev.name);
	itv->sd_gpio.grp_id = IVTV_HW_GPIO;
	v4l2_ctrl_handler_init(&itv->hdl_gpio, 1);
	v4l2_ctrl_new_std(&itv->hdl_gpio, &gpio_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	अगर (itv->hdl_gpio.error)
		वापस itv->hdl_gpio.error;
	itv->sd_gpio.ctrl_handler = &itv->hdl_gpio;
	v4l2_ctrl_handler_setup(&itv->hdl_gpio);
	वापस v4l2_device_रेजिस्टर_subdev(&itv->v4l2_dev, &itv->sd_gpio);
पूर्ण
