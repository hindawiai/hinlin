<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// पंचांग6000-video.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
//
// Copyright (c) 2006-2007 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// Copyright (c) 2007 Michel Ludwig <michel.ludwig@gmail.com>
//	- Fixed module load/unload

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/tuner.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/मुक्तzer.h>

#समावेश "tm6000-regs.h"
#समावेश "tm6000.h"

#घोषणा BUFFER_TIMEOUT     msecs_to_jअगरfies(2000)  /* 2 seconds */

/* Limits minimum and शेष number of buffers */
#घोषणा TM6000_MIN_BUF 4
#घोषणा TM6000_DEF_BUF 8

#घोषणा TM6000_NUM_URB_BUF 8

#घोषणा TM6000_MAX_ISO_PACKETS	46	/* Max number of ISO packets */

/* Declare अटल vars that will be used as parameters */
अटल अचिन्हित पूर्णांक vid_limit = 16;	/* Video memory limit, in Mb */
अटल पूर्णांक video_nr = -1;		/* /dev/videoN, -1 क्रम स्वतःdetect */
अटल पूर्णांक radio_nr = -1;		/* /dev/radioN, -1 क्रम स्वतःdetect */
अटल bool keep_urb;			/* keep urb buffers allocated */

/* Debug level */
पूर्णांक पंचांग6000_debug;
EXPORT_SYMBOL_GPL(पंचांग6000_debug);

अटल काष्ठा पंचांग6000_fmt क्रमmat[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.depth    = 16,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_UYVY,
		.depth    = 16,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_TM6000,
		.depth    = 16,
	पूर्ण
पूर्ण;

/* ------------------------------------------------------------------
 *	DMA and thपढ़ो functions
 * ------------------------------------------------------------------
 */

#घोषणा norm_maxw(a) 720
#घोषणा norm_maxh(a) 576

#घोषणा norm_minw(a) norm_maxw(a)
#घोषणा norm_minh(a) norm_maxh(a)

/*
 * video-buf generic routine to get the next available buffer
 */
अटल अंतरभूत व्योम get_next_buf(काष्ठा पंचांग6000_dmaqueue *dma_q,
			       काष्ठा पंचांग6000_buffer   **buf)
अणु
	काष्ठा पंचांग6000_core *dev = container_of(dma_q, काष्ठा पंचांग6000_core, vidq);

	अगर (list_empty(&dma_q->active)) अणु
		dprपूर्णांकk(dev, V4L2_DEBUG_QUEUE, "No active queue to serve\n");
		*buf = शून्य;
		वापस;
	पूर्ण

	*buf = list_entry(dma_q->active.next,
			काष्ठा पंचांग6000_buffer, vb.queue);
पूर्ण

/*
 * Announces that a buffer were filled and request the next
 */
अटल अंतरभूत व्योम buffer_filled(काष्ठा पंचांग6000_core *dev,
				 काष्ठा पंचांग6000_dmaqueue *dma_q,
				 काष्ठा पंचांग6000_buffer *buf)
अणु
	/* Advice that buffer was filled */
	dprपूर्णांकk(dev, V4L2_DEBUG_ISOC, "[%p/%d] wakeup\n", buf, buf->vb.i);
	buf->vb.state = VIDEOBUF_DONE;
	buf->vb.field_count++;
	buf->vb.ts = kसमय_get_ns();

	list_del(&buf->vb.queue);
	wake_up(&buf->vb.करोne);
पूर्ण

/*
 * Identअगरy the पंचांग5600/6000 buffer header type and properly handles
 */
अटल पूर्णांक copy_streams(u8 *data, अचिन्हित दीर्घ len,
			काष्ठा urb *urb)
अणु
	काष्ठा पंचांग6000_dmaqueue  *dma_q = urb->context;
	काष्ठा पंचांग6000_core *dev = container_of(dma_q, काष्ठा पंचांग6000_core, vidq);
	u8 *ptr = data, *endp = data+len;
	अचिन्हित दीर्घ header = 0;
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक cmd, cpysize, pktsize, size, field, block, line, pos = 0;
	काष्ठा पंचांग6000_buffer *vbuf = शून्य;
	अक्षर *voutp = शून्य;
	अचिन्हित पूर्णांक linewidth;

	अगर (!dev->radio) अणु
		/* get video buffer */
		get_next_buf(dma_q, &vbuf);

		अगर (!vbuf)
			वापस rc;
		voutp = videobuf_to_vदो_स्मृति(&vbuf->vb);

		अगर (!voutp)
			वापस 0;
	पूर्ण

	क्रम (ptr = data; ptr < endp;) अणु
		अगर (!dev->isoc_ctl.cmd) अणु
			/* Header */
			अगर (dev->isoc_ctl.पंचांगp_buf_len > 0) अणु
				/* from last urb or packet */
				header = dev->isoc_ctl.पंचांगp_buf;
				अगर (4 - dev->isoc_ctl.पंचांगp_buf_len > 0) अणु
					स_नकल((u8 *)&header +
						dev->isoc_ctl.पंचांगp_buf_len,
						ptr,
						4 - dev->isoc_ctl.पंचांगp_buf_len);
					ptr += 4 - dev->isoc_ctl.पंचांगp_buf_len;
				पूर्ण
				dev->isoc_ctl.पंचांगp_buf_len = 0;
			पूर्ण अन्यथा अणु
				अगर (ptr + 3 >= endp) अणु
					/* have incomplete header */
					dev->isoc_ctl.पंचांगp_buf_len = endp - ptr;
					स_नकल(&dev->isoc_ctl.पंचांगp_buf, ptr,
						dev->isoc_ctl.पंचांगp_buf_len);
					वापस rc;
				पूर्ण
				/* Seek क्रम sync */
				क्रम (; ptr < endp - 3; ptr++) अणु
					अगर (*(ptr + 3) == 0x47)
						अवरोध;
				पूर्ण
				/* Get message header */
				header = *(अचिन्हित दीर्घ *)ptr;
				ptr += 4;
			पूर्ण

			/* split the header fields */
			size = ((header & 0x7e) << 1);
			अगर (size > 0)
				size -= 4;
			block = (header >> 7) & 0xf;
			field = (header >> 11) & 0x1;
			line  = (header >> 12) & 0x1ff;
			cmd   = (header >> 21) & 0x7;
			/* Validates header fields */
			अगर (size > TM6000_URB_MSG_LEN)
				size = TM6000_URB_MSG_LEN;
			pktsize = TM6000_URB_MSG_LEN;
			/*
			 * calculate position in buffer and change the buffer
			 */
			चयन (cmd) अणु
			हाल TM6000_URB_MSG_VIDEO:
				अगर (!dev->radio) अणु
					अगर ((dev->isoc_ctl.vfield != field) &&
						(field == 1)) अणु
						/*
						 * Announces that a new buffer
						 * were filled
						 */
						buffer_filled(dev, dma_q, vbuf);
						dprपूर्णांकk(dev, V4L2_DEBUG_ISOC,
							"new buffer filled\n");
						get_next_buf(dma_q, &vbuf);
						अगर (!vbuf)
							वापस rc;
						voutp = videobuf_to_vदो_स्मृति(&vbuf->vb);
						अगर (!voutp)
							वापस rc;
						स_रखो(voutp, 0, vbuf->vb.size);
					पूर्ण
					linewidth = vbuf->vb.width << 1;
					pos = ((line << 1) - field - 1) *
					linewidth + block * TM6000_URB_MSG_LEN;
					/* Don't allow to ग_लिखो out of the buffer */
					अगर (pos + size > vbuf->vb.size)
						cmd = TM6000_URB_MSG_ERR;
					dev->isoc_ctl.vfield = field;
				पूर्ण
				अवरोध;
			हाल TM6000_URB_MSG_VBI:
				अवरोध;
			हाल TM6000_URB_MSG_AUDIO:
			हाल TM6000_URB_MSG_PTS:
				size = pktsize; /* Size is always 180 bytes */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Continue the last copy */
			cmd = dev->isoc_ctl.cmd;
			size = dev->isoc_ctl.size;
			pos = dev->isoc_ctl.pos;
			pktsize = dev->isoc_ctl.pktsize;
			field = dev->isoc_ctl.field;
		पूर्ण
		cpysize = (endp - ptr > size) ? size : endp - ptr;
		अगर (cpysize) अणु
			/* copy data in dअगरferent buffers */
			चयन (cmd) अणु
			हाल TM6000_URB_MSG_VIDEO:
				/* Fills video buffer */
				अगर (vbuf)
					स_नकल(&voutp[pos], ptr, cpysize);
				अवरोध;
			हाल TM6000_URB_MSG_AUDIO: अणु
				पूर्णांक i;
				क्रम (i = 0; i < cpysize; i += 2)
					swab16s((u16 *)(ptr + i));

				पंचांग6000_call_fillbuf(dev, TM6000_AUDIO, ptr, cpysize);
				अवरोध;
			पूर्ण
			हाल TM6000_URB_MSG_VBI:
				/* Need some code to copy vbi buffer */
				अवरोध;
			हाल TM6000_URB_MSG_PTS: अणु
				/* Need some code to copy pts */
				u32 pts;
				pts = *(u32 *)ptr;
				dprपूर्णांकk(dev, V4L2_DEBUG_ISOC, "field %d, PTS %x",
					field, pts);
				अवरोध;
			पूर्ण
			पूर्ण
		पूर्ण
		अगर (ptr + pktsize > endp) अणु
			/*
			 * End of URB packet, but cmd processing is not
			 * complete. Preserve the state क्रम a next packet
			 */
			dev->isoc_ctl.pos = pos + cpysize;
			dev->isoc_ctl.size = size - cpysize;
			dev->isoc_ctl.cmd = cmd;
			dev->isoc_ctl.field = field;
			dev->isoc_ctl.pktsize = pktsize - (endp - ptr);
			ptr += endp - ptr;
		पूर्ण अन्यथा अणु
			dev->isoc_ctl.cmd = 0;
			ptr += pktsize;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Identअगरy the पंचांग5600/6000 buffer header type and properly handles
 */
अटल पूर्णांक copy_multiplexed(u8 *ptr, अचिन्हित दीर्घ len,
			काष्ठा urb *urb)
अणु
	काष्ठा पंचांग6000_dmaqueue  *dma_q = urb->context;
	काष्ठा पंचांग6000_core *dev = container_of(dma_q, काष्ठा पंचांग6000_core, vidq);
	अचिन्हित पूर्णांक pos = dev->isoc_ctl.pos, cpysize;
	पूर्णांक rc = 1;
	काष्ठा पंचांग6000_buffer *buf;
	अक्षर *outp = शून्य;

	get_next_buf(dma_q, &buf);
	अगर (buf)
		outp = videobuf_to_vदो_स्मृति(&buf->vb);

	अगर (!outp)
		वापस 0;

	जबतक (len > 0) अणु
		cpysize = min(len, buf->vb.size-pos);
		स_नकल(&outp[pos], ptr, cpysize);
		pos += cpysize;
		ptr += cpysize;
		len -= cpysize;
		अगर (pos >= buf->vb.size) अणु
			pos = 0;
			/* Announces that a new buffer were filled */
			buffer_filled(dev, dma_q, buf);
			dprपूर्णांकk(dev, V4L2_DEBUG_ISOC, "new buffer filled\n");
			get_next_buf(dma_q, &buf);
			अगर (!buf)
				अवरोध;
			outp = videobuf_to_vदो_स्मृति(&(buf->vb));
			अगर (!outp)
				वापस rc;
			pos = 0;
		पूर्ण
	पूर्ण

	dev->isoc_ctl.pos = pos;
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा पंचांग6000_core *dev,
				     पूर्णांक packet, पूर्णांक status)
अणु
	अक्षर *errmsg = "Unknown";

	चयन (status) अणु
	हाल -ENOENT:
		errmsg = "unlinked synchronously";
		अवरोध;
	हाल -ECONNRESET:
		errmsg = "unlinked asynchronously";
		अवरोध;
	हाल -ENOSR:
		errmsg = "Buffer error (overrun)";
		अवरोध;
	हाल -EPIPE:
		errmsg = "Stalled (device not responding)";
		अवरोध;
	हाल -EOVERFLOW:
		errmsg = "Babble (bad cable?)";
		अवरोध;
	हाल -EPROTO:
		errmsg = "Bit-stuff error (bad cable?)";
		अवरोध;
	हाल -EILSEQ:
		errmsg = "CRC/Timeout (could be anything)";
		अवरोध;
	हाल -ETIME:
		errmsg = "Device does not respond";
		अवरोध;
	पूर्ण
	अगर (packet < 0) अणु
		dprपूर्णांकk(dev, V4L2_DEBUG_QUEUE, "URB status %d [%s].\n",
			status, errmsg);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(dev, V4L2_DEBUG_QUEUE, "URB packet %d, status %d [%s].\n",
			packet, status, errmsg);
	पूर्ण
पूर्ण


/*
 * Controls the isoc copy of each urb packet
 */
अटल अंतरभूत पूर्णांक पंचांग6000_isoc_copy(काष्ठा urb *urb)
अणु
	काष्ठा पंचांग6000_dmaqueue  *dma_q = urb->context;
	काष्ठा पंचांग6000_core *dev = container_of(dma_q, काष्ठा पंचांग6000_core, vidq);
	पूर्णांक i, len = 0, rc = 1, status;
	अक्षर *p;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		status = urb->iso_frame_desc[i].status;

		अगर (status < 0) अणु
			prपूर्णांक_err_status(dev, i, status);
			जारी;
		पूर्ण

		len = urb->iso_frame_desc[i].actual_length;

		अगर (len > 0) अणु
			p = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
			अगर (!urb->iso_frame_desc[i].status) अणु
				अगर ((dev->fourcc) == V4L2_PIX_FMT_TM6000) अणु
					rc = copy_multiplexed(p, len, urb);
					अगर (rc <= 0)
						वापस rc;
				पूर्ण अन्यथा अणु
					copy_streams(p, len, urb);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/* ------------------------------------------------------------------
 *	URB control
 * ------------------------------------------------------------------
 */

/*
 * IRQ callback, called by URB callback
 */
अटल व्योम पंचांग6000_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा पंचांग6000_dmaqueue  *dma_q = urb->context;
	काष्ठा पंचांग6000_core *dev = container_of(dma_q, काष्ठा पंचांग6000_core, vidq);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0:
	हाल -ETIMEDOUT:
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		पंचांग6000_err("urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&dev->slock, flags);
	पंचांग6000_isoc_copy(urb);
	spin_unlock_irqrestore(&dev->slock, flags);

	/* Reset urb buffers */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	पूर्ण

	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (urb->status)
		पंचांग6000_err("urb resubmit failed (error=%i)\n",
			urb->status);
पूर्ण

/*
 * Allocate URB buffers
 */
अटल पूर्णांक पंचांग6000_alloc_urb_buffers(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक num_bufs = TM6000_NUM_URB_BUF;
	पूर्णांक i;

	अगर (dev->urb_buffer)
		वापस 0;

	dev->urb_buffer = kदो_स्मृति_array(num_bufs, माप(*dev->urb_buffer),
					GFP_KERNEL);
	अगर (!dev->urb_buffer)
		वापस -ENOMEM;

	dev->urb_dma = kदो_स्मृति_array(num_bufs, माप(*dev->urb_dma),
				     GFP_KERNEL);
	अगर (!dev->urb_dma)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_bufs; i++) अणु
		dev->urb_buffer[i] = usb_alloc_coherent(
					dev->udev, dev->urb_size,
					GFP_KERNEL, &dev->urb_dma[i]);
		अगर (!dev->urb_buffer[i]) अणु
			पंचांग6000_err("unable to allocate %i bytes for transfer buffer %i\n",
				    dev->urb_size, i);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(dev->urb_buffer[i], 0, dev->urb_size);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Free URB buffers
 */
अटल पूर्णांक पंचांग6000_मुक्त_urb_buffers(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक i;

	अगर (!dev->urb_buffer)
		वापस 0;

	क्रम (i = 0; i < TM6000_NUM_URB_BUF; i++) अणु
		अगर (dev->urb_buffer[i]) अणु
			usb_मुक्त_coherent(dev->udev,
					dev->urb_size,
					dev->urb_buffer[i],
					dev->urb_dma[i]);
			dev->urb_buffer[i] = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(dev->urb_buffer);
	kमुक्त(dev->urb_dma);
	dev->urb_buffer = शून्य;
	dev->urb_dma = शून्य;

	वापस 0;
पूर्ण

/*
 * Stop and Deallocate URBs
 */
अटल व्योम पंचांग6000_uninit_isoc(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	dev->isoc_ctl.buf = शून्य;
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		urb = dev->isoc_ctl.urb[i];
		अगर (urb) अणु
			usb_समाप्त_urb(urb);
			usb_unlink_urb(urb);
			usb_मुक्त_urb(urb);
			dev->isoc_ctl.urb[i] = शून्य;
		पूर्ण
		dev->isoc_ctl.transfer_buffer[i] = शून्य;
	पूर्ण

	अगर (!keep_urb)
		पंचांग6000_मुक्त_urb_buffers(dev);

	kमुक्त(dev->isoc_ctl.urb);
	kमुक्त(dev->isoc_ctl.transfer_buffer);

	dev->isoc_ctl.urb = शून्य;
	dev->isoc_ctl.transfer_buffer = शून्य;
	dev->isoc_ctl.num_bufs = 0;
पूर्ण

/*
 * Assign URBs and start IRQ
 */
अटल पूर्णांक पंचांग6000_prepare_isoc(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_dmaqueue *dma_q = &dev->vidq;
	पूर्णांक i, j, sb_size, pipe, size, max_packets;
	पूर्णांक num_bufs = TM6000_NUM_URB_BUF;
	काष्ठा urb *urb;

	/* De-allocates all pending stuff */
	पंचांग6000_uninit_isoc(dev);
	/* Stop पूर्णांकerrupt USB pipe */
	पंचांग6000_ir_पूर्णांक_stop(dev);

	usb_set_पूर्णांकerface(dev->udev,
			  dev->isoc_in.bInterfaceNumber,
			  dev->isoc_in.bAlternateSetting);

	/* Start पूर्णांकerrupt USB pipe */
	पंचांग6000_ir_पूर्णांक_start(dev);

	pipe = usb_rcvisocpipe(dev->udev,
			       dev->isoc_in.endp->desc.bEndpoपूर्णांकAddress &
			       USB_ENDPOINT_NUMBER_MASK);

	size = usb_maxpacket(dev->udev, pipe, usb_pipeout(pipe));

	अगर (size > dev->isoc_in.maxsize)
		size = dev->isoc_in.maxsize;

	dev->isoc_ctl.max_pkt_size = size;

	max_packets = TM6000_MAX_ISO_PACKETS;
	sb_size = max_packets * size;
	dev->urb_size = sb_size;

	dev->isoc_ctl.num_bufs = num_bufs;

	dev->isoc_ctl.urb = kदो_स्मृति_array(num_bufs, माप(व्योम *),
					  GFP_KERNEL);
	अगर (!dev->isoc_ctl.urb)
		वापस -ENOMEM;

	dev->isoc_ctl.transfer_buffer = kदो_स्मृति_array(num_bufs,
						      माप(व्योम *),
						      GFP_KERNEL);
	अगर (!dev->isoc_ctl.transfer_buffer) अणु
		kमुक्त(dev->isoc_ctl.urb);
		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(dev, V4L2_DEBUG_QUEUE, "Allocating %d x %d packets (%d bytes) of %d bytes each to handle %u size\n",
		    max_packets, num_bufs, sb_size,
		    dev->isoc_in.maxsize, size);


	अगर (पंचांग6000_alloc_urb_buffers(dev) < 0) अणु
		पंचांग6000_err("cannot allocate memory for urb buffers\n");

		/* call मुक्त, as some buffers might have been allocated */
		पंचांग6000_मुक्त_urb_buffers(dev);
		kमुक्त(dev->isoc_ctl.urb);
		kमुक्त(dev->isoc_ctl.transfer_buffer);
		वापस -ENOMEM;
	पूर्ण

	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		urb = usb_alloc_urb(max_packets, GFP_KERNEL);
		अगर (!urb) अणु
			पंचांग6000_uninit_isoc(dev);
			पंचांग6000_मुक्त_urb_buffers(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->isoc_ctl.urb[i] = urb;

		urb->transfer_dma = dev->urb_dma[i];
		dev->isoc_ctl.transfer_buffer[i] = dev->urb_buffer[i];

		usb_fill_bulk_urb(urb, dev->udev, pipe,
				  dev->isoc_ctl.transfer_buffer[i], sb_size,
				  पंचांग6000_irq_callback, dma_q);
		urb->पूर्णांकerval = dev->isoc_in.endp->desc.bInterval;
		urb->number_of_packets = max_packets;
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;

		क्रम (j = 0; j < max_packets; j++) अणु
			urb->iso_frame_desc[j].offset = size * j;
			urb->iso_frame_desc[j].length = size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग6000_start_thपढ़ो(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_dmaqueue *dma_q = &dev->vidq;
	पूर्णांक i;

	dma_q->frame = 0;
	dma_q->ini_jअगरfies = jअगरfies;

	init_रुकोqueue_head(&dma_q->wq);

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		पूर्णांक rc = usb_submit_urb(dev->isoc_ctl.urb[i], GFP_ATOMIC);
		अगर (rc) अणु
			पंचांग6000_err("submit of urb %i failed (error=%i)\n", i,
				   rc);
			पंचांग6000_uninit_isoc(dev);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------
 *	Videobuf operations
 * ------------------------------------------------------------------
 */

अटल पूर्णांक
buffer_setup(काष्ठा videobuf_queue *vq, अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा पंचांग6000_fh *fh = vq->priv_data;

	*size = fh->fmt->depth * fh->width * fh->height >> 3;
	अगर (0 == *count)
		*count = TM6000_DEF_BUF;

	अगर (*count < TM6000_MIN_BUF)
		*count = TM6000_MIN_BUF;

	जबतक (*size * *count > vid_limit * 1024 * 1024)
		(*count)--;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_buffer(काष्ठा videobuf_queue *vq, काष्ठा पंचांग6000_buffer *buf)
अणु
	काष्ठा पंचांग6000_fh *fh = vq->priv_data;
	काष्ठा पंचांग6000_core   *dev = fh->dev;
	अचिन्हित दीर्घ flags;

	/* We used to रुको क्रम the buffer to finish here, but this didn't work
	   because, as we were keeping the state as VIDEOBUF_QUEUED,
	   videobuf_queue_cancel marked it as finished क्रम us.
	   (Also, it could wedge क्रमever अगर the hardware was misconfigured.)

	   This should be safe; by the समय we get here, the buffer isn't
	   queued anymore. If we ever start marking the buffers as
	   VIDEOBUF_ACTIVE, it won't be, though.
	*/
	spin_lock_irqsave(&dev->slock, flags);
	अगर (dev->isoc_ctl.buf == buf)
		dev->isoc_ctl.buf = शून्य;
	spin_unlock_irqrestore(&dev->slock, flags);

	videobuf_vदो_स्मृति_मुक्त(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
पूर्ण

अटल पूर्णांक
buffer_prepare(काष्ठा videobuf_queue *vq, काष्ठा videobuf_buffer *vb,
						क्रमागत v4l2_field field)
अणु
	काष्ठा पंचांग6000_fh     *fh  = vq->priv_data;
	काष्ठा पंचांग6000_buffer *buf = container_of(vb, काष्ठा पंचांग6000_buffer, vb);
	काष्ठा पंचांग6000_core   *dev = fh->dev;
	पूर्णांक rc = 0;

	BUG_ON(शून्य == fh->fmt);


	/* FIXME: It assumes depth=2 */
	/* The only currently supported क्रमmat is 16 bits/pixel */
	buf->vb.size = fh->fmt->depth*fh->width*fh->height >> 3;
	अगर (0 != buf->vb.baddr  &&  buf->vb.bsize < buf->vb.size)
		वापस -EINVAL;

	अगर (buf->fmt       != fh->fmt    ||
	    buf->vb.width  != fh->width  ||
	    buf->vb.height != fh->height ||
	    buf->vb.field  != field) अणु
		buf->fmt       = fh->fmt;
		buf->vb.width  = fh->width;
		buf->vb.height = fh->height;
		buf->vb.field  = field;
		buf->vb.state = VIDEOBUF_NEEDS_INIT;
	पूर्ण

	अगर (VIDEOBUF_NEEDS_INIT == buf->vb.state) अणु
		rc = videobuf_iolock(vq, &buf->vb, शून्य);
		अगर (rc != 0)
			जाओ fail;
	पूर्ण

	अगर (!dev->isoc_ctl.num_bufs) अणु
		rc = पंचांग6000_prepare_isoc(dev);
		अगर (rc < 0)
			जाओ fail;

		rc = पंचांग6000_start_thपढ़ो(dev);
		अगर (rc < 0)
			जाओ fail;

	पूर्ण

	buf->vb.state = VIDEOBUF_PREPARED;
	वापस 0;

fail:
	मुक्त_buffer(vq, buf);
	वापस rc;
पूर्ण

अटल व्योम
buffer_queue(काष्ठा videobuf_queue *vq, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा पंचांग6000_buffer    *buf     = container_of(vb, काष्ठा पंचांग6000_buffer, vb);
	काष्ठा पंचांग6000_fh        *fh      = vq->priv_data;
	काष्ठा पंचांग6000_core      *dev     = fh->dev;
	काष्ठा पंचांग6000_dmaqueue  *vidq    = &dev->vidq;

	buf->vb.state = VIDEOBUF_QUEUED;
	list_add_tail(&buf->vb.queue, &vidq->active);
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *vq, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा पंचांग6000_buffer   *buf  = container_of(vb, काष्ठा पंचांग6000_buffer, vb);

	मुक्त_buffer(vq, buf);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops पंचांग6000_video_qops = अणु
	.buf_setup      = buffer_setup,
	.buf_prepare    = buffer_prepare,
	.buf_queue      = buffer_queue,
	.buf_release    = buffer_release,
पूर्ण;

/* ------------------------------------------------------------------
 *	IOCTL handling
 * ------------------------------------------------------------------
 */

अटल bool is_res_पढ़ो(काष्ठा पंचांग6000_core *dev, काष्ठा पंचांग6000_fh *fh)
अणु
	/* Is the current fh handling it? अगर so, that's OK */
	अगर (dev->resources == fh && dev->is_res_पढ़ो)
		वापस true;

	वापस false;
पूर्ण

अटल bool is_res_streaming(काष्ठा पंचांग6000_core *dev, काष्ठा पंचांग6000_fh *fh)
अणु
	/* Is the current fh handling it? अगर so, that's OK */
	अगर (dev->resources == fh)
		वापस true;

	वापस false;
पूर्ण

अटल bool res_get(काष्ठा पंचांग6000_core *dev, काष्ठा पंचांग6000_fh *fh,
		   bool is_res_पढ़ो)
अणु
	/* Is the current fh handling it? अगर so, that's OK */
	अगर (dev->resources == fh && dev->is_res_पढ़ो == is_res_पढ़ो)
		वापस true;

	/* is it मुक्त? */
	अगर (dev->resources)
		वापस false;

	/* grab it */
	dev->resources = fh;
	dev->is_res_पढ़ो = is_res_पढ़ो;
	dprपूर्णांकk(dev, V4L2_DEBUG_RES_LOCK, "res: get\n");
	वापस true;
पूर्ण

अटल व्योम res_मुक्त(काष्ठा पंचांग6000_core *dev, काष्ठा पंचांग6000_fh *fh)
अणु
	/* Is the current fh handling it? अगर so, that's OK */
	अगर (dev->resources != fh)
		वापस;

	dev->resources = शून्य;
	dprपूर्णांकk(dev, V4L2_DEBUG_RES_LOCK, "res: put\n");
पूर्ण

/* ------------------------------------------------------------------
 *	IOCTL vidioc handling
 * ------------------------------------------------------------------
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा पंचांग6000_core *dev = ((काष्ठा पंचांग6000_fh *)priv)->dev;

	strscpy(cap->driver, "tm6000", माप(cap->driver));
	strscpy(cap->card, "Trident TVMaster TM5600/6000/6010",
		माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_DEVICE_CAPS;
	अगर (dev->tuner_type != TUNER_ABSENT)
		cap->capabilities |= V4L2_CAP_TUNER;
	अगर (dev->caps.has_radio)
		cap->capabilities |= V4L2_CAP_RADIO;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(क्रमmat))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmat[f->index].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा पंचांग6000_fh  *fh = priv;

	f->fmt.pix.width        = fh->width;
	f->fmt.pix.height       = fh->height;
	f->fmt.pix.field        = fh->vb_vidq.field;
	f->fmt.pix.pixelक्रमmat  = fh->fmt->fourcc;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * fh->fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;

	वापस 0;
पूर्ण

अटल काष्ठा पंचांग6000_fmt *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmat); i++)
		अगर (क्रमmat[i].fourcc == fourcc)
			वापस क्रमmat+i;
	वापस शून्य;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा पंचांग6000_core *dev = ((काष्ठा पंचांग6000_fh *)priv)->dev;
	काष्ठा पंचांग6000_fmt *fmt;
	क्रमागत v4l2_field field;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt) अणु
		dprपूर्णांकk(dev, 2, "Fourcc format (0x%08x) invalid.\n",
			f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	field = f->fmt.pix.field;

	field = V4L2_FIELD_INTERLACED;

	पंचांग6000_get_std_res(dev);

	f->fmt.pix.width  = dev->width;
	f->fmt.pix.height = dev->height;

	f->fmt.pix.width &= ~0x01;

	f->fmt.pix.field = field;

	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

/*FIXME: This seems to be generic enough to be at videodev2 */
अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा पंचांग6000_fh  *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;
	पूर्णांक ret = vidioc_try_fmt_vid_cap(file, fh, f);
	अगर (ret < 0)
		वापस ret;

	fh->fmt           = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	fh->width         = f->fmt.pix.width;
	fh->height        = f->fmt.pix.height;
	fh->vb_vidq.field = f->fmt.pix.field;
	fh->type          = f->type;

	dev->fourcc       = f->fmt.pix.pixelक्रमmat;

	पंचांग6000_set_fourcc_क्रमmat(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_reqbufs(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_requestbuffers *p)
अणु
	काष्ठा पंचांग6000_fh  *fh = priv;

	वापस videobuf_reqbufs(&fh->vb_vidq, p);
पूर्ण

अटल पूर्णांक vidioc_querybuf(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_buffer *p)
अणु
	काष्ठा पंचांग6000_fh  *fh = priv;

	वापस videobuf_querybuf(&fh->vb_vidq, p);
पूर्ण

अटल पूर्णांक vidioc_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा पंचांग6000_fh  *fh = priv;

	वापस videobuf_qbuf(&fh->vb_vidq, p);
पूर्ण

अटल पूर्णांक vidioc_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा पंचांग6000_fh  *fh = priv;

	वापस videobuf_dqbuf(&fh->vb_vidq, p,
				file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा पंचांग6000_fh *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	अगर (i != fh->type)
		वापस -EINVAL;

	अगर (!res_get(dev, fh, false))
		वापस -EBUSY;
	वापस videobuf_streamon(&fh->vb_vidq);
पूर्ण

अटल पूर्णांक vidioc_streamoff(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा पंचांग6000_fh *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (i != fh->type)
		वापस -EINVAL;

	videobuf_streamoff(&fh->vb_vidq);
	res_मुक्त(dev, fh);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id norm)
अणु
	पूर्णांक rc = 0;
	काष्ठा पंचांग6000_fh *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	dev->norm = norm;
	rc = पंचांग6000_init_analog_mode(dev);

	fh->width  = dev->width;
	fh->height = dev->height;

	अगर (rc < 0)
		वापस rc;

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std, dev->norm);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा पंचांग6000_fh *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	*norm = dev->norm;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *iname[] = अणु
	[TM6000_INPUT_TV] = "Television",
	[TM6000_INPUT_COMPOSITE1] = "Composite 1",
	[TM6000_INPUT_COMPOSITE2] = "Composite 2",
	[TM6000_INPUT_SVIDEO] = "S-Video",
पूर्ण;

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *i)
अणु
	काष्ठा पंचांग6000_fh   *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;
	अचिन्हित पूर्णांक n;

	n = i->index;
	अगर (n >= 3)
		वापस -EINVAL;

	अगर (!dev->vinput[n].type)
		वापस -EINVAL;

	i->index = n;

	अगर (dev->vinput[n].type == TM6000_INPUT_TV)
		i->type = V4L2_INPUT_TYPE_TUNER;
	अन्यथा
		i->type = V4L2_INPUT_TYPE_CAMERA;

	strscpy(i->name, iname[dev->vinput[n].type], माप(i->name));

	i->std = TM6000_STD;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा पंचांग6000_fh   *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	*i = dev->input;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा पंचांग6000_fh   *fh = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;
	पूर्णांक rc = 0;

	अगर (i >= 3)
		वापस -EINVAL;
	अगर (!dev->vinput[i].type)
		वापस -EINVAL;

	dev->input = i;

	rc = vidioc_s_std(file, priv, dev->norm);

	वापस rc;
पूर्ण

/* --- controls ---------------------------------------------- */

अटल पूर्णांक पंचांग6000_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा पंचांग6000_core *dev = container_of(ctrl->handler, काष्ठा पंचांग6000_core, ctrl_handler);
	u8  val = ctrl->val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_CONTRAST:
		पंचांग6000_set_reg(dev, TM6010_REQ07_R08_LUMA_CONTRAST_ADJ, val);
		वापस 0;
	हाल V4L2_CID_BRIGHTNESS:
		पंचांग6000_set_reg(dev, TM6010_REQ07_R09_LUMA_BRIGHTNESS_ADJ, val);
		वापस 0;
	हाल V4L2_CID_SATURATION:
		पंचांग6000_set_reg(dev, TM6010_REQ07_R0A_CHROMA_SATURATION_ADJ, val);
		वापस 0;
	हाल V4L2_CID_HUE:
		पंचांग6000_set_reg(dev, TM6010_REQ07_R0B_CHROMA_HUE_PHASE_ADJ, val);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops पंचांग6000_ctrl_ops = अणु
	.s_ctrl = पंचांग6000_s_ctrl,
पूर्ण;

अटल पूर्णांक पंचांग6000_radio_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा पंचांग6000_core *dev = container_of(ctrl->handler,
			काष्ठा पंचांग6000_core, radio_ctrl_handler);
	u8  val = ctrl->val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		dev->ctl_mute = val;
		पंचांग6000_tvaudio_set_mute(dev, val);
		वापस 0;
	हाल V4L2_CID_AUDIO_VOLUME:
		dev->ctl_volume = val;
		पंचांग6000_set_volume(dev, val);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops पंचांग6000_radio_ctrl_ops = अणु
	.s_ctrl = पंचांग6000_radio_s_ctrl,
पूर्ण;

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *t)
अणु
	काष्ठा पंचांग6000_fh   *fh  = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (UNSET == dev->tuner_type)
		वापस -ENOTTY;
	अगर (0 != t->index)
		वापस -EINVAL;

	strscpy(t->name, "Television", माप(t->name));
	t->type       = V4L2_TUNER_ANALOG_TV;
	t->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO;
	t->rangehigh  = 0xffffffffUL;
	t->rxsubchans = V4L2_TUNER_SUB_STEREO;

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_tuner, t);

	t->audmode = dev->amode;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा पंचांग6000_fh   *fh  = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (UNSET == dev->tuner_type)
		वापस -ENOTTY;
	अगर (0 != t->index)
		वापस -EINVAL;

	अगर (t->audmode > V4L2_TUNER_MODE_STEREO)
		dev->amode = V4L2_TUNER_MODE_STEREO;
	अन्यथा
		dev->amode = t->audmode;
	dprपूर्णांकk(dev, 3, "audio mode: %x\n", t->audmode);

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_tuner, t);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा पंचांग6000_fh   *fh  = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (UNSET == dev->tuner_type)
		वापस -ENOTTY;
	अगर (f->tuner)
		वापस -EINVAL;

	f->frequency = dev->freq;

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_frequency, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा पंचांग6000_fh   *fh  = priv;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (UNSET == dev->tuner_type)
		वापस -ENOTTY;
	अगर (f->tuner != 0)
		वापस -EINVAL;

	dev->freq = f->frequency;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, f);

	वापस 0;
पूर्ण

अटल पूर्णांक radio_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *t)
अणु
	काष्ठा पंचांग6000_fh *fh = file->निजी_data;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (0 != t->index)
		वापस -EINVAL;

	स_रखो(t, 0, माप(*t));
	strscpy(t->name, "Radio", माप(t->name));
	t->type = V4L2_TUNER_RADIO;
	t->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	t->rxsubchans = V4L2_TUNER_SUB_STEREO;
	t->audmode = V4L2_TUNER_MODE_STEREO;

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_tuner, t);

	वापस 0;
पूर्ण

अटल पूर्णांक radio_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा पंचांग6000_fh *fh = file->निजी_data;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (0 != t->index)
		वापस -EINVAL;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_tuner, t);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------
	File operations क्रम the device
   ------------------------------------------------------------------*/

अटल पूर्णांक __पंचांग6000_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा पंचांग6000_core *dev = video_drvdata(file);
	काष्ठा पंचांग6000_fh *fh;
	क्रमागत v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	पूर्णांक rc;
	पूर्णांक radio = 0;

	dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "tm6000: open called (dev=%s)\n",
		video_device_node_name(vdev));

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		अवरोध;
	हाल VFL_TYPE_VBI:
		type = V4L2_BUF_TYPE_VBI_CAPTURE;
		अवरोध;
	हाल VFL_TYPE_RADIO:
		radio = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* If more than one user, mutex should be added */
	dev->users++;

	dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "open dev=%s type=%s users=%d\n",
		video_device_node_name(vdev), v4l2_type_names[type],
		dev->users);

	/* allocate + initialize per filehandle data */
	fh = kzalloc(माप(*fh), GFP_KERNEL);
	अगर (शून्य == fh) अणु
		dev->users--;
		वापस -ENOMEM;
	पूर्ण

	v4l2_fh_init(&fh->fh, vdev);
	file->निजी_data = fh;
	fh->dev      = dev;
	fh->radio    = radio;
	dev->radio   = radio;
	fh->type     = type;
	dev->fourcc  = क्रमmat[0].fourcc;

	fh->fmt      = क्रमmat_by_fourcc(dev->fourcc);

	पंचांग6000_get_std_res(dev);

	fh->width = dev->width;
	fh->height = dev->height;

	dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "Open: fh=%p, dev=%p, dev->vidq=%p\n",
		fh, dev, &dev->vidq);
	dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "Open: list_empty queued=%d\n",
		list_empty(&dev->vidq.queued));
	dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "Open: list_empty active=%d\n",
		list_empty(&dev->vidq.active));

	/* initialize hardware on analog mode */
	rc = पंचांग6000_init_analog_mode(dev);
	अगर (rc < 0) अणु
		v4l2_fh_निकास(&fh->fh);
		kमुक्त(fh);
		वापस rc;
	पूर्ण

	dev->mode = TM6000_MODE_ANALOG;

	अगर (!fh->radio) अणु
		videobuf_queue_vदो_स्मृति_init(&fh->vb_vidq, &पंचांग6000_video_qops,
				शून्य, &dev->slock,
				fh->type,
				V4L2_FIELD_INTERLACED,
				माप(काष्ठा पंचांग6000_buffer), fh, &dev->lock);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "video_open: setting radio device\n");
		पंचांग6000_set_audio_rinput(dev);
		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_radio);
		पंचांग6000_prepare_isoc(dev);
		पंचांग6000_start_thपढ़ो(dev);
	पूर्ण
	v4l2_fh_add(&fh->fh);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग6000_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक res;

	mutex_lock(vdev->lock);
	res = __पंचांग6000_खोलो(file);
	mutex_unlock(vdev->lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार
पंचांग6000_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा पंचांग6000_fh *fh = file->निजी_data;
	काष्ठा पंचांग6000_core *dev = fh->dev;

	अगर (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		पूर्णांक res;

		अगर (!res_get(fh->dev, fh, true))
			वापस -EBUSY;

		अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
			वापस -ERESTARTSYS;
		res = videobuf_पढ़ो_stream(&fh->vb_vidq, data, count, pos, 0,
					file->f_flags & O_NONBLOCK);
		mutex_unlock(&dev->lock);
		वापस res;
	पूर्ण
	वापस 0;
पूर्ण

अटल __poll_t
__पंचांग6000_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा पंचांग6000_fh        *fh = file->निजी_data;
	काष्ठा पंचांग6000_buffer    *buf;
	__poll_t res = 0;

	अगर (v4l2_event_pending(&fh->fh))
		res = EPOLLPRI;
	अन्यथा अगर (req_events & EPOLLPRI)
		poll_रुको(file, &fh->fh.रुको, रुको);
	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != fh->type)
		वापस res | EPOLLERR;

	अगर (!!is_res_streaming(fh->dev, fh))
		वापस res | EPOLLERR;

	अगर (!is_res_पढ़ो(fh->dev, fh)) अणु
		/* streaming capture */
		अगर (list_empty(&fh->vb_vidq.stream))
			वापस res | EPOLLERR;
		buf = list_entry(fh->vb_vidq.stream.next, काष्ठा पंचांग6000_buffer, vb.stream);
		poll_रुको(file, &buf->vb.करोne, रुको);
		अगर (buf->vb.state == VIDEOBUF_DONE ||
		    buf->vb.state == VIDEOBUF_ERROR)
			वापस res | EPOLLIN | EPOLLRDNORM;
	पूर्ण अन्यथा अगर (req_events & (EPOLLIN | EPOLLRDNORM)) अणु
		/* पढ़ो() capture */
		वापस res | videobuf_poll_stream(file, &fh->vb_vidq, रुको);
	पूर्ण
	वापस res;
पूर्ण

अटल __poll_t पंचांग6000_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा पंचांग6000_fh *fh = file->निजी_data;
	काष्ठा पंचांग6000_core *dev = fh->dev;
	__poll_t res;

	mutex_lock(&dev->lock);
	res = __पंचांग6000_poll(file, रुको);
	mutex_unlock(&dev->lock);
	वापस res;
पूर्ण

अटल पूर्णांक पंचांग6000_release(काष्ठा file *file)
अणु
	काष्ठा पंचांग6000_fh         *fh = file->निजी_data;
	काष्ठा पंचांग6000_core      *dev = fh->dev;
	काष्ठा video_device    *vdev = video_devdata(file);

	dprपूर्णांकk(dev, V4L2_DEBUG_OPEN, "tm6000: close called (dev=%s, users=%d)\n",
		video_device_node_name(vdev), dev->users);

	mutex_lock(&dev->lock);
	dev->users--;

	res_मुक्त(dev, fh);

	अगर (!dev->users) अणु
		पंचांग6000_uninit_isoc(dev);

		/* Stop पूर्णांकerrupt USB pipe */
		पंचांग6000_ir_पूर्णांक_stop(dev);

		usb_reset_configuration(dev->udev);

		अगर (dev->पूर्णांक_in.endp)
			usb_set_पूर्णांकerface(dev->udev,
					dev->isoc_in.bInterfaceNumber, 2);
		अन्यथा
			usb_set_पूर्णांकerface(dev->udev,
					dev->isoc_in.bInterfaceNumber, 0);

		/* Start पूर्णांकerrupt USB pipe */
		पंचांग6000_ir_पूर्णांक_start(dev);

		अगर (!fh->radio)
			videobuf_mmap_मुक्त(&fh->vb_vidq);
	पूर्ण
	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	kमुक्त(fh);
	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग6000_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा * vma)
अणु
	काष्ठा पंचांग6000_fh *fh = file->निजी_data;
	काष्ठा पंचांग6000_core *dev = fh->dev;
	पूर्णांक res;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;
	res = videobuf_mmap_mapper(&fh->vb_vidq, vma);
	mutex_unlock(&dev->lock);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations पंचांग6000_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = पंचांग6000_खोलो,
	.release = पंचांग6000_release,
	.unlocked_ioctl = video_ioctl2, /* V4L2 ioctl handler */
	.पढ़ो = पंचांग6000_पढ़ो,
	.poll = पंचांग6000_poll,
	.mmap = पंचांग6000_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap          = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_s_std             = vidioc_s_std,
	.vidioc_g_std             = vidioc_g_std,
	.vidioc_क्रमागत_input        = vidioc_क्रमागत_input,
	.vidioc_g_input           = vidioc_g_input,
	.vidioc_s_input           = vidioc_s_input,
	.vidioc_g_tuner           = vidioc_g_tuner,
	.vidioc_s_tuner           = vidioc_s_tuner,
	.vidioc_g_frequency       = vidioc_g_frequency,
	.vidioc_s_frequency       = vidioc_s_frequency,
	.vidioc_streamon          = vidioc_streamon,
	.vidioc_streamoff         = vidioc_streamoff,
	.vidioc_reqbufs           = vidioc_reqbufs,
	.vidioc_querybuf          = vidioc_querybuf,
	.vidioc_qbuf              = vidioc_qbuf,
	.vidioc_dqbuf             = vidioc_dqbuf,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device पंचांग6000_ढाँचा = अणु
	.name		= "tm6000",
	.fops           = &पंचांग6000_fops,
	.ioctl_ops      = &video_ioctl_ops,
	.release	= video_device_release_empty,
	.tvnorms        = TM6000_STD,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations radio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= पंचांग6000_खोलो,
	.poll		= v4l2_ctrl_poll,
	.release	= पंचांग6000_release,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,
	.vidioc_g_tuner		= radio_g_tuner,
	.vidioc_s_tuner		= radio_s_tuner,
	.vidioc_g_frequency	= vidioc_g_frequency,
	.vidioc_s_frequency	= vidioc_s_frequency,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device पंचांग6000_radio_ढाँचा = अणु
	.name			= "tm6000",
	.fops			= &radio_fops,
	.ioctl_ops		= &radio_ioctl_ops,
पूर्ण;

/* -----------------------------------------------------------------
 *	Initialization and module stuff
 * ------------------------------------------------------------------
 */

अटल व्योम vdev_init(काष्ठा पंचांग6000_core *dev,
		काष्ठा video_device *vfd,
		स्थिर काष्ठा video_device
		*ढाँचा, स्थिर अक्षर *type_name)
अणु
	*vfd = *ढाँचा;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->release = video_device_release_empty;
	vfd->lock = &dev->lock;

	snम_लिखो(vfd->name, माप(vfd->name), "%s %s", dev->name, type_name);

	video_set_drvdata(vfd, dev);
पूर्ण

पूर्णांक पंचांग6000_v4l2_रेजिस्टर(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक ret = 0;

	v4l2_ctrl_handler_init(&dev->ctrl_handler, 6);
	v4l2_ctrl_handler_init(&dev->radio_ctrl_handler, 2);
	v4l2_ctrl_new_std(&dev->radio_ctrl_handler, &पंचांग6000_radio_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&dev->radio_ctrl_handler, &पंचांग6000_radio_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, -15, 15, 1, 0);
	v4l2_ctrl_new_std(&dev->ctrl_handler, &पंचांग6000_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 54);
	v4l2_ctrl_new_std(&dev->ctrl_handler, &पंचांग6000_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 119);
	v4l2_ctrl_new_std(&dev->ctrl_handler, &पंचांग6000_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 112);
	v4l2_ctrl_new_std(&dev->ctrl_handler, &पंचांग6000_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_add_handler(&dev->ctrl_handler,
			&dev->radio_ctrl_handler, शून्य, false);

	अगर (dev->radio_ctrl_handler.error)
		ret = dev->radio_ctrl_handler.error;
	अगर (!ret && dev->ctrl_handler.error)
		ret = dev->ctrl_handler.error;
	अगर (ret)
		जाओ मुक्त_ctrl;

	vdev_init(dev, &dev->vfd, &पंचांग6000_ढाँचा, "video");

	dev->vfd.ctrl_handler = &dev->ctrl_handler;
	dev->vfd.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
			       V4L2_CAP_READWRITE;
	अगर (dev->tuner_type != TUNER_ABSENT)
		dev->vfd.device_caps |= V4L2_CAP_TUNER;

	/* init video dma queues */
	INIT_LIST_HEAD(&dev->vidq.active);
	INIT_LIST_HEAD(&dev->vidq.queued);

	ret = video_रेजिस्टर_device(&dev->vfd, VFL_TYPE_VIDEO, video_nr);

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_INFO "%s: can't register video device\n",
		       dev->name);
		जाओ मुक्त_ctrl;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: registered device %s\n",
	       dev->name, video_device_node_name(&dev->vfd));

	अगर (dev->caps.has_radio) अणु
		vdev_init(dev, &dev->radio_dev, &पंचांग6000_radio_ढाँचा,
							   "radio");
		dev->radio_dev.ctrl_handler = &dev->radio_ctrl_handler;
		dev->radio_dev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		ret = video_रेजिस्टर_device(&dev->radio_dev, VFL_TYPE_RADIO,
					    radio_nr);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_INFO "%s: can't register radio device\n",
			       dev->name);
			जाओ unreg_video;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s: registered device %s\n",
		       dev->name, video_device_node_name(&dev->radio_dev));
	पूर्ण

	prपूर्णांकk(KERN_INFO "Trident TVMaster TM5600/TM6000/TM6010 USB2 board (Load status: %d)\n", ret);
	वापस ret;

unreg_video:
	video_unरेजिस्टर_device(&dev->vfd);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_ctrl_handler_मुक्त(&dev->radio_ctrl_handler);
	वापस ret;
पूर्ण

पूर्णांक पंचांग6000_v4l2_unरेजिस्टर(काष्ठा पंचांग6000_core *dev)
अणु
	video_unरेजिस्टर_device(&dev->vfd);

	/* अगर URB buffers are still allocated मुक्त them now */
	पंचांग6000_मुक्त_urb_buffers(dev);

	video_unरेजिस्टर_device(&dev->radio_dev);
	वापस 0;
पूर्ण

पूर्णांक पंचांग6000_v4l2_निकास(व्योम)
अणु
	वापस 0;
पूर्ण

module_param(video_nr, पूर्णांक, 0);
MODULE_PARM_DESC(video_nr, "Allow changing video device number");

module_param_named(debug, पंचांग6000_debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "activates debug info");

module_param(vid_limit, पूर्णांक, 0644);
MODULE_PARM_DESC(vid_limit, "capture memory limit in megabytes");

module_param(keep_urb, bool, 0);
MODULE_PARM_DESC(keep_urb, "Keep urb buffers allocated even when the device is closed by the user");
