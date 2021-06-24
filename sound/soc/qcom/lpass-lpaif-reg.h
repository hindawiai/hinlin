<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __LPASS_LPAIF_REG_H__
#घोषणा __LPASS_LPAIF_REG_H__

/* LPAIF I2S */

#घोषणा LPAIF_I2SCTL_REG_ADDR(v, addr, port) \
	(v->i2sctrl_reg_base + (addr) + v->i2sctrl_reg_stride * (port))

#घोषणा LPAIF_I2SCTL_REG(v, port)	LPAIF_I2SCTL_REG_ADDR(v, 0x0, (port))

#घोषणा LPAIF_I2SCTL_LOOPBACK_DISABLE	0
#घोषणा LPAIF_I2SCTL_LOOPBACK_ENABLE	1

#घोषणा LPAIF_I2SCTL_SPKEN_DISABLE	0
#घोषणा LPAIF_I2SCTL_SPKEN_ENABLE	1

#घोषणा LPAIF_I2SCTL_MODE_NONE		0
#घोषणा LPAIF_I2SCTL_MODE_SD0		1
#घोषणा LPAIF_I2SCTL_MODE_SD1		2
#घोषणा LPAIF_I2SCTL_MODE_SD2		3
#घोषणा LPAIF_I2SCTL_MODE_SD3		4
#घोषणा LPAIF_I2SCTL_MODE_QUAD01	5
#घोषणा LPAIF_I2SCTL_MODE_QUAD23	6
#घोषणा LPAIF_I2SCTL_MODE_6CH		7
#घोषणा LPAIF_I2SCTL_MODE_8CH		8
#घोषणा LPAIF_I2SCTL_MODE_10CH		9
#घोषणा LPAIF_I2SCTL_MODE_12CH		10
#घोषणा LPAIF_I2SCTL_MODE_14CH		11
#घोषणा LPAIF_I2SCTL_MODE_16CH		12
#घोषणा LPAIF_I2SCTL_MODE_SD4		13
#घोषणा LPAIF_I2SCTL_MODE_SD5		14
#घोषणा LPAIF_I2SCTL_MODE_SD6		15
#घोषणा LPAIF_I2SCTL_MODE_SD7		16
#घोषणा LPAIF_I2SCTL_MODE_QUAD45	17
#घोषणा LPAIF_I2SCTL_MODE_QUAD47	18
#घोषणा LPAIF_I2SCTL_MODE_8CH_2		19

#घोषणा LPAIF_I2SCTL_SPKMODE(mode)	mode

#घोषणा LPAIF_I2SCTL_SPKMONO_STEREO	0
#घोषणा LPAIF_I2SCTL_SPKMONO_MONO	1

#घोषणा LPAIF_I2SCTL_MICEN_DISABLE	0
#घोषणा LPAIF_I2SCTL_MICEN_ENABLE	1

#घोषणा LPAIF_I2SCTL_MICMODE(mode)	mode

#घोषणा LPAIF_I2SCTL_MICMONO_STEREO	0
#घोषणा LPAIF_I2SCTL_MICMONO_MONO	1

#घोषणा LPAIF_I2SCTL_WSSRC_INTERNAL	0
#घोषणा LPAIF_I2SCTL_WSSRC_EXTERNAL	1

#घोषणा LPAIF_I2SCTL_BITWIDTH_16	0
#घोषणा LPAIF_I2SCTL_BITWIDTH_24	1
#घोषणा LPAIF_I2SCTL_BITWIDTH_32	2

#घोषणा LPAIF_I2SCTL_RESET_STATE	0x003C0004
#घोषणा LPAIF_DMACTL_RESET_STATE	0x00200000


/* LPAIF IRQ */
#घोषणा LPAIF_IRQ_REG_ADDR(v, addr, port) \
	(v->irq_reg_base + (addr) + v->irq_reg_stride * (port))

#घोषणा LPAIF_IRQ_PORT_HOST		0

#घोषणा LPAIF_IRQEN_REG(v, port)	LPAIF_IRQ_REG_ADDR(v, 0x0, (port))
#घोषणा LPAIF_IRQSTAT_REG(v, port)	LPAIF_IRQ_REG_ADDR(v, 0x4, (port))
#घोषणा LPAIF_IRQCLEAR_REG(v, port)	LPAIF_IRQ_REG_ADDR(v, 0xC, (port))


#घोषणा LPASS_HDMITX_APP_IRQ_REG_ADDR(v, addr)  \
	((v->hdmi_irq_reg_base) + (addr))

#घोषणा LPASS_HDMITX_APP_IRQEN_REG(v)			LPASS_HDMITX_APP_IRQ_REG_ADDR(v, 0x4)
#घोषणा LPASS_HDMITX_APP_IRQSTAT_REG(v)			LPASS_HDMITX_APP_IRQ_REG_ADDR(v, 0x8)
#घोषणा LPASS_HDMITX_APP_IRQCLEAR_REG(v)		LPASS_HDMITX_APP_IRQ_REG_ADDR(v, 0xC)

#घोषणा LPAIF_IRQ_BITSTRIDE		3

#घोषणा LPAIF_IRQ_PER(chan)		(1 << (LPAIF_IRQ_BITSTRIDE * (chan)))
#घोषणा LPAIF_IRQ_XRUN(chan)		(2 << (LPAIF_IRQ_BITSTRIDE * (chan)))
#घोषणा LPAIF_IRQ_ERR(chan)		(4 << (LPAIF_IRQ_BITSTRIDE * (chan)))

#घोषणा LPAIF_IRQ_ALL(chan)		(7 << (LPAIF_IRQ_BITSTRIDE * (chan)))
#घोषणा LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(chan)	(1 << (14 + chan))
#घोषणा LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(chan)	(1 << (24 + chan))
#घोषणा LPAIF_IRQ_HDMI_METADONE		BIT(23)

/* LPAIF DMA */
#घोषणा LPAIF_HDMI_RDMA_REG_ADDR(v, addr, chan) \
	(v->hdmi_rdma_reg_base + (addr) + v->hdmi_rdma_reg_stride * (chan))

#घोषणा LPAIF_HDMI_RDMACTL_AUDINTF(id)	(id << LPAIF_RDMACTL_AUDINTF_SHIFT)

#घोषणा LPAIF_HDMI_RDMACTL_REG(v, chan)		LPAIF_HDMI_RDMA_REG_ADDR(v, 0x00, (chan))
#घोषणा LPAIF_HDMI_RDMABASE_REG(v, chan)	LPAIF_HDMI_RDMA_REG_ADDR(v, 0x04, (chan))
#घोषणा	LPAIF_HDMI_RDMABUFF_REG(v, chan)	LPAIF_HDMI_RDMA_REG_ADDR(v, 0x08, (chan))
#घोषणा LPAIF_HDMI_RDMACURR_REG(v, chan)	LPAIF_HDMI_RDMA_REG_ADDR(v, 0x0C, (chan))
#घोषणा	LPAIF_HDMI_RDMAPER_REG(v, chan)		LPAIF_HDMI_RDMA_REG_ADDR(v, 0x10, (chan))
#घोषणा	LPAIF_HDMI_RDMAPERCNT_REG(v, chan)	LPAIF_HDMI_RDMA_REG_ADDR(v, 0x14, (chan))

#घोषणा LPAIF_RDMA_REG_ADDR(v, addr, chan) \
	(v->rdma_reg_base + (addr) + v->rdma_reg_stride * (chan))

#घोषणा LPAIF_RDMACTL_AUDINTF(id)	(id << LPAIF_RDMACTL_AUDINTF_SHIFT)

#घोषणा LPAIF_RDMACTL_REG(v, chan)	LPAIF_RDMA_REG_ADDR(v, 0x00, (chan))
#घोषणा LPAIF_RDMABASE_REG(v, chan)	LPAIF_RDMA_REG_ADDR(v, 0x04, (chan))
#घोषणा	LPAIF_RDMABUFF_REG(v, chan)	LPAIF_RDMA_REG_ADDR(v, 0x08, (chan))
#घोषणा LPAIF_RDMACURR_REG(v, chan)	LPAIF_RDMA_REG_ADDR(v, 0x0C, (chan))
#घोषणा	LPAIF_RDMAPER_REG(v, chan)	LPAIF_RDMA_REG_ADDR(v, 0x10, (chan))
#घोषणा	LPAIF_RDMAPERCNT_REG(v, chan)	LPAIF_RDMA_REG_ADDR(v, 0x14, (chan))

#घोषणा LPAIF_WRDMA_REG_ADDR(v, addr, chan) \
	(v->wrdma_reg_base + (addr) + \
	 v->wrdma_reg_stride * (chan - v->wrdma_channel_start))

#घोषणा LPAIF_WRDMACTL_REG(v, chan)	LPAIF_WRDMA_REG_ADDR(v, 0x00, (chan))
#घोषणा LPAIF_WRDMABASE_REG(v, chan)	LPAIF_WRDMA_REG_ADDR(v, 0x04, (chan))
#घोषणा	LPAIF_WRDMABUFF_REG(v, chan)	LPAIF_WRDMA_REG_ADDR(v, 0x08, (chan))
#घोषणा LPAIF_WRDMACURR_REG(v, chan)	LPAIF_WRDMA_REG_ADDR(v, 0x0C, (chan))
#घोषणा	LPAIF_WRDMAPER_REG(v, chan)	LPAIF_WRDMA_REG_ADDR(v, 0x10, (chan))
#घोषणा	LPAIF_WRDMAPERCNT_REG(v, chan)	LPAIF_WRDMA_REG_ADDR(v, 0x14, (chan))

#घोषणा LPAIF_INTFDMA_REG(v, chan, reg, dai_id)  \
	((dai_id ==  LPASS_DP_RX) ? \
		LPAIF_HDMI_RDMA##reg##_REG(v, chan) : \
		 LPAIF_RDMA##reg##_REG(v, chan))

#घोषणा __LPAIF_DMA_REG(v, chan, dir, reg, dai_id)  \
	((dir ==  SNDRV_PCM_STREAM_PLAYBACK) ? \
		(LPAIF_INTFDMA_REG(v, chan, reg, dai_id)) : \
		LPAIF_WRDMA##reg##_REG(v, chan))

#घोषणा LPAIF_DMACTL_REG(v, chan, dir, dai_id) __LPAIF_DMA_REG(v, chan, dir, CTL, dai_id)
#घोषणा LPAIF_DMABASE_REG(v, chan, dir, dai_id) __LPAIF_DMA_REG(v, chan, dir, BASE, dai_id)
#घोषणा	LPAIF_DMABUFF_REG(v, chan, dir, dai_id) __LPAIF_DMA_REG(v, chan, dir, BUFF, dai_id)
#घोषणा LPAIF_DMACURR_REG(v, chan, dir, dai_id) __LPAIF_DMA_REG(v, chan, dir, CURR, dai_id)
#घोषणा	LPAIF_DMAPER_REG(v, chan, dir, dai_id) __LPAIF_DMA_REG(v, chan, dir, PER, dai_id)
#घोषणा	LPAIF_DMAPERCNT_REG(v, chan, dir, dai_id) __LPAIF_DMA_REG(v, chan, dir, PERCNT, dai_id)

#घोषणा LPAIF_DMACTL_BURSTEN_SINGLE	0
#घोषणा LPAIF_DMACTL_BURSTEN_INCR4	1

#घोषणा LPAIF_DMACTL_WPSCNT_ONE		0
#घोषणा LPAIF_DMACTL_WPSCNT_TWO		1
#घोषणा LPAIF_DMACTL_WPSCNT_THREE	2
#घोषणा LPAIF_DMACTL_WPSCNT_FOUR	3
#घोषणा LPAIF_DMACTL_WPSCNT_SIX		5
#घोषणा LPAIF_DMACTL_WPSCNT_EIGHT	7
#घोषणा LPAIF_DMACTL_WPSCNT_TEN		9
#घोषणा LPAIF_DMACTL_WPSCNT_TWELVE	11
#घोषणा LPAIF_DMACTL_WPSCNT_FOURTEEN	13
#घोषणा LPAIF_DMACTL_WPSCNT_SIXTEEN	15

#घोषणा LPAIF_DMACTL_AUDINTF(id)	id

#घोषणा LPAIF_DMACTL_FIFOWM_1		0
#घोषणा LPAIF_DMACTL_FIFOWM_2		1
#घोषणा LPAIF_DMACTL_FIFOWM_3		2
#घोषणा LPAIF_DMACTL_FIFOWM_4		3
#घोषणा LPAIF_DMACTL_FIFOWM_5		4
#घोषणा LPAIF_DMACTL_FIFOWM_6		5
#घोषणा LPAIF_DMACTL_FIFOWM_7		6
#घोषणा LPAIF_DMACTL_FIFOWM_8		7
#घोषणा LPAIF_DMACTL_FIFOWM_9		8
#घोषणा LPAIF_DMACTL_FIFOWM_10		9
#घोषणा LPAIF_DMACTL_FIFOWM_11		10
#घोषणा LPAIF_DMACTL_FIFOWM_12		11
#घोषणा LPAIF_DMACTL_FIFOWM_13		12
#घोषणा LPAIF_DMACTL_FIFOWM_14		13
#घोषणा LPAIF_DMACTL_FIFOWM_15		14
#घोषणा LPAIF_DMACTL_FIFOWM_16		15
#घोषणा LPAIF_DMACTL_FIFOWM_17		16
#घोषणा LPAIF_DMACTL_FIFOWM_18		17
#घोषणा LPAIF_DMACTL_FIFOWM_19		18
#घोषणा LPAIF_DMACTL_FIFOWM_20		19
#घोषणा LPAIF_DMACTL_FIFOWM_21		20
#घोषणा LPAIF_DMACTL_FIFOWM_22		21
#घोषणा LPAIF_DMACTL_FIFOWM_23		22
#घोषणा LPAIF_DMACTL_FIFOWM_24		23
#घोषणा LPAIF_DMACTL_FIFOWM_25		24
#घोषणा LPAIF_DMACTL_FIFOWM_26		25
#घोषणा LPAIF_DMACTL_FIFOWM_27		26
#घोषणा LPAIF_DMACTL_FIFOWM_28		27
#घोषणा LPAIF_DMACTL_FIFOWM_29		28
#घोषणा LPAIF_DMACTL_FIFOWM_30		29
#घोषणा LPAIF_DMACTL_FIFOWM_31		30
#घोषणा LPAIF_DMACTL_FIFOWM_32		31

#घोषणा LPAIF_DMACTL_ENABLE_OFF		0
#घोषणा LPAIF_DMACTL_ENABLE_ON		1

#घोषणा LPAIF_DMACTL_DYNCLK_OFF		0
#घोषणा LPAIF_DMACTL_DYNCLK_ON		1

#पूर्ण_अगर /* __LPASS_LPAIF_REG_H__ */
