<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 */

#अगर_अघोषित IB_HDRS_H
#घोषणा IB_HDRS_H

#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <rdma/ib_verbs.h>

#घोषणा IB_SEQ_NAK	(3 << 29)

/* AETH NAK opcode values */
#घोषणा IB_RNR_NAK                      0x20
#घोषणा IB_NAK_PSN_ERROR                0x60
#घोषणा IB_NAK_INVALID_REQUEST          0x61
#घोषणा IB_NAK_REMOTE_ACCESS_ERROR      0x62
#घोषणा IB_NAK_REMOTE_OPERATIONAL_ERROR 0x63
#घोषणा IB_NAK_INVALID_RD_REQUEST       0x64

#घोषणा IB_BTH_REQ_ACK		BIT(31)
#घोषणा IB_BTH_SOLICITED	BIT(23)
#घोषणा IB_BTH_MIG_REQ		BIT(22)

#घोषणा IB_GRH_VERSION		6
#घोषणा IB_GRH_VERSION_MASK	0xF
#घोषणा IB_GRH_VERSION_SHIFT	28
#घोषणा IB_GRH_TCLASS_MASK	0xFF
#घोषणा IB_GRH_TCLASS_SHIFT	20
#घोषणा IB_GRH_FLOW_MASK	0xFFFFF
#घोषणा IB_GRH_FLOW_SHIFT	0
#घोषणा IB_GRH_NEXT_HDR		0x1B
#घोषणा IB_FECN_SHIFT 31
#घोषणा IB_FECN_MASK 1
#घोषणा IB_FECN_SMASK BIT(IB_FECN_SHIFT)
#घोषणा IB_BECN_SHIFT 30
#घोषणा IB_BECN_MASK 1
#घोषणा IB_BECN_SMASK BIT(IB_BECN_SHIFT)

#घोषणा IB_AETH_CREDIT_SHIFT	24
#घोषणा IB_AETH_CREDIT_MASK	0x1F
#घोषणा IB_AETH_CREDIT_INVAL	0x1F
#घोषणा IB_AETH_NAK_SHIFT	29
#घोषणा IB_MSN_MASK		0xFFFFFF

काष्ठा ib_reth अणु
	__be64 vaddr;        /* potentially unaligned */
	__be32 rkey;
	__be32 length;
पूर्ण __packed;

काष्ठा ib_atomic_eth अणु
	__be64 vaddr;        /* potentially unaligned */
	__be32 rkey;
	__be64 swap_data;    /* potentially unaligned */
	__be64 compare_data; /* potentially unaligned */
पूर्ण __packed;

#समावेश <rdma/tid_rdma_defs.h>

जोड़ ib_ehdrs अणु
	काष्ठा अणु
		__be32 deth[2];
		__be32 imm_data;
	पूर्ण ud;
	काष्ठा अणु
		काष्ठा ib_reth reth;
		__be32 imm_data;
	पूर्ण rc;
	काष्ठा अणु
		__be32 aeth;
		__be64 atomic_ack_eth; /* potentially unaligned */
	पूर्ण __packed at;
	__be32 imm_data;
	__be32 aeth;
	__be32 ieth;
	काष्ठा ib_atomic_eth atomic_eth;
	/* TID RDMA headers */
	जोड़ अणु
		काष्ठा tid_rdma_पढ़ो_req r_req;
		काष्ठा tid_rdma_पढ़ो_resp r_rsp;
		काष्ठा tid_rdma_ग_लिखो_req w_req;
		काष्ठा tid_rdma_ग_लिखो_resp w_rsp;
		काष्ठा tid_rdma_ग_लिखो_data w_data;
		काष्ठा tid_rdma_resync resync;
		काष्ठा tid_rdma_ack ack;
	पूर्ण tid_rdma;
पूर्ण  __packed;

काष्ठा ib_other_headers अणु
	__be32 bth[3];
	जोड़ ib_ehdrs u;
पूर्ण __packed;

काष्ठा ib_header अणु
	__be16 lrh[4];
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ib_grh grh;
			काष्ठा ib_other_headers oth;
		पूर्ण l;
		काष्ठा ib_other_headers oth;
	पूर्ण u;
पूर्ण __packed;

/* accessors क्रम unaligned __be64 items */

अटल अंतरभूत u64 ib_u64_get(__be64 *p)
अणु
	वापस get_unaligned_be64(p);
पूर्ण

अटल अंतरभूत व्योम ib_u64_put(u64 val, __be64 *p)
अणु
	put_unaligned_be64(val, p);
पूर्ण

अटल अंतरभूत u64 get_ib_reth_vaddr(काष्ठा ib_reth *reth)
अणु
	वापस ib_u64_get(&reth->vaddr);
पूर्ण

अटल अंतरभूत व्योम put_ib_reth_vaddr(u64 val, काष्ठा ib_reth *reth)
अणु
	ib_u64_put(val, &reth->vaddr);
पूर्ण

अटल अंतरभूत u64 get_ib_ateth_vaddr(काष्ठा ib_atomic_eth *ateth)
अणु
	वापस ib_u64_get(&ateth->vaddr);
पूर्ण

अटल अंतरभूत व्योम put_ib_ateth_vaddr(u64 val, काष्ठा ib_atomic_eth *ateth)
अणु
	ib_u64_put(val, &ateth->vaddr);
पूर्ण

अटल अंतरभूत u64 get_ib_ateth_swap(काष्ठा ib_atomic_eth *ateth)
अणु
	वापस ib_u64_get(&ateth->swap_data);
पूर्ण

अटल अंतरभूत व्योम put_ib_ateth_swap(u64 val, काष्ठा ib_atomic_eth *ateth)
अणु
	ib_u64_put(val, &ateth->swap_data);
पूर्ण

अटल अंतरभूत u64 get_ib_ateth_compare(काष्ठा ib_atomic_eth *ateth)
अणु
	वापस ib_u64_get(&ateth->compare_data);
पूर्ण

अटल अंतरभूत व्योम put_ib_ateth_compare(u64 val, काष्ठा ib_atomic_eth *ateth)
अणु
	ib_u64_put(val, &ateth->compare_data);
पूर्ण

/*
 * 9B/IB Packet Format
 */
#घोषणा IB_LNH_MASK		3
#घोषणा IB_SC_MASK		0xf
#घोषणा IB_SC_SHIFT		12
#घोषणा IB_SC5_MASK		0x10
#घोषणा IB_SL_MASK		0xf
#घोषणा IB_SL_SHIFT		4
#घोषणा IB_SL_SHIFT		4
#घोषणा IB_LVER_MASK	0xf
#घोषणा IB_LVER_SHIFT	8

अटल अंतरभूत u8 ib_get_lnh(काष्ठा ib_header *hdr)
अणु
	वापस (be16_to_cpu(hdr->lrh[0]) & IB_LNH_MASK);
पूर्ण

अटल अंतरभूत u8 ib_get_sc(काष्ठा ib_header *hdr)
अणु
	वापस ((be16_to_cpu(hdr->lrh[0]) >> IB_SC_SHIFT) & IB_SC_MASK);
पूर्ण

अटल अंतरभूत bool ib_is_sc5(u16 sc5)
अणु
	वापस !!(sc5 & IB_SC5_MASK);
पूर्ण

अटल अंतरभूत u8 ib_get_sl(काष्ठा ib_header *hdr)
अणु
	वापस ((be16_to_cpu(hdr->lrh[0]) >> IB_SL_SHIFT) & IB_SL_MASK);
पूर्ण

अटल अंतरभूत u16 ib_get_dlid(काष्ठा ib_header *hdr)
अणु
	वापस (be16_to_cpu(hdr->lrh[1]));
पूर्ण

अटल अंतरभूत u16 ib_get_slid(काष्ठा ib_header *hdr)
अणु
	वापस (be16_to_cpu(hdr->lrh[3]));
पूर्ण

अटल अंतरभूत u8 ib_get_lver(काष्ठा ib_header *hdr)
अणु
	वापस (u8)((be16_to_cpu(hdr->lrh[0]) >> IB_LVER_SHIFT) &
		   IB_LVER_MASK);
पूर्ण

अटल अंतरभूत u16 ib_get_len(काष्ठा ib_header *hdr)
अणु
	वापस (u16)(be16_to_cpu(hdr->lrh[2]));
पूर्ण

अटल अंतरभूत u32 ib_get_qkey(काष्ठा ib_other_headers *ohdr)
अणु
	वापस be32_to_cpu(ohdr->u.ud.deth[0]);
पूर्ण

अटल अंतरभूत u32 ib_get_sqpn(काष्ठा ib_other_headers *ohdr)
अणु
	वापस ((be32_to_cpu(ohdr->u.ud.deth[1])) & IB_QPN_MASK);
पूर्ण

/*
 * BTH
 */
#घोषणा IB_BTH_OPCODE_MASK	0xff
#घोषणा IB_BTH_OPCODE_SHIFT	24
#घोषणा IB_BTH_PAD_MASK	3
#घोषणा IB_BTH_PKEY_MASK	0xffff
#घोषणा IB_BTH_PAD_SHIFT	20
#घोषणा IB_BTH_A_MASK		1
#घोषणा IB_BTH_A_SHIFT		31
#घोषणा IB_BTH_M_MASK		1
#घोषणा IB_BTH_M_SHIFT		22
#घोषणा IB_BTH_SE_MASK		1
#घोषणा IB_BTH_SE_SHIFT	23
#घोषणा IB_BTH_TVER_MASK	0xf
#घोषणा IB_BTH_TVER_SHIFT	16

अटल अंतरभूत u8 ib_bth_get_pad(काष्ठा ib_other_headers *ohdr)
अणु
	वापस ((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_PAD_SHIFT) &
		   IB_BTH_PAD_MASK);
पूर्ण

अटल अंतरभूत u16 ib_bth_get_pkey(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (be32_to_cpu(ohdr->bth[0]) & IB_BTH_PKEY_MASK);
पूर्ण

अटल अंतरभूत u8 ib_bth_get_opcode(काष्ठा ib_other_headers *ohdr)
अणु
	वापस ((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_OPCODE_SHIFT) &
		   IB_BTH_OPCODE_MASK);
पूर्ण

अटल अंतरभूत u8 ib_bth_get_ackreq(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u8)((be32_to_cpu(ohdr->bth[2]) >> IB_BTH_A_SHIFT) &
		   IB_BTH_A_MASK);
पूर्ण

अटल अंतरभूत u8 ib_bth_get_migreq(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u8)((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_M_SHIFT) &
		    IB_BTH_M_MASK);
पूर्ण

अटल अंतरभूत u8 ib_bth_get_se(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u8)((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_SE_SHIFT) &
		    IB_BTH_SE_MASK);
पूर्ण

अटल अंतरभूत u32 ib_bth_get_psn(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u32)(be32_to_cpu(ohdr->bth[2]));
पूर्ण

अटल अंतरभूत u32 ib_bth_get_qpn(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u32)((be32_to_cpu(ohdr->bth[1])) & IB_QPN_MASK);
पूर्ण

अटल अंतरभूत bool ib_bth_get_becn(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (ohdr->bth[1]) & cpu_to_be32(IB_BECN_SMASK);
पूर्ण

अटल अंतरभूत bool ib_bth_get_fecn(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (ohdr->bth[1]) & cpu_to_be32(IB_FECN_SMASK);
पूर्ण

अटल अंतरभूत u8 ib_bth_get_tver(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u8)((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_TVER_SHIFT)  &
		    IB_BTH_TVER_MASK);
पूर्ण

अटल अंतरभूत bool ib_bth_is_solicited(काष्ठा ib_other_headers *ohdr)
अणु
	वापस ohdr->bth[0] & cpu_to_be32(IB_BTH_SOLICITED);
पूर्ण

अटल अंतरभूत bool ib_bth_is_migration(काष्ठा ib_other_headers *ohdr)
अणु
	वापस ohdr->bth[0] & cpu_to_be32(IB_BTH_MIG_REQ);
पूर्ण
#पूर्ण_अगर                          /* IB_HDRS_H */
