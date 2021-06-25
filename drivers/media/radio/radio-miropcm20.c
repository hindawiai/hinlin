<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Miro PCM20 radio driver क्रम Linux radio support
 * (c) 1998 Ruurd Reitsma <R.A.Reitsma@wbmt.tudelft.nl>
 * Thanks to Norberto Pellici क्रम the ACI device पूर्णांकerface specअगरication
 * The API part is based on the radiotrack driver by M. Kirkwood
 * This driver relies on the aci mixer provided by the snd-miro
 * ALSA driver.
 * Look there क्रम further info...
 *
 * From the original miro RDS sources:
 *
 *  (c) 2001 Robert Siemer <Robert.Siemer@gmx.de>
 *
 *  Many thanks to Fred Seidel <seidel@metabox.de>, the
 *  designer of the RDS decoder hardware. With his help
 *  I was able to code this driver.
 *  Thanks also to Norberto Pellicci, Dominic Mounteney
 *  <DMounteney@pinnaclesys.com> and www.teleauskunft.de
 *  क्रम good hपूर्णांकs on finding Fred. It was somewhat hard
 *  to locate him here in Germany... [:
 *
 * This code has been reपूर्णांकroduced and converted to use
 * the new V4L2 RDS API by:
 *
 * Hans Verkuil <hans.verkuil@cisco.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <sound/aci.h>

#घोषणा RDS_DATASHIFT          2   /* Bit 2 */
#घोषणा RDS_DATAMASK        (1 << RDS_DATASHIFT)
#घोषणा RDS_BUSYMASK        0x10   /* Bit 4 */
#घोषणा RDS_CLOCKMASK       0x08   /* Bit 3 */
#घोषणा RDS_DATA(x)         (((x) >> RDS_DATASHIFT) & 1)

#घोषणा RDS_STATUS      0x01
#घोषणा RDS_STATIONNAME 0x02
#घोषणा RDS_TEXT        0x03
#घोषणा RDS_ALTFREQ     0x04
#घोषणा RDS_TIMEDATE    0x05
#घोषणा RDS_PI_CODE     0x06
#घोषणा RDS_PTYTATP     0x07
#घोषणा RDS_RESET       0x08
#घोषणा RDS_RXVALUE     0x09

अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0);
MODULE_PARM_DESC(radio_nr, "Set radio device number (/dev/radioX).  Default: -1 (autodetect)");

काष्ठा pcm20 अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *rds_pty;
	काष्ठा v4l2_ctrl *rds_ps_name;
	काष्ठा v4l2_ctrl *rds_radio_test;
	काष्ठा v4l2_ctrl *rds_ta;
	काष्ठा v4l2_ctrl *rds_tp;
	काष्ठा v4l2_ctrl *rds_ms;
	/* thपढ़ो क्रम periodic RDS status checking */
	काष्ठा task_काष्ठा *kthपढ़ो;
	अचिन्हित दीर्घ freq;
	u32 audmode;
	काष्ठा snd_miro_aci *aci;
	काष्ठा mutex lock;
पूर्ण;

अटल काष्ठा pcm20 pcm20_card = अणु
	.freq = 87 * 16000,
	.audmode = V4L2_TUNER_MODE_STEREO,
पूर्ण;


अटल पूर्णांक rds_रुकोपढ़ो(काष्ठा snd_miro_aci *aci)
अणु
	u8 byte;
	पूर्णांक i = 2000;

	करो अणु
		byte = inb(aci->aci_port + ACI_REG_RDS);
		i--;
	पूर्ण जबतक ((byte & RDS_BUSYMASK) && i);

	/*
	 * It's magic, but without this the data that you पढ़ो later on
	 * is unreliable and full of bit errors. With this 1 usec delay
	 * everything is fine.
	 */
	udelay(1);
	वापस i ? byte : -1;
पूर्ण

अटल पूर्णांक rds_rawग_लिखो(काष्ठा snd_miro_aci *aci, u8 byte)
अणु
	अगर (rds_रुकोपढ़ो(aci) >= 0) अणु
		outb(byte, aci->aci_port + ACI_REG_RDS);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक rds_ग_लिखो(काष्ठा snd_miro_aci *aci, u8 byte)
अणु
	u8 sendbuffer[8];
	पूर्णांक i;

	क्रम (i = 7; i >= 0; i--)
		sendbuffer[7 - i] = (byte & (1 << i)) ? RDS_DATAMASK : 0;
	sendbuffer[0] |= RDS_CLOCKMASK;

	क्रम (i = 0; i < 8; i++)
		rds_rawग_लिखो(aci, sendbuffer[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक rds_पढ़ोcycle_noरुको(काष्ठा snd_miro_aci *aci)
अणु
	outb(0, aci->aci_port + ACI_REG_RDS);
	वापस rds_रुकोपढ़ो(aci);
पूर्ण

अटल पूर्णांक rds_पढ़ोcycle(काष्ठा snd_miro_aci *aci)
अणु
	अगर (rds_rawग_लिखो(aci, 0) < 0)
		वापस -1;
	वापस rds_रुकोपढ़ो(aci);
पूर्ण

अटल पूर्णांक rds_ack(काष्ठा snd_miro_aci *aci)
अणु
	पूर्णांक i = rds_पढ़ोcycle(aci);

	अगर (i < 0)
		वापस -1;
	अगर (i & RDS_DATAMASK)
		वापस 0;  /* ACK  */
	वापस 1;  /* NACK */
पूर्ण

अटल पूर्णांक rds_cmd(काष्ठा snd_miro_aci *aci, u8 cmd, u8 databuffer[], u8 datasize)
अणु
	पूर्णांक i, j;

	rds_ग_लिखो(aci, cmd);

	/* RDS_RESET करोesn't need further processing */
	अगर (cmd == RDS_RESET)
		वापस 0;
	अगर (rds_ack(aci))
		वापस -EIO;
	अगर (datasize == 0)
		वापस 0;

	/* to be able to use rds_पढ़ोcycle_noरुको()
	   I have to रुकोपढ़ो() here */
	अगर (rds_रुकोपढ़ो(aci) < 0)
		वापस -1;

	स_रखो(databuffer, 0, datasize);

	क्रम (i = 0; i < 8 * datasize; i++) अणु
		j = rds_पढ़ोcycle_noरुको(aci);
		अगर (j < 0)
			वापस -EIO;
		databuffer[i / 8] |= RDS_DATA(j) << (7 - (i % 8));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcm20_setfreq(काष्ठा pcm20 *dev, अचिन्हित दीर्घ freq)
अणु
	अचिन्हित अक्षर freql;
	अचिन्हित अक्षर freqh;
	काष्ठा snd_miro_aci *aci = dev->aci;

	freq /= 160;
	अगर (!(aci->aci_version == 0x07 || aci->aci_version >= 0xb0))
		freq /= 10;  /* I करोn't know exactly which version
			      * needs this hack */
	freql = freq & 0xff;
	freqh = freq >> 8;

	rds_cmd(aci, RDS_RESET, शून्य, 0);
	वापस snd_aci_cmd(aci, ACI_WRITE_TUNE, freql, freqh);
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *v)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);

	strscpy(v->driver, "Miro PCM20", माप(v->driver));
	strscpy(v->card, "Miro PCM20", माप(v->card));
	snम_लिखो(v->bus_info, माप(v->bus_info), "ISA:%s", dev->v4l2_dev.name);
	वापस 0;
पूर्ण

अटल bool sanitize(अक्षर *p, पूर्णांक size)
अणु
	पूर्णांक i;
	bool ret = true;

	क्रम (i = 0; i < size; i++) अणु
		अगर (p[i] < 32) अणु
			p[i] = ' ';
			ret = false;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);
	पूर्णांक res;
	u8 buf;

	अगर (v->index)
		वापस -EINVAL;
	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = 87*16000;
	v->rangehigh = 108*16000;
	res = snd_aci_cmd(dev->aci, ACI_READ_TUNERSTATION, -1, -1);
	v->संकेत = (res & 0x80) ? 0 : 0xffff;
	/* Note: stereo detection करोes not work अगर the audio is muted,
	   it will शेष to mono in that हाल. */
	res = snd_aci_cmd(dev->aci, ACI_READ_TUNERSTEREO, -1, -1);
	v->rxsubchans = (res & 0x40) ? V4L2_TUNER_SUB_MONO :
					V4L2_TUNER_SUB_STEREO;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_CONTROLS;
	v->audmode = dev->audmode;
	res = rds_cmd(dev->aci, RDS_RXVALUE, &buf, 1);
	अगर (res >= 0 && buf)
		v->rxsubchans |= V4L2_TUNER_SUB_RDS;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);

	अगर (v->index)
		वापस -EINVAL;
	अगर (v->audmode > V4L2_TUNER_MODE_STEREO)
		dev->audmode = V4L2_TUNER_MODE_STEREO;
	अन्यथा
		dev->audmode = v->audmode;
	snd_aci_cmd(dev->aci, ACI_SET_TUNERMONO,
			dev->audmode == V4L2_TUNER_MODE_MONO, -1);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;

	f->type = V4L2_TUNER_RADIO;
	f->frequency = dev->freq;
	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	dev->freq = clamp_t(u32, f->frequency, 87 * 16000U, 108 * 16000U);
	pcm20_setfreq(dev, dev->freq);
	वापस 0;
पूर्ण

अटल पूर्णांक pcm20_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा pcm20 *dev = container_of(ctrl->handler, काष्ठा pcm20, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		snd_aci_cmd(dev->aci, ACI_SET_TUNERMUTE, ctrl->val, -1);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pcm20_thपढ़ो(व्योम *data)
अणु
	काष्ठा pcm20 *dev = data;
	स्थिर अचिन्हित no_rds_start_counter = 5;
	स्थिर अचिन्हित sleep_msecs = 2000;
	अचिन्हित no_rds_counter = no_rds_start_counter;

	क्रम (;;) अणु
		अक्षर text_buffer[66];
		u8 buf;
		पूर्णांक res;

		msleep_पूर्णांकerruptible(sleep_msecs);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		res = rds_cmd(dev->aci, RDS_RXVALUE, &buf, 1);
		अगर (res)
			जारी;
		अगर (buf == 0) अणु
			अगर (no_rds_counter == 0)
				जारी;
			no_rds_counter--;
			अगर (no_rds_counter)
				जारी;

			/*
			 * No RDS seen क्रम no_rds_start_counter * sleep_msecs
			 * milliseconds, clear all RDS controls to their
			 * शेष values.
			 */
			v4l2_ctrl_s_ctrl_string(dev->rds_ps_name, "");
			v4l2_ctrl_s_ctrl(dev->rds_ms, 1);
			v4l2_ctrl_s_ctrl(dev->rds_ta, 0);
			v4l2_ctrl_s_ctrl(dev->rds_tp, 0);
			v4l2_ctrl_s_ctrl(dev->rds_pty, 0);
			v4l2_ctrl_s_ctrl_string(dev->rds_radio_test, "");
			जारी;
		पूर्ण
		no_rds_counter = no_rds_start_counter;

		res = rds_cmd(dev->aci, RDS_STATUS, &buf, 1);
		अगर (res)
			जारी;
		अगर ((buf >> 3) & 1) अणु
			res = rds_cmd(dev->aci, RDS_STATIONNAME, text_buffer, 8);
			text_buffer[8] = 0;
			अगर (!res && sanitize(text_buffer, 8))
				v4l2_ctrl_s_ctrl_string(dev->rds_ps_name, text_buffer);
		पूर्ण
		अगर ((buf >> 6) & 1) अणु
			u8 pty;

			res = rds_cmd(dev->aci, RDS_PTYTATP, &pty, 1);
			अगर (!res) अणु
				v4l2_ctrl_s_ctrl(dev->rds_ms, !!(pty & 0x01));
				v4l2_ctrl_s_ctrl(dev->rds_ta, !!(pty & 0x02));
				v4l2_ctrl_s_ctrl(dev->rds_tp, !!(pty & 0x80));
				v4l2_ctrl_s_ctrl(dev->rds_pty, (pty >> 2) & 0x1f);
			पूर्ण
		पूर्ण
		अगर ((buf >> 4) & 1) अणु
			res = rds_cmd(dev->aci, RDS_TEXT, text_buffer, 65);
			text_buffer[65] = 0;
			अगर (!res && sanitize(text_buffer + 1, 64))
				v4l2_ctrl_s_ctrl_string(dev->rds_radio_test, text_buffer + 1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcm20_खोलो(काष्ठा file *file)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);
	पूर्णांक res = v4l2_fh_खोलो(file);

	अगर (!res && v4l2_fh_is_singular_file(file) &&
	    IS_ERR_OR_शून्य(dev->kthपढ़ो)) अणु
		dev->kthपढ़ो = kthपढ़ो_run(pcm20_thपढ़ो, dev, "%s",
					   dev->v4l2_dev.name);
		अगर (IS_ERR(dev->kthपढ़ो)) अणु
			v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
			v4l2_fh_release(file);
			वापस PTR_ERR(dev->kthपढ़ो);
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक pcm20_release(काष्ठा file *file)
अणु
	काष्ठा pcm20 *dev = video_drvdata(file);

	अगर (v4l2_fh_is_singular_file(file) && !IS_ERR_OR_शून्य(dev->kthपढ़ो)) अणु
		kthपढ़ो_stop(dev->kthपढ़ो);
		dev->kthपढ़ो = शून्य;
	पूर्ण
	वापस v4l2_fh_release(file);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations pcm20_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= pcm20_खोलो,
	.poll		= v4l2_ctrl_poll,
	.release	= pcm20_release,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops pcm20_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops pcm20_ctrl_ops = अणु
	.s_ctrl = pcm20_s_ctrl,
पूर्ण;

अटल पूर्णांक __init pcm20_init(व्योम)
अणु
	काष्ठा pcm20 *dev = &pcm20_card;
	काष्ठा v4l2_device *v4l2_dev = &dev->v4l2_dev;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक res;

	dev->aci = snd_aci_get_aci();
	अगर (dev->aci == शून्य) अणु
		v4l2_err(v4l2_dev,
			 "you must load the snd-miro driver first!\n");
		वापस -ENODEV;
	पूर्ण
	strscpy(v4l2_dev->name, "radio-miropcm20", माप(v4l2_dev->name));
	mutex_init(&dev->lock);

	res = v4l2_device_रेजिस्टर(शून्य, v4l2_dev);
	अगर (res < 0) अणु
		v4l2_err(v4l2_dev, "could not register v4l2_device\n");
		वापस -EINVAL;
	पूर्ण

	hdl = &dev->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 7);
	v4l2_ctrl_new_std(hdl, &pcm20_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	dev->rds_pty = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_RDS_RX_PTY, 0, 0x1f, 1, 0);
	dev->rds_ps_name = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_RDS_RX_PS_NAME, 0, 8, 8, 0);
	dev->rds_radio_test = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_RDS_RX_RADIO_TEXT, 0, 64, 64, 0);
	dev->rds_ta = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
	dev->rds_tp = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_RDS_RX_TRAFFIC_PROGRAM, 0, 1, 1, 0);
	dev->rds_ms = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_RDS_RX_MUSIC_SPEECH, 0, 1, 1, 1);
	v4l2_dev->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		res = hdl->error;
		v4l2_err(v4l2_dev, "Could not register control\n");
		जाओ err_hdl;
	पूर्ण
	strscpy(dev->vdev.name, v4l2_dev->name, माप(dev->vdev.name));
	dev->vdev.v4l2_dev = v4l2_dev;
	dev->vdev.fops = &pcm20_fops;
	dev->vdev.ioctl_ops = &pcm20_ioctl_ops;
	dev->vdev.release = video_device_release_empty;
	dev->vdev.lock = &dev->lock;
	dev->vdev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO |
				V4L2_CAP_RDS_CAPTURE;
	video_set_drvdata(&dev->vdev, dev);
	snd_aci_cmd(dev->aci, ACI_SET_TUNERMONO,
			dev->audmode == V4L2_TUNER_MODE_MONO, -1);
	pcm20_setfreq(dev, dev->freq);

	अगर (video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_RADIO, radio_nr) < 0)
		जाओ err_hdl;

	v4l2_info(v4l2_dev, "Mirosound PCM20 Radio tuner\n");
	वापस 0;
err_hdl:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_device_unरेजिस्टर(v4l2_dev);
	वापस -EINVAL;
पूर्ण

MODULE_AUTHOR("Ruurd Reitsma, Krzysztof Helt");
MODULE_DESCRIPTION("A driver for the Miro PCM20 radio card.");
MODULE_LICENSE("GPL");

अटल व्योम __निकास pcm20_cleanup(व्योम)
अणु
	काष्ठा pcm20 *dev = &pcm20_card;

	video_unरेजिस्टर_device(&dev->vdev);
	snd_aci_cmd(dev->aci, ACI_SET_TUNERMUTE, 1, -1);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
पूर्ण

module_init(pcm20_init);
module_निकास(pcm20_cleanup);
