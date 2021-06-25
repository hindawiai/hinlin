<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx_vbi.c - driver क्रम Conexant Cx23100/101/102 USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
	Based on cx88 driver

 */

#समावेश "cx231xx.h"
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/tuner.h>

#समावेश "cx231xx-vbi.h"

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा cx231xx *dev, पूर्णांक packet, पूर्णांक status)
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
		dev_err(dev->dev,
			"URB status %d [%s].\n", status, errmsg);
	पूर्ण अन्यथा अणु
		dev_err(dev->dev,
			"URB packet %d, status %d [%s].\n",
			packet, status, errmsg);
	पूर्ण
पूर्ण

/*
 * Controls the isoc copy of each urb packet
 */
अटल अंतरभूत पूर्णांक cx231xx_isoc_vbi_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	पूर्णांक rc = 1;
	अचिन्हित अक्षर *p_buffer;
	u32 bytes_parsed = 0, buffer_size = 0;
	u8 sav_eav = 0;

	अगर (!dev)
		वापस 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस 0;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		अगर (urb->status == -ENOENT)
			वापस 0;
	पूर्ण

	/* get buffer poपूर्णांकer and length */
	p_buffer = urb->transfer_buffer;
	buffer_size = urb->actual_length;

	अगर (buffer_size > 0) अणु
		bytes_parsed = 0;

		अगर (dma_q->is_partial_line) अणु
			/* Handle the हाल where we were working on a partial
			   line */
			sav_eav = dma_q->last_sav;
		पूर्ण अन्यथा अणु
			/* Check क्रम a SAV/EAV overlapping the
			   buffer boundary */

			sav_eav = cx231xx_find_boundary_SAV_EAV(p_buffer,
							  dma_q->partial_buf,
							  &bytes_parsed);
		पूर्ण

		sav_eav &= 0xF0;
		/* Get the first line अगर we have some portion of an SAV/EAV from
		   the last buffer or a partial line */
		अगर (sav_eav) अणु
			bytes_parsed += cx231xx_get_vbi_line(dev, dma_q,
				sav_eav,		       /* SAV/EAV */
				p_buffer + bytes_parsed,       /* p_buffer */
				buffer_size - bytes_parsed);   /* buffer size */
		पूर्ण

		/* Now parse data that is completely in this buffer */
		dma_q->is_partial_line = 0;

		जबतक (bytes_parsed < buffer_size) अणु
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed, /* buffer size */
				&bytes_used);	/* bytes used to get SAV/EAV */

			bytes_parsed += bytes_used;

			sav_eav &= 0xF0;
			अगर (sav_eav && (bytes_parsed < buffer_size)) अणु
				bytes_parsed += cx231xx_get_vbi_line(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffer+bytes_parsed, /* p_buffer */
					buffer_size-bytes_parsed);/*buf size*/
			पूर्ण
		पूर्ण

		/* Save the last four bytes of the buffer so we can
		check the buffer boundary condition next समय */
		स_नकल(dma_q->partial_buf, p_buffer + buffer_size - 4, 4);
		bytes_parsed = 0;
	पूर्ण

	वापस rc;
पूर्ण

/* ------------------------------------------------------------------
	Vbi buf operations
   ------------------------------------------------------------------*/

अटल पूर्णांक vbi_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);
	u32 height = 0;

	height = ((dev->norm & V4L2_STD_625_50) ?
		  PAL_VBI_LINES : NTSC_VBI_LINES);

	*nplanes = 1;
	sizes[0] = (dev->width * height * 2 * 2);
	वापस 0;
पूर्ण

/* This is called *without* dev->slock held; please keep it that way */
अटल पूर्णांक vbi_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vb->vb2_queue);
	u32 height = 0;
	u32 size;

	height = ((dev->norm & V4L2_STD_625_50) ?
		  PAL_VBI_LINES : NTSC_VBI_LINES);
	size = ((dev->width << 1) * height * 2);

	अगर (vb2_plane_size(vb, 0) < size)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, size);
	वापस 0;
पूर्ण

अटल व्योम vbi_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cx231xx_buffer *buf =
	    container_of(vb, काष्ठा cx231xx_buffer, vb.vb2_buf);
	काष्ठा cx231xx_dmaqueue *vidq = &dev->vbi_mode.vidq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->vbi_mode.slock, flags);
	list_add_tail(&buf->list, &vidq->active);
	spin_unlock_irqrestore(&dev->vbi_mode.slock, flags);
पूर्ण

अटल व्योम वापस_all_buffers(काष्ठा cx231xx *dev,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा cx231xx_dmaqueue *vidq = &dev->vbi_mode.vidq;
	काष्ठा cx231xx_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->vbi_mode.slock, flags);
	dev->vbi_mode.bulk_ctl.buf = शून्य;
	list_क्रम_each_entry_safe(buf, node, &vidq->active, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण
	spin_unlock_irqrestore(&dev->vbi_mode.slock, flags);
पूर्ण

अटल पूर्णांक vbi_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);
	काष्ठा cx231xx_dmaqueue *vidq = &dev->vbi_mode.vidq;
	पूर्णांक ret;

	vidq->sequence = 0;
	ret = cx231xx_init_vbi_isoc(dev, CX231XX_NUM_VBI_PACKETS,
				    CX231XX_NUM_VBI_BUFS,
				    dev->vbi_mode.alt_max_pkt_size[0],
				    cx231xx_isoc_vbi_copy);
	अगर (ret)
		वापस_all_buffers(dev, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम vbi_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);

	वापस_all_buffers(dev, VB2_BUF_STATE_ERROR);
पूर्ण

काष्ठा vb2_ops cx231xx_vbi_qops = अणु
	.queue_setup = vbi_queue_setup,
	.buf_prepare = vbi_buf_prepare,
	.buf_queue = vbi_buf_queue,
	.start_streaming = vbi_start_streaming,
	.stop_streaming = vbi_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

/* ------------------------------------------------------------------
	URB control
   ------------------------------------------------------------------*/

/*
 * IRQ callback, called by URB callback
 */
अटल व्योम cx231xx_irq_vbi_callback(काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	काष्ठा cx231xx_video_mode *vmode =
	    container_of(dma_q, काष्ठा cx231xx_video_mode, vidq);
	काष्ठा cx231xx *dev = container_of(vmode, काष्ठा cx231xx, vbi_mode);
	अचिन्हित दीर्घ flags;

	चयन (urb->status) अणु
	हाल 0:		/* success */
	हाल -ETIMEDOUT:	/* NAK */
		अवरोध;
	हाल -ECONNRESET:	/* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:		/* error */
		dev_err(dev->dev,
			"urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	/* Copy data from URB */
	spin_lock_irqsave(&dev->vbi_mode.slock, flags);
	dev->vbi_mode.bulk_ctl.bulk_copy(dev, urb);
	spin_unlock_irqrestore(&dev->vbi_mode.slock, flags);

	/* Reset status */
	urb->status = 0;

	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (urb->status) अणु
		dev_err(dev->dev, "urb resubmit failed (error=%i)\n",
			urb->status);
	पूर्ण
पूर्ण

/*
 * Stop and Deallocate URBs
 */
व्योम cx231xx_uninit_vbi_isoc(काष्ठा cx231xx *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	dev_dbg(dev->dev, "called cx231xx_uninit_vbi_isoc\n");

	dev->vbi_mode.bulk_ctl.nfields = -1;
	क्रम (i = 0; i < dev->vbi_mode.bulk_ctl.num_bufs; i++) अणु
		urb = dev->vbi_mode.bulk_ctl.urb[i];
		अगर (urb) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(urb);
			अन्यथा
				usb_unlink_urb(urb);

			अगर (dev->vbi_mode.bulk_ctl.transfer_buffer[i]) अणु

				kमुक्त(dev->vbi_mode.bulk_ctl.
				      transfer_buffer[i]);
				dev->vbi_mode.bulk_ctl.transfer_buffer[i] =
				    शून्य;
			पूर्ण
			usb_मुक्त_urb(urb);
			dev->vbi_mode.bulk_ctl.urb[i] = शून्य;
		पूर्ण
		dev->vbi_mode.bulk_ctl.transfer_buffer[i] = शून्य;
	पूर्ण

	kमुक्त(dev->vbi_mode.bulk_ctl.urb);
	kमुक्त(dev->vbi_mode.bulk_ctl.transfer_buffer);

	dev->vbi_mode.bulk_ctl.urb = शून्य;
	dev->vbi_mode.bulk_ctl.transfer_buffer = शून्य;
	dev->vbi_mode.bulk_ctl.num_bufs = 0;

	cx231xx_capture_start(dev, 0, Vbi);
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_uninit_vbi_isoc);

/*
 * Allocate URBs and start IRQ
 */
पूर्णांक cx231xx_init_vbi_isoc(काष्ठा cx231xx *dev, पूर्णांक max_packets,
			  पूर्णांक num_bufs, पूर्णांक max_pkt_size,
			  पूर्णांक (*bulk_copy) (काष्ठा cx231xx *dev,
					    काष्ठा urb *urb))
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = &dev->vbi_mode.vidq;
	पूर्णांक i;
	पूर्णांक sb_size, pipe;
	काष्ठा urb *urb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "called cx231xx_vbi_isoc\n");

	/* De-allocates all pending stuff */
	cx231xx_uninit_vbi_isoc(dev);

	/* clear अगर any halt */
	usb_clear_halt(dev->udev,
		       usb_rcvbulkpipe(dev->udev,
				       dev->vbi_mode.end_poपूर्णांक_addr));

	dev->vbi_mode.bulk_ctl.bulk_copy = bulk_copy;
	dev->vbi_mode.bulk_ctl.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_partial_line = 0;
	dma_q->last_sav = 0;
	dma_q->current_field = -1;
	dma_q->bytes_left_in_line = dev->width << 1;
	dma_q->lines_per_field = ((dev->norm & V4L2_STD_625_50) ?
				  PAL_VBI_LINES : NTSC_VBI_LINES);
	dma_q->lines_completed = 0;
	क्रम (i = 0; i < 8; i++)
		dma_q->partial_buf[i] = 0;

	dev->vbi_mode.bulk_ctl.urb = kसुस्मृति(num_bufs, माप(व्योम *),
					     GFP_KERNEL);
	अगर (!dev->vbi_mode.bulk_ctl.urb) अणु
		dev_err(dev->dev,
			"cannot alloc memory for usb buffers\n");
		वापस -ENOMEM;
	पूर्ण

	dev->vbi_mode.bulk_ctl.transfer_buffer =
	    kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!dev->vbi_mode.bulk_ctl.transfer_buffer) अणु
		dev_err(dev->dev,
			"cannot allocate memory for usbtransfer\n");
		kमुक्त(dev->vbi_mode.bulk_ctl.urb);
		वापस -ENOMEM;
	पूर्ण

	dev->vbi_mode.bulk_ctl.max_pkt_size = max_pkt_size;
	dev->vbi_mode.bulk_ctl.buf = शून्य;

	sb_size = max_packets * dev->vbi_mode.bulk_ctl.max_pkt_size;

	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < dev->vbi_mode.bulk_ctl.num_bufs; i++) अणु

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			cx231xx_uninit_vbi_isoc(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->vbi_mode.bulk_ctl.urb[i] = urb;
		urb->transfer_flags = 0;

		dev->vbi_mode.bulk_ctl.transfer_buffer[i] =
		    kzalloc(sb_size, GFP_KERNEL);
		अगर (!dev->vbi_mode.bulk_ctl.transfer_buffer[i]) अणु
			dev_err(dev->dev,
				"unable to allocate %i bytes for transfer buffer %i\n",
				sb_size, i);
			cx231xx_uninit_vbi_isoc(dev);
			वापस -ENOMEM;
		पूर्ण

		pipe = usb_rcvbulkpipe(dev->udev, dev->vbi_mode.end_poपूर्णांक_addr);
		usb_fill_bulk_urb(urb, dev->udev, pipe,
				  dev->vbi_mode.bulk_ctl.transfer_buffer[i],
				  sb_size, cx231xx_irq_vbi_callback, dma_q);
	पूर्ण

	init_रुकोqueue_head(&dma_q->wq);

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < dev->vbi_mode.bulk_ctl.num_bufs; i++) अणु
		rc = usb_submit_urb(dev->vbi_mode.bulk_ctl.urb[i], GFP_ATOMIC);
		अगर (rc) अणु
			dev_err(dev->dev,
				"submit of urb %i failed (error=%i)\n", i, rc);
			cx231xx_uninit_vbi_isoc(dev);
			वापस rc;
		पूर्ण
	पूर्ण

	cx231xx_capture_start(dev, 1, Vbi);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_init_vbi_isoc);

u32 cx231xx_get_vbi_line(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			 u8 sav_eav, u8 *p_buffer, u32 buffer_size)
अणु
	u32 bytes_copied = 0;
	पूर्णांक current_field = -1;

	चयन (sav_eav) अणु

	हाल SAV_VBI_FIELD1:
		current_field = 1;
		अवरोध;

	हाल SAV_VBI_FIELD2:
		current_field = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (current_field < 0)
		वापस bytes_copied;

	dma_q->last_sav = sav_eav;

	bytes_copied =
	    cx231xx_copy_vbi_line(dev, dma_q, p_buffer, buffer_size,
				  current_field);

	वापस bytes_copied;
पूर्ण

/*
 * Announces that a buffer were filled and request the next
 */
अटल अंतरभूत व्योम vbi_buffer_filled(काष्ठा cx231xx *dev,
				     काष्ठा cx231xx_dmaqueue *dma_q,
				     काष्ठा cx231xx_buffer *buf)
अणु
	/* Advice that buffer was filled */
	/* dev_dbg(dev->dev, "[%p/%d] wakeup\n", buf, buf->vb.index); */

	buf->vb.sequence = dma_q->sequence++;
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();

	dev->vbi_mode.bulk_ctl.buf = शून्य;

	list_del(&buf->list);
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

u32 cx231xx_copy_vbi_line(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			  u8 *p_line, u32 length, पूर्णांक field_number)
अणु
	u32 bytes_to_copy;
	काष्ठा cx231xx_buffer *buf;
	u32 _line_size = dev->width * 2;

	अगर (dma_q->current_field == -1) अणु
		/* Just starting up */
		cx231xx_reset_vbi_buffer(dev, dma_q);
	पूर्ण

	अगर (dma_q->current_field != field_number)
		dma_q->lines_completed = 0;

	/* get the buffer poपूर्णांकer */
	buf = dev->vbi_mode.bulk_ctl.buf;

	/* Remember the field number क्रम next समय */
	dma_q->current_field = field_number;

	bytes_to_copy = dma_q->bytes_left_in_line;
	अगर (bytes_to_copy > length)
		bytes_to_copy = length;

	अगर (dma_q->lines_completed >= dma_q->lines_per_field) अणु
		dma_q->bytes_left_in_line -= bytes_to_copy;
		dma_q->is_partial_line =
		    (dma_q->bytes_left_in_line == 0) ? 0 : 1;
		वापस 0;
	पूर्ण

	dma_q->is_partial_line = 1;

	/* If we करोn't have a buffer, just वापस the number of bytes we would
	   have copied अगर we had a buffer. */
	अगर (!buf) अणु
		dma_q->bytes_left_in_line -= bytes_to_copy;
		dma_q->is_partial_line =
		    (dma_q->bytes_left_in_line == 0) ? 0 : 1;
		वापस bytes_to_copy;
	पूर्ण

	/* copy the data to video buffer */
	cx231xx_करो_vbi_copy(dev, dma_q, p_line, bytes_to_copy);

	dma_q->pos += bytes_to_copy;
	dma_q->bytes_left_in_line -= bytes_to_copy;

	अगर (dma_q->bytes_left_in_line == 0) अणु

		dma_q->bytes_left_in_line = _line_size;
		dma_q->lines_completed++;
		dma_q->is_partial_line = 0;

		अगर (cx231xx_is_vbi_buffer_करोne(dev, dma_q) && buf) अणु

			vbi_buffer_filled(dev, dma_q, buf);

			dma_q->pos = 0;
			dma_q->lines_completed = 0;
			cx231xx_reset_vbi_buffer(dev, dma_q);
		पूर्ण
	पूर्ण

	वापस bytes_to_copy;
पूर्ण

/*
 * video-buf generic routine to get the next available buffer
 */
अटल अंतरभूत व्योम get_next_vbi_buf(काष्ठा cx231xx_dmaqueue *dma_q,
				    काष्ठा cx231xx_buffer **buf)
अणु
	काष्ठा cx231xx_video_mode *vmode =
	    container_of(dma_q, काष्ठा cx231xx_video_mode, vidq);
	काष्ठा cx231xx *dev = container_of(vmode, काष्ठा cx231xx, vbi_mode);
	अक्षर *outp;

	अगर (list_empty(&dma_q->active)) अणु
		dev_err(dev->dev, "No active queue to serve\n");
		dev->vbi_mode.bulk_ctl.buf = शून्य;
		*buf = शून्य;
		वापस;
	पूर्ण

	/* Get the next buffer */
	*buf = list_entry(dma_q->active.next, काष्ठा cx231xx_buffer, list);

	/* Cleans up buffer - Useful क्रम testing क्रम frame/URB loss */
	outp = vb2_plane_vaddr(&(*buf)->vb.vb2_buf, 0);
	स_रखो(outp, 0, vb2_plane_size(&(*buf)->vb.vb2_buf, 0));

	dev->vbi_mode.bulk_ctl.buf = *buf;

	वापस;
पूर्ण

व्योम cx231xx_reset_vbi_buffer(काष्ठा cx231xx *dev,
			      काष्ठा cx231xx_dmaqueue *dma_q)
अणु
	काष्ठा cx231xx_buffer *buf;

	buf = dev->vbi_mode.bulk_ctl.buf;

	अगर (buf == शून्य) अणु
		/* first try to get the buffer */
		get_next_vbi_buf(dma_q, &buf);

		dma_q->pos = 0;
		dma_q->current_field = -1;
	पूर्ण

	dma_q->bytes_left_in_line = dev->width << 1;
	dma_q->lines_completed = 0;
पूर्ण

पूर्णांक cx231xx_करो_vbi_copy(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			u8 *p_buffer, u32 bytes_to_copy)
अणु
	u8 *p_out_buffer = शून्य;
	u32 current_line_bytes_copied = 0;
	काष्ठा cx231xx_buffer *buf;
	u32 _line_size = dev->width << 1;
	व्योम *startग_लिखो;
	पूर्णांक offset, lencopy;

	buf = dev->vbi_mode.bulk_ctl.buf;

	अगर (buf == शून्य)
		वापस -EINVAL;

	p_out_buffer = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	अगर (dma_q->bytes_left_in_line != _line_size) अणु
		current_line_bytes_copied =
		    _line_size - dma_q->bytes_left_in_line;
	पूर्ण

	offset = (dma_q->lines_completed * _line_size) +
		 current_line_bytes_copied;

	अगर (dma_q->current_field == 2) अणु
		/* Populate the second half of the frame */
		offset += (dev->width * 2 * dma_q->lines_per_field);
	पूर्ण

	/* prepare destination address */
	startग_लिखो = p_out_buffer + offset;

	lencopy = dma_q->bytes_left_in_line > bytes_to_copy ?
		  bytes_to_copy : dma_q->bytes_left_in_line;

	स_नकल(startग_लिखो, p_buffer, lencopy);

	वापस 0;
पूर्ण

u8 cx231xx_is_vbi_buffer_करोne(काष्ठा cx231xx *dev,
			      काष्ठा cx231xx_dmaqueue *dma_q)
अणु
	u32 height = 0;

	height = ((dev->norm & V4L2_STD_625_50) ?
		  PAL_VBI_LINES : NTSC_VBI_LINES);
	अगर (dma_q->lines_completed == height && dma_q->current_field == 2)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण
