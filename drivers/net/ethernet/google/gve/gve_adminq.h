<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
 * Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#अगर_अघोषित _GVE_ADMINQ_H
#घोषणा _GVE_ADMINQ_H

#समावेश <linux/build_bug.h>

/* Admin queue opcodes */
क्रमागत gve_adminq_opcodes अणु
	GVE_ADMINQ_DESCRIBE_DEVICE		= 0x1,
	GVE_ADMINQ_CONFIGURE_DEVICE_RESOURCES	= 0x2,
	GVE_ADMINQ_REGISTER_PAGE_LIST		= 0x3,
	GVE_ADMINQ_UNREGISTER_PAGE_LIST		= 0x4,
	GVE_ADMINQ_CREATE_TX_QUEUE		= 0x5,
	GVE_ADMINQ_CREATE_RX_QUEUE		= 0x6,
	GVE_ADMINQ_DESTROY_TX_QUEUE		= 0x7,
	GVE_ADMINQ_DESTROY_RX_QUEUE		= 0x8,
	GVE_ADMINQ_DECONFIGURE_DEVICE_RESOURCES	= 0x9,
	GVE_ADMINQ_SET_DRIVER_PARAMETER		= 0xB,
	GVE_ADMINQ_REPORT_STATS			= 0xC,
	GVE_ADMINQ_REPORT_LINK_SPEED	= 0xD
पूर्ण;

/* Admin queue status codes */
क्रमागत gve_adminq_statuses अणु
	GVE_ADMINQ_COMMAND_UNSET			= 0x0,
	GVE_ADMINQ_COMMAND_PASSED			= 0x1,
	GVE_ADMINQ_COMMAND_ERROR_ABORTED		= 0xFFFFFFF0,
	GVE_ADMINQ_COMMAND_ERROR_ALREADY_EXISTS		= 0xFFFFFFF1,
	GVE_ADMINQ_COMMAND_ERROR_CANCELLED		= 0xFFFFFFF2,
	GVE_ADMINQ_COMMAND_ERROR_DATALOSS		= 0xFFFFFFF3,
	GVE_ADMINQ_COMMAND_ERROR_DEADLINE_EXCEEDED	= 0xFFFFFFF4,
	GVE_ADMINQ_COMMAND_ERROR_FAILED_PRECONDITION	= 0xFFFFFFF5,
	GVE_ADMINQ_COMMAND_ERROR_INTERNAL_ERROR		= 0xFFFFFFF6,
	GVE_ADMINQ_COMMAND_ERROR_INVALID_ARGUMENT	= 0xFFFFFFF7,
	GVE_ADMINQ_COMMAND_ERROR_NOT_FOUND		= 0xFFFFFFF8,
	GVE_ADMINQ_COMMAND_ERROR_OUT_OF_RANGE		= 0xFFFFFFF9,
	GVE_ADMINQ_COMMAND_ERROR_PERMISSION_DENIED	= 0xFFFFFFFA,
	GVE_ADMINQ_COMMAND_ERROR_UNAUTHENTICATED	= 0xFFFFFFFB,
	GVE_ADMINQ_COMMAND_ERROR_RESOURCE_EXHAUSTED	= 0xFFFFFFFC,
	GVE_ADMINQ_COMMAND_ERROR_UNAVAILABLE		= 0xFFFFFFFD,
	GVE_ADMINQ_COMMAND_ERROR_UNIMPLEMENTED		= 0xFFFFFFFE,
	GVE_ADMINQ_COMMAND_ERROR_UNKNOWN_ERROR		= 0xFFFFFFFF,
पूर्ण;

#घोषणा GVE_ADMINQ_DEVICE_DESCRIPTOR_VERSION 1

/* All AdminQ command काष्ठाs should be naturally packed. The अटल_निश्चित
 * calls make sure this is the हाल at compile समय.
 */

काष्ठा gve_adminq_describe_device अणु
	__be64 device_descriptor_addr;
	__be32 device_descriptor_version;
	__be32 available_length;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_describe_device) == 16);

काष्ठा gve_device_descriptor अणु
	__be64 max_रेजिस्टरed_pages;
	__be16 reserved1;
	__be16 tx_queue_entries;
	__be16 rx_queue_entries;
	__be16 शेष_num_queues;
	__be16 mtu;
	__be16 counters;
	__be16 tx_pages_per_qpl;
	__be16 rx_pages_per_qpl;
	u8  mac[ETH_ALEN];
	__be16 num_device_options;
	__be16 total_length;
	u8  reserved2[6];
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_device_descriptor) == 40);

काष्ठा gve_device_option अणु
	__be16 option_id;
	__be16 option_length;
	__be32 feat_mask;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_device_option) == 8);

#घोषणा GVE_DEV_OPT_ID_RAW_ADDRESSING 0x1
#घोषणा GVE_DEV_OPT_LEN_RAW_ADDRESSING 0x0
#घोषणा GVE_DEV_OPT_FEAT_MASK_RAW_ADDRESSING 0x0

काष्ठा gve_adminq_configure_device_resources अणु
	__be64 counter_array;
	__be64 irq_db_addr;
	__be32 num_counters;
	__be32 num_irq_dbs;
	__be32 irq_db_stride;
	__be32 ntfy_blk_msix_base_idx;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_configure_device_resources) == 32);

काष्ठा gve_adminq_रेजिस्टर_page_list अणु
	__be32 page_list_id;
	__be32 num_pages;
	__be64 page_address_list_addr;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_रेजिस्टर_page_list) == 16);

काष्ठा gve_adminq_unरेजिस्टर_page_list अणु
	__be32 page_list_id;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_unरेजिस्टर_page_list) == 4);

#घोषणा GVE_RAW_ADDRESSING_QPL_ID 0xFFFFFFFF

काष्ठा gve_adminq_create_tx_queue अणु
	__be32 queue_id;
	__be32 reserved;
	__be64 queue_resources_addr;
	__be64 tx_ring_addr;
	__be32 queue_page_list_id;
	__be32 ntfy_id;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_create_tx_queue) == 32);

काष्ठा gve_adminq_create_rx_queue अणु
	__be32 queue_id;
	__be32 index;
	__be32 reserved;
	__be32 ntfy_id;
	__be64 queue_resources_addr;
	__be64 rx_desc_ring_addr;
	__be64 rx_data_ring_addr;
	__be32 queue_page_list_id;
	u8 padding[4];
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_create_rx_queue) == 48);

/* Queue resources that are shared with the device */
काष्ठा gve_queue_resources अणु
	जोड़ अणु
		काष्ठा अणु
			__be32 db_index;	/* Device -> Guest */
			__be32 counter_index;	/* Device -> Guest */
		पूर्ण;
		u8 reserved[64];
	पूर्ण;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_queue_resources) == 64);

काष्ठा gve_adminq_destroy_tx_queue अणु
	__be32 queue_id;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_destroy_tx_queue) == 4);

काष्ठा gve_adminq_destroy_rx_queue अणु
	__be32 queue_id;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_destroy_rx_queue) == 4);

/* GVE Set Driver Parameter Types */
क्रमागत gve_set_driver_param_types अणु
	GVE_SET_PARAM_MTU	= 0x1,
पूर्ण;

काष्ठा gve_adminq_set_driver_parameter अणु
	__be32 parameter_type;
	u8 reserved[4];
	__be64 parameter_value;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_set_driver_parameter) == 16);

काष्ठा gve_adminq_report_stats अणु
	__be64 stats_report_len;
	__be64 stats_report_addr;
	__be64 पूर्णांकerval;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_report_stats) == 24);

काष्ठा gve_adminq_report_link_speed अणु
	__be64 link_speed_address;
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_adminq_report_link_speed) == 8);

काष्ठा stats अणु
	__be32 stat_name;
	__be32 queue_id;
	__be64 value;
पूर्ण;

अटल_निश्चित(माप(काष्ठा stats) == 16);

काष्ठा gve_stats_report अणु
	__be64 written_count;
	काष्ठा stats stats[];
पूर्ण;

अटल_निश्चित(माप(काष्ठा gve_stats_report) == 8);

क्रमागत gve_stat_names अणु
	// stats from gve
	TX_WAKE_CNT			= 1,
	TX_STOP_CNT			= 2,
	TX_FRAMES_SENT			= 3,
	TX_BYTES_SENT			= 4,
	TX_LAST_COMPLETION_PROCESSED	= 5,
	RX_NEXT_EXPECTED_SEQUENCE	= 6,
	RX_BUFFERS_POSTED		= 7,
	// stats from NIC
	RX_QUEUE_DROP_CNT		= 65,
	RX_NO_BUFFERS_POSTED		= 66,
	RX_DROPS_PACKET_OVER_MRU	= 67,
	RX_DROPS_INVALID_CHECKSUM	= 68,
पूर्ण;

जोड़ gve_adminq_command अणु
	काष्ठा अणु
		__be32 opcode;
		__be32 status;
		जोड़ अणु
			काष्ठा gve_adminq_configure_device_resources
						configure_device_resources;
			काष्ठा gve_adminq_create_tx_queue create_tx_queue;
			काष्ठा gve_adminq_create_rx_queue create_rx_queue;
			काष्ठा gve_adminq_destroy_tx_queue destroy_tx_queue;
			काष्ठा gve_adminq_destroy_rx_queue destroy_rx_queue;
			काष्ठा gve_adminq_describe_device describe_device;
			काष्ठा gve_adminq_रेजिस्टर_page_list reg_page_list;
			काष्ठा gve_adminq_unरेजिस्टर_page_list unreg_page_list;
			काष्ठा gve_adminq_set_driver_parameter set_driver_param;
			काष्ठा gve_adminq_report_stats report_stats;
			काष्ठा gve_adminq_report_link_speed report_link_speed;
		पूर्ण;
	पूर्ण;
	u8 reserved[64];
पूर्ण;

अटल_निश्चित(माप(जोड़ gve_adminq_command) == 64);

पूर्णांक gve_adminq_alloc(काष्ठा device *dev, काष्ठा gve_priv *priv);
व्योम gve_adminq_मुक्त(काष्ठा device *dev, काष्ठा gve_priv *priv);
व्योम gve_adminq_release(काष्ठा gve_priv *priv);
पूर्णांक gve_adminq_describe_device(काष्ठा gve_priv *priv);
पूर्णांक gve_adminq_configure_device_resources(काष्ठा gve_priv *priv,
					  dma_addr_t counter_array_bus_addr,
					  u32 num_counters,
					  dma_addr_t db_array_bus_addr,
					  u32 num_ntfy_blks);
पूर्णांक gve_adminq_deconfigure_device_resources(काष्ठा gve_priv *priv);
पूर्णांक gve_adminq_create_tx_queues(काष्ठा gve_priv *priv, u32 num_queues);
पूर्णांक gve_adminq_destroy_tx_queues(काष्ठा gve_priv *priv, u32 queue_id);
पूर्णांक gve_adminq_create_rx_queues(काष्ठा gve_priv *priv, u32 num_queues);
पूर्णांक gve_adminq_destroy_rx_queues(काष्ठा gve_priv *priv, u32 queue_id);
पूर्णांक gve_adminq_रेजिस्टर_page_list(काष्ठा gve_priv *priv,
				  काष्ठा gve_queue_page_list *qpl);
पूर्णांक gve_adminq_unरेजिस्टर_page_list(काष्ठा gve_priv *priv, u32 page_list_id);
पूर्णांक gve_adminq_set_mtu(काष्ठा gve_priv *priv, u64 mtu);
पूर्णांक gve_adminq_report_stats(काष्ठा gve_priv *priv, u64 stats_report_len,
			    dma_addr_t stats_report_addr, u64 पूर्णांकerval);
पूर्णांक gve_adminq_report_link_speed(काष्ठा gve_priv *priv);
#पूर्ण_अगर /* _GVE_ADMINQ_H */
