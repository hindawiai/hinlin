<शैली गुरु>
/*
 * Copyright (c) 2006, 2019 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <linux/kernel.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ratelimit.h>
#समावेश <net/addrconf.h>
#समावेश <rdma/ib_cm.h>

#समावेश "rds_single_path.h"
#समावेश "rds.h"
#समावेश "ib.h"
#समावेश "ib_mr.h"

/*
 * Set the selected protocol version
 */
अटल व्योम rds_ib_set_protocol(काष्ठा rds_connection *conn, अचिन्हित पूर्णांक version)
अणु
	conn->c_version = version;
पूर्ण

/*
 * Set up flow control
 */
अटल व्योम rds_ib_set_flow_control(काष्ठा rds_connection *conn, u32 credits)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	अगर (rds_ib_sysctl_flow_control && credits != 0) अणु
		/* We're करोing flow control */
		ic->i_flowctl = 1;
		rds_ib_send_add_credits(conn, credits);
	पूर्ण अन्यथा अणु
		ic->i_flowctl = 0;
	पूर्ण
पूर्ण

/*
 * Connection established.
 * We get here क्रम both outgoing and incoming connection.
 */
व्योम rds_ib_cm_connect_complete(काष्ठा rds_connection *conn, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	स्थिर जोड़ rds_ib_conn_priv *dp = शून्य;
	__be64 ack_seq = 0;
	__be32 credit = 0;
	u8 major = 0;
	u8 minor = 0;
	पूर्णांक err;

	dp = event->param.conn.निजी_data;
	अगर (conn->c_isv6) अणु
		अगर (event->param.conn.निजी_data_len >=
		    माप(काष्ठा rds6_ib_connect_निजी)) अणु
			major = dp->ricp_v6.dp_protocol_major;
			minor = dp->ricp_v6.dp_protocol_minor;
			credit = dp->ricp_v6.dp_credit;
			/* dp काष्ठाure start is not guaranteed to be 8 bytes
			 * aligned.  Since dp_ack_seq is 64-bit extended load
			 * operations can be used so go through get_unaligned
			 * to aव्योम unaligned errors.
			 */
			ack_seq = get_unaligned(&dp->ricp_v6.dp_ack_seq);
		पूर्ण
	पूर्ण अन्यथा अगर (event->param.conn.निजी_data_len >=
		   माप(काष्ठा rds_ib_connect_निजी)) अणु
		major = dp->ricp_v4.dp_protocol_major;
		minor = dp->ricp_v4.dp_protocol_minor;
		credit = dp->ricp_v4.dp_credit;
		ack_seq = get_unaligned(&dp->ricp_v4.dp_ack_seq);
	पूर्ण

	/* make sure it isn't empty data */
	अगर (major) अणु
		rds_ib_set_protocol(conn, RDS_PROTOCOL(major, minor));
		rds_ib_set_flow_control(conn, be32_to_cpu(credit));
	पूर्ण

	अगर (conn->c_version < RDS_PROTOCOL_VERSION) अणु
		अगर (conn->c_version != RDS_PROTOCOL_COMPAT_VERSION) अणु
			pr_notice("RDS/IB: Connection <%pI6c,%pI6c> version %u.%u no longer supported\n",
				  &conn->c_laddr, &conn->c_faddr,
				  RDS_PROTOCOL_MAJOR(conn->c_version),
				  RDS_PROTOCOL_MINOR(conn->c_version));
			rds_conn_destroy(conn);
			वापस;
		पूर्ण
	पूर्ण

	pr_notice("RDS/IB: %s conn connected <%pI6c,%pI6c,%d> version %u.%u%s\n",
		  ic->i_active_side ? "Active" : "Passive",
		  &conn->c_laddr, &conn->c_faddr, conn->c_tos,
		  RDS_PROTOCOL_MAJOR(conn->c_version),
		  RDS_PROTOCOL_MINOR(conn->c_version),
		  ic->i_flowctl ? ", flow control" : "");

	/* receive sl from the peer */
	ic->i_sl = ic->i_cm_id->route.path_rec->sl;

	atomic_set(&ic->i_cq_quiesce, 0);

	/* Init rings and fill recv. this needs to रुको until protocol
	 * negotiation is complete, since ring layout is dअगरferent
	 * from 3.1 to 4.1.
	 */
	rds_ib_send_init_ring(ic);
	rds_ib_recv_init_ring(ic);
	/* Post receive buffers - as a side effect, this will update
	 * the posted credit count. */
	rds_ib_recv_refill(conn, 1, GFP_KERNEL);

	/* update ib_device with this local ipaddr */
	err = rds_ib_update_ipaddr(ic->rds_ibdev, &conn->c_laddr);
	अगर (err)
		prपूर्णांकk(KERN_ERR "rds_ib_update_ipaddr failed (%d)\n",
			err);

	/* If the peer gave us the last packet it saw, process this as अगर
	 * we had received a regular ACK. */
	अगर (dp) अणु
		अगर (ack_seq)
			rds_send_drop_acked(conn, be64_to_cpu(ack_seq),
					    शून्य);
	पूर्ण

	conn->c_proposed_version = conn->c_version;
	rds_connect_complete(conn);
पूर्ण

अटल व्योम rds_ib_cm_fill_conn_param(काष्ठा rds_connection *conn,
				      काष्ठा rdma_conn_param *conn_param,
				      जोड़ rds_ib_conn_priv *dp,
				      u32 protocol_version,
				      u32 max_responder_resources,
				      u32 max_initiator_depth,
				      bool isv6)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा rds_ib_device *rds_ibdev = ic->rds_ibdev;

	स_रखो(conn_param, 0, माप(काष्ठा rdma_conn_param));

	conn_param->responder_resources =
		min_t(u32, rds_ibdev->max_responder_resources, max_responder_resources);
	conn_param->initiator_depth =
		min_t(u32, rds_ibdev->max_initiator_depth, max_initiator_depth);
	conn_param->retry_count = min_t(अचिन्हित पूर्णांक, rds_ib_retry_count, 7);
	conn_param->rnr_retry_count = 7;

	अगर (dp) अणु
		स_रखो(dp, 0, माप(*dp));
		अगर (isv6) अणु
			dp->ricp_v6.dp_saddr = conn->c_laddr;
			dp->ricp_v6.dp_daddr = conn->c_faddr;
			dp->ricp_v6.dp_protocol_major =
			    RDS_PROTOCOL_MAJOR(protocol_version);
			dp->ricp_v6.dp_protocol_minor =
			    RDS_PROTOCOL_MINOR(protocol_version);
			dp->ricp_v6.dp_protocol_minor_mask =
			    cpu_to_be16(RDS_IB_SUPPORTED_PROTOCOLS);
			dp->ricp_v6.dp_ack_seq =
			    cpu_to_be64(rds_ib_piggyb_ack(ic));
			dp->ricp_v6.dp_cmn.ricpc_dp_toss = conn->c_tos;

			conn_param->निजी_data = &dp->ricp_v6;
			conn_param->निजी_data_len = माप(dp->ricp_v6);
		पूर्ण अन्यथा अणु
			dp->ricp_v4.dp_saddr = conn->c_laddr.s6_addr32[3];
			dp->ricp_v4.dp_daddr = conn->c_faddr.s6_addr32[3];
			dp->ricp_v4.dp_protocol_major =
			    RDS_PROTOCOL_MAJOR(protocol_version);
			dp->ricp_v4.dp_protocol_minor =
			    RDS_PROTOCOL_MINOR(protocol_version);
			dp->ricp_v4.dp_protocol_minor_mask =
			    cpu_to_be16(RDS_IB_SUPPORTED_PROTOCOLS);
			dp->ricp_v4.dp_ack_seq =
			    cpu_to_be64(rds_ib_piggyb_ack(ic));
			dp->ricp_v4.dp_cmn.ricpc_dp_toss = conn->c_tos;

			conn_param->निजी_data = &dp->ricp_v4;
			conn_param->निजी_data_len = माप(dp->ricp_v4);
		पूर्ण

		/* Advertise flow control */
		अगर (ic->i_flowctl) अणु
			अचिन्हित पूर्णांक credits;

			credits = IB_GET_POST_CREDITS
				(atomic_पढ़ो(&ic->i_credits));
			अगर (isv6)
				dp->ricp_v6.dp_credit = cpu_to_be32(credits);
			अन्यथा
				dp->ricp_v4.dp_credit = cpu_to_be32(credits);
			atomic_sub(IB_SET_POST_CREDITS(credits),
				   &ic->i_credits);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rds_ib_cq_event_handler(काष्ठा ib_event *event, व्योम *data)
अणु
	rdsdebug("event %u (%s) data %p\n",
		 event->event, ib_event_msg(event->event), data);
पूर्ण

/* Plucking the oldest entry from the ring can be करोne concurrently with
 * the thपढ़ो refilling the ring.  Each ring operation is रक्षित by
 * spinlocks and the transient state of refilling करोesn't change the
 * recording of which entry is oldest.
 *
 * This relies on IB only calling one cq comp_handler क्रम each cq so that
 * there will only be one caller of rds_recv_incoming() per RDS connection.
 */
अटल व्योम rds_ib_cq_comp_handler_recv(काष्ठा ib_cq *cq, व्योम *context)
अणु
	काष्ठा rds_connection *conn = context;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	rdsdebug("conn %p cq %p\n", conn, cq);

	rds_ib_stats_inc(s_ib_evt_handler_call);

	tasklet_schedule(&ic->i_recv_tasklet);
पूर्ण

अटल व्योम poll_scq(काष्ठा rds_ib_connection *ic, काष्ठा ib_cq *cq,
		     काष्ठा ib_wc *wcs)
अणु
	पूर्णांक nr, i;
	काष्ठा ib_wc *wc;

	जबतक ((nr = ib_poll_cq(cq, RDS_IB_WC_MAX, wcs)) > 0) अणु
		क्रम (i = 0; i < nr; i++) अणु
			wc = wcs + i;
			rdsdebug("wc wr_id 0x%llx status %u byte_len %u imm_data %u\n",
				 (अचिन्हित दीर्घ दीर्घ)wc->wr_id, wc->status,
				 wc->byte_len, be32_to_cpu(wc->ex.imm_data));

			अगर (wc->wr_id <= ic->i_send_ring.w_nr ||
			    wc->wr_id == RDS_IB_ACK_WR_ID)
				rds_ib_send_cqe_handler(ic, wc);
			अन्यथा
				rds_ib_mr_cqe_handler(ic, wc);

		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rds_ib_tasklet_fn_send(अचिन्हित दीर्घ data)
अणु
	काष्ठा rds_ib_connection *ic = (काष्ठा rds_ib_connection *)data;
	काष्ठा rds_connection *conn = ic->conn;

	rds_ib_stats_inc(s_ib_tasklet_call);

	/* अगर cq has been alपढ़ोy reaped, ignore incoming cq event */
	अगर (atomic_पढ़ो(&ic->i_cq_quiesce))
		वापस;

	poll_scq(ic, ic->i_send_cq, ic->i_send_wc);
	ib_req_notअगरy_cq(ic->i_send_cq, IB_CQ_NEXT_COMP);
	poll_scq(ic, ic->i_send_cq, ic->i_send_wc);

	अगर (rds_conn_up(conn) &&
	    (!test_bit(RDS_LL_SEND_FULL, &conn->c_flags) ||
	    test_bit(0, &conn->c_map_queued)))
		rds_send_xmit(&ic->conn->c_path[0]);
पूर्ण

अटल व्योम poll_rcq(काष्ठा rds_ib_connection *ic, काष्ठा ib_cq *cq,
		     काष्ठा ib_wc *wcs,
		     काष्ठा rds_ib_ack_state *ack_state)
अणु
	पूर्णांक nr, i;
	काष्ठा ib_wc *wc;

	जबतक ((nr = ib_poll_cq(cq, RDS_IB_WC_MAX, wcs)) > 0) अणु
		क्रम (i = 0; i < nr; i++) अणु
			wc = wcs + i;
			rdsdebug("wc wr_id 0x%llx status %u byte_len %u imm_data %u\n",
				 (अचिन्हित दीर्घ दीर्घ)wc->wr_id, wc->status,
				 wc->byte_len, be32_to_cpu(wc->ex.imm_data));

			rds_ib_recv_cqe_handler(ic, wc, ack_state);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rds_ib_tasklet_fn_recv(अचिन्हित दीर्घ data)
अणु
	काष्ठा rds_ib_connection *ic = (काष्ठा rds_ib_connection *)data;
	काष्ठा rds_connection *conn = ic->conn;
	काष्ठा rds_ib_device *rds_ibdev = ic->rds_ibdev;
	काष्ठा rds_ib_ack_state state;

	अगर (!rds_ibdev)
		rds_conn_drop(conn);

	rds_ib_stats_inc(s_ib_tasklet_call);

	/* अगर cq has been alपढ़ोy reaped, ignore incoming cq event */
	अगर (atomic_पढ़ो(&ic->i_cq_quiesce))
		वापस;

	स_रखो(&state, 0, माप(state));
	poll_rcq(ic, ic->i_recv_cq, ic->i_recv_wc, &state);
	ib_req_notअगरy_cq(ic->i_recv_cq, IB_CQ_SOLICITED);
	poll_rcq(ic, ic->i_recv_cq, ic->i_recv_wc, &state);

	अगर (state.ack_next_valid)
		rds_ib_set_ack(ic, state.ack_next, state.ack_required);
	अगर (state.ack_recv_valid && state.ack_recv > ic->i_ack_recv) अणु
		rds_send_drop_acked(conn, state.ack_recv, शून्य);
		ic->i_ack_recv = state.ack_recv;
	पूर्ण

	अगर (rds_conn_up(conn))
		rds_ib_attempt_ack(ic);
पूर्ण

अटल व्योम rds_ib_qp_event_handler(काष्ठा ib_event *event, व्योम *data)
अणु
	काष्ठा rds_connection *conn = data;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	rdsdebug("conn %p ic %p event %u (%s)\n", conn, ic, event->event,
		 ib_event_msg(event->event));

	चयन (event->event) अणु
	हाल IB_EVENT_COMM_EST:
		rdma_notअगरy(ic->i_cm_id, IB_EVENT_COMM_EST);
		अवरोध;
	शेष:
		rdsdebug("Fatal QP Event %u (%s) - connection %pI6c->%pI6c, reconnecting\n",
			 event->event, ib_event_msg(event->event),
			 &conn->c_laddr, &conn->c_faddr);
		rds_conn_drop(conn);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rds_ib_cq_comp_handler_send(काष्ठा ib_cq *cq, व्योम *context)
अणु
	काष्ठा rds_connection *conn = context;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	rdsdebug("conn %p cq %p\n", conn, cq);

	rds_ib_stats_inc(s_ib_evt_handler_call);

	tasklet_schedule(&ic->i_send_tasklet);
पूर्ण

अटल अंतरभूत पूर्णांक ibdev_get_unused_vector(काष्ठा rds_ib_device *rds_ibdev)
अणु
	पूर्णांक min = rds_ibdev->vector_load[rds_ibdev->dev->num_comp_vectors - 1];
	पूर्णांक index = rds_ibdev->dev->num_comp_vectors - 1;
	पूर्णांक i;

	क्रम (i = rds_ibdev->dev->num_comp_vectors - 1; i >= 0; i--) अणु
		अगर (rds_ibdev->vector_load[i] < min) अणु
			index = i;
			min = rds_ibdev->vector_load[i];
		पूर्ण
	पूर्ण

	rds_ibdev->vector_load[index]++;
	वापस index;
पूर्ण

अटल अंतरभूत व्योम ibdev_put_vector(काष्ठा rds_ib_device *rds_ibdev, पूर्णांक index)
अणु
	rds_ibdev->vector_load[index]--;
पूर्ण

अटल व्योम rds_dma_hdr_मुक्त(काष्ठा ib_device *dev, काष्ठा rds_header *hdr,
		dma_addr_t dma_addr, क्रमागत dma_data_direction dir)
अणु
	ib_dma_unmap_single(dev, dma_addr, माप(*hdr), dir);
	kमुक्त(hdr);
पूर्ण

अटल काष्ठा rds_header *rds_dma_hdr_alloc(काष्ठा ib_device *dev,
		dma_addr_t *dma_addr, क्रमागत dma_data_direction dir)
अणु
	काष्ठा rds_header *hdr;

	hdr = kzalloc_node(माप(*hdr), GFP_KERNEL, ibdev_to_node(dev));
	अगर (!hdr)
		वापस शून्य;

	*dma_addr = ib_dma_map_single(dev, hdr, माप(*hdr),
				      DMA_BIसूचीECTIONAL);
	अगर (ib_dma_mapping_error(dev, *dma_addr)) अणु
		kमुक्त(hdr);
		वापस शून्य;
	पूर्ण

	वापस hdr;
पूर्ण

/* Free the DMA memory used to store काष्ठा rds_header.
 *
 * @dev: the RDS IB device
 * @hdrs: poपूर्णांकer to the array storing DMA memory poपूर्णांकers
 * @dma_addrs: poपूर्णांकer to the array storing DMA addresses
 * @num_hdars: number of headers to मुक्त.
 */
अटल व्योम rds_dma_hdrs_मुक्त(काष्ठा rds_ib_device *dev,
		काष्ठा rds_header **hdrs, dma_addr_t *dma_addrs, u32 num_hdrs,
		क्रमागत dma_data_direction dir)
अणु
	u32 i;

	क्रम (i = 0; i < num_hdrs; i++)
		rds_dma_hdr_मुक्त(dev->dev, hdrs[i], dma_addrs[i], dir);
	kvमुक्त(hdrs);
	kvमुक्त(dma_addrs);
पूर्ण


/* Allocate DMA coherent memory to be used to store काष्ठा rds_header क्रम
 * sending/receiving packets.  The poपूर्णांकers to the DMA memory and the
 * associated DMA addresses are stored in two arrays.
 *
 * @dev: the RDS IB device
 * @dma_addrs: poपूर्णांकer to the array क्रम storing DMA addresses
 * @num_hdrs: number of headers to allocate
 *
 * It वापसs the poपूर्णांकer to the array storing the DMA memory poपूर्णांकers.  On
 * error, शून्य poपूर्णांकer is वापसed.
 */
अटल काष्ठा rds_header **rds_dma_hdrs_alloc(काष्ठा rds_ib_device *dev,
		dma_addr_t **dma_addrs, u32 num_hdrs,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा rds_header **hdrs;
	dma_addr_t *hdr_daddrs;
	u32 i;

	hdrs = kvदो_स्मृति_node(माप(*hdrs) * num_hdrs, GFP_KERNEL,
			     ibdev_to_node(dev->dev));
	अगर (!hdrs)
		वापस शून्य;

	hdr_daddrs = kvदो_स्मृति_node(माप(*hdr_daddrs) * num_hdrs, GFP_KERNEL,
				   ibdev_to_node(dev->dev));
	अगर (!hdr_daddrs) अणु
		kvमुक्त(hdrs);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < num_hdrs; i++) अणु
		hdrs[i] = rds_dma_hdr_alloc(dev->dev, &hdr_daddrs[i], dir);
		अगर (!hdrs[i]) अणु
			rds_dma_hdrs_मुक्त(dev, hdrs, hdr_daddrs, i, dir);
			वापस शून्य;
		पूर्ण
	पूर्ण

	*dma_addrs = hdr_daddrs;
	वापस hdrs;
पूर्ण

/*
 * This needs to be very careful to not leave IS_ERR poपूर्णांकers around क्रम
 * cleanup to trip over.
 */
अटल पूर्णांक rds_ib_setup_qp(काष्ठा rds_connection *conn)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा ib_device *dev = ic->i_cm_id->device;
	काष्ठा ib_qp_init_attr attr;
	काष्ठा ib_cq_init_attr cq_attr = अणुपूर्ण;
	काष्ठा rds_ib_device *rds_ibdev;
	अचिन्हित दीर्घ max_wrs;
	पूर्णांक ret, fr_queue_space;

	/*
	 * It's normal to see a null device अगर an incoming connection races
	 * with device removal, so we करोn't prपूर्णांक a warning.
	 */
	rds_ibdev = rds_ib_get_client_data(dev);
	अगर (!rds_ibdev)
		वापस -EOPNOTSUPP;

	/* The fr_queue_space is currently set to 512, to add extra space on
	 * completion queue and send queue. This extra space is used क्रम FRWR
	 * registration and invalidation work requests
	 */
	fr_queue_space = RDS_IB_DEFAULT_FR_WR;

	/* add the conn now so that connection establishment has the dev */
	rds_ib_add_conn(rds_ibdev, conn);

	max_wrs = rds_ibdev->max_wrs < rds_ib_sysctl_max_send_wr + 1 ?
		rds_ibdev->max_wrs - 1 : rds_ib_sysctl_max_send_wr;
	अगर (ic->i_send_ring.w_nr != max_wrs)
		rds_ib_ring_resize(&ic->i_send_ring, max_wrs);

	max_wrs = rds_ibdev->max_wrs < rds_ib_sysctl_max_recv_wr + 1 ?
		rds_ibdev->max_wrs - 1 : rds_ib_sysctl_max_recv_wr;
	अगर (ic->i_recv_ring.w_nr != max_wrs)
		rds_ib_ring_resize(&ic->i_recv_ring, max_wrs);

	/* Protection करोमुख्य and memory range */
	ic->i_pd = rds_ibdev->pd;

	ic->i_scq_vector = ibdev_get_unused_vector(rds_ibdev);
	cq_attr.cqe = ic->i_send_ring.w_nr + fr_queue_space + 1;
	cq_attr.comp_vector = ic->i_scq_vector;
	ic->i_send_cq = ib_create_cq(dev, rds_ib_cq_comp_handler_send,
				     rds_ib_cq_event_handler, conn,
				     &cq_attr);
	अगर (IS_ERR(ic->i_send_cq)) अणु
		ret = PTR_ERR(ic->i_send_cq);
		ic->i_send_cq = शून्य;
		ibdev_put_vector(rds_ibdev, ic->i_scq_vector);
		rdsdebug("ib_create_cq send failed: %d\n", ret);
		जाओ rds_ibdev_out;
	पूर्ण

	ic->i_rcq_vector = ibdev_get_unused_vector(rds_ibdev);
	cq_attr.cqe = ic->i_recv_ring.w_nr;
	cq_attr.comp_vector = ic->i_rcq_vector;
	ic->i_recv_cq = ib_create_cq(dev, rds_ib_cq_comp_handler_recv,
				     rds_ib_cq_event_handler, conn,
				     &cq_attr);
	अगर (IS_ERR(ic->i_recv_cq)) अणु
		ret = PTR_ERR(ic->i_recv_cq);
		ic->i_recv_cq = शून्य;
		ibdev_put_vector(rds_ibdev, ic->i_rcq_vector);
		rdsdebug("ib_create_cq recv failed: %d\n", ret);
		जाओ send_cq_out;
	पूर्ण

	ret = ib_req_notअगरy_cq(ic->i_send_cq, IB_CQ_NEXT_COMP);
	अगर (ret) अणु
		rdsdebug("ib_req_notify_cq send failed: %d\n", ret);
		जाओ recv_cq_out;
	पूर्ण

	ret = ib_req_notअगरy_cq(ic->i_recv_cq, IB_CQ_SOLICITED);
	अगर (ret) अणु
		rdsdebug("ib_req_notify_cq recv failed: %d\n", ret);
		जाओ recv_cq_out;
	पूर्ण

	/* XXX negotiate max send/recv with remote? */
	स_रखो(&attr, 0, माप(attr));
	attr.event_handler = rds_ib_qp_event_handler;
	attr.qp_context = conn;
	/* + 1 to allow क्रम the single ack message */
	attr.cap.max_send_wr = ic->i_send_ring.w_nr + fr_queue_space + 1;
	attr.cap.max_recv_wr = ic->i_recv_ring.w_nr + 1;
	attr.cap.max_send_sge = rds_ibdev->max_sge;
	attr.cap.max_recv_sge = RDS_IB_RECV_SGE;
	attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	attr.qp_type = IB_QPT_RC;
	attr.send_cq = ic->i_send_cq;
	attr.recv_cq = ic->i_recv_cq;

	/*
	 * XXX this can fail अगर max_*_wr is too large?  Are we supposed
	 * to back off until we get a value that the hardware can support?
	 */
	ret = rdma_create_qp(ic->i_cm_id, ic->i_pd, &attr);
	अगर (ret) अणु
		rdsdebug("rdma_create_qp failed: %d\n", ret);
		जाओ recv_cq_out;
	पूर्ण

	ic->i_send_hdrs = rds_dma_hdrs_alloc(rds_ibdev, &ic->i_send_hdrs_dma,
					     ic->i_send_ring.w_nr,
					     DMA_TO_DEVICE);
	अगर (!ic->i_send_hdrs) अणु
		ret = -ENOMEM;
		rdsdebug("DMA send hdrs alloc failed\n");
		जाओ qp_out;
	पूर्ण

	ic->i_recv_hdrs = rds_dma_hdrs_alloc(rds_ibdev, &ic->i_recv_hdrs_dma,
					     ic->i_recv_ring.w_nr,
					     DMA_FROM_DEVICE);
	अगर (!ic->i_recv_hdrs) अणु
		ret = -ENOMEM;
		rdsdebug("DMA recv hdrs alloc failed\n");
		जाओ send_hdrs_dma_out;
	पूर्ण

	ic->i_ack = rds_dma_hdr_alloc(rds_ibdev->dev, &ic->i_ack_dma,
				      DMA_TO_DEVICE);
	अगर (!ic->i_ack) अणु
		ret = -ENOMEM;
		rdsdebug("DMA ack header alloc failed\n");
		जाओ recv_hdrs_dma_out;
	पूर्ण

	ic->i_sends = vzalloc_node(array_size(माप(काष्ठा rds_ib_send_work),
					      ic->i_send_ring.w_nr),
				   ibdev_to_node(dev));
	अगर (!ic->i_sends) अणु
		ret = -ENOMEM;
		rdsdebug("send allocation failed\n");
		जाओ ack_dma_out;
	पूर्ण

	ic->i_recvs = vzalloc_node(array_size(माप(काष्ठा rds_ib_recv_work),
					      ic->i_recv_ring.w_nr),
				   ibdev_to_node(dev));
	अगर (!ic->i_recvs) अणु
		ret = -ENOMEM;
		rdsdebug("recv allocation failed\n");
		जाओ sends_out;
	पूर्ण

	rds_ib_recv_init_ack(ic);

	rdsdebug("conn %p pd %p cq %p %p\n", conn, ic->i_pd,
		 ic->i_send_cq, ic->i_recv_cq);

	जाओ out;

sends_out:
	vमुक्त(ic->i_sends);

ack_dma_out:
	rds_dma_hdr_मुक्त(rds_ibdev->dev, ic->i_ack, ic->i_ack_dma,
			 DMA_TO_DEVICE);
	ic->i_ack = शून्य;

recv_hdrs_dma_out:
	rds_dma_hdrs_मुक्त(rds_ibdev, ic->i_recv_hdrs, ic->i_recv_hdrs_dma,
			  ic->i_recv_ring.w_nr, DMA_FROM_DEVICE);
	ic->i_recv_hdrs = शून्य;
	ic->i_recv_hdrs_dma = शून्य;

send_hdrs_dma_out:
	rds_dma_hdrs_मुक्त(rds_ibdev, ic->i_send_hdrs, ic->i_send_hdrs_dma,
			  ic->i_send_ring.w_nr, DMA_TO_DEVICE);
	ic->i_send_hdrs = शून्य;
	ic->i_send_hdrs_dma = शून्य;

qp_out:
	rdma_destroy_qp(ic->i_cm_id);
recv_cq_out:
	ib_destroy_cq(ic->i_recv_cq);
	ic->i_recv_cq = शून्य;
send_cq_out:
	ib_destroy_cq(ic->i_send_cq);
	ic->i_send_cq = शून्य;
rds_ibdev_out:
	rds_ib_हटाओ_conn(rds_ibdev, conn);
out:
	rds_ib_dev_put(rds_ibdev);

	वापस ret;
पूर्ण

अटल u32 rds_ib_protocol_compatible(काष्ठा rdma_cm_event *event, bool isv6)
अणु
	स्थिर जोड़ rds_ib_conn_priv *dp = event->param.conn.निजी_data;
	u8 data_len, major, minor;
	u32 version = 0;
	__be16 mask;
	u16 common;

	/*
	 * rdma_cm निजी data is odd - when there is any निजी data in the
	 * request, we will be given a pretty large buffer without telling us the
	 * original size. The only way to tell the dअगरference is by looking at
	 * the contents, which are initialized to zero.
	 * If the protocol version fields aren't set, this is a connection attempt
	 * from an older version. This could be 3.0 or 2.0 - we can't tell.
	 * We really should have changed this क्रम OFED 1.3 :-(
	 */

	/* Be paranoid. RDS always has privdata */
	अगर (!event->param.conn.निजी_data_len) अणु
		prपूर्णांकk(KERN_NOTICE "RDS incoming connection has no private data, "
			"rejecting\n");
		वापस 0;
	पूर्ण

	अगर (isv6) अणु
		data_len = माप(काष्ठा rds6_ib_connect_निजी);
		major = dp->ricp_v6.dp_protocol_major;
		minor = dp->ricp_v6.dp_protocol_minor;
		mask = dp->ricp_v6.dp_protocol_minor_mask;
	पूर्ण अन्यथा अणु
		data_len = माप(काष्ठा rds_ib_connect_निजी);
		major = dp->ricp_v4.dp_protocol_major;
		minor = dp->ricp_v4.dp_protocol_minor;
		mask = dp->ricp_v4.dp_protocol_minor_mask;
	पूर्ण

	/* Even अगर len is crap *now* I still want to check it. -ASG */
	अगर (event->param.conn.निजी_data_len < data_len || major == 0)
		वापस RDS_PROTOCOL_4_0;

	common = be16_to_cpu(mask) & RDS_IB_SUPPORTED_PROTOCOLS;
	अगर (major == 4 && common) अणु
		version = RDS_PROTOCOL_4_0;
		जबतक ((common >>= 1) != 0)
			version++;
	पूर्ण अन्यथा अगर (RDS_PROTOCOL_COMPAT_VERSION ==
		   RDS_PROTOCOL(major, minor)) अणु
		version = RDS_PROTOCOL_COMPAT_VERSION;
	पूर्ण अन्यथा अणु
		अगर (isv6)
			prपूर्णांकk_ratelimited(KERN_NOTICE "RDS: Connection from %pI6c using incompatible protocol version %u.%u\n",
					   &dp->ricp_v6.dp_saddr, major, minor);
		अन्यथा
			prपूर्णांकk_ratelimited(KERN_NOTICE "RDS: Connection from %pI4 using incompatible protocol version %u.%u\n",
					   &dp->ricp_v4.dp_saddr, major, minor);
	पूर्ण
	वापस version;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* Given an IPv6 address, find the net_device which hosts that address and
 * वापस its index.  This is used by the rds_ib_cm_handle_connect() code to
 * find the पूर्णांकerface index of where an incoming request comes from when
 * the request is using a link local address.
 *
 * Note one problem in this search.  It is possible that two पूर्णांकerfaces have
 * the same link local address.  Unक्रमtunately, this cannot be solved unless
 * the underlying layer gives us the पूर्णांकerface which an incoming RDMA connect
 * request comes from.
 */
अटल u32 __rds_find_अगरindex(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा net_device *dev;
	पूर्णांक idx = 0;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		अगर (ipv6_chk_addr(net, addr, dev, 1)) अणु
			idx = dev->अगरindex;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस idx;
पूर्ण
#पूर्ण_अगर

पूर्णांक rds_ib_cm_handle_connect(काष्ठा rdma_cm_id *cm_id,
			     काष्ठा rdma_cm_event *event, bool isv6)
अणु
	__be64 lguid = cm_id->route.path_rec->sgid.global.पूर्णांकerface_id;
	__be64 fguid = cm_id->route.path_rec->dgid.global.पूर्णांकerface_id;
	स्थिर काष्ठा rds_ib_conn_priv_cmn *dp_cmn;
	काष्ठा rds_connection *conn = शून्य;
	काष्ठा rds_ib_connection *ic = शून्य;
	काष्ठा rdma_conn_param conn_param;
	स्थिर जोड़ rds_ib_conn_priv *dp;
	जोड़ rds_ib_conn_priv dp_rep;
	काष्ठा in6_addr s_mapped_addr;
	काष्ठा in6_addr d_mapped_addr;
	स्थिर काष्ठा in6_addr *saddr6;
	स्थिर काष्ठा in6_addr *daddr6;
	पूर्णांक destroy = 1;
	u32 अगरindex = 0;
	u32 version;
	पूर्णांक err = 1;

	/* Check whether the remote protocol version matches ours. */
	version = rds_ib_protocol_compatible(event, isv6);
	अगर (!version) अणु
		err = RDS_RDMA_REJ_INCOMPAT;
		जाओ out;
	पूर्ण

	dp = event->param.conn.निजी_data;
	अगर (isv6) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		dp_cmn = &dp->ricp_v6.dp_cmn;
		saddr6 = &dp->ricp_v6.dp_saddr;
		daddr6 = &dp->ricp_v6.dp_daddr;
		/* If either address is link local, need to find the
		 * पूर्णांकerface index in order to create a proper RDS
		 * connection.
		 */
		अगर (ipv6_addr_type(daddr6) & IPV6_ADDR_LINKLOCAL) अणु
			/* Using init_net क्रम now ..  */
			अगरindex = __rds_find_अगरindex(&init_net, daddr6);
			/* No index found...  Need to bail out. */
			अगर (अगरindex == 0) अणु
				err = -EOPNOTSUPP;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (ipv6_addr_type(saddr6) & IPV6_ADDR_LINKLOCAL) अणु
			/* Use our address to find the correct index. */
			अगरindex = __rds_find_अगरindex(&init_net, daddr6);
			/* No index found...  Need to bail out. */
			अगर (अगरindex == 0) अणु
				err = -EOPNOTSUPP;
				जाओ out;
			पूर्ण
		पूर्ण
#अन्यथा
		err = -EOPNOTSUPP;
		जाओ out;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		dp_cmn = &dp->ricp_v4.dp_cmn;
		ipv6_addr_set_v4mapped(dp->ricp_v4.dp_saddr, &s_mapped_addr);
		ipv6_addr_set_v4mapped(dp->ricp_v4.dp_daddr, &d_mapped_addr);
		saddr6 = &s_mapped_addr;
		daddr6 = &d_mapped_addr;
	पूर्ण

	rdsdebug("saddr %pI6c daddr %pI6c RDSv%u.%u lguid 0x%llx fguid 0x%llx, tos:%d\n",
		 saddr6, daddr6, RDS_PROTOCOL_MAJOR(version),
		 RDS_PROTOCOL_MINOR(version),
		 (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(lguid),
		 (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(fguid), dp_cmn->ricpc_dp_toss);

	/* RDS/IB is not currently netns aware, thus init_net */
	conn = rds_conn_create(&init_net, daddr6, saddr6,
			       &rds_ib_transport, dp_cmn->ricpc_dp_toss,
			       GFP_KERNEL, अगरindex);
	अगर (IS_ERR(conn)) अणु
		rdsdebug("rds_conn_create failed (%ld)\n", PTR_ERR(conn));
		conn = शून्य;
		जाओ out;
	पूर्ण

	/*
	 * The connection request may occur जबतक the
	 * previous connection exist, e.g. in हाल of failover.
	 * But as connections may be initiated simultaneously
	 * by both hosts, we have a अक्रमom backoff mechanism -
	 * see the comment above rds_queue_reconnect()
	 */
	mutex_lock(&conn->c_cm_lock);
	अगर (!rds_conn_transition(conn, RDS_CONN_DOWN, RDS_CONN_CONNECTING)) अणु
		अगर (rds_conn_state(conn) == RDS_CONN_UP) अणु
			rdsdebug("incoming connect while connecting\n");
			rds_conn_drop(conn);
			rds_ib_stats_inc(s_ib_listen_बंदd_stale);
		पूर्ण अन्यथा
		अगर (rds_conn_state(conn) == RDS_CONN_CONNECTING) अणु
			/* Wait and see - our connect may still be succeeding */
			rds_ib_stats_inc(s_ib_connect_raced);
		पूर्ण
		जाओ out;
	पूर्ण

	ic = conn->c_transport_data;

	rds_ib_set_protocol(conn, version);
	rds_ib_set_flow_control(conn, be32_to_cpu(dp_cmn->ricpc_credit));

	/* If the peer gave us the last packet it saw, process this as अगर
	 * we had received a regular ACK. */
	अगर (dp_cmn->ricpc_ack_seq)
		rds_send_drop_acked(conn, be64_to_cpu(dp_cmn->ricpc_ack_seq),
				    शून्य);

	BUG_ON(cm_id->context);
	BUG_ON(ic->i_cm_id);

	ic->i_cm_id = cm_id;
	cm_id->context = conn;

	/* We got halfway through setting up the ib_connection, अगर we
	 * fail now, we have to take the दीर्घ route out of this mess. */
	destroy = 0;

	err = rds_ib_setup_qp(conn);
	अगर (err) अणु
		rds_ib_conn_error(conn, "rds_ib_setup_qp failed (%d)\n", err);
		जाओ out;
	पूर्ण

	rds_ib_cm_fill_conn_param(conn, &conn_param, &dp_rep, version,
				  event->param.conn.responder_resources,
				  event->param.conn.initiator_depth, isv6);

	rdma_set_min_rnr_समयr(cm_id, IB_RNR_TIMER_000_32);
	/* rdma_accept() calls rdma_reject() पूर्णांकernally अगर it fails */
	अगर (rdma_accept(cm_id, &conn_param))
		rds_ib_conn_error(conn, "rdma_accept failed\n");

out:
	अगर (conn)
		mutex_unlock(&conn->c_cm_lock);
	अगर (err)
		rdma_reject(cm_id, &err, माप(पूर्णांक),
			    IB_CM_REJ_CONSUMER_DEFINED);
	वापस destroy;
पूर्ण


पूर्णांक rds_ib_cm_initiate_connect(काष्ठा rdma_cm_id *cm_id, bool isv6)
अणु
	काष्ठा rds_connection *conn = cm_id->context;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा rdma_conn_param conn_param;
	जोड़ rds_ib_conn_priv dp;
	पूर्णांक ret;

	/* If the peer करोesn't करो protocol negotiation, we must
	 * शेष to RDSv3.0 */
	rds_ib_set_protocol(conn, RDS_PROTOCOL_4_1);
	ic->i_flowctl = rds_ib_sysctl_flow_control;	/* advertise flow control */

	ret = rds_ib_setup_qp(conn);
	अगर (ret) अणु
		rds_ib_conn_error(conn, "rds_ib_setup_qp failed (%d)\n", ret);
		जाओ out;
	पूर्ण

	rds_ib_cm_fill_conn_param(conn, &conn_param, &dp,
				  conn->c_proposed_version,
				  अच_पूर्णांक_उच्च, अच_पूर्णांक_उच्च, isv6);
	ret = rdma_connect_locked(cm_id, &conn_param);
	अगर (ret)
		rds_ib_conn_error(conn, "rdma_connect_locked failed (%d)\n",
				  ret);

out:
	/* Beware - वापसing non-zero tells the rdma_cm to destroy
	 * the cm_id. We should certainly not करो it as दीर्घ as we still
	 * "own" the cm_id. */
	अगर (ret) अणु
		अगर (ic->i_cm_id == cm_id)
			ret = 0;
	पूर्ण
	ic->i_active_side = true;
	वापस ret;
पूर्ण

पूर्णांक rds_ib_conn_path_connect(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;
	काष्ठा sockaddr_storage src, dest;
	rdma_cm_event_handler handler;
	काष्ठा rds_ib_connection *ic;
	पूर्णांक ret;

	ic = conn->c_transport_data;

	/* XXX I wonder what affect the port space has */
	/* delegate cm event handler to rdma_transport */
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (conn->c_isv6)
		handler = rds6_rdma_cm_event_handler;
	अन्यथा
#पूर्ण_अगर
		handler = rds_rdma_cm_event_handler;
	ic->i_cm_id = rdma_create_id(&init_net, handler, conn,
				     RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(ic->i_cm_id)) अणु
		ret = PTR_ERR(ic->i_cm_id);
		ic->i_cm_id = शून्य;
		rdsdebug("rdma_create_id() failed: %d\n", ret);
		जाओ out;
	पूर्ण

	rdsdebug("created cm id %p for conn %p\n", ic->i_cm_id, conn);

	अगर (ipv6_addr_v4mapped(&conn->c_faddr)) अणु
		काष्ठा sockaddr_in *sin;

		sin = (काष्ठा sockaddr_in *)&src;
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = conn->c_laddr.s6_addr32[3];
		sin->sin_port = 0;

		sin = (काष्ठा sockaddr_in *)&dest;
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = conn->c_faddr.s6_addr32[3];
		sin->sin_port = htons(RDS_PORT);
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *sin6;

		sin6 = (काष्ठा sockaddr_in6 *)&src;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_addr = conn->c_laddr;
		sin6->sin6_port = 0;
		sin6->sin6_scope_id = conn->c_dev_अगर;

		sin6 = (काष्ठा sockaddr_in6 *)&dest;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_addr = conn->c_faddr;
		sin6->sin6_port = htons(RDS_CM_PORT);
		sin6->sin6_scope_id = conn->c_dev_अगर;
	पूर्ण

	ret = rdma_resolve_addr(ic->i_cm_id, (काष्ठा sockaddr *)&src,
				(काष्ठा sockaddr *)&dest,
				RDS_RDMA_RESOLVE_TIMEOUT_MS);
	अगर (ret) अणु
		rdsdebug("addr resolve failed for cm id %p: %d\n", ic->i_cm_id,
			 ret);
		rdma_destroy_id(ic->i_cm_id);
		ic->i_cm_id = शून्य;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * This is so careful about only cleaning up resources that were built up
 * so that it can be called at any poपूर्णांक during startup.  In fact it
 * can be called multiple बार क्रम a given connection.
 */
व्योम rds_ib_conn_path_shutकरोwn(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	पूर्णांक err = 0;

	rdsdebug("cm %p pd %p cq %p %p qp %p\n", ic->i_cm_id,
		 ic->i_pd, ic->i_send_cq, ic->i_recv_cq,
		 ic->i_cm_id ? ic->i_cm_id->qp : शून्य);

	अगर (ic->i_cm_id) अणु
		rdsdebug("disconnecting cm %p\n", ic->i_cm_id);
		err = rdma_disconnect(ic->i_cm_id);
		अगर (err) अणु
			/* Actually this may happen quite frequently, when
			 * an outgoing connect raced with an incoming connect.
			 */
			rdsdebug("failed to disconnect, cm: %p err %d\n",
				ic->i_cm_id, err);
		पूर्ण

		/* kick off "flush_worker" क्रम all pools in order to reap
		 * all FRMR registrations that are still marked "FRMR_IS_INUSE"
		 */
		rds_ib_flush_mrs();

		/*
		 * We want to रुको क्रम tx and rx completion to finish
		 * beक्रमe we tear करोwn the connection, but we have to be
		 * careful not to get stuck रुकोing on a send ring that
		 * only has unसंकेतed sends in it.  We've shutकरोwn new
		 * sends beक्रमe getting here so by रुकोing क्रम संकेतed
		 * sends to complete we're ensured that there will be no
		 * more tx processing.
		 */
		रुको_event(rds_ib_ring_empty_रुको,
			   rds_ib_ring_empty(&ic->i_recv_ring) &&
			   (atomic_पढ़ो(&ic->i_संकेतed_sends) == 0) &&
			   (atomic_पढ़ो(&ic->i_fastreg_inuse_count) == 0) &&
			   (atomic_पढ़ो(&ic->i_fastreg_wrs) == RDS_IB_DEFAULT_FR_WR));
		tasklet_समाप्त(&ic->i_send_tasklet);
		tasklet_समाप्त(&ic->i_recv_tasklet);

		atomic_set(&ic->i_cq_quiesce, 1);

		/* first destroy the ib state that generates callbacks */
		अगर (ic->i_cm_id->qp)
			rdma_destroy_qp(ic->i_cm_id);
		अगर (ic->i_send_cq) अणु
			अगर (ic->rds_ibdev)
				ibdev_put_vector(ic->rds_ibdev, ic->i_scq_vector);
			ib_destroy_cq(ic->i_send_cq);
		पूर्ण

		अगर (ic->i_recv_cq) अणु
			अगर (ic->rds_ibdev)
				ibdev_put_vector(ic->rds_ibdev, ic->i_rcq_vector);
			ib_destroy_cq(ic->i_recv_cq);
		पूर्ण

		अगर (ic->rds_ibdev) अणु
			/* then मुक्त the resources that ib callbacks use */
			अगर (ic->i_send_hdrs) अणु
				rds_dma_hdrs_मुक्त(ic->rds_ibdev,
						  ic->i_send_hdrs,
						  ic->i_send_hdrs_dma,
						  ic->i_send_ring.w_nr,
						  DMA_TO_DEVICE);
				ic->i_send_hdrs = शून्य;
				ic->i_send_hdrs_dma = शून्य;
			पूर्ण

			अगर (ic->i_recv_hdrs) अणु
				rds_dma_hdrs_मुक्त(ic->rds_ibdev,
						  ic->i_recv_hdrs,
						  ic->i_recv_hdrs_dma,
						  ic->i_recv_ring.w_nr,
						  DMA_FROM_DEVICE);
				ic->i_recv_hdrs = शून्य;
				ic->i_recv_hdrs_dma = शून्य;
			पूर्ण

			अगर (ic->i_ack) अणु
				rds_dma_hdr_मुक्त(ic->rds_ibdev->dev, ic->i_ack,
						 ic->i_ack_dma, DMA_TO_DEVICE);
				ic->i_ack = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN_ON(ic->i_send_hdrs);
			WARN_ON(ic->i_send_hdrs_dma);
			WARN_ON(ic->i_recv_hdrs);
			WARN_ON(ic->i_recv_hdrs_dma);
			WARN_ON(ic->i_ack);
		पूर्ण

		अगर (ic->i_sends)
			rds_ib_send_clear_ring(ic);
		अगर (ic->i_recvs)
			rds_ib_recv_clear_ring(ic);

		rdma_destroy_id(ic->i_cm_id);

		/*
		 * Move connection back to the nodev list.
		 */
		अगर (ic->rds_ibdev)
			rds_ib_हटाओ_conn(ic->rds_ibdev, conn);

		ic->i_cm_id = शून्य;
		ic->i_pd = शून्य;
		ic->i_send_cq = शून्य;
		ic->i_recv_cq = शून्य;
	पूर्ण
	BUG_ON(ic->rds_ibdev);

	/* Clear pending transmit */
	अगर (ic->i_data_op) अणु
		काष्ठा rds_message *rm;

		rm = container_of(ic->i_data_op, काष्ठा rds_message, data);
		rds_message_put(rm);
		ic->i_data_op = शून्य;
	पूर्ण

	/* Clear the ACK state */
	clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
#अगर_घोषित KERNEL_HAS_ATOMIC64
	atomic64_set(&ic->i_ack_next, 0);
#अन्यथा
	ic->i_ack_next = 0;
#पूर्ण_अगर
	ic->i_ack_recv = 0;

	/* Clear flow control state */
	ic->i_flowctl = 0;
	atomic_set(&ic->i_credits, 0);

	/* Re-init rings, but retain sizes. */
	rds_ib_ring_init(&ic->i_send_ring, ic->i_send_ring.w_nr);
	rds_ib_ring_init(&ic->i_recv_ring, ic->i_recv_ring.w_nr);

	अगर (ic->i_ibinc) अणु
		rds_inc_put(&ic->i_ibinc->ii_inc);
		ic->i_ibinc = शून्य;
	पूर्ण

	vमुक्त(ic->i_sends);
	ic->i_sends = शून्य;
	vमुक्त(ic->i_recvs);
	ic->i_recvs = शून्य;
	ic->i_active_side = false;
पूर्ण

पूर्णांक rds_ib_conn_alloc(काष्ठा rds_connection *conn, gfp_t gfp)
अणु
	काष्ठा rds_ib_connection *ic;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* XXX too lazy? */
	ic = kzalloc(माप(काष्ठा rds_ib_connection), gfp);
	अगर (!ic)
		वापस -ENOMEM;

	ret = rds_ib_recv_alloc_caches(ic, gfp);
	अगर (ret) अणु
		kमुक्त(ic);
		वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&ic->ib_node);
	tasklet_init(&ic->i_send_tasklet, rds_ib_tasklet_fn_send,
		     (अचिन्हित दीर्घ)ic);
	tasklet_init(&ic->i_recv_tasklet, rds_ib_tasklet_fn_recv,
		     (अचिन्हित दीर्घ)ic);
	mutex_init(&ic->i_recv_mutex);
#अगर_अघोषित KERNEL_HAS_ATOMIC64
	spin_lock_init(&ic->i_ack_lock);
#पूर्ण_अगर
	atomic_set(&ic->i_संकेतed_sends, 0);
	atomic_set(&ic->i_fastreg_wrs, RDS_IB_DEFAULT_FR_WR);

	/*
	 * rds_ib_conn_shutकरोwn() रुकोs क्रम these to be emptied so they
	 * must be initialized beक्रमe it can be called.
	 */
	rds_ib_ring_init(&ic->i_send_ring, 0);
	rds_ib_ring_init(&ic->i_recv_ring, 0);

	ic->conn = conn;
	conn->c_transport_data = ic;

	spin_lock_irqsave(&ib_nodev_conns_lock, flags);
	list_add_tail(&ic->ib_node, &ib_nodev_conns);
	spin_unlock_irqrestore(&ib_nodev_conns_lock, flags);


	rdsdebug("conn %p conn ic %p\n", conn, conn->c_transport_data);
	वापस 0;
पूर्ण

/*
 * Free a connection. Connection must be shut करोwn and not set क्रम reconnect.
 */
व्योम rds_ib_conn_मुक्त(व्योम *arg)
अणु
	काष्ठा rds_ib_connection *ic = arg;
	spinlock_t	*lock_ptr;

	rdsdebug("ic %p\n", ic);

	/*
	 * Conn is either on a dev's list or on the nodev list.
	 * A race with shutकरोwn() or connect() would cause problems
	 * (since rds_ibdev would change) but that should never happen.
	 */
	lock_ptr = ic->rds_ibdev ? &ic->rds_ibdev->spinlock : &ib_nodev_conns_lock;

	spin_lock_irq(lock_ptr);
	list_del(&ic->ib_node);
	spin_unlock_irq(lock_ptr);

	rds_ib_recv_मुक्त_caches(ic);

	kमुक्त(ic);
पूर्ण


/*
 * An error occurred on the connection
 */
व्योम
__rds_ib_conn_error(काष्ठा rds_connection *conn, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	rds_conn_drop(conn);

	बहु_शुरू(ap, fmt);
	vprपूर्णांकk(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण
