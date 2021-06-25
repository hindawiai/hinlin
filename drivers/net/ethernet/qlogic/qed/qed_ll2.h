<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_LL2_H
#घोषणा _QED_LL2_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/qed/qed_ll2_अगर.h>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_sp.h"

#घोषणा QED_MAX_NUM_OF_LL2_CONNECTIONS                    (4)
/* LL2 queues handles will be split as follows:
 * first will be legacy queues, and then the ctx based queues.
 */
#घोषणा QED_MAX_NUM_OF_LL2_CONNS_PF            (4)
#घोषणा QED_MAX_NUM_OF_LEGACY_LL2_CONNS_PF   (3)

#घोषणा QED_MAX_NUM_OF_CTX_LL2_CONNS_PF	\
	(QED_MAX_NUM_OF_LL2_CONNS_PF - QED_MAX_NUM_OF_LEGACY_LL2_CONNS_PF)

#घोषणा QED_LL2_LEGACY_CONN_BASE_PF     0
#घोषणा QED_LL2_CTX_CONN_BASE_PF        QED_MAX_NUM_OF_LEGACY_LL2_CONNS_PF


काष्ठा qed_ll2_rx_packet अणु
	काष्ठा list_head list_entry;
	काष्ठा core_rx_bd_with_buff_len *rxq_bd;
	dma_addr_t rx_buf_addr;
	u16 buf_length;
	व्योम *cookie;
	u8 placement_offset;
	u16 parse_flags;
	u16 packet_length;
	u16 vlan;
	u32 opaque_data[2];
पूर्ण;

काष्ठा qed_ll2_tx_packet अणु
	काष्ठा list_head list_entry;
	u16 bd_used;
	bool notअगरy_fw;
	व्योम *cookie;
	/* Flexible Array of bds_set determined by max_bds_per_packet */
	काष्ठा अणु
		काष्ठा core_tx_bd *txq_bd;
		dma_addr_t tx_frag;
		u16 frag_len;
	पूर्ण bds_set[];
पूर्ण;

काष्ठा qed_ll2_rx_queue अणु
	/* Lock protecting the Rx queue manipulation */
	spinlock_t lock;
	काष्ठा qed_chain rxq_chain;
	काष्ठा qed_chain rcq_chain;
	u8 rx_sb_index;
	u8 ctx_based;
	bool b_cb_रेजिस्टरed;
	__le16 *p_fw_cons;
	काष्ठा list_head active_descq;
	काष्ठा list_head मुक्त_descq;
	काष्ठा list_head posting_descq;
	काष्ठा qed_ll2_rx_packet *descq_array;
	व्योम __iomem *set_prod_addr;
	काष्ठा core_pwm_prod_update_data db_data;
पूर्ण;

काष्ठा qed_ll2_tx_queue अणु
	/* Lock protecting the Tx queue manipulation */
	spinlock_t lock;
	काष्ठा qed_chain txq_chain;
	u8 tx_sb_index;
	bool b_cb_रेजिस्टरed;
	__le16 *p_fw_cons;
	काष्ठा list_head active_descq;
	काष्ठा list_head मुक्त_descq;
	काष्ठा list_head sending_descq;
	u16 cur_completing_bd_idx;
	व्योम __iomem *करोorbell_addr;
	काष्ठा core_db_data db_msg;
	u16 bds_idx;
	u16 cur_send_frag_num;
	u16 cur_completing_frag_num;
	bool b_completing_packet;
	व्योम *descq_mem; /* memory क्रम variable sized qed_ll2_tx_packet*/
	काष्ठा qed_ll2_tx_packet *cur_send_packet;
	काष्ठा qed_ll2_tx_packet cur_completing_packet;
पूर्ण;

काष्ठा qed_ll2_info अणु
	/* Lock protecting the state of LL2 */
	काष्ठा mutex mutex;

	काष्ठा qed_ll2_acquire_data_inमाला_दो input;
	u32 cid;
	u8 my_id;
	u8 queue_id;
	u8 tx_stats_id;
	bool b_active;
	क्रमागत core_tx_dest tx_dest;
	u8 tx_stats_en;
	bool मुख्य_func_queue;
	काष्ठा qed_ll2_rx_queue rx_queue;
	काष्ठा qed_ll2_tx_queue tx_queue;
	काष्ठा qed_ll2_cbs cbs;
पूर्ण;

बाह्य स्थिर काष्ठा qed_ll2_ops qed_ll2_ops_pass;

/**
 * @brief qed_ll2_acquire_connection - allocate resources,
 *        starts rx & tx (अगर relevant) queues pair. Provides
 *        connecion handler as output parameter.
 *
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param data - describes connection parameters
 * @वापस पूर्णांक
 */
पूर्णांक qed_ll2_acquire_connection(व्योम *cxt, काष्ठा qed_ll2_acquire_data *data);

/**
 * @brief qed_ll2_establish_connection - start previously
 *        allocated LL2 queues pair
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param p_ptt
 * @param connection_handle	LL2 connection's handle obtained from
 *                              qed_ll2_require_connection
 *
 * @वापस 0 on success, failure otherwise
 */
पूर्णांक qed_ll2_establish_connection(व्योम *cxt, u8 connection_handle);

/**
 * @brief qed_ll2_post_rx_buffers - submit buffers to LL2 Rx queue.
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param connection_handle	LL2 connection's handle obtained from
 *				qed_ll2_require_connection
 * @param addr			rx (physical address) buffers to submit
 * @param cookie
 * @param notअगरy_fw		produce corresponding Rx BD immediately
 *
 * @वापस 0 on success, failure otherwise
 */
पूर्णांक qed_ll2_post_rx_buffer(व्योम *cxt,
			   u8 connection_handle,
			   dma_addr_t addr,
			   u16 buf_len, व्योम *cookie, u8 notअगरy_fw);

/**
 * @brief qed_ll2_prepare_tx_packet - request क्रम start Tx BD
 *				      to prepare Tx packet submission to FW.
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param connection_handle
 * @param pkt - info regarding the tx packet
 * @param notअगरy_fw - issue करोorbell to fw क्रम this packet
 *
 * @वापस 0 on success, failure otherwise
 */
पूर्णांक qed_ll2_prepare_tx_packet(व्योम *cxt,
			      u8 connection_handle,
			      काष्ठा qed_ll2_tx_pkt_info *pkt,
			      bool notअगरy_fw);

/**
 * @brief qed_ll2_release_connection -	releases resources
 *					allocated क्रम LL2 connection
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param connection_handle		LL2 connection's handle obtained from
 *					qed_ll2_require_connection
 */
व्योम qed_ll2_release_connection(व्योम *cxt, u8 connection_handle);

/**
 * @brief qed_ll2_set_fragment_of_tx_packet -	provides fragments to fill
 *						Tx BD of BDs requested by
 *						qed_ll2_prepare_tx_packet
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param connection_handle			LL2 connection's handle
 *						obtained from
 *						qed_ll2_require_connection
 * @param addr
 * @param nbytes
 *
 * @वापस 0 on success, failure otherwise
 */
पूर्णांक qed_ll2_set_fragment_of_tx_packet(व्योम *cxt,
				      u8 connection_handle,
				      dma_addr_t addr, u16 nbytes);

/**
 * @brief qed_ll2_terminate_connection -	stops Tx/Rx queues
 *
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param connection_handle			LL2 connection's handle
 *						obtained from
 *						qed_ll2_require_connection
 *
 * @वापस 0 on success, failure otherwise
 */
पूर्णांक qed_ll2_terminate_connection(व्योम *cxt, u8 connection_handle);

/**
 * @brief qed_ll2_get_stats -	get LL2 queue's statistics
 *
 *
 * @param cxt - poपूर्णांकer to the hw-function [opaque to some]
 * @param connection_handle	LL2 connection's handle obtained from
 *				qed_ll2_require_connection
 * @param p_stats
 *
 * @वापस 0 on success, failure otherwise
 */
पूर्णांक qed_ll2_get_stats(व्योम *cxt,
		      u8 connection_handle, काष्ठा qed_ll2_stats *p_stats);

/**
 * @brief qed_ll2_alloc - Allocates LL2 connections set
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_ll2_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ll2_setup - Inits LL2 connections set
 *
 * @param p_hwfn
 *
 */
व्योम qed_ll2_setup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ll2_मुक्त - Releases LL2 connections set
 *
 * @param p_hwfn
 *
 */
व्योम qed_ll2_मुक्त(काष्ठा qed_hwfn *p_hwfn);

#पूर्ण_अगर
