<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_H_
#घोषणा _IAVF_H_

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/udp.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>

#समावेश "iavf_type.h"
#समावेश <linux/avf/virtchnl.h>
#समावेश "iavf_txrx.h"
#समावेश "iavf_fdir.h"
#समावेश "iavf_adv_rss.h"

#घोषणा DEFAULT_DEBUG_LEVEL_SHIFT 3
#घोषणा PFX "iavf: "

/* VSI state flags shared with common code */
क्रमागत iavf_vsi_state_t अणु
	__IAVF_VSI_DOWN,
	/* This must be last as it determines the size of the BITMAP */
	__IAVF_VSI_STATE_SIZE__,
पूर्ण;

/* dummy काष्ठा to make common code less painful */
काष्ठा iavf_vsi अणु
	काष्ठा iavf_adapter *back;
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u16 seid;
	u16 id;
	DECLARE_BITMAP(state, __IAVF_VSI_STATE_SIZE__);
	पूर्णांक base_vector;
	u16 work_limit;
	u16 qs_handle;
	व्योम *priv;     /* client driver data reference. */
पूर्ण;

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IAVF_RX_BUFFER_WRITE	16	/* Must be घातer of 2 */
#घोषणा IAVF_DEFAULT_TXD	512
#घोषणा IAVF_DEFAULT_RXD	512
#घोषणा IAVF_MAX_TXD		4096
#घोषणा IAVF_MIN_TXD		64
#घोषणा IAVF_MAX_RXD		4096
#घोषणा IAVF_MIN_RXD		64
#घोषणा IAVF_REQ_DESCRIPTOR_MULTIPLE	32
#घोषणा IAVF_MAX_AQ_BUF_SIZE	4096
#घोषणा IAVF_AQ_LEN		32
#घोषणा IAVF_AQ_MAX_ERR	20 /* बार to try beक्रमe resetting AQ */

#घोषणा MAXIMUM_ETHERNET_VLAN_SIZE (VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)

#घोषणा IAVF_RX_DESC(R, i) (&(((जोड़ iavf_32byte_rx_desc *)((R)->desc))[i]))
#घोषणा IAVF_TX_DESC(R, i) (&(((काष्ठा iavf_tx_desc *)((R)->desc))[i]))
#घोषणा IAVF_TX_CTXTDESC(R, i) \
	(&(((काष्ठा iavf_tx_context_desc *)((R)->desc))[i]))
#घोषणा IAVF_MAX_REQ_QUEUES 16

#घोषणा IAVF_HKEY_ARRAY_SIZE ((IAVF_VFQF_HKEY_MAX_INDEX + 1) * 4)
#घोषणा IAVF_HLUT_ARRAY_SIZE ((IAVF_VFQF_HLUT_MAX_INDEX + 1) * 4)
#घोषणा IAVF_MBPS_DIVISOR	125000 /* भागisor to convert to Mbps */

#घोषणा IAVF_VIRTCHNL_VF_RESOURCE_SIZE (माप(काष्ठा virtchnl_vf_resource) + \
					(IAVF_MAX_VF_VSI * \
					 माप(काष्ठा virtchnl_vsi_resource)))

/* MAX_MSIX_Q_VECTORS of these are allocated,
 * but we only use one per queue-specअगरic vector.
 */
काष्ठा iavf_q_vector अणु
	काष्ठा iavf_adapter *adapter;
	काष्ठा iavf_vsi *vsi;
	काष्ठा napi_काष्ठा napi;
	काष्ठा iavf_ring_container rx;
	काष्ठा iavf_ring_container tx;
	u32 ring_mask;
	u8 itr_countकरोwn;	/* when 0 should adjust adaptive ITR */
	u8 num_ringpairs;	/* total number of ring pairs in vector */
	u16 v_idx;		/* index in the vsi->q_vector array. */
	u16 reg_idx;		/* रेजिस्टर index of the पूर्णांकerrupt */
	अक्षर name[IFNAMSIZ + 15];
	bool arm_wb_state;
	cpumask_t affinity_mask;
	काष्ठा irq_affinity_notअगरy affinity_notअगरy;
पूर्ण;

/* Helper macros to चयन between पूर्णांकs/sec and what the रेजिस्टर uses.
 * And yes, it's the same math going both ways.  The lowest value
 * supported by all of the iavf hardware is 8.
 */
#घोषणा EITR_INTS_PER_SEC_TO_REG(_eitr) \
	((_eitr) ? (1000000000 / ((_eitr) * 256)) : 8)
#घोषणा EITR_REG_TO_INTS_PER_SEC EITR_INTS_PER_SEC_TO_REG

#घोषणा IAVF_DESC_UNUSED(R) \
	((((R)->next_to_clean > (R)->next_to_use) ? 0 : (R)->count) + \
	(R)->next_to_clean - (R)->next_to_use - 1)

#घोषणा OTHER_VECTOR 1
#घोषणा NONQ_VECS (OTHER_VECTOR)

#घोषणा MIN_MSIX_Q_VECTORS 1
#घोषणा MIN_MSIX_COUNT (MIN_MSIX_Q_VECTORS + NONQ_VECS)

#घोषणा IAVF_QUEUE_END_OF_LIST 0x7FF
#घोषणा IAVF_FREE_VECTOR 0x7FFF
काष्ठा iavf_mac_filter अणु
	काष्ठा list_head list;
	u8 macaddr[ETH_ALEN];
	bool हटाओ;		/* filter needs to be हटाओd */
	bool add;		/* filter needs to be added */
पूर्ण;

काष्ठा iavf_vlan_filter अणु
	काष्ठा list_head list;
	u16 vlan;
	bool हटाओ;		/* filter needs to be हटाओd */
	bool add;		/* filter needs to be added */
पूर्ण;

#घोषणा IAVF_MAX_TRAFFIC_CLASS	4
/* State of traffic class creation */
क्रमागत iavf_tc_state_t अणु
	__IAVF_TC_INVALID, /* no traffic class, शेष state */
	__IAVF_TC_RUNNING, /* traffic classes have been created */
पूर्ण;

/* channel info */
काष्ठा iavf_channel_config अणु
	काष्ठा virtchnl_channel_info ch_info[IAVF_MAX_TRAFFIC_CLASS];
	क्रमागत iavf_tc_state_t state;
	u8 total_qps;
पूर्ण;

/* State of cloud filter */
क्रमागत iavf_cloud_filter_state_t अणु
	__IAVF_CF_INVALID,	 /* cloud filter not added */
	__IAVF_CF_ADD_PENDING, /* cloud filter pending add by the PF */
	__IAVF_CF_DEL_PENDING, /* cloud filter pending del by the PF */
	__IAVF_CF_ACTIVE,	 /* cloud filter is active */
पूर्ण;

/* Driver state. The order of these is important! */
क्रमागत iavf_state_t अणु
	__IAVF_STARTUP,		/* driver loaded, probe complete */
	__IAVF_REMOVE,		/* driver is being unloaded */
	__IAVF_INIT_VERSION_CHECK,	/* aq msg sent, aरुकोing reply */
	__IAVF_INIT_GET_RESOURCES,	/* aq msg sent, aरुकोing reply */
	__IAVF_INIT_SW,		/* got resources, setting up काष्ठाs */
	__IAVF_RESETTING,		/* in reset */
	__IAVF_COMM_FAILED,		/* communication with PF failed */
	/* Below here, watchकरोg is running */
	__IAVF_DOWN,			/* पढ़ोy, can be खोलोed */
	__IAVF_DOWN_PENDING,		/* descending, रुकोing क्रम watchकरोg */
	__IAVF_TESTING,		/* in ethtool self-test */
	__IAVF_RUNNING,		/* खोलोed, working */
पूर्ण;

क्रमागत iavf_critical_section_t अणु
	__IAVF_IN_CRITICAL_TASK,	/* cannot be पूर्णांकerrupted */
	__IAVF_IN_CLIENT_TASK,
	__IAVF_IN_REMOVE_TASK,	/* device being हटाओd */
पूर्ण;

#घोषणा IAVF_CLOUD_FIELD_OMAC		0x01
#घोषणा IAVF_CLOUD_FIELD_IMAC		0x02
#घोषणा IAVF_CLOUD_FIELD_IVLAN	0x04
#घोषणा IAVF_CLOUD_FIELD_TEN_ID	0x08
#घोषणा IAVF_CLOUD_FIELD_IIP		0x10

#घोषणा IAVF_CF_FLAGS_OMAC	IAVF_CLOUD_FIELD_OMAC
#घोषणा IAVF_CF_FLAGS_IMAC	IAVF_CLOUD_FIELD_IMAC
#घोषणा IAVF_CF_FLAGS_IMAC_IVLAN	(IAVF_CLOUD_FIELD_IMAC |\
					 IAVF_CLOUD_FIELD_IVLAN)
#घोषणा IAVF_CF_FLAGS_IMAC_TEN_ID	(IAVF_CLOUD_FIELD_IMAC |\
					 IAVF_CLOUD_FIELD_TEN_ID)
#घोषणा IAVF_CF_FLAGS_OMAC_TEN_ID_IMAC	(IAVF_CLOUD_FIELD_OMAC |\
						 IAVF_CLOUD_FIELD_IMAC |\
						 IAVF_CLOUD_FIELD_TEN_ID)
#घोषणा IAVF_CF_FLAGS_IMAC_IVLAN_TEN_ID	(IAVF_CLOUD_FIELD_IMAC |\
						 IAVF_CLOUD_FIELD_IVLAN |\
						 IAVF_CLOUD_FIELD_TEN_ID)
#घोषणा IAVF_CF_FLAGS_IIP	IAVF_CLOUD_FIELD_IIP

/* bookkeeping of cloud filters */
काष्ठा iavf_cloud_filter अणु
	क्रमागत iavf_cloud_filter_state_t state;
	काष्ठा list_head list;
	काष्ठा virtchnl_filter f;
	अचिन्हित दीर्घ cookie;
	bool del;		/* filter needs to be deleted */
	bool add;		/* filter needs to be added */
पूर्ण;

#घोषणा IAVF_RESET_WAIT_MS 10
#घोषणा IAVF_RESET_WAIT_DETECTED_COUNT 500
#घोषणा IAVF_RESET_WAIT_COMPLETE_COUNT 2000

/* board specअगरic निजी data काष्ठाure */
काष्ठा iavf_adapter अणु
	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा adminq_task;
	काष्ठा delayed_work client_task;
	काष्ठा delayed_work init_task;
	रुको_queue_head_t करोwn_रुकोqueue;
	काष्ठा iavf_q_vector *q_vectors;
	काष्ठा list_head vlan_filter_list;
	काष्ठा list_head mac_filter_list;
	/* Lock to protect accesses to MAC and VLAN lists */
	spinlock_t mac_vlan_list_lock;
	अक्षर misc_vector_name[IFNAMSIZ + 9];
	पूर्णांक num_active_queues;
	पूर्णांक num_req_queues;

	/* TX */
	काष्ठा iavf_ring *tx_rings;
	u32 tx_समयout_count;
	u32 tx_desc_count;

	/* RX */
	काष्ठा iavf_ring *rx_rings;
	u64 hw_csum_rx_error;
	u32 rx_desc_count;
	पूर्णांक num_msix_vectors;
	पूर्णांक num_iwarp_msix;
	पूर्णांक iwarp_base_vector;
	u32 client_pending;
	काष्ठा iavf_client_instance *cinst;
	काष्ठा msix_entry *msix_entries;

	u32 flags;
#घोषणा IAVF_FLAG_RX_CSUM_ENABLED		BIT(0)
#घोषणा IAVF_FLAG_PF_COMMS_FAILED		BIT(3)
#घोषणा IAVF_FLAG_RESET_PENDING		BIT(4)
#घोषणा IAVF_FLAG_RESET_NEEDED		BIT(5)
#घोषणा IAVF_FLAG_WB_ON_ITR_CAPABLE		BIT(6)
#घोषणा IAVF_FLAG_SERVICE_CLIENT_REQUESTED	BIT(9)
#घोषणा IAVF_FLAG_CLIENT_NEEDS_OPEN		BIT(10)
#घोषणा IAVF_FLAG_CLIENT_NEEDS_CLOSE		BIT(11)
#घोषणा IAVF_FLAG_CLIENT_NEEDS_L2_PARAMS	BIT(12)
#घोषणा IAVF_FLAG_PROMISC_ON			BIT(13)
#घोषणा IAVF_FLAG_ALLMULTI_ON			BIT(14)
#घोषणा IAVF_FLAG_LEGACY_RX			BIT(15)
#घोषणा IAVF_FLAG_REINIT_ITR_NEEDED		BIT(16)
#घोषणा IAVF_FLAG_QUEUES_DISABLED		BIT(17)
/* duplicates क्रम common code */
#घोषणा IAVF_FLAG_DCB_ENABLED			0
	/* flags क्रम admin queue service task */
	u32 aq_required;
#घोषणा IAVF_FLAG_AQ_ENABLE_QUEUES		BIT(0)
#घोषणा IAVF_FLAG_AQ_DISABLE_QUEUES		BIT(1)
#घोषणा IAVF_FLAG_AQ_ADD_MAC_FILTER		BIT(2)
#घोषणा IAVF_FLAG_AQ_ADD_VLAN_FILTER		BIT(3)
#घोषणा IAVF_FLAG_AQ_DEL_MAC_FILTER		BIT(4)
#घोषणा IAVF_FLAG_AQ_DEL_VLAN_FILTER		BIT(5)
#घोषणा IAVF_FLAG_AQ_CONFIGURE_QUEUES		BIT(6)
#घोषणा IAVF_FLAG_AQ_MAP_VECTORS		BIT(7)
#घोषणा IAVF_FLAG_AQ_HANDLE_RESET		BIT(8)
#घोषणा IAVF_FLAG_AQ_CONFIGURE_RSS		BIT(9) /* direct AQ config */
#घोषणा IAVF_FLAG_AQ_GET_CONFIG		BIT(10)
/* Newer style, RSS करोne by the PF so we can ignore hardware vagaries. */
#घोषणा IAVF_FLAG_AQ_GET_HENA			BIT(11)
#घोषणा IAVF_FLAG_AQ_SET_HENA			BIT(12)
#घोषणा IAVF_FLAG_AQ_SET_RSS_KEY		BIT(13)
#घोषणा IAVF_FLAG_AQ_SET_RSS_LUT		BIT(14)
#घोषणा IAVF_FLAG_AQ_REQUEST_PROMISC		BIT(15)
#घोषणा IAVF_FLAG_AQ_RELEASE_PROMISC		BIT(16)
#घोषणा IAVF_FLAG_AQ_REQUEST_ALLMULTI		BIT(17)
#घोषणा IAVF_FLAG_AQ_RELEASE_ALLMULTI		BIT(18)
#घोषणा IAVF_FLAG_AQ_ENABLE_VLAN_STRIPPING	BIT(19)
#घोषणा IAVF_FLAG_AQ_DISABLE_VLAN_STRIPPING	BIT(20)
#घोषणा IAVF_FLAG_AQ_ENABLE_CHANNELS		BIT(21)
#घोषणा IAVF_FLAG_AQ_DISABLE_CHANNELS		BIT(22)
#घोषणा IAVF_FLAG_AQ_ADD_CLOUD_FILTER		BIT(23)
#घोषणा IAVF_FLAG_AQ_DEL_CLOUD_FILTER		BIT(24)
#घोषणा IAVF_FLAG_AQ_ADD_Fसूची_FILTER		BIT(25)
#घोषणा IAVF_FLAG_AQ_DEL_Fसूची_FILTER		BIT(26)
#घोषणा IAVF_FLAG_AQ_ADD_ADV_RSS_CFG		BIT(27)
#घोषणा IAVF_FLAG_AQ_DEL_ADV_RSS_CFG		BIT(28)

	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;

	काष्ठा iavf_hw hw; /* defined in iavf_type.h */

	क्रमागत iavf_state_t state;
	अचिन्हित दीर्घ crit_section;

	काष्ठा delayed_work watchकरोg_task;
	bool netdev_रेजिस्टरed;
	bool link_up;
	क्रमागत virtchnl_link_speed link_speed;
	/* This is only populated अगर the VIRTCHNL_VF_CAP_ADV_LINK_SPEED is set
	 * in vf_res->vf_cap_flags. Use ADV_LINK_SUPPORT macro to determine अगर
	 * this field is valid. This field should be used going क्रमward and the
	 * क्रमागत virtchnl_link_speed above should be considered the legacy way of
	 * storing/communicating link speeds.
	 */
	u32 link_speed_mbps;

	क्रमागत virtchnl_ops current_op;
#घोषणा CLIENT_ALLOWED(_a) ((_a)->vf_res ? \
			    (_a)->vf_res->vf_cap_flags & \
				VIRTCHNL_VF_OFFLOAD_IWARP : \
			    0)
#घोषणा CLIENT_ENABLED(_a) ((_a)->cinst)
/* RSS by the PF should be preferred over RSS via other methods. */
#घोषणा RSS_PF(_a) ((_a)->vf_res->vf_cap_flags & \
		    VIRTCHNL_VF_OFFLOAD_RSS_PF)
#घोषणा RSS_AQ(_a) ((_a)->vf_res->vf_cap_flags & \
		    VIRTCHNL_VF_OFFLOAD_RSS_AQ)
#घोषणा RSS_REG(_a) (!((_a)->vf_res->vf_cap_flags & \
		       (VIRTCHNL_VF_OFFLOAD_RSS_AQ | \
			VIRTCHNL_VF_OFFLOAD_RSS_PF)))
#घोषणा VLAN_ALLOWED(_a) ((_a)->vf_res->vf_cap_flags & \
			  VIRTCHNL_VF_OFFLOAD_VLAN)
#घोषणा ADV_LINK_SUPPORT(_a) ((_a)->vf_res->vf_cap_flags & \
			      VIRTCHNL_VF_CAP_ADV_LINK_SPEED)
#घोषणा Fसूची_FLTR_SUPPORT(_a) ((_a)->vf_res->vf_cap_flags & \
			       VIRTCHNL_VF_OFFLOAD_Fसूची_PF)
#घोषणा ADV_RSS_SUPPORT(_a) ((_a)->vf_res->vf_cap_flags & \
			     VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF)
	काष्ठा virtchnl_vf_resource *vf_res; /* incl. all VSIs */
	काष्ठा virtchnl_vsi_resource *vsi_res; /* our LAN VSI */
	काष्ठा virtchnl_version_info pf_version;
#घोषणा PF_IS_V11(_a) (((_a)->pf_version.major == 1) && \
		       ((_a)->pf_version.minor == 1))
	u16 msg_enable;
	काष्ठा iavf_eth_stats current_stats;
	काष्ठा iavf_vsi vsi;
	u32 aq_रुको_count;
	/* RSS stuff */
	u64 hena;
	u16 rss_key_size;
	u16 rss_lut_size;
	u8 *rss_key;
	u8 *rss_lut;
	/* ADQ related members */
	काष्ठा iavf_channel_config ch_config;
	u8 num_tc;
	काष्ठा list_head cloud_filter_list;
	/* lock to protect access to the cloud filter list */
	spinlock_t cloud_filter_list_lock;
	u16 num_cloud_filters;

#घोषणा IAVF_MAX_Fसूची_FILTERS 128	/* max allowed Flow Director filters */
	u16 fdir_active_fltr;
	काष्ठा list_head fdir_list_head;
	spinlock_t fdir_fltr_lock;	/* protect the Flow Director filter list */

	काष्ठा list_head adv_rss_list_head;
	spinlock_t adv_rss_lock;	/* protect the RSS management list */
पूर्ण;


/* Ethtool Private Flags */

/* lan device, used by client पूर्णांकerface */
काष्ठा iavf_device अणु
	काष्ठा list_head list;
	काष्ठा iavf_adapter *vf;
पूर्ण;

/* needed by iavf_ethtool.c */
बाह्य अक्षर iavf_driver_name[];
बाह्य काष्ठा workqueue_काष्ठा *iavf_wq;

पूर्णांक iavf_up(काष्ठा iavf_adapter *adapter);
व्योम iavf_करोwn(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_process_config(काष्ठा iavf_adapter *adapter);
व्योम iavf_schedule_reset(काष्ठा iavf_adapter *adapter);
व्योम iavf_reset(काष्ठा iavf_adapter *adapter);
व्योम iavf_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम iavf_update_stats(काष्ठा iavf_adapter *adapter);
व्योम iavf_reset_पूर्णांकerrupt_capability(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_init_पूर्णांकerrupt_scheme(काष्ठा iavf_adapter *adapter);
व्योम iavf_irq_enable_queues(काष्ठा iavf_adapter *adapter, u32 mask);
व्योम iavf_मुक्त_all_tx_resources(काष्ठा iavf_adapter *adapter);
व्योम iavf_मुक्त_all_rx_resources(काष्ठा iavf_adapter *adapter);

व्योम iavf_napi_add_all(काष्ठा iavf_adapter *adapter);
व्योम iavf_napi_del_all(काष्ठा iavf_adapter *adapter);

पूर्णांक iavf_send_api_ver(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_verअगरy_api_ver(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_send_vf_config_msg(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_get_vf_config(काष्ठा iavf_adapter *adapter);
व्योम iavf_irq_enable(काष्ठा iavf_adapter *adapter, bool flush);
व्योम iavf_configure_queues(काष्ठा iavf_adapter *adapter);
व्योम iavf_deconfigure_queues(काष्ठा iavf_adapter *adapter);
व्योम iavf_enable_queues(काष्ठा iavf_adapter *adapter);
व्योम iavf_disable_queues(काष्ठा iavf_adapter *adapter);
व्योम iavf_map_queues(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_request_queues(काष्ठा iavf_adapter *adapter, पूर्णांक num);
व्योम iavf_add_ether_addrs(काष्ठा iavf_adapter *adapter);
व्योम iavf_del_ether_addrs(काष्ठा iavf_adapter *adapter);
व्योम iavf_add_vlans(काष्ठा iavf_adapter *adapter);
व्योम iavf_del_vlans(काष्ठा iavf_adapter *adapter);
व्योम iavf_set_promiscuous(काष्ठा iavf_adapter *adapter, पूर्णांक flags);
व्योम iavf_request_stats(काष्ठा iavf_adapter *adapter);
व्योम iavf_request_reset(काष्ठा iavf_adapter *adapter);
व्योम iavf_get_hena(काष्ठा iavf_adapter *adapter);
व्योम iavf_set_hena(काष्ठा iavf_adapter *adapter);
व्योम iavf_set_rss_key(काष्ठा iavf_adapter *adapter);
व्योम iavf_set_rss_lut(काष्ठा iavf_adapter *adapter);
व्योम iavf_enable_vlan_stripping(काष्ठा iavf_adapter *adapter);
व्योम iavf_disable_vlan_stripping(काष्ठा iavf_adapter *adapter);
व्योम iavf_virtchnl_completion(काष्ठा iavf_adapter *adapter,
			      क्रमागत virtchnl_ops v_opcode,
			      क्रमागत iavf_status v_retval, u8 *msg, u16 msglen);
पूर्णांक iavf_config_rss(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_lan_add_device(काष्ठा iavf_adapter *adapter);
पूर्णांक iavf_lan_del_device(काष्ठा iavf_adapter *adapter);
व्योम iavf_client_subtask(काष्ठा iavf_adapter *adapter);
व्योम iavf_notअगरy_client_message(काष्ठा iavf_vsi *vsi, u8 *msg, u16 len);
व्योम iavf_notअगरy_client_l2_params(काष्ठा iavf_vsi *vsi);
व्योम iavf_notअगरy_client_खोलो(काष्ठा iavf_vsi *vsi);
व्योम iavf_notअगरy_client_बंद(काष्ठा iavf_vsi *vsi, bool reset);
व्योम iavf_enable_channels(काष्ठा iavf_adapter *adapter);
व्योम iavf_disable_channels(काष्ठा iavf_adapter *adapter);
व्योम iavf_add_cloud_filter(काष्ठा iavf_adapter *adapter);
व्योम iavf_del_cloud_filter(काष्ठा iavf_adapter *adapter);
व्योम iavf_add_fdir_filter(काष्ठा iavf_adapter *adapter);
व्योम iavf_del_fdir_filter(काष्ठा iavf_adapter *adapter);
व्योम iavf_add_adv_rss_cfg(काष्ठा iavf_adapter *adapter);
व्योम iavf_del_adv_rss_cfg(काष्ठा iavf_adapter *adapter);
काष्ठा iavf_mac_filter *iavf_add_filter(काष्ठा iavf_adapter *adapter,
					स्थिर u8 *macaddr);
#पूर्ण_अगर /* _IAVF_H_ */
