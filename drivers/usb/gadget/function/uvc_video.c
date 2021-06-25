<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	uvc_video.c  --  USB Video Class Gadget driver
 *
 *	Copyright (C) 2009-2010
 *	    Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/video.h>

#समावेश <media/v4l2-dev.h>

#समावेश "uvc.h"
#समावेश "uvc_queue.h"
#समावेश "uvc_video.h"

/* --------------------------------------------------------------------------
 * Video codecs
 */

अटल पूर्णांक
uvc_video_encode_header(काष्ठा uvc_video *video, काष्ठा uvc_buffer *buf,
		u8 *data, पूर्णांक len)
अणु
	data[0] = 2;
	data[1] = UVC_STREAM_EOH | video->fid;

	अगर (buf->bytesused - video->queue.buf_used <= len - 2)
		data[1] |= UVC_STREAM_खातापूर्ण;

	वापस 2;
पूर्ण

अटल पूर्णांक
uvc_video_encode_data(काष्ठा uvc_video *video, काष्ठा uvc_buffer *buf,
		u8 *data, पूर्णांक len)
अणु
	काष्ठा uvc_video_queue *queue = &video->queue;
	अचिन्हित पूर्णांक nbytes;
	व्योम *mem;

	/* Copy video data to the USB buffer. */
	mem = buf->mem + queue->buf_used;
	nbytes = min((अचिन्हित पूर्णांक)len, buf->bytesused - queue->buf_used);

	स_नकल(data, mem, nbytes);
	queue->buf_used += nbytes;

	वापस nbytes;
पूर्ण

अटल व्योम
uvc_video_encode_bulk(काष्ठा usb_request *req, काष्ठा uvc_video *video,
		काष्ठा uvc_buffer *buf)
अणु
	व्योम *mem = req->buf;
	पूर्णांक len = video->req_size;
	पूर्णांक ret;

	/* Add a header at the beginning of the payload. */
	अगर (video->payload_size == 0) अणु
		ret = uvc_video_encode_header(video, buf, mem, len);
		video->payload_size += ret;
		mem += ret;
		len -= ret;
	पूर्ण

	/* Process video data. */
	len = min((पूर्णांक)(video->max_payload_size - video->payload_size), len);
	ret = uvc_video_encode_data(video, buf, mem, len);

	video->payload_size += ret;
	len -= ret;

	req->length = video->req_size - len;
	req->zero = video->payload_size == video->max_payload_size;

	अगर (buf->bytesused == video->queue.buf_used) अणु
		video->queue.buf_used = 0;
		buf->state = UVC_BUF_STATE_DONE;
		uvcg_queue_next_buffer(&video->queue, buf);
		video->fid ^= UVC_STREAM_FID;

		video->payload_size = 0;
	पूर्ण

	अगर (video->payload_size == video->max_payload_size ||
	    buf->bytesused == video->queue.buf_used)
		video->payload_size = 0;
पूर्ण

अटल व्योम
uvc_video_encode_isoc(काष्ठा usb_request *req, काष्ठा uvc_video *video,
		काष्ठा uvc_buffer *buf)
अणु
	व्योम *mem = req->buf;
	पूर्णांक len = video->req_size;
	पूर्णांक ret;

	/* Add the header. */
	ret = uvc_video_encode_header(video, buf, mem, len);
	mem += ret;
	len -= ret;

	/* Process video data. */
	ret = uvc_video_encode_data(video, buf, mem, len);
	len -= ret;

	req->length = video->req_size - len;

	अगर (buf->bytesused == video->queue.buf_used) अणु
		video->queue.buf_used = 0;
		buf->state = UVC_BUF_STATE_DONE;
		uvcg_queue_next_buffer(&video->queue, buf);
		video->fid ^= UVC_STREAM_FID;
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------------
 * Request handling
 */

अटल पूर्णांक uvcg_video_ep_queue(काष्ठा uvc_video *video, काष्ठा usb_request *req)
अणु
	पूर्णांक ret;

	ret = usb_ep_queue(video->ep, req, GFP_ATOMIC);
	अगर (ret < 0) अणु
		uvcg_err(&video->uvc->func, "Failed to queue request (%d).\n",
			 ret);

		/* Isochronous endpoपूर्णांकs can't be halted. */
		अगर (usb_endpoपूर्णांक_xfer_bulk(video->ep->desc))
			usb_ep_set_halt(video->ep);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
uvc_video_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा uvc_video *video = req->context;
	काष्ठा uvc_video_queue *queue = &video->queue;
	अचिन्हित दीर्घ flags;

	चयन (req->status) अणु
	हाल 0:
		अवरोध;

	हाल -ESHUTDOWN:	/* disconnect from host. */
		uvcg_dbg(&video->uvc->func, "VS request cancelled.\n");
		uvcg_queue_cancel(queue, 1);
		अवरोध;

	शेष:
		uvcg_info(&video->uvc->func,
			  "VS request completed with status %d.\n",
			  req->status);
		uvcg_queue_cancel(queue, 0);
	पूर्ण

	spin_lock_irqsave(&video->req_lock, flags);
	list_add_tail(&req->list, &video->req_मुक्त);
	spin_unlock_irqrestore(&video->req_lock, flags);

	schedule_work(&video->pump);
पूर्ण

अटल पूर्णांक
uvc_video_मुक्त_requests(काष्ठा uvc_video *video)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < UVC_NUM_REQUESTS; ++i) अणु
		अगर (video->req[i]) अणु
			usb_ep_मुक्त_request(video->ep, video->req[i]);
			video->req[i] = शून्य;
		पूर्ण

		अगर (video->req_buffer[i]) अणु
			kमुक्त(video->req_buffer[i]);
			video->req_buffer[i] = शून्य;
		पूर्ण
	पूर्ण

	INIT_LIST_HEAD(&video->req_मुक्त);
	video->req_size = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_video_alloc_requests(काष्ठा uvc_video *video)
अणु
	अचिन्हित पूर्णांक req_size;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = -ENOMEM;

	BUG_ON(video->req_size);

	req_size = video->ep->maxpacket
		 * max_t(अचिन्हित पूर्णांक, video->ep->maxburst, 1)
		 * (video->ep->mult);

	क्रम (i = 0; i < UVC_NUM_REQUESTS; ++i) अणु
		video->req_buffer[i] = kदो_स्मृति(req_size, GFP_KERNEL);
		अगर (video->req_buffer[i] == शून्य)
			जाओ error;

		video->req[i] = usb_ep_alloc_request(video->ep, GFP_KERNEL);
		अगर (video->req[i] == शून्य)
			जाओ error;

		video->req[i]->buf = video->req_buffer[i];
		video->req[i]->length = 0;
		video->req[i]->complete = uvc_video_complete;
		video->req[i]->context = video;

		list_add_tail(&video->req[i]->list, &video->req_मुक्त);
	पूर्ण

	video->req_size = req_size;

	वापस 0;

error:
	uvc_video_मुक्त_requests(video);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------------
 * Video streaming
 */

/*
 * uvcg_video_pump - Pump video data पूर्णांकo the USB requests
 *
 * This function fills the available USB requests (listed in req_मुक्त) with
 * video data from the queued buffers.
 */
अटल व्योम uvcg_video_pump(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uvc_video *video = container_of(work, काष्ठा uvc_video, pump);
	काष्ठा uvc_video_queue *queue = &video->queue;
	काष्ठा usb_request *req;
	काष्ठा uvc_buffer *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	जबतक (1) अणु
		/* Retrieve the first available USB request, रक्षित by the
		 * request lock.
		 */
		spin_lock_irqsave(&video->req_lock, flags);
		अगर (list_empty(&video->req_मुक्त)) अणु
			spin_unlock_irqrestore(&video->req_lock, flags);
			वापस;
		पूर्ण
		req = list_first_entry(&video->req_मुक्त, काष्ठा usb_request,
					list);
		list_del(&req->list);
		spin_unlock_irqrestore(&video->req_lock, flags);

		/* Retrieve the first available video buffer and fill the
		 * request, रक्षित by the video queue irqlock.
		 */
		spin_lock_irqsave(&queue->irqlock, flags);
		buf = uvcg_queue_head(queue);
		अगर (buf == शून्य) अणु
			spin_unlock_irqrestore(&queue->irqlock, flags);
			अवरोध;
		पूर्ण

		video->encode(req, video, buf);

		/* Queue the USB request */
		ret = uvcg_video_ep_queue(video, req);
		spin_unlock_irqrestore(&queue->irqlock, flags);

		अगर (ret < 0) अणु
			uvcg_queue_cancel(queue, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&video->req_lock, flags);
	list_add_tail(&req->list, &video->req_मुक्त);
	spin_unlock_irqrestore(&video->req_lock, flags);
	वापस;
पूर्ण

/*
 * Enable or disable the video stream.
 */
पूर्णांक uvcg_video_enable(काष्ठा uvc_video *video, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (video->ep == शून्य) अणु
		uvcg_info(&video->uvc->func,
			  "Video enable failed, device is uninitialized.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!enable) अणु
		cancel_work_sync(&video->pump);
		uvcg_queue_cancel(&video->queue, 0);

		क्रम (i = 0; i < UVC_NUM_REQUESTS; ++i)
			अगर (video->req[i])
				usb_ep_dequeue(video->ep, video->req[i]);

		uvc_video_मुक्त_requests(video);
		uvcg_queue_enable(&video->queue, 0);
		वापस 0;
	पूर्ण

	अगर ((ret = uvcg_queue_enable(&video->queue, 1)) < 0)
		वापस ret;

	अगर ((ret = uvc_video_alloc_requests(video)) < 0)
		वापस ret;

	अगर (video->max_payload_size) अणु
		video->encode = uvc_video_encode_bulk;
		video->payload_size = 0;
	पूर्ण अन्यथा
		video->encode = uvc_video_encode_isoc;

	schedule_work(&video->pump);

	वापस ret;
पूर्ण

/*
 * Initialize the UVC video stream.
 */
पूर्णांक uvcg_video_init(काष्ठा uvc_video *video, काष्ठा uvc_device *uvc)
अणु
	INIT_LIST_HEAD(&video->req_मुक्त);
	spin_lock_init(&video->req_lock);
	INIT_WORK(&video->pump, uvcg_video_pump);

	video->uvc = uvc;
	video->fcc = V4L2_PIX_FMT_YUYV;
	video->bpp = 16;
	video->width = 320;
	video->height = 240;
	video->imagesize = 320 * 240 * 2;

	/* Initialize the video buffers queue. */
	uvcg_queue_init(&video->queue, V4L2_BUF_TYPE_VIDEO_OUTPUT,
			&video->mutex);
	वापस 0;
पूर्ण

