<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित COMMON_H
#घोषणा COMMON_H

#समावेश "rvu_struct.h"

#घोषणा OTX2_ALIGN			128  /* Align to cacheline */

#घोषणा Q_SIZE_16		0ULL /* 16 entries */
#घोषणा Q_SIZE_64		1ULL /* 64 entries */
#घोषणा Q_SIZE_256		2ULL
#घोषणा Q_SIZE_1K		3ULL
#घोषणा Q_SIZE_4K		4ULL
#घोषणा Q_SIZE_16K		5ULL
#घोषणा Q_SIZE_64K		6ULL
#घोषणा Q_SIZE_256K		7ULL
#घोषणा Q_SIZE_1M		8ULL /* Million entries */
#घोषणा Q_SIZE_MIN		Q_SIZE_16
#घोषणा Q_SIZE_MAX		Q_SIZE_1M

#घोषणा Q_COUNT(x)		(16ULL << (2 * x))
#घोषणा Q_SIZE(x, n)		((ilog2(x) - (n)) / 2)

/* Admin queue info */

/* Since we पूर्णांकend to add only one inकाष्ठाion at a समय,
 * keep queue size to it's minimum.
 */
#घोषणा AQ_SIZE			Q_SIZE_16
/* HW head & tail poपूर्णांकer mask */
#घोषणा AQ_PTR_MASK		0xFFFFF

काष्ठा qmem अणु
	व्योम            *base;
	dma_addr_t	iova;
	पूर्णांक		alloc_sz;
	u16		entry_sz;
	u8		align;
	u32		qsize;
पूर्ण;

अटल अंतरभूत पूर्णांक qmem_alloc(काष्ठा device *dev, काष्ठा qmem **q,
			     पूर्णांक qsize, पूर्णांक entry_sz)
अणु
	काष्ठा qmem *qmem;
	पूर्णांक aligned_addr;

	अगर (!qsize)
		वापस -EINVAL;

	*q = devm_kzalloc(dev, माप(*qmem), GFP_KERNEL);
	अगर (!*q)
		वापस -ENOMEM;
	qmem = *q;

	qmem->entry_sz = entry_sz;
	qmem->alloc_sz = (qsize * entry_sz) + OTX2_ALIGN;
	qmem->base = dma_alloc_coherent(dev, qmem->alloc_sz,
					 &qmem->iova, GFP_KERNEL);
	अगर (!qmem->base)
		वापस -ENOMEM;

	qmem->qsize = qsize;

	aligned_addr = ALIGN((u64)qmem->iova, OTX2_ALIGN);
	qmem->align = (aligned_addr - qmem->iova);
	qmem->base += qmem->align;
	qmem->iova += qmem->align;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qmem_मुक्त(काष्ठा device *dev, काष्ठा qmem *qmem)
अणु
	अगर (!qmem)
		वापस;

	अगर (qmem->base)
		dma_मुक्त_coherent(dev, qmem->alloc_sz,
				  qmem->base - qmem->align,
				  qmem->iova - qmem->align);
	devm_kमुक्त(dev, qmem);
पूर्ण

काष्ठा admin_queue अणु
	काष्ठा qmem	*inst;
	काष्ठा qmem	*res;
	spinlock_t	lock; /* Serialize inst enqueue from PFs */
पूर्ण;

/* NPA aura count */
क्रमागत npa_aura_sz अणु
	NPA_AURA_SZ_0,
	NPA_AURA_SZ_128,
	NPA_AURA_SZ_256,
	NPA_AURA_SZ_512,
	NPA_AURA_SZ_1K,
	NPA_AURA_SZ_2K,
	NPA_AURA_SZ_4K,
	NPA_AURA_SZ_8K,
	NPA_AURA_SZ_16K,
	NPA_AURA_SZ_32K,
	NPA_AURA_SZ_64K,
	NPA_AURA_SZ_128K,
	NPA_AURA_SZ_256K,
	NPA_AURA_SZ_512K,
	NPA_AURA_SZ_1M,
	NPA_AURA_SZ_MAX,
पूर्ण;

#घोषणा NPA_AURA_COUNT(x)	(1ULL << ((x) + 6))

/* NPA AQ result काष्ठाure क्रम init/पढ़ो/ग_लिखो of aura HW contexts */
काष्ठा npa_aq_aura_res अणु
	काष्ठा	npa_aq_res_s	res;
	काष्ठा	npa_aura_s	aura_ctx;
	काष्ठा	npa_aura_s	ctx_mask;
पूर्ण;

/* NPA AQ result काष्ठाure क्रम init/पढ़ो/ग_लिखो of pool HW contexts */
काष्ठा npa_aq_pool_res अणु
	काष्ठा	npa_aq_res_s	res;
	काष्ठा	npa_pool_s	pool_ctx;
	काष्ठा	npa_pool_s	ctx_mask;
पूर्ण;

/* NIX Transmit schedulers */
क्रमागत nix_scheduler अणु
	NIX_TXSCH_LVL_SMQ = 0x0,
	NIX_TXSCH_LVL_MDQ = 0x0,
	NIX_TXSCH_LVL_TL4 = 0x1,
	NIX_TXSCH_LVL_TL3 = 0x2,
	NIX_TXSCH_LVL_TL2 = 0x3,
	NIX_TXSCH_LVL_TL1 = 0x4,
	NIX_TXSCH_LVL_CNT = 0x5,
पूर्ण;

#घोषणा TXSCH_RR_QTM_MAX		((1 << 24) - 1)
#घोषणा TXSCH_TL1_DFLT_RR_QTM		TXSCH_RR_QTM_MAX
#घोषणा TXSCH_TL1_DFLT_RR_PRIO		(0x1ull)
#घोषणा MAX_SCHED_WEIGHT		0xFF
#घोषणा DFLT_RR_WEIGHT			71
#घोषणा DFLT_RR_QTM	((DFLT_RR_WEIGHT * TXSCH_RR_QTM_MAX) \
			 / MAX_SCHED_WEIGHT)

/* Min/Max packet sizes, excluding FCS */
#घोषणा	NIC_HW_MIN_FRS			40
#घोषणा	NIC_HW_MAX_FRS			9212
#घोषणा	SDP_HW_MAX_FRS			65535
#घोषणा CN10K_LMAC_LINK_MAX_FRS		16380 /* 16k - FCS */
#घोषणा CN10K_LBK_LINK_MAX_FRS		65535 /* 64k */

/* NIX RX action operation*/
#घोषणा NIX_RX_ACTIONOP_DROP		(0x0ull)
#घोषणा NIX_RX_ACTIONOP_UCAST		(0x1ull)
#घोषणा NIX_RX_ACTIONOP_UCAST_IPSEC	(0x2ull)
#घोषणा NIX_RX_ACTIONOP_MCAST		(0x3ull)
#घोषणा NIX_RX_ACTIONOP_RSS		(0x4ull)
/* Use the RX action set in the शेष unicast entry */
#घोषणा NIX_RX_ACTION_DEFAULT		(0xfull)

/* NIX TX action operation*/
#घोषणा NIX_TX_ACTIONOP_DROP		(0x0ull)
#घोषणा NIX_TX_ACTIONOP_UCAST_DEFAULT	(0x1ull)
#घोषणा NIX_TX_ACTIONOP_UCAST_CHAN	(0x2ull)
#घोषणा NIX_TX_ACTIONOP_MCAST		(0x3ull)
#घोषणा NIX_TX_ACTIONOP_DROP_VIOL	(0x5ull)

#घोषणा NPC_MCAM_KEY_X1			0
#घोषणा NPC_MCAM_KEY_X2			1
#घोषणा NPC_MCAM_KEY_X4			2

#घोषणा NIX_INTFX_RX(a)			(0x0ull | (a) << 1)
#घोषणा NIX_INTFX_TX(a)			(0x1ull | (a) << 1)

/* Default पूर्णांकerfaces are NIX0_RX and NIX0_TX */
#घोषणा NIX_INTF_RX			NIX_INTFX_RX(0)
#घोषणा NIX_INTF_TX			NIX_INTFX_TX(0)

#घोषणा NIX_INTF_TYPE_CGX		0
#घोषणा NIX_INTF_TYPE_LBK		1

#घोषणा MAX_LMAC_PKIND			12
#घोषणा NIX_LINK_CGX_LMAC(a, b)		(0 + 4 * (a) + (b))
#घोषणा NIX_LINK_LBK(a)			(12 + (a))
#घोषणा NIX_CHAN_CGX_LMAC_CHX(a, b, c)	(0x800 + 0x100 * (a) + 0x10 * (b) + (c))
#घोषणा NIX_CHAN_LBK_CHX(a, b)		(0 + 0x100 * (a) + (b))
#घोषणा NIX_CHAN_SDP_CH_START		(0x700ull)

#घोषणा SDP_CHANNELS			256

/* NIX LSO क्रमmat indices.
 * As of now TSO is the only one using, so अटलally assigning indices.
 */
#घोषणा NIX_LSO_FORMAT_IDX_TSOV4	0
#घोषणा NIX_LSO_FORMAT_IDX_TSOV6	1

/* RSS info */
#घोषणा MAX_RSS_GROUPS			8
/* Group 0 has to be used in शेष pkt क्रमwarding MCAM entries
 * reserved क्रम NIXLFs. Groups 1-7 can be used क्रम RSS क्रम ntuple
 * filters.
 */
#घोषणा DEFAULT_RSS_CONTEXT_GROUP	0
#घोषणा MAX_RSS_INसूची_TBL_SIZE		256 /* 1 << Max adder bits */

/* NDC info */
क्रमागत ndc_idx_e अणु
	NIX0_RX = 0x0,
	NIX0_TX = 0x1,
	NPA0_U  = 0x2,
	NIX1_RX = 0x4,
	NIX1_TX = 0x5,
पूर्ण;

क्रमागत ndc_ctype_e अणु
	CACHING = 0x0,
	BYPASS = 0x1,
पूर्ण;

#घोषणा NDC_MAX_PORT 6
#घोषणा NDC_READ_TRANS 0
#घोषणा NDC_WRITE_TRANS 1

#पूर्ण_अगर /* COMMON_H */
