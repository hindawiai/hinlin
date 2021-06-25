<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#समावेश "gateway_client.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/udp.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"

/* These are the offsets of the "hw type" and "hw address length" in the dhcp
 * packet starting at the beginning of the dhcp header
 */
#घोषणा BATADV_DHCP_HTYPE_OFFSET	1
#घोषणा BATADV_DHCP_HLEN_OFFSET		2
/* Value of htype representing Ethernet */
#घोषणा BATADV_DHCP_HTYPE_ETHERNET	0x01
/* This is the offset of the "chaddr" field in the dhcp packet starting at the
 * beginning of the dhcp header
 */
#घोषणा BATADV_DHCP_CHADDR_OFFSET	28

/**
 * batadv_gw_node_release() - release gw_node from lists and queue क्रम मुक्त
 *  after rcu grace period
 * @ref: kref poपूर्णांकer of the gw_node
 */
अटल व्योम batadv_gw_node_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_gw_node *gw_node;

	gw_node = container_of(ref, काष्ठा batadv_gw_node, refcount);

	batadv_orig_node_put(gw_node->orig_node);
	kमुक्त_rcu(gw_node, rcu);
पूर्ण

/**
 * batadv_gw_node_put() - decrement the gw_node refcounter and possibly release
 *  it
 * @gw_node: gateway node to मुक्त
 */
व्योम batadv_gw_node_put(काष्ठा batadv_gw_node *gw_node)
अणु
	kref_put(&gw_node->refcount, batadv_gw_node_release);
पूर्ण

/**
 * batadv_gw_get_selected_gw_node() - Get currently selected gateway
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: selected gateway (with increased refcnt), शून्य on errors
 */
काष्ठा batadv_gw_node *
batadv_gw_get_selected_gw_node(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_gw_node *gw_node;

	rcu_पढ़ो_lock();
	gw_node = rcu_dereference(bat_priv->gw.curr_gw);
	अगर (!gw_node)
		जाओ out;

	अगर (!kref_get_unless_zero(&gw_node->refcount))
		gw_node = शून्य;

out:
	rcu_पढ़ो_unlock();
	वापस gw_node;
पूर्ण

/**
 * batadv_gw_get_selected_orig() - Get originator of currently selected gateway
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: orig_node of selected gateway (with increased refcnt), शून्य on errors
 */
काष्ठा batadv_orig_node *
batadv_gw_get_selected_orig(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_gw_node *gw_node;
	काष्ठा batadv_orig_node *orig_node = शून्य;

	gw_node = batadv_gw_get_selected_gw_node(bat_priv);
	अगर (!gw_node)
		जाओ out;

	rcu_पढ़ो_lock();
	orig_node = gw_node->orig_node;
	अगर (!orig_node)
		जाओ unlock;

	अगर (!kref_get_unless_zero(&orig_node->refcount))
		orig_node = शून्य;

unlock:
	rcu_पढ़ो_unlock();
out:
	अगर (gw_node)
		batadv_gw_node_put(gw_node);
	वापस orig_node;
पूर्ण

अटल व्योम batadv_gw_select(काष्ठा batadv_priv *bat_priv,
			     काष्ठा batadv_gw_node *new_gw_node)
अणु
	काष्ठा batadv_gw_node *curr_gw_node;

	spin_lock_bh(&bat_priv->gw.list_lock);

	अगर (new_gw_node)
		kref_get(&new_gw_node->refcount);

	curr_gw_node = rcu_replace_poपूर्णांकer(bat_priv->gw.curr_gw, new_gw_node,
					   true);

	अगर (curr_gw_node)
		batadv_gw_node_put(curr_gw_node);

	spin_unlock_bh(&bat_priv->gw.list_lock);
पूर्ण

/**
 * batadv_gw_reselect() - क्रमce a gateway reselection
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Set a flag to remind the GW component to perक्रमm a new gateway reselection.
 * However this function करोes not ensure that the current gateway is going to be
 * deselected. The reselection mechanism may elect the same gateway once again.
 *
 * This means that invoking batadv_gw_reselect() करोes not guarantee a gateway
 * change and thereक्रमe a uevent is not necessarily expected.
 */
व्योम batadv_gw_reselect(काष्ठा batadv_priv *bat_priv)
अणु
	atomic_set(&bat_priv->gw.reselect, 1);
पूर्ण

/**
 * batadv_gw_check_client_stop() - check अगर client mode has been चयनed off
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * This function assumes the caller has checked that the gw state *is actually
 * changing*. This function is not supposed to be called when there is no state
 * change.
 */
व्योम batadv_gw_check_client_stop(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_gw_node *curr_gw;

	अगर (atomic_पढ़ो(&bat_priv->gw.mode) != BATADV_GW_MODE_CLIENT)
		वापस;

	curr_gw = batadv_gw_get_selected_gw_node(bat_priv);
	अगर (!curr_gw)
		वापस;

	/* deselect the current gateway so that next समय that client mode is
	 * enabled a proper GW_ADD event can be sent
	 */
	batadv_gw_select(bat_priv, शून्य);

	/* अगर baपंचांगan-adv is चयनing the gw client mode off and a gateway was
	 * alपढ़ोy selected, send a DEL uevent
	 */
	batadv_throw_uevent(bat_priv, BATADV_UEV_GW, BATADV_UEV_DEL, शून्य);

	batadv_gw_node_put(curr_gw);
पूर्ण

/**
 * batadv_gw_election() - Elect the best gateway
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_gw_election(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_gw_node *curr_gw = शून्य;
	काष्ठा batadv_gw_node *next_gw = शून्य;
	काष्ठा batadv_neigh_node *router = शून्य;
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य;
	अक्षर gw_addr[18] = अणु '\0' पूर्ण;

	अगर (atomic_पढ़ो(&bat_priv->gw.mode) != BATADV_GW_MODE_CLIENT)
		जाओ out;

	अगर (!bat_priv->algo_ops->gw.get_best_gw_node)
		जाओ out;

	curr_gw = batadv_gw_get_selected_gw_node(bat_priv);

	अगर (!batadv_atomic_dec_not_zero(&bat_priv->gw.reselect) && curr_gw)
		जाओ out;

	/* अगर gw.reselect is set to 1 it means that a previous call to
	 * gw.is_eligible() said that we have a new best GW, thereक्रमe it can
	 * now be picked from the list and selected
	 */
	next_gw = bat_priv->algo_ops->gw.get_best_gw_node(bat_priv);

	अगर (curr_gw == next_gw)
		जाओ out;

	अगर (next_gw) अणु
		प्र_लिखो(gw_addr, "%pM", next_gw->orig_node->orig);

		router = batadv_orig_router_get(next_gw->orig_node,
						BATADV_IF_DEFAULT);
		अगर (!router) अणु
			batadv_gw_reselect(bat_priv);
			जाओ out;
		पूर्ण

		router_अगरinfo = batadv_neigh_अगरinfo_get(router,
							BATADV_IF_DEFAULT);
		अगर (!router_अगरinfo) अणु
			batadv_gw_reselect(bat_priv);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (curr_gw && !next_gw) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Removing selected gateway - no gateway in range\n");
		batadv_throw_uevent(bat_priv, BATADV_UEV_GW, BATADV_UEV_DEL,
				    शून्य);
	पूर्ण अन्यथा अगर (!curr_gw && next_gw) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Adding route to gateway %pM (bandwidth: %u.%u/%u.%u MBit, tq: %i)\n",
			   next_gw->orig_node->orig,
			   next_gw->bandwidth_करोwn / 10,
			   next_gw->bandwidth_करोwn % 10,
			   next_gw->bandwidth_up / 10,
			   next_gw->bandwidth_up % 10,
			   router_अगरinfo->bat_iv.tq_avg);
		batadv_throw_uevent(bat_priv, BATADV_UEV_GW, BATADV_UEV_ADD,
				    gw_addr);
	पूर्ण अन्यथा अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Changing route to gateway %pM (bandwidth: %u.%u/%u.%u MBit, tq: %i)\n",
			   next_gw->orig_node->orig,
			   next_gw->bandwidth_करोwn / 10,
			   next_gw->bandwidth_करोwn % 10,
			   next_gw->bandwidth_up / 10,
			   next_gw->bandwidth_up % 10,
			   router_अगरinfo->bat_iv.tq_avg);
		batadv_throw_uevent(bat_priv, BATADV_UEV_GW, BATADV_UEV_CHANGE,
				    gw_addr);
	पूर्ण

	batadv_gw_select(bat_priv, next_gw);

out:
	अगर (curr_gw)
		batadv_gw_node_put(curr_gw);
	अगर (next_gw)
		batadv_gw_node_put(next_gw);
	अगर (router)
		batadv_neigh_node_put(router);
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);
पूर्ण

/**
 * batadv_gw_check_election() - Elect orig node as best gateway when eligible
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be checked
 */
व्योम batadv_gw_check_election(काष्ठा batadv_priv *bat_priv,
			      काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_orig_node *curr_gw_orig;

	/* पात immediately अगर the routing algorithm करोes not support gateway
	 * election
	 */
	अगर (!bat_priv->algo_ops->gw.is_eligible)
		वापस;

	curr_gw_orig = batadv_gw_get_selected_orig(bat_priv);
	अगर (!curr_gw_orig)
		जाओ reselect;

	/* this node alपढ़ोy is the gateway */
	अगर (curr_gw_orig == orig_node)
		जाओ out;

	अगर (!bat_priv->algo_ops->gw.is_eligible(bat_priv, curr_gw_orig,
						orig_node))
		जाओ out;

reselect:
	batadv_gw_reselect(bat_priv);
out:
	अगर (curr_gw_orig)
		batadv_orig_node_put(curr_gw_orig);
पूर्ण

/**
 * batadv_gw_node_add() - add gateway node to list of available gateways
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: originator announcing gateway capabilities
 * @gateway: announced bandwidth inक्रमmation
 *
 * Has to be called with the appropriate locks being acquired
 * (gw.list_lock).
 */
अटल व्योम batadv_gw_node_add(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_orig_node *orig_node,
			       काष्ठा batadv_tvlv_gateway_data *gateway)
अणु
	काष्ठा batadv_gw_node *gw_node;

	lockdep_निश्चित_held(&bat_priv->gw.list_lock);

	अगर (gateway->bandwidth_करोwn == 0)
		वापस;

	gw_node = kzalloc(माप(*gw_node), GFP_ATOMIC);
	अगर (!gw_node)
		वापस;

	kref_init(&gw_node->refcount);
	INIT_HLIST_NODE(&gw_node->list);
	kref_get(&orig_node->refcount);
	gw_node->orig_node = orig_node;
	gw_node->bandwidth_करोwn = ntohl(gateway->bandwidth_करोwn);
	gw_node->bandwidth_up = ntohl(gateway->bandwidth_up);

	kref_get(&gw_node->refcount);
	hlist_add_head_rcu(&gw_node->list, &bat_priv->gw.gateway_list);
	bat_priv->gw.generation++;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Found new gateway %pM -> gw bandwidth: %u.%u/%u.%u MBit\n",
		   orig_node->orig,
		   ntohl(gateway->bandwidth_करोwn) / 10,
		   ntohl(gateway->bandwidth_करोwn) % 10,
		   ntohl(gateway->bandwidth_up) / 10,
		   ntohl(gateway->bandwidth_up) % 10);

	/* करोn't वापस reference to new gw_node */
	batadv_gw_node_put(gw_node);
पूर्ण

/**
 * batadv_gw_node_get() - retrieve gateway node from list of available gateways
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: originator announcing gateway capabilities
 *
 * Return: gateway node अगर found or शून्य otherwise.
 */
काष्ठा batadv_gw_node *batadv_gw_node_get(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_gw_node *gw_node_पंचांगp, *gw_node = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(gw_node_पंचांगp, &bat_priv->gw.gateway_list,
				 list) अणु
		अगर (gw_node_पंचांगp->orig_node != orig_node)
			जारी;

		अगर (!kref_get_unless_zero(&gw_node_पंचांगp->refcount))
			जारी;

		gw_node = gw_node_पंचांगp;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस gw_node;
पूर्ण

/**
 * batadv_gw_node_update() - update list of available gateways with changed
 *  bandwidth inक्रमmation
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: originator announcing gateway capabilities
 * @gateway: announced bandwidth inक्रमmation
 */
व्योम batadv_gw_node_update(काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_orig_node *orig_node,
			   काष्ठा batadv_tvlv_gateway_data *gateway)
अणु
	काष्ठा batadv_gw_node *gw_node, *curr_gw = शून्य;

	spin_lock_bh(&bat_priv->gw.list_lock);
	gw_node = batadv_gw_node_get(bat_priv, orig_node);
	अगर (!gw_node) अणु
		batadv_gw_node_add(bat_priv, orig_node, gateway);
		spin_unlock_bh(&bat_priv->gw.list_lock);
		जाओ out;
	पूर्ण
	spin_unlock_bh(&bat_priv->gw.list_lock);

	अगर (gw_node->bandwidth_करोwn == ntohl(gateway->bandwidth_करोwn) &&
	    gw_node->bandwidth_up == ntohl(gateway->bandwidth_up))
		जाओ out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Gateway bandwidth of originator %pM changed from %u.%u/%u.%u MBit to %u.%u/%u.%u MBit\n",
		   orig_node->orig,
		   gw_node->bandwidth_करोwn / 10,
		   gw_node->bandwidth_करोwn % 10,
		   gw_node->bandwidth_up / 10,
		   gw_node->bandwidth_up % 10,
		   ntohl(gateway->bandwidth_करोwn) / 10,
		   ntohl(gateway->bandwidth_करोwn) % 10,
		   ntohl(gateway->bandwidth_up) / 10,
		   ntohl(gateway->bandwidth_up) % 10);

	gw_node->bandwidth_करोwn = ntohl(gateway->bandwidth_करोwn);
	gw_node->bandwidth_up = ntohl(gateway->bandwidth_up);

	अगर (ntohl(gateway->bandwidth_करोwn) == 0) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Gateway %pM removed from gateway list\n",
			   orig_node->orig);

		/* Note: We करोn't need a शून्य check here, since curr_gw never
		 * माला_लो dereferenced.
		 */
		spin_lock_bh(&bat_priv->gw.list_lock);
		अगर (!hlist_unhashed(&gw_node->list)) अणु
			hlist_del_init_rcu(&gw_node->list);
			batadv_gw_node_put(gw_node);
			bat_priv->gw.generation++;
		पूर्ण
		spin_unlock_bh(&bat_priv->gw.list_lock);

		curr_gw = batadv_gw_get_selected_gw_node(bat_priv);
		अगर (gw_node == curr_gw)
			batadv_gw_reselect(bat_priv);

		अगर (curr_gw)
			batadv_gw_node_put(curr_gw);
	पूर्ण

out:
	अगर (gw_node)
		batadv_gw_node_put(gw_node);
पूर्ण

/**
 * batadv_gw_node_delete() - Remove orig_node from gateway list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is currently in process of being हटाओd
 */
व्योम batadv_gw_node_delete(काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_tvlv_gateway_data gateway;

	gateway.bandwidth_करोwn = 0;
	gateway.bandwidth_up = 0;

	batadv_gw_node_update(bat_priv, orig_node, &gateway);
पूर्ण

/**
 * batadv_gw_node_मुक्त() - Free gateway inक्रमmation from soft पूर्णांकerface
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_gw_node_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_gw_node *gw_node;
	काष्ठा hlist_node *node_पंचांगp;

	spin_lock_bh(&bat_priv->gw.list_lock);
	hlist_क्रम_each_entry_safe(gw_node, node_पंचांगp,
				  &bat_priv->gw.gateway_list, list) अणु
		hlist_del_init_rcu(&gw_node->list);
		batadv_gw_node_put(gw_node);
		bat_priv->gw.generation++;
	पूर्ण
	spin_unlock_bh(&bat_priv->gw.list_lock);
पूर्ण

/**
 * batadv_gw_dump() - Dump gateways पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 *
 * Return: Error code, or length of message
 */
पूर्णांक batadv_gw_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_priv *bat_priv;
	पूर्णांक अगरindex;
	पूर्णांक ret;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh,
					     BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace || !batadv_softअगर_is_valid(soft_अगरace)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर || primary_अगर->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (!bat_priv->algo_ops->gw.dump) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	bat_priv->algo_ops->gw.dump(msg, cb, bat_priv);

	ret = msg->len;

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	वापस ret;
पूर्ण

/**
 * batadv_gw_dhcp_recipient_get() - check अगर a packet is a DHCP message
 * @skb: the packet to check
 * @header_len: a poपूर्णांकer to the baपंचांगan-adv header size
 * @chaddr: buffer where the client address will be stored. Valid
 *  only अगर the function वापसs BATADV_DHCP_TO_CLIENT
 *
 * This function may re-allocate the data buffer of the skb passed as argument.
 *
 * Return:
 * - BATADV_DHCP_NO अगर the packet is not a dhcp message or अगर there was an error
 *   जबतक parsing it
 * - BATADV_DHCP_TO_SERVER अगर this is a message going to the DHCP server
 * - BATADV_DHCP_TO_CLIENT अगर this is a message going to a DHCP client
 */
क्रमागत batadv_dhcp_recipient
batadv_gw_dhcp_recipient_get(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *header_len,
			     u8 *chaddr)
अणु
	क्रमागत batadv_dhcp_recipient ret = BATADV_DHCP_NO;
	काष्ठा ethhdr *ethhdr;
	काष्ठा iphdr *iphdr;
	काष्ठा ipv6hdr *ipv6hdr;
	काष्ठा udphdr *udphdr;
	काष्ठा vlan_ethhdr *vhdr;
	पूर्णांक chaddr_offset;
	__be16 proto;
	u8 *p;

	/* check क्रम ethernet header */
	अगर (!pskb_may_pull(skb, *header_len + ETH_HLEN))
		वापस BATADV_DHCP_NO;

	ethhdr = eth_hdr(skb);
	proto = ethhdr->h_proto;
	*header_len += ETH_HLEN;

	/* check क्रम initial vlan header */
	अगर (proto == htons(ETH_P_8021Q)) अणु
		अगर (!pskb_may_pull(skb, *header_len + VLAN_HLEN))
			वापस BATADV_DHCP_NO;

		vhdr = vlan_eth_hdr(skb);
		proto = vhdr->h_vlan_encapsulated_proto;
		*header_len += VLAN_HLEN;
	पूर्ण

	/* check क्रम ip header */
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		अगर (!pskb_may_pull(skb, *header_len + माप(*iphdr)))
			वापस BATADV_DHCP_NO;

		iphdr = (काष्ठा iphdr *)(skb->data + *header_len);
		*header_len += iphdr->ihl * 4;

		/* check क्रम udp header */
		अगर (iphdr->protocol != IPPROTO_UDP)
			वापस BATADV_DHCP_NO;

		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (!pskb_may_pull(skb, *header_len + माप(*ipv6hdr)))
			वापस BATADV_DHCP_NO;

		ipv6hdr = (काष्ठा ipv6hdr *)(skb->data + *header_len);
		*header_len += माप(*ipv6hdr);

		/* check क्रम udp header */
		अगर (ipv6hdr->nexthdr != IPPROTO_UDP)
			वापस BATADV_DHCP_NO;

		अवरोध;
	शेष:
		वापस BATADV_DHCP_NO;
	पूर्ण

	अगर (!pskb_may_pull(skb, *header_len + माप(*udphdr)))
		वापस BATADV_DHCP_NO;

	udphdr = (काष्ठा udphdr *)(skb->data + *header_len);
	*header_len += माप(*udphdr);

	/* check क्रम bootp port */
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		अगर (udphdr->dest == htons(67))
			ret = BATADV_DHCP_TO_SERVER;
		अन्यथा अगर (udphdr->source == htons(67))
			ret = BATADV_DHCP_TO_CLIENT;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (udphdr->dest == htons(547))
			ret = BATADV_DHCP_TO_SERVER;
		अन्यथा अगर (udphdr->source == htons(547))
			ret = BATADV_DHCP_TO_CLIENT;
		अवरोध;
	पूर्ण

	chaddr_offset = *header_len + BATADV_DHCP_CHADDR_OFFSET;
	/* store the client address अगर the message is going to a client */
	अगर (ret == BATADV_DHCP_TO_CLIENT) अणु
		अगर (!pskb_may_pull(skb, chaddr_offset + ETH_ALEN))
			वापस BATADV_DHCP_NO;

		/* check अगर the DHCP packet carries an Ethernet DHCP */
		p = skb->data + *header_len + BATADV_DHCP_HTYPE_OFFSET;
		अगर (*p != BATADV_DHCP_HTYPE_ETHERNET)
			वापस BATADV_DHCP_NO;

		/* check अगर the DHCP packet carries a valid Ethernet address */
		p = skb->data + *header_len + BATADV_DHCP_HLEN_OFFSET;
		अगर (*p != ETH_ALEN)
			वापस BATADV_DHCP_NO;

		ether_addr_copy(chaddr, skb->data + chaddr_offset);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * batadv_gw_out_of_range() - check अगर the dhcp request destination is the best
 *  gateway
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the outgoing packet
 *
 * Check अगर the skb is a DHCP request and अगर it is sent to the current best GW
 * server. Due to topology changes it may be the हाल that the GW server
 * previously selected is not the best one anymore.
 *
 * This call might पुनः_स्मृतिate skb data.
 * Must be invoked only when the DHCP packet is going TO a DHCP SERVER.
 *
 * Return: true अगर the packet destination is unicast and it is not the best gw,
 * false otherwise.
 */
bool batadv_gw_out_of_range(काष्ठा batadv_priv *bat_priv,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_neigh_node *neigh_curr = शून्य;
	काष्ठा batadv_neigh_node *neigh_old = शून्य;
	काष्ठा batadv_orig_node *orig_dst_node = शून्य;
	काष्ठा batadv_gw_node *gw_node = शून्य;
	काष्ठा batadv_gw_node *curr_gw = शून्य;
	काष्ठा batadv_neigh_अगरinfo *curr_अगरinfo, *old_अगरinfo;
	काष्ठा ethhdr *ethhdr = (काष्ठा ethhdr *)skb->data;
	bool out_of_range = false;
	u8 curr_tq_avg;
	अचिन्हित लघु vid;

	vid = batadv_get_vid(skb, 0);

	अगर (is_multicast_ether_addr(ethhdr->h_dest))
		जाओ out;

	orig_dst_node = batadv_transtable_search(bat_priv, ethhdr->h_source,
						 ethhdr->h_dest, vid);
	अगर (!orig_dst_node)
		जाओ out;

	gw_node = batadv_gw_node_get(bat_priv, orig_dst_node);
	अगर (!gw_node)
		जाओ out;

	चयन (atomic_पढ़ो(&bat_priv->gw.mode)) अणु
	हाल BATADV_GW_MODE_SERVER:
		/* If we are a GW then we are our best GW. We can artअगरicially
		 * set the tq towards ourself as the maximum value
		 */
		curr_tq_avg = BATADV_TQ_MAX_VALUE;
		अवरोध;
	हाल BATADV_GW_MODE_CLIENT:
		curr_gw = batadv_gw_get_selected_gw_node(bat_priv);
		अगर (!curr_gw)
			जाओ out;

		/* packet is going to our gateway */
		अगर (curr_gw->orig_node == orig_dst_node)
			जाओ out;

		/* If the dhcp packet has been sent to a dअगरferent gw,
		 * we have to evaluate whether the old gw is still
		 * reliable enough
		 */
		neigh_curr = batadv_find_router(bat_priv, curr_gw->orig_node,
						शून्य);
		अगर (!neigh_curr)
			जाओ out;

		curr_अगरinfo = batadv_neigh_अगरinfo_get(neigh_curr,
						      BATADV_IF_DEFAULT);
		अगर (!curr_अगरinfo)
			जाओ out;

		curr_tq_avg = curr_अगरinfo->bat_iv.tq_avg;
		batadv_neigh_अगरinfo_put(curr_अगरinfo);

		अवरोध;
	हाल BATADV_GW_MODE_OFF:
	शेष:
		जाओ out;
	पूर्ण

	neigh_old = batadv_find_router(bat_priv, orig_dst_node, शून्य);
	अगर (!neigh_old)
		जाओ out;

	old_अगरinfo = batadv_neigh_अगरinfo_get(neigh_old, BATADV_IF_DEFAULT);
	अगर (!old_अगरinfo)
		जाओ out;

	अगर ((curr_tq_avg - old_अगरinfo->bat_iv.tq_avg) > BATADV_GW_THRESHOLD)
		out_of_range = true;
	batadv_neigh_अगरinfo_put(old_अगरinfo);

out:
	अगर (orig_dst_node)
		batadv_orig_node_put(orig_dst_node);
	अगर (curr_gw)
		batadv_gw_node_put(curr_gw);
	अगर (gw_node)
		batadv_gw_node_put(gw_node);
	अगर (neigh_old)
		batadv_neigh_node_put(neigh_old);
	अगर (neigh_curr)
		batadv_neigh_node_put(neigh_curr);
	वापस out_of_range;
पूर्ण
