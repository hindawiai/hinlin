<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author: Mikhail Ulyanov
 * Copyright (C) 2014-2015 Cogent Embedded, Inc.  <source@cogentembedded.com>
 * Copyright (C) 2014-2015 Renesas Electronics Corporation
 *
 * This is based on the drivers/media/platक्रमm/s5p-jpeg driver by
 * Andrzej Pietrasiewicz and Jacek Anaszewski.
 * Some portions of code inspired by VSP1 driver by Laurent Pinअक्षरt.
 *
 * TODO in order of priority:
 *      1) Rotation
 *      2) Cropping
 *      3) V4L2_CID_JPEG_ACTIVE_MARKER
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>


#घोषणा DRV_NAME "rcar_jpu"

/*
 * Align JPEG header end to cache line to make sure we will not have any issues
 * with cache; additionally to requerment (33.3.27 R01UH0501EJ0100 Rev.1.00)
 */
#घोषणा JPU_JPEG_HDR_SIZE		(ALIGN(0x258, L1_CACHE_BYTES))
#घोषणा JPU_JPEG_MAX_BYTES_PER_PIXEL	2	/* 16 bit precision क्रमmat */
#घोषणा JPU_JPEG_MIN_SIZE		25	/* SOI + SOF + EOI */
#घोषणा JPU_JPEG_QTBL_SIZE		0x40
#घोषणा JPU_JPEG_HDCTBL_SIZE		0x1c
#घोषणा JPU_JPEG_HACTBL_SIZE		0xb2
#घोषणा JPU_JPEG_HEIGHT_OFFSET		0x91
#घोषणा JPU_JPEG_WIDTH_OFFSET		0x93
#घोषणा JPU_JPEG_SUBS_OFFSET		0x97
#घोषणा JPU_JPEG_QTBL_LUM_OFFSET	0x07
#घोषणा JPU_JPEG_QTBL_CHR_OFFSET	0x4c
#घोषणा JPU_JPEG_HDCTBL_LUM_OFFSET	0xa4
#घोषणा JPU_JPEG_HACTBL_LUM_OFFSET	0xc5
#घोषणा JPU_JPEG_HDCTBL_CHR_OFFSET	0x17c
#घोषणा JPU_JPEG_HACTBL_CHR_OFFSET	0x19d
#घोषणा JPU_JPEG_PADDING_OFFSET		0x24f
#घोषणा JPU_JPEG_LUM 0x00
#घोषणा JPU_JPEG_CHR 0x01
#घोषणा JPU_JPEG_DC  0x00
#घोषणा JPU_JPEG_AC  0x10

#घोषणा JPU_JPEG_422 0x21
#घोषणा JPU_JPEG_420 0x22

#घोषणा JPU_JPEG_DEFAULT_422_PIX_FMT V4L2_PIX_FMT_NV16M
#घोषणा JPU_JPEG_DEFAULT_420_PIX_FMT V4L2_PIX_FMT_NV12M

/* JPEG markers */
#घोषणा TEM	0x01
#घोषणा SOF0	0xc0
#घोषणा RST	0xd0
#घोषणा SOI	0xd8
#घोषणा EOI	0xd9
#घोषणा DHP	0xde
#घोषणा DHT	0xc4
#घोषणा COM	0xfe
#घोषणा DQT	0xdb
#घोषणा DRI	0xdd
#घोषणा APP0	0xe0

#घोषणा JPU_RESET_TIMEOUT	100 /* ms */
#घोषणा JPU_JOB_TIMEOUT		300 /* ms */
#घोषणा JPU_MAX_QUALITY		4
#घोषणा JPU_WIDTH_MIN		16
#घोषणा JPU_HEIGHT_MIN		16
#घोषणा JPU_WIDTH_MAX		4096
#घोषणा JPU_HEIGHT_MAX		4096
#घोषणा JPU_MEMALIGN		8

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा JPU_FMT_TYPE_OUTPUT	0
#घोषणा JPU_FMT_TYPE_CAPTURE	1
#घोषणा JPU_ENC_CAPTURE		(1 << 0)
#घोषणा JPU_ENC_OUTPUT		(1 << 1)
#घोषणा JPU_DEC_CAPTURE		(1 << 2)
#घोषणा JPU_DEC_OUTPUT		(1 << 3)

/*
 * JPEG रेजिस्टरs and bits
 */

/* JPEG code mode रेजिस्टर */
#घोषणा JCMOD	0x00
#घोषणा JCMOD_PCTR		(1 << 7)
#घोषणा JCMOD_MSKIP_ENABLE	(1 << 5)
#घोषणा JCMOD_DSP_ENC		(0 << 3)
#घोषणा JCMOD_DSP_DEC		(1 << 3)
#घोषणा JCMOD_REDU		(7 << 0)
#घोषणा JCMOD_REDU_422		(1 << 0)
#घोषणा JCMOD_REDU_420		(2 << 0)

/* JPEG code command रेजिस्टर */
#घोषणा JCCMD	0x04
#घोषणा JCCMD_SRST	(1 << 12)
#घोषणा JCCMD_JEND	(1 << 2)
#घोषणा JCCMD_JSRT	(1 << 0)

/* JPEG code quantanization table number रेजिस्टर */
#घोषणा JCQTN	0x0c
#घोषणा JCQTN_SHIFT(t)		(((t) - 1) << 1)

/* JPEG code Huffman table number रेजिस्टर */
#घोषणा JCHTN	0x10
#घोषणा JCHTN_AC_SHIFT(t)	(((t) << 1) - 1)
#घोषणा JCHTN_DC_SHIFT(t)	(((t) - 1) << 1)

#घोषणा JCVSZU	0x1c /* JPEG code vertical size upper रेजिस्टर */
#घोषणा JCVSZD	0x20 /* JPEG code vertical size lower रेजिस्टर */
#घोषणा JCHSZU	0x24 /* JPEG code horizontal size upper रेजिस्टर */
#घोषणा JCHSZD	0x28 /* JPEG code horizontal size lower रेजिस्टर */
#घोषणा JCSZ_MASK 0xff /* JPEG code h/v size रेजिस्टर contains only 1 byte*/

#घोषणा JCDTCU	0x2c /* JPEG code data count upper रेजिस्टर */
#घोषणा JCDTCM	0x30 /* JPEG code data count middle रेजिस्टर */
#घोषणा JCDTCD	0x34 /* JPEG code data count lower रेजिस्टर */

/* JPEG पूर्णांकerrupt enable रेजिस्टर */
#घोषणा JINTE	0x38
#घोषणा JINTE_ERR		(7 << 5) /* INT5 + INT6 + INT7 */
#घोषणा JINTE_TRANSF_COMPL	(1 << 10)

/* JPEG पूर्णांकerrupt status रेजिस्टर */
#घोषणा JINTS	0x3c
#घोषणा JINTS_MASK	0x7c68
#घोषणा JINTS_ERR		(1 << 5)
#घोषणा JINTS_PROCESS_COMPL	(1 << 6)
#घोषणा JINTS_TRANSF_COMPL	(1 << 10)

#घोषणा JCDERR	0x40 /* JPEG code decode error रेजिस्टर */
#घोषणा JCDERR_MASK	0xf /* JPEG code decode error रेजिस्टर mask*/

/* JPEG पूर्णांकerface encoding */
#घोषणा JIFECNT	0x70
#घोषणा JIFECNT_INFT_422	0
#घोषणा JIFECNT_INFT_420	1
#घोषणा JIFECNT_SWAP_WB		(3 << 4) /* to JPU */

#घोषणा JIFESYA1	0x74	/* encode source Y address रेजिस्टर 1 */
#घोषणा JIFESCA1	0x78	/* encode source C address रेजिस्टर 1 */
#घोषणा JIFESYA2	0x7c	/* encode source Y address रेजिस्टर 2 */
#घोषणा JIFESCA2	0x80	/* encode source C address रेजिस्टर 2 */
#घोषणा JIFESMW		0x84	/* encode source memory width रेजिस्टर */
#घोषणा JIFESVSZ	0x88	/* encode source vertical size रेजिस्टर */
#घोषणा JIFESHSZ	0x8c	/* encode source horizontal size रेजिस्टर */
#घोषणा JIFEDA1		0x90	/* encode destination address रेजिस्टर 1 */
#घोषणा JIFEDA2		0x94	/* encode destination address रेजिस्टर 2 */

/* JPEG decoding control रेजिस्टर */
#घोषणा JIFDCNT	0xa0
#घोषणा JIFDCNT_SWAP_WB		(3 << 1) /* from JPU */

#घोषणा JIFDSA1		0xa4	/* decode source address रेजिस्टर 1 */
#घोषणा JIFDDMW		0xb0	/* decode destination  memory width रेजिस्टर */
#घोषणा JIFDDVSZ	0xb4	/* decode destination  vert. size रेजिस्टर */
#घोषणा JIFDDHSZ	0xb8	/* decode destination  horiz. size रेजिस्टर */
#घोषणा JIFDDYA1	0xbc	/* decode destination  Y address रेजिस्टर 1 */
#घोषणा JIFDDCA1	0xc0	/* decode destination  C address रेजिस्टर 1 */

#घोषणा JCQTBL(n)	(0x10000 + (n) * 0x40)	/* quantization tables regs */
#घोषणा JCHTBD(n)	(0x10100 + (n) * 0x100)	/* Huffman table DC regs */
#घोषणा JCHTBA(n)	(0x10120 + (n) * 0x100)	/* Huffman table AC regs */

/**
 * काष्ठा jpu - JPEG IP असलtraction
 * @mutex: the mutex protecting this काष्ठाure
 * @lock: spinlock protecting the device contexts
 * @v4l2_dev: v4l2 device क्रम mem2mem mode
 * @vfd_encoder: video device node क्रम encoder mem2mem mode
 * @vfd_decoder: video device node क्रम decoder mem2mem mode
 * @m2m_dev: v4l2 mem2mem device data
 * @curr: poपूर्णांकer to current context
 * @regs: JPEG IP रेजिस्टरs mapping
 * @irq: JPEG IP irq
 * @clk: JPEG IP घड़ी
 * @dev: JPEG IP काष्ठा device
 * @ref_count: reference counter
 */
काष्ठा jpu अणु
	काष्ठा mutex	mutex;
	spinlock_t	lock;
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd_encoder;
	काष्ठा video_device	vfd_decoder;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा jpu_ctx		*curr;

	व्योम __iomem		*regs;
	अचिन्हित पूर्णांक		irq;
	काष्ठा clk		*clk;
	काष्ठा device		*dev;
	पूर्णांक			ref_count;
पूर्ण;

/**
 * काष्ठा jpu_buffer - driver's specअगरic video buffer
 * @buf: m2m buffer
 * @compr_quality: destination image quality in compression mode
 * @subsampling: source image subsampling in decompression mode
 */
काष्ठा jpu_buffer अणु
	काष्ठा v4l2_m2m_buffer buf;
	अचिन्हित लघु	compr_quality;
	अचिन्हित अक्षर	subsampling;
पूर्ण;

/**
 * काष्ठा jpu_fmt - driver's पूर्णांकernal क्रमmat data
 * @fourcc: the fourcc code, 0 अगर not applicable
 * @colorspace: the colorspace specअगरier
 * @bpp: number of bits per pixel per plane
 * @h_align: horizontal alignment order (align to 2^h_align)
 * @v_align: vertical alignment order (align to 2^v_align)
 * @subsampling: (horizontal:4 | vertical:4) subsampling factor
 * @num_planes: number of planes
 * @types: types of queue this क्रमmat is applicable to
 */
काष्ठा jpu_fmt अणु
	u32 fourcc;
	u32 colorspace;
	u8 bpp[2];
	u8 h_align;
	u8 v_align;
	u8 subsampling;
	u8 num_planes;
	u16 types;
पूर्ण;

/**
 * काष्ठा jpu_q_data - parameters of one queue
 * @fmtinfo: driver-specअगरic क्रमmat of this queue
 * @क्रमmat: multiplanar क्रमmat of this queue
 * @sequence: sequence number
 */
काष्ठा jpu_q_data अणु
	काष्ठा jpu_fmt *fmtinfo;
	काष्ठा v4l2_pix_क्रमmat_mplane क्रमmat;
	अचिन्हित पूर्णांक sequence;
पूर्ण;

/**
 * काष्ठा jpu_ctx - the device context data
 * @jpu: JPEG IP device क्रम this context
 * @encoder: compression (encode) operation or decompression (decode)
 * @compr_quality: destination image quality in compression (encode) mode
 * @out_q: source (output) queue inक्रमmation
 * @cap_q: destination (capture) queue inक्रमmation
 * @fh: file handler
 * @ctrl_handler: controls handler
 */
काष्ठा jpu_ctx अणु
	काष्ठा jpu		*jpu;
	bool			encoder;
	अचिन्हित लघु		compr_quality;
	काष्ठा jpu_q_data	out_q;
	काष्ठा jpu_q_data	cap_q;
	काष्ठा v4l2_fh		fh;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
पूर्ण;

 /**
 * jpeg_buffer - description of memory containing input JPEG data
 * @end: end position in the buffer
 * @curr: current position in the buffer
 */
काष्ठा jpeg_buffer अणु
	व्योम *end;
	व्योम *curr;
पूर्ण;

अटल काष्ठा jpu_fmt jpu_क्रमmats[] = अणु
	अणु V4L2_PIX_FMT_JPEG, V4L2_COLORSPACE_JPEG,
	  अणु0, 0पूर्ण, 0, 0, 0, 1, JPU_ENC_CAPTURE | JPU_DEC_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_NV16M, V4L2_COLORSPACE_SRGB,
	  अणु8, 8पूर्ण, 2, 2, JPU_JPEG_422, 2, JPU_ENC_OUTPUT | JPU_DEC_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_NV12M, V4L2_COLORSPACE_SRGB,
	  अणु8, 4पूर्ण, 2, 2, JPU_JPEG_420, 2, JPU_ENC_OUTPUT | JPU_DEC_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_NV16, V4L2_COLORSPACE_SRGB,
	  अणु16, 0पूर्ण, 2, 2, JPU_JPEG_422, 1, JPU_ENC_OUTPUT | JPU_DEC_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_NV12, V4L2_COLORSPACE_SRGB,
	  अणु12, 0पूर्ण, 2, 2, JPU_JPEG_420, 1, JPU_ENC_OUTPUT | JPU_DEC_CAPTURE पूर्ण,
पूर्ण;

अटल स्थिर u8 zigzag[] = अणु
	0x03, 0x02, 0x0b, 0x13, 0x0a, 0x01, 0x00, 0x09,
	0x12, 0x1b, 0x23, 0x1a, 0x11, 0x08, 0x07, 0x06,
	0x0f, 0x10, 0x19, 0x22, 0x2b, 0x33, 0x2a, 0x21,
	0x18, 0x17, 0x0e, 0x05, 0x04, 0x0d, 0x16, 0x1f,
	0x20, 0x29, 0x32, 0x3b, 0x3a, 0x31, 0x28, 0x27,
	0x1e, 0x15, 0x0e, 0x14, 0x10, 0x26, 0x2f, 0x30,
	0x39, 0x38, 0x37, 0x2e, 0x25, 0x1c, 0x24, 0x2b,
	0x36, 0x3f, 0x3e, 0x35, 0x2c, 0x34, 0x3d, 0x3c
पूर्ण;

#घोषणा QTBL_SIZE (ALIGN(JPU_JPEG_QTBL_SIZE, \
			  माप(अचिन्हित पूर्णांक)) / माप(अचिन्हित पूर्णांक))
#घोषणा HDCTBL_SIZE (ALIGN(JPU_JPEG_HDCTBL_SIZE, \
			  माप(अचिन्हित पूर्णांक)) / माप(अचिन्हित पूर्णांक))
#घोषणा HACTBL_SIZE (ALIGN(JPU_JPEG_HACTBL_SIZE, \
			  माप(अचिन्हित पूर्णांक)) / माप(अचिन्हित पूर्णांक))
/*
 * Start of image; Quantization tables
 * SOF0 (17 bytes payload) is Baseline DCT - Sample precision, height, width,
 * Number of image components, (Ci:8 - Hi:4 - Vi:4 - Tq:8) * 3 - Y,Cb,Cr;
 * Huffman tables; Padding with 0xff (33.3.27 R01UH0501EJ0100 Rev.1.00)
 */
#घोषणा JPU_JPEG_HDR_BLOB अणु                                                    \
	0xff, SOI, 0xff, DQT, 0x00, JPU_JPEG_QTBL_SIZE + 0x3, JPU_JPEG_LUM,    \
	[JPU_JPEG_QTBL_LUM_OFFSET ...                                          \
		JPU_JPEG_QTBL_LUM_OFFSET + JPU_JPEG_QTBL_SIZE - 1] = 0x00,     \
	0xff, DQT, 0x00, JPU_JPEG_QTBL_SIZE + 0x3, JPU_JPEG_CHR,               \
	[JPU_JPEG_QTBL_CHR_OFFSET ... JPU_JPEG_QTBL_CHR_OFFSET +               \
		JPU_JPEG_QTBL_SIZE - 1] = 0x00, 0xff, SOF0, 0x00, 0x11, 0x08,  \
	[JPU_JPEG_HEIGHT_OFFSET ... JPU_JPEG_HEIGHT_OFFSET + 1] = 0x00,        \
	[JPU_JPEG_WIDTH_OFFSET ... JPU_JPEG_WIDTH_OFFSET + 1] = 0x00,          \
	0x03, 0x01, [JPU_JPEG_SUBS_OFFSET] = 0x00, JPU_JPEG_LUM,               \
	0x02, 0x11, JPU_JPEG_CHR, 0x03, 0x11, JPU_JPEG_CHR,                    \
	0xff, DHT, 0x00, JPU_JPEG_HDCTBL_SIZE + 0x3, JPU_JPEG_LUM|JPU_JPEG_DC, \
	[JPU_JPEG_HDCTBL_LUM_OFFSET ...                                        \
		JPU_JPEG_HDCTBL_LUM_OFFSET + JPU_JPEG_HDCTBL_SIZE - 1] = 0x00, \
	0xff, DHT, 0x00, JPU_JPEG_HACTBL_SIZE + 0x3, JPU_JPEG_LUM|JPU_JPEG_AC, \
	[JPU_JPEG_HACTBL_LUM_OFFSET ...                                        \
		JPU_JPEG_HACTBL_LUM_OFFSET + JPU_JPEG_HACTBL_SIZE - 1] = 0x00, \
	0xff, DHT, 0x00, JPU_JPEG_HDCTBL_SIZE + 0x3, JPU_JPEG_CHR|JPU_JPEG_DC, \
	[JPU_JPEG_HDCTBL_CHR_OFFSET ...                                        \
		JPU_JPEG_HDCTBL_CHR_OFFSET + JPU_JPEG_HDCTBL_SIZE - 1] = 0x00, \
	0xff, DHT, 0x00, JPU_JPEG_HACTBL_SIZE + 0x3, JPU_JPEG_CHR|JPU_JPEG_AC, \
	[JPU_JPEG_HACTBL_CHR_OFFSET ...                                        \
		JPU_JPEG_HACTBL_CHR_OFFSET + JPU_JPEG_HACTBL_SIZE - 1] = 0x00, \
	[JPU_JPEG_PADDING_OFFSET ... JPU_JPEG_HDR_SIZE - 1] = 0xff             \
पूर्ण

अटल अचिन्हित अक्षर jpeg_hdrs[JPU_MAX_QUALITY][JPU_JPEG_HDR_SIZE] = अणु
	[0 ... JPU_MAX_QUALITY - 1] = JPU_JPEG_HDR_BLOB
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक qtbl_lum[JPU_MAX_QUALITY][QTBL_SIZE] = अणु
	अणु
		0x14101927, 0x322e3e44, 0x10121726, 0x26354144,
		0x19171f26, 0x35414444, 0x27262635, 0x41444444,
		0x32263541, 0x44444444, 0x2e354144, 0x44444444,
		0x3e414444, 0x44444444, 0x44444444, 0x44444444
	पूर्ण,
	अणु
		0x100b0b10, 0x171b1f1e, 0x0b0c0c0f, 0x1417171e,
		0x0b0c0d10, 0x171a232f, 0x100f1017, 0x1a252f40,
		0x1714171a, 0x27334040, 0x1b171a25, 0x33404040,
		0x1f17232f, 0x40404040, 0x1e1e2f40, 0x40404040
	पूर्ण,
	अणु
		0x0c08080c, 0x11151817, 0x0809090b, 0x0f131217,
		0x08090a0c, 0x13141b24, 0x0c0b0c15, 0x141c2435,
		0x110f1314, 0x1e27333b, 0x1513141c, 0x27333b3b,
		0x18121b24, 0x333b3b3b, 0x17172435, 0x3b3b3b3b
	पूर्ण,
	अणु
		0x08060608, 0x0c0e1011, 0x06060608, 0x0a0d0c0f,
		0x06060708, 0x0d0e1218, 0x0808080e, 0x0d131823,
		0x0c0a0d0d, 0x141a2227, 0x0e0d0e13, 0x1a222727,
		0x100c1318, 0x22272727, 0x110f1823, 0x27272727
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक qtbl_chr[JPU_MAX_QUALITY][QTBL_SIZE] = अणु
	अणु
		0x15192026, 0x36444444, 0x191c1826, 0x36444444,
		0x2018202b, 0x42444444, 0x26262b35, 0x44444444,
		0x36424444, 0x44444444, 0x44444444, 0x44444444,
		0x44444444, 0x44444444, 0x44444444, 0x44444444
	पूर्ण,
	अणु
		0x110f1115, 0x141a2630, 0x0f131211, 0x141a232b,
		0x11121416, 0x1a1e2e35, 0x1511161c, 0x1e273540,
		0x14141a1e, 0x27304040, 0x1a1a1e27, 0x303f4040,
		0x26232e35, 0x40404040, 0x302b3540, 0x40404040
	पूर्ण,
	अणु
		0x0d0b0d10, 0x14141d25, 0x0b0e0e0e, 0x10141a20,
		0x0d0e0f11, 0x14172328, 0x100e1115, 0x171e2832,
		0x14101417, 0x1e25323b, 0x1414171e, 0x25303b3b,
		0x1d1a2328, 0x323b3b3b, 0x25202832, 0x3b3b3b3b
	पूर्ण,
	अणु
		0x0908090b, 0x0e111318, 0x080a090b, 0x0e0d1116,
		0x09090d0e, 0x0d0f171a, 0x0b0b0e0e, 0x0f141a21,
		0x0e0e0d0f, 0x14182127, 0x110d0f14, 0x18202727,
		0x1311171a, 0x21272727, 0x18161a21, 0x27272727
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hdctbl_lum[HDCTBL_SIZE] = अणु
	0x00010501, 0x01010101, 0x01000000, 0x00000000,
	0x00010203, 0x04050607, 0x08090a0b
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hdctbl_chr[HDCTBL_SIZE] = अणु
	0x00010501, 0x01010101, 0x01000000, 0x00000000,
	0x00010203, 0x04050607, 0x08090a0b
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hactbl_lum[HACTBL_SIZE] = अणु
	0x00020103, 0x03020403, 0x05050404, 0x0000017d, 0x01020300, 0x04110512,
	0x21314106, 0x13516107,	0x22711432, 0x8191a108, 0x2342b1c1, 0x1552d1f0,
	0x24336272, 0x82090a16, 0x1718191a, 0x25262728, 0x292a3435, 0x36373839,
	0x3a434445, 0x46474849, 0x4a535455, 0x56575859, 0x5a636465, 0x66676869,
	0x6a737475, 0x76777879, 0x7a838485, 0x86878889, 0x8a929394, 0x95969798,
	0x999aa2a3, 0xa4a5a6a7, 0xa8a9aab2, 0xb3b4b5b6, 0xb7b8b9ba, 0xc2c3c4c5,
	0xc6c7c8c9, 0xcad2d3d4, 0xd5d6d7d8, 0xd9dae1e2, 0xe3e4e5e6, 0xe7e8e9ea,
	0xf1f2f3f4, 0xf5f6f7f8, 0xf9fa0000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hactbl_chr[HACTBL_SIZE] = अणु
	0x00020103, 0x03020403, 0x05050404, 0x0000017d, 0x01020300, 0x04110512,
	0x21314106, 0x13516107,	0x22711432, 0x8191a108, 0x2342b1c1, 0x1552d1f0,
	0x24336272, 0x82090a16, 0x1718191a, 0x25262728, 0x292a3435, 0x36373839,
	0x3a434445, 0x46474849, 0x4a535455, 0x56575859, 0x5a636465, 0x66676869,
	0x6a737475, 0x76777879, 0x7a838485, 0x86878889, 0x8a929394, 0x95969798,
	0x999aa2a3, 0xa4a5a6a7, 0xa8a9aab2, 0xb3b4b5b6, 0xb7b8b9ba, 0xc2c3c4c5,
	0xc6c7c8c9, 0xcad2d3d4, 0xd5d6d7d8, 0xd9dae1e2, 0xe3e4e5e6, 0xe7e8e9ea,
	0xf1f2f3f4, 0xf5f6f7f8, 0xf9fa0000
पूर्ण;

अटल स्थिर अक्षर *error_to_text[16] = अणु
	"Normal",
	"SOI not detected",
	"SOF1 to SOFF detected",
	"Subsampling not detected",
	"SOF accuracy error",
	"DQT accuracy error",
	"Component error 1",
	"Component error 2",
	"SOF0, DQT, and DHT not detected when SOS detected",
	"SOS not detected",
	"EOI not detected",
	"Restart interval data number error detected",
	"Image size error",
	"Last MCU data number error",
	"Block data number error",
	"Unknown"
पूर्ण;

अटल काष्ठा jpu_buffer *vb2_to_jpu_buffer(काष्ठा vb2_v4l2_buffer *vb)
अणु
	काष्ठा v4l2_m2m_buffer *b =
		container_of(vb, काष्ठा v4l2_m2m_buffer, vb);

	वापस container_of(b, काष्ठा jpu_buffer, buf);
पूर्ण

अटल u32 jpu_पढ़ो(काष्ठा jpu *jpu, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(jpu->regs + reg);
पूर्ण

अटल व्योम jpu_ग_लिखो(काष्ठा jpu *jpu, u32 val, अचिन्हित पूर्णांक reg)
अणु
	ioग_लिखो32(val, jpu->regs + reg);
पूर्ण

अटल काष्ठा jpu_ctx *ctrl_to_ctx(काष्ठा v4l2_ctrl *c)
अणु
	वापस container_of(c->handler, काष्ठा jpu_ctx, ctrl_handler);
पूर्ण

अटल काष्ठा jpu_ctx *fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा jpu_ctx, fh);
पूर्ण

अटल व्योम jpu_set_tbl(काष्ठा jpu *jpu, u32 reg, स्थिर अचिन्हित पूर्णांक *tbl,
			अचिन्हित पूर्णांक len) अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		jpu_ग_लिखो(jpu, tbl[i], reg + (i << 2));
पूर्ण

अटल व्योम jpu_set_qtbl(काष्ठा jpu *jpu, अचिन्हित लघु quality)
अणु
	jpu_set_tbl(jpu, JCQTBL(0), qtbl_lum[quality], QTBL_SIZE);
	jpu_set_tbl(jpu, JCQTBL(1), qtbl_chr[quality], QTBL_SIZE);
पूर्ण

अटल व्योम jpu_set_htbl(काष्ठा jpu *jpu)
अणु
	jpu_set_tbl(jpu, JCHTBD(0), hdctbl_lum, HDCTBL_SIZE);
	jpu_set_tbl(jpu, JCHTBA(0), hactbl_lum, HACTBL_SIZE);
	jpu_set_tbl(jpu, JCHTBD(1), hdctbl_chr, HDCTBL_SIZE);
	jpu_set_tbl(jpu, JCHTBA(1), hactbl_chr, HACTBL_SIZE);
पूर्ण

अटल पूर्णांक jpu_रुको_reset(काष्ठा jpu *jpu)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(JPU_RESET_TIMEOUT);

	जबतक (jpu_पढ़ो(jpu, JCCMD) & JCCMD_SRST) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(jpu->dev, "timed out in reset\n");
			वापस -ETIMEDOUT;
		पूर्ण
		schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_reset(काष्ठा jpu *jpu)
अणु
	jpu_ग_लिखो(jpu, JCCMD_SRST, JCCMD);
	वापस jpu_रुको_reset(jpu);
पूर्ण

/*
 * ============================================================================
 * video ioctl operations
 * ============================================================================
 */
अटल व्योम put_qtbl(u8 *p, स्थिर u8 *qtbl)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(zigzag); i++)
		p[i] = *(qtbl + zigzag[i]);
पूर्ण

अटल व्योम put_htbl(u8 *p, स्थिर u8 *htbl, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < len; i += 4)
		क्रम (j = 0; j < 4 && (i + j) < len; ++j)
			p[i + j] = htbl[i + 3 - j];
पूर्ण

अटल व्योम jpu_generate_hdr(अचिन्हित लघु quality, अचिन्हित अक्षर *p)
अणु
	put_qtbl(p + JPU_JPEG_QTBL_LUM_OFFSET, (स्थिर u8 *)qtbl_lum[quality]);
	put_qtbl(p + JPU_JPEG_QTBL_CHR_OFFSET, (स्थिर u8 *)qtbl_chr[quality]);

	put_htbl(p + JPU_JPEG_HDCTBL_LUM_OFFSET, (स्थिर u8 *)hdctbl_lum,
		 JPU_JPEG_HDCTBL_SIZE);
	put_htbl(p + JPU_JPEG_HACTBL_LUM_OFFSET, (स्थिर u8 *)hactbl_lum,
		 JPU_JPEG_HACTBL_SIZE);

	put_htbl(p + JPU_JPEG_HDCTBL_CHR_OFFSET, (स्थिर u8 *)hdctbl_chr,
		 JPU_JPEG_HDCTBL_SIZE);
	put_htbl(p + JPU_JPEG_HACTBL_CHR_OFFSET, (स्थिर u8 *)hactbl_chr,
		 JPU_JPEG_HACTBL_SIZE);
पूर्ण

अटल पूर्णांक get_byte(काष्ठा jpeg_buffer *buf)
अणु
	अगर (buf->curr >= buf->end)
		वापस -1;

	वापस *(u8 *)buf->curr++;
पूर्ण

अटल पूर्णांक get_word_be(काष्ठा jpeg_buffer *buf, अचिन्हित पूर्णांक *word)
अणु
	अगर (buf->end - buf->curr < 2)
		वापस -1;

	*word = get_unaligned_be16(buf->curr);
	buf->curr += 2;

	वापस 0;
पूर्ण

अटल व्योम skip(काष्ठा jpeg_buffer *buf, अचिन्हित दीर्घ len)
अणु
	buf->curr += min((अचिन्हित दीर्घ)(buf->end - buf->curr), len);
पूर्ण

अटल u8 jpu_parse_hdr(व्योम *buffer, अचिन्हित दीर्घ size, अचिन्हित पूर्णांक *width,
			  अचिन्हित पूर्णांक *height)
अणु
	काष्ठा jpeg_buffer jpeg_buffer;
	अचिन्हित पूर्णांक word;
	bool soi = false;

	jpeg_buffer.end = buffer + size;
	jpeg_buffer.curr = buffer;

	/*
	 * basic size check and EOI - we करोn't want to let JPU cross
	 * buffer bounds in any हाल. Hope it's stopping by EOI.
	 */
	अगर (size < JPU_JPEG_MIN_SIZE || *(u8 *)(buffer + size - 1) != EOI)
		वापस 0;

	क्रम (;;) अणु
		पूर्णांक c;

		/* skip preceding filler bytes */
		करो
			c = get_byte(&jpeg_buffer);
		जबतक (c == 0xff || c == 0);

		अगर (!soi && c == SOI) अणु
			soi = true;
			जारी;
		पूर्ण अन्यथा अगर (soi != (c != SOI))
			वापस 0;

		चयन (c) अणु
		हाल SOF0: /* SOF0: baseline JPEG */
			skip(&jpeg_buffer, 3); /* segment length and bpp */
			अगर (get_word_be(&jpeg_buffer, height) ||
			    get_word_be(&jpeg_buffer, width) ||
			    get_byte(&jpeg_buffer) != 3) /* YCbCr only */
				वापस 0;

			skip(&jpeg_buffer, 1);
			वापस get_byte(&jpeg_buffer);
		हाल DHT:
		हाल DQT:
		हाल COM:
		हाल DRI:
		हाल APP0 ... APP0 + 0x0f:
			अगर (get_word_be(&jpeg_buffer, &word))
				वापस 0;
			skip(&jpeg_buffer, (दीर्घ)word - 2);
			अवरोध;
		हाल 0:
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_querycap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_capability *cap)
अणु
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->encoder)
		strscpy(cap->card, DRV_NAME " encoder", माप(cap->card));
	अन्यथा
		strscpy(cap->card, DRV_NAME " decoder", माप(cap->card));

	strscpy(cap->driver, DRV_NAME, माप(cap->driver));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(ctx->jpu->dev));
	स_रखो(cap->reserved, 0, माप(cap->reserved));

	वापस 0;
पूर्ण

अटल काष्ठा jpu_fmt *jpu_find_क्रमmat(bool encoder, u32 pixelक्रमmat,
				       अचिन्हित पूर्णांक fmt_type)
अणु
	अचिन्हित पूर्णांक i, fmt_flag;

	अगर (encoder)
		fmt_flag = fmt_type == JPU_FMT_TYPE_OUTPUT ? JPU_ENC_OUTPUT :
							     JPU_ENC_CAPTURE;
	अन्यथा
		fmt_flag = fmt_type == JPU_FMT_TYPE_OUTPUT ? JPU_DEC_OUTPUT :
							     JPU_DEC_CAPTURE;

	क्रम (i = 0; i < ARRAY_SIZE(jpu_क्रमmats); i++) अणु
		काष्ठा jpu_fmt *fmt = &jpu_क्रमmats[i];

		अगर (fmt->fourcc == pixelक्रमmat && fmt->types & fmt_flag)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक jpu_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	अचिन्हित पूर्णांक i, num = 0;

	क्रम (i = 0; i < ARRAY_SIZE(jpu_क्रमmats); ++i) अणु
		अगर (jpu_क्रमmats[i].types & type) अणु
			अगर (num == f->index)
				अवरोध;
			++num;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(jpu_क्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = jpu_क्रमmats[i].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_क्रमागत_fmt_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);

	वापस jpu_क्रमागत_fmt(f, ctx->encoder ? JPU_ENC_CAPTURE :
			    JPU_DEC_CAPTURE);
पूर्ण

अटल पूर्णांक jpu_क्रमागत_fmt_out(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);

	वापस jpu_क्रमागत_fmt(f, ctx->encoder ? JPU_ENC_OUTPUT : JPU_DEC_OUTPUT);
पूर्ण

अटल काष्ठा jpu_q_data *jpu_get_q_data(काष्ठा jpu_ctx *ctx,
					 क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->out_q;
	अन्यथा
		वापस &ctx->cap_q;
पूर्ण

अटल व्योम jpu_bound_align_image(u32 *w, अचिन्हित पूर्णांक w_min,
				  अचिन्हित पूर्णांक w_max, अचिन्हित पूर्णांक w_align,
				  u32 *h, अचिन्हित पूर्णांक h_min,
				  अचिन्हित पूर्णांक h_max, अचिन्हित पूर्णांक h_align)
अणु
	अचिन्हित पूर्णांक width, height, w_step, h_step;

	width = *w;
	height = *h;

	w_step = 1U << w_align;
	h_step = 1U << h_align;
	v4l_bound_align_image(w, w_min, w_max, w_align, h, h_min, h_max,
			      h_align, 3);

	अगर (*w < width && *w + w_step < w_max)
		*w += w_step;
	अगर (*h < height && *h + h_step < h_max)
		*h += h_step;
पूर्ण

अटल पूर्णांक __jpu_try_fmt(काष्ठा jpu_ctx *ctx, काष्ठा jpu_fmt **fmtinfo,
			 काष्ठा v4l2_pix_क्रमmat_mplane *pix,
			 क्रमागत v4l2_buf_type type)
अणु
	काष्ठा jpu_fmt *fmt;
	अचिन्हित पूर्णांक f_type, w, h;

	f_type = V4L2_TYPE_IS_OUTPUT(type) ? JPU_FMT_TYPE_OUTPUT :
						JPU_FMT_TYPE_CAPTURE;

	fmt = jpu_find_क्रमmat(ctx->encoder, pix->pixelक्रमmat, f_type);
	अगर (!fmt) अणु
		अचिन्हित पूर्णांक pixelक्रमmat;

		dev_dbg(ctx->jpu->dev, "unknown format; set default format\n");
		अगर (ctx->encoder)
			pixelक्रमmat = f_type == JPU_FMT_TYPE_OUTPUT ?
				V4L2_PIX_FMT_NV16M : V4L2_PIX_FMT_JPEG;
		अन्यथा
			pixelक्रमmat = f_type == JPU_FMT_TYPE_CAPTURE ?
				V4L2_PIX_FMT_NV16M : V4L2_PIX_FMT_JPEG;
		fmt = jpu_find_क्रमmat(ctx->encoder, pixelक्रमmat, f_type);
	पूर्ण

	pix->pixelक्रमmat = fmt->fourcc;
	pix->colorspace = fmt->colorspace;
	pix->field = V4L2_FIELD_NONE;
	pix->num_planes = fmt->num_planes;

	jpu_bound_align_image(&pix->width, JPU_WIDTH_MIN, JPU_WIDTH_MAX,
			      fmt->h_align, &pix->height, JPU_HEIGHT_MIN,
			      JPU_HEIGHT_MAX, fmt->v_align);

	w = pix->width;
	h = pix->height;

	अगर (fmt->fourcc == V4L2_PIX_FMT_JPEG) अणु
		/* ignore userspaces's sizeimage क्रम encoding */
		अगर (pix->plane_fmt[0].sizeimage <= 0 || ctx->encoder)
			pix->plane_fmt[0].sizeimage = JPU_JPEG_HDR_SIZE +
				(JPU_JPEG_MAX_BYTES_PER_PIXEL * w * h);
		pix->plane_fmt[0].bytesperline = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i, bpl = 0;

		क्रम (i = 0; i < pix->num_planes; ++i)
			bpl = max(bpl, pix->plane_fmt[i].bytesperline);

		bpl = clamp_t(अचिन्हित पूर्णांक, bpl, w, JPU_WIDTH_MAX);
		bpl = round_up(bpl, JPU_MEMALIGN);

		क्रम (i = 0; i < pix->num_planes; ++i) अणु
			pix->plane_fmt[i].bytesperline = bpl;
			pix->plane_fmt[i].sizeimage = bpl * h * fmt->bpp[i] / 8;
		पूर्ण
	पूर्ण

	अगर (fmtinfo)
		*fmtinfo = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_try_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);

	अगर (!v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type))
		वापस -EINVAL;

	वापस __jpu_try_fmt(ctx, शून्य, &f->fmt.pix_mp, f->type);
पूर्ण

अटल पूर्णांक jpu_s_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	काष्ठा jpu_fmt *fmtinfo;
	काष्ठा jpu_q_data *q_data;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ctx->jpu->v4l2_dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	ret = __jpu_try_fmt(ctx, &fmtinfo, &f->fmt.pix_mp, f->type);
	अगर (ret < 0)
		वापस ret;

	q_data = jpu_get_q_data(ctx, f->type);

	q_data->क्रमmat = f->fmt.pix_mp;
	q_data->fmtinfo = fmtinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा jpu_q_data *q_data;
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);

	अगर (!v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type))
		वापस -EINVAL;

	q_data = jpu_get_q_data(ctx, f->type);
	f->fmt.pix_mp = q_data->क्रमmat;

	वापस 0;
पूर्ण

/*
 * V4L2 controls
 */
अटल पूर्णांक jpu_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा jpu_ctx *ctx = ctrl_to_ctx(ctrl);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->jpu->lock, flags);
	अगर (ctrl->id == V4L2_CID_JPEG_COMPRESSION_QUALITY)
		ctx->compr_quality = ctrl->val;
	spin_unlock_irqrestore(&ctx->jpu->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops jpu_ctrl_ops = अणु
	.s_ctrl		= jpu_s_ctrl,
पूर्ण;

अटल पूर्णांक jpu_streamon(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा jpu_ctx *ctx = fh_to_ctx(priv);
	काष्ठा jpu_q_data *src_q_data, *dst_q_data, *orig, adj, *ref;
	क्रमागत v4l2_buf_type adj_type;

	src_q_data = jpu_get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	dst_q_data = jpu_get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);

	अगर (ctx->encoder) अणु
		adj = *src_q_data;
		orig = src_q_data;
		ref = dst_q_data;
		adj_type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	पूर्ण अन्यथा अणु
		adj = *dst_q_data;
		orig = dst_q_data;
		ref = src_q_data;
		adj_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	पूर्ण

	adj.क्रमmat.width = ref->क्रमmat.width;
	adj.क्रमmat.height = ref->क्रमmat.height;

	__jpu_try_fmt(ctx, शून्य, &adj.क्रमmat, adj_type);

	अगर (adj.क्रमmat.width != orig->क्रमmat.width ||
	    adj.क्रमmat.height != orig->क्रमmat.height) अणु
		dev_err(ctx->jpu->dev, "src and dst formats do not match.\n");
		/* maybe we can वापस -EPIPE here? */
		वापस -EINVAL;
	पूर्ण

	वापस v4l2_m2m_streamon(file, ctx->fh.m2m_ctx, type);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops jpu_ioctl_ops = अणु
	.vidioc_querycap		= jpu_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= jpu_क्रमागत_fmt_cap,
	.vidioc_क्रमागत_fmt_vid_out	= jpu_क्रमागत_fmt_out,
	.vidioc_g_fmt_vid_cap_mplane	= jpu_g_fmt,
	.vidioc_g_fmt_vid_out_mplane	= jpu_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= jpu_try_fmt,
	.vidioc_try_fmt_vid_out_mplane	= jpu_try_fmt,
	.vidioc_s_fmt_vid_cap_mplane	= jpu_s_fmt,
	.vidioc_s_fmt_vid_out_mplane	= jpu_s_fmt,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_create_bufs             = v4l2_m2m_ioctl_create_bufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon		= jpu_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe
पूर्ण;

अटल पूर्णांक jpu_controls_create(काष्ठा jpu_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 1);

	ctrl = v4l2_ctrl_new_std(&ctx->ctrl_handler, &jpu_ctrl_ops,
				 V4L2_CID_JPEG_COMPRESSION_QUALITY,
				 0, JPU_MAX_QUALITY - 1, 1, 0);

	अगर (ctx->ctrl_handler.error) अणु
		ret = ctx->ctrl_handler.error;
		जाओ error_मुक्त;
	पूर्ण

	अगर (!ctx->encoder)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE |
				V4L2_CTRL_FLAG_READ_ONLY;

	ret = v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	अगर (ret < 0)
		जाओ error_मुक्त;

	वापस 0;

error_मुक्त:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	वापस ret;
पूर्ण

/*
 * ============================================================================
 * Queue operations
 * ============================================================================
 */
अटल पूर्णांक jpu_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा jpu_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा jpu_q_data *q_data;
	अचिन्हित पूर्णांक i;

	q_data = jpu_get_q_data(ctx, vq->type);

	अगर (*nplanes) अणु
		अगर (*nplanes != q_data->क्रमmat.num_planes)
			वापस -EINVAL;

		क्रम (i = 0; i < *nplanes; i++) अणु
			अचिन्हित पूर्णांक q_size = q_data->क्रमmat.plane_fmt[i].sizeimage;

			अगर (sizes[i] < q_size)
				वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	*nplanes = q_data->क्रमmat.num_planes;

	क्रम (i = 0; i < *nplanes; i++)
		sizes[i] = q_data->क्रमmat.plane_fmt[i].sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा jpu_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा jpu_q_data *q_data;
	अचिन्हित पूर्णांक i;

	q_data = jpu_get_q_data(ctx, vb->vb2_queue->type);

	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			dev_err(ctx->jpu->dev, "%s field isn't supported\n",
					__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < q_data->क्रमmat.num_planes; i++) अणु
		अचिन्हित दीर्घ size = q_data->क्रमmat.plane_fmt[i].sizeimage;

		अगर (vb2_plane_size(vb, i) < size) अणु
			dev_err(ctx->jpu->dev,
				"%s: data will not fit into plane (%lu < %lu)\n",
			       __func__, vb2_plane_size(vb, i), size);
			वापस -EINVAL;
		पूर्ण

		/* decoder capture queue */
		अगर (!ctx->encoder && V4L2_TYPE_IS_CAPTURE(vb->vb2_queue->type))
			vb2_set_plane_payload(vb, i, size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम jpu_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा jpu_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	अगर (!ctx->encoder && V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		काष्ठा jpu_buffer *jpu_buf = vb2_to_jpu_buffer(vbuf);
		काष्ठा jpu_q_data *q_data, adjust;
		व्योम *buffer = vb2_plane_vaddr(vb, 0);
		अचिन्हित दीर्घ buf_size = vb2_get_plane_payload(vb, 0);
		अचिन्हित पूर्णांक width, height;

		u8 subsampling = jpu_parse_hdr(buffer, buf_size, &width,
						 &height);

		/* check अगर JPEG data basic parsing was successful */
		अगर (subsampling != JPU_JPEG_422 && subsampling != JPU_JPEG_420)
			जाओ क्रमmat_error;

		q_data = &ctx->out_q;

		adjust = *q_data;
		adjust.क्रमmat.width = width;
		adjust.क्रमmat.height = height;

		__jpu_try_fmt(ctx, &adjust.fmtinfo, &adjust.क्रमmat,
			      V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);

		अगर (adjust.क्रमmat.width != q_data->क्रमmat.width ||
		    adjust.क्रमmat.height != q_data->क्रमmat.height)
			जाओ क्रमmat_error;

		/*
		 * keep subsampling in buffer to check it
		 * क्रम compatibility in device_run
		 */
		jpu_buf->subsampling = subsampling;
	पूर्ण

	अगर (ctx->fh.m2m_ctx)
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);

	वापस;

क्रमmat_error:
	dev_err(ctx->jpu->dev, "incompatible or corrupted JPEG data\n");
	vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
पूर्ण

अटल व्योम jpu_buf_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा jpu_buffer *jpu_buf = vb2_to_jpu_buffer(vbuf);
	काष्ठा jpu_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा jpu_q_data *q_data = &ctx->out_q;
	क्रमागत v4l2_buf_type type = vb->vb2_queue->type;
	u8 *buffer;

	अगर (vb->state == VB2_BUF_STATE_DONE)
		vbuf->sequence = jpu_get_q_data(ctx, type)->sequence++;

	अगर (!ctx->encoder || vb->state != VB2_BUF_STATE_DONE ||
	    V4L2_TYPE_IS_OUTPUT(type))
		वापस;

	buffer = vb2_plane_vaddr(vb, 0);

	स_नकल(buffer, jpeg_hdrs[jpu_buf->compr_quality], JPU_JPEG_HDR_SIZE);
	*(__be16 *)(buffer + JPU_JPEG_HEIGHT_OFFSET) =
					cpu_to_be16(q_data->क्रमmat.height);
	*(__be16 *)(buffer + JPU_JPEG_WIDTH_OFFSET) =
					cpu_to_be16(q_data->क्रमmat.width);
	*(buffer + JPU_JPEG_SUBS_OFFSET) = q_data->fmtinfo->subsampling;
पूर्ण

अटल पूर्णांक jpu_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित count)
अणु
	काष्ठा jpu_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा jpu_q_data *q_data = jpu_get_q_data(ctx, vq->type);

	q_data->sequence = 0;
	वापस 0;
पूर्ण

अटल व्योम jpu_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा jpu_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vb;
	अचिन्हित दीर्घ flags;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			vb = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vb = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (vb == शून्य)
			वापस;
		spin_lock_irqsave(&ctx->jpu->lock, flags);
		v4l2_m2m_buf_करोne(vb, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&ctx->jpu->lock, flags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops jpu_qops = अणु
	.queue_setup		= jpu_queue_setup,
	.buf_prepare		= jpu_buf_prepare,
	.buf_queue		= jpu_buf_queue,
	.buf_finish		= jpu_buf_finish,
	.start_streaming	= jpu_start_streaming,
	.stop_streaming		= jpu_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक jpu_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा jpu_ctx *ctx = priv;
	पूर्णांक ret;

	स_रखो(src_vq, 0, माप(*src_vq));
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा jpu_buffer);
	src_vq->ops = &jpu_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->jpu->mutex;
	src_vq->dev = ctx->jpu->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	स_रखो(dst_vq, 0, माप(*dst_vq));
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा jpu_buffer);
	dst_vq->ops = &jpu_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->jpu->mutex;
	dst_vq->dev = ctx->jpu->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

/*
 * ============================================================================
 * Device file operations
 * ============================================================================
 */
अटल पूर्णांक jpu_खोलो(काष्ठा file *file)
अणु
	काष्ठा jpu *jpu = video_drvdata(file);
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा jpu_ctx *ctx;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	v4l2_fh_init(&ctx->fh, vfd);
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->jpu = jpu;
	ctx->encoder = vfd == &jpu->vfd_encoder;

	__jpu_try_fmt(ctx, &ctx->out_q.fmtinfo, &ctx->out_q.क्रमmat,
		      V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	__jpu_try_fmt(ctx, &ctx->cap_q.fmtinfo, &ctx->cap_q.क्रमmat,
		      V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(jpu->m2m_dev, ctx, jpu_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ v4l_prepare_rollback;
	पूर्ण

	ret = jpu_controls_create(ctx);
	अगर (ret < 0)
		जाओ v4l_prepare_rollback;

	अगर (mutex_lock_पूर्णांकerruptible(&jpu->mutex)) अणु
		ret = -ERESTARTSYS;
		जाओ v4l_prepare_rollback;
	पूर्ण

	अगर (jpu->ref_count == 0) अणु
		ret = clk_prepare_enable(jpu->clk);
		अगर (ret < 0)
			जाओ device_prepare_rollback;
		/* ...issue software reset */
		ret = jpu_reset(jpu);
		अगर (ret)
			जाओ jpu_reset_rollback;
	पूर्ण

	jpu->ref_count++;

	mutex_unlock(&jpu->mutex);
	वापस 0;

jpu_reset_rollback:
	clk_disable_unprepare(jpu->clk);
device_prepare_rollback:
	mutex_unlock(&jpu->mutex);
v4l_prepare_rollback:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक jpu_release(काष्ठा file *file)
अणु
	काष्ठा jpu *jpu = video_drvdata(file);
	काष्ठा jpu_ctx *ctx = fh_to_ctx(file->निजी_data);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);

	mutex_lock(&jpu->mutex);
	अगर (--jpu->ref_count == 0)
		clk_disable_unprepare(jpu->clk);
	mutex_unlock(&jpu->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations jpu_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= jpu_खोलो,
	.release	= jpu_release,
	.unlocked_ioctl	= video_ioctl2,
	.poll		= v4l2_m2m_fop_poll,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

/*
 * ============================================================================
 * mem2mem callbacks
 * ============================================================================
 */
अटल व्योम jpu_cleanup(काष्ठा jpu_ctx *ctx, bool reset)
अणु
	/* हटाओ current buffers and finish job */
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->jpu->lock, flags);

	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);

	/* ...and give it a chance on next run */
	अगर (reset)
		jpu_ग_लिखो(ctx->jpu, JCCMD_SRST, JCCMD);

	spin_unlock_irqrestore(&ctx->jpu->lock, flags);

	v4l2_m2m_job_finish(ctx->jpu->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम jpu_device_run(व्योम *priv)
अणु
	काष्ठा jpu_ctx *ctx = priv;
	काष्ठा jpu *jpu = ctx->jpu;
	काष्ठा jpu_buffer *jpu_buf;
	काष्ठा jpu_q_data *q_data;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित पूर्णांक w, h, bpl;
	अचिन्हित अक्षर num_planes, subsampling;
	अचिन्हित दीर्घ flags;

	/* ...रुको until module reset completes; we have mutex locked here */
	अगर (jpu_रुको_reset(jpu)) अणु
		jpu_cleanup(ctx, true);
		वापस;
	पूर्ण

	spin_lock_irqsave(&ctx->jpu->lock, flags);

	jpu->curr = ctx;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	अगर (ctx->encoder) अणु
		jpu_buf = vb2_to_jpu_buffer(dst_buf);
		q_data = &ctx->out_q;
	पूर्ण अन्यथा अणु
		jpu_buf = vb2_to_jpu_buffer(src_buf);
		q_data = &ctx->cap_q;
	पूर्ण

	w = q_data->क्रमmat.width;
	h = q_data->क्रमmat.height;
	bpl = q_data->क्रमmat.plane_fmt[0].bytesperline;
	num_planes = q_data->fmtinfo->num_planes;
	subsampling = q_data->fmtinfo->subsampling;

	अगर (ctx->encoder) अणु
		अचिन्हित दीर्घ src_1_addr, src_2_addr, dst_addr;
		अचिन्हित पूर्णांक redu, inft;

		dst_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
		src_1_addr =
			vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
		अगर (num_planes > 1)
			src_2_addr = vb2_dma_contig_plane_dma_addr(
					&src_buf->vb2_buf, 1);
		अन्यथा
			src_2_addr = src_1_addr + w * h;

		jpu_buf->compr_quality = ctx->compr_quality;

		अगर (subsampling == JPU_JPEG_420) अणु
			redu = JCMOD_REDU_420;
			inft = JIFECNT_INFT_420;
		पूर्ण अन्यथा अणु
			redu = JCMOD_REDU_422;
			inft = JIFECNT_INFT_422;
		पूर्ण

		/* only no marker mode works क्रम encoding */
		jpu_ग_लिखो(jpu, JCMOD_DSP_ENC | JCMOD_PCTR | redu |
			  JCMOD_MSKIP_ENABLE, JCMOD);

		jpu_ग_लिखो(jpu, JIFECNT_SWAP_WB | inft, JIFECNT);
		jpu_ग_लिखो(jpu, JIFDCNT_SWAP_WB, JIFDCNT);
		jpu_ग_लिखो(jpu, JINTE_TRANSF_COMPL, JINTE);

		/* Y and C components source addresses */
		jpu_ग_लिखो(jpu, src_1_addr, JIFESYA1);
		jpu_ग_लिखो(jpu, src_2_addr, JIFESCA1);

		/* memory width */
		jpu_ग_लिखो(jpu, bpl, JIFESMW);

		jpu_ग_लिखो(jpu, (w >> 8) & JCSZ_MASK, JCHSZU);
		jpu_ग_लिखो(jpu, w & JCSZ_MASK, JCHSZD);

		jpu_ग_लिखो(jpu, (h >> 8) & JCSZ_MASK, JCVSZU);
		jpu_ग_लिखो(jpu, h & JCSZ_MASK, JCVSZD);

		jpu_ग_लिखो(jpu, w, JIFESHSZ);
		jpu_ग_लिखो(jpu, h, JIFESVSZ);

		jpu_ग_लिखो(jpu, dst_addr + JPU_JPEG_HDR_SIZE, JIFEDA1);

		jpu_ग_लिखो(jpu, 0 << JCQTN_SHIFT(1) | 1 << JCQTN_SHIFT(2) |
			  1 << JCQTN_SHIFT(3), JCQTN);

		jpu_ग_लिखो(jpu, 0 << JCHTN_AC_SHIFT(1) | 0 << JCHTN_DC_SHIFT(1) |
			  1 << JCHTN_AC_SHIFT(2) | 1 << JCHTN_DC_SHIFT(2) |
			  1 << JCHTN_AC_SHIFT(3) | 1 << JCHTN_DC_SHIFT(3),
			  JCHTN);

		jpu_set_qtbl(jpu, ctx->compr_quality);
		jpu_set_htbl(jpu);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ src_addr, dst_1_addr, dst_2_addr;

		अगर (jpu_buf->subsampling != subsampling) अणु
			dev_err(ctx->jpu->dev,
				"src and dst formats do not match.\n");
			spin_unlock_irqrestore(&ctx->jpu->lock, flags);
			jpu_cleanup(ctx, false);
			वापस;
		पूर्ण

		src_addr = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
		dst_1_addr =
			vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
		अगर (q_data->fmtinfo->num_planes > 1)
			dst_2_addr = vb2_dma_contig_plane_dma_addr(
					&dst_buf->vb2_buf, 1);
		अन्यथा
			dst_2_addr = dst_1_addr + w * h;

		/* ...set up decoder operation */
		jpu_ग_लिखो(jpu, JCMOD_DSP_DEC | JCMOD_PCTR, JCMOD);
		jpu_ग_लिखो(jpu, JIFECNT_SWAP_WB, JIFECNT);
		jpu_ग_लिखो(jpu, JIFDCNT_SWAP_WB, JIFDCNT);

		/* ...enable पूर्णांकerrupts on transfer completion and d-g error */
		jpu_ग_लिखो(jpu, JINTE_TRANSF_COMPL | JINTE_ERR, JINTE);

		/* ...set source/destination addresses of encoded data */
		jpu_ग_लिखो(jpu, src_addr, JIFDSA1);
		jpu_ग_लिखो(jpu, dst_1_addr, JIFDDYA1);
		jpu_ग_लिखो(jpu, dst_2_addr, JIFDDCA1);

		jpu_ग_लिखो(jpu, bpl, JIFDDMW);
	पूर्ण

	/* ...start encoder/decoder operation */
	jpu_ग_लिखो(jpu, JCCMD_JSRT, JCCMD);

	spin_unlock_irqrestore(&ctx->jpu->lock, flags);
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops jpu_m2m_ops = अणु
	.device_run	= jpu_device_run,
पूर्ण;

/*
 * ============================================================================
 * IRQ handler
 * ============================================================================
 */
अटल irqवापस_t jpu_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा jpu *jpu = dev_id;
	काष्ठा jpu_ctx *curr_ctx;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित पूर्णांक पूर्णांक_status;

	पूर्णांक_status = jpu_पढ़ो(jpu, JINTS);

	/* ...spurious पूर्णांकerrupt */
	अगर (!((JINTS_TRANSF_COMPL | JINTS_PROCESS_COMPL | JINTS_ERR) &
	    पूर्णांक_status))
		वापस IRQ_NONE;

	/* ...clear पूर्णांकerrupts */
	jpu_ग_लिखो(jpu, ~(पूर्णांक_status & JINTS_MASK), JINTS);
	अगर (पूर्णांक_status & (JINTS_ERR | JINTS_PROCESS_COMPL))
		jpu_ग_लिखो(jpu, JCCMD_JEND, JCCMD);

	spin_lock(&jpu->lock);

	अगर ((पूर्णांक_status & JINTS_PROCESS_COMPL) &&
	   !(पूर्णांक_status & JINTS_TRANSF_COMPL))
		जाओ handled;

	curr_ctx = v4l2_m2m_get_curr_priv(jpu->m2m_dev);
	अगर (!curr_ctx) अणु
		/* ...instance is not running */
		dev_err(jpu->dev, "no active context for m2m\n");
		जाओ handled;
	पूर्ण

	src_buf = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	अगर (पूर्णांक_status & JINTS_TRANSF_COMPL) अणु
		अगर (curr_ctx->encoder) अणु
			अचिन्हित दीर्घ payload_size = jpu_पढ़ो(jpu, JCDTCU) << 16
						   | jpu_पढ़ो(jpu, JCDTCM) << 8
						   | jpu_पढ़ो(jpu, JCDTCD);
			vb2_set_plane_payload(&dst_buf->vb2_buf, 0,
				payload_size + JPU_JPEG_HDR_SIZE);
		पूर्ण

		dst_buf->field = src_buf->field;
		dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;
		अगर (src_buf->flags & V4L2_BUF_FLAG_TIMECODE)
			dst_buf->समयcode = src_buf->समयcode;
		dst_buf->flags = src_buf->flags &
			(V4L2_BUF_FLAG_TIMECODE | V4L2_BUF_FLAG_KEYFRAME |
			 V4L2_BUF_FLAG_PFRAME | V4L2_BUF_FLAG_BFRAME |
			 V4L2_BUF_FLAG_TSTAMP_SRC_MASK);

		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);
	पूर्ण अन्यथा अगर (पूर्णांक_status & JINTS_ERR) अणु
		अचिन्हित अक्षर error = jpu_पढ़ो(jpu, JCDERR) & JCDERR_MASK;

		dev_dbg(jpu->dev, "processing error: %#X: %s\n", error,
			error_to_text[error]);

		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	jpu->curr = शून्य;

	/* ...reset JPU after completion */
	jpu_ग_लिखो(jpu, JCCMD_SRST, JCCMD);
	spin_unlock(&jpu->lock);

	v4l2_m2m_job_finish(jpu->m2m_dev, curr_ctx->fh.m2m_ctx);

	वापस IRQ_HANDLED;

handled:
	spin_unlock(&jpu->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * ============================================================================
 * Driver basic infraकाष्ठाure
 * ============================================================================
 */
अटल स्थिर काष्ठा of_device_id jpu_dt_ids[] = अणु
	अणु .compatible = "renesas,jpu-r8a7790" पूर्ण, /* H2 */
	अणु .compatible = "renesas,jpu-r8a7791" पूर्ण, /* M2-W */
	अणु .compatible = "renesas,jpu-r8a7792" पूर्ण, /* V2H */
	अणु .compatible = "renesas,jpu-r8a7793" पूर्ण, /* M2-N */
	अणु .compatible = "renesas,rcar-gen2-jpu" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jpu_dt_ids);

अटल पूर्णांक jpu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jpu *jpu;
	काष्ठा resource *res;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	jpu = devm_kzalloc(&pdev->dev, माप(*jpu), GFP_KERNEL);
	अगर (!jpu)
		वापस -ENOMEM;

	mutex_init(&jpu->mutex);
	spin_lock_init(&jpu->lock);
	jpu->dev = &pdev->dev;

	/* memory-mapped रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	jpu->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(jpu->regs))
		वापस PTR_ERR(jpu->regs);

	/* पूर्णांकerrupt service routine registration */
	jpu->irq = ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot find IRQ\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, jpu->irq, jpu_irq_handler, 0,
			       dev_name(&pdev->dev), jpu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", jpu->irq);
		वापस ret;
	पूर्ण

	/* घड़ीs */
	jpu->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(jpu->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(jpu->clk);
	पूर्ण

	/* v4l2 device */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &jpu->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		वापस ret;
	पूर्ण

	/* mem2mem device */
	jpu->m2m_dev = v4l2_m2m_init(&jpu_m2m_ops);
	अगर (IS_ERR(jpu->m2m_dev)) अणु
		v4l2_err(&jpu->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(jpu->m2m_dev);
		जाओ device_रेजिस्टर_rollback;
	पूर्ण

	/* fill in qantization and Huffman tables क्रम encoder */
	क्रम (i = 0; i < JPU_MAX_QUALITY; i++)
		jpu_generate_hdr(i, (अचिन्हित अक्षर *)jpeg_hdrs[i]);

	strscpy(jpu->vfd_encoder.name, DRV_NAME, माप(jpu->vfd_encoder.name));
	jpu->vfd_encoder.fops		= &jpu_fops;
	jpu->vfd_encoder.ioctl_ops	= &jpu_ioctl_ops;
	jpu->vfd_encoder.minor		= -1;
	jpu->vfd_encoder.release	= video_device_release_empty;
	jpu->vfd_encoder.lock		= &jpu->mutex;
	jpu->vfd_encoder.v4l2_dev	= &jpu->v4l2_dev;
	jpu->vfd_encoder.vfl_dir	= VFL_सूची_M2M;
	jpu->vfd_encoder.device_caps	= V4L2_CAP_STREAMING |
					  V4L2_CAP_VIDEO_M2M_MPLANE;

	ret = video_रेजिस्टर_device(&jpu->vfd_encoder, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&jpu->v4l2_dev, "Failed to register video device\n");
		जाओ m2m_init_rollback;
	पूर्ण

	video_set_drvdata(&jpu->vfd_encoder, jpu);

	strscpy(jpu->vfd_decoder.name, DRV_NAME, माप(jpu->vfd_decoder.name));
	jpu->vfd_decoder.fops		= &jpu_fops;
	jpu->vfd_decoder.ioctl_ops	= &jpu_ioctl_ops;
	jpu->vfd_decoder.minor		= -1;
	jpu->vfd_decoder.release	= video_device_release_empty;
	jpu->vfd_decoder.lock		= &jpu->mutex;
	jpu->vfd_decoder.v4l2_dev	= &jpu->v4l2_dev;
	jpu->vfd_decoder.vfl_dir	= VFL_सूची_M2M;
	jpu->vfd_decoder.device_caps	= V4L2_CAP_STREAMING |
					  V4L2_CAP_VIDEO_M2M_MPLANE;

	ret = video_रेजिस्टर_device(&jpu->vfd_decoder, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&jpu->v4l2_dev, "Failed to register video device\n");
		जाओ enc_vdev_रेजिस्टर_rollback;
	पूर्ण

	video_set_drvdata(&jpu->vfd_decoder, jpu);
	platक्रमm_set_drvdata(pdev, jpu);

	v4l2_info(&jpu->v4l2_dev, "encoder device registered as /dev/video%d\n",
		  jpu->vfd_encoder.num);
	v4l2_info(&jpu->v4l2_dev, "decoder device registered as /dev/video%d\n",
		  jpu->vfd_decoder.num);

	वापस 0;

enc_vdev_रेजिस्टर_rollback:
	video_unरेजिस्टर_device(&jpu->vfd_encoder);

m2m_init_rollback:
	v4l2_m2m_release(jpu->m2m_dev);

device_रेजिस्टर_rollback:
	v4l2_device_unरेजिस्टर(&jpu->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक jpu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jpu *jpu = platक्रमm_get_drvdata(pdev);

	video_unरेजिस्टर_device(&jpu->vfd_decoder);
	video_unरेजिस्टर_device(&jpu->vfd_encoder);
	v4l2_m2m_release(jpu->m2m_dev);
	v4l2_device_unरेजिस्टर(&jpu->v4l2_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक jpu_suspend(काष्ठा device *dev)
अणु
	काष्ठा jpu *jpu = dev_get_drvdata(dev);

	अगर (jpu->ref_count == 0)
		वापस 0;

	clk_disable_unprepare(jpu->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक jpu_resume(काष्ठा device *dev)
अणु
	काष्ठा jpu *jpu = dev_get_drvdata(dev);

	अगर (jpu->ref_count == 0)
		वापस 0;

	clk_prepare_enable(jpu->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops jpu_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(jpu_suspend, jpu_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver jpu_driver = अणु
	.probe = jpu_probe,
	.हटाओ = jpu_हटाओ,
	.driver = अणु
		.of_match_table = jpu_dt_ids,
		.name = DRV_NAME,
		.pm = &jpu_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jpu_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_AUTHOR("Mikhail Ulianov <mikhail.ulyanov@cogentembedded.com>");
MODULE_DESCRIPTION("Renesas R-Car JPEG processing unit driver");
MODULE_LICENSE("GPL v2");
