<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap-mcpdm.h
 *
 * Copyright (C) 2009 - 2011 Texas Instruments
 *
 * Contact: Misael Lopez Cruz <misael.lopez@ti.com>
 */

#अगर_अघोषित __OMAP_MCPDM_H__
#घोषणा __OMAP_MCPDM_H__

#घोषणा MCPDM_REG_REVISION		0x00
#घोषणा MCPDM_REG_SYSCONFIG		0x10
#घोषणा MCPDM_REG_IRQSTATUS_RAW		0x24
#घोषणा MCPDM_REG_IRQSTATUS		0x28
#घोषणा MCPDM_REG_IRQENABLE_SET		0x2C
#घोषणा MCPDM_REG_IRQENABLE_CLR		0x30
#घोषणा MCPDM_REG_IRQWAKE_EN		0x34
#घोषणा MCPDM_REG_DMAENABLE_SET		0x38
#घोषणा MCPDM_REG_DMAENABLE_CLR		0x3C
#घोषणा MCPDM_REG_DMAWAKEEN		0x40
#घोषणा MCPDM_REG_CTRL			0x44
#घोषणा MCPDM_REG_DN_DATA		0x48
#घोषणा MCPDM_REG_UP_DATA		0x4C
#घोषणा MCPDM_REG_FIFO_CTRL_DN		0x50
#घोषणा MCPDM_REG_FIFO_CTRL_UP		0x54
#घोषणा MCPDM_REG_DN_OFFSET		0x58

/*
 * MCPDM_IRQ bit fields
 * IRQSTATUS_RAW, IRQSTATUS, IRQENABLE_SET, IRQENABLE_CLR
 */

#घोषणा MCPDM_DN_IRQ			(1 << 0)
#घोषणा MCPDM_DN_IRQ_EMPTY		(1 << 1)
#घोषणा MCPDM_DN_IRQ_ALMST_EMPTY	(1 << 2)
#घोषणा MCPDM_DN_IRQ_FULL		(1 << 3)

#घोषणा MCPDM_UP_IRQ			(1 << 8)
#घोषणा MCPDM_UP_IRQ_EMPTY		(1 << 9)
#घोषणा MCPDM_UP_IRQ_ALMST_FULL		(1 << 10)
#घोषणा MCPDM_UP_IRQ_FULL		(1 << 11)

#घोषणा MCPDM_DOWNLINK_IRQ_MASK		0x00F
#घोषणा MCPDM_UPLINK_IRQ_MASK		0xF00

/*
 * MCPDM_DMAENABLE bit fields
 */

#घोषणा MCPDM_DMA_DN_ENABLE		(1 << 0)
#घोषणा MCPDM_DMA_UP_ENABLE		(1 << 1)

/*
 * MCPDM_CTRL bit fields
 */

#घोषणा MCPDM_PDM_UPLINK_EN(x)		(1 << (x - 1)) /* ch1 is at bit 0 */
#घोषणा MCPDM_PDM_DOWNLINK_EN(x)	(1 << (x + 2)) /* ch1 is at bit 3 */
#घोषणा MCPDM_PDMOUTFORMAT		(1 << 8)
#घोषणा MCPDM_CMD_INT			(1 << 9)
#घोषणा MCPDM_STATUS_INT		(1 << 10)
#घोषणा MCPDM_SW_UP_RST			(1 << 11)
#घोषणा MCPDM_SW_DN_RST			(1 << 12)
#घोषणा MCPDM_WD_EN			(1 << 14)
#घोषणा MCPDM_PDM_UP_MASK		0x7
#घोषणा MCPDM_PDM_DN_MASK		(0x1f << 3)


#घोषणा MCPDM_PDMOUTFORMAT_LJUST	(0 << 8)
#घोषणा MCPDM_PDMOUTFORMAT_RJUST	(1 << 8)

/*
 * MCPDM_FIFO_CTRL bit fields
 */

#घोषणा MCPDM_UP_THRES_MAX		0xF
#घोषणा MCPDM_DN_THRES_MAX		0xF

/*
 * MCPDM_DN_OFFSET bit fields
 */

#घोषणा MCPDM_DN_OFST_RX1_EN		(1 << 0)
#घोषणा MCPDM_DNOFST_RX1(x)		((x & 0x1f) << 1)
#घोषणा MCPDM_DN_OFST_RX2_EN		(1 << 8)
#घोषणा MCPDM_DNOFST_RX2(x)		((x & 0x1f) << 9)

व्योम omap_mcpdm_configure_dn_offsets(काष्ठा snd_soc_pcm_runसमय *rtd,
				    u8 rx1, u8 rx2);

#पूर्ण_अगर	/* End of __OMAP_MCPDM_H__ */
