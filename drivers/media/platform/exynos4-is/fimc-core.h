<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 - 2012 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित FIMC_CORE_H_
#घोषणा FIMC_CORE_H_

/*#घोषणा DEBUG*/

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/पन.स>
#समावेश <linux/sizes.h>

#समावेश <media/media-entity.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#घोषणा dbg(fmt, args...) \
	pr_debug("%s:%d: " fmt "\n", __func__, __LINE__, ##args)

/* Time to रुको क्रम next frame VSYNC पूर्णांकerrupt जबतक stopping operation. */
#घोषणा FIMC_SHUTDOWN_TIMEOUT	((100*HZ)/1000)
#घोषणा MAX_FIMC_CLOCKS		2
#घोषणा FIMC_DRIVER_NAME	"exynos4-fimc"
#घोषणा FIMC_MAX_DEVS		4
#घोषणा FIMC_MAX_OUT_BUFS	4
#घोषणा SCALER_MAX_HRATIO	64
#घोषणा SCALER_MAX_VRATIO	64
#घोषणा DMA_MIN_SIZE		8
#घोषणा FIMC_CAMIF_MAX_HEIGHT	0x2000
#घोषणा FIMC_MAX_JPEG_BUF_SIZE	(10 * SZ_1M)
#घोषणा FIMC_MAX_PLANES		3
#घोषणा FIMC_PIX_LIMITS_MAX	4
#घोषणा FIMC_DEF_MIN_SIZE	16
#घोषणा FIMC_DEF_HEIGHT_ALIGN	2
#घोषणा FIMC_DEF_HOR_OFFS_ALIGN	1
#घोषणा FIMC_DEFAULT_WIDTH	640
#घोषणा FIMC_DEFAULT_HEIGHT	480

/* indices to the घड़ीs array */
क्रमागत अणु
	CLK_BUS,
	CLK_GATE,
पूर्ण;

क्रमागत fimc_dev_flags अणु
	ST_LPM,
	/* m2m node */
	ST_M2M_RUN,
	ST_M2M_PEND,
	ST_M2M_SUSPENDING,
	ST_M2M_SUSPENDED,
	/* capture node */
	ST_CAPT_PEND,
	ST_CAPT_RUN,
	ST_CAPT_STREAM,
	ST_CAPT_ISP_STREAM,
	ST_CAPT_SUSPENDED,
	ST_CAPT_SHUT,
	ST_CAPT_BUSY,
	ST_CAPT_APPLY_CFG,
	ST_CAPT_JPEG,
पूर्ण;

#घोषणा fimc_m2m_active(dev) test_bit(ST_M2M_RUN, &(dev)->state)
#घोषणा fimc_m2m_pending(dev) test_bit(ST_M2M_PEND, &(dev)->state)

#घोषणा fimc_capture_running(dev) test_bit(ST_CAPT_RUN, &(dev)->state)
#घोषणा fimc_capture_pending(dev) test_bit(ST_CAPT_PEND, &(dev)->state)
#घोषणा fimc_capture_busy(dev) test_bit(ST_CAPT_BUSY, &(dev)->state)

क्रमागत fimc_datapath अणु
	FIMC_IO_NONE,
	FIMC_IO_CAMERA,
	FIMC_IO_DMA,
	FIMC_IO_LCDFIFO,
	FIMC_IO_WRITEBACK,
	FIMC_IO_ISP,
पूर्ण;

क्रमागत fimc_color_fmt अणु
	FIMC_FMT_RGB444	= 0x10,
	FIMC_FMT_RGB555,
	FIMC_FMT_RGB565,
	FIMC_FMT_RGB666,
	FIMC_FMT_RGB888,
	FIMC_FMT_RGB30_LOCAL,
	FIMC_FMT_YCBCR420 = 0x20,
	FIMC_FMT_YCBYCR422,
	FIMC_FMT_YCRYCB422,
	FIMC_FMT_CBYCRY422,
	FIMC_FMT_CRYCBY422,
	FIMC_FMT_YCBCR444_LOCAL,
	FIMC_FMT_RAW8 = 0x40,
	FIMC_FMT_RAW10,
	FIMC_FMT_RAW12,
	FIMC_FMT_JPEG = 0x80,
	FIMC_FMT_YUYV_JPEG = 0x100,
पूर्ण;

#घोषणा fimc_fmt_is_user_defined(x) (!!((x) & 0x180))
#घोषणा fimc_fmt_is_rgb(x) (!!((x) & 0x10))

#घोषणा IS_M2M(__strt) ((__strt) == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE || \
			__strt == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)

/* The hardware context state. */
#घोषणा	FIMC_PARAMS		(1 << 0)
#घोषणा	FIMC_COMPOSE		(1 << 1)
#घोषणा	FIMC_CTX_M2M		(1 << 16)
#घोषणा	FIMC_CTX_CAP		(1 << 17)
#घोषणा	FIMC_CTX_SHUT		(1 << 18)

/* Image conversion flags */
#घोषणा	FIMC_IN_DMA_ACCESS_TILED	(1 << 0)
#घोषणा	FIMC_IN_DMA_ACCESS_LINEAR	(0 << 0)
#घोषणा	FIMC_OUT_DMA_ACCESS_TILED	(1 << 1)
#घोषणा	FIMC_OUT_DMA_ACCESS_LINEAR	(0 << 1)
#घोषणा	FIMC_SCAN_MODE_PROGRESSIVE	(0 << 2)
#घोषणा	FIMC_SCAN_MODE_INTERLACED	(1 << 2)
/*
 * YCbCr data dynamic range क्रम RGB-YUV color conversion.
 * Y/Cb/Cr: (0 ~ 255) */
#घोषणा	FIMC_COLOR_RANGE_WIDE		(0 << 3)
/* Y (16 ~ 235), Cb/Cr (16 ~ 240) */
#घोषणा	FIMC_COLOR_RANGE_NARROW		(1 << 3)

/**
 * काष्ठा fimc_dma_offset - pixel offset inक्रमmation क्रम DMA
 * @y_h:	y value horizontal offset
 * @y_v:	y value vertical offset
 * @cb_h:	cb value horizontal offset
 * @cb_v:	cb value vertical offset
 * @cr_h:	cr value horizontal offset
 * @cr_v:	cr value vertical offset
 */
काष्ठा fimc_dma_offset अणु
	पूर्णांक	y_h;
	पूर्णांक	y_v;
	पूर्णांक	cb_h;
	पूर्णांक	cb_v;
	पूर्णांक	cr_h;
	पूर्णांक	cr_v;
पूर्ण;

/**
 * काष्ठा fimc_effect - color effect inक्रमmation
 * @type:	effect type
 * @pat_cb:	cr value when type is "arbitrary"
 * @pat_cr:	cr value when type is "arbitrary"
 */
काष्ठा fimc_effect अणु
	u32	type;
	u8	pat_cb;
	u8	pat_cr;
पूर्ण;

/**
 * काष्ठा fimc_scaler - the configuration data क्रम FIMC inetrnal scaler
 * @scaleup_h:		flag indicating scaling up horizontally
 * @scaleup_v:		flag indicating scaling up vertically
 * @copy_mode:		flag indicating transparent DMA transfer (no scaling
 *			and color क्रमmat conversion)
 * @enabled:		flag indicating अगर the scaler is used
 * @hfactor:		horizontal shअगरt factor
 * @vfactor:		vertical shअगरt factor
 * @pre_hratio:		horizontal ratio of the prescaler
 * @pre_vratio:		vertical ratio of the prescaler
 * @pre_dst_width:	the prescaler's destination width
 * @pre_dst_height:	the prescaler's destination height
 * @मुख्य_hratio:	the मुख्य scaler's horizontal ratio
 * @मुख्य_vratio:	the मुख्य scaler's vertical ratio
 * @real_width:		source pixel (width - offset)
 * @real_height:	source pixel (height - offset)
 */
काष्ठा fimc_scaler अणु
	अचिन्हित पूर्णांक scaleup_h:1;
	अचिन्हित पूर्णांक scaleup_v:1;
	अचिन्हित पूर्णांक copy_mode:1;
	अचिन्हित पूर्णांक enabled:1;
	u32	hfactor;
	u32	vfactor;
	u32	pre_hratio;
	u32	pre_vratio;
	u32	pre_dst_width;
	u32	pre_dst_height;
	u32	मुख्य_hratio;
	u32	मुख्य_vratio;
	u32	real_width;
	u32	real_height;
पूर्ण;

/**
 * काष्ठा fimc_addr - the FIMC address set क्रम DMA
 * @y:	 luminance plane address
 * @cb:	 Cb plane address
 * @cr:	 Cr plane address
 */
काष्ठा fimc_addr अणु
	u32	y;
	u32	cb;
	u32	cr;
पूर्ण;

/**
 * काष्ठा fimc_vid_buffer - the driver's video buffer
 * @vb:    v4l videobuf buffer
 * @list:  linked list काष्ठाure क्रम buffer queue
 * @addr: precalculated DMA address set
 * @index: buffer index क्रम the output DMA engine
 */
काष्ठा fimc_vid_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head	list;
	काष्ठा fimc_addr	addr;
	पूर्णांक			index;
पूर्ण;

/**
 * काष्ठा fimc_frame - source/target frame properties
 * @f_width:	image full width (भव screen size)
 * @f_height:	image full height (भव screen size)
 * @o_width:	original image width as set by S_FMT
 * @o_height:	original image height as set by S_FMT
 * @offs_h:	image horizontal pixel offset
 * @offs_v:	image vertical pixel offset
 * @width:	image pixel width
 * @height:	image pixel weight
 * @payload:	image size in bytes (w x h x bpp)
 * @bytesperline: bytesperline value क्रम each plane
 * @addr:	image frame buffer DMA addresses
 * @dma_offset:	DMA offset in bytes
 * @fmt:	fimc color क्रमmat poपूर्णांकer
 * @alpha:	alpha value
 */
काष्ठा fimc_frame अणु
	u32	f_width;
	u32	f_height;
	u32	o_width;
	u32	o_height;
	u32	offs_h;
	u32	offs_v;
	u32	width;
	u32	height;
	अचिन्हित पूर्णांक		payload[VIDEO_MAX_PLANES];
	अचिन्हित पूर्णांक		bytesperline[VIDEO_MAX_PLANES];
	काष्ठा fimc_addr	addr;
	काष्ठा fimc_dma_offset	dma_offset;
	काष्ठा fimc_fmt		*fmt;
	u8			alpha;
पूर्ण;

/**
 * काष्ठा fimc_m2m_device - v4l2 memory-to-memory device data
 * @vfd: the video device node क्रम v4l2 m2m mode
 * @m2m_dev: v4l2 memory-to-memory device data
 * @ctx: hardware context data
 * @refcnt: the reference counter
 */
काष्ठा fimc_m2m_device अणु
	काष्ठा video_device	vfd;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा fimc_ctx		*ctx;
	पूर्णांक			refcnt;
पूर्ण;

#घोषणा FIMC_SD_PAD_SINK_CAM	0
#घोषणा FIMC_SD_PAD_SINK_FIFO	1
#घोषणा FIMC_SD_PAD_SOURCE	2
#घोषणा FIMC_SD_PADS_NUM	3

/**
 * काष्ठा fimc_vid_cap - camera capture device inक्रमmation
 * @ctx: hardware context data
 * @subdev: subdev exposing the FIMC processing block
 * @ve: exynos video device entity काष्ठाure
 * @vd_pad: fimc video capture node pad
 * @sd_pads: fimc video processing block pads
 * @ci_fmt: image क्रमmat at the FIMC camera input (and the scaler output)
 * @wb_fmt: image क्रमmat at the FIMC ISP Writeback input
 * @source_config: बाह्यal image source related configuration काष्ठाure
 * @pending_buf_q: the pending buffer queue head
 * @active_buf_q: the queue head of buffers scheduled in hardware
 * @vbq: the capture am video buffer queue
 * @active_buf_cnt: number of video buffers scheduled in hardware
 * @buf_index: index क्रम managing the output DMA buffers
 * @frame_count: the frame counter क्रम statistics
 * @reqbufs_count: the number of buffers requested in REQBUFS ioctl
 * @streaming: is streaming in progress?
 * @input: capture input type, grp_id of the attached subdev
 * @user_subdev_api: true अगर subdevs are not configured by the host driver
 */
काष्ठा fimc_vid_cap अणु
	काष्ठा fimc_ctx			*ctx;
	काष्ठा v4l2_subdev		subdev;
	काष्ठा exynos_video_entity	ve;
	काष्ठा media_pad		vd_pad;
	काष्ठा media_pad		sd_pads[FIMC_SD_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt	ci_fmt;
	काष्ठा v4l2_mbus_framefmt	wb_fmt;
	काष्ठा fimc_source_info		source_config;
	काष्ठा list_head		pending_buf_q;
	काष्ठा list_head		active_buf_q;
	काष्ठा vb2_queue		vbq;
	पूर्णांक				active_buf_cnt;
	पूर्णांक				buf_index;
	अचिन्हित पूर्णांक			frame_count;
	अचिन्हित पूर्णांक			reqbufs_count;
	bool				streaming;
	u32				input;
	bool				user_subdev_api;
पूर्ण;

/**
 *  काष्ठा fimc_pix_limit - image pixel size limits in various IP configurations
 *
 *  @scaler_en_w: max input pixel width when the scaler is enabled
 *  @scaler_dis_w: max input pixel width when the scaler is disabled
 *  @in_rot_en_h: max input width with the input rotator is on
 *  @in_rot_dis_w: max input width with the input rotator is off
 *  @out_rot_en_w: max output width with the output rotator on
 *  @out_rot_dis_w: max output width with the output rotator off
 */
काष्ठा fimc_pix_limit अणु
	u16 scaler_en_w;
	u16 scaler_dis_w;
	u16 in_rot_en_h;
	u16 in_rot_dis_w;
	u16 out_rot_en_w;
	u16 out_rot_dis_w;
पूर्ण;

/**
 * काष्ठा fimc_variant - FIMC device variant inक्रमmation
 * @has_inp_rot: set अगर has input rotator
 * @has_out_rot: set अगर has output rotator
 * @has_मुख्यscaler_ext: 1 अगर extended मुख्यscaler ratios in CIEXTEN रेजिस्टर
 *			 are present in this IP revision
 * @has_cam_अगर: set अगर this instance has a camera input पूर्णांकerface
 * @has_isp_wb: set अगर this instance has ISP ग_लिखोback input
 * @pix_limit: pixel size स्थिरraपूर्णांकs क्रम the scaler
 * @min_inp_pixsize: minimum input pixel size
 * @min_out_pixsize: minimum output pixel size
 * @hor_offs_align: horizontal pixel offset alignment
 * @min_vsize_align: minimum vertical pixel size alignment
 */
काष्ठा fimc_variant अणु
	अचिन्हित पूर्णांक	has_inp_rot:1;
	अचिन्हित पूर्णांक	has_out_rot:1;
	अचिन्हित पूर्णांक	has_मुख्यscaler_ext:1;
	अचिन्हित पूर्णांक	has_cam_अगर:1;
	अचिन्हित पूर्णांक	has_isp_wb:1;
	स्थिर काष्ठा fimc_pix_limit *pix_limit;
	u16		min_inp_pixsize;
	u16		min_out_pixsize;
	u16		hor_offs_align;
	u16		min_vsize_align;
पूर्ण;

/**
 * काष्ठा fimc_drvdata - per device type driver data
 * @variant: variant inक्रमmation क्रम this device
 * @num_entities: number of fimc instances available in a SoC
 * @lclk_frequency: local bus घड़ी frequency
 * @cistatus2: 1 अगर the FIMC IPs have CISTATUS2 रेजिस्टर
 * @dma_pix_hoff: the horizontal DMA offset unit: 1 - pixels, 0 - bytes
 * @alpha_color: 1 अगर alpha color component is supported
 * @out_buf_count: maximum number of output DMA buffers supported
 */
काष्ठा fimc_drvdata अणु
	स्थिर काष्ठा fimc_variant *variant[FIMC_MAX_DEVS];
	पूर्णांक num_entities;
	अचिन्हित दीर्घ lclk_frequency;
	/* Fields common to all FIMC IP instances */
	u8 cistatus2;
	u8 dma_pix_hoff;
	u8 alpha_color;
	u8 out_buf_count;
पूर्ण;

#घोषणा fimc_get_drvdata(_pdev) \
	((काष्ठा fimc_drvdata *) platक्रमm_get_device_id(_pdev)->driver_data)

काष्ठा fimc_ctx;

/**
 * काष्ठा fimc_dev - असलtraction क्रम FIMC entity
 * @slock:	the spinlock protecting this data काष्ठाure
 * @lock:	the mutex protecting this data काष्ठाure
 * @pdev:	poपूर्णांकer to the FIMC platक्रमm device
 * @pdata:	poपूर्णांकer to the device platक्रमm data
 * @sysreg:	poपूर्णांकer to the SYSREG regmap
 * @variant:	the IP variant inक्रमmation
 * @drv_data:	driver data
 * @id:		FIMC device index (0..FIMC_MAX_DEVS)
 * @घड़ी:	घड़ीs required क्रम FIMC operation
 * @regs:	the mapped hardware रेजिस्टरs
 * @irq_queue:	पूर्णांकerrupt handler रुकोqueue
 * @v4l2_dev:	root v4l2_device
 * @m2m:	memory-to-memory V4L2 device inक्रमmation
 * @vid_cap:	camera capture device inक्रमmation
 * @state:	flags used to synchronize m2m and capture mode operation
 */
काष्ठा fimc_dev अणु
	spinlock_t			slock;
	काष्ठा mutex			lock;
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा s5p_platक्रमm_fimc	*pdata;
	काष्ठा regmap			*sysreg;
	स्थिर काष्ठा fimc_variant	*variant;
	स्थिर काष्ठा fimc_drvdata	*drv_data;
	पूर्णांक				id;
	काष्ठा clk			*घड़ी[MAX_FIMC_CLOCKS];
	व्योम __iomem			*regs;
	रुको_queue_head_t		irq_queue;
	काष्ठा v4l2_device		*v4l2_dev;
	काष्ठा fimc_m2m_device		m2m;
	काष्ठा fimc_vid_cap		vid_cap;
	अचिन्हित दीर्घ			state;
पूर्ण;

/**
 * काष्ठा fimc_ctrls - v4l2 controls काष्ठाure
 * @handler: the control handler
 * @colorfx: image effect control
 * @colorfx_cbcr: Cb/Cr coefficients control
 * @rotate: image rotation control
 * @hflip: horizontal flip control
 * @vflip: vertical flip control
 * @alpha: RGB alpha control
 * @पढ़ोy: true अगर @handler is initialized
 */
काष्ठा fimc_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *colorfx;
		काष्ठा v4l2_ctrl *colorfx_cbcr;
	पूर्ण;
	काष्ठा v4l2_ctrl *rotate;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *alpha;
	bool पढ़ोy;
पूर्ण;

/**
 * काष्ठा fimc_ctx - the device context data
 * @s_frame:		source frame properties
 * @d_frame:		destination frame properties
 * @out_order_1p:	output 1-plane YCBCR order
 * @out_order_2p:	output 2-plane YCBCR order
 * @in_order_1p:	input 1-plane YCBCR order
 * @in_order_2p:	input 2-plane YCBCR order
 * @in_path:		input mode (DMA or camera)
 * @out_path:		output mode (DMA or FIFO)
 * @scaler:		image scaler properties
 * @effect:		image effect
 * @rotation:		image घड़ीwise rotation in degrees
 * @hflip:		indicates image horizontal flip अगर set
 * @vflip:		indicates image vertical flip अगर set
 * @flags:		additional flags क्रम image conversion
 * @state:		flags to keep track of user configuration
 * @fimc_dev:		the FIMC device this context applies to
 * @fh:			v4l2 file handle
 * @ctrls:		v4l2 controls काष्ठाure
 */
काष्ठा fimc_ctx अणु
	काष्ठा fimc_frame	s_frame;
	काष्ठा fimc_frame	d_frame;
	u32			out_order_1p;
	u32			out_order_2p;
	u32			in_order_1p;
	u32			in_order_2p;
	क्रमागत fimc_datapath	in_path;
	क्रमागत fimc_datapath	out_path;
	काष्ठा fimc_scaler	scaler;
	काष्ठा fimc_effect	effect;
	पूर्णांक			rotation;
	अचिन्हित पूर्णांक		hflip:1;
	अचिन्हित पूर्णांक		vflip:1;
	u32			flags;
	u32			state;
	काष्ठा fimc_dev		*fimc_dev;
	काष्ठा v4l2_fh		fh;
	काष्ठा fimc_ctrls	ctrls;
पूर्ण;

#घोषणा fh_to_ctx(__fh) container_of(__fh, काष्ठा fimc_ctx, fh)

अटल अंतरभूत व्योम set_frame_bounds(काष्ठा fimc_frame *f, u32 width, u32 height)
अणु
	f->o_width  = width;
	f->o_height = height;
	f->f_width  = width;
	f->f_height = height;
पूर्ण

अटल अंतरभूत व्योम set_frame_crop(काष्ठा fimc_frame *f,
				  u32 left, u32 top, u32 width, u32 height)
अणु
	f->offs_h = left;
	f->offs_v = top;
	f->width  = width;
	f->height = height;
पूर्ण

अटल अंतरभूत u32 fimc_get_क्रमmat_depth(काष्ठा fimc_fmt *ff)
अणु
	u32 i, depth = 0;

	अगर (ff != शून्य)
		क्रम (i = 0; i < ff->colplanes; i++)
			depth += ff->depth[i];
	वापस depth;
पूर्ण

अटल अंतरभूत bool fimc_capture_active(काष्ठा fimc_dev *fimc)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&fimc->slock, flags);
	ret = !!(fimc->state & (1 << ST_CAPT_RUN) ||
		 fimc->state & (1 << ST_CAPT_PEND));
	spin_unlock_irqrestore(&fimc->slock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम fimc_ctx_state_set(u32 state, काष्ठा fimc_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->fimc_dev->slock, flags);
	ctx->state |= state;
	spin_unlock_irqrestore(&ctx->fimc_dev->slock, flags);
पूर्ण

अटल अंतरभूत bool fimc_ctx_state_is_set(u32 mask, काष्ठा fimc_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&ctx->fimc_dev->slock, flags);
	ret = (ctx->state & mask) == mask;
	spin_unlock_irqrestore(&ctx->fimc_dev->slock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक tiled_fmt(काष्ठा fimc_fmt *fmt)
अणु
	वापस fmt->fourcc == V4L2_PIX_FMT_NV12MT;
पूर्ण

अटल अंतरभूत bool fimc_jpeg_fourcc(u32 pixelक्रमmat)
अणु
	वापस (pixelक्रमmat == V4L2_PIX_FMT_JPEG ||
		pixelक्रमmat == V4L2_PIX_FMT_S5C_UYVY_JPG);
पूर्ण

अटल अंतरभूत bool fimc_user_defined_mbus_fmt(u32 code)
अणु
	वापस (code == MEDIA_BUS_FMT_JPEG_1X8 ||
		code == MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8);
पूर्ण

/* Return the alpha component bit mask */
अटल अंतरभूत पूर्णांक fimc_get_alpha_mask(काष्ठा fimc_fmt *fmt)
अणु
	चयन (fmt->color) अणु
	हाल FIMC_FMT_RGB444:	वापस 0x0f;
	हाल FIMC_FMT_RGB555:	वापस 0x01;
	हाल FIMC_FMT_RGB888:	वापस 0xff;
	शेष:		वापस 0;
	पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा fimc_frame *ctx_get_frame(काष्ठा fimc_ctx *ctx,
					       क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_frame *frame;

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ||
	    type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		अगर (fimc_ctx_state_is_set(FIMC_CTX_M2M, ctx))
			frame = &ctx->s_frame;
		अन्यथा
			वापस ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
		   type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		frame = &ctx->d_frame;
	पूर्ण अन्यथा अणु
		v4l2_err(ctx->fimc_dev->v4l2_dev,
			"Wrong buffer/video queue type (%d)\n", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस frame;
पूर्ण

/* -----------------------------------------------------*/
/* fimc-core.c */
पूर्णांक fimc_vidioc_क्रमागत_fmt_mplane(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f);
पूर्णांक fimc_ctrls_create(काष्ठा fimc_ctx *ctx);
व्योम fimc_ctrls_delete(काष्ठा fimc_ctx *ctx);
व्योम fimc_ctrls_activate(काष्ठा fimc_ctx *ctx, bool active);
व्योम fimc_alpha_ctrl_update(काष्ठा fimc_ctx *ctx);
व्योम __fimc_get_क्रमmat(काष्ठा fimc_frame *frame, काष्ठा v4l2_क्रमmat *f);
व्योम fimc_adjust_mplane_क्रमmat(काष्ठा fimc_fmt *fmt, u32 width, u32 height,
			       काष्ठा v4l2_pix_क्रमmat_mplane *pix);
काष्ठा fimc_fmt *fimc_find_क्रमmat(स्थिर u32 *pixelक्रमmat, स्थिर u32 *mbus_code,
				  अचिन्हित पूर्णांक mask, पूर्णांक index);
काष्ठा fimc_fmt *fimc_get_क्रमmat(अचिन्हित पूर्णांक index);

पूर्णांक fimc_check_scaler_ratio(काष्ठा fimc_ctx *ctx, पूर्णांक sw, पूर्णांक sh,
			    पूर्णांक dw, पूर्णांक dh, पूर्णांक rotation);
पूर्णांक fimc_set_scaler_info(काष्ठा fimc_ctx *ctx);
पूर्णांक fimc_prepare_config(काष्ठा fimc_ctx *ctx, u32 flags);
पूर्णांक fimc_prepare_addr(काष्ठा fimc_ctx *ctx, काष्ठा vb2_buffer *vb,
		      काष्ठा fimc_frame *frame, काष्ठा fimc_addr *addr);
व्योम fimc_prepare_dma_offset(काष्ठा fimc_ctx *ctx, काष्ठा fimc_frame *f);
व्योम fimc_set_yuv_order(काष्ठा fimc_ctx *ctx);
व्योम fimc_capture_irq_handler(काष्ठा fimc_dev *fimc, पूर्णांक deq_buf);

पूर्णांक fimc_रेजिस्टर_m2m_device(काष्ठा fimc_dev *fimc,
			     काष्ठा v4l2_device *v4l2_dev);
व्योम fimc_unरेजिस्टर_m2m_device(काष्ठा fimc_dev *fimc);
पूर्णांक fimc_रेजिस्टर_driver(व्योम);
व्योम fimc_unरेजिस्टर_driver(व्योम);

#अगर_घोषित CONFIG_MFD_SYSCON
अटल अंतरभूत काष्ठा regmap * fimc_get_sysreg_regmap(काष्ठा device_node *node)
अणु
	वापस syscon_regmap_lookup_by_phandle(node, "samsung,sysreg");
पूर्ण
#अन्यथा
#घोषणा fimc_get_sysreg_regmap(node) (शून्य)
#पूर्ण_अगर

/* -----------------------------------------------------*/
/* fimc-m2m.c */
व्योम fimc_m2m_job_finish(काष्ठा fimc_ctx *ctx, पूर्णांक vb_state);

/* -----------------------------------------------------*/
/* fimc-capture.c					*/
पूर्णांक fimc_initialize_capture_subdev(काष्ठा fimc_dev *fimc);
व्योम fimc_unरेजिस्टर_capture_subdev(काष्ठा fimc_dev *fimc);
पूर्णांक fimc_capture_ctrls_create(काष्ठा fimc_dev *fimc);
व्योम fimc_sensor_notअगरy(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक notअगरication,
			व्योम *arg);
पूर्णांक fimc_capture_suspend(काष्ठा fimc_dev *fimc);
पूर्णांक fimc_capture_resume(काष्ठा fimc_dev *fimc);

/*
 * Buffer list manipulation functions. Must be called with fimc.slock held.
 */

/**
 * fimc_active_queue_add - add buffer to the capture active buffers queue
 * @vid_cap:	camera capture device inक्रमmation
 * @buf: buffer to add to the active buffers list
 */
अटल अंतरभूत व्योम fimc_active_queue_add(काष्ठा fimc_vid_cap *vid_cap,
					 काष्ठा fimc_vid_buffer *buf)
अणु
	list_add_tail(&buf->list, &vid_cap->active_buf_q);
	vid_cap->active_buf_cnt++;
पूर्ण

/**
 * fimc_active_queue_pop - pop buffer from the capture active buffers queue
 * @vid_cap:	camera capture device inक्रमmation
 *
 * The caller must assure the active_buf_q list is not empty.
 */
अटल अंतरभूत काष्ठा fimc_vid_buffer *fimc_active_queue_pop(
				    काष्ठा fimc_vid_cap *vid_cap)
अणु
	काष्ठा fimc_vid_buffer *buf;
	buf = list_entry(vid_cap->active_buf_q.next,
			 काष्ठा fimc_vid_buffer, list);
	list_del(&buf->list);
	vid_cap->active_buf_cnt--;
	वापस buf;
पूर्ण

/**
 * fimc_pending_queue_add - add buffer to the capture pending buffers queue
 * @vid_cap:	camera capture device inक्रमmation
 * @buf: buffer to add to the pending buffers list
 */
अटल अंतरभूत व्योम fimc_pending_queue_add(काष्ठा fimc_vid_cap *vid_cap,
					  काष्ठा fimc_vid_buffer *buf)
अणु
	list_add_tail(&buf->list, &vid_cap->pending_buf_q);
पूर्ण

/**
 * fimc_pending_queue_pop - pop buffer from the capture pending buffers queue
 * @vid_cap:	camera capture device inक्रमmation
 *
 * The caller must assure the pending_buf_q list is not empty.
 */
अटल अंतरभूत काष्ठा fimc_vid_buffer *fimc_pending_queue_pop(
				     काष्ठा fimc_vid_cap *vid_cap)
अणु
	काष्ठा fimc_vid_buffer *buf;
	buf = list_entry(vid_cap->pending_buf_q.next,
			काष्ठा fimc_vid_buffer, list);
	list_del(&buf->list);
	वापस buf;
पूर्ण

#पूर्ण_अगर /* FIMC_CORE_H_ */
