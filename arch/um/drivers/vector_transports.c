<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 - Cambridge Greys Limited
 * Copyright (C) 2011 - 2014 Cisco Systems Inc
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/virtio_net.h>
#समावेश <linux/virtio_net.h>
#समावेश <linux/virtio_byteorder.h>
#समावेश <linux/netdev_features.h>
#समावेश "vector_user.h"
#समावेश "vector_kern.h"

#घोषणा GOOD_LINEAR 512
#घोषणा GSO_ERROR "Incoming GSO frames and GRO disabled on the interface"

काष्ठा gre_minimal_header अणु
	uपूर्णांक16_t header;
	uपूर्णांक16_t arptype;
पूर्ण;


काष्ठा uml_gre_data अणु
	uपूर्णांक32_t rx_key;
	uपूर्णांक32_t tx_key;
	uपूर्णांक32_t sequence;

	bool ipv6;
	bool has_sequence;
	bool pin_sequence;
	bool checksum;
	bool key;
	काष्ठा gre_minimal_header expected_header;

	uपूर्णांक32_t checksum_offset;
	uपूर्णांक32_t key_offset;
	uपूर्णांक32_t sequence_offset;

पूर्ण;

काष्ठा uml_l2tpv3_data अणु
	uपूर्णांक64_t rx_cookie;
	uपूर्णांक64_t tx_cookie;
	uपूर्णांक64_t rx_session;
	uपूर्णांक64_t tx_session;
	uपूर्णांक32_t counter;

	bool udp;
	bool ipv6;
	bool has_counter;
	bool pin_counter;
	bool cookie;
	bool cookie_is_64;

	uपूर्णांक32_t cookie_offset;
	uपूर्णांक32_t session_offset;
	uपूर्णांक32_t counter_offset;
पूर्ण;

अटल पूर्णांक l2tpv3_क्रमm_header(uपूर्णांक8_t *header,
	काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp)
अणु
	काष्ठा uml_l2tpv3_data *td = vp->transport_data;
	uपूर्णांक32_t *counter;

	अगर (td->udp)
		*(uपूर्णांक32_t *) header = cpu_to_be32(L2TPV3_DATA_PACKET);
	(*(uपूर्णांक32_t *) (header + td->session_offset)) = td->tx_session;

	अगर (td->cookie) अणु
		अगर (td->cookie_is_64)
			(*(uपूर्णांक64_t *)(header + td->cookie_offset)) =
				td->tx_cookie;
		अन्यथा
			(*(uपूर्णांक32_t *)(header + td->cookie_offset)) =
				td->tx_cookie;
	पूर्ण
	अगर (td->has_counter) अणु
		counter = (uपूर्णांक32_t *)(header + td->counter_offset);
		अगर (td->pin_counter) अणु
			*counter = 0;
		पूर्ण अन्यथा अणु
			td->counter++;
			*counter = cpu_to_be32(td->counter);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gre_क्रमm_header(uपूर्णांक8_t *header,
		काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp)
अणु
	काष्ठा uml_gre_data *td = vp->transport_data;
	uपूर्णांक32_t *sequence;
	*((uपूर्णांक32_t *) header) = *((uपूर्णांक32_t *) &td->expected_header);
	अगर (td->key)
		(*(uपूर्णांक32_t *) (header + td->key_offset)) = td->tx_key;
	अगर (td->has_sequence) अणु
		sequence = (uपूर्णांक32_t *)(header + td->sequence_offset);
		अगर (td->pin_sequence)
			*sequence = 0;
		अन्यथा
			*sequence = cpu_to_be32(++td->sequence);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक raw_क्रमm_header(uपूर्णांक8_t *header,
		काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp)
अणु
	काष्ठा virtio_net_hdr *vheader = (काष्ठा virtio_net_hdr *) header;

	virtio_net_hdr_from_skb(
		skb,
		vheader,
		virtio_legacy_is_little_endian(),
		false,
		0
	);

	वापस 0;
पूर्ण

अटल पूर्णांक l2tpv3_verअगरy_header(
	uपूर्णांक8_t *header, काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp)
अणु
	काष्ठा uml_l2tpv3_data *td = vp->transport_data;
	uपूर्णांक32_t *session;
	uपूर्णांक64_t cookie;

	अगर ((!td->udp) && (!td->ipv6))
		header += माप(काष्ठा iphdr) /* fix क्रम ipv4 raw */;

	/* we करो not करो a strict check क्रम "data" packets as per
	 * the RFC spec because the pure IP spec करोes not have
	 * that anyway.
	 */

	अगर (td->cookie) अणु
		अगर (td->cookie_is_64)
			cookie = *(uपूर्णांक64_t *)(header + td->cookie_offset);
		अन्यथा
			cookie = *(uपूर्णांक32_t *)(header + td->cookie_offset);
		अगर (cookie != td->rx_cookie) अणु
			अगर (net_ratelimit())
				netdev_err(vp->dev, "uml_l2tpv3: unknown cookie id");
			वापस -1;
		पूर्ण
	पूर्ण
	session = (uपूर्णांक32_t *) (header + td->session_offset);
	अगर (*session != td->rx_session) अणु
		अगर (net_ratelimit())
			netdev_err(vp->dev, "uml_l2tpv3: session mismatch");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gre_verअगरy_header(
	uपूर्णांक8_t *header, काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp)
अणु

	uपूर्णांक32_t key;
	काष्ठा uml_gre_data *td = vp->transport_data;

	अगर (!td->ipv6)
		header += माप(काष्ठा iphdr) /* fix क्रम ipv4 raw */;

	अगर (*((uपूर्णांक32_t *) header) != *((uपूर्णांक32_t *) &td->expected_header)) अणु
		अगर (net_ratelimit())
			netdev_err(vp->dev, "header type disagreement, expecting %0x, got %0x",
				*((uपूर्णांक32_t *) &td->expected_header),
				*((uपूर्णांक32_t *) header)
			);
		वापस -1;
	पूर्ण

	अगर (td->key) अणु
		key = (*(uपूर्णांक32_t *)(header + td->key_offset));
		अगर (key != td->rx_key) अणु
			अगर (net_ratelimit())
				netdev_err(vp->dev, "unknown key id %0x, expecting %0x",
						key, td->rx_key);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक raw_verअगरy_header(
	uपूर्णांक8_t *header, काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp)
अणु
	काष्ठा virtio_net_hdr *vheader = (काष्ठा virtio_net_hdr *) header;

	अगर ((vheader->gso_type != VIRTIO_NET_HDR_GSO_NONE) &&
		(vp->req_size != 65536)) अणु
		अगर (net_ratelimit())
			netdev_err(
				vp->dev,
				GSO_ERROR
		);
	पूर्ण
	अगर ((vheader->flags & VIRTIO_NET_HDR_F_DATA_VALID) > 0)
		वापस 1;

	virtio_net_hdr_to_skb(skb, vheader, virtio_legacy_is_little_endian());
	वापस 0;
पूर्ण

अटल bool get_uपूर्णांक_param(
	काष्ठा arglist *def, अक्षर *param, अचिन्हित पूर्णांक *result)
अणु
	अक्षर *arg = uml_vector_fetch_arg(def, param);

	अगर (arg != शून्य) अणु
		अगर (kstrtoपूर्णांक(arg, 0, result) == 0)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool get_uदीर्घ_param(
	काष्ठा arglist *def, अक्षर *param, अचिन्हित दीर्घ *result)
अणु
	अक्षर *arg = uml_vector_fetch_arg(def, param);

	अगर (arg != शून्य) अणु
		अगर (kम_से_अदीर्घ(arg, 0, result) == 0)
			वापस true;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक build_gre_transport_data(काष्ठा vector_निजी *vp)
अणु
	काष्ठा uml_gre_data *td;
	पूर्णांक temp_पूर्णांक;
	पूर्णांक temp_rx;
	पूर्णांक temp_tx;

	vp->transport_data = kदो_स्मृति(माप(काष्ठा uml_gre_data), GFP_KERNEL);
	अगर (vp->transport_data == शून्य)
		वापस -ENOMEM;
	td = vp->transport_data;
	td->sequence = 0;

	td->expected_header.arptype = GRE_IRB;
	td->expected_header.header = 0;

	vp->क्रमm_header = &gre_क्रमm_header;
	vp->verअगरy_header = &gre_verअगरy_header;
	vp->header_size = 4;
	td->key_offset = 4;
	td->sequence_offset = 4;
	td->checksum_offset = 4;

	td->ipv6 = false;
	अगर (get_uपूर्णांक_param(vp->parsed, "v6", &temp_पूर्णांक)) अणु
		अगर (temp_पूर्णांक > 0)
			td->ipv6 = true;
	पूर्ण
	td->key = false;
	अगर (get_uपूर्णांक_param(vp->parsed, "rx_key", &temp_rx)) अणु
		अगर (get_uपूर्णांक_param(vp->parsed, "tx_key", &temp_tx)) अणु
			td->key = true;
			td->expected_header.header |= GRE_MODE_KEY;
			td->rx_key = cpu_to_be32(temp_rx);
			td->tx_key = cpu_to_be32(temp_tx);
			vp->header_size += 4;
			td->sequence_offset += 4;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	td->sequence = false;
	अगर (get_uपूर्णांक_param(vp->parsed, "sequence", &temp_पूर्णांक)) अणु
		अगर (temp_पूर्णांक > 0) अणु
			vp->header_size += 4;
			td->has_sequence = true;
			td->expected_header.header |= GRE_MODE_SEQUENCE;
			अगर (get_uपूर्णांक_param(
				vp->parsed, "pin_sequence", &temp_पूर्णांक)) अणु
				अगर (temp_पूर्णांक > 0)
					td->pin_sequence = true;
			पूर्ण
		पूर्ण
	पूर्ण
	vp->rx_header_size = vp->header_size;
	अगर (!td->ipv6)
		vp->rx_header_size += माप(काष्ठा iphdr);
	वापस 0;
पूर्ण

अटल पूर्णांक build_l2tpv3_transport_data(काष्ठा vector_निजी *vp)
अणु

	काष्ठा uml_l2tpv3_data *td;
	पूर्णांक temp_पूर्णांक, temp_rxs, temp_txs;
	अचिन्हित दीर्घ temp_rx;
	अचिन्हित दीर्घ temp_tx;

	vp->transport_data = kदो_स्मृति(
		माप(काष्ठा uml_l2tpv3_data), GFP_KERNEL);

	अगर (vp->transport_data == शून्य)
		वापस -ENOMEM;

	td = vp->transport_data;

	vp->क्रमm_header = &l2tpv3_क्रमm_header;
	vp->verअगरy_header = &l2tpv3_verअगरy_header;
	td->counter = 0;

	vp->header_size = 4;
	td->session_offset = 0;
	td->cookie_offset = 4;
	td->counter_offset = 4;


	td->ipv6 = false;
	अगर (get_uपूर्णांक_param(vp->parsed, "v6", &temp_पूर्णांक)) अणु
		अगर (temp_पूर्णांक > 0)
			td->ipv6 = true;
	पूर्ण

	अगर (get_uपूर्णांक_param(vp->parsed, "rx_session", &temp_rxs)) अणु
		अगर (get_uपूर्णांक_param(vp->parsed, "tx_session", &temp_txs)) अणु
			td->tx_session = cpu_to_be32(temp_txs);
			td->rx_session = cpu_to_be32(temp_rxs);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	td->cookie_is_64  = false;
	अगर (get_uपूर्णांक_param(vp->parsed, "cookie64", &temp_पूर्णांक)) अणु
		अगर (temp_पूर्णांक > 0)
			td->cookie_is_64  = true;
	पूर्ण
	td->cookie = false;
	अगर (get_uदीर्घ_param(vp->parsed, "rx_cookie", &temp_rx)) अणु
		अगर (get_uदीर्घ_param(vp->parsed, "tx_cookie", &temp_tx)) अणु
			td->cookie = true;
			अगर (td->cookie_is_64) अणु
				td->rx_cookie = cpu_to_be64(temp_rx);
				td->tx_cookie = cpu_to_be64(temp_tx);
				vp->header_size += 8;
				td->counter_offset += 8;
			पूर्ण अन्यथा अणु
				td->rx_cookie = cpu_to_be32(temp_rx);
				td->tx_cookie = cpu_to_be32(temp_tx);
				vp->header_size += 4;
				td->counter_offset += 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	td->has_counter = false;
	अगर (get_uपूर्णांक_param(vp->parsed, "counter", &temp_पूर्णांक)) अणु
		अगर (temp_पूर्णांक > 0) अणु
			td->has_counter = true;
			vp->header_size += 4;
			अगर (get_uपूर्णांक_param(
				vp->parsed, "pin_counter", &temp_पूर्णांक)) अणु
				अगर (temp_पूर्णांक > 0)
					td->pin_counter = true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (get_uपूर्णांक_param(vp->parsed, "udp", &temp_पूर्णांक)) अणु
		अगर (temp_पूर्णांक > 0) अणु
			td->udp = true;
			vp->header_size += 4;
			td->counter_offset += 4;
			td->session_offset += 4;
			td->cookie_offset += 4;
		पूर्ण
	पूर्ण

	vp->rx_header_size = vp->header_size;
	अगर ((!td->ipv6) && (!td->udp))
		vp->rx_header_size += माप(काष्ठा iphdr);

	वापस 0;
पूर्ण

अटल पूर्णांक build_raw_transport_data(काष्ठा vector_निजी *vp)
अणु
	अगर (uml_raw_enable_vnet_headers(vp->fds->rx_fd)) अणु
		अगर (!uml_raw_enable_vnet_headers(vp->fds->tx_fd))
			वापस -1;
		vp->क्रमm_header = &raw_क्रमm_header;
		vp->verअगरy_header = &raw_verअगरy_header;
		vp->header_size = माप(काष्ठा virtio_net_hdr);
		vp->rx_header_size = माप(काष्ठा virtio_net_hdr);
		vp->dev->hw_features |= (NETIF_F_TSO | NETIF_F_GRO);
		vp->dev->features |=
			(NETIF_F_RXCSUM | NETIF_F_HW_CSUM |
				NETIF_F_TSO | NETIF_F_GRO);
		netdev_info(
			vp->dev,
			"raw: using vnet headers for tso and tx/rx checksum"
		);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक build_hybrid_transport_data(काष्ठा vector_निजी *vp)
अणु
	अगर (uml_raw_enable_vnet_headers(vp->fds->rx_fd)) अणु
		vp->क्रमm_header = &raw_क्रमm_header;
		vp->verअगरy_header = &raw_verअगरy_header;
		vp->header_size = माप(काष्ठा virtio_net_hdr);
		vp->rx_header_size = माप(काष्ठा virtio_net_hdr);
		vp->dev->hw_features |=
			(NETIF_F_TSO | NETIF_F_GSO | NETIF_F_GRO);
		vp->dev->features |=
			(NETIF_F_RXCSUM | NETIF_F_HW_CSUM |
				NETIF_F_TSO | NETIF_F_GSO | NETIF_F_GRO);
		netdev_info(
			vp->dev,
			"tap/raw hybrid: using vnet headers for tso and tx/rx checksum"
		);
	पूर्ण अन्यथा अणु
		वापस 0; /* करो not try to enable tap too अगर raw failed */
	पूर्ण
	अगर (uml_tap_enable_vnet_headers(vp->fds->tx_fd))
		वापस 0;
	वापस -1;
पूर्ण

अटल पूर्णांक build_tap_transport_data(काष्ठा vector_निजी *vp)
अणु
	/* "Pure" tap uses the same fd क्रम rx and tx */
	अगर (uml_tap_enable_vnet_headers(vp->fds->tx_fd)) अणु
		vp->क्रमm_header = &raw_क्रमm_header;
		vp->verअगरy_header = &raw_verअगरy_header;
		vp->header_size = माप(काष्ठा virtio_net_hdr);
		vp->rx_header_size = माप(काष्ठा virtio_net_hdr);
		vp->dev->hw_features |=
			(NETIF_F_TSO | NETIF_F_GSO | NETIF_F_GRO);
		vp->dev->features |=
			(NETIF_F_RXCSUM | NETIF_F_HW_CSUM |
				NETIF_F_TSO | NETIF_F_GSO | NETIF_F_GRO);
		netdev_info(
			vp->dev,
			"tap: using vnet headers for tso and tx/rx checksum"
		);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण


अटल पूर्णांक build_bess_transport_data(काष्ठा vector_निजी *vp)
अणु
	vp->क्रमm_header = शून्य;
	vp->verअगरy_header = शून्य;
	vp->header_size = 0;
	vp->rx_header_size = 0;
	वापस 0;
पूर्ण

पूर्णांक build_transport_data(काष्ठा vector_निजी *vp)
अणु
	अक्षर *transport = uml_vector_fetch_arg(vp->parsed, "transport");

	अगर (म_भेदन(transport, TRANS_GRE, TRANS_GRE_LEN) == 0)
		वापस build_gre_transport_data(vp);
	अगर (म_भेदन(transport, TRANS_L2TPV3, TRANS_L2TPV3_LEN) == 0)
		वापस build_l2tpv3_transport_data(vp);
	अगर (म_भेदन(transport, TRANS_RAW, TRANS_RAW_LEN) == 0)
		वापस build_raw_transport_data(vp);
	अगर (म_भेदन(transport, TRANS_TAP, TRANS_TAP_LEN) == 0)
		वापस build_tap_transport_data(vp);
	अगर (म_भेदन(transport, TRANS_HYBRID, TRANS_HYBRID_LEN) == 0)
		वापस build_hybrid_transport_data(vp);
	अगर (म_भेदन(transport, TRANS_BESS, TRANS_BESS_LEN) == 0)
		वापस build_bess_transport_data(vp);
	वापस 0;
पूर्ण

