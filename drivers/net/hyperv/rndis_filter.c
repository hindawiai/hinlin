<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 */
#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/nls.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/ucs2_माला.स>

#समावेश "hyperv_net.h"
#समावेश "netvsc_trace.h"

अटल व्योम rndis_set_multicast(काष्ठा work_काष्ठा *w);

#घोषणा RNDIS_EXT_LEN HV_HYP_PAGE_SIZE
काष्ठा rndis_request अणु
	काष्ठा list_head list_ent;
	काष्ठा completion  रुको_event;

	काष्ठा rndis_message response_msg;
	/*
	 * The buffer क्रम extended info after the RNDIS response message. It's
	 * referenced based on the data offset in the RNDIS message. Its size
	 * is enough क्रम current needs, and should be sufficient क्रम the near
	 * future.
	 */
	u8 response_ext[RNDIS_EXT_LEN];

	/* Simplअगरy allocation by having a netvsc packet अंतरभूत */
	काष्ठा hv_netvsc_packet	pkt;

	काष्ठा rndis_message request_msg;
	/*
	 * The buffer क्रम the extended info after the RNDIS request message.
	 * It is referenced and sized in a similar way as response_ext.
	 */
	u8 request_ext[RNDIS_EXT_LEN];
पूर्ण;

अटल स्थिर u8 netvsc_hash_key[NETVSC_HASH_KEYLEN] = अणु
	0x6d, 0x5a, 0x56, 0xda, 0x25, 0x5b, 0x0e, 0xc2,
	0x41, 0x67, 0x25, 0x3d, 0x43, 0xa3, 0x8f, 0xb0,
	0xd0, 0xca, 0x2b, 0xcb, 0xae, 0x7b, 0x30, 0xb4,
	0x77, 0xcb, 0x2d, 0xa3, 0x80, 0x30, 0xf2, 0x0c,
	0x6a, 0x42, 0xb7, 0x3b, 0xbe, 0xac, 0x01, 0xfa
पूर्ण;

अटल काष्ठा rndis_device *get_rndis_device(व्योम)
अणु
	काष्ठा rndis_device *device;

	device = kzalloc(माप(काष्ठा rndis_device), GFP_KERNEL);
	अगर (!device)
		वापस शून्य;

	spin_lock_init(&device->request_lock);

	INIT_LIST_HEAD(&device->req_list);
	INIT_WORK(&device->mcast_work, rndis_set_multicast);

	device->state = RNDIS_DEV_UNINITIALIZED;

	वापस device;
पूर्ण

अटल काष्ठा rndis_request *get_rndis_request(काष्ठा rndis_device *dev,
					     u32 msg_type,
					     u32 msg_len)
अणु
	काष्ठा rndis_request *request;
	काष्ठा rndis_message *rndis_msg;
	काष्ठा rndis_set_request *set;
	अचिन्हित दीर्घ flags;

	request = kzalloc(माप(काष्ठा rndis_request), GFP_KERNEL);
	अगर (!request)
		वापस शून्य;

	init_completion(&request->रुको_event);

	rndis_msg = &request->request_msg;
	rndis_msg->ndis_msg_type = msg_type;
	rndis_msg->msg_len = msg_len;

	request->pkt.q_idx = 0;

	/*
	 * Set the request id. This field is always after the rndis header क्रम
	 * request/response packet types so we just used the SetRequest as a
	 * ढाँचा
	 */
	set = &rndis_msg->msg.set_req;
	set->req_id = atomic_inc_वापस(&dev->new_req_id);

	/* Add to the request list */
	spin_lock_irqsave(&dev->request_lock, flags);
	list_add_tail(&request->list_ent, &dev->req_list);
	spin_unlock_irqrestore(&dev->request_lock, flags);

	वापस request;
पूर्ण

अटल व्योम put_rndis_request(काष्ठा rndis_device *dev,
			    काष्ठा rndis_request *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->request_lock, flags);
	list_del(&req->list_ent);
	spin_unlock_irqrestore(&dev->request_lock, flags);

	kमुक्त(req);
पूर्ण

अटल व्योम dump_rndis_message(काष्ठा net_device *netdev,
			       स्थिर काष्ठा rndis_message *rndis_msg,
			       स्थिर व्योम *data)
अणु
	चयन (rndis_msg->ndis_msg_type) अणु
	हाल RNDIS_MSG_PACKET:
		अगर (rndis_msg->msg_len - RNDIS_HEADER_SIZE >= माप(काष्ठा rndis_packet)) अणु
			स्थिर काष्ठा rndis_packet *pkt = data + RNDIS_HEADER_SIZE;
			netdev_dbg(netdev, "RNDIS_MSG_PACKET (len %u, "
				   "data offset %u data len %u, # oob %u, "
				   "oob offset %u, oob len %u, pkt offset %u, "
				   "pkt len %u\n",
				   rndis_msg->msg_len,
				   pkt->data_offset,
				   pkt->data_len,
				   pkt->num_oob_data_elements,
				   pkt->oob_data_offset,
				   pkt->oob_data_len,
				   pkt->per_pkt_info_offset,
				   pkt->per_pkt_info_len);
		पूर्ण
		अवरोध;

	हाल RNDIS_MSG_INIT_C:
		अगर (rndis_msg->msg_len - RNDIS_HEADER_SIZE >=
				माप(काष्ठा rndis_initialize_complete)) अणु
			स्थिर काष्ठा rndis_initialize_complete *init_complete =
				data + RNDIS_HEADER_SIZE;
			netdev_dbg(netdev, "RNDIS_MSG_INIT_C "
				"(len %u, id 0x%x, status 0x%x, major %d, minor %d, "
				"device flags %d, max xfer size 0x%x, max pkts %u, "
				"pkt aligned %u)\n",
				rndis_msg->msg_len,
				init_complete->req_id,
				init_complete->status,
				init_complete->major_ver,
				init_complete->minor_ver,
				init_complete->dev_flags,
				init_complete->max_xfer_size,
				init_complete->max_pkt_per_msg,
				init_complete->pkt_alignment_factor);
		पूर्ण
		अवरोध;

	हाल RNDIS_MSG_QUERY_C:
		अगर (rndis_msg->msg_len - RNDIS_HEADER_SIZE >=
				माप(काष्ठा rndis_query_complete)) अणु
			स्थिर काष्ठा rndis_query_complete *query_complete =
				data + RNDIS_HEADER_SIZE;
			netdev_dbg(netdev, "RNDIS_MSG_QUERY_C "
				"(len %u, id 0x%x, status 0x%x, buf len %u, "
				"buf offset %u)\n",
				rndis_msg->msg_len,
				query_complete->req_id,
				query_complete->status,
				query_complete->info_buflen,
				query_complete->info_buf_offset);
		पूर्ण
		अवरोध;

	हाल RNDIS_MSG_SET_C:
		अगर (rndis_msg->msg_len - RNDIS_HEADER_SIZE + माप(काष्ठा rndis_set_complete)) अणु
			स्थिर काष्ठा rndis_set_complete *set_complete =
				data + RNDIS_HEADER_SIZE;
			netdev_dbg(netdev,
				"RNDIS_MSG_SET_C (len %u, id 0x%x, status 0x%x)\n",
				rndis_msg->msg_len,
				set_complete->req_id,
				set_complete->status);
		पूर्ण
		अवरोध;

	हाल RNDIS_MSG_INDICATE:
		अगर (rndis_msg->msg_len - RNDIS_HEADER_SIZE >=
				माप(काष्ठा rndis_indicate_status)) अणु
			स्थिर काष्ठा rndis_indicate_status *indicate_status =
				data + RNDIS_HEADER_SIZE;
			netdev_dbg(netdev, "RNDIS_MSG_INDICATE "
				"(len %u, status 0x%x, buf len %u, buf offset %u)\n",
				rndis_msg->msg_len,
				indicate_status->status,
				indicate_status->status_buflen,
				indicate_status->status_buf_offset);
		पूर्ण
		अवरोध;

	शेष:
		netdev_dbg(netdev, "0x%x (len %u)\n",
			rndis_msg->ndis_msg_type,
			rndis_msg->msg_len);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rndis_filter_send_request(काष्ठा rndis_device *dev,
				  काष्ठा rndis_request *req)
अणु
	काष्ठा hv_netvsc_packet *packet;
	काष्ठा hv_page_buffer page_buf[2];
	काष्ठा hv_page_buffer *pb = page_buf;
	पूर्णांक ret;

	/* Setup the packet to send it */
	packet = &req->pkt;

	packet->total_data_buflen = req->request_msg.msg_len;
	packet->page_buf_cnt = 1;

	pb[0].pfn = virt_to_phys(&req->request_msg) >>
					HV_HYP_PAGE_SHIFT;
	pb[0].len = req->request_msg.msg_len;
	pb[0].offset = offset_in_hvpage(&req->request_msg);

	/* Add one page_buf when request_msg crossing page boundary */
	अगर (pb[0].offset + pb[0].len > HV_HYP_PAGE_SIZE) अणु
		packet->page_buf_cnt++;
		pb[0].len = HV_HYP_PAGE_SIZE -
			pb[0].offset;
		pb[1].pfn = virt_to_phys((व्योम *)&req->request_msg
			+ pb[0].len) >> HV_HYP_PAGE_SHIFT;
		pb[1].offset = 0;
		pb[1].len = req->request_msg.msg_len -
			pb[0].len;
	पूर्ण

	trace_rndis_send(dev->ndev, 0, &req->request_msg);

	rcu_पढ़ो_lock_bh();
	ret = netvsc_send(dev->ndev, packet, शून्य, pb, शून्य, false);
	rcu_पढ़ो_unlock_bh();

	वापस ret;
पूर्ण

अटल व्योम rndis_set_link_state(काष्ठा rndis_device *rdev,
				 काष्ठा rndis_request *request)
अणु
	u32 link_status;
	काष्ठा rndis_query_complete *query_complete;
	u32 msg_len = request->response_msg.msg_len;

	/* Ensure the packet is big enough to access its fields */
	अगर (msg_len - RNDIS_HEADER_SIZE < माप(काष्ठा rndis_query_complete))
		वापस;

	query_complete = &request->response_msg.msg.query_complete;

	अगर (query_complete->status == RNDIS_STATUS_SUCCESS &&
	    query_complete->info_buflen >= माप(u32) &&
	    query_complete->info_buf_offset >= माप(*query_complete) &&
	    msg_len - RNDIS_HEADER_SIZE >= query_complete->info_buf_offset &&
	    msg_len - RNDIS_HEADER_SIZE - query_complete->info_buf_offset
			>= query_complete->info_buflen) अणु
		स_नकल(&link_status, (व्योम *)((अचिन्हित दीर्घ)query_complete +
		       query_complete->info_buf_offset), माप(u32));
		rdev->link_state = link_status != 0;
	पूर्ण
पूर्ण

अटल व्योम rndis_filter_receive_response(काष्ठा net_device *ndev,
					  काष्ठा netvsc_device *nvdev,
					  काष्ठा rndis_message *resp,
					  व्योम *data)
अणु
	u32 *req_id = &resp->msg.init_complete.req_id;
	काष्ठा rndis_device *dev = nvdev->extension;
	काष्ठा rndis_request *request = शून्य;
	bool found = false;
	अचिन्हित दीर्घ flags;

	/* This should never happen, it means control message
	 * response received after device हटाओd.
	 */
	अगर (dev->state == RNDIS_DEV_UNINITIALIZED) अणु
		netdev_err(ndev,
			   "got rndis message uninitialized\n");
		वापस;
	पूर्ण

	/* Ensure the packet is big enough to पढ़ो req_id. Req_id is the 1st
	 * field in any request/response message, so the payload should have at
	 * least माप(u32) bytes
	 */
	अगर (resp->msg_len - RNDIS_HEADER_SIZE < माप(u32)) अणु
		netdev_err(ndev, "rndis msg_len too small: %u\n",
			   resp->msg_len);
		वापस;
	पूर्ण

	/* Copy the request ID पूर्णांकo nvchan->recv_buf */
	*req_id = *(u32 *)(data + RNDIS_HEADER_SIZE);

	spin_lock_irqsave(&dev->request_lock, flags);
	list_क्रम_each_entry(request, &dev->req_list, list_ent) अणु
		/*
		 * All request/response message contains RequestId as the 1st
		 * field
		 */
		अगर (request->request_msg.msg.init_req.req_id == *req_id) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->request_lock, flags);

	अगर (found) अणु
		अगर (resp->msg_len <=
		    माप(काष्ठा rndis_message) + RNDIS_EXT_LEN) अणु
			स_नकल(&request->response_msg, resp, RNDIS_HEADER_SIZE + माप(*req_id));
			स_नकल((व्योम *)&request->response_msg + RNDIS_HEADER_SIZE + माप(*req_id),
			       data + RNDIS_HEADER_SIZE + माप(*req_id),
			       resp->msg_len - RNDIS_HEADER_SIZE - माप(*req_id));
			अगर (request->request_msg.ndis_msg_type ==
			    RNDIS_MSG_QUERY && request->request_msg.msg.
			    query_req.oid == RNDIS_OID_GEN_MEDIA_CONNECT_STATUS)
				rndis_set_link_state(dev, request);
		पूर्ण अन्यथा अणु
			netdev_err(ndev,
				"rndis response buffer overflow "
				"detected (size %u max %zu)\n",
				resp->msg_len,
				माप(काष्ठा rndis_message));

			अगर (resp->ndis_msg_type ==
			    RNDIS_MSG_RESET_C) अणु
				/* करोes not have a request id field */
				request->response_msg.msg.reset_complete.
					status = RNDIS_STATUS_BUFFER_OVERFLOW;
			पूर्ण अन्यथा अणु
				request->response_msg.msg.
				init_complete.status =
					RNDIS_STATUS_BUFFER_OVERFLOW;
			पूर्ण
		पूर्ण

		complete(&request->रुको_event);
	पूर्ण अन्यथा अणु
		netdev_err(ndev,
			"no rndis request found for this response "
			"(id 0x%x res type 0x%x)\n",
			*req_id,
			resp->ndis_msg_type);
	पूर्ण
पूर्ण

/*
 * Get the Per-Packet-Info with the specअगरied type
 * वापस शून्य अगर not found.
 */
अटल अंतरभूत व्योम *rndis_get_ppi(काष्ठा net_device *ndev,
				  काष्ठा rndis_packet *rpkt,
				  u32 rpkt_len, u32 type, u8 पूर्णांकernal,
				  u32 ppi_size, व्योम *data)
अणु
	काष्ठा rndis_per_packet_info *ppi;
	पूर्णांक len;

	अगर (rpkt->per_pkt_info_offset == 0)
		वापस शून्य;

	/* Validate info_offset and info_len */
	अगर (rpkt->per_pkt_info_offset < माप(काष्ठा rndis_packet) ||
	    rpkt->per_pkt_info_offset > rpkt_len) अणु
		netdev_err(ndev, "Invalid per_pkt_info_offset: %u\n",
			   rpkt->per_pkt_info_offset);
		वापस शून्य;
	पूर्ण

	अगर (rpkt->per_pkt_info_len < माप(*ppi) ||
	    rpkt->per_pkt_info_len > rpkt_len - rpkt->per_pkt_info_offset) अणु
		netdev_err(ndev, "Invalid per_pkt_info_len: %u\n",
			   rpkt->per_pkt_info_len);
		वापस शून्य;
	पूर्ण

	ppi = (काष्ठा rndis_per_packet_info *)((uदीर्घ)rpkt +
		rpkt->per_pkt_info_offset);
	/* Copy the PPIs पूर्णांकo nvchan->recv_buf */
	स_नकल(ppi, data + RNDIS_HEADER_SIZE + rpkt->per_pkt_info_offset, rpkt->per_pkt_info_len);
	len = rpkt->per_pkt_info_len;

	जबतक (len > 0) अणु
		/* Validate ppi_offset and ppi_size */
		अगर (ppi->size > len) अणु
			netdev_err(ndev, "Invalid ppi size: %u\n", ppi->size);
			जारी;
		पूर्ण

		अगर (ppi->ppi_offset >= ppi->size) अणु
			netdev_err(ndev, "Invalid ppi_offset: %u\n", ppi->ppi_offset);
			जारी;
		पूर्ण

		अगर (ppi->type == type && ppi->पूर्णांकernal == पूर्णांकernal) अणु
			/* ppi->size should be big enough to hold the वापसed object. */
			अगर (ppi->size - ppi->ppi_offset < ppi_size) अणु
				netdev_err(ndev, "Invalid ppi: size %u ppi_offset %u\n",
					   ppi->size, ppi->ppi_offset);
				जारी;
			पूर्ण
			वापस (व्योम *)((uदीर्घ)ppi + ppi->ppi_offset);
		पूर्ण
		len -= ppi->size;
		ppi = (काष्ठा rndis_per_packet_info *)((uदीर्घ)ppi + ppi->size);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत
व्योम rsc_add_data(काष्ठा netvsc_channel *nvchan,
		  स्थिर काष्ठा ndis_pkt_8021q_info *vlan,
		  स्थिर काष्ठा ndis_tcp_ip_checksum_info *csum_info,
		  स्थिर u32 *hash_info,
		  व्योम *data, u32 len)
अणु
	u32 cnt = nvchan->rsc.cnt;

	अगर (cnt) अणु
		nvchan->rsc.pktlen += len;
	पूर्ण अन्यथा अणु
		/* The data/values poपूर्णांकed by vlan, csum_info and hash_info are shared
		 * across the dअगरferent 'fragments' of the RSC packet; store them पूर्णांकo
		 * the packet itself.
		 */
		अगर (vlan != शून्य) अणु
			स_नकल(&nvchan->rsc.vlan, vlan, माप(*vlan));
			nvchan->rsc.ppi_flags |= NVSC_RSC_VLAN;
		पूर्ण अन्यथा अणु
			nvchan->rsc.ppi_flags &= ~NVSC_RSC_VLAN;
		पूर्ण
		अगर (csum_info != शून्य) अणु
			स_नकल(&nvchan->rsc.csum_info, csum_info, माप(*csum_info));
			nvchan->rsc.ppi_flags |= NVSC_RSC_CSUM_INFO;
		पूर्ण अन्यथा अणु
			nvchan->rsc.ppi_flags &= ~NVSC_RSC_CSUM_INFO;
		पूर्ण
		nvchan->rsc.pktlen = len;
		अगर (hash_info != शून्य) अणु
			nvchan->rsc.hash_info = *hash_info;
			nvchan->rsc.ppi_flags |= NVSC_RSC_HASH_INFO;
		पूर्ण अन्यथा अणु
			nvchan->rsc.ppi_flags &= ~NVSC_RSC_HASH_INFO;
		पूर्ण
	पूर्ण

	nvchan->rsc.data[cnt] = data;
	nvchan->rsc.len[cnt] = len;
	nvchan->rsc.cnt++;
पूर्ण

अटल पूर्णांक rndis_filter_receive_data(काष्ठा net_device *ndev,
				     काष्ठा netvsc_device *nvdev,
				     काष्ठा netvsc_channel *nvchan,
				     काष्ठा rndis_message *msg,
				     व्योम *data, u32 data_buflen)
अणु
	काष्ठा rndis_packet *rndis_pkt = &msg->msg.pkt;
	स्थिर काष्ठा ndis_tcp_ip_checksum_info *csum_info;
	स्थिर काष्ठा ndis_pkt_8021q_info *vlan;
	स्थिर काष्ठा rndis_pktinfo_id *pktinfo_id;
	स्थिर u32 *hash_info;
	u32 data_offset, rpkt_len;
	bool rsc_more = false;
	पूर्णांक ret;

	/* Ensure data_buflen is big enough to पढ़ो header fields */
	अगर (data_buflen < RNDIS_HEADER_SIZE + माप(काष्ठा rndis_packet)) अणु
		netdev_err(ndev, "invalid rndis pkt, data_buflen too small: %u\n",
			   data_buflen);
		वापस NVSP_STAT_FAIL;
	पूर्ण

	/* Copy the RNDIS packet पूर्णांकo nvchan->recv_buf */
	स_नकल(rndis_pkt, data + RNDIS_HEADER_SIZE, माप(*rndis_pkt));

	/* Validate rndis_pkt offset */
	अगर (rndis_pkt->data_offset >= data_buflen - RNDIS_HEADER_SIZE) अणु
		netdev_err(ndev, "invalid rndis packet offset: %u\n",
			   rndis_pkt->data_offset);
		वापस NVSP_STAT_FAIL;
	पूर्ण

	/* Remove the rndis header and pass it back up the stack */
	data_offset = RNDIS_HEADER_SIZE + rndis_pkt->data_offset;

	rpkt_len = data_buflen - RNDIS_HEADER_SIZE;
	data_buflen -= data_offset;

	/*
	 * Make sure we got a valid RNDIS message, now total_data_buflen
	 * should be the data packet size plus the trailer padding size
	 */
	अगर (unlikely(data_buflen < rndis_pkt->data_len)) अणु
		netdev_err(ndev, "rndis message buffer "
			   "overflow detected (got %u, min %u)"
			   "...dropping this message!\n",
			   data_buflen, rndis_pkt->data_len);
		वापस NVSP_STAT_FAIL;
	पूर्ण

	vlan = rndis_get_ppi(ndev, rndis_pkt, rpkt_len, IEEE_8021Q_INFO, 0, माप(*vlan),
			     data);

	csum_info = rndis_get_ppi(ndev, rndis_pkt, rpkt_len, TCPIP_CHKSUM_PKTINFO, 0,
				  माप(*csum_info), data);

	hash_info = rndis_get_ppi(ndev, rndis_pkt, rpkt_len, NBL_HASH_VALUE, 0,
				  माप(*hash_info), data);

	pktinfo_id = rndis_get_ppi(ndev, rndis_pkt, rpkt_len, RNDIS_PKTINFO_ID, 1,
				   माप(*pktinfo_id), data);

	/* Identअगरy RSC frags, drop erroneous packets */
	अगर (pktinfo_id && (pktinfo_id->flag & RNDIS_PKTINFO_SUBALLOC)) अणु
		अगर (pktinfo_id->flag & RNDIS_PKTINFO_1ST_FRAG)
			nvchan->rsc.cnt = 0;
		अन्यथा अगर (nvchan->rsc.cnt == 0)
			जाओ drop;

		rsc_more = true;

		अगर (pktinfo_id->flag & RNDIS_PKTINFO_LAST_FRAG)
			rsc_more = false;

		अगर (rsc_more && nvchan->rsc.is_last)
			जाओ drop;
	पूर्ण अन्यथा अणु
		nvchan->rsc.cnt = 0;
	पूर्ण

	अगर (unlikely(nvchan->rsc.cnt >= NVSP_RSC_MAX))
		जाओ drop;

	/* Put data पूर्णांकo per channel काष्ठाure.
	 * Also, हटाओ the rndis trailer padding from rndis packet message
	 * rndis_pkt->data_len tell us the real data length, we only copy
	 * the data packet to the stack, without the rndis trailer padding
	 */
	rsc_add_data(nvchan, vlan, csum_info, hash_info,
		     data + data_offset, rndis_pkt->data_len);

	अगर (rsc_more)
		वापस NVSP_STAT_SUCCESS;

	ret = netvsc_recv_callback(ndev, nvdev, nvchan);
	nvchan->rsc.cnt = 0;

	वापस ret;

drop:
	वापस NVSP_STAT_FAIL;
पूर्ण

पूर्णांक rndis_filter_receive(काष्ठा net_device *ndev,
			 काष्ठा netvsc_device *net_dev,
			 काष्ठा netvsc_channel *nvchan,
			 व्योम *data, u32 buflen)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);
	काष्ठा rndis_message *rndis_msg = nvchan->recv_buf;

	अगर (buflen < RNDIS_HEADER_SIZE) अणु
		netdev_err(ndev, "Invalid rndis_msg (buflen: %u)\n", buflen);
		वापस NVSP_STAT_FAIL;
	पूर्ण

	/* Copy the RNDIS msg header पूर्णांकo nvchan->recv_buf */
	स_नकल(rndis_msg, data, RNDIS_HEADER_SIZE);

	/* Validate incoming rndis_message packet */
	अगर (rndis_msg->msg_len < RNDIS_HEADER_SIZE ||
	    buflen < rndis_msg->msg_len) अणु
		netdev_err(ndev, "Invalid rndis_msg (buflen: %u, msg_len: %u)\n",
			   buflen, rndis_msg->msg_len);
		वापस NVSP_STAT_FAIL;
	पूर्ण

	अगर (netअगर_msg_rx_status(net_device_ctx))
		dump_rndis_message(ndev, rndis_msg, data);

	चयन (rndis_msg->ndis_msg_type) अणु
	हाल RNDIS_MSG_PACKET:
		वापस rndis_filter_receive_data(ndev, net_dev, nvchan,
						 rndis_msg, data, buflen);
	हाल RNDIS_MSG_INIT_C:
	हाल RNDIS_MSG_QUERY_C:
	हाल RNDIS_MSG_SET_C:
		/* completion msgs */
		rndis_filter_receive_response(ndev, net_dev, rndis_msg, data);
		अवरोध;

	हाल RNDIS_MSG_INDICATE:
		/* notअगरication msgs */
		netvsc_linkstatus_callback(ndev, rndis_msg, data, buflen);
		अवरोध;
	शेष:
		netdev_err(ndev,
			"unhandled rndis message (type %u len %u)\n",
			   rndis_msg->ndis_msg_type,
			   rndis_msg->msg_len);
		वापस NVSP_STAT_FAIL;
	पूर्ण

	वापस NVSP_STAT_SUCCESS;
पूर्ण

अटल पूर्णांक rndis_filter_query_device(काष्ठा rndis_device *dev,
				     काष्ठा netvsc_device *nvdev,
				     u32 oid, व्योम *result, u32 *result_size)
अणु
	काष्ठा rndis_request *request;
	u32 inresult_size = *result_size;
	काष्ठा rndis_query_request *query;
	काष्ठा rndis_query_complete *query_complete;
	u32 msg_len;
	पूर्णांक ret = 0;

	अगर (!result)
		वापस -EINVAL;

	*result_size = 0;
	request = get_rndis_request(dev, RNDIS_MSG_QUERY,
			RNDIS_MESSAGE_SIZE(काष्ठा rndis_query_request));
	अगर (!request) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/* Setup the rndis query */
	query = &request->request_msg.msg.query_req;
	query->oid = oid;
	query->info_buf_offset = माप(काष्ठा rndis_query_request);
	query->info_buflen = 0;
	query->dev_vc_handle = 0;

	अगर (oid == OID_TCP_OFFLOAD_HARDWARE_CAPABILITIES) अणु
		काष्ठा ndis_offload *hwcaps;
		u32 nvsp_version = nvdev->nvsp_version;
		u8 ndis_rev;
		माप_प्रकार size;

		अगर (nvsp_version >= NVSP_PROTOCOL_VERSION_5) अणु
			ndis_rev = NDIS_OFFLOAD_PARAMETERS_REVISION_3;
			size = NDIS_OFFLOAD_SIZE;
		पूर्ण अन्यथा अगर (nvsp_version >= NVSP_PROTOCOL_VERSION_4) अणु
			ndis_rev = NDIS_OFFLOAD_PARAMETERS_REVISION_2;
			size = NDIS_OFFLOAD_SIZE_6_1;
		पूर्ण अन्यथा अणु
			ndis_rev = NDIS_OFFLOAD_PARAMETERS_REVISION_1;
			size = NDIS_OFFLOAD_SIZE_6_0;
		पूर्ण

		request->request_msg.msg_len += size;
		query->info_buflen = size;
		hwcaps = (काष्ठा ndis_offload *)
			((अचिन्हित दीर्घ)query + query->info_buf_offset);

		hwcaps->header.type = NDIS_OBJECT_TYPE_OFFLOAD;
		hwcaps->header.revision = ndis_rev;
		hwcaps->header.size = size;

	पूर्ण अन्यथा अगर (oid == OID_GEN_RECEIVE_SCALE_CAPABILITIES) अणु
		काष्ठा ndis_recv_scale_cap *cap;

		request->request_msg.msg_len +=
			माप(काष्ठा ndis_recv_scale_cap);
		query->info_buflen = माप(काष्ठा ndis_recv_scale_cap);
		cap = (काष्ठा ndis_recv_scale_cap *)((अचिन्हित दीर्घ)query +
						     query->info_buf_offset);
		cap->hdr.type = NDIS_OBJECT_TYPE_RSS_CAPABILITIES;
		cap->hdr.rev = NDIS_RECEIVE_SCALE_CAPABILITIES_REVISION_2;
		cap->hdr.size = माप(काष्ठा ndis_recv_scale_cap);
	पूर्ण

	ret = rndis_filter_send_request(dev, request);
	अगर (ret != 0)
		जाओ cleanup;

	रुको_क्रम_completion(&request->रुको_event);

	/* Copy the response back */
	query_complete = &request->response_msg.msg.query_complete;
	msg_len = request->response_msg.msg_len;

	/* Ensure the packet is big enough to access its fields */
	अगर (msg_len - RNDIS_HEADER_SIZE < माप(काष्ठा rndis_query_complete)) अणु
		ret = -1;
		जाओ cleanup;
	पूर्ण

	अगर (query_complete->info_buflen > inresult_size ||
	    query_complete->info_buf_offset < माप(*query_complete) ||
	    msg_len - RNDIS_HEADER_SIZE < query_complete->info_buf_offset ||
	    msg_len - RNDIS_HEADER_SIZE - query_complete->info_buf_offset
			< query_complete->info_buflen) अणु
		ret = -1;
		जाओ cleanup;
	पूर्ण

	स_नकल(result,
	       (व्योम *)((अचिन्हित दीर्घ)query_complete +
			 query_complete->info_buf_offset),
	       query_complete->info_buflen);

	*result_size = query_complete->info_buflen;

cleanup:
	अगर (request)
		put_rndis_request(dev, request);

	वापस ret;
पूर्ण

/* Get the hardware offload capabilities */
अटल पूर्णांक
rndis_query_hwcaps(काष्ठा rndis_device *dev, काष्ठा netvsc_device *net_device,
		   काष्ठा ndis_offload *caps)
अणु
	u32 caps_len = माप(*caps);
	पूर्णांक ret;

	स_रखो(caps, 0, माप(*caps));

	ret = rndis_filter_query_device(dev, net_device,
					OID_TCP_OFFLOAD_HARDWARE_CAPABILITIES,
					caps, &caps_len);
	अगर (ret)
		वापस ret;

	अगर (caps->header.type != NDIS_OBJECT_TYPE_OFFLOAD) अणु
		netdev_warn(dev->ndev, "invalid NDIS objtype %#x\n",
			    caps->header.type);
		वापस -EINVAL;
	पूर्ण

	अगर (caps->header.revision < NDIS_OFFLOAD_PARAMETERS_REVISION_1) अणु
		netdev_warn(dev->ndev, "invalid NDIS objrev %x\n",
			    caps->header.revision);
		वापस -EINVAL;
	पूर्ण

	अगर (caps->header.size > caps_len ||
	    caps->header.size < NDIS_OFFLOAD_SIZE_6_0) अणु
		netdev_warn(dev->ndev,
			    "invalid NDIS objsize %u, data size %u\n",
			    caps->header.size, caps_len);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rndis_filter_query_device_mac(काष्ठा rndis_device *dev,
					 काष्ठा netvsc_device *net_device)
अणु
	u32 size = ETH_ALEN;

	वापस rndis_filter_query_device(dev, net_device,
				      RNDIS_OID_802_3_PERMANENT_ADDRESS,
				      dev->hw_mac_adr, &size);
पूर्ण

#घोषणा NWADR_STR "NetworkAddress"
#घोषणा NWADR_STRLEN 14

पूर्णांक rndis_filter_set_device_mac(काष्ठा netvsc_device *nvdev,
				स्थिर अक्षर *mac)
अणु
	काष्ठा rndis_device *rdev = nvdev->extension;
	काष्ठा rndis_request *request;
	काष्ठा rndis_set_request *set;
	काष्ठा rndis_config_parameter_info *cpi;
	ब_अक्षर_प्रकार *cfg_nwadr, *cfg_mac;
	काष्ठा rndis_set_complete *set_complete;
	अक्षर macstr[2*ETH_ALEN+1];
	u32 extlen = माप(काष्ठा rndis_config_parameter_info) +
		2*NWADR_STRLEN + 4*ETH_ALEN;
	पूर्णांक ret;

	request = get_rndis_request(rdev, RNDIS_MSG_SET,
		RNDIS_MESSAGE_SIZE(काष्ठा rndis_set_request) + extlen);
	अगर (!request)
		वापस -ENOMEM;

	set = &request->request_msg.msg.set_req;
	set->oid = RNDIS_OID_GEN_RNDIS_CONFIG_PARAMETER;
	set->info_buflen = extlen;
	set->info_buf_offset = माप(काष्ठा rndis_set_request);
	set->dev_vc_handle = 0;

	cpi = (काष्ठा rndis_config_parameter_info *)((uदीर्घ)set +
		set->info_buf_offset);
	cpi->parameter_name_offset =
		माप(काष्ठा rndis_config_parameter_info);
	/* Multiply by 2 because host needs 2 bytes (utf16) क्रम each अक्षर */
	cpi->parameter_name_length = 2*NWADR_STRLEN;
	cpi->parameter_type = RNDIS_CONFIG_PARAM_TYPE_STRING;
	cpi->parameter_value_offset =
		cpi->parameter_name_offset + cpi->parameter_name_length;
	/* Multiply by 4 because each MAC byte displayed as 2 utf16 अक्षरs */
	cpi->parameter_value_length = 4*ETH_ALEN;

	cfg_nwadr = (ब_अक्षर_प्रकार *)((uदीर्घ)cpi + cpi->parameter_name_offset);
	cfg_mac = (ब_अक्षर_प्रकार *)((uदीर्घ)cpi + cpi->parameter_value_offset);
	ret = utf8s_to_utf16s(NWADR_STR, NWADR_STRLEN, UTF16_HOST_ENDIAN,
			      cfg_nwadr, NWADR_STRLEN);
	अगर (ret < 0)
		जाओ cleanup;
	snम_लिखो(macstr, 2*ETH_ALEN+1, "%pm", mac);
	ret = utf8s_to_utf16s(macstr, 2*ETH_ALEN, UTF16_HOST_ENDIAN,
			      cfg_mac, 2*ETH_ALEN);
	अगर (ret < 0)
		जाओ cleanup;

	ret = rndis_filter_send_request(rdev, request);
	अगर (ret != 0)
		जाओ cleanup;

	रुको_क्रम_completion(&request->रुको_event);

	set_complete = &request->response_msg.msg.set_complete;
	अगर (set_complete->status != RNDIS_STATUS_SUCCESS)
		ret = -EIO;

cleanup:
	put_rndis_request(rdev, request);
	वापस ret;
पूर्ण

पूर्णांक
rndis_filter_set_offload_params(काष्ठा net_device *ndev,
				काष्ठा netvsc_device *nvdev,
				काष्ठा ndis_offload_params *req_offloads)
अणु
	काष्ठा rndis_device *rdev = nvdev->extension;
	काष्ठा rndis_request *request;
	काष्ठा rndis_set_request *set;
	काष्ठा ndis_offload_params *offload_params;
	काष्ठा rndis_set_complete *set_complete;
	u32 extlen = माप(काष्ठा ndis_offload_params);
	पूर्णांक ret;
	u32 vsp_version = nvdev->nvsp_version;

	अगर (vsp_version <= NVSP_PROTOCOL_VERSION_4) अणु
		extlen = VERSION_4_OFFLOAD_SIZE;
		/* On NVSP_PROTOCOL_VERSION_4 and below, we करो not support
		 * UDP checksum offload.
		 */
		req_offloads->udp_ip_v4_csum = 0;
		req_offloads->udp_ip_v6_csum = 0;
	पूर्ण

	request = get_rndis_request(rdev, RNDIS_MSG_SET,
		RNDIS_MESSAGE_SIZE(काष्ठा rndis_set_request) + extlen);
	अगर (!request)
		वापस -ENOMEM;

	set = &request->request_msg.msg.set_req;
	set->oid = OID_TCP_OFFLOAD_PARAMETERS;
	set->info_buflen = extlen;
	set->info_buf_offset = माप(काष्ठा rndis_set_request);
	set->dev_vc_handle = 0;

	offload_params = (काष्ठा ndis_offload_params *)((uदीर्घ)set +
				set->info_buf_offset);
	*offload_params = *req_offloads;
	offload_params->header.type = NDIS_OBJECT_TYPE_DEFAULT;
	offload_params->header.revision = NDIS_OFFLOAD_PARAMETERS_REVISION_3;
	offload_params->header.size = extlen;

	ret = rndis_filter_send_request(rdev, request);
	अगर (ret != 0)
		जाओ cleanup;

	रुको_क्रम_completion(&request->रुको_event);
	set_complete = &request->response_msg.msg.set_complete;
	अगर (set_complete->status != RNDIS_STATUS_SUCCESS) अणु
		netdev_err(ndev, "Fail to set offload on host side:0x%x\n",
			   set_complete->status);
		ret = -EINVAL;
	पूर्ण

cleanup:
	put_rndis_request(rdev, request);
	वापस ret;
पूर्ण

अटल पूर्णांक rndis_set_rss_param_msg(काष्ठा rndis_device *rdev,
				   स्थिर u8 *rss_key, u16 flag)
अणु
	काष्ठा net_device *ndev = rdev->ndev;
	काष्ठा net_device_context *ndc = netdev_priv(ndev);
	काष्ठा rndis_request *request;
	काष्ठा rndis_set_request *set;
	काष्ठा rndis_set_complete *set_complete;
	u32 extlen = माप(काष्ठा ndis_recv_scale_param) +
		     4 * ITAB_NUM + NETVSC_HASH_KEYLEN;
	काष्ठा ndis_recv_scale_param *rssp;
	u32 *itab;
	u8 *keyp;
	पूर्णांक i, ret;

	request = get_rndis_request(
			rdev, RNDIS_MSG_SET,
			RNDIS_MESSAGE_SIZE(काष्ठा rndis_set_request) + extlen);
	अगर (!request)
		वापस -ENOMEM;

	set = &request->request_msg.msg.set_req;
	set->oid = OID_GEN_RECEIVE_SCALE_PARAMETERS;
	set->info_buflen = extlen;
	set->info_buf_offset = माप(काष्ठा rndis_set_request);
	set->dev_vc_handle = 0;

	rssp = (काष्ठा ndis_recv_scale_param *)(set + 1);
	rssp->hdr.type = NDIS_OBJECT_TYPE_RSS_PARAMETERS;
	rssp->hdr.rev = NDIS_RECEIVE_SCALE_PARAMETERS_REVISION_2;
	rssp->hdr.size = माप(काष्ठा ndis_recv_scale_param);
	rssp->flag = flag;
	rssp->hashinfo = NDIS_HASH_FUNC_TOEPLITZ | NDIS_HASH_IPV4 |
			 NDIS_HASH_TCP_IPV4 | NDIS_HASH_IPV6 |
			 NDIS_HASH_TCP_IPV6;
	rssp->indirect_tअसलize = 4*ITAB_NUM;
	rssp->indirect_taboffset = माप(काष्ठा ndis_recv_scale_param);
	rssp->hashkey_size = NETVSC_HASH_KEYLEN;
	rssp->hashkey_offset = rssp->indirect_taboffset +
			       rssp->indirect_tअसलize;

	/* Set indirection table entries */
	itab = (u32 *)(rssp + 1);
	क्रम (i = 0; i < ITAB_NUM; i++)
		itab[i] = ndc->rx_table[i];

	/* Set hask key values */
	keyp = (u8 *)((अचिन्हित दीर्घ)rssp + rssp->hashkey_offset);
	स_नकल(keyp, rss_key, NETVSC_HASH_KEYLEN);

	ret = rndis_filter_send_request(rdev, request);
	अगर (ret != 0)
		जाओ cleanup;

	रुको_क्रम_completion(&request->रुको_event);
	set_complete = &request->response_msg.msg.set_complete;
	अगर (set_complete->status == RNDIS_STATUS_SUCCESS) अणु
		अगर (!(flag & NDIS_RSS_PARAM_FLAG_DISABLE_RSS) &&
		    !(flag & NDIS_RSS_PARAM_FLAG_HASH_KEY_UNCHANGED))
			स_नकल(rdev->rss_key, rss_key, NETVSC_HASH_KEYLEN);

	पूर्ण अन्यथा अणु
		netdev_err(ndev, "Fail to set RSS parameters:0x%x\n",
			   set_complete->status);
		ret = -EINVAL;
	पूर्ण

cleanup:
	put_rndis_request(rdev, request);
	वापस ret;
पूर्ण

पूर्णांक rndis_filter_set_rss_param(काष्ठा rndis_device *rdev,
			       स्थिर u8 *rss_key)
अणु
	/* Disable RSS beक्रमe change */
	rndis_set_rss_param_msg(rdev, rss_key,
				NDIS_RSS_PARAM_FLAG_DISABLE_RSS);

	वापस rndis_set_rss_param_msg(rdev, rss_key, 0);
पूर्ण

अटल पूर्णांक rndis_filter_query_device_link_status(काष्ठा rndis_device *dev,
						 काष्ठा netvsc_device *net_device)
अणु
	u32 size = माप(u32);
	u32 link_status;

	वापस rndis_filter_query_device(dev, net_device,
					 RNDIS_OID_GEN_MEDIA_CONNECT_STATUS,
					 &link_status, &size);
पूर्ण

अटल पूर्णांक rndis_filter_query_link_speed(काष्ठा rndis_device *dev,
					 काष्ठा netvsc_device *net_device)
अणु
	u32 size = माप(u32);
	u32 link_speed;
	काष्ठा net_device_context *ndc;
	पूर्णांक ret;

	ret = rndis_filter_query_device(dev, net_device,
					RNDIS_OID_GEN_LINK_SPEED,
					&link_speed, &size);

	अगर (!ret) अणु
		ndc = netdev_priv(dev->ndev);

		/* The link speed reported from host is in 100bps unit, so
		 * we convert it to Mbps here.
		 */
		ndc->speed = link_speed / 10000;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rndis_filter_set_packet_filter(काष्ठा rndis_device *dev,
					  u32 new_filter)
अणु
	काष्ठा rndis_request *request;
	काष्ठा rndis_set_request *set;
	पूर्णांक ret;

	अगर (dev->filter == new_filter)
		वापस 0;

	request = get_rndis_request(dev, RNDIS_MSG_SET,
			RNDIS_MESSAGE_SIZE(काष्ठा rndis_set_request) +
			माप(u32));
	अगर (!request)
		वापस -ENOMEM;

	/* Setup the rndis set */
	set = &request->request_msg.msg.set_req;
	set->oid = RNDIS_OID_GEN_CURRENT_PACKET_FILTER;
	set->info_buflen = माप(u32);
	set->info_buf_offset = माप(काष्ठा rndis_set_request);

	स_नकल((व्योम *)(अचिन्हित दीर्घ)set + माप(काष्ठा rndis_set_request),
	       &new_filter, माप(u32));

	ret = rndis_filter_send_request(dev, request);
	अगर (ret == 0) अणु
		रुको_क्रम_completion(&request->रुको_event);
		dev->filter = new_filter;
	पूर्ण

	put_rndis_request(dev, request);

	वापस ret;
पूर्ण

अटल व्योम rndis_set_multicast(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा rndis_device *rdev
		= container_of(w, काष्ठा rndis_device, mcast_work);
	u32 filter = NDIS_PACKET_TYPE_सूचीECTED;
	अचिन्हित पूर्णांक flags = rdev->ndev->flags;

	अगर (flags & IFF_PROMISC) अणु
		filter = NDIS_PACKET_TYPE_PROMISCUOUS;
	पूर्ण अन्यथा अणु
		अगर (!netdev_mc_empty(rdev->ndev) || (flags & IFF_ALLMULTI))
			filter |= NDIS_PACKET_TYPE_ALL_MULTICAST;
		अगर (flags & IFF_BROADCAST)
			filter |= NDIS_PACKET_TYPE_BROADCAST;
	पूर्ण

	rndis_filter_set_packet_filter(rdev, filter);
पूर्ण

व्योम rndis_filter_update(काष्ठा netvsc_device *nvdev)
अणु
	काष्ठा rndis_device *rdev = nvdev->extension;

	schedule_work(&rdev->mcast_work);
पूर्ण

अटल पूर्णांक rndis_filter_init_device(काष्ठा rndis_device *dev,
				    काष्ठा netvsc_device *nvdev)
अणु
	काष्ठा rndis_request *request;
	काष्ठा rndis_initialize_request *init;
	काष्ठा rndis_initialize_complete *init_complete;
	u32 status;
	पूर्णांक ret;

	request = get_rndis_request(dev, RNDIS_MSG_INIT,
			RNDIS_MESSAGE_SIZE(काष्ठा rndis_initialize_request));
	अगर (!request) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/* Setup the rndis set */
	init = &request->request_msg.msg.init_req;
	init->major_ver = RNDIS_MAJOR_VERSION;
	init->minor_ver = RNDIS_MINOR_VERSION;
	init->max_xfer_size = 0x4000;

	dev->state = RNDIS_DEV_INITIALIZING;

	ret = rndis_filter_send_request(dev, request);
	अगर (ret != 0) अणु
		dev->state = RNDIS_DEV_UNINITIALIZED;
		जाओ cleanup;
	पूर्ण

	रुको_क्रम_completion(&request->रुको_event);

	init_complete = &request->response_msg.msg.init_complete;
	status = init_complete->status;
	अगर (status == RNDIS_STATUS_SUCCESS) अणु
		dev->state = RNDIS_DEV_INITIALIZED;
		nvdev->max_pkt = init_complete->max_pkt_per_msg;
		nvdev->pkt_align = 1 << init_complete->pkt_alignment_factor;
		ret = 0;
	पूर्ण अन्यथा अणु
		dev->state = RNDIS_DEV_UNINITIALIZED;
		ret = -EINVAL;
	पूर्ण

cleanup:
	अगर (request)
		put_rndis_request(dev, request);

	वापस ret;
पूर्ण

अटल bool netvsc_device_idle(स्थिर काष्ठा netvsc_device *nvdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nvdev->num_chn; i++) अणु
		स्थिर काष्ठा netvsc_channel *nvchan = &nvdev->chan_table[i];

		अगर (nvchan->mrc.first != nvchan->mrc.next)
			वापस false;

		अगर (atomic_पढ़ो(&nvchan->queue_sends) > 0)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम rndis_filter_halt_device(काष्ठा netvsc_device *nvdev,
				     काष्ठा rndis_device *dev)
अणु
	काष्ठा rndis_request *request;
	काष्ठा rndis_halt_request *halt;

	/* Attempt to करो a rndis device halt */
	request = get_rndis_request(dev, RNDIS_MSG_HALT,
				RNDIS_MESSAGE_SIZE(काष्ठा rndis_halt_request));
	अगर (!request)
		जाओ cleanup;

	/* Setup the rndis set */
	halt = &request->request_msg.msg.halt_req;
	halt->req_id = atomic_inc_वापस(&dev->new_req_id);

	/* Ignore वापस since this msg is optional. */
	rndis_filter_send_request(dev, request);

	dev->state = RNDIS_DEV_UNINITIALIZED;

cleanup:
	nvdev->destroy = true;

	/* Force flag to be ordered beक्रमe रुकोing */
	wmb();

	/* Wait क्रम all send completions */
	रुको_event(nvdev->रुको_drain, netvsc_device_idle(nvdev));

	अगर (request)
		put_rndis_request(dev, request);
पूर्ण

अटल पूर्णांक rndis_filter_खोलो_device(काष्ठा rndis_device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->state != RNDIS_DEV_INITIALIZED)
		वापस 0;

	ret = rndis_filter_set_packet_filter(dev,
					 NDIS_PACKET_TYPE_BROADCAST |
					 NDIS_PACKET_TYPE_ALL_MULTICAST |
					 NDIS_PACKET_TYPE_सूचीECTED);
	अगर (ret == 0)
		dev->state = RNDIS_DEV_DATAINITIALIZED;

	वापस ret;
पूर्ण

अटल पूर्णांक rndis_filter_बंद_device(काष्ठा rndis_device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->state != RNDIS_DEV_DATAINITIALIZED)
		वापस 0;

	/* Make sure rndis_set_multicast करोesn't re-enable filter! */
	cancel_work_sync(&dev->mcast_work);

	ret = rndis_filter_set_packet_filter(dev, 0);
	अगर (ret == -ENODEV)
		ret = 0;

	अगर (ret == 0)
		dev->state = RNDIS_DEV_INITIALIZED;

	वापस ret;
पूर्ण

अटल व्योम netvsc_sc_खोलो(काष्ठा vmbus_channel *new_sc)
अणु
	काष्ठा net_device *ndev =
		hv_get_drvdata(new_sc->primary_channel->device_obj);
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा netvsc_device *nvscdev;
	u16 chn_index = new_sc->offermsg.offer.sub_channel_index;
	काष्ठा netvsc_channel *nvchan;
	पूर्णांक ret;

	/* This is safe because this callback only happens when
	 * new device is being setup and रुकोing on the channel_init_रुको.
	 */
	nvscdev = rcu_dereference_raw(ndev_ctx->nvdev);
	अगर (!nvscdev || chn_index >= nvscdev->num_chn)
		वापस;

	nvchan = nvscdev->chan_table + chn_index;

	/* Because the device uses NAPI, all the पूर्णांकerrupt batching and
	 * control is करोne via Net softirq, not the channel handling
	 */
	set_channel_पढ़ो_mode(new_sc, HV_CALL_ISR);

	/* Set the channel beक्रमe खोलोing.*/
	nvchan->channel = new_sc;

	new_sc->rqstor_size = netvsc_rqstor_size(netvsc_ring_bytes);
	ret = vmbus_खोलो(new_sc, netvsc_ring_bytes,
			 netvsc_ring_bytes, शून्य, 0,
			 netvsc_channel_cb, nvchan);
	अगर (ret == 0)
		napi_enable(&nvchan->napi);
	अन्यथा
		netdev_notice(ndev, "sub channel open failed: %d\n", ret);

	अगर (atomic_inc_वापस(&nvscdev->खोलो_chn) == nvscdev->num_chn)
		wake_up(&nvscdev->subchan_खोलो);
पूर्ण

/* Open sub-channels after completing the handling of the device probe.
 * This अवरोधs overlap of processing the host message क्रम the
 * new primary channel with the initialization of sub-channels.
 */
पूर्णांक rndis_set_subchannel(काष्ठा net_device *ndev,
			 काष्ठा netvsc_device *nvdev,
			 काष्ठा netvsc_device_info *dev_info)
अणु
	काष्ठा nvsp_message *init_packet = &nvdev->channel_init_pkt;
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा hv_device *hv_dev = ndev_ctx->device_ctx;
	काष्ठा rndis_device *rdev = nvdev->extension;
	पूर्णांक i, ret;

	ASSERT_RTNL();

	स_रखो(init_packet, 0, माप(काष्ठा nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG5_TYPE_SUBCHANNEL;
	init_packet->msg.v5_msg.subchn_req.op = NVSP_SUBCHANNEL_ALLOCATE;
	init_packet->msg.v5_msg.subchn_req.num_subchannels =
						nvdev->num_chn - 1;
	trace_nvsp_send(ndev, init_packet);

	ret = vmbus_sendpacket(hv_dev->channel, init_packet,
			       माप(काष्ठा nvsp_message),
			       (अचिन्हित दीर्घ)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret) अणु
		netdev_err(ndev, "sub channel allocate send failed: %d\n", ret);
		वापस ret;
	पूर्ण

	रुको_क्रम_completion(&nvdev->channel_init_रुको);
	अगर (init_packet->msg.v5_msg.subchn_comp.status != NVSP_STAT_SUCCESS) अणु
		netdev_err(ndev, "sub channel request failed\n");
		वापस -EIO;
	पूर्ण

	/* Check that number of allocated sub channel is within the expected range */
	अगर (init_packet->msg.v5_msg.subchn_comp.num_subchannels > nvdev->num_chn - 1) अणु
		netdev_err(ndev, "invalid number of allocated sub channel\n");
		वापस -EINVAL;
	पूर्ण
	nvdev->num_chn = 1 +
		init_packet->msg.v5_msg.subchn_comp.num_subchannels;

	/* रुको क्रम all sub channels to खोलो */
	रुको_event(nvdev->subchan_खोलो,
		   atomic_पढ़ो(&nvdev->खोलो_chn) == nvdev->num_chn);

	क्रम (i = 0; i < VRSS_SEND_TAB_SIZE; i++)
		ndev_ctx->tx_table[i] = i % nvdev->num_chn;

	/* ignore failures from setting rss parameters, still have channels */
	अगर (dev_info)
		rndis_filter_set_rss_param(rdev, dev_info->rss_key);
	अन्यथा
		rndis_filter_set_rss_param(rdev, netvsc_hash_key);

	netअगर_set_real_num_tx_queues(ndev, nvdev->num_chn);
	netअगर_set_real_num_rx_queues(ndev, nvdev->num_chn);

	वापस 0;
पूर्ण

अटल पूर्णांक rndis_netdev_set_hwcaps(काष्ठा rndis_device *rndis_device,
				   काष्ठा netvsc_device *nvdev)
अणु
	काष्ठा net_device *net = rndis_device->ndev;
	काष्ठा net_device_context *net_device_ctx = netdev_priv(net);
	काष्ठा ndis_offload hwcaps;
	काष्ठा ndis_offload_params offloads;
	अचिन्हित पूर्णांक gso_max_size = GSO_MAX_SIZE;
	पूर्णांक ret;

	/* Find HW offload capabilities */
	ret = rndis_query_hwcaps(rndis_device, nvdev, &hwcaps);
	अगर (ret != 0)
		वापस ret;

	/* A value of zero means "no change"; now turn on what we want. */
	स_रखो(&offloads, 0, माप(काष्ठा ndis_offload_params));

	/* Linux करोes not care about IP checksum, always करोes in kernel */
	offloads.ip_v4_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_DISABLED;

	/* Reset previously set hw_features flags */
	net->hw_features &= ~NETVSC_SUPPORTED_HW_FEATURES;
	net_device_ctx->tx_checksum_mask = 0;

	/* Compute tx offload settings based on hw capabilities */
	net->hw_features |= NETIF_F_RXCSUM;
	net->hw_features |= NETIF_F_SG;
	net->hw_features |= NETIF_F_RXHASH;

	अगर ((hwcaps.csum.ip4_txcsum & NDIS_TXCSUM_ALL_TCP4) == NDIS_TXCSUM_ALL_TCP4) अणु
		/* Can checksum TCP */
		net->hw_features |= NETIF_F_IP_CSUM;
		net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV4_TCP;

		offloads.tcp_ip_v4_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;

		अगर (hwcaps.lsov2.ip4_encap & NDIS_OFFLOAD_ENCAP_8023) अणु
			offloads.lso_v2_ipv4 = NDIS_OFFLOAD_PARAMETERS_LSOV2_ENABLED;
			net->hw_features |= NETIF_F_TSO;

			अगर (hwcaps.lsov2.ip4_maxsz < gso_max_size)
				gso_max_size = hwcaps.lsov2.ip4_maxsz;
		पूर्ण

		अगर (hwcaps.csum.ip4_txcsum & NDIS_TXCSUM_CAP_UDP4) अणु
			offloads.udp_ip_v4_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;
			net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV4_UDP;
		पूर्ण
	पूर्ण

	अगर ((hwcaps.csum.ip6_txcsum & NDIS_TXCSUM_ALL_TCP6) == NDIS_TXCSUM_ALL_TCP6) अणु
		net->hw_features |= NETIF_F_IPV6_CSUM;

		offloads.tcp_ip_v6_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;
		net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV6_TCP;

		अगर ((hwcaps.lsov2.ip6_encap & NDIS_OFFLOAD_ENCAP_8023) &&
		    (hwcaps.lsov2.ip6_opts & NDIS_LSOV2_CAP_IP6) == NDIS_LSOV2_CAP_IP6) अणु
			offloads.lso_v2_ipv6 = NDIS_OFFLOAD_PARAMETERS_LSOV2_ENABLED;
			net->hw_features |= NETIF_F_TSO6;

			अगर (hwcaps.lsov2.ip6_maxsz < gso_max_size)
				gso_max_size = hwcaps.lsov2.ip6_maxsz;
		पूर्ण

		अगर (hwcaps.csum.ip6_txcsum & NDIS_TXCSUM_CAP_UDP6) अणु
			offloads.udp_ip_v6_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;
			net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV6_UDP;
		पूर्ण
	पूर्ण

	अगर (hwcaps.rsc.ip4 && hwcaps.rsc.ip6) अणु
		net->hw_features |= NETIF_F_LRO;

		अगर (net->features & NETIF_F_LRO) अणु
			offloads.rsc_ip_v4 = NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED;
			offloads.rsc_ip_v6 = NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED;
		पूर्ण अन्यथा अणु
			offloads.rsc_ip_v4 = NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED;
			offloads.rsc_ip_v6 = NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED;
		पूर्ण
	पूर्ण

	/* In हाल some hw_features disappeared we need to हटाओ them from
	 * net->features list as they're no दीर्घer supported.
	 */
	net->features &= ~NETVSC_SUPPORTED_HW_FEATURES | net->hw_features;

	netअगर_set_gso_max_size(net, gso_max_size);

	ret = rndis_filter_set_offload_params(net, nvdev, &offloads);

	वापस ret;
पूर्ण

अटल व्योम rndis_get_मित्रly_name(काष्ठा net_device *net,
				    काष्ठा rndis_device *rndis_device,
				    काष्ठा netvsc_device *net_device)
अणु
	ucs2_अक्षर_t wname[256];
	अचिन्हित दीर्घ len;
	u8 अगरalias[256];
	u32 size;

	size = माप(wname);
	अगर (rndis_filter_query_device(rndis_device, net_device,
				      RNDIS_OID_GEN_FRIENDLY_NAME,
				      wname, &size) != 0)
		वापस;	/* ignore अगर host करोes not support */

	अगर (size == 0)
		वापस;	/* name not set */

	/* Convert Winकरोws Unicode string to UTF-8 */
	len = ucs2_as_utf8(अगरalias, wname, माप(अगरalias));

	/* ignore the शेष value from host */
	अगर (म_भेद(अगरalias, "Network Adapter") != 0)
		dev_set_alias(net, अगरalias, len);
पूर्ण

काष्ठा netvsc_device *rndis_filter_device_add(काष्ठा hv_device *dev,
				      काष्ठा netvsc_device_info *device_info)
अणु
	काष्ठा net_device *net = hv_get_drvdata(dev);
	काष्ठा net_device_context *ndc = netdev_priv(net);
	काष्ठा netvsc_device *net_device;
	काष्ठा rndis_device *rndis_device;
	काष्ठा ndis_recv_scale_cap rsscap;
	u32 rsscap_size = माप(काष्ठा ndis_recv_scale_cap);
	u32 mtu, size;
	u32 num_possible_rss_qs;
	पूर्णांक i, ret;

	rndis_device = get_rndis_device();
	अगर (!rndis_device)
		वापस ERR_PTR(-ENODEV);

	/* Let the inner driver handle this first to create the netvsc channel
	 * NOTE! Once the channel is created, we may get a receive callback
	 * (RndisFilterOnReceive()) beक्रमe this call is completed
	 */
	net_device = netvsc_device_add(dev, device_info);
	अगर (IS_ERR(net_device)) अणु
		kमुक्त(rndis_device);
		वापस net_device;
	पूर्ण

	/* Initialize the rndis device */
	net_device->max_chn = 1;
	net_device->num_chn = 1;

	net_device->extension = rndis_device;
	rndis_device->ndev = net;

	/* Send the rndis initialization message */
	ret = rndis_filter_init_device(rndis_device, net_device);
	अगर (ret != 0)
		जाओ err_dev_remv;

	/* Get the MTU from the host */
	size = माप(u32);
	ret = rndis_filter_query_device(rndis_device, net_device,
					RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE,
					&mtu, &size);
	अगर (ret == 0 && size == माप(u32) && mtu < net->mtu)
		net->mtu = mtu;

	/* Get the mac address */
	ret = rndis_filter_query_device_mac(rndis_device, net_device);
	अगर (ret != 0)
		जाओ err_dev_remv;

	स_नकल(device_info->mac_adr, rndis_device->hw_mac_adr, ETH_ALEN);

	/* Get मित्रly name as अगरalias*/
	अगर (!net->अगरalias)
		rndis_get_मित्रly_name(net, rndis_device, net_device);

	/* Query and set hardware capabilities */
	ret = rndis_netdev_set_hwcaps(rndis_device, net_device);
	अगर (ret != 0)
		जाओ err_dev_remv;

	rndis_filter_query_device_link_status(rndis_device, net_device);

	netdev_dbg(net, "Device MAC %pM link state %s\n",
		   rndis_device->hw_mac_adr,
		   rndis_device->link_state ? "down" : "up");

	अगर (net_device->nvsp_version < NVSP_PROTOCOL_VERSION_5)
		जाओ out;

	rndis_filter_query_link_speed(rndis_device, net_device);

	/* vRSS setup */
	स_रखो(&rsscap, 0, rsscap_size);
	ret = rndis_filter_query_device(rndis_device, net_device,
					OID_GEN_RECEIVE_SCALE_CAPABILITIES,
					&rsscap, &rsscap_size);
	अगर (ret || rsscap.num_recv_que < 2)
		जाओ out;

	/* This guarantees that num_possible_rss_qs <= num_online_cpus */
	num_possible_rss_qs = min_t(u32, num_online_cpus(),
				    rsscap.num_recv_que);

	net_device->max_chn = min_t(u32, VRSS_CHANNEL_MAX, num_possible_rss_qs);

	/* We will use the given number of channels अगर available. */
	net_device->num_chn = min(net_device->max_chn, device_info->num_chn);

	अगर (!netअगर_is_rxfh_configured(net)) अणु
		क्रम (i = 0; i < ITAB_NUM; i++)
			ndc->rx_table[i] = ethtool_rxfh_indir_शेष(
						i, net_device->num_chn);
	पूर्ण

	atomic_set(&net_device->खोलो_chn, 1);
	vmbus_set_sc_create_callback(dev->channel, netvsc_sc_खोलो);

	क्रम (i = 1; i < net_device->num_chn; i++) अणु
		ret = netvsc_alloc_recv_comp_ring(net_device, i);
		अगर (ret) अणु
			जबतक (--i != 0)
				vमुक्त(net_device->chan_table[i].mrc.slots);
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 1; i < net_device->num_chn; i++)
		netअगर_napi_add(net, &net_device->chan_table[i].napi,
			       netvsc_poll, NAPI_POLL_WEIGHT);

	वापस net_device;

out:
	/* setting up multiple channels failed */
	net_device->max_chn = 1;
	net_device->num_chn = 1;
	वापस net_device;

err_dev_remv:
	rndis_filter_device_हटाओ(dev, net_device);
	वापस ERR_PTR(ret);
पूर्ण

व्योम rndis_filter_device_हटाओ(काष्ठा hv_device *dev,
				काष्ठा netvsc_device *net_dev)
अणु
	काष्ठा rndis_device *rndis_dev = net_dev->extension;

	/* Halt and release the rndis device */
	rndis_filter_halt_device(net_dev, rndis_dev);

	netvsc_device_हटाओ(dev);
पूर्ण

पूर्णांक rndis_filter_खोलो(काष्ठा netvsc_device *nvdev)
अणु
	अगर (!nvdev)
		वापस -EINVAL;

	वापस rndis_filter_खोलो_device(nvdev->extension);
पूर्ण

पूर्णांक rndis_filter_बंद(काष्ठा netvsc_device *nvdev)
अणु
	अगर (!nvdev)
		वापस -EINVAL;

	वापस rndis_filter_बंद_device(nvdev->extension);
पूर्ण
