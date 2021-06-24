<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Realtek RTL2832U SDR driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 *
 * GNU Radio plugin "gr-kernel" क्रम device usage will be on:
 * https://git.linuxtv.org/anttip/gr-kernel.git
 */

#समावेश "rtl2832_sdr.h"
#समावेश "dvb_usb.h"

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/math64.h>
#समावेश <linux/regmap.h>

अटल bool rtl2832_sdr_emulated_fmt;
module_param_named(emulated_क्रमmats, rtl2832_sdr_emulated_fmt, bool, 0644);
MODULE_PARM_DESC(emulated_क्रमmats, "enable emulated formats (disappears in future)");

/* Original macro करोes not contain enough null poपूर्णांकer checks क्रम our need */
#घोषणा V4L2_SUBDEV_HAS_OP(sd, o, f) \
	((sd) && (sd)->ops && (sd)->ops->o && (sd)->ops->o->f)

#घोषणा MAX_BULK_BUFS            (10)
#घोषणा BULK_BUFFER_SIZE         (128 * 512)

अटल स्थिर काष्ठा v4l2_frequency_band bands_adc[] = अणु
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  300000,
		.rangehigh  =  300000,
	पूर्ण,
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 1,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  900001,
		.rangehigh  = 2800000,
	पूर्ण,
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 2,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = 3200000,
		.rangehigh  = 3200000,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands_fm[] = अणु
	अणु
		.tuner = 1,
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =    50000000,
		.rangehigh  =  2000000000,
	पूर्ण,
पूर्ण;

/* stream क्रमmats */
काष्ठा rtl2832_sdr_क्रमmat अणु
	अक्षर	*name;
	u32	pixelक्रमmat;
	u32	buffersize;
पूर्ण;

अटल काष्ठा rtl2832_sdr_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CU8,
		.buffersize	= BULK_BUFFER_SIZE,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CU16LE,
		.buffersize	= BULK_BUFFER_SIZE * 2,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक NUM_FORMATS = ARRAY_SIZE(क्रमmats);

/* पूर्णांकermediate buffers with raw data from the USB device */
काष्ठा rtl2832_sdr_frame_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा rtl2832_sdr_dev अणु
#घोषणा POWER_ON           0  /* BIT(0) */
#घोषणा URB_BUF            1  /* BIT(1) */
	अचिन्हित दीर्घ flags;

	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;

	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_subdev *v4l2_subdev;

	/* videobuf2 queue and queued buffers list */
	काष्ठा vb2_queue vb_queue;
	काष्ठा list_head queued_bufs;
	spinlock_t queued_bufs_lock; /* Protects queued_bufs */
	अचिन्हित sequence;	     /* buffer sequence counter */

	/* Note अगर taking both locks v4l2_lock must always be locked first! */
	काष्ठा mutex v4l2_lock;      /* Protects everything अन्यथा */
	काष्ठा mutex vb_queue_lock;  /* Protects vb_queue and capt_file */

	/* Poपूर्णांकer to our usb_device, will be शून्य after unplug */
	काष्ठा usb_device *udev; /* Both mutexes most be hold when setting! */

	अचिन्हित पूर्णांक vb_full; /* vb is full and packets dropped */

	काष्ठा urb     *urb_list[MAX_BULK_BUFS];
	पूर्णांक            buf_num;
	अचिन्हित दीर्घ  buf_size;
	u8             *buf_list[MAX_BULK_BUFS];
	dma_addr_t     dma_addr[MAX_BULK_BUFS];
	पूर्णांक urbs_initialized;
	पूर्णांक urbs_submitted;

	अचिन्हित पूर्णांक f_adc, f_tuner;
	u32 pixelक्रमmat;
	u32 buffersize;
	अचिन्हित पूर्णांक num_क्रमmats;

	/* Controls */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *bandwidth_स्वतः;
	काष्ठा v4l2_ctrl *bandwidth;

	/* क्रम sample rate calc */
	अचिन्हित पूर्णांक sample;
	अचिन्हित पूर्णांक sample_measured;
	अचिन्हित दीर्घ jअगरfies_next;
पूर्ण;

/* Private functions */
अटल काष्ठा rtl2832_sdr_frame_buf *rtl2832_sdr_get_next_fill_buf(
		काष्ठा rtl2832_sdr_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rtl2832_sdr_frame_buf *buf = शून्य;

	spin_lock_irqsave(&dev->queued_bufs_lock, flags);
	अगर (list_empty(&dev->queued_bufs))
		जाओ leave;

	buf = list_entry(dev->queued_bufs.next,
			काष्ठा rtl2832_sdr_frame_buf, list);
	list_del(&buf->list);
leave:
	spin_unlock_irqrestore(&dev->queued_bufs_lock, flags);
	वापस buf;
पूर्ण

अटल अचिन्हित पूर्णांक rtl2832_sdr_convert_stream(काष्ठा rtl2832_sdr_dev *dev,
		व्योम *dst, स्थिर u8 *src, अचिन्हित पूर्णांक src_len)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	अचिन्हित पूर्णांक dst_len;

	अगर (dev->pixelक्रमmat ==  V4L2_SDR_FMT_CU8) अणु
		/* native stream, no need to convert */
		स_नकल(dst, src, src_len);
		dst_len = src_len;
	पूर्ण अन्यथा अगर (dev->pixelक्रमmat == V4L2_SDR_FMT_CU16LE) अणु
		/* convert u8 to u16 */
		अचिन्हित पूर्णांक i;
		u16 *u16dst = dst;

		क्रम (i = 0; i < src_len; i++)
			*u16dst++ = (src[i] << 8) | (src[i] >> 0);
		dst_len = 2 * src_len;
	पूर्ण अन्यथा अणु
		dst_len = 0;
	पूर्ण

	/* calculate sample rate and output it in 10 seconds पूर्णांकervals */
	अगर (unlikely(समय_is_beक्रमe_jअगरfies(dev->jअगरfies_next))) अणु
		#घोषणा MSECS 10000UL
		अचिन्हित पूर्णांक msecs = jअगरfies_to_msecs(jअगरfies -
				dev->jअगरfies_next + msecs_to_jअगरfies(MSECS));
		अचिन्हित पूर्णांक samples = dev->sample - dev->sample_measured;

		dev->jअगरfies_next = jअगरfies + msecs_to_jअगरfies(MSECS);
		dev->sample_measured = dev->sample;
		dev_dbg(&pdev->dev,
			"slen=%u samples=%u msecs=%u sample rate=%lu\n",
			src_len, samples, msecs, samples * 1000UL / msecs);
	पूर्ण

	/* total number of I+Q pairs */
	dev->sample += src_len / 2;

	वापस dst_len;
पूर्ण

/*
 * This माला_लो called क्रम the bulk stream pipe. This is करोne in पूर्णांकerrupt
 * समय, so it has to be fast, not crash, and not stall. Neat.
 */
अटल व्योम rtl2832_sdr_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा rtl2832_sdr_dev *dev = urb->context;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_frame_buf *fbuf;

	dev_dbg_ratelimited(&pdev->dev, "status=%d length=%d/%d errors=%d\n",
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
		dev_err_ratelimited(&pdev->dev, "urb failed=%d\n", urb->status);
		अवरोध;
	पूर्ण

	अगर (likely(urb->actual_length > 0)) अणु
		व्योम *ptr;
		अचिन्हित पूर्णांक len;
		/* get मुक्त framebuffer */
		fbuf = rtl2832_sdr_get_next_fill_buf(dev);
		अगर (unlikely(fbuf == शून्य)) अणु
			dev->vb_full++;
			dev_notice_ratelimited(&pdev->dev,
					       "videobuf is full, %d packets dropped\n",
					       dev->vb_full);
			जाओ skip;
		पूर्ण

		/* fill framebuffer */
		ptr = vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0);
		len = rtl2832_sdr_convert_stream(dev, ptr, urb->transfer_buffer,
				urb->actual_length);
		vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0, len);
		fbuf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		fbuf->vb.sequence = dev->sequence++;
		vb2_buffer_करोne(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण
skip:
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक rtl2832_sdr_समाप्त_urbs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक i;

	क्रम (i = dev->urbs_submitted - 1; i >= 0; i--) अणु
		dev_dbg(&pdev->dev, "kill urb=%d\n", i);
		/* stop the URB */
		usb_समाप्त_urb(dev->urb_list[i]);
	पूर्ण
	dev->urbs_submitted = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_submit_urbs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < dev->urbs_initialized; i++) अणु
		dev_dbg(&pdev->dev, "submit urb=%d\n", i);
		ret = usb_submit_urb(dev->urb_list[i], GFP_KERNEL);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Could not submit urb no. %d - get them all back\n",
				i);
			rtl2832_sdr_समाप्त_urbs(dev);
			वापस ret;
		पूर्ण
		dev->urbs_submitted++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_मुक्त_stream_bufs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	अगर (test_bit(URB_BUF, &dev->flags)) अणु
		जबतक (dev->buf_num) अणु
			dev->buf_num--;
			dev_dbg(&pdev->dev, "free buf=%d\n", dev->buf_num);
			usb_मुक्त_coherent(dev->udev, dev->buf_size,
					  dev->buf_list[dev->buf_num],
					  dev->dma_addr[dev->buf_num]);
		पूर्ण
	पूर्ण
	clear_bit(URB_BUF, &dev->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_alloc_stream_bufs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev->buf_num = 0;
	dev->buf_size = BULK_BUFFER_SIZE;

	dev_dbg(&pdev->dev, "all in all I will use %u bytes for streaming\n",
		MAX_BULK_BUFS * BULK_BUFFER_SIZE);

	क्रम (dev->buf_num = 0; dev->buf_num < MAX_BULK_BUFS; dev->buf_num++) अणु
		dev->buf_list[dev->buf_num] = usb_alloc_coherent(dev->udev,
				BULK_BUFFER_SIZE, GFP_KERNEL,
				&dev->dma_addr[dev->buf_num]);
		अगर (!dev->buf_list[dev->buf_num]) अणु
			dev_dbg(&pdev->dev, "alloc buf=%d failed\n",
				dev->buf_num);
			rtl2832_sdr_मुक्त_stream_bufs(dev);
			वापस -ENOMEM;
		पूर्ण

		dev_dbg(&pdev->dev, "alloc buf=%d %p (dma %llu)\n",
			dev->buf_num, dev->buf_list[dev->buf_num],
			(दीर्घ दीर्घ)dev->dma_addr[dev->buf_num]);
		set_bit(URB_BUF, &dev->flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_मुक्त_urbs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक i;

	rtl2832_sdr_समाप्त_urbs(dev);

	क्रम (i = dev->urbs_initialized - 1; i >= 0; i--) अणु
		अगर (dev->urb_list[i]) अणु
			dev_dbg(&pdev->dev, "free urb=%d\n", i);
			/* मुक्त the URBs */
			usb_मुक्त_urb(dev->urb_list[i]);
		पूर्ण
	पूर्ण
	dev->urbs_initialized = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_alloc_urbs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक i, j;

	/* allocate the URBs */
	क्रम (i = 0; i < MAX_BULK_BUFS; i++) अणु
		dev_dbg(&pdev->dev, "alloc urb=%d\n", i);
		dev->urb_list[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!dev->urb_list[i]) अणु
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(dev->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण
		usb_fill_bulk_urb(dev->urb_list[i],
				dev->udev,
				usb_rcvbulkpipe(dev->udev, 0x81),
				dev->buf_list[i],
				BULK_BUFFER_SIZE,
				rtl2832_sdr_urb_complete, dev);

		dev->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		dev->urb_list[i]->transfer_dma = dev->dma_addr[i];
		dev->urbs_initialized++;
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called with vb_queue_lock hold */
अटल व्योम rtl2832_sdr_cleanup_queued_bufs(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	अचिन्हित दीर्घ flags;

	dev_dbg(&pdev->dev, "\n");

	spin_lock_irqsave(&dev->queued_bufs_lock, flags);
	जबतक (!list_empty(&dev->queued_bufs)) अणु
		काष्ठा rtl2832_sdr_frame_buf *buf;

		buf = list_entry(dev->queued_bufs.next,
				काष्ठा rtl2832_sdr_frame_buf, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->queued_bufs_lock, flags);
पूर्ण

अटल पूर्णांक rtl2832_sdr_querycap(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_capability *cap)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, dev->vdev.name, माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

/* Videobuf2 operations */
अटल पूर्णांक rtl2832_sdr_queue_setup(काष्ठा vb2_queue *vq,
		अचिन्हित पूर्णांक *nbuffers,
		अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "nbuffers=%d\n", *nbuffers);

	/* Need at least 8 buffers */
	अगर (vq->num_buffers + *nbuffers < 8)
		*nbuffers = 8 - vq->num_buffers;
	*nplanes = 1;
	sizes[0] = PAGE_ALIGN(dev->buffersize);
	dev_dbg(&pdev->dev, "nbuffers=%d sizes[0]=%d\n", *nbuffers, sizes[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rtl2832_sdr_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	/* Don't allow queueing new buffers after device disconnection */
	अगर (!dev->udev)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम rtl2832_sdr_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rtl2832_sdr_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा rtl2832_sdr_frame_buf *buf =
			container_of(vbuf, काष्ठा rtl2832_sdr_frame_buf, vb);
	अचिन्हित दीर्घ flags;

	/* Check the device has not disconnected between prep and queuing */
	अगर (!dev->udev) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&dev->queued_bufs_lock, flags);
	list_add_tail(&buf->list, &dev->queued_bufs);
	spin_unlock_irqrestore(&dev->queued_bufs_lock, flags);
पूर्ण

अटल पूर्णांक rtl2832_sdr_set_adc(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;
	पूर्णांक ret;
	अचिन्हित पूर्णांक f_sr, f_अगर;
	u8 buf[4], u8पंचांगp1, u8पंचांगp2;
	u64 u64पंचांगp;
	u32 u32पंचांगp;

	dev_dbg(&pdev->dev, "f_adc=%u\n", dev->f_adc);

	अगर (!test_bit(POWER_ON, &dev->flags))
		वापस 0;

	अगर (dev->f_adc == 0)
		वापस 0;

	f_sr = dev->f_adc;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x13e, "\x00\x00", 2);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x115, "\x00\x00\x00\x00", 4);
	अगर (ret)
		जाओ err;

	/* get IF from tuner */
	अगर (fe->ops.tuner_ops.get_अगर_frequency)
		ret = fe->ops.tuner_ops.get_अगर_frequency(fe, &f_अगर);
	अन्यथा
		ret = -EINVAL;

	अगर (ret)
		जाओ err;

	/* program IF */
	u64पंचांगp = f_अगर % pdata->clk;
	u64पंचांगp *= 0x400000;
	u64पंचांगp = भाग_u64(u64पंचांगp, pdata->clk);
	u64पंचांगp = -u64पंचांगp;
	u32पंचांगp = u64पंचांगp & 0x3fffff;

	dev_dbg(&pdev->dev, "f_if=%u if_ctl=%08x\n", f_अगर, u32पंचांगp);

	buf[0] = (u32पंचांगp >> 16) & 0xff;
	buf[1] = (u32पंचांगp >>  8) & 0xff;
	buf[2] = (u32पंचांगp >>  0) & 0xff;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x119, buf, 3);
	अगर (ret)
		जाओ err;

	/* BB / IF mode */
	/* POR: 0x1b1=0x1f, 0x008=0x0d, 0x006=0x80 */
	अगर (f_अगर) अणु
		u8पंचांगp1 = 0x1a; /* disable Zero-IF */
		u8पंचांगp2 = 0x8d; /* enable ADC I */
	पूर्ण अन्यथा अणु
		u8पंचांगp1 = 0x1b; /* enable Zero-IF, DC, IQ */
		u8पंचांगp2 = 0xcd; /* enable ADC I, ADC Q */
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x1b1, u8पंचांगp1);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x008, u8पंचांगp2);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x006, 0x80);
	अगर (ret)
		जाओ err;

	/* program sampling rate (resampling करोwn) */
	u32पंचांगp = भाग_u64(pdata->clk * 0x400000ULL, f_sr * 4U);
	u32पंचांगp <<= 2;
	buf[0] = (u32पंचांगp >> 24) & 0xff;
	buf[1] = (u32पंचांगp >> 16) & 0xff;
	buf[2] = (u32पंचांगp >>  8) & 0xff;
	buf[3] = (u32पंचांगp >>  0) & 0xff;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x19f, buf, 4);
	अगर (ret)
		जाओ err;

	/* low-pass filter */
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x11c,
				"\xca\xdc\xd7\xd8\xe0\xf2\x0e\x35\x06\x50\x9c\x0d\x71\x11\x14\x71\x74\x19\x41\xa5",
				20);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x017, "\x11\x10", 2);
	अगर (ret)
		जाओ err;

	/* mode */
	ret = regmap_ग_लिखो(dev->regmap, 0x019, 0x05);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x01a,
				"\x1b\x16\x0d\x06\x01\xff", 6);
	अगर (ret)
		जाओ err;

	/* FSM */
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x192, "\x00\xf0\x0f", 3);
	अगर (ret)
		जाओ err;

	/* PID filter */
	ret = regmap_ग_लिखो(dev->regmap, 0x061, 0x60);
	अगर (ret)
		जाओ err;

	/* used RF tuner based settings */
	चयन (pdata->tuner) अणु
	हाल RTL2832_SDR_TUNER_E4000:
		ret = regmap_ग_लिखो(dev->regmap, 0x112, 0x5a);
		ret = regmap_ग_लिखो(dev->regmap, 0x102, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x103, 0x5a);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c7, 0x30);
		ret = regmap_ग_लिखो(dev->regmap, 0x104, 0xd0);
		ret = regmap_ग_लिखो(dev->regmap, 0x105, 0xbe);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c8, 0x18);
		ret = regmap_ग_लिखो(dev->regmap, 0x106, 0x35);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c9, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ca, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cb, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x107, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cd, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ce, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x108, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x109, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x10a, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x10b, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_ग_लिखो(dev->regmap, 0x011, 0xd4);
		ret = regmap_ग_लिखो(dev->regmap, 0x1e5, 0xf0);
		ret = regmap_ग_लिखो(dev->regmap, 0x1d9, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x1db, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x1dd, 0x14);
		ret = regmap_ग_लिखो(dev->regmap, 0x1de, 0xec);
		ret = regmap_ग_लिखो(dev->regmap, 0x1d8, 0x0c);
		ret = regmap_ग_लिखो(dev->regmap, 0x1e6, 0x02);
		ret = regmap_ग_लिखो(dev->regmap, 0x1d7, 0x09);
		ret = regmap_ग_लिखो(dev->regmap, 0x00d, 0x83);
		ret = regmap_ग_लिखो(dev->regmap, 0x010, 0x49);
		ret = regmap_ग_लिखो(dev->regmap, 0x00d, 0x87);
		ret = regmap_ग_लिखो(dev->regmap, 0x00d, 0x85);
		ret = regmap_ग_लिखो(dev->regmap, 0x013, 0x02);
		अवरोध;
	हाल RTL2832_SDR_TUNER_FC0012:
	हाल RTL2832_SDR_TUNER_FC0013:
		ret = regmap_ग_लिखो(dev->regmap, 0x112, 0x5a);
		ret = regmap_ग_लिखो(dev->regmap, 0x102, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x103, 0x5a);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c7, 0x2c);
		ret = regmap_ग_लिखो(dev->regmap, 0x104, 0xcc);
		ret = regmap_ग_लिखो(dev->regmap, 0x105, 0xbe);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c8, 0x16);
		ret = regmap_ग_लिखो(dev->regmap, 0x106, 0x35);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c9, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ca, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cb, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x107, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cd, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ce, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x108, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x109, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x10a, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x10b, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x011, "\xe9\xbf", 2);
		ret = regmap_ग_लिखो(dev->regmap, 0x1e5, 0xf0);
		ret = regmap_ग_लिखो(dev->regmap, 0x1d9, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x1db, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x1dd, 0x11);
		ret = regmap_ग_लिखो(dev->regmap, 0x1de, 0xef);
		ret = regmap_ग_लिखो(dev->regmap, 0x1d8, 0x0c);
		ret = regmap_ग_लिखो(dev->regmap, 0x1e6, 0x02);
		ret = regmap_ग_लिखो(dev->regmap, 0x1d7, 0x09);
		अवरोध;
	हाल RTL2832_SDR_TUNER_R820T:
	हाल RTL2832_SDR_TUNER_R828D:
		ret = regmap_ग_लिखो(dev->regmap, 0x112, 0x5a);
		ret = regmap_ग_लिखो(dev->regmap, 0x102, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x115, 0x01);
		ret = regmap_ग_लिखो(dev->regmap, 0x103, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c7, 0x24);
		ret = regmap_ग_लिखो(dev->regmap, 0x104, 0xcc);
		ret = regmap_ग_लिखो(dev->regmap, 0x105, 0xbe);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c8, 0x14);
		ret = regmap_ग_लिखो(dev->regmap, 0x106, 0x35);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c9, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ca, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cb, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x107, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cd, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ce, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x108, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x109, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x10a, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x10b, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_ग_लिखो(dev->regmap, 0x011, 0xf4);
		अवरोध;
	हाल RTL2832_SDR_TUNER_FC2580:
		ret = regmap_ग_लिखो(dev->regmap, 0x112, 0x39);
		ret = regmap_ग_लिखो(dev->regmap, 0x102, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x103, 0x5a);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c7, 0x2c);
		ret = regmap_ग_लिखो(dev->regmap, 0x104, 0xcc);
		ret = regmap_ग_लिखो(dev->regmap, 0x105, 0xbe);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c8, 0x16);
		ret = regmap_ग_लिखो(dev->regmap, 0x106, 0x35);
		ret = regmap_ग_लिखो(dev->regmap, 0x1c9, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ca, 0x21);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cb, 0x00);
		ret = regmap_ग_लिखो(dev->regmap, 0x107, 0x40);
		ret = regmap_ग_लिखो(dev->regmap, 0x1cd, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x1ce, 0x10);
		ret = regmap_ग_लिखो(dev->regmap, 0x108, 0x80);
		ret = regmap_ग_लिखो(dev->regmap, 0x109, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x10a, 0x9c);
		ret = regmap_ग_लिखो(dev->regmap, 0x10b, 0x7f);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_ग_लिखो(dev->regmap, 0x00e, 0xfc);
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x011, "\xe9\xf4", 2);
		अवरोध;
	शेष:
		dev_notice(&pdev->dev, "Unsupported tuner\n");
	पूर्ण

	/* software reset */
	ret = regmap_update_bits(dev->regmap, 0x101, 0x04, 0x04);
	अगर (ret)
		जाओ err;

	ret = regmap_update_bits(dev->regmap, 0x101, 0x04, 0x00);
	अगर (ret)
		जाओ err;
err:
	वापस ret;
पूर्ण;

अटल व्योम rtl2832_sdr_unset_adc(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	/* PID filter */
	ret = regmap_ग_लिखो(dev->regmap, 0x061, 0xe0);
	अगर (ret)
		जाओ err;

	/* mode */
	ret = regmap_ग_लिखो(dev->regmap, 0x019, 0x20);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x017, "\x11\x10", 2);
	अगर (ret)
		जाओ err;

	/* FSM */
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x192, "\x00\x0f\xff", 3);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x13e, "\x40\x00", 2);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x115, "\x06\x3f\xce\xcc", 4);
	अगर (ret)
		जाओ err;
err:
	वापस;
पूर्ण;

अटल पूर्णांक rtl2832_sdr_set_tuner_freq(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा v4l2_ctrl *bandwidth_स्वतः;
	काष्ठा v4l2_ctrl *bandwidth;

	/*
	 * tuner RF (Hz)
	 */
	अगर (dev->f_tuner == 0)
		वापस 0;

	/*
	 * bandwidth (Hz)
	 */
	bandwidth_स्वतः = v4l2_ctrl_find(&dev->hdl,
					V4L2_CID_RF_TUNER_BANDWIDTH_AUTO);
	bandwidth = v4l2_ctrl_find(&dev->hdl, V4L2_CID_RF_TUNER_BANDWIDTH);
	अगर (v4l2_ctrl_g_ctrl(bandwidth_स्वतः)) अणु
		c->bandwidth_hz = dev->f_adc;
		v4l2_ctrl_s_ctrl(bandwidth, dev->f_adc);
	पूर्ण अन्यथा अणु
		c->bandwidth_hz = v4l2_ctrl_g_ctrl(bandwidth);
	पूर्ण

	c->frequency = dev->f_tuner;
	c->delivery_प्रणाली = SYS_DVBT;

	dev_dbg(&pdev->dev, "frequency=%u bandwidth=%d\n",
		c->frequency, c->bandwidth_hz);

	अगर (!test_bit(POWER_ON, &dev->flags))
		वापस 0;

	अगर (!V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, s_frequency)) अणु
		अगर (fe->ops.tuner_ops.set_params)
			fe->ops.tuner_ops.set_params(fe);
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक rtl2832_sdr_set_tuner(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;

	dev_dbg(&pdev->dev, "\n");

	अगर (fe->ops.tuner_ops.init)
		fe->ops.tuner_ops.init(fe);

	वापस 0;
पूर्ण;

अटल व्योम rtl2832_sdr_unset_tuner(काष्ठा rtl2832_sdr_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;

	dev_dbg(&pdev->dev, "\n");

	अगर (fe->ops.tuner_ops.sleep)
		fe->ops.tuner_ops.sleep(fe);

	वापस;
पूर्ण;

अटल पूर्णांक rtl2832_sdr_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_usb_device *d = pdata->dvb_usb_device;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	अगर (!dev->udev)
		वापस -ENODEV;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->v4l2_lock))
		वापस -ERESTARTSYS;

	अगर (d->props->घातer_ctrl)
		d->props->घातer_ctrl(d, 1);

	/* enable ADC */
	अगर (d->props->frontend_ctrl)
		d->props->frontend_ctrl(pdata->dvb_frontend, 1);

	set_bit(POWER_ON, &dev->flags);

	/* wake-up tuner */
	अगर (V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, core, s_घातer))
		ret = v4l2_subdev_call(dev->v4l2_subdev, core, s_घातer, 1);
	अन्यथा
		ret = rtl2832_sdr_set_tuner(dev);
	अगर (ret)
		जाओ err;

	ret = rtl2832_sdr_set_tuner_freq(dev);
	अगर (ret)
		जाओ err;

	ret = rtl2832_sdr_set_adc(dev);
	अगर (ret)
		जाओ err;

	ret = rtl2832_sdr_alloc_stream_bufs(dev);
	अगर (ret)
		जाओ err;

	ret = rtl2832_sdr_alloc_urbs(dev);
	अगर (ret)
		जाओ err;

	dev->sequence = 0;

	ret = rtl2832_sdr_submit_urbs(dev);
	अगर (ret)
		जाओ err;

err:
	mutex_unlock(&dev->v4l2_lock);

	वापस ret;
पूर्ण

अटल व्योम rtl2832_sdr_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_usb_device *d = pdata->dvb_usb_device;

	dev_dbg(&pdev->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	rtl2832_sdr_समाप्त_urbs(dev);
	rtl2832_sdr_मुक्त_urbs(dev);
	rtl2832_sdr_मुक्त_stream_bufs(dev);
	rtl2832_sdr_cleanup_queued_bufs(dev);
	rtl2832_sdr_unset_adc(dev);

	/* sleep tuner */
	अगर (V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, core, s_घातer))
		v4l2_subdev_call(dev->v4l2_subdev, core, s_घातer, 0);
	अन्यथा
		rtl2832_sdr_unset_tuner(dev);

	clear_bit(POWER_ON, &dev->flags);

	/* disable ADC */
	अगर (d->props->frontend_ctrl)
		d->props->frontend_ctrl(pdata->dvb_frontend, 0);

	अगर (d->props->घातer_ctrl)
		d->props->घातer_ctrl(d, 0);

	mutex_unlock(&dev->v4l2_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops rtl2832_sdr_vb2_ops = अणु
	.queue_setup            = rtl2832_sdr_queue_setup,
	.buf_prepare            = rtl2832_sdr_buf_prepare,
	.buf_queue              = rtl2832_sdr_buf_queue,
	.start_streaming        = rtl2832_sdr_start_streaming,
	.stop_streaming         = rtl2832_sdr_stop_streaming,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक rtl2832_sdr_g_tuner(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_tuner *v)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "index=%d type=%d\n", v->index, v->type);

	अगर (v->index == 0) अणु
		strscpy(v->name, "ADC: Realtek RTL2832", माप(v->name));
		v->type = V4L2_TUNER_ADC;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow =   300000;
		v->rangehigh = 3200000;
		ret = 0;
	पूर्ण अन्यथा अगर (v->index == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, g_tuner)) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_tuner, v);
	पूर्ण अन्यथा अगर (v->index == 1) अणु
		strscpy(v->name, "RF: <unknown>", माप(v->name));
		v->type = V4L2_TUNER_RF;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow =    50000000;
		v->rangehigh = 2000000000;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sdr_s_tuner(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	अगर (v->index == 0) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (v->index == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, s_tuner)) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, s_tuner, v);
	पूर्ण अन्यथा अगर (v->index == 1) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sdr_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "tuner=%d type=%d index=%d\n",
		band->tuner, band->type, band->index);

	अगर (band->tuner == 0) अणु
		अगर (band->index >= ARRAY_SIZE(bands_adc))
			वापस -EINVAL;

		*band = bands_adc[band->index];
		ret = 0;
	पूर्ण अन्यथा अगर (band->tuner == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, क्रमागत_freq_bands)) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, क्रमागत_freq_bands, band);
	पूर्ण अन्यथा अगर (band->tuner == 1) अणु
		अगर (band->index >= ARRAY_SIZE(bands_fm))
			वापस -EINVAL;

		*band = bands_fm[band->index];
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sdr_g_frequency(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency *f)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "tuner=%d type=%d\n", f->tuner, f->type);

	अगर (f->tuner == 0) अणु
		f->frequency = dev->f_adc;
		f->type = V4L2_TUNER_ADC;
		ret = 0;
	पूर्ण अन्यथा अगर (f->tuner == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, g_frequency)) अणु
		f->type = V4L2_TUNER_RF;
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_frequency, f);
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		f->frequency = dev->f_tuner;
		f->type = V4L2_TUNER_RF;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sdr_s_frequency(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret, band;

	dev_dbg(&pdev->dev, "tuner=%d type=%d frequency=%u\n",
		f->tuner, f->type, f->frequency);

	/* ADC band midpoपूर्णांकs */
	#घोषणा BAND_ADC_0 ((bands_adc[0].rangehigh + bands_adc[1].rangelow) / 2)
	#घोषणा BAND_ADC_1 ((bands_adc[1].rangehigh + bands_adc[2].rangelow) / 2)

	अगर (f->tuner == 0 && f->type == V4L2_TUNER_ADC) अणु
		अगर (f->frequency < BAND_ADC_0)
			band = 0;
		अन्यथा अगर (f->frequency < BAND_ADC_1)
			band = 1;
		अन्यथा
			band = 2;

		dev->f_adc = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				     bands_adc[band].rangelow,
				     bands_adc[band].rangehigh);

		dev_dbg(&pdev->dev, "ADC frequency=%u Hz\n", dev->f_adc);
		ret = rtl2832_sdr_set_adc(dev);
	पूर्ण अन्यथा अगर (f->tuner == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, s_frequency)) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, s_frequency, f);
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		dev->f_tuner = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				bands_fm[0].rangelow,
				bands_fm[0].rangehigh);
		dev_dbg(&pdev->dev, "RF frequency=%u Hz\n", f->frequency);

		ret = rtl2832_sdr_set_tuner_freq(dev);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sdr_क्रमागत_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	अगर (f->index >= dev->num_क्रमmats)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_g_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	f->fmt.sdr.pixelक्रमmat = dev->pixelक्रमmat;
	f->fmt.sdr.buffersize = dev->buffersize;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_s_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा vb2_queue *q = &dev->vb_queue;
	पूर्णांक i;

	dev_dbg(&pdev->dev, "pixelformat fourcc %4.4s\n",
		(अक्षर *)&f->fmt.sdr.pixelक्रमmat);

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < dev->num_क्रमmats; i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			dev->pixelक्रमmat = क्रमmats[i].pixelक्रमmat;
			dev->buffersize = क्रमmats[i].buffersize;
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	dev->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	dev->buffersize = क्रमmats[0].buffersize;
	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_sdr_try_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rtl2832_sdr_dev *dev = video_drvdata(file);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक i;

	dev_dbg(&pdev->dev, "pixelformat fourcc %4.4s\n",
		(अक्षर *)&f->fmt.sdr.pixelक्रमmat);

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < dev->num_क्रमmats; i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rtl2832_sdr_ioctl_ops = अणु
	.vidioc_querycap          = rtl2832_sdr_querycap,

	.vidioc_क्रमागत_fmt_sdr_cap  = rtl2832_sdr_क्रमागत_fmt_sdr_cap,
	.vidioc_g_fmt_sdr_cap     = rtl2832_sdr_g_fmt_sdr_cap,
	.vidioc_s_fmt_sdr_cap     = rtl2832_sdr_s_fmt_sdr_cap,
	.vidioc_try_fmt_sdr_cap   = rtl2832_sdr_try_fmt_sdr_cap,

	.vidioc_reqbufs           = vb2_ioctl_reqbufs,
	.vidioc_create_bufs       = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf       = vb2_ioctl_prepare_buf,
	.vidioc_querybuf          = vb2_ioctl_querybuf,
	.vidioc_qbuf              = vb2_ioctl_qbuf,
	.vidioc_dqbuf             = vb2_ioctl_dqbuf,

	.vidioc_streamon          = vb2_ioctl_streamon,
	.vidioc_streamoff         = vb2_ioctl_streamoff,

	.vidioc_g_tuner           = rtl2832_sdr_g_tuner,
	.vidioc_s_tuner           = rtl2832_sdr_s_tuner,

	.vidioc_क्रमागत_freq_bands   = rtl2832_sdr_क्रमागत_freq_bands,
	.vidioc_g_frequency       = rtl2832_sdr_g_frequency,
	.vidioc_s_frequency       = rtl2832_sdr_s_frequency,

	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_log_status        = v4l2_ctrl_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations rtl2832_sdr_fops = अणु
	.owner                    = THIS_MODULE,
	.खोलो                     = v4l2_fh_खोलो,
	.release                  = vb2_fop_release,
	.पढ़ो                     = vb2_fop_पढ़ो,
	.poll                     = vb2_fop_poll,
	.mmap                     = vb2_fop_mmap,
	.unlocked_ioctl           = video_ioctl2,
पूर्ण;

अटल काष्ठा video_device rtl2832_sdr_ढाँचा = अणु
	.name                     = "Realtek RTL2832 SDR",
	.release                  = video_device_release_empty,
	.fops                     = &rtl2832_sdr_fops,
	.ioctl_ops                = &rtl2832_sdr_ioctl_ops,
	.device_caps		  = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_STREAMING |
				    V4L2_CAP_READWRITE | V4L2_CAP_TUNER,
पूर्ण;

अटल पूर्णांक rtl2832_sdr_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा rtl2832_sdr_dev *dev =
			container_of(ctrl->handler, काष्ठा rtl2832_sdr_dev,
					hdl);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "id=%d name=%s val=%d min=%lld max=%lld step=%lld\n",
		ctrl->id, ctrl->name, ctrl->val, ctrl->minimum, ctrl->maximum,
		ctrl->step);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
		/* TODO: these controls should be moved to tuner drivers */
		अगर (dev->bandwidth_स्वतः->val) अणु
			/* Round towards the बंदst legal value */
			s32 val = dev->f_adc + भाग_u64(dev->bandwidth->step, 2);
			u32 offset;

			val = clamp_t(s32, val, dev->bandwidth->minimum,
				      dev->bandwidth->maximum);
			offset = val - dev->bandwidth->minimum;
			offset = dev->bandwidth->step *
				भाग_u64(offset, dev->bandwidth->step);
			dev->bandwidth->val = dev->bandwidth->minimum + offset;
		पूर्ण
		c->bandwidth_hz = dev->bandwidth->val;

		अगर (!test_bit(POWER_ON, &dev->flags))
			वापस 0;

		अगर (fe->ops.tuner_ops.set_params)
			ret = fe->ops.tuner_ops.set_params(fe);
		अन्यथा
			ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops rtl2832_sdr_ctrl_ops = अणु
	.s_ctrl = rtl2832_sdr_s_ctrl,
पूर्ण;

अटल व्योम rtl2832_sdr_video_release(काष्ठा v4l2_device *v)
अणु
	काष्ठा rtl2832_sdr_dev *dev =
			container_of(v, काष्ठा rtl2832_sdr_dev, v4l2_dev);
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	v4l2_ctrl_handler_मुक्त(&dev->hdl);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
पूर्ण

/* Platक्रमm driver पूर्णांकerface */
अटल पूर्णांक rtl2832_sdr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtl2832_sdr_dev *dev;
	काष्ठा rtl2832_sdr_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &rtl2832_sdr_ctrl_ops;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Cannot proceed without platform data\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	अगर (!pdev->dev.parent->driver) अणु
		dev_dbg(&pdev->dev, "No parent device\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	/* try to refcount host drv since we are the consumer */
	अगर (!try_module_get(pdev->dev.parent->driver->owner)) अणु
		dev_err(&pdev->dev, "Refcount fail");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_module_put;
	पूर्ण

	/* setup the state */
	subdev = pdata->v4l2_subdev;
	dev->v4l2_subdev = pdata->v4l2_subdev;
	dev->pdev = pdev;
	dev->regmap = pdata->regmap;
	dev->udev = pdata->dvb_usb_device->udev;
	dev->f_adc = bands_adc[0].rangelow;
	dev->f_tuner = bands_fm[0].rangelow;
	dev->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	dev->buffersize = क्रमmats[0].buffersize;
	dev->num_क्रमmats = NUM_FORMATS;
	अगर (!rtl2832_sdr_emulated_fmt)
		dev->num_क्रमmats -= 1;

	mutex_init(&dev->v4l2_lock);
	mutex_init(&dev->vb_queue_lock);
	spin_lock_init(&dev->queued_bufs_lock);
	INIT_LIST_HEAD(&dev->queued_bufs);

	/* Init videobuf2 queue काष्ठाure */
	dev->vb_queue.type = V4L2_BUF_TYPE_SDR_CAPTURE;
	dev->vb_queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	dev->vb_queue.drv_priv = dev;
	dev->vb_queue.buf_काष्ठा_size = माप(काष्ठा rtl2832_sdr_frame_buf);
	dev->vb_queue.ops = &rtl2832_sdr_vb2_ops;
	dev->vb_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	dev->vb_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	ret = vb2_queue_init(&dev->vb_queue);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not initialize vb2 queue\n");
		जाओ err_kमुक्त;
	पूर्ण

	/* Register controls */
	चयन (pdata->tuner) अणु
	हाल RTL2832_SDR_TUNER_E4000:
		v4l2_ctrl_handler_init(&dev->hdl, 9);
		अगर (subdev)
			v4l2_ctrl_add_handler(&dev->hdl, subdev->ctrl_handler,
					      शून्य, true);
		अवरोध;
	हाल RTL2832_SDR_TUNER_R820T:
	हाल RTL2832_SDR_TUNER_R828D:
		v4l2_ctrl_handler_init(&dev->hdl, 2);
		dev->bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->hdl, ops,
							V4L2_CID_RF_TUNER_BANDWIDTH_AUTO,
							0, 1, 1, 1);
		dev->bandwidth = v4l2_ctrl_new_std(&dev->hdl, ops,
						   V4L2_CID_RF_TUNER_BANDWIDTH,
						   0, 8000000, 100000, 0);
		v4l2_ctrl_स्वतः_cluster(2, &dev->bandwidth_स्वतः, 0, false);
		अवरोध;
	हाल RTL2832_SDR_TUNER_FC0012:
	हाल RTL2832_SDR_TUNER_FC0013:
		v4l2_ctrl_handler_init(&dev->hdl, 2);
		dev->bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->hdl, ops,
							V4L2_CID_RF_TUNER_BANDWIDTH_AUTO,
							0, 1, 1, 1);
		dev->bandwidth = v4l2_ctrl_new_std(&dev->hdl, ops,
						   V4L2_CID_RF_TUNER_BANDWIDTH,
						   6000000, 8000000, 1000000,
						   6000000);
		v4l2_ctrl_स्वतः_cluster(2, &dev->bandwidth_स्वतः, 0, false);
		अवरोध;
	हाल RTL2832_SDR_TUNER_FC2580:
		v4l2_ctrl_handler_init(&dev->hdl, 2);
		अगर (subdev)
			v4l2_ctrl_add_handler(&dev->hdl, subdev->ctrl_handler,
					      शून्य, true);
		अवरोध;
	शेष:
		v4l2_ctrl_handler_init(&dev->hdl, 0);
		dev_err(&pdev->dev, "Unsupported tuner\n");
		ret = -ENODEV;
		जाओ err_v4l2_ctrl_handler_मुक्त;
	पूर्ण
	अगर (dev->hdl.error) अणु
		ret = dev->hdl.error;
		dev_err(&pdev->dev, "Could not initialize controls\n");
		जाओ err_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	/* Init video_device काष्ठाure */
	dev->vdev = rtl2832_sdr_ढाँचा;
	dev->vdev.queue = &dev->vb_queue;
	dev->vdev.queue->lock = &dev->vb_queue_lock;
	video_set_drvdata(&dev->vdev, dev);

	/* Register the v4l2_device काष्ठाure */
	dev->v4l2_dev.release = rtl2832_sdr_video_release;
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register v4l2-device %d\n", ret);
		जाओ err_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	dev->v4l2_dev.ctrl_handler = &dev->hdl;
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.lock = &dev->v4l2_lock;
	dev->vdev.vfl_dir = VFL_सूची_RX;

	ret = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_SDR, -1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register as video device %d\n",
			ret);
		जाओ err_v4l2_device_unरेजिस्टर;
	पूर्ण
	dev_info(&pdev->dev, "Registered as %s\n",
		 video_device_node_name(&dev->vdev));
	dev_info(&pdev->dev, "Realtek RTL2832 SDR attached\n");
	dev_notice(&pdev->dev,
		   "SDR API is still slightly experimental and functionality changes may follow\n");
	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;
err_v4l2_device_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_v4l2_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
err_kमुक्त:
	kमुक्त(dev);
err_module_put:
	module_put(pdev->dev.parent->driver->owner);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sdr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtl2832_sdr_dev *dev = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l2_lock);
	/* No need to keep the urbs around after disconnection */
	dev->udev = शून्य;
	v4l2_device_disconnect(&dev->v4l2_dev);
	video_unरेजिस्टर_device(&dev->vdev);
	mutex_unlock(&dev->v4l2_lock);
	mutex_unlock(&dev->vb_queue_lock);
	v4l2_device_put(&dev->v4l2_dev);
	module_put(pdev->dev.parent->driver->owner);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rtl2832_sdr_driver = अणु
	.driver = अणु
		.name   = "rtl2832_sdr",
	पूर्ण,
	.probe          = rtl2832_sdr_probe,
	.हटाओ         = rtl2832_sdr_हटाओ,
पूर्ण;
module_platक्रमm_driver(rtl2832_sdr_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Realtek RTL2832 SDR driver");
MODULE_LICENSE("GPL");
