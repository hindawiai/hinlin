<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अगर_अघोषित RTRS_H
#घोषणा RTRS_H

#समावेश <linux/socket.h>
#समावेश <linux/scatterlist.h>

काष्ठा rtrs_permit;
काष्ठा rtrs_clt;
काष्ठा rtrs_srv_ctx;
काष्ठा rtrs_srv;
काष्ठा rtrs_srv_op;

/*
 * RDMA transport (RTRS) client API
 */

/**
 * क्रमागत rtrs_clt_link_ev - Events about connectivity state of a client
 * @RTRS_CLT_LINK_EV_RECONNECTED	Client was reconnected.
 * @RTRS_CLT_LINK_EV_DISCONNECTED	Client was disconnected.
 */
क्रमागत rtrs_clt_link_ev अणु
	RTRS_CLT_LINK_EV_RECONNECTED,
	RTRS_CLT_LINK_EV_DISCONNECTED,
पूर्ण;

/**
 * Source and destination address of a path to be established
 */
काष्ठा rtrs_addr अणु
	काष्ठा sockaddr_storage *src;
	काष्ठा sockaddr_storage *dst;
पूर्ण;

/**
 * rtrs_clt_ops - it holds the link event callback and निजी poपूर्णांकer.
 * @priv: User supplied निजी data.
 * @link_ev: Event notअगरication callback function क्रम connection state changes
 *	@priv: User supplied data that was passed to rtrs_clt_खोलो()
 *	@ev: Occurred event
 */
काष्ठा rtrs_clt_ops अणु
	व्योम	*priv;
	व्योम	(*link_ev)(व्योम *priv, क्रमागत rtrs_clt_link_ev ev);
पूर्ण;

काष्ठा rtrs_clt *rtrs_clt_खोलो(काष्ठा rtrs_clt_ops *ops,
				 स्थिर अक्षर *sessname,
				 स्थिर काष्ठा rtrs_addr *paths,
				 माप_प्रकार path_cnt, u16 port,
				 माप_प्रकार pdu_sz, u8 reconnect_delay_sec,
				 u16 max_segments,
				 s16 max_reconnect_attempts, u32 nr_poll_queues);

व्योम rtrs_clt_बंद(काष्ठा rtrs_clt *sess);

क्रमागत रुको_type अणु
	RTRS_PERMIT_NOWAIT = 0,
	RTRS_PERMIT_WAIT   = 1
पूर्ण;

/**
 * क्रमागत rtrs_clt_con_type() type of ib connection to use with a given
 * rtrs_permit
 * @ADMIN_CON - use connection reserved क्रम "service" messages
 * @IO_CON - use a connection reserved क्रम IO
 */
क्रमागत rtrs_clt_con_type अणु
	RTRS_ADMIN_CON,
	RTRS_IO_CON
पूर्ण;

काष्ठा rtrs_permit *rtrs_clt_get_permit(काष्ठा rtrs_clt *sess,
				    क्रमागत rtrs_clt_con_type con_type,
				    क्रमागत रुको_type रुको);

व्योम rtrs_clt_put_permit(काष्ठा rtrs_clt *sess, काष्ठा rtrs_permit *permit);

/**
 * rtrs_clt_req_ops - it holds the request confirmation callback
 * and a निजी poपूर्णांकer.
 * @priv: User supplied निजी data.
 * @conf_fn:	callback function to be called as confirmation
 *	@priv:	User provided data, passed back with corresponding
 *		@(conf) confirmation.
 *	@त्रुटि_सं: error number.
 */
काष्ठा rtrs_clt_req_ops अणु
	व्योम	*priv;
	व्योम	(*conf_fn)(व्योम *priv, पूर्णांक त्रुटि_सं);
पूर्ण;

पूर्णांक rtrs_clt_request(पूर्णांक dir, काष्ठा rtrs_clt_req_ops *ops,
		     काष्ठा rtrs_clt *sess, काष्ठा rtrs_permit *permit,
		     स्थिर काष्ठा kvec *vec, माप_प्रकार nr, माप_प्रकार len,
		     काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_cnt);
पूर्णांक rtrs_clt_rdma_cq_direct(काष्ठा rtrs_clt *clt, अचिन्हित पूर्णांक index);

/**
 * rtrs_attrs - RTRS session attributes
 */
काष्ठा rtrs_attrs अणु
	u32		queue_depth;
	u32		max_io_size;
पूर्ण;

पूर्णांक rtrs_clt_query(काष्ठा rtrs_clt *sess, काष्ठा rtrs_attrs *attr);

/*
 * Here goes RTRS server API
 */

/**
 * क्रमागत rtrs_srv_link_ev - Server link events
 * @RTRS_SRV_LINK_EV_CONNECTED:	Connection from client established
 * @RTRS_SRV_LINK_EV_DISCONNECTED:	Connection was disconnected, all
 *					connection RTRS resources were मुक्तd.
 */
क्रमागत rtrs_srv_link_ev अणु
	RTRS_SRV_LINK_EV_CONNECTED,
	RTRS_SRV_LINK_EV_DISCONNECTED,
पूर्ण;

काष्ठा rtrs_srv_ops अणु
	/**
	 * rdma_ev():		Event notअगरication क्रम RDMA operations
	 *			If the callback वापसs a value != 0, an error
	 *			message क्रम the data transfer will be sent to
	 *			the client.

	 *	@priv:		Private data set by rtrs_srv_set_sess_priv()
	 *	@id:		पूर्णांकernal RTRS operation id
	 *	@dir:		READ/WRITE
	 *	@data:		Poपूर्णांकer to (bidirectional) rdma memory area:
	 *			- in हाल of %RTRS_SRV_RDMA_EV_RECV contains
	 *			data sent by the client
	 *			- in हाल of %RTRS_SRV_RDMA_EV_WRITE_REQ poपूर्णांकs
	 *			to the memory area where the response is to be
	 *			written to
	 *	@datalen:	Size of the memory area in @data
	 *	@usr:		The extra user message sent by the client (%vec)
	 *	@usrlen:	Size of the user message
	 */
	पूर्णांक (*rdma_ev)(व्योम *priv,
		       काष्ठा rtrs_srv_op *id, पूर्णांक dir,
		       व्योम *data, माप_प्रकार datalen, स्थिर व्योम *usr,
		       माप_प्रकार usrlen);
	/**
	 * link_ev():		Events about connectivity state changes
	 *			If the callback वापसs != 0 and the event
	 *			%RTRS_SRV_LINK_EV_CONNECTED the corresponding
	 *			session will be destroyed.
	 *	@sess:		Session
	 *	@ev:		event
	 *	@priv:		Private data from user अगर previously set with
	 *			rtrs_srv_set_sess_priv()
	 */
	पूर्णांक (*link_ev)(काष्ठा rtrs_srv *sess, क्रमागत rtrs_srv_link_ev ev,
		       व्योम *priv);
पूर्ण;

काष्ठा rtrs_srv_ctx *rtrs_srv_खोलो(काष्ठा rtrs_srv_ops *ops, u16 port);

व्योम rtrs_srv_बंद(काष्ठा rtrs_srv_ctx *ctx);

bool rtrs_srv_resp_rdma(काष्ठा rtrs_srv_op *id, पूर्णांक त्रुटि_सं);

व्योम rtrs_srv_set_sess_priv(काष्ठा rtrs_srv *sess, व्योम *priv);

पूर्णांक rtrs_srv_get_sess_name(काष्ठा rtrs_srv *sess, अक्षर *sessname, माप_प्रकार len);

पूर्णांक rtrs_srv_get_queue_depth(काष्ठा rtrs_srv *sess);

पूर्णांक rtrs_addr_to_sockaddr(स्थिर अक्षर *str, माप_प्रकार len, u16 port,
			  काष्ठा rtrs_addr *addr);

पूर्णांक sockaddr_to_str(स्थिर काष्ठा sockaddr *addr, अक्षर *buf, माप_प्रकार len);
पूर्णांक rtrs_addr_to_str(स्थिर काष्ठा rtrs_addr *addr, अक्षर *buf, माप_प्रकार len);
#पूर्ण_अगर
