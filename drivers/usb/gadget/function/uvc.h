<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *	uvc_gadget.h  --  USB Video Class Gadget driver
 *
 *	Copyright (C) 2009-2010
 *	    Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित _UVC_GADGET_H_
#घोषणा _UVC_GADGET_H_

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>

#समावेश "uvc_queue.h"

काष्ठा usb_ep;
काष्ठा usb_request;
काष्ठा uvc_descriptor_header;
काष्ठा uvc_device;

/* ------------------------------------------------------------------------
 * Debugging, prपूर्णांकing and logging
 */

#घोषणा UVC_TRACE_PROBE				(1 << 0)
#घोषणा UVC_TRACE_DESCR				(1 << 1)
#घोषणा UVC_TRACE_CONTROL			(1 << 2)
#घोषणा UVC_TRACE_FORMAT			(1 << 3)
#घोषणा UVC_TRACE_CAPTURE			(1 << 4)
#घोषणा UVC_TRACE_CALLS				(1 << 5)
#घोषणा UVC_TRACE_IOCTL				(1 << 6)
#घोषणा UVC_TRACE_FRAME				(1 << 7)
#घोषणा UVC_TRACE_SUSPEND			(1 << 8)
#घोषणा UVC_TRACE_STATUS			(1 << 9)

#घोषणा UVC_WARN_MINMAX				0
#घोषणा UVC_WARN_PROBE_DEF			1

बाह्य अचिन्हित पूर्णांक uvc_gadget_trace_param;

#घोषणा uvc_trace(flag, msg...) \
	करो अणु \
		अगर (uvc_gadget_trace_param & flag) \
			prपूर्णांकk(KERN_DEBUG "uvcvideo: " msg); \
	पूर्ण जबतक (0)

#घोषणा uvcg_dbg(f, fmt, args...) \
	dev_dbg(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##args)
#घोषणा uvcg_info(f, fmt, args...) \
	dev_info(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##args)
#घोषणा uvcg_warn(f, fmt, args...) \
	dev_warn(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##args)
#घोषणा uvcg_err(f, fmt, args...) \
	dev_err(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##args)

/* ------------------------------------------------------------------------
 * Driver specअगरic स्थिरants
 */

#घोषणा UVC_NUM_REQUESTS			4
#घोषणा UVC_MAX_REQUEST_SIZE			64
#घोषणा UVC_MAX_EVENTS				4

/* ------------------------------------------------------------------------
 * Structures
 */

काष्ठा uvc_video अणु
	काष्ठा uvc_device *uvc;
	काष्ठा usb_ep *ep;

	काष्ठा work_काष्ठा pump;

	/* Frame parameters */
	u8 bpp;
	u32 fcc;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक imagesize;
	काष्ठा mutex mutex;	/* protects frame parameters */

	/* Requests */
	अचिन्हित पूर्णांक req_size;
	काष्ठा usb_request *req[UVC_NUM_REQUESTS];
	__u8 *req_buffer[UVC_NUM_REQUESTS];
	काष्ठा list_head req_मुक्त;
	spinlock_t req_lock;

	व्योम (*encode) (काष्ठा usb_request *req, काष्ठा uvc_video *video,
			काष्ठा uvc_buffer *buf);

	/* Context data used by the completion handler */
	__u32 payload_size;
	__u32 max_payload_size;

	काष्ठा uvc_video_queue queue;
	अचिन्हित पूर्णांक fid;
पूर्ण;

क्रमागत uvc_state अणु
	UVC_STATE_DISCONNECTED,
	UVC_STATE_CONNECTED,
	UVC_STATE_STREAMING,
पूर्ण;

काष्ठा uvc_device अणु
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	क्रमागत uvc_state state;
	काष्ठा usb_function func;
	काष्ठा uvc_video video;

	/* Descriptors */
	काष्ठा अणु
		स्थिर काष्ठा uvc_descriptor_header * स्थिर *fs_control;
		स्थिर काष्ठा uvc_descriptor_header * स्थिर *ss_control;
		स्थिर काष्ठा uvc_descriptor_header * स्थिर *fs_streaming;
		स्थिर काष्ठा uvc_descriptor_header * स्थिर *hs_streaming;
		स्थिर काष्ठा uvc_descriptor_header * स्थिर *ss_streaming;
	पूर्ण desc;

	अचिन्हित पूर्णांक control_पूर्णांकf;
	काष्ठा usb_ep *control_ep;
	काष्ठा usb_request *control_req;
	व्योम *control_buf;

	अचिन्हित पूर्णांक streaming_पूर्णांकf;

	/* Events */
	अचिन्हित पूर्णांक event_length;
	अचिन्हित पूर्णांक event_setup_out : 1;
पूर्ण;

अटल अंतरभूत काष्ठा uvc_device *to_uvc(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा uvc_device, func);
पूर्ण

काष्ठा uvc_file_handle अणु
	काष्ठा v4l2_fh vfh;
	काष्ठा uvc_video *device;
पूर्ण;

#घोषणा to_uvc_file_handle(handle) \
	container_of(handle, काष्ठा uvc_file_handle, vfh)

/* ------------------------------------------------------------------------
 * Functions
 */

बाह्य व्योम uvc_function_setup_जारी(काष्ठा uvc_device *uvc);
बाह्य व्योम uvc_endpoपूर्णांक_stream(काष्ठा uvc_device *dev);

बाह्य व्योम uvc_function_connect(काष्ठा uvc_device *uvc);
बाह्य व्योम uvc_function_disconnect(काष्ठा uvc_device *uvc);

#पूर्ण_अगर /* _UVC_GADGET_H_ */
