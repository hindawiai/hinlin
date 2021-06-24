<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "hfi_venus_io.h"
#समावेश "hfi_parser.h"
#समावेश "core.h"
#समावेश "helpers.h"
#समावेश "venc.h"
#समावेश "pm_helpers.h"

#घोषणा NUM_B_FRAMES_MAX	4

/*
 * Three resons to keep MPLANE क्रमmats (despite that the number of planes
 * currently is one):
 * - the MPLANE क्रमmats allow only one plane to be used
 * - the करोwnstream driver use MPLANE क्रमmats too
 * - future firmware versions could add support क्रम >1 planes
 */
अटल स्थिर काष्ठा venus_क्रमmat venc_क्रमmats[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_NV12,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG4,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H263,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_VP8,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_HEVC,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा venus_क्रमmat *
find_क्रमmat(काष्ठा venus_inst *inst, u32 pixfmt, u32 type)
अणु
	स्थिर काष्ठा venus_क्रमmat *fmt = venc_क्रमmats;
	अचिन्हित पूर्णांक size = ARRAY_SIZE(venc_क्रमmats);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (fmt[i].pixfmt == pixfmt)
			अवरोध;
	पूर्ण

	अगर (i == size || fmt[i].type != type)
		वापस शून्य;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    !venus_helper_check_codec(inst, fmt[i].pixfmt))
		वापस शून्य;

	वापस &fmt[i];
पूर्ण

अटल स्थिर काष्ठा venus_क्रमmat *
find_क्रमmat_by_index(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक index, u32 type)
अणु
	स्थिर काष्ठा venus_क्रमmat *fmt = venc_क्रमmats;
	अचिन्हित पूर्णांक size = ARRAY_SIZE(venc_क्रमmats);
	अचिन्हित पूर्णांक i, k = 0;

	अगर (index > size)
		वापस शून्य;

	क्रम (i = 0; i < size; i++) अणु
		bool valid;

		अगर (fmt[i].type != type)
			जारी;
		valid = type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
			venus_helper_check_codec(inst, fmt[i].pixfmt);
		अगर (k == index && valid)
			अवरोध;
		अगर (valid)
			k++;
	पूर्ण

	अगर (i == size)
		वापस शून्य;

	वापस &fmt[i];
पूर्ण

अटल पूर्णांक venc_v4l2_to_hfi(पूर्णांक id, पूर्णांक value)
अणु
	चयन (id) अणु
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		चयन (value) अणु
		हाल V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC:
		शेष:
			वापस HFI_H264_ENTROPY_CAVLC;
		हाल V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC:
			वापस HFI_H264_ENTROPY_CABAC;
		पूर्ण
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		चयन (value) अणु
		हाल V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED:
		शेष:
			वापस HFI_H264_DB_MODE_ALL_BOUNDARY;
		हाल V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED:
			वापस HFI_H264_DB_MODE_DISABLE;
		हाल V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY:
			वापस HFI_H264_DB_MODE_SKIP_SLICE_BOUNDARY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
venc_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "qcom-venus", माप(cap->driver));
	strscpy(cap->card, "Qualcomm Venus video encoder", माप(cap->card));
	strscpy(cap->bus_info, "platform:qcom-venus", माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल पूर्णांक venc_क्रमागत_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt;

	fmt = find_क्रमmat_by_index(inst, f->index, f->type);

	स_रखो(f->reserved, 0, माप(f->reserved));

	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->pixfmt;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा venus_क्रमmat *
venc_try_fmt_common(काष्ठा venus_inst *inst, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *pfmt = pixmp->plane_fmt;
	स्थिर काष्ठा venus_क्रमmat *fmt;
	u32 sizeimage;

	स_रखो(pfmt[0].reserved, 0, माप(pfmt[0].reserved));
	स_रखो(pixmp->reserved, 0, माप(pixmp->reserved));

	fmt = find_क्रमmat(inst, pixmp->pixelक्रमmat, f->type);
	अगर (!fmt) अणु
		अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
			pixmp->pixelक्रमmat = V4L2_PIX_FMT_H264;
		अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
			pixmp->pixelक्रमmat = V4L2_PIX_FMT_NV12;
		अन्यथा
			वापस शून्य;
		fmt = find_क्रमmat(inst, pixmp->pixelक्रमmat, f->type);
	पूर्ण

	pixmp->width = clamp(pixmp->width, frame_width_min(inst),
			     frame_width_max(inst));
	pixmp->height = clamp(pixmp->height, frame_height_min(inst),
			      frame_height_max(inst));

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		pixmp->width = ALIGN(pixmp->width, 128);
		pixmp->height = ALIGN(pixmp->height, 32);
	पूर्ण

	pixmp->width = ALIGN(pixmp->width, 2);
	pixmp->height = ALIGN(pixmp->height, 2);

	अगर (pixmp->field == V4L2_FIELD_ANY)
		pixmp->field = V4L2_FIELD_NONE;
	pixmp->num_planes = fmt->num_planes;
	pixmp->flags = 0;

	sizeimage = venus_helper_get_framesz(pixmp->pixelक्रमmat,
					     pixmp->width,
					     pixmp->height);
	pfmt[0].sizeimage = max(ALIGN(pfmt[0].sizeimage, SZ_4K), sizeimage);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		pfmt[0].bytesperline = ALIGN(pixmp->width, 128);
	अन्यथा
		pfmt[0].bytesperline = 0;

	वापस fmt;
पूर्ण

अटल पूर्णांक venc_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	venc_try_fmt_common(inst, f);

	वापस 0;
पूर्ण

अटल पूर्णांक venc_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	काष्ठा v4l2_pix_क्रमmat_mplane orig_pixmp;
	स्थिर काष्ठा venus_क्रमmat *fmt;
	काष्ठा v4l2_क्रमmat क्रमmat;
	u32 pixfmt_out = 0, pixfmt_cap = 0;
	काष्ठा vb2_queue *q;

	q = v4l2_m2m_get_vq(inst->m2m_ctx, f->type);
	अगर (!q)
		वापस -EINVAL;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	orig_pixmp = *pixmp;

	fmt = venc_try_fmt_common(inst, f);
	अगर (!fmt)
		वापस -EINVAL;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		pixfmt_out = pixmp->pixelक्रमmat;
		pixfmt_cap = inst->fmt_cap->pixfmt;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		pixfmt_cap = pixmp->pixelक्रमmat;
		pixfmt_out = inst->fmt_out->pixfmt;
	पूर्ण

	स_रखो(&क्रमmat, 0, माप(क्रमmat));

	क्रमmat.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	क्रमmat.fmt.pix_mp.pixelक्रमmat = pixfmt_out;
	क्रमmat.fmt.pix_mp.width = orig_pixmp.width;
	क्रमmat.fmt.pix_mp.height = orig_pixmp.height;
	venc_try_fmt_common(inst, &क्रमmat);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		inst->out_width = क्रमmat.fmt.pix_mp.width;
		inst->out_height = क्रमmat.fmt.pix_mp.height;
		inst->colorspace = pixmp->colorspace;
		inst->ycbcr_enc = pixmp->ycbcr_enc;
		inst->quantization = pixmp->quantization;
		inst->xfer_func = pixmp->xfer_func;
	पूर्ण

	स_रखो(&क्रमmat, 0, माप(क्रमmat));

	क्रमmat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	क्रमmat.fmt.pix_mp.pixelक्रमmat = pixfmt_cap;
	क्रमmat.fmt.pix_mp.width = orig_pixmp.width;
	क्रमmat.fmt.pix_mp.height = orig_pixmp.height;
	venc_try_fmt_common(inst, &क्रमmat);

	inst->width = क्रमmat.fmt.pix_mp.width;
	inst->height = क्रमmat.fmt.pix_mp.height;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->fmt_out = fmt;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		inst->fmt_cap = fmt;
		inst->output_buf_size = pixmp->plane_fmt[0].sizeimage;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक venc_g_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		fmt = inst->fmt_cap;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt = inst->fmt_out;
	अन्यथा
		वापस -EINVAL;

	pixmp->pixelक्रमmat = fmt->pixfmt;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		pixmp->width = inst->width;
		pixmp->height = inst->height;
		pixmp->colorspace = inst->colorspace;
		pixmp->ycbcr_enc = inst->ycbcr_enc;
		pixmp->quantization = inst->quantization;
		pixmp->xfer_func = inst->xfer_func;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		pixmp->width = inst->out_width;
		pixmp->height = inst->out_height;
	पूर्ण

	venc_try_fmt_common(inst, f);

	वापस 0;
पूर्ण

अटल पूर्णांक
venc_g_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		s->r.width = inst->out_width;
		s->r.height = inst->out_height;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		s->r.width = inst->width;
		s->r.height = inst->height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	s->r.top = 0;
	s->r.left = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
venc_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	अगर (s->r.width > inst->out_width ||
	    s->r.height > inst->out_height)
		वापस -EINVAL;

	s->r.width = ALIGN(s->r.width, 2);
	s->r.height = ALIGN(s->r.height, 2);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		s->r.top = 0;
		s->r.left = 0;
		inst->width = s->r.width;
		inst->height = s->r.height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक venc_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	काष्ठा v4l2_outputparm *out = &a->parm.output;
	काष्ठा v4l2_fract *समयperframe = &out->समयperframe;
	u64 us_per_frame, fps;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस -EINVAL;

	स_रखो(out->reserved, 0, माप(out->reserved));

	अगर (!समयperframe->denominator)
		समयperframe->denominator = inst->समयperframe.denominator;
	अगर (!समयperframe->numerator)
		समयperframe->numerator = inst->समयperframe.numerator;

	out->capability = V4L2_CAP_TIMEPERFRAME;

	us_per_frame = समयperframe->numerator * (u64)USEC_PER_SEC;
	करो_भाग(us_per_frame, समयperframe->denominator);

	अगर (!us_per_frame)
		वापस -EINVAL;

	fps = (u64)USEC_PER_SEC;
	करो_भाग(fps, us_per_frame);

	inst->समयperframe = *समयperframe;
	inst->fps = fps;

	वापस 0;
पूर्ण

अटल पूर्णांक venc_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस -EINVAL;

	a->parm.output.capability |= V4L2_CAP_TIMEPERFRAME;
	a->parm.output.समयperframe = inst->समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक venc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;

	fmt = find_क्रमmat(inst, fsize->pixel_क्रमmat,
			  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	अगर (!fmt) अणु
		fmt = find_क्रमmat(inst, fsize->pixel_क्रमmat,
				  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		अगर (!fmt)
			वापस -EINVAL;
	पूर्ण

	अगर (fsize->index)
		वापस -EINVAL;

	fsize->stepwise.min_width = frame_width_min(inst);
	fsize->stepwise.max_width = frame_width_max(inst);
	fsize->stepwise.step_width = frame_width_step(inst);
	fsize->stepwise.min_height = frame_height_min(inst);
	fsize->stepwise.max_height = frame_height_max(inst);
	fsize->stepwise.step_height = frame_height_step(inst);

	वापस 0;
पूर्ण

अटल पूर्णांक venc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt;
	अचिन्हित पूर्णांक framerate_factor = 1;

	fival->type = V4L2_FRMIVAL_TYPE_STEPWISE;

	fmt = find_क्रमmat(inst, fival->pixel_क्रमmat,
			  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	अगर (!fmt) अणु
		fmt = find_क्रमmat(inst, fival->pixel_क्रमmat,
				  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		अगर (!fmt)
			वापस -EINVAL;
	पूर्ण

	अगर (fival->index)
		वापस -EINVAL;

	अगर (!fival->width || !fival->height)
		वापस -EINVAL;

	अगर (fival->width > frame_width_max(inst) ||
	    fival->width < frame_width_min(inst) ||
	    fival->height > frame_height_max(inst) ||
	    fival->height < frame_height_min(inst))
		वापस -EINVAL;

	अगर (IS_V1(inst->core)) अणु
		/* framerate is reported in 1/65535 fps unit */
		framerate_factor = (1 << 16);
	पूर्ण

	fival->stepwise.min.numerator = 1;
	fival->stepwise.min.denominator = frate_max(inst) / framerate_factor;
	fival->stepwise.max.numerator = 1;
	fival->stepwise.max.denominator = frate_min(inst) / framerate_factor;
	fival->stepwise.step.numerator = 1;
	fival->stepwise.step.denominator = frate_max(inst) / framerate_factor;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops venc_ioctl_ops = अणु
	.vidioc_querycap = venc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = venc_क्रमागत_fmt,
	.vidioc_क्रमागत_fmt_vid_out = venc_क्रमागत_fmt,
	.vidioc_s_fmt_vid_cap_mplane = venc_s_fmt,
	.vidioc_s_fmt_vid_out_mplane = venc_s_fmt,
	.vidioc_g_fmt_vid_cap_mplane = venc_g_fmt,
	.vidioc_g_fmt_vid_out_mplane = venc_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane = venc_try_fmt,
	.vidioc_try_fmt_vid_out_mplane = venc_try_fmt,
	.vidioc_g_selection = venc_g_selection,
	.vidioc_s_selection = venc_s_selection,
	.vidioc_reqbufs = v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf = v4l2_m2m_ioctl_querybuf,
	.vidioc_create_bufs = v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf = v4l2_m2m_ioctl_prepare_buf,
	.vidioc_qbuf = v4l2_m2m_ioctl_qbuf,
	.vidioc_expbuf = v4l2_m2m_ioctl_expbuf,
	.vidioc_dqbuf = v4l2_m2m_ioctl_dqbuf,
	.vidioc_streamon = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff = v4l2_m2m_ioctl_streamoff,
	.vidioc_s_parm = venc_s_parm,
	.vidioc_g_parm = venc_g_parm,
	.vidioc_क्रमागत_framesizes = venc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = venc_क्रमागत_frameपूर्णांकervals,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक venc_set_properties(काष्ठा venus_inst *inst)
अणु
	काष्ठा venc_controls *ctr = &inst->controls.enc;
	काष्ठा hfi_पूर्णांकra_period पूर्णांकra_period;
	काष्ठा hfi_framerate frate;
	काष्ठा hfi_bitrate brate;
	काष्ठा hfi_idr_period idrp;
	काष्ठा hfi_quantization quant;
	काष्ठा hfi_quantization_range quant_range;
	काष्ठा hfi_enable en;
	काष्ठा hfi_ltr_mode ltr_mode;
	u32 ptype, rate_control, bitrate;
	u32 profile, level;
	पूर्णांक ret;

	ret = venus_helper_set_work_mode(inst);
	अगर (ret)
		वापस ret;

	ptype = HFI_PROPERTY_CONFIG_FRAME_RATE;
	frate.buffer_type = HFI_BUFFER_OUTPUT;
	frate.framerate = inst->fps * (1 << 16);

	ret = hfi_session_set_property(inst, ptype, &frate);
	अगर (ret)
		वापस ret;

	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_H264) अणु
		काष्ठा hfi_h264_vui_timing_info info;
		काष्ठा hfi_h264_entropy_control entropy;
		काष्ठा hfi_h264_db_control deblock;

		ptype = HFI_PROPERTY_PARAM_VENC_H264_VUI_TIMING_INFO;
		info.enable = 1;
		info.fixed_framerate = 1;
		info.समय_scale = NSEC_PER_SEC;

		ret = hfi_session_set_property(inst, ptype, &info);
		अगर (ret)
			वापस ret;

		ptype = HFI_PROPERTY_PARAM_VENC_H264_ENTROPY_CONTROL;
		entropy.entropy_mode = venc_v4l2_to_hfi(
					  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE,
					  ctr->h264_entropy_mode);
		entropy.cabac_model = HFI_H264_CABAC_MODEL_0;

		ret = hfi_session_set_property(inst, ptype, &entropy);
		अगर (ret)
			वापस ret;

		ptype = HFI_PROPERTY_PARAM_VENC_H264_DEBLOCK_CONTROL;
		deblock.mode = venc_v4l2_to_hfi(
				      V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE,
				      ctr->h264_loop_filter_mode);
		deblock.slice_alpha_offset = ctr->h264_loop_filter_alpha;
		deblock.slice_beta_offset = ctr->h264_loop_filter_beta;

		ret = hfi_session_set_property(inst, ptype, &deblock);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_H264 ||
	    inst->fmt_cap->pixfmt == V4L2_PIX_FMT_HEVC) अणु
		/* IDR periodicity, n:
		 * n = 0 - only the first I-frame is IDR frame
		 * n = 1 - all I-frames will be IDR frames
		 * n > 1 - every n-th I-frame will be IDR frame
		 */
		ptype = HFI_PROPERTY_CONFIG_VENC_IDR_PERIOD;
		idrp.idr_period = 0;
		ret = hfi_session_set_property(inst, ptype, &idrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_HEVC) अणु
		काष्ठा hfi_hdr10_pq_sei hdr10;
		अचिन्हित पूर्णांक c;

		ptype = HFI_PROPERTY_PARAM_VENC_HDR10_PQ_SEI;

		क्रम (c = 0; c < 3; c++) अणु
			hdr10.mastering.display_primaries_x[c] =
				ctr->mastering.display_primaries_x[c];
			hdr10.mastering.display_primaries_y[c] =
				ctr->mastering.display_primaries_y[c];
		पूर्ण

		hdr10.mastering.white_poपूर्णांक_x = ctr->mastering.white_poपूर्णांक_x;
		hdr10.mastering.white_poपूर्णांक_y = ctr->mastering.white_poपूर्णांक_y;
		hdr10.mastering.max_display_mastering_luminance =
			ctr->mastering.max_display_mastering_luminance;
		hdr10.mastering.min_display_mastering_luminance =
			ctr->mastering.min_display_mastering_luminance;

		hdr10.cll.max_content_light = ctr->cll.max_content_light_level;
		hdr10.cll.max_pic_average_light =
			ctr->cll.max_pic_average_light_level;

		ret = hfi_session_set_property(inst, ptype, &hdr10);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ctr->num_b_frames) अणु
		u32 max_num_b_frames = NUM_B_FRAMES_MAX;

		ptype = HFI_PROPERTY_PARAM_VENC_MAX_NUM_B_FRAMES;
		ret = hfi_session_set_property(inst, ptype, &max_num_b_frames);
		अगर (ret)
			वापस ret;
	पूर्ण

	ptype = HFI_PROPERTY_CONFIG_VENC_INTRA_PERIOD;
	पूर्णांकra_period.pframes = ctr->num_p_frames;
	पूर्णांकra_period.bframes = ctr->num_b_frames;

	ret = hfi_session_set_property(inst, ptype, &पूर्णांकra_period);
	अगर (ret)
		वापस ret;

	अगर (!ctr->rc_enable)
		rate_control = HFI_RATE_CONTROL_OFF;
	अन्यथा अगर (ctr->bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR)
		rate_control = ctr->frame_skip_mode ? HFI_RATE_CONTROL_VBR_VFR :
						      HFI_RATE_CONTROL_VBR_CFR;
	अन्यथा अगर (ctr->bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
		rate_control = ctr->frame_skip_mode ? HFI_RATE_CONTROL_CBR_VFR :
						      HFI_RATE_CONTROL_CBR_CFR;
	अन्यथा अगर (ctr->bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_CQ)
		rate_control = HFI_RATE_CONTROL_CQ;

	ptype = HFI_PROPERTY_PARAM_VENC_RATE_CONTROL;
	ret = hfi_session_set_property(inst, ptype, &rate_control);
	अगर (ret)
		वापस ret;

	अगर (rate_control == HFI_RATE_CONTROL_CQ && ctr->स्थिर_quality) अणु
		काष्ठा hfi_heic_frame_quality quality = अणुपूर्ण;

		ptype = HFI_PROPERTY_CONFIG_HEIC_FRAME_QUALITY;
		quality.frame_quality = ctr->स्थिर_quality;
		ret = hfi_session_set_property(inst, ptype, &quality);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!ctr->bitrate)
		bitrate = 64000;
	अन्यथा
		bitrate = ctr->bitrate;

	ptype = HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE;
	brate.bitrate = bitrate;
	brate.layer_id = 0;

	ret = hfi_session_set_property(inst, ptype, &brate);
	अगर (ret)
		वापस ret;

	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_H264 ||
	    inst->fmt_cap->pixfmt == V4L2_PIX_FMT_HEVC) अणु
		ptype = HFI_PROPERTY_CONFIG_VENC_SYNC_FRAME_SEQUENCE_HEADER;
		अगर (ctr->header_mode == V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE)
			en.enable = 0;
		अन्यथा
			en.enable = 1;

		ret = hfi_session_set_property(inst, ptype, &en);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!ctr->bitrate_peak)
		bitrate *= 2;
	अन्यथा
		bitrate = ctr->bitrate_peak;

	ptype = HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE;
	brate.bitrate = bitrate;
	brate.layer_id = 0;

	ret = hfi_session_set_property(inst, ptype, &brate);
	अगर (ret)
		वापस ret;

	ptype = HFI_PROPERTY_PARAM_VENC_SESSION_QP;
	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_HEVC) अणु
		quant.qp_i = ctr->hevc_i_qp;
		quant.qp_p = ctr->hevc_p_qp;
		quant.qp_b = ctr->hevc_b_qp;
	पूर्ण अन्यथा अणु
		quant.qp_i = ctr->h264_i_qp;
		quant.qp_p = ctr->h264_p_qp;
		quant.qp_b = ctr->h264_b_qp;
	पूर्ण
	quant.layer_id = 0;
	ret = hfi_session_set_property(inst, ptype, &quant);
	अगर (ret)
		वापस ret;

	ptype = HFI_PROPERTY_PARAM_VENC_SESSION_QP_RANGE;
	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_HEVC) अणु
		quant_range.min_qp = ctr->hevc_min_qp;
		quant_range.max_qp = ctr->hevc_max_qp;
	पूर्ण अन्यथा अणु
		quant_range.min_qp = ctr->h264_min_qp;
		quant_range.max_qp = ctr->h264_max_qp;
	पूर्ण
	quant_range.layer_id = 0;
	ret = hfi_session_set_property(inst, ptype, &quant_range);
	अगर (ret)
		वापस ret;

	ptype = HFI_PROPERTY_PARAM_VENC_LTRMODE;
	ltr_mode.ltr_count = ctr->ltr_count;
	ltr_mode.ltr_mode = HFI_LTR_MODE_MANUAL;
	ltr_mode.trust_mode = 1;
	ret = hfi_session_set_property(inst, ptype, &ltr_mode);
	अगर (ret)
		वापस ret;

	चयन (inst->hfi_codec) अणु
	हाल HFI_VIDEO_CODEC_H264:
		profile = ctr->profile.h264;
		level = ctr->level.h264;
		अवरोध;
	हाल HFI_VIDEO_CODEC_MPEG4:
		profile = ctr->profile.mpeg4;
		level = ctr->level.mpeg4;
		अवरोध;
	हाल HFI_VIDEO_CODEC_VP8:
		profile = ctr->profile.vp8;
		level = 0;
		अवरोध;
	हाल HFI_VIDEO_CODEC_VP9:
		profile = ctr->profile.vp9;
		level = ctr->level.vp9;
		अवरोध;
	हाल HFI_VIDEO_CODEC_HEVC:
		profile = ctr->profile.hevc;
		level = ctr->level.hevc;
		अवरोध;
	हाल HFI_VIDEO_CODEC_MPEG2:
	शेष:
		profile = 0;
		level = 0;
		अवरोध;
	पूर्ण

	ret = venus_helper_set_profile_level(inst, profile, level);
	अगर (ret)
		वापस ret;

	अगर (inst->fmt_cap->pixfmt == V4L2_PIX_FMT_H264 ||
	    inst->fmt_cap->pixfmt == V4L2_PIX_FMT_HEVC) अणु
		काष्ठा hfi_enable en = अणुपूर्ण;

		ptype = HFI_PROPERTY_PARAM_VENC_H264_GENERATE_AUDNAL;

		अगर (ctr->aud_enable)
			en.enable = 1;

		ret = hfi_session_set_property(inst, ptype, &en);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक venc_init_session(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	ret = venus_helper_session_init(inst);
	अगर (ret == -EALREADY)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	ret = venus_helper_set_stride(inst, inst->out_width,
				      inst->out_height);
	अगर (ret)
		जाओ deinit;

	ret = venus_helper_set_input_resolution(inst, inst->width,
						inst->height);
	अगर (ret)
		जाओ deinit;

	ret = venus_helper_set_output_resolution(inst, inst->width,
						 inst->height,
						 HFI_BUFFER_OUTPUT);
	अगर (ret)
		जाओ deinit;

	ret = venus_helper_set_color_क्रमmat(inst, inst->fmt_out->pixfmt);
	अगर (ret)
		जाओ deinit;

	ret = venc_set_properties(inst);
	अगर (ret)
		जाओ deinit;

	वापस 0;
deinit:
	hfi_session_deinit(inst);
	वापस ret;
पूर्ण

अटल पूर्णांक venc_out_num_buffers(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक *num)
अणु
	काष्ठा hfi_buffer_requirements bufreq;
	पूर्णांक ret;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_INPUT, &bufreq);
	अगर (ret)
		वापस ret;

	*num = bufreq.count_actual;

	वापस 0;
पूर्ण

अटल पूर्णांक venc_queue_setup(काष्ठा vb2_queue *q,
			    अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			    अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(q);
	अचिन्हित पूर्णांक num, min = 4;
	पूर्णांक ret;

	अगर (*num_planes) अणु
		अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
		    *num_planes != inst->fmt_out->num_planes)
			वापस -EINVAL;

		अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
		    *num_planes != inst->fmt_cap->num_planes)
			वापस -EINVAL;

		अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
		    sizes[0] < inst->input_buf_size)
			वापस -EINVAL;

		अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
		    sizes[0] < inst->output_buf_size)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	mutex_lock(&inst->lock);
	ret = venc_init_session(inst);
	mutex_unlock(&inst->lock);

	अगर (ret)
		वापस ret;

	चयन (q->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		*num_planes = inst->fmt_out->num_planes;

		ret = venc_out_num_buffers(inst, &num);
		अगर (ret)
			अवरोध;

		num = max(num, min);
		*num_buffers = max(*num_buffers, num);
		inst->num_input_bufs = *num_buffers;

		sizes[0] = venus_helper_get_framesz(inst->fmt_out->pixfmt,
						    inst->out_width,
						    inst->out_height);
		inst->input_buf_size = sizes[0];
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		*num_planes = inst->fmt_cap->num_planes;
		*num_buffers = max(*num_buffers, min);
		inst->num_output_bufs = *num_buffers;
		sizes[0] = venus_helper_get_framesz(inst->fmt_cap->pixfmt,
						    inst->width,
						    inst->height);
		sizes[0] = max(sizes[0], inst->output_buf_size);
		inst->output_buf_size = sizes[0];
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक venc_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);

	inst->buf_count++;

	वापस venus_helper_vb2_buf_init(vb);
पूर्ण

अटल व्योम venc_release_session(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	mutex_lock(&inst->lock);

	ret = hfi_session_deinit(inst);
	अगर (ret || inst->session_error)
		hfi_session_पात(inst);

	mutex_unlock(&inst->lock);

	venus_pm_load_scale(inst);
	INIT_LIST_HEAD(&inst->रेजिस्टरedbufs);
	venus_pm_release_core(inst);
पूर्ण

अटल व्योम venc_buf_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा venus_buffer *buf = to_venus_buffer(vbuf);

	mutex_lock(&inst->lock);
	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		अगर (!list_empty(&inst->रेजिस्टरedbufs))
			list_del_init(&buf->reg_list);
	mutex_unlock(&inst->lock);

	inst->buf_count--;
	अगर (!inst->buf_count)
		venc_release_session(inst);
पूर्ण

अटल पूर्णांक venc_verअगरy_conf(काष्ठा venus_inst *inst)
अणु
	क्रमागत hfi_version ver = inst->core->res->hfi_version;
	काष्ठा hfi_buffer_requirements bufreq;
	पूर्णांक ret;

	अगर (!inst->num_input_bufs || !inst->num_output_bufs)
		वापस -EINVAL;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT, &bufreq);
	अगर (ret)
		वापस ret;

	अगर (inst->num_output_bufs < bufreq.count_actual ||
	    inst->num_output_bufs < HFI_BUFREQ_COUNT_MIN(&bufreq, ver))
		वापस -EINVAL;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_INPUT, &bufreq);
	अगर (ret)
		वापस ret;

	अगर (inst->num_input_bufs < bufreq.count_actual ||
	    inst->num_input_bufs < HFI_BUFREQ_COUNT_MIN(&bufreq, ver))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक venc_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(q);
	पूर्णांक ret;

	mutex_lock(&inst->lock);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 1;
	अन्यथा
		inst->streamon_cap = 1;

	अगर (!(inst->streamon_out & inst->streamon_cap)) अणु
		mutex_unlock(&inst->lock);
		वापस 0;
	पूर्ण

	venus_helper_init_instance(inst);

	inst->sequence_cap = 0;
	inst->sequence_out = 0;

	ret = venus_pm_acquire_core(inst);
	अगर (ret)
		जाओ error;

	ret = venc_set_properties(inst);
	अगर (ret)
		जाओ error;

	ret = venc_verअगरy_conf(inst);
	अगर (ret)
		जाओ error;

	ret = venus_helper_set_num_bufs(inst, inst->num_input_bufs,
					inst->num_output_bufs, 0);
	अगर (ret)
		जाओ error;

	ret = venus_helper_vb2_start_streaming(inst);
	अगर (ret)
		जाओ error;

	mutex_unlock(&inst->lock);

	वापस 0;

error:
	venus_helper_buffers_करोne(inst, q->type, VB2_BUF_STATE_QUEUED);
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 0;
	अन्यथा
		inst->streamon_cap = 0;
	mutex_unlock(&inst->lock);
	वापस ret;
पूर्ण

अटल व्योम venc_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);

	mutex_lock(&inst->lock);
	venus_helper_vb2_buf_queue(vb);
	mutex_unlock(&inst->lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops venc_vb2_ops = अणु
	.queue_setup = venc_queue_setup,
	.buf_init = venc_buf_init,
	.buf_cleanup = venc_buf_cleanup,
	.buf_prepare = venus_helper_vb2_buf_prepare,
	.start_streaming = venc_start_streaming,
	.stop_streaming = venus_helper_vb2_stop_streaming,
	.buf_queue = venc_vb2_buf_queue,
पूर्ण;

अटल व्योम venc_buf_करोne(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक buf_type,
			  u32 tag, u32 bytesused, u32 data_offset, u32 flags,
			  u32 hfi_flags, u64 बारtamp_us)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा vb2_buffer *vb;
	अचिन्हित पूर्णांक type;

	अगर (buf_type == HFI_BUFFER_INPUT)
		type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	अन्यथा
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;

	vbuf = venus_helper_find_buf(inst, type, tag);
	अगर (!vbuf)
		वापस;

	vbuf->flags = flags;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		vb = &vbuf->vb2_buf;
		vb2_set_plane_payload(vb, 0, bytesused + data_offset);
		vb->planes[0].data_offset = data_offset;
		vb->बारtamp = बारtamp_us * NSEC_PER_USEC;
		vbuf->sequence = inst->sequence_cap++;
	पूर्ण अन्यथा अणु
		vbuf->sequence = inst->sequence_out++;
	पूर्ण

	v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_DONE);
पूर्ण

अटल व्योम venc_event_notअगरy(काष्ठा venus_inst *inst, u32 event,
			      काष्ठा hfi_event_data *data)
अणु
	काष्ठा device *dev = inst->core->dev_enc;

	अगर (event == EVT_SESSION_ERROR) अणु
		inst->session_error = true;
		dev_err(dev, "enc: event session error %x\n", inst->error);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hfi_inst_ops venc_hfi_ops = अणु
	.buf_करोne = venc_buf_करोne,
	.event_notअगरy = venc_event_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops venc_m2m_ops = अणु
	.device_run = venus_helper_m2m_device_run,
	.job_पात = venus_helper_m2m_job_पात,
पूर्ण;

अटल पूर्णांक m2m_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा venus_inst *inst = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->ops = &venc_vb2_ops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->drv_priv = inst;
	src_vq->buf_काष्ठा_size = माप(काष्ठा venus_buffer);
	src_vq->allow_zero_bytesused = 1;
	src_vq->min_buffers_needed = 1;
	src_vq->dev = inst->core->dev;
	अगर (inst->core->res->hfi_version == HFI_VERSION_1XX)
		src_vq->bidirectional = 1;
	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->ops = &venc_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->drv_priv = inst;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा venus_buffer);
	dst_vq->allow_zero_bytesused = 1;
	dst_vq->min_buffers_needed = 1;
	dst_vq->dev = inst->core->dev;
	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल व्योम venc_inst_init(काष्ठा venus_inst *inst)
अणु
	inst->fmt_cap = &venc_क्रमmats[3];
	inst->fmt_out = &venc_क्रमmats[0];
	inst->width = 1280;
	inst->height = ALIGN(720, 32);
	inst->out_width = 1280;
	inst->out_height = 720;
	inst->fps = 15;
	inst->समयperframe.numerator = 1;
	inst->समयperframe.denominator = 15;
	inst->hfi_codec = HFI_VIDEO_CODEC_H264;
पूर्ण

अटल पूर्णांक venc_खोलो(काष्ठा file *file)
अणु
	काष्ठा venus_core *core = video_drvdata(file);
	काष्ठा venus_inst *inst;
	पूर्णांक ret;

	inst = kzalloc(माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&inst->dpbbufs);
	INIT_LIST_HEAD(&inst->रेजिस्टरedbufs);
	INIT_LIST_HEAD(&inst->पूर्णांकernalbufs);
	INIT_LIST_HEAD(&inst->list);
	mutex_init(&inst->lock);

	inst->core = core;
	inst->session_type = VIDC_SESSION_TYPE_ENC;
	inst->clk_data.core_id = VIDC_CORE_ID_DEFAULT;
	inst->core_acquired = false;

	venus_helper_init_instance(inst);

	ret = pm_runसमय_get_sync(core->dev_enc);
	अगर (ret < 0)
		जाओ err_put_sync;

	ret = venc_ctrl_init(inst);
	अगर (ret)
		जाओ err_put_sync;

	ret = hfi_session_create(inst, &venc_hfi_ops);
	अगर (ret)
		जाओ err_ctrl_deinit;

	venc_inst_init(inst);

	/*
	 * create m2m device क्रम every instance, the m2m context scheduling
	 * is made by firmware side so we करो not need to care about.
	 */
	inst->m2m_dev = v4l2_m2m_init(&venc_m2m_ops);
	अगर (IS_ERR(inst->m2m_dev)) अणु
		ret = PTR_ERR(inst->m2m_dev);
		जाओ err_session_destroy;
	पूर्ण

	inst->m2m_ctx = v4l2_m2m_ctx_init(inst->m2m_dev, inst, m2m_queue_init);
	अगर (IS_ERR(inst->m2m_ctx)) अणु
		ret = PTR_ERR(inst->m2m_ctx);
		जाओ err_m2m_release;
	पूर्ण

	v4l2_fh_init(&inst->fh, core->vdev_enc);

	inst->fh.ctrl_handler = &inst->ctrl_handler;
	v4l2_fh_add(&inst->fh);
	inst->fh.m2m_ctx = inst->m2m_ctx;
	file->निजी_data = &inst->fh;

	वापस 0;

err_m2m_release:
	v4l2_m2m_release(inst->m2m_dev);
err_session_destroy:
	hfi_session_destroy(inst);
err_ctrl_deinit:
	venc_ctrl_deinit(inst);
err_put_sync:
	pm_runसमय_put_sync(core->dev_enc);
	kमुक्त(inst);
	वापस ret;
पूर्ण

अटल पूर्णांक venc_बंद(काष्ठा file *file)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	v4l2_m2m_ctx_release(inst->m2m_ctx);
	v4l2_m2m_release(inst->m2m_dev);
	venc_ctrl_deinit(inst);
	hfi_session_destroy(inst);
	mutex_destroy(&inst->lock);
	v4l2_fh_del(&inst->fh);
	v4l2_fh_निकास(&inst->fh);

	pm_runसमय_put_sync(inst->core->dev_enc);

	kमुक्त(inst);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations venc_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = venc_खोलो,
	.release = venc_बंद,
	.unlocked_ioctl = video_ioctl2,
	.poll = v4l2_m2m_fop_poll,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा video_device *vdev;
	काष्ठा venus_core *core;
	पूर्णांक ret;

	अगर (!dev->parent)
		वापस -EPROBE_DEFER;

	core = dev_get_drvdata(dev->parent);
	अगर (!core)
		वापस -EPROBE_DEFER;

	platक्रमm_set_drvdata(pdev, core);

	अगर (core->pm_ops->venc_get) अणु
		ret = core->pm_ops->venc_get(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	vdev = video_device_alloc();
	अगर (!vdev)
		वापस -ENOMEM;

	strscpy(vdev->name, "qcom-venus-encoder", माप(vdev->name));
	vdev->release = video_device_release;
	vdev->fops = &venc_fops;
	vdev->ioctl_ops = &venc_ioctl_ops;
	vdev->vfl_dir = VFL_सूची_M2M;
	vdev->v4l2_dev = &core->v4l2_dev;
	vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ err_vdev_release;

	core->vdev_enc = vdev;
	core->dev_enc = dev;

	video_set_drvdata(vdev, core);
	pm_runसमय_enable(dev);

	वापस 0;

err_vdev_release:
	video_device_release(vdev);
	वापस ret;
पूर्ण

अटल पूर्णांक venc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(pdev->dev.parent);

	video_unरेजिस्टर_device(core->vdev_enc);
	pm_runसमय_disable(core->dev_enc);

	अगर (core->pm_ops->venc_put)
		core->pm_ops->venc_put(core->dev_enc);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक venc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret = 0;

	अगर (pm_ops->venc_घातer)
		ret = pm_ops->venc_घातer(dev, POWER_OFF);

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक venc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret = 0;

	अगर (pm_ops->venc_घातer)
		ret = pm_ops->venc_घातer(dev, POWER_ON);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops venc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(venc_runसमय_suspend, venc_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id venc_dt_match[] = अणु
	अणु .compatible = "venus-encoder" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, venc_dt_match);

अटल काष्ठा platक्रमm_driver qcom_venus_enc_driver = अणु
	.probe = venc_probe,
	.हटाओ = venc_हटाओ,
	.driver = अणु
		.name = "qcom-venus-encoder",
		.of_match_table = venc_dt_match,
		.pm = &venc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_venus_enc_driver);

MODULE_ALIAS("platform:qcom-venus-encoder");
MODULE_DESCRIPTION("Qualcomm Venus video encoder driver");
MODULE_LICENSE("GPL v2");
