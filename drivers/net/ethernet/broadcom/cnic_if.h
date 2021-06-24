<शैली गुरु>
/* cnic_अगर.h: QLogic cnic core network driver.
 *
 * Copyright (c) 2006-2014 Broadcom Corporation
 * Copyright (c) 2014-2015 QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */


#अगर_अघोषित CNIC_IF_H
#घोषणा CNIC_IF_H

#समावेश "bnx2x/bnx2x_mfw_req.h"

#घोषणा CNIC_MODULE_VERSION	"2.5.22"
#घोषणा CNIC_MODULE_RELDATE	"July 20, 2015"

#घोषणा CNIC_ULP_RDMA		0
#घोषणा CNIC_ULP_ISCSI		1
#घोषणा CNIC_ULP_FCOE		2
#घोषणा CNIC_ULP_L4		3
#घोषणा MAX_CNIC_ULP_TYPE_EXT	3
#घोषणा MAX_CNIC_ULP_TYPE	4

/* Use CPU native page size up to 16K क्रम cnic ring sizes.  */
#अगर (PAGE_SHIFT > 14)
#घोषणा CNIC_PAGE_BITS	14
#अन्यथा
#घोषणा CNIC_PAGE_BITS	PAGE_SHIFT
#पूर्ण_अगर
#घोषणा CNIC_PAGE_SIZE	(1 << (CNIC_PAGE_BITS))
#घोषणा CNIC_PAGE_ALIGN(addr) ALIGN(addr, CNIC_PAGE_SIZE)
#घोषणा CNIC_PAGE_MASK	(~((CNIC_PAGE_SIZE) - 1))

काष्ठा kwqe अणु
	u32 kwqe_op_flag;

#घोषणा KWQE_QID_SHIFT		8
#घोषणा KWQE_OPCODE_MASK	0x00ff0000
#घोषणा KWQE_OPCODE_SHIFT	16
#घोषणा KWQE_OPCODE(x)		((x & KWQE_OPCODE_MASK) >> KWQE_OPCODE_SHIFT)
#घोषणा KWQE_LAYER_MASK			0x70000000
#घोषणा KWQE_LAYER_SHIFT		28
#घोषणा KWQE_FLAGS_LAYER_MASK_L2	(2<<28)
#घोषणा KWQE_FLAGS_LAYER_MASK_L3	(3<<28)
#घोषणा KWQE_FLAGS_LAYER_MASK_L4	(4<<28)
#घोषणा KWQE_FLAGS_LAYER_MASK_L5_RDMA	(5<<28)
#घोषणा KWQE_FLAGS_LAYER_MASK_L5_ISCSI	(6<<28)
#घोषणा KWQE_FLAGS_LAYER_MASK_L5_FCOE	(7<<28)

	u32 kwqe_info0;
	u32 kwqe_info1;
	u32 kwqe_info2;
	u32 kwqe_info3;
	u32 kwqe_info4;
	u32 kwqe_info5;
	u32 kwqe_info6;
पूर्ण;

काष्ठा kwqe_16 अणु
	u32 kwqe_info0;
	u32 kwqe_info1;
	u32 kwqe_info2;
	u32 kwqe_info3;
पूर्ण;

काष्ठा kcqe अणु
	u32 kcqe_info0;
	u32 kcqe_info1;
	u32 kcqe_info2;
	u32 kcqe_info3;
	u32 kcqe_info4;
	u32 kcqe_info5;
	u32 kcqe_info6;
	u32 kcqe_op_flag;
		#घोषणा KCQE_RAMROD_COMPLETION		(0x1<<27) /* Everest */
		#घोषणा KCQE_FLAGS_LAYER_MASK		(0x7<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_MISC	(0<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_L2	(2<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_L3	(3<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_L4	(4<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_L5_RDMA	(5<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_L5_ISCSI	(6<<28)
		#घोषणा KCQE_FLAGS_LAYER_MASK_L5_FCOE	(7<<28)
		#घोषणा KCQE_FLAGS_NEXT 		(1<<31)
		#घोषणा KCQE_FLAGS_OPCODE_MASK		(0xff<<16)
		#घोषणा KCQE_FLAGS_OPCODE_SHIFT		(16)
		#घोषणा KCQE_OPCODE(op)			\
		(((op) & KCQE_FLAGS_OPCODE_MASK) >> KCQE_FLAGS_OPCODE_SHIFT)
पूर्ण;

#घोषणा MAX_CNIC_CTL_DATA	64
#घोषणा MAX_DRV_CTL_DATA	64

#घोषणा CNIC_CTL_STOP_CMD		1
#घोषणा CNIC_CTL_START_CMD		2
#घोषणा CNIC_CTL_COMPLETION_CMD		3
#घोषणा CNIC_CTL_STOP_ISCSI_CMD		4
#घोषणा CNIC_CTL_FCOE_STATS_GET_CMD	5
#घोषणा CNIC_CTL_ISCSI_STATS_GET_CMD	6

#घोषणा DRV_CTL_IO_WR_CMD		0x101
#घोषणा DRV_CTL_IO_RD_CMD		0x102
#घोषणा DRV_CTL_CTX_WR_CMD		0x103
#घोषणा DRV_CTL_CTXTBL_WR_CMD		0x104
#घोषणा DRV_CTL_RET_L5_SPQ_CREDIT_CMD	0x105
#घोषणा DRV_CTL_START_L2_CMD		0x106
#घोषणा DRV_CTL_STOP_L2_CMD		0x107
#घोषणा DRV_CTL_RET_L2_SPQ_CREDIT_CMD	0x10c
#घोषणा DRV_CTL_ISCSI_STOPPED_CMD	0x10d
#घोषणा DRV_CTL_ULP_REGISTER_CMD	0x10e
#घोषणा DRV_CTL_ULP_UNREGISTER_CMD	0x10f

काष्ठा cnic_ctl_completion अणु
	u32	cid;
	u8	opcode;
	u8	error;
पूर्ण;

काष्ठा cnic_ctl_info अणु
	पूर्णांक	cmd;
	जोड़ अणु
		काष्ठा cnic_ctl_completion comp;
		अक्षर bytes[MAX_CNIC_CTL_DATA];
	पूर्ण data;
पूर्ण;

काष्ठा drv_ctl_spq_credit अणु
	u32	credit_count;
पूर्ण;

काष्ठा drv_ctl_io अणु
	u32		cid_addr;
	u32		offset;
	u32		data;
	dma_addr_t	dma_addr;
पूर्ण;

काष्ठा drv_ctl_l2_ring अणु
	u32		client_id;
	u32		cid;
पूर्ण;

काष्ठा drv_ctl_रेजिस्टर_data अणु
	पूर्णांक ulp_type;
	काष्ठा fcoe_capabilities fcoe_features;
पूर्ण;

काष्ठा drv_ctl_info अणु
	पूर्णांक	cmd;
	पूर्णांक     drv_state;
#घोषणा DRV_NOP		0
#घोषणा DRV_ACTIVE	1
#घोषणा DRV_INACTIVE	2
#घोषणा DRV_UNLOADED	3
	जोड़ अणु
		काष्ठा drv_ctl_spq_credit credit;
		काष्ठा drv_ctl_io io;
		काष्ठा drv_ctl_l2_ring ring;
		पूर्णांक ulp_type;
		काष्ठा drv_ctl_रेजिस्टर_data रेजिस्टर_data;
		अक्षर bytes[MAX_DRV_CTL_DATA];
	पूर्ण data;
पूर्ण;

#घोषणा MAX_NPIV_ENTRIES 64
#घोषणा FC_NPIV_WWN_SIZE 8

काष्ठा cnic_fc_npiv_tbl अणु
	u8 wwpn[MAX_NPIV_ENTRIES][FC_NPIV_WWN_SIZE];
	u8 wwnn[MAX_NPIV_ENTRIES][FC_NPIV_WWN_SIZE];
	u32 count;
पूर्ण;

काष्ठा cnic_ops अणु
	काष्ठा module	*cnic_owner;
	/* Calls to these functions are रक्षित by RCU.  When
	 * unरेजिस्टरing, we रुको क्रम any calls to complete beक्रमe
	 * continuing.
	 */
	पूर्णांक		(*cnic_handler)(व्योम *, व्योम *);
	पूर्णांक		(*cnic_ctl)(व्योम *, काष्ठा cnic_ctl_info *);
पूर्ण;

#घोषणा MAX_CNIC_VEC	8

काष्ठा cnic_irq अणु
	अचिन्हित पूर्णांक	vector;
	व्योम		*status_blk;
	u32		status_blk_num;
	u32		status_blk_num2;
	u32		irq_flags;
#घोषणा CNIC_IRQ_FL_MSIX		0x00000001
पूर्ण;

काष्ठा cnic_eth_dev अणु
	काष्ठा module	*drv_owner;
	u32		drv_state;
#घोषणा CNIC_DRV_STATE_REGD		0x00000001
#घोषणा CNIC_DRV_STATE_USING_MSIX	0x00000002
#घोषणा CNIC_DRV_STATE_NO_ISCSI_OOO	0x00000004
#घोषणा CNIC_DRV_STATE_NO_ISCSI		0x00000008
#घोषणा CNIC_DRV_STATE_NO_FCOE		0x00000010
#घोषणा CNIC_DRV_STATE_HANDLES_IRQ	0x00000020
	u32		chip_id;
	u32		max_kwqe_pending;
	काष्ठा pci_dev	*pdev;
	व्योम __iomem	*io_base;
	व्योम __iomem	*io_base2;
	स्थिर व्योम	*iro_arr;

	u32		ctx_tbl_offset;
	u32		ctx_tbl_len;
	पूर्णांक		ctx_blk_size;
	u32		starting_cid;
	u32		max_iscsi_conn;
	u32		max_fcoe_conn;
	u32		max_rdma_conn;
	u32		fcoe_init_cid;
	u32		max_fcoe_exchanges;
	u32		fcoe_wwn_port_name_hi;
	u32		fcoe_wwn_port_name_lo;
	u32		fcoe_wwn_node_name_hi;
	u32		fcoe_wwn_node_name_lo;

	u16		iscsi_l2_client_id;
	u16		iscsi_l2_cid;
	u8		iscsi_mac[ETH_ALEN];

	पूर्णांक		num_irq;
	काष्ठा cnic_irq	irq_arr[MAX_CNIC_VEC];
	पूर्णांक		(*drv_रेजिस्टर_cnic)(काष्ठा net_device *,
					     काष्ठा cnic_ops *, व्योम *);
	पूर्णांक		(*drv_unरेजिस्टर_cnic)(काष्ठा net_device *);
	पूर्णांक		(*drv_submit_kwqes_32)(काष्ठा net_device *,
					       काष्ठा kwqe *[], u32);
	पूर्णांक		(*drv_submit_kwqes_16)(काष्ठा net_device *,
					       काष्ठा kwqe_16 *[], u32);
	पूर्णांक		(*drv_ctl)(काष्ठा net_device *, काष्ठा drv_ctl_info *);
	पूर्णांक		(*drv_get_fc_npiv_tbl)(काष्ठा net_device *,
					       काष्ठा cnic_fc_npiv_tbl *);
	अचिन्हित दीर्घ	reserved1[2];
	जोड़ drv_info_to_mcp	*addr_drv_info_to_mcp;
पूर्ण;

काष्ठा cnic_sockaddr अणु
	जोड़ अणु
		काष्ठा sockaddr_in	v4;
		काष्ठा sockaddr_in6	v6;
	पूर्ण local;
	जोड़ अणु
		काष्ठा sockaddr_in	v4;
		काष्ठा sockaddr_in6	v6;
	पूर्ण remote;
पूर्ण;

काष्ठा cnic_sock अणु
	काष्ठा cnic_dev *dev;
	व्योम	*context;
	u32	src_ip[4];
	u32	dst_ip[4];
	u16	src_port;
	u16	dst_port;
	u16	vlan_id;
	अचिन्हित अक्षर old_ha[ETH_ALEN];
	अचिन्हित अक्षर ha[ETH_ALEN];
	u32	mtu;
	u32	cid;
	u32	l5_cid;
	u32	pg_cid;
	पूर्णांक	ulp_type;

	u32	ka_समयout;
	u32	ka_पूर्णांकerval;
	u8	ka_max_probe_count;
	u8	tos;
	u8	ttl;
	u8	snd_seq_scale;
	u32	rcv_buf;
	u32	snd_buf;
	u32	seed;

	अचिन्हित दीर्घ	tcp_flags;
#घोषणा SK_TCP_NO_DELAY_ACK	0x1
#घोषणा SK_TCP_KEEP_ALIVE	0x2
#घोषणा SK_TCP_NAGLE		0x4
#घोषणा SK_TCP_TIMESTAMP	0x8
#घोषणा SK_TCP_SACK		0x10
#घोषणा SK_TCP_SEG_SCALING	0x20
	अचिन्हित दीर्घ	flags;
#घोषणा SK_F_INUSE		0
#घोषणा SK_F_OFFLD_COMPLETE	1
#घोषणा SK_F_OFFLD_SCHED	2
#घोषणा SK_F_PG_OFFLD_COMPLETE	3
#घोषणा SK_F_CONNECT_START	4
#घोषणा SK_F_IPV6		5
#घोषणा SK_F_CLOSING		7
#घोषणा SK_F_HW_ERR		8

	atomic_t ref_count;
	u32 state;
	काष्ठा kwqe kwqe1;
	काष्ठा kwqe kwqe2;
	काष्ठा kwqe kwqe3;
पूर्ण;

काष्ठा cnic_dev अणु
	काष्ठा net_device	*netdev;
	काष्ठा pci_dev		*pcidev;
	व्योम __iomem		*regview;
	काष्ठा list_head	list;

	पूर्णांक (*रेजिस्टर_device)(काष्ठा cnic_dev *dev, पूर्णांक ulp_type,
			       व्योम *ulp_ctx);
	पूर्णांक (*unरेजिस्टर_device)(काष्ठा cnic_dev *dev, पूर्णांक ulp_type);
	पूर्णांक (*submit_kwqes)(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				u32 num_wqes);
	पूर्णांक (*submit_kwqes_16)(काष्ठा cnic_dev *dev, काष्ठा kwqe_16 *wqes[],
				u32 num_wqes);

	पूर्णांक (*cm_create)(काष्ठा cnic_dev *, पूर्णांक, u32, u32, काष्ठा cnic_sock **,
			 व्योम *);
	पूर्णांक (*cm_destroy)(काष्ठा cnic_sock *);
	पूर्णांक (*cm_connect)(काष्ठा cnic_sock *, काष्ठा cnic_sockaddr *);
	पूर्णांक (*cm_पात)(काष्ठा cnic_sock *);
	पूर्णांक (*cm_बंद)(काष्ठा cnic_sock *);
	काष्ठा cnic_dev *(*cm_select_dev)(काष्ठा sockaddr_in *, पूर्णांक ulp_type);
	पूर्णांक (*iscsi_nl_msg_recv)(काष्ठा cnic_dev *dev, u32 msg_type,
				 अक्षर *data, u16 data_size);
	पूर्णांक (*get_fc_npiv_tbl)(काष्ठा cnic_dev *, काष्ठा cnic_fc_npiv_tbl *);
	अचिन्हित दीर्घ	flags;
#घोषणा CNIC_F_CNIC_UP		1
#घोषणा CNIC_F_BNX2_CLASS	3
#घोषणा CNIC_F_BNX2X_CLASS	4
	atomic_t	ref_count;
	u8		mac_addr[ETH_ALEN];

	पूर्णांक		max_iscsi_conn;
	पूर्णांक		max_fcoe_conn;
	पूर्णांक		max_rdma_conn;

	पूर्णांक		max_fcoe_exchanges;

	जोड़ drv_info_to_mcp	*stats_addr;
	काष्ठा fcoe_capabilities	*fcoe_cap;

	व्योम		*cnic_priv;
पूर्ण;

#घोषणा CNIC_WR(dev, off, val)		ग_लिखोl(val, dev->regview + off)
#घोषणा CNIC_WR16(dev, off, val)	ग_लिखोw(val, dev->regview + off)
#घोषणा CNIC_WR8(dev, off, val)		ग_लिखोb(val, dev->regview + off)
#घोषणा CNIC_RD(dev, off)		पढ़ोl(dev->regview + off)
#घोषणा CNIC_RD16(dev, off)		पढ़ोw(dev->regview + off)

काष्ठा cnic_ulp_ops अणु
	/* Calls to these functions are रक्षित by RCU.  When
	 * unरेजिस्टरing, we रुको क्रम any calls to complete beक्रमe
	 * continuing.
	 */

	व्योम (*cnic_init)(काष्ठा cnic_dev *dev);
	व्योम (*cnic_निकास)(काष्ठा cnic_dev *dev);
	व्योम (*cnic_start)(व्योम *ulp_ctx);
	व्योम (*cnic_stop)(व्योम *ulp_ctx);
	व्योम (*indicate_kcqes)(व्योम *ulp_ctx, काष्ठा kcqe *cqes[],
				u32 num_cqes);
	व्योम (*indicate_netevent)(व्योम *ulp_ctx, अचिन्हित दीर्घ event, u16 vid);
	व्योम (*cm_connect_complete)(काष्ठा cnic_sock *);
	व्योम (*cm_बंद_complete)(काष्ठा cnic_sock *);
	व्योम (*cm_पात_complete)(काष्ठा cnic_sock *);
	व्योम (*cm_remote_बंद)(काष्ठा cnic_sock *);
	व्योम (*cm_remote_पात)(काष्ठा cnic_sock *);
	पूर्णांक (*iscsi_nl_send_msg)(व्योम *ulp_ctx, u32 msg_type,
				  अक्षर *data, u16 data_size);
	पूर्णांक (*cnic_get_stats)(व्योम *ulp_ctx);
	काष्ठा module *owner;
	atomic_t ref_count;
पूर्ण;

पूर्णांक cnic_रेजिस्टर_driver(पूर्णांक ulp_type, काष्ठा cnic_ulp_ops *ulp_ops);

पूर्णांक cnic_unरेजिस्टर_driver(पूर्णांक ulp_type);

#पूर्ण_अगर
