<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_video.c  --  USB Video Class driver - Video handling
 *
 *      Copyright (C) 2005-2010
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <media/v4l2-common.h>

#समावेश "uvcvideo.h"

/* ------------------------------------------------------------------------
 * UVC Controls
 */

अटल पूर्णांक __uvc_query_ctrl(काष्ठा uvc_device *dev, u8 query, u8 unit,
			u8 पूर्णांकfnum, u8 cs, व्योम *data, u16 size,
			पूर्णांक समयout)
अणु
	u8 type = USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	अचिन्हित पूर्णांक pipe;

	pipe = (query & 0x80) ? usb_rcvctrlpipe(dev->udev, 0)
			      : usb_sndctrlpipe(dev->udev, 0);
	type |= (query & 0x80) ? USB_सूची_IN : USB_सूची_OUT;

	वापस usb_control_msg(dev->udev, pipe, query, type, cs << 8,
			unit << 8 | पूर्णांकfnum, data, size, समयout);
पूर्ण

अटल स्थिर अक्षर *uvc_query_name(u8 query)
अणु
	चयन (query) अणु
	हाल UVC_SET_CUR:
		वापस "SET_CUR";
	हाल UVC_GET_CUR:
		वापस "GET_CUR";
	हाल UVC_GET_MIN:
		वापस "GET_MIN";
	हाल UVC_GET_MAX:
		वापस "GET_MAX";
	हाल UVC_GET_RES:
		वापस "GET_RES";
	हाल UVC_GET_LEN:
		वापस "GET_LEN";
	हाल UVC_GET_INFO:
		वापस "GET_INFO";
	हाल UVC_GET_DEF:
		वापस "GET_DEF";
	शेष:
		वापस "<invalid>";
	पूर्ण
पूर्ण

पूर्णांक uvc_query_ctrl(काष्ठा uvc_device *dev, u8 query, u8 unit,
			u8 पूर्णांकfnum, u8 cs, व्योम *data, u16 size)
अणु
	पूर्णांक ret;
	u8 error;
	u8 पंचांगp;

	ret = __uvc_query_ctrl(dev, query, unit, पूर्णांकfnum, cs, data, size,
				UVC_CTRL_CONTROL_TIMEOUT);
	अगर (likely(ret == size))
		वापस 0;

	dev_err(&dev->udev->dev,
		"Failed to query (%s) UVC control %u on unit %u: %d (exp. %u).\n",
		uvc_query_name(query), cs, unit, ret, size);

	अगर (ret != -EPIPE)
		वापस ret;

	पंचांगp = *(u8 *)data;

	ret = __uvc_query_ctrl(dev, UVC_GET_CUR, 0, पूर्णांकfnum,
			       UVC_VC_REQUEST_ERROR_CODE_CONTROL, data, 1,
			       UVC_CTRL_CONTROL_TIMEOUT);

	error = *(u8 *)data;
	*(u8 *)data = पंचांगp;

	अगर (ret != 1)
		वापस ret < 0 ? ret : -EPIPE;

	uvc_dbg(dev, CONTROL, "Control error %u\n", error);

	चयन (error) अणु
	हाल 0:
		/* Cannot happen - we received a STALL */
		वापस -EPIPE;
	हाल 1: /* Not पढ़ोy */
		वापस -EBUSY;
	हाल 2: /* Wrong state */
		वापस -EILSEQ;
	हाल 3: /* Power */
		वापस -EREMOTE;
	हाल 4: /* Out of range */
		वापस -दुस्फल;
	हाल 5: /* Invalid unit */
	हाल 6: /* Invalid control */
	हाल 7: /* Invalid Request */
	हाल 8: /* Invalid value within range */
		वापस -EINVAL;
	शेष: /* reserved or unknown */
		अवरोध;
	पूर्ण

	वापस -EPIPE;
पूर्ण

अटल व्योम uvc_fixup_video_ctrl(काष्ठा uvc_streaming *stream,
	काष्ठा uvc_streaming_control *ctrl)
अणु
	काष्ठा uvc_क्रमmat *क्रमmat = शून्य;
	काष्ठा uvc_frame *frame = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < stream->nक्रमmats; ++i) अणु
		अगर (stream->क्रमmat[i].index == ctrl->bFormatIndex) अणु
			क्रमmat = &stream->क्रमmat[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (क्रमmat == शून्य)
		वापस;

	क्रम (i = 0; i < क्रमmat->nframes; ++i) अणु
		अगर (क्रमmat->frame[i].bFrameIndex == ctrl->bFrameIndex) अणु
			frame = &क्रमmat->frame[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (frame == शून्य)
		वापस;

	अगर (!(क्रमmat->flags & UVC_FMT_FLAG_COMPRESSED) ||
	     (ctrl->dwMaxVideoFrameSize == 0 &&
	      stream->dev->uvc_version < 0x0110))
		ctrl->dwMaxVideoFrameSize =
			frame->dwMaxVideoFrameBufferSize;

	/* The "TOSHIBA Web Camera - 5M" Chicony device (04f2:b50b) seems to
	 * compute the bandwidth on 16 bits and erroneously sign-extend it to
	 * 32 bits, resulting in a huge bandwidth value. Detect and fix that
	 * condition by setting the 16 MSBs to 0 when they're all equal to 1.
	 */
	अगर ((ctrl->dwMaxPayloadTransferSize & 0xffff0000) == 0xffff0000)
		ctrl->dwMaxPayloadTransferSize &= ~0xffff0000;

	अगर (!(क्रमmat->flags & UVC_FMT_FLAG_COMPRESSED) &&
	    stream->dev->quirks & UVC_QUIRK_FIX_BANDWIDTH &&
	    stream->पूर्णांकf->num_altsetting > 1) अणु
		u32 पूर्णांकerval;
		u32 bandwidth;

		पूर्णांकerval = (ctrl->dwFrameInterval > 100000)
			 ? ctrl->dwFrameInterval
			 : frame->dwFrameInterval[0];

		/* Compute a bandwidth estimation by multiplying the frame
		 * size by the number of video frames per second, भागide the
		 * result by the number of USB frames (or micro-frames क्रम
		 * high-speed devices) per second and add the UVC header size
		 * (assumed to be 12 bytes दीर्घ).
		 */
		bandwidth = frame->wWidth * frame->wHeight / 8 * क्रमmat->bpp;
		bandwidth *= 10000000 / पूर्णांकerval + 1;
		bandwidth /= 1000;
		अगर (stream->dev->udev->speed == USB_SPEED_HIGH)
			bandwidth /= 8;
		bandwidth += 12;

		/* The bandwidth estimate is too low क्रम many cameras. Don't use
		 * maximum packet sizes lower than 1024 bytes to try and work
		 * around the problem. According to measurements करोne on two
		 * dअगरferent camera models, the value is high enough to get most
		 * resolutions working जबतक not preventing two simultaneous
		 * VGA streams at 15 fps.
		 */
		bandwidth = max_t(u32, bandwidth, 1024);

		ctrl->dwMaxPayloadTransferSize = bandwidth;
	पूर्ण
पूर्ण

अटल माप_प्रकार uvc_video_ctrl_size(काष्ठा uvc_streaming *stream)
अणु
	/*
	 * Return the size of the video probe and commit controls, which depends
	 * on the protocol version.
	 */
	अगर (stream->dev->uvc_version < 0x0110)
		वापस 26;
	अन्यथा अगर (stream->dev->uvc_version < 0x0150)
		वापस 34;
	अन्यथा
		वापस 48;
पूर्ण

अटल पूर्णांक uvc_get_video_ctrl(काष्ठा uvc_streaming *stream,
	काष्ठा uvc_streaming_control *ctrl, पूर्णांक probe, u8 query)
अणु
	u16 size = uvc_video_ctrl_size(stream);
	u8 *data;
	पूर्णांक ret;

	अगर ((stream->dev->quirks & UVC_QUIRK_PROBE_DEF) &&
			query == UVC_GET_DEF)
		वापस -EIO;

	data = kदो_स्मृति(size, GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	ret = __uvc_query_ctrl(stream->dev, query, 0, stream->पूर्णांकfnum,
		probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
		size, uvc_समयout_param);

	अगर ((query == UVC_GET_MIN || query == UVC_GET_MAX) && ret == 2) अणु
		/* Some cameras, mostly based on Bison Electronics chipsets,
		 * answer a GET_MIN or GET_MAX request with the wCompQuality
		 * field only.
		 */
		uvc_warn_once(stream->dev, UVC_WARN_MINMAX, "UVC non "
			"compliance - GET_MIN/MAX(PROBE) incorrectly "
			"supported. Enabling workaround.\n");
		स_रखो(ctrl, 0, माप(*ctrl));
		ctrl->wCompQuality = le16_to_cpup((__le16 *)data);
		ret = 0;
		जाओ out;
	पूर्ण अन्यथा अगर (query == UVC_GET_DEF && probe == 1 && ret != size) अणु
		/* Many cameras करोn't support the GET_DEF request on their
		 * video probe control. Warn once and वापस, the caller will
		 * fall back to GET_CUR.
		 */
		uvc_warn_once(stream->dev, UVC_WARN_PROBE_DEF, "UVC non "
			"compliance - GET_DEF(PROBE) not supported. "
			"Enabling workaround.\n");
		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा अगर (ret != size) अणु
		dev_err(&stream->पूर्णांकf->dev,
			"Failed to query (%u) UVC %s control : %d (exp. %u).\n",
			query, probe ? "probe" : "commit", ret, size);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ctrl->bmHपूर्णांक = le16_to_cpup((__le16 *)&data[0]);
	ctrl->bFormatIndex = data[2];
	ctrl->bFrameIndex = data[3];
	ctrl->dwFrameInterval = le32_to_cpup((__le32 *)&data[4]);
	ctrl->wKeyFrameRate = le16_to_cpup((__le16 *)&data[8]);
	ctrl->wPFrameRate = le16_to_cpup((__le16 *)&data[10]);
	ctrl->wCompQuality = le16_to_cpup((__le16 *)&data[12]);
	ctrl->wCompWinकरोwSize = le16_to_cpup((__le16 *)&data[14]);
	ctrl->wDelay = le16_to_cpup((__le16 *)&data[16]);
	ctrl->dwMaxVideoFrameSize = get_unaligned_le32(&data[18]);
	ctrl->dwMaxPayloadTransferSize = get_unaligned_le32(&data[22]);

	अगर (size >= 34) अणु
		ctrl->dwClockFrequency = get_unaligned_le32(&data[26]);
		ctrl->bmFramingInfo = data[30];
		ctrl->bPreferedVersion = data[31];
		ctrl->bMinVersion = data[32];
		ctrl->bMaxVersion = data[33];
	पूर्ण अन्यथा अणु
		ctrl->dwClockFrequency = stream->dev->घड़ी_frequency;
		ctrl->bmFramingInfo = 0;
		ctrl->bPreferedVersion = 0;
		ctrl->bMinVersion = 0;
		ctrl->bMaxVersion = 0;
	पूर्ण

	/* Some broken devices वापस null or wrong dwMaxVideoFrameSize and
	 * dwMaxPayloadTransferSize fields. Try to get the value from the
	 * क्रमmat and frame descriptors.
	 */
	uvc_fixup_video_ctrl(stream, ctrl);
	ret = 0;

out:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक uvc_set_video_ctrl(काष्ठा uvc_streaming *stream,
	काष्ठा uvc_streaming_control *ctrl, पूर्णांक probe)
अणु
	u16 size = uvc_video_ctrl_size(stream);
	u8 *data;
	पूर्णांक ret;

	data = kzalloc(size, GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	*(__le16 *)&data[0] = cpu_to_le16(ctrl->bmHपूर्णांक);
	data[2] = ctrl->bFormatIndex;
	data[3] = ctrl->bFrameIndex;
	*(__le32 *)&data[4] = cpu_to_le32(ctrl->dwFrameInterval);
	*(__le16 *)&data[8] = cpu_to_le16(ctrl->wKeyFrameRate);
	*(__le16 *)&data[10] = cpu_to_le16(ctrl->wPFrameRate);
	*(__le16 *)&data[12] = cpu_to_le16(ctrl->wCompQuality);
	*(__le16 *)&data[14] = cpu_to_le16(ctrl->wCompWinकरोwSize);
	*(__le16 *)&data[16] = cpu_to_le16(ctrl->wDelay);
	put_unaligned_le32(ctrl->dwMaxVideoFrameSize, &data[18]);
	put_unaligned_le32(ctrl->dwMaxPayloadTransferSize, &data[22]);

	अगर (size >= 34) अणु
		put_unaligned_le32(ctrl->dwClockFrequency, &data[26]);
		data[30] = ctrl->bmFramingInfo;
		data[31] = ctrl->bPreferedVersion;
		data[32] = ctrl->bMinVersion;
		data[33] = ctrl->bMaxVersion;
	पूर्ण

	ret = __uvc_query_ctrl(stream->dev, UVC_SET_CUR, 0, stream->पूर्णांकfnum,
		probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
		size, uvc_समयout_param);
	अगर (ret != size) अणु
		dev_err(&stream->पूर्णांकf->dev,
			"Failed to set UVC %s control : %d (exp. %u).\n",
			probe ? "probe" : "commit", ret, size);
		ret = -EIO;
	पूर्ण

	kमुक्त(data);
	वापस ret;
पूर्ण

पूर्णांक uvc_probe_video(काष्ठा uvc_streaming *stream,
	काष्ठा uvc_streaming_control *probe)
अणु
	काष्ठा uvc_streaming_control probe_min, probe_max;
	u16 bandwidth;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Perक्रमm probing. The device should adjust the requested values
	 * according to its capabilities. However, some devices, namely the
	 * first generation UVC Logitech webcams, करोn't implement the Video
	 * Probe control properly, and just वापस the needed bandwidth. For
	 * that reason, अगर the needed bandwidth exceeds the maximum available
	 * bandwidth, try to lower the quality.
	 */
	ret = uvc_set_video_ctrl(stream, probe, 1);
	अगर (ret < 0)
		जाओ करोne;

	/* Get the minimum and maximum values क्रम compression settings. */
	अगर (!(stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX)) अणु
		ret = uvc_get_video_ctrl(stream, &probe_min, 1, UVC_GET_MIN);
		अगर (ret < 0)
			जाओ करोne;
		ret = uvc_get_video_ctrl(stream, &probe_max, 1, UVC_GET_MAX);
		अगर (ret < 0)
			जाओ करोne;

		probe->wCompQuality = probe_max.wCompQuality;
	पूर्ण

	क्रम (i = 0; i < 2; ++i) अणु
		ret = uvc_set_video_ctrl(stream, probe, 1);
		अगर (ret < 0)
			जाओ करोne;
		ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
		अगर (ret < 0)
			जाओ करोne;

		अगर (stream->पूर्णांकf->num_altsetting == 1)
			अवरोध;

		bandwidth = probe->dwMaxPayloadTransferSize;
		अगर (bandwidth <= stream->maxpsize)
			अवरोध;

		अगर (stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX) अणु
			ret = -ENOSPC;
			जाओ करोne;
		पूर्ण

		/* TODO: negotiate compression parameters */
		probe->wKeyFrameRate = probe_min.wKeyFrameRate;
		probe->wPFrameRate = probe_min.wPFrameRate;
		probe->wCompQuality = probe_max.wCompQuality;
		probe->wCompWinकरोwSize = probe_min.wCompWinकरोwSize;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक uvc_commit_video(काष्ठा uvc_streaming *stream,
			    काष्ठा uvc_streaming_control *probe)
अणु
	वापस uvc_set_video_ctrl(stream, probe, 0);
पूर्ण

/* -----------------------------------------------------------------------------
 * Clocks and बारtamps
 */

अटल अंतरभूत kसमय_प्रकार uvc_video_get_समय(व्योम)
अणु
	अगर (uvc_घड़ी_param == CLOCK_MONOTONIC)
		वापस kसमय_get();
	अन्यथा
		वापस kसमय_get_real();
पूर्ण

अटल व्योम
uvc_video_घड़ी_decode(काष्ठा uvc_streaming *stream, काष्ठा uvc_buffer *buf,
		       स्थिर u8 *data, पूर्णांक len)
अणु
	काष्ठा uvc_घड़ी_sample *sample;
	अचिन्हित पूर्णांक header_size;
	bool has_pts = false;
	bool has_scr = false;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार समय;
	u16 host_sof;
	u16 dev_sof;

	चयन (data[1] & (UVC_STREAM_PTS | UVC_STREAM_SCR)) अणु
	हाल UVC_STREAM_PTS | UVC_STREAM_SCR:
		header_size = 12;
		has_pts = true;
		has_scr = true;
		अवरोध;
	हाल UVC_STREAM_PTS:
		header_size = 6;
		has_pts = true;
		अवरोध;
	हाल UVC_STREAM_SCR:
		header_size = 8;
		has_scr = true;
		अवरोध;
	शेष:
		header_size = 2;
		अवरोध;
	पूर्ण

	/* Check क्रम invalid headers. */
	अगर (len < header_size)
		वापस;

	/* Extract the बारtamps:
	 *
	 * - store the frame PTS in the buffer काष्ठाure
	 * - अगर the SCR field is present, retrieve the host SOF counter and
	 *   kernel बारtamps and store them with the SCR STC and SOF fields
	 *   in the ring buffer
	 */
	अगर (has_pts && buf != शून्य)
		buf->pts = get_unaligned_le32(&data[2]);

	अगर (!has_scr)
		वापस;

	/* To limit the amount of data, drop SCRs with an SOF identical to the
	 * previous one.
	 */
	dev_sof = get_unaligned_le16(&data[header_size - 2]);
	अगर (dev_sof == stream->घड़ी.last_sof)
		वापस;

	stream->घड़ी.last_sof = dev_sof;

	host_sof = usb_get_current_frame_number(stream->dev->udev);
	समय = uvc_video_get_समय();

	/* The UVC specअगरication allows device implementations that can't obtain
	 * the USB frame number to keep their own frame counters as दीर्घ as they
	 * match the size and frequency of the frame number associated with USB
	 * SOF tokens. The SOF values sent by such devices dअगरfer from the USB
	 * SOF tokens by a fixed offset that needs to be estimated and accounted
	 * क्रम to make बारtamp recovery as accurate as possible.
	 *
	 * The offset is estimated the first समय a device SOF value is received
	 * as the dअगरference between the host and device SOF values. As the two
	 * SOF values can dअगरfer slightly due to transmission delays, consider
	 * that the offset is null अगर the dअगरference is not higher than 10 ms
	 * (negative dअगरferences can not happen and are thus considered as an
	 * offset). The video commit control wDelay field should be used to
	 * compute a dynamic threshold instead of using a fixed 10 ms value, but
	 * devices करोn't report reliable wDelay values.
	 *
	 * See uvc_video_घड़ी_host_sof() क्रम an explanation regarding why only
	 * the 8 LSBs of the delta are kept.
	 */
	अगर (stream->घड़ी.sof_offset == (u16)-1) अणु
		u16 delta_sof = (host_sof - dev_sof) & 255;
		अगर (delta_sof >= 10)
			stream->घड़ी.sof_offset = delta_sof;
		अन्यथा
			stream->घड़ी.sof_offset = 0;
	पूर्ण

	dev_sof = (dev_sof + stream->घड़ी.sof_offset) & 2047;

	spin_lock_irqsave(&stream->घड़ी.lock, flags);

	sample = &stream->घड़ी.samples[stream->घड़ी.head];
	sample->dev_stc = get_unaligned_le32(&data[header_size - 6]);
	sample->dev_sof = dev_sof;
	sample->host_sof = host_sof;
	sample->host_समय = समय;

	/* Update the sliding winकरोw head and count. */
	stream->घड़ी.head = (stream->घड़ी.head + 1) % stream->घड़ी.size;

	अगर (stream->घड़ी.count < stream->घड़ी.size)
		stream->घड़ी.count++;

	spin_unlock_irqrestore(&stream->घड़ी.lock, flags);
पूर्ण

अटल व्योम uvc_video_घड़ी_reset(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा uvc_घड़ी *घड़ी = &stream->घड़ी;

	घड़ी->head = 0;
	घड़ी->count = 0;
	घड़ी->last_sof = -1;
	घड़ी->sof_offset = -1;
पूर्ण

अटल पूर्णांक uvc_video_घड़ी_init(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा uvc_घड़ी *घड़ी = &stream->घड़ी;

	spin_lock_init(&घड़ी->lock);
	घड़ी->size = 32;

	घड़ी->samples = kदो_स्मृति_array(घड़ी->size, माप(*घड़ी->samples),
				       GFP_KERNEL);
	अगर (घड़ी->samples == शून्य)
		वापस -ENOMEM;

	uvc_video_घड़ी_reset(stream);

	वापस 0;
पूर्ण

अटल व्योम uvc_video_घड़ी_cleanup(काष्ठा uvc_streaming *stream)
अणु
	kमुक्त(stream->घड़ी.samples);
	stream->घड़ी.samples = शून्य;
पूर्ण

/*
 * uvc_video_घड़ी_host_sof - Return the host SOF value क्रम a घड़ी sample
 *
 * Host SOF counters reported by usb_get_current_frame_number() usually करोn't
 * cover the whole 11-bits SOF range (0-2047) but are limited to the HCI frame
 * schedule winकरोw. They can be limited to 8, 9 or 10 bits depending on the host
 * controller and its configuration.
 *
 * We thus need to recover the SOF value corresponding to the host frame number.
 * As the device and host frame numbers are sampled in a लघु पूर्णांकerval, the
 * dअगरference between their values should be equal to a small delta plus an
 * पूर्णांकeger multiple of 256 caused by the host frame number limited precision.
 *
 * To obtain the recovered host SOF value, compute the small delta by masking
 * the high bits of the host frame counter and device SOF dअगरference and add it
 * to the device SOF value.
 */
अटल u16 uvc_video_घड़ी_host_sof(स्थिर काष्ठा uvc_घड़ी_sample *sample)
अणु
	/* The delta value can be negative. */
	s8 delta_sof;

	delta_sof = (sample->host_sof - sample->dev_sof) & 255;

	वापस (sample->dev_sof + delta_sof) & 2047;
पूर्ण

/*
 * uvc_video_घड़ी_update - Update the buffer बारtamp
 *
 * This function converts the buffer PTS बारtamp to the host घड़ी करोमुख्य by
 * going through the USB SOF घड़ी करोमुख्य and stores the result in the V4L2
 * buffer बारtamp field.
 *
 * The relationship between the device घड़ी and the host घड़ी isn't known.
 * However, the device and the host share the common USB SOF घड़ी which can be
 * used to recover that relationship.
 *
 * The relationship between the device घड़ी and the USB SOF घड़ी is considered
 * to be linear over the घड़ी samples sliding winकरोw and is given by
 *
 * SOF = m * PTS + p
 *
 * Several methods to compute the slope (m) and पूर्णांकercept (p) can be used. As
 * the घड़ी drअगरt should be small compared to the sliding winकरोw size, we
 * assume that the line that goes through the poपूर्णांकs at both ends of the winकरोw
 * is a good approximation. Naming those poपूर्णांकs P1 and P2, we get
 *
 * SOF = (SOF2 - SOF1) / (STC2 - STC1) * PTS
 *     + (SOF1 * STC2 - SOF2 * STC1) / (STC2 - STC1)
 *
 * or
 *
 * SOF = ((SOF2 - SOF1) * PTS + SOF1 * STC2 - SOF2 * STC1) / (STC2 - STC1)   (1)
 *
 * to aव्योम losing precision in the भागision. Similarly, the host बारtamp is
 * computed with
 *
 * TS = ((TS2 - TS1) * SOF + TS1 * SOF2 - TS2 * SOF1) / (SOF2 - SOF1)	     (2)
 *
 * SOF values are coded on 11 bits by USB. We extend their precision with 16
 * decimal bits, leading to a 11.16 coding.
 *
 * TODO: To aव्योम surprises with device घड़ी values, PTS/STC बारtamps should
 * be normalized using the nominal device घड़ी frequency reported through the
 * UVC descriptors.
 *
 * Both the PTS/STC and SOF counters roll over, after a fixed but device
 * specअगरic amount of समय क्रम PTS/STC and after 2048ms क्रम SOF. As दीर्घ as the
 * sliding winकरोw size is smaller than the rollover period, dअगरferences computed
 * on अचिन्हित पूर्णांकegers will produce the correct result. However, the p term in
 * the linear relations will be miscomputed.
 *
 * To fix the issue, we subtract a स्थिरant from the PTS and STC values to bring
 * PTS to half the 32 bit STC range. The sliding winकरोw STC values then fit पूर्णांकo
 * the 32 bit range without any rollover.
 *
 * Similarly, we add 2048 to the device SOF values to make sure that the SOF
 * computed by (1) will never be smaller than 0. This offset is then compensated
 * by adding 2048 to the SOF values used in (2). However, this करोesn't prevent
 * rollovers between (1) and (2): the SOF value computed by (1) can be slightly
 * lower than 4096, and the host SOF counters can have rolled over to 2048. This
 * हाल is handled by subtracting 2048 from the SOF value अगर it exceeds the host
 * SOF value at the end of the sliding winकरोw.
 *
 * Finally we subtract a स्थिरant from the host बारtamps to bring the first
 * बारtamp of the sliding winकरोw to 1s.
 */
व्योम uvc_video_घड़ी_update(काष्ठा uvc_streaming *stream,
			    काष्ठा vb2_v4l2_buffer *vbuf,
			    काष्ठा uvc_buffer *buf)
अणु
	काष्ठा uvc_घड़ी *घड़ी = &stream->घड़ी;
	काष्ठा uvc_घड़ी_sample *first;
	काष्ठा uvc_घड़ी_sample *last;
	अचिन्हित दीर्घ flags;
	u64 बारtamp;
	u32 delta_stc;
	u32 y1, y2;
	u32 x1, x2;
	u32 mean;
	u32 sof;
	u64 y;

	अगर (!uvc_hw_बारtamps_param)
		वापस;

	/*
	 * We will get called from __vb2_queue_cancel() अगर there are buffers
	 * करोne but not dequeued by the user, but the sample array has alपढ़ोy
	 * been released at that समय. Just bail out in that हाल.
	 */
	अगर (!घड़ी->samples)
		वापस;

	spin_lock_irqsave(&घड़ी->lock, flags);

	अगर (घड़ी->count < घड़ी->size)
		जाओ करोne;

	first = &घड़ी->samples[घड़ी->head];
	last = &घड़ी->samples[(घड़ी->head - 1) % घड़ी->size];

	/* First step, PTS to SOF conversion. */
	delta_stc = buf->pts - (1UL << 31);
	x1 = first->dev_stc - delta_stc;
	x2 = last->dev_stc - delta_stc;
	अगर (x1 == x2)
		जाओ करोne;

	y1 = (first->dev_sof + 2048) << 16;
	y2 = (last->dev_sof + 2048) << 16;
	अगर (y2 < y1)
		y2 += 2048 << 16;

	y = (u64)(y2 - y1) * (1ULL << 31) + (u64)y1 * (u64)x2
	  - (u64)y2 * (u64)x1;
	y = भाग_u64(y, x2 - x1);

	sof = y;

	uvc_dbg(stream->dev, CLOCK,
		"%s: PTS %u y %llu.%06llu SOF %u.%06llu (x1 %u x2 %u y1 %u y2 %u SOF offset %u)\n",
		stream->dev->name, buf->pts,
		y >> 16, भाग_u64((y & 0xffff) * 1000000, 65536),
		sof >> 16, भाग_u64(((u64)sof & 0xffff) * 1000000LLU, 65536),
		x1, x2, y1, y2, घड़ी->sof_offset);

	/* Second step, SOF to host घड़ी conversion. */
	x1 = (uvc_video_घड़ी_host_sof(first) + 2048) << 16;
	x2 = (uvc_video_घड़ी_host_sof(last) + 2048) << 16;
	अगर (x2 < x1)
		x2 += 2048 << 16;
	अगर (x1 == x2)
		जाओ करोne;

	y1 = NSEC_PER_SEC;
	y2 = (u32)kसमय_प्रकारo_ns(kसमय_sub(last->host_समय, first->host_समय)) + y1;

	/* Interpolated and host SOF बारtamps can wrap around at slightly
	 * dअगरferent बार. Handle this by adding or removing 2048 to or from
	 * the computed SOF value to keep it बंद to the SOF samples mean
	 * value.
	 */
	mean = (x1 + x2) / 2;
	अगर (mean - (1024 << 16) > sof)
		sof += 2048 << 16;
	अन्यथा अगर (sof > mean + (1024 << 16))
		sof -= 2048 << 16;

	y = (u64)(y2 - y1) * (u64)sof + (u64)y1 * (u64)x2
	  - (u64)y2 * (u64)x1;
	y = भाग_u64(y, x2 - x1);

	बारtamp = kसमय_प्रकारo_ns(first->host_समय) + y - y1;

	uvc_dbg(stream->dev, CLOCK,
		"%s: SOF %u.%06llu y %llu ts %llu buf ts %llu (x1 %u/%u/%u x2 %u/%u/%u y1 %u y2 %u)\n",
		stream->dev->name,
		sof >> 16, भाग_u64(((u64)sof & 0xffff) * 1000000LLU, 65536),
		y, बारtamp, vbuf->vb2_buf.बारtamp,
		x1, first->host_sof, first->dev_sof,
		x2, last->host_sof, last->dev_sof, y1, y2);

	/* Update the V4L2 buffer. */
	vbuf->vb2_buf.बारtamp = बारtamp;

करोne:
	spin_unlock_irqrestore(&घड़ी->lock, flags);
पूर्ण

/* ------------------------------------------------------------------------
 * Stream statistics
 */

अटल व्योम uvc_video_stats_decode(काष्ठा uvc_streaming *stream,
		स्थिर u8 *data, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक header_size;
	bool has_pts = false;
	bool has_scr = false;
	u16 scr_sof;
	u32 scr_stc;
	u32 pts;

	अगर (stream->stats.stream.nb_frames == 0 &&
	    stream->stats.frame.nb_packets == 0)
		stream->stats.stream.start_ts = kसमय_get();

	चयन (data[1] & (UVC_STREAM_PTS | UVC_STREAM_SCR)) अणु
	हाल UVC_STREAM_PTS | UVC_STREAM_SCR:
		header_size = 12;
		has_pts = true;
		has_scr = true;
		अवरोध;
	हाल UVC_STREAM_PTS:
		header_size = 6;
		has_pts = true;
		अवरोध;
	हाल UVC_STREAM_SCR:
		header_size = 8;
		has_scr = true;
		अवरोध;
	शेष:
		header_size = 2;
		अवरोध;
	पूर्ण

	/* Check क्रम invalid headers. */
	अगर (len < header_size || data[0] < header_size) अणु
		stream->stats.frame.nb_invalid++;
		वापस;
	पूर्ण

	/* Extract the बारtamps. */
	अगर (has_pts)
		pts = get_unaligned_le32(&data[2]);

	अगर (has_scr) अणु
		scr_stc = get_unaligned_le32(&data[header_size - 6]);
		scr_sof = get_unaligned_le16(&data[header_size - 2]);
	पूर्ण

	/* Is PTS स्थिरant through the whole frame ? */
	अगर (has_pts && stream->stats.frame.nb_pts) अणु
		अगर (stream->stats.frame.pts != pts) अणु
			stream->stats.frame.nb_pts_dअगरfs++;
			stream->stats.frame.last_pts_dअगरf =
				stream->stats.frame.nb_packets;
		पूर्ण
	पूर्ण

	अगर (has_pts) अणु
		stream->stats.frame.nb_pts++;
		stream->stats.frame.pts = pts;
	पूर्ण

	/* Do all frames have a PTS in their first non-empty packet, or beक्रमe
	 * their first empty packet ?
	 */
	अगर (stream->stats.frame.size == 0) अणु
		अगर (len > header_size)
			stream->stats.frame.has_initial_pts = has_pts;
		अगर (len == header_size && has_pts)
			stream->stats.frame.has_early_pts = true;
	पूर्ण

	/* Do the SCR.STC and SCR.SOF fields vary through the frame ? */
	अगर (has_scr && stream->stats.frame.nb_scr) अणु
		अगर (stream->stats.frame.scr_stc != scr_stc)
			stream->stats.frame.nb_scr_dअगरfs++;
	पूर्ण

	अगर (has_scr) अणु
		/* Expand the SOF counter to 32 bits and store its value. */
		अगर (stream->stats.stream.nb_frames > 0 ||
		    stream->stats.frame.nb_scr > 0)
			stream->stats.stream.scr_sof_count +=
				(scr_sof - stream->stats.stream.scr_sof) % 2048;
		stream->stats.stream.scr_sof = scr_sof;

		stream->stats.frame.nb_scr++;
		stream->stats.frame.scr_stc = scr_stc;
		stream->stats.frame.scr_sof = scr_sof;

		अगर (scr_sof < stream->stats.stream.min_sof)
			stream->stats.stream.min_sof = scr_sof;
		अगर (scr_sof > stream->stats.stream.max_sof)
			stream->stats.stream.max_sof = scr_sof;
	पूर्ण

	/* Record the first non-empty packet number. */
	अगर (stream->stats.frame.size == 0 && len > header_size)
		stream->stats.frame.first_data = stream->stats.frame.nb_packets;

	/* Update the frame size. */
	stream->stats.frame.size += len - header_size;

	/* Update the packets counters. */
	stream->stats.frame.nb_packets++;
	अगर (len <= header_size)
		stream->stats.frame.nb_empty++;

	अगर (data[1] & UVC_STREAM_ERR)
		stream->stats.frame.nb_errors++;
पूर्ण

अटल व्योम uvc_video_stats_update(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा uvc_stats_frame *frame = &stream->stats.frame;

	uvc_dbg(stream->dev, STATS,
		"frame %u stats: %u/%u/%u packets, %u/%u/%u pts (%searly %sinitial), %u/%u scr, last pts/stc/sof %u/%u/%u\n",
		stream->sequence, frame->first_data,
		frame->nb_packets - frame->nb_empty, frame->nb_packets,
		frame->nb_pts_dअगरfs, frame->last_pts_dअगरf, frame->nb_pts,
		frame->has_early_pts ? "" : "!",
		frame->has_initial_pts ? "" : "!",
		frame->nb_scr_dअगरfs, frame->nb_scr,
		frame->pts, frame->scr_stc, frame->scr_sof);

	stream->stats.stream.nb_frames++;
	stream->stats.stream.nb_packets += stream->stats.frame.nb_packets;
	stream->stats.stream.nb_empty += stream->stats.frame.nb_empty;
	stream->stats.stream.nb_errors += stream->stats.frame.nb_errors;
	stream->stats.stream.nb_invalid += stream->stats.frame.nb_invalid;

	अगर (frame->has_early_pts)
		stream->stats.stream.nb_pts_early++;
	अगर (frame->has_initial_pts)
		stream->stats.stream.nb_pts_initial++;
	अगर (frame->last_pts_dअगरf <= frame->first_data)
		stream->stats.stream.nb_pts_स्थिरant++;
	अगर (frame->nb_scr >= frame->nb_packets - frame->nb_empty)
		stream->stats.stream.nb_scr_count_ok++;
	अगर (frame->nb_scr_dअगरfs + 1 == frame->nb_scr)
		stream->stats.stream.nb_scr_dअगरfs_ok++;

	स_रखो(&stream->stats.frame, 0, माप(stream->stats.frame));
पूर्ण

माप_प्रकार uvc_video_stats_dump(काष्ठा uvc_streaming *stream, अक्षर *buf,
			    माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक scr_sof_freq;
	अचिन्हित पूर्णांक duration;
	माप_प्रकार count = 0;

	/* Compute the SCR.SOF frequency estimate. At the nominal 1kHz SOF
	 * frequency this will not overflow beक्रमe more than 1h.
	 */
	duration = kसमय_ms_delta(stream->stats.stream.stop_ts,
				  stream->stats.stream.start_ts);
	अगर (duration != 0)
		scr_sof_freq = stream->stats.stream.scr_sof_count * 1000
			     / duration;
	अन्यथा
		scr_sof_freq = 0;

	count += scnम_लिखो(buf + count, size - count,
			   "frames:  %u\npackets: %u\nempty:   %u\n"
			   "errors:  %u\ninvalid: %u\n",
			   stream->stats.stream.nb_frames,
			   stream->stats.stream.nb_packets,
			   stream->stats.stream.nb_empty,
			   stream->stats.stream.nb_errors,
			   stream->stats.stream.nb_invalid);
	count += scnम_लिखो(buf + count, size - count,
			   "pts: %u early, %u initial, %u ok\n",
			   stream->stats.stream.nb_pts_early,
			   stream->stats.stream.nb_pts_initial,
			   stream->stats.stream.nb_pts_स्थिरant);
	count += scnम_लिखो(buf + count, size - count,
			   "scr: %u count ok, %u diff ok\n",
			   stream->stats.stream.nb_scr_count_ok,
			   stream->stats.stream.nb_scr_dअगरfs_ok);
	count += scnम_लिखो(buf + count, size - count,
			   "sof: %u <= sof <= %u, freq %u.%03u kHz\n",
			   stream->stats.stream.min_sof,
			   stream->stats.stream.max_sof,
			   scr_sof_freq / 1000, scr_sof_freq % 1000);

	वापस count;
पूर्ण

अटल व्योम uvc_video_stats_start(काष्ठा uvc_streaming *stream)
अणु
	स_रखो(&stream->stats, 0, माप(stream->stats));
	stream->stats.stream.min_sof = 2048;
पूर्ण

अटल व्योम uvc_video_stats_stop(काष्ठा uvc_streaming *stream)
अणु
	stream->stats.stream.stop_ts = kसमय_get();
पूर्ण

/* ------------------------------------------------------------------------
 * Video codecs
 */

/* Video payload decoding is handled by uvc_video_decode_start(),
 * uvc_video_decode_data() and uvc_video_decode_end().
 *
 * uvc_video_decode_start is called with URB data at the start of a bulk or
 * isochronous payload. It processes header data and वापसs the header size
 * in bytes अगर successful. If an error occurs, it वापसs a negative error
 * code. The following error codes have special meanings.
 *
 * - EAGAIN inक्रमms the caller that the current video buffer should be marked
 *   as करोne, and that the function should be called again with the same data
 *   and a new video buffer. This is used when end of frame conditions can be
 *   reliably detected at the beginning of the next frame only.
 *
 * If an error other than -EAGAIN is वापसed, the caller will drop the current
 * payload. No call to uvc_video_decode_data and uvc_video_decode_end will be
 * made until the next payload. -ENODATA can be used to drop the current
 * payload अगर no other error code is appropriate.
 *
 * uvc_video_decode_data is called क्रम every URB with URB data. It copies the
 * data to the video buffer.
 *
 * uvc_video_decode_end is called with header data at the end of a bulk or
 * isochronous payload. It perक्रमms any additional header data processing and
 * वापसs 0 or a negative error code अगर an error occurred. As header data have
 * alपढ़ोy been processed by uvc_video_decode_start, this functions isn't
 * required to perक्रमm sanity checks a second समय.
 *
 * For isochronous transfers where a payload is always transferred in a single
 * URB, the three functions will be called in a row.
 *
 * To let the decoder process header data and update its पूर्णांकernal state even
 * when no video buffer is available, uvc_video_decode_start must be prepared
 * to be called with a शून्य buf parameter. uvc_video_decode_data and
 * uvc_video_decode_end will never be called with a शून्य buffer.
 */
अटल पूर्णांक uvc_video_decode_start(काष्ठा uvc_streaming *stream,
		काष्ठा uvc_buffer *buf, स्थिर u8 *data, पूर्णांक len)
अणु
	u8 fid;

	/* Sanity checks:
	 * - packet must be at least 2 bytes दीर्घ
	 * - bHeaderLength value must be at least 2 bytes (see above)
	 * - bHeaderLength value can't be larger than the packet size.
	 */
	अगर (len < 2 || data[0] < 2 || data[0] > len) अणु
		stream->stats.frame.nb_invalid++;
		वापस -EINVAL;
	पूर्ण

	fid = data[1] & UVC_STREAM_FID;

	/* Increase the sequence number regardless of any buffer states, so
	 * that discontinuous sequence numbers always indicate lost frames.
	 */
	अगर (stream->last_fid != fid) अणु
		stream->sequence++;
		अगर (stream->sequence)
			uvc_video_stats_update(stream);
	पूर्ण

	uvc_video_घड़ी_decode(stream, buf, data, len);
	uvc_video_stats_decode(stream, data, len);

	/* Store the payload FID bit and वापस immediately when the buffer is
	 * शून्य.
	 */
	अगर (buf == शून्य) अणु
		stream->last_fid = fid;
		वापस -ENODATA;
	पूर्ण

	/* Mark the buffer as bad अगर the error bit is set. */
	अगर (data[1] & UVC_STREAM_ERR) अणु
		uvc_dbg(stream->dev, FRAME,
			"Marking buffer as bad (error bit set)\n");
		buf->error = 1;
	पूर्ण

	/* Synchronize to the input stream by रुकोing क्रम the FID bit to be
	 * toggled when the the buffer state is not UVC_BUF_STATE_ACTIVE.
	 * stream->last_fid is initialized to -1, so the first isochronous
	 * frame will always be in sync.
	 *
	 * If the device करोesn't toggle the FID bit, invert stream->last_fid
	 * when the खातापूर्ण bit is set to क्रमce synchronisation on the next packet.
	 */
	अगर (buf->state != UVC_BUF_STATE_ACTIVE) अणु
		अगर (fid == stream->last_fid) अणु
			uvc_dbg(stream->dev, FRAME,
				"Dropping payload (out of sync)\n");
			अगर ((stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID) &&
			    (data[1] & UVC_STREAM_खातापूर्ण))
				stream->last_fid ^= UVC_STREAM_FID;
			वापस -ENODATA;
		पूर्ण

		buf->buf.field = V4L2_FIELD_NONE;
		buf->buf.sequence = stream->sequence;
		buf->buf.vb2_buf.बारtamp = kसमय_प्रकारo_ns(uvc_video_get_समय());

		/* TODO: Handle PTS and SCR. */
		buf->state = UVC_BUF_STATE_ACTIVE;
	पूर्ण

	/* Mark the buffer as करोne अगर we're at the beginning of a new frame.
	 * End of frame detection is better implemented by checking the खातापूर्ण
	 * bit (FID bit toggling is delayed by one frame compared to the खातापूर्ण
	 * bit), but some devices करोn't set the bit at end of frame (and the
	 * last payload can be lost anyway). We thus must check अगर the FID has
	 * been toggled.
	 *
	 * stream->last_fid is initialized to -1, so the first isochronous
	 * frame will never trigger an end of frame detection.
	 *
	 * Empty buffers (bytesused == 0) करोn't trigger end of frame detection
	 * as it करोesn't make sense to वापस an empty buffer. This also
	 * aव्योमs detecting end of frame conditions at FID toggling अगर the
	 * previous payload had the खातापूर्ण bit set.
	 */
	अगर (fid != stream->last_fid && buf->bytesused != 0) अणु
		uvc_dbg(stream->dev, FRAME,
			"Frame complete (FID bit toggled)\n");
		buf->state = UVC_BUF_STATE_READY;
		वापस -EAGAIN;
	पूर्ण

	stream->last_fid = fid;

	वापस data[0];
पूर्ण

अटल अंतरभूत क्रमागत dma_data_direction uvc_stream_dir(
				काष्ठा uvc_streaming *stream)
अणु
	अगर (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस DMA_FROM_DEVICE;
	अन्यथा
		वापस DMA_TO_DEVICE;
पूर्ण

अटल अंतरभूत काष्ठा device *uvc_stream_to_dmadev(काष्ठा uvc_streaming *stream)
अणु
	वापस bus_to_hcd(stream->dev->udev->bus)->self.sysdev;
पूर्ण

अटल पूर्णांक uvc_submit_urb(काष्ठा uvc_urb *uvc_urb, gfp_t mem_flags)
अणु
	/* Sync DMA. */
	dma_sync_sgtable_क्रम_device(uvc_stream_to_dmadev(uvc_urb->stream),
				    uvc_urb->sgt,
				    uvc_stream_dir(uvc_urb->stream));
	वापस usb_submit_urb(uvc_urb->urb, mem_flags);
पूर्ण

/*
 * uvc_video_decode_data_work: Asynchronous स_नकल processing
 *
 * Copy URB data to video buffers in process context, releasing buffer
 * references and requeuing the URB when करोne.
 */
अटल व्योम uvc_video_copy_data_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uvc_urb *uvc_urb = container_of(work, काष्ठा uvc_urb, work);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < uvc_urb->async_operations; i++) अणु
		काष्ठा uvc_copy_op *op = &uvc_urb->copy_operations[i];

		स_नकल(op->dst, op->src, op->len);

		/* Release reference taken on this buffer. */
		uvc_queue_buffer_release(op->buf);
	पूर्ण

	ret = uvc_submit_urb(uvc_urb, GFP_KERNEL);
	अगर (ret < 0)
		dev_err(&uvc_urb->stream->पूर्णांकf->dev,
			"Failed to resubmit video URB (%d).\n", ret);
पूर्ण

अटल व्योम uvc_video_decode_data(काष्ठा uvc_urb *uvc_urb,
		काष्ठा uvc_buffer *buf, स्थिर u8 *data, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक active_op = uvc_urb->async_operations;
	काष्ठा uvc_copy_op *op = &uvc_urb->copy_operations[active_op];
	अचिन्हित पूर्णांक maxlen;

	अगर (len <= 0)
		वापस;

	maxlen = buf->length - buf->bytesused;

	/* Take a buffer reference क्रम async work. */
	kref_get(&buf->ref);

	op->buf = buf;
	op->src = data;
	op->dst = buf->mem + buf->bytesused;
	op->len = min_t(अचिन्हित पूर्णांक, len, maxlen);

	buf->bytesused += op->len;

	/* Complete the current frame अगर the buffer size was exceeded. */
	अगर (len > maxlen) अणु
		uvc_dbg(uvc_urb->stream->dev, FRAME,
			"Frame complete (overflow)\n");
		buf->error = 1;
		buf->state = UVC_BUF_STATE_READY;
	पूर्ण

	uvc_urb->async_operations++;
पूर्ण

अटल व्योम uvc_video_decode_end(काष्ठा uvc_streaming *stream,
		काष्ठा uvc_buffer *buf, स्थिर u8 *data, पूर्णांक len)
अणु
	/* Mark the buffer as करोne अगर the खातापूर्ण marker is set. */
	अगर (data[1] & UVC_STREAM_खातापूर्ण && buf->bytesused != 0) अणु
		uvc_dbg(stream->dev, FRAME, "Frame complete (EOF found)\n");
		अगर (data[0] == len)
			uvc_dbg(stream->dev, FRAME, "EOF in empty payload\n");
		buf->state = UVC_BUF_STATE_READY;
		अगर (stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID)
			stream->last_fid ^= UVC_STREAM_FID;
	पूर्ण
पूर्ण

/* Video payload encoding is handled by uvc_video_encode_header() and
 * uvc_video_encode_data(). Only bulk transfers are currently supported.
 *
 * uvc_video_encode_header is called at the start of a payload. It adds header
 * data to the transfer buffer and वापसs the header size. As the only known
 * UVC output device transfers a whole frame in a single payload, the खातापूर्ण bit
 * is always set in the header.
 *
 * uvc_video_encode_data is called क्रम every URB and copies the data from the
 * video buffer to the transfer buffer.
 */
अटल पूर्णांक uvc_video_encode_header(काष्ठा uvc_streaming *stream,
		काष्ठा uvc_buffer *buf, u8 *data, पूर्णांक len)
अणु
	data[0] = 2;	/* Header length */
	data[1] = UVC_STREAM_EOH | UVC_STREAM_खातापूर्ण
		| (stream->last_fid & UVC_STREAM_FID);
	वापस 2;
पूर्ण

अटल पूर्णांक uvc_video_encode_data(काष्ठा uvc_streaming *stream,
		काष्ठा uvc_buffer *buf, u8 *data, पूर्णांक len)
अणु
	काष्ठा uvc_video_queue *queue = &stream->queue;
	अचिन्हित पूर्णांक nbytes;
	व्योम *mem;

	/* Copy video data to the URB buffer. */
	mem = buf->mem + queue->buf_used;
	nbytes = min((अचिन्हित पूर्णांक)len, buf->bytesused - queue->buf_used);
	nbytes = min(stream->bulk.max_payload_size - stream->bulk.payload_size,
			nbytes);
	स_नकल(data, mem, nbytes);

	queue->buf_used += nbytes;

	वापस nbytes;
पूर्ण

/* ------------------------------------------------------------------------
 * Metadata
 */

/*
 * Additionally to the payload headers we also want to provide the user with USB
 * Frame Numbers and प्रणाली समय values. The resulting buffer is thus composed
 * of blocks, containing a 64-bit बारtamp in  nanoseconds, a 16-bit USB Frame
 * Number, and a copy of the payload header.
 *
 * Ideally we want to capture all payload headers क्रम each frame. However, their
 * number is unknown and unbound. We thus drop headers that contain no venकरोr
 * data and that either contain no SCR value or an SCR value identical to the
 * previous header.
 */
अटल व्योम uvc_video_decode_meta(काष्ठा uvc_streaming *stream,
				  काष्ठा uvc_buffer *meta_buf,
				  स्थिर u8 *mem, अचिन्हित पूर्णांक length)
अणु
	काष्ठा uvc_meta_buf *meta;
	माप_प्रकार len_std = 2;
	bool has_pts, has_scr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक sof;
	kसमय_प्रकार समय;
	स्थिर u8 *scr;

	अगर (!meta_buf || length == 2)
		वापस;

	अगर (meta_buf->length - meta_buf->bytesused <
	    length + माप(meta->ns) + माप(meta->sof)) अणु
		meta_buf->error = 1;
		वापस;
	पूर्ण

	has_pts = mem[1] & UVC_STREAM_PTS;
	has_scr = mem[1] & UVC_STREAM_SCR;

	अगर (has_pts) अणु
		len_std += 4;
		scr = mem + 6;
	पूर्ण अन्यथा अणु
		scr = mem + 2;
	पूर्ण

	अगर (has_scr)
		len_std += 6;

	अगर (stream->meta.क्रमmat == V4L2_META_FMT_UVC)
		length = len_std;

	अगर (length == len_std && (!has_scr ||
				  !स_भेद(scr, stream->घड़ी.last_scr, 6)))
		वापस;

	meta = (काष्ठा uvc_meta_buf *)((u8 *)meta_buf->mem + meta_buf->bytesused);
	local_irq_save(flags);
	समय = uvc_video_get_समय();
	sof = usb_get_current_frame_number(stream->dev->udev);
	local_irq_restore(flags);
	put_unaligned(kसमय_प्रकारo_ns(समय), &meta->ns);
	put_unaligned(sof, &meta->sof);

	अगर (has_scr)
		स_नकल(stream->घड़ी.last_scr, scr, 6);

	स_नकल(&meta->length, mem, length);
	meta_buf->bytesused += length + माप(meta->ns) + माप(meta->sof);

	uvc_dbg(stream->dev, FRAME,
		"%s(): t-sys %lluns, SOF %u, len %u, flags 0x%x, PTS %u, STC %u frame SOF %u\n",
		__func__, kसमय_प्रकारo_ns(समय), meta->sof, meta->length,
		meta->flags,
		has_pts ? *(u32 *)meta->buf : 0,
		has_scr ? *(u32 *)scr : 0,
		has_scr ? *(u32 *)(scr + 4) & 0x7ff : 0);
पूर्ण

/* ------------------------------------------------------------------------
 * URB handling
 */

/*
 * Set error flag क्रम incomplete buffer.
 */
अटल व्योम uvc_video_validate_buffer(स्थिर काष्ठा uvc_streaming *stream,
				      काष्ठा uvc_buffer *buf)
अणु
	अगर (stream->ctrl.dwMaxVideoFrameSize != buf->bytesused &&
	    !(stream->cur_क्रमmat->flags & UVC_FMT_FLAG_COMPRESSED))
		buf->error = 1;
पूर्ण

/*
 * Completion handler क्रम video URBs.
 */

अटल व्योम uvc_video_next_buffers(काष्ठा uvc_streaming *stream,
		काष्ठा uvc_buffer **video_buf, काष्ठा uvc_buffer **meta_buf)
अणु
	uvc_video_validate_buffer(stream, *video_buf);

	अगर (*meta_buf) अणु
		काष्ठा vb2_v4l2_buffer *vb2_meta = &(*meta_buf)->buf;
		स्थिर काष्ठा vb2_v4l2_buffer *vb2_video = &(*video_buf)->buf;

		vb2_meta->sequence = vb2_video->sequence;
		vb2_meta->field = vb2_video->field;
		vb2_meta->vb2_buf.बारtamp = vb2_video->vb2_buf.बारtamp;

		(*meta_buf)->state = UVC_BUF_STATE_READY;
		अगर (!(*meta_buf)->error)
			(*meta_buf)->error = (*video_buf)->error;
		*meta_buf = uvc_queue_next_buffer(&stream->meta.queue,
						  *meta_buf);
	पूर्ण
	*video_buf = uvc_queue_next_buffer(&stream->queue, *video_buf);
पूर्ण

अटल व्योम uvc_video_decode_isoc(काष्ठा uvc_urb *uvc_urb,
			काष्ठा uvc_buffer *buf, काष्ठा uvc_buffer *meta_buf)
अणु
	काष्ठा urb *urb = uvc_urb->urb;
	काष्ठा uvc_streaming *stream = uvc_urb->stream;
	u8 *mem;
	पूर्णांक ret, i;

	क्रम (i = 0; i < urb->number_of_packets; ++i) अणु
		अगर (urb->iso_frame_desc[i].status < 0) अणु
			uvc_dbg(stream->dev, FRAME,
				"USB isochronous frame lost (%d)\n",
				urb->iso_frame_desc[i].status);
			/* Mark the buffer as faulty. */
			अगर (buf != शून्य)
				buf->error = 1;
			जारी;
		पूर्ण

		/* Decode the payload header. */
		mem = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		करो अणु
			ret = uvc_video_decode_start(stream, buf, mem,
				urb->iso_frame_desc[i].actual_length);
			अगर (ret == -EAGAIN)
				uvc_video_next_buffers(stream, &buf, &meta_buf);
		पूर्ण जबतक (ret == -EAGAIN);

		अगर (ret < 0)
			जारी;

		uvc_video_decode_meta(stream, meta_buf, mem, ret);

		/* Decode the payload data. */
		uvc_video_decode_data(uvc_urb, buf, mem + ret,
			urb->iso_frame_desc[i].actual_length - ret);

		/* Process the header again. */
		uvc_video_decode_end(stream, buf, mem,
			urb->iso_frame_desc[i].actual_length);

		अगर (buf->state == UVC_BUF_STATE_READY)
			uvc_video_next_buffers(stream, &buf, &meta_buf);
	पूर्ण
पूर्ण

अटल व्योम uvc_video_decode_bulk(काष्ठा uvc_urb *uvc_urb,
			काष्ठा uvc_buffer *buf, काष्ठा uvc_buffer *meta_buf)
अणु
	काष्ठा urb *urb = uvc_urb->urb;
	काष्ठा uvc_streaming *stream = uvc_urb->stream;
	u8 *mem;
	पूर्णांक len, ret;

	/*
	 * Ignore ZLPs अगर they're not part of a frame, otherwise process them
	 * to trigger the end of payload detection.
	 */
	अगर (urb->actual_length == 0 && stream->bulk.header_size == 0)
		वापस;

	mem = urb->transfer_buffer;
	len = urb->actual_length;
	stream->bulk.payload_size += len;

	/* If the URB is the first of its payload, decode and save the
	 * header.
	 */
	अगर (stream->bulk.header_size == 0 && !stream->bulk.skip_payload) अणु
		करो अणु
			ret = uvc_video_decode_start(stream, buf, mem, len);
			अगर (ret == -EAGAIN)
				uvc_video_next_buffers(stream, &buf, &meta_buf);
		पूर्ण जबतक (ret == -EAGAIN);

		/* If an error occurred skip the rest of the payload. */
		अगर (ret < 0 || buf == शून्य) अणु
			stream->bulk.skip_payload = 1;
		पूर्ण अन्यथा अणु
			स_नकल(stream->bulk.header, mem, ret);
			stream->bulk.header_size = ret;

			uvc_video_decode_meta(stream, meta_buf, mem, ret);

			mem += ret;
			len -= ret;
		पूर्ण
	पूर्ण

	/* The buffer queue might have been cancelled जबतक a bulk transfer
	 * was in progress, so we can reach here with buf equal to शून्य. Make
	 * sure buf is never dereferenced अगर शून्य.
	 */

	/* Prepare video data क्रम processing. */
	अगर (!stream->bulk.skip_payload && buf != शून्य)
		uvc_video_decode_data(uvc_urb, buf, mem, len);

	/* Detect the payload end by a URB smaller than the maximum size (or
	 * a payload size equal to the maximum) and process the header again.
	 */
	अगर (urb->actual_length < urb->transfer_buffer_length ||
	    stream->bulk.payload_size >= stream->bulk.max_payload_size) अणु
		अगर (!stream->bulk.skip_payload && buf != शून्य) अणु
			uvc_video_decode_end(stream, buf, stream->bulk.header,
				stream->bulk.payload_size);
			अगर (buf->state == UVC_BUF_STATE_READY)
				uvc_video_next_buffers(stream, &buf, &meta_buf);
		पूर्ण

		stream->bulk.header_size = 0;
		stream->bulk.skip_payload = 0;
		stream->bulk.payload_size = 0;
	पूर्ण
पूर्ण

अटल व्योम uvc_video_encode_bulk(काष्ठा uvc_urb *uvc_urb,
	काष्ठा uvc_buffer *buf, काष्ठा uvc_buffer *meta_buf)
अणु
	काष्ठा urb *urb = uvc_urb->urb;
	काष्ठा uvc_streaming *stream = uvc_urb->stream;

	u8 *mem = urb->transfer_buffer;
	पूर्णांक len = stream->urb_size, ret;

	अगर (buf == शून्य) अणु
		urb->transfer_buffer_length = 0;
		वापस;
	पूर्ण

	/* If the URB is the first of its payload, add the header. */
	अगर (stream->bulk.header_size == 0) अणु
		ret = uvc_video_encode_header(stream, buf, mem, len);
		stream->bulk.header_size = ret;
		stream->bulk.payload_size += ret;
		mem += ret;
		len -= ret;
	पूर्ण

	/* Process video data. */
	ret = uvc_video_encode_data(stream, buf, mem, len);

	stream->bulk.payload_size += ret;
	len -= ret;

	अगर (buf->bytesused == stream->queue.buf_used ||
	    stream->bulk.payload_size == stream->bulk.max_payload_size) अणु
		अगर (buf->bytesused == stream->queue.buf_used) अणु
			stream->queue.buf_used = 0;
			buf->state = UVC_BUF_STATE_READY;
			buf->buf.sequence = ++stream->sequence;
			uvc_queue_next_buffer(&stream->queue, buf);
			stream->last_fid ^= UVC_STREAM_FID;
		पूर्ण

		stream->bulk.header_size = 0;
		stream->bulk.payload_size = 0;
	पूर्ण

	urb->transfer_buffer_length = stream->urb_size - len;
पूर्ण

अटल व्योम uvc_video_complete(काष्ठा urb *urb)
अणु
	काष्ठा uvc_urb *uvc_urb = urb->context;
	काष्ठा uvc_streaming *stream = uvc_urb->stream;
	काष्ठा uvc_video_queue *queue = &stream->queue;
	काष्ठा uvc_video_queue *qmeta = &stream->meta.queue;
	काष्ठा vb2_queue *vb2_qmeta = stream->meta.vdev.queue;
	काष्ठा uvc_buffer *buf = शून्य;
	काष्ठा uvc_buffer *buf_meta = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;

	शेष:
		dev_warn(&stream->पूर्णांकf->dev,
			 "Non-zero status (%d) in video completion handler.\n",
			 urb->status);
		fallthrough;
	हाल -ENOENT:		/* usb_poison_urb() called. */
		अगर (stream->frozen)
			वापस;
		fallthrough;
	हाल -ECONNRESET:	/* usb_unlink_urb() called. */
	हाल -ESHUTDOWN:	/* The endpoपूर्णांक is being disabled. */
		uvc_queue_cancel(queue, urb->status == -ESHUTDOWN);
		अगर (vb2_qmeta)
			uvc_queue_cancel(qmeta, urb->status == -ESHUTDOWN);
		वापस;
	पूर्ण

	buf = uvc_queue_get_current_buffer(queue);

	अगर (vb2_qmeta) अणु
		spin_lock_irqsave(&qmeta->irqlock, flags);
		अगर (!list_empty(&qmeta->irqqueue))
			buf_meta = list_first_entry(&qmeta->irqqueue,
						    काष्ठा uvc_buffer, queue);
		spin_unlock_irqrestore(&qmeta->irqlock, flags);
	पूर्ण

	/* Re-initialise the URB async work. */
	uvc_urb->async_operations = 0;

	/* Sync DMA and invalidate vmap range. */
	dma_sync_sgtable_क्रम_cpu(uvc_stream_to_dmadev(uvc_urb->stream),
				 uvc_urb->sgt, uvc_stream_dir(stream));
	invalidate_kernel_vmap_range(uvc_urb->buffer,
				     uvc_urb->stream->urb_size);

	/*
	 * Process the URB headers, and optionally queue expensive स_नकल tasks
	 * to be deferred to a work queue.
	 */
	stream->decode(uvc_urb, buf, buf_meta);

	/* If no async work is needed, resubmit the URB immediately. */
	अगर (!uvc_urb->async_operations) अणु
		ret = uvc_submit_urb(uvc_urb, GFP_ATOMIC);
		अगर (ret < 0)
			dev_err(&stream->पूर्णांकf->dev,
				"Failed to resubmit video URB (%d).\n", ret);
		वापस;
	पूर्ण

	queue_work(stream->async_wq, &uvc_urb->work);
पूर्ण

/*
 * Free transfer buffers.
 */
अटल व्योम uvc_मुक्त_urb_buffers(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा device *dma_dev = uvc_stream_to_dmadev(stream);
	काष्ठा uvc_urb *uvc_urb;

	क्रम_each_uvc_urb(uvc_urb, stream) अणु
		अगर (!uvc_urb->buffer)
			जारी;

		dma_vunmap_noncontiguous(dma_dev, uvc_urb->buffer);
		dma_मुक्त_noncontiguous(dma_dev, stream->urb_size, uvc_urb->sgt,
				       uvc_stream_dir(stream));

		uvc_urb->buffer = शून्य;
		uvc_urb->sgt = शून्य;
	पूर्ण

	stream->urb_size = 0;
पूर्ण

अटल bool uvc_alloc_urb_buffer(काष्ठा uvc_streaming *stream,
				 काष्ठा uvc_urb *uvc_urb, gfp_t gfp_flags)
अणु
	काष्ठा device *dma_dev = uvc_stream_to_dmadev(stream);

	uvc_urb->sgt = dma_alloc_noncontiguous(dma_dev, stream->urb_size,
					       uvc_stream_dir(stream),
					       gfp_flags, 0);
	अगर (!uvc_urb->sgt)
		वापस false;
	uvc_urb->dma = uvc_urb->sgt->sgl->dma_address;

	uvc_urb->buffer = dma_vmap_noncontiguous(dma_dev, stream->urb_size,
						 uvc_urb->sgt);
	अगर (!uvc_urb->buffer) अणु
		dma_मुक्त_noncontiguous(dma_dev, stream->urb_size,
				       uvc_urb->sgt,
				       uvc_stream_dir(stream));
		uvc_urb->sgt = शून्य;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Allocate transfer buffers. This function can be called with buffers
 * alपढ़ोy allocated when resuming from suspend, in which हाल it will
 * वापस without touching the buffers.
 *
 * Limit the buffer size to UVC_MAX_PACKETS bulk/isochronous packets. If the
 * प्रणाली is too low on memory try successively smaller numbers of packets
 * until allocation succeeds.
 *
 * Return the number of allocated packets on success or 0 when out of memory.
 */
अटल पूर्णांक uvc_alloc_urb_buffers(काष्ठा uvc_streaming *stream,
	अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक psize, gfp_t gfp_flags)
अणु
	अचिन्हित पूर्णांक npackets;
	अचिन्हित पूर्णांक i;

	/* Buffers are alपढ़ोy allocated, bail out. */
	अगर (stream->urb_size)
		वापस stream->urb_size / psize;

	/* Compute the number of packets. Bulk endpoपूर्णांकs might transfer UVC
	 * payloads across multiple URBs.
	 */
	npackets = DIV_ROUND_UP(size, psize);
	अगर (npackets > UVC_MAX_PACKETS)
		npackets = UVC_MAX_PACKETS;

	/* Retry allocations until one succeed. */
	क्रम (; npackets > 1; npackets /= 2) अणु
		stream->urb_size = psize * npackets;

		क्रम (i = 0; i < UVC_URBS; ++i) अणु
			काष्ठा uvc_urb *uvc_urb = &stream->uvc_urb[i];

			अगर (!uvc_alloc_urb_buffer(stream, uvc_urb, gfp_flags)) अणु
				uvc_मुक्त_urb_buffers(stream);
				अवरोध;
			पूर्ण

			uvc_urb->stream = stream;
		पूर्ण

		अगर (i == UVC_URBS) अणु
			uvc_dbg(stream->dev, VIDEO,
				"Allocated %u URB buffers of %ux%u bytes each\n",
				UVC_URBS, npackets, psize);
			वापस npackets;
		पूर्ण
	पूर्ण

	uvc_dbg(stream->dev, VIDEO,
		"Failed to allocate URB buffers (%u bytes per packet)\n",
		psize);
	वापस 0;
पूर्ण

/*
 * Uninitialize isochronous/bulk URBs and मुक्त transfer buffers.
 */
अटल व्योम uvc_video_stop_transfer(काष्ठा uvc_streaming *stream,
				    पूर्णांक मुक्त_buffers)
अणु
	काष्ठा uvc_urb *uvc_urb;

	uvc_video_stats_stop(stream);

	/*
	 * We must poison the URBs rather than समाप्त them to ensure that even
	 * after the completion handler वापसs, any asynchronous workqueues
	 * will be prevented from resubmitting the URBs.
	 */
	क्रम_each_uvc_urb(uvc_urb, stream)
		usb_poison_urb(uvc_urb->urb);

	flush_workqueue(stream->async_wq);

	क्रम_each_uvc_urb(uvc_urb, stream) अणु
		usb_मुक्त_urb(uvc_urb->urb);
		uvc_urb->urb = शून्य;
	पूर्ण

	अगर (मुक्त_buffers)
		uvc_मुक्त_urb_buffers(stream);
पूर्ण

/*
 * Compute the maximum number of bytes per पूर्णांकerval क्रम an endpoपूर्णांक.
 */
अटल अचिन्हित पूर्णांक uvc_endpoपूर्णांक_max_bpi(काष्ठा usb_device *dev,
					 काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	u16 psize;
	u16 mult;

	चयन (dev->speed) अणु
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		वापस le16_to_cpu(ep->ss_ep_comp.wBytesPerInterval);
	हाल USB_SPEED_HIGH:
		psize = usb_endpoपूर्णांक_maxp(&ep->desc);
		mult = usb_endpoपूर्णांक_maxp_mult(&ep->desc);
		वापस psize * mult;
	हाल USB_SPEED_WIRELESS:
		psize = usb_endpoपूर्णांक_maxp(&ep->desc);
		वापस psize;
	शेष:
		psize = usb_endpoपूर्णांक_maxp(&ep->desc);
		वापस psize;
	पूर्ण
पूर्ण

/*
 * Initialize isochronous URBs and allocate transfer buffers. The packet size
 * is given by the endpoपूर्णांक.
 */
अटल पूर्णांक uvc_init_video_isoc(काष्ठा uvc_streaming *stream,
	काष्ठा usb_host_endpoपूर्णांक *ep, gfp_t gfp_flags)
अणु
	काष्ठा urb *urb;
	काष्ठा uvc_urb *uvc_urb;
	अचिन्हित पूर्णांक npackets, i;
	u16 psize;
	u32 size;

	psize = uvc_endpoपूर्णांक_max_bpi(stream->dev->udev, ep);
	size = stream->ctrl.dwMaxVideoFrameSize;

	npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);
	अगर (npackets == 0)
		वापस -ENOMEM;

	size = npackets * psize;

	क्रम_each_uvc_urb(uvc_urb, stream) अणु
		urb = usb_alloc_urb(npackets, gfp_flags);
		अगर (urb == शून्य) अणु
			uvc_video_stop_transfer(stream, 1);
			वापस -ENOMEM;
		पूर्ण

		urb->dev = stream->dev->udev;
		urb->context = uvc_urb;
		urb->pipe = usb_rcvisocpipe(stream->dev->udev,
				ep->desc.bEndpoपूर्णांकAddress);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_dma = uvc_urb->dma;
		urb->पूर्णांकerval = ep->desc.bInterval;
		urb->transfer_buffer = uvc_urb->buffer;
		urb->complete = uvc_video_complete;
		urb->number_of_packets = npackets;
		urb->transfer_buffer_length = size;

		क्रम (i = 0; i < npackets; ++i) अणु
			urb->iso_frame_desc[i].offset = i * psize;
			urb->iso_frame_desc[i].length = psize;
		पूर्ण

		uvc_urb->urb = urb;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialize bulk URBs and allocate transfer buffers. The packet size is
 * given by the endpoपूर्णांक.
 */
अटल पूर्णांक uvc_init_video_bulk(काष्ठा uvc_streaming *stream,
	काष्ठा usb_host_endpoपूर्णांक *ep, gfp_t gfp_flags)
अणु
	काष्ठा urb *urb;
	काष्ठा uvc_urb *uvc_urb;
	अचिन्हित पूर्णांक npackets, pipe;
	u16 psize;
	u32 size;

	psize = usb_endpoपूर्णांक_maxp(&ep->desc);
	size = stream->ctrl.dwMaxPayloadTransferSize;
	stream->bulk.max_payload_size = size;

	npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);
	अगर (npackets == 0)
		वापस -ENOMEM;

	size = npackets * psize;

	अगर (usb_endpoपूर्णांक_dir_in(&ep->desc))
		pipe = usb_rcvbulkpipe(stream->dev->udev,
				       ep->desc.bEndpoपूर्णांकAddress);
	अन्यथा
		pipe = usb_sndbulkpipe(stream->dev->udev,
				       ep->desc.bEndpoपूर्णांकAddress);

	अगर (stream->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		size = 0;

	क्रम_each_uvc_urb(uvc_urb, stream) अणु
		urb = usb_alloc_urb(0, gfp_flags);
		अगर (urb == शून्य) अणु
			uvc_video_stop_transfer(stream, 1);
			वापस -ENOMEM;
		पूर्ण

		usb_fill_bulk_urb(urb, stream->dev->udev, pipe,	uvc_urb->buffer,
				  size, uvc_video_complete, uvc_urb);
		urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_dma = uvc_urb->dma;

		uvc_urb->urb = urb;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialize isochronous/bulk URBs and allocate transfer buffers.
 */
अटल पूर्णांक uvc_video_start_transfer(काष्ठा uvc_streaming *stream,
				    gfp_t gfp_flags)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = stream->पूर्णांकf;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा uvc_urb *uvc_urb;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	stream->sequence = -1;
	stream->last_fid = -1;
	stream->bulk.header_size = 0;
	stream->bulk.skip_payload = 0;
	stream->bulk.payload_size = 0;

	uvc_video_stats_start(stream);

	अगर (पूर्णांकf->num_altsetting > 1) अणु
		काष्ठा usb_host_endpoपूर्णांक *best_ep = शून्य;
		अचिन्हित पूर्णांक best_psize = अच_पूर्णांक_उच्च;
		अचिन्हित पूर्णांक bandwidth;
		अचिन्हित पूर्णांक altsetting;
		पूर्णांक पूर्णांकfnum = stream->पूर्णांकfnum;

		/* Isochronous endpoपूर्णांक, select the alternate setting. */
		bandwidth = stream->ctrl.dwMaxPayloadTransferSize;

		अगर (bandwidth == 0) अणु
			uvc_dbg(stream->dev, VIDEO,
				"Device requested null bandwidth, defaulting to lowest\n");
			bandwidth = 1;
		पूर्ण अन्यथा अणु
			uvc_dbg(stream->dev, VIDEO,
				"Device requested %u B/frame bandwidth\n",
				bandwidth);
		पूर्ण

		क्रम (i = 0; i < पूर्णांकf->num_altsetting; ++i) अणु
			काष्ठा usb_host_पूर्णांकerface *alts;
			अचिन्हित पूर्णांक psize;

			alts = &पूर्णांकf->altsetting[i];
			ep = uvc_find_endpoपूर्णांक(alts,
				stream->header.bEndpoपूर्णांकAddress);
			अगर (ep == शून्य)
				जारी;

			/* Check अगर the bandwidth is high enough. */
			psize = uvc_endpoपूर्णांक_max_bpi(stream->dev->udev, ep);
			अगर (psize >= bandwidth && psize <= best_psize) अणु
				altsetting = alts->desc.bAlternateSetting;
				best_psize = psize;
				best_ep = ep;
			पूर्ण
		पूर्ण

		अगर (best_ep == शून्य) अणु
			uvc_dbg(stream->dev, VIDEO,
				"No fast enough alt setting for requested bandwidth\n");
			वापस -EIO;
		पूर्ण

		uvc_dbg(stream->dev, VIDEO,
			"Selecting alternate setting %u (%u B/frame bandwidth)\n",
			altsetting, best_psize);

		ret = usb_set_पूर्णांकerface(stream->dev->udev, पूर्णांकfnum, altsetting);
		अगर (ret < 0)
			वापस ret;

		ret = uvc_init_video_isoc(stream, best_ep, gfp_flags);
	पूर्ण अन्यथा अणु
		/* Bulk endpoपूर्णांक, proceed to URB initialization. */
		ep = uvc_find_endpoपूर्णांक(&पूर्णांकf->altsetting[0],
				stream->header.bEndpoपूर्णांकAddress);
		अगर (ep == शून्य)
			वापस -EIO;

		ret = uvc_init_video_bulk(stream, ep, gfp_flags);
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	/* Submit the URBs. */
	क्रम_each_uvc_urb(uvc_urb, stream) अणु
		ret = uvc_submit_urb(uvc_urb, gfp_flags);
		अगर (ret < 0) अणु
			dev_err(&stream->पूर्णांकf->dev,
				"Failed to submit URB %u (%d).\n",
				uvc_urb_index(uvc_urb), ret);
			uvc_video_stop_transfer(stream, 1);
			वापस ret;
		पूर्ण
	पूर्ण

	/* The Logitech C920 temporarily क्रममाला_लो that it should not be adjusting
	 * Exposure Absolute during init so restore controls to stored values.
	 */
	अगर (stream->dev->quirks & UVC_QUIRK_RESTORE_CTRLS_ON_INIT)
		uvc_ctrl_restore_values(stream->dev);

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
 * Suspend/resume
 */

/*
 * Stop streaming without disabling the video queue.
 *
 * To let userspace applications resume without trouble, we must not touch the
 * video buffers in any way. We mark the device as frozen to make sure the URB
 * completion handler won't try to cancel the queue when we समाप्त the URBs.
 */
पूर्णांक uvc_video_suspend(काष्ठा uvc_streaming *stream)
अणु
	अगर (!uvc_queue_streaming(&stream->queue))
		वापस 0;

	stream->frozen = 1;
	uvc_video_stop_transfer(stream, 0);
	usb_set_पूर्णांकerface(stream->dev->udev, stream->पूर्णांकfnum, 0);
	वापस 0;
पूर्ण

/*
 * Reconfigure the video पूर्णांकerface and restart streaming अगर it was enabled
 * beक्रमe suspend.
 *
 * If an error occurs, disable the video queue. This will wake all pending
 * buffers, making sure userspace applications are notअगरied of the problem
 * instead of रुकोing क्रमever.
 */
पूर्णांक uvc_video_resume(काष्ठा uvc_streaming *stream, पूर्णांक reset)
अणु
	पूर्णांक ret;

	/* If the bus has been reset on resume, set the alternate setting to 0.
	 * This should be the शेष value, but some devices crash or otherwise
	 * misbehave अगर they करोn't receive a SET_INTERFACE request beक्रमe any
	 * other video control request.
	 */
	अगर (reset)
		usb_set_पूर्णांकerface(stream->dev->udev, stream->पूर्णांकfnum, 0);

	stream->frozen = 0;

	uvc_video_घड़ी_reset(stream);

	अगर (!uvc_queue_streaming(&stream->queue))
		वापस 0;

	ret = uvc_commit_video(stream, &stream->ctrl);
	अगर (ret < 0)
		वापस ret;

	वापस uvc_video_start_transfer(stream, GFP_NOIO);
पूर्ण

/* ------------------------------------------------------------------------
 * Video device
 */

/*
 * Initialize the UVC video device by चयनing to alternate setting 0 and
 * retrieve the शेष क्रमmat.
 *
 * Some cameras (namely the Fuji Finepix) set the क्रमmat and frame
 * indexes to zero. The UVC standard करोesn't clearly make this a spec
 * violation, so try to silently fix the values अगर possible.
 *
 * This function is called beक्रमe रेजिस्टरing the device with V4L.
 */
पूर्णांक uvc_video_init(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा uvc_streaming_control *probe = &stream->ctrl;
	काष्ठा uvc_क्रमmat *क्रमmat = शून्य;
	काष्ठा uvc_frame *frame = शून्य;
	काष्ठा uvc_urb *uvc_urb;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (stream->nक्रमmats == 0) अणु
		dev_info(&stream->पूर्णांकf->dev,
			 "No supported video formats found.\n");
		वापस -EINVAL;
	पूर्ण

	atomic_set(&stream->active, 0);

	/* Alternate setting 0 should be the शेष, yet the XBox Live Vision
	 * Cam (and possibly other devices) crash or otherwise misbehave अगर
	 * they करोn't receive a SET_INTERFACE request beक्रमe any other video
	 * control request.
	 */
	usb_set_पूर्णांकerface(stream->dev->udev, stream->पूर्णांकfnum, 0);

	/* Set the streaming probe control with शेष streaming parameters
	 * retrieved from the device. Webcams that करोn't support GET_DEF
	 * requests on the probe control will just keep their current streaming
	 * parameters.
	 */
	अगर (uvc_get_video_ctrl(stream, probe, 1, UVC_GET_DEF) == 0)
		uvc_set_video_ctrl(stream, probe, 1);

	/* Initialize the streaming parameters with the probe control current
	 * value. This makes sure SET_CUR requests on the streaming commit
	 * control will always use values retrieved from a successful GET_CUR
	 * request on the probe control, as required by the UVC specअगरication.
	 */
	ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
	अगर (ret < 0)
		वापस ret;

	/* Check अगर the शेष क्रमmat descriptor exists. Use the first
	 * available क्रमmat otherwise.
	 */
	क्रम (i = stream->nक्रमmats; i > 0; --i) अणु
		क्रमmat = &stream->क्रमmat[i-1];
		अगर (क्रमmat->index == probe->bFormatIndex)
			अवरोध;
	पूर्ण

	अगर (क्रमmat->nframes == 0) अणु
		dev_info(&stream->पूर्णांकf->dev,
			 "No frame descriptor found for the default format.\n");
		वापस -EINVAL;
	पूर्ण

	/* Zero bFrameIndex might be correct. Stream-based क्रमmats (including
	 * MPEG-2 TS and DV) करो not support frames but have a dummy frame
	 * descriptor with bFrameIndex set to zero. If the शेष frame
	 * descriptor is not found, use the first available frame.
	 */
	क्रम (i = क्रमmat->nframes; i > 0; --i) अणु
		frame = &क्रमmat->frame[i-1];
		अगर (frame->bFrameIndex == probe->bFrameIndex)
			अवरोध;
	पूर्ण

	probe->bFormatIndex = क्रमmat->index;
	probe->bFrameIndex = frame->bFrameIndex;

	stream->def_क्रमmat = क्रमmat;
	stream->cur_क्रमmat = क्रमmat;
	stream->cur_frame = frame;

	/* Select the video decoding function */
	अगर (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		अगर (stream->dev->quirks & UVC_QUIRK_BUILTIN_ISIGHT)
			stream->decode = uvc_video_decode_isight;
		अन्यथा अगर (stream->पूर्णांकf->num_altsetting > 1)
			stream->decode = uvc_video_decode_isoc;
		अन्यथा
			stream->decode = uvc_video_decode_bulk;
	पूर्ण अन्यथा अणु
		अगर (stream->पूर्णांकf->num_altsetting == 1)
			stream->decode = uvc_video_encode_bulk;
		अन्यथा अणु
			dev_info(&stream->पूर्णांकf->dev,
				 "Isochronous endpoints are not supported for video output devices.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Prepare asynchronous work items. */
	क्रम_each_uvc_urb(uvc_urb, stream)
		INIT_WORK(&uvc_urb->work, uvc_video_copy_data_work);

	वापस 0;
पूर्ण

पूर्णांक uvc_video_start_streaming(काष्ठा uvc_streaming *stream)
अणु
	पूर्णांक ret;

	ret = uvc_video_घड़ी_init(stream);
	अगर (ret < 0)
		वापस ret;

	/* Commit the streaming parameters. */
	ret = uvc_commit_video(stream, &stream->ctrl);
	अगर (ret < 0)
		जाओ error_commit;

	ret = uvc_video_start_transfer(stream, GFP_KERNEL);
	अगर (ret < 0)
		जाओ error_video;

	वापस 0;

error_video:
	usb_set_पूर्णांकerface(stream->dev->udev, stream->पूर्णांकfnum, 0);
error_commit:
	uvc_video_घड़ी_cleanup(stream);

	वापस ret;
पूर्ण

व्योम uvc_video_stop_streaming(काष्ठा uvc_streaming *stream)
अणु
	uvc_video_stop_transfer(stream, 1);

	अगर (stream->पूर्णांकf->num_altsetting > 1) अणु
		usb_set_पूर्णांकerface(stream->dev->udev, stream->पूर्णांकfnum, 0);
	पूर्ण अन्यथा अणु
		/* UVC करोesn't specअगरy how to inक्रमm a bulk-based device
		 * when the video stream is stopped. Winकरोws sends a
		 * CLEAR_FEATURE(HALT) request to the video streaming
		 * bulk endpoपूर्णांक, mimic the same behaviour.
		 */
		अचिन्हित पूर्णांक epnum = stream->header.bEndpoपूर्णांकAddress
				   & USB_ENDPOINT_NUMBER_MASK;
		अचिन्हित पूर्णांक dir = stream->header.bEndpoपूर्णांकAddress
				 & USB_ENDPOINT_सूची_MASK;
		अचिन्हित पूर्णांक pipe;

		pipe = usb_sndbulkpipe(stream->dev->udev, epnum) | dir;
		usb_clear_halt(stream->dev->udev, pipe);
	पूर्ण

	uvc_video_घड़ी_cleanup(stream);
पूर्ण
