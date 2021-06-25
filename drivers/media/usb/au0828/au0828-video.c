<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Auvitek AU0828 USB Bridge (Analog video support)
 *
 * Copyright (C) 2009 Devin Heiपंचांगueller <dheiपंचांगueller@linuxtv.org>
 * Copyright (C) 2005-2008 Auvitek International, Ltd.
 */

/* Developer Notes:
 *
 * The hardware scaler supported is unimplemented
 * AC97 audio support is unimplemented (only i2s audio mode)
 *
 */

#समावेश "au0828.h"
#समावेश "au8522.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/tuner.h>
#समावेश "au0828-reg.h"

अटल DEFINE_MUTEX(au0828_sysfs_lock);

/* ------------------------------------------------------------------
	Videobuf operations
   ------------------------------------------------------------------*/

अटल अचिन्हित पूर्णांक isoc_debug;
module_param(isoc_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(isoc_debug, "enable debug messages [isoc transfers]");

#घोषणा au0828_isocdbg(fmt, arg...) \
करो अणु\
	अगर (isoc_debug) अणु \
		pr_info("au0828 %s :"fmt, \
		       __func__ , ##arg);	   \
	पूर्ण \
  पूर्ण जबतक (0)

अटल अंतरभूत व्योम i2c_gate_ctrl(काष्ठा au0828_dev *dev, पूर्णांक val)
अणु
	अगर (dev->dvb.frontend && dev->dvb.frontend->ops.analog_ops.i2c_gate_ctrl)
		dev->dvb.frontend->ops.analog_ops.i2c_gate_ctrl(dev->dvb.frontend, val);
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा au0828_dev *dev,
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
		au0828_isocdbg("URB status %d [%s].\n",	status, errmsg);
	पूर्ण अन्यथा अणु
		au0828_isocdbg("URB packet %d, status %d [%s].\n",
			       packet, status, errmsg);
	पूर्ण
पूर्ण

अटल पूर्णांक check_dev(काष्ठा au0828_dev *dev)
अणु
	अगर (test_bit(DEV_DISCONNECTED, &dev->dev_state)) अणु
		pr_info("v4l2 ioctl: device not present\n");
		वापस -ENODEV;
	पूर्ण

	अगर (test_bit(DEV_MISCONFIGURED, &dev->dev_state)) अणु
		pr_info("v4l2 ioctl: device is misconfigured; close and open it again\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * IRQ callback, called by URB callback
 */
अटल व्योम au0828_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा au0828_dmaqueue  *dma_q = urb->context;
	काष्ठा au0828_dev *dev = container_of(dma_q, काष्ठा au0828_dev, vidq);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0:             /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		au0828_isocdbg("au0828_irq_callback called: status kill\n");
		वापस;
	शेष:            /* unknown error */
		au0828_isocdbg("urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	/* Copy data from URB */
	spin_lock_irqsave(&dev->slock, flags);
	dev->isoc_ctl.isoc_copy(dev, urb);
	spin_unlock_irqrestore(&dev->slock, flags);

	/* Reset urb buffers */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	पूर्ण
	urb->status = 0;

	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (urb->status) अणु
		au0828_isocdbg("urb resubmit failed (error=%i)\n",
			       urb->status);
	पूर्ण
	dev->stream_state = STREAM_ON;
पूर्ण

/*
 * Stop and Deallocate URBs
 */
अटल व्योम au0828_uninit_isoc(काष्ठा au0828_dev *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	au0828_isocdbg("au0828: called au0828_uninit_isoc\n");

	dev->isoc_ctl.nfields = -1;
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		urb = dev->isoc_ctl.urb[i];
		अगर (urb) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(urb);
			अन्यथा
				usb_unlink_urb(urb);

			अगर (dev->isoc_ctl.transfer_buffer[i]) अणु
				usb_मुक्त_coherent(dev->usbdev,
					urb->transfer_buffer_length,
					dev->isoc_ctl.transfer_buffer[i],
					urb->transfer_dma);
			पूर्ण
			usb_मुक्त_urb(urb);
			dev->isoc_ctl.urb[i] = शून्य;
		पूर्ण
		dev->isoc_ctl.transfer_buffer[i] = शून्य;
	पूर्ण

	kमुक्त(dev->isoc_ctl.urb);
	kमुक्त(dev->isoc_ctl.transfer_buffer);

	dev->isoc_ctl.urb = शून्य;
	dev->isoc_ctl.transfer_buffer = शून्य;
	dev->isoc_ctl.num_bufs = 0;

	dev->stream_state = STREAM_OFF;
पूर्ण

/*
 * Allocate URBs and start IRQ
 */
अटल पूर्णांक au0828_init_isoc(काष्ठा au0828_dev *dev, पूर्णांक max_packets,
			    पूर्णांक num_bufs, पूर्णांक max_pkt_size,
			    पूर्णांक (*isoc_copy) (काष्ठा au0828_dev *dev, काष्ठा urb *urb))
अणु
	काष्ठा au0828_dmaqueue *dma_q = &dev->vidq;
	पूर्णांक i;
	पूर्णांक sb_size, pipe;
	काष्ठा urb *urb;
	पूर्णांक j, k;
	पूर्णांक rc;

	au0828_isocdbg("au0828: called au0828_prepare_isoc\n");

	dev->isoc_ctl.isoc_copy = isoc_copy;
	dev->isoc_ctl.num_bufs = num_bufs;

	dev->isoc_ctl.urb = kसुस्मृति(num_bufs, माप(व्योम *),  GFP_KERNEL);
	अगर (!dev->isoc_ctl.urb) अणु
		au0828_isocdbg("cannot alloc memory for usb buffers\n");
		वापस -ENOMEM;
	पूर्ण

	dev->isoc_ctl.transfer_buffer = kसुस्मृति(num_bufs, माप(व्योम *),
						GFP_KERNEL);
	अगर (!dev->isoc_ctl.transfer_buffer) अणु
		au0828_isocdbg("cannot allocate memory for usb transfer\n");
		kमुक्त(dev->isoc_ctl.urb);
		वापस -ENOMEM;
	पूर्ण

	dev->isoc_ctl.max_pkt_size = max_pkt_size;
	dev->isoc_ctl.buf = शून्य;

	sb_size = max_packets * dev->isoc_ctl.max_pkt_size;

	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		urb = usb_alloc_urb(max_packets, GFP_KERNEL);
		अगर (!urb) अणु
			au0828_isocdbg("cannot allocate URB\n");
			au0828_uninit_isoc(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->isoc_ctl.urb[i] = urb;

		dev->isoc_ctl.transfer_buffer[i] = usb_alloc_coherent(dev->usbdev,
			sb_size, GFP_KERNEL, &urb->transfer_dma);
		अगर (!dev->isoc_ctl.transfer_buffer[i]) अणु
			au0828_isocdbg("cannot allocate transfer buffer\n");
			au0828_uninit_isoc(dev);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(dev->isoc_ctl.transfer_buffer[i], 0, sb_size);

		pipe = usb_rcvisocpipe(dev->usbdev,
				       dev->isoc_in_endpoपूर्णांकaddr);

		usb_fill_पूर्णांक_urb(urb, dev->usbdev, pipe,
				 dev->isoc_ctl.transfer_buffer[i], sb_size,
				 au0828_irq_callback, dma_q, 1);

		urb->number_of_packets = max_packets;
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;

		k = 0;
		क्रम (j = 0; j < max_packets; j++) अणु
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length =
						dev->isoc_ctl.max_pkt_size;
			k += dev->isoc_ctl.max_pkt_size;
		पूर्ण
	पूर्ण

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		rc = usb_submit_urb(dev->isoc_ctl.urb[i], GFP_ATOMIC);
		अगर (rc) अणु
			au0828_isocdbg("submit of urb %i failed (error=%i)\n",
				       i, rc);
			au0828_uninit_isoc(dev);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Announces that a buffer were filled and request the next
 */
अटल अंतरभूत व्योम buffer_filled(काष्ठा au0828_dev *dev,
				 काष्ठा au0828_dmaqueue *dma_q,
				 काष्ठा au0828_buffer *buf)
अणु
	काष्ठा vb2_v4l2_buffer *vb = &buf->vb;
	काष्ठा vb2_queue *q = vb->vb2_buf.vb2_queue;

	/* Advice that buffer was filled */
	au0828_isocdbg("[%p/%d] wakeup\n", buf, buf->top_field);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		vb->sequence = dev->frame_count++;
	अन्यथा
		vb->sequence = dev->vbi_frame_count++;

	vb->field = V4L2_FIELD_INTERLACED;
	vb->vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&vb->vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

/*
 * Identअगरy the buffer header type and properly handles
 */
अटल व्योम au0828_copy_video(काष्ठा au0828_dev *dev,
			      काष्ठा au0828_dmaqueue  *dma_q,
			      काष्ठा au0828_buffer *buf,
			      अचिन्हित अक्षर *p,
			      अचिन्हित अक्षर *outp, अचिन्हित दीर्घ len)
अणु
	व्योम *fieldstart, *startग_लिखो, *startपढ़ो;
	पूर्णांक  linesकरोne, currlineकरोne, offset, lencopy, reमुख्य;
	पूर्णांक bytesperline = dev->width << 1; /* Assumes 16-bit depth @@@@ */

	अगर (len == 0)
		वापस;

	अगर (dma_q->pos + len > buf->length)
		len = buf->length - dma_q->pos;

	startपढ़ो = p;
	reमुख्य = len;

	/* Interlaces frame */
	अगर (buf->top_field)
		fieldstart = outp;
	अन्यथा
		fieldstart = outp + bytesperline;

	linesकरोne = dma_q->pos / bytesperline;
	currlineकरोne = dma_q->pos % bytesperline;
	offset = linesकरोne * bytesperline * 2 + currlineकरोne;
	startग_लिखो = fieldstart + offset;
	lencopy = bytesperline - currlineकरोne;
	lencopy = lencopy > reमुख्य ? reमुख्य : lencopy;

	अगर ((अक्षर *)startग_लिखो + lencopy > (अक्षर *)outp + buf->length) अणु
		au0828_isocdbg("Overflow of %zi bytes past buffer end (1)\n",
			       ((अक्षर *)startग_लिखो + lencopy) -
			       ((अक्षर *)outp + buf->length));
		reमुख्य = (अक्षर *)outp + buf->length - (अक्षर *)startग_लिखो;
		lencopy = reमुख्य;
	पूर्ण
	अगर (lencopy <= 0)
		वापस;
	स_नकल(startग_लिखो, startपढ़ो, lencopy);

	reमुख्य -= lencopy;

	जबतक (reमुख्य > 0) अणु
		startग_लिखो += lencopy + bytesperline;
		startपढ़ो += lencopy;
		अगर (bytesperline > reमुख्य)
			lencopy = reमुख्य;
		अन्यथा
			lencopy = bytesperline;

		अगर ((अक्षर *)startग_लिखो + lencopy > (अक्षर *)outp +
		    buf->length) अणु
			au0828_isocdbg("Overflow %zi bytes past buf end (2)\n",
				       ((अक्षर *)startग_लिखो + lencopy) -
				       ((अक्षर *)outp + buf->length));
			lencopy = reमुख्य = (अक्षर *)outp + buf->length -
					   (अक्षर *)startग_लिखो;
		पूर्ण
		अगर (lencopy <= 0)
			अवरोध;

		स_नकल(startग_लिखो, startपढ़ो, lencopy);

		reमुख्य -= lencopy;
	पूर्ण

	अगर (offset > 1440) अणु
		/* We have enough data to check क्रम greenscreen */
		अगर (outp[0] < 0x60 && outp[1440] < 0x60)
			dev->greenscreen_detected = 1;
	पूर्ण

	dma_q->pos += len;
पूर्ण

/*
 * video-buf generic routine to get the next available buffer
 */
अटल अंतरभूत व्योम get_next_buf(काष्ठा au0828_dmaqueue *dma_q,
				काष्ठा au0828_buffer **buf)
अणु
	काष्ठा au0828_dev *dev = container_of(dma_q, काष्ठा au0828_dev, vidq);

	अगर (list_empty(&dma_q->active)) अणु
		au0828_isocdbg("No active queue to serve\n");
		dev->isoc_ctl.buf = शून्य;
		*buf = शून्य;
		वापस;
	पूर्ण

	/* Get the next buffer */
	*buf = list_entry(dma_q->active.next, काष्ठा au0828_buffer, list);
	/* Cleans up buffer - Useful क्रम testing क्रम frame/URB loss */
	list_del(&(*buf)->list);
	dma_q->pos = 0;
	(*buf)->vb_buf = (*buf)->mem;
	dev->isoc_ctl.buf = *buf;

	वापस;
पूर्ण

अटल व्योम au0828_copy_vbi(काष्ठा au0828_dev *dev,
			      काष्ठा au0828_dmaqueue  *dma_q,
			      काष्ठा au0828_buffer *buf,
			      अचिन्हित अक्षर *p,
			      अचिन्हित अक्षर *outp, अचिन्हित दीर्घ len)
अणु
	अचिन्हित अक्षर *startग_लिखो, *startपढ़ो;
	पूर्णांक bytesperline;
	पूर्णांक i, j = 0;

	अगर (dev == शून्य) अणु
		au0828_isocdbg("dev is null\n");
		वापस;
	पूर्ण

	अगर (dma_q == शून्य) अणु
		au0828_isocdbg("dma_q is null\n");
		वापस;
	पूर्ण
	अगर (buf == शून्य)
		वापस;
	अगर (p == शून्य) अणु
		au0828_isocdbg("p is null\n");
		वापस;
	पूर्ण
	अगर (outp == शून्य) अणु
		au0828_isocdbg("outp is null\n");
		वापस;
	पूर्ण

	bytesperline = dev->vbi_width;

	अगर (dma_q->pos + len > buf->length)
		len = buf->length - dma_q->pos;

	startपढ़ो = p;
	startग_लिखो = outp + (dma_q->pos / 2);

	/* Make sure the bottom field populates the second half of the frame */
	अगर (buf->top_field == 0)
		startग_लिखो += bytesperline * dev->vbi_height;

	क्रम (i = 0; i < len; i += 2)
		startग_लिखो[j++] = startपढ़ो[i+1];

	dma_q->pos += len;
पूर्ण


/*
 * video-buf generic routine to get the next available VBI buffer
 */
अटल अंतरभूत व्योम vbi_get_next_buf(काष्ठा au0828_dmaqueue *dma_q,
				    काष्ठा au0828_buffer **buf)
अणु
	काष्ठा au0828_dev *dev = container_of(dma_q, काष्ठा au0828_dev, vbiq);

	अगर (list_empty(&dma_q->active)) अणु
		au0828_isocdbg("No active queue to serve\n");
		dev->isoc_ctl.vbi_buf = शून्य;
		*buf = शून्य;
		वापस;
	पूर्ण

	/* Get the next buffer */
	*buf = list_entry(dma_q->active.next, काष्ठा au0828_buffer, list);
	/* Cleans up buffer - Useful क्रम testing क्रम frame/URB loss */
	list_del(&(*buf)->list);
	dma_q->pos = 0;
	(*buf)->vb_buf = (*buf)->mem;
	dev->isoc_ctl.vbi_buf = *buf;
	वापस;
पूर्ण

/*
 * Controls the isoc copy of each urb packet
 */
अटल अंतरभूत पूर्णांक au0828_isoc_copy(काष्ठा au0828_dev *dev, काष्ठा urb *urb)
अणु
	काष्ठा au0828_buffer    *buf;
	काष्ठा au0828_buffer    *vbi_buf;
	काष्ठा au0828_dmaqueue  *dma_q = urb->context;
	काष्ठा au0828_dmaqueue  *vbi_dma_q = &dev->vbiq;
	अचिन्हित अक्षर *outp = शून्य;
	अचिन्हित अक्षर *vbioutp = शून्य;
	पूर्णांक i, len = 0, rc = 1;
	अचिन्हित अक्षर *p;
	अचिन्हित अक्षर fbyte;
	अचिन्हित पूर्णांक vbi_field_size;
	अचिन्हित पूर्णांक reमुख्य, lencopy;

	अगर (!dev)
		वापस 0;

	अगर (test_bit(DEV_DISCONNECTED, &dev->dev_state) ||
	    test_bit(DEV_MISCONFIGURED, &dev->dev_state))
		वापस 0;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		अगर (urb->status == -ENOENT)
			वापस 0;
	पूर्ण

	buf = dev->isoc_ctl.buf;
	अगर (buf != शून्य)
		outp = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	vbi_buf = dev->isoc_ctl.vbi_buf;
	अगर (vbi_buf != शून्य)
		vbioutp = vb2_plane_vaddr(&vbi_buf->vb.vb2_buf, 0);

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		पूर्णांक status = urb->iso_frame_desc[i].status;

		अगर (status < 0) अणु
			prपूर्णांक_err_status(dev, i, status);
			अगर (urb->iso_frame_desc[i].status != -EPROTO)
				जारी;
		पूर्ण

		अगर (urb->iso_frame_desc[i].actual_length <= 0)
			जारी;

		अगर (urb->iso_frame_desc[i].actual_length >
						dev->max_pkt_size) अणु
			au0828_isocdbg("packet bigger than packet size");
			जारी;
		पूर्ण

		p = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		fbyte = p[0];
		len = urb->iso_frame_desc[i].actual_length - 4;
		p += 4;

		अगर (fbyte & 0x80) अणु
			len -= 4;
			p += 4;
			au0828_isocdbg("Video frame %s\n",
				       (fbyte & 0x40) ? "odd" : "even");
			अगर (fbyte & 0x40) अणु
				/* VBI */
				अगर (vbi_buf != शून्य)
					buffer_filled(dev, vbi_dma_q, vbi_buf);
				vbi_get_next_buf(vbi_dma_q, &vbi_buf);
				अगर (vbi_buf == शून्य)
					vbioutp = शून्य;
				अन्यथा
					vbioutp = vb2_plane_vaddr(
						&vbi_buf->vb.vb2_buf, 0);

				/* Video */
				अगर (buf != शून्य)
					buffer_filled(dev, dma_q, buf);
				get_next_buf(dma_q, &buf);
				अगर (buf == शून्य)
					outp = शून्य;
				अन्यथा
					outp = vb2_plane_vaddr(
						&buf->vb.vb2_buf, 0);

				/* As दीर्घ as isoc traffic is arriving, keep
				   resetting the समयr */
				अगर (dev->vid_समयout_running)
					mod_समयr(&dev->vid_समयout,
						  jअगरfies + (HZ / 10));
				अगर (dev->vbi_समयout_running)
					mod_समयr(&dev->vbi_समयout,
						  jअगरfies + (HZ / 10));
			पूर्ण

			अगर (buf != शून्य) अणु
				अगर (fbyte & 0x40)
					buf->top_field = 1;
				अन्यथा
					buf->top_field = 0;
			पूर्ण

			अगर (vbi_buf != शून्य) अणु
				अगर (fbyte & 0x40)
					vbi_buf->top_field = 1;
				अन्यथा
					vbi_buf->top_field = 0;
			पूर्ण

			dev->vbi_पढ़ो = 0;
			vbi_dma_q->pos = 0;
			dma_q->pos = 0;
		पूर्ण

		vbi_field_size = dev->vbi_width * dev->vbi_height * 2;
		अगर (dev->vbi_पढ़ो < vbi_field_size) अणु
			reमुख्य  = vbi_field_size - dev->vbi_पढ़ो;
			अगर (len < reमुख्य)
				lencopy = len;
			अन्यथा
				lencopy = reमुख्य;

			अगर (vbi_buf != शून्य)
				au0828_copy_vbi(dev, vbi_dma_q, vbi_buf, p,
						vbioutp, len);

			len -= lencopy;
			p += lencopy;
			dev->vbi_पढ़ो += lencopy;
		पूर्ण

		अगर (dev->vbi_पढ़ो >= vbi_field_size && buf != शून्य)
			au0828_copy_video(dev, dma_q, buf, p, outp, len);
	पूर्ण
	वापस rc;
पूर्ण

व्योम au0828_usb_v4l2_media_release(काष्ठा au0828_dev *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक i;

	क्रम (i = 0; i < AU0828_MAX_INPUT; i++) अणु
		अगर (AUVI_INPUT(i).type == AU0828_VMUX_UNDEFINED)
			वापस;
		media_device_unरेजिस्टर_entity(&dev->input_ent[i]);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम au0828_usb_v4l2_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा au0828_dev *dev =
		container_of(v4l2_dev, काष्ठा au0828_dev, v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&dev->v4l2_ctrl_hdl);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	au0828_usb_v4l2_media_release(dev);
	au0828_usb_release(dev);
पूर्ण

पूर्णांक au0828_v4l2_device_रेजिस्टर(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				काष्ठा au0828_dev *dev)
अणु
	पूर्णांक retval;

	अगर (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		वापस 0;

	/* Create the v4l2_device */
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->v4l2_dev.mdev = dev->media_dev;
#पूर्ण_अगर
	retval = v4l2_device_रेजिस्टर(&पूर्णांकerface->dev, &dev->v4l2_dev);
	अगर (retval) अणु
		pr_err("%s() v4l2_device_register failed\n",
		       __func__);
		वापस retval;
	पूर्ण

	dev->v4l2_dev.release = au0828_usb_v4l2_release;

	/* This control handler will inherit the controls from au8522 */
	retval = v4l2_ctrl_handler_init(&dev->v4l2_ctrl_hdl, 4);
	अगर (retval) अणु
		pr_err("%s() v4l2_ctrl_handler_init failed\n",
		       __func__);
		वापस retval;
	पूर्ण
	dev->v4l2_dev.ctrl_handler = &dev->v4l2_ctrl_hdl;

	वापस 0;
पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ size = dev->height * dev->bytesperline;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक
buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा au0828_buffer *buf = container_of(vbuf,
				काष्ठा au0828_buffer, vb);
	काष्ठा au0828_dev    *dev = vb2_get_drv_priv(vb->vb2_queue);

	buf->length = dev->height * dev->bytesperline;

	अगर (vb2_plane_size(vb, 0) < buf->length) अणु
		pr_err("%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0), buf->length);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, buf->length);
	वापस 0;
पूर्ण

अटल व्योम
buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा au0828_buffer    *buf     = container_of(vbuf,
							काष्ठा au0828_buffer,
							vb);
	काष्ठा au0828_dev       *dev     = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा au0828_dmaqueue  *vidq    = &dev->vidq;
	अचिन्हित दीर्घ flags = 0;

	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);

	spin_lock_irqsave(&dev->slock, flags);
	list_add_tail(&buf->list, &vidq->active);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल पूर्णांक au0828_i2s_init(काष्ठा au0828_dev *dev)
अणु
	/* Enable i2s mode */
	au0828_ग_लिखोreg(dev, AU0828_AUDIOCTRL_50C, 0x01);
	वापस 0;
पूर्ण

/*
 * Auvitek au0828 analog stream enable
 */
अटल पूर्णांक au0828_analog_stream_enable(काष्ठा au0828_dev *d)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace;
	पूर्णांक ret, h, w;

	dprपूर्णांकk(1, "au0828_analog_stream_enable called\n");

	अगर (test_bit(DEV_DISCONNECTED, &d->dev_state))
		वापस -ENODEV;

	अगरace = usb_अगरnum_to_अगर(d->usbdev, 0);
	अगर (अगरace && अगरace->cur_altsetting->desc.bAlternateSetting != 5) अणु
		dprपूर्णांकk(1, "Changing intf#0 to alt 5\n");
		/* set au0828 पूर्णांकerface0 to AS5 here again */
		ret = usb_set_पूर्णांकerface(d->usbdev, 0, 5);
		अगर (ret < 0) अणु
			pr_info("Au0828 can't set alt setting to 5!\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	h = d->height / 2 + 2;
	w = d->width * 2;

	au0828_ग_लिखोreg(d, AU0828_SENSORCTRL_VBI_103, 0x00);
	au0828_ग_लिखोreg(d, 0x106, 0x00);
	/* set x position */
	au0828_ग_लिखोreg(d, 0x110, 0x00);
	au0828_ग_लिखोreg(d, 0x111, 0x00);
	au0828_ग_लिखोreg(d, 0x114, w & 0xff);
	au0828_ग_लिखोreg(d, 0x115, w >> 8);
	/* set y position */
	au0828_ग_लिखोreg(d, 0x112, 0x00);
	au0828_ग_लिखोreg(d, 0x113, 0x00);
	au0828_ग_लिखोreg(d, 0x116, h & 0xff);
	au0828_ग_लिखोreg(d, 0x117, h >> 8);
	au0828_ग_लिखोreg(d, AU0828_SENSORCTRL_100, 0xb3);

	वापस 0;
पूर्ण

अटल पूर्णांक au0828_analog_stream_disable(काष्ठा au0828_dev *d)
अणु
	dprपूर्णांकk(1, "au0828_analog_stream_disable called\n");
	au0828_ग_लिखोreg(d, AU0828_SENSORCTRL_100, 0x0);
	वापस 0;
पूर्ण

अटल व्योम au0828_analog_stream_reset(काष्ठा au0828_dev *dev)
अणु
	dprपूर्णांकk(1, "au0828_analog_stream_reset called\n");
	au0828_ग_लिखोreg(dev, AU0828_SENSORCTRL_100, 0x0);
	mdelay(30);
	au0828_ग_लिखोreg(dev, AU0828_SENSORCTRL_100, 0xb3);
पूर्ण

/*
 * Some operations needs to stop current streaming
 */
अटल पूर्णांक au0828_stream_पूर्णांकerrupt(काष्ठा au0828_dev *dev)
अणु
	dev->stream_state = STREAM_INTERRUPT;
	अगर (test_bit(DEV_DISCONNECTED, &dev->dev_state))
		वापस -ENODEV;
	वापस 0;
पूर्ण

पूर्णांक au0828_start_analog_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक rc = 0;

	dprपूर्णांकk(1, "au0828_start_analog_streaming called %d\n",
		dev->streaming_users);

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		dev->frame_count = 0;
	अन्यथा
		dev->vbi_frame_count = 0;

	अगर (dev->streaming_users == 0) अणु
		/* If we were करोing ac97 instead of i2s, it would go here...*/
		au0828_i2s_init(dev);
		rc = au0828_init_isoc(dev, AU0828_ISO_PACKETS_PER_URB,
				   AU0828_MAX_ISO_BUFS, dev->max_pkt_size,
				   au0828_isoc_copy);
		अगर (rc < 0) अणु
			pr_info("au0828_init_isoc failed\n");
			वापस rc;
		पूर्ण

		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 1);

		अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
			dev->vid_समयout_running = 1;
			mod_समयr(&dev->vid_समयout, jअगरfies + (HZ / 10));
		पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VBI_CAPTURE) अणु
			dev->vbi_समयout_running = 1;
			mod_समयr(&dev->vbi_समयout, jअगरfies + (HZ / 10));
		पूर्ण
	पूर्ण
	dev->streaming_users++;
	वापस rc;
पूर्ण

अटल व्योम au0828_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा au0828_dmaqueue *vidq = &dev->vidq;
	अचिन्हित दीर्घ flags = 0;

	dprपूर्णांकk(1, "au0828_stop_streaming called %d\n", dev->streaming_users);

	अगर (dev->streaming_users-- == 1) अणु
		au0828_uninit_isoc(dev);
		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);
	पूर्ण

	dev->vid_समयout_running = 0;
	del_समयr_sync(&dev->vid_समयout);

	spin_lock_irqsave(&dev->slock, flags);
	अगर (dev->isoc_ctl.buf != शून्य) अणु
		vb2_buffer_करोne(&dev->isoc_ctl.buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
		dev->isoc_ctl.buf = शून्य;
	पूर्ण
	जबतक (!list_empty(&vidq->active)) अणु
		काष्ठा au0828_buffer *buf;

		buf = list_entry(vidq->active.next, काष्ठा au0828_buffer, list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

व्योम au0828_stop_vbi_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा au0828_dmaqueue *vbiq = &dev->vbiq;
	अचिन्हित दीर्घ flags = 0;

	dprपूर्णांकk(1, "au0828_stop_vbi_streaming called %d\n",
		dev->streaming_users);

	अगर (dev->streaming_users-- == 1) अणु
		au0828_uninit_isoc(dev);
		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);
	पूर्ण

	spin_lock_irqsave(&dev->slock, flags);
	अगर (dev->isoc_ctl.vbi_buf != शून्य) अणु
		vb2_buffer_करोne(&dev->isoc_ctl.vbi_buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
		dev->isoc_ctl.vbi_buf = शून्य;
	पूर्ण
	जबतक (!list_empty(&vbiq->active)) अणु
		काष्ठा au0828_buffer *buf;

		buf = list_entry(vbiq->active.next, काष्ठा au0828_buffer, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);

	dev->vbi_समयout_running = 0;
	del_समयr_sync(&dev->vbi_समयout);
पूर्ण

अटल स्थिर काष्ठा vb2_ops au0828_video_qops = अणु
	.queue_setup     = queue_setup,
	.buf_prepare     = buffer_prepare,
	.buf_queue       = buffer_queue,
	.start_streaming = au0828_start_analog_streaming,
	.stop_streaming  = au0828_stop_streaming,
	.रुको_prepare    = vb2_ops_रुको_prepare,
	.रुको_finish     = vb2_ops_रुको_finish,
पूर्ण;

/* ------------------------------------------------------------------
   V4L2 पूर्णांकerface
   ------------------------------------------------------------------*/
/*
 * au0828_analog_unरेजिस्टर
 * unरेजिस्टर v4l2 devices
 */
पूर्णांक au0828_analog_unरेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	dprपूर्णांकk(1, "au0828_analog_unregister called\n");

	/* No analog TV */
	अगर (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		वापस 0;

	mutex_lock(&au0828_sysfs_lock);
	vb2_video_unरेजिस्टर_device(&dev->vdev);
	vb2_video_unरेजिस्टर_device(&dev->vbi_dev);
	mutex_unlock(&au0828_sysfs_lock);

	v4l2_device_disconnect(&dev->v4l2_dev);
	v4l2_device_put(&dev->v4l2_dev);

	वापस 1;
पूर्ण

/* This function ensures that video frames जारी to be delivered even अगर
   the ITU-656 input isn't receiving any data (thereby preventing applications
   such as tvसमय from hanging) */
अटल व्योम au0828_vid_buffer_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा au0828_dev *dev = from_समयr(dev, t, vid_समयout);
	काष्ठा au0828_dmaqueue *dma_q = &dev->vidq;
	काष्ठा au0828_buffer *buf;
	अचिन्हित अक्षर *vid_data;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&dev->slock, flags);

	buf = dev->isoc_ctl.buf;
	अगर (buf != शून्य) अणु
		vid_data = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
		स_रखो(vid_data, 0x00, buf->length); /* Blank green frame */
		buffer_filled(dev, dma_q, buf);
	पूर्ण
	get_next_buf(dma_q, &buf);

	अगर (dev->vid_समयout_running == 1)
		mod_समयr(&dev->vid_समयout, jअगरfies + (HZ / 10));

	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल व्योम au0828_vbi_buffer_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा au0828_dev *dev = from_समयr(dev, t, vbi_समयout);
	काष्ठा au0828_dmaqueue *dma_q = &dev->vbiq;
	काष्ठा au0828_buffer *buf;
	अचिन्हित अक्षर *vbi_data;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&dev->slock, flags);

	buf = dev->isoc_ctl.vbi_buf;
	अगर (buf != शून्य) अणु
		vbi_data = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
		स_रखो(vbi_data, 0x00, buf->length);
		buffer_filled(dev, dma_q, buf);
	पूर्ण
	vbi_get_next_buf(dma_q, &buf);

	अगर (dev->vbi_समयout_running == 1)
		mod_समयr(&dev->vbi_समयout, jअगरfies + (HZ / 10));
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल पूर्णांक au0828_v4l2_खोलो(काष्ठा file *filp)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(filp);
	पूर्णांक ret;

	dprपूर्णांकk(1,
		"%s called std_set %d dev_state %ld stream users %d users %d\n",
		__func__, dev->std_set_in_tuner_core, dev->dev_state,
		dev->streaming_users, dev->users);

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(filp);
	अगर (ret) अणु
		au0828_isocdbg("%s: v4l2_fh_open() returned error %d\n",
				__func__, ret);
		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण

	अगर (dev->users == 0) अणु
		au0828_analog_stream_enable(dev);
		au0828_analog_stream_reset(dev);
		dev->stream_state = STREAM_OFF;
		set_bit(DEV_INITIALIZED, &dev->dev_state);
	पूर्ण
	dev->users++;
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक au0828_v4l2_बंद(काष्ठा file *filp)
अणु
	पूर्णांक ret;
	काष्ठा au0828_dev *dev = video_drvdata(filp);
	काष्ठा video_device *vdev = video_devdata(filp);

	dprपूर्णांकk(1,
		"%s called std_set %d dev_state %ld stream users %d users %d\n",
		__func__, dev->std_set_in_tuner_core, dev->dev_state,
		dev->streaming_users, dev->users);

	mutex_lock(&dev->lock);
	अगर (vdev->vfl_type == VFL_TYPE_VIDEO && dev->vid_समयout_running) अणु
		/* Cancel समयout thपढ़ो in हाल they didn't call streamoff */
		dev->vid_समयout_running = 0;
		del_समयr_sync(&dev->vid_समयout);
	पूर्ण अन्यथा अगर (vdev->vfl_type == VFL_TYPE_VBI &&
			dev->vbi_समयout_running) अणु
		/* Cancel समयout thपढ़ो in हाल they didn't call streamoff */
		dev->vbi_समयout_running = 0;
		del_समयr_sync(&dev->vbi_समयout);
	पूर्ण

	अगर (test_bit(DEV_DISCONNECTED, &dev->dev_state))
		जाओ end;

	अगर (dev->users == 1) अणु
		/*
		 * Aव्योम putting tuner in sleep अगर DVB or ALSA are
		 * streaming.
		 *
		 * On most USB devices  like au0828 the tuner can
		 * be safely put in sleep state here अगर ALSA isn't
		 * streaming. Exceptions are some very old USB tuner
		 * models such as em28xx-based WinTV USB2 which have
		 * a separate audio output jack. The devices that have
		 * a separate audio output jack have analog tuners,
		 * like Philips FM1236. Those devices are always on,
		 * so the s_घातer callback are silently ignored.
		 * So, the current logic here करोes the following:
		 * Disable (put tuner to sleep) when
		 * - ALSA and DVB aren't streaming.
		 * - the last V4L2 file handler is बंदd.
		 *
		 * FIXME:
		 *
		 * Additionally, this logic could be improved to
		 * disable the media source अगर the above conditions
		 * are met and अगर the device:
		 * - करोesn't have a separate audio out plug (or
		 * - करोesn't use a silicon tuner like xc2028/3028/4000/5000).
		 *
		 * Once this additional logic is in place, a callback
		 * is needed to enable the media source and घातer on
		 * the tuner, क्रम radio to work.
		*/
		ret = v4l_enable_media_source(vdev);
		अगर (ret == 0)
			v4l2_device_call_all(&dev->v4l2_dev, 0, tuner,
					     standby);
		dev->std_set_in_tuner_core = 0;

		/* When बंद the device, set the usb पूर्णांकf0 पूर्णांकo alt0 to मुक्त
		   USB bandwidth */
		ret = usb_set_पूर्णांकerface(dev->usbdev, 0, 0);
		अगर (ret < 0)
			pr_info("Au0828 can't set alternate to 0!\n");
	पूर्ण
end:
	_vb2_fop_release(filp, शून्य);
	dev->users--;
	mutex_unlock(&dev->lock);
	वापस 0;
पूर्ण

/* Must be called with dev->lock held */
अटल व्योम au0828_init_tuner(काष्ठा au0828_dev *dev)
अणु
	काष्ठा v4l2_frequency f = अणु
		.frequency = dev->ctrl_freq,
		.type = V4L2_TUNER_ANALOG_TV,
	पूर्ण;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	अगर (dev->std_set_in_tuner_core)
		वापस;
	dev->std_set_in_tuner_core = 1;
	i2c_gate_ctrl(dev, 1);
	/* If we've never sent the standard in tuner core, करो so now.
	   We करोn't do this at device probe because we don't want to
	   incur the cost of a firmware load */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std, dev->std);
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, &f);
	i2c_gate_ctrl(dev, 0);
पूर्ण

अटल पूर्णांक au0828_set_क्रमmat(काष्ठा au0828_dev *dev, अचिन्हित पूर्णांक cmd,
			     काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	पूर्णांक ret;
	पूर्णांक width = क्रमmat->fmt.pix.width;
	पूर्णांक height = क्रमmat->fmt.pix.height;

	/* If they are demanding a क्रमmat other than the one we support,
	   bail out (tvसमय asks क्रम UYVY and then retries with YUYV) */
	अगर (क्रमmat->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_UYVY)
		वापस -EINVAL;

	/* क्रमmat->fmt.pix.width only support 720 and height 480 */
	अगर (width != 720)
		width = 720;
	अगर (height != 480)
		height = 480;

	क्रमmat->fmt.pix.width = width;
	क्रमmat->fmt.pix.height = height;
	क्रमmat->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	क्रमmat->fmt.pix.bytesperline = width * 2;
	क्रमmat->fmt.pix.sizeimage = width * height * 2;
	क्रमmat->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	क्रमmat->fmt.pix.field = V4L2_FIELD_INTERLACED;

	अगर (cmd == VIDIOC_TRY_FMT)
		वापस 0;

	/* maybe set new image क्रमmat, driver current only support 720*480 */
	dev->width = width;
	dev->height = height;
	dev->frame_size = width * height * 2;
	dev->field_size = width * height;
	dev->bytesperline = width * 2;

	अगर (dev->stream_state == STREAM_ON) अणु
		dprपूर्णांकk(1, "VIDIOC_SET_FMT: interrupting stream!\n");
		ret = au0828_stream_पूर्णांकerrupt(dev);
		अगर (ret != 0) अणु
			dprपूर्णांकk(1, "error interrupting video stream!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	au0828_analog_stream_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	strscpy(cap->driver, "au0828", माप(cap->driver));
	strscpy(cap->card, dev->board.name, माप(cap->card));
	usb_make_path(dev->usbdev, cap->bus_info, माप(cap->bus_info));

	/* set the device capabilities */
	cap->capabilities =
		V4L2_CAP_AUDIO | V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
		V4L2_CAP_TUNER | V4L2_CAP_VBI_CAPTURE | V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s called\n", __func__);

	f->pixelक्रमmat = V4L2_PIX_FMT_UYVY;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	f->fmt.pix.bytesperline = dev->bytesperline;
	f->fmt.pix.sizeimage = dev->frame_size;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M; /* NTSC/PAL */
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	वापस au0828_set_क्रमmat(dev, VIDIOC_TRY_FMT, f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);
	पूर्णांक rc;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	rc = check_dev(dev);
	अगर (rc < 0)
		वापस rc;

	अगर (vb2_is_busy(&dev->vb_vidq)) अणु
		pr_info("%s queue busy\n", __func__);
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	rc = au0828_set_क्रमmat(dev, VIDIOC_S_FMT, f);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id norm)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	अगर (norm == dev->std)
		वापस 0;

	अगर (dev->streaming_users > 0)
		वापस -EBUSY;

	dev->std = norm;

	au0828_init_tuner(dev);

	i2c_gate_ctrl(dev, 1);

	/*
	 * FIXME: when we support something other than 60Hz standards,
	 * we are going to have to make the au0828 bridge adjust the size
	 * of its capture buffer, which is currently hardcoded at 720x480
	 */

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std, norm);

	i2c_gate_ctrl(dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	*norm = dev->std;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *input)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक पंचांगp;

	अटल स्थिर अक्षर *inames[] = अणु
		[AU0828_VMUX_UNDEFINED] = "Undefined",
		[AU0828_VMUX_COMPOSITE] = "Composite",
		[AU0828_VMUX_SVIDEO] = "S-Video",
		[AU0828_VMUX_CABLE] = "Cable TV",
		[AU0828_VMUX_TELEVISION] = "Television",
		[AU0828_VMUX_DVB] = "DVB",
	पूर्ण;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	पंचांगp = input->index;

	अगर (पंचांगp >= AU0828_MAX_INPUT)
		वापस -EINVAL;
	अगर (AUVI_INPUT(पंचांगp).type == 0)
		वापस -EINVAL;

	input->index = पंचांगp;
	strscpy(input->name, inames[AUVI_INPUT(पंचांगp).type], माप(input->name));
	अगर ((AUVI_INPUT(पंचांगp).type == AU0828_VMUX_TELEVISION) ||
	    (AUVI_INPUT(पंचांगp).type == AU0828_VMUX_CABLE)) अणु
		input->type |= V4L2_INPUT_TYPE_TUNER;
		input->audioset = 1;
	पूर्ण अन्यथा अणु
		input->type |= V4L2_INPUT_TYPE_CAMERA;
		input->audioset = 2;
	पूर्ण

	input->std = dev->vdev.tvnorms;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	*i = dev->ctrl_input;
	वापस 0;
पूर्ण

अटल व्योम au0828_s_input(काष्ठा au0828_dev *dev, पूर्णांक index)
अणु
	पूर्णांक i;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	चयन (AUVI_INPUT(index).type) अणु
	हाल AU0828_VMUX_SVIDEO:
		dev->input_type = AU0828_VMUX_SVIDEO;
		dev->ctrl_ainput = 1;
		अवरोध;
	हाल AU0828_VMUX_COMPOSITE:
		dev->input_type = AU0828_VMUX_COMPOSITE;
		dev->ctrl_ainput = 1;
		अवरोध;
	हाल AU0828_VMUX_TELEVISION:
		dev->input_type = AU0828_VMUX_TELEVISION;
		dev->ctrl_ainput = 0;
		अवरोध;
	शेष:
		dprपूर्णांकk(1, "unknown input type set [%d]\n",
			AUVI_INPUT(index).type);
		वापस;
	पूर्ण

	dev->ctrl_input = index;

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_routing,
			AUVI_INPUT(index).vmux, 0, 0);

	क्रम (i = 0; i < AU0828_MAX_INPUT; i++) अणु
		पूर्णांक enable = 0;
		अगर (AUVI_INPUT(i).audio_setup == शून्य)
			जारी;

		अगर (i == index)
			enable = 1;
		अन्यथा
			enable = 0;
		अगर (enable) अणु
			(AUVI_INPUT(i).audio_setup)(dev, enable);
		पूर्ण अन्यथा अणु
			/* Make sure we leave it turned on अगर some
			   other input is routed to this callback */
			अगर ((AUVI_INPUT(i).audio_setup) !=
			    ((AUVI_INPUT(index).audio_setup))) अणु
				(AUVI_INPUT(i).audio_setup)(dev, enable);
			पूर्ण
		पूर्ण
	पूर्ण

	v4l2_device_call_all(&dev->v4l2_dev, 0, audio, s_routing,
			AUVI_INPUT(index).amux, 0, 0);
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक index)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);
	काष्ठा video_device *vfd = video_devdata(file);

	dprपूर्णांकk(1, "VIDIOC_S_INPUT in function %s, input=%d\n", __func__,
		index);
	अगर (index >= AU0828_MAX_INPUT)
		वापस -EINVAL;
	अगर (AUVI_INPUT(index).type == 0)
		वापस -EINVAL;

	अगर (dev->ctrl_input == index)
		वापस 0;

	au0828_s_input(dev, index);

	/*
	 * Input has been changed. Disable the media source
	 * associated with the old input and enable source
	 * क्रम the newly set input
	 */
	v4l_disable_media_source(vfd);
	वापस v4l_enable_media_source(vfd);
पूर्ण

अटल पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_audio *a)
अणु
	अगर (a->index > 1)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s called\n", __func__);

	अगर (a->index == 0)
		strscpy(a->name, "Television", माप(a->name));
	अन्यथा
		strscpy(a->name, "Line in", माप(a->name));

	a->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_audio *a)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	a->index = dev->ctrl_ainput;
	अगर (a->index == 0)
		strscpy(a->name, "Television", माप(a->name));
	अन्यथा
		strscpy(a->name, "Line in", माप(a->name));

	a->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_audio *a)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	अगर (a->index != dev->ctrl_ainput)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret;

	अगर (t->index != 0)
		वापस -EINVAL;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	strscpy(t->name, "Auvitek tuner", माप(t->name));

	au0828_init_tuner(dev);
	i2c_gate_ctrl(dev, 1);
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_tuner, t);
	i2c_gate_ctrl(dev, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	अगर (t->index != 0)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	au0828_init_tuner(dev);
	i2c_gate_ctrl(dev, 1);
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_tuner, t);
	i2c_gate_ctrl(dev, 0);

	dprपूर्णांकk(1, "VIDIOC_S_TUNER: signal = %x, afc = %x\n", t->संकेत,
		t->afc);

	वापस 0;

पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	अगर (freq->tuner != 0)
		वापस -EINVAL;
	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);
	freq->frequency = dev->ctrl_freq;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);
	काष्ठा v4l2_frequency new_freq = *freq;

	अगर (freq->tuner != 0)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	au0828_init_tuner(dev);
	i2c_gate_ctrl(dev, 1);

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, freq);
	/* Get the actual set (and possibly clamped) frequency */
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_frequency, &new_freq);
	dev->ctrl_freq = new_freq.frequency;

	i2c_gate_ctrl(dev, 0);

	au0828_analog_stream_reset(dev);

	वापस 0;
पूर्ण


/* RAW VBI ioctls */

अटल पूर्णांक vidioc_g_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	क्रमmat->fmt.vbi.samples_per_line = dev->vbi_width;
	क्रमmat->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	क्रमmat->fmt.vbi.offset = 0;
	क्रमmat->fmt.vbi.flags = 0;
	क्रमmat->fmt.vbi.sampling_rate = 6750000 * 4 / 2;

	क्रमmat->fmt.vbi.count[0] = dev->vbi_height;
	क्रमmat->fmt.vbi.count[1] = dev->vbi_height;
	क्रमmat->fmt.vbi.start[0] = 21;
	क्रमmat->fmt.vbi.start[1] = 284;
	स_रखो(क्रमmat->fmt.vbi.reserved, 0, माप(क्रमmat->fmt.vbi.reserved));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	f->numerator = 54;
	f->denominator = 59;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = dev->width;
		s->r.height = dev->height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	reg->val = au0828_पढ़ो(dev, reg->reg);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा au0828_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	वापस au0828_ग_लिखोreg(dev, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	dprपूर्णांकk(1, "%s called\n", __func__);

	v4l2_ctrl_log_status(file, fh);
	v4l2_device_call_all(vdev->v4l2_dev, 0, core, log_status);
	वापस 0;
पूर्ण

व्योम au0828_v4l2_suspend(काष्ठा au0828_dev *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	pr_info("stopping V4L2\n");

	अगर (dev->stream_state == STREAM_ON) अणु
		pr_info("stopping V4L2 active URBs\n");
		au0828_analog_stream_disable(dev);
		/* stop urbs */
		क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
			urb = dev->isoc_ctl.urb[i];
			अगर (urb) अणु
				अगर (!irqs_disabled())
					usb_समाप्त_urb(urb);
				अन्यथा
					usb_unlink_urb(urb);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dev->vid_समयout_running)
		del_समयr_sync(&dev->vid_समयout);
	अगर (dev->vbi_समयout_running)
		del_समयr_sync(&dev->vbi_समयout);
पूर्ण

व्योम au0828_v4l2_resume(काष्ठा au0828_dev *dev)
अणु
	पूर्णांक i, rc;

	pr_info("restarting V4L2\n");

	अगर (dev->stream_state == STREAM_ON) अणु
		au0828_stream_पूर्णांकerrupt(dev);
		au0828_init_tuner(dev);
	पूर्ण

	अगर (dev->vid_समयout_running)
		mod_समयr(&dev->vid_समयout, jअगरfies + (HZ / 10));
	अगर (dev->vbi_समयout_running)
		mod_समयr(&dev->vbi_समयout, jअगरfies + (HZ / 10));

	/* If we were करोing ac97 instead of i2s, it would go here...*/
	au0828_i2s_init(dev);

	au0828_analog_stream_enable(dev);

	अगर (!(dev->stream_state == STREAM_ON)) अणु
		au0828_analog_stream_reset(dev);
		/* submit urbs */
		क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
			rc = usb_submit_urb(dev->isoc_ctl.urb[i], GFP_ATOMIC);
			अगर (rc) अणु
				au0828_isocdbg("submit of urb %i failed (error=%i)\n",
					       i, rc);
				au0828_uninit_isoc(dev);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations au0828_v4l_fops = अणु
	.owner      = THIS_MODULE,
	.खोलो       = au0828_v4l2_खोलो,
	.release    = au0828_v4l2_बंद,
	.पढ़ो       = vb2_fop_पढ़ो,
	.poll       = vb2_fop_poll,
	.mmap       = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap            = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap    = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap       = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap     = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap       = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_try_fmt_vbi_cap     = vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_क्रमागतaudio           = vidioc_क्रमागतaudio,
	.vidioc_g_audio             = vidioc_g_audio,
	.vidioc_s_audio             = vidioc_s_audio,
	.vidioc_g_pixelaspect       = vidioc_g_pixelaspect,
	.vidioc_g_selection         = vidioc_g_selection,

	.vidioc_reqbufs             = vb2_ioctl_reqbufs,
	.vidioc_create_bufs         = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf         = vb2_ioctl_prepare_buf,
	.vidioc_querybuf            = vb2_ioctl_querybuf,
	.vidioc_qbuf                = vb2_ioctl_qbuf,
	.vidioc_dqbuf               = vb2_ioctl_dqbuf,
	.vidioc_expbuf               = vb2_ioctl_expbuf,

	.vidioc_s_std               = vidioc_s_std,
	.vidioc_g_std               = vidioc_g_std,
	.vidioc_क्रमागत_input          = vidioc_क्रमागत_input,
	.vidioc_g_input             = vidioc_g_input,
	.vidioc_s_input             = vidioc_s_input,

	.vidioc_streamon            = vb2_ioctl_streamon,
	.vidioc_streamoff           = vb2_ioctl_streamoff,

	.vidioc_g_tuner             = vidioc_g_tuner,
	.vidioc_s_tuner             = vidioc_s_tuner,
	.vidioc_g_frequency         = vidioc_g_frequency,
	.vidioc_s_frequency         = vidioc_s_frequency,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर          = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर          = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_log_status	    = vidioc_log_status,
	.vidioc_subscribe_event     = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event   = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device au0828_video_ढाँचा = अणु
	.fops                       = &au0828_v4l_fops,
	.release                    = video_device_release_empty,
	.ioctl_ops		    = &video_ioctl_ops,
	.tvnorms                    = V4L2_STD_NTSC_M | V4L2_STD_PAL_M,
पूर्ण;

अटल पूर्णांक au0828_vb2_setup(काष्ठा au0828_dev *dev)
अणु
	पूर्णांक rc;
	काष्ठा vb2_queue *q;

	/* Setup Videobuf2 क्रम Video capture */
	q = &dev->vb_vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_READ | VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा au0828_buffer);
	q->ops = &au0828_video_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;

	rc = vb2_queue_init(q);
	अगर (rc < 0)
		वापस rc;

	/* Setup Videobuf2 क्रम VBI capture */
	q = &dev->vb_vbiq;
	q->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	q->io_modes = VB2_READ | VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा au0828_buffer);
	q->ops = &au0828_vbi_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;

	rc = vb2_queue_init(q);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम au0828_analog_create_entities(काष्ठा au0828_dev *dev)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	अटल स्थिर अक्षर * स्थिर inames[] = अणु
		[AU0828_VMUX_COMPOSITE] = "Composite",
		[AU0828_VMUX_SVIDEO] = "S-Video",
		[AU0828_VMUX_CABLE] = "Cable TV",
		[AU0828_VMUX_TELEVISION] = "Television",
		[AU0828_VMUX_DVB] = "DVB",
	पूर्ण;
	पूर्णांक ret, i;

	/* Initialize Video and VBI pads */
	dev->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vdev.entity, 1, &dev->video_pad);
	अगर (ret < 0)
		pr_err("failed to initialize video media entity!\n");

	dev->vbi_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vbi_dev.entity, 1, &dev->vbi_pad);
	अगर (ret < 0)
		pr_err("failed to initialize vbi media entity!\n");

	/* Create entities क्रम each input connector */
	क्रम (i = 0; i < AU0828_MAX_INPUT; i++) अणु
		काष्ठा media_entity *ent = &dev->input_ent[i];

		अगर (AUVI_INPUT(i).type == AU0828_VMUX_UNDEFINED)
			अवरोध;

		ent->name = inames[AUVI_INPUT(i).type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		चयन (AUVI_INPUT(i).type) अणु
		हाल AU0828_VMUX_COMPOSITE:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			अवरोध;
		हाल AU0828_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			अवरोध;
		हाल AU0828_VMUX_CABLE:
		हाल AU0828_VMUX_TELEVISION:
		हाल AU0828_VMUX_DVB:
		शेष: /* Just to shut up a warning */
			ent->function = MEDIA_ENT_F_CONN_RF;
			अवरोध;
		पूर्ण

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		अगर (ret < 0)
			pr_err("failed to initialize input pad[%d]!\n", i);

		ret = media_device_रेजिस्टर_entity(dev->media_dev, ent);
		अगर (ret < 0)
			pr_err("failed to register input entity %d!\n", i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/**************************************************************************/

पूर्णांक au0828_analog_रेजिस्टर(काष्ठा au0828_dev *dev,
			   काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	पूर्णांक retval = -ENOMEM;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक i, ret;

	dprपूर्णांकk(1, "au0828_analog_register called for intf#%d!\n",
		पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber);

	/* No analog TV */
	अगर (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		वापस 0;

	/* set au0828 usb पूर्णांकerface0 to as5 */
	retval = usb_set_पूर्णांकerface(dev->usbdev,
			पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber, 5);
	अगर (retval != 0) अणु
		pr_info("Failure setting usb interface0 to as5\n");
		वापस retval;
	पूर्ण

	/* Figure out which endpoपूर्णांक has the isoc पूर्णांकerface */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (((endpoपूर्णांक->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK)
		     == USB_सूची_IN) &&
		    ((endpoपूर्णांक->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)
		     == USB_ENDPOINT_XFER_ISOC)) अणु

			/* we find our isoc in endpoपूर्णांक */
			u16 पंचांगp = le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);
			dev->max_pkt_size = (पंचांगp & 0x07ff) *
				(((पंचांगp & 0x1800) >> 11) + 1);
			dev->isoc_in_endpoपूर्णांकaddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;
			dprपूर्णांकk(1,
				"Found isoc endpoint 0x%02x, max size = %d\n",
				dev->isoc_in_endpoपूर्णांकaddr, dev->max_pkt_size);
		पूर्ण
	पूर्ण
	अगर (!(dev->isoc_in_endpoपूर्णांकaddr)) अणु
		pr_info("Could not locate isoc endpoint\n");
		वापस -ENODEV;
	पूर्ण

	init_रुकोqueue_head(&dev->खोलो);
	spin_lock_init(&dev->slock);

	/* init video dma queues */
	INIT_LIST_HEAD(&dev->vidq.active);
	INIT_LIST_HEAD(&dev->vbiq.active);

	समयr_setup(&dev->vid_समयout, au0828_vid_buffer_समयout, 0);
	समयr_setup(&dev->vbi_समयout, au0828_vbi_buffer_समयout, 0);

	dev->width = NTSC_STD_W;
	dev->height = NTSC_STD_H;
	dev->field_size = dev->width * dev->height;
	dev->frame_size = dev->field_size << 1;
	dev->bytesperline = dev->width << 1;
	dev->vbi_width = 720;
	dev->vbi_height = 1;
	dev->ctrl_ainput = 0;
	dev->ctrl_freq = 960;
	dev->std = V4L2_STD_NTSC_M;
	/* Default input is TV Tuner */
	au0828_s_input(dev, 0);

	mutex_init(&dev->vb_queue_lock);
	mutex_init(&dev->vb_vbi_queue_lock);

	/* Fill the video capture device काष्ठा */
	dev->vdev = au0828_video_ढाँचा;
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.lock = &dev->lock;
	dev->vdev.queue = &dev->vb_vidq;
	dev->vdev.queue->lock = &dev->vb_queue_lock;
	dev->vdev.device_caps =
		V4L2_CAP_AUDIO | V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
		V4L2_CAP_TUNER | V4L2_CAP_VIDEO_CAPTURE;
	strscpy(dev->vdev.name, "au0828a video", माप(dev->vdev.name));

	/* Setup the VBI device */
	dev->vbi_dev = au0828_video_ढाँचा;
	dev->vbi_dev.v4l2_dev = &dev->v4l2_dev;
	dev->vbi_dev.lock = &dev->lock;
	dev->vbi_dev.queue = &dev->vb_vbiq;
	dev->vbi_dev.queue->lock = &dev->vb_vbi_queue_lock;
	dev->vbi_dev.device_caps =
		V4L2_CAP_AUDIO | V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
		V4L2_CAP_TUNER | V4L2_CAP_VBI_CAPTURE;
	strscpy(dev->vbi_dev.name, "au0828a vbi", माप(dev->vbi_dev.name));

	/* Init entities at the Media Controller */
	au0828_analog_create_entities(dev);

	/* initialize videobuf2 stuff */
	retval = au0828_vb2_setup(dev);
	अगर (retval != 0) अणु
		dprपूर्णांकk(1, "unable to setup videobuf2 queues (error = %d).\n",
			retval);
		वापस -ENODEV;
	पूर्ण

	/* Register the v4l2 device */
	video_set_drvdata(&dev->vdev, dev);
	retval = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (retval != 0) अणु
		dprपूर्णांकk(1, "unable to register video device (error = %d).\n",
			retval);
		वापस -ENODEV;
	पूर्ण

	/* Register the vbi device */
	video_set_drvdata(&dev->vbi_dev, dev);
	retval = video_रेजिस्टर_device(&dev->vbi_dev, VFL_TYPE_VBI, -1);
	अगर (retval != 0) अणु
		dprपूर्णांकk(1, "unable to register vbi device (error = %d).\n",
			retval);
		ret = -ENODEV;
		जाओ err_reg_vbi_dev;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	retval = v4l2_mc_create_media_graph(dev->media_dev);
	अगर (retval) अणु
		pr_err("%s() au0282_dev_register failed to create graph\n",
			__func__);
		ret = -ENODEV;
		जाओ err_reg_vbi_dev;
	पूर्ण
#पूर्ण_अगर

	dprपूर्णांकk(1, "%s completed!\n", __func__);

	वापस 0;

err_reg_vbi_dev:
	vb2_video_unरेजिस्टर_device(&dev->vdev);
	वापस ret;
पूर्ण

