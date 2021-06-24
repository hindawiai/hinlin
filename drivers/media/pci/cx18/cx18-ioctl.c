<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 ioctl प्रणाली call
 *
 *  Derived from ivtv-ioctl.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-version.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-i2c.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-fileops.h"
#समावेश "cx18-vbi.h"
#समावेश "cx18-audio.h"
#समावेश "cx18-video.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-ioctl.h"
#समावेश "cx18-gpio.h"
#समावेश "cx18-controls.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-av-core.h"
#समावेश <media/tveeprom.h>
#समावेश <media/v4l2-event.h>

u16 cx18_service2vbi(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल V4L2_SLICED_TELETEXT_B:
		वापस CX18_SLICED_TYPE_TELETEXT_B;
	हाल V4L2_SLICED_CAPTION_525:
		वापस CX18_SLICED_TYPE_CAPTION_525;
	हाल V4L2_SLICED_WSS_625:
		वापस CX18_SLICED_TYPE_WSS_625;
	हाल V4L2_SLICED_VPS:
		वापस CX18_SLICED_TYPE_VPS;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Check अगर VBI services are allowed on the (field, line) क्रम the video std */
अटल पूर्णांक valid_service_line(पूर्णांक field, पूर्णांक line, पूर्णांक is_pal)
अणु
	वापस (is_pal && line >= 6 &&
		((field == 0 && line <= 23) || (field == 1 && line <= 22))) ||
	       (!is_pal && line >= 10 && line < 22);
पूर्ण

/*
 * For a (field, line, std) and inbound potential set of services क्रम that line,
 * वापस the first valid service of those passed in the incoming set क्रम that
 * line in priority order:
 * CC, VPS, or WSS over TELETEXT क्रम well known lines
 * TELETEXT, beक्रमe VPS, beक्रमe CC, beक्रमe WSS, क्रम other lines
 */
अटल u16 select_service_from_set(पूर्णांक field, पूर्णांक line, u16 set, पूर्णांक is_pal)
अणु
	u16 valid_set = (is_pal ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525);
	पूर्णांक i;

	set = set & valid_set;
	अगर (set == 0 || !valid_service_line(field, line, is_pal))
		वापस 0;
	अगर (!is_pal) अणु
		अगर (line == 21 && (set & V4L2_SLICED_CAPTION_525))
			वापस V4L2_SLICED_CAPTION_525;
	पूर्ण अन्यथा अणु
		अगर (line == 16 && field == 0 && (set & V4L2_SLICED_VPS))
			वापस V4L2_SLICED_VPS;
		अगर (line == 23 && field == 0 && (set & V4L2_SLICED_WSS_625))
			वापस V4L2_SLICED_WSS_625;
		अगर (line == 23)
			वापस 0;
	पूर्ण
	क्रम (i = 0; i < 32; i++) अणु
		अगर (BIT(i) & set)
			वापस 1 << i;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Expand the service_set of *fmt पूर्णांकo valid service_lines क्रम the std,
 * and clear the passed in fmt->service_set
 */
व्योम cx18_expand_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt, पूर्णांक is_pal)
अणु
	u16 set = fmt->service_set;
	पूर्णांक f, l;

	fmt->service_set = 0;
	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++)
			fmt->service_lines[f][l] = select_service_from_set(f, l, set, is_pal);
	पूर्ण
पूर्ण

/*
 * Sanitize the service_lines in *fmt per the video std, and वापस 1
 * अगर any service_line is left as valid after santization
 */
अटल पूर्णांक check_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt, पूर्णांक is_pal)
अणु
	पूर्णांक f, l;
	u16 set = 0;

	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++) अणु
			fmt->service_lines[f][l] = select_service_from_set(f, l, fmt->service_lines[f][l], is_pal);
			set |= fmt->service_lines[f][l];
		पूर्ण
	पूर्ण
	वापस set != 0;
पूर्ण

/* Compute the service_set from the assumed valid service_lines of *fmt */
u16 cx18_get_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt)
अणु
	पूर्णांक f, l;
	u16 set = 0;

	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++)
			set |= fmt->service_lines[f][l];
	पूर्ण
	वापस set;
पूर्ण

अटल पूर्णांक cx18_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;

	pixfmt->width = cx->cxhdl.width;
	pixfmt->height = cx->cxhdl.height;
	pixfmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pixfmt->field = V4L2_FIELD_INTERLACED;
	अगर (id->type == CX18_ENC_STREAM_TYPE_YUV) अणु
		pixfmt->pixelक्रमmat = s->pixelक्रमmat;
		pixfmt->sizeimage = s->vb_bytes_per_frame;
		pixfmt->bytesperline = s->vb_bytes_per_line;
	पूर्ण अन्यथा अणु
		pixfmt->pixelक्रमmat = V4L2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytesperline = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_fmt_vbi_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;
	काष्ठा v4l2_vbi_क्रमmat *vbअगरmt = &fmt->fmt.vbi;

	vbअगरmt->sampling_rate = 27000000;
	vbअगरmt->offset = 248; /* FIXME - slightly wrong क्रम both 50 & 60 Hz */
	vbअगरmt->samples_per_line = VBI_ACTIVE_SAMPLES - 4;
	vbअगरmt->sample_क्रमmat = V4L2_PIX_FMT_GREY;
	vbअगरmt->start[0] = cx->vbi.start[0];
	vbअगरmt->start[1] = cx->vbi.start[1];
	vbअगरmt->count[0] = vbअगरmt->count[1] = cx->vbi.count;
	vbअगरmt->flags = 0;
	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;

	/* sane, V4L2 spec compliant, शेषs */
	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;
	vbअगरmt->io_size = माप(काष्ठा v4l2_sliced_vbi_data) * 36;
	स_रखो(vbअगरmt->service_lines, 0, माप(vbअगरmt->service_lines));
	vbअगरmt->service_set = 0;

	/*
	 * Fetch the configured service_lines and total service_set from the
	 * digitizer/slicer.  Note, cx18_av_vbi() wipes the passed in
	 * fmt->fmt.sliced under valid calling conditions
	 */
	अगर (v4l2_subdev_call(cx->sd_av, vbi, g_sliced_fmt, &fmt->fmt.sliced))
		वापस -EINVAL;

	vbअगरmt->service_set = cx18_get_service_set(vbअगरmt);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	पूर्णांक w = fmt->fmt.pix.width;
	पूर्णांक h = fmt->fmt.pix.height;
	पूर्णांक min_h = 2;

	w = min(w, 720);
	w = max(w, 2);
	अगर (id->type == CX18_ENC_STREAM_TYPE_YUV) अणु
		/* YUV height must be a multiple of 32 */
		h &= ~0x1f;
		min_h = 32;
	पूर्ण
	h = min(h, cx->is_50hz ? 576 : 480);
	h = max(h, min_h);

	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_try_fmt_vbi_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	वापस cx18_g_fmt_vbi_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक cx18_try_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;

	vbअगरmt->io_size = माप(काष्ठा v4l2_sliced_vbi_data) * 36;
	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;

	/* If given a service set, expand it validly & clear passed in set */
	अगर (vbअगरmt->service_set)
		cx18_expand_service_set(vbअगरmt, cx->is_50hz);
	/* Sanitize the service_lines, and compute the new set अगर any valid */
	अगर (check_service_set(vbअगरmt, cx->is_50hz))
		vbअगरmt->service_set = cx18_get_service_set(vbअगरmt);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	पूर्णांक ret;
	पूर्णांक w, h;

	ret = cx18_try_fmt_vid_cap(file, fh, fmt);
	अगर (ret)
		वापस ret;
	w = fmt->fmt.pix.width;
	h = fmt->fmt.pix.height;

	अगर (cx->cxhdl.width == w && cx->cxhdl.height == h &&
	    s->pixelक्रमmat == fmt->fmt.pix.pixelक्रमmat)
		वापस 0;

	अगर (atomic_पढ़ो(&cx->ana_capturing) > 0)
		वापस -EBUSY;

	s->pixelक्रमmat = fmt->fmt.pix.pixelक्रमmat;
	/* HM12 YUV size is (Y=(h*720) + UV=(h*(720/2)))
	   UYUV YUV size is (Y=(h*720) + UV=(h*(720))) */
	अगर (s->pixelक्रमmat == V4L2_PIX_FMT_HM12) अणु
		s->vb_bytes_per_frame = h * 720 * 3 / 2;
		s->vb_bytes_per_line = 720; /* First plane */
	पूर्ण अन्यथा अणु
		s->vb_bytes_per_frame = h * 720 * 2;
		s->vb_bytes_per_line = 1440; /* Packed */
	पूर्ण

	क्रमmat.क्रमmat.width = cx->cxhdl.width = w;
	क्रमmat.क्रमmat.height = cx->cxhdl.height = h;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	v4l2_subdev_call(cx->sd_av, pad, set_fmt, शून्य, &क्रमmat);
	वापस cx18_g_fmt_vid_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक cx18_s_fmt_vbi_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	पूर्णांक ret;

	/*
	 * Changing the Encoder's Raw VBI parameters won't have any effect
	 * अगर any analog capture is ongoing
	 */
	अगर (!cx18_raw_vbi(cx) && atomic_पढ़ो(&cx->ana_capturing) > 0)
		वापस -EBUSY;

	/*
	 * Set the digitizer रेजिस्टरs क्रम raw active VBI.
	 * Note cx18_av_vbi_wipes out a lot of the passed in fmt under valid
	 * calling conditions
	 */
	ret = v4l2_subdev_call(cx->sd_av, vbi, s_raw_fmt, &fmt->fmt.vbi);
	अगर (ret)
		वापस ret;

	/* Store our new v4l2 (non-)sliced VBI state */
	cx->vbi.sliced_in->service_set = 0;
	cx->vbi.in.type = V4L2_BUF_TYPE_VBI_CAPTURE;

	वापस cx18_g_fmt_vbi_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक cx18_s_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	पूर्णांक ret;
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;

	cx18_try_fmt_sliced_vbi_cap(file, fh, fmt);

	/*
	 * Changing the Encoder's Raw VBI parameters won't have any effect
	 * अगर any analog capture is ongoing
	 */
	अगर (cx18_raw_vbi(cx) && atomic_पढ़ो(&cx->ana_capturing) > 0)
		वापस -EBUSY;

	/*
	 * Set the service_lines requested in the digitizer/slicer रेजिस्टरs.
	 * Note, cx18_av_vbi() wipes some "impossible" service lines in the
	 * passed in fmt->fmt.sliced under valid calling conditions
	 */
	ret = v4l2_subdev_call(cx->sd_av, vbi, s_sliced_fmt, &fmt->fmt.sliced);
	अगर (ret)
		वापस ret;
	/* Store our current v4l2 sliced VBI settings */
	cx->vbi.in.type =  V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	स_नकल(cx->vbi.sliced_in, vbअगरmt, माप(*cx->vbi.sliced_in));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक cx18_g_रेजिस्टर(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (reg->reg & 0x3)
		वापस -EINVAL;
	अगर (reg->reg >= CX18_MEM_OFFSET + CX18_MEM_SIZE)
		वापस -EINVAL;
	reg->size = 4;
	reg->val = cx18_पढ़ो_enc(cx, reg->reg);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_s_रेजिस्टर(काष्ठा file *file, व्योम *fh,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (reg->reg & 0x3)
		वापस -EINVAL;
	अगर (reg->reg >= CX18_MEM_OFFSET + CX18_MEM_SIZE)
		वापस -EINVAL;
	cx18_ग_लिखो_enc(cx, reg->val, reg->reg);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cx18_querycap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_capability *vcap)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;

	strscpy(vcap->driver, CX18_DRIVER_NAME, माप(vcap->driver));
	strscpy(vcap->card, cx->card_name, माप(vcap->card));
	snम_लिखो(vcap->bus_info, माप(vcap->bus_info),
		 "PCI:%s", pci_name(cx->pci_dev));
	vcap->capabilities = cx->v4l2_cap | V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	वापस cx18_get_audio_input(cx, vin->index, vin);
पूर्ण

अटल पूर्णांक cx18_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	vin->index = cx->audio_input;
	वापस cx18_get_audio_input(cx, vin->index, vin);
पूर्ण

अटल पूर्णांक cx18_s_audio(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audio *vout)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (vout->index >= cx->nof_audio_inमाला_दो)
		वापस -EINVAL;
	cx->audio_input = vout->index;
	cx18_audio_set_io(cx);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *vin)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	/* set it to शेषs from our table */
	वापस cx18_get_input(cx, vin->index, vin);
पूर्ण

अटल पूर्णांक cx18_g_pixelaspect(काष्ठा file *file, व्योम *fh,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	f->numerator = cx->is_50hz ? 54 : 11;
	f->denominator = cx->is_50hz ? 59 : 10;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.top = sel->r.left = 0;
		sel->r.width = 720;
		sel->r.height = cx->is_50hz ? 576 : 480;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_fmtdesc *fmt)
अणु
	अटल स्थिर काष्ठा v4l2_fmtdesc क्रमmats[] = अणु
		अणु
			.index = 0,
			.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
			.description = "HM12 (YUV 4:1:1)",
			.pixelक्रमmat = V4L2_PIX_FMT_HM12,
		पूर्ण,
		अणु
			.index = 1,
			.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
			.flags = V4L2_FMT_FLAG_COMPRESSED,
			.description = "MPEG",
			.pixelक्रमmat = V4L2_PIX_FMT_MPEG,
		पूर्ण,
		अणु
			.index = 2,
			.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
			.description = "UYVY 4:2:2",
			.pixelक्रमmat = V4L2_PIX_FMT_UYVY,
		पूर्ण,
	पूर्ण;

	अगर (fmt->index > ARRAY_SIZE(क्रमmats) - 1)
		वापस -EINVAL;
	*fmt = क्रमmats[fmt->index];
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	*i = cx->active_input;
	वापस 0;
पूर्ण

पूर्णांक cx18_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक inp)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	v4l2_std_id std = V4L2_STD_ALL;
	स्थिर काष्ठा cx18_card_video_input *card_input =
				cx->card->video_inमाला_दो + inp;

	अगर (inp >= cx->nof_inमाला_दो)
		वापस -EINVAL;

	अगर (inp == cx->active_input) अणु
		CX18_DEBUG_INFO("Input unchanged\n");
		वापस 0;
	पूर्ण

	CX18_DEBUG_INFO("Changing input from %d to %d\n",
			cx->active_input, inp);

	cx->active_input = inp;
	/* Set the audio input to whatever is appropriate क्रम the input type. */
	cx->audio_input = cx->card->video_inमाला_दो[inp].audio_index;
	अगर (card_input->video_type == V4L2_INPUT_TYPE_TUNER)
		std = cx->tuner_std;
	cx->streams[CX18_ENC_STREAM_TYPE_MPG].video_dev.tvnorms = std;
	cx->streams[CX18_ENC_STREAM_TYPE_YUV].video_dev.tvnorms = std;
	cx->streams[CX18_ENC_STREAM_TYPE_VBI].video_dev.tvnorms = std;

	/* prevent others from messing with the streams until
	   we're finished changing inमाला_दो. */
	cx18_mute(cx);
	cx18_video_set_io(cx);
	cx18_audio_set_io(cx);
	cx18_unmute(cx);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_frequency(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (vf->tuner != 0)
		वापस -EINVAL;

	cx18_call_all(cx, tuner, g_frequency, vf);
	वापस 0;
पूर्ण

पूर्णांक cx18_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;

	अगर (vf->tuner != 0)
		वापस -EINVAL;

	cx18_mute(cx);
	CX18_DEBUG_INFO("v4l2 ioctl: set frequency %d\n", vf->frequency);
	cx18_call_all(cx, tuner, s_frequency, vf);
	cx18_unmute(cx);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_std(काष्ठा file *file, व्योम *fh, v4l2_std_id *std)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	*std = cx->std;
	वापस 0;
पूर्ण

पूर्णांक cx18_s_std(काष्ठा file *file, व्योम *fh, v4l2_std_id std)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;

	अगर ((std & V4L2_STD_ALL) == 0)
		वापस -EINVAL;

	अगर (std == cx->std)
		वापस 0;

	अगर (test_bit(CX18_F_I_RADIO_USER, &cx->i_flags) ||
	    atomic_पढ़ो(&cx->ana_capturing) > 0) अणु
		/* Switching standard would turn off the radio or mess
		   with alपढ़ोy running streams, prevent that by
		   वापसing EBUSY. */
		वापस -EBUSY;
	पूर्ण

	cx->std = std;
	cx->is_60hz = (std & V4L2_STD_525_60) ? 1 : 0;
	cx->is_50hz = !cx->is_60hz;
	cx2341x_handler_set_50hz(&cx->cxhdl, cx->is_50hz);
	cx->cxhdl.width = 720;
	cx->cxhdl.height = cx->is_50hz ? 576 : 480;
	cx->vbi.count = cx->is_50hz ? 18 : 12;
	cx->vbi.start[0] = cx->is_50hz ? 6 : 10;
	cx->vbi.start[1] = cx->is_50hz ? 318 : 273;
	CX18_DEBUG_INFO("Switching standard to %llx.\n",
			(अचिन्हित दीर्घ दीर्घ) cx->std);

	/* Tuner */
	cx18_call_all(cx, video, s_std, cx->std);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;

	अगर (vt->index != 0)
		वापस -EINVAL;

	cx18_call_all(cx, tuner, s_tuner, vt);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	अगर (vt->index != 0)
		वापस -EINVAL;

	cx18_call_all(cx, tuner, g_tuner, vt);

	अगर (vt->type == V4L2_TUNER_RADIO)
		strscpy(vt->name, "cx18 Radio Tuner", माप(vt->name));
	अन्यथा
		strscpy(vt->name, "cx18 TV Tuner", माप(vt->name));
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_sliced_vbi_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_sliced_vbi_cap *cap)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;
	पूर्णांक set = cx->is_50hz ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525;
	पूर्णांक f, l;

	अगर (cap->type != V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
		वापस -EINVAL;

	cap->service_set = 0;
	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++) अणु
			अगर (valid_service_line(f, l, cx->is_50hz)) अणु
				/*
				 * We can find all v4l2 supported vbi services
				 * क्रम the standard, on a valid line क्रम the std
				 */
				cap->service_lines[f][l] = set;
				cap->service_set |= set;
			पूर्ण अन्यथा
				cap->service_lines[f][l] = 0;
		पूर्ण
	पूर्ण
	क्रम (f = 0; f < 3; f++)
		cap->reserved[f] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक _cx18_process_idx_data(काष्ठा cx18_buffer *buf,
				  काष्ठा v4l2_enc_idx *idx)
अणु
	पूर्णांक consumed, reमुख्यing;
	काष्ठा v4l2_enc_idx_entry *e_idx;
	काष्ठा cx18_enc_idx_entry *e_buf;

	/* Frame type lookup: 1=I, 2=P, 4=B */
	अटल स्थिर पूर्णांक mapping[8] = अणु
		-1, V4L2_ENC_IDX_FRAME_I, V4L2_ENC_IDX_FRAME_P,
		-1, V4L2_ENC_IDX_FRAME_B, -1, -1, -1
	पूर्ण;

	/*
	 * Assumption here is that a buf holds an पूर्णांकegral number of
	 * काष्ठा cx18_enc_idx_entry objects and is properly aligned.
	 * This is enक्रमced by the module options on IDX buffer sizes.
	 */
	reमुख्यing = buf->bytesused - buf->पढ़ोpos;
	consumed = 0;
	e_idx = &idx->entry[idx->entries];
	e_buf = (काष्ठा cx18_enc_idx_entry *) &buf->buf[buf->पढ़ोpos];

	जबतक (reमुख्यing >= माप(काष्ठा cx18_enc_idx_entry) &&
	       idx->entries < V4L2_ENC_IDX_ENTRIES) अणु

		e_idx->offset = (((u64) le32_to_cpu(e_buf->offset_high)) << 32)
				| le32_to_cpu(e_buf->offset_low);

		e_idx->pts = (((u64) (le32_to_cpu(e_buf->pts_high) & 1)) << 32)
			     | le32_to_cpu(e_buf->pts_low);

		e_idx->length = le32_to_cpu(e_buf->length);

		e_idx->flags = mapping[le32_to_cpu(e_buf->flags) & 0x7];

		e_idx->reserved[0] = 0;
		e_idx->reserved[1] = 0;

		idx->entries++;
		e_idx = &idx->entry[idx->entries];
		e_buf++;

		reमुख्यing -= माप(काष्ठा cx18_enc_idx_entry);
		consumed += माप(काष्ठा cx18_enc_idx_entry);
	पूर्ण

	/* Swallow any partial entries at the end, अगर there are any */
	अगर (reमुख्यing > 0 && reमुख्यing < माप(काष्ठा cx18_enc_idx_entry))
		consumed += reमुख्यing;

	buf->पढ़ोpos += consumed;
	वापस consumed;
पूर्ण

अटल पूर्णांक cx18_process_idx_data(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl,
				 काष्ठा v4l2_enc_idx *idx)
अणु
	अगर (s->type != CX18_ENC_STREAM_TYPE_IDX)
		वापस -EINVAL;

	अगर (mdl->curr_buf == शून्य)
		mdl->curr_buf = list_first_entry(&mdl->buf_list,
						 काष्ठा cx18_buffer, list);

	अगर (list_entry_is_past_end(mdl->curr_buf, &mdl->buf_list, list)) अणु
		/*
		 * For some reason we've exhausted the buffers, but the MDL
		 * object still said some data was unपढ़ो.
		 * Fix that and bail out.
		 */
		mdl->पढ़ोpos = mdl->bytesused;
		वापस 0;
	पूर्ण

	list_क्रम_each_entry_from(mdl->curr_buf, &mdl->buf_list, list) अणु

		/* Skip any empty buffers in the MDL */
		अगर (mdl->curr_buf->पढ़ोpos >= mdl->curr_buf->bytesused)
			जारी;

		mdl->पढ़ोpos += _cx18_process_idx_data(mdl->curr_buf, idx);

		/* निकास when MDL drained or request satisfied */
		अगर (idx->entries >= V4L2_ENC_IDX_ENTRIES ||
		    mdl->curr_buf->पढ़ोpos < mdl->curr_buf->bytesused ||
		    mdl->पढ़ोpos >= mdl->bytesused)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_g_enc_index(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_enc_idx *idx)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;
	काष्ठा cx18_stream *s = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	s32 पंचांगp;
	काष्ठा cx18_mdl *mdl;

	अगर (!cx18_stream_enabled(s)) /* Module options inhibited IDX stream */
		वापस -EINVAL;

	/* Compute the best हाल number of entries we can buffer */
	पंचांगp = s->buffers -
			  s->bufs_per_mdl * CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN;
	अगर (पंचांगp <= 0)
		पंचांगp = 1;
	पंचांगp = पंचांगp * s->buf_size / माप(काष्ठा cx18_enc_idx_entry);

	/* Fill out the header of the वापस काष्ठाure */
	idx->entries = 0;
	idx->entries_cap = पंचांगp;
	स_रखो(idx->reserved, 0, माप(idx->reserved));

	/* Pull IDX MDLs and buffers from q_full and populate the entries */
	करो अणु
		mdl = cx18_dequeue(s, &s->q_full);
		अगर (mdl == शून्य) /* No more IDX data right now */
			अवरोध;

		/* Extract the Index entry data from the MDL and buffers */
		cx18_process_idx_data(s, mdl, idx);
		अगर (mdl->पढ़ोpos < mdl->bytesused) अणु
			/* We finished with data reमुख्यing, push the MDL back */
			cx18_push(s, mdl, &s->q_full);
			अवरोध;
		पूर्ण

		/* We drained this MDL, schedule it to go to the firmware */
		cx18_enqueue(s, mdl, &s->q_मुक्त);

	पूर्ण जबतक (idx->entries < V4L2_ENC_IDX_ENTRIES);

	/* Tell the work handler to send मुक्त IDX MDLs to the firmware */
	cx18_stream_load_fw_queue(s);
	वापस 0;
पूर्ण

अटल काष्ठा videobuf_queue *cx18_vb_queue(काष्ठा cx18_खोलो_id *id)
अणु
	काष्ठा videobuf_queue *q = शून्य;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	चयन (s->vb_type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		q = &s->vbuf_q;
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस q;
पूर्ण

अटल पूर्णांक cx18_streamon(काष्ठा file *file, व्योम *priv,
	क्रमागत v4l2_buf_type type)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	/* Start the hardware only अगर we're the video device */
	अगर ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		वापस -EINVAL;

	अगर (id->type != CX18_ENC_STREAM_TYPE_YUV)
		वापस -EINVAL;

	/* Establish a buffer समयout */
	mod_समयr(&s->vb_समयout, msecs_to_jअगरfies(2000) + jअगरfies);

	वापस videobuf_streamon(cx18_vb_queue(id));
पूर्ण

अटल पूर्णांक cx18_streamoff(काष्ठा file *file, व्योम *priv,
	क्रमागत v4l2_buf_type type)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	/* Start the hardware only अगर we're the video device */
	अगर ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		वापस -EINVAL;

	अगर (id->type != CX18_ENC_STREAM_TYPE_YUV)
		वापस -EINVAL;

	वापस videobuf_streamoff(cx18_vb_queue(id));
पूर्ण

अटल पूर्णांक cx18_reqbufs(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	अगर ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		वापस -EINVAL;

	वापस videobuf_reqbufs(cx18_vb_queue(id), rb);
पूर्ण

अटल पूर्णांक cx18_querybuf(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_buffer *b)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	अगर ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		वापस -EINVAL;

	वापस videobuf_querybuf(cx18_vb_queue(id), b);
पूर्ण

अटल पूर्णांक cx18_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	अगर ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		वापस -EINVAL;

	वापस videobuf_qbuf(cx18_vb_queue(id), b);
पूर्ण

अटल पूर्णांक cx18_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	अगर ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		वापस -EINVAL;

	वापस videobuf_dqbuf(cx18_vb_queue(id), b, file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक cx18_encoder_cmd(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_encoder_cmd *enc)
अणु
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	u32 h;

	चयन (enc->cmd) अणु
	हाल V4L2_ENC_CMD_START:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_START\n");
		enc->flags = 0;
		वापस cx18_start_capture(id);

	हाल V4L2_ENC_CMD_STOP:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_STOP\n");
		enc->flags &= V4L2_ENC_CMD_STOP_AT_GOP_END;
		cx18_stop_capture(id,
				  enc->flags & V4L2_ENC_CMD_STOP_AT_GOP_END);
		अवरोध;

	हाल V4L2_ENC_CMD_PAUSE:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_PAUSE\n");
		enc->flags = 0;
		अगर (!atomic_पढ़ो(&cx->ana_capturing))
			वापस -EPERM;
		अगर (test_and_set_bit(CX18_F_I_ENC_PAUSED, &cx->i_flags))
			वापस 0;
		h = cx18_find_handle(cx);
		अगर (h == CX18_INVALID_TASK_HANDLE) अणु
			CX18_ERR("Can't find valid task handle for V4L2_ENC_CMD_PAUSE\n");
			वापस -EBADFD;
		पूर्ण
		cx18_mute(cx);
		cx18_vapi(cx, CX18_CPU_CAPTURE_PAUSE, 1, h);
		अवरोध;

	हाल V4L2_ENC_CMD_RESUME:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_RESUME\n");
		enc->flags = 0;
		अगर (!atomic_पढ़ो(&cx->ana_capturing))
			वापस -EPERM;
		अगर (!test_and_clear_bit(CX18_F_I_ENC_PAUSED, &cx->i_flags))
			वापस 0;
		h = cx18_find_handle(cx);
		अगर (h == CX18_INVALID_TASK_HANDLE) अणु
			CX18_ERR("Can't find valid task handle for V4L2_ENC_CMD_RESUME\n");
			वापस -EBADFD;
		पूर्ण
		cx18_vapi(cx, CX18_CPU_CAPTURE_RESUME, 1, h);
		cx18_unmute(cx);
		अवरोध;

	शेष:
		CX18_DEBUG_IOCTL("Unknown cmd %d\n", enc->cmd);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_try_encoder_cmd(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_encoder_cmd *enc)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	चयन (enc->cmd) अणु
	हाल V4L2_ENC_CMD_START:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_START\n");
		enc->flags = 0;
		अवरोध;

	हाल V4L2_ENC_CMD_STOP:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_STOP\n");
		enc->flags &= V4L2_ENC_CMD_STOP_AT_GOP_END;
		अवरोध;

	हाल V4L2_ENC_CMD_PAUSE:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_PAUSE\n");
		enc->flags = 0;
		अवरोध;

	हाल V4L2_ENC_CMD_RESUME:
		CX18_DEBUG_IOCTL("V4L2_ENC_CMD_RESUME\n");
		enc->flags = 0;
		अवरोध;

	शेष:
		CX18_DEBUG_IOCTL("Unknown cmd %d\n", enc->cmd);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;
	काष्ठा v4l2_input vidin;
	काष्ठा v4l2_audio audin;
	पूर्णांक i;

	CX18_INFO("Version: %s  Card: %s\n", CX18_VERSION, cx->card_name);
	अगर (cx->hw_flags & CX18_HW_TVEEPROM) अणु
		काष्ठा tveeprom tv;

		cx18_पढ़ो_eeprom(cx, &tv);
	पूर्ण
	cx18_call_all(cx, core, log_status);
	cx18_get_input(cx, cx->active_input, &vidin);
	cx18_get_audio_input(cx, cx->audio_input, &audin);
	CX18_INFO("Video Input: %s\n", vidin.name);
	CX18_INFO("Audio Input: %s\n", audin.name);
	mutex_lock(&cx->gpio_lock);
	CX18_INFO("GPIO:  direction 0x%08x, value 0x%08x\n",
		cx->gpio_dir, cx->gpio_val);
	mutex_unlock(&cx->gpio_lock);
	CX18_INFO("Tuner: %s\n",
		test_bit(CX18_F_I_RADIO_USER, &cx->i_flags) ?  "Radio" : "TV");
	v4l2_ctrl_handler_log_status(&cx->cxhdl.hdl, cx->v4l2_dev.name);
	CX18_INFO("Status flags: 0x%08lx\n", cx->i_flags);
	क्रम (i = 0; i < CX18_MAX_STREAMS; i++) अणु
		काष्ठा cx18_stream *s = &cx->streams[i];

		अगर (s->video_dev.v4l2_dev == शून्य || s->buffers == 0)
			जारी;
		CX18_INFO("Stream %s: status 0x%04lx, %d%% of %d KiB (%d buffers) in use\n",
			  s->name, s->s_flags,
			  atomic_पढ़ो(&s->q_full.depth) * s->bufs_per_mdl * 100
			   / s->buffers,
			  (s->buffers * s->buf_size) / 1024, s->buffers);
	पूर्ण
	CX18_INFO("Read MPEG/VBI: %lld/%lld bytes\n",
			(दीर्घ दीर्घ)cx->mpg_data_received,
			(दीर्घ दीर्घ)cx->vbi_data_inserted);
	वापस 0;
पूर्ण

अटल दीर्घ cx18_शेष(काष्ठा file *file, व्योम *fh, bool valid_prio,
			 अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा cx18 *cx = fh2id(fh)->cx;

	चयन (cmd) अणु
	हाल VIDIOC_INT_RESET: अणु
		u32 val = *(u32 *)arg;

		अगर ((val == 0) || (val & 0x01))
			cx18_call_hw(cx, CX18_HW_GPIO_RESET_CTRL, core, reset,
				     (u32) CX18_GPIO_RESET_Z8F0811);
		अवरोध;
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops cx18_ioctl_ops = अणु
	.vidioc_querycap                = cx18_querycap,
	.vidioc_s_audio                 = cx18_s_audio,
	.vidioc_g_audio                 = cx18_g_audio,
	.vidioc_क्रमागतaudio               = cx18_क्रमागतaudio,
	.vidioc_क्रमागत_input              = cx18_क्रमागत_input,
	.vidioc_g_pixelaspect           = cx18_g_pixelaspect,
	.vidioc_g_selection             = cx18_g_selection,
	.vidioc_g_input                 = cx18_g_input,
	.vidioc_s_input                 = cx18_s_input,
	.vidioc_g_frequency             = cx18_g_frequency,
	.vidioc_s_frequency             = cx18_s_frequency,
	.vidioc_s_tuner                 = cx18_s_tuner,
	.vidioc_g_tuner                 = cx18_g_tuner,
	.vidioc_g_enc_index             = cx18_g_enc_index,
	.vidioc_g_std                   = cx18_g_std,
	.vidioc_s_std                   = cx18_s_std,
	.vidioc_log_status              = cx18_log_status,
	.vidioc_क्रमागत_fmt_vid_cap        = cx18_क्रमागत_fmt_vid_cap,
	.vidioc_encoder_cmd             = cx18_encoder_cmd,
	.vidioc_try_encoder_cmd         = cx18_try_encoder_cmd,
	.vidioc_g_fmt_vid_cap           = cx18_g_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap           = cx18_g_fmt_vbi_cap,
	.vidioc_g_fmt_sliced_vbi_cap    = cx18_g_fmt_sliced_vbi_cap,
	.vidioc_s_fmt_vid_cap           = cx18_s_fmt_vid_cap,
	.vidioc_s_fmt_vbi_cap           = cx18_s_fmt_vbi_cap,
	.vidioc_s_fmt_sliced_vbi_cap    = cx18_s_fmt_sliced_vbi_cap,
	.vidioc_try_fmt_vid_cap         = cx18_try_fmt_vid_cap,
	.vidioc_try_fmt_vbi_cap         = cx18_try_fmt_vbi_cap,
	.vidioc_try_fmt_sliced_vbi_cap  = cx18_try_fmt_sliced_vbi_cap,
	.vidioc_g_sliced_vbi_cap        = cx18_g_sliced_vbi_cap,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर              = cx18_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर              = cx18_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_शेष                 = cx18_शेष,
	.vidioc_streamon                = cx18_streamon,
	.vidioc_streamoff               = cx18_streamoff,
	.vidioc_reqbufs                 = cx18_reqbufs,
	.vidioc_querybuf                = cx18_querybuf,
	.vidioc_qbuf                    = cx18_qbuf,
	.vidioc_dqbuf                   = cx18_dqbuf,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

व्योम cx18_set_funcs(काष्ठा video_device *vdev)
अणु
	vdev->ioctl_ops = &cx18_ioctl_ops;
पूर्ण
