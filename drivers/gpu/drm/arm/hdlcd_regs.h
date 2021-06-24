<शैली गुरु>
/*
 * Copyright (C) 2013,2014 ARM Limited
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 *  ARM HDLCD Controller रेजिस्टर definition
 */

#अगर_अघोषित __HDLCD_REGS_H__
#घोषणा __HDLCD_REGS_H__

/* रेजिस्टर offsets */
#घोषणा HDLCD_REG_VERSION		0x0000	/* ro */
#घोषणा HDLCD_REG_INT_RAWSTAT		0x0010	/* rw */
#घोषणा HDLCD_REG_INT_CLEAR		0x0014	/* wo */
#घोषणा HDLCD_REG_INT_MASK		0x0018	/* rw */
#घोषणा HDLCD_REG_INT_STATUS		0x001c	/* ro */
#घोषणा HDLCD_REG_FB_BASE		0x0100	/* rw */
#घोषणा HDLCD_REG_FB_LINE_LENGTH	0x0104	/* rw */
#घोषणा HDLCD_REG_FB_LINE_COUNT		0x0108	/* rw */
#घोषणा HDLCD_REG_FB_LINE_PITCH		0x010c	/* rw */
#घोषणा HDLCD_REG_BUS_OPTIONS		0x0110	/* rw */
#घोषणा HDLCD_REG_V_SYNC		0x0200	/* rw */
#घोषणा HDLCD_REG_V_BACK_PORCH		0x0204	/* rw */
#घोषणा HDLCD_REG_V_DATA		0x0208	/* rw */
#घोषणा HDLCD_REG_V_FRONT_PORCH		0x020c	/* rw */
#घोषणा HDLCD_REG_H_SYNC		0x0210	/* rw */
#घोषणा HDLCD_REG_H_BACK_PORCH		0x0214	/* rw */
#घोषणा HDLCD_REG_H_DATA		0x0218	/* rw */
#घोषणा HDLCD_REG_H_FRONT_PORCH		0x021c	/* rw */
#घोषणा HDLCD_REG_POLARITIES		0x0220	/* rw */
#घोषणा HDLCD_REG_COMMAND		0x0230	/* rw */
#घोषणा HDLCD_REG_PIXEL_FORMAT		0x0240	/* rw */
#घोषणा HDLCD_REG_RED_SELECT		0x0244	/* rw */
#घोषणा HDLCD_REG_GREEN_SELECT		0x0248	/* rw */
#घोषणा HDLCD_REG_BLUE_SELECT		0x024c	/* rw */

/* version */
#घोषणा HDLCD_PRODUCT_ID		0x1CDC0000
#घोषणा HDLCD_PRODUCT_MASK		0xFFFF0000
#घोषणा HDLCD_VERSION_MAJOR_MASK	0x0000FF00
#घोषणा HDLCD_VERSION_MINOR_MASK	0x000000FF

/* पूर्णांकerrupts */
#घोषणा HDLCD_INTERRUPT_DMA_END		(1 << 0)
#घोषणा HDLCD_INTERRUPT_BUS_ERROR	(1 << 1)
#घोषणा HDLCD_INTERRUPT_VSYNC		(1 << 2)
#घोषणा HDLCD_INTERRUPT_UNDERRUN	(1 << 3)
#घोषणा HDLCD_DEBUG_INT_MASK		(HDLCD_INTERRUPT_DMA_END |  \
					HDLCD_INTERRUPT_BUS_ERROR | \
					HDLCD_INTERRUPT_UNDERRUN)

/* polarities */
#घोषणा HDLCD_POLARITY_VSYNC		(1 << 0)
#घोषणा HDLCD_POLARITY_HSYNC		(1 << 1)
#घोषणा HDLCD_POLARITY_DATAEN		(1 << 2)
#घोषणा HDLCD_POLARITY_DATA		(1 << 3)
#घोषणा HDLCD_POLARITY_PIXELCLK		(1 << 4)

/* commands */
#घोषणा HDLCD_COMMAND_DISABLE		(0 << 0)
#घोषणा HDLCD_COMMAND_ENABLE		(1 << 0)

/* pixel क्रमmat */
#घोषणा HDLCD_PIXEL_FMT_LITTLE_ENDIAN	(0 << 31)
#घोषणा HDLCD_PIXEL_FMT_BIG_ENDIAN	(1 << 31)
#घोषणा HDLCD_BYTES_PER_PIXEL_MASK	(3 << 3)

/* bus options */
#घोषणा HDLCD_BUS_BURST_MASK		0x01f
#घोषणा HDLCD_BUS_MAX_OUTSTAND		0xf00
#घोषणा HDLCD_BUS_BURST_NONE		(0 << 0)
#घोषणा HDLCD_BUS_BURST_1		(1 << 0)
#घोषणा HDLCD_BUS_BURST_2		(1 << 1)
#घोषणा HDLCD_BUS_BURST_4		(1 << 2)
#घोषणा HDLCD_BUS_BURST_8		(1 << 3)
#घोषणा HDLCD_BUS_BURST_16		(1 << 4)

/* Max resolution supported is 4096x4096, 32bpp */
#घोषणा HDLCD_MAX_XRES			4096
#घोषणा HDLCD_MAX_YRES			4096

#घोषणा NR_PALETTE			256

#पूर्ण_अगर /* __HDLCD_REGS_H__ */
