<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * av7110_v4l.c: av7110 video4linux पूर्णांकerface क्रम DVB and Siemens DVB-C analog module
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * originally based on code by:
 * Copyright (C) 1998,1999 Christian Theiss <mistert@rz.fh-augsburg.de>
 *
 * the project's page is at https://linuxtv.org
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/समयr.h>
#समावेश <linux/poll.h>

#समावेश "av7110.h"
#समावेश "av7110_hw.h"
#समावेश "av7110_av.h"

पूर्णांक msp_ग_लिखोreg(काष्ठा av7110 *av7110, u8 dev, u16 reg, u16 val)
अणु
	u8 msg[5] = अणु dev, reg >> 8, reg & 0xff, val >> 8 , val & 0xff पूर्ण;
	काष्ठा i2c_msg msgs = अणु .flags = 0, .len = 5, .buf = msg पूर्ण;

	चयन (av7110->adac_type) अणु
	हाल DVB_ADAC_MSP34x0:
		msgs.addr = 0x40;
		अवरोध;
	हाल DVB_ADAC_MSP34x5:
		msgs.addr = 0x42;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (i2c_transfer(&av7110->i2c_adap, &msgs, 1) != 1) अणु
		dprपूर्णांकk(1, "dvb-ttpci: failed @ card %d, %u = %u\n",
		       av7110->dvb_adapter.num, reg, val);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msp_पढ़ोreg(काष्ठा av7110 *av7110, u8 dev, u16 reg, u16 *val)
अणु
	u8 msg1[3] = अणु dev, reg >> 8, reg & 0xff पूर्ण;
	u8 msg2[2];
	काष्ठा i2c_msg msgs[2] = अणु
		अणु .flags = 0	   , .len = 3, .buf = msg1 पूर्ण,
		अणु .flags = I2C_M_RD, .len = 2, .buf = msg2 पूर्ण
	पूर्ण;

	चयन (av7110->adac_type) अणु
	हाल DVB_ADAC_MSP34x0:
		msgs[0].addr = 0x40;
		msgs[1].addr = 0x40;
		अवरोध;
	हाल DVB_ADAC_MSP34x5:
		msgs[0].addr = 0x42;
		msgs[1].addr = 0x42;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (i2c_transfer(&av7110->i2c_adap, &msgs[0], 2) != 2) अणु
		dprपूर्णांकk(1, "dvb-ttpci: failed @ card %d, %u\n",
		       av7110->dvb_adapter.num, reg);
		वापस -EIO;
	पूर्ण
	*val = (msg2[0] << 8) | msg2[1];
	वापस 0;
पूर्ण

अटल काष्ठा v4l2_input inमाला_दो[4] = अणु
	अणु
		.index		= 0,
		.name		= "DVB",
		.type		= V4L2_INPUT_TYPE_CAMERA,
		.audioset	= 1,
		.tuner		= 0, /* ignored */
		.std		= V4L2_STD_PAL_BG|V4L2_STD_NTSC_M,
		.status		= 0,
		.capabilities	= V4L2_IN_CAP_STD,
	पूर्ण, अणु
		.index		= 1,
		.name		= "Television",
		.type		= V4L2_INPUT_TYPE_TUNER,
		.audioset	= 1,
		.tuner		= 0,
		.std		= V4L2_STD_PAL_BG|V4L2_STD_NTSC_M,
		.status		= 0,
		.capabilities	= V4L2_IN_CAP_STD,
	पूर्ण, अणु
		.index		= 2,
		.name		= "Video",
		.type		= V4L2_INPUT_TYPE_CAMERA,
		.audioset	= 0,
		.tuner		= 0,
		.std		= V4L2_STD_PAL_BG|V4L2_STD_NTSC_M,
		.status		= 0,
		.capabilities	= V4L2_IN_CAP_STD,
	पूर्ण, अणु
		.index		= 3,
		.name		= "Y/C",
		.type		= V4L2_INPUT_TYPE_CAMERA,
		.audioset	= 0,
		.tuner		= 0,
		.std		= V4L2_STD_PAL_BG|V4L2_STD_NTSC_M,
		.status		= 0,
		.capabilities	= V4L2_IN_CAP_STD,
	पूर्ण
पूर्ण;

अटल पूर्णांक ves1820_ग_लिखोreg(काष्ठा saa7146_dev *dev, u8 addr, u8 reg, u8 data)
अणु
	काष्ठा av7110 *av7110 = dev->ext_priv;
	u8 buf[] = अणु 0x00, reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = addr, .flags = 0, .buf = buf, .len = 3 पूर्ण;

	dprपूर्णांकk(4, "dev: %p\n", dev);

	अगर (1 != i2c_transfer(&av7110->i2c_adap, &msg, 1))
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_ग_लिखो(काष्ठा saa7146_dev *dev, u8 addr, u8 data [4])
अणु
	काष्ठा av7110 *av7110 = dev->ext_priv;
	काष्ठा i2c_msg msg = अणु .addr = addr, .flags = 0, .buf = data, .len = 4 पूर्ण;

	dprपूर्णांकk(4, "dev: %p\n", dev);

	अगर (1 != i2c_transfer(&av7110->i2c_adap, &msg, 1))
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_set_tv_freq(काष्ठा saa7146_dev *dev, u32 freq)
अणु
	u32 भाग;
	u8 config;
	u8 buf[4];

	dprपूर्णांकk(4, "freq: 0x%08x\n", freq);

	/* magic number: 614. tuning with the frequency given by v4l2
	   is always off by 614*62.5 = 38375 kHz...*/
	भाग = freq + 614;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0x8e;

	अगर (freq < 16U * 16825 / 100)
		config = 0xa0;
	अन्यथा अगर (freq < 16U * 44725 / 100)
		config = 0x90;
	अन्यथा
		config = 0x30;
	config &= ~0x02;

	buf[3] = config;

	वापस tuner_ग_लिखो(dev, 0x61, buf);
पूर्ण

अटल पूर्णांक stv0297_set_tv_freq(काष्ठा saa7146_dev *dev, u32 freq)
अणु
	काष्ठा av7110 *av7110 = (काष्ठा av7110*)dev->ext_priv;
	u32 भाग;
	u8 data[4];

	भाग = (freq + 38900000 + 31250) / 62500;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0xce;

	अगर (freq < 45000000)
		वापस -EINVAL;
	अन्यथा अगर (freq < 137000000)
		data[3] = 0x01;
	अन्यथा अगर (freq < 403000000)
		data[3] = 0x02;
	अन्यथा अगर (freq < 860000000)
		data[3] = 0x04;
	अन्यथा
		वापस -EINVAL;

	अगर (av7110->fe->ops.i2c_gate_ctrl)
		av7110->fe->ops.i2c_gate_ctrl(av7110->fe, 1);
	वापस tuner_ग_लिखो(dev, 0x63, data);
पूर्ण



अटल काष्ठा saa7146_standard analog_standard[];
अटल काष्ठा saa7146_standard dvb_standard[];
अटल काष्ठा saa7146_standard standard[];

अटल स्थिर काष्ठा v4l2_audio msp3400_v4l2_audio = अणु
	.index = 0,
	.name = "Television",
	.capability = V4L2_AUDCAP_STEREO
पूर्ण;

अटल पूर्णांक av7110_dvb_c_चयन(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा av7110 *av7110 = (काष्ठा av7110*)dev->ext_priv;
	u16 adचयन;
	पूर्णांक source, sync, err;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर ((vv->video_status & STATUS_OVERLAY) != 0) अणु
		vv->ov_suspend = vv->video_fh;
		err = saa7146_stop_preview(vv->video_fh); /* side effect: video_status is now 0, video_fh is शून्य */
		अगर (err != 0) अणु
			dprपूर्णांकk(2, "suspending video failed\n");
			vv->ov_suspend = शून्य;
		पूर्ण
	पूर्ण

	अगर (0 != av7110->current_input) अणु
		dprपूर्णांकk(1, "switching to analog TV:\n");
		adचयन = 1;
		source = SAA7146_HPS_SOURCE_PORT_B;
		sync = SAA7146_HPS_SYNC_PORT_B;
		स_नकल(standard, analog_standard, माप(काष्ठा saa7146_standard) * 2);

		चयन (av7110->current_input) अणु
		हाल 1:
			dprपूर्णांकk(1, "switching SAA7113 to Analog Tuner Input\n");
			msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, 0x0000); // loudspeaker source
			msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0009, 0x0000); // headphone source
			msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000a, 0x0000); // SCART 1 source
			msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000e, 0x3000); // FM matrix, mono
			msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, 0x4f00); // loudspeaker + headphone
			msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0007, 0x4f00); // SCART 1 volume

			अगर (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820) अणु
				अगर (ves1820_ग_लिखोreg(dev, 0x09, 0x0f, 0x60))
					dprपूर्णांकk(1, "setting band in demodulator failed\n");
			पूर्ण अन्यथा अगर (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297) अणु
				saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI); // TDA9819 pin9(STD)
				saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI); // TDA9819 pin30(VIF)
			पूर्ण
			अगर (i2c_ग_लिखोreg(av7110, 0x48, 0x02, 0xd0) != 1)
				dprपूर्णांकk(1, "saa7113 write failed @ card %d", av7110->dvb_adapter.num);
			अवरोध;
		हाल 2:
			dprपूर्णांकk(1, "switching SAA7113 to Video AV CVBS Input\n");
			अगर (i2c_ग_लिखोreg(av7110, 0x48, 0x02, 0xd2) != 1)
				dprपूर्णांकk(1, "saa7113 write failed @ card %d", av7110->dvb_adapter.num);
			अवरोध;
		हाल 3:
			dprपूर्णांकk(1, "switching SAA7113 to Video AV Y/C Input\n");
			अगर (i2c_ग_लिखोreg(av7110, 0x48, 0x02, 0xd9) != 1)
				dprपूर्णांकk(1, "saa7113 write failed @ card %d", av7110->dvb_adapter.num);
			अवरोध;
		शेष:
			dprपूर्णांकk(1, "switching SAA7113 to Input: AV7110: SAA7113: invalid input\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		adचयन = 0;
		source = SAA7146_HPS_SOURCE_PORT_A;
		sync = SAA7146_HPS_SYNC_PORT_A;
		स_नकल(standard, dvb_standard, माप(काष्ठा saa7146_standard) * 2);
		dprपूर्णांकk(1, "switching DVB mode\n");
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, 0x0220); // loudspeaker source
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0009, 0x0220); // headphone source
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000a, 0x0220); // SCART 1 source
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000e, 0x3000); // FM matrix, mono
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, 0x7f00); // loudspeaker + headphone
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0007, 0x7f00); // SCART 1 volume

		अगर (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820) अणु
			अगर (ves1820_ग_लिखोreg(dev, 0x09, 0x0f, 0x20))
				dprपूर्णांकk(1, "setting band in demodulator failed\n");
		पूर्ण अन्यथा अगर (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297) अणु
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTLO); // TDA9819 pin9(STD)
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO); // TDA9819 pin30(VIF)
		पूर्ण
	पूर्ण

	/* hmm, this करोes not करो anything!? */
	अगर (av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, adचयन))
		dprपूर्णांकk(1, "ADSwitch error\n");

	saa7146_set_hps_source_and_sync(dev, source, sync);

	अगर (vv->ov_suspend != शून्य) अणु
		saa7146_start_preview(vv->ov_suspend);
		vv->ov_suspend = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;
	u16 stereo_det;
	s8 stereo;

	dprपूर्णांकk(2, "VIDIOC_G_TUNER: %d\n", t->index);

	अगर (!av7110->analog_tuner_flags || t->index != 0)
		वापस -EINVAL;

	स_रखो(t, 0, माप(*t));
	strscpy((अक्षर *)t->name, "Television", माप(t->name));

	t->type = V4L2_TUNER_ANALOG_TV;
	t->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2 | V4L2_TUNER_CAP_SAP;
	t->rangelow = 772;	/* 48.25 MHZ / 62.5 kHz = 772, see fi1216mk2-specs, page 2 */
	t->rangehigh = 13684;	/* 855.25 MHz / 62.5 kHz = 13684 */
	/* FIXME: add the real संकेत strength here */
	t->संकेत = 0xffff;
	t->afc = 0;

	/* FIXME: standard / stereo detection is still broken */
	msp_पढ़ोreg(av7110, MSP_RD_DEM, 0x007e, &stereo_det);
	dprपूर्णांकk(1, "VIDIOC_G_TUNER: msp3400 TV standard detection: 0x%04x\n", stereo_det);
	msp_पढ़ोreg(av7110, MSP_RD_DSP, 0x0018, &stereo_det);
	dprपूर्णांकk(1, "VIDIOC_G_TUNER: msp3400 stereo detection: 0x%04x\n", stereo_det);
	stereo = (s8)(stereo_det >> 8);
	अगर (stereo > 0x10) अणु
		/* stereo */
		t->rxsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_MONO;
		t->audmode = V4L2_TUNER_MODE_STEREO;
	पूर्ण अन्यथा अगर (stereo < -0x10) अणु
		/* bilingual */
		t->rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		t->audmode = V4L2_TUNER_MODE_LANG1;
	पूर्ण अन्यथा /* mono */
		t->rxsubchans = V4L2_TUNER_SUB_MONO;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;
	u16 fm_matrix, src;
	dprपूर्णांकk(2, "VIDIOC_S_TUNER: %d\n", t->index);

	अगर (!av7110->analog_tuner_flags || av7110->current_input != 1)
		वापस -EINVAL;

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_STEREO:
		dprपूर्णांकk(2, "VIDIOC_S_TUNER: V4L2_TUNER_MODE_STEREO\n");
		fm_matrix = 0x3001; /* stereo */
		src = 0x0020;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		dprपूर्णांकk(2, "VIDIOC_S_TUNER: V4L2_TUNER_MODE_LANG1_LANG2\n");
		fm_matrix = 0x3000; /* bilingual */
		src = 0x0020;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
		dprपूर्णांकk(2, "VIDIOC_S_TUNER: V4L2_TUNER_MODE_LANG1\n");
		fm_matrix = 0x3000; /* mono */
		src = 0x0000;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		dprपूर्णांकk(2, "VIDIOC_S_TUNER: V4L2_TUNER_MODE_LANG2\n");
		fm_matrix = 0x3000; /* mono */
		src = 0x0010;
		अवरोध;
	शेष: /* हाल V4L2_TUNER_MODE_MONO: */
		dprपूर्णांकk(2, "VIDIOC_S_TUNER: TDA9840_SET_MONO\n");
		fm_matrix = 0x3000; /* mono */
		src = 0x0030;
		अवरोध;
	पूर्ण
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000e, fm_matrix);
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, src);
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0009, src);
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000a, src);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_G_FREQ: freq:0x%08x\n", f->frequency);

	अगर (!av7110->analog_tuner_flags || av7110->current_input != 1)
		वापस -EINVAL;

	स_रखो(f, 0, माप(*f));
	f->type = V4L2_TUNER_ANALOG_TV;
	f->frequency =	av7110->current_freq;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_S_FREQUENCY: freq:0x%08x\n", f->frequency);

	अगर (!av7110->analog_tuner_flags || av7110->current_input != 1)
		वापस -EINVAL;

	अगर (V4L2_TUNER_ANALOG_TV != f->type)
		वापस -EINVAL;

	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, 0xffe0); /* fast mute */
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0007, 0xffe0);

	/* tune in desired frequency */
	अगर (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820)
		ves1820_set_tv_freq(dev, f->frequency);
	अन्यथा अगर (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297)
		stv0297_set_tv_freq(dev, f->frequency);
	av7110->current_freq = f->frequency;

	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0015, 0x003f); /* start stereo detection */
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0015, 0x0000);
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, 0x4f00); /* loudspeaker + headphone */
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0007, 0x4f00); /* SCART 1 volume */
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_ENUMINPUT: %d\n", i->index);

	अगर (av7110->analog_tuner_flags) अणु
		अगर (i->index >= 4)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (i->index != 0)
			वापस -EINVAL;
	पूर्ण

	स_नकल(i, &inमाला_दो[i->index], माप(काष्ठा v4l2_input));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	*input = av7110->current_input;
	dprपूर्णांकk(2, "VIDIOC_G_INPUT: %d\n", *input);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_S_INPUT: %d\n", input);

	अगर (!av7110->analog_tuner_flags)
		वापस input ? -EINVAL : 0;

	अगर (input >= 4)
		वापस -EINVAL;

	av7110->current_input = input;
	वापस av7110_dvb_c_चयन(fh);
पूर्ण

अटल पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	dprपूर्णांकk(2, "VIDIOC_G_AUDIO: %d\n", a->index);
	अगर (a->index != 0)
		वापस -EINVAL;
	*a = msp3400_v4l2_audio;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_G_AUDIO: %d\n", a->index);
	अगर (a->index != 0)
		वापस -EINVAL;
	अगर (av7110->current_input >= 2)
		वापस -EINVAL;
	*a = msp3400_v4l2_audio;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audio *a)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_S_AUDIO: %d\n", a->index);
	अगर (av7110->current_input >= 2)
		वापस -EINVAL;
	वापस a->index ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक vidioc_g_sliced_vbi_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_sliced_vbi_cap *cap)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_G_SLICED_VBI_CAP\n");
	अगर (cap->type != V4L2_BUF_TYPE_SLICED_VBI_OUTPUT)
		वापस -EINVAL;
	अगर (FW_VERSION(av7110->arm_app) >= 0x2623) अणु
		cap->service_set = V4L2_SLICED_WSS_625;
		cap->service_lines[0][23] = V4L2_SLICED_WSS_625;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_G_FMT:\n");
	अगर (FW_VERSION(av7110->arm_app) < 0x2623)
		वापस -EINVAL;
	स_रखो(&f->fmt.sliced, 0, माप f->fmt.sliced);
	अगर (av7110->wssMode) अणु
		f->fmt.sliced.service_set = V4L2_SLICED_WSS_625;
		f->fmt.sliced.service_lines[0][23] = V4L2_SLICED_WSS_625;
		f->fmt.sliced.io_size = माप(काष्ठा v4l2_sliced_vbi_data);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *)dev->ext_priv;

	dprपूर्णांकk(2, "VIDIOC_S_FMT\n");
	अगर (FW_VERSION(av7110->arm_app) < 0x2623)
		वापस -EINVAL;
	अगर (f->fmt.sliced.service_set != V4L2_SLICED_WSS_625 &&
	    f->fmt.sliced.service_lines[0][23] != V4L2_SLICED_WSS_625) अणु
		स_रखो(&f->fmt.sliced, 0, माप(f->fmt.sliced));
		/* WSS controlled by firmware */
		av7110->wssMode = 0;
		av7110->wssData = 0;
		वापस av7110_fw_cmd(av7110, COMTYPE_ENCODER,
				     SetWSSConfig, 1, 0);
	पूर्ण अन्यथा अणु
		स_रखो(&f->fmt.sliced, 0, माप(f->fmt.sliced));
		f->fmt.sliced.service_set = V4L2_SLICED_WSS_625;
		f->fmt.sliced.service_lines[0][23] = V4L2_SLICED_WSS_625;
		f->fmt.sliced.io_size = माप(काष्ठा v4l2_sliced_vbi_data);
		/* WSS controlled by userspace */
		av7110->wssMode = 1;
		av7110->wssData = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक av7110_vbi_reset(काष्ठा file *file)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110*) dev->ext_priv;

	dprपूर्णांकk(2, "%s\n", __func__);
	av7110->wssMode = 0;
	av7110->wssData = 0;
	अगर (FW_VERSION(av7110->arm_app) < 0x2623)
		वापस 0;
	अन्यथा
		वापस av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetWSSConfig, 1, 0);
पूर्ण

अटल sमाप_प्रकार av7110_vbi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा av7110 *av7110 = (काष्ठा av7110*) dev->ext_priv;
	काष्ठा v4l2_sliced_vbi_data d;
	पूर्णांक rc;

	dprपूर्णांकk(2, "%s\n", __func__);
	अगर (FW_VERSION(av7110->arm_app) < 0x2623 || !av7110->wssMode || count != माप d)
		वापस -EINVAL;
	अगर (copy_from_user(&d, data, count))
		वापस -EFAULT;
	अगर ((d.id != 0 && d.id != V4L2_SLICED_WSS_625) || d.field != 0 || d.line != 23)
		वापस -EINVAL;
	अगर (d.id)
		av7110->wssData = ((d.data[1] << 8) & 0x3f00) | d.data[0];
	अन्यथा
		av7110->wssData = 0x8000;
	rc = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetWSSConfig, 2, 1, av7110->wssData);
	वापस (rc < 0) ? rc : count;
पूर्ण

/****************************************************************************
 * INITIALIZATION
 ****************************************************************************/

अटल u8 saa7113_init_regs[] = अणु
	0x02, 0xd0,
	0x03, 0x23,
	0x04, 0x00,
	0x05, 0x00,
	0x06, 0xe9,
	0x07, 0x0d,
	0x08, 0x98,
	0x09, 0x02,
	0x0a, 0x80,
	0x0b, 0x40,
	0x0c, 0x40,
	0x0d, 0x00,
	0x0e, 0x01,
	0x0f, 0x7c,
	0x10, 0x48,
	0x11, 0x0c,
	0x12, 0x8b,
	0x13, 0x1a,
	0x14, 0x00,
	0x15, 0x00,
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0x00,
	0x19, 0x00,
	0x1a, 0x00,
	0x1b, 0x00,
	0x1c, 0x00,
	0x1d, 0x00,
	0x1e, 0x00,

	0x41, 0x77,
	0x42, 0x77,
	0x43, 0x77,
	0x44, 0x77,
	0x45, 0x77,
	0x46, 0x77,
	0x47, 0x77,
	0x48, 0x77,
	0x49, 0x77,
	0x4a, 0x77,
	0x4b, 0x77,
	0x4c, 0x77,
	0x4d, 0x77,
	0x4e, 0x77,
	0x4f, 0x77,
	0x50, 0x77,
	0x51, 0x77,
	0x52, 0x77,
	0x53, 0x77,
	0x54, 0x77,
	0x55, 0x77,
	0x56, 0x77,
	0x57, 0xff,

	0xff
पूर्ण;


अटल काष्ठा saa7146_ext_vv av7110_vv_data_st;
अटल काष्ठा saa7146_ext_vv av7110_vv_data_c;

पूर्णांक av7110_init_analog_module(काष्ठा av7110 *av7110)
अणु
	u16 version1, version2;

	अगर (i2c_ग_लिखोreg(av7110, 0x80, 0x0, 0x80) == 1 &&
	    i2c_ग_लिखोreg(av7110, 0x80, 0x0, 0) == 1) अणु
		pr_info("DVB-C analog module @ card %d detected, initializing MSP3400\n",
			av7110->dvb_adapter.num);
		av7110->adac_type = DVB_ADAC_MSP34x0;
	पूर्ण अन्यथा अगर (i2c_ग_लिखोreg(av7110, 0x84, 0x0, 0x80) == 1 &&
		   i2c_ग_लिखोreg(av7110, 0x84, 0x0, 0) == 1) अणु
		pr_info("DVB-C analog module @ card %d detected, initializing MSP3415\n",
			av7110->dvb_adapter.num);
		av7110->adac_type = DVB_ADAC_MSP34x5;
	पूर्ण अन्यथा
		वापस -ENODEV;

	msleep(100); // the probing above resets the msp...
	msp_पढ़ोreg(av7110, MSP_RD_DSP, 0x001e, &version1);
	msp_पढ़ोreg(av7110, MSP_RD_DSP, 0x001f, &version2);
	dprपूर्णांकk(1, "dvb-ttpci: @ card %d MSP34xx version 0x%04x 0x%04x\n",
		av7110->dvb_adapter.num, version1, version2);
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0013, 0x0c00);
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, 0x7f00); // loudspeaker + headphone
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, 0x0220); // loudspeaker source
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0009, 0x0220); // headphone source
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0004, 0x7f00); // loudspeaker volume
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000a, 0x0220); // SCART 1 source
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0007, 0x7f00); // SCART 1 volume
	msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x000d, 0x1900); // prescale SCART

	अगर (i2c_ग_लिखोreg(av7110, 0x48, 0x01, 0x00)!=1) अणु
		pr_info("saa7113 not accessible\n");
	पूर्ण अन्यथा अणु
		u8 *i = saa7113_init_regs;

		अगर ((av7110->dev->pci->subप्रणाली_venकरोr == 0x110a) && (av7110->dev->pci->subप्रणाली_device == 0x0000)) अणु
			/* Fujitsu/Siemens DVB-Cable */
			av7110->analog_tuner_flags |= ANALOG_TUNER_VES1820;
		पूर्ण अन्यथा अगर ((av7110->dev->pci->subप्रणाली_venकरोr == 0x13c2) && (av7110->dev->pci->subप्रणाली_device == 0x0002)) अणु
			/* Hauppauge/TT DVB-C premium */
			av7110->analog_tuner_flags |= ANALOG_TUNER_VES1820;
		पूर्ण अन्यथा अगर ((av7110->dev->pci->subप्रणाली_venकरोr == 0x13c2) && (av7110->dev->pci->subप्रणाली_device == 0x000A)) अणु
			/* Hauppauge/TT DVB-C premium */
			av7110->analog_tuner_flags |= ANALOG_TUNER_STV0297;
		पूर्ण

		/* setup क्रम DVB by शेष */
		अगर (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820) अणु
			अगर (ves1820_ग_लिखोreg(av7110->dev, 0x09, 0x0f, 0x20))
				dprपूर्णांकk(1, "setting band in demodulator failed\n");
		पूर्ण अन्यथा अगर (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297) अणु
			saa7146_setgpio(av7110->dev, 1, SAA7146_GPIO_OUTLO); // TDA9819 pin9(STD)
			saa7146_setgpio(av7110->dev, 3, SAA7146_GPIO_OUTLO); // TDA9819 pin30(VIF)
		पूर्ण

		/* init the saa7113 */
		जबतक (*i != 0xff) अणु
			अगर (i2c_ग_लिखोreg(av7110, 0x48, i[0], i[1]) != 1) अणु
				dprपूर्णांकk(1, "saa7113 initialization failed @ card %d", av7110->dvb_adapter.num);
				अवरोध;
			पूर्ण
			i += 2;
		पूर्ण
		/* setup msp क्रम analog sound: B/G Dual-FM */
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x00bb, 0x02d0); // AD_CV
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0001,  3); // FIR1
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0001, 18); // FIR1
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0001, 27); // FIR1
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0001, 48); // FIR1
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0001, 66); // FIR1
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0001, 72); // FIR1
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005,  4); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005, 64); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005,  0); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005,  3); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005, 18); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005, 27); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005, 48); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005, 66); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0005, 72); // FIR2
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0083, 0xa000); // MODE_REG
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0093, 0x00aa); // DCO1_LO 5.74MHz
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x009b, 0x04fc); // DCO1_HI
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x00a3, 0x038e); // DCO2_LO 5.5MHz
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x00ab, 0x04c6); // DCO2_HI
		msp_ग_लिखोreg(av7110, MSP_WR_DEM, 0x0056, 0); // LOAD_REG 1/2
	पूर्ण

	स_नकल(standard, dvb_standard, माप(काष्ठा saa7146_standard) * 2);
	/* set dd1 stream a & b */
	saa7146_ग_लिखो(av7110->dev, DD1_STREAM_B, 0x00000000);
	saa7146_ग_लिखो(av7110->dev, DD1_INIT, 0x03000700);
	saa7146_ग_लिखो(av7110->dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	वापस 0;
पूर्ण

पूर्णांक av7110_init_v4l(काष्ठा av7110 *av7110)
अणु
	काष्ठा saa7146_dev* dev = av7110->dev;
	काष्ठा saa7146_ext_vv *vv_data;
	पूर्णांक ret;

	/* special हाल DVB-C: these cards have an analog tuner
	   plus need some special handling, so we have separate
	   saa7146_ext_vv data क्रम these... */
	अगर (av7110->analog_tuner_flags)
		vv_data = &av7110_vv_data_c;
	अन्यथा
		vv_data = &av7110_vv_data_st;
	ret = saa7146_vv_init(dev, vv_data);

	अगर (ret) अणु
		ERR("cannot init capture device. skipping\n");
		वापस -ENODEV;
	पूर्ण
	vv_data->vid_ops.vidioc_क्रमागत_input = vidioc_क्रमागत_input;
	vv_data->vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data->vid_ops.vidioc_s_input = vidioc_s_input;
	vv_data->vid_ops.vidioc_g_tuner = vidioc_g_tuner;
	vv_data->vid_ops.vidioc_s_tuner = vidioc_s_tuner;
	vv_data->vid_ops.vidioc_g_frequency = vidioc_g_frequency;
	vv_data->vid_ops.vidioc_s_frequency = vidioc_s_frequency;
	vv_data->vid_ops.vidioc_क्रमागतaudio = vidioc_क्रमागतaudio;
	vv_data->vid_ops.vidioc_g_audio = vidioc_g_audio;
	vv_data->vid_ops.vidioc_s_audio = vidioc_s_audio;
	vv_data->vid_ops.vidioc_g_fmt_vbi_cap = शून्य;

	vv_data->vbi_ops.vidioc_g_tuner = vidioc_g_tuner;
	vv_data->vbi_ops.vidioc_s_tuner = vidioc_s_tuner;
	vv_data->vbi_ops.vidioc_g_frequency = vidioc_g_frequency;
	vv_data->vbi_ops.vidioc_s_frequency = vidioc_s_frequency;
	vv_data->vbi_ops.vidioc_g_fmt_vbi_cap = शून्य;
	vv_data->vbi_ops.vidioc_g_sliced_vbi_cap = vidioc_g_sliced_vbi_cap;
	vv_data->vbi_ops.vidioc_g_fmt_sliced_vbi_out = vidioc_g_fmt_sliced_vbi_out;
	vv_data->vbi_ops.vidioc_s_fmt_sliced_vbi_out = vidioc_s_fmt_sliced_vbi_out;

	अगर (FW_VERSION(av7110->arm_app) < 0x2623)
		vv_data->capabilities &= ~V4L2_CAP_SLICED_VBI_OUTPUT;

	अगर (saa7146_रेजिस्टर_device(&av7110->v4l_dev, dev, "av7110", VFL_TYPE_VIDEO)) अणु
		ERR("cannot register capture device. skipping\n");
		saa7146_vv_release(dev);
		वापस -ENODEV;
	पूर्ण
	अगर (FW_VERSION(av7110->arm_app) >= 0x2623) अणु
		अगर (saa7146_रेजिस्टर_device(&av7110->vbi_dev, dev, "av7110", VFL_TYPE_VBI))
			ERR("cannot register vbi v4l2 device. skipping\n");
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक av7110_निकास_v4l(काष्ठा av7110 *av7110)
अणु
	काष्ठा saa7146_dev* dev = av7110->dev;

	saa7146_unरेजिस्टर_device(&av7110->v4l_dev, av7110->dev);
	saa7146_unरेजिस्टर_device(&av7110->vbi_dev, av7110->dev);

	saa7146_vv_release(dev);

	वापस 0;
पूर्ण



/* FIXME: these values are experimental values that look better than the
   values from the latest "official" driver -- at least क्रम me... (MiHu) */
अटल काष्ठा saa7146_standard standard[] = अणु
	अणु
		.name	= "PAL",	.id		= V4L2_STD_PAL_BG,
		.v_offset	= 0x15,	.v_field	= 288,
		.h_offset	= 0x48,	.h_pixels	= 708,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "NTSC",	.id		= V4L2_STD_NTSC,
		.v_offset	= 0x10,	.v_field	= 244,
		.h_offset	= 0x40,	.h_pixels	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	पूर्ण
पूर्ण;

अटल काष्ठा saa7146_standard analog_standard[] = अणु
	अणु
		.name	= "PAL",	.id		= V4L2_STD_PAL_BG,
		.v_offset	= 0x1b,	.v_field	= 288,
		.h_offset	= 0x08,	.h_pixels	= 708,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "NTSC",	.id		= V4L2_STD_NTSC,
		.v_offset	= 0x10,	.v_field	= 244,
		.h_offset	= 0x40,	.h_pixels	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	पूर्ण
पूर्ण;

अटल काष्ठा saa7146_standard dvb_standard[] = अणु
	अणु
		.name	= "PAL",	.id		= V4L2_STD_PAL_BG,
		.v_offset	= 0x14,	.v_field	= 288,
		.h_offset	= 0x48,	.h_pixels	= 708,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "NTSC",	.id		= V4L2_STD_NTSC,
		.v_offset	= 0x10,	.v_field	= 244,
		.h_offset	= 0x40,	.h_pixels	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	पूर्ण
पूर्ण;

अटल पूर्णांक std_callback(काष्ठा saa7146_dev* dev, काष्ठा saa7146_standard *std)
अणु
	काष्ठा av7110 *av7110 = (काष्ठा av7110*) dev->ext_priv;

	अगर (std->id & V4L2_STD_PAL) अणु
		av7110->vidmode = AV7110_VIDEO_MODE_PAL;
		av7110_set_vidmode(av7110, av7110->vidmode);
	पूर्ण
	अन्यथा अगर (std->id & V4L2_STD_NTSC) अणु
		av7110->vidmode = AV7110_VIDEO_MODE_NTSC;
		av7110_set_vidmode(av7110, av7110->vidmode);
	पूर्ण
	अन्यथा
		वापस -1;

	वापस 0;
पूर्ण


अटल काष्ठा saa7146_ext_vv av7110_vv_data_st = अणु
	.inमाला_दो		= 1,
	.audios		= 1,
	.capabilities	= V4L2_CAP_SLICED_VBI_OUTPUT | V4L2_CAP_AUDIO,
	.flags		= 0,

	.stds		= &standard[0],
	.num_stds	= ARRAY_SIZE(standard),
	.std_callback	= &std_callback,

	.vbi_fops.खोलो	= av7110_vbi_reset,
	.vbi_fops.release = av7110_vbi_reset,
	.vbi_fops.ग_लिखो	= av7110_vbi_ग_लिखो,
पूर्ण;

अटल काष्ठा saa7146_ext_vv av7110_vv_data_c = अणु
	.inमाला_दो		= 1,
	.audios		= 1,
	.capabilities	= V4L2_CAP_TUNER | V4L2_CAP_SLICED_VBI_OUTPUT | V4L2_CAP_AUDIO,
	.flags		= SAA7146_USE_PORT_B_FOR_VBI,

	.stds		= &standard[0],
	.num_stds	= ARRAY_SIZE(standard),
	.std_callback	= &std_callback,

	.vbi_fops.खोलो	= av7110_vbi_reset,
	.vbi_fops.release = av7110_vbi_reset,
	.vbi_fops.ग_लिखो	= av7110_vbi_ग_लिखो,
पूर्ण;

