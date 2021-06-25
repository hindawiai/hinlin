<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 *
 * Copyright (C) 2005-2007 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __LINUX_DMA_IPU_DMA_H
#घोषणा __LINUX_DMA_IPU_DMA_H

#समावेश <linux/types.h>
#समावेश <linux/dmaengine.h>

/* IPU DMA Controller channel definitions. */
क्रमागत ipu_channel अणु
	IDMAC_IC_0 = 0,		/* IC (encoding task) to memory */
	IDMAC_IC_1 = 1,		/* IC (viewfinder task) to memory */
	IDMAC_ADC_0 = 1,
	IDMAC_IC_2 = 2,
	IDMAC_ADC_1 = 2,
	IDMAC_IC_3 = 3,
	IDMAC_IC_4 = 4,
	IDMAC_IC_5 = 5,
	IDMAC_IC_6 = 6,
	IDMAC_IC_7 = 7,		/* IC (sensor data) to memory */
	IDMAC_IC_8 = 8,
	IDMAC_IC_9 = 9,
	IDMAC_IC_10 = 10,
	IDMAC_IC_11 = 11,
	IDMAC_IC_12 = 12,
	IDMAC_IC_13 = 13,
	IDMAC_SDC_0 = 14,	/* Background synchronous display data */
	IDMAC_SDC_1 = 15,	/* Foreground data (overlay) */
	IDMAC_SDC_2 = 16,
	IDMAC_SDC_3 = 17,
	IDMAC_ADC_2 = 18,
	IDMAC_ADC_3 = 19,
	IDMAC_ADC_4 = 20,
	IDMAC_ADC_5 = 21,
	IDMAC_ADC_6 = 22,
	IDMAC_ADC_7 = 23,
	IDMAC_PF_0 = 24,
	IDMAC_PF_1 = 25,
	IDMAC_PF_2 = 26,
	IDMAC_PF_3 = 27,
	IDMAC_PF_4 = 28,
	IDMAC_PF_5 = 29,
	IDMAC_PF_6 = 30,
	IDMAC_PF_7 = 31,
पूर्ण;

/* Order signअगरicant! */
क्रमागत ipu_channel_status अणु
	IPU_CHANNEL_FREE,
	IPU_CHANNEL_INITIALIZED,
	IPU_CHANNEL_READY,
	IPU_CHANNEL_ENABLED,
पूर्ण;

#घोषणा IPU_CHANNELS_NUM 32

क्रमागत pixel_fmt अणु
	/* 1 byte */
	IPU_PIX_FMT_GENERIC,
	IPU_PIX_FMT_RGB332,
	IPU_PIX_FMT_YUV420P,
	IPU_PIX_FMT_YUV422P,
	IPU_PIX_FMT_YUV420P2,
	IPU_PIX_FMT_YVU422P,
	/* 2 bytes */
	IPU_PIX_FMT_RGB565,
	IPU_PIX_FMT_RGB666,
	IPU_PIX_FMT_BGR666,
	IPU_PIX_FMT_YUYV,
	IPU_PIX_FMT_UYVY,
	/* 3 bytes */
	IPU_PIX_FMT_RGB24,
	IPU_PIX_FMT_BGR24,
	/* 4 bytes */
	IPU_PIX_FMT_GENERIC_32,
	IPU_PIX_FMT_RGB32,
	IPU_PIX_FMT_BGR32,
	IPU_PIX_FMT_ABGR32,
	IPU_PIX_FMT_BGRA32,
	IPU_PIX_FMT_RGBA32,
पूर्ण;

क्रमागत ipu_color_space अणु
	IPU_COLORSPACE_RGB,
	IPU_COLORSPACE_YCBCR,
	IPU_COLORSPACE_YUV
पूर्ण;

/*
 * Enumeration of IPU rotation modes
 */
क्रमागत ipu_rotate_mode अणु
	/* Note the क्रमागत values correspond to BAM value */
	IPU_ROTATE_NONE = 0,
	IPU_ROTATE_VERT_FLIP = 1,
	IPU_ROTATE_HORIZ_FLIP = 2,
	IPU_ROTATE_180 = 3,
	IPU_ROTATE_90_RIGHT = 4,
	IPU_ROTATE_90_RIGHT_VFLIP = 5,
	IPU_ROTATE_90_RIGHT_HFLIP = 6,
	IPU_ROTATE_90_LEFT = 7,
पूर्ण;

/*
 * Enumeration of DI ports क्रम ADC.
 */
क्रमागत display_port अणु
	DISP0,
	DISP1,
	DISP2,
	DISP3
पूर्ण;

काष्ठा idmac_video_param अणु
	अचिन्हित लघु		in_width;
	अचिन्हित लघु		in_height;
	uपूर्णांक32_t		in_pixel_fmt;
	अचिन्हित लघु		out_width;
	अचिन्हित लघु		out_height;
	uपूर्णांक32_t		out_pixel_fmt;
	अचिन्हित लघु		out_stride;
	bool			graphics_combine_en;
	bool			global_alpha_en;
	bool			key_color_en;
	क्रमागत display_port	disp;
	अचिन्हित लघु		out_left;
	अचिन्हित लघु		out_top;
पूर्ण;

/*
 * Union of initialization parameters क्रम a logical channel. So far only video
 * parameters are used.
 */
जोड़ ipu_channel_param अणु
	काष्ठा idmac_video_param video;
पूर्ण;

काष्ठा idmac_tx_desc अणु
	काष्ठा dma_async_tx_descriptor	txd;
	काष्ठा scatterlist		*sg;	/* scatterlist क्रम this */
	अचिन्हित पूर्णांक			sg_len;	/* tx-descriptor. */
	काष्ठा list_head		list;
पूर्ण;

काष्ठा idmac_channel अणु
	काष्ठा dma_chan		dma_chan;
	dma_cookie_t		completed;	/* last completed cookie	   */
	जोड़ ipu_channel_param	params;
	क्रमागत ipu_channel	link;	/* input channel, linked to the output	   */
	क्रमागत ipu_channel_status	status;
	व्योम			*client;	/* Only one client per channel	   */
	अचिन्हित पूर्णांक		n_tx_desc;
	काष्ठा idmac_tx_desc	*desc;		/* allocated tx-descriptors	   */
	काष्ठा scatterlist	*sg[2];	/* scatterlist elements in buffer-0 and -1 */
	काष्ठा list_head	मुक्त_list;	/* मुक्त tx-descriptors		   */
	काष्ठा list_head	queue;		/* queued tx-descriptors	   */
	spinlock_t		lock;		/* protects sg[0,1], queue	   */
	काष्ठा mutex		chan_mutex; /* protects status, cookie, मुक्त_list  */
	bool			sec_chan_en;
	पूर्णांक			active_buffer;
	अचिन्हित पूर्णांक		eof_irq;
	अक्षर			eof_name[16];	/* खातापूर्ण IRQ name क्रम request_irq()  */
पूर्ण;

#घोषणा to_tx_desc(tx) container_of(tx, काष्ठा idmac_tx_desc, txd)
#घोषणा to_idmac_chan(c) container_of(c, काष्ठा idmac_channel, dma_chan)

#पूर्ण_अगर /* __LINUX_DMA_IPU_DMA_H */
