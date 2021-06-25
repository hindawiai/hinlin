<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश "saa7164.h"

/* Take the encoder configuration from the port काष्ठा and
 * flush it to the hardware.
 */
अटल व्योम saa7164_vbi_configure(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	dprपूर्णांकk(DBGLVL_VBI, "%s()\n", __func__);

	port->vbi_params.width = port->enc_port->width;
	port->vbi_params.height = port->enc_port->height;
	port->vbi_params.is_50hz =
		(port->enc_port->encodernorm.id & V4L2_STD_625_50) != 0;

	/* Set up the DIF (enable it) क्रम analog mode by शेष */
	saa7164_api_initialize_dअगर(port);
	dprपूर्णांकk(DBGLVL_VBI, "%s() ends\n", __func__);
पूर्ण

अटल पूर्णांक saa7164_vbi_buffers_dealloc(काष्ठा saa7164_port *port)
अणु
	काष्ठा list_head *c, *n, *p, *q, *l, *v;
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा saa7164_user_buffer *ubuf;

	/* Remove any allocated buffers */
	mutex_lock(&port->dmaqueue_lock);

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d) dmaqueue\n", __func__, port->nr);
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु
		buf = list_entry(c, काष्ठा saa7164_buffer, list);
		list_del(c);
		saa7164_buffer_dealloc(buf);
	पूर्ण

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d) used\n", __func__, port->nr);
	list_क्रम_each_safe(p, q, &port->list_buf_used.list) अणु
		ubuf = list_entry(p, काष्ठा saa7164_user_buffer, list);
		list_del(p);
		saa7164_buffer_dealloc_user(ubuf);
	पूर्ण

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d) free\n", __func__, port->nr);
	list_क्रम_each_safe(l, v, &port->list_buf_मुक्त.list) अणु
		ubuf = list_entry(l, काष्ठा saa7164_user_buffer, list);
		list_del(l);
		saa7164_buffer_dealloc_user(ubuf);
	पूर्ण

	mutex_unlock(&port->dmaqueue_lock);
	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d) done\n", __func__, port->nr);

	वापस 0;
पूर्ण

/* Dynamic buffer चयन at vbi start समय */
अटल पूर्णांक saa7164_vbi_buffers_alloc(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा saa7164_user_buffer *ubuf;
	काष्ठा पंचांगHWStreamParameters *params = &port->hw_streamingparams;
	पूर्णांक result = -ENODEV, i;
	पूर्णांक len = 0;

	dprपूर्णांकk(DBGLVL_VBI, "%s()\n", __func__);

	/* TODO: NTSC SPECIFIC */
	/* Init and establish शेषs */
	params->samplesperline = 1440;
	params->numberoflines = 12;
	params->numberoflines = 18;
	params->pitch = 1600;
	params->pitch = 1440;
	params->numpagetables = 2 +
		((params->numberoflines * params->pitch) / PAGE_SIZE);
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

	अगर (vbi_buffers < 16)
		vbi_buffers = 16;
	अगर (vbi_buffers > 512)
		vbi_buffers = 512;

	क्रम (i = 0; i < vbi_buffers; i++) अणु

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


अटल पूर्णांक saa7164_vbi_initialize(काष्ठा saa7164_port *port)
अणु
	saa7164_vbi_configure(port);
	वापस 0;
पूर्ण

/* -- V4L2 --------------------------------------------------------- */
अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;

	वापस saa7164_s_std(fh->port->enc_port, id);
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा saa7164_encoder_fh *fh = file->निजी_data;

	वापस saa7164_g_std(fh->port->enc_port, id);
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;

	वापस saa7164_g_input(fh->port->enc_port, i);
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;

	वापस saa7164_s_input(fh->port->enc_port, i);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;

	वापस saa7164_g_frequency(fh->port->enc_port, f);
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;
	पूर्णांक ret = saa7164_s_frequency(fh->port->enc_port, f);

	अगर (ret == 0)
		saa7164_vbi_initialize(fh->port);
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
	काष्ठा v4l2_capability *cap)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;
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

अटल पूर्णांक saa7164_vbi_stop_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() stop transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_VBI, "%s()    Stopped\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_vbi_acquire_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_ACQUIRE);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() acquire transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_VBI, "%s() Acquired\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_vbi_छोड़ो_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_PAUSE);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() pause transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_VBI, "%s()   Paused\n", __func__);
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
अटल पूर्णांक saa7164_vbi_stop_streaming(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा saa7164_user_buffer *ubuf;
	काष्ठा list_head *c, *n;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d)\n", __func__, port->nr);

	ret = saa7164_vbi_छोड़ो_port(port);
	ret = saa7164_vbi_acquire_port(port);
	ret = saa7164_vbi_stop_port(port);

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d) Hardware stopped\n", __func__,
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
	saa7164_vbi_buffers_dealloc(port);

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d) Released\n", __func__, port->nr);

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_vbi_start_streaming(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक result, ret = 0;

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d)\n", __func__, port->nr);

	port->करोne_first_पूर्णांकerrupt = 0;

	/* allocate all of the PCIe DMA buffer resources on the fly,
	 * allowing चयनing between TS and PS payloads without
	 * requiring a complete driver reload.
	 */
	saa7164_vbi_buffers_alloc(port);

	/* Configure the encoder with any cache values */
#अगर 0
	saa7164_api_set_encoder(port);
	saa7164_api_get_encoder(port);
#पूर्ण_अगर

	/* Place the empty buffers on the hardware */
	saa7164_buffer_cfg_port(port);

	/* Negotiate क्रमmat */
	अगर (saa7164_api_set_vbi_क्रमmat(port) != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() No supported VBI format\n", __func__);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Acquire the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_ACQUIRE);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() acquire transition failed, res = 0x%x\n",
			__func__, result);

		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_VBI, "%s()   Acquired\n", __func__);

	/* Pause the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_PAUSE);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() pause transition failed, res = 0x%x\n",
				__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_vbi_stop_port(port);
		अगर (result != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "%s() pause/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण

		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_VBI, "%s()   Paused\n", __func__);

	/* Start the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_RUN);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() run transition failed, result = 0x%x\n",
				__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_vbi_acquire_port(port);
		result = saa7164_vbi_stop_port(port);
		अगर (result != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "%s() run/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण

		ret = -EIO;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_VBI, "%s()   Running\n", __func__);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_vbi_fmt(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_क्रमmat *f)
अणु
	/* ntsc */
	f->fmt.vbi.samples_per_line = 1440;
	f->fmt.vbi.sampling_rate = 27000000;
	f->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.flags = 0;
	f->fmt.vbi.start[0] = 10;
	f->fmt.vbi.count[0] = 18;
	f->fmt.vbi.start[1] = 263 + 10 + 1;
	f->fmt.vbi.count[1] = 18;
	स_रखो(f->fmt.vbi.reserved, 0, माप(f->fmt.vbi.reserved));
	वापस 0;
पूर्ण

अटल पूर्णांक fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा saa7164_dev *dev;
	काष्ठा saa7164_port *port;
	काष्ठा saa7164_vbi_fh *fh;

	port = (काष्ठा saa7164_port *)video_get_drvdata(video_devdata(file));
	अगर (!port)
		वापस -ENODEV;

	dev = port->dev;

	dprपूर्णांकk(DBGLVL_VBI, "%s()\n", __func__);

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
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_VBI, "%s()\n", __func__);

	/* Shut device करोwn on last बंद */
	अगर (atomic_cmpxchg(&fh->v4l_पढ़ोing, 1, 0) == 1) अणु
		अगर (atomic_dec_वापस(&port->v4l_पढ़ोer_count) == 0) अणु
			/* stop vbi capture then cancel buffers */
			saa7164_vbi_stop_streaming(port);
		पूर्ण
	पूर्ण

	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	kमुक्त(fh);

	वापस 0;
पूर्ण

अटल काष्ठा
saa7164_user_buffer *saa7164_vbi_next_buf(काष्ठा saa7164_port *port)
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
				prपूर्णांकk(KERN_ERR "%s() ubuf %p crc became invalid, was 0x%x became 0x%x\n",
					__func__,
					ubuf, ubuf->crc, crc);
			पूर्ण
		पूर्ण

	पूर्ण
	mutex_unlock(&port->dmaqueue_lock);

	dprपूर्णांकk(DBGLVL_VBI, "%s() returns %p\n", __func__, ubuf);

	वापस ubuf;
पूर्ण

अटल sमाप_प्रकार fops_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
	माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा saa7164_vbi_fh *fh = file->निजी_data;
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

			अगर (saa7164_vbi_initialize(port) < 0) अणु
				prपूर्णांकk(KERN_ERR "%s() EINVAL\n", __func__);
				वापस -EINVAL;
			पूर्ण

			saa7164_vbi_start_streaming(port);
			msleep(200);
		पूर्ण
	पूर्ण

	/* blocking रुको क्रम buffer */
	अगर ((file->f_flags & O_NONBLOCK) == 0) अणु
		अगर (रुको_event_पूर्णांकerruptible(port->रुको_पढ़ो,
			saa7164_vbi_next_buf(port))) अणु
				prपूर्णांकk(KERN_ERR "%s() ERESTARTSYS\n", __func__);
				वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण

	/* Pull the first buffer from the used list */
	ubuf = saa7164_vbi_next_buf(port);

	जबतक ((count > 0) && ubuf) अणु

		/* set reमुख्यing bytes to copy */
		rem = ubuf->actual_size - ubuf->pos;
		cnt = rem > count ? count : rem;

		p = ubuf->data + ubuf->pos;

		dprपूर्णांकk(DBGLVL_VBI,
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
					saa7164_vbi_next_buf(port))) अणु
						अवरोध;
				पूर्ण
			पूर्ण
			ubuf = saa7164_vbi_next_buf(port);
		पूर्ण
	पूर्ण
err:
	अगर (!ret && !ubuf) अणु
		prपूर्णांकk(KERN_ERR "%s() EAGAIN\n", __func__);
		ret = -EAGAIN;
	पूर्ण

	वापस ret;
पूर्ण

अटल __poll_t fops_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा saa7164_vbi_fh *fh = (काष्ठा saa7164_vbi_fh *)file->निजी_data;
	काष्ठा saa7164_port *port = fh->port;
	__poll_t mask = 0;

	port->last_poll_msecs_dअगरf = port->last_poll_msecs;
	port->last_poll_msecs = jअगरfies_to_msecs(jअगरfies);
	port->last_poll_msecs_dअगरf = port->last_poll_msecs -
		port->last_poll_msecs_dअगरf;

	saa7164_histogram_update(&port->poll_पूर्णांकerval,
		port->last_poll_msecs_dअगरf);

	अगर (!video_is_रेजिस्टरed(port->v4l_device))
		वापस EPOLLERR;

	अगर (atomic_cmpxchg(&fh->v4l_पढ़ोing, 0, 1) == 0) अणु
		अगर (atomic_inc_वापस(&port->v4l_पढ़ोer_count) == 1) अणु
			अगर (saa7164_vbi_initialize(port) < 0)
				वापस EPOLLERR;
			saa7164_vbi_start_streaming(port);
			msleep(200);
		पूर्ण
	पूर्ण

	/* blocking रुको क्रम buffer */
	अगर ((file->f_flags & O_NONBLOCK) == 0) अणु
		अगर (रुको_event_पूर्णांकerruptible(port->रुको_पढ़ो,
			saa7164_vbi_next_buf(port))) अणु
				वापस EPOLLERR;
		पूर्ण
	पूर्ण

	/* Pull the first buffer from the used list */
	अगर (!list_empty(&port->list_buf_used.list))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण
अटल स्थिर काष्ठा v4l2_file_operations vbi_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fops_खोलो,
	.release	= fops_release,
	.पढ़ो		= fops_पढ़ो,
	.poll		= fops_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops vbi_ioctl_ops = अणु
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
	.vidioc_g_fmt_vbi_cap	 = saa7164_vbi_fmt,
	.vidioc_try_fmt_vbi_cap	 = saa7164_vbi_fmt,
	.vidioc_s_fmt_vbi_cap	 = saa7164_vbi_fmt,
पूर्ण;

अटल काष्ठा video_device saa7164_vbi_ढाँचा = अणु
	.name          = "saa7164",
	.fops          = &vbi_fops,
	.ioctl_ops     = &vbi_ioctl_ops,
	.minor         = -1,
	.tvnorms       = SAA7164_NORMS,
	.device_caps   = V4L2_CAP_VBI_CAPTURE | V4L2_CAP_READWRITE |
			 V4L2_CAP_TUNER,
पूर्ण;

अटल काष्ठा video_device *saa7164_vbi_alloc(
	काष्ठा saa7164_port *port,
	काष्ठा pci_dev *pci,
	काष्ठा video_device *ढाँचा,
	अक्षर *type)
अणु
	काष्ठा video_device *vfd;
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_VBI, "%s()\n", __func__);

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

पूर्णांक saa7164_vbi_रेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक result = -ENODEV;

	dprपूर्णांकk(DBGLVL_VBI, "%s()\n", __func__);

	BUG_ON(port->type != SAA7164_MPEG_VBI);

	/* Sanity check that the PCI configuration space is active */
	अगर (port->hwcfg.BARLocation == 0) अणु
		prपूर्णांकk(KERN_ERR "%s() failed (errno = %d), NO PCI configuration\n",
			__func__, result);
		result = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* Establish VBI शेषs here */

	/* Allocate and रेजिस्टर the video device node */
	port->v4l_device = saa7164_vbi_alloc(port,
		dev->pci, &saa7164_vbi_ढाँचा, "vbi");

	अगर (!port->v4l_device) अणु
		prपूर्णांकk(KERN_INFO "%s: can't allocate vbi device\n",
			dev->name);
		result = -ENOMEM;
		जाओ failed;
	पूर्ण

	port->enc_port = &dev->ports[port->nr - 2];
	video_set_drvdata(port->v4l_device, port);
	result = video_रेजिस्टर_device(port->v4l_device,
		VFL_TYPE_VBI, -1);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_INFO "%s: can't register vbi device\n",
			dev->name);
		/* TODO: We're going to leak here if we don't dealloc
		 The buffers above. The unreg function can't deal wit it.
		*/
		जाओ failed;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: registered device vbi%d [vbi]\n",
		dev->name, port->v4l_device->num);

	/* Configure the hardware शेषs */

	result = 0;
failed:
	वापस result;
पूर्ण

व्योम saa7164_vbi_unरेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	dprपूर्णांकk(DBGLVL_VBI, "%s(port=%d)\n", __func__, port->nr);

	BUG_ON(port->type != SAA7164_MPEG_VBI);

	अगर (port->v4l_device) अणु
		अगर (port->v4l_device->minor != -1)
			video_unरेजिस्टर_device(port->v4l_device);
		अन्यथा
			video_device_release(port->v4l_device);

		port->v4l_device = शून्य;
	पूर्ण

पूर्ण
