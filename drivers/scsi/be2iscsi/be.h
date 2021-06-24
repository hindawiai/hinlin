<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#अगर_अघोषित BEISCSI_H
#घोषणा BEISCSI_H

#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/irq_poll.h>
#घोषणा FW_VER_LEN	32
#घोषणा MCC_Q_LEN	128
#घोषणा MCC_CQ_LEN	256
#घोषणा MAX_MCC_CMD	16
/* BladeEngine Generation numbers */
#घोषणा BE_GEN2 2
#घोषणा BE_GEN3 3
#घोषणा BE_GEN4	4
काष्ठा be_dma_mem अणु
	व्योम *va;
	dma_addr_t dma;
	u32 size;
पूर्ण;

काष्ठा be_queue_info अणु
	काष्ठा be_dma_mem dma_mem;
	u16 len;
	u16 entry_size;		/* Size of an element in the queue */
	u16 id;
	u16 tail, head;
	bool created;
	u16 used;		/* Number of valid elements in the queue */
पूर्ण;

अटल अंतरभूत u32 MODULO(u16 val, u16 limit)
अणु
	WARN_ON(limit & (limit - 1));
	वापस val & (limit - 1);
पूर्ण

अटल अंतरभूत व्योम index_inc(u16 *index, u16 limit)
अणु
	*index = MODULO((*index + 1), limit);
पूर्ण

अटल अंतरभूत व्योम *queue_head_node(काष्ठा be_queue_info *q)
अणु
	वापस q->dma_mem.va + q->head * q->entry_size;
पूर्ण

अटल अंतरभूत व्योम *queue_get_wrb(काष्ठा be_queue_info *q, अचिन्हित पूर्णांक wrb_num)
अणु
	वापस q->dma_mem.va + wrb_num * q->entry_size;
पूर्ण

अटल अंतरभूत व्योम *queue_tail_node(काष्ठा be_queue_info *q)
अणु
	वापस q->dma_mem.va + q->tail * q->entry_size;
पूर्ण

अटल अंतरभूत व्योम queue_head_inc(काष्ठा be_queue_info *q)
अणु
	index_inc(&q->head, q->len);
पूर्ण

अटल अंतरभूत व्योम queue_tail_inc(काष्ठा be_queue_info *q)
अणु
	index_inc(&q->tail, q->len);
पूर्ण

/*ISCSI */

काष्ठा be_aic_obj अणु		/* Adaptive पूर्णांकerrupt coalescing (AIC) info */
	अचिन्हित दीर्घ jअगरfies;
	u32 eq_prev;		/* Used to calculate eqe */
	u32 prev_eqd;
#घोषणा BEISCSI_EQ_DELAY_MIN	0
#घोषणा BEISCSI_EQ_DELAY_DEF	32
#घोषणा BEISCSI_EQ_DELAY_MAX	128
पूर्ण;

काष्ठा be_eq_obj अणु
	u32 cq_count;
	काष्ठा be_queue_info q;
	काष्ठा beiscsi_hba *phba;
	काष्ठा be_queue_info *cq;
	काष्ठा work_काष्ठा mcc_work; /* Work Item */
	काष्ठा irq_poll	iopoll;
पूर्ण;

काष्ठा be_mcc_obj अणु
	काष्ठा be_queue_info q;
	काष्ठा be_queue_info cq;
पूर्ण;

काष्ठा beiscsi_mcc_tag_state अणु
	अचिन्हित दीर्घ tag_state;
#घोषणा MCC_TAG_STATE_RUNNING	0
#घोषणा MCC_TAG_STATE_TIMEOUT	1
#घोषणा MCC_TAG_STATE_ASYNC	2
#घोषणा MCC_TAG_STATE_IGNORE	3
	व्योम (*cbfn)(काष्ठा beiscsi_hba *, अचिन्हित पूर्णांक);
	काष्ठा be_dma_mem tag_mem_state;
पूर्ण;

काष्ठा be_ctrl_info अणु
	u8 __iomem *csr;
	u8 __iomem *db;		/* Door Bell */
	u8 __iomem *pcicfg;	/* PCI config space */
	काष्ठा pci_dev *pdev;

	/* Mbox used क्रम cmd request/response */
	काष्ठा mutex mbox_lock;	/* For serializing mbox cmds to BE card */
	काष्ठा be_dma_mem mbox_mem;
	/* Mbox mem is adjusted to align to 16 bytes. The allocated addr
	 * is stored क्रम मुक्तing purpose */
	काष्ठा be_dma_mem mbox_mem_alloced;

	/* MCC Rings */
	काष्ठा be_mcc_obj mcc_obj;
	spinlock_t mcc_lock;	/* For serializing mcc cmds to BE card */

	रुको_queue_head_t mcc_रुको[MAX_MCC_CMD + 1];
	अचिन्हित पूर्णांक mcc_tag[MAX_MCC_CMD];
	अचिन्हित पूर्णांक mcc_tag_status[MAX_MCC_CMD + 1];
	अचिन्हित लघु mcc_alloc_index;
	अचिन्हित लघु mcc_मुक्त_index;
	अचिन्हित पूर्णांक mcc_tag_available;

	काष्ठा beiscsi_mcc_tag_state ptag_state[MAX_MCC_CMD + 1];
पूर्ण;

#समावेश "be_cmds.h"

/* WRB index mask क्रम MCC_Q_LEN queue entries */
#घोषणा MCC_Q_WRB_IDX_MASK	CQE_STATUS_WRB_MASK
#घोषणा MCC_Q_WRB_IDX_SHIFT	CQE_STATUS_WRB_SHIFT
/* TAG is from 1...MAX_MCC_CMD, MASK includes MAX_MCC_CMD */
#घोषणा MCC_Q_CMD_TAG_MASK	((MAX_MCC_CMD << 1) - 1)

#घोषणा PAGE_SHIFT_4K		12
#घोषणा PAGE_SIZE_4K		(1 << PAGE_SHIFT_4K)

/* Returns number of pages spanned by the data starting at the given addr */
#घोषणा PAGES_4K_SPANNED(_address, size)				\
		((u32)((((माप_प्रकार)(_address) & (PAGE_SIZE_4K - 1)) +	\
			(size) + (PAGE_SIZE_4K - 1)) >> PAGE_SHIFT_4K))

/* Returns bit offset within a DWORD of a bitfield */
#घोषणा AMAP_BIT_OFFSET(_काष्ठा, field)					\
		(((माप_प्रकार)&(((_काष्ठा *)0)->field))%32)

/* Returns the bit mask of the field that is NOT shअगरted पूर्णांकo location. */
अटल अंतरभूत u32 amap_mask(u32 bitsize)
अणु
	वापस (bitsize == 32 ? 0xFFFFFFFF : (1 << bitsize) - 1);
पूर्ण

अटल अंतरभूत व्योम amap_set(व्योम *ptr, u32 dw_offset, u32 mask,
					u32 offset, u32 value)
अणु
	u32 *dw = (u32 *) ptr + dw_offset;
	*dw &= ~(mask << offset);
	*dw |= (mask & value) << offset;
पूर्ण

#घोषणा AMAP_SET_BITS(_काष्ठा, field, ptr, val)				\
		amap_set(ptr,						\
			दुरत्व(_काष्ठा, field)/32,			\
			amap_mask(माप(((_काष्ठा *)0)->field)),	\
			AMAP_BIT_OFFSET(_काष्ठा, field),		\
			val)

अटल अंतरभूत u32 amap_get(व्योम *ptr, u32 dw_offset, u32 mask, u32 offset)
अणु
	u32 *dw = ptr;
	वापस mask & (*(dw + dw_offset) >> offset);
पूर्ण

#घोषणा AMAP_GET_BITS(_काष्ठा, field, ptr)				\
		amap_get(ptr,						\
			दुरत्व(_काष्ठा, field)/32,			\
			amap_mask(माप(((_काष्ठा *)0)->field)),	\
			AMAP_BIT_OFFSET(_काष्ठा, field))

#घोषणा be_dws_cpu_to_le(wrb, len) swap_dws(wrb, len)
#घोषणा be_dws_le_to_cpu(wrb, len) swap_dws(wrb, len)
अटल अंतरभूत व्योम swap_dws(व्योम *wrb, पूर्णांक len)
अणु
#अगर_घोषित __BIG_ENDIAN
	u32 *dw = wrb;
	WARN_ON(len % 4);
	करो अणु
		*dw = cpu_to_le32(*dw);
		dw++;
		len -= 4;
	पूर्ण जबतक (len);
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण
#पूर्ण_अगर /* BEISCSI_H */
