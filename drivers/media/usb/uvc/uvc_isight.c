<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_isight.c  --  USB Video Class driver - iSight support
 *
 *	Copyright (C) 2006-2007
 *		Ivan N. Zlatev <contact@i-nz.net>
 *	Copyright (C) 2008-2009
 *		Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/usb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>

#समावेश "uvcvideo.h"

/* Built-in iSight webcams implements most of UVC 1.0 except a
 * dअगरferent packet क्रमmat. Instead of sending a header at the
 * beginning of each isochronous transfer payload, the webcam sends a
 * single header per image (on its own in a packet), followed by
 * packets containing data only.
 *
 * Offset   Size (bytes)	Description
 * ------------------------------------------------------------------
 * 0x00	1	Header length
 * 0x01	1	Flags (UVC-compliant)
 * 0x02	4	Always equal to '11223344'
 * 0x06	8	Always equal to 'deadbeefdeadface'
 * 0x0e	16	Unknown
 *
 * The header can be prefixed by an optional, unknown-purpose byte.
 */

अटल पूर्णांक isight_decode(काष्ठा uvc_video_queue *queue, काष्ठा uvc_buffer *buf,
		स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	अटल स्थिर u8 hdr[] = अणु
		0x11, 0x22, 0x33, 0x44,
		0xde, 0xad, 0xbe, 0xef,
		0xde, 0xad, 0xfa, 0xce
	पूर्ण;

	काष्ठा uvc_streaming *stream = uvc_queue_to_stream(queue);
	अचिन्हित पूर्णांक maxlen, nbytes;
	u8 *mem;
	पूर्णांक is_header = 0;

	अगर (buf == शून्य)
		वापस 0;

	अगर ((len >= 14 && स_भेद(&data[2], hdr, 12) == 0) ||
	    (len >= 15 && स_भेद(&data[3], hdr, 12) == 0)) अणु
		uvc_dbg(stream->dev, FRAME, "iSight header found\n");
		is_header = 1;
	पूर्ण

	/* Synchronize to the input stream by रुकोing क्रम a header packet. */
	अगर (buf->state != UVC_BUF_STATE_ACTIVE) अणु
		अगर (!is_header) अणु
			uvc_dbg(stream->dev, FRAME,
				"Dropping packet (out of sync)\n");
			वापस 0;
		पूर्ण

		buf->state = UVC_BUF_STATE_ACTIVE;
	पूर्ण

	/* Mark the buffer as करोne अगर we're at the beginning of a new frame.
	 *
	 * Empty buffers (bytesused == 0) करोn't trigger end of frame detection
	 * as it करोesn't make sense to वापस an empty buffer.
	 */
	अगर (is_header && buf->bytesused != 0) अणु
		buf->state = UVC_BUF_STATE_DONE;
		वापस -EAGAIN;
	पूर्ण

	/* Copy the video data to the buffer. Skip header packets, as they
	 * contain no data.
	 */
	अगर (!is_header) अणु
		maxlen = buf->length - buf->bytesused;
		mem = buf->mem + buf->bytesused;
		nbytes = min(len, maxlen);
		स_नकल(mem, data, nbytes);
		buf->bytesused += nbytes;

		अगर (len > maxlen || buf->bytesused == buf->length) अणु
			uvc_dbg(stream->dev, FRAME,
				"Frame complete (overflow)\n");
			buf->state = UVC_BUF_STATE_DONE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम uvc_video_decode_isight(काष्ठा uvc_urb *uvc_urb, काष्ठा uvc_buffer *buf,
			काष्ठा uvc_buffer *meta_buf)
अणु
	काष्ठा urb *urb = uvc_urb->urb;
	काष्ठा uvc_streaming *stream = uvc_urb->stream;
	पूर्णांक ret, i;

	क्रम (i = 0; i < urb->number_of_packets; ++i) अणु
		अगर (urb->iso_frame_desc[i].status < 0) अणु
			uvc_dbg(stream->dev, FRAME,
				"USB isochronous frame lost (%d)\n",
				urb->iso_frame_desc[i].status);
		पूर्ण

		/* Decode the payload packet.
		 * uvc_video_decode is entered twice when a frame transition
		 * has been detected because the end of frame can only be
		 * reliably detected when the first packet of the new frame
		 * is processed. The first pass detects the transition and
		 * बंदs the previous frame's buffer, the second pass
		 * processes the data of the first payload of the new frame.
		 */
		करो अणु
			ret = isight_decode(&stream->queue, buf,
					urb->transfer_buffer +
					urb->iso_frame_desc[i].offset,
					urb->iso_frame_desc[i].actual_length);

			अगर (buf == शून्य)
				अवरोध;

			अगर (buf->state == UVC_BUF_STATE_DONE ||
			    buf->state == UVC_BUF_STATE_ERROR)
				buf = uvc_queue_next_buffer(&stream->queue,
							buf);
		पूर्ण जबतक (ret == -EAGAIN);
	पूर्ण
पूर्ण
