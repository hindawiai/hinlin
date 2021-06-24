<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  TW5864 driver - H.264 headers generation functions
 *
 *  Copyright (C) 2016 Bluecherry, LLC <मुख्यtainers@bluecherrydvr.com>
 */

#समावेश <linux/log2.h>

#समावेश "tw5864.h"

अटल u8 marker[] = अणु 0x00, 0x00, 0x00, 0x01 पूर्ण;

/*
 * Exponential-Golomb coding functions
 *
 * These functions are used क्रम generation of H.264 bitstream headers.
 *
 * This code is derived from tw5864 reference driver by manufacturers, which
 * itself apparently was derived from x264 project.
 */

/* Bitstream writing context */
काष्ठा bs अणु
	u8 *buf; /* poपूर्णांकer to buffer beginning */
	u8 *buf_end; /* poपूर्णांकer to buffer end */
	u8 *ptr; /* poपूर्णांकer to current byte in buffer */
	अचिन्हित पूर्णांक bits_left; /* number of available bits in current byte */
पूर्ण;

अटल व्योम bs_init(काष्ठा bs *s, व्योम *buf, पूर्णांक size)
अणु
	s->buf = buf;
	s->ptr = buf;
	s->buf_end = s->ptr + size;
	s->bits_left = 8;
पूर्ण

अटल पूर्णांक bs_len(काष्ठा bs *s)
अणु
	वापस s->ptr - s->buf;
पूर्ण

अटल व्योम bs_ग_लिखो(काष्ठा bs *s, पूर्णांक count, u32 bits)
अणु
	अगर (s->ptr >= s->buf_end - 4)
		वापस;
	जबतक (count > 0) अणु
		अगर (count < 32)
			bits &= (1 << count) - 1;
		अगर (count < s->bits_left) अणु
			*s->ptr = (*s->ptr << count) | bits;
			s->bits_left -= count;
			अवरोध;
		पूर्ण
		*s->ptr = (*s->ptr << s->bits_left) |
			(bits >> (count - s->bits_left));
		count -= s->bits_left;
		s->ptr++;
		s->bits_left = 8;
	पूर्ण
पूर्ण

अटल व्योम bs_ग_लिखो1(काष्ठा bs *s, u32 bit)
अणु
	अगर (s->ptr < s->buf_end) अणु
		*s->ptr <<= 1;
		*s->ptr |= bit;
		s->bits_left--;
		अगर (s->bits_left == 0) अणु
			s->ptr++;
			s->bits_left = 8;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bs_ग_लिखो_ue(काष्ठा bs *s, u32 val)
अणु
	अगर (val == 0) अणु
		bs_ग_लिखो1(s, 1);
	पूर्ण अन्यथा अणु
		val++;
		bs_ग_लिखो(s, 2 * fls(val) - 1, val);
	पूर्ण
पूर्ण

अटल व्योम bs_ग_लिखो_se(काष्ठा bs *s, पूर्णांक val)
अणु
	bs_ग_लिखो_ue(s, val <= 0 ? -val * 2 : val * 2 - 1);
पूर्ण

अटल व्योम bs_rbsp_trailing(काष्ठा bs *s)
अणु
	bs_ग_लिखो1(s, 1);
	अगर (s->bits_left != 8)
		bs_ग_लिखो(s, s->bits_left, 0x00);
पूर्ण

/* H.264 headers generation functions */

अटल पूर्णांक tw5864_h264_gen_sps_rbsp(u8 *buf, माप_प्रकार size, पूर्णांक width, पूर्णांक height)
अणु
	काष्ठा bs bs, *s;

	s = &bs;
	bs_init(s, buf, size);
	bs_ग_लिखो(s, 8, 0x42); /* profile_idc, baseline */
	bs_ग_लिखो(s, 1, 1); /* स्थिरraपूर्णांक_set0_flag */
	bs_ग_लिखो(s, 1, 1); /* स्थिरraपूर्णांक_set1_flag */
	bs_ग_लिखो(s, 1, 0); /* स्थिरraपूर्णांक_set2_flag */
	bs_ग_लिखो(s, 5, 0); /* reserved_zero_5bits */
	bs_ग_लिखो(s, 8, 0x1e); /* level_idc */
	bs_ग_लिखो_ue(s, 0); /* seq_parameter_set_id */
	bs_ग_लिखो_ue(s, ilog2(MAX_GOP_SIZE) - 4); /* log2_max_frame_num_minus4 */
	bs_ग_लिखो_ue(s, 0); /* pic_order_cnt_type */
	/* log2_max_pic_order_cnt_lsb_minus4 */
	bs_ग_लिखो_ue(s, ilog2(MAX_GOP_SIZE) - 4);
	bs_ग_लिखो_ue(s, 1); /* num_ref_frames */
	bs_ग_लिखो(s, 1, 0); /* gaps_in_frame_num_value_allowed_flag */
	bs_ग_लिखो_ue(s, width / 16 - 1); /* pic_width_in_mbs_minus1 */
	bs_ग_लिखो_ue(s, height / 16 - 1); /* pic_height_in_map_units_minus1 */
	bs_ग_लिखो(s, 1, 1); /* frame_mbs_only_flag */
	bs_ग_लिखो(s, 1, 0); /* direct_8x8_inference_flag */
	bs_ग_लिखो(s, 1, 0); /* frame_cropping_flag */
	bs_ग_लिखो(s, 1, 0); /* vui_parameters_present_flag */
	bs_rbsp_trailing(s);
	वापस bs_len(s);
पूर्ण

अटल पूर्णांक tw5864_h264_gen_pps_rbsp(u8 *buf, माप_प्रकार size, पूर्णांक qp)
अणु
	काष्ठा bs bs, *s;

	s = &bs;
	bs_init(s, buf, size);
	bs_ग_लिखो_ue(s, 0); /* pic_parameter_set_id */
	bs_ग_लिखो_ue(s, 0); /* seq_parameter_set_id */
	bs_ग_लिखो(s, 1, 0); /* entropy_coding_mode_flag */
	bs_ग_लिखो(s, 1, 0); /* pic_order_present_flag */
	bs_ग_लिखो_ue(s, 0); /* num_slice_groups_minus1 */
	bs_ग_लिखो_ue(s, 0); /* i_num_ref_idx_l0_active_minus1 */
	bs_ग_लिखो_ue(s, 0); /* i_num_ref_idx_l1_active_minus1 */
	bs_ग_लिखो(s, 1, 0); /* weighted_pred_flag */
	bs_ग_लिखो(s, 2, 0); /* weighted_bipred_idc */
	bs_ग_लिखो_se(s, qp - 26); /* pic_init_qp_minus26 */
	bs_ग_लिखो_se(s, qp - 26); /* pic_init_qs_minus26 */
	bs_ग_लिखो_se(s, 0); /* chroma_qp_index_offset */
	bs_ग_लिखो(s, 1, 0); /* deblocking_filter_control_present_flag */
	bs_ग_लिखो(s, 1, 0); /* स्थिरrained_पूर्णांकra_pred_flag */
	bs_ग_लिखो(s, 1, 0); /* redundant_pic_cnt_present_flag */
	bs_rbsp_trailing(s);
	वापस bs_len(s);
पूर्ण

अटल पूर्णांक tw5864_h264_gen_slice_head(u8 *buf, माप_प्रकार size,
				      अचिन्हित पूर्णांक idr_pic_id,
				      अचिन्हित पूर्णांक frame_gop_seqno,
				      पूर्णांक *tail_nb_bits, u8 *tail)
अणु
	काष्ठा bs bs, *s;
	पूर्णांक is_i_frame = frame_gop_seqno == 0;

	s = &bs;
	bs_init(s, buf, size);
	bs_ग_लिखो_ue(s, 0); /* first_mb_in_slice */
	bs_ग_लिखो_ue(s, is_i_frame ? 2 : 5); /* slice_type - I or P */
	bs_ग_लिखो_ue(s, 0); /* pic_parameter_set_id */
	bs_ग_लिखो(s, ilog2(MAX_GOP_SIZE), frame_gop_seqno); /* frame_num */
	अगर (is_i_frame)
		bs_ग_लिखो_ue(s, idr_pic_id);

	/* pic_order_cnt_lsb */
	bs_ग_लिखो(s, ilog2(MAX_GOP_SIZE), frame_gop_seqno);

	अगर (is_i_frame) अणु
		bs_ग_लिखो1(s, 0); /* no_output_of_prior_pics_flag */
		bs_ग_लिखो1(s, 0); /* दीर्घ_term_reference_flag */
	पूर्ण अन्यथा अणु
		bs_ग_लिखो1(s, 0); /* num_ref_idx_active_override_flag */
		bs_ग_लिखो1(s, 0); /* ref_pic_list_reordering_flag_l0 */
		bs_ग_लिखो1(s, 0); /* adaptive_ref_pic_marking_mode_flag */
	पूर्ण

	bs_ग_लिखो_se(s, 0); /* slice_qp_delta */

	अगर (s->bits_left != 8) अणु
		*tail = ((s->ptr[0]) << s->bits_left);
		*tail_nb_bits = 8 - s->bits_left;
	पूर्ण अन्यथा अणु
		*tail = 0;
		*tail_nb_bits = 0;
	पूर्ण

	वापस bs_len(s);
पूर्ण

व्योम tw5864_h264_put_stream_header(u8 **buf, माप_प्रकार *space_left, पूर्णांक qp,
				   पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक nal_len;

	/* SPS */
	स_नकल(*buf, marker, माप(marker));
	*buf += 4;
	*space_left -= 4;

	**buf = 0x67; /* SPS NAL header */
	*buf += 1;
	*space_left -= 1;

	nal_len = tw5864_h264_gen_sps_rbsp(*buf, *space_left, width, height);
	*buf += nal_len;
	*space_left -= nal_len;

	/* PPS */
	स_नकल(*buf, marker, माप(marker));
	*buf += 4;
	*space_left -= 4;

	**buf = 0x68; /* PPS NAL header */
	*buf += 1;
	*space_left -= 1;

	nal_len = tw5864_h264_gen_pps_rbsp(*buf, *space_left, qp);
	*buf += nal_len;
	*space_left -= nal_len;
पूर्ण

व्योम tw5864_h264_put_slice_header(u8 **buf, माप_प्रकार *space_left,
				  अचिन्हित पूर्णांक idr_pic_id,
				  अचिन्हित पूर्णांक frame_gop_seqno,
				  पूर्णांक *tail_nb_bits, u8 *tail)
अणु
	पूर्णांक nal_len;

	स_नकल(*buf, marker, माप(marker));
	*buf += 4;
	*space_left -= 4;

	/* Frame NAL header */
	**buf = (frame_gop_seqno == 0) ? 0x25 : 0x21;
	*buf += 1;
	*space_left -= 1;

	nal_len = tw5864_h264_gen_slice_head(*buf, *space_left, idr_pic_id,
					     frame_gop_seqno, tail_nb_bits,
					     tail);
	*buf += nal_len;
	*space_left -= nal_len;
पूर्ण
