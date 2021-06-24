<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * V4L2 Driver क्रम PXA camera host
 *
 * Copyright (C) 2006, Sascha Hauer, Pengutronix
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 * Copyright (C) 2016, Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/समय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/pxa-dma.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश <media/videobuf2-dma-sg.h>

#समावेश <linux/videodev2.h>

#समावेश <linux/platक्रमm_data/media/camera-pxa.h>

#घोषणा PXA_CAM_VERSION "0.0.6"
#घोषणा PXA_CAM_DRV_NAME "pxa27x-camera"

#घोषणा DEFAULT_WIDTH	640
#घोषणा DEFAULT_HEIGHT	480

/* Camera Interface */
#घोषणा CICR0		0x0000
#घोषणा CICR1		0x0004
#घोषणा CICR2		0x0008
#घोषणा CICR3		0x000C
#घोषणा CICR4		0x0010
#घोषणा CISR		0x0014
#घोषणा CIFR		0x0018
#घोषणा CITOR		0x001C
#घोषणा CIBR0		0x0028
#घोषणा CIBR1		0x0030
#घोषणा CIBR2		0x0038

#घोषणा CICR0_DMAEN	(1UL << 31)	/* DMA request enable */
#घोषणा CICR0_PAR_EN	(1 << 30)	/* Parity enable */
#घोषणा CICR0_SL_CAP_EN	(1 << 29)	/* Capture enable क्रम slave mode */
#घोषणा CICR0_ENB	(1 << 28)	/* Camera पूर्णांकerface enable */
#घोषणा CICR0_DIS	(1 << 27)	/* Camera पूर्णांकerface disable */
#घोषणा CICR0_SIM	(0x7 << 24)	/* Sensor पूर्णांकerface mode mask */
#घोषणा CICR0_TOM	(1 << 9)	/* Time-out mask */
#घोषणा CICR0_RDAVM	(1 << 8)	/* Receive-data-available mask */
#घोषणा CICR0_FEM	(1 << 7)	/* FIFO-empty mask */
#घोषणा CICR0_EOLM	(1 << 6)	/* End-of-line mask */
#घोषणा CICR0_PERRM	(1 << 5)	/* Parity-error mask */
#घोषणा CICR0_QDM	(1 << 4)	/* Quick-disable mask */
#घोषणा CICR0_CDM	(1 << 3)	/* Disable-करोne mask */
#घोषणा CICR0_SOFM	(1 << 2)	/* Start-of-frame mask */
#घोषणा CICR0_खातापूर्णM	(1 << 1)	/* End-of-frame mask */
#घोषणा CICR0_FOM	(1 << 0)	/* FIFO-overrun mask */

#घोषणा CICR1_TBIT	(1UL << 31)	/* Transparency bit */
#घोषणा CICR1_RGBT_CONV	(0x3 << 29)	/* RGBT conversion mask */
#घोषणा CICR1_PPL	(0x7ff << 15)	/* Pixels per line mask */
#घोषणा CICR1_RGB_CONV	(0x7 << 12)	/* RGB conversion mask */
#घोषणा CICR1_RGB_F	(1 << 11)	/* RGB क्रमmat */
#घोषणा CICR1_YCBCR_F	(1 << 10)	/* YCbCr क्रमmat */
#घोषणा CICR1_RGB_BPP	(0x7 << 7)	/* RGB bis per pixel mask */
#घोषणा CICR1_RAW_BPP	(0x3 << 5)	/* Raw bis per pixel mask */
#घोषणा CICR1_COLOR_SP	(0x3 << 3)	/* Color space mask */
#घोषणा CICR1_DW	(0x7 << 0)	/* Data width mask */

#घोषणा CICR2_BLW	(0xff << 24)	/* Beginning-of-line pixel घड़ी
					   रुको count mask */
#घोषणा CICR2_ELW	(0xff << 16)	/* End-of-line pixel घड़ी
					   रुको count mask */
#घोषणा CICR2_HSW	(0x3f << 10)	/* Horizontal sync pulse width mask */
#घोषणा CICR2_BFPW	(0x3f << 3)	/* Beginning-of-frame pixel घड़ी
					   रुको count mask */
#घोषणा CICR2_FSW	(0x7 << 0)	/* Frame stabilization
					   रुको count mask */

#घोषणा CICR3_BFW	(0xff << 24)	/* Beginning-of-frame line घड़ी
					   रुको count mask */
#घोषणा CICR3_EFW	(0xff << 16)	/* End-of-frame line घड़ी
					   रुको count mask */
#घोषणा CICR3_VSW	(0x3f << 10)	/* Vertical sync pulse width mask */
#घोषणा CICR3_BFPW	(0x3f << 3)	/* Beginning-of-frame pixel घड़ी
					   रुको count mask */
#घोषणा CICR3_LPF	(0x7ff << 0)	/* Lines per frame mask */

#घोषणा CICR4_MCLK_DLY	(0x3 << 24)	/* MCLK Data Capture Delay mask */
#घोषणा CICR4_PCLK_EN	(1 << 23)	/* Pixel घड़ी enable */
#घोषणा CICR4_PCP	(1 << 22)	/* Pixel घड़ी polarity */
#घोषणा CICR4_HSP	(1 << 21)	/* Horizontal sync polarity */
#घोषणा CICR4_VSP	(1 << 20)	/* Vertical sync polarity */
#घोषणा CICR4_MCLK_EN	(1 << 19)	/* MCLK enable */
#घोषणा CICR4_FR_RATE	(0x7 << 8)	/* Frame rate mask */
#घोषणा CICR4_DIV	(0xff << 0)	/* Clock भागisor mask */

#घोषणा CISR_FTO	(1 << 15)	/* FIFO समय-out */
#घोषणा CISR_RDAV_2	(1 << 14)	/* Channel 2 receive data available */
#घोषणा CISR_RDAV_1	(1 << 13)	/* Channel 1 receive data available */
#घोषणा CISR_RDAV_0	(1 << 12)	/* Channel 0 receive data available */
#घोषणा CISR_FEMPTY_2	(1 << 11)	/* Channel 2 FIFO empty */
#घोषणा CISR_FEMPTY_1	(1 << 10)	/* Channel 1 FIFO empty */
#घोषणा CISR_FEMPTY_0	(1 << 9)	/* Channel 0 FIFO empty */
#घोषणा CISR_EOL	(1 << 8)	/* End of line */
#घोषणा CISR_PAR_ERR	(1 << 7)	/* Parity error */
#घोषणा CISR_CQD	(1 << 6)	/* Camera पूर्णांकerface quick disable */
#घोषणा CISR_CDD	(1 << 5)	/* Camera पूर्णांकerface disable करोne */
#घोषणा CISR_SOF	(1 << 4)	/* Start of frame */
#घोषणा CISR_खातापूर्ण	(1 << 3)	/* End of frame */
#घोषणा CISR_IFO_2	(1 << 2)	/* FIFO overrun क्रम Channel 2 */
#घोषणा CISR_IFO_1	(1 << 1)	/* FIFO overrun क्रम Channel 1 */
#घोषणा CISR_IFO_0	(1 << 0)	/* FIFO overrun क्रम Channel 0 */

#घोषणा CIFR_FLVL2	(0x7f << 23)	/* FIFO 2 level mask */
#घोषणा CIFR_FLVL1	(0x7f << 16)	/* FIFO 1 level mask */
#घोषणा CIFR_FLVL0	(0xff << 8)	/* FIFO 0 level mask */
#घोषणा CIFR_THL_0	(0x3 << 4)	/* Threshold Level क्रम Channel 0 FIFO */
#घोषणा CIFR_RESET_F	(1 << 3)	/* Reset input FIFOs */
#घोषणा CIFR_FEN2	(1 << 2)	/* FIFO enable क्रम channel 2 */
#घोषणा CIFR_FEN1	(1 << 1)	/* FIFO enable क्रम channel 1 */
#घोषणा CIFR_FEN0	(1 << 0)	/* FIFO enable क्रम channel 0 */

#घोषणा CICR0_SIM_MP	(0 << 24)
#घोषणा CICR0_SIM_SP	(1 << 24)
#घोषणा CICR0_SIM_MS	(2 << 24)
#घोषणा CICR0_SIM_EP	(3 << 24)
#घोषणा CICR0_SIM_ES	(4 << 24)

#घोषणा CICR1_DW_VAL(x)   ((x) & CICR1_DW)	    /* Data bus width */
#घोषणा CICR1_PPL_VAL(x)  (((x) << 15) & CICR1_PPL) /* Pixels per line */
#घोषणा CICR1_COLOR_SP_VAL(x)	(((x) << 3) & CICR1_COLOR_SP)	/* color space */
#घोषणा CICR1_RGB_BPP_VAL(x)	(((x) << 7) & CICR1_RGB_BPP)	/* bpp क्रम rgb */
#घोषणा CICR1_RGBT_CONV_VAL(x)	(((x) << 29) & CICR1_RGBT_CONV)	/* rgbt conv */

#घोषणा CICR2_BLW_VAL(x)  (((x) << 24) & CICR2_BLW) /* Beginning-of-line pixel घड़ी रुको count */
#घोषणा CICR2_ELW_VAL(x)  (((x) << 16) & CICR2_ELW) /* End-of-line pixel घड़ी रुको count */
#घोषणा CICR2_HSW_VAL(x)  (((x) << 10) & CICR2_HSW) /* Horizontal sync pulse width */
#घोषणा CICR2_BFPW_VAL(x) (((x) << 3) & CICR2_BFPW) /* Beginning-of-frame pixel घड़ी रुको count */
#घोषणा CICR2_FSW_VAL(x)  (((x) << 0) & CICR2_FSW)  /* Frame stabilization रुको count */

#घोषणा CICR3_BFW_VAL(x)  (((x) << 24) & CICR3_BFW) /* Beginning-of-frame line घड़ी रुको count  */
#घोषणा CICR3_EFW_VAL(x)  (((x) << 16) & CICR3_EFW) /* End-of-frame line घड़ी रुको count */
#घोषणा CICR3_VSW_VAL(x)  (((x) << 11) & CICR3_VSW) /* Vertical sync pulse width */
#घोषणा CICR3_LPF_VAL(x)  (((x) << 0) & CICR3_LPF)  /* Lines per frame */

#घोषणा CICR0_IRQ_MASK (CICR0_TOM | CICR0_RDAVM | CICR0_FEM | CICR0_EOLM | \
			CICR0_PERRM | CICR0_QDM | CICR0_CDM | CICR0_SOFM | \
			CICR0_खातापूर्णM | CICR0_FOM)

#घोषणा sensor_call(cam, o, f, args...) \
	v4l2_subdev_call(cam->sensor, o, f, ##args)

/*
 * Format handling
 */

/**
 * क्रमागत pxa_mbus_packing - data packing types on the media-bus
 * @PXA_MBUS_PACKING_NONE:	no packing, bit-क्रम-bit transfer to RAM, one
 *				sample represents one pixel
 * @PXA_MBUS_PACKING_2X8_PADHI:	16 bits transferred in 2 8-bit samples, in the
 *				possibly incomplete byte high bits are padding
 * @PXA_MBUS_PACKING_EXTEND16:	sample width (e.g., 10 bits) has to be extended
 *				to 16 bits
 */
क्रमागत pxa_mbus_packing अणु
	PXA_MBUS_PACKING_NONE,
	PXA_MBUS_PACKING_2X8_PADHI,
	PXA_MBUS_PACKING_EXTEND16,
पूर्ण;

/**
 * क्रमागत pxa_mbus_order - sample order on the media bus
 * @PXA_MBUS_ORDER_LE:		least signअगरicant sample first
 * @PXA_MBUS_ORDER_BE:		most signअगरicant sample first
 */
क्रमागत pxa_mbus_order अणु
	PXA_MBUS_ORDER_LE,
	PXA_MBUS_ORDER_BE,
पूर्ण;

/**
 * क्रमागत pxa_mbus_layout - planes layout in memory
 * @PXA_MBUS_LAYOUT_PACKED:		color components packed
 * @PXA_MBUS_LAYOUT_PLANAR_2Y_U_V:	YUV components stored in 3 planes (4:2:2)
 * @PXA_MBUS_LAYOUT_PLANAR_2Y_C:	YUV components stored in a luma and a
 *					chroma plane (C plane is half the size
 *					of Y plane)
 * @PXA_MBUS_LAYOUT_PLANAR_Y_C:		YUV components stored in a luma and a
 *					chroma plane (C plane is the same size
 *					as Y plane)
 */
क्रमागत pxa_mbus_layout अणु
	PXA_MBUS_LAYOUT_PACKED = 0,
	PXA_MBUS_LAYOUT_PLANAR_2Y_U_V,
	PXA_MBUS_LAYOUT_PLANAR_2Y_C,
	PXA_MBUS_LAYOUT_PLANAR_Y_C,
पूर्ण;

/**
 * काष्ठा pxa_mbus_pixelfmt - Data क्रमmat on the media bus
 * @name:		Name of the क्रमmat
 * @fourcc:		Fourcc code, that will be obtained अगर the data is
 *			stored in memory in the following way:
 * @packing:		Type of sample-packing, that has to be used
 * @order:		Sample order when storing in memory
 * @layout:		Planes layout in memory
 * @bits_per_sample:	How many bits the bridge has to sample
 */
काष्ठा pxa_mbus_pixelfmt अणु
	स्थिर अक्षर		*name;
	u32			fourcc;
	क्रमागत pxa_mbus_packing	packing;
	क्रमागत pxa_mbus_order	order;
	क्रमागत pxa_mbus_layout	layout;
	u8			bits_per_sample;
पूर्ण;

/**
 * काष्ठा pxa_mbus_lookup - Lookup FOURCC IDs by mediabus codes क्रम pass-through
 * @code:	mediabus pixel-code
 * @fmt:	pixel क्रमmat description
 */
काष्ठा pxa_mbus_lookup अणु
	u32	code;
	काष्ठा pxa_mbus_pixelfmt	fmt;
पूर्ण;

अटल स्थिर काष्ठा pxa_mbus_lookup mbus_fmt[] = अणु
अणु
	.code = MEDIA_BUS_FMT_YUYV8_2X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_YUYV,
		.name			= "YUYV",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_YVYU8_2X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_YVYU,
		.name			= "YVYU",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_UYVY8_2X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_UYVY,
		.name			= "UYVY",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_VYUY8_2X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_VYUY,
		.name			= "VYUY",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_RGB555,
		.name			= "RGB555",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_RGB555X,
		.name			= "RGB555X",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_BE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_RGB565_2X8_LE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_RGB565,
		.name			= "RGB565",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_RGB565_2X8_BE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_RGB565X,
		.name			= "RGB565X",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_BE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SBGGR8_1X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SBGGR8,
		.name			= "Bayer 8 BGGR",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_NONE,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGBRG8_1X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGBRG8,
		.name			= "Bayer 8 GBRG",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_NONE,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGRBG8_1X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGRBG8,
		.name			= "Bayer 8 GRBG",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_NONE,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SRGGB8_1X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SRGGB8,
		.name			= "Bayer 8 RGGB",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_NONE,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SBGGR10_1X10,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 10,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_Y8_1X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_GREY,
		.name			= "Grey",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_NONE,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_Y10_1X10,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_Y10,
		.name			= "Grey 10bit",
		.bits_per_sample	= 10,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_BE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_RGB444,
		.name			= "RGB444",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_BE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_UYVY8_1X16,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_UYVY,
		.name			= "UYVY 16bit",
		.bits_per_sample	= 16,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_VYUY8_1X16,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_VYUY,
		.name			= "VYUY 16bit",
		.bits_per_sample	= 16,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_YUYV8_1X16,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_YUYV,
		.name			= "YUYV 16bit",
		.bits_per_sample	= 16,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_YVYU8_1X16,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_YVYU,
		.name			= "YVYU 16bit",
		.bits_per_sample	= 16,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGRBG10DPCM8,
		.name			= "Bayer 10 BGGR DPCM 8",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_NONE,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGBRG10_1X10,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGBRG10,
		.name			= "Bayer 10 GBRG",
		.bits_per_sample	= 10,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGRBG10_1X10,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGRBG10,
		.name			= "Bayer 10 GRBG",
		.bits_per_sample	= 10,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SRGGB10_1X10,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SRGGB10,
		.name			= "Bayer 10 RGGB",
		.bits_per_sample	= 10,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SBGGR12_1X12,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SBGGR12,
		.name			= "Bayer 12 BGGR",
		.bits_per_sample	= 12,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGBRG12_1X12,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGBRG12,
		.name			= "Bayer 12 GBRG",
		.bits_per_sample	= 12,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SGRBG12_1X12,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SGRBG12,
		.name			= "Bayer 12 GRBG",
		.bits_per_sample	= 12,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण, अणु
	.code = MEDIA_BUS_FMT_SRGGB12_1X12,
	.fmt = अणु
		.fourcc			= V4L2_PIX_FMT_SRGGB12,
		.name			= "Bayer 12 RGGB",
		.bits_per_sample	= 12,
		.packing		= PXA_MBUS_PACKING_EXTEND16,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PACKED,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल s32 pxa_mbus_bytes_per_line(u32 width, स्थिर काष्ठा pxa_mbus_pixelfmt *mf)
अणु
	अगर (mf->layout != PXA_MBUS_LAYOUT_PACKED)
		वापस width * mf->bits_per_sample / 8;

	चयन (mf->packing) अणु
	हाल PXA_MBUS_PACKING_NONE:
		वापस width * mf->bits_per_sample / 8;
	हाल PXA_MBUS_PACKING_2X8_PADHI:
	हाल PXA_MBUS_PACKING_EXTEND16:
		वापस width * 2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल s32 pxa_mbus_image_size(स्थिर काष्ठा pxa_mbus_pixelfmt *mf,
			u32 bytes_per_line, u32 height)
अणु
	अगर (mf->layout == PXA_MBUS_LAYOUT_PACKED)
		वापस bytes_per_line * height;

	चयन (mf->packing) अणु
	हाल PXA_MBUS_PACKING_2X8_PADHI:
		वापस bytes_per_line * height * 2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pxa_mbus_pixelfmt *pxa_mbus_find_fmtdesc(
	u32 code,
	स्थिर काष्ठा pxa_mbus_lookup *lookup,
	पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		अगर (lookup[i].code == code)
			वापस &lookup[i].fmt;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा pxa_mbus_pixelfmt *pxa_mbus_get_fmtdesc(
	u32 code)
अणु
	वापस pxa_mbus_find_fmtdesc(code, mbus_fmt, ARRAY_SIZE(mbus_fmt));
पूर्ण

/**
 * काष्ठा pxa_camera_क्रमmat_xlate - match between host and sensor क्रमmats
 * @code: code of a sensor provided क्रमmat
 * @host_fmt: host क्रमmat after host translation from code
 *
 * Host and sensor translation काष्ठाure. Used in table of host and sensor
 * क्रमmats matchings in pxa_camera_device. A host can override the generic list
 * generation by implementing get_क्रमmats(), and use it क्रम क्रमmat checks and
 * क्रमmat setup.
 */
काष्ठा pxa_camera_क्रमmat_xlate अणु
	u32 code;
	स्थिर काष्ठा pxa_mbus_pixelfmt *host_fmt;
पूर्ण;

/*
 * Structures
 */
क्रमागत pxa_camera_active_dma अणु
	DMA_Y = 0x1,
	DMA_U = 0x2,
	DMA_V = 0x4,
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा pxa_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer		vbuf;
	काष्ठा list_head		queue;
	u32	code;
	पूर्णांक				nb_planes;
	/* our descriptor lists क्रम Y, U and V channels */
	काष्ठा dma_async_tx_descriptor	*descs[3];
	dma_cookie_t			cookie[3];
	काष्ठा scatterlist		*sg[3];
	पूर्णांक				sg_len[3];
	माप_प्रकार				plane_sizes[3];
	पूर्णांक				inwork;
	क्रमागत pxa_camera_active_dma	active_dma;
पूर्ण;

काष्ठा pxa_camera_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vdev;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा vb2_queue	vb2_vq;
	काष्ठा v4l2_subdev	*sensor;
	काष्ठा pxa_camera_क्रमmat_xlate *user_क्रमmats;
	स्थिर काष्ठा pxa_camera_क्रमmat_xlate *current_fmt;
	काष्ठा v4l2_pix_क्रमmat	current_pix;

	/*
	 * PXA27x is only supposed to handle one camera on its Quick Capture
	 * पूर्णांकerface. If anyone ever builds hardware to enable more than
	 * one camera, they will have to modअगरy this driver too
	 */
	काष्ठा clk		*clk;

	अचिन्हित पूर्णांक		irq;
	व्योम __iomem		*base;

	पूर्णांक			channels;
	काष्ठा dma_chan		*dma_chans[3];

	काष्ठा pxacamera_platक्रमm_data *pdata;
	काष्ठा resource		*res;
	अचिन्हित दीर्घ		platक्रमm_flags;
	अचिन्हित दीर्घ		ciclk;
	अचिन्हित दीर्घ		mclk;
	u32			mclk_भागisor;
	u16			width_flags;	/* max 10 bits */

	काष्ठा list_head	capture;

	spinlock_t		lock;
	काष्ठा mutex		mlock;
	अचिन्हित पूर्णांक		buf_sequence;

	काष्ठा pxa_buffer	*active;
	काष्ठा tasklet_काष्ठा	task_eof;

	u32			save_cicr[5];
पूर्ण;

काष्ठा pxa_cam अणु
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल स्थिर अक्षर *pxa_cam_driver_description = "PXA_Camera";

/*
 * Format translation functions
 */
अटल स्थिर काष्ठा pxa_camera_क्रमmat_xlate
*pxa_mbus_xlate_by_fourcc(काष्ठा pxa_camera_क्रमmat_xlate *user_क्रमmats,
			  अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; user_क्रमmats[i].code; i++)
		अगर (user_क्रमmats[i].host_fmt->fourcc == fourcc)
			वापस user_क्रमmats + i;
	वापस शून्य;
पूर्ण

अटल काष्ठा pxa_camera_क्रमmat_xlate *pxa_mbus_build_fmts_xlate(
	काष्ठा v4l2_device *v4l2_dev, काष्ठा v4l2_subdev *subdev,
	पूर्णांक (*get_क्रमmats)(काष्ठा v4l2_device *, अचिन्हित पूर्णांक,
			   काष्ठा pxa_camera_क्रमmat_xlate *xlate))
अणु
	अचिन्हित पूर्णांक i, fmts = 0, raw_fmts = 0;
	पूर्णांक ret;
	काष्ठा v4l2_subdev_mbus_code_क्रमागत code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा pxa_camera_क्रमmat_xlate *user_क्रमmats;

	जबतक (!v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code, शून्य, &code)) अणु
		raw_fmts++;
		code.index++;
	पूर्ण

	/*
	 * First pass - only count क्रमmats this host-sensor
	 * configuration can provide
	 */
	क्रम (i = 0; i < raw_fmts; i++) अणु
		ret = get_क्रमmats(v4l2_dev, i, शून्य);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
		fmts += ret;
	पूर्ण

	अगर (!fmts)
		वापस ERR_PTR(-ENXIO);

	user_क्रमmats = kसुस्मृति(fmts + 1, माप(*user_क्रमmats), GFP_KERNEL);
	अगर (!user_क्रमmats)
		वापस ERR_PTR(-ENOMEM);

	/* Second pass - actually fill data क्रमmats */
	fmts = 0;
	क्रम (i = 0; i < raw_fmts; i++) अणु
		ret = get_क्रमmats(v4l2_dev, i, user_क्रमmats + fmts);
		अगर (ret < 0)
			जाओ egfmt;
		fmts += ret;
	पूर्ण
	user_क्रमmats[fmts].code = 0;

	वापस user_क्रमmats;
egfmt:
	kमुक्त(user_क्रमmats);
	वापस ERR_PTR(ret);
पूर्ण

/*
 *  Videobuf operations
 */
अटल काष्ठा pxa_buffer *vb2_to_pxa_buffer(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	वापस container_of(vbuf, काष्ठा pxa_buffer, vbuf);
पूर्ण

अटल काष्ठा device *pcdev_to_dev(काष्ठा pxa_camera_dev *pcdev)
अणु
	वापस pcdev->v4l2_dev.dev;
पूर्ण

अटल काष्ठा pxa_camera_dev *v4l2_dev_to_pcdev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा pxa_camera_dev, v4l2_dev);
पूर्ण

अटल व्योम pxa_camera_dma_irq(काष्ठा pxa_camera_dev *pcdev,
			       क्रमागत pxa_camera_active_dma act_dma);

अटल व्योम pxa_camera_dma_irq_y(व्योम *data)
अणु
	काष्ठा pxa_camera_dev *pcdev = data;

	pxa_camera_dma_irq(pcdev, DMA_Y);
पूर्ण

अटल व्योम pxa_camera_dma_irq_u(व्योम *data)
अणु
	काष्ठा pxa_camera_dev *pcdev = data;

	pxa_camera_dma_irq(pcdev, DMA_U);
पूर्ण

अटल व्योम pxa_camera_dma_irq_v(व्योम *data)
अणु
	काष्ठा pxa_camera_dev *pcdev = data;

	pxa_camera_dma_irq(pcdev, DMA_V);
पूर्ण

/**
 * pxa_init_dma_channel - init dma descriptors
 * @pcdev: pxa camera device
 * @buf: pxa camera buffer
 * @channel: dma channel (0 => 'Y', 1 => 'U', 2 => 'V')
 * @sg: dma scatter list
 * @sglen: dma scatter list length
 *
 * Prepares the pxa dma descriptors to transfer one camera channel.
 *
 * Returns 0 अगर success or -ENOMEM अगर no memory is available
 */
अटल पूर्णांक pxa_init_dma_channel(काष्ठा pxa_camera_dev *pcdev,
				काष्ठा pxa_buffer *buf, पूर्णांक channel,
				काष्ठा scatterlist *sg, पूर्णांक sglen)
अणु
	काष्ठा dma_chan *dma_chan = pcdev->dma_chans[channel];
	काष्ठा dma_async_tx_descriptor *tx;

	tx = dmaengine_prep_slave_sg(dma_chan, sg, sglen, DMA_DEV_TO_MEM,
				     DMA_PREP_INTERRUPT | DMA_CTRL_REUSE);
	अगर (!tx) अणु
		dev_err(pcdev_to_dev(pcdev),
			"dmaengine_prep_slave_sg failed\n");
		जाओ fail;
	पूर्ण

	tx->callback_param = pcdev;
	चयन (channel) अणु
	हाल 0:
		tx->callback = pxa_camera_dma_irq_y;
		अवरोध;
	हाल 1:
		tx->callback = pxa_camera_dma_irq_u;
		अवरोध;
	हाल 2:
		tx->callback = pxa_camera_dma_irq_v;
		अवरोध;
	पूर्ण

	buf->descs[channel] = tx;
	वापस 0;
fail:
	dev_dbg(pcdev_to_dev(pcdev),
		"%s (vb=%p) dma_tx=%p\n",
		__func__, buf, tx);

	वापस -ENOMEM;
पूर्ण

अटल व्योम pxa_videobuf_set_actdma(काष्ठा pxa_camera_dev *pcdev,
				    काष्ठा pxa_buffer *buf)
अणु
	buf->active_dma = DMA_Y;
	अगर (buf->nb_planes == 3)
		buf->active_dma |= DMA_U | DMA_V;
पूर्ण

/**
 * pxa_dma_start_channels - start DMA channel क्रम active buffer
 * @pcdev: pxa camera device
 *
 * Initialize DMA channels to the beginning of the active video buffer, and
 * start these channels.
 */
अटल व्योम pxa_dma_start_channels(काष्ठा pxa_camera_dev *pcdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pcdev->channels; i++) अणु
		dev_dbg(pcdev_to_dev(pcdev),
			"%s (channel=%d)\n", __func__, i);
		dma_async_issue_pending(pcdev->dma_chans[i]);
	पूर्ण
पूर्ण

अटल व्योम pxa_dma_stop_channels(काष्ठा pxa_camera_dev *pcdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pcdev->channels; i++) अणु
		dev_dbg(pcdev_to_dev(pcdev),
			"%s (channel=%d)\n", __func__, i);
		dmaengine_terminate_all(pcdev->dma_chans[i]);
	पूर्ण
पूर्ण

अटल व्योम pxa_dma_add_tail_buf(काष्ठा pxa_camera_dev *pcdev,
				 काष्ठा pxa_buffer *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pcdev->channels; i++) अणु
		buf->cookie[i] = dmaengine_submit(buf->descs[i]);
		dev_dbg(pcdev_to_dev(pcdev),
			"%s (channel=%d) : submit vb=%p cookie=%d\n",
			__func__, i, buf, buf->descs[i]->cookie);
	पूर्ण
पूर्ण

/**
 * pxa_camera_start_capture - start video capturing
 * @pcdev: camera device
 *
 * Launch capturing. DMA channels should not be active yet. They should get
 * activated at the end of frame पूर्णांकerrupt, to capture only whole frames, and
 * never begin the capture of a partial frame.
 */
अटल व्योम pxa_camera_start_capture(काष्ठा pxa_camera_dev *pcdev)
अणु
	अचिन्हित दीर्घ cicr0;

	dev_dbg(pcdev_to_dev(pcdev), "%s\n", __func__);
	__raw_ग_लिखोl(__raw_पढ़ोl(pcdev->base + CISR), pcdev->base + CISR);
	/* Enable End-Of-Frame Interrupt */
	cicr0 = __raw_पढ़ोl(pcdev->base + CICR0) | CICR0_ENB;
	cicr0 &= ~CICR0_खातापूर्णM;
	__raw_ग_लिखोl(cicr0, pcdev->base + CICR0);
पूर्ण

अटल व्योम pxa_camera_stop_capture(काष्ठा pxa_camera_dev *pcdev)
अणु
	अचिन्हित दीर्घ cicr0;

	pxa_dma_stop_channels(pcdev);

	cicr0 = __raw_पढ़ोl(pcdev->base + CICR0) & ~CICR0_ENB;
	__raw_ग_लिखोl(cicr0, pcdev->base + CICR0);

	pcdev->active = शून्य;
	dev_dbg(pcdev_to_dev(pcdev), "%s\n", __func__);
पूर्ण

अटल व्योम pxa_camera_wakeup(काष्ठा pxa_camera_dev *pcdev,
			      काष्ठा pxa_buffer *buf,
			      क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vb2_buffer *vb = &buf->vbuf.vb2_buf;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	/* _init is used to debug races, see comment in pxa_camera_reqbufs() */
	list_del_init(&buf->queue);
	vb->बारtamp = kसमय_get_ns();
	vbuf->sequence = pcdev->buf_sequence++;
	vbuf->field = V4L2_FIELD_NONE;
	vb2_buffer_करोne(vb, VB2_BUF_STATE_DONE);
	dev_dbg(pcdev_to_dev(pcdev), "%s dequeued buffer (buf=0x%p)\n",
		__func__, buf);

	अगर (list_empty(&pcdev->capture)) अणु
		pxa_camera_stop_capture(pcdev);
		वापस;
	पूर्ण

	pcdev->active = list_entry(pcdev->capture.next,
				   काष्ठा pxa_buffer, queue);
पूर्ण

/**
 * pxa_camera_check_link_miss - check missed DMA linking
 * @pcdev: camera device
 * @last_submitted: an opaque DMA cookie क्रम last submitted
 * @last_issued: an opaque DMA cookie क्रम last issued
 *
 * The DMA chaining is करोne with DMA running. This means a tiny temporal winकरोw
 * reमुख्यs, where a buffer is queued on the chain, जबतक the chain is alपढ़ोy
 * stopped. This means the tailed buffer would never be transferred by DMA.
 * This function restarts the capture क्रम this corner हाल, where :
 *  - DADR() == DADDR_STOP
 *  - a videobuffer is queued on the pcdev->capture list
 *
 * Please check the "DMA hot chaining timeslice issue" in
 *   Documentation/driver-api/media/drivers/pxa_camera.rst
 *
 * Context: should only be called within the dma irq handler
 */
अटल व्योम pxa_camera_check_link_miss(काष्ठा pxa_camera_dev *pcdev,
				       dma_cookie_t last_submitted,
				       dma_cookie_t last_issued)
अणु
	bool is_dma_stopped = last_submitted != last_issued;

	dev_dbg(pcdev_to_dev(pcdev),
		"%s : top queued buffer=%p, is_dma_stopped=%d\n",
		__func__, pcdev->active, is_dma_stopped);

	अगर (pcdev->active && is_dma_stopped)
		pxa_camera_start_capture(pcdev);
पूर्ण

अटल व्योम pxa_camera_dma_irq(काष्ठा pxa_camera_dev *pcdev,
			       क्रमागत pxa_camera_active_dma act_dma)
अणु
	काष्ठा pxa_buffer *buf, *last_buf;
	अचिन्हित दीर्घ flags;
	u32 camera_status, overrun;
	पूर्णांक chan;
	क्रमागत dma_status last_status;
	dma_cookie_t last_issued;

	spin_lock_irqsave(&pcdev->lock, flags);

	camera_status = __raw_पढ़ोl(pcdev->base + CISR);
	dev_dbg(pcdev_to_dev(pcdev), "camera dma irq, cisr=0x%x dma=%d\n",
		camera_status, act_dma);
	overrun = CISR_IFO_0;
	अगर (pcdev->channels == 3)
		overrun |= CISR_IFO_1 | CISR_IFO_2;

	/*
	 * pcdev->active should not be शून्य in DMA irq handler.
	 *
	 * But there is one corner हाल : अगर capture was stopped due to an
	 * overrun of channel 1, and at that same channel 2 was completed.
	 *
	 * When handling the overrun in DMA irq क्रम channel 1, we'll stop the
	 * capture and restart it (and thus set pcdev->active to शून्य). But the
	 * DMA irq handler will alपढ़ोy be pending क्रम channel 2. So on entering
	 * the DMA irq handler क्रम channel 2 there will be no active buffer, yet
	 * that is normal.
	 */
	अगर (!pcdev->active)
		जाओ out;

	buf = pcdev->active;
	WARN_ON(buf->inwork || list_empty(&buf->queue));

	/*
	 * It's normal अगर the last frame creates an overrun, as there
	 * are no more DMA descriptors to fetch from QCI fअगरos
	 */
	चयन (act_dma) अणु
	हाल DMA_U:
		chan = 1;
		अवरोध;
	हाल DMA_V:
		chan = 2;
		अवरोध;
	शेष:
		chan = 0;
		अवरोध;
	पूर्ण
	last_buf = list_entry(pcdev->capture.prev,
			      काष्ठा pxa_buffer, queue);
	last_status = dma_async_is_tx_complete(pcdev->dma_chans[chan],
					       last_buf->cookie[chan],
					       शून्य, &last_issued);
	अगर (camera_status & overrun &&
	    last_status != DMA_COMPLETE) अणु
		dev_dbg(pcdev_to_dev(pcdev), "FIFO overrun! CISR: %x\n",
			camera_status);
		pxa_camera_stop_capture(pcdev);
		list_क्रम_each_entry(buf, &pcdev->capture, queue)
			pxa_dma_add_tail_buf(pcdev, buf);
		pxa_camera_start_capture(pcdev);
		जाओ out;
	पूर्ण
	buf->active_dma &= ~act_dma;
	अगर (!buf->active_dma) अणु
		pxa_camera_wakeup(pcdev, buf, VB2_BUF_STATE_DONE);
		pxa_camera_check_link_miss(pcdev, last_buf->cookie[chan],
					   last_issued);
	पूर्ण

out:
	spin_unlock_irqrestore(&pcdev->lock, flags);
पूर्ण

अटल u32 mclk_get_भागisor(काष्ठा platक्रमm_device *pdev,
			    काष्ठा pxa_camera_dev *pcdev)
अणु
	अचिन्हित दीर्घ mclk = pcdev->mclk;
	u32 भाग;
	अचिन्हित दीर्घ lcdclk;

	lcdclk = clk_get_rate(pcdev->clk);
	pcdev->ciclk = lcdclk;

	/* mclk <= ciclk / 4 (27.4.2) */
	अगर (mclk > lcdclk / 4) अणु
		mclk = lcdclk / 4;
		dev_warn(&pdev->dev,
			 "Limiting master clock to %lu\n", mclk);
	पूर्ण

	/* We verअगरy mclk != 0, so अगर anyone अवरोधs it, here comes their Oops */
	भाग = (lcdclk + 2 * mclk - 1) / (2 * mclk) - 1;

	/* If we're not supplying MCLK, leave it at 0 */
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_MCLK_EN)
		pcdev->mclk = lcdclk / (2 * (भाग + 1));

	dev_dbg(&pdev->dev, "LCD clock %luHz, target freq %luHz, divisor %u\n",
		lcdclk, mclk, भाग);

	वापस भाग;
पूर्ण

अटल व्योम recalculate_fअगरo_समयout(काष्ठा pxa_camera_dev *pcdev,
				     अचिन्हित दीर्घ pclk)
अणु
	/* We want a समयout > 1 pixel समय, not ">=" */
	u32 ciclk_per_pixel = pcdev->ciclk / pclk + 1;

	__raw_ग_लिखोl(ciclk_per_pixel, pcdev->base + CITOR);
पूर्ण

अटल व्योम pxa_camera_activate(काष्ठा pxa_camera_dev *pcdev)
अणु
	u32 cicr4 = 0;

	/* disable all पूर्णांकerrupts */
	__raw_ग_लिखोl(0x3ff, pcdev->base + CICR0);

	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_PCLK_EN)
		cicr4 |= CICR4_PCLK_EN;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_MCLK_EN)
		cicr4 |= CICR4_MCLK_EN;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_PCP)
		cicr4 |= CICR4_PCP;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_HSP)
		cicr4 |= CICR4_HSP;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_VSP)
		cicr4 |= CICR4_VSP;

	__raw_ग_लिखोl(pcdev->mclk_भागisor | cicr4, pcdev->base + CICR4);

	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_MCLK_EN)
		/* Initialise the समयout under the assumption pclk = mclk */
		recalculate_fअगरo_समयout(pcdev, pcdev->mclk);
	अन्यथा
		/* "Safe default" - 13MHz */
		recalculate_fअगरo_समयout(pcdev, 13000000);

	clk_prepare_enable(pcdev->clk);
पूर्ण

अटल व्योम pxa_camera_deactivate(काष्ठा pxa_camera_dev *pcdev)
अणु
	clk_disable_unprepare(pcdev->clk);
पूर्ण

अटल व्योम pxa_camera_eof(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा pxa_camera_dev *pcdev = from_tasklet(pcdev, t, task_eof);
	अचिन्हित दीर्घ cअगरr;
	काष्ठा pxa_buffer *buf;

	dev_dbg(pcdev_to_dev(pcdev),
		"Camera interrupt status 0x%x\n",
		__raw_पढ़ोl(pcdev->base + CISR));

	/* Reset the FIFOs */
	cअगरr = __raw_पढ़ोl(pcdev->base + CIFR) | CIFR_RESET_F;
	__raw_ग_लिखोl(cअगरr, pcdev->base + CIFR);

	pcdev->active = list_first_entry(&pcdev->capture,
					 काष्ठा pxa_buffer, queue);
	buf = pcdev->active;
	pxa_videobuf_set_actdma(pcdev, buf);

	pxa_dma_start_channels(pcdev);
पूर्ण

अटल irqवापस_t pxa_camera_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pxa_camera_dev *pcdev = data;
	अचिन्हित दीर्घ status, cicr0;

	status = __raw_पढ़ोl(pcdev->base + CISR);
	dev_dbg(pcdev_to_dev(pcdev),
		"Camera interrupt status 0x%lx\n", status);

	अगर (!status)
		वापस IRQ_NONE;

	__raw_ग_लिखोl(status, pcdev->base + CISR);

	अगर (status & CISR_खातापूर्ण) अणु
		cicr0 = __raw_पढ़ोl(pcdev->base + CICR0) | CICR0_खातापूर्णM;
		__raw_ग_लिखोl(cicr0, pcdev->base + CICR0);
		tasklet_schedule(&pcdev->task_eof);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pxa_camera_setup_cicr(काष्ठा pxa_camera_dev *pcdev,
				  अचिन्हित दीर्घ flags, __u32 pixfmt)
अणु
	अचिन्हित दीर्घ dw, bpp;
	u32 cicr0, cicr1, cicr2, cicr3, cicr4 = 0, y_skip_top;
	पूर्णांक ret = sensor_call(pcdev, sensor, g_skip_top_lines, &y_skip_top);

	अगर (ret < 0)
		y_skip_top = 0;

	/*
	 * Datawidth is now guaranteed to be equal to one of the three values.
	 * We fix bit-per-pixel equal to data-width...
	 */
	चयन (pcdev->current_fmt->host_fmt->bits_per_sample) अणु
	हाल 10:
		dw = 4;
		bpp = 0x40;
		अवरोध;
	हाल 9:
		dw = 3;
		bpp = 0x20;
		अवरोध;
	शेष:
		/*
		 * Actually it can only be 8 now,
		 * शेष is just to silence compiler warnings
		 */
	हाल 8:
		dw = 2;
		bpp = 0;
	पूर्ण

	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_PCLK_EN)
		cicr4 |= CICR4_PCLK_EN;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_MCLK_EN)
		cicr4 |= CICR4_MCLK_EN;
	अगर (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		cicr4 |= CICR4_PCP;
	अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		cicr4 |= CICR4_HSP;
	अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		cicr4 |= CICR4_VSP;

	cicr0 = __raw_पढ़ोl(pcdev->base + CICR0);
	अगर (cicr0 & CICR0_ENB)
		__raw_ग_लिखोl(cicr0 & ~CICR0_ENB, pcdev->base + CICR0);

	cicr1 = CICR1_PPL_VAL(pcdev->current_pix.width - 1) | bpp | dw;

	चयन (pixfmt) अणु
	हाल V4L2_PIX_FMT_YUV422P:
		pcdev->channels = 3;
		cicr1 |= CICR1_YCBCR_F;
		/*
		 * Normally, pxa bus wants as input UYVY क्रमmat. We allow all
		 * reorderings of the YUV422 क्रमmat, as no processing is करोne,
		 * and the YUV stream is just passed through without any
		 * transक्रमmation. Note that UYVY is the only क्रमmat that
		 * should be used अगर pxa framebuffer Overlay2 is used.
		 */
		fallthrough;
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
		cicr1 |= CICR1_COLOR_SP_VAL(2);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB555:
		cicr1 |= CICR1_RGB_BPP_VAL(1) | CICR1_RGBT_CONV_VAL(2) |
			CICR1_TBIT | CICR1_COLOR_SP_VAL(1);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		cicr1 |= CICR1_COLOR_SP_VAL(1) | CICR1_RGB_BPP_VAL(2);
		अवरोध;
	पूर्ण

	cicr2 = 0;
	cicr3 = CICR3_LPF_VAL(pcdev->current_pix.height - 1) |
		CICR3_BFW_VAL(min((u32)255, y_skip_top));
	cicr4 |= pcdev->mclk_भागisor;

	__raw_ग_लिखोl(cicr1, pcdev->base + CICR1);
	__raw_ग_लिखोl(cicr2, pcdev->base + CICR2);
	__raw_ग_लिखोl(cicr3, pcdev->base + CICR3);
	__raw_ग_लिखोl(cicr4, pcdev->base + CICR4);

	/* CIF पूर्णांकerrupts are not used, only DMA */
	cicr0 = (cicr0 & CICR0_ENB) | (pcdev->platक्रमm_flags & PXA_CAMERA_MASTER ?
		CICR0_SIM_MP : (CICR0_SL_CAP_EN | CICR0_SIM_SP));
	cicr0 |= CICR0_DMAEN | CICR0_IRQ_MASK;
	__raw_ग_लिखोl(cicr0, pcdev->base + CICR0);
पूर्ण

/*
 * Videobuf2 section
 */
अटल व्योम pxa_buffer_cleanup(काष्ठा pxa_buffer *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3 && buf->descs[i]; i++) अणु
		dmaengine_desc_मुक्त(buf->descs[i]);
		kमुक्त(buf->sg[i]);
		buf->descs[i] = शून्य;
		buf->sg[i] = शून्य;
		buf->sg_len[i] = 0;
		buf->plane_sizes[i] = 0;
	पूर्ण
	buf->nb_planes = 0;
पूर्ण

अटल पूर्णांक pxa_buffer_init(काष्ठा pxa_camera_dev *pcdev,
			   काष्ठा pxa_buffer *buf)
अणु
	काष्ठा vb2_buffer *vb = &buf->vbuf.vb2_buf;
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	पूर्णांक nb_channels = pcdev->channels;
	पूर्णांक i, ret = 0;
	अचिन्हित दीर्घ size = vb2_plane_size(vb, 0);

	चयन (nb_channels) अणु
	हाल 1:
		buf->plane_sizes[0] = size;
		अवरोध;
	हाल 3:
		buf->plane_sizes[0] = size / 2;
		buf->plane_sizes[1] = size / 4;
		buf->plane_sizes[2] = size / 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	buf->nb_planes = nb_channels;

	ret = sg_split(sgt->sgl, sgt->nents, 0, nb_channels,
		       buf->plane_sizes, buf->sg, buf->sg_len, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(pcdev_to_dev(pcdev),
			"sg_split failed: %d\n", ret);
		वापस ret;
	पूर्ण
	क्रम (i = 0; i < nb_channels; i++) अणु
		ret = pxa_init_dma_channel(pcdev, buf, i,
					   buf->sg[i], buf->sg_len[i]);
		अगर (ret) अणु
			pxa_buffer_cleanup(buf);
			वापस ret;
		पूर्ण
	पूर्ण
	INIT_LIST_HEAD(&buf->queue);

	वापस ret;
पूर्ण

अटल व्योम pxac_vb2_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pxa_buffer *buf = vb2_to_pxa_buffer(vb);
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vb->vb2_queue);

	dev_dbg(pcdev_to_dev(pcdev),
		 "%s(vb=%p)\n", __func__, vb);
	pxa_buffer_cleanup(buf);
पूर्ण

अटल व्योम pxac_vb2_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pxa_buffer *buf = vb2_to_pxa_buffer(vb);
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vb->vb2_queue);

	dev_dbg(pcdev_to_dev(pcdev),
		 "%s(vb=%p) nb_channels=%d size=%lu active=%p\n",
		__func__, vb, pcdev->channels, vb2_get_plane_payload(vb, 0),
		pcdev->active);

	list_add_tail(&buf->queue, &pcdev->capture);

	pxa_dma_add_tail_buf(pcdev, buf);
पूर्ण

/*
 * Please check the DMA prepared buffer काष्ठाure in :
 *   Documentation/driver-api/media/drivers/pxa_camera.rst
 * Please check also in pxa_camera_check_link_miss() to understand why DMA chain
 * modअगरication जबतक DMA chain is running will work anyway.
 */
अटल पूर्णांक pxac_vb2_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा pxa_buffer *buf = vb2_to_pxa_buffer(vb);
	पूर्णांक ret = 0;
#अगर_घोषित DEBUG
	पूर्णांक i;
#पूर्ण_अगर

	चयन (pcdev->channels) अणु
	हाल 1:
	हाल 3:
		vb2_set_plane_payload(vb, 0, pcdev->current_pix.sizeimage);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(pcdev_to_dev(pcdev),
		 "%s (vb=%p) nb_channels=%d size=%lu\n",
		__func__, vb, pcdev->channels, vb2_get_plane_payload(vb, 0));

	WARN_ON(!pcdev->current_fmt);

#अगर_घोषित DEBUG
	/*
	 * This can be useful अगर you want to see अगर we actually fill
	 * the buffer with something
	 */
	क्रम (i = 0; i < vb->num_planes; i++)
		स_रखो((व्योम *)vb2_plane_vaddr(vb, i),
		       0xaa, vb2_get_plane_payload(vb, i));
#पूर्ण_अगर

	/*
	 * I think, in buf_prepare you only have to protect global data,
	 * the actual buffer is yours
	 */
	buf->inwork = 0;
	pxa_videobuf_set_actdma(pcdev, buf);

	वापस ret;
पूर्ण

अटल पूर्णांक pxac_vb2_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा pxa_buffer *buf = vb2_to_pxa_buffer(vb);

	dev_dbg(pcdev_to_dev(pcdev),
		 "%s(nb_channels=%d)\n",
		__func__, pcdev->channels);

	वापस pxa_buffer_init(pcdev, buf);
पूर्ण

अटल पूर्णांक pxac_vb2_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbufs,
				अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vq);
	पूर्णांक size = pcdev->current_pix.sizeimage;

	dev_dbg(pcdev_to_dev(pcdev),
		 "%s(vq=%p nbufs=%d num_planes=%d size=%d)\n",
		__func__, vq, *nbufs, *num_planes, size);
	/*
	 * Called from VIDIOC_REQBUFS or in compatibility mode For YUV422P
	 * क्रमmat, even अगर there are 3 planes Y, U and V, we reply there is only
	 * one plane, containing Y, U and V data, one after the other.
	 */
	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	चयन (pcdev->channels) अणु
	हाल 1:
	हाल 3:
		sizes[0] = size;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!*nbufs)
		*nbufs = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vq);

	dev_dbg(pcdev_to_dev(pcdev), "%s(count=%d) active=%p\n",
		__func__, count, pcdev->active);

	pcdev->buf_sequence = 0;
	अगर (!pcdev->active)
		pxa_camera_start_capture(pcdev);

	वापस 0;
पूर्ण

अटल व्योम pxac_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा pxa_camera_dev *pcdev = vb2_get_drv_priv(vq);
	काष्ठा pxa_buffer *buf, *पंचांगp;

	dev_dbg(pcdev_to_dev(pcdev), "%s active=%p\n",
		__func__, pcdev->active);
	pxa_camera_stop_capture(pcdev);

	list_क्रम_each_entry_safe(buf, पंचांगp, &pcdev->capture, queue)
		pxa_camera_wakeup(pcdev, buf, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops pxac_vb2_ops = अणु
	.queue_setup		= pxac_vb2_queue_setup,
	.buf_init		= pxac_vb2_init,
	.buf_prepare		= pxac_vb2_prepare,
	.buf_queue		= pxac_vb2_queue,
	.buf_cleanup		= pxac_vb2_cleanup,
	.start_streaming	= pxac_vb2_start_streaming,
	.stop_streaming		= pxac_vb2_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक pxa_camera_init_videobuf2(काष्ठा pxa_camera_dev *pcdev)
अणु
	पूर्णांक ret;
	काष्ठा vb2_queue *vq = &pcdev->vb2_vq;

	स_रखो(vq, 0, माप(*vq));
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	vq->drv_priv = pcdev;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->buf_काष्ठा_size = माप(काष्ठा pxa_buffer);
	vq->dev = pcdev->v4l2_dev.dev;

	vq->ops = &pxac_vb2_ops;
	vq->mem_ops = &vb2_dma_sg_memops;
	vq->lock = &pcdev->mlock;

	ret = vb2_queue_init(vq);
	dev_dbg(pcdev_to_dev(pcdev),
		 "vb2_queue_init(vq=%p): %d\n", vq, ret);

	वापस ret;
पूर्ण

/*
 * Video ioctls section
 */
अटल पूर्णांक pxa_camera_set_bus_param(काष्ठा pxa_camera_dev *pcdev)
अणु
	अचिन्हित पूर्णांक bus_width = pcdev->current_fmt->host_fmt->bits_per_sample;
	काष्ठा v4l2_mbus_config cfg = अणु.type = V4L2_MBUS_PARALLEL,पूर्ण;
	u32 pixfmt = pcdev->current_fmt->host_fmt->fourcc;
	पूर्णांक mbus_config;
	पूर्णांक ret;

	अगर (!((1 << (bus_width - 1)) & pcdev->width_flags)) अणु
		dev_err(pcdev_to_dev(pcdev), "Unsupported bus width %u",
			bus_width);
		वापस -EINVAL;
	पूर्ण

	pcdev->channels = 1;

	/* Make choices, based on platक्रमm preferences */
	mbus_config = 0;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_MASTER)
		mbus_config |= V4L2_MBUS_MASTER;
	अन्यथा
		mbus_config |= V4L2_MBUS_SLAVE;

	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_HSP)
		mbus_config |= V4L2_MBUS_HSYNC_ACTIVE_HIGH;
	अन्यथा
		mbus_config |= V4L2_MBUS_HSYNC_ACTIVE_LOW;

	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_VSP)
		mbus_config |= V4L2_MBUS_VSYNC_ACTIVE_HIGH;
	अन्यथा
		mbus_config |= V4L2_MBUS_VSYNC_ACTIVE_LOW;

	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_PCP)
		mbus_config |= V4L2_MBUS_PCLK_SAMPLE_RISING;
	अन्यथा
		mbus_config |= V4L2_MBUS_PCLK_SAMPLE_FALLING;
	mbus_config |= V4L2_MBUS_DATA_ACTIVE_HIGH;

	cfg.flags = mbus_config;
	ret = sensor_call(pcdev, pad, set_mbus_config, 0, &cfg);
	अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
		dev_err(pcdev_to_dev(pcdev),
			"Failed to call set_mbus_config: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * If the requested media bus configuration has not been fully applied
	 * make sure it is supported by the platक्रमm.
	 *
	 * PXA करोes not support V4L2_MBUS_DATA_ACTIVE_LOW and the bus mastering
	 * roles should match.
	 */
	अगर (cfg.flags != mbus_config) अणु
		अचिन्हित पूर्णांक pxa_mbus_role = mbus_config & (V4L2_MBUS_MASTER |
							    V4L2_MBUS_SLAVE);
		अगर (pxa_mbus_role != (cfg.flags & (V4L2_MBUS_MASTER |
						   V4L2_MBUS_SLAVE))) अणु
			dev_err(pcdev_to_dev(pcdev),
				"Unsupported mbus configuration: bus mastering\n");
			वापस -EINVAL;
		पूर्ण

		अगर (cfg.flags & V4L2_MBUS_DATA_ACTIVE_LOW) अणु
			dev_err(pcdev_to_dev(pcdev),
				"Unsupported mbus configuration: DATA_ACTIVE_LOW\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pxa_camera_setup_cicr(pcdev, cfg.flags, pixfmt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pxa_mbus_pixelfmt pxa_camera_क्रमmats[] = अणु
	अणु
		.fourcc			= V4L2_PIX_FMT_YUV422P,
		.name			= "Planar YUV422 16 bit",
		.bits_per_sample	= 8,
		.packing		= PXA_MBUS_PACKING_2X8_PADHI,
		.order			= PXA_MBUS_ORDER_LE,
		.layout			= PXA_MBUS_LAYOUT_PLANAR_2Y_U_V,
	पूर्ण,
पूर्ण;

/* This will be corrected as we get more क्रमmats */
अटल bool pxa_camera_packing_supported(स्थिर काष्ठा pxa_mbus_pixelfmt *fmt)
अणु
	वापस	fmt->packing == PXA_MBUS_PACKING_NONE ||
		(fmt->bits_per_sample == 8 &&
		 fmt->packing == PXA_MBUS_PACKING_2X8_PADHI) ||
		(fmt->bits_per_sample > 8 &&
		 fmt->packing == PXA_MBUS_PACKING_EXTEND16);
पूर्ण

अटल पूर्णांक pxa_camera_get_क्रमmats(काष्ठा v4l2_device *v4l2_dev,
				  अचिन्हित पूर्णांक idx,
				  काष्ठा pxa_camera_क्रमmat_xlate *xlate)
अणु
	काष्ठा pxa_camera_dev *pcdev = v4l2_dev_to_pcdev(v4l2_dev);
	पूर्णांक क्रमmats = 0, ret;
	काष्ठा v4l2_subdev_mbus_code_क्रमागत code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.index = idx,
	पूर्ण;
	स्थिर काष्ठा pxa_mbus_pixelfmt *fmt;

	ret = sensor_call(pcdev, pad, क्रमागत_mbus_code, शून्य, &code);
	अगर (ret < 0)
		/* No more क्रमmats */
		वापस 0;

	fmt = pxa_mbus_get_fmtdesc(code.code);
	अगर (!fmt) अणु
		dev_err(pcdev_to_dev(pcdev),
			"Invalid format code #%u: %d\n", idx, code.code);
		वापस 0;
	पूर्ण

	चयन (code.code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		क्रमmats++;
		अगर (xlate) अणु
			xlate->host_fmt	= &pxa_camera_क्रमmats[0];
			xlate->code	= code.code;
			xlate++;
			dev_dbg(pcdev_to_dev(pcdev),
				"Providing format %s using code %d\n",
				pxa_camera_क्रमmats[0].name, code.code);
		पूर्ण
		fallthrough;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		अगर (xlate)
			dev_dbg(pcdev_to_dev(pcdev),
				"Providing format %s packed\n",
				fmt->name);
		अवरोध;
	शेष:
		अगर (!pxa_camera_packing_supported(fmt))
			वापस 0;
		अगर (xlate)
			dev_dbg(pcdev_to_dev(pcdev),
				"Providing format %s in pass-through mode\n",
				fmt->name);
		अवरोध;
	पूर्ण

	/* Generic pass-through */
	क्रमmats++;
	अगर (xlate) अणु
		xlate->host_fmt	= fmt;
		xlate->code	= code.code;
		xlate++;
	पूर्ण

	वापस क्रमmats;
पूर्ण

अटल पूर्णांक pxa_camera_build_क्रमmats(काष्ठा pxa_camera_dev *pcdev)
अणु
	काष्ठा pxa_camera_क्रमmat_xlate *xlate;

	xlate = pxa_mbus_build_fmts_xlate(&pcdev->v4l2_dev, pcdev->sensor,
					  pxa_camera_get_क्रमmats);
	अगर (IS_ERR(xlate))
		वापस PTR_ERR(xlate);

	pcdev->user_क्रमmats = xlate;
	वापस 0;
पूर्ण

अटल व्योम pxa_camera_destroy_क्रमmats(काष्ठा pxa_camera_dev *pcdev)
अणु
	kमुक्त(pcdev->user_क्रमmats);
पूर्ण

अटल पूर्णांक pxa_camera_check_frame(u32 width, u32 height)
अणु
	/* limit to pxa hardware capabilities */
	वापस height < 32 || height > 2048 || width < 48 || width > 2048 ||
		(width & 0x01);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक pxac_vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(file);

	अगर (reg->reg > CIBR2)
		वापस -दुस्फल;

	reg->val = __raw_पढ़ोl(pcdev->base + reg->reg);
	reg->size = माप(__u32);
	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
				  स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(file);

	अगर (reg->reg > CIBR2)
		वापस -दुस्फल;
	अगर (reg->size != माप(__u32))
		वापस -EINVAL;
	__raw_ग_लिखोl(reg->val, pcdev->base + reg->reg);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pxac_vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *filp, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(filp);
	स्थिर काष्ठा pxa_mbus_pixelfmt *क्रमmat;
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; pcdev->user_क्रमmats[idx].code; idx++);
	अगर (f->index >= idx)
		वापस -EINVAL;

	क्रमmat = pcdev->user_क्रमmats[f->index].host_fmt;
	f->pixelक्रमmat = क्रमmat->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_g_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(filp);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	pix->width		= pcdev->current_pix.width;
	pix->height		= pcdev->current_pix.height;
	pix->bytesperline	= pcdev->current_pix.bytesperline;
	pix->sizeimage		= pcdev->current_pix.sizeimage;
	pix->field		= pcdev->current_pix.field;
	pix->pixelक्रमmat	= pcdev->current_fmt->host_fmt->fourcc;
	pix->colorspace		= pcdev->current_pix.colorspace;
	dev_dbg(pcdev_to_dev(pcdev), "current_fmt->fourcc: 0x%08x\n",
		pcdev->current_fmt->host_fmt->fourcc);
	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_try_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(filp);
	स्थिर काष्ठा pxa_camera_क्रमmat_xlate *xlate;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat.क्रमmat;
	__u32 pixfmt = pix->pixelक्रमmat;
	पूर्णांक ret;

	xlate = pxa_mbus_xlate_by_fourcc(pcdev->user_क्रमmats, pixfmt);
	अगर (!xlate) अणु
		dev_warn(pcdev_to_dev(pcdev), "Format %x not found\n", pixfmt);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Limit to pxa hardware capabilities.  YUV422P planar क्रमmat requires
	 * images size to be a multiple of 16 bytes.  If not, zeros will be
	 * inserted between Y and U planes, and U and V planes, which violates
	 * the YUV422P standard.
	 */
	v4l_bound_align_image(&pix->width, 48, 2048, 1,
			      &pix->height, 32, 2048, 0,
			      pixfmt == V4L2_PIX_FMT_YUV422P ? 4 : 0);

	v4l2_fill_mbus_क्रमmat(mf, pix, xlate->code);
	ret = sensor_call(pcdev, pad, set_fmt, &pad_cfg, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	v4l2_fill_pix_क्रमmat(pix, mf);

	/* Only progressive video supported so far */
	चयन (mf->field) अणु
	हाल V4L2_FIELD_ANY:
	हाल V4L2_FIELD_NONE:
		pix->field = V4L2_FIELD_NONE;
		अवरोध;
	शेष:
		/* TODO: support पूर्णांकerlaced at least in pass-through mode */
		dev_err(pcdev_to_dev(pcdev), "Field type %d unsupported.\n",
			mf->field);
		वापस -EINVAL;
	पूर्ण

	ret = pxa_mbus_bytes_per_line(pix->width, xlate->host_fmt);
	अगर (ret < 0)
		वापस ret;

	pix->bytesperline = ret;
	ret = pxa_mbus_image_size(xlate->host_fmt, pix->bytesperline,
				  pix->height);
	अगर (ret < 0)
		वापस ret;

	pix->sizeimage = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_s_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(filp);
	स्थिर काष्ठा pxa_camera_क्रमmat_xlate *xlate;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, is_busy;

	dev_dbg(pcdev_to_dev(pcdev),
		"s_fmt_vid_cap(pix=%dx%d:%x)\n",
		pix->width, pix->height, pix->pixelक्रमmat);

	spin_lock_irqsave(&pcdev->lock, flags);
	is_busy = pcdev->active || vb2_is_busy(&pcdev->vb2_vq);
	spin_unlock_irqrestore(&pcdev->lock, flags);

	अगर (is_busy)
		वापस -EBUSY;

	ret = pxac_vidioc_try_fmt_vid_cap(filp, priv, f);
	अगर (ret)
		वापस ret;

	xlate = pxa_mbus_xlate_by_fourcc(pcdev->user_क्रमmats,
					 pix->pixelक्रमmat);
	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pix, xlate->code);
	ret = sensor_call(pcdev, pad, set_fmt, शून्य, &क्रमmat);
	अगर (ret < 0) अणु
		dev_warn(pcdev_to_dev(pcdev),
			 "Failed to configure for format %x\n",
			 pix->pixelक्रमmat);
	पूर्ण अन्यथा अगर (pxa_camera_check_frame(pix->width, pix->height)) अणु
		dev_warn(pcdev_to_dev(pcdev),
			 "Camera driver produced an unsupported frame %dx%d\n",
			 pix->width, pix->height);
		वापस -EINVAL;
	पूर्ण

	pcdev->current_fmt = xlate;
	pcdev->current_pix = *pix;

	ret = pxa_camera_set_bus_param(pcdev);
	वापस ret;
पूर्ण

अटल पूर्णांक pxac_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->bus_info, "platform:pxa-camera", माप(cap->bus_info));
	strscpy(cap->driver, PXA_CAM_DRV_NAME, माप(cap->driver));
	strscpy(cap->card, pxa_cam_driver_description, माप(cap->card));
	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_input *i)
अणु
	अगर (i->index > 0)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(i->name, "Camera", माप(i->name));

	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक pxac_vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक pxac_sensor_set_घातer(काष्ठा pxa_camera_dev *pcdev, पूर्णांक on)
अणु
	पूर्णांक ret;

	ret = sensor_call(pcdev, core, s_घातer, on);
	अगर (ret == -ENOIOCTLCMD)
		ret = 0;
	अगर (ret) अणु
		dev_warn(pcdev_to_dev(pcdev),
			 "Failed to put subdevice in %s mode: %d\n",
			 on ? "normal operation" : "power saving", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pxac_fops_camera_खोलो(काष्ठा file *filp)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(filp);
	पूर्णांक ret;

	mutex_lock(&pcdev->mlock);
	ret = v4l2_fh_खोलो(filp);
	अगर (ret < 0)
		जाओ out;

	अगर (!v4l2_fh_is_singular_file(filp))
		जाओ out;

	ret = pxac_sensor_set_घातer(pcdev, 1);
	अगर (ret)
		v4l2_fh_release(filp);
out:
	mutex_unlock(&pcdev->mlock);
	वापस ret;
पूर्ण

अटल पूर्णांक pxac_fops_camera_release(काष्ठा file *filp)
अणु
	काष्ठा pxa_camera_dev *pcdev = video_drvdata(filp);
	पूर्णांक ret;
	bool fh_singular;

	mutex_lock(&pcdev->mlock);

	fh_singular = v4l2_fh_is_singular_file(filp);

	ret = _vb2_fop_release(filp, शून्य);

	अगर (fh_singular)
		ret = pxac_sensor_set_घातer(pcdev, 0);

	mutex_unlock(&pcdev->mlock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations pxa_camera_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= pxac_fops_camera_खोलो,
	.release	= pxac_fops_camera_release,
	.पढ़ो		= vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops pxa_camera_ioctl_ops = अणु
	.vidioc_querycap		= pxac_vidioc_querycap,

	.vidioc_क्रमागत_input		= pxac_vidioc_क्रमागत_input,
	.vidioc_g_input			= pxac_vidioc_g_input,
	.vidioc_s_input			= pxac_vidioc_s_input,

	.vidioc_क्रमागत_fmt_vid_cap	= pxac_vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= pxac_vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= pxac_vidioc_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= pxac_vidioc_try_fmt_vid_cap,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर		= pxac_vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर		= pxac_vidioc_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device pxa_camera_videodev_ढाँचा = अणु
	.name = "pxa-camera",
	.minor = -1,
	.fops = &pxa_camera_fops,
	.ioctl_ops = &pxa_camera_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING,
पूर्ण;

अटल पूर्णांक pxa_camera_sensor_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
		     काष्ठा v4l2_subdev *subdev,
		     काष्ठा v4l2_async_subdev *asd)
अणु
	पूर्णांक err;
	काष्ठा v4l2_device *v4l2_dev = notअगरier->v4l2_dev;
	काष्ठा pxa_camera_dev *pcdev = v4l2_dev_to_pcdev(v4l2_dev);
	काष्ठा video_device *vdev = &pcdev->vdev;
	काष्ठा v4l2_pix_क्रमmat *pix = &pcdev->current_pix;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat.क्रमmat;

	dev_info(pcdev_to_dev(pcdev), "%s(): trying to bind a device\n",
		 __func__);
	mutex_lock(&pcdev->mlock);
	*vdev = pxa_camera_videodev_ढाँचा;
	vdev->v4l2_dev = v4l2_dev;
	vdev->lock = &pcdev->mlock;
	pcdev->sensor = subdev;
	pcdev->vdev.queue = &pcdev->vb2_vq;
	pcdev->vdev.v4l2_dev = &pcdev->v4l2_dev;
	pcdev->vdev.ctrl_handler = subdev->ctrl_handler;
	video_set_drvdata(&pcdev->vdev, pcdev);

	err = pxa_camera_build_क्रमmats(pcdev);
	अगर (err) अणु
		dev_err(pcdev_to_dev(pcdev), "building formats failed: %d\n",
			err);
		जाओ out;
	पूर्ण

	pcdev->current_fmt = pcdev->user_क्रमmats;
	pix->field = V4L2_FIELD_NONE;
	pix->width = DEFAULT_WIDTH;
	pix->height = DEFAULT_HEIGHT;
	pix->bytesperline =
		pxa_mbus_bytes_per_line(pix->width,
					pcdev->current_fmt->host_fmt);
	pix->sizeimage =
		pxa_mbus_image_size(pcdev->current_fmt->host_fmt,
				    pix->bytesperline, pix->height);
	pix->pixelक्रमmat = pcdev->current_fmt->host_fmt->fourcc;
	v4l2_fill_mbus_क्रमmat(mf, pix, pcdev->current_fmt->code);

	err = pxac_sensor_set_घातer(pcdev, 1);
	अगर (err)
		जाओ out;

	err = sensor_call(pcdev, pad, set_fmt, शून्य, &क्रमmat);
	अगर (err)
		जाओ out_sensor_घातeroff;

	v4l2_fill_pix_क्रमmat(pix, mf);
	pr_info("%s(): colorspace=0x%x pixfmt=0x%x\n",
		__func__, pix->colorspace, pix->pixelक्रमmat);

	err = pxa_camera_init_videobuf2(pcdev);
	अगर (err)
		जाओ out_sensor_घातeroff;

	err = video_रेजिस्टर_device(&pcdev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (err) अणु
		v4l2_err(v4l2_dev, "register video device failed: %d\n", err);
		pcdev->sensor = शून्य;
	पूर्ण अन्यथा अणु
		dev_info(pcdev_to_dev(pcdev),
			 "PXA Camera driver attached to camera %s\n",
			 subdev->name);
	पूर्ण

out_sensor_घातeroff:
	err = pxac_sensor_set_घातer(pcdev, 0);
out:
	mutex_unlock(&pcdev->mlock);
	वापस err;
पूर्ण

अटल व्योम pxa_camera_sensor_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
		     काष्ठा v4l2_subdev *subdev,
		     काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा pxa_camera_dev *pcdev = v4l2_dev_to_pcdev(notअगरier->v4l2_dev);

	mutex_lock(&pcdev->mlock);
	dev_info(pcdev_to_dev(pcdev),
		 "PXA Camera driver detached from camera %s\n",
		 subdev->name);

	/* disable capture, disable पूर्णांकerrupts */
	__raw_ग_लिखोl(0x3ff, pcdev->base + CICR0);

	/* Stop DMA engine */
	pxa_dma_stop_channels(pcdev);

	pxa_camera_destroy_क्रमmats(pcdev);

	video_unरेजिस्टर_device(&pcdev->vdev);
	pcdev->sensor = शून्य;

	mutex_unlock(&pcdev->mlock);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations pxa_camera_sensor_ops = अणु
	.bound = pxa_camera_sensor_bound,
	.unbind = pxa_camera_sensor_unbind,
पूर्ण;

/*
 * Driver probe, हटाओ, suspend and resume operations
 */
अटल पूर्णांक pxa_camera_suspend(काष्ठा device *dev)
अणु
	काष्ठा pxa_camera_dev *pcdev = dev_get_drvdata(dev);
	पूर्णांक i = 0, ret = 0;

	pcdev->save_cicr[i++] = __raw_पढ़ोl(pcdev->base + CICR0);
	pcdev->save_cicr[i++] = __raw_पढ़ोl(pcdev->base + CICR1);
	pcdev->save_cicr[i++] = __raw_पढ़ोl(pcdev->base + CICR2);
	pcdev->save_cicr[i++] = __raw_पढ़ोl(pcdev->base + CICR3);
	pcdev->save_cicr[i++] = __raw_पढ़ोl(pcdev->base + CICR4);

	अगर (pcdev->sensor)
		ret = pxac_sensor_set_घातer(pcdev, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक pxa_camera_resume(काष्ठा device *dev)
अणु
	काष्ठा pxa_camera_dev *pcdev = dev_get_drvdata(dev);
	पूर्णांक i = 0, ret = 0;

	__raw_ग_लिखोl(pcdev->save_cicr[i++] & ~CICR0_ENB, pcdev->base + CICR0);
	__raw_ग_लिखोl(pcdev->save_cicr[i++], pcdev->base + CICR1);
	__raw_ग_लिखोl(pcdev->save_cicr[i++], pcdev->base + CICR2);
	__raw_ग_लिखोl(pcdev->save_cicr[i++], pcdev->base + CICR3);
	__raw_ग_लिखोl(pcdev->save_cicr[i++], pcdev->base + CICR4);

	अगर (pcdev->sensor) अणु
		ret = pxac_sensor_set_घातer(pcdev, 1);
	पूर्ण

	/* Restart frame capture अगर active buffer exists */
	अगर (!ret && pcdev->active)
		pxa_camera_start_capture(pcdev);

	वापस ret;
पूर्ण

अटल पूर्णांक pxa_camera_pdata_from_dt(काष्ठा device *dev,
				    काष्ठा pxa_camera_dev *pcdev)
अणु
	u32 mclk_rate;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = 0 पूर्ण;
	पूर्णांक err = of_property_पढ़ो_u32(np, "clock-frequency",
				       &mclk_rate);
	अगर (!err) अणु
		pcdev->platक्रमm_flags |= PXA_CAMERA_MCLK_EN;
		pcdev->mclk = mclk_rate;
	पूर्ण

	np = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (!np) अणु
		dev_err(dev, "could not find endpoint\n");
		वापस -EINVAL;
	पूर्ण

	err = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(np), &ep);
	अगर (err) अणु
		dev_err(dev, "could not parse endpoint\n");
		जाओ out;
	पूर्ण

	चयन (ep.bus.parallel.bus_width) अणु
	हाल 4:
		pcdev->platक्रमm_flags |= PXA_CAMERA_DATAWIDTH_4;
		अवरोध;
	हाल 5:
		pcdev->platक्रमm_flags |= PXA_CAMERA_DATAWIDTH_5;
		अवरोध;
	हाल 8:
		pcdev->platक्रमm_flags |= PXA_CAMERA_DATAWIDTH_8;
		अवरोध;
	हाल 9:
		pcdev->platक्रमm_flags |= PXA_CAMERA_DATAWIDTH_9;
		अवरोध;
	हाल 10:
		pcdev->platक्रमm_flags |= PXA_CAMERA_DATAWIDTH_10;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ep.bus.parallel.flags & V4L2_MBUS_MASTER)
		pcdev->platक्रमm_flags |= PXA_CAMERA_MASTER;
	अगर (ep.bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		pcdev->platक्रमm_flags |= PXA_CAMERA_HSP;
	अगर (ep.bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		pcdev->platक्रमm_flags |= PXA_CAMERA_VSP;
	अगर (ep.bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		pcdev->platक्रमm_flags |= PXA_CAMERA_PCLK_EN | PXA_CAMERA_PCP;
	अगर (ep.bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		pcdev->platक्रमm_flags |= PXA_CAMERA_PCLK_EN;

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
				&pcdev->notअगरier,
				of_fwnode_handle(np),
				काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd))
		err = PTR_ERR(asd);
out:
	of_node_put(np);

	वापस err;
पूर्ण

अटल पूर्णांक pxa_camera_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa_camera_dev *pcdev;
	काष्ठा resource *res;
	व्योम __iomem *base;
	काष्ठा dma_slave_config config = अणु
		.src_addr_width = 0,
		.src_maxburst = 8,
		.direction = DMA_DEV_TO_MEM,
	पूर्ण;
	पूर्णांक irq;
	पूर्णांक err = 0, i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!res || irq < 0)
		वापस -ENODEV;

	pcdev = devm_kzalloc(&pdev->dev, माप(*pcdev), GFP_KERNEL);
	अगर (!pcdev) अणु
		dev_err(&pdev->dev, "Could not allocate pcdev\n");
		वापस -ENOMEM;
	पूर्ण

	pcdev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pcdev->clk))
		वापस PTR_ERR(pcdev->clk);

	v4l2_async_notअगरier_init(&pcdev->notअगरier);
	pcdev->res = res;
	pcdev->pdata = pdev->dev.platक्रमm_data;
	अगर (pcdev->pdata) अणु
		काष्ठा v4l2_async_subdev *asd;

		pcdev->platक्रमm_flags = pcdev->pdata->flags;
		pcdev->mclk = pcdev->pdata->mclk_10khz * 10000;
		asd = v4l2_async_notअगरier_add_i2c_subdev(
				&pcdev->notअगरier,
				pcdev->pdata->sensor_i2c_adapter_id,
				pcdev->pdata->sensor_i2c_address,
				काष्ठा v4l2_async_subdev);
		अगर (IS_ERR(asd))
			err = PTR_ERR(asd);
	पूर्ण अन्यथा अगर (pdev->dev.of_node) अणु
		err = pxa_camera_pdata_from_dt(&pdev->dev, pcdev);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण
	अगर (err < 0)
		वापस err;

	अगर (!(pcdev->platक्रमm_flags & (PXA_CAMERA_DATAWIDTH_8 |
			PXA_CAMERA_DATAWIDTH_9 | PXA_CAMERA_DATAWIDTH_10))) अणु
		/*
		 * Platक्रमm hasn't set available data widths. This is bad.
		 * Warn and use a शेष.
		 */
		dev_warn(&pdev->dev, "WARNING! Platform hasn't set available data widths, using default 10 bit\n");
		pcdev->platक्रमm_flags |= PXA_CAMERA_DATAWIDTH_10;
	पूर्ण
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_DATAWIDTH_8)
		pcdev->width_flags = 1 << 7;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_DATAWIDTH_9)
		pcdev->width_flags |= 1 << 8;
	अगर (pcdev->platक्रमm_flags & PXA_CAMERA_DATAWIDTH_10)
		pcdev->width_flags |= 1 << 9;
	अगर (!pcdev->mclk) अणु
		dev_warn(&pdev->dev,
			 "mclk == 0! Please, fix your platform data. Using default 20MHz\n");
		pcdev->mclk = 20000000;
	पूर्ण

	pcdev->mclk_भागisor = mclk_get_भागisor(pdev, pcdev);

	INIT_LIST_HEAD(&pcdev->capture);
	spin_lock_init(&pcdev->lock);
	mutex_init(&pcdev->mlock);

	/*
	 * Request the regions.
	 */
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	pcdev->irq = irq;
	pcdev->base = base;

	/* request dma */
	pcdev->dma_chans[0] = dma_request_chan(&pdev->dev, "CI_Y");
	अगर (IS_ERR(pcdev->dma_chans[0])) अणु
		dev_err(&pdev->dev, "Can't request DMA for Y\n");
		वापस PTR_ERR(pcdev->dma_chans[0]);
	पूर्ण

	pcdev->dma_chans[1] = dma_request_chan(&pdev->dev, "CI_U");
	अगर (IS_ERR(pcdev->dma_chans[1])) अणु
		dev_err(&pdev->dev, "Can't request DMA for U\n");
		err = PTR_ERR(pcdev->dma_chans[1]);
		जाओ निकास_मुक्त_dma_y;
	पूर्ण

	pcdev->dma_chans[2] = dma_request_chan(&pdev->dev, "CI_V");
	अगर (IS_ERR(pcdev->dma_chans[2])) अणु
		dev_err(&pdev->dev, "Can't request DMA for V\n");
		err = PTR_ERR(pcdev->dma_chans[2]);
		जाओ निकास_मुक्त_dma_u;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		config.src_addr = pcdev->res->start + CIBR0 + i * 8;
		err = dmaengine_slave_config(pcdev->dma_chans[i], &config);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "dma slave config failed: %d\n",
				err);
			जाओ निकास_मुक्त_dma;
		पूर्ण
	पूर्ण

	/* request irq */
	err = devm_request_irq(&pdev->dev, pcdev->irq, pxa_camera_irq, 0,
			       PXA_CAM_DRV_NAME, pcdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Camera interrupt register failed\n");
		जाओ निकास_मुक्त_dma;
	पूर्ण

	tasklet_setup(&pcdev->task_eof, pxa_camera_eof);

	pxa_camera_activate(pcdev);

	platक्रमm_set_drvdata(pdev, pcdev);
	err = v4l2_device_रेजिस्टर(&pdev->dev, &pcdev->v4l2_dev);
	अगर (err)
		जाओ निकास_deactivate;

	err = pxa_camera_init_videobuf2(pcdev);
	अगर (err)
		जाओ निकास_notअगरier_cleanup;

	pcdev->notअगरier.ops = &pxa_camera_sensor_ops;
	err = v4l2_async_notअगरier_रेजिस्टर(&pcdev->v4l2_dev, &pcdev->notअगरier);
	अगर (err)
		जाओ निकास_notअगरier_cleanup;

	वापस 0;
निकास_notअगरier_cleanup:
	v4l2_async_notअगरier_cleanup(&pcdev->notअगरier);
	v4l2_device_unरेजिस्टर(&pcdev->v4l2_dev);
निकास_deactivate:
	pxa_camera_deactivate(pcdev);
	tasklet_समाप्त(&pcdev->task_eof);
निकास_मुक्त_dma:
	dma_release_channel(pcdev->dma_chans[2]);
निकास_मुक्त_dma_u:
	dma_release_channel(pcdev->dma_chans[1]);
निकास_मुक्त_dma_y:
	dma_release_channel(pcdev->dma_chans[0]);
	वापस err;
पूर्ण

अटल पूर्णांक pxa_camera_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa_camera_dev *pcdev = platक्रमm_get_drvdata(pdev);

	pxa_camera_deactivate(pcdev);
	tasklet_समाप्त(&pcdev->task_eof);
	dma_release_channel(pcdev->dma_chans[0]);
	dma_release_channel(pcdev->dma_chans[1]);
	dma_release_channel(pcdev->dma_chans[2]);

	v4l2_async_notअगरier_unरेजिस्टर(&pcdev->notअगरier);
	v4l2_async_notअगरier_cleanup(&pcdev->notअगरier);

	v4l2_device_unरेजिस्टर(&pcdev->v4l2_dev);

	dev_info(&pdev->dev, "PXA Camera driver unloaded\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pxa_camera_pm = अणु
	.suspend	= pxa_camera_suspend,
	.resume		= pxa_camera_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pxa_camera_of_match[] = अणु
	अणु .compatible = "marvell,pxa270-qci", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa_camera_of_match);

अटल काष्ठा platक्रमm_driver pxa_camera_driver = अणु
	.driver		= अणु
		.name	= PXA_CAM_DRV_NAME,
		.pm	= &pxa_camera_pm,
		.of_match_table = of_match_ptr(pxa_camera_of_match),
	पूर्ण,
	.probe		= pxa_camera_probe,
	.हटाओ		= pxa_camera_हटाओ,
पूर्ण;

module_platक्रमm_driver(pxa_camera_driver);

MODULE_DESCRIPTION("PXA27x Camera Driver");
MODULE_AUTHOR("Guennadi Liakhovetski <kernel@pengutronix.de>");
MODULE_LICENSE("GPL");
MODULE_VERSION(PXA_CAM_VERSION);
MODULE_ALIAS("platform:" PXA_CAM_DRV_NAME);
