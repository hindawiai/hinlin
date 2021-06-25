<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * driver/media/radio/radio-tea5764.c
 *
 * Driver क्रम TEA5764 radio chip क्रम linux 2.6.
 * This driver is क्रम TEA5764 chip from NXP, used in EZX phones from Motorola.
 * The I2C protocol is used क्रम communicate with chip.
 *
 * Based in radio-tea5761.c Copyright (C) 2005 Nokia Corporation
 *
 *  Copyright (c) 2008 Fabio Belavenuto <belavenuto@gmail.com>
 *
 * History:
 * 2008-12-06   Fabio Belavenuto <belavenuto@gmail.com>
 *              initial code
 *
 * TODO:
 *  add platक्रमm_data support क्रम IRQs platक्रमm dependencies
 *  add RDS support
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>			/* Initdata			*/
#समावेश <linux/videodev2.h>		/* kernel radio काष्ठाs		*/
#समावेश <linux/i2c.h>			/* I2C				*/
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

#घोषणा DRIVER_VERSION	"0.0.2"

#घोषणा DRIVER_AUTHOR	"Fabio Belavenuto <belavenuto@gmail.com>"
#घोषणा DRIVER_DESC	"A driver for the TEA5764 radio chip for EZX Phones."

#घोषणा PINFO(क्रमmat, ...)\
	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": "\
		DRIVER_VERSION ": " क्रमmat "\n", ## __VA_ARGS__)
#घोषणा PWARN(क्रमmat, ...)\
	prपूर्णांकk(KERN_WARNING KBUILD_MODNAME ": "\
		DRIVER_VERSION ": " क्रमmat "\n", ## __VA_ARGS__)
# define PDEBUG(क्रमmat, ...)\
	prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": "\
		DRIVER_VERSION ": " क्रमmat "\n", ## __VA_ARGS__)

/* Frequency limits in MHz -- these are European values.  For Japanese
devices, that would be 76000 and 91000.  */
#घोषणा FREQ_MIN  87500U
#घोषणा FREQ_MAX 108000U
#घोषणा FREQ_MUL 16

/* TEA5764 रेजिस्टरs */
#घोषणा TEA5764_MANID		0x002b
#घोषणा TEA5764_CHIPID		0x5764

#घोषणा TEA5764_INTREG_BLMSK	0x0001
#घोषणा TEA5764_INTREG_FRRMSK	0x0002
#घोषणा TEA5764_INTREG_LEVMSK	0x0008
#घोषणा TEA5764_INTREG_IFMSK	0x0010
#घोषणा TEA5764_INTREG_BLMFLAG	0x0100
#घोषणा TEA5764_INTREG_FRRFLAG	0x0200
#घोषणा TEA5764_INTREG_LEVFLAG	0x0800
#घोषणा TEA5764_INTREG_IFFLAG	0x1000

#घोषणा TEA5764_FRQSET_SUD	0x8000
#घोषणा TEA5764_FRQSET_SM	0x4000

#घोषणा TEA5764_TNCTRL_PUPD1	0x8000
#घोषणा TEA5764_TNCTRL_PUPD0	0x4000
#घोषणा TEA5764_TNCTRL_BLIM	0x2000
#घोषणा TEA5764_TNCTRL_SWPM	0x1000
#घोषणा TEA5764_TNCTRL_IFCTC	0x0800
#घोषणा TEA5764_TNCTRL_AFM	0x0400
#घोषणा TEA5764_TNCTRL_SMUTE	0x0200
#घोषणा TEA5764_TNCTRL_SNC	0x0100
#घोषणा TEA5764_TNCTRL_MU	0x0080
#घोषणा TEA5764_TNCTRL_SSL1	0x0040
#घोषणा TEA5764_TNCTRL_SSL0	0x0020
#घोषणा TEA5764_TNCTRL_HLSI	0x0010
#घोषणा TEA5764_TNCTRL_MST	0x0008
#घोषणा TEA5764_TNCTRL_SWP	0x0004
#घोषणा TEA5764_TNCTRL_DTC	0x0002
#घोषणा TEA5764_TNCTRL_AHLSI	0x0001

#घोषणा TEA5764_TUNCHK_LEVEL(x)	(((x) & 0x00F0) >> 4)
#घोषणा TEA5764_TUNCHK_IFCNT(x) (((x) & 0xFE00) >> 9)
#घोषणा TEA5764_TUNCHK_TUNTO	0x0100
#घोषणा TEA5764_TUNCHK_LD	0x0008
#घोषणा TEA5764_TUNCHK_STEREO	0x0004

#घोषणा TEA5764_TESTREG_TRIGFR	0x0800

काष्ठा tea5764_regs अणु
	u16 पूर्णांकreg;				/* INTFLAG & INTMSK */
	u16 frqset;				/* FRQSETMSB & FRQSETLSB */
	u16 tnctrl;				/* TNCTRL1 & TNCTRL2 */
	u16 frqchk;				/* FRQCHKMSB & FRQCHKLSB */
	u16 tunchk;				/* IFCHK & LEVCHK */
	u16 testreg;				/* TESTBITS & TESTMODE */
	u16 rdsstat;				/* RDSSTAT1 & RDSSTAT2 */
	u16 rdslb;				/* RDSLBMSB & RDSLBLSB */
	u16 rdspb;				/* RDSPBMSB & RDSPBLSB */
	u16 rdsbc;				/* RDSBBC & RDSGBC */
	u16 rdsctrl;				/* RDSCTRL1 & RDSCTRL2 */
	u16 rdsbbl;				/* PAUSEDET & RDSBBL */
	u16 manid;				/* MANID1 & MANID2 */
	u16 chipid;				/* CHIPID1 & CHIPID2 */
पूर्ण __attribute__ ((packed));

काष्ठा tea5764_ग_लिखो_regs अणु
	u8 पूर्णांकreg;				/* INTMSK */
	__be16 frqset;				/* FRQSETMSB & FRQSETLSB */
	__be16 tnctrl;				/* TNCTRL1 & TNCTRL2 */
	__be16 testreg;				/* TESTBITS & TESTMODE */
	__be16 rdsctrl;				/* RDSCTRL1 & RDSCTRL2 */
	__be16 rdsbbl;				/* PAUSEDET & RDSBBL */
पूर्ण __attribute__ ((packed));

#अगर_घोषित CONFIG_RADIO_TEA5764_XTAL
#घोषणा RADIO_TEA5764_XTAL 1
#अन्यथा
#घोषणा RADIO_TEA5764_XTAL 0
#पूर्ण_अगर

अटल पूर्णांक radio_nr = -1;
अटल पूर्णांक use_xtal = RADIO_TEA5764_XTAL;

काष्ठा tea5764_device अणु
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	काष्ठा i2c_client		*i2c_client;
	काष्ठा video_device		vdev;
	काष्ठा tea5764_regs		regs;
	काष्ठा mutex			mutex;
पूर्ण;

/* I2C code related */
अटल पूर्णांक tea5764_i2c_पढ़ो(काष्ठा tea5764_device *radio)
अणु
	पूर्णांक i;
	u16 *p = (u16 *) &radio->regs;

	काष्ठा i2c_msg msgs[1] = अणु
		अणु	.addr = radio->i2c_client->addr,
			.flags = I2C_M_RD,
			.len = माप(radio->regs),
			.buf = (व्योम *)&radio->regs
		पूर्ण,
	पूर्ण;
	अगर (i2c_transfer(radio->i2c_client->adapter, msgs, 1) != 1)
		वापस -EIO;
	क्रम (i = 0; i < माप(काष्ठा tea5764_regs) / माप(u16); i++)
		p[i] = __be16_to_cpu((__क्रमce __be16)p[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक tea5764_i2c_ग_लिखो(काष्ठा tea5764_device *radio)
अणु
	काष्ठा tea5764_ग_लिखो_regs wr;
	काष्ठा tea5764_regs *r = &radio->regs;
	काष्ठा i2c_msg msgs[1] = अणु
		अणु
			.addr = radio->i2c_client->addr,
			.len = माप(wr),
			.buf = (व्योम *)&wr
		पूर्ण,
	पूर्ण;
	wr.पूर्णांकreg  = r->पूर्णांकreg & 0xff;
	wr.frqset  = __cpu_to_be16(r->frqset);
	wr.tnctrl  = __cpu_to_be16(r->tnctrl);
	wr.testreg = __cpu_to_be16(r->testreg);
	wr.rdsctrl = __cpu_to_be16(r->rdsctrl);
	wr.rdsbbl  = __cpu_to_be16(r->rdsbbl);
	अगर (i2c_transfer(radio->i2c_client->adapter, msgs, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल व्योम tea5764_घातer_up(काष्ठा tea5764_device *radio)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;

	अगर (!(r->tnctrl & TEA5764_TNCTRL_PUPD0)) अणु
		r->tnctrl &= ~(TEA5764_TNCTRL_AFM | TEA5764_TNCTRL_MU |
			       TEA5764_TNCTRL_HLSI);
		अगर (!use_xtal)
			r->testreg |= TEA5764_TESTREG_TRIGFR;
		अन्यथा
			r->testreg &= ~TEA5764_TESTREG_TRIGFR;

		r->tnctrl |= TEA5764_TNCTRL_PUPD0;
		tea5764_i2c_ग_लिखो(radio);
	पूर्ण
पूर्ण

अटल व्योम tea5764_घातer_करोwn(काष्ठा tea5764_device *radio)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;

	अगर (r->tnctrl & TEA5764_TNCTRL_PUPD0) अणु
		r->tnctrl &= ~TEA5764_TNCTRL_PUPD0;
		tea5764_i2c_ग_लिखो(radio);
	पूर्ण
पूर्ण

अटल व्योम tea5764_set_freq(काष्ठा tea5764_device *radio, पूर्णांक freq)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;

	/* क्रमmula: (freq [+ or -] 225000) / 8192 */
	अगर (r->tnctrl & TEA5764_TNCTRL_HLSI)
		r->frqset = (freq + 225000) / 8192;
	अन्यथा
		r->frqset = (freq - 225000) / 8192;
पूर्ण

अटल पूर्णांक tea5764_get_freq(काष्ठा tea5764_device *radio)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;

	अगर (r->tnctrl & TEA5764_TNCTRL_HLSI)
		वापस (r->frqchk * 8192) - 225000;
	अन्यथा
		वापस (r->frqchk * 8192) + 225000;
पूर्ण

/* tune an frequency, freq is defined by v4l's TUNER_LOW, i.e. 1/16th kHz */
अटल व्योम tea5764_tune(काष्ठा tea5764_device *radio, पूर्णांक freq)
अणु
	tea5764_set_freq(radio, freq);
	अगर (tea5764_i2c_ग_लिखो(radio))
		PWARN("Could not set frequency!");
पूर्ण

अटल व्योम tea5764_set_auकरोut_mode(काष्ठा tea5764_device *radio, पूर्णांक audmode)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;
	पूर्णांक tnctrl = r->tnctrl;

	अगर (audmode == V4L2_TUNER_MODE_MONO)
		r->tnctrl |= TEA5764_TNCTRL_MST;
	अन्यथा
		r->tnctrl &= ~TEA5764_TNCTRL_MST;
	अगर (tnctrl != r->tnctrl)
		tea5764_i2c_ग_लिखो(radio);
पूर्ण

अटल पूर्णांक tea5764_get_auकरोut_mode(काष्ठा tea5764_device *radio)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;

	अगर (r->tnctrl & TEA5764_TNCTRL_MST)
		वापस V4L2_TUNER_MODE_MONO;
	अन्यथा
		वापस V4L2_TUNER_MODE_STEREO;
पूर्ण

अटल व्योम tea5764_mute(काष्ठा tea5764_device *radio, पूर्णांक on)
अणु
	काष्ठा tea5764_regs *r = &radio->regs;
	पूर्णांक tnctrl = r->tnctrl;

	अगर (on)
		r->tnctrl |= TEA5764_TNCTRL_MU;
	अन्यथा
		r->tnctrl &= ~TEA5764_TNCTRL_MU;
	अगर (tnctrl != r->tnctrl)
		tea5764_i2c_ग_लिखो(radio);
पूर्ण

/* V4L2 vidioc */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा tea5764_device *radio = video_drvdata(file);
	काष्ठा video_device *dev = &radio->vdev;

	strscpy(v->driver, dev->dev.driver->name, माप(v->driver));
	strscpy(v->card, dev->name, माप(v->card));
	snम_लिखो(v->bus_info, माप(v->bus_info),
		 "I2C:%s", dev_name(&dev->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा tea5764_device *radio = video_drvdata(file);
	काष्ठा tea5764_regs *r = &radio->regs;

	अगर (v->index > 0)
		वापस -EINVAL;

	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	tea5764_i2c_पढ़ो(radio);
	v->rangelow   = FREQ_MIN * FREQ_MUL;
	v->rangehigh  = FREQ_MAX * FREQ_MUL;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	अगर (r->tunchk & TEA5764_TUNCHK_STEREO)
		v->rxsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		v->rxsubchans = V4L2_TUNER_SUB_MONO;
	v->audmode = tea5764_get_auकरोut_mode(radio);
	v->संकेत = TEA5764_TUNCHK_LEVEL(r->tunchk) * 0xffff / 0xf;
	v->afc = TEA5764_TUNCHK_IFCNT(r->tunchk);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा tea5764_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	tea5764_set_auकरोut_mode(radio, v->audmode);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा tea5764_device *radio = video_drvdata(file);
	अचिन्हित freq = f->frequency;

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;
	अगर (freq == 0) अणु
		/* We special हाल this as a घातer करोwn control. */
		tea5764_घातer_करोwn(radio);
		/* Yes, that's what is वापसed in this हाल. This
		   whole special हाल is non-compliant and should really
		   be replaced with something better, but changing this
		   might well अवरोध code that depends on this behavior.
		   So we keep it as-is. */
		वापस -EINVAL;
	पूर्ण
	freq = clamp(freq, FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL);
	tea5764_घातer_up(radio);
	tea5764_tune(radio, (freq * 125) / 2);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा tea5764_device *radio = video_drvdata(file);
	काष्ठा tea5764_regs *r = &radio->regs;

	अगर (f->tuner != 0)
		वापस -EINVAL;
	tea5764_i2c_पढ़ो(radio);
	f->type = V4L2_TUNER_RADIO;
	अगर (r->tnctrl & TEA5764_TNCTRL_PUPD0)
		f->frequency = (tea5764_get_freq(radio) * 2) / 125;
	अन्यथा
		f->frequency = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tea5764_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tea5764_device *radio =
		container_of(ctrl->handler, काष्ठा tea5764_device, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		tea5764_mute(radio, ctrl->val);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops tea5764_ctrl_ops = अणु
	.s_ctrl = tea5764_s_ctrl,
पूर्ण;

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations tea5764_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops tea5764_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* V4L2 पूर्णांकerface */
अटल स्थिर काष्ठा video_device tea5764_radio_ढाँचा = अणु
	.name		= "TEA5764 FM-Radio",
	.fops           = &tea5764_fops,
	.ioctl_ops	= &tea5764_ioctl_ops,
	.release	= video_device_release_empty,
पूर्ण;

/* I2C probe: check अगर the device exists and रेजिस्टर with v4l अगर it is */
अटल पूर्णांक tea5764_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tea5764_device *radio;
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा tea5764_regs *r;
	पूर्णांक ret;

	PDEBUG("probe");
	radio = kzalloc(माप(काष्ठा tea5764_device), GFP_KERNEL);
	अगर (!radio)
		वापस -ENOMEM;

	v4l2_dev = &radio->v4l2_dev;
	ret = v4l2_device_रेजिस्टर(&client->dev, v4l2_dev);
	अगर (ret < 0) अणु
		v4l2_err(v4l2_dev, "could not register v4l2_device\n");
		जाओ errfr;
	पूर्ण

	hdl = &radio->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 1);
	v4l2_ctrl_new_std(hdl, &tea5764_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_dev->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		ret = hdl->error;
		v4l2_err(v4l2_dev, "Could not register controls\n");
		जाओ errunreg;
	पूर्ण

	mutex_init(&radio->mutex);
	radio->i2c_client = client;
	ret = tea5764_i2c_पढ़ो(radio);
	अगर (ret)
		जाओ errunreg;
	r = &radio->regs;
	PDEBUG("chipid = %04X, manid = %04X", r->chipid, r->manid);
	अगर (r->chipid != TEA5764_CHIPID ||
		(r->manid & 0x0fff) != TEA5764_MANID) अणु
		PWARN("This chip is not a TEA5764!");
		ret = -EINVAL;
		जाओ errunreg;
	पूर्ण

	radio->vdev = tea5764_radio_ढाँचा;

	i2c_set_clientdata(client, radio);
	video_set_drvdata(&radio->vdev, radio);
	radio->vdev.lock = &radio->mutex;
	radio->vdev.v4l2_dev = v4l2_dev;
	radio->vdev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;

	/* initialize and घातer off the chip */
	tea5764_i2c_पढ़ो(radio);
	tea5764_set_auकरोut_mode(radio, V4L2_TUNER_MODE_STEREO);
	tea5764_mute(radio, 1);
	tea5764_घातer_करोwn(radio);

	ret = video_रेजिस्टर_device(&radio->vdev, VFL_TYPE_RADIO, radio_nr);
	अगर (ret < 0) अणु
		PWARN("Could not register video device!");
		जाओ errunreg;
	पूर्ण

	PINFO("registered.");
	वापस 0;
errunreg:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_device_unरेजिस्टर(v4l2_dev);
errfr:
	kमुक्त(radio);
	वापस ret;
पूर्ण

अटल पूर्णांक tea5764_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tea5764_device *radio = i2c_get_clientdata(client);

	PDEBUG("remove");
	अगर (radio) अणु
		tea5764_घातer_करोwn(radio);
		video_unरेजिस्टर_device(&radio->vdev);
		v4l2_ctrl_handler_मुक्त(&radio->ctrl_handler);
		v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
		kमुक्त(radio);
	पूर्ण
	वापस 0;
पूर्ण

/* I2C subप्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा i2c_device_id tea5764_id[] = अणु
	अणु "radio-tea5764", 0 पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tea5764_id);

अटल काष्ठा i2c_driver tea5764_i2c_driver = अणु
	.driver = अणु
		.name = "radio-tea5764",
	पूर्ण,
	.probe = tea5764_i2c_probe,
	.हटाओ = tea5764_i2c_हटाओ,
	.id_table = tea5764_id,
पूर्ण;

module_i2c_driver(tea5764_i2c_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_param(use_xtal, पूर्णांक, 0);
MODULE_PARM_DESC(use_xtal, "Chip have a xtal connected in board");
module_param(radio_nr, पूर्णांक, 0);
MODULE_PARM_DESC(radio_nr, "video4linux device number to use");
