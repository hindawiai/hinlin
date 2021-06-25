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
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "hfi_venus_io.h"
#समावेश "hfi_parser.h"
#समावेश "core.h"
#समावेश "helpers.h"
#समावेश "vdec.h"
#समावेश "pm_helpers.h"

/*
 * Three resons to keep MPLANE क्रमmats (despite that the number of planes
 * currently is one):
 * - the MPLANE क्रमmats allow only one plane to be used
 * - the करोwnstream driver use MPLANE क्रमmats too
 * - future firmware versions could add support क्रम >1 planes
 */
अटल स्थिर काष्ठा venus_क्रमmat vdec_क्रमmats[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_NV12,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG4,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG2,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H263,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_VC1_ANNEX_G,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_VC1_ANNEX_L,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_VP8,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_VP9,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_XVID,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_HEVC,
		.num_planes = 1,
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा venus_क्रमmat *
find_क्रमmat(काष्ठा venus_inst *inst, u32 pixfmt, u32 type)
अणु
	स्थिर काष्ठा venus_क्रमmat *fmt = vdec_क्रमmats;
	अचिन्हित पूर्णांक size = ARRAY_SIZE(vdec_क्रमmats);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (fmt[i].pixfmt == pixfmt)
			अवरोध;
	पूर्ण

	अगर (i == size || fmt[i].type != type)
		वापस शून्य;

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
	    !venus_helper_check_codec(inst, fmt[i].pixfmt))
		वापस शून्य;

	वापस &fmt[i];
पूर्ण

अटल स्थिर काष्ठा venus_क्रमmat *
find_क्रमmat_by_index(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक index, u32 type)
अणु
	स्थिर काष्ठा venus_क्रमmat *fmt = vdec_क्रमmats;
	अचिन्हित पूर्णांक size = ARRAY_SIZE(vdec_क्रमmats);
	अचिन्हित पूर्णांक i, k = 0;

	अगर (index > size)
		वापस शून्य;

	क्रम (i = 0; i < size; i++) अणु
		bool valid;

		अगर (fmt[i].type != type)
			जारी;
		valid = type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ||
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

अटल स्थिर काष्ठा venus_क्रमmat *
vdec_try_fmt_common(काष्ठा venus_inst *inst, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *pfmt = pixmp->plane_fmt;
	स्थिर काष्ठा venus_क्रमmat *fmt;
	u32 szimage;

	स_रखो(pfmt[0].reserved, 0, माप(pfmt[0].reserved));
	स_रखो(pixmp->reserved, 0, माप(pixmp->reserved));

	fmt = find_क्रमmat(inst, pixmp->pixelक्रमmat, f->type);
	अगर (!fmt) अणु
		अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
			pixmp->pixelक्रमmat = V4L2_PIX_FMT_NV12;
		अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
			pixmp->pixelक्रमmat = V4L2_PIX_FMT_H264;
		अन्यथा
			वापस शून्य;
		fmt = find_क्रमmat(inst, pixmp->pixelक्रमmat, f->type);
	पूर्ण

	pixmp->width = clamp(pixmp->width, frame_width_min(inst),
			     frame_width_max(inst));
	pixmp->height = clamp(pixmp->height, frame_height_min(inst),
			      frame_height_max(inst));

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		pixmp->height = ALIGN(pixmp->height, 32);

	अगर (pixmp->field == V4L2_FIELD_ANY)
		pixmp->field = V4L2_FIELD_NONE;
	pixmp->num_planes = fmt->num_planes;
	pixmp->flags = 0;

	szimage = venus_helper_get_framesz(pixmp->pixelक्रमmat, pixmp->width,
					   pixmp->height);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		pfmt[0].sizeimage = szimage;
		pfmt[0].bytesperline = ALIGN(pixmp->width, 128);
	पूर्ण अन्यथा अणु
		pfmt[0].sizeimage = clamp_t(u32, pfmt[0].sizeimage, 0, SZ_8M);
		pfmt[0].sizeimage = max(pfmt[0].sizeimage, szimage);
		pfmt[0].bytesperline = 0;
	पूर्ण

	वापस fmt;
पूर्ण

अटल पूर्णांक vdec_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	vdec_try_fmt_common(inst, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_check_src_change(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	अगर (inst->subscriptions & V4L2_EVENT_SOURCE_CHANGE &&
	    inst->codec_state == VENUS_DEC_STATE_INIT &&
	    !inst->reconfig)
		वापस -EINVAL;

	अगर (inst->subscriptions & V4L2_EVENT_SOURCE_CHANGE)
		वापस 0;

	/*
	 * The code snippet below is a workaround क्रम backward compatibility
	 * with applications which करोesn't support V4L2 events. It will be
	 * dropped in future once those applications are fixed.
	 */

	अगर (inst->codec_state != VENUS_DEC_STATE_INIT)
		जाओ करोne;

	ret = रुको_event_समयout(inst->reconf_रुको, inst->reconfig,
				 msecs_to_jअगरfies(100));
	अगर (!ret)
		वापस -EINVAL;

	अगर (!(inst->codec_state == VENUS_DEC_STATE_CAPTURE_SETUP) ||
	    !inst->reconfig)
		dev_dbg(inst->core->dev, VDBGH "wrong state\n");

करोne:
	वापस 0;
पूर्ण

अटल पूर्णांक vdec_g_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt = शून्य;
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	पूर्णांक ret;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		fmt = inst->fmt_cap;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt = inst->fmt_out;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		ret = vdec_check_src_change(inst);
		अगर (ret)
			वापस ret;
	पूर्ण

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

	vdec_try_fmt_common(inst, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
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

	fmt = vdec_try_fmt_common(inst, f);

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
	vdec_try_fmt_common(inst, &क्रमmat);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		inst->out_width = क्रमmat.fmt.pix_mp.width;
		inst->out_height = क्रमmat.fmt.pix_mp.height;
		inst->colorspace = pixmp->colorspace;
		inst->ycbcr_enc = pixmp->ycbcr_enc;
		inst->quantization = pixmp->quantization;
		inst->xfer_func = pixmp->xfer_func;
		inst->input_buf_size = pixmp->plane_fmt[0].sizeimage;
	पूर्ण

	स_रखो(&क्रमmat, 0, माप(क्रमmat));

	क्रमmat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	क्रमmat.fmt.pix_mp.pixelक्रमmat = pixfmt_cap;
	क्रमmat.fmt.pix_mp.width = orig_pixmp.width;
	क्रमmat.fmt.pix_mp.height = orig_pixmp.height;
	vdec_try_fmt_common(inst, &क्रमmat);

	inst->width = क्रमmat.fmt.pix_mp.width;
	inst->height = क्रमmat.fmt.pix_mp.height;
	inst->crop.top = 0;
	inst->crop.left = 0;
	inst->crop.width = inst->width;
	inst->crop.height = inst->height;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->fmt_out = fmt;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		inst->fmt_cap = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक
vdec_g_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	s->r.top = 0;
	s->r.left = 0;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		s->r.width = inst->out_width;
		s->r.height = inst->out_height;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_PADDED:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		s->r.width = inst->width;
		s->r.height = inst->height;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		s->r = inst->crop;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vdec_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "qcom-venus", माप(cap->driver));
	strscpy(cap->card, "Qualcomm Venus video decoder", माप(cap->card));
	strscpy(cap->bus_info, "platform:qcom-venus", माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_क्रमागत_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt;

	स_रखो(f->reserved, 0, माप(f->reserved));

	fmt = find_क्रमmat_by_index(inst, f->index, f->type);
	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->pixfmt;
	f->flags = fmt->flags;

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	काष्ठा v4l2_captureparm *cap = &a->parm.capture;
	काष्ठा v4l2_fract *समयperframe = &cap->समयperframe;
	u64 us_per_frame, fps;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस -EINVAL;

	स_रखो(cap->reserved, 0, माप(cap->reserved));
	अगर (!समयperframe->denominator)
		समयperframe->denominator = inst->समयperframe.denominator;
	अगर (!समयperframe->numerator)
		समयperframe->numerator = inst->समयperframe.numerator;
	cap->पढ़ोbuffers = 0;
	cap->extendedmode = 0;
	cap->capability = V4L2_CAP_TIMEPERFRAME;
	us_per_frame = समयperframe->numerator * (u64)USEC_PER_SEC;
	करो_भाग(us_per_frame, समयperframe->denominator);

	अगर (!us_per_frame)
		वापस -EINVAL;

	fps = (u64)USEC_PER_SEC;
	करो_भाग(fps, us_per_frame);

	inst->fps = fps;
	inst->समयperframe = *समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	स्थिर काष्ठा venus_क्रमmat *fmt;

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

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;

	fsize->stepwise.min_width = frame_width_min(inst);
	fsize->stepwise.max_width = frame_width_max(inst);
	fsize->stepwise.step_width = frame_width_step(inst);
	fsize->stepwise.min_height = frame_height_min(inst);
	fsize->stepwise.max_height = frame_height_max(inst);
	fsize->stepwise.step_height = frame_height_step(inst);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	काष्ठा venus_inst *inst = container_of(fh, काष्ठा venus_inst, fh);
	पूर्णांक ret;

	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 2, शून्य);
	हाल V4L2_EVENT_SOURCE_CHANGE:
		ret = v4l2_src_change_event_subscribe(fh, sub);
		अगर (ret)
			वापस ret;
		inst->subscriptions |= V4L2_EVENT_SOURCE_CHANGE;
		वापस 0;
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
vdec_decoder_cmd(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_decoder_cmd *cmd)
अणु
	काष्ठा venus_inst *inst = to_inst(file);
	काष्ठा hfi_frame_data fdata = अणु0पूर्ण;
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_try_decoder_cmd(file, fh, cmd);
	अगर (ret)
		वापस ret;

	mutex_lock(&inst->lock);

	अगर (cmd->cmd == V4L2_DEC_CMD_STOP) अणु
		/*
		 * Implement V4L2_DEC_CMD_STOP by enqueue an empty buffer on
		 * decoder input to संकेत EOS.
		 */
		अगर (!(inst->streamon_out && inst->streamon_cap))
			जाओ unlock;

		fdata.buffer_type = HFI_BUFFER_INPUT;
		fdata.flags |= HFI_BUFFERFLAG_EOS;
		अगर (IS_V6(inst->core))
			fdata.device_addr = 0;
		अन्यथा
			fdata.device_addr = 0xdeadb000;

		ret = hfi_session_process_buf(inst, &fdata);

		अगर (!ret && inst->codec_state == VENUS_DEC_STATE_DECODING) अणु
			inst->codec_state = VENUS_DEC_STATE_DRAIN;
			inst->drain_active = true;
		पूर्ण
	पूर्ण

unlock:
	mutex_unlock(&inst->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops vdec_ioctl_ops = अणु
	.vidioc_querycap = vdec_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vdec_क्रमागत_fmt,
	.vidioc_क्रमागत_fmt_vid_out = vdec_क्रमागत_fmt,
	.vidioc_s_fmt_vid_cap_mplane = vdec_s_fmt,
	.vidioc_s_fmt_vid_out_mplane = vdec_s_fmt,
	.vidioc_g_fmt_vid_cap_mplane = vdec_g_fmt,
	.vidioc_g_fmt_vid_out_mplane = vdec_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane = vdec_try_fmt,
	.vidioc_try_fmt_vid_out_mplane = vdec_try_fmt,
	.vidioc_g_selection = vdec_g_selection,
	.vidioc_reqbufs = v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf = v4l2_m2m_ioctl_querybuf,
	.vidioc_create_bufs = v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf = v4l2_m2m_ioctl_prepare_buf,
	.vidioc_qbuf = v4l2_m2m_ioctl_qbuf,
	.vidioc_expbuf = v4l2_m2m_ioctl_expbuf,
	.vidioc_dqbuf = v4l2_m2m_ioctl_dqbuf,
	.vidioc_streamon = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff = v4l2_m2m_ioctl_streamoff,
	.vidioc_s_parm = vdec_s_parm,
	.vidioc_क्रमागत_framesizes = vdec_क्रमागत_framesizes,
	.vidioc_subscribe_event = vdec_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_try_decoder_cmd = v4l2_m2m_ioctl_try_decoder_cmd,
	.vidioc_decoder_cmd = vdec_decoder_cmd,
पूर्ण;

अटल पूर्णांक vdec_pm_get(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev_dec;
	पूर्णांक ret;

	mutex_lock(&core->pm_lock);
	ret = pm_runसमय_get_sync(dev);
	mutex_unlock(&core->pm_lock);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक vdec_pm_put(काष्ठा venus_inst *inst, bool स्वतःsuspend)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev_dec;
	पूर्णांक ret;

	mutex_lock(&core->pm_lock);

	अगर (स्वतःsuspend)
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	अन्यथा
		ret = pm_runसमय_put_sync(dev);

	mutex_unlock(&core->pm_lock);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक vdec_pm_get_put(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev_dec;
	पूर्णांक ret = 0;

	mutex_lock(&core->pm_lock);

	अगर (pm_runसमय_suspended(dev)) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			जाओ error;

		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

error:
	mutex_unlock(&core->pm_lock);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम vdec_pm_touch(काष्ठा venus_inst *inst)
अणु
	pm_runसमय_mark_last_busy(inst->core->dev_dec);
पूर्ण

अटल पूर्णांक vdec_set_properties(काष्ठा venus_inst *inst)
अणु
	काष्ठा vdec_controls *ctr = &inst->controls.dec;
	काष्ठा hfi_enable en = अणु .enable = 1 पूर्ण;
	u32 ptype, decode_order, conceal;
	पूर्णांक ret;

	अगर (ctr->post_loop_deb_mode) अणु
		ptype = HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER;
		ret = hfi_session_set_property(inst, ptype, &en);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ctr->display_delay_enable && ctr->display_delay == 0) अणु
		ptype = HFI_PROPERTY_PARAM_VDEC_OUTPUT_ORDER;
		decode_order = HFI_OUTPUT_ORDER_DECODE;
		ret = hfi_session_set_property(inst, ptype, &decode_order);
		अगर (ret)
			वापस ret;
	पूर्ण

	ptype = HFI_PROPERTY_PARAM_VDEC_CONCEAL_COLOR;
	conceal = ctr->conceal_color & 0xffff;
	conceal |= ((ctr->conceal_color >> 16) & 0xffff) << 10;
	conceal |= ((ctr->conceal_color >> 32) & 0xffff) << 20;

	ret = hfi_session_set_property(inst, ptype, &conceal);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा is_ubwc_fmt(fmt) (!!((fmt) & HFI_COLOR_FORMAT_UBWC_BASE))

अटल पूर्णांक vdec_output_conf(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा hfi_enable en = अणु .enable = 1 पूर्ण;
	काष्ठा hfi_buffer_requirements bufreq;
	u32 width = inst->out_width;
	u32 height = inst->out_height;
	u32 out_fmt, out2_fmt;
	bool ubwc = false;
	u32 ptype;
	पूर्णांक ret;

	ret = venus_helper_set_work_mode(inst);
	अगर (ret)
		वापस ret;

	अगर (core->res->hfi_version == HFI_VERSION_1XX) अणु
		ptype = HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER;
		ret = hfi_session_set_property(inst, ptype, &en);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Force searching UBWC क्रमmats क्रम bigger then HD resolutions */
	अगर (width > 1920 && height > ALIGN(1080, 32))
		ubwc = true;

	/* For Venus v4/v6 UBWC क्रमmat is mandatory */
	अगर (IS_V4(core) || IS_V6(core))
		ubwc = true;

	ret = venus_helper_get_out_fmts(inst, inst->fmt_cap->pixfmt, &out_fmt,
					&out2_fmt, ubwc);
	अगर (ret)
		वापस ret;

	inst->output_buf_size =
			venus_helper_get_framesz_raw(out_fmt, width, height);
	inst->output2_buf_size =
			venus_helper_get_framesz_raw(out2_fmt, width, height);

	अगर (is_ubwc_fmt(out_fmt)) अणु
		inst->opb_buftype = HFI_BUFFER_OUTPUT2;
		inst->opb_fmt = out2_fmt;
		inst->dpb_buftype = HFI_BUFFER_OUTPUT;
		inst->dpb_fmt = out_fmt;
	पूर्ण अन्यथा अगर (is_ubwc_fmt(out2_fmt)) अणु
		inst->opb_buftype = HFI_BUFFER_OUTPUT;
		inst->opb_fmt = out_fmt;
		inst->dpb_buftype = HFI_BUFFER_OUTPUT2;
		inst->dpb_fmt = out2_fmt;
	पूर्ण अन्यथा अणु
		inst->opb_buftype = HFI_BUFFER_OUTPUT;
		inst->opb_fmt = out_fmt;
		inst->dpb_buftype = 0;
		inst->dpb_fmt = 0;
	पूर्ण

	ret = venus_helper_set_raw_क्रमmat(inst, inst->opb_fmt,
					  inst->opb_buftype);
	अगर (ret)
		वापस ret;

	ret = venus_helper_set_क्रमmat_स्थिरraपूर्णांकs(inst);
	अगर (ret)
		वापस ret;

	अगर (inst->dpb_fmt) अणु
		ret = venus_helper_set_multistream(inst, false, true);
		अगर (ret)
			वापस ret;

		ret = venus_helper_set_raw_क्रमmat(inst, inst->dpb_fmt,
						  inst->dpb_buftype);
		अगर (ret)
			वापस ret;

		ret = venus_helper_set_output_resolution(inst, width, height,
							 HFI_BUFFER_OUTPUT2);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (IS_V3(core) || IS_V4(core) || IS_V6(core)) अणु
		ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT, &bufreq);
		अगर (ret)
			वापस ret;

		अगर (bufreq.size > inst->output_buf_size)
			वापस -EINVAL;

		अगर (inst->dpb_fmt) अणु
			ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT2,
						      &bufreq);
			अगर (ret)
				वापस ret;

			अगर (bufreq.size > inst->output2_buf_size)
				वापस -EINVAL;
		पूर्ण

		अगर (inst->output2_buf_size) अणु
			ret = venus_helper_set_bufsize(inst,
						       inst->output2_buf_size,
						       HFI_BUFFER_OUTPUT2);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (inst->output_buf_size) अणु
			ret = venus_helper_set_bufsize(inst,
						       inst->output_buf_size,
						       HFI_BUFFER_OUTPUT);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = venus_helper_set_dyn_buभ_शेषe(inst);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_session_init(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	ret = venus_helper_session_init(inst);
	अगर (ret == -EALREADY)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	ret = venus_helper_set_input_resolution(inst, frame_width_min(inst),
						frame_height_min(inst));
	अगर (ret)
		जाओ deinit;

	वापस 0;
deinit:
	hfi_session_deinit(inst);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_num_buffers(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक *in_num,
			    अचिन्हित पूर्णांक *out_num)
अणु
	क्रमागत hfi_version ver = inst->core->res->hfi_version;
	काष्ठा hfi_buffer_requirements bufreq;
	पूर्णांक ret;

	*in_num = *out_num = 0;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_INPUT, &bufreq);
	अगर (ret)
		वापस ret;

	*in_num = HFI_BUFREQ_COUNT_MIN(&bufreq, ver);

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT, &bufreq);
	अगर (ret)
		वापस ret;

	*out_num = HFI_BUFREQ_COUNT_MIN(&bufreq, ver);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_queue_setup(काष्ठा vb2_queue *q,
			    अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			    अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(q);
	अचिन्हित पूर्णांक in_num, out_num;
	पूर्णांक ret = 0;

	अगर (*num_planes) अणु
		अचिन्हित पूर्णांक output_buf_size = venus_helper_get_opb_size(inst);

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
		    sizes[0] < output_buf_size)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	ret = vdec_pm_get(inst);
	अगर (ret)
		वापस ret;

	ret = vdec_session_init(inst);
	अगर (ret)
		जाओ put_घातer;

	ret = vdec_num_buffers(inst, &in_num, &out_num);
	अगर (ret)
		जाओ put_घातer;

	ret = vdec_pm_put(inst, false);
	अगर (ret)
		वापस ret;

	चयन (q->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		*num_planes = inst->fmt_out->num_planes;
		sizes[0] = venus_helper_get_framesz(inst->fmt_out->pixfmt,
						    inst->out_width,
						    inst->out_height);
		sizes[0] = max(sizes[0], inst->input_buf_size);
		inst->input_buf_size = sizes[0];
		*num_buffers = max(*num_buffers, in_num);
		inst->num_input_bufs = *num_buffers;
		inst->num_output_bufs = out_num;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		*num_planes = inst->fmt_cap->num_planes;
		sizes[0] = venus_helper_get_framesz(inst->fmt_cap->pixfmt,
						    inst->width,
						    inst->height);
		inst->output_buf_size = sizes[0];
		*num_buffers = max(*num_buffers, out_num);
		inst->num_output_bufs = *num_buffers;

		mutex_lock(&inst->lock);
		अगर (inst->codec_state == VENUS_DEC_STATE_CAPTURE_SETUP)
			inst->codec_state = VENUS_DEC_STATE_STOPPED;
		mutex_unlock(&inst->lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;

put_घातer:
	vdec_pm_put(inst, false);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_verअगरy_conf(काष्ठा venus_inst *inst)
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

	अगर (inst->num_input_bufs < HFI_BUFREQ_COUNT_MIN(&bufreq, ver))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_start_capture(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	अगर (!inst->streamon_out)
		वापस 0;

	अगर (inst->codec_state == VENUS_DEC_STATE_DECODING) अणु
		अगर (inst->reconfig)
			जाओ reconfigure;

		venus_helper_queue_dpb_bufs(inst);
		venus_helper_process_initial_cap_bufs(inst);
		inst->streamon_cap = 1;
		वापस 0;
	पूर्ण

	अगर (inst->codec_state != VENUS_DEC_STATE_STOPPED)
		वापस 0;

reconfigure:
	ret = vdec_output_conf(inst);
	अगर (ret)
		वापस ret;

	ret = venus_helper_set_num_bufs(inst, inst->num_input_bufs,
					VB2_MAX_FRAME, VB2_MAX_FRAME);
	अगर (ret)
		वापस ret;

	ret = venus_helper_पूर्णांकbufs_पुनः_स्मृति(inst);
	अगर (ret)
		जाओ err;

	ret = venus_helper_alloc_dpb_bufs(inst);
	अगर (ret)
		जाओ err;

	ret = venus_helper_queue_dpb_bufs(inst);
	अगर (ret)
		जाओ मुक्त_dpb_bufs;

	ret = venus_helper_process_initial_cap_bufs(inst);
	अगर (ret)
		जाओ मुक्त_dpb_bufs;

	venus_pm_load_scale(inst);

	inst->next_buf_last = false;

	ret = hfi_session_जारी(inst);
	अगर (ret)
		जाओ मुक्त_dpb_bufs;

	inst->codec_state = VENUS_DEC_STATE_DECODING;

	अगर (inst->drain_active)
		inst->codec_state = VENUS_DEC_STATE_DRAIN;

	inst->streamon_cap = 1;
	inst->sequence_cap = 0;
	inst->reconfig = false;
	inst->drain_active = false;

	वापस 0;

मुक्त_dpb_bufs:
	venus_helper_मुक्त_dpb_bufs(inst);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_start_output(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	अगर (inst->codec_state == VENUS_DEC_STATE_SEEK) अणु
		ret = venus_helper_process_initial_out_bufs(inst);
		अगर (inst->next_buf_last)
			inst->codec_state = VENUS_DEC_STATE_DRC;
		अन्यथा
			inst->codec_state = VENUS_DEC_STATE_DECODING;
		जाओ करोne;
	पूर्ण

	अगर (inst->codec_state == VENUS_DEC_STATE_INIT ||
	    inst->codec_state == VENUS_DEC_STATE_CAPTURE_SETUP) अणु
		ret = venus_helper_process_initial_out_bufs(inst);
		जाओ करोne;
	पूर्ण

	अगर (inst->codec_state != VENUS_DEC_STATE_DEINIT)
		वापस -EINVAL;

	venus_helper_init_instance(inst);
	inst->sequence_out = 0;
	inst->reconfig = false;
	inst->next_buf_last = false;

	ret = vdec_set_properties(inst);
	अगर (ret)
		वापस ret;

	ret = vdec_output_conf(inst);
	अगर (ret)
		वापस ret;

	ret = vdec_verअगरy_conf(inst);
	अगर (ret)
		वापस ret;

	ret = venus_helper_set_num_bufs(inst, inst->num_input_bufs,
					VB2_MAX_FRAME, VB2_MAX_FRAME);
	अगर (ret)
		वापस ret;

	ret = venus_helper_vb2_start_streaming(inst);
	अगर (ret)
		वापस ret;

	ret = venus_helper_process_initial_out_bufs(inst);
	अगर (ret)
		वापस ret;

	inst->codec_state = VENUS_DEC_STATE_INIT;

करोne:
	inst->streamon_out = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(q);
	पूर्णांक ret;

	mutex_lock(&inst->lock);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		ret = vdec_start_capture(inst);
	पूर्ण अन्यथा अणु
		ret = vdec_pm_get(inst);
		अगर (ret)
			जाओ error;

		ret = venus_pm_acquire_core(inst);
		अगर (ret)
			जाओ put_घातer;

		ret = vdec_pm_put(inst, true);
		अगर (ret)
			जाओ error;

		ret = vdec_start_output(inst);
	पूर्ण

	अगर (ret)
		जाओ error;

	mutex_unlock(&inst->lock);
	वापस 0;

put_घातer:
	vdec_pm_put(inst, false);
error:
	venus_helper_buffers_करोne(inst, q->type, VB2_BUF_STATE_QUEUED);
	mutex_unlock(&inst->lock);
	वापस ret;
पूर्ण

अटल व्योम vdec_cancel_dst_buffers(काष्ठा venus_inst *inst)
अणु
	काष्ठा vb2_v4l2_buffer *buf;

	जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(inst->m2m_ctx)))
		v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);
पूर्ण

अटल पूर्णांक vdec_stop_capture(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret = 0;

	चयन (inst->codec_state) अणु
	हाल VENUS_DEC_STATE_DECODING:
		ret = hfi_session_flush(inst, HFI_FLUSH_ALL, true);
		fallthrough;
	हाल VENUS_DEC_STATE_DRAIN:
		inst->codec_state = VENUS_DEC_STATE_STOPPED;
		inst->drain_active = false;
		fallthrough;
	हाल VENUS_DEC_STATE_SEEK:
		vdec_cancel_dst_buffers(inst);
		अवरोध;
	हाल VENUS_DEC_STATE_DRC:
		ret = hfi_session_flush(inst, HFI_FLUSH_OUTPUT, true);
		inst->codec_state = VENUS_DEC_STATE_CAPTURE_SETUP;
		venus_helper_मुक्त_dpb_bufs(inst);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vdec_stop_output(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret = 0;

	चयन (inst->codec_state) अणु
	हाल VENUS_DEC_STATE_DECODING:
	हाल VENUS_DEC_STATE_DRAIN:
	हाल VENUS_DEC_STATE_STOPPED:
	हाल VENUS_DEC_STATE_DRC:
		ret = hfi_session_flush(inst, HFI_FLUSH_ALL, true);
		inst->codec_state = VENUS_DEC_STATE_SEEK;
		अवरोध;
	हाल VENUS_DEC_STATE_INIT:
	हाल VENUS_DEC_STATE_CAPTURE_SETUP:
		ret = hfi_session_flush(inst, HFI_FLUSH_INPUT, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vdec_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(q);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&inst->lock);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		ret = vdec_stop_capture(inst);
	अन्यथा
		ret = vdec_stop_output(inst);

	venus_helper_buffers_करोne(inst, q->type, VB2_BUF_STATE_ERROR);

	अगर (ret)
		जाओ unlock;

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 0;
	अन्यथा
		inst->streamon_cap = 0;

unlock:
	mutex_unlock(&inst->lock);
पूर्ण

अटल व्योम vdec_session_release(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	पूर्णांक ret, पात = 0;

	vdec_pm_get(inst);

	mutex_lock(&inst->lock);
	inst->codec_state = VENUS_DEC_STATE_DEINIT;

	ret = hfi_session_stop(inst);
	पात = (ret && ret != -EINVAL) ? 1 : 0;
	ret = hfi_session_unload_res(inst);
	पात = (ret && ret != -EINVAL) ? 1 : 0;
	ret = venus_helper_unरेजिस्टर_bufs(inst);
	पात = (ret && ret != -EINVAL) ? 1 : 0;
	ret = venus_helper_पूर्णांकbufs_मुक्त(inst);
	पात = (ret && ret != -EINVAL) ? 1 : 0;
	ret = hfi_session_deinit(inst);
	पात = (ret && ret != -EINVAL) ? 1 : 0;

	अगर (inst->session_error || core->sys_error)
		पात = 1;

	अगर (पात)
		hfi_session_पात(inst);

	venus_helper_मुक्त_dpb_bufs(inst);
	venus_pm_load_scale(inst);
	INIT_LIST_HEAD(&inst->रेजिस्टरedbufs);
	mutex_unlock(&inst->lock);

	venus_pm_release_core(inst);
	vdec_pm_put(inst, false);
पूर्ण

अटल पूर्णांक vdec_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);

	inst->buf_count++;

	वापस venus_helper_vb2_buf_init(vb);
पूर्ण

अटल व्योम vdec_buf_cleanup(काष्ठा vb2_buffer *vb)
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
		vdec_session_release(inst);
पूर्ण

अटल व्योम vdec_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	अटल स्थिर काष्ठा v4l2_event eos = अणु .type = V4L2_EVENT_EOS पूर्ण;

	vdec_pm_get_put(inst);

	mutex_lock(&inst->lock);

	अगर (inst->next_buf_last && V4L2_TYPE_IS_CAPTURE(vb->vb2_queue->type) &&
	    inst->codec_state == VENUS_DEC_STATE_DRC) अणु
		vbuf->flags |= V4L2_BUF_FLAG_LAST;
		vbuf->sequence = inst->sequence_cap++;
		vbuf->field = V4L2_FIELD_NONE;
		vb2_set_plane_payload(vb, 0, 0);
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_DONE);
		v4l2_event_queue_fh(&inst->fh, &eos);
		inst->next_buf_last = false;
		mutex_unlock(&inst->lock);
		वापस;
	पूर्ण

	venus_helper_vb2_buf_queue(vb);
	mutex_unlock(&inst->lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops vdec_vb2_ops = अणु
	.queue_setup = vdec_queue_setup,
	.buf_init = vdec_buf_init,
	.buf_cleanup = vdec_buf_cleanup,
	.buf_prepare = venus_helper_vb2_buf_prepare,
	.start_streaming = vdec_start_streaming,
	.stop_streaming = vdec_stop_streaming,
	.buf_queue = vdec_vb2_buf_queue,
पूर्ण;

अटल व्योम vdec_buf_करोne(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक buf_type,
			  u32 tag, u32 bytesused, u32 data_offset, u32 flags,
			  u32 hfi_flags, u64 बारtamp_us)
अणु
	क्रमागत vb2_buffer_state state = VB2_BUF_STATE_DONE;
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा vb2_buffer *vb;
	अचिन्हित पूर्णांक type;

	vdec_pm_touch(inst);

	अगर (buf_type == HFI_BUFFER_INPUT)
		type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	अन्यथा
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;

	vbuf = venus_helper_find_buf(inst, type, tag);
	अगर (!vbuf)
		वापस;

	vbuf->flags = flags;
	vbuf->field = V4L2_FIELD_NONE;
	vb = &vbuf->vb2_buf;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		vb2_set_plane_payload(vb, 0, bytesused);
		vb->planes[0].data_offset = data_offset;
		vb->बारtamp = बारtamp_us * NSEC_PER_USEC;
		vbuf->sequence = inst->sequence_cap++;

		अगर (vbuf->flags & V4L2_BUF_FLAG_LAST) अणु
			स्थिर काष्ठा v4l2_event ev = अणु .type = V4L2_EVENT_EOS पूर्ण;

			v4l2_event_queue_fh(&inst->fh, &ev);

			अगर (inst->codec_state == VENUS_DEC_STATE_DRAIN) अणु
				inst->drain_active = false;
				inst->codec_state = VENUS_DEC_STATE_STOPPED;
			पूर्ण
		पूर्ण

		अगर (!bytesused)
			state = VB2_BUF_STATE_ERROR;
	पूर्ण अन्यथा अणु
		vbuf->sequence = inst->sequence_out++;
	पूर्ण

	venus_helper_get_ts_metadata(inst, बारtamp_us, vbuf);

	अगर (hfi_flags & HFI_BUFFERFLAG_READONLY)
		venus_helper_acquire_buf_ref(vbuf);

	अगर (hfi_flags & HFI_BUFFERFLAG_DATACORRUPT)
		state = VB2_BUF_STATE_ERROR;

	अगर (hfi_flags & HFI_BUFFERFLAG_DROP_FRAME) अणु
		state = VB2_BUF_STATE_ERROR;
		vb2_set_plane_payload(vb, 0, 0);
		vb->बारtamp = 0;
	पूर्ण

	v4l2_m2m_buf_करोne(vbuf, state);
पूर्ण

अटल व्योम vdec_event_change(काष्ठा venus_inst *inst,
			      काष्ठा hfi_event_data *ev_data, bool sufficient)
अणु
	अटल स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION पूर्ण;
	काष्ठा device *dev = inst->core->dev_dec;
	काष्ठा v4l2_क्रमmat क्रमmat = अणुपूर्ण;

	mutex_lock(&inst->lock);

	क्रमmat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	क्रमmat.fmt.pix_mp.pixelक्रमmat = inst->fmt_cap->pixfmt;
	क्रमmat.fmt.pix_mp.width = ev_data->width;
	क्रमmat.fmt.pix_mp.height = ev_data->height;

	vdec_try_fmt_common(inst, &क्रमmat);

	inst->width = क्रमmat.fmt.pix_mp.width;
	inst->height = क्रमmat.fmt.pix_mp.height;
	/*
	 * Some versions of the firmware करो not report crop inक्रमmation क्रम
	 * all codecs. For these हालs, set the crop to the coded resolution.
	 */
	अगर (ev_data->input_crop.width > 0 && ev_data->input_crop.height > 0) अणु
		inst->crop.left = ev_data->input_crop.left;
		inst->crop.top = ev_data->input_crop.top;
		inst->crop.width = ev_data->input_crop.width;
		inst->crop.height = ev_data->input_crop.height;
	पूर्ण अन्यथा अणु
		inst->crop.left = 0;
		inst->crop.top = 0;
		inst->crop.width = ev_data->width;
		inst->crop.height = ev_data->height;
	पूर्ण

	inst->out_width = ev_data->width;
	inst->out_height = ev_data->height;

	अगर (inst->bit_depth != ev_data->bit_depth)
		inst->bit_depth = ev_data->bit_depth;

	अगर (inst->pic_काष्ठा != ev_data->pic_काष्ठा)
		inst->pic_काष्ठा = ev_data->pic_काष्ठा;

	dev_dbg(dev, VDBGM "event %s sufficient resources (%ux%u)\n",
		sufficient ? "" : "not", ev_data->width, ev_data->height);

	चयन (inst->codec_state) अणु
	हाल VENUS_DEC_STATE_INIT:
		inst->codec_state = VENUS_DEC_STATE_CAPTURE_SETUP;
		अवरोध;
	हाल VENUS_DEC_STATE_DECODING:
	हाल VENUS_DEC_STATE_DRAIN:
		inst->codec_state = VENUS_DEC_STATE_DRC;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * The assumption is that the firmware have to वापस the last buffer
	 * beक्रमe this event is received in the v4l2 driver. Also the firmware
	 * itself करोesn't mark the last decoder output buffer with HFI EOS flag.
	 */

	अगर (inst->codec_state == VENUS_DEC_STATE_DRC) अणु
		पूर्णांक ret;

		inst->next_buf_last = true;

		ret = hfi_session_flush(inst, HFI_FLUSH_OUTPUT, false);
		अगर (ret)
			dev_dbg(dev, VDBGH "flush output error %d\n", ret);
	पूर्ण

	inst->next_buf_last = true;
	inst->reconfig = true;
	v4l2_event_queue_fh(&inst->fh, &ev);
	wake_up(&inst->reconf_रुको);

	mutex_unlock(&inst->lock);
पूर्ण

अटल व्योम vdec_event_notअगरy(काष्ठा venus_inst *inst, u32 event,
			      काष्ठा hfi_event_data *data)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev_dec;

	vdec_pm_touch(inst);

	चयन (event) अणु
	हाल EVT_SESSION_ERROR:
		inst->session_error = true;
		dev_err(dev, "dec: event session error %x\n", inst->error);
		अवरोध;
	हाल EVT_SYS_EVENT_CHANGE:
		चयन (data->event_type) अणु
		हाल HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_RESOURCES:
			vdec_event_change(inst, data, true);
			अवरोध;
		हाल HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_RESOURCES:
			vdec_event_change(inst, data, false);
			अवरोध;
		हाल HFI_EVENT_RELEASE_BUFFER_REFERENCE:
			venus_helper_release_buf_ref(inst, data->tag);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vdec_flush_करोne(काष्ठा venus_inst *inst)
अणु
	dev_dbg(inst->core->dev_dec, VDBGH "flush done\n");
पूर्ण

अटल स्थिर काष्ठा hfi_inst_ops vdec_hfi_ops = अणु
	.buf_करोne = vdec_buf_करोne,
	.event_notअगरy = vdec_event_notअगरy,
	.flush_करोne = vdec_flush_करोne,
पूर्ण;

अटल व्योम vdec_inst_init(काष्ठा venus_inst *inst)
अणु
	inst->hfi_codec = HFI_VIDEO_CODEC_H264;
	inst->fmt_out = &vdec_क्रमmats[6];
	inst->fmt_cap = &vdec_क्रमmats[0];
	inst->width = frame_width_min(inst);
	inst->height = ALIGN(frame_height_min(inst), 32);
	inst->crop.left = 0;
	inst->crop.top = 0;
	inst->crop.width = inst->width;
	inst->crop.height = inst->height;
	inst->out_width = frame_width_min(inst);
	inst->out_height = frame_height_min(inst);
	inst->fps = 30;
	inst->समयperframe.numerator = 1;
	inst->समयperframe.denominator = 30;
	inst->opb_buftype = HFI_BUFFER_OUTPUT;
पूर्ण

अटल व्योम vdec_m2m_device_run(व्योम *priv)
अणु
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops vdec_m2m_ops = अणु
	.device_run = vdec_m2m_device_run,
	.job_पात = venus_helper_m2m_job_पात,
पूर्ण;

अटल पूर्णांक m2m_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा venus_inst *inst = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->ops = &vdec_vb2_ops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->drv_priv = inst;
	src_vq->buf_काष्ठा_size = माप(काष्ठा venus_buffer);
	src_vq->allow_zero_bytesused = 1;
	src_vq->min_buffers_needed = 0;
	src_vq->dev = inst->core->dev;
	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->ops = &vdec_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->drv_priv = inst;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा venus_buffer);
	dst_vq->allow_zero_bytesused = 1;
	dst_vq->min_buffers_needed = 0;
	dst_vq->dev = inst->core->dev;
	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक vdec_खोलो(काष्ठा file *file)
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
	inst->session_type = VIDC_SESSION_TYPE_DEC;
	inst->num_output_bufs = 1;
	inst->codec_state = VENUS_DEC_STATE_DEINIT;
	inst->buf_count = 0;
	inst->clk_data.core_id = VIDC_CORE_ID_DEFAULT;
	inst->core_acquired = false;
	inst->bit_depth = VIDC_BITDEPTH_8;
	inst->pic_काष्ठा = HFI_INTERLACE_FRAME_PROGRESSIVE;
	init_रुकोqueue_head(&inst->reconf_रुको);
	venus_helper_init_instance(inst);

	ret = vdec_ctrl_init(inst);
	अगर (ret)
		जाओ err_मुक्त;

	ret = hfi_session_create(inst, &vdec_hfi_ops);
	अगर (ret)
		जाओ err_ctrl_deinit;

	vdec_inst_init(inst);

	/*
	 * create m2m device क्रम every instance, the m2m context scheduling
	 * is made by firmware side so we करो not need to care about.
	 */
	inst->m2m_dev = v4l2_m2m_init(&vdec_m2m_ops);
	अगर (IS_ERR(inst->m2m_dev)) अणु
		ret = PTR_ERR(inst->m2m_dev);
		जाओ err_session_destroy;
	पूर्ण

	inst->m2m_ctx = v4l2_m2m_ctx_init(inst->m2m_dev, inst, m2m_queue_init);
	अगर (IS_ERR(inst->m2m_ctx)) अणु
		ret = PTR_ERR(inst->m2m_ctx);
		जाओ err_m2m_release;
	पूर्ण

	v4l2_fh_init(&inst->fh, core->vdev_dec);

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
	vdec_ctrl_deinit(inst);
err_मुक्त:
	kमुक्त(inst);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_बंद(काष्ठा file *file)
अणु
	काष्ठा venus_inst *inst = to_inst(file);

	vdec_pm_get(inst);

	v4l2_m2m_ctx_release(inst->m2m_ctx);
	v4l2_m2m_release(inst->m2m_dev);
	vdec_ctrl_deinit(inst);
	hfi_session_destroy(inst);
	mutex_destroy(&inst->lock);
	v4l2_fh_del(&inst->fh);
	v4l2_fh_निकास(&inst->fh);

	vdec_pm_put(inst, false);

	kमुक्त(inst);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vdec_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = vdec_खोलो,
	.release = vdec_बंद,
	.unlocked_ioctl = video_ioctl2,
	.poll = v4l2_m2m_fop_poll,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक vdec_probe(काष्ठा platक्रमm_device *pdev)
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

	अगर (core->pm_ops->vdec_get) अणु
		ret = core->pm_ops->vdec_get(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	vdev = video_device_alloc();
	अगर (!vdev)
		वापस -ENOMEM;

	strscpy(vdev->name, "qcom-venus-decoder", माप(vdev->name));
	vdev->release = video_device_release;
	vdev->fops = &vdec_fops;
	vdev->ioctl_ops = &vdec_ioctl_ops;
	vdev->vfl_dir = VFL_सूची_M2M;
	vdev->v4l2_dev = &core->v4l2_dev;
	vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ err_vdev_release;

	core->vdev_dec = vdev;
	core->dev_dec = dev;

	video_set_drvdata(vdev, core);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 2000);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	वापस 0;

err_vdev_release:
	video_device_release(vdev);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(pdev->dev.parent);

	video_unरेजिस्टर_device(core->vdev_dec);
	pm_runसमय_disable(core->dev_dec);

	अगर (core->pm_ops->vdec_put)
		core->pm_ops->vdec_put(core->dev_dec);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक vdec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret = 0;

	अगर (pm_ops->vdec_घातer)
		ret = pm_ops->vdec_घातer(dev, POWER_OFF);

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक vdec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret = 0;

	अगर (pm_ops->vdec_घातer)
		ret = pm_ops->vdec_घातer(dev, POWER_ON);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vdec_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(vdec_runसमय_suspend, vdec_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id vdec_dt_match[] = अणु
	अणु .compatible = "venus-decoder" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vdec_dt_match);

अटल काष्ठा platक्रमm_driver qcom_venus_dec_driver = अणु
	.probe = vdec_probe,
	.हटाओ = vdec_हटाओ,
	.driver = अणु
		.name = "qcom-venus-decoder",
		.of_match_table = vdec_dt_match,
		.pm = &vdec_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_venus_dec_driver);

MODULE_ALIAS("platform:qcom-venus-decoder");
MODULE_DESCRIPTION("Qualcomm Venus video decoder driver");
MODULE_LICENSE("GPL v2");
