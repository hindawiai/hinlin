<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2006, Intel Corporation.
 */
#अगर_अघोषित IOP_ADMA_H
#घोषणा IOP_ADMA_H
#समावेश <linux/types.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा IOP_ADMA_SLOT_SIZE 32
#घोषणा IOP_ADMA_THRESHOLD 4
#अगर_घोषित DEBUG
#घोषणा IOP_PARANOIA 1
#अन्यथा
#घोषणा IOP_PARANOIA 0
#पूर्ण_अगर
#घोषणा iop_paranoia(x) BUG_ON(IOP_PARANOIA && (x))

#घोषणा DMA0_ID 0
#घोषणा DMA1_ID 1
#घोषणा AAU_ID 2

/**
 * काष्ठा iop_adma_device - पूर्णांकernal representation of an ADMA device
 * @pdev: Platक्रमm device
 * @id: HW ADMA Device selector
 * @dma_desc_pool: base of DMA descriptor region (DMA address)
 * @dma_desc_pool_virt: base of DMA descriptor region (CPU address)
 * @common: embedded काष्ठा dma_device
 */
काष्ठा iop_adma_device अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक id;
	dma_addr_t dma_desc_pool;
	व्योम *dma_desc_pool_virt;
	काष्ठा dma_device common;
पूर्ण;

/**
 * काष्ठा iop_adma_chan - पूर्णांकernal representation of an ADMA device
 * @pending: allows batching of hardware operations
 * @lock: serializes enqueue/dequeue operations to the slot pool
 * @mmr_base: memory mapped रेजिस्टर base
 * @chain: device chain view of the descriptors
 * @device: parent device
 * @common: common dmaengine channel object members
 * @last_used: place holder क्रम allocation to जारी from where it left off
 * @all_slots: complete करोमुख्य of slots usable by the channel
 * @slots_allocated: records the actual size of the descriptor slot pool
 * @irq_tasklet: bottom half where iop_adma_slot_cleanup runs
 */
काष्ठा iop_adma_chan अणु
	पूर्णांक pending;
	spinlock_t lock; /* protects the descriptor slot pool */
	व्योम __iomem *mmr_base;
	काष्ठा list_head chain;
	काष्ठा iop_adma_device *device;
	काष्ठा dma_chan common;
	काष्ठा iop_adma_desc_slot *last_used;
	काष्ठा list_head all_slots;
	पूर्णांक slots_allocated;
	काष्ठा tasklet_काष्ठा irq_tasklet;
पूर्ण;

/**
 * काष्ठा iop_adma_desc_slot - IOP-ADMA software descriptor
 * @slot_node: node on the iop_adma_chan.all_slots list
 * @chain_node: node on the op_adma_chan.chain list
 * @hw_desc: भव address of the hardware descriptor chain
 * @phys: hardware address of the hardware descriptor chain
 * @group_head: first operation in a transaction
 * @slot_cnt: total slots used in an transaction (group of operations)
 * @slots_per_op: number of slots per operation
 * @idx: pool index
 * @tx_list: list of descriptors that are associated with one operation
 * @async_tx: support क्रम the async_tx api
 * @group_list: list of slots that make up a multi-descriptor transaction
 *	क्रम example transfer lengths larger than the supported hw max
 * @xor_check_result: result of zero sum
 * @crc32_result: result crc calculation
 */
काष्ठा iop_adma_desc_slot अणु
	काष्ठा list_head slot_node;
	काष्ठा list_head chain_node;
	व्योम *hw_desc;
	काष्ठा iop_adma_desc_slot *group_head;
	u16 slot_cnt;
	u16 slots_per_op;
	u16 idx;
	काष्ठा list_head tx_list;
	काष्ठा dma_async_tx_descriptor async_tx;
	जोड़ अणु
		u32 *xor_check_result;
		u32 *crc32_result;
		u32 *pq_check_result;
	पूर्ण;
पूर्ण;

काष्ठा iop_adma_platक्रमm_data अणु
	पूर्णांक hw_id;
	dma_cap_mask_t cap_mask;
	माप_प्रकार pool_size;
पूर्ण;

#घोषणा to_iop_sw_desc(addr_hw_desc) \
	container_of(addr_hw_desc, काष्ठा iop_adma_desc_slot, hw_desc)
#घोषणा iop_hw_desc_slot_idx(hw_desc, idx) \
	( (व्योम *) (((अचिन्हित दीर्घ) hw_desc) + ((idx) << 5)) )
#पूर्ण_अगर
