<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A भव codec example device.
 *
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 * This is a भव codec device driver क्रम testing the codec framework.
 * It simulates a device that uses memory buffers क्रम both source and
 * destination and encodes or decodes the data.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "codec-v4l2-fwht.h"

MODULE_DESCRIPTION("Virtual codec device");
MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com>");
MODULE_LICENSE("GPL v2");

अटल bool multiplanar;
module_param(multiplanar, bool, 0444);
MODULE_PARM_DESC(multiplanar,
		 " use multi-planar API instead of single-planar API");

अटल अचिन्हित पूर्णांक debug;
module_param(debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, " activates debug info");

#घोषणा VICODEC_NAME		"vicodec"
#घोषणा MAX_WIDTH		4096U
#घोषणा MIN_WIDTH		640U
#घोषणा MAX_HEIGHT		2160U
#घोषणा MIN_HEIGHT		360U

#घोषणा dprपूर्णांकk(dev, fmt, arg...) \
	v4l2_dbg(1, debug, &dev->v4l2_dev, "%s: " fmt, __func__, ## arg)


काष्ठा pixfmt_info अणु
	u32 id;
	अचिन्हित पूर्णांक bytesperline_mult;
	अचिन्हित पूर्णांक sizeimage_mult;
	अचिन्हित पूर्णांक sizeimage_भाग;
	अचिन्हित पूर्णांक luma_step;
	अचिन्हित पूर्णांक chroma_step;
	/* Chroma plane subsampling */
	अचिन्हित पूर्णांक width_भाग;
	अचिन्हित पूर्णांक height_भाग;
पूर्ण;

अटल स्थिर काष्ठा v4l2_fwht_pixfmt_info pixfmt_fwht = अणु
	V4L2_PIX_FMT_FWHT, 0, 3, 1, 1, 1, 1, 1, 0, 1
पूर्ण;

अटल स्थिर काष्ठा v4l2_fwht_pixfmt_info pixfmt_stateless_fwht = अणु
	V4L2_PIX_FMT_FWHT_STATELESS, 0, 3, 1, 1, 1, 1, 1, 0, 1
पूर्ण;

अटल व्योम vicodec_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा platक्रमm_device vicodec_pdev = अणु
	.name		= VICODEC_NAME,
	.dev.release	= vicodec_dev_release,
पूर्ण;

/* Per-queue, driver-specअगरic निजी data */
काष्ठा vicodec_q_data अणु
	अचिन्हित पूर्णांक		coded_width;
	अचिन्हित पूर्णांक		coded_height;
	अचिन्हित पूर्णांक		visible_width;
	अचिन्हित पूर्णांक		visible_height;
	अचिन्हित पूर्णांक		sizeimage;
	अचिन्हित पूर्णांक		vb2_sizeimage;
	अचिन्हित पूर्णांक		sequence;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info;
पूर्ण;

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

काष्ठा vicodec_dev_instance अणु
	काष्ठा video_device     vfd;
	काष्ठा mutex            mutex;
	spinlock_t              lock;
	काष्ठा v4l2_m2m_dev     *m2m_dev;
पूर्ण;

काष्ठा vicodec_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा vicodec_dev_instance stateful_enc;
	काष्ठा vicodec_dev_instance stateful_dec;
	काष्ठा vicodec_dev_instance stateless_dec;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device	mdev;
#पूर्ण_अगर

पूर्ण;

काष्ठा vicodec_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा vicodec_dev	*dev;
	bool			is_enc;
	bool			is_stateless;
	spinlock_t		*lock;

	काष्ठा v4l2_ctrl_handler hdl;

	/* Source and destination queue data */
	काष्ठा vicodec_q_data   q_data[2];
	काष्ठा v4l2_fwht_state	state;

	u32			cur_buf_offset;
	u32			comp_max_size;
	u32			comp_size;
	u32			header_size;
	u32			comp_magic_cnt;
	bool			comp_has_frame;
	bool			comp_has_next_frame;
	bool			first_source_change_sent;
	bool			source_changed;
पूर्ण;

अटल स्थिर काष्ठा v4l2_event vicodec_eos_event = अणु
	.type = V4L2_EVENT_EOS
पूर्ण;

अटल अंतरभूत काष्ठा vicodec_ctx *file2ctx(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा vicodec_ctx, fh);
पूर्ण

अटल काष्ठा vicodec_q_data *get_q_data(काष्ठा vicodec_ctx *ctx,
					 क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		वापस &ctx->q_data[V4L2_M2M_SRC];
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		वापस &ctx->q_data[V4L2_M2M_DST];
	शेष:
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम copy_cap_to_ref(स्थिर u8 *cap, स्थिर काष्ठा v4l2_fwht_pixfmt_info *info,
		काष्ठा v4l2_fwht_state *state)
अणु
	पूर्णांक plane_idx;
	u8 *p_ref = state->ref_frame.buf;
	अचिन्हित पूर्णांक cap_stride = state->stride;
	अचिन्हित पूर्णांक ref_stride = state->ref_stride;

	क्रम (plane_idx = 0; plane_idx < info->planes_num; plane_idx++) अणु
		पूर्णांक i;
		अचिन्हित पूर्णांक h_भाग = (plane_idx == 1 || plane_idx == 2) ?
			info->height_भाग : 1;
		स्थिर u8 *row_cap = cap;
		u8 *row_ref = p_ref;

		अगर (info->planes_num == 3 && plane_idx == 1) अणु
			cap_stride /= 2;
			ref_stride /= 2;
		पूर्ण

		अगर (plane_idx == 1 &&
		    (info->id == V4L2_PIX_FMT_NV24 ||
		     info->id == V4L2_PIX_FMT_NV42)) अणु
			cap_stride *= 2;
			ref_stride *= 2;
		पूर्ण

		क्रम (i = 0; i < state->visible_height / h_भाग; i++) अणु
			स_नकल(row_ref, row_cap, ref_stride);
			row_ref += ref_stride;
			row_cap += cap_stride;
		पूर्ण
		cap += cap_stride * (state->coded_height / h_भाग);
		p_ref += ref_stride * (state->coded_height / h_भाग);
	पूर्ण
पूर्ण

अटल bool validate_by_version(अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक version)
अणु
	अगर (!version || version > V4L2_FWHT_VERSION)
		वापस false;

	अगर (version >= 2) अणु
		अचिन्हित पूर्णांक components_num = 1 +
			((flags & V4L2_FWHT_FL_COMPONENTS_NUM_MSK) >>
			 V4L2_FWHT_FL_COMPONENTS_NUM_OFFSET);
		अचिन्हित पूर्णांक pixenc = flags & V4L2_FWHT_FL_PIXENC_MSK;

		अगर (components_num == 0 || components_num > 4 || !pixenc)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool validate_stateless_params_flags(स्थिर काष्ठा v4l2_ctrl_fwht_params *params,
					    स्थिर काष्ठा v4l2_fwht_pixfmt_info *cur_info)
अणु
	अचिन्हित पूर्णांक width_भाग =
		(params->flags & V4L2_FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	अचिन्हित पूर्णांक height_भाग =
		(params->flags & V4L2_FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;
	अचिन्हित पूर्णांक components_num = 3;
	अचिन्हित पूर्णांक pixenc = 0;

	अगर (params->version < 3)
		वापस false;

	components_num = 1 + ((params->flags & V4L2_FWHT_FL_COMPONENTS_NUM_MSK) >>
			      V4L2_FWHT_FL_COMPONENTS_NUM_OFFSET);
	pixenc = (params->flags & V4L2_FWHT_FL_PIXENC_MSK);
	अगर (v4l2_fwht_validate_fmt(cur_info, width_भाग, height_भाग,
				    components_num, pixenc))
		वापस true;
	वापस false;
पूर्ण


अटल व्योम update_state_from_header(काष्ठा vicodec_ctx *ctx)
अणु
	स्थिर काष्ठा fwht_cframe_hdr *p_hdr = &ctx->state.header;

	ctx->state.visible_width = ntohl(p_hdr->width);
	ctx->state.visible_height = ntohl(p_hdr->height);
	ctx->state.colorspace = ntohl(p_hdr->colorspace);
	ctx->state.xfer_func = ntohl(p_hdr->xfer_func);
	ctx->state.ycbcr_enc = ntohl(p_hdr->ycbcr_enc);
	ctx->state.quantization = ntohl(p_hdr->quantization);
पूर्ण

अटल पूर्णांक device_process(काष्ठा vicodec_ctx *ctx,
			  काष्ठा vb2_v4l2_buffer *src_vb,
			  काष्ठा vb2_v4l2_buffer *dst_vb)
अणु
	काष्ठा vicodec_dev *dev = ctx->dev;
	काष्ठा v4l2_fwht_state *state = &ctx->state;
	u8 *p_src, *p_dst;
	पूर्णांक ret = 0;

	अगर (ctx->is_enc || ctx->is_stateless)
		p_src = vb2_plane_vaddr(&src_vb->vb2_buf, 0);
	अन्यथा
		p_src = state->compressed_frame;

	अगर (ctx->is_stateless) अणु
		काष्ठा media_request *src_req = src_vb->vb2_buf.req_obj.req;

		ret = v4l2_ctrl_request_setup(src_req, &ctx->hdl);
		अगर (ret)
			वापस ret;
		update_state_from_header(ctx);

		ctx->state.header.size =
			htonl(vb2_get_plane_payload(&src_vb->vb2_buf, 0));
		/*
		 * set the reference buffer from the reference बारtamp
		 * only अगर this is a P-frame
		 */
		अगर (!(ntohl(ctx->state.header.flags) & V4L2_FWHT_FL_I_FRAME)) अणु
			काष्ठा vb2_buffer *ref_vb2_buf;
			पूर्णांक ref_buf_idx;
			काष्ठा vb2_queue *vq_cap =
				v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
						V4L2_BUF_TYPE_VIDEO_CAPTURE);

			ref_buf_idx = vb2_find_बारtamp(vq_cap,
							 ctx->state.ref_frame_ts, 0);
			अगर (ref_buf_idx < 0)
				वापस -EINVAL;

			ref_vb2_buf = vq_cap->bufs[ref_buf_idx];
			अगर (ref_vb2_buf->state == VB2_BUF_STATE_ERROR)
				ret = -EINVAL;
			ctx->state.ref_frame.buf =
				vb2_plane_vaddr(ref_vb2_buf, 0);
		पूर्ण अन्यथा अणु
			ctx->state.ref_frame.buf = शून्य;
		पूर्ण
	पूर्ण
	p_dst = vb2_plane_vaddr(&dst_vb->vb2_buf, 0);
	अगर (!p_src || !p_dst) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Acquiring kernel pointers to buffers failed\n");
		वापस -EFAULT;
	पूर्ण

	अगर (ctx->is_enc) अणु
		काष्ठा vicodec_q_data *q_src;
		पूर्णांक comp_sz_or_errcode;

		q_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		state->info = q_src->info;
		comp_sz_or_errcode = v4l2_fwht_encode(state, p_src, p_dst);
		अगर (comp_sz_or_errcode < 0)
			वापस comp_sz_or_errcode;
		vb2_set_plane_payload(&dst_vb->vb2_buf, 0, comp_sz_or_errcode);
	पूर्ण अन्यथा अणु
		काष्ठा vicodec_q_data *q_dst;
		अचिन्हित पूर्णांक comp_frame_size = ntohl(ctx->state.header.size);

		q_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		अगर (comp_frame_size > ctx->comp_max_size)
			वापस -EINVAL;
		state->info = q_dst->info;
		ret = v4l2_fwht_decode(state, p_src, p_dst);
		अगर (ret < 0)
			वापस ret;
		अगर (!ctx->is_stateless)
			copy_cap_to_ref(p_dst, ctx->state.info, &ctx->state);

		vb2_set_plane_payload(&dst_vb->vb2_buf, 0, q_dst->sizeimage);
		अगर (ntohl(ctx->state.header.flags) & V4L2_FWHT_FL_I_FRAME)
			dst_vb->flags |= V4L2_BUF_FLAG_KEYFRAME;
		अन्यथा
			dst_vb->flags |= V4L2_BUF_FLAG_PFRAME;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * mem2mem callbacks
 */
अटल क्रमागत vb2_buffer_state get_next_header(काष्ठा vicodec_ctx *ctx,
					     u8 **pp, u32 sz)
अणु
	अटल स्थिर u8 magic[] = अणु
		0x4f, 0x4f, 0x4f, 0x4f, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	u8 *p = *pp;
	u32 state;
	u8 *header = (u8 *)&ctx->state.header;

	state = VB2_BUF_STATE_DONE;

	अगर (!ctx->header_size) अणु
		state = VB2_BUF_STATE_ERROR;
		क्रम (; p < *pp + sz; p++) अणु
			u32 copy;

			p = स_प्रथम(p, magic[ctx->comp_magic_cnt],
				   *pp + sz - p);
			अगर (!p) अणु
				ctx->comp_magic_cnt = 0;
				p = *pp + sz;
				अवरोध;
			पूर्ण
			copy = माप(magic) - ctx->comp_magic_cnt;
			अगर (*pp + sz - p < copy)
				copy = *pp + sz - p;

			स_नकल(header + ctx->comp_magic_cnt, p, copy);
			ctx->comp_magic_cnt += copy;
			अगर (!स_भेद(header, magic, ctx->comp_magic_cnt)) अणु
				p += copy;
				state = VB2_BUF_STATE_DONE;
				अवरोध;
			पूर्ण
			ctx->comp_magic_cnt = 0;
		पूर्ण
		अगर (ctx->comp_magic_cnt < माप(magic)) अणु
			*pp = p;
			वापस state;
		पूर्ण
		ctx->header_size = माप(magic);
	पूर्ण

	अगर (ctx->header_size < माप(काष्ठा fwht_cframe_hdr)) अणु
		u32 copy = माप(काष्ठा fwht_cframe_hdr) - ctx->header_size;

		अगर (*pp + sz - p < copy)
			copy = *pp + sz - p;

		स_नकल(header + ctx->header_size, p, copy);
		p += copy;
		ctx->header_size += copy;
	पूर्ण
	*pp = p;
	वापस state;
पूर्ण

/* device_run() - prepares and starts the device */
अटल व्योम device_run(व्योम *priv)
अणु
	काष्ठा vicodec_ctx *ctx = priv;
	काष्ठा vicodec_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा vicodec_q_data *q_src, *q_dst;
	u32 state;
	काष्ठा media_request *src_req;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	src_req = src_buf->vb2_buf.req_obj.req;

	q_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	state = VB2_BUF_STATE_DONE;
	अगर (device_process(ctx, src_buf, dst_buf))
		state = VB2_BUF_STATE_ERROR;
	अन्यथा
		dst_buf->sequence = q_dst->sequence++;
	dst_buf->flags &= ~V4L2_BUF_FLAG_LAST;
	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, false);

	spin_lock(ctx->lock);
	अगर (!ctx->comp_has_next_frame &&
	    v4l2_m2m_is_last_draining_src_buf(ctx->fh.m2m_ctx, src_buf)) अणु
		dst_buf->flags |= V4L2_BUF_FLAG_LAST;
		v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);
		v4l2_m2m_mark_stopped(ctx->fh.m2m_ctx);
	पूर्ण
	अगर (ctx->is_enc || ctx->is_stateless) अणु
		src_buf->sequence = q_src->sequence++;
		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		v4l2_m2m_buf_करोne(src_buf, state);
	पूर्ण अन्यथा अगर (vb2_get_plane_payload(&src_buf->vb2_buf, 0) == ctx->cur_buf_offset) अणु
		src_buf->sequence = q_src->sequence++;
		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		v4l2_m2m_buf_करोne(src_buf, state);
		ctx->cur_buf_offset = 0;
		ctx->comp_has_next_frame = false;
	पूर्ण
	v4l2_m2m_buf_करोne(dst_buf, state);

	ctx->comp_size = 0;
	ctx->header_size = 0;
	ctx->comp_magic_cnt = 0;
	ctx->comp_has_frame = false;
	spin_unlock(ctx->lock);
	अगर (ctx->is_stateless && src_req)
		v4l2_ctrl_request_complete(src_req, &ctx->hdl);

	अगर (ctx->is_enc)
		v4l2_m2m_job_finish(dev->stateful_enc.m2m_dev, ctx->fh.m2m_ctx);
	अन्यथा अगर (ctx->is_stateless)
		v4l2_m2m_job_finish(dev->stateless_dec.m2m_dev,
				    ctx->fh.m2m_ctx);
	अन्यथा
		v4l2_m2m_job_finish(dev->stateful_dec.m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम job_हटाओ_src_buf(काष्ठा vicodec_ctx *ctx, u32 state)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf;
	काष्ठा vicodec_q_data *q_src;

	q_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	spin_lock(ctx->lock);
	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	src_buf->sequence = q_src->sequence++;
	v4l2_m2m_buf_करोne(src_buf, state);
	ctx->cur_buf_offset = 0;
	spin_unlock(ctx->lock);
पूर्ण

अटल स्थिर काष्ठा v4l2_fwht_pixfmt_info *
info_from_header(स्थिर काष्ठा fwht_cframe_hdr *p_hdr)
अणु
	अचिन्हित पूर्णांक flags = ntohl(p_hdr->flags);
	अचिन्हित पूर्णांक width_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	अचिन्हित पूर्णांक height_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;
	अचिन्हित पूर्णांक components_num = 3;
	अचिन्हित पूर्णांक pixenc = 0;
	अचिन्हित पूर्णांक version = ntohl(p_hdr->version);

	अगर (version >= 2) अणु
		components_num = 1 + ((flags & V4L2_FWHT_FL_COMPONENTS_NUM_MSK) >>
				V4L2_FWHT_FL_COMPONENTS_NUM_OFFSET);
		pixenc = (flags & V4L2_FWHT_FL_PIXENC_MSK);
	पूर्ण
	वापस v4l2_fwht_find_nth_fmt(width_भाग, height_भाग,
				     components_num, pixenc, 0);
पूर्ण

अटल bool is_header_valid(स्थिर काष्ठा fwht_cframe_hdr *p_hdr)
अणु
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info;
	अचिन्हित पूर्णांक w = ntohl(p_hdr->width);
	अचिन्हित पूर्णांक h = ntohl(p_hdr->height);
	अचिन्हित पूर्णांक version = ntohl(p_hdr->version);
	अचिन्हित पूर्णांक flags = ntohl(p_hdr->flags);

	अगर (w < MIN_WIDTH || w > MAX_WIDTH || h < MIN_HEIGHT || h > MAX_HEIGHT)
		वापस false;

	अगर (!validate_by_version(flags, version))
		वापस false;

	info = info_from_header(p_hdr);
	अगर (!info)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम update_capture_data_from_header(काष्ठा vicodec_ctx *ctx)
अणु
	काष्ठा vicodec_q_data *q_dst = get_q_data(ctx,
						  V4L2_BUF_TYPE_VIDEO_CAPTURE);
	स्थिर काष्ठा fwht_cframe_hdr *p_hdr = &ctx->state.header;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info = info_from_header(p_hdr);
	अचिन्हित पूर्णांक flags = ntohl(p_hdr->flags);
	अचिन्हित पूर्णांक hdr_width_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	अचिन्हित पूर्णांक hdr_height_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;

	/*
	 * This function should not be used by a stateless codec since
	 * it changes values in q_data that are not request specअगरic
	 */
	WARN_ON(ctx->is_stateless);

	q_dst->info = info;
	q_dst->visible_width = ntohl(p_hdr->width);
	q_dst->visible_height = ntohl(p_hdr->height);
	q_dst->coded_width = vic_round_dim(q_dst->visible_width, hdr_width_भाग);
	q_dst->coded_height = vic_round_dim(q_dst->visible_height,
					    hdr_height_भाग);

	q_dst->sizeimage = q_dst->coded_width * q_dst->coded_height *
		q_dst->info->sizeimage_mult / q_dst->info->sizeimage_भाग;
	ctx->state.colorspace = ntohl(p_hdr->colorspace);

	ctx->state.xfer_func = ntohl(p_hdr->xfer_func);
	ctx->state.ycbcr_enc = ntohl(p_hdr->ycbcr_enc);
	ctx->state.quantization = ntohl(p_hdr->quantization);
पूर्ण

अटल व्योम set_last_buffer(काष्ठा vb2_v4l2_buffer *dst_buf,
			    स्थिर काष्ठा vb2_v4l2_buffer *src_buf,
			    काष्ठा vicodec_ctx *ctx)
अणु
	काष्ठा vicodec_q_data *q_dst = get_q_data(ctx,
						  V4L2_BUF_TYPE_VIDEO_CAPTURE);

	vb2_set_plane_payload(&dst_buf->vb2_buf, 0, 0);
	dst_buf->sequence = q_dst->sequence++;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, !ctx->is_enc);
	dst_buf->flags |= V4L2_BUF_FLAG_LAST;
	v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);
पूर्ण

अटल पूर्णांक job_पढ़ोy(व्योम *priv)
अणु
	अटल स्थिर u8 magic[] = अणु
		0x4f, 0x4f, 0x4f, 0x4f, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	काष्ठा vicodec_ctx *ctx = priv;
	काष्ठा vb2_v4l2_buffer *src_buf;
	u8 *p_src;
	u8 *p;
	u32 sz;
	u32 state;
	काष्ठा vicodec_q_data *q_dst = get_q_data(ctx,
						  V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक hdr_width_भाग;
	अचिन्हित पूर्णांक hdr_height_भाग;
	अचिन्हित पूर्णांक max_to_copy;
	अचिन्हित पूर्णांक comp_frame_size;

	अगर (ctx->source_changed)
		वापस 0;
	अगर (ctx->is_stateless || ctx->is_enc || ctx->comp_has_frame)
		वापस 1;

restart:
	ctx->comp_has_next_frame = false;
	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	अगर (!src_buf)
		वापस 0;
	p_src = vb2_plane_vaddr(&src_buf->vb2_buf, 0);
	sz = vb2_get_plane_payload(&src_buf->vb2_buf, 0);
	p = p_src + ctx->cur_buf_offset;

	state = VB2_BUF_STATE_DONE;

	अगर (ctx->header_size < माप(काष्ठा fwht_cframe_hdr)) अणु
		state = get_next_header(ctx, &p, p_src + sz - p);
		अगर (ctx->header_size < माप(काष्ठा fwht_cframe_hdr)) अणु
			अगर (v4l2_m2m_is_last_draining_src_buf(ctx->fh.m2m_ctx,
							      src_buf))
				वापस 1;
			job_हटाओ_src_buf(ctx, state);
			जाओ restart;
		पूर्ण
	पूर्ण

	comp_frame_size = ntohl(ctx->state.header.size);

	/*
	 * The current scanned frame might be the first frame of a new
	 * resolution so its size might be larger than ctx->comp_max_size.
	 * In that हाल it is copied up to the current buffer capacity and
	 * the copy will जारी after allocating new large enough buffer
	 * when restreaming
	 */
	max_to_copy = min(comp_frame_size, ctx->comp_max_size);

	अगर (ctx->comp_size < max_to_copy) अणु
		u32 copy = max_to_copy - ctx->comp_size;

		अगर (copy > p_src + sz - p)
			copy = p_src + sz - p;

		स_नकल(ctx->state.compressed_frame + ctx->comp_size,
		       p, copy);
		p += copy;
		ctx->comp_size += copy;
		अगर (ctx->comp_size < max_to_copy) अणु
			अगर (v4l2_m2m_is_last_draining_src_buf(ctx->fh.m2m_ctx,
							      src_buf))
				वापस 1;
			job_हटाओ_src_buf(ctx, state);
			जाओ restart;
		पूर्ण
	पूर्ण
	ctx->cur_buf_offset = p - p_src;
	अगर (ctx->comp_size == comp_frame_size)
		ctx->comp_has_frame = true;
	ctx->comp_has_next_frame = false;
	अगर (ctx->comp_has_frame && sz - ctx->cur_buf_offset >=
			माप(काष्ठा fwht_cframe_hdr)) अणु
		काष्ठा fwht_cframe_hdr *p_hdr = (काष्ठा fwht_cframe_hdr *)p;
		u32 frame_size = ntohl(p_hdr->size);
		u32 reमुख्यing = sz - ctx->cur_buf_offset - माप(*p_hdr);

		अगर (!स_भेद(p, magic, माप(magic)))
			ctx->comp_has_next_frame = reमुख्यing >= frame_size;
	पूर्ण
	/*
	 * अगर the header is invalid the device_run will just drop the frame
	 * with an error
	 */
	अगर (!is_header_valid(&ctx->state.header) && ctx->comp_has_frame)
		वापस 1;
	flags = ntohl(ctx->state.header.flags);
	hdr_width_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	hdr_height_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;

	अगर (ntohl(ctx->state.header.width) != q_dst->visible_width ||
	    ntohl(ctx->state.header.height) != q_dst->visible_height ||
	    !q_dst->info ||
	    hdr_width_भाग != q_dst->info->width_भाग ||
	    hdr_height_भाग != q_dst->info->height_भाग) अणु
		अटल स्थिर काष्ठा v4l2_event rs_event = अणु
			.type = V4L2_EVENT_SOURCE_CHANGE,
			.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
		पूर्ण;

		काष्ठा vb2_v4l2_buffer *dst_buf =
			v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		update_capture_data_from_header(ctx);
		v4l2_event_queue_fh(&ctx->fh, &rs_event);
		set_last_buffer(dst_buf, src_buf, ctx);
		ctx->source_changed = true;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * video ioctls
 */

अटल स्थिर काष्ठा v4l2_fwht_pixfmt_info *find_fmt(u32 fmt)
अणु
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info =
		v4l2_fwht_find_pixfmt(fmt);

	अगर (!info)
		info = v4l2_fwht_get_pixfmt(0);
	वापस info;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, VICODEC_NAME, माप(cap->driver));
	strscpy(cap->card, VICODEC_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
			"platform:%s", VICODEC_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, काष्ठा vicodec_ctx *ctx,
		    bool is_out)
अणु
	bool is_uncomp = (ctx->is_enc && is_out) || (!ctx->is_enc && !is_out);

	अगर (V4L2_TYPE_IS_MULTIPLANAR(f->type) && !multiplanar)
		वापस -EINVAL;
	अगर (!V4L2_TYPE_IS_MULTIPLANAR(f->type) && multiplanar)
		वापस -EINVAL;

	अगर (is_uncomp) अणु
		स्थिर काष्ठा v4l2_fwht_pixfmt_info *info =
					get_q_data(ctx, f->type)->info;

		अगर (ctx->is_enc ||
		    !vb2_is_streaming(&ctx->fh.m2m_ctx->cap_q_ctx.q))
			info = v4l2_fwht_get_pixfmt(f->index);
		अन्यथा
			info = v4l2_fwht_find_nth_fmt(info->width_भाग,
						     info->height_भाग,
						     info->components_num,
						     info->pixenc,
						     f->index);
		अगर (!info)
			वापस -EINVAL;
		f->pixelक्रमmat = info->id;
	पूर्ण अन्यथा अणु
		अगर (f->index)
			वापस -EINVAL;
		f->pixelक्रमmat = ctx->is_stateless ?
			V4L2_PIX_FMT_FWHT_STATELESS : V4L2_PIX_FMT_FWHT;
		अगर (!ctx->is_enc && !ctx->is_stateless)
			f->flags = V4L2_FMT_FLAG_DYN_RESOLUTION |
				   V4L2_FMT_FLAG_CONTINUOUS_BYTESTREAM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);

	वापस क्रमागत_fmt(f, ctx, false);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);

	वापस क्रमागत_fmt(f, ctx, true);
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा vicodec_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा vicodec_q_data *q_data;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा v4l2_pix_क्रमmat *pix;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	info = q_data->info;

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (multiplanar)
			वापस -EINVAL;
		pix = &f->fmt.pix;
		pix->width = q_data->coded_width;
		pix->height = q_data->coded_height;
		pix->field = V4L2_FIELD_NONE;
		pix->pixelक्रमmat = info->id;
		pix->bytesperline = q_data->coded_width *
					info->bytesperline_mult;
		pix->sizeimage = q_data->sizeimage;
		pix->colorspace = ctx->state.colorspace;
		pix->xfer_func = ctx->state.xfer_func;
		pix->ycbcr_enc = ctx->state.ycbcr_enc;
		pix->quantization = ctx->state.quantization;
		अवरोध;

	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		अगर (!multiplanar)
			वापस -EINVAL;
		pix_mp = &f->fmt.pix_mp;
		pix_mp->width = q_data->coded_width;
		pix_mp->height = q_data->coded_height;
		pix_mp->field = V4L2_FIELD_NONE;
		pix_mp->pixelक्रमmat = info->id;
		pix_mp->num_planes = 1;
		pix_mp->plane_fmt[0].bytesperline =
				q_data->coded_width * info->bytesperline_mult;
		pix_mp->plane_fmt[0].sizeimage = q_data->sizeimage;
		pix_mp->colorspace = ctx->state.colorspace;
		pix_mp->xfer_func = ctx->state.xfer_func;
		pix_mp->ycbcr_enc = ctx->state.ycbcr_enc;
		pix_mp->quantization = ctx->state.quantization;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा vicodec_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा v4l2_pix_क्रमmat *pix;
	काष्ठा v4l2_plane_pix_क्रमmat *plane;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info = ctx->is_stateless ?
		&pixfmt_stateless_fwht : &pixfmt_fwht;

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		pix = &f->fmt.pix;
		अगर (pix->pixelक्रमmat != V4L2_PIX_FMT_FWHT &&
		    pix->pixelक्रमmat != V4L2_PIX_FMT_FWHT_STATELESS)
			info = find_fmt(pix->pixelक्रमmat);

		pix->width = clamp(pix->width, MIN_WIDTH, MAX_WIDTH);
		pix->width = vic_round_dim(pix->width, info->width_भाग);

		pix->height = clamp(pix->height, MIN_HEIGHT, MAX_HEIGHT);
		pix->height = vic_round_dim(pix->height, info->height_भाग);

		pix->field = V4L2_FIELD_NONE;
		pix->bytesperline =
			pix->width * info->bytesperline_mult;
		pix->sizeimage = pix->width * pix->height *
			info->sizeimage_mult / info->sizeimage_भाग;
		अगर (pix->pixelक्रमmat == V4L2_PIX_FMT_FWHT)
			pix->sizeimage += माप(काष्ठा fwht_cframe_hdr);
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		pix_mp = &f->fmt.pix_mp;
		plane = pix_mp->plane_fmt;
		अगर (pix_mp->pixelक्रमmat != V4L2_PIX_FMT_FWHT &&
		    pix_mp->pixelक्रमmat != V4L2_PIX_FMT_FWHT_STATELESS)
			info = find_fmt(pix_mp->pixelक्रमmat);
		pix_mp->num_planes = 1;

		pix_mp->width = clamp(pix_mp->width, MIN_WIDTH, MAX_WIDTH);
		pix_mp->width = vic_round_dim(pix_mp->width, info->width_भाग);

		pix_mp->height = clamp(pix_mp->height, MIN_HEIGHT, MAX_HEIGHT);
		pix_mp->height = vic_round_dim(pix_mp->height,
					       info->height_भाग);

		pix_mp->field = V4L2_FIELD_NONE;
		plane->bytesperline =
			pix_mp->width * info->bytesperline_mult;
		plane->sizeimage = pix_mp->width * pix_mp->height *
			info->sizeimage_mult / info->sizeimage_भाग;
		अगर (pix_mp->pixelक्रमmat == V4L2_PIX_FMT_FWHT)
			plane->sizeimage += माप(काष्ठा fwht_cframe_hdr);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा v4l2_pix_क्रमmat *pix;

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर (multiplanar)
			वापस -EINVAL;
		pix = &f->fmt.pix;
		pix->pixelक्रमmat = ctx->is_enc ? V4L2_PIX_FMT_FWHT :
				   find_fmt(f->fmt.pix.pixelक्रमmat)->id;
		pix->colorspace = ctx->state.colorspace;
		pix->xfer_func = ctx->state.xfer_func;
		pix->ycbcr_enc = ctx->state.ycbcr_enc;
		pix->quantization = ctx->state.quantization;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		अगर (!multiplanar)
			वापस -EINVAL;
		pix_mp = &f->fmt.pix_mp;
		pix_mp->pixelक्रमmat = ctx->is_enc ? V4L2_PIX_FMT_FWHT :
				      find_fmt(pix_mp->pixelक्रमmat)->id;
		pix_mp->colorspace = ctx->state.colorspace;
		pix_mp->xfer_func = ctx->state.xfer_func;
		pix_mp->ycbcr_enc = ctx->state.ycbcr_enc;
		pix_mp->quantization = ctx->state.quantization;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस vidioc_try_fmt(ctx, f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा v4l2_pix_क्रमmat *pix;

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (multiplanar)
			वापस -EINVAL;
		pix = &f->fmt.pix;
		अगर (ctx->is_enc)
			pix->pixelक्रमmat = find_fmt(pix->pixelक्रमmat)->id;
		अन्यथा अगर (ctx->is_stateless)
			pix->pixelक्रमmat = V4L2_PIX_FMT_FWHT_STATELESS;
		अन्यथा
			pix->pixelक्रमmat = V4L2_PIX_FMT_FWHT;
		अगर (!pix->colorspace)
			pix->colorspace = V4L2_COLORSPACE_REC709;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		अगर (!multiplanar)
			वापस -EINVAL;
		pix_mp = &f->fmt.pix_mp;
		अगर (ctx->is_enc)
			pix_mp->pixelक्रमmat = find_fmt(pix_mp->pixelक्रमmat)->id;
		अन्यथा अगर (ctx->is_stateless)
			pix_mp->pixelक्रमmat = V4L2_PIX_FMT_FWHT_STATELESS;
		अन्यथा
			pix_mp->pixelक्रमmat = V4L2_PIX_FMT_FWHT;
		अगर (!pix_mp->colorspace)
			pix_mp->colorspace = V4L2_COLORSPACE_REC709;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस vidioc_try_fmt(ctx, f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा vicodec_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vicodec_q_data *q_data;
	काष्ठा vb2_queue *vq;
	bool fmt_changed = true;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा v4l2_pix_क्रमmat *pix;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		pix = &f->fmt.pix;
		अगर (ctx->is_enc && V4L2_TYPE_IS_OUTPUT(f->type))
			fmt_changed =
				!q_data->info ||
				q_data->info->id != pix->pixelक्रमmat ||
				q_data->coded_width != pix->width ||
				q_data->coded_height != pix->height;

		अगर (vb2_is_busy(vq) && fmt_changed)
			वापस -EBUSY;

		अगर (pix->pixelक्रमmat == V4L2_PIX_FMT_FWHT)
			q_data->info = &pixfmt_fwht;
		अन्यथा अगर (pix->pixelक्रमmat == V4L2_PIX_FMT_FWHT_STATELESS)
			q_data->info = &pixfmt_stateless_fwht;
		अन्यथा
			q_data->info = find_fmt(pix->pixelक्रमmat);
		q_data->coded_width = pix->width;
		q_data->coded_height = pix->height;
		q_data->sizeimage = pix->sizeimage;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		pix_mp = &f->fmt.pix_mp;
		अगर (ctx->is_enc && V4L2_TYPE_IS_OUTPUT(f->type))
			fmt_changed =
				!q_data->info ||
				q_data->info->id != pix_mp->pixelक्रमmat ||
				q_data->coded_width != pix_mp->width ||
				q_data->coded_height != pix_mp->height;

		अगर (vb2_is_busy(vq) && fmt_changed)
			वापस -EBUSY;

		अगर (pix_mp->pixelक्रमmat == V4L2_PIX_FMT_FWHT)
			q_data->info = &pixfmt_fwht;
		अन्यथा अगर (pix_mp->pixelक्रमmat == V4L2_PIX_FMT_FWHT_STATELESS)
			q_data->info = &pixfmt_stateless_fwht;
		अन्यथा
			q_data->info = find_fmt(pix_mp->pixelक्रमmat);
		q_data->coded_width = pix_mp->width;
		q_data->coded_height = pix_mp->height;
		q_data->sizeimage = pix_mp->plane_fmt[0].sizeimage;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(ctx->dev,
		"Setting format for type %d, coded wxh: %dx%d, fourcc: 0x%08x\n",
		f->type, q_data->coded_width, q_data->coded_height,
		q_data->info->id);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस vidioc_s_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	काष्ठा vicodec_q_data *q_data;
	काष्ठा vicodec_q_data *q_data_cap;
	काष्ठा v4l2_pix_क्रमmat *pix;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	u32 coded_w = 0, coded_h = 0;
	अचिन्हित पूर्णांक size = 0;
	पूर्णांक ret;

	q_data = get_q_data(ctx, f->type);
	q_data_cap = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	ret = vidioc_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	अगर (ctx->is_enc) अणु
		काष्ठा vb2_queue *vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
		काष्ठा vb2_queue *vq_cap = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
							   V4L2_BUF_TYPE_VIDEO_CAPTURE);
		स्थिर काष्ठा v4l2_fwht_pixfmt_info *info = ctx->is_stateless ?
			&pixfmt_stateless_fwht : &pixfmt_fwht;

		अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
			coded_w = f->fmt.pix.width;
			coded_h = f->fmt.pix.height;
		पूर्ण अन्यथा अणु
			coded_w = f->fmt.pix_mp.width;
			coded_h = f->fmt.pix_mp.height;
		पूर्ण
		अगर (vb2_is_busy(vq) && (coded_w != q_data->coded_width ||
					coded_h != q_data->coded_height))
			वापस -EBUSY;
		size = coded_w * coded_h *
			info->sizeimage_mult / info->sizeimage_भाग;
		अगर (!ctx->is_stateless)
			size += माप(काष्ठा fwht_cframe_hdr);

		अगर (vb2_is_busy(vq_cap) && size > q_data_cap->sizeimage)
			वापस -EBUSY;
	पूर्ण

	ret = vidioc_s_fmt(file2ctx(file), f);
	अगर (!ret) अणु
		अगर (ctx->is_enc) अणु
			q_data->visible_width = coded_w;
			q_data->visible_height = coded_h;
			q_data_cap->coded_width = coded_w;
			q_data_cap->coded_height = coded_h;
			q_data_cap->sizeimage = size;
		पूर्ण

		चयन (f->type) अणु
		हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
			pix = &f->fmt.pix;
			ctx->state.colorspace = pix->colorspace;
			ctx->state.xfer_func = pix->xfer_func;
			ctx->state.ycbcr_enc = pix->ycbcr_enc;
			ctx->state.quantization = pix->quantization;
			अवरोध;
		हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
			pix_mp = &f->fmt.pix_mp;
			ctx->state.colorspace = pix_mp->colorspace;
			ctx->state.xfer_func = pix_mp->xfer_func;
			ctx->state.ycbcr_enc = pix_mp->ycbcr_enc;
			ctx->state.quantization = pix_mp->quantization;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	काष्ठा vicodec_q_data *q_data;

	q_data = get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;
	/*
	 * encoder supports only cropping on the OUTPUT buffer
	 * decoder supports only composing on the CAPTURE buffer
	 */
	अगर (ctx->is_enc && s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		चयन (s->target) अणु
		हाल V4L2_SEL_TGT_CROP:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->visible_width;
			s->r.height = q_data->visible_height;
			वापस 0;
		हाल V4L2_SEL_TGT_CROP_DEFAULT:
		हाल V4L2_SEL_TGT_CROP_BOUNDS:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->coded_width;
			s->r.height = q_data->coded_height;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!ctx->is_enc && s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		चयन (s->target) अणु
		हाल V4L2_SEL_TGT_COMPOSE:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->visible_width;
			s->r.height = q_data->visible_height;
			वापस 0;
		हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->coded_width;
			s->r.height = q_data->coded_height;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_s_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	काष्ठा vicodec_q_data *q_data;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	q_data = get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर (!ctx->is_enc || s->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	s->r.left = 0;
	s->r.top = 0;
	q_data->visible_width = clamp(s->r.width, MIN_WIDTH,
				      q_data->coded_width);
	s->r.width = q_data->visible_width;
	q_data->visible_height = clamp(s->r.height, MIN_HEIGHT,
				       q_data->coded_height);
	s->r.height = q_data->visible_height;
	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_encoder_cmd(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_encoder_cmd *ec)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_try_encoder_cmd(file, fh, ec);
	अगर (ret < 0)
		वापस ret;

	अगर (!vb2_is_streaming(&ctx->fh.m2m_ctx->cap_q_ctx.q) ||
	    !vb2_is_streaming(&ctx->fh.m2m_ctx->out_q_ctx.q))
		वापस 0;

	ret = v4l2_m2m_ioctl_encoder_cmd(file, fh, ec);
	अगर (ret < 0)
		वापस ret;

	अगर (ec->cmd == V4L2_ENC_CMD_STOP &&
	    v4l2_m2m_has_stopped(ctx->fh.m2m_ctx))
		v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);

	अगर (ec->cmd == V4L2_ENC_CMD_START &&
	    v4l2_m2m_has_stopped(ctx->fh.m2m_ctx))
		vb2_clear_last_buffer_dequeued(&ctx->fh.m2m_ctx->cap_q_ctx.q);

	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_decoder_cmd(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_decoder_cmd *dc)
अणु
	काष्ठा vicodec_ctx *ctx = file2ctx(file);
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_try_decoder_cmd(file, fh, dc);
	अगर (ret < 0)
		वापस ret;

	अगर (!vb2_is_streaming(&ctx->fh.m2m_ctx->cap_q_ctx.q) ||
	    !vb2_is_streaming(&ctx->fh.m2m_ctx->out_q_ctx.q))
		वापस 0;

	ret = v4l2_m2m_ioctl_decoder_cmd(file, fh, dc);
	अगर (ret < 0)
		वापस ret;

	अगर (dc->cmd == V4L2_DEC_CMD_STOP &&
	    v4l2_m2m_has_stopped(ctx->fh.m2m_ctx))
		v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);

	अगर (dc->cmd == V4L2_DEC_CMD_START &&
	    v4l2_m2m_has_stopped(ctx->fh.m2m_ctx))
		vb2_clear_last_buffer_dequeued(&ctx->fh.m2m_ctx->cap_q_ctx.q);

	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	चयन (fsize->pixel_क्रमmat) अणु
	हाल V4L2_PIX_FMT_FWHT_STATELESS:
		अवरोध;
	हाल V4L2_PIX_FMT_FWHT:
		अवरोध;
	शेष:
		अगर (find_fmt(fsize->pixel_क्रमmat)->id == fsize->pixel_क्रमmat)
			अवरोध;
		वापस -EINVAL;
	पूर्ण

	अगर (fsize->index)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;

	fsize->stepwise.min_width = MIN_WIDTH;
	fsize->stepwise.max_width = MAX_WIDTH;
	fsize->stepwise.step_width = 8;
	fsize->stepwise.min_height = MIN_HEIGHT;
	fsize->stepwise.max_height = MAX_HEIGHT;
	fsize->stepwise.step_height = 8;

	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	काष्ठा vicodec_ctx *ctx = container_of(fh, काष्ठा vicodec_ctx, fh);

	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		अगर (ctx->is_enc)
			वापस -EINVAL;
		fallthrough;
	हाल V4L2_EVENT_EOS:
		अगर (ctx->is_stateless)
			वापस -EINVAL;
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops vicodec_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,

	.vidioc_g_fmt_vid_cap_mplane	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap_mplane	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mplane	= vidioc_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out	= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= vidioc_s_fmt_vid_out,

	.vidioc_g_fmt_vid_out_mplane	= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out_mplane	= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out_mplane	= vidioc_s_fmt_vid_out,

	.vidioc_reqbufs		= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf		= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf		= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf	= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs	= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon	= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,

	.vidioc_g_selection	= vidioc_g_selection,
	.vidioc_s_selection	= vidioc_s_selection,

	.vidioc_try_encoder_cmd	= v4l2_m2m_ioctl_try_encoder_cmd,
	.vidioc_encoder_cmd	= vicodec_encoder_cmd,
	.vidioc_try_decoder_cmd	= v4l2_m2m_ioctl_try_decoder_cmd,
	.vidioc_decoder_cmd	= vicodec_decoder_cmd,
	.vidioc_क्रमागत_framesizes = vicodec_क्रमागत_framesizes,

	.vidioc_subscribe_event = vicodec_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;


/*
 * Queue operations
 */

अटल पूर्णांक vicodec_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
			       अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			       काष्ठा device *alloc_devs[])
अणु
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vicodec_q_data *q_data = get_q_data(ctx, vq->type);
	अचिन्हित पूर्णांक size = q_data->sizeimage;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;
	q_data->vb2_sizeimage = size;
	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vicodec_q_data *q_data;

	dprपूर्णांकk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			dprपूर्णांकk(ctx->dev, "%s field isn't supported\n",
					__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (vb2_plane_size(vb, 0) < q_data->vb2_sizeimage) अणु
		dprपूर्णांकk(ctx->dev,
			"%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0),
			(दीर्घ)q_data->vb2_sizeimage);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vicodec_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित पूर्णांक sz = vb2_get_plane_payload(&vbuf->vb2_buf, 0);
	u8 *p_src = vb2_plane_vaddr(&vbuf->vb2_buf, 0);
	u8 *p = p_src;
	काष्ठा vb2_queue *vq_out = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
						   V4L2_BUF_TYPE_VIDEO_OUTPUT);
	काष्ठा vb2_queue *vq_cap = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
						   V4L2_BUF_TYPE_VIDEO_CAPTURE);
	bool header_valid = false;
	अटल स्थिर काष्ठा v4l2_event rs_event = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
	पूर्ण;

	अगर (V4L2_TYPE_IS_CAPTURE(vb->vb2_queue->type) &&
	    vb2_is_streaming(vb->vb2_queue) &&
	    v4l2_m2m_dst_buf_is_last(ctx->fh.m2m_ctx)) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < vb->num_planes; i++)
			vb->planes[i].bytesused = 0;

		vbuf->field = V4L2_FIELD_NONE;
		vbuf->sequence =
			get_q_data(ctx, vb->vb2_queue->type)->sequence++;

		v4l2_m2m_last_buffer_करोne(ctx->fh.m2m_ctx, vbuf);
		v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);
		वापस;
	पूर्ण

	/* buf_queue handles only the first source change event */
	अगर (ctx->first_source_change_sent) अणु
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		वापस;
	पूर्ण

	/*
	 * अगर both queues are streaming, the source change event is
	 * handled in job_पढ़ोy
	 */
	अगर (vb2_is_streaming(vq_cap) && vb2_is_streaming(vq_out)) अणु
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		वापस;
	पूर्ण

	/*
	 * source change event is relevant only क्रम the stateful decoder
	 * in the compressed stream
	 */
	अगर (ctx->is_stateless || ctx->is_enc ||
	    V4L2_TYPE_IS_CAPTURE(vb->vb2_queue->type)) अणु
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		वापस;
	पूर्ण

	करो अणु
		क्रमागत vb2_buffer_state state =
			get_next_header(ctx, &p, p_src + sz - p);

		अगर (ctx->header_size < माप(काष्ठा fwht_cframe_hdr)) अणु
			v4l2_m2m_buf_करोne(vbuf, state);
			वापस;
		पूर्ण
		header_valid = is_header_valid(&ctx->state.header);
		/*
		 * p poपूर्णांकs right after the end of the header in the
		 * buffer. If the header is invalid we set p to poपूर्णांक
		 * to the next byte after the start of the header
		 */
		अगर (!header_valid) अणु
			p = p - माप(काष्ठा fwht_cframe_hdr) + 1;
			अगर (p < p_src)
				p = p_src;
			ctx->header_size = 0;
			ctx->comp_magic_cnt = 0;
		पूर्ण

	पूर्ण जबतक (!header_valid);

	ctx->cur_buf_offset = p - p_src;
	update_capture_data_from_header(ctx);
	ctx->first_source_change_sent = true;
	v4l2_event_queue_fh(&ctx->fh, &rs_event);
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल व्योम vicodec_वापस_bufs(काष्ठा vb2_queue *q, u32 state)
अणु
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (vbuf == शून्य)
			वापस;
		v4l2_ctrl_request_complete(vbuf->vb2_buf.req_obj.req,
					   &ctx->hdl);
		spin_lock(ctx->lock);
		v4l2_m2m_buf_करोne(vbuf, state);
		spin_unlock(ctx->lock);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक total_frame_size(काष्ठा vicodec_q_data *q_data)
अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक chroma_भाग;

	अगर (!q_data->info) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	size = q_data->coded_width * q_data->coded_height;
	chroma_भाग = q_data->info->width_भाग * q_data->info->height_भाग;

	अगर (q_data->info->components_num == 4)
		वापस 2 * size + 2 * (size / chroma_भाग);
	अन्यथा अगर (q_data->info->components_num == 3)
		वापस size + 2 * (size / chroma_भाग);
	वापस size;
पूर्ण

अटल पूर्णांक vicodec_start_streaming(काष्ठा vb2_queue *q,
				   अचिन्हित पूर्णांक count)
अणु
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vicodec_q_data *q_data = get_q_data(ctx, q->type);
	काष्ठा v4l2_fwht_state *state = &ctx->state;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info = q_data->info;
	अचिन्हित पूर्णांक size = q_data->coded_width * q_data->coded_height;
	अचिन्हित पूर्णांक chroma_भाग;
	अचिन्हित पूर्णांक total_planes_size;
	u8 *new_comp_frame = शून्य;

	chroma_भाग = info->width_भाग * info->height_भाग;
	q_data->sequence = 0;

	v4l2_m2m_update_start_streaming_state(ctx->fh.m2m_ctx, q);

	state->gop_cnt = 0;

	अगर ((V4L2_TYPE_IS_OUTPUT(q->type) && !ctx->is_enc) ||
	    (V4L2_TYPE_IS_CAPTURE(q->type) && ctx->is_enc))
		वापस 0;

	अगर (info->id == V4L2_PIX_FMT_FWHT ||
	    info->id == V4L2_PIX_FMT_FWHT_STATELESS) अणु
		vicodec_वापस_bufs(q, VB2_BUF_STATE_QUEUED);
		वापस -EINVAL;
	पूर्ण
	total_planes_size = total_frame_size(q_data);
	ctx->comp_max_size = total_planes_size;

	state->visible_width = q_data->visible_width;
	state->visible_height = q_data->visible_height;
	state->coded_width = q_data->coded_width;
	state->coded_height = q_data->coded_height;
	state->stride = q_data->coded_width *
				info->bytesperline_mult;

	अगर (ctx->is_stateless) अणु
		state->ref_stride = state->stride;
		वापस 0;
	पूर्ण
	state->ref_stride = q_data->coded_width * info->luma_alpha_step;

	state->ref_frame.buf = kvदो_स्मृति(total_planes_size, GFP_KERNEL);
	state->ref_frame.luma = state->ref_frame.buf;
	new_comp_frame = kvदो_स्मृति(ctx->comp_max_size, GFP_KERNEL);

	अगर (!state->ref_frame.luma || !new_comp_frame) अणु
		kvमुक्त(state->ref_frame.luma);
		kvमुक्त(new_comp_frame);
		vicodec_वापस_bufs(q, VB2_BUF_STATE_QUEUED);
		वापस -ENOMEM;
	पूर्ण
	/*
	 * अगर state->compressed_frame was alपढ़ोy allocated then
	 * it contain data of the first frame of the new resolution
	 */
	अगर (state->compressed_frame) अणु
		अगर (ctx->comp_size > ctx->comp_max_size)
			ctx->comp_size = ctx->comp_max_size;

		स_नकल(new_comp_frame,
		       state->compressed_frame, ctx->comp_size);
	पूर्ण

	kvमुक्त(state->compressed_frame);
	state->compressed_frame = new_comp_frame;

	अगर (info->components_num < 3) अणु
		state->ref_frame.cb = शून्य;
		state->ref_frame.cr = शून्य;
		state->ref_frame.alpha = शून्य;
		वापस 0;
	पूर्ण

	state->ref_frame.cb = state->ref_frame.luma + size;
	state->ref_frame.cr = state->ref_frame.cb + size / chroma_भाग;

	अगर (info->components_num == 4)
		state->ref_frame.alpha =
			state->ref_frame.cr + size / chroma_भाग;
	अन्यथा
		state->ref_frame.alpha = शून्य;

	वापस 0;
पूर्ण

अटल व्योम vicodec_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(q);

	vicodec_वापस_bufs(q, VB2_BUF_STATE_ERROR);

	v4l2_m2m_update_stop_streaming_state(ctx->fh.m2m_ctx, q);

	अगर (V4L2_TYPE_IS_OUTPUT(q->type) &&
	    v4l2_m2m_has_stopped(ctx->fh.m2m_ctx))
		v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);

	अगर (!ctx->is_enc && V4L2_TYPE_IS_OUTPUT(q->type))
		ctx->first_source_change_sent = false;

	अगर ((!V4L2_TYPE_IS_OUTPUT(q->type) && !ctx->is_enc) ||
	    (V4L2_TYPE_IS_OUTPUT(q->type) && ctx->is_enc)) अणु
		अगर (!ctx->is_stateless)
			kvमुक्त(ctx->state.ref_frame.buf);
		ctx->state.ref_frame.buf = शून्य;
		ctx->state.ref_frame.luma = शून्य;
		ctx->comp_max_size = 0;
		ctx->source_changed = false;
	पूर्ण
	अगर (V4L2_TYPE_IS_OUTPUT(q->type) && !ctx->is_enc) अणु
		ctx->cur_buf_offset = 0;
		ctx->comp_size = 0;
		ctx->header_size = 0;
		ctx->comp_magic_cnt = 0;
		ctx->comp_has_frame = false;
		ctx->comp_has_next_frame = false;
	पूर्ण
पूर्ण

अटल व्योम vicodec_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vicodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &ctx->hdl);
पूर्ण


अटल स्थिर काष्ठा vb2_ops vicodec_qops = अणु
	.queue_setup		= vicodec_queue_setup,
	.buf_out_validate	= vicodec_buf_out_validate,
	.buf_prepare		= vicodec_buf_prepare,
	.buf_queue		= vicodec_buf_queue,
	.buf_request_complete	= vicodec_buf_request_complete,
	.start_streaming	= vicodec_start_streaming,
	.stop_streaming		= vicodec_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा vicodec_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = (multiplanar ?
			V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE :
			V4L2_BUF_TYPE_VIDEO_OUTPUT);
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &vicodec_qops;
	src_vq->mem_ops = &vb2_vदो_स्मृति_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	अगर (ctx->is_enc)
		src_vq->lock = &ctx->dev->stateful_enc.mutex;
	अन्यथा अगर (ctx->is_stateless)
		src_vq->lock = &ctx->dev->stateless_dec.mutex;
	अन्यथा
		src_vq->lock = &ctx->dev->stateful_dec.mutex;
	src_vq->supports_requests = ctx->is_stateless;
	src_vq->requires_requests = ctx->is_stateless;
	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = (multiplanar ?
			V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE :
			V4L2_BUF_TYPE_VIDEO_CAPTURE);
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &vicodec_qops;
	dst_vq->mem_ops = &vb2_vदो_स्मृति_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = src_vq->lock;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक vicodec_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vicodec_ctx *ctx = container_of(ctrl->handler,
			काष्ठा vicodec_ctx, hdl);
	स्थिर काष्ठा v4l2_ctrl_fwht_params *params;
	काष्ठा vicodec_q_data *q_dst = get_q_data(ctx,
			V4L2_BUF_TYPE_VIDEO_CAPTURE);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_STATELESS_FWHT_PARAMS:
		अगर (!q_dst->info)
			वापस -EINVAL;
		params = ctrl->p_new.p_fwht_params;
		अगर (params->width > q_dst->coded_width ||
		    params->width < MIN_WIDTH ||
		    params->height > q_dst->coded_height ||
		    params->height < MIN_HEIGHT)
			वापस -EINVAL;
		अगर (!validate_by_version(params->flags, params->version))
			वापस -EINVAL;
		अगर (!validate_stateless_params_flags(params, q_dst->info))
			वापस -EINVAL;
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम update_header_from_stateless_params(काष्ठा vicodec_ctx *ctx,
						स्थिर काष्ठा v4l2_ctrl_fwht_params *params)
अणु
	काष्ठा fwht_cframe_hdr *p_hdr = &ctx->state.header;

	p_hdr->magic1 = FWHT_MAGIC1;
	p_hdr->magic2 = FWHT_MAGIC2;
	p_hdr->version = htonl(params->version);
	p_hdr->width = htonl(params->width);
	p_hdr->height = htonl(params->height);
	p_hdr->flags = htonl(params->flags);
	p_hdr->colorspace = htonl(params->colorspace);
	p_hdr->xfer_func = htonl(params->xfer_func);
	p_hdr->ycbcr_enc = htonl(params->ycbcr_enc);
	p_hdr->quantization = htonl(params->quantization);
पूर्ण

अटल पूर्णांक vicodec_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vicodec_ctx *ctx = container_of(ctrl->handler,
					       काष्ठा vicodec_ctx, hdl);
	स्थिर काष्ठा v4l2_ctrl_fwht_params *params;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctx->state.gop_size = ctrl->val;
		वापस 0;
	हाल V4L2_CID_FWHT_I_FRAME_QP:
		ctx->state.i_frame_qp = ctrl->val;
		वापस 0;
	हाल V4L2_CID_FWHT_P_FRAME_QP:
		ctx->state.p_frame_qp = ctrl->val;
		वापस 0;
	हाल V4L2_CID_STATELESS_FWHT_PARAMS:
		params = ctrl->p_new.p_fwht_params;
		update_header_from_stateless_params(ctx, params);
		ctx->state.ref_frame_ts = params->backward_ref_ts;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vicodec_ctrl_ops = अणु
	.s_ctrl = vicodec_s_ctrl,
	.try_ctrl = vicodec_try_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vicodec_ctrl_stateless_state = अणु
	.ops		= &vicodec_ctrl_ops,
	.id		= V4L2_CID_STATELESS_FWHT_PARAMS,
	.elem_size      = माप(काष्ठा v4l2_ctrl_fwht_params),
पूर्ण;

/*
 * File operations
 */
अटल पूर्णांक vicodec_खोलो(काष्ठा file *file)
अणु
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info = v4l2_fwht_get_pixfmt(0);
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा vicodec_dev *dev = video_drvdata(file);
	काष्ठा vicodec_ctx *ctx = शून्य;
	काष्ठा v4l2_ctrl_handler *hdl;
	अचिन्हित पूर्णांक raw_size;
	अचिन्हित पूर्णांक comp_size;
	पूर्णांक rc = 0;

	अगर (mutex_lock_पूर्णांकerruptible(vfd->lock))
		वापस -ERESTARTSYS;
	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		rc = -ENOMEM;
		जाओ खोलो_unlock;
	पूर्ण

	अगर (vfd == &dev->stateful_enc.vfd)
		ctx->is_enc = true;
	अन्यथा अगर (vfd == &dev->stateless_dec.vfd)
		ctx->is_stateless = true;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = dev;
	hdl = &ctx->hdl;
	v4l2_ctrl_handler_init(hdl, 5);
	v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops, V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			  1, 16, 1, 10);
	v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops, V4L2_CID_FWHT_I_FRAME_QP,
			  1, 31, 1, 20);
	v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops, V4L2_CID_FWHT_P_FRAME_QP,
			  1, 31, 1, 20);
	अगर (ctx->is_enc)
		v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops,
				  V4L2_CID_MIN_BUFFERS_FOR_OUTPUT, 1, 1, 1, 1);
	अगर (ctx->is_stateless)
		v4l2_ctrl_new_custom(hdl, &vicodec_ctrl_stateless_state, शून्य);
	अगर (hdl->error) अणु
		rc = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		kमुक्त(ctx);
		जाओ खोलो_unlock;
	पूर्ण
	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	अगर (ctx->is_enc)
		ctx->q_data[V4L2_M2M_SRC].info = info;
	अन्यथा अगर (ctx->is_stateless)
		ctx->q_data[V4L2_M2M_SRC].info = &pixfmt_stateless_fwht;
	अन्यथा
		ctx->q_data[V4L2_M2M_SRC].info = &pixfmt_fwht;
	ctx->q_data[V4L2_M2M_SRC].coded_width = 1280;
	ctx->q_data[V4L2_M2M_SRC].coded_height = 720;
	ctx->q_data[V4L2_M2M_SRC].visible_width = 1280;
	ctx->q_data[V4L2_M2M_SRC].visible_height = 720;
	raw_size = 1280 * 720 * info->sizeimage_mult / info->sizeimage_भाग;
	comp_size = 1280 * 720 * pixfmt_fwht.sizeimage_mult /
				 pixfmt_fwht.sizeimage_भाग;
	अगर (ctx->is_enc)
		ctx->q_data[V4L2_M2M_SRC].sizeimage = raw_size;
	अन्यथा अगर (ctx->is_stateless)
		ctx->q_data[V4L2_M2M_SRC].sizeimage = comp_size;
	अन्यथा
		ctx->q_data[V4L2_M2M_SRC].sizeimage =
			comp_size + माप(काष्ठा fwht_cframe_hdr);
	ctx->q_data[V4L2_M2M_DST] = ctx->q_data[V4L2_M2M_SRC];
	अगर (ctx->is_enc) अणु
		ctx->q_data[V4L2_M2M_DST].info = &pixfmt_fwht;
		ctx->q_data[V4L2_M2M_DST].sizeimage =
			comp_size + माप(काष्ठा fwht_cframe_hdr);
	पूर्ण अन्यथा अणु
		ctx->q_data[V4L2_M2M_DST].info = info;
		ctx->q_data[V4L2_M2M_DST].sizeimage = raw_size;
	पूर्ण

	ctx->state.colorspace = V4L2_COLORSPACE_REC709;

	अगर (ctx->is_enc) अणु
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->stateful_enc.m2m_dev,
						    ctx, &queue_init);
		ctx->lock = &dev->stateful_enc.lock;
	पूर्ण अन्यथा अगर (ctx->is_stateless) अणु
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->stateless_dec.m2m_dev,
						    ctx, &queue_init);
		ctx->lock = &dev->stateless_dec.lock;
	पूर्ण अन्यथा अणु
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->stateful_dec.m2m_dev,
						    ctx, &queue_init);
		ctx->lock = &dev->stateful_dec.lock;
	पूर्ण

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		rc = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_मुक्त(hdl);
		v4l2_fh_निकास(&ctx->fh);
		kमुक्त(ctx);
		जाओ खोलो_unlock;
	पूर्ण

	v4l2_fh_add(&ctx->fh);

खोलो_unlock:
	mutex_unlock(vfd->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक vicodec_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा vicodec_ctx *ctx = file2ctx(file);

	mutex_lock(vfd->lock);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(vfd->lock);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->hdl);
	kvमुक्त(ctx->state.compressed_frame);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक vicodec_request_validate(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj;
	काष्ठा v4l2_ctrl_handler *parent_hdl, *hdl;
	काष्ठा vicodec_ctx *ctx = शून्य;
	काष्ठा v4l2_ctrl *ctrl;
	अचिन्हित पूर्णांक count;

	list_क्रम_each_entry(obj, &req->objects, list) अणु
		काष्ठा vb2_buffer *vb;

		अगर (vb2_request_object_is_buffer(obj)) अणु
			vb = container_of(obj, काष्ठा vb2_buffer, req_obj);
			ctx = vb2_get_drv_priv(vb->vb2_queue);

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ctx) अणु
		pr_err("No buffer was provided with the request\n");
		वापस -ENOENT;
	पूर्ण

	count = vb2_request_buffer_cnt(req);
	अगर (!count) अणु
		v4l2_info(&ctx->dev->v4l2_dev,
			  "No buffer was provided with the request\n");
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (count > 1) अणु
		v4l2_info(&ctx->dev->v4l2_dev,
			  "More than one buffer was provided with the request\n");
		वापस -EINVAL;
	पूर्ण

	parent_hdl = &ctx->hdl;

	hdl = v4l2_ctrl_request_hdl_find(req, parent_hdl);
	अगर (!hdl) अणु
		v4l2_info(&ctx->dev->v4l2_dev, "Missing codec control\n");
		वापस -ENOENT;
	पूर्ण
	ctrl = v4l2_ctrl_request_hdl_ctrl_find(hdl,
					       vicodec_ctrl_stateless_state.id);
	v4l2_ctrl_request_hdl_put(hdl);
	अगर (!ctrl) अणु
		v4l2_info(&ctx->dev->v4l2_dev,
			  "Missing required codec control\n");
		वापस -ENOENT;
	पूर्ण

	वापस vb2_request_validate(req);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vicodec_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vicodec_खोलो,
	.release	= vicodec_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device vicodec_videodev = अणु
	.name		= VICODEC_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &vicodec_fops,
	.ioctl_ops	= &vicodec_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
पूर्ण;

अटल स्थिर काष्ठा media_device_ops vicodec_m2m_media_ops = अणु
	.req_validate	= vicodec_request_validate,
	.req_queue	= v4l2_m2m_request_queue,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= device_run,
	.job_पढ़ोy	= job_पढ़ोy,
पूर्ण;

अटल पूर्णांक रेजिस्टर_instance(काष्ठा vicodec_dev *dev,
			     काष्ठा vicodec_dev_instance *dev_instance,
			     स्थिर अक्षर *name, bool is_enc)
अणु
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	spin_lock_init(&dev_instance->lock);
	mutex_init(&dev_instance->mutex);
	dev_instance->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(dev_instance->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init vicodec enc device\n");
		वापस PTR_ERR(dev_instance->m2m_dev);
	पूर्ण

	dev_instance->vfd = vicodec_videodev;
	vfd = &dev_instance->vfd;
	vfd->lock = &dev_instance->mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;
	strscpy(vfd->name, name, माप(vfd->name));
	vfd->device_caps = V4L2_CAP_STREAMING |
		(multiplanar ? V4L2_CAP_VIDEO_M2M_MPLANE : V4L2_CAP_VIDEO_M2M);
	अगर (is_enc) अणु
		v4l2_disable_ioctl(vfd, VIDIOC_DECODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_DECODER_CMD);
	पूर्ण अन्यथा अणु
		v4l2_disable_ioctl(vfd, VIDIOC_ENCODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_ENCODER_CMD);
	पूर्ण
	video_set_drvdata(vfd, dev);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device '%s'\n", name);
		v4l2_m2m_release(dev_instance->m2m_dev);
		वापस ret;
	पूर्ण
	v4l2_info(&dev->v4l2_dev, "Device '%s' registered as /dev/video%d\n",
		  name, vfd->num);
	वापस 0;
पूर्ण

अटल व्योम vicodec_v4l2_dev_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा vicodec_dev *dev = container_of(v4l2_dev, काष्ठा vicodec_dev, v4l2_dev);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	v4l2_m2m_release(dev->stateful_enc.m2m_dev);
	v4l2_m2m_release(dev->stateful_dec.m2m_dev);
	v4l2_m2m_release(dev->stateless_dec.m2m_dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_device_cleanup(&dev->mdev);
#पूर्ण_अगर
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक vicodec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vicodec_dev *dev;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		जाओ मुक्त_dev;

	dev->v4l2_dev.release = vicodec_v4l2_dev_release;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->mdev.dev = &pdev->dev;
	strscpy(dev->mdev.model, "vicodec", माप(dev->mdev.model));
	strscpy(dev->mdev.bus_info, "platform:vicodec",
		माप(dev->mdev.bus_info));
	media_device_init(&dev->mdev);
	dev->mdev.ops = &vicodec_m2m_media_ops;
	dev->v4l2_dev.mdev = &dev->mdev;
#पूर्ण_अगर

	platक्रमm_set_drvdata(pdev, dev);

	ret = रेजिस्टर_instance(dev, &dev->stateful_enc, "stateful-encoder",
				true);
	अगर (ret)
		जाओ unreg_dev;

	ret = रेजिस्टर_instance(dev, &dev->stateful_dec, "stateful-decoder",
				false);
	अगर (ret)
		जाओ unreg_sf_enc;

	ret = रेजिस्टर_instance(dev, &dev->stateless_dec, "stateless-decoder",
				false);
	अगर (ret)
		जाओ unreg_sf_dec;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	ret = v4l2_m2m_रेजिस्टर_media_controller(dev->stateful_enc.m2m_dev,
						 &dev->stateful_enc.vfd,
						 MEDIA_ENT_F_PROC_VIDEO_ENCODER);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller for enc\n");
		जाओ unreg_m2m;
	पूर्ण

	ret = v4l2_m2m_रेजिस्टर_media_controller(dev->stateful_dec.m2m_dev,
						 &dev->stateful_dec.vfd,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller for dec\n");
		जाओ unreg_m2m_sf_enc_mc;
	पूर्ण

	ret = v4l2_m2m_रेजिस्टर_media_controller(dev->stateless_dec.m2m_dev,
						 &dev->stateless_dec.vfd,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller for stateless dec\n");
		जाओ unreg_m2m_sf_dec_mc;
	पूर्ण

	ret = media_device_रेजिस्टर(&dev->mdev);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register mem2mem media device\n");
		जाओ unreg_m2m_sl_dec_mc;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
unreg_m2m_sl_dec_mc:
	v4l2_m2m_unरेजिस्टर_media_controller(dev->stateless_dec.m2m_dev);
unreg_m2m_sf_dec_mc:
	v4l2_m2m_unरेजिस्टर_media_controller(dev->stateful_dec.m2m_dev);
unreg_m2m_sf_enc_mc:
	v4l2_m2m_unरेजिस्टर_media_controller(dev->stateful_enc.m2m_dev);
unreg_m2m:
	video_unरेजिस्टर_device(&dev->stateless_dec.vfd);
	v4l2_m2m_release(dev->stateless_dec.m2m_dev);
#पूर्ण_अगर
unreg_sf_dec:
	video_unरेजिस्टर_device(&dev->stateful_dec.vfd);
	v4l2_m2m_release(dev->stateful_dec.m2m_dev);
unreg_sf_enc:
	video_unरेजिस्टर_device(&dev->stateful_enc.vfd);
	v4l2_m2m_release(dev->stateful_enc.m2m_dev);
unreg_dev:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
मुक्त_dev:
	kमुक्त(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक vicodec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vicodec_dev *dev = platक्रमm_get_drvdata(pdev);

	v4l2_info(&dev->v4l2_dev, "Removing " VICODEC_NAME);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_device_unरेजिस्टर(&dev->mdev);
	v4l2_m2m_unरेजिस्टर_media_controller(dev->stateful_enc.m2m_dev);
	v4l2_m2m_unरेजिस्टर_media_controller(dev->stateful_dec.m2m_dev);
	v4l2_m2m_unरेजिस्टर_media_controller(dev->stateless_dec.m2m_dev);
#पूर्ण_अगर

	video_unरेजिस्टर_device(&dev->stateful_enc.vfd);
	video_unरेजिस्टर_device(&dev->stateful_dec.vfd);
	video_unरेजिस्टर_device(&dev->stateless_dec.vfd);
	v4l2_device_put(&dev->v4l2_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vicodec_pdrv = अणु
	.probe		= vicodec_probe,
	.हटाओ		= vicodec_हटाओ,
	.driver		= अणु
		.name	= VICODEC_NAME,
	पूर्ण,
पूर्ण;

अटल व्योम __निकास vicodec_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vicodec_pdrv);
	platक्रमm_device_unरेजिस्टर(&vicodec_pdev);
पूर्ण

अटल पूर्णांक __init vicodec_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&vicodec_pdev);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&vicodec_pdrv);
	अगर (ret)
		platक्रमm_device_unरेजिस्टर(&vicodec_pdev);

	वापस ret;
पूर्ण

module_init(vicodec_init);
module_निकास(vicodec_निकास);
