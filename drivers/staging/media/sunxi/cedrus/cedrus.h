<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cedrus VPU driver
 *
 * Copyright (C) 2016 Florent Revest <florent.revest@मुक्त-electrons.com>
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 * Copyright (C) 2018 Bootlin
 *
 * Based on the vim2m driver, that is:
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */

#अगर_अघोषित _CEDRUS_H_
#घोषणा _CEDRUS_H_

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश <linux/iopoll.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा CEDRUS_NAME			"cedrus"

#घोषणा CEDRUS_CAPABILITY_UNTILED	BIT(0)
#घोषणा CEDRUS_CAPABILITY_H265_DEC	BIT(1)
#घोषणा CEDRUS_CAPABILITY_H264_DEC	BIT(2)
#घोषणा CEDRUS_CAPABILITY_MPEG2_DEC	BIT(3)
#घोषणा CEDRUS_CAPABILITY_VP8_DEC	BIT(4)

क्रमागत cedrus_codec अणु
	CEDRUS_CODEC_MPEG2,
	CEDRUS_CODEC_H264,
	CEDRUS_CODEC_H265,
	CEDRUS_CODEC_VP8,
	CEDRUS_CODEC_LAST,
पूर्ण;

क्रमागत cedrus_irq_status अणु
	CEDRUS_IRQ_NONE,
	CEDRUS_IRQ_ERROR,
	CEDRUS_IRQ_OK,
पूर्ण;

क्रमागत cedrus_h264_pic_type अणु
	CEDRUS_H264_PIC_TYPE_FRAME	= 0,
	CEDRUS_H264_PIC_TYPE_FIELD,
	CEDRUS_H264_PIC_TYPE_MBAFF,
पूर्ण;

काष्ठा cedrus_control अणु
	काष्ठा v4l2_ctrl_config cfg;
	क्रमागत cedrus_codec	codec;
पूर्ण;

काष्ठा cedrus_h264_run अणु
	स्थिर काष्ठा v4l2_ctrl_h264_decode_params	*decode_params;
	स्थिर काष्ठा v4l2_ctrl_h264_pps			*pps;
	स्थिर काष्ठा v4l2_ctrl_h264_scaling_matrix	*scaling_matrix;
	स्थिर काष्ठा v4l2_ctrl_h264_slice_params	*slice_params;
	स्थिर काष्ठा v4l2_ctrl_h264_sps			*sps;
	स्थिर काष्ठा v4l2_ctrl_h264_pred_weights	*pred_weights;
पूर्ण;

काष्ठा cedrus_mpeg2_run अणु
	स्थिर काष्ठा v4l2_ctrl_mpeg2_slice_params	*slice_params;
	स्थिर काष्ठा v4l2_ctrl_mpeg2_quantization	*quantization;
पूर्ण;

काष्ठा cedrus_h265_run अणु
	स्थिर काष्ठा v4l2_ctrl_hevc_sps			*sps;
	स्थिर काष्ठा v4l2_ctrl_hevc_pps			*pps;
	स्थिर काष्ठा v4l2_ctrl_hevc_slice_params	*slice_params;
पूर्ण;

काष्ठा cedrus_vp8_run अणु
	स्थिर काष्ठा v4l2_ctrl_vp8_frame		*frame_params;
पूर्ण;

काष्ठा cedrus_run अणु
	काष्ठा vb2_v4l2_buffer	*src;
	काष्ठा vb2_v4l2_buffer	*dst;

	जोड़ अणु
		काष्ठा cedrus_h264_run	h264;
		काष्ठा cedrus_mpeg2_run	mpeg2;
		काष्ठा cedrus_h265_run	h265;
		काष्ठा cedrus_vp8_run	vp8;
	पूर्ण;
पूर्ण;

काष्ठा cedrus_buffer अणु
	काष्ठा v4l2_m2m_buffer          m2m_buf;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक			position;
			क्रमागत cedrus_h264_pic_type	pic_type;
		पूर्ण h264;
	पूर्ण codec;
पूर्ण;

काष्ठा cedrus_ctx अणु
	काष्ठा v4l2_fh			fh;
	काष्ठा cedrus_dev		*dev;

	काष्ठा v4l2_pix_क्रमmat		src_fmt;
	काष्ठा v4l2_pix_क्रमmat		dst_fmt;
	क्रमागत cedrus_codec		current_codec;

	काष्ठा v4l2_ctrl_handler	hdl;
	काष्ठा v4l2_ctrl		**ctrls;

	जोड़ अणु
		काष्ठा अणु
			व्योम		*mv_col_buf;
			dma_addr_t	mv_col_buf_dma;
			sमाप_प्रकार		mv_col_buf_field_size;
			sमाप_प्रकार		mv_col_buf_size;
			व्योम		*pic_info_buf;
			dma_addr_t	pic_info_buf_dma;
			sमाप_प्रकार		pic_info_buf_size;
			व्योम		*neighbor_info_buf;
			dma_addr_t	neighbor_info_buf_dma;
			व्योम		*deblk_buf;
			dma_addr_t	deblk_buf_dma;
			sमाप_प्रकार		deblk_buf_size;
			व्योम		*पूर्णांकra_pred_buf;
			dma_addr_t	पूर्णांकra_pred_buf_dma;
			sमाप_प्रकार		पूर्णांकra_pred_buf_size;
		पूर्ण h264;
		काष्ठा अणु
			व्योम		*mv_col_buf;
			dma_addr_t	mv_col_buf_addr;
			sमाप_प्रकार		mv_col_buf_size;
			sमाप_प्रकार		mv_col_buf_unit_size;
			व्योम		*neighbor_info_buf;
			dma_addr_t	neighbor_info_buf_addr;
		पूर्ण h265;
		काष्ठा अणु
			अचिन्हित पूर्णांक	last_frame_p_type;
			अचिन्हित पूर्णांक	last_filter_type;
			अचिन्हित पूर्णांक	last_sharpness_level;

			u8		*entropy_probs_buf;
			dma_addr_t	entropy_probs_buf_dma;
		पूर्ण vp8;
	पूर्ण codec;
पूर्ण;

काष्ठा cedrus_dec_ops अणु
	व्योम (*irq_clear)(काष्ठा cedrus_ctx *ctx);
	व्योम (*irq_disable)(काष्ठा cedrus_ctx *ctx);
	क्रमागत cedrus_irq_status (*irq_status)(काष्ठा cedrus_ctx *ctx);
	व्योम (*setup)(काष्ठा cedrus_ctx *ctx, काष्ठा cedrus_run *run);
	पूर्णांक (*start)(काष्ठा cedrus_ctx *ctx);
	व्योम (*stop)(काष्ठा cedrus_ctx *ctx);
	व्योम (*trigger)(काष्ठा cedrus_ctx *ctx);
पूर्ण;

काष्ठा cedrus_variant अणु
	अचिन्हित पूर्णांक	capabilities;
	अचिन्हित पूर्णांक	mod_rate;
पूर्ण;

काष्ठा cedrus_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;
	काष्ठा media_device	mdev;
	काष्ठा media_pad	pad[2];
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा device		*dev;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा cedrus_dec_ops	*dec_ops[CEDRUS_CODEC_LAST];

	/* Device file mutex */
	काष्ठा mutex		dev_mutex;

	व्योम __iomem		*base;

	काष्ठा clk		*mod_clk;
	काष्ठा clk		*ahb_clk;
	काष्ठा clk		*ram_clk;

	काष्ठा reset_control	*rstc;

	अचिन्हित पूर्णांक		capabilities;
पूर्ण;

बाह्य काष्ठा cedrus_dec_ops cedrus_dec_ops_mpeg2;
बाह्य काष्ठा cedrus_dec_ops cedrus_dec_ops_h264;
बाह्य काष्ठा cedrus_dec_ops cedrus_dec_ops_h265;
बाह्य काष्ठा cedrus_dec_ops cedrus_dec_ops_vp8;

अटल अंतरभूत व्योम cedrus_ग_लिखो(काष्ठा cedrus_dev *dev, u32 reg, u32 val)
अणु
	ग_लिखोl(val, dev->base + reg);
पूर्ण

अटल अंतरभूत u32 cedrus_पढ़ो(काष्ठा cedrus_dev *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->base + reg);
पूर्ण

अटल अंतरभूत u32 cedrus_रुको_क्रम(काष्ठा cedrus_dev *dev, u32 reg, u32 flag)
अणु
	u32 value;

	वापस पढ़ोl_poll_समयout_atomic(dev->base + reg, value,
			(value & flag) == 0, 10, 1000);
पूर्ण

अटल अंतरभूत dma_addr_t cedrus_buf_addr(काष्ठा vb2_buffer *buf,
					 काष्ठा v4l2_pix_क्रमmat *pix_fmt,
					 अचिन्हित पूर्णांक plane)
अणु
	dma_addr_t addr = vb2_dma_contig_plane_dma_addr(buf, 0);

	वापस addr + (pix_fmt ? (dma_addr_t)pix_fmt->bytesperline *
	       pix_fmt->height * plane : 0);
पूर्ण

अटल अंतरभूत dma_addr_t cedrus_dst_buf_addr(काष्ठा cedrus_ctx *ctx,
					     पूर्णांक index, अचिन्हित पूर्णांक plane)
अणु
	काष्ठा vb2_buffer *buf = शून्य;
	काष्ठा vb2_queue *vq;

	अगर (index < 0)
		वापस 0;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (vq)
		buf = vb2_get_buffer(vq, index);

	वापस buf ? cedrus_buf_addr(buf, &ctx->dst_fmt, plane) : 0;
पूर्ण

अटल अंतरभूत काष्ठा cedrus_buffer *
vb2_v4l2_to_cedrus_buffer(स्थिर काष्ठा vb2_v4l2_buffer *p)
अणु
	वापस container_of(p, काष्ठा cedrus_buffer, m2m_buf.vb);
पूर्ण

अटल अंतरभूत काष्ठा cedrus_buffer *
vb2_to_cedrus_buffer(स्थिर काष्ठा vb2_buffer *p)
अणु
	वापस vb2_v4l2_to_cedrus_buffer(to_vb2_v4l2_buffer(p));
पूर्ण

व्योम *cedrus_find_control_data(काष्ठा cedrus_ctx *ctx, u32 id);

#पूर्ण_अगर
