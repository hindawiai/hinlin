<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Rockchip PDM ALSA SoC Digital Audio Interface(DAI)  driver
 *
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co., Ltd
 */

#अगर_अघोषित _ROCKCHIP_PDM_H
#घोषणा _ROCKCHIP_PDM_H

/* PDM REGS */
#घोषणा PDM_SYSCONFIG	(0x0000)
#घोषणा PDM_CTRL0	(0x0004)
#घोषणा PDM_CTRL1	(0x0008)
#घोषणा PDM_CLK_CTRL	(0x000c)
#घोषणा PDM_HPF_CTRL	(0x0010)
#घोषणा PDM_FIFO_CTRL	(0x0014)
#घोषणा PDM_DMA_CTRL	(0x0018)
#घोषणा PDM_INT_EN	(0x001c)
#घोषणा PDM_INT_CLR	(0x0020)
#घोषणा PDM_INT_ST	(0x0024)
#घोषणा PDM_RXFIFO_DATA	(0x0030)
#घोषणा PDM_DATA_VALID	(0x0054)
#घोषणा PDM_VERSION	(0x0058)

/* PDM_SYSCONFIG */
#घोषणा PDM_RX_MASK		(0x1 << 2)
#घोषणा PDM_RX_START		(0x1 << 2)
#घोषणा PDM_RX_STOP		(0x0 << 2)
#घोषणा PDM_RX_CLR_MASK		(0x1 << 0)
#घोषणा PDM_RX_CLR_WR		(0x1 << 0)
#घोषणा PDM_RX_CLR_DONE		(0x0 << 0)

/* PDM CTRL0 */
#घोषणा PDM_PATH_MSK		(0xf << 27)
#घोषणा PDM_MODE_MSK		BIT(31)
#घोषणा PDM_MODE_RJ		0
#घोषणा PDM_MODE_LJ		BIT(31)
#घोषणा PDM_PATH3_EN		BIT(30)
#घोषणा PDM_PATH2_EN		BIT(29)
#घोषणा PDM_PATH1_EN		BIT(28)
#घोषणा PDM_PATH0_EN		BIT(27)
#घोषणा PDM_HWT_EN		BIT(26)
#घोषणा PDM_VDW_MSK		(0x1f << 0)
#घोषणा PDM_VDW(X)		((X - 1) << 0)

/* PDM CTRL1 */
#घोषणा PDM_FD_NUMERATOR_SFT	16
#घोषणा PDM_FD_NUMERATOR_MSK	GENMASK(31, 16)
#घोषणा PDM_FD_DENOMINATOR_SFT	0
#घोषणा PDM_FD_DENOMINATOR_MSK	GENMASK(15, 0)

/* PDM CLK CTRL */
#घोषणा PDM_CLK_FD_RATIO_MSK	BIT(6)
#घोषणा PDM_CLK_FD_RATIO_40	(0X0 << 6)
#घोषणा PDM_CLK_FD_RATIO_35	BIT(6)
#घोषणा PDM_CLK_MSK		BIT(5)
#घोषणा PDM_CLK_EN		BIT(5)
#घोषणा PDM_CLK_DIS		(0x0 << 5)
#घोषणा PDM_CKP_MSK		BIT(3)
#घोषणा PDM_CKP_NORMAL		(0x0 << 3)
#घोषणा PDM_CKP_INVERTED	BIT(3)
#घोषणा PDM_DS_RATIO_MSK	(0x7 << 0)
#घोषणा PDM_CLK_320FS		(0x0 << 0)
#घोषणा PDM_CLK_640FS		(0x1 << 0)
#घोषणा PDM_CLK_1280FS		(0x2 << 0)
#घोषणा PDM_CLK_2560FS		(0x3 << 0)
#घोषणा PDM_CLK_5120FS		(0x4 << 0)

/* PDM HPF CTRL */
#घोषणा PDM_HPF_LE		BIT(3)
#घोषणा PDM_HPF_RE		BIT(2)
#घोषणा PDM_HPF_CF_MSK		(0x3 << 0)
#घोषणा PDM_HPF_3P79HZ		(0x0 << 0)
#घोषणा PDM_HPF_60HZ		(0x1 << 0)
#घोषणा PDM_HPF_243HZ		(0x2 << 0)
#घोषणा PDM_HPF_493HZ		(0x3 << 0)

/* PDM DMA CTRL */
#घोषणा PDM_DMA_RD_MSK		BIT(8)
#घोषणा PDM_DMA_RD_EN		BIT(8)
#घोषणा PDM_DMA_RD_DIS		(0x0 << 8)
#घोषणा PDM_DMA_RDL_MSK		(0x7f << 0)
#घोषणा PDM_DMA_RDL(X)		((X - 1) << 0)

#पूर्ण_अगर /* _ROCKCHIP_PDM_H */
