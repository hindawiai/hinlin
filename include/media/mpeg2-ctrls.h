<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * These are the MPEG2 state controls क्रम use with stateless MPEG-2
 * codec drivers.
 *
 * It turns out that these काष्ठाs are not stable yet and will undergo
 * more changes. So keep them निजी until they are stable and पढ़ोy to
 * become part of the official खुला API.
 */

#अगर_अघोषित _MPEG2_CTRLS_H_
#घोषणा _MPEG2_CTRLS_H_

#घोषणा V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS		(V4L2_CID_CODEC_BASE+250)
#घोषणा V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION		(V4L2_CID_CODEC_BASE+251)

/* क्रमागत v4l2_ctrl_type type values */
#घोषणा V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS 0x0103
#घोषणा	V4L2_CTRL_TYPE_MPEG2_QUANTIZATION 0x0104

#घोषणा V4L2_MPEG2_PICTURE_CODING_TYPE_I	1
#घोषणा V4L2_MPEG2_PICTURE_CODING_TYPE_P	2
#घोषणा V4L2_MPEG2_PICTURE_CODING_TYPE_B	3
#घोषणा V4L2_MPEG2_PICTURE_CODING_TYPE_D	4

काष्ठा v4l2_mpeg2_sequence अणु
	/* ISO/IEC 13818-2, ITU-T Rec. H.262: Sequence header */
	__u16	horizontal_size;
	__u16	vertical_size;
	__u32	vbv_buffer_size;

	/* ISO/IEC 13818-2, ITU-T Rec. H.262: Sequence extension */
	__u16	profile_and_level_indication;
	__u8	progressive_sequence;
	__u8	chroma_क्रमmat;
पूर्ण;

काष्ठा v4l2_mpeg2_picture अणु
	/* ISO/IEC 13818-2, ITU-T Rec. H.262: Picture header */
	__u8	picture_coding_type;

	/* ISO/IEC 13818-2, ITU-T Rec. H.262: Picture coding extension */
	__u8	f_code[2][2];
	__u8	पूर्णांकra_dc_precision;
	__u8	picture_काष्ठाure;
	__u8	top_field_first;
	__u8	frame_pred_frame_dct;
	__u8	concealment_motion_vectors;
	__u8	q_scale_type;
	__u8	पूर्णांकra_vlc_क्रमmat;
	__u8	alternate_scan;
	__u8	repeat_first_field;
	__u16	progressive_frame;
पूर्ण;

काष्ठा v4l2_ctrl_mpeg2_slice_params अणु
	__u32	bit_size;
	__u32	data_bit_offset;
	__u64	backward_ref_ts;
	__u64	क्रमward_ref_ts;

	काष्ठा v4l2_mpeg2_sequence sequence;
	काष्ठा v4l2_mpeg2_picture picture;

	/* ISO/IEC 13818-2, ITU-T Rec. H.262: Slice */
	__u32	quantiser_scale_code;
पूर्ण;

काष्ठा v4l2_ctrl_mpeg2_quantization अणु
	/* ISO/IEC 13818-2, ITU-T Rec. H.262: Quant matrix extension */
	__u8	load_पूर्णांकra_quantiser_matrix;
	__u8	load_non_पूर्णांकra_quantiser_matrix;
	__u8	load_chroma_पूर्णांकra_quantiser_matrix;
	__u8	load_chroma_non_पूर्णांकra_quantiser_matrix;

	__u8	पूर्णांकra_quantiser_matrix[64];
	__u8	non_पूर्णांकra_quantiser_matrix[64];
	__u8	chroma_पूर्णांकra_quantiser_matrix[64];
	__u8	chroma_non_पूर्णांकra_quantiser_matrix[64];
पूर्ण;

#पूर्ण_अगर
