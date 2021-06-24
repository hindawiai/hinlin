<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

/* File क्रम पूर्णांकerrupt macros and functions */

#अगर_अघोषित __BNA_HW_DEFS_H__
#घोषणा __BNA_HW_DEFS_H__

#समावेश "bfi_reg.h"

/* SW imposed limits */

#घोषणा BFI_ENET_DEF_TXQ		1
#घोषणा BFI_ENET_DEF_RXP		1
#घोषणा BFI_ENET_DEF_UCAM		1
#घोषणा BFI_ENET_DEF_RITSZ		1

#घोषणा BFI_ENET_MAX_MCAM		256

#घोषणा BFI_INVALID_RID			-1

#घोषणा BFI_IBIDX_SIZE			4

#घोषणा BFI_VLAN_WORD_SHIFT		5	/* 32 bits */
#घोषणा BFI_VLAN_WORD_MASK		0x1F
#घोषणा BFI_VLAN_BLOCK_SHIFT		9	/* 512 bits */
#घोषणा BFI_VLAN_BMASK_ALL		0xFF

#घोषणा BFI_COALESCING_TIMER_UNIT	5	/* 5us */
#घोषणा BFI_MAX_COALESCING_TIMEO	0xFF	/* in 5us units */
#घोषणा BFI_MAX_INTERPKT_COUNT		0xFF
#घोषणा BFI_MAX_INTERPKT_TIMEO		0xF	/* in 0.5us units */
#घोषणा BFI_TX_COALESCING_TIMEO		20	/* 20 * 5 = 100us */
#घोषणा BFI_TX_INTERPKT_COUNT		12	/* Pkt Cnt = 12 */
#घोषणा BFI_TX_INTERPKT_TIMEO		15	/* 15 * 0.5 = 7.5us */
#घोषणा	BFI_RX_COALESCING_TIMEO		12	/* 12 * 5 = 60us */
#घोषणा	BFI_RX_INTERPKT_COUNT		6	/* Pkt Cnt = 6 */
#घोषणा	BFI_RX_INTERPKT_TIMEO		3	/* 3 * 0.5 = 1.5us */

#घोषणा BFI_TXQ_WI_SIZE			64	/* bytes */
#घोषणा BFI_RXQ_WI_SIZE			8	/* bytes */
#घोषणा BFI_CQ_WI_SIZE			16	/* bytes */
#घोषणा BFI_TX_MAX_WRR_QUOTA		0xFFF

#घोषणा BFI_TX_MAX_VECTORS_PER_WI	4
#घोषणा BFI_TX_MAX_VECTORS_PER_PKT	0xFF
#घोषणा BFI_TX_MAX_DATA_PER_VECTOR	0xFFFF
#घोषणा BFI_TX_MAX_DATA_PER_PKT		0xFFFFFF

/* Small Q buffer size */
#घोषणा BFI_SMALL_RXBUF_SIZE		128

#घोषणा BFI_TX_MAX_PRIO			8
#घोषणा BFI_TX_PRIO_MAP_ALL		0xFF

/*
 *
 * Register definitions and macros
 *
 */

#घोषणा BNA_PCI_REG_CT_ADDRSZ		(0x40000)

#घोषणा ct_reg_addr_init(_bna, _pcidev)					\
अणु									\
	काष्ठा bna_reg_offset reg_offset[] =				\
	अणुअणुHOSTFN0_INT_STATUS, HOSTFN0_INT_MSKपूर्ण,				\
	 अणुHOSTFN1_INT_STATUS, HOSTFN1_INT_MSKपूर्ण,				\
	 अणुHOSTFN2_INT_STATUS, HOSTFN2_INT_MSKपूर्ण,				\
	 अणुHOSTFN3_INT_STATUS, HOSTFN3_INT_MSKपूर्ण पूर्ण;			\
									\
	(_bna)->regs.fn_पूर्णांक_status = (_pcidev)->pci_bar_kva +		\
				reg_offset[(_pcidev)->pci_func].fn_पूर्णांक_status;\
	(_bna)->regs.fn_पूर्णांक_mask = (_pcidev)->pci_bar_kva +		\
				reg_offset[(_pcidev)->pci_func].fn_पूर्णांक_mask;\
पूर्ण

#घोषणा ct_bit_defn_init(_bna, _pcidev)					\
अणु									\
	(_bna)->bits.mbox_status_bits = (__HFN_INT_MBOX_LPU0 |		\
					__HFN_INT_MBOX_LPU1);		\
	(_bna)->bits.mbox_mask_bits = (__HFN_INT_MBOX_LPU0 |		\
					__HFN_INT_MBOX_LPU1);		\
	(_bna)->bits.error_status_bits = (__HFN_INT_ERR_MASK);		\
	(_bna)->bits.error_mask_bits = (__HFN_INT_ERR_MASK);		\
	(_bna)->bits.halt_status_bits = __HFN_INT_LL_HALT;		\
	(_bna)->bits.halt_mask_bits = __HFN_INT_LL_HALT;		\
पूर्ण

#घोषणा ct2_reg_addr_init(_bna, _pcidev)				\
अणु									\
	(_bna)->regs.fn_पूर्णांक_status = (_pcidev)->pci_bar_kva +		\
				CT2_HOSTFN_INT_STATUS;			\
	(_bna)->regs.fn_पूर्णांक_mask = (_pcidev)->pci_bar_kva +		\
				CT2_HOSTFN_INTR_MASK;			\
पूर्ण

#घोषणा ct2_bit_defn_init(_bna, _pcidev)				\
अणु									\
	(_bna)->bits.mbox_status_bits = (__HFN_INT_MBOX_LPU0_CT2 |	\
					__HFN_INT_MBOX_LPU1_CT2);	\
	(_bna)->bits.mbox_mask_bits = (__HFN_INT_MBOX_LPU0_CT2 |	\
					__HFN_INT_MBOX_LPU1_CT2);	\
	(_bna)->bits.error_status_bits = (__HFN_INT_ERR_MASK_CT2);	\
	(_bna)->bits.error_mask_bits = (__HFN_INT_ERR_MASK_CT2);	\
	(_bna)->bits.halt_status_bits = __HFN_INT_CPQ_HALT_CT2;		\
	(_bna)->bits.halt_mask_bits = __HFN_INT_CPQ_HALT_CT2;		\
पूर्ण

#घोषणा bna_reg_addr_init(_bna, _pcidev)				\
अणु									\
	चयन ((_pcidev)->device_id) अणु					\
	हाल PCI_DEVICE_ID_BROCADE_CT:					\
		ct_reg_addr_init((_bna), (_pcidev));			\
		ct_bit_defn_init((_bna), (_pcidev));			\
		अवरोध;							\
	हाल BFA_PCI_DEVICE_ID_CT2:					\
		ct2_reg_addr_init((_bna), (_pcidev));			\
		ct2_bit_defn_init((_bna), (_pcidev));			\
		अवरोध;							\
	पूर्ण								\
पूर्ण

#घोषणा bna_port_id_get(_bna) ((_bna)->ioceth.ioc.port_id)

/*  Interrupt related bits, flags and macros  */

#घोषणा IB_STATUS_BITS		0x0000ffff

#घोषणा BNA_IS_MBOX_INTR(_bna, _पूर्णांकr_status)				\
	((_पूर्णांकr_status) & (_bna)->bits.mbox_status_bits)

#घोषणा BNA_IS_HALT_INTR(_bna, _पूर्णांकr_status)				\
	((_पूर्णांकr_status) & (_bna)->bits.halt_status_bits)

#घोषणा BNA_IS_ERR_INTR(_bna, _पूर्णांकr_status)	\
	((_पूर्णांकr_status) & (_bna)->bits.error_status_bits)

#घोषणा BNA_IS_MBOX_ERR_INTR(_bna, _पूर्णांकr_status)	\
	(BNA_IS_MBOX_INTR(_bna, _पूर्णांकr_status) |		\
	BNA_IS_ERR_INTR(_bna, _पूर्णांकr_status))

#घोषणा BNA_IS_INTX_DATA_INTR(_पूर्णांकr_status)		\
		((_पूर्णांकr_status) & IB_STATUS_BITS)

#घोषणा bna_halt_clear(_bna)						\
करो अणु									\
	u32 init_halt;						\
	init_halt = पढ़ोl((_bna)->ioceth.ioc.ioc_regs.ll_halt);	\
	init_halt &= ~__FW_INIT_HALT_P;					\
	ग_लिखोl(init_halt, (_bna)->ioceth.ioc.ioc_regs.ll_halt);	\
	init_halt = पढ़ोl((_bna)->ioceth.ioc.ioc_regs.ll_halt);	\
पूर्ण जबतक (0)

#घोषणा bna_पूर्णांकx_disable(_bna, _cur_mask)				\
अणु									\
	(_cur_mask) = पढ़ोl((_bna)->regs.fn_पूर्णांक_mask);		\
	ग_लिखोl(0xffffffff, (_bna)->regs.fn_पूर्णांक_mask);		\
पूर्ण

#घोषणा bna_पूर्णांकx_enable(bna, new_mask)					\
	ग_लिखोl((new_mask), (bna)->regs.fn_पूर्णांक_mask)
#घोषणा bna_mbox_पूर्णांकr_disable(bna)					\
करो अणु									\
	u32 mask;							\
	mask = पढ़ोl((bna)->regs.fn_पूर्णांक_mask);				\
	ग_लिखोl((mask | (bna)->bits.mbox_mask_bits |			\
		(bna)->bits.error_mask_bits), (bna)->regs.fn_पूर्णांक_mask); \
	mask = पढ़ोl((bna)->regs.fn_पूर्णांक_mask);				\
पूर्ण जबतक (0)

#घोषणा bna_mbox_पूर्णांकr_enable(bna)					\
करो अणु									\
	u32 mask;							\
	mask = पढ़ोl((bna)->regs.fn_पूर्णांक_mask);				\
	ग_लिखोl((mask & ~((bna)->bits.mbox_mask_bits |			\
		(bna)->bits.error_mask_bits)), (bna)->regs.fn_पूर्णांक_mask);\
	mask = पढ़ोl((bna)->regs.fn_पूर्णांक_mask);				\
पूर्ण जबतक (0)

#घोषणा bna_पूर्णांकr_status_get(_bna, _status)				\
अणु									\
	(_status) = पढ़ोl((_bna)->regs.fn_पूर्णांक_status);			\
	अगर (_status) अणु							\
		ग_लिखोl(((_status) & ~(_bna)->bits.mbox_status_bits),	\
			(_bna)->regs.fn_पूर्णांक_status);			\
	पूर्ण								\
पूर्ण

/*
 * MAX ACK EVENTS : No. of acks that can be accumulated in driver,
 * beक्रमe acking to h/w. The no. of bits is 16 in the करोorbell रेजिस्टर,
 * however we keep this limited to 15 bits.
 * This is because around the edge of 64K boundary (16 bits), one
 * single poll can make the accumulated ACK counter cross the 64K boundary,
 * causing problems, when we try to ack with a value greater than 64K.
 * 15 bits (32K) should  be large enough to accumulate, anyways, and the max.
 * acked events to h/w can be (32K + max poll weight) (currently 64).
 */
#घोषणा BNA_IB_MAX_ACK_EVENTS		BIT(15)

/* These macros build the data portion of the TxQ/RxQ करोorbell */
#घोषणा BNA_DOORBELL_Q_PRD_IDX(_pi)	(0x80000000 | (_pi))
#घोषणा BNA_DOORBELL_Q_STOP		(0x40000000)

/* These macros build the data portion of the IB करोorbell */
#घोषणा BNA_DOORBELL_IB_INT_ACK(_समयout, _events)			\
	(0x80000000 | ((_समयout) << 16) | (_events))
#घोषणा BNA_DOORBELL_IB_INT_DISABLE	(0x40000000)

/* Set the coalescing समयr क्रम the given ib */
#घोषणा bna_ib_coalescing_समयr_set(_i_dbell, _cls_समयr)		\
	((_i_dbell)->करोorbell_ack = BNA_DOORBELL_IB_INT_ACK((_cls_समयr), 0))

/* Acks 'events' # of events क्रम a given ib जबतक disabling पूर्णांकerrupts */
#घोषणा bna_ib_ack_disable_irq(_i_dbell, _events)			\
	(ग_लिखोl(BNA_DOORBELL_IB_INT_ACK(0, (_events)),			\
		(_i_dbell)->करोorbell_addr))

/* Acks 'events' # of events क्रम a given ib */
#घोषणा bna_ib_ack(_i_dbell, _events)					\
	(ग_लिखोl(((_i_dbell)->करोorbell_ack | (_events)),		\
		(_i_dbell)->करोorbell_addr))

#घोषणा bna_ib_start(_bna, _ib, _is_regular)				\
अणु									\
	u32 पूर्णांकx_mask;						\
	काष्ठा bna_ib *ib = _ib;					\
	अगर ((ib->पूर्णांकr_type == BNA_INTR_T_INTX)) अणु			\
		bna_पूर्णांकx_disable((_bna), पूर्णांकx_mask);			\
		पूर्णांकx_mask &= ~(ib->पूर्णांकr_vector);			\
		bna_पूर्णांकx_enable((_bna), पूर्णांकx_mask);			\
	पूर्ण								\
	bna_ib_coalescing_समयr_set(&ib->करोor_bell,			\
			ib->coalescing_समयo);				\
	अगर (_is_regular)						\
		bna_ib_ack(&ib->करोor_bell, 0);				\
पूर्ण

#घोषणा bna_ib_stop(_bna, _ib)						\
अणु									\
	u32 पूर्णांकx_mask;						\
	काष्ठा bna_ib *ib = _ib;					\
	ग_लिखोl(BNA_DOORBELL_IB_INT_DISABLE,				\
		ib->करोor_bell.करोorbell_addr);				\
	अगर (ib->पूर्णांकr_type == BNA_INTR_T_INTX) अणु				\
		bna_पूर्णांकx_disable((_bna), पूर्णांकx_mask);			\
		पूर्णांकx_mask |= ib->पूर्णांकr_vector;				\
		bna_पूर्णांकx_enable((_bna), पूर्णांकx_mask);			\
	पूर्ण								\
पूर्ण

#घोषणा bna_txq_prod_indx_करोorbell(_tcb)				\
	(ग_लिखोl(BNA_DOORBELL_Q_PRD_IDX((_tcb)->producer_index),		\
		(_tcb)->q_dbell))

#घोषणा bna_rxq_prod_indx_करोorbell(_rcb)				\
	(ग_लिखोl(BNA_DOORBELL_Q_PRD_IDX((_rcb)->producer_index),		\
		(_rcb)->q_dbell))

/* TxQ, RxQ, CQ related bits, offsets, macros */

/* TxQ Entry Opcodes */
#घोषणा BNA_TXQ_WI_SEND			(0x402)	/* Single Frame Transmission */
#घोषणा BNA_TXQ_WI_SEND_LSO		(0x403)	/* Multi-Frame Transmission */
#घोषणा BNA_TXQ_WI_EXTENSION		(0x104)	/* Extension WI */

/* TxQ Entry Control Flags */
#घोषणा BNA_TXQ_WI_CF_FCOE_CRC		BIT(8)
#घोषणा BNA_TXQ_WI_CF_IPID_MODE		BIT(5)
#घोषणा BNA_TXQ_WI_CF_INS_PRIO		BIT(4)
#घोषणा BNA_TXQ_WI_CF_INS_VLAN		BIT(3)
#घोषणा BNA_TXQ_WI_CF_UDP_CKSUM		BIT(2)
#घोषणा BNA_TXQ_WI_CF_TCP_CKSUM		BIT(1)
#घोषणा BNA_TXQ_WI_CF_IP_CKSUM		BIT(0)

#घोषणा BNA_TXQ_WI_L4_HDR_N_OFFSET(_hdr_size, _offset) \
		(((_hdr_size) << 10) | ((_offset) & 0x3FF))

/*
 * Completion Q defines
 */
/* CQ Entry Flags */
#घोषणा BNA_CQ_EF_MAC_ERROR	BIT(0)
#घोषणा BNA_CQ_EF_FCS_ERROR	BIT(1)
#घोषणा BNA_CQ_EF_TOO_LONG	BIT(2)
#घोषणा BNA_CQ_EF_FC_CRC_OK	BIT(3)

#घोषणा BNA_CQ_EF_RSVD1		BIT(4)
#घोषणा BNA_CQ_EF_L4_CKSUM_OK	BIT(5)
#घोषणा BNA_CQ_EF_L3_CKSUM_OK	BIT(6)
#घोषणा BNA_CQ_EF_HDS_HEADER	BIT(7)

#घोषणा BNA_CQ_EF_UDP		BIT(8)
#घोषणा BNA_CQ_EF_TCP		BIT(9)
#घोषणा BNA_CQ_EF_IP_OPTIONS	BIT(10)
#घोषणा BNA_CQ_EF_IPV6		BIT(11)

#घोषणा BNA_CQ_EF_IPV4		BIT(12)
#घोषणा BNA_CQ_EF_VLAN		BIT(13)
#घोषणा BNA_CQ_EF_RSS		BIT(14)
#घोषणा BNA_CQ_EF_RSVD2		BIT(15)

#घोषणा BNA_CQ_EF_MCAST_MATCH   BIT(16)
#घोषणा BNA_CQ_EF_MCAST		BIT(17)
#घोषणा BNA_CQ_EF_BCAST		BIT(18)
#घोषणा BNA_CQ_EF_REMOTE	BIT(19)

#घोषणा BNA_CQ_EF_LOCAL		BIT(20)
/* CAT2 ASIC करोes not use bit 21 as per the SPEC.
 * Bit 31 is set in every end of frame completion
 */
#घोषणा BNA_CQ_EF_EOP		BIT(31)

/* Data काष्ठाures */

काष्ठा bna_reg_offset अणु
	u32 fn_पूर्णांक_status;
	u32 fn_पूर्णांक_mask;
पूर्ण;

काष्ठा bna_bit_defn अणु
	u32 mbox_status_bits;
	u32 mbox_mask_bits;
	u32 error_status_bits;
	u32 error_mask_bits;
	u32 halt_status_bits;
	u32 halt_mask_bits;
पूर्ण;

काष्ठा bna_reg अणु
	व्योम __iomem *fn_पूर्णांक_status;
	व्योम __iomem *fn_पूर्णांक_mask;
पूर्ण;

/* TxQ Vector (a.k.a. Tx-Buffer Descriptor) */
काष्ठा bna_dma_addr अणु
	u32		msb;
	u32		lsb;
पूर्ण;

काष्ठा bna_txq_wi_vector अणु
	u16		reserved;
	u16		length;		/* Only 14 LSB are valid */
	काष्ठा bna_dma_addr host_addr; /* Tx-Buf DMA addr */
पूर्ण;

/*  TxQ Entry Structure
 *
 *  BEWARE:  Load values पूर्णांकo this काष्ठाure with correct endianness.
 */
काष्ठा bna_txq_entry अणु
	जोड़ अणु
		काष्ठा अणु
			u8 reserved;
			u8 num_vectors;	/* number of vectors present */
			u16 opcode; /* Either */
						    /* BNA_TXQ_WI_SEND or */
						    /* BNA_TXQ_WI_SEND_LSO */
			u16 flags; /* OR of all the flags */
			u16 l4_hdr_size_n_offset;
			u16 vlan_tag;
			u16 lso_mss;	/* Only 14 LSB are valid */
			u32 frame_length;	/* Only 24 LSB are valid */
		पूर्ण wi;

		काष्ठा अणु
			u16 reserved;
			u16 opcode; /* Must be */
						    /* BNA_TXQ_WI_EXTENSION */
			u32 reserved2[3];	/* Place holder क्रम */
						/* हटाओd vector (12 bytes) */
		पूर्ण wi_ext;
	पूर्ण hdr;
	काष्ठा bna_txq_wi_vector vector[4];
पूर्ण;

/* RxQ Entry Structure */
काष्ठा bna_rxq_entry अणु		/* Rx-Buffer */
	काष्ठा bna_dma_addr host_addr; /* Rx-Buffer DMA address */
पूर्ण;

/* CQ Entry Structure */
काष्ठा bna_cq_entry अणु
	u32 flags;
	u16 vlan_tag;
	u16 length;
	u32 rss_hash;
	u8 valid;
	u8 reserved1;
	u8 reserved2;
	u8 rxq_id;
पूर्ण;

#पूर्ण_अगर /* __BNA_HW_DEFS_H__ */
