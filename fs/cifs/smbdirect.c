<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) 2017, Microsoft Corporation.
 *
 *   Author(s): Long Li <दीर्घli@microsoft.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश "smbdirect.h"
#समावेश "cifs_debug.h"
#समावेश "cifsproto.h"
#समावेश "smb2proto.h"

अटल काष्ठा smbd_response *get_empty_queue_buffer(
		काष्ठा smbd_connection *info);
अटल काष्ठा smbd_response *get_receive_buffer(
		काष्ठा smbd_connection *info);
अटल व्योम put_receive_buffer(
		काष्ठा smbd_connection *info,
		काष्ठा smbd_response *response);
अटल पूर्णांक allocate_receive_buffers(काष्ठा smbd_connection *info, पूर्णांक num_buf);
अटल व्योम destroy_receive_buffers(काष्ठा smbd_connection *info);

अटल व्योम put_empty_packet(
		काष्ठा smbd_connection *info, काष्ठा smbd_response *response);
अटल व्योम enqueue_reassembly(
		काष्ठा smbd_connection *info,
		काष्ठा smbd_response *response, पूर्णांक data_length);
अटल काष्ठा smbd_response *_get_first_reassembly(
		काष्ठा smbd_connection *info);

अटल पूर्णांक smbd_post_recv(
		काष्ठा smbd_connection *info,
		काष्ठा smbd_response *response);

अटल पूर्णांक smbd_post_send_empty(काष्ठा smbd_connection *info);
अटल पूर्णांक smbd_post_send_data(
		काष्ठा smbd_connection *info,
		काष्ठा kvec *iov, पूर्णांक n_vec, पूर्णांक reमुख्यing_data_length);
अटल पूर्णांक smbd_post_send_page(काष्ठा smbd_connection *info,
		काष्ठा page *page, अचिन्हित दीर्घ offset,
		माप_प्रकार size, पूर्णांक reमुख्यing_data_length);

अटल व्योम destroy_mr_list(काष्ठा smbd_connection *info);
अटल पूर्णांक allocate_mr_list(काष्ठा smbd_connection *info);

/* SMBD version number */
#घोषणा SMBD_V1	0x0100

/* Port numbers क्रम SMBD transport */
#घोषणा SMB_PORT	445
#घोषणा SMBD_PORT	5445

/* Address lookup and resolve समयout in ms */
#घोषणा RDMA_RESOLVE_TIMEOUT	5000

/* SMBD negotiation समयout in seconds */
#घोषणा SMBD_NEGOTIATE_TIMEOUT	120

/* SMBD minimum receive size and fragmented sized defined in [MS-SMBD] */
#घोषणा SMBD_MIN_RECEIVE_SIZE		128
#घोषणा SMBD_MIN_FRAGMENTED_SIZE	131072

/*
 * Default maximum number of RDMA पढ़ो/ग_लिखो outstanding on this connection
 * This value is possibly decreased during QP creation on hardware limit
 */
#घोषणा SMBD_CM_RESPONDER_RESOURCES	32

/* Maximum number of retries on data transfer operations */
#घोषणा SMBD_CM_RETRY			6
/* No need to retry on Receiver Not Ready since SMBD manages credits */
#घोषणा SMBD_CM_RNR_RETRY		0

/*
 * User configurable initial values per SMBD transport connection
 * as defined in [MS-SMBD] 3.1.1.1
 * Those may change after a SMBD negotiation
 */
/* The local peer's maximum number of credits to grant to the peer */
पूर्णांक smbd_receive_credit_max = 255;

/* The remote peer's credit request of local peer */
पूर्णांक smbd_send_credit_target = 255;

/* The maximum single message size can be sent to remote peer */
पूर्णांक smbd_max_send_size = 1364;

/*  The maximum fragmented upper-layer payload receive size supported */
पूर्णांक smbd_max_fragmented_recv_size = 1024 * 1024;

/*  The maximum single-message size which can be received */
पूर्णांक smbd_max_receive_size = 8192;

/* The समयout to initiate send of a keepalive message on idle */
पूर्णांक smbd_keep_alive_पूर्णांकerval = 120;

/*
 * User configurable initial values क्रम RDMA transport
 * The actual values used may be lower and are limited to hardware capabilities
 */
/* Default maximum number of SGEs in a RDMA ग_लिखो/पढ़ो */
पूर्णांक smbd_max_frmr_depth = 2048;

/* If payload is less than this byte, use RDMA send/recv not पढ़ो/ग_लिखो */
पूर्णांक rdma_पढ़ोग_लिखो_threshold = 4096;

/* Transport logging functions
 * Logging are defined as classes. They can be OR'ed to define the actual
 * logging level via module parameter smbd_logging_class
 * e.g. cअगरs.smbd_logging_class=0xa0 will log all log_rdma_recv() and
 * log_rdma_event()
 */
#घोषणा LOG_OUTGOING			0x1
#घोषणा LOG_INCOMING			0x2
#घोषणा LOG_READ			0x4
#घोषणा LOG_WRITE			0x8
#घोषणा LOG_RDMA_SEND			0x10
#घोषणा LOG_RDMA_RECV			0x20
#घोषणा LOG_KEEP_ALIVE			0x40
#घोषणा LOG_RDMA_EVENT			0x80
#घोषणा LOG_RDMA_MR			0x100
अटल अचिन्हित पूर्णांक smbd_logging_class;
module_param(smbd_logging_class, uपूर्णांक, 0644);
MODULE_PARM_DESC(smbd_logging_class,
	"Logging class for SMBD transport 0x0 to 0x100");

#घोषणा ERR		0x0
#घोषणा INFO		0x1
अटल अचिन्हित पूर्णांक smbd_logging_level = ERR;
module_param(smbd_logging_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(smbd_logging_level,
	"Logging level for SMBD transport, 0 (default): error, 1: info");

#घोषणा log_rdma(level, class, fmt, args...)				\
करो अणु									\
	अगर (level <= smbd_logging_level || class & smbd_logging_class)	\
		cअगरs_dbg(VFS, "%s:%d " fmt, __func__, __LINE__, ##args);\
पूर्ण जबतक (0)

#घोषणा log_outgoing(level, fmt, args...) \
		log_rdma(level, LOG_OUTGOING, fmt, ##args)
#घोषणा log_incoming(level, fmt, args...) \
		log_rdma(level, LOG_INCOMING, fmt, ##args)
#घोषणा log_पढ़ो(level, fmt, args...)	log_rdma(level, LOG_READ, fmt, ##args)
#घोषणा log_ग_लिखो(level, fmt, args...)	log_rdma(level, LOG_WRITE, fmt, ##args)
#घोषणा log_rdma_send(level, fmt, args...) \
		log_rdma(level, LOG_RDMA_SEND, fmt, ##args)
#घोषणा log_rdma_recv(level, fmt, args...) \
		log_rdma(level, LOG_RDMA_RECV, fmt, ##args)
#घोषणा log_keep_alive(level, fmt, args...) \
		log_rdma(level, LOG_KEEP_ALIVE, fmt, ##args)
#घोषणा log_rdma_event(level, fmt, args...) \
		log_rdma(level, LOG_RDMA_EVENT, fmt, ##args)
#घोषणा log_rdma_mr(level, fmt, args...) \
		log_rdma(level, LOG_RDMA_MR, fmt, ##args)

अटल व्योम smbd_disconnect_rdma_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smbd_connection *info =
		container_of(work, काष्ठा smbd_connection, disconnect_work);

	अगर (info->transport_status == SMBD_CONNECTED) अणु
		info->transport_status = SMBD_DISCONNECTING;
		rdma_disconnect(info->id);
	पूर्ण
पूर्ण

अटल व्योम smbd_disconnect_rdma_connection(काष्ठा smbd_connection *info)
अणु
	queue_work(info->workqueue, &info->disconnect_work);
पूर्ण

/* Upcall from RDMA CM */
अटल पूर्णांक smbd_conn_upcall(
		काष्ठा rdma_cm_id *id, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा smbd_connection *info = id->context;

	log_rdma_event(INFO, "event=%d status=%d\n",
		event->event, event->status);

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		info->ri_rc = 0;
		complete(&info->ri_करोne);
		अवरोध;

	हाल RDMA_CM_EVENT_ADDR_ERROR:
		info->ri_rc = -EHOSTUNREACH;
		complete(&info->ri_करोne);
		अवरोध;

	हाल RDMA_CM_EVENT_ROUTE_ERROR:
		info->ri_rc = -ENETUNREACH;
		complete(&info->ri_करोne);
		अवरोध;

	हाल RDMA_CM_EVENT_ESTABLISHED:
		log_rdma_event(INFO, "connected event=%d\n", event->event);
		info->transport_status = SMBD_CONNECTED;
		wake_up_पूर्णांकerruptible(&info->conn_रुको);
		अवरोध;

	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
	हाल RDMA_CM_EVENT_REJECTED:
		log_rdma_event(INFO, "connecting failed event=%d\n", event->event);
		info->transport_status = SMBD_DISCONNECTED;
		wake_up_पूर्णांकerruptible(&info->conn_रुको);
		अवरोध;

	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
	हाल RDMA_CM_EVENT_DISCONNECTED:
		/* This happenes when we fail the negotiation */
		अगर (info->transport_status == SMBD_NEGOTIATE_FAILED) अणु
			info->transport_status = SMBD_DISCONNECTED;
			wake_up(&info->conn_रुको);
			अवरोध;
		पूर्ण

		info->transport_status = SMBD_DISCONNECTED;
		wake_up_पूर्णांकerruptible(&info->disconn_रुको);
		wake_up_पूर्णांकerruptible(&info->रुको_reassembly_queue);
		wake_up_पूर्णांकerruptible_all(&info->रुको_send_queue);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Upcall from RDMA QP */
अटल व्योम
smbd_qp_async_error_upcall(काष्ठा ib_event *event, व्योम *context)
अणु
	काष्ठा smbd_connection *info = context;

	log_rdma_event(ERR, "%s on device %s info %p\n",
		ib_event_msg(event->event), event->device->name, info);

	चयन (event->event) अणु
	हाल IB_EVENT_CQ_ERR:
	हाल IB_EVENT_QP_FATAL:
		smbd_disconnect_rdma_connection(info);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *smbd_request_payload(काष्ठा smbd_request *request)
अणु
	वापस (व्योम *)request->packet;
पूर्ण

अटल अंतरभूत व्योम *smbd_response_payload(काष्ठा smbd_response *response)
अणु
	वापस (व्योम *)response->packet;
पूर्ण

/* Called when a RDMA send is करोne */
अटल व्योम send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	पूर्णांक i;
	काष्ठा smbd_request *request =
		container_of(wc->wr_cqe, काष्ठा smbd_request, cqe);

	log_rdma_send(INFO, "smbd_request %p completed wc->status=%d\n",
		request, wc->status);

	अगर (wc->status != IB_WC_SUCCESS || wc->opcode != IB_WC_SEND) अणु
		log_rdma_send(ERR, "wc->status=%d wc->opcode=%d\n",
			wc->status, wc->opcode);
		smbd_disconnect_rdma_connection(request->info);
	पूर्ण

	क्रम (i = 0; i < request->num_sge; i++)
		ib_dma_unmap_single(request->info->id->device,
			request->sge[i].addr,
			request->sge[i].length,
			DMA_TO_DEVICE);

	अगर (atomic_dec_and_test(&request->info->send_pending))
		wake_up(&request->info->रुको_send_pending);

	wake_up(&request->info->रुको_post_send);

	mempool_मुक्त(request, request->info->request_mempool);
पूर्ण

अटल व्योम dump_smbd_negotiate_resp(काष्ठा smbd_negotiate_resp *resp)
अणु
	log_rdma_event(INFO, "resp message min_version %u max_version %u negotiated_version %u credits_requested %u credits_granted %u status %u max_readwrite_size %u preferred_send_size %u max_receive_size %u max_fragmented_size %u\n",
		       resp->min_version, resp->max_version,
		       resp->negotiated_version, resp->credits_requested,
		       resp->credits_granted, resp->status,
		       resp->max_पढ़ोग_लिखो_size, resp->preferred_send_size,
		       resp->max_receive_size, resp->max_fragmented_size);
पूर्ण

/*
 * Process a negotiation response message, according to [MS-SMBD]3.1.5.7
 * response, packet_length: the negotiation response message
 * वापस value: true अगर negotiation is a success, false अगर failed
 */
अटल bool process_negotiation_response(
		काष्ठा smbd_response *response, पूर्णांक packet_length)
अणु
	काष्ठा smbd_connection *info = response->info;
	काष्ठा smbd_negotiate_resp *packet = smbd_response_payload(response);

	अगर (packet_length < माप(काष्ठा smbd_negotiate_resp)) अणु
		log_rdma_event(ERR,
			"error: packet_length=%d\n", packet_length);
		वापस false;
	पूर्ण

	अगर (le16_to_cpu(packet->negotiated_version) != SMBD_V1) अणु
		log_rdma_event(ERR, "error: negotiated_version=%x\n",
			le16_to_cpu(packet->negotiated_version));
		वापस false;
	पूर्ण
	info->protocol = le16_to_cpu(packet->negotiated_version);

	अगर (packet->credits_requested == 0) अणु
		log_rdma_event(ERR, "error: credits_requested==0\n");
		वापस false;
	पूर्ण
	info->receive_credit_target = le16_to_cpu(packet->credits_requested);

	अगर (packet->credits_granted == 0) अणु
		log_rdma_event(ERR, "error: credits_granted==0\n");
		वापस false;
	पूर्ण
	atomic_set(&info->send_credits, le16_to_cpu(packet->credits_granted));

	atomic_set(&info->receive_credits, 0);

	अगर (le32_to_cpu(packet->preferred_send_size) > info->max_receive_size) अणु
		log_rdma_event(ERR, "error: preferred_send_size=%d\n",
			le32_to_cpu(packet->preferred_send_size));
		वापस false;
	पूर्ण
	info->max_receive_size = le32_to_cpu(packet->preferred_send_size);

	अगर (le32_to_cpu(packet->max_receive_size) < SMBD_MIN_RECEIVE_SIZE) अणु
		log_rdma_event(ERR, "error: max_receive_size=%d\n",
			le32_to_cpu(packet->max_receive_size));
		वापस false;
	पूर्ण
	info->max_send_size = min_t(पूर्णांक, info->max_send_size,
					le32_to_cpu(packet->max_receive_size));

	अगर (le32_to_cpu(packet->max_fragmented_size) <
			SMBD_MIN_FRAGMENTED_SIZE) अणु
		log_rdma_event(ERR, "error: max_fragmented_size=%d\n",
			le32_to_cpu(packet->max_fragmented_size));
		वापस false;
	पूर्ण
	info->max_fragmented_send_size =
		le32_to_cpu(packet->max_fragmented_size);
	info->rdma_पढ़ोग_लिखो_threshold =
		rdma_पढ़ोग_लिखो_threshold > info->max_fragmented_send_size ?
		info->max_fragmented_send_size :
		rdma_पढ़ोग_लिखो_threshold;


	info->max_पढ़ोग_लिखो_size = min_t(u32,
			le32_to_cpu(packet->max_पढ़ोग_लिखो_size),
			info->max_frmr_depth * PAGE_SIZE);
	info->max_frmr_depth = info->max_पढ़ोग_लिखो_size / PAGE_SIZE;

	वापस true;
पूर्ण

अटल व्योम smbd_post_send_credits(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret = 0;
	पूर्णांक use_receive_queue = 1;
	पूर्णांक rc;
	काष्ठा smbd_response *response;
	काष्ठा smbd_connection *info =
		container_of(work, काष्ठा smbd_connection,
			post_send_credits_work);

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		wake_up(&info->रुको_receive_queues);
		वापस;
	पूर्ण

	अगर (info->receive_credit_target >
		atomic_पढ़ो(&info->receive_credits)) अणु
		जबतक (true) अणु
			अगर (use_receive_queue)
				response = get_receive_buffer(info);
			अन्यथा
				response = get_empty_queue_buffer(info);
			अगर (!response) अणु
				/* now चयन to emtpy packet queue */
				अगर (use_receive_queue) अणु
					use_receive_queue = 0;
					जारी;
				पूर्ण अन्यथा
					अवरोध;
			पूर्ण

			response->type = SMBD_TRANSFER_DATA;
			response->first_segment = false;
			rc = smbd_post_recv(info, response);
			अगर (rc) अणु
				log_rdma_recv(ERR,
					"post_recv failed rc=%d\n", rc);
				put_receive_buffer(info, response);
				अवरोध;
			पूर्ण

			ret++;
		पूर्ण
	पूर्ण

	spin_lock(&info->lock_new_credits_offered);
	info->new_credits_offered += ret;
	spin_unlock(&info->lock_new_credits_offered);

	/* Promptly send an immediate packet as defined in [MS-SMBD] 3.1.1.1 */
	info->send_immediate = true;
	अगर (atomic_पढ़ो(&info->receive_credits) <
		info->receive_credit_target - 1) अणु
		अगर (info->keep_alive_requested == KEEP_ALIVE_PENDING ||
		    info->send_immediate) अणु
			log_keep_alive(INFO, "send an empty message\n");
			smbd_post_send_empty(info);
		पूर्ण
	पूर्ण
पूर्ण

/* Called from softirq, when recv is करोne */
अटल व्योम recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा smbd_data_transfer *data_transfer;
	काष्ठा smbd_response *response =
		container_of(wc->wr_cqe, काष्ठा smbd_response, cqe);
	काष्ठा smbd_connection *info = response->info;
	पूर्णांक data_length = 0;

	log_rdma_recv(INFO, "response=%p type=%d wc status=%d wc opcode %d byte_len=%d pkey_index=%x\n",
		      response, response->type, wc->status, wc->opcode,
		      wc->byte_len, wc->pkey_index);

	अगर (wc->status != IB_WC_SUCCESS || wc->opcode != IB_WC_RECV) अणु
		log_rdma_recv(INFO, "wc->status=%d opcode=%d\n",
			wc->status, wc->opcode);
		smbd_disconnect_rdma_connection(info);
		जाओ error;
	पूर्ण

	ib_dma_sync_single_क्रम_cpu(
		wc->qp->device,
		response->sge.addr,
		response->sge.length,
		DMA_FROM_DEVICE);

	चयन (response->type) अणु
	/* SMBD negotiation response */
	हाल SMBD_NEGOTIATE_RESP:
		dump_smbd_negotiate_resp(smbd_response_payload(response));
		info->full_packet_received = true;
		info->negotiate_करोne =
			process_negotiation_response(response, wc->byte_len);
		complete(&info->negotiate_completion);
		अवरोध;

	/* SMBD data transfer packet */
	हाल SMBD_TRANSFER_DATA:
		data_transfer = smbd_response_payload(response);
		data_length = le32_to_cpu(data_transfer->data_length);

		/*
		 * If this is a packet with data playload place the data in
		 * reassembly queue and wake up the पढ़ोing thपढ़ो
		 */
		अगर (data_length) अणु
			अगर (info->full_packet_received)
				response->first_segment = true;

			अगर (le32_to_cpu(data_transfer->reमुख्यing_data_length))
				info->full_packet_received = false;
			अन्यथा
				info->full_packet_received = true;

			enqueue_reassembly(
				info,
				response,
				data_length);
		पूर्ण अन्यथा
			put_empty_packet(info, response);

		अगर (data_length)
			wake_up_पूर्णांकerruptible(&info->रुको_reassembly_queue);

		atomic_dec(&info->receive_credits);
		info->receive_credit_target =
			le16_to_cpu(data_transfer->credits_requested);
		अगर (le16_to_cpu(data_transfer->credits_granted)) अणु
			atomic_add(le16_to_cpu(data_transfer->credits_granted),
				&info->send_credits);
			/*
			 * We have new send credits granted from remote peer
			 * If any sender is रुकोing क्रम credits, unblock it
			 */
			wake_up_पूर्णांकerruptible(&info->रुको_send_queue);
		पूर्ण

		log_incoming(INFO, "data flags %d data_offset %d data_length %d remaining_data_length %d\n",
			     le16_to_cpu(data_transfer->flags),
			     le32_to_cpu(data_transfer->data_offset),
			     le32_to_cpu(data_transfer->data_length),
			     le32_to_cpu(data_transfer->reमुख्यing_data_length));

		/* Send a KEEP_ALIVE response right away अगर requested */
		info->keep_alive_requested = KEEP_ALIVE_NONE;
		अगर (le16_to_cpu(data_transfer->flags) &
				SMB_सूचीECT_RESPONSE_REQUESTED) अणु
			info->keep_alive_requested = KEEP_ALIVE_PENDING;
		पूर्ण

		वापस;

	शेष:
		log_rdma_recv(ERR,
			"unexpected response type=%d\n", response->type);
	पूर्ण

error:
	put_receive_buffer(info, response);
पूर्ण

अटल काष्ठा rdma_cm_id *smbd_create_id(
		काष्ठा smbd_connection *info,
		काष्ठा sockaddr *dstaddr, पूर्णांक port)
अणु
	काष्ठा rdma_cm_id *id;
	पूर्णांक rc;
	__be16 *sport;

	id = rdma_create_id(&init_net, smbd_conn_upcall, info,
		RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(id)) अणु
		rc = PTR_ERR(id);
		log_rdma_event(ERR, "rdma_create_id() failed %i\n", rc);
		वापस id;
	पूर्ण

	अगर (dstaddr->sa_family == AF_INET6)
		sport = &((काष्ठा sockaddr_in6 *)dstaddr)->sin6_port;
	अन्यथा
		sport = &((काष्ठा sockaddr_in *)dstaddr)->sin_port;

	*sport = htons(port);

	init_completion(&info->ri_करोne);
	info->ri_rc = -ETIMEDOUT;

	rc = rdma_resolve_addr(id, शून्य, (काष्ठा sockaddr *)dstaddr,
		RDMA_RESOLVE_TIMEOUT);
	अगर (rc) अणु
		log_rdma_event(ERR, "rdma_resolve_addr() failed %i\n", rc);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&info->ri_करोne, msecs_to_jअगरfies(RDMA_RESOLVE_TIMEOUT));
	rc = info->ri_rc;
	अगर (rc) अणु
		log_rdma_event(ERR, "rdma_resolve_addr() completed %i\n", rc);
		जाओ out;
	पूर्ण

	info->ri_rc = -ETIMEDOUT;
	rc = rdma_resolve_route(id, RDMA_RESOLVE_TIMEOUT);
	अगर (rc) अणु
		log_rdma_event(ERR, "rdma_resolve_route() failed %i\n", rc);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&info->ri_करोne, msecs_to_jअगरfies(RDMA_RESOLVE_TIMEOUT));
	rc = info->ri_rc;
	अगर (rc) अणु
		log_rdma_event(ERR, "rdma_resolve_route() completed %i\n", rc);
		जाओ out;
	पूर्ण

	वापस id;

out:
	rdma_destroy_id(id);
	वापस ERR_PTR(rc);
पूर्ण

/*
 * Test अगर FRWR (Fast Registration Work Requests) is supported on the device
 * This implementation requries FRWR on RDMA पढ़ो/ग_लिखो
 * वापस value: true अगर it is supported
 */
अटल bool frwr_is_supported(काष्ठा ib_device_attr *attrs)
अणु
	अगर (!(attrs->device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		वापस false;
	अगर (attrs->max_fast_reg_page_list_len == 0)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक smbd_ia_खोलो(
		काष्ठा smbd_connection *info,
		काष्ठा sockaddr *dstaddr, पूर्णांक port)
अणु
	पूर्णांक rc;

	info->id = smbd_create_id(info, dstaddr, port);
	अगर (IS_ERR(info->id)) अणु
		rc = PTR_ERR(info->id);
		जाओ out1;
	पूर्ण

	अगर (!frwr_is_supported(&info->id->device->attrs)) अणु
		log_rdma_event(ERR, "Fast Registration Work Requests (FRWR) is not supported\n");
		log_rdma_event(ERR, "Device capability flags = %llx max_fast_reg_page_list_len = %u\n",
			       info->id->device->attrs.device_cap_flags,
			       info->id->device->attrs.max_fast_reg_page_list_len);
		rc = -EPROTONOSUPPORT;
		जाओ out2;
	पूर्ण
	info->max_frmr_depth = min_t(पूर्णांक,
		smbd_max_frmr_depth,
		info->id->device->attrs.max_fast_reg_page_list_len);
	info->mr_type = IB_MR_TYPE_MEM_REG;
	अगर (info->id->device->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		info->mr_type = IB_MR_TYPE_SG_GAPS;

	info->pd = ib_alloc_pd(info->id->device, 0);
	अगर (IS_ERR(info->pd)) अणु
		rc = PTR_ERR(info->pd);
		log_rdma_event(ERR, "ib_alloc_pd() returned %d\n", rc);
		जाओ out2;
	पूर्ण

	वापस 0;

out2:
	rdma_destroy_id(info->id);
	info->id = शून्य;

out1:
	वापस rc;
पूर्ण

/*
 * Send a negotiation request message to the peer
 * The negotiation procedure is in [MS-SMBD] 3.1.5.2 and 3.1.5.3
 * After negotiation, the transport is connected and पढ़ोy क्रम
 * carrying upper layer SMB payload
 */
अटल पूर्णांक smbd_post_send_negotiate_req(काष्ठा smbd_connection *info)
अणु
	काष्ठा ib_send_wr send_wr;
	पूर्णांक rc = -ENOMEM;
	काष्ठा smbd_request *request;
	काष्ठा smbd_negotiate_req *packet;

	request = mempool_alloc(info->request_mempool, GFP_KERNEL);
	अगर (!request)
		वापस rc;

	request->info = info;

	packet = smbd_request_payload(request);
	packet->min_version = cpu_to_le16(SMBD_V1);
	packet->max_version = cpu_to_le16(SMBD_V1);
	packet->reserved = 0;
	packet->credits_requested = cpu_to_le16(info->send_credit_target);
	packet->preferred_send_size = cpu_to_le32(info->max_send_size);
	packet->max_receive_size = cpu_to_le32(info->max_receive_size);
	packet->max_fragmented_size =
		cpu_to_le32(info->max_fragmented_recv_size);

	request->num_sge = 1;
	request->sge[0].addr = ib_dma_map_single(
				info->id->device, (व्योम *)packet,
				माप(*packet), DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(info->id->device, request->sge[0].addr)) अणु
		rc = -EIO;
		जाओ dma_mapping_failed;
	पूर्ण

	request->sge[0].length = माप(*packet);
	request->sge[0].lkey = info->pd->local_dma_lkey;

	ib_dma_sync_single_क्रम_device(
		info->id->device, request->sge[0].addr,
		request->sge[0].length, DMA_TO_DEVICE);

	request->cqe.करोne = send_करोne;

	send_wr.next = शून्य;
	send_wr.wr_cqe = &request->cqe;
	send_wr.sg_list = request->sge;
	send_wr.num_sge = request->num_sge;
	send_wr.opcode = IB_WR_SEND;
	send_wr.send_flags = IB_SEND_SIGNALED;

	log_rdma_send(INFO, "sge addr=%llx length=%x lkey=%x\n",
		request->sge[0].addr,
		request->sge[0].length, request->sge[0].lkey);

	atomic_inc(&info->send_pending);
	rc = ib_post_send(info->id->qp, &send_wr, शून्य);
	अगर (!rc)
		वापस 0;

	/* अगर we reach here, post send failed */
	log_rdma_send(ERR, "ib_post_send failed rc=%d\n", rc);
	atomic_dec(&info->send_pending);
	ib_dma_unmap_single(info->id->device, request->sge[0].addr,
		request->sge[0].length, DMA_TO_DEVICE);

	smbd_disconnect_rdma_connection(info);

dma_mapping_failed:
	mempool_मुक्त(request, info->request_mempool);
	वापस rc;
पूर्ण

/*
 * Extend the credits to remote peer
 * This implements [MS-SMBD] 3.1.5.9
 * The idea is that we should extend credits to remote peer as quickly as
 * it's allowed, to मुख्यtain data flow. We allocate as much receive
 * buffer as possible, and extend the receive credits to remote peer
 * वापस value: the new credtis being granted.
 */
अटल पूर्णांक manage_credits_prior_sending(काष्ठा smbd_connection *info)
अणु
	पूर्णांक new_credits;

	spin_lock(&info->lock_new_credits_offered);
	new_credits = info->new_credits_offered;
	info->new_credits_offered = 0;
	spin_unlock(&info->lock_new_credits_offered);

	वापस new_credits;
पूर्ण

/*
 * Check अगर we need to send a KEEP_ALIVE message
 * The idle connection समयr triggers a KEEP_ALIVE message when expires
 * SMB_सूचीECT_RESPONSE_REQUESTED is set in the message flag to have peer send
 * back a response.
 * वापस value:
 * 1 अगर SMB_सूचीECT_RESPONSE_REQUESTED needs to be set
 * 0: otherwise
 */
अटल पूर्णांक manage_keep_alive_beक्रमe_sending(काष्ठा smbd_connection *info)
अणु
	अगर (info->keep_alive_requested == KEEP_ALIVE_PENDING) अणु
		info->keep_alive_requested = KEEP_ALIVE_SENT;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Post the send request */
अटल पूर्णांक smbd_post_send(काष्ठा smbd_connection *info,
		काष्ठा smbd_request *request)
अणु
	काष्ठा ib_send_wr send_wr;
	पूर्णांक rc, i;

	क्रम (i = 0; i < request->num_sge; i++) अणु
		log_rdma_send(INFO,
			"rdma_request sge[%d] addr=%llu length=%u\n",
			i, request->sge[i].addr, request->sge[i].length);
		ib_dma_sync_single_क्रम_device(
			info->id->device,
			request->sge[i].addr,
			request->sge[i].length,
			DMA_TO_DEVICE);
	पूर्ण

	request->cqe.करोne = send_करोne;

	send_wr.next = शून्य;
	send_wr.wr_cqe = &request->cqe;
	send_wr.sg_list = request->sge;
	send_wr.num_sge = request->num_sge;
	send_wr.opcode = IB_WR_SEND;
	send_wr.send_flags = IB_SEND_SIGNALED;

	rc = ib_post_send(info->id->qp, &send_wr, शून्य);
	अगर (rc) अणु
		log_rdma_send(ERR, "ib_post_send failed rc=%d\n", rc);
		smbd_disconnect_rdma_connection(info);
		rc = -EAGAIN;
	पूर्ण अन्यथा
		/* Reset समयr क्रम idle connection after packet is sent */
		mod_delayed_work(info->workqueue, &info->idle_समयr_work,
			info->keep_alive_पूर्णांकerval*HZ);

	वापस rc;
पूर्ण

अटल पूर्णांक smbd_post_send_sgl(काष्ठा smbd_connection *info,
	काष्ठा scatterlist *sgl, पूर्णांक data_length, पूर्णांक reमुख्यing_data_length)
अणु
	पूर्णांक num_sgs;
	पूर्णांक i, rc;
	पूर्णांक header_length;
	काष्ठा smbd_request *request;
	काष्ठा smbd_data_transfer *packet;
	पूर्णांक new_credits;
	काष्ठा scatterlist *sg;

रुको_credit:
	/* Wait क्रम send credits. A SMBD packet needs one credit */
	rc = रुको_event_पूर्णांकerruptible(info->रुको_send_queue,
		atomic_पढ़ो(&info->send_credits) > 0 ||
		info->transport_status != SMBD_CONNECTED);
	अगर (rc)
		जाओ err_रुको_credit;

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		log_outgoing(ERR, "disconnected not sending on wait_credit\n");
		rc = -EAGAIN;
		जाओ err_रुको_credit;
	पूर्ण
	अगर (unlikely(atomic_dec_वापस(&info->send_credits) < 0)) अणु
		atomic_inc(&info->send_credits);
		जाओ रुको_credit;
	पूर्ण

रुको_send_queue:
	रुको_event(info->रुको_post_send,
		atomic_पढ़ो(&info->send_pending) < info->send_credit_target ||
		info->transport_status != SMBD_CONNECTED);

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		log_outgoing(ERR, "disconnected not sending on wait_send_queue\n");
		rc = -EAGAIN;
		जाओ err_रुको_send_queue;
	पूर्ण

	अगर (unlikely(atomic_inc_वापस(&info->send_pending) >
				info->send_credit_target)) अणु
		atomic_dec(&info->send_pending);
		जाओ रुको_send_queue;
	पूर्ण

	request = mempool_alloc(info->request_mempool, GFP_KERNEL);
	अगर (!request) अणु
		rc = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	request->info = info;

	/* Fill in the packet header */
	packet = smbd_request_payload(request);
	packet->credits_requested = cpu_to_le16(info->send_credit_target);

	new_credits = manage_credits_prior_sending(info);
	atomic_add(new_credits, &info->receive_credits);
	packet->credits_granted = cpu_to_le16(new_credits);

	info->send_immediate = false;

	packet->flags = 0;
	अगर (manage_keep_alive_beक्रमe_sending(info))
		packet->flags |= cpu_to_le16(SMB_सूचीECT_RESPONSE_REQUESTED);

	packet->reserved = 0;
	अगर (!data_length)
		packet->data_offset = 0;
	अन्यथा
		packet->data_offset = cpu_to_le32(24);
	packet->data_length = cpu_to_le32(data_length);
	packet->reमुख्यing_data_length = cpu_to_le32(reमुख्यing_data_length);
	packet->padding = 0;

	log_outgoing(INFO, "credits_requested=%d credits_granted=%d data_offset=%d data_length=%d remaining_data_length=%d\n",
		     le16_to_cpu(packet->credits_requested),
		     le16_to_cpu(packet->credits_granted),
		     le32_to_cpu(packet->data_offset),
		     le32_to_cpu(packet->data_length),
		     le32_to_cpu(packet->reमुख्यing_data_length));

	/* Map the packet to DMA */
	header_length = माप(काष्ठा smbd_data_transfer);
	/* If this is a packet without payload, करोn't send padding */
	अगर (!data_length)
		header_length = दुरत्व(काष्ठा smbd_data_transfer, padding);

	request->num_sge = 1;
	request->sge[0].addr = ib_dma_map_single(info->id->device,
						 (व्योम *)packet,
						 header_length,
						 DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(info->id->device, request->sge[0].addr)) अणु
		rc = -EIO;
		request->sge[0].addr = 0;
		जाओ err_dma;
	पूर्ण

	request->sge[0].length = header_length;
	request->sge[0].lkey = info->pd->local_dma_lkey;

	/* Fill in the packet data payload */
	num_sgs = sgl ? sg_nents(sgl) : 0;
	क्रम_each_sg(sgl, sg, num_sgs, i) अणु
		request->sge[i+1].addr =
			ib_dma_map_page(info->id->device, sg_page(sg),
			       sg->offset, sg->length, DMA_TO_DEVICE);
		अगर (ib_dma_mapping_error(
				info->id->device, request->sge[i+1].addr)) अणु
			rc = -EIO;
			request->sge[i+1].addr = 0;
			जाओ err_dma;
		पूर्ण
		request->sge[i+1].length = sg->length;
		request->sge[i+1].lkey = info->pd->local_dma_lkey;
		request->num_sge++;
	पूर्ण

	rc = smbd_post_send(info, request);
	अगर (!rc)
		वापस 0;

err_dma:
	क्रम (i = 0; i < request->num_sge; i++)
		अगर (request->sge[i].addr)
			ib_dma_unmap_single(info->id->device,
					    request->sge[i].addr,
					    request->sge[i].length,
					    DMA_TO_DEVICE);
	mempool_मुक्त(request, info->request_mempool);

	/* roll back receive credits and credits to be offered */
	spin_lock(&info->lock_new_credits_offered);
	info->new_credits_offered += new_credits;
	spin_unlock(&info->lock_new_credits_offered);
	atomic_sub(new_credits, &info->receive_credits);

err_alloc:
	अगर (atomic_dec_and_test(&info->send_pending))
		wake_up(&info->रुको_send_pending);

err_रुको_send_queue:
	/* roll back send credits and pending */
	atomic_inc(&info->send_credits);

err_रुको_credit:
	वापस rc;
पूर्ण

/*
 * Send a page
 * page: the page to send
 * offset: offset in the page to send
 * size: length in the page to send
 * reमुख्यing_data_length: reमुख्यing data to send in this payload
 */
अटल पूर्णांक smbd_post_send_page(काष्ठा smbd_connection *info, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार size, पूर्णांक reमुख्यing_data_length)
अणु
	काष्ठा scatterlist sgl;

	sg_init_table(&sgl, 1);
	sg_set_page(&sgl, page, size, offset);

	वापस smbd_post_send_sgl(info, &sgl, size, reमुख्यing_data_length);
पूर्ण

/*
 * Send an empty message
 * Empty message is used to extend credits to peer to क्रम keep live
 * जबतक there is no upper layer payload to send at the समय
 */
अटल पूर्णांक smbd_post_send_empty(काष्ठा smbd_connection *info)
अणु
	info->count_send_empty++;
	वापस smbd_post_send_sgl(info, शून्य, 0, 0);
पूर्ण

/*
 * Send a data buffer
 * iov: the iov array describing the data buffers
 * n_vec: number of iov array
 * reमुख्यing_data_length: reमुख्यing data to send following this packet
 * in segmented SMBD packet
 */
अटल पूर्णांक smbd_post_send_data(
	काष्ठा smbd_connection *info, काष्ठा kvec *iov, पूर्णांक n_vec,
	पूर्णांक reमुख्यing_data_length)
अणु
	पूर्णांक i;
	u32 data_length = 0;
	काष्ठा scatterlist sgl[SMBसूचीECT_MAX_SGE];

	अगर (n_vec > SMBसूचीECT_MAX_SGE) अणु
		cअगरs_dbg(VFS, "Can't fit data to SGL, n_vec=%d\n", n_vec);
		वापस -EINVAL;
	पूर्ण

	sg_init_table(sgl, n_vec);
	क्रम (i = 0; i < n_vec; i++) अणु
		data_length += iov[i].iov_len;
		sg_set_buf(&sgl[i], iov[i].iov_base, iov[i].iov_len);
	पूर्ण

	वापस smbd_post_send_sgl(info, sgl, data_length, reमुख्यing_data_length);
पूर्ण

/*
 * Post a receive request to the transport
 * The remote peer can only send data when a receive request is posted
 * The पूर्णांकeraction is controlled by send/receive credit प्रणाली
 */
अटल पूर्णांक smbd_post_recv(
		काष्ठा smbd_connection *info, काष्ठा smbd_response *response)
अणु
	काष्ठा ib_recv_wr recv_wr;
	पूर्णांक rc = -EIO;

	response->sge.addr = ib_dma_map_single(
				info->id->device, response->packet,
				info->max_receive_size, DMA_FROM_DEVICE);
	अगर (ib_dma_mapping_error(info->id->device, response->sge.addr))
		वापस rc;

	response->sge.length = info->max_receive_size;
	response->sge.lkey = info->pd->local_dma_lkey;

	response->cqe.करोne = recv_करोne;

	recv_wr.wr_cqe = &response->cqe;
	recv_wr.next = शून्य;
	recv_wr.sg_list = &response->sge;
	recv_wr.num_sge = 1;

	rc = ib_post_recv(info->id->qp, &recv_wr, शून्य);
	अगर (rc) अणु
		ib_dma_unmap_single(info->id->device, response->sge.addr,
				    response->sge.length, DMA_FROM_DEVICE);
		smbd_disconnect_rdma_connection(info);
		log_rdma_recv(ERR, "ib_post_recv failed rc=%d\n", rc);
	पूर्ण

	वापस rc;
पूर्ण

/* Perक्रमm SMBD negotiate according to [MS-SMBD] 3.1.5.2 */
अटल पूर्णांक smbd_negotiate(काष्ठा smbd_connection *info)
अणु
	पूर्णांक rc;
	काष्ठा smbd_response *response = get_receive_buffer(info);

	response->type = SMBD_NEGOTIATE_RESP;
	rc = smbd_post_recv(info, response);
	log_rdma_event(INFO, "smbd_post_recv rc=%d iov.addr=%llx iov.length=%x iov.lkey=%x\n",
		       rc, response->sge.addr,
		       response->sge.length, response->sge.lkey);
	अगर (rc)
		वापस rc;

	init_completion(&info->negotiate_completion);
	info->negotiate_करोne = false;
	rc = smbd_post_send_negotiate_req(info);
	अगर (rc)
		वापस rc;

	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&info->negotiate_completion, SMBD_NEGOTIATE_TIMEOUT * HZ);
	log_rdma_event(INFO, "wait_for_completion_timeout rc=%d\n", rc);

	अगर (info->negotiate_करोne)
		वापस 0;

	अगर (rc == 0)
		rc = -ETIMEDOUT;
	अन्यथा अगर (rc == -ERESTARTSYS)
		rc = -EINTR;
	अन्यथा
		rc = -ENOTCONN;

	वापस rc;
पूर्ण

अटल व्योम put_empty_packet(
		काष्ठा smbd_connection *info, काष्ठा smbd_response *response)
अणु
	spin_lock(&info->empty_packet_queue_lock);
	list_add_tail(&response->list, &info->empty_packet_queue);
	info->count_empty_packet_queue++;
	spin_unlock(&info->empty_packet_queue_lock);

	queue_work(info->workqueue, &info->post_send_credits_work);
पूर्ण

/*
 * Implement Connection.FragmentReassemblyBuffer defined in [MS-SMBD] 3.1.1.1
 * This is a queue क्रम reassembling upper layer payload and present to upper
 * layer. All the inncoming payload go to the reassembly queue, regardless of
 * अगर reassembly is required. The uuper layer code पढ़ोs from the queue क्रम all
 * incoming payloads.
 * Put a received packet to the reassembly queue
 * response: the packet received
 * data_length: the size of payload in this packet
 */
अटल व्योम enqueue_reassembly(
	काष्ठा smbd_connection *info,
	काष्ठा smbd_response *response,
	पूर्णांक data_length)
अणु
	spin_lock(&info->reassembly_queue_lock);
	list_add_tail(&response->list, &info->reassembly_queue);
	info->reassembly_queue_length++;
	/*
	 * Make sure reassembly_data_length is updated after list and
	 * reassembly_queue_length are updated. On the dequeue side
	 * reassembly_data_length is checked without a lock to determine
	 * अगर reassembly_queue_length and list is up to date
	 */
	virt_wmb();
	info->reassembly_data_length += data_length;
	spin_unlock(&info->reassembly_queue_lock);
	info->count_reassembly_queue++;
	info->count_enqueue_reassembly_queue++;
पूर्ण

/*
 * Get the first entry at the front of reassembly queue
 * Caller is responsible क्रम locking
 * वापस value: the first entry अगर any, शून्य अगर queue is empty
 */
अटल काष्ठा smbd_response *_get_first_reassembly(काष्ठा smbd_connection *info)
अणु
	काष्ठा smbd_response *ret = शून्य;

	अगर (!list_empty(&info->reassembly_queue)) अणु
		ret = list_first_entry(
			&info->reassembly_queue,
			काष्ठा smbd_response, list);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा smbd_response *get_empty_queue_buffer(
		काष्ठा smbd_connection *info)
अणु
	काष्ठा smbd_response *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->empty_packet_queue_lock, flags);
	अगर (!list_empty(&info->empty_packet_queue)) अणु
		ret = list_first_entry(
			&info->empty_packet_queue,
			काष्ठा smbd_response, list);
		list_del(&ret->list);
		info->count_empty_packet_queue--;
	पूर्ण
	spin_unlock_irqrestore(&info->empty_packet_queue_lock, flags);

	वापस ret;
पूर्ण

/*
 * Get a receive buffer
 * For each remote send, we need to post a receive. The receive buffers are
 * pre-allocated in advance.
 * वापस value: the receive buffer, शून्य अगर none is available
 */
अटल काष्ठा smbd_response *get_receive_buffer(काष्ठा smbd_connection *info)
अणु
	काष्ठा smbd_response *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->receive_queue_lock, flags);
	अगर (!list_empty(&info->receive_queue)) अणु
		ret = list_first_entry(
			&info->receive_queue,
			काष्ठा smbd_response, list);
		list_del(&ret->list);
		info->count_receive_queue--;
		info->count_get_receive_buffer++;
	पूर्ण
	spin_unlock_irqrestore(&info->receive_queue_lock, flags);

	वापस ret;
पूर्ण

/*
 * Return a receive buffer
 * Upon वापसing of a receive buffer, we can post new receive and extend
 * more receive credits to remote peer. This is करोne immediately after a
 * receive buffer is वापसed.
 */
अटल व्योम put_receive_buffer(
	काष्ठा smbd_connection *info, काष्ठा smbd_response *response)
अणु
	अचिन्हित दीर्घ flags;

	ib_dma_unmap_single(info->id->device, response->sge.addr,
		response->sge.length, DMA_FROM_DEVICE);

	spin_lock_irqsave(&info->receive_queue_lock, flags);
	list_add_tail(&response->list, &info->receive_queue);
	info->count_receive_queue++;
	info->count_put_receive_buffer++;
	spin_unlock_irqrestore(&info->receive_queue_lock, flags);

	queue_work(info->workqueue, &info->post_send_credits_work);
पूर्ण

/* Pपुनः_स्मृतिate all receive buffer on transport establishment */
अटल पूर्णांक allocate_receive_buffers(काष्ठा smbd_connection *info, पूर्णांक num_buf)
अणु
	पूर्णांक i;
	काष्ठा smbd_response *response;

	INIT_LIST_HEAD(&info->reassembly_queue);
	spin_lock_init(&info->reassembly_queue_lock);
	info->reassembly_data_length = 0;
	info->reassembly_queue_length = 0;

	INIT_LIST_HEAD(&info->receive_queue);
	spin_lock_init(&info->receive_queue_lock);
	info->count_receive_queue = 0;

	INIT_LIST_HEAD(&info->empty_packet_queue);
	spin_lock_init(&info->empty_packet_queue_lock);
	info->count_empty_packet_queue = 0;

	init_रुकोqueue_head(&info->रुको_receive_queues);

	क्रम (i = 0; i < num_buf; i++) अणु
		response = mempool_alloc(info->response_mempool, GFP_KERNEL);
		अगर (!response)
			जाओ allocate_failed;

		response->info = info;
		list_add_tail(&response->list, &info->receive_queue);
		info->count_receive_queue++;
	पूर्ण

	वापस 0;

allocate_failed:
	जबतक (!list_empty(&info->receive_queue)) अणु
		response = list_first_entry(
				&info->receive_queue,
				काष्ठा smbd_response, list);
		list_del(&response->list);
		info->count_receive_queue--;

		mempool_मुक्त(response, info->response_mempool);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम destroy_receive_buffers(काष्ठा smbd_connection *info)
अणु
	काष्ठा smbd_response *response;

	जबतक ((response = get_receive_buffer(info)))
		mempool_मुक्त(response, info->response_mempool);

	जबतक ((response = get_empty_queue_buffer(info)))
		mempool_मुक्त(response, info->response_mempool);
पूर्ण

/* Implement idle connection समयr [MS-SMBD] 3.1.6.2 */
अटल व्योम idle_connection_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smbd_connection *info = container_of(
					work, काष्ठा smbd_connection,
					idle_समयr_work.work);

	अगर (info->keep_alive_requested != KEEP_ALIVE_NONE) अणु
		log_keep_alive(ERR,
			"error status info->keep_alive_requested=%d\n",
			info->keep_alive_requested);
		smbd_disconnect_rdma_connection(info);
		वापस;
	पूर्ण

	log_keep_alive(INFO, "about to send an empty idle message\n");
	smbd_post_send_empty(info);

	/* Setup the next idle समयout work */
	queue_delayed_work(info->workqueue, &info->idle_समयr_work,
			info->keep_alive_पूर्णांकerval*HZ);
पूर्ण

/*
 * Destroy the transport and related RDMA and memory resources
 * Need to go through all the pending counters and make sure on one is using
 * the transport जबतक it is destroyed
 */
व्योम smbd_destroy(काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smbd_connection *info = server->smbd_conn;
	काष्ठा smbd_response *response;
	अचिन्हित दीर्घ flags;

	अगर (!info) अणु
		log_rdma_event(INFO, "rdma session already destroyed\n");
		वापस;
	पूर्ण

	log_rdma_event(INFO, "destroying rdma session\n");
	अगर (info->transport_status != SMBD_DISCONNECTED) अणु
		rdma_disconnect(server->smbd_conn->id);
		log_rdma_event(INFO, "wait for transport being disconnected\n");
		रुको_event_पूर्णांकerruptible(
			info->disconn_रुको,
			info->transport_status == SMBD_DISCONNECTED);
	पूर्ण

	log_rdma_event(INFO, "destroying qp\n");
	ib_drain_qp(info->id->qp);
	rdma_destroy_qp(info->id);

	log_rdma_event(INFO, "cancelling idle timer\n");
	cancel_delayed_work_sync(&info->idle_समयr_work);

	log_rdma_event(INFO, "wait for all send posted to IB to finish\n");
	रुको_event(info->रुको_send_pending,
		atomic_पढ़ो(&info->send_pending) == 0);

	/* It's not posssible क्रम upper layer to get to reassembly */
	log_rdma_event(INFO, "drain the reassembly queue\n");
	करो अणु
		spin_lock_irqsave(&info->reassembly_queue_lock, flags);
		response = _get_first_reassembly(info);
		अगर (response) अणु
			list_del(&response->list);
			spin_unlock_irqrestore(
				&info->reassembly_queue_lock, flags);
			put_receive_buffer(info, response);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(
				&info->reassembly_queue_lock, flags);
	पूर्ण जबतक (response);
	info->reassembly_data_length = 0;

	log_rdma_event(INFO, "free receive buffers\n");
	रुको_event(info->रुको_receive_queues,
		info->count_receive_queue + info->count_empty_packet_queue
			== info->receive_credit_max);
	destroy_receive_buffers(info);

	/*
	 * For perक्रमmance reasons, memory registration and deregistration
	 * are not locked by srv_mutex. It is possible some processes are
	 * blocked on transport srv_mutex जबतक holding memory registration.
	 * Release the transport srv_mutex to allow them to hit the failure
	 * path when sending data, and then release memory registartions.
	 */
	log_rdma_event(INFO, "freeing mr list\n");
	wake_up_पूर्णांकerruptible_all(&info->रुको_mr);
	जबतक (atomic_पढ़ो(&info->mr_used_count)) अणु
		mutex_unlock(&server->srv_mutex);
		msleep(1000);
		mutex_lock(&server->srv_mutex);
	पूर्ण
	destroy_mr_list(info);

	ib_मुक्त_cq(info->send_cq);
	ib_मुक्त_cq(info->recv_cq);
	ib_dealloc_pd(info->pd);
	rdma_destroy_id(info->id);

	/* मुक्त mempools */
	mempool_destroy(info->request_mempool);
	kmem_cache_destroy(info->request_cache);

	mempool_destroy(info->response_mempool);
	kmem_cache_destroy(info->response_cache);

	info->transport_status = SMBD_DESTROYED;

	destroy_workqueue(info->workqueue);
	log_rdma_event(INFO,  "rdma session destroyed\n");
	kमुक्त(info);
पूर्ण

/*
 * Reconnect this SMBD connection, called from upper layer
 * वापस value: 0 on success, or actual error code
 */
पूर्णांक smbd_reconnect(काष्ठा TCP_Server_Info *server)
अणु
	log_rdma_event(INFO, "reconnecting rdma session\n");

	अगर (!server->smbd_conn) अणु
		log_rdma_event(INFO, "rdma session already destroyed\n");
		जाओ create_conn;
	पूर्ण

	/*
	 * This is possible अगर transport is disconnected and we haven't received
	 * notअगरication from RDMA, but upper layer has detected समयout
	 */
	अगर (server->smbd_conn->transport_status == SMBD_CONNECTED) अणु
		log_rdma_event(INFO, "disconnecting transport\n");
		smbd_destroy(server);
	पूर्ण

create_conn:
	log_rdma_event(INFO, "creating rdma session\n");
	server->smbd_conn = smbd_get_connection(
		server, (काष्ठा sockaddr *) &server->dstaddr);

	अगर (server->smbd_conn)
		cअगरs_dbg(VFS, "RDMA transport re-established\n");

	वापस server->smbd_conn ? 0 : -ENOENT;
पूर्ण

अटल व्योम destroy_caches_and_workqueue(काष्ठा smbd_connection *info)
अणु
	destroy_receive_buffers(info);
	destroy_workqueue(info->workqueue);
	mempool_destroy(info->response_mempool);
	kmem_cache_destroy(info->response_cache);
	mempool_destroy(info->request_mempool);
	kmem_cache_destroy(info->request_cache);
पूर्ण

#घोषणा MAX_NAME_LEN	80
अटल पूर्णांक allocate_caches_and_workqueue(काष्ठा smbd_connection *info)
अणु
	अक्षर name[MAX_NAME_LEN];
	पूर्णांक rc;

	scnम_लिखो(name, MAX_NAME_LEN, "smbd_request_%p", info);
	info->request_cache =
		kmem_cache_create(
			name,
			माप(काष्ठा smbd_request) +
				माप(काष्ठा smbd_data_transfer),
			0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!info->request_cache)
		वापस -ENOMEM;

	info->request_mempool =
		mempool_create(info->send_credit_target, mempool_alloc_slab,
			mempool_मुक्त_slab, info->request_cache);
	अगर (!info->request_mempool)
		जाओ out1;

	scnम_लिखो(name, MAX_NAME_LEN, "smbd_response_%p", info);
	info->response_cache =
		kmem_cache_create(
			name,
			माप(काष्ठा smbd_response) +
				info->max_receive_size,
			0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!info->response_cache)
		जाओ out2;

	info->response_mempool =
		mempool_create(info->receive_credit_max, mempool_alloc_slab,
		       mempool_मुक्त_slab, info->response_cache);
	अगर (!info->response_mempool)
		जाओ out3;

	scnम_लिखो(name, MAX_NAME_LEN, "smbd_%p", info);
	info->workqueue = create_workqueue(name);
	अगर (!info->workqueue)
		जाओ out4;

	rc = allocate_receive_buffers(info, info->receive_credit_max);
	अगर (rc) अणु
		log_rdma_event(ERR, "failed to allocate receive buffers\n");
		जाओ out5;
	पूर्ण

	वापस 0;

out5:
	destroy_workqueue(info->workqueue);
out4:
	mempool_destroy(info->response_mempool);
out3:
	kmem_cache_destroy(info->response_cache);
out2:
	mempool_destroy(info->request_mempool);
out1:
	kmem_cache_destroy(info->request_cache);
	वापस -ENOMEM;
पूर्ण

/* Create a SMBD connection, called by upper layer */
अटल काष्ठा smbd_connection *_smbd_get_connection(
	काष्ठा TCP_Server_Info *server, काष्ठा sockaddr *dstaddr, पूर्णांक port)
अणु
	पूर्णांक rc;
	काष्ठा smbd_connection *info;
	काष्ठा rdma_conn_param conn_param;
	काष्ठा ib_qp_init_attr qp_attr;
	काष्ठा sockaddr_in *addr_in = (काष्ठा sockaddr_in *) dstaddr;
	काष्ठा ib_port_immutable port_immutable;
	u32 ird_ord_hdr[2];

	info = kzalloc(माप(काष्ठा smbd_connection), GFP_KERNEL);
	अगर (!info)
		वापस शून्य;

	info->transport_status = SMBD_CONNECTING;
	rc = smbd_ia_खोलो(info, dstaddr, port);
	अगर (rc) अणु
		log_rdma_event(INFO, "smbd_ia_open rc=%d\n", rc);
		जाओ create_id_failed;
	पूर्ण

	अगर (smbd_send_credit_target > info->id->device->attrs.max_cqe ||
	    smbd_send_credit_target > info->id->device->attrs.max_qp_wr) अणु
		log_rdma_event(ERR, "consider lowering send_credit_target = %d. Possible CQE overrun, device reporting max_cpe %d max_qp_wr %d\n",
			       smbd_send_credit_target,
			       info->id->device->attrs.max_cqe,
			       info->id->device->attrs.max_qp_wr);
		जाओ config_failed;
	पूर्ण

	अगर (smbd_receive_credit_max > info->id->device->attrs.max_cqe ||
	    smbd_receive_credit_max > info->id->device->attrs.max_qp_wr) अणु
		log_rdma_event(ERR, "consider lowering receive_credit_max = %d. Possible CQE overrun, device reporting max_cpe %d max_qp_wr %d\n",
			       smbd_receive_credit_max,
			       info->id->device->attrs.max_cqe,
			       info->id->device->attrs.max_qp_wr);
		जाओ config_failed;
	पूर्ण

	info->receive_credit_max = smbd_receive_credit_max;
	info->send_credit_target = smbd_send_credit_target;
	info->max_send_size = smbd_max_send_size;
	info->max_fragmented_recv_size = smbd_max_fragmented_recv_size;
	info->max_receive_size = smbd_max_receive_size;
	info->keep_alive_पूर्णांकerval = smbd_keep_alive_पूर्णांकerval;

	अगर (info->id->device->attrs.max_send_sge < SMBसूचीECT_MAX_SGE) अणु
		log_rdma_event(ERR,
			"warning: device max_send_sge = %d too small\n",
			info->id->device->attrs.max_send_sge);
		log_rdma_event(ERR, "Queue Pair creation may fail\n");
	पूर्ण
	अगर (info->id->device->attrs.max_recv_sge < SMBसूचीECT_MAX_SGE) अणु
		log_rdma_event(ERR,
			"warning: device max_recv_sge = %d too small\n",
			info->id->device->attrs.max_recv_sge);
		log_rdma_event(ERR, "Queue Pair creation may fail\n");
	पूर्ण

	info->send_cq = शून्य;
	info->recv_cq = शून्य;
	info->send_cq =
		ib_alloc_cq_any(info->id->device, info,
				info->send_credit_target, IB_POLL_SOFTIRQ);
	अगर (IS_ERR(info->send_cq)) अणु
		info->send_cq = शून्य;
		जाओ alloc_cq_failed;
	पूर्ण

	info->recv_cq =
		ib_alloc_cq_any(info->id->device, info,
				info->receive_credit_max, IB_POLL_SOFTIRQ);
	अगर (IS_ERR(info->recv_cq)) अणु
		info->recv_cq = शून्य;
		जाओ alloc_cq_failed;
	पूर्ण

	स_रखो(&qp_attr, 0, माप(qp_attr));
	qp_attr.event_handler = smbd_qp_async_error_upcall;
	qp_attr.qp_context = info;
	qp_attr.cap.max_send_wr = info->send_credit_target;
	qp_attr.cap.max_recv_wr = info->receive_credit_max;
	qp_attr.cap.max_send_sge = SMBसूचीECT_MAX_SGE;
	qp_attr.cap.max_recv_sge = SMBसूचीECT_MAX_SGE;
	qp_attr.cap.max_अंतरभूत_data = 0;
	qp_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	qp_attr.qp_type = IB_QPT_RC;
	qp_attr.send_cq = info->send_cq;
	qp_attr.recv_cq = info->recv_cq;
	qp_attr.port_num = ~0;

	rc = rdma_create_qp(info->id, info->pd, &qp_attr);
	अगर (rc) अणु
		log_rdma_event(ERR, "rdma_create_qp failed %i\n", rc);
		जाओ create_qp_failed;
	पूर्ण

	स_रखो(&conn_param, 0, माप(conn_param));
	conn_param.initiator_depth = 0;

	conn_param.responder_resources =
		info->id->device->attrs.max_qp_rd_atom
			< SMBD_CM_RESPONDER_RESOURCES ?
		info->id->device->attrs.max_qp_rd_atom :
		SMBD_CM_RESPONDER_RESOURCES;
	info->responder_resources = conn_param.responder_resources;
	log_rdma_mr(INFO, "responder_resources=%d\n",
		info->responder_resources);

	/* Need to send IRD/ORD in निजी data क्रम iWARP */
	info->id->device->ops.get_port_immutable(
		info->id->device, info->id->port_num, &port_immutable);
	अगर (port_immutable.core_cap_flags & RDMA_CORE_PORT_IWARP) अणु
		ird_ord_hdr[0] = info->responder_resources;
		ird_ord_hdr[1] = 1;
		conn_param.निजी_data = ird_ord_hdr;
		conn_param.निजी_data_len = माप(ird_ord_hdr);
	पूर्ण अन्यथा अणु
		conn_param.निजी_data = शून्य;
		conn_param.निजी_data_len = 0;
	पूर्ण

	conn_param.retry_count = SMBD_CM_RETRY;
	conn_param.rnr_retry_count = SMBD_CM_RNR_RETRY;
	conn_param.flow_control = 0;

	log_rdma_event(INFO, "connecting to IP %pI4 port %d\n",
		&addr_in->sin_addr, port);

	init_रुकोqueue_head(&info->conn_रुको);
	init_रुकोqueue_head(&info->disconn_रुको);
	init_रुकोqueue_head(&info->रुको_reassembly_queue);
	rc = rdma_connect(info->id, &conn_param);
	अगर (rc) अणु
		log_rdma_event(ERR, "rdma_connect() failed with %i\n", rc);
		जाओ rdma_connect_failed;
	पूर्ण

	रुको_event_पूर्णांकerruptible(
		info->conn_रुको, info->transport_status != SMBD_CONNECTING);

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		log_rdma_event(ERR, "rdma_connect failed port=%d\n", port);
		जाओ rdma_connect_failed;
	पूर्ण

	log_rdma_event(INFO, "rdma_connect connected\n");

	rc = allocate_caches_and_workqueue(info);
	अगर (rc) अणु
		log_rdma_event(ERR, "cache allocation failed\n");
		जाओ allocate_cache_failed;
	पूर्ण

	init_रुकोqueue_head(&info->रुको_send_queue);
	INIT_DELAYED_WORK(&info->idle_समयr_work, idle_connection_समयr);
	queue_delayed_work(info->workqueue, &info->idle_समयr_work,
		info->keep_alive_पूर्णांकerval*HZ);

	init_रुकोqueue_head(&info->रुको_send_pending);
	atomic_set(&info->send_pending, 0);

	init_रुकोqueue_head(&info->रुको_post_send);

	INIT_WORK(&info->disconnect_work, smbd_disconnect_rdma_work);
	INIT_WORK(&info->post_send_credits_work, smbd_post_send_credits);
	info->new_credits_offered = 0;
	spin_lock_init(&info->lock_new_credits_offered);

	rc = smbd_negotiate(info);
	अगर (rc) अणु
		log_rdma_event(ERR, "smbd_negotiate rc=%d\n", rc);
		जाओ negotiation_failed;
	पूर्ण

	rc = allocate_mr_list(info);
	अगर (rc) अणु
		log_rdma_mr(ERR, "memory registration allocation failed\n");
		जाओ allocate_mr_failed;
	पूर्ण

	वापस info;

allocate_mr_failed:
	/* At this poपूर्णांक, need to a full transport shutकरोwn */
	smbd_destroy(server);
	वापस शून्य;

negotiation_failed:
	cancel_delayed_work_sync(&info->idle_समयr_work);
	destroy_caches_and_workqueue(info);
	info->transport_status = SMBD_NEGOTIATE_FAILED;
	init_रुकोqueue_head(&info->conn_रुको);
	rdma_disconnect(info->id);
	रुको_event(info->conn_रुको,
		info->transport_status == SMBD_DISCONNECTED);

allocate_cache_failed:
rdma_connect_failed:
	rdma_destroy_qp(info->id);

create_qp_failed:
alloc_cq_failed:
	अगर (info->send_cq)
		ib_मुक्त_cq(info->send_cq);
	अगर (info->recv_cq)
		ib_मुक्त_cq(info->recv_cq);

config_failed:
	ib_dealloc_pd(info->pd);
	rdma_destroy_id(info->id);

create_id_failed:
	kमुक्त(info);
	वापस शून्य;
पूर्ण

काष्ठा smbd_connection *smbd_get_connection(
	काष्ठा TCP_Server_Info *server, काष्ठा sockaddr *dstaddr)
अणु
	काष्ठा smbd_connection *ret;
	पूर्णांक port = SMBD_PORT;

try_again:
	ret = _smbd_get_connection(server, dstaddr, port);

	/* Try SMB_PORT अगर SMBD_PORT करोesn't work */
	अगर (!ret && port == SMBD_PORT) अणु
		port = SMB_PORT;
		जाओ try_again;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Receive data from receive reassembly queue
 * All the incoming data packets are placed in reassembly queue
 * buf: the buffer to पढ़ो data पूर्णांकo
 * size: the length of data to पढ़ो
 * वापस value: actual data पढ़ो
 * Note: this implementation copies the data from reassebmly queue to receive
 * buffers used by upper layer. This is not the optimal code path. A better way
 * to करो it is to not have upper layer allocate its receive buffers but rather
 * borrow the buffer from reassembly queue, and वापस it after data is
 * consumed. But this will require more changes to upper layer code, and also
 * need to consider packet boundaries जबतक they still being reassembled.
 */
अटल पूर्णांक smbd_recv_buf(काष्ठा smbd_connection *info, अक्षर *buf,
		अचिन्हित पूर्णांक size)
अणु
	काष्ठा smbd_response *response;
	काष्ठा smbd_data_transfer *data_transfer;
	पूर्णांक to_copy, to_पढ़ो, data_पढ़ो, offset;
	u32 data_length, reमुख्यing_data_length, data_offset;
	पूर्णांक rc;

again:
	/*
	 * No need to hold the reassembly queue lock all the समय as we are
	 * the only one पढ़ोing from the front of the queue. The transport
	 * may add more entries to the back of the queue at the same समय
	 */
	log_पढ़ो(INFO, "size=%d info->reassembly_data_length=%d\n", size,
		info->reassembly_data_length);
	अगर (info->reassembly_data_length >= size) अणु
		पूर्णांक queue_length;
		पूर्णांक queue_हटाओd = 0;

		/*
		 * Need to make sure reassembly_data_length is पढ़ो beक्रमe
		 * पढ़ोing reassembly_queue_length and calling
		 * _get_first_reassembly. This call is lock मुक्त
		 * as we never पढ़ो at the end of the queue which are being
		 * updated in SOFTIRQ as more data is received
		 */
		virt_rmb();
		queue_length = info->reassembly_queue_length;
		data_पढ़ो = 0;
		to_पढ़ो = size;
		offset = info->first_entry_offset;
		जबतक (data_पढ़ो < size) अणु
			response = _get_first_reassembly(info);
			data_transfer = smbd_response_payload(response);
			data_length = le32_to_cpu(data_transfer->data_length);
			reमुख्यing_data_length =
				le32_to_cpu(
					data_transfer->reमुख्यing_data_length);
			data_offset = le32_to_cpu(data_transfer->data_offset);

			/*
			 * The upper layer expects RFC1002 length at the
			 * beginning of the payload. Return it to indicate
			 * the total length of the packet. This minimize the
			 * change to upper layer packet processing logic. This
			 * will be eventually हटाओ when an पूर्णांकermediate
			 * transport layer is added
			 */
			अगर (response->first_segment && size == 4) अणु
				अचिन्हित पूर्णांक rfc1002_len =
					data_length + reमुख्यing_data_length;
				*((__be32 *)buf) = cpu_to_be32(rfc1002_len);
				data_पढ़ो = 4;
				response->first_segment = false;
				log_पढ़ो(INFO, "returning rfc1002 length %d\n",
					rfc1002_len);
				जाओ पढ़ो_rfc1002_करोne;
			पूर्ण

			to_copy = min_t(पूर्णांक, data_length - offset, to_पढ़ो);
			स_नकल(
				buf + data_पढ़ो,
				(अक्षर *)data_transfer + data_offset + offset,
				to_copy);

			/* move on to the next buffer? */
			अगर (to_copy == data_length - offset) अणु
				queue_length--;
				/*
				 * No need to lock अगर we are not at the
				 * end of the queue
				 */
				अगर (queue_length)
					list_del(&response->list);
				अन्यथा अणु
					spin_lock_irq(
						&info->reassembly_queue_lock);
					list_del(&response->list);
					spin_unlock_irq(
						&info->reassembly_queue_lock);
				पूर्ण
				queue_हटाओd++;
				info->count_reassembly_queue--;
				info->count_dequeue_reassembly_queue++;
				put_receive_buffer(info, response);
				offset = 0;
				log_पढ़ो(INFO, "put_receive_buffer offset=0\n");
			पूर्ण अन्यथा
				offset += to_copy;

			to_पढ़ो -= to_copy;
			data_पढ़ो += to_copy;

			log_पढ़ो(INFO, "_get_first_reassembly memcpy %d bytes data_transfer_length-offset=%d after that to_read=%d data_read=%d offset=%d\n",
				 to_copy, data_length - offset,
				 to_पढ़ो, data_पढ़ो, offset);
		पूर्ण

		spin_lock_irq(&info->reassembly_queue_lock);
		info->reassembly_data_length -= data_पढ़ो;
		info->reassembly_queue_length -= queue_हटाओd;
		spin_unlock_irq(&info->reassembly_queue_lock);

		info->first_entry_offset = offset;
		log_पढ़ो(INFO, "returning to thread data_read=%d reassembly_data_length=%d first_entry_offset=%d\n",
			 data_पढ़ो, info->reassembly_data_length,
			 info->first_entry_offset);
पढ़ो_rfc1002_करोne:
		वापस data_पढ़ो;
	पूर्ण

	log_पढ़ो(INFO, "wait_event on more data\n");
	rc = रुको_event_पूर्णांकerruptible(
		info->रुको_reassembly_queue,
		info->reassembly_data_length >= size ||
			info->transport_status != SMBD_CONNECTED);
	/* Don't वापस any data अगर पूर्णांकerrupted */
	अगर (rc)
		वापस rc;

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		log_पढ़ो(ERR, "disconnected\n");
		वापस -ECONNABORTED;
	पूर्ण

	जाओ again;
पूर्ण

/*
 * Receive a page from receive reassembly queue
 * page: the page to पढ़ो data पूर्णांकo
 * to_पढ़ो: the length of data to पढ़ो
 * वापस value: actual data पढ़ो
 */
अटल पूर्णांक smbd_recv_page(काष्ठा smbd_connection *info,
		काष्ठा page *page, अचिन्हित पूर्णांक page_offset,
		अचिन्हित पूर्णांक to_पढ़ो)
अणु
	पूर्णांक ret;
	अक्षर *to_address;
	व्योम *page_address;

	/* make sure we have the page पढ़ोy क्रम पढ़ो */
	ret = रुको_event_पूर्णांकerruptible(
		info->रुको_reassembly_queue,
		info->reassembly_data_length >= to_पढ़ो ||
			info->transport_status != SMBD_CONNECTED);
	अगर (ret)
		वापस ret;

	/* now we can पढ़ो from reassembly queue and not sleep */
	page_address = kmap_atomic(page);
	to_address = (अक्षर *) page_address + page_offset;

	log_पढ़ो(INFO, "reading from page=%p address=%p to_read=%d\n",
		page, to_address, to_पढ़ो);

	ret = smbd_recv_buf(info, to_address, to_पढ़ो);
	kunmap_atomic(page_address);

	वापस ret;
पूर्ण

/*
 * Receive data from transport
 * msg: a msghdr poपूर्णांक to the buffer, can be ITER_KVEC or ITER_BVEC
 * वापस: total bytes पढ़ो, or 0. SMB Direct will not करो partial पढ़ो.
 */
पूर्णांक smbd_recv(काष्ठा smbd_connection *info, काष्ठा msghdr *msg)
अणु
	अक्षर *buf;
	काष्ठा page *page;
	अचिन्हित पूर्णांक to_पढ़ो, page_offset;
	पूर्णांक rc;

	अगर (iov_iter_rw(&msg->msg_iter) == WRITE) अणु
		/* It's a bug in upper layer to get there */
		cअगरs_dbg(VFS, "Invalid msg iter dir %u\n",
			 iov_iter_rw(&msg->msg_iter));
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (iov_iter_type(&msg->msg_iter)) अणु
	हाल ITER_KVEC:
		buf = msg->msg_iter.kvec->iov_base;
		to_पढ़ो = msg->msg_iter.kvec->iov_len;
		rc = smbd_recv_buf(info, buf, to_पढ़ो);
		अवरोध;

	हाल ITER_BVEC:
		page = msg->msg_iter.bvec->bv_page;
		page_offset = msg->msg_iter.bvec->bv_offset;
		to_पढ़ो = msg->msg_iter.bvec->bv_len;
		rc = smbd_recv_page(info, page, page_offset, to_पढ़ो);
		अवरोध;

	शेष:
		/* It's a bug in upper layer to get there */
		cअगरs_dbg(VFS, "Invalid msg type %d\n",
			 iov_iter_type(&msg->msg_iter));
		rc = -EINVAL;
	पूर्ण

out:
	/* SMBDirect will पढ़ो it all or nothing */
	अगर (rc > 0)
		msg->msg_iter.count = 0;
	वापस rc;
पूर्ण

/*
 * Send data to transport
 * Each rqst is transported as a SMBDirect payload
 * rqst: the data to ग_लिखो
 * वापस value: 0 अगर successfully ग_लिखो, otherwise error code
 */
पूर्णांक smbd_send(काष्ठा TCP_Server_Info *server,
	पूर्णांक num_rqst, काष्ठा smb_rqst *rqst_array)
अणु
	काष्ठा smbd_connection *info = server->smbd_conn;
	काष्ठा kvec vec;
	पूर्णांक nvecs;
	पूर्णांक size;
	अचिन्हित पूर्णांक buflen, reमुख्यing_data_length;
	पूर्णांक start, i, j;
	पूर्णांक max_iov_size =
		info->max_send_size - माप(काष्ठा smbd_data_transfer);
	काष्ठा kvec *iov;
	पूर्णांक rc;
	काष्ठा smb_rqst *rqst;
	पूर्णांक rqst_idx;

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		rc = -EAGAIN;
		जाओ करोne;
	पूर्ण

	/*
	 * Add in the page array अगर there is one. The caller needs to set
	 * rq_tailsz to PAGE_SIZE when the buffer has multiple pages and
	 * ends at page boundary
	 */
	reमुख्यing_data_length = 0;
	क्रम (i = 0; i < num_rqst; i++)
		reमुख्यing_data_length += smb_rqst_len(server, &rqst_array[i]);

	अगर (reमुख्यing_data_length > info->max_fragmented_send_size) अणु
		log_ग_लिखो(ERR, "payload size %d > max size %d\n",
			reमुख्यing_data_length, info->max_fragmented_send_size);
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	log_ग_लिखो(INFO, "num_rqst=%d total length=%u\n",
			num_rqst, reमुख्यing_data_length);

	rqst_idx = 0;
next_rqst:
	rqst = &rqst_array[rqst_idx];
	iov = rqst->rq_iov;

	cअगरs_dbg(FYI, "Sending smb (RDMA): idx=%d smb_len=%lu\n",
		rqst_idx, smb_rqst_len(server, rqst));
	क्रम (i = 0; i < rqst->rq_nvec; i++)
		dump_smb(iov[i].iov_base, iov[i].iov_len);


	log_ग_लिखो(INFO, "rqst_idx=%d nvec=%d rqst->rq_npages=%d rq_pagesz=%d rq_tailsz=%d buflen=%lu\n",
		  rqst_idx, rqst->rq_nvec, rqst->rq_npages, rqst->rq_pagesz,
		  rqst->rq_tailsz, smb_rqst_len(server, rqst));

	start = i = 0;
	buflen = 0;
	जबतक (true) अणु
		buflen += iov[i].iov_len;
		अगर (buflen > max_iov_size) अणु
			अगर (i > start) अणु
				reमुख्यing_data_length -=
					(buflen-iov[i].iov_len);
				log_ग_लिखो(INFO, "sending iov[] from start=%d i=%d nvecs=%d remaining_data_length=%d\n",
					  start, i, i - start,
					  reमुख्यing_data_length);
				rc = smbd_post_send_data(
					info, &iov[start], i-start,
					reमुख्यing_data_length);
				अगर (rc)
					जाओ करोne;
			पूर्ण अन्यथा अणु
				/* iov[start] is too big, अवरोध it */
				nvecs = (buflen+max_iov_size-1)/max_iov_size;
				log_ग_लिखो(INFO, "iov[%d] iov_base=%p buflen=%d break to %d vectors\n",
					  start, iov[start].iov_base,
					  buflen, nvecs);
				क्रम (j = 0; j < nvecs; j++) अणु
					vec.iov_base =
						(अक्षर *)iov[start].iov_base +
						j*max_iov_size;
					vec.iov_len = max_iov_size;
					अगर (j == nvecs-1)
						vec.iov_len =
							buflen -
							max_iov_size*(nvecs-1);
					reमुख्यing_data_length -= vec.iov_len;
					log_ग_लिखो(INFO,
						"sending vec j=%d iov_base=%p iov_len=%zu remaining_data_length=%d\n",
						  j, vec.iov_base, vec.iov_len,
						  reमुख्यing_data_length);
					rc = smbd_post_send_data(
						info, &vec, 1,
						reमुख्यing_data_length);
					अगर (rc)
						जाओ करोne;
				पूर्ण
				i++;
				अगर (i == rqst->rq_nvec)
					अवरोध;
			पूर्ण
			start = i;
			buflen = 0;
		पूर्ण अन्यथा अणु
			i++;
			अगर (i == rqst->rq_nvec) अणु
				/* send out all reमुख्यing vecs */
				reमुख्यing_data_length -= buflen;
				log_ग_लिखो(INFO, "sending iov[] from start=%d i=%d nvecs=%d remaining_data_length=%d\n",
					  start, i, i - start,
					  reमुख्यing_data_length);
				rc = smbd_post_send_data(info, &iov[start],
					i-start, reमुख्यing_data_length);
				अगर (rc)
					जाओ करोne;
				अवरोध;
			पूर्ण
		पूर्ण
		log_ग_लिखो(INFO, "looping i=%d buflen=%d\n", i, buflen);
	पूर्ण

	/* now sending pages अगर there are any */
	क्रम (i = 0; i < rqst->rq_npages; i++) अणु
		अचिन्हित पूर्णांक offset;

		rqst_page_get_length(rqst, i, &buflen, &offset);
		nvecs = (buflen + max_iov_size - 1) / max_iov_size;
		log_ग_लिखो(INFO, "sending pages buflen=%d nvecs=%d\n",
			buflen, nvecs);
		क्रम (j = 0; j < nvecs; j++) अणु
			size = max_iov_size;
			अगर (j == nvecs-1)
				size = buflen - j*max_iov_size;
			reमुख्यing_data_length -= size;
			log_ग_लिखो(INFO, "sending pages i=%d offset=%d size=%d remaining_data_length=%d\n",
				  i, j * max_iov_size + offset, size,
				  reमुख्यing_data_length);
			rc = smbd_post_send_page(
				info, rqst->rq_pages[i],
				j*max_iov_size + offset,
				size, reमुख्यing_data_length);
			अगर (rc)
				जाओ करोne;
		पूर्ण
	पूर्ण

	rqst_idx++;
	अगर (rqst_idx < num_rqst)
		जाओ next_rqst;

करोne:
	/*
	 * As an optimization, we करोn't रुको क्रम inभागidual I/O to finish
	 * beक्रमe sending the next one.
	 * Send them all and रुको क्रम pending send count to get to 0
	 * that means all the I/Os have been out and we are good to वापस
	 */

	रुको_event(info->रुको_send_pending,
		atomic_पढ़ो(&info->send_pending) == 0);

	वापस rc;
पूर्ण

अटल व्योम रेजिस्टर_mr_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा smbd_mr *mr;
	काष्ठा ib_cqe *cqe;

	अगर (wc->status) अणु
		log_rdma_mr(ERR, "status=%d\n", wc->status);
		cqe = wc->wr_cqe;
		mr = container_of(cqe, काष्ठा smbd_mr, cqe);
		smbd_disconnect_rdma_connection(mr->conn);
	पूर्ण
पूर्ण

/*
 * The work queue function that recovers MRs
 * We need to call ib_dereg_mr() and ib_alloc_mr() beक्रमe this MR can be used
 * again. Both calls are slow, so finish them in a workqueue. This will not
 * block I/O path.
 * There is one workqueue that recovers MRs, there is no need to lock as the
 * I/O requests calling smbd_रेजिस्टर_mr will never update the links in the
 * mr_list.
 */
अटल व्योम smbd_mr_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smbd_connection *info =
		container_of(work, काष्ठा smbd_connection, mr_recovery_work);
	काष्ठा smbd_mr *smbdirect_mr;
	पूर्णांक rc;

	list_क्रम_each_entry(smbdirect_mr, &info->mr_list, list) अणु
		अगर (smbdirect_mr->state == MR_ERROR) अणु

			/* recover this MR entry */
			rc = ib_dereg_mr(smbdirect_mr->mr);
			अगर (rc) अणु
				log_rdma_mr(ERR,
					"ib_dereg_mr failed rc=%x\n",
					rc);
				smbd_disconnect_rdma_connection(info);
				जारी;
			पूर्ण

			smbdirect_mr->mr = ib_alloc_mr(
				info->pd, info->mr_type,
				info->max_frmr_depth);
			अगर (IS_ERR(smbdirect_mr->mr)) अणु
				log_rdma_mr(ERR, "ib_alloc_mr failed mr_type=%x max_frmr_depth=%x\n",
					    info->mr_type,
					    info->max_frmr_depth);
				smbd_disconnect_rdma_connection(info);
				जारी;
			पूर्ण
		पूर्ण अन्यथा
			/* This MR is being used, करोn't recover it */
			जारी;

		smbdirect_mr->state = MR_READY;

		/* smbdirect_mr->state is updated by this function
		 * and is पढ़ो and updated by I/O issuing CPUs trying
		 * to get a MR, the call to atomic_inc_वापस
		 * implicates a memory barrier and guarantees this
		 * value is updated beक्रमe waking up any calls to
		 * get_mr() from the I/O issuing CPUs
		 */
		अगर (atomic_inc_वापस(&info->mr_पढ़ोy_count) == 1)
			wake_up_पूर्णांकerruptible(&info->रुको_mr);
	पूर्ण
पूर्ण

अटल व्योम destroy_mr_list(काष्ठा smbd_connection *info)
अणु
	काष्ठा smbd_mr *mr, *पंचांगp;

	cancel_work_sync(&info->mr_recovery_work);
	list_क्रम_each_entry_safe(mr, पंचांगp, &info->mr_list, list) अणु
		अगर (mr->state == MR_INVALIDATED)
			ib_dma_unmap_sg(info->id->device, mr->sgl,
				mr->sgl_count, mr->dir);
		ib_dereg_mr(mr->mr);
		kमुक्त(mr->sgl);
		kमुक्त(mr);
	पूर्ण
पूर्ण

/*
 * Allocate MRs used क्रम RDMA पढ़ो/ग_लिखो
 * The number of MRs will not exceed hardware capability in responder_resources
 * All MRs are kept in mr_list. The MR can be recovered after it's used
 * Recovery is करोne in smbd_mr_recovery_work. The content of list entry changes
 * as MRs are used and recovered क्रम I/O, but the list links will not change
 */
अटल पूर्णांक allocate_mr_list(काष्ठा smbd_connection *info)
अणु
	पूर्णांक i;
	काष्ठा smbd_mr *smbdirect_mr, *पंचांगp;

	INIT_LIST_HEAD(&info->mr_list);
	init_रुकोqueue_head(&info->रुको_mr);
	spin_lock_init(&info->mr_list_lock);
	atomic_set(&info->mr_पढ़ोy_count, 0);
	atomic_set(&info->mr_used_count, 0);
	init_रुकोqueue_head(&info->रुको_क्रम_mr_cleanup);
	/* Allocate more MRs (2x) than hardware responder_resources */
	क्रम (i = 0; i < info->responder_resources * 2; i++) अणु
		smbdirect_mr = kzalloc(माप(*smbdirect_mr), GFP_KERNEL);
		अगर (!smbdirect_mr)
			जाओ out;
		smbdirect_mr->mr = ib_alloc_mr(info->pd, info->mr_type,
					info->max_frmr_depth);
		अगर (IS_ERR(smbdirect_mr->mr)) अणु
			log_rdma_mr(ERR, "ib_alloc_mr failed mr_type=%x max_frmr_depth=%x\n",
				    info->mr_type, info->max_frmr_depth);
			जाओ out;
		पूर्ण
		smbdirect_mr->sgl = kसुस्मृति(
					info->max_frmr_depth,
					माप(काष्ठा scatterlist),
					GFP_KERNEL);
		अगर (!smbdirect_mr->sgl) अणु
			log_rdma_mr(ERR, "failed to allocate sgl\n");
			ib_dereg_mr(smbdirect_mr->mr);
			जाओ out;
		पूर्ण
		smbdirect_mr->state = MR_READY;
		smbdirect_mr->conn = info;

		list_add_tail(&smbdirect_mr->list, &info->mr_list);
		atomic_inc(&info->mr_पढ़ोy_count);
	पूर्ण
	INIT_WORK(&info->mr_recovery_work, smbd_mr_recovery_work);
	वापस 0;

out:
	kमुक्त(smbdirect_mr);

	list_क्रम_each_entry_safe(smbdirect_mr, पंचांगp, &info->mr_list, list) अणु
		ib_dereg_mr(smbdirect_mr->mr);
		kमुक्त(smbdirect_mr->sgl);
		kमुक्त(smbdirect_mr);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/*
 * Get a MR from mr_list. This function रुकोs until there is at least one
 * MR available in the list. It may access the list जबतक the
 * smbd_mr_recovery_work is recovering the MR list. This करोesn't need a lock
 * as they never modअगरy the same places. However, there may be several CPUs
 * issueing I/O trying to get MR at the same समय, mr_list_lock is used to
 * protect this situation.
 */
अटल काष्ठा smbd_mr *get_mr(काष्ठा smbd_connection *info)
अणु
	काष्ठा smbd_mr *ret;
	पूर्णांक rc;
again:
	rc = रुको_event_पूर्णांकerruptible(info->रुको_mr,
		atomic_पढ़ो(&info->mr_पढ़ोy_count) ||
		info->transport_status != SMBD_CONNECTED);
	अगर (rc) अणु
		log_rdma_mr(ERR, "wait_event_interruptible rc=%x\n", rc);
		वापस शून्य;
	पूर्ण

	अगर (info->transport_status != SMBD_CONNECTED) अणु
		log_rdma_mr(ERR, "info->transport_status=%x\n",
			info->transport_status);
		वापस शून्य;
	पूर्ण

	spin_lock(&info->mr_list_lock);
	list_क्रम_each_entry(ret, &info->mr_list, list) अणु
		अगर (ret->state == MR_READY) अणु
			ret->state = MR_REGISTERED;
			spin_unlock(&info->mr_list_lock);
			atomic_dec(&info->mr_पढ़ोy_count);
			atomic_inc(&info->mr_used_count);
			वापस ret;
		पूर्ण
	पूर्ण

	spin_unlock(&info->mr_list_lock);
	/*
	 * It is possible that we could fail to get MR because other processes may
	 * try to acquire a MR at the same समय. If this is the हाल, retry it.
	 */
	जाओ again;
पूर्ण

/*
 * Register memory क्रम RDMA पढ़ो/ग_लिखो
 * pages[]: the list of pages to रेजिस्टर memory with
 * num_pages: the number of pages to रेजिस्टर
 * tailsz: अगर non-zero, the bytes to रेजिस्टर in the last page
 * writing: true अगर this is a RDMA ग_लिखो (SMB पढ़ो), false क्रम RDMA पढ़ो
 * need_invalidate: true अगर this MR needs to be locally invalidated after I/O
 * वापस value: the MR रेजिस्टरed, शून्य अगर failed.
 */
काष्ठा smbd_mr *smbd_रेजिस्टर_mr(
	काष्ठा smbd_connection *info, काष्ठा page *pages[], पूर्णांक num_pages,
	पूर्णांक offset, पूर्णांक tailsz, bool writing, bool need_invalidate)
अणु
	काष्ठा smbd_mr *smbdirect_mr;
	पूर्णांक rc, i;
	क्रमागत dma_data_direction dir;
	काष्ठा ib_reg_wr *reg_wr;

	अगर (num_pages > info->max_frmr_depth) अणु
		log_rdma_mr(ERR, "num_pages=%d max_frmr_depth=%d\n",
			num_pages, info->max_frmr_depth);
		वापस शून्य;
	पूर्ण

	smbdirect_mr = get_mr(info);
	अगर (!smbdirect_mr) अणु
		log_rdma_mr(ERR, "get_mr returning NULL\n");
		वापस शून्य;
	पूर्ण
	smbdirect_mr->need_invalidate = need_invalidate;
	smbdirect_mr->sgl_count = num_pages;
	sg_init_table(smbdirect_mr->sgl, num_pages);

	log_rdma_mr(INFO, "num_pages=0x%x offset=0x%x tailsz=0x%x\n",
			num_pages, offset, tailsz);

	अगर (num_pages == 1) अणु
		sg_set_page(&smbdirect_mr->sgl[0], pages[0], tailsz, offset);
		जाओ skip_multiple_pages;
	पूर्ण

	/* We have at least two pages to रेजिस्टर */
	sg_set_page(
		&smbdirect_mr->sgl[0], pages[0], PAGE_SIZE - offset, offset);
	i = 1;
	जबतक (i < num_pages - 1) अणु
		sg_set_page(&smbdirect_mr->sgl[i], pages[i], PAGE_SIZE, 0);
		i++;
	पूर्ण
	sg_set_page(&smbdirect_mr->sgl[i], pages[i],
		tailsz ? tailsz : PAGE_SIZE, 0);

skip_multiple_pages:
	dir = writing ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	smbdirect_mr->dir = dir;
	rc = ib_dma_map_sg(info->id->device, smbdirect_mr->sgl, num_pages, dir);
	अगर (!rc) अणु
		log_rdma_mr(ERR, "ib_dma_map_sg num_pages=%x dir=%x rc=%x\n",
			num_pages, dir, rc);
		जाओ dma_map_error;
	पूर्ण

	rc = ib_map_mr_sg(smbdirect_mr->mr, smbdirect_mr->sgl, num_pages,
		शून्य, PAGE_SIZE);
	अगर (rc != num_pages) अणु
		log_rdma_mr(ERR,
			"ib_map_mr_sg failed rc = %d num_pages = %x\n",
			rc, num_pages);
		जाओ map_mr_error;
	पूर्ण

	ib_update_fast_reg_key(smbdirect_mr->mr,
		ib_inc_rkey(smbdirect_mr->mr->rkey));
	reg_wr = &smbdirect_mr->wr;
	reg_wr->wr.opcode = IB_WR_REG_MR;
	smbdirect_mr->cqe.करोne = रेजिस्टर_mr_करोne;
	reg_wr->wr.wr_cqe = &smbdirect_mr->cqe;
	reg_wr->wr.num_sge = 0;
	reg_wr->wr.send_flags = IB_SEND_SIGNALED;
	reg_wr->mr = smbdirect_mr->mr;
	reg_wr->key = smbdirect_mr->mr->rkey;
	reg_wr->access = writing ?
			IB_ACCESS_REMOTE_WRITE | IB_ACCESS_LOCAL_WRITE :
			IB_ACCESS_REMOTE_READ;

	/*
	 * There is no need क्रम रुकोing क्रम complemtion on ib_post_send
	 * on IB_WR_REG_MR. Hardware enक्रमces a barrier and order of execution
	 * on the next ib_post_send when we actaully send I/O to remote peer
	 */
	rc = ib_post_send(info->id->qp, &reg_wr->wr, शून्य);
	अगर (!rc)
		वापस smbdirect_mr;

	log_rdma_mr(ERR, "ib_post_send failed rc=%x reg_wr->key=%x\n",
		rc, reg_wr->key);

	/* If all failed, attempt to recover this MR by setting it MR_ERROR*/
map_mr_error:
	ib_dma_unmap_sg(info->id->device, smbdirect_mr->sgl,
		smbdirect_mr->sgl_count, smbdirect_mr->dir);

dma_map_error:
	smbdirect_mr->state = MR_ERROR;
	अगर (atomic_dec_and_test(&info->mr_used_count))
		wake_up(&info->रुको_क्रम_mr_cleanup);

	smbd_disconnect_rdma_connection(info);

	वापस शून्य;
पूर्ण

अटल व्योम local_inv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा smbd_mr *smbdirect_mr;
	काष्ठा ib_cqe *cqe;

	cqe = wc->wr_cqe;
	smbdirect_mr = container_of(cqe, काष्ठा smbd_mr, cqe);
	smbdirect_mr->state = MR_INVALIDATED;
	अगर (wc->status != IB_WC_SUCCESS) अणु
		log_rdma_mr(ERR, "invalidate failed status=%x\n", wc->status);
		smbdirect_mr->state = MR_ERROR;
	पूर्ण
	complete(&smbdirect_mr->invalidate_करोne);
पूर्ण

/*
 * Deरेजिस्टर a MR after I/O is करोne
 * This function may रुको अगर remote invalidation is not used
 * and we have to locally invalidate the buffer to prevent data is being
 * modअगरied by remote peer after upper layer consumes it
 */
पूर्णांक smbd_deरेजिस्टर_mr(काष्ठा smbd_mr *smbdirect_mr)
अणु
	काष्ठा ib_send_wr *wr;
	काष्ठा smbd_connection *info = smbdirect_mr->conn;
	पूर्णांक rc = 0;

	अगर (smbdirect_mr->need_invalidate) अणु
		/* Need to finish local invalidation beक्रमe वापसing */
		wr = &smbdirect_mr->inv_wr;
		wr->opcode = IB_WR_LOCAL_INV;
		smbdirect_mr->cqe.करोne = local_inv_करोne;
		wr->wr_cqe = &smbdirect_mr->cqe;
		wr->num_sge = 0;
		wr->ex.invalidate_rkey = smbdirect_mr->mr->rkey;
		wr->send_flags = IB_SEND_SIGNALED;

		init_completion(&smbdirect_mr->invalidate_करोne);
		rc = ib_post_send(info->id->qp, wr, शून्य);
		अगर (rc) अणु
			log_rdma_mr(ERR, "ib_post_send failed rc=%x\n", rc);
			smbd_disconnect_rdma_connection(info);
			जाओ करोne;
		पूर्ण
		रुको_क्रम_completion(&smbdirect_mr->invalidate_करोne);
		smbdirect_mr->need_invalidate = false;
	पूर्ण अन्यथा
		/*
		 * For remote invalidation, just set it to MR_INVALIDATED
		 * and defer to mr_recovery_work to recover the MR क्रम next use
		 */
		smbdirect_mr->state = MR_INVALIDATED;

	अगर (smbdirect_mr->state == MR_INVALIDATED) अणु
		ib_dma_unmap_sg(
			info->id->device, smbdirect_mr->sgl,
			smbdirect_mr->sgl_count,
			smbdirect_mr->dir);
		smbdirect_mr->state = MR_READY;
		अगर (atomic_inc_वापस(&info->mr_पढ़ोy_count) == 1)
			wake_up_पूर्णांकerruptible(&info->रुको_mr);
	पूर्ण अन्यथा
		/*
		 * Schedule the work to करो MR recovery क्रम future I/Os MR
		 * recovery is slow and करोn't want it to block current I/O
		 */
		queue_work(info->workqueue, &info->mr_recovery_work);

करोne:
	अगर (atomic_dec_and_test(&info->mr_used_count))
		wake_up(&info->रुको_क्रम_mr_cleanup);

	वापस rc;
पूर्ण
