<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI Camera Access Layer (CAL)
 *
 * Copyright (c) 2015-2020 Texas Instruments Inc.
 *
 * Authors:
 *	Benoit Parrot <bparrot@ti.com>
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */
#अगर_अघोषित __TI_CAL_H__
#घोषणा __TI_CAL_H__

#समावेश <linux/bitfield.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-v4l2.h>

#घोषणा CAL_MODULE_NAME			"cal"
#घोषणा CAL_NUM_CONTEXT			2
#घोषणा CAL_NUM_CSI2_PORTS		2

/*
 * The width is limited by the size of the CAL_WR_DMA_XSIZE_j.XSIZE field,
 * expressed in multiples of 64 bits. The height is limited by the size of the
 * CAL_CSI2_CTXi_j.CTXi_LINES and CAL_WR_DMA_CTRL_j.YSIZE fields, expressed in
 * lines.
 */
#घोषणा CAL_MIN_WIDTH_BYTES		16
#घोषणा CAL_MAX_WIDTH_BYTES		(8192 * 8)
#घोषणा CAL_MIN_HEIGHT_LINES		1
#घोषणा CAL_MAX_HEIGHT_LINES		16383

#घोषणा CAL_CAMERARX_PAD_SINK		0
#घोषणा CAL_CAMERARX_PAD_SOURCE		1

काष्ठा device;
काष्ठा device_node;
काष्ठा resource;
काष्ठा regmap;
काष्ठा regmap_fied;

/* CTRL_CORE_CAMERRX_CONTROL रेजिस्टर field id */
क्रमागत cal_camerarx_field अणु
	F_CTRLCLKEN,
	F_CAMMODE,
	F_LANEENABLE,
	F_CSI_MODE,
	F_MAX_FIELDS,
पूर्ण;

क्रमागत cal_dma_state अणु
	CAL_DMA_RUNNING,
	CAL_DMA_STOP_REQUESTED,
	CAL_DMA_STOP_PENDING,
	CAL_DMA_STOPPED,
पूर्ण;

काष्ठा cal_क्रमmat_info अणु
	u32	fourcc;
	u32	code;
	/* Bits per pixel */
	u8	bpp;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा cal_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer	vb;
	काष्ठा list_head	list;
पूर्ण;

/**
 * काष्ठा cal_dmaqueue - Queue of DMA buffers
 */
काष्ठा cal_dmaqueue अणु
	/**
	 * @lock: Protects all fields in the cal_dmaqueue.
	 */
	spinlock_t		lock;

	/**
	 * @queue: Buffers queued to the driver and रुकोing क्रम DMA processing.
	 * Buffers are added to the list by the vb2 .buffer_queue() operation,
	 * and move to @pending when they are scheduled क्रम the next frame.
	 */
	काष्ठा list_head	queue;
	/**
	 * @pending: Buffer provided to the hardware to DMA the next frame.
	 * Will move to @active at the end of the current frame.
	 */
	काष्ठा cal_buffer	*pending;
	/**
	 * @active: Buffer being DMA'ed to क्रम the current frame. Will be
	 * retired and given back to vb2 at the end of the current frame अगर
	 * a @pending buffer has been scheduled to replace it.
	 */
	काष्ठा cal_buffer	*active;

	/** @state: State of the DMA engine. */
	क्रमागत cal_dma_state	state;
	/** @रुको: Wait queue to संकेत a @state transition to CAL_DMA_STOPPED. */
	काष्ठा रुको_queue_head	रुको;
पूर्ण;

काष्ठा cal_camerarx_data अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक lsb;
		अचिन्हित पूर्णांक msb;
	पूर्ण fields[F_MAX_FIELDS];
	अचिन्हित पूर्णांक num_lanes;
पूर्ण;

काष्ठा cal_data अणु
	स्थिर काष्ठा cal_camerarx_data *camerarx;
	अचिन्हित पूर्णांक num_csi2_phy;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/*
 * The Camera Adaptation Layer (CAL) module is paired with one or more complex
 * I/O PHYs (CAMERARX). It contains multiple instances of CSI-2, processing and
 * DMA contexts.
 *
 * The cal_dev काष्ठाure represents the whole subप्रणाली, including the CAL and
 * the CAMERARX instances. Instances of काष्ठा cal_dev are named cal through the
 * driver.
 *
 * The cal_camerarx काष्ठाure represents one CAMERARX instance. Instances of
 * cal_camerarx are named phy through the driver.
 *
 * The cal_ctx काष्ठाure represents the combination of one CSI-2 context, one
 * processing context and one DMA context. Instance of काष्ठा cal_ctx are named
 * ctx through the driver.
 */

काष्ठा cal_camerarx अणु
	व्योम __iomem		*base;
	काष्ठा resource		*res;
	काष्ठा device		*dev;
	काष्ठा regmap_field	*fields[F_MAX_FIELDS];

	काष्ठा cal_dev		*cal;
	अचिन्हित पूर्णांक		instance;

	काष्ठा v4l2_fwnode_endpoपूर्णांक	endpoपूर्णांक;
	काष्ठा device_node	*sensor_ep_node;
	काष्ठा device_node	*sensor_node;
	काष्ठा v4l2_subdev	*sensor;
	काष्ठा media_pipeline	pipe;

	काष्ठा v4l2_subdev	subdev;
	काष्ठा media_pad	pads[2];
	काष्ठा v4l2_mbus_framefmt	क्रमmats[2];
	स्थिर काष्ठा cal_क्रमmat_info	*fmtinfo;
पूर्ण;

काष्ठा cal_dev अणु
	काष्ठा clk		*fclk;
	पूर्णांक			irq;
	व्योम __iomem		*base;
	काष्ठा resource		*res;
	काष्ठा device		*dev;

	स्थिर काष्ठा cal_data	*data;
	u32			revision;

	/* Control Module handle */
	काष्ठा regmap		*syscon_camerrx;
	u32			syscon_camerrx_offset;

	/* Camera Core Module handle */
	काष्ठा cal_camerarx	*phy[CAL_NUM_CSI2_PORTS];

	काष्ठा cal_ctx		*ctx[CAL_NUM_CONTEXT];

	काष्ठा media_device	mdev;
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा v4l2_async_notअगरier notअगरier;
पूर्ण;

/*
 * There is one cal_ctx काष्ठाure क्रम each camera core context.
 */
काष्ठा cal_ctx अणु
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा video_device	vdev;
	काष्ठा media_pad	pad;

	काष्ठा cal_dev		*cal;
	काष्ठा cal_camerarx	*phy;

	/* v4l2_ioctl mutex */
	काष्ठा mutex		mutex;

	काष्ठा cal_dmaqueue	dma;

	/* video capture */
	स्थिर काष्ठा cal_क्रमmat_info	*fmtinfo;
	/* Used to store current pixel क्रमmat */
	काष्ठा v4l2_क्रमmat	v_fmt;

	/* Current subdev क्रमागतerated क्रमmat */
	स्थिर काष्ठा cal_क्रमmat_info	**active_fmt;
	अचिन्हित पूर्णांक		num_active_fmt;

	अचिन्हित पूर्णांक		sequence;
	काष्ठा vb2_queue	vb_vidq;
	अचिन्हित पूर्णांक		index;
	अचिन्हित पूर्णांक		cport;
पूर्ण;

बाह्य अचिन्हित पूर्णांक cal_debug;
बाह्य पूर्णांक cal_video_nr;
बाह्य bool cal_mc_api;

#घोषणा cal_dbg(level, cal, fmt, arg...)				\
	करो अणु								\
		अगर (cal_debug >= (level))				\
			dev_prपूर्णांकk(KERN_DEBUG, (cal)->dev, fmt, ##arg);	\
	पूर्ण जबतक (0)
#घोषणा cal_info(cal, fmt, arg...)					\
	dev_info((cal)->dev, fmt, ##arg)
#घोषणा cal_err(cal, fmt, arg...)					\
	dev_err((cal)->dev, fmt, ##arg)

#घोषणा ctx_dbg(level, ctx, fmt, arg...)				\
	cal_dbg(level, (ctx)->cal, "ctx%u: " fmt, (ctx)->index, ##arg)
#घोषणा ctx_info(ctx, fmt, arg...)					\
	cal_info((ctx)->cal, "ctx%u: " fmt, (ctx)->index, ##arg)
#घोषणा ctx_err(ctx, fmt, arg...)					\
	cal_err((ctx)->cal, "ctx%u: " fmt, (ctx)->index, ##arg)

#घोषणा phy_dbg(level, phy, fmt, arg...)				\
	cal_dbg(level, (phy)->cal, "phy%u: " fmt, (phy)->instance, ##arg)
#घोषणा phy_info(phy, fmt, arg...)					\
	cal_info((phy)->cal, "phy%u: " fmt, (phy)->instance, ##arg)
#घोषणा phy_err(phy, fmt, arg...)					\
	cal_err((phy)->cal, "phy%u: " fmt, (phy)->instance, ##arg)

अटल अंतरभूत u32 cal_पढ़ो(काष्ठा cal_dev *cal, u32 offset)
अणु
	वापस ioपढ़ो32(cal->base + offset);
पूर्ण

अटल अंतरभूत व्योम cal_ग_लिखो(काष्ठा cal_dev *cal, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, cal->base + offset);
पूर्ण

अटल __always_अंतरभूत u32 cal_पढ़ो_field(काष्ठा cal_dev *cal, u32 offset, u32 mask)
अणु
	वापस FIELD_GET(mask, cal_पढ़ो(cal, offset));
पूर्ण

अटल अंतरभूत व्योम cal_ग_लिखो_field(काष्ठा cal_dev *cal, u32 offset, u32 value,
				   u32 mask)
अणु
	u32 val = cal_पढ़ो(cal, offset);

	val &= ~mask;
	val |= (value << __ffs(mask)) & mask;
	cal_ग_लिखो(cal, offset, val);
पूर्ण

अटल अंतरभूत व्योम cal_set_field(u32 *valp, u32 field, u32 mask)
अणु
	u32 val = *valp;

	val &= ~mask;
	val |= (field << __ffs(mask)) & mask;
	*valp = val;
पूर्ण

बाह्य स्थिर काष्ठा cal_क्रमmat_info cal_क्रमmats[];
बाह्य स्थिर अचिन्हित पूर्णांक cal_num_क्रमmats;
स्थिर काष्ठा cal_क्रमmat_info *cal_क्रमmat_by_fourcc(u32 fourcc);
स्थिर काष्ठा cal_क्रमmat_info *cal_क्रमmat_by_code(u32 code);

व्योम cal_quickdump_regs(काष्ठा cal_dev *cal);

व्योम cal_camerarx_disable(काष्ठा cal_camerarx *phy);
व्योम cal_camerarx_i913_errata(काष्ठा cal_camerarx *phy);
काष्ठा cal_camerarx *cal_camerarx_create(काष्ठा cal_dev *cal,
					 अचिन्हित पूर्णांक instance);
व्योम cal_camerarx_destroy(काष्ठा cal_camerarx *phy);

व्योम cal_ctx_set_dma_addr(काष्ठा cal_ctx *ctx, dma_addr_t addr);
व्योम cal_ctx_start(काष्ठा cal_ctx *ctx);
व्योम cal_ctx_stop(काष्ठा cal_ctx *ctx);

पूर्णांक cal_ctx_v4l2_रेजिस्टर(काष्ठा cal_ctx *ctx);
व्योम cal_ctx_v4l2_unरेजिस्टर(काष्ठा cal_ctx *ctx);
पूर्णांक cal_ctx_v4l2_init(काष्ठा cal_ctx *ctx);
व्योम cal_ctx_v4l2_cleanup(काष्ठा cal_ctx *ctx);

#पूर्ण_अगर /* __TI_CAL_H__ */
