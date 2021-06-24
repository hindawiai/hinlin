<शैली गुरु>
/*
 * Copyright (c) 2009, 2018 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/module.h>
#समावेश <rdma/rdma_cm.h>

#समावेश "rds_single_path.h"
#समावेश "rdma_transport.h"
#समावेश "ib.h"

/* Global IPv4 and IPv6 RDS RDMA listener cm_id */
अटल काष्ठा rdma_cm_id *rds_rdma_listen_id;
#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा rdma_cm_id *rds6_rdma_listen_id;
#पूर्ण_अगर

/* Per IB specअगरication 7.7.3, service level is a 4-bit field. */
#घोषणा TOS_TO_SL(tos)		((tos) & 0xF)

अटल पूर्णांक rds_rdma_cm_event_handler_cmn(काष्ठा rdma_cm_id *cm_id,
					 काष्ठा rdma_cm_event *event,
					 bool isv6)
अणु
	/* this can be null in the listening path */
	काष्ठा rds_connection *conn = cm_id->context;
	काष्ठा rds_transport *trans;
	पूर्णांक ret = 0;
	पूर्णांक *err;
	u8 len;

	rdsdebug("conn %p id %p handling event %u (%s)\n", conn, cm_id,
		 event->event, rdma_event_msg(event->event));

	अगर (cm_id->device->node_type == RDMA_NODE_IB_CA)
		trans = &rds_ib_transport;

	/* Prevent shutकरोwn from tearing करोwn the connection
	 * जबतक we're executing. */
	अगर (conn) अणु
		mutex_lock(&conn->c_cm_lock);

		/* If the connection is being shut करोwn, bail out
		 * right away. We वापस 0 so cm_id करोesn't get
		 * destroyed prematurely */
		अगर (rds_conn_state(conn) == RDS_CONN_DISCONNECTING) अणु
			/* Reject incoming connections जबतक we're tearing
			 * करोwn an existing one. */
			अगर (event->event == RDMA_CM_EVENT_CONNECT_REQUEST)
				ret = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = trans->cm_handle_connect(cm_id, event, isv6);
		अवरोध;

	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
		rdma_set_service_type(cm_id, conn->c_tos);
		rdma_set_min_rnr_समयr(cm_id, IB_RNR_TIMER_000_32);
		/* XXX करो we need to clean up अगर this fails? */
		ret = rdma_resolve_route(cm_id,
					 RDS_RDMA_RESOLVE_TIMEOUT_MS);
		अवरोध;

	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		/* Connection could have been dropped so make sure the
		 * cm_id is valid beक्रमe proceeding
		 */
		अगर (conn) अणु
			काष्ठा rds_ib_connection *ibic;

			ibic = conn->c_transport_data;
			अगर (ibic && ibic->i_cm_id == cm_id) अणु
				cm_id->route.path_rec[0].sl =
					TOS_TO_SL(conn->c_tos);
				ret = trans->cm_initiate_connect(cm_id, isv6);
			पूर्ण अन्यथा अणु
				rds_conn_drop(conn);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल RDMA_CM_EVENT_ESTABLISHED:
		अगर (conn)
			trans->cm_connect_complete(conn, event);
		अवरोध;

	हाल RDMA_CM_EVENT_REJECTED:
		अगर (!conn)
			अवरोध;
		err = (पूर्णांक *)rdma_consumer_reject_data(cm_id, event, &len);
		अगर (!err ||
		    (err && len >= माप(*err) &&
		     ((*err) <= RDS_RDMA_REJ_INCOMPAT))) अणु
			pr_warn("RDS/RDMA: conn <%pI6c, %pI6c> rejected, dropping connection\n",
				&conn->c_laddr, &conn->c_faddr);

			अगर (!conn->c_tos)
				conn->c_proposed_version = RDS_PROTOCOL_COMPAT_VERSION;

			rds_conn_drop(conn);
		पूर्ण
		rdsdebug("Connection rejected: %s\n",
			 rdma_reject_msg(cm_id, event->status));
		अवरोध;
	हाल RDMA_CM_EVENT_ADDR_ERROR:
	हाल RDMA_CM_EVENT_ROUTE_ERROR:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
		अगर (conn)
			rds_conn_drop(conn);
		अवरोध;

	हाल RDMA_CM_EVENT_DISCONNECTED:
		अगर (!conn)
			अवरोध;
		rdsdebug("DISCONNECT event - dropping connection "
			 "%pI6c->%pI6c\n", &conn->c_laddr,
			 &conn->c_faddr);
		rds_conn_drop(conn);
		अवरोध;

	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		अगर (conn) अणु
			pr_info("RDS: RDMA_CM_EVENT_TIMEWAIT_EXIT event: dropping connection %pI6c->%pI6c\n",
				&conn->c_laddr, &conn->c_faddr);
			rds_conn_drop(conn);
		पूर्ण
		अवरोध;

	शेष:
		/* things like device disconnect? */
		prपूर्णांकk(KERN_ERR "RDS: unknown event %u (%s)!\n",
		       event->event, rdma_event_msg(event->event));
		अवरोध;
	पूर्ण

out:
	अगर (conn)
		mutex_unlock(&conn->c_cm_lock);

	rdsdebug("id %p event %u (%s) handling ret %d\n", cm_id, event->event,
		 rdma_event_msg(event->event), ret);

	वापस ret;
पूर्ण

पूर्णांक rds_rdma_cm_event_handler(काष्ठा rdma_cm_id *cm_id,
			      काष्ठा rdma_cm_event *event)
अणु
	वापस rds_rdma_cm_event_handler_cmn(cm_id, event, false);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक rds6_rdma_cm_event_handler(काष्ठा rdma_cm_id *cm_id,
			       काष्ठा rdma_cm_event *event)
अणु
	वापस rds_rdma_cm_event_handler_cmn(cm_id, event, true);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rds_rdma_listen_init_common(rdma_cm_event_handler handler,
				       काष्ठा sockaddr *sa,
				       काष्ठा rdma_cm_id **ret_cm_id)
अणु
	काष्ठा rdma_cm_id *cm_id;
	पूर्णांक ret;

	cm_id = rdma_create_id(&init_net, handler, शून्य,
			       RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(cm_id)) अणु
		ret = PTR_ERR(cm_id);
		prपूर्णांकk(KERN_ERR "RDS/RDMA: failed to setup listener, "
		       "rdma_create_id() returned %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * XXX I bet this binds the cm_id to a device.  If we want to support
	 * fail-over we'll have to take this पूर्णांकo consideration.
	 */
	ret = rdma_bind_addr(cm_id, sa);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "RDS/RDMA: failed to setup listener, "
		       "rdma_bind_addr() returned %d\n", ret);
		जाओ out;
	पूर्ण

	ret = rdma_listen(cm_id, 128);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "RDS/RDMA: failed to setup listener, "
		       "rdma_listen() returned %d\n", ret);
		जाओ out;
	पूर्ण

	rdsdebug("cm %p listening on port %u\n", cm_id, RDS_PORT);

	*ret_cm_id = cm_id;
	cm_id = शून्य;
out:
	अगर (cm_id)
		rdma_destroy_id(cm_id);
	वापस ret;
पूर्ण

/* Initialize the RDS RDMA listeners.  We create two listeners क्रम
 * compatibility reason.  The one on RDS_PORT is used क्रम IPv4
 * requests only.  The one on RDS_CM_PORT is used क्रम IPv6 requests
 * only.  So only IPv6 enabled RDS module will communicate using this
 * port.
 */
अटल पूर्णांक rds_rdma_listen_init(व्योम)
अणु
	पूर्णांक ret;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 sin6;
#पूर्ण_अगर
	काष्ठा sockaddr_in sin;

	sin.sin_family = PF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(RDS_PORT);
	ret = rds_rdma_listen_init_common(rds_rdma_cm_event_handler,
					  (काष्ठा sockaddr *)&sin,
					  &rds_rdma_listen_id);
	अगर (ret != 0)
		वापस ret;

#अगर IS_ENABLED(CONFIG_IPV6)
	sin6.sin6_family = PF_INET6;
	sin6.sin6_addr = in6addr_any;
	sin6.sin6_port = htons(RDS_CM_PORT);
	sin6.sin6_scope_id = 0;
	sin6.sin6_flowinfo = 0;
	ret = rds_rdma_listen_init_common(rds6_rdma_cm_event_handler,
					  (काष्ठा sockaddr *)&sin6,
					  &rds6_rdma_listen_id);
	/* Keep going even when IPv6 is not enabled in the प्रणाली. */
	अगर (ret != 0)
		rdsdebug("Cannot set up IPv6 RDMA listener\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम rds_rdma_listen_stop(व्योम)
अणु
	अगर (rds_rdma_listen_id) अणु
		rdsdebug("cm %p\n", rds_rdma_listen_id);
		rdma_destroy_id(rds_rdma_listen_id);
		rds_rdma_listen_id = शून्य;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (rds6_rdma_listen_id) अणु
		rdsdebug("cm %p\n", rds6_rdma_listen_id);
		rdma_destroy_id(rds6_rdma_listen_id);
		rds6_rdma_listen_id = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक rds_rdma_init(व्योम)
अणु
	पूर्णांक ret;

	ret = rds_ib_init();
	अगर (ret)
		जाओ out;

	ret = rds_rdma_listen_init();
	अगर (ret)
		rds_ib_निकास();
out:
	वापस ret;
पूर्ण
module_init(rds_rdma_init);

अटल व्योम rds_rdma_निकास(व्योम)
अणु
	/* stop listening first to ensure no new connections are attempted */
	rds_rdma_listen_stop();
	rds_ib_निकास();
पूर्ण
module_निकास(rds_rdma_निकास);

MODULE_AUTHOR("Oracle Corporation <rds-devel@oss.oracle.com>");
MODULE_DESCRIPTION("RDS: IB transport");
MODULE_LICENSE("Dual BSD/GPL");
