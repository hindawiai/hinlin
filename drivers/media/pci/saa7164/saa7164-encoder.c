<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश "saa7164.h"

#घोषणा ENCODER_MAX_BITRATE 6500000
#घोषणा ENCODER_MIN_BITRATE 1000000
#घोषणा ENCODER_DEF_BITRATE 5000000

/*
 * This is a dummy non-zero value क्रम the sizeimage field of v4l2_pix_क्रमmat.
 * It is not actually used क्रम anything since this driver करोes not support
 * stream I/O, only पढ़ो(), and because this driver produces an MPEG stream
 * and not discrete frames. But the V4L2 spec करोesn't allow क्रम this value
 * to be 0, so set it to 0x10000 instead.
 *
 * If we ever change this driver to support stream I/O, then this field
 * will be the size of the streaming buffers.
 */
#घोषणा SAA7164_SIZEIMAGE (0x10000)

अटल काष्ठा saa7164_tvnorm saa7164_tvnorms[] = अणु
	अणु
		.name      = "NTSC-M",
		.id        = V4L2_STD_NTSC_M,
	पूर्ण, अणु
		.name      = "NTSC-JP",
		.id        = V4L2_STD_NTSC_M_JP,
	पूर्ण
पूर्ण;

/* Take the encoder configuration क्रमm the port काष्ठा and
 * flush it to the hardware.
 */
अटल व्योम saa7164_encoder_configure(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	port->encoder_params.width = port->width;
	port->encoder_params.height = port->height;
	port->encoder_params.is_50hz =
		(port->encodernorm.id & V4L2_STD_625_50) != 0;

	/* Set up the DIF (enable it) क्रम analog mode by शेष */
	saa7164_api_initialize_dअगर(port);

	/* Configure the correct video standard */
	saa7164_api_configure_dअगर(port, port->encodernorm.id);

	/* Ensure the audio decoder is correct configured */
	saa7164_api_set_audio_std(port);
पूर्ण

अटल पूर्णांक saa7164_encoder_buffers_dealloc(काष्ठा saa7164_port *port)
अणु
	काष्ठा list_head *c, *n, *p, *q, *l, *v;
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा saa7164_user_buffer *ubuf;

	/* Remove any allocated buffers */
	mutex_lock(&port->dmaqueue_lock);

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) dmaqueue\n", __func__, port->nr);
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु
		buf = list_entry(c, काष्ठा saa7164_buffer, list);
		list_del(c);
		saa7164_buffer_dealloc(buf);
	पूर्ण

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) used\n", __func__, port->nr);
	list_क्रम_each_safe(p, q, &port->list_buf_used.list) अणु
		ubuf = list_entry(p, काष्ठा saa7164_user_buffer, list);
		list_del(p);
		saa7164_buffer_dealloc_user(ubuf);
	पूर्ण

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) free\n", __func__, port->nr);
	list_क्रम_each_safe(l, v, &port->list_buf_मुक्त.list) अणु
		ubuf = list_entry(l, काष्ठा saa7164_user_buffer, list);
		list_del(l);
		saa7164_buffer_dealloc_user(ubuf);
	पूर्ण

	mutex_unlock(&port->dmaqueue_lock);
	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) done\n", __func__, port->nr);

	वापस 0;
पूर्ण

/* Dynamic buffer चयन at encoder start समय */
अटल पूर्णांक saa7164_encoder_buffers_alloc(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा saa7164_user_buffer *ubuf;
	काष्ठा पंचांगHWStreamParameters *params = &port->hw_streamingparams;
	पूर्णांक result = -ENODEV, i;
	पूर्णांक len = 0;

	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	अगर (port->encoder_params.stream_type ==
		V4L2_MPEG_STREAM_TYPE_MPEG2_PS) अणु
		dprपूर्णांकk(DBGLVL_ENC,
			"%s() type=V4L2_MPEG_STREAM_TYPE_MPEG2_PS\n",
			__func__);
		params->samplesperline = 128;
		params->numberoflines = 256;
		params->pitch = 128;
		params->numpagetables = 2 +
			((SAA7164_PS_NUMBER_OF_LINES * 128) / PAGE_SIZE);
	पूर्ण अन्यथा
	अगर (port->encoder_params.stream_type ==
		V4L2_MPEG_STREAM_TYPE_MPEG2_TS) अणु
		dprपूर्णांकk(DBGLVL_ENC,
			"%s() type=V4L2_MPEG_STREAM_TYPE_MPEG2_TS\n",
			__func__);
		params->samplesperline = 188;
		params->numberoflines = 312;
		params->pitch = 188;
		params->numpagetables = 2 +
			((SAA7164_TS_NUMBER_OF_LINES * 188) / PAGE_SIZE);
	पूर्ण अन्यथा
		BUG();

	/* Init and establish शेषs */
	params->bitspersample = 8;
	params->linethreshold = 0;
	params->pagetablelistvirt = शून्य;
	params->pagetablelistphys = शून्य;
	params->numpagetableentries = port->hwcfg.buffercount;

	/* Allocate the PCI resources, buffers (hard) */
	क्रम (i = 0; i < port->hwcfg.buffercount; i++) अणु
		buf = saa7164_buffer_alloc(port,
			params->numberoflines *
			params->pitch);

		अगर (!buf) अणु
			prपूर्णांकk(KERN_ERR "%s() failed (errno = %d), unable to allocate buffer\n",
				__func__, result);
			result = -ENOMEM;
			जाओ failed;
		पूर्ण अन्यथा अणु

			mutex_lock(&port->dmaqueue_lock);
			list_add_tail(&buf->list, &port->dmaqueue.list);
			mutex_unlock(&port->dmaqueue_lock);

		पूर्ण
	पूर्ण

	/* Allocate some kernel buffers क्रम copying
	 * to userpsace.
	 */
	len = params->numberoflines * params->pitch;

	अगर (encoder_buffers < 16)
		encoder_buffers = 16;
	अगर (encoder_buffers > 512)
		encoder_buffers = 512;

	क्रम (i = 0; i < encoder_buffers; i++) अणु

		ubuf = saa7164_buffer_alloc_user(dev, len);
		अगर (ubuf) अणु
			mutex_lock(&port->dmaqueue_lock);
			list_add_tail(&ubuf->list, &port->list_buf_मुक्त.list);
			mutex_unlock(&port->dmaqueue_lock);
		पूर्ण

	पूर्ण

	result = 0;

failed:
	वापस result;
पूर्ण

अटल पूर्णांक saa7164_encoder_initialize(काष्ठा saa7164_port *port)
अणु
	saa7164_encoder_configure(port);
	वापस 0;
पूर्ण

/* -- V4L2 --------------------------------------------------------- */
पूर्णांक saa7164_s_std(काष्ठा saa7164_port *port, v4l2_std_id id)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	अचिन्हित पूर्णांक i;

	dprपूर्णांकk(DBGLVL_ENC, "%s(id=0x%x)\n", __func__, (u32)id);

	क्रम (i = 0; i < ARRAY_SIZE(saa7164_tvnorms); i++) अणु
		अगर (id & saa7164_tvnorms[i].id)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(saa7164_tvnorms))
		वापस -EINVAL;

	port->encodernorm = saa7164_tvnorms[i];
	port->std = id;

	/* Update the audio decoder जबतक is not running in
	 * स्वतः detect mode.
	 */
	saa7164_api_set_audio_std(port);

	dprपूर्णांकk(DBGLVL_ENC, "%s(id=0x%x) OK\n", __func__, (u32)id);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_s_std(fh->port, id);
पूर्ण

पूर्णांक saa7164_g_std(काष्ठा saa7164_port *port, v4l2_std_id *id)
अणु
	*id = port->std;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_g_std(fh->port, id);
पूर्ण

पूर्णांक saa7164_क्रमागत_input(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *i)
अणु
	अटल स्थिर अक्षर * स्थिर inमाला_दो[] = अणु
		"tuner", "composite", "svideo", "aux",
		"composite 2", "svideo 2", "aux 2"
	पूर्ण;
	पूर्णांक n;

	अगर (i->index >= 7)
		वापस -EINVAL;

	strscpy(i->name, inमाला_दो[i->index], माप(i->name));

	अगर (i->index == 0)
		i->type = V4L2_INPUT_TYPE_TUNER;
	अन्यथा
		i->type  = V4L2_INPUT_TYPE_CAMERA;

	क्रम (n = 0; n < ARRAY_SIZE(saa7164_tvnorms); n++)
		i->std |= saa7164_tvnorms[n].id;

	वापस 0;
पूर्ण

पूर्णांक saa7164_g_input(काष्ठा saa7164_port *port, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	अगर (saa7164_api_get_videomux(port) != SAA_OK)
		वापस -EIO;

	*i = (port->mux_input - 1);

	dprपूर्णांकk(DBGLVL_ENC, "%s() input=%d\n", __func__, *i);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_g_input(fh->port, i);
पूर्ण

पूर्णांक saa7164_s_input(काष्ठा saa7164_port *port, अचिन्हित पूर्णांक i)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_ENC, "%s() input=%d\n", __func__, i);

	अगर (i >= 7)
		वापस -EINVAL;

	port->mux_input = i + 1;

	अगर (saa7164_api_set_videomux(port) != SAA_OK)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_s_input(fh->port, i);
पूर्ण

पूर्णांक saa7164_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	काष्ठा saa7164_dev *dev = port->dev;

	अगर (0 != t->index)
		वापस -EINVAL;

	strscpy(t->name, "tuner", माप(t->name));
	t->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO;
	t->rangelow = SAA7164_TV_MIN_FREQ;
	t->rangehigh = SAA7164_TV_MAX_FREQ;

	dprपूर्णांकk(DBGLVL_ENC, "VIDIOC_G_TUNER: tuner type %d\n", t->type);

	वापस 0;
पूर्ण

पूर्णांक saa7164_s_tuner(काष्ठा file *file, व्योम *priv,
			   स्थिर काष्ठा v4l2_tuner *t)
अणु
	अगर (0 != t->index)
		वापस -EINVAL;

	/* Update the A/V core */
	वापस 0;
पूर्ण

पूर्णांक saa7164_g_frequency(काष्ठा saa7164_port *port, काष्ठा v4l2_frequency *f)
अणु
	अगर (f->tuner)
		वापस -EINVAL;

	f->frequency = port->freq;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_g_frequency(fh->port, f);
पूर्ण

पूर्णांक saa7164_s_frequency(काष्ठा saa7164_port *port,
			स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_port *tsport;
	काष्ठा dvb_frontend *fe;

	/* TODO: Pull this क्रम the std */
	काष्ठा analog_parameters params = अणु
		.mode      = V4L2_TUNER_ANALOG_TV,
		.audmode   = V4L2_TUNER_MODE_STEREO,
		.std       = port->encodernorm.id,
		.frequency = f->frequency
	पूर्ण;

	/* Stop the encoder */
	dprपूर्णांकk(DBGLVL_ENC, "%s() frequency=%d tuner=%d\n", __func__,
		f->frequency, f->tuner);

	अगर (f->tuner != 0)
		वापस -EINVAL;

	port->freq = clamp(f->frequency,
			   SAA7164_TV_MIN_FREQ, SAA7164_TV_MAX_FREQ);

	/* Update the hardware */
	अगर (port->nr == SAA7164_PORT_ENC1)
		tsport = &dev->ports[SAA7164_PORT_TS1];
	अन्यथा अगर (port->nr == SAA7164_PORT_ENC2)
		tsport = &dev->ports[SAA7164_PORT_TS2];
	अन्यथा
		BUG();

	fe = tsport->dvb.frontend;

	अगर (fe && fe->ops.tuner_ops.set_analog_params)
		fe->ops.tuner_ops.set_analog_params(fe, &params);
	अन्यथा
		prपूर्णांकk(KERN_ERR "%s() No analog tuner, aborting\n", __func__);

	saa7164_encoder_initialize(port);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_s_frequency(fh->port, f);
पूर्ण

अटल पूर्णांक saa7164_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa7164_port *port =
		container_of(ctrl->handler, काष्ठा saa7164_port, ctrl_handler);
	काष्ठा saa7164_encoder_params *params = &port->encoder_params;
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		port->ctl_brightness = ctrl->val;
		saa7164_api_set_usercontrol(port, PU_BRIGHTNESS_CONTROL);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		port->ctl_contrast = ctrl->val;
		saa7164_api_set_usercontrol(port, PU_CONTRAST_CONTROL);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		port->ctl_saturation = ctrl->val;
		saa7164_api_set_usercontrol(port, PU_SATURATION_CONTROL);
		अवरोध;
	हाल V4L2_CID_HUE:
		port->ctl_hue = ctrl->val;
		saa7164_api_set_usercontrol(port, PU_HUE_CONTROL);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		port->ctl_sharpness = ctrl->val;
		saa7164_api_set_usercontrol(port, PU_SHARPNESS_CONTROL);
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
		port->ctl_volume = ctrl->val;
		saa7164_api_set_audio_volume(port, port->ctl_volume);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		params->bitrate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		params->stream_type = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MUTE:
		params->ctl_mute = ctrl->val;
		ret = saa7164_api_audio_mute(port, params->ctl_mute);
		अगर (ret != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__,
				ret);
			ret = -EIO;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		params->ctl_aspect = ctrl->val;
		ret = saa7164_api_set_aspect_ratio(port);
		अगर (ret != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__,
				ret);
			ret = -EIO;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		params->bitrate_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		params->refdist = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		params->bitrate_peak = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		params->gop_size = ctrl->val;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
	काष्ठा v4l2_capability *cap)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	काष्ठा saa7164_dev *dev = port->dev;

	strscpy(cap->driver, dev->name, माप(cap->driver));
	strscpy(cap->card, saa7164_boards[dev->board].name,
		माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(dev->pci));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_TUNER | V4L2_CAP_VBI_CAPTURE |
			    V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
	काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_MPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    = SAA7164_SIZEIMAGE;
	f->fmt.pix.field        = V4L2_FIELD_INTERLACED;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.width        = port->width;
	f->fmt.pix.height       = port->height;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7164_encoder_stop_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() stop transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_ENC, "%s()    Stopped\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_encoder_acquire_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_ACQUIRE);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() acquire transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_ENC, "%s() Acquired\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_encoder_छोड़ो_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_PAUSE);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() pause transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_ENC, "%s()   Paused\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Firmware is very winकरोws centric, meaning you have to transition
 * the part through AVStream / KS Winकरोws stages, क्रमwards or backwards.
 * States are: stopped, acquired (h/w), छोड़ोd, started.
 * We have to leave here will all of the soft buffers on the मुक्त list,
 * अन्यथा the cfg_post() func won't have soft buffers to correctly configure.
 */
अटल पूर्णांक saa7164_encoder_stop_streaming(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा saa7164_user_buffer *ubuf;
	काष्ठा list_head *c, *n;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d)\n", __func__, port->nr);

	ret = saa7164_encoder_छोड़ो_port(port);
	ret = saa7164_encoder_acquire_port(port);
	ret = saa7164_encoder_stop_port(port);

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) Hardware stopped\n", __func__,
		port->nr);

	/* Reset the state of any allocated buffer resources */
	mutex_lock(&port->dmaqueue_lock);

	/* Reset the hard and soft buffer state */
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु
		buf = list_entry(c, काष्ठा saa7164_buffer, list);
		buf->flags = SAA7164_BUFFER_FREE;
		buf->pos = 0;
	पूर्ण

	list_क्रम_each_safe(c, n, &port->list_buf_used.list) अणु
		ubuf = list_entry(c, काष्ठा saa7164_user_buffer, list);
		ubuf->pos = 0;
		list_move_tail(&ubuf->list, &port->list_buf_मुक्त.list);
	पूर्ण

	mutex_unlock(&port->dmaqueue_lock);

	/* Free any allocated resources */
	saa7164_encoder_buffers_dealloc(port);

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) Released\n", __func__, port->nr);

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_encoder_start_streaming(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक result, ret = 0;

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d)\n", __func__, port->nr);

	port->करोne_first_पूर्णांकerrupt = 0;

	/* allocate all of the PCIe DMA buffer resources on the fly,
	 * allowing चयनing between TS and PS payloads without
	 * requiring a complete driver reload.
	 */
	saa7164_encoder_buffers_alloc(port);

	/* Configure the encoder with any cache values */
	saa7164_api_set_encoder(port);
	saa7164_api_get_encoder(port);

	/* Place the empty buffers on the hardware */
	saa7164_buffer_cfg_port(port);

	/* Acquire the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_ACQUIRE);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() acquire transition failed, res = 0x%x\n",
			__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
		अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
			prपूर्णांकk(KERN_ERR "%s() acquire/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण
		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_ENC, "%s()   Acquired\n", __func__);

	/* Pause the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_PAUSE);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() pause transition failed, res = 0x%x\n",
				__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
		अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
			prपूर्णांकk(KERN_ERR "%s() pause/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण

		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_ENC, "%s()   Paused\n", __func__);

	/* Start the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_RUN);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() run transition failed, result = 0x%x\n",
				__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
		अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
			prपूर्णांकk(KERN_ERR "%s() run/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण

		ret = -EIO;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_ENC, "%s()   Running\n", __func__);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा saa7164_dev *dev;
	काष्ठा saa7164_port *port;
	काष्ठा saa7164_encoder_fh *fh;

	port = (काष्ठा saa7164_port *)video_get_drvdata(video_devdata(file));
	अगर (!port)
		वापस -ENODEV;

	dev = port->dev;

	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	/* allocate + initialize per filehandle data */
	fh = kzalloc(माप(*fh), GFP_KERNEL);
	अगर (शून्य == fh)
		वापस -ENOMEM;

	fh->port = port;
	v4l2_fh_init(&fh->fh, video_devdata(file));
	v4l2_fh_add(&fh->fh);
	file->निजी_data = fh;

	वापस 0;
पूर्ण

अटल पूर्णांक fops_release(काष्ठा file *file)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	/* Shut device करोwn on last बंद */
	अगर (atomic_cmpxchg(&fh->v4l_पढ़ोing, 1, 0) == 1) अणु
		अगर (atomic_dec_वापस(&port->v4l_पढ़ोer_count) == 0) अणु
			/* stop mpeg capture then cancel buffers */
			saa7164_encoder_stop_streaming(port);
		पूर्ण
	पूर्ण

	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	kमुक्त(fh);

	वापस 0;
पूर्ण

अटल काष्ठा
saa7164_user_buffer *saa7164_enc_next_buf(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_user_buffer *ubuf = शून्य;
	काष्ठा saa7164_dev *dev = port->dev;
	u32 crc;

	mutex_lock(&port->dmaqueue_lock);
	अगर (!list_empty(&port->list_buf_used.list)) अणु
		ubuf = list_first_entry(&port->list_buf_used.list,
			काष्ठा saa7164_user_buffer, list);

		अगर (crc_checking) अणु
			crc = crc32(0, ubuf->data, ubuf->actual_size);
			अगर (crc != ubuf->crc) अणु
				prपूर्णांकk(KERN_ERR
		"%s() ubuf %p crc became invalid, was 0x%x became 0x%x\n",
					__func__,
					ubuf, ubuf->crc, crc);
			पूर्ण
		पूर्ण

	पूर्ण
	mutex_unlock(&port->dmaqueue_lock);

	dprपूर्णांकk(DBGLVL_ENC, "%s() returns %p\n", __func__, ubuf);

	वापस ubuf;
पूर्ण

अटल sमाप_प्रकार fops_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
	माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	काष्ठा saa7164_user_buffer *ubuf = शून्य;
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret = 0;
	पूर्णांक rem, cnt;
	u8 *p;

	port->last_पढ़ो_msecs_dअगरf = port->last_पढ़ो_msecs;
	port->last_पढ़ो_msecs = jअगरfies_to_msecs(jअगरfies);
	port->last_पढ़ो_msecs_dअगरf = port->last_पढ़ो_msecs -
		port->last_पढ़ो_msecs_dअगरf;

	saa7164_histogram_update(&port->पढ़ो_पूर्णांकerval,
		port->last_पढ़ो_msecs_dअगरf);

	अगर (*pos) अणु
		prपूर्णांकk(KERN_ERR "%s() ESPIPE\n", __func__);
		वापस -ESPIPE;
	पूर्ण

	अगर (atomic_cmpxchg(&fh->v4l_पढ़ोing, 0, 1) == 0) अणु
		अगर (atomic_inc_वापस(&port->v4l_पढ़ोer_count) == 1) अणु

			अगर (saa7164_encoder_initialize(port) < 0) अणु
				prपूर्णांकk(KERN_ERR "%s() EINVAL\n", __func__);
				वापस -EINVAL;
			पूर्ण

			saa7164_encoder_start_streaming(port);
			msleep(200);
		पूर्ण
	पूर्ण

	/* blocking रुको क्रम buffer */
	अगर ((file->f_flags & O_NONBLOCK) == 0) अणु
		अगर (रुको_event_पूर्णांकerruptible(port->रुको_पढ़ो,
			saa7164_enc_next_buf(port))) अणु
				prपूर्णांकk(KERN_ERR "%s() ERESTARTSYS\n", __func__);
				वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण

	/* Pull the first buffer from the used list */
	ubuf = saa7164_enc_next_buf(port);

	जबतक ((count > 0) && ubuf) अणु

		/* set reमुख्यing bytes to copy */
		rem = ubuf->actual_size - ubuf->pos;
		cnt = rem > count ? count : rem;

		p = ubuf->data + ubuf->pos;

		dprपूर्णांकk(DBGLVL_ENC,
			"%s() count=%d cnt=%d rem=%d buf=%p buf->pos=%d\n",
			__func__, (पूर्णांक)count, cnt, rem, ubuf, ubuf->pos);

		अगर (copy_to_user(buffer, p, cnt)) अणु
			prपूर्णांकk(KERN_ERR "%s() copy_to_user failed\n", __func__);
			अगर (!ret) अणु
				prपूर्णांकk(KERN_ERR "%s() EFAULT\n", __func__);
				ret = -EFAULT;
			पूर्ण
			जाओ err;
		पूर्ण

		ubuf->pos += cnt;
		count -= cnt;
		buffer += cnt;
		ret += cnt;

		अगर (ubuf->pos > ubuf->actual_size)
			prपूर्णांकk(KERN_ERR "read() pos > actual, huh?\n");

		अगर (ubuf->pos == ubuf->actual_size) अणु

			/* finished with current buffer, take next buffer */

			/* Requeue the buffer on the मुक्त list */
			ubuf->pos = 0;

			mutex_lock(&port->dmaqueue_lock);
			list_move_tail(&ubuf->list, &port->list_buf_मुक्त.list);
			mutex_unlock(&port->dmaqueue_lock);

			/* Dequeue next */
			अगर ((file->f_flags & O_NONBLOCK) == 0) अणु
				अगर (रुको_event_पूर्णांकerruptible(port->रुको_पढ़ो,
					saa7164_enc_next_buf(port))) अणु
						अवरोध;
				पूर्ण
			पूर्ण
			ubuf = saa7164_enc_next_buf(port);
		पूर्ण
	पूर्ण
err:
	अगर (!ret && !ubuf)
		ret = -EAGAIN;

	वापस ret;
पूर्ण

अटल __poll_t fops_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा saa7164_encoder_fh *fh =
		(काष्ठा saa7164_encoder_fh *)file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	__poll_t mask = v4l2_ctrl_poll(file, रुको);

	port->last_poll_msecs_dअगरf = port->last_poll_msecs;
	port->last_poll_msecs = jअगरfies_to_msecs(jअगरfies);
	port->last_poll_msecs_dअगरf = port->last_poll_msecs -
		port->last_poll_msecs_dअगरf;

	saa7164_histogram_update(&port->poll_पूर्णांकerval,
		port->last_poll_msecs_dअगरf);

	अगर (!(req_events & (EPOLLIN | EPOLLRDNORM)))
		वापस mask;

	अगर (atomic_cmpxchg(&fh->v4l_पढ़ोing, 0, 1) == 0) अणु
		अगर (atomic_inc_वापस(&port->v4l_पढ़ोer_count) == 1) अणु
			अगर (saa7164_encoder_initialize(port) < 0)
				वापस mask | EPOLLERR;
			saa7164_encoder_start_streaming(port);
			msleep(200);
		पूर्ण
	पूर्ण

	/* Pull the first buffer from the used list */
	अगर (!list_empty(&port->list_buf_used.list))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops saa7164_ctrl_ops = अणु
	.s_ctrl = saa7164_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations mpeg_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fops_खोलो,
	.release	= fops_release,
	.पढ़ो		= fops_पढ़ो,
	.poll		= fops_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops mpeg_ioctl_ops = अणु
	.vidioc_s_std		 = vidioc_s_std,
	.vidioc_g_std		 = vidioc_g_std,
	.vidioc_क्रमागत_input	 = saa7164_क्रमागत_input,
	.vidioc_g_input		 = vidioc_g_input,
	.vidioc_s_input		 = vidioc_s_input,
	.vidioc_g_tuner		 = saa7164_g_tuner,
	.vidioc_s_tuner		 = saa7164_s_tuner,
	.vidioc_g_frequency	 = vidioc_g_frequency,
	.vidioc_s_frequency	 = vidioc_s_frequency,
	.vidioc_querycap	 = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	 = vidioc_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	 = vidioc_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	 = vidioc_fmt_vid_cap,
	.vidioc_log_status	 = v4l2_ctrl_log_status,
	.vidioc_subscribe_event  = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device saa7164_mpeg_ढाँचा = अणु
	.name          = "saa7164",
	.fops          = &mpeg_fops,
	.ioctl_ops     = &mpeg_ioctl_ops,
	.minor         = -1,
	.tvnorms       = SAA7164_NORMS,
	.device_caps   = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			 V4L2_CAP_TUNER,
पूर्ण;

अटल काष्ठा video_device *saa7164_encoder_alloc(
	काष्ठा saa7164_port *port,
	काष्ठा pci_dev *pci,
	काष्ठा video_device *ढाँचा,
	अक्षर *type)
अणु
	काष्ठा video_device *vfd;
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	vfd = video_device_alloc();
	अगर (शून्य == vfd)
		वापस शून्य;

	*vfd = *ढाँचा;
	snम_लिखो(vfd->name, माप(vfd->name), "%s %s (%s)", dev->name,
		type, saa7164_boards[dev->board].name);

	vfd->v4l2_dev  = &dev->v4l2_dev;
	vfd->release = video_device_release;
	वापस vfd;
पूर्ण

पूर्णांक saa7164_encoder_रेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा v4l2_ctrl_handler *hdl = &port->ctrl_handler;
	पूर्णांक result = -ENODEV;

	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	BUG_ON(port->type != SAA7164_MPEG_ENCODER);

	/* Sanity check that the PCI configuration space is active */
	अगर (port->hwcfg.BARLocation == 0) अणु
		prपूर्णांकk(KERN_ERR "%s() failed (errno = %d), NO PCI configuration\n",
			__func__, result);
		result = -ENOMEM;
		जाओ fail_pci;
	पूर्ण

	/* Establish encoder शेषs here */
	/* Set शेष TV standard */
	port->encodernorm = saa7164_tvnorms[0];
	port->width = 720;
	port->mux_input = 1; /* Composite */
	port->video_क्रमmat = EU_VIDEO_FORMAT_MPEG_2;
	port->audio_क्रमmat = 0;
	port->video_resolution = 0;
	port->freq = SAA7164_TV_MIN_FREQ;

	v4l2_ctrl_handler_init(hdl, 14);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 255, 1, 127);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_CONTRAST, 0, 255, 1, 66);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 255, 1, 62);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_HUE, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_SHARPNESS, 0x0, 0x0f, 1, 8);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_MPEG_AUDIO_MUTE, 0x0, 0x01, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_AUDIO_VOLUME, -83, 24, 1, 20);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_BITRATE,
			  ENCODER_MIN_BITRATE, ENCODER_MAX_BITRATE,
			  100000, ENCODER_DEF_BITRATE);
	v4l2_ctrl_new_std_menu(hdl, &saa7164_ctrl_ops,
			       V4L2_CID_MPEG_STREAM_TYPE,
			       V4L2_MPEG_STREAM_TYPE_MPEG2_TS, 0,
			       V4L2_MPEG_STREAM_TYPE_MPEG2_PS);
	v4l2_ctrl_new_std_menu(hdl, &saa7164_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_ASPECT,
			       V4L2_MPEG_VIDEO_ASPECT_221x100, 0,
			       V4L2_MPEG_VIDEO_ASPECT_4x3);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_GOP_SIZE, 1, 255, 1, 15);
	v4l2_ctrl_new_std_menu(hdl, &saa7164_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
			       V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
			       V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_B_FRAMES, 1, 3, 1, 1);
	v4l2_ctrl_new_std(hdl, &saa7164_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
			  ENCODER_MIN_BITRATE, ENCODER_MAX_BITRATE,
			  100000, ENCODER_DEF_BITRATE);
	अगर (hdl->error) अणु
		result = hdl->error;
		जाओ fail_hdl;
	पूर्ण

	port->std = V4L2_STD_NTSC_M;

	अगर (port->encodernorm.id & V4L2_STD_525_60)
		port->height = 480;
	अन्यथा
		port->height = 576;

	/* Allocate and रेजिस्टर the video device node */
	port->v4l_device = saa7164_encoder_alloc(port,
		dev->pci, &saa7164_mpeg_ढाँचा, "mpeg");

	अगर (!port->v4l_device) अणु
		prपूर्णांकk(KERN_INFO "%s: can't allocate mpeg device\n",
			dev->name);
		result = -ENOMEM;
		जाओ fail_hdl;
	पूर्ण

	port->v4l_device->ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);
	video_set_drvdata(port->v4l_device, port);
	result = video_रेजिस्टर_device(port->v4l_device,
		VFL_TYPE_VIDEO, -1);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_INFO "%s: can't register mpeg device\n",
			dev->name);
		जाओ fail_reg;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: registered device video%d [mpeg]\n",
		dev->name, port->v4l_device->num);

	/* Configure the hardware शेषs */
	saa7164_api_set_videomux(port);
	saa7164_api_set_usercontrol(port, PU_BRIGHTNESS_CONTROL);
	saa7164_api_set_usercontrol(port, PU_CONTRAST_CONTROL);
	saa7164_api_set_usercontrol(port, PU_HUE_CONTROL);
	saa7164_api_set_usercontrol(port, PU_SATURATION_CONTROL);
	saa7164_api_set_usercontrol(port, PU_SHARPNESS_CONTROL);
	saa7164_api_audio_mute(port, 0);
	saa7164_api_set_audio_volume(port, 20);
	saa7164_api_set_aspect_ratio(port);

	/* Disable audio standard detection, it's buggy */
	saa7164_api_set_audio_detection(port, 0);

	saa7164_api_set_encoder(port);
	saa7164_api_get_encoder(port);
	वापस 0;

fail_reg:
	video_device_release(port->v4l_device);
	port->v4l_device = शून्य;
fail_hdl:
	v4l2_ctrl_handler_मुक्त(hdl);
fail_pci:
	वापस result;
पूर्ण

व्योम saa7164_encoder_unरेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d)\n", __func__, port->nr);

	BUG_ON(port->type != SAA7164_MPEG_ENCODER);

	अगर (port->v4l_device) अणु
		अगर (port->v4l_device->minor != -1)
			video_unरेजिस्टर_device(port->v4l_device);
		अन्यथा
			video_device_release(port->v4l_device);

		port->v4l_device = शून्य;
	पूर्ण
	v4l2_ctrl_handler_मुक्त(&port->ctrl_handler);

	dprपूर्णांकk(DBGLVL_ENC, "%s(port=%d) done\n", __func__, port->nr);
पूर्ण

