<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* SF16-FMI, SF16-FMP and SF16-FMD radio driver क्रम Linux radio support
 * heavily based on rtrack driver...
 * (c) 1997 M. Kirkwood
 * (c) 1998 Petr Vandrovec, vandrove@vc.cvut.cz
 *
 * Fitted to new पूर्णांकerface by Alan Cox <alan@lxorguk.ukuu.org.uk>
 * Made working and cleaned up functions <mikael.hedin@irf.se>
 * Support क्रम ISAPnP by Ladislav Michl <ladis@psi.cz>
 *
 * Notes on the hardware
 *
 *  Frequency control is करोne digitally -- ie out(port,encodefreq(95.8));
 *  No volume control - only mute/unmute - you have to use line volume
 *  control on SB-part of SF16-FMI/SF16-FMP/SF16-FMD
 *
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/kernel.h>	/* __setup			*/
#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/delay.h>	/* udelay			*/
#समावेश <linux/isapnp.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs		*/
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश "lm7000.h"

MODULE_AUTHOR("Petr Vandrovec, vandrove@vc.cvut.cz and M. Kirkwood");
MODULE_DESCRIPTION("A driver for the SF16-FMI, SF16-FMP and SF16-FMD radio.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.3");

अटल पूर्णांक io = -1;
अटल पूर्णांक radio_nr = -1;

module_param(io, पूर्णांक, 0);
MODULE_PARM_DESC(io, "I/O address of the SF16-FMI/SF16-FMP/SF16-FMD card (0x284 or 0x384)");
module_param(radio_nr, पूर्णांक, 0);

काष्ठा fmi
अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा video_device vdev;
	पूर्णांक io;
	bool mute;
	u32 curfreq; /* freq in kHz */
	काष्ठा mutex lock;
पूर्ण;

अटल काष्ठा fmi fmi_card;
अटल काष्ठा pnp_dev *dev;
अटल bool pnp_attached;

#घोषणा RSF16_MINFREQ (87U * 16000)
#घोषणा RSF16_MAXFREQ (108U * 16000)

#घोषणा FMI_BIT_TUN_CE		(1 << 0)
#घोषणा FMI_BIT_TUN_CLK		(1 << 1)
#घोषणा FMI_BIT_TUN_DATA	(1 << 2)
#घोषणा FMI_BIT_VOL_SW		(1 << 3)
#घोषणा FMI_BIT_TUN_STRQ	(1 << 4)

अटल व्योम fmi_set_pins(व्योम *handle, u8 pins)
अणु
	काष्ठा fmi *fmi = handle;
	u8 bits = FMI_BIT_TUN_STRQ;

	अगर (!fmi->mute)
		bits |= FMI_BIT_VOL_SW;

	अगर (pins & LM7000_DATA)
		bits |= FMI_BIT_TUN_DATA;
	अगर (pins & LM7000_CLK)
		bits |= FMI_BIT_TUN_CLK;
	अगर (pins & LM7000_CE)
		bits |= FMI_BIT_TUN_CE;

	mutex_lock(&fmi->lock);
	outb_p(bits, fmi->io);
	mutex_unlock(&fmi->lock);
पूर्ण

अटल अंतरभूत व्योम fmi_mute(काष्ठा fmi *fmi)
अणु
	mutex_lock(&fmi->lock);
	outb(0x00, fmi->io);
	mutex_unlock(&fmi->lock);
पूर्ण

अटल अंतरभूत व्योम fmi_unmute(काष्ठा fmi *fmi)
अणु
	mutex_lock(&fmi->lock);
	outb(0x08, fmi->io);
	mutex_unlock(&fmi->lock);
पूर्ण

अटल अंतरभूत पूर्णांक fmi_माला_लोigstr(काष्ठा fmi *fmi)
अणु
	पूर्णांक val;
	पूर्णांक res;

	mutex_lock(&fmi->lock);
	val = fmi->mute ? 0x00 : 0x08;	/* mute/unmute */
	outb(val, fmi->io);
	outb(val | 0x10, fmi->io);
	msleep(143);		/* was schedule_समयout(HZ/7) */
	res = (पूर्णांक)inb(fmi->io + 1);
	outb(val, fmi->io);

	mutex_unlock(&fmi->lock);
	वापस (res & 2) ? 0 : 0xFFFF;
पूर्ण

अटल व्योम fmi_set_freq(काष्ठा fmi *fmi)
अणु
	fmi->curfreq = clamp(fmi->curfreq, RSF16_MINFREQ, RSF16_MAXFREQ);
	/* rounding in steps of 800 to match the freq
	   that will be used */
	lm7000_set_freq((fmi->curfreq / 800) * 800, fmi, fmi_set_pins);
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *v)
अणु
	strscpy(v->driver, "radio-sf16fmi", माप(v->driver));
	strscpy(v->card, "SF16-FMI/FMP/FMD radio", माप(v->card));
	strscpy(v->bus_info, "ISA:radio-sf16fmi", माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *v)
अणु
	काष्ठा fmi *fmi = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = RSF16_MINFREQ;
	v->rangehigh = RSF16_MAXFREQ;
	v->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
	v->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LOW;
	v->audmode = V4L2_TUNER_MODE_STEREO;
	v->संकेत = fmi_माला_लोigstr(fmi);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *v)
अणु
	वापस v->index ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा fmi *fmi = video_drvdata(file);

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	fmi->curfreq = f->frequency;
	fmi_set_freq(fmi);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *f)
अणु
	काष्ठा fmi *fmi = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = fmi->curfreq;
	वापस 0;
पूर्ण

अटल पूर्णांक fmi_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fmi *fmi = container_of(ctrl->handler, काष्ठा fmi, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		अगर (ctrl->val)
			fmi_mute(fmi);
		अन्यथा
			fmi_unmute(fmi);
		fmi->mute = ctrl->val;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fmi_ctrl_ops = अणु
	.s_ctrl = fmi_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations fmi_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops fmi_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* ladis: this is my card. करोes any other types exist? */
अटल काष्ठा isapnp_device_id id_table[] = अणु
		/* SF16-FMI */
	अणु	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOR('M','F','R'), ISAPNP_FUNCTION(0xad10), 0पूर्ण,
		/* SF16-FMD */
	अणु	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOR('M','F','R'), ISAPNP_FUNCTION(0xad12), 0पूर्ण,
	अणु	ISAPNP_CARD_END, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(isapnp, id_table);

अटल पूर्णांक __init isapnp_fmi_probe(व्योम)
अणु
	पूर्णांक i = 0;

	जबतक (id_table[i].card_venकरोr != 0 && dev == शून्य) अणु
		dev = pnp_find_dev(शून्य, id_table[i].venकरोr,
				   id_table[i].function, शून्य);
		i++;
	पूर्ण

	अगर (!dev)
		वापस -ENODEV;
	अगर (pnp_device_attach(dev) < 0)
		वापस -EAGAIN;
	अगर (pnp_activate_dev(dev) < 0) अणु
		prपूर्णांकk(KERN_ERR "radio-sf16fmi: PnP configure failed (out of resources?)\n");
		pnp_device_detach(dev);
		वापस -ENOMEM;
	पूर्ण
	अगर (!pnp_port_valid(dev, 0)) अणु
		pnp_device_detach(dev);
		वापस -ENODEV;
	पूर्ण

	i = pnp_port_start(dev, 0);
	prपूर्णांकk(KERN_INFO "radio-sf16fmi: PnP reports card at %#x\n", i);

	वापस i;
पूर्ण

अटल पूर्णांक __init fmi_init(व्योम)
अणु
	काष्ठा fmi *fmi = &fmi_card;
	काष्ठा v4l2_device *v4l2_dev = &fmi->v4l2_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &fmi->hdl;
	पूर्णांक res, i;
	पूर्णांक probe_ports[] = अणु 0, 0x284, 0x384 पूर्ण;

	अगर (io < 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(probe_ports); i++) अणु
			io = probe_ports[i];
			अगर (io == 0) अणु
				io = isapnp_fmi_probe();
				अगर (io < 0)
					जारी;
				pnp_attached = true;
			पूर्ण
			अगर (!request_region(io, 2, "radio-sf16fmi")) अणु
				अगर (pnp_attached)
					pnp_device_detach(dev);
				io = -1;
				जारी;
			पूर्ण
			अगर (pnp_attached ||
			    ((inb(io) & 0xf9) == 0xf9 && (inb(io) & 0x4) == 0))
				अवरोध;
			release_region(io, 2);
			io = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!request_region(io, 2, "radio-sf16fmi")) अणु
			prपूर्णांकk(KERN_ERR "radio-sf16fmi: port %#x already in use\n", io);
			वापस -EBUSY;
		पूर्ण
		अगर (inb(io) == 0xff) अणु
			prपूर्णांकk(KERN_ERR "radio-sf16fmi: card not present at %#x\n", io);
			release_region(io, 2);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अगर (io < 0) अणु
		prपूर्णांकk(KERN_ERR "radio-sf16fmi: no cards found\n");
		वापस -ENODEV;
	पूर्ण

	strscpy(v4l2_dev->name, "sf16fmi", माप(v4l2_dev->name));
	fmi->io = io;

	res = v4l2_device_रेजिस्टर(शून्य, v4l2_dev);
	अगर (res < 0) अणु
		release_region(fmi->io, 2);
		अगर (pnp_attached)
			pnp_device_detach(dev);
		v4l2_err(v4l2_dev, "Could not register v4l2_device\n");
		वापस res;
	पूर्ण

	v4l2_ctrl_handler_init(hdl, 1);
	v4l2_ctrl_new_std(hdl, &fmi_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_dev->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		res = hdl->error;
		v4l2_err(v4l2_dev, "Could not register controls\n");
		v4l2_ctrl_handler_मुक्त(hdl);
		v4l2_device_unरेजिस्टर(v4l2_dev);
		वापस res;
	पूर्ण

	strscpy(fmi->vdev.name, v4l2_dev->name, माप(fmi->vdev.name));
	fmi->vdev.v4l2_dev = v4l2_dev;
	fmi->vdev.fops = &fmi_fops;
	fmi->vdev.ioctl_ops = &fmi_ioctl_ops;
	fmi->vdev.release = video_device_release_empty;
	fmi->vdev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	video_set_drvdata(&fmi->vdev, fmi);

	mutex_init(&fmi->lock);

	/* mute card and set शेष frequency */
	fmi->mute = true;
	fmi->curfreq = RSF16_MINFREQ;
	fmi_set_freq(fmi);

	अगर (video_रेजिस्टर_device(&fmi->vdev, VFL_TYPE_RADIO, radio_nr) < 0) अणु
		v4l2_ctrl_handler_मुक्त(hdl);
		v4l2_device_unरेजिस्टर(v4l2_dev);
		release_region(fmi->io, 2);
		अगर (pnp_attached)
			pnp_device_detach(dev);
		वापस -EINVAL;
	पूर्ण

	v4l2_info(v4l2_dev, "card driver at 0x%x\n", fmi->io);
	वापस 0;
पूर्ण

अटल व्योम __निकास fmi_निकास(व्योम)
अणु
	काष्ठा fmi *fmi = &fmi_card;

	v4l2_ctrl_handler_मुक्त(&fmi->hdl);
	video_unरेजिस्टर_device(&fmi->vdev);
	v4l2_device_unरेजिस्टर(&fmi->v4l2_dev);
	release_region(fmi->io, 2);
	अगर (dev && pnp_attached)
		pnp_device_detach(dev);
पूर्ण

module_init(fmi_init);
module_निकास(fmi_निकास);
