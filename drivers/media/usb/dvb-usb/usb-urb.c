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
#समावेश "dvb-usb-common.h"

/* URB stuff क्रम streaming */
अटल व्योम usb_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा usb_data_stream *stream = urb->context;
	पूर्णांक ptype = usb_pipetype(urb->pipe);
	पूर्णांक i;
	u8 *b;

	deb_uxfer("'%s' urb completed. status: %d, length: %d/%d, pack_num: %d, errors: %d\n",
		ptype == PIPE_ISOCHRONOUS ? "isoc" : "bulk",
		urb->status,urb->actual_length,urb->transfer_buffer_length,
		urb->number_of_packets,urb->error_count);

	चयन (urb->status) अणु
		हाल 0:         /* success */
		हाल -ETIMEDOUT:    /* NAK */
			अवरोध;
		हाल -ECONNRESET:   /* समाप्त */
		हाल -ENOENT:
		हाल -ESHUTDOWN:
			वापस;
		शेष:        /* error */
			deb_ts("urb completion error %d.\n", urb->status);
			अवरोध;
	पूर्ण

	b = (u8 *) urb->transfer_buffer;
	चयन (ptype) अणु
		हाल PIPE_ISOCHRONOUS:
			क्रम (i = 0; i < urb->number_of_packets; i++) अणु

				अगर (urb->iso_frame_desc[i].status != 0)
					deb_ts("iso frame descriptor has an error: %d\n",urb->iso_frame_desc[i].status);
				अन्यथा अगर (urb->iso_frame_desc[i].actual_length > 0)
					stream->complete(stream, b + urb->iso_frame_desc[i].offset, urb->iso_frame_desc[i].actual_length);

				urb->iso_frame_desc[i].status = 0;
				urb->iso_frame_desc[i].actual_length = 0;
			पूर्ण
			debug_dump(b,20,deb_uxfer);
			अवरोध;
		हाल PIPE_BULK:
			अगर (urb->actual_length > 0)
				stream->complete(stream, b, urb->actual_length);
			अवरोध;
		शेष:
			err("unknown endpoint type in completion handler.");
			वापस;
	पूर्ण
	usb_submit_urb(urb,GFP_ATOMIC);
पूर्ण

पूर्णांक usb_urb_समाप्त(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < stream->urbs_submitted; i++) अणु
		deb_ts("killing URB no. %d.\n",i);

		/* stop the URB */
		usb_समाप्त_urb(stream->urb_list[i]);
	पूर्ण
	stream->urbs_submitted = 0;
	वापस 0;
पूर्ण

पूर्णांक usb_urb_submit(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i,ret;
	क्रम (i = 0; i < stream->urbs_initialized; i++) अणु
		deb_ts("submitting URB no. %d\n",i);
		अगर ((ret = usb_submit_urb(stream->urb_list[i],GFP_ATOMIC))) अणु
			err("could not submit URB no. %d - get them all back",i);
			usb_urb_समाप्त(stream);
			वापस ret;
		पूर्ण
		stream->urbs_submitted++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb_मुक्त_stream_buffers(काष्ठा usb_data_stream *stream)
अणु
	अगर (stream->state & USB_STATE_URB_BUF) अणु
		जबतक (stream->buf_num) अणु
			stream->buf_num--;
			deb_mem("freeing buffer %d\n",stream->buf_num);
			usb_मुक्त_coherent(stream->udev, stream->buf_size,
					  stream->buf_list[stream->buf_num],
					  stream->dma_addr[stream->buf_num]);
		पूर्ण
	पूर्ण

	stream->state &= ~USB_STATE_URB_BUF;

	वापस 0;
पूर्ण

अटल पूर्णांक usb_allocate_stream_buffers(काष्ठा usb_data_stream *stream, पूर्णांक num, अचिन्हित दीर्घ size)
अणु
	stream->buf_num = 0;
	stream->buf_size = size;

	deb_mem("all in all I will use %lu bytes for streaming\n",num*size);

	क्रम (stream->buf_num = 0; stream->buf_num < num; stream->buf_num++) अणु
		deb_mem("allocating buffer %d\n",stream->buf_num);
		अगर (( stream->buf_list[stream->buf_num] =
					usb_alloc_coherent(stream->udev, size, GFP_KERNEL,
					&stream->dma_addr[stream->buf_num]) ) == शून्य) अणु
			deb_mem("not enough memory for urb-buffer allocation.\n");
			usb_मुक्त_stream_buffers(stream);
			वापस -ENOMEM;
		पूर्ण
		deb_mem("buffer %d: %p (dma: %Lu)\n",
			stream->buf_num,
stream->buf_list[stream->buf_num], (दीर्घ दीर्घ)stream->dma_addr[stream->buf_num]);
		स_रखो(stream->buf_list[stream->buf_num],0,size);
		stream->state |= USB_STATE_URB_BUF;
	पूर्ण
	deb_mem("allocation successful\n");

	वापस 0;
पूर्ण

अटल पूर्णांक usb_bulk_urb_init(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i, j;

	अगर ((i = usb_allocate_stream_buffers(stream,stream->props.count,
					stream->props.u.bulk.buffersize)) < 0)
		वापस i;

	/* allocate the URBs */
	क्रम (i = 0; i < stream->props.count; i++) अणु
		stream->urb_list[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!stream->urb_list[i]) अणु
			deb_mem("not enough memory for urb_alloc_urb!.\n");
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(stream->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण
		usb_fill_bulk_urb( stream->urb_list[i], stream->udev,
				usb_rcvbulkpipe(stream->udev,stream->props.endpoपूर्णांक),
				stream->buf_list[i],
				stream->props.u.bulk.buffersize,
				usb_urb_complete, stream);

		stream->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		stream->urb_list[i]->transfer_dma = stream->dma_addr[i];
		stream->urbs_initialized++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb_isoc_urb_init(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i,j;

	अगर ((i = usb_allocate_stream_buffers(stream,stream->props.count,
					stream->props.u.isoc.framesize*stream->props.u.isoc.framesperurb)) < 0)
		वापस i;

	/* allocate the URBs */
	क्रम (i = 0; i < stream->props.count; i++) अणु
		काष्ठा urb *urb;
		पूर्णांक frame_offset = 0;

		stream->urb_list[i] = usb_alloc_urb(stream->props.u.isoc.framesperurb, GFP_KERNEL);
		अगर (!stream->urb_list[i]) अणु
			deb_mem("not enough memory for urb_alloc_urb!\n");
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(stream->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण

		urb = stream->urb_list[i];

		urb->dev = stream->udev;
		urb->context = stream;
		urb->complete = usb_urb_complete;
		urb->pipe = usb_rcvisocpipe(stream->udev,stream->props.endpoपूर्णांक);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->पूर्णांकerval = stream->props.u.isoc.पूर्णांकerval;
		urb->number_of_packets = stream->props.u.isoc.framesperurb;
		urb->transfer_buffer_length = stream->buf_size;
		urb->transfer_buffer = stream->buf_list[i];
		urb->transfer_dma = stream->dma_addr[i];

		क्रम (j = 0; j < stream->props.u.isoc.framesperurb; j++) अणु
			urb->iso_frame_desc[j].offset = frame_offset;
			urb->iso_frame_desc[j].length = stream->props.u.isoc.framesize;
			frame_offset += stream->props.u.isoc.framesize;
		पूर्ण

		stream->urbs_initialized++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक usb_urb_init(काष्ठा usb_data_stream *stream, काष्ठा usb_data_stream_properties *props)
अणु
	अगर (stream == शून्य || props == शून्य)
		वापस -EINVAL;

	स_नकल(&stream->props, props, माप(*props));

	usb_clear_halt(stream->udev,usb_rcvbulkpipe(stream->udev,stream->props.endpoपूर्णांक));

	अगर (stream->complete == शून्य) अणु
		err("there is no data callback - this doesn't make sense.");
		वापस -EINVAL;
	पूर्ण

	चयन (stream->props.type) अणु
		हाल USB_BULK:
			वापस usb_bulk_urb_init(stream);
		हाल USB_ISOC:
			वापस usb_isoc_urb_init(stream);
		शेष:
			err("unknown URB-type for data transfer.");
			वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक usb_urb_निकास(काष्ठा usb_data_stream *stream)
अणु
	पूर्णांक i;

	usb_urb_समाप्त(stream);

	क्रम (i = 0; i < stream->urbs_initialized; i++) अणु
		अगर (stream->urb_list[i] != शून्य) अणु
			deb_mem("freeing URB no. %d.\n",i);
			/* मुक्त the URBs */
			usb_मुक्त_urb(stream->urb_list[i]);
		पूर्ण
	पूर्ण
	stream->urbs_initialized = 0;

	usb_मुक्त_stream_buffers(stream);
	वापस 0;
पूर्ण
