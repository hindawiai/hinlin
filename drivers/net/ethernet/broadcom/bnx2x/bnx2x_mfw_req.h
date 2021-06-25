<शैली गुरु>
/* bnx2x_mfw_req.h: Qlogic Everest network driver.
 *
 * Copyright (c) 2012-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNX2X_MFW_REQ_H
#घोषणा BNX2X_MFW_REQ_H

#घोषणा PORT_0			0
#घोषणा PORT_1			1
#घोषणा PORT_MAX		2
#घोषणा NVM_PATH_MAX		2

/* FCoE capabilities required from the driver */
काष्ठा fcoe_capabilities अणु
	u32 capability1;
	/* Maximum number of I/Os per connection */
	#घोषणा FCOE_IOS_PER_CONNECTION_MASK    0x0000ffff
	#घोषणा FCOE_IOS_PER_CONNECTION_SHIFT   0
	/* Maximum number of Logins per port */
	#घोषणा FCOE_LOGINS_PER_PORT_MASK       0xffff0000
	#घोषणा FCOE_LOGINS_PER_PORT_SHIFT   16

	u32 capability2;
	/* Maximum number of exchanges */
	#घोषणा FCOE_NUMBER_OF_EXCHANGES_MASK   0x0000ffff
	#घोषणा FCOE_NUMBER_OF_EXCHANGES_SHIFT  0
	/* Maximum NPIV WWN per port */
	#घोषणा FCOE_NPIV_WWN_PER_PORT_MASK     0xffff0000
	#घोषणा FCOE_NPIV_WWN_PER_PORT_SHIFT    16

	u32 capability3;
	/* Maximum number of tarमाला_लो supported */
	#घोषणा FCOE_TARGETS_SUPPORTED_MASK     0x0000ffff
	#घोषणा FCOE_TARGETS_SUPPORTED_SHIFT    0
	/* Maximum number of outstanding commands across all connections */
	#घोषणा FCOE_OUTSTANDING_COMMANDS_MASK  0xffff0000
	#घोषणा FCOE_OUTSTANDING_COMMANDS_SHIFT 16

	u32 capability4;
	#घोषणा FCOE_CAPABILITY4_STATEFUL			0x00000001
	#घोषणा FCOE_CAPABILITY4_STATELESS			0x00000002
	#घोषणा FCOE_CAPABILITY4_CAPABILITIES_REPORTED_VALID	0x00000004
पूर्ण;

काष्ठा glob_ncsi_oem_data अणु
	u32 driver_version;
	u32 unused[3];
	काष्ठा fcoe_capabilities fcoe_features[NVM_PATH_MAX][PORT_MAX];
पूर्ण;

/* current drv_info version */
#घोषणा DRV_INFO_CUR_VER 2

/* drv_info op codes supported */
क्रमागत drv_info_opcode अणु
	ETH_STATS_OPCODE,
	FCOE_STATS_OPCODE,
	ISCSI_STATS_OPCODE
पूर्ण;

#घोषणा ETH_STAT_INFO_VERSION_LEN	12
/*  Per PCI Function Ethernet Statistics required from the driver */
काष्ठा eth_stats_info अणु
	/* Function's Driver Version. padded to 12 */
	u8 version[ETH_STAT_INFO_VERSION_LEN];
	/* Locally Admin Addr. BigEndian EIU48. Actual size is 6 bytes */
	u8 mac_local[8];
	u8 mac_add1[8];		/* Additional Programmed MAC Addr 1. */
	u8 mac_add2[8];		/* Additional Programmed MAC Addr 2. */
	u32 mtu_size;		/* MTU Size. Note   : Negotiated MTU */
	u32 feature_flags;	/* Feature_Flags. */
#घोषणा FEATURE_ETH_CHKSUM_OFFLOAD_MASK		0x01
#घोषणा FEATURE_ETH_LSO_MASK			0x02
#घोषणा FEATURE_ETH_BOOTMODE_MASK		0x1C
#घोषणा FEATURE_ETH_BOOTMODE_SHIFT		2
#घोषणा FEATURE_ETH_BOOTMODE_NONE		(0x0 << 2)
#घोषणा FEATURE_ETH_BOOTMODE_PXE		(0x1 << 2)
#घोषणा FEATURE_ETH_BOOTMODE_ISCSI		(0x2 << 2)
#घोषणा FEATURE_ETH_BOOTMODE_FCOE		(0x3 << 2)
#घोषणा FEATURE_ETH_TOE_MASK			0x20
	u32 lso_max_size;	/* LSO MaxOffloadSize. */
	u32 lso_min_seg_cnt;	/* LSO MinSegmentCount. */
	/* Num Offloaded Connections TCP_IPv4. */
	u32 ipv4_ofld_cnt;
	/* Num Offloaded Connections TCP_IPv6. */
	u32 ipv6_ofld_cnt;
	u32 promiscuous_mode;	/* Promiscuous Mode. non-zero true */
	u32 txq_size;		/* TX Descriptors Queue Size */
	u32 rxq_size;		/* RX Descriptors Queue Size */
	/* TX Descriptor Queue Avg Depth. % Avg Queue Depth since last poll */
	u32 txq_avg_depth;
	/* RX Descriptors Queue Avg Depth. % Avg Queue Depth since last poll */
	u32 rxq_avg_depth;
	/* IOV_Offload. 0=none; 1=MultiQueue, 2=VEB 3= VEPA*/
	u32 iov_offload;
	/* Number of NetQueue/VMQ Config'd. */
	u32 netq_cnt;
	u32 vf_cnt;		/* Num VF asचिन्हित to this PF. */
पूर्ण;

/*  Per PCI Function FCOE Statistics required from the driver */
काष्ठा fcoe_stats_info अणु
	u8 version[12];		/* Function's Driver Version. */
	u8 mac_local[8];	/* Locally Admin Addr. */
	u8 mac_add1[8];		/* Additional Programmed MAC Addr 1. */
	u8 mac_add2[8];		/* Additional Programmed MAC Addr 2. */
	/* QoS Priority (per 802.1p). 0-7255 */
	u32 qos_priority;
	u32 txq_size;		/* FCoE TX Descriptors Queue Size. */
	u32 rxq_size;		/* FCoE RX Descriptors Queue Size. */
	/* FCoE TX Descriptor Queue Avg Depth. */
	u32 txq_avg_depth;
	/* FCoE RX Descriptors Queue Avg Depth. */
	u32 rxq_avg_depth;
	u32 rx_frames_lo;	/* FCoE RX Frames received. */
	u32 rx_frames_hi;	/* FCoE RX Frames received. */
	u32 rx_bytes_lo;	/* FCoE RX Bytes received. */
	u32 rx_bytes_hi;	/* FCoE RX Bytes received. */
	u32 tx_frames_lo;	/* FCoE TX Frames sent. */
	u32 tx_frames_hi;	/* FCoE TX Frames sent. */
	u32 tx_bytes_lo;	/* FCoE TX Bytes sent. */
	u32 tx_bytes_hi;	/* FCoE TX Bytes sent. */
पूर्ण;

/* Per PCI  Function iSCSI Statistics required from the driver*/
काष्ठा iscsi_stats_info अणु
	u8 version[12];		/* Function's Driver Version. */
	u8 mac_local[8];	/* Locally Admin iSCSI MAC Addr. */
	u8 mac_add1[8];		/* Additional Programmed MAC Addr 1. */
	/* QoS Priority (per 802.1p). 0-7255 */
	u32 qos_priority;
	u8 initiator_name[64];	/* iSCSI Boot Initiator Node name. */
	u8 ww_port_name[64];	/* iSCSI World wide port name */
	u8 boot_target_name[64];/* iSCSI Boot Target Name. */
	u8 boot_target_ip[16];	/* iSCSI Boot Target IP. */
	u32 boot_target_portal;	/* iSCSI Boot Target Portal. */
	u8 boot_init_ip[16];	/* iSCSI Boot Initiator IP Address. */
	u32 max_frame_size;	/* Max Frame Size. bytes */
	u32 txq_size;		/* PDU TX Descriptors Queue Size. */
	u32 rxq_size;		/* PDU RX Descriptors Queue Size. */
	u32 txq_avg_depth;	/* PDU TX Descriptor Queue Avg Depth. */
	u32 rxq_avg_depth;	/* PDU RX Descriptors Queue Avg Depth. */
	u32 rx_pdus_lo;		/* iSCSI PDUs received. */
	u32 rx_pdus_hi;		/* iSCSI PDUs received. */
	u32 rx_bytes_lo;	/* iSCSI RX Bytes received. */
	u32 rx_bytes_hi;	/* iSCSI RX Bytes received. */
	u32 tx_pdus_lo;		/* iSCSI PDUs sent. */
	u32 tx_pdus_hi;		/* iSCSI PDUs sent. */
	u32 tx_bytes_lo;	/* iSCSI PDU TX Bytes sent. */
	u32 tx_bytes_hi;	/* iSCSI PDU TX Bytes sent. */
	u32 pcp_prior_map_tbl;	/* C-PCP to S-PCP Priority MapTable.
				 * 9 nibbles, the position of each nibble
				 * represents the C-PCP value, the value
				 * of the nibble = S-PCP value.
				 */
पूर्ण;

जोड़ drv_info_to_mcp अणु
	काष्ठा eth_stats_info	ether_stat;
	काष्ठा fcoe_stats_info	fcoe_stat;
	काष्ठा iscsi_stats_info	iscsi_stat;
पूर्ण;
#पूर्ण_अगर /* BNX2X_MFW_REQ_H */
