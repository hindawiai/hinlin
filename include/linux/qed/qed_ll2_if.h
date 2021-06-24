<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_LL2_IF_H
#घोषणा _QED_LL2_IF_H

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/qed_अगर.h>

क्रमागत qed_ll2_conn_type अणु
	QED_LL2_TYPE_FCOE,
	QED_LL2_TYPE_ISCSI,
	QED_LL2_TYPE_TEST,
	QED_LL2_TYPE_OOO,
	QED_LL2_TYPE_RESERVED2,
	QED_LL2_TYPE_ROCE,
	QED_LL2_TYPE_IWARP,
	QED_LL2_TYPE_RESERVED3,
	MAX_QED_LL2_CONN_TYPE
पूर्ण;

क्रमागत qed_ll2_rx_conn_type अणु
	QED_LL2_RX_TYPE_LEGACY,
	QED_LL2_RX_TYPE_CTX,
	MAX_QED_LL2_RX_CONN_TYPE
पूर्ण;

क्रमागत qed_ll2_roce_flavor_type अणु
	QED_LL2_ROCE,
	QED_LL2_RROCE,
	MAX_QED_LL2_ROCE_FLAVOR_TYPE
पूर्ण;

क्रमागत qed_ll2_tx_dest अणु
	QED_LL2_TX_DEST_NW, /* Light L2 TX Destination to the Network */
	QED_LL2_TX_DEST_LB, /* Light L2 TX Destination to the Loopback */
	QED_LL2_TX_DEST_DROP, /* Light L2 Drop the TX packet */
	QED_LL2_TX_DEST_MAX
पूर्ण;

क्रमागत qed_ll2_error_handle अणु
	QED_LL2_DROP_PACKET,
	QED_LL2_DO_NOTHING,
	QED_LL2_ASSERT,
पूर्ण;

काष्ठा qed_ll2_stats अणु
	u64 gsi_invalid_hdr;
	u64 gsi_invalid_pkt_length;
	u64 gsi_unsupported_pkt_typ;
	u64 gsi_crcchksm_error;

	u64 packet_too_big_discard;
	u64 no_buff_discard;

	u64 rcv_ucast_bytes;
	u64 rcv_mcast_bytes;
	u64 rcv_bcast_bytes;
	u64 rcv_ucast_pkts;
	u64 rcv_mcast_pkts;
	u64 rcv_bcast_pkts;

	u64 sent_ucast_bytes;
	u64 sent_mcast_bytes;
	u64 sent_bcast_bytes;
	u64 sent_ucast_pkts;
	u64 sent_mcast_pkts;
	u64 sent_bcast_pkts;
पूर्ण;

काष्ठा qed_ll2_comp_rx_data अणु
	व्योम *cookie;
	dma_addr_t rx_buf_addr;
	u16 parse_flags;
	u16 err_flags;
	u16 vlan;
	bool b_last_packet;
	u8 connection_handle;

	जोड़ अणु
		u16 packet_length;
		u16 data_length;
	पूर्ण length;

	u32 opaque_data_0;
	u32 opaque_data_1;

	/* GSI only */
	u32 src_qp;
	u16 qp_id;

	जोड़ अणु
		u8 placement_offset;
		u8 data_length_error;
	पूर्ण u;
पूर्ण;

प्रकार
व्योम (*qed_ll2_complete_rx_packet_cb)(व्योम *cxt,
				      काष्ठा qed_ll2_comp_rx_data *data);

प्रकार
व्योम (*qed_ll2_release_rx_packet_cb)(व्योम *cxt,
				     u8 connection_handle,
				     व्योम *cookie,
				     dma_addr_t rx_buf_addr,
				     bool b_last_packet);

प्रकार
व्योम (*qed_ll2_complete_tx_packet_cb)(व्योम *cxt,
				      u8 connection_handle,
				      व्योम *cookie,
				      dma_addr_t first_frag_addr,
				      bool b_last_fragment,
				      bool b_last_packet);

प्रकार
व्योम (*qed_ll2_release_tx_packet_cb)(व्योम *cxt,
				     u8 connection_handle,
				     व्योम *cookie,
				     dma_addr_t first_frag_addr,
				     bool b_last_fragment, bool b_last_packet);

प्रकार
व्योम (*qed_ll2_slowpath_cb)(व्योम *cxt, u8 connection_handle,
			    u32 opaque_data_0, u32 opaque_data_1);

काष्ठा qed_ll2_cbs अणु
	qed_ll2_complete_rx_packet_cb rx_comp_cb;
	qed_ll2_release_rx_packet_cb rx_release_cb;
	qed_ll2_complete_tx_packet_cb tx_comp_cb;
	qed_ll2_release_tx_packet_cb tx_release_cb;
	qed_ll2_slowpath_cb slowpath_cb;
	व्योम *cookie;
पूर्ण;

काष्ठा qed_ll2_acquire_data_inमाला_दो अणु
	क्रमागत qed_ll2_rx_conn_type rx_conn_type;
	क्रमागत qed_ll2_conn_type conn_type;
	u16 mtu;
	u16 rx_num_desc;
	u16 rx_num_ooo_buffers;
	u8 rx_drop_ttl0_flg;
	u8 rx_vlan_removal_en;
	u16 tx_num_desc;
	u8 tx_max_bds_per_packet;
	u8 tx_tc;
	क्रमागत qed_ll2_tx_dest tx_dest;
	क्रमागत qed_ll2_error_handle ai_err_packet_too_big;
	क्रमागत qed_ll2_error_handle ai_err_no_buf;
	bool secondary_queue;
	u8 gsi_enable;
पूर्ण;

काष्ठा qed_ll2_acquire_data अणु
	काष्ठा qed_ll2_acquire_data_inमाला_दो input;
	स्थिर काष्ठा qed_ll2_cbs *cbs;

	/* Output container क्रम LL2 connection's handle */
	u8 *p_connection_handle;
पूर्ण;

काष्ठा qed_ll2_tx_pkt_info अणु
	व्योम *cookie;
	dma_addr_t first_frag;
	क्रमागत qed_ll2_tx_dest tx_dest;
	क्रमागत qed_ll2_roce_flavor_type qed_roce_flavor;
	u16 vlan;
	u16 l4_hdr_offset_w;	/* from start of packet */
	u16 first_frag_len;
	u8 num_of_bds;
	u8 bd_flags;
	bool enable_ip_cksum;
	bool enable_l4_cksum;
	bool calc_ip_len;
	bool हटाओ_stag;
पूर्ण;

#घोषणा QED_LL2_UNUSED_HANDLE   (0xff)

काष्ठा qed_ll2_cb_ops अणु
	पूर्णांक (*rx_cb)(व्योम *, काष्ठा sk_buff *, u32, u32);
	पूर्णांक (*tx_cb)(व्योम *, काष्ठा sk_buff *, bool);
पूर्ण;

काष्ठा qed_ll2_params अणु
	u16 mtu;
	bool drop_ttl0_packets;
	bool rx_vlan_stripping;
	u8 tx_tc;
	bool frags_mapped;
	u8 ll2_mac_address[ETH_ALEN];
पूर्ण;

क्रमागत qed_ll2_xmit_flags अणु
	/* FIP discovery packet */
	QED_LL2_XMIT_FLAGS_FIP_DISCOVERY
पूर्ण;

काष्ठा qed_ll2_ops अणु
/**
 * @brief start - initializes ll2
 *
 * @param cdev
 * @param params - protocol driver configuration क्रम the ll2.
 *
 * @वापस 0 on success, otherwise error value.
 */
	पूर्णांक (*start)(काष्ठा qed_dev *cdev, काष्ठा qed_ll2_params *params);

/**
 * @brief stop - stops the ll2
 *
 * @param cdev
 *
 * @वापस 0 on success, otherwise error value.
 */
	पूर्णांक (*stop)(काष्ठा qed_dev *cdev);

/**
 * @brief start_xmit - transmits an skb over the ll2 पूर्णांकerface
 *
 * @param cdev
 * @param skb
 * @param xmit_flags - Transmit options defined by the क्रमागत qed_ll2_xmit_flags.
 *
 * @वापस 0 on success, otherwise error value.
 */
	पूर्णांक (*start_xmit)(काष्ठा qed_dev *cdev, काष्ठा sk_buff *skb,
			  अचिन्हित दीर्घ xmit_flags);

/**
 * @brief रेजिस्टर_cb_ops - protocol driver रेजिस्टर the callback क्रम Rx/Tx
 * packets. Should be called beक्रमe `start'.
 *
 * @param cdev
 * @param cookie - to be passed to the callback functions.
 * @param ops - the callback functions to रेजिस्टर क्रम Rx / Tx.
 *
 * @वापस 0 on success, otherwise error value.
 */
	व्योम (*रेजिस्टर_cb_ops)(काष्ठा qed_dev *cdev,
				स्थिर काष्ठा qed_ll2_cb_ops *ops,
				व्योम *cookie);

/**
 * @brief get LL2 related statistics
 *
 * @param cdev
 * @param stats - poपूर्णांकer to काष्ठा that would be filled with stats
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*get_stats)(काष्ठा qed_dev *cdev, काष्ठा qed_ll2_stats *stats);
पूर्ण;

#अगर_घोषित CONFIG_QED_LL2
पूर्णांक qed_ll2_alloc_अगर(काष्ठा qed_dev *);
व्योम qed_ll2_dealloc_अगर(काष्ठा qed_dev *);
#अन्यथा
अटल स्थिर काष्ठा qed_ll2_ops qed_ll2_ops_pass = अणु
	.start = शून्य,
	.stop = शून्य,
	.start_xmit = शून्य,
	.रेजिस्टर_cb_ops = शून्य,
	.get_stats = शून्य,
पूर्ण;

अटल अंतरभूत पूर्णांक qed_ll2_alloc_अगर(काष्ठा qed_dev *cdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qed_ll2_dealloc_अगर(काष्ठा qed_dev *cdev)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
