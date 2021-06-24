<शैली गुरु>
/* cnic.h: QLogic CNIC core network driver.
 *
 * Copyright (c) 2006-2014 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */


#अगर_अघोषित CNIC_H
#घोषणा CNIC_H

#घोषणा HC_INDEX_ISCSI_EQ_CONS			6

#घोषणा HC_INDEX_FCOE_EQ_CONS			3

#घोषणा HC_SP_INDEX_ETH_ISCSI_CQ_CONS		5
#घोषणा HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS	1

#घोषणा KWQ_PAGE_CNT	4
#घोषणा KCQ_PAGE_CNT	16

#घोषणा KWQ_CID 		24
#घोषणा KCQ_CID 		25

/*
 *	krnlq_context definition
 */
#घोषणा L5_KRNLQ_FLAGS	0x00000000
#घोषणा L5_KRNLQ_SIZE	0x00000000
#घोषणा L5_KRNLQ_TYPE	0x00000000
#घोषणा KRNLQ_FLAGS_PG_SZ					(0xf<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_256					(0<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_512					(1<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_1K					(2<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_2K					(3<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_4K					(4<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_8K					(5<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_16K					(6<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_32K					(7<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_64K					(8<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_128K					(9<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_256K					(10<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_512K					(11<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_1M					(12<<0)
#घोषणा KRNLQ_FLAGS_PG_SZ_2M					(13<<0)
#घोषणा KRNLQ_FLAGS_QE_SELF_SEQ					(1<<15)
#घोषणा KRNLQ_SIZE_TYPE_SIZE	((((0x28 + 0x1f) & ~0x1f) / 0x20) << 16)
#घोषणा KRNLQ_TYPE_TYPE						(0xf<<28)
#घोषणा KRNLQ_TYPE_TYPE_EMPTY					(0<<28)
#घोषणा KRNLQ_TYPE_TYPE_KRNLQ					(6<<28)

#घोषणा L5_KRNLQ_HOST_QIDX		0x00000004
#घोषणा L5_KRNLQ_HOST_FW_QIDX		0x00000008
#घोषणा L5_KRNLQ_NX_QE_SELF_SEQ 	0x0000000c
#घोषणा L5_KRNLQ_QE_SELF_SEQ_MAX	0x0000000c
#घोषणा L5_KRNLQ_NX_QE_HADDR_HI 	0x00000010
#घोषणा L5_KRNLQ_NX_QE_HADDR_LO 	0x00000014
#घोषणा L5_KRNLQ_PGTBL_PGIDX		0x00000018
#घोषणा L5_KRNLQ_NX_PG_QIDX 		0x00000018
#घोषणा L5_KRNLQ_PGTBL_NPAGES		0x0000001c
#घोषणा L5_KRNLQ_QIDX_INCR		0x0000001c
#घोषणा L5_KRNLQ_PGTBL_HADDR_HI 	0x00000020
#घोषणा L5_KRNLQ_PGTBL_HADDR_LO 	0x00000024

#घोषणा BNX2_PG_CTX_MAP			0x1a0034
#घोषणा BNX2_ISCSI_CTX_MAP		0x1a0074

#घोषणा MAX_COMPLETED_KCQE	64

#घोषणा MAX_CNIC_L5_CONTEXT	256

#घोषणा MAX_CM_SK_TBL_SZ	MAX_CNIC_L5_CONTEXT

#घोषणा MAX_ISCSI_TBL_SZ	256

#घोषणा CNIC_LOCAL_PORT_MIN	60000
#घोषणा CNIC_LOCAL_PORT_MAX	61024
#घोषणा CNIC_LOCAL_PORT_RANGE	(CNIC_LOCAL_PORT_MAX - CNIC_LOCAL_PORT_MIN)

#घोषणा KWQE_CNT (BNX2_PAGE_SIZE / माप(काष्ठा kwqe))
#घोषणा KCQE_CNT (BNX2_PAGE_SIZE / माप(काष्ठा kcqe))
#घोषणा MAX_KWQE_CNT (KWQE_CNT - 1)
#घोषणा MAX_KCQE_CNT (KCQE_CNT - 1)

#घोषणा MAX_KWQ_IDX	((KWQ_PAGE_CNT * KWQE_CNT) - 1)
#घोषणा MAX_KCQ_IDX	((KCQ_PAGE_CNT * KCQE_CNT) - 1)

#घोषणा KWQ_PG(x) (((x) & ~MAX_KWQE_CNT) >> (BNX2_PAGE_BITS - 5))
#घोषणा KWQ_IDX(x) ((x) & MAX_KWQE_CNT)

#घोषणा KCQ_PG(x) (((x) & ~MAX_KCQE_CNT) >> (BNX2_PAGE_BITS - 5))
#घोषणा KCQ_IDX(x) ((x) & MAX_KCQE_CNT)

#घोषणा BNX2X_NEXT_KCQE(x) (((x) & (MAX_KCQE_CNT - 1)) ==		\
		(MAX_KCQE_CNT - 1)) ?					\
		(x) + 2 : (x) + 1

#घोषणा BNX2X_KWQ_DATA_PG(cp, x) ((x) / (cp)->kwq_16_data_pp)
#घोषणा BNX2X_KWQ_DATA_IDX(cp, x) ((x) % (cp)->kwq_16_data_pp)
#घोषणा BNX2X_KWQ_DATA(cp, x)						\
	&(cp)->kwq_16_data[BNX2X_KWQ_DATA_PG(cp, x)][BNX2X_KWQ_DATA_IDX(cp, x)]

#घोषणा DEF_IPID_START		0x8000

#घोषणा DEF_KA_TIMEOUT		10000
#घोषणा DEF_KA_INTERVAL		300000
#घोषणा DEF_KA_MAX_PROBE_COUNT	3
#घोषणा DEF_TOS			0
#घोषणा DEF_TTL			0xfe
#घोषणा DEF_SND_SEQ_SCALE	0
#घोषणा DEF_RCV_BUF		0xffff
#घोषणा DEF_SND_BUF		0xffff
#घोषणा DEF_SEED		0
#घोषणा DEF_MAX_RT_TIME		500
#घोषणा DEF_MAX_DA_COUNT	2
#घोषणा DEF_SWS_TIMER		1000
#घोषणा DEF_MAX_CWND		0xffff

काष्ठा cnic_ctx अणु
	u32		cid;
	व्योम		*ctx;
	dma_addr_t	mapping;
पूर्ण;

#घोषणा BNX2_MAX_CID		0x2000

काष्ठा cnic_dma अणु
	पूर्णांक		num_pages;
	व्योम		**pg_arr;
	dma_addr_t	*pg_map_arr;
	पूर्णांक		pgtbl_size;
	u32		*pgtbl;
	dma_addr_t	pgtbl_map;
पूर्ण;

काष्ठा cnic_id_tbl अणु
	spinlock_t	lock;
	u32		start;
	u32		max;
	u32		next;
	अचिन्हित दीर्घ	*table;
पूर्ण;

#घोषणा CNIC_KWQ16_DATA_SIZE	128

काष्ठा kwqe_16_data अणु
	u8	data[CNIC_KWQ16_DATA_SIZE];
पूर्ण;

काष्ठा cnic_iscsi अणु
	काष्ठा cnic_dma		task_array_info;
	काष्ठा cnic_dma		r2tq_info;
	काष्ठा cnic_dma		hq_info;
पूर्ण;

काष्ठा cnic_context अणु
	u32			cid;
	काष्ठा kwqe_16_data	*kwqe_data;
	dma_addr_t		kwqe_data_mapping;
	रुको_queue_head_t	रुकोq;
	पूर्णांक			रुको_cond;
	अचिन्हित दीर्घ		बारtamp;
	अचिन्हित दीर्घ		ctx_flags;
#घोषणा	CTX_FL_OFFLD_START	0
#घोषणा	CTX_FL_DELETE_WAIT	1
#घोषणा	CTX_FL_CID_ERROR	2
	u8			ulp_proto_id;
	जोड़ अणु
		काष्ठा cnic_iscsi	*iscsi;
	पूर्ण proto;
पूर्ण;

काष्ठा kcq_info अणु
	काष्ठा cnic_dma	dma;
	काष्ठा kcqe	**kcq;

	u16		*hw_prod_idx_ptr;
	u16		sw_prod_idx;
	u16		*status_idx_ptr;
	u32		io_addr;

	u16		(*next_idx)(u16);
	u16		(*hw_idx)(u16);
पूर्ण;

#घोषणा UIO_USE_TX_DOORBELL 0x017855DB

काष्ठा cnic_uio_dev अणु
	काष्ठा uio_info		cnic_uinfo;
	u32			uio_dev;

	पूर्णांक			l2_ring_size;
	व्योम			*l2_ring;
	dma_addr_t		l2_ring_map;

	पूर्णांक			l2_buf_size;
	व्योम			*l2_buf;
	dma_addr_t		l2_buf_map;

	काष्ठा cnic_dev		*dev;
	काष्ठा pci_dev		*pdev;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा cnic_local अणु

	spinlock_t cnic_ulp_lock;
	व्योम *ulp_handle[MAX_CNIC_ULP_TYPE];
	अचिन्हित दीर्घ ulp_flags[MAX_CNIC_ULP_TYPE];
#घोषणा ULP_F_INIT	0
#घोषणा ULP_F_START	1
#घोषणा ULP_F_CALL_PENDING	2
	काष्ठा cnic_ulp_ops __rcu *ulp_ops[MAX_CNIC_ULP_TYPE];

	अचिन्हित दीर्घ cnic_local_flags;
#घोषणा	CNIC_LCL_FL_KWQ_INIT		0x0
#घोषणा	CNIC_LCL_FL_L2_WAIT		0x1
#घोषणा	CNIC_LCL_FL_RINGS_INITED	0x2
#घोषणा	CNIC_LCL_FL_STOP_ISCSI		0x4

	काष्ठा cnic_dev *dev;

	काष्ठा cnic_eth_dev *ethdev;

	काष्ठा cnic_uio_dev *udev;

	पूर्णांक		l2_rx_ring_size;
	पूर्णांक		l2_single_buf_size;

	u16		*rx_cons_ptr;
	u16		*tx_cons_ptr;
	u16		rx_cons;
	u16		tx_cons;

	काष्ठा cnic_dma		kwq_info;
	काष्ठा kwqe		**kwq;

	काष्ठा cnic_dma		kwq_16_data_info;

	u16		max_kwq_idx;

	u16		kwq_prod_idx;
	u32		kwq_io_addr;

	u16		*kwq_con_idx_ptr;
	u16		kwq_con_idx;

	काष्ठा kcq_info	kcq1;
	काष्ठा kcq_info	kcq2;

	जोड़ अणु
		व्योम				*gen;
		काष्ठा status_block_msix	*bnx2;
		काष्ठा host_hc_status_block_e1x	*bnx2x_e1x;
		/* index values - which counter to update */
		#घोषणा SM_RX_ID		0
		#घोषणा SM_TX_ID		1
	पूर्ण status_blk;

	काष्ठा host_sp_status_block	*bnx2x_def_status_blk;

	u32				status_blk_num;
	u32				bnx2x_igu_sb_id;
	u32				पूर्णांक_num;
	u32				last_status_idx;
	काष्ठा tasklet_काष्ठा		cnic_irq_task;

	काष्ठा kcqe		*completed_kcq[MAX_COMPLETED_KCQE];

	काष्ठा cnic_sock	*csk_tbl;
	काष्ठा cnic_id_tbl	csk_port_tbl;

	काष्ठा cnic_dma		gbl_buf_info;

	काष्ठा cnic_iscsi	*iscsi_tbl;
	काष्ठा cnic_context	*ctx_tbl;
	काष्ठा cnic_id_tbl	cid_tbl;
	atomic_t		iscsi_conn;
	u32			iscsi_start_cid;

	u32			fcoe_init_cid;
	u32			fcoe_start_cid;
	काष्ठा cnic_id_tbl	fcoe_cid_tbl;

	u32			max_cid_space;

	/* per connection parameters */
	पूर्णांक			num_iscsi_tasks;
	पूर्णांक			num_ccells;
	पूर्णांक			task_array_size;
	पूर्णांक			r2tq_size;
	पूर्णांक			hq_size;
	पूर्णांक			num_cqs;

	काष्ठा delayed_work	delete_task;

	काष्ठा cnic_ctx		*ctx_arr;
	पूर्णांक			ctx_blks;
	पूर्णांक			ctx_blk_size;
	अचिन्हित दीर्घ		ctx_align;
	पूर्णांक			cids_per_blk;

	u32			chip_id;
	पूर्णांक			func;

	u32			shmem_base;

	काष्ठा cnic_ops		*cnic_ops;
	पूर्णांक			(*start_hw)(काष्ठा cnic_dev *);
	व्योम			(*stop_hw)(काष्ठा cnic_dev *);
	व्योम			(*setup_pgtbl)(काष्ठा cnic_dev *,
					       काष्ठा cnic_dma *);
	पूर्णांक			(*alloc_resc)(काष्ठा cnic_dev *);
	व्योम			(*मुक्त_resc)(काष्ठा cnic_dev *);
	पूर्णांक			(*start_cm)(काष्ठा cnic_dev *);
	व्योम			(*stop_cm)(काष्ठा cnic_dev *);
	व्योम			(*enable_पूर्णांक)(काष्ठा cnic_dev *);
	व्योम			(*disable_पूर्णांक_sync)(काष्ठा cnic_dev *);
	व्योम			(*ack_पूर्णांक)(काष्ठा cnic_dev *);
	व्योम			(*arm_पूर्णांक)(काष्ठा cnic_dev *, u32 index);
	व्योम			(*बंद_conn)(काष्ठा cnic_sock *, u32 opcode);
पूर्ण;

काष्ठा bnx2x_bd_chain_next अणु
	u32	addr_lo;
	u32	addr_hi;
	u8	reserved[8];
पूर्ण;

#घोषणा ISCSI_DEFAULT_MAX_OUTSTANDING_R2T 	(1)

#घोषणा ISCSI_RAMROD_CMD_ID_UPDATE_CONN		(ISCSI_KCQE_OPCODE_UPDATE_CONN)
#घोषणा ISCSI_RAMROD_CMD_ID_INIT		(ISCSI_KCQE_OPCODE_INIT)

#घोषणा CDU_REGION_NUMBER_XCM_AG 2
#घोषणा CDU_REGION_NUMBER_UCM_AG 4

#घोषणा CDU_VALID_DATA(_cid, _region, _type)	\
	(((_cid) << 8) | (((_region)&0xf)<<4) | (((_type)&0xf)))

#घोषणा CDU_CRC8(_cid, _region, _type)	\
	(calc_crc8(CDU_VALID_DATA(_cid, _region, _type), 0xff))

#घोषणा CDU_RSRVD_VALUE_TYPE_A(_cid, _region, _type)	\
	(0x80 | ((CDU_CRC8(_cid, _region, _type)) & 0x7f))

#घोषणा BNX2X_CONTEXT_MEM_SIZE		1024
#घोषणा BNX2X_FCOE_CID			16

#घोषणा BNX2X_ISCSI_START_CID		18
#घोषणा BNX2X_ISCSI_NUM_CONNECTIONS	128
#घोषणा BNX2X_ISCSI_TASK_CONTEXT_SIZE	128
#घोषणा BNX2X_ISCSI_MAX_PENDING_R2TS	4
#घोषणा BNX2X_ISCSI_R2TQE_SIZE		8
#घोषणा BNX2X_ISCSI_HQ_BD_SIZE		64
#घोषणा BNX2X_ISCSI_GLB_BUF_SIZE	64
#घोषणा BNX2X_ISCSI_PBL_NOT_CACHED	0xff
#घोषणा BNX2X_ISCSI_PDU_HEADER_NOT_CACHED	0xff

#घोषणा BNX2X_FCOE_NUM_CONNECTIONS	1024

#घोषणा BNX2X_FCOE_L5_CID_BASE		MAX_ISCSI_TBL_SZ

#घोषणा BNX2X_CHIP_IS_E2_PLUS(bp) (CHIP_IS_E2(bp) || CHIP_IS_E3(bp))

#घोषणा BNX2X_RX_DESC_CNT		(BNX2_PAGE_SIZE / \
					 माप(काष्ठा eth_rx_bd))
#घोषणा BNX2X_MAX_RX_DESC_CNT		(BNX2X_RX_DESC_CNT - 2)
#घोषणा BNX2X_RCQ_DESC_CNT		(BNX2_PAGE_SIZE / \
					 माप(जोड़ eth_rx_cqe))
#घोषणा BNX2X_MAX_RCQ_DESC_CNT		(BNX2X_RCQ_DESC_CNT - 1)

#घोषणा BNX2X_NEXT_RCQE(x) (((x) & BNX2X_MAX_RCQ_DESC_CNT) ==		\
		(BNX2X_MAX_RCQ_DESC_CNT - 1)) ?				\
		((x) + 2) : ((x) + 1)

#घोषणा BNX2X_DEF_SB_ID			HC_SP_SB_ID

#घोषणा BNX2X_SHMEM_MF_BLK_OFFSET	0x7e4

#घोषणा BNX2X_SHMEM_ADDR(base, field)	(base + \
					 दुरत्व(काष्ठा shmem_region, field))

#घोषणा BNX2X_SHMEM2_ADDR(base, field)	(base + \
					 दुरत्व(काष्ठा shmem2_region, field))

#घोषणा BNX2X_SHMEM2_HAS(base, field)				\
		((base) &&					\
		 (CNIC_RD(dev, BNX2X_SHMEM2_ADDR(base, size)) >	\
		  दुरत्व(काष्ठा shmem2_region, field)))

#घोषणा BNX2X_MF_CFG_ADDR(base, field)				\
			((base) + दुरत्व(काष्ठा mf_cfg, field))

#अगर_अघोषित ETH_MAX_RX_CLIENTS_E2
#घोषणा ETH_MAX_RX_CLIENTS_E2 		ETH_MAX_RX_CLIENTS_E1H
#पूर्ण_अगर

#घोषणा CNIC_FUNC(cp)			((cp)->func)

#घोषणा BNX2X_HW_CID(bp, x)		((BP_PORT(bp) << 23) | \
					 (BP_VN(bp) << 17) | (x))

#घोषणा BNX2X_SW_CID(x)			(x & 0x1ffff)

#घोषणा BNX2X_CL_QZONE_ID(bp, cli)					\
		(BNX2X_CHIP_IS_E2_PLUS(bp) ? cli :			\
		 cli + (BP_PORT(bp) * ETH_MAX_RX_CLIENTS_E1H))

#अगर_अघोषित MAX_STAT_COUNTER_ID
#घोषणा MAX_STAT_COUNTER_ID						\
	(CHIP_IS_E1H(bp) ? MAX_STAT_COUNTER_ID_E1H :			\
	 ((BNX2X_CHIP_IS_E2_PLUS(bp)) ? MAX_STAT_COUNTER_ID_E2 :	\
	  MAX_STAT_COUNTER_ID_E1))
#पूर्ण_अगर

#घोषणा CNIC_SUPPORTS_FCOE(cp)						\
	(BNX2X_CHIP_IS_E2_PLUS(bp) && !NO_FCOE(bp))

#घोषणा CNIC_RAMROD_TMO			(HZ / 4)

#पूर्ण_अगर

