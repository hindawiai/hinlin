<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#समावेश "hva.h"
#समावेश "hva-hw.h"

#घोषणा MAX_SPS_PPS_SIZE 128

#घोषणा BITSTREAM_OFFSET_MASK 0x7F

/* video max size*/
#घोषणा H264_MAX_SIZE_W 1920
#घोषणा H264_MAX_SIZE_H 1920

/* macroBlocs number (width & height) */
#घोषणा MB_W(w) ((w + 0xF)  / 0x10)
#घोषणा MB_H(h) ((h + 0xF)  / 0x10)

/* क्रमmula to get temporal or spatial data size */
#घोषणा DATA_SIZE(w, h) (MB_W(w) * MB_H(h) * 16)

#घोषणा SEARCH_WINDOW_BUFFER_MAX_SIZE(w) ((4 * MB_W(w) + 42) * 256 * 3 / 2)
#घोषणा CABAC_CONTEXT_BUFFER_MAX_SIZE(w) (MB_W(w) * 16)
#घोषणा CTX_MB_BUFFER_MAX_SIZE(w) (MB_W(w) * 16 * 8)
#घोषणा SLICE_HEADER_SIZE (4 * 16)
#घोषणा BRC_DATA_SIZE (5 * 16)

/* source buffer copy in YUV 420 MB-tiled क्रमmat with size=16*256*3/2 */
#घोषणा CURRENT_WINDOW_BUFFER_MAX_SIZE (16 * 256 * 3 / 2)

/*
 * 4 lines of pixels (in Luma, Chroma blue and Chroma red) of top MB
 * क्रम deblocking with size=4*16*MBx*2
 */
#घोषणा LOCAL_RECONSTRUCTED_BUFFER_MAX_SIZE(w) (4 * 16 * MB_W(w) * 2)

/* factor क्रम bitrate and cpb buffer size max values अगर profile >= high */
#घोषणा H264_FACTOR_HIGH 1200

/* factor क्रम bitrate and cpb buffer size max values अगर profile < high */
#घोषणा H264_FACTOR_BASELINE 1000

/* number of bytes क्रम NALU_TYPE_FILLER_DATA header and footer */
#घोषणा H264_FILLER_DATA_SIZE 6

काष्ठा h264_profile अणु
	क्रमागत v4l2_mpeg_video_h264_level level;
	u32 max_mb_per_seconds;
	u32 max_frame_size;
	u32 max_bitrate;
	u32 max_cpb_size;
	u32 min_comp_ratio;
पूर्ण;

अटल स्थिर काष्ठा h264_profile h264_infos_list[] = अणु
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_1_0, 1485, 99, 64, 175, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_1B, 1485, 99, 128, 350, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_1_1, 3000, 396, 192, 500, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_1_2, 6000, 396, 384, 1000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_1_3, 11880, 396, 768, 2000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_2_0, 11880, 396, 2000, 2000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_2_1, 19800, 792, 4000, 4000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_2_2, 20250, 1620, 4000, 4000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_3_0, 40500, 1620, 10000, 10000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_3_1, 108000, 3600, 14000, 14000, 4पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_3_2, 216000, 5120, 20000, 20000, 4पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_4_0, 245760, 8192, 20000, 25000, 4पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_4_1, 245760, 8192, 50000, 62500, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_4_2, 522240, 8704, 50000, 62500, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_5_0, 589824, 22080, 135000, 135000, 2पूर्ण,
	अणुV4L2_MPEG_VIDEO_H264_LEVEL_5_1, 983040, 36864, 240000, 240000, 2पूर्ण
पूर्ण;

क्रमागत hva_brc_type अणु
	BRC_TYPE_NONE = 0,
	BRC_TYPE_CBR = 1,
	BRC_TYPE_VBR = 2,
	BRC_TYPE_VBR_LOW_DELAY = 3
पूर्ण;

क्रमागत hva_entropy_coding_mode अणु
	CAVLC = 0,
	CABAC = 1
पूर्ण;

क्रमागत hva_picture_coding_type अणु
	PICTURE_CODING_TYPE_I = 0,
	PICTURE_CODING_TYPE_P = 1,
	PICTURE_CODING_TYPE_B = 2
पूर्ण;

क्रमागत hva_h264_sampling_mode अणु
	SAMPLING_MODE_NV12 = 0,
	SAMPLING_MODE_UYVY = 1,
	SAMPLING_MODE_RGB3 = 3,
	SAMPLING_MODE_XRGB4 = 4,
	SAMPLING_MODE_NV21 = 8,
	SAMPLING_MODE_VYUY = 9,
	SAMPLING_MODE_BGR3 = 11,
	SAMPLING_MODE_XBGR4 = 12,
	SAMPLING_MODE_RGBX4 = 20,
	SAMPLING_MODE_BGRX4 = 28
पूर्ण;

क्रमागत hva_h264_nalu_type अणु
	NALU_TYPE_UNKNOWN = 0,
	NALU_TYPE_SLICE = 1,
	NALU_TYPE_SLICE_DPA = 2,
	NALU_TYPE_SLICE_DPB = 3,
	NALU_TYPE_SLICE_DPC = 4,
	NALU_TYPE_SLICE_IDR = 5,
	NALU_TYPE_SEI = 6,
	NALU_TYPE_SPS = 7,
	NALU_TYPE_PPS = 8,
	NALU_TYPE_AU_DELIMITER = 9,
	NALU_TYPE_SEQ_END = 10,
	NALU_TYPE_STREAM_END = 11,
	NALU_TYPE_FILLER_DATA = 12,
	NALU_TYPE_SPS_EXT = 13,
	NALU_TYPE_PREFIX_UNIT = 14,
	NALU_TYPE_SUBSET_SPS = 15,
	NALU_TYPE_SLICE_AUX = 19,
	NALU_TYPE_SLICE_EXT = 20
पूर्ण;

क्रमागत hva_h264_sei_payload_type अणु
	SEI_BUFFERING_PERIOD = 0,
	SEI_PICTURE_TIMING = 1,
	SEI_STEREO_VIDEO_INFO = 21,
	SEI_FRAME_PACKING_ARRANGEMENT = 45
पूर्ण;

/*
 * stereo Video Info काष्ठा
 */
काष्ठा hva_h264_stereo_video_sei अणु
	u8 field_views_flag;
	u8 top_field_is_left_view_flag;
	u8 current_frame_is_left_view_flag;
	u8 next_frame_is_second_view_flag;
	u8 left_view_self_contained_flag;
	u8 right_view_self_contained_flag;
पूर्ण;

/*
 * काष्ठा hva_h264_td
 *
 * @frame_width: width in pixels of the buffer containing the input frame
 * @frame_height: height in pixels of the buffer containing the input frame
 * @frame_num: the parameter to be written in the slice header
 * @picture_coding_type: type I, P or B
 * @pic_order_cnt_type: POC mode, as defined in H264 std : can be 0,1,2
 * @first_picture_in_sequence: flag telling to encoder that this is the
 *			       first picture in a video sequence.
 *			       Used क्रम VBR
 * @slice_माप_प्रकारype: 0 = no स्थिरraपूर्णांक to बंद the slice
 *		     1= a slice is बंदd as soon as the slice_mb_size limit
 *			is reached
 *		     2= a slice is बंदd as soon as the slice_byte_size limit
 *			is reached
 *		     3= a slice is बंदd as soon as either the slice_byte_size
 *			limit or the slice_mb_size limit is reached
 * @slice_mb_size: defines the slice size in number of macroblocks
 *		   (used when slice_माप_प्रकारype=1 or slice_माप_प्रकारype=3)
 * @ir_param_option: defines the number of macroblocks per frame to be
 *		     refreshed by AIR algorithm OR the refresh period
 *		     by CIR algorithm
 * @पूर्णांकra_refresh_type: enables the adaptive पूर्णांकra refresh algorithm.
 *			Disable=0 / Adaptative=1 and Cycle=2 as पूर्णांकra refresh
 * @use_स्थिरrained_पूर्णांकra_flag: स्थिरrained_पूर्णांकra_pred_flag from PPS
 * @transक्रमm_mode: controls the use of 4x4/8x8 transक्रमm mode
 * @disable_deblocking_filter_idc:
 *		     0: specअगरies that all luma and chroma block edges of
 *			the slice are filtered.
 *		     1: specअगरies that deblocking is disabled क्रम all block
 *			edges of the slice.
 *		     2: specअगरies that all luma and chroma block edges of
 *			the slice are filtered with exception of the block edges
 *			that coincide with slice boundaries
 * @slice_alpha_c0_offset_भाग2: to be written in slice header,
 *				controls deblocking
 * @slice_beta_offset_भाग2: to be written in slice header,
 *			    controls deblocking
 * @encoder_complनिकासy: encoder complनिकासy control (IME).
 *		     0 = I_16x16, P_16x16, Full ME Complनिकासy
 *		     1 = I_16x16, I_NxN, P_16x16, Full ME Complनिकासy
 *		     2 = I_16x16, I_NXN, P_16x16, P_WxH, Full ME Complनिकासy
 *		     4 = I_16x16, P_16x16, Reduced ME Complनिकासy
 *		     5 = I_16x16, I_NxN, P_16x16, Reduced ME Complनिकासy
 *		     6 = I_16x16, I_NXN, P_16x16, P_WxH, Reduced ME Complनिकासy
 *  @chroma_qp_index_offset: coming from picture parameter set
 *			     (PPS see [H.264 STD] 7.4.2.2)
 *  @entropy_coding_mode: entropy coding mode.
 *			  0 = CAVLC
 *			  1 = CABAC
 * @brc_type: selects the bit-rate control algorithm
 *		     0 = स्थिरant Qp, (no BRC)
 *		     1 = CBR
 *		     2 = VBR
 * @quant: Quantization param used in हाल of fix QP encoding (no BRC)
 * @non_VCL_NALU_Size: size of non-VCL NALUs (SPS, PPS, filler),
 *		       used by BRC
 * @cpb_buffer_size: size of Coded Picture Buffer, used by BRC
 * @bit_rate: target bitrate, क्रम BRC
 * @qp_min: min QP threshold
 * @qp_max: max QP threshold
 * @framerate_num: target framerate numerator , used by BRC
 * @framerate_den: target framerate denomurator , used by BRC
 * @delay: End-to-End Initial Delay
 * @strict_HRD_compliancy: flag क्रम HDR compliancy (1)
 *			   May impact quality encoding
 * @addr_source_buffer: address of input frame buffer क्रम current frame
 * @addr_fwd_Ref_Buffer: address of reference frame buffer
 * @addr_rec_buffer: address of reस्थिरructed frame buffer
 * @addr_output_bitstream_start: output bitstream start address
 * @addr_output_bitstream_end: output bitstream end address
 * @addr_बाह्यal_sw : address of बाह्यal search winकरोw
 * @addr_lctx : address of context picture buffer
 * @addr_local_rec_buffer: address of local reस्थिरructed buffer
 * @addr_spatial_context: address of spatial context buffer
 * @bitstream_offset: offset in bits between aligned bitstream start
 *		      address and first bit to be written by HVA.
 *		      Range value is [0..63]
 * @sampling_mode: Input picture क्रमmat .
 *		     0: YUV420 semi_planar Interleaved
 *		     1: YUV422 raster Interleaved
 * @addr_param_out: address of output parameters काष्ठाure
 * @addr_scaling_matrix: address to the coefficient of
 *			 the inverse scaling matrix
 * @addr_scaling_matrix_dir: address to the coefficient of
 *			     the direct scaling matrix
 * @addr_cabac_context_buffer: address of cabac context buffer
 * @GmvX: Input inक्रमmation about the horizontal global displacement of
 *	  the encoded frame versus the previous one
 * @GmvY: Input inक्रमmation about the vertical global displacement of
 *	  the encoded frame versus the previous one
 * @winकरोw_width: width in pixels of the winकरोw to be encoded inside
 *		  the input frame
 * @winकरोw_height: width in pixels of the winकरोw to be encoded inside
 *		   the input frame
 * @winकरोw_horizontal_offset: horizontal offset in pels क्रम input winकरोw
 *			      within input frame
 * @winकरोw_vertical_offset: vertical offset in pels क्रम input winकरोw
 *			    within input frame
 * @addr_roi: Map of QP offset क्रम the Region of Interest algorithm and
 *	      also used क्रम Error map.
 *	      Bit 0-6 used क्रम qp offset (value -64 to 63).
 *	      Bit 7 used to क्रमce पूर्णांकra
 * @addr_slice_header: address to slice header
 * @slice_header_size_in_bits: size in bits of the Slice header
 * @slice_header_offset0: Slice header offset where to insert
 *			  first_Mb_in_slice
 * @slice_header_offset1: Slice header offset where to insert
 *			  slice_qp_delta
 * @slice_header_offset2: Slice header offset where to insert
 *			  num_MBs_in_slice
 * @slice_synchro_enable: enable "slice ready" पूर्णांकerrupt after each slice
 * @max_slice_number: Maximum number of slice in a frame
 *		      (0 is strictly क्रमbidden)
 * @rgb2_yuv_y_coeff: Four coefficients (C0C1C2C3) to convert from RGB to
 *		      YUV क्रम the Y component.
 *		      Y = C0*R + C1*G + C2*B + C3 (C0 is on byte 0)
 * @rgb2_yuv_u_coeff: four coefficients (C0C1C2C3) to convert from RGB to
 *		      YUV क्रम the Y component.
 *		      Y = C0*R + C1*G + C2*B + C3 (C0 is on byte 0)
 * @rgb2_yuv_v_coeff: Four coefficients (C0C1C2C3) to convert from RGB to
 *		      YUV क्रम the U (Cb) component.
 *		      U = C0*R + C1*G + C2*B + C3 (C0 is on byte 0)
 * @slice_byte_size: maximum slice size in bytes
 *		     (used when slice_माप_प्रकारype=2 or slice_माप_प्रकारype=3)
 * @max_air_पूर्णांकra_mb_nb: Maximum number of पूर्णांकra macroblock in a frame
 *			 क्रम the AIR algorithm
 * @brc_no_skip: Disable skipping in the Bitrate Controller
 * @addr_brc_in_out_parameter: address of अटल buffer क्रम BRC parameters
 */
काष्ठा hva_h264_td अणु
	u16 frame_width;
	u16 frame_height;
	u32 frame_num;
	u16 picture_coding_type;
	u16 reserved1;
	u16 pic_order_cnt_type;
	u16 first_picture_in_sequence;
	u16 slice_माप_प्रकारype;
	u16 reserved2;
	u32 slice_mb_size;
	u16 ir_param_option;
	u16 पूर्णांकra_refresh_type;
	u16 use_स्थिरrained_पूर्णांकra_flag;
	u16 transक्रमm_mode;
	u16 disable_deblocking_filter_idc;
	s16 slice_alpha_c0_offset_भाग2;
	s16 slice_beta_offset_भाग2;
	u16 encoder_complनिकासy;
	s16 chroma_qp_index_offset;
	u16 entropy_coding_mode;
	u16 brc_type;
	u16 quant;
	u32 non_vcl_nalu_size;
	u32 cpb_buffer_size;
	u32 bit_rate;
	u16 qp_min;
	u16 qp_max;
	u16 framerate_num;
	u16 framerate_den;
	u16 delay;
	u16 strict_hrd_compliancy;
	u32 addr_source_buffer;
	u32 addr_fwd_ref_buffer;
	u32 addr_rec_buffer;
	u32 addr_output_bitstream_start;
	u32 addr_output_bitstream_end;
	u32 addr_बाह्यal_sw;
	u32 addr_lctx;
	u32 addr_local_rec_buffer;
	u32 addr_spatial_context;
	u16 bitstream_offset;
	u16 sampling_mode;
	u32 addr_param_out;
	u32 addr_scaling_matrix;
	u32 addr_scaling_matrix_dir;
	u32 addr_cabac_context_buffer;
	u32 reserved3;
	u32 reserved4;
	s16 gmv_x;
	s16 gmv_y;
	u16 winकरोw_width;
	u16 winकरोw_height;
	u16 winकरोw_horizontal_offset;
	u16 winकरोw_vertical_offset;
	u32 addr_roi;
	u32 addr_slice_header;
	u16 slice_header_size_in_bits;
	u16 slice_header_offset0;
	u16 slice_header_offset1;
	u16 slice_header_offset2;
	u32 reserved5;
	u32 reserved6;
	u16 reserved7;
	u16 reserved8;
	u16 slice_synchro_enable;
	u16 max_slice_number;
	u32 rgb2_yuv_y_coeff;
	u32 rgb2_yuv_u_coeff;
	u32 rgb2_yuv_v_coeff;
	u32 slice_byte_size;
	u16 max_air_पूर्णांकra_mb_nb;
	u16 brc_no_skip;
	u32 addr_temporal_context;
	u32 addr_brc_in_out_parameter;
पूर्ण;

/*
 * काष्ठा hva_h264_slice_po
 *
 * @ slice_size: slice size
 * @ slice_start_समय: start समय
 * @ slice_stop_समय: stop समय
 * @ slice_num: slice number
 */
काष्ठा hva_h264_slice_po अणु
	u32 slice_size;
	u32 slice_start_समय;
	u32 slice_end_समय;
	u32 slice_num;
पूर्ण;

/*
 * काष्ठा hva_h264_po
 *
 * @ bitstream_size: bitstream size
 * @ dct_bitstream_size: dtc bitstream size
 * @ stuffing_bits: number of stuffing bits inserted by the encoder
 * @ removal_समय: removal समय of current frame (nb of ticks 1/framerate)
 * @ hvc_start_समय: hvc start समय
 * @ hvc_stop_समय: hvc stop समय
 * @ slice_count: slice count
 */
काष्ठा hva_h264_po अणु
	u32 bitstream_size;
	u32 dct_bitstream_size;
	u32 stuffing_bits;
	u32 removal_समय;
	u32 hvc_start_समय;
	u32 hvc_stop_समय;
	u32 slice_count;
	u32 reserved0;
	काष्ठा hva_h264_slice_po slice_params[16];
पूर्ण;

काष्ठा hva_h264_task अणु
	काष्ठा hva_h264_td td;
	काष्ठा hva_h264_po po;
पूर्ण;

/*
 * काष्ठा hva_h264_ctx
 *
 * @seq_info:  sequence inक्रमmation buffer
 * @ref_frame: reference frame buffer
 * @rec_frame: reस्थिरructed frame buffer
 * @task:      task descriptor
 */
काष्ठा hva_h264_ctx अणु
	काष्ठा hva_buffer *seq_info;
	काष्ठा hva_buffer *ref_frame;
	काष्ठा hva_buffer *rec_frame;
	काष्ठा hva_buffer *task;
पूर्ण;

अटल पूर्णांक hva_h264_fill_slice_header(काष्ठा hva_ctx *pctx,
				      u8 *slice_header_addr,
				      काष्ठा hva_controls *ctrls,
				      पूर्णांक frame_num,
				      u16 *header_size,
				      u16 *header_offset0,
				      u16 *header_offset1,
				      u16 *header_offset2)
अणु
	/*
	 * with this HVA hardware version, part of the slice header is computed
	 * on host and part by hardware.
	 * The part of host is precomputed and available through this array.
	 */
	काष्ठा device *dev = ctx_to_dev(pctx);
	पूर्णांक  cabac = V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC;
	अटल स्थिर अचिन्हित अक्षर slice_header[] = अणु
		0x00, 0x00, 0x00, 0x01,
		0x41, 0x34, 0x07, 0x00
	पूर्ण;
	पूर्णांक idr_pic_id = frame_num % 2;
	क्रमागत hva_picture_coding_type type;
	u32 frame_order = frame_num % ctrls->gop_size;

	अगर (!(frame_num % ctrls->gop_size))
		type = PICTURE_CODING_TYPE_I;
	अन्यथा
		type = PICTURE_CODING_TYPE_P;

	स_नकल(slice_header_addr, slice_header, माप(slice_header));

	*header_size = 56;
	*header_offset0 = 40;
	*header_offset1 = 13;
	*header_offset2 = 0;

	अगर (type == PICTURE_CODING_TYPE_I) अणु
		slice_header_addr[4] = 0x65;
		slice_header_addr[5] = 0x11;

		/* toggle the I frame */
		अगर ((frame_num / ctrls->gop_size) % 2) अणु
			*header_size += 4;
			*header_offset1 += 4;
			slice_header_addr[6] = 0x04;
			slice_header_addr[7] = 0x70;

		पूर्ण अन्यथा अणु
			*header_size += 2;
			*header_offset1 += 2;
			slice_header_addr[6] = 0x09;
			slice_header_addr[7] = 0xC0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ctrls->entropy_mode == cabac) अणु
			*header_size += 1;
			*header_offset1 += 1;
			slice_header_addr[7] = 0x80;
		पूर्ण
		/*
		 * update slice header with P frame order
		 * frame order is limited to 16 (coded on 4bits only)
		 */
		slice_header_addr[5] += ((frame_order & 0x0C) >> 2);
		slice_header_addr[6] += ((frame_order & 0x03) << 6);
	पूर्ण

	dev_dbg(dev,
		"%s   %s slice header order %d idrPicId %d header size %d\n",
		pctx->name, __func__, frame_order, idr_pic_id, *header_size);
	वापस 0;
पूर्ण

अटल पूर्णांक hva_h264_fill_data_nal(काष्ठा hva_ctx *pctx,
				  अचिन्हित पूर्णांक stuffing_bytes, u8 *addr,
				  अचिन्हित पूर्णांक stream_size, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा device *dev = ctx_to_dev(pctx);
	अटल स्थिर u8 start[] = अणु 0x00, 0x00, 0x00, 0x01 पूर्ण;

	dev_dbg(dev, "%s   %s stuffing bytes %d\n", pctx->name, __func__,
		stuffing_bytes);

	अगर ((*size + stuffing_bytes + H264_FILLER_DATA_SIZE) > stream_size) अणु
		dev_dbg(dev, "%s   %s too many stuffing bytes %d\n",
			pctx->name, __func__, stuffing_bytes);
		वापस 0;
	पूर्ण

	/* start code */
	स_नकल(addr + *size, start, माप(start));
	*size += माप(start);

	/* nal_unit_type */
	addr[*size] = NALU_TYPE_FILLER_DATA;
	*size += 1;

	स_रखो(addr + *size, 0xff, stuffing_bytes);
	*size += stuffing_bytes;

	addr[*size] = 0x80;
	*size += 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_h264_fill_sei_nal(काष्ठा hva_ctx *pctx,
				 क्रमागत hva_h264_sei_payload_type type,
				 u8 *addr, u32 *size)
अणु
	काष्ठा device *dev = ctx_to_dev(pctx);
	अटल स्थिर u8 start[] = अणु 0x00, 0x00, 0x00, 0x01 पूर्ण;
	काष्ठा hva_h264_stereo_video_sei info;
	u8 offset = 7;
	u8 msg = 0;

	/* start code */
	स_नकल(addr + *size, start, माप(start));
	*size += माप(start);

	/* nal_unit_type */
	addr[*size] = NALU_TYPE_SEI;
	*size += 1;

	/* payload type */
	addr[*size] = type;
	*size += 1;

	चयन (type) अणु
	हाल SEI_STEREO_VIDEO_INFO:
		स_रखो(&info, 0, माप(info));

		/* set to top/bottom frame packing arrangement */
		info.field_views_flag = 1;
		info.top_field_is_left_view_flag = 1;

		/* payload size */
		addr[*size] = 1;
		*size += 1;

		/* payload */
		msg = info.field_views_flag << offset--;

		अगर (info.field_views_flag) अणु
			msg |= info.top_field_is_left_view_flag <<
			       offset--;
		पूर्ण अन्यथा अणु
			msg |= info.current_frame_is_left_view_flag <<
			       offset--;
			msg |= info.next_frame_is_second_view_flag <<
			       offset--;
		पूर्ण
		msg |= info.left_view_self_contained_flag << offset--;
		msg |= info.right_view_self_contained_flag << offset--;

		addr[*size] = msg;
		*size += 1;

		addr[*size] = 0x80;
		*size += 1;

		वापस 0;
	हाल SEI_BUFFERING_PERIOD:
	हाल SEI_PICTURE_TIMING:
	हाल SEI_FRAME_PACKING_ARRANGEMENT:
	शेष:
		dev_err(dev, "%s   sei nal type not supported %d\n",
			pctx->name, type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hva_h264_prepare_task(काष्ठा hva_ctx *pctx,
				 काष्ठा hva_h264_task *task,
				 काष्ठा hva_frame *frame,
				 काष्ठा hva_stream *stream)
अणु
	काष्ठा hva_dev *hva = ctx_to_hdev(pctx);
	काष्ठा device *dev = ctx_to_dev(pctx);
	काष्ठा hva_h264_ctx *ctx = (काष्ठा hva_h264_ctx *)pctx->priv;
	काष्ठा hva_buffer *seq_info = ctx->seq_info;
	काष्ठा hva_buffer *fwd_ref_frame = ctx->ref_frame;
	काष्ठा hva_buffer *loc_rec_frame = ctx->rec_frame;
	काष्ठा hva_h264_td *td = &task->td;
	काष्ठा hva_controls *ctrls = &pctx->ctrls;
	काष्ठा v4l2_fract *समय_per_frame = &pctx->ctrls.समय_per_frame;
	पूर्णांक cavlc =  V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC;
	u32 frame_num = pctx->stream_num;
	u32 addr_esram = hva->esram_addr;
	क्रमागत v4l2_mpeg_video_h264_level level;
	dma_addr_t paddr = 0;
	u8 *slice_header_vaddr;
	u32 frame_width = frame->info.aligned_width;
	u32 frame_height = frame->info.aligned_height;
	u32 max_cpb_buffer_size;
	अचिन्हित पूर्णांक payload = stream->bytesused;
	u32 max_bitrate;

	/* check width and height parameters */
	अगर ((frame_width > max(H264_MAX_SIZE_W, H264_MAX_SIZE_H)) ||
	    (frame_height > max(H264_MAX_SIZE_W, H264_MAX_SIZE_H))) अणु
		dev_err(dev,
			"%s   width(%d) or height(%d) exceeds limits (%dx%d)\n",
			pctx->name, frame_width, frame_height,
			H264_MAX_SIZE_W, H264_MAX_SIZE_H);
		pctx->frame_errors++;
		वापस -EINVAL;
	पूर्ण

	level = ctrls->level;

	स_रखो(td, 0, माप(काष्ठा hva_h264_td));

	td->frame_width = frame_width;
	td->frame_height = frame_height;

	/* set frame alignment */
	td->winकरोw_width =  frame_width;
	td->winकरोw_height = frame_height;
	td->winकरोw_horizontal_offset = 0;
	td->winकरोw_vertical_offset = 0;

	td->first_picture_in_sequence = (!frame_num) ? 1 : 0;

	/* pic_order_cnt_type hard coded to '2' as only I & P frames */
	td->pic_order_cnt_type = 2;

	/* useConstrainedIntraFlag set to false क्रम better coding efficiency */
	td->use_स्थिरrained_पूर्णांकra_flag = false;
	td->brc_type = (ctrls->bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
			? BRC_TYPE_CBR : BRC_TYPE_VBR;

	td->entropy_coding_mode = (ctrls->entropy_mode == cavlc) ? CAVLC :
				  CABAC;

	td->bit_rate = ctrls->bitrate;

	/* set framerate, framerate = 1 n/ समय per frame */
	अगर (समय_per_frame->numerator >= 536) अणु
		/*
		 * due to a hardware bug, framerate denominator can't exceed
		 * 536 (BRC overflow). Compute nearest framerate
		 */
		td->framerate_den = 1;
		td->framerate_num = (समय_per_frame->denominator +
				    (समय_per_frame->numerator >> 1) - 1) /
				    समय_per_frame->numerator;

		/*
		 * update bitrate to पूर्णांकroduce a correction due to
		 * the new framerate
		 * new bitrate = (old bitrate * new framerate) / old framerate
		 */
		td->bit_rate /= समय_per_frame->numerator;
		td->bit_rate *= समय_per_frame->denominator;
		td->bit_rate /= td->framerate_num;
	पूर्ण अन्यथा अणु
		td->framerate_den = समय_per_frame->numerator;
		td->framerate_num = समय_per_frame->denominator;
	पूर्ण

	/* compute maximum bitrate depending on profile */
	अगर (ctrls->profile >= V4L2_MPEG_VIDEO_H264_PROखाता_HIGH)
		max_bitrate = h264_infos_list[level].max_bitrate *
			      H264_FACTOR_HIGH;
	अन्यथा
		max_bitrate = h264_infos_list[level].max_bitrate *
			      H264_FACTOR_BASELINE;

	/* check अगर bitrate करोesn't exceed max size */
	अगर (td->bit_rate > max_bitrate) अणु
		dev_dbg(dev,
			"%s   bitrate (%d) larger than level and profile allow, clip to %d\n",
			pctx->name, td->bit_rate, max_bitrate);
		td->bit_rate = max_bitrate;
	पूर्ण

	/* convert cpb_buffer_size in bits */
	td->cpb_buffer_size = ctrls->cpb_size * 8000;

	/* compute maximum cpb buffer size depending on profile */
	अगर (ctrls->profile >= V4L2_MPEG_VIDEO_H264_PROखाता_HIGH)
		max_cpb_buffer_size =
		    h264_infos_list[level].max_cpb_size * H264_FACTOR_HIGH;
	अन्यथा
		max_cpb_buffer_size =
		    h264_infos_list[level].max_cpb_size * H264_FACTOR_BASELINE;

	/* check अगर cpb buffer size करोesn't exceed max size */
	अगर (td->cpb_buffer_size > max_cpb_buffer_size) अणु
		dev_dbg(dev,
			"%s   cpb size larger than level %d allows, clip to %d\n",
			pctx->name, td->cpb_buffer_size, max_cpb_buffer_size);
		td->cpb_buffer_size = max_cpb_buffer_size;
	पूर्ण

	/* enable skipping in the Bitrate Controller */
	td->brc_no_skip = 0;

	/* initial delay */
	अगर ((ctrls->bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR) &&
	    td->bit_rate)
		td->delay = 1000 * (td->cpb_buffer_size / td->bit_rate);
	अन्यथा
		td->delay = 0;

	चयन (frame->info.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
		td->sampling_mode = SAMPLING_MODE_NV12;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
		td->sampling_mode = SAMPLING_MODE_NV21;
		अवरोध;
	शेष:
		dev_err(dev, "%s   invalid source pixel format\n",
			pctx->name);
		pctx->frame_errors++;
		वापस -EINVAL;
	पूर्ण

	/*
	 * fill matrix color converter (RGB to YUV)
	 * Y = 0,299 R + 0,587 G + 0,114 B
	 * Cb = -0,1687 R -0,3313 G + 0,5 B + 128
	 * Cr = 0,5 R - 0,4187 G - 0,0813 B + 128
	 */
	td->rgb2_yuv_y_coeff = 0x12031008;
	td->rgb2_yuv_u_coeff = 0x800EF7FB;
	td->rgb2_yuv_v_coeff = 0x80FEF40E;

	/* enable/disable transक्रमm mode */
	td->transक्रमm_mode = ctrls->dct8x8;

	/* encoder complनिकासy fix to 2, ENCODE_I_16x16_I_NxN_P_16x16_P_WxH */
	td->encoder_complनिकासy = 2;

	/* quant fix to 28, शेष VBR value */
	td->quant = 28;

	अगर (td->framerate_den == 0) अणु
		dev_err(dev, "%s   invalid framerate\n", pctx->name);
		pctx->frame_errors++;
		वापस -EINVAL;
	पूर्ण

	/* अगर स्वतःmatic framerate, deactivate bitrate controller */
	अगर (td->framerate_num == 0)
		td->brc_type = 0;

	/* compliancy fix to true */
	td->strict_hrd_compliancy = 1;

	/* set minimum & maximum quantizers */
	td->qp_min = clamp_val(ctrls->qpmin, 0, 51);
	td->qp_max = clamp_val(ctrls->qpmax, 0, 51);

	td->addr_source_buffer = frame->paddr;
	td->addr_fwd_ref_buffer = fwd_ref_frame->paddr;
	td->addr_rec_buffer = loc_rec_frame->paddr;

	td->addr_output_bitstream_end = (u32)stream->paddr + stream->size;

	td->addr_output_bitstream_start = (u32)stream->paddr;
	td->bitstream_offset = (((u32)stream->paddr & 0xF) << 3) &
			       BITSTREAM_OFFSET_MASK;

	td->addr_param_out = (u32)ctx->task->paddr +
			     दुरत्व(काष्ठा hva_h264_task, po);

	/* swap spatial and temporal context */
	अगर (frame_num % 2) अणु
		paddr = seq_info->paddr;
		td->addr_spatial_context =  ALIGN(paddr, 0x100);
		paddr = seq_info->paddr + DATA_SIZE(frame_width,
							frame_height);
		td->addr_temporal_context = ALIGN(paddr, 0x100);
	पूर्ण अन्यथा अणु
		paddr = seq_info->paddr;
		td->addr_temporal_context = ALIGN(paddr, 0x100);
		paddr = seq_info->paddr + DATA_SIZE(frame_width,
							frame_height);
		td->addr_spatial_context =  ALIGN(paddr, 0x100);
	पूर्ण

	paddr = seq_info->paddr + 2 * DATA_SIZE(frame_width, frame_height);

	td->addr_brc_in_out_parameter =  ALIGN(paddr, 0x100);

	paddr = td->addr_brc_in_out_parameter + BRC_DATA_SIZE;
	td->addr_slice_header =  ALIGN(paddr, 0x100);
	td->addr_बाह्यal_sw =  ALIGN(addr_esram, 0x100);

	addr_esram += SEARCH_WINDOW_BUFFER_MAX_SIZE(frame_width);
	td->addr_local_rec_buffer = ALIGN(addr_esram, 0x100);

	addr_esram += LOCAL_RECONSTRUCTED_BUFFER_MAX_SIZE(frame_width);
	td->addr_lctx = ALIGN(addr_esram, 0x100);

	addr_esram += CTX_MB_BUFFER_MAX_SIZE(max(frame_width, frame_height));
	td->addr_cabac_context_buffer = ALIGN(addr_esram, 0x100);

	अगर (!(frame_num % ctrls->gop_size)) अणु
		td->picture_coding_type = PICTURE_CODING_TYPE_I;
		stream->vbuf.flags |= V4L2_BUF_FLAG_KEYFRAME;
	पूर्ण अन्यथा अणु
		td->picture_coding_type = PICTURE_CODING_TYPE_P;
		stream->vbuf.flags &= ~V4L2_BUF_FLAG_KEYFRAME;
	पूर्ण

	/* fill the slice header part */
	slice_header_vaddr = seq_info->vaddr + (td->addr_slice_header -
			     seq_info->paddr);

	hva_h264_fill_slice_header(pctx, slice_header_vaddr, ctrls, frame_num,
				   &td->slice_header_size_in_bits,
				   &td->slice_header_offset0,
				   &td->slice_header_offset1,
				   &td->slice_header_offset2);

	td->chroma_qp_index_offset = 2;
	td->slice_synchro_enable = 0;
	td->max_slice_number = 1;

	/*
	 * check the sps/pps header size क्रम key frame only
	 * sps/pps header was previously fill by libv4l
	 * during qbuf of stream buffer
	 */
	अगर ((stream->vbuf.flags == V4L2_BUF_FLAG_KEYFRAME) &&
	    (payload > MAX_SPS_PPS_SIZE)) अणु
		dev_err(dev, "%s   invalid sps/pps size %d\n", pctx->name,
			payload);
		pctx->frame_errors++;
		वापस -EINVAL;
	पूर्ण

	अगर (stream->vbuf.flags != V4L2_BUF_FLAG_KEYFRAME)
		payload = 0;

	/* add SEI nal (video stereo info) */
	अगर (ctrls->sei_fp && hva_h264_fill_sei_nal(pctx, SEI_STEREO_VIDEO_INFO,
						   (u8 *)stream->vaddr,
						   &payload)) अणु
		dev_err(dev, "%s   fail to get SEI nal\n", pctx->name);
		pctx->frame_errors++;
		वापस -EINVAL;
	पूर्ण

	/* fill size of non-VCL NAL units (SPS, PPS, filler and SEI) */
	td->non_vcl_nalu_size = payload * 8;

	/* compute bitstream offset & new start address of bitstream */
	td->addr_output_bitstream_start += ((payload >> 4) << 4);
	td->bitstream_offset += (payload - ((payload >> 4) << 4)) * 8;

	stream->bytesused = payload;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक hva_h264_get_stream_size(काष्ठा hva_h264_task *task)
अणु
	काष्ठा hva_h264_po *po = &task->po;

	वापस po->bitstream_size;
पूर्ण

अटल u32 hva_h264_get_stuffing_bytes(काष्ठा hva_h264_task *task)
अणु
	काष्ठा hva_h264_po *po = &task->po;

	वापस po->stuffing_bits >> 3;
पूर्ण

अटल पूर्णांक hva_h264_खोलो(काष्ठा hva_ctx *pctx)
अणु
	काष्ठा device *dev = ctx_to_dev(pctx);
	काष्ठा hva_h264_ctx *ctx;
	काष्ठा hva_dev *hva = ctx_to_hdev(pctx);
	u32 frame_width = pctx->frameinfo.aligned_width;
	u32 frame_height = pctx->frameinfo.aligned_height;
	u32 size;
	पूर्णांक ret;

	/* check esram size necessary to encode a frame */
	size = SEARCH_WINDOW_BUFFER_MAX_SIZE(frame_width) +
	       LOCAL_RECONSTRUCTED_BUFFER_MAX_SIZE(frame_width) +
	       CTX_MB_BUFFER_MAX_SIZE(max(frame_width, frame_height)) +
	       CABAC_CONTEXT_BUFFER_MAX_SIZE(frame_width);

	अगर (hva->esram_size < size) अणु
		dev_err(dev, "%s   not enough esram (max:%d request:%d)\n",
			pctx->name, hva->esram_size, size);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* allocate context क्रम codec */
	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* allocate sequence info buffer */
	ret = hva_mem_alloc(pctx,
			    2 * DATA_SIZE(frame_width, frame_height) +
			    SLICE_HEADER_SIZE +
			    BRC_DATA_SIZE,
			    "hva sequence info",
			    &ctx->seq_info);
	अगर (ret) अणु
		dev_err(dev,
			"%s   failed to allocate sequence info buffer\n",
			pctx->name);
		जाओ err_ctx;
	पूर्ण

	/* allocate reference frame buffer */
	ret = hva_mem_alloc(pctx,
			    frame_width * frame_height * 3 / 2,
			    "hva reference frame",
			    &ctx->ref_frame);
	अगर (ret) अणु
		dev_err(dev, "%s   failed to allocate reference frame buffer\n",
			pctx->name);
		जाओ err_seq_info;
	पूर्ण

	/* allocate reस्थिरructed frame buffer */
	ret = hva_mem_alloc(pctx,
			    frame_width * frame_height * 3 / 2,
			    "hva reconstructed frame",
			    &ctx->rec_frame);
	अगर (ret) अणु
		dev_err(dev,
			"%s   failed to allocate reconstructed frame buffer\n",
			pctx->name);
		जाओ err_ref_frame;
	पूर्ण

	/* allocate task descriptor */
	ret = hva_mem_alloc(pctx,
			    माप(काष्ठा hva_h264_task),
			    "hva task descriptor",
			    &ctx->task);
	अगर (ret) अणु
		dev_err(dev,
			"%s   failed to allocate task descriptor\n",
			pctx->name);
		जाओ err_rec_frame;
	पूर्ण

	pctx->priv = (व्योम *)ctx;

	वापस 0;

err_rec_frame:
	hva_mem_मुक्त(pctx, ctx->rec_frame);
err_ref_frame:
	hva_mem_मुक्त(pctx, ctx->ref_frame);
err_seq_info:
	hva_mem_मुक्त(pctx, ctx->seq_info);
err_ctx:
	devm_kमुक्त(dev, ctx);
err:
	pctx->sys_errors++;
	वापस ret;
पूर्ण

अटल पूर्णांक hva_h264_बंद(काष्ठा hva_ctx *pctx)
अणु
	काष्ठा hva_h264_ctx *ctx = (काष्ठा hva_h264_ctx *)pctx->priv;
	काष्ठा device *dev = ctx_to_dev(pctx);

	अगर (ctx->seq_info)
		hva_mem_मुक्त(pctx, ctx->seq_info);

	अगर (ctx->ref_frame)
		hva_mem_मुक्त(pctx, ctx->ref_frame);

	अगर (ctx->rec_frame)
		hva_mem_मुक्त(pctx, ctx->rec_frame);

	अगर (ctx->task)
		hva_mem_मुक्त(pctx, ctx->task);

	devm_kमुक्त(dev, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक hva_h264_encode(काष्ठा hva_ctx *pctx, काष्ठा hva_frame *frame,
			   काष्ठा hva_stream *stream)
अणु
	काष्ठा hva_h264_ctx *ctx = (काष्ठा hva_h264_ctx *)pctx->priv;
	काष्ठा hva_h264_task *task = (काष्ठा hva_h264_task *)ctx->task->vaddr;
	u32 stuffing_bytes = 0;
	पूर्णांक ret = 0;

	ret = hva_h264_prepare_task(pctx, task, frame, stream);
	अगर (ret)
		जाओ err;

	ret = hva_hw_execute_task(pctx, H264_ENC, ctx->task);
	अगर (ret)
		जाओ err;

	pctx->stream_num++;
	stream->bytesused += hva_h264_get_stream_size(task);

	stuffing_bytes = hva_h264_get_stuffing_bytes(task);

	अगर (stuffing_bytes)
		hva_h264_fill_data_nal(pctx, stuffing_bytes,
				       (u8 *)stream->vaddr,
				       stream->size,
				       &stream->bytesused);

	/* चयन reference & reस्थिरructed frame */
	swap(ctx->ref_frame, ctx->rec_frame);

	वापस 0;
err:
	stream->bytesused = 0;
	वापस ret;
पूर्ण

स्थिर काष्ठा hva_enc nv12h264enc = अणु
	.name = "H264(NV12)",
	.pixelक्रमmat = V4L2_PIX_FMT_NV12,
	.streamक्रमmat = V4L2_PIX_FMT_H264,
	.max_width = H264_MAX_SIZE_W,
	.max_height = H264_MAX_SIZE_H,
	.खोलो = hva_h264_खोलो,
	.बंद = hva_h264_बंद,
	.encode = hva_h264_encode,
पूर्ण;

स्थिर काष्ठा hva_enc nv21h264enc = अणु
	.name = "H264(NV21)",
	.pixelक्रमmat = V4L2_PIX_FMT_NV21,
	.streamक्रमmat = V4L2_PIX_FMT_H264,
	.max_width = H264_MAX_SIZE_W,
	.max_height = H264_MAX_SIZE_H,
	.खोलो = hva_h264_खोलो,
	.बंद = hva_h264_बंद,
	.encode = hva_h264_encode,
पूर्ण;
