<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STK1160 driver
 *
 * Copyright (C) 2012 Ezequiel Garcia
 * <elezegarcia--a.t--gmail.com>
 *
 * Based on Easycap driver by R.M. Thomas
 *	Copyright (C) 2010 R.M. Thomas
 *	<rmthomas--a.t--sciolus.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>

#समावेश "stk1160.h"

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा stk1160 *dev,
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

	अगर (packet < 0)
		prपूर्णांकk_ratelimited(KERN_WARNING "URB status %d [%s].\n",
				status, errmsg);
	अन्यथा
		prपूर्णांकk_ratelimited(KERN_INFO "URB packet %d, status %d [%s].\n",
			       packet, status, errmsg);
पूर्ण

अटल अंतरभूत
काष्ठा stk1160_buffer *stk1160_next_buffer(काष्ठा stk1160 *dev)
अणु
	काष्ठा stk1160_buffer *buf = शून्य;
	अचिन्हित दीर्घ flags = 0;

	/* Current buffer must be शून्य when this functions माला_लो called */
	WARN_ON(dev->isoc_ctl.buf);

	spin_lock_irqsave(&dev->buf_lock, flags);
	अगर (!list_empty(&dev->avail_bufs)) अणु
		buf = list_first_entry(&dev->avail_bufs,
				काष्ठा stk1160_buffer, list);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&dev->buf_lock, flags);

	वापस buf;
पूर्ण

अटल अंतरभूत
व्योम stk1160_buffer_करोne(काष्ठा stk1160 *dev)
अणु
	काष्ठा stk1160_buffer *buf = dev->isoc_ctl.buf;

	buf->vb.sequence = dev->sequence++;
	buf->vb.field = V4L2_FIELD_INTERLACED;
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();

	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, buf->bytesused);
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	dev->isoc_ctl.buf = शून्य;
पूर्ण

अटल अंतरभूत
व्योम stk1160_copy_video(काष्ठा stk1160 *dev, u8 *src, पूर्णांक len)
अणु
	पूर्णांक linesकरोne, lineoff, lencopy;
	पूर्णांक bytesperline = dev->width * 2;
	काष्ठा stk1160_buffer *buf = dev->isoc_ctl.buf;
	u8 *dst = buf->mem;
	पूर्णांक reमुख्य;

	/*
	 * TODO: These stk1160_dbg are very spammy!
	 * We should 1) check why we are getting them
	 * and 2) add ratelimit.
	 *
	 * UPDATE: One of the reasons (the only one?) क्रम getting these
	 * is incorrect standard (mismatch between expected and configured).
	 * So perhaps, we could add a counter क्रम errors. When the counter
	 * reaches some value, we simply stop streaming.
	 */

	len -= 4;
	src += 4;

	reमुख्य = len;

	linesकरोne = buf->pos / bytesperline;
	lineoff = buf->pos % bytesperline; /* offset in current line */

	अगर (!buf->odd)
		dst += bytesperline;

	/* Multiply linesकरोne by two, to take account of the other field */
	dst += linesकरोne * bytesperline * 2 + lineoff;

	/* Copy the reमुख्यing of current line */
	अगर (reमुख्य < (bytesperline - lineoff))
		lencopy = reमुख्य;
	अन्यथा
		lencopy = bytesperline - lineoff;

	/*
	 * Check अगर we have enough space left in the buffer.
	 * In that हाल, we क्रमce loop निकास after copy.
	 */
	अगर (lencopy > buf->bytesused - buf->length) अणु
		lencopy = buf->bytesused - buf->length;
		reमुख्य = lencopy;
	पूर्ण

	/* Check अगर the copy is करोne */
	अगर (lencopy == 0 || reमुख्य == 0)
		वापस;

	/* Let the bug hunt begin! sanity checks! */
	अगर (lencopy < 0) अणु
		stk1160_dbg("copy skipped: negative lencopy\n");
		वापस;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)dst + lencopy >
		(अचिन्हित दीर्घ)buf->mem + buf->length) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING "stk1160: buffer overflow detected\n");
		वापस;
	पूर्ण

	स_नकल(dst, src, lencopy);

	buf->bytesused += lencopy;
	buf->pos += lencopy;
	reमुख्य -= lencopy;

	/* Copy current field line by line, पूर्णांकerlacing with the other field */
	जबतक (reमुख्य > 0) अणु

		dst += lencopy + bytesperline;
		src += lencopy;

		/* Copy one line at a समय */
		अगर (reमुख्य < bytesperline)
			lencopy = reमुख्य;
		अन्यथा
			lencopy = bytesperline;

		/*
		 * Check अगर we have enough space left in the buffer.
		 * In that हाल, we क्रमce loop निकास after copy.
		 */
		अगर (lencopy > buf->bytesused - buf->length) अणु
			lencopy = buf->bytesused - buf->length;
			reमुख्य = lencopy;
		पूर्ण

		/* Check अगर the copy is करोne */
		अगर (lencopy == 0 || reमुख्य == 0)
			वापस;

		अगर (lencopy < 0) अणु
			prपूर्णांकk_ratelimited(KERN_WARNING "stk1160: negative lencopy detected\n");
			वापस;
		पूर्ण

		अगर ((अचिन्हित दीर्घ)dst + lencopy >
			(अचिन्हित दीर्घ)buf->mem + buf->length) अणु
			prपूर्णांकk_ratelimited(KERN_WARNING "stk1160: buffer overflow detected\n");
			वापस;
		पूर्ण

		स_नकल(dst, src, lencopy);
		reमुख्य -= lencopy;

		buf->bytesused += lencopy;
		buf->pos += lencopy;
	पूर्ण
पूर्ण

/*
 * Controls the isoc copy of each urb packet
 */
अटल व्योम stk1160_process_isoc(काष्ठा stk1160 *dev, काष्ठा urb *urb)
अणु
	पूर्णांक i, len, status;
	u8 *p;

	अगर (!dev) अणु
		stk1160_warn("%s called with null device\n", __func__);
		वापस;
	पूर्ण

	अगर (urb->status < 0) अणु
		/* Prपूर्णांक status and drop current packet (or field?) */
		prपूर्णांक_err_status(dev, -1, urb->status);
		वापस;
	पूर्ण

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		status = urb->iso_frame_desc[i].status;
		अगर (status < 0) अणु
			prपूर्णांक_err_status(dev, i, status);
			जारी;
		पूर्ण

		/* Get packet actual length and poपूर्णांकer to data */
		p = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		len = urb->iso_frame_desc[i].actual_length;

		/* Empty packet */
		अगर (len <= 4)
			जारी;

		/*
		 * An 8-byte packet sequence means end of field.
		 * So अगर we करोn't have any packet, we start receiving one now
		 * and अगर we करो have a packet, then we are करोne with it.
		 *
		 * These end of field packets are always 0xc0 or 0x80,
		 * but not always 8-byte दीर्घ so we करोn't check packet length.
		 */
		अगर (p[0] == 0xc0) अणु

			/*
			 * If first byte is 0xc0 then we received
			 * second field, and frame has ended.
			 */
			अगर (dev->isoc_ctl.buf != शून्य)
				stk1160_buffer_करोne(dev);

			dev->isoc_ctl.buf = stk1160_next_buffer(dev);
			अगर (dev->isoc_ctl.buf == शून्य)
				वापस;
		पूर्ण

		/*
		 * If we करोn't have a buffer here, then it means we
		 * haven't found the start mark sequence.
		 */
		अगर (dev->isoc_ctl.buf == शून्य)
			जारी;

		अगर (p[0] == 0xc0 || p[0] == 0x80) अणु

			/* We set next packet parity and
			 * जारी to get next one
			 */
			dev->isoc_ctl.buf->odd = *p & 0x40;
			dev->isoc_ctl.buf->pos = 0;
			जारी;
		पूर्ण

		stk1160_copy_video(dev, p, len);
	पूर्ण
पूर्ण


/*
 * IRQ callback, called by URB callback
 */
अटल व्योम stk1160_isoc_irq(काष्ठा urb *urb)
अणु
	पूर्णांक i, rc;
	काष्ठा stk1160 *dev = urb->context;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* TODO: check uvc driver: he मुक्तs the queue here */
		वापस;
	शेष:
		stk1160_err("urb error! status %d\n", urb->status);
		वापस;
	पूर्ण

	stk1160_process_isoc(dev, urb);

	/* Reset urb buffers */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	पूर्ण

	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc)
		stk1160_err("urb re-submit failed (%d)\n", rc);
पूर्ण

/*
 * Cancel urbs
 * This function can't be called in atomic context
 */
व्योम stk1160_cancel_isoc(काष्ठा stk1160 *dev)
अणु
	पूर्णांक i, num_bufs = dev->isoc_ctl.num_bufs;

	/*
	 * This check is not necessary, but we add it
	 * to aव्योम a spurious debug message
	 */
	अगर (!num_bufs)
		वापस;

	stk1160_dbg("killing %d urbs...\n", num_bufs);

	क्रम (i = 0; i < num_bufs; i++) अणु

		/*
		 * To समाप्त urbs we can't be in atomic context.
		 * We करोn't care क्रम शून्य poपूर्णांकer since
		 * usb_समाप्त_urb allows it.
		 */
		usb_समाप्त_urb(dev->isoc_ctl.urb[i]);
	पूर्ण

	stk1160_dbg("all urbs killed\n");
पूर्ण

/*
 * Releases urb and transfer buffers
 * Obviusly, associated urb must be समाप्तed beक्रमe releasing it.
 */
व्योम stk1160_मुक्त_isoc(काष्ठा stk1160 *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i, num_bufs = dev->isoc_ctl.num_bufs;

	stk1160_dbg("freeing %d urb buffers...\n", num_bufs);

	क्रम (i = 0; i < num_bufs; i++) अणु

		urb = dev->isoc_ctl.urb[i];
		अगर (urb) अणु

			अगर (dev->isoc_ctl.transfer_buffer[i]) अणु
#अगर_अघोषित CONFIG_DMA_NONCOHERENT
				usb_मुक्त_coherent(dev->udev,
					urb->transfer_buffer_length,
					dev->isoc_ctl.transfer_buffer[i],
					urb->transfer_dma);
#अन्यथा
				kमुक्त(dev->isoc_ctl.transfer_buffer[i]);
#पूर्ण_अगर
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

	stk1160_dbg("all urb buffers freed\n");
पूर्ण

/*
 * Helper क्रम cancelling and मुक्तing urbs
 * This function can't be called in atomic context
 */
व्योम stk1160_uninit_isoc(काष्ठा stk1160 *dev)
अणु
	stk1160_cancel_isoc(dev);
	stk1160_मुक्त_isoc(dev);
पूर्ण

/*
 * Allocate URBs
 */
पूर्णांक stk1160_alloc_isoc(काष्ठा stk1160 *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i, j, k, sb_size, max_packets, num_bufs;

	/*
	 * It may be necessary to release isoc here,
	 * since isoc are only released on disconnection.
	 * (see new_pkt_size flag)
	 */
	अगर (dev->isoc_ctl.num_bufs)
		stk1160_uninit_isoc(dev);

	stk1160_dbg("allocating urbs...\n");

	num_bufs = STK1160_NUM_BUFS;
	max_packets = STK1160_NUM_PACKETS;
	sb_size = max_packets * dev->max_pkt_size;

	dev->isoc_ctl.buf = शून्य;
	dev->isoc_ctl.max_pkt_size = dev->max_pkt_size;
	dev->isoc_ctl.urb = kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!dev->isoc_ctl.urb) अणु
		stk1160_err("out of memory for urb array\n");
		वापस -ENOMEM;
	पूर्ण

	dev->isoc_ctl.transfer_buffer = kसुस्मृति(num_bufs, माप(व्योम *),
						GFP_KERNEL);
	अगर (!dev->isoc_ctl.transfer_buffer) अणु
		stk1160_err("out of memory for usb transfers\n");
		kमुक्त(dev->isoc_ctl.urb);
		वापस -ENOMEM;
	पूर्ण

	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < num_bufs; i++) अणु

		urb = usb_alloc_urb(max_packets, GFP_KERNEL);
		अगर (!urb)
			जाओ मुक्त_i_bufs;
		dev->isoc_ctl.urb[i] = urb;

#अगर_अघोषित CONFIG_DMA_NONCOHERENT
		dev->isoc_ctl.transfer_buffer[i] = usb_alloc_coherent(dev->udev,
			sb_size, GFP_KERNEL, &urb->transfer_dma);
#अन्यथा
		dev->isoc_ctl.transfer_buffer[i] = kदो_स्मृति(sb_size, GFP_KERNEL);
#पूर्ण_अगर
		अगर (!dev->isoc_ctl.transfer_buffer[i]) अणु
			stk1160_err("cannot alloc %d bytes for tx[%d] buffer\n",
				sb_size, i);

			/* Not enough transfer buffers, so just give up */
			अगर (i < STK1160_MIN_BUFS)
				जाओ मुक्त_i_bufs;
			जाओ nomore_tx_bufs;
		पूर्ण
		स_रखो(dev->isoc_ctl.transfer_buffer[i], 0, sb_size);

		/*
		 * FIXME: Where can I get the endpoपूर्णांक?
		 */
		urb->dev = dev->udev;
		urb->pipe = usb_rcvisocpipe(dev->udev, STK1160_EP_VIDEO);
		urb->transfer_buffer = dev->isoc_ctl.transfer_buffer[i];
		urb->transfer_buffer_length = sb_size;
		urb->complete = stk1160_isoc_irq;
		urb->context = dev;
		urb->पूर्णांकerval = 1;
		urb->start_frame = 0;
		urb->number_of_packets = max_packets;
#अगर_अघोषित CONFIG_DMA_NONCOHERENT
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
#अन्यथा
		urb->transfer_flags = URB_ISO_ASAP;
#पूर्ण_अगर

		k = 0;
		क्रम (j = 0; j < max_packets; j++) अणु
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length =
					dev->isoc_ctl.max_pkt_size;
			k += dev->isoc_ctl.max_pkt_size;
		पूर्ण
	पूर्ण

	stk1160_dbg("%d urbs allocated\n", num_bufs);

	/* At last we can say we have some buffers */
	dev->isoc_ctl.num_bufs = num_bufs;

	वापस 0;

nomore_tx_bufs:
	/*
	 * Failed to allocate desired buffer count. However, we may have
	 * enough to work fine, so we just मुक्त the extra urb,
	 * store the allocated count and keep going, fingers crossed!
	 */
	usb_मुक्त_urb(dev->isoc_ctl.urb[i]);
	dev->isoc_ctl.urb[i] = शून्य;

	stk1160_warn("%d urbs allocated. Trying to continue...\n", i - 1);

	dev->isoc_ctl.num_bufs = i - 1;

	वापस 0;

मुक्त_i_bufs:
	/* Save the allocated buffers so far, so we can properly मुक्त them */
	dev->isoc_ctl.num_bufs = i+1;
	stk1160_मुक्त_isoc(dev);
	वापस -ENOMEM;
पूर्ण

