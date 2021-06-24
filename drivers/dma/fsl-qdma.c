<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2014-2015 Freescale
// Copyright 2018 NXP

/*
 * Driver क्रम NXP Layerscape Queue Direct Memory Access Controller
 *
 * Author:
 *  Wen He <wen.he_1@nxp.com>
 *  Jiaheng Fan <jiaheng.fan@nxp.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/dma-mapping.h>

#समावेश "virt-dma.h"
#समावेश "fsldma.h"

/* Register related definition */
#घोषणा FSL_QDMA_DMR			0x0
#घोषणा FSL_QDMA_DSR			0x4
#घोषणा FSL_QDMA_DEIER			0xe00
#घोषणा FSL_QDMA_DEDR			0xe04
#घोषणा FSL_QDMA_DECFDW0R		0xe10
#घोषणा FSL_QDMA_DECFDW1R		0xe14
#घोषणा FSL_QDMA_DECFDW2R		0xe18
#घोषणा FSL_QDMA_DECFDW3R		0xe1c
#घोषणा FSL_QDMA_DECFQIDR		0xe30
#घोषणा FSL_QDMA_DECBR			0xe34

#घोषणा FSL_QDMA_BCQMR(x)		(0xc0 + 0x100 * (x))
#घोषणा FSL_QDMA_BCQSR(x)		(0xc4 + 0x100 * (x))
#घोषणा FSL_QDMA_BCQEDPA_SADDR(x)	(0xc8 + 0x100 * (x))
#घोषणा FSL_QDMA_BCQDPA_SADDR(x)	(0xcc + 0x100 * (x))
#घोषणा FSL_QDMA_BCQEEPA_SADDR(x)	(0xd0 + 0x100 * (x))
#घोषणा FSL_QDMA_BCQEPA_SADDR(x)	(0xd4 + 0x100 * (x))
#घोषणा FSL_QDMA_BCQIER(x)		(0xe0 + 0x100 * (x))
#घोषणा FSL_QDMA_BCQIDR(x)		(0xe4 + 0x100 * (x))

#घोषणा FSL_QDMA_SQDPAR			0x80c
#घोषणा FSL_QDMA_SQEPAR			0x814
#घोषणा FSL_QDMA_BSQMR			0x800
#घोषणा FSL_QDMA_BSQSR			0x804
#घोषणा FSL_QDMA_BSQICR			0x828
#घोषणा FSL_QDMA_CQMR			0xa00
#घोषणा FSL_QDMA_CQDSCR1		0xa08
#घोषणा FSL_QDMA_CQDSCR2                0xa0c
#घोषणा FSL_QDMA_CQIER			0xa10
#घोषणा FSL_QDMA_CQEDR			0xa14
#घोषणा FSL_QDMA_SQCCMR			0xa20

/* Registers क्रम bit and genmask */
#घोषणा FSL_QDMA_CQIDR_SQT		BIT(15)
#घोषणा QDMA_CCDF_FORMAT		BIT(29)
#घोषणा QDMA_CCDF_SER			BIT(30)
#घोषणा QDMA_SG_FIN			BIT(30)
#घोषणा QDMA_SG_LEN_MASK		GENMASK(29, 0)
#घोषणा QDMA_CCDF_MASK			GENMASK(28, 20)

#घोषणा FSL_QDMA_DEDR_CLEAR		GENMASK(31, 0)
#घोषणा FSL_QDMA_BCQIDR_CLEAR		GENMASK(31, 0)
#घोषणा FSL_QDMA_DEIER_CLEAR		GENMASK(31, 0)

#घोषणा FSL_QDMA_BCQIER_CQTIE		BIT(15)
#घोषणा FSL_QDMA_BCQIER_CQPEIE		BIT(23)
#घोषणा FSL_QDMA_BSQICR_ICEN		BIT(31)

#घोषणा FSL_QDMA_BSQICR_ICST(x)		((x) << 16)
#घोषणा FSL_QDMA_CQIER_MEIE		BIT(31)
#घोषणा FSL_QDMA_CQIER_TEIE		BIT(0)
#घोषणा FSL_QDMA_SQCCMR_ENTER_WM	BIT(21)

#घोषणा FSL_QDMA_BCQMR_EN		BIT(31)
#घोषणा FSL_QDMA_BCQMR_EI		BIT(30)
#घोषणा FSL_QDMA_BCQMR_CD_THLD(x)	((x) << 20)
#घोषणा FSL_QDMA_BCQMR_CQ_SIZE(x)	((x) << 16)

#घोषणा FSL_QDMA_BCQSR_QF		BIT(16)
#घोषणा FSL_QDMA_BCQSR_XOFF		BIT(0)

#घोषणा FSL_QDMA_BSQMR_EN		BIT(31)
#घोषणा FSL_QDMA_BSQMR_DI		BIT(30)
#घोषणा FSL_QDMA_BSQMR_CQ_SIZE(x)	((x) << 16)

#घोषणा FSL_QDMA_BSQSR_QE		BIT(17)

#घोषणा FSL_QDMA_DMR_DQD		BIT(30)
#घोषणा FSL_QDMA_DSR_DB		BIT(31)

/* Size related definition */
#घोषणा FSL_QDMA_QUEUE_MAX		8
#घोषणा FSL_QDMA_COMMAND_BUFFER_SIZE	64
#घोषणा FSL_QDMA_DESCRIPTOR_BUFFER_SIZE 32
#घोषणा FSL_QDMA_CIRCULAR_DESC_SIZE_MIN	64
#घोषणा FSL_QDMA_CIRCULAR_DESC_SIZE_MAX	16384
#घोषणा FSL_QDMA_QUEUE_NUM_MAX		8

/* Field definition क्रम CMD */
#घोषणा FSL_QDMA_CMD_RWTTYPE		0x4
#घोषणा FSL_QDMA_CMD_LWC                0x2
#घोषणा FSL_QDMA_CMD_RWTTYPE_OFFSET	28
#घोषणा FSL_QDMA_CMD_NS_OFFSET		27
#घोषणा FSL_QDMA_CMD_DQOS_OFFSET	24
#घोषणा FSL_QDMA_CMD_WTHROTL_OFFSET	20
#घोषणा FSL_QDMA_CMD_DSEN_OFFSET	19
#घोषणा FSL_QDMA_CMD_LWC_OFFSET		16

/* Field definition क्रम Descriptor status */
#घोषणा QDMA_CCDF_STATUS_RTE		BIT(5)
#घोषणा QDMA_CCDF_STATUS_WTE		BIT(4)
#घोषणा QDMA_CCDF_STATUS_CDE		BIT(2)
#घोषणा QDMA_CCDF_STATUS_SDE		BIT(1)
#घोषणा QDMA_CCDF_STATUS_DDE		BIT(0)
#घोषणा QDMA_CCDF_STATUS_MASK		(QDMA_CCDF_STATUS_RTE | \
					QDMA_CCDF_STATUS_WTE | \
					QDMA_CCDF_STATUS_CDE | \
					QDMA_CCDF_STATUS_SDE | \
					QDMA_CCDF_STATUS_DDE)

/* Field definition क्रम Descriptor offset */
#घोषणा QDMA_CCDF_OFFSET		20
#घोषणा QDMA_SDDF_CMD(x)		(((u64)(x)) << 32)

/* Field definition क्रम safe loop count*/
#घोषणा FSL_QDMA_HALT_COUNT		1500
#घोषणा FSL_QDMA_MAX_SIZE		16385
#घोषणा	FSL_QDMA_COMP_TIMEOUT		1000
#घोषणा FSL_COMMAND_QUEUE_OVERFLLOW	10

#घोषणा FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma_engine, x)			\
	(((fsl_qdma_engine)->block_offset) * (x))

/**
 * काष्ठा fsl_qdma_क्रमmat - This is the काष्ठा holding describing compound
 *			    descriptor क्रमmat with qDMA.
 * @status:		    Command status and enqueue status notअगरication.
 * @cfg:		    Frame offset and frame क्रमmat.
 * @addr_lo:		    Holding the compound descriptor of the lower
 *			    32-bits address in memory 40-bit address.
 * @addr_hi:		    Same as above member, but poपूर्णांक high 8-bits in
 *			    memory 40-bit address.
 * @__reserved1:	    Reserved field.
 * @cfg8b_w1:		    Compound descriptor command queue origin produced
 *			    by qDMA and dynamic debug field.
 * @data:		    Poपूर्णांकer to the memory 40-bit address, describes DMA
 *			    source inक्रमmation and DMA destination inक्रमmation.
 */
काष्ठा fsl_qdma_क्रमmat अणु
	__le32 status;
	__le32 cfg;
	जोड़ अणु
		काष्ठा अणु
			__le32 addr_lo;
			u8 addr_hi;
			u8 __reserved1[2];
			u8 cfg8b_w1;
		पूर्ण __packed;
		__le64 data;
	पूर्ण;
पूर्ण __packed;

/* qDMA status notअगरication pre inक्रमmation */
काष्ठा fsl_pre_status अणु
	u64 addr;
	u8 queue;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा fsl_pre_status, pre);

काष्ठा fsl_qdma_chan अणु
	काष्ठा virt_dma_chan		vchan;
	काष्ठा virt_dma_desc		vdesc;
	क्रमागत dma_status			status;
	काष्ठा fsl_qdma_engine		*qdma;
	काष्ठा fsl_qdma_queue		*queue;
पूर्ण;

काष्ठा fsl_qdma_queue अणु
	काष्ठा fsl_qdma_क्रमmat	*virt_head;
	काष्ठा fsl_qdma_क्रमmat	*virt_tail;
	काष्ठा list_head	comp_used;
	काष्ठा list_head	comp_मुक्त;
	काष्ठा dma_pool		*comp_pool;
	काष्ठा dma_pool		*desc_pool;
	spinlock_t		queue_lock;
	dma_addr_t		bus_addr;
	u32                     n_cq;
	u32			id;
	काष्ठा fsl_qdma_क्रमmat	*cq;
	व्योम __iomem		*block_base;
पूर्ण;

काष्ठा fsl_qdma_comp अणु
	dma_addr_t              bus_addr;
	dma_addr_t              desc_bus_addr;
	काष्ठा fsl_qdma_क्रमmat	*virt_addr;
	काष्ठा fsl_qdma_क्रमmat	*desc_virt_addr;
	काष्ठा fsl_qdma_chan	*qchan;
	काष्ठा virt_dma_desc    vdesc;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा fsl_qdma_engine अणु
	काष्ठा dma_device	dma_dev;
	व्योम __iomem		*ctrl_base;
	व्योम __iomem            *status_base;
	व्योम __iomem		*block_base;
	u32			n_chans;
	u32			n_queues;
	काष्ठा mutex            fsl_qdma_mutex;
	पूर्णांक			error_irq;
	पूर्णांक			*queue_irq;
	u32			feature;
	काष्ठा fsl_qdma_queue	*queue;
	काष्ठा fsl_qdma_queue	**status;
	काष्ठा fsl_qdma_chan	*chans;
	पूर्णांक			block_number;
	पूर्णांक			block_offset;
	पूर्णांक			irq_base;
	पूर्णांक			desc_allocated;

पूर्ण;

अटल अंतरभूत u64
qdma_ccdf_addr_get64(स्थिर काष्ठा fsl_qdma_क्रमmat *ccdf)
अणु
	वापस le64_to_cpu(ccdf->data) & (U64_MAX >> 24);
पूर्ण

अटल अंतरभूत व्योम
qdma_desc_addr_set64(काष्ठा fsl_qdma_क्रमmat *ccdf, u64 addr)
अणु
	ccdf->addr_hi = upper_32_bits(addr);
	ccdf->addr_lo = cpu_to_le32(lower_32_bits(addr));
पूर्ण

अटल अंतरभूत u8
qdma_ccdf_get_queue(स्थिर काष्ठा fsl_qdma_क्रमmat *ccdf)
अणु
	वापस ccdf->cfg8b_w1 & U8_MAX;
पूर्ण

अटल अंतरभूत पूर्णांक
qdma_ccdf_get_offset(स्थिर काष्ठा fsl_qdma_क्रमmat *ccdf)
अणु
	वापस (le32_to_cpu(ccdf->cfg) & QDMA_CCDF_MASK) >> QDMA_CCDF_OFFSET;
पूर्ण

अटल अंतरभूत व्योम
qdma_ccdf_set_क्रमmat(काष्ठा fsl_qdma_क्रमmat *ccdf, पूर्णांक offset)
अणु
	ccdf->cfg = cpu_to_le32(QDMA_CCDF_FORMAT |
				(offset << QDMA_CCDF_OFFSET));
पूर्ण

अटल अंतरभूत पूर्णांक
qdma_ccdf_get_status(स्थिर काष्ठा fsl_qdma_क्रमmat *ccdf)
अणु
	वापस (le32_to_cpu(ccdf->status) & QDMA_CCDF_STATUS_MASK);
पूर्ण

अटल अंतरभूत व्योम
qdma_ccdf_set_ser(काष्ठा fsl_qdma_क्रमmat *ccdf, पूर्णांक status)
अणु
	ccdf->status = cpu_to_le32(QDMA_CCDF_SER | status);
पूर्ण

अटल अंतरभूत व्योम qdma_csgf_set_len(काष्ठा fsl_qdma_क्रमmat *csgf, पूर्णांक len)
अणु
	csgf->cfg = cpu_to_le32(len & QDMA_SG_LEN_MASK);
पूर्ण

अटल अंतरभूत व्योम qdma_csgf_set_f(काष्ठा fsl_qdma_क्रमmat *csgf, पूर्णांक len)
अणु
	csgf->cfg = cpu_to_le32(QDMA_SG_FIN | (len & QDMA_SG_LEN_MASK));
पूर्ण

अटल u32 qdma_पढ़ोl(काष्ठा fsl_qdma_engine *qdma, व्योम __iomem *addr)
अणु
	वापस FSL_DMA_IN(qdma, addr, 32);
पूर्ण

अटल व्योम qdma_ग_लिखोl(काष्ठा fsl_qdma_engine *qdma, u32 val,
			व्योम __iomem *addr)
अणु
	FSL_DMA_OUT(qdma, addr, val, 32);
पूर्ण

अटल काष्ठा fsl_qdma_chan *to_fsl_qdma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा fsl_qdma_chan, vchan.chan);
पूर्ण

अटल काष्ठा fsl_qdma_comp *to_fsl_qdma_comp(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा fsl_qdma_comp, vdesc);
पूर्ण

अटल व्योम fsl_qdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);
	काष्ठा fsl_qdma_queue *fsl_queue = fsl_chan->queue;
	काष्ठा fsl_qdma_engine *fsl_qdma = fsl_chan->qdma;
	काष्ठा fsl_qdma_comp *comp_temp, *_comp_temp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	vchan_get_all_descriptors(&fsl_chan->vchan, &head);
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&fsl_chan->vchan, &head);

	अगर (!fsl_queue->comp_pool && !fsl_queue->desc_pool)
		वापस;

	list_क्रम_each_entry_safe(comp_temp, _comp_temp,
				 &fsl_queue->comp_used,	list) अणु
		dma_pool_मुक्त(fsl_queue->comp_pool,
			      comp_temp->virt_addr,
			      comp_temp->bus_addr);
		dma_pool_मुक्त(fsl_queue->desc_pool,
			      comp_temp->desc_virt_addr,
			      comp_temp->desc_bus_addr);
		list_del(&comp_temp->list);
		kमुक्त(comp_temp);
	पूर्ण

	list_क्रम_each_entry_safe(comp_temp, _comp_temp,
				 &fsl_queue->comp_मुक्त, list) अणु
		dma_pool_मुक्त(fsl_queue->comp_pool,
			      comp_temp->virt_addr,
			      comp_temp->bus_addr);
		dma_pool_मुक्त(fsl_queue->desc_pool,
			      comp_temp->desc_virt_addr,
			      comp_temp->desc_bus_addr);
		list_del(&comp_temp->list);
		kमुक्त(comp_temp);
	पूर्ण

	dma_pool_destroy(fsl_queue->comp_pool);
	dma_pool_destroy(fsl_queue->desc_pool);

	fsl_qdma->desc_allocated--;
	fsl_queue->comp_pool = शून्य;
	fsl_queue->desc_pool = शून्य;
पूर्ण

अटल व्योम fsl_qdma_comp_fill_स_नकल(काष्ठा fsl_qdma_comp *fsl_comp,
				      dma_addr_t dst, dma_addr_t src, u32 len)
अणु
	u32 cmd;
	काष्ठा fsl_qdma_क्रमmat *sdf, *ddf;
	काष्ठा fsl_qdma_क्रमmat *ccdf, *csgf_desc, *csgf_src, *csgf_dest;

	ccdf = fsl_comp->virt_addr;
	csgf_desc = fsl_comp->virt_addr + 1;
	csgf_src = fsl_comp->virt_addr + 2;
	csgf_dest = fsl_comp->virt_addr + 3;
	sdf = fsl_comp->desc_virt_addr;
	ddf = fsl_comp->desc_virt_addr + 1;

	स_रखो(fsl_comp->virt_addr, 0, FSL_QDMA_COMMAND_BUFFER_SIZE);
	स_रखो(fsl_comp->desc_virt_addr, 0, FSL_QDMA_DESCRIPTOR_BUFFER_SIZE);
	/* Head Command Descriptor(Frame Descriptor) */
	qdma_desc_addr_set64(ccdf, fsl_comp->bus_addr + 16);
	qdma_ccdf_set_क्रमmat(ccdf, qdma_ccdf_get_offset(ccdf));
	qdma_ccdf_set_ser(ccdf, qdma_ccdf_get_status(ccdf));
	/* Status notअगरication is enqueued to status queue. */
	/* Compound Command Descriptor(Frame List Table) */
	qdma_desc_addr_set64(csgf_desc, fsl_comp->desc_bus_addr);
	/* It must be 32 as Compound S/G Descriptor */
	qdma_csgf_set_len(csgf_desc, 32);
	qdma_desc_addr_set64(csgf_src, src);
	qdma_csgf_set_len(csgf_src, len);
	qdma_desc_addr_set64(csgf_dest, dst);
	qdma_csgf_set_len(csgf_dest, len);
	/* This entry is the last entry. */
	qdma_csgf_set_f(csgf_dest, len);
	/* Descriptor Buffer */
	cmd = cpu_to_le32(FSL_QDMA_CMD_RWTTYPE <<
			  FSL_QDMA_CMD_RWTTYPE_OFFSET);
	sdf->data = QDMA_SDDF_CMD(cmd);

	cmd = cpu_to_le32(FSL_QDMA_CMD_RWTTYPE <<
			  FSL_QDMA_CMD_RWTTYPE_OFFSET);
	cmd |= cpu_to_le32(FSL_QDMA_CMD_LWC << FSL_QDMA_CMD_LWC_OFFSET);
	ddf->data = QDMA_SDDF_CMD(cmd);
पूर्ण

/*
 * Pre-request full command descriptor क्रम enqueue.
 */
अटल पूर्णांक fsl_qdma_pre_request_enqueue_desc(काष्ठा fsl_qdma_queue *queue)
अणु
	पूर्णांक i;
	काष्ठा fsl_qdma_comp *comp_temp, *_comp_temp;

	क्रम (i = 0; i < queue->n_cq + FSL_COMMAND_QUEUE_OVERFLLOW; i++) अणु
		comp_temp = kzalloc(माप(*comp_temp), GFP_KERNEL);
		अगर (!comp_temp)
			जाओ err_alloc;
		comp_temp->virt_addr =
			dma_pool_alloc(queue->comp_pool, GFP_KERNEL,
				       &comp_temp->bus_addr);
		अगर (!comp_temp->virt_addr)
			जाओ err_dma_alloc;

		comp_temp->desc_virt_addr =
			dma_pool_alloc(queue->desc_pool, GFP_KERNEL,
				       &comp_temp->desc_bus_addr);
		अगर (!comp_temp->desc_virt_addr)
			जाओ err_desc_dma_alloc;

		list_add_tail(&comp_temp->list, &queue->comp_मुक्त);
	पूर्ण

	वापस 0;

err_desc_dma_alloc:
	dma_pool_मुक्त(queue->comp_pool, comp_temp->virt_addr,
		      comp_temp->bus_addr);

err_dma_alloc:
	kमुक्त(comp_temp);

err_alloc:
	list_क्रम_each_entry_safe(comp_temp, _comp_temp,
				 &queue->comp_मुक्त, list) अणु
		अगर (comp_temp->virt_addr)
			dma_pool_मुक्त(queue->comp_pool,
				      comp_temp->virt_addr,
				      comp_temp->bus_addr);
		अगर (comp_temp->desc_virt_addr)
			dma_pool_मुक्त(queue->desc_pool,
				      comp_temp->desc_virt_addr,
				      comp_temp->desc_bus_addr);

		list_del(&comp_temp->list);
		kमुक्त(comp_temp);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/*
 * Request a command descriptor क्रम enqueue.
 */
अटल काष्ठा fsl_qdma_comp
*fsl_qdma_request_enqueue_desc(काष्ठा fsl_qdma_chan *fsl_chan)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fsl_qdma_comp *comp_temp;
	पूर्णांक समयout = FSL_QDMA_COMP_TIMEOUT;
	काष्ठा fsl_qdma_queue *queue = fsl_chan->queue;

	जबतक (समयout--) अणु
		spin_lock_irqsave(&queue->queue_lock, flags);
		अगर (!list_empty(&queue->comp_मुक्त)) अणु
			comp_temp = list_first_entry(&queue->comp_मुक्त,
						     काष्ठा fsl_qdma_comp,
						     list);
			list_del(&comp_temp->list);

			spin_unlock_irqrestore(&queue->queue_lock, flags);
			comp_temp->qchan = fsl_chan;
			वापस comp_temp;
		पूर्ण
		spin_unlock_irqrestore(&queue->queue_lock, flags);
		udelay(1);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा fsl_qdma_queue
*fsl_qdma_alloc_queue_resources(काष्ठा platक्रमm_device *pdev,
				काष्ठा fsl_qdma_engine *fsl_qdma)
अणु
	पूर्णांक ret, len, i, j;
	पूर्णांक queue_num, block_number;
	अचिन्हित पूर्णांक queue_size[FSL_QDMA_QUEUE_MAX];
	काष्ठा fsl_qdma_queue *queue_head, *queue_temp;

	queue_num = fsl_qdma->n_queues;
	block_number = fsl_qdma->block_number;

	अगर (queue_num > FSL_QDMA_QUEUE_MAX)
		queue_num = FSL_QDMA_QUEUE_MAX;
	len = माप(*queue_head) * queue_num * block_number;
	queue_head = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!queue_head)
		वापस शून्य;

	ret = device_property_पढ़ो_u32_array(&pdev->dev, "queue-sizes",
					     queue_size, queue_num);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get queue-sizes.\n");
		वापस शून्य;
	पूर्ण
	क्रम (j = 0; j < block_number; j++) अणु
		क्रम (i = 0; i < queue_num; i++) अणु
			अगर (queue_size[i] > FSL_QDMA_CIRCULAR_DESC_SIZE_MAX ||
			    queue_size[i] < FSL_QDMA_CIRCULAR_DESC_SIZE_MIN) अणु
				dev_err(&pdev->dev,
					"Get wrong queue-sizes.\n");
				वापस शून्य;
			पूर्ण
			queue_temp = queue_head + i + (j * queue_num);

			queue_temp->cq =
			dma_alloc_coherent(&pdev->dev,
					   माप(काष्ठा fsl_qdma_क्रमmat) *
					   queue_size[i],
					   &queue_temp->bus_addr,
					   GFP_KERNEL);
			अगर (!queue_temp->cq)
				वापस शून्य;
			queue_temp->block_base = fsl_qdma->block_base +
				FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma, j);
			queue_temp->n_cq = queue_size[i];
			queue_temp->id = i;
			queue_temp->virt_head = queue_temp->cq;
			queue_temp->virt_tail = queue_temp->cq;
			/*
			 * List क्रम queue command buffer
			 */
			INIT_LIST_HEAD(&queue_temp->comp_used);
			spin_lock_init(&queue_temp->queue_lock);
		पूर्ण
	पूर्ण
	वापस queue_head;
पूर्ण

अटल काष्ठा fsl_qdma_queue
*fsl_qdma_prep_status_queue(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status_size;
	काष्ठा fsl_qdma_queue *status_head;
	काष्ठा device_node *np = pdev->dev.of_node;

	ret = of_property_पढ़ो_u32(np, "status-sizes", &status_size);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get status-sizes.\n");
		वापस शून्य;
	पूर्ण
	अगर (status_size > FSL_QDMA_CIRCULAR_DESC_SIZE_MAX ||
	    status_size < FSL_QDMA_CIRCULAR_DESC_SIZE_MIN) अणु
		dev_err(&pdev->dev, "Get wrong status_size.\n");
		वापस शून्य;
	पूर्ण
	status_head = devm_kzalloc(&pdev->dev,
				   माप(*status_head), GFP_KERNEL);
	अगर (!status_head)
		वापस शून्य;

	/*
	 * Buffer क्रम queue command
	 */
	status_head->cq = dma_alloc_coherent(&pdev->dev,
					     माप(काष्ठा fsl_qdma_क्रमmat) *
					     status_size,
					     &status_head->bus_addr,
					     GFP_KERNEL);
	अगर (!status_head->cq) अणु
		devm_kमुक्त(&pdev->dev, status_head);
		वापस शून्य;
	पूर्ण
	status_head->n_cq = status_size;
	status_head->virt_head = status_head->cq;
	status_head->virt_tail = status_head->cq;
	status_head->comp_pool = शून्य;

	वापस status_head;
पूर्ण

अटल पूर्णांक fsl_qdma_halt(काष्ठा fsl_qdma_engine *fsl_qdma)
अणु
	u32 reg;
	पूर्णांक i, j, count = FSL_QDMA_HALT_COUNT;
	व्योम __iomem *block, *ctrl = fsl_qdma->ctrl_base;

	/* Disable the command queue and रुको क्रम idle state. */
	reg = qdma_पढ़ोl(fsl_qdma, ctrl + FSL_QDMA_DMR);
	reg |= FSL_QDMA_DMR_DQD;
	qdma_ग_लिखोl(fsl_qdma, reg, ctrl + FSL_QDMA_DMR);
	क्रम (j = 0; j < fsl_qdma->block_number; j++) अणु
		block = fsl_qdma->block_base +
			FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma, j);
		क्रम (i = 0; i < FSL_QDMA_QUEUE_NUM_MAX; i++)
			qdma_ग_लिखोl(fsl_qdma, 0, block + FSL_QDMA_BCQMR(i));
	पूर्ण
	जबतक (1) अणु
		reg = qdma_पढ़ोl(fsl_qdma, ctrl + FSL_QDMA_DSR);
		अगर (!(reg & FSL_QDMA_DSR_DB))
			अवरोध;
		अगर (count-- < 0)
			वापस -EBUSY;
		udelay(100);
	पूर्ण

	क्रम (j = 0; j < fsl_qdma->block_number; j++) अणु
		block = fsl_qdma->block_base +
			FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma, j);

		/* Disable status queue. */
		qdma_ग_लिखोl(fsl_qdma, 0, block + FSL_QDMA_BSQMR);

		/*
		 * clear the command queue पूर्णांकerrupt detect रेजिस्टर क्रम
		 * all queues.
		 */
		qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_BCQIDR_CLEAR,
			    block + FSL_QDMA_BCQIDR(0));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fsl_qdma_queue_transfer_complete(काष्ठा fsl_qdma_engine *fsl_qdma,
				 व्योम *block,
				 पूर्णांक id)
अणु
	bool duplicate;
	u32 reg, i, count;
	u8 completion_status;
	काष्ठा fsl_qdma_queue *temp_queue;
	काष्ठा fsl_qdma_क्रमmat *status_addr;
	काष्ठा fsl_qdma_comp *fsl_comp = शून्य;
	काष्ठा fsl_qdma_queue *fsl_queue = fsl_qdma->queue;
	काष्ठा fsl_qdma_queue *fsl_status = fsl_qdma->status[id];

	count = FSL_QDMA_MAX_SIZE;

	जबतक (count--) अणु
		duplicate = 0;
		reg = qdma_पढ़ोl(fsl_qdma, block + FSL_QDMA_BSQSR);
		अगर (reg & FSL_QDMA_BSQSR_QE)
			वापस 0;

		status_addr = fsl_status->virt_head;

		अगर (qdma_ccdf_get_queue(status_addr) ==
		   __this_cpu_पढ़ो(pre.queue) &&
			qdma_ccdf_addr_get64(status_addr) ==
			__this_cpu_पढ़ो(pre.addr))
			duplicate = 1;
		i = qdma_ccdf_get_queue(status_addr) +
			id * fsl_qdma->n_queues;
		__this_cpu_ग_लिखो(pre.addr, qdma_ccdf_addr_get64(status_addr));
		__this_cpu_ग_लिखो(pre.queue, qdma_ccdf_get_queue(status_addr));
		temp_queue = fsl_queue + i;

		spin_lock(&temp_queue->queue_lock);
		अगर (list_empty(&temp_queue->comp_used)) अणु
			अगर (!duplicate) अणु
				spin_unlock(&temp_queue->queue_lock);
				वापस -EAGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			fsl_comp = list_first_entry(&temp_queue->comp_used,
						    काष्ठा fsl_qdma_comp, list);
			अगर (fsl_comp->bus_addr + 16 !=
				__this_cpu_पढ़ो(pre.addr)) अणु
				अगर (!duplicate) अणु
					spin_unlock(&temp_queue->queue_lock);
					वापस -EAGAIN;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (duplicate) अणु
			reg = qdma_पढ़ोl(fsl_qdma, block + FSL_QDMA_BSQMR);
			reg |= FSL_QDMA_BSQMR_DI;
			qdma_desc_addr_set64(status_addr, 0x0);
			fsl_status->virt_head++;
			अगर (fsl_status->virt_head == fsl_status->cq
						   + fsl_status->n_cq)
				fsl_status->virt_head = fsl_status->cq;
			qdma_ग_लिखोl(fsl_qdma, reg, block + FSL_QDMA_BSQMR);
			spin_unlock(&temp_queue->queue_lock);
			जारी;
		पूर्ण
		list_del(&fsl_comp->list);

		completion_status = qdma_ccdf_get_status(status_addr);

		reg = qdma_पढ़ोl(fsl_qdma, block + FSL_QDMA_BSQMR);
		reg |= FSL_QDMA_BSQMR_DI;
		qdma_desc_addr_set64(status_addr, 0x0);
		fsl_status->virt_head++;
		अगर (fsl_status->virt_head == fsl_status->cq + fsl_status->n_cq)
			fsl_status->virt_head = fsl_status->cq;
		qdma_ग_लिखोl(fsl_qdma, reg, block + FSL_QDMA_BSQMR);
		spin_unlock(&temp_queue->queue_lock);

		/* The completion_status is evaluated here
		 * (outside of spin lock)
		 */
		अगर (completion_status) अणु
			/* A completion error occurred! */
			अगर (completion_status & QDMA_CCDF_STATUS_WTE) अणु
				/* Write transaction error */
				fsl_comp->vdesc.tx_result.result =
					DMA_TRANS_WRITE_FAILED;
			पूर्ण अन्यथा अगर (completion_status & QDMA_CCDF_STATUS_RTE) अणु
				/* Read transaction error */
				fsl_comp->vdesc.tx_result.result =
					DMA_TRANS_READ_FAILED;
			पूर्ण अन्यथा अणु
				/* Command/source/destination
				 * description error
				 */
				fsl_comp->vdesc.tx_result.result =
					DMA_TRANS_ABORTED;
				dev_err(fsl_qdma->dma_dev.dev,
					"DMA status descriptor error %x\n",
					completion_status);
			पूर्ण
		पूर्ण

		spin_lock(&fsl_comp->qchan->vchan.lock);
		vchan_cookie_complete(&fsl_comp->vdesc);
		fsl_comp->qchan->status = DMA_COMPLETE;
		spin_unlock(&fsl_comp->qchan->vchan.lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t fsl_qdma_error_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक पूर्णांकr;
	काष्ठा fsl_qdma_engine *fsl_qdma = dev_id;
	व्योम __iomem *status = fsl_qdma->status_base;
	अचिन्हित पूर्णांक decfdw0r;
	अचिन्हित पूर्णांक decfdw1r;
	अचिन्हित पूर्णांक decfdw2r;
	अचिन्हित पूर्णांक decfdw3r;

	पूर्णांकr = qdma_पढ़ोl(fsl_qdma, status + FSL_QDMA_DEDR);

	अगर (पूर्णांकr) अणु
		decfdw0r = qdma_पढ़ोl(fsl_qdma, status + FSL_QDMA_DECFDW0R);
		decfdw1r = qdma_पढ़ोl(fsl_qdma, status + FSL_QDMA_DECFDW1R);
		decfdw2r = qdma_पढ़ोl(fsl_qdma, status + FSL_QDMA_DECFDW2R);
		decfdw3r = qdma_पढ़ोl(fsl_qdma, status + FSL_QDMA_DECFDW3R);
		dev_err(fsl_qdma->dma_dev.dev,
			"DMA transaction error! (%x: %x-%x-%x-%x)\n",
			पूर्णांकr, decfdw0r, decfdw1r, decfdw2r, decfdw3r);
	पूर्ण

	qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_DEDR_CLEAR, status + FSL_QDMA_DEDR);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fsl_qdma_queue_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक id;
	अचिन्हित पूर्णांक पूर्णांकr, reg;
	काष्ठा fsl_qdma_engine *fsl_qdma = dev_id;
	व्योम __iomem *block, *ctrl = fsl_qdma->ctrl_base;

	id = irq - fsl_qdma->irq_base;
	अगर (id < 0 && id > fsl_qdma->block_number) अणु
		dev_err(fsl_qdma->dma_dev.dev,
			"irq %d is wrong irq_base is %d\n",
			irq, fsl_qdma->irq_base);
	पूर्ण

	block = fsl_qdma->block_base +
		FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma, id);

	पूर्णांकr = qdma_पढ़ोl(fsl_qdma, block + FSL_QDMA_BCQIDR(0));

	अगर ((पूर्णांकr & FSL_QDMA_CQIDR_SQT) != 0)
		पूर्णांकr = fsl_qdma_queue_transfer_complete(fsl_qdma, block, id);

	अगर (पूर्णांकr != 0) अणु
		reg = qdma_पढ़ोl(fsl_qdma, ctrl + FSL_QDMA_DMR);
		reg |= FSL_QDMA_DMR_DQD;
		qdma_ग_लिखोl(fsl_qdma, reg, ctrl + FSL_QDMA_DMR);
		qdma_ग_लिखोl(fsl_qdma, 0, block + FSL_QDMA_BCQIER(0));
		dev_err(fsl_qdma->dma_dev.dev, "QDMA: status err!\n");
	पूर्ण

	/* Clear all detected events and पूर्णांकerrupts. */
	qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_BCQIDR_CLEAR,
		    block + FSL_QDMA_BCQIDR(0));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
fsl_qdma_irq_init(काष्ठा platक्रमm_device *pdev,
		  काष्ठा fsl_qdma_engine *fsl_qdma)
अणु
	पूर्णांक i;
	पूर्णांक cpu;
	पूर्णांक ret;
	अक्षर irq_name[20];

	fsl_qdma->error_irq =
		platक्रमm_get_irq_byname(pdev, "qdma-error");
	अगर (fsl_qdma->error_irq < 0)
		वापस fsl_qdma->error_irq;

	ret = devm_request_irq(&pdev->dev, fsl_qdma->error_irq,
			       fsl_qdma_error_handler, 0,
			       "qDMA error", fsl_qdma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't register qDMA controller IRQ.\n");
		वापस  ret;
	पूर्ण

	क्रम (i = 0; i < fsl_qdma->block_number; i++) अणु
		प्र_लिखो(irq_name, "qdma-queue%d", i);
		fsl_qdma->queue_irq[i] =
				platक्रमm_get_irq_byname(pdev, irq_name);

		अगर (fsl_qdma->queue_irq[i] < 0)
			वापस fsl_qdma->queue_irq[i];

		ret = devm_request_irq(&pdev->dev,
				       fsl_qdma->queue_irq[i],
				       fsl_qdma_queue_handler,
				       0,
				       "qDMA queue",
				       fsl_qdma);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Can't register qDMA queue IRQ.\n");
			वापस  ret;
		पूर्ण

		cpu = i % num_online_cpus();
		ret = irq_set_affinity_hपूर्णांक(fsl_qdma->queue_irq[i],
					    get_cpu_mask(cpu));
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Can't set cpu %d affinity to IRQ %d.\n",
				cpu,
				fsl_qdma->queue_irq[i]);
			वापस  ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_qdma_irq_निकास(काष्ठा platक्रमm_device *pdev,
			      काष्ठा fsl_qdma_engine *fsl_qdma)
अणु
	पूर्णांक i;

	devm_मुक्त_irq(&pdev->dev, fsl_qdma->error_irq, fsl_qdma);
	क्रम (i = 0; i < fsl_qdma->block_number; i++)
		devm_मुक्त_irq(&pdev->dev, fsl_qdma->queue_irq[i], fsl_qdma);
पूर्ण

अटल पूर्णांक fsl_qdma_reg_init(काष्ठा fsl_qdma_engine *fsl_qdma)
अणु
	u32 reg;
	पूर्णांक i, j, ret;
	काष्ठा fsl_qdma_queue *temp;
	व्योम __iomem *status = fsl_qdma->status_base;
	व्योम __iomem *block, *ctrl = fsl_qdma->ctrl_base;
	काष्ठा fsl_qdma_queue *fsl_queue = fsl_qdma->queue;

	/* Try to halt the qDMA engine first. */
	ret = fsl_qdma_halt(fsl_qdma);
	अगर (ret) अणु
		dev_err(fsl_qdma->dma_dev.dev, "DMA halt failed!");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < fsl_qdma->block_number; i++) अणु
		/*
		 * Clear the command queue पूर्णांकerrupt detect रेजिस्टर क्रम
		 * all queues.
		 */

		block = fsl_qdma->block_base +
			FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma, i);
		qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_BCQIDR_CLEAR,
			    block + FSL_QDMA_BCQIDR(0));
	पूर्ण

	क्रम (j = 0; j < fsl_qdma->block_number; j++) अणु
		block = fsl_qdma->block_base +
			FSL_QDMA_BLOCK_BASE_OFFSET(fsl_qdma, j);
		क्रम (i = 0; i < fsl_qdma->n_queues; i++) अणु
			temp = fsl_queue + i + (j * fsl_qdma->n_queues);
			/*
			 * Initialize Command Queue रेजिस्टरs to
			 * poपूर्णांक to the first
			 * command descriptor in memory.
			 * Dequeue Poपूर्णांकer Address Registers
			 * Enqueue Poपूर्णांकer Address Registers
			 */

			qdma_ग_लिखोl(fsl_qdma, temp->bus_addr,
				    block + FSL_QDMA_BCQDPA_SADDR(i));
			qdma_ग_लिखोl(fsl_qdma, temp->bus_addr,
				    block + FSL_QDMA_BCQEPA_SADDR(i));

			/* Initialize the queue mode. */
			reg = FSL_QDMA_BCQMR_EN;
			reg |= FSL_QDMA_BCQMR_CD_THLD(ilog2(temp->n_cq) - 4);
			reg |= FSL_QDMA_BCQMR_CQ_SIZE(ilog2(temp->n_cq) - 6);
			qdma_ग_लिखोl(fsl_qdma, reg, block + FSL_QDMA_BCQMR(i));
		पूर्ण

		/*
		 * Workaround क्रम erratum: ERR010812.
		 * We must enable XOFF to aव्योम the enqueue rejection occurs.
		 * Setting SQCCMR ENTER_WM to 0x20.
		 */

		qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_SQCCMR_ENTER_WM,
			    block + FSL_QDMA_SQCCMR);

		/*
		 * Initialize status queue रेजिस्टरs to poपूर्णांक to the first
		 * command descriptor in memory.
		 * Dequeue Poपूर्णांकer Address Registers
		 * Enqueue Poपूर्णांकer Address Registers
		 */

		qdma_ग_लिखोl(fsl_qdma, fsl_qdma->status[j]->bus_addr,
			    block + FSL_QDMA_SQEPAR);
		qdma_ग_लिखोl(fsl_qdma, fsl_qdma->status[j]->bus_addr,
			    block + FSL_QDMA_SQDPAR);
		/* Initialize status queue पूर्णांकerrupt. */
		qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_BCQIER_CQTIE,
			    block + FSL_QDMA_BCQIER(0));
		qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_BSQICR_ICEN |
				   FSL_QDMA_BSQICR_ICST(5) | 0x8000,
				   block + FSL_QDMA_BSQICR);
		qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_CQIER_MEIE |
				   FSL_QDMA_CQIER_TEIE,
				   block + FSL_QDMA_CQIER);

		/* Initialize the status queue mode. */
		reg = FSL_QDMA_BSQMR_EN;
		reg |= FSL_QDMA_BSQMR_CQ_SIZE(ilog2
			(fsl_qdma->status[j]->n_cq) - 6);

		qdma_ग_लिखोl(fsl_qdma, reg, block + FSL_QDMA_BSQMR);
		reg = qdma_पढ़ोl(fsl_qdma, block + FSL_QDMA_BSQMR);
	पूर्ण

	/* Initialize controller पूर्णांकerrupt रेजिस्टर. */
	qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_DEDR_CLEAR, status + FSL_QDMA_DEDR);
	qdma_ग_लिखोl(fsl_qdma, FSL_QDMA_DEIER_CLEAR, status + FSL_QDMA_DEIER);

	reg = qdma_पढ़ोl(fsl_qdma, ctrl + FSL_QDMA_DMR);
	reg &= ~FSL_QDMA_DMR_DQD;
	qdma_ग_लिखोl(fsl_qdma, reg, ctrl + FSL_QDMA_DMR);

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
fsl_qdma_prep_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dst,
		     dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_qdma_comp *fsl_comp;
	काष्ठा fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);

	fsl_comp = fsl_qdma_request_enqueue_desc(fsl_chan);

	अगर (!fsl_comp)
		वापस शून्य;

	fsl_qdma_comp_fill_स_नकल(fsl_comp, dst, src, len);

	वापस vchan_tx_prep(&fsl_chan->vchan, &fsl_comp->vdesc, flags);
पूर्ण

अटल व्योम fsl_qdma_enqueue_desc(काष्ठा fsl_qdma_chan *fsl_chan)
अणु
	u32 reg;
	काष्ठा virt_dma_desc *vdesc;
	काष्ठा fsl_qdma_comp *fsl_comp;
	काष्ठा fsl_qdma_queue *fsl_queue = fsl_chan->queue;
	व्योम __iomem *block = fsl_queue->block_base;

	reg = qdma_पढ़ोl(fsl_chan->qdma, block + FSL_QDMA_BCQSR(fsl_queue->id));
	अगर (reg & (FSL_QDMA_BCQSR_QF | FSL_QDMA_BCQSR_XOFF))
		वापस;
	vdesc = vchan_next_desc(&fsl_chan->vchan);
	अगर (!vdesc)
		वापस;
	list_del(&vdesc->node);
	fsl_comp = to_fsl_qdma_comp(vdesc);

	स_नकल(fsl_queue->virt_head++,
	       fsl_comp->virt_addr, माप(काष्ठा fsl_qdma_क्रमmat));
	अगर (fsl_queue->virt_head == fsl_queue->cq + fsl_queue->n_cq)
		fsl_queue->virt_head = fsl_queue->cq;

	list_add_tail(&fsl_comp->list, &fsl_queue->comp_used);
	barrier();
	reg = qdma_पढ़ोl(fsl_chan->qdma, block + FSL_QDMA_BCQMR(fsl_queue->id));
	reg |= FSL_QDMA_BCQMR_EI;
	qdma_ग_लिखोl(fsl_chan->qdma, reg, block + FSL_QDMA_BCQMR(fsl_queue->id));
	fsl_chan->status = DMA_IN_PROGRESS;
पूर्ण

अटल व्योम fsl_qdma_मुक्त_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fsl_qdma_comp *fsl_comp;
	काष्ठा fsl_qdma_queue *fsl_queue;

	fsl_comp = to_fsl_qdma_comp(vdesc);
	fsl_queue = fsl_comp->qchan->queue;

	spin_lock_irqsave(&fsl_queue->queue_lock, flags);
	list_add_tail(&fsl_comp->list, &fsl_queue->comp_मुक्त);
	spin_unlock_irqrestore(&fsl_queue->queue_lock, flags);
पूर्ण

अटल व्योम fsl_qdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);
	काष्ठा fsl_qdma_queue *fsl_queue = fsl_chan->queue;

	spin_lock_irqsave(&fsl_queue->queue_lock, flags);
	spin_lock(&fsl_chan->vchan.lock);
	अगर (vchan_issue_pending(&fsl_chan->vchan))
		fsl_qdma_enqueue_desc(fsl_chan);
	spin_unlock(&fsl_chan->vchan.lock);
	spin_unlock_irqrestore(&fsl_queue->queue_lock, flags);
पूर्ण

अटल व्योम fsl_qdma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);

	vchan_synchronize(&fsl_chan->vchan);
पूर्ण

अटल पूर्णांक fsl_qdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	LIST_HEAD(head);
	अचिन्हित दीर्घ flags;
	काष्ठा fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	vchan_get_all_descriptors(&fsl_chan->vchan, &head);
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&fsl_chan->vchan, &head);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_qdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	पूर्णांक ret;
	काष्ठा fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);
	काष्ठा fsl_qdma_engine *fsl_qdma = fsl_chan->qdma;
	काष्ठा fsl_qdma_queue *fsl_queue = fsl_chan->queue;

	अगर (fsl_queue->comp_pool && fsl_queue->desc_pool)
		वापस fsl_qdma->desc_allocated;

	INIT_LIST_HEAD(&fsl_queue->comp_मुक्त);

	/*
	 * The dma pool क्रम queue command buffer
	 */
	fsl_queue->comp_pool =
	dma_pool_create("comp_pool",
			chan->device->dev,
			FSL_QDMA_COMMAND_BUFFER_SIZE,
			64, 0);
	अगर (!fsl_queue->comp_pool)
		वापस -ENOMEM;

	/*
	 * The dma pool क्रम Descriptor(SD/DD) buffer
	 */
	fsl_queue->desc_pool =
	dma_pool_create("desc_pool",
			chan->device->dev,
			FSL_QDMA_DESCRIPTOR_BUFFER_SIZE,
			32, 0);
	अगर (!fsl_queue->desc_pool)
		जाओ err_desc_pool;

	ret = fsl_qdma_pre_request_enqueue_desc(fsl_queue);
	अगर (ret) अणु
		dev_err(chan->device->dev,
			"failed to alloc dma buffer for S/G descriptor\n");
		जाओ err_mem;
	पूर्ण

	fsl_qdma->desc_allocated++;
	वापस fsl_qdma->desc_allocated;

err_mem:
	dma_pool_destroy(fsl_queue->desc_pool);
err_desc_pool:
	dma_pool_destroy(fsl_queue->comp_pool);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक fsl_qdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i;
	पूर्णांक blk_num, blk_off;
	u32 len, chans, queues;
	काष्ठा resource *res;
	काष्ठा fsl_qdma_chan *fsl_chan;
	काष्ठा fsl_qdma_engine *fsl_qdma;
	काष्ठा device_node *np = pdev->dev.of_node;

	ret = of_property_पढ़ो_u32(np, "dma-channels", &chans);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get dma-channels.\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "block-offset", &blk_off);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get block-offset.\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "block-number", &blk_num);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get block-number.\n");
		वापस ret;
	पूर्ण

	blk_num = min_t(पूर्णांक, blk_num, num_online_cpus());

	len = माप(*fsl_qdma);
	fsl_qdma = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!fsl_qdma)
		वापस -ENOMEM;

	len = माप(*fsl_chan) * chans;
	fsl_qdma->chans = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!fsl_qdma->chans)
		वापस -ENOMEM;

	len = माप(काष्ठा fsl_qdma_queue *) * blk_num;
	fsl_qdma->status = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!fsl_qdma->status)
		वापस -ENOMEM;

	len = माप(पूर्णांक) * blk_num;
	fsl_qdma->queue_irq = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!fsl_qdma->queue_irq)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(np, "fsl,dma-queues", &queues);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get queues.\n");
		वापस ret;
	पूर्ण

	fsl_qdma->desc_allocated = 0;
	fsl_qdma->n_chans = chans;
	fsl_qdma->n_queues = queues;
	fsl_qdma->block_number = blk_num;
	fsl_qdma->block_offset = blk_off;

	mutex_init(&fsl_qdma->fsl_qdma_mutex);

	क्रम (i = 0; i < fsl_qdma->block_number; i++) अणु
		fsl_qdma->status[i] = fsl_qdma_prep_status_queue(pdev);
		अगर (!fsl_qdma->status[i])
			वापस -ENOMEM;
	पूर्ण
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fsl_qdma->ctrl_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fsl_qdma->ctrl_base))
		वापस PTR_ERR(fsl_qdma->ctrl_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	fsl_qdma->status_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fsl_qdma->status_base))
		वापस PTR_ERR(fsl_qdma->status_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	fsl_qdma->block_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fsl_qdma->block_base))
		वापस PTR_ERR(fsl_qdma->block_base);
	fsl_qdma->queue = fsl_qdma_alloc_queue_resources(pdev, fsl_qdma);
	अगर (!fsl_qdma->queue)
		वापस -ENOMEM;

	ret = fsl_qdma_irq_init(pdev, fsl_qdma);
	अगर (ret)
		वापस ret;

	fsl_qdma->irq_base = platक्रमm_get_irq_byname(pdev, "qdma-queue0");
	अगर (fsl_qdma->irq_base < 0)
		वापस fsl_qdma->irq_base;

	fsl_qdma->feature = of_property_पढ़ो_bool(np, "big-endian");
	INIT_LIST_HEAD(&fsl_qdma->dma_dev.channels);

	क्रम (i = 0; i < fsl_qdma->n_chans; i++) अणु
		काष्ठा fsl_qdma_chan *fsl_chan = &fsl_qdma->chans[i];

		fsl_chan->qdma = fsl_qdma;
		fsl_chan->queue = fsl_qdma->queue + i % (fsl_qdma->n_queues *
							fsl_qdma->block_number);
		fsl_chan->vchan.desc_मुक्त = fsl_qdma_मुक्त_desc;
		vchan_init(&fsl_chan->vchan, &fsl_qdma->dma_dev);
	पूर्ण

	dma_cap_set(DMA_MEMCPY, fsl_qdma->dma_dev.cap_mask);

	fsl_qdma->dma_dev.dev = &pdev->dev;
	fsl_qdma->dma_dev.device_मुक्त_chan_resources =
		fsl_qdma_मुक्त_chan_resources;
	fsl_qdma->dma_dev.device_alloc_chan_resources =
		fsl_qdma_alloc_chan_resources;
	fsl_qdma->dma_dev.device_tx_status = dma_cookie_status;
	fsl_qdma->dma_dev.device_prep_dma_स_नकल = fsl_qdma_prep_स_नकल;
	fsl_qdma->dma_dev.device_issue_pending = fsl_qdma_issue_pending;
	fsl_qdma->dma_dev.device_synchronize = fsl_qdma_synchronize;
	fsl_qdma->dma_dev.device_terminate_all = fsl_qdma_terminate_all;

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(40));

	platक्रमm_set_drvdata(pdev, fsl_qdma);

	ret = dma_async_device_रेजिस्टर(&fsl_qdma->dma_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Can't register NXP Layerscape qDMA engine.\n");
		वापस ret;
	पूर्ण

	ret = fsl_qdma_reg_init(fsl_qdma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't Initialize the qDMA engine.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_qdma_cleanup_vchan(काष्ठा dma_device *dmadev)
अणु
	काष्ठा fsl_qdma_chan *chan, *_chan;

	list_क्रम_each_entry_safe(chan, _chan,
				 &dmadev->channels, vchan.chan.device_node) अणु
		list_del(&chan->vchan.chan.device_node);
		tasklet_समाप्त(&chan->vchan.task);
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_qdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा fsl_qdma_queue *status;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_qdma_engine *fsl_qdma = platक्रमm_get_drvdata(pdev);

	fsl_qdma_irq_निकास(pdev, fsl_qdma);
	fsl_qdma_cleanup_vchan(&fsl_qdma->dma_dev);
	of_dma_controller_मुक्त(np);
	dma_async_device_unरेजिस्टर(&fsl_qdma->dma_dev);

	क्रम (i = 0; i < fsl_qdma->block_number; i++) अणु
		status = fsl_qdma->status[i];
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा fsl_qdma_क्रमmat) *
				status->n_cq, status->cq, status->bus_addr);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_qdma_dt_ids[] = अणु
	अणु .compatible = "fsl,ls1021a-qdma", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_qdma_dt_ids);

अटल काष्ठा platक्रमm_driver fsl_qdma_driver = अणु
	.driver		= अणु
		.name	= "fsl-qdma",
		.of_match_table = fsl_qdma_dt_ids,
	पूर्ण,
	.probe          = fsl_qdma_probe,
	.हटाओ		= fsl_qdma_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_qdma_driver);

MODULE_ALIAS("platform:fsl-qdma");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("NXP Layerscape qDMA engine driver");
