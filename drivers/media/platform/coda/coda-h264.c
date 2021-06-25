<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Coda multi-standard codec IP - H.264 helper functions
 *
 * Copyright (C) 2012 Vista Silicon S.L.
 *    Javier Martin, <javier.martin@vista-silicon.com>
 *    Xavier Duret
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>

#समावेश "coda.h"

अटल स्थिर u8 coda_filler_size[8] = अणु 0, 7, 14, 13, 12, 11, 10, 9 पूर्ण;

अटल स्थिर u8 *coda_find_nal_header(स्थिर u8 *buf, स्थिर u8 *end)
अणु
	u32 val = 0xffffffff;

	करो अणु
		val = val << 8 | *buf++;
		अगर (buf >= end)
			वापस शून्य;
	पूर्ण जबतक (val != 0x00000001);

	वापस buf;
पूर्ण

पूर्णांक coda_sps_parse_profile(काष्ठा coda_ctx *ctx, काष्ठा vb2_buffer *vb)
अणु
	स्थिर u8 *buf = vb2_plane_vaddr(vb, 0);
	स्थिर u8 *end = buf + vb2_get_plane_payload(vb, 0);

	/* Find SPS header */
	करो अणु
		buf = coda_find_nal_header(buf, end);
		अगर (!buf)
			वापस -EINVAL;
	पूर्ण जबतक ((*buf++ & 0x1f) != 0x7);

	ctx->params.h264_profile_idc = buf[0];
	ctx->params.h264_level_idc = buf[2];

	वापस 0;
पूर्ण

पूर्णांक coda_h264_filler_nal(पूर्णांक size, अक्षर *p)
अणु
	अगर (size < 6)
		वापस -EINVAL;

	p[0] = 0x00;
	p[1] = 0x00;
	p[2] = 0x00;
	p[3] = 0x01;
	p[4] = 0x0c;
	स_रखो(p + 5, 0xff, size - 6);
	/* Add rbsp stop bit and trailing at the end */
	p[size - 1] = 0x80;

	वापस 0;
पूर्ण

पूर्णांक coda_h264_padding(पूर्णांक size, अक्षर *p)
अणु
	पूर्णांक nal_size;
	पूर्णांक dअगरf;

	dअगरf = size - (size & ~0x7);
	अगर (dअगरf == 0)
		वापस 0;

	nal_size = coda_filler_size[dअगरf];
	coda_h264_filler_nal(nal_size, p);

	वापस nal_size;
पूर्ण

पूर्णांक coda_h264_profile(पूर्णांक profile_idc)
अणु
	चयन (profile_idc) अणु
	हाल 66: वापस V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE;
	हाल 77: वापस V4L2_MPEG_VIDEO_H264_PROखाता_MAIN;
	हाल 88: वापस V4L2_MPEG_VIDEO_H264_PROखाता_EXTENDED;
	हाल 100: वापस V4L2_MPEG_VIDEO_H264_PROखाता_HIGH;
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक coda_h264_level(पूर्णांक level_idc)
अणु
	चयन (level_idc) अणु
	हाल 10: वापस V4L2_MPEG_VIDEO_H264_LEVEL_1_0;
	हाल 9:  वापस V4L2_MPEG_VIDEO_H264_LEVEL_1B;
	हाल 11: वापस V4L2_MPEG_VIDEO_H264_LEVEL_1_1;
	हाल 12: वापस V4L2_MPEG_VIDEO_H264_LEVEL_1_2;
	हाल 13: वापस V4L2_MPEG_VIDEO_H264_LEVEL_1_3;
	हाल 20: वापस V4L2_MPEG_VIDEO_H264_LEVEL_2_0;
	हाल 21: वापस V4L2_MPEG_VIDEO_H264_LEVEL_2_1;
	हाल 22: वापस V4L2_MPEG_VIDEO_H264_LEVEL_2_2;
	हाल 30: वापस V4L2_MPEG_VIDEO_H264_LEVEL_3_0;
	हाल 31: वापस V4L2_MPEG_VIDEO_H264_LEVEL_3_1;
	हाल 32: वापस V4L2_MPEG_VIDEO_H264_LEVEL_3_2;
	हाल 40: वापस V4L2_MPEG_VIDEO_H264_LEVEL_4_0;
	हाल 41: वापस V4L2_MPEG_VIDEO_H264_LEVEL_4_1;
	हाल 42: वापस V4L2_MPEG_VIDEO_H264_LEVEL_4_2;
	हाल 50: वापस V4L2_MPEG_VIDEO_H264_LEVEL_5_0;
	हाल 51: वापस V4L2_MPEG_VIDEO_H264_LEVEL_5_1;
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

काष्ठा rbsp अणु
	अक्षर *buf;
	पूर्णांक size;
	पूर्णांक pos;
पूर्ण;

अटल अंतरभूत पूर्णांक rbsp_पढ़ो_bit(काष्ठा rbsp *rbsp)
अणु
	पूर्णांक shअगरt = 7 - (rbsp->pos % 8);
	पूर्णांक ofs = rbsp->pos++ / 8;

	अगर (ofs >= rbsp->size)
		वापस -EINVAL;

	वापस (rbsp->buf[ofs] >> shअगरt) & 1;
पूर्ण

अटल अंतरभूत पूर्णांक rbsp_ग_लिखो_bit(काष्ठा rbsp *rbsp, पूर्णांक bit)
अणु
	पूर्णांक shअगरt = 7 - (rbsp->pos % 8);
	पूर्णांक ofs = rbsp->pos++ / 8;

	अगर (ofs >= rbsp->size)
		वापस -EINVAL;

	rbsp->buf[ofs] &= ~(1 << shअगरt);
	rbsp->buf[ofs] |= bit << shअगरt;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rbsp_पढ़ो_bits(काष्ठा rbsp *rbsp, पूर्णांक num, पूर्णांक *val)
अणु
	पूर्णांक i, ret;
	पूर्णांक पंचांगp = 0;

	अगर (num > 32)
		वापस -EINVAL;

	क्रम (i = 0; i < num; i++) अणु
		ret = rbsp_पढ़ो_bit(rbsp);
		अगर (ret < 0)
			वापस ret;
		पंचांगp |= ret << (num - i - 1);
	पूर्ण

	अगर (val)
		*val = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_ग_लिखो_bits(काष्ठा rbsp *rbsp, पूर्णांक num, पूर्णांक value)
अणु
	पूर्णांक ret;

	जबतक (num--) अणु
		ret = rbsp_ग_लिखो_bit(rbsp, (value >> num) & 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_पढ़ो_uev(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक leading_zero_bits = 0;
	अचिन्हित पूर्णांक पंचांगp = 0;
	पूर्णांक ret;

	जबतक ((ret = rbsp_पढ़ो_bit(rbsp)) == 0)
		leading_zero_bits++;
	अगर (ret < 0)
		वापस ret;

	अगर (leading_zero_bits > 0) अणु
		ret = rbsp_पढ़ो_bits(rbsp, leading_zero_bits, &पंचांगp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val)
		*val = (1 << leading_zero_bits) - 1 + पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_ग_लिखो_uev(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक पंचांगp = value + 1;
	पूर्णांक leading_zero_bits = fls(पंचांगp) - 1;

	क्रम (i = 0; i < leading_zero_bits; i++) अणु
		ret = rbsp_ग_लिखो_bit(rbsp, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस rbsp_ग_लिखो_bits(rbsp, leading_zero_bits + 1, पंचांगp);
पूर्ण

अटल पूर्णांक rbsp_पढ़ो_sev(काष्ठा rbsp *rbsp, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = rbsp_पढ़ो_uev(rbsp, &पंचांगp);
	अगर (ret)
		वापस ret;

	अगर (val) अणु
		अगर (पंचांगp & 1)
			*val = (पंचांगp + 1) / 2;
		अन्यथा
			*val = -(पंचांगp / 2);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * coda_h264_sps_fixup - fixes frame cropping values in h.264 SPS
 * @ctx: encoder context
 * @width: visible width
 * @height: visible height
 * @buf: buffer containing h.264 SPS RBSP, starting with NAL header
 * @size: modअगरied RBSP size वापस value
 * @max_size: available size in buf
 *
 * Reग_लिखोs the frame cropping values in an h.264 SPS RBSP correctly क्रम the
 * given visible width and height.
 */
पूर्णांक coda_h264_sps_fixup(काष्ठा coda_ctx *ctx, पूर्णांक width, पूर्णांक height, अक्षर *buf,
			पूर्णांक *size, पूर्णांक max_size)
अणु
	पूर्णांक profile_idc;
	अचिन्हित पूर्णांक pic_order_cnt_type;
	पूर्णांक pic_width_in_mbs_minus1, pic_height_in_map_units_minus1;
	पूर्णांक frame_mbs_only_flag, frame_cropping_flag;
	पूर्णांक vui_parameters_present_flag;
	अचिन्हित पूर्णांक crop_right, crop_bottom;
	काष्ठा rbsp sps;
	पूर्णांक pos;
	पूर्णांक ret;

	अगर (*size < 8 || *size >= max_size)
		वापस -EINVAL;

	sps.buf = buf + 5; /* Skip NAL header */
	sps.size = *size - 5;

	profile_idc = sps.buf[0];
	/* Skip स्थिरraपूर्णांक_set[0-5]_flag, reserved_zero_2bits */
	/* Skip level_idc */
	sps.pos = 24;

	/* seq_parameter_set_id */
	ret = rbsp_पढ़ो_uev(&sps, शून्य);
	अगर (ret)
		वापस ret;

	अगर (profile_idc == 100 || profile_idc == 110 || profile_idc == 122 ||
	    profile_idc == 244 || profile_idc == 44 || profile_idc == 83 ||
	    profile_idc == 86 || profile_idc == 118 || profile_idc == 128 ||
	    profile_idc == 138 || profile_idc == 139 || profile_idc == 134 ||
	    profile_idc == 135) अणु
		dev_err(ctx->fh.vdev->dev_parent,
			"%s: Handling profile_idc %d not implemented\n",
			__func__, profile_idc);
		वापस -EINVAL;
	पूर्ण

	/* log2_max_frame_num_minus4 */
	ret = rbsp_पढ़ो_uev(&sps, शून्य);
	अगर (ret)
		वापस ret;

	ret = rbsp_पढ़ो_uev(&sps, &pic_order_cnt_type);
	अगर (ret)
		वापस ret;

	अगर (pic_order_cnt_type == 0) अणु
		/* log2_max_pic_order_cnt_lsb_minus4 */
		ret = rbsp_पढ़ो_uev(&sps, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (pic_order_cnt_type == 1) अणु
		अचिन्हित पूर्णांक i, num_ref_frames_in_pic_order_cnt_cycle;

		/* delta_pic_order_always_zero_flag */
		ret = rbsp_पढ़ो_bit(&sps);
		अगर (ret < 0)
			वापस ret;
		/* offset_क्रम_non_ref_pic */
		ret = rbsp_पढ़ो_sev(&sps, शून्य);
		अगर (ret)
			वापस ret;
		/* offset_क्रम_top_to_bottom_field */
		ret = rbsp_पढ़ो_sev(&sps, शून्य);
		अगर (ret)
			वापस ret;

		ret = rbsp_पढ़ो_uev(&sps,
				    &num_ref_frames_in_pic_order_cnt_cycle);
		अगर (ret)
			वापस ret;
		क्रम (i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++) अणु
			/* offset_क्रम_ref_frame */
			ret = rbsp_पढ़ो_sev(&sps, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* max_num_ref_frames */
	ret = rbsp_पढ़ो_uev(&sps, शून्य);
	अगर (ret)
		वापस ret;

	/* gaps_in_frame_num_value_allowed_flag */
	ret = rbsp_पढ़ो_bit(&sps);
	अगर (ret < 0)
		वापस ret;
	ret = rbsp_पढ़ो_uev(&sps, &pic_width_in_mbs_minus1);
	अगर (ret)
		वापस ret;
	ret = rbsp_पढ़ो_uev(&sps, &pic_height_in_map_units_minus1);
	अगर (ret)
		वापस ret;
	frame_mbs_only_flag = ret = rbsp_पढ़ो_bit(&sps);
	अगर (ret < 0)
		वापस ret;
	अगर (!frame_mbs_only_flag) अणु
		/* mb_adaptive_frame_field_flag */
		ret = rbsp_पढ़ो_bit(&sps);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	/* direct_8x8_inference_flag */
	ret = rbsp_पढ़ो_bit(&sps);
	अगर (ret < 0)
		वापस ret;

	/* Mark position of the frame cropping flag */
	pos = sps.pos;
	frame_cropping_flag = ret = rbsp_पढ़ो_bit(&sps);
	अगर (ret < 0)
		वापस ret;
	अगर (frame_cropping_flag) अणु
		अचिन्हित पूर्णांक crop_left, crop_top;

		ret = rbsp_पढ़ो_uev(&sps, &crop_left);
		अगर (ret)
			वापस ret;
		ret = rbsp_पढ़ो_uev(&sps, &crop_right);
		अगर (ret)
			वापस ret;
		ret = rbsp_पढ़ो_uev(&sps, &crop_top);
		अगर (ret)
			वापस ret;
		ret = rbsp_पढ़ो_uev(&sps, &crop_bottom);
		अगर (ret)
			वापस ret;
	पूर्ण
	vui_parameters_present_flag = ret = rbsp_पढ़ो_bit(&sps);
	अगर (ret < 0)
		वापस ret;
	अगर (vui_parameters_present_flag) अणु
		dev_err(ctx->fh.vdev->dev_parent,
			"%s: Handling vui_parameters not implemented\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	crop_right = round_up(width, 16) - width;
	crop_bottom = round_up(height, 16) - height;
	crop_right /= 2;
	अगर (frame_mbs_only_flag)
		crop_bottom /= 2;
	अन्यथा
		crop_bottom /= 4;


	sps.size = max_size - 5;
	sps.pos = pos;
	frame_cropping_flag = 1;
	ret = rbsp_ग_लिखो_bit(&sps, frame_cropping_flag);
	अगर (ret)
		वापस ret;
	ret = rbsp_ग_लिखो_uev(&sps, 0); /* crop_left */
	अगर (ret)
		वापस ret;
	ret = rbsp_ग_लिखो_uev(&sps, crop_right);
	अगर (ret)
		वापस ret;
	ret = rbsp_ग_लिखो_uev(&sps, 0); /* crop_top */
	अगर (ret)
		वापस ret;
	ret = rbsp_ग_लिखो_uev(&sps, crop_bottom);
	अगर (ret)
		वापस ret;
	ret = rbsp_ग_लिखो_bit(&sps, 0); /* vui_parameters_present_flag */
	अगर (ret)
		वापस ret;
	ret = rbsp_ग_लिखो_bit(&sps, 1);
	अगर (ret)
		वापस ret;

	*size = 5 + DIV_ROUND_UP(sps.pos, 8);

	वापस 0;
पूर्ण
