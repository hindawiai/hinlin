<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IBM Power Virtual Ethernet Device Driver
 *
 * Copyright (C) IBM Corporation, 2003, 2010
 *
 * Authors: Dave Larson <larson1@us.ibm.com>
 *	    Santiago Leon <santil@linux.vnet.ibm.com>
 *	    Brian King <brking@linux.vnet.ibm.com>
 *	    Robert Jennings <rcj@linux.vnet.ibm.com>
 *	    Anton Blanअक्षरd <anton@au.ibm.com>
 */

#अगर_अघोषित _IBMVETH_H
#घोषणा _IBMVETH_H

/* स्थिरants क्रम H_MULTICAST_CTRL */
#घोषणा IbmVethMcastReceptionModअगरyBit     0x80000UL
#घोषणा IbmVethMcastReceptionEnableBit     0x20000UL
#घोषणा IbmVethMcastFilterModअगरyBit        0x40000UL
#घोषणा IbmVethMcastFilterEnableBit        0x10000UL

#घोषणा IbmVethMcastEnableRecv       (IbmVethMcastReceptionModअगरyBit | IbmVethMcastReceptionEnableBit)
#घोषणा IbmVethMcastDisableRecv      (IbmVethMcastReceptionModअगरyBit)
#घोषणा IbmVethMcastEnableFiltering  (IbmVethMcastFilterModअगरyBit | IbmVethMcastFilterEnableBit)
#घोषणा IbmVethMcastDisableFiltering (IbmVethMcastFilterModअगरyBit)
#घोषणा IbmVethMcastAddFilter        0x1UL
#घोषणा IbmVethMcastRemoveFilter     0x2UL
#घोषणा IbmVethMcastClearFilterTable 0x3UL

#घोषणा IBMVETH_ILLAN_LRG_SR_ENABLED	0x0000000000010000UL
#घोषणा IBMVETH_ILLAN_LRG_SND_SUPPORT	0x0000000000008000UL
#घोषणा IBMVETH_ILLAN_PADDED_PKT_CSUM	0x0000000000002000UL
#घोषणा IBMVETH_ILLAN_TRUNK_PRI_MASK	0x0000000000000F00UL
#घोषणा IBMVETH_ILLAN_IPV6_TCP_CSUM		0x0000000000000004UL
#घोषणा IBMVETH_ILLAN_IPV4_TCP_CSUM		0x0000000000000002UL
#घोषणा IBMVETH_ILLAN_ACTIVE_TRUNK		0x0000000000000001UL

/* hcall macros */
#घोषणा h_रेजिस्टर_logical_lan(ua, buflst, rxq, fltlst, mac) \
  plpar_hcall_norets(H_REGISTER_LOGICAL_LAN, ua, buflst, rxq, fltlst, mac)

#घोषणा h_मुक्त_logical_lan(ua) \
  plpar_hcall_norets(H_FREE_LOGICAL_LAN, ua)

#घोषणा h_add_logical_lan_buffer(ua, buf) \
  plpar_hcall_norets(H_ADD_LOGICAL_LAN_BUFFER, ua, buf)

अटल अंतरभूत दीर्घ h_send_logical_lan(अचिन्हित दीर्घ unit_address,
		अचिन्हित दीर्घ desc1, अचिन्हित दीर्घ desc2, अचिन्हित दीर्घ desc3,
		अचिन्हित दीर्घ desc4, अचिन्हित दीर्घ desc5, अचिन्हित दीर्घ desc6,
		अचिन्हित दीर्घ corellator_in, अचिन्हित दीर्घ *corellator_out,
		अचिन्हित दीर्घ mss, अचिन्हित दीर्घ large_send_support)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];

	अगर (large_send_support)
		rc = plpar_hcall9(H_SEND_LOGICAL_LAN, retbuf, unit_address,
				  desc1, desc2, desc3, desc4, desc5, desc6,
				  corellator_in, mss);
	अन्यथा
		rc = plpar_hcall9(H_SEND_LOGICAL_LAN, retbuf, unit_address,
				  desc1, desc2, desc3, desc4, desc5, desc6,
				  corellator_in);

	*corellator_out = retbuf[0];

	वापस rc;
पूर्ण

अटल अंतरभूत दीर्घ h_illan_attributes(अचिन्हित दीर्घ unit_address,
				      अचिन्हित दीर्घ reset_mask, अचिन्हित दीर्घ set_mask,
				      अचिन्हित दीर्घ *ret_attributes)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall(H_ILLAN_ATTRIBUTES, retbuf, unit_address,
			 reset_mask, set_mask);

	*ret_attributes = retbuf[0];

	वापस rc;
पूर्ण

#घोषणा h_multicast_ctrl(ua, cmd, mac) \
  plpar_hcall_norets(H_MULTICAST_CTRL, ua, cmd, mac)

#घोषणा h_change_logical_lan_mac(ua, mac) \
  plpar_hcall_norets(H_CHANGE_LOGICAL_LAN_MAC, ua, mac)

#घोषणा IBMVETH_NUM_BUFF_POOLS 5
#घोषणा IBMVETH_IO_ENTITLEMENT_DEFAULT 4243456 /* MTU of 1500 needs 4.2Mb */
#घोषणा IBMVETH_BUFF_OH 22 /* Overhead: 14 ethernet header + 8 opaque handle */
#घोषणा IBMVETH_MIN_MTU 68
#घोषणा IBMVETH_MAX_POOL_COUNT 4096
#घोषणा IBMVETH_BUFF_LIST_SIZE 4096
#घोषणा IBMVETH_FILT_LIST_SIZE 4096
#घोषणा IBMVETH_MAX_BUF_SIZE (1024 * 128)

अटल पूर्णांक pool_size[] = अणु 512, 1024 * 2, 1024 * 16, 1024 * 32, 1024 * 64 पूर्ण;
अटल पूर्णांक pool_count[] = अणु 256, 512, 256, 256, 256 पूर्ण;
अटल पूर्णांक pool_count_cmo[] = अणु 256, 512, 256, 256, 64 पूर्ण;
अटल पूर्णांक pool_active[] = अणु 1, 1, 0, 0, 1पूर्ण;

#घोषणा IBM_VETH_INVALID_MAP ((u16)0xffff)

काष्ठा ibmveth_buff_pool अणु
    u32 size;
    u32 index;
    u32 buff_size;
    u32 threshold;
    atomic_t available;
    u32 consumer_index;
    u32 producer_index;
    u16 *मुक्त_map;
    dma_addr_t *dma_addr;
    काष्ठा sk_buff **skbuff;
    पूर्णांक active;
    काष्ठा kobject kobj;
पूर्ण;

काष्ठा ibmveth_rx_q अणु
    u64        index;
    u64        num_slots;
    u64        toggle;
    dma_addr_t queue_dma;
    u32        queue_len;
    काष्ठा ibmveth_rx_q_entry *queue_addr;
पूर्ण;

काष्ठा ibmveth_adapter अणु
    काष्ठा vio_dev *vdev;
    काष्ठा net_device *netdev;
    काष्ठा napi_काष्ठा napi;
    अचिन्हित पूर्णांक mcastFilterSize;
    व्योम * buffer_list_addr;
    व्योम * filter_list_addr;
    dma_addr_t buffer_list_dma;
    dma_addr_t filter_list_dma;
    काष्ठा ibmveth_buff_pool rx_buff_pool[IBMVETH_NUM_BUFF_POOLS];
    काष्ठा ibmveth_rx_q rx_queue;
    पूर्णांक pool_config;
    पूर्णांक rx_csum;
    पूर्णांक large_send;
    bool is_active_trunk;
    व्योम *bounce_buffer;
    dma_addr_t bounce_buffer_dma;

    u64 fw_ipv6_csum_support;
    u64 fw_ipv4_csum_support;
    u64 fw_large_send_support;
    /* adapter specअगरic stats */
    u64 replenish_task_cycles;
    u64 replenish_no_mem;
    u64 replenish_add_buff_failure;
    u64 replenish_add_buff_success;
    u64 rx_invalid_buffer;
    u64 rx_no_buffer;
    u64 tx_map_failed;
    u64 tx_send_failed;
    u64 tx_large_packets;
    u64 rx_large_packets;
    /* Ethtool settings */
	u8 duplex;
	u32 speed;
पूर्ण;

/*
 * We pass काष्ठा ibmveth_buf_desc_fields to the hypervisor in रेजिस्टरs,
 * so we करोn't need to byteswap the two elements. However since we use
 * a जोड़ (ibmveth_buf_desc) to convert from the काष्ठा to a u64 we
 * करो end up with endian specअगरic ordering of the elements and that
 * needs correcting.
 */
काष्ठा ibmveth_buf_desc_fields अणु
#अगर_घोषित __BIG_ENDIAN
	u32 flags_len;
	u32 address;
#अन्यथा
	u32 address;
	u32 flags_len;
#पूर्ण_अगर
#घोषणा IBMVETH_BUF_VALID	0x80000000
#घोषणा IBMVETH_BUF_TOGGLE	0x40000000
#घोषणा IBMVETH_BUF_LRG_SND     0x04000000
#घोषणा IBMVETH_BUF_NO_CSUM	0x02000000
#घोषणा IBMVETH_BUF_CSUM_GOOD	0x01000000
#घोषणा IBMVETH_BUF_LEN_MASK	0x00FFFFFF
पूर्ण;

जोड़ ibmveth_buf_desc अणु
    u64 desc;
    काष्ठा ibmveth_buf_desc_fields fields;
पूर्ण;

काष्ठा ibmveth_rx_q_entry अणु
	__be32 flags_off;
#घोषणा IBMVETH_RXQ_TOGGLE		0x80000000
#घोषणा IBMVETH_RXQ_TOGGLE_SHIFT	31
#घोषणा IBMVETH_RXQ_VALID		0x40000000
#घोषणा IBMVETH_RXQ_LRG_PKT		0x04000000
#घोषणा IBMVETH_RXQ_NO_CSUM		0x02000000
#घोषणा IBMVETH_RXQ_CSUM_GOOD		0x01000000
#घोषणा IBMVETH_RXQ_OFF_MASK		0x0000FFFF

	__be32 length;
	/* correlator is only used by the OS, no need to byte swap */
	u64 correlator;
पूर्ण;

#पूर्ण_अगर /* _IBMVETH_H */
