<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * The HSR spec says never to क्रमward the same frame twice on the same
 * पूर्णांकerface. A frame is identअगरied by its source MAC address and its HSR
 * sequence number. This code keeps track of senders and their sequence numbers
 * to allow filtering of duplicate frames, and to detect HSR ring errors.
 * Same code handles filtering of duplicates क्रम PRP as well.
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>
#समावेश "hsr_main.h"
#समावेश "hsr_framereg.h"
#समावेश "hsr_netlink.h"

/*	TODO: use hash lists क्रम mac addresses (linux/jhash.h)?    */

/* seq_nr_after(a, b) - वापस true अगर a is after (higher in sequence than) b,
 * false otherwise.
 */
अटल bool seq_nr_after(u16 a, u16 b)
अणु
	/* Remove inconsistency where
	 * seq_nr_after(a, b) == seq_nr_beक्रमe(a, b)
	 */
	अगर ((पूर्णांक)b - a == 32768)
		वापस false;

	वापस (((s16)(b - a)) < 0);
पूर्ण

#घोषणा seq_nr_beक्रमe(a, b)		seq_nr_after((b), (a))
#घोषणा seq_nr_beक्रमe_or_eq(a, b)	(!seq_nr_after((a), (b)))

bool hsr_addr_is_self(काष्ठा hsr_priv *hsr, अचिन्हित अक्षर *addr)
अणु
	काष्ठा hsr_node *node;

	node = list_first_or_null_rcu(&hsr->self_node_db, काष्ठा hsr_node,
				      mac_list);
	अगर (!node) अणु
		WARN_ONCE(1, "HSR: No self node\n");
		वापस false;
	पूर्ण

	अगर (ether_addr_equal(addr, node->macaddress_A))
		वापस true;
	अगर (ether_addr_equal(addr, node->macaddress_B))
		वापस true;

	वापस false;
पूर्ण

/* Search क्रम mac entry. Caller must hold rcu पढ़ो lock.
 */
अटल काष्ठा hsr_node *find_node_by_addr_A(काष्ठा list_head *node_db,
					    स्थिर अचिन्हित अक्षर addr[ETH_ALEN])
अणु
	काष्ठा hsr_node *node;

	list_क्रम_each_entry_rcu(node, node_db, mac_list) अणु
		अगर (ether_addr_equal(node->macaddress_A, addr))
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Helper क्रम device init; the self_node_db is used in hsr_rcv() to recognize
 * frames from self that's been looped over the HSR ring.
 */
पूर्णांक hsr_create_self_node(काष्ठा hsr_priv *hsr,
			 अचिन्हित अक्षर addr_a[ETH_ALEN],
			 अचिन्हित अक्षर addr_b[ETH_ALEN])
अणु
	काष्ठा list_head *self_node_db = &hsr->self_node_db;
	काष्ठा hsr_node *node, *oldnode;

	node = kदो_स्मृति(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	ether_addr_copy(node->macaddress_A, addr_a);
	ether_addr_copy(node->macaddress_B, addr_b);

	spin_lock_bh(&hsr->list_lock);
	oldnode = list_first_or_null_rcu(self_node_db,
					 काष्ठा hsr_node, mac_list);
	अगर (oldnode) अणु
		list_replace_rcu(&oldnode->mac_list, &node->mac_list);
		spin_unlock_bh(&hsr->list_lock);
		kमुक्त_rcu(oldnode, rcu_head);
	पूर्ण अन्यथा अणु
		list_add_tail_rcu(&node->mac_list, self_node_db);
		spin_unlock_bh(&hsr->list_lock);
	पूर्ण

	वापस 0;
पूर्ण

व्योम hsr_del_self_node(काष्ठा hsr_priv *hsr)
अणु
	काष्ठा list_head *self_node_db = &hsr->self_node_db;
	काष्ठा hsr_node *node;

	spin_lock_bh(&hsr->list_lock);
	node = list_first_or_null_rcu(self_node_db, काष्ठा hsr_node, mac_list);
	अगर (node) अणु
		list_del_rcu(&node->mac_list);
		kमुक्त_rcu(node, rcu_head);
	पूर्ण
	spin_unlock_bh(&hsr->list_lock);
पूर्ण

व्योम hsr_del_nodes(काष्ठा list_head *node_db)
अणु
	काष्ठा hsr_node *node;
	काष्ठा hsr_node *पंचांगp;

	list_क्रम_each_entry_safe(node, पंचांगp, node_db, mac_list)
		kमुक्त(node);
पूर्ण

व्योम prp_handle_san_frame(bool san, क्रमागत hsr_port_type port,
			  काष्ठा hsr_node *node)
अणु
	/* Mark अगर the SAN node is over LAN_A or LAN_B */
	अगर (port == HSR_PT_SLAVE_A) अणु
		node->san_a = true;
		वापस;
	पूर्ण

	अगर (port == HSR_PT_SLAVE_B)
		node->san_b = true;
पूर्ण

/* Allocate an hsr_node and add it to node_db. 'addr' is the node's address_A;
 * seq_out is used to initialize filtering of outgoing duplicate frames
 * originating from the newly added node.
 */
अटल काष्ठा hsr_node *hsr_add_node(काष्ठा hsr_priv *hsr,
				     काष्ठा list_head *node_db,
				     अचिन्हित अक्षर addr[],
				     u16 seq_out, bool san,
				     क्रमागत hsr_port_type rx_port)
अणु
	काष्ठा hsr_node *new_node, *node;
	अचिन्हित दीर्घ now;
	पूर्णांक i;

	new_node = kzalloc(माप(*new_node), GFP_ATOMIC);
	अगर (!new_node)
		वापस शून्य;

	ether_addr_copy(new_node->macaddress_A, addr);

	/* We are only पूर्णांकerested in समय dअगरfs here, so use current jअगरfies
	 * as initialization. (0 could trigger an spurious ring error warning).
	 */
	now = jअगरfies;
	क्रम (i = 0; i < HSR_PT_PORTS; i++) अणु
		new_node->समय_in[i] = now;
		new_node->समय_out[i] = now;
	पूर्ण
	क्रम (i = 0; i < HSR_PT_PORTS; i++)
		new_node->seq_out[i] = seq_out;

	अगर (san && hsr->proto_ops->handle_san_frame)
		hsr->proto_ops->handle_san_frame(san, rx_port, new_node);

	spin_lock_bh(&hsr->list_lock);
	list_क्रम_each_entry_rcu(node, node_db, mac_list,
				lockdep_is_held(&hsr->list_lock)) अणु
		अगर (ether_addr_equal(node->macaddress_A, addr))
			जाओ out;
		अगर (ether_addr_equal(node->macaddress_B, addr))
			जाओ out;
	पूर्ण
	list_add_tail_rcu(&new_node->mac_list, node_db);
	spin_unlock_bh(&hsr->list_lock);
	वापस new_node;
out:
	spin_unlock_bh(&hsr->list_lock);
	kमुक्त(new_node);
	वापस node;
पूर्ण

व्योम prp_update_san_info(काष्ठा hsr_node *node, bool is_sup)
अणु
	अगर (!is_sup)
		वापस;

	node->san_a = false;
	node->san_b = false;
पूर्ण

/* Get the hsr_node from which 'skb' was sent.
 */
काष्ठा hsr_node *hsr_get_node(काष्ठा hsr_port *port, काष्ठा list_head *node_db,
			      काष्ठा sk_buff *skb, bool is_sup,
			      क्रमागत hsr_port_type rx_port)
अणु
	काष्ठा hsr_priv *hsr = port->hsr;
	काष्ठा hsr_node *node;
	काष्ठा ethhdr *ethhdr;
	काष्ठा prp_rct *rct;
	bool san = false;
	u16 seq_out;

	अगर (!skb_mac_header_was_set(skb))
		वापस शून्य;

	ethhdr = (काष्ठा ethhdr *)skb_mac_header(skb);

	list_क्रम_each_entry_rcu(node, node_db, mac_list) अणु
		अगर (ether_addr_equal(node->macaddress_A, ethhdr->h_source)) अणु
			अगर (hsr->proto_ops->update_san_info)
				hsr->proto_ops->update_san_info(node, is_sup);
			वापस node;
		पूर्ण
		अगर (ether_addr_equal(node->macaddress_B, ethhdr->h_source)) अणु
			अगर (hsr->proto_ops->update_san_info)
				hsr->proto_ops->update_san_info(node, is_sup);
			वापस node;
		पूर्ण
	पूर्ण

	/* Everyone may create a node entry, connected node to a HSR/PRP
	 * device.
	 */
	अगर (ethhdr->h_proto == htons(ETH_P_PRP) ||
	    ethhdr->h_proto == htons(ETH_P_HSR)) अणु
		/* Use the existing sequence_nr from the tag as starting poपूर्णांक
		 * क्रम filtering duplicate frames.
		 */
		seq_out = hsr_get_skb_sequence_nr(skb) - 1;
	पूर्ण अन्यथा अणु
		rct = skb_get_PRP_rct(skb);
		अगर (rct && prp_check_lsdu_size(skb, rct, is_sup)) अणु
			seq_out = prp_get_skb_sequence_nr(rct);
		पूर्ण अन्यथा अणु
			अगर (rx_port != HSR_PT_MASTER)
				san = true;
			seq_out = HSR_SEQNR_START;
		पूर्ण
	पूर्ण

	वापस hsr_add_node(hsr, node_db, ethhdr->h_source, seq_out,
			    san, rx_port);
पूर्ण

/* Use the Supervision frame's info about an eventual macaddress_B क्रम merging
 * nodes that has previously had their macaddress_B रेजिस्टरed as a separate
 * node.
 */
व्योम hsr_handle_sup_frame(काष्ठा hsr_frame_info *frame)
अणु
	काष्ठा hsr_node *node_curr = frame->node_src;
	काष्ठा hsr_port *port_rcv = frame->port_rcv;
	काष्ठा hsr_priv *hsr = port_rcv->hsr;
	काष्ठा hsr_sup_payload *hsr_sp;
	काष्ठा hsr_node *node_real;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा list_head *node_db;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक i;

	/* Here either frame->skb_hsr or frame->skb_prp should be
	 * valid as supervision frame always will have protocol
	 * header info.
	 */
	अगर (frame->skb_hsr)
		skb = frame->skb_hsr;
	अन्यथा अगर (frame->skb_prp)
		skb = frame->skb_prp;
	अन्यथा अगर (frame->skb_std)
		skb = frame->skb_std;
	अगर (!skb)
		वापस;

	ethhdr = (काष्ठा ethhdr *)skb_mac_header(skb);

	/* Leave the ethernet header. */
	skb_pull(skb, माप(काष्ठा ethhdr));

	/* And leave the HSR tag. */
	अगर (ethhdr->h_proto == htons(ETH_P_HSR))
		skb_pull(skb, माप(काष्ठा hsr_tag));

	/* And leave the HSR sup tag. */
	skb_pull(skb, माप(काष्ठा hsr_sup_tag));

	hsr_sp = (काष्ठा hsr_sup_payload *)skb->data;

	/* Merge node_curr (रेजिस्टरed on macaddress_B) पूर्णांकo node_real */
	node_db = &port_rcv->hsr->node_db;
	node_real = find_node_by_addr_A(node_db, hsr_sp->macaddress_A);
	अगर (!node_real)
		/* No frame received from AddrA of this node yet */
		node_real = hsr_add_node(hsr, node_db, hsr_sp->macaddress_A,
					 HSR_SEQNR_START - 1, true,
					 port_rcv->type);
	अगर (!node_real)
		जाओ करोne; /* No mem */
	अगर (node_real == node_curr)
		/* Node has alपढ़ोy been merged */
		जाओ करोne;

	ether_addr_copy(node_real->macaddress_B, ethhdr->h_source);
	क्रम (i = 0; i < HSR_PT_PORTS; i++) अणु
		अगर (!node_curr->समय_in_stale[i] &&
		    समय_after(node_curr->समय_in[i], node_real->समय_in[i])) अणु
			node_real->समय_in[i] = node_curr->समय_in[i];
			node_real->समय_in_stale[i] =
						node_curr->समय_in_stale[i];
		पूर्ण
		अगर (seq_nr_after(node_curr->seq_out[i], node_real->seq_out[i]))
			node_real->seq_out[i] = node_curr->seq_out[i];
	पूर्ण
	node_real->addr_B_port = port_rcv->type;

	spin_lock_bh(&hsr->list_lock);
	list_del_rcu(&node_curr->mac_list);
	spin_unlock_bh(&hsr->list_lock);
	kमुक्त_rcu(node_curr, rcu_head);

करोne:
	/* PRP uses v0 header */
	अगर (ethhdr->h_proto == htons(ETH_P_HSR))
		skb_push(skb, माप(काष्ठा hsrv1_ethhdr_sp));
	अन्यथा
		skb_push(skb, माप(काष्ठा hsrv0_ethhdr_sp));
पूर्ण

/* 'skb' is a frame meant क्रम this host, that is to be passed to upper layers.
 *
 * If the frame was sent by a node's B पूर्णांकerface, replace the source
 * address with that node's "official" address (macaddress_A) so that upper
 * layers recognize where it came from.
 */
व्योम hsr_addr_subst_source(काष्ठा hsr_node *node, काष्ठा sk_buff *skb)
अणु
	अगर (!skb_mac_header_was_set(skb)) अणु
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		वापस;
	पूर्ण

	स_नकल(&eth_hdr(skb)->h_source, node->macaddress_A, ETH_ALEN);
पूर्ण

/* 'skb' is a frame meant क्रम another host.
 * 'port' is the outgoing पूर्णांकerface
 *
 * Substitute the target (dest) MAC address अगर necessary, so the it matches the
 * recipient पूर्णांकerface MAC address, regardless of whether that is the
 * recipient's A or B पूर्णांकerface.
 * This is needed to keep the packets flowing through चयनes that learn on
 * which "side" the dअगरferent पूर्णांकerfaces are.
 */
व्योम hsr_addr_subst_dest(काष्ठा hsr_node *node_src, काष्ठा sk_buff *skb,
			 काष्ठा hsr_port *port)
अणु
	काष्ठा hsr_node *node_dst;

	अगर (!skb_mac_header_was_set(skb)) अणु
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		वापस;
	पूर्ण

	अगर (!is_unicast_ether_addr(eth_hdr(skb)->h_dest))
		वापस;

	node_dst = find_node_by_addr_A(&port->hsr->node_db,
				       eth_hdr(skb)->h_dest);
	अगर (!node_dst) अणु
		अगर (net_ratelimit())
			netdev_err(skb->dev, "%s: Unknown node\n", __func__);
		वापस;
	पूर्ण
	अगर (port->type != node_dst->addr_B_port)
		वापस;

	अगर (is_valid_ether_addr(node_dst->macaddress_B))
		ether_addr_copy(eth_hdr(skb)->h_dest, node_dst->macaddress_B);
पूर्ण

व्योम hsr_रेजिस्टर_frame_in(काष्ठा hsr_node *node, काष्ठा hsr_port *port,
			   u16 sequence_nr)
अणु
	/* Don't रेजिस्टर incoming frames without a valid sequence number. This
	 * ensures entries of restarted nodes माला_लो pruned so that they can
	 * re-रेजिस्टर and resume communications.
	 */
	अगर (seq_nr_beक्रमe(sequence_nr, node->seq_out[port->type]))
		वापस;

	node->समय_in[port->type] = jअगरfies;
	node->समय_in_stale[port->type] = false;
पूर्ण

/* 'skb' is a HSR Ethernet frame (with a HSR tag inserted), with a valid
 * ethhdr->h_source address and skb->mac_header set.
 *
 * Return:
 *	 1 अगर frame can be shown to have been sent recently on this पूर्णांकerface,
 *	 0 otherwise, or
 *	 negative error code on error
 */
पूर्णांक hsr_रेजिस्टर_frame_out(काष्ठा hsr_port *port, काष्ठा hsr_node *node,
			   u16 sequence_nr)
अणु
	अगर (seq_nr_beक्रमe_or_eq(sequence_nr, node->seq_out[port->type]) &&
	    समय_is_after_jअगरfies(node->समय_out[port->type] +
	    msecs_to_jअगरfies(HSR_ENTRY_FORGET_TIME)))
		वापस 1;

	node->समय_out[port->type] = jअगरfies;
	node->seq_out[port->type] = sequence_nr;
	वापस 0;
पूर्ण

अटल काष्ठा hsr_port *get_late_port(काष्ठा hsr_priv *hsr,
				      काष्ठा hsr_node *node)
अणु
	अगर (node->समय_in_stale[HSR_PT_SLAVE_A])
		वापस hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	अगर (node->समय_in_stale[HSR_PT_SLAVE_B])
		वापस hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);

	अगर (समय_after(node->समय_in[HSR_PT_SLAVE_B],
		       node->समय_in[HSR_PT_SLAVE_A] +
					msecs_to_jअगरfies(MAX_SLAVE_DIFF)))
		वापस hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	अगर (समय_after(node->समय_in[HSR_PT_SLAVE_A],
		       node->समय_in[HSR_PT_SLAVE_B] +
					msecs_to_jअगरfies(MAX_SLAVE_DIFF)))
		वापस hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);

	वापस शून्य;
पूर्ण

/* Remove stale sequence_nr records. Called by समयr every
 * HSR_LIFE_CHECK_INTERVAL (two seconds or so).
 */
व्योम hsr_prune_nodes(काष्ठा समयr_list *t)
अणु
	काष्ठा hsr_priv *hsr = from_समयr(hsr, t, prune_समयr);
	काष्ठा hsr_node *node;
	काष्ठा hsr_node *पंचांगp;
	काष्ठा hsr_port *port;
	अचिन्हित दीर्घ बारtamp;
	अचिन्हित दीर्घ समय_a, समय_b;

	spin_lock_bh(&hsr->list_lock);
	list_क्रम_each_entry_safe(node, पंचांगp, &hsr->node_db, mac_list) अणु
		/* Don't prune own node. Neither समय_in[HSR_PT_SLAVE_A]
		 * nor समय_in[HSR_PT_SLAVE_B], will ever be updated क्रम
		 * the master port. Thus the master node will be repeatedly
		 * pruned leading to packet loss.
		 */
		अगर (hsr_addr_is_self(hsr, node->macaddress_A))
			जारी;

		/* Shorthand */
		समय_a = node->समय_in[HSR_PT_SLAVE_A];
		समय_b = node->समय_in[HSR_PT_SLAVE_B];

		/* Check क्रम बारtamps old enough to risk wrap-around */
		अगर (समय_after(jअगरfies, समय_a + MAX_JIFFY_OFFSET / 2))
			node->समय_in_stale[HSR_PT_SLAVE_A] = true;
		अगर (समय_after(jअगरfies, समय_b + MAX_JIFFY_OFFSET / 2))
			node->समय_in_stale[HSR_PT_SLAVE_B] = true;

		/* Get age of newest frame from node.
		 * At least one समय_in is OK here; nodes get pruned दीर्घ
		 * beक्रमe both समय_ins can get stale
		 */
		बारtamp = समय_a;
		अगर (node->समय_in_stale[HSR_PT_SLAVE_A] ||
		    (!node->समय_in_stale[HSR_PT_SLAVE_B] &&
		    समय_after(समय_b, समय_a)))
			बारtamp = समय_b;

		/* Warn of ring error only as दीर्घ as we get frames at all */
		अगर (समय_is_after_jअगरfies(बारtamp +
				msecs_to_jअगरfies(1.5 * MAX_SLAVE_DIFF))) अणु
			rcu_पढ़ो_lock();
			port = get_late_port(hsr, node);
			अगर (port)
				hsr_nl_ringerror(hsr, node->macaddress_A, port);
			rcu_पढ़ो_unlock();
		पूर्ण

		/* Prune old entries */
		अगर (समय_is_beक्रमe_jअगरfies(बारtamp +
				msecs_to_jअगरfies(HSR_NODE_FORGET_TIME))) अणु
			hsr_nl_nodeकरोwn(hsr, node->macaddress_A);
			list_del_rcu(&node->mac_list);
			/* Note that we need to मुक्त this entry later: */
			kमुक्त_rcu(node, rcu_head);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hsr->list_lock);

	/* Restart समयr */
	mod_समयr(&hsr->prune_समयr,
		  jअगरfies + msecs_to_jअगरfies(PRUNE_PERIOD));
पूर्ण

व्योम *hsr_get_next_node(काष्ठा hsr_priv *hsr, व्योम *_pos,
			अचिन्हित अक्षर addr[ETH_ALEN])
अणु
	काष्ठा hsr_node *node;

	अगर (!_pos) अणु
		node = list_first_or_null_rcu(&hsr->node_db,
					      काष्ठा hsr_node, mac_list);
		अगर (node)
			ether_addr_copy(addr, node->macaddress_A);
		वापस node;
	पूर्ण

	node = _pos;
	list_क्रम_each_entry_जारी_rcu(node, &hsr->node_db, mac_list) अणु
		ether_addr_copy(addr, node->macaddress_A);
		वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक hsr_get_node_data(काष्ठा hsr_priv *hsr,
		      स्थिर अचिन्हित अक्षर *addr,
		      अचिन्हित अक्षर addr_b[ETH_ALEN],
		      अचिन्हित पूर्णांक *addr_b_अगरindex,
		      पूर्णांक *अगर1_age,
		      u16 *अगर1_seq,
		      पूर्णांक *अगर2_age,
		      u16 *अगर2_seq)
अणु
	काष्ठा hsr_node *node;
	काष्ठा hsr_port *port;
	अचिन्हित दीर्घ tdअगरf;

	node = find_node_by_addr_A(&hsr->node_db, addr);
	अगर (!node)
		वापस -ENOENT;

	ether_addr_copy(addr_b, node->macaddress_B);

	tdअगरf = jअगरfies - node->समय_in[HSR_PT_SLAVE_A];
	अगर (node->समय_in_stale[HSR_PT_SLAVE_A])
		*अगर1_age = पूर्णांक_उच्च;
#अगर HZ <= MSEC_PER_SEC
	अन्यथा अगर (tdअगरf > msecs_to_jअगरfies(पूर्णांक_उच्च))
		*अगर1_age = पूर्णांक_उच्च;
#पूर्ण_अगर
	अन्यथा
		*अगर1_age = jअगरfies_to_msecs(tdअगरf);

	tdअगरf = jअगरfies - node->समय_in[HSR_PT_SLAVE_B];
	अगर (node->समय_in_stale[HSR_PT_SLAVE_B])
		*अगर2_age = पूर्णांक_उच्च;
#अगर HZ <= MSEC_PER_SEC
	अन्यथा अगर (tdअगरf > msecs_to_jअगरfies(पूर्णांक_उच्च))
		*अगर2_age = पूर्णांक_उच्च;
#पूर्ण_अगर
	अन्यथा
		*अगर2_age = jअगरfies_to_msecs(tdअगरf);

	/* Present sequence numbers as अगर they were incoming on पूर्णांकerface */
	*अगर1_seq = node->seq_out[HSR_PT_SLAVE_B];
	*अगर2_seq = node->seq_out[HSR_PT_SLAVE_A];

	अगर (node->addr_B_port != HSR_PT_NONE) अणु
		port = hsr_port_get_hsr(hsr, node->addr_B_port);
		*addr_b_अगरindex = port->dev->अगरindex;
	पूर्ण अन्यथा अणु
		*addr_b_अगरindex = -1;
	पूर्ण

	वापस 0;
पूर्ण
