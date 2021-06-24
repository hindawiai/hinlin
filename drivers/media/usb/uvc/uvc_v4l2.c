<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_v4l2.c  --  USB Video Class driver - V4L2 API
 *
 *      Copyright (C) 2005-2010
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "uvcvideo.h"

/* ------------------------------------------------------------------------
 * UVC ioctls
 */
अटल पूर्णांक uvc_ioctl_ctrl_map(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_xu_control_mapping *xmap)
अणु
	काष्ठा uvc_control_mapping *map;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य)
		वापस -ENOMEM;

	map->id = xmap->id;
	स_नकल(map->name, xmap->name, माप(map->name));
	स_नकल(map->entity, xmap->entity, माप(map->entity));
	map->selector = xmap->selector;
	map->size = xmap->size;
	map->offset = xmap->offset;
	map->v4l2_type = xmap->v4l2_type;
	map->data_type = xmap->data_type;

	चयन (xmap->v4l2_type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER:
	हाल V4L2_CTRL_TYPE_BOOLEAN:
	हाल V4L2_CTRL_TYPE_BUTTON:
		अवरोध;

	हाल V4L2_CTRL_TYPE_MENU:
		/* Prevent excessive memory consumption, as well as पूर्णांकeger
		 * overflows.
		 */
		अगर (xmap->menu_count == 0 ||
		    xmap->menu_count > UVC_MAX_CONTROL_MENU_ENTRIES) अणु
			ret = -EINVAL;
			जाओ मुक्त_map;
		पूर्ण

		size = xmap->menu_count * माप(*map->menu_info);
		map->menu_info = memdup_user(xmap->menu_info, size);
		अगर (IS_ERR(map->menu_info)) अणु
			ret = PTR_ERR(map->menu_info);
			जाओ मुक्त_map;
		पूर्ण

		map->menu_count = xmap->menu_count;
		अवरोध;

	शेष:
		uvc_dbg(chain->dev, CONTROL,
			"Unsupported V4L2 control type %u\n", xmap->v4l2_type);
		ret = -ENOTTY;
		जाओ मुक्त_map;
	पूर्ण

	ret = uvc_ctrl_add_mapping(chain, map);

	kमुक्त(map->menu_info);
मुक्त_map:
	kमुक्त(map);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------
 * V4L2 पूर्णांकerface
 */

/*
 * Find the frame पूर्णांकerval बंदst to the requested frame पूर्णांकerval क्रम the
 * given frame क्रमmat and size. This should be करोne by the device as part of
 * the Video Probe and Commit negotiation, but some hardware करोn't implement
 * that feature.
 */
अटल u32 uvc_try_frame_पूर्णांकerval(काष्ठा uvc_frame *frame, u32 पूर्णांकerval)
अणु
	अचिन्हित पूर्णांक i;

	अगर (frame->bFrameIntervalType) अणु
		u32 best = -1, dist;

		क्रम (i = 0; i < frame->bFrameIntervalType; ++i) अणु
			dist = पूर्णांकerval > frame->dwFrameInterval[i]
			     ? पूर्णांकerval - frame->dwFrameInterval[i]
			     : frame->dwFrameInterval[i] - पूर्णांकerval;

			अगर (dist > best)
				अवरोध;

			best = dist;
		पूर्ण

		पूर्णांकerval = frame->dwFrameInterval[i-1];
	पूर्ण अन्यथा अणु
		स्थिर u32 min = frame->dwFrameInterval[0];
		स्थिर u32 max = frame->dwFrameInterval[1];
		स्थिर u32 step = frame->dwFrameInterval[2];

		पूर्णांकerval = min + (पूर्णांकerval - min + step/2) / step * step;
		अगर (पूर्णांकerval > max)
			पूर्णांकerval = max;
	पूर्ण

	वापस पूर्णांकerval;
पूर्ण

अटल u32 uvc_v4l2_get_bytesperline(स्थिर काष्ठा uvc_क्रमmat *क्रमmat,
	स्थिर काष्ठा uvc_frame *frame)
अणु
	चयन (क्रमmat->fcc) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_M420:
		वापस frame->wWidth;

	शेष:
		वापस क्रमmat->bpp * frame->wWidth / 8;
	पूर्ण
पूर्ण

अटल पूर्णांक uvc_v4l2_try_क्रमmat(काष्ठा uvc_streaming *stream,
	काष्ठा v4l2_क्रमmat *fmt, काष्ठा uvc_streaming_control *probe,
	काष्ठा uvc_क्रमmat **uvc_क्रमmat, काष्ठा uvc_frame **uvc_frame)
अणु
	काष्ठा uvc_क्रमmat *क्रमmat = शून्य;
	काष्ठा uvc_frame *frame = शून्य;
	u16 rw, rh;
	अचिन्हित पूर्णांक d, maxd;
	अचिन्हित पूर्णांक i;
	u32 पूर्णांकerval;
	पूर्णांक ret = 0;
	u8 *fcc;

	अगर (fmt->type != stream->type)
		वापस -EINVAL;

	fcc = (u8 *)&fmt->fmt.pix.pixelक्रमmat;
	uvc_dbg(stream->dev, FORMAT, "Trying format 0x%08x (%c%c%c%c): %ux%u\n",
		fmt->fmt.pix.pixelक्रमmat,
		fcc[0], fcc[1], fcc[2], fcc[3],
		fmt->fmt.pix.width, fmt->fmt.pix.height);

	/* Check अगर the hardware supports the requested क्रमmat, use the शेष
	 * क्रमmat otherwise.
	 */
	क्रम (i = 0; i < stream->nक्रमmats; ++i) अणु
		क्रमmat = &stream->क्रमmat[i];
		अगर (क्रमmat->fcc == fmt->fmt.pix.pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (i == stream->nक्रमmats) अणु
		क्रमmat = stream->def_क्रमmat;
		fmt->fmt.pix.pixelक्रमmat = क्रमmat->fcc;
	पूर्ण

	/* Find the बंदst image size. The distance between image sizes is
	 * the size in pixels of the non-overlapping regions between the
	 * requested size and the frame-specअगरied size.
	 */
	rw = fmt->fmt.pix.width;
	rh = fmt->fmt.pix.height;
	maxd = (अचिन्हित पूर्णांक)-1;

	क्रम (i = 0; i < क्रमmat->nframes; ++i) अणु
		u16 w = क्रमmat->frame[i].wWidth;
		u16 h = क्रमmat->frame[i].wHeight;

		d = min(w, rw) * min(h, rh);
		d = w*h + rw*rh - 2*d;
		अगर (d < maxd) अणु
			maxd = d;
			frame = &क्रमmat->frame[i];
		पूर्ण

		अगर (maxd == 0)
			अवरोध;
	पूर्ण

	अगर (frame == शून्य) अणु
		uvc_dbg(stream->dev, FORMAT, "Unsupported size %ux%u\n",
			fmt->fmt.pix.width, fmt->fmt.pix.height);
		वापस -EINVAL;
	पूर्ण

	/* Use the शेष frame पूर्णांकerval. */
	पूर्णांकerval = frame->dwDefaultFrameInterval;
	uvc_dbg(stream->dev, FORMAT,
		"Using default frame interval %u.%u us (%u.%u fps)\n",
		पूर्णांकerval / 10, पूर्णांकerval % 10, 10000000 / पूर्णांकerval,
		(100000000 / पूर्णांकerval) % 10);

	/* Set the क्रमmat index, frame index and frame पूर्णांकerval. */
	स_रखो(probe, 0, माप(*probe));
	probe->bmHपूर्णांक = 1;	/* dwFrameInterval */
	probe->bFormatIndex = क्रमmat->index;
	probe->bFrameIndex = frame->bFrameIndex;
	probe->dwFrameInterval = uvc_try_frame_पूर्णांकerval(frame, पूर्णांकerval);
	/* Some webcams stall the probe control set request when the
	 * dwMaxVideoFrameSize field is set to zero. The UVC specअगरication
	 * clearly states that the field is पढ़ो-only from the host, so this
	 * is a webcam bug. Set dwMaxVideoFrameSize to the value reported by
	 * the webcam to work around the problem.
	 *
	 * The workaround could probably be enabled क्रम all webcams, so the
	 * quirk can be हटाओd अगर needed. It's currently useful to detect
	 * webcam bugs and fix them beक्रमe they hit the market (providing
	 * developers test their webcams with the Linux driver as well as with
	 * the Winकरोws driver).
	 */
	mutex_lock(&stream->mutex);
	अगर (stream->dev->quirks & UVC_QUIRK_PROBE_EXTRAFIELDS)
		probe->dwMaxVideoFrameSize =
			stream->ctrl.dwMaxVideoFrameSize;

	/* Probe the device. */
	ret = uvc_probe_video(stream, probe);
	mutex_unlock(&stream->mutex);
	अगर (ret < 0)
		जाओ करोne;

	/* After the probe, update fmt with the values वापसed from
	 * negotiation with the device. Some devices वापस invalid bFormatIndex
	 * and bFrameIndex values, in which हाल we can only assume they have
	 * accepted the requested क्रमmat as-is.
	 */
	क्रम (i = 0; i < stream->nक्रमmats; ++i) अणु
		अगर (probe->bFormatIndex == stream->क्रमmat[i].index) अणु
			क्रमmat = &stream->क्रमmat[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == stream->nक्रमmats)
		uvc_dbg(stream->dev, FORMAT,
			"Unknown bFormatIndex %u, using default\n",
			probe->bFormatIndex);

	क्रम (i = 0; i < क्रमmat->nframes; ++i) अणु
		अगर (probe->bFrameIndex == क्रमmat->frame[i].bFrameIndex) अणु
			frame = &क्रमmat->frame[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == क्रमmat->nframes)
		uvc_dbg(stream->dev, FORMAT,
			"Unknown bFrameIndex %u, using default\n",
			probe->bFrameIndex);

	fmt->fmt.pix.width = frame->wWidth;
	fmt->fmt.pix.height = frame->wHeight;
	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = uvc_v4l2_get_bytesperline(क्रमmat, frame);
	fmt->fmt.pix.sizeimage = probe->dwMaxVideoFrameSize;
	fmt->fmt.pix.pixelक्रमmat = क्रमmat->fcc;
	fmt->fmt.pix.colorspace = क्रमmat->colorspace;
	fmt->fmt.pix.xfer_func = क्रमmat->xfer_func;
	fmt->fmt.pix.ycbcr_enc = क्रमmat->ycbcr_enc;

	अगर (uvc_क्रमmat != शून्य)
		*uvc_क्रमmat = क्रमmat;
	अगर (uvc_frame != शून्य)
		*uvc_frame = frame;

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक uvc_v4l2_get_क्रमmat(काष्ठा uvc_streaming *stream,
	काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_क्रमmat *क्रमmat;
	काष्ठा uvc_frame *frame;
	पूर्णांक ret = 0;

	अगर (fmt->type != stream->type)
		वापस -EINVAL;

	mutex_lock(&stream->mutex);
	क्रमmat = stream->cur_क्रमmat;
	frame = stream->cur_frame;

	अगर (क्रमmat == शून्य || frame == शून्य) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	fmt->fmt.pix.pixelक्रमmat = क्रमmat->fcc;
	fmt->fmt.pix.width = frame->wWidth;
	fmt->fmt.pix.height = frame->wHeight;
	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = uvc_v4l2_get_bytesperline(क्रमmat, frame);
	fmt->fmt.pix.sizeimage = stream->ctrl.dwMaxVideoFrameSize;
	fmt->fmt.pix.colorspace = क्रमmat->colorspace;
	fmt->fmt.pix.xfer_func = क्रमmat->xfer_func;
	fmt->fmt.pix.ycbcr_enc = क्रमmat->ycbcr_enc;

करोne:
	mutex_unlock(&stream->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक uvc_v4l2_set_क्रमmat(काष्ठा uvc_streaming *stream,
	काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_streaming_control probe;
	काष्ठा uvc_क्रमmat *क्रमmat;
	काष्ठा uvc_frame *frame;
	पूर्णांक ret;

	अगर (fmt->type != stream->type)
		वापस -EINVAL;

	ret = uvc_v4l2_try_क्रमmat(stream, fmt, &probe, &क्रमmat, &frame);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&stream->mutex);

	अगर (uvc_queue_allocated(&stream->queue)) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	stream->ctrl = probe;
	stream->cur_क्रमmat = क्रमmat;
	stream->cur_frame = frame;

करोne:
	mutex_unlock(&stream->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक uvc_v4l2_get_streamparm(काष्ठा uvc_streaming *stream,
		काष्ठा v4l2_streamparm *parm)
अणु
	u32 numerator, denominator;

	अगर (parm->type != stream->type)
		वापस -EINVAL;

	mutex_lock(&stream->mutex);
	numerator = stream->ctrl.dwFrameInterval;
	mutex_unlock(&stream->mutex);

	denominator = 10000000;
	uvc_simplअगरy_fraction(&numerator, &denominator, 8, 333);

	स_रखो(parm, 0, माप(*parm));
	parm->type = stream->type;

	अगर (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
		parm->parm.capture.capturemode = 0;
		parm->parm.capture.समयperframe.numerator = numerator;
		parm->parm.capture.समयperframe.denominator = denominator;
		parm->parm.capture.extendedmode = 0;
		parm->parm.capture.पढ़ोbuffers = 0;
	पूर्ण अन्यथा अणु
		parm->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
		parm->parm.output.outpuपंचांगode = 0;
		parm->parm.output.समयperframe.numerator = numerator;
		parm->parm.output.समयperframe.denominator = denominator;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_v4l2_set_streamparm(काष्ठा uvc_streaming *stream,
		काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा uvc_streaming_control probe;
	काष्ठा v4l2_fract समयperframe;
	काष्ठा uvc_क्रमmat *क्रमmat;
	काष्ठा uvc_frame *frame;
	u32 पूर्णांकerval, maxd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (parm->type != stream->type)
		वापस -EINVAL;

	अगर (parm->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		समयperframe = parm->parm.capture.समयperframe;
	अन्यथा
		समयperframe = parm->parm.output.समयperframe;

	पूर्णांकerval = uvc_fraction_to_पूर्णांकerval(समयperframe.numerator,
		समयperframe.denominator);
	uvc_dbg(stream->dev, FORMAT, "Setting frame interval to %u/%u (%u)\n",
		समयperframe.numerator, समयperframe.denominator, पूर्णांकerval);

	mutex_lock(&stream->mutex);

	अगर (uvc_queue_streaming(&stream->queue)) अणु
		mutex_unlock(&stream->mutex);
		वापस -EBUSY;
	पूर्ण

	क्रमmat = stream->cur_क्रमmat;
	frame = stream->cur_frame;
	probe = stream->ctrl;
	probe.dwFrameInterval = uvc_try_frame_पूर्णांकerval(frame, पूर्णांकerval);
	maxd = असल((s32)probe.dwFrameInterval - पूर्णांकerval);

	/* Try frames with matching size to find the best frame पूर्णांकerval. */
	क्रम (i = 0; i < क्रमmat->nframes && maxd != 0; i++) अणु
		u32 d, ival;

		अगर (&क्रमmat->frame[i] == stream->cur_frame)
			जारी;

		अगर (क्रमmat->frame[i].wWidth != stream->cur_frame->wWidth ||
		    क्रमmat->frame[i].wHeight != stream->cur_frame->wHeight)
			जारी;

		ival = uvc_try_frame_पूर्णांकerval(&क्रमmat->frame[i], पूर्णांकerval);
		d = असल((s32)ival - पूर्णांकerval);
		अगर (d >= maxd)
			जारी;

		frame = &क्रमmat->frame[i];
		probe.bFrameIndex = frame->bFrameIndex;
		probe.dwFrameInterval = ival;
		maxd = d;
	पूर्ण

	/* Probe the device with the new settings. */
	ret = uvc_probe_video(stream, &probe);
	अगर (ret < 0) अणु
		mutex_unlock(&stream->mutex);
		वापस ret;
	पूर्ण

	stream->ctrl = probe;
	stream->cur_frame = frame;
	mutex_unlock(&stream->mutex);

	/* Return the actual frame period. */
	समयperframe.numerator = probe.dwFrameInterval;
	समयperframe.denominator = 10000000;
	uvc_simplअगरy_fraction(&समयperframe.numerator,
		&समयperframe.denominator, 8, 333);

	अगर (parm->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		parm->parm.capture.समयperframe = समयperframe;
	अन्यथा
		parm->parm.output.समयperframe = समयperframe;

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------
 * Privilege management
 */

/*
 * Privilege management is the multiple-खोलो implementation basis. The current
 * implementation is completely transparent क्रम the end-user and करोesn't
 * require explicit use of the VIDIOC_G_PRIORITY and VIDIOC_S_PRIORITY ioctls.
 * Those ioctls enable finer control on the device (by making possible क्रम a
 * user to request exclusive access to a device), but are not mature yet.
 * Switching to the V4L2 priority mechanism might be considered in the future
 * अगर this situation changes.
 *
 * Each खोलो instance of a UVC device can either be in a privileged or
 * unprivileged state. Only a single instance can be in a privileged state at
 * a given समय. Trying to perक्रमm an operation that requires privileges will
 * स्वतःmatically acquire the required privileges अगर possible, or वापस -EBUSY
 * otherwise. Privileges are dismissed when closing the instance or when
 * मुक्तing the video buffers using VIDIOC_REQBUFS.
 *
 * Operations that require privileges are:
 *
 * - VIDIOC_S_INPUT
 * - VIDIOC_S_PARM
 * - VIDIOC_S_FMT
 * - VIDIOC_REQBUFS
 */
अटल पूर्णांक uvc_acquire_privileges(काष्ठा uvc_fh *handle)
अणु
	/* Always succeed अगर the handle is alपढ़ोy privileged. */
	अगर (handle->state == UVC_HANDLE_ACTIVE)
		वापस 0;

	/* Check अगर the device alपढ़ोy has a privileged handle. */
	अगर (atomic_inc_वापस(&handle->stream->active) != 1) अणु
		atomic_dec(&handle->stream->active);
		वापस -EBUSY;
	पूर्ण

	handle->state = UVC_HANDLE_ACTIVE;
	वापस 0;
पूर्ण

अटल व्योम uvc_dismiss_privileges(काष्ठा uvc_fh *handle)
अणु
	अगर (handle->state == UVC_HANDLE_ACTIVE)
		atomic_dec(&handle->stream->active);

	handle->state = UVC_HANDLE_PASSIVE;
पूर्ण

अटल पूर्णांक uvc_has_privileges(काष्ठा uvc_fh *handle)
अणु
	वापस handle->state == UVC_HANDLE_ACTIVE;
पूर्ण

/* ------------------------------------------------------------------------
 * V4L2 file operations
 */

अटल पूर्णांक uvc_v4l2_खोलो(काष्ठा file *file)
अणु
	काष्ठा uvc_streaming *stream;
	काष्ठा uvc_fh *handle;
	पूर्णांक ret = 0;

	stream = video_drvdata(file);
	uvc_dbg(stream->dev, CALLS, "%s\n", __func__);

	ret = usb_स्वतःpm_get_पूर्णांकerface(stream->dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	/* Create the device handle. */
	handle = kzalloc(माप(*handle), GFP_KERNEL);
	अगर (handle == शून्य) अणु
		usb_स्वतःpm_put_पूर्णांकerface(stream->dev->पूर्णांकf);
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&stream->dev->lock);
	अगर (stream->dev->users == 0) अणु
		ret = uvc_status_start(stream->dev, GFP_KERNEL);
		अगर (ret < 0) अणु
			mutex_unlock(&stream->dev->lock);
			usb_स्वतःpm_put_पूर्णांकerface(stream->dev->पूर्णांकf);
			kमुक्त(handle);
			वापस ret;
		पूर्ण
	पूर्ण

	stream->dev->users++;
	mutex_unlock(&stream->dev->lock);

	v4l2_fh_init(&handle->vfh, &stream->vdev);
	v4l2_fh_add(&handle->vfh);
	handle->chain = stream->chain;
	handle->stream = stream;
	handle->state = UVC_HANDLE_PASSIVE;
	file->निजी_data = handle;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_v4l2_release(काष्ठा file *file)
अणु
	काष्ठा uvc_fh *handle = file->निजी_data;
	काष्ठा uvc_streaming *stream = handle->stream;

	uvc_dbg(stream->dev, CALLS, "%s\n", __func__);

	/* Only मुक्त resources अगर this is a privileged handle. */
	अगर (uvc_has_privileges(handle))
		uvc_queue_release(&stream->queue);

	/* Release the file handle. */
	uvc_dismiss_privileges(handle);
	v4l2_fh_del(&handle->vfh);
	v4l2_fh_निकास(&handle->vfh);
	kमुक्त(handle);
	file->निजी_data = शून्य;

	mutex_lock(&stream->dev->lock);
	अगर (--stream->dev->users == 0)
		uvc_status_stop(stream->dev);
	mutex_unlock(&stream->dev->lock);

	usb_स्वतःpm_put_पूर्णांकerface(stream->dev->पूर्णांकf);
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_querycap(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_capability *cap)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_fh *handle = file->निजी_data;
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा uvc_streaming *stream = handle->stream;

	strscpy(cap->driver, "uvcvideo", माप(cap->driver));
	strscpy(cap->card, vdev->name, माप(cap->card));
	usb_make_path(stream->dev->udev, cap->bus_info, माप(cap->bus_info));
	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | chain->caps;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_क्रमागत_fmt(काष्ठा uvc_streaming *stream,
			      काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा uvc_क्रमmat *क्रमmat;
	क्रमागत v4l2_buf_type type = fmt->type;
	u32 index = fmt->index;

	अगर (fmt->type != stream->type || fmt->index >= stream->nक्रमmats)
		वापस -EINVAL;

	स_रखो(fmt, 0, माप(*fmt));
	fmt->index = index;
	fmt->type = type;

	क्रमmat = &stream->क्रमmat[fmt->index];
	fmt->flags = 0;
	अगर (क्रमmat->flags & UVC_FMT_FLAG_COMPRESSED)
		fmt->flags |= V4L2_FMT_FLAG_COMPRESSED;
	strscpy(fmt->description, क्रमmat->name, माप(fmt->description));
	fmt->description[माप(fmt->description) - 1] = 0;
	fmt->pixelक्रमmat = क्रमmat->fcc;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	वापस uvc_ioctl_क्रमागत_fmt(stream, fmt);
पूर्ण

अटल पूर्णांक uvc_ioctl_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	वापस uvc_ioctl_क्रमागत_fmt(stream, fmt);
पूर्ण

अटल पूर्णांक uvc_ioctl_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	वापस uvc_v4l2_get_क्रमmat(stream, fmt);
पूर्ण

अटल पूर्णांक uvc_ioctl_g_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	वापस uvc_v4l2_get_क्रमmat(stream, fmt);
पूर्ण

अटल पूर्णांक uvc_ioctl_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	पूर्णांक ret;

	ret = uvc_acquire_privileges(handle);
	अगर (ret < 0)
		वापस ret;

	वापस uvc_v4l2_set_क्रमmat(stream, fmt);
पूर्ण

अटल पूर्णांक uvc_ioctl_s_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	पूर्णांक ret;

	ret = uvc_acquire_privileges(handle);
	अगर (ret < 0)
		वापस ret;

	वापस uvc_v4l2_set_क्रमmat(stream, fmt);
पूर्ण

अटल पूर्णांक uvc_ioctl_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	काष्ठा uvc_streaming_control probe;

	वापस uvc_v4l2_try_क्रमmat(stream, fmt, &probe, शून्य, शून्य);
पूर्ण

अटल पूर्णांक uvc_ioctl_try_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	काष्ठा uvc_streaming_control probe;

	वापस uvc_v4l2_try_क्रमmat(stream, fmt, &probe, शून्य, शून्य);
पूर्ण

अटल पूर्णांक uvc_ioctl_reqbufs(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	पूर्णांक ret;

	ret = uvc_acquire_privileges(handle);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&stream->mutex);
	ret = uvc_request_buffers(&stream->queue, rb);
	mutex_unlock(&stream->mutex);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0)
		uvc_dismiss_privileges(handle);

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_querybuf(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	अगर (!uvc_has_privileges(handle))
		वापस -EBUSY;

	वापस uvc_query_buffer(&stream->queue, buf);
पूर्ण

अटल पूर्णांक uvc_ioctl_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	अगर (!uvc_has_privileges(handle))
		वापस -EBUSY;

	वापस uvc_queue_buffer(&stream->queue,
				stream->vdev.v4l2_dev->mdev, buf);
पूर्ण

अटल पूर्णांक uvc_ioctl_expbuf(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_exportbuffer *exp)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	अगर (!uvc_has_privileges(handle))
		वापस -EBUSY;

	वापस uvc_export_buffer(&stream->queue, exp);
पूर्ण

अटल पूर्णांक uvc_ioctl_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	अगर (!uvc_has_privileges(handle))
		वापस -EBUSY;

	वापस uvc_dequeue_buffer(&stream->queue, buf,
				  file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक uvc_ioctl_create_bufs(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_create_buffers *cb)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	पूर्णांक ret;

	ret = uvc_acquire_privileges(handle);
	अगर (ret < 0)
		वापस ret;

	वापस uvc_create_buffers(&stream->queue, cb);
पूर्ण

अटल पूर्णांक uvc_ioctl_streamon(काष्ठा file *file, व्योम *fh,
			      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	पूर्णांक ret;

	अगर (!uvc_has_privileges(handle))
		वापस -EBUSY;

	mutex_lock(&stream->mutex);
	ret = uvc_queue_streamon(&stream->queue, type);
	mutex_unlock(&stream->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक uvc_ioctl_streamoff(काष्ठा file *file, व्योम *fh,
			       क्रमागत v4l2_buf_type type)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	अगर (!uvc_has_privileges(handle))
		वापस -EBUSY;

	mutex_lock(&stream->mutex);
	uvc_queue_streamoff(&stream->queue, type);
	mutex_unlock(&stream->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_क्रमागत_input(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_input *input)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	स्थिर काष्ठा uvc_entity *selector = chain->selector;
	काष्ठा uvc_entity *iterm = शून्य;
	u32 index = input->index;
	पूर्णांक pin = 0;

	अगर (selector == शून्य ||
	    (chain->dev->quirks & UVC_QUIRK_IGNORE_SELECTOR_UNIT)) अणु
		अगर (index != 0)
			वापस -EINVAL;
		list_क्रम_each_entry(iterm, &chain->entities, chain) अणु
			अगर (UVC_ENTITY_IS_ITERM(iterm))
				अवरोध;
		पूर्ण
		pin = iterm->id;
	पूर्ण अन्यथा अगर (index < selector->bNrInPins) अणु
		pin = selector->baSourceID[index];
		list_क्रम_each_entry(iterm, &chain->entities, chain) अणु
			अगर (!UVC_ENTITY_IS_ITERM(iterm))
				जारी;
			अगर (iterm->id == pin)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (iterm == शून्य || iterm->id != pin)
		वापस -EINVAL;

	स_रखो(input, 0, माप(*input));
	input->index = index;
	strscpy(input->name, iterm->name, माप(input->name));
	अगर (UVC_ENTITY_TYPE(iterm) == UVC_ITT_CAMERA)
		input->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	पूर्णांक ret;
	u8 i;

	अगर (chain->selector == शून्य ||
	    (chain->dev->quirks & UVC_QUIRK_IGNORE_SELECTOR_UNIT)) अणु
		*input = 0;
		वापस 0;
	पूर्ण

	ret = uvc_query_ctrl(chain->dev, UVC_GET_CUR, chain->selector->id,
			     chain->dev->पूर्णांकfnum,  UVC_SU_INPUT_SELECT_CONTROL,
			     &i, 1);
	अगर (ret < 0)
		वापस ret;

	*input = i - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	पूर्णांक ret;
	u32 i;

	ret = uvc_acquire_privileges(handle);
	अगर (ret < 0)
		वापस ret;

	अगर (chain->selector == शून्य ||
	    (chain->dev->quirks & UVC_QUIRK_IGNORE_SELECTOR_UNIT)) अणु
		अगर (input)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर (input >= chain->selector->bNrInPins)
		वापस -EINVAL;

	i = input + 1;
	वापस uvc_query_ctrl(chain->dev, UVC_SET_CUR, chain->selector->id,
			      chain->dev->पूर्णांकfnum, UVC_SU_INPUT_SELECT_CONTROL,
			      &i, 1);
पूर्ण

अटल पूर्णांक uvc_ioctl_queryctrl(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_queryctrl *qc)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;

	वापस uvc_query_v4l2_ctrl(chain, qc);
पूर्ण

अटल पूर्णांक uvc_ioctl_query_ext_ctrl(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_query_ext_ctrl *qec)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा v4l2_queryctrl qc = अणु qec->id पूर्ण;
	पूर्णांक ret;

	ret = uvc_query_v4l2_ctrl(chain, &qc);
	अगर (ret)
		वापस ret;

	qec->id = qc.id;
	qec->type = qc.type;
	strscpy(qec->name, qc.name, माप(qec->name));
	qec->minimum = qc.minimum;
	qec->maximum = qc.maximum;
	qec->step = qc.step;
	qec->शेष_value = qc.शेष_value;
	qec->flags = qc.flags;
	qec->elem_size = 4;
	qec->elems = 1;
	qec->nr_of_dims = 0;
	स_रखो(qec->dims, 0, माप(qec->dims));
	स_रखो(qec->reserved, 0, माप(qec->reserved));

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_g_ctrl(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_control *ctrl)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा v4l2_ext_control xctrl;
	पूर्णांक ret;

	स_रखो(&xctrl, 0, माप(xctrl));
	xctrl.id = ctrl->id;

	ret = uvc_ctrl_begin(chain);
	अगर (ret < 0)
		वापस ret;

	ret = uvc_ctrl_get(chain, &xctrl);
	uvc_ctrl_rollback(handle);
	अगर (ret < 0)
		वापस ret;

	ctrl->value = xctrl.value;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_s_ctrl(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_control *ctrl)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा v4l2_ext_control xctrl;
	पूर्णांक ret;

	स_रखो(&xctrl, 0, माप(xctrl));
	xctrl.id = ctrl->id;
	xctrl.value = ctrl->value;

	ret = uvc_ctrl_begin(chain);
	अगर (ret < 0)
		वापस ret;

	ret = uvc_ctrl_set(handle, &xctrl);
	अगर (ret < 0) अणु
		uvc_ctrl_rollback(handle);
		वापस ret;
	पूर्ण

	ret = uvc_ctrl_commit(handle, &xctrl, 1);
	अगर (ret < 0)
		वापस ret;

	ctrl->value = xctrl.value;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_g_ext_ctrls(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_ext_controls *ctrls)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा v4l2_ext_control *ctrl = ctrls->controls;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (ctrls->which == V4L2_CTRL_WHICH_DEF_VAL) अणु
		क्रम (i = 0; i < ctrls->count; ++ctrl, ++i) अणु
			काष्ठा v4l2_queryctrl qc = अणु .id = ctrl->id पूर्ण;

			ret = uvc_query_v4l2_ctrl(chain, &qc);
			अगर (ret < 0) अणु
				ctrls->error_idx = i;
				वापस ret;
			पूर्ण

			ctrl->value = qc.शेष_value;
		पूर्ण

		वापस 0;
	पूर्ण

	ret = uvc_ctrl_begin(chain);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ctrls->count; ++ctrl, ++i) अणु
		ret = uvc_ctrl_get(chain, ctrl);
		अगर (ret < 0) अणु
			uvc_ctrl_rollback(handle);
			ctrls->error_idx = i;
			वापस ret;
		पूर्ण
	पूर्ण

	ctrls->error_idx = 0;

	वापस uvc_ctrl_rollback(handle);
पूर्ण

अटल पूर्णांक uvc_ioctl_s_try_ext_ctrls(काष्ठा uvc_fh *handle,
				     काष्ठा v4l2_ext_controls *ctrls,
				     bool commit)
अणु
	काष्ठा v4l2_ext_control *ctrl = ctrls->controls;
	काष्ठा uvc_video_chain *chain = handle->chain;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Default value cannot be changed */
	अगर (ctrls->which == V4L2_CTRL_WHICH_DEF_VAL)
		वापस -EINVAL;

	ret = uvc_ctrl_begin(chain);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ctrls->count; ++ctrl, ++i) अणु
		ret = uvc_ctrl_set(handle, ctrl);
		अगर (ret < 0) अणु
			uvc_ctrl_rollback(handle);
			ctrls->error_idx = commit ? ctrls->count : i;
			वापस ret;
		पूर्ण
	पूर्ण

	ctrls->error_idx = 0;

	अगर (commit)
		वापस uvc_ctrl_commit(handle, ctrls->controls, ctrls->count);
	अन्यथा
		वापस uvc_ctrl_rollback(handle);
पूर्ण

अटल पूर्णांक uvc_ioctl_s_ext_ctrls(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_ext_controls *ctrls)
अणु
	काष्ठा uvc_fh *handle = fh;

	वापस uvc_ioctl_s_try_ext_ctrls(handle, ctrls, true);
पूर्ण

अटल पूर्णांक uvc_ioctl_try_ext_ctrls(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_ext_controls *ctrls)
अणु
	काष्ठा uvc_fh *handle = fh;

	वापस uvc_ioctl_s_try_ext_ctrls(handle, ctrls, false);
पूर्ण

अटल पूर्णांक uvc_ioctl_querymenu(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_querymenu *qm)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;

	वापस uvc_query_v4l2_menu(chain, qm);
पूर्ण

अटल पूर्णांक uvc_ioctl_g_selection(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_selection *sel)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	अगर (sel->type != stream->type)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (stream->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (stream->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sel->r.left = 0;
	sel->r.top = 0;
	mutex_lock(&stream->mutex);
	sel->r.width = stream->cur_frame->wWidth;
	sel->r.height = stream->cur_frame->wHeight;
	mutex_unlock(&stream->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_g_parm(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;

	वापस uvc_v4l2_get_streamparm(stream, parm);
पूर्ण

अटल पूर्णांक uvc_ioctl_s_parm(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	पूर्णांक ret;

	ret = uvc_acquire_privileges(handle);
	अगर (ret < 0)
		वापस ret;

	वापस uvc_v4l2_set_streamparm(stream, parm);
पूर्ण

अटल पूर्णांक uvc_ioctl_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	काष्ठा uvc_क्रमmat *क्रमmat = शून्य;
	काष्ठा uvc_frame *frame = शून्य;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक i;

	/* Look क्रम the given pixel क्रमmat */
	क्रम (i = 0; i < stream->nक्रमmats; i++) अणु
		अगर (stream->क्रमmat[i].fcc == fsize->pixel_क्रमmat) अणु
			क्रमmat = &stream->क्रमmat[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	/* Skip duplicate frame sizes */
	क्रम (i = 0, index = 0; i < क्रमmat->nframes; i++) अणु
		अगर (frame && frame->wWidth == क्रमmat->frame[i].wWidth &&
		    frame->wHeight == क्रमmat->frame[i].wHeight)
			जारी;
		frame = &क्रमmat->frame[i];
		अगर (index == fsize->index)
			अवरोध;
		index++;
	पूर्ण

	अगर (i == क्रमmat->nframes)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = frame->wWidth;
	fsize->discrete.height = frame->wHeight;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_streaming *stream = handle->stream;
	काष्ठा uvc_क्रमmat *क्रमmat = शून्य;
	काष्ठा uvc_frame *frame = शून्य;
	अचिन्हित पूर्णांक nपूर्णांकervals;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक i;

	/* Look क्रम the given pixel क्रमmat and frame size */
	क्रम (i = 0; i < stream->nक्रमmats; i++) अणु
		अगर (stream->क्रमmat[i].fcc == fival->pixel_क्रमmat) अणु
			क्रमmat = &stream->क्रमmat[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	index = fival->index;
	क्रम (i = 0; i < क्रमmat->nframes; i++) अणु
		अगर (क्रमmat->frame[i].wWidth == fival->width &&
		    क्रमmat->frame[i].wHeight == fival->height) अणु
			frame = &क्रमmat->frame[i];
			nपूर्णांकervals = frame->bFrameIntervalType ?: 1;
			अगर (index < nपूर्णांकervals)
				अवरोध;
			index -= nपूर्णांकervals;
		पूर्ण
	पूर्ण
	अगर (i == क्रमmat->nframes)
		वापस -EINVAL;

	अगर (frame->bFrameIntervalType) अणु
		fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
		fival->discrete.numerator =
			frame->dwFrameInterval[index];
		fival->discrete.denominator = 10000000;
		uvc_simplअगरy_fraction(&fival->discrete.numerator,
			&fival->discrete.denominator, 8, 333);
	पूर्ण अन्यथा अणु
		fival->type = V4L2_FRMIVAL_TYPE_STEPWISE;
		fival->stepwise.min.numerator = frame->dwFrameInterval[0];
		fival->stepwise.min.denominator = 10000000;
		fival->stepwise.max.numerator = frame->dwFrameInterval[1];
		fival->stepwise.max.denominator = 10000000;
		fival->stepwise.step.numerator = frame->dwFrameInterval[2];
		fival->stepwise.step.denominator = 10000000;
		uvc_simplअगरy_fraction(&fival->stepwise.min.numerator,
			&fival->stepwise.min.denominator, 8, 333);
		uvc_simplअगरy_fraction(&fival->stepwise.max.numerator,
			&fival->stepwise.max.denominator, 8, 333);
		uvc_simplअगरy_fraction(&fival->stepwise.step.numerator,
			&fival->stepwise.step.denominator, 8, 333);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_ioctl_subscribe_event(काष्ठा v4l2_fh *fh,
				     स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_event_subscribe(fh, sub, 0, &uvc_ctrl_sub_ev_ops);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ uvc_ioctl_शेष(काष्ठा file *file, व्योम *fh, bool valid_prio,
			      अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा uvc_fh *handle = fh;
	काष्ठा uvc_video_chain *chain = handle->chain;

	चयन (cmd) अणु
	/* Dynamic controls. */
	हाल UVCIOC_CTRL_MAP:
		वापस uvc_ioctl_ctrl_map(chain, arg);

	हाल UVCIOC_CTRL_QUERY:
		वापस uvc_xu_ctrl_query(chain, arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा uvc_xu_control_mapping32 अणु
	u32 id;
	u8 name[32];
	u8 entity[16];
	u8 selector;

	u8 size;
	u8 offset;
	u32 v4l2_type;
	u32 data_type;

	compat_caddr_t menu_info;
	u32 menu_count;

	u32 reserved[4];
पूर्ण;

अटल पूर्णांक uvc_v4l2_get_xu_mapping(काष्ठा uvc_xu_control_mapping *kp,
			स्थिर काष्ठा uvc_xu_control_mapping32 __user *up)
अणु
	काष्ठा uvc_xu_control_mapping32 *p = (व्योम *)kp;
	compat_caddr_t info;
	u32 count;

	अगर (copy_from_user(p, up, माप(*p)))
		वापस -EFAULT;

	count = p->menu_count;
	info = p->menu_info;

	स_रखो(kp->reserved, 0, माप(kp->reserved));
	kp->menu_info = count ? compat_ptr(info) : शून्य;
	kp->menu_count = count;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_v4l2_put_xu_mapping(स्थिर काष्ठा uvc_xu_control_mapping *kp,
			काष्ठा uvc_xu_control_mapping32 __user *up)
अणु
	अगर (copy_to_user(up, kp, दुरत्व(typeof(*up), menu_info)) ||
	    put_user(kp->menu_count, &up->menu_count))
		वापस -EFAULT;

	अगर (clear_user(up->reserved, माप(up->reserved)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा uvc_xu_control_query32 अणु
	u8 unit;
	u8 selector;
	u8 query;
	u16 size;
	compat_caddr_t data;
पूर्ण;

अटल पूर्णांक uvc_v4l2_get_xu_query(काष्ठा uvc_xu_control_query *kp,
			स्थिर काष्ठा uvc_xu_control_query32 __user *up)
अणु
	काष्ठा uvc_xu_control_query32 v;

	अगर (copy_from_user(&v, up, माप(v)))
		वापस -EFAULT;

	*kp = (काष्ठा uvc_xu_control_query)अणु
		.unit = v.unit,
		.selector = v.selector,
		.query = v.query,
		.size = v.size,
		.data = v.size ? compat_ptr(v.data) : शून्य
	पूर्ण;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_v4l2_put_xu_query(स्थिर काष्ठा uvc_xu_control_query *kp,
			काष्ठा uvc_xu_control_query32 __user *up)
अणु
	अगर (copy_to_user(up, kp, दुरत्व(typeof(*up), data)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#घोषणा UVCIOC_CTRL_MAP32	_IOWR('u', 0x20, काष्ठा uvc_xu_control_mapping32)
#घोषणा UVCIOC_CTRL_QUERY32	_IOWR('u', 0x21, काष्ठा uvc_xu_control_query32)

अटल दीर्घ uvc_v4l2_compat_ioctl32(काष्ठा file *file,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा uvc_fh *handle = file->निजी_data;
	जोड़ अणु
		काष्ठा uvc_xu_control_mapping xmap;
		काष्ठा uvc_xu_control_query xqry;
	पूर्ण karg;
	व्योम __user *up = compat_ptr(arg);
	दीर्घ ret;

	चयन (cmd) अणु
	हाल UVCIOC_CTRL_MAP32:
		ret = uvc_v4l2_get_xu_mapping(&karg.xmap, up);
		अगर (ret)
			वापस ret;
		ret = uvc_ioctl_ctrl_map(handle->chain, &karg.xmap);
		अगर (ret)
			वापस ret;
		ret = uvc_v4l2_put_xu_mapping(&karg.xmap, up);
		अगर (ret)
			वापस ret;

		अवरोध;

	हाल UVCIOC_CTRL_QUERY32:
		ret = uvc_v4l2_get_xu_query(&karg.xqry, up);
		अगर (ret)
			वापस ret;
		ret = uvc_xu_ctrl_query(handle->chain, &karg.xqry);
		अगर (ret)
			वापस ret;
		ret = uvc_v4l2_put_xu_query(&karg.xqry, up);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार uvc_v4l2_पढ़ो(काष्ठा file *file, अक्षर __user *data,
		    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uvc_fh *handle = file->निजी_data;
	काष्ठा uvc_streaming *stream = handle->stream;

	uvc_dbg(stream->dev, CALLS, "%s: not implemented\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक uvc_v4l2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा uvc_fh *handle = file->निजी_data;
	काष्ठा uvc_streaming *stream = handle->stream;

	uvc_dbg(stream->dev, CALLS, "%s\n", __func__);

	वापस uvc_queue_mmap(&stream->queue, vma);
पूर्ण

अटल __poll_t uvc_v4l2_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा uvc_fh *handle = file->निजी_data;
	काष्ठा uvc_streaming *stream = handle->stream;

	uvc_dbg(stream->dev, CALLS, "%s\n", __func__);

	वापस uvc_queue_poll(&stream->queue, file, रुको);
पूर्ण

#अगर_अघोषित CONFIG_MMU
अटल अचिन्हित दीर्घ uvc_v4l2_get_unmapped_area(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा uvc_fh *handle = file->निजी_data;
	काष्ठा uvc_streaming *stream = handle->stream;

	uvc_dbg(stream->dev, CALLS, "%s\n", __func__);

	वापस uvc_queue_get_unmapped_area(&stream->queue, pgoff);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा v4l2_ioctl_ops uvc_ioctl_ops = अणु
	.vidioc_querycap = uvc_ioctl_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = uvc_ioctl_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out = uvc_ioctl_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_cap = uvc_ioctl_g_fmt_vid_cap,
	.vidioc_g_fmt_vid_out = uvc_ioctl_g_fmt_vid_out,
	.vidioc_s_fmt_vid_cap = uvc_ioctl_s_fmt_vid_cap,
	.vidioc_s_fmt_vid_out = uvc_ioctl_s_fmt_vid_out,
	.vidioc_try_fmt_vid_cap = uvc_ioctl_try_fmt_vid_cap,
	.vidioc_try_fmt_vid_out = uvc_ioctl_try_fmt_vid_out,
	.vidioc_reqbufs = uvc_ioctl_reqbufs,
	.vidioc_querybuf = uvc_ioctl_querybuf,
	.vidioc_qbuf = uvc_ioctl_qbuf,
	.vidioc_expbuf = uvc_ioctl_expbuf,
	.vidioc_dqbuf = uvc_ioctl_dqbuf,
	.vidioc_create_bufs = uvc_ioctl_create_bufs,
	.vidioc_streamon = uvc_ioctl_streamon,
	.vidioc_streamoff = uvc_ioctl_streamoff,
	.vidioc_क्रमागत_input = uvc_ioctl_क्रमागत_input,
	.vidioc_g_input = uvc_ioctl_g_input,
	.vidioc_s_input = uvc_ioctl_s_input,
	.vidioc_queryctrl = uvc_ioctl_queryctrl,
	.vidioc_query_ext_ctrl = uvc_ioctl_query_ext_ctrl,
	.vidioc_g_ctrl = uvc_ioctl_g_ctrl,
	.vidioc_s_ctrl = uvc_ioctl_s_ctrl,
	.vidioc_g_ext_ctrls = uvc_ioctl_g_ext_ctrls,
	.vidioc_s_ext_ctrls = uvc_ioctl_s_ext_ctrls,
	.vidioc_try_ext_ctrls = uvc_ioctl_try_ext_ctrls,
	.vidioc_querymenu = uvc_ioctl_querymenu,
	.vidioc_g_selection = uvc_ioctl_g_selection,
	.vidioc_g_parm = uvc_ioctl_g_parm,
	.vidioc_s_parm = uvc_ioctl_s_parm,
	.vidioc_क्रमागत_framesizes = uvc_ioctl_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = uvc_ioctl_क्रमागत_frameपूर्णांकervals,
	.vidioc_subscribe_event = uvc_ioctl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_शेष = uvc_ioctl_शेष,
पूर्ण;

स्थिर काष्ठा v4l2_file_operations uvc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uvc_v4l2_खोलो,
	.release	= uvc_v4l2_release,
	.unlocked_ioctl	= video_ioctl2,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl32	= uvc_v4l2_compat_ioctl32,
#पूर्ण_अगर
	.पढ़ो		= uvc_v4l2_पढ़ो,
	.mmap		= uvc_v4l2_mmap,
	.poll		= uvc_v4l2_poll,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area = uvc_v4l2_get_unmapped_area,
#पूर्ण_अगर
पूर्ण;

