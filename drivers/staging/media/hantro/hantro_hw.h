<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Hantro VPU codec driver
 *
 * Copyright 2018 Google LLC.
 *	Tomasz Figa <tfiga@chromium.org>
 */

#अगर_अघोषित HANTRO_HW_H_
#घोषणा HANTRO_HW_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/v4l2-controls.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-core.h>

#घोषणा DEC_8190_ALIGN_MASK	0x07U

#घोषणा MB_DIM			16
#घोषणा MB_WIDTH(w)		DIV_ROUND_UP(w, MB_DIM)
#घोषणा MB_HEIGHT(h)		DIV_ROUND_UP(h, MB_DIM)

काष्ठा hantro_dev;
काष्ठा hantro_ctx;
काष्ठा hantro_buf;
काष्ठा hantro_variant;

/**
 * काष्ठा hantro_aux_buf - auxiliary DMA buffer क्रम hardware data
 *
 * @cpu:	CPU poपूर्णांकer to the buffer.
 * @dma:	DMA address of the buffer.
 * @size:	Size of the buffer.
 * @attrs:	Attributes of the DMA mapping.
 */
काष्ठा hantro_aux_buf अणु
	व्योम *cpu;
	dma_addr_t dma;
	माप_प्रकार size;
	अचिन्हित दीर्घ attrs;
पूर्ण;

/**
 * काष्ठा hantro_jpeg_enc_hw_ctx
 *
 * @bounce_buffer:	Bounce buffer
 */
काष्ठा hantro_jpeg_enc_hw_ctx अणु
	काष्ठा hantro_aux_buf bounce_buffer;
पूर्ण;

/* Max. number of entries in the DPB (HW limitation). */
#घोषणा HANTRO_H264_DPB_SIZE		16

/**
 * काष्ठा hantro_h264_dec_ctrls
 *
 * @decode:	Decode params
 * @scaling:	Scaling info
 * @sps:	SPS info
 * @pps:	PPS info
 */
काष्ठा hantro_h264_dec_ctrls अणु
	स्थिर काष्ठा v4l2_ctrl_h264_decode_params *decode;
	स्थिर काष्ठा v4l2_ctrl_h264_scaling_matrix *scaling;
	स्थिर काष्ठा v4l2_ctrl_h264_sps *sps;
	स्थिर काष्ठा v4l2_ctrl_h264_pps *pps;
पूर्ण;

/**
 * काष्ठा hantro_h264_dec_reflists
 *
 * @p:		P reflist
 * @b0:		B0 reflist
 * @b1:		B1 reflist
 */
काष्ठा hantro_h264_dec_reflists अणु
	u8 p[HANTRO_H264_DPB_SIZE];
	u8 b0[HANTRO_H264_DPB_SIZE];
	u8 b1[HANTRO_H264_DPB_SIZE];
पूर्ण;

/**
 * काष्ठा hantro_h264_dec_hw_ctx
 *
 * @priv:	Private auxiliary buffer क्रम hardware.
 * @dpb:	DPB
 * @reflists:	P/B0/B1 reflists
 * @ctrls:	V4L2 controls attached to a run
 */
काष्ठा hantro_h264_dec_hw_ctx अणु
	काष्ठा hantro_aux_buf priv;
	काष्ठा v4l2_h264_dpb_entry dpb[HANTRO_H264_DPB_SIZE];
	काष्ठा hantro_h264_dec_reflists reflists;
	काष्ठा hantro_h264_dec_ctrls ctrls;
पूर्ण;

/**
 * काष्ठा hantro_mpeg2_dec_hw_ctx
 *
 * @qtable:		Quantization table
 */
काष्ठा hantro_mpeg2_dec_hw_ctx अणु
	काष्ठा hantro_aux_buf qtable;
पूर्ण;

/**
 * काष्ठा hantro_vp8_dec_hw_ctx
 *
 * @segment_map:	Segment map buffer.
 * @prob_tbl:		Probability table buffer.
 */
काष्ठा hantro_vp8_dec_hw_ctx अणु
	काष्ठा hantro_aux_buf segment_map;
	काष्ठा hantro_aux_buf prob_tbl;
पूर्ण;

/**
 * काष्ठा hantro_postproc_ctx
 *
 * @dec_q:		References buffers, in decoder क्रमmat.
 */
काष्ठा hantro_postproc_ctx अणु
	काष्ठा hantro_aux_buf dec_q[VB2_MAX_FRAME];
पूर्ण;

/**
 * काष्ठा hantro_codec_ops - codec mode specअगरic operations
 *
 * @init:	If needed, can be used क्रम initialization.
 *		Optional and called from process context.
 * @निकास:	If needed, can be used to unकरो the .init phase.
 *		Optional and called from process context.
 * @run:	Start single अणुen,de)coding job. Called from atomic context
 *		to indicate that a pair of buffers is पढ़ोy and the hardware
 *		should be programmed and started.
 * @करोne:	Read back processing results and additional data from hardware.
 * @reset:	Reset the hardware in हाल of a समयout.
 */
काष्ठा hantro_codec_ops अणु
	पूर्णांक (*init)(काष्ठा hantro_ctx *ctx);
	व्योम (*निकास)(काष्ठा hantro_ctx *ctx);
	व्योम (*run)(काष्ठा hantro_ctx *ctx);
	व्योम (*करोne)(काष्ठा hantro_ctx *ctx);
	व्योम (*reset)(काष्ठा hantro_ctx *ctx);
पूर्ण;

/**
 * क्रमागत hantro_enc_fmt - source क्रमmat ID क्रम hardware रेजिस्टरs.
 *
 * @RK3288_VPU_ENC_FMT_YUV420P: Y/CbCr 4:2:0 planar क्रमmat
 * @RK3288_VPU_ENC_FMT_YUV420SP: Y/CbCr 4:2:0 semi-planar क्रमmat
 * @RK3288_VPU_ENC_FMT_YUYV422: YUV 4:2:2 packed क्रमmat (YUYV)
 * @RK3288_VPU_ENC_FMT_UYVY422: YUV 4:2:2 packed क्रमmat (UYVY)
 */
क्रमागत hantro_enc_fmt अणु
	RK3288_VPU_ENC_FMT_YUV420P = 0,
	RK3288_VPU_ENC_FMT_YUV420SP = 1,
	RK3288_VPU_ENC_FMT_YUYV422 = 2,
	RK3288_VPU_ENC_FMT_UYVY422 = 3,
पूर्ण;

बाह्य स्थिर काष्ठा hantro_variant rk3399_vpu_variant;
बाह्य स्थिर काष्ठा hantro_variant rk3328_vpu_variant;
बाह्य स्थिर काष्ठा hantro_variant rk3288_vpu_variant;
बाह्य स्थिर काष्ठा hantro_variant imx8mq_vpu_variant;

बाह्य स्थिर काष्ठा hantro_postproc_regs hantro_g1_postproc_regs;

बाह्य स्थिर u32 hantro_vp8_dec_mc_filter[8][6];

व्योम hantro_watchकरोg(काष्ठा work_काष्ठा *work);
व्योम hantro_run(काष्ठा hantro_ctx *ctx);
व्योम hantro_irq_करोne(काष्ठा hantro_dev *vpu,
		     क्रमागत vb2_buffer_state result);
व्योम hantro_start_prepare_run(काष्ठा hantro_ctx *ctx);
व्योम hantro_end_prepare_run(काष्ठा hantro_ctx *ctx);

व्योम hantro_h1_jpeg_enc_run(काष्ठा hantro_ctx *ctx);
व्योम rk3399_vpu_jpeg_enc_run(काष्ठा hantro_ctx *ctx);
पूर्णांक hantro_jpeg_enc_init(काष्ठा hantro_ctx *ctx);
व्योम hantro_jpeg_enc_निकास(काष्ठा hantro_ctx *ctx);
व्योम hantro_jpeg_enc_करोne(काष्ठा hantro_ctx *ctx);

dma_addr_t hantro_h264_get_ref_buf(काष्ठा hantro_ctx *ctx,
				   अचिन्हित पूर्णांक dpb_idx);
पूर्णांक hantro_h264_dec_prepare_run(काष्ठा hantro_ctx *ctx);
व्योम hantro_g1_h264_dec_run(काष्ठा hantro_ctx *ctx);
पूर्णांक hantro_h264_dec_init(काष्ठा hantro_ctx *ctx);
व्योम hantro_h264_dec_निकास(काष्ठा hantro_ctx *ctx);

अटल अंतरभूत माप_प्रकार
hantro_h264_mv_size(अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	/*
	 * A decoded 8-bit 4:2:0 NV12 frame may need memory क्रम up to
	 * 448 bytes per macroblock with additional 32 bytes on
	 * multi-core variants.
	 *
	 * The H264 decoder needs extra space on the output buffers
	 * to store motion vectors. This is needed क्रम reference
	 * frames and only अगर the क्रमmat is non-post-processed NV12.
	 *
	 * Memory layout is as follow:
	 *
	 * +---------------------------+
	 * | Y-plane   256 bytes x MBs |
	 * +---------------------------+
	 * | UV-plane  128 bytes x MBs |
	 * +---------------------------+
	 * | MV buffer  64 bytes x MBs |
	 * +---------------------------+
	 * | MC sync          32 bytes |
	 * +---------------------------+
	 */
	वापस 64 * MB_WIDTH(width) * MB_WIDTH(height) + 32;
पूर्ण

व्योम hantro_g1_mpeg2_dec_run(काष्ठा hantro_ctx *ctx);
व्योम rk3399_vpu_mpeg2_dec_run(काष्ठा hantro_ctx *ctx);
व्योम hantro_mpeg2_dec_copy_qtable(u8 *qtable,
	स्थिर काष्ठा v4l2_ctrl_mpeg2_quantization *ctrl);
पूर्णांक hantro_mpeg2_dec_init(काष्ठा hantro_ctx *ctx);
व्योम hantro_mpeg2_dec_निकास(काष्ठा hantro_ctx *ctx);

व्योम hantro_g1_vp8_dec_run(काष्ठा hantro_ctx *ctx);
व्योम rk3399_vpu_vp8_dec_run(काष्ठा hantro_ctx *ctx);
पूर्णांक hantro_vp8_dec_init(काष्ठा hantro_ctx *ctx);
व्योम hantro_vp8_dec_निकास(काष्ठा hantro_ctx *ctx);
व्योम hantro_vp8_prob_update(काष्ठा hantro_ctx *ctx,
			    स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr);

#पूर्ण_अगर /* HANTRO_HW_H_ */
