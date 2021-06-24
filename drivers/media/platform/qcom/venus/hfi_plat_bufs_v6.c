<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <linux/videodev2.h>

#समावेश "hfi.h"
#समावेश "hfi_plat_bufs.h"
#समावेश "helpers.h"

#घोषणा MIN_INPUT_BUFFERS				4
#घोषणा MIN_ENC_OUTPUT_BUFFERS				4

#घोषणा NV12_UBWC_Y_TILE_WIDTH				32
#घोषणा NV12_UBWC_Y_TILE_HEIGHT				8
#घोषणा NV12_UBWC_UV_TILE_WIDTH				16
#घोषणा NV12_UBWC_UV_TILE_HEIGHT			8
#घोषणा TP10_UBWC_Y_TILE_WIDTH				48
#घोषणा TP10_UBWC_Y_TILE_HEIGHT				4
#घोषणा METADATA_STRIDE_MULTIPLE			64
#घोषणा METADATA_HEIGHT_MULTIPLE			16
#घोषणा HFI_DMA_ALIGNMENT				256

#घोषणा MAX_FE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE		64
#घोषणा MAX_FE_NBR_CTRL_LCU32_LINE_BUFFER_SIZE		64
#घोषणा MAX_FE_NBR_CTRL_LCU16_LINE_BUFFER_SIZE		64
#घोषणा MAX_FE_NBR_DATA_LUMA_LINE_BUFFER_SIZE		640
#घोषणा MAX_FE_NBR_DATA_CB_LINE_BUFFER_SIZE		320
#घोषणा MAX_FE_NBR_DATA_CR_LINE_BUFFER_SIZE		320

#घोषणा MAX_SE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE		(128 / 8)
#घोषणा MAX_SE_NBR_CTRL_LCU32_LINE_BUFFER_SIZE		(128 / 8)
#घोषणा MAX_SE_NBR_CTRL_LCU16_LINE_BUFFER_SIZE		(128 / 8)

#घोषणा MAX_PE_NBR_DATA_LCU64_LINE_BUFFER_SIZE		(64 * 2 * 3)
#घोषणा MAX_PE_NBR_DATA_LCU32_LINE_BUFFER_SIZE		(32 * 2 * 3)
#घोषणा MAX_PE_NBR_DATA_LCU16_LINE_BUFFER_SIZE		(16 * 2 * 3)

#घोषणा MAX_TILE_COLUMNS				32 /* 8K/256 */

#घोषणा VPP_CMD_MAX_SIZE				BIT(20)
#घोषणा NUM_HW_PIC_BUF					32
#घोषणा BIN_BUFFER_THRESHOLD				(1280 * 736)
#घोषणा H264D_MAX_SLICE					1800
/* माप(h264d_buftab_t) aligned to 256 */
#घोषणा SIZE_H264D_BUFTAB_T				256
/* माप(h264d_hw_pic_t) aligned to 32 */
#घोषणा SIZE_H264D_HW_PIC_T				BIT(11)
#घोषणा SIZE_H264D_BSE_CMD_PER_BUF			(32 * 4)
#घोषणा SIZE_H264D_VPP_CMD_PER_BUF			512

/* Line Buffer definitions, One क्रम Luma and 1/2 क्रम each Chroma */
#घोषणा SIZE_H264D_LB_FE_TOP_DATA(width, height)	\
	(MAX_FE_NBR_DATA_LUMA_LINE_BUFFER_SIZE * ALIGN((width), 16) * 3)

#घोषणा SIZE_H264D_LB_FE_TOP_CTRL(width, height)	\
	(MAX_FE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE * (((width) + 15) >> 4))

#घोषणा SIZE_H264D_LB_FE_LEFT_CTRL(width, height)	\
	(MAX_FE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE * (((height) + 15) >> 4))

#घोषणा SIZE_H264D_LB_SE_TOP_CTRL(width, height)	\
	(MAX_SE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE * (((width) + 15) >> 4))

#घोषणा SIZE_H264D_LB_SE_LEFT_CTRL(width, height)	\
	(MAX_SE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE * (((height) + 15) >> 4))

#घोषणा SIZE_H264D_LB_PE_TOP_DATA(width, height)	\
	(MAX_PE_NBR_DATA_LCU64_LINE_BUFFER_SIZE * (((width) + 15) >> 4))

#घोषणा SIZE_H264D_LB_VSP_TOP(width, height)	(((((width) + 15) >> 4) << 7))

#घोषणा SIZE_H264D_LB_RECON_DMA_METADATA_WR(width, height)	\
	(ALIGN((height), 16) * 32)

#घोषणा SIZE_H264D_QP(width, height)	\
	((((width) + 63) >> 6) * (((height) + 63) >> 6) * 128)

#घोषणा SIZE_HW_PIC(size_per_buf)	(NUM_HW_PIC_BUF * (size_per_buf))

#घोषणा H264_CABAC_HDR_RATIO_HD_TOT	1
#घोषणा H264_CABAC_RES_RATIO_HD_TOT	3

/*
 * Some content need more bin buffer, but limit buffer
 * size क्रम high resolution
 */
#घोषणा NUM_SLIST_BUF_H264		(256 + 32)
#घोषणा SIZE_SLIST_BUF_H264		512
#घोषणा LCU_MAX_SIZE_PELS		64
#घोषणा LCU_MIN_SIZE_PELS		16
#घोषणा SIZE_SEI_USERDATA		4096

#घोषणा H265D_MAX_SLICE			600
#घोषणा SIZE_H265D_HW_PIC_T		SIZE_H264D_HW_PIC_T
#घोषणा SIZE_H265D_BSE_CMD_PER_BUF	(16 * माप(u32))
#घोषणा SIZE_H265D_VPP_CMD_PER_BUF	256

#घोषणा SIZE_H265D_LB_FE_TOP_DATA(width, height)	\
	(MAX_FE_NBR_DATA_LUMA_LINE_BUFFER_SIZE * (ALIGN(width, 64) + 8) * 2)

#घोषणा SIZE_H265D_LB_FE_TOP_CTRL(width, height)	\
	(MAX_FE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE *	\
	(ALIGN(width, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS))

#घोषणा SIZE_H265D_LB_FE_LEFT_CTRL(width, height)	\
	(MAX_FE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE *	\
	(ALIGN(height, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS))

#घोषणा SIZE_H265D_LB_SE_TOP_CTRL(width, height)	\
	((LCU_MAX_SIZE_PELS / 8 * (128 / 8)) * (((width) + 15) >> 4))

अटल अंतरभूत u32 size_h265d_lb_se_left_ctrl(u32 width, u32 height)
अणु
	u32 x, y, z;

	x = ((height + 16 - 1) / 8) * MAX_SE_NBR_CTRL_LCU16_LINE_BUFFER_SIZE;
	y = ((height + 32 - 1) / 8) * MAX_SE_NBR_CTRL_LCU32_LINE_BUFFER_SIZE;
	z = ((height + 64 - 1) / 8) * MAX_SE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE;

	वापस max3(x, y, z);
पूर्ण

#घोषणा SIZE_H265D_LB_PE_TOP_DATA(width, height)	\
	(MAX_PE_NBR_DATA_LCU64_LINE_BUFFER_SIZE *	\
	(ALIGN(width, LCU_MIN_SIZE_PELS) / LCU_MIN_SIZE_PELS))

#घोषणा SIZE_H265D_LB_VSP_TOP(width, height)	((((width) + 63) >> 6) * 128)

#घोषणा SIZE_H265D_LB_VSP_LEFT(width, height)	((((height) + 63) >> 6) * 128)

#घोषणा SIZE_H265D_LB_RECON_DMA_METADATA_WR(width, height)	\
	SIZE_H264D_LB_RECON_DMA_METADATA_WR(width, height)

#घोषणा SIZE_H265D_QP(width, height)	SIZE_H264D_QP(width, height)

#घोषणा H265_CABAC_HDR_RATIO_HD_TOT	2
#घोषणा H265_CABAC_RES_RATIO_HD_TOT	2

/*
 * Some content need more bin buffer, but limit buffer size
 * क्रम high resolution
 */
#घोषणा SIZE_SLIST_BUF_H265	BIT(10)
#घोषणा NUM_SLIST_BUF_H265	(80 + 20)
#घोषणा H265_NUM_TILE_COL	32
#घोषणा H265_NUM_TILE_ROW	128
#घोषणा H265_NUM_TILE		(H265_NUM_TILE_ROW * H265_NUM_TILE_COL + 1)

अटल अंतरभूत u32 size_vpxd_lb_fe_left_ctrl(u32 width, u32 height)
अणु
	u32 x, y, z;

	x = ((height + 15) >> 4) * MAX_FE_NBR_CTRL_LCU16_LINE_BUFFER_SIZE;
	y = ((height + 31) >> 5) * MAX_FE_NBR_CTRL_LCU32_LINE_BUFFER_SIZE;
	z = ((height + 63) >> 6) * MAX_FE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE;

	वापस max3(x, y, z);
पूर्ण

#घोषणा SIZE_VPXD_LB_FE_TOP_CTRL(width, height)		\
	(((ALIGN(width, 64) + 8) * 10 * 2)) /* small line */
#घोषणा SIZE_VPXD_LB_SE_TOP_CTRL(width, height) \
	((((width) + 15) >> 4) * MAX_FE_NBR_CTRL_LCU16_LINE_BUFFER_SIZE)

अटल अंतरभूत u32 size_vpxd_lb_se_left_ctrl(u32 width, u32 height)
अणु
	u32 x, y, z;

	x = ((height + 15) >> 4) * MAX_SE_NBR_CTRL_LCU16_LINE_BUFFER_SIZE;
	y = ((height + 31) >> 5) * MAX_SE_NBR_CTRL_LCU32_LINE_BUFFER_SIZE;
	z = ((height + 63) >> 6) * MAX_SE_NBR_CTRL_LCU64_LINE_BUFFER_SIZE;

	वापस max3(x, y, z);
पूर्ण

#घोषणा SIZE_VPXD_LB_RECON_DMA_METADATA_WR(width, height)	\
	ALIGN((ALIGN(height, 16) / (4 / 2)) * 64, 32)
#घोषणा SIZE_VP8D_LB_FE_TOP_DATA(width, height)			\
	((ALIGN(width, 16) + 8) * 10 * 2)
#घोषणा SIZE_VP9D_LB_FE_TOP_DATA(width, height)			\
	((ALIGN(ALIGN(width, 16), 64) + 8) * 10 * 2)
#घोषणा SIZE_VP8D_LB_PE_TOP_DATA(width, height)			\
	((ALIGN(width, 16) >> 4) * 64)
#घोषणा SIZE_VP9D_LB_PE_TOP_DATA(width, height)			\
	((ALIGN(ALIGN(width, 16), 64) >> 6) * 176)
#घोषणा SIZE_VP8D_LB_VSP_TOP(width, height)			\
	(((ALIGN(width, 16) >> 4) * 64 / 2) + 256)
#घोषणा SIZE_VP9D_LB_VSP_TOP(width, height)			\
	(((ALIGN(ALIGN(width, 16), 64) >> 6) * 64 * 8) + 256)

#घोषणा HFI_IRIS2_VP9D_COMV_SIZE				\
	((((8192 + 63) >> 6) * ((4320 + 63) >> 6) * 8 * 8 * 2 * 8))

#घोषणा VPX_DECODER_FRAME_CONCURENCY_LVL		2
#घोषणा VPX_DECODER_FRAME_BIN_HDR_BUDGET_RATIO_NUM	1
#घोषणा VPX_DECODER_FRAME_BIN_HDR_BUDGET_RATIO_DEN	2
#घोषणा VPX_DECODER_FRAME_BIN_RES_BUDGET_RATIO_NUM	3
#घोषणा VPX_DECODER_FRAME_BIN_RES_BUDGET_RATIO_DEN	2

#घोषणा VP8_NUM_FRAME_INFO_BUF			(5 + 1)
#घोषणा VP9_NUM_FRAME_INFO_BUF			32
#घोषणा VP8_NUM_PROBABILITY_TABLE_BUF		VP8_NUM_FRAME_INFO_BUF
#घोषणा VP9_NUM_PROBABILITY_TABLE_BUF		(VP9_NUM_FRAME_INFO_BUF + 4)
#घोषणा VP8_PROB_TABLE_SIZE			3840
#घोषणा VP9_PROB_TABLE_SIZE			3840

#घोषणा VP9_UDC_HEADER_BUF_SIZE			(3 * 128)
#घोषणा MAX_SUPERFRAME_HEADER_LEN		34
#घोषणा CCE_TILE_OFFSET_SIZE			ALIGN(32 * 4 * 4, 32)

#घोषणा QMATRIX_SIZE				(माप(u32) * 128 + 256)
#घोषणा MP2D_QPDUMP_SIZE			115200
#घोषणा HFI_IRIS2_ENC_PERSIST_SIZE		204800
#घोषणा HFI_MAX_COL_FRAME			6
#घोषणा HFI_VENUS_VENC_TRE_WB_BUFF_SIZE		(65 << 4) /* in Bytes */
#घोषणा HFI_VENUS_VENC_DB_LINE_BUFF_PER_MB	512
#घोषणा HFI_VENUS_VPPSG_MAX_REGISTERS		2048
#घोषणा HFI_VENUS_WIDTH_ALIGNMENT		128
#घोषणा HFI_VENUS_WIDTH_TEN_BIT_ALIGNMENT	192
#घोषणा HFI_VENUS_HEIGHT_ALIGNMENT		32

#घोषणा SYSTEM_LAL_TILE10	192
#घोषणा NUM_MBS_720P		(((1280 + 15) >> 4) * ((720 + 15) >> 4))
#घोषणा NUM_MBS_4K		(((4096 + 15) >> 4) * ((2304 + 15) >> 4))
#घोषणा MB_SIZE_IN_PIXEL	(16 * 16)
#घोषणा HDR10PLUS_PAYLOAD_SIZE		1024
#घोषणा HDR10_HIST_EXTRADATA_SIZE	4096

अटल u32 size_vpss_lb(u32 width, u32 height, u32 num_vpp_pipes)
अणु
	u32 vpss_4tap_top_buffer_size, vpss_भाग2_top_buffer_size;
	u32 vpss_4tap_left_buffer_size, vpss_भाग2_left_buffer_size;
	u32 opb_wr_top_line_luma_buf_size, opb_wr_top_line_chroma_buf_size;
	u32 opb_lb_wr_llb_y_buffer_size, opb_lb_wr_llb_uv_buffer_size;
	u32 macrotiling_size;
	u32 size = 0;

	vpss_4tap_top_buffer_size = 0;
	vpss_भाग2_top_buffer_size = 0;
	vpss_4tap_left_buffer_size = 0;
	vpss_भाग2_left_buffer_size = 0;

	macrotiling_size = 32;
	opb_wr_top_line_luma_buf_size =
		ALIGN(width, macrotiling_size) / macrotiling_size * 256;
	opb_wr_top_line_luma_buf_size =
		ALIGN(opb_wr_top_line_luma_buf_size, HFI_DMA_ALIGNMENT) +
		(MAX_TILE_COLUMNS - 1) * 256;
	opb_wr_top_line_luma_buf_size =
		max(opb_wr_top_line_luma_buf_size, (32 * ALIGN(height, 16)));
	opb_wr_top_line_chroma_buf_size = opb_wr_top_line_luma_buf_size;
	opb_lb_wr_llb_y_buffer_size = ALIGN((ALIGN(height, 16) / 2) * 64, 32);
	opb_lb_wr_llb_uv_buffer_size = opb_lb_wr_llb_y_buffer_size;
	size = num_vpp_pipes *
		2 * (vpss_4tap_top_buffer_size + vpss_भाग2_top_buffer_size) +
		2 * (vpss_4tap_left_buffer_size + vpss_भाग2_left_buffer_size) +
		opb_wr_top_line_luma_buf_size +
		opb_wr_top_line_chroma_buf_size +
		opb_lb_wr_llb_uv_buffer_size +
		opb_lb_wr_llb_y_buffer_size;

	वापस size;
पूर्ण

अटल u32 size_h264d_hw_bin_buffer(u32 width, u32 height)
अणु
	u32 size_yuv, size_bin_hdr, size_bin_res;
	u32 size = 0;
	u32 product;

	product = width * height;
	size_yuv = (product <= BIN_BUFFER_THRESHOLD) ?
		((BIN_BUFFER_THRESHOLD * 3) >> 1) : ((product * 3) >> 1);

	size_bin_hdr = size_yuv * H264_CABAC_HDR_RATIO_HD_TOT;
	size_bin_res = size_yuv * H264_CABAC_RES_RATIO_HD_TOT;
	size_bin_hdr = ALIGN(size_bin_hdr, HFI_DMA_ALIGNMENT);
	size_bin_res = ALIGN(size_bin_res, HFI_DMA_ALIGNMENT);
	size = size_bin_hdr + size_bin_res;

	वापस size;
पूर्ण

अटल u32 h264d_scratch_size(u32 width, u32 height, bool is_पूर्णांकerlaced)
अणु
	u32 aligned_width = ALIGN(width, 16);
	u32 aligned_height = ALIGN(height, 16);
	u32 size = 0;

	अगर (!is_पूर्णांकerlaced)
		size = size_h264d_hw_bin_buffer(aligned_width, aligned_height);

	वापस size;
पूर्ण

अटल u32 size_h265d_hw_bin_buffer(u32 width, u32 height)
अणु
	u32 size_yuv, size_bin_hdr, size_bin_res;
	u32 size = 0;
	u32 product;

	product = width * height;
	size_yuv = (product <= BIN_BUFFER_THRESHOLD) ?
		((BIN_BUFFER_THRESHOLD * 3) >> 1) : ((product * 3) >> 1);
	size_bin_hdr = size_yuv * H265_CABAC_HDR_RATIO_HD_TOT;
	size_bin_res = size_yuv * H265_CABAC_RES_RATIO_HD_TOT;
	size_bin_hdr = ALIGN(size_bin_hdr, HFI_DMA_ALIGNMENT);
	size_bin_res = ALIGN(size_bin_res, HFI_DMA_ALIGNMENT);
	size = size_bin_hdr + size_bin_res;

	वापस size;
पूर्ण

अटल u32 h265d_scratch_size(u32 width, u32 height, bool is_पूर्णांकerlaced)
अणु
	u32 aligned_width = ALIGN(width, 16);
	u32 aligned_height = ALIGN(height, 16);
	u32 size = 0;

	अगर (!is_पूर्णांकerlaced)
		size = size_h265d_hw_bin_buffer(aligned_width, aligned_height);

	वापस size;
पूर्ण

अटल u32 vpxd_scratch_size(u32 width, u32 height, bool is_पूर्णांकerlaced)
अणु
	u32 aligned_width = ALIGN(width, 16);
	u32 aligned_height = ALIGN(height, 16);
	u32 size_yuv = aligned_width * aligned_height * 3 / 2;
	u32 size = 0;

	अगर (!is_पूर्णांकerlaced) अणु
		u32 binbuffer1_size, binbufer2_size;

		binbuffer1_size = max_t(u32, size_yuv,
					((BIN_BUFFER_THRESHOLD * 3) >> 1));
		binbuffer1_size *= VPX_DECODER_FRAME_CONCURENCY_LVL *
				   VPX_DECODER_FRAME_BIN_HDR_BUDGET_RATIO_NUM /
				   VPX_DECODER_FRAME_BIN_HDR_BUDGET_RATIO_DEN;
		binbufer2_size = max_t(u32, size_yuv,
				       ((BIN_BUFFER_THRESHOLD * 3) >> 1));
		binbufer2_size *= VPX_DECODER_FRAME_CONCURENCY_LVL *
				  VPX_DECODER_FRAME_BIN_RES_BUDGET_RATIO_NUM /
				  VPX_DECODER_FRAME_BIN_RES_BUDGET_RATIO_DEN;
		size = ALIGN(binbuffer1_size + binbufer2_size,
			     HFI_DMA_ALIGNMENT);
	पूर्ण

	वापस size;
पूर्ण

अटल u32 mpeg2d_scratch_size(u32 width, u32 height, bool is_पूर्णांकerlaced)
अणु
	वापस 0;
पूर्ण

अटल u32 calculate_enc_output_frame_size(u32 width, u32 height, u32 rc_type)
अणु
	u32 aligned_width, aligned_height;
	u32 mbs_per_frame;
	u32 frame_size;

	/*
	 * Encoder output size calculation: 32 Align width/height
	 * For resolution < 720p : YUVsize * 4
	 * For resolution > 720p & <= 4K : YUVsize / 2
	 * For resolution > 4k : YUVsize / 4
	 * Initially frame_size = YUVsize * 2;
	 */
	aligned_width = ALIGN(width, 32);
	aligned_height = ALIGN(height, 32);
	mbs_per_frame = (ALIGN(aligned_height, 16) *
			 ALIGN(aligned_width, 16)) / 256;
	frame_size = width * height * 3;

	अगर (mbs_per_frame < NUM_MBS_720P)
		frame_size = frame_size << 1;
	अन्यथा अगर (mbs_per_frame <= NUM_MBS_4K)
		frame_size = frame_size >> 2;
	अन्यथा
		frame_size = frame_size >> 3;

	अगर (rc_type == HFI_RATE_CONTROL_OFF || rc_type == HFI_RATE_CONTROL_CQ)
		frame_size = frame_size << 1;

	/*
	 * In हाल of opaque color क्रमmat bitdepth will be known
	 * with first ETB, buffers allocated alपढ़ोy with 8 bit
	 * won't be sufficient क्रम 10 bit
	 * calculate size considering 10-bit by शेष
	 * For 10-bit हालs size = size * 1.25
	 */
	frame_size *= 5;
	frame_size /= 4;

	वापस ALIGN(frame_size, SZ_4K);
पूर्ण

अटल u32 calculate_enc_scratch_size(u32 width, u32 height, u32 work_mode,
				      u32 lcu_size, u32 num_vpp_pipes,
				      u32 rc_type)
अणु
	u32 aligned_width, aligned_height, bitstream_size;
	u32 total_bitbin_buffers, size_single_pipe, bitbin_size;
	u32 sao_bin_buffer_size, padded_bin_size, size;

	aligned_width = ALIGN(width, lcu_size);
	aligned_height = ALIGN(height, lcu_size);
	bitstream_size =
		calculate_enc_output_frame_size(width, height, rc_type);

	bitstream_size = ALIGN(bitstream_size, HFI_DMA_ALIGNMENT);

	अगर (work_mode == VIDC_WORK_MODE_2) अणु
		total_bitbin_buffers = 3;
		bitbin_size = bitstream_size * 17 / 10;
		bitbin_size = ALIGN(bitbin_size, HFI_DMA_ALIGNMENT);
	पूर्ण अन्यथा अणु
		total_bitbin_buffers = 1;
		bitstream_size = aligned_width * aligned_height * 3;
		bitbin_size = ALIGN(bitstream_size, HFI_DMA_ALIGNMENT);
	पूर्ण

	अगर (num_vpp_pipes > 2)
		size_single_pipe = bitbin_size / 2;
	अन्यथा
		size_single_pipe = bitbin_size;

	size_single_pipe = ALIGN(size_single_pipe, HFI_DMA_ALIGNMENT);
	sao_bin_buffer_size =
		(64 * (((width + 32) * (height + 32)) >> 10)) + 384;
	padded_bin_size = ALIGN(size_single_pipe, HFI_DMA_ALIGNMENT);
	size_single_pipe = sao_bin_buffer_size + padded_bin_size;
	size_single_pipe = ALIGN(size_single_pipe, HFI_DMA_ALIGNMENT);
	bitbin_size = size_single_pipe * num_vpp_pipes;
	size = ALIGN(bitbin_size, HFI_DMA_ALIGNMENT) *
		total_bitbin_buffers + 512;

	वापस size;
पूर्ण

अटल u32 h264e_scratch_size(u32 width, u32 height, u32 work_mode,
			      u32 num_vpp_pipes, u32 rc_type)
अणु
	वापस calculate_enc_scratch_size(width, height, work_mode, 16,
					  num_vpp_pipes, rc_type);
पूर्ण

अटल u32 h265e_scratch_size(u32 width, u32 height, u32 work_mode,
			      u32 num_vpp_pipes, u32 rc_type)
अणु
	वापस calculate_enc_scratch_size(width, height, work_mode, 32,
					  num_vpp_pipes, rc_type);
पूर्ण

अटल u32 vp8e_scratch_size(u32 width, u32 height, u32 work_mode,
			     u32 num_vpp_pipes, u32 rc_type)
अणु
	वापस calculate_enc_scratch_size(width, height, work_mode, 16,
					  num_vpp_pipes, rc_type);
पूर्ण

अटल u32 hfi_iris2_h264d_comv_size(u32 width, u32 height,
				     u32 yuv_buf_min_count)
अणु
	u32 frame_width_in_mbs = ((width + 15) >> 4);
	u32 frame_height_in_mbs = ((height + 15) >> 4);
	u32 col_mv_aligned_width = (frame_width_in_mbs << 7);
	u32 col_zero_aligned_width = (frame_width_in_mbs << 2);
	u32 col_zero_size = 0, size_colloc = 0, comv_size = 0;

	col_mv_aligned_width = ALIGN(col_mv_aligned_width, 16);
	col_zero_aligned_width = ALIGN(col_zero_aligned_width, 16);
	col_zero_size =
		col_zero_aligned_width * ((frame_height_in_mbs + 1) >> 1);
	col_zero_size = ALIGN(col_zero_size, 64);
	col_zero_size <<= 1;
	col_zero_size = ALIGN(col_zero_size, 512);
	size_colloc = col_mv_aligned_width * ((frame_height_in_mbs + 1) >> 1);
	size_colloc = ALIGN(size_colloc, 64);
	size_colloc <<= 1;
	size_colloc = ALIGN(size_colloc, 512);
	size_colloc += (col_zero_size + SIZE_H264D_BUFTAB_T * 2);
	comv_size = size_colloc * yuv_buf_min_count;
	comv_size += 512;

	वापस comv_size;
पूर्ण

अटल u32 size_h264d_bse_cmd_buf(u32 height)
अणु
	u32 aligned_height = ALIGN(height, 32);

	वापस min_t(u32, (((aligned_height + 15) >> 4) * 3 * 4),
		     H264D_MAX_SLICE) * SIZE_H264D_BSE_CMD_PER_BUF;
पूर्ण

अटल u32 size_h264d_vpp_cmd_buf(u32 height)
अणु
	u32 aligned_height = ALIGN(height, 32);
	u32 size;

	size = min_t(u32, (((aligned_height + 15) >> 4) * 3 * 4),
		     H264D_MAX_SLICE) * SIZE_H264D_VPP_CMD_PER_BUF;
	अगर (size > VPP_CMD_MAX_SIZE)
		size = VPP_CMD_MAX_SIZE;

	वापस size;
पूर्ण

अटल u32 hfi_iris2_h264d_non_comv_size(u32 width, u32 height,
					 u32 num_vpp_pipes)
अणु
	u32 size_bse, size_vpp, size;

	size_bse = size_h264d_bse_cmd_buf(height);
	size_vpp = size_h264d_vpp_cmd_buf(height);
	size =
		ALIGN(size_bse, HFI_DMA_ALIGNMENT) +
		ALIGN(size_vpp, HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_HW_PIC(SIZE_H264D_HW_PIC_T), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H264D_LB_FE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H264D_LB_FE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H264D_LB_FE_LEFT_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_H264D_LB_SE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H264D_LB_SE_LEFT_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_H264D_LB_PE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H264D_LB_VSP_TOP(width, height), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H264D_LB_RECON_DMA_METADATA_WR(width, height),
		      HFI_DMA_ALIGNMENT) * 2 +
		ALIGN(SIZE_H264D_QP(width, height), HFI_DMA_ALIGNMENT);

	वापस ALIGN(size, HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 size_h265d_bse_cmd_buf(u32 width, u32 height)
अणु
	u32 size;

	size = (ALIGN(width, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS) *
	       (ALIGN(height, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS) *
	       NUM_HW_PIC_BUF;
	size = min_t(u32, size, H265D_MAX_SLICE + 1);
	size = 2 * size * SIZE_H265D_BSE_CMD_PER_BUF;

	वापस ALIGN(size, HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 size_h265d_vpp_cmd_buf(u32 width, u32 height)
अणु
	u32 size;

	size = (ALIGN(width, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS) *
	       (ALIGN(height, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS) *
	       NUM_HW_PIC_BUF;
	size = min_t(u32, size, H265D_MAX_SLICE + 1);
	size = ALIGN(size, 4);
	size = 2 * size * SIZE_H265D_VPP_CMD_PER_BUF;
	size = ALIGN(size, HFI_DMA_ALIGNMENT);
	अगर (size > VPP_CMD_MAX_SIZE)
		size = VPP_CMD_MAX_SIZE;

	वापस size;
पूर्ण

अटल u32 hfi_iris2_h265d_comv_size(u32 width, u32 height,
				     u32 yuv_buf_count_min)
अणु
	u32 size;

	size = ALIGN(((((width + 15) >> 4) * ((height + 15) >> 4)) << 8), 512);
	size *= yuv_buf_count_min;
	size += 512;

	वापस size;
पूर्ण

अटल u32 hfi_iris2_h265d_non_comv_size(u32 width, u32 height,
					 u32 num_vpp_pipes)
अणु
	u32 size_bse, size_vpp, size;

	size_bse = size_h265d_bse_cmd_buf(width, height);
	size_vpp = size_h265d_vpp_cmd_buf(width, height);
	size =
		ALIGN(size_bse, HFI_DMA_ALIGNMENT) +
		ALIGN(size_vpp, HFI_DMA_ALIGNMENT) +
		ALIGN(NUM_HW_PIC_BUF * 20 * 22 * 4, HFI_DMA_ALIGNMENT) +
		ALIGN(2 * माप(u16) *
		(ALIGN(width, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS) *
		(ALIGN(height, LCU_MAX_SIZE_PELS) / LCU_MIN_SIZE_PELS),
		       HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_HW_PIC(SIZE_H265D_HW_PIC_T), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H265D_LB_FE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H265D_LB_FE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H265D_LB_FE_LEFT_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(size_h265d_lb_se_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_H265D_LB_SE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H265D_LB_PE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H265D_LB_VSP_TOP(width, height), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_H265D_LB_VSP_LEFT(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_H265D_LB_RECON_DMA_METADATA_WR(width, height),
		      HFI_DMA_ALIGNMENT)
			* 4 +
		ALIGN(SIZE_H265D_QP(width, height), HFI_DMA_ALIGNMENT);

	वापस ALIGN(size, HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 hfi_iris2_vp8d_comv_size(u32 width, u32 height,
				    u32 yuv_min_buf_count)
अणु
	वापस (((width + 15) >> 4) * ((height + 15) >> 4) * 8 * 2);
पूर्ण

अटल u32 h264d_scratch1_size(u32 width, u32 height, u32 min_buf_count,
			       bool split_mode_enabled, u32 num_vpp_pipes)
अणु
	u32 co_mv_size, nonco_mv_size, vpss_lb_size = 0;

	co_mv_size = hfi_iris2_h264d_comv_size(width, height, min_buf_count);
	nonco_mv_size = hfi_iris2_h264d_non_comv_size(width, height,
						      num_vpp_pipes);
	अगर (split_mode_enabled)
		vpss_lb_size = size_vpss_lb(width, height, num_vpp_pipes);

	वापस co_mv_size + nonco_mv_size + vpss_lb_size;
पूर्ण

अटल u32 h265d_scratch1_size(u32 width, u32 height, u32 min_buf_count,
			       bool split_mode_enabled, u32 num_vpp_pipes)
अणु
	u32 co_mv_size, nonco_mv_size, vpss_lb_size = 0;

	co_mv_size = hfi_iris2_h265d_comv_size(width, height, min_buf_count);
	nonco_mv_size = hfi_iris2_h265d_non_comv_size(width, height,
						      num_vpp_pipes);
	अगर (split_mode_enabled)
		vpss_lb_size = size_vpss_lb(width, height, num_vpp_pipes);

	वापस co_mv_size + nonco_mv_size + vpss_lb_size +
		HDR10_HIST_EXTRADATA_SIZE;
पूर्ण

अटल u32 vp8d_scratch1_size(u32 width, u32 height, u32 min_buf_count,
			      bool split_mode_enabled, u32 num_vpp_pipes)
अणु
	u32 vpss_lb_size = 0, size;

	size = hfi_iris2_vp8d_comv_size(width, height, 0);
	size += ALIGN(size_vpxd_lb_fe_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(size_vpxd_lb_se_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_VP8D_LB_VSP_TOP(width, height), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VPXD_LB_FE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		2 * ALIGN(SIZE_VPXD_LB_RECON_DMA_METADATA_WR(width, height),
			  HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VPXD_LB_SE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VP8D_LB_PE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VP8D_LB_FE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT);
	अगर (split_mode_enabled)
		vpss_lb_size = size_vpss_lb(width, height, num_vpp_pipes);

	size += vpss_lb_size;

	वापस size;
पूर्ण

अटल u32 vp9d_scratch1_size(u32 width, u32 height, u32 min_buf_count,
			      bool split_mode_enabled, u32 num_vpp_pipes)
अणु
	u32 vpss_lb_size = 0;
	u32 size;

	size =
		ALIGN(size_vpxd_lb_fe_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(size_vpxd_lb_se_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_VP9D_LB_VSP_TOP(width, height), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VPXD_LB_FE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		2 * ALIGN(SIZE_VPXD_LB_RECON_DMA_METADATA_WR(width, height),
			  HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VPXD_LB_SE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VP9D_LB_PE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VP9D_LB_FE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT);

	अगर (split_mode_enabled)
		vpss_lb_size = size_vpss_lb(width, height, num_vpp_pipes);

	size += vpss_lb_size + HDR10_HIST_EXTRADATA_SIZE;

	वापस size;
पूर्ण

अटल u32 mpeg2d_scratch1_size(u32 width, u32 height, u32 min_buf_count,
				bool split_mode_enabled, u32 num_vpp_pipes)
अणु
	u32 vpss_lb_size = 0;
	u32 size;

	size =
		ALIGN(size_vpxd_lb_fe_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(size_vpxd_lb_se_left_ctrl(width, height),
		      HFI_DMA_ALIGNMENT) * num_vpp_pipes +
		ALIGN(SIZE_VP8D_LB_VSP_TOP(width, height), HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VPXD_LB_FE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		2 * ALIGN(SIZE_VPXD_LB_RECON_DMA_METADATA_WR(width, height),
			  HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VPXD_LB_SE_TOP_CTRL(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VP8D_LB_PE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT) +
		ALIGN(SIZE_VP8D_LB_FE_TOP_DATA(width, height),
		      HFI_DMA_ALIGNMENT);

	अगर (split_mode_enabled)
		vpss_lb_size = size_vpss_lb(width, height, num_vpp_pipes);

	size += vpss_lb_size;

	वापस size;
पूर्ण

अटल u32
calculate_enc_scratch1_size(u32 width, u32 height, u32 lcu_size, u32 num_ref,
			    bool ten_bit, u32 num_vpp_pipes, bool is_h265)
अणु
	u32 line_buf_ctrl_size, line_buf_data_size, leftline_buf_ctrl_size;
	u32 line_buf_sde_size, sps_pps_slice_hdr, topline_buf_ctrl_size_FE;
	u32 leftline_buf_ctrl_size_FE, line_buf_recon_pix_size;
	u32 leftline_buf_recon_pix_size, lambda_lut_size, override_buffer_size;
	u32 col_mv_buf_size, vpp_reg_buffer_size, ir_buffer_size;
	u32 vpss_line_buf, leftline_buf_meta_recony, h265e_colrcbuf_size;
	u32 h265e_framerc_bufsize, h265e_lcubitcnt_bufsize;
	u32 h265e_lcubiपंचांगap_bufsize, se_stats_bufsize;
	u32 bse_reg_buffer_size, bse_slice_cmd_buffer_size, slice_info_bufsize;
	u32 line_buf_ctrl_size_buffid2, slice_cmd_buffer_size;
	u32 width_lcu_num, height_lcu_num, width_coded, height_coded;
	u32 frame_num_lcu, linebuf_meta_recon_uv, topline_bufsize_fe_1stg_sao;
	u32 size, bit_depth, num_lcu_mb;
	u32 vpss_line_buffer_size_1;

	width_lcu_num = (width + lcu_size - 1) / lcu_size;
	height_lcu_num = (height + lcu_size - 1) / lcu_size;
	frame_num_lcu = width_lcu_num * height_lcu_num;
	width_coded = width_lcu_num * lcu_size;
	height_coded = height_lcu_num * lcu_size;
	num_lcu_mb = (height_coded / lcu_size) *
		     ((width_coded + lcu_size * 8) / lcu_size);
	slice_info_bufsize = 256 + (frame_num_lcu << 4);
	slice_info_bufsize = ALIGN(slice_info_bufsize, HFI_DMA_ALIGNMENT);
	line_buf_ctrl_size = ALIGN(width_coded, HFI_DMA_ALIGNMENT);
	line_buf_ctrl_size_buffid2 = ALIGN(width_coded, HFI_DMA_ALIGNMENT);

	bit_depth = ten_bit ? 10 : 8;
	line_buf_data_size =
		(((((bit_depth * width_coded + 1024) +
		(HFI_DMA_ALIGNMENT - 1)) & (~(HFI_DMA_ALIGNMENT - 1))) * 1) +
		(((((bit_depth * width_coded + 1024) >> 1) +
		(HFI_DMA_ALIGNMENT - 1)) & (~(HFI_DMA_ALIGNMENT - 1))) * 2));

	leftline_buf_ctrl_size = is_h265 ?
		((height_coded + 32) / 32 * 4 * 16) :
		((height_coded + 15) / 16 * 5 * 16);

	अगर (num_vpp_pipes > 1) अणु
		leftline_buf_ctrl_size += 512;
		leftline_buf_ctrl_size =
			ALIGN(leftline_buf_ctrl_size, 512) * num_vpp_pipes;
	पूर्ण

	leftline_buf_ctrl_size =
		ALIGN(leftline_buf_ctrl_size, HFI_DMA_ALIGNMENT);
	leftline_buf_recon_pix_size = (((ten_bit + 1) * 2 *
		(height_coded) + HFI_DMA_ALIGNMENT) +
		(HFI_DMA_ALIGNMENT << (num_vpp_pipes - 1)) - 1) &
		(~((HFI_DMA_ALIGNMENT << (num_vpp_pipes - 1)) - 1)) * 1;

	topline_buf_ctrl_size_FE = is_h265 ? (64 * (width_coded >> 5)) :
		(HFI_DMA_ALIGNMENT + 16 * (width_coded >> 4));
	topline_buf_ctrl_size_FE =
		ALIGN(topline_buf_ctrl_size_FE, HFI_DMA_ALIGNMENT);
	leftline_buf_ctrl_size_FE =
		(((HFI_DMA_ALIGNMENT + 64 * (height_coded >> 4)) +
		(HFI_DMA_ALIGNMENT << (num_vpp_pipes - 1)) - 1) &
		(~((HFI_DMA_ALIGNMENT << (num_vpp_pipes - 1)) - 1)) * 1) *
		num_vpp_pipes;
	leftline_buf_meta_recony = (HFI_DMA_ALIGNMENT + 64 *
		((height_coded) / (8 * (ten_bit ? 4 : 8))));
	leftline_buf_meta_recony =
		ALIGN(leftline_buf_meta_recony, HFI_DMA_ALIGNMENT);
	leftline_buf_meta_recony = leftline_buf_meta_recony * num_vpp_pipes;
	linebuf_meta_recon_uv = (HFI_DMA_ALIGNMENT + 64 *
		((height_coded) / (4 * (ten_bit ? 4 : 8))));
	linebuf_meta_recon_uv = ALIGN(linebuf_meta_recon_uv, HFI_DMA_ALIGNMENT);
	linebuf_meta_recon_uv = linebuf_meta_recon_uv * num_vpp_pipes;
	line_buf_recon_pix_size = ((ten_bit ? 3 : 2) * width_coded);
	line_buf_recon_pix_size =
		ALIGN(line_buf_recon_pix_size, HFI_DMA_ALIGNMENT);
	slice_cmd_buffer_size = ALIGN(20480, HFI_DMA_ALIGNMENT);
	sps_pps_slice_hdr = 2048 + 4096;
	col_mv_buf_size = is_h265 ? (16 * ((frame_num_lcu << 2) + 32)) :
		(3 * 16 * (width_lcu_num * height_lcu_num + 32));
	col_mv_buf_size =
		ALIGN(col_mv_buf_size, HFI_DMA_ALIGNMENT) * (num_ref + 1);
	h265e_colrcbuf_size =
		(((width_lcu_num + 7) >> 3) * 16 * 2 * height_lcu_num);
	अगर (num_vpp_pipes > 1)
		h265e_colrcbuf_size =
			ALIGN(h265e_colrcbuf_size, HFI_DMA_ALIGNMENT) *
			num_vpp_pipes;

	h265e_colrcbuf_size = ALIGN(h265e_colrcbuf_size, HFI_DMA_ALIGNMENT) *
				HFI_MAX_COL_FRAME;
	h265e_framerc_bufsize = (is_h265) ? (256 + 16 *
		(14 + (((height_coded >> 5) + 7) >> 3))) :
		(256 + 16 * (14 + (((height_coded >> 4) + 7) >> 3)));
	h265e_framerc_bufsize *= 6;   /* multiply by max numtilescol */
	अगर (num_vpp_pipes > 1)
		h265e_framerc_bufsize =
			ALIGN(h265e_framerc_bufsize, HFI_DMA_ALIGNMENT) *
			num_vpp_pipes;

	h265e_framerc_bufsize = ALIGN(h265e_framerc_bufsize, 512) *
				HFI_MAX_COL_FRAME;
	h265e_lcubitcnt_bufsize = 256 + 4 * frame_num_lcu;
	h265e_lcubitcnt_bufsize =
		ALIGN(h265e_lcubitcnt_bufsize, HFI_DMA_ALIGNMENT);
	h265e_lcubiपंचांगap_bufsize = 256 + (frame_num_lcu >> 3);
	h265e_lcubiपंचांगap_bufsize =
		ALIGN(h265e_lcubiपंचांगap_bufsize, HFI_DMA_ALIGNMENT);
	line_buf_sde_size = 256 + 16 * (width_coded >> 4);
	line_buf_sde_size = ALIGN(line_buf_sde_size, HFI_DMA_ALIGNMENT);
	अगर ((width_coded * height_coded) > (4096 * 2160))
		se_stats_bufsize = 0;
	अन्यथा अगर ((width_coded * height_coded) > (1920 * 1088))
		se_stats_bufsize = (40 * 4 * frame_num_lcu + 256 + 256);
	अन्यथा
		se_stats_bufsize = (1024 * frame_num_lcu + 256 + 256);

	se_stats_bufsize = ALIGN(se_stats_bufsize, HFI_DMA_ALIGNMENT) * 2;
	bse_slice_cmd_buffer_size = (((8192 << 2) + 7) & (~7)) * 6;
	bse_reg_buffer_size = (((512 << 3) + 7) & (~7)) * 4;
	vpp_reg_buffer_size =
		(((HFI_VENUS_VPPSG_MAX_REGISTERS << 3) + 31) & (~31)) * 10;
	lambda_lut_size = 256 * 11;
	override_buffer_size = 16 * ((num_lcu_mb + 7) >> 3);
	override_buffer_size =
		ALIGN(override_buffer_size, HFI_DMA_ALIGNMENT) * 2;
	ir_buffer_size = (((frame_num_lcu << 1) + 7) & (~7)) * 3;
	vpss_line_buffer_size_1 = (((8192 >> 2) << 5) * num_vpp_pipes) + 64;
	vpss_line_buf =
		(((((max(width_coded, height_coded) + 3) >> 2) << 5) + 256) *
		16) + vpss_line_buffer_size_1;
	topline_bufsize_fe_1stg_sao = 16 * (width_coded >> 5);
	topline_bufsize_fe_1stg_sao =
		ALIGN(topline_bufsize_fe_1stg_sao, HFI_DMA_ALIGNMENT);

	size =
		line_buf_ctrl_size + line_buf_data_size +
		line_buf_ctrl_size_buffid2 + leftline_buf_ctrl_size +
		vpss_line_buf + col_mv_buf_size + topline_buf_ctrl_size_FE +
		leftline_buf_ctrl_size_FE + line_buf_recon_pix_size +
		leftline_buf_recon_pix_size +
		leftline_buf_meta_recony + linebuf_meta_recon_uv +
		h265e_colrcbuf_size + h265e_framerc_bufsize +
		h265e_lcubitcnt_bufsize + h265e_lcubiपंचांगap_bufsize +
		line_buf_sde_size +
		topline_bufsize_fe_1stg_sao + override_buffer_size +
		bse_reg_buffer_size + vpp_reg_buffer_size + sps_pps_slice_hdr +
		slice_cmd_buffer_size + bse_slice_cmd_buffer_size +
		ir_buffer_size + slice_info_bufsize + lambda_lut_size +
		se_stats_bufsize + 1024;

	वापस size;
पूर्ण

अटल u32 h264e_scratch1_size(u32 width, u32 height, u32 num_ref, bool ten_bit,
			       u32 num_vpp_pipes)
अणु
	वापस calculate_enc_scratch1_size(width, height, 16, num_ref, ten_bit,
					   num_vpp_pipes, false);
पूर्ण

अटल u32 h265e_scratch1_size(u32 width, u32 height, u32 num_ref, bool ten_bit,
			       u32 num_vpp_pipes)
अणु
	वापस calculate_enc_scratch1_size(width, height, 32, num_ref, ten_bit,
					   num_vpp_pipes, true);
पूर्ण

अटल u32 vp8e_scratch1_size(u32 width, u32 height, u32 num_ref, bool ten_bit,
			      u32 num_vpp_pipes)
अणु
	वापस calculate_enc_scratch1_size(width, height, 16, num_ref, ten_bit,
					   1, false);
पूर्ण

अटल u32 ubwc_metadata_plane_stride(u32 width, u32 metadata_stride_multi,
				      u32 tile_width_pels)
अणु
	वापस ALIGN(((width + (tile_width_pels - 1)) / tile_width_pels),
			metadata_stride_multi);
पूर्ण

अटल u32 ubwc_metadata_plane_bufheight(u32 height, u32 metadata_height_multi,
					 u32 tile_height_pels)
अणु
	वापस ALIGN(((height + (tile_height_pels - 1)) / tile_height_pels),
			metadata_height_multi);
पूर्ण

अटल u32 ubwc_metadata_plane_buffer_size(u32 metadata_stride,
					   u32 metadata_buf_height)
अणु
	वापस ALIGN(metadata_stride * metadata_buf_height, SZ_4K);
पूर्ण

अटल u32 enc_scratch2_size(u32 width, u32 height, u32 num_ref, bool ten_bit)
अणु
	u32 aligned_width, aligned_height, chroma_height, ref_buf_height;
	u32 luma_size, chroma_size;
	u32 metadata_stride, meta_buf_height, meta_size_y, meta_size_c;
	u32 ref_luma_stride_bytes, ref_chroma_height_bytes;
	u32 ref_buf_size, ref_stride;
	u32 size;

	अगर (!ten_bit) अणु
		aligned_height = ALIGN(height, HFI_VENUS_HEIGHT_ALIGNMENT);
		chroma_height = height >> 1;
		chroma_height = ALIGN(chroma_height,
				      HFI_VENUS_HEIGHT_ALIGNMENT);
		aligned_width = ALIGN(width, HFI_VENUS_WIDTH_ALIGNMENT);
		metadata_stride =
			ubwc_metadata_plane_stride(width, 64,
						   NV12_UBWC_Y_TILE_WIDTH);
		meta_buf_height =
			ubwc_metadata_plane_bufheight(height, 16,
						      NV12_UBWC_Y_TILE_HEIGHT);
		meta_size_y = ubwc_metadata_plane_buffer_size(metadata_stride,
							      meta_buf_height);
		meta_size_c = ubwc_metadata_plane_buffer_size(metadata_stride,
							      meta_buf_height);
		size = (aligned_height + chroma_height) * aligned_width +
			meta_size_y + meta_size_c;
		size = (size * (num_ref + 3)) + 4096;
	पूर्ण अन्यथा अणु
		ref_buf_height = (height + (HFI_VENUS_HEIGHT_ALIGNMENT - 1))
					& (~(HFI_VENUS_HEIGHT_ALIGNMENT - 1));
		ref_luma_stride_bytes =
			((width + SYSTEM_LAL_TILE10 - 1) / SYSTEM_LAL_TILE10) *
			SYSTEM_LAL_TILE10;
		ref_stride = 4 * (ref_luma_stride_bytes / 3);
		ref_stride = (ref_stride + (128 - 1)) & (~(128 - 1));
		luma_size = ref_buf_height * ref_stride;
		ref_chroma_height_bytes = (((height + 1) >> 1) +
			(32 - 1)) & (~(32 - 1));
		chroma_size = ref_stride * ref_chroma_height_bytes;
		luma_size = (luma_size + (SZ_4K - 1)) & (~(SZ_4K - 1));
		chroma_size = (chroma_size + (SZ_4K - 1)) & (~(SZ_4K - 1));
		ref_buf_size = luma_size + chroma_size;
		metadata_stride =
			ubwc_metadata_plane_stride(width,
						   METADATA_STRIDE_MULTIPLE,
						   TP10_UBWC_Y_TILE_WIDTH);
		meta_buf_height =
			ubwc_metadata_plane_bufheight(height,
						      METADATA_HEIGHT_MULTIPLE,
						      TP10_UBWC_Y_TILE_HEIGHT);
		meta_size_y = ubwc_metadata_plane_buffer_size(metadata_stride,
							      meta_buf_height);
		meta_size_c = ubwc_metadata_plane_buffer_size(metadata_stride,
							      meta_buf_height);
		size = ref_buf_size + meta_size_y + meta_size_c;
		size = (size * (num_ref + 3)) + 4096;
	पूर्ण

	वापस size;
पूर्ण

अटल u32 enc_persist_size(व्योम)
अणु
	वापस HFI_IRIS2_ENC_PERSIST_SIZE;
पूर्ण

अटल u32 h264d_persist1_size(व्योम)
अणु
	वापस ALIGN((SIZE_SLIST_BUF_H264 * NUM_SLIST_BUF_H264
		     + NUM_HW_PIC_BUF * SIZE_SEI_USERDATA), HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 h265d_persist1_size(व्योम)
अणु
	वापस ALIGN((SIZE_SLIST_BUF_H265 * NUM_SLIST_BUF_H265 + H265_NUM_TILE
			* माप(u32)), HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 vp8d_persist1_size(व्योम)
अणु
	वापस ALIGN(VP8_NUM_PROBABILITY_TABLE_BUF * VP8_PROB_TABLE_SIZE,
			HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 vp9d_persist1_size(व्योम)
अणु
	वापस
		ALIGN(VP9_NUM_PROBABILITY_TABLE_BUF * VP9_PROB_TABLE_SIZE,
		      HFI_DMA_ALIGNMENT) +
		ALIGN(HFI_IRIS2_VP9D_COMV_SIZE, HFI_DMA_ALIGNMENT) +
		ALIGN(MAX_SUPERFRAME_HEADER_LEN, HFI_DMA_ALIGNMENT) +
		ALIGN(VP9_UDC_HEADER_BUF_SIZE, HFI_DMA_ALIGNMENT) +
		ALIGN(VP9_NUM_FRAME_INFO_BUF * CCE_TILE_OFFSET_SIZE,
		      HFI_DMA_ALIGNMENT);
पूर्ण

अटल u32 mpeg2d_persist1_size(व्योम)
अणु
	वापस QMATRIX_SIZE + MP2D_QPDUMP_SIZE;
पूर्ण

काष्ठा dec_bufsize_ops अणु
	u32 (*scratch)(u32 width, u32 height, bool is_पूर्णांकerlaced);
	u32 (*scratch1)(u32 width, u32 height, u32 min_buf_count,
			bool split_mode_enabled, u32 num_vpp_pipes);
	u32 (*persist1)(व्योम);
पूर्ण;

काष्ठा enc_bufsize_ops अणु
	u32 (*scratch)(u32 width, u32 height, u32 work_mode, u32 num_vpp_pipes,
		       u32 rc_type);
	u32 (*scratch1)(u32 width, u32 height, u32 num_ref, bool ten_bit,
			u32 num_vpp_pipes);
	u32 (*scratch2)(u32 width, u32 height, u32 num_ref, bool ten_bit);
	u32 (*persist)(व्योम);
पूर्ण;

अटल काष्ठा dec_bufsize_ops dec_h264_ops = अणु
	.scratch = h264d_scratch_size,
	.scratch1 = h264d_scratch1_size,
	.persist1 = h264d_persist1_size,
पूर्ण;

अटल काष्ठा dec_bufsize_ops dec_h265_ops = अणु
	.scratch = h265d_scratch_size,
	.scratch1 = h265d_scratch1_size,
	.persist1 = h265d_persist1_size,
पूर्ण;

अटल काष्ठा dec_bufsize_ops dec_vp8_ops = अणु
	.scratch = vpxd_scratch_size,
	.scratch1 = vp8d_scratch1_size,
	.persist1 = vp8d_persist1_size,
पूर्ण;

अटल काष्ठा dec_bufsize_ops dec_vp9_ops = अणु
	.scratch = vpxd_scratch_size,
	.scratch1 = vp9d_scratch1_size,
	.persist1 = vp9d_persist1_size,
पूर्ण;

अटल काष्ठा dec_bufsize_ops dec_mpeg2_ops = अणु
	.scratch = mpeg2d_scratch_size,
	.scratch1 = mpeg2d_scratch1_size,
	.persist1 = mpeg2d_persist1_size,
पूर्ण;

अटल काष्ठा enc_bufsize_ops enc_h264_ops = अणु
	.scratch = h264e_scratch_size,
	.scratch1 = h264e_scratch1_size,
	.scratch2 = enc_scratch2_size,
	.persist = enc_persist_size,
पूर्ण;

अटल काष्ठा enc_bufsize_ops enc_h265_ops = अणु
	.scratch = h265e_scratch_size,
	.scratch1 = h265e_scratch1_size,
	.scratch2 = enc_scratch2_size,
	.persist = enc_persist_size,
पूर्ण;

अटल काष्ठा enc_bufsize_ops enc_vp8_ops = अणु
	.scratch = vp8e_scratch_size,
	.scratch1 = vp8e_scratch1_size,
	.scratch2 = enc_scratch2_size,
	.persist = enc_persist_size,
पूर्ण;

अटल u32
calculate_dec_input_frame_size(u32 width, u32 height, u32 codec,
			       u32 max_mbs_per_frame, u32 buffer_size_limit)
अणु
	u32 frame_size, num_mbs;
	u32 भाग_factor = 1;
	u32 base_res_mbs = NUM_MBS_4K;

	/*
	 * Decoder input size calculation:
	 * If clip is 8k buffer size is calculated क्रम 8k : 8k mbs/4
	 * For 8k हालs we expect width/height to be set always.
	 * In all other हालs size is calculated क्रम 4k:
	 * 4k mbs क्रम VP8/VP9 and 4k/2 क्रम reमुख्यing codecs
	 */
	num_mbs = (ALIGN(height, 16) * ALIGN(width, 16)) / 256;
	अगर (num_mbs > NUM_MBS_4K) अणु
		भाग_factor = 4;
		base_res_mbs = max_mbs_per_frame;
	पूर्ण अन्यथा अणु
		base_res_mbs = NUM_MBS_4K;
		अगर (codec == V4L2_PIX_FMT_VP9)
			भाग_factor = 1;
		अन्यथा
			भाग_factor = 2;
	पूर्ण

	frame_size = base_res_mbs * MB_SIZE_IN_PIXEL * 3 / 2 / भाग_factor;

	/* multiply by 10/8 (1.25) to get size क्रम 10 bit हाल */
	अगर (codec == V4L2_PIX_FMT_VP9 || codec == V4L2_PIX_FMT_HEVC)
		frame_size = frame_size + (frame_size >> 2);

	अगर (buffer_size_limit && buffer_size_limit < frame_size)
		frame_size = buffer_size_limit;

	वापस ALIGN(frame_size, SZ_4K);
पूर्ण

अटल पूर्णांक output_buffer_count(u32 session_type, u32 codec)
अणु
	u32 output_min_count;

	अगर (session_type == VIDC_SESSION_TYPE_DEC) अणु
		चयन (codec) अणु
		हाल V4L2_PIX_FMT_MPEG2:
		हाल V4L2_PIX_FMT_VP8:
			output_min_count = 6;
			अवरोध;
		हाल V4L2_PIX_FMT_VP9:
			output_min_count = 9;
			अवरोध;
		हाल V4L2_PIX_FMT_H264:
		हाल V4L2_PIX_FMT_HEVC:
		शेष:
			output_min_count = 18;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		output_min_count = MIN_ENC_OUTPUT_BUFFERS;
	पूर्ण

	वापस output_min_count;
पूर्ण

अटल पूर्णांक bufreq_dec(काष्ठा hfi_plat_buffers_params *params, u32 buftype,
		      काष्ठा hfi_buffer_requirements *bufreq)
अणु
	क्रमागत hfi_version version = params->version;
	u32 codec = params->codec;
	u32 width = params->width, height = params->height, out_min_count;
	काष्ठा dec_bufsize_ops *dec_ops;
	bool is_secondary_output = params->dec.is_secondary_output;
	bool is_पूर्णांकerlaced = params->dec.is_पूर्णांकerlaced;
	u32 max_mbs_per_frame = params->dec.max_mbs_per_frame;
	u32 buffer_size_limit = params->dec.buffer_size_limit;
	u32 num_vpp_pipes = params->num_vpp_pipes;

	चयन (codec) अणु
	हाल V4L2_PIX_FMT_H264:
		dec_ops = &dec_h264_ops;
		अवरोध;
	हाल V4L2_PIX_FMT_HEVC:
		dec_ops = &dec_h265_ops;
		अवरोध;
	हाल V4L2_PIX_FMT_VP8:
		dec_ops = &dec_vp8_ops;
		अवरोध;
	हाल V4L2_PIX_FMT_VP9:
		dec_ops = &dec_vp9_ops;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG2:
		dec_ops = &dec_mpeg2_ops;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	out_min_count = output_buffer_count(VIDC_SESSION_TYPE_DEC, codec);

	bufreq->type = buftype;
	bufreq->region_size = 0;
	bufreq->count_min = 1;
	bufreq->count_actual = 1;
	bufreq->hold_count = 1;
	bufreq->contiguous = 1;
	bufreq->alignment = 256;

	अगर (buftype == HFI_BUFFER_INPUT) अणु
		bufreq->count_min = MIN_INPUT_BUFFERS;
		bufreq->size =
			calculate_dec_input_frame_size(width, height, codec,
						       max_mbs_per_frame,
						       buffer_size_limit);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_OUTPUT ||
		   buftype == HFI_BUFFER_OUTPUT2) अणु
		bufreq->count_min = out_min_count;
		bufreq->size =
			venus_helper_get_framesz_raw(params->hfi_color_fmt,
						     width, height);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_SCRATCH(version)) अणु
		bufreq->size = dec_ops->scratch(width, height, is_पूर्णांकerlaced);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_SCRATCH_1(version)) अणु
		bufreq->size = dec_ops->scratch1(width, height, out_min_count,
						 is_secondary_output,
						 num_vpp_pipes);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_PERSIST_1) अणु
		bufreq->size = dec_ops->persist1();
	पूर्ण अन्यथा अणु
		bufreq->size = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bufreq_enc(काष्ठा hfi_plat_buffers_params *params, u32 buftype,
		      काष्ठा hfi_buffer_requirements *bufreq)
अणु
	क्रमागत hfi_version version = params->version;
	काष्ठा enc_bufsize_ops *enc_ops;
	u32 width = params->width;
	u32 height = params->height;
	bool is_tenbit = params->enc.is_tenbit;
	u32 num_bframes = params->enc.num_b_frames;
	u32 codec = params->codec;
	u32 work_mode = params->enc.work_mode;
	u32 rc_type = params->enc.rc_type;
	u32 num_vpp_pipes = params->num_vpp_pipes;
	u32 num_ref;

	चयन (codec) अणु
	हाल V4L2_PIX_FMT_H264:
		enc_ops = &enc_h264_ops;
		अवरोध;
	हाल V4L2_PIX_FMT_HEVC:
		enc_ops = &enc_h265_ops;
		अवरोध;
	हाल V4L2_PIX_FMT_VP8:
		enc_ops = &enc_vp8_ops;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	num_ref = num_bframes > 0 ? num_bframes + 1 : 1;

	bufreq->type = buftype;
	bufreq->region_size = 0;
	bufreq->count_min = 1;
	bufreq->count_actual = 1;
	bufreq->hold_count = 1;
	bufreq->contiguous = 1;
	bufreq->alignment = 256;

	अगर (buftype == HFI_BUFFER_INPUT) अणु
		bufreq->count_min = MIN_INPUT_BUFFERS;
		bufreq->size =
			venus_helper_get_framesz_raw(params->hfi_color_fmt,
						     width, height);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_OUTPUT ||
		   buftype == HFI_BUFFER_OUTPUT2) अणु
		bufreq->count_min =
			output_buffer_count(VIDC_SESSION_TYPE_ENC, codec);
		bufreq->size = calculate_enc_output_frame_size(width, height,
							       rc_type);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_SCRATCH(version)) अणु
		bufreq->size = enc_ops->scratch(width, height, work_mode,
						num_vpp_pipes, rc_type);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_SCRATCH_1(version)) अणु
		bufreq->size = enc_ops->scratch1(width, height, num_ref,
						 is_tenbit, num_vpp_pipes);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_SCRATCH_2(version)) अणु
		bufreq->size = enc_ops->scratch2(width, height, num_ref,
						 is_tenbit);
	पूर्ण अन्यथा अगर (buftype == HFI_BUFFER_INTERNAL_PERSIST) अणु
		bufreq->size = enc_ops->persist();
	पूर्ण अन्यथा अणु
		bufreq->size = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hfi_plat_bufreq_v6(काष्ठा hfi_plat_buffers_params *params, u32 session_type,
		       u32 buftype, काष्ठा hfi_buffer_requirements *bufreq)
अणु
	अगर (session_type == VIDC_SESSION_TYPE_DEC)
		वापस bufreq_dec(params, buftype, bufreq);
	अन्यथा
		वापस bufreq_enc(params, buftype, bufreq);
पूर्ण
