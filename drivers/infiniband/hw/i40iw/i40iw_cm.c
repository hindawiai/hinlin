<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#समावेश <linux/atomic.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/net.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/list.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <net/arp.h>
#समावेश <net/ndisc.h>
#समावेश <net/neighbour.h>
#समावेश <net/route.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip_fib.h>
#समावेश <net/secure_seq.h>
#समावेश <net/tcp.h>
#समावेश <यंत्र/checksum.h>

#समावेश "i40iw.h"

अटल व्योम i40iw_rem_ref_cm_node(काष्ठा i40iw_cm_node *);
अटल व्योम i40iw_cm_post_event(काष्ठा i40iw_cm_event *event);
अटल व्योम i40iw_disconnect_worker(काष्ठा work_काष्ठा *work);

/**
 * i40iw_मुक्त_sqbuf - put back puda buffer अगर refcount = 0
 * @vsi: poपूर्णांकer to vsi काष्ठाure
 * @bufp: puda buffer to मुक्त
 */
व्योम i40iw_मुक्त_sqbuf(काष्ठा i40iw_sc_vsi *vsi, व्योम *bufp)
अणु
	काष्ठा i40iw_puda_buf *buf = (काष्ठा i40iw_puda_buf *)bufp;
	काष्ठा i40iw_puda_rsrc *ilq = vsi->ilq;

	अगर (!atomic_dec_वापस(&buf->refcount))
		i40iw_puda_ret_bufpool(ilq, buf);
पूर्ण

/**
 * i40iw_derive_hw_ird_setting - Calculate IRD
 *
 * @cm_ird: IRD of connection's node
 *
 * The ird from the connection is rounded to a supported HW
 * setting (2,8,32,64) and then encoded क्रम ird_size field of
 * qp_ctx
 */
अटल u8 i40iw_derive_hw_ird_setting(u16 cm_ird)
अणु
	u8 encoded_ird_size;

	/* ird_size field is encoded in qp_ctx */
	चयन (cm_ird ? roundup_घात_of_two(cm_ird) : 0) अणु
	हाल I40IW_HW_IRD_SETTING_64:
		encoded_ird_size = 3;
		अवरोध;
	हाल I40IW_HW_IRD_SETTING_32:
	हाल I40IW_HW_IRD_SETTING_16:
		encoded_ird_size = 2;
		अवरोध;
	हाल I40IW_HW_IRD_SETTING_8:
	हाल I40IW_HW_IRD_SETTING_4:
		encoded_ird_size = 1;
		अवरोध;
	हाल I40IW_HW_IRD_SETTING_2:
	शेष:
		encoded_ird_size = 0;
		अवरोध;
	पूर्ण
	वापस encoded_ird_size;
पूर्ण

/**
 * i40iw_record_ird_ord - Record IRD/ORD passed in
 * @cm_node: connection's node
 * @conn_ird: connection IRD
 * @conn_ord: connection ORD
 */
अटल व्योम i40iw_record_ird_ord(काष्ठा i40iw_cm_node *cm_node, u32 conn_ird,
				 u32 conn_ord)
अणु
	अगर (conn_ird > I40IW_MAX_IRD_SIZE)
		conn_ird = I40IW_MAX_IRD_SIZE;

	अगर (conn_ord > I40IW_MAX_ORD_SIZE)
		conn_ord = I40IW_MAX_ORD_SIZE;
	अन्यथा अगर (!conn_ord && cm_node->send_rdma0_op == SEND_RDMA_READ_ZERO)
		conn_ord = 1;

	cm_node->ird_size = conn_ird;
	cm_node->ord_size = conn_ord;
पूर्ण

/**
 * i40iw_copy_ip_ntohl - change network to host ip
 * @dst: host ip
 * @src: big endian
 */
व्योम i40iw_copy_ip_ntohl(u32 *dst, __be32 *src)
अणु
	*dst++ = ntohl(*src++);
	*dst++ = ntohl(*src++);
	*dst++ = ntohl(*src++);
	*dst = ntohl(*src);
पूर्ण

/**
 * i40iw_copy_ip_htonl - change host addr to network ip
 * @dst: host ip
 * @src: little endian
 */
अटल अंतरभूत व्योम i40iw_copy_ip_htonl(__be32 *dst, u32 *src)
अणु
	*dst++ = htonl(*src++);
	*dst++ = htonl(*src++);
	*dst++ = htonl(*src++);
	*dst = htonl(*src);
पूर्ण

/**
 * i40iw_fill_sockaddr4 - get addr info क्रम passive connection
 * @cm_node: connection's node
 * @event: upper layer's cm event
 */
अटल अंतरभूत व्योम i40iw_fill_sockaddr4(काष्ठा i40iw_cm_node *cm_node,
					काष्ठा iw_cm_event *event)
अणु
	काष्ठा sockaddr_in *laddr = (काष्ठा sockaddr_in *)&event->local_addr;
	काष्ठा sockaddr_in *raddr = (काष्ठा sockaddr_in *)&event->remote_addr;

	laddr->sin_family = AF_INET;
	raddr->sin_family = AF_INET;

	laddr->sin_port = htons(cm_node->loc_port);
	raddr->sin_port = htons(cm_node->rem_port);

	laddr->sin_addr.s_addr = htonl(cm_node->loc_addr[0]);
	raddr->sin_addr.s_addr = htonl(cm_node->rem_addr[0]);
पूर्ण

/**
 * i40iw_fill_sockaddr6 - get ipv6 addr info क्रम passive side
 * @cm_node: connection's node
 * @event: upper layer's cm event
 */
अटल अंतरभूत व्योम i40iw_fill_sockaddr6(काष्ठा i40iw_cm_node *cm_node,
					काष्ठा iw_cm_event *event)
अणु
	काष्ठा sockaddr_in6 *laddr6 = (काष्ठा sockaddr_in6 *)&event->local_addr;
	काष्ठा sockaddr_in6 *raddr6 = (काष्ठा sockaddr_in6 *)&event->remote_addr;

	laddr6->sin6_family = AF_INET6;
	raddr6->sin6_family = AF_INET6;

	laddr6->sin6_port = htons(cm_node->loc_port);
	raddr6->sin6_port = htons(cm_node->rem_port);

	i40iw_copy_ip_htonl(laddr6->sin6_addr.in6_u.u6_addr32,
			    cm_node->loc_addr);
	i40iw_copy_ip_htonl(raddr6->sin6_addr.in6_u.u6_addr32,
			    cm_node->rem_addr);
पूर्ण

/**
 * i40iw_get_addr_info
 * @cm_node: contains ip/tcp info
 * @cm_info: to get a copy of the cm_node ip/tcp info
*/
अटल व्योम i40iw_get_addr_info(काष्ठा i40iw_cm_node *cm_node,
				काष्ठा i40iw_cm_info *cm_info)
अणु
	cm_info->ipv4 = cm_node->ipv4;
	cm_info->vlan_id = cm_node->vlan_id;
	स_नकल(cm_info->loc_addr, cm_node->loc_addr, माप(cm_info->loc_addr));
	स_नकल(cm_info->rem_addr, cm_node->rem_addr, माप(cm_info->rem_addr));
	cm_info->loc_port = cm_node->loc_port;
	cm_info->rem_port = cm_node->rem_port;
	cm_info->user_pri = cm_node->user_pri;
पूर्ण

/**
 * i40iw_get_cmevent_info - क्रम cm event upcall
 * @cm_node: connection's node
 * @cm_id: upper layers cm काष्ठा क्रम the event
 * @event: upper layer's cm event
 */
अटल अंतरभूत व्योम i40iw_get_cmevent_info(काष्ठा i40iw_cm_node *cm_node,
					  काष्ठा iw_cm_id *cm_id,
					  काष्ठा iw_cm_event *event)
अणु
	स_नकल(&event->local_addr, &cm_id->m_local_addr,
	       माप(event->local_addr));
	स_नकल(&event->remote_addr, &cm_id->m_remote_addr,
	       माप(event->remote_addr));
	अगर (cm_node) अणु
		event->निजी_data = (व्योम *)cm_node->pdata_buf;
		event->निजी_data_len = (u8)cm_node->pdata.size;
		event->ird = cm_node->ird_size;
		event->ord = cm_node->ord_size;
	पूर्ण
पूर्ण

/**
 * i40iw_send_cm_event - upcall cm's event handler
 * @cm_node: connection's node
 * @cm_id: upper layer's cm info काष्ठा
 * @type: Event type to indicate
 * @status: status क्रम the event type
 */
अटल पूर्णांक i40iw_send_cm_event(काष्ठा i40iw_cm_node *cm_node,
			       काष्ठा iw_cm_id *cm_id,
			       क्रमागत iw_cm_event_type type,
			       पूर्णांक status)
अणु
	काष्ठा iw_cm_event event;

	स_रखो(&event, 0, माप(event));
	event.event = type;
	event.status = status;
	चयन (type) अणु
	हाल IW_CM_EVENT_CONNECT_REQUEST:
		अगर (cm_node->ipv4)
			i40iw_fill_sockaddr4(cm_node, &event);
		अन्यथा
			i40iw_fill_sockaddr6(cm_node, &event);
		event.provider_data = (व्योम *)cm_node;
		event.निजी_data = (व्योम *)cm_node->pdata_buf;
		event.निजी_data_len = (u8)cm_node->pdata.size;
		event.ird = cm_node->ird_size;
		अवरोध;
	हाल IW_CM_EVENT_CONNECT_REPLY:
		i40iw_get_cmevent_info(cm_node, cm_id, &event);
		अवरोध;
	हाल IW_CM_EVENT_ESTABLISHED:
		event.ird = cm_node->ird_size;
		event.ord = cm_node->ord_size;
		अवरोध;
	हाल IW_CM_EVENT_DISCONNECT:
		अवरोध;
	हाल IW_CM_EVENT_CLOSE:
		अवरोध;
	शेष:
		i40iw_pr_err("event type received type = %d\n", type);
		वापस -1;
	पूर्ण
	वापस cm_id->event_handler(cm_id, &event);
पूर्ण

/**
 * i40iw_create_event - create cm event
 * @cm_node: connection's node
 * @type: Event type to generate
 */
अटल काष्ठा i40iw_cm_event *i40iw_create_event(काष्ठा i40iw_cm_node *cm_node,
						 क्रमागत i40iw_cm_event_type type)
अणु
	काष्ठा i40iw_cm_event *event;

	अगर (!cm_node->cm_id)
		वापस शून्य;

	event = kzalloc(माप(*event), GFP_ATOMIC);

	अगर (!event)
		वापस शून्य;

	event->type = type;
	event->cm_node = cm_node;
	स_नकल(event->cm_info.rem_addr, cm_node->rem_addr, माप(event->cm_info.rem_addr));
	स_नकल(event->cm_info.loc_addr, cm_node->loc_addr, माप(event->cm_info.loc_addr));
	event->cm_info.rem_port = cm_node->rem_port;
	event->cm_info.loc_port = cm_node->loc_port;
	event->cm_info.cm_id = cm_node->cm_id;

	i40iw_debug(cm_node->dev,
		    I40IW_DEBUG_CM,
		    "node=%p event=%p type=%u dst=%pI4 src=%pI4\n",
		    cm_node,
		    event,
		    type,
		    event->cm_info.loc_addr,
		    event->cm_info.rem_addr);

	i40iw_cm_post_event(event);
	वापस event;
पूर्ण

/**
 * i40iw_मुक्त_retrans_entry - मुक्त send entry
 * @cm_node: connection's node
 */
अटल व्योम i40iw_मुक्त_retrans_entry(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_device *iwdev = cm_node->iwdev;
	काष्ठा i40iw_समयr_entry *send_entry;

	send_entry = cm_node->send_entry;
	अगर (send_entry) अणु
		cm_node->send_entry = शून्य;
		i40iw_मुक्त_sqbuf(&iwdev->vsi, (व्योम *)send_entry->sqbuf);
		kमुक्त(send_entry);
		atomic_dec(&cm_node->ref_count);
	पूर्ण
पूर्ण

/**
 * i40iw_cleanup_retrans_entry - मुक्त send entry with lock
 * @cm_node: connection's node
 */
अटल व्योम i40iw_cleanup_retrans_entry(काष्ठा i40iw_cm_node *cm_node)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm_node->retrans_list_lock, flags);
	i40iw_मुक्त_retrans_entry(cm_node);
	spin_unlock_irqrestore(&cm_node->retrans_list_lock, flags);
पूर्ण

/**
 * i40iw_क्रमm_cm_frame - get a मुक्त packet and build frame
 * @cm_node: connection's node ionfo to use in frame
 * @options: poपूर्णांकer to options info
 * @hdr: poपूर्णांकer mpa header
 * @pdata: poपूर्णांकer to निजी data
 * @flags:  indicates FIN or ACK
 */
अटल काष्ठा i40iw_puda_buf *i40iw_क्रमm_cm_frame(काष्ठा i40iw_cm_node *cm_node,
						  काष्ठा i40iw_kmem_info *options,
						  काष्ठा i40iw_kmem_info *hdr,
						  काष्ठा i40iw_kmem_info *pdata,
						  u8 flags)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;
	काष्ठा i40iw_sc_vsi *vsi = &cm_node->iwdev->vsi;
	u8 *buf;

	काष्ठा tcphdr *tcph;
	काष्ठा iphdr *iph;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा ethhdr *ethh;
	u16 packetsize;
	u16 eth_hlen = ETH_HLEN;
	u32 opts_len = 0;
	u32 pd_len = 0;
	u32 hdr_len = 0;
	u16 vtag;

	sqbuf = i40iw_puda_get_bufpool(vsi->ilq);
	अगर (!sqbuf)
		वापस शून्य;
	buf = sqbuf->mem.va;

	अगर (options)
		opts_len = (u32)options->size;

	अगर (hdr)
		hdr_len = hdr->size;

	अगर (pdata)
		pd_len = pdata->size;

	अगर (cm_node->vlan_id <= VLAN_VID_MASK)
		eth_hlen += 4;

	अगर (cm_node->ipv4)
		packetsize = माप(*iph) + माप(*tcph);
	अन्यथा
		packetsize = माप(*ip6h) + माप(*tcph);
	packetsize += opts_len + hdr_len + pd_len;

	स_रखो(buf, 0x00, eth_hlen + packetsize);

	sqbuf->totallen = packetsize + eth_hlen;
	sqbuf->maclen = eth_hlen;
	sqbuf->tcphlen = माप(*tcph) + opts_len;
	sqbuf->scratch = (व्योम *)cm_node;

	ethh = (काष्ठा ethhdr *)buf;
	buf += eth_hlen;

	अगर (cm_node->ipv4) अणु
		sqbuf->ipv4 = true;

		iph = (काष्ठा iphdr *)buf;
		buf += माप(*iph);
		tcph = (काष्ठा tcphdr *)buf;
		buf += माप(*tcph);

		ether_addr_copy(ethh->h_dest, cm_node->rem_mac);
		ether_addr_copy(ethh->h_source, cm_node->loc_mac);
		अगर (cm_node->vlan_id <= VLAN_VID_MASK) अणु
			((काष्ठा vlan_ethhdr *)ethh)->h_vlan_proto = htons(ETH_P_8021Q);
			vtag = (cm_node->user_pri << VLAN_PRIO_SHIFT) | cm_node->vlan_id;
			((काष्ठा vlan_ethhdr *)ethh)->h_vlan_TCI = htons(vtag);

			((काष्ठा vlan_ethhdr *)ethh)->h_vlan_encapsulated_proto = htons(ETH_P_IP);
		पूर्ण अन्यथा अणु
			ethh->h_proto = htons(ETH_P_IP);
		पूर्ण

		iph->version = IPVERSION;
		iph->ihl = 5;	/* 5 * 4Byte words, IP headr len */
		iph->tos = cm_node->tos;
		iph->tot_len = htons(packetsize);
		iph->id = htons(++cm_node->tcp_cntxt.loc_id);

		iph->frag_off = htons(0x4000);
		iph->ttl = 0x40;
		iph->protocol = IPPROTO_TCP;
		iph->saddr = htonl(cm_node->loc_addr[0]);
		iph->daddr = htonl(cm_node->rem_addr[0]);
	पूर्ण अन्यथा अणु
		sqbuf->ipv4 = false;
		ip6h = (काष्ठा ipv6hdr *)buf;
		buf += माप(*ip6h);
		tcph = (काष्ठा tcphdr *)buf;
		buf += माप(*tcph);

		ether_addr_copy(ethh->h_dest, cm_node->rem_mac);
		ether_addr_copy(ethh->h_source, cm_node->loc_mac);
		अगर (cm_node->vlan_id <= VLAN_VID_MASK) अणु
			((काष्ठा vlan_ethhdr *)ethh)->h_vlan_proto = htons(ETH_P_8021Q);
			vtag = (cm_node->user_pri << VLAN_PRIO_SHIFT) | cm_node->vlan_id;
			((काष्ठा vlan_ethhdr *)ethh)->h_vlan_TCI = htons(vtag);
			((काष्ठा vlan_ethhdr *)ethh)->h_vlan_encapsulated_proto = htons(ETH_P_IPV6);
		पूर्ण अन्यथा अणु
			ethh->h_proto = htons(ETH_P_IPV6);
		पूर्ण
		ip6h->version = 6;
		ip6h->priority = cm_node->tos >> 4;
		ip6h->flow_lbl[0] = cm_node->tos << 4;
		ip6h->flow_lbl[1] = 0;
		ip6h->flow_lbl[2] = 0;
		ip6h->payload_len = htons(packetsize - माप(*ip6h));
		ip6h->nexthdr = 6;
		ip6h->hop_limit = 128;
		i40iw_copy_ip_htonl(ip6h->saddr.in6_u.u6_addr32,
				    cm_node->loc_addr);
		i40iw_copy_ip_htonl(ip6h->daddr.in6_u.u6_addr32,
				    cm_node->rem_addr);
	पूर्ण

	tcph->source = htons(cm_node->loc_port);
	tcph->dest = htons(cm_node->rem_port);

	tcph->seq = htonl(cm_node->tcp_cntxt.loc_seq_num);

	अगर (flags & SET_ACK) अणु
		cm_node->tcp_cntxt.loc_ack_num = cm_node->tcp_cntxt.rcv_nxt;
		tcph->ack_seq = htonl(cm_node->tcp_cntxt.loc_ack_num);
		tcph->ack = 1;
	पूर्ण अन्यथा अणु
		tcph->ack_seq = 0;
	पूर्ण

	अगर (flags & SET_SYN) अणु
		cm_node->tcp_cntxt.loc_seq_num++;
		tcph->syn = 1;
	पूर्ण अन्यथा अणु
		cm_node->tcp_cntxt.loc_seq_num += hdr_len + pd_len;
	पूर्ण

	अगर (flags & SET_FIN) अणु
		cm_node->tcp_cntxt.loc_seq_num++;
		tcph->fin = 1;
	पूर्ण

	अगर (flags & SET_RST)
		tcph->rst = 1;

	tcph->करोff = (u16)((माप(*tcph) + opts_len + 3) >> 2);
	sqbuf->tcphlen = tcph->करोff << 2;
	tcph->winकरोw = htons(cm_node->tcp_cntxt.rcv_wnd);
	tcph->urg_ptr = 0;

	अगर (opts_len) अणु
		स_नकल(buf, options->addr, opts_len);
		buf += opts_len;
	पूर्ण

	अगर (hdr_len) अणु
		स_नकल(buf, hdr->addr, hdr_len);
		buf += hdr_len;
	पूर्ण

	अगर (pdata && pdata->addr)
		स_नकल(buf, pdata->addr, pdata->size);

	atomic_set(&sqbuf->refcount, 1);

	वापस sqbuf;
पूर्ण

/**
 * i40iw_send_reset - Send RST packet
 * @cm_node: connection's node
 */
पूर्णांक i40iw_send_reset(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;
	पूर्णांक flags = SET_RST | SET_ACK;

	sqbuf = i40iw_क्रमm_cm_frame(cm_node, शून्य, शून्य, शून्य, flags);
	अगर (!sqbuf) अणु
		i40iw_pr_err("no sqbuf\n");
		वापस -1;
	पूर्ण

	वापस i40iw_schedule_cm_समयr(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 0, 1);
पूर्ण

/**
 * i40iw_active_खोलो_err - send event क्रम active side cm error
 * @cm_node: connection's node
 * @reset: Flag to send reset or not
 */
अटल व्योम i40iw_active_खोलो_err(काष्ठा i40iw_cm_node *cm_node, bool reset)
अणु
	i40iw_cleanup_retrans_entry(cm_node);
	cm_node->cm_core->stats_connect_errs++;
	अगर (reset) अणु
		i40iw_debug(cm_node->dev,
			    I40IW_DEBUG_CM,
			    "%s cm_node=%p state=%d\n",
			    __func__,
			    cm_node,
			    cm_node->state);
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
	पूर्ण

	cm_node->state = I40IW_CM_STATE_CLOSED;
	i40iw_create_event(cm_node, I40IW_CM_EVENT_ABORTED);
पूर्ण

/**
 * i40iw_passive_खोलो_err - handle passive side cm error
 * @cm_node: connection's node
 * @reset: send reset or just मुक्त cm_node
 */
अटल व्योम i40iw_passive_खोलो_err(काष्ठा i40iw_cm_node *cm_node, bool reset)
अणु
	i40iw_cleanup_retrans_entry(cm_node);
	cm_node->cm_core->stats_passive_errs++;
	cm_node->state = I40IW_CM_STATE_CLOSED;
	i40iw_debug(cm_node->dev,
		    I40IW_DEBUG_CM,
		    "%s cm_node=%p state =%d\n",
		    __func__,
		    cm_node,
		    cm_node->state);
	अगर (reset)
		i40iw_send_reset(cm_node);
	अन्यथा
		i40iw_rem_ref_cm_node(cm_node);
पूर्ण

/**
 * i40iw_event_connect_error - to create connect error event
 * @event: cm inक्रमmation क्रम connect event
 */
अटल व्योम i40iw_event_connect_error(काष्ठा i40iw_cm_event *event)
अणु
	काष्ठा i40iw_qp *iwqp;
	काष्ठा iw_cm_id *cm_id;

	cm_id = event->cm_node->cm_id;
	अगर (!cm_id)
		वापस;

	iwqp = cm_id->provider_data;

	अगर (!iwqp || !iwqp->iwdev)
		वापस;

	iwqp->cm_id = शून्य;
	cm_id->provider_data = शून्य;
	i40iw_send_cm_event(event->cm_node, cm_id,
			    IW_CM_EVENT_CONNECT_REPLY,
			    -ECONNRESET);
	cm_id->rem_ref(cm_id);
	i40iw_rem_ref_cm_node(event->cm_node);
पूर्ण

/**
 * i40iw_process_options
 * @cm_node: connection's node
 * @optionsloc: poपूर्णांक to start of options
 * @optionsize: size of all options
 * @syn_packet: flag अगर syn packet
 */
अटल पूर्णांक i40iw_process_options(काष्ठा i40iw_cm_node *cm_node,
				 u8 *optionsloc,
				 u32 optionsize,
				 u32 syn_packet)
अणु
	u32 पंचांगp;
	u32 offset = 0;
	जोड़ all_known_options *all_options;
	अक्षर got_mss_option = 0;

	जबतक (offset < optionsize) अणु
		all_options = (जोड़ all_known_options *)(optionsloc + offset);
		चयन (all_options->as_base.optionnum) अणु
		हाल OPTION_NUMBER_END:
			offset = optionsize;
			अवरोध;
		हाल OPTION_NUMBER_NONE:
			offset += 1;
			जारी;
		हाल OPTION_NUMBER_MSS:
			i40iw_debug(cm_node->dev,
				    I40IW_DEBUG_CM,
				    "%s: MSS Length: %d Offset: %d Size: %d\n",
				    __func__,
				    all_options->as_mss.length,
				    offset,
				    optionsize);
			got_mss_option = 1;
			अगर (all_options->as_mss.length != 4)
				वापस -1;
			पंचांगp = ntohs(all_options->as_mss.mss);
			अगर (पंचांगp > 0 && पंचांगp < cm_node->tcp_cntxt.mss)
				cm_node->tcp_cntxt.mss = पंचांगp;
			अवरोध;
		हाल OPTION_NUMBER_WINDOW_SCALE:
			cm_node->tcp_cntxt.snd_wscale =
			    all_options->as_winकरोwscale.shअगरtcount;
			अवरोध;
		शेष:
			i40iw_debug(cm_node->dev,
				    I40IW_DEBUG_CM,
				    "TCP Option not understood: %x\n",
				    all_options->as_base.optionnum);
			अवरोध;
		पूर्ण
		offset += all_options->as_base.length;
	पूर्ण
	अगर (!got_mss_option && syn_packet)
		cm_node->tcp_cntxt.mss = I40IW_CM_DEFAULT_MSS;
	वापस 0;
पूर्ण

/**
 * i40iw_handle_tcp_options -
 * @cm_node: connection's node
 * @tcph: poपूर्णांकer tcp header
 * @optionsize: size of options rcvd
 * @passive: active or passive flag
 */
अटल पूर्णांक i40iw_handle_tcp_options(काष्ठा i40iw_cm_node *cm_node,
				    काष्ठा tcphdr *tcph,
				    पूर्णांक optionsize,
				    पूर्णांक passive)
अणु
	u8 *optionsloc = (u8 *)&tcph[1];

	अगर (optionsize) अणु
		अगर (i40iw_process_options(cm_node,
					  optionsloc,
					  optionsize,
					  (u32)tcph->syn)) अणु
			i40iw_debug(cm_node->dev,
				    I40IW_DEBUG_CM,
				    "%s: Node %p, Sending RESET\n",
				    __func__,
				    cm_node);
			अगर (passive)
				i40iw_passive_खोलो_err(cm_node, true);
			अन्यथा
				i40iw_active_खोलो_err(cm_node, true);
			वापस -1;
		पूर्ण
	पूर्ण

	cm_node->tcp_cntxt.snd_wnd = ntohs(tcph->winकरोw) <<
	    cm_node->tcp_cntxt.snd_wscale;

	अगर (cm_node->tcp_cntxt.snd_wnd > cm_node->tcp_cntxt.max_snd_wnd)
		cm_node->tcp_cntxt.max_snd_wnd = cm_node->tcp_cntxt.snd_wnd;
	वापस 0;
पूर्ण

/**
 * i40iw_build_mpa_v1 - build a MPA V1 frame
 * @cm_node: connection's node
 * @start_addr: MPA frame start address
 * @mpa_key: to करो पढ़ो0 or ग_लिखो0
 */
अटल व्योम i40iw_build_mpa_v1(काष्ठा i40iw_cm_node *cm_node,
			       व्योम *start_addr,
			       u8 mpa_key)
अणु
	काष्ठा ietf_mpa_v1 *mpa_frame = (काष्ठा ietf_mpa_v1 *)start_addr;

	चयन (mpa_key) अणु
	हाल MPA_KEY_REQUEST:
		स_नकल(mpa_frame->key, IEFT_MPA_KEY_REQ, IETF_MPA_KEY_SIZE);
		अवरोध;
	हाल MPA_KEY_REPLY:
		स_नकल(mpa_frame->key, IEFT_MPA_KEY_REP, IETF_MPA_KEY_SIZE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mpa_frame->flags = IETF_MPA_FLAGS_CRC;
	mpa_frame->rev = cm_node->mpa_frame_rev;
	mpa_frame->priv_data_len = htons(cm_node->pdata.size);
पूर्ण

/**
 * i40iw_build_mpa_v2 - build a MPA V2 frame
 * @cm_node: connection's node
 * @start_addr: buffer start address
 * @mpa_key: to करो पढ़ो0 or ग_लिखो0
 */
अटल व्योम i40iw_build_mpa_v2(काष्ठा i40iw_cm_node *cm_node,
			       व्योम *start_addr,
			       u8 mpa_key)
अणु
	काष्ठा ietf_mpa_v2 *mpa_frame = (काष्ठा ietf_mpa_v2 *)start_addr;
	काष्ठा ietf_rtr_msg *rtr_msg = &mpa_frame->rtr_msg;
	u16 ctrl_ird, ctrl_ord;

	/* initialize the upper 5 bytes of the frame */
	i40iw_build_mpa_v1(cm_node, start_addr, mpa_key);
	mpa_frame->flags |= IETF_MPA_V2_FLAG;
	mpa_frame->priv_data_len += htons(IETF_RTR_MSG_SIZE);

	/* initialize RTR msg */
	अगर (cm_node->mpav2_ird_ord == IETF_NO_IRD_ORD) अणु
		ctrl_ird = IETF_NO_IRD_ORD;
		ctrl_ord = IETF_NO_IRD_ORD;
	पूर्ण अन्यथा अणु
		ctrl_ird = (cm_node->ird_size > IETF_NO_IRD_ORD) ?
			IETF_NO_IRD_ORD : cm_node->ird_size;
		ctrl_ord = (cm_node->ord_size > IETF_NO_IRD_ORD) ?
			IETF_NO_IRD_ORD : cm_node->ord_size;
	पूर्ण

	ctrl_ird |= IETF_PEER_TO_PEER;

	चयन (mpa_key) अणु
	हाल MPA_KEY_REQUEST:
		ctrl_ord |= IETF_RDMA0_WRITE;
		ctrl_ord |= IETF_RDMA0_READ;
		अवरोध;
	हाल MPA_KEY_REPLY:
		चयन (cm_node->send_rdma0_op) अणु
		हाल SEND_RDMA_WRITE_ZERO:
			ctrl_ord |= IETF_RDMA0_WRITE;
			अवरोध;
		हाल SEND_RDMA_READ_ZERO:
			ctrl_ord |= IETF_RDMA0_READ;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtr_msg->ctrl_ird = htons(ctrl_ird);
	rtr_msg->ctrl_ord = htons(ctrl_ord);
पूर्ण

/**
 * i40iw_cm_build_mpa_frame - build mpa frame क्रम mpa version 1 or version 2
 * @cm_node: connection's node
 * @mpa: mpa: data buffer
 * @mpa_key: to करो पढ़ो0 or ग_लिखो0
 */
अटल पूर्णांक i40iw_cm_build_mpa_frame(काष्ठा i40iw_cm_node *cm_node,
				    काष्ठा i40iw_kmem_info *mpa,
				    u8 mpa_key)
अणु
	पूर्णांक hdr_len = 0;

	चयन (cm_node->mpa_frame_rev) अणु
	हाल IETF_MPA_V1:
		hdr_len = माप(काष्ठा ietf_mpa_v1);
		i40iw_build_mpa_v1(cm_node, mpa->addr, mpa_key);
		अवरोध;
	हाल IETF_MPA_V2:
		hdr_len = माप(काष्ठा ietf_mpa_v2);
		i40iw_build_mpa_v2(cm_node, mpa->addr, mpa_key);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस hdr_len;
पूर्ण

/**
 * i40iw_send_mpa_request - active node send mpa request to passive node
 * @cm_node: connection's node
 */
अटल पूर्णांक i40iw_send_mpa_request(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;

	अगर (!cm_node) अणु
		i40iw_pr_err("cm_node == NULL\n");
		वापस -1;
	पूर्ण

	cm_node->mpa_hdr.addr = &cm_node->mpa_frame;
	cm_node->mpa_hdr.size = i40iw_cm_build_mpa_frame(cm_node,
							 &cm_node->mpa_hdr,
							 MPA_KEY_REQUEST);
	अगर (!cm_node->mpa_hdr.size) अणु
		i40iw_pr_err("mpa size = %d\n", cm_node->mpa_hdr.size);
		वापस -1;
	पूर्ण

	sqbuf = i40iw_क्रमm_cm_frame(cm_node,
				    शून्य,
				    &cm_node->mpa_hdr,
				    &cm_node->pdata,
				    SET_ACK);
	अगर (!sqbuf) अणु
		i40iw_pr_err("sq_buf == NULL\n");
		वापस -1;
	पूर्ण
	वापस i40iw_schedule_cm_समयr(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 1, 0);
पूर्ण

/**
 * i40iw_send_mpa_reject -
 * @cm_node: connection's node
 * @pdata: reject data क्रम connection
 * @plen: length of reject data
 */
अटल पूर्णांक i40iw_send_mpa_reject(काष्ठा i40iw_cm_node *cm_node,
				 स्थिर व्योम *pdata,
				 u8 plen)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;
	काष्ठा i40iw_kmem_info priv_info;

	cm_node->mpa_hdr.addr = &cm_node->mpa_frame;
	cm_node->mpa_hdr.size = i40iw_cm_build_mpa_frame(cm_node,
							 &cm_node->mpa_hdr,
							 MPA_KEY_REPLY);

	cm_node->mpa_frame.flags |= IETF_MPA_FLAGS_REJECT;
	priv_info.addr = (व्योम *)pdata;
	priv_info.size = plen;

	sqbuf = i40iw_क्रमm_cm_frame(cm_node,
				    शून्य,
				    &cm_node->mpa_hdr,
				    &priv_info,
				    SET_ACK | SET_FIN);
	अगर (!sqbuf) अणु
		i40iw_pr_err("no sqbuf\n");
		वापस -ENOMEM;
	पूर्ण
	cm_node->state = I40IW_CM_STATE_FIN_WAIT1;
	वापस i40iw_schedule_cm_समयr(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 1, 0);
पूर्ण

/**
 * i40iw_parse_mpa - process an IETF MPA frame
 * @cm_node: connection's node
 * @buffer: Data poपूर्णांकer
 * @type: to वापस accept or reject
 * @len: Len of mpa buffer
 */
अटल पूर्णांक i40iw_parse_mpa(काष्ठा i40iw_cm_node *cm_node, u8 *buffer, u32 *type, u32 len)
अणु
	काष्ठा ietf_mpa_v1 *mpa_frame;
	काष्ठा ietf_mpa_v2 *mpa_v2_frame;
	काष्ठा ietf_rtr_msg *rtr_msg;
	पूर्णांक mpa_hdr_len;
	पूर्णांक priv_data_len;

	*type = I40IW_MPA_REQUEST_ACCEPT;

	अगर (len < माप(काष्ठा ietf_mpa_v1)) अणु
		i40iw_pr_err("ietf buffer small (%x)\n", len);
		वापस -1;
	पूर्ण

	mpa_frame = (काष्ठा ietf_mpa_v1 *)buffer;
	mpa_hdr_len = माप(काष्ठा ietf_mpa_v1);
	priv_data_len = ntohs(mpa_frame->priv_data_len);

	अगर (priv_data_len > IETF_MAX_PRIV_DATA_LEN) अणु
		i40iw_pr_err("large pri_data %d\n", priv_data_len);
		वापस -1;
	पूर्ण
	अगर (mpa_frame->rev != IETF_MPA_V1 && mpa_frame->rev != IETF_MPA_V2) अणु
		i40iw_pr_err("unsupported mpa rev = %d\n", mpa_frame->rev);
		वापस -1;
	पूर्ण
	अगर (mpa_frame->rev > cm_node->mpa_frame_rev) अणु
		i40iw_pr_err("rev %d\n", mpa_frame->rev);
		वापस -1;
	पूर्ण
	cm_node->mpa_frame_rev = mpa_frame->rev;

	अगर (cm_node->state != I40IW_CM_STATE_MPAREQ_SENT) अणु
		अगर (स_भेद(mpa_frame->key, IEFT_MPA_KEY_REQ, IETF_MPA_KEY_SIZE)) अणु
			i40iw_pr_err("Unexpected MPA Key received\n");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (स_भेद(mpa_frame->key, IEFT_MPA_KEY_REP, IETF_MPA_KEY_SIZE)) अणु
			i40iw_pr_err("Unexpected MPA Key received\n");
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (priv_data_len + mpa_hdr_len > len) अणु
		i40iw_pr_err("ietf buffer len(%x + %x != %x)\n",
			     priv_data_len, mpa_hdr_len, len);
		वापस -1;
	पूर्ण
	अगर (len > MAX_CM_BUFFER) अणु
		i40iw_pr_err("ietf buffer large len = %d\n", len);
		वापस -1;
	पूर्ण

	चयन (mpa_frame->rev) अणु
	हाल IETF_MPA_V2:अणु
			u16 ird_size;
			u16 ord_size;
			u16 ctrl_ord;
			u16 ctrl_ird;

			mpa_v2_frame = (काष्ठा ietf_mpa_v2 *)buffer;
			mpa_hdr_len += IETF_RTR_MSG_SIZE;
			rtr_msg = &mpa_v2_frame->rtr_msg;

			/* parse rtr message */
			ctrl_ord = ntohs(rtr_msg->ctrl_ord);
			ctrl_ird = ntohs(rtr_msg->ctrl_ird);
			ird_size = ctrl_ird & IETF_NO_IRD_ORD;
			ord_size = ctrl_ord & IETF_NO_IRD_ORD;

			अगर (!(ctrl_ird & IETF_PEER_TO_PEER))
				वापस -1;

			अगर (ird_size == IETF_NO_IRD_ORD || ord_size == IETF_NO_IRD_ORD) अणु
				cm_node->mpav2_ird_ord = IETF_NO_IRD_ORD;
				जाओ negotiate_करोne;
			पूर्ण

			अगर (cm_node->state != I40IW_CM_STATE_MPAREQ_SENT) अणु
				/* responder */
				अगर (!ord_size && (ctrl_ord & IETF_RDMA0_READ))
					cm_node->ird_size = 1;
				अगर (cm_node->ord_size > ird_size)
					cm_node->ord_size = ird_size;
			पूर्ण अन्यथा अणु
				/* initiator */
				अगर (!ird_size && (ctrl_ord & IETF_RDMA0_READ))
					वापस -1;
				अगर (cm_node->ord_size > ird_size)
					cm_node->ord_size = ird_size;

				अगर (cm_node->ird_size < ord_size)
					/* no resources available */
					वापस -1;
			पूर्ण

negotiate_करोne:
			अगर (ctrl_ord & IETF_RDMA0_READ)
				cm_node->send_rdma0_op = SEND_RDMA_READ_ZERO;
			अन्यथा अगर (ctrl_ord & IETF_RDMA0_WRITE)
				cm_node->send_rdma0_op = SEND_RDMA_WRITE_ZERO;
			अन्यथा	/* Not supported RDMA0 operation */
				वापस -1;
			i40iw_debug(cm_node->dev, I40IW_DEBUG_CM,
				    "MPAV2: Negotiated ORD: %d, IRD: %d\n",
				    cm_node->ord_size, cm_node->ird_size);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IETF_MPA_V1:
	शेष:
		अवरोध;
	पूर्ण

	स_नकल(cm_node->pdata_buf, buffer + mpa_hdr_len, priv_data_len);
	cm_node->pdata.size = priv_data_len;

	अगर (mpa_frame->flags & IETF_MPA_FLAGS_REJECT)
		*type = I40IW_MPA_REQUEST_REJECT;

	अगर (mpa_frame->flags & IETF_MPA_FLAGS_MARKERS)
		cm_node->snd_mark_en = true;

	वापस 0;
पूर्ण

/**
 * i40iw_schedule_cm_समयr
 * @cm_node: connection's node
 * @sqbuf: buffer to send
 * @type: अगर it is send or बंद
 * @send_retrans: अगर rexmits to be करोne
 * @बंद_when_complete: is cm_node to be हटाओd
 *
 * note - cm_node needs to be रक्षित beक्रमe calling this. Enहाल in:
 *		i40iw_rem_ref_cm_node(cm_core, cm_node);
 *		i40iw_schedule_cm_समयr(...)
 *		atomic_inc(&cm_node->ref_count);
 */
पूर्णांक i40iw_schedule_cm_समयr(काष्ठा i40iw_cm_node *cm_node,
			    काष्ठा i40iw_puda_buf *sqbuf,
			    क्रमागत i40iw_समयr_type type,
			    पूर्णांक send_retrans,
			    पूर्णांक बंद_when_complete)
अणु
	काष्ठा i40iw_sc_vsi *vsi = &cm_node->iwdev->vsi;
	काष्ठा i40iw_cm_core *cm_core = cm_node->cm_core;
	काष्ठा i40iw_समयr_entry *new_send;
	पूर्णांक ret = 0;
	u32 was_समयr_set;
	अचिन्हित दीर्घ flags;

	new_send = kzalloc(माप(*new_send), GFP_ATOMIC);
	अगर (!new_send) अणु
		अगर (type != I40IW_TIMER_TYPE_CLOSE)
			i40iw_मुक्त_sqbuf(vsi, (व्योम *)sqbuf);
		वापस -ENOMEM;
	पूर्ण
	new_send->retrycount = I40IW_DEFAULT_RETRYS;
	new_send->retranscount = I40IW_DEFAULT_RETRANS;
	new_send->sqbuf = sqbuf;
	new_send->समयtosend = jअगरfies;
	new_send->type = type;
	new_send->send_retrans = send_retrans;
	new_send->बंद_when_complete = बंद_when_complete;

	अगर (type == I40IW_TIMER_TYPE_CLOSE) अणु
		new_send->समयtosend += (HZ / 10);
		अगर (cm_node->बंद_entry) अणु
			kमुक्त(new_send);
			i40iw_pr_err("already close entry\n");
			वापस -EINVAL;
		पूर्ण
		cm_node->बंद_entry = new_send;
	पूर्ण

	अगर (type == I40IW_TIMER_TYPE_SEND) अणु
		spin_lock_irqsave(&cm_node->retrans_list_lock, flags);
		cm_node->send_entry = new_send;
		atomic_inc(&cm_node->ref_count);
		spin_unlock_irqrestore(&cm_node->retrans_list_lock, flags);
		new_send->समयtosend = jअगरfies + I40IW_RETRY_TIMEOUT;

		atomic_inc(&sqbuf->refcount);
		i40iw_puda_send_buf(vsi->ilq, sqbuf);
		अगर (!send_retrans) अणु
			i40iw_cleanup_retrans_entry(cm_node);
			अगर (बंद_when_complete)
				i40iw_rem_ref_cm_node(cm_node);
			वापस ret;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	was_समयr_set = समयr_pending(&cm_core->tcp_समयr);

	अगर (!was_समयr_set) अणु
		cm_core->tcp_समयr.expires = new_send->समयtosend;
		add_समयr(&cm_core->tcp_समयr);
	पूर्ण
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	वापस ret;
पूर्ण

/**
 * i40iw_retrans_expired - Could not rexmit the packet
 * @cm_node: connection's node
 */
अटल व्योम i40iw_retrans_expired(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा iw_cm_id *cm_id = cm_node->cm_id;
	क्रमागत i40iw_cm_node_state state = cm_node->state;

	cm_node->state = I40IW_CM_STATE_CLOSED;
	चयन (state) अणु
	हाल I40IW_CM_STATE_SYN_RCVD:
	हाल I40IW_CM_STATE_CLOSING:
		i40iw_rem_ref_cm_node(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_FIN_WAIT1:
	हाल I40IW_CM_STATE_LAST_ACK:
		अगर (cm_node->cm_id)
			cm_id->rem_ref(cm_id);
		i40iw_send_reset(cm_node);
		अवरोध;
	शेष:
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		i40iw_create_event(cm_node, I40IW_CM_EVENT_ABORTED);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_handle_बंद_entry - क्रम handling retry/समयouts
 * @cm_node: connection's node
 * @rem_node: flag क्रम हटाओ cm_node
 */
अटल व्योम i40iw_handle_बंद_entry(काष्ठा i40iw_cm_node *cm_node, u32 rem_node)
अणु
	काष्ठा i40iw_समयr_entry *बंद_entry = cm_node->बंद_entry;
	काष्ठा iw_cm_id *cm_id = cm_node->cm_id;
	काष्ठा i40iw_qp *iwqp;
	अचिन्हित दीर्घ flags;

	अगर (!बंद_entry)
		वापस;
	iwqp = (काष्ठा i40iw_qp *)बंद_entry->sqbuf;
	अगर (iwqp) अणु
		spin_lock_irqsave(&iwqp->lock, flags);
		अगर (iwqp->cm_id) अणु
			iwqp->hw_tcp_state = I40IW_TCP_STATE_CLOSED;
			iwqp->hw_iwarp_state = I40IW_QP_STATE_ERROR;
			iwqp->last_aeq = I40IW_AE_RESET_SENT;
			iwqp->ibqp_state = IB_QPS_ERR;
			spin_unlock_irqrestore(&iwqp->lock, flags);
			i40iw_cm_disconn(iwqp);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&iwqp->lock, flags);
		पूर्ण
	पूर्ण अन्यथा अगर (rem_node) अणु
		/* TIME_WAIT state */
		i40iw_rem_ref_cm_node(cm_node);
	पूर्ण
	अगर (cm_id)
		cm_id->rem_ref(cm_id);
	kमुक्त(बंद_entry);
	cm_node->बंद_entry = शून्य;
पूर्ण

/**
 * i40iw_build_समयr_list - Add cm_nodes to समयr list
 * @समयr_list: ptr to समयr list
 * @hte: ptr to accelerated or non-accelerated list
 */
अटल व्योम i40iw_build_समयr_list(काष्ठा list_head *समयr_list,
				   काष्ठा list_head *hte)
अणु
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा list_head *list_core_temp, *list_node;

	list_क्रम_each_safe(list_node, list_core_temp, hte) अणु
		cm_node = container_of(list_node, काष्ठा i40iw_cm_node, list);
		अगर (cm_node->बंद_entry || cm_node->send_entry) अणु
			atomic_inc(&cm_node->ref_count);
			list_add(&cm_node->समयr_entry, समयr_list);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40iw_cm_समयr_tick - प्रणाली's समयr expired callback
 * @t: Timer instance to fetch the cm_core poपूर्णांकer from
 */
अटल व्योम i40iw_cm_समयr_tick(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ nextसमयout = jअगरfies + I40IW_LONG_TIME;
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा i40iw_समयr_entry *send_entry, *बंद_entry;
	काष्ठा list_head *list_core_temp;
	काष्ठा i40iw_sc_vsi *vsi;
	काष्ठा list_head *list_node;
	काष्ठा i40iw_cm_core *cm_core = from_समयr(cm_core, t, tcp_समयr);
	u32 समय_रखोr = 0;
	अचिन्हित दीर्घ समयtosend;
	अचिन्हित दीर्घ flags;

	काष्ठा list_head समयr_list;

	INIT_LIST_HEAD(&समयr_list);

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	i40iw_build_समयr_list(&समयr_list, &cm_core->non_accelerated_list);
	i40iw_build_समयr_list(&समयr_list, &cm_core->accelerated_list);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	list_क्रम_each_safe(list_node, list_core_temp, &समयr_list) अणु
		cm_node = container_of(list_node,
				       काष्ठा i40iw_cm_node,
				       समयr_entry);
		बंद_entry = cm_node->बंद_entry;

		अगर (बंद_entry) अणु
			अगर (समय_after(बंद_entry->समयtosend, jअगरfies)) अणु
				अगर (nextसमयout > बंद_entry->समयtosend ||
				    !समय_रखोr) अणु
					nextसमयout = बंद_entry->समयtosend;
					समय_रखोr = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				i40iw_handle_बंद_entry(cm_node, 1);
			पूर्ण
		पूर्ण

		spin_lock_irqsave(&cm_node->retrans_list_lock, flags);

		send_entry = cm_node->send_entry;
		अगर (!send_entry)
			जाओ करोne;
		अगर (समय_after(send_entry->समयtosend, jअगरfies)) अणु
			अगर (cm_node->state != I40IW_CM_STATE_OFFLOADED) अणु
				अगर ((nextसमयout > send_entry->समयtosend) ||
				    !समय_रखोr) अणु
					nextसमयout = send_entry->समयtosend;
					समय_रखोr = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				i40iw_मुक्त_retrans_entry(cm_node);
			पूर्ण
			जाओ करोne;
		पूर्ण

		अगर ((cm_node->state == I40IW_CM_STATE_OFFLOADED) ||
		    (cm_node->state == I40IW_CM_STATE_CLOSED)) अणु
			i40iw_मुक्त_retrans_entry(cm_node);
			जाओ करोne;
		पूर्ण

		अगर (!send_entry->retranscount || !send_entry->retrycount) अणु
			i40iw_मुक्त_retrans_entry(cm_node);

			spin_unlock_irqrestore(&cm_node->retrans_list_lock, flags);
			i40iw_retrans_expired(cm_node);
			cm_node->state = I40IW_CM_STATE_CLOSED;
			spin_lock_irqsave(&cm_node->retrans_list_lock, flags);
			जाओ करोne;
		पूर्ण
		spin_unlock_irqrestore(&cm_node->retrans_list_lock, flags);

		vsi = &cm_node->iwdev->vsi;

		अगर (!cm_node->ack_rcvd) अणु
			atomic_inc(&send_entry->sqbuf->refcount);
			i40iw_puda_send_buf(vsi->ilq, send_entry->sqbuf);
			cm_node->cm_core->stats_pkt_retrans++;
		पूर्ण
		spin_lock_irqsave(&cm_node->retrans_list_lock, flags);
		अगर (send_entry->send_retrans) अणु
			send_entry->retranscount--;
			समयtosend = (I40IW_RETRY_TIMEOUT <<
				      (I40IW_DEFAULT_RETRANS -
				       send_entry->retranscount));

			send_entry->समयtosend = jअगरfies +
			    min(समयtosend, I40IW_MAX_TIMEOUT);
			अगर (nextसमयout > send_entry->समयtosend || !समय_रखोr) अणु
				nextसमयout = send_entry->समयtosend;
				समय_रखोr = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक बंद_when_complete;

			बंद_when_complete = send_entry->बंद_when_complete;
			i40iw_debug(cm_node->dev,
				    I40IW_DEBUG_CM,
				    "cm_node=%p state=%d\n",
				    cm_node,
				    cm_node->state);
			i40iw_मुक्त_retrans_entry(cm_node);
			अगर (बंद_when_complete)
				i40iw_rem_ref_cm_node(cm_node);
		पूर्ण
करोne:
		spin_unlock_irqrestore(&cm_node->retrans_list_lock, flags);
		i40iw_rem_ref_cm_node(cm_node);
	पूर्ण

	अगर (समय_रखोr) अणु
		spin_lock_irqsave(&cm_core->ht_lock, flags);
		अगर (!समयr_pending(&cm_core->tcp_समयr)) अणु
			cm_core->tcp_समयr.expires = nextसमयout;
			add_समयr(&cm_core->tcp_समयr);
		पूर्ण
		spin_unlock_irqrestore(&cm_core->ht_lock, flags);
	पूर्ण
पूर्ण

/**
 * i40iw_send_syn - send SYN packet
 * @cm_node: connection's node
 * @sendack: flag to set ACK bit or not
 */
पूर्णांक i40iw_send_syn(काष्ठा i40iw_cm_node *cm_node, u32 sendack)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;
	पूर्णांक flags = SET_SYN;
	अक्षर optionsbuffer[माप(काष्ठा option_mss) +
			   माप(काष्ठा option_winकरोwscale) +
			   माप(काष्ठा option_base) + TCP_OPTIONS_PADDING];
	काष्ठा i40iw_kmem_info opts;

	पूर्णांक optionssize = 0;
	/* Sending MSS option */
	जोड़ all_known_options *options;

	opts.addr = optionsbuffer;
	अगर (!cm_node) अणु
		i40iw_pr_err("no cm_node\n");
		वापस -EINVAL;
	पूर्ण

	options = (जोड़ all_known_options *)&optionsbuffer[optionssize];
	options->as_mss.optionnum = OPTION_NUMBER_MSS;
	options->as_mss.length = माप(काष्ठा option_mss);
	options->as_mss.mss = htons(cm_node->tcp_cntxt.mss);
	optionssize += माप(काष्ठा option_mss);

	options = (जोड़ all_known_options *)&optionsbuffer[optionssize];
	options->as_winकरोwscale.optionnum = OPTION_NUMBER_WINDOW_SCALE;
	options->as_winकरोwscale.length = माप(काष्ठा option_winकरोwscale);
	options->as_winकरोwscale.shअगरtcount = cm_node->tcp_cntxt.rcv_wscale;
	optionssize += माप(काष्ठा option_winकरोwscale);
	options = (जोड़ all_known_options *)&optionsbuffer[optionssize];
	options->as_end = OPTION_NUMBER_END;
	optionssize += 1;

	अगर (sendack)
		flags |= SET_ACK;

	opts.size = optionssize;

	sqbuf = i40iw_क्रमm_cm_frame(cm_node, &opts, शून्य, शून्य, flags);
	अगर (!sqbuf) अणु
		i40iw_pr_err("no sqbuf\n");
		वापस -1;
	पूर्ण
	वापस i40iw_schedule_cm_समयr(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 1, 0);
पूर्ण

/**
 * i40iw_send_ack - Send ACK packet
 * @cm_node: connection's node
 */
अटल व्योम i40iw_send_ack(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;
	काष्ठा i40iw_sc_vsi *vsi = &cm_node->iwdev->vsi;

	sqbuf = i40iw_क्रमm_cm_frame(cm_node, शून्य, शून्य, शून्य, SET_ACK);
	अगर (sqbuf)
		i40iw_puda_send_buf(vsi->ilq, sqbuf);
	अन्यथा
		i40iw_pr_err("no sqbuf\n");
पूर्ण

/**
 * i40iw_send_fin - Send FIN pkt
 * @cm_node: connection's node
 */
अटल पूर्णांक i40iw_send_fin(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_puda_buf *sqbuf;

	sqbuf = i40iw_क्रमm_cm_frame(cm_node, शून्य, शून्य, शून्य, SET_ACK | SET_FIN);
	अगर (!sqbuf) अणु
		i40iw_pr_err("no sqbuf\n");
		वापस -1;
	पूर्ण
	वापस i40iw_schedule_cm_समयr(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 1, 0);
पूर्ण

/**
 * i40iw_find_node - find a cm node that matches the reference cm node
 * @cm_core: cm's core
 * @rem_port: remote tcp port num
 * @rem_addr: remote ip addr
 * @loc_port: local tcp port num
 * @loc_addr: loc ip addr
 * @add_refcnt: flag to increment refcount of cm_node
 * @accelerated_list: flag क्रम accelerated vs non-accelerated list to search
 */
काष्ठा i40iw_cm_node *i40iw_find_node(काष्ठा i40iw_cm_core *cm_core,
				      u16 rem_port,
				      u32 *rem_addr,
				      u16 loc_port,
				      u32 *loc_addr,
				      bool add_refcnt,
				      bool accelerated_list)
अणु
	काष्ठा list_head *hte;
	काष्ठा i40iw_cm_node *cm_node;
	अचिन्हित दीर्घ flags;

	hte = accelerated_list ?
	      &cm_core->accelerated_list : &cm_core->non_accelerated_list;

	/* walk list and find cm_node associated with this session ID */
	spin_lock_irqsave(&cm_core->ht_lock, flags);
	list_क्रम_each_entry(cm_node, hte, list) अणु
		अगर (!स_भेद(cm_node->loc_addr, loc_addr, माप(cm_node->loc_addr)) &&
		    (cm_node->loc_port == loc_port) &&
		    !स_भेद(cm_node->rem_addr, rem_addr, माप(cm_node->rem_addr)) &&
		    (cm_node->rem_port == rem_port)) अणु
			अगर (add_refcnt)
				atomic_inc(&cm_node->ref_count);
			spin_unlock_irqrestore(&cm_core->ht_lock, flags);
			वापस cm_node;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	/* no owner node */
	वापस शून्य;
पूर्ण

/**
 * i40iw_find_listener - find a cm node listening on this addr-port pair
 * @cm_core: cm's core
 * @dst_port: listener tcp port num
 * @dst_addr: listener ip addr
 * @vlan_id: vlan id क्रम the given address
 * @listener_state: state to match with listen node's
 */
अटल काष्ठा i40iw_cm_listener *i40iw_find_listener(
						     काष्ठा i40iw_cm_core *cm_core,
						     u32 *dst_addr,
						     u16 dst_port,
						     u16 vlan_id,
						     क्रमागत i40iw_cm_listener_state
						     listener_state)
अणु
	काष्ठा i40iw_cm_listener *listen_node;
	अटल स्थिर u32 ip_zero[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 listen_addr[4];
	u16 listen_port;
	अचिन्हित दीर्घ flags;

	/* walk list and find cm_node associated with this session ID */
	spin_lock_irqsave(&cm_core->listen_list_lock, flags);
	list_क्रम_each_entry(listen_node, &cm_core->listen_nodes, list) अणु
		स_नकल(listen_addr, listen_node->loc_addr, माप(listen_addr));
		listen_port = listen_node->loc_port;
		/* compare node pair, वापस node handle अगर a match */
		अगर ((!स_भेद(listen_addr, dst_addr, माप(listen_addr)) ||
		     !स_भेद(listen_addr, ip_zero, माप(listen_addr))) &&
		     (listen_port == dst_port) &&
		     (listener_state & listen_node->listener_state)) अणु
			atomic_inc(&listen_node->ref_count);
			spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);
			वापस listen_node;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);
	वापस शून्य;
पूर्ण

/**
 * i40iw_add_hte_node - add a cm node to the hash table
 * @cm_core: cm's core
 * @cm_node: connection's node
 */
अटल व्योम i40iw_add_hte_node(काष्ठा i40iw_cm_core *cm_core,
			       काष्ठा i40iw_cm_node *cm_node)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!cm_node || !cm_core) अणु
		i40iw_pr_err("cm_node or cm_core == NULL\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	list_add_tail(&cm_node->list, &cm_core->non_accelerated_list);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);
पूर्ण

/**
 * i40iw_find_port - find port that matches reference port
 * @hte: ptr to accelerated or non-accelerated list
 * @port: port number to locate
 */
अटल bool i40iw_find_port(काष्ठा list_head *hte, u16 port)
अणु
	काष्ठा i40iw_cm_node *cm_node;

	list_क्रम_each_entry(cm_node, hte, list) अणु
		अगर (cm_node->loc_port == port)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * i40iw_port_in_use - determine अगर port is in use
 * @cm_core: cm's core
 * @port: port number
 */
bool i40iw_port_in_use(काष्ठा i40iw_cm_core *cm_core, u16 port)
अणु
	काष्ठा i40iw_cm_listener *listen_node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	अगर (i40iw_find_port(&cm_core->accelerated_list, port) ||
	    i40iw_find_port(&cm_core->non_accelerated_list, port)) अणु
		spin_unlock_irqrestore(&cm_core->ht_lock, flags);
		वापस true;
	पूर्ण
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	spin_lock_irqsave(&cm_core->listen_list_lock, flags);
	list_क्रम_each_entry(listen_node, &cm_core->listen_nodes, list) अणु
		अगर (listen_node->loc_port == port) अणु
			spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);

	वापस false;
पूर्ण

/**
 * i40iw_del_multiple_qhash - Remove qhash and child listens
 * @iwdev: iWarp device
 * @cm_info: CM info क्रम parent listen node
 * @cm_parent_listen_node: The parent listen node
 */
अटल क्रमागत i40iw_status_code i40iw_del_multiple_qhash(
						       काष्ठा i40iw_device *iwdev,
						       काष्ठा i40iw_cm_info *cm_info,
						       काष्ठा i40iw_cm_listener *cm_parent_listen_node)
अणु
	काष्ठा i40iw_cm_listener *child_listen_node;
	क्रमागत i40iw_status_code ret = I40IW_ERR_CONFIG;
	काष्ठा list_head *pos, *tpos;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iwdev->cm_core.listen_list_lock, flags);
	list_क्रम_each_safe(pos, tpos, &cm_parent_listen_node->child_listen_list) अणु
		child_listen_node = list_entry(pos, काष्ठा i40iw_cm_listener, child_listen_list);
		अगर (child_listen_node->ipv4)
			i40iw_debug(&iwdev->sc_dev,
				    I40IW_DEBUG_CM,
				    "removing child listen for IP=%pI4, port=%d, vlan=%d\n",
				    child_listen_node->loc_addr,
				    child_listen_node->loc_port,
				    child_listen_node->vlan_id);
		अन्यथा
			i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_CM,
				    "removing child listen for IP=%pI6, port=%d, vlan=%d\n",
				    child_listen_node->loc_addr,
				    child_listen_node->loc_port,
				    child_listen_node->vlan_id);
		list_del(pos);
		स_नकल(cm_info->loc_addr, child_listen_node->loc_addr,
		       माप(cm_info->loc_addr));
		cm_info->vlan_id = child_listen_node->vlan_id;
		अगर (child_listen_node->qhash_set) अणु
			ret = i40iw_manage_qhash(iwdev, cm_info,
						 I40IW_QHASH_TYPE_TCP_SYN,
						 I40IW_QHASH_MANAGE_TYPE_DELETE,
						 शून्य, false);
			child_listen_node->qhash_set = false;
		पूर्ण अन्यथा अणु
			ret = I40IW_SUCCESS;
		पूर्ण
		i40iw_debug(&iwdev->sc_dev,
			    I40IW_DEBUG_CM,
			    "freed pointer = %p\n",
			    child_listen_node);
		kमुक्त(child_listen_node);
		cm_parent_listen_node->cm_core->stats_listen_nodes_destroyed++;
	पूर्ण
	spin_unlock_irqrestore(&iwdev->cm_core.listen_list_lock, flags);

	वापस ret;
पूर्ण

/**
 * i40iw_netdev_vlan_ipv6 - Gets the netdev and vlan
 * @addr: local IPv6 address
 * @vlan_id: vlan id क्रम the given IPv6 address
 *
 * Returns the net_device of the IPv6 address and also sets the
 * vlan id क्रम that address.
 */
अटल काष्ठा net_device *i40iw_netdev_vlan_ipv6(u32 *addr, u16 *vlan_id)
अणु
	काष्ठा net_device *ip_dev = शून्य;
	काष्ठा in6_addr laddr6;

	अगर (!IS_ENABLED(CONFIG_IPV6))
		वापस शून्य;
	i40iw_copy_ip_htonl(laddr6.in6_u.u6_addr32, addr);
	अगर (vlan_id)
		*vlan_id = I40IW_NO_VLAN;
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, ip_dev) अणु
		अगर (ipv6_chk_addr(&init_net, &laddr6, ip_dev, 1)) अणु
			अगर (vlan_id)
				*vlan_id = rdma_vlan_dev_vlan_id(ip_dev);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ip_dev;
पूर्ण

/**
 * i40iw_get_vlan_ipv4 - Returns the vlan_id क्रम IPv4 address
 * @addr: local IPv4 address
 */
अटल u16 i40iw_get_vlan_ipv4(u32 *addr)
अणु
	काष्ठा net_device *netdev;
	u16 vlan_id = I40IW_NO_VLAN;

	netdev = ip_dev_find(&init_net, htonl(addr[0]));
	अगर (netdev) अणु
		vlan_id = rdma_vlan_dev_vlan_id(netdev);
		dev_put(netdev);
	पूर्ण
	वापस vlan_id;
पूर्ण

/**
 * i40iw_add_mqh_6 - Adds multiple qhashes क्रम IPv6
 * @iwdev: iWarp device
 * @cm_info: CM info क्रम parent listen node
 * @cm_parent_listen_node: The parent listen node
 *
 * Adds a qhash and a child listen node क्रम every IPv6 address
 * on the adapter and adds the associated qhash filter
 */
अटल क्रमागत i40iw_status_code i40iw_add_mqh_6(काष्ठा i40iw_device *iwdev,
					      काष्ठा i40iw_cm_info *cm_info,
					      काष्ठा i40iw_cm_listener *cm_parent_listen_node)
अणु
	काष्ठा net_device *ip_dev;
	काष्ठा inet6_dev *idev;
	काष्ठा inet6_अगरaddr *अगरp, *पंचांगp;
	क्रमागत i40iw_status_code ret = 0;
	काष्ठा i40iw_cm_listener *child_listen_node;
	अचिन्हित दीर्घ flags;

	rtnl_lock();
	क्रम_each_netdev(&init_net, ip_dev) अणु
		अगर ((((rdma_vlan_dev_vlan_id(ip_dev) < I40IW_NO_VLAN) &&
		      (rdma_vlan_dev_real_dev(ip_dev) == iwdev->netdev)) ||
		     (ip_dev == iwdev->netdev)) && (ip_dev->flags & IFF_UP)) अणु
			idev = __in6_dev_get(ip_dev);
			अगर (!idev) अणु
				i40iw_pr_err("idev == NULL\n");
				अवरोध;
			पूर्ण
			list_क्रम_each_entry_safe(अगरp, पंचांगp, &idev->addr_list, अगर_list) अणु
				i40iw_debug(&iwdev->sc_dev,
					    I40IW_DEBUG_CM,
					    "IP=%pI6, vlan_id=%d, MAC=%pM\n",
					    &अगरp->addr,
					    rdma_vlan_dev_vlan_id(ip_dev),
					    ip_dev->dev_addr);
				child_listen_node =
					kzalloc(माप(*child_listen_node), GFP_ATOMIC);
				i40iw_debug(&iwdev->sc_dev,
					    I40IW_DEBUG_CM,
					    "Allocating child listener %p\n",
					    child_listen_node);
				अगर (!child_listen_node) अणु
					ret = I40IW_ERR_NO_MEMORY;
					जाओ निकास;
				पूर्ण
				cm_info->vlan_id = rdma_vlan_dev_vlan_id(ip_dev);
				cm_parent_listen_node->vlan_id = cm_info->vlan_id;

				स_नकल(child_listen_node, cm_parent_listen_node,
				       माप(*child_listen_node));

				i40iw_copy_ip_ntohl(child_listen_node->loc_addr,
						    अगरp->addr.in6_u.u6_addr32);
				स_नकल(cm_info->loc_addr, child_listen_node->loc_addr,
				       माप(cm_info->loc_addr));

				ret = i40iw_manage_qhash(iwdev, cm_info,
							 I40IW_QHASH_TYPE_TCP_SYN,
							 I40IW_QHASH_MANAGE_TYPE_ADD,
							 शून्य, true);
				अगर (!ret) अणु
					child_listen_node->qhash_set = true;
					spin_lock_irqsave(&iwdev->cm_core.listen_list_lock, flags);
					list_add(&child_listen_node->child_listen_list,
						 &cm_parent_listen_node->child_listen_list);
					spin_unlock_irqrestore(&iwdev->cm_core.listen_list_lock, flags);
					cm_parent_listen_node->cm_core->stats_listen_nodes_created++;
				पूर्ण अन्यथा अणु
					kमुक्त(child_listen_node);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
निकास:
	rtnl_unlock();
	वापस ret;
पूर्ण

/**
 * i40iw_add_mqh_4 - Adds multiple qhashes क्रम IPv4
 * @iwdev: iWarp device
 * @cm_info: CM info क्रम parent listen node
 * @cm_parent_listen_node: The parent listen node
 *
 * Adds a qhash and a child listen node क्रम every IPv4 address
 * on the adapter and adds the associated qhash filter
 */
अटल क्रमागत i40iw_status_code i40iw_add_mqh_4(
				काष्ठा i40iw_device *iwdev,
				काष्ठा i40iw_cm_info *cm_info,
				काष्ठा i40iw_cm_listener *cm_parent_listen_node)
अणु
	काष्ठा net_device *dev;
	काष्ठा in_device *idev;
	काष्ठा i40iw_cm_listener *child_listen_node;
	क्रमागत i40iw_status_code ret = 0;
	अचिन्हित दीर्घ flags;

	rtnl_lock();
	क्रम_each_netdev(&init_net, dev) अणु
		अगर ((((rdma_vlan_dev_vlan_id(dev) < I40IW_NO_VLAN) &&
		      (rdma_vlan_dev_real_dev(dev) == iwdev->netdev)) ||
		    (dev == iwdev->netdev)) && (dev->flags & IFF_UP)) अणु
			स्थिर काष्ठा in_अगरaddr *अगरa;

			idev = in_dev_get(dev);

			in_dev_क्रम_each_अगरa_rtnl(अगरa, idev) अणु
				i40iw_debug(&iwdev->sc_dev,
					    I40IW_DEBUG_CM,
					    "Allocating child CM Listener forIP=%pI4, vlan_id=%d, MAC=%pM\n",
					    &अगरa->अगरa_address,
					    rdma_vlan_dev_vlan_id(dev),
					    dev->dev_addr);
				child_listen_node = kzalloc(माप(*child_listen_node), GFP_KERNEL);
				cm_parent_listen_node->cm_core->stats_listen_nodes_created++;
				i40iw_debug(&iwdev->sc_dev,
					    I40IW_DEBUG_CM,
					    "Allocating child listener %p\n",
					    child_listen_node);
				अगर (!child_listen_node) अणु
					in_dev_put(idev);
					ret = I40IW_ERR_NO_MEMORY;
					जाओ निकास;
				पूर्ण
				cm_info->vlan_id = rdma_vlan_dev_vlan_id(dev);
				cm_parent_listen_node->vlan_id = cm_info->vlan_id;
				स_नकल(child_listen_node,
				       cm_parent_listen_node,
				       माप(*child_listen_node));

				child_listen_node->loc_addr[0] = ntohl(अगरa->अगरa_address);
				स_नकल(cm_info->loc_addr, child_listen_node->loc_addr,
				       माप(cm_info->loc_addr));

				ret = i40iw_manage_qhash(iwdev,
							 cm_info,
							 I40IW_QHASH_TYPE_TCP_SYN,
							 I40IW_QHASH_MANAGE_TYPE_ADD,
							 शून्य,
							 true);
				अगर (!ret) अणु
					child_listen_node->qhash_set = true;
					spin_lock_irqsave(&iwdev->cm_core.listen_list_lock, flags);
					list_add(&child_listen_node->child_listen_list,
						 &cm_parent_listen_node->child_listen_list);
					spin_unlock_irqrestore(&iwdev->cm_core.listen_list_lock, flags);
				पूर्ण अन्यथा अणु
					kमुक्त(child_listen_node);
					cm_parent_listen_node->cm_core->stats_listen_nodes_created--;
				पूर्ण
			पूर्ण

			in_dev_put(idev);
		पूर्ण
	पूर्ण
निकास:
	rtnl_unlock();
	वापस ret;
पूर्ण

/**
 * i40iw_dec_refcnt_listen - delete listener and associated cm nodes
 * @cm_core: cm's core
 * @listener: passive connection's listener
 * @मुक्त_hanging_nodes: to मुक्त associated cm_nodes
 * @apbvt_del: flag to delete the apbvt
 */
अटल पूर्णांक i40iw_dec_refcnt_listen(काष्ठा i40iw_cm_core *cm_core,
				   काष्ठा i40iw_cm_listener *listener,
				   पूर्णांक मुक्त_hanging_nodes, bool apbvt_del)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक err = 0;
	काष्ठा list_head *list_pos;
	काष्ठा list_head *list_temp;
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा list_head reset_list;
	काष्ठा i40iw_cm_info nfo;
	काष्ठा i40iw_cm_node *loopback;
	क्रमागत i40iw_cm_node_state old_state;
	अचिन्हित दीर्घ flags;

	/* मुक्त non-accelerated child nodes क्रम this listener */
	INIT_LIST_HEAD(&reset_list);
	अगर (मुक्त_hanging_nodes) अणु
		spin_lock_irqsave(&cm_core->ht_lock, flags);
		list_क्रम_each_safe(list_pos,
				   list_temp, &cm_core->non_accelerated_list) अणु
			cm_node = container_of(list_pos, काष्ठा i40iw_cm_node, list);
			अगर ((cm_node->listener == listener) &&
			    !cm_node->accelerated) अणु
				atomic_inc(&cm_node->ref_count);
				list_add(&cm_node->reset_entry, &reset_list);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&cm_core->ht_lock, flags);
	पूर्ण

	list_क्रम_each_safe(list_pos, list_temp, &reset_list) अणु
		cm_node = container_of(list_pos, काष्ठा i40iw_cm_node, reset_entry);
		loopback = cm_node->loopbackpartner;
		अगर (cm_node->state >= I40IW_CM_STATE_FIN_WAIT1) अणु
			i40iw_rem_ref_cm_node(cm_node);
		पूर्ण अन्यथा अणु
			अगर (!loopback) अणु
				i40iw_cleanup_retrans_entry(cm_node);
				err = i40iw_send_reset(cm_node);
				अगर (err) अणु
					cm_node->state = I40IW_CM_STATE_CLOSED;
					i40iw_pr_err("send reset\n");
				पूर्ण अन्यथा अणु
					old_state = cm_node->state;
					cm_node->state = I40IW_CM_STATE_LISTENER_DESTROYED;
					अगर (old_state != I40IW_CM_STATE_MPAREQ_RCVD)
						i40iw_rem_ref_cm_node(cm_node);
				पूर्ण
			पूर्ण अन्यथा अणु
				काष्ठा i40iw_cm_event event;

				event.cm_node = loopback;
				स_नकल(event.cm_info.rem_addr,
				       loopback->rem_addr, माप(event.cm_info.rem_addr));
				स_नकल(event.cm_info.loc_addr,
				       loopback->loc_addr, माप(event.cm_info.loc_addr));
				event.cm_info.rem_port = loopback->rem_port;
				event.cm_info.loc_port = loopback->loc_port;
				event.cm_info.cm_id = loopback->cm_id;
				event.cm_info.ipv4 = loopback->ipv4;
				atomic_inc(&loopback->ref_count);
				loopback->state = I40IW_CM_STATE_CLOSED;
				i40iw_event_connect_error(&event);
				cm_node->state = I40IW_CM_STATE_LISTENER_DESTROYED;
				i40iw_rem_ref_cm_node(cm_node);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!atomic_dec_वापस(&listener->ref_count)) अणु
		spin_lock_irqsave(&cm_core->listen_list_lock, flags);
		list_del(&listener->list);
		spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);

		अगर (listener->iwdev) अणु
			अगर (apbvt_del)
				i40iw_manage_apbvt(listener->iwdev,
						   listener->loc_port,
						   I40IW_MANAGE_APBVT_DEL);

			स_नकल(nfo.loc_addr, listener->loc_addr, माप(nfo.loc_addr));
			nfo.loc_port = listener->loc_port;
			nfo.ipv4 = listener->ipv4;
			nfo.vlan_id = listener->vlan_id;
			nfo.user_pri = listener->user_pri;

			अगर (!list_empty(&listener->child_listen_list)) अणु
				i40iw_del_multiple_qhash(listener->iwdev, &nfo, listener);
			पूर्ण अन्यथा अणु
				अगर (listener->qhash_set)
					i40iw_manage_qhash(listener->iwdev,
							   &nfo,
							   I40IW_QHASH_TYPE_TCP_SYN,
							   I40IW_QHASH_MANAGE_TYPE_DELETE,
							   शून्य,
							   false);
			पूर्ण
		पूर्ण

		cm_core->stats_listen_destroyed++;
		kमुक्त(listener);
		cm_core->stats_listen_nodes_destroyed++;
		listener = शून्य;
		ret = 0;
	पूर्ण

	अगर (listener) अणु
		अगर (atomic_पढ़ो(&listener->pend_accepts_cnt) > 0)
			i40iw_debug(cm_core->dev,
				    I40IW_DEBUG_CM,
				    "%s: listener (%p) pending accepts=%u\n",
				    __func__,
				    listener,
				    atomic_पढ़ो(&listener->pend_accepts_cnt));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40iw_cm_del_listen - delete a linstener
 * @cm_core: cm's core
  * @listener: passive connection's listener
 * @apbvt_del: flag to delete apbvt
 */
अटल पूर्णांक i40iw_cm_del_listen(काष्ठा i40iw_cm_core *cm_core,
			       काष्ठा i40iw_cm_listener *listener,
			       bool apbvt_del)
अणु
	listener->listener_state = I40IW_CM_LISTENER_PASSIVE_STATE;
	listener->cm_id = शून्य;	/* going to be destroyed pretty soon */
	वापस i40iw_dec_refcnt_listen(cm_core, listener, 1, apbvt_del);
पूर्ण

/**
 * i40iw_addr_resolve_neigh - resolve neighbor address
 * @iwdev: iwarp device काष्ठाure
 * @src_ip: local ip address
 * @dst_ip: remote ip address
 * @arpindex: अगर there is an arp entry
 */
अटल पूर्णांक i40iw_addr_resolve_neigh(काष्ठा i40iw_device *iwdev,
				    u32 src_ip,
				    u32 dst_ip,
				    पूर्णांक arpindex)
अणु
	काष्ठा rtable *rt;
	काष्ठा neighbour *neigh;
	पूर्णांक rc = arpindex;
	__be32 dst_ipaddr = htonl(dst_ip);
	__be32 src_ipaddr = htonl(src_ip);

	rt = ip_route_output(&init_net, dst_ipaddr, src_ipaddr, 0, 0);
	अगर (IS_ERR(rt)) अणु
		i40iw_pr_err("ip_route_output\n");
		वापस rc;
	पूर्ण

	neigh = dst_neigh_lookup(&rt->dst, &dst_ipaddr);

	rcu_पढ़ो_lock();
	अगर (neigh) अणु
		अगर (neigh->nud_state & NUD_VALID) अणु
			अगर (arpindex >= 0) अणु
				अगर (ether_addr_equal(iwdev->arp_table[arpindex].mac_addr,
						     neigh->ha))
					/* Mac address same as arp table */
					जाओ resolve_neigh_निकास;
				i40iw_manage_arp_cache(iwdev,
						       iwdev->arp_table[arpindex].mac_addr,
						       &dst_ip,
						       true,
						       I40IW_ARP_DELETE);
			पूर्ण

			i40iw_manage_arp_cache(iwdev, neigh->ha, &dst_ip, true, I40IW_ARP_ADD);
			rc = i40iw_arp_table(iwdev, &dst_ip, true, शून्य, I40IW_ARP_RESOLVE);
		पूर्ण अन्यथा अणु
			neigh_event_send(neigh, शून्य);
		पूर्ण
	पूर्ण
 resolve_neigh_निकास:

	rcu_पढ़ो_unlock();
	अगर (neigh)
		neigh_release(neigh);

	ip_rt_put(rt);
	वापस rc;
पूर्ण

/*
 * i40iw_get_dst_ipv6
 */
अटल काष्ठा dst_entry *i40iw_get_dst_ipv6(काष्ठा sockaddr_in6 *src_addr,
					    काष्ठा sockaddr_in6 *dst_addr)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.daddr = dst_addr->sin6_addr;
	fl6.saddr = src_addr->sin6_addr;
	अगर (ipv6_addr_type(&fl6.daddr) & IPV6_ADDR_LINKLOCAL)
		fl6.flowi6_oअगर = dst_addr->sin6_scope_id;

	dst = ip6_route_output(&init_net, शून्य, &fl6);
	वापस dst;
पूर्ण

/**
 * i40iw_addr_resolve_neigh_ipv6 - resolve neighbor ipv6 address
 * @iwdev: iwarp device काष्ठाure
 * @src: source ip address
 * @dest: remote ip address
 * @arpindex: अगर there is an arp entry
 */
अटल पूर्णांक i40iw_addr_resolve_neigh_ipv6(काष्ठा i40iw_device *iwdev,
					 u32 *src,
					 u32 *dest,
					 पूर्णांक arpindex)
अणु
	काष्ठा neighbour *neigh;
	पूर्णांक rc = arpindex;
	काष्ठा dst_entry *dst;
	काष्ठा sockaddr_in6 dst_addr;
	काष्ठा sockaddr_in6 src_addr;

	स_रखो(&dst_addr, 0, माप(dst_addr));
	dst_addr.sin6_family = AF_INET6;
	i40iw_copy_ip_htonl(dst_addr.sin6_addr.in6_u.u6_addr32, dest);
	स_रखो(&src_addr, 0, माप(src_addr));
	src_addr.sin6_family = AF_INET6;
	i40iw_copy_ip_htonl(src_addr.sin6_addr.in6_u.u6_addr32, src);
	dst = i40iw_get_dst_ipv6(&src_addr, &dst_addr);
	अगर (!dst || dst->error) अणु
		अगर (dst) अणु
			i40iw_pr_err("ip6_route_output returned dst->error = %d\n",
				     dst->error);
			dst_release(dst);
		पूर्ण
		वापस rc;
	पूर्ण

	neigh = dst_neigh_lookup(dst, dst_addr.sin6_addr.in6_u.u6_addr32);

	rcu_पढ़ो_lock();
	अगर (neigh) अणु
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_CM, "dst_neigh_lookup MAC=%pM\n", neigh->ha);
		अगर (neigh->nud_state & NUD_VALID) अणु
			अगर (arpindex >= 0) अणु
				अगर (ether_addr_equal
				    (iwdev->arp_table[arpindex].mac_addr,
				     neigh->ha)) अणु
					/* Mac address same as in arp table */
					जाओ resolve_neigh_निकास6;
				पूर्ण
				i40iw_manage_arp_cache(iwdev,
						       iwdev->arp_table[arpindex].mac_addr,
						       dest,
						       false,
						       I40IW_ARP_DELETE);
			पूर्ण
			i40iw_manage_arp_cache(iwdev,
					       neigh->ha,
					       dest,
					       false,
					       I40IW_ARP_ADD);
			rc = i40iw_arp_table(iwdev,
					     dest,
					     false,
					     शून्य,
					     I40IW_ARP_RESOLVE);
		पूर्ण अन्यथा अणु
			neigh_event_send(neigh, शून्य);
		पूर्ण
	पूर्ण

 resolve_neigh_निकास6:
	rcu_पढ़ो_unlock();
	अगर (neigh)
		neigh_release(neigh);
	dst_release(dst);
	वापस rc;
पूर्ण

/**
 * i40iw_ipv4_is_loopback - check अगर loopback
 * @loc_addr: local addr to compare
 * @rem_addr: remote address
 */
अटल bool i40iw_ipv4_is_loopback(u32 loc_addr, u32 rem_addr)
अणु
	वापस ipv4_is_loopback(htonl(rem_addr)) || (loc_addr == rem_addr);
पूर्ण

/**
 * i40iw_ipv6_is_loopback - check अगर loopback
 * @loc_addr: local addr to compare
 * @rem_addr: remote address
 */
अटल bool i40iw_ipv6_is_loopback(u32 *loc_addr, u32 *rem_addr)
अणु
	काष्ठा in6_addr raddr6;

	i40iw_copy_ip_htonl(raddr6.in6_u.u6_addr32, rem_addr);
	वापस !स_भेद(loc_addr, rem_addr, 16) || ipv6_addr_loopback(&raddr6);
पूर्ण

/**
 * i40iw_make_cm_node - create a new instance of a cm node
 * @cm_core: cm's core
 * @iwdev: iwarp device काष्ठाure
 * @cm_info: quad info क्रम connection
 * @listener: passive connection's listener
 */
अटल काष्ठा i40iw_cm_node *i40iw_make_cm_node(
				   काष्ठा i40iw_cm_core *cm_core,
				   काष्ठा i40iw_device *iwdev,
				   काष्ठा i40iw_cm_info *cm_info,
				   काष्ठा i40iw_cm_listener *listener)
अणु
	काष्ठा i40iw_cm_node *cm_node;
	पूर्णांक oldarpindex;
	पूर्णांक arpindex;
	काष्ठा net_device *netdev = iwdev->netdev;

	/* create an hte and cm_node क्रम this instance */
	cm_node = kzalloc(माप(*cm_node), GFP_ATOMIC);
	अगर (!cm_node)
		वापस शून्य;

	/* set our node specअगरic transport info */
	cm_node->ipv4 = cm_info->ipv4;
	cm_node->vlan_id = cm_info->vlan_id;
	अगर ((cm_node->vlan_id == I40IW_NO_VLAN) && iwdev->dcb)
		cm_node->vlan_id = 0;
	cm_node->tos = cm_info->tos;
	cm_node->user_pri = cm_info->user_pri;
	अगर (listener) अणु
		अगर (listener->tos != cm_info->tos)
			i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_DCB,
				    "application TOS[%d] and remote client TOS[%d] mismatch\n",
				     listener->tos, cm_info->tos);
		cm_node->tos = max(listener->tos, cm_info->tos);
		cm_node->user_pri = rt_tos2priority(cm_node->tos);
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_DCB, "listener: TOS:[%d] UP:[%d]\n",
			    cm_node->tos, cm_node->user_pri);
	पूर्ण
	स_नकल(cm_node->loc_addr, cm_info->loc_addr, माप(cm_node->loc_addr));
	स_नकल(cm_node->rem_addr, cm_info->rem_addr, माप(cm_node->rem_addr));
	cm_node->loc_port = cm_info->loc_port;
	cm_node->rem_port = cm_info->rem_port;

	cm_node->mpa_frame_rev = iwdev->mpa_version;
	cm_node->send_rdma0_op = SEND_RDMA_READ_ZERO;
	cm_node->ird_size = I40IW_MAX_IRD_SIZE;
	cm_node->ord_size = I40IW_MAX_ORD_SIZE;

	cm_node->listener = listener;
	cm_node->cm_id = cm_info->cm_id;
	ether_addr_copy(cm_node->loc_mac, netdev->dev_addr);
	spin_lock_init(&cm_node->retrans_list_lock);
	cm_node->ack_rcvd = false;

	atomic_set(&cm_node->ref_count, 1);
	/* associate our parent CM core */
	cm_node->cm_core = cm_core;
	cm_node->tcp_cntxt.loc_id = I40IW_CM_DEF_LOCAL_ID;
	cm_node->tcp_cntxt.rcv_wscale = I40IW_CM_DEFAULT_RCV_WND_SCALE;
	cm_node->tcp_cntxt.rcv_wnd =
			I40IW_CM_DEFAULT_RCV_WND_SCALED >> I40IW_CM_DEFAULT_RCV_WND_SCALE;
	अगर (cm_node->ipv4) अणु
		cm_node->tcp_cntxt.loc_seq_num = secure_tcp_seq(htonl(cm_node->loc_addr[0]),
							htonl(cm_node->rem_addr[0]),
							htons(cm_node->loc_port),
							htons(cm_node->rem_port));
		cm_node->tcp_cntxt.mss = iwdev->vsi.mtu - I40IW_MTU_TO_MSS_IPV4;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6)) अणु
		__be32 loc[4] = अणु
			htonl(cm_node->loc_addr[0]), htonl(cm_node->loc_addr[1]),
			htonl(cm_node->loc_addr[2]), htonl(cm_node->loc_addr[3])
		पूर्ण;
		__be32 rem[4] = अणु
			htonl(cm_node->rem_addr[0]), htonl(cm_node->rem_addr[1]),
			htonl(cm_node->rem_addr[2]), htonl(cm_node->rem_addr[3])
		पूर्ण;
		cm_node->tcp_cntxt.loc_seq_num = secure_tcpv6_seq(loc, rem,
							htons(cm_node->loc_port),
							htons(cm_node->rem_port));
		cm_node->tcp_cntxt.mss = iwdev->vsi.mtu - I40IW_MTU_TO_MSS_IPV6;
	पूर्ण

	cm_node->iwdev = iwdev;
	cm_node->dev = &iwdev->sc_dev;

	अगर ((cm_node->ipv4 &&
	     i40iw_ipv4_is_loopback(cm_node->loc_addr[0], cm_node->rem_addr[0])) ||
	     (!cm_node->ipv4 && i40iw_ipv6_is_loopback(cm_node->loc_addr,
						       cm_node->rem_addr))) अणु
		arpindex = i40iw_arp_table(iwdev,
					   cm_node->rem_addr,
					   false,
					   शून्य,
					   I40IW_ARP_RESOLVE);
	पूर्ण अन्यथा अणु
		oldarpindex = i40iw_arp_table(iwdev,
					      cm_node->rem_addr,
					      false,
					      शून्य,
					      I40IW_ARP_RESOLVE);
		अगर (cm_node->ipv4)
			arpindex = i40iw_addr_resolve_neigh(iwdev,
							    cm_info->loc_addr[0],
							    cm_info->rem_addr[0],
							    oldarpindex);
		अन्यथा अगर (IS_ENABLED(CONFIG_IPV6))
			arpindex = i40iw_addr_resolve_neigh_ipv6(iwdev,
								 cm_info->loc_addr,
								 cm_info->rem_addr,
								 oldarpindex);
		अन्यथा
			arpindex = -EINVAL;
	पूर्ण
	अगर (arpindex < 0) अणु
		i40iw_pr_err("cm_node arpindex\n");
		kमुक्त(cm_node);
		वापस शून्य;
	पूर्ण
	ether_addr_copy(cm_node->rem_mac, iwdev->arp_table[arpindex].mac_addr);
	i40iw_add_hte_node(cm_core, cm_node);
	cm_core->stats_nodes_created++;
	वापस cm_node;
पूर्ण

/**
 * i40iw_rem_ref_cm_node - destroy an instance of a cm node
 * @cm_node: connection's node
 */
अटल व्योम i40iw_rem_ref_cm_node(काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_cm_core *cm_core = cm_node->cm_core;
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_cm_info nfo;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm_node->cm_core->ht_lock, flags);
	अगर (atomic_dec_वापस(&cm_node->ref_count)) अणु
		spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);
		वापस;
	पूर्ण
	list_del(&cm_node->list);
	spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);

	/* अगर the node is destroyed beक्रमe connection was accelerated */
	अगर (!cm_node->accelerated && cm_node->accept_pend) अणु
		pr_err("node destroyed before established\n");
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
	पूर्ण
	अगर (cm_node->बंद_entry)
		i40iw_handle_बंद_entry(cm_node, 0);
	अगर (cm_node->listener) अणु
		i40iw_dec_refcnt_listen(cm_core, cm_node->listener, 0, true);
	पूर्ण अन्यथा अणु
		अगर (cm_node->apbvt_set) अणु
			i40iw_manage_apbvt(cm_node->iwdev,
					   cm_node->loc_port,
					   I40IW_MANAGE_APBVT_DEL);
			cm_node->apbvt_set = 0;
		पूर्ण
		i40iw_get_addr_info(cm_node, &nfo);
		अगर (cm_node->qhash_set) अणु
			i40iw_manage_qhash(cm_node->iwdev,
					   &nfo,
					   I40IW_QHASH_TYPE_TCP_ESTABLISHED,
					   I40IW_QHASH_MANAGE_TYPE_DELETE,
					   शून्य,
					   false);
			cm_node->qhash_set = 0;
		पूर्ण
	पूर्ण

	iwqp = cm_node->iwqp;
	अगर (iwqp) अणु
		iwqp->cm_node = शून्य;
		i40iw_qp_rem_ref(&iwqp->ibqp);
		cm_node->iwqp = शून्य;
	पूर्ण अन्यथा अगर (cm_node->qhash_set) अणु
		i40iw_get_addr_info(cm_node, &nfo);
		i40iw_manage_qhash(cm_node->iwdev,
				   &nfo,
				   I40IW_QHASH_TYPE_TCP_ESTABLISHED,
				   I40IW_QHASH_MANAGE_TYPE_DELETE,
				   शून्य,
				   false);
		cm_node->qhash_set = 0;
	पूर्ण

	cm_node->cm_core->stats_nodes_destroyed++;
	kमुक्त(cm_node);
पूर्ण

/**
 * i40iw_handle_fin_pkt - FIN packet received
 * @cm_node: connection's node
 */
अटल व्योम i40iw_handle_fin_pkt(काष्ठा i40iw_cm_node *cm_node)
अणु
	u32 ret;

	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_RCVD:
	हाल I40IW_CM_STATE_SYN_SENT:
	हाल I40IW_CM_STATE_ESTABLISHED:
	हाल I40IW_CM_STATE_MPAREJ_RCVD:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_LAST_ACK;
		i40iw_send_fin(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_MPAREQ_SENT:
		i40iw_create_event(cm_node, I40IW_CM_EVENT_ABORTED);
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_FIN_WAIT1:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSING;
		i40iw_send_ack(cm_node);
		/*
		 * Wait क्रम ACK as this is simultaneous बंद.
		 * After we receive ACK, करो not send anything.
		 * Just rm the node.
		 */
		अवरोध;
	हाल I40IW_CM_STATE_FIN_WAIT2:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_TIME_WAIT;
		i40iw_send_ack(cm_node);
		ret =
		    i40iw_schedule_cm_समयr(cm_node, शून्य, I40IW_TIMER_TYPE_CLOSE, 1, 0);
		अगर (ret)
			i40iw_pr_err("node %p state = %d\n", cm_node, cm_node->state);
		अवरोध;
	हाल I40IW_CM_STATE_TIME_WAIT:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		i40iw_rem_ref_cm_node(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_OFFLOADED:
	शेष:
		i40iw_pr_err("bad state node %p state = %d\n", cm_node, cm_node->state);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_handle_rst_pkt - process received RST packet
 * @cm_node: connection's node
 * @rbuf: receive buffer
 */
अटल व्योम i40iw_handle_rst_pkt(काष्ठा i40iw_cm_node *cm_node,
				 काष्ठा i40iw_puda_buf *rbuf)
अणु
	i40iw_cleanup_retrans_entry(cm_node);
	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_SENT:
	हाल I40IW_CM_STATE_MPAREQ_SENT:
		चयन (cm_node->mpa_frame_rev) अणु
		हाल IETF_MPA_V2:
			cm_node->mpa_frame_rev = IETF_MPA_V1;
			/* send a syn and जाओ syn sent state */
			cm_node->state = I40IW_CM_STATE_SYN_SENT;
			अगर (i40iw_send_syn(cm_node, 0))
				i40iw_active_खोलो_err(cm_node, false);
			अवरोध;
		हाल IETF_MPA_V1:
		शेष:
			i40iw_active_खोलो_err(cm_node, false);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल I40IW_CM_STATE_MPAREQ_RCVD:
		atomic_inc(&cm_node->passive_state);
		अवरोध;
	हाल I40IW_CM_STATE_ESTABLISHED:
	हाल I40IW_CM_STATE_SYN_RCVD:
	हाल I40IW_CM_STATE_LISTENING:
		i40iw_pr_err("Bad state state = %d\n", cm_node->state);
		i40iw_passive_खोलो_err(cm_node, false);
		अवरोध;
	हाल I40IW_CM_STATE_OFFLOADED:
		i40iw_active_खोलो_err(cm_node, false);
		अवरोध;
	हाल I40IW_CM_STATE_CLOSED:
		अवरोध;
	हाल I40IW_CM_STATE_FIN_WAIT2:
	हाल I40IW_CM_STATE_FIN_WAIT1:
	हाल I40IW_CM_STATE_LAST_ACK:
		cm_node->cm_id->rem_ref(cm_node->cm_id);
		fallthrough;
	हाल I40IW_CM_STATE_TIME_WAIT:
		cm_node->state = I40IW_CM_STATE_CLOSED;
		i40iw_rem_ref_cm_node(cm_node);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_handle_rcv_mpa - Process a recv'd mpa buffer
 * @cm_node: connection's node
 * @rbuf: receive buffer
 */
अटल व्योम i40iw_handle_rcv_mpa(काष्ठा i40iw_cm_node *cm_node,
				 काष्ठा i40iw_puda_buf *rbuf)
अणु
	पूर्णांक ret;
	पूर्णांक datasize = rbuf->datalen;
	u8 *dataloc = rbuf->data;

	क्रमागत i40iw_cm_event_type type = I40IW_CM_EVENT_UNKNOWN;
	u32 res_type;

	ret = i40iw_parse_mpa(cm_node, dataloc, &res_type, datasize);
	अगर (ret) अणु
		अगर (cm_node->state == I40IW_CM_STATE_MPAREQ_SENT)
			i40iw_active_खोलो_err(cm_node, true);
		अन्यथा
			i40iw_passive_खोलो_err(cm_node, true);
		वापस;
	पूर्ण

	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_ESTABLISHED:
		अगर (res_type == I40IW_MPA_REQUEST_REJECT)
			i40iw_pr_err("state for reject\n");
		cm_node->state = I40IW_CM_STATE_MPAREQ_RCVD;
		type = I40IW_CM_EVENT_MPA_REQ;
		i40iw_send_ack(cm_node);	/* ACK received MPA request */
		atomic_set(&cm_node->passive_state,
			   I40IW_PASSIVE_STATE_INDICATED);
		अवरोध;
	हाल I40IW_CM_STATE_MPAREQ_SENT:
		i40iw_cleanup_retrans_entry(cm_node);
		अगर (res_type == I40IW_MPA_REQUEST_REJECT) अणु
			type = I40IW_CM_EVENT_MPA_REJECT;
			cm_node->state = I40IW_CM_STATE_MPAREJ_RCVD;
		पूर्ण अन्यथा अणु
			type = I40IW_CM_EVENT_CONNECTED;
			cm_node->state = I40IW_CM_STATE_OFFLOADED;
		पूर्ण
		i40iw_send_ack(cm_node);
		अवरोध;
	शेष:
		pr_err("%s wrong cm_node state =%d\n", __func__, cm_node->state);
		अवरोध;
	पूर्ण
	i40iw_create_event(cm_node, type);
पूर्ण

/**
 * i40iw_indicate_pkt_err - Send up err event to cm
 * @cm_node: connection's node
 */
अटल व्योम i40iw_indicate_pkt_err(काष्ठा i40iw_cm_node *cm_node)
अणु
	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_SENT:
	हाल I40IW_CM_STATE_MPAREQ_SENT:
		i40iw_active_खोलो_err(cm_node, true);
		अवरोध;
	हाल I40IW_CM_STATE_ESTABLISHED:
	हाल I40IW_CM_STATE_SYN_RCVD:
		i40iw_passive_खोलो_err(cm_node, true);
		अवरोध;
	हाल I40IW_CM_STATE_OFFLOADED:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_check_syn - Check क्रम error on received syn ack
 * @cm_node: connection's node
 * @tcph: poपूर्णांकer tcp header
 */
अटल पूर्णांक i40iw_check_syn(काष्ठा i40iw_cm_node *cm_node, काष्ठा tcphdr *tcph)
अणु
	पूर्णांक err = 0;

	अगर (ntohl(tcph->ack_seq) != cm_node->tcp_cntxt.loc_seq_num) अणु
		err = 1;
		i40iw_active_खोलो_err(cm_node, true);
	पूर्ण
	वापस err;
पूर्ण

/**
 * i40iw_check_seq - check seq numbers अगर OK
 * @cm_node: connection's node
 * @tcph: poपूर्णांकer tcp header
 */
अटल पूर्णांक i40iw_check_seq(काष्ठा i40iw_cm_node *cm_node, काष्ठा tcphdr *tcph)
अणु
	पूर्णांक err = 0;
	u32 seq;
	u32 ack_seq;
	u32 loc_seq_num = cm_node->tcp_cntxt.loc_seq_num;
	u32 rcv_nxt = cm_node->tcp_cntxt.rcv_nxt;
	u32 rcv_wnd;

	seq = ntohl(tcph->seq);
	ack_seq = ntohl(tcph->ack_seq);
	rcv_wnd = cm_node->tcp_cntxt.rcv_wnd;
	अगर (ack_seq != loc_seq_num)
		err = -1;
	अन्यथा अगर (!between(seq, rcv_nxt, (rcv_nxt + rcv_wnd)))
		err = -1;
	अगर (err) अणु
		i40iw_pr_err("seq number\n");
		i40iw_indicate_pkt_err(cm_node);
	पूर्ण
	वापस err;
पूर्ण

/**
 * i40iw_handle_syn_pkt - is क्रम Passive node
 * @cm_node: connection's node
 * @rbuf: receive buffer
 */
अटल व्योम i40iw_handle_syn_pkt(काष्ठा i40iw_cm_node *cm_node,
				 काष्ठा i40iw_puda_buf *rbuf)
अणु
	काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)rbuf->tcph;
	पूर्णांक ret;
	u32 inc_sequence;
	पूर्णांक optionsize;
	काष्ठा i40iw_cm_info nfo;

	optionsize = (tcph->करोff << 2) - माप(काष्ठा tcphdr);
	inc_sequence = ntohl(tcph->seq);

	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_SENT:
	हाल I40IW_CM_STATE_MPAREQ_SENT:
		/* Rcvd syn on active खोलो connection */
		i40iw_active_खोलो_err(cm_node, 1);
		अवरोध;
	हाल I40IW_CM_STATE_LISTENING:
		/* Passive OPEN */
		अगर (atomic_पढ़ो(&cm_node->listener->pend_accepts_cnt) >
		    cm_node->listener->backlog) अणु
			cm_node->cm_core->stats_backlog_drops++;
			i40iw_passive_खोलो_err(cm_node, false);
			अवरोध;
		पूर्ण
		ret = i40iw_handle_tcp_options(cm_node, tcph, optionsize, 1);
		अगर (ret) अणु
			i40iw_passive_खोलो_err(cm_node, false);
			/* drop pkt */
			अवरोध;
		पूर्ण
		cm_node->tcp_cntxt.rcv_nxt = inc_sequence + 1;
		cm_node->accept_pend = 1;
		atomic_inc(&cm_node->listener->pend_accepts_cnt);

		cm_node->state = I40IW_CM_STATE_SYN_RCVD;
		i40iw_get_addr_info(cm_node, &nfo);
		ret = i40iw_manage_qhash(cm_node->iwdev,
					 &nfo,
					 I40IW_QHASH_TYPE_TCP_ESTABLISHED,
					 I40IW_QHASH_MANAGE_TYPE_ADD,
					 (व्योम *)cm_node,
					 false);
		cm_node->qhash_set = true;
		अवरोध;
	हाल I40IW_CM_STATE_CLOSED:
		i40iw_cleanup_retrans_entry(cm_node);
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_OFFLOADED:
	हाल I40IW_CM_STATE_ESTABLISHED:
	हाल I40IW_CM_STATE_FIN_WAIT1:
	हाल I40IW_CM_STATE_FIN_WAIT2:
	हाल I40IW_CM_STATE_MPAREQ_RCVD:
	हाल I40IW_CM_STATE_LAST_ACK:
	हाल I40IW_CM_STATE_CLOSING:
	हाल I40IW_CM_STATE_UNKNOWN:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_handle_synack_pkt - Process SYN+ACK packet (active side)
 * @cm_node: connection's node
 * @rbuf: receive buffer
 */
अटल व्योम i40iw_handle_synack_pkt(काष्ठा i40iw_cm_node *cm_node,
				    काष्ठा i40iw_puda_buf *rbuf)
अणु
	काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)rbuf->tcph;
	पूर्णांक ret;
	u32 inc_sequence;
	पूर्णांक optionsize;

	optionsize = (tcph->करोff << 2) - माप(काष्ठा tcphdr);
	inc_sequence = ntohl(tcph->seq);
	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_SENT:
		i40iw_cleanup_retrans_entry(cm_node);
		/* active खोलो */
		अगर (i40iw_check_syn(cm_node, tcph)) अणु
			i40iw_pr_err("check syn fail\n");
			वापस;
		पूर्ण
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		/* setup options */
		ret = i40iw_handle_tcp_options(cm_node, tcph, optionsize, 0);
		अगर (ret) अणु
			i40iw_debug(cm_node->dev,
				    I40IW_DEBUG_CM,
				    "cm_node=%p tcp_options failed\n",
				    cm_node);
			अवरोध;
		पूर्ण
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->tcp_cntxt.rcv_nxt = inc_sequence + 1;
		i40iw_send_ack(cm_node);	/* ACK  क्रम the syn_ack */
		ret = i40iw_send_mpa_request(cm_node);
		अगर (ret) अणु
			i40iw_debug(cm_node->dev,
				    I40IW_DEBUG_CM,
				    "cm_node=%p i40iw_send_mpa_request failed\n",
				    cm_node);
			अवरोध;
		पूर्ण
		cm_node->state = I40IW_CM_STATE_MPAREQ_SENT;
		अवरोध;
	हाल I40IW_CM_STATE_MPAREQ_RCVD:
		i40iw_passive_खोलो_err(cm_node, true);
		अवरोध;
	हाल I40IW_CM_STATE_LISTENING:
		cm_node->tcp_cntxt.loc_seq_num = ntohl(tcph->ack_seq);
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_CLOSED:
		cm_node->tcp_cntxt.loc_seq_num = ntohl(tcph->ack_seq);
		i40iw_cleanup_retrans_entry(cm_node);
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_ESTABLISHED:
	हाल I40IW_CM_STATE_FIN_WAIT1:
	हाल I40IW_CM_STATE_FIN_WAIT2:
	हाल I40IW_CM_STATE_LAST_ACK:
	हाल I40IW_CM_STATE_OFFLOADED:
	हाल I40IW_CM_STATE_CLOSING:
	हाल I40IW_CM_STATE_UNKNOWN:
	हाल I40IW_CM_STATE_MPAREQ_SENT:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_handle_ack_pkt - process packet with ACK
 * @cm_node: connection's node
 * @rbuf: receive buffer
 */
अटल पूर्णांक i40iw_handle_ack_pkt(काष्ठा i40iw_cm_node *cm_node,
				काष्ठा i40iw_puda_buf *rbuf)
अणु
	काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)rbuf->tcph;
	u32 inc_sequence;
	पूर्णांक ret = 0;
	पूर्णांक optionsize;
	u32 datasize = rbuf->datalen;

	optionsize = (tcph->करोff << 2) - माप(काष्ठा tcphdr);

	अगर (i40iw_check_seq(cm_node, tcph))
		वापस -EINVAL;

	inc_sequence = ntohl(tcph->seq);
	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_RCVD:
		i40iw_cleanup_retrans_entry(cm_node);
		ret = i40iw_handle_tcp_options(cm_node, tcph, optionsize, 1);
		अगर (ret)
			अवरोध;
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		cm_node->state = I40IW_CM_STATE_ESTABLISHED;
		अगर (datasize) अणु
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			i40iw_handle_rcv_mpa(cm_node, rbuf);
		पूर्ण
		अवरोध;
	हाल I40IW_CM_STATE_ESTABLISHED:
		i40iw_cleanup_retrans_entry(cm_node);
		अगर (datasize) अणु
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			i40iw_handle_rcv_mpa(cm_node, rbuf);
		पूर्ण
		अवरोध;
	हाल I40IW_CM_STATE_MPAREQ_SENT:
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		अगर (datasize) अणु
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			cm_node->ack_rcvd = false;
			i40iw_handle_rcv_mpa(cm_node, rbuf);
		पूर्ण अन्यथा अणु
			cm_node->ack_rcvd = true;
		पूर्ण
		अवरोध;
	हाल I40IW_CM_STATE_LISTENING:
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_CLOSED:
		i40iw_cleanup_retrans_entry(cm_node);
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_LAST_ACK:
	हाल I40IW_CM_STATE_CLOSING:
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		अगर (!cm_node->accept_pend)
			cm_node->cm_id->rem_ref(cm_node->cm_id);
		i40iw_rem_ref_cm_node(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_FIN_WAIT1:
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_FIN_WAIT2;
		अवरोध;
	हाल I40IW_CM_STATE_SYN_SENT:
	हाल I40IW_CM_STATE_FIN_WAIT2:
	हाल I40IW_CM_STATE_OFFLOADED:
	हाल I40IW_CM_STATE_MPAREQ_RCVD:
	हाल I40IW_CM_STATE_UNKNOWN:
	शेष:
		i40iw_cleanup_retrans_entry(cm_node);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40iw_process_packet - process cm packet
 * @cm_node: connection's node
 * @rbuf: receive buffer
 */
अटल व्योम i40iw_process_packet(काष्ठा i40iw_cm_node *cm_node,
				 काष्ठा i40iw_puda_buf *rbuf)
अणु
	क्रमागत i40iw_tcpip_pkt_type pkt_type = I40IW_PKT_TYPE_UNKNOWN;
	काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)rbuf->tcph;
	u32 fin_set = 0;
	पूर्णांक ret;

	अगर (tcph->rst) अणु
		pkt_type = I40IW_PKT_TYPE_RST;
	पूर्ण अन्यथा अगर (tcph->syn) अणु
		pkt_type = I40IW_PKT_TYPE_SYN;
		अगर (tcph->ack)
			pkt_type = I40IW_PKT_TYPE_SYNACK;
	पूर्ण अन्यथा अगर (tcph->ack) अणु
		pkt_type = I40IW_PKT_TYPE_ACK;
	पूर्ण
	अगर (tcph->fin)
		fin_set = 1;

	चयन (pkt_type) अणु
	हाल I40IW_PKT_TYPE_SYN:
		i40iw_handle_syn_pkt(cm_node, rbuf);
		अवरोध;
	हाल I40IW_PKT_TYPE_SYNACK:
		i40iw_handle_synack_pkt(cm_node, rbuf);
		अवरोध;
	हाल I40IW_PKT_TYPE_ACK:
		ret = i40iw_handle_ack_pkt(cm_node, rbuf);
		अगर (fin_set && !ret)
			i40iw_handle_fin_pkt(cm_node);
		अवरोध;
	हाल I40IW_PKT_TYPE_RST:
		i40iw_handle_rst_pkt(cm_node, rbuf);
		अवरोध;
	शेष:
		अगर (fin_set &&
		    (!i40iw_check_seq(cm_node, (काष्ठा tcphdr *)rbuf->tcph)))
			i40iw_handle_fin_pkt(cm_node);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_make_listen_node - create a listen node with params
 * @cm_core: cm's core
 * @iwdev: iwarp device काष्ठाure
 * @cm_info: quad info क्रम connection
 */
अटल काष्ठा i40iw_cm_listener *i40iw_make_listen_node(
					काष्ठा i40iw_cm_core *cm_core,
					काष्ठा i40iw_device *iwdev,
					काष्ठा i40iw_cm_info *cm_info)
अणु
	काष्ठा i40iw_cm_listener *listener;
	अचिन्हित दीर्घ flags;

	/* cannot have multiple matching listeners */
	listener = i40iw_find_listener(cm_core, cm_info->loc_addr,
				       cm_info->loc_port,
				       cm_info->vlan_id,
				       I40IW_CM_LISTENER_EITHER_STATE);
	अगर (listener &&
	    (listener->listener_state == I40IW_CM_LISTENER_ACTIVE_STATE)) अणु
		atomic_dec(&listener->ref_count);
		i40iw_debug(cm_core->dev,
			    I40IW_DEBUG_CM,
			    "Not creating listener since it already exists\n");
		वापस शून्य;
	पूर्ण

	अगर (!listener) अणु
		/* create a CM listen node (1/2 node to compare incoming traffic to) */
		listener = kzalloc(माप(*listener), GFP_KERNEL);
		अगर (!listener)
			वापस शून्य;
		cm_core->stats_listen_nodes_created++;
		स_नकल(listener->loc_addr, cm_info->loc_addr, माप(listener->loc_addr));
		listener->loc_port = cm_info->loc_port;

		INIT_LIST_HEAD(&listener->child_listen_list);

		atomic_set(&listener->ref_count, 1);
	पूर्ण अन्यथा अणु
		listener->reused_node = 1;
	पूर्ण

	listener->cm_id = cm_info->cm_id;
	listener->ipv4 = cm_info->ipv4;
	listener->vlan_id = cm_info->vlan_id;
	atomic_set(&listener->pend_accepts_cnt, 0);
	listener->cm_core = cm_core;
	listener->iwdev = iwdev;

	listener->backlog = cm_info->backlog;
	listener->listener_state = I40IW_CM_LISTENER_ACTIVE_STATE;

	अगर (!listener->reused_node) अणु
		spin_lock_irqsave(&cm_core->listen_list_lock, flags);
		list_add(&listener->list, &cm_core->listen_nodes);
		spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);
	पूर्ण

	वापस listener;
पूर्ण

/**
 * i40iw_create_cm_node - make a connection node with params
 * @cm_core: cm's core
 * @iwdev: iwarp device काष्ठाure
 * @conn_param: upper layer connection parameters
 * @cm_info: quad info क्रम connection
 */
अटल काष्ठा i40iw_cm_node *i40iw_create_cm_node(
					काष्ठा i40iw_cm_core *cm_core,
					काष्ठा i40iw_device *iwdev,
					काष्ठा iw_cm_conn_param *conn_param,
					काष्ठा i40iw_cm_info *cm_info)
अणु
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा i40iw_cm_listener *loopback_remotelistener;
	काष्ठा i40iw_cm_node *loopback_remotenode;
	काष्ठा i40iw_cm_info loopback_cm_info;

	u16 निजी_data_len = conn_param->निजी_data_len;
	स्थिर व्योम *निजी_data = conn_param->निजी_data;

	/* create a CM connection node */
	cm_node = i40iw_make_cm_node(cm_core, iwdev, cm_info, शून्य);
	अगर (!cm_node)
		वापस ERR_PTR(-ENOMEM);
	/* set our node side to client (active) side */
	cm_node->tcp_cntxt.client = 1;
	cm_node->tcp_cntxt.rcv_wscale = I40IW_CM_DEFAULT_RCV_WND_SCALE;

	i40iw_record_ird_ord(cm_node, conn_param->ird, conn_param->ord);

	अगर (!स_भेद(cm_info->loc_addr, cm_info->rem_addr, माप(cm_info->loc_addr))) अणु
		loopback_remotelistener = i40iw_find_listener(
						cm_core,
						cm_info->rem_addr,
						cm_node->rem_port,
						cm_node->vlan_id,
						I40IW_CM_LISTENER_ACTIVE_STATE);
		अगर (!loopback_remotelistener) अणु
			i40iw_rem_ref_cm_node(cm_node);
			वापस ERR_PTR(-ECONNREFUSED);
		पूर्ण अन्यथा अणु
			loopback_cm_info = *cm_info;
			loopback_cm_info.loc_port = cm_info->rem_port;
			loopback_cm_info.rem_port = cm_info->loc_port;
			loopback_cm_info.cm_id = loopback_remotelistener->cm_id;
			loopback_cm_info.ipv4 = cm_info->ipv4;
			loopback_remotenode = i40iw_make_cm_node(cm_core,
								 iwdev,
								 &loopback_cm_info,
								 loopback_remotelistener);
			अगर (!loopback_remotenode) अणु
				i40iw_rem_ref_cm_node(cm_node);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
			cm_core->stats_loopbacks++;
			loopback_remotenode->loopbackpartner = cm_node;
			loopback_remotenode->tcp_cntxt.rcv_wscale =
				I40IW_CM_DEFAULT_RCV_WND_SCALE;
			cm_node->loopbackpartner = loopback_remotenode;
			स_नकल(loopback_remotenode->pdata_buf, निजी_data,
			       निजी_data_len);
			loopback_remotenode->pdata.size = निजी_data_len;

			अगर (loopback_remotenode->ord_size > cm_node->ird_size)
				loopback_remotenode->ord_size =
					cm_node->ird_size;

			cm_node->state = I40IW_CM_STATE_OFFLOADED;
			cm_node->tcp_cntxt.rcv_nxt =
				loopback_remotenode->tcp_cntxt.loc_seq_num;
			loopback_remotenode->tcp_cntxt.rcv_nxt =
				cm_node->tcp_cntxt.loc_seq_num;
			cm_node->tcp_cntxt.max_snd_wnd =
				loopback_remotenode->tcp_cntxt.rcv_wnd;
			loopback_remotenode->tcp_cntxt.max_snd_wnd = cm_node->tcp_cntxt.rcv_wnd;
			cm_node->tcp_cntxt.snd_wnd = loopback_remotenode->tcp_cntxt.rcv_wnd;
			loopback_remotenode->tcp_cntxt.snd_wnd = cm_node->tcp_cntxt.rcv_wnd;
			cm_node->tcp_cntxt.snd_wscale = loopback_remotenode->tcp_cntxt.rcv_wscale;
			loopback_remotenode->tcp_cntxt.snd_wscale = cm_node->tcp_cntxt.rcv_wscale;
		पूर्ण
		वापस cm_node;
	पूर्ण

	cm_node->pdata.size = निजी_data_len;
	cm_node->pdata.addr = cm_node->pdata_buf;

	स_नकल(cm_node->pdata_buf, निजी_data, निजी_data_len);

	cm_node->state = I40IW_CM_STATE_SYN_SENT;
	वापस cm_node;
पूर्ण

/**
 * i40iw_cm_reject - reject and tearकरोwn a connection
 * @cm_node: connection's node
 * @pdata: ptr to निजी data क्रम reject
 * @plen: size of निजी data
 */
अटल पूर्णांक i40iw_cm_reject(काष्ठा i40iw_cm_node *cm_node, स्थिर व्योम *pdata, u8 plen)
अणु
	पूर्णांक ret = 0;
	पूर्णांक err;
	पूर्णांक passive_state;
	काष्ठा iw_cm_id *cm_id = cm_node->cm_id;
	काष्ठा i40iw_cm_node *loopback = cm_node->loopbackpartner;

	अगर (cm_node->tcp_cntxt.client)
		वापस ret;
	i40iw_cleanup_retrans_entry(cm_node);

	अगर (!loopback) अणु
		passive_state = atomic_inc_वापस(&cm_node->passive_state);
		अगर (passive_state == I40IW_SEND_RESET_EVENT) अणु
			cm_node->state = I40IW_CM_STATE_CLOSED;
			i40iw_rem_ref_cm_node(cm_node);
		पूर्ण अन्यथा अणु
			अगर (cm_node->state == I40IW_CM_STATE_LISTENER_DESTROYED) अणु
				i40iw_rem_ref_cm_node(cm_node);
			पूर्ण अन्यथा अणु
				ret = i40iw_send_mpa_reject(cm_node, pdata, plen);
				अगर (ret) अणु
					cm_node->state = I40IW_CM_STATE_CLOSED;
					err = i40iw_send_reset(cm_node);
					अगर (err)
						i40iw_pr_err("send reset failed\n");
				पूर्ण अन्यथा अणु
					cm_id->add_ref(cm_id);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		cm_node->cm_id = शून्य;
		अगर (cm_node->state == I40IW_CM_STATE_LISTENER_DESTROYED) अणु
			i40iw_rem_ref_cm_node(cm_node);
			i40iw_rem_ref_cm_node(loopback);
		पूर्ण अन्यथा अणु
			ret = i40iw_send_cm_event(loopback,
						  loopback->cm_id,
						  IW_CM_EVENT_CONNECT_REPLY,
						  -ECONNREFUSED);
			i40iw_rem_ref_cm_node(cm_node);
			loopback->state = I40IW_CM_STATE_CLOSING;

			cm_id = loopback->cm_id;
			i40iw_rem_ref_cm_node(loopback);
			cm_id->rem_ref(cm_id);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40iw_cm_बंद - बंद of cm connection
 * @cm_node: connection's node
 */
अटल पूर्णांक i40iw_cm_बंद(काष्ठा i40iw_cm_node *cm_node)
अणु
	पूर्णांक ret = 0;

	अगर (!cm_node)
		वापस -EINVAL;

	चयन (cm_node->state) अणु
	हाल I40IW_CM_STATE_SYN_RCVD:
	हाल I40IW_CM_STATE_SYN_SENT:
	हाल I40IW_CM_STATE_ONE_SIDE_ESTABLISHED:
	हाल I40IW_CM_STATE_ESTABLISHED:
	हाल I40IW_CM_STATE_ACCEPTING:
	हाल I40IW_CM_STATE_MPAREQ_SENT:
	हाल I40IW_CM_STATE_MPAREQ_RCVD:
		i40iw_cleanup_retrans_entry(cm_node);
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_CLOSE_WAIT:
		cm_node->state = I40IW_CM_STATE_LAST_ACK;
		i40iw_send_fin(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_FIN_WAIT1:
	हाल I40IW_CM_STATE_FIN_WAIT2:
	हाल I40IW_CM_STATE_LAST_ACK:
	हाल I40IW_CM_STATE_TIME_WAIT:
	हाल I40IW_CM_STATE_CLOSING:
		ret = -1;
		अवरोध;
	हाल I40IW_CM_STATE_LISTENING:
		i40iw_cleanup_retrans_entry(cm_node);
		i40iw_send_reset(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_MPAREJ_RCVD:
	हाल I40IW_CM_STATE_UNKNOWN:
	हाल I40IW_CM_STATE_INITED:
	हाल I40IW_CM_STATE_CLOSED:
	हाल I40IW_CM_STATE_LISTENER_DESTROYED:
		i40iw_rem_ref_cm_node(cm_node);
		अवरोध;
	हाल I40IW_CM_STATE_OFFLOADED:
		अगर (cm_node->send_entry)
			i40iw_pr_err("send_entry\n");
		i40iw_rem_ref_cm_node(cm_node);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40iw_receive_ilq - recv an ETHERNET packet, and process it
 * through CM
 * @vsi: poपूर्णांकer to the vsi काष्ठाure
 * @rbuf: receive buffer
 */
व्योम i40iw_receive_ilq(काष्ठा i40iw_sc_vsi *vsi, काष्ठा i40iw_puda_buf *rbuf)
अणु
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा i40iw_cm_listener *listener;
	काष्ठा iphdr *iph;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा tcphdr *tcph;
	काष्ठा i40iw_cm_info cm_info;
	काष्ठा i40iw_sc_dev *dev = vsi->dev;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;
	काष्ठा i40iw_cm_core *cm_core = &iwdev->cm_core;
	काष्ठा vlan_ethhdr *ethh;
	u16 vtag;

	/* अगर vlan, then maclen = 18 अन्यथा 14 */
	iph = (काष्ठा iphdr *)rbuf->iph;
	स_रखो(&cm_info, 0, माप(cm_info));

	i40iw_debug_buf(dev,
			I40IW_DEBUG_ILQ,
			"RECEIVE ILQ BUFFER",
			rbuf->mem.va,
			rbuf->totallen);
	ethh = (काष्ठा vlan_ethhdr *)rbuf->mem.va;

	अगर (ethh->h_vlan_proto == htons(ETH_P_8021Q)) अणु
		vtag = ntohs(ethh->h_vlan_TCI);
		cm_info.user_pri = (vtag & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
		cm_info.vlan_id = vtag & VLAN_VID_MASK;
		i40iw_debug(cm_core->dev,
			    I40IW_DEBUG_CM,
			    "%s vlan_id=%d\n",
			    __func__,
			    cm_info.vlan_id);
	पूर्ण अन्यथा अणु
		cm_info.vlan_id = I40IW_NO_VLAN;
	पूर्ण
	tcph = (काष्ठा tcphdr *)rbuf->tcph;

	अगर (rbuf->ipv4) अणु
		cm_info.loc_addr[0] = ntohl(iph->daddr);
		cm_info.rem_addr[0] = ntohl(iph->saddr);
		cm_info.ipv4 = true;
		cm_info.tos = iph->tos;
	पूर्ण अन्यथा अणु
		ip6h = (काष्ठा ipv6hdr *)rbuf->iph;
		i40iw_copy_ip_ntohl(cm_info.loc_addr,
				    ip6h->daddr.in6_u.u6_addr32);
		i40iw_copy_ip_ntohl(cm_info.rem_addr,
				    ip6h->saddr.in6_u.u6_addr32);
		cm_info.ipv4 = false;
		cm_info.tos = (ip6h->priority << 4) | (ip6h->flow_lbl[0] >> 4);
	पूर्ण
	cm_info.loc_port = ntohs(tcph->dest);
	cm_info.rem_port = ntohs(tcph->source);
	cm_node = i40iw_find_node(cm_core,
				  cm_info.rem_port,
				  cm_info.rem_addr,
				  cm_info.loc_port,
				  cm_info.loc_addr,
				  true,
				  false);

	अगर (!cm_node) अणु
		/* Only type of packet accepted are क्रम */
		/* the PASSIVE खोलो (syn only) */
		अगर (!tcph->syn || tcph->ack)
			वापस;
		listener =
		    i40iw_find_listener(cm_core,
					cm_info.loc_addr,
					cm_info.loc_port,
					cm_info.vlan_id,
					I40IW_CM_LISTENER_ACTIVE_STATE);
		अगर (!listener) अणु
			cm_info.cm_id = शून्य;
			i40iw_debug(cm_core->dev,
				    I40IW_DEBUG_CM,
				    "%s no listener found\n",
				    __func__);
			वापस;
		पूर्ण
		cm_info.cm_id = listener->cm_id;
		cm_node = i40iw_make_cm_node(cm_core, iwdev, &cm_info, listener);
		अगर (!cm_node) अणु
			i40iw_debug(cm_core->dev,
				    I40IW_DEBUG_CM,
				    "%s allocate node failed\n",
				    __func__);
			atomic_dec(&listener->ref_count);
			वापस;
		पूर्ण
		अगर (!tcph->rst && !tcph->fin) अणु
			cm_node->state = I40IW_CM_STATE_LISTENING;
		पूर्ण अन्यथा अणु
			i40iw_rem_ref_cm_node(cm_node);
			वापस;
		पूर्ण
		atomic_inc(&cm_node->ref_count);
	पूर्ण अन्यथा अगर (cm_node->state == I40IW_CM_STATE_OFFLOADED) अणु
		i40iw_rem_ref_cm_node(cm_node);
		वापस;
	पूर्ण
	i40iw_process_packet(cm_node, rbuf);
	i40iw_rem_ref_cm_node(cm_node);
पूर्ण

/**
 * i40iw_setup_cm_core - allocate a top level instance of a cm
 * core
 * @iwdev: iwarp device काष्ठाure
 */
पूर्णांक i40iw_setup_cm_core(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_cm_core *cm_core = &iwdev->cm_core;

	cm_core->iwdev = iwdev;
	cm_core->dev = &iwdev->sc_dev;

	INIT_LIST_HEAD(&cm_core->accelerated_list);
	INIT_LIST_HEAD(&cm_core->non_accelerated_list);
	INIT_LIST_HEAD(&cm_core->listen_nodes);

	समयr_setup(&cm_core->tcp_समयr, i40iw_cm_समयr_tick, 0);

	spin_lock_init(&cm_core->ht_lock);
	spin_lock_init(&cm_core->listen_list_lock);
	spin_lock_init(&cm_core->apbvt_lock);

	cm_core->event_wq = alloc_ordered_workqueue("iwewq",
						    WQ_MEM_RECLAIM);
	अगर (!cm_core->event_wq)
		जाओ error;

	cm_core->disconn_wq = alloc_ordered_workqueue("iwdwq",
						      WQ_MEM_RECLAIM);
	अगर (!cm_core->disconn_wq)
		जाओ error;

	वापस 0;
error:
	i40iw_cleanup_cm_core(&iwdev->cm_core);

	वापस -ENOMEM;
पूर्ण

/**
 * i40iw_cleanup_cm_core - deallocate a top level instance of a
 * cm core
 * @cm_core: cm's core
 */
व्योम i40iw_cleanup_cm_core(काष्ठा i40iw_cm_core *cm_core)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!cm_core)
		वापस;

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	अगर (समयr_pending(&cm_core->tcp_समयr))
		del_समयr_sync(&cm_core->tcp_समयr);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	अगर (cm_core->event_wq)
		destroy_workqueue(cm_core->event_wq);
	अगर (cm_core->disconn_wq)
		destroy_workqueue(cm_core->disconn_wq);
पूर्ण

/**
 * i40iw_init_tcp_ctx - setup qp context
 * @cm_node: connection's node
 * @tcp_info: offload info क्रम tcp
 * @iwqp: associate qp क्रम the connection
 */
अटल व्योम i40iw_init_tcp_ctx(काष्ठा i40iw_cm_node *cm_node,
			       काष्ठा i40iw_tcp_offload_info *tcp_info,
			       काष्ठा i40iw_qp *iwqp)
अणु
	tcp_info->ipv4 = cm_node->ipv4;
	tcp_info->drop_ooo_seg = true;
	tcp_info->wscale = true;
	tcp_info->ignore_tcp_opt = true;
	tcp_info->ignore_tcp_uns_opt = true;
	tcp_info->no_nagle = false;

	tcp_info->ttl = I40IW_DEFAULT_TTL;
	tcp_info->rtt_var = cpu_to_le32(I40IW_DEFAULT_RTT_VAR);
	tcp_info->ss_thresh = cpu_to_le32(I40IW_DEFAULT_SS_THRESH);
	tcp_info->rexmit_thresh = I40IW_DEFAULT_REXMIT_THRESH;

	tcp_info->tcp_state = I40IW_TCP_STATE_ESTABLISHED;
	tcp_info->snd_wscale = cm_node->tcp_cntxt.snd_wscale;
	tcp_info->rcv_wscale = cm_node->tcp_cntxt.rcv_wscale;

	tcp_info->snd_nxt = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);
	tcp_info->snd_wnd = cpu_to_le32(cm_node->tcp_cntxt.snd_wnd);
	tcp_info->rcv_nxt = cpu_to_le32(cm_node->tcp_cntxt.rcv_nxt);
	tcp_info->snd_max = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);

	tcp_info->snd_una = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);
	tcp_info->cwnd = cpu_to_le32(2 * cm_node->tcp_cntxt.mss);
	tcp_info->snd_wl1 = cpu_to_le32(cm_node->tcp_cntxt.rcv_nxt);
	tcp_info->snd_wl2 = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);
	tcp_info->max_snd_winकरोw = cpu_to_le32(cm_node->tcp_cntxt.max_snd_wnd);
	tcp_info->rcv_wnd = cpu_to_le32(cm_node->tcp_cntxt.rcv_wnd <<
					cm_node->tcp_cntxt.rcv_wscale);

	tcp_info->flow_label = 0;
	tcp_info->snd_mss = cpu_to_le32(((u32)cm_node->tcp_cntxt.mss));
	अगर (cm_node->vlan_id <= VLAN_VID_MASK) अणु
		tcp_info->insert_vlan_tag = true;
		tcp_info->vlan_tag = cpu_to_le16(((u16)cm_node->user_pri << I40IW_VLAN_PRIO_SHIFT) |
						  cm_node->vlan_id);
	पूर्ण
	अगर (cm_node->ipv4) अणु
		tcp_info->src_port = cpu_to_le16(cm_node->loc_port);
		tcp_info->dst_port = cpu_to_le16(cm_node->rem_port);

		tcp_info->dest_ip_addr3 = cpu_to_le32(cm_node->rem_addr[0]);
		tcp_info->local_ipaddr3 = cpu_to_le32(cm_node->loc_addr[0]);
		tcp_info->arp_idx =
			cpu_to_le16((u16)i40iw_arp_table(
							 iwqp->iwdev,
							 &tcp_info->dest_ip_addr3,
							 true,
							 शून्य,
							 I40IW_ARP_RESOLVE));
	पूर्ण अन्यथा अणु
		tcp_info->src_port = cpu_to_le16(cm_node->loc_port);
		tcp_info->dst_port = cpu_to_le16(cm_node->rem_port);
		tcp_info->dest_ip_addr0 = cpu_to_le32(cm_node->rem_addr[0]);
		tcp_info->dest_ip_addr1 = cpu_to_le32(cm_node->rem_addr[1]);
		tcp_info->dest_ip_addr2 = cpu_to_le32(cm_node->rem_addr[2]);
		tcp_info->dest_ip_addr3 = cpu_to_le32(cm_node->rem_addr[3]);
		tcp_info->local_ipaddr0 = cpu_to_le32(cm_node->loc_addr[0]);
		tcp_info->local_ipaddr1 = cpu_to_le32(cm_node->loc_addr[1]);
		tcp_info->local_ipaddr2 = cpu_to_le32(cm_node->loc_addr[2]);
		tcp_info->local_ipaddr3 = cpu_to_le32(cm_node->loc_addr[3]);
		tcp_info->arp_idx =
			cpu_to_le16((u16)i40iw_arp_table(
							 iwqp->iwdev,
							 &tcp_info->dest_ip_addr0,
							 false,
							 शून्य,
							 I40IW_ARP_RESOLVE));
	पूर्ण
पूर्ण

/**
 * i40iw_cm_init_tsa_conn - setup qp क्रम RTS
 * @iwqp: associate qp क्रम the connection
 * @cm_node: connection's node
 */
अटल व्योम i40iw_cm_init_tsa_conn(काष्ठा i40iw_qp *iwqp,
				   काष्ठा i40iw_cm_node *cm_node)
अणु
	काष्ठा i40iw_tcp_offload_info tcp_info;
	काष्ठा i40iwarp_offload_info *iwarp_info;
	काष्ठा i40iw_qp_host_ctx_info *ctx_info;
	काष्ठा i40iw_device *iwdev = iwqp->iwdev;
	काष्ठा i40iw_sc_dev *dev = &iwqp->iwdev->sc_dev;

	स_रखो(&tcp_info, 0x00, माप(काष्ठा i40iw_tcp_offload_info));
	iwarp_info = &iwqp->iwarp_info;
	ctx_info = &iwqp->ctx_info;

	ctx_info->tcp_info = &tcp_info;
	ctx_info->send_cq_num = iwqp->iwscq->sc_cq.cq_uk.cq_id;
	ctx_info->rcv_cq_num = iwqp->iwrcq->sc_cq.cq_uk.cq_id;

	iwarp_info->ord_size = cm_node->ord_size;
	iwarp_info->ird_size = i40iw_derive_hw_ird_setting(cm_node->ird_size);

	अगर (iwarp_info->ord_size == 1)
		iwarp_info->ord_size = 2;

	iwarp_info->rd_enable = true;
	iwarp_info->rdmap_ver = 1;
	iwarp_info->ddp_ver = 1;

	iwarp_info->pd_id = iwqp->iwpd->sc_pd.pd_id;

	ctx_info->tcp_info_valid = true;
	ctx_info->iwarp_info_valid = true;
	ctx_info->add_to_qoslist = true;
	ctx_info->user_pri = cm_node->user_pri;

	i40iw_init_tcp_ctx(cm_node, &tcp_info, iwqp);
	अगर (cm_node->snd_mark_en) अणु
		iwarp_info->snd_mark_en = true;
		iwarp_info->snd_mark_offset = (tcp_info.snd_nxt &
				SNDMARKER_SEQNMASK) + cm_node->lsmm_size;
	पूर्ण

	cm_node->state = I40IW_CM_STATE_OFFLOADED;
	tcp_info.tcp_state = I40IW_TCP_STATE_ESTABLISHED;
	tcp_info.src_mac_addr_idx = iwdev->mac_ip_table_idx;
	tcp_info.tos = cm_node->tos;

	dev->iw_priv_qp_ops->qp_setctx(&iwqp->sc_qp, (u64 *)(iwqp->host_ctx.va), ctx_info);

	/* once tcp_info is set, no need to करो it again */
	ctx_info->tcp_info_valid = false;
	ctx_info->iwarp_info_valid = false;
	ctx_info->add_to_qoslist = false;
पूर्ण

/**
 * i40iw_cm_disconn - when a connection is being बंदd
 * @iwqp: associate qp क्रम the connection
 */
व्योम i40iw_cm_disconn(काष्ठा i40iw_qp *iwqp)
अणु
	काष्ठा disconn_work *work;
	काष्ठा i40iw_device *iwdev = iwqp->iwdev;
	काष्ठा i40iw_cm_core *cm_core = &iwdev->cm_core;
	अचिन्हित दीर्घ flags;

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस;	/* Timer will clean up */

	spin_lock_irqsave(&iwdev->qptable_lock, flags);
	अगर (!iwdev->qp_table[iwqp->ibqp.qp_num]) अणु
		spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_CM,
			    "%s qp_id %d is already freed\n",
			     __func__, iwqp->ibqp.qp_num);
		kमुक्त(work);
		वापस;
	पूर्ण
	i40iw_qp_add_ref(&iwqp->ibqp);
	spin_unlock_irqrestore(&iwdev->qptable_lock, flags);

	work->iwqp = iwqp;
	INIT_WORK(&work->work, i40iw_disconnect_worker);
	queue_work(cm_core->disconn_wq, &work->work);
	वापस;
पूर्ण

/**
 * i40iw_qp_disconnect - मुक्त qp and बंद cm
 * @iwqp: associate qp क्रम the connection
 */
अटल व्योम i40iw_qp_disconnect(काष्ठा i40iw_qp *iwqp)
अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_ib_device *iwibdev;

	iwdev = to_iwdev(iwqp->ibqp.device);
	अगर (!iwdev) अणु
		i40iw_pr_err("iwdev == NULL\n");
		वापस;
	पूर्ण

	iwibdev = iwdev->iwibdev;

	अगर (iwqp->active_conn) अणु
		/* indicate this connection is NOT active */
		iwqp->active_conn = 0;
	पूर्ण अन्यथा अणु
		/* Need to मुक्त the Last Streaming Mode Message */
		अगर (iwqp->ietf_mem.va) अणु
			अगर (iwqp->lsmm_mr)
				iwibdev->ibdev.ops.dereg_mr(iwqp->lsmm_mr,
							    शून्य);
			i40iw_मुक्त_dma_mem(iwdev->sc_dev.hw, &iwqp->ietf_mem);
		पूर्ण
	पूर्ण

	/* बंद the CM node करोwn अगर it is still active */
	अगर (iwqp->cm_node) अणु
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_CM, "%s Call close API\n", __func__);
		i40iw_cm_बंद(iwqp->cm_node);
	पूर्ण
पूर्ण

/**
 * i40iw_cm_disconn_true - called by worker thपढ़ो to disconnect qp
 * @iwqp: associate qp क्रम the connection
 */
अटल व्योम i40iw_cm_disconn_true(काष्ठा i40iw_qp *iwqp)
अणु
	काष्ठा iw_cm_id *cm_id;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_sc_qp *qp = &iwqp->sc_qp;
	u16 last_ae;
	u8 original_hw_tcp_state;
	u8 original_ibqp_state;
	पूर्णांक disconn_status = 0;
	पूर्णांक issue_disconn = 0;
	पूर्णांक issue_बंद = 0;
	पूर्णांक issue_flush = 0;
	काष्ठा ib_event ibevent;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!iwqp) अणु
		i40iw_pr_err("iwqp == NULL\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&iwqp->lock, flags);
	cm_id = iwqp->cm_id;
	/* make sure we havent alपढ़ोy बंदd this connection */
	अगर (!cm_id) अणु
		spin_unlock_irqrestore(&iwqp->lock, flags);
		वापस;
	पूर्ण

	iwdev = to_iwdev(iwqp->ibqp.device);

	original_hw_tcp_state = iwqp->hw_tcp_state;
	original_ibqp_state = iwqp->ibqp_state;
	last_ae = iwqp->last_aeq;

	अगर (qp->term_flags) अणु
		issue_disconn = 1;
		issue_बंद = 1;
		iwqp->cm_id = शून्य;
		/*When term समयr expires after cm_समयr, करोn't want
		 *terminate-handler to issue cm_disconn which can re-मुक्त
		 *a QP even after its refcnt=0.
		 */
		i40iw_terminate_del_समयr(qp);
		अगर (!iwqp->flush_issued) अणु
			iwqp->flush_issued = 1;
			issue_flush = 1;
		पूर्ण
	पूर्ण अन्यथा अगर ((original_hw_tcp_state == I40IW_TCP_STATE_CLOSE_WAIT) ||
		   ((original_ibqp_state == IB_QPS_RTS) &&
		    (last_ae == I40IW_AE_LLP_CONNECTION_RESET))) अणु
		issue_disconn = 1;
		अगर (last_ae == I40IW_AE_LLP_CONNECTION_RESET)
			disconn_status = -ECONNRESET;
	पूर्ण

	अगर (((original_hw_tcp_state == I40IW_TCP_STATE_CLOSED) ||
	     (original_hw_tcp_state == I40IW_TCP_STATE_TIME_WAIT) ||
	     (last_ae == I40IW_AE_RDMAP_ROE_BAD_LLP_CLOSE) ||
	     (last_ae == I40IW_AE_LLP_CONNECTION_RESET) ||
	      iwdev->reset)) अणु
		issue_बंद = 1;
		iwqp->cm_id = शून्य;
		अगर (!iwqp->flush_issued) अणु
			iwqp->flush_issued = 1;
			issue_flush = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&iwqp->lock, flags);
	अगर (issue_flush && !iwqp->destroyed) अणु
		/* Flush the queues */
		i40iw_flush_wqes(iwdev, iwqp);

		अगर (qp->term_flags && iwqp->ibqp.event_handler) अणु
			ibevent.device = iwqp->ibqp.device;
			ibevent.event = (qp->eventtype == TERM_EVENT_QP_FATAL) ?
					IB_EVENT_QP_FATAL : IB_EVENT_QP_ACCESS_ERR;
			ibevent.element.qp = &iwqp->ibqp;
			iwqp->ibqp.event_handler(&ibevent, iwqp->ibqp.qp_context);
		पूर्ण
	पूर्ण

	अगर (cm_id && cm_id->event_handler) अणु
		अगर (issue_disconn) अणु
			ret = i40iw_send_cm_event(शून्य,
						  cm_id,
						  IW_CM_EVENT_DISCONNECT,
						  disconn_status);

			अगर (ret)
				i40iw_debug(&iwdev->sc_dev,
					    I40IW_DEBUG_CM,
					    "disconnect event failed %s: - cm_id = %p\n",
					    __func__, cm_id);
		पूर्ण
		अगर (issue_बंद) अणु
			i40iw_qp_disconnect(iwqp);
			cm_id->provider_data = iwqp;
			ret = i40iw_send_cm_event(शून्य, cm_id, IW_CM_EVENT_CLOSE, 0);
			अगर (ret)
				i40iw_debug(&iwdev->sc_dev,
					    I40IW_DEBUG_CM,
					    "close event failed %s: - cm_id = %p\n",
					    __func__, cm_id);
			cm_id->rem_ref(cm_id);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40iw_disconnect_worker - worker क्रम connection बंद
 * @work: poपूर्णांकs or disconn काष्ठाure
 */
अटल व्योम i40iw_disconnect_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा disconn_work *dwork = container_of(work, काष्ठा disconn_work, work);
	काष्ठा i40iw_qp *iwqp = dwork->iwqp;

	kमुक्त(dwork);
	i40iw_cm_disconn_true(iwqp);
	i40iw_qp_rem_ref(&iwqp->ibqp);
पूर्ण

/**
 * i40iw_accept - रेजिस्टरed call क्रम connection to be accepted
 * @cm_id: cm inक्रमmation क्रम passive connection
 * @conn_param: accpet parameters
 */
पूर्णांक i40iw_accept(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param)
अणु
	काष्ठा ib_qp *ibqp;
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_cm_core *cm_core;
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा ib_qp_attr attr;
	पूर्णांक passive_state;
	काष्ठा ib_mr *ibmr;
	काष्ठा i40iw_pd *iwpd;
	u16 buf_len = 0;
	काष्ठा i40iw_kmem_info accept;
	क्रमागत i40iw_status_code status;
	u64 tagged_offset;
	अचिन्हित दीर्घ flags;

	स_रखो(&attr, 0, माप(attr));
	ibqp = i40iw_get_qp(cm_id->device, conn_param->qpn);
	अगर (!ibqp)
		वापस -EINVAL;

	iwqp = to_iwqp(ibqp);
	iwdev = iwqp->iwdev;
	dev = &iwdev->sc_dev;
	cm_core = &iwdev->cm_core;
	cm_node = (काष्ठा i40iw_cm_node *)cm_id->provider_data;

	अगर (((काष्ठा sockaddr_in *)&cm_id->local_addr)->sin_family == AF_INET) अणु
		cm_node->ipv4 = true;
		cm_node->vlan_id = i40iw_get_vlan_ipv4(cm_node->loc_addr);
	पूर्ण अन्यथा अणु
		cm_node->ipv4 = false;
		i40iw_netdev_vlan_ipv6(cm_node->loc_addr, &cm_node->vlan_id);
	पूर्ण
	i40iw_debug(cm_node->dev,
		    I40IW_DEBUG_CM,
		    "Accept vlan_id=%d\n",
		    cm_node->vlan_id);
	अगर (cm_node->state == I40IW_CM_STATE_LISTENER_DESTROYED) अणु
		अगर (cm_node->loopbackpartner)
			i40iw_rem_ref_cm_node(cm_node->loopbackpartner);
		i40iw_rem_ref_cm_node(cm_node);
		वापस -EINVAL;
	पूर्ण

	passive_state = atomic_inc_वापस(&cm_node->passive_state);
	अगर (passive_state == I40IW_SEND_RESET_EVENT) अणु
		i40iw_rem_ref_cm_node(cm_node);
		वापस -ECONNRESET;
	पूर्ण

	cm_node->cm_core->stats_accepts++;
	iwqp->cm_node = (व्योम *)cm_node;
	cm_node->iwqp = iwqp;

	buf_len = conn_param->निजी_data_len + I40IW_MAX_IETF_SIZE;

	status = i40iw_allocate_dma_mem(dev->hw, &iwqp->ietf_mem, buf_len, 1);

	अगर (status)
		वापस -ENOMEM;
	cm_node->pdata.size = conn_param->निजी_data_len;
	accept.addr = iwqp->ietf_mem.va;
	accept.size = i40iw_cm_build_mpa_frame(cm_node, &accept, MPA_KEY_REPLY);
	स_नकल(accept.addr + accept.size, conn_param->निजी_data,
	       conn_param->निजी_data_len);

	/* setup our first outgoing iWarp send WQE (the IETF frame response) */
	अगर ((cm_node->ipv4 &&
	     !i40iw_ipv4_is_loopback(cm_node->loc_addr[0], cm_node->rem_addr[0])) ||
	    (!cm_node->ipv4 &&
	     !i40iw_ipv6_is_loopback(cm_node->loc_addr, cm_node->rem_addr))) अणु
		iwpd = iwqp->iwpd;
		tagged_offset = (uपूर्णांकptr_t)iwqp->ietf_mem.va;
		ibmr = i40iw_reg_phys_mr(&iwpd->ibpd,
					 iwqp->ietf_mem.pa,
					 buf_len,
					 IB_ACCESS_LOCAL_WRITE,
					 &tagged_offset);
		अगर (IS_ERR(ibmr)) अणु
			i40iw_मुक्त_dma_mem(dev->hw, &iwqp->ietf_mem);
			वापस -ENOMEM;
		पूर्ण

		ibmr->pd = &iwpd->ibpd;
		ibmr->device = iwpd->ibpd.device;
		iwqp->lsmm_mr = ibmr;
		अगर (iwqp->page)
			iwqp->sc_qp.qp_uk.sq_base = kmap(iwqp->page);
		dev->iw_priv_qp_ops->qp_send_lsmm(&iwqp->sc_qp,
							iwqp->ietf_mem.va,
							(accept.size + conn_param->निजी_data_len),
							ibmr->lkey);

	पूर्ण अन्यथा अणु
		अगर (iwqp->page)
			iwqp->sc_qp.qp_uk.sq_base = kmap(iwqp->page);
		dev->iw_priv_qp_ops->qp_send_lsmm(&iwqp->sc_qp, शून्य, 0, 0);
	पूर्ण

	अगर (iwqp->page)
		kunmap(iwqp->page);

	iwqp->cm_id = cm_id;
	cm_node->cm_id = cm_id;

	cm_id->provider_data = (व्योम *)iwqp;
	iwqp->active_conn = 0;

	cm_node->lsmm_size = accept.size + conn_param->निजी_data_len;
	i40iw_cm_init_tsa_conn(iwqp, cm_node);
	cm_id->add_ref(cm_id);
	i40iw_qp_add_ref(&iwqp->ibqp);

	attr.qp_state = IB_QPS_RTS;
	cm_node->qhash_set = false;
	i40iw_modअगरy_qp(&iwqp->ibqp, &attr, IB_QP_STATE, शून्य);

	cm_node->accelerated = true;
	spin_lock_irqsave(&cm_core->ht_lock, flags);
	list_move_tail(&cm_node->list, &cm_core->accelerated_list);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	status =
		i40iw_send_cm_event(cm_node, cm_id, IW_CM_EVENT_ESTABLISHED, 0);
	अगर (status)
		i40iw_debug(dev, I40IW_DEBUG_CM, "error sending cm event - ESTABLISHED\n");

	अगर (cm_node->loopbackpartner) अणु
		cm_node->loopbackpartner->pdata.size = conn_param->निजी_data_len;

		/* copy entire MPA frame to our cm_node's frame */
		स_नकल(cm_node->loopbackpartner->pdata_buf,
		       conn_param->निजी_data,
		       conn_param->निजी_data_len);
		i40iw_create_event(cm_node->loopbackpartner, I40IW_CM_EVENT_CONNECTED);
	पूर्ण

	अगर (cm_node->accept_pend) अणु
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
		cm_node->accept_pend = 0;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40iw_reject - रेजिस्टरed call क्रम connection to be rejected
 * @cm_id: cm inक्रमmation क्रम passive connection
 * @pdata: निजी data to be sent
 * @pdata_len: निजी data length
 */
पूर्णांक i40iw_reject(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *pdata, u8 pdata_len)
अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा i40iw_cm_node *loopback;

	cm_node = (काष्ठा i40iw_cm_node *)cm_id->provider_data;
	loopback = cm_node->loopbackpartner;
	cm_node->cm_id = cm_id;
	cm_node->pdata.size = pdata_len;

	iwdev = to_iwdev(cm_id->device);
	अगर (!iwdev)
		वापस -EINVAL;
	cm_node->cm_core->stats_rejects++;

	अगर (pdata_len + माप(काष्ठा ietf_mpa_v2) > MAX_CM_BUFFER)
		वापस -EINVAL;

	अगर (loopback) अणु
		स_नकल(&loopback->pdata_buf, pdata, pdata_len);
		loopback->pdata.size = pdata_len;
	पूर्ण

	वापस i40iw_cm_reject(cm_node, pdata, pdata_len);
पूर्ण

/**
 * i40iw_connect - रेजिस्टरed call क्रम connection to be established
 * @cm_id: cm inक्रमmation क्रम passive connection
 * @conn_param: Inक्रमmation about the connection
 */
पूर्णांक i40iw_connect(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param)
अणु
	काष्ठा ib_qp *ibqp;
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा i40iw_cm_info cm_info;
	काष्ठा sockaddr_in *laddr;
	काष्ठा sockaddr_in *raddr;
	काष्ठा sockaddr_in6 *laddr6;
	काष्ठा sockaddr_in6 *raddr6;
	पूर्णांक ret = 0;

	ibqp = i40iw_get_qp(cm_id->device, conn_param->qpn);
	अगर (!ibqp)
		वापस -EINVAL;
	iwqp = to_iwqp(ibqp);
	अगर (!iwqp)
		वापस -EINVAL;
	iwdev = to_iwdev(iwqp->ibqp.device);
	अगर (!iwdev)
		वापस -EINVAL;

	laddr = (काष्ठा sockaddr_in *)&cm_id->m_local_addr;
	raddr = (काष्ठा sockaddr_in *)&cm_id->m_remote_addr;
	laddr6 = (काष्ठा sockaddr_in6 *)&cm_id->m_local_addr;
	raddr6 = (काष्ठा sockaddr_in6 *)&cm_id->m_remote_addr;

	अगर (!(laddr->sin_port) || !(raddr->sin_port))
		वापस -EINVAL;

	iwqp->active_conn = 1;
	iwqp->cm_id = शून्य;
	cm_id->provider_data = iwqp;

	/* set up the connection params क्रम the node */
	अगर (cm_id->remote_addr.ss_family == AF_INET) अणु
		cm_info.ipv4 = true;
		स_रखो(cm_info.loc_addr, 0, माप(cm_info.loc_addr));
		स_रखो(cm_info.rem_addr, 0, माप(cm_info.rem_addr));
		cm_info.loc_addr[0] = ntohl(laddr->sin_addr.s_addr);
		cm_info.rem_addr[0] = ntohl(raddr->sin_addr.s_addr);
		cm_info.loc_port = ntohs(laddr->sin_port);
		cm_info.rem_port = ntohs(raddr->sin_port);
		cm_info.vlan_id = i40iw_get_vlan_ipv4(cm_info.loc_addr);
	पूर्ण अन्यथा अणु
		cm_info.ipv4 = false;
		i40iw_copy_ip_ntohl(cm_info.loc_addr,
				    laddr6->sin6_addr.in6_u.u6_addr32);
		i40iw_copy_ip_ntohl(cm_info.rem_addr,
				    raddr6->sin6_addr.in6_u.u6_addr32);
		cm_info.loc_port = ntohs(laddr6->sin6_port);
		cm_info.rem_port = ntohs(raddr6->sin6_port);
		i40iw_netdev_vlan_ipv6(cm_info.loc_addr, &cm_info.vlan_id);
	पूर्ण
	cm_info.cm_id = cm_id;
	cm_info.tos = cm_id->tos;
	cm_info.user_pri = rt_tos2priority(cm_id->tos);
	i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_DCB, "%s TOS:[%d] UP:[%d]\n",
		    __func__, cm_id->tos, cm_info.user_pri);
	cm_id->add_ref(cm_id);
	cm_node = i40iw_create_cm_node(&iwdev->cm_core, iwdev,
				       conn_param, &cm_info);

	अगर (IS_ERR(cm_node)) अणु
		ret = PTR_ERR(cm_node);
		cm_id->rem_ref(cm_id);
		वापस ret;
	पूर्ण

	अगर ((cm_info.ipv4 && (laddr->sin_addr.s_addr != raddr->sin_addr.s_addr)) ||
	    (!cm_info.ipv4 && स_भेद(laddr6->sin6_addr.in6_u.u6_addr32,
				     raddr6->sin6_addr.in6_u.u6_addr32,
				     माप(laddr6->sin6_addr.in6_u.u6_addr32)))) अणु
		अगर (i40iw_manage_qhash(iwdev, &cm_info, I40IW_QHASH_TYPE_TCP_ESTABLISHED,
				       I40IW_QHASH_MANAGE_TYPE_ADD, शून्य, true)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		cm_node->qhash_set = true;
	पूर्ण

	अगर (i40iw_manage_apbvt(iwdev, cm_info.loc_port,
			       I40IW_MANAGE_APBVT_ADD)) अणु
		ret =  -EINVAL;
		जाओ err;
	पूर्ण

	cm_node->apbvt_set = true;
	iwqp->cm_node = cm_node;
	cm_node->iwqp = iwqp;
	iwqp->cm_id = cm_id;
	i40iw_qp_add_ref(&iwqp->ibqp);

	अगर (cm_node->state != I40IW_CM_STATE_OFFLOADED) अणु
		cm_node->state = I40IW_CM_STATE_SYN_SENT;
		ret = i40iw_send_syn(cm_node, 0);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (cm_node->loopbackpartner) अणु
		cm_node->loopbackpartner->state = I40IW_CM_STATE_MPAREQ_RCVD;
		i40iw_create_event(cm_node->loopbackpartner,
				   I40IW_CM_EVENT_MPA_REQ);
	पूर्ण

	i40iw_debug(cm_node->dev,
		    I40IW_DEBUG_CM,
		    "Api - connect(): port=0x%04x, cm_node=%p, cm_id = %p.\n",
		    cm_node->rem_port,
		    cm_node,
		    cm_node->cm_id);

	वापस 0;

err:
	अगर (cm_info.ipv4)
		i40iw_debug(&iwdev->sc_dev,
			    I40IW_DEBUG_CM,
			    "Api - connect() FAILED: dest addr=%pI4",
			    cm_info.rem_addr);
	अन्यथा
		i40iw_debug(&iwdev->sc_dev,
			    I40IW_DEBUG_CM,
			    "Api - connect() FAILED: dest addr=%pI6",
			    cm_info.rem_addr);

	i40iw_rem_ref_cm_node(cm_node);
	cm_id->rem_ref(cm_id);
	iwdev->cm_core.stats_connect_errs++;
	वापस ret;
पूर्ण

/**
 * i40iw_create_listen - रेजिस्टरed call creating listener
 * @cm_id: cm inक्रमmation क्रम passive connection
 * @backlog: to max accept pending count
 */
पूर्णांक i40iw_create_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog)
अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_cm_listener *cm_listen_node;
	काष्ठा i40iw_cm_info cm_info;
	क्रमागत i40iw_status_code ret;
	काष्ठा sockaddr_in *laddr;
	काष्ठा sockaddr_in6 *laddr6;
	bool wildcard = false;

	iwdev = to_iwdev(cm_id->device);
	अगर (!iwdev)
		वापस -EINVAL;

	laddr = (काष्ठा sockaddr_in *)&cm_id->m_local_addr;
	laddr6 = (काष्ठा sockaddr_in6 *)&cm_id->m_local_addr;
	स_रखो(&cm_info, 0, माप(cm_info));
	अगर (laddr->sin_family == AF_INET) अणु
		cm_info.ipv4 = true;
		cm_info.loc_addr[0] = ntohl(laddr->sin_addr.s_addr);
		cm_info.loc_port = ntohs(laddr->sin_port);

		अगर (laddr->sin_addr.s_addr != INADDR_ANY)
			cm_info.vlan_id = i40iw_get_vlan_ipv4(cm_info.loc_addr);
		अन्यथा
			wildcard = true;

	पूर्ण अन्यथा अणु
		cm_info.ipv4 = false;
		i40iw_copy_ip_ntohl(cm_info.loc_addr,
				    laddr6->sin6_addr.in6_u.u6_addr32);
		cm_info.loc_port = ntohs(laddr6->sin6_port);
		अगर (ipv6_addr_type(&laddr6->sin6_addr) != IPV6_ADDR_ANY)
			i40iw_netdev_vlan_ipv6(cm_info.loc_addr,
					       &cm_info.vlan_id);
		अन्यथा
			wildcard = true;
	पूर्ण
	cm_info.backlog = backlog;
	cm_info.cm_id = cm_id;

	cm_listen_node = i40iw_make_listen_node(&iwdev->cm_core, iwdev, &cm_info);
	अगर (!cm_listen_node) अणु
		i40iw_pr_err("cm_listen_node == NULL\n");
		वापस -ENOMEM;
	पूर्ण

	cm_id->provider_data = cm_listen_node;

	cm_listen_node->tos = cm_id->tos;
	cm_listen_node->user_pri = rt_tos2priority(cm_id->tos);
	cm_info.user_pri = cm_listen_node->user_pri;

	अगर (!cm_listen_node->reused_node) अणु
		अगर (wildcard) अणु
			अगर (cm_info.ipv4)
				ret = i40iw_add_mqh_4(iwdev,
						      &cm_info,
						      cm_listen_node);
			अन्यथा
				ret = i40iw_add_mqh_6(iwdev,
						      &cm_info,
						      cm_listen_node);
			अगर (ret)
				जाओ error;

			ret = i40iw_manage_apbvt(iwdev,
						 cm_info.loc_port,
						 I40IW_MANAGE_APBVT_ADD);

			अगर (ret)
				जाओ error;
		पूर्ण अन्यथा अणु
			ret = i40iw_manage_qhash(iwdev,
						 &cm_info,
						 I40IW_QHASH_TYPE_TCP_SYN,
						 I40IW_QHASH_MANAGE_TYPE_ADD,
						 शून्य,
						 true);
			अगर (ret)
				जाओ error;
			cm_listen_node->qhash_set = true;
			ret = i40iw_manage_apbvt(iwdev,
						 cm_info.loc_port,
						 I40IW_MANAGE_APBVT_ADD);
			अगर (ret)
				जाओ error;
		पूर्ण
	पूर्ण
	cm_id->add_ref(cm_id);
	cm_listen_node->cm_core->stats_listen_created++;
	वापस 0;
 error:
	i40iw_cm_del_listen(&iwdev->cm_core, (व्योम *)cm_listen_node, false);
	वापस -EINVAL;
पूर्ण

/**
 * i40iw_destroy_listen - रेजिस्टरed call to destroy listener
 * @cm_id: cm inक्रमmation क्रम passive connection
 */
पूर्णांक i40iw_destroy_listen(काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा i40iw_device *iwdev;

	iwdev = to_iwdev(cm_id->device);
	अगर (cm_id->provider_data)
		i40iw_cm_del_listen(&iwdev->cm_core, cm_id->provider_data, true);
	अन्यथा
		i40iw_pr_err("cm_id->provider_data was NULL\n");

	cm_id->rem_ref(cm_id);

	वापस 0;
पूर्ण

/**
 * i40iw_cm_event_connected - handle connected active node
 * @event: the info क्रम cm_node of connection
 */
अटल व्योम i40iw_cm_event_connected(काष्ठा i40iw_cm_event *event)
अणु
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_cm_core *cm_core;
	काष्ठा i40iw_cm_node *cm_node;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा ib_qp_attr attr;
	काष्ठा iw_cm_id *cm_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	bool पढ़ो0;

	cm_node = event->cm_node;
	cm_id = cm_node->cm_id;
	iwqp = (काष्ठा i40iw_qp *)cm_id->provider_data;
	iwdev = to_iwdev(iwqp->ibqp.device);
	dev = &iwdev->sc_dev;
	cm_core = &iwdev->cm_core;

	अगर (iwqp->destroyed) अणु
		status = -ETIMEDOUT;
		जाओ error;
	पूर्ण
	i40iw_cm_init_tsa_conn(iwqp, cm_node);
	पढ़ो0 = (cm_node->send_rdma0_op == SEND_RDMA_READ_ZERO);
	अगर (iwqp->page)
		iwqp->sc_qp.qp_uk.sq_base = kmap(iwqp->page);
	dev->iw_priv_qp_ops->qp_send_rtt(&iwqp->sc_qp, पढ़ो0);
	अगर (iwqp->page)
		kunmap(iwqp->page);

	स_रखो(&attr, 0, माप(attr));
	attr.qp_state = IB_QPS_RTS;
	cm_node->qhash_set = false;
	i40iw_modअगरy_qp(&iwqp->ibqp, &attr, IB_QP_STATE, शून्य);

	cm_node->accelerated = true;
	spin_lock_irqsave(&cm_core->ht_lock, flags);
	list_move_tail(&cm_node->list, &cm_core->accelerated_list);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);
	status = i40iw_send_cm_event(cm_node, cm_id, IW_CM_EVENT_CONNECT_REPLY,
				     0);
	अगर (status)
		i40iw_debug(dev, I40IW_DEBUG_CM, "error sending cm event - CONNECT_REPLY\n");

	वापस;

error:
	iwqp->cm_id = शून्य;
	cm_id->provider_data = शून्य;
	i40iw_send_cm_event(event->cm_node,
			    cm_id,
			    IW_CM_EVENT_CONNECT_REPLY,
			    status);
	cm_id->rem_ref(cm_id);
	i40iw_rem_ref_cm_node(event->cm_node);
पूर्ण

/**
 * i40iw_cm_event_reset - handle reset
 * @event: the info क्रम cm_node of connection
 */
अटल व्योम i40iw_cm_event_reset(काष्ठा i40iw_cm_event *event)
अणु
	काष्ठा i40iw_cm_node *cm_node = event->cm_node;
	काष्ठा iw_cm_id   *cm_id = cm_node->cm_id;
	काष्ठा i40iw_qp *iwqp;

	अगर (!cm_id)
		वापस;

	iwqp = cm_id->provider_data;
	अगर (!iwqp)
		वापस;

	i40iw_debug(cm_node->dev,
		    I40IW_DEBUG_CM,
		    "reset event %p - cm_id = %p\n",
		     event->cm_node, cm_id);
	iwqp->cm_id = शून्य;

	i40iw_send_cm_event(cm_node, cm_node->cm_id, IW_CM_EVENT_DISCONNECT, -ECONNRESET);
	i40iw_send_cm_event(cm_node, cm_node->cm_id, IW_CM_EVENT_CLOSE, 0);
पूर्ण

/**
 * i40iw_cm_event_handler - worker thपढ़ो callback to send event to cm upper layer
 * @work: poपूर्णांकer of cm event info.
 */
अटल व्योम i40iw_cm_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i40iw_cm_event *event = container_of(work,
						    काष्ठा i40iw_cm_event,
						    event_work);
	काष्ठा i40iw_cm_node *cm_node;

	अगर (!event || !event->cm_node || !event->cm_node->cm_core)
		वापस;

	cm_node = event->cm_node;

	चयन (event->type) अणु
	हाल I40IW_CM_EVENT_MPA_REQ:
		i40iw_send_cm_event(cm_node,
				    cm_node->cm_id,
				    IW_CM_EVENT_CONNECT_REQUEST,
				    0);
		अवरोध;
	हाल I40IW_CM_EVENT_RESET:
		i40iw_cm_event_reset(event);
		अवरोध;
	हाल I40IW_CM_EVENT_CONNECTED:
		अगर (!event->cm_node->cm_id ||
		    (event->cm_node->state != I40IW_CM_STATE_OFFLOADED))
			अवरोध;
		i40iw_cm_event_connected(event);
		अवरोध;
	हाल I40IW_CM_EVENT_MPA_REJECT:
		अगर (!event->cm_node->cm_id ||
		    (cm_node->state == I40IW_CM_STATE_OFFLOADED))
			अवरोध;
		i40iw_send_cm_event(cm_node,
				    cm_node->cm_id,
				    IW_CM_EVENT_CONNECT_REPLY,
				    -ECONNREFUSED);
		अवरोध;
	हाल I40IW_CM_EVENT_ABORTED:
		अगर (!event->cm_node->cm_id ||
		    (event->cm_node->state == I40IW_CM_STATE_OFFLOADED))
			अवरोध;
		i40iw_event_connect_error(event);
		अवरोध;
	शेष:
		i40iw_pr_err("event type = %d\n", event->type);
		अवरोध;
	पूर्ण

	event->cm_info.cm_id->rem_ref(event->cm_info.cm_id);
	i40iw_rem_ref_cm_node(event->cm_node);
	kमुक्त(event);
पूर्ण

/**
 * i40iw_cm_post_event - queue event request क्रम worker thपढ़ो
 * @event: cm node's info क्रम up event call
 */
अटल व्योम i40iw_cm_post_event(काष्ठा i40iw_cm_event *event)
अणु
	atomic_inc(&event->cm_node->ref_count);
	event->cm_info.cm_id->add_ref(event->cm_info.cm_id);
	INIT_WORK(&event->event_work, i40iw_cm_event_handler);

	queue_work(event->cm_node->cm_core->event_wq, &event->event_work);
पूर्ण

/**
 * i40iw_qhash_ctrl - enable/disable qhash क्रम list
 * @iwdev: device poपूर्णांकer
 * @parent_listen_node: parent listen node
 * @nfo: cm info node
 * @ipaddr: Poपूर्णांकer to IPv4 or IPv6 address
 * @ipv4: flag indicating IPv4 when true
 * @अगरup: flag indicating पूर्णांकerface up when true
 *
 * Enables or disables the qhash क्रम the node in the child
 * listen list that matches ipaddr. If no matching IP was found
 * it will allocate and add a new child listen node to the
 * parent listen node. The listen_list_lock is assumed to be
 * held when called.
 */
अटल व्योम i40iw_qhash_ctrl(काष्ठा i40iw_device *iwdev,
			     काष्ठा i40iw_cm_listener *parent_listen_node,
			     काष्ठा i40iw_cm_info *nfo,
			     u32 *ipaddr, bool ipv4, bool अगरup)
अणु
	काष्ठा list_head *child_listen_list = &parent_listen_node->child_listen_list;
	काष्ठा i40iw_cm_listener *child_listen_node;
	काष्ठा list_head *pos, *tpos;
	क्रमागत i40iw_status_code ret;
	bool node_allocated = false;
	क्रमागत i40iw_quad_hash_manage_type op =
		अगरup ? I40IW_QHASH_MANAGE_TYPE_ADD : I40IW_QHASH_MANAGE_TYPE_DELETE;

	list_क्रम_each_safe(pos, tpos, child_listen_list) अणु
		child_listen_node =
			list_entry(pos,
				   काष्ठा i40iw_cm_listener,
				   child_listen_list);
		अगर (!स_भेद(child_listen_node->loc_addr, ipaddr, ipv4 ? 4 : 16))
			जाओ set_qhash;
	पूर्ण

	/* अगर not found then add a child listener अगर पूर्णांकerface is going up */
	अगर (!अगरup)
		वापस;
	child_listen_node = kmemdup(parent_listen_node,
			माप(*child_listen_node), GFP_ATOMIC);
	अगर (!child_listen_node)
		वापस;
	node_allocated = true;

	स_नकल(child_listen_node->loc_addr, ipaddr,  ipv4 ? 4 : 16);

set_qhash:
	स_नकल(nfo->loc_addr,
	       child_listen_node->loc_addr,
	       माप(nfo->loc_addr));
	nfo->vlan_id = child_listen_node->vlan_id;
	ret = i40iw_manage_qhash(iwdev, nfo,
				 I40IW_QHASH_TYPE_TCP_SYN,
				 op,
				 शून्य, false);
	अगर (!ret) अणु
		child_listen_node->qhash_set = अगरup;
		अगर (node_allocated)
			list_add(&child_listen_node->child_listen_list,
				 &parent_listen_node->child_listen_list);
	पूर्ण अन्यथा अगर (node_allocated) अणु
		kमुक्त(child_listen_node);
	पूर्ण
पूर्ण

/**
 * i40iw_cm_tearकरोwn_connections - tearकरोwn QPs
 * @iwdev: device poपूर्णांकer
 * @ipaddr: Poपूर्णांकer to IPv4 or IPv6 address
 * @nfo: cm info node
 * @disconnect_all: flag indicating disconnect all QPs
 * tearकरोwn QPs where source or destination addr matches ip addr
 */
व्योम i40iw_cm_tearकरोwn_connections(काष्ठा i40iw_device *iwdev, u32 *ipaddr,
				   काष्ठा i40iw_cm_info *nfo,
				   bool disconnect_all)
अणु
	काष्ठा i40iw_cm_core *cm_core = &iwdev->cm_core;
	काष्ठा list_head *list_core_temp;
	काष्ठा list_head *list_node;
	काष्ठा i40iw_cm_node *cm_node;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head tearकरोwn_list;
	काष्ठा ib_qp_attr attr;

	INIT_LIST_HEAD(&tearकरोwn_list);
	spin_lock_irqsave(&cm_core->ht_lock, flags);
	list_क्रम_each_safe(list_node, list_core_temp,
			   &cm_core->accelerated_list) अणु
		cm_node = container_of(list_node, काष्ठा i40iw_cm_node, list);
		अगर (disconnect_all ||
		    (nfo->vlan_id == cm_node->vlan_id &&
		    (!स_भेद(cm_node->loc_addr, ipaddr, nfo->ipv4 ? 4 : 16) ||
		     !स_भेद(cm_node->rem_addr, ipaddr, nfo->ipv4 ? 4 : 16)))) अणु
			atomic_inc(&cm_node->ref_count);
			list_add(&cm_node->tearकरोwn_entry, &tearकरोwn_list);
		पूर्ण
	पूर्ण
	list_क्रम_each_safe(list_node, list_core_temp,
			   &cm_core->non_accelerated_list) अणु
		cm_node = container_of(list_node, काष्ठा i40iw_cm_node, list);
		अगर (disconnect_all ||
		    (nfo->vlan_id == cm_node->vlan_id &&
		    (!स_भेद(cm_node->loc_addr, ipaddr, nfo->ipv4 ? 4 : 16) ||
		     !स_भेद(cm_node->rem_addr, ipaddr, nfo->ipv4 ? 4 : 16)))) अणु
			atomic_inc(&cm_node->ref_count);
			list_add(&cm_node->tearकरोwn_entry, &tearकरोwn_list);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	list_क्रम_each_safe(list_node, list_core_temp, &tearकरोwn_list) अणु
		cm_node = container_of(list_node, काष्ठा i40iw_cm_node,
				       tearकरोwn_entry);
		attr.qp_state = IB_QPS_ERR;
		i40iw_modअगरy_qp(&cm_node->iwqp->ibqp, &attr, IB_QP_STATE, शून्य);
		अगर (iwdev->reset)
			i40iw_cm_disconn(cm_node->iwqp);
		i40iw_rem_ref_cm_node(cm_node);
	पूर्ण
पूर्ण

/**
 * i40iw_अगर_notअगरy - process an अगरकरोwn on an पूर्णांकerface
 * @iwdev: device poपूर्णांकer
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ipaddr: Poपूर्णांकer to IPv4 or IPv6 address
 * @ipv4: flag indicating IPv4 when true
 * @अगरup: flag indicating पूर्णांकerface up when true
 */
व्योम i40iw_अगर_notअगरy(काष्ठा i40iw_device *iwdev, काष्ठा net_device *netdev,
		     u32 *ipaddr, bool ipv4, bool अगरup)
अणु
	काष्ठा i40iw_cm_core *cm_core = &iwdev->cm_core;
	अचिन्हित दीर्घ flags;
	काष्ठा i40iw_cm_listener *listen_node;
	अटल स्थिर u32 ip_zero[4] = अणु 0, 0, 0, 0 पूर्ण;
	काष्ठा i40iw_cm_info nfo;
	u16 vlan_id = rdma_vlan_dev_vlan_id(netdev);
	क्रमागत i40iw_status_code ret;
	क्रमागत i40iw_quad_hash_manage_type op =
		अगरup ? I40IW_QHASH_MANAGE_TYPE_ADD : I40IW_QHASH_MANAGE_TYPE_DELETE;

	nfo.vlan_id = vlan_id;
	nfo.ipv4 = ipv4;

	/* Disable or enable qhash क्रम listeners */
	spin_lock_irqsave(&cm_core->listen_list_lock, flags);
	list_क्रम_each_entry(listen_node, &cm_core->listen_nodes, list) अणु
		अगर (vlan_id == listen_node->vlan_id &&
		    (!स_भेद(listen_node->loc_addr, ipaddr, ipv4 ? 4 : 16) ||
		    !स_भेद(listen_node->loc_addr, ip_zero, ipv4 ? 4 : 16))) अणु
			स_नकल(nfo.loc_addr, listen_node->loc_addr,
			       माप(nfo.loc_addr));
			nfo.loc_port = listen_node->loc_port;
			nfo.user_pri = listen_node->user_pri;
			अगर (!list_empty(&listen_node->child_listen_list)) अणु
				i40iw_qhash_ctrl(iwdev,
						 listen_node,
						 &nfo,
						 ipaddr, ipv4, अगरup);
			पूर्ण अन्यथा अगर (स_भेद(listen_node->loc_addr, ip_zero,
					  ipv4 ? 4 : 16)) अणु
				ret = i40iw_manage_qhash(iwdev,
							 &nfo,
							 I40IW_QHASH_TYPE_TCP_SYN,
							 op,
							 शून्य,
							 false);
				अगर (!ret)
					listen_node->qhash_set = अगरup;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cm_core->listen_list_lock, flags);

	/* tearकरोwn connected qp's on अगरकरोwn */
	अगर (!अगरup)
		i40iw_cm_tearकरोwn_connections(iwdev, ipaddr, &nfo, false);
पूर्ण
