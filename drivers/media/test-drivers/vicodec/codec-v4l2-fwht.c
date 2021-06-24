<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * A V4L2 frontend क्रम the FWHT codec
 *
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>
#समावेश "codec-v4l2-fwht.h"

अटल स्थिर काष्ठा v4l2_fwht_pixfmt_info v4l2_fwht_pixfmts[] = अणु
	अणु V4L2_PIX_FMT_YUV420,  1, 3, 2, 1, 1, 2, 2, 3, 3, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_YVU420,  1, 3, 2, 1, 1, 2, 2, 3, 3, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_YUV422P, 1, 2, 1, 1, 1, 2, 1, 3, 3, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_NV12,    1, 3, 2, 1, 2, 2, 2, 3, 2, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_NV21,    1, 3, 2, 1, 2, 2, 2, 3, 2, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_NV16,    1, 2, 1, 1, 2, 2, 1, 3, 2, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_NV61,    1, 2, 1, 1, 2, 2, 1, 3, 2, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_NV24,    1, 3, 1, 1, 2, 1, 1, 3, 2, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_NV42,    1, 3, 1, 1, 2, 1, 1, 3, 2, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_YUYV,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_YVYU,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_UYVY,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_VYUY,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4L2_FWHT_FL_PIXENC_YUVपूर्ण,
	अणु V4L2_PIX_FMT_BGR24,   3, 3, 1, 3, 3, 1, 1, 3, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_RGB24,   3, 3, 1, 3, 3, 1, 1, 3, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_HSV24,   3, 3, 1, 3, 3, 1, 1, 3, 1, V4L2_FWHT_FL_PIXENC_HSVपूर्ण,
	अणु V4L2_PIX_FMT_BGR32,   4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_XBGR32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_ABGR32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_RGB32,   4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_XRGB32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_ARGB32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_BGRX32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_BGRA32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_RGBX32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_RGBA32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
	अणु V4L2_PIX_FMT_HSV32,   4, 4, 1, 4, 4, 1, 1, 4, 1, V4L2_FWHT_FL_PIXENC_HSVपूर्ण,
	अणु V4L2_PIX_FMT_GREY,    1, 1, 1, 1, 0, 1, 1, 1, 1, V4L2_FWHT_FL_PIXENC_RGBपूर्ण,
पूर्ण;

bool v4l2_fwht_validate_fmt(स्थिर काष्ठा v4l2_fwht_pixfmt_info *info,
			    u32 width_भाग, u32 height_भाग, u32 components_num,
			    u32 pixenc)
अणु
	अगर (info->width_भाग == width_भाग &&
	    info->height_भाग == height_भाग &&
	    (!pixenc || info->pixenc == pixenc) &&
	    info->components_num == components_num)
		वापस true;
	वापस false;
पूर्ण

स्थिर काष्ठा v4l2_fwht_pixfmt_info *v4l2_fwht_find_nth_fmt(u32 width_भाग,
							  u32 height_भाग,
							  u32 components_num,
							  u32 pixenc,
							  अचिन्हित पूर्णांक start_idx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(v4l2_fwht_pixfmts); i++) अणु
		bool is_valid = v4l2_fwht_validate_fmt(&v4l2_fwht_pixfmts[i],
						       width_भाग, height_भाग,
						       components_num, pixenc);
		अगर (is_valid) अणु
			अगर (start_idx == 0)
				वापस v4l2_fwht_pixfmts + i;
			start_idx--;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

स्थिर काष्ठा v4l2_fwht_pixfmt_info *v4l2_fwht_find_pixfmt(u32 pixelक्रमmat)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(v4l2_fwht_pixfmts); i++)
		अगर (v4l2_fwht_pixfmts[i].id == pixelक्रमmat)
			वापस v4l2_fwht_pixfmts + i;
	वापस शून्य;
पूर्ण

स्थिर काष्ठा v4l2_fwht_pixfmt_info *v4l2_fwht_get_pixfmt(u32 idx)
अणु
	अगर (idx >= ARRAY_SIZE(v4l2_fwht_pixfmts))
		वापस शून्य;
	वापस v4l2_fwht_pixfmts + idx;
पूर्ण

अटल पूर्णांक prepare_raw_frame(काष्ठा fwht_raw_frame *rf,
			 स्थिर काष्ठा v4l2_fwht_pixfmt_info *info, u8 *buf,
			 अचिन्हित पूर्णांक size)
अणु
	rf->luma = buf;
	rf->width_भाग = info->width_भाग;
	rf->height_भाग = info->height_भाग;
	rf->luma_alpha_step = info->luma_alpha_step;
	rf->chroma_step = info->chroma_step;
	rf->alpha = शून्य;
	rf->components_num = info->components_num;

	/*
	 * The buffer is शून्य अगर it is the reference
	 * frame of an I-frame in the stateless decoder
	 */
	अगर (!buf) अणु
		rf->luma = शून्य;
		rf->cb = शून्य;
		rf->cr = शून्य;
		rf->alpha = शून्य;
		वापस 0;
	पूर्ण
	चयन (info->id) अणु
	हाल V4L2_PIX_FMT_GREY:
		rf->cb = शून्य;
		rf->cr = शून्य;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		rf->cb = rf->luma + size;
		rf->cr = rf->cb + size / 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YVU420:
		rf->cr = rf->luma + size;
		rf->cb = rf->cr + size / 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		rf->cb = rf->luma + size;
		rf->cr = rf->cb + size / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV24:
		rf->cb = rf->luma + size;
		rf->cr = rf->cb + 1;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV42:
		rf->cr = rf->luma + size;
		rf->cb = rf->cr + 1;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		rf->cb = rf->luma + 1;
		rf->cr = rf->cb + 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YVYU:
		rf->cr = rf->luma + 1;
		rf->cb = rf->cr + 2;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		अवरोध;
	हाल V4L2_PIX_FMT_VYUY:
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_HSV24:
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR24:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_XRGB32:
	हाल V4L2_PIX_FMT_HSV32:
	हाल V4L2_PIX_FMT_ARGB32:
		rf->alpha = rf->luma;
		rf->cr = rf->luma + 1;
		rf->cb = rf->cr + 2;
		rf->luma += 2;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_ABGR32:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		rf->alpha = rf->cr + 1;
		अवरोध;
	हाल V4L2_PIX_FMT_BGRX32:
	हाल V4L2_PIX_FMT_BGRA32:
		rf->alpha = rf->luma;
		rf->cb = rf->luma + 1;
		rf->cr = rf->cb + 2;
		rf->luma += 2;
		अवरोध;
	हाल V4L2_PIX_FMT_RGBX32:
	हाल V4L2_PIX_FMT_RGBA32:
		rf->alpha = rf->luma + 3;
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक v4l2_fwht_encode(काष्ठा v4l2_fwht_state *state, u8 *p_in, u8 *p_out)
अणु
	अचिन्हित पूर्णांक size = state->stride * state->coded_height;
	अचिन्हित पूर्णांक chroma_stride = state->stride;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info = state->info;
	काष्ठा fwht_cframe_hdr *p_hdr;
	काष्ठा fwht_cframe cf;
	काष्ठा fwht_raw_frame rf;
	u32 encoding;
	u32 flags = 0;

	अगर (!info)
		वापस -EINVAL;

	अगर (prepare_raw_frame(&rf, info, p_in, size))
		वापस -EINVAL;

	अगर (info->planes_num == 3)
		chroma_stride /= 2;

	अगर (info->id == V4L2_PIX_FMT_NV24 ||
	    info->id == V4L2_PIX_FMT_NV42)
		chroma_stride *= 2;

	cf.i_frame_qp = state->i_frame_qp;
	cf.p_frame_qp = state->p_frame_qp;
	cf.rlc_data = (__be16 *)(p_out + माप(*p_hdr));

	encoding = fwht_encode_frame(&rf, &state->ref_frame, &cf,
				     !state->gop_cnt,
				     state->gop_cnt == state->gop_size - 1,
				     state->visible_width,
				     state->visible_height,
				     state->stride, chroma_stride);
	अगर (!(encoding & FWHT_FRAME_PCODED))
		state->gop_cnt = 0;
	अगर (++state->gop_cnt >= state->gop_size)
		state->gop_cnt = 0;

	p_hdr = (काष्ठा fwht_cframe_hdr *)p_out;
	p_hdr->magic1 = FWHT_MAGIC1;
	p_hdr->magic2 = FWHT_MAGIC2;
	p_hdr->version = htonl(V4L2_FWHT_VERSION);
	p_hdr->width = htonl(state->visible_width);
	p_hdr->height = htonl(state->visible_height);
	flags |= (info->components_num - 1) << V4L2_FWHT_FL_COMPONENTS_NUM_OFFSET;
	flags |= info->pixenc;
	अगर (encoding & FWHT_LUMA_UNENCODED)
		flags |= V4L2_FWHT_FL_LUMA_IS_UNCOMPRESSED;
	अगर (encoding & FWHT_CB_UNENCODED)
		flags |= V4L2_FWHT_FL_CB_IS_UNCOMPRESSED;
	अगर (encoding & FWHT_CR_UNENCODED)
		flags |= V4L2_FWHT_FL_CR_IS_UNCOMPRESSED;
	अगर (encoding & FWHT_ALPHA_UNENCODED)
		flags |= V4L2_FWHT_FL_ALPHA_IS_UNCOMPRESSED;
	अगर (!(encoding & FWHT_FRAME_PCODED))
		flags |= V4L2_FWHT_FL_I_FRAME;
	अगर (rf.height_भाग == 1)
		flags |= V4L2_FWHT_FL_CHROMA_FULL_HEIGHT;
	अगर (rf.width_भाग == 1)
		flags |= V4L2_FWHT_FL_CHROMA_FULL_WIDTH;
	p_hdr->flags = htonl(flags);
	p_hdr->colorspace = htonl(state->colorspace);
	p_hdr->xfer_func = htonl(state->xfer_func);
	p_hdr->ycbcr_enc = htonl(state->ycbcr_enc);
	p_hdr->quantization = htonl(state->quantization);
	p_hdr->size = htonl(cf.size);
	वापस cf.size + माप(*p_hdr);
पूर्ण

पूर्णांक v4l2_fwht_decode(काष्ठा v4l2_fwht_state *state, u8 *p_in, u8 *p_out)
अणु
	u32 flags;
	काष्ठा fwht_cframe cf;
	अचिन्हित पूर्णांक components_num = 3;
	अचिन्हित पूर्णांक version;
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info;
	अचिन्हित पूर्णांक hdr_width_भाग, hdr_height_भाग;
	काष्ठा fwht_raw_frame dst_rf;
	अचिन्हित पूर्णांक dst_chroma_stride = state->stride;
	अचिन्हित पूर्णांक ref_chroma_stride = state->ref_stride;
	अचिन्हित पूर्णांक dst_size = state->stride * state->coded_height;
	अचिन्हित पूर्णांक ref_size;

	अगर (!state->info)
		वापस -EINVAL;

	info = state->info;

	version = ntohl(state->header.version);
	अगर (!version || version > V4L2_FWHT_VERSION) अणु
		pr_err("version %d is not supported, current version is %d\n",
		       version, V4L2_FWHT_VERSION);
		वापस -EINVAL;
	पूर्ण

	अगर (state->header.magic1 != FWHT_MAGIC1 ||
	    state->header.magic2 != FWHT_MAGIC2)
		वापस -EINVAL;

	/* TODO: support resolution changes */
	अगर (ntohl(state->header.width)  != state->visible_width ||
	    ntohl(state->header.height) != state->visible_height)
		वापस -EINVAL;

	flags = ntohl(state->header.flags);

	अगर (version >= 2) अणु
		अगर ((flags & V4L2_FWHT_FL_PIXENC_MSK) != info->pixenc)
			वापस -EINVAL;
		components_num = 1 + ((flags & V4L2_FWHT_FL_COMPONENTS_NUM_MSK) >>
				V4L2_FWHT_FL_COMPONENTS_NUM_OFFSET);
	पूर्ण

	अगर (components_num != info->components_num)
		वापस -EINVAL;

	state->colorspace = ntohl(state->header.colorspace);
	state->xfer_func = ntohl(state->header.xfer_func);
	state->ycbcr_enc = ntohl(state->header.ycbcr_enc);
	state->quantization = ntohl(state->header.quantization);
	cf.rlc_data = (__be16 *)p_in;
	cf.size = ntohl(state->header.size);

	hdr_width_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	hdr_height_भाग = (flags & V4L2_FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;
	अगर (hdr_width_भाग != info->width_भाग ||
	    hdr_height_भाग != info->height_भाग)
		वापस -EINVAL;

	अगर (prepare_raw_frame(&dst_rf, info, p_out, dst_size))
		वापस -EINVAL;
	अगर (info->planes_num == 3) अणु
		dst_chroma_stride /= 2;
		ref_chroma_stride /= 2;
	पूर्ण
	अगर (info->id == V4L2_PIX_FMT_NV24 ||
	    info->id == V4L2_PIX_FMT_NV42) अणु
		dst_chroma_stride *= 2;
		ref_chroma_stride *= 2;
	पूर्ण


	ref_size = state->ref_stride * state->coded_height;

	अगर (prepare_raw_frame(&state->ref_frame, info, state->ref_frame.buf,
			      ref_size))
		वापस -EINVAL;

	अगर (!fwht_decode_frame(&cf, flags, components_num,
			state->visible_width, state->visible_height,
			&state->ref_frame, state->ref_stride, ref_chroma_stride,
			&dst_rf, state->stride, dst_chroma_stride))
		वापस -EINVAL;
	वापस 0;
पूर्ण
