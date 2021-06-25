<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) 2017, Microsoft Corporation.
 *
 *   Author(s): Long Li <दीर्घli@microsoft.com>
 */
#अगर_अघोषित _SMBसूचीECT_H
#घोषणा _SMBसूचीECT_H

#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
#घोषणा cअगरs_rdma_enabled(server)	((server)->rdma)

#समावेश "cifsglob.h"
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <linux/mempool.h>

बाह्य पूर्णांक rdma_पढ़ोग_लिखो_threshold;
बाह्य पूर्णांक smbd_max_frmr_depth;
बाह्य पूर्णांक smbd_keep_alive_पूर्णांकerval;
बाह्य पूर्णांक smbd_max_receive_size;
बाह्य पूर्णांक smbd_max_fragmented_recv_size;
बाह्य पूर्णांक smbd_max_send_size;
बाह्य पूर्णांक smbd_send_credit_target;
बाह्य पूर्णांक smbd_receive_credit_max;

क्रमागत keep_alive_status अणु
	KEEP_ALIVE_NONE,
	KEEP_ALIVE_PENDING,
	KEEP_ALIVE_SENT,
पूर्ण;

क्रमागत smbd_connection_status अणु
	SMBD_CREATED,
	SMBD_CONNECTING,
	SMBD_CONNECTED,
	SMBD_NEGOTIATE_FAILED,
	SMBD_DISCONNECTING,
	SMBD_DISCONNECTED,
	SMBD_DESTROYED
पूर्ण;

/*
 * The context क्रम the SMBDirect transport
 * Everything related to the transport is here. It has several logical parts
 * 1. RDMA related काष्ठाures
 * 2. SMBDirect connection parameters
 * 3. Memory registrations
 * 4. Receive and reassembly queues क्रम data receive path
 * 5. mempools क्रम allocating packets
 */
काष्ठा smbd_connection अणु
	क्रमागत smbd_connection_status transport_status;

	/* RDMA related */
	काष्ठा rdma_cm_id *id;
	काष्ठा ib_qp_init_attr qp_attr;
	काष्ठा ib_pd *pd;
	काष्ठा ib_cq *send_cq, *recv_cq;
	काष्ठा ib_device_attr dev_attr;
	पूर्णांक ri_rc;
	काष्ठा completion ri_करोne;
	रुको_queue_head_t conn_रुको;
	रुको_queue_head_t disconn_रुको;

	काष्ठा completion negotiate_completion;
	bool negotiate_करोne;

	काष्ठा work_काष्ठा disconnect_work;
	काष्ठा work_काष्ठा post_send_credits_work;

	spinlock_t lock_new_credits_offered;
	पूर्णांक new_credits_offered;

	/* Connection parameters defined in [MS-SMBD] 3.1.1.1 */
	पूर्णांक receive_credit_max;
	पूर्णांक send_credit_target;
	पूर्णांक max_send_size;
	पूर्णांक max_fragmented_recv_size;
	पूर्णांक max_fragmented_send_size;
	पूर्णांक max_receive_size;
	पूर्णांक keep_alive_पूर्णांकerval;
	पूर्णांक max_पढ़ोग_लिखो_size;
	क्रमागत keep_alive_status keep_alive_requested;
	पूर्णांक protocol;
	atomic_t send_credits;
	atomic_t receive_credits;
	पूर्णांक receive_credit_target;
	पूर्णांक fragment_reassembly_reमुख्यing;

	/* Memory registrations */
	/* Maximum number of RDMA पढ़ो/ग_लिखो outstanding on this connection */
	पूर्णांक responder_resources;
	/* Maximum number of SGEs in a RDMA ग_लिखो/पढ़ो */
	पूर्णांक max_frmr_depth;
	/*
	 * If payload is less than or equal to the threshold,
	 * use RDMA send/recv to send upper layer I/O.
	 * If payload is more than the threshold,
	 * use RDMA पढ़ो/ग_लिखो through memory registration क्रम I/O.
	 */
	पूर्णांक rdma_पढ़ोग_लिखो_threshold;
	क्रमागत ib_mr_type mr_type;
	काष्ठा list_head mr_list;
	spinlock_t mr_list_lock;
	/* The number of available MRs पढ़ोy क्रम memory registration */
	atomic_t mr_पढ़ोy_count;
	atomic_t mr_used_count;
	रुको_queue_head_t रुको_mr;
	काष्ठा work_काष्ठा mr_recovery_work;
	/* Used by transport to रुको until all MRs are वापसed */
	रुको_queue_head_t रुको_क्रम_mr_cleanup;

	/* Activity accoutning */
	atomic_t send_pending;
	रुको_queue_head_t रुको_send_pending;
	रुको_queue_head_t रुको_post_send;

	/* Receive queue */
	काष्ठा list_head receive_queue;
	पूर्णांक count_receive_queue;
	spinlock_t receive_queue_lock;

	काष्ठा list_head empty_packet_queue;
	पूर्णांक count_empty_packet_queue;
	spinlock_t empty_packet_queue_lock;

	रुको_queue_head_t रुको_receive_queues;

	/* Reassembly queue */
	काष्ठा list_head reassembly_queue;
	spinlock_t reassembly_queue_lock;
	रुको_queue_head_t रुको_reassembly_queue;

	/* total data length of reassembly queue */
	पूर्णांक reassembly_data_length;
	पूर्णांक reassembly_queue_length;
	/* the offset to first buffer in reassembly queue */
	पूर्णांक first_entry_offset;

	bool send_immediate;

	रुको_queue_head_t रुको_send_queue;

	/*
	 * Indicate अगर we have received a full packet on the connection
	 * This is used to identअगरy the first SMBD packet of a assembled
	 * payload (SMB packet) in reassembly queue so we can वापस a
	 * RFC1002 length to upper layer to indicate the length of the SMB
	 * packet received
	 */
	bool full_packet_received;

	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा delayed_work idle_समयr_work;

	/* Memory pool क्रम pपुनः_स्मृतिating buffers */
	/* request pool क्रम RDMA send */
	काष्ठा kmem_cache *request_cache;
	mempool_t *request_mempool;

	/* response pool क्रम RDMA receive */
	काष्ठा kmem_cache *response_cache;
	mempool_t *response_mempool;

	/* क्रम debug purposes */
	अचिन्हित पूर्णांक count_get_receive_buffer;
	अचिन्हित पूर्णांक count_put_receive_buffer;
	अचिन्हित पूर्णांक count_reassembly_queue;
	अचिन्हित पूर्णांक count_enqueue_reassembly_queue;
	अचिन्हित पूर्णांक count_dequeue_reassembly_queue;
	अचिन्हित पूर्णांक count_send_empty;
पूर्ण;

क्रमागत smbd_message_type अणु
	SMBD_NEGOTIATE_RESP,
	SMBD_TRANSFER_DATA,
पूर्ण;

#घोषणा SMB_सूचीECT_RESPONSE_REQUESTED 0x0001

/* SMBD negotiation request packet [MS-SMBD] 2.2.1 */
काष्ठा smbd_negotiate_req अणु
	__le16 min_version;
	__le16 max_version;
	__le16 reserved;
	__le16 credits_requested;
	__le32 preferred_send_size;
	__le32 max_receive_size;
	__le32 max_fragmented_size;
पूर्ण __packed;

/* SMBD negotiation response packet [MS-SMBD] 2.2.2 */
काष्ठा smbd_negotiate_resp अणु
	__le16 min_version;
	__le16 max_version;
	__le16 negotiated_version;
	__le16 reserved;
	__le16 credits_requested;
	__le16 credits_granted;
	__le32 status;
	__le32 max_पढ़ोग_लिखो_size;
	__le32 preferred_send_size;
	__le32 max_receive_size;
	__le32 max_fragmented_size;
पूर्ण __packed;

/* SMBD data transfer packet with payload [MS-SMBD] 2.2.3 */
काष्ठा smbd_data_transfer अणु
	__le16 credits_requested;
	__le16 credits_granted;
	__le16 flags;
	__le16 reserved;
	__le32 reमुख्यing_data_length;
	__le32 data_offset;
	__le32 data_length;
	__le32 padding;
	__u8 buffer[];
पूर्ण __packed;

/* The packet fields क्रम a रेजिस्टरed RDMA buffer */
काष्ठा smbd_buffer_descriptor_v1 अणु
	__le64 offset;
	__le32 token;
	__le32 length;
पूर्ण __packed;

/* Default maximum number of SGEs in a RDMA send/recv */
#घोषणा SMBसूचीECT_MAX_SGE	16
/* The context क्रम a SMBD request */
काष्ठा smbd_request अणु
	काष्ठा smbd_connection *info;
	काष्ठा ib_cqe cqe;

	/* the SGE entries क्रम this packet */
	काष्ठा ib_sge sge[SMBसूचीECT_MAX_SGE];
	पूर्णांक num_sge;

	/* SMBD packet header follows this काष्ठाure */
	u8 packet[];
पूर्ण;

/* The context क्रम a SMBD response */
काष्ठा smbd_response अणु
	काष्ठा smbd_connection *info;
	काष्ठा ib_cqe cqe;
	काष्ठा ib_sge sge;

	क्रमागत smbd_message_type type;

	/* Link to receive queue or reassembly queue */
	काष्ठा list_head list;

	/* Indicate अगर this is the 1st packet of a payload */
	bool first_segment;

	/* SMBD packet header and payload follows this काष्ठाure */
	u8 packet[];
पूर्ण;

/* Create a SMBDirect session */
काष्ठा smbd_connection *smbd_get_connection(
	काष्ठा TCP_Server_Info *server, काष्ठा sockaddr *dstaddr);

/* Reconnect SMBDirect session */
पूर्णांक smbd_reconnect(काष्ठा TCP_Server_Info *server);
/* Destroy SMBDirect session */
व्योम smbd_destroy(काष्ठा TCP_Server_Info *server);

/* Interface क्रम carrying upper layer I/O through send/recv */
पूर्णांक smbd_recv(काष्ठा smbd_connection *info, काष्ठा msghdr *msg);
पूर्णांक smbd_send(काष्ठा TCP_Server_Info *server,
	पूर्णांक num_rqst, काष्ठा smb_rqst *rqst);

क्रमागत mr_state अणु
	MR_READY,
	MR_REGISTERED,
	MR_INVALIDATED,
	MR_ERROR
पूर्ण;

काष्ठा smbd_mr अणु
	काष्ठा smbd_connection	*conn;
	काष्ठा list_head	list;
	क्रमागत mr_state		state;
	काष्ठा ib_mr		*mr;
	काष्ठा scatterlist	*sgl;
	पूर्णांक			sgl_count;
	क्रमागत dma_data_direction	dir;
	जोड़ अणु
		काष्ठा ib_reg_wr	wr;
		काष्ठा ib_send_wr	inv_wr;
	पूर्ण;
	काष्ठा ib_cqe		cqe;
	bool			need_invalidate;
	काष्ठा completion	invalidate_करोne;
पूर्ण;

/* Interfaces to रेजिस्टर and deरेजिस्टर MR क्रम RDMA पढ़ो/ग_लिखो */
काष्ठा smbd_mr *smbd_रेजिस्टर_mr(
	काष्ठा smbd_connection *info, काष्ठा page *pages[], पूर्णांक num_pages,
	पूर्णांक offset, पूर्णांक tailsz, bool writing, bool need_invalidate);
पूर्णांक smbd_deरेजिस्टर_mr(काष्ठा smbd_mr *mr);

#अन्यथा
#घोषणा cअगरs_rdma_enabled(server)	0
काष्ठा smbd_connection अणुपूर्ण;
अटल अंतरभूत व्योम *smbd_get_connection(
	काष्ठा TCP_Server_Info *server, काष्ठा sockaddr *dstaddr) अणुवापस शून्य;पूर्ण
अटल अंतरभूत पूर्णांक smbd_reconnect(काष्ठा TCP_Server_Info *server) अणुवापस -1; पूर्ण
अटल अंतरभूत व्योम smbd_destroy(काष्ठा TCP_Server_Info *server) अणुपूर्ण
अटल अंतरभूत पूर्णांक smbd_recv(काष्ठा smbd_connection *info, काष्ठा msghdr *msg) अणुवापस -1; पूर्ण
अटल अंतरभूत पूर्णांक smbd_send(काष्ठा TCP_Server_Info *server, पूर्णांक num_rqst, काष्ठा smb_rqst *rqst) अणुवापस -1; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
