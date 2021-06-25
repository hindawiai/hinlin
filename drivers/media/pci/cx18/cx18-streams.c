<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 init/start/stop/निकास stream functions
 *
 *  Derived from ivtv-streams.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-fileops.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-i2c.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-ioctl.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-scb.h"
#समावेश "cx18-dvb.h"

#घोषणा CX18_DSP0_INTERRUPT_MASK	0xd0004C

अटल स्थिर काष्ठा v4l2_file_operations cx18_v4l2_enc_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = cx18_v4l2_पढ़ो,
	.खोलो = cx18_v4l2_खोलो,
	.unlocked_ioctl = video_ioctl2,
	.release = cx18_v4l2_बंद,
	.poll = cx18_v4l2_enc_poll,
	.mmap = cx18_v4l2_mmap,
पूर्ण;

/* offset from 0 to रेजिस्टर ts v4l2 minors on */
#घोषणा CX18_V4L2_ENC_TS_OFFSET   16
/* offset from 0 to रेजिस्टर pcm v4l2 minors on */
#घोषणा CX18_V4L2_ENC_PCM_OFFSET  24
/* offset from 0 to रेजिस्टर yuv v4l2 minors on */
#घोषणा CX18_V4L2_ENC_YUV_OFFSET  32

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक vfl_type;
	पूर्णांक num_offset;
	पूर्णांक dma;
	u32 caps;
पूर्ण cx18_stream_info[] = अणु
	अणु	/* CX18_ENC_STREAM_TYPE_MPG */
		"encoder MPEG",
		VFL_TYPE_VIDEO, 0,
		PCI_DMA_FROMDEVICE,
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		V4L2_CAP_AUDIO | V4L2_CAP_TUNER
	पूर्ण,
	अणु	/* CX18_ENC_STREAM_TYPE_TS */
		"TS",
		VFL_TYPE_VIDEO, -1,
		PCI_DMA_FROMDEVICE,
	पूर्ण,
	अणु	/* CX18_ENC_STREAM_TYPE_YUV */
		"encoder YUV",
		VFL_TYPE_VIDEO, CX18_V4L2_ENC_YUV_OFFSET,
		PCI_DMA_FROMDEVICE,
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		V4L2_CAP_STREAMING | V4L2_CAP_AUDIO | V4L2_CAP_TUNER
	पूर्ण,
	अणु	/* CX18_ENC_STREAM_TYPE_VBI */
		"encoder VBI",
		VFL_TYPE_VBI, 0,
		PCI_DMA_FROMDEVICE,
		V4L2_CAP_VBI_CAPTURE | V4L2_CAP_SLICED_VBI_CAPTURE |
		V4L2_CAP_READWRITE | V4L2_CAP_TUNER
	पूर्ण,
	अणु	/* CX18_ENC_STREAM_TYPE_PCM */
		"encoder PCM audio",
		VFL_TYPE_VIDEO, CX18_V4L2_ENC_PCM_OFFSET,
		PCI_DMA_FROMDEVICE,
		V4L2_CAP_TUNER | V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
	पूर्ण,
	अणु	/* CX18_ENC_STREAM_TYPE_IDX */
		"encoder IDX",
		VFL_TYPE_VIDEO, -1,
		PCI_DMA_FROMDEVICE,
	पूर्ण,
	अणु	/* CX18_ENC_STREAM_TYPE_RAD */
		"encoder radio",
		VFL_TYPE_RADIO, 0,
		PCI_DMA_NONE,
		V4L2_CAP_RADIO | V4L2_CAP_TUNER
	पूर्ण,
पूर्ण;


अटल व्योम cx18_dma_मुक्त(काष्ठा videobuf_queue *q,
	काष्ठा cx18_stream *s, काष्ठा cx18_videobuf_buffer *buf)
अणु
	videobuf_रुकोon(q, &buf->vb, 0, 0);
	videobuf_vदो_स्मृति_मुक्त(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
पूर्ण

अटल पूर्णांक cx18_prepare_buffer(काष्ठा videobuf_queue *q,
	काष्ठा cx18_stream *s,
	काष्ठा cx18_videobuf_buffer *buf,
	u32 pixelक्रमmat,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	क्रमागत v4l2_field field)
अणु
	काष्ठा cx18 *cx = s->cx;
	पूर्णांक rc = 0;

	/* check settings */
	buf->bytes_used = 0;

	अगर ((width  < 48) || (height < 32))
		वापस -EINVAL;

	buf->vb.size = (width * height * 2);
	अगर ((buf->vb.baddr != 0) && (buf->vb.bsize < buf->vb.size))
		वापस -EINVAL;

	/* alloc + fill काष्ठा (अगर changed) */
	अगर (buf->vb.width != width || buf->vb.height != height ||
	    buf->vb.field != field || s->pixelक्रमmat != pixelक्रमmat ||
	    buf->tvnorm != cx->std) अणु

		buf->vb.width  = width;
		buf->vb.height = height;
		buf->vb.field  = field;
		buf->tvnorm    = cx->std;
		s->pixelक्रमmat = pixelक्रमmat;

		/* HM12 YUV size is (Y=(h*720) + UV=(h*(720/2)))
		   UYUV YUV size is (Y=(h*720) + UV=(h*(720))) */
		अगर (s->pixelक्रमmat == V4L2_PIX_FMT_HM12)
			s->vb_bytes_per_frame = height * 720 * 3 / 2;
		अन्यथा
			s->vb_bytes_per_frame = height * 720 * 2;
		cx18_dma_मुक्त(q, s, buf);
	पूर्ण

	अगर ((buf->vb.baddr != 0) && (buf->vb.bsize < buf->vb.size))
		वापस -EINVAL;

	अगर (buf->vb.field == 0)
		buf->vb.field = V4L2_FIELD_INTERLACED;

	अगर (VIDEOBUF_NEEDS_INIT == buf->vb.state) अणु
		buf->vb.width  = width;
		buf->vb.height = height;
		buf->vb.field  = field;
		buf->tvnorm    = cx->std;
		s->pixelक्रमmat = pixelक्रमmat;

		/* HM12 YUV size is (Y=(h*720) + UV=(h*(720/2)))
		   UYUV YUV size is (Y=(h*720) + UV=(h*(720))) */
		अगर (s->pixelक्रमmat == V4L2_PIX_FMT_HM12)
			s->vb_bytes_per_frame = height * 720 * 3 / 2;
		अन्यथा
			s->vb_bytes_per_frame = height * 720 * 2;
		rc = videobuf_iolock(q, &buf->vb, शून्य);
		अगर (rc != 0)
			जाओ fail;
	पूर्ण
	buf->vb.state = VIDEOBUF_PREPARED;
	वापस 0;

fail:
	cx18_dma_मुक्त(q, s, buf);
	वापस rc;

पूर्ण

/* VB_MIN_बफ_मानE is lcm(1440 * 480, 1440 * 576)
   1440 is a single line of 4:2:2 YUV at 720 luma samples wide
*/
#घोषणा VB_MIN_BUFFERS 32
#घोषणा VB_MIN_बफ_मानE 4147200

अटल पूर्णांक buffer_setup(काष्ठा videobuf_queue *q,
	अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा cx18_stream *s = q->priv_data;
	काष्ठा cx18 *cx = s->cx;

	*size = 2 * cx->cxhdl.width * cx->cxhdl.height;
	अगर (*count == 0)
		*count = VB_MIN_BUFFERS;

	जबतक (*size * *count > VB_MIN_BUFFERS * VB_MIN_बफ_मानE)
		(*count)--;

	q->field = V4L2_FIELD_INTERLACED;
	q->last = V4L2_FIELD_INTERLACED;

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा videobuf_queue *q,
	काष्ठा videobuf_buffer *vb,
	क्रमागत v4l2_field field)
अणु
	काष्ठा cx18_videobuf_buffer *buf =
		container_of(vb, काष्ठा cx18_videobuf_buffer, vb);
	काष्ठा cx18_stream *s = q->priv_data;
	काष्ठा cx18 *cx = s->cx;

	वापस cx18_prepare_buffer(q, s, buf, s->pixelक्रमmat,
		cx->cxhdl.width, cx->cxhdl.height, field);
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *q,
	काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा cx18_videobuf_buffer *buf =
		container_of(vb, काष्ठा cx18_videobuf_buffer, vb);
	काष्ठा cx18_stream *s = q->priv_data;

	cx18_dma_मुक्त(q, s, buf);
पूर्ण

अटल व्योम buffer_queue(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा cx18_videobuf_buffer *buf =
		container_of(vb, काष्ठा cx18_videobuf_buffer, vb);
	काष्ठा cx18_stream *s = q->priv_data;

	buf->vb.state = VIDEOBUF_QUEUED;

	list_add_tail(&buf->vb.queue, &s->vb_capture);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops cx18_videobuf_qops = अणु
	.buf_setup    = buffer_setup,
	.buf_prepare  = buffer_prepare,
	.buf_queue    = buffer_queue,
	.buf_release  = buffer_release,
पूर्ण;

अटल व्योम cx18_stream_init(काष्ठा cx18 *cx, पूर्णांक type)
अणु
	काष्ठा cx18_stream *s = &cx->streams[type];

	स_रखो(s, 0, माप(*s));

	/* initialize cx18_stream fields */
	s->dvb = शून्य;
	s->cx = cx;
	s->type = type;
	s->name = cx18_stream_info[type].name;
	s->handle = CX18_INVALID_TASK_HANDLE;

	s->dma = cx18_stream_info[type].dma;
	s->v4l2_dev_caps = cx18_stream_info[type].caps;
	s->buffers = cx->stream_buffers[type];
	s->buf_size = cx->stream_buf_size[type];
	INIT_LIST_HEAD(&s->buf_pool);
	s->bufs_per_mdl = 1;
	s->mdl_size = s->buf_size * s->bufs_per_mdl;

	init_रुकोqueue_head(&s->रुकोq);
	s->id = -1;
	spin_lock_init(&s->q_मुक्त.lock);
	cx18_queue_init(&s->q_मुक्त);
	spin_lock_init(&s->q_busy.lock);
	cx18_queue_init(&s->q_busy);
	spin_lock_init(&s->q_full.lock);
	cx18_queue_init(&s->q_full);
	spin_lock_init(&s->q_idle.lock);
	cx18_queue_init(&s->q_idle);

	INIT_WORK(&s->out_work_order, cx18_out_work_handler);

	INIT_LIST_HEAD(&s->vb_capture);
	समयr_setup(&s->vb_समयout, cx18_vb_समयout, 0);
	spin_lock_init(&s->vb_lock);
	अगर (type == CX18_ENC_STREAM_TYPE_YUV) अणु
		spin_lock_init(&s->vbuf_q_lock);

		s->vb_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		videobuf_queue_vदो_स्मृति_init(&s->vbuf_q, &cx18_videobuf_qops,
			&cx->pci_dev->dev, &s->vbuf_q_lock,
			V4L2_BUF_TYPE_VIDEO_CAPTURE,
			V4L2_FIELD_INTERLACED,
			माप(काष्ठा cx18_videobuf_buffer),
			s, &cx->serialize_lock);

		/* Assume the previous pixel शेष */
		s->pixelक्रमmat = V4L2_PIX_FMT_HM12;
		s->vb_bytes_per_frame = cx->cxhdl.height * 720 * 3 / 2;
		s->vb_bytes_per_line = 720;
	पूर्ण
पूर्ण

अटल पूर्णांक cx18_prep_dev(काष्ठा cx18 *cx, पूर्णांक type)
अणु
	काष्ठा cx18_stream *s = &cx->streams[type];
	u32 cap = cx->v4l2_cap;
	पूर्णांक num_offset = cx18_stream_info[type].num_offset;
	पूर्णांक num = cx->instance + cx18_first_minor + num_offset;

	/*
	 * These five fields are always initialized.
	 * For analog capture related streams, अगर video_dev.v4l2_dev == शून्य then the
	 * stream is not in use.
	 * For the TS stream, अगर dvb == शून्य then the stream is not in use.
	 * In those हालs no other fields but these four can be used.
	 */
	s->video_dev.v4l2_dev = शून्य;
	s->dvb = शून्य;
	s->cx = cx;
	s->type = type;
	s->name = cx18_stream_info[type].name;

	/* Check whether the radio is supported */
	अगर (type == CX18_ENC_STREAM_TYPE_RAD && !(cap & V4L2_CAP_RADIO))
		वापस 0;

	/* Check whether VBI is supported */
	अगर (type == CX18_ENC_STREAM_TYPE_VBI &&
	    !(cap & (V4L2_CAP_VBI_CAPTURE | V4L2_CAP_SLICED_VBI_CAPTURE)))
		वापस 0;

	/* User explicitly selected 0 buffers क्रम these streams, so करोn't
	   create them. */
	अगर (cx18_stream_info[type].dma != PCI_DMA_NONE &&
	    cx->stream_buffers[type] == 0) अणु
		CX18_INFO("Disabled %s device\n", cx18_stream_info[type].name);
		वापस 0;
	पूर्ण

	cx18_stream_init(cx, type);

	/* Allocate the cx18_dvb काष्ठा only क्रम the TS on cards with DTV */
	अगर (type == CX18_ENC_STREAM_TYPE_TS) अणु
		अगर (cx->card->hw_all & CX18_HW_DVB) अणु
			s->dvb = kzalloc(माप(काष्ठा cx18_dvb), GFP_KERNEL);
			अगर (s->dvb == शून्य) अणु
				CX18_ERR("Couldn't allocate cx18_dvb structure for %s\n",
					 s->name);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Don't need buffers क्रम the TS, अगर there is no DVB */
			s->buffers = 0;
		पूर्ण
	पूर्ण

	अगर (num_offset == -1)
		वापस 0;

	/* initialize the v4l2 video device काष्ठाure */
	snम_लिखो(s->video_dev.name, माप(s->video_dev.name), "%s %s",
		 cx->v4l2_dev.name, s->name);

	s->video_dev.num = num;
	s->video_dev.v4l2_dev = &cx->v4l2_dev;
	s->video_dev.fops = &cx18_v4l2_enc_fops;
	s->video_dev.release = video_device_release_empty;
	अगर (cx->card->video_inमाला_दो->video_type == CX18_CARD_INPUT_VID_TUNER)
		s->video_dev.tvnorms = cx->tuner_std;
	अन्यथा
		s->video_dev.tvnorms = V4L2_STD_ALL;
	s->video_dev.lock = &cx->serialize_lock;
	cx18_set_funcs(&s->video_dev);
	वापस 0;
पूर्ण

/* Initialize v4l2 variables and रेजिस्टर v4l2 devices */
पूर्णांक cx18_streams_setup(काष्ठा cx18 *cx)
अणु
	पूर्णांक type, ret;

	/* Setup V4L2 Devices */
	क्रम (type = 0; type < CX18_MAX_STREAMS; type++) अणु
		/* Prepare device */
		ret = cx18_prep_dev(cx, type);
		अगर (ret < 0)
			अवरोध;

		/* Allocate Stream */
		ret = cx18_stream_alloc(&cx->streams[type]);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	अगर (type == CX18_MAX_STREAMS)
		वापस 0;

	/* One or more streams could not be initialized. Clean 'em all up. */
	cx18_streams_cleanup(cx, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक cx18_reg_dev(काष्ठा cx18 *cx, पूर्णांक type)
अणु
	काष्ठा cx18_stream *s = &cx->streams[type];
	पूर्णांक vfl_type = cx18_stream_info[type].vfl_type;
	स्थिर अक्षर *name;
	पूर्णांक num, ret;

	अगर (type == CX18_ENC_STREAM_TYPE_TS && s->dvb != शून्य) अणु
		ret = cx18_dvb_रेजिस्टर(s);
		अगर (ret < 0) अणु
			CX18_ERR("DVB failed to register\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (s->video_dev.v4l2_dev == शून्य)
		वापस 0;

	num = s->video_dev.num;
	s->video_dev.device_caps = s->v4l2_dev_caps;	/* device capabilities */
	/* card number + user defined offset + device offset */
	अगर (type != CX18_ENC_STREAM_TYPE_MPG) अणु
		काष्ठा cx18_stream *s_mpg = &cx->streams[CX18_ENC_STREAM_TYPE_MPG];

		अगर (s_mpg->video_dev.v4l2_dev)
			num = s_mpg->video_dev.num
			    + cx18_stream_info[type].num_offset;
	पूर्ण
	video_set_drvdata(&s->video_dev, s);

	/* Register device. First try the desired minor, then any मुक्त one. */
	ret = video_रेजिस्टर_device_no_warn(&s->video_dev, vfl_type, num);
	अगर (ret < 0) अणु
		CX18_ERR("Couldn't register v4l2 device for %s (device node number %d)\n",
			s->name, num);
		s->video_dev.v4l2_dev = शून्य;
		वापस ret;
	पूर्ण

	name = video_device_node_name(&s->video_dev);

	चयन (vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		CX18_INFO("Registered device %s for %s (%d x %d.%02d kB)\n",
			  name, s->name, cx->stream_buffers[type],
			  cx->stream_buf_size[type] / 1024,
			  (cx->stream_buf_size[type] * 100 / 1024) % 100);
		अवरोध;

	हाल VFL_TYPE_RADIO:
		CX18_INFO("Registered device %s for %s\n", name, s->name);
		अवरोध;

	हाल VFL_TYPE_VBI:
		अगर (cx->stream_buffers[type])
			CX18_INFO("Registered device %s for %s (%d x %d bytes)\n",
				  name, s->name, cx->stream_buffers[type],
				  cx->stream_buf_size[type]);
		अन्यथा
			CX18_INFO("Registered device %s for %s\n",
				name, s->name);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Register v4l2 devices */
पूर्णांक cx18_streams_रेजिस्टर(काष्ठा cx18 *cx)
अणु
	पूर्णांक type;
	पूर्णांक err;
	पूर्णांक ret = 0;

	/* Register V4L2 devices */
	क्रम (type = 0; type < CX18_MAX_STREAMS; type++) अणु
		err = cx18_reg_dev(cx, type);
		अगर (err && ret == 0)
			ret = err;
	पूर्ण

	अगर (ret == 0)
		वापस 0;

	/* One or more streams could not be initialized. Clean 'em all up. */
	cx18_streams_cleanup(cx, 1);
	वापस ret;
पूर्ण

/* Unरेजिस्टर v4l2 devices */
व्योम cx18_streams_cleanup(काष्ठा cx18 *cx, पूर्णांक unरेजिस्टर)
अणु
	काष्ठा video_device *vdev;
	पूर्णांक type;

	/* Tearकरोwn all streams */
	क्रम (type = 0; type < CX18_MAX_STREAMS; type++) अणु

		/* The TS has a cx18_dvb काष्ठाure, not a video_device */
		अगर (type == CX18_ENC_STREAM_TYPE_TS) अणु
			अगर (cx->streams[type].dvb != शून्य) अणु
				अगर (unरेजिस्टर)
					cx18_dvb_unरेजिस्टर(&cx->streams[type]);
				kमुक्त(cx->streams[type].dvb);
				cx->streams[type].dvb = शून्य;
				cx18_stream_मुक्त(&cx->streams[type]);
			पूर्ण
			जारी;
		पूर्ण

		/* No काष्ठा video_device, but can have buffers allocated */
		अगर (type == CX18_ENC_STREAM_TYPE_IDX) अणु
			/* If the module params didn't inhibit IDX ... */
			अगर (cx->stream_buffers[type] != 0) अणु
				cx->stream_buffers[type] = 0;
				/*
				 * Beक्रमe calling cx18_stream_मुक्त(),
				 * check अगर the IDX stream was actually set up.
				 * Needed, since the cx18_probe() error path
				 * निकासs through here as well as normal clean up
				 */
				अगर (cx->streams[type].buffers != 0)
					cx18_stream_मुक्त(&cx->streams[type]);
			पूर्ण
			जारी;
		पूर्ण

		/* If काष्ठा video_device exists, can have buffers allocated */
		vdev = &cx->streams[type].video_dev;

		अगर (vdev->v4l2_dev == शून्य)
			जारी;

		अगर (type == CX18_ENC_STREAM_TYPE_YUV)
			videobuf_mmap_मुक्त(&cx->streams[type].vbuf_q);

		cx18_stream_मुक्त(&cx->streams[type]);

		video_unरेजिस्टर_device(vdev);
	पूर्ण
पूर्ण

अटल व्योम cx18_vbi_setup(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18 *cx = s->cx;
	पूर्णांक raw = cx18_raw_vbi(cx);
	u32 data[CX2341X_MBOX_MAX_DATA];
	पूर्णांक lines;

	अगर (cx->is_60hz) अणु
		cx->vbi.count = 12;
		cx->vbi.start[0] = 10;
		cx->vbi.start[1] = 273;
	पूर्ण अन्यथा अणु        /* PAL/SECAM */
		cx->vbi.count = 18;
		cx->vbi.start[0] = 6;
		cx->vbi.start[1] = 318;
	पूर्ण

	/* setup VBI रेजिस्टरs */
	अगर (raw)
		v4l2_subdev_call(cx->sd_av, vbi, s_raw_fmt, &cx->vbi.in.fmt.vbi);
	अन्यथा
		v4l2_subdev_call(cx->sd_av, vbi, s_sliced_fmt, &cx->vbi.in.fmt.sliced);

	/*
	 * Send the CX18_CPU_SET_RAW_VBI_PARAM API command to setup Encoder Raw
	 * VBI when the first analog capture channel starts, as once it starts
	 * (e.g. MPEG), we can't effect any change in the Encoder Raw VBI setup
	 * (i.e. क्रम the VBI capture channels).  We also send it क्रम each
	 * analog capture channel anyway just to make sure we get the proper
	 * behavior
	 */
	अगर (raw) अणु
		lines = cx->vbi.count * 2;
	पूर्ण अन्यथा अणु
		/*
		 * For 525/60 प्रणालीs, according to the VIP 2 & BT.656 std:
		 * The EAV RP code's Field bit toggles on line 4, a few lines
		 * after the Vertcal Blank bit has alपढ़ोy toggled.
		 * Tell the encoder to capture 21-4+1=18 lines per field,
		 * since we want lines 10 through 21.
		 *
		 * For 625/50 प्रणालीs, according to the VIP 2 & BT.656 std:
		 * The EAV RP code's Field bit toggles on line 1, a few lines
		 * after the Vertcal Blank bit has alपढ़ोy toggled.
		 * (We've actually set the digitizer so that the Field bit
		 * toggles on line 2.) Tell the encoder to capture 23-2+1=22
		 * lines per field, since we want lines 6 through 23.
		 */
		lines = cx->is_60hz ? (21 - 4 + 1) * 2 : (23 - 2 + 1) * 2;
	पूर्ण

	data[0] = s->handle;
	/* Lines per field */
	data[1] = (lines / 2) | ((lines / 2) << 16);
	/* bytes per line */
	data[2] = (raw ? VBI_ACTIVE_SAMPLES
		       : (cx->is_60hz ? VBI_HBLANK_SAMPLES_60HZ
				      : VBI_HBLANK_SAMPLES_50HZ));
	/* Every X number of frames a VBI पूर्णांकerrupt arrives
	   (frames as in 25 or 30 fps) */
	data[3] = 1;
	/*
	 * Set the SAV/EAV RP codes to look क्रम as start/stop poपूर्णांकs
	 * when in VIP-1.1 mode
	 */
	अगर (raw) अणु
		/*
		 * Start codes क्रम beginning of "active" line in vertical blank
		 * 0x20 (               VerticalBlank                )
		 * 0x60 (     EvenField VerticalBlank                )
		 */
		data[4] = 0x20602060;
		/*
		 * End codes क्रम end of "active" raw lines and regular lines
		 * 0x30 (               VerticalBlank HorizontalBlank)
		 * 0x70 (     EvenField VerticalBlank HorizontalBlank)
		 * 0x90 (Task                         HorizontalBlank)
		 * 0xd0 (Task EvenField               HorizontalBlank)
		 */
		data[5] = 0x307090d0;
	पूर्ण अन्यथा अणु
		/*
		 * End codes क्रम active video, we want data in the hblank region
		 * 0xb0 (Task         0 VerticalBlank HorizontalBlank)
		 * 0xf0 (Task EvenField VerticalBlank HorizontalBlank)
		 *
		 * Since the V bit is only allowed to toggle in the EAV RP code,
		 * just beक्रमe the first active region line, these two
		 * are problematic:
		 * 0x90 (Task                         HorizontalBlank)
		 * 0xd0 (Task EvenField               HorizontalBlank)
		 *
		 * We have set the digitzer such that we करोn't have to worry
		 * about these problem codes.
		 */
		data[4] = 0xB0F0B0F0;
		/*
		 * Start codes क्रम beginning of active line in vertical blank
		 * 0xa0 (Task           VerticalBlank                )
		 * 0xe0 (Task EvenField VerticalBlank                )
		 */
		data[5] = 0xA0E0A0E0;
	पूर्ण

	CX18_DEBUG_INFO("Setup VBI h: %d lines %x bpl %d fr %d %x %x\n",
			data[0], data[1], data[2], data[3], data[4], data[5]);

	cx18_api(cx, CX18_CPU_SET_RAW_VBI_PARAM, 6, data);
पूर्ण

व्योम cx18_stream_rotate_idx_mdls(काष्ठा cx18 *cx)
अणु
	काष्ठा cx18_stream *s = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	काष्ठा cx18_mdl *mdl;

	अगर (!cx18_stream_enabled(s))
		वापस;

	/* Return अगर the firmware is not running low on MDLs */
	अगर ((atomic_पढ़ो(&s->q_मुक्त.depth) + atomic_पढ़ो(&s->q_busy.depth)) >=
					    CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN)
		वापस;

	/* Return अगर there are no MDLs to rotate back to the firmware */
	अगर (atomic_पढ़ो(&s->q_full.depth) < 2)
		वापस;

	/*
	 * Take the oldest IDX MDL still holding data, and discard its index
	 * entries by scheduling the MDL to go back to the firmware
	 */
	mdl = cx18_dequeue(s, &s->q_full);
	अगर (mdl != शून्य)
		cx18_enqueue(s, mdl, &s->q_मुक्त);
पूर्ण

अटल
काष्ठा cx18_queue *_cx18_stream_put_mdl_fw(काष्ठा cx18_stream *s,
					   काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18 *cx = s->cx;
	काष्ठा cx18_queue *q;

	/* Don't give it to the firmware, if we're not running a capture */
	अगर (s->handle == CX18_INVALID_TASK_HANDLE ||
	    test_bit(CX18_F_S_STOPPING, &s->s_flags) ||
	    !test_bit(CX18_F_S_STREAMING, &s->s_flags))
		वापस cx18_enqueue(s, mdl, &s->q_मुक्त);

	q = cx18_enqueue(s, mdl, &s->q_busy);
	अगर (q != &s->q_busy)
		वापस q; /* The firmware has the max MDLs it can handle */

	cx18_mdl_sync_क्रम_device(s, mdl);
	cx18_vapi(cx, CX18_CPU_DE_SET_MDL, 5, s->handle,
		  (व्योम __iomem *) &cx->scb->cpu_mdl[mdl->id] - cx->enc_mem,
		  s->bufs_per_mdl, mdl->id, s->mdl_size);
	वापस q;
पूर्ण

अटल
व्योम _cx18_stream_load_fw_queue(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18_queue *q;
	काष्ठा cx18_mdl *mdl;

	अगर (atomic_पढ़ो(&s->q_मुक्त.depth) == 0 ||
	    atomic_पढ़ो(&s->q_busy.depth) >= CX18_MAX_FW_MDLS_PER_STREAM)
		वापस;

	/* Move from q_मुक्त to q_busy notअगरying the firmware, until the limit */
	करो अणु
		mdl = cx18_dequeue(s, &s->q_मुक्त);
		अगर (mdl == शून्य)
			अवरोध;
		q = _cx18_stream_put_mdl_fw(s, mdl);
	पूर्ण जबतक (atomic_पढ़ो(&s->q_busy.depth) < CX18_MAX_FW_MDLS_PER_STREAM
		 && q == &s->q_busy);
पूर्ण

व्योम cx18_out_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx18_stream *s =
			 container_of(work, काष्ठा cx18_stream, out_work_order);

	_cx18_stream_load_fw_queue(s);
पूर्ण

अटल व्योम cx18_stream_configure_mdls(काष्ठा cx18_stream *s)
अणु
	cx18_unload_queues(s);

	चयन (s->type) अणु
	हाल CX18_ENC_STREAM_TYPE_YUV:
		/*
		 * Height should be a multiple of 32 lines.
		 * Set the MDL size to the exact size needed क्रम one frame.
		 * Use enough buffers per MDL to cover the MDL size
		 */
		अगर (s->pixelक्रमmat == V4L2_PIX_FMT_HM12)
			s->mdl_size = 720 * s->cx->cxhdl.height * 3 / 2;
		अन्यथा
			s->mdl_size = 720 * s->cx->cxhdl.height * 2;
		s->bufs_per_mdl = s->mdl_size / s->buf_size;
		अगर (s->mdl_size % s->buf_size)
			s->bufs_per_mdl++;
		अवरोध;
	हाल CX18_ENC_STREAM_TYPE_VBI:
		s->bufs_per_mdl = 1;
		अगर  (cx18_raw_vbi(s->cx)) अणु
			s->mdl_size = (s->cx->is_60hz ? 12 : 18)
						       * 2 * VBI_ACTIVE_SAMPLES;
		पूर्ण अन्यथा अणु
			/*
			 * See comment in cx18_vbi_setup() below about the
			 * extra lines we capture in sliced VBI mode due to
			 * the lines on which EAV RP codes toggle.
			*/
			s->mdl_size = s->cx->is_60hz
				   ? (21 - 4 + 1) * 2 * VBI_HBLANK_SAMPLES_60HZ
				   : (23 - 2 + 1) * 2 * VBI_HBLANK_SAMPLES_50HZ;
		पूर्ण
		अवरोध;
	शेष:
		s->bufs_per_mdl = 1;
		s->mdl_size = s->buf_size * s->bufs_per_mdl;
		अवरोध;
	पूर्ण

	cx18_load_queues(s);
पूर्ण

पूर्णांक cx18_start_v4l2_encode_stream(काष्ठा cx18_stream *s)
अणु
	u32 data[MAX_MB_ARGUMENTS];
	काष्ठा cx18 *cx = s->cx;
	पूर्णांक captype = 0;
	काष्ठा cx18_stream *s_idx;

	अगर (!cx18_stream_enabled(s))
		वापस -EINVAL;

	CX18_DEBUG_INFO("Start encoder stream %s\n", s->name);

	चयन (s->type) अणु
	हाल CX18_ENC_STREAM_TYPE_MPG:
		captype = CAPTURE_CHANNEL_TYPE_MPEG;
		cx->mpg_data_received = cx->vbi_data_inserted = 0;
		cx->dualwatch_jअगरfies = jअगरfies;
		cx->dualwatch_stereo_mode = v4l2_ctrl_g_ctrl(cx->cxhdl.audio_mode);
		cx->search_pack_header = 0;
		अवरोध;

	हाल CX18_ENC_STREAM_TYPE_IDX:
		captype = CAPTURE_CHANNEL_TYPE_INDEX;
		अवरोध;
	हाल CX18_ENC_STREAM_TYPE_TS:
		captype = CAPTURE_CHANNEL_TYPE_TS;
		अवरोध;
	हाल CX18_ENC_STREAM_TYPE_YUV:
		captype = CAPTURE_CHANNEL_TYPE_YUV;
		अवरोध;
	हाल CX18_ENC_STREAM_TYPE_PCM:
		captype = CAPTURE_CHANNEL_TYPE_PCM;
		अवरोध;
	हाल CX18_ENC_STREAM_TYPE_VBI:
#अगर_घोषित CX18_ENCODER_PARSES_SLICED
		captype = cx18_raw_vbi(cx) ?
		     CAPTURE_CHANNEL_TYPE_VBI : CAPTURE_CHANNEL_TYPE_SLICED_VBI;
#अन्यथा
		/*
		 * Currently we set things up so that Sliced VBI from the
		 * digitizer is handled as Raw VBI by the encoder
		 */
		captype = CAPTURE_CHANNEL_TYPE_VBI;
#पूर्ण_अगर
		cx->vbi.frame = 0;
		cx->vbi.inserted_frame = 0;
		स_रखो(cx->vbi.sliced_mpeg_size,
			0, माप(cx->vbi.sliced_mpeg_size));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Clear Streamoff flags in हाल left from last capture */
	clear_bit(CX18_F_S_STREAMOFF, &s->s_flags);

	cx18_vapi_result(cx, data, CX18_CREATE_TASK, 1, CPU_CMD_MASK_CAPTURE);
	s->handle = data[0];
	cx18_vapi(cx, CX18_CPU_SET_CHANNEL_TYPE, 2, s->handle, captype);

	/*
	 * For everything but CAPTURE_CHANNEL_TYPE_TS, play it safe and
	 * set up all the parameters, as it is not obvious which parameters the
	 * firmware shares across capture channel types and which it करोes not.
	 *
	 * Some of the cx18_vapi() calls below apply to only certain capture
	 * channel types.  We're hoping there's no harm in calling most of them
	 * anyway, as दीर्घ as the values are all consistent.  Setting some
	 * shared parameters will have no effect once an analog capture channel
	 * has started streaming.
	 */
	अगर (captype != CAPTURE_CHANNEL_TYPE_TS) अणु
		cx18_vapi(cx, CX18_CPU_SET_VER_CROP_LINE, 2, s->handle, 0);
		cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 3, s->handle, 3, 1);
		cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 3, s->handle, 8, 0);
		cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 3, s->handle, 4, 1);

		/*
		 * Audio related reset according to
		 * Documentation/driver-api/media/drivers/cx2341x-devel.rst
		 */
		अगर (atomic_पढ़ो(&cx->ana_capturing) == 0)
			cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 2,
				  s->handle, 12);

		/*
		 * Number of lines क्रम Field 1 & Field 2 according to
		 * Documentation/driver-api/media/drivers/cx2341x-devel.rst
		 * Field 1 is 312 क्रम 625 line प्रणालीs in BT.656
		 * Field 2 is 313 क्रम 625 line प्रणालीs in BT.656
		 */
		cx18_vapi(cx, CX18_CPU_SET_CAPTURE_LINE_NO, 3,
			  s->handle, 312, 313);

		अगर (cx->v4l2_cap & V4L2_CAP_VBI_CAPTURE)
			cx18_vbi_setup(s);

		/*
		 * Select to receive I, P, and B frame index entries, अगर the
		 * index stream is enabled.  Otherwise disable index entry
		 * generation.
		 */
		s_idx = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
		cx18_vapi_result(cx, data, CX18_CPU_SET_INDEXTABLE, 2,
				 s->handle, cx18_stream_enabled(s_idx) ? 7 : 0);

		/* Call out to the common CX2341x API setup क्रम user controls */
		cx->cxhdl.priv = s;
		cx2341x_handler_setup(&cx->cxhdl);

		/*
		 * When starting a capture and we're set क्रम radio,
		 * ensure the video is muted, despite the user control.
		 */
		अगर (!cx->cxhdl.video_mute &&
		    test_bit(CX18_F_I_RADIO_USER, &cx->i_flags))
			cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2, s->handle,
			  (v4l2_ctrl_g_ctrl(cx->cxhdl.video_mute_yuv) << 8) | 1);

		/* Enable the Video Format Converter क्रम UYVY 4:2:2 support,
		 * rather than the शेष HM12 Macroblovk 4:2:0 support.
		 */
		अगर (captype == CAPTURE_CHANNEL_TYPE_YUV) अणु
			अगर (s->pixelक्रमmat == V4L2_PIX_FMT_UYVY)
				cx18_vapi(cx, CX18_CPU_SET_VFC_PARAM, 2,
					s->handle, 1);
			अन्यथा
				/* If in करोubt, शेष to HM12 */
				cx18_vapi(cx, CX18_CPU_SET_VFC_PARAM, 2,
					s->handle, 0);
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&cx->tot_capturing) == 0) अणु
		cx2341x_handler_set_busy(&cx->cxhdl, 1);
		clear_bit(CX18_F_I_EOS, &cx->i_flags);
		cx18_ग_लिखो_reg(cx, 7, CX18_DSP0_INTERRUPT_MASK);
	पूर्ण

	cx18_vapi(cx, CX18_CPU_DE_SET_MDL_ACK, 3, s->handle,
		(व्योम __iomem *)&cx->scb->cpu_mdl_ack[s->type][0] - cx->enc_mem,
		(व्योम __iomem *)&cx->scb->cpu_mdl_ack[s->type][1] - cx->enc_mem);

	/* Init all the cpu_mdls क्रम this stream */
	cx18_stream_configure_mdls(s);
	_cx18_stream_load_fw_queue(s);

	/* begin_capture */
	अगर (cx18_vapi(cx, CX18_CPU_CAPTURE_START, 1, s->handle)) अणु
		CX18_DEBUG_WARN("Error starting capture!\n");
		/* Ensure we're really not capturing beक्रमe releasing MDLs */
		set_bit(CX18_F_S_STOPPING, &s->s_flags);
		अगर (s->type == CX18_ENC_STREAM_TYPE_MPG)
			cx18_vapi(cx, CX18_CPU_CAPTURE_STOP, 2, s->handle, 1);
		अन्यथा
			cx18_vapi(cx, CX18_CPU_CAPTURE_STOP, 1, s->handle);
		clear_bit(CX18_F_S_STREAMING, &s->s_flags);
		/* FIXME - CX18_F_S_STREAMOFF as well? */
		cx18_vapi(cx, CX18_CPU_DE_RELEASE_MDL, 1, s->handle);
		cx18_vapi(cx, CX18_DESTROY_TASK, 1, s->handle);
		s->handle = CX18_INVALID_TASK_HANDLE;
		clear_bit(CX18_F_S_STOPPING, &s->s_flags);
		अगर (atomic_पढ़ो(&cx->tot_capturing) == 0) अणु
			set_bit(CX18_F_I_EOS, &cx->i_flags);
			cx18_ग_लिखो_reg(cx, 5, CX18_DSP0_INTERRUPT_MASK);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/* you're live! sit back and aरुको पूर्णांकerrupts :) */
	अगर (captype != CAPTURE_CHANNEL_TYPE_TS)
		atomic_inc(&cx->ana_capturing);
	atomic_inc(&cx->tot_capturing);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx18_start_v4l2_encode_stream);

व्योम cx18_stop_all_captures(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;

	क्रम (i = CX18_MAX_STREAMS - 1; i >= 0; i--) अणु
		काष्ठा cx18_stream *s = &cx->streams[i];

		अगर (!cx18_stream_enabled(s))
			जारी;
		अगर (test_bit(CX18_F_S_STREAMING, &s->s_flags))
			cx18_stop_v4l2_encode_stream(s, 0);
	पूर्ण
पूर्ण

पूर्णांक cx18_stop_v4l2_encode_stream(काष्ठा cx18_stream *s, पूर्णांक gop_end)
अणु
	काष्ठा cx18 *cx = s->cx;

	अगर (!cx18_stream_enabled(s))
		वापस -EINVAL;

	/* This function assumes that you are allowed to stop the capture
	   and that we are actually capturing */

	CX18_DEBUG_INFO("Stop Capture\n");

	अगर (atomic_पढ़ो(&cx->tot_capturing) == 0)
		वापस 0;

	set_bit(CX18_F_S_STOPPING, &s->s_flags);
	अगर (s->type == CX18_ENC_STREAM_TYPE_MPG)
		cx18_vapi(cx, CX18_CPU_CAPTURE_STOP, 2, s->handle, !gop_end);
	अन्यथा
		cx18_vapi(cx, CX18_CPU_CAPTURE_STOP, 1, s->handle);

	अगर (s->type == CX18_ENC_STREAM_TYPE_MPG && gop_end) अणु
		CX18_INFO("ignoring gop_end: not (yet?) supported by the firmware\n");
	पूर्ण

	अगर (s->type != CX18_ENC_STREAM_TYPE_TS)
		atomic_dec(&cx->ana_capturing);
	atomic_dec(&cx->tot_capturing);

	/* Clear capture and no-पढ़ो bits */
	clear_bit(CX18_F_S_STREAMING, &s->s_flags);

	/* Tell the CX23418 it can't use our buffers anymore */
	cx18_vapi(cx, CX18_CPU_DE_RELEASE_MDL, 1, s->handle);

	cx18_vapi(cx, CX18_DESTROY_TASK, 1, s->handle);
	s->handle = CX18_INVALID_TASK_HANDLE;
	clear_bit(CX18_F_S_STOPPING, &s->s_flags);

	अगर (atomic_पढ़ो(&cx->tot_capturing) > 0)
		वापस 0;

	cx2341x_handler_set_busy(&cx->cxhdl, 0);
	cx18_ग_लिखो_reg(cx, 5, CX18_DSP0_INTERRUPT_MASK);
	wake_up(&s->रुकोq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx18_stop_v4l2_encode_stream);

u32 cx18_find_handle(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;

	/* find first available handle to be used क्रम global settings */
	क्रम (i = 0; i < CX18_MAX_STREAMS; i++) अणु
		काष्ठा cx18_stream *s = &cx->streams[i];

		अगर (s->video_dev.v4l2_dev && (s->handle != CX18_INVALID_TASK_HANDLE))
			वापस s->handle;
	पूर्ण
	वापस CX18_INVALID_TASK_HANDLE;
पूर्ण

काष्ठा cx18_stream *cx18_handle_to_stream(काष्ठा cx18 *cx, u32 handle)
अणु
	पूर्णांक i;
	काष्ठा cx18_stream *s;

	अगर (handle == CX18_INVALID_TASK_HANDLE)
		वापस शून्य;

	क्रम (i = 0; i < CX18_MAX_STREAMS; i++) अणु
		s = &cx->streams[i];
		अगर (s->handle != handle)
			जारी;
		अगर (cx18_stream_enabled(s))
			वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण
