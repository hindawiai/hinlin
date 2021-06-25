<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * header file क्रम Samsung EXYNOS5 SoC series G-Scaler driver

 */

#अगर_अघोषित GSC_CORE_H_
#घोषणा GSC_CORE_H_

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "gsc-regs.h"

#घोषणा CONFIG_VB2_GSC_DMA_CONTIG	1
#घोषणा GSC_MODULE_NAME			"exynos-gsc"

#घोषणा GSC_SHUTDOWN_TIMEOUT		((100*HZ)/1000)
#घोषणा GSC_MAX_DEVS			4
#घोषणा GSC_MAX_CLOCKS			4
#घोषणा GSC_M2M_BUF_NUM			0
#घोषणा GSC_MAX_CTRL_NUM		10
#घोषणा GSC_SC_ALIGN_4			4
#घोषणा GSC_SC_ALIGN_2			2
#घोषणा DEFAULT_CSC_EQ			1
#घोषणा DEFAULT_CSC_RANGE		1

#घोषणा GSC_PARAMS			(1 << 0)
#घोषणा GSC_SRC_FMT			(1 << 1)
#घोषणा GSC_DST_FMT			(1 << 2)
#घोषणा GSC_CTX_M2M			(1 << 3)
#घोषणा GSC_CTX_STOP_REQ		(1 << 6)
#घोषणा	GSC_CTX_ABORT			(1 << 7)

क्रमागत gsc_dev_flags अणु
	/* क्रम m2m node */
	ST_M2M_OPEN,
	ST_M2M_RUN,
	ST_M2M_PEND,
	ST_M2M_SUSPENDED,
	ST_M2M_SUSPENDING,
पूर्ण;

क्रमागत gsc_irq अणु
	GSC_IRQ_DONE,
	GSC_IRQ_OVERRUN
पूर्ण;

/**
 * क्रमागत gsc_datapath - the path of data used क्रम G-Scaler
 * @GSC_CAMERA: from camera
 * @GSC_DMA: from/to DMA
 * @GSC_WRITEBACK: from FIMD
 */
क्रमागत gsc_datapath अणु
	GSC_CAMERA = 0x1,
	GSC_DMA,
	GSC_WRITEBACK,
पूर्ण;

क्रमागत gsc_color_fmt अणु
	GSC_RGB = 0x1,
	GSC_YUV420 = 0x2,
	GSC_YUV422 = 0x4,
	GSC_YUV444 = 0x8,
पूर्ण;

क्रमागत gsc_yuv_fmt अणु
	GSC_LSB_Y = 0x10,
	GSC_LSB_C,
	GSC_CBCR = 0x20,
	GSC_CRCB,
पूर्ण;

#घोषणा fh_to_ctx(__fh) container_of(__fh, काष्ठा gsc_ctx, fh)
#घोषणा is_rgb(x) (!!((x) & 0x1))
#घोषणा is_yuv420(x) (!!((x) & 0x2))
#घोषणा is_yuv422(x) (!!((x) & 0x4))

#घोषणा gsc_m2m_active(dev)	test_bit(ST_M2M_RUN, &(dev)->state)
#घोषणा gsc_m2m_pending(dev)	test_bit(ST_M2M_PEND, &(dev)->state)
#घोषणा gsc_m2m_खोलोed(dev)	test_bit(ST_M2M_OPEN, &(dev)->state)

#घोषणा ctrl_to_ctx(__ctrl) \
	container_of((__ctrl)->handler, काष्ठा gsc_ctx, ctrl_handler)
/**
 * काष्ठा gsc_fmt - the driver's पूर्णांकernal color क्रमmat data
 * @mbus_code: Media Bus pixel code, -1 अगर not applicable
 * @pixelक्रमmat: the fourcc code क्रम this क्रमmat, 0 अगर not applicable
 * @color: color encoding
 * @yorder: Y/C order
 * @corder: Chrominance order control
 * @num_planes: number of physically non-contiguous data planes
 * @num_comp: number of physically contiguous data planes
 * @depth: per plane driver's private 'number of bits per pixel'
 * @flags: flags indicating which operation mode क्रमmat applies to
 */
काष्ठा gsc_fmt अणु
	u32 mbus_code;
	u32	pixelक्रमmat;
	u32	color;
	u32	yorder;
	u32	corder;
	u16	num_planes;
	u16	num_comp;
	u8	depth[VIDEO_MAX_PLANES];
	u32	flags;
पूर्ण;

/**
 * काष्ठा gsc_input_buf - the driver's video buffer
 * @vb:	videobuf2 buffer
 * @list : linked list काष्ठाure क्रम buffer queue
 * @idx : index of G-Scaler input buffer
 */
काष्ठा gsc_input_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head	list;
	पूर्णांक			idx;
पूर्ण;

/**
 * काष्ठा gsc_addr - the G-Scaler physical address set
 * @y:	 luminance plane address
 * @cb:	 Cb plane address
 * @cr:	 Cr plane address
 */
काष्ठा gsc_addr अणु
	dma_addr_t y;
	dma_addr_t cb;
	dma_addr_t cr;
पूर्ण;

/* काष्ठा gsc_ctrls - the G-Scaler control set
 * @rotate: rotation degree
 * @hflip: horizontal flip
 * @vflip: vertical flip
 * @global_alpha: the alpha value of current frame
 */
काष्ठा gsc_ctrls अणु
	काष्ठा v4l2_ctrl *rotate;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *global_alpha;
पूर्ण;

/**
 * काष्ठा gsc_scaler - the configuration data क्रम G-Scaler inetrnal scaler
 * @pre_shfactor:	pre sclaer shअगरt factor
 * @pre_hratio:		horizontal ratio of the prescaler
 * @pre_vratio:		vertical ratio of the prescaler
 * @मुख्य_hratio:	the मुख्य scaler's horizontal ratio
 * @मुख्य_vratio:	the मुख्य scaler's vertical ratio
 */
काष्ठा gsc_scaler अणु
	u32 pre_shfactor;
	u32 pre_hratio;
	u32 pre_vratio;
	u32 मुख्य_hratio;
	u32 मुख्य_vratio;
पूर्ण;

काष्ठा gsc_dev;

काष्ठा gsc_ctx;

/**
 * काष्ठा gsc_frame - source/target frame properties
 * @f_width:	SRC : SRCIMG_WIDTH, DST : OUTPUTDMA_WHOLE_IMG_WIDTH
 * @f_height:	SRC : SRCIMG_HEIGHT, DST : OUTPUTDMA_WHOLE_IMG_HEIGHT
 * @crop:	cropped(source)/scaled(destination) size
 * @payload:	image size in bytes (w x h x bpp)
 * @addr:	image frame buffer physical addresses
 * @fmt:	G-Scaler color क्रमmat poपूर्णांकer
 * @colorspace: value indicating v4l2_colorspace
 * @alpha:	frame's alpha value
 */
काष्ठा gsc_frame अणु
	u32 f_width;
	u32 f_height;
	काष्ठा v4l2_rect crop;
	अचिन्हित दीर्घ payload[VIDEO_MAX_PLANES];
	काष्ठा gsc_addr	addr;
	स्थिर काष्ठा gsc_fmt *fmt;
	u32 colorspace;
	u8 alpha;
पूर्ण;

/**
 * काष्ठा gsc_m2m_device - v4l2 memory-to-memory device data
 * @vfd: the video device node क्रम v4l2 m2m mode
 * @m2m_dev: v4l2 memory-to-memory device data
 * @ctx: hardware context data
 * @refcnt: the reference counter
 */
काष्ठा gsc_m2m_device अणु
	काष्ठा video_device	*vfd;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा gsc_ctx		*ctx;
	पूर्णांक			refcnt;
पूर्ण;

/**
 *  काष्ठा gsc_pix_max - image pixel size limits in various IP configurations
 *
 *  @org_scaler_bypass_w: max pixel width when the scaler is disabled
 *  @org_scaler_bypass_h: max pixel height when the scaler is disabled
 *  @org_scaler_input_w: max pixel width when the scaler is enabled
 *  @org_scaler_input_h: max pixel height when the scaler is enabled
 *  @real_rot_dis_w: max pixel src cropped height with the rotator is off
 *  @real_rot_dis_h: max pixel src croppped width with the rotator is off
 *  @real_rot_en_w: max pixel src cropped width with the rotator is on
 *  @real_rot_en_h: max pixel src cropped height with the rotator is on
 *  @target_rot_dis_w: max pixel dst scaled width with the rotator is off
 *  @target_rot_dis_h: max pixel dst scaled height with the rotator is off
 *  @target_rot_en_w: max pixel dst scaled width with the rotator is on
 *  @target_rot_en_h: max pixel dst scaled height with the rotator is on
 */
काष्ठा gsc_pix_max अणु
	u16 org_scaler_bypass_w;
	u16 org_scaler_bypass_h;
	u16 org_scaler_input_w;
	u16 org_scaler_input_h;
	u16 real_rot_dis_w;
	u16 real_rot_dis_h;
	u16 real_rot_en_w;
	u16 real_rot_en_h;
	u16 target_rot_dis_w;
	u16 target_rot_dis_h;
	u16 target_rot_en_w;
	u16 target_rot_en_h;
पूर्ण;

/**
 *  काष्ठा gsc_pix_min - image pixel size limits in various IP configurations
 *
 *  @org_w: minimum source pixel width
 *  @org_h: minimum source pixel height
 *  @real_w: minimum input crop pixel width
 *  @real_h: minimum input crop pixel height
 *  @target_rot_dis_w: minimum output scaled pixel height when rotator is off
 *  @target_rot_dis_h: minimum output scaled pixel height when rotator is off
 *  @target_rot_en_w: minimum output scaled pixel height when rotator is on
 *  @target_rot_en_h: minimum output scaled pixel height when rotator is on
 */
काष्ठा gsc_pix_min अणु
	u16 org_w;
	u16 org_h;
	u16 real_w;
	u16 real_h;
	u16 target_rot_dis_w;
	u16 target_rot_dis_h;
	u16 target_rot_en_w;
	u16 target_rot_en_h;
पूर्ण;

काष्ठा gsc_pix_align अणु
	u16 org_h;
	u16 org_w;
	u16 offset_h;
	u16 real_w;
	u16 real_h;
	u16 target_w;
	u16 target_h;
पूर्ण;

/*
 * काष्ठा gsc_variant - G-Scaler variant inक्रमmation
 */
काष्ठा gsc_variant अणु
	काष्ठा gsc_pix_max *pix_max;
	काष्ठा gsc_pix_min *pix_min;
	काष्ठा gsc_pix_align *pix_align;
	u16		in_buf_cnt;
	u16		out_buf_cnt;
	u16		sc_up_max;
	u16		sc_करोwn_max;
	u16		poly_sc_करोwn_max;
	u16		pre_sc_करोwn_max;
	u16		local_sc_करोwn;
पूर्ण;

/**
 * काष्ठा gsc_driverdata - per device type driver data क्रम init समय.
 *
 * @variant: the variant inक्रमmation क्रम this driver.
 * @num_entities: the number of g-scalers
 * @clk_names: घड़ी names
 * @num_घड़ीs: the number of घड़ीs in @clk_names
 * @num_entities: the number of g-scalers
 */
काष्ठा gsc_driverdata अणु
	काष्ठा gsc_variant *variant[GSC_MAX_DEVS];
	स्थिर अक्षर	*clk_names[GSC_MAX_CLOCKS];
	पूर्णांक		num_घड़ीs;
	पूर्णांक		num_entities;
पूर्ण;

/**
 * काष्ठा gsc_dev - असलtraction क्रम G-Scaler entity
 * @slock:	the spinlock protecting this data काष्ठाure
 * @lock:	the mutex protecting this data काष्ठाure
 * @pdev:	poपूर्णांकer to the G-Scaler platक्रमm device
 * @variant:	the IP variant inक्रमmation
 * @id:		G-Scaler device index (0..GSC_MAX_DEVS)
 * @num_घड़ीs:	number of घड़ीs required क्रम G-Scaler operation
 * @घड़ी:	घड़ीs required क्रम G-Scaler operation
 * @regs:	the mapped hardware रेजिस्टरs
 * @irq_queue:	पूर्णांकerrupt handler रुकोqueue
 * @m2m:	memory-to-memory V4L2 device inक्रमmation
 * @state:	flags used to synchronize m2m and capture mode operation
 * @vdev:	video device क्रम G-Scaler instance
 * @v4l2_dev:	v4l2_device क्रम G-Scaler instance
 */
काष्ठा gsc_dev अणु
	spinlock_t			slock;
	काष्ठा mutex			lock;
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा gsc_variant		*variant;
	u16				id;
	पूर्णांक				num_घड़ीs;
	काष्ठा clk			*घड़ी[GSC_MAX_CLOCKS];
	व्योम __iomem			*regs;
	रुको_queue_head_t		irq_queue;
	काष्ठा gsc_m2m_device		m2m;
	अचिन्हित दीर्घ			state;
	काष्ठा video_device		vdev;
	काष्ठा v4l2_device		v4l2_dev;
पूर्ण;

/**
 * काष्ठा gsc_ctx - the device context data
 * @s_frame:		source frame properties
 * @d_frame:		destination frame properties
 * @in_path:		input mode (DMA or camera)
 * @out_path:		output mode (DMA or FIFO)
 * @scaler:		image scaler properties
 * @flags:		additional flags क्रम image conversion
 * @state:		flags to keep track of user configuration
 * @rotation:		rotation
 * @hflip:		horizontal flip
 * @vflip:		vertical flip
 * @gsc_dev:		the G-Scaler device this context applies to
 * @m2m_ctx:		memory-to-memory device context
 * @fh:                 v4l2 file handle
 * @ctrl_handler:       v4l2 controls handler
 * @gsc_ctrls:		G-Scaler control set
 * @ctrls_rdy:          true अगर the control handler is initialized
 * @out_colorspace:     the colorspace of the OUTPUT queue
 */
काष्ठा gsc_ctx अणु
	काष्ठा gsc_frame	s_frame;
	काष्ठा gsc_frame	d_frame;
	क्रमागत gsc_datapath	in_path;
	क्रमागत gsc_datapath	out_path;
	काष्ठा gsc_scaler	scaler;
	u32			flags;
	u32			state;
	पूर्णांक			rotation;
	अचिन्हित पूर्णांक		hflip:1;
	अचिन्हित पूर्णांक		vflip:1;
	काष्ठा gsc_dev		*gsc_dev;
	काष्ठा v4l2_m2m_ctx	*m2m_ctx;
	काष्ठा v4l2_fh		fh;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा gsc_ctrls	gsc_ctrls;
	bool			ctrls_rdy;
	क्रमागत v4l2_colorspace out_colorspace;
पूर्ण;

व्योम gsc_set_prefbuf(काष्ठा gsc_dev *gsc, काष्ठा gsc_frame *frm);
पूर्णांक gsc_रेजिस्टर_m2m_device(काष्ठा gsc_dev *gsc);
व्योम gsc_unरेजिस्टर_m2m_device(काष्ठा gsc_dev *gsc);
व्योम gsc_m2m_job_finish(काष्ठा gsc_ctx *ctx, पूर्णांक vb_state);

u32 get_plane_size(काष्ठा gsc_frame *fr, अचिन्हित पूर्णांक plane);
स्थिर काष्ठा gsc_fmt *get_क्रमmat(पूर्णांक index);
स्थिर काष्ठा gsc_fmt *find_fmt(u32 *pixelक्रमmat, u32 *mbus_code, u32 index);
पूर्णांक gsc_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f);
पूर्णांक gsc_try_fmt_mplane(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_क्रमmat *f);
व्योम gsc_set_frame_size(काष्ठा gsc_frame *frame, पूर्णांक width, पूर्णांक height);
पूर्णांक gsc_g_fmt_mplane(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_क्रमmat *f);
व्योम gsc_check_crop_change(u32 पंचांगp_w, u32 पंचांगp_h, u32 *w, u32 *h);
पूर्णांक gsc_try_selection(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_selection *s);
पूर्णांक gsc_cal_prescaler_ratio(काष्ठा gsc_variant *var, u32 src, u32 dst,
							u32 *ratio);
व्योम gsc_get_prescaler_shfactor(u32 hratio, u32 vratio, u32 *sh);
व्योम gsc_check_src_scale_info(काष्ठा gsc_variant *var,
				काष्ठा gsc_frame *s_frame,
				u32 *wratio, u32 tx, u32 ty, u32 *hratio);
पूर्णांक gsc_check_scaler_ratio(काष्ठा gsc_variant *var, पूर्णांक sw, पूर्णांक sh, पूर्णांक dw,
			   पूर्णांक dh, पूर्णांक rot, पूर्णांक out_path);
पूर्णांक gsc_set_scaler_info(काष्ठा gsc_ctx *ctx);
पूर्णांक gsc_ctrls_create(काष्ठा gsc_ctx *ctx);
व्योम gsc_ctrls_delete(काष्ठा gsc_ctx *ctx);
पूर्णांक gsc_prepare_addr(काष्ठा gsc_ctx *ctx, काष्ठा vb2_buffer *vb,
		     काष्ठा gsc_frame *frame, काष्ठा gsc_addr *addr);

अटल अंतरभूत व्योम gsc_ctx_state_lock_set(u32 state, काष्ठा gsc_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->gsc_dev->slock, flags);
	ctx->state |= state;
	spin_unlock_irqrestore(&ctx->gsc_dev->slock, flags);
पूर्ण

अटल अंतरभूत व्योम gsc_ctx_state_lock_clear(u32 state, काष्ठा gsc_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->gsc_dev->slock, flags);
	ctx->state &= ~state;
	spin_unlock_irqrestore(&ctx->gsc_dev->slock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_tiled(स्थिर काष्ठा gsc_fmt *fmt)
अणु
	वापस fmt->pixelक्रमmat == V4L2_PIX_FMT_NV12MT_16X16;
पूर्ण

अटल अंतरभूत व्योम gsc_hw_enable_control(काष्ठा gsc_dev *dev, bool on)
अणु
	u32 cfg = पढ़ोl(dev->regs + GSC_ENABLE);

	अगर (on)
		cfg |= GSC_ENABLE_ON;
	अन्यथा
		cfg &= ~GSC_ENABLE_ON;

	ग_लिखोl(cfg, dev->regs + GSC_ENABLE);
पूर्ण

अटल अंतरभूत पूर्णांक gsc_hw_get_irq_status(काष्ठा gsc_dev *dev)
अणु
	u32 cfg = पढ़ोl(dev->regs + GSC_IRQ);
	अगर (cfg & GSC_IRQ_STATUS_OR_IRQ)
		वापस GSC_IRQ_OVERRUN;
	अन्यथा
		वापस GSC_IRQ_DONE;

पूर्ण

अटल अंतरभूत व्योम gsc_hw_clear_irq(काष्ठा gsc_dev *dev, पूर्णांक irq)
अणु
	u32 cfg = पढ़ोl(dev->regs + GSC_IRQ);
	अगर (irq == GSC_IRQ_OVERRUN)
		cfg |= GSC_IRQ_STATUS_OR_IRQ;
	अन्यथा अगर (irq == GSC_IRQ_DONE)
		cfg |= GSC_IRQ_STATUS_FRM_DONE_IRQ;
	ग_लिखोl(cfg, dev->regs + GSC_IRQ);
पूर्ण

अटल अंतरभूत bool gsc_ctx_state_is_set(u32 mask, काष्ठा gsc_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&ctx->gsc_dev->slock, flags);
	ret = (ctx->state & mask) == mask;
	spin_unlock_irqrestore(&ctx->gsc_dev->slock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा gsc_frame *ctx_get_frame(काष्ठा gsc_ctx *ctx,
					      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा gsc_frame *frame;

	अगर (V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE == type) अणु
		frame = &ctx->s_frame;
	पूर्ण अन्यथा अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == type) अणु
		frame = &ctx->d_frame;
	पूर्ण अन्यथा अणु
		pr_err("Wrong buffer/video queue type (%d)", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस frame;
पूर्ण

व्योम gsc_hw_set_sw_reset(काष्ठा gsc_dev *dev);
पूर्णांक gsc_रुको_reset(काष्ठा gsc_dev *dev);

व्योम gsc_hw_set_frm_करोne_irq_mask(काष्ठा gsc_dev *dev, bool mask);
व्योम gsc_hw_set_gsc_irq_enable(काष्ठा gsc_dev *dev, bool mask);
व्योम gsc_hw_set_input_buf_masking(काष्ठा gsc_dev *dev, u32 shअगरt, bool enable);
व्योम gsc_hw_set_output_buf_masking(काष्ठा gsc_dev *dev, u32 shअगरt, bool enable);
व्योम gsc_hw_set_input_addr(काष्ठा gsc_dev *dev, काष्ठा gsc_addr *addr,
							पूर्णांक index);
व्योम gsc_hw_set_output_addr(काष्ठा gsc_dev *dev, काष्ठा gsc_addr *addr,
							पूर्णांक index);
व्योम gsc_hw_set_input_path(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_in_size(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_in_image_rgb(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_in_image_क्रमmat(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_output_path(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_out_size(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_out_image_rgb(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_out_image_क्रमmat(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_prescaler(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_मुख्यscaler(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_rotation(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_global_alpha(काष्ठा gsc_ctx *ctx);
व्योम gsc_hw_set_sfr_update(काष्ठा gsc_ctx *ctx);

#पूर्ण_अगर /* GSC_CORE_H_ */
