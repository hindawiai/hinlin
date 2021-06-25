<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/prefetch.h>

#समावेश <यंत्र/sync_bitops.h>
#समावेश <यंत्र/mshyperv.h>

#समावेश "hyperv_net.h"
#समावेश "netvsc_trace.h"

/*
 * Switch the data path from the synthetic पूर्णांकerface to the VF
 * पूर्णांकerface.
 */
पूर्णांक netvsc_चयन_datapath(काष्ठा net_device *ndev, bool vf)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);
	काष्ठा hv_device *dev = net_device_ctx->device_ctx;
	काष्ठा netvsc_device *nv_dev = rtnl_dereference(net_device_ctx->nvdev);
	काष्ठा nvsp_message *init_pkt = &nv_dev->channel_init_pkt;
	पूर्णांक ret, retry = 0;

	/* Block sending traffic to VF अगर it's about to be gone */
	अगर (!vf)
		net_device_ctx->data_path_is_vf = vf;

	स_रखो(init_pkt, 0, माप(काष्ठा nvsp_message));
	init_pkt->hdr.msg_type = NVSP_MSG4_TYPE_SWITCH_DATA_PATH;
	अगर (vf)
		init_pkt->msg.v4_msg.active_dp.active_datapath =
			NVSP_DATAPATH_VF;
	अन्यथा
		init_pkt->msg.v4_msg.active_dp.active_datapath =
			NVSP_DATAPATH_SYNTHETIC;

again:
	trace_nvsp_send(ndev, init_pkt);

	ret = vmbus_sendpacket(dev->channel, init_pkt,
			       माप(काष्ठा nvsp_message),
			       (अचिन्हित दीर्घ)init_pkt, VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);

	/* If failed to चयन to/from VF, let data_path_is_vf stay false,
	 * so we use synthetic path to send data.
	 */
	अगर (ret) अणु
		अगर (ret != -EAGAIN) अणु
			netdev_err(ndev,
				   "Unable to send sw datapath msg, err: %d\n",
				   ret);
			वापस ret;
		पूर्ण

		अगर (retry++ < RETRY_MAX) अणु
			usleep_range(RETRY_US_LO, RETRY_US_HI);
			जाओ again;
		पूर्ण अन्यथा अणु
			netdev_err(
				ndev,
				"Retry failed to send sw datapath msg, err: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	रुको_क्रम_completion(&nv_dev->channel_init_रुको);
	net_device_ctx->data_path_is_vf = vf;

	वापस 0;
पूर्ण

/* Worker to setup sub channels on initial setup
 * Initial hotplug event occurs in softirq context
 * and can't रुको क्रम channels.
 */
अटल व्योम netvsc_subchan_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा netvsc_device *nvdev =
		container_of(w, काष्ठा netvsc_device, subchan_work);
	काष्ठा rndis_device *rdev;
	पूर्णांक i, ret;

	/* Aव्योम deadlock with device removal alपढ़ोy under RTNL */
	अगर (!rtnl_trylock()) अणु
		schedule_work(w);
		वापस;
	पूर्ण

	rdev = nvdev->extension;
	अगर (rdev) अणु
		ret = rndis_set_subchannel(rdev->ndev, nvdev, शून्य);
		अगर (ret == 0) अणु
			netअगर_device_attach(rdev->ndev);
		पूर्ण अन्यथा अणु
			/* fallback to only primary channel */
			क्रम (i = 1; i < nvdev->num_chn; i++)
				netअगर_napi_del(&nvdev->chan_table[i].napi);

			nvdev->max_chn = 1;
			nvdev->num_chn = 1;
		पूर्ण
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल काष्ठा netvsc_device *alloc_net_device(व्योम)
अणु
	काष्ठा netvsc_device *net_device;

	net_device = kzalloc(माप(काष्ठा netvsc_device), GFP_KERNEL);
	अगर (!net_device)
		वापस शून्य;

	init_रुकोqueue_head(&net_device->रुको_drain);
	net_device->destroy = false;
	net_device->tx_disable = true;

	net_device->max_pkt = RNDIS_MAX_PKT_DEFAULT;
	net_device->pkt_align = RNDIS_PKT_ALIGN_DEFAULT;

	init_completion(&net_device->channel_init_रुको);
	init_रुकोqueue_head(&net_device->subchan_खोलो);
	INIT_WORK(&net_device->subchan_work, netvsc_subchan_work);

	वापस net_device;
पूर्ण

अटल व्योम मुक्त_netvsc_device(काष्ठा rcu_head *head)
अणु
	काष्ठा netvsc_device *nvdev
		= container_of(head, काष्ठा netvsc_device, rcu);
	पूर्णांक i;

	kमुक्त(nvdev->extension);
	vमुक्त(nvdev->recv_buf);
	vमुक्त(nvdev->send_buf);
	kमुक्त(nvdev->send_section_map);

	क्रम (i = 0; i < VRSS_CHANNEL_MAX; i++) अणु
		xdp_rxq_info_unreg(&nvdev->chan_table[i].xdp_rxq);
		kमुक्त(nvdev->chan_table[i].recv_buf);
		vमुक्त(nvdev->chan_table[i].mrc.slots);
	पूर्ण

	kमुक्त(nvdev);
पूर्ण

अटल व्योम मुक्त_netvsc_device_rcu(काष्ठा netvsc_device *nvdev)
अणु
	call_rcu(&nvdev->rcu, मुक्त_netvsc_device);
पूर्ण

अटल व्योम netvsc_revoke_recv_buf(काष्ठा hv_device *device,
				   काष्ठा netvsc_device *net_device,
				   काष्ठा net_device *ndev)
अणु
	काष्ठा nvsp_message *revoke_packet;
	पूर्णांक ret;

	/*
	 * If we got a section count, it means we received a
	 * SendReceiveBufferComplete msg (ie sent
	 * NvspMessage1TypeSendReceiveBuffer msg) thereक्रमe, we need
	 * to send a revoke msg here
	 */
	अगर (net_device->recv_section_cnt) अणु
		/* Send the revoke receive buffer */
		revoke_packet = &net_device->revoke_packet;
		स_रखो(revoke_packet, 0, माप(काष्ठा nvsp_message));

		revoke_packet->hdr.msg_type =
			NVSP_MSG1_TYPE_REVOKE_RECV_BUF;
		revoke_packet->msg.v1_msg.
		revoke_recv_buf.id = NETVSC_RECEIVE_BUFFER_ID;

		trace_nvsp_send(ndev, revoke_packet);

		ret = vmbus_sendpacket(device->channel,
				       revoke_packet,
				       माप(काष्ठा nvsp_message),
				       VMBUS_RQST_ID_NO_RESPONSE,
				       VM_PKT_DATA_INBAND, 0);
		/* If the failure is because the channel is rescinded;
		 * ignore the failure since we cannot send on a rescinded
		 * channel. This would allow us to properly cleanup
		 * even when the channel is rescinded.
		 */
		अगर (device->channel->rescind)
			ret = 0;
		/*
		 * If we failed here, we might as well वापस and
		 * have a leak rather than जारी and a bugchk
		 */
		अगर (ret != 0) अणु
			netdev_err(ndev, "unable to send "
				"revoke receive buffer to netvsp\n");
			वापस;
		पूर्ण
		net_device->recv_section_cnt = 0;
	पूर्ण
पूर्ण

अटल व्योम netvsc_revoke_send_buf(काष्ठा hv_device *device,
				   काष्ठा netvsc_device *net_device,
				   काष्ठा net_device *ndev)
अणु
	काष्ठा nvsp_message *revoke_packet;
	पूर्णांक ret;

	/* Deal with the send buffer we may have setup.
	 * If we got a  send section size, it means we received a
	 * NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE msg (ie sent
	 * NVSP_MSG1_TYPE_SEND_SEND_BUF msg) thereक्रमe, we need
	 * to send a revoke msg here
	 */
	अगर (net_device->send_section_cnt) अणु
		/* Send the revoke receive buffer */
		revoke_packet = &net_device->revoke_packet;
		स_रखो(revoke_packet, 0, माप(काष्ठा nvsp_message));

		revoke_packet->hdr.msg_type =
			NVSP_MSG1_TYPE_REVOKE_SEND_BUF;
		revoke_packet->msg.v1_msg.revoke_send_buf.id =
			NETVSC_SEND_BUFFER_ID;

		trace_nvsp_send(ndev, revoke_packet);

		ret = vmbus_sendpacket(device->channel,
				       revoke_packet,
				       माप(काष्ठा nvsp_message),
				       VMBUS_RQST_ID_NO_RESPONSE,
				       VM_PKT_DATA_INBAND, 0);

		/* If the failure is because the channel is rescinded;
		 * ignore the failure since we cannot send on a rescinded
		 * channel. This would allow us to properly cleanup
		 * even when the channel is rescinded.
		 */
		अगर (device->channel->rescind)
			ret = 0;

		/* If we failed here, we might as well वापस and
		 * have a leak rather than जारी and a bugchk
		 */
		अगर (ret != 0) अणु
			netdev_err(ndev, "unable to send "
				   "revoke send buffer to netvsp\n");
			वापस;
		पूर्ण
		net_device->send_section_cnt = 0;
	पूर्ण
पूर्ण

अटल व्योम netvsc_tearकरोwn_recv_gpadl(काष्ठा hv_device *device,
				       काष्ठा netvsc_device *net_device,
				       काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;

	अगर (net_device->recv_buf_gpadl_handle) अणु
		ret = vmbus_tearकरोwn_gpadl(device->channel,
					   net_device->recv_buf_gpadl_handle);

		/* If we failed here, we might as well वापस and have a leak
		 * rather than जारी and a bugchk
		 */
		अगर (ret != 0) अणु
			netdev_err(ndev,
				   "unable to teardown receive buffer's gpadl\n");
			वापस;
		पूर्ण
		net_device->recv_buf_gpadl_handle = 0;
	पूर्ण
पूर्ण

अटल व्योम netvsc_tearकरोwn_send_gpadl(काष्ठा hv_device *device,
				       काष्ठा netvsc_device *net_device,
				       काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;

	अगर (net_device->send_buf_gpadl_handle) अणु
		ret = vmbus_tearकरोwn_gpadl(device->channel,
					   net_device->send_buf_gpadl_handle);

		/* If we failed here, we might as well वापस and have a leak
		 * rather than जारी and a bugchk
		 */
		अगर (ret != 0) अणु
			netdev_err(ndev,
				   "unable to teardown send buffer's gpadl\n");
			वापस;
		पूर्ण
		net_device->send_buf_gpadl_handle = 0;
	पूर्ण
पूर्ण

पूर्णांक netvsc_alloc_recv_comp_ring(काष्ठा netvsc_device *net_device, u32 q_idx)
अणु
	काष्ठा netvsc_channel *nvchan = &net_device->chan_table[q_idx];
	पूर्णांक node = cpu_to_node(nvchan->channel->target_cpu);
	माप_प्रकार size;

	size = net_device->recv_completion_cnt * माप(काष्ठा recv_comp_data);
	nvchan->mrc.slots = vzalloc_node(size, node);
	अगर (!nvchan->mrc.slots)
		nvchan->mrc.slots = vzalloc(size);

	वापस nvchan->mrc.slots ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक netvsc_init_buf(काष्ठा hv_device *device,
			   काष्ठा netvsc_device *net_device,
			   स्थिर काष्ठा netvsc_device_info *device_info)
अणु
	काष्ठा nvsp_1_message_send_receive_buffer_complete *resp;
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	काष्ठा nvsp_message *init_packet;
	अचिन्हित पूर्णांक buf_size;
	माप_प्रकार map_words;
	पूर्णांक i, ret = 0;

	/* Get receive buffer area. */
	buf_size = device_info->recv_sections * device_info->recv_section_size;
	buf_size = roundup(buf_size, PAGE_SIZE);

	/* Legacy hosts only allow smaller receive buffer */
	अगर (net_device->nvsp_version <= NVSP_PROTOCOL_VERSION_2)
		buf_size = min_t(अचिन्हित पूर्णांक, buf_size,
				 NETVSC_RECEIVE_BUFFER_SIZE_LEGACY);

	net_device->recv_buf = vzalloc(buf_size);
	अगर (!net_device->recv_buf) अणु
		netdev_err(ndev,
			   "unable to allocate receive buffer of size %u\n",
			   buf_size);
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	net_device->recv_buf_size = buf_size;

	/*
	 * Establish the gpadl handle क्रम this buffer on this
	 * channel.  Note: This call uses the vmbus connection rather
	 * than the channel to establish the gpadl handle.
	 */
	ret = vmbus_establish_gpadl(device->channel, net_device->recv_buf,
				    buf_size,
				    &net_device->recv_buf_gpadl_handle);
	अगर (ret != 0) अणु
		netdev_err(ndev,
			"unable to establish receive buffer's gpadl\n");
		जाओ cleanup;
	पूर्ण

	/* Notअगरy the NetVsp of the gpadl handle */
	init_packet = &net_device->channel_init_pkt;
	स_रखो(init_packet, 0, माप(काष्ठा nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG1_TYPE_SEND_RECV_BUF;
	init_packet->msg.v1_msg.send_recv_buf.
		gpadl_handle = net_device->recv_buf_gpadl_handle;
	init_packet->msg.v1_msg.
		send_recv_buf.id = NETVSC_RECEIVE_BUFFER_ID;

	trace_nvsp_send(ndev, init_packet);

	/* Send the gpadl notअगरication request */
	ret = vmbus_sendpacket(device->channel, init_packet,
			       माप(काष्ठा nvsp_message),
			       (अचिन्हित दीर्घ)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret != 0) अणु
		netdev_err(ndev,
			"unable to send receive buffer's gpadl to netvsp\n");
		जाओ cleanup;
	पूर्ण

	रुको_क्रम_completion(&net_device->channel_init_रुको);

	/* Check the response */
	resp = &init_packet->msg.v1_msg.send_recv_buf_complete;
	अगर (resp->status != NVSP_STAT_SUCCESS) अणु
		netdev_err(ndev,
			   "Unable to complete receive buffer initialization with NetVsp - status %d\n",
			   resp->status);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* Parse the response */
	netdev_dbg(ndev, "Receive sections: %u sub_allocs: size %u count: %u\n",
		   resp->num_sections, resp->sections[0].sub_alloc_size,
		   resp->sections[0].num_sub_allocs);

	/* There should only be one section क्रम the entire receive buffer */
	अगर (resp->num_sections != 1 || resp->sections[0].offset != 0) अणु
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	net_device->recv_section_size = resp->sections[0].sub_alloc_size;
	net_device->recv_section_cnt = resp->sections[0].num_sub_allocs;

	/* Ensure buffer will not overflow */
	अगर (net_device->recv_section_size < NETVSC_MTU_MIN || (u64)net_device->recv_section_size *
	    (u64)net_device->recv_section_cnt > (u64)buf_size) अणु
		netdev_err(ndev, "invalid recv_section_size %u\n",
			   net_device->recv_section_size);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	क्रम (i = 0; i < VRSS_CHANNEL_MAX; i++) अणु
		काष्ठा netvsc_channel *nvchan = &net_device->chan_table[i];

		nvchan->recv_buf = kzalloc(net_device->recv_section_size, GFP_KERNEL);
		अगर (nvchan->recv_buf == शून्य) अणु
			ret = -ENOMEM;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* Setup receive completion ring.
	 * Add 1 to the recv_section_cnt because at least one entry in a
	 * ring buffer has to be empty.
	 */
	net_device->recv_completion_cnt = net_device->recv_section_cnt + 1;
	ret = netvsc_alloc_recv_comp_ring(net_device, 0);
	अगर (ret)
		जाओ cleanup;

	/* Now setup the send buffer. */
	buf_size = device_info->send_sections * device_info->send_section_size;
	buf_size = round_up(buf_size, PAGE_SIZE);

	net_device->send_buf = vzalloc(buf_size);
	अगर (!net_device->send_buf) अणु
		netdev_err(ndev, "unable to allocate send buffer of size %u\n",
			   buf_size);
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/* Establish the gpadl handle क्रम this buffer on this
	 * channel.  Note: This call uses the vmbus connection rather
	 * than the channel to establish the gpadl handle.
	 */
	ret = vmbus_establish_gpadl(device->channel, net_device->send_buf,
				    buf_size,
				    &net_device->send_buf_gpadl_handle);
	अगर (ret != 0) अणु
		netdev_err(ndev,
			   "unable to establish send buffer's gpadl\n");
		जाओ cleanup;
	पूर्ण

	/* Notअगरy the NetVsp of the gpadl handle */
	init_packet = &net_device->channel_init_pkt;
	स_रखो(init_packet, 0, माप(काष्ठा nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG1_TYPE_SEND_SEND_BUF;
	init_packet->msg.v1_msg.send_send_buf.gpadl_handle =
		net_device->send_buf_gpadl_handle;
	init_packet->msg.v1_msg.send_send_buf.id = NETVSC_SEND_BUFFER_ID;

	trace_nvsp_send(ndev, init_packet);

	/* Send the gpadl notअगरication request */
	ret = vmbus_sendpacket(device->channel, init_packet,
			       माप(काष्ठा nvsp_message),
			       (अचिन्हित दीर्घ)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret != 0) अणु
		netdev_err(ndev,
			   "unable to send send buffer's gpadl to netvsp\n");
		जाओ cleanup;
	पूर्ण

	रुको_क्रम_completion(&net_device->channel_init_रुको);

	/* Check the response */
	अगर (init_packet->msg.v1_msg.
	    send_send_buf_complete.status != NVSP_STAT_SUCCESS) अणु
		netdev_err(ndev, "Unable to complete send buffer "
			   "initialization with NetVsp - status %d\n",
			   init_packet->msg.v1_msg.
			   send_send_buf_complete.status);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* Parse the response */
	net_device->send_section_size = init_packet->msg.
				v1_msg.send_send_buf_complete.section_size;
	अगर (net_device->send_section_size < NETVSC_MTU_MIN) अणु
		netdev_err(ndev, "invalid send_section_size %u\n",
			   net_device->send_section_size);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* Section count is simply the size भागided by the section size. */
	net_device->send_section_cnt = buf_size / net_device->send_section_size;

	netdev_dbg(ndev, "Send section size: %d, Section count:%d\n",
		   net_device->send_section_size, net_device->send_section_cnt);

	/* Setup state क्रम managing the send buffer. */
	map_words = DIV_ROUND_UP(net_device->send_section_cnt, BITS_PER_LONG);

	net_device->send_section_map = kसुस्मृति(map_words, माप(uदीर्घ), GFP_KERNEL);
	अगर (net_device->send_section_map == शून्य) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	जाओ निकास;

cleanup:
	netvsc_revoke_recv_buf(device, net_device, ndev);
	netvsc_revoke_send_buf(device, net_device, ndev);
	netvsc_tearकरोwn_recv_gpadl(device, net_device, ndev);
	netvsc_tearकरोwn_send_gpadl(device, net_device, ndev);

निकास:
	वापस ret;
पूर्ण

/* Negotiate NVSP protocol version */
अटल पूर्णांक negotiate_nvsp_ver(काष्ठा hv_device *device,
			      काष्ठा netvsc_device *net_device,
			      काष्ठा nvsp_message *init_packet,
			      u32 nvsp_ver)
अणु
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	पूर्णांक ret;

	स_रखो(init_packet, 0, माप(काष्ठा nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG_TYPE_INIT;
	init_packet->msg.init_msg.init.min_protocol_ver = nvsp_ver;
	init_packet->msg.init_msg.init.max_protocol_ver = nvsp_ver;
	trace_nvsp_send(ndev, init_packet);

	/* Send the init request */
	ret = vmbus_sendpacket(device->channel, init_packet,
			       माप(काष्ठा nvsp_message),
			       (अचिन्हित दीर्घ)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);

	अगर (ret != 0)
		वापस ret;

	रुको_क्रम_completion(&net_device->channel_init_रुको);

	अगर (init_packet->msg.init_msg.init_complete.status !=
	    NVSP_STAT_SUCCESS)
		वापस -EINVAL;

	अगर (nvsp_ver == NVSP_PROTOCOL_VERSION_1)
		वापस 0;

	/* NVSPv2 or later: Send NDIS config */
	स_रखो(init_packet, 0, माप(काष्ठा nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG2_TYPE_SEND_NDIS_CONFIG;
	init_packet->msg.v2_msg.send_ndis_config.mtu = ndev->mtu + ETH_HLEN;
	init_packet->msg.v2_msg.send_ndis_config.capability.ieee8021q = 1;

	अगर (nvsp_ver >= NVSP_PROTOCOL_VERSION_5) अणु
		अगर (hv_is_isolation_supported())
			netdev_info(ndev, "SR-IOV not advertised by guests on the host supporting isolation\n");
		अन्यथा
			init_packet->msg.v2_msg.send_ndis_config.capability.sriov = 1;

		/* Teaming bit is needed to receive link speed updates */
		init_packet->msg.v2_msg.send_ndis_config.capability.teaming = 1;
	पूर्ण

	अगर (nvsp_ver >= NVSP_PROTOCOL_VERSION_61)
		init_packet->msg.v2_msg.send_ndis_config.capability.rsc = 1;

	trace_nvsp_send(ndev, init_packet);

	ret = vmbus_sendpacket(device->channel, init_packet,
				माप(काष्ठा nvsp_message),
				VMBUS_RQST_ID_NO_RESPONSE,
				VM_PKT_DATA_INBAND, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक netvsc_connect_vsp(काष्ठा hv_device *device,
			      काष्ठा netvsc_device *net_device,
			      स्थिर काष्ठा netvsc_device_info *device_info)
अणु
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	अटल स्थिर u32 ver_list[] = अणु
		NVSP_PROTOCOL_VERSION_1, NVSP_PROTOCOL_VERSION_2,
		NVSP_PROTOCOL_VERSION_4, NVSP_PROTOCOL_VERSION_5,
		NVSP_PROTOCOL_VERSION_6, NVSP_PROTOCOL_VERSION_61
	पूर्ण;
	काष्ठा nvsp_message *init_packet;
	पूर्णांक ndis_version, i, ret;

	init_packet = &net_device->channel_init_pkt;

	/* Negotiate the latest NVSP protocol supported */
	क्रम (i = ARRAY_SIZE(ver_list) - 1; i >= 0; i--)
		अगर (negotiate_nvsp_ver(device, net_device, init_packet,
				       ver_list[i])  == 0) अणु
			net_device->nvsp_version = ver_list[i];
			अवरोध;
		पूर्ण

	अगर (i < 0) अणु
		ret = -EPROTO;
		जाओ cleanup;
	पूर्ण

	अगर (hv_is_isolation_supported() && net_device->nvsp_version < NVSP_PROTOCOL_VERSION_61) अणु
		netdev_err(ndev, "Invalid NVSP version 0x%x (expected >= 0x%x) from the host supporting isolation\n",
			   net_device->nvsp_version, NVSP_PROTOCOL_VERSION_61);
		ret = -EPROTO;
		जाओ cleanup;
	पूर्ण

	pr_debug("Negotiated NVSP version:%x\n", net_device->nvsp_version);

	/* Send the ndis version */
	स_रखो(init_packet, 0, माप(काष्ठा nvsp_message));

	अगर (net_device->nvsp_version <= NVSP_PROTOCOL_VERSION_4)
		ndis_version = 0x00060001;
	अन्यथा
		ndis_version = 0x0006001e;

	init_packet->hdr.msg_type = NVSP_MSG1_TYPE_SEND_NDIS_VER;
	init_packet->msg.v1_msg.
		send_ndis_ver.ndis_major_ver =
				(ndis_version & 0xFFFF0000) >> 16;
	init_packet->msg.v1_msg.
		send_ndis_ver.ndis_minor_ver =
				ndis_version & 0xFFFF;

	trace_nvsp_send(ndev, init_packet);

	/* Send the init request */
	ret = vmbus_sendpacket(device->channel, init_packet,
				माप(काष्ठा nvsp_message),
				VMBUS_RQST_ID_NO_RESPONSE,
				VM_PKT_DATA_INBAND, 0);
	अगर (ret != 0)
		जाओ cleanup;


	ret = netvsc_init_buf(device, net_device, device_info);

cleanup:
	वापस ret;
पूर्ण

/*
 * netvsc_device_हटाओ - Callback when the root bus device is हटाओd
 */
व्योम netvsc_device_हटाओ(काष्ठा hv_device *device)
अणु
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);
	काष्ठा netvsc_device *net_device
		= rtnl_dereference(net_device_ctx->nvdev);
	पूर्णांक i;

	/*
	 * Revoke receive buffer. If host is pre-Win2016 then tear करोwn
	 * receive buffer GPADL. Do the same क्रम send buffer.
	 */
	netvsc_revoke_recv_buf(device, net_device, ndev);
	अगर (vmbus_proto_version < VERSION_WIN10)
		netvsc_tearकरोwn_recv_gpadl(device, net_device, ndev);

	netvsc_revoke_send_buf(device, net_device, ndev);
	अगर (vmbus_proto_version < VERSION_WIN10)
		netvsc_tearकरोwn_send_gpadl(device, net_device, ndev);

	RCU_INIT_POINTER(net_device_ctx->nvdev, शून्य);

	/* Disable NAPI and disassociate its context from the device. */
	क्रम (i = 0; i < net_device->num_chn; i++) अणु
		/* See also vmbus_reset_channel_cb(). */
		napi_disable(&net_device->chan_table[i].napi);
		netअगर_napi_del(&net_device->chan_table[i].napi);
	पूर्ण

	/*
	 * At this poपूर्णांक, no one should be accessing net_device
	 * except in here
	 */
	netdev_dbg(ndev, "net device safe to remove\n");

	/* Now, we can बंद the channel safely */
	vmbus_बंद(device->channel);

	/*
	 * If host is Win2016 or higher then we करो the GPADL tear करोwn
	 * here after VMBus is बंदd.
	*/
	अगर (vmbus_proto_version >= VERSION_WIN10) अणु
		netvsc_tearकरोwn_recv_gpadl(device, net_device, ndev);
		netvsc_tearकरोwn_send_gpadl(device, net_device, ndev);
	पूर्ण

	/* Release all resources */
	मुक्त_netvsc_device_rcu(net_device);
पूर्ण

#घोषणा RING_AVAIL_PERCENT_HIWATER 20
#घोषणा RING_AVAIL_PERCENT_LOWATER 10

अटल अंतरभूत व्योम netvsc_मुक्त_send_slot(काष्ठा netvsc_device *net_device,
					 u32 index)
अणु
	sync_change_bit(index, net_device->send_section_map);
पूर्ण

अटल व्योम netvsc_send_tx_complete(काष्ठा net_device *ndev,
				    काष्ठा netvsc_device *net_device,
				    काष्ठा vmbus_channel *channel,
				    स्थिर काष्ठा vmpacket_descriptor *desc,
				    पूर्णांक budget)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	u16 q_idx = 0;
	पूर्णांक queue_sends;
	u64 cmd_rqst;

	cmd_rqst = vmbus_request_addr(&channel->requestor, (u64)desc->trans_id);
	अगर (cmd_rqst == VMBUS_RQST_ERROR) अणु
		netdev_err(ndev, "Incorrect transaction id\n");
		वापस;
	पूर्ण

	skb = (काष्ठा sk_buff *)(अचिन्हित दीर्घ)cmd_rqst;

	/* Notअगरy the layer above us */
	अगर (likely(skb)) अणु
		स्थिर काष्ठा hv_netvsc_packet *packet
			= (काष्ठा hv_netvsc_packet *)skb->cb;
		u32 send_index = packet->send_buf_index;
		काष्ठा netvsc_stats *tx_stats;

		अगर (send_index != NETVSC_INVALID_INDEX)
			netvsc_मुक्त_send_slot(net_device, send_index);
		q_idx = packet->q_idx;

		tx_stats = &net_device->chan_table[q_idx].tx_stats;

		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->packets += packet->total_packets;
		tx_stats->bytes += packet->total_bytes;
		u64_stats_update_end(&tx_stats->syncp);

		napi_consume_skb(skb, budget);
	पूर्ण

	queue_sends =
		atomic_dec_वापस(&net_device->chan_table[q_idx].queue_sends);

	अगर (unlikely(net_device->destroy)) अणु
		अगर (queue_sends == 0)
			wake_up(&net_device->रुको_drain);
	पूर्ण अन्यथा अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(ndev, q_idx);

		अगर (netअगर_tx_queue_stopped(txq) && !net_device->tx_disable &&
		    (hv_get_avail_to_ग_लिखो_percent(&channel->outbound) >
		     RING_AVAIL_PERCENT_HIWATER || queue_sends < 1)) अणु
			netअगर_tx_wake_queue(txq);
			ndev_ctx->eth_stats.wake_queue++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम netvsc_send_completion(काष्ठा net_device *ndev,
				   काष्ठा netvsc_device *net_device,
				   काष्ठा vmbus_channel *incoming_channel,
				   स्थिर काष्ठा vmpacket_descriptor *desc,
				   पूर्णांक budget)
अणु
	स्थिर काष्ठा nvsp_message *nvsp_packet;
	u32 msglen = hv_pkt_datalen(desc);
	काष्ठा nvsp_message *pkt_rqst;
	u64 cmd_rqst;

	/* First check अगर this is a VMBUS completion without data payload */
	अगर (!msglen) अणु
		cmd_rqst = vmbus_request_addr(&incoming_channel->requestor,
					      (u64)desc->trans_id);
		अगर (cmd_rqst == VMBUS_RQST_ERROR) अणु
			netdev_err(ndev, "Invalid transaction id\n");
			वापस;
		पूर्ण

		pkt_rqst = (काष्ठा nvsp_message *)(uपूर्णांकptr_t)cmd_rqst;
		चयन (pkt_rqst->hdr.msg_type) अणु
		हाल NVSP_MSG4_TYPE_SWITCH_DATA_PATH:
			complete(&net_device->channel_init_रुको);
			अवरोध;

		शेष:
			netdev_err(ndev, "Unexpected VMBUS completion!!\n");
		पूर्ण
		वापस;
	पूर्ण

	/* Ensure packet is big enough to पढ़ो header fields */
	अगर (msglen < माप(काष्ठा nvsp_message_header)) अणु
		netdev_err(ndev, "nvsp_message length too small: %u\n", msglen);
		वापस;
	पूर्ण

	nvsp_packet = hv_pkt_data(desc);
	चयन (nvsp_packet->hdr.msg_type) अणु
	हाल NVSP_MSG_TYPE_INIT_COMPLETE:
		अगर (msglen < माप(काष्ठा nvsp_message_header) +
				माप(काष्ठा nvsp_message_init_complete)) अणु
			netdev_err(ndev, "nvsp_msg length too small: %u\n",
				   msglen);
			वापस;
		पूर्ण
		fallthrough;

	हाल NVSP_MSG1_TYPE_SEND_RECV_BUF_COMPLETE:
		अगर (msglen < माप(काष्ठा nvsp_message_header) +
				माप(काष्ठा nvsp_1_message_send_receive_buffer_complete)) अणु
			netdev_err(ndev, "nvsp_msg1 length too small: %u\n",
				   msglen);
			वापस;
		पूर्ण
		fallthrough;

	हाल NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE:
		अगर (msglen < माप(काष्ठा nvsp_message_header) +
				माप(काष्ठा nvsp_1_message_send_send_buffer_complete)) अणु
			netdev_err(ndev, "nvsp_msg1 length too small: %u\n",
				   msglen);
			वापस;
		पूर्ण
		fallthrough;

	हाल NVSP_MSG5_TYPE_SUBCHANNEL:
		अगर (msglen < माप(काष्ठा nvsp_message_header) +
				माप(काष्ठा nvsp_5_subchannel_complete)) अणु
			netdev_err(ndev, "nvsp_msg5 length too small: %u\n",
				   msglen);
			वापस;
		पूर्ण
		/* Copy the response back */
		स_नकल(&net_device->channel_init_pkt, nvsp_packet,
		       माप(काष्ठा nvsp_message));
		complete(&net_device->channel_init_रुको);
		अवरोध;

	हाल NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE:
		netvsc_send_tx_complete(ndev, net_device, incoming_channel,
					desc, budget);
		अवरोध;

	शेष:
		netdev_err(ndev,
			   "Unknown send completion type %d received!!\n",
			   nvsp_packet->hdr.msg_type);
	पूर्ण
पूर्ण

अटल u32 netvsc_get_next_send_section(काष्ठा netvsc_device *net_device)
अणु
	अचिन्हित दीर्घ *map_addr = net_device->send_section_map;
	अचिन्हित पूर्णांक i;

	क्रम_each_clear_bit(i, map_addr, net_device->send_section_cnt) अणु
		अगर (sync_test_and_set_bit(i, map_addr) == 0)
			वापस i;
	पूर्ण

	वापस NETVSC_INVALID_INDEX;
पूर्ण

अटल व्योम netvsc_copy_to_send_buf(काष्ठा netvsc_device *net_device,
				    अचिन्हित पूर्णांक section_index,
				    u32 pend_size,
				    काष्ठा hv_netvsc_packet *packet,
				    काष्ठा rndis_message *rndis_msg,
				    काष्ठा hv_page_buffer *pb,
				    bool xmit_more)
अणु
	अक्षर *start = net_device->send_buf;
	अक्षर *dest = start + (section_index * net_device->send_section_size)
		     + pend_size;
	पूर्णांक i;
	u32 padding = 0;
	u32 page_count = packet->cp_partial ? packet->rmsg_pgcnt :
		packet->page_buf_cnt;
	u32 reमुख्य;

	/* Add padding */
	reमुख्य = packet->total_data_buflen & (net_device->pkt_align - 1);
	अगर (xmit_more && reमुख्य) अणु
		padding = net_device->pkt_align - reमुख्य;
		rndis_msg->msg_len += padding;
		packet->total_data_buflen += padding;
	पूर्ण

	क्रम (i = 0; i < page_count; i++) अणु
		अक्षर *src = phys_to_virt(pb[i].pfn << HV_HYP_PAGE_SHIFT);
		u32 offset = pb[i].offset;
		u32 len = pb[i].len;

		स_नकल(dest, (src + offset), len);
		dest += len;
	पूर्ण

	अगर (padding)
		स_रखो(dest, 0, padding);
पूर्ण

अटल अंतरभूत पूर्णांक netvsc_send_pkt(
	काष्ठा hv_device *device,
	काष्ठा hv_netvsc_packet *packet,
	काष्ठा netvsc_device *net_device,
	काष्ठा hv_page_buffer *pb,
	काष्ठा sk_buff *skb)
अणु
	काष्ठा nvsp_message nvmsg;
	काष्ठा nvsp_1_message_send_rndis_packet *rpkt =
		&nvmsg.msg.v1_msg.send_rndis_pkt;
	काष्ठा netvsc_channel * स्थिर nvchan =
		&net_device->chan_table[packet->q_idx];
	काष्ठा vmbus_channel *out_channel = nvchan->channel;
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(ndev, packet->q_idx);
	u64 req_id;
	पूर्णांक ret;
	u32 ring_avail = hv_get_avail_to_ग_लिखो_percent(&out_channel->outbound);

	स_रखो(&nvmsg, 0, माप(काष्ठा nvsp_message));
	nvmsg.hdr.msg_type = NVSP_MSG1_TYPE_SEND_RNDIS_PKT;
	अगर (skb)
		rpkt->channel_type = 0;		/* 0 is RMC_DATA */
	अन्यथा
		rpkt->channel_type = 1;		/* 1 is RMC_CONTROL */

	rpkt->send_buf_section_index = packet->send_buf_index;
	अगर (packet->send_buf_index == NETVSC_INVALID_INDEX)
		rpkt->send_buf_section_size = 0;
	अन्यथा
		rpkt->send_buf_section_size = packet->total_data_buflen;

	req_id = (uदीर्घ)skb;

	अगर (out_channel->rescind)
		वापस -ENODEV;

	trace_nvsp_send_pkt(ndev, out_channel, rpkt);

	अगर (packet->page_buf_cnt) अणु
		अगर (packet->cp_partial)
			pb += packet->rmsg_pgcnt;

		ret = vmbus_sendpacket_pagebuffer(out_channel,
						  pb, packet->page_buf_cnt,
						  &nvmsg, माप(nvmsg),
						  req_id);
	पूर्ण अन्यथा अणु
		ret = vmbus_sendpacket(out_channel,
				       &nvmsg, माप(nvmsg),
				       req_id, VM_PKT_DATA_INBAND,
				       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	पूर्ण

	अगर (ret == 0) अणु
		atomic_inc_वापस(&nvchan->queue_sends);

		अगर (ring_avail < RING_AVAIL_PERCENT_LOWATER) अणु
			netअगर_tx_stop_queue(txq);
			ndev_ctx->eth_stats.stop_queue++;
		पूर्ण
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		netअगर_tx_stop_queue(txq);
		ndev_ctx->eth_stats.stop_queue++;
	पूर्ण अन्यथा अणु
		netdev_err(ndev,
			   "Unable to send packet pages %u len %u, ret %d\n",
			   packet->page_buf_cnt, packet->total_data_buflen,
			   ret);
	पूर्ण

	अगर (netअगर_tx_queue_stopped(txq) &&
	    atomic_पढ़ो(&nvchan->queue_sends) < 1 &&
	    !net_device->tx_disable) अणु
		netअगर_tx_wake_queue(txq);
		ndev_ctx->eth_stats.wake_queue++;
		अगर (ret == -EAGAIN)
			ret = -ENOSPC;
	पूर्ण

	वापस ret;
पूर्ण

/* Move packet out of multi send data (msd), and clear msd */
अटल अंतरभूत व्योम move_pkt_msd(काष्ठा hv_netvsc_packet **msd_send,
				काष्ठा sk_buff **msd_skb,
				काष्ठा multi_send_data *msdp)
अणु
	*msd_skb = msdp->skb;
	*msd_send = msdp->pkt;
	msdp->skb = शून्य;
	msdp->pkt = शून्य;
	msdp->count = 0;
पूर्ण

/* RCU alपढ़ोy held by caller */
/* Batching/bouncing logic is deचिन्हित to attempt to optimize
 * perक्रमmance.
 *
 * For small, non-LSO packets we copy the packet to a send buffer
 * which is pre-रेजिस्टरed with the Hyper-V side. This enables the
 * hypervisor to aव्योम remapping the aperture to access the packet
 * descriptor and data.
 *
 * If we alपढ़ोy started using a buffer and the netdev is transmitting
 * a burst of packets, keep on copying पूर्णांकo the buffer until it is
 * full or we are करोne collecting a burst. If there is an existing
 * buffer with space क्रम the RNDIS descriptor but not the packet, copy
 * the RNDIS descriptor to the buffer, keeping the packet in place.
 *
 * If we करो batching and send more than one packet using a single
 * NetVSC message, मुक्त the SKBs of the packets copied, except क्रम the
 * last packet. This is करोne to streamline the handling of the हाल
 * where the last packet only had the RNDIS descriptor copied to the
 * send buffer, with the data poपूर्णांकers included in the NetVSC message.
 */
पूर्णांक netvsc_send(काष्ठा net_device *ndev,
		काष्ठा hv_netvsc_packet *packet,
		काष्ठा rndis_message *rndis_msg,
		काष्ठा hv_page_buffer *pb,
		काष्ठा sk_buff *skb,
		bool xdp_tx)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा netvsc_device *net_device
		= rcu_dereference_bh(ndev_ctx->nvdev);
	काष्ठा hv_device *device = ndev_ctx->device_ctx;
	पूर्णांक ret = 0;
	काष्ठा netvsc_channel *nvchan;
	u32 pktlen = packet->total_data_buflen, msd_len = 0;
	अचिन्हित पूर्णांक section_index = NETVSC_INVALID_INDEX;
	काष्ठा multi_send_data *msdp;
	काष्ठा hv_netvsc_packet *msd_send = शून्य, *cur_send = शून्य;
	काष्ठा sk_buff *msd_skb = शून्य;
	bool try_batch, xmit_more;

	/* If device is rescinded, वापस error and packet will get dropped. */
	अगर (unlikely(!net_device || net_device->destroy))
		वापस -ENODEV;

	nvchan = &net_device->chan_table[packet->q_idx];
	packet->send_buf_index = NETVSC_INVALID_INDEX;
	packet->cp_partial = false;

	/* Send a control message or XDP packet directly without accessing
	 * msd (Multi-Send Data) field which may be changed during data packet
	 * processing.
	 */
	अगर (!skb || xdp_tx)
		वापस netvsc_send_pkt(device, packet, net_device, pb, skb);

	/* batch packets in send buffer अगर possible */
	msdp = &nvchan->msd;
	अगर (msdp->pkt)
		msd_len = msdp->pkt->total_data_buflen;

	try_batch =  msd_len > 0 && msdp->count < net_device->max_pkt;
	अगर (try_batch && msd_len + pktlen + net_device->pkt_align <
	    net_device->send_section_size) अणु
		section_index = msdp->pkt->send_buf_index;

	पूर्ण अन्यथा अगर (try_batch && msd_len + packet->rmsg_size <
		   net_device->send_section_size) अणु
		section_index = msdp->pkt->send_buf_index;
		packet->cp_partial = true;

	पूर्ण अन्यथा अगर (pktlen + net_device->pkt_align <
		   net_device->send_section_size) अणु
		section_index = netvsc_get_next_send_section(net_device);
		अगर (unlikely(section_index == NETVSC_INVALID_INDEX)) अणु
			++ndev_ctx->eth_stats.tx_send_full;
		पूर्ण अन्यथा अणु
			move_pkt_msd(&msd_send, &msd_skb, msdp);
			msd_len = 0;
		पूर्ण
	पूर्ण

	/* Keep aggregating only अगर stack says more data is coming
	 * and not करोing mixed modes send and not flow blocked
	 */
	xmit_more = netdev_xmit_more() &&
		!packet->cp_partial &&
		!netअगर_xmit_stopped(netdev_get_tx_queue(ndev, packet->q_idx));

	अगर (section_index != NETVSC_INVALID_INDEX) अणु
		netvsc_copy_to_send_buf(net_device,
					section_index, msd_len,
					packet, rndis_msg, pb, xmit_more);

		packet->send_buf_index = section_index;

		अगर (packet->cp_partial) अणु
			packet->page_buf_cnt -= packet->rmsg_pgcnt;
			packet->total_data_buflen = msd_len + packet->rmsg_size;
		पूर्ण अन्यथा अणु
			packet->page_buf_cnt = 0;
			packet->total_data_buflen += msd_len;
		पूर्ण

		अगर (msdp->pkt) अणु
			packet->total_packets += msdp->pkt->total_packets;
			packet->total_bytes += msdp->pkt->total_bytes;
		पूर्ण

		अगर (msdp->skb)
			dev_consume_skb_any(msdp->skb);

		अगर (xmit_more) अणु
			msdp->skb = skb;
			msdp->pkt = packet;
			msdp->count++;
		पूर्ण अन्यथा अणु
			cur_send = packet;
			msdp->skb = शून्य;
			msdp->pkt = शून्य;
			msdp->count = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		move_pkt_msd(&msd_send, &msd_skb, msdp);
		cur_send = packet;
	पूर्ण

	अगर (msd_send) अणु
		पूर्णांक m_ret = netvsc_send_pkt(device, msd_send, net_device,
					    शून्य, msd_skb);

		अगर (m_ret != 0) अणु
			netvsc_मुक्त_send_slot(net_device,
					      msd_send->send_buf_index);
			dev_kमुक्त_skb_any(msd_skb);
		पूर्ण
	पूर्ण

	अगर (cur_send)
		ret = netvsc_send_pkt(device, cur_send, net_device, pb, skb);

	अगर (ret != 0 && section_index != NETVSC_INVALID_INDEX)
		netvsc_मुक्त_send_slot(net_device, section_index);

	वापस ret;
पूर्ण

/* Send pending recv completions */
अटल पूर्णांक send_recv_completions(काष्ठा net_device *ndev,
				 काष्ठा netvsc_device *nvdev,
				 काष्ठा netvsc_channel *nvchan)
अणु
	काष्ठा multi_recv_comp *mrc = &nvchan->mrc;
	काष्ठा recv_comp_msg अणु
		काष्ठा nvsp_message_header hdr;
		u32 status;
	पूर्ण  __packed;
	काष्ठा recv_comp_msg msg = अणु
		.hdr.msg_type = NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE,
	पूर्ण;
	पूर्णांक ret;

	जबतक (mrc->first != mrc->next) अणु
		स्थिर काष्ठा recv_comp_data *rcd
			= mrc->slots + mrc->first;

		msg.status = rcd->status;
		ret = vmbus_sendpacket(nvchan->channel, &msg, माप(msg),
				       rcd->tid, VM_PKT_COMP, 0);
		अगर (unlikely(ret)) अणु
			काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);

			++ndev_ctx->eth_stats.rx_comp_busy;
			वापस ret;
		पूर्ण

		अगर (++mrc->first == nvdev->recv_completion_cnt)
			mrc->first = 0;
	पूर्ण

	/* receive completion ring has been emptied */
	अगर (unlikely(nvdev->destroy))
		wake_up(&nvdev->रुको_drain);

	वापस 0;
पूर्ण

/* Count how many receive completions are outstanding */
अटल व्योम recv_comp_slot_avail(स्थिर काष्ठा netvsc_device *nvdev,
				 स्थिर काष्ठा multi_recv_comp *mrc,
				 u32 *filled, u32 *avail)
अणु
	u32 count = nvdev->recv_completion_cnt;

	अगर (mrc->next >= mrc->first)
		*filled = mrc->next - mrc->first;
	अन्यथा
		*filled = (count - mrc->first) + mrc->next;

	*avail = count - *filled - 1;
पूर्ण

/* Add receive complete to ring to send to host. */
अटल व्योम enq_receive_complete(काष्ठा net_device *ndev,
				 काष्ठा netvsc_device *nvdev, u16 q_idx,
				 u64 tid, u32 status)
अणु
	काष्ठा netvsc_channel *nvchan = &nvdev->chan_table[q_idx];
	काष्ठा multi_recv_comp *mrc = &nvchan->mrc;
	काष्ठा recv_comp_data *rcd;
	u32 filled, avail;

	recv_comp_slot_avail(nvdev, mrc, &filled, &avail);

	अगर (unlikely(filled > NAPI_POLL_WEIGHT)) अणु
		send_recv_completions(ndev, nvdev, nvchan);
		recv_comp_slot_avail(nvdev, mrc, &filled, &avail);
	पूर्ण

	अगर (unlikely(!avail)) अणु
		netdev_err(ndev, "Recv_comp full buf q:%hd, tid:%llx\n",
			   q_idx, tid);
		वापस;
	पूर्ण

	rcd = mrc->slots + mrc->next;
	rcd->tid = tid;
	rcd->status = status;

	अगर (++mrc->next == nvdev->recv_completion_cnt)
		mrc->next = 0;
पूर्ण

अटल पूर्णांक netvsc_receive(काष्ठा net_device *ndev,
			  काष्ठा netvsc_device *net_device,
			  काष्ठा netvsc_channel *nvchan,
			  स्थिर काष्ठा vmpacket_descriptor *desc)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);
	काष्ठा vmbus_channel *channel = nvchan->channel;
	स्थिर काष्ठा vmtransfer_page_packet_header *vmxferpage_packet
		= container_of(desc, स्थिर काष्ठा vmtransfer_page_packet_header, d);
	स्थिर काष्ठा nvsp_message *nvsp = hv_pkt_data(desc);
	u32 msglen = hv_pkt_datalen(desc);
	u16 q_idx = channel->offermsg.offer.sub_channel_index;
	अक्षर *recv_buf = net_device->recv_buf;
	u32 status = NVSP_STAT_SUCCESS;
	पूर्णांक i;
	पूर्णांक count = 0;

	/* Ensure packet is big enough to पढ़ो header fields */
	अगर (msglen < माप(काष्ठा nvsp_message_header)) अणु
		netअगर_err(net_device_ctx, rx_err, ndev,
			  "invalid nvsp header, length too small: %u\n",
			  msglen);
		वापस 0;
	पूर्ण

	/* Make sure this is a valid nvsp packet */
	अगर (unlikely(nvsp->hdr.msg_type != NVSP_MSG1_TYPE_SEND_RNDIS_PKT)) अणु
		netअगर_err(net_device_ctx, rx_err, ndev,
			  "Unknown nvsp packet type received %u\n",
			  nvsp->hdr.msg_type);
		वापस 0;
	पूर्ण

	/* Validate xfer page pkt header */
	अगर ((desc->offset8 << 3) < माप(काष्ठा vmtransfer_page_packet_header)) अणु
		netअगर_err(net_device_ctx, rx_err, ndev,
			  "Invalid xfer page pkt, offset too small: %u\n",
			  desc->offset8 << 3);
		वापस 0;
	पूर्ण

	अगर (unlikely(vmxferpage_packet->xfer_pageset_id != NETVSC_RECEIVE_BUFFER_ID)) अणु
		netअगर_err(net_device_ctx, rx_err, ndev,
			  "Invalid xfer page set id - expecting %x got %x\n",
			  NETVSC_RECEIVE_BUFFER_ID,
			  vmxferpage_packet->xfer_pageset_id);
		वापस 0;
	पूर्ण

	count = vmxferpage_packet->range_cnt;

	/* Check count क्रम a valid value */
	अगर (NETVSC_XFER_HEADER_SIZE(count) > desc->offset8 << 3) अणु
		netअगर_err(net_device_ctx, rx_err, ndev,
			  "Range count is not valid: %d\n",
			  count);
		वापस 0;
	पूर्ण

	/* Each range represents 1 RNDIS pkt that contains 1 ethernet frame */
	क्रम (i = 0; i < count; i++) अणु
		u32 offset = vmxferpage_packet->ranges[i].byte_offset;
		u32 buflen = vmxferpage_packet->ranges[i].byte_count;
		व्योम *data;
		पूर्णांक ret;

		अगर (unlikely(offset > net_device->recv_buf_size ||
			     buflen > net_device->recv_buf_size - offset)) अणु
			nvchan->rsc.cnt = 0;
			status = NVSP_STAT_FAIL;
			netअगर_err(net_device_ctx, rx_err, ndev,
				  "Packet offset:%u + len:%u too big\n",
				  offset, buflen);

			जारी;
		पूर्ण

		/* We're going to copy (sections of) the packet पूर्णांकo nvchan->recv_buf;
		 * make sure that nvchan->recv_buf is large enough to hold the packet.
		 */
		अगर (unlikely(buflen > net_device->recv_section_size)) अणु
			nvchan->rsc.cnt = 0;
			status = NVSP_STAT_FAIL;
			netअगर_err(net_device_ctx, rx_err, ndev,
				  "Packet too big: buflen=%u recv_section_size=%u\n",
				  buflen, net_device->recv_section_size);

			जारी;
		पूर्ण

		data = recv_buf + offset;

		nvchan->rsc.is_last = (i == count - 1);

		trace_rndis_recv(ndev, q_idx, data);

		/* Pass it to the upper layer */
		ret = rndis_filter_receive(ndev, net_device,
					   nvchan, data, buflen);

		अगर (unlikely(ret != NVSP_STAT_SUCCESS)) अणु
			/* Drop incomplete packet */
			nvchan->rsc.cnt = 0;
			status = NVSP_STAT_FAIL;
		पूर्ण
	पूर्ण

	enq_receive_complete(ndev, net_device, q_idx,
			     vmxferpage_packet->d.trans_id, status);

	वापस count;
पूर्ण

अटल व्योम netvsc_send_table(काष्ठा net_device *ndev,
			      काष्ठा netvsc_device *nvscdev,
			      स्थिर काष्ठा nvsp_message *nvmsg,
			      u32 msglen)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);
	u32 count, offset, *tab;
	पूर्णांक i;

	/* Ensure packet is big enough to पढ़ो send_table fields */
	अगर (msglen < माप(काष्ठा nvsp_message_header) +
		     माप(काष्ठा nvsp_5_send_indirect_table)) अणु
		netdev_err(ndev, "nvsp_v5_msg length too small: %u\n", msglen);
		वापस;
	पूर्ण

	count = nvmsg->msg.v5_msg.send_table.count;
	offset = nvmsg->msg.v5_msg.send_table.offset;

	अगर (count != VRSS_SEND_TAB_SIZE) अणु
		netdev_err(ndev, "Received wrong send-table size:%u\n", count);
		वापस;
	पूर्ण

	/* If negotiated version <= NVSP_PROTOCOL_VERSION_6, the offset may be
	 * wrong due to a host bug. So fix the offset here.
	 */
	अगर (nvscdev->nvsp_version <= NVSP_PROTOCOL_VERSION_6 &&
	    msglen >= माप(काष्ठा nvsp_message_header) +
	    माप(जोड़ nvsp_6_message_uber) + count * माप(u32))
		offset = माप(काष्ठा nvsp_message_header) +
			 माप(जोड़ nvsp_6_message_uber);

	/* Boundary check क्रम all versions */
	अगर (msglen < count * माप(u32) || offset > msglen - count * माप(u32)) अणु
		netdev_err(ndev, "Received send-table offset too big:%u\n",
			   offset);
		वापस;
	पूर्ण

	tab = (व्योम *)nvmsg + offset;

	क्रम (i = 0; i < count; i++)
		net_device_ctx->tx_table[i] = tab[i];
पूर्ण

अटल व्योम netvsc_send_vf(काष्ठा net_device *ndev,
			   स्थिर काष्ठा nvsp_message *nvmsg,
			   u32 msglen)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);

	/* Ensure packet is big enough to पढ़ो its fields */
	अगर (msglen < माप(काष्ठा nvsp_message_header) +
		     माप(काष्ठा nvsp_4_send_vf_association)) अणु
		netdev_err(ndev, "nvsp_v4_msg length too small: %u\n", msglen);
		वापस;
	पूर्ण

	net_device_ctx->vf_alloc = nvmsg->msg.v4_msg.vf_assoc.allocated;
	net_device_ctx->vf_serial = nvmsg->msg.v4_msg.vf_assoc.serial;
	netdev_info(ndev, "VF slot %u %s\n",
		    net_device_ctx->vf_serial,
		    net_device_ctx->vf_alloc ? "added" : "removed");
पूर्ण

अटल व्योम netvsc_receive_inband(काष्ठा net_device *ndev,
				  काष्ठा netvsc_device *nvscdev,
				  स्थिर काष्ठा vmpacket_descriptor *desc)
अणु
	स्थिर काष्ठा nvsp_message *nvmsg = hv_pkt_data(desc);
	u32 msglen = hv_pkt_datalen(desc);

	/* Ensure packet is big enough to पढ़ो header fields */
	अगर (msglen < माप(काष्ठा nvsp_message_header)) अणु
		netdev_err(ndev, "inband nvsp_message length too small: %u\n", msglen);
		वापस;
	पूर्ण

	चयन (nvmsg->hdr.msg_type) अणु
	हाल NVSP_MSG5_TYPE_SEND_INसूचीECTION_TABLE:
		netvsc_send_table(ndev, nvscdev, nvmsg, msglen);
		अवरोध;

	हाल NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION:
		अगर (hv_is_isolation_supported())
			netdev_err(ndev, "Ignore VF_ASSOCIATION msg from the host supporting isolation\n");
		अन्यथा
			netvsc_send_vf(ndev, nvmsg, msglen);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक netvsc_process_raw_pkt(काष्ठा hv_device *device,
				  काष्ठा netvsc_channel *nvchan,
				  काष्ठा netvsc_device *net_device,
				  काष्ठा net_device *ndev,
				  स्थिर काष्ठा vmpacket_descriptor *desc,
				  पूर्णांक budget)
अणु
	काष्ठा vmbus_channel *channel = nvchan->channel;
	स्थिर काष्ठा nvsp_message *nvmsg = hv_pkt_data(desc);

	trace_nvsp_recv(ndev, channel, nvmsg);

	चयन (desc->type) अणु
	हाल VM_PKT_COMP:
		netvsc_send_completion(ndev, net_device, channel, desc, budget);
		अवरोध;

	हाल VM_PKT_DATA_USING_XFER_PAGES:
		वापस netvsc_receive(ndev, net_device, nvchan, desc);
		अवरोध;

	हाल VM_PKT_DATA_INBAND:
		netvsc_receive_inband(ndev, net_device, desc);
		अवरोध;

	शेष:
		netdev_err(ndev, "unhandled packet type %d, tid %llx\n",
			   desc->type, desc->trans_id);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hv_device *netvsc_channel_to_device(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा vmbus_channel *primary = channel->primary_channel;

	वापस primary ? primary->device_obj : channel->device_obj;
पूर्ण

/* Network processing softirq
 * Process data in incoming ring buffer from host
 * Stops when ring is empty or budget is met or exceeded.
 */
पूर्णांक netvsc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netvsc_channel *nvchan
		= container_of(napi, काष्ठा netvsc_channel, napi);
	काष्ठा netvsc_device *net_device = nvchan->net_device;
	काष्ठा vmbus_channel *channel = nvchan->channel;
	काष्ठा hv_device *device = netvsc_channel_to_device(channel);
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	पूर्णांक work_करोne = 0;
	पूर्णांक ret;

	/* If starting a new पूर्णांकerval */
	अगर (!nvchan->desc)
		nvchan->desc = hv_pkt_iter_first(channel);

	जबतक (nvchan->desc && work_करोne < budget) अणु
		work_करोne += netvsc_process_raw_pkt(device, nvchan, net_device,
						    ndev, nvchan->desc, budget);
		nvchan->desc = hv_pkt_iter_next(channel, nvchan->desc);
	पूर्ण

	/* Send any pending receive completions */
	ret = send_recv_completions(ndev, net_device, nvchan);

	/* If it did not exhaust NAPI budget this समय
	 *  and not करोing busy poll
	 * then re-enable host पूर्णांकerrupts
	 *  and reschedule अगर ring is not empty
	 *   or sending receive completion failed.
	 */
	अगर (work_करोne < budget &&
	    napi_complete_करोne(napi, work_करोne) &&
	    (ret || hv_end_पढ़ो(&channel->inbound)) &&
	    napi_schedule_prep(napi)) अणु
		hv_begin_पढ़ो(&channel->inbound);
		__napi_schedule(napi);
	पूर्ण

	/* Driver may overshoot since multiple packets per descriptor */
	वापस min(work_करोne, budget);
पूर्ण

/* Call back when data is available in host ring buffer.
 * Processing is deferred until network softirq (NAPI)
 */
व्योम netvsc_channel_cb(व्योम *context)
अणु
	काष्ठा netvsc_channel *nvchan = context;
	काष्ठा vmbus_channel *channel = nvchan->channel;
	काष्ठा hv_ring_buffer_info *rbi = &channel->inbound;

	/* preload first vmpacket descriptor */
	prefetch(hv_get_ring_buffer(rbi) + rbi->priv_पढ़ो_index);

	अगर (napi_schedule_prep(&nvchan->napi)) अणु
		/* disable पूर्णांकerrupts from host */
		hv_begin_पढ़ो(rbi);

		__napi_schedule_irqoff(&nvchan->napi);
	पूर्ण
पूर्ण

/*
 * netvsc_device_add - Callback when the device beदीर्घing to this
 * driver is added
 */
काष्ठा netvsc_device *netvsc_device_add(काष्ठा hv_device *device,
				स्थिर काष्ठा netvsc_device_info *device_info)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा netvsc_device *net_device;
	काष्ठा net_device *ndev = hv_get_drvdata(device);
	काष्ठा net_device_context *net_device_ctx = netdev_priv(ndev);

	net_device = alloc_net_device();
	अगर (!net_device)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < VRSS_SEND_TAB_SIZE; i++)
		net_device_ctx->tx_table[i] = 0;

	/* Because the device uses NAPI, all the पूर्णांकerrupt batching and
	 * control is करोne via Net softirq, not the channel handling
	 */
	set_channel_पढ़ो_mode(device->channel, HV_CALL_ISR);

	/* If we're reखोलोing the device we may have multiple queues, fill the
	 * chn_table with the शेष channel to use it beक्रमe subchannels are
	 * खोलोed.
	 * Initialize the channel state beक्रमe we खोलो;
	 * we can be पूर्णांकerrupted as soon as we खोलो the channel.
	 */

	क्रम (i = 0; i < VRSS_CHANNEL_MAX; i++) अणु
		काष्ठा netvsc_channel *nvchan = &net_device->chan_table[i];

		nvchan->channel = device->channel;
		nvchan->net_device = net_device;
		u64_stats_init(&nvchan->tx_stats.syncp);
		u64_stats_init(&nvchan->rx_stats.syncp);

		ret = xdp_rxq_info_reg(&nvchan->xdp_rxq, ndev, i, 0);

		अगर (ret) अणु
			netdev_err(ndev, "xdp_rxq_info_reg fail: %d\n", ret);
			जाओ cleanup2;
		पूर्ण

		ret = xdp_rxq_info_reg_mem_model(&nvchan->xdp_rxq,
						 MEM_TYPE_PAGE_SHARED, शून्य);

		अगर (ret) अणु
			netdev_err(ndev, "xdp reg_mem_model fail: %d\n", ret);
			जाओ cleanup2;
		पूर्ण
	पूर्ण

	/* Enable NAPI handler beक्रमe init callbacks */
	netअगर_napi_add(ndev, &net_device->chan_table[0].napi,
		       netvsc_poll, NAPI_POLL_WEIGHT);

	/* Open the channel */
	device->channel->rqstor_size = netvsc_rqstor_size(netvsc_ring_bytes);
	ret = vmbus_खोलो(device->channel, netvsc_ring_bytes,
			 netvsc_ring_bytes,  शून्य, 0,
			 netvsc_channel_cb, net_device->chan_table);

	अगर (ret != 0) अणु
		netdev_err(ndev, "unable to open channel: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	/* Channel is खोलोed */
	netdev_dbg(ndev, "hv_netvsc channel opened successfully\n");

	napi_enable(&net_device->chan_table[0].napi);

	/* Connect with the NetVsp */
	ret = netvsc_connect_vsp(device, net_device, device_info);
	अगर (ret != 0) अणु
		netdev_err(ndev,
			"unable to connect to NetVSP - %d\n", ret);
		जाओ बंद;
	पूर्ण

	/* Writing nvdev poपूर्णांकer unlocks netvsc_send(), make sure chn_table is
	 * populated.
	 */
	rcu_assign_poपूर्णांकer(net_device_ctx->nvdev, net_device);

	वापस net_device;

बंद:
	RCU_INIT_POINTER(net_device_ctx->nvdev, शून्य);
	napi_disable(&net_device->chan_table[0].napi);

	/* Now, we can बंद the channel safely */
	vmbus_बंद(device->channel);

cleanup:
	netअगर_napi_del(&net_device->chan_table[0].napi);

cleanup2:
	मुक्त_netvsc_device(&net_device->rcu);

	वापस ERR_PTR(ret);
पूर्ण
