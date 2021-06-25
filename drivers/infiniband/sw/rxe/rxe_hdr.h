<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_HDR_H
#घोषणा RXE_HDR_H

/* extracted inक्रमmation about a packet carried in an sk_buff काष्ठा fits in
 * the skbuff cb array. Must be at most 48 bytes. stored in control block of
 * sk_buff क्रम received packets.
 */
काष्ठा rxe_pkt_info अणु
	काष्ठा rxe_dev		*rxe;		/* device that owns packet */
	काष्ठा rxe_qp		*qp;		/* qp that owns packet */
	काष्ठा rxe_send_wqe	*wqe;		/* send wqe */
	u8			*hdr;		/* poपूर्णांकs to bth */
	u32			mask;		/* useful info about pkt */
	u32			psn;		/* bth psn of packet */
	u16			pkey_index;	/* partition of pkt */
	u16			paylen;		/* length of bth - icrc */
	u8			port_num;	/* port pkt received on */
	u8			opcode;		/* bth opcode of packet */
पूर्ण;

/* Macros should be used only क्रम received skb */
अटल अंतरभूत काष्ठा rxe_pkt_info *SKB_TO_PKT(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा rxe_pkt_info) > माप(skb->cb));
	वापस (व्योम *)skb->cb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *PKT_TO_SKB(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस container_of((व्योम *)pkt, काष्ठा sk_buff, cb);
पूर्ण

/*
 * IBA header types and methods
 *
 * Some of these are क्रम reference and completeness only since
 * rxe करोes not currently support RD transport
 * most of this could be moved पूर्णांकo IB core. ib_pack.h has
 * part of this but is incomplete
 *
 * Header specअगरic routines to insert/extract values to/from headers
 * the routines that are named __hhh_(set_)fff() take a poपूर्णांकer to a
 * hhh header and get(set) the fff field. The routines named
 * hhh_(set_)fff take a packet info काष्ठा and find the
 * header and field based on the opcode in the packet.
 * Conversion to/from network byte order from cpu order is also करोne.
 */

#घोषणा RXE_ICRC_SIZE		(4)
#घोषणा RXE_MAX_HDR_LENGTH	(80)

/******************************************************************************
 * Base Transport Header
 ******************************************************************************/
काष्ठा rxe_bth अणु
	u8			opcode;
	u8			flags;
	__be16			pkey;
	__be32			qpn;
	__be32			apsn;
पूर्ण;

#घोषणा BTH_TVER		(0)
#घोषणा BTH_DEF_PKEY		(0xffff)

#घोषणा BTH_SE_MASK		(0x80)
#घोषणा BTH_MIG_MASK		(0x40)
#घोषणा BTH_PAD_MASK		(0x30)
#घोषणा BTH_TVER_MASK		(0x0f)
#घोषणा BTH_FECN_MASK		(0x80000000)
#घोषणा BTH_BECN_MASK		(0x40000000)
#घोषणा BTH_RESV6A_MASK		(0x3f000000)
#घोषणा BTH_QPN_MASK		(0x00ffffff)
#घोषणा BTH_ACK_MASK		(0x80000000)
#घोषणा BTH_RESV7_MASK		(0x7f000000)
#घोषणा BTH_PSN_MASK		(0x00ffffff)

अटल अंतरभूत u8 __bth_opcode(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस bth->opcode;
पूर्ण

अटल अंतरभूत व्योम __bth_set_opcode(व्योम *arg, u8 opcode)
अणु
	काष्ठा rxe_bth *bth = arg;

	bth->opcode = opcode;
पूर्ण

अटल अंतरभूत u8 __bth_se(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस 0 != (BTH_SE_MASK & bth->flags);
पूर्ण

अटल अंतरभूत व्योम __bth_set_se(व्योम *arg, पूर्णांक se)
अणु
	काष्ठा rxe_bth *bth = arg;

	अगर (se)
		bth->flags |= BTH_SE_MASK;
	अन्यथा
		bth->flags &= ~BTH_SE_MASK;
पूर्ण

अटल अंतरभूत u8 __bth_mig(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस 0 != (BTH_MIG_MASK & bth->flags);
पूर्ण

अटल अंतरभूत व्योम __bth_set_mig(व्योम *arg, u8 mig)
अणु
	काष्ठा rxe_bth *bth = arg;

	अगर (mig)
		bth->flags |= BTH_MIG_MASK;
	अन्यथा
		bth->flags &= ~BTH_MIG_MASK;
पूर्ण

अटल अंतरभूत u8 __bth_pad(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस (BTH_PAD_MASK & bth->flags) >> 4;
पूर्ण

अटल अंतरभूत व्योम __bth_set_pad(व्योम *arg, u8 pad)
अणु
	काष्ठा rxe_bth *bth = arg;

	bth->flags = (BTH_PAD_MASK & (pad << 4)) |
			(~BTH_PAD_MASK & bth->flags);
पूर्ण

अटल अंतरभूत u8 __bth_tver(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस BTH_TVER_MASK & bth->flags;
पूर्ण

अटल अंतरभूत व्योम __bth_set_tver(व्योम *arg, u8 tver)
अणु
	काष्ठा rxe_bth *bth = arg;

	bth->flags = (BTH_TVER_MASK & tver) |
			(~BTH_TVER_MASK & bth->flags);
पूर्ण

अटल अंतरभूत u16 __bth_pkey(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस be16_to_cpu(bth->pkey);
पूर्ण

अटल अंतरभूत व्योम __bth_set_pkey(व्योम *arg, u16 pkey)
अणु
	काष्ठा rxe_bth *bth = arg;

	bth->pkey = cpu_to_be16(pkey);
पूर्ण

अटल अंतरभूत u32 __bth_qpn(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस BTH_QPN_MASK & be32_to_cpu(bth->qpn);
पूर्ण

अटल अंतरभूत व्योम __bth_set_qpn(व्योम *arg, u32 qpn)
अणु
	काष्ठा rxe_bth *bth = arg;
	u32 resvqpn = be32_to_cpu(bth->qpn);

	bth->qpn = cpu_to_be32((BTH_QPN_MASK & qpn) |
			       (~BTH_QPN_MASK & resvqpn));
पूर्ण

अटल अंतरभूत पूर्णांक __bth_fecn(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस 0 != (cpu_to_be32(BTH_FECN_MASK) & bth->qpn);
पूर्ण

अटल अंतरभूत व्योम __bth_set_fecn(व्योम *arg, पूर्णांक fecn)
अणु
	काष्ठा rxe_bth *bth = arg;

	अगर (fecn)
		bth->qpn |= cpu_to_be32(BTH_FECN_MASK);
	अन्यथा
		bth->qpn &= ~cpu_to_be32(BTH_FECN_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक __bth_becn(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस 0 != (cpu_to_be32(BTH_BECN_MASK) & bth->qpn);
पूर्ण

अटल अंतरभूत व्योम __bth_set_becn(व्योम *arg, पूर्णांक becn)
अणु
	काष्ठा rxe_bth *bth = arg;

	अगर (becn)
		bth->qpn |= cpu_to_be32(BTH_BECN_MASK);
	अन्यथा
		bth->qpn &= ~cpu_to_be32(BTH_BECN_MASK);
पूर्ण

अटल अंतरभूत u8 __bth_resv6a(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस (BTH_RESV6A_MASK & be32_to_cpu(bth->qpn)) >> 24;
पूर्ण

अटल अंतरभूत व्योम __bth_set_resv6a(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	bth->qpn = cpu_to_be32(~BTH_RESV6A_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक __bth_ack(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस 0 != (cpu_to_be32(BTH_ACK_MASK) & bth->apsn);
पूर्ण

अटल अंतरभूत व्योम __bth_set_ack(व्योम *arg, पूर्णांक ack)
अणु
	काष्ठा rxe_bth *bth = arg;

	अगर (ack)
		bth->apsn |= cpu_to_be32(BTH_ACK_MASK);
	अन्यथा
		bth->apsn &= ~cpu_to_be32(BTH_ACK_MASK);
पूर्ण

अटल अंतरभूत व्योम __bth_set_resv7(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	bth->apsn &= ~cpu_to_be32(BTH_RESV7_MASK);
पूर्ण

अटल अंतरभूत u32 __bth_psn(व्योम *arg)
अणु
	काष्ठा rxe_bth *bth = arg;

	वापस BTH_PSN_MASK & be32_to_cpu(bth->apsn);
पूर्ण

अटल अंतरभूत व्योम __bth_set_psn(व्योम *arg, u32 psn)
अणु
	काष्ठा rxe_bth *bth = arg;
	u32 apsn = be32_to_cpu(bth->apsn);

	bth->apsn = cpu_to_be32((BTH_PSN_MASK & psn) |
			(~BTH_PSN_MASK & apsn));
पूर्ण

अटल अंतरभूत u8 bth_opcode(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_opcode(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_opcode(काष्ठा rxe_pkt_info *pkt, u8 opcode)
अणु
	__bth_set_opcode(pkt->hdr, opcode);
पूर्ण

अटल अंतरभूत u8 bth_se(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_se(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_se(काष्ठा rxe_pkt_info *pkt, पूर्णांक se)
अणु
	__bth_set_se(pkt->hdr, se);
पूर्ण

अटल अंतरभूत u8 bth_mig(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_mig(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_mig(काष्ठा rxe_pkt_info *pkt, u8 mig)
अणु
	__bth_set_mig(pkt->hdr, mig);
पूर्ण

अटल अंतरभूत u8 bth_pad(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_pad(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_pad(काष्ठा rxe_pkt_info *pkt, u8 pad)
अणु
	__bth_set_pad(pkt->hdr, pad);
पूर्ण

अटल अंतरभूत u8 bth_tver(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_tver(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_tver(काष्ठा rxe_pkt_info *pkt, u8 tver)
अणु
	__bth_set_tver(pkt->hdr, tver);
पूर्ण

अटल अंतरभूत u16 bth_pkey(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_pkey(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_pkey(काष्ठा rxe_pkt_info *pkt, u16 pkey)
अणु
	__bth_set_pkey(pkt->hdr, pkey);
पूर्ण

अटल अंतरभूत u32 bth_qpn(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_qpn(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_qpn(काष्ठा rxe_pkt_info *pkt, u32 qpn)
अणु
	__bth_set_qpn(pkt->hdr, qpn);
पूर्ण

अटल अंतरभूत पूर्णांक bth_fecn(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_fecn(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_fecn(काष्ठा rxe_pkt_info *pkt, पूर्णांक fecn)
अणु
	__bth_set_fecn(pkt->hdr, fecn);
पूर्ण

अटल अंतरभूत पूर्णांक bth_becn(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_becn(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_becn(काष्ठा rxe_pkt_info *pkt, पूर्णांक becn)
अणु
	__bth_set_becn(pkt->hdr, becn);
पूर्ण

अटल अंतरभूत u8 bth_resv6a(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_resv6a(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_resv6a(काष्ठा rxe_pkt_info *pkt)
अणु
	__bth_set_resv6a(pkt->hdr);
पूर्ण

अटल अंतरभूत पूर्णांक bth_ack(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_ack(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_ack(काष्ठा rxe_pkt_info *pkt, पूर्णांक ack)
अणु
	__bth_set_ack(pkt->hdr, ack);
पूर्ण

अटल अंतरभूत व्योम bth_set_resv7(काष्ठा rxe_pkt_info *pkt)
अणु
	__bth_set_resv7(pkt->hdr);
पूर्ण

अटल अंतरभूत u32 bth_psn(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __bth_psn(pkt->hdr);
पूर्ण

अटल अंतरभूत व्योम bth_set_psn(काष्ठा rxe_pkt_info *pkt, u32 psn)
अणु
	__bth_set_psn(pkt->hdr, psn);
पूर्ण

अटल अंतरभूत व्योम bth_init(काष्ठा rxe_pkt_info *pkt, u8 opcode, पूर्णांक se,
			    पूर्णांक mig, पूर्णांक pad, u16 pkey, u32 qpn, पूर्णांक ack_req,
			    u32 psn)
अणु
	काष्ठा rxe_bth *bth = (काष्ठा rxe_bth *)(pkt->hdr);

	bth->opcode = opcode;
	bth->flags = (pad << 4) & BTH_PAD_MASK;
	अगर (se)
		bth->flags |= BTH_SE_MASK;
	अगर (mig)
		bth->flags |= BTH_MIG_MASK;
	bth->pkey = cpu_to_be16(pkey);
	bth->qpn = cpu_to_be32(qpn & BTH_QPN_MASK);
	psn &= BTH_PSN_MASK;
	अगर (ack_req)
		psn |= BTH_ACK_MASK;
	bth->apsn = cpu_to_be32(psn);
पूर्ण

/******************************************************************************
 * Reliable Datagram Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_rdeth अणु
	__be32			een;
पूर्ण;

#घोषणा RDETH_EEN_MASK		(0x00ffffff)

अटल अंतरभूत u8 __rdeth_een(व्योम *arg)
अणु
	काष्ठा rxe_rdeth *rdeth = arg;

	वापस RDETH_EEN_MASK & be32_to_cpu(rdeth->een);
पूर्ण

अटल अंतरभूत व्योम __rdeth_set_een(व्योम *arg, u32 een)
अणु
	काष्ठा rxe_rdeth *rdeth = arg;

	rdeth->een = cpu_to_be32(RDETH_EEN_MASK & een);
पूर्ण

अटल अंतरभूत u8 rdeth_een(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __rdeth_een(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RDETH]);
पूर्ण

अटल अंतरभूत व्योम rdeth_set_een(काष्ठा rxe_pkt_info *pkt, u32 een)
अणु
	__rdeth_set_een(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RDETH], een);
पूर्ण

/******************************************************************************
 * Datagram Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_deth अणु
	__be32			qkey;
	__be32			sqp;
पूर्ण;

#घोषणा GSI_QKEY		(0x80010000)
#घोषणा DETH_SQP_MASK		(0x00ffffff)

अटल अंतरभूत u32 __deth_qkey(व्योम *arg)
अणु
	काष्ठा rxe_deth *deth = arg;

	वापस be32_to_cpu(deth->qkey);
पूर्ण

अटल अंतरभूत व्योम __deth_set_qkey(व्योम *arg, u32 qkey)
अणु
	काष्ठा rxe_deth *deth = arg;

	deth->qkey = cpu_to_be32(qkey);
पूर्ण

अटल अंतरभूत u32 __deth_sqp(व्योम *arg)
अणु
	काष्ठा rxe_deth *deth = arg;

	वापस DETH_SQP_MASK & be32_to_cpu(deth->sqp);
पूर्ण

अटल अंतरभूत व्योम __deth_set_sqp(व्योम *arg, u32 sqp)
अणु
	काष्ठा rxe_deth *deth = arg;

	deth->sqp = cpu_to_be32(DETH_SQP_MASK & sqp);
पूर्ण

अटल अंतरभूत u32 deth_qkey(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __deth_qkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_DETH]);
पूर्ण

अटल अंतरभूत व्योम deth_set_qkey(काष्ठा rxe_pkt_info *pkt, u32 qkey)
अणु
	__deth_set_qkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_DETH], qkey);
पूर्ण

अटल अंतरभूत u32 deth_sqp(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __deth_sqp(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_DETH]);
पूर्ण

अटल अंतरभूत व्योम deth_set_sqp(काष्ठा rxe_pkt_info *pkt, u32 sqp)
अणु
	__deth_set_sqp(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_DETH], sqp);
पूर्ण

/******************************************************************************
 * RDMA Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_reth अणु
	__be64			va;
	__be32			rkey;
	__be32			len;
पूर्ण;

अटल अंतरभूत u64 __reth_va(व्योम *arg)
अणु
	काष्ठा rxe_reth *reth = arg;

	वापस be64_to_cpu(reth->va);
पूर्ण

अटल अंतरभूत व्योम __reth_set_va(व्योम *arg, u64 va)
अणु
	काष्ठा rxe_reth *reth = arg;

	reth->va = cpu_to_be64(va);
पूर्ण

अटल अंतरभूत u32 __reth_rkey(व्योम *arg)
अणु
	काष्ठा rxe_reth *reth = arg;

	वापस be32_to_cpu(reth->rkey);
पूर्ण

अटल अंतरभूत व्योम __reth_set_rkey(व्योम *arg, u32 rkey)
अणु
	काष्ठा rxe_reth *reth = arg;

	reth->rkey = cpu_to_be32(rkey);
पूर्ण

अटल अंतरभूत u32 __reth_len(व्योम *arg)
अणु
	काष्ठा rxe_reth *reth = arg;

	वापस be32_to_cpu(reth->len);
पूर्ण

अटल अंतरभूत व्योम __reth_set_len(व्योम *arg, u32 len)
अणु
	काष्ठा rxe_reth *reth = arg;

	reth->len = cpu_to_be32(len);
पूर्ण

अटल अंतरभूत u64 reth_va(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __reth_va(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RETH]);
पूर्ण

अटल अंतरभूत व्योम reth_set_va(काष्ठा rxe_pkt_info *pkt, u64 va)
अणु
	__reth_set_va(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RETH], va);
पूर्ण

अटल अंतरभूत u32 reth_rkey(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __reth_rkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RETH]);
पूर्ण

अटल अंतरभूत व्योम reth_set_rkey(काष्ठा rxe_pkt_info *pkt, u32 rkey)
अणु
	__reth_set_rkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RETH], rkey);
पूर्ण

अटल अंतरभूत u32 reth_len(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __reth_len(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RETH]);
पूर्ण

अटल अंतरभूत व्योम reth_set_len(काष्ठा rxe_pkt_info *pkt, u32 len)
अणु
	__reth_set_len(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_RETH], len);
पूर्ण

/******************************************************************************
 * Atomic Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_aपंचांगeth अणु
	__be64			va;
	__be32			rkey;
	__be64			swap_add;
	__be64			comp;
पूर्ण __packed;

अटल अंतरभूत u64 __aपंचांगeth_va(व्योम *arg)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	वापस be64_to_cpu(aपंचांगeth->va);
पूर्ण

अटल अंतरभूत व्योम __aपंचांगeth_set_va(व्योम *arg, u64 va)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	aपंचांगeth->va = cpu_to_be64(va);
पूर्ण

अटल अंतरभूत u32 __aपंचांगeth_rkey(व्योम *arg)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	वापस be32_to_cpu(aपंचांगeth->rkey);
पूर्ण

अटल अंतरभूत व्योम __aपंचांगeth_set_rkey(व्योम *arg, u32 rkey)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	aपंचांगeth->rkey = cpu_to_be32(rkey);
पूर्ण

अटल अंतरभूत u64 __aपंचांगeth_swap_add(व्योम *arg)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	वापस be64_to_cpu(aपंचांगeth->swap_add);
पूर्ण

अटल अंतरभूत व्योम __aपंचांगeth_set_swap_add(व्योम *arg, u64 swap_add)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	aपंचांगeth->swap_add = cpu_to_be64(swap_add);
पूर्ण

अटल अंतरभूत u64 __aपंचांगeth_comp(व्योम *arg)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	वापस be64_to_cpu(aपंचांगeth->comp);
पूर्ण

अटल अंतरभूत व्योम __aपंचांगeth_set_comp(व्योम *arg, u64 comp)
अणु
	काष्ठा rxe_aपंचांगeth *aपंचांगeth = arg;

	aपंचांगeth->comp = cpu_to_be64(comp);
पूर्ण

अटल अंतरभूत u64 aपंचांगeth_va(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aपंचांगeth_va(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH]);
पूर्ण

अटल अंतरभूत व्योम aपंचांगeth_set_va(काष्ठा rxe_pkt_info *pkt, u64 va)
अणु
	__aपंचांगeth_set_va(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH], va);
पूर्ण

अटल अंतरभूत u32 aपंचांगeth_rkey(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aपंचांगeth_rkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH]);
पूर्ण

अटल अंतरभूत व्योम aपंचांगeth_set_rkey(काष्ठा rxe_pkt_info *pkt, u32 rkey)
अणु
	__aपंचांगeth_set_rkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH], rkey);
पूर्ण

अटल अंतरभूत u64 aपंचांगeth_swap_add(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aपंचांगeth_swap_add(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH]);
पूर्ण

अटल अंतरभूत व्योम aपंचांगeth_set_swap_add(काष्ठा rxe_pkt_info *pkt, u64 swap_add)
अणु
	__aपंचांगeth_set_swap_add(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH], swap_add);
पूर्ण

अटल अंतरभूत u64 aपंचांगeth_comp(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aपंचांगeth_comp(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH]);
पूर्ण

अटल अंतरभूत व्योम aपंचांगeth_set_comp(काष्ठा rxe_pkt_info *pkt, u64 comp)
अणु
	__aपंचांगeth_set_comp(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMETH], comp);
पूर्ण

/******************************************************************************
 * Ack Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_aeth अणु
	__be32			smsn;
पूर्ण;

#घोषणा AETH_SYN_MASK		(0xff000000)
#घोषणा AETH_MSN_MASK		(0x00ffffff)

क्रमागत aeth_syndrome अणु
	AETH_TYPE_MASK		= 0xe0,
	AETH_ACK		= 0x00,
	AETH_RNR_NAK		= 0x20,
	AETH_RSVD		= 0x40,
	AETH_NAK		= 0x60,
	AETH_ACK_UNLIMITED	= 0x1f,
	AETH_NAK_PSN_SEQ_ERROR	= 0x60,
	AETH_NAK_INVALID_REQ	= 0x61,
	AETH_NAK_REM_ACC_ERR	= 0x62,
	AETH_NAK_REM_OP_ERR	= 0x63,
	AETH_NAK_INV_RD_REQ	= 0x64,
पूर्ण;

अटल अंतरभूत u8 __aeth_syn(व्योम *arg)
अणु
	काष्ठा rxe_aeth *aeth = arg;

	वापस (AETH_SYN_MASK & be32_to_cpu(aeth->smsn)) >> 24;
पूर्ण

अटल अंतरभूत व्योम __aeth_set_syn(व्योम *arg, u8 syn)
अणु
	काष्ठा rxe_aeth *aeth = arg;
	u32 smsn = be32_to_cpu(aeth->smsn);

	aeth->smsn = cpu_to_be32((AETH_SYN_MASK & (syn << 24)) |
			 (~AETH_SYN_MASK & smsn));
पूर्ण

अटल अंतरभूत u32 __aeth_msn(व्योम *arg)
अणु
	काष्ठा rxe_aeth *aeth = arg;

	वापस AETH_MSN_MASK & be32_to_cpu(aeth->smsn);
पूर्ण

अटल अंतरभूत व्योम __aeth_set_msn(व्योम *arg, u32 msn)
अणु
	काष्ठा rxe_aeth *aeth = arg;
	u32 smsn = be32_to_cpu(aeth->smsn);

	aeth->smsn = cpu_to_be32((AETH_MSN_MASK & msn) |
			 (~AETH_MSN_MASK & smsn));
पूर्ण

अटल अंतरभूत u8 aeth_syn(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aeth_syn(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_AETH]);
पूर्ण

अटल अंतरभूत व्योम aeth_set_syn(काष्ठा rxe_pkt_info *pkt, u8 syn)
अणु
	__aeth_set_syn(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_AETH], syn);
पूर्ण

अटल अंतरभूत u32 aeth_msn(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aeth_msn(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_AETH]);
पूर्ण

अटल अंतरभूत व्योम aeth_set_msn(काष्ठा rxe_pkt_info *pkt, u32 msn)
अणु
	__aeth_set_msn(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_AETH], msn);
पूर्ण

/******************************************************************************
 * Atomic Ack Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_aपंचांगack अणु
	__be64			orig;
पूर्ण;

अटल अंतरभूत u64 __aपंचांगack_orig(व्योम *arg)
अणु
	काष्ठा rxe_aपंचांगack *aपंचांगack = arg;

	वापस be64_to_cpu(aपंचांगack->orig);
पूर्ण

अटल अंतरभूत व्योम __aपंचांगack_set_orig(व्योम *arg, u64 orig)
अणु
	काष्ठा rxe_aपंचांगack *aपंचांगack = arg;

	aपंचांगack->orig = cpu_to_be64(orig);
पूर्ण

अटल अंतरभूत u64 aपंचांगack_orig(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __aपंचांगack_orig(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMACK]);
पूर्ण

अटल अंतरभूत व्योम aपंचांगack_set_orig(काष्ठा rxe_pkt_info *pkt, u64 orig)
अणु
	__aपंचांगack_set_orig(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_ATMACK], orig);
पूर्ण

/******************************************************************************
 * Immediate Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_immdt अणु
	__be32			imm;
पूर्ण;

अटल अंतरभूत __be32 __immdt_imm(व्योम *arg)
अणु
	काष्ठा rxe_immdt *immdt = arg;

	वापस immdt->imm;
पूर्ण

अटल अंतरभूत व्योम __immdt_set_imm(व्योम *arg, __be32 imm)
अणु
	काष्ठा rxe_immdt *immdt = arg;

	immdt->imm = imm;
पूर्ण

अटल अंतरभूत __be32 immdt_imm(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __immdt_imm(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_IMMDT]);
पूर्ण

अटल अंतरभूत व्योम immdt_set_imm(काष्ठा rxe_pkt_info *pkt, __be32 imm)
अणु
	__immdt_set_imm(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_IMMDT], imm);
पूर्ण

/******************************************************************************
 * Invalidate Extended Transport Header
 ******************************************************************************/
काष्ठा rxe_ieth अणु
	__be32			rkey;
पूर्ण;

अटल अंतरभूत u32 __ieth_rkey(व्योम *arg)
अणु
	काष्ठा rxe_ieth *ieth = arg;

	वापस be32_to_cpu(ieth->rkey);
पूर्ण

अटल अंतरभूत व्योम __ieth_set_rkey(व्योम *arg, u32 rkey)
अणु
	काष्ठा rxe_ieth *ieth = arg;

	ieth->rkey = cpu_to_be32(rkey);
पूर्ण

अटल अंतरभूत u32 ieth_rkey(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस __ieth_rkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_IETH]);
पूर्ण

अटल अंतरभूत व्योम ieth_set_rkey(काष्ठा rxe_pkt_info *pkt, u32 rkey)
अणु
	__ieth_set_rkey(pkt->hdr +
		rxe_opcode[pkt->opcode].offset[RXE_IETH], rkey);
पूर्ण

क्रमागत rxe_hdr_length अणु
	RXE_BTH_BYTES		= माप(काष्ठा rxe_bth),
	RXE_DETH_BYTES		= माप(काष्ठा rxe_deth),
	RXE_IMMDT_BYTES		= माप(काष्ठा rxe_immdt),
	RXE_RETH_BYTES		= माप(काष्ठा rxe_reth),
	RXE_AETH_BYTES		= माप(काष्ठा rxe_aeth),
	RXE_ATMACK_BYTES	= माप(काष्ठा rxe_aपंचांगack),
	RXE_ATMETH_BYTES	= माप(काष्ठा rxe_aपंचांगeth),
	RXE_IETH_BYTES		= माप(काष्ठा rxe_ieth),
	RXE_RDETH_BYTES		= माप(काष्ठा rxe_rdeth),
पूर्ण;

अटल अंतरभूत माप_प्रकार header_size(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस rxe_opcode[pkt->opcode].length;
पूर्ण

अटल अंतरभूत व्योम *payload_addr(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस pkt->hdr + rxe_opcode[pkt->opcode].offset[RXE_PAYLOAD];
पूर्ण

अटल अंतरभूत माप_प्रकार payload_size(काष्ठा rxe_pkt_info *pkt)
अणु
	वापस pkt->paylen - rxe_opcode[pkt->opcode].offset[RXE_PAYLOAD]
		- bth_pad(pkt) - RXE_ICRC_SIZE;
पूर्ण

#पूर्ण_अगर /* RXE_HDR_H */
