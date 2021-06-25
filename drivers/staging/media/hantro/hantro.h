<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Hantro VPU codec driver
 *
 * Copyright 2018 Google LLC.
 *	Tomasz Figa <tfiga@chromium.org>
 *
 * Based on s5p-mfc driver by Samsung Electronics Co., Ltd.
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित HANTRO_H_
#घोषणा HANTRO_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>
#समावेश <linux/clk.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "hantro_hw.h"

काष्ठा hantro_ctx;
काष्ठा hantro_codec_ops;

#घोषणा HANTRO_JPEG_ENCODER	BIT(0)
#घोषणा HANTRO_ENCODERS		0x0000ffff
#घोषणा HANTRO_MPEG2_DECODER	BIT(16)
#घोषणा HANTRO_VP8_DECODER	BIT(17)
#घोषणा HANTRO_H264_DECODER	BIT(18)
#घोषणा HANTRO_DECODERS		0xffff0000

/**
 * काष्ठा hantro_irq - irq handler and name
 *
 * @name:			irq name क्रम device tree lookup
 * @handler:			पूर्णांकerrupt handler
 */
काष्ठा hantro_irq अणु
	स्थिर अक्षर *name;
	irqवापस_t (*handler)(पूर्णांक irq, व्योम *priv);
पूर्ण;

/**
 * काष्ठा hantro_variant - inक्रमmation about VPU hardware variant
 *
 * @enc_offset:			Offset from VPU base to encoder रेजिस्टरs.
 * @dec_offset:			Offset from VPU base to decoder रेजिस्टरs.
 * @enc_fmts:			Encoder क्रमmats.
 * @num_enc_fmts:		Number of encoder क्रमmats.
 * @dec_fmts:			Decoder क्रमmats.
 * @num_dec_fmts:		Number of decoder क्रमmats.
 * @postproc_fmts:		Post-processor क्रमmats.
 * @num_postproc_fmts:		Number of post-processor क्रमmats.
 * @codec:			Supported codecs
 * @codec_ops:			Codec ops.
 * @init:			Initialize hardware.
 * @runसमय_resume:		reenable hardware after घातer gating
 * @irqs:			array of irq names and पूर्णांकerrupt handlers
 * @num_irqs:			number of irqs in the array
 * @clk_names:			array of घड़ी names
 * @num_घड़ीs:			number of घड़ीs in the array
 * @reg_names:			array of रेजिस्टर range names
 * @num_regs:			number of रेजिस्टर range names in the array
 * @postproc_regs:		&काष्ठा hantro_postproc_regs poपूर्णांकer
 */
काष्ठा hantro_variant अणु
	अचिन्हित पूर्णांक enc_offset;
	अचिन्हित पूर्णांक dec_offset;
	स्थिर काष्ठा hantro_fmt *enc_fmts;
	अचिन्हित पूर्णांक num_enc_fmts;
	स्थिर काष्ठा hantro_fmt *dec_fmts;
	अचिन्हित पूर्णांक num_dec_fmts;
	स्थिर काष्ठा hantro_fmt *postproc_fmts;
	अचिन्हित पूर्णांक num_postproc_fmts;
	अचिन्हित पूर्णांक codec;
	स्थिर काष्ठा hantro_codec_ops *codec_ops;
	पूर्णांक (*init)(काष्ठा hantro_dev *vpu);
	पूर्णांक (*runसमय_resume)(काष्ठा hantro_dev *vpu);
	स्थिर काष्ठा hantro_irq *irqs;
	पूर्णांक num_irqs;
	स्थिर अक्षर * स्थिर *clk_names;
	पूर्णांक num_घड़ीs;
	स्थिर अक्षर * स्थिर *reg_names;
	पूर्णांक num_regs;
	स्थिर काष्ठा hantro_postproc_regs *postproc_regs;
पूर्ण;

/**
 * क्रमागत hantro_codec_mode - codec operating mode.
 * @HANTRO_MODE_NONE:  No operating mode. Used क्रम RAW video क्रमmats.
 * @HANTRO_MODE_JPEG_ENC: JPEG encoder.
 * @HANTRO_MODE_H264_DEC: H264 decoder.
 * @HANTRO_MODE_MPEG2_DEC: MPEG-2 decoder.
 * @HANTRO_MODE_VP8_DEC: VP8 decoder.
 */
क्रमागत hantro_codec_mode अणु
	HANTRO_MODE_NONE = -1,
	HANTRO_MODE_JPEG_ENC,
	HANTRO_MODE_H264_DEC,
	HANTRO_MODE_MPEG2_DEC,
	HANTRO_MODE_VP8_DEC,
पूर्ण;

/*
 * काष्ठा hantro_ctrl - helper type to declare supported controls
 * @codec:	codec id this control beदीर्घ to (HANTRO_JPEG_ENCODER, etc.)
 * @cfg:	control configuration
 */
काष्ठा hantro_ctrl अणु
	अचिन्हित पूर्णांक codec;
	काष्ठा v4l2_ctrl_config cfg;
पूर्ण;

/*
 * काष्ठा hantro_func - Hantro VPU functionality
 *
 * @id:			processing functionality ID (can be
 *			%MEDIA_ENT_F_PROC_VIDEO_ENCODER or
 *			%MEDIA_ENT_F_PROC_VIDEO_DECODER)
 * @vdev:		&काष्ठा video_device that exposes the encoder or
 *			decoder functionality
 * @source_pad:		&काष्ठा media_pad with the source pad.
 * @sink:		&काष्ठा media_entity poपूर्णांकer with the sink entity
 * @sink_pad:		&काष्ठा media_pad with the sink pad.
 * @proc:		&काष्ठा media_entity poपूर्णांकer with the M2M device itself.
 * @proc_pads:		&काष्ठा media_pad with the @proc pads.
 * @पूर्णांकf_devnode:	&काष्ठा media_पूर्णांकf devnode poपूर्णांकer with the पूर्णांकerface
 *			with controls the M2M device.
 *
 * Contains everything needed to attach the video device to the media device.
 */
काष्ठा hantro_func अणु
	अचिन्हित पूर्णांक id;
	काष्ठा video_device vdev;
	काष्ठा media_pad source_pad;
	काष्ठा media_entity sink;
	काष्ठा media_pad sink_pad;
	काष्ठा media_entity proc;
	काष्ठा media_pad proc_pads[2];
	काष्ठा media_पूर्णांकf_devnode *पूर्णांकf_devnode;
पूर्ण;

अटल अंतरभूत काष्ठा hantro_func *
hantro_vdev_to_func(काष्ठा video_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा hantro_func, vdev);
पूर्ण

/**
 * काष्ठा hantro_dev - driver data
 * @v4l2_dev:		V4L2 device to रेजिस्टर video devices क्रम.
 * @m2m_dev:		mem2mem device associated to this device.
 * @mdev:		media device associated to this device.
 * @encoder:		encoder functionality.
 * @decoder:		decoder functionality.
 * @pdev:		Poपूर्णांकer to VPU platक्रमm device.
 * @dev:		Poपूर्णांकer to device क्रम convenient logging using
 *			dev_ macros.
 * @घड़ीs:		Array of घड़ी handles.
 * @reg_bases:		Mapped addresses of VPU रेजिस्टरs.
 * @enc_base:		Mapped address of VPU encoder रेजिस्टर क्रम convenience.
 * @dec_base:		Mapped address of VPU decoder रेजिस्टर क्रम convenience.
 * @ctrl_base:		Mapped address of VPU control block.
 * @vpu_mutex:		Mutex to synchronize V4L2 calls.
 * @irqlock:		Spinlock to synchronize access to data काष्ठाures
 *			shared with पूर्णांकerrupt handlers.
 * @variant:		Hardware variant-specअगरic parameters.
 * @watchकरोg_work:	Delayed work क्रम hardware समयout handling.
 */
काष्ठा hantro_dev अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा media_device mdev;
	काष्ठा hantro_func *encoder;
	काष्ठा hantro_func *decoder;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;
	काष्ठा clk_bulk_data *घड़ीs;
	व्योम __iomem **reg_bases;
	व्योम __iomem *enc_base;
	व्योम __iomem *dec_base;
	व्योम __iomem *ctrl_base;

	काष्ठा mutex vpu_mutex;	/* video_device lock */
	spinlock_t irqlock;
	स्थिर काष्ठा hantro_variant *variant;
	काष्ठा delayed_work watchकरोg_work;
पूर्ण;

/**
 * काष्ठा hantro_ctx - Context (instance) निजी data.
 *
 * @dev:		VPU driver data to which the context beदीर्घs.
 * @fh:			V4L2 file handler.
 * @is_encoder:		Decoder or encoder context?
 *
 * @sequence_cap:       Sequence counter क्रम capture queue
 * @sequence_out:       Sequence counter क्रम output queue
 *
 * @vpu_src_fmt:	Descriptor of active source क्रमmat.
 * @src_fmt:		V4L2 pixel क्रमmat of active source क्रमmat.
 * @vpu_dst_fmt:	Descriptor of active destination क्रमmat.
 * @dst_fmt:		V4L2 pixel क्रमmat of active destination क्रमmat.
 *
 * @ctrl_handler:	Control handler used to रेजिस्टर controls.
 * @jpeg_quality:	User-specअगरied JPEG compression quality.
 *
 * @codec_ops:		Set of operations related to codec mode.
 * @postproc:		Post-processing context.
 * @h264_dec:		H.264-decoding context.
 * @jpeg_enc:		JPEG-encoding context.
 * @mpeg2_dec:		MPEG-2-decoding context.
 * @vp8_dec:		VP8-decoding context.
 */
काष्ठा hantro_ctx अणु
	काष्ठा hantro_dev *dev;
	काष्ठा v4l2_fh fh;
	bool is_encoder;

	u32 sequence_cap;
	u32 sequence_out;

	स्थिर काष्ठा hantro_fmt *vpu_src_fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane src_fmt;
	स्थिर काष्ठा hantro_fmt *vpu_dst_fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane dst_fmt;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	पूर्णांक jpeg_quality;

	स्थिर काष्ठा hantro_codec_ops *codec_ops;
	काष्ठा hantro_postproc_ctx postproc;

	/* Specअगरic क्रम particular codec modes. */
	जोड़ अणु
		काष्ठा hantro_h264_dec_hw_ctx h264_dec;
		काष्ठा hantro_jpeg_enc_hw_ctx jpeg_enc;
		काष्ठा hantro_mpeg2_dec_hw_ctx mpeg2_dec;
		काष्ठा hantro_vp8_dec_hw_ctx vp8_dec;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा hantro_fmt - inक्रमmation about supported video क्रमmats.
 * @name:	Human पढ़ोable name of the क्रमmat.
 * @fourcc:	FourCC code of the क्रमmat. See V4L2_PIX_FMT_*.
 * @codec_mode:	Codec mode related to this क्रमmat. See
 *		क्रमागत hantro_codec_mode.
 * @header_size: Optional header size. Currently used by JPEG encoder.
 * @max_depth:	Maximum depth, क्रम bitstream क्रमmats
 * @enc_fmt:	Format identअगरier क्रम encoder रेजिस्टरs.
 * @frmsize:	Supported range of frame sizes (only क्रम bitstream क्रमmats).
 */
काष्ठा hantro_fmt अणु
	अक्षर *name;
	u32 fourcc;
	क्रमागत hantro_codec_mode codec_mode;
	पूर्णांक header_size;
	पूर्णांक max_depth;
	क्रमागत hantro_enc_fmt enc_fmt;
	काष्ठा v4l2_frmsize_stepwise frmsize;
पूर्ण;

काष्ठा hantro_reg अणु
	u32 base;
	u32 shअगरt;
	u32 mask;
पूर्ण;

काष्ठा hantro_postproc_regs अणु
	काष्ठा hantro_reg pipeline_en;
	काष्ठा hantro_reg max_burst;
	काष्ठा hantro_reg clk_gate;
	काष्ठा hantro_reg out_swap32;
	काष्ठा hantro_reg out_endian;
	काष्ठा hantro_reg out_luma_base;
	काष्ठा hantro_reg input_width;
	काष्ठा hantro_reg input_height;
	काष्ठा hantro_reg output_width;
	काष्ठा hantro_reg output_height;
	काष्ठा hantro_reg input_fmt;
	काष्ठा hantro_reg output_fmt;
	काष्ठा hantro_reg orig_width;
	काष्ठा hantro_reg display_width;
पूर्ण;

/* Logging helpers */

/**
 * DOC: hantro_debug: Module parameter to control level of debugging messages.
 *
 * Level of debugging messages can be controlled by bits of
 * module parameter called "debug". Meaning of particular
 * bits is as follows:
 *
 * bit 0 - global inक्रमmation: mode, size, init, release
 * bit 1 - each run start/result inक्रमmation
 * bit 2 - contents of small controls from userspace
 * bit 3 - contents of big controls from userspace
 * bit 4 - detail fmt, ctrl, buffer q/dq inक्रमmation
 * bit 5 - detail function enter/leave trace inक्रमmation
 * bit 6 - रेजिस्टर ग_लिखो/पढ़ो inक्रमmation
 */
बाह्य पूर्णांक hantro_debug;

#घोषणा vpu_debug(level, fmt, args...)				\
	करो अणु							\
		अगर (hantro_debug & BIT(level))		\
			pr_info("%s:%d: " fmt,	                \
				 __func__, __LINE__, ##args);	\
	पूर्ण जबतक (0)

#घोषणा vpu_err(fmt, args...)					\
	pr_err("%s:%d: " fmt, __func__, __LINE__, ##args)

/* Structure access helpers. */
अटल अंतरभूत काष्ठा hantro_ctx *fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा hantro_ctx, fh);
पूर्ण

/* Register accessors. */
अटल अंतरभूत व्योम vepu_ग_लिखो_relaxed(काष्ठा hantro_dev *vpu,
				      u32 val, u32 reg)
अणु
	vpu_debug(6, "0x%04x = 0x%08x\n", reg / 4, val);
	ग_लिखोl_relaxed(val, vpu->enc_base + reg);
पूर्ण

अटल अंतरभूत व्योम vepu_ग_लिखो(काष्ठा hantro_dev *vpu, u32 val, u32 reg)
अणु
	vpu_debug(6, "0x%04x = 0x%08x\n", reg / 4, val);
	ग_लिखोl(val, vpu->enc_base + reg);
पूर्ण

अटल अंतरभूत u32 vepu_पढ़ो(काष्ठा hantro_dev *vpu, u32 reg)
अणु
	u32 val = पढ़ोl(vpu->enc_base + reg);

	vpu_debug(6, "0x%04x = 0x%08x\n", reg / 4, val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम vdpu_ग_लिखो_relaxed(काष्ठा hantro_dev *vpu,
				      u32 val, u32 reg)
अणु
	vpu_debug(6, "0x%04x = 0x%08x\n", reg / 4, val);
	ग_लिखोl_relaxed(val, vpu->dec_base + reg);
पूर्ण

अटल अंतरभूत व्योम vdpu_ग_लिखो(काष्ठा hantro_dev *vpu, u32 val, u32 reg)
अणु
	vpu_debug(6, "0x%04x = 0x%08x\n", reg / 4, val);
	ग_लिखोl(val, vpu->dec_base + reg);
पूर्ण

अटल अंतरभूत u32 vdpu_पढ़ो(काष्ठा hantro_dev *vpu, u32 reg)
अणु
	u32 val = पढ़ोl(vpu->dec_base + reg);

	vpu_debug(6, "0x%04x = 0x%08x\n", reg / 4, val);
	वापस val;
पूर्ण

अटल अंतरभूत u32 vdpu_पढ़ो_mask(काष्ठा hantro_dev *vpu,
				 स्थिर काष्ठा hantro_reg *reg,
				 u32 val)
अणु
	u32 v;

	v = vdpu_पढ़ो(vpu, reg->base);
	v &= ~(reg->mask << reg->shअगरt);
	v |= ((val & reg->mask) << reg->shअगरt);
	वापस v;
पूर्ण

अटल अंतरभूत व्योम hantro_reg_ग_लिखो(काष्ठा hantro_dev *vpu,
				    स्थिर काष्ठा hantro_reg *reg,
				    u32 val)
अणु
	vdpu_ग_लिखो_relaxed(vpu, vdpu_पढ़ो_mask(vpu, reg, val), reg->base);
पूर्ण

अटल अंतरभूत व्योम hantro_reg_ग_लिखो_s(काष्ठा hantro_dev *vpu,
				      स्थिर काष्ठा hantro_reg *reg,
				      u32 val)
अणु
	vdpu_ग_लिखो(vpu, vdpu_पढ़ो_mask(vpu, reg, val), reg->base);
पूर्ण

व्योम *hantro_get_ctrl(काष्ठा hantro_ctx *ctx, u32 id);
dma_addr_t hantro_get_ref(काष्ठा hantro_ctx *ctx, u64 ts);

अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
hantro_get_src_buf(काष्ठा hantro_ctx *ctx)
अणु
	वापस v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
पूर्ण

अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
hantro_get_dst_buf(काष्ठा hantro_ctx *ctx)
अणु
	वापस v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
पूर्ण

अटल अंतरभूत bool
hantro_needs_postproc(स्थिर काष्ठा hantro_ctx *ctx,
		      स्थिर काष्ठा hantro_fmt *fmt)
अणु
	वापस !ctx->is_encoder && fmt->fourcc != V4L2_PIX_FMT_NV12;
पूर्ण

अटल अंतरभूत dma_addr_t
hantro_get_dec_buf_addr(काष्ठा hantro_ctx *ctx, काष्ठा vb2_buffer *vb)
अणु
	अगर (hantro_needs_postproc(ctx, ctx->vpu_dst_fmt))
		वापस ctx->postproc.dec_q[vb->index].dma;
	वापस vb2_dma_contig_plane_dma_addr(vb, 0);
पूर्ण

व्योम hantro_postproc_disable(काष्ठा hantro_ctx *ctx);
व्योम hantro_postproc_enable(काष्ठा hantro_ctx *ctx);
व्योम hantro_postproc_मुक्त(काष्ठा hantro_ctx *ctx);
पूर्णांक hantro_postproc_alloc(काष्ठा hantro_ctx *ctx);

#पूर्ण_अगर /* HANTRO_H_ */
