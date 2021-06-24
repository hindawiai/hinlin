<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_SP_H
#घोषणा _QED_SP_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश "qed.h"
#समावेश "qed_hsi.h"

क्रमागत spq_mode अणु
	QED_SPQ_MODE_BLOCK,     /* Client will poll a designated mem. address */
	QED_SPQ_MODE_CB,        /* Client supplies a callback */
	QED_SPQ_MODE_EBLOCK,    /* QED should block until completion */
पूर्ण;

काष्ठा qed_spq_comp_cb अणु
	व्योम	(*function)(काष्ठा qed_hwfn *,
			    व्योम *,
			    जोड़ event_ring_data *,
			    u8 fw_वापस_code);
	व्योम	*cookie;
पूर्ण;

/**
 * @brief qed_eth_cqe_completion - handles the completion of a
 *        ramrod on the cqe ring
 *
 * @param p_hwfn
 * @param cqe
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_eth_cqe_completion(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा eth_slow_path_rx_cqe *cqe);

/**
 *  @file
 *
 *  QED Slow-hwfn queue पूर्णांकerface
 */

जोड़ ramrod_data अणु
	काष्ठा pf_start_ramrod_data pf_start;
	काष्ठा pf_update_ramrod_data pf_update;
	काष्ठा rx_queue_start_ramrod_data rx_queue_start;
	काष्ठा rx_queue_update_ramrod_data rx_queue_update;
	काष्ठा rx_queue_stop_ramrod_data rx_queue_stop;
	काष्ठा tx_queue_start_ramrod_data tx_queue_start;
	काष्ठा tx_queue_stop_ramrod_data tx_queue_stop;
	काष्ठा vport_start_ramrod_data vport_start;
	काष्ठा vport_stop_ramrod_data vport_stop;
	काष्ठा rx_update_gft_filter_data rx_update_gft;
	काष्ठा vport_update_ramrod_data vport_update;
	काष्ठा core_rx_start_ramrod_data core_rx_queue_start;
	काष्ठा core_rx_stop_ramrod_data core_rx_queue_stop;
	काष्ठा core_tx_start_ramrod_data core_tx_queue_start;
	काष्ठा core_tx_stop_ramrod_data core_tx_queue_stop;
	काष्ठा vport_filter_update_ramrod_data vport_filter_update;

	काष्ठा rdma_init_func_ramrod_data rdma_init_func;
	काष्ठा rdma_बंद_func_ramrod_data rdma_बंद_func;
	काष्ठा rdma_रेजिस्टर_tid_ramrod_data rdma_रेजिस्टर_tid;
	काष्ठा rdma_deरेजिस्टर_tid_ramrod_data rdma_deरेजिस्टर_tid;
	काष्ठा roce_create_qp_resp_ramrod_data roce_create_qp_resp;
	काष्ठा roce_create_qp_req_ramrod_data roce_create_qp_req;
	काष्ठा roce_modअगरy_qp_resp_ramrod_data roce_modअगरy_qp_resp;
	काष्ठा roce_modअगरy_qp_req_ramrod_data roce_modअगरy_qp_req;
	काष्ठा roce_query_qp_resp_ramrod_data roce_query_qp_resp;
	काष्ठा roce_query_qp_req_ramrod_data roce_query_qp_req;
	काष्ठा roce_destroy_qp_resp_ramrod_data roce_destroy_qp_resp;
	काष्ठा roce_destroy_qp_req_ramrod_data roce_destroy_qp_req;
	काष्ठा roce_init_func_ramrod_data roce_init_func;
	काष्ठा rdma_create_cq_ramrod_data rdma_create_cq;
	काष्ठा rdma_destroy_cq_ramrod_data rdma_destroy_cq;
	काष्ठा rdma_srq_create_ramrod_data rdma_create_srq;
	काष्ठा rdma_srq_destroy_ramrod_data rdma_destroy_srq;
	काष्ठा rdma_srq_modअगरy_ramrod_data rdma_modअगरy_srq;
	काष्ठा iwarp_create_qp_ramrod_data iwarp_create_qp;
	काष्ठा iwarp_tcp_offload_ramrod_data iwarp_tcp_offload;
	काष्ठा iwarp_mpa_offload_ramrod_data iwarp_mpa_offload;
	काष्ठा iwarp_modअगरy_qp_ramrod_data iwarp_modअगरy_qp;
	काष्ठा iwarp_init_func_ramrod_data iwarp_init_func;
	काष्ठा fcoe_init_ramrod_params fcoe_init;
	काष्ठा fcoe_conn_offload_ramrod_params fcoe_conn_ofld;
	काष्ठा fcoe_conn_terminate_ramrod_params fcoe_conn_terminate;
	काष्ठा fcoe_stat_ramrod_params fcoe_stat;

	काष्ठा iscsi_init_ramrod_params iscsi_init;
	काष्ठा iscsi_spe_conn_offload iscsi_conn_offload;
	काष्ठा iscsi_conn_update_ramrod_params iscsi_conn_update;
	काष्ठा iscsi_spe_conn_mac_update iscsi_conn_mac_update;
	काष्ठा iscsi_spe_conn_termination iscsi_conn_terminate;

	काष्ठा vf_start_ramrod_data vf_start;
	काष्ठा vf_stop_ramrod_data vf_stop;
पूर्ण;

#घोषणा EQ_MAX_CREDIT   0xffffffff

क्रमागत spq_priority अणु
	QED_SPQ_PRIORITY_NORMAL,
	QED_SPQ_PRIORITY_HIGH,
पूर्ण;

जोड़ qed_spq_req_comp अणु
	काष्ठा qed_spq_comp_cb	cb;
	u64			*करोne_addr;
पूर्ण;

काष्ठा qed_spq_comp_करोne अणु
	अचिन्हित पूर्णांक	करोne;
	u8		fw_वापस_code;
पूर्ण;

काष्ठा qed_spq_entry अणु
	काष्ठा list_head		list;

	u8				flags;

	/* HSI slow path element */
	काष्ठा slow_path_element	elem;

	जोड़ ramrod_data		ramrod;

	क्रमागत spq_priority		priority;

	/* pending queue क्रम this entry */
	काष्ठा list_head		*queue;

	क्रमागत spq_mode			comp_mode;
	काष्ठा qed_spq_comp_cb		comp_cb;
	काष्ठा qed_spq_comp_करोne	comp_करोne; /* SPQ_MODE_EBLOCK */

	/* Posted entry क्रम unlimited list entry in EBLOCK mode */
	काष्ठा qed_spq_entry		*post_ent;
पूर्ण;

काष्ठा qed_eq अणु
	काष्ठा qed_chain	chain;
	u8			eq_sb_index;    /* index within the SB */
	__le16			*p_fw_cons;     /* ptr to index value */
पूर्ण;

काष्ठा qed_consq अणु
	काष्ठा qed_chain chain;
पूर्ण;

प्रकार पूर्णांक (*qed_spq_async_comp_cb)(काष्ठा qed_hwfn *p_hwfn, u8 opcode,
				     __le16 echo, जोड़ event_ring_data *data,
				     u8 fw_वापस_code);

पूर्णांक
qed_spq_रेजिस्टर_async_cb(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत protocol_type protocol_id,
			  qed_spq_async_comp_cb cb);

व्योम
qed_spq_unरेजिस्टर_async_cb(काष्ठा qed_hwfn *p_hwfn,
			    क्रमागत protocol_type protocol_id);

काष्ठा qed_spq अणु
	spinlock_t		lock; /* SPQ lock */

	काष्ठा list_head	unlimited_pending;
	काष्ठा list_head	pending;
	काष्ठा list_head	completion_pending;
	काष्ठा list_head	मुक्त_pool;

	काष्ठा qed_chain	chain;

	/* allocated dma-able memory क्रम spq entries (+ramrod data) */
	dma_addr_t		p_phys;
	काष्ठा qed_spq_entry	*p_virt;

#घोषणा SPQ_RING_SIZE \
	(CORE_SPQE_PAGE_SIZE_BYTES / माप(काष्ठा slow_path_element))

	/* Biपंचांगap क्रम handling out-of-order completions */
	DECLARE_BITMAP(p_comp_biपंचांगap, SPQ_RING_SIZE);
	u8			comp_biपंचांगap_idx;

	/* Statistics */
	u32			unlimited_pending_count;
	u32			normal_count;
	u32			high_count;
	u32			comp_sent_count;
	u32			comp_count;

	u32			cid;
	u32			db_addr_offset;
	काष्ठा core_db_data	db_data;
	qed_spq_async_comp_cb	async_comp_cb[MAX_PROTOCOL_TYPE];
पूर्ण;

/**
 * @brief qed_spq_post - Posts a Slow hwfn request to FW, or lacking that
 *        Pends it to the future list.
 *
 * @param p_hwfn
 * @param p_req
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_spq_post(काष्ठा qed_hwfn *p_hwfn,
		 काष्ठा qed_spq_entry *p_ent,
		 u8 *fw_वापस_code);

/**
 * @brief qed_spq_allocate - Alloocates & initializes the SPQ and EQ.
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_spq_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_spq_setup - Reset the SPQ to its start state.
 *
 * @param p_hwfn
 */
व्योम qed_spq_setup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_spq_deallocate - Deallocates the given SPQ काष्ठा.
 *
 * @param p_hwfn
 */
व्योम qed_spq_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_spq_get_entry - Obtain an entrry from the spq
 *        मुक्त pool list.
 *
 *
 *
 * @param p_hwfn
 * @param pp_ent
 *
 * @वापस पूर्णांक
 */
पूर्णांक
qed_spq_get_entry(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_spq_entry **pp_ent);

/**
 * @brief qed_spq_वापस_entry - Return an entry to spq मुक्त
 *                                 pool list
 *
 * @param p_hwfn
 * @param p_ent
 */
व्योम qed_spq_वापस_entry(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_spq_entry *p_ent);
/**
 * @brief qed_eq_allocate - Allocates & initializes an EQ काष्ठा
 *
 * @param p_hwfn
 * @param num_elem number of elements in the eq
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_eq_alloc(काष्ठा qed_hwfn *p_hwfn, u16 num_elem);

/**
 * @brief qed_eq_setup - Reset the EQ to its start state.
 *
 * @param p_hwfn
 */
व्योम qed_eq_setup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_eq_मुक्त - deallocates the given EQ काष्ठा.
 *
 * @param p_hwfn
 */
व्योम qed_eq_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_eq_prod_update - update the FW with शेष EQ producer
 *
 * @param p_hwfn
 * @param prod
 */
व्योम qed_eq_prod_update(काष्ठा qed_hwfn *p_hwfn,
			u16 prod);

/**
 * @brief qed_eq_completion - Completes currently pending EQ elements
 *
 * @param p_hwfn
 * @param cookie
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_eq_completion(काष्ठा qed_hwfn *p_hwfn,
		      व्योम *cookie);

/**
 * @brief qed_spq_completion - Completes a single event
 *
 * @param p_hwfn
 * @param echo - echo value from cookie (used क्रम determining completion)
 * @param p_data - data from cookie (used in callback function अगर applicable)
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_spq_completion(काष्ठा qed_hwfn *p_hwfn,
		       __le16 echo,
		       u8 fw_वापस_code,
		       जोड़ event_ring_data *p_data);

/**
 * @brief qed_spq_get_cid - Given p_hwfn, वापस cid क्रम the hwfn's SPQ
 *
 * @param p_hwfn
 *
 * @वापस u32 - SPQ CID
 */
u32 qed_spq_get_cid(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_consq_alloc - Allocates & initializes an ConsQ
 *        काष्ठा
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_consq_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_consq_setup - Reset the ConsQ to its start state.
 *
 * @param p_hwfn
 */
व्योम qed_consq_setup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_consq_मुक्त - deallocates the given ConsQ काष्ठा.
 *
 * @param p_hwfn
 */
व्योम qed_consq_मुक्त(काष्ठा qed_hwfn *p_hwfn);
पूर्णांक qed_spq_pend_post(काष्ठा qed_hwfn *p_hwfn);

/**
 * @file
 *
 * @brief Slow-hwfn low-level commands (Ramrods) function definitions.
 */

#घोषणा QED_SP_EQ_COMPLETION  0x01
#घोषणा QED_SP_CQE_COMPLETION 0x02

काष्ठा qed_sp_init_data अणु
	u32			cid;
	u16			opaque_fid;

	/* Inक्रमmation regarding operation upon sending & completion */
	क्रमागत spq_mode		comp_mode;
	काष्ठा qed_spq_comp_cb *p_comp_data;
पूर्ण;

/**
 * @brief Returns a SPQ entry to the pool / मुक्तs the entry अगर allocated.
 *        Should be called on in error flows after initializing the SPQ entry
 *        and beक्रमe posting it.
 *
 * @param p_hwfn
 * @param p_ent
 */
व्योम qed_sp_destroy_request(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_spq_entry *p_ent);

पूर्णांक qed_sp_init_request(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_spq_entry **pp_ent,
			u8 cmd,
			u8 protocol,
			काष्ठा qed_sp_init_data *p_data);

/**
 * @brief qed_sp_pf_start - PF Function Start Ramrod
 *
 * This ramrod is sent to initialize a physical function (PF). It will
 * configure the function related parameters and ग_लिखो its completion to the
 * event ring specअगरied in the parameters.
 *
 * Ramrods complete on the common event ring क्रम the PF. This ring is
 * allocated by the driver on host memory and its parameters are written
 * to the पूर्णांकernal RAM of the UStorm by the Function Start Ramrod.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_tunn
 * @param allow_npar_tx_चयन
 *
 * @वापस पूर्णांक
 */

पूर्णांक qed_sp_pf_start(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_tunnel_info *p_tunn,
		    bool allow_npar_tx_चयन);

/**
 * @brief qed_sp_pf_update - PF Function Update Ramrod
 *
 * This ramrod updates function-related parameters. Every parameter can be
 * updated independently, according to configuration flags.
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */

पूर्णांक qed_sp_pf_update(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_sp_pf_update_stag - Update firmware of new outer tag
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_sp_pf_update_stag(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_sp_pf_stop - PF Function Stop Ramrod
 *
 * This ramrod is sent to बंद a Physical Function (PF). It is the last ramrod
 * sent and the last completion written to the PFs Event Ring. This ramrod also
 * deletes the context क्रम the Slowhwfn connection on this PF.
 *
 * @note Not required क्रम first packet.
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */

/**
 * @brief qed_sp_pf_update_ufp - PF ufp update Ramrod
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_sp_pf_update_ufp(काष्ठा qed_hwfn *p_hwfn);

पूर्णांक qed_sp_pf_stop(काष्ठा qed_hwfn *p_hwfn);

पूर्णांक qed_sp_pf_update_tunn_cfg(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      काष्ठा qed_tunnel_info *p_tunn,
			      क्रमागत spq_mode comp_mode,
			      काष्ठा qed_spq_comp_cb *p_comp_data);
/**
 * @brief qed_sp_heartbeat_ramrod - Send empty Ramrod
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */

पूर्णांक qed_sp_heartbeat_ramrod(काष्ठा qed_hwfn *p_hwfn);

#पूर्ण_अगर
