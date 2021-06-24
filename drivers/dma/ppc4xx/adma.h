<शैली गुरु>
/*
 * 2006-2009 (C) DENX Software Engineering.
 *
 * Author: Yuri Tikhonov <yur@emcraft.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of
 * any kind, whether express or implied.
 */

#अगर_अघोषित _PPC440SPE_ADMA_H
#घोषणा _PPC440SPE_ADMA_H

#समावेश <linux/types.h>
#समावेश "dma.h"
#समावेश "xor.h"

#घोषणा to_ppc440spe_adma_chan(chan) \
		container_of(chan, काष्ठा ppc440spe_adma_chan, common)
#घोषणा to_ppc440spe_adma_device(dev) \
		container_of(dev, काष्ठा ppc440spe_adma_device, common)
#घोषणा tx_to_ppc440spe_adma_slot(tx) \
		container_of(tx, काष्ठा ppc440spe_adma_desc_slot, async_tx)

/* Default polynomial (क्रम 440SP is only available) */
#घोषणा PPC440SPE_DEFAULT_POLY	0x4d

#घोषणा PPC440SPE_ADMA_ENGINES_NUM	(XOR_ENGINES_NUM + DMA_ENGINES_NUM)

#घोषणा PPC440SPE_ADMA_WATCHDOG_MSEC	3
#घोषणा PPC440SPE_ADMA_THRESHOLD	1

#घोषणा PPC440SPE_DMA0_ID	0
#घोषणा PPC440SPE_DMA1_ID	1
#घोषणा PPC440SPE_XOR_ID	2

#घोषणा PPC440SPE_ADMA_DMA_MAX_BYTE_COUNT	0xFFFFFFUL
/* this is the XOR_CBBCR width */
#घोषणा PPC440SPE_ADMA_XOR_MAX_BYTE_COUNT	(1 << 31)
#घोषणा PPC440SPE_ADMA_ZERO_SUM_MAX_BYTE_COUNT PPC440SPE_ADMA_XOR_MAX_BYTE_COUNT

#घोषणा PPC440SPE_RXOR_RUN	0

#घोषणा MQ0_CF2H_RXOR_BS_MASK	0x1FF

#अघोषित ADMA_LL_DEBUG

/**
 * काष्ठा ppc440spe_adma_device - पूर्णांकernal representation of an ADMA device
 * @dev: device
 * @dma_reg: base क्रम DMAx रेजिस्टर access
 * @xor_reg: base क्रम XOR रेजिस्टर access
 * @i2o_reg: base क्रम I2O रेजिस्टर access
 * @id: HW ADMA Device selector
 * @dma_desc_pool_virt: base of DMA descriptor region (CPU address)
 * @dma_desc_pool: base of DMA descriptor region (DMA address)
 * @pool_size: size of the pool
 * @irq: DMAx or XOR irq number
 * @err_irq: DMAx error irq number
 * @common: embedded काष्ठा dma_device
 */
काष्ठा ppc440spe_adma_device अणु
	काष्ठा device *dev;
	काष्ठा dma_regs __iomem *dma_reg;
	काष्ठा xor_regs __iomem *xor_reg;
	काष्ठा i2o_regs __iomem *i2o_reg;
	पूर्णांक id;
	व्योम *dma_desc_pool_virt;
	dma_addr_t dma_desc_pool;
	माप_प्रकार pool_size;
	पूर्णांक irq;
	पूर्णांक err_irq;
	काष्ठा dma_device common;
पूर्ण;

/**
 * काष्ठा ppc440spe_adma_chan - पूर्णांकernal representation of an ADMA channel
 * @lock: serializes enqueue/dequeue operations to the slot pool
 * @device: parent device
 * @chain: device chain view of the descriptors
 * @common: common dmaengine channel object members
 * @all_slots: complete करोमुख्य of slots usable by the channel
 * @pending: allows batching of hardware operations
 * @slots_allocated: records the actual size of the descriptor slot pool
 * @hw_chain_inited: h/w descriptor chain initialization flag
 * @irq_tasklet: bottom half where ppc440spe_adma_slot_cleanup runs
 * @needs_unmap: अगर buffers should not be unmapped upon final processing
 * @pdest_page: P destination page क्रम async validate operation
 * @qdest_page: Q destination page क्रम async validate operation
 * @pdest: P dma addr क्रम async validate operation
 * @qdest: Q dma addr क्रम async validate operation
 */
काष्ठा ppc440spe_adma_chan अणु
	spinlock_t lock;
	काष्ठा ppc440spe_adma_device *device;
	काष्ठा list_head chain;
	काष्ठा dma_chan common;
	काष्ठा list_head all_slots;
	काष्ठा ppc440spe_adma_desc_slot *last_used;
	पूर्णांक pending;
	पूर्णांक slots_allocated;
	पूर्णांक hw_chain_inited;
	काष्ठा tasklet_काष्ठा irq_tasklet;
	u8 needs_unmap;
	काष्ठा page *pdest_page;
	काष्ठा page *qdest_page;
	dma_addr_t pdest;
	dma_addr_t qdest;
पूर्ण;

काष्ठा ppc440spe_rxor अणु
	u32 addrl;
	u32 addrh;
	पूर्णांक len;
	पूर्णांक xor_count;
	पूर्णांक addr_count;
	पूर्णांक desc_count;
	पूर्णांक state;
पूर्ण;

/**
 * काष्ठा ppc440spe_adma_desc_slot - PPC440SPE-ADMA software descriptor
 * @phys: hardware address of the hardware descriptor chain
 * @group_head: first operation in a transaction
 * @hw_next: poपूर्णांकer to the next descriptor in chain
 * @async_tx: support क्रम the async_tx api
 * @slot_node: node on the iop_adma_chan.all_slots list
 * @chain_node: node on the op_adma_chan.chain list
 * @group_list: list of slots that make up a multi-descriptor transaction
 *              क्रम example transfer lengths larger than the supported hw max
 * @unmap_len: transaction bytecount
 * @hw_desc: भव address of the hardware descriptor chain
 * @stride: currently chained or not
 * @idx: pool index
 * @slot_cnt: total slots used in an transaction (group of operations)
 * @src_cnt: number of sources set in this descriptor
 * @dst_cnt: number of destinations set in the descriptor
 * @slots_per_op: number of slots per operation
 * @descs_per_op: number of slot per P/Q operation see comment
 *                क्रम ppc440spe_prep_dma_pqxor function
 * @flags: desc state/type
 * @reverse_flags: 1 अगर a corresponding rxor address uses reversed address order
 * @xor_check_result: result of zero sum
 * @crc32_result: result crc calculation
 */
काष्ठा ppc440spe_adma_desc_slot अणु
	dma_addr_t phys;
	काष्ठा ppc440spe_adma_desc_slot *group_head;
	काष्ठा ppc440spe_adma_desc_slot *hw_next;
	काष्ठा dma_async_tx_descriptor async_tx;
	काष्ठा list_head slot_node;
	काष्ठा list_head chain_node; /* node in channel ops list */
	काष्ठा list_head group_list; /* list */
	अचिन्हित पूर्णांक unmap_len;
	व्योम *hw_desc;
	u16 stride;
	u16 idx;
	u16 slot_cnt;
	u8 src_cnt;
	u8 dst_cnt;
	u8 slots_per_op;
	u8 descs_per_op;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ reverse_flags[8];

#घोषणा PPC440SPE_DESC_INT	0	/* generate पूर्णांकerrupt on complete */
#घोषणा PPC440SPE_ZERO_P	1	/* clear P destionaion */
#घोषणा PPC440SPE_ZERO_Q	2	/* clear Q destination */
#घोषणा PPC440SPE_COHERENT	3	/* src/dst are coherent */

#घोषणा PPC440SPE_DESC_WXOR	4	/* WXORs are in chain */
#घोषणा PPC440SPE_DESC_RXOR	5	/* RXOR is in chain */

#घोषणा PPC440SPE_DESC_RXOR123	8	/* CDB क्रम RXOR123 operation */
#घोषणा PPC440SPE_DESC_RXOR124	9	/* CDB क्रम RXOR124 operation */
#घोषणा PPC440SPE_DESC_RXOR125	10	/* CDB क्रम RXOR125 operation */
#घोषणा PPC440SPE_DESC_RXOR12	11	/* CDB क्रम RXOR12 operation */
#घोषणा PPC440SPE_DESC_RXOR_REV	12	/* CDB has srcs in reversed order */

#घोषणा PPC440SPE_DESC_PCHECK	13
#घोषणा PPC440SPE_DESC_QCHECK	14

#घोषणा PPC440SPE_DESC_RXOR_MSK	0x3

	काष्ठा ppc440spe_rxor rxor_cursor;

	जोड़ अणु
		u32 *xor_check_result;
		u32 *crc32_result;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* _PPC440SPE_ADMA_H */
