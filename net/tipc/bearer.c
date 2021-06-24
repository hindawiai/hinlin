<शैली गुरु>
/*
 * net/tipc/bearer.c: TIPC bearer code
 *
 * Copyright (c) 1996-2006, 2013-2016, Ericsson AB
 * Copyright (c) 2004-2006, 2010-2013, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <net/sock.h>
#समावेश "core.h"
#समावेश "bearer.h"
#समावेश "link.h"
#समावेश "discover.h"
#समावेश "monitor.h"
#समावेश "bcast.h"
#समावेश "netlink.h"
#समावेश "udp_media.h"
#समावेश "trace.h"
#समावेश "crypto.h"

#घोषणा MAX_ADDR_STR 60

अटल काष्ठा tipc_media * स्थिर media_info_array[] = अणु
	&eth_media_info,
#अगर_घोषित CONFIG_TIPC_MEDIA_IB
	&ib_media_info,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
	&udp_media_info,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल काष्ठा tipc_bearer *bearer_get(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	वापस rcu_dereference(tn->bearer_list[bearer_id]);
पूर्ण

अटल व्योम bearer_disable(काष्ठा net *net, काष्ठा tipc_bearer *b);
अटल पूर्णांक tipc_l2_rcv_msg(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);

/**
 * tipc_media_find - locates specअगरied media object by name
 * @name: name to locate
 */
काष्ठा tipc_media *tipc_media_find(स्थिर अक्षर *name)
अणु
	u32 i;

	क्रम (i = 0; media_info_array[i] != शून्य; i++) अणु
		अगर (!म_भेद(media_info_array[i]->name, name))
			अवरोध;
	पूर्ण
	वापस media_info_array[i];
पूर्ण

/**
 * media_find_id - locates specअगरied media object by type identअगरier
 * @type: type identअगरier to locate
 */
अटल काष्ठा tipc_media *media_find_id(u8 type)
अणु
	u32 i;

	क्रम (i = 0; media_info_array[i] != शून्य; i++) अणु
		अगर (media_info_array[i]->type_id == type)
			अवरोध;
	पूर्ण
	वापस media_info_array[i];
पूर्ण

/**
 * tipc_media_addr_म_लिखो - record media address in prपूर्णांक buffer
 * @buf: output buffer
 * @len: output buffer size reमुख्यing
 * @a: input media address
 */
पूर्णांक tipc_media_addr_म_लिखो(अक्षर *buf, पूर्णांक len, काष्ठा tipc_media_addr *a)
अणु
	अक्षर addr_str[MAX_ADDR_STR];
	काष्ठा tipc_media *m;
	पूर्णांक ret;

	m = media_find_id(a->media_id);

	अगर (m && !m->addr2str(a, addr_str, माप(addr_str)))
		ret = scnम_लिखो(buf, len, "%s(%s)", m->name, addr_str);
	अन्यथा अणु
		u32 i;

		ret = scnम_लिखो(buf, len, "UNKNOWN(%u)", a->media_id);
		क्रम (i = 0; i < माप(a->value); i++)
			ret += scnम_लिखो(buf + ret, len - ret,
					    "-%x", a->value[i]);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * bearer_name_validate - validate & (optionally) deस्थिरruct bearer name
 * @name: ptr to bearer name string
 * @name_parts: ptr to area क्रम bearer name components (or शून्य अगर not needed)
 *
 * Return: 1 अगर bearer name is valid, otherwise 0.
 */
अटल पूर्णांक bearer_name_validate(स्थिर अक्षर *name,
				काष्ठा tipc_bearer_names *name_parts)
अणु
	अक्षर name_copy[TIPC_MAX_BEARER_NAME];
	अक्षर *media_name;
	अक्षर *अगर_name;
	u32 media_len;
	u32 अगर_len;

	/* copy bearer name & ensure length is OK */
	अगर (strscpy(name_copy, name, TIPC_MAX_BEARER_NAME) < 0)
		वापस 0;

	/* ensure all component parts of bearer name are present */
	media_name = name_copy;
	अगर_name = म_अक्षर(media_name, ':');
	अगर (अगर_name == शून्य)
		वापस 0;
	*(अगर_name++) = 0;
	media_len = अगर_name - media_name;
	अगर_len = म_माप(अगर_name) + 1;

	/* validate component parts of bearer name */
	अगर ((media_len <= 1) || (media_len > TIPC_MAX_MEDIA_NAME) ||
	    (अगर_len <= 1) || (अगर_len > TIPC_MAX_IF_NAME))
		वापस 0;

	/* वापस bearer name components, अगर necessary */
	अगर (name_parts) अणु
		म_नकल(name_parts->media_name, media_name);
		म_नकल(name_parts->अगर_name, अगर_name);
	पूर्ण
	वापस 1;
पूर्ण

/**
 * tipc_bearer_find - locates bearer object with matching bearer name
 * @net: the applicable net namespace
 * @name: bearer name to locate
 */
काष्ठा tipc_bearer *tipc_bearer_find(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_bearer *b;
	u32 i;

	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		b = rtnl_dereference(tn->bearer_list[i]);
		अगर (b && (!म_भेद(b->name, name)))
			वापस b;
	पूर्ण
	वापस शून्य;
पूर्ण

/*     tipc_bearer_get_name - get the bearer name from its id.
 *     @net: network namespace
 *     @name: a poपूर्णांकer to the buffer where the name will be stored.
 *     @bearer_id: the id to get the name from.
 */
पूर्णांक tipc_bearer_get_name(काष्ठा net *net, अक्षर *name, u32 bearer_id)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_bearer *b;

	अगर (bearer_id >= MAX_BEARERS)
		वापस -EINVAL;

	b = rtnl_dereference(tn->bearer_list[bearer_id]);
	अगर (!b)
		वापस -EINVAL;

	म_नकल(name, b->name);
	वापस 0;
पूर्ण

व्योम tipc_bearer_add_dest(काष्ठा net *net, u32 bearer_id, u32 dest)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_bearer *b;

	rcu_पढ़ो_lock();
	b = rcu_dereference(tn->bearer_list[bearer_id]);
	अगर (b)
		tipc_disc_add_dest(b->disc);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम tipc_bearer_हटाओ_dest(काष्ठा net *net, u32 bearer_id, u32 dest)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_bearer *b;

	rcu_पढ़ो_lock();
	b = rcu_dereference(tn->bearer_list[bearer_id]);
	अगर (b)
		tipc_disc_हटाओ_dest(b->disc);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * tipc_enable_bearer - enable bearer with the given name
 * @net: the applicable net namespace
 * @name: bearer name to enable
 * @disc_करोमुख्य: bearer करोमुख्य
 * @prio: bearer priority
 * @attr: nlattr array
 * @extack: netlink extended ack
 */
अटल पूर्णांक tipc_enable_bearer(काष्ठा net *net, स्थिर अक्षर *name,
			      u32 disc_करोमुख्य, u32 prio,
			      काष्ठा nlattr *attr[],
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_bearer_names b_names;
	पूर्णांक with_this_prio = 1;
	काष्ठा tipc_bearer *b;
	काष्ठा tipc_media *m;
	काष्ठा sk_buff *skb;
	पूर्णांक bearer_id = 0;
	पूर्णांक res = -EINVAL;
	अक्षर *errstr = "";
	u32 i;

	अगर (!bearer_name_validate(name, &b_names)) अणु
		errstr = "illegal name";
		NL_SET_ERR_MSG(extack, "Illegal name");
		जाओ rejected;
	पूर्ण

	अगर (prio > TIPC_MAX_LINK_PRI && prio != TIPC_MEDIA_LINK_PRI) अणु
		errstr = "illegal priority";
		NL_SET_ERR_MSG(extack, "Illegal priority");
		जाओ rejected;
	पूर्ण

	m = tipc_media_find(b_names.media_name);
	अगर (!m) अणु
		errstr = "media not registered";
		NL_SET_ERR_MSG(extack, "Media not registered");
		जाओ rejected;
	पूर्ण

	अगर (prio == TIPC_MEDIA_LINK_PRI)
		prio = m->priority;

	/* Check new bearer vs existing ones and find मुक्त bearer id अगर any */
	bearer_id = MAX_BEARERS;
	i = MAX_BEARERS;
	जबतक (i-- != 0) अणु
		b = rtnl_dereference(tn->bearer_list[i]);
		अगर (!b) अणु
			bearer_id = i;
			जारी;
		पूर्ण
		अगर (!म_भेद(name, b->name)) अणु
			errstr = "already enabled";
			NL_SET_ERR_MSG(extack, "Already enabled");
			जाओ rejected;
		पूर्ण

		अगर (b->priority == prio &&
		    (++with_this_prio > 2)) अणु
			pr_warn("Bearer <%s>: already 2 bearers with priority %u\n",
				name, prio);

			अगर (prio == TIPC_MIN_LINK_PRI) अणु
				errstr = "cannot adjust to lower";
				NL_SET_ERR_MSG(extack, "Cannot adjust to lower");
				जाओ rejected;
			पूर्ण

			pr_warn("Bearer <%s>: trying with adjusted priority\n",
				name);
			prio--;
			bearer_id = MAX_BEARERS;
			i = MAX_BEARERS;
			with_this_prio = 1;
		पूर्ण
	पूर्ण

	अगर (bearer_id >= MAX_BEARERS) अणु
		errstr = "max 3 bearers permitted";
		NL_SET_ERR_MSG(extack, "Max 3 bearers permitted");
		जाओ rejected;
	पूर्ण

	b = kzalloc(माप(*b), GFP_ATOMIC);
	अगर (!b)
		वापस -ENOMEM;

	म_नकल(b->name, name);
	b->media = m;
	res = m->enable_media(net, b, attr);
	अगर (res) अणु
		kमुक्त(b);
		errstr = "failed to enable media";
		NL_SET_ERR_MSG(extack, "Failed to enable media");
		जाओ rejected;
	पूर्ण

	b->identity = bearer_id;
	b->tolerance = m->tolerance;
	b->min_win = m->min_win;
	b->max_win = m->max_win;
	b->करोमुख्य = disc_करोमुख्य;
	b->net_plane = bearer_id + 'A';
	b->priority = prio;
	refcount_set(&b->refcnt, 1);

	res = tipc_disc_create(net, b, &b->bcast_addr, &skb);
	अगर (res) अणु
		bearer_disable(net, b);
		errstr = "failed to create discoverer";
		NL_SET_ERR_MSG(extack, "Failed to create discoverer");
		जाओ rejected;
	पूर्ण

	test_and_set_bit_lock(0, &b->up);
	rcu_assign_poपूर्णांकer(tn->bearer_list[bearer_id], b);
	अगर (skb)
		tipc_bearer_xmit_skb(net, bearer_id, skb, &b->bcast_addr);

	अगर (tipc_mon_create(net, bearer_id)) अणु
		bearer_disable(net, b);
		वापस -ENOMEM;
	पूर्ण

	pr_info("Enabled bearer <%s>, priority %u\n", name, prio);

	वापस res;
rejected:
	pr_warn("Enabling of bearer <%s> rejected, %s\n", name, errstr);
	वापस res;
पूर्ण

/**
 * tipc_reset_bearer - Reset all links established over this bearer
 * @net: the applicable net namespace
 * @b: the target bearer
 */
अटल पूर्णांक tipc_reset_bearer(काष्ठा net *net, काष्ठा tipc_bearer *b)
अणु
	pr_info("Resetting bearer <%s>\n", b->name);
	tipc_node_delete_links(net, b->identity);
	tipc_disc_reset(net, b);
	वापस 0;
पूर्ण

bool tipc_bearer_hold(काष्ठा tipc_bearer *b)
अणु
	वापस (b && refcount_inc_not_zero(&b->refcnt));
पूर्ण

व्योम tipc_bearer_put(काष्ठा tipc_bearer *b)
अणु
	अगर (b && refcount_dec_and_test(&b->refcnt))
		kमुक्त_rcu(b, rcu);
पूर्ण

/**
 * bearer_disable - disable this bearer
 * @net: the applicable net namespace
 * @b: the bearer to disable
 *
 * Note: This routine assumes caller holds RTNL lock.
 */
अटल व्योम bearer_disable(काष्ठा net *net, काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	पूर्णांक bearer_id = b->identity;

	pr_info("Disabling bearer <%s>\n", b->name);
	clear_bit_unlock(0, &b->up);
	tipc_node_delete_links(net, bearer_id);
	b->media->disable_media(b);
	RCU_INIT_POINTER(b->media_ptr, शून्य);
	अगर (b->disc)
		tipc_disc_delete(b->disc);
	RCU_INIT_POINTER(tn->bearer_list[bearer_id], शून्य);
	tipc_bearer_put(b);
	tipc_mon_delete(net, bearer_id);
पूर्ण

पूर्णांक tipc_enable_l2_media(काष्ठा net *net, काष्ठा tipc_bearer *b,
			 काष्ठा nlattr *attr[])
अणु
	अक्षर *dev_name = म_अक्षर((स्थिर अक्षर *)b->name, ':') + 1;
	पूर्णांक hwaddr_len = b->media->hwaddr_len;
	u8 node_id[NODE_ID_LEN] = अणु0,पूर्ण;
	काष्ठा net_device *dev;

	/* Find device with specअगरied name */
	dev = dev_get_by_name(net, dev_name);
	अगर (!dev)
		वापस -ENODEV;
	अगर (tipc_mtu_bad(dev, 0)) अणु
		dev_put(dev);
		वापस -EINVAL;
	पूर्ण
	अगर (dev == net->loopback_dev) अणु
		dev_put(dev);
		pr_info("Enabling <%s> not permitted\n", b->name);
		वापस -EINVAL;
	पूर्ण

	/* Autoconfigure own node identity अगर needed */
	अगर (!tipc_own_id(net) && hwaddr_len <= NODE_ID_LEN) अणु
		स_नकल(node_id, dev->dev_addr, hwaddr_len);
		tipc_net_init(net, node_id, 0);
	पूर्ण
	अगर (!tipc_own_id(net)) अणु
		dev_put(dev);
		pr_warn("Failed to obtain node identity\n");
		वापस -EINVAL;
	पूर्ण

	/* Associate TIPC bearer with L2 bearer */
	rcu_assign_poपूर्णांकer(b->media_ptr, dev);
	b->pt.dev = dev;
	b->pt.type = htons(ETH_P_TIPC);
	b->pt.func = tipc_l2_rcv_msg;
	dev_add_pack(&b->pt);
	स_रखो(&b->bcast_addr, 0, माप(b->bcast_addr));
	स_नकल(b->bcast_addr.value, dev->broadcast, hwaddr_len);
	b->bcast_addr.media_id = b->media->type_id;
	b->bcast_addr.broadcast = TIPC_BROADCAST_SUPPORT;
	b->mtu = dev->mtu;
	b->media->raw2addr(b, &b->addr, (अक्षर *)dev->dev_addr);
	rcu_assign_poपूर्णांकer(dev->tipc_ptr, b);
	वापस 0;
पूर्ण

/* tipc_disable_l2_media - detach TIPC bearer from an L2 पूर्णांकerface
 * @b: the target bearer
 *
 * Mark L2 bearer as inactive so that incoming buffers are thrown away
 */
व्योम tipc_disable_l2_media(काष्ठा tipc_bearer *b)
अणु
	काष्ठा net_device *dev;

	dev = (काष्ठा net_device *)rtnl_dereference(b->media_ptr);
	dev_हटाओ_pack(&b->pt);
	RCU_INIT_POINTER(dev->tipc_ptr, शून्य);
	synchronize_net();
	dev_put(dev);
पूर्ण

/**
 * tipc_l2_send_msg - send a TIPC packet out over an L2 पूर्णांकerface
 * @net: the associated network namespace
 * @skb: the packet to be sent
 * @b: the bearer through which the packet is to be sent
 * @dest: peer destination address
 */
पूर्णांक tipc_l2_send_msg(काष्ठा net *net, काष्ठा sk_buff *skb,
		     काष्ठा tipc_bearer *b, काष्ठा tipc_media_addr *dest)
अणु
	काष्ठा net_device *dev;
	पूर्णांक delta;

	dev = (काष्ठा net_device *)rcu_dereference(b->media_ptr);
	अगर (!dev)
		वापस 0;

	delta = SKB_DATA_ALIGN(dev->hard_header_len - skb_headroom(skb));
	अगर ((delta > 0) && pskb_expand_head(skb, delta, 0, GFP_ATOMIC)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	skb_reset_network_header(skb);
	skb->dev = dev;
	skb->protocol = htons(ETH_P_TIPC);
	dev_hard_header(skb, dev, ETH_P_TIPC, dest->value,
			dev->dev_addr, skb->len);
	dev_queue_xmit(skb);
	वापस 0;
पूर्ण

bool tipc_bearer_bcast_support(काष्ठा net *net, u32 bearer_id)
अणु
	bool supp = false;
	काष्ठा tipc_bearer *b;

	rcu_पढ़ो_lock();
	b = bearer_get(net, bearer_id);
	अगर (b)
		supp = (b->bcast_addr.broadcast == TIPC_BROADCAST_SUPPORT);
	rcu_पढ़ो_unlock();
	वापस supp;
पूर्ण

पूर्णांक tipc_bearer_mtu(काष्ठा net *net, u32 bearer_id)
अणु
	पूर्णांक mtu = 0;
	काष्ठा tipc_bearer *b;

	rcu_पढ़ो_lock();
	b = rcu_dereference(tipc_net(net)->bearer_list[bearer_id]);
	अगर (b)
		mtu = b->mtu;
	rcu_पढ़ो_unlock();
	वापस mtu;
पूर्ण

/* tipc_bearer_xmit_skb - sends buffer to destination over bearer
 */
व्योम tipc_bearer_xmit_skb(काष्ठा net *net, u32 bearer_id,
			  काष्ठा sk_buff *skb,
			  काष्ठा tipc_media_addr *dest)
अणु
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	काष्ठा tipc_bearer *b;

	rcu_पढ़ो_lock();
	b = bearer_get(net, bearer_id);
	अगर (likely(b && (test_bit(0, &b->up) || msg_is_reset(hdr)))) अणु
#अगर_घोषित CONFIG_TIPC_CRYPTO
		tipc_crypto_xmit(net, &skb, b, dest, शून्य);
		अगर (skb)
#पूर्ण_अगर
			b->media->send_msg(net, skb, b, dest);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* tipc_bearer_xmit() -send buffer to destination over bearer
 */
व्योम tipc_bearer_xmit(काष्ठा net *net, u32 bearer_id,
		      काष्ठा sk_buff_head *xmitq,
		      काष्ठा tipc_media_addr *dst,
		      काष्ठा tipc_node *__dnode)
अणु
	काष्ठा tipc_bearer *b;
	काष्ठा sk_buff *skb, *पंचांगp;

	अगर (skb_queue_empty(xmitq))
		वापस;

	rcu_पढ़ो_lock();
	b = bearer_get(net, bearer_id);
	अगर (unlikely(!b))
		__skb_queue_purge(xmitq);
	skb_queue_walk_safe(xmitq, skb, पंचांगp) अणु
		__skb_dequeue(xmitq);
		अगर (likely(test_bit(0, &b->up) || msg_is_reset(buf_msg(skb)))) अणु
#अगर_घोषित CONFIG_TIPC_CRYPTO
			tipc_crypto_xmit(net, &skb, b, dst, __dnode);
			अगर (skb)
#पूर्ण_अगर
				b->media->send_msg(net, skb, b, dst);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* tipc_bearer_bc_xmit() - broadcast buffers to all destinations
 */
व्योम tipc_bearer_bc_xmit(काष्ठा net *net, u32 bearer_id,
			 काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_media_addr *dst;
	पूर्णांक net_id = tn->net_id;
	काष्ठा tipc_bearer *b;
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा tipc_msg *hdr;

	rcu_पढ़ो_lock();
	b = bearer_get(net, bearer_id);
	अगर (unlikely(!b || !test_bit(0, &b->up)))
		__skb_queue_purge(xmitq);
	skb_queue_walk_safe(xmitq, skb, पंचांगp) अणु
		hdr = buf_msg(skb);
		msg_set_non_seq(hdr, 1);
		msg_set_mc_netid(hdr, net_id);
		__skb_dequeue(xmitq);
		dst = &b->bcast_addr;
#अगर_घोषित CONFIG_TIPC_CRYPTO
		tipc_crypto_xmit(net, &skb, b, dst, शून्य);
		अगर (skb)
#पूर्ण_अगर
			b->media->send_msg(net, skb, b, dst);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * tipc_l2_rcv_msg - handle incoming TIPC message from an पूर्णांकerface
 * @skb: the received message
 * @dev: the net device that the packet was received on
 * @pt: the packet_type काष्ठाure which was used to रेजिस्टर this handler
 * @orig_dev: the original receive net device in हाल the device is a bond
 *
 * Accept only packets explicitly sent to this node, or broadcast packets;
 * ignores packets sent using पूर्णांकerface multicast, and traffic sent to other
 * nodes (which can happen अगर पूर्णांकerface is running in promiscuous mode).
 */
अटल पूर्णांक tipc_l2_rcv_msg(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा tipc_bearer *b;

	rcu_पढ़ो_lock();
	b = rcu_dereference(dev->tipc_ptr) ?:
		rcu_dereference(orig_dev->tipc_ptr);
	अगर (likely(b && test_bit(0, &b->up) &&
		   (skb->pkt_type <= PACKET_MULTICAST))) अणु
		skb_mark_not_on_list(skb);
		TIPC_SKB_CB(skb)->flags = 0;
		tipc_rcv(dev_net(b->pt.dev), skb, b);
		rcu_पढ़ो_unlock();
		वापस NET_RX_SUCCESS;
	पूर्ण
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

/**
 * tipc_l2_device_event - handle device events from network device
 * @nb: the context of the notअगरication
 * @evt: the type of event
 * @ptr: the net device that the event was on
 *
 * This function is called by the Ethernet driver in हाल of link
 * change event.
 */
अटल पूर्णांक tipc_l2_device_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ evt,
				व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा tipc_bearer *b;

	b = rtnl_dereference(dev->tipc_ptr);
	अगर (!b)
		वापस NOTIFY_DONE;

	trace_tipc_l2_device_event(dev, b, evt);
	चयन (evt) अणु
	हाल NETDEV_CHANGE:
		अगर (netअगर_carrier_ok(dev) && netअगर_oper_up(dev)) अणु
			test_and_set_bit_lock(0, &b->up);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल NETDEV_GOING_DOWN:
		clear_bit_unlock(0, &b->up);
		tipc_reset_bearer(net, b);
		अवरोध;
	हाल NETDEV_UP:
		test_and_set_bit_lock(0, &b->up);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (tipc_mtu_bad(dev, 0)) अणु
			bearer_disable(net, b);
			अवरोध;
		पूर्ण
		b->mtu = dev->mtu;
		tipc_reset_bearer(net, b);
		अवरोध;
	हाल NETDEV_CHANGEADDR:
		b->media->raw2addr(b, &b->addr,
				   (अक्षर *)dev->dev_addr);
		tipc_reset_bearer(net, b);
		अवरोध;
	हाल NETDEV_UNREGISTER:
	हाल NETDEV_CHANGENAME:
		bearer_disable(net, b);
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block notअगरier = अणु
	.notअगरier_call  = tipc_l2_device_event,
	.priority	= 0,
पूर्ण;

पूर्णांक tipc_bearer_setup(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&notअगरier);
पूर्ण

व्योम tipc_bearer_cleanup(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&notअगरier);
पूर्ण

व्योम tipc_bearer_stop(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_bearer *b;
	u32 i;

	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		b = rtnl_dereference(tn->bearer_list[i]);
		अगर (b) अणु
			bearer_disable(net, b);
			tn->bearer_list[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम tipc_clone_to_loopback(काष्ठा net *net, काष्ठा sk_buff_head *pkts)
अणु
	काष्ठा net_device *dev = net->loopback_dev;
	काष्ठा sk_buff *skb, *_skb;
	पूर्णांक exp;

	skb_queue_walk(pkts, _skb) अणु
		skb = pskb_copy(_skb, GFP_ATOMIC);
		अगर (!skb)
			जारी;

		exp = SKB_DATA_ALIGN(dev->hard_header_len - skb_headroom(skb));
		अगर (exp > 0 && pskb_expand_head(skb, exp, 0, GFP_ATOMIC)) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		skb_reset_network_header(skb);
		dev_hard_header(skb, dev, ETH_P_TIPC, dev->dev_addr,
				dev->dev_addr, skb->len);
		skb->dev = dev;
		skb->pkt_type = PACKET_HOST;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx_ni(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक tipc_loopback_rcv_pkt(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				 काष्ठा packet_type *pt, काष्ठा net_device *od)
अणु
	consume_skb(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

पूर्णांक tipc_attach_loopback(काष्ठा net *net)
अणु
	काष्ठा net_device *dev = net->loopback_dev;
	काष्ठा tipc_net *tn = tipc_net(net);

	अगर (!dev)
		वापस -ENODEV;

	dev_hold(dev);
	tn->loopback_pt.dev = dev;
	tn->loopback_pt.type = htons(ETH_P_TIPC);
	tn->loopback_pt.func = tipc_loopback_rcv_pkt;
	dev_add_pack(&tn->loopback_pt);
	वापस 0;
पूर्ण

व्योम tipc_detach_loopback(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	dev_हटाओ_pack(&tn->loopback_pt);
	dev_put(net->loopback_dev);
पूर्ण

/* Caller should hold rtnl_lock to protect the bearer */
अटल पूर्णांक __tipc_nl_add_bearer(काष्ठा tipc_nl_msg *msg,
				काष्ठा tipc_bearer *bearer, पूर्णांक nlflags)
अणु
	व्योम *hdr;
	काष्ठा nlattr *attrs;
	काष्ठा nlattr *prop;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  nlflags, TIPC_NL_BEARER_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_BEARER);
	अगर (!attrs)
		जाओ msg_full;

	अगर (nla_put_string(msg->skb, TIPC_NLA_BEARER_NAME, bearer->name))
		जाओ attr_msg_full;

	prop = nla_nest_start_noflag(msg->skb, TIPC_NLA_BEARER_PROP);
	अगर (!prop)
		जाओ prop_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_PRIO, bearer->priority))
		जाओ prop_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_TOL, bearer->tolerance))
		जाओ prop_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_WIN, bearer->max_win))
		जाओ prop_msg_full;
	अगर (bearer->media->type_id == TIPC_MEDIA_TYPE_UDP)
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_MTU, bearer->mtu))
			जाओ prop_msg_full;

	nla_nest_end(msg->skb, prop);

#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
	अगर (bearer->media->type_id == TIPC_MEDIA_TYPE_UDP) अणु
		अगर (tipc_udp_nl_add_bearer_data(msg, bearer))
			जाओ attr_msg_full;
	पूर्ण
#पूर्ण_अगर

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	वापस 0;

prop_msg_full:
	nla_nest_cancel(msg->skb, prop);
attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण

पूर्णांक tipc_nl_bearer_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक err;
	पूर्णांक i = cb->args[0];
	काष्ठा tipc_bearer *bearer;
	काष्ठा tipc_nl_msg msg;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);

	अगर (i == MAX_BEARERS)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rtnl_lock();
	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		bearer = rtnl_dereference(tn->bearer_list[i]);
		अगर (!bearer)
			जारी;

		err = __tipc_nl_add_bearer(&msg, bearer, NLM_F_MULTI);
		अगर (err)
			अवरोध;
	पूर्ण
	rtnl_unlock();

	cb->args[0] = i;
	वापस skb->len;
पूर्ण

पूर्णांक tipc_nl_bearer_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *name;
	काष्ठा sk_buff *rep;
	काष्ठा tipc_bearer *bearer;
	काष्ठा tipc_nl_msg msg;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	काष्ठा net *net = genl_info_net(info);

	अगर (!info->attrs[TIPC_NLA_BEARER])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_BEARER_NAME])
		वापस -EINVAL;
	name = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	rep = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	msg.skb = rep;
	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	rtnl_lock();
	bearer = tipc_bearer_find(net, name);
	अगर (!bearer) अणु
		err = -EINVAL;
		NL_SET_ERR_MSG(info->extack, "Bearer not found");
		जाओ err_out;
	पूर्ण

	err = __tipc_nl_add_bearer(&msg, bearer, 0);
	अगर (err)
		जाओ err_out;
	rtnl_unlock();

	वापस genlmsg_reply(rep, info);
err_out:
	rtnl_unlock();
	nlmsg_मुक्त(rep);

	वापस err;
पूर्ण

पूर्णांक __tipc_nl_bearer_disable(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *name;
	काष्ठा tipc_bearer *bearer;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);

	अगर (!info->attrs[TIPC_NLA_BEARER])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_BEARER_NAME])
		वापस -EINVAL;

	name = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	bearer = tipc_bearer_find(net, name);
	अगर (!bearer) अणु
		NL_SET_ERR_MSG(info->extack, "Bearer not found");
		वापस -EINVAL;
	पूर्ण

	bearer_disable(net, bearer);

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_bearer_disable(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_bearer_disable(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण

पूर्णांक __tipc_nl_bearer_enable(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *bearer;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	u32 करोमुख्य = 0;
	u32 prio;

	prio = TIPC_MEDIA_LINK_PRI;

	अगर (!info->attrs[TIPC_NLA_BEARER])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_BEARER_NAME])
		वापस -EINVAL;

	bearer = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	अगर (attrs[TIPC_NLA_BEARER_DOMAIN])
		करोमुख्य = nla_get_u32(attrs[TIPC_NLA_BEARER_DOMAIN]);

	अगर (attrs[TIPC_NLA_BEARER_PROP]) अणु
		काष्ठा nlattr *props[TIPC_NLA_PROP_MAX + 1];

		err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_BEARER_PROP],
					      props);
		अगर (err)
			वापस err;

		अगर (props[TIPC_NLA_PROP_PRIO])
			prio = nla_get_u32(props[TIPC_NLA_PROP_PRIO]);
	पूर्ण

	वापस tipc_enable_bearer(net, bearer, करोमुख्य, prio, attrs,
				  info->extack);
पूर्ण

पूर्णांक tipc_nl_bearer_enable(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_bearer_enable(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण

पूर्णांक tipc_nl_bearer_add(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *name;
	काष्ठा tipc_bearer *b;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);

	अगर (!info->attrs[TIPC_NLA_BEARER])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_BEARER_NAME])
		वापस -EINVAL;
	name = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	rtnl_lock();
	b = tipc_bearer_find(net, name);
	अगर (!b) अणु
		rtnl_unlock();
		NL_SET_ERR_MSG(info->extack, "Bearer not found");
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
	अगर (attrs[TIPC_NLA_BEARER_UDP_OPTS]) अणु
		err = tipc_udp_nl_bearer_add(b,
					     attrs[TIPC_NLA_BEARER_UDP_OPTS]);
		अगर (err) अणु
			rtnl_unlock();
			वापस err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	rtnl_unlock();

	वापस 0;
पूर्ण

पूर्णांक __tipc_nl_bearer_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा tipc_bearer *b;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	अक्षर *name;
	पूर्णांक err;

	अगर (!info->attrs[TIPC_NLA_BEARER])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_BEARER_NAME])
		वापस -EINVAL;
	name = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	b = tipc_bearer_find(net, name);
	अगर (!b) अणु
		NL_SET_ERR_MSG(info->extack, "Bearer not found");
		वापस -EINVAL;
	पूर्ण

	अगर (attrs[TIPC_NLA_BEARER_PROP]) अणु
		काष्ठा nlattr *props[TIPC_NLA_PROP_MAX + 1];

		err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_BEARER_PROP],
					      props);
		अगर (err)
			वापस err;

		अगर (props[TIPC_NLA_PROP_TOL]) अणु
			b->tolerance = nla_get_u32(props[TIPC_NLA_PROP_TOL]);
			tipc_node_apply_property(net, b, TIPC_NLA_PROP_TOL);
		पूर्ण
		अगर (props[TIPC_NLA_PROP_PRIO])
			b->priority = nla_get_u32(props[TIPC_NLA_PROP_PRIO]);
		अगर (props[TIPC_NLA_PROP_WIN])
			b->max_win = nla_get_u32(props[TIPC_NLA_PROP_WIN]);
		अगर (props[TIPC_NLA_PROP_MTU]) अणु
			अगर (b->media->type_id != TIPC_MEDIA_TYPE_UDP) अणु
				NL_SET_ERR_MSG(info->extack,
					       "MTU property is unsupported");
				वापस -EINVAL;
			पूर्ण
#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
			अगर (tipc_udp_mtu_bad(nla_get_u32
					     (props[TIPC_NLA_PROP_MTU]))) अणु
				NL_SET_ERR_MSG(info->extack,
					       "MTU value is out-of-range");
				वापस -EINVAL;
			पूर्ण
			b->mtu = nla_get_u32(props[TIPC_NLA_PROP_MTU]);
			tipc_node_apply_property(net, b, TIPC_NLA_PROP_MTU);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_bearer_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_bearer_set(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक __tipc_nl_add_media(काष्ठा tipc_nl_msg *msg,
			       काष्ठा tipc_media *media, पूर्णांक nlflags)
अणु
	व्योम *hdr;
	काष्ठा nlattr *attrs;
	काष्ठा nlattr *prop;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  nlflags, TIPC_NL_MEDIA_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MEDIA);
	अगर (!attrs)
		जाओ msg_full;

	अगर (nla_put_string(msg->skb, TIPC_NLA_MEDIA_NAME, media->name))
		जाओ attr_msg_full;

	prop = nla_nest_start_noflag(msg->skb, TIPC_NLA_MEDIA_PROP);
	अगर (!prop)
		जाओ prop_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_PRIO, media->priority))
		जाओ prop_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_TOL, media->tolerance))
		जाओ prop_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_WIN, media->max_win))
		जाओ prop_msg_full;
	अगर (media->type_id == TIPC_MEDIA_TYPE_UDP)
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PROP_MTU, media->mtu))
			जाओ prop_msg_full;

	nla_nest_end(msg->skb, prop);
	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	वापस 0;

prop_msg_full:
	nla_nest_cancel(msg->skb, prop);
attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण

पूर्णांक tipc_nl_media_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक err;
	पूर्णांक i = cb->args[0];
	काष्ठा tipc_nl_msg msg;

	अगर (i == MAX_MEDIA)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rtnl_lock();
	क्रम (; media_info_array[i] != शून्य; i++) अणु
		err = __tipc_nl_add_media(&msg, media_info_array[i],
					  NLM_F_MULTI);
		अगर (err)
			अवरोध;
	पूर्ण
	rtnl_unlock();

	cb->args[0] = i;
	वापस skb->len;
पूर्ण

पूर्णांक tipc_nl_media_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *name;
	काष्ठा tipc_nl_msg msg;
	काष्ठा tipc_media *media;
	काष्ठा sk_buff *rep;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];

	अगर (!info->attrs[TIPC_NLA_MEDIA])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_MEDIA_MAX,
					  info->attrs[TIPC_NLA_MEDIA],
					  tipc_nl_media_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_MEDIA_NAME])
		वापस -EINVAL;
	name = nla_data(attrs[TIPC_NLA_MEDIA_NAME]);

	rep = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	msg.skb = rep;
	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	rtnl_lock();
	media = tipc_media_find(name);
	अगर (!media) अणु
		NL_SET_ERR_MSG(info->extack, "Media not found");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	err = __tipc_nl_add_media(&msg, media, 0);
	अगर (err)
		जाओ err_out;
	rtnl_unlock();

	वापस genlmsg_reply(rep, info);
err_out:
	rtnl_unlock();
	nlmsg_मुक्त(rep);

	वापस err;
पूर्ण

पूर्णांक __tipc_nl_media_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *name;
	काष्ठा tipc_media *m;
	काष्ठा nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];

	अगर (!info->attrs[TIPC_NLA_MEDIA])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_MEDIA_MAX,
					  info->attrs[TIPC_NLA_MEDIA],
					  tipc_nl_media_policy, info->extack);

	अगर (!attrs[TIPC_NLA_MEDIA_NAME])
		वापस -EINVAL;
	name = nla_data(attrs[TIPC_NLA_MEDIA_NAME]);

	m = tipc_media_find(name);
	अगर (!m) अणु
		NL_SET_ERR_MSG(info->extack, "Media not found");
		वापस -EINVAL;
	पूर्ण
	अगर (attrs[TIPC_NLA_MEDIA_PROP]) अणु
		काष्ठा nlattr *props[TIPC_NLA_PROP_MAX + 1];

		err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_MEDIA_PROP],
					      props);
		अगर (err)
			वापस err;

		अगर (props[TIPC_NLA_PROP_TOL])
			m->tolerance = nla_get_u32(props[TIPC_NLA_PROP_TOL]);
		अगर (props[TIPC_NLA_PROP_PRIO])
			m->priority = nla_get_u32(props[TIPC_NLA_PROP_PRIO]);
		अगर (props[TIPC_NLA_PROP_WIN])
			m->max_win = nla_get_u32(props[TIPC_NLA_PROP_WIN]);
		अगर (props[TIPC_NLA_PROP_MTU]) अणु
			अगर (m->type_id != TIPC_MEDIA_TYPE_UDP) अणु
				NL_SET_ERR_MSG(info->extack,
					       "MTU property is unsupported");
				वापस -EINVAL;
			पूर्ण
#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
			अगर (tipc_udp_mtu_bad(nla_get_u32
					     (props[TIPC_NLA_PROP_MTU]))) अणु
				NL_SET_ERR_MSG(info->extack,
					       "MTU value is out-of-range");
				वापस -EINVAL;
			पूर्ण
			m->mtu = nla_get_u32(props[TIPC_NLA_PROP_MTU]);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_media_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_media_set(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण
