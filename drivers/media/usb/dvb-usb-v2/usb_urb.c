<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* usb-urb.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file keeps functions क्रम initializing and handling the
 * BULK and ISOC USB data transfers in a generic way.
 * Can be used क्रम DVB-only and also, that's the plan, क्रम
 * Hybrid USB devices (analog and DVB).
 */
#समावेश "dvb_usb_common.h"

/* URB stuff क्रम streaming */

पूर्णांक usb_urb_reconfig(काष्ठा usb_data_stream *stream,
		काष्ठा usb_data_stream_properties *props);

अटल व्योम usb_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा usb_data_stream *stream = urb->context;
	पूर्णांक ptype = usb_pipetype(urb->pipe);
	पूर्णांक i;
	u8 *b;

	dev_dbg_ratelimited(&stream->udev->dev,
			"%s: %s urb completed status=%d length=%d/%d pack_num=%d errors=%d\n",
			__func__, ptype == PIPE_ISOCHRONOUS ? "isoc" : "bulk",
			urb->status, urb->actual_length,
			urb->transfer_buffer_length,
			urb->number_of_packets, urb->error_count);

	चयन (urb->status) अणु
	हाल 0:         /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:        /* error */
		dev_dbg_ratelimited(&stream->udev->dev,
				"%s: urb completion failed=%d\n",
				__func__, urb->status);
		अवरोध;
	पूर्ण

	b = (u8 *) urb->transfer_buffer;
	चयन (ptype) अणु
	हाल PIPE_ISOCHRONOUS:
		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अगर (urb->iso_frame_desc[i].status != 0)
				dev_dbg(&stream->udev->dev,
						"%s: iso frame descriptor has an error=%d\n",
						__func__,
						urb->iso_frame_desc[i].status);
			अन्यथा अगर (urb->iso_frame_desc[i].actual_length > 0)
				stream->complete(stream,
					b + urb->iso_frame_desc[i].offset,
					urb->iso_frame_desc[i].actual_length);

			urb->iso_frame_desc[i].status = 0;
			urb->iso_frame_desc[i].actual_length = 0;
		पूर्ण
		अवरोध;
	हाल PIPE_BULK:
		अगर (urb->actual_length > 0)
			stream->complete(stream, b, urb->actual_length);
		अवरोध;
	शेष:
		dev_err(&stream->udev->dev,
				"%s: unknown endpoint type in completion handler\n",
				KBUILD_MODNAME);
		वापस;
	पूर्ण
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

पूर्णांक usb_urb_समाप्तv2(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < stream->urbs_submitted; i++) अणु
		dev_dbg(&stream->udev->dev, "%s: kill urb=%d\n", __func__, i);
		/* stop the URB */
		usb_समाप्त_urb(stream->urb_list[i]);
	पूर्ण
	stream->urbs_submitted = 0;
	वापस 0;
पूर्ण

पूर्णांक usb_urb_submitv2(काष्ठा usb_data_stream *stream,
		काष्ठा usb_data_stream_properties *props)
अणु
	पूर्णांक i, ret;

	अगर (props) अणु
		ret = usb_urb_reconfig(stream, props);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < stream->urbs_initialized; i++) अणु
		dev_dbg(&stream->udev->dev, "%s: submit urb=%d\n", __func__, i);
		ret = usb_submit_urb(stream->urb_list[i], GFP_ATOMIC);
		अगर (ret) अणु
			dev_err(&stream->udev->dev,
					"%s: could not submit urb no. %d - get them all back\n",
					KBUILD_MODNAME, i);
			usb_urb_समाप्तv2(stream);
			वापस ret;
		पूर्ण
		stream->urbs_submitted++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb_urb_मुक्त_urbs(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i;

	usb_urb_समाप्तv2(stream);

	क्रम (i = stream->urbs_initialized - 1; i >= 0; i--) अणु
		अगर (stream->urb_list[i]) अणु
			dev_dbg(&stream->udev->dev, "%s: free urb=%d\n",
					__func__, i);
			/* मुक्त the URBs */
			usb_मुक्त_urb(stream->urb_list[i]);
		पूर्ण
	पूर्ण
	stream->urbs_initialized = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक usb_urb_alloc_bulk_urbs(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i, j;

	/* allocate the URBs */
	क्रम (i = 0; i < stream->props.count; i++) अणु
		dev_dbg(&stream->udev->dev, "%s: alloc urb=%d\n", __func__, i);
		stream->urb_list[i] = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!stream->urb_list[i]) अणु
			dev_dbg(&stream->udev->dev, "%s: failed\n", __func__);
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(stream->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण
		usb_fill_bulk_urb(stream->urb_list[i],
				stream->udev,
				usb_rcvbulkpipe(stream->udev,
						stream->props.endpoपूर्णांक),
				stream->buf_list[i],
				stream->props.u.bulk.buffersize,
				usb_urb_complete, stream);

		stream->urbs_initialized++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb_urb_alloc_isoc_urbs(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i, j;

	/* allocate the URBs */
	क्रम (i = 0; i < stream->props.count; i++) अणु
		काष्ठा urb *urb;
		पूर्णांक frame_offset = 0;
		dev_dbg(&stream->udev->dev, "%s: alloc urb=%d\n", __func__, i);
		stream->urb_list[i] = usb_alloc_urb(
				stream->props.u.isoc.framesperurb, GFP_ATOMIC);
		अगर (!stream->urb_list[i]) अणु
			dev_dbg(&stream->udev->dev, "%s: failed\n", __func__);
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(stream->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण

		urb = stream->urb_list[i];

		urb->dev = stream->udev;
		urb->context = stream;
		urb->complete = usb_urb_complete;
		urb->pipe = usb_rcvisocpipe(stream->udev,
				stream->props.endpoपूर्णांक);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->पूर्णांकerval = stream->props.u.isoc.पूर्णांकerval;
		urb->number_of_packets = stream->props.u.isoc.framesperurb;
		urb->transfer_buffer_length = stream->props.u.isoc.framesize *
				stream->props.u.isoc.framesperurb;
		urb->transfer_buffer = stream->buf_list[i];

		क्रम (j = 0; j < stream->props.u.isoc.framesperurb; j++) अणु
			urb->iso_frame_desc[j].offset = frame_offset;
			urb->iso_frame_desc[j].length =
					stream->props.u.isoc.framesize;
			frame_offset += stream->props.u.isoc.framesize;
		पूर्ण

		stream->urbs_initialized++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb_मुक्त_stream_buffers(काष्ठा usb_data_stream *stream)
अणु
	अगर (stream->state & USB_STATE_URB_BUF) अणु
		जबतक (stream->buf_num) अणु
			stream->buf_num--;
			kमुक्त(stream->buf_list[stream->buf_num]);
		पूर्ण
	पूर्ण

	stream->state &= ~USB_STATE_URB_BUF;

	वापस 0;
पूर्ण

अटल पूर्णांक usb_alloc_stream_buffers(काष्ठा usb_data_stream *stream, पूर्णांक num,
				    अचिन्हित दीर्घ size)
अणु
	stream->buf_num = 0;
	stream->buf_size = size;

	dev_dbg(&stream->udev->dev,
			"%s: all in all I will use %lu bytes for streaming\n",
			__func__,  num * size);

	क्रम (stream->buf_num = 0; stream->buf_num < num; stream->buf_num++) अणु
		stream->buf_list[stream->buf_num] = kzalloc(size, GFP_ATOMIC);
		अगर (!stream->buf_list[stream->buf_num]) अणु
			dev_dbg(&stream->udev->dev, "%s: alloc buf=%d failed\n",
					__func__, stream->buf_num);
			usb_मुक्त_stream_buffers(stream);
			वापस -ENOMEM;
		पूर्ण

		dev_dbg(&stream->udev->dev, "%s: alloc buf=%d %p (dma %llu)\n",
				__func__, stream->buf_num,
				stream->buf_list[stream->buf_num],
				(दीर्घ दीर्घ)stream->dma_addr[stream->buf_num]);
		stream->state |= USB_STATE_URB_BUF;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक usb_urb_reconfig(काष्ठा usb_data_stream *stream,
		काष्ठा usb_data_stream_properties *props)
अणु
	पूर्णांक buf_size;

	अगर (!props)
		वापस 0;

	/* check allocated buffers are large enough क्रम the request */
	अगर (props->type == USB_BULK) अणु
		buf_size = stream->props.u.bulk.buffersize;
	पूर्ण अन्यथा अगर (props->type == USB_ISOC) अणु
		buf_size = props->u.isoc.framesize * props->u.isoc.framesperurb;
	पूर्ण अन्यथा अणु
		dev_err(&stream->udev->dev, "%s: invalid endpoint type=%d\n",
				KBUILD_MODNAME, props->type);
		वापस -EINVAL;
	पूर्ण

	अगर (stream->buf_num < props->count || stream->buf_size < buf_size) अणु
		dev_err(&stream->udev->dev,
				"%s: cannot reconfigure as allocated buffers are too small\n",
				KBUILD_MODNAME);
		वापस -EINVAL;
	पूर्ण

	/* check अगर all fields are same */
	अगर (stream->props.type == props->type &&
			stream->props.count == props->count &&
			stream->props.endpoपूर्णांक == props->endpoपूर्णांक) अणु
		अगर (props->type == USB_BULK &&
				props->u.bulk.buffersize ==
				stream->props.u.bulk.buffersize)
			वापस 0;
		अन्यथा अगर (props->type == USB_ISOC &&
				props->u.isoc.framesperurb ==
				stream->props.u.isoc.framesperurb &&
				props->u.isoc.framesize ==
				stream->props.u.isoc.framesize &&
				props->u.isoc.पूर्णांकerval ==
				stream->props.u.isoc.पूर्णांकerval)
			वापस 0;
	पूर्ण

	dev_dbg(&stream->udev->dev, "%s: re-alloc urbs\n", __func__);

	usb_urb_मुक्त_urbs(stream);
	स_नकल(&stream->props, props, माप(*props));
	अगर (props->type == USB_BULK)
		वापस usb_urb_alloc_bulk_urbs(stream);
	अन्यथा अगर (props->type == USB_ISOC)
		वापस usb_urb_alloc_isoc_urbs(stream);

	वापस 0;
पूर्ण

पूर्णांक usb_urb_initv2(काष्ठा usb_data_stream *stream,
		स्थिर काष्ठा usb_data_stream_properties *props)
अणु
	पूर्णांक ret;

	अगर (!stream || !props)
		वापस -EINVAL;

	स_नकल(&stream->props, props, माप(*props));

	अगर (!stream->complete) अणु
		dev_err(&stream->udev->dev,
				"%s: there is no data callback - this doesn't make sense\n",
				KBUILD_MODNAME);
		वापस -EINVAL;
	पूर्ण

	चयन (stream->props.type) अणु
	हाल USB_BULK:
		ret = usb_alloc_stream_buffers(stream, stream->props.count,
				stream->props.u.bulk.buffersize);
		अगर (ret < 0)
			वापस ret;

		वापस usb_urb_alloc_bulk_urbs(stream);
	हाल USB_ISOC:
		ret = usb_alloc_stream_buffers(stream, stream->props.count,
				stream->props.u.isoc.framesize *
				stream->props.u.isoc.framesperurb);
		अगर (ret < 0)
			वापस ret;

		वापस usb_urb_alloc_isoc_urbs(stream);
	शेष:
		dev_err(&stream->udev->dev,
				"%s: unknown urb-type for data transfer\n",
				KBUILD_MODNAME);
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक usb_urb_निकासv2(काष्ठा usb_data_stream *stream)
अणु
	usb_urb_मुक्त_urbs(stream);
	usb_मुक्त_stream_buffers(stream);

	वापस 0;
पूर्ण
