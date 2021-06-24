<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/drivers/media/platक्रमm/s5p-jpeg/jpeg-core.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित JPEG_CORE_H_
#घोषणा JPEG_CORE_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा S5P_JPEG_M2M_NAME		"s5p-jpeg"

#घोषणा JPEG_MAX_CLOCKS			4

/* JPEG compression quality setting */
#घोषणा S5P_JPEG_COMPR_QUAL_BEST	0
#घोषणा S5P_JPEG_COMPR_QUAL_WORST	3

/* JPEG RGB to YCbCr conversion matrix coefficients */
#घोषणा S5P_JPEG_COEF11			0x4d
#घोषणा S5P_JPEG_COEF12			0x97
#घोषणा S5P_JPEG_COEF13			0x1e
#घोषणा S5P_JPEG_COEF21			0x2c
#घोषणा S5P_JPEG_COEF22			0x57
#घोषणा S5P_JPEG_COEF23			0x83
#घोषणा S5P_JPEG_COEF31			0x83
#घोषणा S5P_JPEG_COEF32			0x6e
#घोषणा S5P_JPEG_COEF33			0x13

#घोषणा EXYNOS3250_IRQ_TIMEOUT		0x10000000

/* a selection of JPEG markers */
#घोषणा TEM				0x01
#घोषणा SOF0				0xc0
#घोषणा DHT				0xc4
#घोषणा RST				0xd0
#घोषणा SOI				0xd8
#घोषणा EOI				0xd9
#घोषणा	SOS				0xda
#घोषणा DQT				0xdb
#घोषणा DHP				0xde

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा SJPEG_FMT_FLAG_ENC_CAPTURE	(1 << 0)
#घोषणा SJPEG_FMT_FLAG_ENC_OUTPUT	(1 << 1)
#घोषणा SJPEG_FMT_FLAG_DEC_CAPTURE	(1 << 2)
#घोषणा SJPEG_FMT_FLAG_DEC_OUTPUT	(1 << 3)
#घोषणा SJPEG_FMT_FLAG_S5P		(1 << 4)
#घोषणा SJPEG_FMT_FLAG_EXYNOS3250	(1 << 5)
#घोषणा SJPEG_FMT_FLAG_EXYNOS4		(1 << 6)
#घोषणा SJPEG_FMT_RGB			(1 << 7)
#घोषणा SJPEG_FMT_NON_RGB		(1 << 8)

#घोषणा S5P_JPEG_ENCODE		0
#घोषणा S5P_JPEG_DECODE		1
#घोषणा S5P_JPEG_DISABLE	-1

#घोषणा FMT_TYPE_OUTPUT		0
#घोषणा FMT_TYPE_CAPTURE	1

#घोषणा SJPEG_SUBSAMPLING_444	0x11
#घोषणा SJPEG_SUBSAMPLING_422	0x21
#घोषणा SJPEG_SUBSAMPLING_420	0x22

#घोषणा S5P_JPEG_MAX_MARKER	4

/* Version numbers */
क्रमागत sjpeg_version अणु
	SJPEG_S5P,
	SJPEG_EXYNOS3250,
	SJPEG_EXYNOS4,
	SJPEG_EXYNOS5420,
	SJPEG_EXYNOS5433,
पूर्ण;

क्रमागत exynos4_jpeg_result अणु
	OK_ENC_OR_DEC,
	ERR_PROT,
	ERR_DEC_INVALID_FORMAT,
	ERR_MULTI_SCAN,
	ERR_FRAME,
	ERR_UNKNOWN,
पूर्ण;

क्रमागत  exynos4_jpeg_img_quality_level अणु
	QUALITY_LEVEL_1 = 0,	/* high */
	QUALITY_LEVEL_2,
	QUALITY_LEVEL_3,
	QUALITY_LEVEL_4,	/* low */
पूर्ण;

क्रमागत s5p_jpeg_ctx_state अणु
	JPEGCTX_RUNNING = 0,
	JPEGCTX_RESOLUTION_CHANGE,
पूर्ण;

/**
 * काष्ठा s5p_jpeg - JPEG IP असलtraction
 * @lock:		the mutex protecting this काष्ठाure
 * @slock:		spinlock protecting the device contexts
 * @v4l2_dev:		v4l2 device क्रम mem2mem mode
 * @vfd_encoder:	video device node क्रम encoder mem2mem mode
 * @vfd_decoder:	video device node क्रम decoder mem2mem mode
 * @m2m_dev:		v4l2 mem2mem device data
 * @regs:		JPEG IP रेजिस्टरs mapping
 * @irq:		JPEG IP irq
 * @irq_ret:		JPEG IP irq result value
 * @घड़ीs:		JPEG IP घड़ी(s)
 * @dev:		JPEG IP काष्ठा device
 * @variant:		driver variant to be used
 * @irq_status:		पूर्णांकerrupt flags set during single encode/decode
 *			operation
 */
काष्ठा s5p_jpeg अणु
	काष्ठा mutex		lock;
	spinlock_t		slock;

	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	*vfd_encoder;
	काष्ठा video_device	*vfd_decoder;
	काष्ठा v4l2_m2m_dev	*m2m_dev;

	व्योम __iomem		*regs;
	अचिन्हित पूर्णांक		irq;
	क्रमागत exynos4_jpeg_result irq_ret;
	काष्ठा clk		*घड़ीs[JPEG_MAX_CLOCKS];
	काष्ठा device		*dev;
	काष्ठा s5p_jpeg_variant *variant;
	u32			irq_status;
पूर्ण;

काष्ठा s5p_jpeg_variant अणु
	अचिन्हित पूर्णांक		version;
	अचिन्हित पूर्णांक		fmt_ver_flag;
	अचिन्हित पूर्णांक		hw3250_compat:1;
	अचिन्हित पूर्णांक		htbl_reinit:1;
	अचिन्हित पूर्णांक		hw_ex4_compat:1;
	काष्ठा v4l2_m2m_ops	*m2m_ops;
	irqवापस_t		(*jpeg_irq)(पूर्णांक irq, व्योम *priv);
	स्थिर अक्षर		*clk_names[JPEG_MAX_CLOCKS];
	पूर्णांक			num_घड़ीs;
पूर्ण;

/**
 * काष्ठा s5p_jpeg_fmt - driver's पूर्णांकernal color क्रमmat data
 * @fourcc:	the fourcc code, 0 अगर not applicable
 * @depth:	number of bits per pixel
 * @colplanes:	number of color planes (1 क्रम packed क्रमmats)
 * @memplanes:	number of memory planes (1 क्रम packed क्रमmats)
 * @h_align:	horizontal alignment order (align to 2^h_align)
 * @v_align:	vertical alignment order (align to 2^v_align)
 * @subsampling:subsampling of a raw क्रमmat or a JPEG
 * @flags:	flags describing क्रमmat applicability
 */
काष्ठा s5p_jpeg_fmt अणु
	u32	fourcc;
	पूर्णांक	depth;
	पूर्णांक	colplanes;
	पूर्णांक	memplanes;
	पूर्णांक	h_align;
	पूर्णांक	v_align;
	पूर्णांक	subsampling;
	u32	flags;
पूर्ण;

/**
 * काष्ठा s5p_jpeg_marker - collection of markers from jpeg header
 * @marker:	markers' positions relative to the buffer beginning
 * @len:	markers' payload lengths (without length field)
 * @n:		number of markers in collection
 */
काष्ठा s5p_jpeg_marker अणु
	u32	marker[S5P_JPEG_MAX_MARKER];
	u32	len[S5P_JPEG_MAX_MARKER];
	u32	n;
पूर्ण;

/**
 * काष्ठा s5p_jpeg_q_data - parameters of one queue
 * @fmt:	driver-specअगरic क्रमmat of this queue
 * @w:		image width
 * @h:		image height
 * @sos:	SOS marker's position relative to the buffer beginning
 * @dht:	DHT markers' positions relative to the buffer beginning
 * @dqt:	DQT markers' positions relative to the buffer beginning
 * @sof:	SOF0 marker's position relative to the buffer beginning
 * @sof_len:	SOF0 marker's payload length (without length field itself)
 * @size:	image buffer size in bytes
 */
काष्ठा s5p_jpeg_q_data अणु
	काष्ठा s5p_jpeg_fmt	*fmt;
	u32			w;
	u32			h;
	u32			sos;
	काष्ठा s5p_jpeg_marker	dht;
	काष्ठा s5p_jpeg_marker	dqt;
	u32			sof;
	u32			sof_len;
	u32			size;
पूर्ण;

/**
 * काष्ठा s5p_jpeg_ctx - the device context data
 * @jpeg:		JPEG IP device क्रम this context
 * @mode:		compression (encode) operation or decompression (decode)
 * @compr_quality:	destination image quality in compression (encode) mode
 * @restart_पूर्णांकerval:	JPEG restart पूर्णांकerval क्रम JPEG encoding
 * @subsampling:	subsampling of a raw क्रमmat or a JPEG
 * @out_q:		source (output) queue inक्रमmation
 * @cap_q:		destination (capture) queue queue inक्रमmation
 * @scale_factor:	scale factor क्रम JPEG decoding
 * @crop_rect:		a rectangle representing crop area of the output buffer
 * @fh:			V4L2 file handle
 * @hdr_parsed:		set अगर header has been parsed during decompression
 * @crop_altered:	set अगर crop rectangle has been altered by the user space
 * @ctrl_handler:	controls handler
 * @state:		state of the context
 */
काष्ठा s5p_jpeg_ctx अणु
	काष्ठा s5p_jpeg		*jpeg;
	अचिन्हित पूर्णांक		mode;
	अचिन्हित लघु		compr_quality;
	अचिन्हित लघु		restart_पूर्णांकerval;
	अचिन्हित लघु		subsampling;
	काष्ठा s5p_jpeg_q_data	out_q;
	काष्ठा s5p_jpeg_q_data	cap_q;
	अचिन्हित पूर्णांक		scale_factor;
	काष्ठा v4l2_rect	crop_rect;
	काष्ठा v4l2_fh		fh;
	bool			hdr_parsed;
	bool			crop_altered;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	क्रमागत s5p_jpeg_ctx_state	state;
पूर्ण;

/**
 * काष्ठा s5p_jpeg_buffer - description of memory containing input JPEG data
 * @size:	buffer size
 * @curr:	current position in the buffer
 * @data:	poपूर्णांकer to the data
 */
काष्ठा s5p_jpeg_buffer अणु
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ curr;
	अचिन्हित दीर्घ data;
पूर्ण;

/**
 * काष्ठा s5p_jpeg_addr - JPEG converter physical address set क्रम DMA
 * @y:   luminance plane physical address
 * @cb:  Cb plane physical address
 * @cr:  Cr plane physical address
 */
काष्ठा s5p_jpeg_addr अणु
	u32     y;
	u32     cb;
	u32     cr;
पूर्ण;

#पूर्ण_अगर /* JPEG_CORE_H */
