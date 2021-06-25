<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004, 2020 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems.  All rights reserved.
 */

#अगर_अघोषित IB_VERBS_H
#घोषणा IB_VERBS_H

#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/irq_poll.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/refcount.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/cgroup_rdma.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/preempt.h>
#समावेश <linux/dim.h>
#समावेश <uapi/rdma/ib_user_verbs.h>
#समावेश <rdma/rdma_counter.h>
#समावेश <rdma/restrack.h>
#समावेश <rdma/signature.h>
#समावेश <uapi/rdma/rdma_user_ioctl.h>
#समावेश <uapi/rdma/ib_user_ioctl_verbs.h>

#घोषणा IB_FW_VERSION_NAME_MAX	ETHTOOL_FWVERS_LEN

काष्ठा ib_umem_odp;
काष्ठा ib_uqp_object;
काष्ठा ib_usrq_object;
काष्ठा ib_uwq_object;
काष्ठा rdma_cm_id;

बाह्य काष्ठा workqueue_काष्ठा *ib_wq;
बाह्य काष्ठा workqueue_काष्ठा *ib_comp_wq;
बाह्य काष्ठा workqueue_काष्ठा *ib_comp_unbound_wq;

काष्ठा ib_ucq_object;

__म_लिखो(3, 4) __cold
व्योम ibdev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा ib_device *ibdev,
		  स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_emerg(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_alert(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_crit(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_err(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_warn(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_notice(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम ibdev_info(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...);

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#घोषणा ibdev_dbg(__dev, क्रमmat, args...)                       \
	dynamic_ibdev_dbg(__dev, क्रमmat, ##args)
#अन्यथा
__म_लिखो(2, 3) __cold
अटल अंतरभूत
व्योम ibdev_dbg(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...) अणुपूर्ण
#पूर्ण_अगर

#घोषणा ibdev_level_ratelimited(ibdev_level, ibdev, fmt, ...)           \
करो अणु                                                                    \
	अटल DEFINE_RATELIMIT_STATE(_rs,                              \
				      DEFAULT_RATELIMIT_INTERVAL,       \
				      DEFAULT_RATELIMIT_BURST);         \
	अगर (__ratelimit(&_rs))                                          \
		ibdev_level(ibdev, fmt, ##__VA_ARGS__);                 \
पूर्ण जबतक (0)

#घोषणा ibdev_emerg_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_emerg, ibdev, fmt, ##__VA_ARGS__)
#घोषणा ibdev_alert_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_alert, ibdev, fmt, ##__VA_ARGS__)
#घोषणा ibdev_crit_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_crit, ibdev, fmt, ##__VA_ARGS__)
#घोषणा ibdev_err_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_err, ibdev, fmt, ##__VA_ARGS__)
#घोषणा ibdev_warn_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_warn, ibdev, fmt, ##__VA_ARGS__)
#घोषणा ibdev_notice_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_notice, ibdev, fmt, ##__VA_ARGS__)
#घोषणा ibdev_info_ratelimited(ibdev, fmt, ...) \
	ibdev_level_ratelimited(ibdev_info, ibdev, fmt, ##__VA_ARGS__)

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
/* descriptor check is first to prevent flooding with "callbacks suppressed" */
#घोषणा ibdev_dbg_ratelimited(ibdev, fmt, ...)                          \
करो अणु                                                                    \
	अटल DEFINE_RATELIMIT_STATE(_rs,                              \
				      DEFAULT_RATELIMIT_INTERVAL,       \
				      DEFAULT_RATELIMIT_BURST);         \
	DEFINE_DYNAMIC_DEBUG_METADATA(descriptor, fmt);                 \
	अगर (DYNAMIC_DEBUG_BRANCH(descriptor) && __ratelimit(&_rs))      \
		__dynamic_ibdev_dbg(&descriptor, ibdev, fmt,            \
				    ##__VA_ARGS__);                     \
पूर्ण जबतक (0)
#अन्यथा
__म_लिखो(2, 3) __cold
अटल अंतरभूत
व्योम ibdev_dbg_ratelimited(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *क्रमmat, ...) अणुपूर्ण
#पूर्ण_अगर

जोड़ ib_gid अणु
	u8	raw[16];
	काष्ठा अणु
		__be64	subnet_prefix;
		__be64	पूर्णांकerface_id;
	पूर्ण global;
पूर्ण;

बाह्य जोड़ ib_gid zgid;

क्रमागत ib_gid_type अणु
	IB_GID_TYPE_IB = IB_UVERBS_GID_TYPE_IB,
	IB_GID_TYPE_ROCE = IB_UVERBS_GID_TYPE_ROCE_V1,
	IB_GID_TYPE_ROCE_UDP_ENCAP = IB_UVERBS_GID_TYPE_ROCE_V2,
	IB_GID_TYPE_SIZE
पूर्ण;

#घोषणा ROCE_V2_UDP_DPORT      4791
काष्ठा ib_gid_attr अणु
	काष्ठा net_device __rcu	*ndev;
	काष्ठा ib_device	*device;
	जोड़ ib_gid		gid;
	क्रमागत ib_gid_type	gid_type;
	u16			index;
	u32			port_num;
पूर्ण;

क्रमागत अणु
	/* set the local administered indication */
	IB_SA_WELL_KNOWN_GUID	= BIT_ULL(57) | 2,
पूर्ण;

क्रमागत rdma_transport_type अणु
	RDMA_TRANSPORT_IB,
	RDMA_TRANSPORT_IWARP,
	RDMA_TRANSPORT_USNIC,
	RDMA_TRANSPORT_USNIC_UDP,
	RDMA_TRANSPORT_UNSPECIFIED,
पूर्ण;

क्रमागत rdma_protocol_type अणु
	RDMA_PROTOCOL_IB,
	RDMA_PROTOCOL_IBOE,
	RDMA_PROTOCOL_IWARP,
	RDMA_PROTOCOL_USNIC_UDP
पूर्ण;

__attribute_स्थिर__ क्रमागत rdma_transport_type
rdma_node_get_transport(अचिन्हित पूर्णांक node_type);

क्रमागत rdma_network_type अणु
	RDMA_NETWORK_IB,
	RDMA_NETWORK_ROCE_V1,
	RDMA_NETWORK_IPV4,
	RDMA_NETWORK_IPV6
पूर्ण;

अटल अंतरभूत क्रमागत ib_gid_type ib_network_to_gid_type(क्रमागत rdma_network_type network_type)
अणु
	अगर (network_type == RDMA_NETWORK_IPV4 ||
	    network_type == RDMA_NETWORK_IPV6)
		वापस IB_GID_TYPE_ROCE_UDP_ENCAP;
	अन्यथा अगर (network_type == RDMA_NETWORK_ROCE_V1)
		वापस IB_GID_TYPE_ROCE;
	अन्यथा
		वापस IB_GID_TYPE_IB;
पूर्ण

अटल अंतरभूत क्रमागत rdma_network_type
rdma_gid_attr_network_type(स्थिर काष्ठा ib_gid_attr *attr)
अणु
	अगर (attr->gid_type == IB_GID_TYPE_IB)
		वापस RDMA_NETWORK_IB;

	अगर (attr->gid_type == IB_GID_TYPE_ROCE)
		वापस RDMA_NETWORK_ROCE_V1;

	अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)&attr->gid))
		वापस RDMA_NETWORK_IPV4;
	अन्यथा
		वापस RDMA_NETWORK_IPV6;
पूर्ण

क्रमागत rdma_link_layer अणु
	IB_LINK_LAYER_UNSPECIFIED,
	IB_LINK_LAYER_INFINIBAND,
	IB_LINK_LAYER_ETHERNET,
पूर्ण;

क्रमागत ib_device_cap_flags अणु
	IB_DEVICE_RESIZE_MAX_WR			= (1 << 0),
	IB_DEVICE_BAD_PKEY_CNTR			= (1 << 1),
	IB_DEVICE_BAD_QKEY_CNTR			= (1 << 2),
	IB_DEVICE_RAW_MULTI			= (1 << 3),
	IB_DEVICE_AUTO_PATH_MIG			= (1 << 4),
	IB_DEVICE_CHANGE_PHY_PORT		= (1 << 5),
	IB_DEVICE_UD_AV_PORT_ENFORCE		= (1 << 6),
	IB_DEVICE_CURR_QP_STATE_MOD		= (1 << 7),
	IB_DEVICE_SHUTDOWN_PORT			= (1 << 8),
	/* Not in use, क्रमmer INIT_TYPE		= (1 << 9),*/
	IB_DEVICE_PORT_ACTIVE_EVENT		= (1 << 10),
	IB_DEVICE_SYS_IMAGE_GUID		= (1 << 11),
	IB_DEVICE_RC_RNR_NAK_GEN		= (1 << 12),
	IB_DEVICE_SRQ_RESIZE			= (1 << 13),
	IB_DEVICE_N_NOTIFY_CQ			= (1 << 14),

	/*
	 * This device supports a per-device lkey or stag that can be
	 * used without perक्रमming a memory registration क्रम the local
	 * memory.  Note that ULPs should never check this flag, but
	 * instead of use the local_dma_lkey flag in the ib_pd काष्ठाure,
	 * which will always contain a usable lkey.
	 */
	IB_DEVICE_LOCAL_DMA_LKEY		= (1 << 15),
	/* Reserved, old SEND_W_INV		= (1 << 16),*/
	IB_DEVICE_MEM_WINDOW			= (1 << 17),
	/*
	 * Devices should set IB_DEVICE_UD_IP_SUM अगर they support
	 * insertion of UDP and TCP checksum on outgoing UD IPoIB
	 * messages and can verअगरy the validity of checksum क्रम
	 * incoming messages.  Setting this flag implies that the
	 * IPoIB driver may set NETIF_F_IP_CSUM क्रम datagram mode.
	 */
	IB_DEVICE_UD_IP_CSUM			= (1 << 18),
	IB_DEVICE_UD_TSO			= (1 << 19),
	IB_DEVICE_XRC				= (1 << 20),

	/*
	 * This device supports the IB "base memory management extension",
	 * which includes support क्रम fast registrations (IB_WR_REG_MR,
	 * IB_WR_LOCAL_INV and IB_WR_SEND_WITH_INV verbs).  This flag should
	 * also be set by any iWarp device which must support FRs to comply
	 * to the iWarp verbs spec.  iWarp devices also support the
	 * IB_WR_RDMA_READ_WITH_INV verb क्रम RDMA READs that invalidate the
	 * stag.
	 */
	IB_DEVICE_MEM_MGT_EXTENSIONS		= (1 << 21),
	IB_DEVICE_BLOCK_MULTICAST_LOOPBACK	= (1 << 22),
	IB_DEVICE_MEM_WINDOW_TYPE_2A		= (1 << 23),
	IB_DEVICE_MEM_WINDOW_TYPE_2B		= (1 << 24),
	IB_DEVICE_RC_IP_CSUM			= (1 << 25),
	/* Deprecated. Please use IB_RAW_PACKET_CAP_IP_CSUM. */
	IB_DEVICE_RAW_IP_CSUM			= (1 << 26),
	/*
	 * Devices should set IB_DEVICE_CROSS_CHANNEL अगर they
	 * support execution of WQEs that involve synchronization
	 * of I/O operations with single completion queue managed
	 * by hardware.
	 */
	IB_DEVICE_CROSS_CHANNEL			= (1 << 27),
	IB_DEVICE_MANAGED_FLOW_STEERING		= (1 << 29),
	IB_DEVICE_INTEGRITY_HANDOVER		= (1 << 30),
	IB_DEVICE_ON_DEMAND_PAGING		= (1ULL << 31),
	IB_DEVICE_SG_GAPS_REG			= (1ULL << 32),
	IB_DEVICE_VIRTUAL_FUNCTION		= (1ULL << 33),
	/* Deprecated. Please use IB_RAW_PACKET_CAP_SCATTER_FCS. */
	IB_DEVICE_RAW_SCATTER_FCS		= (1ULL << 34),
	IB_DEVICE_RDMA_NETDEV_OPA		= (1ULL << 35),
	/* The device supports padding incoming ग_लिखोs to cacheline. */
	IB_DEVICE_PCI_WRITE_END_PADDING		= (1ULL << 36),
	IB_DEVICE_ALLOW_USER_UNREG		= (1ULL << 37),
पूर्ण;

क्रमागत ib_atomic_cap अणु
	IB_ATOMIC_NONE,
	IB_ATOMIC_HCA,
	IB_ATOMIC_GLOB
पूर्ण;

क्रमागत ib_odp_general_cap_bits अणु
	IB_ODP_SUPPORT		= 1 << 0,
	IB_ODP_SUPPORT_IMPLICIT = 1 << 1,
पूर्ण;

क्रमागत ib_odp_transport_cap_bits अणु
	IB_ODP_SUPPORT_SEND	= 1 << 0,
	IB_ODP_SUPPORT_RECV	= 1 << 1,
	IB_ODP_SUPPORT_WRITE	= 1 << 2,
	IB_ODP_SUPPORT_READ	= 1 << 3,
	IB_ODP_SUPPORT_ATOMIC	= 1 << 4,
	IB_ODP_SUPPORT_SRQ_RECV	= 1 << 5,
पूर्ण;

काष्ठा ib_odp_caps अणु
	uपूर्णांक64_t general_caps;
	काष्ठा अणु
		uपूर्णांक32_t  rc_odp_caps;
		uपूर्णांक32_t  uc_odp_caps;
		uपूर्णांक32_t  ud_odp_caps;
		uपूर्णांक32_t  xrc_odp_caps;
	पूर्ण per_transport_caps;
पूर्ण;

काष्ठा ib_rss_caps अणु
	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported, e.g.
	 * supported_qpts |= 1 << IB_QPT_UD
	 */
	u32 supported_qpts;
	u32 max_rwq_indirection_tables;
	u32 max_rwq_indirection_table_size;
पूर्ण;

क्रमागत ib_पंचांग_cap_flags अणु
	/*  Support tag matching with rendezvous offload क्रम RC transport */
	IB_TM_CAP_RNDV_RC = 1 << 0,
पूर्ण;

काष्ठा ib_पंचांग_caps अणु
	/* Max size of RNDV header */
	u32 max_rndv_hdr_size;
	/* Max number of entries in tag matching list */
	u32 max_num_tags;
	/* From क्रमागत ib_पंचांग_cap_flags */
	u32 flags;
	/* Max number of outstanding list operations */
	u32 max_ops;
	/* Max number of SGE in tag matching entry */
	u32 max_sge;
पूर्ण;

काष्ठा ib_cq_init_attr अणु
	अचिन्हित पूर्णांक	cqe;
	u32		comp_vector;
	u32		flags;
पूर्ण;

क्रमागत ib_cq_attr_mask अणु
	IB_CQ_MODERATE = 1 << 0,
पूर्ण;

काष्ठा ib_cq_caps अणु
	u16     max_cq_moderation_count;
	u16     max_cq_moderation_period;
पूर्ण;

काष्ठा ib_dm_mr_attr अणु
	u64		length;
	u64		offset;
	u32		access_flags;
पूर्ण;

काष्ठा ib_dm_alloc_attr अणु
	u64	length;
	u32	alignment;
	u32	flags;
पूर्ण;

काष्ठा ib_device_attr अणु
	u64			fw_ver;
	__be64			sys_image_guid;
	u64			max_mr_size;
	u64			page_size_cap;
	u32			venकरोr_id;
	u32			venकरोr_part_id;
	u32			hw_ver;
	पूर्णांक			max_qp;
	पूर्णांक			max_qp_wr;
	u64			device_cap_flags;
	पूर्णांक			max_send_sge;
	पूर्णांक			max_recv_sge;
	पूर्णांक			max_sge_rd;
	पूर्णांक			max_cq;
	पूर्णांक			max_cqe;
	पूर्णांक			max_mr;
	पूर्णांक			max_pd;
	पूर्णांक			max_qp_rd_atom;
	पूर्णांक			max_ee_rd_atom;
	पूर्णांक			max_res_rd_atom;
	पूर्णांक			max_qp_init_rd_atom;
	पूर्णांक			max_ee_init_rd_atom;
	क्रमागत ib_atomic_cap	atomic_cap;
	क्रमागत ib_atomic_cap	masked_atomic_cap;
	पूर्णांक			max_ee;
	पूर्णांक			max_rdd;
	पूर्णांक			max_mw;
	पूर्णांक			max_raw_ipv6_qp;
	पूर्णांक			max_raw_ethy_qp;
	पूर्णांक			max_mcast_grp;
	पूर्णांक			max_mcast_qp_attach;
	पूर्णांक			max_total_mcast_qp_attach;
	पूर्णांक			max_ah;
	पूर्णांक			max_srq;
	पूर्णांक			max_srq_wr;
	पूर्णांक			max_srq_sge;
	अचिन्हित पूर्णांक		max_fast_reg_page_list_len;
	अचिन्हित पूर्णांक		max_pi_fast_reg_page_list_len;
	u16			max_pkeys;
	u8			local_ca_ack_delay;
	पूर्णांक			sig_prot_cap;
	पूर्णांक			sig_guard_cap;
	काष्ठा ib_odp_caps	odp_caps;
	uपूर्णांक64_t		बारtamp_mask;
	uपूर्णांक64_t		hca_core_घड़ी; /* in KHZ */
	काष्ठा ib_rss_caps	rss_caps;
	u32			max_wq_type_rq;
	u32			raw_packet_caps; /* Use ib_raw_packet_caps क्रमागत */
	काष्ठा ib_पंचांग_caps	पंचांग_caps;
	काष्ठा ib_cq_caps       cq_caps;
	u64			max_dm_size;
	/* Max entries क्रम sgl क्रम optimized perक्रमmance per READ */
	u32			max_sgl_rd;
पूर्ण;

क्रमागत ib_mtu अणु
	IB_MTU_256  = 1,
	IB_MTU_512  = 2,
	IB_MTU_1024 = 3,
	IB_MTU_2048 = 4,
	IB_MTU_4096 = 5
पूर्ण;

क्रमागत opa_mtu अणु
	OPA_MTU_8192 = 6,
	OPA_MTU_10240 = 7
पूर्ण;

अटल अंतरभूत पूर्णांक ib_mtu_क्रमागत_to_पूर्णांक(क्रमागत ib_mtu mtu)
अणु
	चयन (mtu) अणु
	हाल IB_MTU_256:  वापस  256;
	हाल IB_MTU_512:  वापस  512;
	हाल IB_MTU_1024: वापस 1024;
	हाल IB_MTU_2048: वापस 2048;
	हाल IB_MTU_4096: वापस 4096;
	शेष: 	  वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत ib_mtu ib_mtu_पूर्णांक_to_क्रमागत(पूर्णांक mtu)
अणु
	अगर (mtu >= 4096)
		वापस IB_MTU_4096;
	अन्यथा अगर (mtu >= 2048)
		वापस IB_MTU_2048;
	अन्यथा अगर (mtu >= 1024)
		वापस IB_MTU_1024;
	अन्यथा अगर (mtu >= 512)
		वापस IB_MTU_512;
	अन्यथा
		वापस IB_MTU_256;
पूर्ण

अटल अंतरभूत पूर्णांक opa_mtu_क्रमागत_to_पूर्णांक(क्रमागत opa_mtu mtu)
अणु
	चयन (mtu) अणु
	हाल OPA_MTU_8192:
		वापस 8192;
	हाल OPA_MTU_10240:
		वापस 10240;
	शेष:
		वापस(ib_mtu_क्रमागत_to_पूर्णांक((क्रमागत ib_mtu)mtu));
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत opa_mtu opa_mtu_पूर्णांक_to_क्रमागत(पूर्णांक mtu)
अणु
	अगर (mtu >= 10240)
		वापस OPA_MTU_10240;
	अन्यथा अगर (mtu >= 8192)
		वापस OPA_MTU_8192;
	अन्यथा
		वापस ((क्रमागत opa_mtu)ib_mtu_पूर्णांक_to_क्रमागत(mtu));
पूर्ण

क्रमागत ib_port_state अणु
	IB_PORT_NOP		= 0,
	IB_PORT_DOWN		= 1,
	IB_PORT_INIT		= 2,
	IB_PORT_ARMED		= 3,
	IB_PORT_ACTIVE		= 4,
	IB_PORT_ACTIVE_DEFER	= 5
पूर्ण;

क्रमागत ib_port_phys_state अणु
	IB_PORT_PHYS_STATE_SLEEP = 1,
	IB_PORT_PHYS_STATE_POLLING = 2,
	IB_PORT_PHYS_STATE_DISABLED = 3,
	IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING = 4,
	IB_PORT_PHYS_STATE_LINK_UP = 5,
	IB_PORT_PHYS_STATE_LINK_ERROR_RECOVERY = 6,
	IB_PORT_PHYS_STATE_PHY_TEST = 7,
पूर्ण;

क्रमागत ib_port_width अणु
	IB_WIDTH_1X	= 1,
	IB_WIDTH_2X	= 16,
	IB_WIDTH_4X	= 2,
	IB_WIDTH_8X	= 4,
	IB_WIDTH_12X	= 8
पूर्ण;

अटल अंतरभूत पूर्णांक ib_width_क्रमागत_to_पूर्णांक(क्रमागत ib_port_width width)
अणु
	चयन (width) अणु
	हाल IB_WIDTH_1X:  वापस  1;
	हाल IB_WIDTH_2X:  वापस  2;
	हाल IB_WIDTH_4X:  वापस  4;
	हाल IB_WIDTH_8X:  वापस  8;
	हाल IB_WIDTH_12X: वापस 12;
	शेष: 	  वापस -1;
	पूर्ण
पूर्ण

क्रमागत ib_port_speed अणु
	IB_SPEED_SDR	= 1,
	IB_SPEED_DDR	= 2,
	IB_SPEED_QDR	= 4,
	IB_SPEED_FDR10	= 8,
	IB_SPEED_FDR	= 16,
	IB_SPEED_EDR	= 32,
	IB_SPEED_HDR	= 64,
	IB_SPEED_NDR	= 128,
पूर्ण;

/**
 * काष्ठा rdma_hw_stats
 * @lock - Mutex to protect parallel ग_लिखो access to lअगरespan and values
 *    of counters, which are 64bits and not guaranteeed to be written
 *    atomicaly on 32bits प्रणालीs.
 * @बारtamp - Used by the core code to track when the last update was
 * @lअगरespan - Used by the core code to determine how old the counters
 *   should be beक्रमe being updated again.  Stored in jअगरfies, शेषs
 *   to 10 milliseconds, drivers can override the शेष be specअगरying
 *   their own value during their allocation routine.
 * @name - Array of poपूर्णांकers to अटल names used क्रम the counters in
 *   directory.
 * @num_counters - How many hardware counters there are.  If name is
 *   लघुer than this number, a kernel oops will result.  Driver authors
 *   are encouraged to leave BUILD_BUG_ON(ARRAY_SIZE(@name) < num_counters)
 *   in their code to prevent this.
 * @value - Array of u64 counters that are accessed by the sysfs code and
 *   filled in by the drivers get_stats routine
 */
काष्ठा rdma_hw_stats अणु
	काष्ठा mutex	lock; /* Protect lअगरespan and values[] */
	अचिन्हित दीर्घ	बारtamp;
	अचिन्हित दीर्घ	lअगरespan;
	स्थिर अक्षर * स्थिर *names;
	पूर्णांक		num_counters;
	u64		value[];
पूर्ण;

#घोषणा RDMA_HW_STATS_DEFAULT_LIFESPAN 10
/**
 * rdma_alloc_hw_stats_काष्ठा - Helper function to allocate dynamic काष्ठा
 *   क्रम drivers.
 * @names - Array of अटल स्थिर अक्षर *
 * @num_counters - How many elements in array
 * @lअगरespan - How many milliseconds between updates
 */
अटल अंतरभूत काष्ठा rdma_hw_stats *rdma_alloc_hw_stats_काष्ठा(
		स्थिर अक्षर * स्थिर *names, पूर्णांक num_counters,
		अचिन्हित दीर्घ lअगरespan)
अणु
	काष्ठा rdma_hw_stats *stats;

	stats = kzalloc(माप(*stats) + num_counters * माप(u64),
			GFP_KERNEL);
	अगर (!stats)
		वापस शून्य;
	stats->names = names;
	stats->num_counters = num_counters;
	stats->lअगरespan = msecs_to_jअगरfies(lअगरespan);

	वापस stats;
पूर्ण


/* Define bits क्रम the various functionality this port needs to be supported by
 * the core.
 */
/* Management                           0x00000FFF */
#घोषणा RDMA_CORE_CAP_IB_MAD            0x00000001
#घोषणा RDMA_CORE_CAP_IB_SMI            0x00000002
#घोषणा RDMA_CORE_CAP_IB_CM             0x00000004
#घोषणा RDMA_CORE_CAP_IW_CM             0x00000008
#घोषणा RDMA_CORE_CAP_IB_SA             0x00000010
#घोषणा RDMA_CORE_CAP_OPA_MAD           0x00000020

/* Address क्रमmat                       0x000FF000 */
#घोषणा RDMA_CORE_CAP_AF_IB             0x00001000
#घोषणा RDMA_CORE_CAP_ETH_AH            0x00002000
#घोषणा RDMA_CORE_CAP_OPA_AH            0x00004000
#घोषणा RDMA_CORE_CAP_IB_GRH_REQUIRED   0x00008000

/* Protocol                             0xFFF00000 */
#घोषणा RDMA_CORE_CAP_PROT_IB           0x00100000
#घोषणा RDMA_CORE_CAP_PROT_ROCE         0x00200000
#घोषणा RDMA_CORE_CAP_PROT_IWARP        0x00400000
#घोषणा RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP 0x00800000
#घोषणा RDMA_CORE_CAP_PROT_RAW_PACKET   0x01000000
#घोषणा RDMA_CORE_CAP_PROT_USNIC        0x02000000

#घोषणा RDMA_CORE_PORT_IB_GRH_REQUIRED (RDMA_CORE_CAP_IB_GRH_REQUIRED \
					| RDMA_CORE_CAP_PROT_ROCE     \
					| RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP)

#घोषणा RDMA_CORE_PORT_IBA_IB          (RDMA_CORE_CAP_PROT_IB  \
					| RDMA_CORE_CAP_IB_MAD \
					| RDMA_CORE_CAP_IB_SMI \
					| RDMA_CORE_CAP_IB_CM  \
					| RDMA_CORE_CAP_IB_SA  \
					| RDMA_CORE_CAP_AF_IB)
#घोषणा RDMA_CORE_PORT_IBA_ROCE        (RDMA_CORE_CAP_PROT_ROCE \
					| RDMA_CORE_CAP_IB_MAD  \
					| RDMA_CORE_CAP_IB_CM   \
					| RDMA_CORE_CAP_AF_IB   \
					| RDMA_CORE_CAP_ETH_AH)
#घोषणा RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP			\
					(RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP \
					| RDMA_CORE_CAP_IB_MAD  \
					| RDMA_CORE_CAP_IB_CM   \
					| RDMA_CORE_CAP_AF_IB   \
					| RDMA_CORE_CAP_ETH_AH)
#घोषणा RDMA_CORE_PORT_IWARP           (RDMA_CORE_CAP_PROT_IWARP \
					| RDMA_CORE_CAP_IW_CM)
#घोषणा RDMA_CORE_PORT_INTEL_OPA       (RDMA_CORE_PORT_IBA_IB  \
					| RDMA_CORE_CAP_OPA_MAD)

#घोषणा RDMA_CORE_PORT_RAW_PACKET	(RDMA_CORE_CAP_PROT_RAW_PACKET)

#घोषणा RDMA_CORE_PORT_USNIC		(RDMA_CORE_CAP_PROT_USNIC)

काष्ठा ib_port_attr अणु
	u64			subnet_prefix;
	क्रमागत ib_port_state	state;
	क्रमागत ib_mtu		max_mtu;
	क्रमागत ib_mtu		active_mtu;
	u32                     phys_mtu;
	पूर्णांक			gid_tbl_len;
	अचिन्हित पूर्णांक		ip_gids:1;
	/* This is the value from PortInfo CapabilityMask, defined by IBA */
	u32			port_cap_flags;
	u32			max_msg_sz;
	u32			bad_pkey_cntr;
	u32			qkey_viol_cntr;
	u16			pkey_tbl_len;
	u32			sm_lid;
	u32			lid;
	u8			lmc;
	u8			max_vl_num;
	u8			sm_sl;
	u8			subnet_समयout;
	u8			init_type_reply;
	u8			active_width;
	u16			active_speed;
	u8                      phys_state;
	u16			port_cap_flags2;
पूर्ण;

क्रमागत ib_device_modअगरy_flags अणु
	IB_DEVICE_MODIFY_SYS_IMAGE_GUID	= 1 << 0,
	IB_DEVICE_MODIFY_NODE_DESC	= 1 << 1
पूर्ण;

#घोषणा IB_DEVICE_NODE_DESC_MAX 64

काष्ठा ib_device_modअगरy अणु
	u64	sys_image_guid;
	अक्षर	node_desc[IB_DEVICE_NODE_DESC_MAX];
पूर्ण;

क्रमागत ib_port_modअगरy_flags अणु
	IB_PORT_SHUTDOWN		= 1,
	IB_PORT_INIT_TYPE		= (1<<2),
	IB_PORT_RESET_QKEY_CNTR		= (1<<3),
	IB_PORT_OPA_MASK_CHG		= (1<<4)
पूर्ण;

काष्ठा ib_port_modअगरy अणु
	u32	set_port_cap_mask;
	u32	clr_port_cap_mask;
	u8	init_type;
पूर्ण;

क्रमागत ib_event_type अणु
	IB_EVENT_CQ_ERR,
	IB_EVENT_QP_FATAL,
	IB_EVENT_QP_REQ_ERR,
	IB_EVENT_QP_ACCESS_ERR,
	IB_EVENT_COMM_EST,
	IB_EVENT_SQ_DRAINED,
	IB_EVENT_PATH_MIG,
	IB_EVENT_PATH_MIG_ERR,
	IB_EVENT_DEVICE_FATAL,
	IB_EVENT_PORT_ACTIVE,
	IB_EVENT_PORT_ERR,
	IB_EVENT_LID_CHANGE,
	IB_EVENT_PKEY_CHANGE,
	IB_EVENT_SM_CHANGE,
	IB_EVENT_SRQ_ERR,
	IB_EVENT_SRQ_LIMIT_REACHED,
	IB_EVENT_QP_LAST_WQE_REACHED,
	IB_EVENT_CLIENT_REREGISTER,
	IB_EVENT_GID_CHANGE,
	IB_EVENT_WQ_FATAL,
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ ib_event_msg(क्रमागत ib_event_type event);

काष्ठा ib_event अणु
	काष्ठा ib_device	*device;
	जोड़ अणु
		काष्ठा ib_cq	*cq;
		काष्ठा ib_qp	*qp;
		काष्ठा ib_srq	*srq;
		काष्ठा ib_wq	*wq;
		u32		port_num;
	पूर्ण element;
	क्रमागत ib_event_type	event;
पूर्ण;

काष्ठा ib_event_handler अणु
	काष्ठा ib_device *device;
	व्योम            (*handler)(काष्ठा ib_event_handler *, काष्ठा ib_event *);
	काष्ठा list_head  list;
पूर्ण;

#घोषणा INIT_IB_EVENT_HANDLER(_ptr, _device, _handler)		\
	करो अणु							\
		(_ptr)->device  = _device;			\
		(_ptr)->handler = _handler;			\
		INIT_LIST_HEAD(&(_ptr)->list);			\
	पूर्ण जबतक (0)

काष्ठा ib_global_route अणु
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	जोड़ ib_gid	dgid;
	u32		flow_label;
	u8		sgid_index;
	u8		hop_limit;
	u8		traffic_class;
पूर्ण;

काष्ठा ib_grh अणु
	__be32		version_tclass_flow;
	__be16		paylen;
	u8		next_hdr;
	u8		hop_limit;
	जोड़ ib_gid	sgid;
	जोड़ ib_gid	dgid;
पूर्ण;

जोड़ rdma_network_hdr अणु
	काष्ठा ib_grh ibgrh;
	काष्ठा अणु
		/* The IB spec states that अगर it's IPv4, the header
		 * is located in the last 20 bytes of the header.
		 */
		u8		reserved[20];
		काष्ठा iphdr	roce4grh;
	पूर्ण;
पूर्ण;

#घोषणा IB_QPN_MASK		0xFFFFFF

क्रमागत अणु
	IB_MULTICAST_QPN = 0xffffff
पूर्ण;

#घोषणा IB_LID_PERMISSIVE	cpu_to_be16(0xFFFF)
#घोषणा IB_MULTICAST_LID_BASE	cpu_to_be16(0xC000)

क्रमागत ib_ah_flags अणु
	IB_AH_GRH	= 1
पूर्ण;

क्रमागत ib_rate अणु
	IB_RATE_PORT_CURRENT = 0,
	IB_RATE_2_5_GBPS = 2,
	IB_RATE_5_GBPS   = 5,
	IB_RATE_10_GBPS  = 3,
	IB_RATE_20_GBPS  = 6,
	IB_RATE_30_GBPS  = 4,
	IB_RATE_40_GBPS  = 7,
	IB_RATE_60_GBPS  = 8,
	IB_RATE_80_GBPS  = 9,
	IB_RATE_120_GBPS = 10,
	IB_RATE_14_GBPS  = 11,
	IB_RATE_56_GBPS  = 12,
	IB_RATE_112_GBPS = 13,
	IB_RATE_168_GBPS = 14,
	IB_RATE_25_GBPS  = 15,
	IB_RATE_100_GBPS = 16,
	IB_RATE_200_GBPS = 17,
	IB_RATE_300_GBPS = 18,
	IB_RATE_28_GBPS  = 19,
	IB_RATE_50_GBPS  = 20,
	IB_RATE_400_GBPS = 21,
	IB_RATE_600_GBPS = 22,
पूर्ण;

/**
 * ib_rate_to_mult - Convert the IB rate क्रमागत to a multiple of the
 * base rate of 2.5 Gbit/sec.  For example, IB_RATE_5_GBPS will be
 * converted to 2, since 5 Gbit/sec is 2 * 2.5 Gbit/sec.
 * @rate: rate to convert.
 */
__attribute_स्थिर__ पूर्णांक ib_rate_to_mult(क्रमागत ib_rate rate);

/**
 * ib_rate_to_mbps - Convert the IB rate क्रमागत to Mbps.
 * For example, IB_RATE_2_5_GBPS will be converted to 2500.
 * @rate: rate to convert.
 */
__attribute_स्थिर__ पूर्णांक ib_rate_to_mbps(क्रमागत ib_rate rate);


/**
 * क्रमागत ib_mr_type - memory region type
 * @IB_MR_TYPE_MEM_REG:       memory region that is used क्रम
 *                            normal registration
 * @IB_MR_TYPE_SG_GAPS:       memory region that is capable to
 *                            रेजिस्टर any arbitrary sg lists (without
 *                            the normal mr स्थिरraपूर्णांकs - see
 *                            ib_map_mr_sg)
 * @IB_MR_TYPE_DM:            memory region that is used क्रम device
 *                            memory registration
 * @IB_MR_TYPE_USER:          memory region that is used क्रम the user-space
 *                            application
 * @IB_MR_TYPE_DMA:           memory region that is used क्रम DMA operations
 *                            without address translations (VA=PA)
 * @IB_MR_TYPE_INTEGRITY:     memory region that is used क्रम
 *                            data पूर्णांकegrity operations
 */
क्रमागत ib_mr_type अणु
	IB_MR_TYPE_MEM_REG,
	IB_MR_TYPE_SG_GAPS,
	IB_MR_TYPE_DM,
	IB_MR_TYPE_USER,
	IB_MR_TYPE_DMA,
	IB_MR_TYPE_INTEGRITY,
पूर्ण;

क्रमागत ib_mr_status_check अणु
	IB_MR_CHECK_SIG_STATUS = 1,
पूर्ण;

/**
 * काष्ठा ib_mr_status - Memory region status container
 *
 * @fail_status: Biपंचांगask of MR checks status. For each
 *     failed check a corresponding status bit is set.
 * @sig_err: Additional info क्रम IB_MR_CEHCK_SIG_STATUS
 *     failure.
 */
काष्ठा ib_mr_status अणु
	u32		    fail_status;
	काष्ठा ib_sig_err   sig_err;
पूर्ण;

/**
 * mult_to_ib_rate - Convert a multiple of 2.5 Gbit/sec to an IB rate
 * क्रमागत.
 * @mult: multiple to convert.
 */
__attribute_स्थिर__ क्रमागत ib_rate mult_to_ib_rate(पूर्णांक mult);

काष्ठा rdma_ah_init_attr अणु
	काष्ठा rdma_ah_attr *ah_attr;
	u32 flags;
	काष्ठा net_device *xmit_slave;
पूर्ण;

क्रमागत rdma_ah_attr_type अणु
	RDMA_AH_ATTR_TYPE_UNDEFINED,
	RDMA_AH_ATTR_TYPE_IB,
	RDMA_AH_ATTR_TYPE_ROCE,
	RDMA_AH_ATTR_TYPE_OPA,
पूर्ण;

काष्ठा ib_ah_attr अणु
	u16			dlid;
	u8			src_path_bits;
पूर्ण;

काष्ठा roce_ah_attr अणु
	u8			dmac[ETH_ALEN];
पूर्ण;

काष्ठा opa_ah_attr अणु
	u32			dlid;
	u8			src_path_bits;
	bool			make_grd;
पूर्ण;

काष्ठा rdma_ah_attr अणु
	काष्ठा ib_global_route	grh;
	u8			sl;
	u8			अटल_rate;
	u32			port_num;
	u8			ah_flags;
	क्रमागत rdma_ah_attr_type type;
	जोड़ अणु
		काष्ठा ib_ah_attr ib;
		काष्ठा roce_ah_attr roce;
		काष्ठा opa_ah_attr opa;
	पूर्ण;
पूर्ण;

क्रमागत ib_wc_status अणु
	IB_WC_SUCCESS,
	IB_WC_LOC_LEN_ERR,
	IB_WC_LOC_QP_OP_ERR,
	IB_WC_LOC_EEC_OP_ERR,
	IB_WC_LOC_PROT_ERR,
	IB_WC_WR_FLUSH_ERR,
	IB_WC_MW_BIND_ERR,
	IB_WC_BAD_RESP_ERR,
	IB_WC_LOC_ACCESS_ERR,
	IB_WC_REM_INV_REQ_ERR,
	IB_WC_REM_ACCESS_ERR,
	IB_WC_REM_OP_ERR,
	IB_WC_RETRY_EXC_ERR,
	IB_WC_RNR_RETRY_EXC_ERR,
	IB_WC_LOC_RDD_VIOL_ERR,
	IB_WC_REM_INV_RD_REQ_ERR,
	IB_WC_REM_ABORT_ERR,
	IB_WC_INV_EECN_ERR,
	IB_WC_INV_EEC_STATE_ERR,
	IB_WC_FATAL_ERR,
	IB_WC_RESP_TIMEOUT_ERR,
	IB_WC_GENERAL_ERR
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ ib_wc_status_msg(क्रमागत ib_wc_status status);

क्रमागत ib_wc_opcode अणु
	IB_WC_SEND = IB_UVERBS_WC_SEND,
	IB_WC_RDMA_WRITE = IB_UVERBS_WC_RDMA_WRITE,
	IB_WC_RDMA_READ = IB_UVERBS_WC_RDMA_READ,
	IB_WC_COMP_SWAP = IB_UVERBS_WC_COMP_SWAP,
	IB_WC_FETCH_ADD = IB_UVERBS_WC_FETCH_ADD,
	IB_WC_BIND_MW = IB_UVERBS_WC_BIND_MW,
	IB_WC_LOCAL_INV = IB_UVERBS_WC_LOCAL_INV,
	IB_WC_LSO = IB_UVERBS_WC_TSO,
	IB_WC_REG_MR,
	IB_WC_MASKED_COMP_SWAP,
	IB_WC_MASKED_FETCH_ADD,
/*
 * Set value of IB_WC_RECV so consumers can test अगर a completion is a
 * receive by testing (opcode & IB_WC_RECV).
 */
	IB_WC_RECV			= 1 << 7,
	IB_WC_RECV_RDMA_WITH_IMM
पूर्ण;

क्रमागत ib_wc_flags अणु
	IB_WC_GRH		= 1,
	IB_WC_WITH_IMM		= (1<<1),
	IB_WC_WITH_INVALIDATE	= (1<<2),
	IB_WC_IP_CSUM_OK	= (1<<3),
	IB_WC_WITH_SMAC		= (1<<4),
	IB_WC_WITH_VLAN		= (1<<5),
	IB_WC_WITH_NETWORK_HDR_TYPE	= (1<<6),
पूर्ण;

काष्ठा ib_wc अणु
	जोड़ अणु
		u64		wr_id;
		काष्ठा ib_cqe	*wr_cqe;
	पूर्ण;
	क्रमागत ib_wc_status	status;
	क्रमागत ib_wc_opcode	opcode;
	u32			venकरोr_err;
	u32			byte_len;
	काष्ठा ib_qp	       *qp;
	जोड़ अणु
		__be32		imm_data;
		u32		invalidate_rkey;
	पूर्ण ex;
	u32			src_qp;
	u32			slid;
	पूर्णांक			wc_flags;
	u16			pkey_index;
	u8			sl;
	u8			dlid_path_bits;
	u32 port_num; /* valid only क्रम DR SMPs on चयनes */
	u8			smac[ETH_ALEN];
	u16			vlan_id;
	u8			network_hdr_type;
पूर्ण;

क्रमागत ib_cq_notअगरy_flags अणु
	IB_CQ_SOLICITED			= 1 << 0,
	IB_CQ_NEXT_COMP			= 1 << 1,
	IB_CQ_SOLICITED_MASK		= IB_CQ_SOLICITED | IB_CQ_NEXT_COMP,
	IB_CQ_REPORT_MISSED_EVENTS	= 1 << 2,
पूर्ण;

क्रमागत ib_srq_type अणु
	IB_SRQT_BASIC = IB_UVERBS_SRQT_BASIC,
	IB_SRQT_XRC = IB_UVERBS_SRQT_XRC,
	IB_SRQT_TM = IB_UVERBS_SRQT_TM,
पूर्ण;

अटल अंतरभूत bool ib_srq_has_cq(क्रमागत ib_srq_type srq_type)
अणु
	वापस srq_type == IB_SRQT_XRC ||
	       srq_type == IB_SRQT_TM;
पूर्ण

क्रमागत ib_srq_attr_mask अणु
	IB_SRQ_MAX_WR	= 1 << 0,
	IB_SRQ_LIMIT	= 1 << 1,
पूर्ण;

काष्ठा ib_srq_attr अणु
	u32	max_wr;
	u32	max_sge;
	u32	srq_limit;
पूर्ण;

काष्ठा ib_srq_init_attr अणु
	व्योम		      (*event_handler)(काष्ठा ib_event *, व्योम *);
	व्योम		       *srq_context;
	काष्ठा ib_srq_attr	attr;
	क्रमागत ib_srq_type	srq_type;

	काष्ठा अणु
		काष्ठा ib_cq   *cq;
		जोड़ अणु
			काष्ठा अणु
				काष्ठा ib_xrcd *xrcd;
			पूर्ण xrc;

			काष्ठा अणु
				u32		max_num_tags;
			पूर्ण tag_matching;
		पूर्ण;
	पूर्ण ext;
पूर्ण;

काष्ठा ib_qp_cap अणु
	u32	max_send_wr;
	u32	max_recv_wr;
	u32	max_send_sge;
	u32	max_recv_sge;
	u32	max_अंतरभूत_data;

	/*
	 * Maximum number of rdma_rw_ctx काष्ठाures in flight at a समय.
	 * ib_create_qp() will calculate the right amount of neededed WRs
	 * and MRs based on this.
	 */
	u32	max_rdma_ctxs;
पूर्ण;

क्रमागत ib_sig_type अणु
	IB_SIGNAL_ALL_WR,
	IB_SIGNAL_REQ_WR
पूर्ण;

क्रमागत ib_qp_type अणु
	/*
	 * IB_QPT_SMI and IB_QPT_GSI have to be the first two entries
	 * here (and in that order) since the MAD layer uses them as
	 * indices पूर्णांकo a 2-entry table.
	 */
	IB_QPT_SMI,
	IB_QPT_GSI,

	IB_QPT_RC = IB_UVERBS_QPT_RC,
	IB_QPT_UC = IB_UVERBS_QPT_UC,
	IB_QPT_UD = IB_UVERBS_QPT_UD,
	IB_QPT_RAW_IPV6,
	IB_QPT_RAW_ETHERTYPE,
	IB_QPT_RAW_PACKET = IB_UVERBS_QPT_RAW_PACKET,
	IB_QPT_XRC_INI = IB_UVERBS_QPT_XRC_INI,
	IB_QPT_XRC_TGT = IB_UVERBS_QPT_XRC_TGT,
	IB_QPT_MAX,
	IB_QPT_DRIVER = IB_UVERBS_QPT_DRIVER,
	/* Reserve a range क्रम qp types पूर्णांकernal to the low level driver.
	 * These qp types will not be visible at the IB core layer, so the
	 * IB_QPT_MAX usages should not be affected in the core layer
	 */
	IB_QPT_RESERVED1 = 0x1000,
	IB_QPT_RESERVED2,
	IB_QPT_RESERVED3,
	IB_QPT_RESERVED4,
	IB_QPT_RESERVED5,
	IB_QPT_RESERVED6,
	IB_QPT_RESERVED7,
	IB_QPT_RESERVED8,
	IB_QPT_RESERVED9,
	IB_QPT_RESERVED10,
पूर्ण;

क्रमागत ib_qp_create_flags अणु
	IB_QP_CREATE_IPOIB_UD_LSO		= 1 << 0,
	IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK	=
		IB_UVERBS_QP_CREATE_BLOCK_MULTICAST_LOOPBACK,
	IB_QP_CREATE_CROSS_CHANNEL              = 1 << 2,
	IB_QP_CREATE_MANAGED_SEND               = 1 << 3,
	IB_QP_CREATE_MANAGED_RECV               = 1 << 4,
	IB_QP_CREATE_NETIF_QP			= 1 << 5,
	IB_QP_CREATE_INTEGRITY_EN		= 1 << 6,
	IB_QP_CREATE_NETDEV_USE			= 1 << 7,
	IB_QP_CREATE_SCATTER_FCS		=
		IB_UVERBS_QP_CREATE_SCATTER_FCS,
	IB_QP_CREATE_CVLAN_STRIPPING		=
		IB_UVERBS_QP_CREATE_CVLAN_STRIPPING,
	IB_QP_CREATE_SOURCE_QPN			= 1 << 10,
	IB_QP_CREATE_PCI_WRITE_END_PADDING	=
		IB_UVERBS_QP_CREATE_PCI_WRITE_END_PADDING,
	/* reserve bits 26-31 क्रम low level drivers' पूर्णांकernal use */
	IB_QP_CREATE_RESERVED_START		= 1 << 26,
	IB_QP_CREATE_RESERVED_END		= 1 << 31,
पूर्ण;

/*
 * Note: users may not call ib_बंद_qp or ib_destroy_qp from the event_handler
 * callback to destroy the passed in QP.
 */

काष्ठा ib_qp_init_attr अणु
	/* Consumer's event_handler callback must not block */
	व्योम                  (*event_handler)(काष्ठा ib_event *, व्योम *);

	व्योम		       *qp_context;
	काष्ठा ib_cq	       *send_cq;
	काष्ठा ib_cq	       *recv_cq;
	काष्ठा ib_srq	       *srq;
	काष्ठा ib_xrcd	       *xrcd;     /* XRC TGT QPs only */
	काष्ठा ib_qp_cap	cap;
	क्रमागत ib_sig_type	sq_sig_type;
	क्रमागत ib_qp_type		qp_type;
	u32			create_flags;

	/*
	 * Only needed क्रम special QP types, or when using the RW API.
	 */
	u32			port_num;
	काष्ठा ib_rwq_ind_table *rwq_ind_tbl;
	u32			source_qpn;
पूर्ण;

काष्ठा ib_qp_खोलो_attr अणु
	व्योम                  (*event_handler)(काष्ठा ib_event *, व्योम *);
	व्योम		       *qp_context;
	u32			qp_num;
	क्रमागत ib_qp_type		qp_type;
पूर्ण;

क्रमागत ib_rnr_समयout अणु
	IB_RNR_TIMER_655_36 =  0,
	IB_RNR_TIMER_000_01 =  1,
	IB_RNR_TIMER_000_02 =  2,
	IB_RNR_TIMER_000_03 =  3,
	IB_RNR_TIMER_000_04 =  4,
	IB_RNR_TIMER_000_06 =  5,
	IB_RNR_TIMER_000_08 =  6,
	IB_RNR_TIMER_000_12 =  7,
	IB_RNR_TIMER_000_16 =  8,
	IB_RNR_TIMER_000_24 =  9,
	IB_RNR_TIMER_000_32 = 10,
	IB_RNR_TIMER_000_48 = 11,
	IB_RNR_TIMER_000_64 = 12,
	IB_RNR_TIMER_000_96 = 13,
	IB_RNR_TIMER_001_28 = 14,
	IB_RNR_TIMER_001_92 = 15,
	IB_RNR_TIMER_002_56 = 16,
	IB_RNR_TIMER_003_84 = 17,
	IB_RNR_TIMER_005_12 = 18,
	IB_RNR_TIMER_007_68 = 19,
	IB_RNR_TIMER_010_24 = 20,
	IB_RNR_TIMER_015_36 = 21,
	IB_RNR_TIMER_020_48 = 22,
	IB_RNR_TIMER_030_72 = 23,
	IB_RNR_TIMER_040_96 = 24,
	IB_RNR_TIMER_061_44 = 25,
	IB_RNR_TIMER_081_92 = 26,
	IB_RNR_TIMER_122_88 = 27,
	IB_RNR_TIMER_163_84 = 28,
	IB_RNR_TIMER_245_76 = 29,
	IB_RNR_TIMER_327_68 = 30,
	IB_RNR_TIMER_491_52 = 31
पूर्ण;

क्रमागत ib_qp_attr_mask अणु
	IB_QP_STATE			= 1,
	IB_QP_CUR_STATE			= (1<<1),
	IB_QP_EN_SQD_ASYNC_NOTIFY	= (1<<2),
	IB_QP_ACCESS_FLAGS		= (1<<3),
	IB_QP_PKEY_INDEX		= (1<<4),
	IB_QP_PORT			= (1<<5),
	IB_QP_QKEY			= (1<<6),
	IB_QP_AV			= (1<<7),
	IB_QP_PATH_MTU			= (1<<8),
	IB_QP_TIMEOUT			= (1<<9),
	IB_QP_RETRY_CNT			= (1<<10),
	IB_QP_RNR_RETRY			= (1<<11),
	IB_QP_RQ_PSN			= (1<<12),
	IB_QP_MAX_QP_RD_ATOMIC		= (1<<13),
	IB_QP_ALT_PATH			= (1<<14),
	IB_QP_MIN_RNR_TIMER		= (1<<15),
	IB_QP_SQ_PSN			= (1<<16),
	IB_QP_MAX_DEST_RD_ATOMIC	= (1<<17),
	IB_QP_PATH_MIG_STATE		= (1<<18),
	IB_QP_CAP			= (1<<19),
	IB_QP_DEST_QPN			= (1<<20),
	IB_QP_RESERVED1			= (1<<21),
	IB_QP_RESERVED2			= (1<<22),
	IB_QP_RESERVED3			= (1<<23),
	IB_QP_RESERVED4			= (1<<24),
	IB_QP_RATE_LIMIT		= (1<<25),

	IB_QP_ATTR_STANDARD_BITS = GENMASK(20, 0),
पूर्ण;

क्रमागत ib_qp_state अणु
	IB_QPS_RESET,
	IB_QPS_INIT,
	IB_QPS_RTR,
	IB_QPS_RTS,
	IB_QPS_SQD,
	IB_QPS_SQE,
	IB_QPS_ERR
पूर्ण;

क्रमागत ib_mig_state अणु
	IB_MIG_MIGRATED,
	IB_MIG_REARM,
	IB_MIG_ARMED
पूर्ण;

क्रमागत ib_mw_type अणु
	IB_MW_TYPE_1 = 1,
	IB_MW_TYPE_2 = 2
पूर्ण;

काष्ठा ib_qp_attr अणु
	क्रमागत ib_qp_state	qp_state;
	क्रमागत ib_qp_state	cur_qp_state;
	क्रमागत ib_mtu		path_mtu;
	क्रमागत ib_mig_state	path_mig_state;
	u32			qkey;
	u32			rq_psn;
	u32			sq_psn;
	u32			dest_qp_num;
	पूर्णांक			qp_access_flags;
	काष्ठा ib_qp_cap	cap;
	काष्ठा rdma_ah_attr	ah_attr;
	काष्ठा rdma_ah_attr	alt_ah_attr;
	u16			pkey_index;
	u16			alt_pkey_index;
	u8			en_sqd_async_notअगरy;
	u8			sq_draining;
	u8			max_rd_atomic;
	u8			max_dest_rd_atomic;
	u8			min_rnr_समयr;
	u32			port_num;
	u8			समयout;
	u8			retry_cnt;
	u8			rnr_retry;
	u32			alt_port_num;
	u8			alt_समयout;
	u32			rate_limit;
	काष्ठा net_device	*xmit_slave;
पूर्ण;

क्रमागत ib_wr_opcode अणु
	/* These are shared with userspace */
	IB_WR_RDMA_WRITE = IB_UVERBS_WR_RDMA_WRITE,
	IB_WR_RDMA_WRITE_WITH_IMM = IB_UVERBS_WR_RDMA_WRITE_WITH_IMM,
	IB_WR_SEND = IB_UVERBS_WR_SEND,
	IB_WR_SEND_WITH_IMM = IB_UVERBS_WR_SEND_WITH_IMM,
	IB_WR_RDMA_READ = IB_UVERBS_WR_RDMA_READ,
	IB_WR_ATOMIC_CMP_AND_SWP = IB_UVERBS_WR_ATOMIC_CMP_AND_SWP,
	IB_WR_ATOMIC_FETCH_AND_ADD = IB_UVERBS_WR_ATOMIC_FETCH_AND_ADD,
	IB_WR_BIND_MW = IB_UVERBS_WR_BIND_MW,
	IB_WR_LSO = IB_UVERBS_WR_TSO,
	IB_WR_SEND_WITH_INV = IB_UVERBS_WR_SEND_WITH_INV,
	IB_WR_RDMA_READ_WITH_INV = IB_UVERBS_WR_RDMA_READ_WITH_INV,
	IB_WR_LOCAL_INV = IB_UVERBS_WR_LOCAL_INV,
	IB_WR_MASKED_ATOMIC_CMP_AND_SWP =
		IB_UVERBS_WR_MASKED_ATOMIC_CMP_AND_SWP,
	IB_WR_MASKED_ATOMIC_FETCH_AND_ADD =
		IB_UVERBS_WR_MASKED_ATOMIC_FETCH_AND_ADD,

	/* These are kernel only and can not be issued by userspace */
	IB_WR_REG_MR = 0x20,
	IB_WR_REG_MR_INTEGRITY,

	/* reserve values क्रम low level drivers' पूर्णांकernal use.
	 * These values will not be used at all in the ib core layer.
	 */
	IB_WR_RESERVED1 = 0xf0,
	IB_WR_RESERVED2,
	IB_WR_RESERVED3,
	IB_WR_RESERVED4,
	IB_WR_RESERVED5,
	IB_WR_RESERVED6,
	IB_WR_RESERVED7,
	IB_WR_RESERVED8,
	IB_WR_RESERVED9,
	IB_WR_RESERVED10,
पूर्ण;

क्रमागत ib_send_flags अणु
	IB_SEND_FENCE		= 1,
	IB_SEND_SIGNALED	= (1<<1),
	IB_SEND_SOLICITED	= (1<<2),
	IB_SEND_INLINE		= (1<<3),
	IB_SEND_IP_CSUM		= (1<<4),

	/* reserve bits 26-31 क्रम low level drivers' पूर्णांकernal use */
	IB_SEND_RESERVED_START	= (1 << 26),
	IB_SEND_RESERVED_END	= (1 << 31),
पूर्ण;

काष्ठा ib_sge अणु
	u64	addr;
	u32	length;
	u32	lkey;
पूर्ण;

काष्ठा ib_cqe अणु
	व्योम (*करोne)(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
पूर्ण;

काष्ठा ib_send_wr अणु
	काष्ठा ib_send_wr      *next;
	जोड़ अणु
		u64		wr_id;
		काष्ठा ib_cqe	*wr_cqe;
	पूर्ण;
	काष्ठा ib_sge	       *sg_list;
	पूर्णांक			num_sge;
	क्रमागत ib_wr_opcode	opcode;
	पूर्णांक			send_flags;
	जोड़ अणु
		__be32		imm_data;
		u32		invalidate_rkey;
	पूर्ण ex;
पूर्ण;

काष्ठा ib_rdma_wr अणु
	काष्ठा ib_send_wr	wr;
	u64			remote_addr;
	u32			rkey;
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा ib_rdma_wr *rdma_wr(स्थिर काष्ठा ib_send_wr *wr)
अणु
	वापस container_of(wr, काष्ठा ib_rdma_wr, wr);
पूर्ण

काष्ठा ib_atomic_wr अणु
	काष्ठा ib_send_wr	wr;
	u64			remote_addr;
	u64			compare_add;
	u64			swap;
	u64			compare_add_mask;
	u64			swap_mask;
	u32			rkey;
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा ib_atomic_wr *atomic_wr(स्थिर काष्ठा ib_send_wr *wr)
अणु
	वापस container_of(wr, काष्ठा ib_atomic_wr, wr);
पूर्ण

काष्ठा ib_ud_wr अणु
	काष्ठा ib_send_wr	wr;
	काष्ठा ib_ah		*ah;
	व्योम			*header;
	पूर्णांक			hlen;
	पूर्णांक			mss;
	u32			remote_qpn;
	u32			remote_qkey;
	u16			pkey_index; /* valid क्रम GSI only */
	u32			port_num; /* valid क्रम DR SMPs on चयन only */
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा ib_ud_wr *ud_wr(स्थिर काष्ठा ib_send_wr *wr)
अणु
	वापस container_of(wr, काष्ठा ib_ud_wr, wr);
पूर्ण

काष्ठा ib_reg_wr अणु
	काष्ठा ib_send_wr	wr;
	काष्ठा ib_mr		*mr;
	u32			key;
	पूर्णांक			access;
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा ib_reg_wr *reg_wr(स्थिर काष्ठा ib_send_wr *wr)
अणु
	वापस container_of(wr, काष्ठा ib_reg_wr, wr);
पूर्ण

काष्ठा ib_recv_wr अणु
	काष्ठा ib_recv_wr      *next;
	जोड़ अणु
		u64		wr_id;
		काष्ठा ib_cqe	*wr_cqe;
	पूर्ण;
	काष्ठा ib_sge	       *sg_list;
	पूर्णांक			num_sge;
पूर्ण;

क्रमागत ib_access_flags अणु
	IB_ACCESS_LOCAL_WRITE = IB_UVERBS_ACCESS_LOCAL_WRITE,
	IB_ACCESS_REMOTE_WRITE = IB_UVERBS_ACCESS_REMOTE_WRITE,
	IB_ACCESS_REMOTE_READ = IB_UVERBS_ACCESS_REMOTE_READ,
	IB_ACCESS_REMOTE_ATOMIC = IB_UVERBS_ACCESS_REMOTE_ATOMIC,
	IB_ACCESS_MW_BIND = IB_UVERBS_ACCESS_MW_BIND,
	IB_ZERO_BASED = IB_UVERBS_ACCESS_ZERO_BASED,
	IB_ACCESS_ON_DEMAND = IB_UVERBS_ACCESS_ON_DEMAND,
	IB_ACCESS_HUGETLB = IB_UVERBS_ACCESS_HUGETLB,
	IB_ACCESS_RELAXED_ORDERING = IB_UVERBS_ACCESS_RELAXED_ORDERING,

	IB_ACCESS_OPTIONAL = IB_UVERBS_ACCESS_OPTIONAL_RANGE,
	IB_ACCESS_SUPPORTED =
		((IB_ACCESS_HUGETLB << 1) - 1) | IB_ACCESS_OPTIONAL,
पूर्ण;

/*
 * XXX: these are apparently used क्रम ->rereg_user_mr, no idea why they
 * are hidden here instead of a uapi header!
 */
क्रमागत ib_mr_rereg_flags अणु
	IB_MR_REREG_TRANS	= 1,
	IB_MR_REREG_PD		= (1<<1),
	IB_MR_REREG_ACCESS	= (1<<2),
	IB_MR_REREG_SUPPORTED	= ((IB_MR_REREG_ACCESS << 1) - 1)
पूर्ण;

काष्ठा ib_umem;

क्रमागत rdma_हटाओ_reason अणु
	/*
	 * Userspace requested uobject deletion or initial try
	 * to हटाओ uobject via cleanup. Call could fail
	 */
	RDMA_REMOVE_DESTROY,
	/* Context deletion. This call should delete the actual object itself */
	RDMA_REMOVE_CLOSE,
	/* Driver is being hot-unplugged. This call should delete the actual object itself */
	RDMA_REMOVE_DRIVER_REMOVE,
	/* uobj is being cleaned-up beक्रमe being committed */
	RDMA_REMOVE_ABORT,
	/* The driver failed to destroy the uobject and is being disconnected */
	RDMA_REMOVE_DRIVER_FAILURE,
पूर्ण;

काष्ठा ib_rdmacg_object अणु
#अगर_घोषित CONFIG_CGROUP_RDMA
	काष्ठा rdma_cgroup	*cg;		/* owner rdma cgroup */
#पूर्ण_अगर
पूर्ण;

काष्ठा ib_ucontext अणु
	काष्ठा ib_device       *device;
	काष्ठा ib_uverbs_file  *ufile;

	काष्ठा ib_rdmacg_object	cg_obj;
	/*
	 * Implementation details of the RDMA core, करोn't use in drivers:
	 */
	काष्ठा rdma_restrack_entry res;
	काष्ठा xarray mmap_xa;
पूर्ण;

काष्ठा ib_uobject अणु
	u64			user_handle;	/* handle given to us by userspace */
	/* ufile & ucontext owning this object */
	काष्ठा ib_uverbs_file  *ufile;
	/* FIXME, save memory: ufile->context == context */
	काष्ठा ib_ucontext     *context;	/* associated user context */
	व्योम		       *object;		/* containing object */
	काष्ठा list_head	list;		/* link to context's list */
	काष्ठा ib_rdmacg_object	cg_obj;		/* rdmacg object */
	पूर्णांक			id;		/* index पूर्णांकo kernel idr */
	काष्ठा kref		ref;
	atomic_t		usecnt;		/* protects exclusive access */
	काष्ठा rcu_head		rcu;		/* kमुक्त_rcu() overhead */

	स्थिर काष्ठा uverbs_api_object *uapi_object;
पूर्ण;

काष्ठा ib_udata अणु
	स्थिर व्योम __user *inbuf;
	व्योम __user *outbuf;
	माप_प्रकार       inlen;
	माप_प्रकार       outlen;
पूर्ण;

काष्ठा ib_pd अणु
	u32			local_dma_lkey;
	u32			flags;
	काष्ठा ib_device       *device;
	काष्ठा ib_uobject      *uobject;
	atomic_t          	usecnt; /* count all resources */

	u32			unsafe_global_rkey;

	/*
	 * Implementation details of the RDMA core, करोn't use in drivers:
	 */
	काष्ठा ib_mr	       *__पूर्णांकernal_mr;
	काष्ठा rdma_restrack_entry res;
पूर्ण;

काष्ठा ib_xrcd अणु
	काष्ठा ib_device       *device;
	atomic_t		usecnt; /* count all exposed resources */
	काष्ठा inode	       *inode;
	काष्ठा rw_semaphore	tgt_qps_rwsem;
	काष्ठा xarray		tgt_qps;
पूर्ण;

काष्ठा ib_ah अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_pd		*pd;
	काष्ठा ib_uobject	*uobject;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	क्रमागत rdma_ah_attr_type	type;
पूर्ण;

प्रकार व्योम (*ib_comp_handler)(काष्ठा ib_cq *cq, व्योम *cq_context);

क्रमागत ib_poll_context अणु
	IB_POLL_SOFTIRQ,	   /* poll from softirq context */
	IB_POLL_WORKQUEUE,	   /* poll from workqueue */
	IB_POLL_UNBOUND_WORKQUEUE, /* poll from unbound workqueue */
	IB_POLL_LAST_POOL_TYPE = IB_POLL_UNBOUND_WORKQUEUE,

	IB_POLL_सूचीECT,		   /* caller context, no hw completions */
पूर्ण;

काष्ठा ib_cq अणु
	काष्ठा ib_device       *device;
	काष्ठा ib_ucq_object   *uobject;
	ib_comp_handler   	comp_handler;
	व्योम                  (*event_handler)(काष्ठा ib_event *, व्योम *);
	व्योम                   *cq_context;
	पूर्णांक               	cqe;
	अचिन्हित पूर्णांक		cqe_used;
	atomic_t          	usecnt; /* count number of work queues */
	क्रमागत ib_poll_context	poll_ctx;
	काष्ठा ib_wc		*wc;
	काष्ठा list_head        pool_entry;
	जोड़ अणु
		काष्ठा irq_poll		iop;
		काष्ठा work_काष्ठा	work;
	पूर्ण;
	काष्ठा workqueue_काष्ठा *comp_wq;
	काष्ठा dim *dim;

	/* updated only by trace poपूर्णांकs */
	kसमय_प्रकार बारtamp;
	u8 पूर्णांकerrupt:1;
	u8 shared:1;
	अचिन्हित पूर्णांक comp_vector;

	/*
	 * Implementation details of the RDMA core, करोn't use in drivers:
	 */
	काष्ठा rdma_restrack_entry res;
पूर्ण;

काष्ठा ib_srq अणु
	काष्ठा ib_device       *device;
	काष्ठा ib_pd	       *pd;
	काष्ठा ib_usrq_object  *uobject;
	व्योम		      (*event_handler)(काष्ठा ib_event *, व्योम *);
	व्योम		       *srq_context;
	क्रमागत ib_srq_type	srq_type;
	atomic_t		usecnt;

	काष्ठा अणु
		काष्ठा ib_cq   *cq;
		जोड़ अणु
			काष्ठा अणु
				काष्ठा ib_xrcd *xrcd;
				u32		srq_num;
			पूर्ण xrc;
		पूर्ण;
	पूर्ण ext;

	/*
	 * Implementation details of the RDMA core, करोn't use in drivers:
	 */
	काष्ठा rdma_restrack_entry res;
पूर्ण;

क्रमागत ib_raw_packet_caps अणु
	/* Strip cvlan from incoming packet and report it in the matching work
	 * completion is supported.
	 */
	IB_RAW_PACKET_CAP_CVLAN_STRIPPING	= (1 << 0),
	/* Scatter FCS field of an incoming packet to host memory is supported.
	 */
	IB_RAW_PACKET_CAP_SCATTER_FCS		= (1 << 1),
	/* Checksum offloads are supported (क्रम both send and receive). */
	IB_RAW_PACKET_CAP_IP_CSUM		= (1 << 2),
	/* When a packet is received क्रम an RQ with no receive WQEs, the
	 * packet processing is delayed.
	 */
	IB_RAW_PACKET_CAP_DELAY_DROP		= (1 << 3),
पूर्ण;

क्रमागत ib_wq_type अणु
	IB_WQT_RQ = IB_UVERBS_WQT_RQ,
पूर्ण;

क्रमागत ib_wq_state अणु
	IB_WQS_RESET,
	IB_WQS_RDY,
	IB_WQS_ERR
पूर्ण;

काष्ठा ib_wq अणु
	काष्ठा ib_device       *device;
	काष्ठा ib_uwq_object   *uobject;
	व्योम		    *wq_context;
	व्योम		    (*event_handler)(काष्ठा ib_event *, व्योम *);
	काष्ठा ib_pd	       *pd;
	काष्ठा ib_cq	       *cq;
	u32		wq_num;
	क्रमागत ib_wq_state       state;
	क्रमागत ib_wq_type	wq_type;
	atomic_t		usecnt;
पूर्ण;

क्रमागत ib_wq_flags अणु
	IB_WQ_FLAGS_CVLAN_STRIPPING	= IB_UVERBS_WQ_FLAGS_CVLAN_STRIPPING,
	IB_WQ_FLAGS_SCATTER_FCS		= IB_UVERBS_WQ_FLAGS_SCATTER_FCS,
	IB_WQ_FLAGS_DELAY_DROP		= IB_UVERBS_WQ_FLAGS_DELAY_DROP,
	IB_WQ_FLAGS_PCI_WRITE_END_PADDING =
				IB_UVERBS_WQ_FLAGS_PCI_WRITE_END_PADDING,
पूर्ण;

काष्ठा ib_wq_init_attr अणु
	व्योम		       *wq_context;
	क्रमागत ib_wq_type	wq_type;
	u32		max_wr;
	u32		max_sge;
	काष्ठा	ib_cq	       *cq;
	व्योम		    (*event_handler)(काष्ठा ib_event *, व्योम *);
	u32		create_flags; /* Use क्रमागत ib_wq_flags */
पूर्ण;

क्रमागत ib_wq_attr_mask अणु
	IB_WQ_STATE		= 1 << 0,
	IB_WQ_CUR_STATE		= 1 << 1,
	IB_WQ_FLAGS		= 1 << 2,
पूर्ण;

काष्ठा ib_wq_attr अणु
	क्रमागत	ib_wq_state	wq_state;
	क्रमागत	ib_wq_state	curr_wq_state;
	u32			flags; /* Use क्रमागत ib_wq_flags */
	u32			flags_mask; /* Use क्रमागत ib_wq_flags */
पूर्ण;

काष्ठा ib_rwq_ind_table अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_uobject      *uobject;
	atomic_t		usecnt;
	u32		ind_tbl_num;
	u32		log_ind_tbl_size;
	काष्ठा ib_wq	**ind_tbl;
पूर्ण;

काष्ठा ib_rwq_ind_table_init_attr अणु
	u32		log_ind_tbl_size;
	/* Each entry is a poपूर्णांकer to Receive Work Queue */
	काष्ठा ib_wq	**ind_tbl;
पूर्ण;

क्रमागत port_pkey_state अणु
	IB_PORT_PKEY_NOT_VALID = 0,
	IB_PORT_PKEY_VALID = 1,
	IB_PORT_PKEY_LISTED = 2,
पूर्ण;

काष्ठा ib_qp_security;

काष्ठा ib_port_pkey अणु
	क्रमागत port_pkey_state	state;
	u16			pkey_index;
	u32			port_num;
	काष्ठा list_head	qp_list;
	काष्ठा list_head	to_error_list;
	काष्ठा ib_qp_security  *sec;
पूर्ण;

काष्ठा ib_ports_pkeys अणु
	काष्ठा ib_port_pkey	मुख्य;
	काष्ठा ib_port_pkey	alt;
पूर्ण;

काष्ठा ib_qp_security अणु
	काष्ठा ib_qp	       *qp;
	काष्ठा ib_device       *dev;
	/* Hold this mutex when changing port and pkey settings. */
	काष्ठा mutex		mutex;
	काष्ठा ib_ports_pkeys  *ports_pkeys;
	/* A list of all खोलो shared QP handles.  Required to enक्रमce security
	 * properly क्रम all users of a shared QP.
	 */
	काष्ठा list_head        shared_qp_list;
	व्योम                   *security;
	bool			destroying;
	atomic_t		error_list_count;
	काष्ठा completion	error_complete;
	पूर्णांक			error_comps_pending;
पूर्ण;

/*
 * @max_ग_लिखो_sge: Maximum SGE elements per RDMA WRITE request.
 * @max_पढ़ो_sge:  Maximum SGE elements per RDMA READ request.
 */
काष्ठा ib_qp अणु
	काष्ठा ib_device       *device;
	काष्ठा ib_pd	       *pd;
	काष्ठा ib_cq	       *send_cq;
	काष्ठा ib_cq	       *recv_cq;
	spinlock_t		mr_lock;
	पूर्णांक			mrs_used;
	काष्ठा list_head	rdma_mrs;
	काष्ठा list_head	sig_mrs;
	काष्ठा ib_srq	       *srq;
	काष्ठा ib_xrcd	       *xrcd; /* XRC TGT QPs only */
	काष्ठा list_head	xrcd_list;

	/* count बार खोलोed, mcast attaches, flow attaches */
	atomic_t		usecnt;
	काष्ठा list_head	खोलो_list;
	काष्ठा ib_qp           *real_qp;
	काष्ठा ib_uqp_object   *uobject;
	व्योम                  (*event_handler)(काष्ठा ib_event *, व्योम *);
	व्योम		       *qp_context;
	/* sgid_attrs associated with the AV's */
	स्थिर काष्ठा ib_gid_attr *av_sgid_attr;
	स्थिर काष्ठा ib_gid_attr *alt_path_sgid_attr;
	u32			qp_num;
	u32			max_ग_लिखो_sge;
	u32			max_पढ़ो_sge;
	क्रमागत ib_qp_type		qp_type;
	काष्ठा ib_rwq_ind_table *rwq_ind_tbl;
	काष्ठा ib_qp_security  *qp_sec;
	u32			port;

	bool			पूर्णांकegrity_en;
	/*
	 * Implementation details of the RDMA core, करोn't use in drivers:
	 */
	काष्ठा rdma_restrack_entry     res;

	/* The counter the qp is bind to */
	काष्ठा rdma_counter    *counter;
पूर्ण;

काष्ठा ib_dm अणु
	काष्ठा ib_device  *device;
	u32		   length;
	u32		   flags;
	काष्ठा ib_uobject *uobject;
	atomic_t	   usecnt;
पूर्ण;

काष्ठा ib_mr अणु
	काष्ठा ib_device  *device;
	काष्ठा ib_pd	  *pd;
	u32		   lkey;
	u32		   rkey;
	u64		   iova;
	u64		   length;
	अचिन्हित पूर्णांक	   page_size;
	क्रमागत ib_mr_type	   type;
	bool		   need_inval;
	जोड़ अणु
		काष्ठा ib_uobject	*uobject;	/* user */
		काष्ठा list_head	qp_entry;	/* FR */
	पूर्ण;

	काष्ठा ib_dm      *dm;
	काष्ठा ib_sig_attrs *sig_attrs; /* only क्रम IB_MR_TYPE_INTEGRITY MRs */
	/*
	 * Implementation details of the RDMA core, करोn't use in drivers:
	 */
	काष्ठा rdma_restrack_entry res;
पूर्ण;

काष्ठा ib_mw अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_pd		*pd;
	काष्ठा ib_uobject	*uobject;
	u32			rkey;
	क्रमागत ib_mw_type         type;
पूर्ण;

/* Supported steering options */
क्रमागत ib_flow_attr_type अणु
	/* steering according to rule specअगरications */
	IB_FLOW_ATTR_NORMAL		= 0x0,
	/* शेष unicast and multicast rule -
	 * receive all Eth traffic which isn't steered to any QP
	 */
	IB_FLOW_ATTR_ALL_DEFAULT	= 0x1,
	/* शेष multicast rule -
	 * receive all Eth multicast traffic which isn't steered to any QP
	 */
	IB_FLOW_ATTR_MC_DEFAULT		= 0x2,
	/* snअगरfer rule - receive all port traffic */
	IB_FLOW_ATTR_SNIFFER		= 0x3
पूर्ण;

/* Supported steering header types */
क्रमागत ib_flow_spec_type अणु
	/* L2 headers*/
	IB_FLOW_SPEC_ETH		= 0x20,
	IB_FLOW_SPEC_IB			= 0x22,
	/* L3 header*/
	IB_FLOW_SPEC_IPV4		= 0x30,
	IB_FLOW_SPEC_IPV6		= 0x31,
	IB_FLOW_SPEC_ESP                = 0x34,
	/* L4 headers*/
	IB_FLOW_SPEC_TCP		= 0x40,
	IB_FLOW_SPEC_UDP		= 0x41,
	IB_FLOW_SPEC_VXLAN_TUNNEL	= 0x50,
	IB_FLOW_SPEC_GRE		= 0x51,
	IB_FLOW_SPEC_MPLS		= 0x60,
	IB_FLOW_SPEC_INNER		= 0x100,
	/* Actions */
	IB_FLOW_SPEC_ACTION_TAG         = 0x1000,
	IB_FLOW_SPEC_ACTION_DROP        = 0x1001,
	IB_FLOW_SPEC_ACTION_HANDLE	= 0x1002,
	IB_FLOW_SPEC_ACTION_COUNT       = 0x1003,
पूर्ण;
#घोषणा IB_FLOW_SPEC_LAYER_MASK	0xF0
#घोषणा IB_FLOW_SPEC_SUPPORT_LAYERS 10

क्रमागत ib_flow_flags अणु
	IB_FLOW_ATTR_FLAGS_DONT_TRAP = 1UL << 1, /* Continue match, no steal */
	IB_FLOW_ATTR_FLAGS_EGRESS = 1UL << 2, /* Egress flow */
	IB_FLOW_ATTR_FLAGS_RESERVED  = 1UL << 3  /* Must be last */
पूर्ण;

काष्ठा ib_flow_eth_filter अणु
	u8	dst_mac[6];
	u8	src_mac[6];
	__be16	ether_type;
	__be16	vlan_tag;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_eth अणु
	u32			  type;
	u16			  size;
	काष्ठा ib_flow_eth_filter val;
	काष्ठा ib_flow_eth_filter mask;
पूर्ण;

काष्ठा ib_flow_ib_filter अणु
	__be16 dlid;
	__u8   sl;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_ib अणु
	u32			 type;
	u16			 size;
	काष्ठा ib_flow_ib_filter val;
	काष्ठा ib_flow_ib_filter mask;
पूर्ण;

/* IPv4 header flags */
क्रमागत ib_ipv4_flags अणु
	IB_IPV4_DONT_FRAG = 0x2, /* Don't enable packet fragmentation */
	IB_IPV4_MORE_FRAG = 0X4  /* For All fragmented packets except the
				    last have this flag set */
पूर्ण;

काष्ठा ib_flow_ipv4_filter अणु
	__be32	src_ip;
	__be32	dst_ip;
	u8	proto;
	u8	tos;
	u8	ttl;
	u8	flags;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_ipv4 अणु
	u32			   type;
	u16			   size;
	काष्ठा ib_flow_ipv4_filter val;
	काष्ठा ib_flow_ipv4_filter mask;
पूर्ण;

काष्ठा ib_flow_ipv6_filter अणु
	u8	src_ip[16];
	u8	dst_ip[16];
	__be32	flow_label;
	u8	next_hdr;
	u8	traffic_class;
	u8	hop_limit;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_ipv6 अणु
	u32			   type;
	u16			   size;
	काष्ठा ib_flow_ipv6_filter val;
	काष्ठा ib_flow_ipv6_filter mask;
पूर्ण;

काष्ठा ib_flow_tcp_udp_filter अणु
	__be16	dst_port;
	__be16	src_port;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_tcp_udp अणु
	u32			      type;
	u16			      size;
	काष्ठा ib_flow_tcp_udp_filter val;
	काष्ठा ib_flow_tcp_udp_filter mask;
पूर्ण;

काष्ठा ib_flow_tunnel_filter अणु
	__be32	tunnel_id;
	u8	real_sz[];
पूर्ण;

/* ib_flow_spec_tunnel describes the Vxlan tunnel
 * the tunnel_id from val has the vni value
 */
काष्ठा ib_flow_spec_tunnel अणु
	u32			      type;
	u16			      size;
	काष्ठा ib_flow_tunnel_filter  val;
	काष्ठा ib_flow_tunnel_filter  mask;
पूर्ण;

काष्ठा ib_flow_esp_filter अणु
	__be32	spi;
	__be32  seq;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_esp अणु
	u32                           type;
	u16			      size;
	काष्ठा ib_flow_esp_filter     val;
	काष्ठा ib_flow_esp_filter     mask;
पूर्ण;

काष्ठा ib_flow_gre_filter अणु
	__be16 c_ks_res0_ver;
	__be16 protocol;
	__be32 key;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_gre अणु
	u32                           type;
	u16			      size;
	काष्ठा ib_flow_gre_filter     val;
	काष्ठा ib_flow_gre_filter     mask;
पूर्ण;

काष्ठा ib_flow_mpls_filter अणु
	__be32 tag;
	/* Must be last */
	u8	real_sz[];
पूर्ण;

काष्ठा ib_flow_spec_mpls अणु
	u32                           type;
	u16			      size;
	काष्ठा ib_flow_mpls_filter     val;
	काष्ठा ib_flow_mpls_filter     mask;
पूर्ण;

काष्ठा ib_flow_spec_action_tag अणु
	क्रमागत ib_flow_spec_type	      type;
	u16			      size;
	u32                           tag_id;
पूर्ण;

काष्ठा ib_flow_spec_action_drop अणु
	क्रमागत ib_flow_spec_type	      type;
	u16			      size;
पूर्ण;

काष्ठा ib_flow_spec_action_handle अणु
	क्रमागत ib_flow_spec_type	      type;
	u16			      size;
	काष्ठा ib_flow_action	     *act;
पूर्ण;

क्रमागत ib_counters_description अणु
	IB_COUNTER_PACKETS,
	IB_COUNTER_BYTES,
पूर्ण;

काष्ठा ib_flow_spec_action_count अणु
	क्रमागत ib_flow_spec_type type;
	u16 size;
	काष्ठा ib_counters *counters;
पूर्ण;

जोड़ ib_flow_spec अणु
	काष्ठा अणु
		u32			type;
		u16			size;
	पूर्ण;
	काष्ठा ib_flow_spec_eth		eth;
	काष्ठा ib_flow_spec_ib		ib;
	काष्ठा ib_flow_spec_ipv4        ipv4;
	काष्ठा ib_flow_spec_tcp_udp	tcp_udp;
	काष्ठा ib_flow_spec_ipv6        ipv6;
	काष्ठा ib_flow_spec_tunnel      tunnel;
	काष्ठा ib_flow_spec_esp		esp;
	काष्ठा ib_flow_spec_gre		gre;
	काष्ठा ib_flow_spec_mpls	mpls;
	काष्ठा ib_flow_spec_action_tag  flow_tag;
	काष्ठा ib_flow_spec_action_drop drop;
	काष्ठा ib_flow_spec_action_handle action;
	काष्ठा ib_flow_spec_action_count flow_count;
पूर्ण;

काष्ठा ib_flow_attr अणु
	क्रमागत ib_flow_attr_type type;
	u16	     size;
	u16	     priority;
	u32	     flags;
	u8	     num_of_specs;
	u32	     port;
	जोड़ ib_flow_spec flows[];
पूर्ण;

काष्ठा ib_flow अणु
	काष्ठा ib_qp		*qp;
	काष्ठा ib_device	*device;
	काष्ठा ib_uobject	*uobject;
पूर्ण;

क्रमागत ib_flow_action_type अणु
	IB_FLOW_ACTION_UNSPECIFIED,
	IB_FLOW_ACTION_ESP = 1,
पूर्ण;

काष्ठा ib_flow_action_attrs_esp_keymats अणु
	क्रमागत ib_uverbs_flow_action_esp_keymat			protocol;
	जोड़ अणु
		काष्ठा ib_uverbs_flow_action_esp_keymat_aes_gcm aes_gcm;
	पूर्ण keymat;
पूर्ण;

काष्ठा ib_flow_action_attrs_esp_replays अणु
	क्रमागत ib_uverbs_flow_action_esp_replay			protocol;
	जोड़ अणु
		काष्ठा ib_uverbs_flow_action_esp_replay_bmp	bmp;
	पूर्ण replay;
पूर्ण;

क्रमागत ib_flow_action_attrs_esp_flags अणु
	/* All user-space flags at the top: Use क्रमागत ib_uverbs_flow_action_esp_flags
	 * This is करोne in order to share the same flags between user-space and
	 * kernel and spare an unnecessary translation.
	 */

	/* Kernel flags */
	IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED	= 1ULL << 32,
	IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS	= 1ULL << 33,
पूर्ण;

काष्ठा ib_flow_spec_list अणु
	काष्ठा ib_flow_spec_list	*next;
	जोड़ ib_flow_spec		spec;
पूर्ण;

काष्ठा ib_flow_action_attrs_esp अणु
	काष्ठा ib_flow_action_attrs_esp_keymats		*keymat;
	काष्ठा ib_flow_action_attrs_esp_replays		*replay;
	काष्ठा ib_flow_spec_list			*encap;
	/* Used only अगर IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED is enabled.
	 * Value of 0 is a valid value.
	 */
	u32						esn;
	u32						spi;
	u32						seq;
	u32						tfc_pad;
	/* Use क्रमागत ib_flow_action_attrs_esp_flags */
	u64						flags;
	u64						hard_limit_pkts;
पूर्ण;

काष्ठा ib_flow_action अणु
	काष्ठा ib_device		*device;
	काष्ठा ib_uobject		*uobject;
	क्रमागत ib_flow_action_type	type;
	atomic_t			usecnt;
पूर्ण;

काष्ठा ib_mad;
काष्ठा ib_grh;

क्रमागत ib_process_mad_flags अणु
	IB_MAD_IGNORE_MKEY	= 1,
	IB_MAD_IGNORE_BKEY	= 2,
	IB_MAD_IGNORE_ALL	= IB_MAD_IGNORE_MKEY | IB_MAD_IGNORE_BKEY
पूर्ण;

क्रमागत ib_mad_result अणु
	IB_MAD_RESULT_FAILURE  = 0,      /* (!SUCCESS is the important flag) */
	IB_MAD_RESULT_SUCCESS  = 1 << 0, /* MAD was successfully processed   */
	IB_MAD_RESULT_REPLY    = 1 << 1, /* Reply packet needs to be sent    */
	IB_MAD_RESULT_CONSUMED = 1 << 2  /* Packet consumed: stop processing */
पूर्ण;

काष्ठा ib_port_cache अणु
	u64		      subnet_prefix;
	काष्ठा ib_pkey_cache  *pkey;
	काष्ठा ib_gid_table   *gid;
	u8                     lmc;
	क्रमागत ib_port_state     port_state;
पूर्ण;

काष्ठा ib_port_immutable अणु
	पूर्णांक                           pkey_tbl_len;
	पूर्णांक                           gid_tbl_len;
	u32                           core_cap_flags;
	u32                           max_mad_size;
पूर्ण;

काष्ठा ib_port_data अणु
	काष्ठा ib_device *ib_dev;

	काष्ठा ib_port_immutable immutable;

	spinlock_t pkey_list_lock;
	काष्ठा list_head pkey_list;

	काष्ठा ib_port_cache cache;

	spinlock_t netdev_lock;
	काष्ठा net_device __rcu *netdev;
	काष्ठा hlist_node ndev_hash_link;
	काष्ठा rdma_port_counter port_counter;
	काष्ठा rdma_hw_stats *hw_stats;
पूर्ण;

/* rdma netdev type - specअगरies protocol type */
क्रमागत rdma_netdev_t अणु
	RDMA_NETDEV_OPA_VNIC,
	RDMA_NETDEV_IPOIB,
पूर्ण;

/**
 * काष्ठा rdma_netdev - rdma netdev
 * For हालs where netstack पूर्णांकerfacing is required.
 */
काष्ठा rdma_netdev अणु
	व्योम              *clnt_priv;
	काष्ठा ib_device  *hca;
	u32		   port_num;
	पूर्णांक                mtu;

	/*
	 * cleanup function must be specअगरied.
	 * FIXME: This is only used क्रम OPA_VNIC and that usage should be
	 * हटाओd too.
	 */
	व्योम (*मुक्त_rdma_netdev)(काष्ठा net_device *netdev);

	/* control functions */
	व्योम (*set_id)(काष्ठा net_device *netdev, पूर्णांक id);
	/* send packet */
	पूर्णांक (*send)(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		    काष्ठा ib_ah *address, u32 dqpn);
	/* multicast */
	पूर्णांक (*attach_mcast)(काष्ठा net_device *dev, काष्ठा ib_device *hca,
			    जोड़ ib_gid *gid, u16 mlid,
			    पूर्णांक set_qkey, u32 qkey);
	पूर्णांक (*detach_mcast)(काष्ठा net_device *dev, काष्ठा ib_device *hca,
			    जोड़ ib_gid *gid, u16 mlid);
	/* समयout */
	व्योम (*tx_समयout)(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
पूर्ण;

काष्ठा rdma_netdev_alloc_params अणु
	माप_प्रकार माप_priv;
	अचिन्हित पूर्णांक txqs;
	अचिन्हित पूर्णांक rxqs;
	व्योम *param;

	पूर्णांक (*initialize_rdma_netdev)(काष्ठा ib_device *device, u32 port_num,
				      काष्ठा net_device *netdev, व्योम *param);
पूर्ण;

काष्ठा ib_odp_counters अणु
	atomic64_t faults;
	atomic64_t invalidations;
	atomic64_t prefetch;
पूर्ण;

काष्ठा ib_counters अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_uobject	*uobject;
	/* num of objects attached */
	atomic_t	usecnt;
पूर्ण;

काष्ठा ib_counters_पढ़ो_attr अणु
	u64	*counters_buff;
	u32	ncounters;
	u32	flags; /* use क्रमागत ib_पढ़ो_counters_flags */
पूर्ण;

काष्ठा uverbs_attr_bundle;
काष्ठा iw_cm_id;
काष्ठा iw_cm_conn_param;

#घोषणा INIT_RDMA_OBJ_SIZE(ib_काष्ठा, drv_काष्ठा, member)                      \
	.size_##ib_काष्ठा =                                                    \
		(माप(काष्ठा drv_काष्ठा) +                                   \
		 BUILD_BUG_ON_ZERO(दुरत्व(काष्ठा drv_काष्ठा, member)) +      \
		 BUILD_BUG_ON_ZERO(                                            \
			 !__same_type(((काष्ठा drv_काष्ठा *)शून्य)->member,     \
				      काष्ठा ib_काष्ठा)))

#घोषणा rdma_zalloc_drv_obj_gfp(ib_dev, ib_type, gfp)                         \
	((काष्ठा ib_type *)kzalloc(ib_dev->ops.size_##ib_type, gfp))

#घोषणा rdma_zalloc_drv_obj(ib_dev, ib_type)                                   \
	rdma_zalloc_drv_obj_gfp(ib_dev, ib_type, GFP_KERNEL)

#घोषणा DECLARE_RDMA_OBJ_SIZE(ib_काष्ठा) माप_प्रकार size_##ib_काष्ठा

काष्ठा rdma_user_mmap_entry अणु
	काष्ठा kref ref;
	काष्ठा ib_ucontext *ucontext;
	अचिन्हित दीर्घ start_pgoff;
	माप_प्रकार npages;
	bool driver_हटाओd;
पूर्ण;

/* Return the offset (in bytes) the user should pass to libc's mmap() */
अटल अंतरभूत u64
rdma_user_mmap_get_offset(स्थिर काष्ठा rdma_user_mmap_entry *entry)
अणु
	वापस (u64)entry->start_pgoff << PAGE_SHIFT;
पूर्ण

/**
 * काष्ठा ib_device_ops - InfiniBand device operations
 * This काष्ठाure defines all the InfiniBand device operations, providers will
 * need to define the supported operations, otherwise they will be set to null.
 */
काष्ठा ib_device_ops अणु
	काष्ठा module *owner;
	क्रमागत rdma_driver_id driver_id;
	u32 uverbs_abi_ver;
	अचिन्हित पूर्णांक uverbs_no_driver_id_binding:1;

	पूर्णांक (*post_send)(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_send_wr *send_wr,
			 स्थिर काष्ठा ib_send_wr **bad_send_wr);
	पूर्णांक (*post_recv)(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_recv_wr *recv_wr,
			 स्थिर काष्ठा ib_recv_wr **bad_recv_wr);
	व्योम (*drain_rq)(काष्ठा ib_qp *qp);
	व्योम (*drain_sq)(काष्ठा ib_qp *qp);
	पूर्णांक (*poll_cq)(काष्ठा ib_cq *cq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
	पूर्णांक (*peek_cq)(काष्ठा ib_cq *cq, पूर्णांक wc_cnt);
	पूर्णांक (*req_notअगरy_cq)(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags);
	पूर्णांक (*post_srq_recv)(काष्ठा ib_srq *srq,
			     स्थिर काष्ठा ib_recv_wr *recv_wr,
			     स्थिर काष्ठा ib_recv_wr **bad_recv_wr);
	पूर्णांक (*process_mad)(काष्ठा ib_device *device, पूर्णांक process_mad_flags,
			   u32 port_num, स्थिर काष्ठा ib_wc *in_wc,
			   स्थिर काष्ठा ib_grh *in_grh,
			   स्थिर काष्ठा ib_mad *in_mad, काष्ठा ib_mad *out_mad,
			   माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index);
	पूर्णांक (*query_device)(काष्ठा ib_device *device,
			    काष्ठा ib_device_attr *device_attr,
			    काष्ठा ib_udata *udata);
	पूर्णांक (*modअगरy_device)(काष्ठा ib_device *device, पूर्णांक device_modअगरy_mask,
			     काष्ठा ib_device_modअगरy *device_modअगरy);
	व्योम (*get_dev_fw_str)(काष्ठा ib_device *device, अक्षर *str);
	स्थिर काष्ठा cpumask *(*get_vector_affinity)(काष्ठा ib_device *ibdev,
						     पूर्णांक comp_vector);
	पूर्णांक (*query_port)(काष्ठा ib_device *device, u32 port_num,
			  काष्ठा ib_port_attr *port_attr);
	पूर्णांक (*modअगरy_port)(काष्ठा ib_device *device, u32 port_num,
			   पूर्णांक port_modअगरy_mask,
			   काष्ठा ib_port_modअगरy *port_modअगरy);
	/**
	 * The following mandatory functions are used only at device
	 * registration.  Keep functions such as these at the end of this
	 * काष्ठाure to aव्योम cache line misses when accessing काष्ठा ib_device
	 * in fast paths.
	 */
	पूर्णांक (*get_port_immutable)(काष्ठा ib_device *device, u32 port_num,
				  काष्ठा ib_port_immutable *immutable);
	क्रमागत rdma_link_layer (*get_link_layer)(काष्ठा ib_device *device,
					       u32 port_num);
	/**
	 * When calling get_netdev, the HW venकरोr's driver should वापस the
	 * net device of device @device at port @port_num or शून्य अगर such
	 * a net device करोesn't exist. The venकरोr driver should call dev_hold
	 * on this net device. The HW venकरोr's device driver must guarantee
	 * that this function वापसs शून्य beक्रमe the net device has finished
	 * NETDEV_UNREGISTER state.
	 */
	काष्ठा net_device *(*get_netdev)(काष्ठा ib_device *device,
					 u32 port_num);
	/**
	 * rdma netdev operation
	 *
	 * Driver implementing alloc_rdma_netdev or rdma_netdev_get_params
	 * must वापस -EOPNOTSUPP अगर it करोesn't support the specअगरied type.
	 */
	काष्ठा net_device *(*alloc_rdma_netdev)(
		काष्ठा ib_device *device, u32 port_num, क्रमागत rdma_netdev_t type,
		स्थिर अक्षर *name, अचिन्हित अक्षर name_assign_type,
		व्योम (*setup)(काष्ठा net_device *));

	पूर्णांक (*rdma_netdev_get_params)(काष्ठा ib_device *device, u32 port_num,
				      क्रमागत rdma_netdev_t type,
				      काष्ठा rdma_netdev_alloc_params *params);
	/**
	 * query_gid should be वापस GID value क्रम @device, when @port_num
	 * link layer is either IB or iWarp. It is no-op अगर @port_num port
	 * is RoCE link layer.
	 */
	पूर्णांक (*query_gid)(काष्ठा ib_device *device, u32 port_num, पूर्णांक index,
			 जोड़ ib_gid *gid);
	/**
	 * When calling add_gid, the HW venकरोr's driver should add the gid
	 * of device of port at gid index available at @attr. Meta-info of
	 * that gid (क्रम example, the network device related to this gid) is
	 * available at @attr. @context allows the HW venकरोr driver to store
	 * extra inक्रमmation together with a GID entry. The HW venकरोr driver may
	 * allocate memory to contain this inक्रमmation and store it in @context
	 * when a new GID entry is written to. Params are consistent until the
	 * next call of add_gid or delete_gid. The function should वापस 0 on
	 * success or error otherwise. The function could be called
	 * concurrently क्रम dअगरferent ports. This function is only called when
	 * roce_gid_table is used.
	 */
	पूर्णांक (*add_gid)(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context);
	/**
	 * When calling del_gid, the HW venकरोr's driver should delete the
	 * gid of device @device at gid index gid_index of port port_num
	 * available in @attr.
	 * Upon the deletion of a GID entry, the HW venकरोr must मुक्त any
	 * allocated memory. The caller will clear @context afterwards.
	 * This function is only called when roce_gid_table is used.
	 */
	पूर्णांक (*del_gid)(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context);
	पूर्णांक (*query_pkey)(काष्ठा ib_device *device, u32 port_num, u16 index,
			  u16 *pkey);
	पूर्णांक (*alloc_ucontext)(काष्ठा ib_ucontext *context,
			      काष्ठा ib_udata *udata);
	व्योम (*dealloc_ucontext)(काष्ठा ib_ucontext *context);
	पूर्णांक (*mmap)(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma);
	/**
	 * This will be called once refcount of an entry in mmap_xa reaches
	 * zero. The type of the memory that was mapped may dअगरfer between
	 * entries and is opaque to the rdma_user_mmap पूर्णांकerface.
	 * Thereक्रमe needs to be implemented by the driver in mmap_मुक्त.
	 */
	व्योम (*mmap_मुक्त)(काष्ठा rdma_user_mmap_entry *entry);
	व्योम (*disassociate_ucontext)(काष्ठा ib_ucontext *ibcontext);
	पूर्णांक (*alloc_pd)(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
	पूर्णांक (*dealloc_pd)(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
	पूर्णांक (*create_ah)(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *attr,
			 काष्ठा ib_udata *udata);
	पूर्णांक (*create_user_ah)(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *attr,
			      काष्ठा ib_udata *udata);
	पूर्णांक (*modअगरy_ah)(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);
	पूर्णांक (*query_ah)(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);
	पूर्णांक (*destroy_ah)(काष्ठा ib_ah *ah, u32 flags);
	पूर्णांक (*create_srq)(काष्ठा ib_srq *srq,
			  काष्ठा ib_srq_init_attr *srq_init_attr,
			  काष्ठा ib_udata *udata);
	पूर्णांक (*modअगरy_srq)(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr,
			  क्रमागत ib_srq_attr_mask srq_attr_mask,
			  काष्ठा ib_udata *udata);
	पूर्णांक (*query_srq)(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr);
	पूर्णांक (*destroy_srq)(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata);
	काष्ठा ib_qp *(*create_qp)(काष्ठा ib_pd *pd,
				   काष्ठा ib_qp_init_attr *qp_init_attr,
				   काष्ठा ib_udata *udata);
	पूर्णांक (*modअगरy_qp)(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
			 पूर्णांक qp_attr_mask, काष्ठा ib_udata *udata);
	पूर्णांक (*query_qp)(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
			पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr);
	पूर्णांक (*destroy_qp)(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);
	पूर्णांक (*create_cq)(काष्ठा ib_cq *cq, स्थिर काष्ठा ib_cq_init_attr *attr,
			 काष्ठा ib_udata *udata);
	पूर्णांक (*modअगरy_cq)(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period);
	पूर्णांक (*destroy_cq)(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);
	पूर्णांक (*resize_cq)(काष्ठा ib_cq *cq, पूर्णांक cqe, काष्ठा ib_udata *udata);
	काष्ठा ib_mr *(*get_dma_mr)(काष्ठा ib_pd *pd, पूर्णांक mr_access_flags);
	काष्ठा ib_mr *(*reg_user_mr)(काष्ठा ib_pd *pd, u64 start, u64 length,
				     u64 virt_addr, पूर्णांक mr_access_flags,
				     काष्ठा ib_udata *udata);
	काष्ठा ib_mr *(*reg_user_mr_dmabuf)(काष्ठा ib_pd *pd, u64 offset,
					    u64 length, u64 virt_addr, पूर्णांक fd,
					    पूर्णांक mr_access_flags,
					    काष्ठा ib_udata *udata);
	काष्ठा ib_mr *(*rereg_user_mr)(काष्ठा ib_mr *mr, पूर्णांक flags, u64 start,
				       u64 length, u64 virt_addr,
				       पूर्णांक mr_access_flags, काष्ठा ib_pd *pd,
				       काष्ठा ib_udata *udata);
	पूर्णांक (*dereg_mr)(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata);
	काष्ठा ib_mr *(*alloc_mr)(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
				  u32 max_num_sg);
	काष्ठा ib_mr *(*alloc_mr_पूर्णांकegrity)(काष्ठा ib_pd *pd,
					    u32 max_num_data_sg,
					    u32 max_num_meta_sg);
	पूर्णांक (*advise_mr)(काष्ठा ib_pd *pd,
			 क्रमागत ib_uverbs_advise_mr_advice advice, u32 flags,
			 काष्ठा ib_sge *sg_list, u32 num_sge,
			 काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*map_mr_sg)(काष्ठा ib_mr *mr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
			 अचिन्हित पूर्णांक *sg_offset);
	पूर्णांक (*check_mr_status)(काष्ठा ib_mr *mr, u32 check_mask,
			       काष्ठा ib_mr_status *mr_status);
	पूर्णांक (*alloc_mw)(काष्ठा ib_mw *mw, काष्ठा ib_udata *udata);
	पूर्णांक (*dealloc_mw)(काष्ठा ib_mw *mw);
	पूर्णांक (*attach_mcast)(काष्ठा ib_qp *qp, जोड़ ib_gid *gid, u16 lid);
	पूर्णांक (*detach_mcast)(काष्ठा ib_qp *qp, जोड़ ib_gid *gid, u16 lid);
	पूर्णांक (*alloc_xrcd)(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata);
	पूर्णांक (*dealloc_xrcd)(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata);
	काष्ठा ib_flow *(*create_flow)(काष्ठा ib_qp *qp,
				       काष्ठा ib_flow_attr *flow_attr,
				       काष्ठा ib_udata *udata);
	पूर्णांक (*destroy_flow)(काष्ठा ib_flow *flow_id);
	काष्ठा ib_flow_action *(*create_flow_action_esp)(
		काष्ठा ib_device *device,
		स्थिर काष्ठा ib_flow_action_attrs_esp *attr,
		काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*destroy_flow_action)(काष्ठा ib_flow_action *action);
	पूर्णांक (*modअगरy_flow_action_esp)(
		काष्ठा ib_flow_action *action,
		स्थिर काष्ठा ib_flow_action_attrs_esp *attr,
		काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*set_vf_link_state)(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
				 पूर्णांक state);
	पूर्णांक (*get_vf_config)(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			     काष्ठा अगरla_vf_info *ivf);
	पूर्णांक (*get_vf_stats)(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			    काष्ठा अगरla_vf_stats *stats);
	पूर्णांक (*get_vf_guid)(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			    काष्ठा अगरla_vf_guid *node_guid,
			    काष्ठा अगरla_vf_guid *port_guid);
	पूर्णांक (*set_vf_guid)(काष्ठा ib_device *device, पूर्णांक vf, u32 port, u64 guid,
			   पूर्णांक type);
	काष्ठा ib_wq *(*create_wq)(काष्ठा ib_pd *pd,
				   काष्ठा ib_wq_init_attr *init_attr,
				   काष्ठा ib_udata *udata);
	पूर्णांक (*destroy_wq)(काष्ठा ib_wq *wq, काष्ठा ib_udata *udata);
	पूर्णांक (*modअगरy_wq)(काष्ठा ib_wq *wq, काष्ठा ib_wq_attr *attr,
			 u32 wq_attr_mask, काष्ठा ib_udata *udata);
	पूर्णांक (*create_rwq_ind_table)(काष्ठा ib_rwq_ind_table *ib_rwq_ind_table,
				    काष्ठा ib_rwq_ind_table_init_attr *init_attr,
				    काष्ठा ib_udata *udata);
	पूर्णांक (*destroy_rwq_ind_table)(काष्ठा ib_rwq_ind_table *wq_ind_table);
	काष्ठा ib_dm *(*alloc_dm)(काष्ठा ib_device *device,
				  काष्ठा ib_ucontext *context,
				  काष्ठा ib_dm_alloc_attr *attr,
				  काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*dealloc_dm)(काष्ठा ib_dm *dm, काष्ठा uverbs_attr_bundle *attrs);
	काष्ठा ib_mr *(*reg_dm_mr)(काष्ठा ib_pd *pd, काष्ठा ib_dm *dm,
				   काष्ठा ib_dm_mr_attr *attr,
				   काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*create_counters)(काष्ठा ib_counters *counters,
			       काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*destroy_counters)(काष्ठा ib_counters *counters);
	पूर्णांक (*पढ़ो_counters)(काष्ठा ib_counters *counters,
			     काष्ठा ib_counters_पढ़ो_attr *counters_पढ़ो_attr,
			     काष्ठा uverbs_attr_bundle *attrs);
	पूर्णांक (*map_mr_sg_pi)(काष्ठा ib_mr *mr, काष्ठा scatterlist *data_sg,
			    पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
			    काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
			    अचिन्हित पूर्णांक *meta_sg_offset);

	/**
	 * alloc_hw_stats - Allocate a काष्ठा rdma_hw_stats and fill in the
	 *   driver initialized data.  The काष्ठा is kमुक्त()'ed by the sysfs
	 *   core when the device is हटाओd.  A lअगरespan of -1 in the वापस
	 *   काष्ठा tells the core to set a शेष lअगरespan.
	 */
	काष्ठा rdma_hw_stats *(*alloc_hw_stats)(काष्ठा ib_device *device,
						u32 port_num);
	/**
	 * get_hw_stats - Fill in the counter value(s) in the stats काष्ठा.
	 * @index - The index in the value array we wish to have updated, or
	 *   num_counters अगर we want all stats updated
	 * Return codes -
	 *   < 0 - Error, no counters updated
	 *   index - Updated the single counter poपूर्णांकed to by index
	 *   num_counters - Updated all counters (will reset the बारtamp
	 *     and prevent further calls क्रम lअगरespan milliseconds)
	 * Drivers are allowed to update all counters in leiu of just the
	 *   one given in index at their option
	 */
	पूर्णांक (*get_hw_stats)(काष्ठा ib_device *device,
			    काष्ठा rdma_hw_stats *stats, u32 port, पूर्णांक index);
	/*
	 * This function is called once क्रम each port when a ib device is
	 * रेजिस्टरed.
	 */
	पूर्णांक (*init_port)(काष्ठा ib_device *device, u32 port_num,
			 काष्ठा kobject *port_sysfs);
	/**
	 * Allows rdma drivers to add their own restrack attributes.
	 */
	पूर्णांक (*fill_res_mr_entry)(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr);
	पूर्णांक (*fill_res_mr_entry_raw)(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr);
	पूर्णांक (*fill_res_cq_entry)(काष्ठा sk_buff *msg, काष्ठा ib_cq *ibcq);
	पूर्णांक (*fill_res_cq_entry_raw)(काष्ठा sk_buff *msg, काष्ठा ib_cq *ibcq);
	पूर्णांक (*fill_res_qp_entry)(काष्ठा sk_buff *msg, काष्ठा ib_qp *ibqp);
	पूर्णांक (*fill_res_qp_entry_raw)(काष्ठा sk_buff *msg, काष्ठा ib_qp *ibqp);
	पूर्णांक (*fill_res_cm_id_entry)(काष्ठा sk_buff *msg, काष्ठा rdma_cm_id *id);

	/* Device lअगरecycle callbacks */
	/*
	 * Called after the device becomes रेजिस्टरed, beक्रमe clients are
	 * attached
	 */
	पूर्णांक (*enable_driver)(काष्ठा ib_device *dev);
	/*
	 * This is called as part of ib_dealloc_device().
	 */
	व्योम (*dealloc_driver)(काष्ठा ib_device *dev);

	/* iWarp CM callbacks */
	व्योम (*iw_add_ref)(काष्ठा ib_qp *qp);
	व्योम (*iw_rem_ref)(काष्ठा ib_qp *qp);
	काष्ठा ib_qp *(*iw_get_qp)(काष्ठा ib_device *device, पूर्णांक qpn);
	पूर्णांक (*iw_connect)(काष्ठा iw_cm_id *cm_id,
			  काष्ठा iw_cm_conn_param *conn_param);
	पूर्णांक (*iw_accept)(काष्ठा iw_cm_id *cm_id,
			 काष्ठा iw_cm_conn_param *conn_param);
	पूर्णांक (*iw_reject)(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *pdata,
			 u8 pdata_len);
	पूर्णांक (*iw_create_listen)(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog);
	पूर्णांक (*iw_destroy_listen)(काष्ठा iw_cm_id *cm_id);
	/**
	 * counter_bind_qp - Bind a QP to a counter.
	 * @counter - The counter to be bound. If counter->id is zero then
	 *   the driver needs to allocate a new counter and set counter->id
	 */
	पूर्णांक (*counter_bind_qp)(काष्ठा rdma_counter *counter, काष्ठा ib_qp *qp);
	/**
	 * counter_unbind_qp - Unbind the qp from the dynamically-allocated
	 *   counter and bind it onto the शेष one
	 */
	पूर्णांक (*counter_unbind_qp)(काष्ठा ib_qp *qp);
	/**
	 * counter_dealloc -De-allocate the hw counter
	 */
	पूर्णांक (*counter_dealloc)(काष्ठा rdma_counter *counter);
	/**
	 * counter_alloc_stats - Allocate a काष्ठा rdma_hw_stats and fill in
	 * the driver initialized data.
	 */
	काष्ठा rdma_hw_stats *(*counter_alloc_stats)(
		काष्ठा rdma_counter *counter);
	/**
	 * counter_update_stats - Query the stats value of this counter
	 */
	पूर्णांक (*counter_update_stats)(काष्ठा rdma_counter *counter);

	/**
	 * Allows rdma drivers to add their own restrack attributes
	 * dumped via 'rdma stat' iproute2 command.
	 */
	पूर्णांक (*fill_stat_mr_entry)(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr);

	/* query driver क्रम its ucontext properties */
	पूर्णांक (*query_ucontext)(काष्ठा ib_ucontext *context,
			      काष्ठा uverbs_attr_bundle *attrs);

	DECLARE_RDMA_OBJ_SIZE(ib_ah);
	DECLARE_RDMA_OBJ_SIZE(ib_counters);
	DECLARE_RDMA_OBJ_SIZE(ib_cq);
	DECLARE_RDMA_OBJ_SIZE(ib_mw);
	DECLARE_RDMA_OBJ_SIZE(ib_pd);
	DECLARE_RDMA_OBJ_SIZE(ib_rwq_ind_table);
	DECLARE_RDMA_OBJ_SIZE(ib_srq);
	DECLARE_RDMA_OBJ_SIZE(ib_ucontext);
	DECLARE_RDMA_OBJ_SIZE(ib_xrcd);
पूर्ण;

काष्ठा ib_core_device अणु
	/* device must be the first element in काष्ठाure until,
	 * जोड़ of ib_core_device and device exists in ib_device.
	 */
	काष्ठा device dev;
	possible_net_t rdma_net;
	काष्ठा kobject *ports_kobj;
	काष्ठा list_head port_list;
	काष्ठा ib_device *owner; /* reach back to owner ib_device */
पूर्ण;

काष्ठा rdma_restrack_root;
काष्ठा ib_device अणु
	/* Do not access @dma_device directly from ULP nor from HW drivers. */
	काष्ठा device                *dma_device;
	काष्ठा ib_device_ops	     ops;
	अक्षर                          name[IB_DEVICE_NAME_MAX];
	काष्ठा rcu_head rcu_head;

	काष्ठा list_head              event_handler_list;
	/* Protects event_handler_list */
	काष्ठा rw_semaphore event_handler_rwsem;

	/* Protects QP's event_handler calls and खोलो_qp list */
	spinlock_t qp_खोलो_list_lock;

	काष्ठा rw_semaphore	      client_data_rwsem;
	काष्ठा xarray                 client_data;
	काष्ठा mutex                  unregistration_lock;

	/* Synchronize GID, Pkey cache entries, subnet prefix, LMC */
	rwlock_t cache_lock;
	/**
	 * port_data is indexed by port number
	 */
	काष्ठा ib_port_data *port_data;

	पूर्णांक			      num_comp_vectors;

	जोड़ अणु
		काष्ठा device		dev;
		काष्ठा ib_core_device	coredev;
	पूर्ण;

	/* First group क्रम device attributes,
	 * Second group क्रम driver provided attributes (optional).
	 * It is शून्य terminated array.
	 */
	स्थिर काष्ठा attribute_group	*groups[3];

	u64			     uverbs_cmd_mask;

	अक्षर			     node_desc[IB_DEVICE_NODE_DESC_MAX];
	__be64			     node_guid;
	u32			     local_dma_lkey;
	u16                          is_चयन:1;
	/* Indicates kernel verbs support, should not be used in drivers */
	u16                          kverbs_provider:1;
	/* CQ adaptive moderation (RDMA DIM) */
	u16                          use_cq_dim:1;
	u8                           node_type;
	u32			     phys_port_cnt;
	काष्ठा ib_device_attr        attrs;
	काष्ठा attribute_group	     *hw_stats_ag;
	काष्ठा rdma_hw_stats         *hw_stats;

#अगर_घोषित CONFIG_CGROUP_RDMA
	काष्ठा rdmacg_device         cg_device;
#पूर्ण_अगर

	u32                          index;

	spinlock_t                   cq_pools_lock;
	काष्ठा list_head             cq_pools[IB_POLL_LAST_POOL_TYPE + 1];

	काष्ठा rdma_restrack_root *res;

	स्थिर काष्ठा uapi_definition   *driver_def;

	/*
	 * Positive refcount indicates that the device is currently
	 * रेजिस्टरed and cannot be unरेजिस्टरed.
	 */
	refcount_t refcount;
	काष्ठा completion unreg_completion;
	काष्ठा work_काष्ठा unregistration_work;

	स्थिर काष्ठा rdma_link_ops *link_ops;

	/* Protects compat_devs xarray modअगरications */
	काष्ठा mutex compat_devs_mutex;
	/* Maपूर्णांकains compat devices क्रम each net namespace */
	काष्ठा xarray compat_devs;

	/* Used by iWarp CM */
	अक्षर iw_अगरname[IFNAMSIZ];
	u32 iw_driver_flags;
	u32 lag_flags;
पूर्ण;

काष्ठा ib_client_nl_info;
काष्ठा ib_client अणु
	स्थिर अक्षर *name;
	पूर्णांक (*add)(काष्ठा ib_device *ibdev);
	व्योम (*हटाओ)(काष्ठा ib_device *, व्योम *client_data);
	व्योम (*नाम)(काष्ठा ib_device *dev, व्योम *client_data);
	पूर्णांक (*get_nl_info)(काष्ठा ib_device *ibdev, व्योम *client_data,
			   काष्ठा ib_client_nl_info *res);
	पूर्णांक (*get_global_nl_info)(काष्ठा ib_client_nl_info *res);

	/* Returns the net_dev beदीर्घing to this ib_client and matching the
	 * given parameters.
	 * @dev:	 An RDMA device that the net_dev use क्रम communication.
	 * @port:	 A physical port number on the RDMA device.
	 * @pkey:	 P_Key that the net_dev uses अगर applicable.
	 * @gid:	 A GID that the net_dev uses to communicate.
	 * @addr:	 An IP address the net_dev is configured with.
	 * @client_data: The device's client data set by ib_set_client_data().
	 *
	 * An ib_client that implements a net_dev on top of RDMA devices
	 * (such as IP over IB) should implement this callback, allowing the
	 * rdma_cm module to find the right net_dev क्रम a given request.
	 *
	 * The caller is responsible क्रम calling dev_put on the वापसed
	 * netdev. */
	काष्ठा net_device *(*get_net_dev_by_params)(
			काष्ठा ib_device *dev,
			u32 port,
			u16 pkey,
			स्थिर जोड़ ib_gid *gid,
			स्थिर काष्ठा sockaddr *addr,
			व्योम *client_data);

	refcount_t uses;
	काष्ठा completion uses_zero;
	u32 client_id;

	/* kverbs are not required by the client */
	u8 no_kverbs_req:1;
पूर्ण;

/*
 * IB block DMA iterator
 *
 * Iterates the DMA-mapped SGL in contiguous memory blocks aligned
 * to a HW supported page size.
 */
काष्ठा ib_block_iter अणु
	/* पूर्णांकernal states */
	काष्ठा scatterlist *__sg;	/* sg holding the current aligned block */
	dma_addr_t __dma_addr;		/* unaligned DMA address of this block */
	अचिन्हित पूर्णांक __sg_nents;	/* number of SG entries */
	अचिन्हित पूर्णांक __sg_advance;	/* number of bytes to advance in sg in next step */
	अचिन्हित पूर्णांक __pg_bit;		/* alignment of current block */
पूर्ण;

काष्ठा ib_device *_ib_alloc_device(माप_प्रकार size);
#घोषणा ib_alloc_device(drv_काष्ठा, member)                                    \
	container_of(_ib_alloc_device(माप(काष्ठा drv_काष्ठा) +              \
				      BUILD_BUG_ON_ZERO(दुरत्व(              \
					      काष्ठा drv_काष्ठा, member))),    \
		     काष्ठा drv_काष्ठा, member)

व्योम ib_dealloc_device(काष्ठा ib_device *device);

व्योम ib_get_device_fw_str(काष्ठा ib_device *device, अक्षर *str);

पूर्णांक ib_रेजिस्टर_device(काष्ठा ib_device *device, स्थिर अक्षर *name,
		       काष्ठा device *dma_device);
व्योम ib_unरेजिस्टर_device(काष्ठा ib_device *device);
व्योम ib_unरेजिस्टर_driver(क्रमागत rdma_driver_id driver_id);
व्योम ib_unरेजिस्टर_device_and_put(काष्ठा ib_device *device);
व्योम ib_unरेजिस्टर_device_queued(काष्ठा ib_device *ib_dev);

पूर्णांक ib_रेजिस्टर_client   (काष्ठा ib_client *client);
व्योम ib_unरेजिस्टर_client(काष्ठा ib_client *client);

व्योम __rdma_block_iter_start(काष्ठा ib_block_iter *biter,
			     काष्ठा scatterlist *sglist,
			     अचिन्हित पूर्णांक nents,
			     अचिन्हित दीर्घ pgsz);
bool __rdma_block_iter_next(काष्ठा ib_block_iter *biter);

/**
 * rdma_block_iter_dma_address - get the aligned dma address of the current
 * block held by the block iterator.
 * @biter: block iterator holding the memory block
 */
अटल अंतरभूत dma_addr_t
rdma_block_iter_dma_address(काष्ठा ib_block_iter *biter)
अणु
	वापस biter->__dma_addr & ~(BIT_ULL(biter->__pg_bit) - 1);
पूर्ण

/**
 * rdma_क्रम_each_block - iterate over contiguous memory blocks of the sg list
 * @sglist: sglist to iterate over
 * @biter: block iterator holding the memory block
 * @nents: maximum number of sg entries to iterate over
 * @pgsz: best HW supported page size to use
 *
 * Callers may use rdma_block_iter_dma_address() to get each
 * blocks aligned DMA address.
 */
#घोषणा rdma_क्रम_each_block(sglist, biter, nents, pgsz)		\
	क्रम (__rdma_block_iter_start(biter, sglist, nents,	\
				     pgsz);			\
	     __rdma_block_iter_next(biter);)

/**
 * ib_get_client_data - Get IB client context
 * @device:Device to get context क्रम
 * @client:Client to get context क्रम
 *
 * ib_get_client_data() वापसs the client context data set with
 * ib_set_client_data(). This can only be called जबतक the client is
 * रेजिस्टरed to the device, once the ib_client हटाओ() callback वापसs this
 * cannot be called.
 */
अटल अंतरभूत व्योम *ib_get_client_data(काष्ठा ib_device *device,
				       काष्ठा ib_client *client)
अणु
	वापस xa_load(&device->client_data, client->client_id);
पूर्ण
व्योम  ib_set_client_data(काष्ठा ib_device *device, काष्ठा ib_client *client,
			 व्योम *data);
व्योम ib_set_device_ops(काष्ठा ib_device *device,
		       स्थिर काष्ठा ib_device_ops *ops);

पूर्णांक rdma_user_mmap_io(काष्ठा ib_ucontext *ucontext, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot,
		      काष्ठा rdma_user_mmap_entry *entry);
पूर्णांक rdma_user_mmap_entry_insert(काष्ठा ib_ucontext *ucontext,
				काष्ठा rdma_user_mmap_entry *entry,
				माप_प्रकार length);
पूर्णांक rdma_user_mmap_entry_insert_range(काष्ठा ib_ucontext *ucontext,
				      काष्ठा rdma_user_mmap_entry *entry,
				      माप_प्रकार length, u32 min_pgoff,
				      u32 max_pgoff);

काष्ठा rdma_user_mmap_entry *
rdma_user_mmap_entry_get_pgoff(काष्ठा ib_ucontext *ucontext,
			       अचिन्हित दीर्घ pgoff);
काष्ठा rdma_user_mmap_entry *
rdma_user_mmap_entry_get(काष्ठा ib_ucontext *ucontext,
			 काष्ठा vm_area_काष्ठा *vma);
व्योम rdma_user_mmap_entry_put(काष्ठा rdma_user_mmap_entry *entry);

व्योम rdma_user_mmap_entry_हटाओ(काष्ठा rdma_user_mmap_entry *entry);

अटल अंतरभूत पूर्णांक ib_copy_from_udata(व्योम *dest, काष्ठा ib_udata *udata, माप_प्रकार len)
अणु
	वापस copy_from_user(dest, udata->inbuf, len) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक ib_copy_to_udata(काष्ठा ib_udata *udata, व्योम *src, माप_प्रकार len)
अणु
	वापस copy_to_user(udata->outbuf, src, len) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत bool ib_is_buffer_cleared(स्थिर व्योम __user *p,
					माप_प्रकार len)
अणु
	bool ret;
	u8 *buf;

	अगर (len > अच_लघु_उच्च)
		वापस false;

	buf = memdup_user(p, len);
	अगर (IS_ERR(buf))
		वापस false;

	ret = !स_प्रथम_inv(buf, 0, len);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल अंतरभूत bool ib_is_udata_cleared(काष्ठा ib_udata *udata,
				       माप_प्रकार offset,
				       माप_प्रकार len)
अणु
	वापस ib_is_buffer_cleared(udata->inbuf + offset, len);
पूर्ण

/**
 * ib_modअगरy_qp_is_ok - Check that the supplied attribute mask
 * contains all required attributes and no attributes not allowed क्रम
 * the given QP state transition.
 * @cur_state: Current QP state
 * @next_state: Next QP state
 * @type: QP type
 * @mask: Mask of supplied QP attributes
 *
 * This function is a helper function that a low-level driver's
 * modअगरy_qp method can use to validate the consumer's input.  It
 * checks that cur_state and next_state are valid QP states, that a
 * transition from cur_state to next_state is allowed by the IB spec,
 * and that the attribute mask supplied is allowed क्रम the transition.
 */
bool ib_modअगरy_qp_is_ok(क्रमागत ib_qp_state cur_state, क्रमागत ib_qp_state next_state,
			क्रमागत ib_qp_type type, क्रमागत ib_qp_attr_mask mask);

व्योम ib_रेजिस्टर_event_handler(काष्ठा ib_event_handler *event_handler);
व्योम ib_unरेजिस्टर_event_handler(काष्ठा ib_event_handler *event_handler);
व्योम ib_dispatch_event(स्थिर काष्ठा ib_event *event);

पूर्णांक ib_query_port(काष्ठा ib_device *device,
		  u32 port_num, काष्ठा ib_port_attr *port_attr);

क्रमागत rdma_link_layer rdma_port_get_link_layer(काष्ठा ib_device *device,
					       u32 port_num);

/**
 * rdma_cap_ib_चयन - Check अगर the device is IB चयन
 * @device: Device to check
 *
 * Device driver is responsible क्रम setting is_चयन bit on
 * in ib_device काष्ठाure at init समय.
 *
 * Return: true अगर the device is IB चयन.
 */
अटल अंतरभूत bool rdma_cap_ib_चयन(स्थिर काष्ठा ib_device *device)
अणु
	वापस device->is_चयन;
पूर्ण

/**
 * rdma_start_port - Return the first valid port number क्रम the device
 * specअगरied
 *
 * @device: Device to be checked
 *
 * Return start port number
 */
अटल अंतरभूत u32 rdma_start_port(स्थिर काष्ठा ib_device *device)
अणु
	वापस rdma_cap_ib_चयन(device) ? 0 : 1;
पूर्ण

/**
 * rdma_क्रम_each_port - Iterate over all valid port numbers of the IB device
 * @device - The काष्ठा ib_device * to iterate over
 * @iter - The अचिन्हित पूर्णांक to store the port number
 */
#घोषणा rdma_क्रम_each_port(device, iter)                                       \
	क्रम (iter = rdma_start_port(device +				       \
				    BUILD_BUG_ON_ZERO(!__same_type(u32,	       \
								   iter)));    \
	     iter <= rdma_end_port(device); iter++)

/**
 * rdma_end_port - Return the last valid port number क्रम the device
 * specअगरied
 *
 * @device: Device to be checked
 *
 * Return last port number
 */
अटल अंतरभूत u32 rdma_end_port(स्थिर काष्ठा ib_device *device)
अणु
	वापस rdma_cap_ib_चयन(device) ? 0 : device->phys_port_cnt;
पूर्ण

अटल अंतरभूत पूर्णांक rdma_is_port_valid(स्थिर काष्ठा ib_device *device,
				     अचिन्हित पूर्णांक port)
अणु
	वापस (port >= rdma_start_port(device) &&
		port <= rdma_end_port(device));
पूर्ण

अटल अंतरभूत bool rdma_is_grh_required(स्थिर काष्ठा ib_device *device,
					u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_PORT_IB_GRH_REQUIRED;
पूर्ण

अटल अंतरभूत bool rdma_protocol_ib(स्थिर काष्ठा ib_device *device,
				    u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_PROT_IB;
पूर्ण

अटल अंतरभूत bool rdma_protocol_roce(स्थिर काष्ठा ib_device *device,
				      u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       (RDMA_CORE_CAP_PROT_ROCE | RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP);
पूर्ण

अटल अंतरभूत bool rdma_protocol_roce_udp_encap(स्थिर काष्ठा ib_device *device,
						u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP;
पूर्ण

अटल अंतरभूत bool rdma_protocol_roce_eth_encap(स्थिर काष्ठा ib_device *device,
						u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_PROT_ROCE;
पूर्ण

अटल अंतरभूत bool rdma_protocol_iwarp(स्थिर काष्ठा ib_device *device,
				       u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_PROT_IWARP;
पूर्ण

अटल अंतरभूत bool rdma_ib_or_roce(स्थिर काष्ठा ib_device *device,
				   u32 port_num)
अणु
	वापस rdma_protocol_ib(device, port_num) ||
		rdma_protocol_roce(device, port_num);
पूर्ण

अटल अंतरभूत bool rdma_protocol_raw_packet(स्थिर काष्ठा ib_device *device,
					    u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_PROT_RAW_PACKET;
पूर्ण

अटल अंतरभूत bool rdma_protocol_usnic(स्थिर काष्ठा ib_device *device,
				       u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_PROT_USNIC;
पूर्ण

/**
 * rdma_cap_ib_mad - Check अगर the port of a device supports Infiniband
 * Management Datagrams.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * Management Datagrams (MAD) are a required part of the InfiniBand
 * specअगरication and are supported on all InfiniBand devices.  A slightly
 * extended version are also supported on OPA पूर्णांकerfaces.
 *
 * Return: true अगर the port supports sending/receiving of MAD packets.
 */
अटल अंतरभूत bool rdma_cap_ib_mad(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_IB_MAD;
पूर्ण

/**
 * rdma_cap_opa_mad - Check अगर the port of device provides support क्रम OPA
 * Management Datagrams.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * Intel OmniPath devices extend and/or replace the InfiniBand Management
 * datagrams with their own versions.  These OPA MADs share many but not all of
 * the अक्षरacteristics of InfiniBand MADs.
 *
 * OPA MADs dअगरfer in the following ways:
 *
 *    1) MADs are variable size up to 2K
 *       IBTA defined MADs reमुख्य fixed at 256 bytes
 *    2) OPA SMPs must carry valid PKeys
 *    3) OPA SMP packets are a dअगरferent क्रमmat
 *
 * Return: true अगर the port supports OPA MAD packet क्रमmats.
 */
अटल अंतरभूत bool rdma_cap_opa_mad(काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
		RDMA_CORE_CAP_OPA_MAD;
पूर्ण

/**
 * rdma_cap_ib_smi - Check अगर the port of a device provides an Infiniband
 * Subnet Management Agent (SMA) on the Subnet Management Interface (SMI).
 * @device: Device to check
 * @port_num: Port number to check
 *
 * Each InfiniBand node is required to provide a Subnet Management Agent
 * that the subnet manager can access.  Prior to the fabric being fully
 * configured by the subnet manager, the SMA is accessed via a well known
 * पूर्णांकerface called the Subnet Management Interface (SMI).  This पूर्णांकerface
 * uses directed route packets to communicate with the SM to get around the
 * chicken and egg problem of the SM needing to know what's on the fabric
 * in order to configure the fabric, and needing to configure the fabric in
 * order to send packets to the devices on the fabric.  These directed
 * route packets करो not need the fabric fully configured in order to reach
 * their destination.  The SMI is the only method allowed to send
 * directed route packets on an InfiniBand fabric.
 *
 * Return: true अगर the port provides an SMI.
 */
अटल अंतरभूत bool rdma_cap_ib_smi(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_IB_SMI;
पूर्ण

/**
 * rdma_cap_ib_cm - Check अगर the port of device has the capability Infiniband
 * Communication Manager.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * The InfiniBand Communication Manager is one of many pre-defined General
 * Service Agents (GSA) that are accessed via the General Service
 * Interface (GSI).  It's role is to facilitate establishment of connections
 * between nodes as well as other management related tasks क्रम established
 * connections.
 *
 * Return: true अगर the port supports an IB CM (this करोes not guarantee that
 * a CM is actually running however).
 */
अटल अंतरभूत bool rdma_cap_ib_cm(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_IB_CM;
पूर्ण

/**
 * rdma_cap_iw_cm - Check अगर the port of device has the capability IWARP
 * Communication Manager.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * Similar to above, but specअगरic to iWARP connections which have a dअगरferent
 * managment protocol than InfiniBand.
 *
 * Return: true अगर the port supports an iWARP CM (this करोes not guarantee that
 * a CM is actually running however).
 */
अटल अंतरभूत bool rdma_cap_iw_cm(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_IW_CM;
पूर्ण

/**
 * rdma_cap_ib_sa - Check अगर the port of device has the capability Infiniband
 * Subnet Administration.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * An InfiniBand Subnet Administration (SA) service is a pre-defined General
 * Service Agent (GSA) provided by the Subnet Manager (SM).  On InfiniBand
 * fabrics, devices should resolve routes to other hosts by contacting the
 * SA to query the proper route.
 *
 * Return: true अगर the port should act as a client to the fabric Subnet
 * Administration पूर्णांकerface.  This करोes not imply that the SA service is
 * running locally.
 */
अटल अंतरभूत bool rdma_cap_ib_sa(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_IB_SA;
पूर्ण

/**
 * rdma_cap_ib_mcast - Check अगर the port of device has the capability Infiniband
 * Multicast.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * InfiniBand multicast registration is more complex than normal IPv4 or
 * IPv6 multicast registration.  Each Host Channel Adapter must रेजिस्टर
 * with the Subnet Manager when it wishes to join a multicast group.  It
 * should करो so only once regardless of how many queue pairs it subscribes
 * to this group.  And it should leave the group only after all queue pairs
 * attached to the group have been detached.
 *
 * Return: true अगर the port must undertake the additional adminstrative
 * overhead of रेजिस्टरing/unरेजिस्टरing with the SM and tracking of the
 * total number of queue pairs attached to the multicast group.
 */
अटल अंतरभूत bool rdma_cap_ib_mcast(स्थिर काष्ठा ib_device *device,
				     u32 port_num)
अणु
	वापस rdma_cap_ib_sa(device, port_num);
पूर्ण

/**
 * rdma_cap_af_ib - Check अगर the port of device has the capability
 * Native Infiniband Address.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * InfiniBand addressing uses a port's GUID + Subnet Prefix to make a शेष
 * GID.  RoCE uses a dअगरferent mechanism, but still generates a GID via
 * a prescribed mechanism and port specअगरic data.
 *
 * Return: true अगर the port uses a GID address to identअगरy devices on the
 * network.
 */
अटल अंतरभूत bool rdma_cap_af_ib(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_AF_IB;
पूर्ण

/**
 * rdma_cap_eth_ah - Check अगर the port of device has the capability
 * Ethernet Address Handle.
 * @device: Device to check
 * @port_num: Port number to check
 *
 * RoCE is InfiniBand over Ethernet, and it uses a well defined technique
 * to fabricate GIDs over Ethernet/IP specअगरic addresses native to the
 * port.  Normally, packet headers are generated by the sending host
 * adapter, but when sending connectionless datagrams, we must manually
 * inject the proper headers क्रम the fabric we are communicating over.
 *
 * Return: true अगर we are running as a RoCE port and must क्रमce the
 * addition of a Global Route Header built from our Ethernet Address
 * Handle पूर्णांकo our header list क्रम connectionless packets.
 */
अटल अंतरभूत bool rdma_cap_eth_ah(स्थिर काष्ठा ib_device *device, u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.core_cap_flags &
	       RDMA_CORE_CAP_ETH_AH;
पूर्ण

/**
 * rdma_cap_opa_ah - Check अगर the port of device supports
 * OPA Address handles
 * @device: Device to check
 * @port_num: Port number to check
 *
 * Return: true अगर we are running on an OPA device which supports
 * the extended OPA addressing.
 */
अटल अंतरभूत bool rdma_cap_opa_ah(काष्ठा ib_device *device, u32 port_num)
अणु
	वापस (device->port_data[port_num].immutable.core_cap_flags &
		RDMA_CORE_CAP_OPA_AH) == RDMA_CORE_CAP_OPA_AH;
पूर्ण

/**
 * rdma_max_mad_size - Return the max MAD size required by this RDMA Port.
 *
 * @device: Device
 * @port_num: Port number
 *
 * This MAD size includes the MAD headers and MAD payload.  No other headers
 * are included.
 *
 * Return the max MAD size required by the Port.  Will वापस 0 अगर the port
 * करोes not support MADs
 */
अटल अंतरभूत माप_प्रकार rdma_max_mad_size(स्थिर काष्ठा ib_device *device,
				       u32 port_num)
अणु
	वापस device->port_data[port_num].immutable.max_mad_size;
पूर्ण

/**
 * rdma_cap_roce_gid_table - Check अगर the port of device uses roce_gid_table
 * @device: Device to check
 * @port_num: Port number to check
 *
 * RoCE GID table mechanism manages the various GIDs क्रम a device.
 *
 * NOTE: अगर allocating the port's GID table has failed, this call will still
 * वापस true, but any RoCE GID table API will fail.
 *
 * Return: true अगर the port uses RoCE GID table mechanism in order to manage
 * its GIDs.
 */
अटल अंतरभूत bool rdma_cap_roce_gid_table(स्थिर काष्ठा ib_device *device,
					   u32 port_num)
अणु
	वापस rdma_protocol_roce(device, port_num) &&
		device->ops.add_gid && device->ops.del_gid;
पूर्ण

/*
 * Check अगर the device supports READ W/ INVALIDATE.
 */
अटल अंतरभूत bool rdma_cap_पढ़ो_inv(काष्ठा ib_device *dev, u32 port_num)
अणु
	/*
	 * iWarp drivers must support READ W/ INVALIDATE.  No other protocol
	 * has support क्रम it yet.
	 */
	वापस rdma_protocol_iwarp(dev, port_num);
पूर्ण

/**
 * rdma_core_cap_opa_port - Return whether the RDMA Port is OPA or not.
 * @device: Device
 * @port_num: 1 based Port number
 *
 * Return true अगर port is an Intel OPA port , false अगर not
 */
अटल अंतरभूत bool rdma_core_cap_opa_port(काष्ठा ib_device *device,
					  u32 port_num)
अणु
	वापस (device->port_data[port_num].immutable.core_cap_flags &
		RDMA_CORE_PORT_INTEL_OPA) == RDMA_CORE_PORT_INTEL_OPA;
पूर्ण

/**
 * rdma_mtu_क्रमागत_to_पूर्णांक - Return the mtu of the port as an पूर्णांकeger value.
 * @device: Device
 * @port_num: Port number
 * @mtu: क्रमागत value of MTU
 *
 * Return the MTU size supported by the port as an पूर्णांकeger value. Will वापस
 * -1 अगर क्रमागत value of mtu is not supported.
 */
अटल अंतरभूत पूर्णांक rdma_mtu_क्रमागत_to_पूर्णांक(काष्ठा ib_device *device, u32 port,
				       पूर्णांक mtu)
अणु
	अगर (rdma_core_cap_opa_port(device, port))
		वापस opa_mtu_क्रमागत_to_पूर्णांक((क्रमागत opa_mtu)mtu);
	अन्यथा
		वापस ib_mtu_क्रमागत_to_पूर्णांक((क्रमागत ib_mtu)mtu);
पूर्ण

/**
 * rdma_mtu_from_attr - Return the mtu of the port from the port attribute.
 * @device: Device
 * @port_num: Port number
 * @attr: port attribute
 *
 * Return the MTU size supported by the port as an पूर्णांकeger value.
 */
अटल अंतरभूत पूर्णांक rdma_mtu_from_attr(काष्ठा ib_device *device, u32 port,
				     काष्ठा ib_port_attr *attr)
अणु
	अगर (rdma_core_cap_opa_port(device, port))
		वापस attr->phys_mtu;
	अन्यथा
		वापस ib_mtu_क्रमागत_to_पूर्णांक(attr->max_mtu);
पूर्ण

पूर्णांक ib_set_vf_link_state(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			 पूर्णांक state);
पूर्णांक ib_get_vf_config(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
		     काष्ठा अगरla_vf_info *info);
पूर्णांक ib_get_vf_stats(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
		    काष्ठा अगरla_vf_stats *stats);
पूर्णांक ib_get_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
		    काष्ठा अगरla_vf_guid *node_guid,
		    काष्ठा अगरla_vf_guid *port_guid);
पूर्णांक ib_set_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port, u64 guid,
		   पूर्णांक type);

पूर्णांक ib_query_pkey(काष्ठा ib_device *device,
		  u32 port_num, u16 index, u16 *pkey);

पूर्णांक ib_modअगरy_device(काष्ठा ib_device *device,
		     पूर्णांक device_modअगरy_mask,
		     काष्ठा ib_device_modअगरy *device_modअगरy);

पूर्णांक ib_modअगरy_port(काष्ठा ib_device *device,
		   u32 port_num, पूर्णांक port_modअगरy_mask,
		   काष्ठा ib_port_modअगरy *port_modअगरy);

पूर्णांक ib_find_gid(काष्ठा ib_device *device, जोड़ ib_gid *gid,
		u32 *port_num, u16 *index);

पूर्णांक ib_find_pkey(काष्ठा ib_device *device,
		 u32 port_num, u16 pkey, u16 *index);

क्रमागत ib_pd_flags अणु
	/*
	 * Create a memory registration क्रम all memory in the प्रणाली and place
	 * the rkey क्रम it पूर्णांकo pd->unsafe_global_rkey.  This can be used by
	 * ULPs to aव्योम the overhead of dynamic MRs.
	 *
	 * This flag is generally considered unsafe and must only be used in
	 * extremly trusted environments.  Every use of it will log a warning
	 * in the kernel log.
	 */
	IB_PD_UNSAFE_GLOBAL_RKEY	= 0x01,
पूर्ण;

काष्ठा ib_pd *__ib_alloc_pd(काष्ठा ib_device *device, अचिन्हित पूर्णांक flags,
		स्थिर अक्षर *caller);

/**
 * ib_alloc_pd - Allocates an unused protection करोमुख्य.
 * @device: The device on which to allocate the protection करोमुख्य.
 * @flags: protection करोमुख्य flags
 *
 * A protection करोमुख्य object provides an association between QPs, shared
 * receive queues, address handles, memory regions, and memory winकरोws.
 *
 * Every PD has a local_dma_lkey which can be used as the lkey value क्रम local
 * memory operations.
 */
#घोषणा ib_alloc_pd(device, flags) \
	__ib_alloc_pd((device), (flags), KBUILD_MODNAME)

पूर्णांक ib_dealloc_pd_user(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);

/**
 * ib_dealloc_pd - Deallocate kernel PD
 * @pd: The protection करोमुख्य
 *
 * NOTE: क्रम user PD use ib_dealloc_pd_user with valid udata!
 */
अटल अंतरभूत व्योम ib_dealloc_pd(काष्ठा ib_pd *pd)
अणु
	पूर्णांक ret = ib_dealloc_pd_user(pd, शून्य);

	WARN_ONCE(ret, "Destroy of kernel PD shouldn't fail");
पूर्ण

क्रमागत rdma_create_ah_flags अणु
	/* In a sleepable context */
	RDMA_CREATE_AH_SLEEPABLE = BIT(0),
पूर्ण;

/**
 * rdma_create_ah - Creates an address handle क्रम the given address vector.
 * @pd: The protection करोमुख्य associated with the address handle.
 * @ah_attr: The attributes of the address vector.
 * @flags: Create address handle flags (see क्रमागत rdma_create_ah_flags).
 *
 * The address handle is used to reference a local or global destination
 * in all UD QP post sends.
 */
काष्ठा ib_ah *rdma_create_ah(काष्ठा ib_pd *pd, काष्ठा rdma_ah_attr *ah_attr,
			     u32 flags);

/**
 * rdma_create_user_ah - Creates an address handle क्रम the given address vector.
 * It resolves destination mac address क्रम ah attribute of RoCE type.
 * @pd: The protection करोमुख्य associated with the address handle.
 * @ah_attr: The attributes of the address vector.
 * @udata: poपूर्णांकer to user's input output buffer inक्रमmation need by
 *         provider driver.
 *
 * It वापसs 0 on success and वापसs appropriate error code on error.
 * The address handle is used to reference a local or global destination
 * in all UD QP post sends.
 */
काष्ठा ib_ah *rdma_create_user_ah(काष्ठा ib_pd *pd,
				  काष्ठा rdma_ah_attr *ah_attr,
				  काष्ठा ib_udata *udata);
/**
 * ib_get_gids_from_rdma_hdr - Get sgid and dgid from GRH or IPv4 header
 *   work completion.
 * @hdr: the L3 header to parse
 * @net_type: type of header to parse
 * @sgid: place to store source gid
 * @dgid: place to store destination gid
 */
पूर्णांक ib_get_gids_from_rdma_hdr(स्थिर जोड़ rdma_network_hdr *hdr,
			      क्रमागत rdma_network_type net_type,
			      जोड़ ib_gid *sgid, जोड़ ib_gid *dgid);

/**
 * ib_get_rdma_header_version - Get the header version
 * @hdr: the L3 header to parse
 */
पूर्णांक ib_get_rdma_header_version(स्थिर जोड़ rdma_network_hdr *hdr);

/**
 * ib_init_ah_attr_from_wc - Initializes address handle attributes from a
 *   work completion.
 * @device: Device on which the received message arrived.
 * @port_num: Port on which the received message arrived.
 * @wc: Work completion associated with the received message.
 * @grh: References the received global route header.  This parameter is
 *   ignored unless the work completion indicates that the GRH is valid.
 * @ah_attr: Returned attributes that can be used when creating an address
 *   handle क्रम replying to the message.
 * When ib_init_ah_attr_from_wc() वापसs success,
 * (a) क्रम IB link layer it optionally contains a reference to SGID attribute
 * when GRH is present क्रम IB link layer.
 * (b) क्रम RoCE link layer it contains a reference to SGID attribute.
 * User must invoke rdma_cleanup_ah_attr_gid_attr() to release reference to SGID
 * attributes which are initialized using ib_init_ah_attr_from_wc().
 *
 */
पूर्णांक ib_init_ah_attr_from_wc(काष्ठा ib_device *device, u32 port_num,
			    स्थिर काष्ठा ib_wc *wc, स्थिर काष्ठा ib_grh *grh,
			    काष्ठा rdma_ah_attr *ah_attr);

/**
 * ib_create_ah_from_wc - Creates an address handle associated with the
 *   sender of the specअगरied work completion.
 * @pd: The protection करोमुख्य associated with the address handle.
 * @wc: Work completion inक्रमmation associated with a received message.
 * @grh: References the received global route header.  This parameter is
 *   ignored unless the work completion indicates that the GRH is valid.
 * @port_num: The outbound port number to associate with the address.
 *
 * The address handle is used to reference a local or global destination
 * in all UD QP post sends.
 */
काष्ठा ib_ah *ib_create_ah_from_wc(काष्ठा ib_pd *pd, स्थिर काष्ठा ib_wc *wc,
				   स्थिर काष्ठा ib_grh *grh, u32 port_num);

/**
 * rdma_modअगरy_ah - Modअगरies the address vector associated with an address
 *   handle.
 * @ah: The address handle to modअगरy.
 * @ah_attr: The new address vector attributes to associate with the
 *   address handle.
 */
पूर्णांक rdma_modअगरy_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);

/**
 * rdma_query_ah - Queries the address vector associated with an address
 *   handle.
 * @ah: The address handle to query.
 * @ah_attr: The address vector attributes associated with the address
 *   handle.
 */
पूर्णांक rdma_query_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);

क्रमागत rdma_destroy_ah_flags अणु
	/* In a sleepable context */
	RDMA_DESTROY_AH_SLEEPABLE = BIT(0),
पूर्ण;

/**
 * rdma_destroy_ah_user - Destroys an address handle.
 * @ah: The address handle to destroy.
 * @flags: Destroy address handle flags (see क्रमागत rdma_destroy_ah_flags).
 * @udata: Valid user data or शून्य क्रम kernel objects
 */
पूर्णांक rdma_destroy_ah_user(काष्ठा ib_ah *ah, u32 flags, काष्ठा ib_udata *udata);

/**
 * rdma_destroy_ah - Destroys an kernel address handle.
 * @ah: The address handle to destroy.
 * @flags: Destroy address handle flags (see क्रमागत rdma_destroy_ah_flags).
 *
 * NOTE: क्रम user ah use rdma_destroy_ah_user with valid udata!
 */
अटल अंतरभूत व्योम rdma_destroy_ah(काष्ठा ib_ah *ah, u32 flags)
अणु
	पूर्णांक ret = rdma_destroy_ah_user(ah, flags, शून्य);

	WARN_ONCE(ret, "Destroy of kernel AH shouldn't fail");
पूर्ण

काष्ठा ib_srq *ib_create_srq_user(काष्ठा ib_pd *pd,
				  काष्ठा ib_srq_init_attr *srq_init_attr,
				  काष्ठा ib_usrq_object *uobject,
				  काष्ठा ib_udata *udata);
अटल अंतरभूत काष्ठा ib_srq *
ib_create_srq(काष्ठा ib_pd *pd, काष्ठा ib_srq_init_attr *srq_init_attr)
अणु
	अगर (!pd->device->ops.create_srq)
		वापस ERR_PTR(-EOPNOTSUPP);

	वापस ib_create_srq_user(pd, srq_init_attr, शून्य, शून्य);
पूर्ण

/**
 * ib_modअगरy_srq - Modअगरies the attributes क्रम the specअगरied SRQ.
 * @srq: The SRQ to modअगरy.
 * @srq_attr: On input, specअगरies the SRQ attributes to modअगरy.  On output,
 *   the current values of selected SRQ attributes are वापसed.
 * @srq_attr_mask: A bit-mask used to specअगरy which attributes of the SRQ
 *   are being modअगरied.
 *
 * The mask may contain IB_SRQ_MAX_WR to resize the SRQ and/or
 * IB_SRQ_LIMIT to set the SRQ's limit and request notअगरication when
 * the number of receives queued drops below the limit.
 */
पूर्णांक ib_modअगरy_srq(काष्ठा ib_srq *srq,
		  काष्ठा ib_srq_attr *srq_attr,
		  क्रमागत ib_srq_attr_mask srq_attr_mask);

/**
 * ib_query_srq - Returns the attribute list and current values क्रम the
 *   specअगरied SRQ.
 * @srq: The SRQ to query.
 * @srq_attr: The attributes of the specअगरied SRQ.
 */
पूर्णांक ib_query_srq(काष्ठा ib_srq *srq,
		 काष्ठा ib_srq_attr *srq_attr);

/**
 * ib_destroy_srq_user - Destroys the specअगरied SRQ.
 * @srq: The SRQ to destroy.
 * @udata: Valid user data or शून्य क्रम kernel objects
 */
पूर्णांक ib_destroy_srq_user(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata);

/**
 * ib_destroy_srq - Destroys the specअगरied kernel SRQ.
 * @srq: The SRQ to destroy.
 *
 * NOTE: क्रम user srq use ib_destroy_srq_user with valid udata!
 */
अटल अंतरभूत व्योम ib_destroy_srq(काष्ठा ib_srq *srq)
अणु
	पूर्णांक ret = ib_destroy_srq_user(srq, शून्य);

	WARN_ONCE(ret, "Destroy of kernel SRQ shouldn't fail");
पूर्ण

/**
 * ib_post_srq_recv - Posts a list of work requests to the specअगरied SRQ.
 * @srq: The SRQ to post the work request on.
 * @recv_wr: A list of work requests to post on the receive queue.
 * @bad_recv_wr: On an immediate failure, this parameter will reference
 *   the work request that failed to be posted on the QP.
 */
अटल अंतरभूत पूर्णांक ib_post_srq_recv(काष्ठा ib_srq *srq,
				   स्थिर काष्ठा ib_recv_wr *recv_wr,
				   स्थिर काष्ठा ib_recv_wr **bad_recv_wr)
अणु
	स्थिर काष्ठा ib_recv_wr *dummy;

	वापस srq->device->ops.post_srq_recv(srq, recv_wr,
					      bad_recv_wr ? : &dummy);
पूर्ण

काष्ठा ib_qp *ib_create_named_qp(काष्ठा ib_pd *pd,
				 काष्ठा ib_qp_init_attr *qp_init_attr,
				 स्थिर अक्षर *caller);
अटल अंतरभूत काष्ठा ib_qp *ib_create_qp(काष्ठा ib_pd *pd,
					 काष्ठा ib_qp_init_attr *init_attr)
अणु
	वापस ib_create_named_qp(pd, init_attr, KBUILD_MODNAME);
पूर्ण

/**
 * ib_modअगरy_qp_with_udata - Modअगरies the attributes क्रम the specअगरied QP.
 * @qp: The QP to modअगरy.
 * @attr: On input, specअगरies the QP attributes to modअगरy.  On output,
 *   the current values of selected QP attributes are वापसed.
 * @attr_mask: A bit-mask used to specअगरy which attributes of the QP
 *   are being modअगरied.
 * @udata: poपूर्णांकer to user's input output buffer inक्रमmation
 *   are being modअगरied.
 * It वापसs 0 on success and वापसs appropriate error code on error.
 */
पूर्णांक ib_modअगरy_qp_with_udata(काष्ठा ib_qp *qp,
			    काष्ठा ib_qp_attr *attr,
			    पूर्णांक attr_mask,
			    काष्ठा ib_udata *udata);

/**
 * ib_modअगरy_qp - Modअगरies the attributes क्रम the specअगरied QP and then
 *   transitions the QP to the given state.
 * @qp: The QP to modअगरy.
 * @qp_attr: On input, specअगरies the QP attributes to modअगरy.  On output,
 *   the current values of selected QP attributes are वापसed.
 * @qp_attr_mask: A bit-mask used to specअगरy which attributes of the QP
 *   are being modअगरied.
 */
पूर्णांक ib_modअगरy_qp(काष्ठा ib_qp *qp,
		 काष्ठा ib_qp_attr *qp_attr,
		 पूर्णांक qp_attr_mask);

/**
 * ib_query_qp - Returns the attribute list and current values क्रम the
 *   specअगरied QP.
 * @qp: The QP to query.
 * @qp_attr: The attributes of the specअगरied QP.
 * @qp_attr_mask: A bit-mask used to select specअगरic attributes to query.
 * @qp_init_attr: Additional attributes of the selected QP.
 *
 * The qp_attr_mask may be used to limit the query to gathering only the
 * selected attributes.
 */
पूर्णांक ib_query_qp(काष्ठा ib_qp *qp,
		काष्ठा ib_qp_attr *qp_attr,
		पूर्णांक qp_attr_mask,
		काष्ठा ib_qp_init_attr *qp_init_attr);

/**
 * ib_destroy_qp - Destroys the specअगरied QP.
 * @qp: The QP to destroy.
 * @udata: Valid udata or शून्य क्रम kernel objects
 */
पूर्णांक ib_destroy_qp_user(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);

/**
 * ib_destroy_qp - Destroys the specअगरied kernel QP.
 * @qp: The QP to destroy.
 *
 * NOTE: क्रम user qp use ib_destroy_qp_user with valid udata!
 */
अटल अंतरभूत पूर्णांक ib_destroy_qp(काष्ठा ib_qp *qp)
अणु
	वापस ib_destroy_qp_user(qp, शून्य);
पूर्ण

/**
 * ib_खोलो_qp - Obtain a reference to an existing sharable QP.
 * @xrcd - XRC करोमुख्य
 * @qp_खोलो_attr: Attributes identअगरying the QP to खोलो.
 *
 * Returns a reference to a sharable QP.
 */
काष्ठा ib_qp *ib_खोलो_qp(काष्ठा ib_xrcd *xrcd,
			 काष्ठा ib_qp_खोलो_attr *qp_खोलो_attr);

/**
 * ib_बंद_qp - Release an बाह्यal reference to a QP.
 * @qp: The QP handle to release
 *
 * The खोलोed QP handle is released by the caller.  The underlying
 * shared QP is not destroyed until all पूर्णांकernal references are released.
 */
पूर्णांक ib_बंद_qp(काष्ठा ib_qp *qp);

/**
 * ib_post_send - Posts a list of work requests to the send queue of
 *   the specअगरied QP.
 * @qp: The QP to post the work request on.
 * @send_wr: A list of work requests to post on the send queue.
 * @bad_send_wr: On an immediate failure, this parameter will reference
 *   the work request that failed to be posted on the QP.
 *
 * While IBA Vol. 1 section 11.4.1.1 specअगरies that अगर an immediate
 * error is वापसed, the QP state shall not be affected,
 * ib_post_send() will वापस an immediate error after queueing any
 * earlier work requests in the list.
 */
अटल अंतरभूत पूर्णांक ib_post_send(काष्ठा ib_qp *qp,
			       स्थिर काष्ठा ib_send_wr *send_wr,
			       स्थिर काष्ठा ib_send_wr **bad_send_wr)
अणु
	स्थिर काष्ठा ib_send_wr *dummy;

	वापस qp->device->ops.post_send(qp, send_wr, bad_send_wr ? : &dummy);
पूर्ण

/**
 * ib_post_recv - Posts a list of work requests to the receive queue of
 *   the specअगरied QP.
 * @qp: The QP to post the work request on.
 * @recv_wr: A list of work requests to post on the receive queue.
 * @bad_recv_wr: On an immediate failure, this parameter will reference
 *   the work request that failed to be posted on the QP.
 */
अटल अंतरभूत पूर्णांक ib_post_recv(काष्ठा ib_qp *qp,
			       स्थिर काष्ठा ib_recv_wr *recv_wr,
			       स्थिर काष्ठा ib_recv_wr **bad_recv_wr)
अणु
	स्थिर काष्ठा ib_recv_wr *dummy;

	वापस qp->device->ops.post_recv(qp, recv_wr, bad_recv_wr ? : &dummy);
पूर्ण

काष्ठा ib_cq *__ib_alloc_cq(काष्ठा ib_device *dev, व्योम *निजी, पूर्णांक nr_cqe,
			    पूर्णांक comp_vector, क्रमागत ib_poll_context poll_ctx,
			    स्थिर अक्षर *caller);
अटल अंतरभूत काष्ठा ib_cq *ib_alloc_cq(काष्ठा ib_device *dev, व्योम *निजी,
					पूर्णांक nr_cqe, पूर्णांक comp_vector,
					क्रमागत ib_poll_context poll_ctx)
अणु
	वापस __ib_alloc_cq(dev, निजी, nr_cqe, comp_vector, poll_ctx,
			     KBUILD_MODNAME);
पूर्ण

काष्ठा ib_cq *__ib_alloc_cq_any(काष्ठा ib_device *dev, व्योम *निजी,
				पूर्णांक nr_cqe, क्रमागत ib_poll_context poll_ctx,
				स्थिर अक्षर *caller);

/**
 * ib_alloc_cq_any: Allocate kernel CQ
 * @dev: The IB device
 * @निजी: Private data attached to the CQE
 * @nr_cqe: Number of CQEs in the CQ
 * @poll_ctx: Context used क्रम polling the CQ
 */
अटल अंतरभूत काष्ठा ib_cq *ib_alloc_cq_any(काष्ठा ib_device *dev,
					    व्योम *निजी, पूर्णांक nr_cqe,
					    क्रमागत ib_poll_context poll_ctx)
अणु
	वापस __ib_alloc_cq_any(dev, निजी, nr_cqe, poll_ctx,
				 KBUILD_MODNAME);
पूर्ण

व्योम ib_मुक्त_cq(काष्ठा ib_cq *cq);
पूर्णांक ib_process_cq_direct(काष्ठा ib_cq *cq, पूर्णांक budget);

/**
 * ib_create_cq - Creates a CQ on the specअगरied device.
 * @device: The device on which to create the CQ.
 * @comp_handler: A user-specअगरied callback that is invoked when a
 *   completion event occurs on the CQ.
 * @event_handler: A user-specअगरied callback that is invoked when an
 *   asynchronous event not associated with a completion occurs on the CQ.
 * @cq_context: Context associated with the CQ वापसed to the user via
 *   the associated completion and event handlers.
 * @cq_attr: The attributes the CQ should be created upon.
 *
 * Users can examine the cq काष्ठाure to determine the actual CQ size.
 */
काष्ठा ib_cq *__ib_create_cq(काष्ठा ib_device *device,
			     ib_comp_handler comp_handler,
			     व्योम (*event_handler)(काष्ठा ib_event *, व्योम *),
			     व्योम *cq_context,
			     स्थिर काष्ठा ib_cq_init_attr *cq_attr,
			     स्थिर अक्षर *caller);
#घोषणा ib_create_cq(device, cmp_hndlr, evt_hndlr, cq_ctxt, cq_attr) \
	__ib_create_cq((device), (cmp_hndlr), (evt_hndlr), (cq_ctxt), (cq_attr), KBUILD_MODNAME)

/**
 * ib_resize_cq - Modअगरies the capacity of the CQ.
 * @cq: The CQ to resize.
 * @cqe: The minimum size of the CQ.
 *
 * Users can examine the cq काष्ठाure to determine the actual CQ size.
 */
पूर्णांक ib_resize_cq(काष्ठा ib_cq *cq, पूर्णांक cqe);

/**
 * rdma_set_cq_moderation - Modअगरies moderation params of the CQ
 * @cq: The CQ to modअगरy.
 * @cq_count: number of CQEs that will trigger an event
 * @cq_period: max period of समय in usec beक्रमe triggering an event
 *
 */
पूर्णांक rdma_set_cq_moderation(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period);

/**
 * ib_destroy_cq_user - Destroys the specअगरied CQ.
 * @cq: The CQ to destroy.
 * @udata: Valid user data or शून्य क्रम kernel objects
 */
पूर्णांक ib_destroy_cq_user(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);

/**
 * ib_destroy_cq - Destroys the specअगरied kernel CQ.
 * @cq: The CQ to destroy.
 *
 * NOTE: क्रम user cq use ib_destroy_cq_user with valid udata!
 */
अटल अंतरभूत व्योम ib_destroy_cq(काष्ठा ib_cq *cq)
अणु
	पूर्णांक ret = ib_destroy_cq_user(cq, शून्य);

	WARN_ONCE(ret, "Destroy of kernel CQ shouldn't fail");
पूर्ण

/**
 * ib_poll_cq - poll a CQ क्रम completion(s)
 * @cq:the CQ being polled
 * @num_entries:maximum number of completions to वापस
 * @wc:array of at least @num_entries &काष्ठा ib_wc where completions
 *   will be वापसed
 *
 * Poll a CQ क्रम (possibly multiple) completions.  If the वापस value
 * is < 0, an error occurred.  If the वापस value is >= 0, it is the
 * number of completions वापसed.  If the वापस value is
 * non-negative and < num_entries, then the CQ was emptied.
 */
अटल अंतरभूत पूर्णांक ib_poll_cq(काष्ठा ib_cq *cq, पूर्णांक num_entries,
			     काष्ठा ib_wc *wc)
अणु
	वापस cq->device->ops.poll_cq(cq, num_entries, wc);
पूर्ण

/**
 * ib_req_notअगरy_cq - Request completion notअगरication on a CQ.
 * @cq: The CQ to generate an event क्रम.
 * @flags:
 *   Must contain exactly one of %IB_CQ_SOLICITED or %IB_CQ_NEXT_COMP
 *   to request an event on the next solicited event or next work
 *   completion at any type, respectively. %IB_CQ_REPORT_MISSED_EVENTS
 *   may also be |ed in to request a hपूर्णांक about missed events, as
 *   described below.
 *
 * Return Value:
 *    < 0 means an error occurred जबतक requesting notअगरication
 *   == 0 means notअगरication was requested successfully, and अगर
 *        IB_CQ_REPORT_MISSED_EVENTS was passed in, then no events
 *        were missed and it is safe to रुको क्रम another event.  In
 *        this हाल is it guaranteed that any work completions added
 *        to the CQ since the last CQ poll will trigger a completion
 *        notअगरication event.
 *    > 0 is only वापसed अगर IB_CQ_REPORT_MISSED_EVENTS was passed
 *        in.  It means that the consumer must poll the CQ again to
 *        make sure it is empty to aव्योम missing an event because of a
 *        race between requesting notअगरication and an entry being
 *        added to the CQ.  This वापस value means it is possible
 *        (but not guaranteed) that a work completion has been added
 *        to the CQ since the last poll without triggering a
 *        completion notअगरication event.
 */
अटल अंतरभूत पूर्णांक ib_req_notअगरy_cq(काष्ठा ib_cq *cq,
				   क्रमागत ib_cq_notअगरy_flags flags)
अणु
	वापस cq->device->ops.req_notअगरy_cq(cq, flags);
पूर्ण

काष्ठा ib_cq *ib_cq_pool_get(काष्ठा ib_device *dev, अचिन्हित पूर्णांक nr_cqe,
			     पूर्णांक comp_vector_hपूर्णांक,
			     क्रमागत ib_poll_context poll_ctx);

व्योम ib_cq_pool_put(काष्ठा ib_cq *cq, अचिन्हित पूर्णांक nr_cqe);

/*
 * Drivers that करोn't need a DMA mapping at the RDMA layer, set dma_device to
 * शून्य. This causes the ib_dma* helpers to just stash the kernel भव
 * address पूर्णांकo the dma address.
 */
अटल अंतरभूत bool ib_uses_virt_dma(काष्ठा ib_device *dev)
अणु
	वापस IS_ENABLED(CONFIG_INFINIBAND_VIRT_DMA) && !dev->dma_device;
पूर्ण

/**
 * ib_dma_mapping_error - check a DMA addr क्रम error
 * @dev: The device क्रम which the dma_addr was created
 * @dma_addr: The DMA address to check
 */
अटल अंतरभूत पूर्णांक ib_dma_mapping_error(काष्ठा ib_device *dev, u64 dma_addr)
अणु
	अगर (ib_uses_virt_dma(dev))
		वापस 0;
	वापस dma_mapping_error(dev->dma_device, dma_addr);
पूर्ण

/**
 * ib_dma_map_single - Map a kernel भव address to DMA address
 * @dev: The device क्रम which the dma_addr is to be created
 * @cpu_addr: The kernel भव address
 * @size: The size of the region in bytes
 * @direction: The direction of the DMA
 */
अटल अंतरभूत u64 ib_dma_map_single(काष्ठा ib_device *dev,
				    व्योम *cpu_addr, माप_प्रकार size,
				    क्रमागत dma_data_direction direction)
अणु
	अगर (ib_uses_virt_dma(dev))
		वापस (uपूर्णांकptr_t)cpu_addr;
	वापस dma_map_single(dev->dma_device, cpu_addr, size, direction);
पूर्ण

/**
 * ib_dma_unmap_single - Destroy a mapping created by ib_dma_map_single()
 * @dev: The device क्रम which the DMA address was created
 * @addr: The DMA address
 * @size: The size of the region in bytes
 * @direction: The direction of the DMA
 */
अटल अंतरभूत व्योम ib_dma_unmap_single(काष्ठा ib_device *dev,
				       u64 addr, माप_प्रकार size,
				       क्रमागत dma_data_direction direction)
अणु
	अगर (!ib_uses_virt_dma(dev))
		dma_unmap_single(dev->dma_device, addr, size, direction);
पूर्ण

/**
 * ib_dma_map_page - Map a physical page to DMA address
 * @dev: The device क्रम which the dma_addr is to be created
 * @page: The page to be mapped
 * @offset: The offset within the page
 * @size: The size of the region in bytes
 * @direction: The direction of the DMA
 */
अटल अंतरभूत u64 ib_dma_map_page(काष्ठा ib_device *dev,
				  काष्ठा page *page,
				  अचिन्हित दीर्घ offset,
				  माप_प्रकार size,
					 क्रमागत dma_data_direction direction)
अणु
	अगर (ib_uses_virt_dma(dev))
		वापस (uपूर्णांकptr_t)(page_address(page) + offset);
	वापस dma_map_page(dev->dma_device, page, offset, size, direction);
पूर्ण

/**
 * ib_dma_unmap_page - Destroy a mapping created by ib_dma_map_page()
 * @dev: The device क्रम which the DMA address was created
 * @addr: The DMA address
 * @size: The size of the region in bytes
 * @direction: The direction of the DMA
 */
अटल अंतरभूत व्योम ib_dma_unmap_page(काष्ठा ib_device *dev,
				     u64 addr, माप_प्रकार size,
				     क्रमागत dma_data_direction direction)
अणु
	अगर (!ib_uses_virt_dma(dev))
		dma_unmap_page(dev->dma_device, addr, size, direction);
पूर्ण

पूर्णांक ib_dma_virt_map_sg(काष्ठा ib_device *dev, काष्ठा scatterlist *sg, पूर्णांक nents);
अटल अंतरभूत पूर्णांक ib_dma_map_sg_attrs(काष्ठा ib_device *dev,
				      काष्ठा scatterlist *sg, पूर्णांक nents,
				      क्रमागत dma_data_direction direction,
				      अचिन्हित दीर्घ dma_attrs)
अणु
	अगर (ib_uses_virt_dma(dev))
		वापस ib_dma_virt_map_sg(dev, sg, nents);
	वापस dma_map_sg_attrs(dev->dma_device, sg, nents, direction,
				dma_attrs);
पूर्ण

अटल अंतरभूत व्योम ib_dma_unmap_sg_attrs(काष्ठा ib_device *dev,
					 काष्ठा scatterlist *sg, पूर्णांक nents,
					 क्रमागत dma_data_direction direction,
					 अचिन्हित दीर्घ dma_attrs)
अणु
	अगर (!ib_uses_virt_dma(dev))
		dma_unmap_sg_attrs(dev->dma_device, sg, nents, direction,
				   dma_attrs);
पूर्ण

/**
 * ib_dma_map_sg - Map a scatter/gather list to DMA addresses
 * @dev: The device क्रम which the DMA addresses are to be created
 * @sg: The array of scatter/gather entries
 * @nents: The number of scatter/gather entries
 * @direction: The direction of the DMA
 */
अटल अंतरभूत पूर्णांक ib_dma_map_sg(काष्ठा ib_device *dev,
				काष्ठा scatterlist *sg, पूर्णांक nents,
				क्रमागत dma_data_direction direction)
अणु
	वापस ib_dma_map_sg_attrs(dev, sg, nents, direction, 0);
पूर्ण

/**
 * ib_dma_unmap_sg - Unmap a scatter/gather list of DMA addresses
 * @dev: The device क्रम which the DMA addresses were created
 * @sg: The array of scatter/gather entries
 * @nents: The number of scatter/gather entries
 * @direction: The direction of the DMA
 */
अटल अंतरभूत व्योम ib_dma_unmap_sg(काष्ठा ib_device *dev,
				   काष्ठा scatterlist *sg, पूर्णांक nents,
				   क्रमागत dma_data_direction direction)
अणु
	ib_dma_unmap_sg_attrs(dev, sg, nents, direction, 0);
पूर्ण

/**
 * ib_dma_max_seg_size - Return the size limit of a single DMA transfer
 * @dev: The device to query
 *
 * The वापसed value represents a size in bytes.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ib_dma_max_seg_size(काष्ठा ib_device *dev)
अणु
	अगर (ib_uses_virt_dma(dev))
		वापस अच_पूर्णांक_उच्च;
	वापस dma_get_max_seg_size(dev->dma_device);
पूर्ण

/**
 * ib_dma_sync_single_क्रम_cpu - Prepare DMA region to be accessed by CPU
 * @dev: The device क्रम which the DMA address was created
 * @addr: The DMA address
 * @size: The size of the region in bytes
 * @dir: The direction of the DMA
 */
अटल अंतरभूत व्योम ib_dma_sync_single_क्रम_cpu(काष्ठा ib_device *dev,
					      u64 addr,
					      माप_प्रकार size,
					      क्रमागत dma_data_direction dir)
अणु
	अगर (!ib_uses_virt_dma(dev))
		dma_sync_single_क्रम_cpu(dev->dma_device, addr, size, dir);
पूर्ण

/**
 * ib_dma_sync_single_क्रम_device - Prepare DMA region to be accessed by device
 * @dev: The device क्रम which the DMA address was created
 * @addr: The DMA address
 * @size: The size of the region in bytes
 * @dir: The direction of the DMA
 */
अटल अंतरभूत व्योम ib_dma_sync_single_क्रम_device(काष्ठा ib_device *dev,
						 u64 addr,
						 माप_प्रकार size,
						 क्रमागत dma_data_direction dir)
अणु
	अगर (!ib_uses_virt_dma(dev))
		dma_sync_single_क्रम_device(dev->dma_device, addr, size, dir);
पूर्ण

/* ib_reg_user_mr - रेजिस्टर a memory region क्रम भव addresses from kernel
 * space. This function should be called when 'current' is the owning MM.
 */
काष्ठा ib_mr *ib_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
			     u64 virt_addr, पूर्णांक mr_access_flags);

/* ib_advise_mr -  give an advice about an address range in a memory region */
पूर्णांक ib_advise_mr(काष्ठा ib_pd *pd, क्रमागत ib_uverbs_advise_mr_advice advice,
		 u32 flags, काष्ठा ib_sge *sg_list, u32 num_sge);
/**
 * ib_dereg_mr_user - Deरेजिस्टरs a memory region and हटाओs it from the
 *   HCA translation table.
 * @mr: The memory region to deरेजिस्टर.
 * @udata: Valid user data or शून्य क्रम kernel object
 *
 * This function can fail, अगर the memory region has memory winकरोws bound to it.
 */
पूर्णांक ib_dereg_mr_user(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata);

/**
 * ib_dereg_mr - Deरेजिस्टरs a kernel memory region and हटाओs it from the
 *   HCA translation table.
 * @mr: The memory region to deरेजिस्टर.
 *
 * This function can fail, अगर the memory region has memory winकरोws bound to it.
 *
 * NOTE: क्रम user mr use ib_dereg_mr_user with valid udata!
 */
अटल अंतरभूत पूर्णांक ib_dereg_mr(काष्ठा ib_mr *mr)
अणु
	वापस ib_dereg_mr_user(mr, शून्य);
पूर्ण

काष्ठा ib_mr *ib_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			  u32 max_num_sg);

काष्ठा ib_mr *ib_alloc_mr_पूर्णांकegrity(काष्ठा ib_pd *pd,
				    u32 max_num_data_sg,
				    u32 max_num_meta_sg);

/**
 * ib_update_fast_reg_key - updates the key portion of the fast_reg MR
 *   R_Key and L_Key.
 * @mr - काष्ठा ib_mr poपूर्णांकer to be updated.
 * @newkey - new key to be used.
 */
अटल अंतरभूत व्योम ib_update_fast_reg_key(काष्ठा ib_mr *mr, u8 newkey)
अणु
	mr->lkey = (mr->lkey & 0xffffff00) | newkey;
	mr->rkey = (mr->rkey & 0xffffff00) | newkey;
पूर्ण

/**
 * ib_inc_rkey - increments the key portion of the given rkey. Can be used
 * क्रम calculating a new rkey क्रम type 2 memory winकरोws.
 * @rkey - the rkey to increment.
 */
अटल अंतरभूत u32 ib_inc_rkey(u32 rkey)
अणु
	स्थिर u32 mask = 0x000000ff;
	वापस ((rkey + 1) & mask) | (rkey & ~mask);
पूर्ण

/**
 * ib_attach_mcast - Attaches the specअगरied QP to a multicast group.
 * @qp: QP to attach to the multicast group.  The QP must be type
 *   IB_QPT_UD.
 * @gid: Multicast group GID.
 * @lid: Multicast group LID in host byte order.
 *
 * In order to send and receive multicast packets, subnet
 * administration must have created the multicast group and configured
 * the fabric appropriately.  The port associated with the specअगरied
 * QP must also be a member of the multicast group.
 */
पूर्णांक ib_attach_mcast(काष्ठा ib_qp *qp, जोड़ ib_gid *gid, u16 lid);

/**
 * ib_detach_mcast - Detaches the specअगरied QP from a multicast group.
 * @qp: QP to detach from the multicast group.
 * @gid: Multicast group GID.
 * @lid: Multicast group LID in host byte order.
 */
पूर्णांक ib_detach_mcast(काष्ठा ib_qp *qp, जोड़ ib_gid *gid, u16 lid);

काष्ठा ib_xrcd *ib_alloc_xrcd_user(काष्ठा ib_device *device,
				   काष्ठा inode *inode, काष्ठा ib_udata *udata);
पूर्णांक ib_dealloc_xrcd_user(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata);

अटल अंतरभूत पूर्णांक ib_check_mr_access(काष्ठा ib_device *ib_dev,
				     अचिन्हित पूर्णांक flags)
अणु
	/*
	 * Local ग_लिखो permission is required अगर remote ग_लिखो or
	 * remote atomic permission is also requested.
	 */
	अगर (flags & (IB_ACCESS_REMOTE_ATOMIC | IB_ACCESS_REMOTE_WRITE) &&
	    !(flags & IB_ACCESS_LOCAL_WRITE))
		वापस -EINVAL;

	अगर (flags & ~IB_ACCESS_SUPPORTED)
		वापस -EINVAL;

	अगर (flags & IB_ACCESS_ON_DEMAND &&
	    !(ib_dev->attrs.device_cap_flags & IB_DEVICE_ON_DEMAND_PAGING))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत bool ib_access_writable(पूर्णांक access_flags)
अणु
	/*
	 * We have writable memory backing the MR अगर any of the following
	 * access flags are set.  "Local write" and "remote write" obviously
	 * require ग_लिखो access.  "Remote atomic" can करो things like fetch and
	 * add, which will modअगरy memory, and "MW bind" can change permissions
	 * by binding a winकरोw.
	 */
	वापस access_flags &
		(IB_ACCESS_LOCAL_WRITE   | IB_ACCESS_REMOTE_WRITE |
		 IB_ACCESS_REMOTE_ATOMIC | IB_ACCESS_MW_BIND);
पूर्ण

/**
 * ib_check_mr_status: lightweight check of MR status.
 *     This routine may provide status checks on a selected
 *     ib_mr. first use is क्रम signature status check.
 *
 * @mr: A memory region.
 * @check_mask: Biपंचांगask of which checks to perक्रमm from
 *     ib_mr_status_check क्रमागतeration.
 * @mr_status: The container of relevant status checks.
 *     failed checks will be indicated in the status biपंचांगask
 *     and the relevant info shall be in the error item.
 */
पूर्णांक ib_check_mr_status(काष्ठा ib_mr *mr, u32 check_mask,
		       काष्ठा ib_mr_status *mr_status);

/**
 * ib_device_try_get: Hold a registration lock
 * device: The device to lock
 *
 * A device under an active registration lock cannot become unरेजिस्टरed. It
 * is only possible to obtain a registration lock on a device that is fully
 * रेजिस्टरed, otherwise this function वापसs false.
 *
 * The registration lock is only necessary क्रम actions which require the
 * device to still be रेजिस्टरed. Uses that only require the device poपूर्णांकer to
 * be valid should use get_device(&ibdev->dev) to hold the memory.
 *
 */
अटल अंतरभूत bool ib_device_try_get(काष्ठा ib_device *dev)
अणु
	वापस refcount_inc_not_zero(&dev->refcount);
पूर्ण

व्योम ib_device_put(काष्ठा ib_device *device);
काष्ठा ib_device *ib_device_get_by_netdev(काष्ठा net_device *ndev,
					  क्रमागत rdma_driver_id driver_id);
काष्ठा ib_device *ib_device_get_by_name(स्थिर अक्षर *name,
					क्रमागत rdma_driver_id driver_id);
काष्ठा net_device *ib_get_net_dev_by_params(काष्ठा ib_device *dev, u32 port,
					    u16 pkey, स्थिर जोड़ ib_gid *gid,
					    स्थिर काष्ठा sockaddr *addr);
पूर्णांक ib_device_set_netdev(काष्ठा ib_device *ib_dev, काष्ठा net_device *ndev,
			 अचिन्हित पूर्णांक port);
काष्ठा net_device *ib_device_netdev(काष्ठा ib_device *dev, u32 port);

काष्ठा ib_wq *ib_create_wq(काष्ठा ib_pd *pd,
			   काष्ठा ib_wq_init_attr *init_attr);
पूर्णांक ib_destroy_wq_user(काष्ठा ib_wq *wq, काष्ठा ib_udata *udata);
पूर्णांक ib_modअगरy_wq(काष्ठा ib_wq *wq, काष्ठा ib_wq_attr *attr,
		 u32 wq_attr_mask);

पूर्णांक ib_map_mr_sg(काष्ठा ib_mr *mr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		 अचिन्हित पूर्णांक *sg_offset, अचिन्हित पूर्णांक page_size);
पूर्णांक ib_map_mr_sg_pi(काष्ठा ib_mr *mr, काष्ठा scatterlist *data_sg,
		    पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
		    काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
		    अचिन्हित पूर्णांक *meta_sg_offset, अचिन्हित पूर्णांक page_size);

अटल अंतरभूत पूर्णांक
ib_map_mr_sg_zbva(काष्ठा ib_mr *mr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		  अचिन्हित पूर्णांक *sg_offset, अचिन्हित पूर्णांक page_size)
अणु
	पूर्णांक n;

	n = ib_map_mr_sg(mr, sg, sg_nents, sg_offset, page_size);
	mr->iova = 0;

	वापस n;
पूर्ण

पूर्णांक ib_sg_to_pages(काष्ठा ib_mr *mr, काष्ठा scatterlist *sgl, पूर्णांक sg_nents,
		अचिन्हित पूर्णांक *sg_offset, पूर्णांक (*set_page)(काष्ठा ib_mr *, u64));

व्योम ib_drain_rq(काष्ठा ib_qp *qp);
व्योम ib_drain_sq(काष्ठा ib_qp *qp);
व्योम ib_drain_qp(काष्ठा ib_qp *qp);

पूर्णांक ib_get_eth_speed(काष्ठा ib_device *dev, u32 port_num, u16 *speed,
		     u8 *width);

अटल अंतरभूत u8 *rdma_ah_retrieve_dmac(काष्ठा rdma_ah_attr *attr)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_ROCE)
		वापस attr->roce.dmac;
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_dlid(काष्ठा rdma_ah_attr *attr, u32 dlid)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_IB)
		attr->ib.dlid = (u16)dlid;
	अन्यथा अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA)
		attr->opa.dlid = dlid;
पूर्ण

अटल अंतरभूत u32 rdma_ah_get_dlid(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_IB)
		वापस attr->ib.dlid;
	अन्यथा अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA)
		वापस attr->opa.dlid;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_sl(काष्ठा rdma_ah_attr *attr, u8 sl)
अणु
	attr->sl = sl;
पूर्ण

अटल अंतरभूत u8 rdma_ah_get_sl(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	वापस attr->sl;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_path_bits(काष्ठा rdma_ah_attr *attr,
					 u8 src_path_bits)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_IB)
		attr->ib.src_path_bits = src_path_bits;
	अन्यथा अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA)
		attr->opa.src_path_bits = src_path_bits;
पूर्ण

अटल अंतरभूत u8 rdma_ah_get_path_bits(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_IB)
		वापस attr->ib.src_path_bits;
	अन्यथा अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA)
		वापस attr->opa.src_path_bits;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_make_grd(काष्ठा rdma_ah_attr *attr,
					bool make_grd)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA)
		attr->opa.make_grd = make_grd;
पूर्ण

अटल अंतरभूत bool rdma_ah_get_make_grd(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA)
		वापस attr->opa.make_grd;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_port_num(काष्ठा rdma_ah_attr *attr, u32 port_num)
अणु
	attr->port_num = port_num;
पूर्ण

अटल अंतरभूत u32 rdma_ah_get_port_num(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	वापस attr->port_num;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_अटल_rate(काष्ठा rdma_ah_attr *attr,
					   u8 अटल_rate)
अणु
	attr->अटल_rate = अटल_rate;
पूर्ण

अटल अंतरभूत u8 rdma_ah_get_अटल_rate(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	वापस attr->अटल_rate;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_ah_flags(काष्ठा rdma_ah_attr *attr,
					क्रमागत ib_ah_flags flag)
अणु
	attr->ah_flags = flag;
पूर्ण

अटल अंतरभूत क्रमागत ib_ah_flags
		rdma_ah_get_ah_flags(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	वापस attr->ah_flags;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ib_global_route
		*rdma_ah_पढ़ो_grh(स्थिर काष्ठा rdma_ah_attr *attr)
अणु
	वापस &attr->grh;
पूर्ण

/*To retrieve and modअगरy the grh */
अटल अंतरभूत काष्ठा ib_global_route
		*rdma_ah_retrieve_grh(काष्ठा rdma_ah_attr *attr)
अणु
	वापस &attr->grh;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_dgid_raw(काष्ठा rdma_ah_attr *attr, व्योम *dgid)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(attr);

	स_नकल(grh->dgid.raw, dgid, माप(grh->dgid));
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_subnet_prefix(काष्ठा rdma_ah_attr *attr,
					     __be64 prefix)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(attr);

	grh->dgid.global.subnet_prefix = prefix;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_पूर्णांकerface_id(काष्ठा rdma_ah_attr *attr,
					    __be64 अगर_id)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(attr);

	grh->dgid.global.पूर्णांकerface_id = अगर_id;
पूर्ण

अटल अंतरभूत व्योम rdma_ah_set_grh(काष्ठा rdma_ah_attr *attr,
				   जोड़ ib_gid *dgid, u32 flow_label,
				   u8 sgid_index, u8 hop_limit,
				   u8 traffic_class)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(attr);

	attr->ah_flags = IB_AH_GRH;
	अगर (dgid)
		grh->dgid = *dgid;
	grh->flow_label = flow_label;
	grh->sgid_index = sgid_index;
	grh->hop_limit = hop_limit;
	grh->traffic_class = traffic_class;
	grh->sgid_attr = शून्य;
पूर्ण

व्योम rdma_destroy_ah_attr(काष्ठा rdma_ah_attr *ah_attr);
व्योम rdma_move_grh_sgid_attr(काष्ठा rdma_ah_attr *attr, जोड़ ib_gid *dgid,
			     u32 flow_label, u8 hop_limit, u8 traffic_class,
			     स्थिर काष्ठा ib_gid_attr *sgid_attr);
व्योम rdma_copy_ah_attr(काष्ठा rdma_ah_attr *dest,
		       स्थिर काष्ठा rdma_ah_attr *src);
व्योम rdma_replace_ah_attr(काष्ठा rdma_ah_attr *old,
			  स्थिर काष्ठा rdma_ah_attr *new);
व्योम rdma_move_ah_attr(काष्ठा rdma_ah_attr *dest, काष्ठा rdma_ah_attr *src);

/**
 * rdma_ah_find_type - Return address handle type.
 *
 * @dev: Device to be checked
 * @port_num: Port number
 */
अटल अंतरभूत क्रमागत rdma_ah_attr_type rdma_ah_find_type(काष्ठा ib_device *dev,
						       u32 port_num)
अणु
	अगर (rdma_protocol_roce(dev, port_num))
		वापस RDMA_AH_ATTR_TYPE_ROCE;
	अगर (rdma_protocol_ib(dev, port_num)) अणु
		अगर (rdma_cap_opa_ah(dev, port_num))
			वापस RDMA_AH_ATTR_TYPE_OPA;
		वापस RDMA_AH_ATTR_TYPE_IB;
	पूर्ण

	वापस RDMA_AH_ATTR_TYPE_UNDEFINED;
पूर्ण

/**
 * ib_lid_cpu16 - Return lid in 16bit CPU encoding.
 *     In the current implementation the only way to get
 *     get the 32bit lid is from other sources क्रम OPA.
 *     For IB, lids will always be 16bits so cast the
 *     value accordingly.
 *
 * @lid: A 32bit LID
 */
अटल अंतरभूत u16 ib_lid_cpu16(u32 lid)
अणु
	WARN_ON_ONCE(lid & 0xFFFF0000);
	वापस (u16)lid;
पूर्ण

/**
 * ib_lid_be16 - Return lid in 16bit BE encoding.
 *
 * @lid: A 32bit LID
 */
अटल अंतरभूत __be16 ib_lid_be16(u32 lid)
अणु
	WARN_ON_ONCE(lid & 0xFFFF0000);
	वापस cpu_to_be16((u16)lid);
पूर्ण

/**
 * ib_get_vector_affinity - Get the affinity mappings of a given completion
 *   vector
 * @device:         the rdma device
 * @comp_vector:    index of completion vector
 *
 * Returns शून्य on failure, otherwise a corresponding cpu map of the
 * completion vector (वापसs all-cpus map अगर the device driver करोesn't
 * implement get_vector_affinity).
 */
अटल अंतरभूत स्थिर काष्ठा cpumask *
ib_get_vector_affinity(काष्ठा ib_device *device, पूर्णांक comp_vector)
अणु
	अगर (comp_vector < 0 || comp_vector >= device->num_comp_vectors ||
	    !device->ops.get_vector_affinity)
		वापस शून्य;

	वापस device->ops.get_vector_affinity(device, comp_vector);

पूर्ण

/**
 * rdma_roce_rescan_device - Rescan all of the network devices in the प्रणाली
 * and add their gids, as needed, to the relevant RoCE devices.
 *
 * @device:         the rdma device
 */
व्योम rdma_roce_rescan_device(काष्ठा ib_device *ibdev);

काष्ठा ib_ucontext *ib_uverbs_get_ucontext_file(काष्ठा ib_uverbs_file *ufile);

पूर्णांक uverbs_destroy_def_handler(काष्ठा uverbs_attr_bundle *attrs);

काष्ठा net_device *rdma_alloc_netdev(काष्ठा ib_device *device, u32 port_num,
				     क्रमागत rdma_netdev_t type, स्थिर अक्षर *name,
				     अचिन्हित अक्षर name_assign_type,
				     व्योम (*setup)(काष्ठा net_device *));

पूर्णांक rdma_init_netdev(काष्ठा ib_device *device, u32 port_num,
		     क्रमागत rdma_netdev_t type, स्थिर अक्षर *name,
		     अचिन्हित अक्षर name_assign_type,
		     व्योम (*setup)(काष्ठा net_device *),
		     काष्ठा net_device *netdev);

/**
 * rdma_set_device_sysfs_group - Set device attributes group to have
 *				 driver specअगरic sysfs entries at
 *				 क्रम infiniband class.
 *
 * @device:	device poपूर्णांकer क्रम which attributes to be created
 * @group:	Poपूर्णांकer to group which should be added when device
 *		is रेजिस्टरed with sysfs.
 * rdma_set_device_sysfs_group() allows existing drivers to expose one
 * group per device to have sysfs attributes.
 *
 * NOTE: New drivers should not make use of this API; instead new device
 * parameter should be exposed via netlink command. This API and mechanism
 * exist only क्रम existing drivers.
 */
अटल अंतरभूत व्योम
rdma_set_device_sysfs_group(काष्ठा ib_device *dev,
			    स्थिर काष्ठा attribute_group *group)
अणु
	dev->groups[1] = group;
पूर्ण

/**
 * rdma_device_to_ibdev - Get ib_device poपूर्णांकer from device poपूर्णांकer
 *
 * @device:	device poपूर्णांकer क्रम which ib_device poपूर्णांकer to retrieve
 *
 * rdma_device_to_ibdev() retrieves ib_device poपूर्णांकer from device.
 *
 */
अटल अंतरभूत काष्ठा ib_device *rdma_device_to_ibdev(काष्ठा device *device)
अणु
	काष्ठा ib_core_device *coredev =
		container_of(device, काष्ठा ib_core_device, dev);

	वापस coredev->owner;
पूर्ण

/**
 * ibdev_to_node - वापस the NUMA node क्रम a given ib_device
 * @dev:	device to get the NUMA node क्रम.
 */
अटल अंतरभूत पूर्णांक ibdev_to_node(काष्ठा ib_device *ibdev)
अणु
	काष्ठा device *parent = ibdev->dev.parent;

	अगर (!parent)
		वापस NUMA_NO_NODE;
	वापस dev_to_node(parent);
पूर्ण

/**
 * rdma_device_to_drv_device - Helper macro to reach back to driver's
 *			       ib_device holder काष्ठाure from device poपूर्णांकer.
 *
 * NOTE: New drivers should not make use of this API; This API is only क्रम
 * existing drivers who have exposed sysfs entries using
 * rdma_set_device_sysfs_group().
 */
#घोषणा rdma_device_to_drv_device(dev, drv_dev_काष्ठा, ibdev_member)           \
	container_of(rdma_device_to_ibdev(dev), drv_dev_काष्ठा, ibdev_member)

bool rdma_dev_access_netns(स्थिर काष्ठा ib_device *device,
			   स्थिर काष्ठा net *net);

#घोषणा IB_ROCE_UDP_ENCAP_VALID_PORT_MIN (0xC000)
#घोषणा IB_ROCE_UDP_ENCAP_VALID_PORT_MAX (0xFFFF)
#घोषणा IB_GRH_FLOWLABEL_MASK (0x000FFFFF)

/**
 * rdma_flow_label_to_udp_sport - generate a RoCE v2 UDP src port value based
 *                               on the flow_label
 *
 * This function will convert the 20 bit flow_label input to a valid RoCE v2
 * UDP src port 14 bit value. All RoCE V2 drivers should use this same
 * convention.
 */
अटल अंतरभूत u16 rdma_flow_label_to_udp_sport(u32 fl)
अणु
	u32 fl_low = fl & 0x03fff, fl_high = fl & 0xFC000;

	fl_low ^= fl_high >> 14;
	वापस (u16)(fl_low | IB_ROCE_UDP_ENCAP_VALID_PORT_MIN);
पूर्ण

/**
 * rdma_calc_flow_label - generate a RDMA symmetric flow label value based on
 *                        local and remote qpn values
 *
 * This function folded the multiplication results of two qpns, 24 bit each,
 * fields, and converts it to a 20 bit results.
 *
 * This function will create symmetric flow_label value based on the local
 * and remote qpn values. this will allow both the requester and responder
 * to calculate the same flow_label क्रम a given connection.
 *
 * This helper function should be used by driver in हाल the upper layer
 * provide a zero flow_label value. This is to improve entropy of RDMA
 * traffic in the network.
 */
अटल अंतरभूत u32 rdma_calc_flow_label(u32 lqpn, u32 rqpn)
अणु
	u64 v = (u64)lqpn * rqpn;

	v ^= v >> 20;
	v ^= v >> 40;

	वापस (u32)(v & IB_GRH_FLOWLABEL_MASK);
पूर्ण

स्थिर काष्ठा ib_port_immutable*
ib_port_immutable_पढ़ो(काष्ठा ib_device *dev, अचिन्हित पूर्णांक port);
#पूर्ण_अगर /* IB_VERBS_H */
