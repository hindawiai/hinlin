<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006-2009 DENX Software Engineering.
 *
 * Author: Yuri Tikhonov <yur@emcraft.com>
 *
 * Further porting to arch/घातerpc by
 * 	Anम_से_दij Gustschin <agust@denx.de>
 */

/*
 * This driver supports the asynchrounous DMA copy and RAID engines available
 * on the AMCC PPC440SPe Processors.
 * Based on the Intel Xscale(R) family of I/O Processors (IOP 32x, 33x, 134x)
 * ADMA driver written by D.Williams.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/async_tx.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>
#समावेश "adma.h"
#समावेश "../dmaengine.h"

क्रमागत ppc_adma_init_code अणु
	PPC_ADMA_INIT_OK = 0,
	PPC_ADMA_INIT_MEMRES,
	PPC_ADMA_INIT_MEMREG,
	PPC_ADMA_INIT_ALLOC,
	PPC_ADMA_INIT_COHERENT,
	PPC_ADMA_INIT_CHANNEL,
	PPC_ADMA_INIT_IRQ1,
	PPC_ADMA_INIT_IRQ2,
	PPC_ADMA_INIT_REGISTER
पूर्ण;

अटल अक्षर *ppc_adma_errors[] = अणु
	[PPC_ADMA_INIT_OK] = "ok",
	[PPC_ADMA_INIT_MEMRES] = "failed to get memory resource",
	[PPC_ADMA_INIT_MEMREG] = "failed to request memory region",
	[PPC_ADMA_INIT_ALLOC] = "failed to allocate memory for adev "
				"structure",
	[PPC_ADMA_INIT_COHERENT] = "failed to allocate coherent memory for "
				   "hardware descriptors",
	[PPC_ADMA_INIT_CHANNEL] = "failed to allocate memory for channel",
	[PPC_ADMA_INIT_IRQ1] = "failed to request first irq",
	[PPC_ADMA_INIT_IRQ2] = "failed to request second irq",
	[PPC_ADMA_INIT_REGISTER] = "failed to register dma async device",
पूर्ण;

अटल क्रमागत ppc_adma_init_code
ppc440spe_adma_devices[PPC440SPE_ADMA_ENGINES_NUM];

काष्ठा ppc_dma_chan_ref अणु
	काष्ठा dma_chan *chan;
	काष्ठा list_head node;
पूर्ण;

/* The list of channels exported by ppc440spe ADMA */
अटल काष्ठा list_head
ppc440spe_adma_chan_list = LIST_HEAD_INIT(ppc440spe_adma_chan_list);

/* This flag is set when want to refetch the xor chain in the पूर्णांकerrupt
 * handler
 */
अटल u32 करो_xor_refetch;

/* Poपूर्णांकer to DMA0, DMA1 CP/CS FIFO */
अटल व्योम *ppc440spe_dma_fअगरo_buf;

/* Poपूर्णांकers to last submitted to DMA0, DMA1 CDBs */
अटल काष्ठा ppc440spe_adma_desc_slot *chan_last_sub[3];
अटल काष्ठा ppc440spe_adma_desc_slot *chan_first_cdb[3];

/* Poपूर्णांकer to last linked and submitted xor CB */
अटल काष्ठा ppc440spe_adma_desc_slot *xor_last_linked;
अटल काष्ठा ppc440spe_adma_desc_slot *xor_last_submit;

/* This array is used in data-check operations क्रम storing a pattern */
अटल अक्षर ppc440spe_qword[16];

अटल atomic_t ppc440spe_adma_err_irq_ref;
अटल dcr_host_t ppc440spe_mq_dcr_host;
अटल अचिन्हित पूर्णांक ppc440spe_mq_dcr_len;

/* Since RXOR operations use the common रेजिस्टर (MQ0_CF2H) क्रम setting-up
 * the block size in transactions, then we करो not allow to activate more than
 * only one RXOR transactions simultaneously. So use this var to store
 * the inक्रमmation about is RXOR currently active (PPC440SPE_RXOR_RUN bit is
 * set) or not (PPC440SPE_RXOR_RUN is clear).
 */
अटल अचिन्हित दीर्घ ppc440spe_rxor_state;

/* These are used in enable & check routines
 */
अटल u32 ppc440spe_r6_enabled;
अटल काष्ठा ppc440spe_adma_chan *ppc440spe_r6_tchan;
अटल काष्ठा completion ppc440spe_r6_test_comp;

अटल पूर्णांक ppc440spe_adma_dma2rxor_prep_src(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		काष्ठा ppc440spe_rxor *cursor, पूर्णांक index,
		पूर्णांक src_cnt, u32 addr);
अटल व्योम ppc440spe_adma_dma2rxor_set_src(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		पूर्णांक index, dma_addr_t addr);
अटल व्योम ppc440spe_adma_dma2rxor_set_mult(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		पूर्णांक index, u8 mult);

#अगर_घोषित ADMA_LL_DEBUG
#घोषणा ADMA_LL_DBG(x) (अणु अगर (1) x; 0; पूर्ण)
#अन्यथा
#घोषणा ADMA_LL_DBG(x) (अणु अगर (0) x; 0; पूर्ण)
#पूर्ण_अगर

अटल व्योम prपूर्णांक_cb(काष्ठा ppc440spe_adma_chan *chan, व्योम *block)
अणु
	काष्ठा dma_cdb *cdb;
	काष्ठा xor_cb *cb;
	पूर्णांक i;

	चयन (chan->device->id) अणु
	हाल 0:
	हाल 1:
		cdb = block;

		pr_debug("CDB at %p [%d]:\n"
			"\t attr 0x%02x opc 0x%02x cnt 0x%08x\n"
			"\t sg1u 0x%08x sg1l 0x%08x\n"
			"\t sg2u 0x%08x sg2l 0x%08x\n"
			"\t sg3u 0x%08x sg3l 0x%08x\n",
			cdb, chan->device->id,
			cdb->attr, cdb->opc, le32_to_cpu(cdb->cnt),
			le32_to_cpu(cdb->sg1u), le32_to_cpu(cdb->sg1l),
			le32_to_cpu(cdb->sg2u), le32_to_cpu(cdb->sg2l),
			le32_to_cpu(cdb->sg3u), le32_to_cpu(cdb->sg3l)
		);
		अवरोध;
	हाल 2:
		cb = block;

		pr_debug("CB at %p [%d]:\n"
			"\t cbc 0x%08x cbbc 0x%08x cbs 0x%08x\n"
			"\t cbtah 0x%08x cbtal 0x%08x\n"
			"\t cblah 0x%08x cblal 0x%08x\n",
			cb, chan->device->id,
			cb->cbc, cb->cbbc, cb->cbs,
			cb->cbtah, cb->cbtal,
			cb->cblah, cb->cblal);
		क्रम (i = 0; i < 16; i++) अणु
			अगर (i && !cb->ops[i].h && !cb->ops[i].l)
				जारी;
			pr_debug("\t ops[%2d]: h 0x%08x l 0x%08x\n",
				i, cb->ops[i].h, cb->ops[i].l);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_cb_list(काष्ठा ppc440spe_adma_chan *chan,
			  काष्ठा ppc440spe_adma_desc_slot *iter)
अणु
	क्रम (; iter; iter = iter->hw_next)
		prपूर्णांक_cb(chan, iter->hw_desc);
पूर्ण

अटल व्योम prep_dma_xor_dbg(पूर्णांक id, dma_addr_t dst, dma_addr_t *src,
			     अचिन्हित पूर्णांक src_cnt)
अणु
	पूर्णांक i;

	pr_debug("\n%s(%d):\nsrc: ", __func__, id);
	क्रम (i = 0; i < src_cnt; i++)
		pr_debug("\t0x%016llx ", src[i]);
	pr_debug("dst:\n\t0x%016llx\n", dst);
पूर्ण

अटल व्योम prep_dma_pq_dbg(पूर्णांक id, dma_addr_t *dst, dma_addr_t *src,
			    अचिन्हित पूर्णांक src_cnt)
अणु
	पूर्णांक i;

	pr_debug("\n%s(%d):\nsrc: ", __func__, id);
	क्रम (i = 0; i < src_cnt; i++)
		pr_debug("\t0x%016llx ", src[i]);
	pr_debug("dst: ");
	क्रम (i = 0; i < 2; i++)
		pr_debug("\t0x%016llx ", dst[i]);
पूर्ण

अटल व्योम prep_dma_pqzero_sum_dbg(पूर्णांक id, dma_addr_t *src,
				    अचिन्हित पूर्णांक src_cnt,
				    स्थिर अचिन्हित अक्षर *scf)
अणु
	पूर्णांक i;

	pr_debug("\n%s(%d):\nsrc(coef): ", __func__, id);
	अगर (scf) अणु
		क्रम (i = 0; i < src_cnt; i++)
			pr_debug("\t0x%016llx(0x%02x) ", src[i], scf[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < src_cnt; i++)
			pr_debug("\t0x%016llx(no) ", src[i]);
	पूर्ण

	pr_debug("dst: ");
	क्रम (i = 0; i < 2; i++)
		pr_debug("\t0x%016llx ", src[src_cnt + i]);
पूर्ण

/******************************************************************************
 * Command (Descriptor) Blocks low-level routines
 ******************************************************************************/
/**
 * ppc440spe_desc_init_पूर्णांकerrupt - initialize the descriptor क्रम INTERRUPT
 * pseuकरो operation
 */
अटल व्योम ppc440spe_desc_init_पूर्णांकerrupt(काष्ठा ppc440spe_adma_desc_slot *desc,
					  काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा xor_cb *p;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_XOR_ID:
		p = desc->hw_desc;
		स_रखो(desc->hw_desc, 0, माप(काष्ठा xor_cb));
		/* NOP with Command Block Complete Enable */
		p->cbc = XOR_CBCR_CBCE_BIT;
		अवरोध;
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		स_रखो(desc->hw_desc, 0, माप(काष्ठा dma_cdb));
		/* NOP with पूर्णांकerrupt */
		set_bit(PPC440SPE_DESC_INT, &desc->flags);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unsupported id %d in %s\n", chan->device->id,
				__func__);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_init_null_xor - initialize the descriptor क्रम शून्य XOR
 * pseuकरो operation
 */
अटल व्योम ppc440spe_desc_init_null_xor(काष्ठा ppc440spe_adma_desc_slot *desc)
अणु
	स_रखो(desc->hw_desc, 0, माप(काष्ठा xor_cb));
	desc->hw_next = शून्य;
	desc->src_cnt = 0;
	desc->dst_cnt = 1;
पूर्ण

/**
 * ppc440spe_desc_init_xor - initialize the descriptor क्रम XOR operation
 */
अटल व्योम ppc440spe_desc_init_xor(काष्ठा ppc440spe_adma_desc_slot *desc,
					 पूर्णांक src_cnt, अचिन्हित दीर्घ flags)
अणु
	काष्ठा xor_cb *hw_desc = desc->hw_desc;

	स_रखो(desc->hw_desc, 0, माप(काष्ठा xor_cb));
	desc->hw_next = शून्य;
	desc->src_cnt = src_cnt;
	desc->dst_cnt = 1;

	hw_desc->cbc = XOR_CBCR_TGT_BIT | src_cnt;
	अगर (flags & DMA_PREP_INTERRUPT)
		/* Enable पूर्णांकerrupt on completion */
		hw_desc->cbc |= XOR_CBCR_CBCE_BIT;
पूर्ण

/**
 * ppc440spe_desc_init_dma2pq - initialize the descriptor क्रम PQ
 * operation in DMA2 controller
 */
अटल व्योम ppc440spe_desc_init_dma2pq(काष्ठा ppc440spe_adma_desc_slot *desc,
		पूर्णांक dst_cnt, पूर्णांक src_cnt, अचिन्हित दीर्घ flags)
अणु
	काष्ठा xor_cb *hw_desc = desc->hw_desc;

	स_रखो(desc->hw_desc, 0, माप(काष्ठा xor_cb));
	desc->hw_next = शून्य;
	desc->src_cnt = src_cnt;
	desc->dst_cnt = dst_cnt;
	स_रखो(desc->reverse_flags, 0, माप(desc->reverse_flags));
	desc->descs_per_op = 0;

	hw_desc->cbc = XOR_CBCR_TGT_BIT;
	अगर (flags & DMA_PREP_INTERRUPT)
		/* Enable पूर्णांकerrupt on completion */
		hw_desc->cbc |= XOR_CBCR_CBCE_BIT;
पूर्ण

#घोषणा DMA_CTRL_FLAGS_LAST	DMA_PREP_FENCE
#घोषणा DMA_PREP_ZERO_P		(DMA_CTRL_FLAGS_LAST << 1)
#घोषणा DMA_PREP_ZERO_Q		(DMA_PREP_ZERO_P << 1)

/**
 * ppc440spe_desc_init_dma01pq - initialize the descriptors क्रम PQ operation
 * with DMA0/1
 */
अटल व्योम ppc440spe_desc_init_dma01pq(काष्ठा ppc440spe_adma_desc_slot *desc,
				पूर्णांक dst_cnt, पूर्णांक src_cnt, अचिन्हित दीर्घ flags,
				अचिन्हित दीर्घ op)
अणु
	काष्ठा dma_cdb *hw_desc;
	काष्ठा ppc440spe_adma_desc_slot *iter;
	u8 करोpc;

	/* Common initialization of a PQ descriptors chain */
	set_bits(op, &desc->flags);
	desc->src_cnt = src_cnt;
	desc->dst_cnt = dst_cnt;

	/* WXOR MULTICAST अगर both P and Q are being computed
	 * MV_SG1_SG2 अगर Q only
	 */
	करोpc = (desc->dst_cnt == DMA_DEST_MAX_NUM) ?
		DMA_CDB_OPC_MULTICAST : DMA_CDB_OPC_MV_SG1_SG2;

	list_क्रम_each_entry(iter, &desc->group_list, chain_node) अणु
		hw_desc = iter->hw_desc;
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));

		अगर (likely(!list_is_last(&iter->chain_node,
				&desc->group_list))) अणु
			/* set 'next' poपूर्णांकer */
			iter->hw_next = list_entry(iter->chain_node.next,
				काष्ठा ppc440spe_adma_desc_slot, chain_node);
			clear_bit(PPC440SPE_DESC_INT, &iter->flags);
		पूर्ण अन्यथा अणु
			/* this is the last descriptor.
			 * this slot will be pasted from ADMA level
			 * each समय it wants to configure parameters
			 * of the transaction (src, dst, ...)
			 */
			iter->hw_next = शून्य;
			अगर (flags & DMA_PREP_INTERRUPT)
				set_bit(PPC440SPE_DESC_INT, &iter->flags);
			अन्यथा
				clear_bit(PPC440SPE_DESC_INT, &iter->flags);
		पूर्ण
	पूर्ण

	/* Set OPS depending on WXOR/RXOR type of operation */
	अगर (!test_bit(PPC440SPE_DESC_RXOR, &desc->flags)) अणु
		/* This is a WXOR only chain:
		 * - first descriptors are क्रम zeroing destinations
		 *   अगर PPC440SPE_ZERO_P/Q set;
		 * - descriptors reमुख्यed are क्रम GF-XOR operations.
		 */
		iter = list_first_entry(&desc->group_list,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);

		अगर (test_bit(PPC440SPE_ZERO_P, &desc->flags)) अणु
			hw_desc = iter->hw_desc;
			hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
			iter = list_first_entry(&iter->chain_node,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		पूर्ण

		अगर (test_bit(PPC440SPE_ZERO_Q, &desc->flags)) अणु
			hw_desc = iter->hw_desc;
			hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
			iter = list_first_entry(&iter->chain_node,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		पूर्ण

		list_क्रम_each_entry_from(iter, &desc->group_list, chain_node) अणु
			hw_desc = iter->hw_desc;
			hw_desc->opc = करोpc;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This is either RXOR-only or mixed RXOR/WXOR */

		/* The first 1 or 2 slots in chain are always RXOR,
		 * अगर need to calculate P & Q, then there are two
		 * RXOR slots; अगर only P or only Q, then there is one
		 */
		iter = list_first_entry(&desc->group_list,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		hw_desc = iter->hw_desc;
		hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;

		अगर (desc->dst_cnt == DMA_DEST_MAX_NUM) अणु
			iter = list_first_entry(&iter->chain_node,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			hw_desc = iter->hw_desc;
			hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
		पूर्ण

		/* The reमुख्यing descs (अगर any) are WXORs */
		अगर (test_bit(PPC440SPE_DESC_WXOR, &desc->flags)) अणु
			iter = list_first_entry(&iter->chain_node,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			list_क्रम_each_entry_from(iter, &desc->group_list,
						chain_node) अणु
				hw_desc = iter->hw_desc;
				hw_desc->opc = करोpc;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_init_dma01pqzero_sum - initialize the descriptor
 * क्रम PQ_ZERO_SUM operation
 */
अटल व्योम ppc440spe_desc_init_dma01pqzero_sum(
				काष्ठा ppc440spe_adma_desc_slot *desc,
				पूर्णांक dst_cnt, पूर्णांक src_cnt)
अणु
	काष्ठा dma_cdb *hw_desc;
	काष्ठा ppc440spe_adma_desc_slot *iter;
	पूर्णांक i = 0;
	u8 करोpc = (dst_cnt == 2) ? DMA_CDB_OPC_MULTICAST :
				   DMA_CDB_OPC_MV_SG1_SG2;
	/*
	 * Initialize starting from 2nd or 3rd descriptor dependent
	 * on dst_cnt. First one or two slots are क्रम cloning P
	 * and/or Q to chan->pdest and/or chan->qdest as we have
	 * to preserve original P/Q.
	 */
	iter = list_first_entry(&desc->group_list,
				काष्ठा ppc440spe_adma_desc_slot, chain_node);
	iter = list_entry(iter->chain_node.next,
			  काष्ठा ppc440spe_adma_desc_slot, chain_node);

	अगर (dst_cnt > 1) अणु
		iter = list_entry(iter->chain_node.next,
				  काष्ठा ppc440spe_adma_desc_slot, chain_node);
	पूर्ण
	/* initialize each source descriptor in chain */
	list_क्रम_each_entry_from(iter, &desc->group_list, chain_node) अणु
		hw_desc = iter->hw_desc;
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
		iter->src_cnt = 0;
		iter->dst_cnt = 0;

		/* This is a ZERO_SUM operation:
		 * - <src_cnt> descriptors starting from 2nd or 3rd
		 *   descriptor are क्रम GF-XOR operations;
		 * - reमुख्यing <dst_cnt> descriptors are क्रम checking the result
		 */
		अगर (i++ < src_cnt)
			/* MV_SG1_SG2 अगर only Q is being verअगरied
			 * MULTICAST अगर both P and Q are being verअगरied
			 */
			hw_desc->opc = करोpc;
		अन्यथा
			/* DMA_CDB_OPC_DCHECK128 operation */
			hw_desc->opc = DMA_CDB_OPC_DCHECK128;

		अगर (likely(!list_is_last(&iter->chain_node,
					 &desc->group_list))) अणु
			/* set 'next' poपूर्णांकer */
			iter->hw_next = list_entry(iter->chain_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
		पूर्ण अन्यथा अणु
			/* this is the last descriptor.
			 * this slot will be pasted from ADMA level
			 * each समय it wants to configure parameters
			 * of the transaction (src, dst, ...)
			 */
			iter->hw_next = शून्य;
			/* always enable पूर्णांकerrupt generation since we get
			 * the status of pqzero from the handler
			 */
			set_bit(PPC440SPE_DESC_INT, &iter->flags);
		पूर्ण
	पूर्ण
	desc->src_cnt = src_cnt;
	desc->dst_cnt = dst_cnt;
पूर्ण

/**
 * ppc440spe_desc_init_स_नकल - initialize the descriptor क्रम MEMCPY operation
 */
अटल व्योम ppc440spe_desc_init_स_नकल(काष्ठा ppc440spe_adma_desc_slot *desc,
					अचिन्हित दीर्घ flags)
अणु
	काष्ठा dma_cdb *hw_desc = desc->hw_desc;

	स_रखो(desc->hw_desc, 0, माप(काष्ठा dma_cdb));
	desc->hw_next = शून्य;
	desc->src_cnt = 1;
	desc->dst_cnt = 1;

	अगर (flags & DMA_PREP_INTERRUPT)
		set_bit(PPC440SPE_DESC_INT, &desc->flags);
	अन्यथा
		clear_bit(PPC440SPE_DESC_INT, &desc->flags);

	hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
पूर्ण

/**
 * ppc440spe_desc_set_src_addr - set source address पूर्णांकo the descriptor
 */
अटल व्योम ppc440spe_desc_set_src_addr(काष्ठा ppc440spe_adma_desc_slot *desc,
					काष्ठा ppc440spe_adma_chan *chan,
					पूर्णांक src_idx, dma_addr_t addrh,
					dma_addr_t addrl)
अणु
	काष्ठा dma_cdb *dma_hw_desc;
	काष्ठा xor_cb *xor_hw_desc;
	phys_addr_t addr64, पंचांगplow, पंचांगphi;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		अगर (!addrh) अणु
			addr64 = addrl;
			पंचांगphi = (addr64 >> 32);
			पंचांगplow = (addr64 & 0xFFFFFFFF);
		पूर्ण अन्यथा अणु
			पंचांगphi = addrh;
			पंचांगplow = addrl;
		पूर्ण
		dma_hw_desc = desc->hw_desc;
		dma_hw_desc->sg1l = cpu_to_le32((u32)पंचांगplow);
		dma_hw_desc->sg1u |= cpu_to_le32((u32)पंचांगphi);
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		xor_hw_desc = desc->hw_desc;
		xor_hw_desc->ops[src_idx].l = addrl;
		xor_hw_desc->ops[src_idx].h |= addrh;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_set_src_mult - set source address mult पूर्णांकo the descriptor
 */
अटल व्योम ppc440spe_desc_set_src_mult(काष्ठा ppc440spe_adma_desc_slot *desc,
			काष्ठा ppc440spe_adma_chan *chan, u32 mult_index,
			पूर्णांक sg_index, अचिन्हित अक्षर mult_value)
अणु
	काष्ठा dma_cdb *dma_hw_desc;
	u32 *psgu;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		dma_hw_desc = desc->hw_desc;

		चयन (sg_index) अणु
		/* क्रम RXOR operations set multiplier
		 * पूर्णांकo source cued address
		 */
		हाल DMA_CDB_SG_SRC:
			psgu = &dma_hw_desc->sg1u;
			अवरोध;
		/* क्रम WXOR operations set multiplier
		 * पूर्णांकo destination cued address(es)
		 */
		हाल DMA_CDB_SG_DST1:
			psgu = &dma_hw_desc->sg2u;
			अवरोध;
		हाल DMA_CDB_SG_DST2:
			psgu = &dma_hw_desc->sg3u;
			अवरोध;
		शेष:
			BUG();
		पूर्ण

		*psgu |= cpu_to_le32(mult_value << mult_index);
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_set_dest_addr - set destination address पूर्णांकo the descriptor
 */
अटल व्योम ppc440spe_desc_set_dest_addr(काष्ठा ppc440spe_adma_desc_slot *desc,
				काष्ठा ppc440spe_adma_chan *chan,
				dma_addr_t addrh, dma_addr_t addrl,
				u32 dst_idx)
अणु
	काष्ठा dma_cdb *dma_hw_desc;
	काष्ठा xor_cb *xor_hw_desc;
	phys_addr_t addr64, पंचांगphi, पंचांगplow;
	u32 *psgu, *psgl;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		अगर (!addrh) अणु
			addr64 = addrl;
			पंचांगphi = (addr64 >> 32);
			पंचांगplow = (addr64 & 0xFFFFFFFF);
		पूर्ण अन्यथा अणु
			पंचांगphi = addrh;
			पंचांगplow = addrl;
		पूर्ण
		dma_hw_desc = desc->hw_desc;

		psgu = dst_idx ? &dma_hw_desc->sg3u : &dma_hw_desc->sg2u;
		psgl = dst_idx ? &dma_hw_desc->sg3l : &dma_hw_desc->sg2l;

		*psgl = cpu_to_le32((u32)पंचांगplow);
		*psgu |= cpu_to_le32((u32)पंचांगphi);
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		xor_hw_desc = desc->hw_desc;
		xor_hw_desc->cbtal = addrl;
		xor_hw_desc->cbtah |= addrh;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_set_byte_count - set number of data bytes involved
 * पूर्णांकo the operation
 */
अटल व्योम ppc440spe_desc_set_byte_count(काष्ठा ppc440spe_adma_desc_slot *desc,
				काष्ठा ppc440spe_adma_chan *chan,
				u32 byte_count)
अणु
	काष्ठा dma_cdb *dma_hw_desc;
	काष्ठा xor_cb *xor_hw_desc;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		dma_hw_desc = desc->hw_desc;
		dma_hw_desc->cnt = cpu_to_le32(byte_count);
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		xor_hw_desc = desc->hw_desc;
		xor_hw_desc->cbbc = byte_count;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_set_rxor_block_size - set RXOR block size
 */
अटल अंतरभूत व्योम ppc440spe_desc_set_rxor_block_size(u32 byte_count)
अणु
	/* assume that byte_count is aligned on the 512-boundary;
	 * thus ग_लिखो it directly to the रेजिस्टर (bits 23:31 are
	 * reserved there).
	 */
	dcr_ग_लिखो(ppc440spe_mq_dcr_host, DCRN_MQ0_CF2H, byte_count);
पूर्ण

/**
 * ppc440spe_desc_set_dcheck - set CHECK pattern
 */
अटल व्योम ppc440spe_desc_set_dcheck(काष्ठा ppc440spe_adma_desc_slot *desc,
				काष्ठा ppc440spe_adma_chan *chan, u8 *qword)
अणु
	काष्ठा dma_cdb *dma_hw_desc;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		dma_hw_desc = desc->hw_desc;
		ioग_लिखो32(qword[0], &dma_hw_desc->sg3l);
		ioग_लिखो32(qword[4], &dma_hw_desc->sg3u);
		ioग_लिखो32(qword[8], &dma_hw_desc->sg2l);
		ioग_लिखो32(qword[12], &dma_hw_desc->sg2u);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * ppc440spe_xor_set_link - set link address in xor CB
 */
अटल व्योम ppc440spe_xor_set_link(काष्ठा ppc440spe_adma_desc_slot *prev_desc,
				काष्ठा ppc440spe_adma_desc_slot *next_desc)
अणु
	काष्ठा xor_cb *xor_hw_desc = prev_desc->hw_desc;

	अगर (unlikely(!next_desc || !(next_desc->phys))) अणु
		prपूर्णांकk(KERN_ERR "%s: next_desc=0x%p; next_desc->phys=0x%llx\n",
			__func__, next_desc,
			next_desc ? next_desc->phys : 0);
		BUG();
	पूर्ण

	xor_hw_desc->cbs = 0;
	xor_hw_desc->cblal = next_desc->phys;
	xor_hw_desc->cblah = 0;
	xor_hw_desc->cbc |= XOR_CBCR_LNK_BIT;
पूर्ण

/**
 * ppc440spe_desc_set_link - set the address of descriptor following this
 * descriptor in chain
 */
अटल व्योम ppc440spe_desc_set_link(काष्ठा ppc440spe_adma_chan *chan,
				काष्ठा ppc440spe_adma_desc_slot *prev_desc,
				काष्ठा ppc440spe_adma_desc_slot *next_desc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ppc440spe_adma_desc_slot *tail = next_desc;

	अगर (unlikely(!prev_desc || !next_desc ||
		(prev_desc->hw_next && prev_desc->hw_next != next_desc))) अणु
		/* If previous next is overwritten something is wrong.
		 * though we may refetch from append to initiate list
		 * processing; in this हाल - it's ok.
		 */
		prपूर्णांकk(KERN_ERR "%s: prev_desc=0x%p; next_desc=0x%p; "
			"prev->hw_next=0x%p\n", __func__, prev_desc,
			next_desc, prev_desc ? prev_desc->hw_next : 0);
		BUG();
	पूर्ण

	local_irq_save(flags);

	/* करो s/w chaining both क्रम DMA and XOR descriptors */
	prev_desc->hw_next = next_desc;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		/* bind descriptor to the chain */
		जबतक (tail->hw_next)
			tail = tail->hw_next;
		xor_last_linked = tail;

		अगर (prev_desc == xor_last_submit)
			/* करो not link to the last submitted CB */
			अवरोध;
		ppc440spe_xor_set_link(prev_desc, next_desc);
		अवरोध;
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/**
 * ppc440spe_desc_get_link - get the address of the descriptor that
 * follows this one
 */
अटल अंतरभूत u32 ppc440spe_desc_get_link(काष्ठा ppc440spe_adma_desc_slot *desc,
					काष्ठा ppc440spe_adma_chan *chan)
अणु
	अगर (!desc->hw_next)
		वापस 0;

	वापस desc->hw_next->phys;
पूर्ण

/**
 * ppc440spe_desc_is_aligned - check alignment
 */
अटल अंतरभूत पूर्णांक ppc440spe_desc_is_aligned(
	काष्ठा ppc440spe_adma_desc_slot *desc, पूर्णांक num_slots)
अणु
	वापस (desc->idx & (num_slots - 1)) ? 0 : 1;
पूर्ण

/**
 * ppc440spe_chan_xor_slot_count - get the number of slots necessary क्रम
 * XOR operation
 */
अटल पूर्णांक ppc440spe_chan_xor_slot_count(माप_प्रकार len, पूर्णांक src_cnt,
			पूर्णांक *slots_per_op)
अणु
	पूर्णांक slot_cnt;

	/* each XOR descriptor provides up to 16 source opeअक्रमs */
	slot_cnt = *slots_per_op = (src_cnt + XOR_MAX_OPS - 1)/XOR_MAX_OPS;

	अगर (likely(len <= PPC440SPE_ADMA_XOR_MAX_BYTE_COUNT))
		वापस slot_cnt;

	prपूर्णांकk(KERN_ERR "%s: len %d > max %d !!\n",
		__func__, len, PPC440SPE_ADMA_XOR_MAX_BYTE_COUNT);
	BUG();
	वापस slot_cnt;
पूर्ण

/**
 * ppc440spe_dma2_pq_slot_count - get the number of slots necessary क्रम
 * DMA2 PQ operation
 */
अटल पूर्णांक ppc440spe_dma2_pq_slot_count(dma_addr_t *srcs,
		पूर्णांक src_cnt, माप_प्रकार len)
अणु
	चिन्हित दीर्घ दीर्घ order = 0;
	पूर्णांक state = 0;
	पूर्णांक addr_count = 0;
	पूर्णांक i;
	क्रम (i = 1; i < src_cnt; i++) अणु
		dma_addr_t cur_addr = srcs[i];
		dma_addr_t old_addr = srcs[i-1];
		चयन (state) अणु
		हाल 0:
			अगर (cur_addr == old_addr + len) अणु
				/* direct RXOR */
				order = 1;
				state = 1;
				अगर (i == src_cnt-1)
					addr_count++;
			पूर्ण अन्यथा अगर (old_addr == cur_addr + len) अणु
				/* reverse RXOR */
				order = -1;
				state = 1;
				अगर (i == src_cnt-1)
					addr_count++;
			पूर्ण अन्यथा अणु
				state = 3;
			पूर्ण
			अवरोध;
		हाल 1:
			अगर (i == src_cnt-2 || (order == -1
				&& cur_addr != old_addr - len)) अणु
				order = 0;
				state = 0;
				addr_count++;
			पूर्ण अन्यथा अगर (cur_addr == old_addr + len*order) अणु
				state = 2;
				अगर (i == src_cnt-1)
					addr_count++;
			पूर्ण अन्यथा अगर (cur_addr == old_addr + 2*len) अणु
				state = 2;
				अगर (i == src_cnt-1)
					addr_count++;
			पूर्ण अन्यथा अगर (cur_addr == old_addr + 3*len) अणु
				state = 2;
				अगर (i == src_cnt-1)
					addr_count++;
			पूर्ण अन्यथा अणु
				order = 0;
				state = 0;
				addr_count++;
			पूर्ण
			अवरोध;
		हाल 2:
			order = 0;
			state = 0;
			addr_count++;
				अवरोध;
		पूर्ण
		अगर (state == 3)
			अवरोध;
	पूर्ण
	अगर (src_cnt <= 1 || (state != 1 && state != 2)) अणु
		pr_err("%s: src_cnt=%d, state=%d, addr_count=%d, order=%lld\n",
			__func__, src_cnt, state, addr_count, order);
		क्रम (i = 0; i < src_cnt; i++)
			pr_err("\t[%d] 0x%llx \n", i, srcs[i]);
		BUG();
	पूर्ण

	वापस (addr_count + XOR_MAX_OPS - 1) / XOR_MAX_OPS;
पूर्ण


/******************************************************************************
 * ADMA channel low-level routines
 ******************************************************************************/

अटल u32
ppc440spe_chan_get_current_descriptor(काष्ठा ppc440spe_adma_chan *chan);
अटल व्योम ppc440spe_chan_append(काष्ठा ppc440spe_adma_chan *chan);

/**
 * ppc440spe_adma_device_clear_eot_status - पूर्णांकerrupt ack to XOR or DMA engine
 */
अटल व्योम ppc440spe_adma_device_clear_eot_status(
					काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा dma_regs *dma_reg;
	काष्ठा xor_regs *xor_reg;
	u8 *p = chan->device->dma_desc_pool_virt;
	काष्ठा dma_cdb *cdb;
	u32 rv, i;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		/* पढ़ो FIFO to ack */
		dma_reg = chan->device->dma_reg;
		जबतक ((rv = ioपढ़ो32(&dma_reg->csfpl))) अणु
			i = rv & DMA_CDB_ADDR_MSK;
			cdb = (काष्ठा dma_cdb *)&p[i -
			    (u32)chan->device->dma_desc_pool];

			/* Clear opcode to ack. This is necessary क्रम
			 * ZeroSum operations only
			 */
			cdb->opc = 0;

			अगर (test_bit(PPC440SPE_RXOR_RUN,
			    &ppc440spe_rxor_state)) अणु
				/* probably this is a completed RXOR op,
				 * get poपूर्णांकer to CDB using the fact that
				 * physical and भव addresses of CDB
				 * in pools have the same offsets
				 */
				अगर (le32_to_cpu(cdb->sg1u) &
				    DMA_CUED_XOR_BASE) अणु
					/* this is a RXOR */
					clear_bit(PPC440SPE_RXOR_RUN,
						  &ppc440spe_rxor_state);
				पूर्ण
			पूर्ण

			अगर (rv & DMA_CDB_STATUS_MSK) अणु
				/* ZeroSum check failed
				 */
				काष्ठा ppc440spe_adma_desc_slot *iter;
				dma_addr_t phys = rv & ~DMA_CDB_MSK;

				/*
				 * Update the status of corresponding
				 * descriptor.
				 */
				list_क्रम_each_entry(iter, &chan->chain,
				    chain_node) अणु
					अगर (iter->phys == phys)
						अवरोध;
				पूर्ण
				/*
				 * अगर cannot find the corresponding
				 * slot it's a bug
				 */
				BUG_ON(&iter->chain_node == &chan->chain);

				अगर (iter->xor_check_result) अणु
					अगर (test_bit(PPC440SPE_DESC_PCHECK,
						     &iter->flags)) अणु
						*iter->xor_check_result |=
							SUM_CHECK_P_RESULT;
					पूर्ण अन्यथा
					अगर (test_bit(PPC440SPE_DESC_QCHECK,
						     &iter->flags)) अणु
						*iter->xor_check_result |=
							SUM_CHECK_Q_RESULT;
					पूर्ण अन्यथा
						BUG();
				पूर्ण
			पूर्ण
		पूर्ण

		rv = ioपढ़ो32(&dma_reg->dsts);
		अगर (rv) अणु
			pr_err("DMA%d err status: 0x%x\n",
			       chan->device->id, rv);
			/* ग_लिखो back to clear */
			ioग_लिखो32(rv, &dma_reg->dsts);
		पूर्ण
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		/* reset status bits to ack */
		xor_reg = chan->device->xor_reg;
		rv = ioपढ़ो32be(&xor_reg->sr);
		ioग_लिखो32be(rv, &xor_reg->sr);

		अगर (rv & (XOR_IE_ICBIE_BIT|XOR_IE_ICIE_BIT|XOR_IE_RPTIE_BIT)) अणु
			अगर (rv & XOR_IE_RPTIE_BIT) अणु
				/* Read PLB Timeout Error.
				 * Try to resubmit the CB
				 */
				u32 val = ioपढ़ो32be(&xor_reg->ccbalr);

				ioग_लिखो32be(val, &xor_reg->cblalr);

				val = ioपढ़ो32be(&xor_reg->crsr);
				ioग_लिखो32be(val | XOR_CRSR_XAE_BIT,
					    &xor_reg->crsr);
			पूर्ण अन्यथा
				pr_err("XOR ERR 0x%x status\n", rv);
			अवरोध;
		पूर्ण

		/*  अगर the XORcore is idle, but there are unprocessed CBs
		 * then refetch the s/w chain here
		 */
		अगर (!(ioपढ़ो32be(&xor_reg->sr) & XOR_SR_XCP_BIT) &&
		    करो_xor_refetch)
			ppc440spe_chan_append(chan);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_chan_is_busy - get the channel status
 */
अटल पूर्णांक ppc440spe_chan_is_busy(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा dma_regs *dma_reg;
	काष्ठा xor_regs *xor_reg;
	पूर्णांक busy = 0;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		dma_reg = chan->device->dma_reg;
		/*  अगर command FIFO's head and tail poपूर्णांकers are equal and
		 * status tail is the same as command, then channel is मुक्त
		 */
		अगर (ioपढ़ो16(&dma_reg->cpfhp) != ioपढ़ो16(&dma_reg->cpftp) ||
		    ioपढ़ो16(&dma_reg->cpftp) != ioपढ़ो16(&dma_reg->csftp))
			busy = 1;
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		/* use the special status bit क्रम the XORcore
		 */
		xor_reg = chan->device->xor_reg;
		busy = (ioपढ़ो32be(&xor_reg->sr) & XOR_SR_XCP_BIT) ? 1 : 0;
		अवरोध;
	पूर्ण

	वापस busy;
पूर्ण

/**
 * ppc440spe_chan_set_first_xor_descriptor -  init XORcore chain
 */
अटल व्योम ppc440spe_chan_set_first_xor_descriptor(
				काष्ठा ppc440spe_adma_chan *chan,
				काष्ठा ppc440spe_adma_desc_slot *next_desc)
अणु
	काष्ठा xor_regs *xor_reg = chan->device->xor_reg;

	अगर (ioपढ़ो32be(&xor_reg->sr) & XOR_SR_XCP_BIT)
		prपूर्णांकk(KERN_INFO "%s: Warn: XORcore is running "
			"when try to set the first CDB!\n",
			__func__);

	xor_last_submit = xor_last_linked = next_desc;

	ioग_लिखो32be(XOR_CRSR_64BA_BIT, &xor_reg->crsr);

	ioग_लिखो32be(next_desc->phys, &xor_reg->cblalr);
	ioग_लिखो32be(0, &xor_reg->cblahr);
	ioग_लिखो32be(ioपढ़ो32be(&xor_reg->cbcr) | XOR_CBCR_LNK_BIT,
		    &xor_reg->cbcr);

	chan->hw_chain_inited = 1;
पूर्ण

/**
 * ppc440spe_dma_put_desc - put DMA0,1 descriptor to FIFO.
 * called with irqs disabled
 */
अटल व्योम ppc440spe_dma_put_desc(काष्ठा ppc440spe_adma_chan *chan,
		काष्ठा ppc440spe_adma_desc_slot *desc)
अणु
	u32 pcdb;
	काष्ठा dma_regs *dma_reg = chan->device->dma_reg;

	pcdb = desc->phys;
	अगर (!test_bit(PPC440SPE_DESC_INT, &desc->flags))
		pcdb |= DMA_CDB_NO_INT;

	chan_last_sub[chan->device->id] = desc;

	ADMA_LL_DBG(prपूर्णांक_cb(chan, desc->hw_desc));

	ioग_लिखो32(pcdb, &dma_reg->cpfpl);
पूर्ण

/**
 * ppc440spe_chan_append - update the h/w chain in the channel
 */
अटल व्योम ppc440spe_chan_append(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा xor_regs *xor_reg;
	काष्ठा ppc440spe_adma_desc_slot *iter;
	काष्ठा xor_cb *xcb;
	u32 cur_desc;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		cur_desc = ppc440spe_chan_get_current_descriptor(chan);

		अगर (likely(cur_desc)) अणु
			iter = chan_last_sub[chan->device->id];
			BUG_ON(!iter);
		पूर्ण अन्यथा अणु
			/* first peer */
			iter = chan_first_cdb[chan->device->id];
			BUG_ON(!iter);
			ppc440spe_dma_put_desc(chan, iter);
			chan->hw_chain_inited = 1;
		पूर्ण

		/* is there something new to append */
		अगर (!iter->hw_next)
			अवरोध;

		/* flush descriptors from the s/w queue to fअगरo */
		list_क्रम_each_entry_जारी(iter, &chan->chain, chain_node) अणु
			ppc440spe_dma_put_desc(chan, iter);
			अगर (!iter->hw_next)
				अवरोध;
		पूर्ण
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		/* update h/w links and refetch */
		अगर (!xor_last_submit->hw_next)
			अवरोध;

		xor_reg = chan->device->xor_reg;
		/* the last linked CDB has to generate an पूर्णांकerrupt
		 * that we'd be able to append the next lists to h/w
		 * regardless of the XOR engine state at the moment of
		 * appending of these next lists
		 */
		xcb = xor_last_linked->hw_desc;
		xcb->cbc |= XOR_CBCR_CBCE_BIT;

		अगर (!(ioपढ़ो32be(&xor_reg->sr) & XOR_SR_XCP_BIT)) अणु
			/* XORcore is idle. Refetch now */
			करो_xor_refetch = 0;
			ppc440spe_xor_set_link(xor_last_submit,
				xor_last_submit->hw_next);

			ADMA_LL_DBG(prपूर्णांक_cb_list(chan,
				xor_last_submit->hw_next));

			xor_last_submit = xor_last_linked;
			ioग_लिखो32be(ioपढ़ो32be(&xor_reg->crsr) |
				    XOR_CRSR_RCBE_BIT | XOR_CRSR_64BA_BIT,
				    &xor_reg->crsr);
		पूर्ण अन्यथा अणु
			/* XORcore is running. Refetch later in the handler */
			करो_xor_refetch = 1;
		पूर्ण

		अवरोध;
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/**
 * ppc440spe_chan_get_current_descriptor - get the currently executed descriptor
 */
अटल u32
ppc440spe_chan_get_current_descriptor(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा dma_regs *dma_reg;
	काष्ठा xor_regs *xor_reg;

	अगर (unlikely(!chan->hw_chain_inited))
		/* h/w descriptor chain is not initialized yet */
		वापस 0;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		dma_reg = chan->device->dma_reg;
		वापस ioपढ़ो32(&dma_reg->acpl) & (~DMA_CDB_MSK);
	हाल PPC440SPE_XOR_ID:
		xor_reg = chan->device->xor_reg;
		वापस ioपढ़ो32be(&xor_reg->ccbalr);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ppc440spe_chan_run - enable the channel
 */
अटल व्योम ppc440spe_chan_run(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा xor_regs *xor_reg;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		/* DMAs are always enabled, करो nothing */
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		/* drain ग_लिखो buffer */
		xor_reg = chan->device->xor_reg;

		/* fetch descriptor poपूर्णांकed to in <link> */
		ioग_लिखो32be(XOR_CRSR_64BA_BIT | XOR_CRSR_XAE_BIT,
			    &xor_reg->crsr);
		अवरोध;
	पूर्ण
पूर्ण

/******************************************************************************
 * ADMA device level
 ******************************************************************************/

अटल व्योम ppc440spe_chan_start_null_xor(काष्ठा ppc440spe_adma_chan *chan);
अटल पूर्णांक ppc440spe_adma_alloc_chan_resources(काष्ठा dma_chan *chan);

अटल dma_cookie_t
ppc440spe_adma_tx_submit(काष्ठा dma_async_tx_descriptor *tx);

अटल व्योम ppc440spe_adma_set_dest(काष्ठा ppc440spe_adma_desc_slot *tx,
				    dma_addr_t addr, पूर्णांक index);
अटल व्योम
ppc440spe_adma_स_नकल_xor_set_src(काष्ठा ppc440spe_adma_desc_slot *tx,
				  dma_addr_t addr, पूर्णांक index);

अटल व्योम
ppc440spe_adma_pq_set_dest(काष्ठा ppc440spe_adma_desc_slot *tx,
			   dma_addr_t *paddr, अचिन्हित दीर्घ flags);
अटल व्योम
ppc440spe_adma_pq_set_src(काष्ठा ppc440spe_adma_desc_slot *tx,
			  dma_addr_t addr, पूर्णांक index);
अटल व्योम
ppc440spe_adma_pq_set_src_mult(काष्ठा ppc440spe_adma_desc_slot *tx,
			       अचिन्हित अक्षर mult, पूर्णांक index, पूर्णांक dst_pos);
अटल व्योम
ppc440spe_adma_pqzero_sum_set_dest(काष्ठा ppc440spe_adma_desc_slot *tx,
				   dma_addr_t paddr, dma_addr_t qaddr);

अटल काष्ठा page *ppc440spe_rxor_srcs[32];

/**
 * ppc440spe_can_rxor - check अगर the opeअक्रमs may be processed with RXOR
 */
अटल पूर्णांक ppc440spe_can_rxor(काष्ठा page **srcs, पूर्णांक src_cnt, माप_प्रकार len)
अणु
	पूर्णांक i, order = 0, state = 0;
	पूर्णांक idx = 0;

	अगर (unlikely(!(src_cnt > 1)))
		वापस 0;

	BUG_ON(src_cnt > ARRAY_SIZE(ppc440spe_rxor_srcs));

	/* Skip holes in the source list beक्रमe checking */
	क्रम (i = 0; i < src_cnt; i++) अणु
		अगर (!srcs[i])
			जारी;
		ppc440spe_rxor_srcs[idx++] = srcs[i];
	पूर्ण
	src_cnt = idx;

	क्रम (i = 1; i < src_cnt; i++) अणु
		अक्षर *cur_addr = page_address(ppc440spe_rxor_srcs[i]);
		अक्षर *old_addr = page_address(ppc440spe_rxor_srcs[i - 1]);

		चयन (state) अणु
		हाल 0:
			अगर (cur_addr == old_addr + len) अणु
				/* direct RXOR */
				order = 1;
				state = 1;
			पूर्ण अन्यथा अगर (old_addr == cur_addr + len) अणु
				/* reverse RXOR */
				order = -1;
				state = 1;
			पूर्ण अन्यथा
				जाओ out;
			अवरोध;
		हाल 1:
			अगर ((i == src_cnt - 2) ||
			    (order == -1 && cur_addr != old_addr - len)) अणु
				order = 0;
				state = 0;
			पूर्ण अन्यथा अगर ((cur_addr == old_addr + len * order) ||
				   (cur_addr == old_addr + 2 * len) ||
				   (cur_addr == old_addr + 3 * len)) अणु
				state = 2;
			पूर्ण अन्यथा अणु
				order = 0;
				state = 0;
			पूर्ण
			अवरोध;
		हाल 2:
			order = 0;
			state = 0;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (state == 1 || state == 2)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * ppc440spe_adma_device_estimate - estimate the efficiency of processing
 *	the operation given on this channel. It's assumed that 'chan' is
 *	capable to process 'cap' type of operation.
 * @chan: channel to use
 * @cap: type of transaction
 * @dst_lst: array of destination poपूर्णांकers
 * @dst_cnt: number of destination opeअक्रमs
 * @src_lst: array of source poपूर्णांकers
 * @src_cnt: number of source opeअक्रमs
 * @src_sz: size of each source opeअक्रम
 */
अटल पूर्णांक ppc440spe_adma_estimate(काष्ठा dma_chan *chan,
	क्रमागत dma_transaction_type cap, काष्ठा page **dst_lst, पूर्णांक dst_cnt,
	काष्ठा page **src_lst, पूर्णांक src_cnt, माप_प्रकार src_sz)
अणु
	पूर्णांक ef = 1;

	अगर (cap == DMA_PQ || cap == DMA_PQ_VAL) अणु
		/* If RAID-6 capabilities were not activated करोn't try
		 * to use them
		 */
		अगर (unlikely(!ppc440spe_r6_enabled))
			वापस -1;
	पूर्ण
	/*  In the current implementation of ppc440spe ADMA driver it
	 * makes sense to pick out only pq हाल, because it may be
	 * processed:
	 * (1) either using Biskup method on DMA2;
	 * (2) or on DMA0/1.
	 *  Thus we give a favour to (1) अगर the sources are suitable;
	 * अन्यथा let it be processed on one of the DMA0/1 engines.
	 *  In the sum_product हाल where destination is also the
	 * source process it on DMA0/1 only.
	 */
	अगर (cap == DMA_PQ && chan->chan_id == PPC440SPE_XOR_ID) अणु

		अगर (dst_cnt == 1 && src_cnt == 2 && dst_lst[0] == src_lst[1])
			ef = 0; /* sum_product हाल, process on DMA0/1 */
		अन्यथा अगर (ppc440spe_can_rxor(src_lst, src_cnt, src_sz))
			ef = 3; /* override (DMA0/1 + idle) */
		अन्यथा
			ef = 0; /* can't process on DMA2 अगर !rxor */
	पूर्ण

	/* channel idleness increases the priority */
	अगर (likely(ef) &&
	    !ppc440spe_chan_is_busy(to_ppc440spe_adma_chan(chan)))
		ef++;

	वापस ef;
पूर्ण

काष्ठा dma_chan *
ppc440spe_async_tx_find_best_channel(क्रमागत dma_transaction_type cap,
	काष्ठा page **dst_lst, पूर्णांक dst_cnt, काष्ठा page **src_lst,
	पूर्णांक src_cnt, माप_प्रकार src_sz)
अणु
	काष्ठा dma_chan *best_chan = शून्य;
	काष्ठा ppc_dma_chan_ref *ref;
	पूर्णांक best_rank = -1;

	अगर (unlikely(!src_sz))
		वापस शून्य;
	अगर (src_sz > PAGE_SIZE) अणु
		/*
		 * should a user of the api ever pass > PAGE_SIZE requests
		 * we sort out हालs where temporary page-sized buffers
		 * are used.
		 */
		चयन (cap) अणु
		हाल DMA_PQ:
			अगर (src_cnt == 1 && dst_lst[1] == src_lst[0])
				वापस शून्य;
			अगर (src_cnt == 2 && dst_lst[1] == src_lst[1])
				वापस शून्य;
			अवरोध;
		हाल DMA_PQ_VAL:
		हाल DMA_XOR_VAL:
			वापस शून्य;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(ref, &ppc440spe_adma_chan_list, node) अणु
		अगर (dma_has_cap(cap, ref->chan->device->cap_mask)) अणु
			पूर्णांक rank;

			rank = ppc440spe_adma_estimate(ref->chan, cap, dst_lst,
					dst_cnt, src_lst, src_cnt, src_sz);
			अगर (rank > best_rank) अणु
				best_rank = rank;
				best_chan = ref->chan;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस best_chan;
पूर्ण
EXPORT_SYMBOL_GPL(ppc440spe_async_tx_find_best_channel);

/**
 * ppc440spe_get_group_entry - get group entry with index idx
 * @tdesc: is the last allocated slot in the group.
 */
अटल काष्ठा ppc440spe_adma_desc_slot *
ppc440spe_get_group_entry(काष्ठा ppc440spe_adma_desc_slot *tdesc, u32 entry_idx)
अणु
	काष्ठा ppc440spe_adma_desc_slot *iter = tdesc->group_head;
	पूर्णांक i = 0;

	अगर (entry_idx < 0 || entry_idx >= (tdesc->src_cnt + tdesc->dst_cnt)) अणु
		prपूर्णांकk("%s: entry_idx %d, src_cnt %d, dst_cnt %d\n",
			__func__, entry_idx, tdesc->src_cnt, tdesc->dst_cnt);
		BUG();
	पूर्ण

	list_क्रम_each_entry(iter, &tdesc->group_list, chain_node) अणु
		अगर (i++ == entry_idx)
			अवरोध;
	पूर्ण
	वापस iter;
पूर्ण

/**
 * ppc440spe_adma_मुक्त_slots - flags descriptor slots क्रम reuse
 * @slot: Slot to मुक्त
 * Caller must hold &ppc440spe_chan->lock जबतक calling this function
 */
अटल व्योम ppc440spe_adma_मुक्त_slots(काष्ठा ppc440spe_adma_desc_slot *slot,
				      काष्ठा ppc440spe_adma_chan *chan)
अणु
	पूर्णांक stride = slot->slots_per_op;

	जबतक (stride--) अणु
		slot->slots_per_op = 0;
		slot = list_entry(slot->slot_node.next,
				काष्ठा ppc440spe_adma_desc_slot,
				slot_node);
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_run_tx_complete_actions - call functions to be called
 * upon completion
 */
अटल dma_cookie_t ppc440spe_adma_run_tx_complete_actions(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		काष्ठा ppc440spe_adma_chan *chan,
		dma_cookie_t cookie)
अणु
	BUG_ON(desc->async_tx.cookie < 0);
	अगर (desc->async_tx.cookie > 0) अणु
		cookie = desc->async_tx.cookie;
		desc->async_tx.cookie = 0;

		dma_descriptor_unmap(&desc->async_tx);
		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		dmaengine_desc_get_callback_invoke(&desc->async_tx, शून्य);
	पूर्ण

	/* run dependent operations */
	dma_run_dependencies(&desc->async_tx);

	वापस cookie;
पूर्ण

/**
 * ppc440spe_adma_clean_slot - clean up CDB slot (अगर ack is set)
 */
अटल पूर्णांक ppc440spe_adma_clean_slot(काष्ठा ppc440spe_adma_desc_slot *desc,
		काष्ठा ppc440spe_adma_chan *chan)
अणु
	/* the client is allowed to attach dependent operations
	 * until 'ack' is set
	 */
	अगर (!async_tx_test_ack(&desc->async_tx))
		वापस 0;

	/* leave the last descriptor in the chain
	 * so we can append to it
	 */
	अगर (list_is_last(&desc->chain_node, &chan->chain) ||
	    desc->phys == ppc440spe_chan_get_current_descriptor(chan))
		वापस 1;

	अगर (chan->device->id != PPC440SPE_XOR_ID) अणु
		/* our DMA पूर्णांकerrupt handler clears opc field of
		 * each processed descriptor. For all types of
		 * operations except क्रम ZeroSum we करो not actually
		 * need ack from the पूर्णांकerrupt handler. ZeroSum is a
		 * special हाल since the result of this operation
		 * is available from the handler only, so अगर we see
		 * such type of descriptor (which is unprocessed yet)
		 * then leave it in chain.
		 */
		काष्ठा dma_cdb *cdb = desc->hw_desc;
		अगर (cdb->opc == DMA_CDB_OPC_DCHECK128)
			वापस 1;
	पूर्ण

	dev_dbg(chan->device->common.dev, "\tfree slot %llx: %d stride: %d\n",
		desc->phys, desc->idx, desc->slots_per_op);

	list_del(&desc->chain_node);
	ppc440spe_adma_मुक्त_slots(desc, chan);
	वापस 0;
पूर्ण

/**
 * __ppc440spe_adma_slot_cleanup - this is the common clean-up routine
 *	which runs through the channel CDBs list until reach the descriptor
 *	currently processed. When routine determines that all CDBs of group
 *	are completed then corresponding callbacks (अगर any) are called and slots
 *	are मुक्तd.
 */
अटल व्योम __ppc440spe_adma_slot_cleanup(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा ppc440spe_adma_desc_slot *iter, *_iter, *group_start = शून्य;
	dma_cookie_t cookie = 0;
	u32 current_desc = ppc440spe_chan_get_current_descriptor(chan);
	पूर्णांक busy = ppc440spe_chan_is_busy(chan);
	पूर्णांक seen_current = 0, slot_cnt = 0, slots_per_op = 0;

	dev_dbg(chan->device->common.dev, "ppc440spe adma%d: %s\n",
		chan->device->id, __func__);

	अगर (!current_desc) अणु
		/*  There were no transactions yet, so
		 * nothing to clean
		 */
		वापस;
	पूर्ण

	/* मुक्त completed slots from the chain starting with
	 * the oldest descriptor
	 */
	list_क्रम_each_entry_safe(iter, _iter, &chan->chain,
					chain_node) अणु
		dev_dbg(chan->device->common.dev, "\tcookie: %d slot: %d "
		    "busy: %d this_desc: %#llx next_desc: %#x "
		    "cur: %#x ack: %d\n",
		    iter->async_tx.cookie, iter->idx, busy, iter->phys,
		    ppc440spe_desc_get_link(iter, chan), current_desc,
		    async_tx_test_ack(&iter->async_tx));
		prefetch(_iter);
		prefetch(&_iter->async_tx);

		/* करो not advance past the current descriptor loaded पूर्णांकo the
		 * hardware channel,subsequent descriptors are either in process
		 * or have not been submitted
		 */
		अगर (seen_current)
			अवरोध;

		/* stop the search अगर we reach the current descriptor and the
		 * channel is busy, or अगर it appears that the current descriptor
		 * needs to be re-पढ़ो (i.e. has been appended to)
		 */
		अगर (iter->phys == current_desc) अणु
			BUG_ON(seen_current++);
			अगर (busy || ppc440spe_desc_get_link(iter, chan)) अणु
				/* not all descriptors of the group have
				 * been completed; निकास.
				 */
				अवरोध;
			पूर्ण
		पूर्ण

		/* detect the start of a group transaction */
		अगर (!slot_cnt && !slots_per_op) अणु
			slot_cnt = iter->slot_cnt;
			slots_per_op = iter->slots_per_op;
			अगर (slot_cnt <= slots_per_op) अणु
				slot_cnt = 0;
				slots_per_op = 0;
			पूर्ण
		पूर्ण

		अगर (slot_cnt) अणु
			अगर (!group_start)
				group_start = iter;
			slot_cnt -= slots_per_op;
		पूर्ण

		/* all the members of a group are complete */
		अगर (slots_per_op != 0 && slot_cnt == 0) अणु
			काष्ठा ppc440spe_adma_desc_slot *grp_iter, *_grp_iter;
			पूर्णांक end_of_chain = 0;

			/* clean up the group */
			slot_cnt = group_start->slot_cnt;
			grp_iter = group_start;
			list_क्रम_each_entry_safe_from(grp_iter, _grp_iter,
				&chan->chain, chain_node) अणु

				cookie = ppc440spe_adma_run_tx_complete_actions(
					grp_iter, chan, cookie);

				slot_cnt -= slots_per_op;
				end_of_chain = ppc440spe_adma_clean_slot(
				    grp_iter, chan);
				अगर (end_of_chain && slot_cnt) अणु
					/* Should रुको क्रम ZeroSum completion */
					अगर (cookie > 0)
						chan->common.completed_cookie = cookie;
					वापस;
				पूर्ण

				अगर (slot_cnt == 0 || end_of_chain)
					अवरोध;
			पूर्ण

			/* the group should be complete at this poपूर्णांक */
			BUG_ON(slot_cnt);

			slots_per_op = 0;
			group_start = शून्य;
			अगर (end_of_chain)
				अवरोध;
			अन्यथा
				जारी;
		पूर्ण अन्यथा अगर (slots_per_op) /* रुको क्रम group completion */
			जारी;

		cookie = ppc440spe_adma_run_tx_complete_actions(iter, chan,
		    cookie);

		अगर (ppc440spe_adma_clean_slot(iter, chan))
			अवरोध;
	पूर्ण

	BUG_ON(!seen_current);

	अगर (cookie > 0) अणु
		chan->common.completed_cookie = cookie;
		pr_debug("\tcompleted cookie %d\n", cookie);
	पूर्ण

पूर्ण

/**
 * ppc440spe_adma_tasklet - clean up watch-करोg initiator
 */
अटल व्योम ppc440spe_adma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ppc440spe_adma_chan *chan = from_tasklet(chan, t, irq_tasklet);

	spin_lock_nested(&chan->lock, SINGLE_DEPTH_NESTING);
	__ppc440spe_adma_slot_cleanup(chan);
	spin_unlock(&chan->lock);
पूर्ण

/**
 * ppc440spe_adma_slot_cleanup - clean up scheduled initiator
 */
अटल व्योम ppc440spe_adma_slot_cleanup(काष्ठा ppc440spe_adma_chan *chan)
अणु
	spin_lock_bh(&chan->lock);
	__ppc440spe_adma_slot_cleanup(chan);
	spin_unlock_bh(&chan->lock);
पूर्ण

/**
 * ppc440spe_adma_alloc_slots - allocate मुक्त slots (अगर any)
 */
अटल काष्ठा ppc440spe_adma_desc_slot *ppc440spe_adma_alloc_slots(
		काष्ठा ppc440spe_adma_chan *chan, पूर्णांक num_slots,
		पूर्णांक slots_per_op)
अणु
	काष्ठा ppc440spe_adma_desc_slot *iter = शून्य, *_iter;
	काष्ठा ppc440spe_adma_desc_slot *alloc_start = शून्य;
	काष्ठा list_head chain = LIST_HEAD_INIT(chain);
	पूर्णांक slots_found, retry = 0;


	BUG_ON(!num_slots || !slots_per_op);
	/* start search from the last allocated descrtiptor
	 * अगर a contiguous allocation can not be found start searching
	 * from the beginning of the list
	 */
retry:
	slots_found = 0;
	अगर (retry == 0)
		iter = chan->last_used;
	अन्यथा
		iter = list_entry(&chan->all_slots,
				  काष्ठा ppc440spe_adma_desc_slot,
				  slot_node);
	list_क्रम_each_entry_safe_जारी(iter, _iter, &chan->all_slots,
	    slot_node) अणु
		prefetch(_iter);
		prefetch(&_iter->async_tx);
		अगर (iter->slots_per_op) अणु
			slots_found = 0;
			जारी;
		पूर्ण

		/* start the allocation अगर the slot is correctly aligned */
		अगर (!slots_found++)
			alloc_start = iter;

		अगर (slots_found == num_slots) अणु
			काष्ठा ppc440spe_adma_desc_slot *alloc_tail = शून्य;
			काष्ठा ppc440spe_adma_desc_slot *last_used = शून्य;

			iter = alloc_start;
			जबतक (num_slots) अणु
				पूर्णांक i;
				/* pre-ack all but the last descriptor */
				अगर (num_slots != slots_per_op)
					async_tx_ack(&iter->async_tx);

				list_add_tail(&iter->chain_node, &chain);
				alloc_tail = iter;
				iter->async_tx.cookie = 0;
				iter->hw_next = शून्य;
				iter->flags = 0;
				iter->slot_cnt = num_slots;
				iter->xor_check_result = शून्य;
				क्रम (i = 0; i < slots_per_op; i++) अणु
					iter->slots_per_op = slots_per_op - i;
					last_used = iter;
					iter = list_entry(iter->slot_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						slot_node);
				पूर्ण
				num_slots -= slots_per_op;
			पूर्ण
			alloc_tail->group_head = alloc_start;
			alloc_tail->async_tx.cookie = -EBUSY;
			list_splice(&chain, &alloc_tail->group_list);
			chan->last_used = last_used;
			वापस alloc_tail;
		पूर्ण
	पूर्ण
	अगर (!retry++)
		जाओ retry;

	/* try to मुक्त some slots अगर the allocation fails */
	tasklet_schedule(&chan->irq_tasklet);
	वापस शून्य;
पूर्ण

/**
 * ppc440spe_adma_alloc_chan_resources -  allocate pools क्रम CDB slots
 */
अटल पूर्णांक ppc440spe_adma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *slot = शून्य;
	अक्षर *hw_desc;
	पूर्णांक i, db_sz;
	पूर्णांक init;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);
	init = ppc440spe_chan->slots_allocated ? 0 : 1;
	chan->chan_id = ppc440spe_chan->device->id;

	/* Allocate descriptor slots */
	i = ppc440spe_chan->slots_allocated;
	अगर (ppc440spe_chan->device->id != PPC440SPE_XOR_ID)
		db_sz = माप(काष्ठा dma_cdb);
	अन्यथा
		db_sz = माप(काष्ठा xor_cb);

	क्रम (; i < (ppc440spe_chan->device->pool_size / db_sz); i++) अणु
		slot = kzalloc(माप(काष्ठा ppc440spe_adma_desc_slot),
			       GFP_KERNEL);
		अगर (!slot) अणु
			prपूर्णांकk(KERN_INFO "SPE ADMA Channel only initialized"
				" %d descriptor slots", i--);
			अवरोध;
		पूर्ण

		hw_desc = (अक्षर *) ppc440spe_chan->device->dma_desc_pool_virt;
		slot->hw_desc = (व्योम *) &hw_desc[i * db_sz];
		dma_async_tx_descriptor_init(&slot->async_tx, chan);
		slot->async_tx.tx_submit = ppc440spe_adma_tx_submit;
		INIT_LIST_HEAD(&slot->chain_node);
		INIT_LIST_HEAD(&slot->slot_node);
		INIT_LIST_HEAD(&slot->group_list);
		slot->phys = ppc440spe_chan->device->dma_desc_pool + i * db_sz;
		slot->idx = i;

		spin_lock_bh(&ppc440spe_chan->lock);
		ppc440spe_chan->slots_allocated++;
		list_add_tail(&slot->slot_node, &ppc440spe_chan->all_slots);
		spin_unlock_bh(&ppc440spe_chan->lock);
	पूर्ण

	अगर (i && !ppc440spe_chan->last_used) अणु
		ppc440spe_chan->last_used =
			list_entry(ppc440spe_chan->all_slots.next,
				काष्ठा ppc440spe_adma_desc_slot,
				slot_node);
	पूर्ण

	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d: allocated %d descriptor slots\n",
		ppc440spe_chan->device->id, i);

	/* initialize the channel and the chain with a null operation */
	अगर (init) अणु
		चयन (ppc440spe_chan->device->id) अणु
		हाल PPC440SPE_DMA0_ID:
		हाल PPC440SPE_DMA1_ID:
			ppc440spe_chan->hw_chain_inited = 0;
			/* Use WXOR क्रम self-testing */
			अगर (!ppc440spe_r6_tchan)
				ppc440spe_r6_tchan = ppc440spe_chan;
			अवरोध;
		हाल PPC440SPE_XOR_ID:
			ppc440spe_chan_start_null_xor(ppc440spe_chan);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		ppc440spe_chan->needs_unmap = 1;
	पूर्ण

	वापस (i > 0) ? i : -ENOMEM;
पूर्ण

/**
 * ppc440spe_rxor_set_region_data -
 */
अटल व्योम ppc440spe_rxor_set_region(काष्ठा ppc440spe_adma_desc_slot *desc,
	u8 xor_arg_no, u32 mask)
अणु
	काष्ठा xor_cb *xcb = desc->hw_desc;

	xcb->ops[xor_arg_no].h |= mask;
पूर्ण

/**
 * ppc440spe_rxor_set_src -
 */
अटल व्योम ppc440spe_rxor_set_src(काष्ठा ppc440spe_adma_desc_slot *desc,
	u8 xor_arg_no, dma_addr_t addr)
अणु
	काष्ठा xor_cb *xcb = desc->hw_desc;

	xcb->ops[xor_arg_no].h |= DMA_CUED_XOR_BASE;
	xcb->ops[xor_arg_no].l = addr;
पूर्ण

/**
 * ppc440spe_rxor_set_mult -
 */
अटल व्योम ppc440spe_rxor_set_mult(काष्ठा ppc440spe_adma_desc_slot *desc,
	u8 xor_arg_no, u8 idx, u8 mult)
अणु
	काष्ठा xor_cb *xcb = desc->hw_desc;

	xcb->ops[xor_arg_no].h |= mult << (DMA_CUED_MULT1_OFF + idx * 8);
पूर्ण

/**
 * ppc440spe_adma_check_threshold - append CDBs to h/w chain अगर threshold
 *	has been achieved
 */
अटल व्योम ppc440spe_adma_check_threshold(काष्ठा ppc440spe_adma_chan *chan)
अणु
	dev_dbg(chan->device->common.dev, "ppc440spe adma%d: pending: %d\n",
		chan->device->id, chan->pending);

	अगर (chan->pending >= PPC440SPE_ADMA_THRESHOLD) अणु
		chan->pending = 0;
		ppc440spe_chan_append(chan);
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_tx_submit - submit new descriptor group to the channel
 *	(it's not necessary that descriptors will be submitted to the h/w
 *	chains too right now)
 */
अटल dma_cookie_t ppc440spe_adma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा ppc440spe_adma_desc_slot *sw_desc;
	काष्ठा ppc440spe_adma_chan *chan = to_ppc440spe_adma_chan(tx->chan);
	काष्ठा ppc440spe_adma_desc_slot *group_start, *old_chain_tail;
	पूर्णांक slot_cnt;
	पूर्णांक slots_per_op;
	dma_cookie_t cookie;

	sw_desc = tx_to_ppc440spe_adma_slot(tx);

	group_start = sw_desc->group_head;
	slot_cnt = group_start->slot_cnt;
	slots_per_op = group_start->slots_per_op;

	spin_lock_bh(&chan->lock);
	cookie = dma_cookie_assign(tx);

	अगर (unlikely(list_empty(&chan->chain))) अणु
		/* first peer */
		list_splice_init(&sw_desc->group_list, &chan->chain);
		chan_first_cdb[chan->device->id] = group_start;
	पूर्ण अन्यथा अणु
		/* isn't first peer, bind CDBs to chain */
		old_chain_tail = list_entry(chan->chain.prev,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		list_splice_init(&sw_desc->group_list,
		    &old_chain_tail->chain_node);
		/* fix up the hardware chain */
		ppc440spe_desc_set_link(chan, old_chain_tail, group_start);
	पूर्ण

	/* increment the pending count by the number of operations */
	chan->pending += slot_cnt / slots_per_op;
	ppc440spe_adma_check_threshold(chan);
	spin_unlock_bh(&chan->lock);

	dev_dbg(chan->device->common.dev,
		"ppc440spe adma%d: %s cookie: %d slot: %d tx %p\n",
		chan->device->id, __func__,
		sw_desc->async_tx.cookie, sw_desc->idx, sw_desc);

	वापस cookie;
पूर्ण

/**
 * ppc440spe_adma_prep_dma_पूर्णांकerrupt - prepare CDB क्रम a pseuकरो DMA operation
 */
अटल काष्ठा dma_async_tx_descriptor *ppc440spe_adma_prep_dma_पूर्णांकerrupt(
		काष्ठा dma_chan *chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc, *group_start;
	पूर्णांक slot_cnt, slots_per_op;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);

	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d: %s\n", ppc440spe_chan->device->id,
		__func__);

	spin_lock_bh(&ppc440spe_chan->lock);
	slot_cnt = slots_per_op = 1;
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt,
			slots_per_op);
	अगर (sw_desc) अणु
		group_start = sw_desc->group_head;
		ppc440spe_desc_init_पूर्णांकerrupt(group_start, ppc440spe_chan);
		group_start->unmap_len = 0;
		sw_desc->async_tx.flags = flags;
	पूर्ण
	spin_unlock_bh(&ppc440spe_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

/**
 * ppc440spe_adma_prep_dma_स_नकल - prepare CDB क्रम a MEMCPY operation
 */
अटल काष्ठा dma_async_tx_descriptor *ppc440spe_adma_prep_dma_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dma_dest,
		dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc, *group_start;
	पूर्णांक slot_cnt, slots_per_op;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);

	अगर (unlikely(!len))
		वापस शून्य;

	BUG_ON(len > PPC440SPE_ADMA_DMA_MAX_BYTE_COUNT);

	spin_lock_bh(&ppc440spe_chan->lock);

	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d: %s len: %u int_en %d\n",
		ppc440spe_chan->device->id, __func__, len,
		flags & DMA_PREP_INTERRUPT ? 1 : 0);
	slot_cnt = slots_per_op = 1;
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt,
		slots_per_op);
	अगर (sw_desc) अणु
		group_start = sw_desc->group_head;
		ppc440spe_desc_init_स_नकल(group_start, flags);
		ppc440spe_adma_set_dest(group_start, dma_dest, 0);
		ppc440spe_adma_स_नकल_xor_set_src(group_start, dma_src, 0);
		ppc440spe_desc_set_byte_count(group_start, ppc440spe_chan, len);
		sw_desc->unmap_len = len;
		sw_desc->async_tx.flags = flags;
	पूर्ण
	spin_unlock_bh(&ppc440spe_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

/**
 * ppc440spe_adma_prep_dma_xor - prepare CDB क्रम a XOR operation
 */
अटल काष्ठा dma_async_tx_descriptor *ppc440spe_adma_prep_dma_xor(
		काष्ठा dma_chan *chan, dma_addr_t dma_dest,
		dma_addr_t *dma_src, u32 src_cnt, माप_प्रकार len,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc, *group_start;
	पूर्णांक slot_cnt, slots_per_op;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);

	ADMA_LL_DBG(prep_dma_xor_dbg(ppc440spe_chan->device->id,
				     dma_dest, dma_src, src_cnt));
	अगर (unlikely(!len))
		वापस शून्य;
	BUG_ON(len > PPC440SPE_ADMA_XOR_MAX_BYTE_COUNT);

	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d: %s src_cnt: %d len: %u int_en: %d\n",
		ppc440spe_chan->device->id, __func__, src_cnt, len,
		flags & DMA_PREP_INTERRUPT ? 1 : 0);

	spin_lock_bh(&ppc440spe_chan->lock);
	slot_cnt = ppc440spe_chan_xor_slot_count(len, src_cnt, &slots_per_op);
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt,
			slots_per_op);
	अगर (sw_desc) अणु
		group_start = sw_desc->group_head;
		ppc440spe_desc_init_xor(group_start, src_cnt, flags);
		ppc440spe_adma_set_dest(group_start, dma_dest, 0);
		जबतक (src_cnt--)
			ppc440spe_adma_स_नकल_xor_set_src(group_start,
				dma_src[src_cnt], src_cnt);
		ppc440spe_desc_set_byte_count(group_start, ppc440spe_chan, len);
		sw_desc->unmap_len = len;
		sw_desc->async_tx.flags = flags;
	पूर्ण
	spin_unlock_bh(&ppc440spe_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल अंतरभूत व्योम
ppc440spe_desc_set_xor_src_cnt(काष्ठा ppc440spe_adma_desc_slot *desc,
				पूर्णांक src_cnt);
अटल व्योम ppc440spe_init_rxor_cursor(काष्ठा ppc440spe_rxor *cursor);

/**
 * ppc440spe_adma_init_dma2rxor_slot -
 */
अटल व्योम ppc440spe_adma_init_dma2rxor_slot(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		dma_addr_t *src, पूर्णांक src_cnt)
अणु
	पूर्णांक i;

	/* initialize CDB */
	क्रम (i = 0; i < src_cnt; i++) अणु
		ppc440spe_adma_dma2rxor_prep_src(desc, &desc->rxor_cursor, i,
						 desc->src_cnt, (u32)src[i]);
	पूर्ण
पूर्ण

/**
 * ppc440spe_dma01_prep_mult -
 * क्रम Q operation where destination is also the source
 */
अटल काष्ठा ppc440spe_adma_desc_slot *ppc440spe_dma01_prep_mult(
		काष्ठा ppc440spe_adma_chan *ppc440spe_chan,
		dma_addr_t *dst, पूर्णांक dst_cnt, dma_addr_t *src, पूर्णांक src_cnt,
		स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_desc_slot *sw_desc = शून्य;
	अचिन्हित दीर्घ op = 0;
	पूर्णांक slot_cnt;

	set_bit(PPC440SPE_DESC_WXOR, &op);
	slot_cnt = 2;

	spin_lock_bh(&ppc440spe_chan->lock);

	/* use WXOR, each descriptor occupies one slot */
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt, 1);
	अगर (sw_desc) अणु
		काष्ठा ppc440spe_adma_chan *chan;
		काष्ठा ppc440spe_adma_desc_slot *iter;
		काष्ठा dma_cdb *hw_desc;

		chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);
		set_bits(op, &sw_desc->flags);
		sw_desc->src_cnt = src_cnt;
		sw_desc->dst_cnt = dst_cnt;
		/* First descriptor, zero data in the destination and copy it
		 * to q page using MULTICAST transfer.
		 */
		iter = list_first_entry(&sw_desc->group_list,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
		/* set 'next' poपूर्णांकer */
		iter->hw_next = list_entry(iter->chain_node.next,
					   काष्ठा ppc440spe_adma_desc_slot,
					   chain_node);
		clear_bit(PPC440SPE_DESC_INT, &iter->flags);
		hw_desc = iter->hw_desc;
		hw_desc->opc = DMA_CDB_OPC_MULTICAST;

		ppc440spe_desc_set_dest_addr(iter, chan,
					     DMA_CUED_XOR_BASE, dst[0], 0);
		ppc440spe_desc_set_dest_addr(iter, chan, 0, dst[1], 1);
		ppc440spe_desc_set_src_addr(iter, chan, 0, DMA_CUED_XOR_HB,
					    src[0]);
		ppc440spe_desc_set_byte_count(iter, ppc440spe_chan, len);
		iter->unmap_len = len;

		/*
		 * Second descriptor, multiply data from the q page
		 * and store the result in real destination.
		 */
		iter = list_first_entry(&iter->chain_node,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
		iter->hw_next = शून्य;
		अगर (flags & DMA_PREP_INTERRUPT)
			set_bit(PPC440SPE_DESC_INT, &iter->flags);
		अन्यथा
			clear_bit(PPC440SPE_DESC_INT, &iter->flags);

		hw_desc = iter->hw_desc;
		hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
		ppc440spe_desc_set_src_addr(iter, chan, 0,
					    DMA_CUED_XOR_HB, dst[1]);
		ppc440spe_desc_set_dest_addr(iter, chan,
					     DMA_CUED_XOR_BASE, dst[0], 0);

		ppc440spe_desc_set_src_mult(iter, chan, DMA_CUED_MULT1_OFF,
					    DMA_CDB_SG_DST1, scf[0]);
		ppc440spe_desc_set_byte_count(iter, ppc440spe_chan, len);
		iter->unmap_len = len;
		sw_desc->async_tx.flags = flags;
	पूर्ण

	spin_unlock_bh(&ppc440spe_chan->lock);

	वापस sw_desc;
पूर्ण

/**
 * ppc440spe_dma01_prep_sum_product -
 * Dx = A*(P+Pxy) + B*(Q+Qxy) operation where destination is also
 * the source.
 */
अटल काष्ठा ppc440spe_adma_desc_slot *ppc440spe_dma01_prep_sum_product(
		काष्ठा ppc440spe_adma_chan *ppc440spe_chan,
		dma_addr_t *dst, dma_addr_t *src, पूर्णांक src_cnt,
		स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_desc_slot *sw_desc = शून्य;
	अचिन्हित दीर्घ op = 0;
	पूर्णांक slot_cnt;

	set_bit(PPC440SPE_DESC_WXOR, &op);
	slot_cnt = 3;

	spin_lock_bh(&ppc440spe_chan->lock);

	/* WXOR, each descriptor occupies one slot */
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt, 1);
	अगर (sw_desc) अणु
		काष्ठा ppc440spe_adma_chan *chan;
		काष्ठा ppc440spe_adma_desc_slot *iter;
		काष्ठा dma_cdb *hw_desc;

		chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);
		set_bits(op, &sw_desc->flags);
		sw_desc->src_cnt = src_cnt;
		sw_desc->dst_cnt = 1;
		/* 1st descriptor, src[1] data to q page and zero destination */
		iter = list_first_entry(&sw_desc->group_list,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
		iter->hw_next = list_entry(iter->chain_node.next,
					   काष्ठा ppc440spe_adma_desc_slot,
					   chain_node);
		clear_bit(PPC440SPE_DESC_INT, &iter->flags);
		hw_desc = iter->hw_desc;
		hw_desc->opc = DMA_CDB_OPC_MULTICAST;

		ppc440spe_desc_set_dest_addr(iter, chan, DMA_CUED_XOR_BASE,
					     *dst, 0);
		ppc440spe_desc_set_dest_addr(iter, chan, 0,
					     ppc440spe_chan->qdest, 1);
		ppc440spe_desc_set_src_addr(iter, chan, 0, DMA_CUED_XOR_HB,
					    src[1]);
		ppc440spe_desc_set_byte_count(iter, ppc440spe_chan, len);
		iter->unmap_len = len;

		/* 2nd descriptor, multiply src[1] data and store the
		 * result in destination */
		iter = list_first_entry(&iter->chain_node,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
		/* set 'next' poपूर्णांकer */
		iter->hw_next = list_entry(iter->chain_node.next,
					   काष्ठा ppc440spe_adma_desc_slot,
					   chain_node);
		अगर (flags & DMA_PREP_INTERRUPT)
			set_bit(PPC440SPE_DESC_INT, &iter->flags);
		अन्यथा
			clear_bit(PPC440SPE_DESC_INT, &iter->flags);

		hw_desc = iter->hw_desc;
		hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
		ppc440spe_desc_set_src_addr(iter, chan, 0, DMA_CUED_XOR_HB,
					    ppc440spe_chan->qdest);
		ppc440spe_desc_set_dest_addr(iter, chan, DMA_CUED_XOR_BASE,
					     *dst, 0);
		ppc440spe_desc_set_src_mult(iter, chan,	DMA_CUED_MULT1_OFF,
					    DMA_CDB_SG_DST1, scf[1]);
		ppc440spe_desc_set_byte_count(iter, ppc440spe_chan, len);
		iter->unmap_len = len;

		/*
		 * 3rd descriptor, multiply src[0] data and xor it
		 * with destination
		 */
		iter = list_first_entry(&iter->chain_node,
					काष्ठा ppc440spe_adma_desc_slot,
					chain_node);
		स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
		iter->hw_next = शून्य;
		अगर (flags & DMA_PREP_INTERRUPT)
			set_bit(PPC440SPE_DESC_INT, &iter->flags);
		अन्यथा
			clear_bit(PPC440SPE_DESC_INT, &iter->flags);

		hw_desc = iter->hw_desc;
		hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
		ppc440spe_desc_set_src_addr(iter, chan, 0, DMA_CUED_XOR_HB,
					    src[0]);
		ppc440spe_desc_set_dest_addr(iter, chan, DMA_CUED_XOR_BASE,
					     *dst, 0);
		ppc440spe_desc_set_src_mult(iter, chan, DMA_CUED_MULT1_OFF,
					    DMA_CDB_SG_DST1, scf[0]);
		ppc440spe_desc_set_byte_count(iter, ppc440spe_chan, len);
		iter->unmap_len = len;
		sw_desc->async_tx.flags = flags;
	पूर्ण

	spin_unlock_bh(&ppc440spe_chan->lock);

	वापस sw_desc;
पूर्ण

अटल काष्ठा ppc440spe_adma_desc_slot *ppc440spe_dma01_prep_pq(
		काष्ठा ppc440spe_adma_chan *ppc440spe_chan,
		dma_addr_t *dst, पूर्णांक dst_cnt, dma_addr_t *src, पूर्णांक src_cnt,
		स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक slot_cnt;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc = शून्य, *iter;
	अचिन्हित दीर्घ op = 0;
	अचिन्हित अक्षर mult = 1;

	pr_debug("%s: dst_cnt %d, src_cnt %d, len %d\n",
		 __func__, dst_cnt, src_cnt, len);
	/*  select operations WXOR/RXOR depending on the
	 * source addresses of चालकs and the number
	 * of destinations (RXOR support only Q-parity calculations)
	 */
	set_bit(PPC440SPE_DESC_WXOR, &op);
	अगर (!test_and_set_bit(PPC440SPE_RXOR_RUN, &ppc440spe_rxor_state)) अणु
		/* no active RXOR;
		 * करो RXOR अगर:
		 * - there are more than 1 source,
		 * - len is aligned on 512-byte boundary,
		 * - source addresses fit to one of 4 possible regions.
		 */
		अगर (src_cnt > 1 &&
		    !(len & MQ0_CF2H_RXOR_BS_MASK) &&
		    (src[0] + len) == src[1]) अणु
			/* may करो RXOR R1 R2 */
			set_bit(PPC440SPE_DESC_RXOR, &op);
			अगर (src_cnt != 2) अणु
				/* may try to enhance region of RXOR */
				अगर ((src[1] + len) == src[2]) अणु
					/* करो RXOR R1 R2 R3 */
					set_bit(PPC440SPE_DESC_RXOR123,
						&op);
				पूर्ण अन्यथा अगर ((src[1] + len * 2) == src[2]) अणु
					/* करो RXOR R1 R2 R4 */
					set_bit(PPC440SPE_DESC_RXOR124, &op);
				पूर्ण अन्यथा अगर ((src[1] + len * 3) == src[2]) अणु
					/* करो RXOR R1 R2 R5 */
					set_bit(PPC440SPE_DESC_RXOR125,
						&op);
				पूर्ण अन्यथा अणु
					/* करो RXOR R1 R2 */
					set_bit(PPC440SPE_DESC_RXOR12,
						&op);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* करो RXOR R1 R2 */
				set_bit(PPC440SPE_DESC_RXOR12, &op);
			पूर्ण
		पूर्ण

		अगर (!test_bit(PPC440SPE_DESC_RXOR, &op)) अणु
			/* can not करो this operation with RXOR */
			clear_bit(PPC440SPE_RXOR_RUN,
				&ppc440spe_rxor_state);
		पूर्ण अन्यथा अणु
			/* can करो; set block size right now */
			ppc440spe_desc_set_rxor_block_size(len);
		पूर्ण
	पूर्ण

	/* Number of necessary slots depends on operation type selected */
	अगर (!test_bit(PPC440SPE_DESC_RXOR, &op)) अणु
		/*  This is a WXOR only chain. Need descriptors क्रम each
		 * source to GF-XOR them with WXOR, and need descriptors
		 * क्रम each destination to zero them with WXOR
		 */
		slot_cnt = src_cnt;

		अगर (flags & DMA_PREP_ZERO_P) अणु
			slot_cnt++;
			set_bit(PPC440SPE_ZERO_P, &op);
		पूर्ण
		अगर (flags & DMA_PREP_ZERO_Q) अणु
			slot_cnt++;
			set_bit(PPC440SPE_ZERO_Q, &op);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*  Need 1/2 descriptor क्रम RXOR operation, and
		 * need (src_cnt - (2 or 3)) क्रम WXOR of sources
		 * reमुख्यed (अगर any)
		 */
		slot_cnt = dst_cnt;

		अगर (flags & DMA_PREP_ZERO_P)
			set_bit(PPC440SPE_ZERO_P, &op);
		अगर (flags & DMA_PREP_ZERO_Q)
			set_bit(PPC440SPE_ZERO_Q, &op);

		अगर (test_bit(PPC440SPE_DESC_RXOR12, &op))
			slot_cnt += src_cnt - 2;
		अन्यथा
			slot_cnt += src_cnt - 3;

		/*  Thus we have either RXOR only chain or
		 * mixed RXOR/WXOR
		 */
		अगर (slot_cnt == dst_cnt)
			/* RXOR only chain */
			clear_bit(PPC440SPE_DESC_WXOR, &op);
	पूर्ण

	spin_lock_bh(&ppc440spe_chan->lock);
	/* क्रम both RXOR/WXOR each descriptor occupies one slot */
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt, 1);
	अगर (sw_desc) अणु
		ppc440spe_desc_init_dma01pq(sw_desc, dst_cnt, src_cnt,
				flags, op);

		/* setup dst/src/mult */
		pr_debug("%s: set dst descriptor 0, 1: 0x%016llx, 0x%016llx\n",
			 __func__, dst[0], dst[1]);
		ppc440spe_adma_pq_set_dest(sw_desc, dst, flags);
		जबतक (src_cnt--) अणु
			ppc440spe_adma_pq_set_src(sw_desc, src[src_cnt],
						  src_cnt);

			/* NOTE: "Multi = 0 is equivalent to = 1" as it
			 * stated in 440SPSPe_RAID6_Addendum_UM_1_17.pdf
			 * करोesn't work क्रम RXOR with DMA0/1! Instead, multi=0
			 * leads to zeroing source data after RXOR.
			 * So, क्रम P हाल set-up mult=1 explicitly.
			 */
			अगर (!(flags & DMA_PREP_PQ_DISABLE_Q))
				mult = scf[src_cnt];
			ppc440spe_adma_pq_set_src_mult(sw_desc,
				mult, src_cnt,  dst_cnt - 1);
		पूर्ण

		/* Setup byte count क्रमeach slot just allocated */
		sw_desc->async_tx.flags = flags;
		list_क्रम_each_entry(iter, &sw_desc->group_list,
				chain_node) अणु
			ppc440spe_desc_set_byte_count(iter,
				ppc440spe_chan, len);
			iter->unmap_len = len;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ppc440spe_chan->lock);

	वापस sw_desc;
पूर्ण

अटल काष्ठा ppc440spe_adma_desc_slot *ppc440spe_dma2_prep_pq(
		काष्ठा ppc440spe_adma_chan *ppc440spe_chan,
		dma_addr_t *dst, पूर्णांक dst_cnt, dma_addr_t *src, पूर्णांक src_cnt,
		स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक slot_cnt, descs_per_op;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc = शून्य, *iter;
	अचिन्हित दीर्घ op = 0;
	अचिन्हित अक्षर mult = 1;

	BUG_ON(!dst_cnt);
	/*pr_debug("%s: dst_cnt %d, src_cnt %d, len %d\n",
		 __func__, dst_cnt, src_cnt, len);*/

	spin_lock_bh(&ppc440spe_chan->lock);
	descs_per_op = ppc440spe_dma2_pq_slot_count(src, src_cnt, len);
	अगर (descs_per_op < 0) अणु
		spin_unlock_bh(&ppc440spe_chan->lock);
		वापस शून्य;
	पूर्ण

	/* depending on number of sources we have 1 or 2 RXOR chains */
	slot_cnt = descs_per_op * dst_cnt;

	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt, 1);
	अगर (sw_desc) अणु
		op = slot_cnt;
		sw_desc->async_tx.flags = flags;
		list_क्रम_each_entry(iter, &sw_desc->group_list, chain_node) अणु
			ppc440spe_desc_init_dma2pq(iter, dst_cnt, src_cnt,
				--op ? 0 : flags);
			ppc440spe_desc_set_byte_count(iter, ppc440spe_chan,
				len);
			iter->unmap_len = len;

			ppc440spe_init_rxor_cursor(&(iter->rxor_cursor));
			iter->rxor_cursor.len = len;
			iter->descs_per_op = descs_per_op;
		पूर्ण
		op = 0;
		list_क्रम_each_entry(iter, &sw_desc->group_list, chain_node) अणु
			op++;
			अगर (op % descs_per_op == 0)
				ppc440spe_adma_init_dma2rxor_slot(iter, src,
								  src_cnt);
			अगर (likely(!list_is_last(&iter->chain_node,
						 &sw_desc->group_list))) अणु
				/* set 'next' poपूर्णांकer */
				iter->hw_next =
					list_entry(iter->chain_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
				ppc440spe_xor_set_link(iter, iter->hw_next);
			पूर्ण अन्यथा अणु
				/* this is the last descriptor. */
				iter->hw_next = शून्य;
			पूर्ण
		पूर्ण

		/* fixup head descriptor */
		sw_desc->dst_cnt = dst_cnt;
		अगर (flags & DMA_PREP_ZERO_P)
			set_bit(PPC440SPE_ZERO_P, &sw_desc->flags);
		अगर (flags & DMA_PREP_ZERO_Q)
			set_bit(PPC440SPE_ZERO_Q, &sw_desc->flags);

		/* setup dst/src/mult */
		ppc440spe_adma_pq_set_dest(sw_desc, dst, flags);

		जबतक (src_cnt--) अणु
			/* handle descriptors (अगर dst_cnt == 2) inside
			 * the ppc440spe_adma_pq_set_srcxxx() functions
			 */
			ppc440spe_adma_pq_set_src(sw_desc, src[src_cnt],
						  src_cnt);
			अगर (!(flags & DMA_PREP_PQ_DISABLE_Q))
				mult = scf[src_cnt];
			ppc440spe_adma_pq_set_src_mult(sw_desc,
					mult, src_cnt, dst_cnt - 1);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ppc440spe_chan->lock);
	ppc440spe_desc_set_rxor_block_size(len);
	वापस sw_desc;
पूर्ण

/**
 * ppc440spe_adma_prep_dma_pq - prepare CDB (group) क्रम a GF-XOR operation
 */
अटल काष्ठा dma_async_tx_descriptor *ppc440spe_adma_prep_dma_pq(
		काष्ठा dma_chan *chan, dma_addr_t *dst, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc = शून्य;
	पूर्णांक dst_cnt = 0;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);

	ADMA_LL_DBG(prep_dma_pq_dbg(ppc440spe_chan->device->id,
				    dst, src, src_cnt));
	BUG_ON(!len);
	BUG_ON(len > PPC440SPE_ADMA_XOR_MAX_BYTE_COUNT);
	BUG_ON(!src_cnt);

	अगर (src_cnt == 1 && dst[1] == src[0]) अणु
		dma_addr_t dest[2];

		/* dst[1] is real destination (Q) */
		dest[0] = dst[1];
		/* this is the page to multicast source data to */
		dest[1] = ppc440spe_chan->qdest;
		sw_desc = ppc440spe_dma01_prep_mult(ppc440spe_chan,
				dest, 2, src, src_cnt, scf, len, flags);
		वापस sw_desc ? &sw_desc->async_tx : शून्य;
	पूर्ण

	अगर (src_cnt == 2 && dst[1] == src[1]) अणु
		sw_desc = ppc440spe_dma01_prep_sum_product(ppc440spe_chan,
					&dst[1], src, 2, scf, len, flags);
		वापस sw_desc ? &sw_desc->async_tx : शून्य;
	पूर्ण

	अगर (!(flags & DMA_PREP_PQ_DISABLE_P)) अणु
		BUG_ON(!dst[0]);
		dst_cnt++;
		flags |= DMA_PREP_ZERO_P;
	पूर्ण

	अगर (!(flags & DMA_PREP_PQ_DISABLE_Q)) अणु
		BUG_ON(!dst[1]);
		dst_cnt++;
		flags |= DMA_PREP_ZERO_Q;
	पूर्ण

	BUG_ON(!dst_cnt);

	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d: %s src_cnt: %d len: %u int_en: %d\n",
		ppc440spe_chan->device->id, __func__, src_cnt, len,
		flags & DMA_PREP_INTERRUPT ? 1 : 0);

	चयन (ppc440spe_chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		sw_desc = ppc440spe_dma01_prep_pq(ppc440spe_chan,
				dst, dst_cnt, src, src_cnt, scf,
				len, flags);
		अवरोध;

	हाल PPC440SPE_XOR_ID:
		sw_desc = ppc440spe_dma2_prep_pq(ppc440spe_chan,
				dst, dst_cnt, src, src_cnt, scf,
				len, flags);
		अवरोध;
	पूर्ण

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

/**
 * ppc440spe_adma_prep_dma_pqzero_sum - prepare CDB group क्रम
 * a PQ_ZERO_SUM operation
 */
अटल काष्ठा dma_async_tx_descriptor *ppc440spe_adma_prep_dma_pqzero_sum(
		काष्ठा dma_chan *chan, dma_addr_t *pq, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		क्रमागत sum_check_flags *pqres, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *sw_desc, *iter;
	dma_addr_t pdest, qdest;
	पूर्णांक slot_cnt, slots_per_op, idst, dst_cnt;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);

	अगर (flags & DMA_PREP_PQ_DISABLE_P)
		pdest = 0;
	अन्यथा
		pdest = pq[0];

	अगर (flags & DMA_PREP_PQ_DISABLE_Q)
		qdest = 0;
	अन्यथा
		qdest = pq[1];

	ADMA_LL_DBG(prep_dma_pqzero_sum_dbg(ppc440spe_chan->device->id,
					    src, src_cnt, scf));

	/* Always use WXOR क्रम P/Q calculations (two destinations).
	 * Need 1 or 2 extra slots to verअगरy results are zero.
	 */
	idst = dst_cnt = (pdest && qdest) ? 2 : 1;

	/* One additional slot per destination to clone P/Q
	 * beक्रमe calculation (we have to preserve destinations).
	 */
	slot_cnt = src_cnt + dst_cnt * 2;
	slots_per_op = 1;

	spin_lock_bh(&ppc440spe_chan->lock);
	sw_desc = ppc440spe_adma_alloc_slots(ppc440spe_chan, slot_cnt,
					     slots_per_op);
	अगर (sw_desc) अणु
		ppc440spe_desc_init_dma01pqzero_sum(sw_desc, dst_cnt, src_cnt);

		/* Setup byte count क्रम each slot just allocated */
		sw_desc->async_tx.flags = flags;
		list_क्रम_each_entry(iter, &sw_desc->group_list, chain_node) अणु
			ppc440spe_desc_set_byte_count(iter, ppc440spe_chan,
						      len);
			iter->unmap_len = len;
		पूर्ण

		अगर (pdest) अणु
			काष्ठा dma_cdb *hw_desc;
			काष्ठा ppc440spe_adma_chan *chan;

			iter = sw_desc->group_head;
			chan = to_ppc440spe_adma_chan(iter->async_tx.chan);
			स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
			iter->hw_next = list_entry(iter->chain_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			hw_desc = iter->hw_desc;
			hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
			iter->src_cnt = 0;
			iter->dst_cnt = 0;
			ppc440spe_desc_set_dest_addr(iter, chan, 0,
						     ppc440spe_chan->pdest, 0);
			ppc440spe_desc_set_src_addr(iter, chan, 0, 0, pdest);
			ppc440spe_desc_set_byte_count(iter, ppc440spe_chan,
						      len);
			iter->unmap_len = 0;
			/* override pdest to preserve original P */
			pdest = ppc440spe_chan->pdest;
		पूर्ण
		अगर (qdest) अणु
			काष्ठा dma_cdb *hw_desc;
			काष्ठा ppc440spe_adma_chan *chan;

			iter = list_first_entry(&sw_desc->group_list,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			chan = to_ppc440spe_adma_chan(iter->async_tx.chan);

			अगर (pdest) अणु
				iter = list_entry(iter->chain_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			पूर्ण

			स_रखो(iter->hw_desc, 0, माप(काष्ठा dma_cdb));
			iter->hw_next = list_entry(iter->chain_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			hw_desc = iter->hw_desc;
			hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
			iter->src_cnt = 0;
			iter->dst_cnt = 0;
			ppc440spe_desc_set_dest_addr(iter, chan, 0,
						     ppc440spe_chan->qdest, 0);
			ppc440spe_desc_set_src_addr(iter, chan, 0, 0, qdest);
			ppc440spe_desc_set_byte_count(iter, ppc440spe_chan,
						      len);
			iter->unmap_len = 0;
			/* override qdest to preserve original Q */
			qdest = ppc440spe_chan->qdest;
		पूर्ण

		/* Setup destinations क्रम P/Q ops */
		ppc440spe_adma_pqzero_sum_set_dest(sw_desc, pdest, qdest);

		/* Setup zero QWORDs पूर्णांकo DCHECK CDBs */
		idst = dst_cnt;
		list_क्रम_each_entry_reverse(iter, &sw_desc->group_list,
					    chain_node) अणु
			/*
			 * The last CDB corresponds to Q-parity check,
			 * the one beक्रमe last CDB corresponds
			 * P-parity check
			 */
			अगर (idst == DMA_DEST_MAX_NUM) अणु
				अगर (idst == dst_cnt) अणु
					set_bit(PPC440SPE_DESC_QCHECK,
						&iter->flags);
				पूर्ण अन्यथा अणु
					set_bit(PPC440SPE_DESC_PCHECK,
						&iter->flags);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (qdest) अणु
					set_bit(PPC440SPE_DESC_QCHECK,
						&iter->flags);
				पूर्ण अन्यथा अणु
					set_bit(PPC440SPE_DESC_PCHECK,
						&iter->flags);
				पूर्ण
			पूर्ण
			iter->xor_check_result = pqres;

			/*
			 * set it to zero, अगर check fail then result will
			 * be updated
			 */
			*iter->xor_check_result = 0;
			ppc440spe_desc_set_dcheck(iter, ppc440spe_chan,
				ppc440spe_qword);

			अगर (!(--dst_cnt))
				अवरोध;
		पूर्ण

		/* Setup sources and mults क्रम P/Q ops */
		list_क्रम_each_entry_जारी_reverse(iter, &sw_desc->group_list,
						     chain_node) अणु
			काष्ठा ppc440spe_adma_chan *chan;
			u32 mult_dst;

			chan = to_ppc440spe_adma_chan(iter->async_tx.chan);
			ppc440spe_desc_set_src_addr(iter, chan, 0,
						    DMA_CUED_XOR_HB,
						    src[src_cnt - 1]);
			अगर (qdest) अणु
				mult_dst = (dst_cnt - 1) ? DMA_CDB_SG_DST2 :
							   DMA_CDB_SG_DST1;
				ppc440spe_desc_set_src_mult(iter, chan,
							    DMA_CUED_MULT1_OFF,
							    mult_dst,
							    scf[src_cnt - 1]);
			पूर्ण
			अगर (!(--src_cnt))
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ppc440spe_chan->lock);
	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

/**
 * ppc440spe_adma_prep_dma_xor_zero_sum - prepare CDB group क्रम
 * XOR ZERO_SUM operation
 */
अटल काष्ठा dma_async_tx_descriptor *ppc440spe_adma_prep_dma_xor_zero_sum(
		काष्ठा dma_chan *chan, dma_addr_t *src, अचिन्हित पूर्णांक src_cnt,
		माप_प्रकार len, क्रमागत sum_check_flags *result, अचिन्हित दीर्घ flags)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	dma_addr_t pq[2];

	/* validate P, disable Q */
	pq[0] = src[0];
	pq[1] = 0;
	flags |= DMA_PREP_PQ_DISABLE_Q;

	tx = ppc440spe_adma_prep_dma_pqzero_sum(chan, pq, &src[1],
						src_cnt - 1, 0, len,
						result, flags);
	वापस tx;
पूर्ण

/**
 * ppc440spe_adma_set_dest - set destination address पूर्णांकo descriptor
 */
अटल व्योम ppc440spe_adma_set_dest(काष्ठा ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t addr, पूर्णांक index)
अणु
	काष्ठा ppc440spe_adma_chan *chan;

	BUG_ON(index >= sw_desc->dst_cnt);

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		/* to करो: support transfers lengths >
		 * PPC440SPE_ADMA_DMA/XOR_MAX_BYTE_COUNT
		 */
		ppc440spe_desc_set_dest_addr(sw_desc->group_head,
			chan, 0, addr, index);
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		sw_desc = ppc440spe_get_group_entry(sw_desc, index);
		ppc440spe_desc_set_dest_addr(sw_desc,
			chan, 0, addr, index);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ppc440spe_adma_pq_zero_op(काष्ठा ppc440spe_adma_desc_slot *iter,
		काष्ठा ppc440spe_adma_chan *chan, dma_addr_t addr)
अणु
	/*  To clear destinations update the descriptor
	 * (P or Q depending on index) as follows:
	 * addr is destination (0 corresponds to SG2):
	 */
	ppc440spe_desc_set_dest_addr(iter, chan, DMA_CUED_XOR_BASE, addr, 0);

	/* ... and the addr is source: */
	ppc440spe_desc_set_src_addr(iter, chan, 0, DMA_CUED_XOR_HB, addr);

	/* addr is always SG2 then the mult is always DST1 */
	ppc440spe_desc_set_src_mult(iter, chan, DMA_CUED_MULT1_OFF,
				    DMA_CDB_SG_DST1, 1);
पूर्ण

/**
 * ppc440spe_adma_pq_set_dest - set destination address पूर्णांकo descriptor
 * क्रम the PQXOR operation
 */
अटल व्योम ppc440spe_adma_pq_set_dest(काष्ठा ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t *addrs, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ppc440spe_adma_desc_slot *iter;
	काष्ठा ppc440spe_adma_chan *chan;
	dma_addr_t paddr, qaddr;
	dma_addr_t addr = 0, ppath, qpath;
	पूर्णांक index = 0, i;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	अगर (flags & DMA_PREP_PQ_DISABLE_P)
		paddr = 0;
	अन्यथा
		paddr = addrs[0];

	अगर (flags & DMA_PREP_PQ_DISABLE_Q)
		qaddr = 0;
	अन्यथा
		qaddr = addrs[1];

	अगर (!paddr || !qaddr)
		addr = paddr ? paddr : qaddr;

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		/* walk through the WXOR source list and set P/Q-destinations
		 * क्रम each slot:
		 */
		अगर (!test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags)) अणु
			/* This is WXOR-only chain; may have 1/2 zero descs */
			अगर (test_bit(PPC440SPE_ZERO_P, &sw_desc->flags))
				index++;
			अगर (test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags))
				index++;

			iter = ppc440spe_get_group_entry(sw_desc, index);
			अगर (addr) अणु
				/* one destination */
				list_क्रम_each_entry_from(iter,
					&sw_desc->group_list, chain_node)
					ppc440spe_desc_set_dest_addr(iter, chan,
						DMA_CUED_XOR_BASE, addr, 0);
			पूर्ण अन्यथा अणु
				/* two destinations */
				list_क्रम_each_entry_from(iter,
					&sw_desc->group_list, chain_node) अणु
					ppc440spe_desc_set_dest_addr(iter, chan,
						DMA_CUED_XOR_BASE, paddr, 0);
					ppc440spe_desc_set_dest_addr(iter, chan,
						DMA_CUED_XOR_BASE, qaddr, 1);
				पूर्ण
			पूर्ण

			अगर (index) अणु
				/*  To clear destinations update the descriptor
				 * (1st,2nd, or both depending on flags)
				 */
				index = 0;
				अगर (test_bit(PPC440SPE_ZERO_P,
						&sw_desc->flags)) अणु
					iter = ppc440spe_get_group_entry(
							sw_desc, index++);
					ppc440spe_adma_pq_zero_op(iter, chan,
							paddr);
				पूर्ण

				अगर (test_bit(PPC440SPE_ZERO_Q,
						&sw_desc->flags)) अणु
					iter = ppc440spe_get_group_entry(
							sw_desc, index++);
					ppc440spe_adma_pq_zero_op(iter, chan,
							qaddr);
				पूर्ण

				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* This is RXOR-only or RXOR/WXOR mixed chain */

			/* If we want to include destination पूर्णांकo calculations,
			 * then make dest addresses cued with mult=1 (XOR).
			 */
			ppath = test_bit(PPC440SPE_ZERO_P, &sw_desc->flags) ?
					DMA_CUED_XOR_HB :
					DMA_CUED_XOR_BASE |
						(1 << DMA_CUED_MULT1_OFF);
			qpath = test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags) ?
					DMA_CUED_XOR_HB :
					DMA_CUED_XOR_BASE |
						(1 << DMA_CUED_MULT1_OFF);

			/* Setup destination(s) in RXOR slot(s) */
			iter = ppc440spe_get_group_entry(sw_desc, index++);
			ppc440spe_desc_set_dest_addr(iter, chan,
						paddr ? ppath : qpath,
						paddr ? paddr : qaddr, 0);
			अगर (!addr) अणु
				/* two destinations */
				iter = ppc440spe_get_group_entry(sw_desc,
								 index++);
				ppc440spe_desc_set_dest_addr(iter, chan,
						qpath, qaddr, 0);
			पूर्ण

			अगर (test_bit(PPC440SPE_DESC_WXOR, &sw_desc->flags)) अणु
				/* Setup destination(s) in reमुख्यing WXOR
				 * slots
				 */
				iter = ppc440spe_get_group_entry(sw_desc,
								 index);
				अगर (addr) अणु
					/* one destination */
					list_क्रम_each_entry_from(iter,
					    &sw_desc->group_list,
					    chain_node)
						ppc440spe_desc_set_dest_addr(
							iter, chan,
							DMA_CUED_XOR_BASE,
							addr, 0);

				पूर्ण अन्यथा अणु
					/* two destinations */
					list_क्रम_each_entry_from(iter,
					    &sw_desc->group_list,
					    chain_node) अणु
						ppc440spe_desc_set_dest_addr(
							iter, chan,
							DMA_CUED_XOR_BASE,
							paddr, 0);
						ppc440spe_desc_set_dest_addr(
							iter, chan,
							DMA_CUED_XOR_BASE,
							qaddr, 1);
					पूर्ण
				पूर्ण
			पूर्ण

		पूर्ण
		अवरोध;

	हाल PPC440SPE_XOR_ID:
		/* DMA2 descriptors have only 1 destination, so there are
		 * two chains - one क्रम each dest.
		 * If we want to include destination पूर्णांकo calculations,
		 * then make dest addresses cued with mult=1 (XOR).
		 */
		ppath = test_bit(PPC440SPE_ZERO_P, &sw_desc->flags) ?
				DMA_CUED_XOR_HB :
				DMA_CUED_XOR_BASE |
					(1 << DMA_CUED_MULT1_OFF);

		qpath = test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags) ?
				DMA_CUED_XOR_HB :
				DMA_CUED_XOR_BASE |
					(1 << DMA_CUED_MULT1_OFF);

		iter = ppc440spe_get_group_entry(sw_desc, 0);
		क्रम (i = 0; i < sw_desc->descs_per_op; i++) अणु
			ppc440spe_desc_set_dest_addr(iter, chan,
				paddr ? ppath : qpath,
				paddr ? paddr : qaddr, 0);
			iter = list_entry(iter->chain_node.next,
					  काष्ठा ppc440spe_adma_desc_slot,
					  chain_node);
		पूर्ण

		अगर (!addr) अणु
			/* Two destinations; setup Q here */
			iter = ppc440spe_get_group_entry(sw_desc,
				sw_desc->descs_per_op);
			क्रम (i = 0; i < sw_desc->descs_per_op; i++) अणु
				ppc440spe_desc_set_dest_addr(iter,
					chan, qpath, qaddr, 0);
				iter = list_entry(iter->chain_node.next,
						काष्ठा ppc440spe_adma_desc_slot,
						chain_node);
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_pq_zero_sum_set_dest - set destination address पूर्णांकo descriptor
 * क्रम the PQ_ZERO_SUM operation
 */
अटल व्योम ppc440spe_adma_pqzero_sum_set_dest(
		काष्ठा ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t paddr, dma_addr_t qaddr)
अणु
	काष्ठा ppc440spe_adma_desc_slot *iter, *end;
	काष्ठा ppc440spe_adma_chan *chan;
	dma_addr_t addr = 0;
	पूर्णांक idx;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	/* walk through the WXOR source list and set P/Q-destinations
	 * क्रम each slot
	 */
	idx = (paddr && qaddr) ? 2 : 1;
	/* set end */
	list_क्रम_each_entry_reverse(end, &sw_desc->group_list,
				    chain_node) अणु
		अगर (!(--idx))
			अवरोध;
	पूर्ण
	/* set start */
	idx = (paddr && qaddr) ? 2 : 1;
	iter = ppc440spe_get_group_entry(sw_desc, idx);

	अगर (paddr && qaddr) अणु
		/* two destinations */
		list_क्रम_each_entry_from(iter, &sw_desc->group_list,
					 chain_node) अणु
			अगर (unlikely(iter == end))
				अवरोध;
			ppc440spe_desc_set_dest_addr(iter, chan,
						DMA_CUED_XOR_BASE, paddr, 0);
			ppc440spe_desc_set_dest_addr(iter, chan,
						DMA_CUED_XOR_BASE, qaddr, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* one destination */
		addr = paddr ? paddr : qaddr;
		list_क्रम_each_entry_from(iter, &sw_desc->group_list,
					 chain_node) अणु
			अगर (unlikely(iter == end))
				अवरोध;
			ppc440spe_desc_set_dest_addr(iter, chan,
						DMA_CUED_XOR_BASE, addr, 0);
		पूर्ण
	पूर्ण

	/*  The reमुख्यing descriptors are DATACHECK. These have no need in
	 * destination. Actually, these destinations are used there
	 * as sources क्रम check operation. So, set addr as source.
	 */
	ppc440spe_desc_set_src_addr(end, chan, 0, 0, addr ? addr : paddr);

	अगर (!addr) अणु
		end = list_entry(end->chain_node.next,
				 काष्ठा ppc440spe_adma_desc_slot, chain_node);
		ppc440spe_desc_set_src_addr(end, chan, 0, 0, qaddr);
	पूर्ण
पूर्ण

/**
 * ppc440spe_desc_set_xor_src_cnt - set source count पूर्णांकo descriptor
 */
अटल अंतरभूत व्योम ppc440spe_desc_set_xor_src_cnt(
			काष्ठा ppc440spe_adma_desc_slot *desc,
			पूर्णांक src_cnt)
अणु
	काष्ठा xor_cb *hw_desc = desc->hw_desc;

	hw_desc->cbc &= ~XOR_CDCR_OAC_MSK;
	hw_desc->cbc |= src_cnt;
पूर्ण

/**
 * ppc440spe_adma_pq_set_src - set source address पूर्णांकo descriptor
 */
अटल व्योम ppc440spe_adma_pq_set_src(काष्ठा ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t addr, पूर्णांक index)
अणु
	काष्ठा ppc440spe_adma_chan *chan;
	dma_addr_t haddr = 0;
	काष्ठा ppc440spe_adma_desc_slot *iter = शून्य;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		/* DMA0,1 may करो: WXOR, RXOR, RXOR+WXORs chain
		 */
		अगर (test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags)) अणु
			/* RXOR-only or RXOR/WXOR operation */
			पूर्णांक iskip = test_bit(PPC440SPE_DESC_RXOR12,
				&sw_desc->flags) ?  2 : 3;

			अगर (index == 0) अणु
				/* 1st slot (RXOR) */
				/* setup sources region (R1-2-3, R1-2-4,
				 * or R1-2-5)
				 */
				अगर (test_bit(PPC440SPE_DESC_RXOR12,
						&sw_desc->flags))
					haddr = DMA_RXOR12 <<
						DMA_CUED_REGION_OFF;
				अन्यथा अगर (test_bit(PPC440SPE_DESC_RXOR123,
				    &sw_desc->flags))
					haddr = DMA_RXOR123 <<
						DMA_CUED_REGION_OFF;
				अन्यथा अगर (test_bit(PPC440SPE_DESC_RXOR124,
				    &sw_desc->flags))
					haddr = DMA_RXOR124 <<
						DMA_CUED_REGION_OFF;
				अन्यथा अगर (test_bit(PPC440SPE_DESC_RXOR125,
				    &sw_desc->flags))
					haddr = DMA_RXOR125 <<
						DMA_CUED_REGION_OFF;
				अन्यथा
					BUG();
				haddr |= DMA_CUED_XOR_BASE;
				iter = ppc440spe_get_group_entry(sw_desc, 0);
			पूर्ण अन्यथा अगर (index < iskip) अणु
				/* 1st slot (RXOR)
				 * shall actually set source address only once
				 * instead of first <iskip>
				 */
				iter = शून्य;
			पूर्ण अन्यथा अणु
				/* 2nd/3d and next slots (WXOR);
				 * skip first slot with RXOR
				 */
				haddr = DMA_CUED_XOR_HB;
				iter = ppc440spe_get_group_entry(sw_desc,
				    index - iskip + sw_desc->dst_cnt);
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक znum = 0;

			/* WXOR-only operation; skip first slots with
			 * zeroing destinations
			 */
			अगर (test_bit(PPC440SPE_ZERO_P, &sw_desc->flags))
				znum++;
			अगर (test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags))
				znum++;

			haddr = DMA_CUED_XOR_HB;
			iter = ppc440spe_get_group_entry(sw_desc,
					index + znum);
		पूर्ण

		अगर (likely(iter)) अणु
			ppc440spe_desc_set_src_addr(iter, chan, 0, haddr, addr);

			अगर (!index &&
			    test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags) &&
			    sw_desc->dst_cnt == 2) अणु
				/* अगर we have two destinations क्रम RXOR, then
				 * setup source in the second descr too
				 */
				iter = ppc440spe_get_group_entry(sw_desc, 1);
				ppc440spe_desc_set_src_addr(iter, chan, 0,
					haddr, addr);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल PPC440SPE_XOR_ID:
		/* DMA2 may करो Biskup */
		iter = sw_desc->group_head;
		अगर (iter->dst_cnt == 2) अणु
			/* both P & Q calculations required; set P src here */
			ppc440spe_adma_dma2rxor_set_src(iter, index, addr);

			/* this is क्रम Q */
			iter = ppc440spe_get_group_entry(sw_desc,
				sw_desc->descs_per_op);
		पूर्ण
		ppc440spe_adma_dma2rxor_set_src(iter, index, addr);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_स_नकल_xor_set_src - set source address पूर्णांकo descriptor
 */
अटल व्योम ppc440spe_adma_स_नकल_xor_set_src(
		काष्ठा ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t addr, पूर्णांक index)
अणु
	काष्ठा ppc440spe_adma_chan *chan;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);
	sw_desc = sw_desc->group_head;

	अगर (likely(sw_desc))
		ppc440spe_desc_set_src_addr(sw_desc, chan, index, 0, addr);
पूर्ण

/**
 * ppc440spe_adma_dma2rxor_inc_addr  -
 */
अटल व्योम ppc440spe_adma_dma2rxor_inc_addr(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		काष्ठा ppc440spe_rxor *cursor, पूर्णांक index, पूर्णांक src_cnt)
अणु
	cursor->addr_count++;
	अगर (index == src_cnt - 1) अणु
		ppc440spe_desc_set_xor_src_cnt(desc, cursor->addr_count);
	पूर्ण अन्यथा अगर (cursor->addr_count == XOR_MAX_OPS) अणु
		ppc440spe_desc_set_xor_src_cnt(desc, cursor->addr_count);
		cursor->addr_count = 0;
		cursor->desc_count++;
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_dma2rxor_prep_src - setup RXOR types in DMA2 CDB
 */
अटल पूर्णांक ppc440spe_adma_dma2rxor_prep_src(
		काष्ठा ppc440spe_adma_desc_slot *hdesc,
		काष्ठा ppc440spe_rxor *cursor, पूर्णांक index,
		पूर्णांक src_cnt, u32 addr)
अणु
	पूर्णांक rval = 0;
	u32 sign;
	काष्ठा ppc440spe_adma_desc_slot *desc = hdesc;
	पूर्णांक i;

	क्रम (i = 0; i < cursor->desc_count; i++) अणु
		desc = list_entry(hdesc->chain_node.next,
				  काष्ठा ppc440spe_adma_desc_slot,
				  chain_node);
	पूर्ण

	चयन (cursor->state) अणु
	हाल 0:
		अगर (addr == cursor->addrl + cursor->len) अणु
			/* direct RXOR */
			cursor->state = 1;
			cursor->xor_count++;
			अगर (index == src_cnt-1) अणु
				ppc440spe_rxor_set_region(desc,
					cursor->addr_count,
					DMA_RXOR12 << DMA_CUED_REGION_OFF);
				ppc440spe_adma_dma2rxor_inc_addr(
					desc, cursor, index, src_cnt);
			पूर्ण
		पूर्ण अन्यथा अगर (cursor->addrl == addr + cursor->len) अणु
			/* reverse RXOR */
			cursor->state = 1;
			cursor->xor_count++;
			set_bit(cursor->addr_count, &desc->reverse_flags[0]);
			अगर (index == src_cnt-1) अणु
				ppc440spe_rxor_set_region(desc,
					cursor->addr_count,
					DMA_RXOR12 << DMA_CUED_REGION_OFF);
				ppc440spe_adma_dma2rxor_inc_addr(
					desc, cursor, index, src_cnt);
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "Cannot build "
				"DMA2 RXOR command block.\n");
			BUG();
		पूर्ण
		अवरोध;
	हाल 1:
		sign = test_bit(cursor->addr_count,
				desc->reverse_flags)
			? -1 : 1;
		अगर (index == src_cnt-2 || (sign == -1
			&& addr != cursor->addrl - 2*cursor->len)) अणु
			cursor->state = 0;
			cursor->xor_count = 1;
			cursor->addrl = addr;
			ppc440spe_rxor_set_region(desc,
				cursor->addr_count,
				DMA_RXOR12 << DMA_CUED_REGION_OFF);
			ppc440spe_adma_dma2rxor_inc_addr(
				desc, cursor, index, src_cnt);
		पूर्ण अन्यथा अगर (addr == cursor->addrl + 2*sign*cursor->len) अणु
			cursor->state = 2;
			cursor->xor_count = 0;
			ppc440spe_rxor_set_region(desc,
				cursor->addr_count,
				DMA_RXOR123 << DMA_CUED_REGION_OFF);
			अगर (index == src_cnt-1) अणु
				ppc440spe_adma_dma2rxor_inc_addr(
					desc, cursor, index, src_cnt);
			पूर्ण
		पूर्ण अन्यथा अगर (addr == cursor->addrl + 3*cursor->len) अणु
			cursor->state = 2;
			cursor->xor_count = 0;
			ppc440spe_rxor_set_region(desc,
				cursor->addr_count,
				DMA_RXOR124 << DMA_CUED_REGION_OFF);
			अगर (index == src_cnt-1) अणु
				ppc440spe_adma_dma2rxor_inc_addr(
					desc, cursor, index, src_cnt);
			पूर्ण
		पूर्ण अन्यथा अगर (addr == cursor->addrl + 4*cursor->len) अणु
			cursor->state = 2;
			cursor->xor_count = 0;
			ppc440spe_rxor_set_region(desc,
				cursor->addr_count,
				DMA_RXOR125 << DMA_CUED_REGION_OFF);
			अगर (index == src_cnt-1) अणु
				ppc440spe_adma_dma2rxor_inc_addr(
					desc, cursor, index, src_cnt);
			पूर्ण
		पूर्ण अन्यथा अणु
			cursor->state = 0;
			cursor->xor_count = 1;
			cursor->addrl = addr;
			ppc440spe_rxor_set_region(desc,
				cursor->addr_count,
				DMA_RXOR12 << DMA_CUED_REGION_OFF);
			ppc440spe_adma_dma2rxor_inc_addr(
				desc, cursor, index, src_cnt);
		पूर्ण
		अवरोध;
	हाल 2:
		cursor->state = 0;
		cursor->addrl = addr;
		cursor->xor_count++;
		अगर (index) अणु
			ppc440spe_adma_dma2rxor_inc_addr(
				desc, cursor, index, src_cnt);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण

/**
 * ppc440spe_adma_dma2rxor_set_src - set RXOR source address; it's assumed that
 *	ppc440spe_adma_dma2rxor_prep_src() has alपढ़ोy करोne prior this call
 */
अटल व्योम ppc440spe_adma_dma2rxor_set_src(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		पूर्णांक index, dma_addr_t addr)
अणु
	काष्ठा xor_cb *xcb = desc->hw_desc;
	पूर्णांक k = 0, op = 0, lop = 0;

	/* get the RXOR opeअक्रम which corresponds to index addr */
	जबतक (op <= index) अणु
		lop = op;
		अगर (k == XOR_MAX_OPS) अणु
			k = 0;
			desc = list_entry(desc->chain_node.next,
				काष्ठा ppc440spe_adma_desc_slot, chain_node);
			xcb = desc->hw_desc;

		पूर्ण
		अगर ((xcb->ops[k++].h & (DMA_RXOR12 << DMA_CUED_REGION_OFF)) ==
		    (DMA_RXOR12 << DMA_CUED_REGION_OFF))
			op += 2;
		अन्यथा
			op += 3;
	पूर्ण

	BUG_ON(k < 1);

	अगर (test_bit(k-1, desc->reverse_flags)) अणु
		/* reverse opeअक्रम order; put last op in RXOR group */
		अगर (index == op - 1)
			ppc440spe_rxor_set_src(desc, k - 1, addr);
	पूर्ण अन्यथा अणु
		/* direct opeअक्रम order; put first op in RXOR group */
		अगर (index == lop)
			ppc440spe_rxor_set_src(desc, k - 1, addr);
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_dma2rxor_set_mult - set RXOR multipliers; it's assumed that
 *	ppc440spe_adma_dma2rxor_prep_src() has alपढ़ोy करोne prior this call
 */
अटल व्योम ppc440spe_adma_dma2rxor_set_mult(
		काष्ठा ppc440spe_adma_desc_slot *desc,
		पूर्णांक index, u8 mult)
अणु
	काष्ठा xor_cb *xcb = desc->hw_desc;
	पूर्णांक k = 0, op = 0, lop = 0;

	/* get the RXOR opeअक्रम which corresponds to index mult */
	जबतक (op <= index) अणु
		lop = op;
		अगर (k == XOR_MAX_OPS) अणु
			k = 0;
			desc = list_entry(desc->chain_node.next,
					  काष्ठा ppc440spe_adma_desc_slot,
					  chain_node);
			xcb = desc->hw_desc;

		पूर्ण
		अगर ((xcb->ops[k++].h & (DMA_RXOR12 << DMA_CUED_REGION_OFF)) ==
		    (DMA_RXOR12 << DMA_CUED_REGION_OFF))
			op += 2;
		अन्यथा
			op += 3;
	पूर्ण

	BUG_ON(k < 1);
	अगर (test_bit(k-1, desc->reverse_flags)) अणु
		/* reverse order */
		ppc440spe_rxor_set_mult(desc, k - 1, op - index - 1, mult);
	पूर्ण अन्यथा अणु
		/* direct order */
		ppc440spe_rxor_set_mult(desc, k - 1, index - lop, mult);
	पूर्ण
पूर्ण

/**
 * ppc440spe_init_rxor_cursor -
 */
अटल व्योम ppc440spe_init_rxor_cursor(काष्ठा ppc440spe_rxor *cursor)
अणु
	स_रखो(cursor, 0, माप(काष्ठा ppc440spe_rxor));
	cursor->state = 2;
पूर्ण

/**
 * ppc440spe_adma_pq_set_src_mult - set multiplication coefficient पूर्णांकo
 * descriptor क्रम the PQXOR operation
 */
अटल व्योम ppc440spe_adma_pq_set_src_mult(
		काष्ठा ppc440spe_adma_desc_slot *sw_desc,
		अचिन्हित अक्षर mult, पूर्णांक index, पूर्णांक dst_pos)
अणु
	काष्ठा ppc440spe_adma_chan *chan;
	u32 mult_idx, mult_dst;
	काष्ठा ppc440spe_adma_desc_slot *iter = शून्य, *iter1 = शून्य;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	चयन (chan->device->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		अगर (test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags)) अणु
			पूर्णांक region = test_bit(PPC440SPE_DESC_RXOR12,
					&sw_desc->flags) ? 2 : 3;

			अगर (index < region) अणु
				/* RXOR multipliers */
				iter = ppc440spe_get_group_entry(sw_desc,
					sw_desc->dst_cnt - 1);
				अगर (sw_desc->dst_cnt == 2)
					iter1 = ppc440spe_get_group_entry(
							sw_desc, 0);

				mult_idx = DMA_CUED_MULT1_OFF + (index << 3);
				mult_dst = DMA_CDB_SG_SRC;
			पूर्ण अन्यथा अणु
				/* WXOR multiplier */
				iter = ppc440spe_get_group_entry(sw_desc,
							index - region +
							sw_desc->dst_cnt);
				mult_idx = DMA_CUED_MULT1_OFF;
				mult_dst = dst_pos ? DMA_CDB_SG_DST2 :
						     DMA_CDB_SG_DST1;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक znum = 0;

			/* WXOR-only;
			 * skip first slots with destinations (अगर ZERO_DST has
			 * place)
			 */
			अगर (test_bit(PPC440SPE_ZERO_P, &sw_desc->flags))
				znum++;
			अगर (test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags))
				znum++;

			iter = ppc440spe_get_group_entry(sw_desc, index + znum);
			mult_idx = DMA_CUED_MULT1_OFF;
			mult_dst = dst_pos ? DMA_CDB_SG_DST2 : DMA_CDB_SG_DST1;
		पूर्ण

		अगर (likely(iter)) अणु
			ppc440spe_desc_set_src_mult(iter, chan,
				mult_idx, mult_dst, mult);

			अगर (unlikely(iter1)) अणु
				/* अगर we have two destinations क्रम RXOR, then
				 * we've just set Q mult. Set-up P now.
				 */
				ppc440spe_desc_set_src_mult(iter1, chan,
					mult_idx, mult_dst, 1);
			पूर्ण

		पूर्ण
		अवरोध;

	हाल PPC440SPE_XOR_ID:
		iter = sw_desc->group_head;
		अगर (sw_desc->dst_cnt == 2) अणु
			/* both P & Q calculations required; set P mult here */
			ppc440spe_adma_dma2rxor_set_mult(iter, index, 1);

			/* and then set Q mult */
			iter = ppc440spe_get_group_entry(sw_desc,
			       sw_desc->descs_per_op);
		पूर्ण
		ppc440spe_adma_dma2rxor_set_mult(iter, index, mult);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_मुक्त_chan_resources - मुक्त the resources allocated
 */
अटल व्योम ppc440spe_adma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	काष्ठा ppc440spe_adma_desc_slot *iter, *_iter;
	पूर्णांक in_use_descs = 0;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);
	ppc440spe_adma_slot_cleanup(ppc440spe_chan);

	spin_lock_bh(&ppc440spe_chan->lock);
	list_क्रम_each_entry_safe(iter, _iter, &ppc440spe_chan->chain,
					chain_node) अणु
		in_use_descs++;
		list_del(&iter->chain_node);
	पूर्ण
	list_क्रम_each_entry_safe_reverse(iter, _iter,
			&ppc440spe_chan->all_slots, slot_node) अणु
		list_del(&iter->slot_node);
		kमुक्त(iter);
		ppc440spe_chan->slots_allocated--;
	पूर्ण
	ppc440spe_chan->last_used = शून्य;

	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d %s slots_allocated %d\n",
		ppc440spe_chan->device->id,
		__func__, ppc440spe_chan->slots_allocated);
	spin_unlock_bh(&ppc440spe_chan->lock);

	/* one is ok since we left it on there on purpose */
	अगर (in_use_descs > 1)
		prपूर्णांकk(KERN_ERR "SPE: Freeing %d in use descriptors!\n",
			in_use_descs - 1);
पूर्ण

/**
 * ppc440spe_adma_tx_status - poll the status of an ADMA transaction
 * @chan: ADMA channel handle
 * @cookie: ADMA transaction identअगरier
 * @txstate: a holder क्रम the current state of the channel
 */
अटल क्रमागत dma_status ppc440spe_adma_tx_status(काष्ठा dma_chan *chan,
			dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;
	क्रमागत dma_status ret;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);
	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	ppc440spe_adma_slot_cleanup(ppc440spe_chan);

	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

/**
 * ppc440spe_adma_eot_handler - end of transfer पूर्णांकerrupt handler
 */
अटल irqवापस_t ppc440spe_adma_eot_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ppc440spe_adma_chan *chan = data;

	dev_dbg(chan->device->common.dev,
		"ppc440spe adma%d: %s\n", chan->device->id, __func__);

	tasklet_schedule(&chan->irq_tasklet);
	ppc440spe_adma_device_clear_eot_status(chan);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ppc440spe_adma_err_handler - DMA error पूर्णांकerrupt handler;
 *	करो the same things as a eot handler
 */
अटल irqवापस_t ppc440spe_adma_err_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ppc440spe_adma_chan *chan = data;

	dev_dbg(chan->device->common.dev,
		"ppc440spe adma%d: %s\n", chan->device->id, __func__);

	tasklet_schedule(&chan->irq_tasklet);
	ppc440spe_adma_device_clear_eot_status(chan);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ppc440spe_test_callback - called when test operation has been करोne
 */
अटल व्योम ppc440spe_test_callback(व्योम *unused)
अणु
	complete(&ppc440spe_r6_test_comp);
पूर्ण

/**
 * ppc440spe_adma_issue_pending - flush all pending descriptors to h/w
 */
अटल व्योम ppc440spe_adma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;

	ppc440spe_chan = to_ppc440spe_adma_chan(chan);
	dev_dbg(ppc440spe_chan->device->common.dev,
		"ppc440spe adma%d: %s %d \n", ppc440spe_chan->device->id,
		__func__, ppc440spe_chan->pending);

	अगर (ppc440spe_chan->pending) अणु
		ppc440spe_chan->pending = 0;
		ppc440spe_chan_append(ppc440spe_chan);
	पूर्ण
पूर्ण

/**
 * ppc440spe_chan_start_null_xor - initiate the first XOR operation (DMA engines
 *	use FIFOs (as opposite to chains used in XOR) so this is a XOR
 *	specअगरic operation)
 */
अटल व्योम ppc440spe_chan_start_null_xor(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा ppc440spe_adma_desc_slot *sw_desc, *group_start;
	dma_cookie_t cookie;
	पूर्णांक slot_cnt, slots_per_op;

	dev_dbg(chan->device->common.dev,
		"ppc440spe adma%d: %s\n", chan->device->id, __func__);

	spin_lock_bh(&chan->lock);
	slot_cnt = ppc440spe_chan_xor_slot_count(0, 2, &slots_per_op);
	sw_desc = ppc440spe_adma_alloc_slots(chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		group_start = sw_desc->group_head;
		list_splice_init(&sw_desc->group_list, &chan->chain);
		async_tx_ack(&sw_desc->async_tx);
		ppc440spe_desc_init_null_xor(group_start);

		cookie = dma_cookie_assign(&sw_desc->async_tx);

		/* initialize the completed cookie to be less than
		 * the most recently used cookie
		 */
		chan->common.completed_cookie = cookie - 1;

		/* channel should not be busy */
		BUG_ON(ppc440spe_chan_is_busy(chan));

		/* set the descriptor address */
		ppc440spe_chan_set_first_xor_descriptor(chan, sw_desc);

		/* run the descriptor */
		ppc440spe_chan_run(chan);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "ppc440spe adma%d"
			" failed to allocate null descriptor\n",
			chan->device->id);
	spin_unlock_bh(&chan->lock);
पूर्ण

/**
 * ppc440spe_test_raid6 - test are RAID-6 capabilities enabled successfully.
 *	For this we just perक्रमm one WXOR operation with the same source
 *	and destination addresses, the GF-multiplier is 1; so अगर RAID-6
 *	capabilities are enabled then we'll get src/dst filled with zero.
 */
अटल पूर्णांक ppc440spe_test_raid6(काष्ठा ppc440spe_adma_chan *chan)
अणु
	काष्ठा ppc440spe_adma_desc_slot *sw_desc, *iter;
	काष्ठा page *pg;
	अक्षर *a;
	dma_addr_t dma_addr, addrs[2];
	अचिन्हित दीर्घ op = 0;
	पूर्णांक rval = 0;

	set_bit(PPC440SPE_DESC_WXOR, &op);

	pg = alloc_page(GFP_KERNEL);
	अगर (!pg)
		वापस -ENOMEM;

	spin_lock_bh(&chan->lock);
	sw_desc = ppc440spe_adma_alloc_slots(chan, 1, 1);
	अगर (sw_desc) अणु
		/* 1 src, 1 dsr, पूर्णांक_ena, WXOR */
		ppc440spe_desc_init_dma01pq(sw_desc, 1, 1, 1, op);
		list_क्रम_each_entry(iter, &sw_desc->group_list, chain_node) अणु
			ppc440spe_desc_set_byte_count(iter, chan, PAGE_SIZE);
			iter->unmap_len = PAGE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		rval = -EFAULT;
		spin_unlock_bh(&chan->lock);
		जाओ निकास;
	पूर्ण
	spin_unlock_bh(&chan->lock);

	/* Fill the test page with ones */
	स_रखो(page_address(pg), 0xFF, PAGE_SIZE);
	dma_addr = dma_map_page(chan->device->dev, pg, 0,
				PAGE_SIZE, DMA_BIसूचीECTIONAL);

	/* Setup addresses */
	ppc440spe_adma_pq_set_src(sw_desc, dma_addr, 0);
	ppc440spe_adma_pq_set_src_mult(sw_desc, 1, 0, 0);
	addrs[0] = dma_addr;
	addrs[1] = 0;
	ppc440spe_adma_pq_set_dest(sw_desc, addrs, DMA_PREP_PQ_DISABLE_Q);

	async_tx_ack(&sw_desc->async_tx);
	sw_desc->async_tx.callback = ppc440spe_test_callback;
	sw_desc->async_tx.callback_param = शून्य;

	init_completion(&ppc440spe_r6_test_comp);

	ppc440spe_adma_tx_submit(&sw_desc->async_tx);
	ppc440spe_adma_issue_pending(&chan->common);

	रुको_क्रम_completion(&ppc440spe_r6_test_comp);

	/* Now check अगर the test page is zeroed */
	a = page_address(pg);
	अगर ((*(u32 *)a) == 0 && स_भेद(a, a+4, PAGE_SIZE-4) == 0) अणु
		/* page is zero - RAID-6 enabled */
		rval = 0;
	पूर्ण अन्यथा अणु
		/* RAID-6 was not enabled */
		rval = -EINVAL;
	पूर्ण
निकास:
	__मुक्त_page(pg);
	वापस rval;
पूर्ण

अटल व्योम ppc440spe_adma_init_capabilities(काष्ठा ppc440spe_adma_device *adev)
अणु
	चयन (adev->id) अणु
	हाल PPC440SPE_DMA0_ID:
	हाल PPC440SPE_DMA1_ID:
		dma_cap_set(DMA_MEMCPY, adev->common.cap_mask);
		dma_cap_set(DMA_INTERRUPT, adev->common.cap_mask);
		dma_cap_set(DMA_PQ, adev->common.cap_mask);
		dma_cap_set(DMA_PQ_VAL, adev->common.cap_mask);
		dma_cap_set(DMA_XOR_VAL, adev->common.cap_mask);
		अवरोध;
	हाल PPC440SPE_XOR_ID:
		dma_cap_set(DMA_XOR, adev->common.cap_mask);
		dma_cap_set(DMA_PQ, adev->common.cap_mask);
		dma_cap_set(DMA_INTERRUPT, adev->common.cap_mask);
		adev->common.cap_mask = adev->common.cap_mask;
		अवरोध;
	पूर्ण

	/* Set base routines */
	adev->common.device_alloc_chan_resources =
				ppc440spe_adma_alloc_chan_resources;
	adev->common.device_मुक्त_chan_resources =
				ppc440spe_adma_मुक्त_chan_resources;
	adev->common.device_tx_status = ppc440spe_adma_tx_status;
	adev->common.device_issue_pending = ppc440spe_adma_issue_pending;

	/* Set prep routines based on capability */
	अगर (dma_has_cap(DMA_MEMCPY, adev->common.cap_mask)) अणु
		adev->common.device_prep_dma_स_नकल =
			ppc440spe_adma_prep_dma_स_नकल;
	पूर्ण
	अगर (dma_has_cap(DMA_XOR, adev->common.cap_mask)) अणु
		adev->common.max_xor = XOR_MAX_OPS;
		adev->common.device_prep_dma_xor =
			ppc440spe_adma_prep_dma_xor;
	पूर्ण
	अगर (dma_has_cap(DMA_PQ, adev->common.cap_mask)) अणु
		चयन (adev->id) अणु
		हाल PPC440SPE_DMA0_ID:
			dma_set_maxpq(&adev->common,
				DMA0_FIFO_SIZE / माप(काष्ठा dma_cdb), 0);
			अवरोध;
		हाल PPC440SPE_DMA1_ID:
			dma_set_maxpq(&adev->common,
				DMA1_FIFO_SIZE / माप(काष्ठा dma_cdb), 0);
			अवरोध;
		हाल PPC440SPE_XOR_ID:
			adev->common.max_pq = XOR_MAX_OPS * 3;
			अवरोध;
		पूर्ण
		adev->common.device_prep_dma_pq =
			ppc440spe_adma_prep_dma_pq;
	पूर्ण
	अगर (dma_has_cap(DMA_PQ_VAL, adev->common.cap_mask)) अणु
		चयन (adev->id) अणु
		हाल PPC440SPE_DMA0_ID:
			adev->common.max_pq = DMA0_FIFO_SIZE /
						माप(काष्ठा dma_cdb);
			अवरोध;
		हाल PPC440SPE_DMA1_ID:
			adev->common.max_pq = DMA1_FIFO_SIZE /
						माप(काष्ठा dma_cdb);
			अवरोध;
		पूर्ण
		adev->common.device_prep_dma_pq_val =
			ppc440spe_adma_prep_dma_pqzero_sum;
	पूर्ण
	अगर (dma_has_cap(DMA_XOR_VAL, adev->common.cap_mask)) अणु
		चयन (adev->id) अणु
		हाल PPC440SPE_DMA0_ID:
			adev->common.max_xor = DMA0_FIFO_SIZE /
						माप(काष्ठा dma_cdb);
			अवरोध;
		हाल PPC440SPE_DMA1_ID:
			adev->common.max_xor = DMA1_FIFO_SIZE /
						माप(काष्ठा dma_cdb);
			अवरोध;
		पूर्ण
		adev->common.device_prep_dma_xor_val =
			ppc440spe_adma_prep_dma_xor_zero_sum;
	पूर्ण
	अगर (dma_has_cap(DMA_INTERRUPT, adev->common.cap_mask)) अणु
		adev->common.device_prep_dma_पूर्णांकerrupt =
			ppc440spe_adma_prep_dma_पूर्णांकerrupt;
	पूर्ण
	pr_info("%s: AMCC(R) PPC440SP(E) ADMA Engine: "
	  "( %s%s%s%s%s%s)\n",
	  dev_name(adev->dev),
	  dma_has_cap(DMA_PQ, adev->common.cap_mask) ? "pq " : "",
	  dma_has_cap(DMA_PQ_VAL, adev->common.cap_mask) ? "pq_val " : "",
	  dma_has_cap(DMA_XOR, adev->common.cap_mask) ? "xor " : "",
	  dma_has_cap(DMA_XOR_VAL, adev->common.cap_mask) ? "xor_val " : "",
	  dma_has_cap(DMA_MEMCPY, adev->common.cap_mask) ? "memcpy " : "",
	  dma_has_cap(DMA_INTERRUPT, adev->common.cap_mask) ? "intr " : "");
पूर्ण

अटल पूर्णांक ppc440spe_adma_setup_irqs(काष्ठा ppc440spe_adma_device *adev,
				     काष्ठा ppc440spe_adma_chan *chan,
				     पूर्णांक *initcode)
अणु
	काष्ठा platक्रमm_device *ofdev;
	काष्ठा device_node *np;
	पूर्णांक ret;

	ofdev = container_of(adev->dev, काष्ठा platक्रमm_device, dev);
	np = ofdev->dev.of_node;
	अगर (adev->id != PPC440SPE_XOR_ID) अणु
		adev->err_irq = irq_of_parse_and_map(np, 1);
		अगर (!adev->err_irq) अणु
			dev_warn(adev->dev, "no err irq resource?\n");
			*initcode = PPC_ADMA_INIT_IRQ2;
			adev->err_irq = -ENXIO;
		पूर्ण अन्यथा
			atomic_inc(&ppc440spe_adma_err_irq_ref);
	पूर्ण अन्यथा अणु
		adev->err_irq = -ENXIO;
	पूर्ण

	adev->irq = irq_of_parse_and_map(np, 0);
	अगर (!adev->irq) अणु
		dev_err(adev->dev, "no irq resource\n");
		*initcode = PPC_ADMA_INIT_IRQ1;
		ret = -ENXIO;
		जाओ err_irq_map;
	पूर्ण
	dev_dbg(adev->dev, "irq %d, err irq %d\n",
		adev->irq, adev->err_irq);

	ret = request_irq(adev->irq, ppc440spe_adma_eot_handler,
			  0, dev_driver_string(adev->dev), chan);
	अगर (ret) अणु
		dev_err(adev->dev, "can't request irq %d\n",
			adev->irq);
		*initcode = PPC_ADMA_INIT_IRQ1;
		ret = -EIO;
		जाओ err_req1;
	पूर्ण

	/* only DMA engines have a separate error IRQ
	 * so it's Ok अगर err_irq < 0 in XOR engine हाल.
	 */
	अगर (adev->err_irq > 0) अणु
		/* both DMA engines share common error IRQ */
		ret = request_irq(adev->err_irq,
				  ppc440spe_adma_err_handler,
				  IRQF_SHARED,
				  dev_driver_string(adev->dev),
				  chan);
		अगर (ret) अणु
			dev_err(adev->dev, "can't request irq %d\n",
				adev->err_irq);
			*initcode = PPC_ADMA_INIT_IRQ2;
			ret = -EIO;
			जाओ err_req2;
		पूर्ण
	पूर्ण

	अगर (adev->id == PPC440SPE_XOR_ID) अणु
		/* enable XOR engine पूर्णांकerrupts */
		ioग_लिखो32be(XOR_IE_CBCIE_BIT | XOR_IE_ICBIE_BIT |
			    XOR_IE_ICIE_BIT | XOR_IE_RPTIE_BIT,
			    &adev->xor_reg->ier);
	पूर्ण अन्यथा अणु
		u32 mask, enable;

		np = of_find_compatible_node(शून्य, शून्य, "ibm,i2o-440spe");
		अगर (!np) अणु
			pr_err("%s: can't find I2O device tree node\n",
				__func__);
			ret = -ENODEV;
			जाओ err_req2;
		पूर्ण
		adev->i2o_reg = of_iomap(np, 0);
		अगर (!adev->i2o_reg) अणु
			pr_err("%s: failed to map I2O registers\n", __func__);
			of_node_put(np);
			ret = -EINVAL;
			जाओ err_req2;
		पूर्ण
		of_node_put(np);
		/* Unmask 'CS FIFO Attention' पूर्णांकerrupts and
		 * enable generating पूर्णांकerrupts on errors
		 */
		enable = (adev->id == PPC440SPE_DMA0_ID) ?
			 ~(I2O_IOPIM_P0SNE | I2O_IOPIM_P0EM) :
			 ~(I2O_IOPIM_P1SNE | I2O_IOPIM_P1EM);
		mask = ioपढ़ो32(&adev->i2o_reg->iopim) & enable;
		ioग_लिखो32(mask, &adev->i2o_reg->iopim);
	पूर्ण
	वापस 0;

err_req2:
	मुक्त_irq(adev->irq, chan);
err_req1:
	irq_dispose_mapping(adev->irq);
err_irq_map:
	अगर (adev->err_irq > 0) अणु
		अगर (atomic_dec_and_test(&ppc440spe_adma_err_irq_ref))
			irq_dispose_mapping(adev->err_irq);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ppc440spe_adma_release_irqs(काष्ठा ppc440spe_adma_device *adev,
					काष्ठा ppc440spe_adma_chan *chan)
अणु
	u32 mask, disable;

	अगर (adev->id == PPC440SPE_XOR_ID) अणु
		/* disable XOR engine पूर्णांकerrupts */
		mask = ioपढ़ो32be(&adev->xor_reg->ier);
		mask &= ~(XOR_IE_CBCIE_BIT | XOR_IE_ICBIE_BIT |
			  XOR_IE_ICIE_BIT | XOR_IE_RPTIE_BIT);
		ioग_लिखो32be(mask, &adev->xor_reg->ier);
	पूर्ण अन्यथा अणु
		/* disable DMAx engine पूर्णांकerrupts */
		disable = (adev->id == PPC440SPE_DMA0_ID) ?
			  (I2O_IOPIM_P0SNE | I2O_IOPIM_P0EM) :
			  (I2O_IOPIM_P1SNE | I2O_IOPIM_P1EM);
		mask = ioपढ़ो32(&adev->i2o_reg->iopim) | disable;
		ioग_लिखो32(mask, &adev->i2o_reg->iopim);
	पूर्ण
	मुक्त_irq(adev->irq, chan);
	irq_dispose_mapping(adev->irq);
	अगर (adev->err_irq > 0) अणु
		मुक्त_irq(adev->err_irq, chan);
		अगर (atomic_dec_and_test(&ppc440spe_adma_err_irq_ref)) अणु
			irq_dispose_mapping(adev->err_irq);
			iounmap(adev->i2o_reg);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ppc440spe_adma_probe - probe the asynch device
 */
अटल पूर्णांक ppc440spe_adma_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा resource res;
	काष्ठा ppc440spe_adma_device *adev;
	काष्ठा ppc440spe_adma_chan *chan;
	काष्ठा ppc_dma_chan_ref *ref, *_ref;
	पूर्णांक ret = 0, initcode = PPC_ADMA_INIT_OK;
	स्थिर u32 *idx;
	पूर्णांक len;
	व्योम *regs;
	u32 id, pool_size;

	अगर (of_device_is_compatible(np, "amcc,xor-accelerator")) अणु
		id = PPC440SPE_XOR_ID;
		/* As far as the XOR engine is concerned, it करोes not
		 * use FIFOs but uses linked list. So there is no dependency
		 * between pool size to allocate and the engine configuration.
		 */
		pool_size = PAGE_SIZE << 1;
	पूर्ण अन्यथा अणु
		/* it is DMA0 or DMA1 */
		idx = of_get_property(np, "cell-index", &len);
		अगर (!idx || (len != माप(u32))) अणु
			dev_err(&ofdev->dev, "Device node %pOF has missing "
				"or invalid cell-index property\n",
				np);
			वापस -EINVAL;
		पूर्ण
		id = *idx;
		/* DMA0,1 engines use FIFO to मुख्यtain CDBs, so we
		 * should allocate the pool accordingly to size of this
		 * FIFO. Thus, the pool size depends on the FIFO depth:
		 * how much CDBs poपूर्णांकers the FIFO may contain then so
		 * much CDBs we should provide in the pool.
		 * That is
		 *   CDB size = 32B;
		 *   CDBs number = (DMA0_FIFO_SIZE >> 3);
		 *   Pool size = CDBs number * CDB size =
		 *      = (DMA0_FIFO_SIZE >> 3) << 5 = DMA0_FIFO_SIZE << 2.
		 */
		pool_size = (id == PPC440SPE_DMA0_ID) ?
			    DMA0_FIFO_SIZE : DMA1_FIFO_SIZE;
		pool_size <<= 2;
	पूर्ण

	अगर (of_address_to_resource(np, 0, &res)) अणु
		dev_err(&ofdev->dev, "failed to get memory resource\n");
		initcode = PPC_ADMA_INIT_MEMRES;
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!request_mem_region(res.start, resource_size(&res),
				dev_driver_string(&ofdev->dev))) अणु
		dev_err(&ofdev->dev, "failed to request memory region %pR\n",
			&res);
		initcode = PPC_ADMA_INIT_MEMREG;
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* create a device */
	adev = kzalloc(माप(*adev), GFP_KERNEL);
	अगर (!adev) अणु
		initcode = PPC_ADMA_INIT_ALLOC;
		ret = -ENOMEM;
		जाओ err_adev_alloc;
	पूर्ण

	adev->id = id;
	adev->pool_size = pool_size;
	/* allocate coherent memory क्रम hardware descriptors */
	adev->dma_desc_pool_virt = dma_alloc_coherent(&ofdev->dev,
					adev->pool_size, &adev->dma_desc_pool,
					GFP_KERNEL);
	अगर (adev->dma_desc_pool_virt == शून्य) अणु
		dev_err(&ofdev->dev, "failed to allocate %d bytes of coherent "
			"memory for hardware descriptors\n",
			adev->pool_size);
		initcode = PPC_ADMA_INIT_COHERENT;
		ret = -ENOMEM;
		जाओ err_dma_alloc;
	पूर्ण
	dev_dbg(&ofdev->dev, "allocated descriptor pool virt 0x%p phys 0x%llx\n",
		adev->dma_desc_pool_virt, (u64)adev->dma_desc_pool);

	regs = ioremap(res.start, resource_size(&res));
	अगर (!regs) अणु
		dev_err(&ofdev->dev, "failed to ioremap regs!\n");
		ret = -ENOMEM;
		जाओ err_regs_alloc;
	पूर्ण

	अगर (adev->id == PPC440SPE_XOR_ID) अणु
		adev->xor_reg = regs;
		/* Reset XOR */
		ioग_लिखो32be(XOR_CRSR_XASR_BIT, &adev->xor_reg->crsr);
		ioग_लिखो32be(XOR_CRSR_64BA_BIT, &adev->xor_reg->crrr);
	पूर्ण अन्यथा अणु
		माप_प्रकार fअगरo_size = (adev->id == PPC440SPE_DMA0_ID) ?
				   DMA0_FIFO_SIZE : DMA1_FIFO_SIZE;
		adev->dma_reg = regs;
		/* DMAx_FIFO_SIZE is defined in bytes,
		 * <fsiz> - is defined in number of CDB poपूर्णांकers (8byte).
		 * DMA FIFO Length = CSlength + CPlength, where
		 * CSlength = CPlength = (fsiz + 1) * 8.
		 */
		ioग_लिखो32(DMA_FIFO_ENABLE | ((fअगरo_size >> 3) - 2),
			  &adev->dma_reg->fsiz);
		/* Configure DMA engine */
		ioग_लिखो32(DMA_CFG_DXEPR_HP | DMA_CFG_DFMPP_HP | DMA_CFG_FALGN,
			  &adev->dma_reg->cfg);
		/* Clear Status */
		ioग_लिखो32(~0, &adev->dma_reg->dsts);
	पूर्ण

	adev->dev = &ofdev->dev;
	adev->common.dev = &ofdev->dev;
	INIT_LIST_HEAD(&adev->common.channels);
	platक्रमm_set_drvdata(ofdev, adev);

	/* create a channel */
	chan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan) अणु
		initcode = PPC_ADMA_INIT_CHANNEL;
		ret = -ENOMEM;
		जाओ err_chan_alloc;
	पूर्ण

	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->chain);
	INIT_LIST_HEAD(&chan->all_slots);
	chan->device = adev;
	chan->common.device = &adev->common;
	dma_cookie_init(&chan->common);
	list_add_tail(&chan->common.device_node, &adev->common.channels);
	tasklet_setup(&chan->irq_tasklet, ppc440spe_adma_tasklet);

	/* allocate and map helper pages क्रम async validation or
	 * async_mult/async_sum_product operations on DMA0/1.
	 */
	अगर (adev->id != PPC440SPE_XOR_ID) अणु
		chan->pdest_page = alloc_page(GFP_KERNEL);
		chan->qdest_page = alloc_page(GFP_KERNEL);
		अगर (!chan->pdest_page ||
		    !chan->qdest_page) अणु
			अगर (chan->pdest_page)
				__मुक्त_page(chan->pdest_page);
			अगर (chan->qdest_page)
				__मुक्त_page(chan->qdest_page);
			ret = -ENOMEM;
			जाओ err_page_alloc;
		पूर्ण
		chan->pdest = dma_map_page(&ofdev->dev, chan->pdest_page, 0,
					   PAGE_SIZE, DMA_BIसूचीECTIONAL);
		chan->qdest = dma_map_page(&ofdev->dev, chan->qdest_page, 0,
					   PAGE_SIZE, DMA_BIसूचीECTIONAL);
	पूर्ण

	ref = kदो_स्मृति(माप(*ref), GFP_KERNEL);
	अगर (ref) अणु
		ref->chan = &chan->common;
		INIT_LIST_HEAD(&ref->node);
		list_add_tail(&ref->node, &ppc440spe_adma_chan_list);
	पूर्ण अन्यथा अणु
		dev_err(&ofdev->dev, "failed to allocate channel reference!\n");
		ret = -ENOMEM;
		जाओ err_ref_alloc;
	पूर्ण

	ret = ppc440spe_adma_setup_irqs(adev, chan, &initcode);
	अगर (ret)
		जाओ err_irq;

	ppc440spe_adma_init_capabilities(adev);

	ret = dma_async_device_रेजिस्टर(&adev->common);
	अगर (ret) अणु
		initcode = PPC_ADMA_INIT_REGISTER;
		dev_err(&ofdev->dev, "failed to register dma device\n");
		जाओ err_dev_reg;
	पूर्ण

	जाओ out;

err_dev_reg:
	ppc440spe_adma_release_irqs(adev, chan);
err_irq:
	list_क्रम_each_entry_safe(ref, _ref, &ppc440spe_adma_chan_list, node) अणु
		अगर (chan == to_ppc440spe_adma_chan(ref->chan)) अणु
			list_del(&ref->node);
			kमुक्त(ref);
		पूर्ण
	पूर्ण
err_ref_alloc:
	अगर (adev->id != PPC440SPE_XOR_ID) अणु
		dma_unmap_page(&ofdev->dev, chan->pdest,
			       PAGE_SIZE, DMA_BIसूचीECTIONAL);
		dma_unmap_page(&ofdev->dev, chan->qdest,
			       PAGE_SIZE, DMA_BIसूचीECTIONAL);
		__मुक्त_page(chan->pdest_page);
		__मुक्त_page(chan->qdest_page);
	पूर्ण
err_page_alloc:
	kमुक्त(chan);
err_chan_alloc:
	अगर (adev->id == PPC440SPE_XOR_ID)
		iounmap(adev->xor_reg);
	अन्यथा
		iounmap(adev->dma_reg);
err_regs_alloc:
	dma_मुक्त_coherent(adev->dev, adev->pool_size,
			  adev->dma_desc_pool_virt,
			  adev->dma_desc_pool);
err_dma_alloc:
	kमुक्त(adev);
err_adev_alloc:
	release_mem_region(res.start, resource_size(&res));
out:
	अगर (id < PPC440SPE_ADMA_ENGINES_NUM)
		ppc440spe_adma_devices[id] = initcode;

	वापस ret;
पूर्ण

/**
 * ppc440spe_adma_हटाओ - हटाओ the asynch device
 */
अटल पूर्णांक ppc440spe_adma_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा ppc440spe_adma_device *adev = platक्रमm_get_drvdata(ofdev);
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा resource res;
	काष्ठा dma_chan *chan, *_chan;
	काष्ठा ppc_dma_chan_ref *ref, *_ref;
	काष्ठा ppc440spe_adma_chan *ppc440spe_chan;

	अगर (adev->id < PPC440SPE_ADMA_ENGINES_NUM)
		ppc440spe_adma_devices[adev->id] = -1;

	dma_async_device_unरेजिस्टर(&adev->common);

	list_क्रम_each_entry_safe(chan, _chan, &adev->common.channels,
				 device_node) अणु
		ppc440spe_chan = to_ppc440spe_adma_chan(chan);
		ppc440spe_adma_release_irqs(adev, ppc440spe_chan);
		tasklet_समाप्त(&ppc440spe_chan->irq_tasklet);
		अगर (adev->id != PPC440SPE_XOR_ID) अणु
			dma_unmap_page(&ofdev->dev, ppc440spe_chan->pdest,
					PAGE_SIZE, DMA_BIसूचीECTIONAL);
			dma_unmap_page(&ofdev->dev, ppc440spe_chan->qdest,
					PAGE_SIZE, DMA_BIसूचीECTIONAL);
			__मुक्त_page(ppc440spe_chan->pdest_page);
			__मुक्त_page(ppc440spe_chan->qdest_page);
		पूर्ण
		list_क्रम_each_entry_safe(ref, _ref, &ppc440spe_adma_chan_list,
					 node) अणु
			अगर (ppc440spe_chan ==
			    to_ppc440spe_adma_chan(ref->chan)) अणु
				list_del(&ref->node);
				kमुक्त(ref);
			पूर्ण
		पूर्ण
		list_del(&chan->device_node);
		kमुक्त(ppc440spe_chan);
	पूर्ण

	dma_मुक्त_coherent(adev->dev, adev->pool_size,
			  adev->dma_desc_pool_virt, adev->dma_desc_pool);
	अगर (adev->id == PPC440SPE_XOR_ID)
		iounmap(adev->xor_reg);
	अन्यथा
		iounmap(adev->dma_reg);
	of_address_to_resource(np, 0, &res);
	release_mem_region(res.start, resource_size(&res));
	kमुक्त(adev);
	वापस 0;
पूर्ण

/*
 * /sys driver पूर्णांकerface to enable h/w RAID-6 capabilities
 * Files created in e.g. /sys/devices/plb.0/400100100.dma0/driver/
 * directory are "devices", "enable" and "poly".
 * "devices" shows available engines.
 * "enable" is used to enable RAID-6 capabilities or to check
 * whether these has been activated.
 * "poly" allows setting/checking used polynomial (क्रम PPC440SPe only).
 */

अटल sमाप_प्रकार devices_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	sमाप_प्रकार size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < PPC440SPE_ADMA_ENGINES_NUM; i++) अणु
		अगर (ppc440spe_adma_devices[i] == -1)
			जारी;
		size += scnम_लिखो(buf + size, PAGE_SIZE - size,
				 "PPC440SP(E)-ADMA.%d: %s\n", i,
				 ppc_adma_errors[ppc440spe_adma_devices[i]]);
	पूर्ण
	वापस size;
पूर्ण
अटल DRIVER_ATTR_RO(devices);

अटल sमाप_प्रकार enable_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE,
			"PPC440SP(e) RAID-6 capabilities are %sABLED.\n",
			ppc440spe_r6_enabled ? "EN" : "DIS");
पूर्ण

अटल sमाप_प्रकार enable_store(काष्ठा device_driver *dev, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;

	अगर (!count || count > 11)
		वापस -EINVAL;

	अगर (!ppc440spe_r6_tchan)
		वापस -EFAULT;

	/* Write a key */
	माला_पूछो(buf, "%lx", &val);
	dcr_ग_लिखो(ppc440spe_mq_dcr_host, DCRN_MQ0_XORBA, val);
	isync();

	/* Verअगरy whether it really works now */
	अगर (ppc440spe_test_raid6(ppc440spe_r6_tchan) == 0) अणु
		pr_info("PPC440SP(e) RAID-6 has been activated "
			"successfully\n");
		ppc440spe_r6_enabled = 1;
	पूर्ण अन्यथा अणु
		pr_info("PPC440SP(e) RAID-6 hasn't been activated!"
			" Error key ?\n");
		ppc440spe_r6_enabled = 0;
	पूर्ण
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(enable);

अटल sमाप_प्रकार poly_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	sमाप_प्रकार size = 0;
	u32 reg;

#अगर_घोषित CONFIG_440SP
	/* 440SP has fixed polynomial */
	reg = 0x4d;
#अन्यथा
	reg = dcr_पढ़ो(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL);
	reg >>= MQ0_CFBHL_POLY;
	reg &= 0xFF;
#पूर्ण_अगर

	size = snम_लिखो(buf, PAGE_SIZE, "PPC440SP(e) RAID-6 driver "
			"uses 0x1%02x polynomial.\n", reg);
	वापस size;
पूर्ण

अटल sमाप_प्रकार poly_store(काष्ठा device_driver *dev, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	अचिन्हित दीर्घ reg, val;

#अगर_घोषित CONFIG_440SP
	/* 440SP uses शेष 0x14D polynomial only */
	वापस -EINVAL;
#पूर्ण_अगर

	अगर (!count || count > 6)
		वापस -EINVAL;

	/* e.g., 0x14D or 0x11D */
	माला_पूछो(buf, "%lx", &val);

	अगर (val & ~0x1FF)
		वापस -EINVAL;

	val &= 0xFF;
	reg = dcr_पढ़ो(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL);
	reg &= ~(0xFF << MQ0_CFBHL_POLY);
	reg |= val << MQ0_CFBHL_POLY;
	dcr_ग_लिखो(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL, reg);

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(poly);

/*
 * Common initialisation क्रम RAID engines; allocate memory क्रम
 * DMAx FIFOs, perक्रमm configuration common क्रम all DMA engines.
 * Further DMA engine specअगरic configuration is करोne at probe समय.
 */
अटल पूर्णांक ppc440spe_configure_raid_devices(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource i2o_res;
	काष्ठा i2o_regs __iomem *i2o_reg;
	dcr_host_t i2o_dcr_host;
	अचिन्हित पूर्णांक dcr_base, dcr_len;
	पूर्णांक i, ret;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,i2o-440spe");
	अगर (!np) अणु
		pr_err("%s: can't find I2O device tree node\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	अगर (of_address_to_resource(np, 0, &i2o_res)) अणु
		of_node_put(np);
		वापस -EINVAL;
	पूर्ण

	i2o_reg = of_iomap(np, 0);
	अगर (!i2o_reg) अणु
		pr_err("%s: failed to map I2O registers\n", __func__);
		of_node_put(np);
		वापस -EINVAL;
	पूर्ण

	/* Get I2O DCRs base */
	dcr_base = dcr_resource_start(np, 0);
	dcr_len = dcr_resource_len(np, 0);
	अगर (!dcr_base && !dcr_len) अणु
		pr_err("%pOF: can't get DCR registers base/len!\n", np);
		of_node_put(np);
		iounmap(i2o_reg);
		वापस -ENODEV;
	पूर्ण

	i2o_dcr_host = dcr_map(np, dcr_base, dcr_len);
	अगर (!DCR_MAP_OK(i2o_dcr_host)) अणु
		pr_err("%pOF: failed to map DCRs!\n", np);
		of_node_put(np);
		iounmap(i2o_reg);
		वापस -ENODEV;
	पूर्ण
	of_node_put(np);

	/* Provide memory regions क्रम DMA's FIFOs: I2O, DMA0 and DMA1 share
	 * the base address of FIFO memory space.
	 * Actually we need twice more physical memory than programmed in the
	 * <fsiz> रेजिस्टर (because there are two FIFOs क्रम each DMA: CP and CS)
	 */
	ppc440spe_dma_fअगरo_buf = kदो_स्मृति((DMA0_FIFO_SIZE + DMA1_FIFO_SIZE) << 1,
					 GFP_KERNEL);
	अगर (!ppc440spe_dma_fअगरo_buf) अणु
		pr_err("%s: DMA FIFO buffer allocation failed.\n", __func__);
		iounmap(i2o_reg);
		dcr_unmap(i2o_dcr_host, dcr_len);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Configure h/w
	 */
	/* Reset I2O/DMA */
	mtdcri(SDR0, DCRN_SDR0_SRST, DCRN_SDR0_SRST_I2ODMA);
	mtdcri(SDR0, DCRN_SDR0_SRST, 0);

	/* Setup the base address of mmaped रेजिस्टरs */
	dcr_ग_लिखो(i2o_dcr_host, DCRN_I2O0_IBAH, (u32)(i2o_res.start >> 32));
	dcr_ग_लिखो(i2o_dcr_host, DCRN_I2O0_IBAL, (u32)(i2o_res.start) |
						I2O_REG_ENABLE);
	dcr_unmap(i2o_dcr_host, dcr_len);

	/* Setup FIFO memory space base address */
	ioग_लिखो32(0, &i2o_reg->अगरbah);
	ioग_लिखो32(((u32)__pa(ppc440spe_dma_fअगरo_buf)), &i2o_reg->अगरbal);

	/* set zero FIFO size क्रम I2O, so the whole
	 * ppc440spe_dma_fअगरo_buf is used by DMAs.
	 * DMAx_FIFOs will be configured जबतक probe.
	 */
	ioग_लिखो32(0, &i2o_reg->अगरsiz);
	iounmap(i2o_reg);

	/* To prepare WXOR/RXOR functionality we need access to
	 * Memory Queue Module DCRs (finally it will be enabled
	 * via /sys पूर्णांकerface of the ppc440spe ADMA driver).
	 */
	np = of_find_compatible_node(शून्य, शून्य, "ibm,mq-440spe");
	अगर (!np) अणु
		pr_err("%s: can't find MQ device tree node\n",
			__func__);
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	/* Get MQ DCRs base */
	dcr_base = dcr_resource_start(np, 0);
	dcr_len = dcr_resource_len(np, 0);
	अगर (!dcr_base && !dcr_len) अणु
		pr_err("%pOF: can't get DCR registers base/len!\n", np);
		ret = -ENODEV;
		जाओ out_mq;
	पूर्ण

	ppc440spe_mq_dcr_host = dcr_map(np, dcr_base, dcr_len);
	अगर (!DCR_MAP_OK(ppc440spe_mq_dcr_host)) अणु
		pr_err("%pOF: failed to map DCRs!\n", np);
		ret = -ENODEV;
		जाओ out_mq;
	पूर्ण
	of_node_put(np);
	ppc440spe_mq_dcr_len = dcr_len;

	/* Set HB alias */
	dcr_ग_लिखो(ppc440spe_mq_dcr_host, DCRN_MQ0_BAUH, DMA_CUED_XOR_HB);

	/* Set:
	 * - LL transaction passing limit to 1;
	 * - Memory controller cycle limit to 1;
	 * - Galois Polynomial to 0x14d (शेष)
	 */
	dcr_ग_लिखो(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL,
		  (1 << MQ0_CFBHL_TPLM) | (1 << MQ0_CFBHL_HBCL) |
		  (PPC440SPE_DEFAULT_POLY << MQ0_CFBHL_POLY));

	atomic_set(&ppc440spe_adma_err_irq_ref, 0);
	क्रम (i = 0; i < PPC440SPE_ADMA_ENGINES_NUM; i++)
		ppc440spe_adma_devices[i] = -1;

	वापस 0;

out_mq:
	of_node_put(np);
out_मुक्त:
	kमुक्त(ppc440spe_dma_fअगरo_buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id ppc440spe_adma_of_match[] = अणु
	अणु .compatible	= "ibm,dma-440spe", पूर्ण,
	अणु .compatible	= "amcc,xor-accelerator", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ppc440spe_adma_of_match);

अटल काष्ठा platक्रमm_driver ppc440spe_adma_driver = अणु
	.probe = ppc440spe_adma_probe,
	.हटाओ = ppc440spe_adma_हटाओ,
	.driver = अणु
		.name = "PPC440SP(E)-ADMA",
		.of_match_table = ppc440spe_adma_of_match,
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक ppc440spe_adma_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ppc440spe_configure_raid_devices();
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&ppc440spe_adma_driver);
	अगर (ret) अणु
		pr_err("%s: failed to register platform driver\n",
			__func__);
		जाओ out_reg;
	पूर्ण

	/* Initialization status */
	ret = driver_create_file(&ppc440spe_adma_driver.driver,
				 &driver_attr_devices);
	अगर (ret)
		जाओ out_dev;

	/* RAID-6 h/w enable entry */
	ret = driver_create_file(&ppc440spe_adma_driver.driver,
				 &driver_attr_enable);
	अगर (ret)
		जाओ out_en;

	/* GF polynomial to use */
	ret = driver_create_file(&ppc440spe_adma_driver.driver,
				 &driver_attr_poly);
	अगर (!ret)
		वापस ret;

	driver_हटाओ_file(&ppc440spe_adma_driver.driver,
			   &driver_attr_enable);
out_en:
	driver_हटाओ_file(&ppc440spe_adma_driver.driver,
			   &driver_attr_devices);
out_dev:
	/* User will not be able to enable h/w RAID-6 */
	pr_err("%s: failed to create RAID-6 driver interface\n",
		__func__);
	platक्रमm_driver_unरेजिस्टर(&ppc440spe_adma_driver);
out_reg:
	dcr_unmap(ppc440spe_mq_dcr_host, ppc440spe_mq_dcr_len);
	kमुक्त(ppc440spe_dma_fअगरo_buf);
	वापस ret;
पूर्ण

अटल व्योम __निकास ppc440spe_adma_निकास(व्योम)
अणु
	driver_हटाओ_file(&ppc440spe_adma_driver.driver,
			   &driver_attr_poly);
	driver_हटाओ_file(&ppc440spe_adma_driver.driver,
			   &driver_attr_enable);
	driver_हटाओ_file(&ppc440spe_adma_driver.driver,
			   &driver_attr_devices);
	platक्रमm_driver_unरेजिस्टर(&ppc440spe_adma_driver);
	dcr_unmap(ppc440spe_mq_dcr_host, ppc440spe_mq_dcr_len);
	kमुक्त(ppc440spe_dma_fअगरo_buf);
पूर्ण

arch_initcall(ppc440spe_adma_init);
module_निकास(ppc440spe_adma_निकास);

MODULE_AUTHOR("Yuri Tikhonov <yur@emcraft.com>");
MODULE_DESCRIPTION("PPC440SPE ADMA Engine Driver");
MODULE_LICENSE("GPL");
