<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) STMicroelectronics SA 2017
 * Author(s): M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *            Pierre-Yves Mordret <pierre-yves.mordret@st.com>
 *
 * Driver क्रम STM32 MDMA controller
 *
 * Inspired by sपंचांग32-dma.c and dma-jz4780.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश "virt-dma.h"

/*  MDMA Generic getter/setter */
#घोषणा STM32_MDMA_SHIFT(n)		(ffs(n) - 1)
#घोषणा STM32_MDMA_SET(n, mask)		(((n) << STM32_MDMA_SHIFT(mask)) & \
					 (mask))
#घोषणा STM32_MDMA_GET(n, mask)		(((n) & (mask)) >> \
					 STM32_MDMA_SHIFT(mask))

#घोषणा STM32_MDMA_GISR0		0x0000 /* MDMA Int Status Reg 1 */
#घोषणा STM32_MDMA_GISR1		0x0004 /* MDMA Int Status Reg 2 */

/* MDMA Channel x पूर्णांकerrupt/status रेजिस्टर */
#घोषणा STM32_MDMA_CISR(x)		(0x40 + 0x40 * (x)) /* x = 0..62 */
#घोषणा STM32_MDMA_CISR_CRQA		BIT(16)
#घोषणा STM32_MDMA_CISR_TCIF		BIT(4)
#घोषणा STM32_MDMA_CISR_BTIF		BIT(3)
#घोषणा STM32_MDMA_CISR_BRTIF		BIT(2)
#घोषणा STM32_MDMA_CISR_CTCIF		BIT(1)
#घोषणा STM32_MDMA_CISR_TEIF		BIT(0)

/* MDMA Channel x पूर्णांकerrupt flag clear रेजिस्टर */
#घोषणा STM32_MDMA_CIFCR(x)		(0x44 + 0x40 * (x))
#घोषणा STM32_MDMA_CIFCR_CLTCIF		BIT(4)
#घोषणा STM32_MDMA_CIFCR_CBTIF		BIT(3)
#घोषणा STM32_MDMA_CIFCR_CBRTIF		BIT(2)
#घोषणा STM32_MDMA_CIFCR_CCTCIF		BIT(1)
#घोषणा STM32_MDMA_CIFCR_CTEIF		BIT(0)
#घोषणा STM32_MDMA_CIFCR_CLEAR_ALL	(STM32_MDMA_CIFCR_CLTCIF \
					| STM32_MDMA_CIFCR_CBTIF \
					| STM32_MDMA_CIFCR_CBRTIF \
					| STM32_MDMA_CIFCR_CCTCIF \
					| STM32_MDMA_CIFCR_CTEIF)

/* MDMA Channel x error status रेजिस्टर */
#घोषणा STM32_MDMA_CESR(x)		(0x48 + 0x40 * (x))
#घोषणा STM32_MDMA_CESR_BSE		BIT(11)
#घोषणा STM32_MDMA_CESR_ASR		BIT(10)
#घोषणा STM32_MDMA_CESR_TEMD		BIT(9)
#घोषणा STM32_MDMA_CESR_TELD		BIT(8)
#घोषणा STM32_MDMA_CESR_TED		BIT(7)
#घोषणा STM32_MDMA_CESR_TEA_MASK	GENMASK(6, 0)

/* MDMA Channel x control रेजिस्टर */
#घोषणा STM32_MDMA_CCR(x)		(0x4C + 0x40 * (x))
#घोषणा STM32_MDMA_CCR_SWRQ		BIT(16)
#घोषणा STM32_MDMA_CCR_WEX		BIT(14)
#घोषणा STM32_MDMA_CCR_HEX		BIT(13)
#घोषणा STM32_MDMA_CCR_BEX		BIT(12)
#घोषणा STM32_MDMA_CCR_PL_MASK		GENMASK(7, 6)
#घोषणा STM32_MDMA_CCR_PL(n)		STM32_MDMA_SET(n, \
						       STM32_MDMA_CCR_PL_MASK)
#घोषणा STM32_MDMA_CCR_TCIE		BIT(5)
#घोषणा STM32_MDMA_CCR_BTIE		BIT(4)
#घोषणा STM32_MDMA_CCR_BRTIE		BIT(3)
#घोषणा STM32_MDMA_CCR_CTCIE		BIT(2)
#घोषणा STM32_MDMA_CCR_TEIE		BIT(1)
#घोषणा STM32_MDMA_CCR_EN		BIT(0)
#घोषणा STM32_MDMA_CCR_IRQ_MASK		(STM32_MDMA_CCR_TCIE \
					| STM32_MDMA_CCR_BTIE \
					| STM32_MDMA_CCR_BRTIE \
					| STM32_MDMA_CCR_CTCIE \
					| STM32_MDMA_CCR_TEIE)

/* MDMA Channel x transfer configuration रेजिस्टर */
#घोषणा STM32_MDMA_CTCR(x)		(0x50 + 0x40 * (x))
#घोषणा STM32_MDMA_CTCR_BWM		BIT(31)
#घोषणा STM32_MDMA_CTCR_SWRM		BIT(30)
#घोषणा STM32_MDMA_CTCR_TRGM_MSK	GENMASK(29, 28)
#घोषणा STM32_MDMA_CTCR_TRGM(n)		STM32_MDMA_SET((n), \
						       STM32_MDMA_CTCR_TRGM_MSK)
#घोषणा STM32_MDMA_CTCR_TRGM_GET(n)	STM32_MDMA_GET((n), \
						       STM32_MDMA_CTCR_TRGM_MSK)
#घोषणा STM32_MDMA_CTCR_PAM_MASK	GENMASK(27, 26)
#घोषणा STM32_MDMA_CTCR_PAM(n)		STM32_MDMA_SET(n, \
						       STM32_MDMA_CTCR_PAM_MASK)
#घोषणा STM32_MDMA_CTCR_PKE		BIT(25)
#घोषणा STM32_MDMA_CTCR_TLEN_MSK	GENMASK(24, 18)
#घोषणा STM32_MDMA_CTCR_TLEN(n)		STM32_MDMA_SET((n), \
						       STM32_MDMA_CTCR_TLEN_MSK)
#घोषणा STM32_MDMA_CTCR_TLEN_GET(n)	STM32_MDMA_GET((n), \
						       STM32_MDMA_CTCR_TLEN_MSK)
#घोषणा STM32_MDMA_CTCR_LEN2_MSK	GENMASK(25, 18)
#घोषणा STM32_MDMA_CTCR_LEN2(n)		STM32_MDMA_SET((n), \
						       STM32_MDMA_CTCR_LEN2_MSK)
#घोषणा STM32_MDMA_CTCR_LEN2_GET(n)	STM32_MDMA_GET((n), \
						       STM32_MDMA_CTCR_LEN2_MSK)
#घोषणा STM32_MDMA_CTCR_DBURST_MASK	GENMASK(17, 15)
#घोषणा STM32_MDMA_CTCR_DBURST(n)	STM32_MDMA_SET(n, \
						    STM32_MDMA_CTCR_DBURST_MASK)
#घोषणा STM32_MDMA_CTCR_SBURST_MASK	GENMASK(14, 12)
#घोषणा STM32_MDMA_CTCR_SBURST(n)	STM32_MDMA_SET(n, \
						    STM32_MDMA_CTCR_SBURST_MASK)
#घोषणा STM32_MDMA_CTCR_DINCOS_MASK	GENMASK(11, 10)
#घोषणा STM32_MDMA_CTCR_DINCOS(n)	STM32_MDMA_SET((n), \
						    STM32_MDMA_CTCR_DINCOS_MASK)
#घोषणा STM32_MDMA_CTCR_SINCOS_MASK	GENMASK(9, 8)
#घोषणा STM32_MDMA_CTCR_SINCOS(n)	STM32_MDMA_SET((n), \
						    STM32_MDMA_CTCR_SINCOS_MASK)
#घोषणा STM32_MDMA_CTCR_DSIZE_MASK	GENMASK(7, 6)
#घोषणा STM32_MDMA_CTCR_DSIZE(n)	STM32_MDMA_SET(n, \
						     STM32_MDMA_CTCR_DSIZE_MASK)
#घोषणा STM32_MDMA_CTCR_SSIZE_MASK	GENMASK(5, 4)
#घोषणा STM32_MDMA_CTCR_SSIZE(n)	STM32_MDMA_SET(n, \
						     STM32_MDMA_CTCR_SSIZE_MASK)
#घोषणा STM32_MDMA_CTCR_DINC_MASK	GENMASK(3, 2)
#घोषणा STM32_MDMA_CTCR_DINC(n)		STM32_MDMA_SET((n), \
						      STM32_MDMA_CTCR_DINC_MASK)
#घोषणा STM32_MDMA_CTCR_SINC_MASK	GENMASK(1, 0)
#घोषणा STM32_MDMA_CTCR_SINC(n)		STM32_MDMA_SET((n), \
						      STM32_MDMA_CTCR_SINC_MASK)
#घोषणा STM32_MDMA_CTCR_CFG_MASK	(STM32_MDMA_CTCR_SINC_MASK \
					| STM32_MDMA_CTCR_DINC_MASK \
					| STM32_MDMA_CTCR_SINCOS_MASK \
					| STM32_MDMA_CTCR_DINCOS_MASK \
					| STM32_MDMA_CTCR_LEN2_MSK \
					| STM32_MDMA_CTCR_TRGM_MSK)

/* MDMA Channel x block number of data रेजिस्टर */
#घोषणा STM32_MDMA_CBNDTR(x)		(0x54 + 0x40 * (x))
#घोषणा STM32_MDMA_CBNDTR_BRC_MK	GENMASK(31, 20)
#घोषणा STM32_MDMA_CBNDTR_BRC(n)	STM32_MDMA_SET(n, \
						       STM32_MDMA_CBNDTR_BRC_MK)
#घोषणा STM32_MDMA_CBNDTR_BRC_GET(n)	STM32_MDMA_GET((n), \
						       STM32_MDMA_CBNDTR_BRC_MK)

#घोषणा STM32_MDMA_CBNDTR_BRDUM		BIT(19)
#घोषणा STM32_MDMA_CBNDTR_BRSUM		BIT(18)
#घोषणा STM32_MDMA_CBNDTR_BNDT_MASK	GENMASK(16, 0)
#घोषणा STM32_MDMA_CBNDTR_BNDT(n)	STM32_MDMA_SET(n, \
						    STM32_MDMA_CBNDTR_BNDT_MASK)

/* MDMA Channel x source address रेजिस्टर */
#घोषणा STM32_MDMA_CSAR(x)		(0x58 + 0x40 * (x))

/* MDMA Channel x destination address रेजिस्टर */
#घोषणा STM32_MDMA_CDAR(x)		(0x5C + 0x40 * (x))

/* MDMA Channel x block repeat address update रेजिस्टर */
#घोषणा STM32_MDMA_CBRUR(x)		(0x60 + 0x40 * (x))
#घोषणा STM32_MDMA_CBRUR_DUV_MASK	GENMASK(31, 16)
#घोषणा STM32_MDMA_CBRUR_DUV(n)		STM32_MDMA_SET(n, \
						      STM32_MDMA_CBRUR_DUV_MASK)
#घोषणा STM32_MDMA_CBRUR_SUV_MASK	GENMASK(15, 0)
#घोषणा STM32_MDMA_CBRUR_SUV(n)		STM32_MDMA_SET(n, \
						      STM32_MDMA_CBRUR_SUV_MASK)

/* MDMA Channel x link address रेजिस्टर */
#घोषणा STM32_MDMA_CLAR(x)		(0x64 + 0x40 * (x))

/* MDMA Channel x trigger and bus selection रेजिस्टर */
#घोषणा STM32_MDMA_CTBR(x)		(0x68 + 0x40 * (x))
#घोषणा STM32_MDMA_CTBR_DBUS		BIT(17)
#घोषणा STM32_MDMA_CTBR_SBUS		BIT(16)
#घोषणा STM32_MDMA_CTBR_TSEL_MASK	GENMASK(7, 0)
#घोषणा STM32_MDMA_CTBR_TSEL(n)		STM32_MDMA_SET(n, \
						      STM32_MDMA_CTBR_TSEL_MASK)

/* MDMA Channel x mask address रेजिस्टर */
#घोषणा STM32_MDMA_CMAR(x)		(0x70 + 0x40 * (x))

/* MDMA Channel x mask data रेजिस्टर */
#घोषणा STM32_MDMA_CMDR(x)		(0x74 + 0x40 * (x))

#घोषणा STM32_MDMA_MAX_BUF_LEN		128
#घोषणा STM32_MDMA_MAX_BLOCK_LEN	65536
#घोषणा STM32_MDMA_MAX_CHANNELS		63
#घोषणा STM32_MDMA_MAX_REQUESTS		256
#घोषणा STM32_MDMA_MAX_BURST		128
#घोषणा STM32_MDMA_VERY_HIGH_PRIORITY	0x3

क्रमागत sपंचांग32_mdma_trigger_mode अणु
	STM32_MDMA_BUFFER,
	STM32_MDMA_BLOCK,
	STM32_MDMA_BLOCK_REP,
	STM32_MDMA_LINKED_LIST,
पूर्ण;

क्रमागत sपंचांग32_mdma_width अणु
	STM32_MDMA_BYTE,
	STM32_MDMA_HALF_WORD,
	STM32_MDMA_WORD,
	STM32_MDMA_DOUBLE_WORD,
पूर्ण;

क्रमागत sपंचांग32_mdma_inc_mode अणु
	STM32_MDMA_FIXED = 0,
	STM32_MDMA_INC = 2,
	STM32_MDMA_DEC = 3,
पूर्ण;

काष्ठा sपंचांग32_mdma_chan_config अणु
	u32 request;
	u32 priority_level;
	u32 transfer_config;
	u32 mask_addr;
	u32 mask_data;
पूर्ण;

काष्ठा sपंचांग32_mdma_hwdesc अणु
	u32 ctcr;
	u32 cbndtr;
	u32 csar;
	u32 cdar;
	u32 cbrur;
	u32 clar;
	u32 ctbr;
	u32 dummy;
	u32 cmar;
	u32 cmdr;
पूर्ण __aligned(64);

काष्ठा sपंचांग32_mdma_desc_node अणु
	काष्ठा sपंचांग32_mdma_hwdesc *hwdesc;
	dma_addr_t hwdesc_phys;
पूर्ण;

काष्ठा sपंचांग32_mdma_desc अणु
	काष्ठा virt_dma_desc vdesc;
	u32 ccr;
	bool cyclic;
	u32 count;
	काष्ठा sपंचांग32_mdma_desc_node node[];
पूर्ण;

काष्ठा sपंचांग32_mdma_chan अणु
	काष्ठा virt_dma_chan vchan;
	काष्ठा dma_pool *desc_pool;
	u32 id;
	काष्ठा sपंचांग32_mdma_desc *desc;
	u32 curr_hwdesc;
	काष्ठा dma_slave_config dma_config;
	काष्ठा sपंचांग32_mdma_chan_config chan_config;
	bool busy;
	u32 mem_burst;
	u32 mem_width;
पूर्ण;

काष्ठा sपंचांग32_mdma_device अणु
	काष्ठा dma_device ddev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	पूर्णांक irq;
	u32 nr_channels;
	u32 nr_requests;
	u32 nr_ahb_addr_masks;
	काष्ठा sपंचांग32_mdma_chan chan[STM32_MDMA_MAX_CHANNELS];
	u32 ahb_addr_masks[];
पूर्ण;

अटल काष्ठा sपंचांग32_mdma_device *sपंचांग32_mdma_get_dev(
	काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	वापस container_of(chan->vchan.chan.device, काष्ठा sपंचांग32_mdma_device,
			    ddev);
पूर्ण

अटल काष्ठा sपंचांग32_mdma_chan *to_sपंचांग32_mdma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा sपंचांग32_mdma_chan, vchan.chan);
पूर्ण

अटल काष्ठा sपंचांग32_mdma_desc *to_sपंचांग32_mdma_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा sपंचांग32_mdma_desc, vdesc);
पूर्ण

अटल काष्ठा device *chan2dev(काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	वापस &chan->vchan.chan.dev->device;
पूर्ण

अटल काष्ठा device *mdma2dev(काष्ठा sपंचांग32_mdma_device *mdma_dev)
अणु
	वापस mdma_dev->ddev.dev;
पूर्ण

अटल u32 sपंचांग32_mdma_पढ़ो(काष्ठा sपंचांग32_mdma_device *dmadev, u32 reg)
अणु
	वापस पढ़ोl_relaxed(dmadev->base + reg);
पूर्ण

अटल व्योम sपंचांग32_mdma_ग_लिखो(काष्ठा sपंचांग32_mdma_device *dmadev, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, dmadev->base + reg);
पूर्ण

अटल व्योम sपंचांग32_mdma_set_bits(काष्ठा sपंचांग32_mdma_device *dmadev, u32 reg,
				u32 mask)
अणु
	व्योम __iomem *addr = dmadev->base + reg;

	ग_लिखोl_relaxed(पढ़ोl_relaxed(addr) | mask, addr);
पूर्ण

अटल व्योम sपंचांग32_mdma_clr_bits(काष्ठा sपंचांग32_mdma_device *dmadev, u32 reg,
				u32 mask)
अणु
	व्योम __iomem *addr = dmadev->base + reg;

	ग_लिखोl_relaxed(पढ़ोl_relaxed(addr) & ~mask, addr);
पूर्ण

अटल काष्ठा sपंचांग32_mdma_desc *sपंचांग32_mdma_alloc_desc(
		काष्ठा sपंचांग32_mdma_chan *chan, u32 count)
अणु
	काष्ठा sपंचांग32_mdma_desc *desc;
	पूर्णांक i;

	desc = kzalloc(काष्ठा_size(desc, node, count), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	क्रम (i = 0; i < count; i++) अणु
		desc->node[i].hwdesc =
			dma_pool_alloc(chan->desc_pool, GFP_NOWAIT,
				       &desc->node[i].hwdesc_phys);
		अगर (!desc->node[i].hwdesc)
			जाओ err;
	पूर्ण

	desc->count = count;

	वापस desc;

err:
	dev_err(chan2dev(chan), "Failed to allocate descriptor\n");
	जबतक (--i >= 0)
		dma_pool_मुक्त(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल व्योम sपंचांग32_mdma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा sपंचांग32_mdma_desc *desc = to_sपंचांग32_mdma_desc(vdesc);
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(vdesc->tx.chan);
	पूर्णांक i;

	क्रम (i = 0; i < desc->count; i++)
		dma_pool_मुक्त(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kमुक्त(desc);
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_get_width(काष्ठा sपंचांग32_mdma_chan *chan,
				क्रमागत dma_slave_buswidth width)
अणु
	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		वापस ffs(width) - 1;
	शेष:
		dev_err(chan2dev(chan), "Dma bus width %i not supported\n",
			width);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल क्रमागत dma_slave_buswidth sपंचांग32_mdma_get_max_width(dma_addr_t addr,
							u32 buf_len, u32 tlen)
अणु
	क्रमागत dma_slave_buswidth max_width = DMA_SLAVE_BUSWIDTH_8_BYTES;

	क्रम (max_width = DMA_SLAVE_BUSWIDTH_8_BYTES;
	     max_width > DMA_SLAVE_BUSWIDTH_1_BYTE;
	     max_width >>= 1) अणु
		/*
		 * Address and buffer length both have to be aligned on
		 * bus width
		 */
		अगर ((((buf_len | addr) & (max_width - 1)) == 0) &&
		    tlen >= max_width)
			अवरोध;
	पूर्ण

	वापस max_width;
पूर्ण

अटल u32 sपंचांग32_mdma_get_best_burst(u32 buf_len, u32 tlen, u32 max_burst,
				     क्रमागत dma_slave_buswidth width)
अणु
	u32 best_burst;

	best_burst = min((u32)1 << __ffs(tlen | buf_len),
			 max_burst * width) / width;

	वापस (best_burst > 0) ? best_burst : 1;
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_disable_chan(काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	u32 ccr, cisr, id, reg;
	पूर्णांक ret;

	id = chan->id;
	reg = STM32_MDMA_CCR(id);

	/* Disable पूर्णांकerrupts */
	sपंचांग32_mdma_clr_bits(dmadev, reg, STM32_MDMA_CCR_IRQ_MASK);

	ccr = sपंचांग32_mdma_पढ़ो(dmadev, reg);
	अगर (ccr & STM32_MDMA_CCR_EN) अणु
		sपंचांग32_mdma_clr_bits(dmadev, reg, STM32_MDMA_CCR_EN);

		/* Ensure that any ongoing transfer has been completed */
		ret = पढ़ोl_relaxed_poll_समयout_atomic(
				dmadev->base + STM32_MDMA_CISR(id), cisr,
				(cisr & STM32_MDMA_CISR_CTCIF), 10, 1000);
		अगर (ret) अणु
			dev_err(chan2dev(chan), "%s: timeout!\n", __func__);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_mdma_stop(काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	u32 status;
	पूर्णांक ret;

	/* Disable DMA */
	ret = sपंचांग32_mdma_disable_chan(chan);
	अगर (ret < 0)
		वापस;

	/* Clear पूर्णांकerrupt status अगर it is there */
	status = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CISR(chan->id));
	अगर (status) अणु
		dev_dbg(chan2dev(chan), "%s(): clearing interrupt: 0x%08x\n",
			__func__, status);
		sपंचांग32_mdma_set_bits(dmadev, STM32_MDMA_CIFCR(chan->id), status);
	पूर्ण

	chan->busy = false;
पूर्ण

अटल व्योम sपंचांग32_mdma_set_bus(काष्ठा sपंचांग32_mdma_device *dmadev, u32 *ctbr,
			       u32 ctbr_mask, u32 src_addr)
अणु
	u32 mask;
	पूर्णांक i;

	/* Check अगर memory device is on AHB or AXI */
	*ctbr &= ~ctbr_mask;
	mask = src_addr & 0xF0000000;
	क्रम (i = 0; i < dmadev->nr_ahb_addr_masks; i++) अणु
		अगर (mask == dmadev->ahb_addr_masks[i]) अणु
			*ctbr |= ctbr_mask;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_set_xfer_param(काष्ठा sपंचांग32_mdma_chan *chan,
				     क्रमागत dma_transfer_direction direction,
				     u32 *mdma_ccr, u32 *mdma_ctcr,
				     u32 *mdma_ctbr, dma_addr_t addr,
				     u32 buf_len)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	काष्ठा sपंचांग32_mdma_chan_config *chan_config = &chan->chan_config;
	क्रमागत dma_slave_buswidth src_addr_width, dst_addr_width;
	phys_addr_t src_addr, dst_addr;
	पूर्णांक src_bus_width, dst_bus_width;
	u32 src_maxburst, dst_maxburst, src_best_burst, dst_best_burst;
	u32 ccr, ctcr, ctbr, tlen;

	src_addr_width = chan->dma_config.src_addr_width;
	dst_addr_width = chan->dma_config.dst_addr_width;
	src_maxburst = chan->dma_config.src_maxburst;
	dst_maxburst = chan->dma_config.dst_maxburst;

	ccr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CCR(chan->id));
	ctcr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CTCR(chan->id));
	ctbr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CTBR(chan->id));

	/* Enable HW request mode */
	ctcr &= ~STM32_MDMA_CTCR_SWRM;

	/* Set DINC, SINC, DINCOS, SINCOS, TRGM and TLEN retrieve from DT */
	ctcr &= ~STM32_MDMA_CTCR_CFG_MASK;
	ctcr |= chan_config->transfer_config & STM32_MDMA_CTCR_CFG_MASK;

	/*
	 * For buffer transfer length (TLEN) we have to set
	 * the number of bytes - 1 in CTCR रेजिस्टर
	 */
	tlen = STM32_MDMA_CTCR_LEN2_GET(ctcr);
	ctcr &= ~STM32_MDMA_CTCR_LEN2_MSK;
	ctcr |= STM32_MDMA_CTCR_TLEN((tlen - 1));

	/* Disable Pack Enable */
	ctcr &= ~STM32_MDMA_CTCR_PKE;

	/* Check burst size स्थिरraपूर्णांकs */
	अगर (src_maxburst * src_addr_width > STM32_MDMA_MAX_BURST ||
	    dst_maxburst * dst_addr_width > STM32_MDMA_MAX_BURST) अणु
		dev_err(chan2dev(chan),
			"burst size * bus width higher than %d bytes\n",
			STM32_MDMA_MAX_BURST);
		वापस -EINVAL;
	पूर्ण

	अगर ((!is_घातer_of_2(src_maxburst) && src_maxburst > 0) ||
	    (!is_घातer_of_2(dst_maxburst) && dst_maxburst > 0)) अणु
		dev_err(chan2dev(chan), "burst size must be a power of 2\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Configure channel control:
	 * - Clear SW request as in this हाल this is a HW one
	 * - Clear WEX, HEX and BEX bits
	 * - Set priority level
	 */
	ccr &= ~(STM32_MDMA_CCR_SWRQ | STM32_MDMA_CCR_WEX | STM32_MDMA_CCR_HEX |
		 STM32_MDMA_CCR_BEX | STM32_MDMA_CCR_PL_MASK);
	ccr |= STM32_MDMA_CCR_PL(chan_config->priority_level);

	/* Configure Trigger selection */
	ctbr &= ~STM32_MDMA_CTBR_TSEL_MASK;
	ctbr |= STM32_MDMA_CTBR_TSEL(chan_config->request);

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		dst_addr = chan->dma_config.dst_addr;

		/* Set device data size */
		dst_bus_width = sपंचांग32_mdma_get_width(chan, dst_addr_width);
		अगर (dst_bus_width < 0)
			वापस dst_bus_width;
		ctcr &= ~STM32_MDMA_CTCR_DSIZE_MASK;
		ctcr |= STM32_MDMA_CTCR_DSIZE(dst_bus_width);

		/* Set device burst value */
		dst_best_burst = sपंचांग32_mdma_get_best_burst(buf_len, tlen,
							   dst_maxburst,
							   dst_addr_width);
		chan->mem_burst = dst_best_burst;
		ctcr &= ~STM32_MDMA_CTCR_DBURST_MASK;
		ctcr |= STM32_MDMA_CTCR_DBURST((ilog2(dst_best_burst)));

		/* Set memory data size */
		src_addr_width = sपंचांग32_mdma_get_max_width(addr, buf_len, tlen);
		chan->mem_width = src_addr_width;
		src_bus_width = sपंचांग32_mdma_get_width(chan, src_addr_width);
		अगर (src_bus_width < 0)
			वापस src_bus_width;
		ctcr &= ~STM32_MDMA_CTCR_SSIZE_MASK |
			STM32_MDMA_CTCR_SINCOS_MASK;
		ctcr |= STM32_MDMA_CTCR_SSIZE(src_bus_width) |
			STM32_MDMA_CTCR_SINCOS(src_bus_width);

		/* Set memory burst value */
		src_maxburst = STM32_MDMA_MAX_BUF_LEN / src_addr_width;
		src_best_burst = sपंचांग32_mdma_get_best_burst(buf_len, tlen,
							   src_maxburst,
							   src_addr_width);
		chan->mem_burst = src_best_burst;
		ctcr &= ~STM32_MDMA_CTCR_SBURST_MASK;
		ctcr |= STM32_MDMA_CTCR_SBURST((ilog2(src_best_burst)));

		/* Select bus */
		sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_DBUS,
				   dst_addr);

		अगर (dst_bus_width != src_bus_width)
			ctcr |= STM32_MDMA_CTCR_PKE;

		/* Set destination address */
		sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CDAR(chan->id), dst_addr);
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		src_addr = chan->dma_config.src_addr;

		/* Set device data size */
		src_bus_width = sपंचांग32_mdma_get_width(chan, src_addr_width);
		अगर (src_bus_width < 0)
			वापस src_bus_width;
		ctcr &= ~STM32_MDMA_CTCR_SSIZE_MASK;
		ctcr |= STM32_MDMA_CTCR_SSIZE(src_bus_width);

		/* Set device burst value */
		src_best_burst = sपंचांग32_mdma_get_best_burst(buf_len, tlen,
							   src_maxburst,
							   src_addr_width);
		ctcr &= ~STM32_MDMA_CTCR_SBURST_MASK;
		ctcr |= STM32_MDMA_CTCR_SBURST((ilog2(src_best_burst)));

		/* Set memory data size */
		dst_addr_width = sपंचांग32_mdma_get_max_width(addr, buf_len, tlen);
		chan->mem_width = dst_addr_width;
		dst_bus_width = sपंचांग32_mdma_get_width(chan, dst_addr_width);
		अगर (dst_bus_width < 0)
			वापस dst_bus_width;
		ctcr &= ~(STM32_MDMA_CTCR_DSIZE_MASK |
			STM32_MDMA_CTCR_DINCOS_MASK);
		ctcr |= STM32_MDMA_CTCR_DSIZE(dst_bus_width) |
			STM32_MDMA_CTCR_DINCOS(dst_bus_width);

		/* Set memory burst value */
		dst_maxburst = STM32_MDMA_MAX_BUF_LEN / dst_addr_width;
		dst_best_burst = sपंचांग32_mdma_get_best_burst(buf_len, tlen,
							   dst_maxburst,
							   dst_addr_width);
		ctcr &= ~STM32_MDMA_CTCR_DBURST_MASK;
		ctcr |= STM32_MDMA_CTCR_DBURST((ilog2(dst_best_burst)));

		/* Select bus */
		sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_SBUS,
				   src_addr);

		अगर (dst_bus_width != src_bus_width)
			ctcr |= STM32_MDMA_CTCR_PKE;

		/* Set source address */
		sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CSAR(chan->id), src_addr);
		अवरोध;

	शेष:
		dev_err(chan2dev(chan), "Dma direction is not supported\n");
		वापस -EINVAL;
	पूर्ण

	*mdma_ccr = ccr;
	*mdma_ctcr = ctcr;
	*mdma_ctbr = ctbr;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_mdma_dump_hwdesc(काष्ठा sपंचांग32_mdma_chan *chan,
				   काष्ठा sपंचांग32_mdma_desc_node *node)
अणु
	dev_dbg(chan2dev(chan), "hwdesc:  %pad\n", &node->hwdesc_phys);
	dev_dbg(chan2dev(chan), "CTCR:    0x%08x\n", node->hwdesc->ctcr);
	dev_dbg(chan2dev(chan), "CBNDTR:  0x%08x\n", node->hwdesc->cbndtr);
	dev_dbg(chan2dev(chan), "CSAR:    0x%08x\n", node->hwdesc->csar);
	dev_dbg(chan2dev(chan), "CDAR:    0x%08x\n", node->hwdesc->cdar);
	dev_dbg(chan2dev(chan), "CBRUR:   0x%08x\n", node->hwdesc->cbrur);
	dev_dbg(chan2dev(chan), "CLAR:    0x%08x\n", node->hwdesc->clar);
	dev_dbg(chan2dev(chan), "CTBR:    0x%08x\n", node->hwdesc->ctbr);
	dev_dbg(chan2dev(chan), "CMAR:    0x%08x\n", node->hwdesc->cmar);
	dev_dbg(chan2dev(chan), "CMDR:    0x%08x\n\n", node->hwdesc->cmdr);
पूर्ण

अटल व्योम sपंचांग32_mdma_setup_hwdesc(काष्ठा sपंचांग32_mdma_chan *chan,
				    काष्ठा sपंचांग32_mdma_desc *desc,
				    क्रमागत dma_transfer_direction dir, u32 count,
				    dma_addr_t src_addr, dma_addr_t dst_addr,
				    u32 len, u32 ctcr, u32 ctbr, bool is_last,
				    bool is_first, bool is_cyclic)
अणु
	काष्ठा sपंचांग32_mdma_chan_config *config = &chan->chan_config;
	काष्ठा sपंचांग32_mdma_hwdesc *hwdesc;
	u32 next = count + 1;

	hwdesc = desc->node[count].hwdesc;
	hwdesc->ctcr = ctcr;
	hwdesc->cbndtr &= ~(STM32_MDMA_CBNDTR_BRC_MK |
			STM32_MDMA_CBNDTR_BRDUM |
			STM32_MDMA_CBNDTR_BRSUM |
			STM32_MDMA_CBNDTR_BNDT_MASK);
	hwdesc->cbndtr |= STM32_MDMA_CBNDTR_BNDT(len);
	hwdesc->csar = src_addr;
	hwdesc->cdar = dst_addr;
	hwdesc->cbrur = 0;
	hwdesc->ctbr = ctbr;
	hwdesc->cmar = config->mask_addr;
	hwdesc->cmdr = config->mask_data;

	अगर (is_last) अणु
		अगर (is_cyclic)
			hwdesc->clar = desc->node[0].hwdesc_phys;
		अन्यथा
			hwdesc->clar = 0;
	पूर्ण अन्यथा अणु
		hwdesc->clar = desc->node[next].hwdesc_phys;
	पूर्ण

	sपंचांग32_mdma_dump_hwdesc(chan, &desc->node[count]);
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_setup_xfer(काष्ठा sपंचांग32_mdma_chan *chan,
				 काष्ठा sपंचांग32_mdma_desc *desc,
				 काष्ठा scatterlist *sgl, u32 sg_len,
				 क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	काष्ठा dma_slave_config *dma_config = &chan->dma_config;
	काष्ठा scatterlist *sg;
	dma_addr_t src_addr, dst_addr;
	u32 ccr, ctcr, ctbr;
	पूर्णांक i, ret = 0;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		अगर (sg_dma_len(sg) > STM32_MDMA_MAX_BLOCK_LEN) अणु
			dev_err(chan2dev(chan), "Invalid block len\n");
			वापस -EINVAL;
		पूर्ण

		अगर (direction == DMA_MEM_TO_DEV) अणु
			src_addr = sg_dma_address(sg);
			dst_addr = dma_config->dst_addr;
			ret = sपंचांग32_mdma_set_xfer_param(chan, direction, &ccr,
							&ctcr, &ctbr, src_addr,
							sg_dma_len(sg));
			sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_SBUS,
					   src_addr);
		पूर्ण अन्यथा अणु
			src_addr = dma_config->src_addr;
			dst_addr = sg_dma_address(sg);
			ret = sपंचांग32_mdma_set_xfer_param(chan, direction, &ccr,
							&ctcr, &ctbr, dst_addr,
							sg_dma_len(sg));
			sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_DBUS,
					   dst_addr);
		पूर्ण

		अगर (ret < 0)
			वापस ret;

		sपंचांग32_mdma_setup_hwdesc(chan, desc, direction, i, src_addr,
					dst_addr, sg_dma_len(sg), ctcr, ctbr,
					i == sg_len - 1, i == 0, false);
	पूर्ण

	/* Enable पूर्णांकerrupts */
	ccr &= ~STM32_MDMA_CCR_IRQ_MASK;
	ccr |= STM32_MDMA_CCR_TEIE | STM32_MDMA_CCR_CTCIE;
	अगर (sg_len > 1)
		ccr |= STM32_MDMA_CCR_BTIE;
	desc->ccr = ccr;

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sपंचांग32_mdma_prep_slave_sg(काष्ठा dma_chan *c, काष्ठा scatterlist *sgl,
			 u32 sg_len, क्रमागत dma_transfer_direction direction,
			 अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा sपंचांग32_mdma_desc *desc;
	पूर्णांक i, ret;

	/*
	 * Once DMA is in setup cyclic mode the channel we cannot assign this
	 * channel anymore. The DMA channel needs to be पातed or terminated
	 * क्रम allowing another request.
	 */
	अगर (chan->desc && chan->desc->cyclic) अणु
		dev_err(chan2dev(chan),
			"Request not allowed when dma in cyclic mode\n");
		वापस शून्य;
	पूर्ण

	desc = sपंचांग32_mdma_alloc_desc(chan, sg_len);
	अगर (!desc)
		वापस शून्य;

	ret = sपंचांग32_mdma_setup_xfer(chan, desc, sgl, sg_len, direction);
	अगर (ret < 0)
		जाओ xfer_setup_err;

	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

xfer_setup_err:
	क्रम (i = 0; i < desc->count; i++)
		dma_pool_मुक्त(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sपंचांग32_mdma_prep_dma_cyclic(काष्ठा dma_chan *c, dma_addr_t buf_addr,
			   माप_प्रकार buf_len, माप_प्रकार period_len,
			   क्रमागत dma_transfer_direction direction,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	काष्ठा dma_slave_config *dma_config = &chan->dma_config;
	काष्ठा sपंचांग32_mdma_desc *desc;
	dma_addr_t src_addr, dst_addr;
	u32 ccr, ctcr, ctbr, count;
	पूर्णांक i, ret;

	/*
	 * Once DMA is in setup cyclic mode the channel we cannot assign this
	 * channel anymore. The DMA channel needs to be पातed or terminated
	 * क्रम allowing another request.
	 */
	अगर (chan->desc && chan->desc->cyclic) अणु
		dev_err(chan2dev(chan),
			"Request not allowed when dma in cyclic mode\n");
		वापस शून्य;
	पूर्ण

	अगर (!buf_len || !period_len || period_len > STM32_MDMA_MAX_BLOCK_LEN) अणु
		dev_err(chan2dev(chan), "Invalid buffer/period len\n");
		वापस शून्य;
	पूर्ण

	अगर (buf_len % period_len) अणु
		dev_err(chan2dev(chan), "buf_len not multiple of period_len\n");
		वापस शून्य;
	पूर्ण

	count = buf_len / period_len;

	desc = sपंचांग32_mdma_alloc_desc(chan, count);
	अगर (!desc)
		वापस शून्य;

	/* Select bus */
	अगर (direction == DMA_MEM_TO_DEV) अणु
		src_addr = buf_addr;
		ret = sपंचांग32_mdma_set_xfer_param(chan, direction, &ccr, &ctcr,
						&ctbr, src_addr, period_len);
		sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_SBUS,
				   src_addr);
	पूर्ण अन्यथा अणु
		dst_addr = buf_addr;
		ret = sपंचांग32_mdma_set_xfer_param(chan, direction, &ccr, &ctcr,
						&ctbr, dst_addr, period_len);
		sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_DBUS,
				   dst_addr);
	पूर्ण

	अगर (ret < 0)
		जाओ xfer_setup_err;

	/* Enable पूर्णांकerrupts */
	ccr &= ~STM32_MDMA_CCR_IRQ_MASK;
	ccr |= STM32_MDMA_CCR_TEIE | STM32_MDMA_CCR_CTCIE | STM32_MDMA_CCR_BTIE;
	desc->ccr = ccr;

	/* Configure hwdesc list */
	क्रम (i = 0; i < count; i++) अणु
		अगर (direction == DMA_MEM_TO_DEV) अणु
			src_addr = buf_addr + i * period_len;
			dst_addr = dma_config->dst_addr;
		पूर्ण अन्यथा अणु
			src_addr = dma_config->src_addr;
			dst_addr = buf_addr + i * period_len;
		पूर्ण

		sपंचांग32_mdma_setup_hwdesc(chan, desc, direction, i, src_addr,
					dst_addr, period_len, ctcr, ctbr,
					i == count - 1, i == 0, true);
	पूर्ण

	desc->cyclic = true;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

xfer_setup_err:
	क्रम (i = 0; i < desc->count; i++)
		dma_pool_मुक्त(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sपंचांग32_mdma_prep_dma_स_नकल(काष्ठा dma_chan *c, dma_addr_t dest, dma_addr_t src,
			   माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	क्रमागत dma_slave_buswidth max_width;
	काष्ठा sपंचांग32_mdma_desc *desc;
	काष्ठा sपंचांग32_mdma_hwdesc *hwdesc;
	u32 ccr, ctcr, ctbr, cbndtr, count, max_burst, mdma_burst;
	u32 best_burst, tlen;
	माप_प्रकार xfer_count, offset;
	पूर्णांक src_bus_width, dst_bus_width;
	पूर्णांक i;

	/*
	 * Once DMA is in setup cyclic mode the channel we cannot assign this
	 * channel anymore. The DMA channel needs to be पातed or terminated
	 * to allow another request
	 */
	अगर (chan->desc && chan->desc->cyclic) अणु
		dev_err(chan2dev(chan),
			"Request not allowed when dma in cyclic mode\n");
		वापस शून्य;
	पूर्ण

	count = DIV_ROUND_UP(len, STM32_MDMA_MAX_BLOCK_LEN);
	desc = sपंचांग32_mdma_alloc_desc(chan, count);
	अगर (!desc)
		वापस शून्य;

	ccr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CCR(chan->id));
	ctcr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CTCR(chan->id));
	ctbr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CTBR(chan->id));
	cbndtr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CBNDTR(chan->id));

	/* Enable sw req, some पूर्णांकerrupts and clear other bits */
	ccr &= ~(STM32_MDMA_CCR_WEX | STM32_MDMA_CCR_HEX |
		 STM32_MDMA_CCR_BEX | STM32_MDMA_CCR_PL_MASK |
		 STM32_MDMA_CCR_IRQ_MASK);
	ccr |= STM32_MDMA_CCR_TEIE;

	/* Enable SW request mode, dest/src inc and clear other bits */
	ctcr &= ~(STM32_MDMA_CTCR_BWM | STM32_MDMA_CTCR_TRGM_MSK |
		  STM32_MDMA_CTCR_PAM_MASK | STM32_MDMA_CTCR_PKE |
		  STM32_MDMA_CTCR_TLEN_MSK | STM32_MDMA_CTCR_DBURST_MASK |
		  STM32_MDMA_CTCR_SBURST_MASK | STM32_MDMA_CTCR_DINCOS_MASK |
		  STM32_MDMA_CTCR_SINCOS_MASK | STM32_MDMA_CTCR_DSIZE_MASK |
		  STM32_MDMA_CTCR_SSIZE_MASK | STM32_MDMA_CTCR_DINC_MASK |
		  STM32_MDMA_CTCR_SINC_MASK);
	ctcr |= STM32_MDMA_CTCR_SWRM | STM32_MDMA_CTCR_SINC(STM32_MDMA_INC) |
		STM32_MDMA_CTCR_DINC(STM32_MDMA_INC);

	/* Reset HW request */
	ctbr &= ~STM32_MDMA_CTBR_TSEL_MASK;

	/* Select bus */
	sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_SBUS, src);
	sपंचांग32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_DBUS, dest);

	/* Clear CBNDTR रेजिस्टरs */
	cbndtr &= ~(STM32_MDMA_CBNDTR_BRC_MK | STM32_MDMA_CBNDTR_BRDUM |
			STM32_MDMA_CBNDTR_BRSUM | STM32_MDMA_CBNDTR_BNDT_MASK);

	अगर (len <= STM32_MDMA_MAX_BLOCK_LEN) अणु
		cbndtr |= STM32_MDMA_CBNDTR_BNDT(len);
		अगर (len <= STM32_MDMA_MAX_BUF_LEN) अणु
			/* Setup a buffer transfer */
			ccr |= STM32_MDMA_CCR_TCIE | STM32_MDMA_CCR_CTCIE;
			ctcr |= STM32_MDMA_CTCR_TRGM(STM32_MDMA_BUFFER);
		पूर्ण अन्यथा अणु
			/* Setup a block transfer */
			ccr |= STM32_MDMA_CCR_BTIE | STM32_MDMA_CCR_CTCIE;
			ctcr |= STM32_MDMA_CTCR_TRGM(STM32_MDMA_BLOCK);
		पूर्ण

		tlen = STM32_MDMA_MAX_BUF_LEN;
		ctcr |= STM32_MDMA_CTCR_TLEN((tlen - 1));

		/* Set source best burst size */
		max_width = sपंचांग32_mdma_get_max_width(src, len, tlen);
		src_bus_width = sपंचांग32_mdma_get_width(chan, max_width);

		max_burst = tlen / max_width;
		best_burst = sपंचांग32_mdma_get_best_burst(len, tlen, max_burst,
						       max_width);
		mdma_burst = ilog2(best_burst);

		ctcr |= STM32_MDMA_CTCR_SBURST(mdma_burst) |
			STM32_MDMA_CTCR_SSIZE(src_bus_width) |
			STM32_MDMA_CTCR_SINCOS(src_bus_width);

		/* Set destination best burst size */
		max_width = sपंचांग32_mdma_get_max_width(dest, len, tlen);
		dst_bus_width = sपंचांग32_mdma_get_width(chan, max_width);

		max_burst = tlen / max_width;
		best_burst = sपंचांग32_mdma_get_best_burst(len, tlen, max_burst,
						       max_width);
		mdma_burst = ilog2(best_burst);

		ctcr |= STM32_MDMA_CTCR_DBURST(mdma_burst) |
			STM32_MDMA_CTCR_DSIZE(dst_bus_width) |
			STM32_MDMA_CTCR_DINCOS(dst_bus_width);

		अगर (dst_bus_width != src_bus_width)
			ctcr |= STM32_MDMA_CTCR_PKE;

		/* Prepare hardware descriptor */
		hwdesc = desc->node[0].hwdesc;
		hwdesc->ctcr = ctcr;
		hwdesc->cbndtr = cbndtr;
		hwdesc->csar = src;
		hwdesc->cdar = dest;
		hwdesc->cbrur = 0;
		hwdesc->clar = 0;
		hwdesc->ctbr = ctbr;
		hwdesc->cmar = 0;
		hwdesc->cmdr = 0;

		sपंचांग32_mdma_dump_hwdesc(chan, &desc->node[0]);
	पूर्ण अन्यथा अणु
		/* Setup a LLI transfer */
		ctcr |= STM32_MDMA_CTCR_TRGM(STM32_MDMA_LINKED_LIST) |
			STM32_MDMA_CTCR_TLEN((STM32_MDMA_MAX_BUF_LEN - 1));
		ccr |= STM32_MDMA_CCR_BTIE | STM32_MDMA_CCR_CTCIE;
		tlen = STM32_MDMA_MAX_BUF_LEN;

		क्रम (i = 0, offset = 0; offset < len;
		     i++, offset += xfer_count) अणु
			xfer_count = min_t(माप_प्रकार, len - offset,
					   STM32_MDMA_MAX_BLOCK_LEN);

			/* Set source best burst size */
			max_width = sपंचांग32_mdma_get_max_width(src, len, tlen);
			src_bus_width = sपंचांग32_mdma_get_width(chan, max_width);

			max_burst = tlen / max_width;
			best_burst = sपंचांग32_mdma_get_best_burst(len, tlen,
							       max_burst,
							       max_width);
			mdma_burst = ilog2(best_burst);

			ctcr |= STM32_MDMA_CTCR_SBURST(mdma_burst) |
				STM32_MDMA_CTCR_SSIZE(src_bus_width) |
				STM32_MDMA_CTCR_SINCOS(src_bus_width);

			/* Set destination best burst size */
			max_width = sपंचांग32_mdma_get_max_width(dest, len, tlen);
			dst_bus_width = sपंचांग32_mdma_get_width(chan, max_width);

			max_burst = tlen / max_width;
			best_burst = sपंचांग32_mdma_get_best_burst(len, tlen,
							       max_burst,
							       max_width);
			mdma_burst = ilog2(best_burst);

			ctcr |= STM32_MDMA_CTCR_DBURST(mdma_burst) |
				STM32_MDMA_CTCR_DSIZE(dst_bus_width) |
				STM32_MDMA_CTCR_DINCOS(dst_bus_width);

			अगर (dst_bus_width != src_bus_width)
				ctcr |= STM32_MDMA_CTCR_PKE;

			/* Prepare hardware descriptor */
			sपंचांग32_mdma_setup_hwdesc(chan, desc, DMA_MEM_TO_MEM, i,
						src + offset, dest + offset,
						xfer_count, ctcr, ctbr,
						i == count - 1, i == 0, false);
		पूर्ण
	पूर्ण

	desc->ccr = ccr;

	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल व्योम sपंचांग32_mdma_dump_reg(काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);

	dev_dbg(chan2dev(chan), "CCR:     0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CCR(chan->id)));
	dev_dbg(chan2dev(chan), "CTCR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CTCR(chan->id)));
	dev_dbg(chan2dev(chan), "CBNDTR:  0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CBNDTR(chan->id)));
	dev_dbg(chan2dev(chan), "CSAR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CSAR(chan->id)));
	dev_dbg(chan2dev(chan), "CDAR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CDAR(chan->id)));
	dev_dbg(chan2dev(chan), "CBRUR:   0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CBRUR(chan->id)));
	dev_dbg(chan2dev(chan), "CLAR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CLAR(chan->id)));
	dev_dbg(chan2dev(chan), "CTBR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CTBR(chan->id)));
	dev_dbg(chan2dev(chan), "CMAR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CMAR(chan->id)));
	dev_dbg(chan2dev(chan), "CMDR:    0x%08x\n",
		sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CMDR(chan->id)));
पूर्ण

अटल व्योम sपंचांग32_mdma_start_transfer(काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	काष्ठा virt_dma_desc *vdesc;
	काष्ठा sपंचांग32_mdma_hwdesc *hwdesc;
	u32 id = chan->id;
	u32 status, reg;

	vdesc = vchan_next_desc(&chan->vchan);
	अगर (!vdesc) अणु
		chan->desc = शून्य;
		वापस;
	पूर्ण

	list_del(&vdesc->node);

	chan->desc = to_sपंचांग32_mdma_desc(vdesc);
	hwdesc = chan->desc->node[0].hwdesc;
	chan->curr_hwdesc = 0;

	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CCR(id), chan->desc->ccr);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CTCR(id), hwdesc->ctcr);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CBNDTR(id), hwdesc->cbndtr);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CSAR(id), hwdesc->csar);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CDAR(id), hwdesc->cdar);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CBRUR(id), hwdesc->cbrur);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CLAR(id), hwdesc->clar);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CTBR(id), hwdesc->ctbr);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CMAR(id), hwdesc->cmar);
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CMDR(id), hwdesc->cmdr);

	/* Clear पूर्णांकerrupt status अगर it is there */
	status = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CISR(id));
	अगर (status)
		sपंचांग32_mdma_set_bits(dmadev, STM32_MDMA_CIFCR(id), status);

	sपंचांग32_mdma_dump_reg(chan);

	/* Start DMA */
	sपंचांग32_mdma_set_bits(dmadev, STM32_MDMA_CCR(id), STM32_MDMA_CCR_EN);

	/* Set SW request in हाल of MEM2MEM transfer */
	अगर (hwdesc->ctcr & STM32_MDMA_CTCR_SWRM) अणु
		reg = STM32_MDMA_CCR(id);
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CCR_SWRQ);
	पूर्ण

	chan->busy = true;

	dev_dbg(chan2dev(chan), "vchan %pK: started\n", &chan->vchan);
पूर्ण

अटल व्योम sपंचांग32_mdma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	अगर (!vchan_issue_pending(&chan->vchan))
		जाओ end;

	dev_dbg(chan2dev(chan), "vchan %pK: issued\n", &chan->vchan);

	अगर (!chan->desc && !chan->busy)
		sपंचांग32_mdma_start_transfer(chan);

end:
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_छोड़ो(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	ret = sपंचांग32_mdma_disable_chan(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	अगर (!ret)
		dev_dbg(chan2dev(chan), "vchan %pK: pause\n", &chan->vchan);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_resume(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	काष्ठा sपंचांग32_mdma_hwdesc *hwdesc;
	अचिन्हित दीर्घ flags;
	u32 status, reg;

	hwdesc = chan->desc->node[chan->curr_hwdesc].hwdesc;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	/* Re-configure control रेजिस्टर */
	sपंचांग32_mdma_ग_लिखो(dmadev, STM32_MDMA_CCR(chan->id), chan->desc->ccr);

	/* Clear पूर्णांकerrupt status अगर it is there */
	status = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CISR(chan->id));
	अगर (status)
		sपंचांग32_mdma_set_bits(dmadev, STM32_MDMA_CIFCR(chan->id), status);

	sपंचांग32_mdma_dump_reg(chan);

	/* Re-start DMA */
	reg = STM32_MDMA_CCR(chan->id);
	sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CCR_EN);

	/* Set SW request in हाल of MEM2MEM transfer */
	अगर (hwdesc->ctcr & STM32_MDMA_CTCR_SWRM)
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CCR_SWRQ);

	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	dev_dbg(chan2dev(chan), "vchan %pK: resume\n", &chan->vchan);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_terminate_all(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	अगर (chan->desc) अणु
		vchan_terminate_vdesc(&chan->desc->vdesc);
		अगर (chan->busy)
			sपंचांग32_mdma_stop(chan);
		chan->desc = शून्य;
	पूर्ण
	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_mdma_synchronize(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);

	vchan_synchronize(&chan->vchan);
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_slave_config(काष्ठा dma_chan *c,
				   काष्ठा dma_slave_config *config)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);

	स_नकल(&chan->dma_config, config, माप(*config));

	वापस 0;
पूर्ण

अटल माप_प्रकार sपंचांग32_mdma_desc_residue(काष्ठा sपंचांग32_mdma_chan *chan,
				      काष्ठा sपंचांग32_mdma_desc *desc,
				      u32 curr_hwdesc)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	काष्ठा sपंचांग32_mdma_hwdesc *hwdesc = desc->node[0].hwdesc;
	u32 cbndtr, residue, modulo, burst_size;
	पूर्णांक i;

	residue = 0;
	क्रम (i = curr_hwdesc + 1; i < desc->count; i++) अणु
		hwdesc = desc->node[i].hwdesc;
		residue += STM32_MDMA_CBNDTR_BNDT(hwdesc->cbndtr);
	पूर्ण
	cbndtr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CBNDTR(chan->id));
	residue += cbndtr & STM32_MDMA_CBNDTR_BNDT_MASK;

	अगर (!chan->mem_burst)
		वापस residue;

	burst_size = chan->mem_burst * chan->mem_width;
	modulo = residue % burst_size;
	अगर (modulo)
		residue = residue - modulo + burst_size;

	वापस residue;
पूर्ण

अटल क्रमागत dma_status sपंचांग32_mdma_tx_status(काष्ठा dma_chan *c,
					    dma_cookie_t cookie,
					    काष्ठा dma_tx_state *state)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;
	u32 residue = 0;

	status = dma_cookie_status(c, cookie, state);
	अगर ((status == DMA_COMPLETE) || (!state))
		वापस status;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	vdesc = vchan_find_desc(&chan->vchan, cookie);
	अगर (chan->desc && cookie == chan->desc->vdesc.tx.cookie)
		residue = sपंचांग32_mdma_desc_residue(chan, chan->desc,
						  chan->curr_hwdesc);
	अन्यथा अगर (vdesc)
		residue = sपंचांग32_mdma_desc_residue(chan,
						  to_sपंचांग32_mdma_desc(vdesc), 0);
	dma_set_residue(state, residue);

	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	वापस status;
पूर्ण

अटल व्योम sपंचांग32_mdma_xfer_end(काष्ठा sपंचांग32_mdma_chan *chan)
अणु
	vchan_cookie_complete(&chan->desc->vdesc);
	chan->desc = शून्य;
	chan->busy = false;

	/* Start the next transfer अगर this driver has a next desc */
	sपंचांग32_mdma_start_transfer(chan);
पूर्ण

अटल irqवापस_t sपंचांग32_mdma_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = devid;
	काष्ठा sपंचांग32_mdma_chan *chan = devid;
	u32 reg, id, ccr, ien, status;

	/* Find out which channel generates the पूर्णांकerrupt */
	status = पढ़ोl_relaxed(dmadev->base + STM32_MDMA_GISR0);
	अगर (status) अणु
		id = __ffs(status);
	पूर्ण अन्यथा अणु
		status = पढ़ोl_relaxed(dmadev->base + STM32_MDMA_GISR1);
		अगर (!status) अणु
			dev_dbg(mdma2dev(dmadev), "spurious it\n");
			वापस IRQ_NONE;
		पूर्ण
		id = __ffs(status);
		/*
		 * As GISR0 provides status क्रम channel id from 0 to 31,
		 * so GISR1 provides status क्रम channel id from 32 to 62
		 */
		id += 32;
	पूर्ण

	chan = &dmadev->chan[id];
	अगर (!chan) अणु
		dev_warn(mdma2dev(dmadev), "MDMA channel not initialized\n");
		वापस IRQ_NONE;
	पूर्ण

	/* Handle पूर्णांकerrupt क्रम the channel */
	spin_lock(&chan->vchan.lock);
	status = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CISR(id));
	/* Mask Channel ReQuest Active bit which can be set in हाल of MEM2MEM */
	status &= ~STM32_MDMA_CISR_CRQA;
	ccr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CCR(id));
	ien = (ccr & STM32_MDMA_CCR_IRQ_MASK) >> 1;

	अगर (!(status & ien)) अणु
		spin_unlock(&chan->vchan.lock);
		dev_warn(chan2dev(chan),
			 "spurious it (status=0x%04x, ien=0x%04x)\n",
			 status, ien);
		वापस IRQ_NONE;
	पूर्ण

	reg = STM32_MDMA_CIFCR(id);

	अगर (status & STM32_MDMA_CISR_TEIF) अणु
		dev_err(chan2dev(chan), "Transfer Err: stat=0x%08x\n",
			पढ़ोl_relaxed(dmadev->base + STM32_MDMA_CESR(id)));
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CTEIF);
		status &= ~STM32_MDMA_CISR_TEIF;
	पूर्ण

	अगर (status & STM32_MDMA_CISR_CTCIF) अणु
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CCTCIF);
		status &= ~STM32_MDMA_CISR_CTCIF;
		sपंचांग32_mdma_xfer_end(chan);
	पूर्ण

	अगर (status & STM32_MDMA_CISR_BRTIF) अणु
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CBRTIF);
		status &= ~STM32_MDMA_CISR_BRTIF;
	पूर्ण

	अगर (status & STM32_MDMA_CISR_BTIF) अणु
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CBTIF);
		status &= ~STM32_MDMA_CISR_BTIF;
		chan->curr_hwdesc++;
		अगर (chan->desc && chan->desc->cyclic) अणु
			अगर (chan->curr_hwdesc == chan->desc->count)
				chan->curr_hwdesc = 0;
			vchan_cyclic_callback(&chan->desc->vdesc);
		पूर्ण
	पूर्ण

	अगर (status & STM32_MDMA_CISR_TCIF) अणु
		sपंचांग32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CLTCIF);
		status &= ~STM32_MDMA_CISR_TCIF;
	पूर्ण

	अगर (status) अणु
		sपंचांग32_mdma_set_bits(dmadev, reg, status);
		dev_err(chan2dev(chan), "DMA error: status=0x%08x\n", status);
		अगर (!(ccr & STM32_MDMA_CCR_EN))
			dev_err(chan2dev(chan), "chan disabled by HW\n");
	पूर्ण

	spin_unlock(&chan->vchan.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_alloc_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	पूर्णांक ret;

	chan->desc_pool = dmam_pool_create(dev_name(&c->dev->device),
					   c->device->dev,
					   माप(काष्ठा sपंचांग32_mdma_hwdesc),
					  __alignof__(काष्ठा sपंचांग32_mdma_hwdesc),
					   0);
	अगर (!chan->desc_pool) अणु
		dev_err(chan2dev(chan), "failed to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	ret = pm_runसमय_resume_and_get(dmadev->ddev.dev);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32_mdma_disable_chan(chan);
	अगर (ret < 0)
		pm_runसमय_put(dmadev->ddev.dev);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_mdma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan = to_sपंचांग32_mdma_chan(c);
	काष्ठा sपंचांग32_mdma_device *dmadev = sपंचांग32_mdma_get_dev(chan);
	अचिन्हित दीर्घ flags;

	dev_dbg(chan2dev(chan), "Freeing channel %d\n", chan->id);

	अगर (chan->busy) अणु
		spin_lock_irqsave(&chan->vchan.lock, flags);
		sपंचांग32_mdma_stop(chan);
		chan->desc = शून्य;
		spin_unlock_irqrestore(&chan->vchan.lock, flags);
	पूर्ण

	pm_runसमय_put(dmadev->ddev.dev);
	vchan_मुक्त_chan_resources(to_virt_chan(c));
	dmam_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;
पूर्ण

अटल काष्ठा dma_chan *sपंचांग32_mdma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					    काष्ठा of_dma *ofdma)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = ofdma->of_dma_data;
	काष्ठा sपंचांग32_mdma_chan *chan;
	काष्ठा dma_chan *c;
	काष्ठा sपंचांग32_mdma_chan_config config;

	अगर (dma_spec->args_count < 5) अणु
		dev_err(mdma2dev(dmadev), "Bad number of args\n");
		वापस शून्य;
	पूर्ण

	config.request = dma_spec->args[0];
	config.priority_level = dma_spec->args[1];
	config.transfer_config = dma_spec->args[2];
	config.mask_addr = dma_spec->args[3];
	config.mask_data = dma_spec->args[4];

	अगर (config.request >= dmadev->nr_requests) अणु
		dev_err(mdma2dev(dmadev), "Bad request line\n");
		वापस शून्य;
	पूर्ण

	अगर (config.priority_level > STM32_MDMA_VERY_HIGH_PRIORITY) अणु
		dev_err(mdma2dev(dmadev), "Priority level not supported\n");
		वापस शून्य;
	पूर्ण

	c = dma_get_any_slave_channel(&dmadev->ddev);
	अगर (!c) अणु
		dev_err(mdma2dev(dmadev), "No more channels available\n");
		वापस शून्य;
	पूर्ण

	chan = to_sपंचांग32_mdma_chan(c);
	chan->chan_config = config;

	वापस c;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_mdma_of_match[] = अणु
	अणु .compatible = "st,stm32h7-mdma", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_mdma_of_match);

अटल पूर्णांक sपंचांग32_mdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_mdma_chan *chan;
	काष्ठा sपंचांग32_mdma_device *dmadev;
	काष्ठा dma_device *dd;
	काष्ठा device_node *of_node;
	काष्ठा resource *res;
	काष्ठा reset_control *rst;
	u32 nr_channels, nr_requests;
	पूर्णांक i, count, ret;

	of_node = pdev->dev.of_node;
	अगर (!of_node)
		वापस -ENODEV;

	ret = device_property_पढ़ो_u32(&pdev->dev, "dma-channels",
				       &nr_channels);
	अगर (ret) अणु
		nr_channels = STM32_MDMA_MAX_CHANNELS;
		dev_warn(&pdev->dev, "MDMA defaulting on %i channels\n",
			 nr_channels);
	पूर्ण

	ret = device_property_पढ़ो_u32(&pdev->dev, "dma-requests",
				       &nr_requests);
	अगर (ret) अणु
		nr_requests = STM32_MDMA_MAX_REQUESTS;
		dev_warn(&pdev->dev, "MDMA defaulting on %i request lines\n",
			 nr_requests);
	पूर्ण

	count = device_property_count_u32(&pdev->dev, "st,ahb-addr-masks");
	अगर (count < 0)
		count = 0;

	dmadev = devm_kzalloc(&pdev->dev, माप(*dmadev) + माप(u32) * count,
			      GFP_KERNEL);
	अगर (!dmadev)
		वापस -ENOMEM;

	dmadev->nr_channels = nr_channels;
	dmadev->nr_requests = nr_requests;
	device_property_पढ़ो_u32_array(&pdev->dev, "st,ahb-addr-masks",
				       dmadev->ahb_addr_masks,
				       count);
	dmadev->nr_ahb_addr_masks = count;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dmadev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dmadev->base))
		वापस PTR_ERR(dmadev->base);

	dmadev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dmadev->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(dmadev->clk),
				     "Missing clock controller\n");

	ret = clk_prepare_enable(dmadev->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "clk_prep_enable error: %d\n", ret);
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		ret = PTR_ERR(rst);
		अगर (ret == -EPROBE_DEFER)
			जाओ err_clk;
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rst);
		udelay(2);
		reset_control_deनिश्चित(rst);
	पूर्ण

	dd = &dmadev->ddev;
	dma_cap_set(DMA_SLAVE, dd->cap_mask);
	dma_cap_set(DMA_PRIVATE, dd->cap_mask);
	dma_cap_set(DMA_CYCLIC, dd->cap_mask);
	dma_cap_set(DMA_MEMCPY, dd->cap_mask);
	dd->device_alloc_chan_resources = sपंचांग32_mdma_alloc_chan_resources;
	dd->device_मुक्त_chan_resources = sपंचांग32_mdma_मुक्त_chan_resources;
	dd->device_tx_status = sपंचांग32_mdma_tx_status;
	dd->device_issue_pending = sपंचांग32_mdma_issue_pending;
	dd->device_prep_slave_sg = sपंचांग32_mdma_prep_slave_sg;
	dd->device_prep_dma_cyclic = sपंचांग32_mdma_prep_dma_cyclic;
	dd->device_prep_dma_स_नकल = sपंचांग32_mdma_prep_dma_स_नकल;
	dd->device_config = sपंचांग32_mdma_slave_config;
	dd->device_छोड़ो = sपंचांग32_mdma_छोड़ो;
	dd->device_resume = sपंचांग32_mdma_resume;
	dd->device_terminate_all = sपंचांग32_mdma_terminate_all;
	dd->device_synchronize = sपंचांग32_mdma_synchronize;
	dd->descriptor_reuse = true;

	dd->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_8_BYTES);
	dd->dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_8_BYTES);
	dd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV) |
		BIT(DMA_MEM_TO_MEM);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	dd->max_burst = STM32_MDMA_MAX_BURST;
	dd->dev = &pdev->dev;
	INIT_LIST_HEAD(&dd->channels);

	क्रम (i = 0; i < dmadev->nr_channels; i++) अणु
		chan = &dmadev->chan[i];
		chan->id = i;
		chan->vchan.desc_मुक्त = sपंचांग32_mdma_desc_मुक्त;
		vchan_init(&chan->vchan, dd);
	पूर्ण

	dmadev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dmadev->irq < 0) अणु
		ret = dmadev->irq;
		जाओ err_clk;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, dmadev->irq, sपंचांग32_mdma_irq_handler,
			       0, dev_name(&pdev->dev), dmadev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		जाओ err_clk;
	पूर्ण

	ret = dmaenginem_async_device_रेजिस्टर(dd);
	अगर (ret)
		जाओ err_clk;

	ret = of_dma_controller_रेजिस्टर(of_node, sपंचांग32_mdma_of_xlate, dmadev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"STM32 MDMA DMA OF registration failed %d\n", ret);
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dmadev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_put(&pdev->dev);

	dev_info(&pdev->dev, "STM32 MDMA driver registered\n");

	वापस 0;

err_clk:
	clk_disable_unprepare(dmadev->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग32_mdma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = dev_get_drvdata(dev);

	clk_disable_unprepare(dmadev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(dmadev->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_mdma_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_mdma_device *dmadev = dev_get_drvdata(dev);
	u32 ccr, id;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (id = 0; id < dmadev->nr_channels; id++) अणु
		ccr = sपंचांग32_mdma_पढ़ो(dmadev, STM32_MDMA_CCR(id));
		अगर (ccr & STM32_MDMA_CCR_EN) अणु
			dev_warn(dev, "Suspend is prevented by Chan %i\n", id);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	pm_runसमय_put_sync(dev);

	pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_mdma_pm_resume(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_mdma_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_mdma_pm_suspend, sपंचांग32_mdma_pm_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_mdma_runसमय_suspend,
			   sपंचांग32_mdma_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_mdma_driver = अणु
	.probe = sपंचांग32_mdma_probe,
	.driver = अणु
		.name = "stm32-mdma",
		.of_match_table = sपंचांग32_mdma_of_match,
		.pm = &sपंचांग32_mdma_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sपंचांग32_mdma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sपंचांग32_mdma_driver);
पूर्ण

subsys_initcall(sपंचांग32_mdma_init);

MODULE_DESCRIPTION("Driver for STM32 MDMA controller");
MODULE_AUTHOR("M'boumba Cedric Madianga <cedric.madianga@gmail.com>");
MODULE_AUTHOR("Pierre-Yves Mordret <pierre-yves.mordret@st.com>");
MODULE_LICENSE("GPL v2");
