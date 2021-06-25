<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI VPE mem2mem driver, based on the भव v4l2-mem2mem example driver
 *
 * Copyright (c) 2013 Texas Instruments Inc.
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 *
 * Based on the भव v4l2-mem2mem example device
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/log2.h>
#समावेश <linux/sizes.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "vpdma.h"
#समावेश "vpdma_priv.h"
#समावेश "vpe_regs.h"
#समावेश "sc.h"
#समावेश "csc.h"

#घोषणा VPE_MODULE_NAME "vpe"

/* minimum and maximum frame sizes */
#घोषणा MIN_W		32
#घोषणा MIN_H		32
#घोषणा MAX_W		2048
#घोषणा MAX_H		2048

/* required alignments */
#घोषणा S_ALIGN		0	/* multiple of 1 */
#घोषणा H_ALIGN		1	/* multiple of 2 */

/* flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा VPE_FMT_TYPE_CAPTURE	(1 << 0)
#घोषणा VPE_FMT_TYPE_OUTPUT	(1 << 1)

/* used as plane indices */
#घोषणा VPE_MAX_PLANES	2
#घोषणा VPE_LUMA	0
#घोषणा VPE_CHROMA	1

/* per m2m context info */
#घोषणा VPE_MAX_SRC_BUFS	3	/* need 3 src fields to de-पूर्णांकerlace */

#घोषणा VPE_DEF_BUFS_PER_JOB	1	/* शेष one buffer per batch job */

/*
 * each VPE context can need up to 3 config descriptors, 7 input descriptors,
 * 3 output descriptors, and 10 control descriptors
 */
#घोषणा VPE_DESC_LIST_SIZE	(10 * VPDMA_DTD_DESC_SIZE +	\
					13 * VPDMA_CFD_CTD_DESC_SIZE)

#घोषणा vpe_dbg(vpedev, fmt, arg...)	\
		dev_dbg((vpedev)->v4l2_dev.dev, fmt, ##arg)
#घोषणा vpe_err(vpedev, fmt, arg...)	\
		dev_err((vpedev)->v4l2_dev.dev, fmt, ##arg)

काष्ठा vpe_us_coeffs अणु
	अचिन्हित लघु	anchor_fid0_c0;
	अचिन्हित लघु	anchor_fid0_c1;
	अचिन्हित लघु	anchor_fid0_c2;
	अचिन्हित लघु	anchor_fid0_c3;
	अचिन्हित लघु	पूर्णांकerp_fid0_c0;
	अचिन्हित लघु	पूर्णांकerp_fid0_c1;
	अचिन्हित लघु	पूर्णांकerp_fid0_c2;
	अचिन्हित लघु	पूर्णांकerp_fid0_c3;
	अचिन्हित लघु	anchor_fid1_c0;
	अचिन्हित लघु	anchor_fid1_c1;
	अचिन्हित लघु	anchor_fid1_c2;
	अचिन्हित लघु	anchor_fid1_c3;
	अचिन्हित लघु	पूर्णांकerp_fid1_c0;
	अचिन्हित लघु	पूर्णांकerp_fid1_c1;
	अचिन्हित लघु	पूर्णांकerp_fid1_c2;
	अचिन्हित लघु	पूर्णांकerp_fid1_c3;
पूर्ण;

/*
 * Default upsampler coefficients
 */
अटल स्थिर काष्ठा vpe_us_coeffs us_coeffs[] = अणु
	अणु
		/* Coefficients क्रम progressive input */
		0x00C8, 0x0348, 0x0018, 0x3FD8, 0x3FB8, 0x0378, 0x00E8, 0x3FE8,
		0x00C8, 0x0348, 0x0018, 0x3FD8, 0x3FB8, 0x0378, 0x00E8, 0x3FE8,
	पूर्ण,
	अणु
		/* Coefficients क्रम Top Field Interlaced input */
		0x0051, 0x03D5, 0x3FE3, 0x3FF7, 0x3FB5, 0x02E9, 0x018F, 0x3FD3,
		/* Coefficients क्रम Bottom Field Interlaced input */
		0x016B, 0x0247, 0x00B1, 0x3F9D, 0x3FCF, 0x03DB, 0x005D, 0x3FF9,
	पूर्ण,
पूर्ण;

/*
 * the following रेजिस्टरs are क्रम configuring some of the parameters of the
 * motion and edge detection blocks inside DEI, these generally reमुख्य the same,
 * these could be passed later via userspace अगर some one needs to tweak these.
 */
काष्ठा vpe_dei_regs अणु
	अचिन्हित दीर्घ mdt_spacial_freq_thr_reg;		/* VPE_DEI_REG2 */
	अचिन्हित दीर्घ edi_config_reg;			/* VPE_DEI_REG3 */
	अचिन्हित दीर्घ edi_lut_reg0;			/* VPE_DEI_REG4 */
	अचिन्हित दीर्घ edi_lut_reg1;			/* VPE_DEI_REG5 */
	अचिन्हित दीर्घ edi_lut_reg2;			/* VPE_DEI_REG6 */
	अचिन्हित दीर्घ edi_lut_reg3;			/* VPE_DEI_REG7 */
पूर्ण;

/*
 * शेष expert DEI रेजिस्टर values, unlikely to be modअगरied.
 */
अटल स्थिर काष्ठा vpe_dei_regs dei_regs = अणु
	.mdt_spacial_freq_thr_reg = 0x020C0804u,
	.edi_config_reg = 0x0118100Cu,
	.edi_lut_reg0 = 0x08040200u,
	.edi_lut_reg1 = 0x1010100Cu,
	.edi_lut_reg2 = 0x10101010u,
	.edi_lut_reg3 = 0x10101010u,
पूर्ण;

/*
 * The port_data काष्ठाure contains per-port data.
 */
काष्ठा vpe_port_data अणु
	क्रमागत vpdma_channel channel;	/* VPDMA channel */
	u8	vb_index;		/* input frame f, f-1, f-2 index */
	u8	vb_part;		/* plane index क्रम co-panar क्रमmats */
पूर्ण;

/*
 * Define indices पूर्णांकo the port_data tables
 */
#घोषणा VPE_PORT_LUMA1_IN	0
#घोषणा VPE_PORT_CHROMA1_IN	1
#घोषणा VPE_PORT_LUMA2_IN	2
#घोषणा VPE_PORT_CHROMA2_IN	3
#घोषणा VPE_PORT_LUMA3_IN	4
#घोषणा VPE_PORT_CHROMA3_IN	5
#घोषणा VPE_PORT_MV_IN		6
#घोषणा VPE_PORT_MV_OUT		7
#घोषणा VPE_PORT_LUMA_OUT	8
#घोषणा VPE_PORT_CHROMA_OUT	9
#घोषणा VPE_PORT_RGB_OUT	10

अटल स्थिर काष्ठा vpe_port_data port_data[11] = अणु
	[VPE_PORT_LUMA1_IN] = अणु
		.channel	= VPE_CHAN_LUMA1_IN,
		.vb_index	= 0,
		.vb_part	= VPE_LUMA,
	पूर्ण,
	[VPE_PORT_CHROMA1_IN] = अणु
		.channel	= VPE_CHAN_CHROMA1_IN,
		.vb_index	= 0,
		.vb_part	= VPE_CHROMA,
	पूर्ण,
	[VPE_PORT_LUMA2_IN] = अणु
		.channel	= VPE_CHAN_LUMA2_IN,
		.vb_index	= 1,
		.vb_part	= VPE_LUMA,
	पूर्ण,
	[VPE_PORT_CHROMA2_IN] = अणु
		.channel	= VPE_CHAN_CHROMA2_IN,
		.vb_index	= 1,
		.vb_part	= VPE_CHROMA,
	पूर्ण,
	[VPE_PORT_LUMA3_IN] = अणु
		.channel	= VPE_CHAN_LUMA3_IN,
		.vb_index	= 2,
		.vb_part	= VPE_LUMA,
	पूर्ण,
	[VPE_PORT_CHROMA3_IN] = अणु
		.channel	= VPE_CHAN_CHROMA3_IN,
		.vb_index	= 2,
		.vb_part	= VPE_CHROMA,
	पूर्ण,
	[VPE_PORT_MV_IN] = अणु
		.channel	= VPE_CHAN_MV_IN,
	पूर्ण,
	[VPE_PORT_MV_OUT] = अणु
		.channel	= VPE_CHAN_MV_OUT,
	पूर्ण,
	[VPE_PORT_LUMA_OUT] = अणु
		.channel	= VPE_CHAN_LUMA_OUT,
		.vb_part	= VPE_LUMA,
	पूर्ण,
	[VPE_PORT_CHROMA_OUT] = अणु
		.channel	= VPE_CHAN_CHROMA_OUT,
		.vb_part	= VPE_CHROMA,
	पूर्ण,
	[VPE_PORT_RGB_OUT] = अणु
		.channel	= VPE_CHAN_RGB_OUT,
		.vb_part	= VPE_LUMA,
	पूर्ण,
पूर्ण;


/* driver info क्रम each of the supported video क्रमmats */
काष्ठा vpe_fmt अणु
	u32	fourcc;			/* standard क्रमmat identअगरier */
	u8	types;			/* CAPTURE and/or OUTPUT */
	u8	coplanar;		/* set क्रम unpacked Luma and Chroma */
	/* vpdma क्रमmat info क्रम each plane */
	काष्ठा vpdma_data_क्रमmat स्थिर *vpdma_fmt[VPE_MAX_PLANES];
पूर्ण;

अटल काष्ठा vpe_fmt vpe_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_NV16,
		.types		= VPE_FMT_TYPE_CAPTURE | VPE_FMT_TYPE_OUTPUT,
		.coplanar	= 1,
		.vpdma_fmt	= अणु &vpdma_yuv_fmts[VPDMA_DATA_FMT_Y444],
				    &vpdma_yuv_fmts[VPDMA_DATA_FMT_C444],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12,
		.types		= VPE_FMT_TYPE_CAPTURE | VPE_FMT_TYPE_OUTPUT,
		.coplanar	= 1,
		.vpdma_fmt	= अणु &vpdma_yuv_fmts[VPDMA_DATA_FMT_Y420],
				    &vpdma_yuv_fmts[VPDMA_DATA_FMT_C420],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV21,
		.types		= VPE_FMT_TYPE_CAPTURE | VPE_FMT_TYPE_OUTPUT,
		.coplanar	= 1,
		.vpdma_fmt	= अणु &vpdma_yuv_fmts[VPDMA_DATA_FMT_Y420],
				    &vpdma_yuv_fmts[VPDMA_DATA_FMT_CB420],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.types		= VPE_FMT_TYPE_CAPTURE | VPE_FMT_TYPE_OUTPUT,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_yuv_fmts[VPDMA_DATA_FMT_YCB422],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.types		= VPE_FMT_TYPE_CAPTURE | VPE_FMT_TYPE_OUTPUT,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_yuv_fmts[VPDMA_DATA_FMT_CBY422],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB24,
		.types		= VPE_FMT_TYPE_CAPTURE,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_rgb_fmts[VPDMA_DATA_FMT_RGB24],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB32,
		.types		= VPE_FMT_TYPE_CAPTURE,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_rgb_fmts[VPDMA_DATA_FMT_ARGB32],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_BGR24,
		.types		= VPE_FMT_TYPE_CAPTURE,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_rgb_fmts[VPDMA_DATA_FMT_BGR24],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_BGR32,
		.types		= VPE_FMT_TYPE_CAPTURE,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_rgb_fmts[VPDMA_DATA_FMT_ABGR32],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.types		= VPE_FMT_TYPE_CAPTURE,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_rgb_fmts[VPDMA_DATA_FMT_RGB565],
				  पूर्ण,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB555,
		.types		= VPE_FMT_TYPE_CAPTURE,
		.coplanar	= 0,
		.vpdma_fmt	= अणु &vpdma_rgb_fmts[VPDMA_DATA_FMT_RGBA16_5551],
				  पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * per-queue, driver-specअगरic निजी data.
 * there is one source queue and one destination queue क्रम each m2m context.
 */
काष्ठा vpe_q_data अणु
	/* current v4l2 क्रमmat info */
	काष्ठा v4l2_क्रमmat	क्रमmat;
	अचिन्हित पूर्णांक		flags;
	काष्ठा v4l2_rect	c_rect;				/* crop/compose rectangle */
	काष्ठा vpe_fmt		*fmt;				/* क्रमmat info */
पूर्ण;

/* vpe_q_data flag bits */
#घोषणा	Q_DATA_FRAME_1D			BIT(0)
#घोषणा	Q_DATA_MODE_TILED		BIT(1)
#घोषणा	Q_DATA_INTERLACED_ALTERNATE	BIT(2)
#घोषणा	Q_DATA_INTERLACED_SEQ_TB	BIT(3)
#घोषणा	Q_DATA_INTERLACED_SEQ_BT	BIT(4)

#घोषणा Q_IS_SEQ_XX		(Q_DATA_INTERLACED_SEQ_TB | \
				Q_DATA_INTERLACED_SEQ_BT)

#घोषणा Q_IS_INTERLACED		(Q_DATA_INTERLACED_ALTERNATE | \
				Q_DATA_INTERLACED_SEQ_TB | \
				Q_DATA_INTERLACED_SEQ_BT)

क्रमागत अणु
	Q_DATA_SRC = 0,
	Q_DATA_DST = 1,
पूर्ण;

/* find our क्रमmat description corresponding to the passed v4l2_क्रमmat */
अटल काष्ठा vpe_fmt *__find_क्रमmat(u32 fourcc)
अणु
	काष्ठा vpe_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < ARRAY_SIZE(vpe_क्रमmats); k++) अणु
		fmt = &vpe_क्रमmats[k];
		अगर (fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा vpe_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f)
अणु
	वापस __find_क्रमmat(f->fmt.pix.pixelक्रमmat);
पूर्ण

/*
 * there is one vpe_dev काष्ठाure in the driver, it is shared by
 * all instances.
 */
काष्ठा vpe_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;
	काष्ठा v4l2_m2m_dev	*m2m_dev;

	atomic_t		num_instances;	/* count of driver instances */
	dma_addr_t		loaded_mmrs;	/* shaकरोw mmrs in device */
	काष्ठा mutex		dev_mutex;
	spinlock_t		lock;

	पूर्णांक			irq;
	व्योम __iomem		*base;
	काष्ठा resource		*res;

	काष्ठा vpdma_data	vpdma_data;
	काष्ठा vpdma_data	*vpdma;		/* vpdma data handle */
	काष्ठा sc_data		*sc;		/* scaler data handle */
	काष्ठा csc_data		*csc;		/* csc data handle */
पूर्ण;

/*
 * There is one vpe_ctx काष्ठाure क्रम each m2m context.
 */
काष्ठा vpe_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा vpe_dev		*dev;
	काष्ठा v4l2_ctrl_handler hdl;

	अचिन्हित पूर्णांक		field;			/* current field */
	अचिन्हित पूर्णांक		sequence;		/* current frame/field seq */
	अचिन्हित पूर्णांक		पातing;		/* पात after next irq */

	अचिन्हित पूर्णांक		bufs_per_job;		/* input buffers per batch */
	अचिन्हित पूर्णांक		bufs_completed;		/* bufs करोne in this batch */

	काष्ठा vpe_q_data	q_data[2];		/* src & dst queue data */
	काष्ठा vb2_v4l2_buffer	*src_vbs[VPE_MAX_SRC_BUFS];
	काष्ठा vb2_v4l2_buffer	*dst_vb;

	dma_addr_t		mv_buf_dma[2];		/* dma addrs of motion vector in/out bufs */
	व्योम			*mv_buf[2];		/* भव addrs of motion vector bufs */
	माप_प्रकार			mv_buf_size;		/* current motion vector buffer size */
	काष्ठा vpdma_buf	mmr_adb;		/* shaकरोw reg addr/data block */
	काष्ठा vpdma_buf	sc_coeff_h;		/* h coeff buffer */
	काष्ठा vpdma_buf	sc_coeff_v;		/* v coeff buffer */
	काष्ठा vpdma_desc_list	desc_list;		/* DMA descriptor list */

	bool			deपूर्णांकerlacing;		/* using de-पूर्णांकerlacer */
	bool			load_mmrs;		/* have new shaकरोw reg values */

	अचिन्हित पूर्णांक		src_mv_buf_selector;
पूर्ण;


/*
 * M2M devices get 2 queues.
 * Return the queue given the type.
 */
अटल काष्ठा vpe_q_data *get_q_data(काष्ठा vpe_ctx *ctx,
				     क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &ctx->q_data[Q_DATA_SRC];
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &ctx->q_data[Q_DATA_DST];
	शेष:
		वापस शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल u32 पढ़ो_reg(काष्ठा vpe_dev *dev, पूर्णांक offset)
अणु
	वापस ioपढ़ो32(dev->base + offset);
पूर्ण

अटल व्योम ग_लिखो_reg(काष्ठा vpe_dev *dev, पूर्णांक offset, u32 value)
अणु
	ioग_लिखो32(value, dev->base + offset);
पूर्ण

/* रेजिस्टर field पढ़ो/ग_लिखो helpers */
अटल पूर्णांक get_field(u32 value, u32 mask, पूर्णांक shअगरt)
अणु
	वापस (value & (mask << shअगरt)) >> shअगरt;
पूर्ण

अटल पूर्णांक पढ़ो_field_reg(काष्ठा vpe_dev *dev, पूर्णांक offset, u32 mask, पूर्णांक shअगरt)
अणु
	वापस get_field(पढ़ो_reg(dev, offset), mask, shअगरt);
पूर्ण

अटल व्योम ग_लिखो_field(u32 *valp, u32 field, u32 mask, पूर्णांक shअगरt)
अणु
	u32 val = *valp;

	val &= ~(mask << shअगरt);
	val |= (field & mask) << shअगरt;
	*valp = val;
पूर्ण

अटल व्योम ग_लिखो_field_reg(काष्ठा vpe_dev *dev, पूर्णांक offset, u32 field,
		u32 mask, पूर्णांक shअगरt)
अणु
	u32 val = पढ़ो_reg(dev, offset);

	ग_लिखो_field(&val, field, mask, shअगरt);

	ग_लिखो_reg(dev, offset, val);
पूर्ण

/*
 * DMA address/data block क्रम the shaकरोw रेजिस्टरs
 */
काष्ठा vpe_mmr_adb अणु
	काष्ठा vpdma_adb_hdr	out_fmt_hdr;
	u32			out_fmt_reg[1];
	u32			out_fmt_pad[3];
	काष्ठा vpdma_adb_hdr	us1_hdr;
	u32			us1_regs[8];
	काष्ठा vpdma_adb_hdr	us2_hdr;
	u32			us2_regs[8];
	काष्ठा vpdma_adb_hdr	us3_hdr;
	u32			us3_regs[8];
	काष्ठा vpdma_adb_hdr	dei_hdr;
	u32			dei_regs[8];
	काष्ठा vpdma_adb_hdr	sc_hdr0;
	u32			sc_regs0[7];
	u32			sc_pad0[1];
	काष्ठा vpdma_adb_hdr	sc_hdr8;
	u32			sc_regs8[6];
	u32			sc_pad8[2];
	काष्ठा vpdma_adb_hdr	sc_hdr17;
	u32			sc_regs17[9];
	u32			sc_pad17[3];
	काष्ठा vpdma_adb_hdr	csc_hdr;
	u32			csc_regs[6];
	u32			csc_pad[2];
पूर्ण;

#घोषणा GET_OFFSET_TOP(ctx, obj, reg)	\
	((obj)->res->start - ctx->dev->res->start + reg)

#घोषणा VPE_SET_MMR_ADB_HDR(ctx, hdr, regs, offset_a)	\
	VPDMA_SET_MMR_ADB_HDR(ctx->mmr_adb, vpe_mmr_adb, hdr, regs, offset_a)
/*
 * Set the headers क्रम all of the address/data block काष्ठाures.
 */
अटल व्योम init_adb_hdrs(काष्ठा vpe_ctx *ctx)
अणु
	VPE_SET_MMR_ADB_HDR(ctx, out_fmt_hdr, out_fmt_reg, VPE_CLK_FORMAT_SELECT);
	VPE_SET_MMR_ADB_HDR(ctx, us1_hdr, us1_regs, VPE_US1_R0);
	VPE_SET_MMR_ADB_HDR(ctx, us2_hdr, us2_regs, VPE_US2_R0);
	VPE_SET_MMR_ADB_HDR(ctx, us3_hdr, us3_regs, VPE_US3_R0);
	VPE_SET_MMR_ADB_HDR(ctx, dei_hdr, dei_regs, VPE_DEI_FRAME_SIZE);
	VPE_SET_MMR_ADB_HDR(ctx, sc_hdr0, sc_regs0,
		GET_OFFSET_TOP(ctx, ctx->dev->sc, CFG_SC0));
	VPE_SET_MMR_ADB_HDR(ctx, sc_hdr8, sc_regs8,
		GET_OFFSET_TOP(ctx, ctx->dev->sc, CFG_SC8));
	VPE_SET_MMR_ADB_HDR(ctx, sc_hdr17, sc_regs17,
		GET_OFFSET_TOP(ctx, ctx->dev->sc, CFG_SC17));
	VPE_SET_MMR_ADB_HDR(ctx, csc_hdr, csc_regs,
		GET_OFFSET_TOP(ctx, ctx->dev->csc, CSC_CSC00));
पूर्ण;

/*
 * Allocate or re-allocate the motion vector DMA buffers
 * There are two buffers, one क्रम input and one क्रम output.
 * However, the roles are reversed after each field is processed.
 * In other words, after each field is processed, the previous
 * output (dst) MV buffer becomes the new input (src) MV buffer.
 */
अटल पूर्णांक पुनः_स्मृति_mv_buffers(काष्ठा vpe_ctx *ctx, माप_प्रकार size)
अणु
	काष्ठा device *dev = ctx->dev->v4l2_dev.dev;

	अगर (ctx->mv_buf_size == size)
		वापस 0;

	अगर (ctx->mv_buf[0])
		dma_मुक्त_coherent(dev, ctx->mv_buf_size, ctx->mv_buf[0],
			ctx->mv_buf_dma[0]);

	अगर (ctx->mv_buf[1])
		dma_मुक्त_coherent(dev, ctx->mv_buf_size, ctx->mv_buf[1],
			ctx->mv_buf_dma[1]);

	अगर (size == 0)
		वापस 0;

	ctx->mv_buf[0] = dma_alloc_coherent(dev, size, &ctx->mv_buf_dma[0],
				GFP_KERNEL);
	अगर (!ctx->mv_buf[0]) अणु
		vpe_err(ctx->dev, "failed to allocate motion vector buffer\n");
		वापस -ENOMEM;
	पूर्ण

	ctx->mv_buf[1] = dma_alloc_coherent(dev, size, &ctx->mv_buf_dma[1],
				GFP_KERNEL);
	अगर (!ctx->mv_buf[1]) अणु
		vpe_err(ctx->dev, "failed to allocate motion vector buffer\n");
		dma_मुक्त_coherent(dev, size, ctx->mv_buf[0],
			ctx->mv_buf_dma[0]);

		वापस -ENOMEM;
	पूर्ण

	ctx->mv_buf_size = size;
	ctx->src_mv_buf_selector = 0;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_mv_buffers(काष्ठा vpe_ctx *ctx)
अणु
	पुनः_स्मृति_mv_buffers(ctx, 0);
पूर्ण

/*
 * While de-पूर्णांकerlacing, we keep the two most recent input buffers
 * around.  This function मुक्तs those two buffers when we have
 * finished processing the current stream.
 */
अटल व्योम मुक्त_vbs(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_dev *dev = ctx->dev;
	अचिन्हित दीर्घ flags;

	अगर (ctx->src_vbs[2] == शून्य)
		वापस;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (ctx->src_vbs[2]) अणु
		v4l2_m2m_buf_करोne(ctx->src_vbs[2], VB2_BUF_STATE_DONE);
		अगर (ctx->src_vbs[1] && (ctx->src_vbs[1] != ctx->src_vbs[2]))
			v4l2_m2m_buf_करोne(ctx->src_vbs[1], VB2_BUF_STATE_DONE);
		ctx->src_vbs[2] = शून्य;
		ctx->src_vbs[1] = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

/*
 * Enable or disable the VPE घड़ीs
 */
अटल व्योम vpe_set_घड़ी_enable(काष्ठा vpe_dev *dev, bool on)
अणु
	u32 val = 0;

	अगर (on)
		val = VPE_DATA_PATH_CLK_ENABLE | VPE_VPEDMA_CLK_ENABLE;
	ग_लिखो_reg(dev, VPE_CLK_ENABLE, val);
पूर्ण

अटल व्योम vpe_top_reset(काष्ठा vpe_dev *dev)
अणु

	ग_लिखो_field_reg(dev, VPE_CLK_RESET, 1, VPE_DATA_PATH_CLK_RESET_MASK,
		VPE_DATA_PATH_CLK_RESET_SHIFT);

	usleep_range(100, 150);

	ग_लिखो_field_reg(dev, VPE_CLK_RESET, 0, VPE_DATA_PATH_CLK_RESET_MASK,
		VPE_DATA_PATH_CLK_RESET_SHIFT);
पूर्ण

अटल व्योम vpe_top_vpdma_reset(काष्ठा vpe_dev *dev)
अणु
	ग_लिखो_field_reg(dev, VPE_CLK_RESET, 1, VPE_VPDMA_CLK_RESET_MASK,
		VPE_VPDMA_CLK_RESET_SHIFT);

	usleep_range(100, 150);

	ग_लिखो_field_reg(dev, VPE_CLK_RESET, 0, VPE_VPDMA_CLK_RESET_MASK,
		VPE_VPDMA_CLK_RESET_SHIFT);
पूर्ण

/*
 * Load the correct of upsampler coefficients पूर्णांकo the shaकरोw MMRs
 */
अटल व्योम set_us_coefficients(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	काष्ठा vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SRC];
	u32 *us1_reg = &mmr_adb->us1_regs[0];
	u32 *us2_reg = &mmr_adb->us2_regs[0];
	u32 *us3_reg = &mmr_adb->us3_regs[0];
	स्थिर अचिन्हित लघु *cp, *end_cp;

	cp = &us_coeffs[0].anchor_fid0_c0;

	अगर (s_q_data->flags & Q_IS_INTERLACED)		/* पूर्णांकerlaced */
		cp += माप(us_coeffs[0]) / माप(*cp);

	end_cp = cp + माप(us_coeffs[0]) / माप(*cp);

	जबतक (cp < end_cp) अणु
		ग_लिखो_field(us1_reg, *cp++, VPE_US_C0_MASK, VPE_US_C0_SHIFT);
		ग_लिखो_field(us1_reg, *cp++, VPE_US_C1_MASK, VPE_US_C1_SHIFT);
		*us2_reg++ = *us1_reg;
		*us3_reg++ = *us1_reg++;
	पूर्ण
	ctx->load_mmrs = true;
पूर्ण

/*
 * Set the upsampler config mode and the VPDMA line mode in the shaकरोw MMRs.
 */
अटल व्योम set_cfg_modes(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_fmt *fmt = ctx->q_data[Q_DATA_SRC].fmt;
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	u32 *us1_reg0 = &mmr_adb->us1_regs[0];
	u32 *us2_reg0 = &mmr_adb->us2_regs[0];
	u32 *us3_reg0 = &mmr_adb->us3_regs[0];
	पूर्णांक cfg_mode = 1;

	/*
	 * Cfg Mode 0: YUV420 source, enable upsampler, DEI is de-पूर्णांकerlacing.
	 * Cfg Mode 1: YUV422 source, disable upsampler, DEI is de-पूर्णांकerlacing.
	 */

	अगर (fmt->fourcc == V4L2_PIX_FMT_NV12 ||
	    fmt->fourcc == V4L2_PIX_FMT_NV21)
		cfg_mode = 0;

	ग_लिखो_field(us1_reg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);
	ग_लिखो_field(us2_reg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);
	ग_लिखो_field(us3_reg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);

	ctx->load_mmrs = true;
पूर्ण

अटल व्योम set_line_modes(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_fmt *fmt = ctx->q_data[Q_DATA_SRC].fmt;
	पूर्णांक line_mode = 1;

	अगर (fmt->fourcc == V4L2_PIX_FMT_NV12 ||
	    fmt->fourcc == V4L2_PIX_FMT_NV21)
		line_mode = 0;		/* द्विगुन lines to line buffer */

	/* regs क्रम now */
	vpdma_set_line_mode(ctx->dev->vpdma, line_mode, VPE_CHAN_CHROMA1_IN);
	vpdma_set_line_mode(ctx->dev->vpdma, line_mode, VPE_CHAN_CHROMA2_IN);
	vpdma_set_line_mode(ctx->dev->vpdma, line_mode, VPE_CHAN_CHROMA3_IN);

	/* frame start क्रम input luma */
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_LUMA1_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_LUMA2_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_LUMA3_IN);

	/* frame start क्रम input chroma */
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_CHROMA1_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_CHROMA2_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_CHROMA3_IN);

	/* frame start क्रम MV in client */
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_MV_IN);
पूर्ण

/*
 * Set the shaकरोw रेजिस्टरs that are modअगरied when the source
 * क्रमmat changes.
 */
अटल व्योम set_src_रेजिस्टरs(काष्ठा vpe_ctx *ctx)
अणु
	set_us_coefficients(ctx);
पूर्ण

/*
 * Set the shaकरोw रेजिस्टरs that are modअगरied when the destination
 * क्रमmat changes.
 */
अटल व्योम set_dst_रेजिस्टरs(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	काष्ठा vpe_fmt *fmt = ctx->q_data[Q_DATA_DST].fmt;
	स्थिर काष्ठा v4l2_क्रमmat_info *finfo;
	u32 val = 0;

	finfo = v4l2_क्रमmat_info(fmt->fourcc);
	अगर (v4l2_is_क्रमmat_rgb(finfo)) अणु
		val |= VPE_RGB_OUT_SELECT;
		vpdma_set_bg_color(ctx->dev->vpdma,
			(काष्ठा vpdma_data_क्रमmat *)fmt->vpdma_fmt[0], 0xff);
	पूर्ण अन्यथा अगर (fmt->fourcc == V4L2_PIX_FMT_NV16)
		val |= VPE_COLOR_SEPARATE_422;

	/*
	 * the source of CHR_DS and CSC is always the scaler, irrespective of
	 * whether it's used or not
	 */
	val |= VPE_DS_SRC_DEI_SCALER | VPE_CSC_SRC_DEI_SCALER;

	अगर (fmt->fourcc != V4L2_PIX_FMT_NV12 &&
	    fmt->fourcc != V4L2_PIX_FMT_NV21)
		val |= VPE_DS_BYPASS;

	mmr_adb->out_fmt_reg[0] = val;

	ctx->load_mmrs = true;
पूर्ण

/*
 * Set the de-पूर्णांकerlacer shaकरोw रेजिस्टर values
 */
अटल व्योम set_dei_regs(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	काष्ठा vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SRC];
	अचिन्हित पूर्णांक src_h = s_q_data->c_rect.height;
	अचिन्हित पूर्णांक src_w = s_q_data->c_rect.width;
	u32 *dei_mmr0 = &mmr_adb->dei_regs[0];
	bool deपूर्णांकerlace = true;
	u32 val = 0;

	/*
	 * according to TRM, we should set DEI in progressive bypass mode when
	 * the input content is progressive, however, DEI is bypassed correctly
	 * क्रम both progressive and पूर्णांकerlace content in पूर्णांकerlace bypass mode.
	 * It has been recommended not to use progressive bypass mode.
	 */
	अगर (!(s_q_data->flags & Q_IS_INTERLACED) || !ctx->deपूर्णांकerlacing) अणु
		deपूर्णांकerlace = false;
		val = VPE_DEI_INTERLACE_BYPASS;
	पूर्ण

	src_h = deपूर्णांकerlace ? src_h * 2 : src_h;

	val |= (src_h << VPE_DEI_HEIGHT_SHIFT) |
		(src_w << VPE_DEI_WIDTH_SHIFT) |
		VPE_DEI_FIELD_FLUSH;

	*dei_mmr0 = val;

	ctx->load_mmrs = true;
पूर्ण

अटल व्योम set_dei_shaकरोw_रेजिस्टरs(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	u32 *dei_mmr = &mmr_adb->dei_regs[0];
	स्थिर काष्ठा vpe_dei_regs *cur = &dei_regs;

	dei_mmr[2]  = cur->mdt_spacial_freq_thr_reg;
	dei_mmr[3]  = cur->edi_config_reg;
	dei_mmr[4]  = cur->edi_lut_reg0;
	dei_mmr[5]  = cur->edi_lut_reg1;
	dei_mmr[6]  = cur->edi_lut_reg2;
	dei_mmr[7]  = cur->edi_lut_reg3;

	ctx->load_mmrs = true;
पूर्ण

अटल व्योम config_edi_input_mode(काष्ठा vpe_ctx *ctx, पूर्णांक mode)
अणु
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	u32 *edi_config_reg = &mmr_adb->dei_regs[3];

	अगर (mode & 0x2)
		ग_लिखो_field(edi_config_reg, 1, 1, 2);	/* EDI_ENABLE_3D */

	अगर (mode & 0x3)
		ग_लिखो_field(edi_config_reg, 1, 1, 3);	/* EDI_CHROMA_3D  */

	ग_लिखो_field(edi_config_reg, mode, VPE_EDI_INP_MODE_MASK,
		VPE_EDI_INP_MODE_SHIFT);

	ctx->load_mmrs = true;
पूर्ण

/*
 * Set the shaकरोw रेजिस्टरs whose values are modअगरied when either the
 * source or destination क्रमmat is changed.
 */
अटल पूर्णांक set_srcdst_params(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_q_data *s_q_data =  &ctx->q_data[Q_DATA_SRC];
	काष्ठा vpe_q_data *d_q_data =  &ctx->q_data[Q_DATA_DST];
	काष्ठा vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	अचिन्हित पूर्णांक src_w = s_q_data->c_rect.width;
	अचिन्हित पूर्णांक src_h = s_q_data->c_rect.height;
	अचिन्हित पूर्णांक dst_w = d_q_data->c_rect.width;
	अचिन्हित पूर्णांक dst_h = d_q_data->c_rect.height;
	काष्ठा v4l2_pix_क्रमmat_mplane *spix;
	माप_प्रकार mv_buf_size;
	पूर्णांक ret;

	ctx->sequence = 0;
	ctx->field = V4L2_FIELD_TOP;
	spix = &s_q_data->क्रमmat.fmt.pix_mp;

	अगर ((s_q_data->flags & Q_IS_INTERLACED) &&
			!(d_q_data->flags & Q_IS_INTERLACED)) अणु
		पूर्णांक bytes_per_line;
		स्थिर काष्ठा vpdma_data_क्रमmat *mv =
			&vpdma_misc_fmts[VPDMA_DATA_FMT_MV];

		/*
		 * we make sure that the source image has a 16 byte aligned
		 * stride, we need to करो the same क्रम the motion vector buffer
		 * by aligning it's stride to the next 16 byte boundary. this
		 * extra space will not be used by the de-पूर्णांकerlacer, but will
		 * ensure that vpdma operates correctly
		 */
		bytes_per_line = ALIGN((spix->width * mv->depth) >> 3,
				       VPDMA_STRIDE_ALIGN);
		mv_buf_size = bytes_per_line * spix->height;

		ctx->deपूर्णांकerlacing = true;
		src_h <<= 1;
	पूर्ण अन्यथा अणु
		ctx->deपूर्णांकerlacing = false;
		mv_buf_size = 0;
	पूर्ण

	मुक्त_vbs(ctx);
	ctx->src_vbs[2] = ctx->src_vbs[1] = ctx->src_vbs[0] = शून्य;

	ret = पुनः_स्मृति_mv_buffers(ctx, mv_buf_size);
	अगर (ret)
		वापस ret;

	set_cfg_modes(ctx);
	set_dei_regs(ctx);

	csc_set_coeff(ctx->dev->csc, &mmr_adb->csc_regs[0],
		      &s_q_data->क्रमmat, &d_q_data->क्रमmat);

	sc_set_hs_coeffs(ctx->dev->sc, ctx->sc_coeff_h.addr, src_w, dst_w);
	sc_set_vs_coeffs(ctx->dev->sc, ctx->sc_coeff_v.addr, src_h, dst_h);

	sc_config_scaler(ctx->dev->sc, &mmr_adb->sc_regs0[0],
		&mmr_adb->sc_regs8[0], &mmr_adb->sc_regs17[0],
		src_w, src_h, dst_w, dst_h);

	वापस 0;
पूर्ण

/*
 * mem2mem callbacks
 */

/*
 * job_पढ़ोy() - check whether an instance is पढ़ोy to be scheduled to run
 */
अटल पूर्णांक job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा vpe_ctx *ctx = priv;

	/*
	 * This check is needed as this might be called directly from driver
	 * When called by m2m framework, this will always satisfy, but when
	 * called from vpe_irq, this might fail. (src stream with zero buffers)
	 */
	अगर (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) <= 0 ||
		v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx) <= 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम job_पात(व्योम *priv)
अणु
	काष्ठा vpe_ctx *ctx = priv;

	/* Will cancel the transaction in the next पूर्णांकerrupt handler */
	ctx->पातing = 1;
पूर्ण

अटल व्योम vpe_dump_regs(काष्ठा vpe_dev *dev)
अणु
#घोषणा DUMPREG(r) vpe_dbg(dev, "%-35s %08x\n", #r, पढ़ो_reg(dev, VPE_##r))

	vpe_dbg(dev, "VPE Registers:\n");

	DUMPREG(PID);
	DUMPREG(SYSCONFIG);
	DUMPREG(INT0_STATUS0_RAW);
	DUMPREG(INT0_STATUS0);
	DUMPREG(INT0_ENABLE0);
	DUMPREG(INT0_STATUS1_RAW);
	DUMPREG(INT0_STATUS1);
	DUMPREG(INT0_ENABLE1);
	DUMPREG(CLK_ENABLE);
	DUMPREG(CLK_RESET);
	DUMPREG(CLK_FORMAT_SELECT);
	DUMPREG(CLK_RANGE_MAP);
	DUMPREG(US1_R0);
	DUMPREG(US1_R1);
	DUMPREG(US1_R2);
	DUMPREG(US1_R3);
	DUMPREG(US1_R4);
	DUMPREG(US1_R5);
	DUMPREG(US1_R6);
	DUMPREG(US1_R7);
	DUMPREG(US2_R0);
	DUMPREG(US2_R1);
	DUMPREG(US2_R2);
	DUMPREG(US2_R3);
	DUMPREG(US2_R4);
	DUMPREG(US2_R5);
	DUMPREG(US2_R6);
	DUMPREG(US2_R7);
	DUMPREG(US3_R0);
	DUMPREG(US3_R1);
	DUMPREG(US3_R2);
	DUMPREG(US3_R3);
	DUMPREG(US3_R4);
	DUMPREG(US3_R5);
	DUMPREG(US3_R6);
	DUMPREG(US3_R7);
	DUMPREG(DEI_FRAME_SIZE);
	DUMPREG(MDT_BYPASS);
	DUMPREG(MDT_SF_THRESHOLD);
	DUMPREG(EDI_CONFIG);
	DUMPREG(DEI_EDI_LUT_R0);
	DUMPREG(DEI_EDI_LUT_R1);
	DUMPREG(DEI_EDI_LUT_R2);
	DUMPREG(DEI_EDI_LUT_R3);
	DUMPREG(DEI_FMD_WINDOW_R0);
	DUMPREG(DEI_FMD_WINDOW_R1);
	DUMPREG(DEI_FMD_CONTROL_R0);
	DUMPREG(DEI_FMD_CONTROL_R1);
	DUMPREG(DEI_FMD_STATUS_R0);
	DUMPREG(DEI_FMD_STATUS_R1);
	DUMPREG(DEI_FMD_STATUS_R2);
#अघोषित DUMPREG

	sc_dump_regs(dev->sc);
	csc_dump_regs(dev->csc);
पूर्ण

अटल व्योम add_out_dtd(काष्ठा vpe_ctx *ctx, पूर्णांक port)
अणु
	काष्ठा vpe_q_data *q_data = &ctx->q_data[Q_DATA_DST];
	स्थिर काष्ठा vpe_port_data *p_data = &port_data[port];
	काष्ठा vb2_buffer *vb = &ctx->dst_vb->vb2_buf;
	काष्ठा vpe_fmt *fmt = q_data->fmt;
	स्थिर काष्ठा vpdma_data_क्रमmat *vpdma_fmt;
	पूर्णांक mv_buf_selector = !ctx->src_mv_buf_selector;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	dma_addr_t dma_addr;
	u32 flags = 0;
	u32 offset = 0;
	u32 stride;

	अगर (port == VPE_PORT_MV_OUT) अणु
		vpdma_fmt = &vpdma_misc_fmts[VPDMA_DATA_FMT_MV];
		dma_addr = ctx->mv_buf_dma[mv_buf_selector];
		q_data = &ctx->q_data[Q_DATA_SRC];
		pix = &q_data->क्रमmat.fmt.pix_mp;
		stride = ALIGN((pix->width * vpdma_fmt->depth) >> 3,
			       VPDMA_STRIDE_ALIGN);
	पूर्ण अन्यथा अणु
		/* to incorporate पूर्णांकerleaved क्रमmats */
		पूर्णांक plane = fmt->coplanar ? p_data->vb_part : 0;

		pix = &q_data->क्रमmat.fmt.pix_mp;
		vpdma_fmt = fmt->vpdma_fmt[plane];
		/*
		 * If we are using a single plane buffer and
		 * we need to set a separate vpdma chroma channel.
		 */
		अगर (pix->num_planes == 1 && plane) अणु
			dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
			/* Compute required offset */
			offset = pix->plane_fmt[0].bytesperline * pix->height;
		पूर्ण अन्यथा अणु
			dma_addr = vb2_dma_contig_plane_dma_addr(vb, plane);
			/* Use address as is, no offset */
			offset = 0;
		पूर्ण
		अगर (!dma_addr) अणु
			vpe_err(ctx->dev,
				"acquiring output buffer(%d) dma_addr failed\n",
				port);
			वापस;
		पूर्ण
		/* Apply the offset */
		dma_addr += offset;
		stride = pix->plane_fmt[VPE_LUMA].bytesperline;
	पूर्ण

	अगर (q_data->flags & Q_DATA_FRAME_1D)
		flags |= VPDMA_DATA_FRAME_1D;
	अगर (q_data->flags & Q_DATA_MODE_TILED)
		flags |= VPDMA_DATA_MODE_TILED;

	vpdma_set_max_size(ctx->dev->vpdma, VPDMA_MAX_SIZE1,
			   MAX_W, MAX_H);

	vpdma_add_out_dtd(&ctx->desc_list, pix->width,
			  stride, &q_data->c_rect,
			  vpdma_fmt, dma_addr, MAX_OUT_WIDTH_REG1,
			  MAX_OUT_HEIGHT_REG1, p_data->channel, flags);
पूर्ण

अटल व्योम add_in_dtd(काष्ठा vpe_ctx *ctx, पूर्णांक port)
अणु
	काष्ठा vpe_q_data *q_data = &ctx->q_data[Q_DATA_SRC];
	स्थिर काष्ठा vpe_port_data *p_data = &port_data[port];
	काष्ठा vb2_buffer *vb = &ctx->src_vbs[p_data->vb_index]->vb2_buf;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vpe_fmt *fmt = q_data->fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	स्थिर काष्ठा vpdma_data_क्रमmat *vpdma_fmt;
	पूर्णांक mv_buf_selector = ctx->src_mv_buf_selector;
	पूर्णांक field = vbuf->field == V4L2_FIELD_BOTTOM;
	पूर्णांक frame_width, frame_height;
	dma_addr_t dma_addr;
	u32 flags = 0;
	u32 offset = 0;
	u32 stride;

	pix = &q_data->क्रमmat.fmt.pix_mp;
	अगर (port == VPE_PORT_MV_IN) अणु
		vpdma_fmt = &vpdma_misc_fmts[VPDMA_DATA_FMT_MV];
		dma_addr = ctx->mv_buf_dma[mv_buf_selector];
		stride = ALIGN((pix->width * vpdma_fmt->depth) >> 3,
			       VPDMA_STRIDE_ALIGN);
	पूर्ण अन्यथा अणु
		/* to incorporate पूर्णांकerleaved क्रमmats */
		पूर्णांक plane = fmt->coplanar ? p_data->vb_part : 0;

		vpdma_fmt = fmt->vpdma_fmt[plane];
		/*
		 * If we are using a single plane buffer and
		 * we need to set a separate vpdma chroma channel.
		 */
		अगर (pix->num_planes == 1 && plane) अणु
			dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
			/* Compute required offset */
			offset = pix->plane_fmt[0].bytesperline * pix->height;
		पूर्ण अन्यथा अणु
			dma_addr = vb2_dma_contig_plane_dma_addr(vb, plane);
			/* Use address as is, no offset */
			offset = 0;
		पूर्ण
		अगर (!dma_addr) अणु
			vpe_err(ctx->dev,
				"acquiring output buffer(%d) dma_addr failed\n",
				port);
			वापस;
		पूर्ण
		/* Apply the offset */
		dma_addr += offset;
		stride = pix->plane_fmt[VPE_LUMA].bytesperline;

		/*
		 * field used in VPDMA desc  = 0 (top) / 1 (bottom)
		 * Use top or bottom field from same vb alternately
		 * For each de-पूर्णांकerlacing operation, f,f-1,f-2 should be one
		 * of TBT or BTB
		 */
		अगर (q_data->flags & Q_DATA_INTERLACED_SEQ_TB ||
		    q_data->flags & Q_DATA_INTERLACED_SEQ_BT) अणु
			/* Select initial value based on क्रमmat */
			अगर (q_data->flags & Q_DATA_INTERLACED_SEQ_BT)
				field = 1;
			अन्यथा
				field = 0;

			/* Toggle क्रम each vb_index and each operation */
			field = (field + p_data->vb_index + ctx->sequence) % 2;

			अगर (field) अणु
				पूर्णांक height = pix->height / 2;
				पूर्णांक bpp;

				अगर (fmt->fourcc == V4L2_PIX_FMT_NV12 ||
				    fmt->fourcc == V4L2_PIX_FMT_NV21)
					bpp = 1;
				अन्यथा
					bpp = vpdma_fmt->depth >> 3;

				अगर (plane)
					height /= 2;

				dma_addr += pix->width * height * bpp;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (q_data->flags & Q_DATA_FRAME_1D)
		flags |= VPDMA_DATA_FRAME_1D;
	अगर (q_data->flags & Q_DATA_MODE_TILED)
		flags |= VPDMA_DATA_MODE_TILED;

	frame_width = q_data->c_rect.width;
	frame_height = q_data->c_rect.height;

	अगर (p_data->vb_part && (fmt->fourcc == V4L2_PIX_FMT_NV12 ||
				fmt->fourcc == V4L2_PIX_FMT_NV21))
		frame_height /= 2;

	vpdma_add_in_dtd(&ctx->desc_list, pix->width, stride,
			 &q_data->c_rect, vpdma_fmt, dma_addr,
			 p_data->channel, field, flags, frame_width,
			 frame_height, 0, 0);
पूर्ण

/*
 * Enable the expected IRQ sources
 */
अटल व्योम enable_irqs(काष्ठा vpe_ctx *ctx)
अणु
	ग_लिखो_reg(ctx->dev, VPE_INT0_ENABLE0_SET, VPE_INT0_LIST0_COMPLETE);
	ग_लिखो_reg(ctx->dev, VPE_INT0_ENABLE1_SET, VPE_DEI_ERROR_INT |
				VPE_DS1_UV_ERROR_INT);

	vpdma_enable_list_complete_irq(ctx->dev->vpdma, 0, 0, true);
पूर्ण

अटल व्योम disable_irqs(काष्ठा vpe_ctx *ctx)
अणु
	ग_लिखो_reg(ctx->dev, VPE_INT0_ENABLE0_CLR, 0xffffffff);
	ग_लिखो_reg(ctx->dev, VPE_INT0_ENABLE1_CLR, 0xffffffff);

	vpdma_enable_list_complete_irq(ctx->dev->vpdma, 0, 0, false);
पूर्ण

/* device_run() - prepares and starts the device
 *
 * This function is only called when both the source and destination
 * buffers are in place.
 */
अटल व्योम device_run(व्योम *priv)
अणु
	काष्ठा vpe_ctx *ctx = priv;
	काष्ठा sc_data *sc = ctx->dev->sc;
	काष्ठा vpe_q_data *d_q_data = &ctx->q_data[Q_DATA_DST];
	काष्ठा vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SRC];
	स्थिर काष्ठा v4l2_क्रमmat_info *d_finfo;

	d_finfo = v4l2_क्रमmat_info(d_q_data->fmt->fourcc);

	अगर (ctx->deपूर्णांकerlacing && s_q_data->flags & Q_IS_SEQ_XX &&
	    ctx->sequence % 2 == 0) अणु
		/* When using SEQ_XX type buffers, each buffer has two fields
		 * each buffer has two fields (top & bottom)
		 * Removing one buffer is actually getting two fields
		 * Alternate between two operations:-
		 * Even : consume one field but DO NOT REMOVE from queue
		 * Odd : consume other field and REMOVE from queue
		 */
		ctx->src_vbs[0] = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		WARN_ON(ctx->src_vbs[0] == शून्य);
	पूर्ण अन्यथा अणु
		ctx->src_vbs[0] = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		WARN_ON(ctx->src_vbs[0] == शून्य);
	पूर्ण

	ctx->dst_vb = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	WARN_ON(ctx->dst_vb == शून्य);

	अगर (ctx->deपूर्णांकerlacing) अणु

		अगर (ctx->src_vbs[2] == शून्य) अणु
			ctx->src_vbs[2] = ctx->src_vbs[0];
			WARN_ON(ctx->src_vbs[2] == शून्य);
			ctx->src_vbs[1] = ctx->src_vbs[0];
			WARN_ON(ctx->src_vbs[1] == शून्य);
		पूर्ण

		/*
		 * we have output the first 2 frames through line average, we
		 * now चयन to EDI de-पूर्णांकerlacer
		 */
		अगर (ctx->sequence == 2)
			config_edi_input_mode(ctx, 0x3); /* EDI (Y + UV) */
	पूर्ण

	/* config descriptors */
	अगर (ctx->dev->loaded_mmrs != ctx->mmr_adb.dma_addr || ctx->load_mmrs) अणु
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->mmr_adb);
		vpdma_add_cfd_adb(&ctx->desc_list, CFD_MMR_CLIENT, &ctx->mmr_adb);

		set_line_modes(ctx);

		ctx->dev->loaded_mmrs = ctx->mmr_adb.dma_addr;
		ctx->load_mmrs = false;
	पूर्ण

	अगर (sc->loaded_coeff_h != ctx->sc_coeff_h.dma_addr ||
			sc->load_coeff_h) अणु
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->sc_coeff_h);
		vpdma_add_cfd_block(&ctx->desc_list, CFD_SC_CLIENT,
			&ctx->sc_coeff_h, 0);

		sc->loaded_coeff_h = ctx->sc_coeff_h.dma_addr;
		sc->load_coeff_h = false;
	पूर्ण

	अगर (sc->loaded_coeff_v != ctx->sc_coeff_v.dma_addr ||
			sc->load_coeff_v) अणु
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->sc_coeff_v);
		vpdma_add_cfd_block(&ctx->desc_list, CFD_SC_CLIENT,
			&ctx->sc_coeff_v, SC_COEF_SRAM_SIZE >> 4);

		sc->loaded_coeff_v = ctx->sc_coeff_v.dma_addr;
		sc->load_coeff_v = false;
	पूर्ण

	/* output data descriptors */
	अगर (ctx->deपूर्णांकerlacing)
		add_out_dtd(ctx, VPE_PORT_MV_OUT);

	अगर (v4l2_is_क्रमmat_rgb(d_finfo)) अणु
		add_out_dtd(ctx, VPE_PORT_RGB_OUT);
	पूर्ण अन्यथा अणु
		add_out_dtd(ctx, VPE_PORT_LUMA_OUT);
		अगर (d_q_data->fmt->coplanar)
			add_out_dtd(ctx, VPE_PORT_CHROMA_OUT);
	पूर्ण

	/* input data descriptors */
	अगर (ctx->deपूर्णांकerlacing) अणु
		add_in_dtd(ctx, VPE_PORT_LUMA3_IN);
		add_in_dtd(ctx, VPE_PORT_CHROMA3_IN);

		add_in_dtd(ctx, VPE_PORT_LUMA2_IN);
		add_in_dtd(ctx, VPE_PORT_CHROMA2_IN);
	पूर्ण

	add_in_dtd(ctx, VPE_PORT_LUMA1_IN);
	add_in_dtd(ctx, VPE_PORT_CHROMA1_IN);

	अगर (ctx->deपूर्णांकerlacing)
		add_in_dtd(ctx, VPE_PORT_MV_IN);

	/* sync on channel control descriptors क्रम input ports */
	vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_LUMA1_IN);
	vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_CHROMA1_IN);

	अगर (ctx->deपूर्णांकerlacing) अणु
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_LUMA2_IN);
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_CHROMA2_IN);

		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_LUMA3_IN);
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_CHROMA3_IN);

		vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_MV_IN);
	पूर्ण

	/* sync on channel control descriptors क्रम output ports */
	अगर (v4l2_is_क्रमmat_rgb(d_finfo)) अणु
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_RGB_OUT);
	पूर्ण अन्यथा अणु
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_LUMA_OUT);
		अगर (d_q_data->fmt->coplanar)
			vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
				VPE_CHAN_CHROMA_OUT);
	पूर्ण

	अगर (ctx->deपूर्णांकerlacing)
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_MV_OUT);

	enable_irqs(ctx);

	vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->desc_list.buf);
	vpdma_submit_descs(ctx->dev->vpdma, &ctx->desc_list, 0);
पूर्ण

अटल व्योम dei_error(काष्ठा vpe_ctx *ctx)
अणु
	dev_warn(ctx->dev->v4l2_dev.dev,
		"received DEI error interrupt\n");
पूर्ण

अटल व्योम ds1_uv_error(काष्ठा vpe_ctx *ctx)
अणु
	dev_warn(ctx->dev->v4l2_dev.dev,
		"received downsampler error interrupt\n");
पूर्ण

अटल irqवापस_t vpe_irq(पूर्णांक irq_vpe, व्योम *data)
अणु
	काष्ठा vpe_dev *dev = (काष्ठा vpe_dev *)data;
	काष्ठा vpe_ctx *ctx;
	काष्ठा vpe_q_data *d_q_data;
	काष्ठा vb2_v4l2_buffer *s_vb, *d_vb;
	अचिन्हित दीर्घ flags;
	u32 irqst0, irqst1;
	bool list_complete = false;

	irqst0 = पढ़ो_reg(dev, VPE_INT0_STATUS0);
	अगर (irqst0) अणु
		ग_लिखो_reg(dev, VPE_INT0_STATUS0_CLR, irqst0);
		vpe_dbg(dev, "INT0_STATUS0 = 0x%08x\n", irqst0);
	पूर्ण

	irqst1 = पढ़ो_reg(dev, VPE_INT0_STATUS1);
	अगर (irqst1) अणु
		ग_लिखो_reg(dev, VPE_INT0_STATUS1_CLR, irqst1);
		vpe_dbg(dev, "INT0_STATUS1 = 0x%08x\n", irqst1);
	पूर्ण

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	अगर (!ctx) अणु
		vpe_err(dev, "instance released before end of transaction\n");
		जाओ handled;
	पूर्ण

	अगर (irqst1) अणु
		अगर (irqst1 & VPE_DEI_ERROR_INT) अणु
			irqst1 &= ~VPE_DEI_ERROR_INT;
			dei_error(ctx);
		पूर्ण
		अगर (irqst1 & VPE_DS1_UV_ERROR_INT) अणु
			irqst1 &= ~VPE_DS1_UV_ERROR_INT;
			ds1_uv_error(ctx);
		पूर्ण
	पूर्ण

	अगर (irqst0) अणु
		अगर (irqst0 & VPE_INT0_LIST0_COMPLETE)
			vpdma_clear_list_stat(ctx->dev->vpdma, 0, 0);

		irqst0 &= ~(VPE_INT0_LIST0_COMPLETE);
		list_complete = true;
	पूर्ण

	अगर (irqst0 | irqst1) अणु
		dev_warn(dev->v4l2_dev.dev, "Unexpected interrupt: INT0_STATUS0 = 0x%08x, INT0_STATUS1 = 0x%08x\n",
			irqst0, irqst1);
	पूर्ण

	/*
	 * Setup next operation only when list complete IRQ occurs
	 * otherwise, skip the following code
	 */
	अगर (!list_complete)
		जाओ handled;

	disable_irqs(ctx);

	vpdma_unmap_desc_buf(dev->vpdma, &ctx->desc_list.buf);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->mmr_adb);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_h);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_v);

	vpdma_reset_desc_list(&ctx->desc_list);

	 /* the previous dst mv buffer becomes the next src mv buffer */
	ctx->src_mv_buf_selector = !ctx->src_mv_buf_selector;

	s_vb = ctx->src_vbs[0];
	d_vb = ctx->dst_vb;

	d_vb->flags = s_vb->flags;
	d_vb->vb2_buf.बारtamp = s_vb->vb2_buf.बारtamp;

	अगर (s_vb->flags & V4L2_BUF_FLAG_TIMECODE)
		d_vb->समयcode = s_vb->समयcode;

	d_vb->sequence = ctx->sequence;
	s_vb->sequence = ctx->sequence;

	d_q_data = &ctx->q_data[Q_DATA_DST];
	अगर (d_q_data->flags & Q_IS_INTERLACED) अणु
		d_vb->field = ctx->field;
		अगर (ctx->field == V4L2_FIELD_BOTTOM) अणु
			ctx->sequence++;
			ctx->field = V4L2_FIELD_TOP;
		पूर्ण अन्यथा अणु
			WARN_ON(ctx->field != V4L2_FIELD_TOP);
			ctx->field = V4L2_FIELD_BOTTOM;
		पूर्ण
	पूर्ण अन्यथा अणु
		d_vb->field = V4L2_FIELD_NONE;
		ctx->sequence++;
	पूर्ण

	अगर (ctx->deपूर्णांकerlacing) अणु
		/*
		 * Allow source buffer to be dequeued only अगर it won't be used
		 * in the next iteration. All vbs are initialized to first
		 * buffer and we are shअगरting buffers every iteration, क्रम the
		 * first two iterations, no buffer will be dequeued.
		 * This ensures that driver will keep (n-2)th (n-1)th and (n)th
		 * field when deपूर्णांकerlacing is enabled
		 */
		अगर (ctx->src_vbs[2] != ctx->src_vbs[1])
			s_vb = ctx->src_vbs[2];
		अन्यथा
			s_vb = शून्य;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);

	अगर (s_vb)
		v4l2_m2m_buf_करोne(s_vb, VB2_BUF_STATE_DONE);

	v4l2_m2m_buf_करोne(d_vb, VB2_BUF_STATE_DONE);

	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (ctx->deपूर्णांकerlacing) अणु
		ctx->src_vbs[2] = ctx->src_vbs[1];
		ctx->src_vbs[1] = ctx->src_vbs[0];
	पूर्ण

	/*
	 * Since the vb2_buf_करोne has alपढ़ोy been called fir therse
	 * buffer we can now शून्य them out so that we won't try
	 * to clean out stray poपूर्णांकer later on.
	*/
	ctx->src_vbs[0] = शून्य;
	ctx->dst_vb = शून्य;

	अगर (ctx->पातing)
		जाओ finished;

	ctx->bufs_completed++;
	अगर (ctx->bufs_completed < ctx->bufs_per_job && job_पढ़ोy(ctx)) अणु
		device_run(ctx);
		जाओ handled;
	पूर्ण

finished:
	vpe_dbg(ctx->dev, "finishing transaction\n");
	ctx->bufs_completed = 0;
	v4l2_m2m_job_finish(dev->m2m_dev, ctx->fh.m2m_ctx);
handled:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * video ioctls
 */
अटल पूर्णांक vpe_querycap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, VPE_MODULE_NAME, माप(cap->driver));
	strscpy(cap->card, VPE_MODULE_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		VPE_MODULE_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक __क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, index;
	काष्ठा vpe_fmt *fmt = शून्य;

	index = 0;
	क्रम (i = 0; i < ARRAY_SIZE(vpe_क्रमmats); ++i) अणु
		अगर (vpe_क्रमmats[i].types & type) अणु
			अगर (index == f->index) अणु
				fmt = &vpe_क्रमmats[i];
				अवरोध;
			पूर्ण
			index++;
		पूर्ण
	पूर्ण

	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vpe_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(f->type))
		वापस __क्रमागत_fmt(f, VPE_FMT_TYPE_OUTPUT);

	वापस __क्रमागत_fmt(f, VPE_FMT_TYPE_CAPTURE);
पूर्ण

अटल पूर्णांक vpe_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा vpe_ctx *ctx = file->निजी_data;
	काष्ठा vb2_queue *vq;
	काष्ठा vpe_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	*f = q_data->क्रमmat;

	अगर (V4L2_TYPE_IS_CAPTURE(f->type)) अणु
		काष्ठा vpe_q_data *s_q_data;
		काष्ठा v4l2_pix_क्रमmat_mplane *spix;

		/* get colorimetry from the source queue */
		s_q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		spix = &s_q_data->क्रमmat.fmt.pix_mp;

		pix->colorspace = spix->colorspace;
		pix->xfer_func = spix->xfer_func;
		pix->ycbcr_enc = spix->ycbcr_enc;
		pix->quantization = spix->quantization;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __vpe_try_fmt(काष्ठा vpe_ctx *ctx, काष्ठा v4l2_क्रमmat *f,
		       काष्ठा vpe_fmt *fmt, पूर्णांक type)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *plane_fmt;
	अचिन्हित पूर्णांक w_align;
	पूर्णांक i, depth, depth_bytes, height;
	अचिन्हित पूर्णांक stride = 0;
	स्थिर काष्ठा v4l2_क्रमmat_info *finfo;

	अगर (!fmt || !(fmt->types & type)) अणु
		vpe_dbg(ctx->dev, "Fourcc format (0x%08x) invalid.\n",
			pix->pixelक्रमmat);
		fmt = __find_क्रमmat(V4L2_PIX_FMT_YUYV);
	पूर्ण

	अगर (pix->field != V4L2_FIELD_NONE &&
	    pix->field != V4L2_FIELD_ALTERNATE &&
	    pix->field != V4L2_FIELD_SEQ_TB &&
	    pix->field != V4L2_FIELD_SEQ_BT)
		pix->field = V4L2_FIELD_NONE;

	depth = fmt->vpdma_fmt[VPE_LUMA]->depth;

	/*
	 * the line stride should 16 byte aligned क्रम VPDMA to work, based on
	 * the bytes per pixel, figure out how much the width should be aligned
	 * to make sure line stride is 16 byte aligned
	 */
	depth_bytes = depth >> 3;

	अगर (depth_bytes == 3) अणु
		/*
		 * अगर bpp is 3(as in some RGB क्रमmats), the pixel width करोesn't
		 * really help in ensuring line stride is 16 byte aligned
		 */
		w_align = 4;
	पूर्ण अन्यथा अणु
		/*
		 * क्रम the reमुख्यder bpp(4, 2 and 1), the pixel width alignment
		 * can ensure a line stride alignment of 16 bytes. For example,
		 * अगर bpp is 2, then the line stride can be 16 byte aligned अगर
		 * the width is 8 byte aligned
		 */

		/*
		 * HACK: using order_base_2() here causes lots of यंत्र output
		 * errors with smatch, on i386:
		 * ./arch/x86/include/यंत्र/bitops.h:457:22:
		 *		 warning: यंत्र output is not an lvalue
		 * Perhaps some gcc optimization is करोing the wrong thing
		 * there.
		 * Let's get rid of them by करोing the calculus on two steps
		 */
		w_align = roundup_घात_of_two(VPDMA_DESC_ALIGN / depth_bytes);
		w_align = ilog2(w_align);
	पूर्ण

	v4l_bound_align_image(&pix->width, MIN_W, MAX_W, w_align,
			      &pix->height, MIN_H, MAX_H, H_ALIGN,
			      S_ALIGN);

	अगर (!pix->num_planes || pix->num_planes > 2)
		pix->num_planes = fmt->coplanar ? 2 : 1;
	अन्यथा अगर (pix->num_planes > 1 && !fmt->coplanar)
		pix->num_planes = 1;

	pix->pixelक्रमmat = fmt->fourcc;
	finfo = v4l2_क्रमmat_info(fmt->fourcc);

	/*
	 * For the actual image parameters, we need to consider the field
	 * height of the image क्रम SEQ_XX buffers.
	 */
	अगर (pix->field == V4L2_FIELD_SEQ_TB || pix->field == V4L2_FIELD_SEQ_BT)
		height = pix->height / 2;
	अन्यथा
		height = pix->height;

	अगर (!pix->colorspace) अणु
		अगर (v4l2_is_क्रमmat_rgb(finfo)) अणु
			pix->colorspace = V4L2_COLORSPACE_SRGB;
		पूर्ण अन्यथा अणु
			अगर (height > 1280)	/* HD */
				pix->colorspace = V4L2_COLORSPACE_REC709;
			अन्यथा			/* SD */
				pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pix->num_planes; i++) अणु
		plane_fmt = &pix->plane_fmt[i];
		depth = fmt->vpdma_fmt[i]->depth;

		stride = (pix->width * fmt->vpdma_fmt[VPE_LUMA]->depth) >> 3;
		अगर (stride > plane_fmt->bytesperline)
			plane_fmt->bytesperline = stride;

		plane_fmt->bytesperline = clamp_t(u32, plane_fmt->bytesperline,
						  stride,
						  VPDMA_MAX_STRIDE);

		plane_fmt->bytesperline = ALIGN(plane_fmt->bytesperline,
						VPDMA_STRIDE_ALIGN);

		अगर (i == VPE_LUMA) अणु
			plane_fmt->sizeimage = pix->height *
					       plane_fmt->bytesperline;

			अगर (pix->num_planes == 1 && fmt->coplanar)
				plane_fmt->sizeimage += pix->height *
					plane_fmt->bytesperline *
					fmt->vpdma_fmt[VPE_CHROMA]->depth >> 3;

		पूर्ण अन्यथा अणु /* i == VIP_CHROMA */
			plane_fmt->sizeimage = (pix->height *
					       plane_fmt->bytesperline *
					       depth) >> 3;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpe_try_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vpe_ctx *ctx = file->निजी_data;
	काष्ठा vpe_fmt *fmt = find_क्रमmat(f);

	अगर (V4L2_TYPE_IS_OUTPUT(f->type))
		वापस __vpe_try_fmt(ctx, f, fmt, VPE_FMT_TYPE_OUTPUT);
	अन्यथा
		वापस __vpe_try_fmt(ctx, f, fmt, VPE_FMT_TYPE_CAPTURE);
पूर्ण

अटल पूर्णांक __vpe_s_fmt(काष्ठा vpe_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा v4l2_pix_क्रमmat_mplane *qpix;
	काष्ठा vpe_q_data *q_data;
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	अगर (vb2_is_busy(vq)) अणु
		vpe_err(ctx->dev, "queue busy\n");
		वापस -EBUSY;
	पूर्ण

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	qpix = &q_data->क्रमmat.fmt.pix_mp;
	q_data->fmt		= find_क्रमmat(f);
	q_data->क्रमmat = *f;

	q_data->c_rect.left	= 0;
	q_data->c_rect.top	= 0;
	q_data->c_rect.width	= pix->width;
	q_data->c_rect.height	= pix->height;

	अगर (qpix->field == V4L2_FIELD_ALTERNATE)
		q_data->flags |= Q_DATA_INTERLACED_ALTERNATE;
	अन्यथा अगर (qpix->field == V4L2_FIELD_SEQ_TB)
		q_data->flags |= Q_DATA_INTERLACED_SEQ_TB;
	अन्यथा अगर (qpix->field == V4L2_FIELD_SEQ_BT)
		q_data->flags |= Q_DATA_INTERLACED_SEQ_BT;
	अन्यथा
		q_data->flags &= ~Q_IS_INTERLACED;

	/* the crop height is halved क्रम the हाल of SEQ_XX buffers */
	अगर (q_data->flags & Q_IS_SEQ_XX)
		q_data->c_rect.height /= 2;

	vpe_dbg(ctx->dev, "Setting format for type %d, wxh: %dx%d, fmt: %d bpl_y %d",
		f->type, pix->width, pix->height, pix->pixelक्रमmat,
		pix->plane_fmt[0].bytesperline);
	अगर (pix->num_planes == 2)
		vpe_dbg(ctx->dev, " bpl_uv %d\n",
			pix->plane_fmt[1].bytesperline);

	वापस 0;
पूर्ण

अटल पूर्णांक vpe_s_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;
	काष्ठा vpe_ctx *ctx = file->निजी_data;

	ret = vpe_try_fmt(file, priv, f);
	अगर (ret)
		वापस ret;

	ret = __vpe_s_fmt(ctx, f);
	अगर (ret)
		वापस ret;

	अगर (V4L2_TYPE_IS_OUTPUT(f->type))
		set_src_रेजिस्टरs(ctx);
	अन्यथा
		set_dst_रेजिस्टरs(ctx);

	वापस set_srcdst_params(ctx);
पूर्ण

अटल पूर्णांक __vpe_try_selection(काष्ठा vpe_ctx *ctx, काष्ठा v4l2_selection *s)
अणु
	काष्ठा vpe_q_data *q_data;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	पूर्णांक height;

	अगर ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		वापस -EINVAL;

	q_data = get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;

	pix = &q_data->क्रमmat.fmt.pix_mp;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
		/*
		 * COMPOSE target is only valid क्रम capture buffer type, वापस
		 * error क्रम output buffer type
		 */
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		/*
		 * CROP target is only valid क्रम output buffer type, वापस
		 * error क्रम capture buffer type
		 */
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	/*
	 * bound and शेष crop/compose tarमाला_लो are invalid tarमाला_लो to
	 * try/set
	 */
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * For SEQ_XX buffers, crop height should be less than the height of
	 * the field height, not the buffer height
	 */
	अगर (q_data->flags & Q_IS_SEQ_XX)
		height = pix->height / 2;
	अन्यथा
		height = pix->height;

	अगर (s->r.top < 0 || s->r.left < 0) अणु
		vpe_err(ctx->dev, "negative values for top and left\n");
		s->r.top = s->r.left = 0;
	पूर्ण

	v4l_bound_align_image(&s->r.width, MIN_W, pix->width, 1,
		&s->r.height, MIN_H, height, H_ALIGN, S_ALIGN);

	/* adjust left/top अगर cropping rectangle is out of bounds */
	अगर (s->r.left + s->r.width > pix->width)
		s->r.left = pix->width - s->r.width;
	अगर (s->r.top + s->r.height > pix->height)
		s->r.top = pix->height - s->r.height;

	वापस 0;
पूर्ण

अटल पूर्णांक vpe_g_selection(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_selection *s)
अणु
	काष्ठा vpe_ctx *ctx = file->निजी_data;
	काष्ठा vpe_q_data *q_data;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	bool use_c_rect = false;

	अगर ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		वापस -EINVAL;

	q_data = get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;

	pix = &q_data->क्रमmat.fmt.pix_mp;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		use_c_rect = true;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		use_c_rect = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (use_c_rect) अणु
		/*
		 * क्रम CROP/COMPOSE target type, वापस c_rect params from the
		 * respective buffer type
		 */
		s->r = q_data->c_rect;
	पूर्ण अन्यथा अणु
		/*
		 * क्रम DEFAULT/BOUNDS target type, वापस width and height from
		 * S_FMT of the respective buffer type
		 */
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = pix->width;
		s->r.height = pix->height;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक vpe_s_selection(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_selection *s)
अणु
	काष्ठा vpe_ctx *ctx = file->निजी_data;
	काष्ठा vpe_q_data *q_data;
	काष्ठा v4l2_selection sel = *s;
	पूर्णांक ret;

	ret = __vpe_try_selection(ctx, &sel);
	अगर (ret)
		वापस ret;

	q_data = get_q_data(ctx, sel.type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर ((q_data->c_rect.left == sel.r.left) &&
			(q_data->c_rect.top == sel.r.top) &&
			(q_data->c_rect.width == sel.r.width) &&
			(q_data->c_rect.height == sel.r.height)) अणु
		vpe_dbg(ctx->dev,
			"requested crop/compose values are already set\n");
		वापस 0;
	पूर्ण

	q_data->c_rect = sel.r;

	वापस set_srcdst_params(ctx);
पूर्ण

/*
 * defines number of buffers/frames a context can process with VPE beक्रमe
 * चयनing to a dअगरferent context. शेष value is 1 buffer per context
 */
#घोषणा V4L2_CID_VPE_BUFS_PER_JOB		(V4L2_CID_USER_TI_VPE_BASE + 0)

अटल पूर्णांक vpe_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vpe_ctx *ctx =
		container_of(ctrl->handler, काष्ठा vpe_ctx, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VPE_BUFS_PER_JOB:
		ctx->bufs_per_job = ctrl->val;
		अवरोध;

	शेष:
		vpe_err(ctx->dev, "Invalid control\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vpe_ctrl_ops = अणु
	.s_ctrl = vpe_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops vpe_ioctl_ops = अणु
	.vidioc_querycap		= vpe_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= vpe_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap_mplane	= vpe_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= vpe_try_fmt,
	.vidioc_s_fmt_vid_cap_mplane	= vpe_s_fmt,

	.vidioc_क्रमागत_fmt_vid_out	= vpe_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out_mplane	= vpe_g_fmt,
	.vidioc_try_fmt_vid_out_mplane	= vpe_try_fmt,
	.vidioc_s_fmt_vid_out_mplane	= vpe_s_fmt,

	.vidioc_g_selection		= vpe_g_selection,
	.vidioc_s_selection		= vpe_s_selection,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/*
 * Queue operations
 */
अटल पूर्णांक vpe_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	पूर्णांक i;
	काष्ठा vpe_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vpe_q_data *q_data;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;

	q_data = get_q_data(ctx, vq->type);
	अगर (!q_data)
		वापस -EINVAL;

	pix = &q_data->क्रमmat.fmt.pix_mp;
	*nplanes = pix->num_planes;

	क्रम (i = 0; i < *nplanes; i++)
		sizes[i] = pix->plane_fmt[i].sizeimage;

	vpe_dbg(ctx->dev, "get %d buffer(s) of size %d", *nbuffers,
		sizes[VPE_LUMA]);
	अगर (*nplanes == 2)
		vpe_dbg(ctx->dev, " and %d\n", sizes[VPE_CHROMA]);

	वापस 0;
पूर्ण

अटल पूर्णांक vpe_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vpe_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vpe_q_data *q_data;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	पूर्णांक i;

	vpe_dbg(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	अगर (!q_data)
		वापस -EINVAL;

	pix = &q_data->क्रमmat.fmt.pix_mp;

	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (!(q_data->flags & Q_IS_INTERLACED)) अणु
			vbuf->field = V4L2_FIELD_NONE;
		पूर्ण अन्यथा अणु
			अगर (vbuf->field != V4L2_FIELD_TOP &&
			    vbuf->field != V4L2_FIELD_BOTTOM &&
			    vbuf->field != V4L2_FIELD_SEQ_TB &&
			    vbuf->field != V4L2_FIELD_SEQ_BT)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pix->num_planes; i++) अणु
		अगर (vb2_plane_size(vb, i) < pix->plane_fmt[i].sizeimage) अणु
			vpe_err(ctx->dev,
				"data will not fit into plane (%lu < %lu)\n",
				vb2_plane_size(vb, i),
				(दीर्घ)pix->plane_fmt[i].sizeimage);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pix->num_planes; i++)
		vb2_set_plane_payload(vb, i, pix->plane_fmt[i].sizeimage);

	वापस 0;
पूर्ण

अटल व्योम vpe_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vpe_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक check_srcdst_sizes(काष्ठा vpe_ctx *ctx)
अणु
	काष्ठा vpe_q_data *s_q_data =  &ctx->q_data[Q_DATA_SRC];
	काष्ठा vpe_q_data *d_q_data =  &ctx->q_data[Q_DATA_DST];
	अचिन्हित पूर्णांक src_w = s_q_data->c_rect.width;
	अचिन्हित पूर्णांक src_h = s_q_data->c_rect.height;
	अचिन्हित पूर्णांक dst_w = d_q_data->c_rect.width;
	अचिन्हित पूर्णांक dst_h = d_q_data->c_rect.height;

	अगर (src_w == dst_w && src_h == dst_h)
		वापस 0;

	अगर (src_h <= SC_MAX_PIXEL_HEIGHT &&
	    src_w <= SC_MAX_PIXEL_WIDTH &&
	    dst_h <= SC_MAX_PIXEL_HEIGHT &&
	    dst_w <= SC_MAX_PIXEL_WIDTH)
		वापस 0;

	वापस -1;
पूर्ण

अटल व्योम vpe_वापस_all_buffers(काष्ठा vpe_ctx *ctx,  काष्ठा vb2_queue *q,
				   क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vb2_v4l2_buffer *vb;
	अचिन्हित दीर्घ flags;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vb = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vb = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (!vb)
			अवरोध;
		spin_lock_irqsave(&ctx->dev->lock, flags);
		v4l2_m2m_buf_करोne(vb, state);
		spin_unlock_irqrestore(&ctx->dev->lock, flags);
	पूर्ण

	/*
	 * Cleanup the in-transit vb2 buffers that have been
	 * हटाओd from their respective queue alपढ़ोy but क्रम
	 * which procecessing has not been completed yet.
	 */
	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		spin_lock_irqsave(&ctx->dev->lock, flags);

		अगर (ctx->src_vbs[2])
			v4l2_m2m_buf_करोne(ctx->src_vbs[2], state);

		अगर (ctx->src_vbs[1] && (ctx->src_vbs[1] != ctx->src_vbs[2]))
			v4l2_m2m_buf_करोne(ctx->src_vbs[1], state);

		अगर (ctx->src_vbs[0] &&
		    (ctx->src_vbs[0] != ctx->src_vbs[1]) &&
		    (ctx->src_vbs[0] != ctx->src_vbs[2]))
			v4l2_m2m_buf_करोne(ctx->src_vbs[0], state);

		ctx->src_vbs[2] = शून्य;
		ctx->src_vbs[1] = शून्य;
		ctx->src_vbs[0] = शून्य;

		spin_unlock_irqrestore(&ctx->dev->lock, flags);
	पूर्ण अन्यथा अणु
		अगर (ctx->dst_vb) अणु
			spin_lock_irqsave(&ctx->dev->lock, flags);

			v4l2_m2m_buf_करोne(ctx->dst_vb, state);
			ctx->dst_vb = शून्य;
			spin_unlock_irqrestore(&ctx->dev->lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक vpe_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vpe_ctx *ctx = vb2_get_drv_priv(q);

	/* Check any of the size exceed maximum scaling sizes */
	अगर (check_srcdst_sizes(ctx)) अणु
		vpe_err(ctx->dev,
			"Conversion setup failed, check source and destination parameters\n"
			);
		vpe_वापस_all_buffers(ctx, q, VB2_BUF_STATE_QUEUED);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->deपूर्णांकerlacing)
		config_edi_input_mode(ctx, 0x0);

	अगर (ctx->sequence != 0)
		set_srcdst_params(ctx);

	वापस 0;
पूर्ण

अटल व्योम vpe_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा vpe_ctx *ctx = vb2_get_drv_priv(q);

	vpe_dump_regs(ctx->dev);
	vpdma_dump_regs(ctx->dev->vpdma);

	vpe_वापस_all_buffers(ctx, q, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops vpe_qops = अणु
	.queue_setup	 = vpe_queue_setup,
	.buf_prepare	 = vpe_buf_prepare,
	.buf_queue	 = vpe_buf_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.start_streaming = vpe_start_streaming,
	.stop_streaming  = vpe_stop_streaming,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा vpe_ctx *ctx = priv;
	काष्ठा vpe_dev *dev = ctx->dev;
	पूर्णांक ret;

	स_रखो(src_vq, 0, माप(*src_vq));
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &vpe_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &dev->dev_mutex;
	src_vq->dev = dev->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	स_रखो(dst_vq, 0, माप(*dst_vq));
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &vpe_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &dev->dev_mutex;
	dst_vq->dev = dev->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_config vpe_bufs_per_job = अणु
	.ops = &vpe_ctrl_ops,
	.id = V4L2_CID_VPE_BUFS_PER_JOB,
	.name = "Buffers Per Transaction",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = VPE_DEF_BUFS_PER_JOB,
	.min = 1,
	.max = VIDEO_MAX_FRAME,
	.step = 1,
पूर्ण;

/*
 * File operations
 */
अटल पूर्णांक vpe_खोलो(काष्ठा file *file)
अणु
	काष्ठा vpe_dev *dev = video_drvdata(file);
	काष्ठा vpe_q_data *s_q_data;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा vpe_ctx *ctx;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	पूर्णांक ret;

	vpe_dbg(dev, "vpe_open\n");

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->dev_mutex)) अणु
		ret = -ERESTARTSYS;
		जाओ मुक्त_ctx;
	पूर्ण

	ret = vpdma_create_desc_list(&ctx->desc_list, VPE_DESC_LIST_SIZE,
			VPDMA_LIST_TYPE_NORMAL);
	अगर (ret != 0)
		जाओ unlock;

	ret = vpdma_alloc_desc_buf(&ctx->mmr_adb, माप(काष्ठा vpe_mmr_adb));
	अगर (ret != 0)
		जाओ मुक्त_desc_list;

	ret = vpdma_alloc_desc_buf(&ctx->sc_coeff_h, SC_COEF_SRAM_SIZE);
	अगर (ret != 0)
		जाओ मुक्त_mmr_adb;

	ret = vpdma_alloc_desc_buf(&ctx->sc_coeff_v, SC_COEF_SRAM_SIZE);
	अगर (ret != 0)
		जाओ मुक्त_sc_h;

	init_adb_hdrs(ctx);

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = ctx;

	hdl = &ctx->hdl;
	v4l2_ctrl_handler_init(hdl, 1);
	v4l2_ctrl_new_custom(hdl, &vpe_bufs_per_job, शून्य);
	अगर (hdl->error) अणु
		ret = hdl->error;
		जाओ निकास_fh;
	पूर्ण
	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	s_q_data = &ctx->q_data[Q_DATA_SRC];
	pix = &s_q_data->क्रमmat.fmt.pix_mp;
	s_q_data->fmt = __find_क्रमmat(V4L2_PIX_FMT_YUYV);
	pix->pixelक्रमmat = s_q_data->fmt->fourcc;
	s_q_data->क्रमmat.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	pix->width = 1920;
	pix->height = 1080;
	pix->num_planes = 1;
	pix->plane_fmt[VPE_LUMA].bytesperline = (pix->width *
			s_q_data->fmt->vpdma_fmt[VPE_LUMA]->depth) >> 3;
	pix->plane_fmt[VPE_LUMA].sizeimage =
			pix->plane_fmt[VPE_LUMA].bytesperline *
			pix->height;
	pix->colorspace = V4L2_COLORSPACE_REC709;
	pix->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	pix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	pix->quantization = V4L2_QUANTIZATION_DEFAULT;
	pix->field = V4L2_FIELD_NONE;
	s_q_data->c_rect.left = 0;
	s_q_data->c_rect.top = 0;
	s_q_data->c_rect.width = pix->width;
	s_q_data->c_rect.height = pix->height;
	s_q_data->flags = 0;

	ctx->q_data[Q_DATA_DST] = *s_q_data;
	ctx->q_data[Q_DATA_DST].क्रमmat.type =
			V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;

	set_dei_shaकरोw_रेजिस्टरs(ctx);
	set_src_रेजिस्टरs(ctx);
	set_dst_रेजिस्टरs(ctx);
	ret = set_srcdst_params(ctx);
	अगर (ret)
		जाओ निकास_fh;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ निकास_fh;
	पूर्ण

	v4l2_fh_add(&ctx->fh);

	/*
	 * क्रम now, just report the creation of the first instance, we can later
	 * optimize the driver to enable or disable घड़ीs when the first
	 * instance is created or the last instance released
	 */
	अगर (atomic_inc_वापस(&dev->num_instances) == 1)
		vpe_dbg(dev, "first instance created\n");

	ctx->bufs_per_job = VPE_DEF_BUFS_PER_JOB;

	ctx->load_mmrs = true;

	vpe_dbg(dev, "created instance %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

	mutex_unlock(&dev->dev_mutex);

	वापस 0;
निकास_fh:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_fh_निकास(&ctx->fh);
	vpdma_मुक्त_desc_buf(&ctx->sc_coeff_v);
मुक्त_sc_h:
	vpdma_मुक्त_desc_buf(&ctx->sc_coeff_h);
मुक्त_mmr_adb:
	vpdma_मुक्त_desc_buf(&ctx->mmr_adb);
मुक्त_desc_list:
	vpdma_मुक्त_desc_list(&ctx->desc_list);
unlock:
	mutex_unlock(&dev->dev_mutex);
मुक्त_ctx:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक vpe_release(काष्ठा file *file)
अणु
	काष्ठा vpe_dev *dev = video_drvdata(file);
	काष्ठा vpe_ctx *ctx = file->निजी_data;

	vpe_dbg(dev, "releasing instance %p\n", ctx);

	mutex_lock(&dev->dev_mutex);
	मुक्त_mv_buffers(ctx);

	vpdma_unmap_desc_buf(dev->vpdma, &ctx->desc_list.buf);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->mmr_adb);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_h);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_v);

	vpdma_मुक्त_desc_list(&ctx->desc_list);
	vpdma_मुक्त_desc_buf(&ctx->mmr_adb);

	vpdma_मुक्त_desc_buf(&ctx->sc_coeff_v);
	vpdma_मुक्त_desc_buf(&ctx->sc_coeff_h);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->hdl);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	kमुक्त(ctx);

	/*
	 * क्रम now, just report the release of the last instance, we can later
	 * optimize the driver to enable or disable घड़ीs when the first
	 * instance is created or the last instance released
	 */
	अगर (atomic_dec_वापस(&dev->num_instances) == 0)
		vpe_dbg(dev, "last instance released\n");

	mutex_unlock(&dev->dev_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vpe_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vpe_खोलो,
	.release	= vpe_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device vpe_videodev = अणु
	.name		= VPE_MODULE_NAME,
	.fops		= &vpe_fops,
	.ioctl_ops	= &vpe_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
	.vfl_dir	= VFL_सूची_M2M,
	.device_caps	= V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= device_run,
	.job_पढ़ोy	= job_पढ़ोy,
	.job_पात	= job_पात,
पूर्ण;

अटल पूर्णांक vpe_runसमय_get(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक r;

	dev_dbg(&pdev->dev, "vpe_runtime_get\n");

	r = pm_runसमय_get_sync(&pdev->dev);
	WARN_ON(r < 0);
	अगर (r)
		pm_runसमय_put_noidle(&pdev->dev);
	वापस r < 0 ? r : 0;
पूर्ण

अटल व्योम vpe_runसमय_put(काष्ठा platक्रमm_device *pdev)
अणु

	पूर्णांक r;

	dev_dbg(&pdev->dev, "vpe_runtime_put\n");

	r = pm_runसमय_put_sync(&pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल व्योम vpe_fw_cb(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpe_dev *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	vfd = &dev->vfd;
	*vfd = vpe_videodev;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		vpe_err(dev, "Failed to register video device\n");

		vpe_set_घड़ी_enable(dev, 0);
		vpe_runसमय_put(pdev);
		pm_runसमय_disable(&pdev->dev);
		v4l2_m2m_release(dev->m2m_dev);
		v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

		वापस;
	पूर्ण

	video_set_drvdata(vfd, dev);
	dev_info(dev->v4l2_dev.dev, "Device registered as /dev/video%d\n",
		vfd->num);
पूर्ण

अटल पूर्णांक vpe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpe_dev *dev;
	पूर्णांक ret, irq, func;

	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"32-bit consistent DMA enable failed\n");
		वापस ret;
	पूर्ण

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	spin_lock_init(&dev->lock);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		वापस ret;

	atomic_set(&dev->num_instances, 0);
	mutex_init(&dev->dev_mutex);

	dev->res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						"vpe_top");
	अगर (!dev->res) अणु
		dev_err(&pdev->dev, "missing 'vpe_top' resources data\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * HACK: we get resource info from device tree in the क्रमm of a list of
	 * VPE sub blocks, the driver currently uses only the base of vpe_top
	 * क्रम रेजिस्टर access, the driver should be changed later to access
	 * रेजिस्टरs based on the sub block base addresses
	 */
	dev->base = devm_ioremap(&pdev->dev, dev->res->start, SZ_32K);
	अगर (!dev->base) अणु
		ret = -ENOMEM;
		जाओ v4l2_dev_unreg;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, vpe_irq, 0, VPE_MODULE_NAME,
			dev);
	अगर (ret)
		जाओ v4l2_dev_unreg;

	platक्रमm_set_drvdata(pdev, dev);

	dev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		vpe_err(dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		जाओ v4l2_dev_unreg;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	ret = vpe_runसमय_get(pdev);
	अगर (ret)
		जाओ rel_m2m;

	/* Perक्रमm clk enable followed by reset */
	vpe_set_घड़ी_enable(dev, 1);

	vpe_top_reset(dev);

	func = पढ़ो_field_reg(dev, VPE_PID, VPE_PID_FUNC_MASK,
		VPE_PID_FUNC_SHIFT);
	vpe_dbg(dev, "VPE PID function %x\n", func);

	vpe_top_vpdma_reset(dev);

	dev->sc = sc_create(pdev, "sc");
	अगर (IS_ERR(dev->sc)) अणु
		ret = PTR_ERR(dev->sc);
		जाओ runसमय_put;
	पूर्ण

	dev->csc = csc_create(pdev, "csc");
	अगर (IS_ERR(dev->csc)) अणु
		ret = PTR_ERR(dev->csc);
		जाओ runसमय_put;
	पूर्ण

	dev->vpdma = &dev->vpdma_data;
	ret = vpdma_create(pdev, dev->vpdma, vpe_fw_cb);
	अगर (ret)
		जाओ runसमय_put;

	वापस 0;

runसमय_put:
	vpe_runसमय_put(pdev);
rel_m2m:
	pm_runसमय_disable(&pdev->dev);
	v4l2_m2m_release(dev->m2m_dev);
v4l2_dev_unreg:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक vpe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpe_dev *dev = platक्रमm_get_drvdata(pdev);

	v4l2_info(&dev->v4l2_dev, "Removing " VPE_MODULE_NAME);

	v4l2_m2m_release(dev->m2m_dev);
	video_unरेजिस्टर_device(&dev->vfd);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	vpe_set_घड़ी_enable(dev, 0);
	vpe_runसमय_put(pdev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id vpe_of_match[] = अणु
	अणु
		.compatible = "ti,dra7-vpe",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vpe_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver vpe_pdrv = अणु
	.probe		= vpe_probe,
	.हटाओ		= vpe_हटाओ,
	.driver		= अणु
		.name	= VPE_MODULE_NAME,
		.of_match_table = of_match_ptr(vpe_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vpe_pdrv);

MODULE_DESCRIPTION("TI VPE driver");
MODULE_AUTHOR("Dale Farnsworth, <dale@farnsworth.org>");
MODULE_LICENSE("GPL");
