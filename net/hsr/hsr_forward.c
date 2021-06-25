<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * Frame router क्रम HSR and PRP.
 */

#समावेश "hsr_forward.h"
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश "hsr_main.h"
#समावेश "hsr_framereg.h"

काष्ठा hsr_node;

/* The uses I can see क्रम these HSR supervision frames are:
 * 1) Use the frames that are sent after node initialization ("HSR_TLV.Type =
 *    22") to reset any sequence_nr counters beदीर्घing to that node. Useful अगर
 *    the other node's counter has been reset क्रम some reason.
 *    --
 *    Or not - resetting the counter and bridging the frame would create a
 *    loop, unक्रमtunately.
 *
 * 2) Use the LअगरeCheck frames to detect ring अवरोधs. I.e. अगर no LअगरeCheck
 *    frame is received from a particular node, we know something is wrong.
 *    We just रेजिस्टर these (as with normal frames) and throw them away.
 *
 * 3) Allow dअगरferent MAC addresses क्रम the two slave पूर्णांकerfaces, using the
 *    MacAddressA field.
 */
अटल bool is_supervision_frame(काष्ठा hsr_priv *hsr, काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth_hdr;
	काष्ठा hsr_sup_tag *hsr_sup_tag;
	काष्ठा hsrv1_ethhdr_sp *hsr_V1_hdr;

	WARN_ON_ONCE(!skb_mac_header_was_set(skb));
	eth_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);

	/* Correct addr? */
	अगर (!ether_addr_equal(eth_hdr->h_dest,
			      hsr->sup_multicast_addr))
		वापस false;

	/* Correct ether type?. */
	अगर (!(eth_hdr->h_proto == htons(ETH_P_PRP) ||
	      eth_hdr->h_proto == htons(ETH_P_HSR)))
		वापस false;

	/* Get the supervision header from correct location. */
	अगर (eth_hdr->h_proto == htons(ETH_P_HSR)) अणु /* Okay HSRv1. */
		hsr_V1_hdr = (काष्ठा hsrv1_ethhdr_sp *)skb_mac_header(skb);
		अगर (hsr_V1_hdr->hsr.encap_proto != htons(ETH_P_PRP))
			वापस false;

		hsr_sup_tag = &hsr_V1_hdr->hsr_sup;
	पूर्ण अन्यथा अणु
		hsr_sup_tag =
		     &((काष्ठा hsrv0_ethhdr_sp *)skb_mac_header(skb))->hsr_sup;
	पूर्ण

	अगर (hsr_sup_tag->HSR_TLV_type != HSR_TLV_ANNOUNCE &&
	    hsr_sup_tag->HSR_TLV_type != HSR_TLV_LIFE_CHECK &&
	    hsr_sup_tag->HSR_TLV_type != PRP_TLV_LIFE_CHECK_DD &&
	    hsr_sup_tag->HSR_TLV_type != PRP_TLV_LIFE_CHECK_DA)
		वापस false;
	अगर (hsr_sup_tag->HSR_TLV_length != 12 &&
	    hsr_sup_tag->HSR_TLV_length != माप(काष्ठा hsr_sup_payload))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *create_stripped_skb_hsr(काष्ठा sk_buff *skb_in,
					       काष्ठा hsr_frame_info *frame)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक copylen;
	अचिन्हित अक्षर *dst, *src;

	skb_pull(skb_in, HSR_HLEN);
	skb = __pskb_copy(skb_in, skb_headroom(skb_in) - HSR_HLEN, GFP_ATOMIC);
	skb_push(skb_in, HSR_HLEN);
	अगर (!skb)
		वापस शून्य;

	skb_reset_mac_header(skb);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start -= HSR_HLEN;

	copylen = 2 * ETH_ALEN;
	अगर (frame->is_vlan)
		copylen += VLAN_HLEN;
	src = skb_mac_header(skb_in);
	dst = skb_mac_header(skb);
	स_नकल(dst, src, copylen);

	skb->protocol = eth_hdr(skb)->h_proto;
	वापस skb;
पूर्ण

काष्ठा sk_buff *hsr_get_untagged_frame(काष्ठा hsr_frame_info *frame,
				       काष्ठा hsr_port *port)
अणु
	अगर (!frame->skb_std) अणु
		अगर (frame->skb_hsr) अणु
			frame->skb_std =
				create_stripped_skb_hsr(frame->skb_hsr, frame);
		पूर्ण अन्यथा अणु
			/* Unexpected */
			WARN_ONCE(1, "%s:%d: Unexpected frame received (port_src %s)\n",
				  __खाता__, __LINE__, port->dev->name);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस skb_clone(frame->skb_std, GFP_ATOMIC);
पूर्ण

काष्ठा sk_buff *prp_get_untagged_frame(काष्ठा hsr_frame_info *frame,
				       काष्ठा hsr_port *port)
अणु
	अगर (!frame->skb_std) अणु
		अगर (frame->skb_prp) अणु
			/* trim the skb by len - HSR_HLEN to exclude RCT */
			skb_trim(frame->skb_prp,
				 frame->skb_prp->len - HSR_HLEN);
			frame->skb_std =
				__pskb_copy(frame->skb_prp,
					    skb_headroom(frame->skb_prp),
					    GFP_ATOMIC);
		पूर्ण अन्यथा अणु
			/* Unexpected */
			WARN_ONCE(1, "%s:%d: Unexpected frame received (port_src %s)\n",
				  __खाता__, __LINE__, port->dev->name);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस skb_clone(frame->skb_std, GFP_ATOMIC);
पूर्ण

अटल व्योम prp_set_lan_id(काष्ठा prp_rct *trailer,
			   काष्ठा hsr_port *port)
अणु
	पूर्णांक lane_id;

	अगर (port->type == HSR_PT_SLAVE_A)
		lane_id = 0;
	अन्यथा
		lane_id = 1;

	/* Add net_id in the upper 3 bits of lane_id */
	lane_id |= port->hsr->net_id;
	set_prp_lan_id(trailer, lane_id);
पूर्ण

/* Tailroom क्रम PRP rct should have been created beक्रमe calling this */
अटल काष्ठा sk_buff *prp_fill_rct(काष्ठा sk_buff *skb,
				    काष्ठा hsr_frame_info *frame,
				    काष्ठा hsr_port *port)
अणु
	काष्ठा prp_rct *trailer;
	पूर्णांक min_size = ETH_ZLEN;
	पूर्णांक lsdu_size;

	अगर (!skb)
		वापस skb;

	अगर (frame->is_vlan)
		min_size = VLAN_ETH_ZLEN;

	अगर (skb_put_padto(skb, min_size))
		वापस शून्य;

	trailer = (काष्ठा prp_rct *)skb_put(skb, HSR_HLEN);
	lsdu_size = skb->len - 14;
	अगर (frame->is_vlan)
		lsdu_size -= 4;
	prp_set_lan_id(trailer, port);
	set_prp_LSDU_size(trailer, lsdu_size);
	trailer->sequence_nr = htons(frame->sequence_nr);
	trailer->PRP_suffix = htons(ETH_P_PRP);
	skb->protocol = eth_hdr(skb)->h_proto;

	वापस skb;
पूर्ण

अटल व्योम hsr_set_path_id(काष्ठा hsr_ethhdr *hsr_ethhdr,
			    काष्ठा hsr_port *port)
अणु
	पूर्णांक path_id;

	अगर (port->type == HSR_PT_SLAVE_A)
		path_id = 0;
	अन्यथा
		path_id = 1;

	set_hsr_tag_path(&hsr_ethhdr->hsr_tag, path_id);
पूर्ण

अटल काष्ठा sk_buff *hsr_fill_tag(काष्ठा sk_buff *skb,
				    काष्ठा hsr_frame_info *frame,
				    काष्ठा hsr_port *port, u8 proto_version)
अणु
	काष्ठा hsr_ethhdr *hsr_ethhdr;
	पूर्णांक lsdu_size;

	/* pad to minimum packet size which is 60 + 6 (HSR tag) */
	अगर (skb_put_padto(skb, ETH_ZLEN + HSR_HLEN))
		वापस शून्य;

	lsdu_size = skb->len - 14;
	अगर (frame->is_vlan)
		lsdu_size -= 4;

	hsr_ethhdr = (काष्ठा hsr_ethhdr *)skb_mac_header(skb);

	hsr_set_path_id(hsr_ethhdr, port);
	set_hsr_tag_LSDU_size(&hsr_ethhdr->hsr_tag, lsdu_size);
	hsr_ethhdr->hsr_tag.sequence_nr = htons(frame->sequence_nr);
	hsr_ethhdr->hsr_tag.encap_proto = hsr_ethhdr->ethhdr.h_proto;
	hsr_ethhdr->ethhdr.h_proto = htons(proto_version ?
			ETH_P_HSR : ETH_P_PRP);
	skb->protocol = hsr_ethhdr->ethhdr.h_proto;

	वापस skb;
पूर्ण

/* If the original frame was an HSR tagged frame, just clone it to be sent
 * unchanged. Otherwise, create a निजी frame especially tagged क्रम 'port'.
 */
काष्ठा sk_buff *hsr_create_tagged_frame(काष्ठा hsr_frame_info *frame,
					काष्ठा hsr_port *port)
अणु
	अचिन्हित अक्षर *dst, *src;
	काष्ठा sk_buff *skb;
	पूर्णांक movelen;

	अगर (frame->skb_hsr) अणु
		काष्ठा hsr_ethhdr *hsr_ethhdr =
			(काष्ठा hsr_ethhdr *)skb_mac_header(frame->skb_hsr);

		/* set the lane id properly */
		hsr_set_path_id(hsr_ethhdr, port);
		वापस skb_clone(frame->skb_hsr, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (port->dev->features & NETIF_F_HW_HSR_TAG_INS) अणु
		वापस skb_clone(frame->skb_std, GFP_ATOMIC);
	पूर्ण

	/* Create the new skb with enough headroom to fit the HSR tag */
	skb = __pskb_copy(frame->skb_std,
			  skb_headroom(frame->skb_std) + HSR_HLEN, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;
	skb_reset_mac_header(skb);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start += HSR_HLEN;

	movelen = ETH_HLEN;
	अगर (frame->is_vlan)
		movelen += VLAN_HLEN;

	src = skb_mac_header(skb);
	dst = skb_push(skb, HSR_HLEN);
	स_हटाओ(dst, src, movelen);
	skb_reset_mac_header(skb);

	/* skb_put_padto मुक्त skb on error and hsr_fill_tag वापसs शून्य in
	 * that हाल
	 */
	वापस hsr_fill_tag(skb, frame, port, port->hsr->prot_version);
पूर्ण

काष्ठा sk_buff *prp_create_tagged_frame(काष्ठा hsr_frame_info *frame,
					काष्ठा hsr_port *port)
अणु
	काष्ठा sk_buff *skb;

	अगर (frame->skb_prp) अणु
		काष्ठा prp_rct *trailer = skb_get_PRP_rct(frame->skb_prp);

		अगर (trailer) अणु
			prp_set_lan_id(trailer, port);
		पूर्ण अन्यथा अणु
			WARN_ONCE(!trailer, "errored PRP skb");
			वापस शून्य;
		पूर्ण
		वापस skb_clone(frame->skb_prp, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (port->dev->features & NETIF_F_HW_HSR_TAG_INS) अणु
		वापस skb_clone(frame->skb_std, GFP_ATOMIC);
	पूर्ण

	skb = skb_copy_expand(frame->skb_std, 0,
			      skb_tailroom(frame->skb_std) + HSR_HLEN,
			      GFP_ATOMIC);
	prp_fill_rct(skb, frame, port);

	वापस skb;
पूर्ण

अटल व्योम hsr_deliver_master(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       काष्ठा hsr_node *node_src)
अणु
	bool was_multicast_frame;
	पूर्णांक res;

	was_multicast_frame = (skb->pkt_type == PACKET_MULTICAST);
	hsr_addr_subst_source(node_src, skb);
	skb_pull(skb, ETH_HLEN);
	res = netअगर_rx(skb);
	अगर (res == NET_RX_DROP) अणु
		dev->stats.rx_dropped++;
	पूर्ण अन्यथा अणु
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		अगर (was_multicast_frame)
			dev->stats.multicast++;
	पूर्ण
पूर्ण

अटल पूर्णांक hsr_xmit(काष्ठा sk_buff *skb, काष्ठा hsr_port *port,
		    काष्ठा hsr_frame_info *frame)
अणु
	अगर (frame->port_rcv->type == HSR_PT_MASTER) अणु
		hsr_addr_subst_dest(frame->node_src, skb, port);

		/* Address substitution (IEC62439-3 pp 26, 50): replace mac
		 * address of outgoing frame with that of the outgoing slave's.
		 */
		ether_addr_copy(eth_hdr(skb)->h_source, port->dev->dev_addr);
	पूर्ण
	वापस dev_queue_xmit(skb);
पूर्ण

bool prp_drop_frame(काष्ठा hsr_frame_info *frame, काष्ठा hsr_port *port)
अणु
	वापस ((frame->port_rcv->type == HSR_PT_SLAVE_A &&
		 port->type ==  HSR_PT_SLAVE_B) ||
		(frame->port_rcv->type == HSR_PT_SLAVE_B &&
		 port->type ==  HSR_PT_SLAVE_A));
पूर्ण

bool hsr_drop_frame(काष्ठा hsr_frame_info *frame, काष्ठा hsr_port *port)
अणु
	अगर (port->dev->features & NETIF_F_HW_HSR_FWD)
		वापस prp_drop_frame(frame, port);

	वापस false;
पूर्ण

/* Forward the frame through all devices except:
 * - Back through the receiving device
 * - If it's a HSR frame: through a device where it has passed beक्रमe
 * - अगर it's a PRP frame: through another PRP slave device (no bridge)
 * - To the local HSR master only अगर the frame is directly addressed to it, or
 *   a non-supervision multicast or broadcast frame.
 *
 * HSR slave devices should insert a HSR tag पूर्णांकo the frame, or क्रमward the
 * frame unchanged अगर it's alपढ़ोy tagged. Interlink devices should strip HSR
 * tags अगर they're of the non-HSR type (but only after duplicate discard). The
 * master device always strips HSR tags.
 */
अटल व्योम hsr_क्रमward_करो(काष्ठा hsr_frame_info *frame)
अणु
	काष्ठा hsr_port *port;
	काष्ठा sk_buff *skb;
	bool sent = false;

	hsr_क्रम_each_port(frame->port_rcv->hsr, port) अणु
		काष्ठा hsr_priv *hsr = port->hsr;
		/* Don't send frame back the way it came */
		अगर (port == frame->port_rcv)
			जारी;

		/* Don't deliver locally unless we should */
		अगर (port->type == HSR_PT_MASTER && !frame->is_local_dest)
			जारी;

		/* Deliver frames directly addressed to us to master only */
		अगर (port->type != HSR_PT_MASTER && frame->is_local_exclusive)
			जारी;

		/* If hardware duplicate generation is enabled, only send out
		 * one port.
		 */
		अगर ((port->dev->features & NETIF_F_HW_HSR_DUP) && sent)
			जारी;

		/* Don't send frame over port where it has been sent beक्रमe.
		 * Also fro SAN, this shouldn't be करोne.
		 */
		अगर (!frame->is_from_san &&
		    hsr_रेजिस्टर_frame_out(port, frame->node_src,
					   frame->sequence_nr))
			जारी;

		अगर (frame->is_supervision && port->type == HSR_PT_MASTER) अणु
			hsr_handle_sup_frame(frame);
			जारी;
		पूर्ण

		/* Check अगर frame is to be dropped. Eg. क्रम PRP no क्रमward
		 * between ports.
		 */
		अगर (hsr->proto_ops->drop_frame &&
		    hsr->proto_ops->drop_frame(frame, port))
			जारी;

		अगर (port->type != HSR_PT_MASTER)
			skb = hsr->proto_ops->create_tagged_frame(frame, port);
		अन्यथा
			skb = hsr->proto_ops->get_untagged_frame(frame, port);

		अगर (!skb) अणु
			frame->port_rcv->dev->stats.rx_dropped++;
			जारी;
		पूर्ण

		skb->dev = port->dev;
		अगर (port->type == HSR_PT_MASTER) अणु
			hsr_deliver_master(skb, port->dev, frame->node_src);
		पूर्ण अन्यथा अणु
			अगर (!hsr_xmit(skb, port, frame))
				sent = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम check_local_dest(काष्ठा hsr_priv *hsr, काष्ठा sk_buff *skb,
			     काष्ठा hsr_frame_info *frame)
अणु
	अगर (hsr_addr_is_self(hsr, eth_hdr(skb)->h_dest)) अणु
		frame->is_local_exclusive = true;
		skb->pkt_type = PACKET_HOST;
	पूर्ण अन्यथा अणु
		frame->is_local_exclusive = false;
	पूर्ण

	अगर (skb->pkt_type == PACKET_HOST ||
	    skb->pkt_type == PACKET_MULTICAST ||
	    skb->pkt_type == PACKET_BROADCAST) अणु
		frame->is_local_dest = true;
	पूर्ण अन्यथा अणु
		frame->is_local_dest = false;
	पूर्ण
पूर्ण

अटल व्योम handle_std_frame(काष्ठा sk_buff *skb,
			     काष्ठा hsr_frame_info *frame)
अणु
	काष्ठा hsr_port *port = frame->port_rcv;
	काष्ठा hsr_priv *hsr = port->hsr;
	अचिन्हित दीर्घ irqflags;

	frame->skb_hsr = शून्य;
	frame->skb_prp = शून्य;
	frame->skb_std = skb;

	अगर (port->type != HSR_PT_MASTER) अणु
		frame->is_from_san = true;
	पूर्ण अन्यथा अणु
		/* Sequence nr क्रम the master node */
		spin_lock_irqsave(&hsr->seqnr_lock, irqflags);
		frame->sequence_nr = hsr->sequence_nr;
		hsr->sequence_nr++;
		spin_unlock_irqrestore(&hsr->seqnr_lock, irqflags);
	पूर्ण
पूर्ण

पूर्णांक hsr_fill_frame_info(__be16 proto, काष्ठा sk_buff *skb,
			काष्ठा hsr_frame_info *frame)
अणु
	काष्ठा hsr_port *port = frame->port_rcv;
	काष्ठा hsr_priv *hsr = port->hsr;

	/* HSRv0 supervisory frames द्विगुन as a tag so treat them as tagged. */
	अगर ((!hsr->prot_version && proto == htons(ETH_P_PRP)) ||
	    proto == htons(ETH_P_HSR)) अणु
		/* Check अगर skb contains hsr_ethhdr */
		अगर (skb->mac_len < माप(काष्ठा hsr_ethhdr))
			वापस -EINVAL;

		/* HSR tagged frame :- Data or Supervision */
		frame->skb_std = शून्य;
		frame->skb_prp = शून्य;
		frame->skb_hsr = skb;
		frame->sequence_nr = hsr_get_skb_sequence_nr(skb);
		वापस 0;
	पूर्ण

	/* Standard frame or PRP from master port */
	handle_std_frame(skb, frame);

	वापस 0;
पूर्ण

पूर्णांक prp_fill_frame_info(__be16 proto, काष्ठा sk_buff *skb,
			काष्ठा hsr_frame_info *frame)
अणु
	/* Supervision frame */
	काष्ठा prp_rct *rct = skb_get_PRP_rct(skb);

	अगर (rct &&
	    prp_check_lsdu_size(skb, rct, frame->is_supervision)) अणु
		frame->skb_hsr = शून्य;
		frame->skb_std = शून्य;
		frame->skb_prp = skb;
		frame->sequence_nr = prp_get_skb_sequence_nr(rct);
		वापस 0;
	पूर्ण
	handle_std_frame(skb, frame);

	वापस 0;
पूर्ण

अटल पूर्णांक fill_frame_info(काष्ठा hsr_frame_info *frame,
			   काष्ठा sk_buff *skb, काष्ठा hsr_port *port)
अणु
	काष्ठा hsr_priv *hsr = port->hsr;
	काष्ठा hsr_vlan_ethhdr *vlan_hdr;
	काष्ठा ethhdr *ethhdr;
	__be16 proto;
	पूर्णांक ret;

	/* Check अगर skb contains ethhdr */
	अगर (skb->mac_len < माप(काष्ठा ethhdr))
		वापस -EINVAL;

	स_रखो(frame, 0, माप(*frame));
	frame->is_supervision = is_supervision_frame(port->hsr, skb);
	frame->node_src = hsr_get_node(port, &hsr->node_db, skb,
				       frame->is_supervision,
				       port->type);
	अगर (!frame->node_src)
		वापस -1; /* Unknown node and !is_supervision, or no mem */

	ethhdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	frame->is_vlan = false;
	proto = ethhdr->h_proto;

	अगर (proto == htons(ETH_P_8021Q))
		frame->is_vlan = true;

	अगर (frame->is_vlan) अणु
		vlan_hdr = (काष्ठा hsr_vlan_ethhdr *)ethhdr;
		proto = vlan_hdr->vlanhdr.h_vlan_encapsulated_proto;
		/* FIXME: */
		netdev_warn_once(skb->dev, "VLAN not yet supported");
	पूर्ण

	frame->is_from_san = false;
	frame->port_rcv = port;
	ret = hsr->proto_ops->fill_frame_info(proto, skb, frame);
	अगर (ret)
		वापस ret;

	check_local_dest(port->hsr, skb, frame);

	वापस 0;
पूर्ण

/* Must be called holding rcu पढ़ो lock (because of the port parameter) */
व्योम hsr_क्रमward_skb(काष्ठा sk_buff *skb, काष्ठा hsr_port *port)
अणु
	काष्ठा hsr_frame_info frame;

	अगर (fill_frame_info(&frame, skb, port) < 0)
		जाओ out_drop;

	hsr_रेजिस्टर_frame_in(frame.node_src, port, frame.sequence_nr);
	hsr_क्रमward_करो(&frame);
	/* Gets called क्रम ingress frames as well as egress from master port.
	 * So check and increment stats क्रम master port only here.
	 */
	अगर (port->type == HSR_PT_MASTER) अणु
		port->dev->stats.tx_packets++;
		port->dev->stats.tx_bytes += skb->len;
	पूर्ण

	kमुक्त_skb(frame.skb_hsr);
	kमुक्त_skb(frame.skb_prp);
	kमुक्त_skb(frame.skb_std);
	वापस;

out_drop:
	port->dev->stats.tx_dropped++;
	kमुक्त_skb(skb);
पूर्ण
