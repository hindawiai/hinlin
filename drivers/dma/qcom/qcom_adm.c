<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

/* ADM रेजिस्टरs - calculated from channel number and security करोमुख्य */
#घोषणा ADM_CHAN_MULTI			0x4
#घोषणा ADM_CI_MULTI			0x4
#घोषणा ADM_CRCI_MULTI			0x4
#घोषणा ADM_EE_MULTI			0x800
#घोषणा ADM_CHAN_OFFS(chan)		(ADM_CHAN_MULTI * (chan))
#घोषणा ADM_EE_OFFS(ee)			(ADM_EE_MULTI * (ee))
#घोषणा ADM_CHAN_EE_OFFS(chan, ee)	(ADM_CHAN_OFFS(chan) + ADM_EE_OFFS(ee))
#घोषणा ADM_CHAN_OFFS(chan)		(ADM_CHAN_MULTI * (chan))
#घोषणा ADM_CI_OFFS(ci)			(ADM_CHAN_OFF(ci))
#घोषणा ADM_CH_CMD_PTR(chan, ee)	(ADM_CHAN_EE_OFFS(chan, ee))
#घोषणा ADM_CH_RSLT(chan, ee)		(0x40 + ADM_CHAN_EE_OFFS(chan, ee))
#घोषणा ADM_CH_FLUSH_STATE0(chan, ee)	(0x80 + ADM_CHAN_EE_OFFS(chan, ee))
#घोषणा ADM_CH_STATUS_SD(chan, ee)	(0x200 + ADM_CHAN_EE_OFFS(chan, ee))
#घोषणा ADM_CH_CONF(chan)		(0x240 + ADM_CHAN_OFFS(chan))
#घोषणा ADM_CH_RSLT_CONF(chan, ee)	(0x300 + ADM_CHAN_EE_OFFS(chan, ee))
#घोषणा ADM_SEC_DOMAIN_IRQ_STATUS(ee)	(0x380 + ADM_EE_OFFS(ee))
#घोषणा ADM_CI_CONF(ci)			(0x390 + (ci) * ADM_CI_MULTI)
#घोषणा ADM_GP_CTL			0x3d8
#घोषणा ADM_CRCI_CTL(crci, ee)		(0x400 + (crci) * ADM_CRCI_MULTI + \
						ADM_EE_OFFS(ee))

/* channel status */
#घोषणा ADM_CH_STATUS_VALID		BIT(1)

/* channel result */
#घोषणा ADM_CH_RSLT_VALID		BIT(31)
#घोषणा ADM_CH_RSLT_ERR			BIT(3)
#घोषणा ADM_CH_RSLT_FLUSH		BIT(2)
#घोषणा ADM_CH_RSLT_TPD			BIT(1)

/* channel conf */
#घोषणा ADM_CH_CONF_SHADOW_EN		BIT(12)
#घोषणा ADM_CH_CONF_MPU_DISABLE		BIT(11)
#घोषणा ADM_CH_CONF_PERM_MPU_CONF	BIT(9)
#घोषणा ADM_CH_CONF_FORCE_RSLT_EN	BIT(7)
#घोषणा ADM_CH_CONF_SEC_DOMAIN(ee)	((((ee) & 0x3) << 4) | (((ee) & 0x4) << 11))

/* channel result conf */
#घोषणा ADM_CH_RSLT_CONF_FLUSH_EN	BIT(1)
#घोषणा ADM_CH_RSLT_CONF_IRQ_EN		BIT(0)

/* CRCI CTL */
#घोषणा ADM_CRCI_CTL_MUX_SEL		BIT(18)
#घोषणा ADM_CRCI_CTL_RST		BIT(17)

/* CI configuration */
#घोषणा ADM_CI_RANGE_END(x)		((x) << 24)
#घोषणा ADM_CI_RANGE_START(x)		((x) << 16)
#घोषणा ADM_CI_BURST_4_WORDS		BIT(2)
#घोषणा ADM_CI_BURST_8_WORDS		BIT(3)

/* GP CTL */
#घोषणा ADM_GP_CTL_LP_EN		BIT(12)
#घोषणा ADM_GP_CTL_LP_CNT(x)		((x) << 8)

/* Command poपूर्णांकer list entry */
#घोषणा ADM_CPLE_LP			BIT(31)
#घोषणा ADM_CPLE_CMD_PTR_LIST		BIT(29)

/* Command list entry */
#घोषणा ADM_CMD_LC			BIT(31)
#घोषणा ADM_CMD_DST_CRCI(n)		(((n) & 0xf) << 7)
#घोषणा ADM_CMD_SRC_CRCI(n)		(((n) & 0xf) << 3)

#घोषणा ADM_CMD_TYPE_SINGLE		0x0
#घोषणा ADM_CMD_TYPE_BOX		0x3

#घोषणा ADM_CRCI_MUX_SEL		BIT(4)
#घोषणा ADM_DESC_ALIGN			8
#घोषणा ADM_MAX_XFER			(SZ_64K - 1)
#घोषणा ADM_MAX_ROWS			(SZ_64K - 1)
#घोषणा ADM_MAX_CHANNELS		16

काष्ठा adm_desc_hw_box अणु
	u32 cmd;
	u32 src_addr;
	u32 dst_addr;
	u32 row_len;
	u32 num_rows;
	u32 row_offset;
पूर्ण;

काष्ठा adm_desc_hw_single अणु
	u32 cmd;
	u32 src_addr;
	u32 dst_addr;
	u32 len;
पूर्ण;

काष्ठा adm_async_desc अणु
	काष्ठा virt_dma_desc vd;
	काष्ठा adm_device *adev;

	माप_प्रकार length;
	क्रमागत dma_transfer_direction dir;
	dma_addr_t dma_addr;
	माप_प्रकार dma_len;

	व्योम *cpl;
	dma_addr_t cp_addr;
	u32 crci;
	u32 mux;
	u32 blk_size;
पूर्ण;

काष्ठा adm_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा adm_device *adev;

	/* parsed from DT */
	u32 id;			/* channel id */

	काष्ठा adm_async_desc *curr_txd;
	काष्ठा dma_slave_config slave;
	काष्ठा list_head node;

	पूर्णांक error;
	पूर्णांक initialized;
पूर्ण;

अटल अंतरभूत काष्ठा adm_chan *to_adm_chan(काष्ठा dma_chan *common)
अणु
	वापस container_of(common, काष्ठा adm_chan, vc.chan);
पूर्ण

काष्ठा adm_device अणु
	व्योम __iomem *regs;
	काष्ठा device *dev;
	काष्ठा dma_device common;
	काष्ठा device_dma_parameters dma_parms;
	काष्ठा adm_chan *channels;

	u32 ee;

	काष्ठा clk *core_clk;
	काष्ठा clk *अगरace_clk;

	काष्ठा reset_control *clk_reset;
	काष्ठा reset_control *c0_reset;
	काष्ठा reset_control *c1_reset;
	काष्ठा reset_control *c2_reset;
	पूर्णांक irq;
पूर्ण;

/**
 * adm_मुक्त_chan - Frees dma resources associated with the specअगरic channel
 *
 * @chan: dma channel
 *
 * Free all allocated descriptors associated with this channel
 */
अटल व्योम adm_मुक्त_chan(काष्ठा dma_chan *chan)
अणु
	/* मुक्त all queued descriptors */
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

/**
 * adm_get_blksize - Get block size from burst value
 *
 * @burst: Burst size of transaction
 */
अटल पूर्णांक adm_get_blksize(अचिन्हित पूर्णांक burst)
अणु
	पूर्णांक ret;

	चयन (burst) अणु
	हाल 16:
	हाल 32:
	हाल 64:
	हाल 128:
		ret = ffs(burst >> 4) - 1;
		अवरोध;
	हाल 192:
		ret = 4;
		अवरोध;
	हाल 256:
		ret = 5;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * adm_process_fc_descriptors - Process descriptors क्रम flow controlled xfers
 *
 * @achan: ADM channel
 * @desc: Descriptor memory poपूर्णांकer
 * @sg: Scatterlist entry
 * @crci: CRCI value
 * @burst: Burst size of transaction
 * @direction: DMA transfer direction
 */
अटल व्योम *adm_process_fc_descriptors(काष्ठा adm_chan *achan, व्योम *desc,
					काष्ठा scatterlist *sg, u32 crci,
					u32 burst,
					क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा adm_desc_hw_box *box_desc = शून्य;
	काष्ठा adm_desc_hw_single *single_desc;
	u32 reमुख्यder = sg_dma_len(sg);
	u32 rows, row_offset, crci_cmd;
	u32 mem_addr = sg_dma_address(sg);
	u32 *incr_addr = &mem_addr;
	u32 *src, *dst;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		crci_cmd = ADM_CMD_SRC_CRCI(crci);
		row_offset = burst;
		src = &achan->slave.src_addr;
		dst = &mem_addr;
	पूर्ण अन्यथा अणु
		crci_cmd = ADM_CMD_DST_CRCI(crci);
		row_offset = burst << 16;
		src = &mem_addr;
		dst = &achan->slave.dst_addr;
	पूर्ण

	जबतक (reमुख्यder >= burst) अणु
		box_desc = desc;
		box_desc->cmd = ADM_CMD_TYPE_BOX | crci_cmd;
		box_desc->row_offset = row_offset;
		box_desc->src_addr = *src;
		box_desc->dst_addr = *dst;

		rows = reमुख्यder / burst;
		rows = min_t(u32, rows, ADM_MAX_ROWS);
		box_desc->num_rows = rows << 16 | rows;
		box_desc->row_len = burst << 16 | burst;

		*incr_addr += burst * rows;
		reमुख्यder -= burst * rows;
		desc += माप(*box_desc);
	पूर्ण

	/* अगर leftover bytes, करो one single descriptor */
	अगर (reमुख्यder) अणु
		single_desc = desc;
		single_desc->cmd = ADM_CMD_TYPE_SINGLE | crci_cmd;
		single_desc->len = reमुख्यder;
		single_desc->src_addr = *src;
		single_desc->dst_addr = *dst;
		desc += माप(*single_desc);

		अगर (sg_is_last(sg))
			single_desc->cmd |= ADM_CMD_LC;
	पूर्ण अन्यथा अणु
		अगर (box_desc && sg_is_last(sg))
			box_desc->cmd |= ADM_CMD_LC;
	पूर्ण

	वापस desc;
पूर्ण

/**
 * adm_process_non_fc_descriptors - Process descriptors क्रम non-fc xfers
 *
 * @achan: ADM channel
 * @desc: Descriptor memory poपूर्णांकer
 * @sg: Scatterlist entry
 * @direction: DMA transfer direction
 */
अटल व्योम *adm_process_non_fc_descriptors(काष्ठा adm_chan *achan, व्योम *desc,
					    काष्ठा scatterlist *sg,
					    क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा adm_desc_hw_single *single_desc;
	u32 reमुख्यder = sg_dma_len(sg);
	u32 mem_addr = sg_dma_address(sg);
	u32 *incr_addr = &mem_addr;
	u32 *src, *dst;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		src = &achan->slave.src_addr;
		dst = &mem_addr;
	पूर्ण अन्यथा अणु
		src = &mem_addr;
		dst = &achan->slave.dst_addr;
	पूर्ण

	करो अणु
		single_desc = desc;
		single_desc->cmd = ADM_CMD_TYPE_SINGLE;
		single_desc->src_addr = *src;
		single_desc->dst_addr = *dst;
		single_desc->len = (reमुख्यder > ADM_MAX_XFER) ?
				ADM_MAX_XFER : reमुख्यder;

		reमुख्यder -= single_desc->len;
		*incr_addr += single_desc->len;
		desc += माप(*single_desc);
	पूर्ण जबतक (reमुख्यder);

	/* set last command अगर this is the end of the whole transaction */
	अगर (sg_is_last(sg))
		single_desc->cmd |= ADM_CMD_LC;

	वापस desc;
पूर्ण

/**
 * adm_prep_slave_sg - Prep slave sg transaction
 *
 * @chan: dma channel
 * @sgl: scatter gather list
 * @sg_len: length of sg
 * @direction: DMA transfer direction
 * @flags: DMA flags
 * @context: transfer context (unused)
 */
अटल काष्ठा dma_async_tx_descriptor *adm_prep_slave_sg(काष्ठा dma_chan *chan,
							 काष्ठा scatterlist *sgl,
							 अचिन्हित पूर्णांक sg_len,
							 क्रमागत dma_transfer_direction direction,
							 अचिन्हित दीर्घ flags,
							 व्योम *context)
अणु
	काष्ठा adm_chan *achan = to_adm_chan(chan);
	काष्ठा adm_device *adev = achan->adev;
	काष्ठा adm_async_desc *async_desc;
	काष्ठा scatterlist *sg;
	dma_addr_t cple_addr;
	u32 i, burst;
	u32 single_count = 0, box_count = 0, crci = 0;
	व्योम *desc;
	u32 *cple;
	पूर्णांक blk_size = 0;

	अगर (!is_slave_direction(direction)) अणु
		dev_err(adev->dev, "invalid dma direction\n");
		वापस शून्य;
	पूर्ण

	/*
	 * get burst value from slave configuration
	 */
	burst = (direction == DMA_MEM_TO_DEV) ?
		achan->slave.dst_maxburst :
		achan->slave.src_maxburst;

	/* अगर using flow control, validate burst and crci values */
	अगर (achan->slave.device_fc) अणु
		blk_size = adm_get_blksize(burst);
		अगर (blk_size < 0) अणु
			dev_err(adev->dev, "invalid burst value: %d\n",
				burst);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		crci = achan->slave.slave_id & 0xf;
		अगर (!crci || achan->slave.slave_id > 0x1f) अणु
			dev_err(adev->dev, "invalid crci value\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	/* iterate through sgs and compute allocation size of काष्ठाures */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		अगर (achan->slave.device_fc) अणु
			box_count += DIV_ROUND_UP(sg_dma_len(sg) / burst,
						  ADM_MAX_ROWS);
			अगर (sg_dma_len(sg) % burst)
				single_count++;
		पूर्ण अन्यथा अणु
			single_count += DIV_ROUND_UP(sg_dma_len(sg),
						     ADM_MAX_XFER);
		पूर्ण
	पूर्ण

	async_desc = kzalloc(माप(*async_desc), GFP_NOWAIT);
	अगर (!async_desc)
		वापस ERR_PTR(-ENOMEM);

	अगर (crci)
		async_desc->mux = achan->slave.slave_id & ADM_CRCI_MUX_SEL ?
					ADM_CRCI_CTL_MUX_SEL : 0;
	async_desc->crci = crci;
	async_desc->blk_size = blk_size;
	async_desc->dma_len = single_count * माप(काष्ठा adm_desc_hw_single) +
				box_count * माप(काष्ठा adm_desc_hw_box) +
				माप(*cple) + 2 * ADM_DESC_ALIGN;

	async_desc->cpl = kzalloc(async_desc->dma_len, GFP_NOWAIT);
	अगर (!async_desc->cpl)
		जाओ मुक्त;

	async_desc->adev = adev;

	/* both command list entry and descriptors must be 8 byte aligned */
	cple = PTR_ALIGN(async_desc->cpl, ADM_DESC_ALIGN);
	desc = PTR_ALIGN(cple + 1, ADM_DESC_ALIGN);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		async_desc->length += sg_dma_len(sg);

		अगर (achan->slave.device_fc)
			desc = adm_process_fc_descriptors(achan, desc, sg, crci,
							  burst, direction);
		अन्यथा
			desc = adm_process_non_fc_descriptors(achan, desc, sg,
							      direction);
	पूर्ण

	async_desc->dma_addr = dma_map_single(adev->dev, async_desc->cpl,
					      async_desc->dma_len,
					      DMA_TO_DEVICE);
	अगर (dma_mapping_error(adev->dev, async_desc->dma_addr))
		जाओ मुक्त;

	cple_addr = async_desc->dma_addr + ((व्योम *)cple - async_desc->cpl);

	/* init cmd list */
	dma_sync_single_क्रम_cpu(adev->dev, cple_addr, माप(*cple),
				DMA_TO_DEVICE);
	*cple = ADM_CPLE_LP;
	*cple |= (async_desc->dma_addr + ADM_DESC_ALIGN) >> 3;
	dma_sync_single_क्रम_device(adev->dev, cple_addr, माप(*cple),
				   DMA_TO_DEVICE);

	वापस vchan_tx_prep(&achan->vc, &async_desc->vd, flags);

मुक्त:
	kमुक्त(async_desc);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * adm_terminate_all - terminate all transactions on a channel
 * @chan: dma channel
 *
 * Dequeues and मुक्तs all transactions, पातs current transaction
 * No callbacks are करोne
 *
 */
अटल पूर्णांक adm_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा adm_chan *achan = to_adm_chan(chan);
	काष्ठा adm_device *adev = achan->adev;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&achan->vc.lock, flags);
	vchan_get_all_descriptors(&achan->vc, &head);

	/* send flush command to terminate current transaction */
	ग_लिखोl_relaxed(0x0,
		       adev->regs + ADM_CH_FLUSH_STATE0(achan->id, adev->ee));

	spin_unlock_irqrestore(&achan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&achan->vc, &head);

	वापस 0;
पूर्ण

अटल पूर्णांक adm_slave_config(काष्ठा dma_chan *chan, काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा adm_chan *achan = to_adm_chan(chan);
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&achan->vc.lock, flag);
	स_नकल(&achan->slave, cfg, माप(काष्ठा dma_slave_config));
	spin_unlock_irqrestore(&achan->vc.lock, flag);

	वापस 0;
पूर्ण

/**
 * adm_start_dma - start next transaction
 * @achan: ADM dma channel
 */
अटल व्योम adm_start_dma(काष्ठा adm_chan *achan)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&achan->vc);
	काष्ठा adm_device *adev = achan->adev;
	काष्ठा adm_async_desc *async_desc;

	lockdep_निश्चित_held(&achan->vc.lock);

	अगर (!vd)
		वापस;

	list_del(&vd->node);

	/* ग_लिखो next command list out to the CMD FIFO */
	async_desc = container_of(vd, काष्ठा adm_async_desc, vd);
	achan->curr_txd = async_desc;

	/* reset channel error */
	achan->error = 0;

	अगर (!achan->initialized) अणु
		/* enable पूर्णांकerrupts */
		ग_लिखोl(ADM_CH_CONF_SHADOW_EN |
		       ADM_CH_CONF_PERM_MPU_CONF |
		       ADM_CH_CONF_MPU_DISABLE |
		       ADM_CH_CONF_SEC_DOMAIN(adev->ee),
		       adev->regs + ADM_CH_CONF(achan->id));

		ग_लिखोl(ADM_CH_RSLT_CONF_IRQ_EN | ADM_CH_RSLT_CONF_FLUSH_EN,
		       adev->regs + ADM_CH_RSLT_CONF(achan->id, adev->ee));

		achan->initialized = 1;
	पूर्ण

	/* set the crci block size अगर this transaction requires CRCI */
	अगर (async_desc->crci) अणु
		ग_लिखोl(async_desc->mux | async_desc->blk_size,
		       adev->regs + ADM_CRCI_CTL(async_desc->crci, adev->ee));
	पूर्ण

	/* make sure IRQ enable करोesn't get reordered */
	wmb();

	/* ग_लिखो next command list out to the CMD FIFO */
	ग_लिखोl(ALIGN(async_desc->dma_addr, ADM_DESC_ALIGN) >> 3,
	       adev->regs + ADM_CH_CMD_PTR(achan->id, adev->ee));
पूर्ण

/**
 * adm_dma_irq - irq handler क्रम ADM controller
 * @irq: IRQ of पूर्णांकerrupt
 * @data: callback data
 *
 * IRQ handler क्रम the bam controller
 */
अटल irqवापस_t adm_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adm_device *adev = data;
	u32 srcs, i;
	काष्ठा adm_async_desc *async_desc;
	अचिन्हित दीर्घ flags;

	srcs = पढ़ोl_relaxed(adev->regs +
			ADM_SEC_DOMAIN_IRQ_STATUS(adev->ee));

	क्रम (i = 0; i < ADM_MAX_CHANNELS; i++) अणु
		काष्ठा adm_chan *achan = &adev->channels[i];
		u32 status, result;

		अगर (srcs & BIT(i)) अणु
			status = पढ़ोl_relaxed(adev->regs +
					       ADM_CH_STATUS_SD(i, adev->ee));

			/* अगर no result present, skip */
			अगर (!(status & ADM_CH_STATUS_VALID))
				जारी;

			result = पढ़ोl_relaxed(adev->regs +
				ADM_CH_RSLT(i, adev->ee));

			/* no valid results, skip */
			अगर (!(result & ADM_CH_RSLT_VALID))
				जारी;

			/* flag error अगर transaction was flushed or failed */
			अगर (result & (ADM_CH_RSLT_ERR | ADM_CH_RSLT_FLUSH))
				achan->error = 1;

			spin_lock_irqsave(&achan->vc.lock, flags);
			async_desc = achan->curr_txd;

			achan->curr_txd = शून्य;

			अगर (async_desc) अणु
				vchan_cookie_complete(&async_desc->vd);

				/* kick off next DMA */
				adm_start_dma(achan);
			पूर्ण

			spin_unlock_irqrestore(&achan->vc.lock, flags);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * adm_tx_status - वापसs status of transaction
 * @chan: dma channel
 * @cookie: transaction cookie
 * @txstate: DMA transaction state
 *
 * Return status of dma transaction
 */
अटल क्रमागत dma_status adm_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
				     काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा adm_chan *achan = to_adm_chan(chan);
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	माप_प्रकार residue = 0;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&achan->vc.lock, flags);

	vd = vchan_find_desc(&achan->vc, cookie);
	अगर (vd)
		residue = container_of(vd, काष्ठा adm_async_desc, vd)->length;

	spin_unlock_irqrestore(&achan->vc.lock, flags);

	/*
	 * residue is either the full length अगर it is in the issued list, or 0
	 * अगर it is in progress.  We have no reliable way of determining
	 * anything inbetween
	 */
	dma_set_residue(txstate, residue);

	अगर (achan->error)
		वापस DMA_ERROR;

	वापस ret;
पूर्ण

/**
 * adm_issue_pending - starts pending transactions
 * @chan: dma channel
 *
 * Issues all pending transactions and starts DMA
 */
अटल व्योम adm_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा adm_chan *achan = to_adm_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&achan->vc.lock, flags);

	अगर (vchan_issue_pending(&achan->vc) && !achan->curr_txd)
		adm_start_dma(achan);
	spin_unlock_irqrestore(&achan->vc.lock, flags);
पूर्ण

/**
 * adm_dma_मुक्त_desc - मुक्त descriptor memory
 * @vd: भव descriptor
 *
 */
अटल व्योम adm_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा adm_async_desc *async_desc = container_of(vd,
			काष्ठा adm_async_desc, vd);

	dma_unmap_single(async_desc->adev->dev, async_desc->dma_addr,
			 async_desc->dma_len, DMA_TO_DEVICE);
	kमुक्त(async_desc->cpl);
	kमुक्त(async_desc);
पूर्ण

अटल व्योम adm_channel_init(काष्ठा adm_device *adev, काष्ठा adm_chan *achan,
			     u32 index)
अणु
	achan->id = index;
	achan->adev = adev;

	vchan_init(&achan->vc, &adev->common);
	achan->vc.desc_मुक्त = adm_dma_मुक्त_desc;
पूर्ण

अटल पूर्णांक adm_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adm_device *adev;
	पूर्णांक ret;
	u32 i;

	adev = devm_kzalloc(&pdev->dev, माप(*adev), GFP_KERNEL);
	अगर (!adev)
		वापस -ENOMEM;

	adev->dev = &pdev->dev;

	adev->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adev->regs))
		वापस PTR_ERR(adev->regs);

	adev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (adev->irq < 0)
		वापस adev->irq;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "qcom,ee", &adev->ee);
	अगर (ret) अणु
		dev_err(adev->dev, "Execution environment unspecified\n");
		वापस ret;
	पूर्ण

	adev->core_clk = devm_clk_get(adev->dev, "core");
	अगर (IS_ERR(adev->core_clk))
		वापस PTR_ERR(adev->core_clk);

	adev->अगरace_clk = devm_clk_get(adev->dev, "iface");
	अगर (IS_ERR(adev->अगरace_clk))
		वापस PTR_ERR(adev->अगरace_clk);

	adev->clk_reset = devm_reset_control_get_exclusive(&pdev->dev, "clk");
	अगर (IS_ERR(adev->clk_reset)) अणु
		dev_err(adev->dev, "failed to get ADM0 reset\n");
		वापस PTR_ERR(adev->clk_reset);
	पूर्ण

	adev->c0_reset = devm_reset_control_get_exclusive(&pdev->dev, "c0");
	अगर (IS_ERR(adev->c0_reset)) अणु
		dev_err(adev->dev, "failed to get ADM0 C0 reset\n");
		वापस PTR_ERR(adev->c0_reset);
	पूर्ण

	adev->c1_reset = devm_reset_control_get_exclusive(&pdev->dev, "c1");
	अगर (IS_ERR(adev->c1_reset)) अणु
		dev_err(adev->dev, "failed to get ADM0 C1 reset\n");
		वापस PTR_ERR(adev->c1_reset);
	पूर्ण

	adev->c2_reset = devm_reset_control_get_exclusive(&pdev->dev, "c2");
	अगर (IS_ERR(adev->c2_reset)) अणु
		dev_err(adev->dev, "failed to get ADM0 C2 reset\n");
		वापस PTR_ERR(adev->c2_reset);
	पूर्ण

	ret = clk_prepare_enable(adev->core_clk);
	अगर (ret) अणु
		dev_err(adev->dev, "failed to prepare/enable core clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(adev->अगरace_clk);
	अगर (ret) अणु
		dev_err(adev->dev, "failed to prepare/enable iface clock\n");
		जाओ err_disable_core_clk;
	पूर्ण

	reset_control_निश्चित(adev->clk_reset);
	reset_control_निश्चित(adev->c0_reset);
	reset_control_निश्चित(adev->c1_reset);
	reset_control_निश्चित(adev->c2_reset);

	udelay(2);

	reset_control_deनिश्चित(adev->clk_reset);
	reset_control_deनिश्चित(adev->c0_reset);
	reset_control_deनिश्चित(adev->c1_reset);
	reset_control_deनिश्चित(adev->c2_reset);

	adev->channels = devm_kसुस्मृति(adev->dev, ADM_MAX_CHANNELS,
				      माप(*adev->channels), GFP_KERNEL);

	अगर (!adev->channels) अणु
		ret = -ENOMEM;
		जाओ err_disable_clks;
	पूर्ण

	/* allocate and initialize channels */
	INIT_LIST_HEAD(&adev->common.channels);

	क्रम (i = 0; i < ADM_MAX_CHANNELS; i++)
		adm_channel_init(adev, &adev->channels[i], i);

	/* reset CRCIs */
	क्रम (i = 0; i < 16; i++)
		ग_लिखोl(ADM_CRCI_CTL_RST, adev->regs +
			ADM_CRCI_CTL(i, adev->ee));

	/* configure client पूर्णांकerfaces */
	ग_लिखोl(ADM_CI_RANGE_START(0x40) | ADM_CI_RANGE_END(0xb0) |
	       ADM_CI_BURST_8_WORDS, adev->regs + ADM_CI_CONF(0));
	ग_लिखोl(ADM_CI_RANGE_START(0x2a) | ADM_CI_RANGE_END(0x2c) |
	       ADM_CI_BURST_8_WORDS, adev->regs + ADM_CI_CONF(1));
	ग_लिखोl(ADM_CI_RANGE_START(0x12) | ADM_CI_RANGE_END(0x28) |
	       ADM_CI_BURST_8_WORDS, adev->regs + ADM_CI_CONF(2));
	ग_लिखोl(ADM_GP_CTL_LP_EN | ADM_GP_CTL_LP_CNT(0xf),
	       adev->regs + ADM_GP_CTL);

	ret = devm_request_irq(adev->dev, adev->irq, adm_dma_irq,
			       0, "adm_dma", adev);
	अगर (ret)
		जाओ err_disable_clks;

	platक्रमm_set_drvdata(pdev, adev);

	adev->common.dev = adev->dev;
	adev->common.dev->dma_parms = &adev->dma_parms;

	/* set capabilities */
	dma_cap_zero(adev->common.cap_mask);
	dma_cap_set(DMA_SLAVE, adev->common.cap_mask);
	dma_cap_set(DMA_PRIVATE, adev->common.cap_mask);

	/* initialize dmaengine apis */
	adev->common.directions = BIT(DMA_DEV_TO_MEM | DMA_MEM_TO_DEV);
	adev->common.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	adev->common.src_addr_widths = DMA_SLAVE_BUSWIDTH_4_BYTES;
	adev->common.dst_addr_widths = DMA_SLAVE_BUSWIDTH_4_BYTES;
	adev->common.device_मुक्त_chan_resources = adm_मुक्त_chan;
	adev->common.device_prep_slave_sg = adm_prep_slave_sg;
	adev->common.device_issue_pending = adm_issue_pending;
	adev->common.device_tx_status = adm_tx_status;
	adev->common.device_terminate_all = adm_terminate_all;
	adev->common.device_config = adm_slave_config;

	ret = dma_async_device_रेजिस्टर(&adev->common);
	अगर (ret) अणु
		dev_err(adev->dev, "failed to register dma async device\n");
		जाओ err_disable_clks;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 of_dma_xlate_by_chan_id,
					 &adev->common);
	अगर (ret)
		जाओ err_unरेजिस्टर_dma;

	वापस 0;

err_unरेजिस्टर_dma:
	dma_async_device_unरेजिस्टर(&adev->common);
err_disable_clks:
	clk_disable_unprepare(adev->अगरace_clk);
err_disable_core_clk:
	clk_disable_unprepare(adev->core_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक adm_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adm_device *adev = platक्रमm_get_drvdata(pdev);
	काष्ठा adm_chan *achan;
	u32 i;

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&adev->common);

	क्रम (i = 0; i < ADM_MAX_CHANNELS; i++) अणु
		achan = &adev->channels[i];

		/* mask IRQs क्रम this channel/EE pair */
		ग_लिखोl(0, adev->regs + ADM_CH_RSLT_CONF(achan->id, adev->ee));

		tasklet_समाप्त(&adev->channels[i].vc.task);
		adm_terminate_all(&adev->channels[i].vc.chan);
	पूर्ण

	devm_मुक्त_irq(adev->dev, adev->irq, adev);

	clk_disable_unprepare(adev->core_clk);
	clk_disable_unprepare(adev->अगरace_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adm_of_match[] = अणु
	अणु .compatible = "qcom,adm", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adm_of_match);

अटल काष्ठा platक्रमm_driver adm_dma_driver = अणु
	.probe = adm_dma_probe,
	.हटाओ = adm_dma_हटाओ,
	.driver = अणु
		.name = "adm-dma-engine",
		.of_match_table = adm_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(adm_dma_driver);

MODULE_AUTHOR("Andy Gross <agross@codeaurora.org>");
MODULE_DESCRIPTION("QCOM ADM DMA engine driver");
MODULE_LICENSE("GPL v2");
