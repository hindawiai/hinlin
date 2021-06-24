<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2004 - 2009 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित IOATDMA_H
#घोषणा IOATDMA_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/cache.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "registers.h"
#समावेश "hw.h"

#घोषणा IOAT_DMA_VERSION  "5.00"

#घोषणा IOAT_DMA_DCA_ANY_CPU		~0

#घोषणा to_ioatdma_device(dev) container_of(dev, काष्ठा ioatdma_device, dma_dev)
#घोषणा to_dev(ioat_chan) (&(ioat_chan)->ioat_dma->pdev->dev)
#घोषणा to_pdev(ioat_chan) ((ioat_chan)->ioat_dma->pdev)

#घोषणा chan_num(ch) ((पूर्णांक)((ch)->reg_base - (ch)->ioat_dma->reg_base) / 0x80)

/* ioat hardware assumes at least two sources क्रम raid operations */
#घोषणा src_cnt_to_sw(x) ((x) + 2)
#घोषणा src_cnt_to_hw(x) ((x) - 2)
#घोषणा ndest_to_sw(x) ((x) + 1)
#घोषणा ndest_to_hw(x) ((x) - 1)
#घोषणा src16_cnt_to_sw(x) ((x) + 9)
#घोषणा src16_cnt_to_hw(x) ((x) - 9)

/*
 * workaround क्रम IOAT ver.3.0 null descriptor issue
 * (channel वापसs error when size is 0)
 */
#घोषणा शून्य_DESC_BUFFER_SIZE 1

क्रमागत ioat_irq_mode अणु
	IOAT_NOIRQ = 0,
	IOAT_MSIX,
	IOAT_MSI,
	IOAT_INTX
पूर्ण;

/**
 * काष्ठा ioatdma_device - पूर्णांकernal representation of a IOAT device
 * @pdev: PCI-Express device
 * @reg_base: MMIO रेजिस्टर space base address
 * @completion_pool: DMA buffers क्रम completion ops
 * @sed_hw_pool: DMA super descriptor pools
 * @dma_dev: embedded काष्ठा dma_device
 * @version: version of ioatdma device
 * @msix_entries: irq handlers
 * @idx: per channel data
 * @dca: direct cache access context
 * @irq_mode: पूर्णांकerrupt mode (INTX, MSI, MSIX)
 * @cap: पढ़ो DMA capabilities रेजिस्टर
 */
काष्ठा ioatdma_device अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *reg_base;
	काष्ठा dma_pool *completion_pool;
#घोषणा MAX_SED_POOLS	5
	काष्ठा dma_pool *sed_hw_pool[MAX_SED_POOLS];
	काष्ठा dma_device dma_dev;
	u8 version;
#घोषणा IOAT_MAX_CHANS 4
	काष्ठा msix_entry msix_entries[IOAT_MAX_CHANS];
	काष्ठा ioatdma_chan *idx[IOAT_MAX_CHANS];
	काष्ठा dca_provider *dca;
	क्रमागत ioat_irq_mode irq_mode;
	u32 cap;

	/* shaकरोw version क्रम CB3.3 chan reset errata workaround */
	u64 msixtba0;
	u64 msixdata0;
	u32 msixpba;
पूर्ण;

#घोषणा IOAT_MAX_ORDER 16
#घोषणा IOAT_MAX_DESCS (1 << IOAT_MAX_ORDER)
#घोषणा IOAT_CHUNK_SIZE (SZ_512K)
#घोषणा IOAT_DESCS_PER_CHUNK (IOAT_CHUNK_SIZE / IOAT_DESC_SZ)

काष्ठा ioat_descs अणु
	व्योम *virt;
	dma_addr_t hw;
पूर्ण;

काष्ठा ioatdma_chan अणु
	काष्ठा dma_chan dma_chan;
	व्योम __iomem *reg_base;
	dma_addr_t last_completion;
	spinlock_t cleanup_lock;
	अचिन्हित दीर्घ state;
	#घोषणा IOAT_CHAN_DOWN 0
	#घोषणा IOAT_COMPLETION_ACK 1
	#घोषणा IOAT_RESET_PENDING 2
	#घोषणा IOAT_KOBJ_INIT_FAIL 3
	#घोषणा IOAT_RUN 5
	#घोषणा IOAT_CHAN_ACTIVE 6
	काष्ठा समयr_list समयr;
	#घोषणा RESET_DELAY msecs_to_jअगरfies(100)
	काष्ठा ioatdma_device *ioat_dma;
	dma_addr_t completion_dma;
	u64 *completion;
	काष्ठा tasklet_काष्ठा cleanup_task;
	काष्ठा kobject kobj;

/* ioat v2 / v3 channel attributes
 * @xfercap_log; log2 of channel max transfer length (क्रम fast भागision)
 * @head: allocated index
 * @issued: hardware notअगरication poपूर्णांक
 * @tail: cleanup index
 * @dmacount: identical to 'head' except क्रम occasionally resetting to zero
 * @alloc_order: log2 of the number of allocated descriptors
 * @produce: number of descriptors to produce at submit समय
 * @ring: software ring buffer implementation of hardware ring
 * @prep_lock: serializes descriptor preparation (producers)
 */
	माप_प्रकार xfercap_log;
	u16 head;
	u16 issued;
	u16 tail;
	u16 dmacount;
	u16 alloc_order;
	u16 produce;
	काष्ठा ioat_ring_ent **ring;
	spinlock_t prep_lock;
	काष्ठा ioat_descs descs[IOAT_MAX_DESCS / IOAT_DESCS_PER_CHUNK];
	पूर्णांक desc_chunks;
	पूर्णांक पूर्णांकr_coalesce;
	पूर्णांक prev_पूर्णांकr_coalesce;
पूर्ण;

काष्ठा ioat_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा dma_chan *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा dma_chan *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/**
 * काष्ठा ioat_sed_ent - wrapper around super extended hardware descriptor
 * @hw: hardware SED
 * @dma: dma address क्रम the SED
 * @parent: poपूर्णांक to the dma descriptor that's the parent
 * @hw_pool: descriptor pool index
 */
काष्ठा ioat_sed_ent अणु
	काष्ठा ioat_sed_raw_descriptor *hw;
	dma_addr_t dma;
	काष्ठा ioat_ring_ent *parent;
	अचिन्हित पूर्णांक hw_pool;
पूर्ण;

/**
 * काष्ठा ioat_ring_ent - wrapper around hardware descriptor
 * @hw: hardware DMA descriptor (क्रम स_नकल)
 * @xor: hardware xor descriptor
 * @xor_ex: hardware xor extension descriptor
 * @pq: hardware pq descriptor
 * @pq_ex: hardware pq extension descriptor
 * @pqu: hardware pq update descriptor
 * @raw: hardware raw (un-typed) descriptor
 * @txd: the generic software descriptor क्रम all engines
 * @len: total transaction length क्रम unmap
 * @result: asynchronous result of validate operations
 * @id: identअगरier क्रम debug
 * @sed: poपूर्णांकer to super extended descriptor sw desc
 */

काष्ठा ioat_ring_ent अणु
	जोड़ अणु
		काष्ठा ioat_dma_descriptor *hw;
		काष्ठा ioat_xor_descriptor *xor;
		काष्ठा ioat_xor_ext_descriptor *xor_ex;
		काष्ठा ioat_pq_descriptor *pq;
		काष्ठा ioat_pq_ext_descriptor *pq_ex;
		काष्ठा ioat_pq_update_descriptor *pqu;
		काष्ठा ioat_raw_descriptor *raw;
	पूर्ण;
	माप_प्रकार len;
	काष्ठा dma_async_tx_descriptor txd;
	क्रमागत sum_check_flags *result;
	#अगर_घोषित DEBUG
	पूर्णांक id;
	#पूर्ण_अगर
	काष्ठा ioat_sed_ent *sed;
पूर्ण;

बाह्य स्थिर काष्ठा sysfs_ops ioat_sysfs_ops;
बाह्य काष्ठा ioat_sysfs_entry ioat_version_attr;
बाह्य काष्ठा ioat_sysfs_entry ioat_cap_attr;
बाह्य पूर्णांक ioat_pending_level;
बाह्य पूर्णांक ioat_ring_alloc_order;
बाह्य काष्ठा kobj_type ioat_ktype;
बाह्य काष्ठा kmem_cache *ioat_cache;
बाह्य पूर्णांक ioat_ring_max_alloc_order;
बाह्य काष्ठा kmem_cache *ioat_sed_cache;

अटल अंतरभूत काष्ठा ioatdma_chan *to_ioat_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा ioatdma_chan, dma_chan);
पूर्ण

/* wrapper around hardware descriptor क्रमmat + additional software fields */
#अगर_घोषित DEBUG
#घोषणा set_desc_id(desc, i) ((desc)->id = (i))
#घोषणा desc_id(desc) ((desc)->id)
#अन्यथा
#घोषणा set_desc_id(desc, i)
#घोषणा desc_id(desc) (0)
#पूर्ण_अगर

अटल अंतरभूत व्योम
__dump_desc_dbg(काष्ठा ioatdma_chan *ioat_chan, काष्ठा ioat_dma_descriptor *hw,
		काष्ठा dma_async_tx_descriptor *tx, पूर्णांक id)
अणु
	काष्ठा device *dev = to_dev(ioat_chan);

	dev_dbg(dev, "desc[%d]: (%#llx->%#llx) cookie: %d flags: %#x"
		" ctl: %#10.8x (op: %#x int_en: %d compl: %d)\n", id,
		(अचिन्हित दीर्घ दीर्घ) tx->phys,
		(अचिन्हित दीर्घ दीर्घ) hw->next, tx->cookie, tx->flags,
		hw->ctl, hw->ctl_f.op, hw->ctl_f.पूर्णांक_en, hw->ctl_f.compl_ग_लिखो);
पूर्ण

#घोषणा dump_desc_dbg(c, d) \
	(अणु अगर (d) __dump_desc_dbg(c, d->hw, &d->txd, desc_id(d)); 0; पूर्ण)

अटल अंतरभूत काष्ठा ioatdma_chan *
ioat_chan_by_index(काष्ठा ioatdma_device *ioat_dma, पूर्णांक index)
अणु
	वापस ioat_dma->idx[index];
पूर्ण

अटल अंतरभूत u64 ioat_chansts(काष्ठा ioatdma_chan *ioat_chan)
अणु
	वापस पढ़ोq(ioat_chan->reg_base + IOAT_CHANSTS_OFFSET);
पूर्ण

अटल अंतरभूत u64 ioat_chansts_to_addr(u64 status)
अणु
	वापस status & IOAT_CHANSTS_COMPLETED_DESCRIPTOR_ADDR;
पूर्ण

अटल अंतरभूत u32 ioat_chanerr(काष्ठा ioatdma_chan *ioat_chan)
अणु
	वापस पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
पूर्ण

अटल अंतरभूत व्योम ioat_suspend(काष्ठा ioatdma_chan *ioat_chan)
अणु
	u8 ver = ioat_chan->ioat_dma->version;

	ग_लिखोb(IOAT_CHANCMD_SUSPEND,
	       ioat_chan->reg_base + IOAT_CHANCMD_OFFSET(ver));
पूर्ण

अटल अंतरभूत व्योम ioat_reset(काष्ठा ioatdma_chan *ioat_chan)
अणु
	u8 ver = ioat_chan->ioat_dma->version;

	ग_लिखोb(IOAT_CHANCMD_RESET,
	       ioat_chan->reg_base + IOAT_CHANCMD_OFFSET(ver));
पूर्ण

अटल अंतरभूत bool ioat_reset_pending(काष्ठा ioatdma_chan *ioat_chan)
अणु
	u8 ver = ioat_chan->ioat_dma->version;
	u8 cmd;

	cmd = पढ़ोb(ioat_chan->reg_base + IOAT_CHANCMD_OFFSET(ver));
	वापस (cmd & IOAT_CHANCMD_RESET) == IOAT_CHANCMD_RESET;
पूर्ण

अटल अंतरभूत bool is_ioat_active(अचिन्हित दीर्घ status)
अणु
	वापस ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_ACTIVE);
पूर्ण

अटल अंतरभूत bool is_ioat_idle(अचिन्हित दीर्घ status)
अणु
	वापस ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_DONE);
पूर्ण

अटल अंतरभूत bool is_ioat_halted(अचिन्हित दीर्घ status)
अणु
	वापस ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_HALTED);
पूर्ण

अटल अंतरभूत bool is_ioat_suspended(अचिन्हित दीर्घ status)
अणु
	वापस ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED);
पूर्ण

/* channel was fatally programmed */
अटल अंतरभूत bool is_ioat_bug(अचिन्हित दीर्घ err)
अणु
	वापस !!err;
पूर्ण


अटल अंतरभूत u32 ioat_ring_size(काष्ठा ioatdma_chan *ioat_chan)
अणु
	वापस 1 << ioat_chan->alloc_order;
पूर्ण

/* count of descriptors in flight with the engine */
अटल अंतरभूत u16 ioat_ring_active(काष्ठा ioatdma_chan *ioat_chan)
अणु
	वापस CIRC_CNT(ioat_chan->head, ioat_chan->tail,
			ioat_ring_size(ioat_chan));
पूर्ण

/* count of descriptors pending submission to hardware */
अटल अंतरभूत u16 ioat_ring_pending(काष्ठा ioatdma_chan *ioat_chan)
अणु
	वापस CIRC_CNT(ioat_chan->head, ioat_chan->issued,
			ioat_ring_size(ioat_chan));
पूर्ण

अटल अंतरभूत u32 ioat_ring_space(काष्ठा ioatdma_chan *ioat_chan)
अणु
	वापस ioat_ring_size(ioat_chan) - ioat_ring_active(ioat_chan);
पूर्ण

अटल अंतरभूत u16
ioat_xferlen_to_descs(काष्ठा ioatdma_chan *ioat_chan, माप_प्रकार len)
अणु
	u16 num_descs = len >> ioat_chan->xfercap_log;

	num_descs += !!(len & ((1 << ioat_chan->xfercap_log) - 1));
	वापस num_descs;
पूर्ण

अटल अंतरभूत काष्ठा ioat_ring_ent *
ioat_get_ring_ent(काष्ठा ioatdma_chan *ioat_chan, u16 idx)
अणु
	वापस ioat_chan->ring[idx & (ioat_ring_size(ioat_chan) - 1)];
पूर्ण

अटल अंतरभूत व्योम
ioat_set_chainaddr(काष्ठा ioatdma_chan *ioat_chan, u64 addr)
अणु
	ग_लिखोl(addr & 0x00000000FFFFFFFF,
	       ioat_chan->reg_base + IOAT2_CHAINADDR_OFFSET_LOW);
	ग_लिखोl(addr >> 32,
	       ioat_chan->reg_base + IOAT2_CHAINADDR_OFFSET_HIGH);
पूर्ण

/* IOAT Prep functions */
काष्ठा dma_async_tx_descriptor *
ioat_dma_prep_स_नकल_lock(काष्ठा dma_chan *c, dma_addr_t dma_dest,
			   dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_पूर्णांकerrupt_lock(काष्ठा dma_chan *c, अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_xor(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
	       अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_xor_val(काष्ठा dma_chan *chan, dma_addr_t *src,
		    अचिन्हित पूर्णांक src_cnt, माप_प्रकार len,
		    क्रमागत sum_check_flags *result, अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_pq(काष्ठा dma_chan *chan, dma_addr_t *dst, dma_addr_t *src,
	      अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
	      अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_pq_val(काष्ठा dma_chan *chan, dma_addr_t *pq, dma_addr_t *src,
		  अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		  क्रमागत sum_check_flags *pqres, अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_pqxor(काष्ठा dma_chan *chan, dma_addr_t dst, dma_addr_t *src,
		 अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *
ioat_prep_pqxor_val(काष्ठा dma_chan *chan, dma_addr_t *src,
		     अचिन्हित पूर्णांक src_cnt, माप_प्रकार len,
		     क्रमागत sum_check_flags *result, अचिन्हित दीर्घ flags);

/* IOAT Operation functions */
irqवापस_t ioat_dma_करो_पूर्णांकerrupt(पूर्णांक irq, व्योम *data);
irqवापस_t ioat_dma_करो_पूर्णांकerrupt_msix(पूर्णांक irq, व्योम *data);
काष्ठा ioat_ring_ent **
ioat_alloc_ring(काष्ठा dma_chan *c, पूर्णांक order, gfp_t flags);
व्योम ioat_start_null_desc(काष्ठा ioatdma_chan *ioat_chan);
व्योम ioat_मुक्त_ring_ent(काष्ठा ioat_ring_ent *desc, काष्ठा dma_chan *chan);
पूर्णांक ioat_reset_hw(काष्ठा ioatdma_chan *ioat_chan);
क्रमागत dma_status
ioat_tx_status(काष्ठा dma_chan *c, dma_cookie_t cookie,
		काष्ठा dma_tx_state *txstate);
व्योम ioat_cleanup_event(काष्ठा tasklet_काष्ठा *t);
व्योम ioat_समयr_event(काष्ठा समयr_list *t);
पूर्णांक ioat_check_space_lock(काष्ठा ioatdma_chan *ioat_chan, पूर्णांक num_descs);
व्योम ioat_issue_pending(काष्ठा dma_chan *chan);

/* IOAT Init functions */
bool is_bwd_ioat(काष्ठा pci_dev *pdev);
काष्ठा dca_provider *ioat_dca_init(काष्ठा pci_dev *pdev, व्योम __iomem *iobase);
व्योम ioat_kobject_add(काष्ठा ioatdma_device *ioat_dma, काष्ठा kobj_type *type);
व्योम ioat_kobject_del(काष्ठा ioatdma_device *ioat_dma);
पूर्णांक ioat_dma_setup_पूर्णांकerrupts(काष्ठा ioatdma_device *ioat_dma);
व्योम ioat_stop(काष्ठा ioatdma_chan *ioat_chan);
#पूर्ण_अगर /* IOATDMA_H */
