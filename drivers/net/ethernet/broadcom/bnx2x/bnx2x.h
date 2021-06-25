<शैली गुरु>
/* bnx2x.h: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 */

#अगर_अघोषित BNX2X_H
#घोषणा BNX2X_H

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/types.h>
#समावेश <linux/pci_regs.h>

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/समयcounter.h>

/* compilation समय flags */

/* define this to make the driver मुक्तze on error to allow getting debug info
 * (you will need to reboot afterwards) */
/* #घोषणा BNX2X_STOP_ON_ERROR */

/* FIXME: Delete the DRV_MODULE_VERSION below, but please be warned
 * that it is not an easy task because such change has all chances
 * to अवरोध this driver due to amount of abuse of in-kernel पूर्णांकerfaces
 * between modules and FW.
 *
 * DO NOT UPDATE DRV_MODULE_VERSION below.
 */
#घोषणा DRV_MODULE_VERSION      "1.713.36-0"
#घोषणा BNX2X_BC_VER            0x040200

#अगर defined(CONFIG_DCB)
#घोषणा BCM_DCBNL
#पूर्ण_अगर

#समावेश "bnx2x_hsi.h"

#समावेश "../cnic_if.h"

#घोषणा BNX2X_MIN_MSIX_VEC_CNT(bp)		((bp)->min_msix_vec_cnt)

#समावेश <linux/mdपन.स>

#समावेश "bnx2x_reg.h"
#समावेश "bnx2x_fw_defs.h"
#समावेश "bnx2x_mfw_req.h"
#समावेश "bnx2x_link.h"
#समावेश "bnx2x_sp.h"
#समावेश "bnx2x_dcb.h"
#समावेश "bnx2x_stats.h"
#समावेश "bnx2x_vfpf.h"

क्रमागत bnx2x_पूर्णांक_mode अणु
	BNX2X_INT_MODE_MSIX,
	BNX2X_INT_MODE_INTX,
	BNX2X_INT_MODE_MSI
पूर्ण;

/* error/debug prपूर्णांकs */

#घोषणा DRV_MODULE_NAME		"bnx2x"

/* क्रम messages that are currently off */
#घोषणा BNX2X_MSG_OFF			0x0
#घोषणा BNX2X_MSG_MCP			0x0010000 /* was: NETIF_MSG_HW */
#घोषणा BNX2X_MSG_STATS			0x0020000 /* was: NETIF_MSG_TIMER */
#घोषणा BNX2X_MSG_NVM			0x0040000 /* was: NETIF_MSG_HW */
#घोषणा BNX2X_MSG_DMAE			0x0080000 /* was: NETIF_MSG_HW */
#घोषणा BNX2X_MSG_SP			0x0100000 /* was: NETIF_MSG_INTR */
#घोषणा BNX2X_MSG_FP			0x0200000 /* was: NETIF_MSG_INTR */
#घोषणा BNX2X_MSG_IOV			0x0800000
#घोषणा BNX2X_MSG_PTP			0x1000000
#घोषणा BNX2X_MSG_IDLE			0x2000000 /* used क्रम idle check*/
#घोषणा BNX2X_MSG_ETHTOOL		0x4000000
#घोषणा BNX2X_MSG_DCB			0x8000000

/* regular debug prपूर्णांक */
#घोषणा DP_INNER(fmt, ...)					\
	pr_notice("[%s:%d(%s)]" fmt,				\
		  __func__, __LINE__,				\
		  bp->dev ? (bp->dev->name) : "?",		\
		  ##__VA_ARGS__);

#घोषणा DP(__mask, fmt, ...)					\
करो अणु								\
	अगर (unlikely(bp->msg_enable & (__mask)))		\
		DP_INNER(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा DP_AND(__mask, fmt, ...)				\
करो अणु								\
	अगर (unlikely((bp->msg_enable & (__mask)) == __mask))	\
		DP_INNER(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा DP_CONT(__mask, fmt, ...)				\
करो अणु								\
	अगर (unlikely(bp->msg_enable & (__mask)))		\
		pr_cont(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

/* errors debug prपूर्णांक */
#घोषणा BNX2X_DBG_ERR(fmt, ...)					\
करो अणु								\
	अगर (unlikely(netअगर_msg_probe(bp)))			\
		pr_err("[%s:%d(%s)]" fmt,			\
		       __func__, __LINE__,			\
		       bp->dev ? (bp->dev->name) : "?",		\
		       ##__VA_ARGS__);				\
पूर्ण जबतक (0)

/* क्रम errors (never masked) */
#घोषणा BNX2X_ERR(fmt, ...)					\
करो अणु								\
	pr_err("[%s:%d(%s)]" fmt,				\
	       __func__, __LINE__,				\
	       bp->dev ? (bp->dev->name) : "?",			\
	       ##__VA_ARGS__);					\
पूर्ण जबतक (0)

#घोषणा BNX2X_ERROR(fmt, ...)					\
	pr_err("[%s:%d]" fmt, __func__, __LINE__, ##__VA_ARGS__)

/* beक्रमe we have a dev->name use dev_info() */
#घोषणा BNX2X_DEV_INFO(fmt, ...)				 \
करो अणु								 \
	अगर (unlikely(netअगर_msg_probe(bp)))			 \
		dev_info(&bp->pdev->dev, fmt, ##__VA_ARGS__);	 \
पूर्ण जबतक (0)

/* Error handling */
व्योम bnx2x_panic_dump(काष्ठा bnx2x *bp, bool disable_पूर्णांक);
#अगर_घोषित BNX2X_STOP_ON_ERROR
#घोषणा bnx2x_panic()				\
करो अणु						\
	bp->panic = 1;				\
	BNX2X_ERR("driver assert\n");		\
	bnx2x_panic_dump(bp, true);		\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा bnx2x_panic()				\
करो अणु						\
	bp->panic = 1;				\
	BNX2X_ERR("driver assert\n");		\
	bnx2x_panic_dump(bp, false);		\
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा bnx2x_mc_addr(ha)      ((ha)->addr)
#घोषणा bnx2x_uc_addr(ha)      ((ha)->addr)

#घोषणा U64_LO(x)			((u32)(((u64)(x)) & 0xffffffff))
#घोषणा U64_HI(x)			((u32)(((u64)(x)) >> 32))
#घोषणा HILO_U64(hi, lo)		((((u64)(hi)) << 32) + (lo))

#घोषणा REG_ADDR(bp, offset)		((bp->regview) + (offset))

#घोषणा REG_RD(bp, offset)		पढ़ोl(REG_ADDR(bp, offset))
#घोषणा REG_RD8(bp, offset)		पढ़ोb(REG_ADDR(bp, offset))
#घोषणा REG_RD16(bp, offset)		पढ़ोw(REG_ADDR(bp, offset))

#घोषणा REG_WR_RELAXED(bp, offset, val)	\
	ग_लिखोl_relaxed((u32)val, REG_ADDR(bp, offset))

#घोषणा REG_WR16_RELAXED(bp, offset, val) \
	ग_लिखोw_relaxed((u16)val, REG_ADDR(bp, offset))

#घोषणा REG_WR(bp, offset, val)		ग_लिखोl((u32)val, REG_ADDR(bp, offset))
#घोषणा REG_WR8(bp, offset, val)	ग_लिखोb((u8)val, REG_ADDR(bp, offset))
#घोषणा REG_WR16(bp, offset, val)	ग_लिखोw((u16)val, REG_ADDR(bp, offset))

#घोषणा REG_RD_IND(bp, offset)		bnx2x_reg_rd_ind(bp, offset)
#घोषणा REG_WR_IND(bp, offset, val)	bnx2x_reg_wr_ind(bp, offset, val)

#घोषणा REG_RD_DMAE(bp, offset, valp, len32) \
	करो अणु \
		bnx2x_पढ़ो_dmae(bp, offset, len32);\
		स_नकल(valp, bnx2x_sp(bp, wb_data[0]), (len32) * 4); \
	पूर्ण जबतक (0)

#घोषणा REG_WR_DMAE(bp, offset, valp, len32) \
	करो अणु \
		स_नकल(bnx2x_sp(bp, wb_data[0]), valp, (len32) * 4); \
		bnx2x_ग_लिखो_dmae(bp, bnx2x_sp_mapping(bp, wb_data), \
				 offset, len32); \
	पूर्ण जबतक (0)

#घोषणा REG_WR_DMAE_LEN(bp, offset, valp, len32) \
	REG_WR_DMAE(bp, offset, valp, len32)

#घोषणा VIRT_WR_DMAE_LEN(bp, data, addr, len32, le32_swap) \
	करो अणु \
		स_नकल(GUNZIP_BUF(bp), data, (len32) * 4); \
		bnx2x_ग_लिखो_big_buf_wb(bp, addr, len32); \
	पूर्ण जबतक (0)

#घोषणा SHMEM_ADDR(bp, field)		(bp->common.shmem_base + \
					 दुरत्व(काष्ठा shmem_region, field))
#घोषणा SHMEM_RD(bp, field)		REG_RD(bp, SHMEM_ADDR(bp, field))
#घोषणा SHMEM_WR(bp, field, val)	REG_WR(bp, SHMEM_ADDR(bp, field), val)

#घोषणा SHMEM2_ADDR(bp, field)		(bp->common.shmem2_base + \
					 दुरत्व(काष्ठा shmem2_region, field))
#घोषणा SHMEM2_RD(bp, field)		REG_RD(bp, SHMEM2_ADDR(bp, field))
#घोषणा SHMEM2_WR(bp, field, val)	REG_WR(bp, SHMEM2_ADDR(bp, field), val)
#घोषणा MF_CFG_ADDR(bp, field)		(bp->common.mf_cfg_base + \
					 दुरत्व(काष्ठा mf_cfg, field))
#घोषणा MF2_CFG_ADDR(bp, field)		(bp->common.mf2_cfg_base + \
					 दुरत्व(काष्ठा mf2_cfg, field))

#घोषणा MF_CFG_RD(bp, field)		REG_RD(bp, MF_CFG_ADDR(bp, field))
#घोषणा MF_CFG_WR(bp, field, val)	REG_WR(bp,\
					       MF_CFG_ADDR(bp, field), (val))
#घोषणा MF2_CFG_RD(bp, field)		REG_RD(bp, MF2_CFG_ADDR(bp, field))

#घोषणा SHMEM2_HAS(bp, field)		((bp)->common.shmem2_base &&	\
					 (SHMEM2_RD((bp), size) >	\
					 दुरत्व(काष्ठा shmem2_region, field)))

#घोषणा EMAC_RD(bp, reg)		REG_RD(bp, emac_base + reg)
#घोषणा EMAC_WR(bp, reg, val)		REG_WR(bp, emac_base + reg, val)

/* SP SB indices */

/* General SP events - stats query, cfc delete, etc  */
#घोषणा HC_SP_INDEX_ETH_DEF_CONS		3

/* EQ completions */
#घोषणा HC_SP_INDEX_EQ_CONS			7

/* FCoE L2 connection completions */
#घोषणा HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS		6
#घोषणा HC_SP_INDEX_ETH_FCOE_RX_CQ_CONS		4
/* iSCSI L2 */
#घोषणा HC_SP_INDEX_ETH_ISCSI_CQ_CONS		5
#घोषणा HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS	1

/* Special clients parameters */

/* SB indices */
/* FCoE L2 */
#घोषणा BNX2X_FCOE_L2_RX_INDEX \
	(&bp->def_status_blk->sp_sb.\
	index_values[HC_SP_INDEX_ETH_FCOE_RX_CQ_CONS])

#घोषणा BNX2X_FCOE_L2_TX_INDEX \
	(&bp->def_status_blk->sp_sb.\
	index_values[HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS])

/**
 *  CIDs and CLIDs:
 *  CLIDs below is a CLID क्रम func 0, then the CLID क्रम other
 *  functions will be calculated by the क्रमmula:
 *
 *  FUNC_N_CLID_X = N * NUM_SPECIAL_CLIENTS + FUNC_0_CLID_X
 *
 */
क्रमागत अणु
	BNX2X_ISCSI_ETH_CL_ID_IDX,
	BNX2X_FCOE_ETH_CL_ID_IDX,
	BNX2X_MAX_CNIC_ETH_CL_ID_IDX,
पूर्ण;

/* use a value high enough to be above all the PFs, which has least signअगरicant
 * nibble as 8, so when cnic needs to come up with a CID क्रम UIO to use to
 * calculate करोorbell address according to old करोorbell configuration scheme
 * (db_msg_sz 1 << 7 * cid + 0x40 DPM offset) it can come up with a valid number
 * We must aव्योम coming up with cid 8 क्रम iscsi since according to this method
 * the designated UIO cid will come out 0 and it has a special handling क्रम that
 * हाल which करोesn't suit us. Thereक्रमe will will cieling to बंदs cid which
 * has least signigअगरcant nibble 8 and अगर it is 8 we will move क्रमward to 0x18.
 */

#घोषणा BNX2X_1st_NON_L2_ETH_CID(bp)	(BNX2X_NUM_NON_CNIC_QUEUES(bp) * \
					 (bp)->max_cos)
/* amount of cids traversed by UIO's DPM addition to करोorbell */
#घोषणा UIO_DPM				8
/* roundup to DPM offset */
#घोषणा UIO_ROUNDUP(bp)			(roundup(BNX2X_1st_NON_L2_ETH_CID(bp), \
					 UIO_DPM))
/* offset to nearest value which has lsb nibble matching DPM */
#घोषणा UIO_CID_OFFSET(bp)		((UIO_ROUNDUP(bp) + UIO_DPM) % \
					 (UIO_DPM * 2))
/* add offset to rounded-up cid to get a value which could be used with UIO */
#घोषणा UIO_DPM_ALIGN(bp)		(UIO_ROUNDUP(bp) + UIO_CID_OFFSET(bp))
/* but रुको - aव्योम UIO special हाल क्रम cid 0 */
#घोषणा UIO_DPM_CID0_OFFSET(bp)		((UIO_DPM * 2) * \
					 (UIO_DPM_ALIGN(bp) == UIO_DPM))
/* Properly DPM aligned CID dajusted to cid 0 secal हाल */
#घोषणा BNX2X_CNIC_START_ETH_CID(bp)	(UIO_DPM_ALIGN(bp) + \
					 (UIO_DPM_CID0_OFFSET(bp)))
/* how many cids were wasted  - need this value क्रम cid allocation */
#घोषणा UIO_CID_PAD(bp)			(BNX2X_CNIC_START_ETH_CID(bp) - \
					 BNX2X_1st_NON_L2_ETH_CID(bp))
	/* iSCSI L2 */
#घोषणा	BNX2X_ISCSI_ETH_CID(bp)		(BNX2X_CNIC_START_ETH_CID(bp))
	/* FCoE L2 */
#घोषणा	BNX2X_FCOE_ETH_CID(bp)		(BNX2X_CNIC_START_ETH_CID(bp) + 1)

#घोषणा CNIC_SUPPORT(bp)		((bp)->cnic_support)
#घोषणा CNIC_ENABLED(bp)		((bp)->cnic_enabled)
#घोषणा CNIC_LOADED(bp)			((bp)->cnic_loaded)
#घोषणा FCOE_INIT(bp)			((bp)->fcoe_init)

#घोषणा AEU_IN_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR \
	AEU_INPUTS_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR

#घोषणा SM_RX_ID			0
#घोषणा SM_TX_ID			1

/* defines क्रम multiple tx priority indices */
#घोषणा FIRST_TX_ONLY_COS_INDEX		1
#घोषणा FIRST_TX_COS_INDEX		0

/* rules क्रम calculating the cids of tx-only connections */
#घोषणा CID_TO_FP(cid, bp)		((cid) % BNX2X_NUM_NON_CNIC_QUEUES(bp))
#घोषणा CID_COS_TO_TX_ONLY_CID(cid, cos, bp) \
				(cid + cos * BNX2X_NUM_NON_CNIC_QUEUES(bp))

/* fp index inside class of service range */
#घोषणा FP_COS_TO_TXQ(fp, cos, bp) \
			((fp)->index + cos * BNX2X_NUM_NON_CNIC_QUEUES(bp))

/* Indexes क्रम transmission queues array:
 * txdata क्रम RSS i CoS j is at location i + (j * num of RSS)
 * txdata क्रम FCoE (अगर exist) is at location max cos * num of RSS
 * txdata क्रम FWD (अगर exist) is one location after FCoE
 * txdata क्रम OOO (अगर exist) is one location after FWD
 */
क्रमागत अणु
	FCOE_TXQ_IDX_OFFSET,
	FWD_TXQ_IDX_OFFSET,
	OOO_TXQ_IDX_OFFSET,
पूर्ण;
#घोषणा MAX_ETH_TXQ_IDX(bp)	(BNX2X_NUM_NON_CNIC_QUEUES(bp) * (bp)->max_cos)
#घोषणा FCOE_TXQ_IDX(bp)	(MAX_ETH_TXQ_IDX(bp) + FCOE_TXQ_IDX_OFFSET)

/* fast path */
/*
 * This driver uses new build_skb() API :
 * RX ring buffer contains poपूर्णांकer to kदो_स्मृति() data only,
 * skb are built only after Hardware filled the frame.
 */
काष्ठा sw_rx_bd अणु
	u8		*data;
	DEFINE_DMA_UNMAP_ADDR(mapping);
पूर्ण;

काष्ठा sw_tx_bd अणु
	काष्ठा sk_buff	*skb;
	u16		first_bd;
	u8		flags;
/* Set on the first BD descriptor when there is a split BD */
#घोषणा BNX2X_TSO_SPLIT_BD		(1<<0)
#घोषणा BNX2X_HAS_SECOND_PBD		(1<<1)
पूर्ण;

काष्ठा sw_rx_page अणु
	काष्ठा page	*page;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	अचिन्हित पूर्णांक	offset;
पूर्ण;

जोड़ db_prod अणु
	काष्ठा करोorbell_set_prod data;
	u32		raw;
पूर्ण;

/* dropless fc FW/HW related params */
#घोषणा BRB_SIZE(bp)		(CHIP_IS_E3(bp) ? 1024 : 512)
#घोषणा MAX_AGG_QS(bp)		(CHIP_IS_E1(bp) ? \
					ETH_MAX_AGGREGATION_QUEUES_E1 :\
					ETH_MAX_AGGREGATION_QUEUES_E1H_E2)
#घोषणा FW_DROP_LEVEL(bp)	(3 + MAX_SPQ_PENDING + MAX_AGG_QS(bp))
#घोषणा FW_PREFETCH_CNT		16
#घोषणा DROPLESS_FC_HEADROOM	100

/* MC hsi */
#घोषणा BCM_PAGE_SHIFT		12
#घोषणा BCM_PAGE_SIZE		(1 << BCM_PAGE_SHIFT)
#घोषणा BCM_PAGE_MASK		(~(BCM_PAGE_SIZE - 1))
#घोषणा BCM_PAGE_ALIGN(addr)	(((addr) + BCM_PAGE_SIZE - 1) & BCM_PAGE_MASK)

#घोषणा PAGES_PER_SGE_SHIFT	0
#घोषणा PAGES_PER_SGE		(1 << PAGES_PER_SGE_SHIFT)
#घोषणा SGE_PAGE_SHIFT		12
#घोषणा SGE_PAGE_SIZE		(1 << SGE_PAGE_SHIFT)
#घोषणा SGE_PAGE_MASK		(~(SGE_PAGE_SIZE - 1))
#घोषणा SGE_PAGE_ALIGN(addr)	(((addr) + SGE_PAGE_SIZE - 1) & SGE_PAGE_MASK)
#घोषणा SGE_PAGES		(SGE_PAGE_SIZE * PAGES_PER_SGE)
#घोषणा TPA_AGG_SIZE		min_t(u32, (min_t(u32, 8, MAX_SKB_FRAGS) * \
					    SGE_PAGES), 0xffff)

/* SGE ring related macros */
#घोषणा NUM_RX_SGE_PAGES	2
#घोषणा RX_SGE_CNT		(BCM_PAGE_SIZE / माप(काष्ठा eth_rx_sge))
#घोषणा NEXT_PAGE_SGE_DESC_CNT	2
#घोषणा MAX_RX_SGE_CNT		(RX_SGE_CNT - NEXT_PAGE_SGE_DESC_CNT)
/* RX_SGE_CNT is promised to be a घातer of 2 */
#घोषणा RX_SGE_MASK		(RX_SGE_CNT - 1)
#घोषणा NUM_RX_SGE		(RX_SGE_CNT * NUM_RX_SGE_PAGES)
#घोषणा MAX_RX_SGE		(NUM_RX_SGE - 1)
#घोषणा NEXT_SGE_IDX(x)		((((x) & RX_SGE_MASK) == \
				  (MAX_RX_SGE_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_SGE_DESC_CNT : \
					(x) + 1)
#घोषणा RX_SGE(x)		((x) & MAX_RX_SGE)

/*
 * Number of required  SGEs is the sum of two:
 * 1. Number of possible खोलोed aggregations (next packet क्रम
 *    these aggregations will probably consume SGE immediately)
 * 2. Rest of BRB blocks भागided by 2 (block will consume new SGE only
 *    after placement on BD क्रम new TPA aggregation)
 *
 * Takes पूर्णांकo account NEXT_PAGE_SGE_DESC_CNT "next" elements on each page
 */
#घोषणा NUM_SGE_REQ		(MAX_AGG_QS(bp) + \
					(BRB_SIZE(bp) - MAX_AGG_QS(bp)) / 2)
#घोषणा NUM_SGE_PG_REQ		((NUM_SGE_REQ + MAX_RX_SGE_CNT - 1) / \
						MAX_RX_SGE_CNT)
#घोषणा SGE_TH_LO(bp)		(NUM_SGE_REQ + \
				 NUM_SGE_PG_REQ * NEXT_PAGE_SGE_DESC_CNT)
#घोषणा SGE_TH_HI(bp)		(SGE_TH_LO(bp) + DROPLESS_FC_HEADROOM)

/* Manipulate a bit vector defined as an array of u64 */

/* Number of bits in one sge_mask array element */
#घोषणा BIT_VEC64_ELEM_SZ		64
#घोषणा BIT_VEC64_ELEM_SHIFT		6
#घोषणा BIT_VEC64_ELEM_MASK		((u64)BIT_VEC64_ELEM_SZ - 1)

#घोषणा __BIT_VEC64_SET_BIT(el, bit) \
	करो अणु \
		el = ((el) | ((u64)0x1 << (bit))); \
	पूर्ण जबतक (0)

#घोषणा __BIT_VEC64_CLEAR_BIT(el, bit) \
	करो अणु \
		el = ((el) & (~((u64)0x1 << (bit)))); \
	पूर्ण जबतक (0)

#घोषणा BIT_VEC64_SET_BIT(vec64, idx) \
	__BIT_VEC64_SET_BIT((vec64)[(idx) >> BIT_VEC64_ELEM_SHIFT], \
			   (idx) & BIT_VEC64_ELEM_MASK)

#घोषणा BIT_VEC64_CLEAR_BIT(vec64, idx) \
	__BIT_VEC64_CLEAR_BIT((vec64)[(idx) >> BIT_VEC64_ELEM_SHIFT], \
			     (idx) & BIT_VEC64_ELEM_MASK)

#घोषणा BIT_VEC64_TEST_BIT(vec64, idx) \
	(((vec64)[(idx) >> BIT_VEC64_ELEM_SHIFT] >> \
	((idx) & BIT_VEC64_ELEM_MASK)) & 0x1)

/* Creates a biपंचांगask of all ones in less signअगरicant bits.
   idx - index of the most signअगरicant bit in the created mask */
#घोषणा BIT_VEC64_ONES_MASK(idx) \
		(((u64)0x1 << (((idx) & BIT_VEC64_ELEM_MASK) + 1)) - 1)
#घोषणा BIT_VEC64_ELEM_ONE_MASK	((u64)(~0))

/*******************************************************/

/* Number of u64 elements in SGE mask array */
#घोषणा RX_SGE_MASK_LEN			(NUM_RX_SGE / BIT_VEC64_ELEM_SZ)
#घोषणा RX_SGE_MASK_LEN_MASK		(RX_SGE_MASK_LEN - 1)
#घोषणा NEXT_SGE_MASK_ELEM(el)		(((el) + 1) & RX_SGE_MASK_LEN_MASK)

जोड़ host_hc_status_block अणु
	/* poपूर्णांकer to fp status block e1x */
	काष्ठा host_hc_status_block_e1x *e1x_sb;
	/* poपूर्णांकer to fp status block e2 */
	काष्ठा host_hc_status_block_e2  *e2_sb;
पूर्ण;

काष्ठा bnx2x_agg_info अणु
	/*
	 * First aggregation buffer is a data buffer, the following - are pages.
	 * We will pपुनः_स्मृतिate the data buffer क्रम each aggregation when
	 * we खोलो the पूर्णांकerface and will replace the BD at the consumer
	 * with this one when we receive the TPA_START CQE in order to
	 * keep the Rx BD ring consistent.
	 */
	काष्ठा sw_rx_bd		first_buf;
	u8			tpa_state;
#घोषणा BNX2X_TPA_START			1
#घोषणा BNX2X_TPA_STOP			2
#घोषणा BNX2X_TPA_ERROR			3
	u8			placement_offset;
	u16			parsing_flags;
	u16			vlan_tag;
	u16			len_on_bd;
	u32			rxhash;
	क्रमागत pkt_hash_types	rxhash_type;
	u16			gro_size;
	u16			full_page;
पूर्ण;

#घोषणा Q_STATS_OFFSET32(stat_name) \
			(दुरत्व(काष्ठा bnx2x_eth_q_stats, stat_name) / 4)

काष्ठा bnx2x_fp_txdata अणु

	काष्ठा sw_tx_bd		*tx_buf_ring;

	जोड़ eth_tx_bd_types	*tx_desc_ring;
	dma_addr_t		tx_desc_mapping;

	u32			cid;

	जोड़ db_prod		tx_db;

	u16			tx_pkt_prod;
	u16			tx_pkt_cons;
	u16			tx_bd_prod;
	u16			tx_bd_cons;

	अचिन्हित दीर्घ		tx_pkt;

	__le16			*tx_cons_sb;

	पूर्णांक			txq_index;
	काष्ठा bnx2x_fastpath	*parent_fp;
	पूर्णांक			tx_ring_size;
पूर्ण;

क्रमागत bnx2x_tpa_mode_t अणु
	TPA_MODE_DISABLED,
	TPA_MODE_LRO,
	TPA_MODE_GRO
पूर्ण;

काष्ठा bnx2x_alloc_pool अणु
	काष्ठा page	*page;
	अचिन्हित पूर्णांक	offset;
पूर्ण;

काष्ठा bnx2x_fastpath अणु
	काष्ठा bnx2x		*bp; /* parent */

	काष्ठा napi_काष्ठा	napi;

	जोड़ host_hc_status_block	status_blk;
	/* chip independent लघुcuts पूर्णांकo sb काष्ठाure */
	__le16			*sb_index_values;
	__le16			*sb_running_index;
	/* chip independent लघुcut पूर्णांकo rx_prods_offset memory */
	u32			ustorm_rx_prods_offset;

	u32			rx_buf_size;
	u32			rx_frag_size; /* 0 अगर kदो_स्मृतिed(), or rx_buf_size + NET_SKB_PAD */
	dma_addr_t		status_blk_mapping;

	क्रमागत bnx2x_tpa_mode_t	mode;

	u8			max_cos; /* actual number of active tx coses */
	काष्ठा bnx2x_fp_txdata	*txdata_ptr[BNX2X_MULTI_TX_COS];

	काष्ठा sw_rx_bd		*rx_buf_ring;	/* BDs mappings ring */
	काष्ठा sw_rx_page	*rx_page_ring;	/* SGE pages mappings ring */

	काष्ठा eth_rx_bd	*rx_desc_ring;
	dma_addr_t		rx_desc_mapping;

	जोड़ eth_rx_cqe	*rx_comp_ring;
	dma_addr_t		rx_comp_mapping;

	/* SGE ring */
	काष्ठा eth_rx_sge	*rx_sge_ring;
	dma_addr_t		rx_sge_mapping;

	u64			sge_mask[RX_SGE_MASK_LEN];

	u32			cid;

	__le16			fp_hc_idx;

	u8			index;		/* number in fp array */
	u8			rx_queue;	/* index क्रम skb_record */
	u8			cl_id;		/* eth client id */
	u8			cl_qzone_id;
	u8			fw_sb_id;	/* status block number in FW */
	u8			igu_sb_id;	/* status block number in HW */

	u16			rx_bd_prod;
	u16			rx_bd_cons;
	u16			rx_comp_prod;
	u16			rx_comp_cons;
	u16			rx_sge_prod;
	/* The last maximal completed SGE */
	u16			last_max_sge;
	__le16			*rx_cons_sb;

	/* TPA related */
	काष्ठा bnx2x_agg_info	*tpa_info;
#अगर_घोषित BNX2X_STOP_ON_ERROR
	u64			tpa_queue_used;
#पूर्ण_अगर
	/* The size is calculated using the following:
	     माप name field from netdev काष्ठाure +
	     4 ('-Xx-' string) +
	     4 (क्रम the digits and to make it DWORD aligned) */
#घोषणा FP_NAME_SIZE		(माप(((काष्ठा net_device *)0)->name) + 8)
	अक्षर			name[FP_NAME_SIZE];

	काष्ठा bnx2x_alloc_pool	page_pool;
पूर्ण;

#घोषणा bnx2x_fp(bp, nr, var)	((bp)->fp[(nr)].var)
#घोषणा bnx2x_sp_obj(bp, fp)	((bp)->sp_objs[(fp)->index])
#घोषणा bnx2x_fp_stats(bp, fp)	(&((bp)->fp_stats[(fp)->index]))
#घोषणा bnx2x_fp_qstats(bp, fp)	(&((bp)->fp_stats[(fp)->index].eth_q_stats))

/* Use 2500 as a mini-jumbo MTU क्रम FCoE */
#घोषणा BNX2X_FCOE_MINI_JUMBO_MTU	2500

#घोषणा	FCOE_IDX_OFFSET		0

#घोषणा FCOE_IDX(bp)		(BNX2X_NUM_NON_CNIC_QUEUES(bp) + \
				 FCOE_IDX_OFFSET)
#घोषणा bnx2x_fcoe_fp(bp)	(&bp->fp[FCOE_IDX(bp)])
#घोषणा bnx2x_fcoe(bp, var)	(bnx2x_fcoe_fp(bp)->var)
#घोषणा bnx2x_fcoe_inner_sp_obj(bp)	(&bp->sp_objs[FCOE_IDX(bp)])
#घोषणा bnx2x_fcoe_sp_obj(bp, var)	(bnx2x_fcoe_inner_sp_obj(bp)->var)
#घोषणा bnx2x_fcoe_tx(bp, var)	(bnx2x_fcoe_fp(bp)-> \
						txdata_ptr[FIRST_TX_COS_INDEX] \
						->var)

#घोषणा IS_ETH_FP(fp)		((fp)->index < BNX2X_NUM_ETH_QUEUES((fp)->bp))
#घोषणा IS_FCOE_FP(fp)		((fp)->index == FCOE_IDX((fp)->bp))
#घोषणा IS_FCOE_IDX(idx)	((idx) == FCOE_IDX(bp))

/* MC hsi */
#घोषणा MAX_FETCH_BD		13	/* HW max BDs per packet */
#घोषणा RX_COPY_THRESH		92

#घोषणा NUM_TX_RINGS		16
#घोषणा TX_DESC_CNT		(BCM_PAGE_SIZE / माप(जोड़ eth_tx_bd_types))
#घोषणा NEXT_PAGE_TX_DESC_CNT	1
#घोषणा MAX_TX_DESC_CNT		(TX_DESC_CNT - NEXT_PAGE_TX_DESC_CNT)
#घोषणा NUM_TX_BD		(TX_DESC_CNT * NUM_TX_RINGS)
#घोषणा MAX_TX_BD		(NUM_TX_BD - 1)
#घोषणा MAX_TX_AVAIL		(MAX_TX_DESC_CNT * NUM_TX_RINGS - 2)
#घोषणा NEXT_TX_IDX(x)		((((x) & MAX_TX_DESC_CNT) == \
				  (MAX_TX_DESC_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_TX_DESC_CNT : \
					(x) + 1)
#घोषणा TX_BD(x)		((x) & MAX_TX_BD)
#घोषणा TX_BD_POFF(x)		((x) & MAX_TX_DESC_CNT)

/* number of NEXT_PAGE descriptors may be required during placement */
#घोषणा NEXT_CNT_PER_TX_PKT(bds)	\
				(((bds) + MAX_TX_DESC_CNT - 1) / \
				 MAX_TX_DESC_CNT * NEXT_PAGE_TX_DESC_CNT)
/* max BDs per tx packet w/o next_pages:
 * START_BD		- describes packed
 * START_BD(splitted)	- includes unpaged data segment क्रम GSO
 * PARSING_BD		- क्रम TSO and CSUM data
 * PARSING_BD2		- क्रम encapsulation data
 * Frag BDs		- describes pages क्रम frags
 */
#घोषणा BDS_PER_TX_PKT		4
#घोषणा MAX_BDS_PER_TX_PKT	(MAX_SKB_FRAGS + BDS_PER_TX_PKT)
/* max BDs per tx packet including next pages */
#घोषणा MAX_DESC_PER_TX_PKT	(MAX_BDS_PER_TX_PKT + \
				 NEXT_CNT_PER_TX_PKT(MAX_BDS_PER_TX_PKT))

/* The RX BD ring is special, each bd is 8 bytes but the last one is 16 */
#घोषणा NUM_RX_RINGS		8
#घोषणा RX_DESC_CNT		(BCM_PAGE_SIZE / माप(काष्ठा eth_rx_bd))
#घोषणा NEXT_PAGE_RX_DESC_CNT	2
#घोषणा MAX_RX_DESC_CNT		(RX_DESC_CNT - NEXT_PAGE_RX_DESC_CNT)
#घोषणा RX_DESC_MASK		(RX_DESC_CNT - 1)
#घोषणा NUM_RX_BD		(RX_DESC_CNT * NUM_RX_RINGS)
#घोषणा MAX_RX_BD		(NUM_RX_BD - 1)
#घोषणा MAX_RX_AVAIL		(MAX_RX_DESC_CNT * NUM_RX_RINGS - 2)

/* dropless fc calculations क्रम BDs
 *
 * Number of BDs should as number of buffers in BRB:
 * Low threshold takes पूर्णांकo account NEXT_PAGE_RX_DESC_CNT
 * "next" elements on each page
 */
#घोषणा NUM_BD_REQ		BRB_SIZE(bp)
#घोषणा NUM_BD_PG_REQ		((NUM_BD_REQ + MAX_RX_DESC_CNT - 1) / \
					      MAX_RX_DESC_CNT)
#घोषणा BD_TH_LO(bp)		(NUM_BD_REQ + \
				 NUM_BD_PG_REQ * NEXT_PAGE_RX_DESC_CNT + \
				 FW_DROP_LEVEL(bp))
#घोषणा BD_TH_HI(bp)		(BD_TH_LO(bp) + DROPLESS_FC_HEADROOM)

#घोषणा MIN_RX_AVAIL		((bp)->dropless_fc ? BD_TH_HI(bp) + 128 : 128)

#घोषणा MIN_RX_SIZE_TPA_HW	(CHIP_IS_E1(bp) ? \
					ETH_MIN_RX_CQES_WITH_TPA_E1 : \
					ETH_MIN_RX_CQES_WITH_TPA_E1H_E2)
#घोषणा MIN_RX_SIZE_NONTPA_HW   ETH_MIN_RX_CQES_WITHOUT_TPA
#घोषणा MIN_RX_SIZE_TPA		(max_t(u32, MIN_RX_SIZE_TPA_HW, MIN_RX_AVAIL))
#घोषणा MIN_RX_SIZE_NONTPA	(max_t(u32, MIN_RX_SIZE_NONTPA_HW,\
								MIN_RX_AVAIL))

#घोषणा NEXT_RX_IDX(x)		((((x) & RX_DESC_MASK) == \
				  (MAX_RX_DESC_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_RX_DESC_CNT : \
					(x) + 1)
#घोषणा RX_BD(x)		((x) & MAX_RX_BD)

/*
 * As दीर्घ as CQE is X बार bigger than BD entry we have to allocate X बार
 * more pages क्रम CQ ring in order to keep it balanced with BD ring
 */
#घोषणा CQE_BD_REL	(माप(जोड़ eth_rx_cqe) / माप(काष्ठा eth_rx_bd))
#घोषणा NUM_RCQ_RINGS		(NUM_RX_RINGS * CQE_BD_REL)
#घोषणा RCQ_DESC_CNT		(BCM_PAGE_SIZE / माप(जोड़ eth_rx_cqe))
#घोषणा NEXT_PAGE_RCQ_DESC_CNT	1
#घोषणा MAX_RCQ_DESC_CNT	(RCQ_DESC_CNT - NEXT_PAGE_RCQ_DESC_CNT)
#घोषणा NUM_RCQ_BD		(RCQ_DESC_CNT * NUM_RCQ_RINGS)
#घोषणा MAX_RCQ_BD		(NUM_RCQ_BD - 1)
#घोषणा MAX_RCQ_AVAIL		(MAX_RCQ_DESC_CNT * NUM_RCQ_RINGS - 2)
#घोषणा NEXT_RCQ_IDX(x)		((((x) & MAX_RCQ_DESC_CNT) == \
				  (MAX_RCQ_DESC_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_RCQ_DESC_CNT : \
					(x) + 1)
#घोषणा RCQ_BD(x)		((x) & MAX_RCQ_BD)

/* dropless fc calculations क्रम RCQs
 *
 * Number of RCQs should be as number of buffers in BRB:
 * Low threshold takes पूर्णांकo account NEXT_PAGE_RCQ_DESC_CNT
 * "next" elements on each page
 */
#घोषणा NUM_RCQ_REQ		BRB_SIZE(bp)
#घोषणा NUM_RCQ_PG_REQ		((NUM_BD_REQ + MAX_RCQ_DESC_CNT - 1) / \
					      MAX_RCQ_DESC_CNT)
#घोषणा RCQ_TH_LO(bp)		(NUM_RCQ_REQ + \
				 NUM_RCQ_PG_REQ * NEXT_PAGE_RCQ_DESC_CNT + \
				 FW_DROP_LEVEL(bp))
#घोषणा RCQ_TH_HI(bp)		(RCQ_TH_LO(bp) + DROPLESS_FC_HEADROOM)

/* This is needed क्रम determining of last_max */
#घोषणा SUB_S16(a, b)		(s16)((s16)(a) - (s16)(b))
#घोषणा SUB_S32(a, b)		(s32)((s32)(a) - (s32)(b))

#घोषणा BNX2X_SWCID_SHIFT	17
#घोषणा BNX2X_SWCID_MASK	((0x1 << BNX2X_SWCID_SHIFT) - 1)

/* used on a CID received from the HW */
#घोषणा SW_CID(x)			(le32_to_cpu(x) & BNX2X_SWCID_MASK)
#घोषणा CQE_CMD(x)			(le32_to_cpu(x) >> \
					COMMON_RAMROD_ETH_RX_CQE_CMD_ID_SHIFT)

#घोषणा BD_UNMAP_ADDR(bd)		HILO_U64(le32_to_cpu((bd)->addr_hi), \
						 le32_to_cpu((bd)->addr_lo))
#घोषणा BD_UNMAP_LEN(bd)		(le16_to_cpu((bd)->nbytes))

#घोषणा BNX2X_DB_MIN_SHIFT		3	/* 8 bytes */
#घोषणा BNX2X_DB_SHIFT			3	/* 8 bytes*/
#अगर (BNX2X_DB_SHIFT < BNX2X_DB_MIN_SHIFT)
#त्रुटि "Min DB doorbell stride is 8"
#पूर्ण_अगर
#घोषणा DOORBELL_RELAXED(bp, cid, val) \
	ग_लिखोl_relaxed((u32)(val), (bp)->करोorbells + ((bp)->db_size * (cid)))

/* TX CSUM helpers */
#घोषणा SKB_CS_OFF(skb)		(दुरत्व(काष्ठा tcphdr, check) - \
				 skb->csum_offset)
#घोषणा SKB_CS(skb)		(*(u16 *)(skb_transport_header(skb) + \
					  skb->csum_offset))

#घोषणा pbd_tcp_flags(tcp_hdr)	(ntohl(tcp_flag_word(tcp_hdr))>>16 & 0xff)

#घोषणा XMIT_PLAIN		0
#घोषणा XMIT_CSUM_V4		(1 << 0)
#घोषणा XMIT_CSUM_V6		(1 << 1)
#घोषणा XMIT_CSUM_TCP		(1 << 2)
#घोषणा XMIT_GSO_V4		(1 << 3)
#घोषणा XMIT_GSO_V6		(1 << 4)
#घोषणा XMIT_CSUM_ENC_V4	(1 << 5)
#घोषणा XMIT_CSUM_ENC_V6	(1 << 6)
#घोषणा XMIT_GSO_ENC_V4		(1 << 7)
#घोषणा XMIT_GSO_ENC_V6		(1 << 8)

#घोषणा XMIT_CSUM_ENC		(XMIT_CSUM_ENC_V4 | XMIT_CSUM_ENC_V6)
#घोषणा XMIT_GSO_ENC		(XMIT_GSO_ENC_V4 | XMIT_GSO_ENC_V6)

#घोषणा XMIT_CSUM		(XMIT_CSUM_V4 | XMIT_CSUM_V6 | XMIT_CSUM_ENC)
#घोषणा XMIT_GSO		(XMIT_GSO_V4 | XMIT_GSO_V6 | XMIT_GSO_ENC)

/* stuff added to make the code fit 80Col */
#घोषणा CQE_TYPE(cqe_fp_flags)	 ((cqe_fp_flags) & ETH_FAST_PATH_RX_CQE_TYPE)
#घोषणा CQE_TYPE_START(cqe_type) ((cqe_type) == RX_ETH_CQE_TYPE_ETH_START_AGG)
#घोषणा CQE_TYPE_STOP(cqe_type)  ((cqe_type) == RX_ETH_CQE_TYPE_ETH_STOP_AGG)
#घोषणा CQE_TYPE_SLOW(cqe_type)  ((cqe_type) == RX_ETH_CQE_TYPE_ETH_RAMROD)
#घोषणा CQE_TYPE_FAST(cqe_type)  ((cqe_type) == RX_ETH_CQE_TYPE_ETH_FASTPATH)

#घोषणा ETH_RX_ERROR_FALGS		ETH_FAST_PATH_RX_CQE_PHY_DECODE_ERR_FLG

#घोषणा BNX2X_PRS_FLAG_OVERETH_IPV4(flags) \
				(((le16_to_cpu(flags) & \
				   PARSING_FLAGS_OVER_ETHERNET_PROTOCOL) >> \
				  PARSING_FLAGS_OVER_ETHERNET_PROTOCOL_SHIFT) \
				 == PRS_FLAG_OVERETH_IPV4)
#घोषणा BNX2X_RX_SUM_FIX(cqe) \
	BNX2X_PRS_FLAG_OVERETH_IPV4(cqe->fast_path_cqe.pars_flags.flags)

#घोषणा FP_USB_FUNC_OFF	\
			दुरत्व(काष्ठा cstorm_status_block_u, func)
#घोषणा FP_CSB_FUNC_OFF	\
			दुरत्व(काष्ठा cstorm_status_block_c, func)

#घोषणा HC_INDEX_ETH_RX_CQ_CONS		1

#घोषणा HC_INDEX_OOO_TX_CQ_CONS		4

#घोषणा HC_INDEX_ETH_TX_CQ_CONS_COS0	5

#घोषणा HC_INDEX_ETH_TX_CQ_CONS_COS1	6

#घोषणा HC_INDEX_ETH_TX_CQ_CONS_COS2	7

#घोषणा HC_INDEX_ETH_FIRST_TX_CQ_CONS	HC_INDEX_ETH_TX_CQ_CONS_COS0

#घोषणा BNX2X_RX_SB_INDEX \
	(&fp->sb_index_values[HC_INDEX_ETH_RX_CQ_CONS])

#घोषणा BNX2X_TX_SB_INDEX_BASE BNX2X_TX_SB_INDEX_COS0

#घोषणा BNX2X_TX_SB_INDEX_COS0 \
	(&fp->sb_index_values[HC_INDEX_ETH_TX_CQ_CONS_COS0])

/* end of fast path */

/* common */

काष्ठा bnx2x_common अणु

	u32			chip_id;
/* chip num:16-31, rev:12-15, metal:4-11, bond_id:0-3 */
#घोषणा CHIP_ID(bp)			(bp->common.chip_id & 0xfffffff0)

#घोषणा CHIP_NUM(bp)			(bp->common.chip_id >> 16)
#घोषणा CHIP_NUM_57710			0x164e
#घोषणा CHIP_NUM_57711			0x164f
#घोषणा CHIP_NUM_57711E			0x1650
#घोषणा CHIP_NUM_57712			0x1662
#घोषणा CHIP_NUM_57712_MF		0x1663
#घोषणा CHIP_NUM_57712_VF		0x166f
#घोषणा CHIP_NUM_57713			0x1651
#घोषणा CHIP_NUM_57713E			0x1652
#घोषणा CHIP_NUM_57800			0x168a
#घोषणा CHIP_NUM_57800_MF		0x16a5
#घोषणा CHIP_NUM_57800_VF		0x16a9
#घोषणा CHIP_NUM_57810			0x168e
#घोषणा CHIP_NUM_57810_MF		0x16ae
#घोषणा CHIP_NUM_57810_VF		0x16af
#घोषणा CHIP_NUM_57811			0x163d
#घोषणा CHIP_NUM_57811_MF		0x163e
#घोषणा CHIP_NUM_57811_VF		0x163f
#घोषणा CHIP_NUM_57840_OBSOLETE		0x168d
#घोषणा CHIP_NUM_57840_MF_OBSOLETE	0x16ab
#घोषणा CHIP_NUM_57840_4_10		0x16a1
#घोषणा CHIP_NUM_57840_2_20		0x16a2
#घोषणा CHIP_NUM_57840_MF		0x16a4
#घोषणा CHIP_NUM_57840_VF		0x16ad
#घोषणा CHIP_IS_E1(bp)			(CHIP_NUM(bp) == CHIP_NUM_57710)
#घोषणा CHIP_IS_57711(bp)		(CHIP_NUM(bp) == CHIP_NUM_57711)
#घोषणा CHIP_IS_57711E(bp)		(CHIP_NUM(bp) == CHIP_NUM_57711E)
#घोषणा CHIP_IS_57712(bp)		(CHIP_NUM(bp) == CHIP_NUM_57712)
#घोषणा CHIP_IS_57712_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57712_VF)
#घोषणा CHIP_IS_57712_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57712_MF)
#घोषणा CHIP_IS_57800(bp)		(CHIP_NUM(bp) == CHIP_NUM_57800)
#घोषणा CHIP_IS_57800_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57800_MF)
#घोषणा CHIP_IS_57800_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57800_VF)
#घोषणा CHIP_IS_57810(bp)		(CHIP_NUM(bp) == CHIP_NUM_57810)
#घोषणा CHIP_IS_57810_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57810_MF)
#घोषणा CHIP_IS_57810_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57810_VF)
#घोषणा CHIP_IS_57811(bp)		(CHIP_NUM(bp) == CHIP_NUM_57811)
#घोषणा CHIP_IS_57811_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57811_MF)
#घोषणा CHIP_IS_57811_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57811_VF)
#घोषणा CHIP_IS_57840(bp)		\
		((CHIP_NUM(bp) == CHIP_NUM_57840_4_10) || \
		 (CHIP_NUM(bp) == CHIP_NUM_57840_2_20) || \
		 (CHIP_NUM(bp) == CHIP_NUM_57840_OBSOLETE))
#घोषणा CHIP_IS_57840_MF(bp)	((CHIP_NUM(bp) == CHIP_NUM_57840_MF) || \
				 (CHIP_NUM(bp) == CHIP_NUM_57840_MF_OBSOLETE))
#घोषणा CHIP_IS_57840_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57840_VF)
#घोषणा CHIP_IS_E1H(bp)			(CHIP_IS_57711(bp) || \
					 CHIP_IS_57711E(bp))
#घोषणा CHIP_IS_57811xx(bp)		(CHIP_IS_57811(bp) || \
					 CHIP_IS_57811_MF(bp) || \
					 CHIP_IS_57811_VF(bp))
#घोषणा CHIP_IS_E2(bp)			(CHIP_IS_57712(bp) || \
					 CHIP_IS_57712_MF(bp) || \
					 CHIP_IS_57712_VF(bp))
#घोषणा CHIP_IS_E3(bp)			(CHIP_IS_57800(bp) || \
					 CHIP_IS_57800_MF(bp) || \
					 CHIP_IS_57800_VF(bp) || \
					 CHIP_IS_57810(bp) || \
					 CHIP_IS_57810_MF(bp) || \
					 CHIP_IS_57810_VF(bp) || \
					 CHIP_IS_57811xx(bp) || \
					 CHIP_IS_57840(bp) || \
					 CHIP_IS_57840_MF(bp) || \
					 CHIP_IS_57840_VF(bp))
#घोषणा CHIP_IS_E1x(bp)			(CHIP_IS_E1((bp)) || CHIP_IS_E1H((bp)))
#घोषणा USES_WARPCORE(bp)		(CHIP_IS_E3(bp))
#घोषणा IS_E1H_OFFSET			(!CHIP_IS_E1(bp))

#घोषणा CHIP_REV_SHIFT			12
#घोषणा CHIP_REV_MASK			(0xF << CHIP_REV_SHIFT)
#घोषणा CHIP_REV_VAL(bp)		(bp->common.chip_id & CHIP_REV_MASK)
#घोषणा CHIP_REV_Ax			(0x0 << CHIP_REV_SHIFT)
#घोषणा CHIP_REV_Bx			(0x1 << CHIP_REV_SHIFT)
/* assume maximum 5 revisions */
#घोषणा CHIP_REV_IS_SLOW(bp)		(CHIP_REV_VAL(bp) > 0x00005000)
/* Emul versions are A=>0xe, B=>0xc, C=>0xa, D=>8, E=>6 */
#घोषणा CHIP_REV_IS_EMUL(bp)		((CHIP_REV_IS_SLOW(bp)) && \
					 !(CHIP_REV_VAL(bp) & 0x00001000))
/* FPGA versions are A=>0xf, B=>0xd, C=>0xb, D=>9, E=>7 */
#घोषणा CHIP_REV_IS_FPGA(bp)		((CHIP_REV_IS_SLOW(bp)) && \
					 (CHIP_REV_VAL(bp) & 0x00001000))

#घोषणा CHIP_TIME(bp)			((CHIP_REV_IS_EMUL(bp)) ? 2000 : \
					((CHIP_REV_IS_FPGA(bp)) ? 200 : 1))

#घोषणा CHIP_METAL(bp)			(bp->common.chip_id & 0x00000ff0)
#घोषणा CHIP_BOND_ID(bp)		(bp->common.chip_id & 0x0000000f)
#घोषणा CHIP_REV_SIM(bp)		(((CHIP_REV_MASK - CHIP_REV_VAL(bp)) >>\
					   (CHIP_REV_SHIFT + 1)) \
						<< CHIP_REV_SHIFT)
#घोषणा CHIP_REV(bp)			(CHIP_REV_IS_SLOW(bp) ? \
						CHIP_REV_SIM(bp) :\
						CHIP_REV_VAL(bp))
#घोषणा CHIP_IS_E3B0(bp)		(CHIP_IS_E3(bp) && \
					 (CHIP_REV(bp) == CHIP_REV_Bx))
#घोषणा CHIP_IS_E3A0(bp)		(CHIP_IS_E3(bp) && \
					 (CHIP_REV(bp) == CHIP_REV_Ax))
/* This define is used in two मुख्य places:
 * 1. In the early stages of nic_load, to know अगर to configure Parser / Searcher
 * to nic-only mode or to offload mode. Offload mode is configured अगर either the
 * chip is E1x (where MIC_MODE रेजिस्टर is not applicable), or अगर cnic alपढ़ोy
 * रेजिस्टरed क्रम this port (which means that the user wants storage services).
 * 2. During cnic-related load, to know अगर offload mode is alपढ़ोy configured in
 * the HW or needs to be configured.
 * Since the transition from nic-mode to offload-mode in HW causes traffic
 * corruption, nic-mode is configured only in ports on which storage services
 * where never requested.
 */
#घोषणा CONFIGURE_NIC_MODE(bp)		(!CHIP_IS_E1x(bp) && !CNIC_ENABLED(bp))

	पूर्णांक			flash_size;
#घोषणा BNX2X_NVRAM_1MB_SIZE			0x20000	/* 1M bit in bytes */
#घोषणा BNX2X_NVRAM_TIMEOUT_COUNT		30000
#घोषणा BNX2X_NVRAM_PAGE_SIZE			256

	u32			shmem_base;
	u32			shmem2_base;
	u32			mf_cfg_base;
	u32			mf2_cfg_base;

	u32			hw_config;

	u32			bc_ver;

	u8			पूर्णांक_block;
#घोषणा INT_BLOCK_HC			0
#घोषणा INT_BLOCK_IGU			1
#घोषणा INT_BLOCK_MODE_NORMAL		0
#घोषणा INT_BLOCK_MODE_BW_COMP		2
#घोषणा CHIP_INT_MODE_IS_NBC(bp)		\
			(!CHIP_IS_E1x(bp) &&	\
			!((bp)->common.पूर्णांक_block & INT_BLOCK_MODE_BW_COMP))
#घोषणा CHIP_INT_MODE_IS_BC(bp) (!CHIP_INT_MODE_IS_NBC(bp))

	u8			chip_port_mode;
#घोषणा CHIP_4_PORT_MODE			0x0
#घोषणा CHIP_2_PORT_MODE			0x1
#घोषणा CHIP_PORT_MODE_NONE			0x2
#घोषणा CHIP_MODE(bp)			(bp->common.chip_port_mode)
#घोषणा CHIP_MODE_IS_4_PORT(bp) (CHIP_MODE(bp) == CHIP_4_PORT_MODE)

	u32			boot_mode;
पूर्ण;

/* IGU MSIX STATISTICS on 57712: 64 क्रम VFs; 4 क्रम PFs; 4 क्रम Attentions */
#घोषणा BNX2X_IGU_STAS_MSG_VF_CNT 64
#घोषणा BNX2X_IGU_STAS_MSG_PF_CNT 4

#घोषणा MAX_IGU_ATTN_ACK_TO       100
/* end of common */

/* port */

काष्ठा bnx2x_port अणु
	u32			pmf;

	u32			link_config[LINK_CONFIG_SIZE];

	u32			supported[LINK_CONFIG_SIZE];

	u32			advertising[LINK_CONFIG_SIZE];

	u32			phy_addr;

	/* used to synchronize phy accesses */
	काष्ठा mutex		phy_mutex;

	u32			port_stx;

	काष्ठा nig_stats	old_nig_stats;
पूर्ण;

/* end of port */

#घोषणा STATS_OFFSET32(stat_name) \
			(दुरत्व(काष्ठा bnx2x_eth_stats, stat_name) / 4)

/* slow path */
#घोषणा BNX2X_MAX_NUM_OF_VFS	64
#घोषणा BNX2X_VF_CID_WND	4 /* log num of queues per VF. HW config. */
#घोषणा BNX2X_CIDS_PER_VF	(1 << BNX2X_VF_CID_WND)

/* We need to reserve करोorbell addresses क्रम all VF and queue combinations */
#घोषणा BNX2X_VF_CIDS		(BNX2X_MAX_NUM_OF_VFS * BNX2X_CIDS_PER_VF)

/* The करोorbell is configured to have the same number of CIDs क्रम PFs and क्रम
 * VFs. For this reason the PF CID zone is as large as the VF zone.
 */
#घोषणा BNX2X_FIRST_VF_CID	BNX2X_VF_CIDS
#घोषणा BNX2X_MAX_NUM_VF_QUEUES	64
#घोषणा BNX2X_VF_ID_INVALID	0xFF

/* the number of VF CIDS multiplied by the amount of bytes reserved क्रम each
 * cid must not exceed the size of the VF करोorbell
 */
#घोषणा BNX2X_VF_BAR_SIZE	512
#अगर (BNX2X_VF_BAR_SIZE < BNX2X_CIDS_PER_VF * (1 << BNX2X_DB_SHIFT))
#त्रुटि "VF doorbell bar size is 512"
#पूर्ण_अगर

/*
 * The total number of L2 queues, MSIX vectors and HW contexts (CIDs) is
 * control by the number of fast-path status blocks supported by the
 * device (HW/FW). Each fast-path status block (FP-SB) aka non-शेष
 * status block represents an independent पूर्णांकerrupts context that can
 * serve a regular L2 networking queue. However special L2 queues such
 * as the FCoE queue करो not require a FP-SB and other components like
 * the CNIC may consume FP-SB reducing the number of possible L2 queues
 *
 * If the maximum number of FP-SB available is X then:
 * a. If CNIC is supported it consumes 1 FP-SB thus the max number of
 *    regular L2 queues is Y=X-1
 * b. In MF mode the actual number of L2 queues is Y= (X-1/MF_factor)
 * c. If the FCoE L2 queue is supported the actual number of L2 queues
 *    is Y+1
 * d. The number of irqs (MSIX vectors) is either Y+1 (one extra क्रम
 *    slow-path पूर्णांकerrupts) or Y+2 अगर CNIC is supported (one additional
 *    FP पूर्णांकerrupt context क्रम the CNIC).
 * e. The number of HW context (CID count) is always X or X+1 अगर FCoE
 *    L2 queue is supported. The cid क्रम the FCoE L2 queue is always X.
 */

/* fast-path पूर्णांकerrupt contexts E1x */
#घोषणा FP_SB_MAX_E1x		16
/* fast-path पूर्णांकerrupt contexts E2 */
#घोषणा FP_SB_MAX_E2		HC_SB_MAX_SB_E2

जोड़ cdu_context अणु
	काष्ठा eth_context eth;
	अक्षर pad[1024];
पूर्ण;

/* CDU host DB स्थिरants */
#घोषणा CDU_ILT_PAGE_SZ_HW	2
#घोषणा CDU_ILT_PAGE_SZ		(8192 << CDU_ILT_PAGE_SZ_HW) /* 32K */
#घोषणा ILT_PAGE_CIDS		(CDU_ILT_PAGE_SZ / माप(जोड़ cdu_context))

#घोषणा CNIC_ISCSI_CID_MAX	256
#घोषणा CNIC_FCOE_CID_MAX	2048
#घोषणा CNIC_CID_MAX		(CNIC_ISCSI_CID_MAX + CNIC_FCOE_CID_MAX)
#घोषणा CNIC_ILT_LINES		DIV_ROUND_UP(CNIC_CID_MAX, ILT_PAGE_CIDS)

#घोषणा QM_ILT_PAGE_SZ_HW	0
#घोषणा QM_ILT_PAGE_SZ		(4096 << QM_ILT_PAGE_SZ_HW) /* 4K */
#घोषणा QM_CID_ROUND		1024

/* TM (समयrs) host DB स्थिरants */
#घोषणा TM_ILT_PAGE_SZ_HW	0
#घोषणा TM_ILT_PAGE_SZ		(4096 << TM_ILT_PAGE_SZ_HW) /* 4K */
#घोषणा TM_CONN_NUM		(BNX2X_FIRST_VF_CID + \
				 BNX2X_VF_CIDS + \
				 CNIC_ISCSI_CID_MAX)
#घोषणा TM_ILT_SZ		(8 * TM_CONN_NUM)
#घोषणा TM_ILT_LINES		DIV_ROUND_UP(TM_ILT_SZ, TM_ILT_PAGE_SZ)

/* SRC (Searcher) host DB स्थिरants */
#घोषणा SRC_ILT_PAGE_SZ_HW	0
#घोषणा SRC_ILT_PAGE_SZ		(4096 << SRC_ILT_PAGE_SZ_HW) /* 4K */
#घोषणा SRC_HASH_BITS		10
#घोषणा SRC_CONN_NUM		(1 << SRC_HASH_BITS) /* 1024 */
#घोषणा SRC_ILT_SZ		(माप(काष्ठा src_ent) * SRC_CONN_NUM)
#घोषणा SRC_T2_SZ		SRC_ILT_SZ
#घोषणा SRC_ILT_LINES		DIV_ROUND_UP(SRC_ILT_SZ, SRC_ILT_PAGE_SZ)

#घोषणा MAX_DMAE_C		8

/* DMA memory not used in fastpath */
काष्ठा bnx2x_slowpath अणु
	जोड़ अणु
		काष्ठा mac_configuration_cmd		e1x;
		काष्ठा eth_classअगरy_rules_ramrod_data	e2;
	पूर्ण mac_rdata;

	जोड़ अणु
		काष्ठा eth_classअगरy_rules_ramrod_data	e2;
	पूर्ण vlan_rdata;

	जोड़ अणु
		काष्ठा tstorm_eth_mac_filter_config	e1x;
		काष्ठा eth_filter_rules_ramrod_data	e2;
	पूर्ण rx_mode_rdata;

	जोड़ अणु
		काष्ठा mac_configuration_cmd		e1;
		काष्ठा eth_multicast_rules_ramrod_data  e2;
	पूर्ण mcast_rdata;

	काष्ठा eth_rss_update_ramrod_data	rss_rdata;

	/* Queue State related ramrods are always sent under rtnl_lock */
	जोड़ अणु
		काष्ठा client_init_ramrod_data  init_data;
		काष्ठा client_update_ramrod_data update_data;
		काष्ठा tpa_update_ramrod_data tpa_data;
	पूर्ण q_rdata;

	जोड़ अणु
		काष्ठा function_start_data	func_start;
		/* pfc configuration क्रम DCBX ramrod */
		काष्ठा flow_control_configuration pfc_config;
	पूर्ण func_rdata;

	/* afex ramrod can not be a part of func_rdata जोड़ because these
	 * events might arrive in parallel to other events from func_rdata.
	 * Thereक्रमe, अगर they would have been defined in the same जोड़,
	 * data can get corrupted.
	 */
	जोड़ अणु
		काष्ठा afex_vअगर_list_ramrod_data	vअगरlist_data;
		काष्ठा function_update_data		func_update;
	पूर्ण func_afex_rdata;

	/* used by dmae command executer */
	काष्ठा dmae_command		dmae[MAX_DMAE_C];

	u32				stats_comp;
	जोड़ mac_stats			mac_stats;
	काष्ठा nig_stats		nig_stats;
	काष्ठा host_port_stats		port_stats;
	काष्ठा host_func_stats		func_stats;

	u32				wb_comp;
	u32				wb_data[4];

	जोड़ drv_info_to_mcp		drv_info_to_mcp;
पूर्ण;

#घोषणा bnx2x_sp(bp, var)		(&bp->slowpath->var)
#घोषणा bnx2x_sp_mapping(bp, var) \
		(bp->slowpath_mapping + दुरत्व(काष्ठा bnx2x_slowpath, var))

/* attn group wiring */
#घोषणा MAX_DYNAMIC_ATTN_GRPS		8

काष्ठा attn_route अणु
	u32 sig[5];
पूर्ण;

काष्ठा iro अणु
	u32 base;
	u16 m1;
	u16 m2;
	u16 m3;
	u16 size;
पूर्ण;

काष्ठा hw_context अणु
	जोड़ cdu_context *vcxt;
	dma_addr_t cxt_mapping;
	माप_प्रकार size;
पूर्ण;

/* क्रमward */
काष्ठा bnx2x_ilt;

काष्ठा bnx2x_vfdb;

क्रमागत bnx2x_recovery_state अणु
	BNX2X_RECOVERY_DONE,
	BNX2X_RECOVERY_INIT,
	BNX2X_RECOVERY_WAIT,
	BNX2X_RECOVERY_FAILED,
	BNX2X_RECOVERY_NIC_LOADING
पूर्ण;

/*
 * Event queue (EQ or event ring) MC hsi
 * NUM_EQ_PAGES and EQ_DESC_CNT_PAGE must be घातer of 2
 */
#घोषणा NUM_EQ_PAGES		1
#घोषणा EQ_DESC_CNT_PAGE	(BCM_PAGE_SIZE / माप(जोड़ event_ring_elem))
#घोषणा EQ_DESC_MAX_PAGE	(EQ_DESC_CNT_PAGE - 1)
#घोषणा NUM_EQ_DESC		(EQ_DESC_CNT_PAGE * NUM_EQ_PAGES)
#घोषणा EQ_DESC_MASK		(NUM_EQ_DESC - 1)
#घोषणा MAX_EQ_AVAIL		(EQ_DESC_MAX_PAGE * NUM_EQ_PAGES - 2)

/* depends on EQ_DESC_CNT_PAGE being a घातer of 2 */
#घोषणा NEXT_EQ_IDX(x)		((((x) & EQ_DESC_MAX_PAGE) == \
				  (EQ_DESC_MAX_PAGE - 1)) ? (x) + 2 : (x) + 1)

/* depends on the above and on NUM_EQ_PAGES being a घातer of 2 */
#घोषणा EQ_DESC(x)		((x) & EQ_DESC_MASK)

#घोषणा BNX2X_EQ_INDEX \
	(&bp->def_status_blk->sp_sb.\
	index_values[HC_SP_INDEX_EQ_CONS])

/* This is a data that will be used to create a link report message.
 * We will keep the data used क्रम the last link report in order
 * to prevent reporting the same link parameters twice.
 */
काष्ठा bnx2x_link_report_data अणु
	u16 line_speed;			/* Effective line speed */
	अचिन्हित दीर्घ link_report_flags;/* BNX2X_LINK_REPORT_XXX flags */
पूर्ण;

क्रमागत अणु
	BNX2X_LINK_REPORT_FD,		/* Full DUPLEX */
	BNX2X_LINK_REPORT_LINK_DOWN,
	BNX2X_LINK_REPORT_RX_FC_ON,
	BNX2X_LINK_REPORT_TX_FC_ON,
पूर्ण;

क्रमागत अणु
	BNX2X_PORT_QUERY_IDX,
	BNX2X_PF_QUERY_IDX,
	BNX2X_FCOE_QUERY_IDX,
	BNX2X_FIRST_QUEUE_QUERY_IDX,
पूर्ण;

काष्ठा bnx2x_fw_stats_req अणु
	काष्ठा stats_query_header hdr;
	काष्ठा stats_query_entry query[FP_SB_MAX_E1x+
		BNX2X_FIRST_QUEUE_QUERY_IDX];
पूर्ण;

काष्ठा bnx2x_fw_stats_data अणु
	काष्ठा stats_counter		storm_counters;
	काष्ठा per_port_stats		port;
	काष्ठा per_pf_stats		pf;
	काष्ठा fcoe_statistics_params	fcoe;
	काष्ठा per_queue_stats		queue_stats[1];
पूर्ण;

/* Public slow path states */
क्रमागत sp_rtnl_flag अणु
	BNX2X_SP_RTNL_SETUP_TC,
	BNX2X_SP_RTNL_TX_TIMEOUT,
	BNX2X_SP_RTNL_FAN_FAILURE,
	BNX2X_SP_RTNL_AFEX_F_UPDATE,
	BNX2X_SP_RTNL_ENABLE_SRIOV,
	BNX2X_SP_RTNL_VFPF_MCAST,
	BNX2X_SP_RTNL_VFPF_CHANNEL_DOWN,
	BNX2X_SP_RTNL_RX_MODE,
	BNX2X_SP_RTNL_HYPERVISOR_VLAN,
	BNX2X_SP_RTNL_TX_STOP,
	BNX2X_SP_RTNL_GET_DRV_VERSION,
	BNX2X_SP_RTNL_UPDATE_SVID,
पूर्ण;

क्रमागत bnx2x_iov_flag अणु
	BNX2X_IOV_HANDLE_VF_MSG,
	BNX2X_IOV_HANDLE_FLR,
पूर्ण;

काष्ठा bnx2x_prev_path_list अणु
	काष्ठा list_head list;
	u8 bus;
	u8 slot;
	u8 path;
	u8 aer;
	u8 undi;
पूर्ण;

काष्ठा bnx2x_sp_objs अणु
	/* MACs object */
	काष्ठा bnx2x_vlan_mac_obj mac_obj;

	/* Queue State object */
	काष्ठा bnx2x_queue_sp_obj q_obj;

	/* VLANs object */
	काष्ठा bnx2x_vlan_mac_obj vlan_obj;
पूर्ण;

काष्ठा bnx2x_fp_stats अणु
	काष्ठा tstorm_per_queue_stats old_tclient;
	काष्ठा ustorm_per_queue_stats old_uclient;
	काष्ठा xstorm_per_queue_stats old_xclient;
	काष्ठा bnx2x_eth_q_stats eth_q_stats;
	काष्ठा bnx2x_eth_q_stats_old eth_q_stats_old;
पूर्ण;

क्रमागत अणु
	SUB_MF_MODE_UNKNOWN = 0,
	SUB_MF_MODE_UFP,
	SUB_MF_MODE_NPAR1_DOT_5,
	SUB_MF_MODE_BD,
पूर्ण;

काष्ठा bnx2x_vlan_entry अणु
	काष्ठा list_head link;
	u16 vid;
	bool hw;
पूर्ण;

क्रमागत bnx2x_udp_port_type अणु
	BNX2X_UDP_PORT_VXLAN,
	BNX2X_UDP_PORT_GENEVE,
	BNX2X_UDP_PORT_MAX,
पूर्ण;

काष्ठा bnx2x अणु
	/* Fields used in the tx and पूर्णांकr/napi perक्रमmance paths
	 * are grouped together in the beginning of the काष्ठाure
	 */
	काष्ठा bnx2x_fastpath	*fp;
	काष्ठा bnx2x_sp_objs	*sp_objs;
	काष्ठा bnx2x_fp_stats	*fp_stats;
	काष्ठा bnx2x_fp_txdata	*bnx2x_txq;
	व्योम __iomem		*regview;
	व्योम __iomem		*करोorbells;
	u16			db_size;

	u8			pf_num;	/* असलolute PF number */
	u8			pfid;	/* per-path PF number */
	पूर्णांक			base_fw_ndsb; /**/
#घोषणा BP_PATH(bp)			(CHIP_IS_E1x(bp) ? 0 : (bp->pf_num & 1))
#घोषणा BP_PORT(bp)			(bp->pfid & 1)
#घोषणा BP_FUNC(bp)			(bp->pfid)
#घोषणा BP_ABS_FUNC(bp)			(bp->pf_num)
#घोषणा BP_VN(bp)			((bp)->pfid >> 1)
#घोषणा BP_MAX_VN_NUM(bp)		(CHIP_MODE_IS_4_PORT(bp) ? 2 : 4)
#घोषणा BP_L_ID(bp)			(BP_VN(bp) << 2)
#घोषणा BP_FW_MB_IDX_VN(bp, vn)		(BP_PORT(bp) +\
	  (vn) * ((CHIP_IS_E1x(bp) || (CHIP_MODE_IS_4_PORT(bp))) ? 2  : 1))
#घोषणा BP_FW_MB_IDX(bp)		BP_FW_MB_IDX_VN(bp, BP_VN(bp))

#अगर_घोषित CONFIG_BNX2X_SRIOV
	/* protects vf2pf mailbox from simultaneous access */
	काष्ठा mutex		vf2pf_mutex;
	/* vf pf channel mailbox contains request and response buffers */
	काष्ठा bnx2x_vf_mbx_msg	*vf2pf_mbox;
	dma_addr_t		vf2pf_mbox_mapping;

	/* we set aside a copy of the acquire response */
	काष्ठा pfvf_acquire_resp_tlv acquire_resp;

	/* bulletin board क्रम messages from pf to vf */
	जोड़ pf_vf_bulletin   *pf2vf_bulletin;
	dma_addr_t		pf2vf_bulletin_mapping;

	जोड़ pf_vf_bulletin		shaकरोw_bulletin;
	काष्ठा pf_vf_bulletin_content	old_bulletin;

	u16 requested_nr_virtfn;
#पूर्ण_अगर /* CONFIG_BNX2X_SRIOV */

	काष्ठा net_device	*dev;
	काष्ठा pci_dev		*pdev;

	स्थिर काष्ठा iro	*iro_arr;
#घोषणा IRO (bp->iro_arr)

	क्रमागत bnx2x_recovery_state recovery_state;
	पूर्णांक			is_leader;
	काष्ठा msix_entry	*msix_table;

	पूर्णांक			tx_ring_size;

/* L2 header size + 2*VLANs (8 bytes) + LLC SNAP (8 bytes) */
#घोषणा ETH_OVERHEAD		(ETH_HLEN + 8 + 8)
#घोषणा ETH_MIN_PACKET_SIZE		(ETH_ZLEN - ETH_HLEN)
#घोषणा ETH_MAX_PACKET_SIZE		ETH_DATA_LEN
#घोषणा ETH_MAX_JUMBO_PACKET_SIZE	9600
/* TCP with Timestamp Option (32) + IPv6 (40) */
#घोषणा ETH_MAX_TPA_HEADER_SIZE		72

	/* Max supported alignment is 256 (8 shअगरt)
	 * minimal alignment shअगरt 6 is optimal क्रम 57xxx HW perक्रमmance
	 */
#घोषणा BNX2X_RX_ALIGN_SHIFT		max(6, min(8, L1_CACHE_SHIFT))

	/* FW uses 2 Cache lines Alignment क्रम start packet and size
	 *
	 * We assume skb_build() uses माप(काष्ठा skb_shared_info) bytes
	 * at the end of skb->data, to aव्योम wasting a full cache line.
	 * This reduces memory use (skb->truesize).
	 */
#घोषणा BNX2X_FW_RX_ALIGN_START	(1UL << BNX2X_RX_ALIGN_SHIFT)

#घोषणा BNX2X_FW_RX_ALIGN_END					\
	max_t(u64, 1UL << BNX2X_RX_ALIGN_SHIFT,			\
	    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

#घोषणा BNX2X_PXP_DRAM_ALIGN		(BNX2X_RX_ALIGN_SHIFT - 5)

	काष्ठा host_sp_status_block *def_status_blk;
#घोषणा DEF_SB_IGU_ID			16
#घोषणा DEF_SB_ID			HC_SP_SB_ID
	__le16			def_idx;
	__le16			def_att_idx;
	u32			attn_state;
	काष्ठा attn_route	attn_group[MAX_DYNAMIC_ATTN_GRPS];

	/* slow path ring */
	काष्ठा eth_spe		*spq;
	dma_addr_t		spq_mapping;
	u16			spq_prod_idx;
	काष्ठा eth_spe		*spq_prod_bd;
	काष्ठा eth_spe		*spq_last_bd;
	__le16			*dsb_sp_prod;
	atomic_t		cq_spq_left; /* ETH_XXX ramrods credit */
	/* used to synchronize spq accesses */
	spinlock_t		spq_lock;

	/* event queue */
	जोड़ event_ring_elem	*eq_ring;
	dma_addr_t		eq_mapping;
	u16			eq_prod;
	u16			eq_cons;
	__le16			*eq_cons_sb;
	atomic_t		eq_spq_left; /* COMMON_XXX ramrods credit */

	/* Counter क्रम marking that there is a STAT_QUERY ramrod pending */
	u16			stats_pending;
	/*  Counter क्रम completed statistics ramrods */
	u16			stats_comp;

	/* End of fields used in the perक्रमmance code paths */

	पूर्णांक			panic;
	पूर्णांक			msg_enable;

	u32			flags;
#घोषणा PCIX_FLAG			(1 << 0)
#घोषणा PCI_32BIT_FLAG			(1 << 1)
#घोषणा ONE_PORT_FLAG			(1 << 2)
#घोषणा NO_WOL_FLAG			(1 << 3)
#घोषणा USING_MSIX_FLAG			(1 << 5)
#घोषणा USING_MSI_FLAG			(1 << 6)
#घोषणा DISABLE_MSI_FLAG		(1 << 7)
#घोषणा NO_MCP_FLAG			(1 << 9)
#घोषणा MF_FUNC_DIS			(1 << 11)
#घोषणा OWN_CNIC_IRQ			(1 << 12)
#घोषणा NO_ISCSI_OOO_FLAG		(1 << 13)
#घोषणा NO_ISCSI_FLAG			(1 << 14)
#घोषणा NO_FCOE_FLAG			(1 << 15)
#घोषणा BC_SUPPORTS_PFC_STATS		(1 << 17)
#घोषणा TX_SWITCHING			(1 << 18)
#घोषणा BC_SUPPORTS_FCOE_FEATURES	(1 << 19)
#घोषणा USING_SINGLE_MSIX_FLAG		(1 << 20)
#घोषणा BC_SUPPORTS_DCBX_MSG_NON_PMF	(1 << 21)
#घोषणा IS_VF_FLAG			(1 << 22)
#घोषणा BC_SUPPORTS_RMMOD_CMD		(1 << 23)
#घोषणा HAS_PHYS_PORT_ID		(1 << 24)
#घोषणा AER_ENABLED			(1 << 25)
#घोषणा PTP_SUPPORTED			(1 << 26)
#घोषणा TX_TIMESTAMPING_EN		(1 << 27)

#घोषणा BP_NOMCP(bp)			((bp)->flags & NO_MCP_FLAG)

#अगर_घोषित CONFIG_BNX2X_SRIOV
#घोषणा IS_VF(bp)			((bp)->flags & IS_VF_FLAG)
#घोषणा IS_PF(bp)			(!((bp)->flags & IS_VF_FLAG))
#अन्यथा
#घोषणा IS_VF(bp)			false
#घोषणा IS_PF(bp)			true
#पूर्ण_अगर

#घोषणा NO_ISCSI(bp)		((bp)->flags & NO_ISCSI_FLAG)
#घोषणा NO_ISCSI_OOO(bp)	((bp)->flags & NO_ISCSI_OOO_FLAG)
#घोषणा NO_FCOE(bp)		((bp)->flags & NO_FCOE_FLAG)

	u8			cnic_support;
	bool			cnic_enabled;
	bool			cnic_loaded;
	काष्ठा cnic_eth_dev	*(*cnic_probe)(काष्ठा net_device *);

	/* Flag that indicates that we can start looking क्रम FCoE L2 queue
	 * completions in the शेष status block.
	 */
	bool			fcoe_init;

	पूर्णांक			mrrs;

	काष्ठा delayed_work	sp_task;
	काष्ठा delayed_work	iov_task;

	atomic_t		पूर्णांकerrupt_occurred;
	काष्ठा delayed_work	sp_rtnl_task;

	काष्ठा delayed_work	period_task;
	काष्ठा समयr_list	समयr;
	पूर्णांक			current_पूर्णांकerval;

	u16			fw_seq;
	u16			fw_drv_pulse_wr_seq;
	u32			func_stx;

	काष्ठा link_params	link_params;
	काष्ठा link_vars	link_vars;
	u32			link_cnt;
	काष्ठा bnx2x_link_report_data last_reported_link;
	bool			क्रमce_link_करोwn;

	काष्ठा mdio_अगर_info	mdio;

	काष्ठा bnx2x_common	common;
	काष्ठा bnx2x_port	port;

	काष्ठा cmng_init	cmng;

	u32			mf_config[E1HVN_MAX];
	u32			mf_ext_config;
	u32			path_has_ovlan; /* E3 */
	u16			mf_ov;
	u8			mf_mode;
#घोषणा IS_MF(bp)		(bp->mf_mode != 0)
#घोषणा IS_MF_SI(bp)		(bp->mf_mode == MULTI_FUNCTION_SI)
#घोषणा IS_MF_SD(bp)		(bp->mf_mode == MULTI_FUNCTION_SD)
#घोषणा IS_MF_AFEX(bp)		(bp->mf_mode == MULTI_FUNCTION_AFEX)
	u8			mf_sub_mode;
#घोषणा IS_MF_UFP(bp)		(IS_MF_SD(bp) && \
				 bp->mf_sub_mode == SUB_MF_MODE_UFP)
#घोषणा IS_MF_BD(bp)		(IS_MF_SD(bp) && \
				 bp->mf_sub_mode == SUB_MF_MODE_BD)

	u8			wol;

	पूर्णांक			rx_ring_size;

	u16			tx_quick_cons_trip_पूर्णांक;
	u16			tx_quick_cons_trip;
	u16			tx_ticks_पूर्णांक;
	u16			tx_ticks;

	u16			rx_quick_cons_trip_पूर्णांक;
	u16			rx_quick_cons_trip;
	u16			rx_ticks_पूर्णांक;
	u16			rx_ticks;
/* Maximal coalescing समयout in us */
#घोषणा BNX2X_MAX_COALESCE_TOUT		(0xff*BNX2X_BTR)

	u32			lin_cnt;

	u16			state;
#घोषणा BNX2X_STATE_CLOSED		0
#घोषणा BNX2X_STATE_OPENING_WAIT4_LOAD	0x1000
#घोषणा BNX2X_STATE_OPENING_WAIT4_PORT	0x2000
#घोषणा BNX2X_STATE_OPEN		0x3000
#घोषणा BNX2X_STATE_CLOSING_WAIT4_HALT	0x4000
#घोषणा BNX2X_STATE_CLOSING_WAIT4_DELETE 0x5000

#घोषणा BNX2X_STATE_DIAG		0xe000
#घोषणा BNX2X_STATE_ERROR		0xf000

#घोषणा BNX2X_MAX_PRIORITY		8
	पूर्णांक			num_queues;
	uपूर्णांक			num_ethernet_queues;
	uपूर्णांक			num_cnic_queues;
	पूर्णांक			disable_tpa;

	u32			rx_mode;
#घोषणा BNX2X_RX_MODE_NONE		0
#घोषणा BNX2X_RX_MODE_NORMAL		1
#घोषणा BNX2X_RX_MODE_ALLMULTI		2
#घोषणा BNX2X_RX_MODE_PROMISC		3
#घोषणा BNX2X_MAX_MULTICAST		64

	u8			igu_dsb_id;
	u8			igu_base_sb;
	u8			igu_sb_cnt;
	u8			min_msix_vec_cnt;

	u32			igu_base_addr;
	dma_addr_t		def_status_blk_mapping;

	काष्ठा bnx2x_slowpath	*slowpath;
	dma_addr_t		slowpath_mapping;

	/* Mechanism protecting the drv_info_to_mcp */
	काष्ठा mutex		drv_info_mutex;
	bool			drv_info_mng_owner;

	/* Total number of FW statistics requests */
	u8			fw_stats_num;

	/*
	 * This is a memory buffer that will contain both statistics
	 * ramrod request and data.
	 */
	व्योम			*fw_stats;
	dma_addr_t		fw_stats_mapping;

	/*
	 * FW statistics request लघुcut (poपूर्णांकs at the
	 * beginning of fw_stats buffer).
	 */
	काष्ठा bnx2x_fw_stats_req	*fw_stats_req;
	dma_addr_t			fw_stats_req_mapping;
	पूर्णांक				fw_stats_req_sz;

	/*
	 * FW statistics data लघुcut (poपूर्णांकs at the beginning of
	 * fw_stats buffer + fw_stats_req_sz).
	 */
	काष्ठा bnx2x_fw_stats_data	*fw_stats_data;
	dma_addr_t			fw_stats_data_mapping;
	पूर्णांक				fw_stats_data_sz;

	/* For max 1024 cids (VF RSS), 32KB ILT page size and 1KB
	 * context size we need 8 ILT entries.
	 */
#घोषणा ILT_MAX_L2_LINES	32
	काष्ठा hw_context	context[ILT_MAX_L2_LINES];

	काष्ठा bnx2x_ilt	*ilt;
#घोषणा BP_ILT(bp)		((bp)->ilt)
#घोषणा ILT_MAX_LINES		256
/*
 * Maximum supported number of RSS queues: number of IGU SBs minus one that goes
 * to CNIC.
 */
#घोषणा BNX2X_MAX_RSS_COUNT(bp)	((bp)->igu_sb_cnt - CNIC_SUPPORT(bp))

/*
 * Maximum CID count that might be required by the bnx2x:
 * Max RSS * Max_Tx_Multi_Cos + FCoE + iSCSI
 */

#घोषणा BNX2X_L2_CID_COUNT(bp)	(BNX2X_NUM_ETH_QUEUES(bp) * BNX2X_MULTI_TX_COS \
				+ CNIC_SUPPORT(bp) * (2 + UIO_CID_PAD(bp)))
#घोषणा BNX2X_L2_MAX_CID(bp)	(BNX2X_MAX_RSS_COUNT(bp) * BNX2X_MULTI_TX_COS \
				+ CNIC_SUPPORT(bp) * (2 + UIO_CID_PAD(bp)))
#घोषणा L2_ILT_LINES(bp)	(DIV_ROUND_UP(BNX2X_L2_CID_COUNT(bp),\
					ILT_PAGE_CIDS))

	पूर्णांक			qm_cid_count;

	bool			dropless_fc;

	व्योम			*t2;
	dma_addr_t		t2_mapping;
	काष्ठा cnic_ops	__rcu	*cnic_ops;
	व्योम			*cnic_data;
	u32			cnic_tag;
	काष्ठा cnic_eth_dev	cnic_eth_dev;
	जोड़ host_hc_status_block cnic_sb;
	dma_addr_t		cnic_sb_mapping;
	काष्ठा eth_spe		*cnic_kwq;
	काष्ठा eth_spe		*cnic_kwq_prod;
	काष्ठा eth_spe		*cnic_kwq_cons;
	काष्ठा eth_spe		*cnic_kwq_last;
	u16			cnic_kwq_pending;
	u16			cnic_spq_pending;
	u8			fip_mac[ETH_ALEN];
	काष्ठा mutex		cnic_mutex;
	काष्ठा bnx2x_vlan_mac_obj iscsi_l2_mac_obj;

	/* Start index of the "special" (CNIC related) L2 clients */
	u8				cnic_base_cl_id;

	पूर्णांक			dmae_पढ़ोy;
	/* used to synchronize dmae accesses */
	spinlock_t		dmae_lock;

	/* used to protect the FW mail box */
	काष्ठा mutex		fw_mb_mutex;

	/* used to synchronize stats collecting */
	पूर्णांक			stats_state;

	/* used क्रम synchronization of concurrent thपढ़ोs statistics handling */
	काष्ठा semaphore	stats_lock;

	/* used by dmae command loader */
	काष्ठा dmae_command	stats_dmae;
	पूर्णांक			executer_idx;

	u16			stats_counter;
	काष्ठा bnx2x_eth_stats	eth_stats;
	काष्ठा host_func_stats		func_stats;
	काष्ठा bnx2x_eth_stats_old	eth_stats_old;
	काष्ठा bnx2x_net_stats_old	net_stats_old;
	काष्ठा bnx2x_fw_port_stats_old	fw_stats_old;
	bool			stats_init;

	काष्ठा z_stream_s	*strm;
	व्योम			*gunzip_buf;
	dma_addr_t		gunzip_mapping;
	पूर्णांक			gunzip_outlen;
#घोषणा FW_BUF_SIZE			0x8000
#घोषणा GUNZIP_BUF(bp)			(bp->gunzip_buf)
#घोषणा GUNZIP_PHYS(bp)			(bp->gunzip_mapping)
#घोषणा GUNZIP_OUTLEN(bp)		(bp->gunzip_outlen)

	काष्ठा raw_op		*init_ops;
	/* Init blocks offsets inside init_ops */
	u16			*init_ops_offsets;
	/* Data blob - has 32 bit granularity */
	u32			*init_data;
	u32			init_mode_flags;
#घोषणा INIT_MODE_FLAGS(bp)	(bp->init_mode_flags)
	/* Zipped PRAM blobs - raw data */
	स्थिर u8		*tsem_पूर्णांक_table_data;
	स्थिर u8		*tsem_pram_data;
	स्थिर u8		*usem_पूर्णांक_table_data;
	स्थिर u8		*usem_pram_data;
	स्थिर u8		*xsem_पूर्णांक_table_data;
	स्थिर u8		*xsem_pram_data;
	स्थिर u8		*csem_पूर्णांक_table_data;
	स्थिर u8		*csem_pram_data;
#घोषणा INIT_OPS(bp)			(bp->init_ops)
#घोषणा INIT_OPS_OFFSETS(bp)		(bp->init_ops_offsets)
#घोषणा INIT_DATA(bp)			(bp->init_data)
#घोषणा INIT_TSEM_INT_TABLE_DATA(bp)	(bp->tsem_पूर्णांक_table_data)
#घोषणा INIT_TSEM_PRAM_DATA(bp)		(bp->tsem_pram_data)
#घोषणा INIT_USEM_INT_TABLE_DATA(bp)	(bp->usem_पूर्णांक_table_data)
#घोषणा INIT_USEM_PRAM_DATA(bp)		(bp->usem_pram_data)
#घोषणा INIT_XSEM_INT_TABLE_DATA(bp)	(bp->xsem_पूर्णांक_table_data)
#घोषणा INIT_XSEM_PRAM_DATA(bp)		(bp->xsem_pram_data)
#घोषणा INIT_CSEM_INT_TABLE_DATA(bp)	(bp->csem_पूर्णांक_table_data)
#घोषणा INIT_CSEM_PRAM_DATA(bp)		(bp->csem_pram_data)

#घोषणा PHY_FW_VER_LEN			20
	अक्षर			fw_ver[32];
	स्थिर काष्ठा firmware	*firmware;

	काष्ठा bnx2x_vfdb	*vfdb;
#घोषणा IS_SRIOV(bp)		((bp)->vfdb)

	/* DCB support on/off */
	u16 dcb_state;
#घोषणा BNX2X_DCB_STATE_OFF			0
#घोषणा BNX2X_DCB_STATE_ON			1

	/* DCBX engine mode */
	पूर्णांक dcbx_enabled;
#घोषणा BNX2X_DCBX_ENABLED_OFF			0
#घोषणा BNX2X_DCBX_ENABLED_ON_NEG_OFF		1
#घोषणा BNX2X_DCBX_ENABLED_ON_NEG_ON		2
#घोषणा BNX2X_DCBX_ENABLED_INVALID		(-1)

	bool dcbx_mode_uset;

	काष्ठा bnx2x_config_dcbx_params		dcbx_config_params;
	काष्ठा bnx2x_dcbx_port_params		dcbx_port_params;
	पूर्णांक					dcb_version;

	/* CAM credit pools */
	काष्ठा bnx2x_credit_pool_obj		vlans_pool;

	काष्ठा bnx2x_credit_pool_obj		macs_pool;

	/* RX_MODE object */
	काष्ठा bnx2x_rx_mode_obj		rx_mode_obj;

	/* MCAST object */
	काष्ठा bnx2x_mcast_obj			mcast_obj;

	/* RSS configuration object */
	काष्ठा bnx2x_rss_config_obj		rss_conf_obj;

	/* Function State controlling object */
	काष्ठा bnx2x_func_sp_obj		func_obj;

	अचिन्हित दीर्घ				sp_state;

	/* operation indication क्रम the sp_rtnl task */
	अचिन्हित दीर्घ				sp_rtnl_state;

	/* Indication of the IOV tasks */
	अचिन्हित दीर्घ				iov_task_state;

	/* DCBX Negotiation results */
	काष्ठा dcbx_features			dcbx_local_feat;
	u32					dcbx_error;

#अगर_घोषित BCM_DCBNL
	काष्ठा dcbx_features			dcbx_remote_feat;
	u32					dcbx_remote_flags;
#पूर्ण_अगर
	/* AFEX: store शेष vlan used */
	पूर्णांक					afex_def_vlan_tag;
	क्रमागत mf_cfg_afex_vlan_mode		afex_vlan_mode;
	u32					pending_max;

	/* multiple tx classes of service */
	u8					max_cos;

	/* priority to cos mapping */
	u8					prio_to_cos[8];

	पूर्णांक fp_array_size;
	u32 dump_preset_idx;

	u8					phys_port_id[ETH_ALEN];

	/* PTP related context */
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा work_काष्ठा ptp_task;
	काष्ठा cyclecounter cyclecounter;
	काष्ठा समयcounter समयcounter;
	bool समयcounter_init_करोne;
	काष्ठा sk_buff *ptp_tx_skb;
	अचिन्हित दीर्घ ptp_tx_start;
	bool hwtstamp_ioctl_called;
	u16 tx_type;
	u16 rx_filter;

	काष्ठा bnx2x_link_report_data		vf_link_vars;
	काष्ठा list_head vlan_reg;
	u16 vlan_cnt;
	u16 vlan_credit;
	bool accept_any_vlan;

	/* Vxlan/Geneve related inक्रमmation */
	u16 udp_tunnel_ports[BNX2X_UDP_PORT_MAX];
पूर्ण;

/* Tx queues may be less or equal to Rx queues */
बाह्य पूर्णांक num_queues;
#घोषणा BNX2X_NUM_QUEUES(bp)	(bp->num_queues)
#घोषणा BNX2X_NUM_ETH_QUEUES(bp) ((bp)->num_ethernet_queues)
#घोषणा BNX2X_NUM_NON_CNIC_QUEUES(bp)	(BNX2X_NUM_QUEUES(bp) - \
					 (bp)->num_cnic_queues)
#घोषणा BNX2X_NUM_RX_QUEUES(bp)	BNX2X_NUM_QUEUES(bp)

#घोषणा is_multi(bp)		(BNX2X_NUM_QUEUES(bp) > 1)

#घोषणा BNX2X_MAX_QUEUES(bp)	BNX2X_MAX_RSS_COUNT(bp)
/* #घोषणा is_eth_multi(bp)	(BNX2X_NUM_ETH_QUEUES(bp) > 1) */

#घोषणा RSS_IPV4_CAP_MASK						\
	TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV4_CAPABILITY

#घोषणा RSS_IPV4_TCP_CAP_MASK						\
	TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV4_TCP_CAPABILITY

#घोषणा RSS_IPV6_CAP_MASK						\
	TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV6_CAPABILITY

#घोषणा RSS_IPV6_TCP_CAP_MASK						\
	TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV6_TCP_CAPABILITY

काष्ठा bnx2x_func_init_params अणु
	/* dma */
	bool		spq_active;
	dma_addr_t	spq_map;
	u16		spq_prod;

	u16		func_id;	/* असल fid */
	u16		pf_id;
पूर्ण;

#घोषणा क्रम_each_cnic_queue(bp, var) \
	क्रम ((var) = BNX2X_NUM_ETH_QUEUES(bp); (var) < BNX2X_NUM_QUEUES(bp); \
	     (var)++) \
		अगर (skip_queue(bp, var))	\
			जारी;		\
		अन्यथा

#घोषणा क्रम_each_eth_queue(bp, var) \
	क्रम ((var) = 0; (var) < BNX2X_NUM_ETH_QUEUES(bp); (var)++)

#घोषणा क्रम_each_nonशेष_eth_queue(bp, var) \
	क्रम ((var) = 1; (var) < BNX2X_NUM_ETH_QUEUES(bp); (var)++)

#घोषणा क्रम_each_queue(bp, var) \
	क्रम ((var) = 0; (var) < BNX2X_NUM_QUEUES(bp); (var)++) \
		अगर (skip_queue(bp, var))	\
			जारी;		\
		अन्यथा

/* Skip क्रमwarding FP */
#घोषणा क्रम_each_valid_rx_queue(bp, var)			\
	क्रम ((var) = 0;						\
	     (var) < (CNIC_LOADED(bp) ? BNX2X_NUM_QUEUES(bp) :	\
		      BNX2X_NUM_ETH_QUEUES(bp));		\
	     (var)++)						\
		अगर (skip_rx_queue(bp, var))			\
			जारी;				\
		अन्यथा

#घोषणा क्रम_each_rx_queue_cnic(bp, var) \
	क्रम ((var) = BNX2X_NUM_ETH_QUEUES(bp); (var) < BNX2X_NUM_QUEUES(bp); \
	     (var)++) \
		अगर (skip_rx_queue(bp, var))	\
			जारी;		\
		अन्यथा

#घोषणा क्रम_each_rx_queue(bp, var) \
	क्रम ((var) = 0; (var) < BNX2X_NUM_QUEUES(bp); (var)++) \
		अगर (skip_rx_queue(bp, var))	\
			जारी;		\
		अन्यथा

/* Skip OOO FP */
#घोषणा क्रम_each_valid_tx_queue(bp, var)			\
	क्रम ((var) = 0;						\
	     (var) < (CNIC_LOADED(bp) ? BNX2X_NUM_QUEUES(bp) :	\
		      BNX2X_NUM_ETH_QUEUES(bp));		\
	     (var)++)						\
		अगर (skip_tx_queue(bp, var))			\
			जारी;				\
		अन्यथा

#घोषणा क्रम_each_tx_queue_cnic(bp, var) \
	क्रम ((var) = BNX2X_NUM_ETH_QUEUES(bp); (var) < BNX2X_NUM_QUEUES(bp); \
	     (var)++) \
		अगर (skip_tx_queue(bp, var))	\
			जारी;		\
		अन्यथा

#घोषणा क्रम_each_tx_queue(bp, var) \
	क्रम ((var) = 0; (var) < BNX2X_NUM_QUEUES(bp); (var)++) \
		अगर (skip_tx_queue(bp, var))	\
			जारी;		\
		अन्यथा

#घोषणा क्रम_each_nonशेष_queue(bp, var) \
	क्रम ((var) = 1; (var) < BNX2X_NUM_QUEUES(bp); (var)++) \
		अगर (skip_queue(bp, var))	\
			जारी;		\
		अन्यथा

#घोषणा क्रम_each_cos_in_tx_queue(fp, var) \
	क्रम ((var) = 0; (var) < (fp)->max_cos; (var)++)

/* skip rx queue
 * अगर FCOE l2 support is disabled and this is the fcoe L2 queue
 */
#घोषणा skip_rx_queue(bp, idx)	(NO_FCOE(bp) && IS_FCOE_IDX(idx))

/* skip tx queue
 * अगर FCOE l2 support is disabled and this is the fcoe L2 queue
 */
#घोषणा skip_tx_queue(bp, idx)	(NO_FCOE(bp) && IS_FCOE_IDX(idx))

#घोषणा skip_queue(bp, idx)	(NO_FCOE(bp) && IS_FCOE_IDX(idx))

/*self test*/
पूर्णांक bnx2x_idle_chk(काष्ठा bnx2x *bp);

/**
 * bnx2x_set_mac_one - configure a single MAC address
 *
 * @bp:			driver handle
 * @mac:		MAC to configure
 * @obj:		MAC object handle
 * @set:		अगर 'true' add a new MAC, otherwise - delete
 * @mac_type:		the type of the MAC to configure (e.g. ETH, UC list)
 * @ramrod_flags:	RAMROD_XXX flags (e.g. RAMROD_CONT, RAMROD_COMP_WAIT)
 *
 * Configures one MAC according to provided parameters or जारीs the
 * execution of previously scheduled commands अगर RAMROD_CONT is set in
 * ramrod_flags.
 *
 * Returns zero अगर operation has successfully completed, a positive value अगर the
 * operation has been successfully scheduled and a negative - अगर a requested
 * operations has failed.
 */
पूर्णांक bnx2x_set_mac_one(काष्ठा bnx2x *bp, u8 *mac,
		      काष्ठा bnx2x_vlan_mac_obj *obj, bool set,
		      पूर्णांक mac_type, अचिन्हित दीर्घ *ramrod_flags);

पूर्णांक bnx2x_set_vlan_one(काष्ठा bnx2x *bp, u16 vlan,
		       काष्ठा bnx2x_vlan_mac_obj *obj, bool set,
		       अचिन्हित दीर्घ *ramrod_flags);

/**
 * bnx2x_del_all_macs - delete all MACs configured क्रम the specअगरic MAC object
 *
 * @bp:			driver handle
 * @mac_obj:		MAC object handle
 * @mac_type:		type of the MACs to clear (BNX2X_XXX_MAC)
 * @रुको_क्रम_comp:	अगर 'true' block until completion
 *
 * Deletes all MACs of the specअगरic type (e.g. ETH, UC list).
 *
 * Returns zero अगर operation has successfully completed, a positive value अगर the
 * operation has been successfully scheduled and a negative - अगर a requested
 * operations has failed.
 */
पूर्णांक bnx2x_del_all_macs(काष्ठा bnx2x *bp,
		       काष्ठा bnx2x_vlan_mac_obj *mac_obj,
		       पूर्णांक mac_type, bool रुको_क्रम_comp);

/* Init Function API  */
व्योम bnx2x_func_init(काष्ठा bnx2x *bp, काष्ठा bnx2x_func_init_params *p);
व्योम bnx2x_init_sb(काष्ठा bnx2x *bp, dma_addr_t mapping, पूर्णांक vfid,
		    u8 vf_valid, पूर्णांक fw_sb_id, पूर्णांक igu_sb_id);
पूर्णांक bnx2x_get_gpio(काष्ठा bnx2x *bp, पूर्णांक gpio_num, u8 port);
पूर्णांक bnx2x_set_gpio(काष्ठा bnx2x *bp, पूर्णांक gpio_num, u32 mode, u8 port);
पूर्णांक bnx2x_set_mult_gpio(काष्ठा bnx2x *bp, u8 pins, u32 mode);
पूर्णांक bnx2x_set_gpio_पूर्णांक(काष्ठा bnx2x *bp, पूर्णांक gpio_num, u32 mode, u8 port);
व्योम bnx2x_पढ़ो_mf_cfg(काष्ठा bnx2x *bp);

पूर्णांक bnx2x_pretend_func(काष्ठा bnx2x *bp, u16 pretend_func_val);

/* dmae */
व्योम bnx2x_पढ़ो_dmae(काष्ठा bnx2x *bp, u32 src_addr, u32 len32);
व्योम bnx2x_ग_लिखो_dmae(काष्ठा bnx2x *bp, dma_addr_t dma_addr, u32 dst_addr,
		      u32 len32);
व्योम bnx2x_post_dmae(काष्ठा bnx2x *bp, काष्ठा dmae_command *dmae, पूर्णांक idx);
u32 bnx2x_dmae_opcode_add_comp(u32 opcode, u8 comp_type);
u32 bnx2x_dmae_opcode_clr_src_reset(u32 opcode);
u32 bnx2x_dmae_opcode(काष्ठा bnx2x *bp, u8 src_type, u8 dst_type,
		      bool with_comp, u8 comp_type);

व्योम bnx2x_prep_dmae_with_comp(काष्ठा bnx2x *bp, काष्ठा dmae_command *dmae,
			       u8 src_type, u8 dst_type);
पूर्णांक bnx2x_issue_dmae_with_comp(काष्ठा bnx2x *bp, काष्ठा dmae_command *dmae,
			       u32 *comp);

/* FLR related routines */
u32 bnx2x_flr_clnup_poll_count(काष्ठा bnx2x *bp);
व्योम bnx2x_tx_hw_flushed(काष्ठा bnx2x *bp, u32 poll_count);
पूर्णांक bnx2x_send_final_clnup(काष्ठा bnx2x *bp, u8 clnup_func, u32 poll_cnt);
u8 bnx2x_is_pcie_pending(काष्ठा pci_dev *dev);
पूर्णांक bnx2x_flr_clnup_poll_hw_counter(काष्ठा bnx2x *bp, u32 reg,
				    अक्षर *msg, u32 poll_cnt);

व्योम bnx2x_calc_fc_adv(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_sp_post(काष्ठा bnx2x *bp, पूर्णांक command, पूर्णांक cid,
		  u32 data_hi, u32 data_lo, पूर्णांक cmd_type);
व्योम bnx2x_update_coalesce(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_get_cur_phy_idx(काष्ठा bnx2x *bp);

bool bnx2x_port_after_undi(काष्ठा bnx2x *bp);

अटल अंतरभूत u32 reg_poll(काष्ठा bnx2x *bp, u32 reg, u32 expected, पूर्णांक ms,
			   पूर्णांक रुको)
अणु
	u32 val;

	करो अणु
		val = REG_RD(bp, reg);
		अगर (val == expected)
			अवरोध;
		ms -= रुको;
		msleep(रुको);

	पूर्ण जबतक (ms > 0);

	वापस val;
पूर्ण

व्योम bnx2x_igu_clear_sb_gen(काष्ठा bnx2x *bp, u8 func, u8 idu_sb_id,
			    bool is_pf);

#घोषणा BNX2X_ILT_ZALLOC(x, y, size)					\
	x = dma_alloc_coherent(&bp->pdev->dev, size, y, GFP_KERNEL)

#घोषणा BNX2X_ILT_FREE(x, y, size) \
	करो अणु \
		अगर (x) अणु \
			dma_मुक्त_coherent(&bp->pdev->dev, size, x, y); \
			x = शून्य; \
			y = 0; \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा ILOG2(x)	(ilog2((x)))

#घोषणा ILT_NUM_PAGE_ENTRIES	(3072)
/* In 57710/11 we use whole table since we have 8 func
 * In 57712 we have only 4 func, but use same size per func, then only half of
 * the table in use
 */
#घोषणा ILT_PER_FUNC		(ILT_NUM_PAGE_ENTRIES/8)

#घोषणा FUNC_ILT_BASE(func)	(func * ILT_PER_FUNC)
/*
 * the phys address is shअगरted right 12 bits and has an added
 * 1=valid bit added to the 53rd bit
 * then since this is a wide रेजिस्टर(TM)
 * we split it पूर्णांकo two 32 bit ग_लिखोs
 */
#घोषणा ONCHIP_ADDR1(x)		((u32)(((u64)x >> 12) & 0xFFFFFFFF))
#घोषणा ONCHIP_ADDR2(x)		((u32)((1 << 20) | ((u64)x >> 44)))

/* load/unload mode */
#घोषणा LOAD_NORMAL			0
#घोषणा LOAD_OPEN			1
#घोषणा LOAD_DIAG			2
#घोषणा LOAD_LOOPBACK_EXT		3
#घोषणा UNLOAD_NORMAL			0
#घोषणा UNLOAD_CLOSE			1
#घोषणा UNLOAD_RECOVERY			2

/* DMAE command defines */
#घोषणा DMAE_TIMEOUT			-1
#घोषणा DMAE_PCI_ERROR			-2	/* E2 and onward */
#घोषणा DMAE_NOT_RDY			-3
#घोषणा DMAE_PCI_ERR_FLAG		0x80000000

#घोषणा DMAE_SRC_PCI			0
#घोषणा DMAE_SRC_GRC			1

#घोषणा DMAE_DST_NONE			0
#घोषणा DMAE_DST_PCI			1
#घोषणा DMAE_DST_GRC			2

#घोषणा DMAE_COMP_PCI			0
#घोषणा DMAE_COMP_GRC			1

/* E2 and onward - PCI error handling in the completion */

#घोषणा DMAE_COMP_REGULAR		0
#घोषणा DMAE_COM_SET_ERR		1

#घोषणा DMAE_CMD_SRC_PCI		(DMAE_SRC_PCI << \
						DMAE_COMMAND_SRC_SHIFT)
#घोषणा DMAE_CMD_SRC_GRC		(DMAE_SRC_GRC << \
						DMAE_COMMAND_SRC_SHIFT)

#घोषणा DMAE_CMD_DST_PCI		(DMAE_DST_PCI << \
						DMAE_COMMAND_DST_SHIFT)
#घोषणा DMAE_CMD_DST_GRC		(DMAE_DST_GRC << \
						DMAE_COMMAND_DST_SHIFT)

#घोषणा DMAE_CMD_C_DST_PCI		(DMAE_COMP_PCI << \
						DMAE_COMMAND_C_DST_SHIFT)
#घोषणा DMAE_CMD_C_DST_GRC		(DMAE_COMP_GRC << \
						DMAE_COMMAND_C_DST_SHIFT)

#घोषणा DMAE_CMD_C_ENABLE		DMAE_COMMAND_C_TYPE_ENABLE

#घोषणा DMAE_CMD_ENDIANITY_NO_SWAP	(0 << DMAE_COMMAND_ENDIANITY_SHIFT)
#घोषणा DMAE_CMD_ENDIANITY_B_SWAP	(1 << DMAE_COMMAND_ENDIANITY_SHIFT)
#घोषणा DMAE_CMD_ENDIANITY_DW_SWAP	(2 << DMAE_COMMAND_ENDIANITY_SHIFT)
#घोषणा DMAE_CMD_ENDIANITY_B_DW_SWAP	(3 << DMAE_COMMAND_ENDIANITY_SHIFT)

#घोषणा DMAE_CMD_PORT_0			0
#घोषणा DMAE_CMD_PORT_1			DMAE_COMMAND_PORT

#घोषणा DMAE_CMD_SRC_RESET		DMAE_COMMAND_SRC_RESET
#घोषणा DMAE_CMD_DST_RESET		DMAE_COMMAND_DST_RESET
#घोषणा DMAE_CMD_E1HVN_SHIFT		DMAE_COMMAND_E1HVN_SHIFT

#घोषणा DMAE_SRC_PF			0
#घोषणा DMAE_SRC_VF			1

#घोषणा DMAE_DST_PF			0
#घोषणा DMAE_DST_VF			1

#घोषणा DMAE_C_SRC			0
#घोषणा DMAE_C_DST			1

#घोषणा DMAE_LEN32_RD_MAX		0x80
#घोषणा DMAE_LEN32_WR_MAX(bp)		(CHIP_IS_E1(bp) ? 0x400 : 0x2000)

#घोषणा DMAE_COMP_VAL			0x60d0d0ae /* E2 and on - upper bit
						    * indicates error
						    */

#घोषणा MAX_DMAE_C_PER_PORT		8
#घोषणा INIT_DMAE_C(bp)			(BP_PORT(bp) * MAX_DMAE_C_PER_PORT + \
					 BP_VN(bp))
#घोषणा PMF_DMAE_C(bp)			(BP_PORT(bp) * MAX_DMAE_C_PER_PORT + \
					 E1HVN_MAX)

/* Following is the DMAE channel number allocation क्रम the clients.
 *   MFW: OCBB/OCSD implementations use DMAE channels 14/15 respectively.
 *   Driver: 0-3 and 8-11 (क्रम PF dmae operations)
 *           4 and 12 (क्रम stats requests)
 */
#घोषणा BNX2X_FW_DMAE_C                 13 /* Channel क्रम FW DMAE operations */

/* PCIE link and speed */
#घोषणा PCICFG_LINK_WIDTH		0x1f00000
#घोषणा PCICFG_LINK_WIDTH_SHIFT		20
#घोषणा PCICFG_LINK_SPEED		0xf0000
#घोषणा PCICFG_LINK_SPEED_SHIFT		16

#घोषणा BNX2X_NUM_TESTS_SF		7
#घोषणा BNX2X_NUM_TESTS_MF		3
#घोषणा BNX2X_NUM_TESTS(bp)		(IS_MF(bp) ? BNX2X_NUM_TESTS_MF : \
					     IS_VF(bp) ? 0 : BNX2X_NUM_TESTS_SF)

#घोषणा BNX2X_PHY_LOOPBACK		0
#घोषणा BNX2X_MAC_LOOPBACK		1
#घोषणा BNX2X_EXT_LOOPBACK		2
#घोषणा BNX2X_PHY_LOOPBACK_FAILED	1
#घोषणा BNX2X_MAC_LOOPBACK_FAILED	2
#घोषणा BNX2X_EXT_LOOPBACK_FAILED	3
#घोषणा BNX2X_LOOPBACK_FAILED		(BNX2X_MAC_LOOPBACK_FAILED | \
					 BNX2X_PHY_LOOPBACK_FAILED)

#घोषणा STROM_ASSERT_ARRAY_SIZE		50

/* must be used on a CID beक्रमe placing it on a HW ring */
#घोषणा HW_CID(bp, x)			((BP_PORT(bp) << 23) | \
					 (BP_VN(bp) << BNX2X_SWCID_SHIFT) | \
					 (x))

#घोषणा SP_DESC_CNT		(BCM_PAGE_SIZE / माप(काष्ठा eth_spe))
#घोषणा MAX_SP_DESC_CNT			(SP_DESC_CNT - 1)

#घोषणा BNX2X_BTR			4
#घोषणा MAX_SPQ_PENDING			8

/* CMNG स्थिरants, as derived from प्रणाली spec calculations */
/* शेष MIN rate in हाल VNIC min rate is configured to zero - 100Mbps */
#घोषणा DEF_MIN_RATE					100
/* resolution of the rate shaping समयr - 400 usec */
#घोषणा RS_PERIODIC_TIMEOUT_USEC			400
/* number of bytes in single QM arbitration cycle -
 * coefficient क्रम calculating the fairness समयr */
#घोषणा QM_ARB_BYTES					160000
/* resolution of Min algorithm 1:100 */
#घोषणा MIN_RES						100
/* how many bytes above threshold क्रम the minimal credit of Min algorithm*/
#घोषणा MIN_ABOVE_THRESH				32768
/* Fairness algorithm पूर्णांकegration समय coefficient -
 * क्रम calculating the actual Tfair */
#घोषणा T_FAIR_COEF	((MIN_ABOVE_THRESH +  QM_ARB_BYTES) * 8 * MIN_RES)
/* Memory of fairness algorithm . 2 cycles */
#घोषणा FAIR_MEM					2

#घोषणा ATTN_NIG_FOR_FUNC		(1L << 8)
#घोषणा ATTN_SW_TIMER_4_FUNC		(1L << 9)
#घोषणा GPIO_2_FUNC			(1L << 10)
#घोषणा GPIO_3_FUNC			(1L << 11)
#घोषणा GPIO_4_FUNC			(1L << 12)
#घोषणा ATTN_GENERAL_ATTN_1		(1L << 13)
#घोषणा ATTN_GENERAL_ATTN_2		(1L << 14)
#घोषणा ATTN_GENERAL_ATTN_3		(1L << 15)
#घोषणा ATTN_GENERAL_ATTN_4		(1L << 13)
#घोषणा ATTN_GENERAL_ATTN_5		(1L << 14)
#घोषणा ATTN_GENERAL_ATTN_6		(1L << 15)

#घोषणा ATTN_HARD_WIRED_MASK		0xff00
#घोषणा ATTENTION_ID			4

#घोषणा IS_MF_STORAGE_ONLY(bp) (IS_MF_STORAGE_PERSONALITY_ONLY(bp) || \
				 IS_MF_FCOE_AFEX(bp))

/* stuff added to make the code fit 80Col */

#घोषणा BNX2X_PMF_LINK_ASSERT \
	GENERAL_ATTEN_OFFSET(LINK_SYNC_ATTENTION_BIT_FUNC_0 + BP_FUNC(bp))

#घोषणा BNX2X_MC_ASSERT_BITS \
	(GENERAL_ATTEN_OFFSET(TSTORM_FATAL_ASSERT_ATTENTION_BIT) | \
	 GENERAL_ATTEN_OFFSET(USTORM_FATAL_ASSERT_ATTENTION_BIT) | \
	 GENERAL_ATTEN_OFFSET(CSTORM_FATAL_ASSERT_ATTENTION_BIT) | \
	 GENERAL_ATTEN_OFFSET(XSTORM_FATAL_ASSERT_ATTENTION_BIT))

#घोषणा BNX2X_MCP_ASSERT \
	GENERAL_ATTEN_OFFSET(MCP_FATAL_ASSERT_ATTENTION_BIT)

#घोषणा BNX2X_GRC_TIMEOUT	GENERAL_ATTEN_OFFSET(LATCHED_ATTN_TIMEOUT_GRC)
#घोषणा BNX2X_GRC_RSV		(GENERAL_ATTEN_OFFSET(LATCHED_ATTN_RBCR) | \
				 GENERAL_ATTEN_OFFSET(LATCHED_ATTN_RBCT) | \
				 GENERAL_ATTEN_OFFSET(LATCHED_ATTN_RBCN) | \
				 GENERAL_ATTEN_OFFSET(LATCHED_ATTN_RBCU) | \
				 GENERAL_ATTEN_OFFSET(LATCHED_ATTN_RBCP) | \
				 GENERAL_ATTEN_OFFSET(LATCHED_ATTN_RSVD_GRC))

#घोषणा HW_INTERRUPT_ASSERT_SET_0 \
				(AEU_INPUTS_ATTN_BITS_TSDM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_TCM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_TSEMI_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_BRB_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_PBCLIENT_HW_INTERRUPT)
#घोषणा HW_PRTY_ASSERT_SET_0	(AEU_INPUTS_ATTN_BITS_BRB_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_PARSER_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_TSDM_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_SEARCHER_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_TSEMI_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_TCM_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_PBCLIENT_PARITY_ERROR)
#घोषणा HW_INTERRUPT_ASSERT_SET_1 \
				(AEU_INPUTS_ATTN_BITS_QM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_TIMERS_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_XSDM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_XCM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_XSEMI_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_USDM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_UCM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_USEMI_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_UPB_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_CSDM_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_CCM_HW_INTERRUPT)
#घोषणा HW_PRTY_ASSERT_SET_1	(AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR |\
			     AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR)
#घोषणा HW_INTERRUPT_ASSERT_SET_2 \
				(AEU_INPUTS_ATTN_BITS_CSEMI_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_CDU_HW_INTERRUPT | \
				 AEU_INPUTS_ATTN_BITS_DMAE_HW_INTERRUPT | \
			AEU_INPUTS_ATTN_BITS_PXPPCICLOCKCLIENT_HW_INTERRUPT |\
				 AEU_INPUTS_ATTN_BITS_MISC_HW_INTERRUPT)
#घोषणा HW_PRTY_ASSERT_SET_2	(AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR | \
			AEU_INPUTS_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR |\
				 AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR | \
				 AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR)

#घोषणा HW_PRTY_ASSERT_SET_3_WITHOUT_SCPAD \
		(AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY | \
		 AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY | \
		 AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY)

#घोषणा HW_PRTY_ASSERT_SET_3 (HW_PRTY_ASSERT_SET_3_WITHOUT_SCPAD | \
			      AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY)

#घोषणा HW_PRTY_ASSERT_SET_4 (AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR | \
			      AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR)

#घोषणा MULTI_MASK			0x7f

#घोषणा DEF_USB_FUNC_OFF	दुरत्व(काष्ठा cstorm_def_status_block_u, func)
#घोषणा DEF_CSB_FUNC_OFF	दुरत्व(काष्ठा cstorm_def_status_block_c, func)
#घोषणा DEF_XSB_FUNC_OFF	दुरत्व(काष्ठा xstorm_def_status_block, func)
#घोषणा DEF_TSB_FUNC_OFF	दुरत्व(काष्ठा tstorm_def_status_block, func)

#घोषणा DEF_USB_IGU_INDEX_OFF \
			दुरत्व(काष्ठा cstorm_def_status_block_u, igu_index)
#घोषणा DEF_CSB_IGU_INDEX_OFF \
			दुरत्व(काष्ठा cstorm_def_status_block_c, igu_index)
#घोषणा DEF_XSB_IGU_INDEX_OFF \
			दुरत्व(काष्ठा xstorm_def_status_block, igu_index)
#घोषणा DEF_TSB_IGU_INDEX_OFF \
			दुरत्व(काष्ठा tstorm_def_status_block, igu_index)

#घोषणा DEF_USB_SEGMENT_OFF \
			दुरत्व(काष्ठा cstorm_def_status_block_u, segment)
#घोषणा DEF_CSB_SEGMENT_OFF \
			दुरत्व(काष्ठा cstorm_def_status_block_c, segment)
#घोषणा DEF_XSB_SEGMENT_OFF \
			दुरत्व(काष्ठा xstorm_def_status_block, segment)
#घोषणा DEF_TSB_SEGMENT_OFF \
			दुरत्व(काष्ठा tstorm_def_status_block, segment)

#घोषणा BNX2X_SP_DSB_INDEX \
		(&bp->def_status_blk->sp_sb.\
					index_values[HC_SP_INDEX_ETH_DEF_CONS])

#घोषणा CAM_IS_INVALID(x) \
	(GET_FLAG(x.flags, \
	MAC_CONFIGURATION_ENTRY_ACTION_TYPE) == \
	(T_ETH_MAC_COMMAND_INVALIDATE))

/* Number of u32 elements in MC hash array */
#घोषणा MC_HASH_SIZE			8
#घोषणा MC_HASH_OFFSET(bp, i)		(BAR_TSTRORM_INTMEM + \
	TSTORM_APPROXIMATE_MATCH_MULTICAST_FILTERING_OFFSET(BP_FUNC(bp)) + i*4)

#अगर_अघोषित PXP2_REG_PXP2_INT_STS
#घोषणा PXP2_REG_PXP2_INT_STS		PXP2_REG_PXP2_INT_STS_0
#पूर्ण_अगर

#अगर_अघोषित ETH_MAX_RX_CLIENTS_E2
#घोषणा ETH_MAX_RX_CLIENTS_E2		ETH_MAX_RX_CLIENTS_E1H
#पूर्ण_अगर

#घोषणा BNX2X_VPD_LEN			128
#घोषणा VENDOR_ID_LEN			4

#घोषणा VF_ACQUIRE_THRESH		3
#घोषणा VF_ACQUIRE_MAC_FILTERS		1
#घोषणा VF_ACQUIRE_MC_FILTERS		10
#घोषणा VF_ACQUIRE_VLAN_FILTERS		2 /* VLAN0 + 'real' VLAN */

#घोषणा GOOD_ME_REG(me_reg) (((me_reg) & ME_REG_VF_VALID) && \
			    (!((me_reg) & ME_REG_VF_ERR)))
पूर्णांक bnx2x_compare_fw_ver(काष्ठा bnx2x *bp, u32 load_code, bool prपूर्णांक_err);

/* Congestion management fairness mode */
#घोषणा CMNG_FNS_NONE			0
#घोषणा CMNG_FNS_MINMAX			1

#घोषणा HC_SEG_ACCESS_DEF		0   /*Driver decision 0-3*/
#घोषणा HC_SEG_ACCESS_ATTN		4
#घोषणा HC_SEG_ACCESS_NORM		0   /*Driver decision 0-1*/

व्योम bnx2x_set_ethtool_ops(काष्ठा bnx2x *bp, काष्ठा net_device *netdev);
व्योम bnx2x_notअगरy_link_changed(काष्ठा bnx2x *bp);

#घोषणा BNX2X_MF_SD_PROTOCOL(bp) \
	((bp)->mf_config[BP_VN(bp)] & FUNC_MF_CFG_PROTOCOL_MASK)

#घोषणा BNX2X_IS_MF_SD_PROTOCOL_ISCSI(bp) \
	(BNX2X_MF_SD_PROTOCOL(bp) == FUNC_MF_CFG_PROTOCOL_ISCSI)

#घोषणा BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp) \
	(BNX2X_MF_SD_PROTOCOL(bp) == FUNC_MF_CFG_PROTOCOL_FCOE)

#घोषणा IS_MF_ISCSI_SD(bp) (IS_MF_SD(bp) && BNX2X_IS_MF_SD_PROTOCOL_ISCSI(bp))
#घोषणा IS_MF_FCOE_SD(bp) (IS_MF_SD(bp) && BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp))
#घोषणा IS_MF_ISCSI_SI(bp) (IS_MF_SI(bp) && BNX2X_IS_MF_EXT_PROTOCOL_ISCSI(bp))

#घोषणा IS_MF_ISCSI_ONLY(bp)    (IS_MF_ISCSI_SD(bp) ||  IS_MF_ISCSI_SI(bp))

#घोषणा BNX2X_MF_EXT_PROTOCOL_MASK					\
				(MACP_FUNC_CFG_FLAGS_ETHERNET |		\
				 MACP_FUNC_CFG_FLAGS_ISCSI_OFFLOAD |	\
				 MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD)

#घोषणा BNX2X_MF_EXT_PROT(bp)	((bp)->mf_ext_config &			\
				 BNX2X_MF_EXT_PROTOCOL_MASK)

#घोषणा BNX2X_HAS_MF_EXT_PROTOCOL_FCOE(bp)				\
		(BNX2X_MF_EXT_PROT(bp) & MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD)

#घोषणा BNX2X_IS_MF_EXT_PROTOCOL_FCOE(bp)				\
		(BNX2X_MF_EXT_PROT(bp) == MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD)

#घोषणा BNX2X_IS_MF_EXT_PROTOCOL_ISCSI(bp)				\
		(BNX2X_MF_EXT_PROT(bp) == MACP_FUNC_CFG_FLAGS_ISCSI_OFFLOAD)

#घोषणा IS_MF_FCOE_AFEX(bp)						\
		(IS_MF_AFEX(bp) && BNX2X_IS_MF_EXT_PROTOCOL_FCOE(bp))

#घोषणा IS_MF_SD_STORAGE_PERSONALITY_ONLY(bp)				\
				(IS_MF_SD(bp) &&			\
				 (BNX2X_IS_MF_SD_PROTOCOL_ISCSI(bp) ||	\
				  BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp)))

#घोषणा IS_MF_SI_STORAGE_PERSONALITY_ONLY(bp)				\
				(IS_MF_SI(bp) &&			\
				 (BNX2X_IS_MF_EXT_PROTOCOL_ISCSI(bp) ||	\
				  BNX2X_IS_MF_EXT_PROTOCOL_FCOE(bp)))

#घोषणा IS_MF_STORAGE_PERSONALITY_ONLY(bp)				\
			(IS_MF_SD_STORAGE_PERSONALITY_ONLY(bp) ||	\
			 IS_MF_SI_STORAGE_PERSONALITY_ONLY(bp))

/* Determines whether BW configuration arrives in 100Mb units or in
 * percentages from actual physical link speed.
 */
#घोषणा IS_MF_PERCENT_BW(bp) (IS_MF_SI(bp) || IS_MF_UFP(bp) || IS_MF_BD(bp))

#घोषणा SET_FLAG(value, mask, flag) \
	करो अणु\
		(value) &= ~(mask);\
		(value) |= ((flag) << (mask##_SHIFT));\
	पूर्ण जबतक (0)

#घोषणा GET_FLAG(value, mask) \
	(((value) & (mask)) >> (mask##_SHIFT))

#घोषणा GET_FIELD(value, fname) \
	(((value) & (fname##_MASK)) >> (fname##_SHIFT))

क्रमागत अणु
	SWITCH_UPDATE,
	AFEX_UPDATE,
पूर्ण;

#घोषणा NUM_MACS	8

व्योम bnx2x_set_local_cmng(काष्ठा bnx2x *bp);

व्योम bnx2x_update_mng_version(काष्ठा bnx2x *bp);

व्योम bnx2x_update_mfw_dump(काष्ठा bnx2x *bp);

#घोषणा MCPR_SCRATCH_BASE(bp) \
	(CHIP_IS_E1x(bp) ? MCP_REG_MCPR_SCRATCH : MCP_A_REG_MCPR_SCRATCH)

#घोषणा E1H_MAX_MF_SB_COUNT (HC_SB_MAX_SB_E1X/(E1HVN_MAX * PORT_MAX))

व्योम bnx2x_init_ptp(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_configure_ptp_filters(काष्ठा bnx2x *bp);
व्योम bnx2x_set_rx_ts(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb);
व्योम bnx2x_रेजिस्टर_phc(काष्ठा bnx2x *bp);

#घोषणा BNX2X_MAX_PHC_DRIFT 31000000
#घोषणा BNX2X_PTP_TX_TIMEOUT

/* Re-configure all previously configured vlan filters.
 * Meant क्रम implicit re-load flows.
 */
पूर्णांक bnx2x_vlan_reconfigure_vid(काष्ठा bnx2x *bp);

#पूर्ण_अगर /* bnx2x.h */
