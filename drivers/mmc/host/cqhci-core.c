<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>

#समावेश "cqhci.h"
#समावेश "cqhci-crypto.h"

#घोषणा DCMD_SLOT 31
#घोषणा NUM_SLOTS 32

काष्ठा cqhci_slot अणु
	काष्ठा mmc_request *mrq;
	अचिन्हित पूर्णांक flags;
#घोषणा CQHCI_EXTERNAL_TIMEOUT	BIT(0)
#घोषणा CQHCI_COMPLETED		BIT(1)
#घोषणा CQHCI_HOST_CRC		BIT(2)
#घोषणा CQHCI_HOST_TIMEOUT	BIT(3)
#घोषणा CQHCI_HOST_OTHER	BIT(4)
पूर्ण;

अटल अंतरभूत u8 *get_desc(काष्ठा cqhci_host *cq_host, u8 tag)
अणु
	वापस cq_host->desc_base + (tag * cq_host->slot_sz);
पूर्ण

अटल अंतरभूत u8 *get_link_desc(काष्ठा cqhci_host *cq_host, u8 tag)
अणु
	u8 *desc = get_desc(cq_host, tag);

	वापस desc + cq_host->task_desc_len;
पूर्ण

अटल अंतरभूत dma_addr_t get_trans_desc_dma(काष्ठा cqhci_host *cq_host, u8 tag)
अणु
	वापस cq_host->trans_desc_dma_base +
		(cq_host->mmc->max_segs * tag *
		 cq_host->trans_desc_len);
पूर्ण

अटल अंतरभूत u8 *get_trans_desc(काष्ठा cqhci_host *cq_host, u8 tag)
अणु
	वापस cq_host->trans_desc_base +
		(cq_host->trans_desc_len * cq_host->mmc->max_segs * tag);
पूर्ण

अटल व्योम setup_trans_desc(काष्ठा cqhci_host *cq_host, u8 tag)
अणु
	u8 *link_temp;
	dma_addr_t trans_temp;

	link_temp = get_link_desc(cq_host, tag);
	trans_temp = get_trans_desc_dma(cq_host, tag);

	स_रखो(link_temp, 0, cq_host->link_desc_len);
	अगर (cq_host->link_desc_len > 8)
		*(link_temp + 8) = 0;

	अगर (tag == DCMD_SLOT && (cq_host->mmc->caps2 & MMC_CAP2_CQE_DCMD)) अणु
		*link_temp = CQHCI_VALID(0) | CQHCI_ACT(0) | CQHCI_END(1);
		वापस;
	पूर्ण

	*link_temp = CQHCI_VALID(1) | CQHCI_ACT(0x6) | CQHCI_END(0);

	अगर (cq_host->dma64) अणु
		__le64 *data_addr = (__le64 __क्रमce *)(link_temp + 4);

		data_addr[0] = cpu_to_le64(trans_temp);
	पूर्ण अन्यथा अणु
		__le32 *data_addr = (__le32 __क्रमce *)(link_temp + 4);

		data_addr[0] = cpu_to_le32(trans_temp);
	पूर्ण
पूर्ण

अटल व्योम cqhci_set_irqs(काष्ठा cqhci_host *cq_host, u32 set)
अणु
	cqhci_ग_लिखोl(cq_host, set, CQHCI_ISTE);
	cqhci_ग_लिखोl(cq_host, set, CQHCI_ISGE);
पूर्ण

#घोषणा DRV_NAME "cqhci"

#घोषणा CQHCI_DUMP(f, x...) \
	pr_err("%s: " DRV_NAME ": " f, mmc_hostname(mmc), ## x)

अटल व्योम cqhci_dumpregs(काष्ठा cqhci_host *cq_host)
अणु
	काष्ठा mmc_host *mmc = cq_host->mmc;

	CQHCI_DUMP("============ CQHCI REGISTER DUMP ===========\n");

	CQHCI_DUMP("Caps:      0x%08x | Version:  0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_CAP),
		   cqhci_पढ़ोl(cq_host, CQHCI_VER));
	CQHCI_DUMP("Config:    0x%08x | Control:  0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_CFG),
		   cqhci_पढ़ोl(cq_host, CQHCI_CTL));
	CQHCI_DUMP("Int stat:  0x%08x | Int enab: 0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_IS),
		   cqhci_पढ़ोl(cq_host, CQHCI_ISTE));
	CQHCI_DUMP("Int sig:   0x%08x | Int Coal: 0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_ISGE),
		   cqhci_पढ़ोl(cq_host, CQHCI_IC));
	CQHCI_DUMP("TDL base:  0x%08x | TDL up32: 0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_TDLBA),
		   cqhci_पढ़ोl(cq_host, CQHCI_TDLBAU));
	CQHCI_DUMP("Doorbell:  0x%08x | TCN:      0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_TDBR),
		   cqhci_पढ़ोl(cq_host, CQHCI_TCN));
	CQHCI_DUMP("Dev queue: 0x%08x | Dev Pend: 0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_DQS),
		   cqhci_पढ़ोl(cq_host, CQHCI_DPT));
	CQHCI_DUMP("Task clr:  0x%08x | SSC1:     0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_TCLR),
		   cqhci_पढ़ोl(cq_host, CQHCI_SSC1));
	CQHCI_DUMP("SSC2:      0x%08x | DCMD rsp: 0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_SSC2),
		   cqhci_पढ़ोl(cq_host, CQHCI_CRDCT));
	CQHCI_DUMP("RED mask:  0x%08x | TERRI:    0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_RMEM),
		   cqhci_पढ़ोl(cq_host, CQHCI_TERRI));
	CQHCI_DUMP("Resp idx:  0x%08x | Resp arg: 0x%08x\n",
		   cqhci_पढ़ोl(cq_host, CQHCI_CRI),
		   cqhci_पढ़ोl(cq_host, CQHCI_CRA));

	अगर (cq_host->ops->dumpregs)
		cq_host->ops->dumpregs(mmc);
	अन्यथा
		CQHCI_DUMP(": ===========================================\n");
पूर्ण

/*
 * The allocated descriptor table क्रम task, link & transfer descritors
 * looks like:
 * |----------|
 * |task desc |  |->|----------|
 * |----------|  |  |trans desc|
 * |link desc-|->|  |----------|
 * |----------|          .
 *      .                .
 *  no. of slots      max-segs
 *      .           |----------|
 * |----------|
 * The idea here is to create the [task+trans] table and mark & poपूर्णांक the
 * link desc to the transfer desc table on a per slot basis.
 */
अटल पूर्णांक cqhci_host_alloc_tdl(काष्ठा cqhci_host *cq_host)
अणु
	पूर्णांक i = 0;

	/* task descriptor can be 64/128 bit irrespective of arch */
	अगर (cq_host->caps & CQHCI_TASK_DESC_SZ_128) अणु
		cqhci_ग_लिखोl(cq_host, cqhci_पढ़ोl(cq_host, CQHCI_CFG) |
			       CQHCI_TASK_DESC_SZ, CQHCI_CFG);
		cq_host->task_desc_len = 16;
	पूर्ण अन्यथा अणु
		cq_host->task_desc_len = 8;
	पूर्ण

	/*
	 * 96 bits length of transfer desc instead of 128 bits which means
	 * ADMA would expect next valid descriptor at the 96th bit
	 * or 128th bit
	 */
	अगर (cq_host->dma64) अणु
		अगर (cq_host->quirks & CQHCI_QUIRK_SHORT_TXFR_DESC_SZ)
			cq_host->trans_desc_len = 12;
		अन्यथा
			cq_host->trans_desc_len = 16;
		cq_host->link_desc_len = 16;
	पूर्ण अन्यथा अणु
		cq_host->trans_desc_len = 8;
		cq_host->link_desc_len = 8;
	पूर्ण

	/* total size of a slot: 1 task & 1 transfer (link) */
	cq_host->slot_sz = cq_host->task_desc_len + cq_host->link_desc_len;

	cq_host->desc_size = cq_host->slot_sz * cq_host->num_slots;

	cq_host->data_size = cq_host->trans_desc_len * cq_host->mmc->max_segs *
		cq_host->mmc->cqe_qdepth;

	pr_debug("%s: cqhci: desc_size: %zu data_sz: %zu slot-sz: %d\n",
		 mmc_hostname(cq_host->mmc), cq_host->desc_size, cq_host->data_size,
		 cq_host->slot_sz);

	/*
	 * allocate a dma-mapped chunk of memory क्रम the descriptors
	 * allocate a dma-mapped chunk of memory क्रम link descriptors
	 * setup each link-desc memory offset per slot-number to
	 * the descriptor table.
	 */
	cq_host->desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc),
						 cq_host->desc_size,
						 &cq_host->desc_dma_base,
						 GFP_KERNEL);
	अगर (!cq_host->desc_base)
		वापस -ENOMEM;

	cq_host->trans_desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc),
					      cq_host->data_size,
					      &cq_host->trans_desc_dma_base,
					      GFP_KERNEL);
	अगर (!cq_host->trans_desc_base) अणु
		dmam_मुक्त_coherent(mmc_dev(cq_host->mmc), cq_host->desc_size,
				   cq_host->desc_base,
				   cq_host->desc_dma_base);
		cq_host->desc_base = शून्य;
		cq_host->desc_dma_base = 0;
		वापस -ENOMEM;
	पूर्ण

	pr_debug("%s: cqhci: desc-base: 0x%p trans-base: 0x%p\n desc_dma 0x%llx trans_dma: 0x%llx\n",
		 mmc_hostname(cq_host->mmc), cq_host->desc_base, cq_host->trans_desc_base,
		(अचिन्हित दीर्घ दीर्घ)cq_host->desc_dma_base,
		(अचिन्हित दीर्घ दीर्घ)cq_host->trans_desc_dma_base);

	क्रम (; i < (cq_host->num_slots); i++)
		setup_trans_desc(cq_host, i);

	वापस 0;
पूर्ण

अटल व्योम __cqhci_enable(काष्ठा cqhci_host *cq_host)
अणु
	काष्ठा mmc_host *mmc = cq_host->mmc;
	u32 cqcfg;

	cqcfg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);

	/* Configuration must not be changed जबतक enabled */
	अगर (cqcfg & CQHCI_ENABLE) अणु
		cqcfg &= ~CQHCI_ENABLE;
		cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_CFG);
	पूर्ण

	cqcfg &= ~(CQHCI_DCMD | CQHCI_TASK_DESC_SZ);

	अगर (mmc->caps2 & MMC_CAP2_CQE_DCMD)
		cqcfg |= CQHCI_DCMD;

	अगर (cq_host->caps & CQHCI_TASK_DESC_SZ_128)
		cqcfg |= CQHCI_TASK_DESC_SZ;

	अगर (mmc->caps2 & MMC_CAP2_CRYPTO)
		cqcfg |= CQHCI_CRYPTO_GENERAL_ENABLE;

	cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_CFG);

	cqhci_ग_लिखोl(cq_host, lower_32_bits(cq_host->desc_dma_base),
		     CQHCI_TDLBA);
	cqhci_ग_लिखोl(cq_host, upper_32_bits(cq_host->desc_dma_base),
		     CQHCI_TDLBAU);

	cqhci_ग_लिखोl(cq_host, cq_host->rca, CQHCI_SSC2);

	cqhci_set_irqs(cq_host, 0);

	cqcfg |= CQHCI_ENABLE;

	cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_CFG);

	mmc->cqe_on = true;

	अगर (cq_host->ops->enable)
		cq_host->ops->enable(mmc);

	/* Ensure all ग_लिखोs are करोne beक्रमe पूर्णांकerrupts are enabled */
	wmb();

	cqhci_set_irqs(cq_host, CQHCI_IS_MASK);

	cq_host->activated = true;
पूर्ण

अटल व्योम __cqhci_disable(काष्ठा cqhci_host *cq_host)
अणु
	u32 cqcfg;

	cqcfg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	cqcfg &= ~CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_CFG);

	cq_host->mmc->cqe_on = false;

	cq_host->activated = false;
पूर्ण

पूर्णांक cqhci_deactivate(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;

	अगर (cq_host->enabled && cq_host->activated)
		__cqhci_disable(cq_host);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cqhci_deactivate);

पूर्णांक cqhci_resume(काष्ठा mmc_host *mmc)
अणु
	/* Re-enable is करोne upon first request */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cqhci_resume);

अटल पूर्णांक cqhci_enable(काष्ठा mmc_host *mmc, काष्ठा mmc_card *card)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	पूर्णांक err;

	अगर (!card->ext_csd.cmdq_en)
		वापस -EINVAL;

	अगर (cq_host->enabled)
		वापस 0;

	cq_host->rca = card->rca;

	err = cqhci_host_alloc_tdl(cq_host);
	अगर (err) अणु
		pr_err("%s: Failed to enable CQE, error %d\n",
		       mmc_hostname(mmc), err);
		वापस err;
	पूर्ण

	__cqhci_enable(cq_host);

	cq_host->enabled = true;

#अगर_घोषित DEBUG
	cqhci_dumpregs(cq_host);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* CQHCI is idle and should halt immediately, so set a small समयout */
#घोषणा CQHCI_OFF_TIMEOUT 100

अटल u32 cqhci_पढ़ो_ctl(काष्ठा cqhci_host *cq_host)
अणु
	वापस cqhci_पढ़ोl(cq_host, CQHCI_CTL);
पूर्ण

अटल व्योम cqhci_off(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 reg;
	पूर्णांक err;

	अगर (!cq_host->enabled || !mmc->cqe_on || cq_host->recovery_halt)
		वापस;

	अगर (cq_host->ops->disable)
		cq_host->ops->disable(mmc, false);

	cqhci_ग_लिखोl(cq_host, CQHCI_HALT, CQHCI_CTL);

	err = पढ़ोx_poll_समयout(cqhci_पढ़ो_ctl, cq_host, reg,
				 reg & CQHCI_HALT, 0, CQHCI_OFF_TIMEOUT);
	अगर (err < 0)
		pr_err("%s: cqhci: CQE stuck on\n", mmc_hostname(mmc));
	अन्यथा
		pr_debug("%s: cqhci: CQE off\n", mmc_hostname(mmc));

	अगर (cq_host->ops->post_disable)
		cq_host->ops->post_disable(mmc);

	mmc->cqe_on = false;
पूर्ण

अटल व्योम cqhci_disable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;

	अगर (!cq_host->enabled)
		वापस;

	cqhci_off(mmc);

	__cqhci_disable(cq_host);

	dmam_मुक्त_coherent(mmc_dev(mmc), cq_host->data_size,
			   cq_host->trans_desc_base,
			   cq_host->trans_desc_dma_base);

	dmam_मुक्त_coherent(mmc_dev(mmc), cq_host->desc_size,
			   cq_host->desc_base,
			   cq_host->desc_dma_base);

	cq_host->trans_desc_base = शून्य;
	cq_host->desc_base = शून्य;

	cq_host->enabled = false;
पूर्ण

अटल व्योम cqhci_prep_task_desc(काष्ठा mmc_request *mrq,
				 काष्ठा cqhci_host *cq_host, पूर्णांक tag)
अणु
	__le64 *task_desc = (__le64 __क्रमce *)get_desc(cq_host, tag);
	u32 req_flags = mrq->data->flags;
	u64 desc0;

	desc0 = CQHCI_VALID(1) |
		CQHCI_END(1) |
		CQHCI_INT(1) |
		CQHCI_ACT(0x5) |
		CQHCI_FORCED_PROG(!!(req_flags & MMC_DATA_FORCED_PRG)) |
		CQHCI_DATA_TAG(!!(req_flags & MMC_DATA_DAT_TAG)) |
		CQHCI_DATA_सूची(!!(req_flags & MMC_DATA_READ)) |
		CQHCI_PRIORITY(!!(req_flags & MMC_DATA_PRIO)) |
		CQHCI_QBAR(!!(req_flags & MMC_DATA_QBR)) |
		CQHCI_REL_WRITE(!!(req_flags & MMC_DATA_REL_WR)) |
		CQHCI_BLK_COUNT(mrq->data->blocks) |
		CQHCI_BLK_ADDR((u64)mrq->data->blk_addr);

	task_desc[0] = cpu_to_le64(desc0);

	अगर (cq_host->caps & CQHCI_TASK_DESC_SZ_128) अणु
		u64 desc1 = cqhci_crypto_prep_task_desc(mrq);

		task_desc[1] = cpu_to_le64(desc1);

		pr_debug("%s: cqhci: tag %d task descriptor 0x%016llx%016llx\n",
			 mmc_hostname(mrq->host), mrq->tag, desc1, desc0);
	पूर्ण अन्यथा अणु
		pr_debug("%s: cqhci: tag %d task descriptor 0x%016llx\n",
			 mmc_hostname(mrq->host), mrq->tag, desc0);
	पूर्ण
पूर्ण

अटल पूर्णांक cqhci_dma_map(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक sg_count;
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस -EINVAL;

	sg_count = dma_map_sg(mmc_dev(host), data->sg,
			      data->sg_len,
			      (data->flags & MMC_DATA_WRITE) ?
			      DMA_TO_DEVICE : DMA_FROM_DEVICE);
	अगर (!sg_count) अणु
		pr_err("%s: sg-len: %d\n", __func__, data->sg_len);
		वापस -ENOMEM;
	पूर्ण

	वापस sg_count;
पूर्ण

अटल व्योम cqhci_set_tran_desc(u8 *desc, dma_addr_t addr, पूर्णांक len, bool end,
				bool dma64)
अणु
	__le32 *attr = (__le32 __क्रमce *)desc;

	*attr = (CQHCI_VALID(1) |
		 CQHCI_END(end ? 1 : 0) |
		 CQHCI_INT(0) |
		 CQHCI_ACT(0x4) |
		 CQHCI_DAT_LENGTH(len));

	अगर (dma64) अणु
		__le64 *dataddr = (__le64 __क्रमce *)(desc + 4);

		dataddr[0] = cpu_to_le64(addr);
	पूर्ण अन्यथा अणु
		__le32 *dataddr = (__le32 __क्रमce *)(desc + 4);

		dataddr[0] = cpu_to_le32(addr);
	पूर्ण
पूर्ण

अटल पूर्णांक cqhci_prep_tran_desc(काष्ठा mmc_request *mrq,
			       काष्ठा cqhci_host *cq_host, पूर्णांक tag)
अणु
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक i, sg_count, len;
	bool end = false;
	bool dma64 = cq_host->dma64;
	dma_addr_t addr;
	u8 *desc;
	काष्ठा scatterlist *sg;

	sg_count = cqhci_dma_map(mrq->host, mrq);
	अगर (sg_count < 0) अणु
		pr_err("%s: %s: unable to map sg lists, %d\n",
				mmc_hostname(mrq->host), __func__, sg_count);
		वापस sg_count;
	पूर्ण

	desc = get_trans_desc(cq_host, tag);

	क्रम_each_sg(data->sg, sg, sg_count, i) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);

		अगर ((i+1) == sg_count)
			end = true;
		cqhci_set_tran_desc(desc, addr, len, end, dma64);
		desc += cq_host->trans_desc_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cqhci_prep_dcmd_desc(काष्ठा mmc_host *mmc,
				   काष्ठा mmc_request *mrq)
अणु
	u64 *task_desc = शून्य;
	u64 data = 0;
	u8 resp_type;
	u8 *desc;
	__le64 *dataddr;
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u8 timing;

	अगर (!(mrq->cmd->flags & MMC_RSP_PRESENT)) अणु
		resp_type = 0x0;
		timing = 0x1;
	पूर्ण अन्यथा अणु
		अगर (mrq->cmd->flags & MMC_RSP_R1B) अणु
			resp_type = 0x3;
			timing = 0x0;
		पूर्ण अन्यथा अणु
			resp_type = 0x2;
			timing = 0x1;
		पूर्ण
	पूर्ण

	task_desc = (__le64 __क्रमce *)get_desc(cq_host, cq_host->dcmd_slot);
	स_रखो(task_desc, 0, cq_host->task_desc_len);
	data |= (CQHCI_VALID(1) |
		 CQHCI_END(1) |
		 CQHCI_INT(1) |
		 CQHCI_QBAR(1) |
		 CQHCI_ACT(0x5) |
		 CQHCI_CMD_INDEX(mrq->cmd->opcode) |
		 CQHCI_CMD_TIMING(timing) | CQHCI_RESP_TYPE(resp_type));
	अगर (cq_host->ops->update_dcmd_desc)
		cq_host->ops->update_dcmd_desc(mmc, mrq, &data);
	*task_desc |= data;
	desc = (u8 *)task_desc;
	pr_debug("%s: cqhci: dcmd: cmd: %d timing: %d resp: %d\n",
		 mmc_hostname(mmc), mrq->cmd->opcode, timing, resp_type);
	dataddr = (__le64 __क्रमce *)(desc + 4);
	dataddr[0] = cpu_to_le64((u64)mrq->cmd->arg);

पूर्ण

अटल व्योम cqhci_post_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (data) अणु
		dma_unmap_sg(mmc_dev(host), data->sg, data->sg_len,
			     (data->flags & MMC_DATA_READ) ?
			     DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक cqhci_tag(काष्ठा mmc_request *mrq)
अणु
	वापस mrq->cmd ? DCMD_SLOT : mrq->tag;
पूर्ण

अटल पूर्णांक cqhci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक err = 0;
	पूर्णांक tag = cqhci_tag(mrq);
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	अचिन्हित दीर्घ flags;

	अगर (!cq_host->enabled) अणु
		pr_err("%s: cqhci: not enabled\n", mmc_hostname(mmc));
		वापस -EINVAL;
	पूर्ण

	/* First request after resume has to re-enable */
	अगर (!cq_host->activated)
		__cqhci_enable(cq_host);

	अगर (!mmc->cqe_on) अणु
		अगर (cq_host->ops->pre_enable)
			cq_host->ops->pre_enable(mmc);

		cqhci_ग_लिखोl(cq_host, 0, CQHCI_CTL);
		mmc->cqe_on = true;
		pr_debug("%s: cqhci: CQE on\n", mmc_hostname(mmc));
		अगर (cqhci_पढ़ोl(cq_host, CQHCI_CTL) && CQHCI_HALT) अणु
			pr_err("%s: cqhci: CQE failed to exit halt state\n",
			       mmc_hostname(mmc));
		पूर्ण
		अगर (cq_host->ops->enable)
			cq_host->ops->enable(mmc);
	पूर्ण

	अगर (mrq->data) अणु
		cqhci_prep_task_desc(mrq, cq_host, tag);

		err = cqhci_prep_tran_desc(mrq, cq_host, tag);
		अगर (err) अणु
			pr_err("%s: cqhci: failed to setup tx desc: %d\n",
			       mmc_hostname(mmc), err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		cqhci_prep_dcmd_desc(mmc, mrq);
	पूर्ण

	spin_lock_irqsave(&cq_host->lock, flags);

	अगर (cq_host->recovery_halt) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	cq_host->slot[tag].mrq = mrq;
	cq_host->slot[tag].flags = 0;

	cq_host->qcnt += 1;
	/* Make sure descriptors are पढ़ोy beक्रमe ringing the करोorbell */
	wmb();
	cqhci_ग_लिखोl(cq_host, 1 << tag, CQHCI_TDBR);
	अगर (!(cqhci_पढ़ोl(cq_host, CQHCI_TDBR) & (1 << tag)))
		pr_debug("%s: cqhci: doorbell not set for tag %d\n",
			 mmc_hostname(mmc), tag);
out_unlock:
	spin_unlock_irqrestore(&cq_host->lock, flags);

	अगर (err)
		cqhci_post_req(mmc, mrq);

	वापस err;
पूर्ण

अटल व्योम cqhci_recovery_needed(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
				  bool notअगरy)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;

	अगर (!cq_host->recovery_halt) अणु
		cq_host->recovery_halt = true;
		pr_debug("%s: cqhci: recovery needed\n", mmc_hostname(mmc));
		wake_up(&cq_host->रुको_queue);
		अगर (notअगरy && mrq->recovery_notअगरier)
			mrq->recovery_notअगरier(mrq);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक cqhci_error_flags(पूर्णांक error1, पूर्णांक error2)
अणु
	पूर्णांक error = error1 ? error1 : error2;

	चयन (error) अणु
	हाल -EILSEQ:
		वापस CQHCI_HOST_CRC;
	हाल -ETIMEDOUT:
		वापस CQHCI_HOST_TIMEOUT;
	शेष:
		वापस CQHCI_HOST_OTHER;
	पूर्ण
पूर्ण

अटल व्योम cqhci_error_irq(काष्ठा mmc_host *mmc, u32 status, पूर्णांक cmd_error,
			    पूर्णांक data_error)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	काष्ठा cqhci_slot *slot;
	u32 terri;
	u32 tdpe;
	पूर्णांक tag;

	spin_lock(&cq_host->lock);

	terri = cqhci_पढ़ोl(cq_host, CQHCI_TERRI);

	pr_debug("%s: cqhci: error IRQ status: 0x%08x cmd error %d data error %d TERRI: 0x%08x\n",
		 mmc_hostname(mmc), status, cmd_error, data_error, terri);

	/* Forget about errors when recovery has alपढ़ोy been triggered */
	अगर (cq_host->recovery_halt)
		जाओ out_unlock;

	अगर (!cq_host->qcnt) अणु
		WARN_ONCE(1, "%s: cqhci: error when idle. IRQ status: 0x%08x cmd error %d data error %d TERRI: 0x%08x\n",
			  mmc_hostname(mmc), status, cmd_error, data_error,
			  terri);
		जाओ out_unlock;
	पूर्ण

	अगर (CQHCI_TERRI_C_VALID(terri)) अणु
		tag = CQHCI_TERRI_C_TASK(terri);
		slot = &cq_host->slot[tag];
		अगर (slot->mrq) अणु
			slot->flags = cqhci_error_flags(cmd_error, data_error);
			cqhci_recovery_needed(mmc, slot->mrq, true);
		पूर्ण
	पूर्ण

	अगर (CQHCI_TERRI_D_VALID(terri)) अणु
		tag = CQHCI_TERRI_D_TASK(terri);
		slot = &cq_host->slot[tag];
		अगर (slot->mrq) अणु
			slot->flags = cqhci_error_flags(data_error, cmd_error);
			cqhci_recovery_needed(mmc, slot->mrq, true);
		पूर्ण
	पूर्ण

	/*
	 * Handle ICCE ("Invalid Crypto Configuration Error").  This should
	 * never happen, since the block layer ensures that all crypto-enabled
	 * I/O requests have a valid keyslot beक्रमe they reach the driver.
	 *
	 * Note that GCE ("General Crypto Error") is dअगरferent; it alपढ़ोy got
	 * handled above by checking TERRI.
	 */
	अगर (status & CQHCI_IS_ICCE) अणु
		tdpe = cqhci_पढ़ोl(cq_host, CQHCI_TDPE);
		WARN_ONCE(1,
			  "%s: cqhci: invalid crypto configuration error. IRQ status: 0x%08x TDPE: 0x%08x\n",
			  mmc_hostname(mmc), status, tdpe);
		जबतक (tdpe != 0) अणु
			tag = __ffs(tdpe);
			tdpe &= ~(1 << tag);
			slot = &cq_host->slot[tag];
			अगर (!slot->mrq)
				जारी;
			slot->flags = cqhci_error_flags(data_error, cmd_error);
			cqhci_recovery_needed(mmc, slot->mrq, true);
		पूर्ण
	पूर्ण

	अगर (!cq_host->recovery_halt) अणु
		/*
		 * The only way to guarantee क्रमward progress is to mark at
		 * least one task in error, so अगर none is indicated, pick one.
		 */
		क्रम (tag = 0; tag < NUM_SLOTS; tag++) अणु
			slot = &cq_host->slot[tag];
			अगर (!slot->mrq)
				जारी;
			slot->flags = cqhci_error_flags(data_error, cmd_error);
			cqhci_recovery_needed(mmc, slot->mrq, true);
			अवरोध;
		पूर्ण
	पूर्ण

out_unlock:
	spin_unlock(&cq_host->lock);
पूर्ण

अटल व्योम cqhci_finish_mrq(काष्ठा mmc_host *mmc, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	काष्ठा cqhci_slot *slot = &cq_host->slot[tag];
	काष्ठा mmc_request *mrq = slot->mrq;
	काष्ठा mmc_data *data;

	अगर (!mrq) अणु
		WARN_ONCE(1, "%s: cqhci: spurious TCN for tag %d\n",
			  mmc_hostname(mmc), tag);
		वापस;
	पूर्ण

	/* No completions allowed during recovery */
	अगर (cq_host->recovery_halt) अणु
		slot->flags |= CQHCI_COMPLETED;
		वापस;
	पूर्ण

	slot->mrq = शून्य;

	cq_host->qcnt -= 1;

	data = mrq->data;
	अगर (data) अणु
		अगर (data->error)
			data->bytes_xfered = 0;
		अन्यथा
			data->bytes_xfered = data->blksz * data->blocks;
	पूर्ण

	mmc_cqe_request_करोne(mmc, mrq);
पूर्ण

irqवापस_t cqhci_irq(काष्ठा mmc_host *mmc, u32 पूर्णांकmask, पूर्णांक cmd_error,
		      पूर्णांक data_error)
अणु
	u32 status;
	अचिन्हित दीर्घ tag = 0, comp_status;
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;

	status = cqhci_पढ़ोl(cq_host, CQHCI_IS);
	cqhci_ग_लिखोl(cq_host, status, CQHCI_IS);

	pr_debug("%s: cqhci: IRQ status: 0x%08x\n", mmc_hostname(mmc), status);

	अगर ((status & (CQHCI_IS_RED | CQHCI_IS_GCE | CQHCI_IS_ICCE)) ||
	    cmd_error || data_error)
		cqhci_error_irq(mmc, status, cmd_error, data_error);

	अगर (status & CQHCI_IS_TCC) अणु
		/* पढ़ो TCN and complete the request */
		comp_status = cqhci_पढ़ोl(cq_host, CQHCI_TCN);
		cqhci_ग_लिखोl(cq_host, comp_status, CQHCI_TCN);
		pr_debug("%s: cqhci: TCN: 0x%08lx\n",
			 mmc_hostname(mmc), comp_status);

		spin_lock(&cq_host->lock);

		क्रम_each_set_bit(tag, &comp_status, cq_host->num_slots) अणु
			/* complete the corresponding mrq */
			pr_debug("%s: cqhci: completing tag %lu\n",
				 mmc_hostname(mmc), tag);
			cqhci_finish_mrq(mmc, tag);
		पूर्ण

		अगर (cq_host->रुकोing_क्रम_idle && !cq_host->qcnt) अणु
			cq_host->रुकोing_क्रम_idle = false;
			wake_up(&cq_host->रुको_queue);
		पूर्ण

		spin_unlock(&cq_host->lock);
	पूर्ण

	अगर (status & CQHCI_IS_TCL)
		wake_up(&cq_host->रुको_queue);

	अगर (status & CQHCI_IS_HAC)
		wake_up(&cq_host->रुको_queue);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(cqhci_irq);

अटल bool cqhci_is_idle(काष्ठा cqhci_host *cq_host, पूर्णांक *ret)
अणु
	अचिन्हित दीर्घ flags;
	bool is_idle;

	spin_lock_irqsave(&cq_host->lock, flags);
	is_idle = !cq_host->qcnt || cq_host->recovery_halt;
	*ret = cq_host->recovery_halt ? -EBUSY : 0;
	cq_host->रुकोing_क्रम_idle = !is_idle;
	spin_unlock_irqrestore(&cq_host->lock, flags);

	वापस is_idle;
पूर्ण

अटल पूर्णांक cqhci_रुको_क्रम_idle(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	पूर्णांक ret;

	रुको_event(cq_host->रुको_queue, cqhci_is_idle(cq_host, &ret));

	वापस ret;
पूर्ण

अटल bool cqhci_समयout(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
			  bool *recovery_needed)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	पूर्णांक tag = cqhci_tag(mrq);
	काष्ठा cqhci_slot *slot = &cq_host->slot[tag];
	अचिन्हित दीर्घ flags;
	bool समयd_out;

	spin_lock_irqsave(&cq_host->lock, flags);
	समयd_out = slot->mrq == mrq;
	अगर (समयd_out) अणु
		slot->flags |= CQHCI_EXTERNAL_TIMEOUT;
		cqhci_recovery_needed(mmc, mrq, false);
		*recovery_needed = cq_host->recovery_halt;
	पूर्ण
	spin_unlock_irqrestore(&cq_host->lock, flags);

	अगर (समयd_out) अणु
		pr_err("%s: cqhci: timeout for tag %d\n",
		       mmc_hostname(mmc), tag);
		cqhci_dumpregs(cq_host);
	पूर्ण

	वापस समयd_out;
पूर्ण

अटल bool cqhci_tasks_cleared(काष्ठा cqhci_host *cq_host)
अणु
	वापस !(cqhci_पढ़ोl(cq_host, CQHCI_CTL) & CQHCI_CLEAR_ALL_TASKS);
पूर्ण

अटल bool cqhci_clear_all_tasks(काष्ठा mmc_host *mmc, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	bool ret;
	u32 ctl;

	cqhci_set_irqs(cq_host, CQHCI_IS_TCL);

	ctl = cqhci_पढ़ोl(cq_host, CQHCI_CTL);
	ctl |= CQHCI_CLEAR_ALL_TASKS;
	cqhci_ग_लिखोl(cq_host, ctl, CQHCI_CTL);

	रुको_event_समयout(cq_host->रुको_queue, cqhci_tasks_cleared(cq_host),
			   msecs_to_jअगरfies(समयout) + 1);

	cqhci_set_irqs(cq_host, 0);

	ret = cqhci_tasks_cleared(cq_host);

	अगर (!ret)
		pr_debug("%s: cqhci: Failed to clear tasks\n",
			 mmc_hostname(mmc));

	वापस ret;
पूर्ण

अटल bool cqhci_halted(काष्ठा cqhci_host *cq_host)
अणु
	वापस cqhci_पढ़ोl(cq_host, CQHCI_CTL) & CQHCI_HALT;
पूर्ण

अटल bool cqhci_halt(काष्ठा mmc_host *mmc, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	bool ret;
	u32 ctl;

	अगर (cqhci_halted(cq_host))
		वापस true;

	cqhci_set_irqs(cq_host, CQHCI_IS_HAC);

	ctl = cqhci_पढ़ोl(cq_host, CQHCI_CTL);
	ctl |= CQHCI_HALT;
	cqhci_ग_लिखोl(cq_host, ctl, CQHCI_CTL);

	रुको_event_समयout(cq_host->रुको_queue, cqhci_halted(cq_host),
			   msecs_to_jअगरfies(समयout) + 1);

	cqhci_set_irqs(cq_host, 0);

	ret = cqhci_halted(cq_host);

	अगर (!ret)
		pr_debug("%s: cqhci: Failed to halt\n", mmc_hostname(mmc));

	वापस ret;
पूर्ण

/*
 * After halting we expect to be able to use the command line. We पूर्णांकerpret the
 * failure to halt to mean the data lines might still be in use (and the upper
 * layers will need to send a STOP command), so we set the समयout based on a
 * generous command समयout.
 */
#घोषणा CQHCI_START_HALT_TIMEOUT	5

अटल व्योम cqhci_recovery_start(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;

	pr_debug("%s: cqhci: %s\n", mmc_hostname(mmc), __func__);

	WARN_ON(!cq_host->recovery_halt);

	cqhci_halt(mmc, CQHCI_START_HALT_TIMEOUT);

	अगर (cq_host->ops->disable)
		cq_host->ops->disable(mmc, true);

	mmc->cqe_on = false;
पूर्ण

अटल पूर्णांक cqhci_error_from_flags(अचिन्हित पूर्णांक flags)
अणु
	अगर (!flags)
		वापस 0;

	/* CRC errors might indicate re-tuning so prefer to report that */
	अगर (flags & CQHCI_HOST_CRC)
		वापस -EILSEQ;

	अगर (flags & (CQHCI_EXTERNAL_TIMEOUT | CQHCI_HOST_TIMEOUT))
		वापस -ETIMEDOUT;

	वापस -EIO;
पूर्ण

अटल व्योम cqhci_recover_mrq(काष्ठा cqhci_host *cq_host, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा cqhci_slot *slot = &cq_host->slot[tag];
	काष्ठा mmc_request *mrq = slot->mrq;
	काष्ठा mmc_data *data;

	अगर (!mrq)
		वापस;

	slot->mrq = शून्य;

	cq_host->qcnt -= 1;

	data = mrq->data;
	अगर (data) अणु
		data->bytes_xfered = 0;
		data->error = cqhci_error_from_flags(slot->flags);
	पूर्ण अन्यथा अणु
		mrq->cmd->error = cqhci_error_from_flags(slot->flags);
	पूर्ण

	mmc_cqe_request_करोne(cq_host->mmc, mrq);
पूर्ण

अटल व्योम cqhci_recover_mrqs(काष्ठा cqhci_host *cq_host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cq_host->num_slots; i++)
		cqhci_recover_mrq(cq_host, i);
पूर्ण

/*
 * By now the command and data lines should be unused so there is no reason क्रम
 * CQHCI to take a दीर्घ समय to halt, but अगर it करोesn't halt there could be
 * problems clearing tasks, so be generous.
 */
#घोषणा CQHCI_FINISH_HALT_TIMEOUT	20

/* CQHCI could be expected to clear it's पूर्णांकernal state pretty quickly */
#घोषणा CQHCI_CLEAR_TIMEOUT		20

अटल व्योम cqhci_recovery_finish(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	अचिन्हित दीर्घ flags;
	u32 cqcfg;
	bool ok;

	pr_debug("%s: cqhci: %s\n", mmc_hostname(mmc), __func__);

	WARN_ON(!cq_host->recovery_halt);

	ok = cqhci_halt(mmc, CQHCI_FINISH_HALT_TIMEOUT);

	अगर (!cqhci_clear_all_tasks(mmc, CQHCI_CLEAR_TIMEOUT))
		ok = false;

	/*
	 * The specअगरication contradicts itself, by saying that tasks cannot be
	 * cleared अगर CQHCI करोes not halt, but अगर CQHCI करोes not halt, it should
	 * be disabled/re-enabled, but not to disable beक्रमe clearing tasks.
	 * Have a go anyway.
	 */
	अगर (!ok) अणु
		pr_debug("%s: cqhci: disable / re-enable\n", mmc_hostname(mmc));
		cqcfg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
		cqcfg &= ~CQHCI_ENABLE;
		cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_CFG);
		cqcfg |= CQHCI_ENABLE;
		cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_CFG);
		/* Be sure that there are no tasks */
		ok = cqhci_halt(mmc, CQHCI_FINISH_HALT_TIMEOUT);
		अगर (!cqhci_clear_all_tasks(mmc, CQHCI_CLEAR_TIMEOUT))
			ok = false;
		WARN_ON(!ok);
	पूर्ण

	cqhci_recover_mrqs(cq_host);

	WARN_ON(cq_host->qcnt);

	spin_lock_irqsave(&cq_host->lock, flags);
	cq_host->qcnt = 0;
	cq_host->recovery_halt = false;
	mmc->cqe_on = false;
	spin_unlock_irqrestore(&cq_host->lock, flags);

	/* Ensure all ग_लिखोs are करोne beक्रमe पूर्णांकerrupts are re-enabled */
	wmb();

	cqhci_ग_लिखोl(cq_host, CQHCI_IS_HAC | CQHCI_IS_TCL, CQHCI_IS);

	cqhci_set_irqs(cq_host, CQHCI_IS_MASK);

	pr_debug("%s: cqhci: recovery done\n", mmc_hostname(mmc));
पूर्ण

अटल स्थिर काष्ठा mmc_cqe_ops cqhci_cqe_ops = अणु
	.cqe_enable = cqhci_enable,
	.cqe_disable = cqhci_disable,
	.cqe_request = cqhci_request,
	.cqe_post_req = cqhci_post_req,
	.cqe_off = cqhci_off,
	.cqe_रुको_क्रम_idle = cqhci_रुको_क्रम_idle,
	.cqe_समयout = cqhci_समयout,
	.cqe_recovery_start = cqhci_recovery_start,
	.cqe_recovery_finish = cqhci_recovery_finish,
पूर्ण;

काष्ठा cqhci_host *cqhci_pltfm_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cqhci_host *cq_host;
	काष्ठा resource *cqhci_memres = शून्य;

	/* check and setup CMDQ पूर्णांकerface */
	cqhci_memres = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "cqhci");
	अगर (!cqhci_memres) अणु
		dev_dbg(&pdev->dev, "CMDQ not supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cq_host = devm_kzalloc(&pdev->dev, माप(*cq_host), GFP_KERNEL);
	अगर (!cq_host)
		वापस ERR_PTR(-ENOMEM);
	cq_host->mmio = devm_ioremap(&pdev->dev,
				     cqhci_memres->start,
				     resource_size(cqhci_memres));
	अगर (!cq_host->mmio) अणु
		dev_err(&pdev->dev, "failed to remap cqhci regs\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	dev_dbg(&pdev->dev, "CMDQ ioremap: done\n");

	वापस cq_host;
पूर्ण
EXPORT_SYMBOL(cqhci_pltfm_init);

अटल अचिन्हित पूर्णांक cqhci_ver_major(काष्ठा cqhci_host *cq_host)
अणु
	वापस CQHCI_VER_MAJOR(cqhci_पढ़ोl(cq_host, CQHCI_VER));
पूर्ण

अटल अचिन्हित पूर्णांक cqhci_ver_minor(काष्ठा cqhci_host *cq_host)
अणु
	u32 ver = cqhci_पढ़ोl(cq_host, CQHCI_VER);

	वापस CQHCI_VER_MINOR1(ver) * 10 + CQHCI_VER_MINOR2(ver);
पूर्ण

पूर्णांक cqhci_init(काष्ठा cqhci_host *cq_host, काष्ठा mmc_host *mmc,
	      bool dma64)
अणु
	पूर्णांक err;

	cq_host->dma64 = dma64;
	cq_host->mmc = mmc;
	cq_host->mmc->cqe_निजी = cq_host;

	cq_host->num_slots = NUM_SLOTS;
	cq_host->dcmd_slot = DCMD_SLOT;

	mmc->cqe_ops = &cqhci_cqe_ops;

	mmc->cqe_qdepth = NUM_SLOTS;
	अगर (mmc->caps2 & MMC_CAP2_CQE_DCMD)
		mmc->cqe_qdepth -= 1;

	cq_host->slot = devm_kसुस्मृति(mmc_dev(mmc), cq_host->num_slots,
				     माप(*cq_host->slot), GFP_KERNEL);
	अगर (!cq_host->slot) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	err = cqhci_crypto_init(cq_host);
	अगर (err) अणु
		pr_err("%s: CQHCI crypto initialization failed\n",
		       mmc_hostname(mmc));
		जाओ out_err;
	पूर्ण

	spin_lock_init(&cq_host->lock);

	init_completion(&cq_host->halt_comp);
	init_रुकोqueue_head(&cq_host->रुको_queue);

	pr_info("%s: CQHCI version %u.%02u\n",
		mmc_hostname(mmc), cqhci_ver_major(cq_host),
		cqhci_ver_minor(cq_host));

	वापस 0;

out_err:
	pr_err("%s: CQHCI version %u.%02u failed to initialize, error %d\n",
	       mmc_hostname(mmc), cqhci_ver_major(cq_host),
	       cqhci_ver_minor(cq_host), err);
	वापस err;
पूर्ण
EXPORT_SYMBOL(cqhci_init);

MODULE_AUTHOR("Venkat Gopalakrishnan <venkatg@codeaurora.org>");
MODULE_DESCRIPTION("Command Queue Host Controller Interface driver");
MODULE_LICENSE("GPL v2");
