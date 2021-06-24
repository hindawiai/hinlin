<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ingenic JZ4780 DMA controller
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Alex Smith <alex@alex-smith.me.uk>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

/* Global रेजिस्टरs. */
#घोषणा JZ_DMA_REG_DMAC		0x00
#घोषणा JZ_DMA_REG_सूचीQP	0x04
#घोषणा JZ_DMA_REG_DDR		0x08
#घोषणा JZ_DMA_REG_DDRS		0x0c
#घोषणा JZ_DMA_REG_DCKE		0x10
#घोषणा JZ_DMA_REG_DCKES	0x14
#घोषणा JZ_DMA_REG_DCKEC	0x18
#घोषणा JZ_DMA_REG_DMACP	0x1c
#घोषणा JZ_DMA_REG_DSIRQP	0x20
#घोषणा JZ_DMA_REG_DSIRQM	0x24
#घोषणा JZ_DMA_REG_DCIRQP	0x28
#घोषणा JZ_DMA_REG_DCIRQM	0x2c

/* Per-channel रेजिस्टरs. */
#घोषणा JZ_DMA_REG_CHAN(n)	(n * 0x20)
#घोषणा JZ_DMA_REG_DSA		0x00
#घोषणा JZ_DMA_REG_DTA		0x04
#घोषणा JZ_DMA_REG_DTC		0x08
#घोषणा JZ_DMA_REG_DRT		0x0c
#घोषणा JZ_DMA_REG_DCS		0x10
#घोषणा JZ_DMA_REG_DCM		0x14
#घोषणा JZ_DMA_REG_DDA		0x18
#घोषणा JZ_DMA_REG_DSD		0x1c

#घोषणा JZ_DMA_DMAC_DMAE	BIT(0)
#घोषणा JZ_DMA_DMAC_AR		BIT(2)
#घोषणा JZ_DMA_DMAC_HLT		BIT(3)
#घोषणा JZ_DMA_DMAC_FAIC	BIT(27)
#घोषणा JZ_DMA_DMAC_FMSC	BIT(31)

#घोषणा JZ_DMA_DRT_AUTO		0x8

#घोषणा JZ_DMA_DCS_CTE		BIT(0)
#घोषणा JZ_DMA_DCS_HLT		BIT(2)
#घोषणा JZ_DMA_DCS_TT		BIT(3)
#घोषणा JZ_DMA_DCS_AR		BIT(4)
#घोषणा JZ_DMA_DCS_DES8		BIT(30)

#घोषणा JZ_DMA_DCM_LINK		BIT(0)
#घोषणा JZ_DMA_DCM_TIE		BIT(1)
#घोषणा JZ_DMA_DCM_STDE		BIT(2)
#घोषणा JZ_DMA_DCM_TSZ_SHIFT	8
#घोषणा JZ_DMA_DCM_TSZ_MASK	(0x7 << JZ_DMA_DCM_TSZ_SHIFT)
#घोषणा JZ_DMA_DCM_DP_SHIFT	12
#घोषणा JZ_DMA_DCM_SP_SHIFT	14
#घोषणा JZ_DMA_DCM_DAI		BIT(22)
#घोषणा JZ_DMA_DCM_SAI		BIT(23)

#घोषणा JZ_DMA_SIZE_4_BYTE	0x0
#घोषणा JZ_DMA_SIZE_1_BYTE	0x1
#घोषणा JZ_DMA_SIZE_2_BYTE	0x2
#घोषणा JZ_DMA_SIZE_16_BYTE	0x3
#घोषणा JZ_DMA_SIZE_32_BYTE	0x4
#घोषणा JZ_DMA_SIZE_64_BYTE	0x5
#घोषणा JZ_DMA_SIZE_128_BYTE	0x6

#घोषणा JZ_DMA_WIDTH_32_BIT	0x0
#घोषणा JZ_DMA_WIDTH_8_BIT	0x1
#घोषणा JZ_DMA_WIDTH_16_BIT	0x2

#घोषणा JZ_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE)	 | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

#घोषणा JZ4780_DMA_CTRL_OFFSET	0x1000

/* macros क्रम use with jz4780_dma_soc_data.flags */
#घोषणा JZ_SOC_DATA_ALLOW_LEGACY_DT	BIT(0)
#घोषणा JZ_SOC_DATA_PROGRAMMABLE_DMA	BIT(1)
#घोषणा JZ_SOC_DATA_PER_CHAN_PM		BIT(2)
#घोषणा JZ_SOC_DATA_NO_DCKES_DCKEC	BIT(3)
#घोषणा JZ_SOC_DATA_BREAK_LINKS		BIT(4)

/**
 * काष्ठा jz4780_dma_hwdesc - descriptor काष्ठाure पढ़ो by the DMA controller.
 * @dcm: value क्रम the DCM (channel command) रेजिस्टर
 * @dsa: source address
 * @dta: target address
 * @dtc: transfer count (number of blocks of the transfer size specअगरied in DCM
 * to transfer) in the low 24 bits, offset of the next descriptor from the
 * descriptor base address in the upper 8 bits.
 */
काष्ठा jz4780_dma_hwdesc अणु
	uपूर्णांक32_t dcm;
	uपूर्णांक32_t dsa;
	uपूर्णांक32_t dta;
	uपूर्णांक32_t dtc;
पूर्ण;

/* Size of allocations क्रम hardware descriptor blocks. */
#घोषणा JZ_DMA_DESC_BLOCK_SIZE	PAGE_SIZE
#घोषणा JZ_DMA_MAX_DESC		\
	(JZ_DMA_DESC_BLOCK_SIZE / माप(काष्ठा jz4780_dma_hwdesc))

काष्ठा jz4780_dma_desc अणु
	काष्ठा virt_dma_desc vdesc;

	काष्ठा jz4780_dma_hwdesc *desc;
	dma_addr_t desc_phys;
	अचिन्हित पूर्णांक count;
	क्रमागत dma_transaction_type type;
	uपूर्णांक32_t status;
पूर्ण;

काष्ठा jz4780_dma_chan अणु
	काष्ठा virt_dma_chan vchan;
	अचिन्हित पूर्णांक id;
	काष्ठा dma_pool *desc_pool;

	uपूर्णांक32_t transfer_type;
	uपूर्णांक32_t transfer_shअगरt;
	काष्ठा dma_slave_config	config;

	काष्ठा jz4780_dma_desc *desc;
	अचिन्हित पूर्णांक curr_hwdesc;
पूर्ण;

काष्ठा jz4780_dma_soc_data अणु
	अचिन्हित पूर्णांक nb_channels;
	अचिन्हित पूर्णांक transfer_ord_max;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा jz4780_dma_dev अणु
	काष्ठा dma_device dma_device;
	व्योम __iomem *chn_base;
	व्योम __iomem *ctrl_base;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक irq;
	स्थिर काष्ठा jz4780_dma_soc_data *soc_data;

	uपूर्णांक32_t chan_reserved;
	काष्ठा jz4780_dma_chan chan[];
पूर्ण;

काष्ठा jz4780_dma_filter_data अणु
	uपूर्णांक32_t transfer_type;
	पूर्णांक channel;
पूर्ण;

अटल अंतरभूत काष्ठा jz4780_dma_chan *to_jz4780_dma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा jz4780_dma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत काष्ठा jz4780_dma_desc *to_jz4780_dma_desc(
	काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा jz4780_dma_desc, vdesc);
पूर्ण

अटल अंतरभूत काष्ठा jz4780_dma_dev *jz4780_dma_chan_parent(
	काष्ठा jz4780_dma_chan *jzchan)
अणु
	वापस container_of(jzchan->vchan.chan.device, काष्ठा jz4780_dma_dev,
			    dma_device);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t jz4780_dma_chn_पढ़ोl(काष्ठा jz4780_dma_dev *jzdma,
	अचिन्हित पूर्णांक chn, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(jzdma->chn_base + reg + JZ_DMA_REG_CHAN(chn));
पूर्ण

अटल अंतरभूत व्योम jz4780_dma_chn_ग_लिखोl(काष्ठा jz4780_dma_dev *jzdma,
	अचिन्हित पूर्णांक chn, अचिन्हित पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, jzdma->chn_base + reg + JZ_DMA_REG_CHAN(chn));
पूर्ण

अटल अंतरभूत uपूर्णांक32_t jz4780_dma_ctrl_पढ़ोl(काष्ठा jz4780_dma_dev *jzdma,
	अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(jzdma->ctrl_base + reg);
पूर्ण

अटल अंतरभूत व्योम jz4780_dma_ctrl_ग_लिखोl(काष्ठा jz4780_dma_dev *jzdma,
	अचिन्हित पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, jzdma->ctrl_base + reg);
पूर्ण

अटल अंतरभूत व्योम jz4780_dma_chan_enable(काष्ठा jz4780_dma_dev *jzdma,
	अचिन्हित पूर्णांक chn)
अणु
	अगर (jzdma->soc_data->flags & JZ_SOC_DATA_PER_CHAN_PM) अणु
		अचिन्हित पूर्णांक reg;

		अगर (jzdma->soc_data->flags & JZ_SOC_DATA_NO_DCKES_DCKEC)
			reg = JZ_DMA_REG_DCKE;
		अन्यथा
			reg = JZ_DMA_REG_DCKES;

		jz4780_dma_ctrl_ग_लिखोl(jzdma, reg, BIT(chn));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम jz4780_dma_chan_disable(काष्ठा jz4780_dma_dev *jzdma,
	अचिन्हित पूर्णांक chn)
अणु
	अगर ((jzdma->soc_data->flags & JZ_SOC_DATA_PER_CHAN_PM) &&
			!(jzdma->soc_data->flags & JZ_SOC_DATA_NO_DCKES_DCKEC))
		jz4780_dma_ctrl_ग_लिखोl(jzdma, JZ_DMA_REG_DCKEC, BIT(chn));
पूर्ण

अटल काष्ठा jz4780_dma_desc *jz4780_dma_desc_alloc(
	काष्ठा jz4780_dma_chan *jzchan, अचिन्हित पूर्णांक count,
	क्रमागत dma_transaction_type type)
अणु
	काष्ठा jz4780_dma_desc *desc;

	अगर (count > JZ_DMA_MAX_DESC)
		वापस शून्य;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->desc = dma_pool_alloc(jzchan->desc_pool, GFP_NOWAIT,
				    &desc->desc_phys);
	अगर (!desc->desc) अणु
		kमुक्त(desc);
		वापस शून्य;
	पूर्ण

	desc->count = count;
	desc->type = type;
	वापस desc;
पूर्ण

अटल व्योम jz4780_dma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा jz4780_dma_desc *desc = to_jz4780_dma_desc(vdesc);
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(vdesc->tx.chan);

	dma_pool_मुक्त(jzchan->desc_pool, desc->desc, desc->desc_phys);
	kमुक्त(desc);
पूर्ण

अटल uपूर्णांक32_t jz4780_dma_transfer_size(काष्ठा jz4780_dma_chan *jzchan,
	अचिन्हित दीर्घ val, uपूर्णांक32_t *shअगरt)
अणु
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	पूर्णांक ord = ffs(val) - 1;

	/*
	 * 8 byte transfer sizes unsupported so fall back on 4. If it's larger
	 * than the maximum, just limit it. It is perfectly safe to fall back
	 * in this way since we won't exceed the maximum burst size supported
	 * by the device, the only effect is reduced efficiency. This is better
	 * than refusing to perक्रमm the request at all.
	 */
	अगर (ord == 3)
		ord = 2;
	अन्यथा अगर (ord > jzdma->soc_data->transfer_ord_max)
		ord = jzdma->soc_data->transfer_ord_max;

	*shअगरt = ord;

	चयन (ord) अणु
	हाल 0:
		वापस JZ_DMA_SIZE_1_BYTE;
	हाल 1:
		वापस JZ_DMA_SIZE_2_BYTE;
	हाल 2:
		वापस JZ_DMA_SIZE_4_BYTE;
	हाल 4:
		वापस JZ_DMA_SIZE_16_BYTE;
	हाल 5:
		वापस JZ_DMA_SIZE_32_BYTE;
	हाल 6:
		वापस JZ_DMA_SIZE_64_BYTE;
	शेष:
		वापस JZ_DMA_SIZE_128_BYTE;
	पूर्ण
पूर्ण

अटल पूर्णांक jz4780_dma_setup_hwdesc(काष्ठा jz4780_dma_chan *jzchan,
	काष्ठा jz4780_dma_hwdesc *desc, dma_addr_t addr, माप_प्रकार len,
	क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा dma_slave_config *config = &jzchan->config;
	uपूर्णांक32_t width, maxburst, tsz;

	अगर (direction == DMA_MEM_TO_DEV) अणु
		desc->dcm = JZ_DMA_DCM_SAI;
		desc->dsa = addr;
		desc->dta = config->dst_addr;

		width = config->dst_addr_width;
		maxburst = config->dst_maxburst;
	पूर्ण अन्यथा अणु
		desc->dcm = JZ_DMA_DCM_DAI;
		desc->dsa = config->src_addr;
		desc->dta = addr;

		width = config->src_addr_width;
		maxburst = config->src_maxburst;
	पूर्ण

	/*
	 * This calculates the maximum transfer size that can be used with the
	 * given address, length, width and maximum burst size. The address
	 * must be aligned to the transfer size, the total length must be
	 * भागisible by the transfer size, and we must not use more than the
	 * maximum burst specअगरied by the user.
	 */
	tsz = jz4780_dma_transfer_size(jzchan, addr | len | (width * maxburst),
				       &jzchan->transfer_shअगरt);

	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		width = JZ_DMA_WIDTH_32_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	desc->dcm |= tsz << JZ_DMA_DCM_TSZ_SHIFT;
	desc->dcm |= width << JZ_DMA_DCM_SP_SHIFT;
	desc->dcm |= width << JZ_DMA_DCM_DP_SHIFT;

	desc->dtc = len >> jzchan->transfer_shअगरt;
	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *jz4780_dma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags,
	व्योम *context)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	काष्ठा jz4780_dma_desc *desc;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	desc = jz4780_dma_desc_alloc(jzchan, sg_len, DMA_SLAVE);
	अगर (!desc)
		वापस शून्य;

	क्रम (i = 0; i < sg_len; i++) अणु
		err = jz4780_dma_setup_hwdesc(jzchan, &desc->desc[i],
					      sg_dma_address(&sgl[i]),
					      sg_dma_len(&sgl[i]),
					      direction);
		अगर (err < 0) अणु
			jz4780_dma_desc_मुक्त(&jzchan->desc->vdesc);
			वापस शून्य;
		पूर्ण

		desc->desc[i].dcm |= JZ_DMA_DCM_TIE;

		अगर (i != (sg_len - 1) &&
		    !(jzdma->soc_data->flags & JZ_SOC_DATA_BREAK_LINKS)) अणु
			/* Automatically proceeed to the next descriptor. */
			desc->desc[i].dcm |= JZ_DMA_DCM_LINK;

			/*
			 * The upper 8 bits of the DTC field in the descriptor
			 * must be set to (offset from descriptor base of next
			 * descriptor >> 4).
			 */
			desc->desc[i].dtc |=
				(((i + 1) * माप(*desc->desc)) >> 4) << 24;
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&jzchan->vchan, &desc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *jz4780_dma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा jz4780_dma_desc *desc;
	अचिन्हित पूर्णांक periods, i;
	पूर्णांक err;

	अगर (buf_len % period_len)
		वापस शून्य;

	periods = buf_len / period_len;

	desc = jz4780_dma_desc_alloc(jzchan, periods, DMA_CYCLIC);
	अगर (!desc)
		वापस शून्य;

	क्रम (i = 0; i < periods; i++) अणु
		err = jz4780_dma_setup_hwdesc(jzchan, &desc->desc[i], buf_addr,
					      period_len, direction);
		अगर (err < 0) अणु
			jz4780_dma_desc_मुक्त(&jzchan->desc->vdesc);
			वापस शून्य;
		पूर्ण

		buf_addr += period_len;

		/*
		 * Set the link bit to indicate that the controller should
		 * स्वतःmatically proceed to the next descriptor. In
		 * jz4780_dma_begin(), this will be cleared अगर we need to issue
		 * an पूर्णांकerrupt after each period.
		 */
		desc->desc[i].dcm |= JZ_DMA_DCM_TIE | JZ_DMA_DCM_LINK;

		/*
		 * The upper 8 bits of the DTC field in the descriptor must be
		 * set to (offset from descriptor base of next descriptor >> 4).
		 * If this is the last descriptor, link it back to the first,
		 * i.e. leave offset set to 0, otherwise poपूर्णांक to the next one.
		 */
		अगर (i != (periods - 1)) अणु
			desc->desc[i].dtc |=
				(((i + 1) * माप(*desc->desc)) >> 4) << 24;
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&jzchan->vchan, &desc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *jz4780_dma_prep_dma_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा jz4780_dma_desc *desc;
	uपूर्णांक32_t tsz;

	desc = jz4780_dma_desc_alloc(jzchan, 1, DMA_MEMCPY);
	अगर (!desc)
		वापस शून्य;

	tsz = jz4780_dma_transfer_size(jzchan, dest | src | len,
				       &jzchan->transfer_shअगरt);

	jzchan->transfer_type = JZ_DMA_DRT_AUTO;

	desc->desc[0].dsa = src;
	desc->desc[0].dta = dest;
	desc->desc[0].dcm = JZ_DMA_DCM_TIE | JZ_DMA_DCM_SAI | JZ_DMA_DCM_DAI |
			    tsz << JZ_DMA_DCM_TSZ_SHIFT |
			    JZ_DMA_WIDTH_32_BIT << JZ_DMA_DCM_SP_SHIFT |
			    JZ_DMA_WIDTH_32_BIT << JZ_DMA_DCM_DP_SHIFT;
	desc->desc[0].dtc = len >> jzchan->transfer_shअगरt;

	वापस vchan_tx_prep(&jzchan->vchan, &desc->vdesc, flags);
पूर्ण

अटल व्योम jz4780_dma_begin(काष्ठा jz4780_dma_chan *jzchan)
अणु
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	काष्ठा virt_dma_desc *vdesc;
	अचिन्हित पूर्णांक i;
	dma_addr_t desc_phys;

	अगर (!jzchan->desc) अणु
		vdesc = vchan_next_desc(&jzchan->vchan);
		अगर (!vdesc)
			वापस;

		list_del(&vdesc->node);

		jzchan->desc = to_jz4780_dma_desc(vdesc);
		jzchan->curr_hwdesc = 0;

		अगर (jzchan->desc->type == DMA_CYCLIC && vdesc->tx.callback) अणु
			/*
			 * The DMA controller करोesn't support triggering an
			 * पूर्णांकerrupt after processing each descriptor, only
			 * after processing an entire terminated list of
			 * descriptors. For a cyclic DMA setup the list of
			 * descriptors is not terminated so we can never get an
			 * पूर्णांकerrupt.
			 *
			 * If the user requested a callback क्रम a cyclic DMA
			 * setup then we workaround this hardware limitation
			 * here by degrading to a set of unlinked descriptors
			 * which we will submit in sequence in response to the
			 * completion of processing the previous descriptor.
			 */
			क्रम (i = 0; i < jzchan->desc->count; i++)
				jzchan->desc->desc[i].dcm &= ~JZ_DMA_DCM_LINK;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * There is an existing transfer, thereक्रमe this must be one
		 * क्रम which we unlinked the descriptors above. Advance to the
		 * next one in the list.
		 */
		jzchan->curr_hwdesc =
			(jzchan->curr_hwdesc + 1) % jzchan->desc->count;
	पूर्ण

	/* Enable the channel's घड़ी. */
	jz4780_dma_chan_enable(jzdma, jzchan->id);

	/* Use 4-word descriptors. */
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DCS, 0);

	/* Set transfer type. */
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DRT,
			      jzchan->transfer_type);

	/*
	 * Set the transfer count. This is redundant क्रम a descriptor-driven
	 * transfer. However, there can be a delay between the transfer start
	 * समय and when DTCn reg contains the new transfer count. Setting
	 * it explicitly ensures residue is computed correctly at all बार.
	 */
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DTC,
				jzchan->desc->desc[jzchan->curr_hwdesc].dtc);

	/* Write descriptor address and initiate descriptor fetch. */
	desc_phys = jzchan->desc->desc_phys +
		    (jzchan->curr_hwdesc * माप(*jzchan->desc->desc));
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DDA, desc_phys);
	jz4780_dma_ctrl_ग_लिखोl(jzdma, JZ_DMA_REG_DDRS, BIT(jzchan->id));

	/* Enable the channel. */
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DCS,
			      JZ_DMA_DCS_CTE);
पूर्ण

अटल व्योम jz4780_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&jzchan->vchan.lock, flags);

	अगर (vchan_issue_pending(&jzchan->vchan) && !jzchan->desc)
		jz4780_dma_begin(jzchan);

	spin_unlock_irqrestore(&jzchan->vchan.lock, flags);
पूर्ण

अटल पूर्णांक jz4780_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&jzchan->vchan.lock, flags);

	/* Clear the DMA status and stop the transfer. */
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DCS, 0);
	अगर (jzchan->desc) अणु
		vchan_terminate_vdesc(&jzchan->desc->vdesc);
		jzchan->desc = शून्य;
	पूर्ण

	jz4780_dma_chan_disable(jzdma, jzchan->id);

	vchan_get_all_descriptors(&jzchan->vchan, &head);

	spin_unlock_irqrestore(&jzchan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&jzchan->vchan, &head);
	वापस 0;
पूर्ण

अटल व्योम jz4780_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);

	vchan_synchronize(&jzchan->vchan);
	jz4780_dma_chan_disable(jzdma, jzchan->id);
पूर्ण

अटल पूर्णांक jz4780_dma_config(काष्ठा dma_chan *chan,
	काष्ठा dma_slave_config *config)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	अगर ((config->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
	   || (config->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES))
		वापस -EINVAL;

	/* Copy the reset of the slave configuration, it is used later. */
	स_नकल(&jzchan->config, config, माप(jzchan->config));

	वापस 0;
पूर्ण

अटल माप_प्रकार jz4780_dma_desc_residue(काष्ठा jz4780_dma_chan *jzchan,
	काष्ठा jz4780_dma_desc *desc, अचिन्हित पूर्णांक next_sg)
अणु
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = next_sg; i < desc->count; i++)
		count += desc->desc[i].dtc & GENMASK(23, 0);

	अगर (next_sg != 0)
		count += jz4780_dma_chn_पढ़ोl(jzdma, jzchan->id,
					 JZ_DMA_REG_DTC);

	वापस count << jzchan->transfer_shअगरt;
पूर्ण

अटल क्रमागत dma_status jz4780_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ residue = 0;

	spin_lock_irqsave(&jzchan->vchan.lock, flags);

	status = dma_cookie_status(chan, cookie, txstate);
	अगर ((status == DMA_COMPLETE) || (txstate == शून्य))
		जाओ out_unlock_irqrestore;

	vdesc = vchan_find_desc(&jzchan->vchan, cookie);
	अगर (vdesc) अणु
		/* On the issued list, so hasn't been processed yet */
		residue = jz4780_dma_desc_residue(jzchan,
					to_jz4780_dma_desc(vdesc), 0);
	पूर्ण अन्यथा अगर (cookie == jzchan->desc->vdesc.tx.cookie) अणु
		residue = jz4780_dma_desc_residue(jzchan, jzchan->desc,
					jzchan->curr_hwdesc + 1);
	पूर्ण
	dma_set_residue(txstate, residue);

	अगर (vdesc && jzchan->desc && vdesc == &jzchan->desc->vdesc
	    && jzchan->desc->status & (JZ_DMA_DCS_AR | JZ_DMA_DCS_HLT))
		status = DMA_ERROR;

out_unlock_irqrestore:
	spin_unlock_irqrestore(&jzchan->vchan.lock, flags);
	वापस status;
पूर्ण

अटल bool jz4780_dma_chan_irq(काष्ठा jz4780_dma_dev *jzdma,
				काष्ठा jz4780_dma_chan *jzchan)
अणु
	स्थिर अचिन्हित पूर्णांक soc_flags = jzdma->soc_data->flags;
	काष्ठा jz4780_dma_desc *desc = jzchan->desc;
	uपूर्णांक32_t dcs;
	bool ack = true;

	spin_lock(&jzchan->vchan.lock);

	dcs = jz4780_dma_chn_पढ़ोl(jzdma, jzchan->id, JZ_DMA_REG_DCS);
	jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id, JZ_DMA_REG_DCS, 0);

	अगर (dcs & JZ_DMA_DCS_AR) अणु
		dev_warn(&jzchan->vchan.chan.dev->device,
			 "address error (DCS=0x%x)\n", dcs);
	पूर्ण

	अगर (dcs & JZ_DMA_DCS_HLT) अणु
		dev_warn(&jzchan->vchan.chan.dev->device,
			 "channel halt (DCS=0x%x)\n", dcs);
	पूर्ण

	अगर (jzchan->desc) अणु
		jzchan->desc->status = dcs;

		अगर ((dcs & (JZ_DMA_DCS_AR | JZ_DMA_DCS_HLT)) == 0) अणु
			अगर (jzchan->desc->type == DMA_CYCLIC) अणु
				vchan_cyclic_callback(&jzchan->desc->vdesc);

				jz4780_dma_begin(jzchan);
			पूर्ण अन्यथा अगर (dcs & JZ_DMA_DCS_TT) अणु
				अगर (!(soc_flags & JZ_SOC_DATA_BREAK_LINKS) ||
				    (jzchan->curr_hwdesc + 1 == desc->count)) अणु
					vchan_cookie_complete(&desc->vdesc);
					jzchan->desc = शून्य;
				पूर्ण

				jz4780_dma_begin(jzchan);
			पूर्ण अन्यथा अणु
				/* False positive - जारी the transfer */
				ack = false;
				jz4780_dma_chn_ग_लिखोl(jzdma, jzchan->id,
						      JZ_DMA_REG_DCS,
						      JZ_DMA_DCS_CTE);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&jzchan->vchan.chan.dev->device,
			"channel IRQ with no active transfer\n");
	पूर्ण

	spin_unlock(&jzchan->vchan.lock);

	वापस ack;
पूर्ण

अटल irqवापस_t jz4780_dma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा jz4780_dma_dev *jzdma = data;
	अचिन्हित पूर्णांक nb_channels = jzdma->soc_data->nb_channels;
	अचिन्हित दीर्घ pending;
	uपूर्णांक32_t dmac;
	पूर्णांक i;

	pending = jz4780_dma_ctrl_पढ़ोl(jzdma, JZ_DMA_REG_सूचीQP);

	क्रम_each_set_bit(i, &pending, nb_channels) अणु
		अगर (jz4780_dma_chan_irq(jzdma, &jzdma->chan[i]))
			pending &= ~BIT(i);
	पूर्ण

	/* Clear halt and address error status of all channels. */
	dmac = jz4780_dma_ctrl_पढ़ोl(jzdma, JZ_DMA_REG_DMAC);
	dmac &= ~(JZ_DMA_DMAC_HLT | JZ_DMA_DMAC_AR);
	jz4780_dma_ctrl_ग_लिखोl(jzdma, JZ_DMA_REG_DMAC, dmac);

	/* Clear पूर्णांकerrupt pending status. */
	jz4780_dma_ctrl_ग_लिखोl(jzdma, JZ_DMA_REG_सूचीQP, pending);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक jz4780_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	jzchan->desc_pool = dma_pool_create(dev_name(&chan->dev->device),
					    chan->device->dev,
					    JZ_DMA_DESC_BLOCK_SIZE,
					    PAGE_SIZE, 0);
	अगर (!jzchan->desc_pool) अणु
		dev_err(&chan->dev->device,
			"failed to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम jz4780_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	vchan_मुक्त_chan_resources(&jzchan->vchan);
	dma_pool_destroy(jzchan->desc_pool);
	jzchan->desc_pool = शून्य;
पूर्ण

अटल bool jz4780_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	काष्ठा jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	काष्ठा jz4780_dma_filter_data *data = param;


	अगर (data->channel > -1) अणु
		अगर (data->channel != jzchan->id)
			वापस false;
	पूर्ण अन्यथा अगर (jzdma->chan_reserved & BIT(jzchan->id)) अणु
		वापस false;
	पूर्ण

	jzchan->transfer_type = data->transfer_type;

	वापस true;
पूर्ण

अटल काष्ठा dma_chan *jz4780_of_dma_xlate(काष्ठा of_phandle_args *dma_spec,
	काष्ठा of_dma *ofdma)
अणु
	काष्ठा jz4780_dma_dev *jzdma = ofdma->of_dma_data;
	dma_cap_mask_t mask = jzdma->dma_device.cap_mask;
	काष्ठा jz4780_dma_filter_data data;

	अगर (dma_spec->args_count != 2)
		वापस शून्य;

	data.transfer_type = dma_spec->args[0];
	data.channel = dma_spec->args[1];

	अगर (data.channel > -1) अणु
		अगर (data.channel >= jzdma->soc_data->nb_channels) अणु
			dev_err(jzdma->dma_device.dev,
				"device requested non-existent channel %u\n",
				data.channel);
			वापस शून्य;
		पूर्ण

		/* Can only select a channel marked as reserved. */
		अगर (!(jzdma->chan_reserved & BIT(data.channel))) अणु
			dev_err(jzdma->dma_device.dev,
				"device requested unreserved channel %u\n",
				data.channel);
			वापस शून्य;
		पूर्ण

		jzdma->chan[data.channel].transfer_type = data.transfer_type;

		वापस dma_get_slave_channel(
			&jzdma->chan[data.channel].vchan.chan);
	पूर्ण अन्यथा अणु
		वापस __dma_request_channel(&mask, jz4780_dma_filter_fn, &data,
					     ofdma->of_node);
	पूर्ण
पूर्ण

अटल पूर्णांक jz4780_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा jz4780_dma_soc_data *soc_data;
	काष्ठा jz4780_dma_dev *jzdma;
	काष्ठा jz4780_dma_chan *jzchan;
	काष्ठा dma_device *dd;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	अगर (!dev->of_node) अणु
		dev_err(dev, "This driver must be probed from devicetree\n");
		वापस -EINVAL;
	पूर्ण

	soc_data = device_get_match_data(dev);
	अगर (!soc_data)
		वापस -EINVAL;

	jzdma = devm_kzalloc(dev, काष्ठा_size(jzdma, chan,
			     soc_data->nb_channels), GFP_KERNEL);
	अगर (!jzdma)
		वापस -ENOMEM;

	jzdma->soc_data = soc_data;
	platक्रमm_set_drvdata(pdev, jzdma);

	jzdma->chn_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(jzdma->chn_base))
		वापस PTR_ERR(jzdma->chn_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		jzdma->ctrl_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(jzdma->ctrl_base))
			वापस PTR_ERR(jzdma->ctrl_base);
	पूर्ण अन्यथा अगर (soc_data->flags & JZ_SOC_DATA_ALLOW_LEGACY_DT) अणु
		/*
		 * On JZ4780, अगर the second memory resource was not supplied,
		 * assume we're using an old devicetree, and calculate the
		 * offset to the control रेजिस्टरs.
		 */
		jzdma->ctrl_base = jzdma->chn_base + JZ4780_DMA_CTRL_OFFSET;
	पूर्ण अन्यथा अणु
		dev_err(dev, "failed to get I/O memory\n");
		वापस -EINVAL;
	पूर्ण

	jzdma->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(jzdma->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		ret = PTR_ERR(jzdma->clk);
		वापस ret;
	पूर्ण

	clk_prepare_enable(jzdma->clk);

	/* Property is optional, अगर it करोesn't exist the value will reमुख्य 0. */
	of_property_पढ़ो_u32_index(dev->of_node, "ingenic,reserved-channels",
				   0, &jzdma->chan_reserved);

	dd = &jzdma->dma_device;

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);
	dma_cap_set(DMA_SLAVE, dd->cap_mask);
	dma_cap_set(DMA_CYCLIC, dd->cap_mask);

	dd->dev = dev;
	dd->copy_align = DMAENGINE_ALIGN_4_BYTES;
	dd->device_alloc_chan_resources = jz4780_dma_alloc_chan_resources;
	dd->device_मुक्त_chan_resources = jz4780_dma_मुक्त_chan_resources;
	dd->device_prep_slave_sg = jz4780_dma_prep_slave_sg;
	dd->device_prep_dma_cyclic = jz4780_dma_prep_dma_cyclic;
	dd->device_prep_dma_स_नकल = jz4780_dma_prep_dma_स_नकल;
	dd->device_config = jz4780_dma_config;
	dd->device_terminate_all = jz4780_dma_terminate_all;
	dd->device_synchronize = jz4780_dma_synchronize;
	dd->device_tx_status = jz4780_dma_tx_status;
	dd->device_issue_pending = jz4780_dma_issue_pending;
	dd->src_addr_widths = JZ_DMA_BUSWIDTHS;
	dd->dst_addr_widths = JZ_DMA_BUSWIDTHS;
	dd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	/*
	 * Enable DMA controller, mark all channels as not programmable.
	 * Also set the FMSC bit - it increases MSC perक्रमmance, so it makes
	 * little sense not to enable it.
	 */
	jz4780_dma_ctrl_ग_लिखोl(jzdma, JZ_DMA_REG_DMAC, JZ_DMA_DMAC_DMAE |
			       JZ_DMA_DMAC_FAIC | JZ_DMA_DMAC_FMSC);

	अगर (soc_data->flags & JZ_SOC_DATA_PROGRAMMABLE_DMA)
		jz4780_dma_ctrl_ग_लिखोl(jzdma, JZ_DMA_REG_DMACP, 0);

	INIT_LIST_HEAD(&dd->channels);

	क्रम (i = 0; i < soc_data->nb_channels; i++) अणु
		jzchan = &jzdma->chan[i];
		jzchan->id = i;

		vchan_init(&jzchan->vchan, dd);
		jzchan->vchan.desc_मुक्त = jz4780_dma_desc_मुक्त;
	पूर्ण

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_disable_clk;

	jzdma->irq = ret;

	ret = request_irq(jzdma->irq, jz4780_dma_irq_handler, 0, dev_name(dev),
			  jzdma);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ %u!\n", jzdma->irq);
		जाओ err_disable_clk;
	पूर्ण

	ret = dmaenginem_async_device_रेजिस्टर(dd);
	अगर (ret) अणु
		dev_err(dev, "failed to register device\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Register with OF DMA helpers. */
	ret = of_dma_controller_रेजिस्टर(dev->of_node, jz4780_of_dma_xlate,
					 jzdma);
	अगर (ret) अणु
		dev_err(dev, "failed to register OF DMA controller\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	dev_info(dev, "JZ4780 DMA controller initialised\n");
	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(jzdma->irq, jzdma);

err_disable_clk:
	clk_disable_unprepare(jzdma->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक jz4780_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jz4780_dma_dev *jzdma = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	of_dma_controller_मुक्त(pdev->dev.of_node);

	clk_disable_unprepare(jzdma->clk);
	मुक्त_irq(jzdma->irq, jzdma);

	क्रम (i = 0; i < jzdma->soc_data->nb_channels; i++)
		tasklet_समाप्त(&jzdma->chan[i].vchan.task);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा jz4780_dma_soc_data jz4740_dma_soc_data = अणु
	.nb_channels = 6,
	.transfer_ord_max = 5,
	.flags = JZ_SOC_DATA_BREAK_LINKS,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data jz4725b_dma_soc_data = अणु
	.nb_channels = 6,
	.transfer_ord_max = 5,
	.flags = JZ_SOC_DATA_PER_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC |
		 JZ_SOC_DATA_BREAK_LINKS,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data jz4760_dma_soc_data = अणु
	.nb_channels = 5,
	.transfer_ord_max = 6,
	.flags = JZ_SOC_DATA_PER_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data jz4760b_dma_soc_data = अणु
	.nb_channels = 5,
	.transfer_ord_max = 6,
	.flags = JZ_SOC_DATA_PER_CHAN_PM,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data jz4770_dma_soc_data = अणु
	.nb_channels = 6,
	.transfer_ord_max = 6,
	.flags = JZ_SOC_DATA_PER_CHAN_PM,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data jz4780_dma_soc_data = अणु
	.nb_channels = 32,
	.transfer_ord_max = 7,
	.flags = JZ_SOC_DATA_ALLOW_LEGACY_DT | JZ_SOC_DATA_PROGRAMMABLE_DMA,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data x1000_dma_soc_data = अणु
	.nb_channels = 8,
	.transfer_ord_max = 7,
	.flags = JZ_SOC_DATA_PROGRAMMABLE_DMA,
पूर्ण;

अटल स्थिर काष्ठा jz4780_dma_soc_data x1830_dma_soc_data = अणु
	.nb_channels = 32,
	.transfer_ord_max = 7,
	.flags = JZ_SOC_DATA_PROGRAMMABLE_DMA,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4780_dma_dt_match[] = अणु
	अणु .compatible = "ingenic,jz4740-dma", .data = &jz4740_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,jz4725b-dma", .data = &jz4725b_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,jz4760-dma", .data = &jz4760_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,jz4760b-dma", .data = &jz4760b_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,jz4770-dma", .data = &jz4770_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,jz4780-dma", .data = &jz4780_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,x1000-dma", .data = &x1000_dma_soc_data पूर्ण,
	अणु .compatible = "ingenic,x1830-dma", .data = &x1830_dma_soc_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4780_dma_dt_match);

अटल काष्ठा platक्रमm_driver jz4780_dma_driver = अणु
	.probe		= jz4780_dma_probe,
	.हटाओ		= jz4780_dma_हटाओ,
	.driver	= अणु
		.name	= "jz4780-dma",
		.of_match_table = jz4780_dma_dt_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init jz4780_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&jz4780_dma_driver);
पूर्ण
subsys_initcall(jz4780_dma_init);

अटल व्योम __निकास jz4780_dma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&jz4780_dma_driver);
पूर्ण
module_निकास(jz4780_dma_निकास);

MODULE_AUTHOR("Alex Smith <alex@alex-smith.me.uk>");
MODULE_DESCRIPTION("Ingenic JZ4780 DMA controller driver");
MODULE_LICENSE("GPL");
