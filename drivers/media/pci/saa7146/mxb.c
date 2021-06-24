<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    mxb - v4l2 driver क्रम the Mulसमयdia eXtension Board

    Copyright (C) 1998-2006 Michael Hunold <michael@mihu.de>

    Visit http://www.themm.net/~mihu/linux/saa7146/mxb.hपंचांगl
    क्रम further details about this card.

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DEBUG_VARIABLE debug

#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>
#समावेश <media/tuner.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/i2c/saa7115.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश "tea6415c.h"
#समावेश "tea6420.h"

#घोषणा MXB_AUDIOS	6

#घोषणा I2C_SAA7111A  0x24
#घोषणा	I2C_TDA9840   0x42
#घोषणा	I2C_TEA6415C  0x43
#घोषणा	I2C_TEA6420_1 0x4c
#घोषणा	I2C_TEA6420_2 0x4d
#घोषणा	I2C_TUNER     0x60

#घोषणा MXB_BOARD_CAN_DO_VBI(dev)   (dev->revision != 0)

/* global variable */
अटल पूर्णांक mxb_num;

/* initial frequence the tuner will be tuned to.
   in verden (lower saxony, germany) 4148 is a
   channel called "phoenix" */
अटल पूर्णांक freq = 4148;
module_param(freq, पूर्णांक, 0644);
MODULE_PARM_DESC(freq, "initial frequency the tuner will be tuned to while setup");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off device debugging (default:off).");

#घोषणा MXB_INPUTS 4
क्रमागत अणु TUNER, AUX1, AUX3, AUX3_YC पूर्ण;

अटल काष्ठा v4l2_input mxb_inमाला_दो[MXB_INPUTS] = अणु
	अणु TUNER,   "Tuner",          V4L2_INPUT_TYPE_TUNER,  0x3f, 0,
		V4L2_STD_PAL_BG | V4L2_STD_PAL_I, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु AUX1,	   "AUX1",           V4L2_INPUT_TYPE_CAMERA, 0x3f, 0,
		V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु AUX3,	   "AUX3 Composite", V4L2_INPUT_TYPE_CAMERA, 0x3f, 0,
		V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु AUX3_YC, "AUX3 S-Video",   V4L2_INPUT_TYPE_CAMERA, 0x3f, 0,
		V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
पूर्ण;

/* this array holds the inक्रमmation, which port of the saa7146 each
   input actually uses. the mxb uses port 0 क्रम every input */
अटल काष्ठा अणु
	पूर्णांक hps_source;
	पूर्णांक hps_sync;
पूर्ण input_port_selection[MXB_INPUTS] = अणु
	अणु SAA7146_HPS_SOURCE_PORT_A, SAA7146_HPS_SYNC_PORT_A पूर्ण,
	अणु SAA7146_HPS_SOURCE_PORT_A, SAA7146_HPS_SYNC_PORT_A पूर्ण,
	अणु SAA7146_HPS_SOURCE_PORT_A, SAA7146_HPS_SYNC_PORT_A पूर्ण,
	अणु SAA7146_HPS_SOURCE_PORT_A, SAA7146_HPS_SYNC_PORT_A पूर्ण,
पूर्ण;

/* this array holds the inक्रमmation of the audio source (mxb_audios),
   which has to be चयनed corresponding to the video source (mxb_channels) */
अटल पूर्णांक video_audio_connect[MXB_INPUTS] =
	अणु 0, 1, 3, 3 पूर्ण;

काष्ठा mxb_routing अणु
	u32 input;
	u32 output;
पूर्ण;

/* these are the available audio sources, which can चयनed
   to the line- and cd-output inभागidually */
अटल काष्ठा v4l2_audio mxb_audios[MXB_AUDIOS] = अणु
	    अणु
		.index	= 0,
		.name	= "Tuner",
		.capability = V4L2_AUDCAP_STEREO,
	पूर्ण , अणु
		.index	= 1,
		.name	= "AUX1",
		.capability = V4L2_AUDCAP_STEREO,
	पूर्ण , अणु
		.index	= 2,
		.name	= "AUX2",
		.capability = V4L2_AUDCAP_STEREO,
	पूर्ण , अणु
		.index	= 3,
		.name	= "AUX3",
		.capability = V4L2_AUDCAP_STEREO,
	पूर्ण , अणु
		.index	= 4,
		.name	= "Radio (X9)",
		.capability = V4L2_AUDCAP_STEREO,
	पूर्ण , अणु
		.index	= 5,
		.name	= "CD-ROM (X10)",
		.capability = V4L2_AUDCAP_STEREO,
	पूर्ण
पूर्ण;

/* These are the necessary input-output-pins क्रम bringing one audio source
   (see above) to the CD-output. Note that gain is set to 0 in this table. */
अटल काष्ठा mxb_routing TEA6420_cd[MXB_AUDIOS + 1][2] = अणु
	अणु अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण पूर्ण,	/* Tuner */
	अणु अणु 5, 1 पूर्ण, अणु 6, 1 पूर्ण पूर्ण,	/* AUX 1 */
	अणु अणु 4, 1 पूर्ण, अणु 6, 1 पूर्ण पूर्ण,	/* AUX 2 */
	अणु अणु 3, 1 पूर्ण, अणु 6, 1 पूर्ण पूर्ण,	/* AUX 3 */
	अणु अणु 1, 1 पूर्ण, अणु 3, 1 पूर्ण पूर्ण,	/* Radio */
	अणु अणु 1, 1 पूर्ण, अणु 2, 1 पूर्ण पूर्ण,	/* CD-Rom */
	अणु अणु 6, 1 पूर्ण, अणु 6, 1 पूर्ण पूर्ण	/* Mute */
पूर्ण;

/* These are the necessary input-output-pins क्रम bringing one audio source
   (see above) to the line-output. Note that gain is set to 0 in this table. */
अटल काष्ठा mxb_routing TEA6420_line[MXB_AUDIOS + 1][2] = अणु
	अणु अणु 2, 3 पूर्ण, अणु 1, 2 पूर्ण पूर्ण,
	अणु अणु 5, 3 पूर्ण, अणु 6, 2 पूर्ण पूर्ण,
	अणु अणु 4, 3 पूर्ण, अणु 6, 2 पूर्ण पूर्ण,
	अणु अणु 3, 3 पूर्ण, अणु 6, 2 पूर्ण पूर्ण,
	अणु अणु 2, 3 पूर्ण, अणु 3, 2 पूर्ण पूर्ण,
	अणु अणु 2, 3 पूर्ण, अणु 2, 2 पूर्ण पूर्ण,
	अणु अणु 6, 3 पूर्ण, अणु 6, 2 पूर्ण पूर्ण	/* Mute */
पूर्ण;

काष्ठा mxb
अणु
	काष्ठा video_device	video_dev;
	काष्ठा video_device	vbi_dev;

	काष्ठा i2c_adapter	i2c_adapter;

	काष्ठा v4l2_subdev	*saa7111a;
	काष्ठा v4l2_subdev	*tda9840;
	काष्ठा v4l2_subdev	*tea6415c;
	काष्ठा v4l2_subdev	*tuner;
	काष्ठा v4l2_subdev	*tea6420_1;
	काष्ठा v4l2_subdev	*tea6420_2;

	पूर्णांक	cur_mode;	/* current audio mode (mono, stereo, ...) */
	पूर्णांक	cur_input;	/* current input */
	पूर्णांक	cur_audinput;	/* current audio input */
	पूर्णांक	cur_mute;	/* current mute status */
	काष्ठा v4l2_frequency	cur_freq;	/* current frequency the tuner is tuned to */
पूर्ण;

#घोषणा saa7111a_call(mxb, o, f, args...) \
	v4l2_subdev_call(mxb->saa7111a, o, f, ##args)
#घोषणा tda9840_call(mxb, o, f, args...) \
	v4l2_subdev_call(mxb->tda9840, o, f, ##args)
#घोषणा tea6415c_call(mxb, o, f, args...) \
	v4l2_subdev_call(mxb->tea6415c, o, f, ##args)
#घोषणा tuner_call(mxb, o, f, args...) \
	v4l2_subdev_call(mxb->tuner, o, f, ##args)
#घोषणा call_all(dev, o, f, args...) \
	v4l2_device_call_until_err(&dev->v4l2_dev, 0, o, f, ##args)

अटल व्योम mxb_update_audmode(काष्ठा mxb *mxb)
अणु
	काष्ठा v4l2_tuner t = अणु
		.audmode = mxb->cur_mode,
	पूर्ण;

	tda9840_call(mxb, tuner, s_tuner, &t);
पूर्ण

अटल अंतरभूत व्योम tea6420_route(काष्ठा mxb *mxb, पूर्णांक idx)
अणु
	v4l2_subdev_call(mxb->tea6420_1, audio, s_routing,
		TEA6420_cd[idx][0].input, TEA6420_cd[idx][0].output, 0);
	v4l2_subdev_call(mxb->tea6420_2, audio, s_routing,
		TEA6420_cd[idx][1].input, TEA6420_cd[idx][1].output, 0);
	v4l2_subdev_call(mxb->tea6420_1, audio, s_routing,
		TEA6420_line[idx][0].input, TEA6420_line[idx][0].output, 0);
	v4l2_subdev_call(mxb->tea6420_2, audio, s_routing,
		TEA6420_line[idx][1].input, TEA6420_line[idx][1].output, 0);
पूर्ण

अटल काष्ठा saa7146_extension extension;

अटल पूर्णांक mxb_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa7146_dev *dev = container_of(ctrl->handler,
				काष्ठा saa7146_dev, ctrl_handler);
	काष्ठा mxb *mxb = dev->ext_priv;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		mxb->cur_mute = ctrl->val;
		/* चयन the audio-source */
		tea6420_route(mxb, ctrl->val ? 6 :
				video_audio_connect[mxb->cur_input]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mxb_ctrl_ops = अणु
	.s_ctrl = mxb_s_ctrl,
पूर्ण;

अटल पूर्णांक mxb_probe(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev->ctrl_handler;
	काष्ठा mxb *mxb = शून्य;

	v4l2_ctrl_new_std(hdl, &mxb_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	अगर (hdl->error)
		वापस hdl->error;
	mxb = kzalloc(माप(काष्ठा mxb), GFP_KERNEL);
	अगर (mxb == शून्य) अणु
		DEB_D("not enough kernel memory\n");
		वापस -ENOMEM;
	पूर्ण


	snम_लिखो(mxb->i2c_adapter.name, माप(mxb->i2c_adapter.name), "mxb%d", mxb_num);

	saa7146_i2c_adapter_prepare(dev, &mxb->i2c_adapter, SAA7146_I2C_BUS_BIT_RATE_480);
	अगर (i2c_add_adapter(&mxb->i2c_adapter) < 0) अणु
		DEB_S("cannot register i2c-device. skipping.\n");
		kमुक्त(mxb);
		वापस -EFAULT;
	पूर्ण

	mxb->saa7111a = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"saa7111", I2C_SAA7111A, शून्य);
	mxb->tea6420_1 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tea6420", I2C_TEA6420_1, शून्य);
	mxb->tea6420_2 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tea6420", I2C_TEA6420_2, शून्य);
	mxb->tea6415c = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tea6415c", I2C_TEA6415C, शून्य);
	mxb->tda9840 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tda9840", I2C_TDA9840, शून्य);
	mxb->tuner = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tuner", I2C_TUNER, शून्य);

	/* check अगर all devices are present */
	अगर (!mxb->tea6420_1 || !mxb->tea6420_2 || !mxb->tea6415c ||
	    !mxb->tda9840 || !mxb->saa7111a || !mxb->tuner) अणु
		pr_err("did not find all i2c devices. aborting\n");
		i2c_del_adapter(&mxb->i2c_adapter);
		kमुक्त(mxb);
		वापस -ENODEV;
	पूर्ण

	/* all devices are present, probe was successful */

	/* we store the poपूर्णांकer in our निजी data field */
	dev->ext_priv = mxb;

	v4l2_ctrl_handler_setup(hdl);

	वापस 0;
पूर्ण

/* some init data क्रम the saa7740, the so-called 'sound arena module'.
   there are no specs available, so we simply use some init values */
अटल काष्ठा अणु
	पूर्णांक	length;
	अक्षर	data[9];
पूर्ण mxb_saa7740_init[] = अणु
	अणु 3, अणु 0x80, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x80, 0x89, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x80, 0xb0, 0x0a पूर्ण पूर्ण,अणु 3, अणु 0x00, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x49, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x4a, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x4b, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x4c, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x4d, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x4e, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x4f, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x50, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x51, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x52, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x53, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x54, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x55, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x56, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x57, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x58, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x59, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x5a, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x5b, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x5c, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x5d, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x5e, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x5f, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x60, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x61, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x62, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x63, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x64, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x65, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x66, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x67, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x68, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x69, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x6a, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x6b, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x6c, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x6d, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x6e, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x6f, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x70, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x71, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x72, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x73, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x74, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x75, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x76, 0x00, 0x00 पूर्ण पूर्ण,
	अणु 3, अणु 0x77, 0x00, 0x00 पूर्ण पूर्ण,अणु 3, अणु 0x41, 0x00, 0x42 पूर्ण पूर्ण,
	अणु 3, अणु 0x42, 0x10, 0x42 पूर्ण पूर्ण,अणु 3, अणु 0x43, 0x20, 0x42 पूर्ण पूर्ण,
	अणु 3, अणु 0x44, 0x30, 0x42 पूर्ण पूर्ण,अणु 3, अणु 0x45, 0x00, 0x01 पूर्ण पूर्ण,
	अणु 3, अणु 0x46, 0x00, 0x01 पूर्ण पूर्ण,अणु 3, अणु 0x47, 0x00, 0x01 पूर्ण पूर्ण,
	अणु 3, अणु 0x48, 0x00, 0x01 पूर्ण पूर्ण,
	अणु 9, अणु 0x01, 0x03, 0xc5, 0x5c, 0x7a, 0x85, 0x01, 0x00, 0x54 पूर्ण पूर्ण,
	अणु 9, अणु 0x21, 0x03, 0xc5, 0x5c, 0x7a, 0x85, 0x01, 0x00, 0x54 पूर्ण पूर्ण,
	अणु 9, अणु 0x09, 0x0b, 0xb4, 0x6b, 0x74, 0x85, 0x95, 0x00, 0x34 पूर्ण पूर्ण,
	अणु 9, अणु 0x29, 0x0b, 0xb4, 0x6b, 0x74, 0x85, 0x95, 0x00, 0x34 पूर्ण पूर्ण,
	अणु 9, अणु 0x11, 0x17, 0x43, 0x62, 0x68, 0x89, 0xd1, 0xff, 0xb0 पूर्ण पूर्ण,
	अणु 9, अणु 0x31, 0x17, 0x43, 0x62, 0x68, 0x89, 0xd1, 0xff, 0xb0 पूर्ण पूर्ण,
	अणु 9, अणु 0x19, 0x20, 0x62, 0x51, 0x5a, 0x95, 0x19, 0x01, 0x50 पूर्ण पूर्ण,
	अणु 9, अणु 0x39, 0x20, 0x62, 0x51, 0x5a, 0x95, 0x19, 0x01, 0x50 पूर्ण पूर्ण,
	अणु 9, अणु 0x05, 0x3e, 0xd2, 0x69, 0x4e, 0x9a, 0x51, 0x00, 0xf0 पूर्ण पूर्ण,
	अणु 9, अणु 0x25, 0x3e, 0xd2, 0x69, 0x4e, 0x9a, 0x51, 0x00, 0xf0 पूर्ण पूर्ण,
	अणु 9, अणु 0x0d, 0x3d, 0xa1, 0x40, 0x7d, 0x9f, 0x29, 0xfe, 0x14 पूर्ण पूर्ण,
	अणु 9, अणु 0x2d, 0x3d, 0xa1, 0x40, 0x7d, 0x9f, 0x29, 0xfe, 0x14 पूर्ण पूर्ण,
	अणु 9, अणु 0x15, 0x73, 0xa1, 0x50, 0x5d, 0xa6, 0xf5, 0xfe, 0x38 पूर्ण पूर्ण,
	अणु 9, अणु 0x35, 0x73, 0xa1, 0x50, 0x5d, 0xa6, 0xf5, 0xfe, 0x38 पूर्ण पूर्ण,
	अणु 9, अणु 0x1d, 0xed, 0xd0, 0x68, 0x29, 0xb4, 0xe1, 0x00, 0xb8 पूर्ण पूर्ण,
	अणु 9, अणु 0x3d, 0xed, 0xd0, 0x68, 0x29, 0xb4, 0xe1, 0x00, 0xb8 पूर्ण पूर्ण,
	अणु 3, अणु 0x80, 0xb3, 0x0a पूर्ण पूर्ण,
	अणु-1, अणु 0 पूर्ण पूर्ण
पूर्ण;

/* bring hardware to a sane state. this has to be करोne, just in हाल someone
   wants to capture from this device beक्रमe it has been properly initialized.
   the capture engine would badly fail, because no valid संकेत arrives on the
   saa7146, thus leading to समयouts and stuff. */
अटल पूर्णांक mxb_init_करोne(काष्ठा saa7146_dev* dev)
अणु
	काष्ठा mxb* mxb = (काष्ठा mxb*)dev->ext_priv;
	काष्ठा i2c_msg msg;
	काष्ठा tuner_setup tun_setup;
	v4l2_std_id std = V4L2_STD_PAL_BG;

	पूर्णांक i = 0, err = 0;

	/* mute audio on tea6420s */
	tea6420_route(mxb, 6);

	/* select video mode in saa7111a */
	saa7111a_call(mxb, video, s_std, std);

	/* select tuner-output on saa7111a */
	i = 0;
	saa7111a_call(mxb, video, s_routing, SAA7115_COMPOSITE0,
		SAA7111_FMT_CCIR, 0);

	/* select a tuner type */
	tun_setup.mode_mask = T_ANALOG_TV;
	tun_setup.addr = ADDR_UNSET;
	tun_setup.type = TUNER_PHILIPS_PAL;
	tuner_call(mxb, tuner, s_type_addr, &tun_setup);
	/* tune in some frequency on tuner */
	mxb->cur_freq.tuner = 0;
	mxb->cur_freq.type = V4L2_TUNER_ANALOG_TV;
	mxb->cur_freq.frequency = freq;
	tuner_call(mxb, tuner, s_frequency, &mxb->cur_freq);

	/* set a शेष video standard */
	/* These two gpio calls set the GPIO pins that control the tda9820 */
	saa7146_ग_लिखो(dev, GPIO_CTRL, 0x00404050);
	saa7111a_call(mxb, core, s_gpio, 1);
	saa7111a_call(mxb, video, s_std, std);
	tuner_call(mxb, video, s_std, std);

	/* चयन to tuner-channel on tea6415c */
	tea6415c_call(mxb, video, s_routing, 3, 17, 0);

	/* select tuner-output on multicable on tea6415c */
	tea6415c_call(mxb, video, s_routing, 3, 13, 0);

	/* the rest क्रम mxb */
	mxb->cur_input = 0;
	mxb->cur_audinput = video_audio_connect[mxb->cur_input];
	mxb->cur_mute = 1;

	mxb->cur_mode = V4L2_TUNER_MODE_STEREO;
	mxb_update_audmode(mxb);

	/* check अगर the saa7740 (aka 'sound arena module') is present
	   on the mxb. अगर so, we must initialize it. due to lack of
	   inक्रमmation about the saa7740, the values were reverse
	   engineered. */
	msg.addr = 0x1b;
	msg.flags = 0;
	msg.len = mxb_saa7740_init[0].length;
	msg.buf = &mxb_saa7740_init[0].data[0];

	err = i2c_transfer(&mxb->i2c_adapter, &msg, 1);
	अगर (err == 1) अणु
		/* the sound arena module is a pos, that's probably the reason
		   philips refuses to hand out a datasheet क्रम the saa7740...
		   it seems to screw up the i2c bus, so we disable fast irq
		   based i2c transactions here and rely on the slow and safe
		   polling method ... */
		extension.flags &= ~SAA7146_USE_I2C_IRQ;
		क्रम (i = 1; ; i++) अणु
			अगर (-1 == mxb_saa7740_init[i].length)
				अवरोध;

			msg.len = mxb_saa7740_init[i].length;
			msg.buf = &mxb_saa7740_init[i].data[0];
			err = i2c_transfer(&mxb->i2c_adapter, &msg, 1);
			अगर (err != 1) अणु
				DEB_D("failed to initialize 'sound arena module'\n");
				जाओ err;
			पूर्ण
		पूर्ण
		pr_info("'sound arena module' detected\n");
	पूर्ण
err:
	/* the rest क्रम saa7146: you should definitely set some basic values
	   क्रम the input-port handling of the saa7146. */

	/* ext->saa has been filled by the core driver */

	/* some stuff is करोne via variables */
	saa7146_set_hps_source_and_sync(dev, input_port_selection[mxb->cur_input].hps_source,
			input_port_selection[mxb->cur_input].hps_sync);

	/* some stuff is करोne via direct ग_लिखो to the रेजिस्टरs */

	/* this is ugly, but because of the fact that this is completely
	   hardware dependend, it should be करोne directly... */
	saa7146_ग_लिखो(dev, DD1_STREAM_B,	0x00000000);
	saa7146_ग_लिखो(dev, DD1_INIT,		0x02000200);
	saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	वापस 0;
पूर्ण

/* पूर्णांकerrupt-handler. this माला_लो called when irq_mask is != 0.
   it must clear the पूर्णांकerrupt-bits in irq_mask it has handled */
/*
व्योम mxb_irq_bh(काष्ठा saa7146_dev* dev, u32* irq_mask)
अणु
	काष्ठा mxb* mxb = (काष्ठा mxb*)dev->ext_priv;
पूर्ण
*/

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	DEB_EE("VIDIOC_ENUMINPUT %d\n", i->index);
	अगर (i->index >= MXB_INPUTS)
		वापस -EINVAL;
	स_नकल(i, &mxb_inमाला_दो[i->index], माप(काष्ठा v4l2_input));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;
	*i = mxb->cur_input;

	DEB_EE("VIDIOC_G_INPUT %d\n", *i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;
	पूर्णांक err = 0;
	पूर्णांक i = 0;

	DEB_EE("VIDIOC_S_INPUT %d\n", input);

	अगर (input >= MXB_INPUTS)
		वापस -EINVAL;

	mxb->cur_input = input;

	saa7146_set_hps_source_and_sync(dev, input_port_selection[input].hps_source,
			input_port_selection[input].hps_sync);

	/* prepare चयनing of tea6415c and saa7111a;
	   have a look at the 'background'-file क्रम further inक्रमmation  */
	चयन (input) अणु
	हाल TUNER:
		i = SAA7115_COMPOSITE0;

		err = tea6415c_call(mxb, video, s_routing, 3, 17, 0);

		/* connect tuner-output always to multicable */
		अगर (!err)
			err = tea6415c_call(mxb, video, s_routing, 3, 13, 0);
		अवरोध;
	हाल AUX3_YC:
		/* nothing to be करोne here. aux3_yc is
		   directly connected to the saa711a */
		i = SAA7115_SVIDEO1;
		अवरोध;
	हाल AUX3:
		/* nothing to be करोne here. aux3 is
		   directly connected to the saa711a */
		i = SAA7115_COMPOSITE1;
		अवरोध;
	हाल AUX1:
		i = SAA7115_COMPOSITE0;
		err = tea6415c_call(mxb, video, s_routing, 1, 17, 0);
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	/* चयन video in saa7111a */
	अगर (saa7111a_call(mxb, video, s_routing, i, SAA7111_FMT_CCIR, 0))
		pr_err("VIDIOC_S_INPUT: could not address saa7111a\n");

	mxb->cur_audinput = video_audio_connect[input];
	/* चयन the audio-source only अगर necessary */
	अगर (0 == mxb->cur_mute)
		tea6420_route(mxb, mxb->cur_audinput);
	अगर (mxb->cur_audinput == 0)
		mxb_update_audmode(mxb);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	अगर (t->index) अणु
		DEB_D("VIDIOC_G_TUNER: channel %d does not have a tuner attached\n",
		      t->index);
		वापस -EINVAL;
	पूर्ण

	DEB_EE("VIDIOC_G_TUNER: %d\n", t->index);

	स_रखो(t, 0, माप(*t));
	strscpy(t->name, "TV Tuner", माप(t->name));
	t->type = V4L2_TUNER_ANALOG_TV;
	t->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2 | V4L2_TUNER_CAP_SAP;
	t->audmode = mxb->cur_mode;
	वापस call_all(dev, tuner, g_tuner, t);
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	अगर (t->index) अणु
		DEB_D("VIDIOC_S_TUNER: channel %d does not have a tuner attached\n",
		      t->index);
		वापस -EINVAL;
	पूर्ण

	mxb->cur_mode = t->audmode;
	वापस call_all(dev, tuner, s_tuner, t);
पूर्ण

अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *fh, v4l2_std_id *norm)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;

	वापस call_all(dev, video, querystd, norm);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	अगर (f->tuner)
		वापस -EINVAL;
	*f = mxb->cur_freq;

	DEB_EE("VIDIOC_G_FREQ: freq:0x%08x\n", mxb->cur_freq.frequency);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	अगर (f->tuner)
		वापस -EINVAL;

	अगर (V4L2_TUNER_ANALOG_TV != f->type)
		वापस -EINVAL;

	DEB_EE("VIDIOC_S_FREQUENCY: freq:0x%08x\n", mxb->cur_freq.frequency);

	/* tune in desired frequency */
	tuner_call(mxb, tuner, s_frequency, f);
	/* let the tuner subdev clamp the frequency to the tuner range */
	mxb->cur_freq = *f;
	tuner_call(mxb, tuner, g_frequency, &mxb->cur_freq);
	अगर (mxb->cur_audinput == 0)
		mxb_update_audmode(mxb);

	अगर (mxb->cur_input)
		वापस 0;

	/* hack: changing the frequency should invalidate the vbi-counter (=> alevt) */
	spin_lock(&dev->slock);
	vv->vbi_fieldcount = 0;
	spin_unlock(&dev->slock);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	अगर (a->index >= MXB_AUDIOS)
		वापस -EINVAL;
	*a = mxb_audios[a->index];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	DEB_EE("VIDIOC_G_AUDIO\n");
	*a = mxb_audios[mxb->cur_audinput];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audio *a)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	DEB_D("VIDIOC_S_AUDIO %d\n", a->index);
	अगर (a->index >= 32 ||
	    !(mxb_inमाला_दो[mxb->cur_input].audioset & (1 << a->index)))
		वापस -EINVAL;

	अगर (mxb->cur_audinput != a->index) अणु
		mxb->cur_audinput = a->index;
		tea6420_route(mxb, a->index);
		अगर (mxb->cur_audinput == 0)
			mxb_update_audmode(mxb);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;

	अगर (reg->reg > pci_resource_len(dev->pci, 0) - 4)
		वापस -EINVAL;
	reg->val = saa7146_पढ़ो(dev, reg->reg);
	reg->size = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;

	अगर (reg->reg > pci_resource_len(dev->pci, 0) - 4)
		वापस -EINVAL;
	saa7146_ग_लिखो(dev, reg->reg, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा saa7146_ext_vv vv_data;

/* this function only माला_लो called when the probing was successful */
अटल पूर्णांक mxb_attach(काष्ठा saa7146_dev *dev, काष्ठा saa7146_pci_extension_data *info)
अणु
	काष्ठा mxb *mxb;

	DEB_EE("dev:%p\n", dev);

	saa7146_vv_init(dev, &vv_data);
	अगर (mxb_probe(dev)) अणु
		saa7146_vv_release(dev);
		वापस -1;
	पूर्ण
	mxb = (काष्ठा mxb *)dev->ext_priv;

	vv_data.vid_ops.vidioc_क्रमागत_input = vidioc_क्रमागत_input;
	vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data.vid_ops.vidioc_s_input = vidioc_s_input;
	vv_data.vid_ops.vidioc_querystd = vidioc_querystd;
	vv_data.vid_ops.vidioc_g_tuner = vidioc_g_tuner;
	vv_data.vid_ops.vidioc_s_tuner = vidioc_s_tuner;
	vv_data.vid_ops.vidioc_g_frequency = vidioc_g_frequency;
	vv_data.vid_ops.vidioc_s_frequency = vidioc_s_frequency;
	vv_data.vid_ops.vidioc_क्रमागतaudio = vidioc_क्रमागतaudio;
	vv_data.vid_ops.vidioc_g_audio = vidioc_g_audio;
	vv_data.vid_ops.vidioc_s_audio = vidioc_s_audio;
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	vv_data.vid_ops.vidioc_g_रेजिस्टर = vidioc_g_रेजिस्टर;
	vv_data.vid_ops.vidioc_s_रेजिस्टर = vidioc_s_रेजिस्टर;
#पूर्ण_अगर
	अगर (saa7146_रेजिस्टर_device(&mxb->video_dev, dev, "mxb", VFL_TYPE_VIDEO)) अणु
		ERR("cannot register capture v4l2 device. skipping.\n");
		saa7146_vv_release(dev);
		वापस -1;
	पूर्ण

	/* initialization stuff (vbi) (only क्रम revision > 0 and क्रम extensions which want it)*/
	अगर (MXB_BOARD_CAN_DO_VBI(dev)) अणु
		अगर (saa7146_रेजिस्टर_device(&mxb->vbi_dev, dev, "mxb", VFL_TYPE_VBI)) अणु
			ERR("cannot register vbi v4l2 device. skipping.\n");
		पूर्ण
	पूर्ण

	pr_info("found Multimedia eXtension Board #%d\n", mxb_num);

	mxb_num++;
	mxb_init_करोne(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mxb_detach(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	DEB_EE("dev:%p\n", dev);

	/* mute audio on tea6420s */
	tea6420_route(mxb, 6);

	saa7146_unरेजिस्टर_device(&mxb->video_dev,dev);
	अगर (MXB_BOARD_CAN_DO_VBI(dev))
		saa7146_unरेजिस्टर_device(&mxb->vbi_dev, dev);
	saa7146_vv_release(dev);

	mxb_num--;

	i2c_del_adapter(&mxb->i2c_adapter);
	kमुक्त(mxb);

	वापस 0;
पूर्ण

अटल पूर्णांक std_callback(काष्ठा saa7146_dev *dev, काष्ठा saa7146_standard *standard)
अणु
	काष्ठा mxb *mxb = (काष्ठा mxb *)dev->ext_priv;

	अगर (V4L2_STD_PAL_I == standard->id) अणु
		v4l2_std_id std = V4L2_STD_PAL_I;

		DEB_D("VIDIOC_S_STD: setting mxb for PAL_I\n");
		/* These two gpio calls set the GPIO pins that control the tda9820 */
		saa7146_ग_लिखो(dev, GPIO_CTRL, 0x00404050);
		saa7111a_call(mxb, core, s_gpio, 0);
		saa7111a_call(mxb, video, s_std, std);
		अगर (mxb->cur_input == 0)
			tuner_call(mxb, video, s_std, std);
	पूर्ण अन्यथा अणु
		v4l2_std_id std = V4L2_STD_PAL_BG;

		अगर (mxb->cur_input)
			std = standard->id;
		DEB_D("VIDIOC_S_STD: setting mxb for PAL/NTSC/SECAM\n");
		/* These two gpio calls set the GPIO pins that control the tda9820 */
		saa7146_ग_लिखो(dev, GPIO_CTRL, 0x00404050);
		saa7111a_call(mxb, core, s_gpio, 1);
		saa7111a_call(mxb, video, s_std, std);
		अगर (mxb->cur_input == 0)
			tuner_call(mxb, video, s_std, std);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा saa7146_standard standard[] = अणु
	अणु
		.name	= "PAL-BG",	.id	= V4L2_STD_PAL_BG,
		.v_offset	= 0x17,	.v_field	= 288,
		.h_offset	= 0x14,	.h_pixels	= 680,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "PAL-I",	.id	= V4L2_STD_PAL_I,
		.v_offset	= 0x17,	.v_field	= 288,
		.h_offset	= 0x14,	.h_pixels	= 680,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "NTSC",	.id	= V4L2_STD_NTSC,
		.v_offset	= 0x16,	.v_field	= 240,
		.h_offset	= 0x06,	.h_pixels	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	पूर्ण, अणु
		.name	= "SECAM",	.id	= V4L2_STD_SECAM,
		.v_offset	= 0x14,	.v_field	= 288,
		.h_offset	= 0x14,	.h_pixels	= 720,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण
पूर्ण;

अटल काष्ठा saa7146_pci_extension_data mxb = अणु
	.ext_priv = "Multimedia eXtension Board",
	.ext = &extension,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु
		.venकरोr    = PCI_VENDOR_ID_PHILIPS,
		.device	   = PCI_DEVICE_ID_PHILIPS_SAA7146,
		.subvenकरोr = 0x0000,
		.subdevice = 0x0000,
		.driver_data = (अचिन्हित दीर्घ)&mxb,
	पूर्ण, अणु
		.venकरोr	= 0,
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_tbl);

अटल काष्ठा saa7146_ext_vv vv_data = अणु
	.inमाला_दो		= MXB_INPUTS,
	.capabilities	= V4L2_CAP_TUNER | V4L2_CAP_VBI_CAPTURE | V4L2_CAP_AUDIO,
	.stds		= &standard[0],
	.num_stds	= ARRAY_SIZE(standard),
	.std_callback	= &std_callback,
पूर्ण;

अटल काष्ठा saa7146_extension extension = अणु
	.name		= "Multimedia eXtension Board",
	.flags		= SAA7146_USE_I2C_IRQ,

	.pci_tbl	= &pci_tbl[0],
	.module		= THIS_MODULE,

	.attach		= mxb_attach,
	.detach		= mxb_detach,

	.irq_mask	= 0,
	.irq_func	= शून्य,
पूर्ण;

अटल पूर्णांक __init mxb_init_module(व्योम)
अणु
	अगर (saa7146_रेजिस्टर_extension(&extension)) अणु
		DEB_S("failed to register extension\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास mxb_cleanup_module(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&extension);
पूर्ण

module_init(mxb_init_module);
module_निकास(mxb_cleanup_module);

MODULE_DESCRIPTION("video4linux-2 driver for the Siemens-Nixdorf 'Multimedia eXtension board'");
MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_LICENSE("GPL");
