<शैली गुरु>
/******************************************************************************
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * vxge-मुख्य.h: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *              Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#अगर_अघोषित VXGE_MAIN_H
#घोषणा VXGE_MAIN_H

#समावेश "vxge-traffic.h"
#समावेश "vxge-config.h"
#समावेश "vxge-version.h"
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>

#घोषणा VXGE_DRIVER_NAME		"vxge"
#घोषणा VXGE_DRIVER_VENDOR		"Neterion, Inc"
#घोषणा VXGE_DRIVER_FW_VERSION_MAJOR	1

#घोषणा DRV_VERSION	VXGE_VERSION_MAJOR"."VXGE_VERSION_MINOR"."\
	VXGE_VERSION_FIX"."VXGE_VERSION_BUILD"-"\
	VXGE_VERSION_FOR

#घोषणा PCI_DEVICE_ID_TITAN_WIN		0x5733
#घोषणा PCI_DEVICE_ID_TITAN_UNI		0x5833
#घोषणा VXGE_HW_TITAN1_PCI_REVISION	1
#घोषणा VXGE_HW_TITAN1A_PCI_REVISION	2

#घोषणा	VXGE_USE_DEFAULT		0xffffffff
#घोषणा VXGE_HW_VPATH_MSIX_ACTIVE	4
#घोषणा VXGE_ALARM_MSIX_ID		2
#घोषणा VXGE_HW_RXSYNC_FREQ_CNT		4
#घोषणा VXGE_LL_WATCH_DOG_TIMEOUT	(15 * HZ)
#घोषणा VXGE_LL_RX_COPY_THRESHOLD	256
#घोषणा VXGE_DEF_FIFO_LENGTH		84

#घोषणा NO_STEERING		0
#घोषणा PORT_STEERING		0x1
#घोषणा RTH_STEERING		0x2
#घोषणा RX_TOS_STEERING		0x3
#घोषणा RX_VLAN_STEERING	0x4
#घोषणा RTH_BUCKET_SIZE		4

#घोषणा	TX_PRIORITY_STEERING	1
#घोषणा	TX_VLAN_STEERING	2
#घोषणा	TX_PORT_STEERING	3
#घोषणा	TX_MULTIQ_STEERING	4

#घोषणा VXGE_HW_MAC_ADDR_LEARN_DEFAULT VXGE_HW_RTS_MAC_DISABLE

#घोषणा VXGE_TTI_BTIMER_VAL 250000

#घोषणा VXGE_TTI_LTIMER_VAL	1000
#घोषणा VXGE_T1A_TTI_LTIMER_VAL	80
#घोषणा VXGE_TTI_RTIMER_VAL	0
#घोषणा VXGE_TTI_RTIMER_ADAPT_VAL	10
#घोषणा VXGE_T1A_TTI_RTIMER_VAL	400
#घोषणा VXGE_RTI_BTIMER_VAL	250
#घोषणा VXGE_RTI_LTIMER_VAL	100
#घोषणा VXGE_RTI_RTIMER_VAL	0
#घोषणा VXGE_RTI_RTIMER_ADAPT_VAL	15
#घोषणा VXGE_FIFO_INDICATE_MAX_PKTS	VXGE_DEF_FIFO_LENGTH
#घोषणा VXGE_ISR_POLLING_CNT 	8
#घोषणा VXGE_MAX_CONFIG_DEV	0xFF
#घोषणा VXGE_EXEC_MODE_DISABLE	0
#घोषणा VXGE_EXEC_MODE_ENABLE	1
#घोषणा VXGE_MAX_CONFIG_PORT	1
#घोषणा VXGE_ALL_VID_DISABLE	0
#घोषणा VXGE_ALL_VID_ENABLE	1
#घोषणा VXGE_PAUSE_CTRL_DISABLE	0
#घोषणा VXGE_PAUSE_CTRL_ENABLE	1

#घोषणा TTI_TX_URANGE_A	5
#घोषणा TTI_TX_URANGE_B	15
#घोषणा TTI_TX_URANGE_C	40
#घोषणा TTI_TX_UFC_A	5
#घोषणा TTI_TX_UFC_B	40
#घोषणा TTI_TX_UFC_C	60
#घोषणा TTI_TX_UFC_D	100
#घोषणा TTI_T1A_TX_UFC_A	30
#घोषणा TTI_T1A_TX_UFC_B	80
/* Slope - (max_mtu - min_mtu)/(max_mtu_ufc - min_mtu_ufc) */
/* Slope - 93 */
/* 60 - 9k Mtu, 140 - 1.5k mtu */
#घोषणा TTI_T1A_TX_UFC_C(mtu)	(60 + ((VXGE_HW_MAX_MTU - mtu) / 93))

/* Slope - 37 */
/* 100 - 9k Mtu, 300 - 1.5k mtu */
#घोषणा TTI_T1A_TX_UFC_D(mtu)	(100 + ((VXGE_HW_MAX_MTU - mtu) / 37))


#घोषणा RTI_RX_URANGE_A		5
#घोषणा RTI_RX_URANGE_B		15
#घोषणा RTI_RX_URANGE_C		40
#घोषणा RTI_T1A_RX_URANGE_A	1
#घोषणा RTI_T1A_RX_URANGE_B	20
#घोषणा RTI_T1A_RX_URANGE_C	50
#घोषणा RTI_RX_UFC_A		1
#घोषणा RTI_RX_UFC_B		5
#घोषणा RTI_RX_UFC_C		10
#घोषणा RTI_RX_UFC_D		15
#घोषणा RTI_T1A_RX_UFC_B	20
#घोषणा RTI_T1A_RX_UFC_C	50
#घोषणा RTI_T1A_RX_UFC_D	60

/*
 * The पूर्णांकerrupt rate is मुख्यtained at 3k per second with the moderation
 * parameters क्रम most traffic but not all. This is the maximum पूर्णांकerrupt
 * count allowed per function with INTA or per vector in the हाल of
 * MSI-X in a 10 millisecond समय period. Enabled only क्रम Titan 1A.
 */
#घोषणा VXGE_T1A_MAX_INTERRUPT_COUNT	100
#घोषणा VXGE_T1A_MAX_TX_INTERRUPT_COUNT	200

/* Milli secs समयr period */
#घोषणा VXGE_TIMER_DELAY		10000

#घोषणा VXGE_LL_MAX_FRAME_SIZE(dev) ((dev)->mtu + VXGE_HW_MAC_HEADER_MAX_SIZE)

#घोषणा is_sriov(function_mode) \
	((function_mode == VXGE_HW_FUNCTION_MODE_SRIOV) || \
	(function_mode == VXGE_HW_FUNCTION_MODE_SRIOV_8) || \
	(function_mode == VXGE_HW_FUNCTION_MODE_SRIOV_4))

क्रमागत vxge_reset_event अणु
	/* reset events */
	VXGE_LL_VPATH_RESET	= 0,
	VXGE_LL_DEVICE_RESET	= 1,
	VXGE_LL_FULL_RESET	= 2,
	VXGE_LL_START_RESET	= 3,
	VXGE_LL_COMPL_RESET	= 4
पूर्ण;
/* These flags represent the devices temporary state */
क्रमागत vxge_device_state_t अणु
__VXGE_STATE_RESET_CARD = 0,
__VXGE_STATE_CARD_UP
पूर्ण;

क्रमागत vxge_mac_addr_state अणु
	/* mac address states */
	VXGE_LL_MAC_ADDR_IN_LIST        = 0,
	VXGE_LL_MAC_ADDR_IN_DA_TABLE    = 1
पूर्ण;

काष्ठा vxge_drv_config अणु
	पूर्णांक config_dev_cnt;
	पूर्णांक total_dev_cnt;
	पूर्णांक g_no_cpus;
	अचिन्हित पूर्णांक vpath_per_dev;
पूर्ण;

काष्ठा macInfo अणु
	अचिन्हित अक्षर macaddr[ETH_ALEN];
	अचिन्हित अक्षर macmask[ETH_ALEN];
	अचिन्हित पूर्णांक vpath_no;
	क्रमागत vxge_mac_addr_state state;
पूर्ण;

काष्ठा vxge_config अणु
	पूर्णांक		tx_छोड़ो_enable;
	पूर्णांक		rx_छोड़ो_enable;

#घोषणा	NEW_NAPI_WEIGHT	64
	पूर्णांक		napi_weight;
	पूर्णांक		पूर्णांकr_type;
#घोषणा INTA	0
#घोषणा MSI	1
#घोषणा MSI_X	2

	पूर्णांक		addr_learn_en;

	u32		rth_steering:2,
			rth_algorithm:2,
			rth_hash_type_tcpipv4:1,
			rth_hash_type_ipv4:1,
			rth_hash_type_tcpipv6:1,
			rth_hash_type_ipv6:1,
			rth_hash_type_tcpipv6ex:1,
			rth_hash_type_ipv6ex:1,
			rth_bkt_sz:8;
	पूर्णांक		rth_jhash_golden_ratio;
	पूर्णांक		tx_steering_type;
	पूर्णांक 	fअगरo_indicate_max_pkts;
	काष्ठा vxge_hw_device_hw_info device_hw_info;
पूर्ण;

काष्ठा vxge_msix_entry अणु
	/* Mimicing the msix_entry काष्ठा of Kernel. */
	u16 vector;
	u16 entry;
	u16 in_use;
	व्योम *arg;
पूर्ण;

/* Software Statistics */

काष्ठा vxge_sw_stats अणु

	/* Virtual Path */
	अचिन्हित दीर्घ vpaths_खोलो;
	अचिन्हित दीर्घ vpath_खोलो_fail;

	/* Misc. */
	अचिन्हित दीर्घ link_up;
	अचिन्हित दीर्घ link_करोwn;
पूर्ण;

काष्ठा vxge_mac_addrs अणु
	काष्ठा list_head item;
	u64 macaddr;
	u64 macmask;
	क्रमागत vxge_mac_addr_state state;
पूर्ण;

काष्ठा vxgedev;

काष्ठा vxge_fअगरo_stats अणु
	काष्ठा u64_stats_sync	syncp;
	u64 tx_frms;
	u64 tx_bytes;

	अचिन्हित दीर्घ tx_errors;
	अचिन्हित दीर्घ txd_not_मुक्त;
	अचिन्हित दीर्घ txd_out_of_desc;
	अचिन्हित दीर्घ pci_map_fail;
पूर्ण;

काष्ठा vxge_fअगरo अणु
	काष्ठा net_device *ndev;
	काष्ठा pci_dev *pdev;
	काष्ठा __vxge_hw_fअगरo *handle;
	काष्ठा netdev_queue *txq;

	पूर्णांक tx_steering_type;
	पूर्णांक indicate_max_pkts;

	/* Adaptive पूर्णांकerrupt moderation parameters used in T1A */
	अचिन्हित दीर्घ पूर्णांकerrupt_count;
	अचिन्हित दीर्घ jअगरfies;

	u32 tx_vector_no;
	/* Tx stats */
	काष्ठा vxge_fअगरo_stats stats;
पूर्ण ____cacheline_aligned;

काष्ठा vxge_ring_stats अणु
	काष्ठा u64_stats_sync syncp;
	u64 rx_frms;
	u64 rx_mcast;
	u64 rx_bytes;

	अचिन्हित दीर्घ rx_errors;
	अचिन्हित दीर्घ rx_dropped;
	अचिन्हित दीर्घ prev_rx_frms;
	अचिन्हित दीर्घ pci_map_fail;
	अचिन्हित दीर्घ skb_alloc_fail;
पूर्ण;

काष्ठा vxge_ring अणु
	काष्ठा net_device	*ndev;
	काष्ठा pci_dev		*pdev;
	काष्ठा __vxge_hw_ring	*handle;
	/* The vpath id मुख्यtained in the driver -
	 * 0 to 'maximum_vpaths_in_function - 1'
	 */
	पूर्णांक driver_id;

	/* Adaptive पूर्णांकerrupt moderation parameters used in T1A */
	अचिन्हित दीर्घ पूर्णांकerrupt_count;
	अचिन्हित दीर्घ jअगरfies;

	/* copy of the flag indicating whether rx_hwts is to be used */
	u32 rx_hwts:1;

	पूर्णांक pkts_processed;
	पूर्णांक budget;

	काष्ठा napi_काष्ठा napi;
	काष्ठा napi_काष्ठा *napi_p;

#घोषणा VXGE_MAX_MAC_ADDR_COUNT		30

	पूर्णांक vlan_tag_strip;
	u32 rx_vector_no;
	क्रमागत vxge_hw_status last_status;

	/* Rx stats */
	काष्ठा vxge_ring_stats stats;
पूर्ण ____cacheline_aligned;

काष्ठा vxge_vpath अणु
	काष्ठा vxge_fअगरo fअगरo;
	काष्ठा vxge_ring ring;

	काष्ठा __vxge_hw_vpath_handle *handle;

	/* Actual vpath id क्रम this vpath in the device - 0 to 16 */
	पूर्णांक device_id;
	पूर्णांक max_mac_addr_cnt;
	पूर्णांक is_configured;
	पूर्णांक is_खोलो;
	काष्ठा vxgedev *vdev;
	u8 macaddr[ETH_ALEN];
	u8 macmask[ETH_ALEN];

#घोषणा VXGE_MAX_LEARN_MAC_ADDR_CNT	2048
	/* mac addresses currently programmed पूर्णांकo NIC */
	u16 mac_addr_cnt;
	u16 mcast_addr_cnt;
	काष्ठा list_head mac_addr_list;

	u32 level_err;
	u32 level_trace;
पूर्ण;
#घोषणा VXGE_COPY_DEBUG_INFO_TO_LL(vdev, err, trace) अणु	\
	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु		\
		vdev->vpaths[i].level_err = err;		\
		vdev->vpaths[i].level_trace = trace;		\
	पूर्ण							\
	vdev->level_err = err;					\
	vdev->level_trace = trace;				\
पूर्ण

काष्ठा vxgedev अणु
	काष्ठा net_device	*ndev;
	काष्ठा pci_dev		*pdev;
	काष्ठा __vxge_hw_device *devh;
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	पूर्णांक vlan_tag_strip;
	काष्ठा vxge_config	config;
	अचिन्हित दीर्घ	state;

	/* Indicates which vpath to reset */
	अचिन्हित दीर्घ  vp_reset;

	/* Timer used क्रम polling vpath resets */
	काष्ठा समयr_list vp_reset_समयr;

	/* Timer used क्रम polling vpath lockup */
	काष्ठा समयr_list vp_lockup_समयr;

	/*
	 * Flags to track whether device is in All Multicast
	 * or in promiscuous mode.
	 */
	u16		all_multi_flg;

	/* A flag indicating whether rx_hwts is to be used or not. */
	u32	rx_hwts:1,
		titan1:1;

	काष्ठा vxge_msix_entry *vxge_entries;
	काष्ठा msix_entry *entries;
	/*
	 * 4 क्रम each vpath * 17;
	 * total is 68
	 */
#घोषणा	VXGE_MAX_REQUESTED_MSIX	68
#घोषणा VXGE_INTR_STRLEN 80
	अक्षर desc[VXGE_MAX_REQUESTED_MSIX][VXGE_INTR_STRLEN];

	क्रमागत vxge_hw_event cric_err_event;

	पूर्णांक max_vpath_supported;
	पूर्णांक no_of_vpath;

	काष्ठा napi_काष्ठा napi;
	/* A debug option, when enabled and अगर error condition occurs,
	 * the driver will करो following steps:
	 * - mask all पूर्णांकerrupts
	 * - Not clear the source of the alarm
	 * - gracefully stop all I/O
	 * A diagnostic dump of रेजिस्टर and stats at this poपूर्णांक
	 * reveals very useful inक्रमmation.
	 */
	पूर्णांक exec_mode;
	पूर्णांक max_config_port;
	काष्ठा vxge_vpath	*vpaths;

	काष्ठा __vxge_hw_vpath_handle *vp_handles[VXGE_HW_MAX_VIRTUAL_PATHS];
	व्योम __iomem *bar0;
	काष्ठा vxge_sw_stats	stats;
	पूर्णांक		mtu;
	/* Below variables are used क्रम vpath selection to transmit a packet */
	u8 		vpath_selector[VXGE_HW_MAX_VIRTUAL_PATHS];
	u64		vpaths_deployed;

	u32 		पूर्णांकr_cnt;
	u32 		level_err;
	u32 		level_trace;
	अक्षर		fw_version[VXGE_HW_FW_STRLEN];
	काष्ठा work_काष्ठा reset_task;
पूर्ण;

काष्ठा vxge_rx_priv अणु
	काष्ठा sk_buff		*skb;
	अचिन्हित अक्षर		*skb_data;
	dma_addr_t		data_dma;
	dma_addr_t		data_size;
पूर्ण;

काष्ठा vxge_tx_priv अणु
	काष्ठा sk_buff		*skb;
	dma_addr_t		dma_buffers[MAX_SKB_FRAGS+1];
पूर्ण;

#घोषणा VXGE_MODULE_PARAM_INT(p, val) \
	अटल पूर्णांक p = val; \
	module_param(p, पूर्णांक, 0)

अटल अंतरभूत
व्योम vxge_os_समयr(काष्ठा समयr_list *समयr, व्योम (*func)(काष्ठा समयr_list *),
		   अचिन्हित दीर्घ समयout)
अणु
	समयr_setup(समयr, func, 0);
	mod_समयr(समयr, jअगरfies + समयout);
पूर्ण

व्योम vxge_initialize_ethtool_ops(काष्ठा net_device *ndev);
पूर्णांक vxge_fw_upgrade(काष्ठा vxgedev *vdev, अक्षर *fw_name, पूर्णांक override);

/* #घोषणा VXGE_DEBUG_INIT: debug क्रम initialization functions
 * #घोषणा VXGE_DEBUG_TX	 : debug transmit related functions
 * #घोषणा VXGE_DEBUG_RX  : debug recevice related functions
 * #घोषणा VXGE_DEBUG_MEM : debug memory module
 * #घोषणा VXGE_DEBUG_LOCK: debug locks
 * #घोषणा VXGE_DEBUG_SEM : debug semaphore
 * #घोषणा VXGE_DEBUG_ENTRYEXIT: debug functions by adding entry निकास statements
*/
#घोषणा VXGE_DEBUG_INIT		0x00000001
#घोषणा VXGE_DEBUG_TX		0x00000002
#घोषणा VXGE_DEBUG_RX		0x00000004
#घोषणा VXGE_DEBUG_MEM		0x00000008
#घोषणा VXGE_DEBUG_LOCK		0x00000010
#घोषणा VXGE_DEBUG_SEM		0x00000020
#घोषणा VXGE_DEBUG_ENTRYEXIT	0x00000040
#घोषणा VXGE_DEBUG_INTR		0x00000080
#घोषणा VXGE_DEBUG_LL_CONFIG	0x00000100

/* Debug tracing क्रम VXGE driver */
#अगर_अघोषित VXGE_DEBUG_MASK
#घोषणा VXGE_DEBUG_MASK	0x0
#पूर्ण_अगर

#अगर (VXGE_DEBUG_LL_CONFIG & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_ll_config(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_LL_CONFIG, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_ll_config(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर (VXGE_DEBUG_INIT & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_init(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_INIT, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_init(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर (VXGE_DEBUG_TX & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_tx(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_TX, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_tx(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर (VXGE_DEBUG_RX & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_rx(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_RX, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_rx(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर (VXGE_DEBUG_MEM & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_mem(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_MEM, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_mem(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर (VXGE_DEBUG_ENTRYEXIT & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_entryनिकास(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_ENTRYEXIT, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_entryनिकास(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर (VXGE_DEBUG_INTR & VXGE_DEBUG_MASK)
#घोषणा vxge_debug_पूर्णांकr(level, fmt, ...) \
	vxge_debug_ll(level, VXGE_DEBUG_INTR, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा vxge_debug_पूर्णांकr(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा VXGE_DEVICE_DEBUG_LEVEL_SET(level, mask, vdev) अणु\
	vxge_hw_device_debug_set((काष्ठा __vxge_hw_device  *)vdev->devh, \
		level, mask);\
	VXGE_COPY_DEBUG_INFO_TO_LL(vdev, \
		vxge_hw_device_error_level_get((काष्ठा __vxge_hw_device  *) \
			vdev->devh), \
		vxge_hw_device_trace_level_get((काष्ठा __vxge_hw_device  *) \
			vdev->devh));\
पूर्ण

#अगर_घोषित NETIF_F_GSO
#घोषणा vxge_tcp_mss(skb) (skb_shinfo(skb)->gso_size)
#घोषणा vxge_udp_mss(skb) (skb_shinfo(skb)->gso_size)
#घोषणा vxge_offload_type(skb) (skb_shinfo(skb)->gso_type)
#पूर्ण_अगर

#पूर्ण_अगर
