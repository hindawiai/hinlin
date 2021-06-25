<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USB_STREAM_H
#घोषणा __USB_STREAM_H

#समावेश <uapi/sound/usb_stream.h>

#घोषणा USB_STREAM_NURBS 4
#घोषणा USB_STREAM_URBDEPTH 4

काष्ठा usb_stream_kernel अणु
	काष्ठा usb_stream *s;

	व्योम *ग_लिखो_page;

	अचिन्हित n_o_ps;

	काष्ठा urb *inurb[USB_STREAM_NURBS];
	काष्ठा urb *idle_inurb;
	काष्ठा urb *completed_inurb;
	काष्ठा urb *outurb[USB_STREAM_NURBS];
	काष्ठा urb *idle_outurb;
	काष्ठा urb *completed_outurb;
	काष्ठा urb *i_urb;

	पूर्णांक iso_frame_balance;

	रुको_queue_head_t sleep;

	अचिन्हित out_phase;
	अचिन्हित out_phase_peeked;
	अचिन्हित freqn;
पूर्ण;

काष्ठा usb_stream *usb_stream_new(काष्ठा usb_stream_kernel *sk,
				  काष्ठा usb_device *dev,
				  अचिन्हित in_endpoपूर्णांक, अचिन्हित out_endpoपूर्णांक,
				  अचिन्हित sample_rate, अचिन्हित use_packsize,
				  अचिन्हित period_frames, अचिन्हित frame_size);
व्योम usb_stream_मुक्त(काष्ठा usb_stream_kernel *);
पूर्णांक usb_stream_start(काष्ठा usb_stream_kernel *);
व्योम usb_stream_stop(काष्ठा usb_stream_kernel *);

#पूर्ण_अगर /* __USB_STREAM_H */
