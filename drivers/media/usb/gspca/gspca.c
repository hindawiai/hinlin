<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Main USB camera driver
 *
 * Copyright (C) 2008-2011 Jean-Franथईois Moine <http://moinejf.मुक्त.fr>
 *
 * Camera button input handling by Mथँrton Nथऊmeth
 * Copyright (C) 2009-2010 Mथँrton Nथऊmeth <nm127@मुक्तmail.hu>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा GSPCA_VERSION	"2.14.0"

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kसमय.स>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

#समावेश "gspca.h"

#अगर IS_ENABLED(CONFIG_INPUT)
#समावेश <linux/input.h>
#समावेश <linux/usb/input.h>
#पूर्ण_अगर

/* global values */
#घोषणा DEF_NURBS 3		/* शेष number of URBs */
#अगर DEF_NURBS > MAX_NURBS
#त्रुटि "DEF_NURBS too big"
#पूर्ण_अगर

MODULE_AUTHOR("Jean-Franथईois Moine <http://moinejf.free.fr>");
MODULE_DESCRIPTION("GSPCA USB Camera Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(GSPCA_VERSION);

पूर्णांक gspca_debug;
EXPORT_SYMBOL(gspca_debug);

अटल व्योम PDEBUG_MODE(काष्ठा gspca_dev *gspca_dev, पूर्णांक debug, अक्षर *txt,
			__u32 pixfmt, पूर्णांक w, पूर्णांक h)
अणु
	अगर ((pixfmt >> 24) >= '0' && (pixfmt >> 24) <= 'z') अणु
		gspca_dbg(gspca_dev, debug, "%s %c%c%c%c %dx%d\n",
			  txt,
			  pixfmt & 0xff,
			  (pixfmt >> 8) & 0xff,
			  (pixfmt >> 16) & 0xff,
			  pixfmt >> 24,
			  w, h);
	पूर्ण अन्यथा अणु
		gspca_dbg(gspca_dev, debug, "%s 0x%08x %dx%d\n",
			  txt,
			  pixfmt,
			  w, h);
	पूर्ण
पूर्ण

/* specअगरic memory types - !! should be dअगरferent from V4L2_MEMORY_xxx */
#घोषणा GSPCA_MEMORY_NO 0	/* V4L2_MEMORY_xxx starts from 1 */
#घोषणा GSPCA_MEMORY_READ 7

/*
 * Input and पूर्णांकerrupt endpoपूर्णांक handling functions
 */
#अगर IS_ENABLED(CONFIG_INPUT)
अटल व्योम पूर्णांक_irq(काष्ठा urb *urb)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) urb->context;
	पूर्णांक ret;

	ret = urb->status;
	चयन (ret) अणु
	हाल 0:
		अगर (gspca_dev->sd_desc->पूर्णांक_pkt_scan(gspca_dev,
		    urb->transfer_buffer, urb->actual_length) < 0) अणु
			gspca_err(gspca_dev, "Unknown packet received\n");
		पूर्ण
		अवरोध;

	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		/* Stop is requested either by software or hardware is gone,
		 * keep the ret value non-zero and करोn't resubmit later.
		 */
		अवरोध;

	शेष:
		gspca_err(gspca_dev, "URB error %i, resubmitting\n",
			  urb->status);
		urb->status = 0;
		ret = 0;
	पूर्ण

	अगर (ret == 0) अणु
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0)
			pr_err("Resubmit URB failed with error %i\n", ret);
	पूर्ण
पूर्ण

अटल पूर्णांक gspca_input_connect(काष्ठा gspca_dev *dev)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक err = 0;

	dev->input_dev = शून्य;
	अगर (dev->sd_desc->पूर्णांक_pkt_scan || dev->sd_desc->other_input)  अणु
		input_dev = input_allocate_device();
		अगर (!input_dev)
			वापस -ENOMEM;

		usb_make_path(dev->dev, dev->phys, माप(dev->phys));
		strlcat(dev->phys, "/input0", माप(dev->phys));

		input_dev->name = dev->sd_desc->name;
		input_dev->phys = dev->phys;

		usb_to_input_id(dev->dev, &input_dev->id);

		input_dev->evbit[0] = BIT_MASK(EV_KEY);
		input_dev->keybit[BIT_WORD(KEY_CAMERA)] = BIT_MASK(KEY_CAMERA);
		input_dev->dev.parent = &dev->dev->dev;

		err = input_रेजिस्टर_device(input_dev);
		अगर (err) अणु
			pr_err("Input device registration failed with error %i\n",
			       err);
			input_dev->dev.parent = शून्य;
			input_मुक्त_device(input_dev);
		पूर्ण अन्यथा अणु
			dev->input_dev = input_dev;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक alloc_and_submit_पूर्णांक_urb(काष्ठा gspca_dev *gspca_dev,
			  काष्ठा usb_endpoपूर्णांक_descriptor *ep)
अणु
	अचिन्हित पूर्णांक buffer_len;
	पूर्णांक पूर्णांकerval;
	काष्ठा urb *urb;
	काष्ठा usb_device *dev;
	व्योम *buffer = शून्य;
	पूर्णांक ret = -EINVAL;

	buffer_len = le16_to_cpu(ep->wMaxPacketSize);
	पूर्णांकerval = ep->bInterval;
	gspca_dbg(gspca_dev, D_CONF, "found int in endpoint: 0x%x, buffer_len=%u, interval=%u\n",
		  ep->bEndpoपूर्णांकAddress, buffer_len, पूर्णांकerval);

	dev = gspca_dev->dev;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	buffer = usb_alloc_coherent(dev, buffer_len,
				GFP_KERNEL, &urb->transfer_dma);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ error_buffer;
	पूर्ण
	usb_fill_पूर्णांक_urb(urb, dev,
		usb_rcvपूर्णांकpipe(dev, ep->bEndpoपूर्णांकAddress),
		buffer, buffer_len,
		पूर्णांक_irq, (व्योम *)gspca_dev, पूर्णांकerval);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "submit int URB failed with error %i\n",
			  ret);
		जाओ error_submit;
	पूर्ण
	gspca_dev->पूर्णांक_urb = urb;
	वापस ret;

error_submit:
	usb_मुक्त_coherent(dev,
			  urb->transfer_buffer_length,
			  urb->transfer_buffer,
			  urb->transfer_dma);
error_buffer:
	usb_मुक्त_urb(urb);
error:
	वापस ret;
पूर्ण

अटल व्योम gspca_input_create_urb(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	पूर्णांक i;

	अगर (gspca_dev->sd_desc->पूर्णांक_pkt_scan)  अणु
		पूर्णांकf = usb_अगरnum_to_अगर(gspca_dev->dev, gspca_dev->अगरace);
		पूर्णांकf_desc = पूर्णांकf->cur_altsetting;
		क्रम (i = 0; i < पूर्णांकf_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
			ep = &पूर्णांकf_desc->endpoपूर्णांक[i].desc;
			अगर (usb_endpoपूर्णांक_dir_in(ep) &&
			    usb_endpoपूर्णांक_xfer_पूर्णांक(ep)) अणु

				alloc_and_submit_पूर्णांक_urb(gspca_dev, ep);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gspca_input_destroy_urb(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा urb *urb;

	urb = gspca_dev->पूर्णांक_urb;
	अगर (urb) अणु
		gspca_dev->पूर्णांक_urb = शून्य;
		usb_समाप्त_urb(urb);
		usb_मुक्त_coherent(gspca_dev->dev,
				  urb->transfer_buffer_length,
				  urb->transfer_buffer,
				  urb->transfer_dma);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम gspca_input_destroy_urb(काष्ठा gspca_dev *gspca_dev)
अणु
पूर्ण

अटल अंतरभूत व्योम gspca_input_create_urb(काष्ठा gspca_dev *gspca_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक gspca_input_connect(काष्ठा gspca_dev *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * fill a video frame from an URB and resubmit
 */
अटल व्योम fill_frame(काष्ठा gspca_dev *gspca_dev,
			काष्ठा urb *urb)
अणु
	u8 *data;		/* address of data in the iso message */
	पूर्णांक i, len, st;
	cam_pkt_op pkt_scan;

	अगर (urb->status != 0) अणु
		अगर (urb->status == -ESHUTDOWN)
			वापस;		/* disconnection */
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			वापस;
#पूर्ण_अगर
		gspca_err(gspca_dev, "urb status: %d\n", urb->status);
		urb->status = 0;
		जाओ resubmit;
	पूर्ण
	pkt_scan = gspca_dev->sd_desc->pkt_scan;
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		len = urb->iso_frame_desc[i].actual_length;

		/* check the packet status and length */
		st = urb->iso_frame_desc[i].status;
		अगर (st) अणु
			gspca_dbg(gspca_dev, D_PACK, "ISOC data error: [%d] len=%d, status=%d\n",
			       i, len, st);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			जारी;
		पूर्ण
		अगर (len == 0) अणु
			अगर (gspca_dev->empty_packet == 0)
				gspca_dev->empty_packet = 1;
			जारी;
		पूर्ण

		/* let the packet be analyzed by the subdriver */
		gspca_dbg(gspca_dev, D_PACK, "packet [%d] o:%d l:%d\n",
			  i, urb->iso_frame_desc[i].offset, len);
		data = (u8 *) urb->transfer_buffer
					+ urb->iso_frame_desc[i].offset;
		pkt_scan(gspca_dev, data, len);
	पूर्ण

resubmit:
	अगर (!gspca_dev->streaming)
		वापस;
	/* resubmit the URB */
	st = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (st < 0)
		pr_err("usb_submit_urb() ret %d\n", st);
पूर्ण

/*
 * ISOC message पूर्णांकerrupt from the USB device
 *
 * Analyse each packet and call the subdriver क्रम copy to the frame buffer.
 */
अटल व्योम isoc_irq(काष्ठा urb *urb)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) urb->context;

	gspca_dbg(gspca_dev, D_PACK, "isoc irq\n");
	अगर (!gspca_dev->streaming)
		वापस;
	fill_frame(gspca_dev, urb);
पूर्ण

/*
 * bulk message पूर्णांकerrupt from the USB device
 */
अटल व्योम bulk_irq(काष्ठा urb *urb)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) urb->context;
	पूर्णांक st;

	gspca_dbg(gspca_dev, D_PACK, "bulk irq\n");
	अगर (!gspca_dev->streaming)
		वापस;
	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ESHUTDOWN:
		वापस;		/* disconnection */
	शेष:
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			वापस;
#पूर्ण_अगर
		gspca_err(gspca_dev, "urb status: %d\n", urb->status);
		urb->status = 0;
		जाओ resubmit;
	पूर्ण

	gspca_dbg(gspca_dev, D_PACK, "packet l:%d\n", urb->actual_length);
	gspca_dev->sd_desc->pkt_scan(gspca_dev,
				urb->transfer_buffer,
				urb->actual_length);

resubmit:
	अगर (!gspca_dev->streaming)
		वापस;
	/* resubmit the URB */
	अगर (gspca_dev->cam.bulk_nurbs != 0) अणु
		st = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (st < 0)
			pr_err("usb_submit_urb() ret %d\n", st);
	पूर्ण
पूर्ण

/*
 * add data to the current frame
 *
 * This function is called by the subdrivers at पूर्णांकerrupt level.
 *
 * To build a frame, these ones must add
 *	- one FIRST_PACKET
 *	- 0 or many INTER_PACKETs
 *	- one LAST_PACKET
 * DISCARD_PACKET invalidates the whole frame.
 */
व्योम gspca_frame_add(काष्ठा gspca_dev *gspca_dev,
			क्रमागत gspca_packet_type packet_type,
			स्थिर u8 *data,
			पूर्णांक len)
अणु
	काष्ठा gspca_buffer *buf;
	अचिन्हित दीर्घ flags;

	gspca_dbg(gspca_dev, D_PACK, "add t:%d l:%d\n",	packet_type, len);

	spin_lock_irqsave(&gspca_dev->qlock, flags);
	buf = list_first_entry_or_null(&gspca_dev->buf_list,
				       typeof(*buf), list);
	spin_unlock_irqrestore(&gspca_dev->qlock, flags);

	अगर (packet_type == FIRST_PACKET) अणु
		/* अगर there is no queued buffer, discard the whole frame */
		अगर (!buf) अणु
			gspca_dev->last_packet_type = DISCARD_PACKET;
			gspca_dev->sequence++;
			वापस;
		पूर्ण
		gspca_dev->image = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
		gspca_dev->image_len = 0;
	पूर्ण अन्यथा अणु
		चयन (gspca_dev->last_packet_type) अणु
		हाल DISCARD_PACKET:
			अगर (packet_type == LAST_PACKET) अणु
				gspca_dev->last_packet_type = packet_type;
				gspca_dev->image = शून्य;
				gspca_dev->image_len = 0;
			पूर्ण
			वापस;
		हाल LAST_PACKET:
			वापस;
		पूर्ण
	पूर्ण

	/* append the packet to the frame buffer */
	अगर (len > 0) अणु
		अगर (gspca_dev->image_len + len > PAGE_ALIGN(gspca_dev->pixfmt.sizeimage)) अणु
			gspca_err(gspca_dev, "frame overflow %d > %d\n",
				  gspca_dev->image_len + len,
				  PAGE_ALIGN(gspca_dev->pixfmt.sizeimage));
			packet_type = DISCARD_PACKET;
		पूर्ण अन्यथा अणु
/* !! image is शून्य only when last pkt is LAST or DISCARD
			अगर (gspca_dev->image == शून्य) अणु
				pr_err("gspca_frame_add() image == NULL\n");
				वापस;
			पूर्ण
 */
			स_नकल(gspca_dev->image + gspca_dev->image_len,
				data, len);
			gspca_dev->image_len += len;
		पूर्ण
	पूर्ण
	gspca_dev->last_packet_type = packet_type;

	/* अगर last packet, invalidate packet concatenation until
	 * next first packet, wake up the application and advance
	 * in the queue */
	अगर (packet_type == LAST_PACKET) अणु
		spin_lock_irqsave(&gspca_dev->qlock, flags);
		list_del(&buf->list);
		spin_unlock_irqrestore(&gspca_dev->qlock, flags);
		buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		vb2_set_plane_payload(&buf->vb.vb2_buf, 0,
				      gspca_dev->image_len);
		buf->vb.sequence = gspca_dev->sequence++;
		buf->vb.field = V4L2_FIELD_NONE;
		gspca_dbg(gspca_dev, D_FRAM, "frame complete len:%d\n",
			  gspca_dev->image_len);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		gspca_dev->image = शून्य;
		gspca_dev->image_len = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(gspca_frame_add);

अटल व्योम destroy_urbs(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक i;

	gspca_dbg(gspca_dev, D_STREAM, "kill transfer\n");

	/* Killing all URBs guarantee that no URB completion
	 * handler is running. Thereक्रमe, there shouldn't
	 * be anyone trying to access gspca_dev->urb[i]
	 */
	क्रम (i = 0; i < MAX_NURBS; i++)
		usb_समाप्त_urb(gspca_dev->urb[i]);

	gspca_dbg(gspca_dev, D_STREAM, "releasing urbs\n");
	क्रम (i = 0; i < MAX_NURBS; i++) अणु
		urb = gspca_dev->urb[i];
		अगर (!urb)
			जारी;
		gspca_dev->urb[i] = शून्य;
		usb_मुक्त_coherent(gspca_dev->dev,
				  urb->transfer_buffer_length,
				  urb->transfer_buffer,
				  urb->transfer_dma);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक gspca_set_alt0(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->alt == 0)
		वापस 0;
	ret = usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace, 0);
	अगर (ret < 0)
		pr_err("set alt 0 err %d\n", ret);
	वापस ret;
पूर्ण

/*
 * look क्रम an input transfer endpoपूर्णांक in an alternate setting.
 *
 * If xfer_ep is invalid, वापस the first valid ep found, otherwise
 * look क्रम exactly the ep with address equal to xfer_ep.
 */
अटल काष्ठा usb_host_endpoपूर्णांक *alt_xfer(काष्ठा usb_host_पूर्णांकerface *alt,
					  पूर्णांक xfer, पूर्णांक xfer_ep)
अणु
	काष्ठा usb_host_endpoपूर्णांक *ep;
	पूर्णांक i, attr;

	क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep = &alt->endpoपूर्णांक[i];
		attr = ep->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
		अगर (attr == xfer
		    && ep->desc.wMaxPacketSize != 0
		    && usb_endpoपूर्णांक_dir_in(&ep->desc)
		    && (xfer_ep < 0 || ep->desc.bEndpoपूर्णांकAddress == xfer_ep))
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

/* compute the minimum bandwidth क्रम the current transfer */
अटल u32 which_bandwidth(काष्ठा gspca_dev *gspca_dev)
अणु
	u32 bandwidth;

	/* get the (max) image size */
	bandwidth = gspca_dev->pixfmt.sizeimage;

	/* अगर the image is compressed, estimate its mean size */
	अगर (!gspca_dev->cam.needs_full_bandwidth &&
	    bandwidth < gspca_dev->pixfmt.width *
				gspca_dev->pixfmt.height)
		bandwidth = bandwidth * 3 / 8;	/* 0.375 */

	/* estimate the frame rate */
	अगर (gspca_dev->sd_desc->get_streamparm) अणु
		काष्ठा v4l2_streamparm parm;

		gspca_dev->sd_desc->get_streamparm(gspca_dev, &parm);
		bandwidth *= parm.parm.capture.समयperframe.denominator;
		bandwidth /= parm.parm.capture.समयperframe.numerator;
	पूर्ण अन्यथा अणु

		/* करोn't hope more than 15 fps with USB 1.1 and
		 * image resolution >= 640x480 */
		अगर (gspca_dev->pixfmt.width >= 640
		 && gspca_dev->dev->speed == USB_SPEED_FULL)
			bandwidth *= 15;		/* 15 fps */
		अन्यथा
			bandwidth *= 30;		/* 30 fps */
	पूर्ण

	gspca_dbg(gspca_dev, D_STREAM, "min bandwidth: %d\n", bandwidth);
	वापस bandwidth;
पूर्ण

/* endpoपूर्णांक table */
#घोषणा MAX_ALT 16
काष्ठा ep_tb_s अणु
	u32 alt;
	u32 bandwidth;
पूर्ण;

/*
 * build the table of the endpoपूर्णांकs
 * and compute the minimum bandwidth क्रम the image transfer
 */
अटल पूर्णांक build_isoc_ep_tb(काष्ठा gspca_dev *gspca_dev,
			काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			काष्ठा ep_tb_s *ep_tb)
अणु
	काष्ठा usb_host_endpoपूर्णांक *ep;
	पूर्णांक i, j, nbalt, psize, found;
	u32 bandwidth, last_bw;

	nbalt = पूर्णांकf->num_altsetting;
	अगर (nbalt > MAX_ALT)
		nbalt = MAX_ALT;	/* fixme: should warn */

	/* build the endpoपूर्णांक table */
	i = 0;
	last_bw = 0;
	क्रम (;;) अणु
		ep_tb->bandwidth = 2000 * 2000 * 120;
		found = 0;
		क्रम (j = 0; j < nbalt; j++) अणु
			ep = alt_xfer(&पूर्णांकf->altsetting[j],
				      USB_ENDPOINT_XFER_ISOC,
				      gspca_dev->xfer_ep);
			अगर (ep == शून्य)
				जारी;
			अगर (ep->desc.bInterval == 0) अणु
				pr_err("alt %d iso endp with 0 interval\n", j);
				जारी;
			पूर्ण
			psize = le16_to_cpu(ep->desc.wMaxPacketSize);
			psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
			bandwidth = psize * 1000;
			अगर (gspca_dev->dev->speed == USB_SPEED_HIGH
			 || gspca_dev->dev->speed >= USB_SPEED_SUPER)
				bandwidth *= 8;
			bandwidth /= 1 << (ep->desc.bInterval - 1);
			अगर (bandwidth <= last_bw)
				जारी;
			अगर (bandwidth < ep_tb->bandwidth) अणु
				ep_tb->bandwidth = bandwidth;
				ep_tb->alt = j;
				found = 1;
			पूर्ण
		पूर्ण
		अगर (!found)
			अवरोध;
		gspca_dbg(gspca_dev, D_STREAM, "alt %d bandwidth %d\n",
			  ep_tb->alt, ep_tb->bandwidth);
		last_bw = ep_tb->bandwidth;
		i++;
		ep_tb++;
	पूर्ण

	/*
	 * If the camera:
	 * has a usb audio class पूर्णांकerface (a built in usb mic); and
	 * is a usb 1 full speed device; and
	 * uses the max full speed iso bandwidth; and
	 * and has more than 1 alt setting
	 * then skip the highest alt setting to spare bandwidth क्रम the mic
	 */
	अगर (gspca_dev->audio &&
			gspca_dev->dev->speed == USB_SPEED_FULL &&
			last_bw >= 1000000 &&
			i > 1) अणु
		gspca_dbg(gspca_dev, D_STREAM, "dev has usb audio, skipping highest alt\n");
		i--;
		ep_tb--;
	पूर्ण

	/* get the requested bandwidth and start at the highest atlsetting */
	bandwidth = which_bandwidth(gspca_dev);
	ep_tb--;
	जबतक (i > 1) अणु
		ep_tb--;
		अगर (ep_tb->bandwidth < bandwidth)
			अवरोध;
		i--;
	पूर्ण
	वापस i;
पूर्ण

/*
 * create the URBs क्रम image transfer
 */
अटल पूर्णांक create_urbs(काष्ठा gspca_dev *gspca_dev,
			काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा urb *urb;
	पूर्णांक n, nurbs, i, psize, npkt, bsize;

	/* calculate the packet size and the number of packets */
	psize = le16_to_cpu(ep->desc.wMaxPacketSize);

	अगर (!gspca_dev->cam.bulk) अणु		/* isoc */

		/* See paragraph 5.9 / table 5-11 of the usb 2.0 spec. */
		अगर (gspca_dev->pkt_size == 0)
			psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
		अन्यथा
			psize = gspca_dev->pkt_size;
		npkt = gspca_dev->cam.npkt;
		अगर (npkt == 0)
			npkt = 32;		/* शेष value */
		bsize = psize * npkt;
		gspca_dbg(gspca_dev, D_STREAM,
			  "isoc %d pkts size %d = bsize:%d\n",
			  npkt, psize, bsize);
		nurbs = DEF_NURBS;
	पूर्ण अन्यथा अणु				/* bulk */
		npkt = 0;
		bsize = gspca_dev->cam.bulk_size;
		अगर (bsize == 0)
			bsize = psize;
		gspca_dbg(gspca_dev, D_STREAM, "bulk bsize:%d\n", bsize);
		अगर (gspca_dev->cam.bulk_nurbs != 0)
			nurbs = gspca_dev->cam.bulk_nurbs;
		अन्यथा
			nurbs = 1;
	पूर्ण

	क्रम (n = 0; n < nurbs; n++) अणु
		urb = usb_alloc_urb(npkt, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		gspca_dev->urb[n] = urb;
		urb->transfer_buffer = usb_alloc_coherent(gspca_dev->dev,
						bsize,
						GFP_KERNEL,
						&urb->transfer_dma);

		अगर (urb->transfer_buffer == शून्य) अणु
			pr_err("usb_alloc_coherent failed\n");
			वापस -ENOMEM;
		पूर्ण
		urb->dev = gspca_dev->dev;
		urb->context = gspca_dev;
		urb->transfer_buffer_length = bsize;
		अगर (npkt != 0) अणु		/* ISOC */
			urb->pipe = usb_rcvisocpipe(gspca_dev->dev,
						    ep->desc.bEndpoपूर्णांकAddress);
			urb->transfer_flags = URB_ISO_ASAP
					| URB_NO_TRANSFER_DMA_MAP;
			urb->पूर्णांकerval = 1 << (ep->desc.bInterval - 1);
			urb->complete = isoc_irq;
			urb->number_of_packets = npkt;
			क्रम (i = 0; i < npkt; i++) अणु
				urb->iso_frame_desc[i].length = psize;
				urb->iso_frame_desc[i].offset = psize * i;
			पूर्ण
		पूर्ण अन्यथा अणु		/* bulk */
			urb->pipe = usb_rcvbulkpipe(gspca_dev->dev,
						ep->desc.bEndpoपूर्णांकAddress);
			urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
			urb->complete = bulk_irq;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Note: both the queue and the usb locks should be held when calling this */
अटल व्योम gspca_stream_off(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dev->streaming = false;
	gspca_dev->usb_err = 0;
	अगर (gspca_dev->sd_desc->stopN)
		gspca_dev->sd_desc->stopN(gspca_dev);
	destroy_urbs(gspca_dev);
	gspca_input_destroy_urb(gspca_dev);
	gspca_set_alt0(gspca_dev);
	अगर (gspca_dev->present)
		gspca_input_create_urb(gspca_dev);
	अगर (gspca_dev->sd_desc->stop0)
		gspca_dev->sd_desc->stop0(gspca_dev);
	gspca_dbg(gspca_dev, D_STREAM, "stream off OK\n");
पूर्ण

/*
 * start the USB transfer
 */
अटल पूर्णांक gspca_init_transfer(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा urb *urb;
	काष्ठा ep_tb_s ep_tb[MAX_ALT];
	पूर्णांक n, ret, xfer, alt, alt_idx;

	/* reset the streaming variables */
	gspca_dev->image = शून्य;
	gspca_dev->image_len = 0;
	gspca_dev->last_packet_type = DISCARD_PACKET;

	gspca_dev->usb_err = 0;

	/* करो the specअगरic subdriver stuff beक्रमe endpoपूर्णांक selection */
	पूर्णांकf = usb_अगरnum_to_अगर(gspca_dev->dev, gspca_dev->अगरace);
	gspca_dev->alt = gspca_dev->cam.bulk ? पूर्णांकf->num_altsetting : 0;
	अगर (gspca_dev->sd_desc->isoc_init) अणु
		ret = gspca_dev->sd_desc->isoc_init(gspca_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	xfer = gspca_dev->cam.bulk ? USB_ENDPOINT_XFER_BULK
				   : USB_ENDPOINT_XFER_ISOC;

	/* अगर bulk or the subdriver क्रमced an altsetting, get the endpoपूर्णांक */
	अगर (gspca_dev->alt != 0) अणु
		gspca_dev->alt--;	/* (previous version compatibility) */
		ep = alt_xfer(&पूर्णांकf->altsetting[gspca_dev->alt], xfer,
			      gspca_dev->xfer_ep);
		अगर (ep == शून्य) अणु
			pr_err("bad altsetting %d\n", gspca_dev->alt);
			वापस -EIO;
		पूर्ण
		ep_tb[0].alt = gspca_dev->alt;
		alt_idx = 1;
	पूर्ण अन्यथा अणु
		/* अन्यथा, compute the minimum bandwidth
		 * and build the endpoपूर्णांक table */
		alt_idx = build_isoc_ep_tb(gspca_dev, पूर्णांकf, ep_tb);
		अगर (alt_idx <= 0) अणु
			pr_err("no transfer endpoint found\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* set the highest alternate setting and
	 * loop until urb submit succeeds */
	gspca_input_destroy_urb(gspca_dev);

	gspca_dev->alt = ep_tb[--alt_idx].alt;
	alt = -1;
	क्रम (;;) अणु
		अगर (alt != gspca_dev->alt) अणु
			alt = gspca_dev->alt;
			अगर (पूर्णांकf->num_altsetting > 1) अणु
				ret = usb_set_पूर्णांकerface(gspca_dev->dev,
							gspca_dev->अगरace,
							alt);
				अगर (ret < 0) अणु
					अगर (ret == -ENOSPC)
						जाओ retry; /*fixme: ugly*/
					pr_err("set alt %d err %d\n", alt, ret);
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!gspca_dev->cam.no_urb_create) अणु
			gspca_dbg(gspca_dev, D_STREAM, "init transfer alt %d\n",
				  alt);
			ret = create_urbs(gspca_dev,
				alt_xfer(&पूर्णांकf->altsetting[alt], xfer,
					 gspca_dev->xfer_ep));
			अगर (ret < 0) अणु
				destroy_urbs(gspca_dev);
				जाओ out;
			पूर्ण
		पूर्ण

		/* clear the bulk endpoपूर्णांक */
		अगर (gspca_dev->cam.bulk)
			usb_clear_halt(gspca_dev->dev,
					gspca_dev->urb[0]->pipe);

		/* start the cam */
		ret = gspca_dev->sd_desc->start(gspca_dev);
		अगर (ret < 0) अणु
			destroy_urbs(gspca_dev);
			जाओ out;
		पूर्ण
		v4l2_ctrl_handler_setup(gspca_dev->vdev.ctrl_handler);
		gspca_dev->streaming = true;

		/* some bulk transfers are started by the subdriver */
		अगर (gspca_dev->cam.bulk && gspca_dev->cam.bulk_nurbs == 0)
			अवरोध;

		/* submit the URBs */
		क्रम (n = 0; n < MAX_NURBS; n++) अणु
			urb = gspca_dev->urb[n];
			अगर (urb == शून्य)
				अवरोध;
			ret = usb_submit_urb(urb, GFP_KERNEL);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		अगर (ret >= 0)
			अवरोध;			/* transfer is started */

		/* something when wrong
		 * stop the webcam and मुक्त the transfer resources */
		gspca_stream_off(gspca_dev);
		अगर (ret != -ENOSPC) अणु
			pr_err("usb_submit_urb alt %d err %d\n",
			       gspca_dev->alt, ret);
			जाओ out;
		पूर्ण

		/* the bandwidth is not wide enough
		 * negotiate or try a lower alternate setting */
retry:
		gspca_err(gspca_dev, "alt %d - bandwidth not wide enough, trying again\n",
			  alt);
		msleep(20);	/* रुको क्रम समाप्त complete */
		अगर (gspca_dev->sd_desc->isoc_nego) अणु
			ret = gspca_dev->sd_desc->isoc_nego(gspca_dev);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (alt_idx <= 0) अणु
				pr_err("no transfer endpoint found\n");
				ret = -EIO;
				जाओ out;
			पूर्ण
			gspca_dev->alt = ep_tb[--alt_idx].alt;
		पूर्ण
	पूर्ण
out:
	gspca_input_create_urb(gspca_dev);
	वापस ret;
पूर्ण

अटल व्योम gspca_set_शेष_mode(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;

	i = gspca_dev->cam.nmodes - 1;	/* take the highest mode */
	gspca_dev->curr_mode = i;
	gspca_dev->pixfmt = gspca_dev->cam.cam_mode[i];

	/* करोes nothing अगर ctrl_handler == शून्य */
	v4l2_ctrl_handler_setup(gspca_dev->vdev.ctrl_handler);
पूर्ण

अटल पूर्णांक wxh_to_mode(काष्ठा gspca_dev *gspca_dev,
			पूर्णांक width, पूर्णांक height, u32 pixelक्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gspca_dev->cam.nmodes; i++) अणु
		अगर (width == gspca_dev->cam.cam_mode[i].width
		    && height == gspca_dev->cam.cam_mode[i].height
		    && pixelक्रमmat == gspca_dev->cam.cam_mode[i].pixelक्रमmat)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wxh_to_nearest_mode(काष्ठा gspca_dev *gspca_dev,
			पूर्णांक width, पूर्णांक height, u32 pixelक्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = gspca_dev->cam.nmodes; --i >= 0; ) अणु
		अगर (width >= gspca_dev->cam.cam_mode[i].width
		    && height >= gspca_dev->cam.cam_mode[i].height
		    && pixelक्रमmat == gspca_dev->cam.cam_mode[i].pixelक्रमmat)
			वापस i;
	पूर्ण
	क्रम (i = gspca_dev->cam.nmodes; --i > 0; ) अणु
		अगर (width >= gspca_dev->cam.cam_mode[i].width
		    && height >= gspca_dev->cam.cam_mode[i].height)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

/*
 * search a mode with the right pixel क्रमmat
 */
अटल पूर्णांक gspca_get_mode(काष्ठा gspca_dev *gspca_dev,
			पूर्णांक mode,
			पूर्णांक pixfmt)
अणु
	पूर्णांक modeU, modeD;

	modeU = modeD = mode;
	जबतक ((modeU < gspca_dev->cam.nmodes) || modeD >= 0) अणु
		अगर (--modeD >= 0) अणु
			अगर (gspca_dev->cam.cam_mode[modeD].pixelक्रमmat
								== pixfmt)
				वापस modeD;
		पूर्ण
		अगर (++modeU < gspca_dev->cam.nmodes) अणु
			अगर (gspca_dev->cam.cam_mode[modeU].pixelक्रमmat
								== pixfmt)
				वापस modeU;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_chip_info(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_dbg_chip_info *chip)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	gspca_dev->usb_err = 0;
	अगर (gspca_dev->sd_desc->get_chip_info)
		वापस gspca_dev->sd_desc->get_chip_info(gspca_dev, chip);
	वापस chip->match.addr ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	gspca_dev->usb_err = 0;
	वापस gspca_dev->sd_desc->get_रेजिस्टर(gspca_dev, reg);
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	gspca_dev->usb_err = 0;
	वापस gspca_dev->sd_desc->set_रेजिस्टर(gspca_dev, reg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_fmtdesc *fmtdesc)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);
	पूर्णांक i, j, index;
	__u32 fmt_tb[8];

	/* give an index to each क्रमmat */
	index = 0;
	क्रम (i = gspca_dev->cam.nmodes; --i >= 0; ) अणु
		fmt_tb[index] = gspca_dev->cam.cam_mode[i].pixelक्रमmat;
		j = 0;
		क्रम (;;) अणु
			अगर (fmt_tb[j] == fmt_tb[index])
				अवरोध;
			j++;
		पूर्ण
		अगर (j == index) अणु
			अगर (fmtdesc->index == index)
				अवरोध;		/* new क्रमmat */
			index++;
			अगर (index >= ARRAY_SIZE(fmt_tb))
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (i < 0)
		वापस -EINVAL;		/* no more क्रमmat */

	fmtdesc->pixelक्रमmat = fmt_tb[index];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *_priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);
	u32 priv = fmt->fmt.pix.priv;

	fmt->fmt.pix = gspca_dev->pixfmt;
	/* some drivers use priv पूर्णांकernally, so keep the original value */
	fmt->fmt.pix.priv = priv;
	वापस 0;
पूर्ण

अटल पूर्णांक try_fmt_vid_cap(काष्ठा gspca_dev *gspca_dev,
			काष्ठा v4l2_क्रमmat *fmt)
अणु
	पूर्णांक w, h, mode, mode2;

	w = fmt->fmt.pix.width;
	h = fmt->fmt.pix.height;

	PDEBUG_MODE(gspca_dev, D_CONF, "try fmt cap",
		    fmt->fmt.pix.pixelक्रमmat, w, h);

	/* search the nearest mode क्रम width and height */
	mode = wxh_to_nearest_mode(gspca_dev, w, h, fmt->fmt.pix.pixelक्रमmat);

	/* OK अगर right palette */
	अगर (gspca_dev->cam.cam_mode[mode].pixelक्रमmat
						!= fmt->fmt.pix.pixelक्रमmat) अणु

		/* अन्यथा, search the बंदst mode with the same pixel क्रमmat */
		mode2 = gspca_get_mode(gspca_dev, mode,
					fmt->fmt.pix.pixelक्रमmat);
		अगर (mode2 >= 0)
			mode = mode2;
	पूर्ण
	fmt->fmt.pix = gspca_dev->cam.cam_mode[mode];
	अगर (gspca_dev->sd_desc->try_fmt) अणु
		/* pass original resolution to subdriver try_fmt */
		fmt->fmt.pix.width = w;
		fmt->fmt.pix.height = h;
		gspca_dev->sd_desc->try_fmt(gspca_dev, fmt);
	पूर्ण
	वापस mode;			/* used when s_fmt */
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *_priv,
				  काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);
	u32 priv = fmt->fmt.pix.priv;

	अगर (try_fmt_vid_cap(gspca_dev, fmt) < 0)
		वापस -EINVAL;
	/* some drivers use priv पूर्णांकernally, so keep the original value */
	fmt->fmt.pix.priv = priv;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *_priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);
	u32 priv = fmt->fmt.pix.priv;
	पूर्णांक mode;

	अगर (vb2_is_busy(&gspca_dev->queue))
		वापस -EBUSY;

	mode = try_fmt_vid_cap(gspca_dev, fmt);
	अगर (mode < 0)
		वापस -EINVAL;

	gspca_dev->curr_mode = mode;
	अगर (gspca_dev->sd_desc->try_fmt)
		/* subdriver try_fmt can modअगरy क्रमmat parameters */
		gspca_dev->pixfmt = fmt->fmt.pix;
	अन्यथा
		gspca_dev->pixfmt = gspca_dev->cam.cam_mode[mode];
	/* some drivers use priv पूर्णांकernally, so keep the original value */
	fmt->fmt.pix.priv = priv;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);
	पूर्णांक i;
	__u32 index = 0;

	अगर (gspca_dev->sd_desc->क्रमागत_framesizes)
		वापस gspca_dev->sd_desc->क्रमागत_framesizes(gspca_dev, fsize);

	क्रम (i = 0; i < gspca_dev->cam.nmodes; i++) अणु
		अगर (fsize->pixel_क्रमmat !=
				gspca_dev->cam.cam_mode[i].pixelक्रमmat)
			जारी;

		अगर (fsize->index == index) अणु
			fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
			fsize->discrete.width =
				gspca_dev->cam.cam_mode[i].width;
			fsize->discrete.height =
				gspca_dev->cam.cam_mode[i].height;
			वापस 0;
		पूर्ण
		index++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *filp, व्योम *priv,
				      काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(filp);
	पूर्णांक mode;
	__u32 i;

	mode = wxh_to_mode(gspca_dev, fival->width, fival->height,
			   fival->pixel_क्रमmat);
	अगर (mode < 0)
		वापस -EINVAL;

	अगर (gspca_dev->cam.mode_framerates == शून्य ||
			gspca_dev->cam.mode_framerates[mode].nrates == 0)
		वापस -EINVAL;

	अगर (fival->pixel_क्रमmat !=
			gspca_dev->cam.cam_mode[mode].pixelक्रमmat)
		वापस -EINVAL;

	क्रम (i = 0; i < gspca_dev->cam.mode_framerates[mode].nrates; i++) अणु
		अगर (fival->index == i) अणु
			fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
			fival->discrete.numerator = 1;
			fival->discrete.denominator =
				gspca_dev->cam.mode_framerates[mode].rates[i];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम gspca_release(काष्ठा v4l2_device *v4l2_device)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(v4l2_device, काष्ठा gspca_dev, v4l2_dev);

	v4l2_ctrl_handler_मुक्त(gspca_dev->vdev.ctrl_handler);
	v4l2_device_unरेजिस्टर(&gspca_dev->v4l2_dev);
	kमुक्त(gspca_dev->usb_buf);
	kमुक्त(gspca_dev);
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	strscpy((अक्षर *)cap->driver, gspca_dev->sd_desc->name,
		माप(cap->driver));
	अगर (gspca_dev->dev->product != शून्य) अणु
		strscpy((अक्षर *)cap->card, gspca_dev->dev->product,
			माप(cap->card));
	पूर्ण अन्यथा अणु
		snम_लिखो((अक्षर *) cap->card, माप cap->card,
			"USB Camera (%04x:%04x)",
			le16_to_cpu(gspca_dev->dev->descriptor.idVenकरोr),
			le16_to_cpu(gspca_dev->dev->descriptor.idProduct));
	पूर्ण
	usb_make_path(gspca_dev->dev, (अक्षर *) cap->bus_info,
			माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *input)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	अगर (input->index != 0)
		वापस -EINVAL;
	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->status = gspca_dev->cam.input_flags;
	strscpy(input->name, gspca_dev->sd_desc->name,
		माप input->name);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_jpegcomp(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_jpegcompression *jpegcomp)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	gspca_dev->usb_err = 0;
	वापस gspca_dev->sd_desc->get_jcomp(gspca_dev, jpegcomp);
पूर्ण

अटल पूर्णांक vidioc_s_jpegcomp(काष्ठा file *file, व्योम *priv,
			स्थिर काष्ठा v4l2_jpegcompression *jpegcomp)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(file);

	gspca_dev->usb_err = 0;
	वापस gspca_dev->sd_desc->set_jcomp(gspca_dev, jpegcomp);
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *filp, व्योम *priv,
			काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(filp);

	parm->parm.capture.पढ़ोbuffers = gspca_dev->queue.min_buffers_needed;

	अगर (!gspca_dev->sd_desc->get_streamparm)
		वापस 0;

	parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	gspca_dev->usb_err = 0;
	gspca_dev->sd_desc->get_streamparm(gspca_dev, parm);
	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक vidioc_s_parm(काष्ठा file *filp, व्योम *priv,
			काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा gspca_dev *gspca_dev = video_drvdata(filp);

	parm->parm.capture.पढ़ोbuffers = gspca_dev->queue.min_buffers_needed;

	अगर (!gspca_dev->sd_desc->set_streamparm) अणु
		parm->parm.capture.capability = 0;
		वापस 0;
	पूर्ण

	parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	gspca_dev->usb_err = 0;
	gspca_dev->sd_desc->set_streamparm(gspca_dev, parm);
	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक gspca_queue_setup(काष्ठा vb2_queue *vq,
			     अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			     अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा gspca_dev *gspca_dev = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = PAGE_ALIGN(gspca_dev->pixfmt.sizeimage);

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक gspca_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा gspca_dev *gspca_dev = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = PAGE_ALIGN(gspca_dev->pixfmt.sizeimage);

	अगर (vb2_plane_size(vb, 0) < size) अणु
		gspca_err(gspca_dev, "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gspca_buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा gspca_dev *gspca_dev = vb2_get_drv_priv(vb->vb2_queue);

	अगर (!gspca_dev->sd_desc->dq_callback)
		वापस;

	gspca_dev->usb_err = 0;
	अगर (gspca_dev->present)
		gspca_dev->sd_desc->dq_callback(gspca_dev);
पूर्ण

अटल व्योम gspca_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा gspca_dev *gspca_dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा gspca_buffer *buf = to_gspca_buffer(vb);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gspca_dev->qlock, flags);
	list_add_tail(&buf->list, &gspca_dev->buf_list);
	spin_unlock_irqrestore(&gspca_dev->qlock, flags);
पूर्ण

अटल व्योम gspca_वापस_all_buffers(काष्ठा gspca_dev *gspca_dev,
				     क्रमागत vb2_buffer_state state)
अणु
	काष्ठा gspca_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gspca_dev->qlock, flags);
	list_क्रम_each_entry_safe(buf, node, &gspca_dev->buf_list, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&gspca_dev->qlock, flags);
पूर्ण

अटल पूर्णांक gspca_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा gspca_dev *gspca_dev = vb2_get_drv_priv(vq);
	पूर्णांक ret;

	gspca_dev->sequence = 0;

	ret = gspca_init_transfer(gspca_dev);
	अगर (ret)
		gspca_वापस_all_buffers(gspca_dev, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम gspca_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा gspca_dev *gspca_dev = vb2_get_drv_priv(vq);

	gspca_stream_off(gspca_dev);

	/* Release all active buffers */
	gspca_वापस_all_buffers(gspca_dev, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops gspca_qops = अणु
	.queue_setup		= gspca_queue_setup,
	.buf_prepare		= gspca_buffer_prepare,
	.buf_finish		= gspca_buffer_finish,
	.buf_queue		= gspca_buffer_queue,
	.start_streaming	= gspca_start_streaming,
	.stop_streaming		= gspca_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations dev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops dev_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,
	.vidioc_क्रमागत_input	= vidioc_क्रमागत_input,
	.vidioc_g_input		= vidioc_g_input,
	.vidioc_s_input		= vidioc_s_input,
	.vidioc_g_jpegcomp	= vidioc_g_jpegcomp,
	.vidioc_s_jpegcomp	= vidioc_s_jpegcomp,
	.vidioc_g_parm		= vidioc_g_parm,
	.vidioc_s_parm		= vidioc_s_parm,
	.vidioc_क्रमागत_framesizes = vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = vidioc_क्रमागत_frameपूर्णांकervals,

	.vidioc_reqbufs		= vb2_ioctl_reqbufs,
	.vidioc_create_bufs	= vb2_ioctl_create_bufs,
	.vidioc_querybuf	= vb2_ioctl_querybuf,
	.vidioc_qbuf		= vb2_ioctl_qbuf,
	.vidioc_dqbuf		= vb2_ioctl_dqbuf,
	.vidioc_expbuf		= vb2_ioctl_expbuf,
	.vidioc_streamon	= vb2_ioctl_streamon,
	.vidioc_streamoff	= vb2_ioctl_streamoff,

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info	= vidioc_g_chip_info,
	.vidioc_g_रेजिस्टर	= vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर	= vidioc_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device gspca_ढाँचा = अणु
	.name = "gspca main driver",
	.fops = &dev_fops,
	.ioctl_ops = &dev_ioctl_ops,
	.release = video_device_release_empty, /* We use v4l2_dev.release */
पूर्ण;

/*
 * probe and create a new gspca device
 *
 * This function must be called by the sub-driver when it is
 * called क्रम probing a new device.
 */
पूर्णांक gspca_dev_probe2(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर काष्ठा sd_desc *sd_desc,
		पूर्णांक dev_size,
		काष्ठा module *module)
अणु
	काष्ठा gspca_dev *gspca_dev;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	pr_info("%s-" GSPCA_VERSION " probing %04x:%04x\n",
		sd_desc->name, id->idVenकरोr, id->idProduct);

	/* create the device */
	अगर (dev_size < माप *gspca_dev)
		dev_size = माप *gspca_dev;
	gspca_dev = kzalloc(dev_size, GFP_KERNEL);
	अगर (!gspca_dev) अणु
		pr_err("couldn't kzalloc gspca struct\n");
		वापस -ENOMEM;
	पूर्ण
	gspca_dev->usb_buf = kzalloc(USB_BUF_SZ, GFP_KERNEL);
	अगर (!gspca_dev->usb_buf) अणु
		pr_err("out of memory\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	gspca_dev->dev = dev;
	gspca_dev->अगरace = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	gspca_dev->xfer_ep = -1;

	/* check अगर any audio device */
	अगर (dev->actconfig->desc.bNumInterfaces != 1) अणु
		पूर्णांक i;
		काष्ठा usb_पूर्णांकerface *पूर्णांकf2;

		क्रम (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) अणु
			पूर्णांकf2 = dev->actconfig->पूर्णांकerface[i];
			अगर (पूर्णांकf2 != शून्य
			 && पूर्णांकf2->altsetting != शून्य
			 && पूर्णांकf2->altsetting->desc.bInterfaceClass ==
					 USB_CLASS_AUDIO) अणु
				gspca_dev->audio = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	gspca_dev->v4l2_dev.release = gspca_release;
	ret = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &gspca_dev->v4l2_dev);
	अगर (ret)
		जाओ out;
	gspca_dev->present = true;
	gspca_dev->sd_desc = sd_desc;
	gspca_dev->empty_packet = -1;	/* करोn't check the empty packets */
	gspca_dev->vdev = gspca_ढाँचा;
	gspca_dev->vdev.v4l2_dev = &gspca_dev->v4l2_dev;
	gspca_dev->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE |
				      V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	video_set_drvdata(&gspca_dev->vdev, gspca_dev);
	gspca_dev->module = module;

	mutex_init(&gspca_dev->usb_lock);
	gspca_dev->vdev.lock = &gspca_dev->usb_lock;
	init_रुकोqueue_head(&gspca_dev->wq);

	/* Initialize the vb2 queue */
	q = &gspca_dev->queue;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	q->drv_priv = gspca_dev;
	q->buf_काष्ठा_size = माप(काष्ठा gspca_buffer);
	q->ops = &gspca_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->lock = &gspca_dev->usb_lock;
	ret = vb2_queue_init(q);
	अगर (ret)
		जाओ out;
	gspca_dev->vdev.queue = q;

	INIT_LIST_HEAD(&gspca_dev->buf_list);
	spin_lock_init(&gspca_dev->qlock);

	/* configure the subdriver and initialize the USB device */
	ret = sd_desc->config(gspca_dev, id);
	अगर (ret < 0)
		जाओ out;
	ret = sd_desc->init(gspca_dev);
	अगर (ret < 0)
		जाओ out;
	अगर (sd_desc->init_controls)
		ret = sd_desc->init_controls(gspca_dev);
	अगर (ret < 0)
		जाओ out;
	gspca_set_शेष_mode(gspca_dev);

	ret = gspca_input_connect(gspca_dev);
	अगर (ret)
		जाओ out;

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	अगर (!gspca_dev->sd_desc->get_रेजिस्टर)
		v4l2_disable_ioctl(&gspca_dev->vdev, VIDIOC_DBG_G_REGISTER);
	अगर (!gspca_dev->sd_desc->set_रेजिस्टर)
		v4l2_disable_ioctl(&gspca_dev->vdev, VIDIOC_DBG_S_REGISTER);
#पूर्ण_अगर
	अगर (!gspca_dev->sd_desc->get_jcomp)
		v4l2_disable_ioctl(&gspca_dev->vdev, VIDIOC_G_JPEGCOMP);
	अगर (!gspca_dev->sd_desc->set_jcomp)
		v4l2_disable_ioctl(&gspca_dev->vdev, VIDIOC_S_JPEGCOMP);

	/* init video stuff */
	ret = video_रेजिस्टर_device(&gspca_dev->vdev,
				  VFL_TYPE_VIDEO,
				  -1);
	अगर (ret < 0) अणु
		pr_err("video_register_device err %d\n", ret);
		जाओ out;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, gspca_dev);
	gspca_dbg(gspca_dev, D_PROBE, "%s created\n",
		  video_device_node_name(&gspca_dev->vdev));

	gspca_input_create_urb(gspca_dev);

	वापस 0;
out:
#अगर IS_ENABLED(CONFIG_INPUT)
	अगर (gspca_dev->input_dev)
		input_unरेजिस्टर_device(gspca_dev->input_dev);
#पूर्ण_अगर
	v4l2_ctrl_handler_मुक्त(gspca_dev->vdev.ctrl_handler);
	v4l2_device_unरेजिस्टर(&gspca_dev->v4l2_dev);
	अगर (sd_desc->probe_error)
		sd_desc->probe_error(gspca_dev);
	kमुक्त(gspca_dev->usb_buf);
	kमुक्त(gspca_dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(gspca_dev_probe2);

/* same function as the previous one, but check the पूर्णांकerface */
पूर्णांक gspca_dev_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर काष्ठा sd_desc *sd_desc,
		पूर्णांक dev_size,
		काष्ठा module *module)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	/* we करोn't handle multi-config cameras */
	अगर (dev->descriptor.bNumConfigurations != 1) अणु
		pr_err("%04x:%04x too many config\n",
		       id->idVenकरोr, id->idProduct);
		वापस -ENODEV;
	पूर्ण

	/* the USB video पूर्णांकerface must be the first one */
	अगर (dev->actconfig->desc.bNumInterfaces != 1
	 && पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0)
		वापस -ENODEV;

	वापस gspca_dev_probe2(पूर्णांकf, id, sd_desc, dev_size, module);
पूर्ण
EXPORT_SYMBOL(gspca_dev_probe);

/*
 * USB disconnection
 *
 * This function must be called by the sub-driver
 * when the device disconnects, after the specअगरic resources are मुक्तd.
 */
व्योम gspca_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gspca_dev *gspca_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
#अगर IS_ENABLED(CONFIG_INPUT)
	काष्ठा input_dev *input_dev;
#पूर्ण_अगर

	gspca_dbg(gspca_dev, D_PROBE, "%s disconnect\n",
		  video_device_node_name(&gspca_dev->vdev));

	mutex_lock(&gspca_dev->usb_lock);
	gspca_dev->present = false;
	destroy_urbs(gspca_dev);
	gspca_input_destroy_urb(gspca_dev);

	vb2_queue_error(&gspca_dev->queue);

#अगर IS_ENABLED(CONFIG_INPUT)
	input_dev = gspca_dev->input_dev;
	अगर (input_dev) अणु
		gspca_dev->input_dev = शून्य;
		input_unरेजिस्टर_device(input_dev);
	पूर्ण
#पूर्ण_अगर

	v4l2_device_disconnect(&gspca_dev->v4l2_dev);
	video_unरेजिस्टर_device(&gspca_dev->vdev);

	mutex_unlock(&gspca_dev->usb_lock);

	/* (this will call gspca_release() immediately or on last बंद) */
	v4l2_device_put(&gspca_dev->v4l2_dev);
पूर्ण
EXPORT_SYMBOL(gspca_disconnect);

#अगर_घोषित CONFIG_PM
पूर्णांक gspca_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा gspca_dev *gspca_dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	gspca_input_destroy_urb(gspca_dev);

	अगर (!vb2_start_streaming_called(&gspca_dev->queue))
		वापस 0;

	mutex_lock(&gspca_dev->usb_lock);
	gspca_dev->frozen = 1;		/* aव्योम urb error messages */
	gspca_dev->usb_err = 0;
	अगर (gspca_dev->sd_desc->stopN)
		gspca_dev->sd_desc->stopN(gspca_dev);
	destroy_urbs(gspca_dev);
	gspca_set_alt0(gspca_dev);
	अगर (gspca_dev->sd_desc->stop0)
		gspca_dev->sd_desc->stop0(gspca_dev);
	mutex_unlock(&gspca_dev->usb_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(gspca_suspend);

पूर्णांक gspca_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gspca_dev *gspca_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक streaming, ret = 0;

	mutex_lock(&gspca_dev->usb_lock);
	gspca_dev->frozen = 0;
	gspca_dev->usb_err = 0;
	gspca_dev->sd_desc->init(gspca_dev);
	/*
	 * Most subdrivers send all ctrl values on sd_start and thus
	 * only ग_लिखो to the device रेजिस्टरs on s_ctrl when streaming ->
	 * Clear streaming to aव्योम setting all ctrls twice.
	 */
	streaming = vb2_start_streaming_called(&gspca_dev->queue);
	अगर (streaming)
		ret = gspca_init_transfer(gspca_dev);
	अन्यथा
		gspca_input_create_urb(gspca_dev);
	mutex_unlock(&gspca_dev->usb_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(gspca_resume);
#पूर्ण_अगर

/* -- module insert / हटाओ -- */
अटल पूर्णांक __init gspca_init(व्योम)
अणु
	pr_info("v" GSPCA_VERSION " registered\n");
	वापस 0;
पूर्ण
अटल व्योम __निकास gspca_निकास(व्योम)
अणु
पूर्ण

module_init(gspca_init);
module_निकास(gspca_निकास);

module_param_named(debug, gspca_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		"1:probe 2:config 3:stream 4:frame 5:packet 6:usbi 7:usbo");
