<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI Camera Access Layer (CAL) - Video Device
 *
 * Copyright (c) 2015-2020 Texas Instruments Inc.
 *
 * Authors:
 *	Benoit Parrot <bparrot@ti.com>
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/ioctl.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/videodev2.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "cal.h"

/*  Prपूर्णांक Four-अक्षरacter-code (FOURCC) */
अटल अक्षर *fourcc_to_str(u32 fmt)
अणु
	अटल अक्षर code[5];

	code[0] = (अचिन्हित अक्षर)(fmt & 0xff);
	code[1] = (अचिन्हित अक्षर)((fmt >> 8) & 0xff);
	code[2] = (अचिन्हित अक्षर)((fmt >> 16) & 0xff);
	code[3] = (अचिन्हित अक्षर)((fmt >> 24) & 0xff);
	code[4] = '\0';

	वापस code;
पूर्ण

/* ------------------------------------------------------------------
 *	V4L2 Common IOCTLs
 * ------------------------------------------------------------------
 */

अटल पूर्णांक cal_querycap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);

	strscpy(cap->driver, CAL_MODULE_NAME, माप(cap->driver));
	strscpy(cap->card, CAL_MODULE_NAME, माप(cap->card));

	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", dev_name(ctx->cal->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक cal_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);

	*f = ctx->v_fmt;

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------
 *	V4L2 Video Node Centric IOCTLs
 * ------------------------------------------------------------------
 */

अटल स्थिर काष्ठा cal_क्रमmat_info *find_क्रमmat_by_pix(काष्ठा cal_ctx *ctx,
							u32 pixelक्रमmat)
अणु
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < ctx->num_active_fmt; k++) अणु
		fmtinfo = ctx->active_fmt[k];
		अगर (fmtinfo->fourcc == pixelक्रमmat)
			वापस fmtinfo;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा cal_क्रमmat_info *find_क्रमmat_by_code(काष्ठा cal_ctx *ctx,
							 u32 code)
अणु
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < ctx->num_active_fmt; k++) अणु
		fmtinfo = ctx->active_fmt[k];
		अगर (fmtinfo->code == code)
			वापस fmtinfo;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक cal_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;

	अगर (f->index >= ctx->num_active_fmt)
		वापस -EINVAL;

	fmtinfo = ctx->active_fmt[f->index];

	f->pixelक्रमmat = fmtinfo->fourcc;
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	वापस 0;
पूर्ण

अटल पूर्णांक __subdev_get_क्रमmat(काष्ठा cal_ctx *ctx,
			       काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.क्रमmat;
	पूर्णांक ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = 0;

	ret = v4l2_subdev_call(ctx->phy->sensor, pad, get_fmt, शून्य, &sd_fmt);
	अगर (ret)
		वापस ret;

	*fmt = *mbus_fmt;

	ctx_dbg(1, ctx, "%s %dx%d code:%04X\n", __func__,
		fmt->width, fmt->height, fmt->code);

	वापस 0;
पूर्ण

अटल पूर्णांक __subdev_set_क्रमmat(काष्ठा cal_ctx *ctx,
			       काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.क्रमmat;
	पूर्णांक ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = 0;
	*mbus_fmt = *fmt;

	ret = v4l2_subdev_call(ctx->phy->sensor, pad, set_fmt, शून्य, &sd_fmt);
	अगर (ret)
		वापस ret;

	ctx_dbg(1, ctx, "%s %dx%d code:%04X\n", __func__,
		fmt->width, fmt->height, fmt->code);

	वापस 0;
पूर्ण

अटल व्योम cal_calc_क्रमmat_size(काष्ठा cal_ctx *ctx,
				 स्थिर काष्ठा cal_क्रमmat_info *fmtinfo,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	u32 bpl, max_width;

	/*
	 * Maximum width is bound by the DMA max width in bytes.
	 * We need to recalculate the actual maxi width depending on the
	 * number of bytes per pixels required.
	 */
	max_width = CAL_MAX_WIDTH_BYTES / (ALIGN(fmtinfo->bpp, 8) >> 3);
	v4l_bound_align_image(&f->fmt.pix.width, 48, max_width, 2,
			      &f->fmt.pix.height, 32, CAL_MAX_HEIGHT_LINES,
			      0, 0);

	bpl = (f->fmt.pix.width * ALIGN(fmtinfo->bpp, 8)) >> 3;
	f->fmt.pix.bytesperline = ALIGN(bpl, 16);

	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;

	ctx_dbg(3, ctx, "%s: fourcc: %s size: %dx%d bpl:%d img_size:%d\n",
		__func__, fourcc_to_str(f->fmt.pix.pixelक्रमmat),
		f->fmt.pix.width, f->fmt.pix.height,
		f->fmt.pix.bytesperline, f->fmt.pix.sizeimage);
पूर्ण

अटल पूर्णांक cal_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse;
	पूर्णांक ret, found;

	fmtinfo = find_क्रमmat_by_pix(ctx, f->fmt.pix.pixelक्रमmat);
	अगर (!fmtinfo) अणु
		ctx_dbg(3, ctx, "Fourcc format (0x%08x) not found.\n",
			f->fmt.pix.pixelक्रमmat);

		/* Just get the first one क्रमागतerated */
		fmtinfo = ctx->active_fmt[0];
		f->fmt.pix.pixelक्रमmat = fmtinfo->fourcc;
	पूर्ण

	f->fmt.pix.field = ctx->v_fmt.fmt.pix.field;

	/* check क्रम/find a valid width/height */
	ret = 0;
	found = false;
	fse.pad = 0;
	fse.code = fmtinfo->code;
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रम (fse.index = 0; ; fse.index++) अणु
		ret = v4l2_subdev_call(ctx->phy->sensor, pad, क्रमागत_frame_size,
				       शून्य, &fse);
		अगर (ret)
			अवरोध;

		अगर ((f->fmt.pix.width == fse.max_width) &&
		    (f->fmt.pix.height == fse.max_height)) अणु
			found = true;
			अवरोध;
		पूर्ण अन्यथा अगर ((f->fmt.pix.width >= fse.min_width) &&
			 (f->fmt.pix.width <= fse.max_width) &&
			 (f->fmt.pix.height >= fse.min_height) &&
			 (f->fmt.pix.height <= fse.max_height)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		/* use existing values as शेष */
		f->fmt.pix.width = ctx->v_fmt.fmt.pix.width;
		f->fmt.pix.height =  ctx->v_fmt.fmt.pix.height;
	पूर्ण

	/*
	 * Use current colorspace क्रम now, it will get
	 * updated properly during s_fmt
	 */
	f->fmt.pix.colorspace = ctx->v_fmt.fmt.pix.colorspace;
	cal_calc_क्रमmat_size(ctx, fmtinfo, f);
	वापस 0;
पूर्ण

अटल पूर्णांक cal_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	काष्ठा vb2_queue *q = &ctx->vb_vidq;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = CAL_CAMERARX_PAD_SINK,
	पूर्ण;
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	पूर्णांक ret;

	अगर (vb2_is_busy(q)) अणु
		ctx_dbg(3, ctx, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	ret = cal_try_fmt_vid_cap(file, priv, f);
	अगर (ret < 0)
		वापस ret;

	fmtinfo = find_क्रमmat_by_pix(ctx, f->fmt.pix.pixelक्रमmat);

	v4l2_fill_mbus_क्रमmat(&sd_fmt.क्रमmat, &f->fmt.pix, fmtinfo->code);

	ret = __subdev_set_क्रमmat(ctx, &sd_fmt.क्रमmat);
	अगर (ret)
		वापस ret;

	/* Just द्विगुन check nothing has gone wrong */
	अगर (sd_fmt.क्रमmat.code != fmtinfo->code) अणु
		ctx_dbg(3, ctx,
			"%s subdev changed format on us, this should not happen\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	v4l2_fill_pix_क्रमmat(&ctx->v_fmt.fmt.pix, &sd_fmt.क्रमmat);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelक्रमmat = fmtinfo->fourcc;
	ctx->v_fmt.fmt.pix.field = sd_fmt.क्रमmat.field;
	cal_calc_क्रमmat_size(ctx, fmtinfo, &ctx->v_fmt);

	v4l2_subdev_call(&ctx->phy->subdev, pad, set_fmt, शून्य, &sd_fmt);

	ctx->fmtinfo = fmtinfo;
	*f = ctx->v_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse;
	पूर्णांक ret;

	/* check क्रम valid क्रमmat */
	fmtinfo = find_क्रमmat_by_pix(ctx, fsize->pixel_क्रमmat);
	अगर (!fmtinfo) अणु
		ctx_dbg(3, ctx, "Invalid pixel code: %x\n",
			fsize->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	fse.index = fsize->index;
	fse.pad = 0;
	fse.code = fmtinfo->code;
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	ret = v4l2_subdev_call(ctx->phy->sensor, pad, क्रमागत_frame_size, शून्य,
			       &fse);
	अगर (ret)
		वापस ret;

	ctx_dbg(1, ctx, "%s: index: %d code: %x W:[%d,%d] H:[%d,%d]\n",
		__func__, fse.index, fse.code, fse.min_width, fse.max_width,
		fse.min_height, fse.max_height);

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_input *inp)
अणु
	अगर (inp->index > 0)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	प्र_लिखो(inp->name, "Camera %u", inp->index);
	वापस 0;
पूर्ण

अटल पूर्णांक cal_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cal_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस i > 0 ? -EINVAL : 0;
पूर्ण

/* समयperframe is arbitrary and continuous */
अटल पूर्णांक cal_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	fmtinfo = find_क्रमmat_by_pix(ctx, fival->pixel_क्रमmat);
	अगर (!fmtinfo)
		वापस -EINVAL;

	fie.code = fmtinfo->code;
	ret = v4l2_subdev_call(ctx->phy->sensor, pad, क्रमागत_frame_पूर्णांकerval,
			       शून्य, &fie);
	अगर (ret)
		वापस ret;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops cal_ioctl_video_ops = अणु
	.vidioc_querycap      = cal_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = cal_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = cal_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = cal_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = cal_s_fmt_vid_cap,
	.vidioc_क्रमागत_framesizes   = cal_क्रमागत_framesizes,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_create_bufs   = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf   = vb2_ioctl_prepare_buf,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_expbuf        = vb2_ioctl_expbuf,
	.vidioc_क्रमागत_input    = cal_क्रमागत_input,
	.vidioc_g_input       = cal_g_input,
	.vidioc_s_input       = cal_s_input,
	.vidioc_क्रमागत_frameपूर्णांकervals = cal_क्रमागत_frameपूर्णांकervals,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_log_status    = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* ------------------------------------------------------------------
 *	V4L2 Media Controller Centric IOCTLs
 * ------------------------------------------------------------------
 */

अटल पूर्णांक cal_mc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= cal_num_क्रमmats)
		वापस -EINVAL;

	f->pixelक्रमmat = cal_क्रमmats[f->index].fourcc;
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	वापस 0;
पूर्ण

अटल व्योम cal_mc_try_fmt(काष्ठा cal_ctx *ctx, काष्ठा v4l2_क्रमmat *f,
			   स्थिर काष्ठा cal_क्रमmat_info **info)
अणु
	काष्ठा v4l2_pix_क्रमmat *क्रमmat = &f->fmt.pix;
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक bpp;

	/*
	 * Default to the first क्रमmat अगर the requested pixel क्रमmat code isn't
	 * supported.
	 */
	fmtinfo = cal_क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (!fmtinfo)
		fmtinfo = &cal_क्रमmats[0];

	/*
	 * Clamp the size, update the pixel क्रमmat. The field and colorspace are
	 * accepted as-is, except क्रम V4L2_FIELD_ANY that is turned पूर्णांकo
	 * V4L2_FIELD_NONE.
	 */
	bpp = ALIGN(fmtinfo->bpp, 8);

	क्रमmat->width = clamp_t(अचिन्हित पूर्णांक, क्रमmat->width,
				CAL_MIN_WIDTH_BYTES * 8 / bpp,
				CAL_MAX_WIDTH_BYTES * 8 / bpp);
	क्रमmat->height = clamp_t(अचिन्हित पूर्णांक, क्रमmat->height,
				 CAL_MIN_HEIGHT_LINES, CAL_MAX_HEIGHT_LINES);
	क्रमmat->pixelक्रमmat = fmtinfo->fourcc;

	अगर (क्रमmat->field == V4L2_FIELD_ANY)
		क्रमmat->field = V4L2_FIELD_NONE;

	/*
	 * Calculate the number of bytes per line and the image size. The
	 * hardware stores the stride as a number of 16 bytes words, in a
	 * चिन्हित 15-bit value. Only 14 bits are thus usable.
	 */
	क्रमmat->bytesperline = ALIGN(clamp(क्रमmat->bytesperline,
					   क्रमmat->width * bpp / 8,
					   ((1U << 14) - 1) * 16), 16);

	क्रमmat->sizeimage = क्रमmat->height * क्रमmat->bytesperline;

	क्रमmat->colorspace = ctx->v_fmt.fmt.pix.colorspace;

	अगर (info)
		*info = fmtinfo;

	ctx_dbg(3, ctx, "%s: %s %ux%u (bytesperline %u sizeimage %u)\n",
		__func__, fourcc_to_str(क्रमmat->pixelक्रमmat),
		क्रमmat->width, क्रमmat->height,
		क्रमmat->bytesperline, क्रमmat->sizeimage);
पूर्ण

अटल पूर्णांक cal_mc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);

	cal_mc_try_fmt(ctx, f, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक cal_mc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;

	अगर (vb2_is_busy(&ctx->vb_vidq)) अणु
		ctx_dbg(3, ctx, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	cal_mc_try_fmt(ctx, f, &fmtinfo);

	ctx->v_fmt = *f;
	ctx->fmtinfo = fmtinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_mc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा cal_ctx *ctx = video_drvdata(file);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक bpp;

	अगर (fsize->index > 0)
		वापस -EINVAL;

	fmtinfo = cal_क्रमmat_by_fourcc(fsize->pixel_क्रमmat);
	अगर (!fmtinfo) अणु
		ctx_dbg(3, ctx, "Invalid pixel format 0x%08x\n",
			fsize->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	bpp = ALIGN(fmtinfo->bpp, 8);

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = CAL_MIN_WIDTH_BYTES * 8 / bpp;
	fsize->stepwise.max_width = CAL_MAX_WIDTH_BYTES * 8 / bpp;
	fsize->stepwise.step_width = 64 / bpp;
	fsize->stepwise.min_height = CAL_MIN_HEIGHT_LINES;
	fsize->stepwise.max_height = CAL_MAX_HEIGHT_LINES;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops cal_ioctl_mc_ops = अणु
	.vidioc_querycap      = cal_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = cal_mc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = cal_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = cal_mc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = cal_mc_s_fmt_vid_cap,
	.vidioc_क्रमागत_framesizes   = cal_mc_क्रमागत_framesizes,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_create_bufs   = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf   = vb2_ioctl_prepare_buf,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_expbuf        = vb2_ioctl_expbuf,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_log_status    = v4l2_ctrl_log_status,
पूर्ण;

/* ------------------------------------------------------------------
 *	videobuf2 Common Operations
 * ------------------------------------------------------------------
 */

अटल पूर्णांक cal_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cal_ctx *ctx = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = ctx->v_fmt.fmt.pix.sizeimage;

	अगर (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		size = sizes[0];
	पूर्ण

	*nplanes = 1;
	sizes[0] = size;

	ctx_dbg(3, ctx, "nbuffers=%d, size=%d\n", *nbuffers, sizes[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक cal_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cal_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cal_buffer *buf = container_of(vb, काष्ठा cal_buffer,
					      vb.vb2_buf);
	अचिन्हित दीर्घ size;

	size = ctx->v_fmt.fmt.pix.sizeimage;
	अगर (vb2_plane_size(vb, 0) < size) अणु
		ctx_err(ctx,
			"data will not fit into plane (%lu < %lu)\n",
			vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);
	वापस 0;
पूर्ण

अटल व्योम cal_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cal_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cal_buffer *buf = container_of(vb, काष्ठा cal_buffer,
					      vb.vb2_buf);
	अचिन्हित दीर्घ flags;

	/* recheck locking */
	spin_lock_irqsave(&ctx->dma.lock, flags);
	list_add_tail(&buf->list, &ctx->dma.queue);
	spin_unlock_irqrestore(&ctx->dma.lock, flags);
पूर्ण

अटल व्योम cal_release_buffers(काष्ठा cal_ctx *ctx,
				क्रमागत vb2_buffer_state state)
अणु
	काष्ठा cal_buffer *buf, *पंचांगp;

	/* Release all queued buffers. */
	spin_lock_irq(&ctx->dma.lock);

	list_क्रम_each_entry_safe(buf, पंचांगp, &ctx->dma.queue, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण

	अगर (ctx->dma.pending) अणु
		vb2_buffer_करोne(&ctx->dma.pending->vb.vb2_buf, state);
		ctx->dma.pending = शून्य;
	पूर्ण

	अगर (ctx->dma.active) अणु
		vb2_buffer_करोne(&ctx->dma.active->vb.vb2_buf, state);
		ctx->dma.active = शून्य;
	पूर्ण

	spin_unlock_irq(&ctx->dma.lock);
पूर्ण

/* ------------------------------------------------------------------
 *	videobuf2 Operations
 * ------------------------------------------------------------------
 */

अटल पूर्णांक cal_video_check_क्रमmat(काष्ठा cal_ctx *ctx)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = &ctx->phy->क्रमmats[CAL_CAMERARX_PAD_SOURCE];

	अगर (ctx->fmtinfo->code != क्रमmat->code ||
	    ctx->v_fmt.fmt.pix.height != क्रमmat->height ||
	    ctx->v_fmt.fmt.pix.width != क्रमmat->width ||
	    ctx->v_fmt.fmt.pix.field != क्रमmat->field)
		वापस -EPIPE;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cal_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा cal_buffer *buf;
	dma_addr_t addr;
	पूर्णांक ret;

	ret = media_pipeline_start(&ctx->vdev.entity, &ctx->phy->pipe);
	अगर (ret < 0) अणु
		ctx_err(ctx, "Failed to start media pipeline: %d\n", ret);
		जाओ error_release_buffers;
	पूर्ण

	/*
	 * Verअगरy that the currently configured क्रमmat matches the output of
	 * the connected CAMERARX.
	 */
	ret = cal_video_check_क्रमmat(ctx);
	अगर (ret < 0) अणु
		ctx_dbg(3, ctx,
			"Format mismatch between CAMERARX and video node\n");
		जाओ error_pipeline;
	पूर्ण

	spin_lock_irq(&ctx->dma.lock);
	buf = list_first_entry(&ctx->dma.queue, काष्ठा cal_buffer, list);
	ctx->dma.pending = buf;
	list_del(&buf->list);
	spin_unlock_irq(&ctx->dma.lock);

	addr = vb2_dma_contig_plane_dma_addr(&buf->vb.vb2_buf, 0);

	pm_runसमय_get_sync(ctx->cal->dev);

	cal_ctx_set_dma_addr(ctx, addr);
	cal_ctx_start(ctx);

	ret = v4l2_subdev_call(&ctx->phy->subdev, video, s_stream, 1);
	अगर (ret)
		जाओ error_stop;

	अगर (cal_debug >= 4)
		cal_quickdump_regs(ctx->cal);

	वापस 0;

error_stop:
	cal_ctx_stop(ctx);
	pm_runसमय_put_sync(ctx->cal->dev);

error_pipeline:
	media_pipeline_stop(&ctx->vdev.entity);
error_release_buffers:
	cal_release_buffers(ctx, VB2_BUF_STATE_QUEUED);

	वापस ret;
पूर्ण

अटल व्योम cal_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा cal_ctx *ctx = vb2_get_drv_priv(vq);

	cal_ctx_stop(ctx);

	v4l2_subdev_call(&ctx->phy->subdev, video, s_stream, 0);

	pm_runसमय_put_sync(ctx->cal->dev);

	cal_release_buffers(ctx, VB2_BUF_STATE_ERROR);

	media_pipeline_stop(&ctx->vdev.entity);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cal_video_qops = अणु
	.queue_setup		= cal_queue_setup,
	.buf_prepare		= cal_buffer_prepare,
	.buf_queue		= cal_buffer_queue,
	.start_streaming	= cal_start_streaming,
	.stop_streaming		= cal_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/* ------------------------------------------------------------------
 *	V4L2 Initialization and Registration
 * ------------------------------------------------------------------
 */

अटल स्थिर काष्ठा v4l2_file_operations cal_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = vb2_fop_release,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2, /* V4L2 ioctl handler */
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल पूर्णांक cal_ctx_v4l2_init_क्रमmats(काष्ठा cal_ctx *ctx)
अणु
	काष्ठा v4l2_subdev_mbus_code_क्रमागत mbus_code;
	काष्ठा v4l2_mbus_framefmt mbus_fmt;
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक i, j, k;
	पूर्णांक ret = 0;

	/* Enumerate sub device क्रमmats and enable all matching local क्रमmats */
	ctx->active_fmt = devm_kसुस्मृति(ctx->cal->dev, cal_num_क्रमmats,
				       माप(*ctx->active_fmt), GFP_KERNEL);
	ctx->num_active_fmt = 0;

	क्रम (j = 0, i = 0; ; ++j) अणु

		स_रखो(&mbus_code, 0, माप(mbus_code));
		mbus_code.index = j;
		mbus_code.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(ctx->phy->sensor, pad, क्रमागत_mbus_code,
				       शून्य, &mbus_code);
		अगर (ret == -EINVAL)
			अवरोध;

		अगर (ret) अणु
			ctx_err(ctx, "Error enumerating mbus codes in subdev %s: %d\n",
				ctx->phy->sensor->name, ret);
			वापस ret;
		पूर्ण

		ctx_dbg(2, ctx,
			"subdev %s: code: %04x idx: %u\n",
			ctx->phy->sensor->name, mbus_code.code, j);

		क्रम (k = 0; k < cal_num_क्रमmats; k++) अणु
			fmtinfo = &cal_क्रमmats[k];

			अगर (mbus_code.code == fmtinfo->code) अणु
				ctx->active_fmt[i] = fmtinfo;
				ctx_dbg(2, ctx,
					"matched fourcc: %s: code: %04x idx: %u\n",
					fourcc_to_str(fmtinfo->fourcc),
					fmtinfo->code, i);
				ctx->num_active_fmt = ++i;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i == 0) अणु
		ctx_err(ctx, "No suitable format reported by subdev %s\n",
			ctx->phy->sensor->name);
		वापस -EINVAL;
	पूर्ण

	ret = __subdev_get_क्रमmat(ctx, &mbus_fmt);
	अगर (ret)
		वापस ret;

	fmtinfo = find_क्रमmat_by_code(ctx, mbus_fmt.code);
	अगर (!fmtinfo) अणु
		ctx_dbg(3, ctx, "mbus code format (0x%08x) not found.\n",
			mbus_fmt.code);
		वापस -EINVAL;
	पूर्ण

	/* Save current क्रमmat */
	v4l2_fill_pix_क्रमmat(&ctx->v_fmt.fmt.pix, &mbus_fmt);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelक्रमmat = fmtinfo->fourcc;
	cal_calc_क्रमmat_size(ctx, fmtinfo, &ctx->v_fmt);
	ctx->fmtinfo = fmtinfo;

	वापस 0;
पूर्ण

पूर्णांक cal_ctx_v4l2_रेजिस्टर(काष्ठा cal_ctx *ctx)
अणु
	काष्ठा video_device *vfd = &ctx->vdev;
	पूर्णांक ret;

	ret = cal_ctx_v4l2_init_क्रमmats(ctx);
	अगर (ret)
		वापस ret;

	अगर (!cal_mc_api) अणु
		काष्ठा v4l2_ctrl_handler *hdl = &ctx->ctrl_handler;

		ret = v4l2_ctrl_add_handler(hdl, ctx->phy->sensor->ctrl_handler,
					    शून्य, true);
		अगर (ret < 0) अणु
			ctx_err(ctx, "Failed to add sensor ctrl handler\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, cal_video_nr);
	अगर (ret < 0) अणु
		ctx_err(ctx, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	ret = media_create_pad_link(&ctx->phy->subdev.entity,
				    CAL_CAMERARX_PAD_SOURCE,
				    &vfd->entity, 0,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	अगर (ret) अणु
		ctx_err(ctx, "Failed to create media link for context %u\n",
			ctx->index);
		video_unरेजिस्टर_device(vfd);
		वापस ret;
	पूर्ण

	ctx_info(ctx, "V4L2 device registered as %s\n",
		 video_device_node_name(vfd));

	वापस 0;
पूर्ण

व्योम cal_ctx_v4l2_unरेजिस्टर(काष्ठा cal_ctx *ctx)
अणु
	ctx_dbg(1, ctx, "unregistering %s\n",
		video_device_node_name(&ctx->vdev));

	video_unरेजिस्टर_device(&ctx->vdev);
पूर्ण

पूर्णांक cal_ctx_v4l2_init(काष्ठा cal_ctx *ctx)
अणु
	काष्ठा video_device *vfd = &ctx->vdev;
	काष्ठा vb2_queue *q = &ctx->vb_vidq;
	पूर्णांक ret;

	INIT_LIST_HEAD(&ctx->dma.queue);
	spin_lock_init(&ctx->dma.lock);
	mutex_init(&ctx->mutex);
	init_रुकोqueue_head(&ctx->dma.रुको);

	/* Initialize the vb2 queue. */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->drv_priv = ctx;
	q->buf_काष्ठा_size = माप(काष्ठा cal_buffer);
	q->ops = &cal_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &ctx->mutex;
	q->min_buffers_needed = 3;
	q->dev = ctx->cal->dev;

	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;

	/* Initialize the video device and media entity. */
	vfd->fops = &cal_fops;
	vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING
			 | (cal_mc_api ? V4L2_CAP_IO_MC : 0);
	vfd->v4l2_dev = &ctx->cal->v4l2_dev;
	vfd->queue = q;
	snम_लिखो(vfd->name, माप(vfd->name), "CAL output %u", ctx->index);
	vfd->release = video_device_release_empty;
	vfd->ioctl_ops = cal_mc_api ? &cal_ioctl_mc_ops : &cal_ioctl_video_ops;
	vfd->lock = &ctx->mutex;
	video_set_drvdata(vfd, ctx);

	ctx->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &ctx->pad);
	अगर (ret < 0)
		वापस ret;

	अगर (!cal_mc_api) अणु
		/* Initialize the control handler. */
		काष्ठा v4l2_ctrl_handler *hdl = &ctx->ctrl_handler;

		ret = v4l2_ctrl_handler_init(hdl, 11);
		अगर (ret < 0) अणु
			ctx_err(ctx, "Failed to init ctrl handler\n");
			जाओ error;
		पूर्ण

		vfd->ctrl_handler = hdl;
	पूर्ण

	वापस 0;

error:
	media_entity_cleanup(&vfd->entity);
	वापस ret;
पूर्ण

व्योम cal_ctx_v4l2_cleanup(काष्ठा cal_ctx *ctx)
अणु
	अगर (!cal_mc_api)
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);

	media_entity_cleanup(&ctx->vdev.entity);
पूर्ण
