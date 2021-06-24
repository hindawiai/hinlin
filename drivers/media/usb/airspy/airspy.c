<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AirSpy SDR driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

/* AirSpy USB API commands (from AirSpy Library) */
क्रमागत अणु
	CMD_INVALID                       = 0x00,
	CMD_RECEIVER_MODE                 = 0x01,
	CMD_SI5351C_WRITE                 = 0x02,
	CMD_SI5351C_READ                  = 0x03,
	CMD_R820T_WRITE                   = 0x04,
	CMD_R820T_READ                    = 0x05,
	CMD_SPIFLASH_ERASE                = 0x06,
	CMD_SPIFLASH_WRITE                = 0x07,
	CMD_SPIFLASH_READ                 = 0x08,
	CMD_BOARD_ID_READ                 = 0x09,
	CMD_VERSION_STRING_READ           = 0x0a,
	CMD_BOARD_PARTID_SERIALNO_READ    = 0x0b,
	CMD_SET_SAMPLE_RATE               = 0x0c,
	CMD_SET_FREQ                      = 0x0d,
	CMD_SET_LNA_GAIN                  = 0x0e,
	CMD_SET_MIXER_GAIN                = 0x0f,
	CMD_SET_VGA_GAIN                  = 0x10,
	CMD_SET_LNA_AGC                   = 0x11,
	CMD_SET_MIXER_AGC                 = 0x12,
	CMD_SET_PACKING                   = 0x13,
पूर्ण;

/*
 *       bEndpoपूर्णांकAddress     0x81  EP 1 IN
 *         Transfer Type            Bulk
 *       wMaxPacketSize     0x0200  1x 512 bytes
 */
#घोषणा MAX_BULK_BUFS            (6)
#घोषणा BULK_BUFFER_SIZE         (128 * 512)

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = 20000000,
		.rangehigh  = 20000000,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands_rf[] = अणु
	अणु
		.tuner = 1,
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =   24000000,
		.rangehigh  = 1750000000,
	पूर्ण,
पूर्ण;

/* stream क्रमmats */
काष्ठा airspy_क्रमmat अणु
	u32	pixelक्रमmat;
	u32	buffersize;
पूर्ण;

/* क्रमmat descriptions क्रम capture and preview */
अटल काष्ठा airspy_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_RU12LE,
		.buffersize	= BULK_BUFFER_SIZE,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक NUM_FORMATS = ARRAY_SIZE(क्रमmats);

/* पूर्णांकermediate buffers with raw data from the USB device */
काष्ठा airspy_frame_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा airspy अणु
#घोषणा POWER_ON	   1
#घोषणा USB_STATE_URB_BUF  2
	अचिन्हित दीर्घ flags;

	काष्ठा device *dev;
	काष्ठा usb_device *udev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;

	/* videobuf2 queue and queued buffers list */
	काष्ठा vb2_queue vb_queue;
	काष्ठा list_head queued_bufs;
	spinlock_t queued_bufs_lock; /* Protects queued_bufs */
	अचिन्हित sequence;	     /* Buffer sequence counter */
	अचिन्हित पूर्णांक vb_full;        /* vb is full and packets dropped */

	/* Note अगर taking both locks v4l2_lock must always be locked first! */
	काष्ठा mutex v4l2_lock;      /* Protects everything अन्यथा */
	काष्ठा mutex vb_queue_lock;  /* Protects vb_queue and capt_file */

	काष्ठा urb     *urb_list[MAX_BULK_BUFS];
	पूर्णांक            buf_num;
	अचिन्हित दीर्घ  buf_size;
	u8             *buf_list[MAX_BULK_BUFS];
	dma_addr_t     dma_addr[MAX_BULK_BUFS];
	पूर्णांक            urbs_initialized;
	पूर्णांक            urbs_submitted;

	/* USB control message buffer */
	#घोषणा BUF_SIZE 128
	u8 buf[BUF_SIZE];

	/* Current configuration */
	अचिन्हित पूर्णांक f_adc;
	अचिन्हित पूर्णांक f_rf;
	u32 pixelक्रमmat;
	u32 buffersize;

	/* Controls */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *lna_gain_स्वतः;
	काष्ठा v4l2_ctrl *lna_gain;
	काष्ठा v4l2_ctrl *mixer_gain_स्वतः;
	काष्ठा v4l2_ctrl *mixer_gain;
	काष्ठा v4l2_ctrl *अगर_gain;

	/* Sample rate calc */
	अचिन्हित दीर्घ jअगरfies_next;
	अचिन्हित पूर्णांक sample;
	अचिन्हित पूर्णांक sample_measured;
पूर्ण;

#घोषणा airspy_dbg_usb_control_msg(_dev, _r, _t, _v, _i, _b, _l) अणु \
	अक्षर *_direction; \
	अगर (_t & USB_सूची_IN) \
		_direction = "<<<"; \
	अन्यथा \
		_direction = ">>>"; \
	dev_dbg(_dev, "%02x %02x %02x %02x %02x %02x %02x %02x %s %*ph\n", \
			_t, _r, _v & 0xff, _v >> 8, _i & 0xff, _i >> 8, \
			_l & 0xff, _l >> 8, _direction, _l, _b); \
पूर्ण

/* execute firmware command */
अटल पूर्णांक airspy_ctrl_msg(काष्ठा airspy *s, u8 request, u16 value, u16 index,
		u8 *data, u16 size)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	u8 requesttype;

	चयन (request) अणु
	हाल CMD_RECEIVER_MODE:
	हाल CMD_SET_FREQ:
		pipe = usb_sndctrlpipe(s->udev, 0);
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		अवरोध;
	हाल CMD_BOARD_ID_READ:
	हाल CMD_VERSION_STRING_READ:
	हाल CMD_BOARD_PARTID_SERIALNO_READ:
	हाल CMD_SET_LNA_GAIN:
	हाल CMD_SET_MIXER_GAIN:
	हाल CMD_SET_VGA_GAIN:
	हाल CMD_SET_LNA_AGC:
	हाल CMD_SET_MIXER_AGC:
		pipe = usb_rcvctrlpipe(s->udev, 0);
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		अवरोध;
	शेष:
		dev_err(s->dev, "Unknown command %02x\n", request);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* ग_लिखो request */
	अगर (!(requesttype & USB_सूची_IN))
		स_नकल(s->buf, data, size);

	ret = usb_control_msg(s->udev, pipe, request, requesttype, value,
			index, s->buf, size, 1000);
	airspy_dbg_usb_control_msg(s->dev, request, requesttype, value,
			index, s->buf, size);
	अगर (ret < 0) अणु
		dev_err(s->dev, "usb_control_msg() failed %d request %02x\n",
				ret, request);
		जाओ err;
	पूर्ण

	/* पढ़ो request */
	अगर (requesttype & USB_सूची_IN)
		स_नकल(data, s->buf, size);

	वापस 0;
err:
	वापस ret;
पूर्ण

/* Private functions */
अटल काष्ठा airspy_frame_buf *airspy_get_next_fill_buf(काष्ठा airspy *s)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा airspy_frame_buf *buf = शून्य;

	spin_lock_irqsave(&s->queued_bufs_lock, flags);
	अगर (list_empty(&s->queued_bufs))
		जाओ leave;

	buf = list_entry(s->queued_bufs.next,
			काष्ठा airspy_frame_buf, list);
	list_del(&buf->list);
leave:
	spin_unlock_irqrestore(&s->queued_bufs_lock, flags);
	वापस buf;
पूर्ण

अटल अचिन्हित पूर्णांक airspy_convert_stream(काष्ठा airspy *s,
		व्योम *dst, व्योम *src, अचिन्हित पूर्णांक src_len)
अणु
	अचिन्हित पूर्णांक dst_len;

	अगर (s->pixelक्रमmat == V4L2_SDR_FMT_RU12LE) अणु
		स_नकल(dst, src, src_len);
		dst_len = src_len;
	पूर्ण अन्यथा अणु
		dst_len = 0;
	पूर्ण

	/* calculate sample rate and output it in 10 seconds पूर्णांकervals */
	अगर (unlikely(समय_is_beक्रमe_jअगरfies(s->jअगरfies_next))) अणु
		#घोषणा MSECS 10000UL
		अचिन्हित पूर्णांक msecs = jअगरfies_to_msecs(jअगरfies -
				s->jअगरfies_next + msecs_to_jअगरfies(MSECS));
		अचिन्हित पूर्णांक samples = s->sample - s->sample_measured;

		s->jअगरfies_next = jअगरfies + msecs_to_jअगरfies(MSECS);
		s->sample_measured = s->sample;
		dev_dbg(s->dev, "slen=%u samples=%u msecs=%u sample rate=%lu\n",
				src_len, samples, msecs,
				samples * 1000UL / msecs);
	पूर्ण

	/* total number of samples */
	s->sample += src_len / 2;

	वापस dst_len;
पूर्ण

/*
 * This माला_लो called क्रम the bulk stream pipe. This is करोne in पूर्णांकerrupt
 * समय, so it has to be fast, not crash, and not stall. Neat.
 */
अटल व्योम airspy_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा airspy *s = urb->context;
	काष्ठा airspy_frame_buf *fbuf;

	dev_dbg_ratelimited(s->dev, "status=%d length=%d/%d errors=%d\n",
			urb->status, urb->actual_length,
			urb->transfer_buffer_length, urb->error_count);

	चयन (urb->status) अणु
	हाल 0:             /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:            /* error */
		dev_err_ratelimited(s->dev, "URB failed %d\n", urb->status);
		अवरोध;
	पूर्ण

	अगर (likely(urb->actual_length > 0)) अणु
		व्योम *ptr;
		अचिन्हित पूर्णांक len;
		/* get मुक्त framebuffer */
		fbuf = airspy_get_next_fill_buf(s);
		अगर (unlikely(fbuf == शून्य)) अणु
			s->vb_full++;
			dev_notice_ratelimited(s->dev,
					"videobuf is full, %d packets dropped\n",
					s->vb_full);
			जाओ skip;
		पूर्ण

		/* fill framebuffer */
		ptr = vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0);
		len = airspy_convert_stream(s, ptr, urb->transfer_buffer,
				urb->actual_length);
		vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0, len);
		fbuf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		fbuf->vb.sequence = s->sequence++;
		vb2_buffer_करोne(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण
skip:
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक airspy_समाप्त_urbs(काष्ठा airspy *s)
अणु
	पूर्णांक i;

	क्रम (i = s->urbs_submitted - 1; i >= 0; i--) अणु
		dev_dbg(s->dev, "kill urb=%d\n", i);
		/* stop the URB */
		usb_समाप्त_urb(s->urb_list[i]);
	पूर्ण
	s->urbs_submitted = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_submit_urbs(काष्ठा airspy *s)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < s->urbs_initialized; i++) अणु
		dev_dbg(s->dev, "submit urb=%d\n", i);
		ret = usb_submit_urb(s->urb_list[i], GFP_ATOMIC);
		अगर (ret) अणु
			dev_err(s->dev, "Could not submit URB no. %d - get them all back\n",
					i);
			airspy_समाप्त_urbs(s);
			वापस ret;
		पूर्ण
		s->urbs_submitted++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_मुक्त_stream_bufs(काष्ठा airspy *s)
अणु
	अगर (test_bit(USB_STATE_URB_BUF, &s->flags)) अणु
		जबतक (s->buf_num) अणु
			s->buf_num--;
			dev_dbg(s->dev, "free buf=%d\n", s->buf_num);
			usb_मुक्त_coherent(s->udev, s->buf_size,
					  s->buf_list[s->buf_num],
					  s->dma_addr[s->buf_num]);
		पूर्ण
	पूर्ण
	clear_bit(USB_STATE_URB_BUF, &s->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_alloc_stream_bufs(काष्ठा airspy *s)
अणु
	s->buf_num = 0;
	s->buf_size = BULK_BUFFER_SIZE;

	dev_dbg(s->dev, "all in all I will use %u bytes for streaming\n",
			MAX_BULK_BUFS * BULK_BUFFER_SIZE);

	क्रम (s->buf_num = 0; s->buf_num < MAX_BULK_BUFS; s->buf_num++) अणु
		s->buf_list[s->buf_num] = usb_alloc_coherent(s->udev,
				BULK_BUFFER_SIZE, GFP_ATOMIC,
				&s->dma_addr[s->buf_num]);
		अगर (!s->buf_list[s->buf_num]) अणु
			dev_dbg(s->dev, "alloc buf=%d failed\n", s->buf_num);
			airspy_मुक्त_stream_bufs(s);
			वापस -ENOMEM;
		पूर्ण

		dev_dbg(s->dev, "alloc buf=%d %p (dma %llu)\n", s->buf_num,
				s->buf_list[s->buf_num],
				(दीर्घ दीर्घ)s->dma_addr[s->buf_num]);
		set_bit(USB_STATE_URB_BUF, &s->flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_मुक्त_urbs(काष्ठा airspy *s)
अणु
	पूर्णांक i;

	airspy_समाप्त_urbs(s);

	क्रम (i = s->urbs_initialized - 1; i >= 0; i--) अणु
		अगर (s->urb_list[i]) अणु
			dev_dbg(s->dev, "free urb=%d\n", i);
			/* मुक्त the URBs */
			usb_मुक्त_urb(s->urb_list[i]);
		पूर्ण
	पूर्ण
	s->urbs_initialized = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_alloc_urbs(काष्ठा airspy *s)
अणु
	पूर्णांक i, j;

	/* allocate the URBs */
	क्रम (i = 0; i < MAX_BULK_BUFS; i++) अणु
		dev_dbg(s->dev, "alloc urb=%d\n", i);
		s->urb_list[i] = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!s->urb_list[i]) अणु
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(s->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण
		usb_fill_bulk_urb(s->urb_list[i],
				s->udev,
				usb_rcvbulkpipe(s->udev, 0x81),
				s->buf_list[i],
				BULK_BUFFER_SIZE,
				airspy_urb_complete, s);

		s->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		s->urb_list[i]->transfer_dma = s->dma_addr[i];
		s->urbs_initialized++;
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called with vb_queue_lock hold */
अटल व्योम airspy_cleanup_queued_bufs(काष्ठा airspy *s)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(s->dev, "\n");

	spin_lock_irqsave(&s->queued_bufs_lock, flags);
	जबतक (!list_empty(&s->queued_bufs)) अणु
		काष्ठा airspy_frame_buf *buf;

		buf = list_entry(s->queued_bufs.next,
				काष्ठा airspy_frame_buf, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&s->queued_bufs_lock, flags);
पूर्ण

/* The user yanked out the cable... */
अटल व्योम airspy_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा v4l2_device *v = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा airspy *s = container_of(v, काष्ठा airspy, v4l2_dev);

	dev_dbg(s->dev, "\n");

	mutex_lock(&s->vb_queue_lock);
	mutex_lock(&s->v4l2_lock);
	/* No need to keep the urbs around after disconnection */
	s->udev = शून्य;
	v4l2_device_disconnect(&s->v4l2_dev);
	video_unरेजिस्टर_device(&s->vdev);
	mutex_unlock(&s->v4l2_lock);
	mutex_unlock(&s->vb_queue_lock);

	v4l2_device_put(&s->v4l2_dev);
पूर्ण

/* Videobuf2 operations */
अटल पूर्णांक airspy_queue_setup(काष्ठा vb2_queue *vq,
		अचिन्हित पूर्णांक *nbuffers,
		अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा airspy *s = vb2_get_drv_priv(vq);

	dev_dbg(s->dev, "nbuffers=%d\n", *nbuffers);

	/* Need at least 8 buffers */
	अगर (vq->num_buffers + *nbuffers < 8)
		*nbuffers = 8 - vq->num_buffers;
	*nplanes = 1;
	sizes[0] = PAGE_ALIGN(s->buffersize);

	dev_dbg(s->dev, "nbuffers=%d sizes[0]=%d\n", *nbuffers, sizes[0]);
	वापस 0;
पूर्ण

अटल व्योम airspy_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा airspy *s = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा airspy_frame_buf *buf =
			container_of(vbuf, काष्ठा airspy_frame_buf, vb);
	अचिन्हित दीर्घ flags;

	/* Check the device has not disconnected between prep and queuing */
	अगर (unlikely(!s->udev)) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&s->queued_bufs_lock, flags);
	list_add_tail(&buf->list, &s->queued_bufs);
	spin_unlock_irqrestore(&s->queued_bufs_lock, flags);
पूर्ण

अटल पूर्णांक airspy_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा airspy *s = vb2_get_drv_priv(vq);
	पूर्णांक ret;

	dev_dbg(s->dev, "\n");

	अगर (!s->udev)
		वापस -ENODEV;

	mutex_lock(&s->v4l2_lock);

	s->sequence = 0;

	set_bit(POWER_ON, &s->flags);

	ret = airspy_alloc_stream_bufs(s);
	अगर (ret)
		जाओ err_clear_bit;

	ret = airspy_alloc_urbs(s);
	अगर (ret)
		जाओ err_मुक्त_stream_bufs;

	ret = airspy_submit_urbs(s);
	अगर (ret)
		जाओ err_मुक्त_urbs;

	/* start hardware streaming */
	ret = airspy_ctrl_msg(s, CMD_RECEIVER_MODE, 1, 0, शून्य, 0);
	अगर (ret)
		जाओ err_समाप्त_urbs;

	जाओ निकास_mutex_unlock;

err_समाप्त_urbs:
	airspy_समाप्त_urbs(s);
err_मुक्त_urbs:
	airspy_मुक्त_urbs(s);
err_मुक्त_stream_bufs:
	airspy_मुक्त_stream_bufs(s);
err_clear_bit:
	clear_bit(POWER_ON, &s->flags);

	/* वापस all queued buffers to vb2 */
	अणु
		काष्ठा airspy_frame_buf *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &s->queued_bufs, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण

निकास_mutex_unlock:
	mutex_unlock(&s->v4l2_lock);

	वापस ret;
पूर्ण

अटल व्योम airspy_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा airspy *s = vb2_get_drv_priv(vq);

	dev_dbg(s->dev, "\n");

	mutex_lock(&s->v4l2_lock);

	/* stop hardware streaming */
	airspy_ctrl_msg(s, CMD_RECEIVER_MODE, 0, 0, शून्य, 0);

	airspy_समाप्त_urbs(s);
	airspy_मुक्त_urbs(s);
	airspy_मुक्त_stream_bufs(s);

	airspy_cleanup_queued_bufs(s);

	clear_bit(POWER_ON, &s->flags);

	mutex_unlock(&s->v4l2_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops airspy_vb2_ops = अणु
	.queue_setup            = airspy_queue_setup,
	.buf_queue              = airspy_buf_queue,
	.start_streaming        = airspy_start_streaming,
	.stop_streaming         = airspy_stop_streaming,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक airspy_querycap(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_capability *cap)
अणु
	काष्ठा airspy *s = video_drvdata(file);

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, s->vdev.name, माप(cap->card));
	usb_make_path(s->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक airspy_क्रमागत_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= NUM_FORMATS)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_g_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा airspy *s = video_drvdata(file);

	f->fmt.sdr.pixelक्रमmat = s->pixelक्रमmat;
	f->fmt.sdr.buffersize = s->buffersize;
	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_s_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा airspy *s = video_drvdata(file);
	काष्ठा vb2_queue *q = &s->vb_queue;
	पूर्णांक i;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			s->pixelक्रमmat = क्रमmats[i].pixelक्रमmat;
			s->buffersize = क्रमmats[i].buffersize;
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	s->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	s->buffersize = क्रमmats[0].buffersize;
	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_try_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक i;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक airspy_s_tuner(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_tuner *v)
अणु
	पूर्णांक ret;

	अगर (v->index == 0)
		ret = 0;
	अन्यथा अगर (v->index == 1)
		ret = 0;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *v)
अणु
	पूर्णांक ret;

	अगर (v->index == 0) अणु
		strscpy(v->name, "AirSpy ADC", माप(v->name));
		v->type = V4L2_TUNER_ADC;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow  = bands[0].rangelow;
		v->rangehigh = bands[0].rangehigh;
		ret = 0;
	पूर्ण अन्यथा अगर (v->index == 1) अणु
		strscpy(v->name, "AirSpy RF", माप(v->name));
		v->type = V4L2_TUNER_RF;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow  = bands_rf[0].rangelow;
		v->rangehigh = bands_rf[0].rangehigh;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_g_frequency(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency *f)
अणु
	काष्ठा airspy *s = video_drvdata(file);
	पूर्णांक ret;

	अगर (f->tuner == 0) अणु
		f->type = V4L2_TUNER_ADC;
		f->frequency = s->f_adc;
		dev_dbg(s->dev, "ADC frequency=%u Hz\n", s->f_adc);
		ret = 0;
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		f->type = V4L2_TUNER_RF;
		f->frequency = s->f_rf;
		dev_dbg(s->dev, "RF frequency=%u Hz\n", s->f_rf);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_s_frequency(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा airspy *s = video_drvdata(file);
	पूर्णांक ret;
	u8 buf[4];

	अगर (f->tuner == 0) अणु
		s->f_adc = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				bands[0].rangelow,
				bands[0].rangehigh);
		dev_dbg(s->dev, "ADC frequency=%u Hz\n", s->f_adc);
		ret = 0;
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		s->f_rf = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				bands_rf[0].rangelow,
				bands_rf[0].rangehigh);
		dev_dbg(s->dev, "RF frequency=%u Hz\n", s->f_rf);
		buf[0] = (s->f_rf >>  0) & 0xff;
		buf[1] = (s->f_rf >>  8) & 0xff;
		buf[2] = (s->f_rf >> 16) & 0xff;
		buf[3] = (s->f_rf >> 24) & 0xff;
		ret = airspy_ctrl_msg(s, CMD_SET_FREQ, 0, 0, buf, 4);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency_band *band)
अणु
	पूर्णांक ret;

	अगर (band->tuner == 0) अणु
		अगर (band->index >= ARRAY_SIZE(bands)) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			*band = bands[band->index];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (band->tuner == 1) अणु
		अगर (band->index >= ARRAY_SIZE(bands_rf)) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			*band = bands_rf[band->index];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops airspy_ioctl_ops = अणु
	.vidioc_querycap          = airspy_querycap,

	.vidioc_क्रमागत_fmt_sdr_cap  = airspy_क्रमागत_fmt_sdr_cap,
	.vidioc_g_fmt_sdr_cap     = airspy_g_fmt_sdr_cap,
	.vidioc_s_fmt_sdr_cap     = airspy_s_fmt_sdr_cap,
	.vidioc_try_fmt_sdr_cap   = airspy_try_fmt_sdr_cap,

	.vidioc_reqbufs           = vb2_ioctl_reqbufs,
	.vidioc_create_bufs       = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf       = vb2_ioctl_prepare_buf,
	.vidioc_querybuf          = vb2_ioctl_querybuf,
	.vidioc_qbuf              = vb2_ioctl_qbuf,
	.vidioc_dqbuf             = vb2_ioctl_dqbuf,

	.vidioc_streamon          = vb2_ioctl_streamon,
	.vidioc_streamoff         = vb2_ioctl_streamoff,

	.vidioc_g_tuner           = airspy_g_tuner,
	.vidioc_s_tuner           = airspy_s_tuner,

	.vidioc_g_frequency       = airspy_g_frequency,
	.vidioc_s_frequency       = airspy_s_frequency,
	.vidioc_क्रमागत_freq_bands   = airspy_क्रमागत_freq_bands,

	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_log_status        = v4l2_ctrl_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations airspy_fops = अणु
	.owner                    = THIS_MODULE,
	.खोलो                     = v4l2_fh_खोलो,
	.release                  = vb2_fop_release,
	.पढ़ो                     = vb2_fop_पढ़ो,
	.poll                     = vb2_fop_poll,
	.mmap                     = vb2_fop_mmap,
	.unlocked_ioctl           = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा video_device airspy_ढाँचा = अणु
	.name                     = "AirSpy SDR",
	.release                  = video_device_release_empty,
	.fops                     = &airspy_fops,
	.ioctl_ops                = &airspy_ioctl_ops,
पूर्ण;

अटल व्योम airspy_video_release(काष्ठा v4l2_device *v)
अणु
	काष्ठा airspy *s = container_of(v, काष्ठा airspy, v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&s->hdl);
	v4l2_device_unरेजिस्टर(&s->v4l2_dev);
	kमुक्त(s);
पूर्ण

अटल पूर्णांक airspy_set_lna_gain(काष्ठा airspy *s)
अणु
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(s->dev, "lna auto=%d->%d val=%d->%d\n",
			s->lna_gain_स्वतः->cur.val, s->lna_gain_स्वतः->val,
			s->lna_gain->cur.val, s->lna_gain->val);

	ret = airspy_ctrl_msg(s, CMD_SET_LNA_AGC, 0, s->lna_gain_स्वतः->val,
			&u8पंचांगp, 1);
	अगर (ret)
		जाओ err;

	अगर (s->lna_gain_स्वतः->val == false) अणु
		ret = airspy_ctrl_msg(s, CMD_SET_LNA_GAIN, 0, s->lna_gain->val,
				&u8पंचांगp, 1);
		अगर (ret)
			जाओ err;
	पूर्ण
err:
	अगर (ret)
		dev_dbg(s->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_set_mixer_gain(काष्ठा airspy *s)
अणु
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(s->dev, "mixer auto=%d->%d val=%d->%d\n",
			s->mixer_gain_स्वतः->cur.val, s->mixer_gain_स्वतः->val,
			s->mixer_gain->cur.val, s->mixer_gain->val);

	ret = airspy_ctrl_msg(s, CMD_SET_MIXER_AGC, 0, s->mixer_gain_स्वतः->val,
			&u8पंचांगp, 1);
	अगर (ret)
		जाओ err;

	अगर (s->mixer_gain_स्वतः->val == false) अणु
		ret = airspy_ctrl_msg(s, CMD_SET_MIXER_GAIN, 0,
				s->mixer_gain->val, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;
	पूर्ण
err:
	अगर (ret)
		dev_dbg(s->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_set_अगर_gain(काष्ठा airspy *s)
अणु
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(s->dev, "val=%d->%d\n", s->अगर_gain->cur.val, s->अगर_gain->val);

	ret = airspy_ctrl_msg(s, CMD_SET_VGA_GAIN, 0, s->अगर_gain->val,
			&u8पंचांगp, 1);
	अगर (ret)
		dev_dbg(s->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक airspy_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा airspy *s = container_of(ctrl->handler, काष्ठा airspy, hdl);
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN_AUTO:
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN:
		ret = airspy_set_lna_gain(s);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO:
	हाल  V4L2_CID_RF_TUNER_MIXER_GAIN:
		ret = airspy_set_mixer_gain(s);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_IF_GAIN:
		ret = airspy_set_अगर_gain(s);
		अवरोध;
	शेष:
		dev_dbg(s->dev, "unknown ctrl: id=%d name=%s\n",
				ctrl->id, ctrl->name);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops airspy_ctrl_ops = अणु
	.s_ctrl = airspy_s_ctrl,
पूर्ण;

अटल पूर्णांक airspy_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा airspy *s;
	पूर्णांक ret;
	u8 u8पंचांगp, buf[BUF_SIZE];

	s = kzalloc(माप(काष्ठा airspy), GFP_KERNEL);
	अगर (s == शून्य) अणु
		dev_err(&पूर्णांकf->dev, "Could not allocate memory for state\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&s->v4l2_lock);
	mutex_init(&s->vb_queue_lock);
	spin_lock_init(&s->queued_bufs_lock);
	INIT_LIST_HEAD(&s->queued_bufs);
	s->dev = &पूर्णांकf->dev;
	s->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	s->f_adc = bands[0].rangelow;
	s->f_rf = bands_rf[0].rangelow;
	s->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	s->buffersize = क्रमmats[0].buffersize;

	/* Detect device */
	ret = airspy_ctrl_msg(s, CMD_BOARD_ID_READ, 0, 0, &u8पंचांगp, 1);
	अगर (ret == 0)
		ret = airspy_ctrl_msg(s, CMD_VERSION_STRING_READ, 0, 0,
				buf, BUF_SIZE);
	अगर (ret) अणु
		dev_err(s->dev, "Could not detect board\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	buf[BUF_SIZE - 1] = '\0';

	dev_info(s->dev, "Board ID: %02x\n", u8पंचांगp);
	dev_info(s->dev, "Firmware version: %s\n", buf);

	/* Init videobuf2 queue काष्ठाure */
	s->vb_queue.type = V4L2_BUF_TYPE_SDR_CAPTURE;
	s->vb_queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	s->vb_queue.drv_priv = s;
	s->vb_queue.buf_काष्ठा_size = माप(काष्ठा airspy_frame_buf);
	s->vb_queue.ops = &airspy_vb2_ops;
	s->vb_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	s->vb_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	ret = vb2_queue_init(&s->vb_queue);
	अगर (ret) अणु
		dev_err(s->dev, "Could not initialize vb2 queue\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	/* Init video_device काष्ठाure */
	s->vdev = airspy_ढाँचा;
	s->vdev.queue = &s->vb_queue;
	s->vdev.queue->lock = &s->vb_queue_lock;
	video_set_drvdata(&s->vdev, s);

	/* Register the v4l2_device काष्ठाure */
	s->v4l2_dev.release = airspy_video_release;
	ret = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &s->v4l2_dev);
	अगर (ret) अणु
		dev_err(s->dev, "Failed to register v4l2-device (%d)\n", ret);
		जाओ err_मुक्त_mem;
	पूर्ण

	/* Register controls */
	v4l2_ctrl_handler_init(&s->hdl, 5);
	s->lna_gain_स्वतः = v4l2_ctrl_new_std(&s->hdl, &airspy_ctrl_ops,
			V4L2_CID_RF_TUNER_LNA_GAIN_AUTO, 0, 1, 1, 0);
	s->lna_gain = v4l2_ctrl_new_std(&s->hdl, &airspy_ctrl_ops,
			V4L2_CID_RF_TUNER_LNA_GAIN, 0, 14, 1, 8);
	v4l2_ctrl_स्वतः_cluster(2, &s->lna_gain_स्वतः, 0, false);
	s->mixer_gain_स्वतः = v4l2_ctrl_new_std(&s->hdl, &airspy_ctrl_ops,
			V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO, 0, 1, 1, 0);
	s->mixer_gain = v4l2_ctrl_new_std(&s->hdl, &airspy_ctrl_ops,
			V4L2_CID_RF_TUNER_MIXER_GAIN, 0, 15, 1, 8);
	v4l2_ctrl_स्वतः_cluster(2, &s->mixer_gain_स्वतः, 0, false);
	s->अगर_gain = v4l2_ctrl_new_std(&s->hdl, &airspy_ctrl_ops,
			V4L2_CID_RF_TUNER_IF_GAIN, 0, 15, 1, 0);
	अगर (s->hdl.error) अणु
		ret = s->hdl.error;
		dev_err(s->dev, "Could not initialize controls\n");
		जाओ err_मुक्त_controls;
	पूर्ण

	v4l2_ctrl_handler_setup(&s->hdl);

	s->v4l2_dev.ctrl_handler = &s->hdl;
	s->vdev.v4l2_dev = &s->v4l2_dev;
	s->vdev.lock = &s->v4l2_lock;
	s->vdev.device_caps = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_STREAMING |
			      V4L2_CAP_READWRITE | V4L2_CAP_TUNER;

	ret = video_रेजिस्टर_device(&s->vdev, VFL_TYPE_SDR, -1);
	अगर (ret) अणु
		dev_err(s->dev, "Failed to register as video device (%d)\n",
				ret);
		जाओ err_मुक्त_controls;
	पूर्ण
	dev_info(s->dev, "Registered as %s\n",
			video_device_node_name(&s->vdev));
	dev_notice(s->dev, "SDR API is still slightly experimental and functionality changes may follow\n");
	वापस 0;

err_मुक्त_controls:
	v4l2_ctrl_handler_मुक्त(&s->hdl);
	v4l2_device_unरेजिस्टर(&s->v4l2_dev);
err_मुक्त_mem:
	kमुक्त(s);
	वापस ret;
पूर्ण

/* USB device ID list */
अटल स्थिर काष्ठा usb_device_id airspy_id_table[] = अणु
	अणु USB_DEVICE(0x1d50, 0x60a1) पूर्ण, /* AirSpy */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, airspy_id_table);

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver airspy_driver = अणु
	.name                     = KBUILD_MODNAME,
	.probe                    = airspy_probe,
	.disconnect               = airspy_disconnect,
	.id_table                 = airspy_id_table,
पूर्ण;

module_usb_driver(airspy_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("AirSpy SDR");
MODULE_LICENSE("GPL");
