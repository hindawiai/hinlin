<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * (c) 2004 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>

/* ------------------------------------------------------------------ */

MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक empress_nr[] = अणु[0 ... (SAA7134_MAXBOARDS - 1)] = UNSET पूर्ण;

module_param_array(empress_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(empress_nr,"ts device number");

/* ------------------------------------------------------------------ */

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vq->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	u32 leading_null_bytes = 0;
	पूर्णांक err;

	err = saa7134_ts_start_streaming(vq, count);
	अगर (err)
		वापस err;

	/* If more cards start to need this, then this
	   should probably be added to the card definitions. */
	चयन (dev->board) अणु
	हाल SAA7134_BOARD_BEHOLD_M6:
	हाल SAA7134_BOARD_BEHOLD_M63:
	हाल SAA7134_BOARD_BEHOLD_M6_EXTRA:
		leading_null_bytes = 1;
		अवरोध;
	पूर्ण
	saa_call_all(dev, core, init, leading_null_bytes);
	/* Unmute audio */
	saa_ग_लिखोb(SAA7134_AUDIO_MUTE_CTRL,
			saa_पढ़ोb(SAA7134_AUDIO_MUTE_CTRL) & ~(1 << 6));
	dev->empress_started = 1;
	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vq->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;

	saa7134_ts_stop_streaming(vq);
	saa_ग_लिखोb(SAA7134_SPECIAL_MODE, 0x00);
	msleep(20);
	saa_ग_लिखोb(SAA7134_SPECIAL_MODE, 0x01);
	msleep(100);
	/* Mute audio */
	saa_ग_लिखोb(SAA7134_AUDIO_MUTE_CTRL,
			saa_पढ़ोb(SAA7134_AUDIO_MUTE_CTRL) | (1 << 6));
	dev->empress_started = 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops saa7134_empress_qops = अणु
	.queue_setup	= saa7134_ts_queue_setup,
	.buf_init	= saa7134_ts_buffer_init,
	.buf_prepare	= saa7134_ts_buffer_prepare,
	.buf_queue	= saa7134_vb2_buffer_queue,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक empress_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_MPEG;
	वापस 0;
पूर्ण

अटल पूर्णांक empress_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &fmt.क्रमmat;

	saa_call_all(dev, pad, get_fmt, शून्य, &fmt);

	v4l2_fill_pix_क्रमmat(&f->fmt.pix, mbus_fmt);
	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage    = TS_PACKET_SIZE * dev->ts.nr_packets;
	f->fmt.pix.bytesperline = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक empress_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	saa_call_all(dev, pad, set_fmt, शून्य, &क्रमmat);
	v4l2_fill_pix_क्रमmat(&f->fmt.pix, &क्रमmat.क्रमmat);

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage    = TS_PACKET_SIZE * dev->ts.nr_packets;
	f->fmt.pix.bytesperline = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक empress_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	saa_call_all(dev, pad, set_fmt, &pad_cfg, &क्रमmat);
	v4l2_fill_pix_क्रमmat(&f->fmt.pix, &क्रमmat.क्रमmat);

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage    = TS_PACKET_SIZE * dev->ts.nr_packets;
	f->fmt.pix.bytesperline = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations ts_fops =
अणु
	.owner	  = THIS_MODULE,
	.खोलो	  = v4l2_fh_खोलो,
	.release  = vb2_fop_release,
	.पढ़ो	  = vb2_fop_पढ़ो,
	.poll	  = vb2_fop_poll,
	.mmap	  = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops ts_ioctl_ops = अणु
	.vidioc_querycap		= saa7134_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= empress_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= empress_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= empress_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= empress_g_fmt_vid_cap,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_g_frequency		= saa7134_g_frequency,
	.vidioc_s_frequency		= saa7134_s_frequency,
	.vidioc_g_tuner			= saa7134_g_tuner,
	.vidioc_s_tuner			= saa7134_s_tuner,
	.vidioc_क्रमागत_input		= saa7134_क्रमागत_input,
	.vidioc_g_input			= saa7134_g_input,
	.vidioc_s_input			= saa7134_s_input,
	.vidioc_s_std			= saa7134_s_std,
	.vidioc_g_std			= saa7134_g_std,
	.vidioc_querystd		= saa7134_querystd,
	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/* ----------------------------------------------------------- */

अटल स्थिर काष्ठा video_device saa7134_empress_ढाँचा = अणु
	.name          = "saa7134-empress",
	.fops          = &ts_fops,
	.ioctl_ops     = &ts_ioctl_ops,

	.tvnorms			= SAA7134_NORMS,
पूर्ण;

अटल व्योम empress_संकेत_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा saa7134_dev* dev =
		container_of(work, काष्ठा saa7134_dev, empress_workqueue);

	अगर (dev->noसंकेत) अणु
		pr_debug("no video signal\n");
	पूर्ण अन्यथा अणु
		pr_debug("video signal acquired\n");
	पूर्ण
पूर्ण

अटल व्योम empress_संकेत_change(काष्ठा saa7134_dev *dev)
अणु
	schedule_work(&dev->empress_workqueue);
पूर्ण

अटल bool empress_ctrl_filter(स्थिर काष्ठा v4l2_ctrl *ctrl)
अणु
	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
	हाल V4L2_CID_HUE:
	हाल V4L2_CID_CONTRAST:
	हाल V4L2_CID_SATURATION:
	हाल V4L2_CID_AUDIO_MUTE:
	हाल V4L2_CID_AUDIO_VOLUME:
	हाल V4L2_CID_PRIVATE_INVERT:
	हाल V4L2_CID_PRIVATE_AUTOMUTE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक empress_init(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev->empress_ctrl_handler;
	काष्ठा vb2_queue *q;
	पूर्णांक err;

	pr_debug("%s: %s\n", dev->name, __func__);
	dev->empress_dev = video_device_alloc();
	अगर (शून्य == dev->empress_dev)
		वापस -ENOMEM;
	*(dev->empress_dev) = saa7134_empress_ढाँचा;
	dev->empress_dev->v4l2_dev  = &dev->v4l2_dev;
	dev->empress_dev->release = video_device_release;
	dev->empress_dev->lock = &dev->lock;
	snम_लिखो(dev->empress_dev->name, माप(dev->empress_dev->name),
		 "%s empress (%s)", dev->name,
		 saa7134_boards[dev->board].name);
	v4l2_ctrl_handler_init(hdl, 21);
	v4l2_ctrl_add_handler(hdl, &dev->ctrl_handler, empress_ctrl_filter, false);
	अगर (dev->empress_sd)
		v4l2_ctrl_add_handler(hdl, dev->empress_sd->ctrl_handler, शून्य, true);
	अगर (hdl->error) अणु
		video_device_release(dev->empress_dev);
		वापस hdl->error;
	पूर्ण
	dev->empress_dev->ctrl_handler = hdl;

	INIT_WORK(&dev->empress_workqueue, empress_संकेत_update);

	q = &dev->empress_vbq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	/*
	 * Do not add VB2_USERPTR: the saa7134 DMA engine cannot handle
	 * transfers that करो not start at the beginning of a page. A USERPTR
	 * can start anywhere in a page, so USERPTR support is a no-go.
	 */
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv = &dev->ts_q;
	q->ops = &saa7134_empress_qops;
	q->gfp_flags = GFP_DMA32;
	q->mem_ops = &vb2_dma_sg_memops;
	q->buf_काष्ठा_size = माप(काष्ठा saa7134_buf);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;
	err = vb2_queue_init(q);
	अगर (err) अणु
		video_device_release(dev->empress_dev);
		dev->empress_dev = शून्य;
		वापस err;
	पूर्ण
	dev->empress_dev->queue = q;
	dev->empress_dev->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
					V4L2_CAP_VIDEO_CAPTURE;
	अगर (dev->tuner_type != TUNER_ABSENT && dev->tuner_type != UNSET)
		dev->empress_dev->device_caps |= V4L2_CAP_TUNER;

	video_set_drvdata(dev->empress_dev, dev);
	err = video_रेजिस्टर_device(dev->empress_dev,VFL_TYPE_VIDEO,
				    empress_nr[dev->nr]);
	अगर (err < 0) अणु
		pr_info("%s: can't register video device\n",
		       dev->name);
		video_device_release(dev->empress_dev);
		dev->empress_dev = शून्य;
		वापस err;
	पूर्ण
	pr_info("%s: registered device %s [mpeg]\n",
	       dev->name, video_device_node_name(dev->empress_dev));

	empress_संकेत_update(&dev->empress_workqueue);
	वापस 0;
पूर्ण

अटल पूर्णांक empress_fini(काष्ठा saa7134_dev *dev)
अणु
	pr_debug("%s: %s\n", dev->name, __func__);

	अगर (शून्य == dev->empress_dev)
		वापस 0;
	flush_work(&dev->empress_workqueue);
	vb2_video_unरेजिस्टर_device(dev->empress_dev);
	v4l2_ctrl_handler_मुक्त(&dev->empress_ctrl_handler);
	dev->empress_dev = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा saa7134_mpeg_ops empress_ops = अणु
	.type          = SAA7134_MPEG_EMPRESS,
	.init          = empress_init,
	.fini          = empress_fini,
	.संकेत_change = empress_संकेत_change,
पूर्ण;

अटल पूर्णांक __init empress_रेजिस्टर(व्योम)
अणु
	वापस saa7134_ts_रेजिस्टर(&empress_ops);
पूर्ण

अटल व्योम __निकास empress_unरेजिस्टर(व्योम)
अणु
	saa7134_ts_unरेजिस्टर(&empress_ops);
पूर्ण

module_init(empress_रेजिस्टर);
module_निकास(empress_unरेजिस्टर);
