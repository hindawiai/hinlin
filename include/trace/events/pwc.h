<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_PWC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PWC_H

#समावेश <linux/usb.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM pwc

TRACE_EVENT(pwc_handler_enter,
	TP_PROTO(काष्ठा urb *urb, काष्ठा pwc_device *pdev),
	TP_ARGS(urb, pdev),
	TP_STRUCT__entry(
		__field(काष्ठा urb*, urb)
		__field(काष्ठा pwc_frame_buf*, fbuf)
		__field(पूर्णांक, urb__status)
		__field(u32, urb__actual_length)
		__field(पूर्णांक, fbuf__filled)
		__string(name, pdev->v4l2_dev.name)
	),
	TP_fast_assign(
		__entry->urb = urb;
		__entry->fbuf = pdev->fill_buf;
		__entry->urb__status = urb->status;
		__entry->urb__actual_length = urb->actual_length;
		__entry->fbuf__filled = (pdev->fill_buf
					 ? pdev->fill_buf->filled : 0);
		__assign_str(name, pdev->v4l2_dev.name);
	),
	TP_prपूर्णांकk("dev=%s (fbuf=%p filled=%d) urb=%p (status=%d actual_length=%u)",
		__get_str(name),
		__entry->fbuf,
		__entry->fbuf__filled,
		__entry->urb,
		__entry->urb__status,
		__entry->urb__actual_length)
);

TRACE_EVENT(pwc_handler_निकास,
	TP_PROTO(काष्ठा urb *urb, काष्ठा pwc_device *pdev),
	TP_ARGS(urb, pdev),
	TP_STRUCT__entry(
		__field(काष्ठा urb*, urb)
		__field(काष्ठा pwc_frame_buf*, fbuf)
		__field(पूर्णांक, fbuf__filled)
		__string(name, pdev->v4l2_dev.name)
	),
	TP_fast_assign(
		__entry->urb = urb;
		__entry->fbuf = pdev->fill_buf;
		__entry->fbuf__filled = pdev->fill_buf->filled;
		__assign_str(name, pdev->v4l2_dev.name);
	),
	TP_prपूर्णांकk(" dev=%s (fbuf=%p filled=%d) urb=%p",
		__get_str(name),
		__entry->fbuf,
		__entry->fbuf__filled,
		__entry->urb)
);

#पूर्ण_अगर /* _TRACE_PWC_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
