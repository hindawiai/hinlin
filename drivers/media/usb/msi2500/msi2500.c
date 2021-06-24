<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mirics MSi2500 driver
 * Mirics MSi3101 SDR Dongle driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 *
 * That driver is somehow based of pwc driver:
 *  (C) 1999-2004 Nemosoft Unv.
 *  (C) 2004-2006 Luc Saillard (luc@saillard.org)
 *  (C) 2011 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <linux/usb.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <linux/spi/spi.h>

अटल bool msi2500_emulated_fmt;
module_param_named(emulated_क्रमmats, msi2500_emulated_fmt, bool, 0644);
MODULE_PARM_DESC(emulated_क्रमmats, "enable emulated formats (disappears in future)");

/*
 *   iConfiguration          0
 *     bInterfaceNumber        0
 *     bAlternateSetting       1
 *     bNumEndpoपूर्णांकs           1
 *       bEndpoपूर्णांकAddress     0x81  EP 1 IN
 *       bmAttributes            1
 *         Transfer Type            Isochronous
 *       wMaxPacketSize     0x1400  3x 1024 bytes
 *       bInterval               1
 */
#घोषणा MAX_ISO_BUFS            (8)
#घोषणा ISO_FRAMES_PER_DESC     (8)
#घोषणा ISO_MAX_FRAME_SIZE      (3 * 1024)
#घोषणा ISO_BUFFER_SIZE         (ISO_FRAMES_PER_DESC * ISO_MAX_FRAME_SIZE)
#घोषणा MAX_ISOC_ERRORS         20

/*
 * TODO: These क्रमmats should be moved to V4L2 API. Formats are currently
 * disabled from क्रमmats[] table, not visible to userspace.
 */
 /* चिन्हित 12-bit */
#घोषणा MSI2500_PIX_FMT_SDR_S12         v4l2_fourcc('D', 'S', '1', '2')
/* Mirics MSi2500 क्रमmat 384 */
#घोषणा MSI2500_PIX_FMT_SDR_MSI2500_384 v4l2_fourcc('M', '3', '8', '4')

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  1200000,
		.rangehigh  = 15000000,
	पूर्ण,
पूर्ण;

/* stream क्रमmats */
काष्ठा msi2500_क्रमmat अणु
	u32	pixelक्रमmat;
	u32	buffersize;
पूर्ण;

/* क्रमmat descriptions क्रम capture and preview */
अटल काष्ठा msi2500_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CS8,
		.buffersize	= 3 * 1008,
#अगर 0
	पूर्ण, अणु
		.pixelक्रमmat	= MSI2500_PIX_FMT_SDR_MSI2500_384,
	पूर्ण, अणु
		.pixelक्रमmat	= MSI2500_PIX_FMT_SDR_S12,
#पूर्ण_अगर
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CS14LE,
		.buffersize	= 3 * 1008,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CU8,
		.buffersize	= 3 * 1008,
	पूर्ण, अणु
		.pixelक्रमmat	=  V4L2_SDR_FMT_CU16LE,
		.buffersize	= 3 * 1008,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक NUM_FORMATS = ARRAY_SIZE(क्रमmats);

/* पूर्णांकermediate buffers with raw data from the USB device */
काष्ठा msi2500_frame_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा msi2500_dev अणु
	काष्ठा device *dev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_subdev *v4l2_subdev;
	काष्ठा spi_master *master;

	/* videobuf2 queue and queued buffers list */
	काष्ठा vb2_queue vb_queue;
	काष्ठा list_head queued_bufs;
	spinlock_t queued_bufs_lock; /* Protects queued_bufs */

	/* Note अगर taking both locks v4l2_lock must always be locked first! */
	काष्ठा mutex v4l2_lock;      /* Protects everything अन्यथा */
	काष्ठा mutex vb_queue_lock;  /* Protects vb_queue and capt_file */

	/* Poपूर्णांकer to our usb_device, will be शून्य after unplug */
	काष्ठा usb_device *udev; /* Both mutexes most be hold when setting! */

	अचिन्हित पूर्णांक f_adc;
	u32 pixelक्रमmat;
	u32 buffersize;
	अचिन्हित पूर्णांक num_क्रमmats;

	अचिन्हित पूर्णांक isoc_errors; /* number of contiguous ISOC errors */
	अचिन्हित पूर्णांक vb_full; /* vb is full and packets dropped */

	काष्ठा urb *urbs[MAX_ISO_BUFS];

	/* Controls */
	काष्ठा v4l2_ctrl_handler hdl;

	u32 next_sample; /* क्रम track lost packets */
	u32 sample; /* क्रम sample rate calc */
	अचिन्हित दीर्घ jअगरfies_next;
पूर्ण;

/* Private functions */
अटल काष्ठा msi2500_frame_buf *msi2500_get_next_fill_buf(
							काष्ठा msi2500_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा msi2500_frame_buf *buf = शून्य;

	spin_lock_irqsave(&dev->queued_bufs_lock, flags);
	अगर (list_empty(&dev->queued_bufs))
		जाओ leave;

	buf = list_entry(dev->queued_bufs.next, काष्ठा msi2500_frame_buf, list);
	list_del(&buf->list);
leave:
	spin_unlock_irqrestore(&dev->queued_bufs_lock, flags);
	वापस buf;
पूर्ण

/*
 * +===========================================================================
 * |   00-1023 | USB packet type '504'
 * +===========================================================================
 * |   00-  03 | sequence number of first sample in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | garbage
 * +---------------------------------------------------------------------------
 * |   16-1023 | samples
 * +---------------------------------------------------------------------------
 * चिन्हित 8-bit sample
 * 504 * 2 = 1008 samples
 *
 *
 * +===========================================================================
 * |   00-1023 | USB packet type '384'
 * +===========================================================================
 * |   00-  03 | sequence number of first sample in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | garbage
 * +---------------------------------------------------------------------------
 * |   16- 175 | samples
 * +---------------------------------------------------------------------------
 * |  176- 179 | control bits क्रम previous samples
 * +---------------------------------------------------------------------------
 * |  180- 339 | samples
 * +---------------------------------------------------------------------------
 * |  340- 343 | control bits क्रम previous samples
 * +---------------------------------------------------------------------------
 * |  344- 503 | samples
 * +---------------------------------------------------------------------------
 * |  504- 507 | control bits क्रम previous samples
 * +---------------------------------------------------------------------------
 * |  508- 667 | samples
 * +---------------------------------------------------------------------------
 * |  668- 671 | control bits क्रम previous samples
 * +---------------------------------------------------------------------------
 * |  672- 831 | samples
 * +---------------------------------------------------------------------------
 * |  832- 835 | control bits क्रम previous samples
 * +---------------------------------------------------------------------------
 * |  836- 995 | samples
 * +---------------------------------------------------------------------------
 * |  996- 999 | control bits क्रम previous samples
 * +---------------------------------------------------------------------------
 * | 1000-1023 | garbage
 * +---------------------------------------------------------------------------
 *
 * Bytes 4 - 7 could have some meaning?
 *
 * Control bits क्रम previous samples is 32-bit field, containing 16 x 2-bit
 * numbers. This results one 2-bit number क्रम 8 samples. It is likely used क्रम
 * क्रम bit shअगरting sample by given bits, increasing actual sampling resolution.
 * Number 2 (0b10) was never seen.
 *
 * 6 * 16 * 2 * 4 = 768 samples. 768 * 4 = 3072 bytes
 *
 *
 * +===========================================================================
 * |   00-1023 | USB packet type '336'
 * +===========================================================================
 * |   00-  03 | sequence number of first sample in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | garbage
 * +---------------------------------------------------------------------------
 * |   16-1023 | samples
 * +---------------------------------------------------------------------------
 * चिन्हित 12-bit sample
 *
 *
 * +===========================================================================
 * |   00-1023 | USB packet type '252'
 * +===========================================================================
 * |   00-  03 | sequence number of first sample in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | garbage
 * +---------------------------------------------------------------------------
 * |   16-1023 | samples
 * +---------------------------------------------------------------------------
 * चिन्हित 14-bit sample
 */

अटल पूर्णांक msi2500_convert_stream(काष्ठा msi2500_dev *dev, u8 *dst, u8 *src,
				  अचिन्हित पूर्णांक src_len)
अणु
	अचिन्हित पूर्णांक i, j, transactions, dst_len = 0;
	u32 sample[3];

	/* There could be 1-3 1024 byte transactions per packet */
	transactions = src_len / 1024;

	क्रम (i = 0; i < transactions; i++) अणु
		sample[i] = src[3] << 24 | src[2] << 16 | src[1] << 8 |
				src[0] << 0;
		अगर (i == 0 && dev->next_sample != sample[0]) अणु
			dev_dbg_ratelimited(dev->dev,
					    "%d samples lost, %d %08x:%08x\n",
					    sample[0] - dev->next_sample,
					    src_len, dev->next_sample,
					    sample[0]);
		पूर्ण

		/*
		 * Dump all unknown 'garbage' data - maybe we will discover
		 * someday अगर there is something rational...
		 */
		dev_dbg_ratelimited(dev->dev, "%*ph\n", 12, &src[4]);

		src += 16; /* skip header */

		चयन (dev->pixelक्रमmat) अणु
		हाल V4L2_SDR_FMT_CU8: /* 504 x IQ samples */
		अणु
			s8 *s8src = (s8 *)src;
			u8 *u8dst = (u8 *)dst;

			क्रम (j = 0; j < 1008; j++)
				*u8dst++ = *s8src++ + 128;

			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 504;
			अवरोध;
		पूर्ण
		हाल  V4L2_SDR_FMT_CU16LE: /* 252 x IQ samples */
		अणु
			s16 *s16src = (s16 *)src;
			u16 *u16dst = (u16 *)dst;
			काष्ठा अणुचिन्हित पूर्णांक x:14; पूर्ण se; /* sign extension */
			अचिन्हित पूर्णांक uपंचांगp;

			क्रम (j = 0; j < 1008; j += 2) अणु
				/* sign extension from 14-bit to चिन्हित पूर्णांक */
				se.x = *s16src++;
				/* from चिन्हित पूर्णांक to अचिन्हित पूर्णांक */
				uपंचांगp = se.x + 8192;
				/* from 14-bit to 16-bit */
				*u16dst++ = uपंचांगp << 2 | uपंचांगp >> 12;
			पूर्ण

			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 252;
			अवरोध;
		पूर्ण
		हाल MSI2500_PIX_FMT_SDR_MSI2500_384: /* 384 x IQ samples */
			/* Dump unknown 'garbage' data */
			dev_dbg_ratelimited(dev->dev, "%*ph\n", 24, &src[1000]);
			स_नकल(dst, src, 984);
			src += 984 + 24;
			dst += 984;
			dst_len += 984;
			dev->next_sample = sample[i] + 384;
			अवरोध;
		हाल V4L2_SDR_FMT_CS8:         /* 504 x IQ samples */
			स_नकल(dst, src, 1008);
			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 504;
			अवरोध;
		हाल MSI2500_PIX_FMT_SDR_S12:  /* 336 x IQ samples */
			स_नकल(dst, src, 1008);
			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 336;
			अवरोध;
		हाल V4L2_SDR_FMT_CS14LE:      /* 252 x IQ samples */
			स_नकल(dst, src, 1008);
			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 252;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* calculate sample rate and output it in 10 seconds पूर्णांकervals */
	अगर (unlikely(समय_is_beक्रमe_jअगरfies(dev->jअगरfies_next))) अणु
		#घोषणा MSECS 10000UL
		अचिन्हित पूर्णांक msecs = jअगरfies_to_msecs(jअगरfies -
				dev->jअगरfies_next + msecs_to_jअगरfies(MSECS));
		अचिन्हित पूर्णांक samples = dev->next_sample - dev->sample;

		dev->jअगरfies_next = jअगरfies + msecs_to_jअगरfies(MSECS);
		dev->sample = dev->next_sample;
		dev_dbg(dev->dev, "size=%u samples=%u msecs=%u sample rate=%lu\n",
			src_len, samples, msecs,
			samples * 1000UL / msecs);
	पूर्ण

	वापस dst_len;
पूर्ण

/*
 * This माला_लो called क्रम the Isochronous pipe (stream). This is करोne in पूर्णांकerrupt
 * समय, so it has to be fast, not crash, and not stall. Neat.
 */
अटल व्योम msi2500_isoc_handler(काष्ठा urb *urb)
अणु
	काष्ठा msi2500_dev *dev = (काष्ठा msi2500_dev *)urb->context;
	पूर्णांक i, flen, ख_स्थितिus;
	अचिन्हित अक्षर *iso_buf = शून्य;
	काष्ठा msi2500_frame_buf *fbuf;

	अगर (unlikely(urb->status == -ENOENT ||
		     urb->status == -ECONNRESET ||
		     urb->status == -ESHUTDOWN)) अणु
		dev_dbg(dev->dev, "URB (%p) unlinked %ssynchronously\n",
			urb, urb->status == -ENOENT ? "" : "a");
		वापस;
	पूर्ण

	अगर (unlikely(urb->status != 0)) अणु
		dev_dbg(dev->dev, "called with status %d\n", urb->status);
		/* Give up after a number of contiguous errors */
		अगर (++dev->isoc_errors > MAX_ISOC_ERRORS)
			dev_dbg(dev->dev, "Too many ISOC errors, bailing out\n");
		जाओ handler_end;
	पूर्ण अन्यथा अणु
		/* Reset ISOC error counter. We did get here, after all. */
		dev->isoc_errors = 0;
	पूर्ण

	/* Compact data */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		व्योम *ptr;

		/* Check frame error */
		ख_स्थितिus = urb->iso_frame_desc[i].status;
		अगर (unlikely(ख_स्थितिus)) अणु
			dev_dbg_ratelimited(dev->dev,
					    "frame=%d/%d has error %d skipping\n",
					    i, urb->number_of_packets, ख_स्थितिus);
			जारी;
		पूर्ण

		/* Check अगर that frame contains data */
		flen = urb->iso_frame_desc[i].actual_length;
		अगर (unlikely(flen == 0))
			जारी;

		iso_buf = urb->transfer_buffer + urb->iso_frame_desc[i].offset;

		/* Get मुक्त framebuffer */
		fbuf = msi2500_get_next_fill_buf(dev);
		अगर (unlikely(fbuf == शून्य)) अणु
			dev->vb_full++;
			dev_dbg_ratelimited(dev->dev,
					    "videobuf is full, %d packets dropped\n",
					    dev->vb_full);
			जारी;
		पूर्ण

		/* fill framebuffer */
		ptr = vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0);
		flen = msi2500_convert_stream(dev, ptr, iso_buf, flen);
		vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0, flen);
		vb2_buffer_करोne(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण

handler_end:
	i = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(i != 0))
		dev_dbg(dev->dev, "Error (%d) re-submitting urb\n", i);
पूर्ण

अटल व्योम msi2500_iso_stop(काष्ठा msi2500_dev *dev)
अणु
	पूर्णांक i;

	dev_dbg(dev->dev, "\n");

	/* Unlinking ISOC buffers one by one */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		अगर (dev->urbs[i]) अणु
			dev_dbg(dev->dev, "Unlinking URB %p\n", dev->urbs[i]);
			usb_समाप्त_urb(dev->urbs[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम msi2500_iso_मुक्त(काष्ठा msi2500_dev *dev)
अणु
	पूर्णांक i;

	dev_dbg(dev->dev, "\n");

	/* Freeing ISOC buffers one by one */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		अगर (dev->urbs[i]) अणु
			dev_dbg(dev->dev, "Freeing URB\n");
			अगर (dev->urbs[i]->transfer_buffer) अणु
				usb_मुक्त_coherent(dev->udev,
					dev->urbs[i]->transfer_buffer_length,
					dev->urbs[i]->transfer_buffer,
					dev->urbs[i]->transfer_dma);
			पूर्ण
			usb_मुक्त_urb(dev->urbs[i]);
			dev->urbs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Both v4l2_lock and vb_queue_lock should be locked when calling this */
अटल व्योम msi2500_isoc_cleanup(काष्ठा msi2500_dev *dev)
अणु
	dev_dbg(dev->dev, "\n");

	msi2500_iso_stop(dev);
	msi2500_iso_मुक्त(dev);
पूर्ण

/* Both v4l2_lock and vb_queue_lock should be locked when calling this */
अटल पूर्णांक msi2500_isoc_init(काष्ठा msi2500_dev *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i, j, ret;

	dev_dbg(dev->dev, "\n");

	dev->isoc_errors = 0;

	ret = usb_set_पूर्णांकerface(dev->udev, 0, 1);
	अगर (ret)
		वापस ret;

	/* Allocate and init Isochronuous urbs */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
		अगर (urb == शून्य) अणु
			msi2500_isoc_cleanup(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->urbs[i] = urb;
		dev_dbg(dev->dev, "Allocated URB at 0x%p\n", urb);

		urb->पूर्णांकerval = 1;
		urb->dev = dev->udev;
		urb->pipe = usb_rcvisocpipe(dev->udev, 0x81);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_buffer = usb_alloc_coherent(dev->udev,
				ISO_BUFFER_SIZE,
				GFP_KERNEL, &urb->transfer_dma);
		अगर (urb->transfer_buffer == शून्य) अणु
			dev_err(dev->dev,
				"Failed to allocate urb buffer %d\n", i);
			msi2500_isoc_cleanup(dev);
			वापस -ENOMEM;
		पूर्ण
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->complete = msi2500_isoc_handler;
		urb->context = dev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;
		क्रम (j = 0; j < ISO_FRAMES_PER_DESC; j++) अणु
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = ISO_MAX_FRAME_SIZE;
		पूर्ण
	पूर्ण

	/* link */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		ret = usb_submit_urb(dev->urbs[i], GFP_KERNEL);
		अगर (ret) अणु
			dev_err(dev->dev,
				"usb_submit_urb %d failed with error %d\n",
				i, ret);
			msi2500_isoc_cleanup(dev);
			वापस ret;
		पूर्ण
		dev_dbg(dev->dev, "URB 0x%p submitted.\n", dev->urbs[i]);
	पूर्ण

	/* All is करोne... */
	वापस 0;
पूर्ण

/* Must be called with vb_queue_lock hold */
अटल व्योम msi2500_cleanup_queued_bufs(काष्ठा msi2500_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(dev->dev, "\n");

	spin_lock_irqsave(&dev->queued_bufs_lock, flags);
	जबतक (!list_empty(&dev->queued_bufs)) अणु
		काष्ठा msi2500_frame_buf *buf;

		buf = list_entry(dev->queued_bufs.next,
				 काष्ठा msi2500_frame_buf, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->queued_bufs_lock, flags);
पूर्ण

/* The user yanked out the cable... */
अटल व्योम msi2500_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा v4l2_device *v = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा msi2500_dev *dev =
			container_of(v, काष्ठा msi2500_dev, v4l2_dev);

	dev_dbg(dev->dev, "\n");

	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l2_lock);
	/* No need to keep the urbs around after disconnection */
	dev->udev = शून्य;
	v4l2_device_disconnect(&dev->v4l2_dev);
	video_unरेजिस्टर_device(&dev->vdev);
	spi_unरेजिस्टर_master(dev->master);
	mutex_unlock(&dev->v4l2_lock);
	mutex_unlock(&dev->vb_queue_lock);

	v4l2_device_put(&dev->v4l2_dev);
पूर्ण

अटल पूर्णांक msi2500_querycap(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_capability *cap)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "\n");

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, dev->vdev.name, माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

/* Videobuf2 operations */
अटल पूर्णांक msi2500_queue_setup(काष्ठा vb2_queue *vq,
			       अचिन्हित पूर्णांक *nbuffers,
			       अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			       काष्ठा device *alloc_devs[])
अणु
	काष्ठा msi2500_dev *dev = vb2_get_drv_priv(vq);

	dev_dbg(dev->dev, "nbuffers=%d\n", *nbuffers);

	/* Absolute min and max number of buffers available क्रम mmap() */
	*nbuffers = clamp_t(अचिन्हित पूर्णांक, *nbuffers, 8, 32);
	*nplanes = 1;
	sizes[0] = PAGE_ALIGN(dev->buffersize);
	dev_dbg(dev->dev, "nbuffers=%d sizes[0]=%d\n", *nbuffers, sizes[0]);
	वापस 0;
पूर्ण

अटल व्योम msi2500_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा msi2500_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा msi2500_frame_buf *buf = container_of(vbuf,
						     काष्ठा msi2500_frame_buf,
						     vb);
	अचिन्हित दीर्घ flags;

	/* Check the device has not disconnected between prep and queuing */
	अगर (unlikely(!dev->udev)) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&dev->queued_bufs_lock, flags);
	list_add_tail(&buf->list, &dev->queued_bufs);
	spin_unlock_irqrestore(&dev->queued_bufs_lock, flags);
पूर्ण

#घोषणा CMD_WREG               0x41
#घोषणा CMD_START_STREAMING    0x43
#घोषणा CMD_STOP_STREAMING     0x45
#घोषणा CMD_READ_UNKNOWN       0x48

#घोषणा msi2500_dbg_usb_control_msg(_dev, _r, _t, _v, _i, _b, _l) अणु \
	अक्षर *_direction; \
	अगर (_t & USB_सूची_IN) \
		_direction = "<<<"; \
	अन्यथा \
		_direction = ">>>"; \
	dev_dbg(_dev, "%02x %02x %02x %02x %02x %02x %02x %02x %s %*ph\n", \
			_t, _r, _v & 0xff, _v >> 8, _i & 0xff, _i >> 8, \
			_l & 0xff, _l >> 8, _direction, _l, _b); \
पूर्ण

अटल पूर्णांक msi2500_ctrl_msg(काष्ठा msi2500_dev *dev, u8 cmd, u32 data)
अणु
	पूर्णांक ret;
	u8 request = cmd;
	u8 requesttype = USB_सूची_OUT | USB_TYPE_VENDOR;
	u16 value = (data >> 0) & 0xffff;
	u16 index = (data >> 16) & 0xffff;

	msi2500_dbg_usb_control_msg(dev->dev, request, requesttype,
				    value, index, शून्य, 0);
	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0), request,
			      requesttype, value, index, शून्य, 0, 2000);
	अगर (ret)
		dev_err(dev->dev, "failed %d, cmd %02x, data %04x\n",
			ret, cmd, data);

	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_set_usb_adc(काष्ठा msi2500_dev *dev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक f_vco, f_sr, भाग_n, k, k_cw, भाग_out;
	u32 reg3, reg4, reg7;
	काष्ठा v4l2_ctrl *bandwidth_स्वतः;
	काष्ठा v4l2_ctrl *bandwidth;

	f_sr = dev->f_adc;

	/* set tuner, subdev, filters according to sampling rate */
	bandwidth_स्वतः = v4l2_ctrl_find(&dev->hdl,
			V4L2_CID_RF_TUNER_BANDWIDTH_AUTO);
	अगर (v4l2_ctrl_g_ctrl(bandwidth_स्वतः)) अणु
		bandwidth = v4l2_ctrl_find(&dev->hdl,
				V4L2_CID_RF_TUNER_BANDWIDTH);
		v4l2_ctrl_s_ctrl(bandwidth, dev->f_adc);
	पूर्ण

	/* select stream क्रमmat */
	चयन (dev->pixelक्रमmat) अणु
	हाल V4L2_SDR_FMT_CU8:
		reg7 = 0x000c9407; /* 504 */
		अवरोध;
	हाल  V4L2_SDR_FMT_CU16LE:
		reg7 = 0x00009407; /* 252 */
		अवरोध;
	हाल V4L2_SDR_FMT_CS8:
		reg7 = 0x000c9407; /* 504 */
		अवरोध;
	हाल MSI2500_PIX_FMT_SDR_MSI2500_384:
		reg7 = 0x0000a507; /* 384 */
		अवरोध;
	हाल MSI2500_PIX_FMT_SDR_S12:
		reg7 = 0x00008507; /* 336 */
		अवरोध;
	हाल V4L2_SDR_FMT_CS14LE:
		reg7 = 0x00009407; /* 252 */
		अवरोध;
	शेष:
		reg7 = 0x000c9407; /* 504 */
		अवरोध;
	पूर्ण

	/*
	 * Fractional-N synthesizer
	 *
	 *           +----------------------------------------+
	 *           v                                        |
	 *  Fref   +----+     +-------+     +-----+         +------+     +---+
	 * ------> | PD | --> |  VCO  | --> | /2  | ------> | /N.F | <-- | K |
	 *         +----+     +-------+     +-----+         +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+     +-----+  Fout
	 *                    | /Rout | --> | /12 | ------>
	 *                    +-------+     +-----+
	 */
	/*
	 * Synthesizer config is just a educated guess...
	 *
	 * [7:0]   0x03, रेजिस्टर address
	 * [8]     1, घातer control
	 * [9]     ?, घातer control
	 * [12:10] output भागider
	 * [13]    0 ?
	 * [14]    0 ?
	 * [15]    fractional MSB, bit 20
	 * [16:19] N
	 * [23:20] ?
	 * [24:31] 0x01
	 *
	 * output भागider
	 * val   भाग
	 *   0     - (invalid)
	 *   1     4
	 *   2     6
	 *   3     8
	 *   4    10
	 *   5    12
	 *   6    14
	 *   7    16
	 *
	 * VCO 202000000 - 720000000++
	 */

	#घोषणा F_REF 24000000
	#घोषणा DIV_PRE_N 2
	#घोषणा DIV_LO_OUT 12
	reg3 = 0x01000303;
	reg4 = 0x00000004;

	/* XXX: Filters? AGC? VCO band? */
	अगर (f_sr < 6000000)
		reg3 |= 0x1 << 20;
	अन्यथा अगर (f_sr < 7000000)
		reg3 |= 0x5 << 20;
	अन्यथा अगर (f_sr < 8500000)
		reg3 |= 0x9 << 20;
	अन्यथा
		reg3 |= 0xd << 20;

	क्रम (भाग_out = 4; भाग_out < 16; भाग_out += 2) अणु
		f_vco = f_sr * भाग_out * DIV_LO_OUT;
		dev_dbg(dev->dev, "div_out=%u f_vco=%u\n", भाग_out, f_vco);
		अगर (f_vco >= 202000000)
			अवरोध;
	पूर्ण

	/* Calculate PLL पूर्णांकeger and fractional control word. */
	भाग_n = भाग_u64_rem(f_vco, DIV_PRE_N * F_REF, &k);
	k_cw = भाग_u64((u64) k * 0x200000, DIV_PRE_N * F_REF);

	reg3 |= भाग_n << 16;
	reg3 |= (भाग_out / 2 - 1) << 10;
	reg3 |= ((k_cw >> 20) & 0x000001) << 15; /* [20] */
	reg4 |= ((k_cw >>  0) & 0x0fffff) <<  8; /* [19:0] */

	dev_dbg(dev->dev,
		"f_sr=%u f_vco=%u div_n=%u k=%u div_out=%u reg3=%08x reg4=%08x\n",
		f_sr, f_vco, भाग_n, k, भाग_out, reg3, reg4);

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00608008);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00000c05);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00020000);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00480102);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00f38008);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, reg7);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, reg4);
	अगर (ret)
		जाओ err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, reg3);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा msi2500_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक ret;

	dev_dbg(dev->dev, "\n");

	अगर (!dev->udev)
		वापस -ENODEV;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->v4l2_lock))
		वापस -ERESTARTSYS;

	/* wake-up tuner */
	v4l2_subdev_call(dev->v4l2_subdev, core, s_घातer, 1);

	ret = msi2500_set_usb_adc(dev);

	ret = msi2500_isoc_init(dev);
	अगर (ret)
		msi2500_cleanup_queued_bufs(dev);

	ret = msi2500_ctrl_msg(dev, CMD_START_STREAMING, 0);

	mutex_unlock(&dev->v4l2_lock);

	वापस ret;
पूर्ण

अटल व्योम msi2500_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा msi2500_dev *dev = vb2_get_drv_priv(vq);

	dev_dbg(dev->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	अगर (dev->udev)
		msi2500_isoc_cleanup(dev);

	msi2500_cleanup_queued_bufs(dev);

	/* according to tests, at least 700us delay is required  */
	msleep(20);
	अगर (dev->udev && !msi2500_ctrl_msg(dev, CMD_STOP_STREAMING, 0)) अणु
		/* sleep USB IF / ADC */
		msi2500_ctrl_msg(dev, CMD_WREG, 0x01000003);
	पूर्ण

	/* sleep tuner */
	v4l2_subdev_call(dev->v4l2_subdev, core, s_घातer, 0);

	mutex_unlock(&dev->v4l2_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops msi2500_vb2_ops = अणु
	.queue_setup            = msi2500_queue_setup,
	.buf_queue              = msi2500_buf_queue,
	.start_streaming        = msi2500_start_streaming,
	.stop_streaming         = msi2500_stop_streaming,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक msi2500_क्रमागत_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "index=%d\n", f->index);

	अगर (f->index >= dev->num_क्रमmats)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक msi2500_g_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
		(अक्षर *)&dev->pixelक्रमmat);

	f->fmt.sdr.pixelक्रमmat = dev->pixelक्रमmat;
	f->fmt.sdr.buffersize = dev->buffersize;
	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));

	वापस 0;
पूर्ण

अटल पूर्णांक msi2500_s_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	काष्ठा vb2_queue *q = &dev->vb_queue;
	पूर्णांक i;

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
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

अटल पूर्णांक msi2500_try_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	पूर्णांक i;

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
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

अटल पूर्णांक msi2500_s_tuner(काष्ठा file *file, व्योम *priv,
			   स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	अगर (v->index == 0)
		ret = 0;
	अन्यथा अगर (v->index == 1)
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, s_tuner, v);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *v)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	अगर (v->index == 0) अणु
		strscpy(v->name, "Mirics MSi2500", माप(v->name));
		v->type = V4L2_TUNER_ADC;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow =   1200000;
		v->rangehigh = 15000000;
		ret = 0;
	पूर्ण अन्यथा अगर (v->index == 1) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_tuner, v);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_g_frequency(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_frequency *f)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	पूर्णांक ret  = 0;

	dev_dbg(dev->dev, "tuner=%d type=%d\n", f->tuner, f->type);

	अगर (f->tuner == 0) अणु
		f->frequency = dev->f_adc;
		ret = 0;
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		f->type = V4L2_TUNER_RF;
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_frequency, f);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_s_frequency(काष्ठा file *file, व्योम *priv,
			       स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "tuner=%d type=%d frequency=%u\n",
		f->tuner, f->type, f->frequency);

	अगर (f->tuner == 0) अणु
		dev->f_adc = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				     bands[0].rangelow,
				     bands[0].rangehigh);
		dev_dbg(dev->dev, "ADC frequency=%u Hz\n", dev->f_adc);
		ret = msi2500_set_usb_adc(dev);
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, s_frequency, f);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा msi2500_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "tuner=%d type=%d index=%d\n",
		band->tuner, band->type, band->index);

	अगर (band->tuner == 0) अणु
		अगर (band->index >= ARRAY_SIZE(bands)) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			*band = bands[band->index];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (band->tuner == 1) अणु
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner,
				       क्रमागत_freq_bands, band);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops msi2500_ioctl_ops = अणु
	.vidioc_querycap          = msi2500_querycap,

	.vidioc_क्रमागत_fmt_sdr_cap  = msi2500_क्रमागत_fmt_sdr_cap,
	.vidioc_g_fmt_sdr_cap     = msi2500_g_fmt_sdr_cap,
	.vidioc_s_fmt_sdr_cap     = msi2500_s_fmt_sdr_cap,
	.vidioc_try_fmt_sdr_cap   = msi2500_try_fmt_sdr_cap,

	.vidioc_reqbufs           = vb2_ioctl_reqbufs,
	.vidioc_create_bufs       = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf       = vb2_ioctl_prepare_buf,
	.vidioc_querybuf          = vb2_ioctl_querybuf,
	.vidioc_qbuf              = vb2_ioctl_qbuf,
	.vidioc_dqbuf             = vb2_ioctl_dqbuf,

	.vidioc_streamon          = vb2_ioctl_streamon,
	.vidioc_streamoff         = vb2_ioctl_streamoff,

	.vidioc_g_tuner           = msi2500_g_tuner,
	.vidioc_s_tuner           = msi2500_s_tuner,

	.vidioc_g_frequency       = msi2500_g_frequency,
	.vidioc_s_frequency       = msi2500_s_frequency,
	.vidioc_क्रमागत_freq_bands   = msi2500_क्रमागत_freq_bands,

	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_log_status        = v4l2_ctrl_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations msi2500_fops = अणु
	.owner                    = THIS_MODULE,
	.खोलो                     = v4l2_fh_खोलो,
	.release                  = vb2_fop_release,
	.पढ़ो                     = vb2_fop_पढ़ो,
	.poll                     = vb2_fop_poll,
	.mmap                     = vb2_fop_mmap,
	.unlocked_ioctl           = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा video_device msi2500_ढाँचा = अणु
	.name                     = "Mirics MSi3101 SDR Dongle",
	.release                  = video_device_release_empty,
	.fops                     = &msi2500_fops,
	.ioctl_ops                = &msi2500_ioctl_ops,
पूर्ण;

अटल व्योम msi2500_video_release(काष्ठा v4l2_device *v)
अणु
	काष्ठा msi2500_dev *dev = container_of(v, काष्ठा msi2500_dev, v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&dev->hdl);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक msi2500_transfer_one_message(काष्ठा spi_master *master,
					काष्ठा spi_message *m)
अणु
	काष्ठा msi2500_dev *dev = spi_master_get_devdata(master);
	काष्ठा spi_transfer *t;
	पूर्णांक ret = 0;
	u32 data;

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		dev_dbg(dev->dev, "msg=%*ph\n", t->len, t->tx_buf);
		data = 0x09; /* reg 9 is SPI adapter */
		data |= ((u8 *)t->tx_buf)[0] << 8;
		data |= ((u8 *)t->tx_buf)[1] << 16;
		data |= ((u8 *)t->tx_buf)[2] << 24;
		ret = msi2500_ctrl_msg(dev, CMD_WREG, data);
	पूर्ण

	m->status = ret;
	spi_finalize_current_message(master);
	वापस ret;
पूर्ण

अटल पूर्णांक msi2500_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा msi2500_dev *dev;
	काष्ठा v4l2_subdev *sd;
	काष्ठा spi_master *master;
	पूर्णांक ret;
	अटल काष्ठा spi_board_info board_info = अणु
		.modalias		= "msi001",
		.bus_num		= 0,
		.chip_select		= 0,
		.max_speed_hz		= 12000000,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mutex_init(&dev->v4l2_lock);
	mutex_init(&dev->vb_queue_lock);
	spin_lock_init(&dev->queued_bufs_lock);
	INIT_LIST_HEAD(&dev->queued_bufs);
	dev->dev = &पूर्णांकf->dev;
	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	dev->f_adc = bands[0].rangelow;
	dev->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	dev->buffersize = क्रमmats[0].buffersize;
	dev->num_क्रमmats = NUM_FORMATS;
	अगर (!msi2500_emulated_fmt)
		dev->num_क्रमmats -= 2;

	/* Init videobuf2 queue काष्ठाure */
	dev->vb_queue.type = V4L2_BUF_TYPE_SDR_CAPTURE;
	dev->vb_queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	dev->vb_queue.drv_priv = dev;
	dev->vb_queue.buf_काष्ठा_size = माप(काष्ठा msi2500_frame_buf);
	dev->vb_queue.ops = &msi2500_vb2_ops;
	dev->vb_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	dev->vb_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	ret = vb2_queue_init(&dev->vb_queue);
	अगर (ret) अणु
		dev_err(dev->dev, "Could not initialize vb2 queue\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	/* Init video_device काष्ठाure */
	dev->vdev = msi2500_ढाँचा;
	dev->vdev.queue = &dev->vb_queue;
	dev->vdev.queue->lock = &dev->vb_queue_lock;
	video_set_drvdata(&dev->vdev, dev);

	/* Register the v4l2_device काष्ठाure */
	dev->v4l2_dev.release = msi2500_video_release;
	ret = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to register v4l2-device (%d)\n", ret);
		जाओ err_मुक्त_mem;
	पूर्ण

	/* SPI master adapter */
	master = spi_alloc_master(dev->dev, 0);
	अगर (master == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_unरेजिस्टर_v4l2_dev;
	पूर्ण

	dev->master = master;
	master->bus_num = -1;
	master->num_chipselect = 1;
	master->transfer_one_message = msi2500_transfer_one_message;
	spi_master_set_devdata(master, dev);
	ret = spi_रेजिस्टर_master(master);
	अगर (ret) अणु
		spi_master_put(master);
		जाओ err_unरेजिस्टर_v4l2_dev;
	पूर्ण

	/* load v4l2 subdevice */
	sd = v4l2_spi_new_subdev(&dev->v4l2_dev, master, &board_info);
	dev->v4l2_subdev = sd;
	अगर (sd == शून्य) अणु
		dev_err(dev->dev, "cannot get v4l2 subdevice\n");
		ret = -ENODEV;
		जाओ err_unरेजिस्टर_master;
	पूर्ण

	/* Register controls */
	v4l2_ctrl_handler_init(&dev->hdl, 0);
	अगर (dev->hdl.error) अणु
		ret = dev->hdl.error;
		dev_err(dev->dev, "Could not initialize controls\n");
		जाओ err_मुक्त_controls;
	पूर्ण

	/* currently all controls are from subdev */
	v4l2_ctrl_add_handler(&dev->hdl, sd->ctrl_handler, शून्य, true);

	dev->v4l2_dev.ctrl_handler = &dev->hdl;
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.lock = &dev->v4l2_lock;
	dev->vdev.device_caps = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_STREAMING |
				V4L2_CAP_READWRITE | V4L2_CAP_TUNER;

	ret = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_SDR, -1);
	अगर (ret) अणु
		dev_err(dev->dev,
			"Failed to register as video device (%d)\n", ret);
		जाओ err_unरेजिस्टर_v4l2_dev;
	पूर्ण
	dev_info(dev->dev, "Registered as %s\n",
		 video_device_node_name(&dev->vdev));
	dev_notice(dev->dev,
		   "SDR API is still slightly experimental and functionality changes may follow\n");
	वापस 0;
err_मुक्त_controls:
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
err_unरेजिस्टर_master:
	spi_unरेजिस्टर_master(dev->master);
err_unरेजिस्टर_v4l2_dev:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_मुक्त_mem:
	kमुक्त(dev);
err:
	वापस ret;
पूर्ण

/* USB device ID list */
अटल स्थिर काष्ठा usb_device_id msi2500_id_table[] = अणु
	अणुUSB_DEVICE(0x1df7, 0x2500)पूर्ण, /* Mirics MSi3101 SDR Dongle */
	अणुUSB_DEVICE(0x2040, 0xd300)पूर्ण, /* Hauppauge WinTV 133559 LF */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, msi2500_id_table);

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver msi2500_driver = अणु
	.name                     = KBUILD_MODNAME,
	.probe                    = msi2500_probe,
	.disconnect               = msi2500_disconnect,
	.id_table                 = msi2500_id_table,
पूर्ण;

module_usb_driver(msi2500_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Mirics MSi3101 SDR Dongle");
MODULE_LICENSE("GPL");
