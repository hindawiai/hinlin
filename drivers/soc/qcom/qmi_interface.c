<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/qrtr.h>
#समावेश <linux/net.h>
#समावेश <linux/completion.h>
#समावेश <linux/idr.h>
#समावेश <linux/माला.स>
#समावेश <net/sock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/soc/qcom/qmi.h>

अटल काष्ठा socket *qmi_sock_create(काष्ठा qmi_handle *qmi,
				      काष्ठा sockaddr_qrtr *sq);

/**
 * qmi_recv_new_server() - handler of NEW_SERVER control message
 * @qmi:	qmi handle
 * @service:	service id of the new server
 * @instance:	instance id of the new server
 * @node:	node of the new server
 * @port:	port of the new server
 *
 * Calls the new_server callback to inक्रमm the client about a newly रेजिस्टरed
 * server matching the currently रेजिस्टरed service lookup.
 */
अटल व्योम qmi_recv_new_server(काष्ठा qmi_handle *qmi,
				अचिन्हित पूर्णांक service, अचिन्हित पूर्णांक instance,
				अचिन्हित पूर्णांक node, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qmi_ops *ops = &qmi->ops;
	काष्ठा qmi_service *svc;
	पूर्णांक ret;

	अगर (!ops->new_server)
		वापस;

	/* Ignore खातापूर्ण marker */
	अगर (!node && !port)
		वापस;

	svc = kzalloc(माप(*svc), GFP_KERNEL);
	अगर (!svc)
		वापस;

	svc->service = service;
	svc->version = instance & 0xff;
	svc->instance = instance >> 8;
	svc->node = node;
	svc->port = port;

	ret = ops->new_server(qmi, svc);
	अगर (ret < 0)
		kमुक्त(svc);
	अन्यथा
		list_add(&svc->list_node, &qmi->lookup_results);
पूर्ण

/**
 * qmi_recv_del_server() - handler of DEL_SERVER control message
 * @qmi:	qmi handle
 * @node:	node of the dying server, a value of -1 matches all nodes
 * @port:	port of the dying server, a value of -1 matches all ports
 *
 * Calls the del_server callback क्रम each previously seen server, allowing the
 * client to react to the disappearing server.
 */
अटल व्योम qmi_recv_del_server(काष्ठा qmi_handle *qmi,
				अचिन्हित पूर्णांक node, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qmi_ops *ops = &qmi->ops;
	काष्ठा qmi_service *svc;
	काष्ठा qmi_service *पंचांगp;

	list_क्रम_each_entry_safe(svc, पंचांगp, &qmi->lookup_results, list_node) अणु
		अगर (node != -1 && svc->node != node)
			जारी;
		अगर (port != -1 && svc->port != port)
			जारी;

		अगर (ops->del_server)
			ops->del_server(qmi, svc);

		list_del(&svc->list_node);
		kमुक्त(svc);
	पूर्ण
पूर्ण

/**
 * qmi_recv_bye() - handler of BYE control message
 * @qmi:	qmi handle
 * @node:	id of the dying node
 *
 * Signals the client that all previously रेजिस्टरed services on this node are
 * now gone and then calls the bye callback to allow the client client further
 * cleaning up resources associated with this remote.
 */
अटल व्योम qmi_recv_bye(काष्ठा qmi_handle *qmi,
			 अचिन्हित पूर्णांक node)
अणु
	काष्ठा qmi_ops *ops = &qmi->ops;

	qmi_recv_del_server(qmi, node, -1);

	अगर (ops->bye)
		ops->bye(qmi, node);
पूर्ण

/**
 * qmi_recv_del_client() - handler of DEL_CLIENT control message
 * @qmi:	qmi handle
 * @node:	node of the dying client
 * @port:	port of the dying client
 *
 * Signals the client about a dying client, by calling the del_client callback.
 */
अटल व्योम qmi_recv_del_client(काष्ठा qmi_handle *qmi,
				अचिन्हित पूर्णांक node, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qmi_ops *ops = &qmi->ops;

	अगर (ops->del_client)
		ops->del_client(qmi, node, port);
पूर्ण

अटल व्योम qmi_recv_ctrl_pkt(काष्ठा qmi_handle *qmi,
			      स्थिर व्योम *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा qrtr_ctrl_pkt *pkt = buf;

	अगर (len < माप(काष्ठा qrtr_ctrl_pkt)) अणु
		pr_debug("ignoring short control packet\n");
		वापस;
	पूर्ण

	चयन (le32_to_cpu(pkt->cmd)) अणु
	हाल QRTR_TYPE_BYE:
		qmi_recv_bye(qmi, le32_to_cpu(pkt->client.node));
		अवरोध;
	हाल QRTR_TYPE_NEW_SERVER:
		qmi_recv_new_server(qmi,
				    le32_to_cpu(pkt->server.service),
				    le32_to_cpu(pkt->server.instance),
				    le32_to_cpu(pkt->server.node),
				    le32_to_cpu(pkt->server.port));
		अवरोध;
	हाल QRTR_TYPE_DEL_SERVER:
		qmi_recv_del_server(qmi,
				    le32_to_cpu(pkt->server.node),
				    le32_to_cpu(pkt->server.port));
		अवरोध;
	हाल QRTR_TYPE_DEL_CLIENT:
		qmi_recv_del_client(qmi,
				    le32_to_cpu(pkt->client.node),
				    le32_to_cpu(pkt->client.port));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qmi_send_new_lookup(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc)
अणु
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा kvec iv = अणु &pkt, माप(pkt) पूर्ण;
	पूर्णांक ret;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_NEW_LOOKUP);
	pkt.server.service = cpu_to_le32(svc->service);
	pkt.server.instance = cpu_to_le32(svc->version | svc->instance << 8);

	sq.sq_family = qmi->sq.sq_family;
	sq.sq_node = qmi->sq.sq_node;
	sq.sq_port = QRTR_PORT_CTRL;

	msg.msg_name = &sq;
	msg.msg_namelen = माप(sq);

	mutex_lock(&qmi->sock_lock);
	अगर (qmi->sock) अणु
		ret = kernel_sendmsg(qmi->sock, &msg, &iv, 1, माप(pkt));
		अगर (ret < 0)
			pr_err("failed to send lookup registration: %d\n", ret);
	पूर्ण
	mutex_unlock(&qmi->sock_lock);
पूर्ण

/**
 * qmi_add_lookup() - रेजिस्टर a new lookup with the name service
 * @qmi:	qmi handle
 * @service:	service id of the request
 * @instance:	instance id of the request
 * @version:	version number of the request
 *
 * Registering a lookup query with the name server will cause the name server
 * to send NEW_SERVER and DEL_SERVER control messages to this socket as
 * matching services are रेजिस्टरed.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक qmi_add_lookup(काष्ठा qmi_handle *qmi, अचिन्हित पूर्णांक service,
		   अचिन्हित पूर्णांक version, अचिन्हित पूर्णांक instance)
अणु
	काष्ठा qmi_service *svc;

	svc = kzalloc(माप(*svc), GFP_KERNEL);
	अगर (!svc)
		वापस -ENOMEM;

	svc->service = service;
	svc->version = version;
	svc->instance = instance;

	list_add(&svc->list_node, &qmi->lookups);

	qmi_send_new_lookup(qmi, svc);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qmi_add_lookup);

अटल व्योम qmi_send_new_server(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc)
अणु
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा kvec iv = अणु &pkt, माप(pkt) पूर्ण;
	पूर्णांक ret;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_NEW_SERVER);
	pkt.server.service = cpu_to_le32(svc->service);
	pkt.server.instance = cpu_to_le32(svc->version | svc->instance << 8);
	pkt.server.node = cpu_to_le32(qmi->sq.sq_node);
	pkt.server.port = cpu_to_le32(qmi->sq.sq_port);

	sq.sq_family = qmi->sq.sq_family;
	sq.sq_node = qmi->sq.sq_node;
	sq.sq_port = QRTR_PORT_CTRL;

	msg.msg_name = &sq;
	msg.msg_namelen = माप(sq);

	mutex_lock(&qmi->sock_lock);
	अगर (qmi->sock) अणु
		ret = kernel_sendmsg(qmi->sock, &msg, &iv, 1, माप(pkt));
		अगर (ret < 0)
			pr_err("send service registration failed: %d\n", ret);
	पूर्ण
	mutex_unlock(&qmi->sock_lock);
पूर्ण

/**
 * qmi_add_server() - रेजिस्टर a service with the name service
 * @qmi:	qmi handle
 * @service:	type of the service
 * @instance:	instance of the service
 * @version:	version of the service
 *
 * Register a new service with the name service. This allows clients to find
 * and start sending messages to the client associated with @qmi.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक qmi_add_server(काष्ठा qmi_handle *qmi, अचिन्हित पूर्णांक service,
		   अचिन्हित पूर्णांक version, अचिन्हित पूर्णांक instance)
अणु
	काष्ठा qmi_service *svc;

	svc = kzalloc(माप(*svc), GFP_KERNEL);
	अगर (!svc)
		वापस -ENOMEM;

	svc->service = service;
	svc->version = version;
	svc->instance = instance;

	list_add(&svc->list_node, &qmi->services);

	qmi_send_new_server(qmi, svc);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qmi_add_server);

/**
 * qmi_txn_init() - allocate transaction id within the given QMI handle
 * @qmi:	QMI handle
 * @txn:	transaction context
 * @ei:		description of how to decode a matching response (optional)
 * @c_काष्ठा:	poपूर्णांकer to the object to decode the response पूर्णांकo (optional)
 *
 * This allocates a transaction id within the QMI handle. If @ei and @c_काष्ठा
 * are specअगरied any responses to this transaction will be decoded as described
 * by @ei पूर्णांकo @c_काष्ठा.
 *
 * A client calling qmi_txn_init() must call either qmi_txn_रुको() or
 * qmi_txn_cancel() to मुक्त up the allocated resources.
 *
 * Return: Transaction id on success, negative त्रुटि_सं on failure.
 */
पूर्णांक qmi_txn_init(काष्ठा qmi_handle *qmi, काष्ठा qmi_txn *txn,
		 काष्ठा qmi_elem_info *ei, व्योम *c_काष्ठा)
अणु
	पूर्णांक ret;

	स_रखो(txn, 0, माप(*txn));

	mutex_init(&txn->lock);
	init_completion(&txn->completion);
	txn->qmi = qmi;
	txn->ei = ei;
	txn->dest = c_काष्ठा;

	mutex_lock(&qmi->txn_lock);
	ret = idr_alloc_cyclic(&qmi->txns, txn, 0, U16_MAX, GFP_KERNEL);
	अगर (ret < 0)
		pr_err("failed to allocate transaction id\n");

	txn->id = ret;
	mutex_unlock(&qmi->txn_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qmi_txn_init);

/**
 * qmi_txn_रुको() - रुको क्रम a response on a transaction
 * @txn:	transaction handle
 * @समयout:	समयout, in jअगरfies
 *
 * If the transaction is decoded by the means of @ei and @c_काष्ठा the वापस
 * value will be the वापसed value of qmi_decode_message(), otherwise it's up
 * to the specअगरied message handler to fill out the result.
 *
 * Return: the transaction response on success, negative त्रुटि_सं on failure.
 */
पूर्णांक qmi_txn_रुको(काष्ठा qmi_txn *txn, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा qmi_handle *qmi = txn->qmi;
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&txn->completion, समयout);

	mutex_lock(&qmi->txn_lock);
	mutex_lock(&txn->lock);
	idr_हटाओ(&qmi->txns, txn->id);
	mutex_unlock(&txn->lock);
	mutex_unlock(&qmi->txn_lock);

	अगर (ret == 0)
		वापस -ETIMEDOUT;
	अन्यथा
		वापस txn->result;
पूर्ण
EXPORT_SYMBOL(qmi_txn_रुको);

/**
 * qmi_txn_cancel() - cancel an ongoing transaction
 * @txn:	transaction id
 */
व्योम qmi_txn_cancel(काष्ठा qmi_txn *txn)
अणु
	काष्ठा qmi_handle *qmi = txn->qmi;

	mutex_lock(&qmi->txn_lock);
	mutex_lock(&txn->lock);
	idr_हटाओ(&qmi->txns, txn->id);
	mutex_unlock(&txn->lock);
	mutex_unlock(&qmi->txn_lock);
पूर्ण
EXPORT_SYMBOL(qmi_txn_cancel);

/**
 * qmi_invoke_handler() - find and invoke a handler क्रम a message
 * @qmi:	qmi handle
 * @sq:		sockaddr of the sender
 * @txn:	transaction object क्रम the message
 * @buf:	buffer containing the message
 * @len:	length of @buf
 *
 * Find handler and invoke handler क्रम the incoming message.
 */
अटल व्योम qmi_invoke_handler(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			       काष्ठा qmi_txn *txn, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा qmi_msg_handler *handler;
	स्थिर काष्ठा qmi_header *hdr = buf;
	व्योम *dest;
	पूर्णांक ret;

	अगर (!qmi->handlers)
		वापस;

	क्रम (handler = qmi->handlers; handler->fn; handler++) अणु
		अगर (handler->type == hdr->type &&
		    handler->msg_id == hdr->msg_id)
			अवरोध;
	पूर्ण

	अगर (!handler->fn)
		वापस;

	dest = kzalloc(handler->decoded_size, GFP_KERNEL);
	अगर (!dest)
		वापस;

	ret = qmi_decode_message(buf, len, handler->ei, dest);
	अगर (ret < 0)
		pr_err("failed to decode incoming message\n");
	अन्यथा
		handler->fn(qmi, sq, txn, dest);

	kमुक्त(dest);
पूर्ण

/**
 * qmi_handle_net_reset() - invoked to handle ENETRESET on a QMI handle
 * @qmi:	the QMI context
 *
 * As a result of रेजिस्टरing a name service with the QRTR all खोलो sockets are
 * flagged with ENETRESET and this function will be called. The typical हाल is
 * the initial boot, where this संकेतs that the local node id has been
 * configured and as such any bound sockets needs to be rebound. So बंद the
 * socket, inक्रमm the client and re-initialize the socket.
 *
 * For clients it's generally sufficient to react to the del_server callbacks,
 * but server code is expected to treat the net_reset callback as a "bye" from
 * all nodes.
 *
 * Finally the QMI handle will send out registration requests क्रम any lookups
 * and services.
 */
अटल व्योम qmi_handle_net_reset(काष्ठा qmi_handle *qmi)
अणु
	काष्ठा sockaddr_qrtr sq;
	काष्ठा qmi_service *svc;
	काष्ठा socket *sock;

	sock = qmi_sock_create(qmi, &sq);
	अगर (IS_ERR(sock))
		वापस;

	mutex_lock(&qmi->sock_lock);
	sock_release(qmi->sock);
	qmi->sock = शून्य;
	mutex_unlock(&qmi->sock_lock);

	qmi_recv_del_server(qmi, -1, -1);

	अगर (qmi->ops.net_reset)
		qmi->ops.net_reset(qmi);

	mutex_lock(&qmi->sock_lock);
	qmi->sock = sock;
	qmi->sq = sq;
	mutex_unlock(&qmi->sock_lock);

	list_क्रम_each_entry(svc, &qmi->lookups, list_node)
		qmi_send_new_lookup(qmi, svc);

	list_क्रम_each_entry(svc, &qmi->services, list_node)
		qmi_send_new_server(qmi, svc);
पूर्ण

अटल व्योम qmi_handle_message(काष्ठा qmi_handle *qmi,
			       काष्ठा sockaddr_qrtr *sq,
			       स्थिर व्योम *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा qmi_header *hdr;
	काष्ठा qmi_txn पंचांगp_txn;
	काष्ठा qmi_txn *txn = शून्य;
	पूर्णांक ret;

	अगर (len < माप(*hdr)) अणु
		pr_err("ignoring short QMI packet\n");
		वापस;
	पूर्ण

	hdr = buf;

	/* If this is a response, find the matching transaction handle */
	अगर (hdr->type == QMI_RESPONSE) अणु
		mutex_lock(&qmi->txn_lock);
		txn = idr_find(&qmi->txns, hdr->txn_id);

		/* Ignore unexpected responses */
		अगर (!txn) अणु
			mutex_unlock(&qmi->txn_lock);
			वापस;
		पूर्ण

		mutex_lock(&txn->lock);
		mutex_unlock(&qmi->txn_lock);

		अगर (txn->dest && txn->ei) अणु
			ret = qmi_decode_message(buf, len, txn->ei, txn->dest);
			अगर (ret < 0)
				pr_err("failed to decode incoming message\n");

			txn->result = ret;
			complete(&txn->completion);
		पूर्ण अन्यथा  अणु
			qmi_invoke_handler(qmi, sq, txn, buf, len);
		पूर्ण

		mutex_unlock(&txn->lock);
	पूर्ण अन्यथा अणु
		/* Create a txn based on the txn_id of the incoming message */
		स_रखो(&पंचांगp_txn, 0, माप(पंचांगp_txn));
		पंचांगp_txn.id = hdr->txn_id;

		qmi_invoke_handler(qmi, sq, &पंचांगp_txn, buf, len);
	पूर्ण
पूर्ण

अटल व्योम qmi_data_पढ़ोy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qmi_handle *qmi = container_of(work, काष्ठा qmi_handle, work);
	काष्ठा qmi_ops *ops = &qmi->ops;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा msghdr msg = अणु .msg_name = &sq, .msg_namelen = माप(sq) पूर्ण;
	काष्ठा kvec iv;
	sमाप_प्रकार msglen;

	क्रम (;;) अणु
		iv.iov_base = qmi->recv_buf;
		iv.iov_len = qmi->recv_buf_size;

		mutex_lock(&qmi->sock_lock);
		अगर (qmi->sock)
			msglen = kernel_recvmsg(qmi->sock, &msg, &iv, 1,
						iv.iov_len, MSG_DONTWAIT);
		अन्यथा
			msglen = -EPIPE;
		mutex_unlock(&qmi->sock_lock);
		अगर (msglen == -EAGAIN)
			अवरोध;

		अगर (msglen == -ENETRESET) अणु
			qmi_handle_net_reset(qmi);

			/* The old qmi->sock is gone, our work is करोne */
			अवरोध;
		पूर्ण

		अगर (msglen < 0) अणु
			pr_err("qmi recvmsg failed: %zd\n", msglen);
			अवरोध;
		पूर्ण

		अगर (sq.sq_node == qmi->sq.sq_node &&
		    sq.sq_port == QRTR_PORT_CTRL) अणु
			qmi_recv_ctrl_pkt(qmi, qmi->recv_buf, msglen);
		पूर्ण अन्यथा अगर (ops->msg_handler) अणु
			ops->msg_handler(qmi, &sq, qmi->recv_buf, msglen);
		पूर्ण अन्यथा अणु
			qmi_handle_message(qmi, &sq, qmi->recv_buf, msglen);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qmi_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा qmi_handle *qmi = sk->sk_user_data;

	/*
	 * This will be शून्य अगर we receive data जबतक being in
	 * qmi_handle_release()
	 */
	अगर (!qmi)
		वापस;

	queue_work(qmi->wq, &qmi->work);
पूर्ण

अटल काष्ठा socket *qmi_sock_create(काष्ठा qmi_handle *qmi,
				      काष्ठा sockaddr_qrtr *sq)
अणु
	काष्ठा socket *sock;
	पूर्णांक ret;

	ret = sock_create_kern(&init_net, AF_QIPCRTR, SOCK_DGRAM,
			       PF_QIPCRTR, &sock);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	ret = kernel_माला_लोockname(sock, (काष्ठा sockaddr *)sq);
	अगर (ret < 0) अणु
		sock_release(sock);
		वापस ERR_PTR(ret);
	पूर्ण

	sock->sk->sk_user_data = qmi;
	sock->sk->sk_data_पढ़ोy = qmi_data_पढ़ोy;
	sock->sk->sk_error_report = qmi_data_पढ़ोy;

	वापस sock;
पूर्ण

/**
 * qmi_handle_init() - initialize a QMI client handle
 * @qmi:	QMI handle to initialize
 * @recv_buf_size: maximum size of incoming message
 * @ops:	reference to callbacks क्रम QRTR notअगरications
 * @handlers:	शून्य-terminated list of QMI message handlers
 *
 * This initializes the QMI client handle to allow sending and receiving QMI
 * messages. As messages are received the appropriate handler will be invoked.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक qmi_handle_init(काष्ठा qmi_handle *qmi, माप_प्रकार recv_buf_size,
		    स्थिर काष्ठा qmi_ops *ops,
		    स्थिर काष्ठा qmi_msg_handler *handlers)
अणु
	पूर्णांक ret;

	mutex_init(&qmi->txn_lock);
	mutex_init(&qmi->sock_lock);

	idr_init(&qmi->txns);

	INIT_LIST_HEAD(&qmi->lookups);
	INIT_LIST_HEAD(&qmi->lookup_results);
	INIT_LIST_HEAD(&qmi->services);

	INIT_WORK(&qmi->work, qmi_data_पढ़ोy_work);

	qmi->handlers = handlers;
	अगर (ops)
		qmi->ops = *ops;

	/* Make room क्रम the header */
	recv_buf_size += माप(काष्ठा qmi_header);
	/* Must also be sufficient to hold a control packet */
	अगर (recv_buf_size < माप(काष्ठा qrtr_ctrl_pkt))
		recv_buf_size = माप(काष्ठा qrtr_ctrl_pkt);

	qmi->recv_buf_size = recv_buf_size;
	qmi->recv_buf = kzalloc(recv_buf_size, GFP_KERNEL);
	अगर (!qmi->recv_buf)
		वापस -ENOMEM;

	qmi->wq = alloc_workqueue("qmi_msg_handler", WQ_UNBOUND, 1);
	अगर (!qmi->wq) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_recv_buf;
	पूर्ण

	qmi->sock = qmi_sock_create(qmi, &qmi->sq);
	अगर (IS_ERR(qmi->sock)) अणु
		अगर (PTR_ERR(qmi->sock) == -EAFNOSUPPORT) अणु
			ret = -EPROBE_DEFER;
		पूर्ण अन्यथा अणु
			pr_err("failed to create QMI socket\n");
			ret = PTR_ERR(qmi->sock);
		पूर्ण
		जाओ err_destroy_wq;
	पूर्ण

	वापस 0;

err_destroy_wq:
	destroy_workqueue(qmi->wq);
err_मुक्त_recv_buf:
	kमुक्त(qmi->recv_buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qmi_handle_init);

/**
 * qmi_handle_release() - release the QMI client handle
 * @qmi:	QMI client handle
 *
 * This बंदs the underlying socket and stops any handling of QMI messages.
 */
व्योम qmi_handle_release(काष्ठा qmi_handle *qmi)
अणु
	काष्ठा socket *sock = qmi->sock;
	काष्ठा qmi_service *svc, *पंचांगp;

	sock->sk->sk_user_data = शून्य;
	cancel_work_sync(&qmi->work);

	qmi_recv_del_server(qmi, -1, -1);

	mutex_lock(&qmi->sock_lock);
	sock_release(sock);
	qmi->sock = शून्य;
	mutex_unlock(&qmi->sock_lock);

	destroy_workqueue(qmi->wq);

	idr_destroy(&qmi->txns);

	kमुक्त(qmi->recv_buf);

	/* Free रेजिस्टरed lookup requests */
	list_क्रम_each_entry_safe(svc, पंचांगp, &qmi->lookups, list_node) अणु
		list_del(&svc->list_node);
		kमुक्त(svc);
	पूर्ण

	/* Free रेजिस्टरed service inक्रमmation */
	list_क्रम_each_entry_safe(svc, पंचांगp, &qmi->services, list_node) अणु
		list_del(&svc->list_node);
		kमुक्त(svc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qmi_handle_release);

/**
 * qmi_send_message() - send a QMI message
 * @qmi:	QMI client handle
 * @sq:		destination sockaddr
 * @txn:	transaction object to use क्रम the message
 * @type:	type of message to send
 * @msg_id:	message id
 * @len:	max length of the QMI message
 * @ei:		QMI message description
 * @c_काष्ठा:	object to be encoded
 *
 * This function encodes @c_काष्ठा using @ei पूर्णांकo a message of type @type,
 * with @msg_id and @txn पूर्णांकo a buffer of maximum size @len, and sends this to
 * @sq.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
अटल sमाप_प्रकार qmi_send_message(काष्ठा qmi_handle *qmi,
				काष्ठा sockaddr_qrtr *sq, काष्ठा qmi_txn *txn,
				पूर्णांक type, पूर्णांक msg_id, माप_प्रकार len,
				काष्ठा qmi_elem_info *ei, स्थिर व्योम *c_काष्ठा)
अणु
	काष्ठा msghdr msghdr = अणुपूर्ण;
	काष्ठा kvec iv;
	व्योम *msg;
	पूर्णांक ret;

	msg = qmi_encode_message(type,
				 msg_id, &len,
				 txn->id, ei,
				 c_काष्ठा);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	iv.iov_base = msg;
	iv.iov_len = len;

	अगर (sq) अणु
		msghdr.msg_name = sq;
		msghdr.msg_namelen = माप(*sq);
	पूर्ण

	mutex_lock(&qmi->sock_lock);
	अगर (qmi->sock) अणु
		ret = kernel_sendmsg(qmi->sock, &msghdr, &iv, 1, len);
		अगर (ret < 0)
			pr_err("failed to send QMI message\n");
	पूर्ण अन्यथा अणु
		ret = -EPIPE;
	पूर्ण
	mutex_unlock(&qmi->sock_lock);

	kमुक्त(msg);

	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * qmi_send_request() - send a request QMI message
 * @qmi:	QMI client handle
 * @sq:		destination sockaddr
 * @txn:	transaction object to use क्रम the message
 * @msg_id:	message id
 * @len:	max length of the QMI message
 * @ei:		QMI message description
 * @c_काष्ठा:	object to be encoded
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
sमाप_प्रकार qmi_send_request(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			 काष्ठा qmi_txn *txn, पूर्णांक msg_id, माप_प्रकार len,
			 काष्ठा qmi_elem_info *ei, स्थिर व्योम *c_काष्ठा)
अणु
	वापस qmi_send_message(qmi, sq, txn, QMI_REQUEST, msg_id, len, ei,
				c_काष्ठा);
पूर्ण
EXPORT_SYMBOL(qmi_send_request);

/**
 * qmi_send_response() - send a response QMI message
 * @qmi:	QMI client handle
 * @sq:		destination sockaddr
 * @txn:	transaction object to use क्रम the message
 * @msg_id:	message id
 * @len:	max length of the QMI message
 * @ei:		QMI message description
 * @c_काष्ठा:	object to be encoded
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
sमाप_प्रकार qmi_send_response(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			  काष्ठा qmi_txn *txn, पूर्णांक msg_id, माप_प्रकार len,
			  काष्ठा qmi_elem_info *ei, स्थिर व्योम *c_काष्ठा)
अणु
	वापस qmi_send_message(qmi, sq, txn, QMI_RESPONSE, msg_id, len, ei,
				c_काष्ठा);
पूर्ण
EXPORT_SYMBOL(qmi_send_response);

/**
 * qmi_send_indication() - send an indication QMI message
 * @qmi:	QMI client handle
 * @sq:		destination sockaddr
 * @msg_id:	message id
 * @len:	max length of the QMI message
 * @ei:		QMI message description
 * @c_काष्ठा:	object to be encoded
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
sमाप_प्रकार qmi_send_indication(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			    पूर्णांक msg_id, माप_प्रकार len, काष्ठा qmi_elem_info *ei,
			    स्थिर व्योम *c_काष्ठा)
अणु
	काष्ठा qmi_txn txn;
	sमाप_प्रकार rval;
	पूर्णांक ret;

	ret = qmi_txn_init(qmi, &txn, शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	rval = qmi_send_message(qmi, sq, &txn, QMI_INDICATION, msg_id, len, ei,
				c_काष्ठा);

	/* We करोn't care about future messages on this txn */
	qmi_txn_cancel(&txn);

	वापस rval;
पूर्ण
EXPORT_SYMBOL(qmi_send_indication);
