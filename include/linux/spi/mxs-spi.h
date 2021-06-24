<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/spi/mxs-spi.h
 *
 * Freescale i.MX233/i.MX28 SPI controller रेजिस्टर definition
 *
 * Copyright 2008 Embedded Alley Solutions, Inc.
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __LINUX_SPI_MXS_SPI_H__
#घोषणा __LINUX_SPI_MXS_SPI_H__

#समावेश <linux/dmaengine.h>

#घोषणा ssp_is_old(host)	((host)->devid == IMX23_SSP)

/* SSP रेजिस्टरs */
#घोषणा HW_SSP_CTRL0				0x000
#घोषणा  BM_SSP_CTRL0_RUN			(1 << 29)
#घोषणा  BM_SSP_CTRL0_SDIO_IRQ_CHECK		(1 << 28)
#घोषणा  BM_SSP_CTRL0_LOCK_CS			(1 << 27)
#घोषणा  BM_SSP_CTRL0_IGNORE_CRC		(1 << 26)
#घोषणा  BM_SSP_CTRL0_READ			(1 << 25)
#घोषणा  BM_SSP_CTRL0_DATA_XFER			(1 << 24)
#घोषणा  BP_SSP_CTRL0_BUS_WIDTH			22
#घोषणा  BM_SSP_CTRL0_BUS_WIDTH			(0x3 << 22)
#घोषणा  BM_SSP_CTRL0_WAIT_FOR_IRQ		(1 << 21)
#घोषणा  BM_SSP_CTRL0_WAIT_FOR_CMD		(1 << 20)
#घोषणा  BM_SSP_CTRL0_LONG_RESP			(1 << 19)
#घोषणा  BM_SSP_CTRL0_GET_RESP			(1 << 17)
#घोषणा  BM_SSP_CTRL0_ENABLE			(1 << 16)
#घोषणा  BP_SSP_CTRL0_XFER_COUNT		0
#घोषणा  BM_SSP_CTRL0_XFER_COUNT		0xffff
#घोषणा HW_SSP_CMD0				0x010
#घोषणा  BM_SSP_CMD0_DBL_DATA_RATE_EN		(1 << 25)
#घोषणा  BM_SSP_CMD0_SLOW_CLKING_EN		(1 << 22)
#घोषणा  BM_SSP_CMD0_CONT_CLKING_EN		(1 << 21)
#घोषणा  BM_SSP_CMD0_APPEND_8CYC		(1 << 20)
#घोषणा  BP_SSP_CMD0_BLOCK_SIZE			16
#घोषणा  BM_SSP_CMD0_BLOCK_SIZE			(0xf << 16)
#घोषणा  BP_SSP_CMD0_BLOCK_COUNT		8
#घोषणा  BM_SSP_CMD0_BLOCK_COUNT		(0xff << 8)
#घोषणा  BP_SSP_CMD0_CMD			0
#घोषणा  BM_SSP_CMD0_CMD			0xff
#घोषणा HW_SSP_CMD1				0x020
#घोषणा HW_SSP_XFER_SIZE			0x030
#घोषणा HW_SSP_BLOCK_SIZE			0x040
#घोषणा  BP_SSP_BLOCK_SIZE_BLOCK_COUNT		4
#घोषणा  BM_SSP_BLOCK_SIZE_BLOCK_COUNT		(0xffffff << 4)
#घोषणा  BP_SSP_BLOCK_SIZE_BLOCK_SIZE		0
#घोषणा  BM_SSP_BLOCK_SIZE_BLOCK_SIZE		0xf
#घोषणा HW_SSP_TIMING(h)			(ssp_is_old(h) ? 0x050 : 0x070)
#घोषणा  BP_SSP_TIMING_TIMEOUT			16
#घोषणा  BM_SSP_TIMING_TIMEOUT			(0xffff << 16)
#घोषणा  BP_SSP_TIMING_CLOCK_DIVIDE		8
#घोषणा  BM_SSP_TIMING_CLOCK_DIVIDE		(0xff << 8)
#घोषणा  BF_SSP_TIMING_CLOCK_DIVIDE(v)		\
			(((v) << 8) & BM_SSP_TIMING_CLOCK_DIVIDE)
#घोषणा  BP_SSP_TIMING_CLOCK_RATE		0
#घोषणा  BM_SSP_TIMING_CLOCK_RATE		0xff
#घोषणा BF_SSP_TIMING_CLOCK_RATE(v)		\
			(((v) << 0) & BM_SSP_TIMING_CLOCK_RATE)
#घोषणा HW_SSP_CTRL1(h)				(ssp_is_old(h) ? 0x060 : 0x080)
#घोषणा  BM_SSP_CTRL1_SDIO_IRQ			(1 << 31)
#घोषणा  BM_SSP_CTRL1_SDIO_IRQ_EN		(1 << 30)
#घोषणा  BM_SSP_CTRL1_RESP_ERR_IRQ		(1 << 29)
#घोषणा  BM_SSP_CTRL1_RESP_ERR_IRQ_EN		(1 << 28)
#घोषणा  BM_SSP_CTRL1_RESP_TIMEOUT_IRQ		(1 << 27)
#घोषणा  BM_SSP_CTRL1_RESP_TIMEOUT_IRQ_EN	(1 << 26)
#घोषणा  BM_SSP_CTRL1_DATA_TIMEOUT_IRQ		(1 << 25)
#घोषणा  BM_SSP_CTRL1_DATA_TIMEOUT_IRQ_EN	(1 << 24)
#घोषणा  BM_SSP_CTRL1_DATA_CRC_IRQ		(1 << 23)
#घोषणा  BM_SSP_CTRL1_DATA_CRC_IRQ_EN		(1 << 22)
#घोषणा  BM_SSP_CTRL1_FIFO_UNDERRUN_IRQ		(1 << 21)
#घोषणा  BM_SSP_CTRL1_FIFO_UNDERRUN_IRQ_EN	(1 << 20)
#घोषणा  BM_SSP_CTRL1_RECV_TIMEOUT_IRQ		(1 << 17)
#घोषणा  BM_SSP_CTRL1_RECV_TIMEOUT_IRQ_EN	(1 << 16)
#घोषणा  BM_SSP_CTRL1_FIFO_OVERRUN_IRQ		(1 << 15)
#घोषणा  BM_SSP_CTRL1_FIFO_OVERRUN_IRQ_EN	(1 << 14)
#घोषणा  BM_SSP_CTRL1_DMA_ENABLE		(1 << 13)
#घोषणा  BM_SSP_CTRL1_PHASE			(1 << 10)
#घोषणा  BM_SSP_CTRL1_POLARITY			(1 << 9)
#घोषणा  BP_SSP_CTRL1_WORD_LENGTH		4
#घोषणा  BM_SSP_CTRL1_WORD_LENGTH		(0xf << 4)
#घोषणा  BF_SSP_CTRL1_WORD_LENGTH(v)		\
			(((v) << 4) & BM_SSP_CTRL1_WORD_LENGTH)
#घोषणा  BV_SSP_CTRL1_WORD_LENGTH__FOUR_BITS	0x3
#घोषणा  BV_SSP_CTRL1_WORD_LENGTH__EIGHT_BITS	0x7
#घोषणा  BV_SSP_CTRL1_WORD_LENGTH__SIXTEEN_BITS	0xF
#घोषणा  BP_SSP_CTRL1_SSP_MODE			0
#घोषणा  BM_SSP_CTRL1_SSP_MODE			0xf
#घोषणा  BF_SSP_CTRL1_SSP_MODE(v)		\
			(((v) << 0) & BM_SSP_CTRL1_SSP_MODE)
#घोषणा  BV_SSP_CTRL1_SSP_MODE__SPI		0x0
#घोषणा  BV_SSP_CTRL1_SSP_MODE__SSI		0x1
#घोषणा  BV_SSP_CTRL1_SSP_MODE__SD_MMC		0x3
#घोषणा  BV_SSP_CTRL1_SSP_MODE__MS		0x4

#घोषणा HW_SSP_DATA(h)				(ssp_is_old(h) ? 0x070 : 0x090)

#घोषणा HW_SSP_SDRESP0(h)			(ssp_is_old(h) ? 0x080 : 0x0a0)
#घोषणा HW_SSP_SDRESP1(h)			(ssp_is_old(h) ? 0x090 : 0x0b0)
#घोषणा HW_SSP_SDRESP2(h)			(ssp_is_old(h) ? 0x0a0 : 0x0c0)
#घोषणा HW_SSP_SDRESP3(h)			(ssp_is_old(h) ? 0x0b0 : 0x0d0)
#घोषणा HW_SSP_STATUS(h)			(ssp_is_old(h) ? 0x0c0 : 0x100)
#घोषणा  BM_SSP_STATUS_CARD_DETECT		(1 << 28)
#घोषणा  BM_SSP_STATUS_SDIO_IRQ			(1 << 17)
#घोषणा  BM_SSP_STATUS_FIFO_EMPTY		(1 << 5)

#घोषणा BF_SSP(value, field)	(((value) << BP_SSP_##field) & BM_SSP_##field)

#घोषणा SSP_PIO_NUM	3

क्रमागत mxs_ssp_id अणु
	IMX23_SSP,
	IMX28_SSP,
पूर्ण;

काष्ठा mxs_ssp अणु
	काष्ठा device			*dev;
	व्योम __iomem			*base;
	काष्ठा clk			*clk;
	अचिन्हित पूर्णांक			clk_rate;
	क्रमागत mxs_ssp_id			devid;

	काष्ठा dma_chan			*dmach;
	अचिन्हित पूर्णांक			dma_dir;
	क्रमागत dma_transfer_direction	slave_dirn;
	u32				ssp_pio_words[SSP_PIO_NUM];
पूर्ण;

व्योम mxs_ssp_set_clk_rate(काष्ठा mxs_ssp *ssp, अचिन्हित पूर्णांक rate);

#पूर्ण_अगर	/* __LINUX_SPI_MXS_SPI_H__ */
