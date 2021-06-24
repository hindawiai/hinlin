<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Networking over Thunderbolt cable using Apple ThunderboltIP protocol
 *
 * Copyright (C) 2017, Intel Corporation
 * Authors: Amir Levy <amir.jer.levy@पूर्णांकel.com>
 *          Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jhash.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sizes.h>
#समावेश <linux/thunderbolt.h>
#समावेश <linux/uuid.h>
#समावेश <linux/workqueue.h>

#समावेश <net/ip6_checksum.h>

/* Protocol समयouts in ms */
#घोषणा TBNET_LOGIN_DELAY	4500
#घोषणा TBNET_LOGIN_TIMEOUT	500
#घोषणा TBNET_LOGOUT_TIMEOUT	1000

#घोषणा TBNET_RING_SIZE		256
#घोषणा TBNET_LOGIN_RETRIES	60
#घोषणा TBNET_LOGOUT_RETRIES	10
#घोषणा TBNET_MATCH_FRAGS_ID	BIT(1)
#घोषणा TBNET_64K_FRAMES	BIT(2)
#घोषणा TBNET_MAX_MTU		SZ_64K
#घोषणा TBNET_FRAME_SIZE	SZ_4K
#घोषणा TBNET_MAX_PAYLOAD_SIZE	\
	(TBNET_FRAME_SIZE - माप(काष्ठा thunderbolt_ip_frame_header))
/* Rx packets need to hold space क्रम skb_shared_info */
#घोषणा TBNET_RX_MAX_SIZE	\
	(TBNET_FRAME_SIZE + SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))
#घोषणा TBNET_RX_PAGE_ORDER	get_order(TBNET_RX_MAX_SIZE)
#घोषणा TBNET_RX_PAGE_SIZE	(PAGE_SIZE << TBNET_RX_PAGE_ORDER)

#घोषणा TBNET_L0_PORT_NUM(route) ((route) & GENMASK(5, 0))

/**
 * काष्ठा thunderbolt_ip_frame_header - Header क्रम each Thunderbolt frame
 * @frame_size: size of the data with the frame
 * @frame_index: running index on the frames
 * @frame_id: ID of the frame to match frames to specअगरic packet
 * @frame_count: how many frames assembles a full packet
 *
 * Each data frame passed to the high-speed DMA ring has this header. If
 * the XDoमुख्य network directory announces that %TBNET_MATCH_FRAGS_ID is
 * supported then @frame_id is filled, otherwise it stays %0.
 */
काष्ठा thunderbolt_ip_frame_header अणु
	u32 frame_size;
	u16 frame_index;
	u16 frame_id;
	u32 frame_count;
पूर्ण;

क्रमागत thunderbolt_ip_frame_pdf अणु
	TBIP_PDF_FRAME_START = 1,
	TBIP_PDF_FRAME_END,
पूर्ण;

क्रमागत thunderbolt_ip_type अणु
	TBIP_LOGIN,
	TBIP_LOGIN_RESPONSE,
	TBIP_LOGOUT,
	TBIP_STATUS,
पूर्ण;

काष्ठा thunderbolt_ip_header अणु
	u32 route_hi;
	u32 route_lo;
	u32 length_sn;
	uuid_t uuid;
	uuid_t initiator_uuid;
	uuid_t target_uuid;
	u32 type;
	u32 command_id;
पूर्ण;

#घोषणा TBIP_HDR_LENGTH_MASK		GENMASK(5, 0)
#घोषणा TBIP_HDR_SN_MASK		GENMASK(28, 27)
#घोषणा TBIP_HDR_SN_SHIFT		27

काष्ठा thunderbolt_ip_login अणु
	काष्ठा thunderbolt_ip_header hdr;
	u32 proto_version;
	u32 transmit_path;
	u32 reserved[4];
पूर्ण;

#घोषणा TBIP_LOGIN_PROTO_VERSION	1

काष्ठा thunderbolt_ip_login_response अणु
	काष्ठा thunderbolt_ip_header hdr;
	u32 status;
	u32 receiver_mac[2];
	u32 receiver_mac_len;
	u32 reserved[4];
पूर्ण;

काष्ठा thunderbolt_ip_logout अणु
	काष्ठा thunderbolt_ip_header hdr;
पूर्ण;

काष्ठा thunderbolt_ip_status अणु
	काष्ठा thunderbolt_ip_header hdr;
	u32 status;
पूर्ण;

काष्ठा tbnet_stats अणु
	u64 tx_packets;
	u64 rx_packets;
	u64 tx_bytes;
	u64 rx_bytes;
	u64 rx_errors;
	u64 tx_errors;
	u64 rx_length_errors;
	u64 rx_over_errors;
	u64 rx_crc_errors;
	u64 rx_missed_errors;
पूर्ण;

काष्ठा tbnet_frame अणु
	काष्ठा net_device *dev;
	काष्ठा page *page;
	काष्ठा ring_frame frame;
पूर्ण;

काष्ठा tbnet_ring अणु
	काष्ठा tbnet_frame frames[TBNET_RING_SIZE];
	अचिन्हित पूर्णांक cons;
	अचिन्हित पूर्णांक prod;
	काष्ठा tb_ring *ring;
पूर्ण;

/**
 * काष्ठा tbnet - ThunderboltIP network driver निजी data
 * @svc: XDoमुख्य service the driver is bound to
 * @xd: XDoमुख्य the service bदीर्घs to
 * @handler: ThunderboltIP configuration protocol handler
 * @dev: Networking device
 * @napi: NAPI काष्ठाure क्रम Rx polling
 * @stats: Network statistics
 * @skb: Network packet that is currently processed on Rx path
 * @command_id: ID used क्रम next configuration protocol packet
 * @login_sent: ThunderboltIP login message successfully sent
 * @login_received: ThunderboltIP login message received from the remote
 *		    host
 * @local_transmit_path: HopID we are using to send out packets
 * @remote_transmit_path: HopID the other end is using to send packets to us
 * @connection_lock: Lock serializing access to @login_sent,
 *		     @login_received and @transmit_path.
 * @login_retries: Number of login retries currently करोne
 * @login_work: Worker to send ThunderboltIP login packets
 * @connected_work: Worker that finalizes the ThunderboltIP connection
 *		    setup and enables DMA paths क्रम high speed data
 *		    transfers
 * @disconnect_work: Worker that handles tearing करोwn the ThunderboltIP
 *		     connection
 * @rx_hdr: Copy of the currently processed Rx frame. Used when a
 *	    network packet consists of multiple Thunderbolt frames.
 *	    In host byte order.
 * @rx_ring: Software ring holding Rx frames
 * @frame_id: Frame ID use क्रम next Tx packet
 *            (अगर %TBNET_MATCH_FRAGS_ID is supported in both ends)
 * @tx_ring: Software ring holding Tx frames
 */
काष्ठा tbnet अणु
	स्थिर काष्ठा tb_service *svc;
	काष्ठा tb_xकरोमुख्य *xd;
	काष्ठा tb_protocol_handler handler;
	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा tbnet_stats stats;
	काष्ठा sk_buff *skb;
	atomic_t command_id;
	bool login_sent;
	bool login_received;
	पूर्णांक local_transmit_path;
	पूर्णांक remote_transmit_path;
	काष्ठा mutex connection_lock;
	पूर्णांक login_retries;
	काष्ठा delayed_work login_work;
	काष्ठा work_काष्ठा connected_work;
	काष्ठा work_काष्ठा disconnect_work;
	काष्ठा thunderbolt_ip_frame_header rx_hdr;
	काष्ठा tbnet_ring rx_ring;
	atomic_t frame_id;
	काष्ठा tbnet_ring tx_ring;
पूर्ण;

/* Network property directory UUID: c66189ca-1cce-4195-bdb8-49592e5f5a4f */
अटल स्थिर uuid_t tbnet_dir_uuid =
	UUID_INIT(0xc66189ca, 0x1cce, 0x4195,
		  0xbd, 0xb8, 0x49, 0x59, 0x2e, 0x5f, 0x5a, 0x4f);

/* ThunderboltIP protocol UUID: 798f589e-3616-8a47-97c6-5664a920c8dd */
अटल स्थिर uuid_t tbnet_svc_uuid =
	UUID_INIT(0x798f589e, 0x3616, 0x8a47,
		  0x97, 0xc6, 0x56, 0x64, 0xa9, 0x20, 0xc8, 0xdd);

अटल काष्ठा tb_property_dir *tbnet_dir;

अटल व्योम tbnet_fill_header(काष्ठा thunderbolt_ip_header *hdr, u64 route,
	u8 sequence, स्थिर uuid_t *initiator_uuid, स्थिर uuid_t *target_uuid,
	क्रमागत thunderbolt_ip_type type, माप_प्रकार size, u32 command_id)
अणु
	u32 length_sn;

	/* Length करोes not include route_hi/lo and length_sn fields */
	length_sn = (size - 3 * 4) / 4;
	length_sn |= (sequence << TBIP_HDR_SN_SHIFT) & TBIP_HDR_SN_MASK;

	hdr->route_hi = upper_32_bits(route);
	hdr->route_lo = lower_32_bits(route);
	hdr->length_sn = length_sn;
	uuid_copy(&hdr->uuid, &tbnet_svc_uuid);
	uuid_copy(&hdr->initiator_uuid, initiator_uuid);
	uuid_copy(&hdr->target_uuid, target_uuid);
	hdr->type = type;
	hdr->command_id = command_id;
पूर्ण

अटल पूर्णांक tbnet_login_response(काष्ठा tbnet *net, u64 route, u8 sequence,
				u32 command_id)
अणु
	काष्ठा thunderbolt_ip_login_response reply;
	काष्ठा tb_xकरोमुख्य *xd = net->xd;

	स_रखो(&reply, 0, माप(reply));
	tbnet_fill_header(&reply.hdr, route, sequence, xd->local_uuid,
			  xd->remote_uuid, TBIP_LOGIN_RESPONSE, माप(reply),
			  command_id);
	स_नकल(reply.receiver_mac, net->dev->dev_addr, ETH_ALEN);
	reply.receiver_mac_len = ETH_ALEN;

	वापस tb_xकरोमुख्य_response(xd, &reply, माप(reply),
				   TB_CFG_PKG_XDOMAIN_RESP);
पूर्ण

अटल पूर्णांक tbnet_login_request(काष्ठा tbnet *net, u8 sequence)
अणु
	काष्ठा thunderbolt_ip_login_response reply;
	काष्ठा thunderbolt_ip_login request;
	काष्ठा tb_xकरोमुख्य *xd = net->xd;

	स_रखो(&request, 0, माप(request));
	tbnet_fill_header(&request.hdr, xd->route, sequence, xd->local_uuid,
			  xd->remote_uuid, TBIP_LOGIN, माप(request),
			  atomic_inc_वापस(&net->command_id));

	request.proto_version = TBIP_LOGIN_PROTO_VERSION;
	request.transmit_path = net->local_transmit_path;

	वापस tb_xकरोमुख्य_request(xd, &request, माप(request),
				  TB_CFG_PKG_XDOMAIN_RESP, &reply,
				  माप(reply), TB_CFG_PKG_XDOMAIN_RESP,
				  TBNET_LOGIN_TIMEOUT);
पूर्ण

अटल पूर्णांक tbnet_logout_response(काष्ठा tbnet *net, u64 route, u8 sequence,
				 u32 command_id)
अणु
	काष्ठा thunderbolt_ip_status reply;
	काष्ठा tb_xकरोमुख्य *xd = net->xd;

	स_रखो(&reply, 0, माप(reply));
	tbnet_fill_header(&reply.hdr, route, sequence, xd->local_uuid,
			  xd->remote_uuid, TBIP_STATUS, माप(reply),
			  atomic_inc_वापस(&net->command_id));
	वापस tb_xकरोमुख्य_response(xd, &reply, माप(reply),
				   TB_CFG_PKG_XDOMAIN_RESP);
पूर्ण

अटल पूर्णांक tbnet_logout_request(काष्ठा tbnet *net)
अणु
	काष्ठा thunderbolt_ip_logout request;
	काष्ठा thunderbolt_ip_status reply;
	काष्ठा tb_xकरोमुख्य *xd = net->xd;

	स_रखो(&request, 0, माप(request));
	tbnet_fill_header(&request.hdr, xd->route, 0, xd->local_uuid,
			  xd->remote_uuid, TBIP_LOGOUT, माप(request),
			  atomic_inc_वापस(&net->command_id));

	वापस tb_xकरोमुख्य_request(xd, &request, माप(request),
				  TB_CFG_PKG_XDOMAIN_RESP, &reply,
				  माप(reply), TB_CFG_PKG_XDOMAIN_RESP,
				  TBNET_LOGOUT_TIMEOUT);
पूर्ण

अटल व्योम start_login(काष्ठा tbnet *net)
अणु
	mutex_lock(&net->connection_lock);
	net->login_sent = false;
	net->login_received = false;
	mutex_unlock(&net->connection_lock);

	queue_delayed_work(प्रणाली_दीर्घ_wq, &net->login_work,
			   msecs_to_jअगरfies(1000));
पूर्ण

अटल व्योम stop_login(काष्ठा tbnet *net)
अणु
	cancel_delayed_work_sync(&net->login_work);
	cancel_work_sync(&net->connected_work);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tbnet_frame_size(स्थिर काष्ठा tbnet_frame *tf)
अणु
	वापस tf->frame.size ? : TBNET_FRAME_SIZE;
पूर्ण

अटल व्योम tbnet_मुक्त_buffers(काष्ठा tbnet_ring *ring)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < TBNET_RING_SIZE; i++) अणु
		काष्ठा device *dma_dev = tb_ring_dma_device(ring->ring);
		काष्ठा tbnet_frame *tf = &ring->frames[i];
		क्रमागत dma_data_direction dir;
		अचिन्हित पूर्णांक order;
		माप_प्रकार size;

		अगर (!tf->page)
			जारी;

		अगर (ring->ring->is_tx) अणु
			dir = DMA_TO_DEVICE;
			order = 0;
			size = TBNET_FRAME_SIZE;
		पूर्ण अन्यथा अणु
			dir = DMA_FROM_DEVICE;
			order = TBNET_RX_PAGE_ORDER;
			size = TBNET_RX_PAGE_SIZE;
		पूर्ण

		अगर (tf->frame.buffer_phy)
			dma_unmap_page(dma_dev, tf->frame.buffer_phy, size,
				       dir);

		__मुक्त_pages(tf->page, order);
		tf->page = शून्य;
	पूर्ण

	ring->cons = 0;
	ring->prod = 0;
पूर्ण

अटल व्योम tbnet_tear_करोwn(काष्ठा tbnet *net, bool send_logout)
अणु
	netअगर_carrier_off(net->dev);
	netअगर_stop_queue(net->dev);

	stop_login(net);

	mutex_lock(&net->connection_lock);

	अगर (net->login_sent && net->login_received) अणु
		पूर्णांक ret, retries = TBNET_LOGOUT_RETRIES;

		जबतक (send_logout && retries-- > 0) अणु
			ret = tbnet_logout_request(net);
			अगर (ret != -ETIMEDOUT)
				अवरोध;
		पूर्ण

		tb_ring_stop(net->rx_ring.ring);
		tb_ring_stop(net->tx_ring.ring);
		tbnet_मुक्त_buffers(&net->rx_ring);
		tbnet_मुक्त_buffers(&net->tx_ring);

		ret = tb_xकरोमुख्य_disable_paths(net->xd,
					       net->local_transmit_path,
					       net->rx_ring.ring->hop,
					       net->remote_transmit_path,
					       net->tx_ring.ring->hop);
		अगर (ret)
			netdev_warn(net->dev, "failed to disable DMA paths\n");

		tb_xकरोमुख्य_release_in_hopid(net->xd, net->remote_transmit_path);
		net->remote_transmit_path = 0;
	पूर्ण

	net->login_retries = 0;
	net->login_sent = false;
	net->login_received = false;

	mutex_unlock(&net->connection_lock);
पूर्ण

अटल पूर्णांक tbnet_handle_packet(स्थिर व्योम *buf, माप_प्रकार size, व्योम *data)
अणु
	स्थिर काष्ठा thunderbolt_ip_login *pkg = buf;
	काष्ठा tbnet *net = data;
	u32 command_id;
	पूर्णांक ret = 0;
	u32 sequence;
	u64 route;

	/* Make sure the packet is क्रम us */
	अगर (size < माप(काष्ठा thunderbolt_ip_header))
		वापस 0;
	अगर (!uuid_equal(&pkg->hdr.initiator_uuid, net->xd->remote_uuid))
		वापस 0;
	अगर (!uuid_equal(&pkg->hdr.target_uuid, net->xd->local_uuid))
		वापस 0;

	route = ((u64)pkg->hdr.route_hi << 32) | pkg->hdr.route_lo;
	route &= ~BIT_ULL(63);
	अगर (route != net->xd->route)
		वापस 0;

	sequence = pkg->hdr.length_sn & TBIP_HDR_SN_MASK;
	sequence >>= TBIP_HDR_SN_SHIFT;
	command_id = pkg->hdr.command_id;

	चयन (pkg->hdr.type) अणु
	हाल TBIP_LOGIN:
		अगर (!netअगर_running(net->dev))
			अवरोध;

		ret = tbnet_login_response(net, route, sequence,
					   pkg->hdr.command_id);
		अगर (!ret) अणु
			mutex_lock(&net->connection_lock);
			net->login_received = true;
			net->remote_transmit_path = pkg->transmit_path;

			/* If we reached the number of max retries or
			 * previous logout, schedule another round of
			 * login retries
			 */
			अगर (net->login_retries >= TBNET_LOGIN_RETRIES ||
			    !net->login_sent) अणु
				net->login_retries = 0;
				queue_delayed_work(प्रणाली_दीर्घ_wq,
						   &net->login_work, 0);
			पूर्ण
			mutex_unlock(&net->connection_lock);

			queue_work(प्रणाली_दीर्घ_wq, &net->connected_work);
		पूर्ण
		अवरोध;

	हाल TBIP_LOGOUT:
		ret = tbnet_logout_response(net, route, sequence, command_id);
		अगर (!ret)
			queue_work(प्रणाली_दीर्घ_wq, &net->disconnect_work);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर (ret)
		netdev_warn(net->dev, "failed to send ThunderboltIP response\n");

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक tbnet_available_buffers(स्थिर काष्ठा tbnet_ring *ring)
अणु
	वापस ring->prod - ring->cons;
पूर्ण

अटल पूर्णांक tbnet_alloc_rx_buffers(काष्ठा tbnet *net, अचिन्हित पूर्णांक nbuffers)
अणु
	काष्ठा tbnet_ring *ring = &net->rx_ring;
	पूर्णांक ret;

	जबतक (nbuffers--) अणु
		काष्ठा device *dma_dev = tb_ring_dma_device(ring->ring);
		अचिन्हित पूर्णांक index = ring->prod & (TBNET_RING_SIZE - 1);
		काष्ठा tbnet_frame *tf = &ring->frames[index];
		dma_addr_t dma_addr;

		अगर (tf->page)
			अवरोध;

		/* Allocate page (order > 0) so that it can hold maximum
		 * ThunderboltIP frame (4kB) and the additional room क्रम
		 * SKB shared info required by build_skb().
		 */
		tf->page = dev_alloc_pages(TBNET_RX_PAGE_ORDER);
		अगर (!tf->page) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण

		dma_addr = dma_map_page(dma_dev, tf->page, 0,
					TBNET_RX_PAGE_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dma_dev, dma_addr)) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण

		tf->frame.buffer_phy = dma_addr;
		tf->dev = net->dev;

		tb_ring_rx(ring->ring, &tf->frame);

		ring->prod++;
	पूर्ण

	वापस 0;

err_मुक्त:
	tbnet_मुक्त_buffers(ring);
	वापस ret;
पूर्ण

अटल काष्ठा tbnet_frame *tbnet_get_tx_buffer(काष्ठा tbnet *net)
अणु
	काष्ठा tbnet_ring *ring = &net->tx_ring;
	काष्ठा device *dma_dev = tb_ring_dma_device(ring->ring);
	काष्ठा tbnet_frame *tf;
	अचिन्हित पूर्णांक index;

	अगर (!tbnet_available_buffers(ring))
		वापस शून्य;

	index = ring->cons++ & (TBNET_RING_SIZE - 1);

	tf = &ring->frames[index];
	tf->frame.size = 0;

	dma_sync_single_क्रम_cpu(dma_dev, tf->frame.buffer_phy,
				tbnet_frame_size(tf), DMA_TO_DEVICE);

	वापस tf;
पूर्ण

अटल व्योम tbnet_tx_callback(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame,
			      bool canceled)
अणु
	काष्ठा tbnet_frame *tf = container_of(frame, typeof(*tf), frame);
	काष्ठा tbnet *net = netdev_priv(tf->dev);

	/* Return buffer to the ring */
	net->tx_ring.prod++;

	अगर (tbnet_available_buffers(&net->tx_ring) >= TBNET_RING_SIZE / 2)
		netअगर_wake_queue(net->dev);
पूर्ण

अटल पूर्णांक tbnet_alloc_tx_buffers(काष्ठा tbnet *net)
अणु
	काष्ठा tbnet_ring *ring = &net->tx_ring;
	काष्ठा device *dma_dev = tb_ring_dma_device(ring->ring);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < TBNET_RING_SIZE; i++) अणु
		काष्ठा tbnet_frame *tf = &ring->frames[i];
		dma_addr_t dma_addr;

		tf->page = alloc_page(GFP_KERNEL);
		अगर (!tf->page) अणु
			tbnet_मुक्त_buffers(ring);
			वापस -ENOMEM;
		पूर्ण

		dma_addr = dma_map_page(dma_dev, tf->page, 0, TBNET_FRAME_SIZE,
					DMA_TO_DEVICE);
		अगर (dma_mapping_error(dma_dev, dma_addr)) अणु
			__मुक्त_page(tf->page);
			tf->page = शून्य;
			tbnet_मुक्त_buffers(ring);
			वापस -ENOMEM;
		पूर्ण

		tf->dev = net->dev;
		tf->frame.buffer_phy = dma_addr;
		tf->frame.callback = tbnet_tx_callback;
		tf->frame.sof = TBIP_PDF_FRAME_START;
		tf->frame.eof = TBIP_PDF_FRAME_END;
	पूर्ण

	ring->cons = 0;
	ring->prod = TBNET_RING_SIZE - 1;

	वापस 0;
पूर्ण

अटल व्योम tbnet_connected_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tbnet *net = container_of(work, typeof(*net), connected_work);
	bool connected;
	पूर्णांक ret;

	अगर (netअगर_carrier_ok(net->dev))
		वापस;

	mutex_lock(&net->connection_lock);
	connected = net->login_sent && net->login_received;
	mutex_unlock(&net->connection_lock);

	अगर (!connected)
		वापस;

	ret = tb_xकरोमुख्य_alloc_in_hopid(net->xd, net->remote_transmit_path);
	अगर (ret != net->remote_transmit_path) अणु
		netdev_err(net->dev, "failed to allocate Rx HopID\n");
		वापस;
	पूर्ण

	/* Both logins successful so enable the high-speed DMA paths and
	 * start the network device queue.
	 */
	ret = tb_xकरोमुख्य_enable_paths(net->xd, net->local_transmit_path,
				      net->rx_ring.ring->hop,
				      net->remote_transmit_path,
				      net->tx_ring.ring->hop);
	अगर (ret) अणु
		netdev_err(net->dev, "failed to enable DMA paths\n");
		वापस;
	पूर्ण

	tb_ring_start(net->tx_ring.ring);
	tb_ring_start(net->rx_ring.ring);

	ret = tbnet_alloc_rx_buffers(net, TBNET_RING_SIZE);
	अगर (ret)
		जाओ err_stop_rings;

	ret = tbnet_alloc_tx_buffers(net);
	अगर (ret)
		जाओ err_मुक्त_rx_buffers;

	netअगर_carrier_on(net->dev);
	netअगर_start_queue(net->dev);
	वापस;

err_मुक्त_rx_buffers:
	tbnet_मुक्त_buffers(&net->rx_ring);
err_stop_rings:
	tb_ring_stop(net->rx_ring.ring);
	tb_ring_stop(net->tx_ring.ring);
	tb_xकरोमुख्य_release_in_hopid(net->xd, net->remote_transmit_path);
पूर्ण

अटल व्योम tbnet_login_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tbnet *net = container_of(work, typeof(*net), login_work.work);
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(TBNET_LOGIN_DELAY);
	पूर्णांक ret;

	अगर (netअगर_carrier_ok(net->dev))
		वापस;

	ret = tbnet_login_request(net, net->login_retries % 4);
	अगर (ret) अणु
		अगर (net->login_retries++ < TBNET_LOGIN_RETRIES) अणु
			queue_delayed_work(प्रणाली_दीर्घ_wq, &net->login_work,
					   delay);
		पूर्ण अन्यथा अणु
			netdev_info(net->dev, "ThunderboltIP login timed out\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		net->login_retries = 0;

		mutex_lock(&net->connection_lock);
		net->login_sent = true;
		mutex_unlock(&net->connection_lock);

		queue_work(प्रणाली_दीर्घ_wq, &net->connected_work);
	पूर्ण
पूर्ण

अटल व्योम tbnet_disconnect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tbnet *net = container_of(work, typeof(*net), disconnect_work);

	tbnet_tear_करोwn(net, false);
पूर्ण

अटल bool tbnet_check_frame(काष्ठा tbnet *net, स्थिर काष्ठा tbnet_frame *tf,
			      स्थिर काष्ठा thunderbolt_ip_frame_header *hdr)
अणु
	u32 frame_id, frame_count, frame_size, frame_index;
	अचिन्हित पूर्णांक size;

	अगर (tf->frame.flags & RING_DESC_CRC_ERROR) अणु
		net->stats.rx_crc_errors++;
		वापस false;
	पूर्ण अन्यथा अगर (tf->frame.flags & RING_DESC_BUFFER_OVERRUN) अणु
		net->stats.rx_over_errors++;
		वापस false;
	पूर्ण

	/* Should be greater than just header i.e. contains data */
	size = tbnet_frame_size(tf);
	अगर (size <= माप(*hdr)) अणु
		net->stats.rx_length_errors++;
		वापस false;
	पूर्ण

	frame_count = le32_to_cpu(hdr->frame_count);
	frame_size = le32_to_cpu(hdr->frame_size);
	frame_index = le16_to_cpu(hdr->frame_index);
	frame_id = le16_to_cpu(hdr->frame_id);

	अगर ((frame_size > size - माप(*hdr)) || !frame_size) अणु
		net->stats.rx_length_errors++;
		वापस false;
	पूर्ण

	/* In हाल we're in the middle of packet, validate the frame
	 * header based on first fragment of the packet.
	 */
	अगर (net->skb && net->rx_hdr.frame_count) अणु
		/* Check the frame count fits the count field */
		अगर (frame_count != net->rx_hdr.frame_count) अणु
			net->stats.rx_length_errors++;
			वापस false;
		पूर्ण

		/* Check the frame identअगरiers are incremented correctly,
		 * and id is matching.
		 */
		अगर (frame_index != net->rx_hdr.frame_index + 1 ||
		    frame_id != net->rx_hdr.frame_id) अणु
			net->stats.rx_missed_errors++;
			वापस false;
		पूर्ण

		अगर (net->skb->len + frame_size > TBNET_MAX_MTU) अणु
			net->stats.rx_length_errors++;
			वापस false;
		पूर्ण

		वापस true;
	पूर्ण

	/* Start of packet, validate the frame header */
	अगर (frame_count == 0 || frame_count > TBNET_RING_SIZE / 4) अणु
		net->stats.rx_length_errors++;
		वापस false;
	पूर्ण
	अगर (frame_index != 0) अणु
		net->stats.rx_missed_errors++;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक tbnet_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tbnet *net = container_of(napi, काष्ठा tbnet, napi);
	अचिन्हित पूर्णांक cleaned_count = tbnet_available_buffers(&net->rx_ring);
	काष्ठा device *dma_dev = tb_ring_dma_device(net->rx_ring.ring);
	अचिन्हित पूर्णांक rx_packets = 0;

	जबतक (rx_packets < budget) अणु
		स्थिर काष्ठा thunderbolt_ip_frame_header *hdr;
		अचिन्हित पूर्णांक hdr_size = माप(*hdr);
		काष्ठा sk_buff *skb = शून्य;
		काष्ठा ring_frame *frame;
		काष्ठा tbnet_frame *tf;
		काष्ठा page *page;
		bool last = true;
		u32 frame_size;

		/* Return some buffers to hardware, one at a समय is too
		 * slow so allocate MAX_SKB_FRAGS buffers at the same
		 * समय.
		 */
		अगर (cleaned_count >= MAX_SKB_FRAGS) अणु
			tbnet_alloc_rx_buffers(net, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		frame = tb_ring_poll(net->rx_ring.ring);
		अगर (!frame)
			अवरोध;

		dma_unmap_page(dma_dev, frame->buffer_phy,
			       TBNET_RX_PAGE_SIZE, DMA_FROM_DEVICE);

		tf = container_of(frame, typeof(*tf), frame);

		page = tf->page;
		tf->page = शून्य;
		net->rx_ring.cons++;
		cleaned_count++;

		hdr = page_address(page);
		अगर (!tbnet_check_frame(net, tf, hdr)) अणु
			__मुक्त_pages(page, TBNET_RX_PAGE_ORDER);
			dev_kमुक्त_skb_any(net->skb);
			net->skb = शून्य;
			जारी;
		पूर्ण

		frame_size = le32_to_cpu(hdr->frame_size);

		skb = net->skb;
		अगर (!skb) अणु
			skb = build_skb(page_address(page),
					TBNET_RX_PAGE_SIZE);
			अगर (!skb) अणु
				__मुक्त_pages(page, TBNET_RX_PAGE_ORDER);
				net->stats.rx_errors++;
				अवरोध;
			पूर्ण

			skb_reserve(skb, hdr_size);
			skb_put(skb, frame_size);

			net->skb = skb;
		पूर्ण अन्यथा अणु
			skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
					page, hdr_size, frame_size,
					TBNET_RX_PAGE_SIZE - hdr_size);
		पूर्ण

		net->rx_hdr.frame_size = frame_size;
		net->rx_hdr.frame_count = le32_to_cpu(hdr->frame_count);
		net->rx_hdr.frame_index = le16_to_cpu(hdr->frame_index);
		net->rx_hdr.frame_id = le16_to_cpu(hdr->frame_id);
		last = net->rx_hdr.frame_index == net->rx_hdr.frame_count - 1;

		rx_packets++;
		net->stats.rx_bytes += frame_size;

		अगर (last) अणु
			skb->protocol = eth_type_trans(skb, net->dev);
			napi_gro_receive(&net->napi, skb);
			net->skb = शून्य;
		पूर्ण
	पूर्ण

	net->stats.rx_packets += rx_packets;

	अगर (cleaned_count)
		tbnet_alloc_rx_buffers(net, cleaned_count);

	अगर (rx_packets >= budget)
		वापस budget;

	napi_complete_करोne(napi, rx_packets);
	/* Re-enable the ring पूर्णांकerrupt */
	tb_ring_poll_complete(net->rx_ring.ring);

	वापस rx_packets;
पूर्ण

अटल व्योम tbnet_start_poll(व्योम *data)
अणु
	काष्ठा tbnet *net = data;

	napi_schedule(&net->napi);
पूर्ण

अटल पूर्णांक tbnet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा tbnet *net = netdev_priv(dev);
	काष्ठा tb_xकरोमुख्य *xd = net->xd;
	u16 sof_mask, eof_mask;
	काष्ठा tb_ring *ring;
	पूर्णांक hopid;

	netअगर_carrier_off(dev);

	ring = tb_ring_alloc_tx(xd->tb->nhi, -1, TBNET_RING_SIZE,
				RING_FLAG_FRAME);
	अगर (!ring) अणु
		netdev_err(dev, "failed to allocate Tx ring\n");
		वापस -ENOMEM;
	पूर्ण
	net->tx_ring.ring = ring;

	hopid = tb_xकरोमुख्य_alloc_out_hopid(xd, -1);
	अगर (hopid < 0) अणु
		netdev_err(dev, "failed to allocate Tx HopID\n");
		tb_ring_मुक्त(net->tx_ring.ring);
		net->tx_ring.ring = शून्य;
		वापस hopid;
	पूर्ण
	net->local_transmit_path = hopid;

	sof_mask = BIT(TBIP_PDF_FRAME_START);
	eof_mask = BIT(TBIP_PDF_FRAME_END);

	ring = tb_ring_alloc_rx(xd->tb->nhi, -1, TBNET_RING_SIZE,
				RING_FLAG_FRAME, 0, sof_mask, eof_mask,
				tbnet_start_poll, net);
	अगर (!ring) अणु
		netdev_err(dev, "failed to allocate Rx ring\n");
		tb_ring_मुक्त(net->tx_ring.ring);
		net->tx_ring.ring = शून्य;
		वापस -ENOMEM;
	पूर्ण
	net->rx_ring.ring = ring;

	napi_enable(&net->napi);
	start_login(net);

	वापस 0;
पूर्ण

अटल पूर्णांक tbnet_stop(काष्ठा net_device *dev)
अणु
	काष्ठा tbnet *net = netdev_priv(dev);

	napi_disable(&net->napi);

	cancel_work_sync(&net->disconnect_work);
	tbnet_tear_करोwn(net, true);

	tb_ring_मुक्त(net->rx_ring.ring);
	net->rx_ring.ring = शून्य;

	tb_xकरोमुख्य_release_out_hopid(net->xd, net->local_transmit_path);
	tb_ring_मुक्त(net->tx_ring.ring);
	net->tx_ring.ring = शून्य;

	वापस 0;
पूर्ण

अटल bool tbnet_xmit_csum_and_map(काष्ठा tbnet *net, काष्ठा sk_buff *skb,
	काष्ठा tbnet_frame **frames, u32 frame_count)
अणु
	काष्ठा thunderbolt_ip_frame_header *hdr = page_address(frames[0]->page);
	काष्ठा device *dma_dev = tb_ring_dma_device(net->tx_ring.ring);
	__wsum wsum = htonl(skb->len - skb_transport_offset(skb));
	अचिन्हित पूर्णांक i, len, offset = skb_transport_offset(skb);
	__be16 protocol = skb->protocol;
	व्योम *data = skb->data;
	व्योम *dest = hdr + 1;
	__sum16 *tucso;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		/* No need to calculate checksum so we just update the
		 * total frame count and sync the frames क्रम DMA.
		 */
		क्रम (i = 0; i < frame_count; i++) अणु
			hdr = page_address(frames[i]->page);
			hdr->frame_count = cpu_to_le32(frame_count);
			dma_sync_single_क्रम_device(dma_dev,
				frames[i]->frame.buffer_phy,
				tbnet_frame_size(frames[i]), DMA_TO_DEVICE);
		पूर्ण

		वापस true;
	पूर्ण

	अगर (protocol == htons(ETH_P_8021Q)) अणु
		काष्ठा vlan_hdr *vhdr, vh;

		vhdr = skb_header_poपूर्णांकer(skb, ETH_HLEN, माप(vh), &vh);
		अगर (!vhdr)
			वापस false;

		protocol = vhdr->h_vlan_encapsulated_proto;
	पूर्ण

	/* Data poपूर्णांकs on the beginning of packet.
	 * Check is the checksum असलolute place in the packet.
	 * ipcso will update IP checksum.
	 * tucso will update TCP/UPD checksum.
	 */
	अगर (protocol == htons(ETH_P_IP)) अणु
		__sum16 *ipcso = dest + ((व्योम *)&(ip_hdr(skb)->check) - data);

		*ipcso = 0;
		*ipcso = ip_fast_csum(dest + skb_network_offset(skb),
				      ip_hdr(skb)->ihl);

		अगर (ip_hdr(skb)->protocol == IPPROTO_TCP)
			tucso = dest + ((व्योम *)&(tcp_hdr(skb)->check) - data);
		अन्यथा अगर (ip_hdr(skb)->protocol == IPPROTO_UDP)
			tucso = dest + ((व्योम *)&(udp_hdr(skb)->check) - data);
		अन्यथा
			वापस false;

		*tucso = ~csum_tcpudp_magic(ip_hdr(skb)->saddr,
					    ip_hdr(skb)->daddr, 0,
					    ip_hdr(skb)->protocol, 0);
	पूर्ण अन्यथा अगर (skb_is_gso_v6(skb)) अणु
		tucso = dest + ((व्योम *)&(tcp_hdr(skb)->check) - data);
		*tucso = ~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
					  &ipv6_hdr(skb)->daddr, 0,
					  IPPROTO_TCP, 0);
		वापस false;
	पूर्ण अन्यथा अगर (protocol == htons(ETH_P_IPV6)) अणु
		tucso = dest + skb_checksum_start_offset(skb) + skb->csum_offset;
		*tucso = ~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
					  &ipv6_hdr(skb)->daddr, 0,
					  ipv6_hdr(skb)->nexthdr, 0);
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	/* First frame was headers, rest of the frames contain data.
	 * Calculate checksum over each frame.
	 */
	क्रम (i = 0; i < frame_count; i++) अणु
		hdr = page_address(frames[i]->page);
		dest = (व्योम *)(hdr + 1) + offset;
		len = le32_to_cpu(hdr->frame_size) - offset;
		wsum = csum_partial(dest, len, wsum);
		hdr->frame_count = cpu_to_le32(frame_count);

		offset = 0;
	पूर्ण

	*tucso = csum_fold(wsum);

	/* Checksum is finally calculated and we करोn't touch the memory
	 * anymore, so DMA sync the frames now.
	 */
	क्रम (i = 0; i < frame_count; i++) अणु
		dma_sync_single_क्रम_device(dma_dev, frames[i]->frame.buffer_phy,
			tbnet_frame_size(frames[i]), DMA_TO_DEVICE);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम *tbnet_kmap_frag(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक frag_num,
			     अचिन्हित पूर्णांक *len)
अणु
	स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[frag_num];

	*len = skb_frag_size(frag);
	वापस kmap_atomic(skb_frag_page(frag)) + skb_frag_off(frag);
पूर्ण

अटल netdev_tx_t tbnet_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा tbnet *net = netdev_priv(dev);
	काष्ठा tbnet_frame *frames[MAX_SKB_FRAGS];
	u16 frame_id = atomic_पढ़ो(&net->frame_id);
	काष्ठा thunderbolt_ip_frame_header *hdr;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक data_len = skb->len;
	अचिन्हित पूर्णांक nframes, i;
	अचिन्हित पूर्णांक frag = 0;
	व्योम *src = skb->data;
	u32 frame_index = 0;
	bool unmap = false;
	व्योम *dest;

	nframes = DIV_ROUND_UP(data_len, TBNET_MAX_PAYLOAD_SIZE);
	अगर (tbnet_available_buffers(&net->tx_ring) < nframes) अणु
		netअगर_stop_queue(net->dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	frames[frame_index] = tbnet_get_tx_buffer(net);
	अगर (!frames[frame_index])
		जाओ err_drop;

	hdr = page_address(frames[frame_index]->page);
	dest = hdr + 1;

	/* If overall packet is bigger than the frame data size */
	जबतक (data_len > TBNET_MAX_PAYLOAD_SIZE) अणु
		अचिन्हित पूर्णांक size_left = TBNET_MAX_PAYLOAD_SIZE;

		hdr->frame_size = cpu_to_le32(TBNET_MAX_PAYLOAD_SIZE);
		hdr->frame_index = cpu_to_le16(frame_index);
		hdr->frame_id = cpu_to_le16(frame_id);

		करो अणु
			अगर (len > size_left) अणु
				/* Copy data onto Tx buffer data with
				 * full frame size then अवरोध and go to
				 * next frame
				 */
				स_नकल(dest, src, size_left);
				len -= size_left;
				dest += size_left;
				src += size_left;
				अवरोध;
			पूर्ण

			स_नकल(dest, src, len);
			size_left -= len;
			dest += len;

			अगर (unmap) अणु
				kunmap_atomic(src);
				unmap = false;
			पूर्ण

			/* Ensure all fragments have been processed */
			अगर (frag < skb_shinfo(skb)->nr_frags) अणु
				/* Map and then unmap quickly */
				src = tbnet_kmap_frag(skb, frag++, &len);
				unmap = true;
			पूर्ण अन्यथा अगर (unlikely(size_left > 0)) अणु
				जाओ err_drop;
			पूर्ण
		पूर्ण जबतक (size_left > 0);

		data_len -= TBNET_MAX_PAYLOAD_SIZE;
		frame_index++;

		frames[frame_index] = tbnet_get_tx_buffer(net);
		अगर (!frames[frame_index])
			जाओ err_drop;

		hdr = page_address(frames[frame_index]->page);
		dest = hdr + 1;
	पूर्ण

	hdr->frame_size = cpu_to_le32(data_len);
	hdr->frame_index = cpu_to_le16(frame_index);
	hdr->frame_id = cpu_to_le16(frame_id);

	frames[frame_index]->frame.size = data_len + माप(*hdr);

	/* In हाल the reमुख्यing data_len is smaller than a frame */
	जबतक (len < data_len) अणु
		स_नकल(dest, src, len);
		data_len -= len;
		dest += len;

		अगर (unmap) अणु
			kunmap_atomic(src);
			unmap = false;
		पूर्ण

		अगर (frag < skb_shinfo(skb)->nr_frags) अणु
			src = tbnet_kmap_frag(skb, frag++, &len);
			unmap = true;
		पूर्ण अन्यथा अगर (unlikely(data_len > 0)) अणु
			जाओ err_drop;
		पूर्ण
	पूर्ण

	स_नकल(dest, src, data_len);

	अगर (unmap)
		kunmap_atomic(src);

	अगर (!tbnet_xmit_csum_and_map(net, skb, frames, frame_index + 1))
		जाओ err_drop;

	क्रम (i = 0; i < frame_index + 1; i++)
		tb_ring_tx(net->tx_ring.ring, &frames[i]->frame);

	अगर (net->svc->prtcstns & TBNET_MATCH_FRAGS_ID)
		atomic_inc(&net->frame_id);

	net->stats.tx_packets++;
	net->stats.tx_bytes += skb->len;

	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;

err_drop:
	/* We can re-use the buffers */
	net->tx_ring.cons -= frame_index;

	dev_kमुक्त_skb_any(skb);
	net->stats.tx_errors++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम tbnet_get_stats64(काष्ठा net_device *dev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा tbnet *net = netdev_priv(dev);

	stats->tx_packets = net->stats.tx_packets;
	stats->rx_packets = net->stats.rx_packets;
	stats->tx_bytes = net->stats.tx_bytes;
	stats->rx_bytes = net->stats.rx_bytes;
	stats->rx_errors = net->stats.rx_errors + net->stats.rx_length_errors +
		net->stats.rx_over_errors + net->stats.rx_crc_errors +
		net->stats.rx_missed_errors;
	stats->tx_errors = net->stats.tx_errors;
	stats->rx_length_errors = net->stats.rx_length_errors;
	stats->rx_over_errors = net->stats.rx_over_errors;
	stats->rx_crc_errors = net->stats.rx_crc_errors;
	stats->rx_missed_errors = net->stats.rx_missed_errors;
पूर्ण

अटल स्थिर काष्ठा net_device_ops tbnet_netdev_ops = अणु
	.nकरो_खोलो = tbnet_खोलो,
	.nकरो_stop = tbnet_stop,
	.nकरो_start_xmit = tbnet_start_xmit,
	.nकरो_get_stats64 = tbnet_get_stats64,
पूर्ण;

अटल व्योम tbnet_generate_mac(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा tbnet *net = netdev_priv(dev);
	स्थिर काष्ठा tb_xकरोमुख्य *xd = net->xd;
	u8 phy_port;
	u32 hash;

	phy_port = tb_phy_port_from_link(TBNET_L0_PORT_NUM(xd->route));

	/* Unicast and locally administered MAC */
	dev->dev_addr[0] = phy_port << 4 | 0x02;
	hash = jhash2((u32 *)xd->local_uuid, 4, 0);
	स_नकल(dev->dev_addr + 1, &hash, माप(hash));
	hash = jhash2((u32 *)xd->local_uuid, 4, hash);
	dev->dev_addr[5] = hash & 0xff;
पूर्ण

अटल पूर्णांक tbnet_probe(काष्ठा tb_service *svc, स्थिर काष्ठा tb_service_id *id)
अणु
	काष्ठा tb_xकरोमुख्य *xd = tb_service_parent(svc);
	काष्ठा net_device *dev;
	काष्ठा tbnet *net;
	पूर्णांक ret;

	dev = alloc_etherdev(माप(*net));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &svc->dev);

	net = netdev_priv(dev);
	INIT_DELAYED_WORK(&net->login_work, tbnet_login_work);
	INIT_WORK(&net->connected_work, tbnet_connected_work);
	INIT_WORK(&net->disconnect_work, tbnet_disconnect_work);
	mutex_init(&net->connection_lock);
	atomic_set(&net->command_id, 0);
	atomic_set(&net->frame_id, 0);
	net->svc = svc;
	net->dev = dev;
	net->xd = xd;

	tbnet_generate_mac(dev);

	म_नकल(dev->name, "thunderbolt%d");
	dev->netdev_ops = &tbnet_netdev_ops;

	/* ThunderboltIP takes advantage of TSO packets but instead of
	 * segmenting them we just split the packet पूर्णांकo Thunderbolt
	 * frames (maximum payload size of each frame is 4084 bytes) and
	 * calculate checksum over the whole packet here.
	 *
	 * The receiving side करोes the opposite अगर the host OS supports
	 * LRO, otherwise it needs to split the large packet पूर्णांकo MTU
	 * sized smaller packets.
	 *
	 * In order to receive large packets from the networking stack,
	 * we need to announce support क्रम most of the offloading
	 * features here.
	 */
	dev->hw_features = NETIF_F_SG | NETIF_F_ALL_TSO | NETIF_F_GRO |
			   NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	dev->features = dev->hw_features | NETIF_F_HIGHDMA;
	dev->hard_header_len += माप(काष्ठा thunderbolt_ip_frame_header);

	netअगर_napi_add(dev, &net->napi, tbnet_poll, NAPI_POLL_WEIGHT);

	/* MTU range: 68 - 65522 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = TBNET_MAX_MTU - ETH_HLEN;

	net->handler.uuid = &tbnet_svc_uuid;
	net->handler.callback = tbnet_handle_packet;
	net->handler.data = net;
	tb_रेजिस्टर_protocol_handler(&net->handler);

	tb_service_set_drvdata(svc, net);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret) अणु
		tb_unरेजिस्टर_protocol_handler(&net->handler);
		मुक्त_netdev(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tbnet_हटाओ(काष्ठा tb_service *svc)
अणु
	काष्ठा tbnet *net = tb_service_get_drvdata(svc);

	unरेजिस्टर_netdev(net->dev);
	tb_unरेजिस्टर_protocol_handler(&net->handler);
	मुक्त_netdev(net->dev);
पूर्ण

अटल व्योम tbnet_shutकरोwn(काष्ठा tb_service *svc)
अणु
	tbnet_tear_करोwn(tb_service_get_drvdata(svc), true);
पूर्ण

अटल पूर्णांक __maybe_unused tbnet_suspend(काष्ठा device *dev)
अणु
	काष्ठा tb_service *svc = tb_to_service(dev);
	काष्ठा tbnet *net = tb_service_get_drvdata(svc);

	stop_login(net);
	अगर (netअगर_running(net->dev)) अणु
		netअगर_device_detach(net->dev);
		tbnet_tear_करोwn(net, true);
	पूर्ण

	tb_unरेजिस्टर_protocol_handler(&net->handler);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tbnet_resume(काष्ठा device *dev)
अणु
	काष्ठा tb_service *svc = tb_to_service(dev);
	काष्ठा tbnet *net = tb_service_get_drvdata(svc);

	tb_रेजिस्टर_protocol_handler(&net->handler);

	netअगर_carrier_off(net->dev);
	अगर (netअगर_running(net->dev)) अणु
		netअगर_device_attach(net->dev);
		start_login(net);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tbnet_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tbnet_suspend, tbnet_resume)
पूर्ण;

अटल स्थिर काष्ठा tb_service_id tbnet_ids[] = अणु
	अणु TB_SERVICE("network", 1) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(tbsvc, tbnet_ids);

अटल काष्ठा tb_service_driver tbnet_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "thunderbolt-net",
		.pm = &tbnet_pm_ops,
	पूर्ण,
	.probe = tbnet_probe,
	.हटाओ = tbnet_हटाओ,
	.shutकरोwn = tbnet_shutकरोwn,
	.id_table = tbnet_ids,
पूर्ण;

अटल पूर्णांक __init tbnet_init(व्योम)
अणु
	पूर्णांक ret;

	tbnet_dir = tb_property_create_dir(&tbnet_dir_uuid);
	अगर (!tbnet_dir)
		वापस -ENOMEM;

	tb_property_add_immediate(tbnet_dir, "prtcid", 1);
	tb_property_add_immediate(tbnet_dir, "prtcvers", 1);
	tb_property_add_immediate(tbnet_dir, "prtcrevs", 1);
	/* Currently only announce support क्रम match frags ID (bit 1). Bit 0
	 * is reserved क्रम full E2E flow control which we करो not support at
	 * the moment.
	 */
	tb_property_add_immediate(tbnet_dir, "prtcstns",
				  TBNET_MATCH_FRAGS_ID | TBNET_64K_FRAMES);

	ret = tb_रेजिस्टर_property_dir("network", tbnet_dir);
	अगर (ret) अणु
		tb_property_मुक्त_dir(tbnet_dir);
		वापस ret;
	पूर्ण

	वापस tb_रेजिस्टर_service_driver(&tbnet_driver);
पूर्ण
module_init(tbnet_init);

अटल व्योम __निकास tbnet_निकास(व्योम)
अणु
	tb_unरेजिस्टर_service_driver(&tbnet_driver);
	tb_unरेजिस्टर_property_dir("network", tbnet_dir);
	tb_property_मुक्त_dir(tbnet_dir);
पूर्ण
module_निकास(tbnet_निकास);

MODULE_AUTHOR("Amir Levy <amir.jer.levy@intel.com>");
MODULE_AUTHOR("Michael Jamet <michael.jamet@intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Thunderbolt network driver");
MODULE_LICENSE("GPL v2");
